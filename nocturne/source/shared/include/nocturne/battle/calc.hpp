// Battle calculations: hit/critical/ailment rolls, rewards, first strike,
// ambush, escape and consecutive encounters.
//
// Original translation unit: nbCalc (the HD remaster keeps the same function
// list). Damage formulas from the same unit live in the legacy sources for now
// (battle_affinity.c, battle_action_formula_frames.c).
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/ee/float.hpp"

namespace nocturne::nb {

// ---- Hit resolution -------------------------------------------------------

enum class HitType : int32_t {
    Normal   = 0,
    Critical = 1,
    Weakness = 2,   // target is weak to the element (earns a half press turn)
};

// Result of nbGetKoukaType ("kouka" = 効果, effect).
enum class EffectResult : int32_t {
    Hit   = 0,
    Repel = 1,
    Drain = 2,
    Null  = 3,
    Miss  = 4,
    Fail  = 5,      // no effect / condition not met
    // 6..14: outcomes handled by special code elsewhere. Most come straight
    // from NormalSkill::program (see resolveEffect); 11 is a single-target
    // skill against a formation with stat 0x1000.
    Special6 = 6, Special7 = 7, Special8 = 8, Special9 = 9, Special10 = 10,
    Special11 = 11, Special12 = 12, Special13 = 13, Special14 = 14,
};

// Alignment class used by skill conditions (nbGet3Zokusei). Raw alignment
// -1/0/+1 maps to 0/1/2; which pole is "light" is not yet confirmed.
enum class AlignmentClass : int32_t { Minus = 0, Neutral = 1, Plus = 2 };

// What nbCheckBadKaifuku ("kaifuku" = 回復, recovery) is asked.
enum class AilmentCheck : int32_t {
    TurnEndRecovery = 0, // roll to shake off the ailment
    IsBound         = 1,
    IsAsleep        = 2,
    HasCurable      = 3,
};

HitType rollCritical(ActionProcessData& action, int32_t skill, int32_t source, int32_t target);   // nbGetHitType [version]
// [version] nbGetKoukaType: a physical (damageClass 0) or magic (1) skill's
// accuracy, before the 50..100 clamp.
ee::Float hitAccuracy(const NormalSkill& s, const UnitWork& attacker, const UnitWork& defender, ee::Float hitRate,
                      ee::Float accuracyBuff, ee::Float evasionBuff);
// [version] ... whether the target's affinity decides the outcome (Repel,
// Drain, Null), past Pierce.
bool affinityOutcome(int32_t skill, const NormalSkill& s, const UnitWork& attacker, Affinity affinity,
                     MainProcessData& data, EffectResult& outcome);
// The Demi-fiend's level, Agility and Luck, and the enemies' averages, for
// the first-strike and back-attack rolls.
struct InitiativeStats {
    int32_t playerLevel, playerAgility, playerLuck;
    int32_t enemyLevel, enemyAgility, enemyLuck;
};
// [version] nbCheckSensei: the player's chance (of 128) to keep the
// initiative, by the area's first-strike entry (coefficients: six, x1 ..);
// nbCheckBackAttack: a side's score (only printed).
int32_t firstStrikeChance(const InitiativeStats& s, uint8_t table, const ee::Float* coefficients);
int32_t initiativeScore(int32_t level, int32_t luck, int32_t agility);
// US Maniax's physical accuracy: 100 - failpoint and the agility scores.
int32_t agilityScore(const UnitWork& unit);
ee::Float physicalAccuracy(const NormalSkill& skill, const UnitWork& attacker, const UnitWork& defender);
AlignmentClass alignmentClass(int32_t formindex);                                                  // nbGet3Zokusei
bool meetsSkillCondition(int32_t skill, int32_t source, int32_t target);                          // nbCheckKoukaJyoken
EffectResult resolveEffect(int32_t skill, int32_t source, int32_t target);                         // nbGetKoukaType
bool rollStoneShatter(int32_t skill, int32_t target);                                              // nbCheckStoneDead
bool checkAilment(const UnitWork* unit, AilmentCheck check);                                       // nbCheckBadKaifuku
ee::Float criticalPower(int32_t source, ee::Float power);                                          // nbGetCriticalPow

// ---- Skill data queries ---------------------------------------------------

ee::Float hpDrainRate(int32_t skill);              // nbGetHpDrainRitu
ee::Float mpDrainRate(int32_t skill);              // nbGetMpDrainRitu
ee::Float reductionRate(int32_t skill);            // nbGetGensyoRitu
bool hasHitEffect(int32_t skill);                  // nbCheckHitEffect
int32_t deadType();                                // nbGetDeadType
bool isSingleTargetSkill(int32_t skill);           // nbCheckSingleTargetSkill

// ---- Unit state -----------------------------------------------------------

enum class Resource : int32_t { Hp = 0, Mp = 1 };
void addHpMp(int32_t formindex, Resource resource, int32_t amount);  // nbAddHpMp
void setAilment(int32_t formindex, bool set, uint32_t badstat);      // nbSetBadStat
bool isCursed(int32_t formindex);                                    // nbCheckBadCurse
bool sameSide(int32_t formindex1, int32_t formindex2);               // nbCheckFormationFriend
bool rollPanicAction(const UnitWork& unit);                          // nbCheckBadPanicAction
bool isPartyPetrified();                                             // nbCheckBadStatusGameOver
void updateHpModelScale(Formation& form);                            // nbSetHpScale
const UnitVisual& unitVisual(const UnitWork& unit);                  // (unnamed, 0x259A60)
// [version] The model a devil is drawn with (source/<version>/src/battle/calc.cpp).
int32_t visualModel(int32_t id);

// ---- Encounter flow -------------------------------------------------------

enum class Side : int32_t { Player = 0, Enemy = 1 };

void setEncounter(int32_t encno);                                    // (unnamed, 0x259658)
int32_t averageLevel(MainProcessData& data, Side side);              // nbGetLvAvg2
int32_t averageCombatLevel(MainProcessData& data, Side side);        // nbGetLvAvg: over the combatants
bool escapeAllowed(const MainProcessData& data);                     // nbGetEscapeSwitch
int32_t averageParam(MainProcessData& data, Side side, Param stat);  // nbGetParamAvg
int32_t averageEncounterParam(MainProcessData& data, Side side, Param stat); // nbGetParamAvg2
bool rollEnemiesFirst(MainProcessData& data);                        // nbCheckSensei
bool rollBackAttack(MainProcessData& data);                          // nbCheckBackAttack
bool rollEscape(MainProcessData& data);                              // nbCheckEscape
// [version] nbCheckEscape: the weight of attempts and of the stat ratio; the
// difficulty's say (false: escape fails).
int32_t escapeWeight();
bool escapeDifficulty(int32_t& chance, bool normal);
bool rollConsecutiveEncounter(MainProcessData& data);                // nbCheckRenzokuEncount

// ---- Rewards --------------------------------------------------------------

void addEncounterItem(MainProcessData& data);       // nbGetEncountTableItem
void addDefeatRewards(const UnitWork& defeated);    // nbGetExpMakaItem
int32_t scatteredMacca(const UnitWork& unit);       // nbGetMakaBaramaki
ee::Float maccaShareDivisor();   // [version] ... the party's Macca over this
int32_t earnedExp(const MainProcessData& data);     // nbGetKakutokuExp
int32_t earnedMacca(const MainProcessData& data);   // nbGetKakutokuMaka

} // namespace nocturne::nb
