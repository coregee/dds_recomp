#include "resource_loader_flow.h"
#include "resource_loader_support.h"
#include "script_construction.h"
#include "file_device.h"
#include "file_worker_control.h"
#include "file_loader_support.h"
#include "pac_compression.h"
#include "pac_parser.h"
#include "material_lists.h"
#include "diagnostic_transport.h"
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
enum {MANAGER=0x575618,DEBUG_TAG=0x551648};
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
#endif
static void wait(void){(void)ps2KernelWaitSema(word(MANAGER));}
static void signal(void){(void)ps2KernelSignalSema(word(MANAGER));}
/* 00297460: callers discard V0. Preserve lock release before submission,
 * including the nested locked allocation/read path and the retry underflow. */
void ps2ResourceProcessPhase(void)
{
 ENTER(0x20);wait();uint32_t r=word(MANAGER+8),locked=1;
 if(r){uint32_t type=byte(r),phase=byte(r+1);
  if(type==0){
   if(phase==0){putByte(r+1,1);signal();locked=0;put(r+12,(uint32_t)ps2FileRequestRead(sx(word(r+8)),0x296fd8,sx(r)));}
   else if(phase==7){
    uint64_t handle=ps2MemoryHandleTryAllocate(sx(word(r+0x14)));put(r+0x20,(uint32_t)handle);
    if(!handle){(void)ps2DiagnosticPrintf(0x5468e8,sx(word(word(r+12)+0x10)));putByte(r+2,byte(r+2)+255);}
    else{uint32_t p=ps2MemoryHandleAcquirePointer((uint32_t)handle);put(r+0x24,p);putByte(r+1,3);put(r+0x28,p);(void)ps2ResourceQueueRawRead(sx(r));}
   }
  }else if(type==1){
   if(phase==0){putByte(r+1,1);signal();locked=0;put(r+12,(uint32_t)ps2FileRequestRead(sx(word(r+8)),0x296d90,sx(r)));}
   else if(phase==3){signal();locked=0;(void)ps2ResourceQueuePacRead(sx(r));}
  }else if(type==2&&phase==0){putByte(r+1,1);signal();locked=0;put(r+12,(uint32_t)ps2FileRequestStream(sx(word(r+8)),0x2972a0,sx(r),0x180));}
 }
 if(locked)signal();LEAVE(0x20);
}
static void phaseWithTag(uint32_t tag)
{uint32_t old=word(DEBUG_TAG);put(DEBUG_TAG,tag);ps2ResourceProcessPhase();put(DEBUG_TAG,old);}
static void append(uint32_t link,uint32_t offset,uint32_t request)
{uint32_t node=word(link);while(node){link=node+offset;node=word(link);}put(link,request);}
static void popActive(uint32_t request)
{uint32_t next=word(request+4);put(MANAGER+8,next);if(!next)put(MANAGER+12,0);}
/* 00296d90: PAC completion pops the head unconditionally. A decoded request
 * still increments pending; its remaining count and slot length stay intact. */
uint64_t ps2ResourcePacFileEvent(uint64_t job,uint64_t event,uint64_t unused,uint64_t processed,uint64_t request)
{
 ENTER(0x30);uint32_t r=(uint32_t)request;(void)unused;
 if(event==2){putByte(r+1,2);put(r+12,(uint32_t)job);(void)ps2FileCommandSize(job);}
 else if(event==4){put(r+0x14,(uint32_t)processed);putByte(r+1,3);put(r+0x10,(uint32_t)processed);(void)ps2ResourceQueuePacRead(request);}
 else if(event==5){
  wait();if(half(r+0x68))putByte(r+1,5);
  else{put(MANAGER+0x20+half(r+0x6a)*8,(uint32_t)processed);uint32_t left=word(r+0x10)-(uint32_t)processed;put(r+0x10,left);if(!left){putByte(r+1,5);popActive(r);}else putByte(r+1,3);}
  putByte(MANAGER+6,byte(MANAGER+6)+1);
  if(byte(r+1)==5){ps2ResourcePushReusable(MANAGER,request);signal();(void)ps2FileCommandClose(job);}else signal();
  phaseWithTag(1);
 }else if(event==7){wait();ps2ResourceRemoveReusable(MANAGER,request);signal();(void)ps2FileJobReleaseIfTerminal(job);put(r+12,0);putByte(r+1,6);}
 LEAVE(0x30);return 0;
}
/* 00296fd8: allocation failure enters phase7 with retry10. Completion only
 * pops the active head when its sign-extended word equals the full argument. */
