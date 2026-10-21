/* Native queue construction, terminal ownership and completion polling. */
#include "resource_request_lifecycle.h"
#include "resource_loader_flow.h"
#include "resource_loader_support.h"
#include "file_loader_support.h"
#include "file_worker_control.h"
#include "material_construction_release.h"
#include "pac_parser.h"
#include "ps2_sdk_helpers.h"
#include "heap_queue.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveRequestLifecycleAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint8_t r8(uint32_t a){uint8_t v;memcpy(&v,at(a),1);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint8_t v){memcpy(at(a),&v,1);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
#endif
void ps2ResourceRequestInitialize(uint64_t request,uint64_t kind,uint64_t path,uint64_t callback,uint64_t parameter){
 ENTER(0x30);uint32_t r=(uint32_t)request;w8(r,(uint8_t)kind);uint64_t name=ps2FilePathClone(path);w32(r+24,(uint32_t)callback);w32(r+8,(uint32_t)name);w32(r+28,(uint32_t)parameter);
 (void)ps2KernelWaitSema(r32(0x575618));uint32_t tail=r32(0x575624);int kick=!tail;
 if(tail)w32(tail+4,r);else w32(0x575620,r);
 w32(0x575624,r);(void)ps2KernelSignalSema(r32(0x575618));LEAVE(0x30);
 /* Original restores its frame before the phase processor tail call. */
 if(kick)ps2ResourceProcessPhase();
}
uint64_t ps2ResourceReadRequestCreate(uint64_t path,uint64_t high,uint64_t callback,uint64_t parameter){
 ENTER(0x30);uint32_t r=ps2PoolAllocateZeroed(48);w8(r+3,(uint8_t)high);ps2ResourceRequestInitialize(sx(r),0,path,callback,parameter);LEAVE(0x30);return sx(r);
}
uint64_t ps2ResourcePacRequestCreate(uint64_t path,uint64_t flag,uint64_t headerCallback,uint64_t callback,uint64_t parameter){
 ENTER(0x40);uint32_t r=ps2PoolAllocateZeroed(112);ps2PacInitialize(sx(r+48),headerCallback);if(flag)ps2PacSetFlag2(sx(r+48));ps2ResourceRequestInitialize(sx(r),1,path,callback,parameter);LEAVE(0x40);return sx(r);
}
uint64_t ps2ResourcePacRequestRelease(uint64_t request){
 ENTER(0x10);uint32_t r=(uint32_t)request;if(r8(r+1)!=6){LEAVE(0x10);return 1;}
 uint32_t job=r32(r+12);if(job)ps2FileJobReleaseIfTerminal(sx(job));ps2PacReleaseRecords(sx(r+48));ps2PoolRelease(r32(r+8));ps2PoolRelease(r);LEAVE(0x10);return 0;
}
uint64_t ps2ResourcePacRequestFree(uint64_t request){return ps2ResourcePacRequestRelease(request);}
uint64_t ps2ResourceRequestRelease(uint64_t request){
 ENTER(0x10);uint32_t r=(uint32_t)request;
 if(r8(r)==1){LEAVE(0x10);return ps2ResourcePacRequestRelease(request);}
 if(r8(r+1)!=6){LEAVE(0x10);return 1;}
 uint32_t job=r32(r+12);if(job)ps2FileJobReleaseIfTerminal(sx(job));ps2PoolRelease(r32(r+8));ps2PoolRelease(r);LEAVE(0x10);return 0;
}
uint64_t ps2ResourceWait(uint64_t request){
 ENTER(0x10);uint64_t result;while(!(result=fileCheckEnd(request))){ps2FileWorkerDefaultPriority();(void)ps2ResourcePump();}LEAVE(0x10);return result;
}
uint64_t ps2ResourcePacWait(uint64_t request){return ps2ResourceWait(request);}
void ps2ModelRemovePending(uint64_t major,uint64_t minor){
 uint32_t link=0x32c478+((uint32_t)major<<2),p=r32(link);while(p){if(sx(r32(p+4))==minor){w32(link,r32(p));ps2PoolRelease(p);return;}link=p;p=r32(p);}
}
uint64_t ps2ModelBuildPrefixedPath(uint64_t destination,uint64_t filename){
 uint8_t prefix[8];memcpy(prefix,at(0x54f628),8);memcpy(at((uint32_t)destination),prefix,8);ps2Strcat(at((uint32_t)destination),at((uint32_t)filename));return destination;
}
