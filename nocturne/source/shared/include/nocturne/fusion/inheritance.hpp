// Skill inheritance ("keisyo" = 継承): which skills a fused or evolved devil
// can take from its sources, and how likely (original unit: cmb).
//
// A skill's rate for a devil = base score for (devil inheritance type, skill
// element) / the skill's inheritance level + (unit level - species level) + 1,
// capped at 99; 0 if the skill's form mask excludes the devil's form.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"

namespace nocturne::cmb {

uint8_t inheritScore(int16_t skillattr, int16_t keisyotype);     // cmbGetKeisyoSkillScore
uint8_t inheritFormMatch(uint16_t skillForm, uint16_t devilForm);// cmbGetKeisyoSkillMotion
// cmbGetKeisyoSkillLevel [version]. Hardtype's doesn't reset its row
// counter, so it starts from what the caller left there (`counter`; US
// Maniax ignores it), and leaves it in `counterOut`.
uint8_t inheritLevel(uint16_t skill, uint32_t counter = 0, uint32_t* counterOut = nullptr);
uint8_t inheritRate(const UnitWork& unit, uint16_t skill);       // cmbCalcKeisyoSkillRate
int32_t totalInheritRate(const UnitWork& unit);                  // cmbCalcTotalKeisyoSkillRate

// The 24-slot list of skills waiting to be inherited (UnitWork::keisyoskill).
int8_t inheritedEnd(const UnitWork& unit);                       // cmbGetKeisyoSkillEndIndex: first empty slot
void clearInherited(UnitWork& unit);                             // cmbClearKeisyoSkill
int8_t findInherited(uint16_t skill, const UnitWork& unit);      // cmbChkKeisyoSkillOwner
int8_t countInherited(const UnitWork& unit);                     // cmbChkKeisyoSkillNums

} // namespace nocturne::cmb
