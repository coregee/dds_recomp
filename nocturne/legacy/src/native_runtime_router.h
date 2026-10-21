#ifndef NOCTURNE_NATIVE_RUNTIME_ROUTER_H
#define NOCTURNE_NATIVE_RUNTIME_ROUTER_H
#include "battle_native_flow.h"
/* Host control transport. A selected owner executes original fixed statements;
 * it must not supply an external result. Ownership is checked before dispatch.
 * Unknown PCs and switched-thread continuations retain the actual machine. */
typedef struct NocturneNativeRouter {
 void *owner;
 int (*contains)(void *,uint32_t);
 uint32_t (*resume)(void *,NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
} NocturneNativeRouter;
typedef struct NocturneNativeRouteCounts {
 uint64_t dispatches,syscalls,erets;
} NocturneNativeRouteCounts;
/* Count one actual unexecuted non-delay SYS and enter the architectural
 * exception. Caller must have reached SYS through a verified native owner.
 * This operation supplies neither a service return nor an interrupt event. */
uint32_t nocturneNativeEnterSyscall(NocturneWakeupMachine *,uint64_t remaining,NocturneWakeupStop *);
/* Remaining budget is relative to the incoming instruction count. ERET follows
 * its real selected PC; it never restores the initial caller. Counts accumulate.
 * stop_pc is an explicit observation boundary, checked before dispatch. */
uint32_t nocturneNativeRouteResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,const NocturneNativeRouter *,uint64_t remaining,uint32_t stop_pc,NocturneWakeupStop *,NocturneNativeRouteCounts *);
#endif
