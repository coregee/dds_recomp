// Differential tests for the enemy AI and targeting
// (rewrite: src/battle/ai.cpp, ai_script.cpp, targeting.cpp;
// legacy: battle_ai_*.c, battle_targeting.c).
#include <cstdint>
#include <cstring>

#include "harness.hpp"
#include "interface_world.hpp"
#include "nocturne/battle/action.hpp"
#include "nocturne/battle/bad_ai.hpp"
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
    // Every devil has AI level 0 in the shipped data; patch the actor's
    // record so the dormant levels 1..3 are exercised too.
    const_cast<DevilAI&>(dat::devilAI(unit.id)).ailevel = static_cast<uint16_t>(g.chance(50) ? g.range(1, 3) : 0);
    unit.nowcommand = static_cast<int16_t>(g.pick({0, 1, 1, 1, 3, 5, 7, 4, 6}));
    unit.nowindex = unit.nowcommand == 5 ? static_cast<uint16_t>(g.range(0, 60)) : aiSkill(g);
    // Summon skills may target empty summon slots (0x800); with a (patched)
    // AI level the effect estimate would then read an absent unit, which the
    // original does through guest address 0. Levels are all 0 in the game.
    if (dat::devilAI(unit.id).ailevel != 0)
        for (int k = 0; k < 16; ++k)
            if (!(form(k).stat & 1))
                form(k).stat &= ~0x800u;

    auto& select = at<nb::TargetSelectData>(FW_TARSEL);
    std::memset(&select, 0, sizeof select);
    select.data.address = FW_MAIN;
    select.act.address = kAct;

    scriptWork();
    for (int i = 0; i < 8; ++i) scriptParam(i, g.chance(80) ? g.range(0, 100) : g.range(0, 0x17f));   // negative ones make invalid conditions
    at<int32_t>(0x005514e8) = g.range(-3, 20);   // the rotation counter (static, restored by the harness)
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
    buffQuery("nbAiChkHojoMax", nbAiChkHojoMax, nb::ai::buffAtLimit);
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
            dat::globalWork().maka = g.chance(20) ? 0 : g.range(1, 99999);
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
        return badVoid(0x0028e3c8, nb::SetSingleTarget);
    });
    bad("SetGroupTarget", [=](Gen&) { return badVoid(0x0028e470, nb::SetGroupTarget); });
    bad("SetTarget", [](Gen& g) {
        const int32_t rev = g.range(0, 1);
        if (g.chance(50)) {   // any skill, for every target type
            act().work->nowcommand = 1;
            act().work->nowindex = static_cast<uint16_t>(g.range(1, 0x11f));
        }
        return Pair{[=] { return iface::origVm(0x0028e4b0, {kAct, sx(rev)}); }, [=] { return norm(nb::SetTarget(act(), rev)); }};
    });
    bad("CheckBadActionSkill", [](Gen& g) {
        const int32_t skill = g.range(0x20, 0x48), type = g.range(1, 4);
        return Pair{[=] { return iface::origVm(0x0028e560, {sx(skill), sx(type)}); },
                    [=] { return norm(nb::CheckBadActionSkill(skill, type)); }};
    });
    bad("GetBadActionSkill", [](Gen& g) {
        const int32_t type = g.range(1, 4);
        return Pair{[=] { return iface::origVm(0x0028e5c8, {kAct, sx(type)}); },
                    [=] { return norm(nb::GetBadActionSkill(act(), type)); }};
    });
    bad("BadKaja", [=](Gen&) { return badInt(0x0028e758, nb::BadKaja); });
    bad("BadKaifuku", [=](Gen&) { return badInt(0x0028e818, nb::BadKaifuku); });
    bad("BadAttack", [=](Gen&) { return badInt(0x0028e8d8, nb::BadAttack); });
    bad("BadMaka", [=](Gen&) { return badInt(0x0028e9b8, nb::BadMaka); });
    bad("BadNego", [=](Gen&) { return badInt(0x0028eab8, nb::BadNego); });
    bad("BadReturn", [=](Gen&) { return badInt(0x0028eb80, nb::BadReturn); });
    bad("BadBadWait", [=](Gen&) { return badInt(0x0028ec18, nb::BadBadWait); });
    bad("BadDamage", [=](Gen&) { return badInt(0x0028ec90, nb::BadDamage); });
    bad("MakeRituList", [=](Gen&) { return badVoid(0x0028edc8, nb::MakeRituList); });
    bad("GetBadAiAction", [](Gen& g) {
        nb::MakeRituList(act());
        auto* list = &at<nb::BadRitu>(0x00575490);
        for (int i = 0; i < at<int32_t>(0x00551558); ++i)
            if (g.chance(25))
                list[i].ritu = 0;
        return Pair{[] { return iface::origVm(0x0028ecc8, {}); }, [] { return norm(nb::GetBadAiAction()); }};
    });
    bad("AddRituList", [](Gen& g) {
        at<int32_t>(0x00551558) = g.range(0, 9);
        const int32_t type = g.range(0, 9), ritu = g.range(0, 60);
        return Pair{[=] { return iface::origVmVoid(0x0028ed98, {sx(type), sx(ritu)}); },
                    [=] { nb::AddRituList(type, ritu); return uint64_t{0}; }};
    });
    bad("nbRunBadAi", [=](Gen&) { return badInt(0x0028f0a0, nb::nbRunBadAi); });
    bad("nbSetJyokyoMes", [](Gen& g) {
        const int32_t mes = g.range(0, 0x60), id = g.range(-1, 3), ind = g.range(0, 0x17f);
        return Pair{[=] { return iface::origVmVoid(0x002592b0, {kAct, sx(mes), sx(id), sx(ind)}); },
                    [=] { nb::nbSetJyokyoMes(act(), mes, id, ind); return uint64_t{0}; }};
    });
    bad("nbGetJyokyoMes", [](Gen& g) {
        const int32_t mes = g.range(0, 0x60);
        return Pair{[=] { return iface::origVm(0x00259300, {FW_MAIN, sx(mes)}); },
                    [=] { return norm(nb::nbGetJyokyoMes(mainData(), mes)); }};
    });

    // ---- choosing a target (against the original instructions) ----
    // A target selection in progress for the actor: the lists, the cursor,
    // its animation, the pad.
    auto tarsel = [&](const char* name, std::function<Pair(Gen&)> make) {
        add(name, [make](Gen& g) {
            std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);   // the fakes' pool
            auto& t = at<nb::TargetSelectData>(FW_TARSEL);
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
            t.jyokyotime = g.range(0, 3);
            t.time = g.range(0, 29);
            for (int i = 0; i < 8; ++i)   // the pad: nothing, a fresh press, a repeat
                at<uint8_t>(0x002f5830 + static_cast<uint32_t>(i)) = static_cast<uint8_t>(g.pick<int32_t>({0, 0, 0, 0x80, 2, 0x82}));
            dat::globalWork().config = static_cast<uint32_t>(g.rng());
            mainData().stat = g.chance(30) ? (mainData().stat ^ 8u) : mainData().stat;
            mainData().stat = g.chance(10) ? (mainData().stat | 0x200000u) : (mainData().stat & ~0x200000u);
            act().stat = g.chance(20) ? (act().stat | 0x80u) : (act().stat & ~0x80u);
            if (g.chance(10))
                at<nb::TargetSelectData>(FW_TARSEL).act.address = 0;
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
    auto tVoid = [](uint32_t entry, void (*rewrite)(nb::TargetSelectData&)) {
        return Pair{[=] { return iface::origVmVoid(entry, {FW_TARSEL}); }, [=] { rewrite(at<nb::TargetSelectData>(FW_TARSEL)); return uint64_t{0}; }};
    };
    tarsel("nbGetTarSelStat", [](Gen&) { return Pair{[] { return iface::origVm(0x0025d6b8, {}); }, [] { return norm(nb::nbGetTarSelStat()); }}; });
    tarsel("nbSetTarSelStat", [](Gen& g) {
        const int32_t s = g.range(0, 300);
        return Pair{[=] { return iface::origVmVoid(0x0025d6d8, {sx(s)}); }, [=] { nb::nbSetTarSelStat(s); return uint64_t{0}; }};
    });
    tarsel("nbSetTarSelJyokyoTime", [](Gen& g) {
        const int32_t s = g.range(-2, 30);
        return Pair{[=] { return iface::origVmVoid(0x0025d700, {sx(s)}); }, [=] { nb::nbSetTarSelJyokyoTime(s); return uint64_t{0}; }};
    });
    tarsel("AnimeTargetCursor", [=](Gen&) { return tVoid(0x0025d728, nb::AnimeTargetCursor); });
    tarsel("SetCursor", [=](Gen&) { return tVoid(0x0025de40, nb::SetCursor); });
    tarsel("UpdateSelect", [=](Gen&) { return tVoid(0x0025e100, nb::UpdateSelect); });
    tarsel("OnOffTargetCursor", [=](Gen&) { return tVoid(0x0025e278, nb::OnOffTargetCursor); });
    tarsel("DispTargetHelp", [=](Gen&) { return tVoid(0x0025e300, nb::DispTargetHelp); });
    tarsel("MemoryCommand", [=](Gen&) { return tVoid(0x0025e3f8, nb::MemoryCommand); });
    tarsel("CursorSelect", [=](Gen&) { return tVoid(0x0025e448, nb::CursorSelect); });
    tarsel("CursorSelectAuto", [=](Gen&) { return tVoid(0x0025e6e0, nb::CursorSelectAuto); });
    tarsel("CheckFriend", [](Gen& g) {
        const int32_t f = g.range(-1, 16);
        return Pair{[=] { return iface::origVm(0x0025e070, {FW_TARSEL, sx(f)}); },
                    [=] { return norm(nb::CheckFriend(at<nb::TargetSelectData>(FW_TARSEL), f) ? 1 : 0); }};
    });
    tarsel("CheckEnemy", [](Gen& g) {
        const int32_t f = g.range(-1, 16);
        return Pair{[=] { return iface::origVm(0x0025e0b8, {FW_TARSEL, sx(f)}); },
                    [=] { return norm(nb::CheckEnemy(at<nb::TargetSelectData>(FW_TARSEL), f) ? 1 : 0); }};
    });
    tarsel("nbSetTargetProcess", [](Gen& g) {
        const int32_t ctype = g.range(0, 2), crule = g.range(0, 4), carea = g.range(0, 3);
        const int32_t pi = act().partyindex;
        return Pair{[=] { return iface::origVm(0x0025dfa0, {kAct, sx(pi), sx(ctype), sx(crule), sx(carea)}); },
                    [=] { return norm(nb::nbSetTargetProcess(act(), pi, ctype, crule, carea) ? 1 : 0); }};
    });
    tarsel("nbTarSelProcess1", [](Gen&) {
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(0x005442b8, 0x3f9, 1, 1, 0, 0, FW_TARSEL));
        return Pair{[=] { return iface::origVm(0x0025e720, {process}); }, [=] { return norm(nb::nbTarSelProcess1(process)); }};
    });
    tarsel("nbTarSelShutdown", [](Gen&) {
        const uint32_t data = ps2PoolAllocate(0x44);
        at<nb::TargetSelectData>(data).data.address = FW_MAIN;
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(0x005442b8, 0x3f9, 1, 1, 0, 0, data));
        return Pair{[=] { return iface::origVmVoid(0x0025e7d8, {process}); }, [=] { nb::nbTarSelShutdown(process); return uint64_t{0}; }};
    });
    tarsel("InitTarSelProcessData", [](Gen&) {
        return Pair{[] { return iface::origVm(0x0025e800, {FW_MAIN}); },
                    [] { return norm(static_cast<int32_t>(nb::InitTarSelProcessData(mainData()))); }};
    });
    tarsel("nbInitTarSelProcess", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x0025e870, {FW_MAIN}); }, [] { nb::nbInitTarSelProcess(mainData()); return uint64_t{0}; }};
    });
    tarsel("nbPlaySe", [](Gen& g) {
        const int32_t se = g.range(0, 40);
        return Pair{[=] { return iface::origVmVoid(0x0028d090, {sx(se)}); }, [=] { nb::nbPlaySe(se); return uint64_t{0}; }};
    });
    tarsel("dds3CheckConfigBit", [](Gen& g) {
        const int32_t type = g.range(-1, 6);
        return Pair{[=] { return iface::origVm(0x0029bae0, {sx(type)}); }, [=] { return norm(nb::dds3CheckConfigBit(type)); }};
    });
    tarsel("SetTarget", [](Gen& g) {
        act().work->nowcommand = static_cast<int16_t>(g.pick<int32_t>({0, 1, 1, 6, 5, 3}));
        if (g.chance(30))
            act().work->nowindex = 0xdf;
        return Pair{[] { return iface::origVmVoid(0x00251428, {kAct}); }, [] { nb::SetTarget(act()); return uint64_t{0}; }};
    });
    tarsel("SetAction_TARSEL", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x00254178, {kAct}); }, [] { nb::SetAction_TARSEL(act()); return uint64_t{0}; }};
    });

    // ---- whether a skill would do anything ----
    // Targets hurt or not, ailing or not, buffs near their limits; the
    // skills each check knows about.
    static const int32_t kErrorSkills[] = {0x24, 0x27, 0x29, 0x51, 0x5e, 0x2a, 0x52, 0x5d, 0x2b, 0x2e, 0x30, 0x58, 0x31, 0x32,
                                           0x33, 0x55, 0xed, 0xf8, 0x44, 0x46, 0xe0, 0xda, 0x34, 0x36, 0x40, 0x43, 0xcb,
                                           0xce, 0x109, 0x114, 0x49, 0x4a, 0x4b, 0x4c, 0x50, 0x10, 0x60, 0x100};
    auto skillWorld = [](Gen& g) {
        auto unitAt = [](uint32_t address) -> UnitWork& { return at<UnitWork>(address); };
        for (int f = 0; f < 16; ++f) {
            if (!formUnit(f))
                continue;
            UnitWork& u = unitAt(formUnit(f));
            u.maxhp = static_cast<uint16_t>(g.range(1, 500));
            u.hp = g.chance(50) ? u.maxhp : static_cast<uint16_t>(g.range(0, u.maxhp));
            u.maxmp = static_cast<uint16_t>(g.range(1, 300));
            u.mp = g.chance(50) ? u.maxmp : static_cast<uint16_t>(g.range(0, u.maxmp));
            u.badstat = static_cast<uint16_t>(g.chance(60) ? 0 : 1u << g.range(0, 11));
        }
        for (int k = 0; k < 14; ++k)
            for (int c = 4; c < 16; ++c)
                party(k).count[c] = static_cast<int16_t>(g.chance(50) ? g.pick<int32_t>({4, -4, 1, -1}) : g.range(-4, 4));
        GlobalWork& global = dat::globalWork();
        for (int i = 0; i < 16; ++i) {
            UnitWork& u = global.units[i];
            u.flag = g.chance(70) ? (u.flag | 1u) : (u.flag & ~1u);
            u.maxhp = static_cast<uint16_t>(g.range(1, 500));
            u.hp = g.chance(50) ? u.maxhp : static_cast<uint16_t>(g.range(0, u.maxhp));
            u.maxmp = static_cast<uint16_t>(g.range(1, 300));
            u.mp = g.chance(50) ? u.maxmp : static_cast<uint16_t>(g.range(0, u.maxmp));
            u.badstat = static_cast<uint16_t>(g.chance(60) ? 0 : g.chance(40) ? 0x800 : 1u << g.range(0, 11));
        }
        global.fieldskills = static_cast<uint32_t>(g.below(16));
        if (g.chance(10))
            mainData().stat |= 0x08000000;
        else
            mainData().stat &= ~0x08000000u;
    };
    auto pickSkill = [](Gen& g) { return g.chance(85) ? g.pick(kErrorSkills) : g.range(0, 0x11f); };
    auto select = [](Gen& g) {
        if (g.chance(40))
            return 1u << g.below(16);   // a single target
        return static_cast<uint32_t>(g.rng()) & 0xffffu;
    };
    add("CheckDeadUnit", [=](Gen& g) {
        skillWorld(g);
        return Pair{[] { return iface::origVm(0x00290048, {}); }, [] { return norm(nb::CheckDeadUnit() ? 1 : 0); }};
    });
    add("nbDispSkillErrorMessage", [=](Gen& g) {
        const int32_t err = g.range(-1, 5);
        return Pair{[=] { return iface::origVmVoid(0x00290490, {sx(err)}); }, [=] { nb::nbDispSkillErrorMessage(err); return uint64_t{0}; }};
    });
    add("nbCheckBattleSkillError1", [=](Gen& g) {
        skillWorld(g);
        const int32_t s = pickSkill(g);
        return Pair{[=] { return iface::origVm(0x00290520, {sx(s)}); }, [=] { return norm(nb::nbCheckBattleSkillError1(s)); }};
    });
    add("nbCheckBattleSkillError2", [=](Gen& g) {
        skillWorld(g);
        const int32_t s = pickSkill(g);
        const uint32_t sel = select(g);
        return Pair{[=] { return iface::origVm(0x00290568, {sx(s), sel}); }, [=] { return norm(nb::nbCheckBattleSkillError2(s, sel)); }};
    });
    add("nbCheckBattleSkillError3", [=](Gen& g) {
        skillWorld(g);
        const int32_t s = pickSkill(g);
        const uint32_t sel = select(g);
        return Pair{[=] { return iface::origVm(0x00290780, {sx(s), sel}); }, [=] { return norm(nb::nbCheckBattleSkillError3(s, sel)); }};
    });
    add("nbCheckCampSkillError", [=](Gen& g) {
        skillWorld(g);
        const int32_t s = pickSkill(g);
        const uint32_t sel = select(g);
        return Pair{[=] { return iface::origVm(0x00290908, {sx(s), sel}); }, [=] { return norm(nb::nbCheckCampSkillError(s, sel)); }};
    });

    add("SetAction_AI", [](Gen&) {
        return Pair{[] { return iface::origVmVoid(0x00253bf8, {kAct}); }, [] { nb::SetAction_AI(act()); return uint64_t{0}; }};
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
        {"nbCommand_AI", nbCommand_AI, nb::ai::script::runTableAi},
        {"nbCommand_BTL_AI_ROT_CLR", nbCommand_BTL_AI_ROT_CLR, nb::ai::script::rotationClear},
        {"nbCommand_BTL_AI_ROT_NEXT", nbCommand_BTL_AI_ROT_NEXT, nb::ai::script::rotationNext},
        {"nbCommand_BTL_AI_ROT_GET", nbCommand_BTL_AI_ROT_GET, nb::ai::script::rotationGet},
        {"nbCommand_BTL_PNL_ON", nbCommand_BTL_PNL_ON, nb::ai::script::panelOn},
        {"nbCommand_BTL_CAM_ORG", nbCommand_BTL_CAM_ORG, nb::ai::script::cameraOrigin},
    };
    for (const Command& c : kCommands)
        add(c.name, [c](Gen&) { return Pair{[c] { return norm(c.legacy()); }, [c] { return norm(c.rewrite()); }}; });
}

} // namespace difftest
