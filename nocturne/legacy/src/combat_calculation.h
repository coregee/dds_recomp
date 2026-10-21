#ifndef NOCTURNE_COMBAT_CALCULATION_H
#define NOCTURNE_COMBAT_CALCULATION_H
#include <stdint.h>

/* Native SLUS_209.11 integer slots retain their complete low64 values.
 * Array addresses and word arithmetic wrap at32 bits. Float returns are F0;
 * CriticalPower additionally consumes F12. This readable algorithm layer does
 * not provide volatile-register/HI/LO or original guest-frame transport. */
uint64_t ps2CombatHitType_002654B8(uint64_t context,uint64_t skill,uint64_t source,uint64_t target);
uint64_t ps2CombatAlignment_00265868(uint64_t form);
/* A1 is an unused positional slot; only incoming A0 and A2 are read. */
uint64_t ps2CombatEffectCondition_002658B8(uint64_t skill,uint64_t unused,uint64_t target);
uint64_t ps2CombatEffectType_00265948(uint64_t skill,uint64_t source,uint64_t target);
void ps2CombatAddHpMp_002660C0(uint64_t form,uint64_t resource,uint64_t amount);
float ps2CombatHpDrainRate_00266C90(uint64_t skill);
float ps2CombatMpDrainRate_00266CD8(uint64_t skill);
float ps2CombatReductionRate_00266D20(uint64_t skill);
uint64_t ps2CombatCheckHitEffect_00267370(uint64_t effect);
uint64_t ps2CombatDeadType_00267388(void);
uint64_t ps2CombatCheckStoneDeath_00267390(uint64_t skill,uint64_t form);
void ps2CombatSetStatus_002674D0(uint64_t form,uint64_t set,uint64_t status);
uint64_t ps2CombatCheckStatusRecovery_00267530(uint64_t unit,uint64_t mode);
uint64_t ps2CombatCheckCurse_002677B8(uint64_t form);
void ps2CombatAddEncounterItems_00269318(uint64_t context);
void ps2CombatAddRewards_00269448(uint64_t unit);
uint64_t ps2CombatLevelAverage_002697D8(uint64_t context,uint64_t enemy);
uint64_t ps2CombatParameterAverage_002698C0(uint64_t context,uint64_t enemy,uint64_t parameter);
uint64_t ps2CombatEncounterParameterAverage_002699B0(uint64_t context,uint64_t enemy,uint64_t parameter);
uint64_t ps2CombatCheckPlayerInitiative_00269AD8(uint64_t context);
uint64_t ps2CombatCheckEnemyInitiative_00269D20(uint64_t context);
uint64_t ps2CombatCheckEscape_00269E98(uint64_t context);
uint64_t ps2CombatCheckConsecutiveEncounter_0026A158(uint64_t context);
uint64_t ps2CombatSingleTargetSkill_0026A448(uint64_t skill);
uint64_t ps2CombatSameFormation_0026A470(uint64_t first,uint64_t second);
uint64_t ps2CombatScatteredMoney_0026A4B0(uint64_t unit);
uint64_t ps2CombatCheckPanicAction_0026A688(uint64_t unit);
uint64_t ps2CombatCheckStatusGameOver_0026A6D8(void);
void ps2CombatSetHpModelScale_0026A740(uint64_t record);
/* A0 is read by SLTI even though its result is dead; F12 determines F0. */
float ps2CombatCriticalPower_0026A828(uint64_t source,float power);
uint64_t ps2CombatEarnedExperience_0026A840(uint64_t context);
uint64_t ps2CombatEarnedMoney_0026A870(uint64_t context);
void ps2CombatSetEncounter_00259658(uint64_t encounter);
uint64_t ps2CombatModelScaleDescriptor_00259A60(uint64_t unit);

/* Pure address transport into the same graph used by real registered callees. */
void *nocturneResolveCombatCalculationAddress(uint32_t address);
#endif
