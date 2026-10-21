// Differential test: rewritten nb::calc vs. the legacy combat_calculation.c.
//
// For every case, a random battle state is written into fake PS2 RAM. The
// legacy function runs, then the state is restored and the rewrite runs.
// The two must agree on the return value, any trap, the RNG draws, the debug
// prints and every byte of dynamic RAM.
//
// usage: differential <path to SLUS_209.11> [cases per function] [seed]
#include <csetjmp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <random>
#include <string>
#include <vector>

#include "fake_world.h"
#include "nocturne/battle/calc.hpp"
#include "nocturne/data/tables.hpp"

extern "C" {
#include "combat_calculation.h"
}

using namespace nocturne;

// ---- platform hooks for the rewrite -------------------------------------------

void* nocturne::guest::resolve(uint32_t address) { return fw_resolve(address); }
uint32_t nocturne::guest::addressOf(const void* pointer) { return fw_address_of(pointer); }

namespace {

template <class T> T& at(uint32_t address) { return *static_cast<T*>(fw_resolve(address)); }

uint64_t floatBits(float f) { uint32_t b; std::memcpy(&b, &f, 4); return b; }
uint64_t norm(uint64_t legacyRegister) { return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(legacyRegister))); }
uint64_t norm(int32_t value) { return static_cast<uint64_t>(static_cast<int64_t>(value)); }
uint64_t norm(bool value) { return value ? 1 : 0; }

// ---- random battle states -------------------------------------------------------

struct Gen {
    std::mt19937_64 rng;
    uint32_t below(uint32_t n) { return static_cast<uint32_t>(rng() % n); }
    int32_t range(int32_t lo, int32_t hi) { return lo + static_cast<int32_t>(below(static_cast<uint32_t>(hi - lo + 1))); }
    bool chance(uint32_t percent) { return below(100) < percent; }
    template <class T, size_t N> T pick(const T (&values)[N]) { return values[below(N)]; }
};

const uint16_t kAilments[] = {0, 0, 0, 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800};

void randomUnit(Gen& g, UnitWork& u, bool enemy)
{
    std::memset(&u, 0, sizeof u);
    static const uint32_t kPlayerFlags[] = {1, 3, 3, 3, 7, 5, 0, 0x23};
    static const uint32_t kEnemyFlags[] = {0x21, 0x21, 0x23, 0x25, 0x01};
    u.flag = enemy ? g.pick(kEnemyFlags) : g.pick(kPlayerFlags);
    u.id = static_cast<uint16_t>(g.range(1, 0x17f));
    u.maxhp = static_cast<uint16_t>(g.range(1, 999));
    u.hp = static_cast<uint16_t>(g.chance(10) ? 0 : g.range(0, u.maxhp));
    u.maxmp = static_cast<uint16_t>(g.range(0, 500));
    u.mp = static_cast<uint16_t>(g.range(0, u.maxmp));
    u.badstat = g.pick(kAilments) | (g.chance(10) ? 0x8000 : 0);
    u.level = static_cast<uint16_t>(g.range(1, 99));
    for (int i = 0; i < 6; ++i) {
        u.param[i] = static_cast<int8_t>(g.range(0, 40));
        u.mitamaparam[i] = static_cast<int8_t>(g.range(0, 5));
    }
}

void randomWorld(Gen& g)
{
    std::memset(fw_ram + FW_DYNAMIC_BEGIN, 0, FW_DYNAMIC_END - FW_DYNAMIC_BEGIN);
    at<uint32_t>(dat::address::GlobalWorkPointer) = FW_GLOBAL;

    GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
    global.maka = g.range(0, 999999);
    global.unknown_0a4c = g.below(4);
    for (int i = 0; i < 16; ++i)
        randomUnit(g, global.units[i], false);
    global.units[0].flag = 7; // the Demi-fiend

    // Formation slots: 0..3 the party, 4..13 enemies; some slots empty.
    auto* formUnits = &at<uint32_t>(FW_FORM_UNITS);
    for (int f = 0; f < 14; ++f) {
        bool empty = f > 0 && g.chance(15);
        if (f < 4) {
            formUnits[f] = empty ? 0 : FW_GLOBAL + 0xa54 + 0xec * static_cast<uint32_t>(f == 0 ? 0 : g.range(1, 15));
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
        party[f].flag = flag;
        party[f].formindex = static_cast<int16_t>(f);
    }

    nb::MainProcessData& data = at<nb::MainProcessData>(FW_MAIN);
    data.form.address = FW_FORMS;
    data.party.address = FW_PARTY;
    data.encpackno = g.chance(15) ? 0 : g.range(1, 39);
    data.packno = g.range(0, 3);
    data.packindex = g.range(0, 11);
    static const int32_t kSpecialEncounters[] = {0, 0x10b, 0x11c, 0x149, 0x408, -1};
    data.encno = g.chance(10) ? g.pick(kSpecialEncounters) : g.range(1, 1279);
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
    data.maka = static_cast<uint32_t>(g.range(0, 30000));
    data.exp = static_cast<uint32_t>(g.range(0, 40000));
    data.previndex = 7;
    data.turn = 3;

    nb::ActionProcessData& action = at<nb::ActionProcessData>(FW_ACTION);
    action.data.address = FW_MAIN;
    action.autoskill = -1;
}

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
    static const int32_t kSpecial[] = {0, 0, 0, Skill::HolyMelody, Skill::EvilMelody, 0xbe, 0xc7, 0xd4};
    return g.chance(35) ? g.pick(kSpecial) : g.range(0, 0x17f);
}

