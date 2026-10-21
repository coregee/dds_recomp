// Battle ("nb" = new battle) process state, PS2 layout.
//
// These structures are only partly identified. Named fields are either
// confirmed by native code in the rewritten functions or, where marked
// "tentative", placed by the HD remaster's field order (nbMainProcessData_t
// etc.), which keeps declaration order but not offsets.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

// Formation indices: 0..3 are the player's active party, 4..13 the enemies.
inline constexpr int32_t kPlayerFormations = 4;
inline constexpr int32_t kFirstEnemyFormation = 4;
inline constexpr int32_t kFormationCount = 14;

struct Vec4 { ee::Float x, y, z, w; };

// nbFormation: a combatant's on-screen slot (model, position, effects).
struct Formation {
    Vec4 orgpos, orgrot, pos, rot, center;
    ee::Float r, h, cr;
    ee::Float scl;            // model scale; shrinks with HP (nbSetHpScale)
    ee::Float oneshotr, allshotr, movey, movez;
    int32_t type;
    uint32_t time;
    uint32_t stat;            // FormationStat bits
    uint32_t flag;
    uint32_t anime;
    uint32_t basic;           // dds3Basic_t*
    int32_t serial;
    uint32_t hunit;
    int16_t partyindex;
    int16_t formindex;
    uint8_t unknown_94[0xf0 - 0x94];
};
static_assert(sizeof(Formation) == 0xf0);
static_assert(offsetof(Formation, scl) == 0x5c);
static_assert(offsetof(Formation, stat) == 0x78);
static_assert(offsetof(Formation, formindex) == 0x92);

namespace FormationStat {
inline constexpr uint32_t Unknown1000 = 0x1000; // nbGetKoukaType result 11
inline constexpr uint32_t Unknown2000 = 0x2000; // makes crits near-certain on Hard
} // namespace FormationStat

// nbParty: per-combatant battle bookkeeping (buffs, affinities).
struct Party {
    int16_t flag;             // PartyFlag bits
    int16_t formindex;
    int16_t statindex;
    uint16_t partyindex;
    int16_t count[20];        // buff/debuff ("hojo") counters by type
    uint32_t aisyo[16];       // current packed affinity per Attribute
    uint16_t hojoskill[8];
};
static_assert(sizeof(Party) == 128);
static_assert(offsetof(Party, aisyo) == 0x30);

namespace PartyFlag {
inline constexpr uint16_t Active     = 0x001;
inline constexpr uint16_t EnemySide  = 0x002;
inline constexpr uint16_t Inactive   = 0x004; // tentative
inline constexpr uint16_t AlwaysCrit = 0x100; // tentative: forces critical hits
inline constexpr uint16_t EndureFired = 0x200; // Endure / Never Yield saved this unit
inline constexpr uint16_t EndureSpent = 0x400; // ... and cannot again this battle
} // namespace PartyFlag

// nbMainProcessData: the battle as a whole.
struct MainProcessData {
    Ptr32<Formation> form;    // [kFormationCount]
    Ptr32<UnitWork> enemyunit;   // tentative
    uint8_t unknown_08[8];
    Ptr32<Party> party;       // [kFormationCount]
    uint32_t unknown_14;
    int16_t playerpcnt;       // tentative
    int16_t enemypcnt;        // tentative: enemy combatant count
    int16_t activeunit;
    uint16_t unknown_1e;
    uint32_t sound, sound_mem;   // tentative
    // Where this encounter came from: encountPack(encpackno)
    //   .enctable[packno].ritu[packindex].encountid == encno
    int32_t encpackno;
    int32_t packno;
    int32_t packindex;
    int32_t encno;            // index into the Encount table
    int32_t formationtype;
    uint32_t actionstack;     // tentative
    int32_t actionstackp;     // tentative
    uint32_t endtype;         // how the battle ended (3 = escaped)
    int8_t order[12];         // tentative
    int8_t orderindex;
    uint8_t unknown_55;
    int16_t previndex;
    uint16_t prevcommand, prevcommind, prevflag, debug;
    uint32_t stat;            // BattleStat bits (legacy headers call this "flag")
    uint32_t flag;
    uint8_t turn;
    int8_t phase, nextphase;
    uint8_t esccnt;           // escape attempts so far; each one helps
    uint8_t unknown_6c[0x98 - 0x6c];
    uint8_t item[4];          // spoils so far
    uint8_t itemcnt[4];
    uint32_t maka;            // Macca earned
    uint32_t exp;             // EXP earned
    uint8_t unknown_a8[0x14c - 0xa8];
    int32_t piercedResistance;   // set when Pierce ignored Null/Drain (tentative name)
};
static_assert(offsetof(MainProcessData, party) == 0x10);
static_assert(offsetof(MainProcessData, encpackno) == 0x28);
static_assert(offsetof(MainProcessData, encno) == 0x34);
static_assert(offsetof(MainProcessData, endtype) == 0x44);
static_assert(offsetof(MainProcessData, orderindex) == 0x54);
static_assert(offsetof(MainProcessData, stat) == 0x60);
static_assert(offsetof(MainProcessData, esccnt) == 0x6b);
static_assert(offsetof(MainProcessData, item) == 0x98);
static_assert(offsetof(MainProcessData, exp) == 0xa4);
static_assert(offsetof(MainProcessData, piercedResistance) == 0x14c);

namespace BattleStat {
inline constexpr uint32_t BossBattle          = 0x00000001; // tentative: Stinger ("DANTE SUTING BOSS NG") and the Melody instant kills fail
inline constexpr uint32_t InitiativeRolled    = 0x00000008;
inline constexpr uint32_t BackAttack          = 0x00000010;
inline constexpr uint32_t EnemiesFirst        = 0x00000080;
inline constexpr uint32_t Unknown400          = 0x00000400;
inline constexpr uint32_t DebugAlwaysHit      = 0x08000000; // debug event bit 0xC07
inline constexpr uint32_t DebugAlwaysRepel    = 0x40000000; // debug event bit 0xC0D
} // namespace BattleStat

// nbActionProcessData: one unit's action in progress.
struct ActionProcessData {
    Ptr32<MainProcessData> data;
    uint8_t unknown_04[0x58 - 0x04];
    int32_t autoskill;        // passive that fired (e.g. Might); tentative name
};
static_assert(offsetof(ActionProcessData, autoskill) == 0x58);

} // namespace nocturne::nb
