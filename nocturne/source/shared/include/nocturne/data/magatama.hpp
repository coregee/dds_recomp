// Magatama ("hearts"): owning, equipping bonuses, their skills and mastery,
// and the Demi-fiend's "race" (original units: cmb, cmp, rst, dat).
//
// Magatama 1..25 (0 = none) are described by dat::magatama(id). Progress
// lives in GlobalWork: hearts_owned[] (in acquisition order),
// hearts_skill_state[id] (low nibble: skills learned; bit 7: mastered),
// hearts_learned_skills[id][] and hearts_param_upgrades[id][].
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"

namespace nocturne::magatama {

// ---- Ownership -------------------------------------------------------------------

bool owns(int8_t id);                                  // cmbChkGetHearts
bool hasMagatama(int8_t id);                           // cmpChkHaveHearts: the same, for menus
bool ownsAllNormal();                                  // cmpChkHaveNormalHeartsAll: 1..24 (not Masakados)
// datAddHearts: add to the collection (and teach its starting skills);
// false if already owned. Owning all normal Magatama sets event 0x860.
bool add(int32_t id);
int8_t fromItem(uint16_t item);                        // fclChkItemHearts: the Magatama an item gives, 0 if none

// ---- Stat bonuses ------------------------------------------------------------------

int8_t baseParam(int8_t id, int8_t stat, bool mastered);     // cmbGetHeartsDefaultParam
int8_t paramWithUpgrades(int8_t id, int8_t stat, bool mastered); // cmbGetHeartsParamEx
int8_t param(int8_t id, int8_t stat);                  // cmbGetHeartsParam: as currently mastered
void addParams(uint8_t id, UnitWork& unit);            // ps2HeartsAddParam (0x222408): equip
void removeParams(uint8_t id, UnitWork& unit);         // cmbSubHeartsParam: unequip
int16_t affinityRow(uint8_t id);                       // cmbGetHeartsAisyo: 0 for none
// cmbGetParamBase (rst): the Demi-fiend's stat without the equipped
// Magatama's bonus; a demon's effective stat.
int32_t paramWithoutMagatama(const UnitWork& unit, int32_t stat);

// ---- Skills and mastery --------------------------------------------------------------

int16_t skillCount(uint8_t id);                        // cmbGetHeartsSkillNums
uint16_t skillAt(uint8_t id, int8_t index);            // (0x222210)
int8_t learnedCount(uint8_t id);                       // cmbGetHeartsAfterSkillNums
void recordLearned(int8_t id, uint16_t skill);         // cmbAddHeartsSkill
int8_t learnStartingSkills(uint8_t id, UnitWork& unit);// cmbCreateDefaultHeartsSkill: returns skillcnt
// cmbChkGetHeartsSkill: the next skill the unit can learn from it now, 0 if none.
uint16_t nextSkill(uint8_t id, const UnitWork& unit);
// rstCreateBeforeSkillList: skills still to come, from a Magatama (the
// Demi-fiend) or the unit's growth table (demons).
void upcomingSkills(int8_t id, const UnitWork* unit, int8_t levelOffset, UpcomingSkills& list);
bool isMastered(uint8_t id);                           // cmbChkHeartsMaster
int8_t masteredCount();                                // cmbGetMasterHeartsNums
void setMastered(int8_t id);                           // cmbSetHeartsMaster

// ---- The Demi-fiend's race ------------------------------------------------------------

uint8_t statClass(int8_t id);                          // cmbChkHeartsStat: flag & 7
// cmbChkMasterHeartsStatNums: the dominant stat class among mastered
// Magatama (1 or 4, else 0) and a tier 0..5 from how many are mastered.
uint8_t masteredStatClass(uint8_t* tier);
// cmbGetPlayerRaceID: 0 with no tier, else 3 x (tier - 1) + 1, 2 or 3 for
// class 1, neither, or class 4.
uint8_t playerRace();

} // namespace nocturne::magatama
