// Differential test: the rewritten battle and unit code vs. the legacy C.
//
// For every case, a random battle state is written into fake PS2 RAM. The
// legacy function runs, then the state is restored and the rewrite runs.
// The two must agree on the return value, any trap, the RNG draws, the debug
// prints and every byte of dynamic RAM. Callees run as real code on both
// sides (legacy callees vs. rewritten callees); only the engine boundary is
// faked (fake_world.c).
//
// Fusion and growth tests are in fusion_tests.cpp.
//
// usage: differential <path to SLUS_209.11> [cases per function] [seed] [name filter]
#include <csetjmp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "fake_world.h"
#include "harness.hpp"
#include "version_map.hpp"
#include "interface_world.hpp"
#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/encount.hpp"
#include "nocturne/battle/result.hpp"
#include "nocturne/facility/shop.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/damage.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/variant.hpp"
#if __has_include("nocturne/hardtype.hpp")
#include "nocturne/hardtype.hpp"
#endif

extern "C" {
#include "battle_affinity.h"
#include "battle_effects.h"
#include "battle_power.h"
#include "battle_support_access.h"
#include "battle_targeting.h"
#include "combat_calculation.h"

// From nocturne.h, battle_action_status.h and unit_progression.h, which use
// C-only constructs.
struct datUnitWork_PS2;
int32_t datGetBaseParam(datUnitWork_PS2* work, int32_t paratype);
int32_t datGetParam(datUnitWork_PS2* work, int32_t paratype);
int32_t datGetBaseMaxHp(datUnitWork_PS2* work);
int32_t datGetBaseMaxMp(datUnitWork_PS2* work);
uint32_t datGetMaxHp(datUnitWork_PS2* work);
uint32_t datGetMaxMp(datUnitWork_PS2* work);
int32_t datGetPlayerLevel(void);
int32_t datGetRace(datUnitWork_PS2* work);
int32_t datCheckSyojiSkill(datUnitWork_PS2* work, uint32_t skill);
int32_t datCheckSkillInParty(int32_t skillid);
void datSetBadStat(datUnitWork_PS2* work, uint32_t badstat);
void datResetBadStat(datUnitWork_PS2* work, uint32_t badstat);
void datOverwriteBadStat(datUnitWork_PS2* work, uint32_t badstat);
int32_t datGetBadStatusAttr(int32_t bad);
uint32_t datAddHp(datUnitWork_PS2* work, int32_t hp);
uint32_t datAddMp(datUnitWork_PS2* work, int32_t mp);
int32_t datCheckDying(datUnitWork_PS2* work);
int32_t nbHatudoCheckSkill(datUnitWork_PS2* work, int32_t skill);
uint64_t nbGetDevilFormatFlag(uint64_t form);
uint64_t nbCheckKuisibariSkill(uint64_t form);
uint64_t nbCheckKuisibari2Skill(uint64_t form);
void nbSetKuisibariStop(uint64_t form);
uint64_t nbGetUnitID(uint64_t work);
uint64_t ps2UnitMagicHitPower_00242CB0(uint64_t unit);
uint64_t ps2UnitEvasionPower_00242D50(uint64_t unit);
uint64_t datGetSkillCost(uint64_t unit, uint64_t skill);
uint64_t nbCheckSkillCost(uint64_t formation, uint64_t skill);
uint64_t nbGetLvAvg(uint64_t main, uint64_t side);
uint64_t nbCheckSkillUse(uint64_t formation, uint64_t skill);
uint64_t nbGetAisyoTable(uint64_t formation);
uint64_t nbGetEscapeSwitch(uint64_t main);
uint64_t nbGetVirtualKoukaPoint(uint64_t skill, uint64_t source, uint64_t target);
}

using namespace nocturne;

// ---- platform hooks for the rewrite -------------------------------------------

void* nocturne::guest::resolve(uint32_t address) { return fw_resolve(address); }
uint32_t nocturne::guest::addressOf(const void* pointer) { return pointer ? fw_address_of(pointer) : 0; }

namespace difftest {

namespace {
const uint16_t kAilments[] = {0, 0, 0, 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800};

} // namespace

// Skills that change battle calculations, so random units own them often.
int32_t interestingSkill(Gen& g)
{
    static const int32_t kFixed[] = {
        skill::Pierce, skill::Might, skill::BrightMight, skill::DarkMight, skill::MindsEye, skill::FastRetreat,
        skill::LifeBonus, skill::LifeGain, skill::LifeSurge, skill::ManaBonus, skill::ManaGain, skill::ManaSurge,
        skill::SonsOath, skill::Endure, skill::NeverYield, skill::HolyMelody, skill::EvilMelody,
    };
    switch (g.below(6)) {
    case 0: return g.pick(kFixed);
    case 1: return skill::AntiPhys + g.range(0, 9);
    case 2: return skill::VoidPhys + g.range(0, 9);
    case 3: return g.chance(50) ? skill::PhysDrain + g.range(0, 4) : skill::PhysRepel + g.range(0, 4);
    case 4: return skill::FireBoost + g.range(0, 3);
    default: return g.range(0, 0x1ff);
    }
}

void randomUnit(Gen& g, UnitWork& u, bool enemy)
{
    std::memset(&u, 0, sizeof u);
    static const uint32_t kPlayerFlags[] = {1, 3, 3, 3, 7, 5, 0, 0x23};
    static const uint32_t kEnemyFlags[] = {0x21, 0x21, 0x23, 0x25, 0x01};
    u.flag = enemy ? g.pick(kEnemyFlags) : g.pick(kPlayerFlags);
    u.id = static_cast<uint16_t>(g.chance(5) ? 0x125 : g.range(1, lastDevilWithAi()));
    u.maxhp = static_cast<uint16_t>(g.chance(3) ? 0 : g.range(1, 999));
    u.hp = static_cast<uint16_t>(g.chance(10) ? 0 : g.range(0, u.maxhp));
    u.maxmp = static_cast<uint16_t>(g.range(0, 500));
    u.mp = static_cast<uint16_t>(g.range(0, u.maxmp));
    u.badstat = g.pick(kAilments) | (g.chance(10) ? 0x8000 : 0);
    u.level = static_cast<uint16_t>(g.chance(3) ? g.range(100, 255) : g.range(1, 99));
    for (int i = 0; i < 6; ++i) {
        u.param[i] = static_cast<int8_t>(g.range(-2, 40));
        u.skillparam[i] = static_cast<int8_t>(g.chance(20) ? g.range(-3, 5) : 0);
        u.mitamaparam[i] = static_cast<int8_t>(g.range(0, 5));
    }
    u.skillcnt = static_cast<uint16_t>(g.range(0, 10));
    for (int i = 0; i < u.skillcnt; ++i)
        u.skill[i] = static_cast<uint16_t>(interestingSkill(g));
}

} // namespace difftest

namespace {

using namespace difftest;

uint32_t randomAffinity(Gen& g)
{
    static const uint32_t kValues[] = {
        100, 100, 100, 100, 50, 0x80000096u, 0x10000, 0x20000, 0x40000, 0x110000, 0x100064, 10, 200, 0,
    };
    return g.pick(kValues);
}

void randomParty(Gen& g, nb::Party& p)
{
    for (int i = 4; i <= 8; ++i)
        p.count[i] = static_cast<int16_t>(g.chance(50) ? g.range(-4, 4) : 0);
    for (int i = 9; i <= 15; ++i)
        p.count[i] = static_cast<int16_t>(g.chance(15) ? 1 : 0);
    if (g.chance(5))
        p.count[19] = static_cast<int16_t>(g.range(1, 447));
    for (uint32_t& a : p.affinities)
        a = randomAffinity(g);
}

void randomWorld(Gen& g)
{
    std::memset(fw_ram + FW_DYNAMIC_BEGIN, 0, dynamicEnd() - FW_DYNAMIC_BEGIN);
    at<uint32_t>(dat::address::GlobalWorkPointer) = FW_GLOBAL;

    GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
    global.macca = g.range(0, 999999);
    global.fieldskills = g.below(4);
    for (int i = 0; i < 16; ++i)
        randomUnit(g, global.units[i], false);
    global.units[0].flag = 7; // the Demi-fiend

    // Formation slots: 0..3 the party, 4..13 enemies; some slots empty.
    auto* formUnits = &at<uint32_t>(FW_FORM_UNITS);
    for (int f = 0; f < 14; ++f) {
        bool empty = f > 0 && g.chance(15);
        if (f < 4) {
            formUnits[f] = empty ? 0 : FW_GLOBAL + static_cast<uint32_t>(offsetof(nocturne::GlobalWork, units)) + 0xec * static_cast<uint32_t>(f == 0 ? 0 : g.range(1, 15));
        } else {
            uint32_t address = FW_ENEMIES + 0xec * static_cast<uint32_t>(f - 4);
            randomUnit(g, at<UnitWork>(address), true);
            formUnits[f] = empty ? 0 : address;
        }
    }

    auto* forms = &at<nb::Formation>(FW_FORMS);
    auto* party = &at<nb::Party>(FW_PARTY);
    for (int f = 0; f < 14; ++f) {
        static const uint32_t kFormStats[] = {0, 0, 0, 0x1000, 0x2000, 0x3000};
        forms[f].stat = g.pick(kFormStats);
        forms[f].formindex = static_cast<int16_t>(g.chance(80) ? f : g.range(0, 13));
        forms[f].scl = ee::Float::fromInt(g.range(1, 3));
        int16_t flag = static_cast<int16_t>(formUnits[f] ? 1 : 0);
        if (f >= 4) flag |= 2;
        if (g.chance(10)) flag |= 4;
        if (g.chance(10)) flag |= 0x100;
        if (g.chance(15)) flag |= 0x200;
        if (g.chance(15)) flag |= 0x400;
        party[f].flag = flag;
        party[f].formindex = static_cast<int16_t>(f);
        randomParty(g, party[f]);
    }
    // Each formation's model object (+0x1C its control block) and unit handle
    // (+0x8C its draw flags' address, +0xA4 bit 0x10000 while it loads).
    for (int f = 0; f < 16; ++f) {
        const uint32_t object = FW_MODELS + 0x20u * f, handle = FW_MODELS + 0x200u + 0x20u * f - 0x8c;
        forms[f].basic = g.chance(85) ? object : 0;
        at<uint32_t>(object + 0x1c) = FW_MODELS + 0x440u + 0x10u * f - 0xc4;
        forms[f].hunit = handle;
        at<uint32_t>(handle + 0x8c) = FW_MODELS + 0x400u + 4u * f;
        at<uint32_t>(FW_MODELS + 0x400u + 4u * f) = static_cast<uint32_t>(g.rng());
        at<uint32_t>(handle + 0xa4) = g.chance(10) ? 0x10000u : 0;
    }

    nb::MainProcessData& data = at<nb::MainProcessData>(FW_MAIN);
    data.form.address = FW_FORMS;
    data.party.address = FW_PARTY;
    data.encpackno = g.chance(15) ? 0 : g.range(1, 39);
    data.packno = g.range(0, 3);
    data.packindex = g.range(0, 11);
    static const int32_t kSpecialEncounters[] = {0, 0x10b, 0x11c, 0x149, 0x408, -1};
    // Boss refights (datBossPress_t encounters) sometimes.
    static const int32_t kRefights[] = {14, 55, 83, 84, 116, 117, 271, 194, 196, 197, 198, 199,
                                        713, 714, 329, 327, 328, 284, 970, 1008, 334, 472, 333, 267};
    data.encno = g.chance(10) ? g.pick(kSpecialEncounters) : g.chance(20) ? g.pick(kRefights) : g.range(1, 1279);
    if (data.encno < 0) data.encno = g.range(1, 1279);
    static const uint32_t kStatBits[] = {0x1, 0x8, 0x10, 0x80, 0x400};
    for (uint32_t bit : kStatBits) if (g.chance(30)) data.stat |= bit;
    if (g.chance(3)) data.stat |= 0x08000000;
    if (g.chance(3)) data.stat |= 0x40000000;
    data.esccnt = static_cast<uint8_t>(g.range(0, 5));
    data.enemypcnt = static_cast<int16_t>(g.range(0, 10));
    for (int i = 0; i < 4; ++i) {
        data.item[i] = static_cast<uint8_t>(g.chance(40) ? g.range(1, 60) : 0);
        data.itemcnt[i] = static_cast<uint8_t>(data.item[i] ? g.range(1, 255) : 0);
    }
    data.macca = static_cast<uint32_t>(g.range(0, 30000));
    data.exp = static_cast<uint32_t>(g.range(0, 40000));
    data.previndex = 7;
    data.turn = 3;

    nb::ActionProcessData& action = at<nb::ActionProcessData>(FW_ACTION);
    action.data.address = FW_MAIN;
    action.autoskill = -1;
}

} // namespace

