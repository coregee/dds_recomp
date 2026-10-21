#ifndef NOCTURNE_BATTLE_SYSCALL_KERNEL_RESUME_H
#define NOCTURNE_BATTLE_SYSCALL_KERNEL_RESUME_H
#include "battle_native_flow.h"
/* All556 existing syscall/context words, entered at actual PC.
 * ERET0 and external8 retain actual state for the outer native router;
 * this API does not synthesize a syscall exception or any service result. */
uint32_t nocturneBattleSyscallKernelResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
