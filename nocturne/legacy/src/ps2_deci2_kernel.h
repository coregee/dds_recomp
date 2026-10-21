#ifndef NOCTURNE_PS2_DECI2_KERNEL_H
#define NOCTURNE_PS2_DECI2_KERNEL_H
#include "battle_native_flow.h"
/* Explicit installed-PCS profile; raw EE hardware debug semantics differ.
 * PCCR CTE-enabled counter updates require a clock owner and stop at the
 * actual write instruction. PCR values are preserved while CTE is clear.
 * Ordinary flat-RAM access does not construct TLBs or emulate cache refills.
 * No BIOS result, allocated port ID or callback acknowledgement supplied. */
typedef struct NocturneDeci2PlatformState {
 uint32_t version,profile,bad_vaddr,rd23,error_epc,pccr,pcr0,pcr1;
} NocturneDeci2PlatformState;
_Static_assert(sizeof(NocturneDeci2PlatformState)==32,"DECI2 platform32");
uint32_t nocturneDeci2KernelResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *,NocturneDeci2PlatformState *);
#endif
