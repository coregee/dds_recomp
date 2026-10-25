// Unit stats and state (original unit: datCalc).
//
// Everything about a single UnitWork that does not depend on the battle:
// stats with their bonuses, derived powers, max HP/MP, base affinity,
// skill ownership, ailments, HP/MP changes.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/data/types.hpp"

namespace nocturne::dat {

// [version]: defined by each version.

// ---- Stats -----------------------------------------------------------------

int32_t baseParam(const UnitWork& unit, Param stat);    // datGetBaseParam: base + skill + Mitama bonus, 1..40 [version]
int32_t param(const UnitWork& unit, Param stat);        // datGetParam: as above; Fly drops all but Agility to 1
int32_t attackPower(const UnitWork& unit);              // datGetNormalAtkPow: (St + Lv) * 2, halved by Poison
int32_t defensePower(const UnitWork& unit);             // datGetDefPow: (Vi + Lv) * 2
int32_t magicAccuracy(const UnitWork& unit);            // datGetMagicHitPow [version]
int32_t evasionPower(const UnitWork& unit);             // datGetSakePow [version]
int32_t baseMaxHp(const UnitWork& unit);                // datGetBaseMaxHp: (Lv + Vi) * 6
int32_t baseMaxMp(const UnitWork& unit);                // datGetBaseMaxMp: (Lv + Ma) * 3 [version]
uint32_t maxHp(const UnitWork& unit);                   // datGetMaxHp: with Life Bonus/Gain/Surge
uint32_t maxMp(const UnitWork& unit);                   // datGetMaxMp: with Mana Bonus/Gain/Surge
int32_t playerLevel();                                  // datGetPlayerLevel: the Demi-fiend's level
Race race(const UnitWork& unit);                        // datGetRace

// ---- Affinity and alignment -------------------------------------------------

// datGetAisyo: the unit's own affinity to an element, before battle effects.
uint32_t affinity(const UnitWork& unit, Attribute attr);
// datGet3Zokusei: -1, 0 or +1 from DevilFormat flags 0x80/0x40 (Demi-fiend: 0).
int32_t alignment(const UnitWork& unit);

// ---- Skills -----------------------------------------------------------------

bool hasSkill(const UnitWork& unit, int32_t skill);     // datCheckSyojiSkill
bool partyHasSkill(int32_t skill);                      // datCheckSkillInParty
int32_t skillCost(const UnitWork& unit, int32_t skill); // datGetSkillCost: HP or MP to pay [version]

// ---- Ailments and HP/MP -----------------------------------------------------

void setAilment(UnitWork& unit, uint32_t badstat);      // datSetBadStat: only if it outranks the current one
void clearAilment(UnitWork& unit, uint32_t badstat);    // datResetBadStat
void overwriteAilment(UnitWork& unit, uint32_t badstat);// datOverwriteBadStat
Attribute ailmentElement(uint32_t badstat);             // datGetBadStatusAttr: which element inflicts it
uint32_t addClamped(uint16_t& current, uint16_t maximum, int32_t amount);   // current + amount, kept in 0..maximum
uint32_t addHp(UnitWork& unit, int32_t amount);         // datAddHp: clamped to 0..maxhp, returns new HP [version]
uint32_t addMp(UnitWork& unit, int32_t amount);         // datAddMp
bool isDying(const UnitWork& unit);                     // datCheckDying: HP below 25%

} // namespace nocturne::dat
