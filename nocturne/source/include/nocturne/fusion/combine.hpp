// Making the fused devil: inherited skills, Mitama boosts, sacrifice EXP,
// and cmbGetBirthDevil, the whole fusion (original unit: fclCombineCalcCore).
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/fusion/rules.hpp"

namespace nocturne::cmb {

// fclKeisyoList_t: the skills a fused devil inherited, for the results screen.
struct InheritedSkillList {
    uint16_t skill[8];
    uint8_t count;
};
static_assert(offsetof(InheritedSkillList, count) == 0x10);

// ---- Mitama boosts ----------------------------------------------------------------

int8_t mitamaBoostIndex(uint16_t mitama);                         // cmbGetPowerUpTableIndex: -1 if none
// cmbCalcParamUpVal: the new Mitama bonus for a stat, rate% of the stat
// (at least +1), at most doubling it and keeping the total within `max`.
int32_t raisedMitamaBonus(int32_t stat, int32_t bonus, int32_t max, uint8_t rate);
bool applyMitamaBoost(uint16_t mitama, UnitWork& unit);           // cmbCalcParamPowerUp

// ---- Inherited skills ---------------------------------------------------------------

// cmbAddKeisyoSkillFromSkill: offer `from`'s skills to `to`'s inheritance
// list (those it can inherit and doesn't know).
void addInheritableSkills(UnitWork& to, const UnitWork& from);
void removeInherited(UnitWork& unit, uint8_t index);              // cmbDeleteKeisyoSkill: and re-sort
int8_t learnInherited(uint16_t skill, UnitWork& unit);            // cmbMoveKeisyoSkillToSkill
uint16_t randomInheritedSkill(const UnitWork& unit);              // cmbRndGetKeisyoSkill: weighted by rate
// cmbRndAddKeisyoSkillToSkill: learn (total source skills + 2.7) / 3.7 of
// the offered skills, at random, up to 8 skills in all.
void learnRandomInherited(const UnitWork& devil1, const UnitWork& devil2, const UnitWork* sacrifice,
                          UnitWork& result, InheritedSkillList* learned);

// ---- Fusion -------------------------------------------------------------------------

// cmbCalcIkenieExp: a sacrifice gives 1.5x its EXP, with the level-ups (and
// random stat gains) that brings.
void addSacrificeExp(UnitWork& result, const UnitWork& devil1, const UnitWork& devil2, const UnitWork& sacrifice);
void stockDevilInfo(const UnitWork& unit, uint16_t* id, uint8_t* race);   // cmbGetStockDevilInfo

// cmbGetBirthDevil: fuse two devils (and a sacrifice), writing the new devil
// to `result`. LevelMode chooses the units' levels over species levels;
// accidents are only possible when `accidents` is set.
FusionType fuse(const UnitWork& devil1, const UnitWork& devil2, const UnitWork* sacrifice, UnitWork* result,
                bool cursed, bool unitLevels, bool accidents, InheritedSkillList* learned);

} // namespace nocturne::cmb
