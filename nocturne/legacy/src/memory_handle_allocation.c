/* Original PS2 bodies; independently encoded and compared with original instructions. */
#include <stdint.h>
#include <string.h>
#include "memory_handle_allocation.h"
#include "memory_handle_unlink.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "ps2_memory.h"
extern void *nocturneResolveMemoryHandleAddress(uint32_t address);
extern void nocturneCallMemoryPressure(uint32_t entry,int32_t rounded_size);
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMemoryHandleAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address){uint32_t word;memcpy(&word,at(address),4);return word;}
static uint32_t r16(uint32_t address){uint16_t word;memcpy(&word,at(address),2);return word;}
static void w32(uint32_t address,uint32_t word){memcpy(at(address),&word,4);}
static void w16(uint32_t address,uint32_t word){uint16_t half=(uint16_t)word;memcpy(at(address),&half,2);}
static int32_t signed_word(uint32_t word){return (int32_t)((int64_t)word-((word&0x80000000)?INT64_C(4294967296):0));}
static void pressure(uint32_t entry,uint32_t size){
#if UINTPTR_MAX > UINT32_MAX
    nocturneCallMemoryPressure(entry,signed_word(size));
#else
    ((void (*)(int32_t))(uintptr_t)entry)(signed_word(size));
#endif
}

uint32_t ps2MemoryHandleAllocate(int32_t size)
{
    uint32_t rounded=((uint32_t)size+127)&0xffffff80;
    uint32_t restore=ps2KernelDisableInterrupts(),handle=r32(0x577f1c);
    for(;;){
        uint32_t state=r16(handle+12);
        if(state==0){
            uint32_t next=r32(handle+4),data=r32(handle+8),gap=r32(next+8)-data;
            if(signed_word(gap)<signed_word(rounded)){handle=next;continue;}
            if(signed_word(rounded)<signed_word(gap)){
                uint32_t split=ps2PoolAllocate(16),start=r32(handle+8);
                w32(split,handle);start+=rounded;w16(split+12,0);
                uint32_t after=r32(handle+4);w32(split+8,start);w32(split+4,after);w16(split+14,0);
                uint32_t live_after=r32(handle+4);w32(live_after,split);w32(handle+4,split);
            }
            w16(handle+12,1);if(restore)ps2KernelEnableInterrupts();return handle;
        }
        if(state==2){
            if(restore)ps2KernelEnableInterrupts();
            uint32_t callback=r32(0x551830);if(callback)pressure(callback,rounded);
        }
        handle=r32(handle+4);
    }
}

void ps2MemoryHandleFree(uint32_t handle)
{
    if(!handle)return;
    uint32_t restore=ps2KernelDisableInterrupts(),next=r32(handle+4);
    if(r16(next+12)==0){ps2MemoryHandleUnlinkNext(handle);ps2PoolRelease(next);}
    uint32_t previous=r32(handle);
    if(r16(previous+12)==0){ps2MemoryHandleUnlinkNext(previous);ps2PoolRelease(handle);}
    else{w16(handle+14,0);w16(handle+12,0);}
    if(restore)ps2KernelEnableInterrupts();
}

void ps2MemoryHandleReallocate(uint32_t handle,int32_t size)
{
    uint32_t restore=ps2KernelDisableInterrupts(),next=r32(handle+4),data=r32(handle+8);
    uint32_t rounded=((uint32_t)size+127)&0xffffff80,next_data=r32(next+8),old_size=next_data-data;
    if(rounded==old_size){if(restore)ps2KernelEnableInterrupts();return;}
    if(signed_word(old_size)<signed_word(rounded)){
        uint32_t following=r32(next+4),state=r16(next+12),following_data=r32(following+8);
        uint32_t combined=following_data-next_data+old_size;
        if(state==0&&signed_word(combined)>=signed_word(rounded)){
            if(combined==rounded){w32(following,handle);uint32_t live_next=r32(next+4);w32(handle+4,live_next);ps2PoolRelease(next);}
            else w32(next+8,data+rounded);
        }else{
            uint32_t replacement=ps2MemoryHandleAllocate(signed_word(rounded));
            uint32_t source=r32(handle+8),destination=r32(replacement+8);
            ps2Memcpy(at(destination),at(source),old_size);
            uint32_t old_previous=r32(handle),new_previous=r32(replacement),new_data=r32(replacement+8);
            w32(handle,new_previous);uint32_t old_data=r32(handle+8),new_next=r32(replacement+4);
            w32(handle+8,new_data);w32(handle+4,new_next);w32(replacement,old_previous);w32(replacement+4,next);w32(replacement+8,old_data);
            uint32_t previous=r32(handle);w32(previous+4,handle);uint32_t after=r32(handle+4);w32(after,handle);
            previous=r32(replacement);w32(previous+4,replacement);after=r32(replacement+4);w32(after,replacement);
            ps2MemoryHandleFree(replacement);
        }
    }else{
        uint32_t state=r16(next+12);
        if(state==0)w32(next+8,data+rounded);
        else{
            uint32_t split=ps2PoolAllocate(16),start=r32(handle+8);
            w32(split,handle);start+=rounded;w32(split+4,next);w32(split+8,start);w32(next,split);w16(split+12,0);w32(handle+4,split);w16(split+14,0);
        }
    }
    if(restore)ps2KernelEnableInterrupts();
}
