#ifndef NOCTURNE_SIF_INITIALIZATION_NATIVE_H
#define NOCTURNE_SIF_INITIALIZATION_NATIVE_H
#include "battle_native_flow.h"
/* Nine complete existing retail owners: RPC/CMD initialization, command table
 * publication, EnableDmac wrapper and actual18/22/120/121/122 veneers. Flags,
 * arrays, native frames, raw signed selection and MMIO use shared state.
 * Every SYS yields before execution. IOP readiness/handlers, DMA progress and
 * registration/service results are never supplied by this source owner. */
uint32_t nocturneSifInitializationResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
