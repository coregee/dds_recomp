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
// The other half: the damage rate in percent (0x244078, no original name).
uint32_t affinityRate(const UnitWork& unit, Attribute attr);
bool canTalk(const UnitWork& unit);                        // datCheckTalk: no ailment that stops a negotiation
int32_t levelForDraw(const UnitWork& unit);               // datGetLevelForDraw: shown as at most 99
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
bool isPlayerDead();                                       // datCheckPlayerDead
void addMacca(int32_t amount);                             // datAddMaka: 0..9,999,999
bool hasMacca(int32_t amount);                             // datCheckMaka
void addMaccaPercent(int32_t percent);                     // datAddMakaPar: 0..9,999,999
// datInitPlayer: a new game's Demi-fiend alone in the stock, no Macca or items.
void initPlayer();
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
int32_t uniqueDevilId(int32_t uniqueId);                   // datGetUniqueDevilId: its devil ID, or -1
int32_t findDevil(int32_t devil);                          // datSearchDevilStock: unit index of a demon, or -1
bool isStockFull();                                        // datCheckStockFull
int32_t removeDevil(int32_t devil);                        // datDelDevil
void clearPartyCommandMemory();                            // datAllClearCommMemory

// ---- Items ----------------------------------------------------------------------

bool hasItem(int32_t item, int32_t count);                 // datCheckItem: at least `count` on hand
bool isItemFull(int32_t item);                             // datCheckItemFull: 99, or a key item held
// datAddItem: Magatama items join the collection; items below 0x70 stack
// to 0..99; key items set event 0x360 + ID (the Deathstone also counts).
void addItem(int32_t item, int32_t count);
int32_t receiveItem(uint16_t item, int32_t count);        // fclAddItem: the same, always returns 1
// datGetItemSkillNo: the skill an item uses; item 1 picks one of six at random.
int32_t itemSkill(int32_t item);   // datGetItemSkillNo [version]

// ---- Skills outside battle ----------------------------------------------------

// datSetAutoKaifukuSkill: Life/Mana Aid, Victory Cry, Life/Mana Refill.
void applyRecoverySkill(UnitWork& unit, uint16_t skill);
void recoverPartyWhileWalking();                           // datFieldSkillKaifuku: Life/Mana Refill
uint16_t luckyFindOwner();                                 // datCheckSkillTakaraSagasi: devil ID, 0 if none

// ---- Boss refights (the Labyrinth of Amala's Fiends and bosses) -------------------
// datBossPress_t: a refightable boss (table at 0x3FA430, 40 entries).
struct BossPress {
    int32_t flag;                // event bit: the refight is open
    int32_t flag2;               // event bit set by a new record
    int32_t encid;               // the encounter
    int32_t dbest;               // the record to beat (press turns)
};
#if !NOCTURNE_VANILLA   // (Maniax's refights)
void initBossPress();                                      // datInitBossPress: no records yet
// datBossRashGetRec: type 0 the best press turns (999 if none), 1 the last
// fight's (1 if none), 2 the record to beat; 0 if not a refight.
int32_t bossPressRecord(int32_t encounter, int32_t type);
void updateBossPressRecord(int32_t encounter, int32_t press);   // datBossRashUpdRec
#endif
bool isBossRefight(int32_t encounter);                     // datBossRashChk (Vanilla: none, false)

// ---- Reason (Kotowari) ----------------------------------------------------------

void addReasonPoints(int32_t reason, int32_t amount);      // datAddKotowariPoint: 0..128
int32_t reasonRank(int32_t rank);                          // datGetKotowariLank: the Reason in place `rank`

} // namespace nocturne::dat
