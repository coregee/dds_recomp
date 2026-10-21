#ifndef NOCTURNE_MEMORY_HANDLE_ALLOCATION_H
#define NOCTURNE_MEMORY_HANDLE_ALLOCATION_H
#include <stdint.h>
/* Retain original raw32 descriptors and load/store order. */
uint32_t ps2MemoryHandleAllocate(int32_t size);
void ps2MemoryHandleReallocate(uint32_t handle,int32_t size);
void ps2MemoryHandleFree(uint32_t handle);
#endif
