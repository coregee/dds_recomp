// Whether a skill would do anything (original unit: nbSkillError): before a
// skill is used, in battle or from the menu, the game refuses one that can't
// change its targets. The checks return an error number (0: fine): 1 no
// effect, 2 no one to revive, 3 / 4 buffs that can't move.
//
// Names are the HD remaster's.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

bool anyStockDead();                                             // anyone in the stock dead
bool anyDead(UnitWork* const* list, int32_t cnt);                // any of them dead
bool allFullHp(UnitWork* const* list, int32_t cnt);              // all at full HP
bool allFullMp(UnitWork* const* list, int32_t cnt);              // all at full MP
bool anyHasAilment(UnitWork* const* list, int32_t cnt, uint32_t bad); // any with one of the ailments
bool anyBuffMovable(Party* const* list, int32_t cnt, uint32_t hojo); // any buff counter the skill would move
void showSkillError(int32_t err);
int32_t reviveError(int32_t nskill);
int32_t targetSkillError(int32_t nskill, uint32_t select);           // select: formation slots
int32_t buffSkillError(int32_t nskill, uint32_t select);
// [version] More skills checked as buffs (source/<version>/src/battle/skill_error.cpp).
bool versionBuffSkill(int32_t nskill);
int32_t menuSkillError(int32_t nskill, uint32_t select);             // select: stock units

} // namespace nocturne::nb
