/* Complete pointer release, IPU context, decoder scheduling and close bodies. */
#include "movie_decoder.h"
#include "movie_initialize.h"
#include "movie_archive.h"
#include "material_construction_release.h"
#include "material_fiveword_pool.h"
#include "memory_handle_allocation.h"
#include "file_worker_control.h"
#include "heap_queue.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveMovieArchiveAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static int mmio(uint32_t a){return a>=0x10000000&&a<0x10010000;}
static uint32_t r32(uint32_t a){
 if(mmio(a)){
#if UINTPTR_MAX > UINT32_MAX
  return nocturneMovieDecoderMmioRead(a);
#else
  return *(volatile uint32_t *)(uintptr_t)a;
#endif
 }
 uint32_t v;memcpy(&v,at(a),4);return v;
}
static void w32(uint32_t a,uint32_t v){
 if(mmio(a)){
#if UINTPTR_MAX > UINT32_MAX
  nocturneMovieDecoderMmioWrite(a,v);
#else
  *(volatile uint32_t *)(uintptr_t)a=v;
#endif
 }else memcpy(at(a),&v,4);
}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
static int64_t s64(uint64_t v){return v>>63?-1-(int64_t)~v:(int64_t)v;}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t ps2PoolContainsPointer(uint64_t pointer){
 if(s64(pointer)<s32(r32(0x552060)))return 0;
 return s64(pointer)<s32(r32(0x552064));
}
uint64_t ps2MemoryHandleFindPointer(uint64_t pointer){
 uint32_t restore=ps2KernelDisableInterrupts(),node=r32(0x577f1c);
 for(;;){
  uint32_t state=r16(node+12);
  if(state==1&&sx(r32(node+8))==pointer){if(restore)ps2KernelEnableInterrupts();return sx(node);}
  if(state==2&&restore)ps2KernelEnableInterrupts();
  node=r32(node+4);
 }
}
void ps2MemoryPointerFree(uint64_t pointer){ps2MemoryHandleFree((uint32_t)ps2MemoryHandleFindPointer(pointer));}
void ps2PoolOrMemoryPointerFree(uint64_t pointer){
 if(!pointer)return;
 if(ps2PoolContainsPointer(pointer))ps2PoolRelease((uint32_t)pointer);else ps2MemoryPointerFree(pointer);
}
void ps2MovieDeferPointerFree(uint64_t pointer){
 if(!pointer)return;uint32_t node=ps2PoolAllocateZeroed(160);
 if(ps2PoolContainsPointer(pointer)){w32(node+4,(uint32_t)pointer);*at(node+12)=2;}
 else{*at(node+12)=1;w32(node+8,(uint32_t)ps2MemoryHandleFindPointer(pointer));}
 (void)ps2KernelWaitSema(r32(0x581018));uint32_t tail=r32(0x581020);
 if(tail)w32(tail,node);else w32(0x58101c,node);
 w32(0x581020,node);(void)ps2KernelSignalSema(r32(0x581018));
}
void ps2MemoryHandleDeferFree(uint64_t handle){ps2DeferredQueueAppend(0x552098,(uint32_t)handle);}
static uint64_t dmaControl(uint32_t channel,uint64_t control){
 (void)ps2KernelDisableInterrupts();w32(0x1000f590,r32(0x1000f520)|0x10000);
 w32(channel,(uint32_t)control);w32(0x1000f590,r32(0x1000f520)&0xfffeffff);
 return ps2KernelEnableInterrupts();
}
uint64_t ps2MovieIpuFromDmaControl(uint64_t control){return dmaControl(0x1000b000,control);}
uint64_t ps2MovieIpuToDmaControl(uint64_t control){return dmaControl(0x1000b400,control);}
void ps2MovieIpuSaveContext(uint64_t context){
 uint32_t c=(uint32_t)context;(void)ps2MovieIpuToDmaControl(1);
 w32(c,r32(0x1000b410));w32(c+4,r32(0x1000b430));w32(c+8,r32(0x1000b420));w32(c+12,r32(0x1000b400));
 while(r32(0x10002010)&0xf0){}
 (void)ps2MovieIpuFromDmaControl(0);
 w32(c+16,r32(0x1000b010));w32(c+20,r32(0x1000b020));w32(c+24,r32(0x1000b000));w32(c+28,r32(0x10002020));w32(c+32,r32(0x10002010));
}
void ps2MovieIpuRestoreContext(uint64_t context){
 uint32_t c=(uint32_t)context,bp=r32(c+28),bits=bp&127,fifo=((bp>>8)&15)+((bp>>16)&3);
 uint32_t qwc=r32(c+8)+fifo,address=r32(c)-fifo*16,from=r32(c+16);
 if(from&&r32(c+20)){w32(0x1000b010,from);w32(0x1000b020,r32(c+20));(void)ps2MovieIpuFromDmaControl(sx(r32(c+24))|256);}
 while(s32(r32(0x10002010))<0){}
 w32(0x10002000,bits);while(s32(r32(0x10002010))<0){}
 if(address&&qwc){w32(0x1000b410,address);w32(0x1000b430,r32(c+4));w32(0x1000b420,qwc);(void)ps2MovieIpuToDmaControl(sx(r32(c+12))|256);}
}
uint64_t ps2MovieIpuWait(uint64_t mode){
 if(!mode){while(s32(r32(0x10002010))<0){}return 0;}
 return mode==1?r32(0x10002010)>>31:0;
}
void ps2MovieDecoderInputDma(uint64_t decoder){
 uint32_t d=(uint32_t)decoder;
 if(!*at(d+12)){w32(0x552158,d);w32(0x1000b430,r32(d+76)&0x0fffffff);w32(0x1000b420,0);w32(0x1000b400,0x105);*at(d+18)=0;return;}
 if(!*at(d+82)){*at(d+18)=1;return;}
 w32(0x552158,d);*at(d+100)=1;w32(0x1000b410,(r32(d+84)+((uint32_t)*at(d+83)<<13))&0x0fffffff);
 w32(0x1000b420,512);w32(0x1000b400,0x101);*at(d+18)=0;
}
uint64_t ps2MovieIpuReadHeader(void){
 w32(0x10002000,0x40000000);(void)ps2MovieIpuWait(0);uint32_t result=r32(0x10002000);
 (void)ps2MovieIpuWait(0);w32(0x10002000,0x40000008);(void)ps2MovieIpuWait(0);return sx(result);
}
void ps2MovieDecoderStart(uint64_t decoder){
 uint32_t d=(uint32_t)decoder,c=d+104;
 if(!*at(d+14)){
  *at(d+14)=1;uint32_t enable=r32(0x1000f520);w32(0x1000f520,0x10000);w32(0x1000b400,1);w32(0x1000f520,enable);
  w32(0x10002010,0x40000000);(void)ps2MovieIpuWait(0);w32(0x10002000,0);(void)ps2MovieIpuWait(0);
  ps2MovieDecoderInputDma(decoder);w32(0x10002010,0);ps2MovieIpuSaveContext(sx(c));
 }
 uint8_t selected=*at(d+24);uint32_t length=r32(d+28),chunks=(uint32_t)(s32(length)/16);
 uint32_t output=r32(d+32+(uint32_t)selected*4)&0x0fffffff;
 w32(0x552154,d);w32(0x552158,d);w32(d+120,output);w32(d+124,chunks);w32(d+128,256);*at(d+24)=selected^1;*at(d+17)=1;
 ps2MovieIpuRestoreContext(sx(c));
 if(*at(d+101)){w32(0x10002000,0x40000020);(void)ps2MovieIpuWait(0);}else *at(d+101)=1;
 uint32_t header=(uint32_t)ps2MovieIpuReadHeader(),shifted=(header>>8)|(header&0x80000000?0xff000000:0);
 w32(0x10002010,shifted&0x00fb0000);uint32_t table=0x529ce8+(uint32_t)*at(d+20)*2;
 uint32_t command=0x10000000|((uint32_t)*at(table)<<27)|((uint32_t)*at(table+1)<<26)|(header&0x04000000?0x01010000:0x10000);
 w32(0x10002000,command);
}
void ps2MovieDecoderSchedule(uint64_t interrupts_disabled){
 if(r32(0x552154))return;uint32_t restore=interrupts_disabled?0:ps2KernelDisableInterrupts(),node=r32(0x55215c);
 while(node){
  if((uint32_t)*at(node+26)+*at(node+19)>=2||(*at(node+12)==1&&!*at(node+82))){node=r32(node+4);continue;}
  (void)ps2MovieDecoderQueueRemove(sx(node),1);ps2MovieDecoderStart(sx(node));break;
 }
 if(!interrupts_disabled&&restore)ps2KernelEnableInterrupts();
}
void ps2MovieDecoderDestroy(uint64_t decoder){
 uint32_t d=(uint32_t)decoder,restore=ps2KernelDisableInterrupts(),active=0;*at(d+15)=1;
 ps2MovieDecoderListRemove(decoder);(void)ps2MovieDecoderQueueRemove(decoder,1);
 if(sx(r32(0x552154))==decoder){
  w32(0x10002010,0x40000000);active=1;(void)ps2MovieIpuWait(0);uint32_t enable=r32(0x1000f520);
  w32(0x1000f520,0x10000);w32(0x1000b400,1);w32(0x1000b000,0);w32(0x1000f520,enable);w32(0x552154,0);
 }
 if(restore)ps2KernelEnableInterrupts();
 ps2PoolOrMemoryPointerFree(sx(r32(d+76)));ps2PoolOrMemoryPointerFree(sx(r32(d+32)));ps2PoolOrMemoryPointerFree(sx(r32(d+36)));
 ps2MovieDeferPointerFree(sx(r32(d+40)));ps2MovieDeferPointerFree(sx(r32(d+44)));
 uint32_t staging=r32(d+84);if(staging)ps2PoolOrMemoryPointerFree(sx(staging-256));
 uint32_t handle=r32(d+56);if(handle)ps2MemoryHandleDeferFree(sx(handle));
 if(active)ps2MovieDecoderSchedule(0);
}
void ps2MovieClosePollHook(void){
#if UINTPTR_MAX > UINT32_MAX
 nocturneMovieClosePollArrival();
#endif
 /* 002a8078 is JR RA / NOP. Arrival is a host-only external IOP event. */
}
void ps2MovieControlClose(uint64_t control){
 uint32_t c=(uint32_t)control;if(!*at(c))return;uint8_t state=*at(c+1);*at(c+2)=1;
 if(state==5){*at(c+1)=7;(void)ps2FileCommandClose(sx(r32(c+16)));state=*at(c+1);}
 if(state!=6)do{ps2MovieClosePollHook();}while(*at(c+1)!=6);
 uint32_t record=r32(c+28);
 if(!*at(c+3))ps2MemoryHandleFree(r32(record));
 else{ps2MemoryHandleFree(r32(record+64));ps2MemoryHandleFree(r32(record+76));}
 ps2PoolRelease(record);ps2MovieDecoderDestroy(sx(c+36));if(*at(c+32))ps2MovieStopDecoderCommand();*at(c)=0;
}
