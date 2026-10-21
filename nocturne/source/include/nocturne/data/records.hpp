// Game data records in their original PS2 layout.
//
// Field names follow the original developers' names as preserved by the
// Unity HD remaster (pc/il2cpp/dump.cs, e.g. datUnitWork_s). HD objects are
// managed classes with different offsets; the PS2 offsets asserted below come
// from native loads in SLUS_209.11. "unknown_XX" fields have no confirmed use.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/data/types.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/guest.hpp"

namespace nocturne {

// datUnitWork: one demon or the Demi-fiend, in the stock or in battle.
struct UnitWork {
    uint32_t flag;            // UnitFlag bits
    uint16_t id;              // devil ID (index into the DevilFormat table)
    uint16_t hp, maxhp;
    uint16_t mp, maxmp;
    uint16_t badstat;         // Ailment in the low 12 bits + flags (types.hpp)
    int32_t exp;
    uint16_t level;
    int8_t param[6];          // indexed by Param
    int8_t skillparam[6];
    uint16_t uniqueid;
    uint16_t reserve1, reserve2;
    uint8_t namecode[16];     // HD: char[] namecode (length tentative)
    uint16_t skillcnt;
    uint16_t skill[24];
    int16_t nowcommand;       // command chosen this turn
    uint16_t nowindex;        // its skill / item index
    int16_t nowtarea, nowtform;
    int16_t prevcommand;
    uint16_t previndex;
    int16_t prevtarea, prevtform;
    int8_t mitamaparam[6];    // stat bonuses from Mitama fusion
    int8_t levelupparam[6];
    uint16_t keisyoskill[24]; // inherited skills ("keisyo" = inheritance)
    uint8_t keiattr[24];
    uint16_t hensinmae;       // ID before transformation (evolution)
    uint16_t getdevilhearts[4];
    uint32_t hensinmaeexp;
    uint8_t fullnamecode[16];