void difftest::battleWorld(Gen& g) { randomWorld(g); }

namespace {

// Formation indices that hold a unit.
int occupiedForm(Gen& g, int lo = 0, int hi = 13)
{
    for (;;) {
        int f = g.range(lo, hi);
        if (at<uint32_t>(FW_FORM_UNITS + 4 * static_cast<uint32_t>(f))) return f;
    }
}

int32_t randomSkill(Gen& g)
{
    static const int32_t kSpecial[] = {0, 0, 0, skill::HolyMelody, skill::EvilMelody, 0xbe, 0xc7, 0xd4};
    return g.chance(35) ? g.pick(kSpecial) : g.range(0, 0x17f);
}

// An active skill with a NormalSkill record, including the special-cased
// ones. Skips random-ailment skills with an empty mask, where the original
// reads an uninitialised choice.
int32_t activeSkill(Gen& g)
{
    static const int32_t kSpecial[] = {0, 0x110, skill::Stinger, 0x103, 0x104, 0x4f, 0xd2, 0xc0};
    // Skills by category, so each code path is reached often.
    static std::vector<int32_t> byBadtype[4], byHptype[17], byMptype[17];
    if (byBadtype[0].empty()) {
        for (int32_t s = 0; s < 0x120; ++s) {
            const NormalSkill& n = dat::normalSkill(s);
            if (n.badtype < 4) byBadtype[n.badtype].push_back(s);
            if (n.hptype < 17) byHptype[n.hptype].push_back(s);
            if (n.mptype < 17) byMptype[n.mptype].push_back(s);
        }
    }
    for (;;) {
        int32_t s;
        uint32_t mode = g.below(10);
        if (mode < 2) {
            s = g.pick(kSpecial);
        } else if (mode < 5) {
            auto& list = byBadtype[g.below(4)];
            s = list.empty() ? 0 : list[g.below(static_cast<uint32_t>(list.size()))];
        } else if (mode < 7) {
            auto& list = (g.chance(50) ? byHptype : byMptype)[g.below(17)];
            s = list.empty() ? 0 : list[g.below(static_cast<uint32_t>(list.size()))];
        } else {
            s = g.range(0, 0x11f);
        }
        const NormalSkill& n = dat::normalSkill(s);
        if (n.badtype == 3 && (n.badstatus & 0x3fff) == 0)
            continue;
        return s;
    }
}

const float kRatios[] = {0.0f, 0.5f, 1.0f, 1.0f, 1.5f, 2.0f, 0.25f, 1.25f};

// ---- running a case ---------------------------------------------------------------

struct Outcome {
    int trap = 0;
    uint64_t result = 0;
    fw_trace trace{};
    std::vector<uint8_t> ram;
    std::vector<uint8_t> statics;
};

// Static game data some functions write to (nbSetNormalSkill0 rewrites the
// normal attack's skill data; the AI rotation counter). Compared, and
// restored between the two runs and after each case.
struct StaticRange { uint32_t address, size; };
const StaticRange kWrittenStatics[] = {
    {0x0055123c, 4},                                       // the party panel shown (nbPanelPartyShow)
    {0x00000000, 0x10},                                    // writes through a null request (a speaker with no name)
    {0x003d7998, 60}, {0x003d7998 + 0xa4 * 60, 4 * 60},   // NormalSkill 0, 0xA4..0xA7
    {0x003d6998, 8}, {0x003d6998 + 0xa4 * 8, 4 * 8},      // SkillInfo
    {0x003dbd20, 4}, {0x003dbd20 + 0xa4 * 4, 4 * 4},      // skill hit effects
    {0x005514e8, 4},                                       // AI rotation counter
    {0x00551120, 4},                                       // the stock demon chosen (STKSEL)
    {0x00575360, 0x20},                                    // the skill's sound file name (READY)
    {0x0056be60, 0x0056c880 - 0x0056be60},                 // message manager and its nodes
    {0x0056bbc4, 0x90},                                    // font contexts and {var n} strings
    {0x0054f400, 0x48},                                    // font settings (result, spacing, mode, style...)
    {0x0056b668, 0x20},                                    // font texture cells
    {0x0056ba30, 0x0056bbc4 - 0x0056ba30},                 // font styles, pools and counters
    {0x00326060, 8},                                       // default advance per style
    {0x003261e8, 0x24},                                    // styles loaded
    {0x0054ea00, 4},                                       // the last character laid out
    {0x00551ea0, 4},                                       // bytes of the last decoded glyph
    {0x00551b80, 4},                                       // the display buffer being built
    {0x0056bc50, 0x110},                                   // entered names' glyphs and references
    {0x002f5830, 0x20},                                    // pad triggers
    {0x0054ea20, 4},                                       // pointer to the entered names
    {0x0056c880, 0x40},                                    // BuildCharacterName's buffer
    {0x0054e994, 0xc},                                     // the running scripts
    {0x0054e95c, 0x28},                                    // dds3DrawFlag, the screen blur and quake, refused settings
    {0x00551bac, 12},                                      // the screen blur's fade
    {0x00551c10, 0x48},                                    // the event effects' fades
    {0x005572c0, 0x1f0},                                   // their settings
    {0x0054f278, 8},                                       // which event effects are drawn
    {0x003201d0, 0x28},                                    // Eve_Blur's settings
    {0x00320258, 0x18},                                    // Eve_Filter's settings
    {0x002f59bc, 4},                                       // the field of view
    {0x002f5b40, 0x34},                                    // lights, ambient, fog
    {0x00551bc0, 0x50},                                    // the light, ambient, fog and soften fades
    {0x00557220, 0x80},                                    // the light colours' packed ends, direction turns
    {0x005572a0, 0x20},                                    // the fog parameters' ends
    {0x005518a8, 8},                                       // soften, bias
    {0x00551c58, 0x24},                                    // TwoOperation's operands; the running COMM's work
    {0x00575490, 0x80},                                    // the ailment AI's weighted actions
    {0x00551558, 4},                                       // ... and how many
    {0x00320e40, 0x30},                                    // the battle camera (nbCameraCurrent)
    {0x0054e804, 0x20},                                    // the kernel's stop and slow motion (dds3Stop, dds3SlowOn)
    {0x00551208, 4},                                       // the stock panel's fade out
    {0x00551d80, 4},                                       // the skill effect's state (effBTLSkillSetState)
    {0x00551520, 0x30},                                    // the encounter threshold (nbGetEncountMax), the battle music (nbBgmLoad)
    {0x01280000, 0x100},                                   // a unit placed above 0x1200000 (variant_tests.cpp)
    {0x00000190, 0x1000},                                  // Hardtype's AI writes through stale registers here (nbAiAiChk, conditions 60/61)
    // Hardtype keeps its own state among its code, and an option byte after
    // it (none in US Maniax).
    {0x002fdc20, nocturne::kVariant == nocturne::Variant::Hardtype ? 0x176cu : 0u},
    {0x00575450, 0x20},                                    // a unit's sound file name
    {0x005510d8, 0x38},                                    // the result screen's counters and textures
    {0x00574e80, 0xd0},                                    // ... its rows
    {0x00574f50, 0x400},                                   // ... its level-up animations
};

// ... at the version's addresses (those it has; Hardtype's own state and
// the low pages are its own).
const std::vector<StaticRange>& writtenStatics()
{
    static const std::vector<StaticRange> ranges = [] {
        std::vector<StaticRange> out;
        for (const StaticRange& r : kWrittenStatics) {
            const uint32_t at = r.address < 0x002f5000 || r.address >= 0x01000000 ? r.address : difftest::version::data(r.address);
            if (at != 0 && r.size != 0)
                out.push_back({at, r.size});
        }
        return out;
    }();
    return ranges;
}

std::vector<uint8_t> captureStatics()
{
    std::vector<uint8_t> bytes;
    for (const StaticRange& r : writtenStatics())
        bytes.insert(bytes.end(), fw_ram + r.address, fw_ram + r.address + r.size);
    return bytes;
}

void restoreStatics(const std::vector<uint8_t>& bytes)
{
    size_t offset = 0;
    for (const StaticRange& r : writtenStatics()) {
        std::memcpy(fw_ram + r.address, bytes.data() + offset, r.size);
        offset += r.size;
    }
}

// Traps longjmp out of the code under test; no frame in between owns
// anything with a destructor.
#pragma warning(disable : 4611)
Outcome run(const std::function<uint64_t()>& body, uint64_t seed, int normal, uint32_t moon)
{
    Outcome out;
    fw_begin_case(seed, normal, moon);
    std::jmp_buf target;
    fw_trap_target = &target;
    int code = setjmp(target);
    if (code == 0)
        out.result = body();
    else
        out.trap = code;
    out.trace = fw_current_trace;
    out.ram.assign(fw_ram + FW_DYNAMIC_BEGIN, fw_ram + dynamicEnd());
    out.statics = captureStatics();
    return out;
}

std::string describe(const Outcome& a, const Outcome& b)
{
    char buffer[256];
    if (a.trap != b.trap) { std::snprintf(buffer, sizeof buffer, "trap %d vs %d", a.trap, b.trap); return buffer; }
    if (a.result != b.result) { std::snprintf(buffer, sizeof buffer, "result %llx vs %llx", (unsigned long long)a.result, (unsigned long long)b.result); return buffer; }
    if (a.trace.rng_count != b.trace.rng_count) { std::snprintf(buffer, sizeof buffer, "%u vs %u RNG draws", a.trace.rng_count, b.trace.rng_count); return buffer; }
    for (uint32_t i = 0; i < a.trace.rng_count && i < FW_MAX_TRACE; ++i)
        if (a.trace.rng_limit[i] != b.trace.rng_limit[i]) { std::snprintf(buffer, sizeof buffer, "RNG draw %u: limit %u vs %u", i, a.trace.rng_limit[i], b.trace.rng_limit[i]); return buffer; }
    if (a.trace.print_count != b.trace.print_count) {   // (and the first format where they part)
        uint32_t k = 0;
        while (k < a.trace.print_count && k < b.trace.print_count && k < FW_MAX_TRACE &&
               a.trace.print_format[k] == b.trace.print_format[k])
            ++k;
        auto format = [&](const Outcome& o) { return k < o.trace.print_count && k < FW_MAX_TRACE ? o.trace.print_format[k] : 0u; };
        std::snprintf(buffer, sizeof buffer, "%u vs %u prints (print %u: format %08x vs %08x)", a.trace.print_count,
                      b.trace.print_count, k, format(a), format(b));
        return buffer;
    }
    for (uint32_t i = 0; i < a.trace.print_count && i < FW_MAX_TRACE; ++i) {
        if (a.trace.print_format[i] != b.trace.print_format[i]) { std::snprintf(buffer, sizeof buffer, "print %u: format %08x vs %08x", i, a.trace.print_format[i], b.trace.print_format[i]); return buffer; }
        for (int k = 0; k < fw_print_arg_count(a.trace.print_format[i]); ++k)
            if (a.trace.print_args[i][k] != b.trace.print_args[i][k]) { std::snprintf(buffer, sizeof buffer, "print %u arg %d: %lld vs %lld", i, k, (long long)a.trace.print_args[i][k], (long long)b.trace.print_args[i][k]); return buffer; }
    }
    if (a.statics != b.statics) {
        size_t offset = 0;
        for (const StaticRange& r : writtenStatics()) {   // (as captured: at the version's addresses)
            for (uint32_t i = 0; i < r.size; ++i)
                if (a.statics[offset + i] != b.statics[offset + i]) {
                    std::snprintf(buffer, sizeof buffer, "static data writes differ at %08x: %02x vs %02x", r.address + i,
                                  a.statics[offset + i], b.statics[offset + i]);
                    return buffer;
                }
            offset += r.size;
        }
    }
    // DIFF_DUMP=address,bytes: print that RAM from both sides.
#pragma warning(suppress : 4996)
    if (const char* dump = std::getenv("DIFF_DUMP")) {
        const uint32_t at = static_cast<uint32_t>(std::strtoul(dump, nullptr, 16));
        const char* comma = std::strchr(dump, ',');
        const uint32_t count = comma ? static_cast<uint32_t>(std::strtoul(comma + 1, nullptr, 16)) : 0x40;
        for (int side = 0; side < 2; ++side) {
            const auto& ram = side == 0 ? a.ram : b.ram;
            std::fprintf(stderr, "%s %08x:", side == 0 ? "orig" : "new ", at);
            for (uint32_t k = 0; k < count && at + k - FW_DYNAMIC_BEGIN < ram.size(); ++k)
                std::fprintf(stderr, "%s%02x", k % 16 ? " " : "\n  ", ram[at + k - FW_DYNAMIC_BEGIN]);
            std::fprintf(stderr, "\n");
        }
    }
    // DIFF_ALL: list the first 24 differing bytes, not just the first.
#pragma warning(suppress : 4996)
    const bool all = std::getenv("DIFF_ALL") != nullptr;
    std::string listed;
    int shown = 0;
    for (size_t i = 0; i < a.ram.size(); ++i) {
        if (a.ram[i] == b.ram[i])
            continue;
        std::snprintf(buffer, sizeof buffer, "RAM %08zx: %02x vs %02x", FW_DYNAMIC_BEGIN + i, a.ram[i], b.ram[i]);
        if (!all)
            return buffer;
        listed += (listed.empty() ? "" : "; ") + std::string(buffer);
        if (++shown == 24)
            break;
    }
    return listed;
}

nb::MainProcessData& mainData() { return at<nb::MainProcessData>(FW_MAIN); }
uint32_t formUnit(int f) { return at<uint32_t>(FW_FORM_UNITS + 4 * static_cast<uint32_t>(f)); }

// What a version models of registers its code leaves (hardtype.hpp): as the
// interpreter's, 0 when a case's call starts.
void resetLeftRegisters()
{
#if __has_include("nocturne/hardtype.hpp")
    nocturne::hardtype::affinityRegister() = 0;
#endif
}

// nbCalc's functions that versions patch, against the executable's own
// instructions (the tests above compare with US Maniax's legacy C).
void addCalcInstructionTests(std::vector<TestCase>& t)
{
    using iface::origVm;
    auto add = [&t](const char* name, std::function<Pair(Gen&)> body) {
        t.push_back({name, [body](Gen& g) {
                         if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype)   // what Hardtype reads at fixed addresses
                             for (uint32_t address : {0x01248f41u, 0x01248f44u, 0x0124a213u, 0x002ff388u})
                                 at<uint8_t>(address) = static_cast<uint8_t>(g.below(256));
                         return body(g);
                     }});
    };
    add("nbGetHitType (instructions)", [](Gen& g) {
        int32_t skill = randomSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        return Pair{[=] { return origVm(0x002654b8, {FW_ACTION, sx(skill), sx(s), sx(d)}); },
                    [=] { return norm(static_cast<int32_t>(nb::rollCritical(at<nb::ActionProcessData>(FW_ACTION), skill, s, d))); }};
    });
    add("nbGetKoukaType (instructions)", [](Gen& g) {
        int32_t skill = randomSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        return Pair{[=] { return origVm(0x00265948, {sx(skill), sx(s), sx(d)}); },
                    [=] { return norm(static_cast<int32_t>(nb::resolveEffect(skill, s, d))); }};
    });
    add("nbGetAisyo (instructions)", [](Gen& g) {
        int32_t skill = g.chance(15) ? -1 : activeSkill(g), f = occupiedForm(g), attr = g.range(-1, 15);
        if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype) {   // its own passives, and its families'
            UnitWork& unit = at<UnitWork>(formUnit(f));
            if (g.chance(50))
                attr = g.range(1, 10);
            for (int k = 0; k < 3; ++k)
                if (g.chance(60))
                    unit.skill[g.below(8)] = static_cast<uint16_t>(g.pick<int32_t>({0x16b, 0x16d, 0x16f, 0x171, 0x13a, 0x13e, 0x140, 0x14a, 0x14c}));
            unit.skillcnt = static_cast<uint16_t>(std::max<int32_t>(unit.skillcnt, 8));
        }
        return Pair{[=] { return origVm(0x00267890, {sx(skill), sx(f), sx(attr)}); },
                    [=] { return norm(static_cast<int32_t>(nb::affinity(skill, f, static_cast<Attribute>(attr)).raw)); }};
    });
    add("nbGetAisyoRitu (instructions)", [](Gen& g) {
        int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype) {   // its boosts and Pierce
            UnitWork& unit = at<UnitWork>(formUnit(s));
            for (int k = 0; k < 3; ++k)
                if (g.chance(60))
                    unit.skill[g.below(8)] = static_cast<uint16_t>(g.pick<int32_t>({0x173, 0x174, 0x177, 0x135, 0x136, 0x137, 0x138, 0x165, 0x169}));
            unit.skillcnt = static_cast<uint16_t>(std::max<int32_t>(unit.skillcnt, 8));
            if (g.chance(30))
                skill = 0;
            for (int tries = 0; tries < 40 && g.chance(50); ++tries) {   // a Fire..Force skill
                skill = g.range(1, 0x11f);
                const int8_t element = dat::skillInfo(skill).skillattr;
                if (element >= 1 && element <= 4 && dat::skillInfo(skill).type == 0)
                    break;
            }
        }
        return Pair{[=] { origVm(0x00266130, {sx(skill), sx(s), sx(d)}); return uint64_t{iface::origVmFloat()}; },
                    [=] { return uint64_t{nb::damageRatio(skill, s, d).bits()}; }};
    });
    auto power = [&add](const char* name, uint32_t entry, int32_t (*rewrite)(int32_t, int32_t, int32_t, int32_t)) {
        add(name, [=](Gen& g) {
            int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g), base = g.range(0, 300);
            return Pair{[=] { return origVm(entry, {sx(skill), sx(s), sx(d), sx(base)}); }, [=] { return norm(rewrite(skill, s, d, base)); }};
        });
    };
    power("nbGetMagicAttack (instructions)", 0x002688d0, nb::magicPower);
    power("nbGetMagicKaifuku (instructions)", 0x00268c60, nb::magicHealPower);
    // (Hardtype's tests its caller's skill, in s6: 0 for a direct call. The
    // skill-0x97 case runs through nbGetKoukaHp.)
    power("nbGetMaxHpWazaPoint (instructions)", 0x00268d60,
          [](int32_t, int32_t s, int32_t d, int32_t base) { return nb::maxHpPower(0, s, d, base); });
    add("nbGetKoukaHp (instructions)", [](Gen& g) {
        int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g), count = g.range(0, 4), damage = g.range(0, 1);
        const float ratio = g.pick(kRatios);
        return Pair{[=] { return origVm(0x00266350, {sx(damage), sx(skill), sx(s), sx(d), sx(count)}, {static_cast<uint32_t>(floatBits(ratio))}); },
                    [=] { return norm(nb::hpEffect(ratio, damage != 0, skill, s, d, count)); }};
    });
    add("GetAddExp", [](Gen& g) {
        const int32_t index = g.range(0, 15), exp = g.chance(10) ? g.range(-50, 0) : g.range(0, 100000);
        if (g.chance(30))
            nocturne::dat::globalWork().units[index].exp = g.range(0, 0x7fffffff);
        return Pair{[=] { return origVm(0x0024bff0, {sx(index), sx(exp)}); }, [=] { return norm(nb::cappedExp(index, exp)); }};
    });
    add("nbResultAddExp", [](Gen& g) {
        nb::MainProcessData& main = mainData();
        for (int i = 0; i < 4; ++i) {
            main.item[i] = static_cast<uint8_t>(g.chance(50) ? 0 : g.range(1, 0x9f));
            main.itemcnt[i] = static_cast<uint8_t>(g.chance(20) ? 0 : g.range(1, 5));
        }
        for (UnitWork& unit : nocturne::dat::globalWork().units) {
            unit.flag = (unit.flag & ~3u) | static_cast<uint32_t>(g.range(0, 3));
            if (g.chance(30))
                unit.skill[g.below(8)] = 0x162;
            unit.skillcnt = static_cast<uint16_t>(std::max<int32_t>(unit.skillcnt, 8));
        }
        return Pair{[] { return iface::origVmVoid(0x0024c060, {}); }, [] { nb::grantSpoils(mainData()); return uint64_t{0}; }};
    });
    // ---- the result screen (nbResultProcess) ----
    const auto resultStatics = [](Gen& g) {
        for (uint32_t k = 0; k < 0x38; k += 4)
            at<uint32_t>(difftest::version::dataOrDie(0x005510d8) + k) = g.chance(50) ? 0 : static_cast<uint32_t>(g.range(0, 80));
    };
    add("nbResultTexDel", [=](Gen& g) {
        resultStatics(g);
        for (uint32_t k = 0; k < 3; ++k)
            at<uint32_t>(difftest::version::dataOrDie(0x00551104) + 4 * k) = g.chance(20) ? 0 : static_cast<uint32_t>(g.rng());
        return Pair{[] { return iface::origVmVoid(0x0024a258, {}); }, [] { nb::releaseResultTextures(); return uint64_t{0}; }};
    });
    add("nbResultLvupAnmAdd", [](Gen& g) {
        const uint32_t slots = difftest::version::dataOrDie(0x00574f50);
        const bool full = g.chance(10);
        for (uint32_t k = 0; k < 64; ++k) {
            at<int32_t>(slots + 16 * k) = full || g.chance(70) ? 1 : 0;
            at<int32_t>(slots + 16 * k + 12) = g.range(0, 20);
        }
        const int32_t a = g.range(-1, 20), b = g.range(-1, 100);
        return Pair{[=] { return iface::origVmVoid(0x0024a298, {sx(a), sx(b)}); }, [=] { nb::addLevelUpAnimation(a, b); return uint64_t{0}; }};
    });
    add("nbResultFinWaitChk", [=](Gen& g) {
        resultStatics(g);
        const uint32_t rows = difftest::version::dataOrDie(0x00574e80);
        for (uint32_t k = 0; k < 4; ++k) {
            const uint32_t row = rows + 0x34 * k, source = FW_SCRATCH + 0x20 * k;
            at<int32_t>(row) = g.chance(70) ? 1 : 0;
            at<uint32_t>(source + 0x10) = static_cast<uint32_t>(g.range(0, 500));
            at<uint32_t>(row + 0x2c) = static_cast<uint32_t>(g.range(0, 20));
            at<uint32_t>(row + 4) = at<uint32_t>(source + 0x10) + at<uint32_t>(row + 0x2c) - (g.chance(50) ? 0 : g.range(0, 3));
            at<uint32_t>(row + 0x14) = source;
        }
        return Pair{[] { return iface::origVm(0x0024afa0, {}); }, [] { return norm(nb::finishWait()); }};
    });
    add("ShutdownProcess (0x24BE88)", [](Gen& g) {
        nb::MainProcessData& main = mainData();
        for (uint32_t* id : {&main.AutoCommProcessID, &main.CameraProcessID, &main.EffectProcessID, &main.UnitProcessID,
                             &main.HelpProcessID, &main.PanelProcessID})
            *id = g.chance(40) ? 0 : static_cast<uint32_t>(g.range(1, 0x1000));
        return Pair{[] { return iface::origVmVoid(0x0024be88, {}); }, [] { nb::stopBattleProcesses(); return uint64_t{0}; }};
    });
    add("ClearStage (0x24BF40)", [](Gen& g) {
        for (int32_t i = 0; i < 14; ++i)
            if (g.chance(50))
                at<nb::Formation>(FW_FORMS + 0xf0u * static_cast<uint32_t>(i)).pacRequest = g.chance(30) ? 0 : static_cast<uint32_t>(g.range(1, 0x1000));
        return Pair{[] { return iface::origVmVoid(0x0024bf40, {}); }, [] { nb::clearStage(); return uint64_t{0}; }};
    });
    add("nbResultProcess1", [=](Gen& g) {
        resultStatics(g);
        nb::MainProcessData& main = mainData();
        main.AutoCommProcessID = g.chance(50) ? 0 : 7;
        main.HelpProcessID = g.chance(50) ? 0 : 9;
        return Pair{[] { return iface::origVm(0x0024c378, {0}); }, [] { return norm(static_cast<int32_t>(nb::firstResultStep(0))); }};
    });
    add("nbResultShutdown", [=](Gen& g) {
        resultStatics(g);
        mainData().ResultProcessID = static_cast<uint32_t>(g.range(0, 100));
        return Pair{[] { return iface::origVmVoid(0x0024c3c8, {0}); }, [] { nb::shutdownResult(0); return uint64_t{0}; }};
    });
    add("nbInitResultProcess", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x0024c3f0, {FW_MAIN}); }, [] { nb::startResultProcess(mainData()); return uint64_t{0}; }};
    });
    // The shop: a work at FW_SHOP with random lists, one of the seven places.
    const auto openShop = [](Gen& g) {
        at<uint32_t>(difftest::version::dataOrDie(0x00551f2c)) = FW_SHOP;
        at<int8_t>(FW_SHOP + 0x19) = static_cast<int8_t>(g.range(0, 6));
        for (uint32_t i = 0; i < 0x44; ++i)
            at<uint16_t>(FW_SHOP + 0x2200 + 2 * i) = static_cast<uint16_t>(g.chance(10) ? 0 : g.range(1, 0x9f));
    };
    add("ps2ShopItemId", [=](Gen& g) {
        openShop(g);
        const int32_t index = g.range(0, 31);
        const bool selling = g.chance(50);
        return Pair{[=] { return origVm(0x002071e0, {sx(index), selling ? 1u : 0u}); },
                    [=] { return norm(nocturne::fcl::listedItem(index, selling)); }};
    });
    add("ps2ShopPackId", [](Gen& g) {
        const int32_t place = g.range(0, 6);
        return Pair{[=] { return origVm(0x00207210, {sx(place)}); }, [=] { return norm(nocturne::fcl::packOf(place)); }};
    });
    add("ps2ShopItemCount", [](Gen& g) {
        const int32_t place = g.range(0, 6);
        return Pair{[=] { return origVm(0x00207290, {sx(place)}); }, [=] { return norm(nocturne::fcl::packItemCount(place)); }};
    });
    add("ps2ShopItemPrice", [=](Gen& g) {
        openShop(g);
        const int32_t index = g.range(0, 31);
        const bool selling = g.chance(30);
        return Pair{[=] { return origVm(0x002073d8, {sx(index), selling ? 0xffu : 0u}); },
                    [=] { return norm(uint64_t{nocturne::fcl::itemPrice(index, selling)}); }};
    });
    add("nbCheckSensei (instructions)", [](Gen& g) {
        // An area entry with one of the six coefficients (the original reads
        // past them; Hardtype's wider tables reach other packs' bytes).
        nb::MainProcessData& data = mainData();
        for (int tries = 0; tries < 64 && nb::encounterEntry(data.encpackno, data.packno, data.packindex).firstStrike >= 6; ++tries) {
            data.packno = g.range(0, 3);
            data.packindex = g.range(0, 11);
        }
        return Pair{[] { return origVm(0x00269ad8, {FW_MAIN}); }, [] { return norm(nb::rollEnemiesFirst(mainData())); }};
    });
    add("nbCheckBackAttack (instructions)", [](Gen&) {
        return Pair{[] { return origVm(0x00269d20, {FW_MAIN}); }, [] { return norm(nb::rollBackAttack(mainData())); }};
    });
    add("nbCheckEscape (instructions)", [](Gen&) {
        return Pair{[] { return origVm(0x00269e98, {FW_MAIN}); }, [] { return norm(nb::rollEscape(mainData())); }};
    });
    add("nbCheckRenzokuEncount (instructions)", [](Gen&) {
        return Pair{[] { return origVm(0x0026a158, {FW_MAIN}); }, [] { return norm(nb::rollConsecutiveEncounter(mainData())); }};
    });
    add("nbGetKoukaBadDamage (instructions)", [](Gen& g) {
        int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g), preview = g.chance(20) ? 1 : 0;
        const float ratio = g.pick(kRatios);
        return Pair{[=] { return origVm(0x00266d60, {sx(skill), sx(s), sx(d), sx(preview)}, {static_cast<uint32_t>(floatBits(ratio))}); },
                    [=] { return norm(static_cast<int32_t>(nb::rollAilmentInflict(ratio, skill, s, d, preview != 0))); }};
    });
}

