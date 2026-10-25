// Differential tests for the devil stock, skill inheritance and growth
// (rewrite: src/fusion; legacy: the cmb/rst units).
#include <cstdint>
#include <cstring>

#include "harness.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/fusion/accident.hpp"
#include "nocturne/fusion/growth.hpp"
#include "nocturne/fusion/inheritance.hpp"
#include "nocturne/fusion/sort.hpp"
#include "nocturne/fusion/stock.hpp"

// Legacy prototypes (the legacy headers use C-only constructs).
extern "C" {
void ps2ClearUnitWork(datUnitWork_PS2* unit);
void cmbCopyDefaultDevilToStock(uint16_t devil_id, datUnitWork_PS2* unit);
void cmbCopyCustomDevilToStock(datUnitWork_PS2* destination, const datUnitWork_PS2* source);
int8_t cmbChkStockDevil(uint16_t devil_id, const datUnitWork_PS2* units, uint8_t count);
int8_t cmbChkStockDevilNums(const datUnitWork_PS2* units, uint8_t count);
int8_t cmbGetEmptyStockIndex(const datUnitWork_PS2* units, uint8_t count);
int8_t cmbGetStockDevilIndex(uint16_t devil_id, const datUnitWork_PS2* units, uint8_t count);
void cmbDeleteUnitFromStockList(int8_t unit_index);
void cmbAddUnitToStockList(int8_t unit_index);
int8_t cmbDeleteDevilFromStock(uint16_t devil_id, datUnitWork_PS2* units, uint8_t count);
int8_t cmbAddDefaultDevilToStock(uint16_t devil_id, datUnitWork_PS2* units, uint8_t count);
int8_t cmbAddCustomDevilToStock(const datUnitWork_PS2* source, datUnitWork_PS2* units, uint8_t count);
int8_t cmbChkDarkDevil(uint16_t devil_id);
int8_t cmbChkStockDarkDevilNums(const datUnitWork_PS2* units, uint8_t count);
int8_t cmbChkIkenieIllegalDevil(uint16_t devil_id);
uint8_t cmbGetKeisyoSkillScore(int16_t skill_attribute, int16_t inheritance_type);
uint8_t cmbGetKeisyoSkillMotion(uint16_t skill_form, uint16_t devil_form);
uint8_t cmbGetKeisyoSkillLevel(uint16_t skill_id);
uint8_t cmbCalcKeisyoSkillRate(const datUnitWork_PS2* unit, uint16_t skill_id);
int32_t cmbCalcTotalKeisyoSkillRate(const datUnitWork_PS2* unit);
int8_t cmbGetKeisyoSkillEndIndex(const datUnitWork_PS2* unit);
void cmbClearKeisyoSkill(datUnitWork_PS2* unit);
int8_t cmbChkKeisyoSkillOwner(uint16_t skill, const datUnitWork_PS2* unit);
int8_t cmbChkKeisyoSkillNums(const datUnitWork_PS2* unit);
void cmbClearSkill(datUnitWork_PS2* unit);
void cmbCreateDefaultSkill(uint16_t devil_id, datUnitWork_PS2* unit);
void ps2CreateLevelSkill(uint16_t devil_id, uint8_t level, datUnitWork_PS2* unit);
int8_t cmbChkSkillOwner(uint16_t skill, datUnitWork_PS2* unit);
int8_t cmbAddSkill(uint16_t skill, datUnitWork_PS2* unit);
const void* cmbChkLevelUpEvent(const datUnitWork_PS2* unit, int8_t* event_count);
uint32_t cmpCalcLevelUpBaseExp(int32_t level);
uint32_t cmbCalcLevelUpExp(const datUnitWork_PS2* unit, int32_t level);
uint32_t cmbChkLevelUpExp(const datUnitWork_PS2* unit);
int32_t cmbGetLevelUpCount(const datUnitWork_PS2* unit, int32_t added_exp);
int32_t cmbGetParam(datUnitWork_PS2* unit, int32_t index);
int8_t cmbAddLevelUpParamEx(datUnitWork_PS2* unit, int8_t mode);
int8_t ps2AddLevelUpParam(datUnitWork_PS2* unit);
int8_t cmbChkEvoAttention(const datUnitWork_PS2* unit);
int8_t cmbChkCancelEvo(const datUnitWork_PS2* unit);
int8_t cmbChkDevilEvo(const datUnitWork_PS2* unit);
int8_t cmbGetDevilEvoLevel(const datUnitWork_PS2* unit);
int8_t cmbChkEvoNeedFlag(uint16_t devil_id);
int32_t cmbChkEvoDevilLev(const datUnitWork_PS2* player, const datUnitWork_PS2* stock, const datUnitWork_PS2* evolved, int32_t event_level);
void cmbCopyEvoDevilToStock(datUnitWork_PS2* unit, const datUnitWork_PS2* evolved_unit);
uint16_t cmbGetPowerUpSkill(uint16_t skill);
uint16_t rstRndGetPowerUpSkill(const datUnitWork_PS2* unit, int8_t* index);
uint16_t cmbGetMutationSkill(uint16_t skill, datUnitWork_PS2* unit);
void ps2FusionSortSkills_00213350(uint64_t unit);
void ps2FusionSortDescriptors_002133A0(uint64_t output, uint64_t count);
uint64_t ps2FusionAccidentEventDisabled_001FD3B0(uint64_t id);
uint64_t ps2FusionAccidentMetaOnly_001FE2C8(uint64_t id);
uint64_t ps2FusionAccidentCheck_001FE2F0(void);
uint64_t ps2FusionAccidentType_001FE368(void);
uint64_t ps2FusionAccidentFallback_001FE388(uint64_t excluded_id);
uint64_t ps2FusionAccidentSelect_001FE410(uint64_t excluded_id);
uint64_t ps2FusionAccidentBoost_001FE570(uint64_t unit);
}

