// The functions another version changes (variants/README.md), against the
// original instructions of whichever executable the test runs on. In the US
// Maniax build they check the base behaviour; in a version's build that
// version's, where the legacy-C tests of the same functions are skipped
// (variants/<name>/differential-skip.txt).
#include "harness.hpp"
#include "version_map.hpp"
#include "interface_world.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/battle/targeting.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/fusion/accident.hpp"
#include "nocturne/fusion/combine.hpp"
#include "nocturne/fusion/growth.hpp"
#include "nocturne/fusion/inheritance.hpp"
#include "nocturne/variant.hpp"

namespace difftest {

using namespace nocturne;
using iface::I;
using iface::origVm;

namespace {

// A unit in an occupied slot, as the battle world builds them.
uint32_t someUnit(Gen& g)
{
    for (;;) {
        const uint32_t unit = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(g.range(0, 13)));
        if (unit)
            return unit;
    }
}

// The bytes Hardtype's own code reads at fixed addresses (hardtype.hpp:
// the global work's moon phase, moon move bits and a Magatama where the game
// allocates it, and its option byte).
void hardtypeBytes(Gen& g)
{
    for (uint32_t address : {0x01248f41u, 0x01248f44u, 0x0124a213u, 0x002ff388u})
        at<uint8_t>(address) = static_cast<uint8_t>(g.below(256));
}

} // namespace