std::vector<TestCase> tests()
{
    std::vector<TestCase> t;
    t.push_back({"nbGetHitType", [](Gen& g) {
        int32_t skill = randomSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        return Pair{[=] { return norm(ps2CombatHitType_002654B8(FW_ACTION, sx(skill), sx(s), sx(d))); },
                    [=] { return norm(static_cast<int32_t>(nb::rollCritical(at<nb::ActionProcessData>(FW_ACTION), skill, s, d))); }};
    }});
    t.push_back({"nbGet3Zokusei", [](Gen& g) {
        int32_t f = occupiedForm(g);
        return Pair{[=] { return norm(ps2CombatAlignment_00265868(sx(f))); },
                    [=] { return norm(static_cast<int32_t>(nb::alignmentClass(f))); }};
    }});
    t.push_back({"nbCheckKoukaJyoken", [](Gen& g) {
        int32_t skill = randomSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        return Pair{[=] { return norm(ps2CombatEffectCondition_002658B8(sx(skill), sx(s), sx(d))); },
                    [=] { return norm(nb::meetsSkillCondition(skill, s, d)); }};
    }});
    t.push_back({"nbGetKoukaType", [](Gen& g) {
        int32_t skill = randomSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        return Pair{[=] { return norm(ps2CombatEffectType_00265948(sx(skill), sx(s), sx(d))); },
                    [=] { return norm(static_cast<int32_t>(nb::resolveEffect(skill, s, d))); }};
    }});
    t.push_back({"nbAddHpMp", [](Gen& g) {
        int32_t f = g.range(0, 13), type = g.range(0, 2), amount = g.range(-600, 600);
        return Pair{[=] { ps2CombatAddHpMp_002660C0(sx(f), sx(type), sx(amount)); return uint64_t{0}; },
                    [=] { nb::addHpMp(f, static_cast<nb::Resource>(type), amount); return uint64_t{0}; }};
    }});
    t.push_back({"nbGetHpDrainRitu", [](Gen& g) {
        int32_t skill = randomSkill(g);
        return Pair{[=] { return floatBits(ps2CombatHpDrainRate_00266C90(sx(skill))); },
                    [=] { return uint64_t{nb::hpDrainRate(skill).bits()}; }};
    }});
    t.push_back({"nbGetMpDrainRitu", [](Gen& g) {
        int32_t skill = randomSkill(g);
        return Pair{[=] { return floatBits(ps2CombatMpDrainRate_00266CD8(sx(skill))); },
                    [=] { return uint64_t{nb::mpDrainRate(skill).bits()}; }};
    }});
    t.push_back({"nbGetGensyoRitu", [](Gen& g) {
        int32_t skill = randomSkill(g);
        return Pair{[=] { return floatBits(ps2CombatReductionRate_00266D20(sx(skill))); },
                    [=] { return uint64_t{nb::reductionRate(skill).bits()}; }};
    }});
    t.push_back({"nbCheckHitEffect", [](Gen& g) {
        int32_t skill = randomSkill(g);
        return Pair{[=] { return norm(ps2CombatCheckHitEffect_00267370(sx(skill))); },
                    [=] { return norm(nb::hasHitEffect(skill)); }};
    }});
    t.push_back({"nbGetDeadType", [](Gen&) {
        return Pair{[] { return norm(ps2CombatDeadType_00267388()); }, [] { return norm(nb::deadType()); }};
    }});
    t.push_back({"nbCheckStoneDead", [](Gen& g) {
        int32_t skill = randomSkill(g), f = g.range(0, 13);
        if (formUnit(f) && g.chance(60)) unitAt(formUnit(f)).badstat = 0x400;
        return Pair{[=] { return norm(ps2CombatCheckStoneDeath_00267390(sx(skill), sx(f))); },
                    [=] { return norm(nb::rollStoneShatter(skill, f)); }};
    }});
    t.push_back({"nbSetBadStat", [](Gen& g) {
        int32_t f = g.range(0, 13), set = g.range(0, 1);
        uint32_t status = g.chance(15) ? 0x8000u : g.pick(kAilments);
        return Pair{[=] { ps2CombatSetStatus_002674D0(sx(f), sx(set), status); return uint64_t{0}; },
                    [=] { nb::setAilment(f, set != 0, status); return uint64_t{0}; }};
    }});
    t.push_back({"nbCheckBadKaifuku", [](Gen& g) {
        uint32_t unit = formUnit(g.range(0, 13));
        int32_t mode = g.range(0, 4);
        return Pair{[=] { return norm(ps2CombatCheckStatusRecovery_00267530(unit, sx(mode))); },
                    [=] { return norm(nb::checkAilment(unit ? &unitAt(unit) : nullptr, static_cast<nb::AilmentCheck>(mode))); }};
    }});
    t.push_back({"nbCheckBadCurse", [](Gen& g) {
        int32_t f = g.range(0, 13);
        return Pair{[=] { return norm(ps2CombatCheckCurse_002677B8(sx(f))); }, [=] { return norm(nb::isCursed(f)); }};
    }});
    t.push_back({"nbGetEncountTableItem", [](Gen&) {
        return Pair{[] { ps2CombatAddEncounterItems_00269318(FW_MAIN); return uint64_t{0}; },
                    [] { nb::addEncounterItem(mainData()); return uint64_t{0}; }};
    }});
    t.push_back({"nbGetExpMakaItem", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        return Pair{[=] { ps2CombatAddRewards_00269448(unit); return uint64_t{0}; },
                    [=] { nb::addDefeatRewards(unitAt(unit)); return uint64_t{0}; }};
    }});
    t.push_back({"nbGetLvAvg2", [](Gen& g) {
        int32_t side = g.range(0, 1);
        return Pair{[=] { return norm(ps2CombatLevelAverage_002697D8(FW_MAIN, sx(side))); },
                    [=] { return norm(nb::averageLevel(mainData(), static_cast<nb::Side>(side))); }};
    }});
    t.push_back({"nbGetParamAvg", [](Gen& g) {
        int32_t side = g.range(0, 1), stat = g.range(0, 5);
        return Pair{[=] { return norm(ps2CombatParameterAverage_002698C0(FW_MAIN, sx(side), sx(stat))); },
                    [=] { return norm(nb::averageParam(mainData(), static_cast<nb::Side>(side), static_cast<Param>(stat))); }};
    }});
    t.push_back({"nbGetParamAvg2", [](Gen& g) {
        int32_t side = g.range(0, 1), stat = g.range(0, 5);
        return Pair{[=] { return norm(ps2CombatEncounterParameterAverage_002699B0(FW_MAIN, sx(side), sx(stat))); },
                    [=] { return norm(nb::averageEncounterParam(mainData(), static_cast<nb::Side>(side), static_cast<Param>(stat))); }};
    }});
    t.push_back({"nbCheckSensei", [](Gen&) {
        return Pair{[] { return norm(ps2CombatCheckPlayerInitiative_00269AD8(FW_MAIN)); },
                    [] { return norm(nb::rollEnemiesFirst(mainData())); }};
    }});
    t.push_back({"nbCheckBackAttack", [](Gen&) {
        return Pair{[] { return norm(ps2CombatCheckEnemyInitiative_00269D20(FW_MAIN)); },
                    [] { return norm(nb::rollBackAttack(mainData())); }};
    }});
    t.push_back({"nbCheckEscape", [](Gen&) {
        return Pair{[] { return norm(ps2CombatCheckEscape_00269E98(FW_MAIN)); },
                    [] { return norm(nb::rollEscape(mainData())); }};
    }});
    t.push_back({"nbCheckRenzokuEncount", [](Gen&) {
        return Pair{[] { return norm(ps2CombatCheckConsecutiveEncounter_0026A158(FW_MAIN)); },
                    [] { return norm(nb::rollConsecutiveEncounter(mainData())); }};
    }});
    t.push_back({"nbCheckSingleTargetSkill", [](Gen& g) {
        int32_t skill = randomSkill(g);
        return Pair{[=] { return norm(ps2CombatSingleTargetSkill_0026A448(sx(skill))); },
                    [=] { return norm(nb::isSingleTargetSkill(skill)); }};
    }});
    t.push_back({"nbCheckFormationFriend", [](Gen& g) {
        int32_t a = g.range(0, 13), b = g.range(0, 13);
        return Pair{[=] { return norm(ps2CombatSameFormation_0026A470(sx(a), sx(b))); }, [=] { return norm(nb::sameSide(a, b)); }};
    }});
    t.push_back({"nbGetMakaBaramaki", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        return Pair{[=] { return norm(ps2CombatScatteredMoney_0026A4B0(unit)); },
                    [=] { return norm(nb::scatteredMacca(unitAt(unit))); }};
    }});
    t.push_back({"nbCheckBadPanicAction", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        return Pair{[=] { return norm(ps2CombatCheckPanicAction_0026A688(unit)); },
                    [=] { return norm(nb::rollPanicAction(unitAt(unit))); }};
    }});
    t.push_back({"nbCheckBadStatusGameOver", [](Gen& g) {
        for (int f = 0; f < 4; ++f)
            if (formUnit(f) && g.chance(70)) unitAt(formUnit(f)).badstat = 0x400;
        return Pair{[] { return norm(ps2CombatCheckStatusGameOver_0026A6D8()); }, [] { return norm(nb::isPartyPetrified()); }};
    }});
    t.push_back({"nbSetHpScale", [](Gen& g) {
        uint32_t form = FW_FORMS + 0xf0 * static_cast<uint32_t>(g.range(0, 13));
        return Pair{[=] { ps2CombatSetHpModelScale_0026A740(form); return uint64_t{0}; },
                    [=] { nb::updateHpModelScale(at<nb::Formation>(form)); return uint64_t{0}; }};
    }});
    t.push_back({"nbGetCriticalPow", [](Gen& g) {
        int32_t s = g.range(0, 13);
        float power = static_cast<float>(g.range(0, 100000)) / 7.0f;
        return Pair{[=] { return floatBits(ps2CombatCriticalPower_0026A828(sx(s), power)); },
                    [=] { return uint64_t{nb::criticalPower(s, power).bits()}; }};
    }});
    t.push_back({"nbGetKakutokuExp", [](Gen&) {
        return Pair{[] { return norm(ps2CombatEarnedExperience_0026A840(FW_MAIN)); }, [] { return norm(nb::earnedExp(mainData())); }};
    }});
    t.push_back({"nbGetKakutokuMaka", [](Gen&) {
        return Pair{[] { return norm(ps2CombatEarnedMoney_0026A870(FW_MAIN)); }, [] { return norm(nb::earnedMacca(mainData())); }};
    }});
    t.push_back({"setEncounter (0x259658)", [](Gen& g) {
        int32_t id = g.range(0, 1279);
        return Pair{[=] { ps2CombatSetEncounter_00259658(sx(id)); return uint64_t{0}; },
                    [=] { nb::setEncounter(id); return uint64_t{0}; }};
    }});
    t.push_back({"unitVisual (0x259A60)", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        return Pair{[=] { return norm(ps2CombatModelScaleDescriptor_00259A60(unit)); },
                    [=] { return norm(static_cast<int32_t>(guest::addressOf(&nb::unitVisual(unitAt(unit))))); }};
    }});

    // ---- datCalc: unit stats -------------------------------------------------
    auto unitTest = [&t](const char* name, auto legacy, auto rewrite) {
        t.push_back({name, [=](Gen& g) {
            uint32_t unit = formUnit(occupiedForm(g));
            int32_t stat = g.range(0, 5);
            return Pair{[=] { return legacy(unit, stat); }, [=] { return rewrite(unitAt(unit), stat); }};
        }});
    };
    unitTest("datGetBaseParam", [](uint32_t u, int32_t s) { return norm(datGetBaseParam(legacyUnit(u), s)); },
             [](UnitWork& u, int32_t s) { return norm(dat::baseParam(u, static_cast<Param>(s))); });
    unitTest("datGetParam", [](uint32_t u, int32_t s) { return norm(datGetParam(legacyUnit(u), s)); },
             [](UnitWork& u, int32_t s) { return norm(dat::param(u, static_cast<Param>(s))); });
    unitTest("datGetNormalAtkPow", [](uint32_t u, int32_t) { return norm(datGetNormalAtkPow(u)); },
             [](UnitWork& u, int32_t) { return norm(dat::attackPower(u)); });
    unitTest("datGetDefPow", [](uint32_t u, int32_t) { return norm(datGetDefPow(u)); },
             [](UnitWork& u, int32_t) { return norm(dat::defensePower(u)); });
    unitTest("datGetMagicHitPow", [](uint32_t u, int32_t) { return norm(ps2UnitMagicHitPower_00242CB0(u)); },
             [](UnitWork& u, int32_t) { return norm(dat::magicAccuracy(u)); });
    unitTest("datGetSakePow", [](uint32_t u, int32_t) { return norm(ps2UnitEvasionPower_00242D50(u)); },
             [](UnitWork& u, int32_t) { return norm(dat::evasionPower(u)); });
    unitTest("datGetBaseMaxHp", [](uint32_t u, int32_t) { return norm(datGetBaseMaxHp(legacyUnit(u))); },
             [](UnitWork& u, int32_t) { return norm(dat::baseMaxHp(u)); });
    unitTest("datGetBaseMaxMp", [](uint32_t u, int32_t) { return norm(datGetBaseMaxMp(legacyUnit(u))); },
             [](UnitWork& u, int32_t) { return norm(dat::baseMaxMp(u)); });
    unitTest("datGetMaxHp", [](uint32_t u, int32_t) { return uint64_t{datGetMaxHp(legacyUnit(u))}; },
             [](UnitWork& u, int32_t) { return uint64_t{dat::maxHp(u)}; });
    unitTest("datGetMaxMp", [](uint32_t u, int32_t) { return uint64_t{datGetMaxMp(legacyUnit(u))}; },
             [](UnitWork& u, int32_t) { return uint64_t{dat::maxMp(u)}; });
    unitTest("datGetRace", [](uint32_t u, int32_t) { return norm(datGetRace(legacyUnit(u))); },
             [](UnitWork& u, int32_t) { return norm(static_cast<int32_t>(dat::race(u))); });
    unitTest("datGet3Zokusei", [](uint32_t u, int32_t) { return norm(datGet3Zokusei(u)); },
             [](UnitWork& u, int32_t) { return norm(dat::alignment(u)); });
    unitTest("datCheckDying", [](uint32_t u, int32_t) { return norm(datCheckDying(legacyUnit(u))); },
             [](UnitWork& u, int32_t) { return norm(dat::isDying(u)); });
    t.push_back({"datGetPlayerLevel", [](Gen&) {
        return Pair{[] { return norm(datGetPlayerLevel()); }, [] { return norm(dat::playerLevel()); }};
    }});
    t.push_back({"datGetAisyo", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        int32_t attr = g.range(-1, 15);
        return Pair{[=] { return norm(datGetAisyo(unit, sx(attr))); },
                    [=] { return norm(static_cast<int32_t>(dat::affinity(unitAt(unit), static_cast<Attribute>(attr)))); }};
    }});
    t.push_back({"datCheckSyojiSkill", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        UnitWork& u = unitAt(unit);
        int32_t skill = g.chance(50) && u.skillcnt ? u.skill[g.below(u.skillcnt)] : interestingSkill(g);
        return Pair{[=] { return norm(datCheckSyojiSkill(legacyUnit(unit), static_cast<uint32_t>(skill))); },
                    [=] { return norm(dat::hasSkill(unitAt(unit), skill)); }};
    }});
    t.push_back({"datCheckSkillInParty", [](Gen& g) {
        int32_t skill = interestingSkill(g);
        return Pair{[=] { return norm(datCheckSkillInParty(skill)); }, [=] { return norm(dat::partyHasSkill(skill)); }};
    }});
    auto ailmentWrite = [&t](const char* name, void (*legacy)(datUnitWork_PS2*, uint32_t), void (*rewrite)(UnitWork&, uint32_t)) {
        t.push_back({name, [=](Gen& g) {
            uint32_t unit = formUnit(occupiedForm(g));
            uint32_t bad = g.chance(15) ? 0x8000u : (g.chance(80) ? g.pick(kAilments) : g.below(0x10000));
            return Pair{[=] { legacy(legacyUnit(unit), bad); return uint64_t{0}; },
                        [=] { rewrite(unitAt(unit), bad); return uint64_t{0}; }};
        }});
    };
    ailmentWrite("datSetBadStat", datSetBadStat, dat::setAilment);
    ailmentWrite("datResetBadStat", datResetBadStat, dat::clearAilment);
    ailmentWrite("datOverwriteBadStat", datOverwriteBadStat, dat::overwriteAilment);
    t.push_back({"datGetBadStatusAttr", [](Gen& g) {
        int32_t bad = g.chance(70) ? (1 << g.range(0, 15)) : g.range(-2, 0x5000);
        return Pair{[=] { return norm(datGetBadStatusAttr(bad)); },
                    [=] { return norm(static_cast<int32_t>(dat::ailmentElement(static_cast<uint32_t>(bad)))); }};
    }});
    t.push_back({"datAddHp", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        int32_t amount = g.range(-1200, 1200);
        return Pair{[=] { return uint64_t{datAddHp(legacyUnit(unit), amount)}; }, [=] { return uint64_t{dat::addHp(unitAt(unit), amount)}; }};
    }});
    t.push_back({"datAddMp", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        int32_t amount = g.range(-1200, 1200);
        return Pair{[=] { return uint64_t{datAddMp(legacyUnit(unit), amount)}; }, [=] { return uint64_t{dat::addMp(unitAt(unit), amount)}; }};
    }});

    // ---- nbCalc: combatant queries ---------------------------------------------
    t.push_back({"nbGetBadStat", [](Gen& g) {
        int32_t f = g.range(0, 15);
        return Pair{[=] { return norm(nbGetBadStat(sx(f))); }, [=] { return uint64_t{nb::badStat(f)}; }};
    }});
    t.push_back({"nbGetNormalSkillAttr", [](Gen& g) {
        int32_t skill = g.range(0, 0x1ff);
        return Pair{[=] { return norm(nbGetNormalSkillAttr(sx(skill))); },
                    [=] { return norm(static_cast<int32_t>(nb::skillAttribute(skill))); }};
    }});
    t.push_back({"nbCheckFormationPlayerSide", [](Gen& g) {
        int32_t f = g.range(-3, 15);
        return Pair{[=] { return norm(nbCheckFormationPlayerSide(sx(f))); }, [=] { return norm(nb::isPlayerSide(f)); }};
    }});
    t.push_back({"nbHatudoCheckSkill", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        UnitWork& u = unitAt(unit);
        int32_t skill = g.chance(30) ? (g.chance(50) ? skill::BrightMight : skill::DarkMight)
                      : g.chance(50) && u.skillcnt ? u.skill[g.below(u.skillcnt)] : interestingSkill(g);
        return Pair{[=] { return norm(nbHatudoCheckSkill(legacyUnit(unit), skill)); },
                    [=] { return norm(nb::passiveActive(unitAt(unit), skill)); }};
    }});
    t.push_back({"nbGetDevilFormatFlag", [](Gen& g) {
        int32_t f = g.range(0, 15);
        return Pair{[=] { return norm(nbGetDevilFormatFlag(sx(f))); },
                    [=] { return norm(static_cast<int32_t>(nb::devilFormatFlag(f))); }};
    }});
    t.push_back({"nbGetUnitID", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        return Pair{[=] { return norm(nbGetUnitID(unit)); }, [=] { return norm(nb::unitModelId(unitAt(unit))); }};
    }});
    t.push_back({"nbCheckKuisibariSkill", [](Gen& g) {
        int32_t f = occupiedForm(g);
        if (g.chance(50)) { UnitWork& u = unitAt(formUnit(f)); u.skill[0] = skill::Endure; if (!u.skillcnt) u.skillcnt = 1; }
        return Pair{[=] { return norm(nbCheckKuisibariSkill(sx(f))); }, [=] { return norm(nb::checkEndure(f)); }};
    }});
    t.push_back({"nbCheckKuisibari2Skill", [](Gen& g) {
        int32_t f = occupiedForm(g);
        if (g.chance(50)) { UnitWork& u = unitAt(formUnit(f)); u.skill[0] = skill::NeverYield; if (!u.skillcnt) u.skillcnt = 1; }
        return Pair{[=] { return norm(nbCheckKuisibari2Skill(sx(f))); }, [=] { return norm(nb::checkNeverYield(f)); }};
    }});
    t.push_back({"nbSetKuisibariStop", [](Gen& g) {
        int32_t f = g.range(0, 15);
        return Pair{[=] { nbSetKuisibariStop(sx(f)); return uint64_t{0}; }, [=] { nb::markEndureUsed(f); return uint64_t{0}; }};
    }});

    // ---- nbCalc: buffs ---------------------------------------------------------
    t.push_back({"nbGetHojoCounter", [](Gen& g) {
        int32_t f = g.range(0, 15), type = g.range(0, 19);
        return Pair{[=] { return norm(nbGetHojoCounter(sx(f), sx(type))); }, [=] { return norm(nb::buffCounter(f, type)); }};
    }});
    t.push_back({"nbSetHojoCounter", [](Gen& g) {
        int32_t f = g.range(0, 15), type = g.range(0, 19), value = g.range(-40000, 40000);
        return Pair{[=] { nbSetHojoCounter(sx(f), sx(type), sx(value)); return uint64_t{0}; },
                    [=] { nb::setBuffCounter(f, type, value); return uint64_t{0}; }};
    }});
    t.push_back({"nbGetHojoCounterMax", [](Gen& g) {
        int32_t type = g.range(-2, 22);
        return Pair{[=] { return norm(nbGetHojoCounterMax(sx(type))); }, [=] { return norm(nb::buffMax(type, 0)); }};
    }});
    t.push_back({"nbGetHojoCounterMin", [](Gen& g) {
        int32_t type = g.range(-2, 22);
        return Pair{[=] { return norm(nbGetHojoCounterMin(sx(type))); }, [=] { return norm(nb::buffMin(type, 0)); }};
    }});
    t.push_back({"nbSetHojoAddCounter", [](Gen& g) {
        int32_t f = g.range(0, 15), type = g.range(0, 19), delta = g.range(-6, 6), preview = g.range(0, 1);
        return Pair{[=] { return norm(nbSetHojoAddCounter(sx(f), sx(type), sx(delta), sx(preview))); },
                    [=] { return norm(nb::addBuff(f, type, delta, preview != 0)); }};
    }});
    t.push_back({"nbSetHojoKouka", [](Gen& g) {
        int32_t f = g.range(0, 15), amount = g.range(-2, 4), preview = g.range(0, 1);
        uint32_t mask = static_cast<uint32_t>(g.rng()) & (g.chance(50) ? 0x10403ffu : 0x1ffffffu);
        return Pair{[=] { return norm(nbSetHojoKouka(sx(f), mask, sx(amount), sx(preview))); },
                    [=] { return norm(nb::applyBuffs(f, mask, amount, preview != 0)); }};
    }});
    t.push_back({"nbGetHojoRitu", [](Gen& g) {
        int32_t f = occupiedForm(g), type = g.range(4, 8);
        return Pair{[=] { return floatBits(nbGetHojoRitu(sx(f), sx(type))); },
                    [=] { return uint64_t{nb::buffMultiplier(f, type).bits()}; }};
    }});

    // ---- nbCalc: affinity -----------------------------------------------------
    t.push_back({"nbGetAisyo", [](Gen& g) {
        int32_t skill = g.chance(15) ? -1 : activeSkill(g), f = occupiedForm(g), attr = g.range(-1, 15);
        return Pair{[=] { return norm(nbGetAisyo(sx(skill), sx(f), sx(attr))); },
                    [=] { return norm(static_cast<int32_t>(nb::affinity(skill, f, static_cast<Attribute>(attr)).raw)); }};
    }});
    t.push_back({"nbGetVirtualAisyo", [](Gen& g) {
        int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        return Pair{[=] { return norm(nbGetVirtualAisyo(sx(skill), sx(s), sx(d))); },
                    [=] { return norm(static_cast<int32_t>(nb::virtualAffinity(skill, s, d))); }};
    }});
    t.push_back({"nbGetAisyoRitu", [](Gen& g) {
        int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        return Pair{[=] { return floatBits(nbGetAisyoRitu(sx(skill), sx(s), sx(d))); },
                    [=] { return uint64_t{nb::damageRatio(skill, s, d).bits()}; }};
    }});

    // ---- nbCalc: power, effects, ailments -------------------------------------
    auto powerTest = [&t](const char* name, uint64_t (*legacy)(uint64_t, uint64_t, uint64_t, uint64_t),
                          int32_t (*rewrite)(int32_t, int32_t, int32_t, int32_t)) {
        t.push_back({name, [=](Gen& g) {
            int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g), power = g.range(0, 300);
            return Pair{[=] { return norm(legacy(sx(skill), sx(s), sx(d), sx(power))); },
                        [=] { return norm(rewrite(skill, s, d, power)); }};
        }});
    };
    powerTest("nbGetButuriAttack", nbGetButuriAttack, nb::physicalPower);
    powerTest("nbGetButuriKaifuku", nbGetButuriKaifuku, nb::physicalHealPower);
    powerTest("nbGetMagicAttack", nbGetMagicAttack, nb::magicPower);
    powerTest("nbGetMagicKaifuku", nbGetMagicKaifuku, nb::magicHealPower);
    powerTest("nbGetMaxHpWazaPoint", nbGetMaxHpWazaPoint, nb::maxHpPower);

    auto effectTest = [&t](const char* name, uint64_t (*legacy)(float, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t),
                           int32_t (*rewrite)(ee::Float, bool, int32_t, int32_t, int32_t, int32_t)) {
        t.push_back({name, [=](Gen& g) {
            int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g), count = g.range(0, 4);
            int32_t damage = g.range(0, 1);
            float ratio = g.pick(kRatios);
            return Pair{[=] { return norm(legacy(ratio, sx(damage), sx(skill), sx(s), sx(d), sx(count))); },
                        [=] { return norm(rewrite(ratio, damage != 0, skill, s, d, count)); }};
        }});
    };
    effectTest("nbGetKoukaHp", nbGetKoukaHp, nb::hpEffect);
    effectTest("nbGetKoukaMp", nbGetKoukaMp, nb::mpEffect);

    auto ailmentTest = [&t](const char* name, uint64_t (*legacy)(float, uint64_t, uint64_t, uint64_t, uint64_t),
                            uint32_t (*rewrite)(ee::Float, int32_t, int32_t, int32_t, bool)) {
        t.push_back({name, [=](Gen& g) {
            int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g), preview = g.chance(20) ? 1 : 0;
            float ratio = g.pick(kRatios);
            return Pair{[=] { return norm(legacy(ratio, sx(skill), sx(s), sx(d), sx(preview))); },
                        [=] { return norm(static_cast<int32_t>(rewrite(ratio, skill, s, d, preview != 0))); }};
        }});
    };
    ailmentTest("nbGetKoukaBadDamage", nbGetKoukaBadDamage, nb::rollAilmentInflict);
    ailmentTest("nbGetKoukaBadKaifuku", nbGetKoukaBadKaifuku, nb::rollAilmentCure);

    // ---- nbCalc: skill costs, AI helpers ---------------------------------------
    t.push_back({"datGetSkillCost", [](Gen& g) {
        uint32_t unit = formUnit(occupiedForm(g));
        int32_t skill = activeSkill(g);
        return Pair{[=] { return norm(datGetSkillCost(unit, sx(skill))); }, [=] { return norm(dat::skillCost(unitAt(unit), skill)); }};
    }});
    t.push_back({"nbCheckSkillCost", [](Gen& g) {
        int32_t f = occupiedForm(g), skill = activeSkill(g);
        return Pair{[=] { return norm(nbCheckSkillCost(sx(f), sx(skill))); },
                    [=] { return norm(static_cast<int32_t>(nb::checkSkillCost(f, skill))); }};
    }});
    t.push_back({"nbCheckSkillUse", [](Gen& g) {
        int32_t f = occupiedForm(g), skill = activeSkill(g);
        return Pair{[=] { return norm(nbCheckSkillUse(sx(f), sx(skill))); }, [=] { return norm(nb::checkSkillUse(f, skill)); }};
    }});
    t.push_back({"nbGetLvAvg", [](Gen& g) {
        int32_t side = g.range(0, 1);
        return Pair{[=] { return norm(nbGetLvAvg(FW_MAIN, sx(side))); },
                    [=] { return norm(nb::averageCombatLevel(mainData(), static_cast<nb::Side>(side))); }};
    }});
    t.push_back({"nbGetAisyoTable", [](Gen& g) {
        int32_t f = occupiedForm(g);
        return Pair{[=] { return norm(nbGetAisyoTable(sx(f))); }, [=] { return norm(nb::affinityRowOf(f)); }};
    }});
    t.push_back({"nbGetEscapeSwitch", [](Gen&) {
        return Pair{[] { return norm(nbGetEscapeSwitch(FW_MAIN)); }, [] { return norm(nb::escapeAllowed(mainData())); }};
    }});
    t.push_back({"nbGetVirtualKoukaPoint", [](Gen& g) {
        int32_t skill = activeSkill(g), s = occupiedForm(g), d = occupiedForm(g);
        return Pair{[=] { return norm(nbGetVirtualKoukaPoint(sx(skill), sx(s), sx(d))); },
                    [=] { return norm(nb::estimateEffect(skill, s, d)); }};
    }});

    // Every curing skill in the shipped data has badlevel 255 (always works),
    // so the cure-chance roll is dead in practice. Exercise it anyway by
    // patching a chance into the skill record for the duration of the call.
    t.push_back({"nbGetKoukaBadKaifuku (patched chance)", [](Gen& g) {
        int32_t s = occupiedForm(g), d = occupiedForm(g), preview = g.chance(10) ? 1 : 0;
        int32_t skill = 0x2c + static_cast<int32_t>(g.below(6));   // Me Patra .. Recarm
        uint8_t chance = static_cast<uint8_t>(g.range(1, 200));
        float ratio = g.pick(kRatios);
        auto patched = [=](auto call) {
            uint8_t& badlevel = const_cast<NormalSkill&>(dat::normalSkill(skill)).badlevel;
            uint8_t original = badlevel;
            badlevel = chance;
            uint64_t result = call();
            badlevel = original;
            return result;
        };
        return Pair{[=] { return patched([&] { return norm(nbGetKoukaBadKaifuku(ratio, sx(skill), sx(s), sx(d), sx(preview))); }); },
                    [=] { return patched([&] { return norm(static_cast<int32_t>(nb::rollAilmentCure(ratio, skill, s, d, preview != 0))); }); }};
    }});

    addFusionTests(t);
    addProgressionTests(t);
    addFusionCoreTests(t);
    addMagatamaTests(t);
    // The tests so far compare against the legacy C (US Maniax only); most
    // after run the executable's own instructions (ai_tests.cpp marks its own).
    for (TestCase& c : t)
        c.legacyC = true;
    addCalcInstructionTests(t);
    addAiTests(t);
    addMessageTests(t);
    addFontTests(t);
    addPanelTests(t);
    addScriptTests(t);
    addDataTests(t);
    addKoukaTests(t);
    addVariantTests(t);
    return t;
}

} // namespace

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::fprintf(stderr, "usage: %s <SLUS_209.11> [cases] [seed]\n", argv[0]);
        return 2;
    }
    std::setvbuf(stdout, nullptr, _IONBF, 0);   // results survive a run that stops
    if (!difftest::version::load(argv[1]))
        return 2;
    if (!fw_load_elf(argv[1])) {
        std::fprintf(stderr, "cannot load %s\n", argv[1]);
        return 2;
    }
    iface::loadData(argv[1]);
    int cases = argc > 2 ? std::atoi(argv[2]) : 2000;
    uint64_t seed = argc > 3 ? std::strtoull(argv[3], nullptr, 0) : 1;
    const char* filter = argc > 4 ? argv[4] : "";