// ---- running a case ---------------------------------------------------------------

struct Outcome {
    int trap = 0;
    uint64_t result = 0;
    fw_trace trace{};
    std::vector<uint8_t> ram;
};

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
    out.ram.assign(fw_ram + FW_DYNAMIC_BEGIN, fw_ram + FW_DYNAMIC_END);
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
    if (a.trace.print_count != b.trace.print_count) { std::snprintf(buffer, sizeof buffer, "%u vs %u prints", a.trace.print_count, b.trace.print_count); return buffer; }
    for (uint32_t i = 0; i < a.trace.print_count && i < FW_MAX_TRACE; ++i) {
        if (a.trace.print_format[i] != b.trace.print_format[i]) { std::snprintf(buffer, sizeof buffer, "print %u: format %08x vs %08x", i, a.trace.print_format[i], b.trace.print_format[i]); return buffer; }
        for (int k = 0; k < fw_print_arg_count(a.trace.print_format[i]); ++k)
            if (a.trace.print_args[i][k] != b.trace.print_args[i][k]) { std::snprintf(buffer, sizeof buffer, "print %u arg %d: %lld vs %lld", i, k, (long long)a.trace.print_args[i][k], (long long)b.trace.print_args[i][k]); return buffer; }
    }
    for (size_t i = 0; i < a.ram.size(); ++i)
        if (a.ram[i] != b.ram[i]) { std::snprintf(buffer, sizeof buffer, "RAM %08zx: %02x vs %02x", FW_DYNAMIC_BEGIN + i, a.ram[i], b.ram[i]); return buffer; }
    return {};
}

struct Pair {
    std::function<uint64_t()> legacy, rewrite;
};

struct TestCase {
    const char* name;
    std::function<Pair(Gen&)> make;
};

uint64_t sx(int32_t v) { return static_cast<uint64_t>(static_cast<int64_t>(v)); }

nb::MainProcessData& mainData() { return at<nb::MainProcessData>(FW_MAIN); }
UnitWork& unitAt(uint32_t address) { return at<UnitWork>(address); }
uint32_t formUnit(int f) { return at<uint32_t>(FW_FORM_UNITS + 4 * static_cast<uint32_t>(f)); }

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
    return t;
}

} // namespace

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::fprintf(stderr, "usage: %s <SLUS_209.11> [cases] [seed]\n", argv[0]);
        return 2;
    }
    if (!fw_load_elf(argv[1])) {
        std::fprintf(stderr, "cannot load %s\n", argv[1]);
        return 2;
    }
    int cases = argc > 2 ? std::atoi(argv[2]) : 2000;
    uint64_t seed = argc > 3 ? std::strtoull(argv[3], nullptr, 0) : 1;

    std::vector<uint8_t> saved(FW_DYNAMIC_END - FW_DYNAMIC_BEGIN);
    int failedFunctions = 0;
    for (const TestCase& test : tests()) {
        int failures = 0, traps = 0;
        uint64_t draws = 0;
        for (int i = 0; i < cases; ++i) {
            uint64_t caseSeed = seed * 1000003u + static_cast<uint64_t>(i);
            Gen g{std::mt19937_64(caseSeed)};
            randomWorld(g);
            Pair pair = test.make(g);
            int normal = g.chance(50) ? 1 : 0;
            uint32_t moon = g.chance(30) ? kMoonFull : g.below(16);
            std::memcpy(saved.data(), fw_ram + FW_DYNAMIC_BEGIN, saved.size());

            Outcome legacy = run(pair.legacy, caseSeed, normal, moon);
            std::memcpy(fw_ram + FW_DYNAMIC_BEGIN, saved.data(), saved.size());
            Outcome rewrite = run(pair.rewrite, caseSeed, normal, moon);

            traps += legacy.trap != 0;
            draws += legacy.trace.rng_count;
            std::string diff = describe(legacy, rewrite);
            if (!diff.empty() && failures++ < 3)
                std::printf("  FAIL %s case %d (seed %llu): %s\n", test.name, i, (unsigned long long)caseSeed, diff.c_str());
        }
        std::printf("%-26s %s  %d cases, %llu RNG draws, %d traps\n", test.name,
                    failures ? "FAIL" : "ok  ", cases, (unsigned long long)draws, traps);
        failedFunctions += failures != 0;
    }
    std::printf("%s: %d function(s) differ\n", failedFunctions ? "FAILED" : "PASSED", failedFunctions);
    return failedFunctions ? 1 : 0;
}
