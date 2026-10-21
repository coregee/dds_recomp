#ifndef NOCTURNE_HEAP_QUEUE_H
#define NOCTURNE_HEAP_QUEUE_H
#include <stdint.h>
/* Ordinary RAM and raw 32-bit PS2 addresses. Kernel services have an explicit
 * value boundary: this reconstruction does not emulate scheduling or timing. */
uint32_t ps2HeapMalloc(uint32_t size);
uint32_t ps2HeapMallocReentrant(uint32_t context,uint32_t size);
void ps2HeapGrow(uint32_t context,uint32_t size);
void ps2HeapFree(uint32_t context,uint32_t payload);
uint32_t ps2HeapTrim(uint32_t context,uint32_t pad);
uint32_t ps2HeapSbrkReentrant(uint32_t context,uint32_t increment);
uint32_t ps2HeapSbrk(uint32_t increment);
void ps2HeapLock(void);
void ps2HeapUnlock(void);
uint32_t ps2KernelGetThreadId(void);
uint32_t ps2KernelEndOfHeap(void);
uint32_t ps2KernelWaitSema(uint32_t id);
uint32_t ps2KernelSignalSema(uint32_t id);
uint32_t ps2KernelCreateSema(const void *parameters);
uint32_t ps2CreateSemaphore(uint32_t initial,uint32_t maximum,uint32_t option);
void ps2DeferredQueueInitialize(uint32_t queue,uint32_t callback);
void ps2DeferredQueueAppend(uint32_t queue,uint32_t value);
void ps2MatListReleasePolicy(uint32_t list,uint32_t deferred);
void ps2MemoryArenaInitialize(uint32_t size);
void *nocturneResolveHeapAddress(uint32_t address);
uint32_t nocturneHeapRuntimeStateRaw(void);
uint32_t nocturneHeapKernelValue(uint32_t selector,uint32_t argument);
uint32_t nocturneHeapKernelCreateValue(const void *parameters);
#endif
