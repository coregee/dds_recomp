#ifndef NOCTURNE_PS2_SEMAPHORE_WAIT_DELETE_H
#define NOCTURNE_PS2_SEMAPHORE_WAIT_DELETE_H
#include "battle_native_flow.h"
/* Original203 words, complete65/68 wrappers and helpers. Allocator/free
 * chains, waiter lists, scheduler choice and actual ERET use shared RAM.
 * RETURNED0 denotes ERET; it can select idle while the caller remains WAIT.
 * Do not replace that switch with a returned semaphore/RPC success. */
uint32_t nocturneSemaphoreWaitDeleteResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif
