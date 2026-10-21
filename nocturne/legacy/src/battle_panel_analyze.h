#ifndef NOCTURNE_BATTLE_PANEL_ANALYZE_H
#define NOCTURNE_BATTLE_PANEL_ANALYZE_H
#include "battle_panel_owner.h"
/* Full original7 Analyze bodies. CPU/FPR/VU/HI/LO, guest RAM and SP/RA are live.
 * Host handled1/0 is dispatch status, never an assumed native V0 result. */
uint32_t nocturneBattlePanelAnalyzeBody(uint32_t entry);
/* Real-native integration boundaries. Execute whole original callee operations
 * against actual banks/frame, or stop at the genuine boundary. A semantic
 * return alone, seeded allocator result or supplied service answer is invalid. */
void nocturneBattlePanelAnalyzeCall(uint32_t target,uint32_t pc);
void nocturneBattlePanelAnalyzeIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattlePanelAnalyzeTrap(uint32_t code,uint32_t pc);
void *nocturneResolveBattlePanelAnalyzeAddress(uint32_t address);
uint32_t nocturneBattlePanelAnalyzeStackPointer(void);
void nocturneBattlePanelAnalyzeSetStackPointer(uint32_t address);
uint32_t nocturneBattlePanelAnalyzeFcsr(void);
void nocturneEffectHostCpuRead(unsigned reg,uint32_t words[4]);
void nocturneEffectHostCpuWrite(unsigned reg,const uint32_t words[4]);
void ps2BattlePanelCenterFontRequest_0027A240(uint64_t a0,uint64_t a1);
void ps2BattlePanelDrawScaledGradientRect_0027A630(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,float f12,float f13);
void nbPanelAnalyzeInit(void);
void nbPanelAnalyzeStart(void);
void ps2BattlePanelSetAnalyzeUnit_00280538(uint64_t a0);
void nbPanelAnalyzeRun(void);
void ps2BattlePanelSetEnabled_00282200(uint64_t a0);
#endif
