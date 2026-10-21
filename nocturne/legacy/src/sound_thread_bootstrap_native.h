#ifndef NOCTURNE_SOUND_THREAD_BOOTSTRAP_NATIVE_H
#define NOCTURNE_SOUND_THREAD_BOOTSTRAP_NATIVE_H
#include "battle_native_flow.h"
/* Entire85-word initializer/worker/three veneers in one actual machine/RAM.
 * External8 and unexecuted-SYS9 are native continuations, never replies.
 * observation_pc is a passive caller-selected instruction boundary; UINT32_MAX
 * disables it. A stop there changes no guest state and supplies no result.
 * Unowned SREG, command-drain and RPC-creator targets transfer with real
 * link/delay effects retained. Their behavior is not replaced here. */
uint32_t nocturneSoundThreadBootstrapResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,uint32_t observation_pc,NocturneWakeupStop *);
#endif
