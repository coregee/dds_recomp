#ifndef NOCTURNE_SOUND_RPC_QUEUE_NATIVE_H
#define NOCTURNE_SOUND_RPC_QUEUE_NATIVE_H
#include "battle_native_flow.h"
/* Complete155 original words. Queue/server publication, native list traversal,
 * empty-request poll and real Sleep call execute in the shared CPU128/RAM.
 * DI/EI use actual EDI/EXL/ERL/KSU permission and only change EIE.
 * Requests and callback results are never supplied. Unowned nonempty-request
 * service2DF260 transfers with native link/delay effects for its real owner. */
uint32_t nocturneSoundRpcQueueResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
