#ifndef NOCTURNE_BATTLE_PANEL_COLOR_CALLERS_H
#define NOCTURNE_BATTLE_PANEL_COLOR_CALLERS_H
#include <stdint.h>
/* Six complete registered variants, zero new identities. Dispatch consumes
 * the actual live full CPU128/FPR32/HI/LO/VU banks and guest SP/RA. Handled1/0
 * is host dispatch status only; actual native V0 remains in the shared bank.
 * No argument seeding, snapshots, register repair or assumed upper lanes. */
uint32_t nocturneBattlePanelColorCallerBody(uint32_t entry);

/* UNIMPLEMENTED real-native boundary routes. Each hook must execute original
 * callee operations against the current bank/frame, retaining all actual
 * clobbers and RAM effects. A semantic result alone is insufficient. Reject
 * unsupported routes before callee execution; never return a supplied value.
 * NativeCall receives original fixed call PC and target; RA/delay are already
 * executed. Indirect is restricted by the source to genuine OT target2ACD40.
 * Trap must stop at the actual BREAK and never synthesize normal return. */
void nocturneBattlePanelColorCallerNativeCall(uint32_t target,uint32_t pc);
void nocturneBattlePanelColorCallerIndirectCall(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattlePanelColorCallerTrap(uint32_t code,uint32_t pc);
#endif
