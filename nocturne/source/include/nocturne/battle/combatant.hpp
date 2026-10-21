// Questions about one combatant, by formation index (original unit: nbCalc).
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/data/types.hpp"

namespace nocturne::nb {

uint32_t badStat(int32_t formindex);                     // nbGetBadStat: current ailment, 0 for an empty slot
Attribute skillAttribute(int32_t skill);                 // nbGetNormalSkillAttr: the skill's element
bool isPlayerSide(int32_t formindex);                    // nbCheckFormationPlayerSide
bool passiveActive(const UnitWork& unit, int32_t skill); // nbHatudoCheckSkill: owned, and its moon condition holds
uint32_t devilFormatFlag(int32_t formindex);             // nbGetDevilFormatFlag: DevilFormat::flag (0 for the Demi-fiend)
int32_t unitModelId(const UnitWork& unit);               // nbGetUnitID: model to draw (255 = Fly)

// Can the combatant use this skill now?
enum class SkillCheck : int32_t { Ok = 0, NotEnoughHp = 1, NotEnoughMp = 2, Muted = 3 };
SkillCheck checkSkillCost(int32_t formindex, int32_t skill);   // nbCheckSkillCost
// nbCheckSkillUse: the same answer, coded 0 ok, 1 muted, 2 HP, 3 MP.
int32_t checkSkillUse(int32_t formindex, int32_t skill);

// Endure / Never Yield: survive a fatal hit once per battle.
bool checkEndure(int32_t formindex);                     // nbCheckKuisibariSkill
bool checkNeverYield(int32_t formindex);                 // nbCheckKuisibari2Skill
void markEndureUsed(int32_t formindex);                  // nbSetKuisibariStop

} // namespace nocturne::nb