namespace difftest {
namespace {

constexpr uint32_t kStock = FW_GLOBAL + static_cast<uint32_t>(offsetof(nocturne::GlobalWork, units));   // GlobalWork::units[16]
constexpr uint32_t kScratch = FW_ENEMIES;        // a spare unit in dynamic RAM
constexpr uint16_t kDevilCount = 384;

uint32_t stockUnit(int i) { return kStock + 0xec * static_cast<uint32_t>(i); }

} // namespace

// Devils with growth events of interest (evolution, notices) turn up often.
uint16_t randomDevil(Gen& g)
{
    static std::vector<uint16_t> evolving;
    if (evolving.empty()) {
        for (uint16_t d = 0; d < kDevilCount; ++d)
            for (const GrowthEvent& e : dat::devilGrowth(d).event)
                if (e.type == GrowthEventType::Evolve || e.type == GrowthEventType::EvolveNotice) {
                    evolving.push_back(d);
                    break;
                }
    }
    if (g.chance(10)) return 0;
    if (g.chance(30)) return evolving[g.below(static_cast<uint32_t>(evolving.size()))];
    if (g.chance(15)) return dat::kDarkDevil[g.below(37)];
    return static_cast<uint16_t>(g.below(kDevilCount));
}

namespace {

// Skills from the inheritance and power-up tables, and anything else.
uint16_t randomSkill(Gen& g)
{
    switch (g.below(4)) {
    case 0: return dat::kInheritanceLevel[g.below(227)].skillId();
    case 1: return dat::kSkillPowerUp[g.below(55)].skill;
    case 2: return 0;
    default: return static_cast<uint16_t>(g.below(0x200));
    }
}

void randomStockUnit(Gen& g, UnitWork& u)
{
    randomUnit(g, u, false);
    static const uint32_t kFlags[] = {0, 0, 1, 1, 1, 3, 5, 0x201, 0x41, 2};
    u.flag = g.pick(kFlags);
    u.id = randomDevil(g);
    u.exp = g.chance(10) ? g.range(-5, 0) : g.range(0, 2000000);
    u.uniqueid = static_cast<uint16_t>(g.below(0x10000));
    for (int8_t& p : u.levelupparam) p = static_cast<int8_t>(g.range(0, 20));
    u.skillcnt = static_cast<uint16_t>(g.range(0, 8));
    for (int i = 0; i < 24; ++i)
        u.skill[i] = i < u.skillcnt || g.chance(10) ? randomSkill(g) : 0;
    int inherited = g.range(0, 24);
    for (int i = 0; i < 24; ++i)
        u.inheritedSkills[i] = i < inherited ? randomSkill(g) : (g.chance(5) ? randomSkill(g) : 0);
    u.preEvolutionId = g.chance(20) ? randomDevil(g) : 0;
    u.preEvolutionExp = g.chance(20) ? g.below(100000) : 0;
}

} // namespace

void randomStock(Gen& g)
{
    GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
    for (int i = 0; i < 16; ++i)
        randomStockUnit(g, global.units[i]);
    if (g.chance(80)) {
        global.units[0].id = 0;   // the Demi-fiend
        global.units[0].flag = 7;
    }
    global.stock_count = g.range(0, 15);
    for (uint8_t& slot : global.stock_list)
        slot = static_cast<uint8_t>(g.chance(5) ? g.below(256) : g.below(16));
    global.hearts_equipped = static_cast<uint8_t>(g.below(26));
    global.hearts_owned_count = static_cast<uint8_t>(g.chance(80) ? g.range(1, 25) : 0);
    global.stock_capacity = g.chance(5) ? g.range(-1, 0) : g.range(1, 12);
    for (int i = 1; i < 4; ++i)
        global.reason_points[i] = static_cast<uint8_t>(g.chance(30) ? 64 : g.range(0, 128));
    global.macca = g.chance(5) ? g.range(-5, 0) : g.range(0, 9999999);
    randomStockUnit(g, unitAt(kScratch));
}

namespace {

uint8_t randomCount(Gen& g) { return static_cast<uint8_t>(g.chance(70) ? 16 : g.range(0, 16)); }

} // namespace

void addFusionTests(std::vector<TestCase>& t)
{
    // A case whose world includes a random stock.
    auto add = [&t](const char* name, std::function<Pair(Gen&)> make) {
        t.push_back({name, [make](Gen& g) { randomStock(g); return make(g); }});
    };
    auto L = legacyUnit;

    // ---- stock -----------------------------------------------------------------
    add("ps2ClearUnitWork", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        return Pair{[=] { ps2ClearUnitWork(L(u)); return uint64_t{0}; }, [=] { cmb::clearUnit(unitAt(u)); return uint64_t{0}; }};
    });
    add("cmbCopyDefaultDevilToStock", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        uint16_t devil = randomDevil(g);
        return Pair{[=] { cmbCopyDefaultDevilToStock(devil, L(u)); return uint64_t{0}; },
                    [=] { cmb::copyDefaultDevil(devil, unitAt(u)); return uint64_t{0}; }};
    });
    add("cmbCopyCustomDevilToStock", [L](Gen& g) {
        uint32_t d = stockUnit(g.range(0, 15)), s = g.chance(20) ? kScratch : stockUnit(g.range(0, 15));
        return Pair{[=] { cmbCopyCustomDevilToStock(L(d), L(s)); return uint64_t{0}; },
                    [=] { cmb::copyCustomDevil(unitAt(d), unitAt(s)); return uint64_t{0}; }};
    });
    auto search = [&add, L](const char* name, int8_t (*legacy)(uint16_t, const datUnitWork_PS2*, uint8_t),
                            int8_t (*rewrite)(uint16_t, const UnitWork*, uint8_t)) {
        add(name, [=](Gen& g) {
            uint16_t devil = g.chance(50) ? unitAt(stockUnit(g.range(0, 15))).id : randomDevil(g);
            uint8_t count = randomCount(g);
            return Pair{[=] { return norm(int32_t{legacy(devil, L(kStock), count)}); },
                        [=] { return norm(int32_t{rewrite(devil, &unitAt(kStock), count)}); }};
        });
    };
    search("cmbChkStockDevil", cmbChkStockDevil, cmb::findStockDevil);
    search("cmbGetStockDevilIndex", cmbGetStockDevilIndex, cmb::findStockDevilAnyFlag);
    auto count = [&add, L](const char* name, int8_t (*legacy)(const datUnitWork_PS2*, uint8_t),
                           int8_t (*rewrite)(const UnitWork*, uint8_t)) {
        add(name, [=](Gen& g) {
            uint8_t n = randomCount(g);
            return Pair{[=] { return norm(int32_t{legacy(L(kStock), n)}); }, [=] { return norm(int32_t{rewrite(&unitAt(kStock), n)}); }};
        });
    };
    count("cmbChkStockDevilNums", cmbChkStockDevilNums, cmb::countStockDevils);
    count("cmbGetEmptyStockIndex", cmbGetEmptyStockIndex, cmb::findEmptyStockSlot);
    count("cmbChkStockDarkDevilNums", cmbChkStockDarkDevilNums, cmb::countDarkDevils);
    add("cmbDeleteUnitFromStockList", [](Gen& g) {
        int8_t index = static_cast<int8_t>(g.chance(10) ? g.range(-128, 127) : g.range(0, 15));
        return Pair{[=] { cmbDeleteUnitFromStockList(index); return uint64_t{0}; },
                    [=] { cmb::removeFromStockList(index); return uint64_t{0}; }};
    });
    add("cmbAddUnitToStockList", [](Gen& g) {
        int8_t index = static_cast<int8_t>(g.range(-2, 15));
        return Pair{[=] { cmbAddUnitToStockList(index); return uint64_t{0}; },
                    [=] { cmb::appendToStockList(index); return uint64_t{0}; }};
    });
    add("cmbDeleteDevilFromStock", [L](Gen& g) {
        uint16_t devil = g.chance(60) ? unitAt(stockUnit(g.range(0, 15))).id : randomDevil(g);
        uint8_t n = randomCount(g);
        return Pair{[=] { return norm(int32_t{cmbDeleteDevilFromStock(devil, L(kStock), n)}); },
                    [=] { return norm(int32_t{cmb::deleteDevil(devil, &unitAt(kStock), n)}); }};
    });
    add("cmbAddDefaultDevilToStock", [L](Gen& g) {
        uint16_t devil = randomDevil(g);
        uint8_t n = randomCount(g);
        return Pair{[=] { return norm(int32_t{cmbAddDefaultDevilToStock(devil, L(kStock), n)}); },
                    [=] { return norm(int32_t{cmb::addDefaultDevil(devil, &unitAt(kStock), n)}); }};
    });
    add("cmbAddCustomDevilToStock", [L](Gen& g) {
        uint8_t n = randomCount(g);
        return Pair{[=] { return norm(int32_t{cmbAddCustomDevilToStock(L(kScratch), L(kStock), n)}); },
                    [=] { return norm(int32_t{cmb::addCustomDevil(unitAt(kScratch), &unitAt(kStock), n)}); }};
    });
    auto devilQuery = [&add](const char* name, int8_t (*legacy)(uint16_t), bool (*rewrite)(uint16_t)) {
        add(name, [=](Gen& g) {
            uint16_t devil = g.chance(10) ? static_cast<uint16_t>(g.below(0x10000)) : randomDevil(g);
            return Pair{[=] { return norm(int32_t{legacy(devil)}); }, [=] { return norm(rewrite(devil)); }};
        });
    };
    devilQuery("cmbChkDarkDevil", cmbChkDarkDevil, cmb::isDarkDevil);
    devilQuery("cmbChkIkenieIllegalDevil", cmbChkIkenieIllegalDevil, cmb::cannotBeSacrificed);
    devilQuery("cmbChkEvoNeedFlag", cmbChkEvoNeedFlag, cmb::evolutionNeedsEvent);

    // ---- inheritance ----------------------------------------------------------
    add("cmbGetKeisyoSkillScore", [](Gen& g) {
        int16_t attr = static_cast<int16_t>(g.range(-3, 20)), type = static_cast<int16_t>(g.range(-3, 15));
        return Pair{[=] { return uint64_t{cmbGetKeisyoSkillScore(attr, type)}; }, [=] { return uint64_t{cmb::inheritScore(attr, type)}; }};
    });
    add("cmbGetKeisyoSkillMotion", [](Gen& g) {
        uint16_t a = static_cast<uint16_t>(g.below(0x10000)), b = static_cast<uint16_t>(g.below(0x10000));
        if (g.chance(50)) { a &= 0x1f; b = static_cast<uint16_t>(1u << g.below(6)); }
        return Pair{[=] { return uint64_t{cmbGetKeisyoSkillMotion(a, b)}; }, [=] { return uint64_t{cmb::inheritFormMatch(a, b)}; }};
    });
    add("cmbGetKeisyoSkillLevel", [](Gen& g) {
        uint16_t s = randomSkill(g);
        return Pair{[=] { return uint64_t{cmbGetKeisyoSkillLevel(s)}; }, [=] { return uint64_t{cmb::inheritLevel(s)}; }};
    });
    add("cmbCalcKeisyoSkillRate", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        uint16_t s = randomSkill(g);
        return Pair{[=] { return uint64_t{cmbCalcKeisyoSkillRate(L(u), s)}; }, [=] { return uint64_t{cmb::inheritRate(unitAt(u), s)}; }};
    });
    auto unitQuery = [&add, L](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            uint32_t u = g.chance(10) ? kScratch : stockUnit(g.range(0, 15));
            return Pair{[=] { return legacy(L(u)); }, [=] { return rewrite(unitAt(u)); }};
        });
    };
    unitQuery("cmbCalcTotalKeisyoSkillRate", [](datUnitWork_PS2* u) { return norm(cmbCalcTotalKeisyoSkillRate(u)); },
              [](UnitWork& u) { return norm(cmb::totalInheritRate(u)); });
    unitQuery("cmbGetKeisyoSkillEndIndex", [](datUnitWork_PS2* u) { return norm(int32_t{cmbGetKeisyoSkillEndIndex(u)}); },
              [](UnitWork& u) { return norm(int32_t{cmb::inheritedEnd(u)}); });
    unitQuery("cmbClearKeisyoSkill", [](datUnitWork_PS2* u) { cmbClearKeisyoSkill(u); return uint64_t{0}; },
              [](UnitWork& u) { cmb::clearInherited(u); return uint64_t{0}; });
    unitQuery("cmbChkKeisyoSkillNums", [](datUnitWork_PS2* u) { return norm(int32_t{cmbChkKeisyoSkillNums(u)}); },
              [](UnitWork& u) { return norm(int32_t{cmb::countInherited(u)}); });
    add("cmbChkKeisyoSkillOwner", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        uint16_t s = g.chance(50) ? unitAt(u).inheritedSkills[g.below(24)] : randomSkill(g);
        return Pair{[=] { return norm(int32_t{cmbChkKeisyoSkillOwner(s, L(u))}); }, [=] { return norm(int32_t{cmb::findInherited(s, unitAt(u))}); }};
    });

    // ---- skills -----------------------------------------------------------------
    unitQuery("cmbClearSkill", [](datUnitWork_PS2* u) { cmbClearSkill(u); return uint64_t{0}; },
              [](UnitWork& u) { cmb::clearSkills(u); return uint64_t{0}; });
    add("cmbCreateDefaultSkill", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        uint16_t devil = randomDevil(g);
        return Pair{[=] { cmbCreateDefaultSkill(devil, L(u)); return uint64_t{0}; },
                    [=] { cmb::createDefaultSkills(devil, unitAt(u)); return uint64_t{0}; }};
    });
    add("ps2CreateLevelSkill", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        uint16_t devil = randomDevil(g);
        uint8_t level = static_cast<uint8_t>(g.below(256));
        return Pair{[=] { ps2CreateLevelSkill(devil, level, L(u)); return uint64_t{0}; },
                    [=] { cmb::createLevelSkills(devil, level, unitAt(u)); return uint64_t{0}; }};
    });
    auto skillOnUnit = [&add, L](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            uint32_t u = stockUnit(g.range(0, 15));
            uint16_t s = g.chance(40) ? unitAt(u).skill[g.below(24)] : randomSkill(g);
            return Pair{[=] { return norm(int32_t{legacy(s, L(u))}); }, [=] { return norm(int32_t{rewrite(s, unitAt(u))}); }};
        });
    };
    skillOnUnit("cmbChkSkillOwner", cmbChkSkillOwner, cmb::findSkill);
    skillOnUnit("cmbAddSkill", cmbAddSkill, cmb::addSkill);
    add("cmbChkLevelUpEvent", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        bool withCount = g.chance(80);
        auto pack = [](const void* event, int8_t n) {
            return (uint64_t{event ? fw_address_of(event) : 0u} << 8) | static_cast<uint8_t>(n);
        };
        return Pair{[=] { int8_t n = 0x55; const void* e = cmbChkLevelUpEvent(L(u), withCount ? &n : nullptr); return pack(e, n); },
                    [=] { int8_t n = 0x55; const void* e = cmb::levelUpEvents(unitAt(u), withCount ? &n : nullptr); return pack(e, n); }};
    });

    // ---- EXP ----------------------------------------------------------------------
    add("cmpCalcLevelUpBaseExp", [](Gen& g) {
        int32_t level = g.chance(90) ? g.range(0, 256) : static_cast<int32_t>(g.rng());
        return Pair{[=] { return uint64_t{cmpCalcLevelUpBaseExp(level)}; }, [=] { return uint64_t{cmb::baseExpForLevel(level)}; }};
    });
    add("cmbCalcLevelUpExp", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        int32_t level = g.range(0, 256);
        return Pair{[=] { return uint64_t{cmbCalcLevelUpExp(L(u), level)}; }, [=] { return uint64_t{cmb::expForLevel(unitAt(u), level)}; }};
    });
    unitQuery("cmbChkLevelUpExp", [](datUnitWork_PS2* u) { return uint64_t{cmbChkLevelUpExp(u)}; },
              [](UnitWork& u) { return uint64_t{cmb::expForNextLevel(u)}; });
    add("cmbGetLevelUpCount", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        int32_t added = g.chance(10) ? static_cast<int32_t>(g.rng()) : g.range(0, 500000);
        return Pair{[=] { return norm(cmbGetLevelUpCount(L(u), added)); }, [=] { return norm(cmb::levelUpCount(unitAt(u), added)); }};
    });

    // ---- level-up stats ---------------------------------------------------------
    add("cmbGetParam", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        int32_t stat = g.range(0, 5);
        return Pair{[=] { return norm(cmbGetParam(L(u), stat)); }, [=] { return norm(cmb::growthParam(unitAt(u), stat)); }};
    });
    add("cmbAddLevelUpParamEx", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        if (g.chance(25)) unitAt(u).id = 0;
        if (g.chance(20)) unitAt(u).param[g.below(6)] = 40;
        int8_t mode = static_cast<int8_t>(g.range(0, 2));
        return Pair{[=] { return norm(int32_t{cmbAddLevelUpParamEx(L(u), mode)}); },
                    [=] { return norm(int32_t{cmb::rollLevelUpStat(unitAt(u), mode)}); }};
    });
    unitQuery("ps2AddLevelUpParam", [](datUnitWork_PS2* u) { return norm(int32_t{ps2AddLevelUpParam(u)}); },
              [](UnitWork& u) { return norm(int32_t{cmb::addLevelUpStat(u)}); });

    // ---- evolution --------------------------------------------------------------
    unitQuery("cmbChkEvoAttention", [](datUnitWork_PS2* u) { return norm(int32_t{cmbChkEvoAttention(u)}); },
              [](UnitWork& u) { return norm(int32_t{cmb::evolutionNotice(u)}); });
    unitQuery("cmbChkCancelEvo", [](datUnitWork_PS2* u) { return norm(int32_t{cmbChkCancelEvo(u)}); },
              [](UnitWork& u) { return norm(int32_t{cmb::evolutionPassed(u)}); });
    unitQuery("cmbChkDevilEvo", [](datUnitWork_PS2* u) { return norm(int32_t{cmbChkDevilEvo(u)}); },
              [](UnitWork& u) { return norm(int32_t{cmb::evolvedSpeciesLevel(u)}); });
    unitQuery("cmbGetDevilEvoLevel", [](datUnitWork_PS2* u) { return norm(int32_t{cmbGetDevilEvoLevel(u)}); },
              [](UnitWork& u) { return norm(int32_t{cmb::evolutionLevel(u)}); });
    add("cmbChkEvoDevilLev", [L](Gen& g) {
        uint32_t p = stockUnit(0), s = stockUnit(g.range(1, 15)), e = kScratch;
        int32_t eventLevel = g.chance(30) ? -1 : g.range(0, 120);
        return Pair{[=] { return norm(cmbChkEvoDevilLev(L(p), L(s), L(e), eventLevel)); },
                    [=] { return norm(cmb::evolutionLevelLimit(unitAt(p), unitAt(s), unitAt(e), eventLevel)); }};
    });
    add("cmbCopyEvoDevilToStock", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        if (g.chance(70)) cmb::copyDefaultDevil(randomDevil(g), unitAt(kScratch));
        return Pair{[=] { cmbCopyEvoDevilToStock(L(u), L(kScratch)); return uint64_t{0}; },
                    [=] { cmb::copyEvolvedDevil(unitAt(u), unitAt(kScratch)); return uint64_t{0}; }};
    });

    // ---- power-ups and mutation --------------------------------------------------
    add("cmbGetPowerUpSkill", [](Gen& g) {
        uint16_t s = randomSkill(g);
        return Pair{[=] { return uint64_t{cmbGetPowerUpSkill(s)}; }, [=] { return uint64_t{cmb::powerUpSkill(s)}; }};
    });
    add("rstRndGetPowerUpSkill", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        bool withSlot = g.chance(80);
        return Pair{[=] { int8_t slot = 0x55; uint16_t s = rstRndGetPowerUpSkill(L(u), withSlot ? &slot : nullptr); return uint64_t{s} << 8 | static_cast<uint8_t>(slot); },
                    [=] { int8_t slot = 0x55; uint16_t s = cmb::randomPowerUpSkill(unitAt(u), withSlot ? &slot : nullptr); return uint64_t{s} << 8 | static_cast<uint8_t>(slot); }};
    });
    add("cmbGetMutationSkill", [L](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        uint16_t s = g.chance(50) ? unitAt(u).skill[g.below(8)] : randomSkill(g);
        return Pair{[=] { return uint64_t{cmbGetMutationSkill(s, L(u))}; }, [=] { return uint64_t{cmb::mutationSkill(s, unitAt(u))}; }};
    });

    // ---- sorting (and the PS2 qsort under it) -----------------------------------
    add("cmbSortKeisyoSkill", [](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        UnitWork& unit = unitAt(u);
        uint16_t pool[4];
        for (uint16_t& p : pool) p = randomSkill(g);
        for (int i = 0; i < 24; ++i) {   // few distinct values, so many ties
            unit.inheritedSkills[i] = g.chance(25) ? 0 : pool[g.below(4)];
            unit.keiattr[i] = static_cast<uint8_t>(g.below(256));
        }
        return Pair{[=] { ps2FusionSortSkills_00213350(u); return uint64_t{0}; },
                    [=] { cmb::sortInheritedSkills(unitAt(u)); return uint64_t{0}; }};
    });
    add("sortDevilsByRace (0x2133A0)", [](Gen& g) {
        uint16_t count = static_cast<uint16_t>(g.chance(50) ? 384 : g.range(0, 384));
        return Pair{[=] { ps2FusionSortDescriptors_002133A0(FW_SCRATCH, count); return uint64_t{0}; },
                    [=] { cmb::sortDevilsByRace(&at<cmb::DevilSortEntry>(FW_SCRATCH), count); return uint64_t{0}; }};
    });

    // ---- accidents ----------------------------------------------------------------
    // Legacy returns the raw flag mask (2) where the rewrite returns a bool.
    devilQuery("cmbChkEventDevil", [](uint16_t d) { return static_cast<int8_t>(ps2FusionAccidentEventDisabled_001FD3B0(d) != 0); }, cmb::isEventLocked);
    devilQuery("cmbChkMetaOnlyDevil", [](uint16_t d) { return static_cast<int8_t>(ps2FusionAccidentMetaOnly_001FE2C8(d) != 0); }, cmb::isSpecialFusionOnly);
    add("cmbChkAccident", [](Gen&) {
        return Pair{[] { return norm(ps2FusionAccidentCheck_001FE2F0()); }, [] { return norm(cmb::rollAccident()); }};
    });
    add("cmbChkAccidentType", [](Gen&) {
        return Pair{[] { return norm(ps2FusionAccidentType_001FE368()); }, [] { return norm(int32_t{cmb::rollAccidentType()}); }};
    });
    auto stockedDevil = [](Gen& g) { return g.chance(50) ? unitAt(stockUnit(g.range(0, 15))).id : randomDevil(g); };
    add("cmbGetAccidentFailDevil", [stockedDevil](Gen& g) {
        GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
        for (int i = 0; i < 16; ++i)   // put fallback devils in the stock
            if (g.chance(50)) { global.units[i].id = dat::kAccidentFailTbl[g.below(14)]; global.units[i].flag |= 1; }
        uint16_t excluded = g.chance(50) ? dat::kAccidentFailTbl[g.below(14)] : stockedDevil(g);
        return Pair{[=] { return norm(ps2FusionAccidentFallback_001FE388(excluded)); }, [=] { return norm(int32_t{cmb::accidentFallbackDevil(excluded)}); }};
    });
    add("cmbRndGetAccidentBirthDevil", [stockedDevil](Gen& g) {
        at<GlobalWork>(FW_GLOBAL).units[0].level = static_cast<uint16_t>(g.range(1, 99));
        uint16_t excluded = stockedDevil(g);
        return Pair{[=] { return norm(ps2FusionAccidentSelect_001FE410(excluded)); }, [=] { return norm(int32_t{cmb::randomAccidentDevil(excluded)}); }};
    });
    add("cmbAddParamAccidentBirthDevil", [](Gen& g) {
        uint32_t u = stockUnit(g.range(0, 15));
        for (int8_t& p : unitAt(u).param) p = static_cast<int8_t>(g.below(256));
        return Pair{[=] { ps2FusionAccidentBoost_001FE570(u); return uint64_t{0}; },
                    [=] { cmb::boostAccidentDevil(unitAt(u)); return uint64_t{0}; }};
    });
}

} // namespace difftest
