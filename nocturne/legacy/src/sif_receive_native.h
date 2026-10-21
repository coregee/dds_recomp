#ifndef NOCTURNE_SIF_RECEIVE_NATIVE_H
#define NOCTURNE_SIF_RECEIVE_NATIVE_H
#include "battle_native_flow.h"
/* Original78 game and13 BIOS words. Packet/header data and SIF0 device state
 * are explicit inputs; no IOP delivery, handler result or ready TCB supplied.
 * Dispatch transfers to the actual registered handler using its stack copy.
 * SetDChain rearms the channel; DMAE0 gives no autonomous transfer progress. */
uint32_t nocturneSifReceiveResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
