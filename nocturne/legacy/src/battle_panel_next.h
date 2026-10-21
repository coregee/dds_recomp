#ifndef NOCTURNE_BATTLE_PANEL_NEXT_H
#define NOCTURNE_BATTLE_PANEL_NEXT_H
#include "battle_panel_owner.h"
/* Full original five-body source. Actual CPU/FPR/HI/LO/VU banks and guest
 * RAM/SP/RA are live; dispatch1/0 is host handling, never a supplied V0. */
uint32_t nocturneBattlePanelNextBody(uint32_t entry);
uint32_t nocturneBattlePanelNextRun(uint32_t entry);
const uint64_t *nocturneBattlePanelNextLastStop(void);
uint32_t nocturneBattlePanelOwnerRun(uint32_t entry);
const uint64_t *nocturneBattlePanelOwnerLastStop(void);
void nocturneEffectHostCpuRead(unsigned reg,uint32_t words[4]);
void nocturneEffectHostCpuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattlePanelNextStackPointer(void);
void nocturneBattlePanelNextSetStackPointer(uint32_t address);
uint32_t nocturneBattlePanelNextFcsr(void);
void *nocturneResolveBattlePanelNextAddress(uint32_t address);
void nocturneBattlePanelNextDependencyStop(uint32_t entry,uint32_t pc);
_Noreturn void nocturneBattlePanelNextTrap(uint32_t code,uint32_t pc);
void ps2BattlePanelDrawPivotScaledTexture_00279F10(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,float f12);
void nbPanelPressGaugeInit(void);
void nbPanelPressGauge(uint64_t a0);
uint64_t nbPanelPressTurnGaugeRun(void);
void ps2BattlePanelStartPTAOnly_0027D980(void);
#endif
