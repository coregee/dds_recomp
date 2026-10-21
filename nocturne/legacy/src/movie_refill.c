/* Original decoder refill, DMA callbacks, completion worker and audio reservation. */
#include "movie_refill.h"
#include "movie_archive.h"
#include "movie_decoder.h"
#include "movie_manager.h"
#include "libc_stream.h"
#include "material_fiveword_pool.h"
#include "draw_interrupt.h"
#include "draw_consumer_support.h"
#include "heap_queue.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveMovieArchiveAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int64_t s64(uint64_t v){return v>>63?-1-(int64_t)~v:(int64_t)v;}
static uint64_t consume(uint32_t entry,uint64_t decoder,uint64_t payload,uint64_t event,uint64_t buffer,uint64_t bytes){
 uint64_t arguments[5]={decoder,payload,event,buffer,bytes};
#if UINTPTR_MAX > UINT32_MAX
 return nocturneMovieDecoderConsume(entry,arguments);
#else
 typedef uint64_t (*Callback)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
 return ((Callback)(uintptr_t)entry)(decoder,payload,event,buffer,bytes);
#endif
}
/* 002c43e8: seven ready slots, eight-slot index, 256-byte previous-tail window. */
void ps2MovieDecoderRefill(uint64_t decoder){
 uint32_t d=(uint32_t)decoder,ready=*at(d+82);
 if(*at(d+81)||ready>=7)return;
 do{
  uint32_t slot=(uint32_t)*at(d+83)+ready;if(slot>=8)slot-=8;
  uint32_t output=((r32(d+84)+(slot<<13))&0x0fffffffu)|0x20000000u,ended=0;
#if UINTPTR_MAX > UINT32_MAX
  uint32_t local=nocturneLibcStreamLocalAddress(&ended,4);
#else
  uint32_t local=(uint32_t)(uintptr_t)&ended;
#endif
  uint64_t available=consume(r32(d+92),decoder,sx(r32(d+96)),0,local,0);
#if UINTPTR_MAX > UINT32_MAX
  nocturneLibcStreamEndLocal();
#endif
  if(s64(available)<8192){
   if(!ended)return;
   if(s64(available)>0){(void)consume(r32(d+92),decoder,sx(r32(d+96)),1,sx(output),available);ready++;}
   *at(d+81)=1;
  }else{
   if(available==8192&&ended)*at(d+81)=1;
   (void)consume(r32(d+92),decoder,sx(r32(d+96)),1,sx(output),8192);ready++;
  }
  if(slot==7){
   uint32_t input=output+0x1f00,target=((r32(d+84)-0x100)&0x0fffffffu)|0x20000000u;
   for(unsigned k=0;k<0x100;k+=32){uint64_t words[4];memcpy(words,at(input+k),32);memcpy(at(target+k),words,32);}
  }
  *at(d+82)=(uint8_t)ready;
 }while(!*at(d+81)&&ready<7);
}
/* 002c4b40: the input owner is cleared before callback/refill work. */
uint64_t ps2MovieInputDmaInterrupt(void){
 uint32_t d=r32(0x552158);
 if(d){
  w32(0x552144,r32(d+72));w32(0x552158,0);
  if(*at(d+17)&&*at(d+12)==1){
   if(*at(d+100)){
    *at(d+100)=0;uint8_t slot=(uint8_t)(*at(d+83)+1);*at(d+83)=slot==8?0:slot;
    *at(d+82)=(uint8_t)(*at(d+82)-1);
   }
   ps2MovieDecoderRefill(sx(d));ps2MovieDecoderInputDma(sx(d));
  }
 }
 nocturneDrawInterruptSync();EE_SYSTEM_EI();return 0;
}
/* 002c4b10: includes the thread-ID load omitted by the old Ghidra entry. */
uint64_t ps2MovieOutputDmaInterrupt(void){
 (void)ps2DrawWakeThread(sx(r32(0x552164)));
 nocturneDrawInterruptSync();EE_SYSTEM_EI();return 0;
}
/* 002c4a40 is an infinite worker; external test observation never adds a return. */
void ps2MovieDecoderCompletionThread(void){
 for(;;){
  (void)ps2KernelSleepThread();uint32_t d=r32(0x552154);if(!d)continue;
  ps2MovieIpuSaveContext(sx(d+104));if(!r32(d+112))*at(d+17)=0;
  if(!*at(d+16))*at(d+16)=1;
  *at(d+26)=(uint8_t)(*at(d+26)+1);uint32_t frames=r32(d+68)+1;
  w32(0x552154,0);w32(d+68,frames);
  if(frames==r32(d+64)){
   if(!*at(d+21))*at(d+15)=1;
   else{*at(d+14)=0;w32(d+68,0);*at(d+101)=0;}
  }
  if(!*at(d+15)){
   uint32_t restore=ps2KernelDisableInterrupts();ps2MovieDecoderQueueAppend(sx(d),0);
   if(restore)(void)ps2KernelEnableInterrupts();
  }
  ps2MovieDecoderSchedule(0);
 }
}
/* 002c4c28: release a decoded frame, advance display count and reschedule. */
void ps2MovieDecoderFrameConsumed(uint64_t decoder){
 uint32_t d=(uint32_t)decoder,restore=ps2KernelDisableInterrupts();
 if(*at(d+26)){
  *at(d+26)=(uint8_t)(*at(d+26)-1);*at(d+25)^=1;*at(d+19)=(uint8_t)(*at(d+19)+1);
 }
 uint32_t frames=r32(d+72)+1;w32(d+72,frames);
 if(frames==r32(d+64)&&*at(d+21))w32(d+72,0);
 if(restore)(void)ps2KernelEnableInterrupts();ps2MovieDecoderSchedule(0);
}
/* 002c5098: staged bytes take priority over the semaphore-protected ring. */
uint64_t ps2MovieAudioReserve(uint64_t bytes){
 uint32_t c=r32(0x552168),record=r32(c+28);
 (void)ps2KernelWaitSema(r32(0x551b48));uint32_t available=r32(record+112),output;
 if(s64(sx(available))>0){
  output=r32(record+116);w32(record+112,available-(uint32_t)bytes);w32(record+116,output+(uint32_t)bytes);
 }else{
  uint32_t count=r32(record+104),offset=r32(record+100);output=r32(record+96)+offset;
  uint32_t next=offset+(uint32_t)bytes;
  if(s64(sx(count))<s64(bytes)){output=0;w32(0x55216c,r32(c+108));}
  else{w32(record+104,count-(uint32_t)bytes);if(s64(sx(next))>65535)next-=65536;w32(record+100,next);}
 }
 (void)ps2KernelSignalSema(r32(0x551b48));return sx(output);
}
