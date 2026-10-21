/* Complete original file-device paths, thread construction and job queues. */
#include "file_device.h"
#include "file_loader_support.h"
#include "ps2_memory.h"
#include "ps2_sdk_helpers.h"
#include "material_fiveword_pool.h"
#include "heap_queue.h"
#include "texture_construction.h"
#include <string.h>
extern void *nocturneResolveFileDeviceAddress(uint32_t address);
extern uint64_t nocturneFileThreadCreateValue(const void *parameters);
extern uint64_t nocturneFileThreadStartValue(uint64_t id,uint64_t parameters);
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveFileDeviceAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void w8(uint32_t a,uint32_t v){*at(a)=(uint8_t)v;}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
static void prefix(uint32_t destination,uint32_t source,int bytes){
    uint32_t word=r32(source),a=*at(source+4),b=bytes>5?*at(source+5):0;
    w32(destination,word);w8(destination+4,a);
    if(bytes>5)w8(destination+5,b);
    if(bytes>6)w8(destination+6,*at(source+6));
}
uint64_t ps2FileHostRoot(void){return UINT64_C(0x529ac0);}
uint64_t ps2FileNormalizePath(uint64_t path_raw,uint64_t device)
{
    uint32_t path=(uint32_t)path_raw,length=ps2Strlen((const char *)at(path)),destination;
    if(device==0){
        destination=ps2PoolAllocate(s32(length+10));prefix(destination,0x551968,7);
        uint32_t i=0;int32_t c=(int32_t)(int8_t)*at(path);
        while(c){
            if(c==47)c=92;else if((uint32_t)(c-97)<26)c-=32;
            w8(destination+7+i,(uint32_t)c);i++;c=(int32_t)(int8_t)*at(path+i);
        }
        w8(destination+7+i,59);w8(destination+8+i,49);w8(destination+9+i,0);
    }else if(device==1){
        if(*at(path)==47){
            uint32_t root=(uint32_t)ps2FileHostRoot(),root_length=ps2Strlen((const char *)at(root));
            destination=ps2PoolAllocate(s32(length+root_length));
            ps2Memcpy(at(destination),at(root),root_length);
            ps2Memcpy(at(destination+root_length),at(path+1),length);
        }else{
            destination=ps2PoolAllocate(s32(length+7));prefix(destination,0x551970,6);
            ps2Memcpy(at(destination+6),at(path),length);w8(destination+6+length,0);
        }
    }else if(device==2){
        destination=ps2PoolAllocate(s32(length+6));prefix(destination,0x551978,5);
        ps2Memcpy(at(destination+5),at(path),length);w8(destination+5+length,0);
    }else if(device==3){
        destination=ps2PoolAllocate(s32(length+1));ps2Strcpy((char *)at(destination),(const char *)at(path));
    }else return 0;
    return sx(destination);
}
uint64_t ps2FileResolvePath(uint64_t path_raw,uint32_t *output)
{
    uint32_t path=(uint32_t)path_raw,device,skip=0;
    if(!ps2Strchr((const char *)at(path),58))device=*at(0x55195e);
    else if(ps2Memcmp(at(path),at(0x551968),7)==0){
        if(ps2Memcmp(at(path+7),at(0x551980),7)==0)device=3;
        else{device=0;skip=7;}
    }else if(ps2Memcmp(at(path),at(0x551970),6)==0){device=1;skip=6;}
    else if(ps2Memcmp(at(path),at(0x551978),5)==0){device=2;skip=5;}
    else if(ps2Memcmp(at(path),at(0x551988),6)==0){device=3;skip=6;}
    else return UINT64_MAX;
    uint32_t normalized=(uint32_t)ps2FileNormalizePath(sx(path+skip),device);
    memcpy(output,&normalized,4);return device;
}
uint64_t ps2KernelCreateThread(const void *parameters){return nocturneFileThreadCreateValue(parameters);}
uint64_t ps2KernelStartThread(uint64_t id,uint64_t parameters){return nocturneFileThreadStartValue(id,parameters);}
uint64_t ps2ThreadCreateWithStack(uint64_t entry,uint64_t stack,uint64_t bytes,uint64_t priority)
{
    uint8_t parameters[48];ps2Memset(parameters,0,48);
    uint32_t word=(uint32_t)entry;memcpy(parameters+4,&word,4);
    word=(uint32_t)stack;memcpy(parameters+8,&word,4);
    word=(uint32_t)bytes;memcpy(parameters+12,&word,4);
    word=(uint32_t)priority;memcpy(parameters+20,&word,4);
    word=0x554170;memcpy(parameters+16,&word,4);
    return ps2KernelCreateThread(parameters);
}
uint64_t ps2ThreadCreateAllocated(uint64_t entry,uint64_t bytes,uint64_t priority)
{
    uint64_t stack=ps2TextureStagingAllocate(bytes);
    return ps2ThreadCreateWithStack(entry,stack,bytes,priority);
}
void ps2FileDeviceInitialize(uint64_t device)
{
    uint32_t record=0x529b00+(uint32_t)device*24;
    if(s32(r32(record))<0){
        w32(record+4,ps2CreateSemaphore(0,255,0));
        uint64_t entry=device==3?UINT64_C(0x2bed50):UINT64_C(0x2be8c8);
        w32(0x551960,72);
        uint64_t thread=ps2ThreadCreateAllocated(entry,16384,72);
        w32(record,(uint32_t)thread);(void)ps2KernelStartThread(thread,sx(record));
    }
}
void ps2FileJobEnqueue(uint64_t job_raw)
{
    uint32_t job=(uint32_t)job_raw,restore=ps2KernelDisableInterrupts();
    uint32_t record=0x529b00+(uint32_t)*at(job+20)*24;
    if(s32(r32(record))<0)ps2FileDeviceInitialize(*at(job+20));
    uint32_t previous=r32(0x55194c);w32(job+4,previous);
    if(previous)w32(previous,job);else w32(0x551948,job);
    w32(0x55194c,job);
    previous=r32(record+12);w32(job+12,previous);
    if(previous)w32(previous+8,job);else w32(record+8,job);
    w32(record+12,job);w16(0x55195c,r16(0x55195c)+1);
    if(restore)ps2KernelEnableInterrupts();
    if(!previous)(void)ps2KernelSignalSema(r32(record+4));
}
uint64_t ps2FileRequestRead(uint64_t path,uint64_t callback,uint64_t payload)
{
    uint32_t normalized;uint64_t device=ps2FileResolvePath(path,&normalized);
    if(device>>63)return 0;
    uint64_t job=ps2FileJobCreate(sx(normalized),device,1,callback,payload);
    ps2FileJobEnqueue(job);return job;
}
uint64_t ps2FileRequestStream(uint64_t path,uint64_t callback,uint64_t payload,uint64_t bytes)
{
    uint32_t normalized;uint64_t device=ps2FileResolvePath(path,&normalized);
    if(device>>63)return 0;
    uint64_t job=ps2FileJobCreate(sx(normalized),device,2,callback,payload);
    uint32_t fallback=r16(0x551964);
    if(bytes==0)bytes=fallback;
    w32((uint32_t)job+36,(uint32_t)bytes);ps2FileJobEnqueue(job);return job;
}
