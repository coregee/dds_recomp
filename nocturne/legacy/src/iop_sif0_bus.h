#ifndef NOCTURNE_IOP_SIF0_BUS_H
#define NOCTURNE_IOP_SIF0_BUS_H
#include "iop_sifman_native.h"
#include "sif0_transport.h"
typedef struct {
 NocturneIopSifmanDevice bus;
 NocturneSif0Transport transport;
 uint64_t instruction_clock,iop_due;
 uint32_t iop_event_armed,iop_cycles_per_instruction;
} NocturneIopSif0World;
/* Fixed observed relocated module profile. Native received RPC, SIFMAN ISR
 * statements share RAM/IRQ. CHCR starts compute transport and schedule its
 * pending completion. Explicit cycles-per-instruction is a finite harness
 * clock profile, not general R3000/PCSX2 instruction timing. Delivery clears
 * CHCR and publishes an IOP IRQ request only. ISR statements are admitted when
 * the caller reaches their actual PC; guest exception entry remains unowned. */
uint32_t nocturneIopSif0Resume(NocturneIopMachine *,uint8_t *,uint32_t,
 uint8_t *,uint32_t,uint64_t,NocturneIopSif0World *);
#endif