    uint16_t ailment() const { return badstat & 0x0fff; }
    bool isEnemy() const { return (flag & 0x20) != 0; }
    bool isPlayerCharacter() const { return (flag & 0x04) != 0; }
};
static_assert(sizeof(UnitWork) == 0xec);
static_assert(offsetof(UnitWork, badstat) == 0x0e);
static_assert(offsetof(UnitWork, level) == 0x14);
static_assert(offsetof(UnitWork, param) == 0x16);
static_assert(offsetof(UnitWork, skillcnt) == 0x38);
static_assert(offsetof(UnitWork, nowcommand) == 0x6a);
static_assert(offsetof(UnitWork, mitamaparam) == 0x7a);
static_assert(offsetof(UnitWork, keisyoskill) == 0x86);
static_assert(offsetof(UnitWork, hensinmae) == 0xce);
static_assert(offsetof(UnitWork, hensinmaeexp) == 0xd8);

// datNormalSkill: how an active skill hits. Table at 0x3D7998, 60 bytes/entry.
struct NormalSkill {
    uint8_t flag;
    uint8_t use;
    uint8_t koukatype;        // 0 = physical, 1 = magic, other = neither (no hit roll)
    uint8_t costtype;
    uint16_t cost, costbase;
    uint8_t targettype;       // 0 = single target
    uint8_t targetarea, targetrule, targetrandom;
    uint16_t untargetbadstat, targetprog;
    uint8_t hittype;          // alignment condition mask, see nbCheckKoukaJyoken
    uint8_t hitlevel;         // base accuracy in percent; 255 = never misses
    uint16_t hitprog;
    uint8_t targetcntmin, targetcntmax;
    uint16_t hptype;          // 12/13 = HP drain
    int16_t hpn;
    uint16_t mptype;          // 12/13 = MP drain
    int16_t mpn;
    int16_t hpbase, mpbase;
    uint16_t minus;           // percentage reduction ("gensyo")
    uint8_t badtype, badlevel;
    uint16_t badstatus;       // ailment inflicted (e.g. Mudo: Dead, Lullaby: Sleep)
    uint32_t hojotype;        // buff/debuff ("hojo") kinds applied
    int8_t hojopoint;
    uint8_t deadtype;
    uint8_t unknown_2e[2];
    uint32_t program;         // special-behaviour selector, see nbGetKoukaType
    int16_t criticalpoint;    // base critical chance
    int16_t failpoint;        // accuracy penalty
    int16_t magicbase, magiclimit;
};
static_assert(sizeof(NormalSkill) == 60);
static_assert(offsetof(NormalSkill, hittype) == 0x10);
static_assert(offsetof(NormalSkill, hptype) == 0x16);
static_assert(offsetof(NormalSkill, minus) == 0x22);
static_assert(offsetof(NormalSkill, hojotype) == 0x28);
static_assert(offsetof(NormalSkill, program) == 0x30);
static_assert(offsetof(NormalSkill, criticalpoint) == 0x34);

// datSkill: what every skill ID is. Table at 0x3D6998, 8 bytes, 512 entries.
struct SkillInfo {
    int8_t skillattr;         // element (Attribute); -1 none
    int8_t type;              // 0 active (has a NormalSkill), 1 passive, -1 unused
    int16_t index;
    uint16_t keisyoform;      // which demons can inherit it (mask)
    int8_t capacity;
    uint8_t flag;
};
static_assert(sizeof(SkillInfo) == 8);

// datSpecialSkill: tuning numbers for passive/auto skills. Table at 0x3DC1E0,
// indexed by (skill - 0x128). E.g. Fast Retreat n=150, Might n=300,
// Mind's Eye n=3, Anti-<element> n=50.
struct SpecialSkill {
    int16_t n, m, a, b;
};
static_assert(sizeof(SpecialSkill) == 8);

// datDevilFormat: species data for each devil ID. Table at 0x3497C0, 60 bytes.
struct DevilFormat {
    uint32_t flag;
    Race race;
    uint8_t level;
    uint16_t hp, maxhp, mp, maxmp;
    int16_t aisyoid;          // row in the affinity table; doubles as a model/species ID
    int8_t param[6];
    uint16_t skill[8];
    int16_t keisyotype;
    uint16_t keisyoform;
    uint16_t dropmakka;       // Macca reward
    uint16_t dropexp;         // EXP reward
    uint8_t dropitem[2];      // ordinary drops ...
    uint8_t droppoint[2];     // ... and their chances in percent
    uint16_t specialbit;      // event bit gating specialitem (0 = always)
    uint8_t specialitem, specialpoint;
    uint8_t hougyokupoint;    // chance to drop a Bead
    uint8_t masekipoint;      // chance to drop a Life Stone
    int8_t attackattr;
    uint8_t attackcnt, attackinterval, reserve1;
};
static_assert(sizeof(DevilFormat) == 60);
static_assert(offsetof(DevilFormat, param) == 0x10);
static_assert(offsetof(DevilFormat, dropmakka) == 0x2a);
static_assert(offsetof(DevilFormat, specialbit) == 0x32);

// datEncount: one enemy group. Table at 0x3AEFE0, 38 bytes/entry.
struct Encount {
    int8_t backattack;        // -1 never ambushes, 1 always, otherwise rolled
    int8_t esc;
    uint8_t item, itemcnt;    // guaranteed item reward
    uint8_t formationtype;
    uint8_t unknown_05;
    uint16_t devil[11];       // devil IDs, 0 = empty
    uint16_t stageid, areaid;
    uint16_t flag;            // EncountFlag bits
    uint8_t maxparty, maxcall;
    uint16_t btlsound;
};
static_assert(sizeof(Encount) == 38);
static_assert(offsetof(Encount, devil) == 6);
static_assert(offsetof(Encount, flag) == 0x20);

namespace EncountFlag {
inline constexpr uint16_t EnemiesAlwaysFirst = 0x02; // nbCheckSensei
inline constexpr uint16_t PlayerAlwaysFirst  = 0x04;
inline constexpr uint16_t ForcedFollowUp    = 0x10; // nbCheckRenzokuEncount
inline constexpr uint16_t AlwaysEscapable   = 0x20;
} // namespace EncountFlag

// datEncountRitu: one weighted entry of an area's random-encounter table.
struct EncountRitu {
    uint16_t encountid;
    uint16_t ritu;            // selection weight
    uint8_t sensei;           // first-strike coefficient index, see nbCheckSensei
    uint8_t renzokuritu;      // chance (%) of a consecutive encounter
    uint16_t renzokuindex;    // which entry follows
};
static_assert(sizeof(EncountRitu) == 8);

struct EncountTbl {
    int32_t normalritu;
    EncountRitu ritu[12];
};
static_assert(sizeof(EncountTbl) == 100);

// datEncountPack: an area's encounter tables. Table at 0x3BADE0, 420 bytes.
struct EncountPack {
    uint16_t stageid, areaid, btlsound, moonchk, table2, eventbit1, eventbit2;
    uint8_t table1[6];
    EncountTbl enctable[4];
};
static_assert(sizeof(EncountPack) == 420);

// Per-devil model record (0x310 bytes; table at 0x34F1E0, fallback record at
// 0x3494B0). Only the battle model scale is identified so far.
struct UnitVisual {
    uint8_t unknown_00[0x18];
    ee::Float scale;
    uint8_t unknown_1c[0x310 - 0x1c];
};
static_assert(sizeof(UnitVisual) == 0x310);

// datGlobalWork: the save-game state. Partial: only fields used so far.
struct GlobalWork {
    uint8_t unknown_0000[0x840];
    uint32_t event_bits[128];
    uint8_t moon_flags, moon_phase;
    uint8_t unknown_0a42[2];
    uint32_t moon_move_bits;
    int32_t maka;             // Macca on hand
    uint32_t unknown_0a4c;    // bit 1 quintuples consecutive-encounter odds (role unknown)
    int32_t stock_capacity;
    UnitWork units[16];       // units[0] is the Demi-fiend
};
static_assert(offsetof(GlobalWork, maka) == 0xa48);
static_assert(offsetof(GlobalWork, units) == 0xa54);

} // namespace nocturne