#pragma warning(suppress : 4996)
    const bool verbose = std::getenv("DIFF_VERBOSE") != nullptr;   // name each test as it starts
#pragma warning(suppress : 4996)
    const bool verboseCases = verbose && std::strcmp(std::getenv("DIFF_VERBOSE"), "2") == 0;   // ... and each case
    // DIFF_SKIP: test names to leave out, comma-separated (a version's tests
    // that still compare against US Maniax's legacy C).
#pragma warning(suppress : 4996)
    const std::string skip = std::string(",") + (std::getenv("DIFF_SKIP") ? std::getenv("DIFF_SKIP") : "") + ",";
    // Tests of functions Hardtype patches that the port doesn't follow yet
    // (or whose generators write US Maniax's record layouts): they differ
    // or crash against Hardtype's instructions. source/hardtype/README.md.
    static const std::vector<const char*> kHardtypePending = {};
    // DIFF_PENDING: run them anyway.
#pragma warning(suppress : 4996)
    volatile bool hardtype = nocturne::kVariant == nocturne::Variant::Hardtype && !std::getenv("DIFF_PENDING");
#pragma warning(suppress : 4996)
    const bool runPending = std::getenv("DIFF_PENDING") != nullptr;
    volatile bool japanese =
        !nocturne::kBuild.us && !runPending;
    // Tests of what the JP builds change that the port doesn't follow yet
    // (docs/versions.md).
    static const std::vector<const char*> kJapanesePending = {
    };
    // ... and of what the Chronicle Edition changes on top.
    static const std::vector<const char*> kChroniclePending = {
    };
    volatile bool chronicle = nocturne::kVariant == nocturne::Variant::Chronicle && !runPending;
    auto listed = [](const std::vector<const char*>& list, const char* name) {
        for (const char* p : list) {   // a trailing * matches the prefix
            const size_t n = std::strlen(p);
            if (p[n - 1] == '*' ? std::strncmp(p, name, n - 1) == 0 : std::strcmp(p, name) == 0)
                return true;
        }
        return false;
    };
    auto pending = [&](const TestCase& test) {
        if (japanese && listed(kJapanesePending, test.name))
            return true;
        return (hardtype && listed(kHardtypePending, test.name)) || (chronicle && listed(kChroniclePending, test.name));
    };

    std::vector<uint8_t> saved(dynamicEnd() - FW_DYNAMIC_BEGIN);
    // The executable's image as loaded: each test starts from it, so what
    // one test's worlds leave in static memory can't reach the next.
    const std::vector<uint8_t> pristine(fw_ram, fw_ram + FW_DYNAMIC_BEGIN);
    int failedFunctions = 0, skippedTests = 0, pendingTests = 0;
    // DIFF_RESULTS=<file>: each test's outcome, one "name<TAB>outcome" line
    // (ok, differ, pending, or legacy: a test of US Maniax's legacy C another
    // version skips), for tools/function_map.py's per-build columns.
