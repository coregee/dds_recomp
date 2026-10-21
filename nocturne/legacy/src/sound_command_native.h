#ifndef NOCTURNE_SOUND_COMMAND_NATIVE_H
#define NOCTURNE_SOUND_COMMAND_NATIVE_H
#include "battle_native_flow.h"
/* Actual181-word drain/send/cache/119-veneer bodies. No queue advance or
 * success is supplied by the router. Unknown calls transfer8 with native
 * effects, syscall119 yields unexecuted9. CACHE uses an explicit actual
 * cache owner: return1 only after committing its full effect, including
 * any dirty64B writeback; return0 must change nothing. A NULL owner stops10
 * before counting/executing CACHE, preserving prior native SYNC0 effects.
 * This is not a silent no-op cache or an assumed successful DMA service. */
typedef int (*NocturneSoundCommandCache)(void *,uint32_t pc,uint32_t operation,uint32_t address);
uint32_t nocturneSoundCommandResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *,NocturneSoundCommandCache,void *);
#endif
