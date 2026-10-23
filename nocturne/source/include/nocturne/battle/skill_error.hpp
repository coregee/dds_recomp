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

bool CheckDeadUnit();                                            // anyone in the stock dead
bool CheckDeadUnit2(UnitWork* const* list, int32_t cnt);         // any of them dead
bool CheckMaxHp(UnitWork* const* list, int32_t cnt);             // all at full HP
bool CheckMaxMp(UnitWork* const* list, int32_t cnt);             // all at full MP
bool CheckBad(UnitWork* const* list, int32_t cnt, uint32_t bad); // any with one of the ailments
bool CheckHojo(Party* const* list, int32_t cnt, uint32_t hojo);  // any buff counter the skill would move
void nbDispSkillErrorMessage(int32_t err);
int32_t nbCheckBattleSkillError1(int32_t nskill);
int32_t nbCheckBattleSkillError2(int32_t nskill, uint32_t select);   // select: formation slots
int32_t nbCheckBattleSkillError3(int32_t nskill, uint32_t select);
int32_t nbCheckCampSkillError(int32_t nskill, uint32_t select);      // select: stock units

} // namespace nocturne::nb
