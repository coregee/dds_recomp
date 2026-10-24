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

// A unit's death in the devil AI table (DevilAI::deadscriptid / deadeventno):
bool diesByEvent(const Formation& form);                // it runs a script or starts an event
int32_t hasDeathScript(const Formation& form);           // the script to run, or 0
int32_t hasDeathEvent(const Formation& form);            // the event to start, or 0

// The stock and the enemies' units (nbMisc).
bool recruitDevil(const UnitWork& s);                    // a devil talked into joining enters the stock
void setDevilNameVariable(int32_t hmsg, int32_t no, const UnitWork& work);   // {var no}: its name ({var 0} "nobody" for id 0)
int32_t addEnemyUnit(MainProcessData& data, int32_t id);             // a called enemy's unit: its index, or -1
int32_t randomSummonableStock();                          // a random devil in the stock that can be summoned, or -1
void forgetChainTargets();
int32_t motionEndType(const Formation& form, int32_t motion);        // Formation::motionend
int32_t motionEndData(const Formation& form, int32_t motion);                            // forget the party's last targets on the other side

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
