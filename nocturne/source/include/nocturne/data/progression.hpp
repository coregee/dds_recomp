// The save game's party and the Demi-fiend's progress: adding and losing
// demons, Magatama, Reason points, recovery skills (original unit: datCalc).
//
// All of these work on GlobalWork (dat::globalWork()): units[0] is the
// Demi-fiend, units[1..3] are reserved, demons live in units[4..].
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/data/types.hpp"

namespace nocturne::dat {

// ---- One unit -----------------------------------------------------------------

// cmpSetMaxHPMP: recompute max HP/MP and keep current HP/MP in proportion.
void rescaleHpMp(UnitWork& unit);
// datGetAisyoFlag: only the Null/Repel/Drain/Weak bits of the unit's affinity.
uint32_t affinityFlags(const UnitWork& unit, Attribute attr);
void addExp(UnitWork& unit, int32_t exp);                 // datAddExp
void clearCommandMemory(UnitWork& unit);                   // datClearCommMemory: forget last turn's command
// datSetDevilWork: a fresh demon of the species, as when it joins.
void initDevil(uint16_t devil, UnitWork& unit);
// datCopyDevilWork (0x245D30): reset to the species' level, stats and
// skills, with the matching EXP; registers it in the compendium.
void resetToSpecies(uint16_t devil, UnitWork& unit);

// ---- The Demi-fiend -----------------------------------------------------------

int32_t playerParam(Param stat);                           // datGetPlayerParam: without the Magatama's bonus
void addPlayerParam(Param stat, int32_t amount);           // datAddPlayerParam: capped at 40, refills HP/MP
int32_t playerAlignment();                                 // datGetPlayerLND: 0..2, 1 (neutral) for no race
void addMaccaPercent(int32_t percent);                     // datAddMakaPar: 0..9,999,999
void removeMagatama();                                     // datRemoveHearts
void equipMagatama(uint8_t id);                            // datEquipHearts

// ---- The party and stock ------------------------------------------------------

int32_t companionParam(uint16_t devil, Param stat);        // datGetNakamaParam
void killCompanion(uint16_t devil);                        // datDeadNakama: and leaves the party
// datAddDevil: into the first free stock slot; returns the unit index or -1
// if full. A negative `devil` (bit 31) skips the compendium.
int32_t addDevil(int32_t devil, bool joinParty);
void addUniqueDevil(int32_t devil, bool joinParty, int32_t uniqueId);   // datAddUniqueDevil
int32_t findUniqueDevil(int32_t uniqueId);                 // datSearchUniqueDevilStock: unit index or -1
void clearPartyCommandMemory();                            // datAllClearCommMemory

// ---- Items ----------------------------------------------------------------------

bool hasItem(int32_t item, int32_t count);                 // datCheckItem: at least `count` on hand

// ---- Skills outside battle ----------------------------------------------------

// datSetAutoKaifukuSkill: Life/Mana Aid, Victory Cry, Life/Mana Refill.
void applyRecoverySkill(UnitWork& unit, uint16_t skill);
void recoverPartyWhileWalking();                           // datFieldSkillKaifuku: Life/Mana Refill
uint16_t luckyFindOwner();                                 // datCheckSkillTakaraSagasi: devil ID, 0 if none

// ---- Reason (Kotowari) ----------------------------------------------------------

void addReasonPoints(int32_t reason, int32_t amount);      // datAddKotowariPoint: 0..128
int32_t reasonRank(int32_t rank);                          // datGetKotowariLank: the Reason in place `rank`

} // namespace nocturne::dat
