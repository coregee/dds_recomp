#ifndef NOCTURNE_SIF_CONTROL_KERNEL_NATIVE_H
#define NOCTURNE_SIF_CONTROL_KERNEL_NATIVE_H
#include "battle_native_flow.h"
/* Complete414 original installed-BIOS words for selectors18/22/120/121/122
 * and their static helper closure. Shared queue helpers carry no identity
 * credit. Callers own actual syscall entry and current RAM/MMIO state.
 * No handler ID, free-list state, DMA progress, register acknowledgement,
 * IOP readiness, interrupt or return value is synthesized. */
uint32_t nocturneSifControlKernelResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
