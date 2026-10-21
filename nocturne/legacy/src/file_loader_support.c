/* Complete original PS2 bodies. Raw EE words and instruction store order retained. */
#include "file_loader_support.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_unlink.h"
#include "ps2_memory.h"
#include <string.h>
extern void *nocturneResolveFileLoaderAddress(uint32_t address);
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveFileLoaderAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address){uint32_t v;memcpy(&v,at(address),4);return v;}
static uint32_t r16(uint32_t address){uint16_t v;memcpy(&v,at(address),2);return v;}
static void w32(uint32_t address,uint32_t v){memcpy(at(address),&v,4);}
static void w16(uint32_t address,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(address),&h,2);}
static void w8(uint32_t address,uint32_t v){*at(address)=(uint8_t)v;}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}

uint64_t ps2MemoryHandleTryAllocate(uint64_t size)
{
    uint32_t rounded=((uint32_t)size+127)&0xffffff80;
    uint32_t restore=ps2KernelDisableInterrupts(),handle=r32(0x577f1c);
    for(;;){
        uint32_t state=r16(handle+12);
        if(state==0){
            uint32_t next=r32(handle+4),gap=r32(next+8)-r32(handle+8);
            if(s32(gap)<s32(rounded)){handle=next;continue;}
            if(s32(rounded)<s32(gap)){
                uint32_t split=ps2PoolAllocate(16),start=r32(handle+8);
                w32(split,handle);start+=rounded;w16(split+12,0);
                uint32_t after=r32(handle+4);w32(split+8,start);w32(split+4,after);w16(split+14,0);
                uint32_t live_after=r32(handle+4);w32(live_after,split);w32(handle+4,split);
            }
            w16(handle+12,1);if(restore)ps2KernelEnableInterrupts();return sx(handle);
        }
        if(state==2){if(restore)ps2KernelEnableInterrupts();return 0;}
        handle=r32(handle+4);
    }
}

uint64_t ps2FileJobCreate(uint64_t path,uint64_t device,uint64_t mode,uint64_t callback,uint64_t payload)
{
    uint32_t job=ps2PoolAllocateZeroed(64);
    w32(job+60,(uint32_t)payload);w32(job+16,(uint32_t)path);
    w8(job+20,(uint32_t)device);w8(job+21,(uint32_t)mode);
    w32(job+56,(uint32_t)callback);w32(job+40,UINT32_MAX);w8(job+22,0);
    return sx(job);
}

void ps2FileJobRelease(uint64_t job_raw)
{
    uint32_t restore=ps2KernelDisableInterrupts(),job=(uint32_t)job_raw;
    uint32_t previous=r32(job+4),next=r32(job);
    if(previous)w32(previous,next);else w32(0x551954,next);
    if(next)w32(next+4,previous);else w32(0x551958,previous);
    w16(0x551950,r16(0x551950)-1);
    if(restore)ps2KernelEnableInterrupts();
    ps2PoolRelease(r32(job+16));ps2PoolRelease(job);
}

uint64_t ps2FileJobReleaseIfTerminal(uint64_t job_raw)
{
    uint32_t job=(uint32_t)job_raw;int state=(int)(int8_t)*at(job+22);
    if(state>=7&&state<9){ps2FileJobRelease(job_raw);return 0;}
    return UINT64_MAX;
}

uint64_t ps2FilePathClone(uint64_t path_raw)
{
    if(path_raw==0)return 0;
    uint32_t length=ps2Strlen((const char *)at((uint32_t)path_raw));
    uint32_t copy=ps2PoolAllocate(length+1);
    ps2Memcpy(at(copy),at((uint32_t)path_raw),length);w8(copy+length,0);
    return sx(copy);
}
