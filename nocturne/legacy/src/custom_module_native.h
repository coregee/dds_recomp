#ifndef NOCTURNE_CUSTOM_MODULE_NATIVE_H
#define NOCTURNE_CUSTOM_MODULE_NATIVE_H
#include "battle_native_flow.h"
/* Original612 words, including two retained unreachable padding NOPs.
 * Actual handle/pool/strlen/copy/private RPC, mutex and request semaphores
 * use shared RAM/owners. End handler releases mutex before request signal.
 * No allocated address, module result or IOP reply is supplied by this owner.
 * Arbitrary callbacks/printf remain true unexecuted transfer boundaries. */
uint32_t nocturneCustomModuleResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
