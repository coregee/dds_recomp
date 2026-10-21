#ifndef NOCTURNE_RPC_RESPONSE_NATIVE_H
#define NOCTURNE_RPC_RESPONSE_NATIVE_H
#include "battle_native_flow.h"
/* Original77 words: response handler, iSignal67 veneer and reply allocators.
 * An incoming packet is an explicit external input, not proof of IOP arrival.
 * Callback execution and interrupt-context scheduling require their real owners.
 * Positive semaphore IDs execute the installed native negative67 dispatch. */
uint32_t nocturneRpcResponseResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