uint64_t ps2ResourceReadFileEvent(uint64_t job,uint64_t event,uint64_t unused,uint64_t processed,uint64_t request)
{
 ENTER(0x30);uint32_t r=(uint32_t)request;(void)unused;
 if(event==2){putByte(r+1,2);put(r+12,(uint32_t)job);(void)ps2FileCommandSize(job);}
 else if(event==4){
  put(r+0x10,(uint32_t)processed);put(r+0x14,(uint32_t)processed);uint64_t handle;
  if(!byte(r+3))handle=ps2MemoryHandleTryAllocate(processed);else handle=ps2MemoryHandleAllocateHigh(processed);
  put(r+0x20,(uint32_t)handle);
  if(!handle&&!byte(r+3)){putByte(r+1,7);putByte(r+2,10);}
  else{uint32_t p=ps2MemoryHandleAcquirePointer((uint32_t)handle);put(r+0x24,p);putByte(r+1,3);put(r+0x28,p);(void)ps2ResourceQueueRawRead(request);}
 }else if(event==5){
  wait();uint32_t left=word(r+0x10)-(uint32_t)processed;put(r+0x10,left);
  if(!left){putByte(r+1,5);if(sx(word(MANAGER+8))==request)popActive(r);}else{putByte(r+1,3);put(r+0x28,word(r+0x28)+(uint32_t)processed);}
  if(byte(r+1)==5){ps2ResourcePushReusable(MANAGER,request);signal();(void)ps2FileCommandClose(job);phaseWithTag(2);}else{signal();(void)ps2ResourceQueueRawRead(request);}
 }else if(event==7){
  (void)ps2FileJobReleaseIfTerminal(job);put(r+12,0);putByte(r+1,6);wait();ps2ResourceRemoveReusable(MANAGER,request);
  if(word(r+0x18))append(MANAGER+0x10,0x2c,r);signal();
 }
 LEAVE(0x30);return 0;
}
/* 002972a0: event2 does not store job. Writes advance the pointer even on the
 * final chunk. Job release precedes acquiring the reusable/completion lock. */
uint64_t ps2ResourceWriteFileEvent(uint64_t job,uint64_t event,uint64_t unused,uint64_t processed,uint64_t request)
{
 ENTER(0x30);uint32_t r=(uint32_t)request;(void)unused;
 if(event==2){putByte(r+1,3);(void)ps2ResourceQueueRawWrite(request);}
 else if(event==6){
  wait();put(r+0x28,word(r+0x28)+(uint32_t)processed);uint32_t left=word(r+0x10)-(uint32_t)processed;put(r+0x10,left);
  if(!left){putByte(r+1,5);if(sx(word(MANAGER+8))==request)popActive(r);}else putByte(r+1,3);
  if(byte(r+1)==5){ps2ResourcePushReusable(MANAGER,request);signal();(void)ps2FileCommandClose(job);phaseWithTag(3);}else{signal();(void)ps2ResourceQueueRawWrite(request);}
 }else if(event==7){
  (void)ps2FileJobReleaseIfTerminal(job);put(r+12,0);putByte(r+1,6);wait();ps2ResourceRemoveReusable(MANAGER,request);
  if(word(r+0x18))append(MANAGER+0x10,0x2c,r);signal();
 }
 LEAVE(0x30);return 0;
}
/* 002976c0: original dereferences the slot before its null check and spins on
 * a non-PAC pending slot. Keep those unchecked preconditions. */
uint64_t ps2ResourcePump(void)
{
 ENTER(0x50);(void)ps2ResourceDrainCompleted();
 while(byte(MANAGER+6)){
  uint32_t index=byte(MANAGER+4),r=word(MANAGER+0x24+index*8);
  if(byte(r)!=1)continue;
  if(r&&ps2PacDecodeChunk(sx(r+0x30),sx(word(MANAGER+0x1c)+(index<<16)),sx(word(MANAGER+0x20+index*8)))==UINT64_MAX){
   (void)ps2ResourceUnlinkActive(sx(r));putHalf(r+0x68,1);if(word(r+0x18))append(MANAGER+0x14,0x6c,r);
  }
  wait();putByte(MANAGER+4,index==3?0:index+1);putByte(MANAGER+7,byte(MANAGER+7)+1);putByte(MANAGER+6,byte(MANAGER+6)+255);signal();
 }
 ps2ResourceProcessPhase();uint32_t link=MANAGER+0x14,r=word(link);
 while(r){if(byte(r+1)==6){put(link,word(r+0x6c));nocturneResourcePacCompletionCallback(word(r+0x18),sx(r),sx(word(r+0x1c)));}else link=r+0x6c;r=word(link);}
 uint64_t result=word(MANAGER+8)!=0;LEAVE(0x50);return result;
}
