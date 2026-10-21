#include <stdint.h>
#include <string.h>
#include "memory_handle_unlink.h"
extern void *nocturneResolveMemoryHandleAddress(uint32_t address);
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMemoryHandleAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address){uint32_t word;memcpy(&word,at(address),4);return word;}
static void w32(uint32_t address,uint32_t word){memcpy(at(address),&word,4);}
/* Original002a9540: capture both links before either ordered store. */
uint32_t ps2MemoryHandleUnlinkNext(uint32_t handle)
{
    uint32_t removed=r32(handle+4),next=r32(removed+4);
    w32(next,handle);
    w32(handle+4,next);
    return removed;
}
