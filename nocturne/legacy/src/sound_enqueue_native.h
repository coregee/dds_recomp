#ifndef NOCTURNE_SOUND_ENQUEUE_NATIVE_H
#define NOCTURNE_SOUND_ENQUEUE_NATIVE_H
#include "battle_native_flow.h"
/* Complete131 original words. Counter wrap skips zero, full-ring retries,
 * real byte/vector memcpy, slot/header publication, synchronous pump and
 * actual WakeupThread51 call execute against shared raw banks and RAM.
 * Caller owns actual syscall entry/scheduling; no queue space, returned
 * thread ID, wake result, worker completion or DMA response is supplied. */
uint32_t nocturneSoundEnqueueResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
