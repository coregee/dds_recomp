// The save game's data functions (datCalc: field skills, the party on the
// field, stock and item queries, boss refights): the rewrite against the
// original instructions, run by the EE interpreter.
#include <cstring>

#include "harness.hpp"
#include "version_map.hpp"
#include "interface_world.hpp"
#include "nocturne/data/field_skill.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"

extern "C" {
uint32_t ps2PoolAllocate(int32_t);

// The legacy battle code's boss-refight check is the rewrite.
int32_t datBossRashChk(int32_t eid) { return nocturne::dat::isBossRefight(eid) ? 1 : 0; }
}

namespace difftest {

namespace {

using namespace nocturne::dat;
using iface::A;
using iface::I;
using iface::origVm;
using iface::origVmVoid;

GlobalWork& global() { return at<GlobalWork>(FW_GLOBAL); }
uint32_t unitAddress(int index) { return FW_GLOBAL + static_cast<uint32_t>(offsetof(GlobalWork, units)) + 0xecu * static_cast<uint32_t>(index); }

// A save game: the random stock of the fusion tests, story demons (unique
// IDs, the first Pixie), items, boss records.
void dataWorld(Gen& g)
{
    std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
    at<uint32_t>(difftest::version::dataOrDie(0x0054ea20)) = FW_GLOBAL;
    randomStock(g);
    GlobalWork& w = global();
    for (UnitWork& unit : w.units) {
        if (g.chance(20))
            unit.flag |= UnitFlag::Unique;
        if (g.chance(10))
            unit.flag |= UnitFlag::Pixie;
        if (g.chance(10))
            unit.flag |= UnitFlag::KeepInStock;
        if (g.chance(30))
            unit.uniqueid = static_cast<uint16_t>(g.range(0, 5));
        if (g.chance(10))
            unit.badstat = static_cast<uint16_t>(g.pick<int32_t>({0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x8040}));
        if (g.chance(10))
            unit.id = devil::Dante;
        if (g.chance(25))   // a unit of the enemy's side (the formulas differ)
            unit.flag |= UnitFlag::Enemy;
        if (g.chance(10))
            unit.hp = static_cast<uint16_t>(g.range(0, 3));
    }
    for (uint8_t& count : w.item_counts)
        count = static_cast<uint8_t>(g.chance(50) ? 0 : g.chance(30) ? g.range(97, 100) : g.below(256));
    for (auto& record : w.boss_records) {
        record[0] = static_cast<int16_t>(g.chance(30) ? g.range(-1, 0) : g.range(1, 30));
        record[1] = static_cast<int16_t>(g.chance(30) ? g.range(-1, 0) : g.range(1, 30));
    }
    w.fieldskills = static_cast<uint32_t>(g.rng());
}

int someUnit(Gen& g) { return g.range(0, 15); }

// An active skill (one with a NormalSkill record).
int32_t someSkill(Gen& g)
{
    for (;;) {
        const int32_t skill = g.chance(5) ? 0 : static_cast<int32_t>(g.below(0x180));
        if (skillInfo(skill).type == 0)
            return skill;
    }
}

int32_t someDevil(Gen& g)
{
    if (g.chance(50))
        return global().units[someUnit(g)].id;
    return g.chance(5) ? g.range(-2, 0x200) : randomDevil(g);
}

// An encounter of the boss refight table, or another.
int32_t someEncounter(Gen& g)
{
    static const int32_t refights[] = {14, 55, 83, 84, 116, 117, 271, 194, 196, 197, 198, 199, 713, 714, 329,
                                       327, 328, 284, 970, 1008, 334, 472, 333, 267, 0x3e0, 0x3e1, 673, 1028};
    return g.chance(80) ? g.pick(refights) : g.range(0, 1300);
}

using Body = std::function<Pair(Gen&)>;

} // namespace

void addDataTests(std::vector<TestCase>& t)
{
    auto add = [&](const char* name, Body body) {
        t.push_back({name, [body](Gen& g) {
                         dataWorld(g);
                         return body(g);
                     }});
    };
    auto unit = [](uint32_t address) -> UnitWork& { return at<UnitWork>(address); };

    // ---- skills outside battle ----
    struct Power {
        const char* name;
        uint32_t entry;
        int32_t (*rewrite)(int32_t, UnitWork&, UnitWork&, int32_t);
    };
    static const Power powers[] = {
        {"GetButuriAttack", 0x00242e00, fieldPhysicalPower},
        {"GetButuriKaifuku", 0x00242fe0, fieldPhysicalHealPower},
        {"GetMagicAttack", 0x00242ff8, fieldMagicPower},
        {"GetMagicKaifuku", 0x00243170, fieldMagicHealPower},
        {"GetMaxHpWazaPoint", 0x00243200, fieldMaxHpPower},
    };
    for (const Power& p : powers) {
        const uint32_t entry = p.entry;
        auto rewrite = p.rewrite;
        add(p.name, [=](Gen& g) {
            const int32_t skill = someSkill(g), power = g.chance(80) ? g.range(0, 200) : g.range(-20, 1000);
            const uint32_t s = unitAddress(someUnit(g)), d = unitAddress(someUnit(g));
            return Pair{[=] { return origVm(entry, {I(skill), s, d, I(power)}); },
                        [=] { return norm(rewrite(skill, unit(s), unit(d), power)); }};
        });
    }
    add("GetAisyoRitu", [=](Gen& g) {
        const int32_t skill = someSkill(g);
        const uint32_t s = unitAddress(someUnit(g)), d = unitAddress(someUnit(g));
        return Pair{[=] { origVm(0x002432d0, {I(skill), s, d}); return uint64_t{iface::origVmFloat()}; },
                    [=] { return uint64_t{fieldAffinityRate(skill, unit(s), unit(d)).bits()}; }};
    });
    add("datGetSkillKouka", [=](Gen& g) {
        const int32_t skill = someSkill(g), type = g.chance(90) ? g.range(0, 1) : g.range(-1, 3);
        const uint32_t s = unitAddress(someUnit(g)), d = unitAddress(someUnit(g));
        return Pair{[=] { return origVm(0x00243368, {I(skill), I(type), s, d}); },
                    [=] { return norm(fieldSkillEffect(skill, type, unit(s), unit(d))); }};
    });
    add("datGetSkillBadKouka", [=](Gen& g) {
        const int32_t skill = someSkill(g);
        const uint32_t s = unitAddress(someUnit(g)), d = unitAddress(someUnit(g));
        return Pair{[=] { return origVm(0x00243760, {I(skill), s, d}); },
                    [=] { return norm(static_cast<int32_t>(fieldSkillAilment(skill, unit(s), unit(d)))); }};
    });
    add("datExecSkill", [=](Gen& g) {
        const int32_t skill = someSkill(g);
        const uint32_t s = g.chance(5) ? 0 : unitAddress(someUnit(g)), d = g.chance(5) ? 0 : unitAddress(someUnit(g));
        return Pair{[=] { return origVm(0x00243998, {I(skill), s, d}); },
                    [=] { return norm(useFieldSkill(skill, s ? &unit(s) : nullptr, d ? &unit(d) : nullptr)); }};
    });

    // ---- the party on the field ----
    add("datPartyDamage", [](Gen& g) {
        const int32_t mode = g.range(0, 7);
        return Pair{[=] { return origVmVoid(0x002447c0, {I(mode)}); }, [=] { partyDamage(mode); return uint64_t{0}; }};
    });
    add("datPartyDamageFld", [](Gen& g) {
        const int32_t mode = g.range(0, 5);
        return Pair{[=] { return origVmVoid(0x00244a38, {I(mode)}); }, [=] { partyFieldDamage(mode); return uint64_t{0}; }};
    });
    add("datPartyDamagePipe", [](Gen& g) {
        const int32_t big = g.chance(30) ? 0 : g.range(-2, 5), small = g.chance(30) ? 0 : g.range(-2, 5);
        return Pair{[=] { return origVmVoid(0x00244cc0, {I(big), I(small)}); }, [=] { partyPipeDamage(big, small); return uint64_t{0}; }};
    });
    add("datPartyKaifuku", [](Gen&) {
        return Pair{[=] { return origVmVoid(0x00244dd8, {}); }, [=] { partyRecover(); return uint64_t{0}; }};
    });

    // ---- queries ----
    add("affinityRate", [=](Gen& g) {
        const uint32_t u = unitAddress(someUnit(g));
        const int32_t attr = g.range(0, 19);
        return Pair{[=] { return origVm(0x00244078, {u, I(attr)}); },
                    [=] { return norm(static_cast<int32_t>(affinityRate(unit(u), static_cast<nocturne::Attribute>(attr)))); }};
    });
    add("datCheckTalk", [=](Gen& g) {
        const uint32_t u = unitAddress(someUnit(g));
        if (g.chance(50))
            unit(u).badstat = static_cast<uint16_t>(g.below(0x10000));
        return Pair{[=] { return origVm(0x002444a8, {u}); }, [=] { return norm(canTalk(unit(u))); }};
    });
    add("datGetLevelForDraw", [=](Gen& g) {
        const uint32_t u = unitAddress(someUnit(g));
        if (g.chance(30))
            unit(u).level = static_cast<uint16_t>(g.range(95, 300));
        return Pair{[=] { return origVm(0x00245d18, {u}); }, [=] { return norm(levelForDraw(unit(u))); }};
    });
    add("datCheckPlayerDead", [](Gen& g) {
        if (g.chance(30))
            global().units[0].badstat = static_cast<uint16_t>(0x800 | (g.chance(50) ? 0x8000 : 0));
        return Pair{[=] { return origVm(0x002445a8, {}); }, [=] { return norm(isPlayerDead()); }};
    });
    add("datAddMaka", [](Gen& g) {
        const int32_t amount = g.chance(20) ? static_cast<int32_t>(g.rng()) : g.range(-100000, 100000);
        return Pair{[=] { return origVmVoid(0x00244238, {I(amount)}); }, [=] { addMacca(amount); return uint64_t{0}; }};
    });
    add("datCheckMaka", [](Gen& g) {
        const int32_t amount = g.chance(50) ? global().macca + g.range(-2, 2) : g.range(-10, 9999999);
        return Pair{[=] { return origVm(0x002442c8, {I(amount)}); }, [=] { return norm(hasMacca(amount)); }};
    });
    add("datInitPlayer", [](Gen&) {
        return Pair{[=] { return origVmVoid(0x00245b10, {}); }, [=] { initPlayer(); return uint64_t{0}; }};
    });
    add("datGetUniqueDevilId", [](Gen& g) {
        const int32_t id = g.range(-1, 6);
        return Pair{[=] { return origVm(0x00245250, {I(id)}); }, [=] { return norm(uniqueDevilId(id)); }};
    });
    add("datSearchDevilStock", [](Gen& g) {
        const int32_t devil = someDevil(g);
        return Pair{[=] { return origVm(0x00244530, {I(devil)}); }, [=] { return norm(findDevil(devil)); }};
    });
    add("datCheckStockFull", [](Gen&) {
        return Pair{[=] { return origVm(0x00244eb8, {}); }, [=] { return norm(isStockFull()); }};
    });
    add("datDelDevil", [](Gen& g) {
        const int32_t devil = someDevil(g);
        return Pair{[=] { return origVm(0x00245c78, {I(devil)}); }, [=] { return norm(removeDevil(devil)); }};
    });
    add("datCheckItemFull", [](Gen& g) {
        const int32_t item = g.range(0, 0x9f);
        return Pair{[=] { return origVm(0x00244410, {I(item)}); }, [=] { return norm(isItemFull(item)); }};
    });
    add("datInitBossPress", [](Gen&) {
        return Pair{[=] { return origVmVoid(0x00245c40, {}); }, [=] { initBossPress(); return uint64_t{0}; }};
    });
    add("datBossRashGetRec", [](Gen& g) {
        const int32_t encounter = someEncounter(g), type = g.range(-1, 3);
        return Pair{[=] { return origVm(0x00245e60, {I(encounter), I(type)}); }, [=] { return norm(bossPressRecord(encounter, type)); }};
    });
    add("datBossRashUpdRec", [](Gen& g) {
        const int32_t encounter = someEncounter(g), press = g.chance(20) ? 0 : g.range(-1, 40);
        return Pair{[=] { return origVmVoid(0x00245f68, {I(encounter), I(press)}); },
                    [=] { updateBossPressRecord(encounter, press); return uint64_t{0}; }};
    });
    add("datBossRashChk", [](Gen& g) {
        const int32_t encounter = someEncounter(g);
        return Pair{[=] { return origVm(0x00246038, {I(encounter)}); }, [=] { return norm(isBossRefight(encounter)); }};
    });
}

} // namespace difftest
