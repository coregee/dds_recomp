#ifndef NOCTURNE_NATIVE_KERNEL_ROUTER_H
#define NOCTURNE_NATIVE_KERNEL_ROUTER_H
#include "native_runtime_router.h"
/* Complete existing exception, scheduler, thread, semaphore and newlib heap
 * owners. Actual PC chooses the original body; unknown continuations stop.
 * contains/body let another source owner compose this into its own router.
 * No initialization, interrupt delivery, clock or service response is supplied. */
int nocturneNativeKernelOwns(uint32_t);
uint32_t nocturneNativeKernelBody(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
uint32_t nocturneNativeKernelResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,uint32_t,NocturneWakeupStop *,NocturneNativeRouteCounts *);
#endif
