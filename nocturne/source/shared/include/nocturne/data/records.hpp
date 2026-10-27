// Game data records in their original PS2 layout.
//
// Field names follow the original developers' names as preserved by the
// Unity HD remaster (pc/il2cpp/dump.cs, e.g. datUnitWork_s). HD objects are
// managed classes with different offsets; the PS2 offsets asserted below come
// from native loads in SLUS_209.11. "unknown_XX" fields have no confirmed use.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "nocturne/data/types.hpp"
#include "nocturne/build.hpp"
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
    uint16_t inheritedSkills[24]; // inherited skills ("keisyo" = inheritance) (HD: keisyoskill)
    uint8_t keiattr[24];
    uint16_t preEvolutionId;  // ID before transformation (evolution) (HD: hensinmae)
    uint16_t getdevilhearts[4];
    uint32_t preEvolutionExp;   // (HD: hensinmaeexp)
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
static_assert(offsetof(UnitWork, inheritedSkills) == 0x86);
static_assert(offsetof(UnitWork, preEvolutionId) == 0xce);
static_assert(offsetof(UnitWork, preEvolutionExp) == 0xd8);

// datNormalSkill: how an active skill hits. Table at 0x3D7998, 60 bytes/entry.
struct NormalSkill {
    uint8_t flag;
    uint8_t use;
    uint8_t damageClass;      // 0 = physical, 1 = magic, other = neither (no hit roll) (HD: koukatype)
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
    uint32_t buffKinds;        // buff/debuff ("hojo") kinds applied (HD: hojotype)
    int8_t buffAmount;   // (HD: hojopoint)
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
static_assert(offsetof(NormalSkill, buffKinds) == 0x28);
static_assert(offsetof(NormalSkill, program) == 0x30);
static_assert(offsetof(NormalSkill, criticalpoint) == 0x34);

// datSkill: what every skill ID is. Table at 0x3D6998, 8 bytes, 512 entries.
struct SkillInfo {
    int8_t skillattr;         // element (Attribute); -1 none
    int8_t type;              // 0 active (has a NormalSkill), 1 passive, -1 unused
    int16_t index;
    uint16_t inheritMask;     // which demons can inherit it (mask) (HD: keisyoform)
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

// datDevilNegoFormat_s: how a devil talks (table at 0x3DCB38, 48 bytes per
// devil). Only the talk-starting types are used by the rewrite so far.
struct TalkGift {              // datNegoPresent_s
    uint8_t weight, item;   // (HD: ritu)
};
struct DevilTalkFormat {
    uint32_t speechStyle, speechTrait;   // (HD: kucyo, tokucyo)
    uint8_t tokuboutype, honboutype, fighttype, reqtype, tuikareqtype;
    uint8_t privatesel, privateselindex;
    uint8_t ambushTalk;        // nonzero: it may open an ambush with talk (CheckSenseiNego) (HD: senseitype)
    uint8_t begForLife;        // ... beg for its life (CheckInotiNego) (HD: inotitype)
    uint8_t askToJoin;         // ... ask to join (CheckBinjoNego) (HD: binjotype)
    uint16_t lastEnemyTalk;    // ... speak up as the last one able to (CheckMukanNego) (HD: mukantype)
    uint16_t lastEnemyTalkIndex;   // (HD: mukanindex)
    TalkGift itemA[4], itemB[4], stones[4];   // what it gives in talks (nbGetNegoYaruItemA, B, Stone)
    uint8_t unknown_2e[2];
};
static_assert(sizeof(DevilTalkFormat) == 0x30 && offsetof(DevilTalkFormat, lastEnemyTalk) == 0x12);

// datDevilFormat: species data for each devil ID. Table at 0x3497C0, 60 bytes.
struct DevilFormat {
    uint32_t flag;
    Race race;
    uint8_t level;
    uint16_t hp, maxhp, mp, maxmp;
    int16_t affinityId;       // row in the affinity table; doubles as a model/species ID (HD: aisyoid)
    int8_t param[6];
    uint16_t skill[8];
    int16_t inheritType;   // (HD: keisyotype)
    uint16_t inheritMask;   // (HD: keisyoform)
    uint16_t dropmakka;       // Macca reward
    uint16_t dropexp;         // EXP reward
    uint8_t dropitem[2];      // ordinary drops ...
    uint8_t droppoint[2];     // ... and their chances in percent
    uint16_t specialbit;      // event bit gating specialitem (0 = always)
    uint8_t specialitem, specialpoint;
    uint8_t beadDropChance;   // chance to drop a Bead (HD: hougyokupoint)
    uint8_t lifeStoneDropChance; // chance to drop a Life Stone (HD: masekipoint)
    int8_t attackattr;
    uint8_t attackcnt, attackinterval, reserve1;
};
static_assert(sizeof(DevilFormat) == 60);

// DevilFormat::flag bits.
namespace DevilFlag {
inline constexpr uint32_t TwoPressTurns  = 0x010; // two press turn icons a turn (nbSetPressMaePhase)
inline constexpr uint32_t AlignmentPlus  = 0x040; // datGet3Zokusei +1
inline constexpr uint32_t AlignmentMinus = 0x080; // datGet3Zokusei -1
inline constexpr uint32_t NoHpCost       = 0x200; // HP-cost skills are free
inline constexpr uint32_t NoMpCost       = 0x400; // MP-cost skills are free
inline constexpr uint32_t MissIsFail     = 0x800; // a missed skill reports "no effect"
} // namespace DevilFlag
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
inline constexpr uint16_t Boss               = 0x01; // sets BattleStat::BossBattle (SetBattleFlag)
inline constexpr uint16_t EnemiesAlwaysFirst = 0x02; // nbCheckSensei
inline constexpr uint16_t PlayerAlwaysFirst  = 0x04;
inline constexpr uint16_t ForcedFollowUp    = 0x10; // nbCheckRenzokuEncount
inline constexpr uint16_t AlwaysEscapable   = 0x20;
inline constexpr uint16_t Unknown8          = 0x08; // sets BattleStat::Unknown800 (SetFlag)
} // namespace EncountFlag

// datEncountRitu: one weighted entry of an area's random-encounter table.
struct EncounterEntry {
    uint16_t encountid;
    uint16_t weight;          // selection weight (HD: ritu)
    uint8_t firstStrike;      // first-strike coefficient index, see nbCheckSensei (HD: sensei)
    uint8_t chainChance;      // chance (%) of a consecutive encounter (HD: renzokuritu)
    uint16_t chainEntry;      // which entry follows (HD: renzokuindex)
};
static_assert(sizeof(EncounterEntry) == 8);

struct EncountTbl {
    int32_t normalWeight;   // (HD: normalritu)
    EncounterEntry entries[12];   // (HD: ritu)
};
static_assert(sizeof(EncountTbl) == 100);

// datEncountPack: an area's encounter tables. Table at 0x3BADE0, 420 bytes.
struct EncountPack {
    uint16_t stageid, areaid, btlsound, moonchk, table2, eventbit1, eventbit2;
    uint8_t table1[6];
    EncountTbl enctable[4];
};
static_assert(sizeof(EncountPack) == 420);

// fclSkill: how a devil grows. Table at 0x333CF8, 102 bytes, per devil ID.
struct GrowthEvent {
    int8_t targetlevel;       // level at which it happens
    uint8_t type;             // GrowthEventType
    uint16_t param;           // skill ID for Skill; evolution target etc.
};
namespace GrowthEventType {
inline constexpr uint8_t None         = 0;
inline constexpr uint8_t Skill        = 1;   // learn skill `param` at targetlevel
inline constexpr uint8_t Evolve       = 5;   // evolves into devil `param` at targetlevel
inline constexpr uint8_t EvolveNotice = 7;   // the "can evolve" notice
// 2..4, 6, 8..10 also occur; their meaning is not yet established.
} // namespace GrowthEventType
struct DevilGrowth {
    int8_t growparam[6];      // weights for level-up stat increases (by Param)
    GrowthEvent event[24];
};
static_assert(sizeof(DevilGrowth) == 102);

// The items: 160 (the first release's 128).
inline constexpr int32_t kItemCount = kBuild.vanilla ? 0x80 : 0xa0;

// datItem: table at 0x3DC4A0, 8 bytes, one per item (item ID).
struct ItemData {
    uint8_t use;
    uint8_t flag;
    uint16_t skillid;         // skill the item casts (Bead: Diarahan)
    uint32_t price;
};
static_assert(sizeof(ItemData) == 8);

// fclHearts: Magatama. Table at 0x339E00, 66 bytes, 26 entries (0 = none).
struct MagatamaSkill {        // fclHeartsSkill_t
    uint8_t targetlevel;
    uint8_t unknown_01;
    uint16_t id;              // skill taught
};
struct MagatamaData {         // fclHearts_t
    uint8_t flag;             // low 3 bits: the Magatama's stat class
    uint8_t unknown_01;
    int16_t affinityId;       // affinity row while equipped (HD: aisyoid)
    int16_t masteredAffinityId; // ... once mastered (HD: masteraisyoid)
    int8_t growparam[6];      // stat bonuses while equipped (by Param)
    int8_t mastergrowparam[6];
    int8_t autoasignparam[6]; // Demi-fiend level-up stat weights
    uint8_t splitlevel;       // fclHeartsSplt_t
    uint8_t splitid;
    MagatamaSkill skill[8];
    uint8_t event[8];
};
static_assert(sizeof(MagatamaData) == 66);
static_assert(offsetof(MagatamaData, autoasignparam) == 0x12);
static_assert(offsetof(MagatamaData, skill) == 0x1a);

// ---- Evolution and skill inheritance ----------------------------------------

struct EvolutionRequirement {     // evolution needs this event bit set
    uint16_t devil;
    uint16_t eventbit;
};
struct InheritanceLevel {         // fclKeisyoSkillLevel_t: skill "level" divisor
    uint16_t skill;
    uint8_t level;
    uint8_t unknown_03;
    uint16_t skillId() const { return skill; }
};
struct InheritanceScoreRow {
    int16_t inheritType;          // DevilFormat::keisyotype (HD: keisyotype)
    uint16_t score[16];           // low byte: base rate for each element column
};
struct InheritanceScores {        // how well each kind of devil inherits each element
    int16_t unknown_00;
    int16_t attribute[16];        // column keys: SkillInfo::skillattr
    InheritanceScoreRow row[12];
};
struct SkillPowerUp {             // a skill and its stronger version
    uint16_t skill;
    uint16_t target;
};
static_assert(sizeof(InheritanceScores) == 442);

// ---- Fusion tables (fclCombineTable) ----------------------------------------

struct FusionPair {           // fclCombCom_t: two devils -> a result
    uint16_t devil1, devil2, birth;
};
struct RankShift {            // fclRankBase_t
    uint8_t race;
    uint8_t flag;             // 1 one rank up the race, 2 one rank down, 0 no result
};
struct SpiritRankTable {      // fclRankTbl_t: what a Spirit does to each race
    uint16_t devil;
    RankShift base[32];
};
struct SpiritParamUp {        // fclCombSpirit_t: a Mitama's stat boost
    uint16_t devil;
    uint16_t paramtype[2];    // Param raised
    uint8_t uprate;
    uint8_t unknown_07;
};
struct SacrificeRacePattern {     // fclIkenieExtPattern_t
    uint8_t race1, race2, race3, birthrace;
};
struct SacrificeDevilPattern {    // fclIkenieExtPatternDev_t
    uint16_t devil1, devil2, devil3, birth;
};
struct SacrificeResultPattern {   // fclIkenieExtPatternDev2_t: normal result + sacrifice -> birth
    uint16_t devil1, devil2, birth;
};
struct SacrificeDevilRacePattern { // fclIkenieExtPatternDevRace_t
    uint16_t devil;
    uint8_t race1, race2;
    uint16_t birth;
};
struct EventDevil {           // fclEventDevil_t: not fusible until the event bit is set
    uint16_t devil;
    uint16_t unknown_02;
    uint32_t eventflag;
};
struct MoonRange {            // fclCombineManinKagTbl entry: Kagutsuchi phases
    uint8_t min, max;
};
static_assert(sizeof(SpiritRankTable) == 66);
static_assert(sizeof(SpiritParamUp) == 8);
static_assert(sizeof(SacrificeDevilRacePattern) == 6);
static_assert(sizeof(EventDevil) == 8);

// Per-devil model record (0x310 bytes; table at 0x34F1E0, fallback record at
// 0x3494B0). Only the battle model scale is identified so far.
// A motion of a unit's model (0x1C bytes; the field names are tentative).
struct UnitMotion {
    uint8_t unknown_00[0x10];
    int16_t targeting;        // the target packet's kind for this motion (nbMakeTargetPacket)
    uint8_t unknown_12[3];
    int8_t sound;             // its piece in the unit's motion banks (-1 none; nbGetMotionSeNo)
    uint8_t endtype;          // how it ends (Formation::motionend)
    int8_t enddata;
    ee::Float speed;
};
static_assert(sizeof(UnitMotion) == 0x1c);

struct UnitVisual {
    ee::Float center[4];      // the box the camera targets the unit by: its centre (Formation::center)
    ee::Float size;           // ... its radius (with scale: a called ally's slot radius)
    ee::Float height;
    ee::Float scale;
    // Motion 0 is none: its first bytes hold the rest of the unit's set-up
    // (nbAddUnitStock), read through the accessors below.
    UnitMotion motion[27];

