// Differential tests for the fusion rules and cmbGetBirthDevil
// (rewrite: src/fusion/rules.cpp, combine.cpp; legacy: fusion_core.c).
#include <cstdint>
#include <cstring>
#include <utility>
#include <vector>

#include "harness.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/fusion/combine.hpp"
#include "nocturne/fusion/rules.hpp"

extern "C" {
uint64_t ps2FusionCore_001FD498(uint64_t p0);
uint64_t ps2FusionCore_001FD4E0(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3);
uint64_t ps2FusionCore_001FD538(uint64_t p0, uint64_t p1);
uint64_t ps2FusionCore_001FD610(uint64_t p0, uint64_t p1, uint64_t p2);
uint64_t ps2FusionCore_001FD708(uint64_t p0, uint64_t p1, uint64_t p2);
uint64_t ps2FusionCore_001FD730(uint64_t p0, uint64_t p1, uint64_t p2);
uint64_t ps2FusionCore_001FD878(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
uint64_t ps2FusionCore_001FDA08(uint64_t p0);
uint64_t ps2FusionCore_001FDAC0(uint64_t p0, uint64_t p1);
uint64_t ps2FusionCore_001FDCA0(uint64_t p0, uint64_t p1);
uint64_t ps2FusionCore_001FDD18(uint64_t p0, uint64_t p1);
uint64_t ps2FusionCore_001FDDE8(uint64_t p0, uint64_t p1, uint64_t p2);
uint64_t ps2FusionCore_001FDEC0(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3);
uint64_t ps2FusionCore_001FDF78(uint64_t p0, uint64_t p1);
void ps2FusionCore_001FE170(uint64_t p0, uint64_t p1, uint64_t p2);
uint64_t ps2FusionCore_001FE1A0(uint64_t p0, uint64_t p1);
uint64_t ps2FusionCore_001FE280(uint64_t p0);
uint64_t ps2FusionCore_001FE5F0(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3);
uint64_t ps2FusionCore_001FE690(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
void ps2FusionCore_001FE880(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3);
uint64_t ps2FusionCore_001FEA20(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
void ps2FusionCore_001FEB28(uint64_t p0, uint64_t p1);
void ps2FusionCore_001FEC40(uint64_t p0, uint64_t p1);
uint64_t ps2FusionCore_001FEC68(uint64_t p0, uint64_t p1);
uint64_t ps2FusionCore_001FF428(uint64_t p0);
void ps2FusionCore_001FF4D0(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);
uint64_t ps2FusionCore_001FF648(uint64_t p0);
uint64_t ps2FusionCore_001FF758(uint64_t p0, uint64_t p1, uint64_t p2);
uint64_t ps2FusionCore_001FF790(uint64_t p0, uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6, uint64_t p7);
}

namespace difftest {
namespace {

constexpr uint32_t kUnits = FW_GLOBAL + 0xa54;
constexpr uint32_t kResult = FW_ENEMIES;            // a spare unit for results
constexpr uint32_t kIds = FW_SCRATCH;               // uint16_t[3]
constexpr uint32_t kRaces = FW_SCRATCH + 8;         // uint8_t[3]
constexpr uint32_t kType = FW_SCRATCH + 12;         // uint8_t
constexpr uint32_t kList = FW_SCRATCH + 16;         // InheritedSkillList
constexpr uint32_t kInfo = FW_SCRATCH + 64;         // stockDevilInfo outputs

uint32_t unitAddress(int i) { return kUnits + 0xec * static_cast<uint32_t>(i); }
uint8_t raceOf(uint16_t devil) { return static_cast<uint8_t>(dat::devilFormat(devil).race); }

// Races only bosses have. An Element with one of these never returns on the
// PS2 either (cmbGetRankUpDownDevil with no shift), so keep them out.
bool ownable(uint16_t devil)
{
    uint8_t race = raceOf(devil);
    return race != 0 && race != 31 && !(race >= 33 && race != 38);
}

const std::vector<uint16_t>& devilsOfRace(uint8_t race)
{
    static std::vector<uint16_t> byRace[256];
    static bool built = false;
    if (!built) {
        for (uint16_t d = 1; d < 384; ++d)
            if (ownable(d)) byRace[raceOf(d)].push_back(d);
        built = true;
    }
    return byRace[race];
}

uint16_t devilOfRace(Gen& g, uint8_t race)
{
    const std::vector<uint16_t>& list = devilsOfRace(race);
    return list.empty() ? 1 : list[g.below(static_cast<uint32_t>(list.size()))];
}

// Fusion inputs: Elements, Mitamas, special pairs and patterns turn up often.
uint16_t fusionDevil(Gen& g)
{
    for (;;) {
        uint16_t d;
        switch (g.below(8)) {
        case 0: d = devilOfRace(g, static_cast<uint8_t>(Race::Element)); break;
        case 1: d = devilOfRace(g, static_cast<uint8_t>(Race::Mitama)); break;
        case 2: { const FusionPair& p = dat::kExtPatternTbl[g.below(3)]; d = g.chance(50) ? p.devil1 : p.devil2; break; }
        case 3: { const SacrificeDevilPattern& p = dat::kIkenieExtPatternDevTbl[g.below(7)]; d = g.pick({p.devil1, p.devil2, p.devil3}); break; }
        case 4: d = dat::kIkenieExtPatternDevRaceTbl[g.below(2)].devil; break;
        default: d = static_cast<uint16_t>(g.range(1, 383)); break;
        }
        if (ownable(d)) return d;
    }
}

// Three stock units set up as fusion inputs; sometimes a known pattern.
struct Inputs { uint32_t a, b, c; };
Inputs fusionInputs(Gen& g)
{
    Inputs in{unitAddress(g.range(1, 5)), unitAddress(g.range(6, 10)), unitAddress(g.range(11, 15))};
    UnitWork& a = unitAt(in.a);
    UnitWork& b = unitAt(in.b);
    UnitWork& c = unitAt(in.c);
    a.id = fusionDevil(g);
    b.id = fusionDevil(g);
    c.id = fusionDevil(g);
    switch (g.below(6)) {
    case 0: { const FusionPair& p = dat::kExtPatternTbl[g.below(3)]; a.id = p.devil1; b.id = p.devil2; break; }
    case 1: { const SacrificeDevilPattern& p = dat::kIkenieExtPatternDevTbl[g.below(7)]; a.id = p.devil1; b.id = p.devil2; c.id = p.devil3; break; }
    case 2: { const SacrificeDevilRacePattern& p = dat::kIkenieExtPatternDevRaceTbl[g.below(2)];
              a.id = p.devil; b.id = devilOfRace(g, p.race1); c.id = devilOfRace(g, p.race2); break; }
    case 3: { const SacrificeRacePattern& p = dat::kIkenieExtPatternTbl[0];
              a.id = devilOfRace(g, p.race1); b.id = devilOfRace(g, p.race2); c.id = devilOfRace(g, p.race3); break; }
    default: break;
    }
    for (UnitWork* u : {&a, &b, &c})
        if (g.chance(5)) u->id = devil::Metatron;
    if (g.chance(50)) std::swap(a.id, b.id);
    for (UnitWork* u : {&a, &b, &c}) {
        if (g.chance(10)) u->flag |= 0x1000;   // cursed
        u->level = static_cast<uint16_t>(g.range(1, 99));
    }
    return in;
}

// cmbGetBirthDevil's ids/races ordering, written to kIds/kRaces.
void writeOrder(const Inputs& in)
{
    const UnitWork& a = unitAt(in.a);
    const UnitWork& b = unitAt(in.b);
    auto* ids = &at<uint16_t>(kIds);
    auto* races = &at<uint8_t>(kRaces);
    const UnitWork& first = b.level < a.level ? a : b;
    const UnitWork& second = b.level < a.level ? b : a;
    ids[0] = first.id; races[0] = raceOf(first.id);
    ids[1] = second.id; races[1] = raceOf(second.id);
    ids[2] = unitAt(in.c).id; races[2] = raceOf(ids[2]);
}

} // namespace

void addFusionCoreTests(std::vector<TestCase>& t)
{
    auto add = [&t](const char* name, std::function<Pair(Gen&)> make) {
        t.push_back({name, [make](Gen& g) { randomStock(g); return make(g); }});
    };
    auto none = [](auto call) { return [call] { call(); return uint64_t{0}; }; };

    // ---- Mitama boosts ------------------------------------------------------------
    add("cmbGetPowerUpTableIndex", [](Gen& g) {
        uint16_t m = g.chance(70) ? dat::kSpiritParamUpTbl[g.below(4)].devil : fusionDevil(g);
        return Pair{[=] { return norm(ps2FusionCore_001FD498(m)); }, [=] { return norm(int32_t{cmb::mitamaBoostIndex(m)}); }};
    });
    add("cmbCalcParamUpVal", [](Gen& g) {
        int32_t stat = g.range(-5, 45), bonus = g.range(-10, 45), max = g.chance(80) ? 40 : g.range(-5, 99);
        uint8_t rate = static_cast<uint8_t>(g.below(256));
        return Pair{[=] { return norm(ps2FusionCore_001FD4E0(sx(stat), sx(bonus), sx(max), rate)); },
                    [=] { return norm(cmb::raisedMitamaBonus(stat, bonus, max, rate)); }};
    });
    add("cmbCalcParamPowerUp", [none](Gen& g) {
        uint16_t m = g.chance(80) ? dat::kSpiritParamUpTbl[g.below(4)].devil : fusionDevil(g);
        uint32_t u = unitAddress(g.range(0, 15));
        for (int8_t& p : unitAt(u).mitamaparam) p = static_cast<int8_t>(g.range(-3, 20));
        return Pair{[=] { return norm(ps2FusionCore_001FD538(m, u)); }, [=] { return norm(cmb::applyMitamaBoost(m, unitAt(u))); }};
    });

    // ---- table lookups -----------------------------------------------------------
    auto devilPair = [&add](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            Inputs in = fusionInputs(g);
            uint16_t a = unitAt(in.a).id, b = unitAt(in.b).id, c = unitAt(in.c).id;
            return Pair{[=] { return norm(legacy(a, b, c)); }, [=] { return norm(rewrite(a, b, c)); }};
        });
    };
    devilPair("cmbChkIkenieExtPattern", [](uint16_t a, uint16_t b, uint16_t c) { return ps2FusionCore_001FD610(a, b, c); },
              [](uint16_t a, uint16_t b, uint16_t c) { return int32_t{cmb::sacrificeRacePattern(a, b, c)}; });
    devilPair("cmbChkMetato", [](uint16_t a, uint16_t b, uint16_t c) { return ps2FusionCore_001FD708(a, b, c); },
              [](uint16_t a, uint16_t b, uint16_t c) { return cmb::isMetatronPair(a, b, c); });
    devilPair("cmbChkIkenieExtPatternDevRace", [](uint16_t a, uint16_t b, uint16_t c) { return ps2FusionCore_001FD730(a, b, c); },
              [](uint16_t a, uint16_t b, uint16_t c) { return int32_t{cmb::sacrificeDevilRacePattern(a, b, c)}; });
    devilPair("cmbChkExtPattern", [](uint16_t a, uint16_t b, uint16_t) { return ps2FusionCore_001FE1A0(a, b); },
              [](uint16_t a, uint16_t b, uint16_t) { return int32_t{cmb::specialPairResult(a, b)}; });
    devilPair("cmbGetBirthSpirit", [](uint16_t a, uint16_t b, uint16_t) { return ps2FusionCore_001FDD18(a, b); },
              [](uint16_t a, uint16_t b, uint16_t) { return int32_t{cmb::mitamaFromElements(a, b)}; });
    devilPair("cmbGetBirthDevilRace", [](uint16_t a, uint16_t b, uint16_t c) { return ps2FusionCore_001FDDE8(a, b, c & 1); },
              [](uint16_t a, uint16_t b, uint16_t c) { return int32_t{cmb::resultRace(a, b, (c & 1) != 0)}; });
    auto devilQuery = [&add](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            uint16_t d = g.chance(50) ? fusionDevil(g) : static_cast<uint16_t>(g.below(384));
            if (g.chance(30)) d = g.pick({dat::kExtPatternTbl[g.below(3)].birth, dat::kIkenieExtPatternDevTbl[g.below(7)].birth,
                                         dat::kIkenieExtPatternDev2Tbl[g.below(19)].birth, dat::kIkenieExtPatternDevRaceTbl[g.below(2)].birth});
            return Pair{[=] { return norm(legacy(d)); }, [=] { return norm(rewrite(d)); }};
        });
    };
    devilQuery("cmbChkExtPatternBirthDevil", [](uint16_t d) { return ps2FusionCore_001FE280(d); }, [](uint16_t d) { return cmb::isSpecialPairResult(d); });
    devilQuery("cmbChkIkenieExtPatternBirthDevil", [](uint16_t d) { return ps2FusionCore_001FDA08(d); }, [](uint16_t d) { return cmb::isSacrificePatternResult(d); });
    devilQuery("cmbCalcCombineManin", [](uint16_t d) { return ps2FusionCore_001FF648(d); }, [](uint16_t d) { return int32_t{cmb::fiendFusion(d)}; });
    add("cmbGetRankUpDown", [](Gen& g) {
        uint16_t soul = g.chance(80) ? dat::kRankUpDownTbl[g.below(4)].devil : fusionDevil(g);
        int8_t race = static_cast<int8_t>(g.chance(90) ? g.range(0, 40) : g.range(-128, 127));
        return Pair{[=] { return norm(ps2FusionCore_001FDCA0(soul, sx(race))); },
                    [=] { return norm(int32_t{cmb::elementRankShift(soul, static_cast<Race>(race))}); }};
    });
    add("cmbGetAverageLevel", [](Gen& g) {
        Inputs in = fusionInputs(g);
        if (g.chance(20)) unitAt(in.c).level = 0;
        bool third = g.chance(60);
        int32_t mode = g.range(0, 1);
        return Pair{[=] { return norm(ps2FusionCore_001FDEC0(in.a, in.b, third ? in.c : 0, sx(mode))); },
                    [=] { return norm(cmb::averageLevel(unitAt(in.a), unitAt(in.b), third ? &unitAt(in.c) : nullptr, mode != 0)); }};
    });
    add("cmbGetStockDevilInfo", [none](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        return Pair{none([=] { ps2FusionCore_001FE170(u, kInfo, kInfo + 4); }),
                    none([=] { cmb::stockDevilInfo(unitAt(u), &at<uint16_t>(kInfo), &at<uint8_t>(kInfo + 4)); })};
    });

    // ---- choosing the devil --------------------------------------------------------
    add("cmbGetTargetDevil", [](Gen& g) {
        uint8_t race = static_cast<uint8_t>(g.chance(90) ? g.range(0, 39) : g.below(256));
        uint8_t level = static_cast<uint8_t>(g.chance(90) ? g.range(1, 99) : g.below(256));
        return Pair{[=] { return norm(ps2FusionCore_001FDF78(race, level)); }, [=] { return norm(int32_t{cmb::targetDevil(race, level)}); }};
    });
    add("cmbGetRankUpDownDevil", [](Gen& g) {
        uint16_t d = fusionDevil(g);
        uint8_t shift = static_cast<uint8_t>(g.range(0, 2));
        return Pair{[=] { return norm(ps2FusionCore_001FDAC0(d, shift)); }, [=] { return norm(int32_t{cmb::rankShiftedDevil(d, shift)}); }};
    });
    add("cmbCalcNormal2", [](Gen& g) {
        Inputs in = fusionInputs(g);
        int32_t cursed = g.range(0, 1), mode = g.range(0, 1);
        return Pair{[=] { return norm(ps2FusionCore_001FE5F0(in.a, in.b, sx(cursed), sx(mode))); },
                    [=] { return norm(int32_t{cmb::normalFusion(unitAt(in.a), unitAt(in.b), cursed != 0, mode != 0)}); }};
    });
    add("cmbCalcDevil2", [](Gen& g) {
        Inputs in = fusionInputs(g);
        writeOrder(in);
        int32_t cursed = g.range(0, 1), mode = g.range(0, 1);
        bool withType = g.chance(90);
        return Pair{[=] { return norm(ps2FusionCore_001FE690(in.a, in.b, sx(cursed), sx(mode), kIds, kRaces, withType ? kType : 0)); },
                    [=] { cmb::FusionType* type = withType ? &at<cmb::FusionType>(kType) : nullptr;
                          return norm(int32_t{cmb::twoDevilFusion(unitAt(in.a), unitAt(in.b), cursed != 0, mode != 0,
                                                                  &at<uint16_t>(kIds), &at<uint8_t>(kRaces), type)}); }};
    });

    // ---- sacrificial fusion ----------------------------------------------------------
    add("cmbChkIkenieExtPatternDev", [](Gen& g) {
        Inputs in = fusionInputs(g);
        int32_t cursed = g.range(0, 1), mode = g.range(0, 1);
        return Pair{[=] { return norm(ps2FusionCore_001FD878(in.a, in.b, in.c, sx(cursed), sx(mode))); },
                    [=] { return norm(int32_t{cmb::sacrificeDevilPattern(unitAt(in.a), unitAt(in.b), unitAt(in.c), cursed != 0, mode != 0)}); }};
    });
    add("cmbCalcIkenie", [](Gen& g) {
        Inputs in = fusionInputs(g);
        writeOrder(in);
        int32_t cursed = g.range(0, 1), mode = g.range(0, 1);
        return Pair{[=] { return norm(ps2FusionCore_001FEA20(in.a, in.b, in.c, sx(cursed), sx(mode), kIds, kRaces)); },
                    [=] { return norm(int32_t{cmb::sacrificeFusion(unitAt(in.a), unitAt(in.b), unitAt(in.c), cursed != 0, mode != 0,
                                                                   &at<uint16_t>(kIds), &at<uint8_t>(kRaces))}); }};
    });
    add("cmbCalcIkenieExp", [none](Gen& g) {
        Inputs in = fusionInputs(g);
        UnitWork& sacrifice = unitAt(in.c);
        sacrifice.exp = g.chance(10) ? static_cast<int32_t>(g.rng()) : g.range(0, 3000000);
        unitAt(in.a).level = static_cast<uint16_t>(g.chance(10) ? g.range(240, 255) : g.range(1, 99));
        return Pair{none([=] { ps2FusionCore_001FE880(in.a, in.b, in.c, in.c); }),
                    none([=] { cmb::addSacrificeExp(unitAt(in.a), unitAt(in.b), unitAt(in.c), unitAt(in.c)); })};
    });
    add("cmbChkDante", [](Gen& g) {
        Inputs in = fusionInputs(g);
        for (uint32_t u : {in.a, in.b, in.c}) if (g.chance(20)) unitAt(u).id = devil::Dante;
        bool third = g.chance(50);
        return Pair{[=] { return norm(ps2FusionCore_001FF758(in.a, in.b, third ? in.c : 0)); },
                    [=] { return norm(cmb::involvesDante(unitAt(in.a), unitAt(in.b), third ? &unitAt(in.c) : nullptr)); }};
    });

    // ---- inherited skills ------------------------------------------------------------
    add("cmbAddKeisyoSkillFromSkill", [none](Gen& g) {
        Inputs in = fusionInputs(g);
        UnitWork& to = unitAt(in.a);
        if (g.chance(30)) {   // a nearly full or full list
            int filled = g.range(20, 24);
            for (int i = 0; i < 24; ++i)
                to.keisyoskill[i] = i < filled ? static_cast<uint16_t>(0x100 + i) : 0;
        }
        return Pair{none([=] { ps2FusionCore_001FEB28(in.a, in.b); }), none([=] { cmb::addInheritableSkills(unitAt(in.a), unitAt(in.b)); })};
    });
    add("cmbDeleteKeisyoSkill", [none](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        uint8_t index = static_cast<uint8_t>(g.range(0, 24));
        return Pair{none([=] { ps2FusionCore_001FEC40(u, index); }), none([=] { cmb::removeInherited(unitAt(u), index); })};
    });
    add("cmbMoveKeisyoSkillToSkill", [](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        uint16_t s = g.chance(70) ? unitAt(u).keisyoskill[g.below(24)] : static_cast<uint16_t>(g.below(0x200));
        return Pair{[=] { return norm(ps2FusionCore_001FEC68(s, u)); }, [=] { return norm(int32_t{cmb::learnInherited(s, unitAt(u))}); }};
    });
    add("cmbRndGetKeisyoSkill", [](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        return Pair{[=] { return norm(ps2FusionCore_001FF428(u)); }, [=] { return norm(int32_t{cmb::randomInheritedSkill(unitAt(u))}); }};
    });
    add("cmbRndAddKeisyoSkillToSkill", [none](Gen& g) {
        Inputs in = fusionInputs(g);
        uint32_t result = unitAddress(0);
        bool third = g.chance(50), list = g.chance(80);
        return Pair{none([=] { ps2FusionCore_001FF4D0(in.a, in.b, third ? in.c : 0, result, list ? kList : 0); }),
                    none([=] { cmb::learnRandomInherited(unitAt(in.a), unitAt(in.b), third ? &unitAt(in.c) : nullptr, unitAt(result),
                                                         list ? &at<cmb::InheritedSkillList>(kList) : nullptr); })};
    });

    // ---- the whole fusion --------------------------------------------------------------
    // On failure the original copies its uninitialised scratch unit to the
    // result; that garbage isn't compared.
    add("cmbGetBirthDevil", [](Gen& g) {
        Inputs in = fusionInputs(g);
        bool third = g.chance(40), list = g.chance(80);
        int32_t cursed = g.range(0, 1), mode = g.range(0, 1), accidents = g.chance(70) ? 1 : 0;
        if (g.chance(30)) at<GlobalWork>(FW_GLOBAL).item_counts[item::Deathstone] = 1;
        auto clearOnFailure = [](uint64_t type) {
            if (type == 0) std::memset(&unitAt(kResult), 0, sizeof(UnitWork));
            return type;
        };
        return Pair{[=] { return clearOnFailure(norm(ps2FusionCore_001FF790(in.a, in.b, third ? in.c : 0, kResult, sx(cursed), sx(mode),
                                                                            sx(accidents), list ? kList : 0))); },
                    [=] { return clearOnFailure(norm(int32_t{static_cast<uint8_t>(cmb::fuse(unitAt(in.a), unitAt(in.b),
                              third ? &unitAt(in.c) : nullptr, &unitAt(kResult), cursed != 0, mode != 0, accidents != 0,
                              list ? &at<cmb::InheritedSkillList>(kList) : nullptr))})); }};
    });
}

} // namespace difftest
