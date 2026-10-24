// How devils grow: learning skills, EXP, level-up stats, evolution and skill
// power-ups (original unit: cmb; a few helpers from rst, the results screen).
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"

namespace nocturne::cmb {

// ---- Skills -----------------------------------------------------------------

void clearSkills(UnitWork& unit);                                  // cmbClearSkill (first 12 slots)
void createDefaultSkills(uint16_t devil, UnitWork& unit);          // cmbCreateDefaultSkill: the level-0 skills
void createLevelSkills(uint16_t devil, uint8_t level, UnitWork& unit); // ps2CreateLevelSkill (0x222828): all up to `level`
int8_t findSkill(uint16_t skill, const UnitWork& unit);            // cmbChkSkillOwner
int8_t addSkill(uint16_t skill, UnitWork& unit);                   // cmbAddSkill: slot, -2 if owned, -1 if full
// cmbChkLevelUpEvent: the first growth event at the unit's level, and how many.
const GrowthEvent* levelUpEvents(const UnitWork& unit, int8_t* count);

// ---- EXP ----------------------------------------------------------------------

// cmpCalcLevelUpBaseExp: 1.42 L^3 - 5, at least 0.
uint32_t baseExpForLevel(int32_t level);
// cmbCalcLevelUpExp: total EXP a unit needs to be at `level`. For demons the
// curve starts at their species level and is scaled by (2.7 - 0.017 x species
// level); evolved demons add the EXP they had before evolving.
uint32_t expForLevel(const UnitWork& unit, int32_t level);
uint32_t expForNextLevel(const UnitWork& unit);                    // cmbChkLevelUpExp
int32_t levelUpCount(const UnitWork& unit, int32_t addedExp);      // cmbGetLevelUpCount

// ---- Level-up stats ---------------------------------------------------------

// cmbGetParam (rst): the Demi-fiend's raw stat, or a demon's effective stat.
int32_t growthParam(const UnitWork& unit, int32_t stat);
// cmbAddLevelUpParamEx: pick which stat rises at a level-up (and, in mode 0,
// raise it). Returns the stat index, -1 if none can, 6 if the roll misses.
int8_t rollLevelUpStat(UnitWork& unit, int8_t mode);
int8_t addLevelUpStat(UnitWork& unit);                             // ps2AddLevelUpParam (0x223080): mode 0

// ---- Evolution ----------------------------------------------------------------

int8_t evolutionNotice(const UnitWork& unit);                      // cmbChkEvoAttention
int8_t evolutionPassed(const UnitWork& unit);                      // cmbChkCancelEvo
int8_t evolvedSpeciesLevel(const UnitWork& unit);                  // cmbChkDevilEvo
int8_t evolutionLevel(const UnitWork& unit);                       // cmbGetDevilEvoLevel
bool evolutionNeedsEvent(uint16_t devil);                          // cmbChkEvoNeedFlag
int32_t evolutionLevelLimit(const UnitWork& player, const UnitWork& stock,
                            const UnitWork& evolved, int32_t eventLevel); // cmbChkEvoDevilLev
void copyEvolvedDevil(UnitWork& unit, const UnitWork& evolved);    // cmbCopyEvoDevilToStock

// ---- Skill power-ups and mutation -------------------------------------------

uint16_t powerUpSkill(uint16_t skill);                             // cmbGetPowerUpSkill: 0 if none
uint16_t randomPowerUpSkill(const UnitWork& unit, int8_t* slot);   // rstRndGetPowerUpSkill
uint16_t mutationSkill(uint16_t skill, UnitWork& unit);            // cmbGetMutationSkill [version]

} // namespace nocturne::cmb
