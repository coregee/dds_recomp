// Differential tests for the party and progression code
// (rewrite: src/data/progression.cpp; legacy: unit_progression.c).
#include <cstdint>

#include "harness.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"

extern "C" {
void ps2UnitRecalculateMaxHpMp_00240A98(uint64_t unit);
uint64_t ps2UnitAffinityFlags_00244098(uint64_t unit, uint64_t attribute);
void ps2UnitAddMakaPercent_00244268(uint64_t percent);
uint64_t ps2UnitPlayerParameter_002445C0(uint64_t parameter);
void ps2UnitAddPlayerParameter_00244610(uint64_t parameter, uint64_t amount);
uint64_t ps2UnitCompanionParameter_00244668(uint64_t species, uint64_t parameter);
uint64_t ps2UnitPlayerAlignment_002446B0(void);
void ps2UnitKillCompanion_002446F8(uint64_t species);
void ps2UnitInitializeCompanion_00244EF8(uint64_t species, uint64_t unit);
uint64_t ps2UnitAddCompanion_00245020(uint64_t species, uint64_t join_party);
void ps2UnitAddUniqueCompanion_00245180(uint64_t species, uint64_t join_party, uint64_t unique_id);
uint64_t ps2UnitFindUniqueCompanion_002451F0(uint64_t unique_id);
void ps2UnitAddExperience_002452B8(uint64_t unit, uint64_t experience);
void ps2UnitRemoveMagatama_00245380(void);
void ps2UnitEquipMagatama_002453E8(uint64_t id);
void ps2UnitApplyRecoverySkill_00245478(uint64_t unit, uint64_t skill);
void ps2UnitRecoverFieldParty_002455B8(void);
uint64_t ps2UnitFindTreasureSkillOwner_002456D0(void);
void ps2UnitClearPartyCommandMemory_00245808(void);
void ps2UnitAddReasonPoints_00245890(uint64_t reason, uint64_t amount);
uint64_t ps2UnitReasonRank_002458D0(uint64_t rank);
void ps2UnitRefreshCompanion_00245D30(uint64_t species, uint64_t unit);
void datClearCommMemory(uint64_t work);
}

