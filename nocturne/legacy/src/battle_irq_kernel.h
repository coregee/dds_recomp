#ifndef NOCTURNE_BATTLE_IRQ_KERNEL_H
#define NOCTURNE_BATTLE_IRQ_KERNEL_H
#include "battle_native_flow.h"
/* Resumable fixed-PC BIOS owner. No exception/event entry is synthesized.
 * TRANSFER retains the real architectural next pc after all link/delay effects;
 * the external router must execute its real owner, then resume at m->pc.
 * PROCESSOR_DOMAIN is a hard boundary, never an external reply.
 * Existing outcome0 means an actual ERET, not sleeping-caller completion. */
uint32_t nocturneBattleIrqKernelResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t max_instructions,NocturneWakeupStop *);
#endif
