/* Actual job completion, all command requests and four-worker priority control. */
#include "file_worker_control.h"
#include "file_device.h"
#include "file_loader_support.h"
#include "material_fiveword_pool.h"
#include "heap_queue.h"
#include <string.h>
extern void *nocturneResolveFileDeviceAddress(uint32_t address);
extern uint64_t nocturneFilePriorityValue(uint64_t id,uint64_t priority);
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveFileDeviceAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void w8(uint32_t a,uint32_t v){*at(a)=(uint8_t)v;}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
static int32_t s16(uint32_t v){return (int32_t)(v&32767)-(int32_t)(v&32768);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
uint64_t ps2FileJobComplete(uint64_t job_raw)
{
    uint32_t job=(uint32_t)job_raw,restore=ps2KernelDisableInterrupts();
    uint32_t previous=r32(job+4),next=r32(job);
    if(previous)w32(previous,next);else w32(0x551948,next);
    if(next)w32(next+4,previous);else w32(0x55194c,previous);
    uint32_t record=0x529b00+(uint32_t)*at(job+20)*24;
    previous=r32(job+12);next=r32(job+8);
    if(previous)w32(previous+8,next);else w32(record+8,next);
    if(next)w32(next+12,previous);else w32(record+12,previous);
    previous=r32(0x551958);w32(job+4,previous);
    if(previous)w32(previous,job);else w32(0x551954,job);
    uint32_t count=r16(0x551950),active=r16(0x55195c);count++;
    w32(0x551958,job);active--;w32(job,0);w16(0x551950,count);w16(0x55195c,active);
    if(restore){ps2KernelEnableInterrupts();count=r16(0x551950);}
    if(s16(count)>=9)ps2FileJobRelease(sx(r32(0x551954)));
    if(!r32(record+8))return 0;
    return sx(ps2KernelSignalSema(r32(record+4)));
}
static int ready(uint32_t job){return (int8_t)*at(job+22)==7;}
static void signal(uint32_t job){uint32_t record=0x529b00+(uint32_t)*at(job+20)*24;(void)ps2KernelSignalSema(r32(record+4));}
uint64_t ps2FileCommandSeek(uint64_t job_raw,uint64_t offset,uint64_t origin)
{
    uint32_t job=(uint32_t)job_raw;if(!ready(job))return UINT64_MAX;
    w32(job+24,(uint32_t)offset);w32(job+36,(uint32_t)origin);w8(job+21,3);signal(job);return 0;
}
uint64_t ps2FileCommandSize(uint64_t job_raw)
{
    uint32_t job=(uint32_t)job_raw;if(!ready(job))return UINT64_MAX;
    w8(job+21,4);signal(job);return 0;
}
uint64_t ps2FileCommandRead(uint64_t job_raw,uint64_t buffer,uint64_t bytes)
{
    uint32_t job=(uint32_t)job_raw;if(!ready(job))return UINT64_MAX;
    w32(job+28,(uint32_t)bytes);w8(job+21,5);w32(job+32,(uint32_t)buffer);signal(job);return 0;
}
uint64_t ps2FileCommandWrite(uint64_t job_raw,uint64_t buffer,uint64_t bytes)
{
    uint32_t job=(uint32_t)job_raw;if(!ready(job))return UINT64_MAX;
    w32(job+28,(uint32_t)bytes);w8(job+21,6);w32(job+32,(uint32_t)buffer);signal(job);return 0;
}
uint64_t ps2FileCommandRetry(uint64_t job_raw)
{
    uint32_t job=(uint32_t)job_raw;if((int8_t)*at(job+22)!=9)return UINT64_MAX;
    w32(job+44,0);w8(job+22,7);return 0;
}
uint64_t ps2FileCommandClose(uint64_t job_raw)
{
    uint32_t job=(uint32_t)job_raw;if(!ready(job))return UINT64_MAX;
    w8(job+21,7);signal(job);return 0;
}
uint64_t ps2FileRequestLoad(uint64_t path,uint64_t buffer,uint64_t bytes,uint64_t callback,uint64_t payload)
{
    uint32_t normalized;uint64_t device=ps2FileResolvePath(path,&normalized);if(device>>63)return 0;
    uint64_t job=ps2FileJobCreate(sx(normalized),device,8,callback,payload);
    w32((uint32_t)job+28,(uint32_t)bytes);w32((uint32_t)job+32,(uint32_t)buffer);w32((uint32_t)job+24,0);
    ps2FileJobEnqueue(job);return job;
}
uint64_t ps2FileRequestStore(uint64_t path,uint64_t buffer,uint64_t bytes,uint64_t callback,uint64_t payload,uint64_t stream_bytes)
{
    uint32_t normalized;uint64_t device=ps2FileResolvePath(path,&normalized);if(device>>63)return 0;
    uint64_t job=ps2FileJobCreate(sx(normalized),device,9,callback,payload);
    uint32_t fallback=r16(0x551964);w32((uint32_t)job+28,(uint32_t)bytes);
    if(stream_bytes==0)stream_bytes=fallback;
    w32((uint32_t)job+32,(uint32_t)buffer);w32((uint32_t)job+36,(uint32_t)stream_bytes);w32((uint32_t)job+24,0);
    ps2FileJobEnqueue(job);return job;
}
uint64_t ps2KernelChangeThreadPriority(uint64_t id,uint64_t priority){return nocturneFilePriorityValue(id,priority);}
void ps2FileWorkerPriority(uint64_t priority)
{
    if(sx(r32(0x551960))==priority)return;
    w32(0x551960,(uint32_t)priority);
    for(uint32_t k=0;k<4;k++){
        uint32_t id=r32(0x529b00+k*24);
        if(s32(id)>=0)(void)ps2KernelChangeThreadPriority(sx(id),priority);
    }
}
void ps2FileWorkerMoviePriority(void){w8(0x55195f,3);ps2FileWorkerPriority(120);}
void ps2FileWorkerDefaultPriority(void){ps2FileWorkerPriority(72);}
void ps2FileWorkerPriorityTick(void)
{
    uint32_t count=*at(0x55195f);if(!count)return;
    count=(count+255)&255;w8(0x55195f,count);
    if(!count)ps2FileWorkerDefaultPriority();
}
