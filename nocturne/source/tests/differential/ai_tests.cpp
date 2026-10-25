// Differential tests for the enemy AI and targeting
// (rewrite: src/battle/ai.cpp, ai_script.cpp, targeting.cpp;
// legacy: battle_ai_*.c, battle_targeting.c).
#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

#include "harness.hpp"
#include "version_map.hpp"
#include "interface_world.hpp"
#include "nocturne/battle/action.hpp"
#include "nocturne/battle/bad_ai.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/comm_select.hpp"
#include "nocturne/battle/pad.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/data/devil_ai.hpp"
#include "nocturne/variant.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/skill_error.hpp"
#include "nocturne/battle/target_select.hpp"
#include "nocturne/battle/ai.hpp"
#include "nocturne/battle/ai_script.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/battle/targeting.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"

// The legacy headers use C11 static assertions.
#define _Static_assert static_assert
extern "C" {
#include "battle_ai_actions.h"
#include "battle_ai_conditions.h"
#include "battle_ai_estimates.h"
#include "battle_ai_execution.h"
#include "battle_ai_filters.h"
#include "battle_ai_selection.h"
#include "battle_script_commands.h"
#include "battle_targeting.h"
}
#undef _Static_assert

extern "C" {
uint64_t dds3StartProcess(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
uint32_t ps2PoolAllocate(int32_t);
}

namespace difftest {
namespace {

using nb::ActionProcessData;
using nb::Formation;
using nb::MainProcessData;
using nb::Party;

constexpr uint32_t kAct = FW_ACTION;
constexpr uint32_t kOut = FW_SCRATCH;   // outputs for type/rule/area

ActionProcessData& act() { return at<ActionProcessData>(kAct); }
MainProcessData& mainData() { return at<MainProcessData>(FW_MAIN); }
Formation& form(int f) { return at<Formation>(FW_FORMS + 0xf0 * static_cast<uint32_t>(f)); }
Party& party(int k) { return at<Party>(FW_PARTY + 128 * static_cast<uint32_t>(k)); }
uint32_t formUnit(int f) { return at<uint32_t>(FW_FORM_UNITS + 4 * static_cast<uint32_t>(f)); }

const uint16_t kSummonSkills[] = {0xde, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xfc};

// The AI's skill choices: real skills, summons, attack variants.
uint16_t aiSkill(Gen& g)
{
    switch (g.below(5)) {
    case 0: return g.pick(kSummonSkills);
    case 1: return static_cast<uint16_t>(g.range(0xa4, 0xa7));
    case 2: return 0;
    default: return static_cast<uint16_t>(g.range(1, 0x11f));
    }
}

// Turns the random battle into an enemy's turn with AI state.
// Hardtype's AI records (source/hardtype/include/nocturne/data/devil_ai.hpp):
// a table of their addresses by devil.
constexpr bool kPackedAi = nocturne::kVariant == nocturne::Variant::Hardtype;
uint32_t packedRecord(int32_t devil) { return at<uint32_t>(dat::address::DevilAI + 4u * static_cast<uint32_t>(devil)); }

void prepareAi(Gen& g)
{
    MainProcessData& main = mainData();
    for (int f = 0; f < 16; ++f) {
        Formation& slot = form(f);
        uint32_t stat = slot.stat & ~0xfu;
        bool present = f < 14 && formUnit(f);
        if (present) stat |= 1;
        if (present && g.chance(70)) stat |= 4;   // only occupied slots are targetable
        slot.formindex = static_cast<int16_t>(f);
        if (g.chance(15)) stat |= 8;
        if (g.chance(10)) stat |= 0x40;
        if (g.chance(20)) stat |= 0x800;
        slot.stat = stat;
        slot.orgpos.x = ee::Float::fromInt(g.range(-50, 50));
        slot.partyindex = static_cast<int16_t>(g.range(0, 13));
    }
    for (int k = 0; k < 14; ++k) {
        Party& p = party(k);
        if (g.chance(10)) p.flag = static_cast<int16_t>(p.flag | (g.chance(50) ? 0x8 : 0x20));
        for (int c = 0; c < 4; ++c) p.count[c] = static_cast<int16_t>(g.range(0, 6));
        p.count[18] = static_cast<int16_t>(g.range(0, 5));
    }
    // The press turn gauge's counts and Hardtype's byte at 0x1248F41, which
    // Hardtype's AI conditions read.
    at<uint32_t>(difftest::version::dataOrDie(0x00551fe0)) = static_cast<uint32_t>(g.range(0, 8));
    at<uint32_t>(difftest::version::dataOrDie(0x00551fe4)) = static_cast<uint32_t>(g.range(0, 8));
    at<uint8_t>(0x01248f41) = static_cast<uint8_t>(g.range(0, 15));   // (Hardtype reads the moon phase here)
    main.summonallowed = g.chance(70) ? 1 : 0;
    main.turn = static_cast<uint8_t>(g.range(0, 10));
    main.playerpcnt = static_cast<int16_t>(g.range(0, 4));
    main.enemypcnt = static_cast<int16_t>(g.range(0, 10));

    int f = g.range(4, 13);
    while (!formUnit(f)) f = g.range(4, 13);
    ActionProcessData& a = act();
    a.data.address = FW_MAIN;
    a.form.address = FW_FORMS + 0xf0 * static_cast<uint32_t>(f);
    a.partyindex = f;
    a.party.address = FW_PARTY + 128u * static_cast<uint32_t>(f);
    a.work.address = formUnit(f);
    a.aiselect = g.chance(50) ? static_cast<uint32_t>(g.rng()) & 0x3fff : 0;
    a.aijokentbl = g.range(0, 2);
    for (int8_t& tried : a.aichktbl) tried = static_cast<int8_t>(g.chance(20) ? g.pick({1, -1, 0x40}) : 0);
    a.aisummonid = static_cast<uint32_t>(g.chance(80) ? g.range(1, 383) : g.range(-1, 0));
    a.massuruid = g.range(0, 0x11f);
    a.select = 0;
    UnitWork& unit = *a.work;
    // (Hardtype: a devil whose table AI runs: with a record, action tables
    // and no script. Script devils' checks point at nothing real.)
    if constexpr (kPackedAi)
        while (packedRecord(unit.id) < dat::address::DevilAI || packedRecord(unit.id) >= difftest::version::dataOrDie(0x003a7fe0) ||
               dat::aiRecord(unit.id).tables() <= 0 || dat::aiRecord(unit.id).script() != 0)
            unit.id = static_cast<uint16_t>(g.range(1, 383));
    // Every devil has AI level 0 in the shipped data; patch the actor's
    // record so the dormant levels 1..3 are exercised too.
    // (Hardtype's own records are all level 0; the higher levels still run
    // its effect estimates.)
    const uint16_t level = static_cast<uint16_t>(g.chance(50) ? g.range(1, 3) : 0);
    if constexpr (kPackedAi)
        at<uint16_t>(packedRecord(unit.id) + 0xa) = level;
    else
        const_cast<DevilAI&>(dat::devilAI(unit.id)).ailevel = level;
    unit.nowcommand = static_cast<int16_t>(g.pick({0, 1, 1, 1, 3, 5, 7, 4, 6}));
    unit.nowindex = unit.nowcommand == 5 ? static_cast<uint16_t>(g.range(0, 60)) : aiSkill(g);
    // Summon skills may target empty summon slots (0x800); with a (patched)
    // AI level the effect estimate would then read an absent unit, which the
    // original does through guest address 0. Levels are all 0 in the game.
    if (dat::aiRecord(unit.id).level() != 0)
        for (int k = 0; k < 16; ++k)
            if (!(form(k).stat & 1))
                form(k).stat &= ~0x800u;

    auto& select = at<nb::TargetCursor>(FW_TARSEL);
    std::memset(&select, 0, sizeof select);
    select.data.address = FW_MAIN;
    select.act.address = kAct;

    scriptWork();
    for (int i = 0; i < 8; ++i) scriptParam(i, g.chance(80) ? g.range(0, 100) : g.range(0, 0x17f));   // negative ones make invalid conditions
    at<int32_t>(difftest::version::dataOrDie(0x005514e8)) = g.range(-3, 20);   // the rotation counter (static, restored by the harness)
}

// A condition word that tends to hold: valid types with fitting parameters.
uint32_t conditionWord(Gen& g)
{
    static const uint16_t kAilmentValues[] = {0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800};
    uint32_t type = g.chance(5) ? 0 : static_cast<uint32_t>(g.range(1, 28));
    uint32_t n;
    switch (type) {
    case 7: case 8: case 9: case 10: n = g.pick(kAilmentValues); break;
    case 11: case 12: n = static_cast<uint32_t>(g.range(1, 383)); break;
    case 13: case 14: case 25: case 26: n = static_cast<uint32_t>(g.range(0, 19)); break;
    case 28: n = static_cast<uint32_t>(g.range(0, 0x11f)); break;
    default: n = static_cast<uint32_t>(g.chance(80) ? g.range(0, 100) : g.range(0, 0xffff)); break;
    }
    return type << 16 | n;
}

} // namespace

void addAiTests(std::vector<TestCase>& t)
{
    const size_t first = t.size();
    auto add = [&t](const char* name, std::function<Pair(Gen&)> make) {
        t.push_back({name, [make](Gen& g) { prepareAi(g); return make(g); }});
    };
    auto none = [](auto call) { return [call] { call(); return uint64_t{0}; }; };

    // ---- conditions ------------------------------------------------------------------
    struct Condition { const char* name; uint64_t (*legacy)(uint64_t, uint64_t); bool (*rewrite)(nb::ActionProcessData&, int32_t); uint32_t type; };
    static const Condition kConditions[] = {
        {"nbAiChkMyHp", nbAiChkMyHp, nb::ai::ownHpAtMost, 1},
        {"nbAiChkMyMp", nbAiChkMyMp, nb::ai::ownMpAtMost, 24},
        {"nbAiChkFrHp", nbAiChkFrHp, nb::ai::allyHpAtMost, 2},
        {"nbAiChkDmgCnt", nbAiChkDmgCnt, nb::ai::damageCountAtLeast, 3},
        {"nbAiChkChkCnt", nbAiChkChkCnt, nb::ai::checkedAtLeast, 4},
        {"nbAiChkFrCnt", nbAiChkFrCnt, nb::ai::allyCountAtMost, 5},
        {"nbAiChkEnCnt", nbAiChkEnCnt, nb::ai::enemyCountAtMost, 6},
        {"nbAiChkMyBad", nbAiChkMyBad, nb::ai::ownAilment, 7},
        {"nbAiChkFrBad", nbAiChkFrBad, nb::ai::allyAilment, 8},
        {"nbAiChkEnBad", nbAiChkEnBad, nb::ai::enemyAilment, 9},
        {"nbAiChkEnAllBad", nbAiChkEnAllBad, nb::ai::allEnemiesAilment, 10},
        {"nbAiChkEnId", nbAiChkEnId, nb::ai::enemyIsDevil, 11},
        {"nbAiChkFrId", nbAiChkFrId, nb::ai::allyIsDevil, 12},
        {"nbAiChkEnHojo", nbAiChkEnHojo, nb::ai::enemyBuff, 13},
        {"nbAiChkFrHojo", nbAiChkFrHojo, nb::ai::allyBuff, 14},
        {"nbAiChkBa", nbAiChkBa, nb::ai::backAttack, 15},
        {"nbAiChkEnLight", nbAiChkEnLight, nb::ai::enemyIsLight, 16},
        {"nbAiChkEnDark", nbAiChkEnDark, nb::ai::enemyIsDark, 17},
        {"nbAiChkPow", nbAiChkPow, nb::ai::ownFocus, 18},
        {"nbAiChkPlv", nbAiChkPlv, nb::ai::playerLevelAtLeast, 19},
        {"nbAiChkPPartyLv", nbAiChkPPartyLv, nb::ai::partyLevelAtLeast, 20},
        {"nbAiChkTurn", nbAiChkTurn, nb::ai::turnAtLeast, 22},
        {"nbAiChkSensei", nbAiChkSensei, nb::ai::enemiesStruckFirst, 23},
        {"nbAiChkEnHojoMax", nbAiChkEnHojoMax, nb::ai::enemyBuffAtLimit, 25},
        {"nbAiChkFrHojoMax", nbAiChkFrHojoMax, nb::ai::allyBuffAtLimit, 26},
        {"nbAiChkEnHamamHk", nbAiChkEnHamamHk, nb::ai::enemyNotImmuneToExpel, 27},
        {"nbAiChkSkillNoMp", nbAiChkSkillNoMp, nb::ai::cannotAfford, 28},
    };
    for (const Condition& c : kConditions) {
        add(c.name, [c](Gen& g) {
            uint32_t word = conditionWord(g);
            int32_t n = static_cast<int32_t>((word & 0xffff0000u) ? word & 0xffff : 50);
            if ((word >> 16) != c.type && g.chance(50)) n = static_cast<int32_t>(conditionWord(g) & 0xffff);
            return Pair{[=] { return norm(c.legacy(kAct, static_cast<uint64_t>(n))); }, [=] { return norm(c.rewrite(act(), n)); }};
        });
    }
    auto buffQuery = [&add](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            int32_t f = g.range(0, 13), code = g.range(-1, 20);
            return Pair{[=] { return norm(legacy(sx(f), sx(code))); }, [=] { return norm(rewrite(f, code)); }};
        });
    };
    buffQuery("nbAiChkHojo", nbAiChkHojo, nb::ai::hasBuff);
    buffQuery("nbAiChkHojoMax", nbAiChkHojoMax, [](int32_t f, int32_t code) { return nb::ai::buffAtLimit(f, code, 0); });
    add("nbAiChkJoken", [](Gen& g) {
        uint32_t word = conditionWord(g);
        return Pair{[=] { return norm(nbAiChkJoken(kAct, word)); }, [=] { return norm(nb::ai::condition(act(), word)); }};
    });

    // ---- choosing an action -----------------------------------------------------------
    add("nbAiAiChk", [](Gen& g) {
        int32_t index = g.range(0, 2);
        return Pair{[=] { return norm(nbAiAiChk(kAct, sx(index))); }, [=] { return norm(nb::ai::check(act(), index)); }};
    });
    add("nbAiGetKoudou", [](Gen& g) {
        int32_t table = g.range(0, 2);
        return Pair{[=] { return norm(nbAiGetKoudou(kAct, sx(table))); }, [=] { return norm(nb::ai::drawAction(act(), table)); }};
    });
    add("nbAiSetKoudou", [none](Gen& g) {
        int32_t table = g.range(0, 2), action = g.range(0, 4);
        return Pair{none([=] { nbAiSetKoudou(kAct, sx(table), sx(action)); }), none([=] { nb::ai::setAction(act(), table, action); })};
    });
    add("nbAiChkCost", [](Gen&) {
        return Pair{[] { return norm(nbAiChkCost(kAct)); }, [] { return norm(nb::ai::costBlocks(act())); }};
    });
    add("nbAiChkClose", [](Gen&) {
        return Pair{[] { return norm(nbAiChkClose(kAct)); }, [] { return norm(nb::ai::canProceed(act())); }};
    });
    add("nbRunAiSub", [](Gen& g) {
        int32_t table = g.range(0, 2);
        return Pair{[=] { return norm(nbRunAiSub(kAct, sx(table))); }, [=] { return norm(nb::ai::runTable(act(), table)); }};
    });
    add("nbRunAi", [](Gen&) {
        return Pair{[] { return norm(nbRunAi(kAct)); }, [] { return norm(nb::ai::run(act())); }};
    });
    for (size_t k = first; k < t.size(); ++k)   // (the tests so far are against the legacy C)
        t[k].legacyC = true;

    // ---- choosing an action, against the original instructions ----
    // (Hardtype's AI records differ: these follow whichever executable runs.)
    auto someCheck = [](Gen& g) { return g.range(0, std::max(0, dat::aiRecord(act().work->id).checks() - 1)); };
    // A table of the actor's record (Hardtype: one of its own, walked from the
    // first; the checks may point at shared or unreachable ones).
    auto someTable = [](Gen& g) {
        const dat::AiRecord record = dat::aiRecord(act().work->id);
        if constexpr (!kPackedAi) {
            return static_cast<uint32_t>(g.range(0, 2));
        } else {
            uint32_t table = record.firstTable();
            for (int32_t pick = g.range(0, record.tables() - 1); pick > 0; --pick)
                table += 2 + 8u * static_cast<uint32_t>(std::max(record.actions(table), 1));
            return table;
        }
    };
    add("nbAiAiChk (instructions)", [=](Gen& g) {
        const int32_t index = someCheck(g);
        return Pair{[=] { return iface::origVm(0x002867a8, {kAct, sx(index)}); }, [=] { return norm(nb::ai::check(act(), index)); }};
    });
    add("nbAiGetKoudou (instructions)", [=](Gen& g) {
        const uint32_t table = someTable(g);
        return Pair{[=] { return iface::origVm(0x00286888, {kAct, table}); }, [=] { return norm(nb::ai::drawAction(act(), table)); }};
    });
    add("nbAiSetKoudou (instructions)", [=](Gen& g) {
        const uint32_t table = someTable(g);
        const int32_t action = g.range(0, 4);
        return Pair{[=] { return iface::origVmVoid(0x002869a0, {kAct, table, sx(action)}); },
                    [=] { nb::ai::setAction(act(), table, action); return uint64_t{0}; }};
    });
    add("nbAiChkCost (instructions)", [](Gen&) {
        return Pair{[] { return iface::origVm(0x00287860, {kAct}); }, [] { return norm(nb::ai::costBlocks(act())); }};
    });
    add("nbAiChkClose (instructions)", [](Gen&) {
        return Pair{[] { return iface::origVm(0x00287928, {kAct}); }, [] { return norm(nb::ai::canProceed(act())); }};
    });
    add("nbRunAiSub (instructions)", [=](Gen& g) {
        const uint32_t table = someTable(g);
        return Pair{[=] { return iface::origVm(0x00287b40, {kAct, table}); }, [=] { return norm(nb::ai::runTable(act(), table)); }};
    });
    add("nbRunAi (instructions)", [](Gen&) {
        return Pair{[] { return iface::origVm(0x00287cb8, {kAct}); }, [] { return norm(nb::ai::run(act())); }};
    });
    // ---- the ailment AI (against the original instructions) ----
    // An ailing unit: panicked, charmed, cursed or neither; sometimes a
    // Demi-fiend or an ally devil; healing and buff skills to choose from.
    auto bad = [&](const char* name, std::function<Pair(Gen&)> make) {
        add(name, [make](Gen& g) {
            if (g.chance(50)) {   // the actor on the player's side
                int f = g.range(0, 3), tries = 0;
                while (!formUnit(f) && ++tries < 20)
                    f = g.range(0, 3);
                if (formUnit(f)) {
                    nb::ActionProcessData& a = act();
                    a.form.address = FW_FORMS + 0xf0 * static_cast<uint32_t>(f);
                    a.partyindex = f;
                    a.party.address = FW_PARTY + 128u * static_cast<uint32_t>(f);
                    a.work.address = formUnit(f);
                }
            }
            UnitWork& unit = *act().work;
            unit.badstat = static_cast<uint16_t>(g.pick<int32_t>({0, 8, 8, 0x80, 0x80, 4, 0x40}) |
                                                 (g.chance(30) ? kBadStatCurse : 0));
            unit.flag &= ~0x24u;
            unit.flag |= g.pick<uint32_t>({0, 4, 0x20, 0x20});
            if (g.chance(30))
                unit.id = static_cast<uint16_t>(g.range(0x100, 0x17f));
            for (int i = 0; i < unit.skillcnt && i < 24; ++i)
                if (g.chance(30))
                    unit.skill[i] = static_cast<uint16_t>(g.chance(50) ? g.range(0x24, 0x29) : g.range(0x40, 0x44));
            act().party->flag = static_cast<int16_t>(act().party->flag & ~0x800);
            if (g.chance(20))
                act().party->flag = static_cast<int16_t>(act().party->flag | 0x800);
            dat::globalWork().macca = g.chance(20) ? 0 : g.range(1, 99999);
            if (g.chance(20))
                mainData().stat |= 1;
            mainData().stat = g.chance(50) ? mainData().stat | 8 : mainData().stat & ~8u;
            return make(g);
        });
    };
    auto badVoid = [](uint32_t entry, auto rewrite) {
        return Pair{[=] { return iface::origVmVoid(entry, {kAct}); }, [=] { rewrite(act()); return uint64_t{0}; }};
    };
    auto badInt = [](uint32_t entry, int32_t (*rewrite)(nb::ActionProcessData&)) {
        return Pair{[=] { return iface::origVm(entry, {kAct}); }, [=] { return norm(rewrite(act())); }};
    };
    bad("SetSingleTarget", [=](Gen& g) {
        if (g.chance(30)) {   // a single selectable slot
            const int keep = g.range(0, 15);
            for (int f = 0; f < 16; ++f)
                if (f != keep)
                    form(f).stat &= ~4u;
            form(keep).stat |= 4;
        }
        return badVoid(0x0028e3c8, nb::setSingleTarget);
    });
    bad("SetGroupTarget", [=](Gen&) { return badVoid(0x0028e470, nb::setGroupTarget); });
    bad("SetTarget", [](Gen& g) {
        const int32_t rev = g.range(0, 1);
        if (g.chance(50)) {   // any skill, for every target type
            act().work->nowcommand = 1;
            act().work->nowindex = static_cast<uint16_t>(g.range(1, 0x11f));
        }
        return Pair{[=] { return iface::origVm(0x0028e4b0, {kAct, sx(rev)}); }, [=] { return norm(nb::setTarget(act(), rev)); }};
    });
    bad("CheckBadActionSkill", [](Gen& g) {
        const int32_t skill = g.range(0x20, 0x48), type = g.range(1, 4);
        return Pair{[=] { return iface::origVm(0x0028e560, {sx(skill), sx(type)}); },
                    [=] { return norm(nb::ailmentSkillUsable(skill, type)); }};
    });
    bad("GetBadActionSkill", [](Gen& g) {
        const int32_t type = g.range(1, 4);
        return Pair{[=] { return iface::origVm(0x0028e5c8, {kAct, sx(type)}); },
                    [=] { return norm(nb::ailmentSkill(act(), type)); }};
    });
    bad("BadKaja", [=](Gen&) { return badInt(0x0028e758, nb::ailmentBuff); });
    bad("BadKaifuku", [=](Gen&) { return badInt(0x0028e818, nb::ailmentHeal); });
    bad("BadAttack", [=](Gen&) { return badInt(0x0028e8d8, nb::ailmentAttack); });
    bad("BadMaka", [=](Gen&) { return badInt(0x0028e9b8, nb::ailmentThrowMacca); });
    bad("BadNego", [=](Gen&) { return badInt(0x0028eab8, nb::ailmentTalk); });
    bad("BadReturn", [=](Gen&) { return badInt(0x0028eb80, nb::ailmentReturn); });
    bad("BadBadWait", [=](Gen&) { return badInt(0x0028ec18, nb::ailmentLoseTurn); });
    bad("BadDamage", [=](Gen&) { return badInt(0x0028ec90, nb::ailmentSelfDamage); });
    bad("MakeRituList", [=](Gen&) { return badVoid(0x0028edc8, nb::buildAilmentWeights); });
    bad("GetBadAiAction", [](Gen& g) {
        nb::buildAilmentWeights(act());
        auto* list = &at<nb::AilmentWeight>(difftest::version::dataOrDie(0x00575490));
        for (int i = 0; i < at<int32_t>(difftest::version::dataOrDie(0x00551558)); ++i)
            if (g.chance(25))
                list[i].weight = 0;
        return Pair{[] { return iface::origVm(0x0028ecc8, {}); }, [] { return norm(nb::chooseAilmentAction()); }};
    });
    bad("AddRituList", [](Gen& g) {
        at<int32_t>(difftest::version::dataOrDie(0x00551558)) = g.range(0, 9);
        const int32_t type = g.range(0, 9), ritu = g.range(0, 60);
        return Pair{[=] { return iface::origVmVoid(0x0028ed98, {sx(type), sx(ritu)}); },
                    [=] { nb::addAilmentWeight(type, ritu); return uint64_t{0}; }};
    });
    bad("nbRunBadAi", [=](Gen&) { return badInt(0x0028f0a0, nb::runAilmentAi); });
    bad("nbSetJyokyoMes", [](Gen& g) {
        const int32_t mes = g.range(0, 0x60), id = g.range(-1, 3), ind = g.range(0, 0x17f);
        return Pair{[=] { return iface::origVmVoid(0x002592b0, {kAct, sx(mes), sx(id), sx(ind)}); },
                    [=] { nb::setStatusMessage(act(), mes, id, ind); return uint64_t{0}; }};
    });
    bad("nbGetJyokyoMes", [](Gen& g) {
        const int32_t mes = g.range(0, 0x60);
        return Pair{[=] { return iface::origVm(0x00259300, {FW_MAIN, sx(mes)}); },
                    [=] { return norm(nb::statusMessage(mainData(), mes)); }};
    });

    // ---- choosing a target (against the original instructions) ----
    // A target selection in progress for the actor: the lists, the cursor,
    // its animation, the pad.
    auto tarsel = [&](const char* name, std::function<Pair(Gen&)> make) {
        add(name, [make](Gen& g) {
            std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);   // the fakes' pool
            auto& t = at<nb::TargetCursor>(FW_TARSEL);
            t.stat = static_cast<uint8_t>(g.chance(70) ? 1 : g.range(0, 2));
            t.ctype = static_cast<int8_t>(g.chance(10) ? g.range(-1, 3) : g.range(0, 2));
            t.friendcnt = static_cast<int8_t>(g.range(0, 4));
            t.enemycnt = static_cast<int8_t>(g.chance(15) ? 0 : g.range(1, 10));
            for (int i = 0; i < 12; ++i) {
                t.friendno[i] = static_cast<int8_t>(g.range(0, 3));
                t.enemyno[i] = static_cast<int8_t>(g.range(4, 13));
            }
            t.nowcarea = static_cast<uint8_t>(g.chance(10) ? g.range(0, 3) : g.range(1, 2));
            const int count = t.nowcarea == 1 ? t.friendcnt : t.enemycnt;
            t.nowno = static_cast<int8_t>(count > 0 ? g.range(0, count - 1) : 0);
            t.nowform = static_cast<int8_t>(g.range(0, 13));
            t.partyindex = static_cast<int16_t>(act().partyindex);
            t.nameDelay = g.range(0, 3);
            t.time = g.range(0, 29);
            for (int i = 0; i < 8; ++i)   // the pad: nothing, a fresh press, a repeat
                at<uint8_t>(difftest::version::dataOrDie(0x002f5830) + static_cast<uint32_t>(i)) = static_cast<uint8_t>(g.pick<int32_t>({0, 0, 0, 0x80, 2, 0x82}));
            dat::globalWork().config = static_cast<uint32_t>(g.rng());
            mainData().stat = g.chance(30) ? (mainData().stat ^ 8u) : mainData().stat;
            mainData().stat = g.chance(10) ? (mainData().stat | 0x200000u) : (mainData().stat & ~0x200000u);
            act().stat = g.chance(20) ? (act().stat | 0x80u) : (act().stat & ~0x80u);
            if (g.chance(10))
                at<nb::TargetCursor>(FW_TARSEL).act.address = 0;
            UnitWork& unit = *act().work;
            unit.prevtarea = static_cast<int16_t>(g.range(-1, 3));
            unit.prevtform = static_cast<int16_t>(g.range(-1, 13));
            for (int f = 0; f < 16; ++f) {
                form(f).anime = g.chance(30) ? (form(f).anime | 8u) : (form(f).anime & ~8u);
                if (g.chance(30)) form(f).stat ^= 8u;
            }
            return make(g);
        });
    };
    auto tVoid = [](uint32_t entry, void (*rewrite)(nb::TargetCursor&)) {
        return Pair{[=] { return iface::origVmVoid(entry, {FW_TARSEL}); }, [=] { rewrite(at<nb::TargetCursor>(FW_TARSEL)); return uint64_t{0}; }};
    };
    tarsel("nbGetTarSelStat", [](Gen&) { return Pair{[] { return iface::origVm(0x0025d6b8, {}); }, [] { return norm(nb::targetCursorState()); }}; });
    tarsel("nbSetTarSelStat", [](Gen& g) {
        const int32_t s = g.range(0, 300);
        return Pair{[=] { return iface::origVmVoid(0x0025d6d8, {sx(s)}); }, [=] { nb::setTargetCursorState(s); return uint64_t{0}; }};
    });
    tarsel("nbSetTarSelJyokyoTime", [](Gen& g) {
        const int32_t s = g.range(-2, 30);
        return Pair{[=] { return iface::origVmVoid(0x0025d700, {sx(s)}); }, [=] { nb::setTargetNameDelay(s); return uint64_t{0}; }};
    });
    tarsel("AnimeTargetCursor", [=](Gen&) { return tVoid(0x0025d728, nb::animateTargetCursor); });
    tarsel("SetCursor", [=](Gen&) { return tVoid(0x0025de40, nb::placeTargetCursor); });
    tarsel("UpdateSelect", [=](Gen&) { return tVoid(0x0025e100, nb::markTargets); });
    tarsel("OnOffTargetCursor", [=](Gen&) { return tVoid(0x0025e278, nb::showTargetCursors); });
    tarsel("DispTargetHelp", [=](Gen& g) {
        iface::helpWorld(g);
        return tVoid(0x0025e300, nb::showTargetName);
    });
    tarsel("MemoryCommand", [=](Gen&) { return tVoid(0x0025e3f8, nb::rememberTarget); });
    tarsel("CursorSelect", [=](Gen&) { return tVoid(0x0025e448, nb::readTargetPad); });
    tarsel("CursorSelectAuto", [=](Gen&) { return tVoid(0x0025e6e0, nb::chooseTargetAutomatically); });
    tarsel("CheckFriend", [](Gen& g) {
        const int32_t f = g.range(-1, 16);
        return Pair{[=] { return iface::origVm(0x0025e070, {FW_TARSEL, sx(f)}); },
                    [=] { return norm(nb::onActorSide(at<nb::TargetCursor>(FW_TARSEL), f) ? 1 : 0); }};
    });
    tarsel("CheckEnemy", [](Gen& g) {
        const int32_t f = g.range(-1, 16);
        return Pair{[=] { return iface::origVm(0x0025e0b8, {FW_TARSEL, sx(f)}); },
                    [=] { return norm(nb::onOtherSide(at<nb::TargetCursor>(FW_TARSEL), f) ? 1 : 0); }};
    });
    tarsel("nbSetTargetProcess", [](Gen& g) {
        const int32_t ctype = g.range(0, 2), crule = g.range(0, 4), carea = g.range(0, 3);
        const int32_t pi = act().partyindex;
        return Pair{[=] { return iface::origVm(0x0025dfa0, {kAct, sx(pi), sx(ctype), sx(crule), sx(carea)}); },
                    [=] { return norm(nb::startTargetCursor(act(), pi, ctype, crule, carea) ? 1 : 0); }};
    });
    tarsel("nbTarSelProcess1", [](Gen& g) {
        iface::helpWorld(g);
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x005442b8), 0x3f9, 1, 1, 0, 0, FW_TARSEL));
        return Pair{[=] { return iface::origVm(0x0025e720, {process}); }, [=] { return norm(nb::runTargetCursor(process)); }};
    });
    tarsel("nbTarSelShutdown", [](Gen&) {
        const uint32_t data = ps2PoolAllocate(0x44);
        at<nb::TargetCursor>(data).data.address = FW_MAIN;
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x005442b8), 0x3f9, 1, 1, 0, 0, data));
        return Pair{[=] { return iface::origVmVoid(0x0025e7d8, {process}); }, [=] { nb::shutdownTargetCursor(process); return uint64_t{0}; }};
    });
    tarsel("InitTarSelProcessData", [](Gen&) {
        return Pair{[] { return iface::origVm(0x0025e800, {FW_MAIN}); },
                    [] { return norm(static_cast<int32_t>(nb::newTargetCursor(mainData()))); }};
    });
    tarsel("nbInitTarSelProcess", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x0025e870, {FW_MAIN}); }, [] { nb::startTargetCursorProcess(mainData()); return uint64_t{0}; }};
    });
    tarsel("nbPlaySe", [](Gen& g) {
        const int32_t se = g.range(0, 40);
        return Pair{[=] { return iface::origVmVoid(0x0028d090, {sx(se)}); }, [=] { nb::playBattleSound(se); return uint64_t{0}; }};
    });
    tarsel("dds3CheckConfigBit", [](Gen& g) {
        const int32_t type = g.range(-1, 6);
        return Pair{[=] { return iface::origVm(0x0029bae0, {sx(type)}); }, [=] { return norm(nb::configOption(type)); }};
    });
    tarsel("SetTarget", [](Gen& g) {
        act().work->nowcommand = static_cast<int16_t>(g.pick<int32_t>({0, 1, 1, 6, 5, 3}));
        if (g.chance(30))
            act().work->nowindex = 0xdf;
        return Pair{[] { return iface::origVmVoid(0x00251428, {kAct}); }, [] { nb::setTarget(act()); return uint64_t{0}; }};
    });
    tarsel("SetAction_TARSEL", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x00254178, {kAct}); }, [] { nb::enterTargetSelect(act()); return uint64_t{0}; }};
    });

    // ---- whether a skill would do anything ----
    // Targets hurt or not, ailing or not, buffs near their limits; the
    // skills each check knows about.
    static const int32_t kErrorSkills[] = {0x24, 0x27, 0x29, 0x51, 0x5e, 0x2a, 0x52, 0x5d, 0x2b, 0x2e, 0x30, 0x58, 0x31, 0x32,
                                           0x33, 0x55, 0xed, 0xf8, 0x44, 0x46, 0xe0, 0xda, 0x34, 0x36, 0x40, 0x43, 0xcb,
                                           0xce, 0x109, 0x114, 0x49, 0x4a, 0x4b, 0x4c, 0x50, 0x10, 0x60, 0x100};
    // HP or MP: full, one short, empty or anything (all full sometimes).
    auto points = [](Gen& g, uint16_t max, bool full) {
        if (full)
            return max;
        switch (g.below(4)) {
        case 0: return max;
        case 1: return static_cast<uint16_t>(max - 1);
        case 2: return uint16_t{0};
        default: return static_cast<uint16_t>(g.range(0, max));
        }
    };
    auto skillWorld = [=](Gen& g) {
        auto unitAt = [](uint32_t address) -> UnitWork& { return at<UnitWork>(address); };
        const bool allHp = g.chance(40), allMp = g.chance(40);
        for (int f = 0; f < 16; ++f) {
            if (!formUnit(f))
                continue;
            UnitWork& u = unitAt(formUnit(f));
            u.maxhp = static_cast<uint16_t>(g.range(1, 500));
            u.hp = points(g, u.maxhp, allHp);
            u.maxmp = static_cast<uint16_t>(g.range(1, 300));
            u.mp = points(g, u.maxmp, allMp);
            u.badstat = static_cast<uint16_t>(g.chance(60) ? 0 : 1u << g.range(0, 11));
        }
        // Buff counters: anything, or all at their upper or all at their lower limit.
        const int limits = g.below(3);
        for (int k = 0; k < 14; ++k)
            for (int c = 4; c < 16; ++c)
                party(k).count[c] = static_cast<int16_t>(limits == 1   ? nb::buffMax(c, 0)
                                                         : limits == 2 ? nb::buffMin(c, 0)
                                                         : g.chance(50) ? g.pick<int32_t>({4, -4, 1, -1}) : g.range(-4, 4));
        GlobalWork& global = dat::globalWork();
        for (int i = 0; i < 16; ++i) {
            UnitWork& u = global.units[i];
            u.flag = g.chance(70) ? (u.flag | 1u) : (u.flag & ~1u);
            u.maxhp = static_cast<uint16_t>(g.range(1, 500));
            u.hp = points(g, u.maxhp, allHp);
            u.maxmp = static_cast<uint16_t>(g.range(1, 300));
            u.mp = points(g, u.maxmp, allMp);
            u.badstat = static_cast<uint16_t>(g.chance(60) ? 0 : g.chance(40) ? 0x800 : 1u << g.range(0, 11));
        }
        global.fieldskills = static_cast<uint32_t>(g.below(16));
        if (g.chance(10))
            mainData().stat |= 0x08000000;
        else
            mainData().stat &= ~0x08000000u;
    };
    auto pickSkill = [](Gen& g) {
        if (g.chance(20))   // the rarer branches
            return g.pick<int32_t>({0xda, 0x114, 0x35, 0xcc, 0xce, 0xe0});
        return g.chance(85) ? g.pick(kErrorSkills) : g.range(0, 0x11f);
    };
    auto select = [](Gen& g) {
        if (g.chance(40))
            return 1u << g.below(16);   // a single target
        return static_cast<uint32_t>(g.rng()) & 0xffffu;
    };
    // ---- choosing a command ----
    // The acting unit (the Demi-fiend or a demon) with skills of every kind,
    // items, a stock, battle flags, the pad, and its menu at FW_COMMSEL
    // filled by the rewrite's SetCommList (tested on its own) and then
    // scrambled.
    auto commUnit = [](Gen& g) {
        ActionProcessData& a = act();
        party(a.partyindex).formindex = static_cast<int16_t>(a.partyindex);
        UnitWork& unit = *a.work;
        unit.flag = g.chance(50) ? (unit.flag | UnitFlag::PlayerCharacter) : (unit.flag & ~UnitFlag::PlayerCharacter);
        unit.badstat = static_cast<uint16_t>(g.chance(60) ? 0 : g.pick<int32_t>({0x20, 0x200, 0x800, 0x8020, 1, 0x40}));
        unit.skillcnt = static_cast<uint16_t>(g.range(0, 24));
        for (uint16_t& s : unit.skill)
            s = static_cast<uint16_t>(g.chance(10) ? 0 : g.chance(15) ? g.pick<int32_t>({0x48, 0xdf, 0x33, 0x10})
                                                       : g.chance(30) ? g.range(0x180, 0x1ff) : g.range(1, 0x17f));
        // Hardtype reads a register the skill list leaves: the summoning
        // skill last leaves the RNG's second state word, so make that an
        // address in RAM.
        if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype) {
            for (uint32_t address : {4u, 6u, 0x14u})   // ... or a small number: 0, 2 or 16
                at<uint16_t>(address) = static_cast<uint16_t>(g.chance(50) ? 0 : g.range(1, 0xffff));
            if (g.chance(40)) {
                if (unit.skillcnt > 0)
                    unit.skill[unit.skillcnt - 1] = 0xdf;
                at<uint32_t>(difftest::version::dataOrDie(0x00529bdc)) = g.pick<uint32_t>({FW_MAIN, kAct, act().party.address, 0x10, 0});
                mainData().playerpcnt = static_cast<int16_t>(g.range(0, 4));
            }
        }
        unit.prevcommand = static_cast<int16_t>(g.range(-1, 8));
        unit.previndex = static_cast<uint16_t>(g.chance(50) ? unit.skill[g.below(24)] : g.range(0, 0x9f));
        a.stat = g.chance(30) ? (a.stat | 0x80u) : (a.stat & ~0x80u);
        MainProcessData& main = mainData();
        main.stat &= ~0x04200005u;
        main.stat |= (g.chance(30) ? 1u : 0u) | (g.chance(30) ? 4u : 0u) | (g.chance(5) ? 0x200000u : 0u) | (g.chance(5) ? 0x4000000u : 0u);
        main.CommandMenuProcessID = g.chance(50) ? FW_COMMSEL_PROCESS : 0x00777000;
        GlobalWork& global = dat::globalWork();
        for (uint8_t& count : global.item_counts)
            count = static_cast<uint8_t>(g.chance(30) ? g.range(1, 9) : 0);
        global.stock_count = g.range(0, 16);
        for (int i = 0; i < 16; ++i) {
            global.stock_list[i] = static_cast<uint8_t>(g.below(16));
            UnitWork& u = global.units[i];
            u.flag = static_cast<uint32_t>(g.below(8));
            u.hp = static_cast<uint16_t>(g.chance(20) ? 0 : g.range(1, 300));
            u.badstat = static_cast<uint16_t>(g.chance(20) ? 0x800 : 0);
        }
        global.config = static_cast<uint32_t>(g.rng());
        // The pad: usually one or two buttons, just pressed (0x82) or held (2).
        for (int i = 0; i < 16; ++i)
            at<uint8_t>(nb::pad::kAddress + static_cast<uint32_t>(i)) = 0;
        for (int n = g.range(0, 2); n > 0; --n)
            at<uint8_t>(nb::pad::kAddress + static_cast<uint32_t>(g.chance(70) ? g.pick<int32_t>({4, 5, 6, 6, 7, 7}) : g.range(0, 15))) =
                static_cast<uint8_t>(g.pick<int32_t>({0x82, 0x82, 0x02, 0x80}));
    };
    auto commWorld = [=](Gen& g) {
        commUnit(g);
        nb::CommandMenu& d = at<nb::CommandMenu>(FW_COMMSEL);
        std::memset(&d, 0, sizeof d);
        d.mem = 0x00777301;
        d.data.address = FW_MAIN;
        d.act.address = kAct;
        d.my.address = act().party.address;
        nb::fillCommandLists(d, *d.my);
        d.state = static_cast<int8_t>(g.range(0, 4));
        d.tab = static_cast<uint8_t>(g.below(6));
        for (int t = 0; t < 6; ++t) {
            if (d.counts[t] > 3 && g.chance(20))    // short lists too
                d.counts[t] = g.range(2, 3);
            const int32_t count = d.counts[t];
            d.nowcursor[t] = count > 0 ? g.range(0, count - 1) : 0;
            if (count > 0 && g.chance(30))   // at an end
                d.nowcursor[t] = g.chance(50) ? 0 : count - 1;
            d.nowlisty[t] = count > 0 ? std::max(0, d.nowcursor[t] - g.range(0, 3)) : 0;
            for (int i = 0; i < count; ++i)
                if (g.chance(10))
                    d.unavailable[t][i] = static_cast<int8_t>(g.range(-1, 6));
        }
        d.cnt = g.chance(70) ? 2 : 3;
        d.animation = static_cast<uint32_t>(g.below(0x40));
        d.alpha = g.chance(30) ? g.pick<int32_t>({0, 0x80}) : g.range(0, 0x80);
        d.helpAlpha = g.chance(30) ? g.pick<int32_t>({0, 0x80}) : g.range(0, 0x80);
        d.ox = g.chance(20) ? 0 : g.range(-40, 40);
        d.summonGrow = g.chance(20) ? ee::Float::fromBits(g.pick<uint32_t>({0u, 0x3c23d70au, 0x80000000u}))
                                : ee::Float::fromInt(g.range(0, 100)) / ee::Float::fromInt(100);
    };
    auto comm = [&, commWorld](const char* name, std::function<Pair(Gen&)> make) {
        add(name, [=](Gen& g) { commWorld(g); return make(g); });
    };
    auto commVoid = [](uint32_t entry, void (*rewrite)(nb::CommandMenu&)) {
        return Pair{[=] { return iface::origVmVoid(entry, {FW_COMMSEL}); },
                    [=] { rewrite(at<nb::CommandMenu>(FW_COMMSEL)); return uint64_t{0}; }};
    };
    comm("GetCommSelProcessData", [](Gen&) {
        return Pair{[] { return iface::origVm(0x00259cf8, {}); },
                    [] { return norm(static_cast<int32_t>(iface::addr(&nb::commandMenu()))); }};
    });
    comm("GetCommListCnt", [](Gen& g) {
        const int32_t tab = g.range(0, 5);
        return Pair{[=] { return iface::origVm(0x00259c90, {FW_COMMSEL, sx(tab)}); },
                    [=] { return norm(nb::visibleRows(at<nb::CommandMenu>(FW_COMMSEL), tab)); }};
    });
    comm("AnimeCommandList", [=](Gen&) { return commVoid(0x0025b408, nb::animateCommandMenu); });
    comm("CheckSelectError", [](Gen&) {
        return Pair{[] { return iface::origVm(0x0025c190, {FW_COMMSEL}); },
                    [] { return norm(nb::entryUnavailable(at<nb::CommandMenu>(FW_COMMSEL)) ? 1 : 0); }};
    });
    comm("MemoryCommandComm (0x25C1D8)", [=](Gen&) { return commVoid(0x0025c1d8, nb::commitCommand); });
    comm("GetNextCommType", [](Gen& g) {
        const bool right = g.chance(50);
        if (g.chance(30))   // tabs left empty
            for (int32_t& count : at<nb::CommandMenu>(FW_COMMSEL).counts)
                if (g.chance(50))
                    count = 0;
        return Pair{[=] { return iface::origVm(0x0025c308, {FW_COMMSEL, right ? 1u : 0u}); },
                    [=] { return norm(nb::nextTab(at<nb::CommandMenu>(FW_COMMSEL), right)); }};
    });
    comm("SelectCommandList", [=](Gen& g) {
        // Mostly up or down on a tab with a list to move through, the cursor
        // near an end of it or of the rows shown.
        nb::CommandMenu& d = at<nb::CommandMenu>(FW_COMMSEL);
        if (g.chance(60)) {
            for (int tries = 0; tries < 6 && d.counts[d.tab] < 2; ++tries)
                d.tab = static_cast<uint8_t>((d.tab + 1) % 6);
            const int32_t t = d.tab, count = d.counts[t];
            if (count >= 2) {
                const int32_t rows = nb::visibleRows(d, t);
                d.nowcursor[t] = g.pick<int32_t>({0, 1, count - 1, count - 2, g.range(0, count - 1)});
                d.nowcursor[t] = std::clamp(d.nowcursor[t], 0, count - 1);
                d.nowlisty[t] = std::max(0, g.chance(50) ? d.nowcursor[t] - rows + 1 + g.range(0, 1) : d.nowcursor[t] - g.range(0, 1));
                if (g.chance(30))
                    d.nowlisty[t] = std::max(0, count - rows);
            }
            at<uint8_t>(nb::pad::kAddress + (g.chance(50) ? 6u : 7u)) = static_cast<uint8_t>(g.chance(60) ? 0x82 : 0x02);
        }
        return commVoid(0x0025c368, nb::readCommandPad);
    });
    comm("SelectCommandListAuto", [=](Gen&) { return commVoid(0x0025c840, nb::chooseCommandAutomatically); });
    comm("nbGetCommSelStat", [](Gen&) {
        return Pair{[] { return iface::origVm(0x0025c888, {}); }, [] { return norm(nb::commandMenuState()); }};
    });
    comm("nbSetCommSelStat", [](Gen& g) {
        const int32_t s = g.range(-2, 300);
        return Pair{[=] { return iface::origVmVoid(0x0025c8a8, {sx(s)}); },
                    [=] { nb::setCommandMenuState(static_cast<int8_t>(s)); return uint64_t{0}; }};
    });
    comm("nbCloseCommSel", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x0025c8d0, {}); }, [] { nb::closeCommandMenu(); return uint64_t{0}; }};
    });
    comm("nbCommSelShutdown", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x0025cb40, {FW_COMMSEL_PROCESS}); },
                    [] { nb::shutdownCommandMenu(FW_COMMSEL_PROCESS); return uint64_t{0}; }};
    });
    comm("SetCommList", [](Gen&) {
        const uint32_t my = act().party.address;
        return Pair{[=] { return iface::origVmVoid(0x0025cb80, {FW_COMMSEL, my}); },
                    [=] { nb::fillCommandLists(at<nb::CommandMenu>(FW_COMMSEL), at<Party>(my)); return uint64_t{0}; }};
    });
    comm("SetPrevCursor", [](Gen& g) {
        const nb::CommandMenu& d = at<nb::CommandMenu>(FW_COMMSEL);
        const int32_t tab = g.range(0, 5);
        const int32_t index = d.counts[tab] > 0 && g.chance(80) ? g.range(0, d.counts[tab] - 1) : g.range(0, 8);
        return Pair{[=] { return iface::origVmVoid(0x0025d1e8, {FW_COMMSEL, sx(tab), sx(index)}); },
                    [=] { nb::placeCommandCursor(at<nb::CommandMenu>(FW_COMMSEL), tab, index); return uint64_t{0}; }};
    });
    comm("SetCommCursor2", [=](Gen&) { return commVoid(0x0025d2a0, nb::restorePreviousCommand); });
    comm("nbSetAutoCommSel", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x0025d4c0, {}); }, [] { nb::setAutoCommand(); return uint64_t{0}; }};
    });
    add("InitCommSelProcessData", [=](Gen& g) {
        commUnit(g);
        const uint32_t my = act().party.address;
        return Pair{[=] { return iface::origVm(0x0025d500, {FW_MAIN, my, kAct}); },
                    [=] { return norm(static_cast<int32_t>(nb::newCommandMenu(mainData(), at<Party>(my), act()))); }};
    });
    add("nbInitCommSelProcess", [=](Gen& g) {
        commUnit(g);
        mainData().MainProcessID = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), g.range(1, 9), 0, 0, 0, 0, FW_MAIN));
        const uint32_t my = act().party.address;
        return Pair{[=] { return iface::origVmVoid(0x0025d620, {FW_MAIN, my, kAct}); },
                    [=] { nb::startCommandMenu(mainData(), at<Party>(my), act()); return uint64_t{0}; }};
    });

    // ---- the states that choose: COMM, BAD, TARSEL, STKSEL ----
    // The menu world, the help line (skill errors say why) and the
    // target cursor; the unit's command as the menu left it.
    auto chooseWorld = [=](Gen& g) {
        commWorld(g);
        mainData().statusMessageTable = iface::helpWorld(g, {0x42, 0x46}).id;
        ActionProcessData& a = act();
        UnitWork& unit = *a.work;
        unit.nowcommand = static_cast<int16_t>(g.range(-1, 9));
        unit.nowindex = static_cast<uint16_t>(
            unit.nowcommand == 5 ? g.range(1, 0x9f)
            : g.chance(50)       ? g.pick<int32_t>({0xde, 0xdf, 0xe0, 0xe2, 0xe6, 0xfc, 0x31, 0x32, 0x24, 0x44, 0x46, 0x49, 0x4a})
                                 : g.range(1, 0x17f));
        a.party->flag = static_cast<int16_t>(g.chance(50) ? (a.party->flag | g.pick<int32_t>({2, 4})) : (a.party->flag & ~6));
        // Targets marked, some at full HP, some buffs at their limits (for
        // the skill-error checks).
        for (int f = 0; f < 16; ++f)
            form(f).stat = g.chance(40) ? (form(f).stat | 8u) : (form(f).stat & ~8u);
        for (int f = 4; f < 14; ++f)   // (a present enemy's slot has its unit, as in the game)
            if (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(form(f).partyindex)))
                form(f).stat &= ~1u;
        for (int f = 0; f < 16; ++f)
            if (formUnit(f) && g.chance(50)) {
                UnitWork& u = at<UnitWork>(formUnit(f));
                u.hp = u.maxhp;
                u.mp = u.maxmp;
            }
        for (int k = 0; k < 14; ++k)
            for (int c = 4; c < 16; ++c)
                if (g.chance(50))
                    party(k).count[c] = static_cast<int16_t>(g.pick<int32_t>({4, -4}));
        a.talkType = g.range(0, 6);
        at<nb::CommandMenu>(FW_COMMSEL).state = static_cast<int8_t>(g.chance(60) ? 3 : g.range(0, 4));
        at<nb::TargetCursor>(FW_TARSEL).stat = static_cast<uint8_t>(g.range(0, 3));
        at<int32_t>(difftest::version::dataOrDie(0x0054e824)) = g.chance(20) ? 1 : 0;   // the debug pad shortcuts
        for (int b : {3, 9, 11})
            if (g.chance(15))
                at<uint8_t>(nb::pad::kAddress + static_cast<uint32_t>(b)) = 0x80;
        mainData().stat = g.chance(20) ? (mainData().stat | 0x40u) : (mainData().stat & ~0x40u);
        for (int f = 0; f < 4; ++f)   // the party's slots, for the summon slot
            form(f).stat = g.chance(60) ? (form(f).stat | 1u) : (form(f).stat & ~1u);
    };
    auto state = [](uint32_t entry, int32_t (*rewrite)(ActionProcessData&)) {
        return Pair{[=] { return iface::origVm(entry, {kAct}); }, [=] { return norm(rewrite(act())); }};
    };
    auto stateVoid = [](uint32_t entry, void (*rewrite)(ActionProcessData&)) {
        return Pair{[=] { return iface::origVmVoid(entry, {kAct}); }, [=] { rewrite(act()); return uint64_t{0}; }};
    };
    add("SetAction_COMM", [=](Gen& g) {
        commUnit(g);
        // A presentation queue with FORMONOFF packets among others.
        const uint32_t queue = ps2PoolAllocate(static_cast<int32_t>(sizeof(nb::EffectQueue)));
        std::memset(&at<nb::EffectQueue>(queue), 0, sizeof(nb::EffectQueue));
        for (int n = g.range(0, 4); n > 0; --n)
            nb::addPacket(at<nb::EffectQueue>(queue), 0, 10, 0).type =
                static_cast<int8_t>(g.pick<int32_t>({nb::kFormOnOff, nb::kFormFlagOnOff, nb::kSe}));
        mainData().EffectQueueProcessID = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), 1, 0, 0, 0, 0, queue));
        mainData().stat = g.chance(30) ? (mainData().stat | 0x40u) : (mainData().stat & ~0x40u);
        return stateVoid(0x00253830, nb::enterCommand);
    });
    add("CheckAction_COMM", [=](Gen& g) {
        chooseWorld(g);
        if (g.chance(40)) {   // a skill aimed at the stock, chosen by hand
            UnitWork& unit = *act().work;
            unit.nowcommand = 1;
            unit.nowindex = static_cast<uint16_t>(g.pick<int32_t>({0x31, 0x32, 0x49, 0x4a}));
            act().party->flag = static_cast<int16_t>((act().party->flag & ~6) | g.pick<int32_t>({0, 2, 4, 6}));
            act().stat &= ~0x80u;
            at<nb::CommandMenu>(FW_COMMSEL).state = 3;
        }
        return state(0x002538a0, nb::updateCommand);
    });
    add("SetAction_BAD", [=](Gen&) { return stateVoid(0x00253de0, nb::enterAilment); });
    add("CheckAction_TARSEL", [=](Gen& g) {
        chooseWorld(g);
        if (g.chance(50)) {   // a target chosen by hand for a buff or a healing item
            UnitWork& unit = *act().work;
            const bool item = g.chance(50);
            unit.nowcommand = static_cast<int16_t>(item ? 5 : 1);
            unit.nowindex = static_cast<uint16_t>(item ? g.range(2, 6) : g.pick<int32_t>({0x44, 0x45, 0x46, 0xe0}));
            act().stat &= ~0x80u;
            mainData().stat &= ~0x40u;
            at<nb::TargetCursor>(FW_TARSEL).stat = 0;
            if (g.chance(60))
                for (int k = 0; k < 14; ++k)
                    for (int c = 4; c < 16; ++c)
                        party(k).count[c] = static_cast<int16_t>(nb::buffMax(c, 0));
        }
        return state(0x00254190, nb::updateTargetSelect);
    });
    add("SetAction_STKSEL", [=](Gen& g) {
        chooseWorld(g);
        act().select = static_cast<uint32_t>(g.rng());
        return stateVoid(0x00254360, nb::enterStockSelect);
    });
    add("CheckAction_STKSEL", [=](Gen& g) {
        chooseWorld(g);
        at<int32_t>(difftest::version::dataOrDie(0x00551120)) = g.chance(30) ? -1 : g.chance(30) ? -2 : g.range(0, 15);
        return state(0x002543a0, nb::updateStockSelect);
    });
    add("nbSetPlayerSummonFormation", [=](Gen& g) {
        for (int f = 0; f < 4; ++f) {
            form(f).stat = g.chance(50) ? (form(f).stat | 1u) : (form(f).stat & ~1u);
            form(f).stat = g.chance(30) ? (form(f).stat | 0x800u) : form(f).stat;
            form(f).r = ee::Float::fromBits(0x3f800000u + g.below(0x03000000u));   // 1 .. 128, any mantissa
            form(f).orgpos.x = ee::Float::fromInt(g.range(-500, 500));
            form(f).orgrot.y = ee::Float::fromInt(g.range(1, 7));
            form(f).rot.y = ee::Float::fromInt(g.range(-7, 0));
        }
        return Pair{[] { return iface::origVmVoid(0x0028b448, {FW_MAIN}); }, [] { nb::ai::prepareAllySummonSlot(mainData()); return uint64_t{0}; }};
    });

    // ---- the help line ----
    // On top of the AI world: the fonts, a message window and the line
    // showing something (iface::helpWorld).
    auto pickMessage = [](Gen& g, const iface::HelpWorld& w) {
        return g.chance(90) ? w.messages[g.below(static_cast<uint32_t>(w.messages.size()))] : 0;
    };
    auto pickColor = [](Gen& g) { return g.chance(60) ? g.pick<uint32_t>({0x89feff80u, 0xa09dc380u}) : static_cast<uint32_t>(g.rng()); };
    add("nbDispText", [=](Gen& g) {
        const iface::HelpWorld w = iface::helpWorld(g);
        static const char* const names[] = {"Pixie", "Jack Frost", "Mudo", "Lv 12"};
        const uint32_t t1 = iface::guestString(names[g.below(4)]);
        const uint32_t t2 = g.chance(50) ? iface::guestString(names[g.below(4)]) : 0;
        const int32_t type = g.pick<int32_t>({-1, 0, 0, 1, 1, 2, 2, 3});
        const int32_t max = g.range(-1, 60);
        const uint32_t col = pickColor(g);
        at<nb::HelpLine>(FW_HELP).reqmsgno = pickMessage(g, w);
        return Pair{[=] { return iface::origVmVoid(0x00288e18, {t1, t2, sx(type), sx(max), sx(static_cast<int32_t>(col))}); },
                    [=] { nb::showHelpText(t1, t2, type, max, col); return uint64_t{0}; }};
    });
    add("nbDispSkillName", [=](Gen& g) {
        iface::helpWorld(g);
        const int32_t id = g.range(1, 0x1ff);   // (0 is in Japanese, which the English font lacks)
        return Pair{[=] { return iface::origVmVoid(0x00289008, {sx(id)}); }, [=] { nb::showSkillName(id); return uint64_t{0}; }};
    });
    add("nbDispItemName", [=](Gen& g) {
        iface::helpWorld(g);
        const int32_t id = g.range(1, 0x9f);   // (0 is in Japanese)
        return Pair{[=] { return iface::origVmVoid(0x00289040, {sx(id)}); }, [=] { nb::showItemName(id); return uint64_t{0}; }};
    });
    add("nbDispMiscActionNameComm", [=](Gen& g) {
        iface::helpWorld(g);
        const int32_t comm = g.range(-1, 9);
        return Pair{[=] { return iface::origVmVoid(0x002890b0, {sx(comm)}); }, [=] { nb::showCommandName(comm); return uint64_t{0}; }};
    });
    add("nbDispBattleText", [=](Gen& g) {
        iface::helpWorld(g);
        const int32_t id = g.range(0, 14);
        return Pair{[=] { return iface::origVmVoid(0x002891a8, {sx(id)}); }, [=] { nb::showBattleText(id); return uint64_t{0}; }};
    });
    add("nbDispDevilName", [=](Gen& g) {
        iface::helpWorld(g);
        const int32_t id = g.chance(30) ? 0 : g.range(1, 0x17f);
        GlobalWork& global = dat::globalWork();
        for (int i = 0; i < 64; ++i) {   // the Demi-fiend's race comes from the Magatama mastered
            global.hearts_owned[i] = static_cast<uint8_t>(g.chance(50) ? 0 : g.below(256));
            global.hearts_skill_state[i] = static_cast<uint8_t>(g.chance(50) ? 0 : g.below(256));
        }
        return Pair{[=] { return iface::origVmVoid(0x002891e0, {sx(id)}); }, [=] { nb::showDevilName(id); return uint64_t{0}; }};
    });
    add("nbDispJyokyoHelp", [=](Gen& g) {
        const iface::HelpWorld w = iface::helpWorld(g);
        const int32_t no = pickMessage(g, w);
        // (index 0 of the item and skill names is in Japanese, which the English font lacks)
        const int32_t varId = g.range(-2, 11);
        // (within each kind's table: 25 Magatama, 32 areas and sub-areas)
        const int32_t last = varId == 9 ? 24 : varId == 6 || varId == 7 ? 31 : 0x9f;
        const int32_t varInd = g.chance(30) && varId != 3 && varId != 5 ? 0 : g.range(1, last);
        return Pair{[=] { return iface::origVmVoid(0x002892a8, {sx(w.id), sx(no), sx(varId), sx(varInd)}); },
                    [=] { nb::showStatusMessage(w.id, no, varId, varInd); return uint64_t{0}; }};
    });
    add("nbDispMsgHelp", [=](Gen& g) {
        const iface::HelpWorld w = iface::helpWorld(g);
        const int32_t no = pickMessage(g, w), type = g.range(-1, 4);
        return Pair{[=] { return iface::origVmVoid(0x00289310, {sx(w.id), sx(no), sx(type)}); },
                    [=] { nb::showHelpMessage(w.id, no, type); return uint64_t{0}; }};
    });
    add("nbHelpOff", [=](Gen& g) {
        iface::helpWorld(g);
        return Pair{[] { return iface::origVmVoid(0x00289450, {}); }, [] { nb::clearHelpLine(); return uint64_t{0}; }};
    });
    add("nbHelpShutdown", [=](Gen& g) {
        iface::helpWorld(g);
        return Pair{[] { return iface::origVmVoid(0x002898c0, {FW_HELP_PROCESS}); }, [] { nb::shutdownHelpLine(FW_HELP_PROCESS); return uint64_t{0}; }};
    });
    add("InitHelpProcessData", [](Gen&) {
        return Pair{[] { return iface::origVm(0x00289940, {}); }, [] { return norm(static_cast<int32_t>(nb::newHelpLine())); }};
    });
    add("nbInitHelpProcess", [](Gen& g) {
        mainData().MainProcessID = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), g.range(1, 9), 0, 0, 0, 0, FW_MAIN));
        return Pair{[] { return iface::origVmVoid(0x00289990, {FW_MAIN}); }, [] { nb::startHelpLine(mainData()); return uint64_t{0}; }};
    });

    add("CheckDeadUnit", [=](Gen& g) {
        skillWorld(g);
        return Pair{[] { return iface::origVm(0x00290048, {}); }, [] { return norm(nb::anyStockDead() ? 1 : 0); }};
    });
    // The checks over a target list: units (by formation) or parties, the
    // guest list for the original, the same pointers for the rewrite.
    struct UnitCheck { const char* name; uint32_t original; bool (*rewrite)(UnitWork* const*, int32_t); };
    static const UnitCheck kUnitChecks[] = {
        {"CheckDeadUnit2", 0x002900a0, nb::anyDead},
        {"CheckMaxHp", 0x002900e8, nb::allFullHp},
        {"CheckMaxMp", 0x00290138, nb::allFullMp},
    };
    auto unitList = [](Gen& g, std::vector<UnitWork*>& units) {
        // (the game lists only formations with a unit)
        std::vector<uint32_t> present;
        for (uint32_t f = 0; f < 14; ++f)
            if (const uint32_t unit = at<uint32_t>(FW_FORM_UNITS + 4u * f))
                present.push_back(unit);
        const int32_t cnt = present.empty() ? 0 : g.range(0, 6);
        for (int32_t i = 0; i < cnt; ++i) {
            const uint32_t unit = present[g.below(static_cast<uint32_t>(present.size()))];
            at<uint32_t>(FW_SCRATCH + 4u * static_cast<uint32_t>(i)) = unit;
            units.push_back(&at<UnitWork>(unit));
        }
        return cnt;
    };
    for (const UnitCheck& check : kUnitChecks) {
        const UnitCheck* c = &check;
        add(c->name, [=](Gen& g) {
            skillWorld(g);
            auto units = std::make_shared<std::vector<UnitWork*>>();
            const int32_t cnt = unitList(g, *units);
            return Pair{[=] { return iface::origVm(c->original, {FW_SCRATCH, sx(cnt)}); },
                        [=] { return norm(c->rewrite(units->data(), cnt) ? 1 : 0); }};
        });
    }
    add("CheckBad", [=](Gen& g) {
        skillWorld(g);
        auto units = std::make_shared<std::vector<UnitWork*>>();
        const int32_t cnt = unitList(g, *units);
        const uint32_t bad = g.chance(50) ? 1u << g.below(16) : static_cast<uint32_t>(g.rng());
        return Pair{[=] { return iface::origVm(0x00290188, {FW_SCRATCH, sx(cnt), bad}); },
                    [=] { return norm(nb::anyHasAilment(units->data(), cnt, bad) ? 1 : 0); }};
    });
    add("CheckHojo", [=](Gen& g) {
        skillWorld(g);
        auto parties = std::make_shared<std::vector<Party*>>();
        const int32_t cnt = g.range(0, 6);
        for (int32_t i = 0; i < cnt; ++i) {
            const uint32_t party = FW_PARTY + static_cast<uint32_t>(sizeof(Party)) * static_cast<uint32_t>(g.range(0, 13));
            at<uint32_t>(FW_SCRATCH + 4u * static_cast<uint32_t>(i)) = party;
            parties->push_back(&at<Party>(party));
        }
        const uint32_t hojo = g.chance(60) ? 1u << g.below(25) : static_cast<uint32_t>(g.rng());
        return Pair{[=] { return iface::origVm(0x002901d0, {FW_SCRATCH, sx(cnt), hojo}); },
                    [=] { return norm(nb::anyBuffMovable(parties->data(), cnt, hojo) ? 1 : 0); }};
    });
    add("nbDispSkillErrorMessage", [=](Gen& g) {
        const int32_t err = g.range(-1, 5);
        mainData().statusMessageTable = iface::helpWorld(g, {0x42, 0x46}).id;
        return Pair{[=] { return iface::origVmVoid(0x00290490, {sx(err)}); }, [=] { nb::showSkillError(err); return uint64_t{0}; }};
    });
    add("nbCheckBattleSkillError1", [=](Gen& g) {
        skillWorld(g);
        const int32_t s = pickSkill(g);
        return Pair{[=] { return iface::origVm(0x00290520, {sx(s)}); }, [=] { return norm(nb::reviveError(s)); }};
    });
    add("nbCheckBattleSkillError2", [=](Gen& g) {
        skillWorld(g);
        const int32_t s = pickSkill(g);
        const uint32_t sel = select(g);
        return Pair{[=] { return iface::origVm(0x00290568, {sx(s), sel}); }, [=] { return norm(nb::targetSkillError(s, sel)); }};
    });
    add("nbCheckBattleSkillError3", [=](Gen& g) {
        skillWorld(g);
        // (and Hardtype's own buffs)
        const int32_t s = g.chance(20) ? g.pick<int32_t>({0x3a, 0x80, 0x85, 0x9c, 0xe4, 0xf4, 0x106, 0x11d}) : pickSkill(g);
        const uint32_t sel = select(g);
        return Pair{[=] { return iface::origVm(0x00290780, {sx(s), sel}); }, [=] { return norm(nb::buffSkillError(s, sel)); }};
    });
    add("nbCheckCampSkillError", [=](Gen& g) {
        skillWorld(g);
        const int32_t s = pickSkill(g);
        const uint32_t sel = select(g);
        return Pair{[=] { return iface::origVm(0x00290908, {sx(s), sel}); }, [=] { return norm(nb::menuSkillError(s, sel)); }};
    });

    add("SetAction_AI", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x00253bf8, {kAct}); }, [] { nb::enterAi(act()); return uint64_t{0}; }};
    });

    // ---- choosing targets --------------------------------------------------------------
    struct Filter { const char* name; void (*legacy)(uint64_t); void (*rewrite)(nb::ActionProcessData&); };
    static const Filter kFilters[] = {
        {"nbAiSelLifeMin", nbAiSelLifeMin, nb::ai::selectLowestHp},
        {"nbAiSelBaarLv", nbAiSelBaarLv, nb::ai::selectLowestLevelNotFlying},
        {"nbAiSelLvMin", nbAiSelLvMin, nb::ai::selectLowestLevel},
        {"nbAiSelLight", nbAiSelLight, nb::ai::selectLight},
        {"nbAiSelDark", nbAiSelDark, nb::ai::selectDark},
        {"nbAiSelPlayer", nbAiSelPlayer, nb::ai::selectDemiFiend},
        {"nbAiSelJoken", nbAiSelJoken, nb::ai::selectByCondition},
        {"nbAiSelRnd", nbAiSelRnd, nb::ai::selectAll},
    };
    for (const Filter& f : kFilters)
        add(f.name, [f, none](Gen&) { return Pair{none([f] { f.legacy(kAct); }), none([f] { f.rewrite(act()); })}; });
    add("nbAiSelBad", [none](Gen& g) {
        int32_t ailment = g.pick({0, 1, 4, 0x20, 0x40, 0x200, 0x800});
        return Pair{none([=] { nbAiSelBad(kAct, sx(ailment)); }), none([=] { nb::ai::selectAilment(act(), ailment); })};
    });
    add("nbAiSelId", [none](Gen& g) {
        int32_t devil = g.chance(50) ? at<UnitWork>(formUnit(g.range(0, 3)) ? formUnit(g.range(0, 3)) : formUnit(4)).id : g.range(1, 383);
        return Pair{none([=] { nbAiSelId(kAct, sx(devil)); }), none([=] { nb::ai::selectDevil(act(), devil); })};
    });
    add("nbAiSelAi", [](Gen& g) {
        bool group = g.chance(30);
        return Pair{[=] { return norm(nbAiSelAi(kAct, 0, group ? 1 : 0)); }, [=] { return norm(nb::ai::selectBest(act(), 0, group)); }};
    });
    auto targetSelect = [&add](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            int32_t selector = g.chance(90) ? g.range(0, 10) : g.range(-1, 15);
            int32_t parameter = selector == 3 ? g.range(1, 383) : g.pick({0, 1, 0x20, 0x40, 0x800});
            return Pair{[=] { return norm(legacy(kAct, sx(selector), sx(parameter))); }, [=] { return norm(rewrite(act(), selector, parameter)); }};
        });
    };
    targetSelect("nbSetSingleTarget2", nbSetSingleTarget2, nb::ai::selectSingleTarget);
    targetSelect("nbSetGroupTarget2", nbSetGroupTarget2, nb::ai::selectGroupTarget);
    targetSelect("nbSetAiTarget", nbSetAiTarget, nb::ai::selectTargets);
    add("nbSetEnemySummonFormation", [](Gen& g) {
        int32_t devil = g.chance(80) ? g.range(1, 383) : g.range(-2, 0);
        return Pair{[=] { return norm(nbSetEnemySummonFormation(FW_MAIN, sx(devil))); },
                    [=] { return norm(nb::ai::prepareSummonSlots(mainData(), devil)); }};
    });
    add("nbGetSelectBit", [](Gen&) {
        return Pair{[] { return norm(nbGetSelectBit(FW_MAIN)); }, [] { return norm(static_cast<int32_t>(nb::ai::selectedBits(mainData()))); }};
    });
    add("nbSetNormalSkill0", [none](Gen&) {
        uint32_t unit = act().work.address;
        return Pair{none([=] { nbSetNormalSkill0(unit); }), none([=] { nb::ai::setNormalAttack(unitAt(unit)); })};
    });

    // ---- targeting ----------------------------------------------------------------------
    add("datGetItemSkillNo", [](Gen& g) {
        int32_t item = g.chance(30) ? 1 : g.range(0, 159);
        return Pair{[=] { return norm(datGetItemSkillNo(sx(item))); }, [=] { return norm(dat::itemSkill(item)); }};
    });
    add("nbGetItemSkillNo", [](Gen& g) {
        int32_t item = g.chance(30) ? 1 : g.range(0, 159);
        return Pair{[=] { return norm(nbGetItemSkillNo(kAct, sx(item))); }, [=] { return norm(nb::itemSkillFor(act(), item)); }};
    });
    add("nbGetTargetTypeRuleArea", [none](Gen& g) {
        int32_t reverse = g.range(0, 1);
        uint32_t unit = act().work.address;
        bool outputs = g.chance(90);
        return Pair{none([=] { nbGetTargetTypeRuleArea(kAct, unit, outputs ? kOut : 0, kOut + 4, outputs ? kOut + 8 : 0, sx(reverse)); }),
                    none([=] { nb::targetTypeRuleArea(act(), unitAt(unit), outputs ? &at<int32_t>(kOut) : nullptr, &at<int32_t>(kOut + 4),
                                                       outputs ? &at<int32_t>(kOut + 8) : nullptr, reverse != 0); })};
    });
    add("CheckFormCursor", [](Gen& g) {
        int32_t self = g.range(0, 15), type = g.range(0, 2), rule = g.range(0, 15), area = g.range(0, 3), target = g.range(0, 15);
        return Pair{[=] { return norm(CheckFormCursor(sx(self), sx(type), sx(rule), sx(area), sx(target))); },
                    [=] { return norm(nb::canTarget(self, type, rule, area, target)); }};
    });
    add("nbSetSelectOkMark", [](Gen& g) {
        int32_t partyIndex = g.range(0, 13), type = g.range(0, 2), rule = g.range(0, 15), area = g.range(0, 3);
        return Pair{[=] { return norm(nbSetSelectOkMark(sx(partyIndex), sx(type), sx(rule), sx(area))); },
                    [=] { return norm(nb::markTargetable(partyIndex, type, rule, area)); }};
    });

    // ---- script commands ------------------------------------------------------------------
    struct Command { const char* name; uint64_t (*legacy)(); int32_t (*rewrite)(); };
    static const Command kCommands[] = {
        {"nbCommand_AI_CHK_MYHP", nbCommand_AI_CHK_MYHP, nb::ai::script::checkOwnHp},
        {"nbCommand_AI_CHK_MYMP", nbCommand_AI_CHK_MYMP, nb::ai::script::checkOwnMp},
        {"nbCommand_AI_CHK_FRHP", nbCommand_AI_CHK_FRHP, nb::ai::script::checkAllyHp},
        {"nbCommand_AI_CHK_DMGCNT", nbCommand_AI_CHK_DMGCNT, nb::ai::script::checkDamageCount},
        {"nbCommand_AI_CHK_FRCNT", nbCommand_AI_CHK_FRCNT, nb::ai::script::checkAllyCount},
        {"nbCommand_AI_CHK_ENCNT", nbCommand_AI_CHK_ENCNT, nb::ai::script::checkEnemyCount},
        {"nbCommand_AI_CHK_MYBAD", nbCommand_AI_CHK_MYBAD, nb::ai::script::checkOwnAilment},
        {"nbCommand_AI_CHK_FRBAD", nbCommand_AI_CHK_FRBAD, nb::ai::script::checkAllyAilment},
        {"nbCommand_AI_CHK_ENBAD", nbCommand_AI_CHK_ENBAD, nb::ai::script::checkEnemyAilment},
        {"nbCommand_AI_CHK_ENALLBAD", nbCommand_AI_CHK_ENALLBAD, nb::ai::script::checkAllEnemiesAilment},
        {"nbCommand_AI_CHK_ENID", nbCommand_AI_CHK_ENID, nb::ai::script::checkEnemyDevil},
        {"nbCommand_AI_CHK_FRID", nbCommand_AI_CHK_FRID, nb::ai::script::checkAllyDevil},
        {"nbCommand_AI_CHK_ENHOJO", nbCommand_AI_CHK_ENHOJO, nb::ai::script::checkEnemyBuff},
        {"nbCommand_AI_CHK_FRHOJO", nbCommand_AI_CHK_FRHOJO, nb::ai::script::checkAllyBuff},
        {"nbCommand_AI_CHK_ENHOJOMAX", nbCommand_AI_CHK_ENHOJOMAX, nb::ai::script::checkEnemyBuffLimit},
        {"nbCommand_AI_CHK_FRHOJOMAX", nbCommand_AI_CHK_FRHOJOMAX, nb::ai::script::checkAllyBuffLimit},
        {"nbCommand_AI_CHK_BA", nbCommand_AI_CHK_BA, nb::ai::script::checkBackAttack},
        {"nbCommand_AI_CHK_ENLIGHT", nbCommand_AI_CHK_ENLIGHT, nb::ai::script::checkEnemyLight},
        {"nbCommand_AI_CHK_ENDARK", nbCommand_AI_CHK_ENDARK, nb::ai::script::checkEnemyDark},
        {"nbCommand_AI_CHK_POW", nbCommand_AI_CHK_POW, nb::ai::script::checkFocus},
        {"nbCommand_AI_CHK_PLV", nbCommand_AI_CHK_PLV, nb::ai::script::checkPlayerLevel},
        {"nbCommand_AI_CHK_PPARTYLV", nbCommand_AI_CHK_PPARTYLV, nb::ai::script::checkPartyLevel},
        {"nbCommand_AI_CHK_ENHAMAMHK", nbCommand_AI_CHK_ENHAMAMHK, nb::ai::script::checkExpelWeakness},
        {"nbCommand_AI_CHK_SKILLNOMP", nbCommand_AI_CHK_SKILLNOMP, nb::ai::script::checkCannotAfford},
        {"nbCommand_AI_CHK_ESCAPE", nbCommand_AI_CHK_ESCAPE, nb::ai::script::checkEscape},
        {"nbCommand_AI_GET_TURN", nbCommand_AI_GET_TURN, nb::ai::script::getTurn},
        {"nbCommand_AI_GET_PRESSKOUDO", nbCommand_AI_GET_PRESSKOUDO, nb::ai::script::getPressCount},
        {"nbCommand_AI_GET_MYLV", nbCommand_AI_GET_MYLV, nb::ai::script::getOwnLevel},
        {"nbCommand_AI_GET_MYAISYO", nbCommand_AI_GET_MYAISYO, nb::ai::script::getOwnAffinityRow},
        {"nbCommand_AI_GET_FUREA", nbCommand_AI_GET_FUREA, nb::ai::script::getMoonPhase},
        {"nbCommand_AI_ACT_ATTACK", nbCommand_AI_ACT_ATTACK, nb::ai::script::actAttack},
        {"nbCommand_AI_ACT_ESCAPE", nbCommand_AI_ACT_ESCAPE, nb::ai::script::actEscape},
        {"nbCommand_AI_ACT_SKILL", nbCommand_AI_ACT_SKILL, nb::ai::script::actSkill},
        {"nbCommand_AI_ACT_SUMMON", nbCommand_AI_ACT_SUMMON, nb::ai::script::actSummon},
        {"nbCommand_AI_SET_CRITICAL", nbCommand_AI_SET_CRITICAL, nb::ai::script::setCritical},
        {"nbCommand_AI_TAR_AI", nbCommand_AI_TAR_AI, nb::ai::script::targetByAi},
        {"nbCommand_AI_ACT_WAIT", nbCommand_AI_ACT_WAIT, nb::ai::script::actWait},
        {"nbCommand_AI_TAR_LIFEMIN", nbCommand_AI_TAR_LIFEMIN, nb::ai::script::targetLowestHp},
        {"nbCommand_AI_TAR_BAARLV", nbCommand_AI_TAR_BAARLV, nb::ai::script::targetLowestLevelNotFlying},
        {"nbCommand_AI_TAR_LVMIN", nbCommand_AI_TAR_LVMIN, nb::ai::script::targetLowestLevel},
        {"nbCommand_AI_TAR_BAD", nbCommand_AI_TAR_BAD, nb::ai::script::targetAilment},
        {"nbCommand_AI_TAR_ID", nbCommand_AI_TAR_ID, nb::ai::script::targetDevil},
        {"nbCommand_AI_TAR_LIGHT", nbCommand_AI_TAR_LIGHT, nb::ai::script::targetLight},
        {"nbCommand_AI_TAR_DARK", nbCommand_AI_TAR_DARK, nb::ai::script::targetDark},
        {"nbCommand_AI_TAR_PLAYER", nbCommand_AI_TAR_PLAYER, nb::ai::script::targetDemiFiend},
        {"nbCommand_AI_TAR_RND", nbCommand_AI_TAR_RND, nb::ai::script::targetAll},
        {"nbCommand_AI_TAR_JOKEN", nbCommand_AI_TAR_JOKEN, nb::ai::script::targetByCondition},
        {"nbCommand_AI", nbCommand_AI, nb::ai::script::runTableAi},
#if !NOCTURNE_VANILLA
        {"nbCommand_BTL_AI_ROT_CLR", nbCommand_BTL_AI_ROT_CLR, nb::ai::script::rotationClear},
        {"nbCommand_BTL_AI_ROT_NEXT", nbCommand_BTL_AI_ROT_NEXT, nb::ai::script::rotationNext},
        {"nbCommand_BTL_AI_ROT_GET", nbCommand_BTL_AI_ROT_GET, nb::ai::script::rotationGet},
#endif
        {"nbCommand_BTL_PNL_ON", nbCommand_BTL_PNL_ON, nb::ai::script::panelOn},
        {"nbCommand_BTL_CAM_ORG", nbCommand_BTL_CAM_ORG, nb::ai::script::cameraOrigin},
    };
    const size_t firstCommand = t.size();
    for (const Command& c : kCommands)
        add(c.name, [c](Gen& g) {
            if (std::strncmp(c.name, "nbCommand_AI_TAR_", 17) == 0 || std::strcmp(c.name, "nbCommand_AI_ACT_WAIT") == 0) {
                // A command the targets apply to, and stale marks to replace.
                ActionProcessData& a = act();
                a.work->nowcommand = static_cast<int16_t>(g.chance(80) ? g.pick<int32_t>({0, 1, 5}) : g.range(-1, 7));
                a.work->nowindex = static_cast<uint16_t>(g.range(0, 0x17f));
                a.select = static_cast<uint32_t>(g.rng());
            }
            return Pair{[c] { return norm(c.legacy()); }, [c] { return norm(c.rewrite()); }};
        });
    for (size_t k = firstCommand; k < t.size(); ++k)   // (against the legacy C)
        t[k].legacyC = true;
}

} // namespace difftest
