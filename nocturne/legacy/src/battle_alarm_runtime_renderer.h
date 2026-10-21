#ifndef NOCTURNE_BATTLE_ALARM_RUNTIME_RENDERER_H
#define NOCTURNE_BATTLE_ALARM_RUNTIME_RENDERER_H
#include "battle_wakeup_renderer_transport.h"
#include "battle_alarm_runtime.h"
typedef struct NocturneAlarmRendererConfig{uint32_t version,target_future,intc_stat,intc_mask;}NocturneAlarmRendererConfig;
typedef struct NocturneAlarmRendererState{
 uint32_t version,target_future,intc_stat,intc_mask;
 uint64_t edges,compare_requests,overflow_requests,idle_words,idle_spins,irq_entries,syscall_entries,erets;
}NocturneAlarmRendererState;
/* Exact nine additional source-owned RAM extents; init never seeds RAM.
 * Existing kernel/alarm init APIs precede this once per connected world. */
uint32_t nocturneBattlePanelRendererRuntimeInit(const NocturneAlarmRendererConfig *,const NocturneWakeupRendererSpan *,uint32_t);
uint32_t nocturneBattlePanelRendererRuntimeSnapshot(NocturneAlarmRendererState *);
#endif
