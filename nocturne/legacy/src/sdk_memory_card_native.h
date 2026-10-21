#ifndef NOCTURNE_SDK_MEMORY_CARD_NATIVE_H
#define NOCTURNE_SDK_MEMORY_CARD_NATIVE_H
#include "battle_native_flow.h"
/* Complete28 retail bodies, including two indirect callbacks not yet in the
 * Ghidra function inventory. Original RPC,cache,kernel and alarm callees are
 * real external owners; TRANSFER is not a supplied return or completion.
 * The caller supplies ordinary input RAM and genuinely received IOP packets.
 * Uncached aliases, pending transactions and semaphore ownership are retained. */
uint32_t nocturneSdkMemoryCardResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