namespace difftest {
namespace {

constexpr uint32_t kUnits = FW_GLOBAL + static_cast<uint32_t>(offsetof(nocturne::GlobalWork, units));
uint32_t unitAddress(int i) { return kUnits + 0xec * static_cast<uint32_t>(i); }

const uint16_t kRecoverySkills[] = {skill::LifeAid, skill::ManaAid, skill::VictoryCry, skill::LifeRefill, skill::ManaRefill};

// Give party members the skills these functions look for.
void sprinkleFieldSkills(Gen& g)
{
    for (int i = 0; i < 16; ++i) {
        UnitWork& u = unitAt(unitAddress(i));
        if (g.chance(30)) u.flag |= 3;
        if (u.skillcnt < 24 && g.chance(50)) u.skill[u.skillcnt++] = g.chance(40) ? skill::LuckyFind : g.pick(kRecoverySkills);
        if (g.chance(30)) u.param[5] = static_cast<int8_t>(g.range(-5, 40));
    }
}

} // namespace

void addProgressionTests(std::vector<TestCase>& t)
{
    auto add = [&t](const char* name, std::function<Pair(Gen&)> make) {
        t.push_back({name, [make](Gen& g) { randomStock(g); sprinkleFieldSkills(g); return make(g); }});
    };
    auto none = [](auto call) { return [call] { call(); return uint64_t{0}; }; };

    add("cmpSetMaxHPMP", [none](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        return Pair{none([=] { ps2UnitRecalculateMaxHpMp_00240A98(u); }), none([=] { dat::rescaleHpMp(unitAt(u)); })};
    });
    add("datGetAisyoFlag", [](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        int32_t attr = g.range(0, 10);
        return Pair{[=] { return ps2UnitAffinityFlags_00244098(u, sx(attr)); },
                    [=] { return norm(static_cast<int32_t>(dat::affinityFlags(unitAt(u), static_cast<Attribute>(attr)))); }};
    });
    add("datAddMakaPar", [none](Gen& g) {
        int32_t percent = g.chance(10) ? static_cast<int32_t>(g.rng()) : g.range(-150, 150);
        return Pair{none([=] { ps2UnitAddMakaPercent_00244268(sx(percent)); }), none([=] { dat::addMaccaPercent(percent); })};
    });
    add("datGetPlayerParam", [](Gen& g) {
        int32_t stat = g.range(0, 5);
        return Pair{[=] { return norm(ps2UnitPlayerParameter_002445C0(sx(stat))); },
                    [=] { return norm(dat::playerParam(static_cast<Param>(stat))); }};
    });
    add("datAddPlayerParam", [none](Gen& g) {
        int32_t stat = g.range(0, 5), amount = g.range(-50, 50);
        return Pair{none([=] { ps2UnitAddPlayerParameter_00244610(sx(stat), sx(amount)); }),
                    none([=] { dat::addPlayerParam(static_cast<Param>(stat), amount); })};
    });
    add("datGetNakamaParam", [](Gen& g) {
        uint16_t devil = g.chance(60) ? unitAt(unitAddress(g.range(0, 15))).id : randomDevil(g);
        int32_t stat = g.range(0, 5);
        return Pair{[=] { return norm(ps2UnitCompanionParameter_00244668(devil, sx(stat))); },
                    [=] { return norm(dat::companionParam(devil, static_cast<Param>(stat))); }};
    });
    add("datGetPlayerLND", [](Gen&) {
        return Pair{[] { return norm(ps2UnitPlayerAlignment_002446B0()); }, [] { return norm(dat::playerAlignment()); }};
    });
    add("datDeadNakama", [none](Gen& g) {
        uint16_t devil = g.chance(70) ? unitAt(unitAddress(g.range(0, 15))).id : randomDevil(g);
        return Pair{none([=] { ps2UnitKillCompanion_002446F8(devil); }), none([=] { dat::killCompanion(devil); })};
    });
    add("datSetDevilWork", [none](Gen& g) {
        uint16_t devil = randomDevil(g);
        uint32_t u = unitAddress(g.range(0, 15));
        return Pair{none([=] { ps2UnitInitializeCompanion_00244EF8(devil, u); }), none([=] { dat::initDevil(devil, unitAt(u)); })};
    });
    add("datAddDevil", [](Gen& g) {
        int32_t devil = randomDevil(g) | (g.chance(30) ? INT32_MIN : 0);
        int32_t join = g.range(0, 1);
        return Pair{[=] { return norm(ps2UnitAddCompanion_00245020(sx(devil), sx(join))); },
                    [=] { return norm(dat::addDevil(devil, join != 0)); }};
    });
    add("datAddUniqueDevil", [none](Gen& g) {
        int32_t devil = randomDevil(g) | (g.chance(30) ? INT32_MIN : 0);
        int32_t join = g.range(0, 1), unique = g.chance(30) ? 1 : g.range(0, 0xffff);
        return Pair{none([=] { ps2UnitAddUniqueCompanion_00245180(sx(devil), sx(join), sx(unique)); }),
                    none([=] { dat::addUniqueDevil(devil, join != 0, unique); })};
    });
    add("datSearchUniqueDevilStock", [](Gen& g) {
        for (int i = 0; i < 16; ++i)
            if (g.chance(30)) unitAt(unitAddress(i)).flag |= 0x400;
        int32_t unique = g.chance(50) ? unitAt(unitAddress(g.range(0, 15))).uniqueid : g.range(0, 0xffff);
        return Pair{[=] { return norm(ps2UnitFindUniqueCompanion_002451F0(sx(unique))); }, [=] { return norm(dat::findUniqueDevil(unique)); }};
    });
    add("datAddExp", [none](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        int32_t exp = g.chance(10) ? static_cast<int32_t>(g.rng()) : g.range(0, 100000);
        return Pair{none([=] { ps2UnitAddExperience_002452B8(u, sx(exp)); }), none([=] { dat::addExp(unitAt(u), exp); })};
    });
    add("datRemoveHearts", [none](Gen&) {
        return Pair{none([] { ps2UnitRemoveMagatama_00245380(); }), none([] { dat::removeMagatama(); })};
    });
    add("datEquipHearts", [none](Gen& g) {
        uint8_t id = static_cast<uint8_t>(g.chance(20) ? at<GlobalWork>(FW_GLOBAL).hearts_equipped : g.below(25));
        return Pair{none([=] { ps2UnitEquipMagatama_002453E8(id); }), none([=] { dat::equipMagatama(id); })};
    });
    add("datSetAutoKaifukuSkill", [none](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        uint16_t skill = g.chance(80) ? g.pick(kRecoverySkills) : static_cast<uint16_t>(g.below(0x200));
        return Pair{none([=] { ps2UnitApplyRecoverySkill_00245478(u, skill); }), none([=] { dat::applyRecoverySkill(unitAt(u), skill); })};
    });
    add("datFieldSkillKaifuku", [none](Gen&) {
        return Pair{none([] { ps2UnitRecoverFieldParty_002455B8(); }), none([] { dat::recoverPartyWhileWalking(); })};
    });
    add("datCheckSkillTakaraSagasi", [](Gen&) {
        return Pair{[] { return norm(ps2UnitFindTreasureSkillOwner_002456D0()); }, [] { return norm(int32_t{dat::luckyFindOwner()}); }};
    });
    add("datClearCommMemory", [none](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        return Pair{none([=] { datClearCommMemory(u); }), none([=] { dat::clearCommandMemory(unitAt(u)); })};
    });
    add("datAllClearCommMemory", [none](Gen&) {
        return Pair{none([] { ps2UnitClearPartyCommandMemory_00245808(); }), none([] { dat::clearPartyCommandMemory(); })};
    });
    add("datAddKotowariPoint", [none](Gen& g) {
        int32_t reason = g.range(0, 3), amount = g.chance(10) ? static_cast<int32_t>(g.rng()) : g.range(-150, 150);
        return Pair{none([=] { ps2UnitAddReasonPoints_00245890(sx(reason), sx(amount)); }), none([=] { dat::addReasonPoints(reason, amount); })};
    });
    add("datGetKotowariLank", [](Gen& g) {
        int32_t rank = g.range(0, 2);
        return Pair{[=] { return norm(ps2UnitReasonRank_002458D0(sx(rank))); }, [=] { return norm(dat::reasonRank(rank)); }};
    });
    add("datCopyDevilWork", [none](Gen& g) {
        uint16_t devil = randomDevil(g);
        uint32_t u = unitAddress(g.range(0, 15));
        // Max HP/MP are computed with the unit's old skill count over the new
        // skill list, so leave HP/MP passives where the old count reaches.
        static const uint16_t kBonuses[] = {skill::LifeBonus, skill::LifeGain, skill::LifeSurge,
                                            skill::ManaBonus, skill::ManaGain, skill::ManaSurge};
        UnitWork& unit = unitAt(u);
        unit.skillcnt = static_cast<uint16_t>(g.range(0, 24));
        for (uint16_t& s : unit.skill)
            if (g.chance(30)) s = g.pick(kBonuses);
        return Pair{none([=] { ps2UnitRefreshCompanion_00245D30(devil, u); }), none([=] { dat::resetToSpecies(devil, unitAt(u)); })};
    });
}

} // namespace difftest
