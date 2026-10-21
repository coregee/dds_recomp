#include "resource_loader_support.h"
#include "script_construction.h"
#include "file_worker_control.h"
#include "heap_queue.h"
#include <string.h>
static void *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t byte(uint32_t a){return *(uint8_t *)at(a);}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void putHalf(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void putByte(uint32_t a,uint32_t v){*(uint8_t *)at(a)=(uint8_t)v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
enum { MANAGER=0x575618 };
/* 002967e8: compare the original full64 request, clear every matching slot. */
uint64_t ps2ResourceUnlinkActive(uint64_t request)
{
 (void)ps2KernelWaitSema(word(MANAGER));
 for(uint32_t i=0;i<4;i++){uint32_t a=MANAGER+0x24+i*8;if(sx(word(a))==request)put(a,0);}
 uint32_t previous=0,current=word(MANAGER+8);
 while(current){
  if(sx(current)==request){uint32_t next=word(current+4);if(!next)put(MANAGER+12,previous);if(previous)put(previous+4,next);else put(MANAGER+8,next);break;}
  previous=current;current=word(previous+4);
 }
 return sx(ps2KernelSignalSema(word(MANAGER)));
}
/* 002968a8/002968b8: intrusive reusable chain at manager+18, request+4. */
void ps2ResourcePushReusable(uint64_t manager,uint64_t request)
{uint32_t m=(uint32_t)manager,r=(uint32_t)request,v=word(m+24);put(r+4,v);put(m+24,r);}
void ps2ResourceRemoveReusable(uint64_t manager,uint64_t request)
{
 uint32_t link=(uint32_t)manager+24,current=word(link);
 while(sx(current)!=request){link=current+4;current=word(link);}
 put(link,word((uint32_t)request+4));
}
uint64_t fileGetMemHandle(uint64_t request){return sx(word((uint32_t)request+0x20));}
uint64_t fileGetLoadPtr(uint64_t request){return sx(word((uint32_t)request+0x24));}
uint64_t fileGetLoadSize(uint64_t request){return sx(word((uint32_t)request+0x14));}
uint64_t fileCheckEnd(uint64_t request)
{uint32_t r=(uint32_t)request;return (byte(r)!=1||half(r+0x68)!=0)&&byte(r+1)==6;}
uint64_t ps2ResourcePacCheckEnd(uint64_t request)
{uint32_t r=(uint32_t)request;return half(r+0x68)!=0&&byte(r+1)==6;}
/* 00296c88: reserve one of four 64KiB PAC input slots before submitting read. */
uint64_t ps2ResourceQueuePacRead(uint64_t request)
{
 uint32_t r=(uint32_t)request;(void)ps2KernelWaitSema(word(MANAGER));
 if(!byte(MANAGER+7)||byte(r+1)!=3)return sx(ps2KernelSignalSema(word(MANAGER)));
 putByte(r+1,4);uint32_t slot=byte(MANAGER+5);putByte(MANAGER+5,slot==3?0:slot+1);
 putHalf(r+0x6a,slot);putByte(MANAGER+7,byte(MANAGER+7)+255);put(MANAGER+0x24+slot*8,r);
 uint32_t bytes=word(r+0x10);if((int32_t)bytes>65536)bytes=65536;
 (void)ps2KernelSignalSema(word(MANAGER));
 return ps2FileCommandRead(sx(word(r+12)),sx(word(MANAGER+0x1c)+(slot<<16)),sx(bytes));
}
uint64_t ps2ResourceQueueRawRead(uint64_t request)
{
 uint32_t r=(uint32_t)request;(void)ps2KernelWaitSema(word(MANAGER));
 if(byte(r+1)!=3)return sx(ps2KernelSignalSema(word(MANAGER)));
 putByte(r+1,4);(void)ps2KernelSignalSema(word(MANAGER));
 uint32_t bytes=word(r+0x10);if((int32_t)bytes>32768)bytes=32768;
 return ps2FileCommandRead(sx(word(r+12)),sx(word(r+0x28)),sx(bytes));
}
uint64_t ps2ResourceQueueRawWrite(uint64_t request)
{
 uint32_t r=(uint32_t)request;(void)ps2KernelWaitSema(word(MANAGER));
 if(byte(r+1)!=3)return sx(ps2KernelSignalSema(word(MANAGER)));
 putByte(r+1,4);(void)ps2KernelSignalSema(word(MANAGER));
 uint32_t bytes=word(r+0x10);if((int32_t)bytes>32768)bytes=32768;
 return ps2FileCommandWrite(sx(word(r+12)),sx(word(r+0x28)),sx(bytes));
}
/* 00297658: unlink before each real callback, then reacquire and reread head. */
uint64_t ps2ResourceDrainCompleted(void)
{
 for(;;){
  (void)ps2KernelWaitSema(word(MANAGER));uint32_t request=word(MANAGER+0x10);
  if(!request)return sx(ps2KernelSignalSema(word(MANAGER)));
  put(MANAGER+0x10,word(request+0x2c));(void)ps2KernelSignalSema(word(MANAGER));
  uint32_t entry=word(request+0x18);nocturneResourceCompletionCallback(entry,sx(request),sx(word(request+0x1c)));
 }
}
