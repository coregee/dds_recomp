#ifndef NOCTURNE_BATTLE_ALARM_KERNEL_DISPATCH_H
#define NOCTURNE_BATTLE_ALARM_KERNEL_DISPATCH_H
#include "battle_wakeup_kernel.h"
/* Optional fixed native owner sharing the same machine, memory and budget.
 * A successful return leaves pc at the actual incoming RA; failures retain
 * the stopped machine and all prior effects. This extended profile also admits
 * exact SleepThread50; a kernel ERET may switch to another thread and does not
 * alone prove that the original sleeping caller returned. */
typedef uint32_t (*NocturneWakeupNativeFunction)(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
uint32_t nocturneThreadKernelSyscallWithAlarm(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint32_t syscall_pc,uint64_t max_instructions,NocturneWakeupStop *,NocturneWakeupNativeFunction alarm_registration);
#endif
