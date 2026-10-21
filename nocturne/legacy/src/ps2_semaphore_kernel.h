#ifndef NOCTURNE_PS2_SEMAPHORE_KERNEL_H
#define NOCTURNE_PS2_SEMAPHORE_KERNEL_H
#include "battle_native_flow.h"
/* Complete56 original BIOS words. Actual free-head, count,32-byte records,
 * parameters and allocation failures execute against one shared RAM owner.
 * No semaphore ID, constructor return, pool reset or wait state is supplied.
 * External8 retains native JR/delay effects; caller owns syscall entry/ERET. */
uint32_t nocturneSemaphoreKernelResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
