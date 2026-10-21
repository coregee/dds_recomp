/* Complete native movie streaming state callbacks and ring consumers. */
#include "movie_stream.h"
#include "movie_archive.h"
#include "file_worker_control.h"
#include "file_loader_support.h"
#include "material_fiveword_pool.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "heap_queue.h"
#include "ps2_memory.h"
#include "compiler_numeric.h"
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
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
static void copy(uint32_t output,uint32_t input,uint32_t bytes){ps2Memcpy(at(output),at(input),bytes);}
void ps2MovieOrdinaryReadPump(uint64_t control){
 uint32_t c=(uint32_t)control,remaining=r32(c+24),record=r32(c+28);if(!remaining)return;
 if(s32(0x20000-r32(record+16))<16384){*at(c+1)=5;return;}
 *at(c+1)=4;uint32_t bytes=s32(remaining)<16385?remaining:16384;
 uint32_t destination=r32(record+12),next=destination+bytes,start=r32(record+4);
 if(next>=start+0x20000)next=start;w32(record+12,next);
 (void)ps2FileCommandRead(sx(r32(c+16)),sx(destination),sx(bytes));
}
uint64_t ps2MovieOrdinaryFileCallback(uint64_t job,uint64_t event,uint64_t buffer,uint64_t result,uint64_t control){
 (void)buffer;uint32_t c=(uint32_t)control,record=r32(c+28),bytes=(uint32_t)result;w32(c+16,(uint32_t)job);
 uint8_t state=*at(c+1);
 if(*at(c+2)&&(uint8_t)(state-6)>1){*at(c+1)=7;(void)ps2FileCommandClose(job);return 0;}
 switch(state){
 case 0:if(event==2){*at(c+1)=1;(void)ps2FileCommandSize(job);}break;
 case 1:if(event==4){w32(c+24,bytes);w32(c+20,bytes);ps2MovieOrdinaryReadPump(control);}break;
 case 4:
  if(event!=5)break;
  {uint32_t restore=ps2KernelDisableInterrupts();w32(record+16,r32(record+16)+bytes);w32(c+24,r32(c+24)-bytes);if(restore)ps2KernelEnableInterrupts();}
  if(r32(c+24))ps2MovieOrdinaryReadPump(control);else{*at(c+1)=7;(void)ps2FileCommandClose(job);}break;
 case 7:if(event==7){w32(c+16,0);*at(c+1)=6;(void)ps2FileJobReleaseIfTerminal(job);}break;
 default:break;
 }
 return 0;
}
uint64_t ps2MovieOrdinaryConsume(uint64_t decoder,uint64_t control,uint64_t event,uint64_t buffer,uint64_t bytes){
 (void)decoder;uint32_t c=(uint32_t)control,record=r32(c+28),destination=(uint32_t)buffer,n=(uint32_t)bytes;
 if(event==1){
  if(*at(c+2))return 0;uint32_t input=r32(record+8),start=r32(record+4),over=input-start+n-0x20000;
  if(s32(over)<0){copy(destination,input,n);w32(record+8,input+n);}
  else{copy(destination,input,n-over);if(s32(over)>0)copy(destination+n-over,start,over);w32(record+8,start+over);}
  w32(record+16,r32(record+16)-n);return sx(r32(c+24));
 }
 if(event==0){if(*at(c+2)){*at(destination)=1;return 0;}if(!r32(c+24))*at(destination)=1;return sx(r32(record+16));}
 if(event==2&&!*at(c+2)&&*at(c+1)==5)ps2MovieOrdinaryReadPump(control);
 return 0;
}
void ps2MovieIpsReadPump(uint64_t control){
 uint32_t c=(uint32_t)control,remaining=r32(c+24),record=r32(c+28);if(!remaining)return;
 if(s32(0x10000-r32(record+92))<16384||s32(r32(record+108)-r32(record+104)+0x10000)<16384){*at(c+1)=5;return;}
 *at(c+1)=4;uint32_t bytes=s32(remaining)<16385?remaining:16384;
 (void)ps2FileCommandRead(sx(r32(c+16)),sx(r32(record+80)),sx(bytes));
}
uint64_t ps2MovieIpsCopy(uint64_t output,uint64_t input,uint64_t bytes){copy((uint32_t)output,(uint32_t)input,(uint32_t)bytes);return output;}
uint64_t ps2MovieIpsConsume(uint64_t decoder,uint64_t control,uint64_t event,uint64_t buffer,uint64_t bytes){
 (void)decoder;uint32_t c=(uint32_t)control,record=r32(c+28),destination=(uint32_t)buffer,n=(uint32_t)bytes;
 if(event==1){
  if(*at(c+2))return 0;uint32_t offset=r32(record+88),start=r32(record+84),next=offset+n,over=next-0x10000;
  if(s32(over)<0){(void)ps2MovieIpsCopy(buffer,sx(start+offset),bytes);w32(record+88,next);}
  else{(void)ps2MovieIpsCopy(buffer,sx(start+offset),sx(n-over));if(s32(over)>0)(void)ps2MovieIpsCopy(sx(destination+n-over),sx(start),sx(over));w32(record+88,over);}
  w32(record+92,r32(record+92)-n);return sx(r32(c+24));
 }
 if(event==0){if(*at(c+2)){*at(destination)=1;return 0;}if(!r32(c+24))*at(destination)=1;return sx(r32(record+92));}
 if(event==2&&!*at(c+2)&&*at(c+1)==5)ps2MovieIpsReadPump(control);
 return 0;
}
uint64_t ps2MovieIpsFileCallback(uint64_t job,uint64_t event,uint64_t buffer,uint64_t result,uint64_t control){
 uint32_t c=(uint32_t)control,record=r32(c+28),delivered=(uint32_t)result;w32(c+16,(uint32_t)job);uint8_t state=*at(c+1);
 if(*at(c+2)&&(uint8_t)(state-6)>1){*at(c+1)=7;(void)ps2FileCommandClose(job);return 0;}
 switch(state){
 case 0:if(event==2){*at(c+1)=1;(void)ps2FileCommandSize(job);}break;
 case 1:if(event==4){w32(c+24,delivered);*at(c+1)=2;w32(c+20,delivered);(void)ps2FileCommandRead(job,sx(record),64);}break;
 case 2:
  if(event==5){
   uint32_t size=r32(record+24)-64,handle=ps2MemoryHandleAllocate(s32(size));w32(record+64,handle);
   w32(record+68,ps2MemoryHandleAcquirePointer(handle));*at(c+1)=3;
   (void)ps2FileCommandRead(job,sx(r32(record+68)),sx(size));w32(c+24,r32(c+24)-r32(record+24));
  }break;
 case 3:if(event==5)ps2MovieIpsReadPump(control);break;
 case 4:
  if(event==5){
   uint32_t block=r32(record+28);if(!block)nocturneCompilerArithmeticTrap(7);
   uint32_t count=(uint32_t)((int64_t)s32(delivered)/(int64_t)s32(block)),input=(uint32_t)buffer;
   do{
    uint32_t packet=r32(record+72);int32_t group=s32(packet)/8;uint32_t shift=(packet-(uint32_t)group*8)&31;
    if(*at(r32(record+68)+(uint32_t)group)&(UINT32_C(1)<<shift)){
     (void)ps2KernelWaitSema(r32(0x551b48));uint32_t used=r32(record+104),offset=r32(record+100)+used;
     if(s32(offset)>65535)offset-=65536;uint32_t over=offset+block-65536,start=r32(record+96);
     if(s32(over)>0){copy(start+offset,input,block-over);input+=block;copy(start,input-over,over);}
     else{copy(start+offset,input,block);input+=block;}
     uint32_t next=used+block;
     if(s32(next)>65536){uint32_t base=r32(record+100)+next-65536;w32(record+100,base);if(s32(base)>65535)w32(record+100,base-65536);w32(record+104,65536);}
     else w32(record+104,next);
     (void)ps2KernelSignalSema(r32(0x551b48));
    }else{
     uint32_t restore=ps2KernelDisableInterrupts(),offset=r32(record+88)+r32(record+92);if(s32(offset)>65535)offset-=65536;
     copy(r32(record+84)+offset,input,block);w32(record+92,r32(record+92)+block);if(restore)ps2KernelEnableInterrupts();input+=block;
    }
    count--;w32(record+72,r32(record+72)+1);
   }while(count);
   w32(c+24,r32(c+24)-delivered);
   if(r32(c+24))ps2MovieIpsReadPump(control);else{*at(c+1)=7;(void)ps2FileCommandClose(job);}
  }break;
 case 7:if(event==7){w32(c+16,0);*at(c+1)=6;(void)ps2FileJobReleaseIfTerminal(job);}break;
 default:break;
 }
 return 0;
}
