#ifndef NOCTURNE_SOUND_STATE_NATIVE_H
#define NOCTURNE_SOUND_STATE_NATIVE_H
#include "battle_native_flow.h"
/* Nine complete271-word original callers/initializers. Actual heap/RPC,
 * enqueue and kernel owners use shared state. Printf really spills integer
 * and FPU banks and initializes the native FILE records; vfprintf2D6678
 * remains a true unresolved transfer. No diagnostic or heap return supplied. */
uint32_t nocturneSoundStateResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
