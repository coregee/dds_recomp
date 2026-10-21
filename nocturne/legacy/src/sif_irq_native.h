#ifndef NOCTURNE_SIF_IRQ_NATIVE_H
#define NOCTURNE_SIF_IRQ_NATIVE_H
#include "battle_native_flow.h"
/* Original164 BIOS,5 SDK trampoline and80 game words. The callback lists,
 * received packets and hardware interrupt state are declared inputs; native
 * dispatch, user transition, negative5 return and reschedule execute in RAM.
 * Incoming IOP binds run actual lookup, reply allocation and SIF submission.
 * Fatal/unowned callbacks remain transfers; no client return is supplied. */
uint32_t nocturneSifIrqResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
