#ifndef NOCTURNE_BATTLE_PANEL_ANALYZE_DEPENDENCIES_H
#define NOCTURNE_BATTLE_PANEL_ANALYZE_DEPENDENCIES_H
#include "battle_panel_analyze.h"
/* Sixteen complete native-bank private variants; host dispatch status only.
 * Existing helpers/retail dependencies gain no new function identity here. */
uint32_t nocturneBattlePanelAnalyzeDependencyBody(uint32_t entry);
void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
uint64_t nocturneBattleActionFormulaSecondaryLo(void);
uint64_t nocturneBattleActionFormulaSecondaryHi(void);
#endif
