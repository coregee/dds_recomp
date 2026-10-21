#ifndef NOCTURNE_SOUND_ACK_NATIVE_H
#define NOCTURNE_SOUND_ACK_NATIVE_H
#include "battle_native_flow.h"
/* Original command80000001 handler. Packet+10 selects a raw32bit index;
 * context+1C owns the destination table pointer. No bounds clamp,EE wake,
 * ACK-wait result or completed transport is supplied. JR and its delay slot
 * require two remaining instructions; insufficient budget stops before JR.
 * Unbacked memory faults are terminal for this owner: an exception/branch
 * continuation is not reconstructed by retrying a delay-slot fault. */
uint32_t nocturneSoundAckResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
