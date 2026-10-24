// Which combatants an action can target (original unit: nbCalc / nbTarSel).
//
// An action has a target type (0 one, 1 a group, 2 everyone), a rule (bit 0
// self only, bit 1 not self, bit 2 empty summon slots allowed, bit 3 empty
// slots only) and an area (bit 0 the actor's side, bit 1 the other side,
// swapped when `reverse` or a back attack flips sides).
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbGetItemSkillNo: the skill an item uses in battle (item 1 uses the
// skill already rolled for this action).
int32_t itemSkillFor(const ActionProcessData& act, int32_t item);
// nbGetTargetTypeRuleArea: for the unit's chosen command.
void targetTypeRuleArea(const ActionProcessData& act, const UnitWork& unit, int32_t* type, int32_t* rule,
                        int32_t* area, bool reverse);

TargetCursor& targetSelectData();                                  // GetTarSelProcessData
// CheckFormCursor: can the unit in party slot `self` target formation slot `target`.
bool canTarget(int32_t self, int32_t type, int32_t rule, int32_t area, int32_t target);
// nbSetSelectOkMark: mark every targetable slot (FormationStat::Selectable),
// list them per side, and sort the other side by screen position. Returns
// whether anything can be targeted.
bool markTargetable(int32_t partyIndex, int32_t type, int32_t rule, int32_t area);

} // namespace nocturne::nb
