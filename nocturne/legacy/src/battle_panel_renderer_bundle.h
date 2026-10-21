#ifndef NOCTURNE_BATTLE_PANEL_RENDERER_BUNDLE_H
#define NOCTURNE_BATTLE_PANEL_RENDERER_BUNDLE_H
#include <stdint.h>
#include "battle_renderer_indexed_cache.h"
/* Host BEFORE/state API only. Native entry never requires an init receipt. */
uint32_t nocturneBattlePanelRendererCacheInit(const NocturneIndexedCacheConfig *config);
uint32_t nocturneBattlePanelRendererCacheSnapshot(NocturneIndexedCacheState *out);
/* Host observation only: 1=normal native return,0=tagged unprovided stop.
 * Native V0 and all live banks are retained, never seeded from this result. */
uint32_t nocturneBattlePanelRendererRun(uint32_t entry);
typedef struct NocturneBattlePanelRendererStop {
 uint32_t version,reason,pc,operation;uint64_t target;uint32_t sp,ra;
} NocturneBattlePanelRendererStop;
const NocturneBattlePanelRendererStop *nocturneBattlePanelRendererLastStop(void);
typedef struct NocturneBattlePanelRendererCallReceipt {
 uint32_t version,completed,has_result,trap_code;uint64_t result;
 uint32_t unprovided,core_observer_tainted;
} NocturneBattlePanelRendererCallReceipt;
/* Actual target ABI0..5 raw slots; zeroargs require VOID. A private host
 * trampoline always uses CoreObserve V1, never publishes its context as A0. */
uint32_t nocturneBattlePanelRendererObserveCall(void (*function)(void),uint32_t argc,const uint64_t *arguments,uint32_t return_width);
const NocturneBattlePanelRendererCallReceipt *nocturneBattlePanelRendererLastCall(void);
void nocturneBattlePanelRendererCall(uint32_t target,uint32_t pc);
void nocturneBattlePanelRendererIndirect(uint64_t target,uint32_t pc);
void nocturneBattlePanelRendererSyscall(uint32_t pc,uint64_t selector,uint32_t argc,const uint64_t *arguments);
_Noreturn void nocturneBattlePanelRendererUnprovided(uint32_t pc,uint32_t operation,uint64_t target);
_Noreturn void nocturneBattlePanelRendererAbort(void);
_Noreturn void nocturneBattlePanelRendererTrap(uint32_t code,uint32_t pc);
/* operation:1=direct,2=indirect,3=syscall,4=Status,5=DI,6=EI,7=SYNC,
 * 8=BREAK,9=invariant. These are observation tags, not OS replies. */
#endif