void addVariantTests(std::vector<TestCase>& t)
{
    auto add = [&](const char* name, std::function<Pair(Gen&)> body) {
        t.push_back({name, [body](Gen& g) {
                         hardtypeBytes(g);
                         return body(g);
                     }});
    };
    // A unit where the battle world keeps them, or copied above 0x1200000
    // (where the game's global work and its stock sit).
    auto placedUnit = [](Gen& g) {
        const uint32_t unit = someUnit(g);
        if (!g.chance(40))
            return unit;
        constexpr uint32_t kHigh = 0x01280000;
        at<UnitWork>(kHigh) = at<UnitWork>(unit);
        return kHigh;
    };
    add("datGetBaseParam (instructions)", [=](Gen& g) {
        const uint32_t unit = placedUnit(g);
        UnitWork& u = unitAt(unit);
        for (int k = 0; k < 6; ++k) {
            u.param[k] = static_cast<int8_t>(g.chance(20) ? g.range(-128, 127) : g.range(0, 60));
            u.mitamaparam[k] = static_cast<int8_t>(g.range(-5, 30));
            u.skillparam[k] = static_cast<int8_t>(g.range(-10, 10));
        }
        const int32_t stat = g.range(0, 5);
        return Pair{[=] { return origVm(0x00243e78, {unit, I(stat)}); },
                    [=] { return norm(dat::baseParam(unitAt(unit), static_cast<Param>(stat))); }};
    });
    add("datGetMagicHitPow (instructions)", [=](Gen& g) {
        const uint32_t unit = placedUnit(g);
        return Pair{[=] { return origVm(0x00242cb0, {unit}); }, [=] { return norm(dat::magicAccuracy(unitAt(unit))); }};
    });
    add("datGetSakePow (instructions)", [=](Gen& g) {
        const uint32_t unit = placedUnit(g);
        return Pair{[=] { return origVm(0x00242d50, {unit}); }, [=] { return norm(dat::evasionPower(unitAt(unit))); }};
    });
    add("datGetBaseMaxMp (instructions)", [=](Gen& g) {
        const uint32_t unit = placedUnit(g);
        unitAt(unit).level = static_cast<uint16_t>(g.chance(20) ? g.range(250, 400) : g.range(1, 99));
        return Pair{[=] { return origVm(0x00242ae8, {unit}); }, [=] { return norm(dat::baseMaxMp(unitAt(unit))); }};
    });
    add("datAddHp (instructions)", [=](Gen& g) {
        const uint32_t unit = placedUnit(g);
        const int32_t amount = g.range(-300, 300);
        return Pair{[=] { return origVm(0x00243e28, {unit, I(amount)}); }, [=] { return norm(static_cast<int32_t>(dat::addHp(unitAt(unit), amount))); }};
    });
    // (The enemies' units, where Hardtype finds them by their address.)
    auto skillUnit = [=](Gen& g) {
        const uint32_t unit = placedUnit(g);
        if (!g.chance(30))
            return unit;
        constexpr uint32_t kEnemyHeap = 0x01160400;
        at<UnitWork>(kEnemyHeap) = at<UnitWork>(unit);
        return kEnemyHeap;
    };
    add("datGetSkillCost (instructions)", [=](Gen& g) {
        const uint32_t unit = skillUnit(g);
        UnitWork& u = unitAt(unit);
        const int32_t skill = g.chance(50) ? g.range(1, 0x80) : g.range(0, 0x1ff);
        if (g.chance(40))
            u.skill[g.below(8)] = 0x179;
        u.maxhp = static_cast<uint16_t>(g.range(1, 9999));
        return Pair{[=] { return origVm(0x002459e8, {unit, I(skill)}); }, [=] { return norm(dat::skillCost(unitAt(unit), skill)); }};
    });
    // ---- battle ----
    add("nbGetTargetTypeRuleArea (instructions)", [=](Gen& g) {
        const uint32_t unit = someUnit(g);
        UnitWork& u = unitAt(unit);
        u.nowcommand = static_cast<int16_t>(g.range(-1, 7));
        u.nowindex = static_cast<uint16_t>(u.nowcommand == 5 ? g.range(1, 0x40) : g.chance(20) ? g.pick<int32_t>({0x45, 0x46}) : g.range(0, 0x11f));
        at<nb::ActionProcessData>(FW_ACTION).data.address = FW_MAIN;
        at<nb::MainProcessData>(FW_MAIN).stat ^= g.chance(50) ? 8u : 0u;
        const int32_t reverse = g.range(0, 1);
        const uint32_t out = FW_SCRATCH + 0x900;
        for (int k = 0; k < 3; ++k)
            at<uint32_t>(out + 4u * k) = 0x55555555u;
        return Pair{[=] { return iface::origVmVoid(0x00258de8, {FW_ACTION, unit, out, out + 4, out + 8, I(reverse)}); },
                    [=] {
                        nb::targetTypeRuleArea(at<nb::ActionProcessData>(FW_ACTION), unitAt(unit), &at<int32_t>(out), &at<int32_t>(out + 4),
                                               &at<int32_t>(out + 8), reverse != 0);
                        return uint64_t{0};
                    }};
    });
    // ---- fusion ----
    add("cmbChkEventDevil (instructions)", [](Gen& g) {
        const uint16_t devil = static_cast<uint16_t>(g.chance(60) ? dat::kEventDevilTbl[g.below(dat::kEventDevilCount)].devil : g.range(0, 383));
        return Pair{[=] { return origVm(0x001fd3b0, {devil}); }, [=] { return norm(cmb::isEventLocked(devil)); }};
    });
    add("cmbCalcIkenieExp (instructions)", [=](Gen& g) {
        const uint32_t result = someUnit(g), sacrifice = someUnit(g);
        unitAt(sacrifice).exp = g.chance(10) ? static_cast<int32_t>(g.rng()) : g.range(0, 3000000);
        unitAt(result).level = static_cast<uint16_t>(g.chance(10) ? g.range(240, 255) : g.range(1, 99));
        return Pair{[=] { return iface::origVmVoid(0x001fe880, {result, result, result, sacrifice}); },
                    [=] { cmb::addSacrificeExp(unitAt(result), unitAt(result), unitAt(result), unitAt(sacrifice)); return uint64_t{0}; }};
    });
    // A skill from the inheritance table, or any.
    auto inheritSkill = [](Gen& g) {
        return g.chance(70) ? dat::kInheritanceLevel[g.below(dat::kInheritanceLevelCount)].skillId()
                            : static_cast<uint16_t>(g.range(0, 0x1ff));
    };
    add("cmbGetKeisyoSkillLevel (instructions)", [=](Gen& g) {
        const uint16_t skill = inheritSkill(g);
        const uint32_t counter = g.chance(50) ? 0 : g.chance(80) ? static_cast<uint32_t>(g.range(0, 320)) : static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x00222bb0, {skill, I(static_cast<int32_t>(counter))}); },
                    [=] { return norm(int32_t{cmb::inheritLevel(skill, counter)}); }};
    });
    add("cmbCalcKeisyoSkillRate (instructions)", [=](Gen& g) {
        const uint32_t unit = someUnit(g);
        unitAt(unit).level = static_cast<uint16_t>(g.range(1, 99));
        const uint16_t skill = inheritSkill(g);
        return Pair{[=] { return origVm(0x00222bf0, {unit, skill}); }, [=] { return norm(int32_t{cmb::inheritRate(unitAt(unit), skill)}); }};
    });
    add("cmbGetMutationSkill (instructions)", [=](Gen& g) {
        const uint32_t unit = someUnit(g);
        unitAt(unit).level = static_cast<uint16_t>(g.range(1, 99));
        const uint16_t skill = g.chance(50) ? unitAt(unit).skill[g.below(8)] : inheritSkill(g);
        at<uint32_t>(difftest::version::dataOrDie(0x00529be0)) = static_cast<uint32_t>(g.rng());   // the RNG state's carry bit
        return Pair{[=] { return origVm(0x00223520, {skill, unit}); }, [=] { return norm(int32_t{cmb::mutationSkill(skill, unitAt(unit))}); }};
    });
    add("datGetItemSkillNo (instructions)", [](Gen& g) {
        const int32_t item = g.chance(10) ? 1 : g.range(0, 0x9f);
        return Pair{[=] { return origVm(0x00245c90, {I(item)}); }, [=] { return norm(dat::itemSkill(item)); }};
    });
}

} // namespace difftest
