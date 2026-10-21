#ifndef NOCTURNE_RPC_CLIENT_NATIVE_H
#define NOCTURNE_RPC_CLIENT_NATIVE_H
#include "battle_native_flow.h"
/* Complete358 original words. Native packet reserve/release, Bind/Call,
 * heap/loadfile client initialization and65/68 veneers. Sends and semaphores
 * use the shared actual owners; no server pointer, RPC completion, semaphore
 * reply or synthetic return is supplied. Synchronous waits can switch to a
 * different thread while the calling client stays pending. */
uint32_t nocturneRpcClientResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
