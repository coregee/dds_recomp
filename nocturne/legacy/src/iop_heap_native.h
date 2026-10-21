#ifndef NOCTURNE_IOP_HEAP_NATIVE_H
#define NOCTURNE_IOP_HEAP_NATIVE_H
#include "battle_native_flow.h"
/* Ten original client bodies,303 words. Real CallRpc/cache/DMA/semaphore
 * owners operate on shared RAM. No heap address or service result is supplied
 * by this owner. Pending submission does not mean completed allocation. */
uint32_t nocturneIopHeapResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
