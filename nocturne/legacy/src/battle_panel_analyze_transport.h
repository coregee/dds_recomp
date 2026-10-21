#ifndef NOCTURNE_BATTLE_PANEL_ANALYZE_TRANSPORT_H
#define NOCTURNE_BATTLE_PANEL_ANALYZE_TRANSPORT_H
#include "battle_panel_analyze_dependencies.h"
#include "battle_panel_renderer_bundle.h"
#include "battle_native_flow.h"
uint32_t nocturneBattlePanelAnalyzeRun(uint32_t entry);
uint32_t nocturneBattlePanelAnalyzeRunTyped(uint32_t entry);
const NocturneBattlePanelRendererStop *nocturneBattlePanelAnalyzeLastStop(void);
void nocturneBattlePanelAnalyzeBaseCall(uint32_t target,uint32_t pc);
void nocturneBattlePanelAnalyzeSyscall(uint32_t pc,uint64_t selector);
/* Raw resumable source route. Inputs and returned state are actual full banks;
 * a different thread PC or unprovided boundary must stop the static caller. */
uint32_t nocturneBattlePanelAnalyzeRawOwns(uint32_t pc);
void nocturneBattlePanelAnalyzeRawCall(uint32_t entry,uint32_t call_pc);
void nocturneBattlePanelAnalyzeRawSyscall(uint32_t pc,uint64_t selector);
/* Explicit initialized ordinary-RAM ranges and non-bank CPU BEFORE fields.
 * No service answer or return-state input is accepted. Live banks are read at
 * each genuine native entry; counts and special fields then remain source-owned. */
uint32_t nocturneBattlePanelAnalyzeRawConfigure(const NocturneWakeupMachine *before,const uint32_t *ranges,uint32_t count,uint64_t limit);
const NocturneWakeupMachine *nocturneBattlePanelAnalyzeRawState(void);
const NocturneWakeupStop *nocturneBattlePanelAnalyzeRawStop(void);
#endif
