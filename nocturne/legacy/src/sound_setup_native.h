#ifndef NOCTURNE_SOUND_SETUP_NATIVE_H
#define NOCTURNE_SOUND_SETUP_NATIVE_H
#include "battle_native_flow.h"
/* Complete439 original words: sound entry/modules/load-module/version and
 * native strncpy/memcmp. RPC/semaphore/cache/DMA/memcpy use shared owners.
 * Module/IOP replies, heap allocations and callback returns are not supplied.
 * Unsupported downstream callers remain real control-transfer boundaries. */
uint32_t nocturneSoundSetupResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