#pragma warning(suppress : 4996)
    const char* resultsPath = std::getenv("DIFF_RESULTS");
#pragma warning(suppress : 4996)
    FILE* results = resultsPath ? std::fopen(resultsPath, "w") : nullptr;
    auto record = [&](const TestCase& test, const char* outcome) {
        if (results)
            std::fprintf(results, "%s\t%s\n", test.name, outcome);
    };
    // Another version than US Maniax (a variable, so the checks below aren't constant).
    volatile bool otherVersion = nocturne::kVariant != nocturne::Variant::Us;
    for (const TestCase& test : tests()) {
        if (!std::strstr(test.name, filter) || skip.find("," + std::string(test.name) + ",") != std::string::npos)
            continue;
        if (otherVersion && test.legacyC) {
            ++skippedTests;
            record(test, "legacy");
            continue;
        }
        if (pending(test)) {
            ++pendingTests;
            record(test, "pending");
            continue;
        }
        std::memcpy(fw_ram, pristine.data(), pristine.size());
        if (verbose)
            std::fprintf(stderr, "running %s\n", test.name);
        int failures = 0, traps = 0;
        uint64_t draws = 0;
        bool skippedLegacy = false;
        bool usText = false;   // it set up the US font and message engine (version_map.hpp)
        std::optional<difftest::version::NoCounterpart> missing;   // it reached what the version lacks
        for (int i = 0; i < cases; ++i) {
            uint64_t caseSeed = seed * 1000003u + static_cast<uint64_t>(i);
            if (verboseCases)
                std::fprintf(stderr, "  case %d (seed %llu)\n", i, (unsigned long long)caseSeed);
            Gen g{std::mt19937_64(caseSeed)};
            randomWorld(g);
            Pair pair;
            try {
                pair = test.make(g);
            } catch (const difftest::version::UsTextOnly&) {
                usText = true;
                break;
            } catch (const difftest::version::NoCounterpart& e) {
                missing = e;
                break;
            }
            int normal = g.chance(50) ? 1 : 0;
            uint32_t moon = g.chance(30) ? kMoonFull : g.below(16);
            std::memcpy(saved.data(), fw_ram + FW_DYNAMIC_BEGIN, saved.size());
            std::vector<uint8_t> statics = captureStatics();

            const uint64_t interpreted = iface::interpretedCalls();
            Outcome legacy;
            try {
                legacy = run(pair.legacy, caseSeed, normal, moon);
            } catch (const difftest::version::NoCounterpart& e) {
                missing = e;
                break;
            }
            // Another version's build: a test against US Maniax's legacy C
            // (its first case runs no instructions) says nothing about it.
            if (otherVersion && i == 0 && iface::interpretedCalls() == interpreted) {
                skippedLegacy = true;
                break;
            }
            std::memcpy(fw_ram + FW_DYNAMIC_BEGIN, saved.data(), saved.size());
            restoreStatics(statics);
            resetLeftRegisters();
            Outcome rewrite;
            try {
                rewrite = run(pair.rewrite, caseSeed, normal, moon);
            } catch (const difftest::version::NoCounterpart& e) {
                missing = e;
                break;
            }
            restoreStatics(statics);

            traps += legacy.trap != 0;
            draws += legacy.trace.rng_count;
            std::string diff = describe(legacy, rewrite);
            if (!diff.empty() && failures++ < 3)
                std::printf("  FAIL %s case %d (seed %llu): %s\n", test.name, i, (unsigned long long)caseSeed, diff.c_str());
        }
        if (skippedLegacy) {
            ++skippedTests;
            record(test, "legacy");
            continue;
        }
        if (usText) {
            ++pendingTests;
            record(test, "pending");
            continue;
        }
        if (missing) {
            std::printf("%-26s pending: no counterpart for US Maniax's %s at %08x\n", test.name,
                        missing->code ? "code" : "data", missing->maniax);
            ++pendingTests;
            record(test, "pending");
            continue;
        }
        record(test, failures ? "differ" : "ok");
        std::printf("%-26s %s  %d cases, %llu RNG draws, %d traps\n", test.name,
                    failures ? "FAIL" : "ok  ", cases, (unsigned long long)draws, traps);
        failedFunctions += failures != 0;
    }
    if (skippedTests)
        std::printf("(%d test(s) against US Maniax's legacy C skipped for this version)\n", skippedTests);
    if (pendingTests)
        std::printf("(%d test(s) of what this version changes, still to port, skipped)\n", pendingTests);
    if (results)
        std::fclose(results);
    std::printf("%s: %d function(s) differ\n", failedFunctions ? "FAILED" : "PASSED", failedFunctions);
    return failedFunctions ? 1 : 0;
}