    ee::Float oneShotRadius() const { return fieldAt<ee::Float>(0x1c); }   // (Formation::oneshotr)
    ee::Float allShotRadius() const { return fieldAt<ee::Float>(0x20); }   // (Formation::allshotr)
    uint16_t setupFlag() const { return fieldAt<uint16_t>(0x2a); }         // 1: FormationStat 0x80 (tentative)

private:
    template <class T> T fieldAt(size_t offset) const
    {
        T value;
        std::memcpy(&value, reinterpret_cast<const uint8_t*>(this) + offset, sizeof value);
        return value;
    }
};
static_assert(sizeof(UnitVisual) == 0x310);

// datDevilAI_t: how an enemy devil chooses its actions (battle/ai.hpp).
struct AiCheck {               // datDevilAIChk_s
    uint32_t check[2];         // conditions, (type << 16) | parameter; 0 = always
    uint32_t table;            // the action table to use when both hold
};
struct AiAction {              // datDevilAITbl_s
    uint16_t weight;           // weight (HD: ritu)
    uint16_t skill;            // a skill, or a 0x8xxx command (attack, escape ...)
    uint32_t target;           // (selector << 16) | parameter
};
struct DevilAI {
    uint16_t scriptid;         // AI script, or 0 for the table AI
    uint16_t ailevel;          // target choice: 0 any, 1 best effect, 2 ... skipping immunities
    AiCheck aichk[3];          // tried in order; none holding means table 0
    AiAction aitable[3][5];
    uint16_t deadscriptid;
    uint16_t deadeventno;
};
static_assert(sizeof(AiAction) == 8);
static_assert(sizeof(DevilAI) == 164);
static_assert(offsetof(DevilAI, aitable) == 0x28);

// fclencyceelem_t: a compendium entry, a snapshot of a demon (0xB0 bytes).
struct EncycRecord {
    uint16_t id;
    uint16_t reserved0;
    uint16_t maxhp, maxmp;
    int32_t exp;
    uint16_t level;
    int8_t param[6];
    int8_t skillparam[6];
    uint16_t skillcnt;
    uint16_t skill[24];
    int8_t mitamaparam[6];
    int8_t levelupparam[6];
    uint16_t inheritedSkills[24];   // (HD: keisyoskill)
    uint8_t keiattr[24];
    uint16_t preEvolutionId;   // (HD: hensinmae)
    uint16_t reserved1;
    uint32_t flag;            // the unit's flags 0x40 | 0x200 only
    uint32_t reserved2;
    uint32_t preEvolutionExp;   // (HD: hensinmaeexp)
};
static_assert(sizeof(EncycRecord) == 0xb0);
static_assert(offsetof(EncycRecord, flag) == 0xa4);

// rstSkillInfo_t: skills a unit will learn later (results / Magatama menus).
struct UpcomingSkills {
    int8_t skillcnt;
    uint8_t targetlevel[24];
    uint8_t unknown_19;
    uint16_t skill[24];
};
static_assert(sizeof(UpcomingSkills) == 0x4a);

// datGlobalWork: the save-game state. Partial: only fields used so far.
// The JP builds' global work is 4 bytes shorter before the script
// variables, so every field after sits 4 lower; the block before the options
// (the entered names' bitmaps among it) is shorter still: from the options
// on, fields sit 0x2450 lower. The offsets below are the US release's.
inline constexpr std::size_t kGlobalWorkShift = kBuild.us ? 0 : 4;
inline constexpr std::size_t kGlobalWorkTailShift = kBuild.us ? 0 : 0x2450;

struct GlobalWork {
    uint8_t unknown_0000[0x40 - kGlobalWorkShift];
    int32_t script_ints[256];       // the script VM's global variables (scrInitGlobalWork)
    uint32_t script_floats[256];    // ... as float bits
    uint32_t event_bits[128];
    uint8_t moon_flags, moon_phase;
    uint8_t unknown_0a42[2];
    uint32_t moon_move_bits;
    int32_t macca;            // Macca on hand (HD: maka)
    uint32_t fieldskills;     // field skills in effect: Estoma 1, Riberama 2 (quintuples consecutive-encounter odds), Liftoma 4, Lightoma 8
    int32_t stock_capacity;   // how many demons the stock can hold
    UnitWork units[16];       // units[0] the Demi-fiend, 1..3 reserved, 4.. demons
    uint8_t stock_list[16];   // display order of the stock (unit indexes)
    int32_t stock_count;
    uint8_t item_counts[0xa0];   // (the first release counts its 0x80 items here; the rest is other data)
    int16_t boss_records[40][2];
    uint8_t unknown_1a68[0x240];
    uint8_t loanCounts[64];   // Loans taken from demons, by race (HD: syakkincnt)
    uint8_t questionAnswers[4];   // the talks' questions answered: [0] in all, [1..3] by kind (HD: negoques)
    uint8_t reason_points[4]; // [1..3]: points toward each Reason (Kotowari)
    uint8_t unknown_1cf0[4];
    ee::Float encountDistance; // walked toward the next encounter roll (HD: encountkyori)
    uint16_t encountCount;    // the encounter count (HD: encountcnt)
    uint8_t hearts_equipped;  // Magatama ID, 0 = none
    uint8_t hearts_owned[64];
    uint8_t hearts_skill_state[64];
    uint8_t hearts_owned_count;
    uint8_t unknown_1d7c[0x11ab8 - 0x1d7c - (kGlobalWorkTailShift - kGlobalWorkShift)];   // (US Maniax's offsets)
    uint32_t config;          // the options' bits (dds3CheckConfigBit)
    uint32_t unknown_11abc;
    uint16_t hearts_learned_skills[26][12]; // Magatama skills learned, in order
    uint8_t unknown_11d30[0x90];
    uint8_t hearts_param_upgrades[26][6];   // extra stat bonuses per Magatama
    uint8_t unknown_11e5c[0x24];
    int32_t encyc_count;                    // compendium entries
    uint8_t unknown_11e84[0xc];
    EncycRecord encyc_records[184];
};
// (US Maniax's offsets.)
static_assert(offsetof(GlobalWork, script_ints) + kGlobalWorkShift == 0x40 &&
              offsetof(GlobalWork, event_bits) + kGlobalWorkShift == 0x840);
static_assert(offsetof(GlobalWork, macca) + kGlobalWorkShift == 0xa48);
static_assert(offsetof(GlobalWork, units) + kGlobalWorkShift == 0xa54);
static_assert(offsetof(GlobalWork, stock_list) + kGlobalWorkShift == 0x1914);
static_assert(offsetof(GlobalWork, item_counts) + kGlobalWorkShift == 0x1928);
static_assert(offsetof(GlobalWork, reason_points) + kGlobalWorkShift == 0x1cec && offsetof(GlobalWork, loanCounts) + kGlobalWorkShift == 0x1ca8);
static_assert(offsetof(GlobalWork, config) + kGlobalWorkTailShift == 0x11ab8);
static_assert(offsetof(GlobalWork, hearts_equipped) + kGlobalWorkShift == 0x1cfa);
static_assert(offsetof(GlobalWork, hearts_owned_count) + kGlobalWorkShift == 0x1d7b);
static_assert(offsetof(GlobalWork, hearts_learned_skills) + kGlobalWorkTailShift == 0x11ac0);
static_assert(offsetof(GlobalWork, hearts_param_upgrades) + kGlobalWorkTailShift == 0x11dc0);
static_assert(offsetof(GlobalWork, encyc_count) + kGlobalWorkTailShift == 0x11e80);
static_assert(offsetof(GlobalWork, encyc_records) + kGlobalWorkTailShift == 0x11e90);

} // namespace nocturne
