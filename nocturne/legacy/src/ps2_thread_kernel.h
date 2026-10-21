#ifndef NOCTURNE_PS2_THREAD_KERNEL_H
#define NOCTURNE_PS2_THREAD_KERNEL_H
#include "battle_native_flow.h"
/* Complete183 original BIOS words: CreateThread32, StartThread34 wrapper and
 * helper, free-TCB pop. The15-word pop also belongs to the IRQ owner.
 * Use actual PC, shared machine and RAM. No thread ID, queue, context, syscall
 * entry or scheduler result is synthesized. ERET0 may select another thread;
 * transfer8 preserves real branch/delay effects for the outer native owner. */
uint32_t nocturneThreadKernelResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
