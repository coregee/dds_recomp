#ifndef NOCTURNE_BATTLE_WAKEUP_RENDERER_TRANSPORT_H
#define NOCTURNE_BATTLE_WAKEUP_RENDERER_TRANSPORT_H
#include "battle_wakeup_kernel.h"
/* Diagnostic-owned actual CP0/SA/COP1-ACC cells, explicit BEFORE once/world.
 * Shared Status/FCSR/CPU/FPR/HILO/RAM remain their existing real owners. */
typedef struct NocturneWakeupRendererConfig {
 uint32_t version,cause,epc,sa,fpu_acc;
} NocturneWakeupRendererConfig;
typedef struct NocturneWakeupRendererSpan {uint32_t address,length;} NocturneWakeupRendererSpan;
typedef struct NocturneWakeupRendererState {
 uint32_t version,cause,epc,sa,fpu_acc,stopped_kernel;
 uint64_t calls,native_steps,sync_p;
} NocturneWakeupRendererState;
typedef struct NocturneWakeupRendererCall {
 uint32_t version,outcome;uint64_t ordinal,selector;
 uint32_t entry_pc,return_pc;uint64_t native_steps,sync_p;
} NocturneWakeupRendererCall;
/* Return0=valid operation,1=invalid. Init never seeds RAM or shared banks.
 * Spans must be the seven prior kernel BEFORE extents, the original47/53
 * dispatch words at1203C/12054, then full gueststack (ten spans total).
 * Calls occur through genuine native source syscall sites, never this API. */
uint32_t nocturneBattlePanelRendererKernelInit(const NocturneWakeupRendererConfig *,const NocturneWakeupRendererSpan *,uint32_t);
uint32_t nocturneBattlePanelRendererKernelSnapshot(NocturneWakeupRendererState *);
uint64_t nocturneBattlePanelRendererKernelCallCount(void);
uint32_t nocturneBattlePanelRendererKernelReceiptOverflow(void);
uint32_t nocturneBattlePanelRendererKernelGetCall(uint64_t,NocturneWakeupRendererCall *);
/* Only valid after an actual unfinished kernel call. This is authoritative
 * full stopped CPU including signextended kernelSP; legacy EffectHost CPU29
 * exposes only uint32 SP and cannot represent that stopped prefix fully. */
uint32_t nocturneBattlePanelRendererKernelStoppedMachine(NocturneWakeupMachine *);
/* Separate installed alarm/timer BEFORE owner. Init validates eleven exact
 * constructor spans and never writes RAM/shared banks or supplies a result.
 * Timer values are explicit no-clock/no-edge inputs; MODE flags are W1C.
 * Passive256-event ring never caps native execution; Overflow reports loss. */
typedef struct NocturneWakeupRendererAlarmState {uint32_t version,count,mode,comp;} NocturneWakeupRendererAlarmState;
typedef struct NocturneWakeupRendererAlarmEvent {uint32_t operation,address,bytes,value;} NocturneWakeupRendererAlarmEvent;
uint32_t nocturneBattlePanelRendererAlarmInit(const NocturneWakeupRendererAlarmState *,const NocturneWakeupRendererSpan *,uint32_t);
uint32_t nocturneBattlePanelRendererAlarmSnapshot(NocturneWakeupRendererAlarmState *);
uint64_t nocturneBattlePanelRendererAlarmEventCount(void);
uint32_t nocturneBattlePanelRendererAlarmEventOverflow(void);
uint32_t nocturneBattlePanelRendererAlarmGetEvent(uint64_t,NocturneWakeupRendererAlarmEvent *);
#endif
