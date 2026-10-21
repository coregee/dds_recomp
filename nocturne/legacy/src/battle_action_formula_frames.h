#ifndef NOCTURNE_BATTLE_ACTION_FORMULA_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_FORMULA_FRAMES_H
#include <stdint.h>
/* Native raw positional slots/F12/F0; shared bank/SP required. Zero new credit. */
#include "nocturne.h"
uint64_t nocturneBattleActionFormulaSecondaryLo(void);
uint64_t nocturneBattleActionFormulaSecondaryHi(void);
void nocturneBattleActionFormulaSecondaryWrite(uint64_t loValue,uint64_t hiValue);
uint64_t ps2BattleActionFormula_001E0F50(uint64_t a0);
uint64_t ps2BattleActionFormula_001E9998(void);
uint64_t ps2BattleActionFormula_00242A88(uint64_t a0);
uint64_t ps2BattleActionFormula_00242B68(uint64_t a0);
uint64_t ps2BattleActionFormula_00242D18(uint64_t a0);
void ps2BattleActionFormula_00243BD0(uint64_t a0, uint64_t a1);
void ps2BattleActionFormula_00243C10(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_00243E78(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_00243EE0(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_00243F40(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_00243FE8(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_002440C0(uint64_t a0);
uint64_t ps2BattleActionFormula_002515D8(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_002516E8(uint64_t a0, uint64_t a1, uint64_t a2);
void ps2BattleActionFormula_002517E0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
uint64_t ps2BattleActionFormula_00262F58(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionFormula_002654B8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
float ps2BattleActionFormula_00266130(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionFormula_00266350(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
uint64_t ps2BattleActionFormula_00266878(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
float ps2BattleActionFormula_00266C90(uint64_t a0);
float ps2BattleActionFormula_00266CD8(uint64_t a0);
float ps2BattleActionFormula_00266D20(uint64_t a0);
uint64_t ps2BattleActionFormula_00266D60(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionFormula_00267180(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionFormula_00267370(uint64_t a0);
uint64_t ps2BattleActionFormula_00267388(void);
uint64_t ps2BattleActionFormula_00267390(uint64_t a0, uint64_t a1);
void ps2BattleActionFormula_002674D0(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionFormula_00267530(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_00267890(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionFormula_00267E38(uint64_t a0);
uint64_t ps2BattleActionFormula_00267E90(uint64_t a0, uint64_t a1);
float ps2BattleActionFormula_002684B0(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_00268620(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionFormula_002688B8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionFormula_002688D0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionFormula_00268C60(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionFormula_00268D60(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionFormula_0026A2D8(uint64_t a0);
uint64_t ps2BattleActionFormula_0026A338(uint64_t a0);
void ps2BattleActionFormula_0026A398(uint64_t a0);
uint64_t ps2BattleActionFormula_0026A3D8(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_0026A468(uint64_t a0);
uint64_t ps2BattleActionFormula_0026A470(uint64_t a0, uint64_t a1);
float ps2BattleActionFormula_0026A828(uint64_t a0, float f12);
float ps2BattleActionFormula_002C0C00(uint64_t a0);
uint64_t ps2BattleActionFormula_002D18B0(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionFormula_002D3398(uint64_t a0, uint64_t a1);
float ps2BattleActionFormulaLegacy_sdfGetRandFloat(uint32_t *state);
uint32_t ps2BattleActionFormulaLegacy_evtBitCheck(int32_t no);
uint32_t ps2BattleActionFormulaLegacy_evtGetAgeOfMoon(void);
int32_t ps2BattleActionFormulaLegacy_datGetBaseMaxHp(datUnitWork_PS2 *work);
void ps2BattleActionFormulaLegacy_datSetBadStat(datUnitWork_PS2 *work,uint32_t status);
void ps2BattleActionFormulaLegacy_datResetBadStat(datUnitWork_PS2 *work,uint32_t status);
int32_t ps2BattleActionFormulaLegacy_datGetBaseParam(datUnitWork_PS2 *work,int32_t selector);
int32_t ps2BattleActionFormulaLegacy_datGetParam(datUnitWork_PS2 *work,int32_t selector);
int32_t ps2BattleActionFormulaLegacy_datGetBadStatusAttr(int32_t status);
int32_t ps2BattleActionFormulaLegacy_datCheckSyojiSkill(datUnitWork_PS2 *work,uint32_t skill);
int32_t ps2BattleActionFormulaLegacy_nbHatudoCheckSkill(datUnitWork_PS2 *work,int32_t skill);
#endif
