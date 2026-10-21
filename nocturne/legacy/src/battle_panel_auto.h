#ifndef NOCTURNE_BATTLE_PANEL_AUTO_H
#define NOCTURNE_BATTLE_PANEL_AUTO_H
#include "battle_panel_owner.h"
/* Full original Auto bodies and registered private variants. Actual CPU/FPR/HI/LO/VU banks and guest
 * RAM/SP/RA are live; dispatch1/0 is host handling, never a supplied V0. */
uint32_t nocturneBattlePanelAutoBody(uint32_t entry);
uint32_t nocturneBattlePanelAutoRun(uint32_t entry);
const uint64_t *nocturneBattlePanelAutoLastStop(void);
uint32_t nocturneBattlePanelOwnerRun(uint32_t entry);
const uint64_t *nocturneBattlePanelOwnerLastStop(void);
void nocturneEffectHostCpuRead(unsigned reg,uint32_t words[4]);
void nocturneEffectHostCpuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattlePanelAutoStackPointer(void);
void nocturneBattlePanelAutoSetStackPointer(uint32_t address);
uint32_t nocturneBattlePanelAutoFcsr(void);
void *nocturneResolveBattlePanelAutoAddress(uint32_t address);
void nocturneBattlePanelAutoDependencyStop(uint32_t entry,uint32_t pc);
_Noreturn void nocturneBattlePanelAutoIndirectStop(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattlePanelAutoTrap(uint32_t code,uint32_t pc);
void ps2BattlePanelDrawGradientRect_0027A4E0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6);
void nbPanelAutoShow(void);
uint64_t nbPanelAutoCheckShow(void);
void nbPanelAutoInit(void);
void ps2BattlePanelDrawAutoIndicator_00281E60(uint64_t a0);
#endif
