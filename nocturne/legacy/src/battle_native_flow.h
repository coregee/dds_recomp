#ifndef NOCTURNE_BATTLE_NATIVE_FLOW_H
#define NOCTURNE_BATTLE_NATIVE_FLOW_H
#include "battle_wakeup_kernel.h"
/* Resumable native owners share the actual machine and RAM. A transfer is
 * never a supplied result or sleeping-caller completion. The outer router
 * follows actual pc, including ERET into another thread or callback. */
enum NocturneNativeFlow {
 NOCTURNE_NATIVE_TRANSFER=8,
 /* At an actual unexecuted non-delay SYSCALL. The router counts this word
  * exactly once and applies architectural exception entry; no service reply. */
 NOCTURNE_NATIVE_SYSCALL=9,
 NOCTURNE_NATIVE_PROCESSOR_DOMAIN=10
};
/* Transfer stops use pc=actual next32-bit PC and target=SE32(pc), bytes0.
 * Existing RETURNED0 denotes an executed ERET in these resumable owners,
 * not return of the original caller. Faults retain all prior effects.
 * Each owner receives a remaining instruction budget; zero stops with7. */
#endif
