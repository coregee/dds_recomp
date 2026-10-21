#ifndef NOCTURNE_PS2_FLUSH_CACHE_NATIVE_H
#define NOCTURNE_PS2_FLUSH_CACHE_NATIVE_H
#include "sound_command_native.h"
/* Original100 dispatcher plus complete mode0 D-cache sweep. Other modes
 * remain real transfers to their original unowned instruction/BTAC bodies.
 * Callback executes exact indexed DXWBIN effects; never an OS reply. */
uint32_t nocturneFlushCacheResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *,NocturneSoundCommandCache,void *);
#endif
