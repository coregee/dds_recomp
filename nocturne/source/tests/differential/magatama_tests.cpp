// Differential tests for Magatama and the compendium
// (rewrite: src/data/magatama.cpp, src/facility/compendium.cpp, items in
// progression.cpp; legacy: hearts_*.c, rst_stats.c, fcl_encyc.c,
// compendium_records.c, compendium_restore.c).
#include <cstdint>
#include <cstring>
#include <utility>

#include "harness.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/magatama.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/facility/compendium.hpp"

extern "C" {
int8_t cmbChkGetHearts(int8_t id);
int8_t cmpChkHaveHearts(int8_t id);
int32_t cmpChkHaveNormalHeartsAll(void);
int32_t datAddHearts(int32_t id);
int8_t fclChkItemHearts(uint16_t itemid);
int8_t cmbGetHeartsDefaultParam(int8_t id, int8_t index, int8_t type);
int8_t cmbGetHeartsParamEx(int8_t id, int8_t index, int8_t mode);
int8_t cmbGetHeartsParam(int8_t id, int8_t index);
void ps2HeartsAddParam(uint8_t id, datUnitWork_PS2* unit);
void cmbSubHeartsParam(uint8_t id, datUnitWork_PS2* unit);
int16_t cmbGetHeartsAisyo(uint8_t id);
int32_t cmbGetParamBase(datUnitWork_PS2* unit, int32_t index);
int16_t cmbGetHeartsSkillNums(uint8_t id);
uint16_t ps2HeartsSkillAt(uint8_t id, int8_t index);
int8_t cmbGetHeartsAfterSkillNums(uint8_t id);
void cmbAddHeartsSkill(int8_t id, uint16_t skill);
int8_t cmbCreateDefaultHeartsSkill(uint8_t id, datUnitWork_PS2* unit);
uint16_t cmbChkGetHeartsSkill(uint8_t id, datUnitWork_PS2* unit);
void rstCreateBeforeSkillList(int8_t id, datUnitWork_PS2* unit, int8_t level_offset, void* info);
int8_t cmbChkHeartsMaster(uint8_t id);
int8_t cmbGetMasterHeartsNums(void);
void cmbSetHeartsMaster(int8_t id);
uint8_t cmbChkHeartsStat(int8_t id);
uint8_t cmbChkMasterHeartsStatNums(uint8_t* tier);
uint8_t cmbGetPlayerRaceID(datUnitWork_PS2* unit);
void datAddItem(int32_t id, int32_t num);
int32_t fclAddItem(uint16_t itemid, int32_t num);

void fclEncyc_SetElem(void* elem, datUnitWork_PS2* unit);
int32_t fclEncycGetNum(void);
int32_t fclEncycGetRatio2(void);
uint64_t ps2CompendiumRecords_00216910(uint64_t p0, uint64_t p1);
uint64_t ps2CompendiumRecords_00216A18(uint64_t p0, uint64_t p1);
void ps2CompendiumRecords_00219FC0(uint64_t p0, uint64_t p1);
void ps2CompendiumRecords_00216C08(void);
uint64_t ps2CompendiumRecords_00219400(uint64_t p0);
void ps2CompendiumRecords_00219BA0(uint64_t p0);
void ps2CompendiumRecords_00219BF0(uint64_t p0);
void ps2CompendiumRecords_00219DC0(uint64_t p0, uint64_t p1);
uint64_t ps2CompendiumRecords_00219C40(uint64_t p0, uint64_t p1);
uint64_t ps2CompendiumRecords_00219D00(uint64_t p0, uint64_t p1);
uint64_t ps2CompendiumRestore_00216BF0(void);
uint64_t ps2CompendiumRestore_00219318(uint64_t p0);
void ps2CompendiumRestore_0021A0B8(uint64_t p0, uint64_t p1);
void ps2CompendiumRestore_0021A118(uint64_t p0, uint64_t p1);
uint64_t ps2CompendiumRestore_0021A308(uint64_t p0, uint64_t p1);
uint64_t ps2CompendiumRestore_00216B20(uint64_t p0);
}

namespace difftest {
namespace {

constexpr uint32_t kUnits = FW_GLOBAL + 0xa54;
constexpr uint32_t kRecords = FW_GLOBAL + 0x11e90;
constexpr uint32_t kScratchUnit = FW_ENEMIES;      // a spare unit
constexpr uint32_t kScratchRecord = FW_ENEMIES + 0x100;
constexpr uint32_t kList = FW_SCRATCH;             // byte / int16 lists, skill info

uint32_t unitAddress(int i) { return kUnits + 0xec * static_cast<uint32_t>(i); }
uint32_t recordAddress(int i) { return kRecords + 0xb0 * static_cast<uint32_t>(i); }

void randomMagatama(Gen& g)
{
    GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
    int owned = g.chance(10) ? 25 : g.range(0, 25);
    global.hearts_owned_count = static_cast<uint8_t>(owned);
    bool all = owned == 25 || g.chance(20);
    for (int i = 0; i < owned; ++i)
        global.hearts_owned[i] = static_cast<uint8_t>(all ? i + 1 : g.range(1, 25));
    for (int id = 0; id < 26; ++id) {
        global.hearts_skill_state[id] = static_cast<uint8_t>(g.range(0, 8) | (g.chance(40) ? 0x80 : 0));
        for (uint8_t& up : global.hearts_param_upgrades[id])
            up = static_cast<uint8_t>(g.chance(20) ? g.range(0, 5) : 0);
    }
    if (g.chance(15)) {   // (nearly) everything mastered: the top tiers
        int count = g.range(23, 25);
        global.hearts_owned_count = static_cast<uint8_t>(count);
        for (int i = 0; i < count; ++i) {
            global.hearts_owned[i] = static_cast<uint8_t>(i + 1);
            global.hearts_skill_state[i + 1] |= 0x80;
        }
    }
    global.hearts_equipped = static_cast<uint8_t>(g.below(26));
}

// Compendium entries, some exact snapshots of stock demons.
void randomCompendium(Gen& g)
{
    GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
    int32_t entries = g.chance(10) ? g.range(182, 184) : g.range(0, 60);
    global.encyc_count = entries;
    for (int i = 0; i < entries; ++i) {
        UnitWork unit;
        randomUnit(g, unit, false);
        if (g.chance(40)) unit = global.units[g.range(4, 15)];
        else unit.id = static_cast<uint16_t>(g.range(1, 383));
        fcl::setRecord(global.encyc_records[i], unit);
        if (g.chance(20)) {   // a small difference
            EncycRecord& r = global.encyc_records[i];
            switch (g.below(5)) {
            case 0: r.level += 1; break;
            case 1: r.param[g.below(6)] += 1; break;
            case 2: if (r.skillcnt) r.skill[g.below(r.skillcnt)] ^= 1; break;
            case 3: r.flag ^= 0x40; break;
            default: r.preEvolutionExp += 1; break;
            }
        }
    }
    for (int i = 4; i < 16; ++i) {
        UnitWork& u = global.units[i];
        if (g.chance(20)) u.flag |= 0x10;
        if (g.chance(10)) u.badstat = 0x800;
    }
}

int8_t magatamaId(Gen& g) { return static_cast<int8_t>(g.chance(90) ? g.range(0, 25) : g.range(-3, 30)); }

} // namespace

void addMagatamaTests(std::vector<TestCase>& t)
{
    auto add = [&t](const char* name, std::function<Pair(Gen&)> make) {
        t.push_back({name, [make](Gen& g) { randomStock(g); randomMagatama(g); randomCompendium(g); return make(g); }});
    };
    auto none = [](auto call) { return [call] { call(); return uint64_t{0}; }; };

    // ---- ownership -------------------------------------------------------------
    add("cmbChkGetHearts", [](Gen& g) {
        int8_t id = magatamaId(g);
        return Pair{[=] { return norm(int32_t{cmbChkGetHearts(id)}); }, [=] { return norm(magatama::owns(id)); }};
    });
    add("cmpChkHaveHearts", [](Gen& g) {
        int8_t id = magatamaId(g);
        return Pair{[=] { return norm(int32_t{cmpChkHaveHearts(id)}); }, [=] { return norm(magatama::hasMagatama(id)); }};
    });
    add("cmpChkHaveNormalHeartsAll", [](Gen&) {
        return Pair{[] { return norm(cmpChkHaveNormalHeartsAll()); }, [] { return norm(magatama::ownsAllNormal()); }};
    });
    add("datAddHearts", [](Gen& g) {
        GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
        if (g.chance(30)) {   // own 1..24 but one, to reach the "all" event
            global.hearts_owned_count = 23;
            int missing = g.range(1, 24), n = 0;
            for (int id = 1; id <= 24; ++id) if (id != missing) global.hearts_owned[n++] = static_cast<uint8_t>(id);
        }
        int32_t id = g.range(1, 25);
        return Pair{[=] { return norm(datAddHearts(id)); }, [=] { return norm(magatama::add(id)); }};
    });
    add("fclChkItemHearts", [](Gen& g) {
        uint16_t item = static_cast<uint16_t>(g.chance(70) ? g.range(0x38, 0x60) : g.below(0x10000));
        return Pair{[=] { return norm(int32_t{fclChkItemHearts(item)}); }, [=] { return norm(int32_t{magatama::fromItem(item)}); }};
    });

    // ---- stat bonuses ----------------------------------------------------------
    add("cmbGetHeartsDefaultParam", [](Gen& g) {
        int8_t id = magatamaId(g), stat = static_cast<int8_t>(g.range(0, 5)), type = static_cast<int8_t>(g.range(-1, 2));
        return Pair{[=] { return norm(int32_t{cmbGetHeartsDefaultParam(id, stat, type)}); },
                    [=] { return norm(int32_t{magatama::baseParam(id, stat, type != 0)}); }};
    });
    add("cmbGetHeartsParamEx", [](Gen& g) {
        int8_t id = static_cast<int8_t>(g.range(0, 25)), stat = static_cast<int8_t>(g.range(0, 5)), mode = static_cast<int8_t>(g.range(0, 2));
        return Pair{[=] { return norm(int32_t{cmbGetHeartsParamEx(id, stat, mode)}); },
                    [=] { return norm(int32_t{magatama::paramWithUpgrades(id, stat, mode != 0)}); }};
    });
    add("cmbGetHeartsParam", [](Gen& g) {
        int8_t id = static_cast<int8_t>(g.range(0, 25)), stat = static_cast<int8_t>(g.range(0, 5));
        return Pair{[=] { return norm(int32_t{cmbGetHeartsParam(id, stat)}); }, [=] { return norm(int32_t{magatama::param(id, stat)}); }};
    });
    auto unitWithMagatama = [&add](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            uint8_t id = static_cast<uint8_t>(g.range(0, 25));
            uint32_t u = unitAddress(g.range(0, 15));
            return Pair{[=] { legacy(id, legacyUnit(u)); return uint64_t{0}; }, [=] { rewrite(id, unitAt(u)); return uint64_t{0}; }};
        });
    };
    unitWithMagatama("ps2HeartsAddParam", ps2HeartsAddParam, magatama::addParams);
    unitWithMagatama("cmbSubHeartsParam", cmbSubHeartsParam, magatama::removeParams);
    add("cmbGetHeartsAisyo", [](Gen& g) {
        uint8_t id = static_cast<uint8_t>(g.range(0, 25));
        return Pair{[=] { return norm(int32_t{cmbGetHeartsAisyo(id)}); }, [=] { return norm(int32_t{magatama::affinityRow(id)}); }};
    });
    add("cmbGetParamBase", [](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        if (g.chance(40)) unitAt(u).id = 0;
        int32_t stat = g.range(0, 5);
        return Pair{[=] { return norm(cmbGetParamBase(legacyUnit(u), stat)); }, [=] { return norm(magatama::paramWithoutMagatama(unitAt(u), stat)); }};
    });

    // ---- skills and mastery ----------------------------------------------------
    add("cmbGetHeartsSkillNums", [](Gen& g) {
        uint8_t id = static_cast<uint8_t>(g.range(0, 25));
        return Pair{[=] { return norm(int32_t{cmbGetHeartsSkillNums(id)}); }, [=] { return norm(int32_t{magatama::skillCount(id)}); }};
    });
    add("cmbGetHeartsSkillAt (0x222210)", [](Gen& g) {
        uint8_t id = static_cast<uint8_t>(g.range(1, 25));
        int8_t index = static_cast<int8_t>(g.range(-2, 9));
        return Pair{[=] { return norm(int32_t{ps2HeartsSkillAt(id, index)}); }, [=] { return norm(int32_t{magatama::skillAt(id, index)}); }};
    });
    add("cmbGetHeartsAfterSkillNums", [](Gen& g) {
        uint8_t id = static_cast<uint8_t>(g.range(0, 25));
        return Pair{[=] { return norm(int32_t{cmbGetHeartsAfterSkillNums(id)}); }, [=] { return norm(int32_t{magatama::learnedCount(id)}); }};
    });
    add("cmbAddHeartsSkill", [none](Gen& g) {
        int8_t id = static_cast<int8_t>(g.range(0, 25));
        uint16_t skill = static_cast<uint16_t>(g.below(0x200));
        return Pair{none([=] { cmbAddHeartsSkill(id, skill); }), none([=] { magatama::recordLearned(id, skill); })};
    });
    add("cmbCreateDefaultHeartsSkill", [](Gen& g) {
        uint8_t id = static_cast<uint8_t>(g.range(0, 25));
        uint32_t u = unitAddress(0);
        return Pair{[=] { return norm(int32_t{cmbCreateDefaultHeartsSkill(id, legacyUnit(u))}); },
                    [=] { return norm(int32_t{magatama::learnStartingSkills(id, unitAt(u))}); }};
    });
    add("cmbChkGetHeartsSkill", [](Gen& g) {
        uint8_t id = static_cast<uint8_t>(g.range(0, 25));
        uint32_t u = unitAddress(0);
        UnitWork& player = unitAt(u);
        player.level = static_cast<uint16_t>(g.range(1, 99));
        if (g.chance(50)) at<GlobalWork>(FW_GLOBAL).hearts_skill_state[id] &= 0xf0;   // nothing learned yet
        if (g.chance(50) && player.skillcnt < 8) player.skill[player.skillcnt++] = dat::magatama(id).skill[g.below(8)].id;
        return Pair{[=] { return norm(int32_t{cmbChkGetHeartsSkill(id, legacyUnit(u))}); },
                    [=] { return norm(int32_t{magatama::nextSkill(id, unitAt(u))}); }};
    });
    add("rstCreateBeforeSkillList", [none](Gen& g) {
        int8_t id = static_cast<int8_t>(g.range(0, 25));
        uint32_t u = unitAddress(g.range(0, 15));
        if (g.chance(40)) unitAt(u).id = 0;
        int8_t offset = static_cast<int8_t>(g.range(-5, 5));
        bool null = g.chance(5);
        return Pair{none([=] { rstCreateBeforeSkillList(id, null ? nullptr : legacyUnit(u), offset, &at<UpcomingSkills>(kList)); }),
                    none([=] { magatama::upcomingSkills(id, null ? nullptr : &unitAt(u), offset, at<UpcomingSkills>(kList)); })};
    });
    add("cmbChkHeartsMaster", [](Gen& g) {
        uint8_t id = static_cast<uint8_t>(g.range(0, 25));
        return Pair{[=] { return norm(int32_t{cmbChkHeartsMaster(id)}); }, [=] { return norm(magatama::isMastered(id)); }};
    });
    add("cmbGetMasterHeartsNums", [](Gen&) {
        return Pair{[] { return norm(int32_t{cmbGetMasterHeartsNums()}); }, [] { return norm(int32_t{magatama::masteredCount()}); }};
    });
    add("cmbSetHeartsMaster", [none](Gen& g) {
        int8_t id = static_cast<int8_t>(g.range(0, 25));
        return Pair{none([=] { cmbSetHeartsMaster(id); }), none([=] { magatama::setMastered(id); })};
    });
    add("cmbChkHeartsStat", [](Gen& g) {
        int8_t id = magatamaId(g);
        return Pair{[=] { return norm(int32_t{cmbChkHeartsStat(id)}); }, [=] { return norm(int32_t{magatama::statClass(id)}); }};
    });
    add("cmbChkMasterHeartsStatNums", [](Gen& g) {
        bool withTier = g.chance(80);
        auto pack = [](uint8_t stat, uint8_t tier) { return uint64_t{stat} << 8 | tier; };
        return Pair{[=] { uint8_t tier = 0x55; uint8_t s = cmbChkMasterHeartsStatNums(withTier ? &tier : nullptr); return pack(s, tier); },
                    [=] { uint8_t tier = 0x55; uint8_t s = magatama::masteredStatClass(withTier ? &tier : nullptr); return pack(s, tier); }};
    });
    add("cmbGetPlayerRaceID", [](Gen&) {
        return Pair{[] { return norm(int32_t{cmbGetPlayerRaceID(legacyUnit(unitAddress(0)))}); }, [] { return norm(int32_t{magatama::playerRace()}); }};
    });

    // ---- items ---------------------------------------------------------------------
    auto itemTest = [&add](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            int32_t item;
            switch (g.below(4)) {
            case 0: item = g.range(0x40, 0x58); break;        // Magatama
            case 1: item = item::Deathstone; break;
            case 2: item = g.range(0x70, 0x9f); break;        // key items
            default: item = g.range(1, 0x6f); break;
            }
            int32_t count = g.chance(80) ? g.range(-120, 120) : 0;
            uint8_t held = static_cast<uint8_t>(g.range(0, 99));
            if (g.chance(30)) count = (g.chance(50) ? 100 : 0) - held;   // totals of exactly 100 / 0
            at<GlobalWork>(FW_GLOBAL).item_counts[item] = held;
            return Pair{[=] { return legacy(item, count); }, [=] { return rewrite(item, count); }};
        });
    };
    itemTest("datAddItem", [](int32_t i, int32_t n) { datAddItem(i, n); return uint64_t{0}; },
             [](int32_t i, int32_t n) { dat::addItem(i, n); return uint64_t{0}; });
    itemTest("fclAddItem", [](int32_t i, int32_t n) { return norm(fclAddItem(static_cast<uint16_t>(i), n)); },
             [](int32_t i, int32_t n) { return norm(dat::receiveItem(static_cast<uint16_t>(i), n)); });

    // ---- compendium --------------------------------------------------------------
    add("fclEncyc_SetElem", [none](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        return Pair{none([=] { fclEncyc_SetElem(&at<EncycRecord>(kScratchRecord), legacyUnit(u)); }),
                    none([=] { fcl::setRecord(at<EncycRecord>(kScratchRecord), unitAt(u)); })};
    });
    add("fclencyceelem_t.Clear (0x219FC0)", [none](Gen& g) {
        uint32_t source = recordAddress(g.range(0, 40));
        return Pair{none([=] { ps2CompendiumRecords_00219FC0(kScratchRecord, source); }),
                    none([=] { fcl::copyRecord(at<EncycRecord>(kScratchRecord), at<EncycRecord>(source)); })};
    });
    add("fclEncycSearch", [](Gen& g) {
        GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
        int32_t id = g.chance(60) && global.encyc_count ? global.encyc_records[g.below(static_cast<uint32_t>(global.encyc_count))].id
                                                        : g.range(-2, 400);
        return Pair{[=] { return norm(ps2CompendiumRestore_00216B20(sx(id))); }, [=] { return norm(fcl::find(id)); }};
    });
    add("fclEncycGetNum", [](Gen&) {
        return Pair{[] { return norm(fclEncycGetNum()); }, [] { return norm(fcl::count()); }};
    });
    add("fclEncycGetRatio2", [](Gen&) {
        return Pair{[] { return norm(fclEncycGetRatio2()); }, [] { return norm(fcl::completionPercent()); }};
    });
    add("fclEncycRegist", [](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        int32_t overwrite = g.range(0, 1);
        return Pair{[=] { return norm(ps2CompendiumRecords_00216A18(u, sx(overwrite))); },
                    [=] { return norm(fcl::record(unitAt(u), overwrite != 0)); }};
    });
    add("fclEncycRegist2", [](Gen& g) {
        GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
        UnitWork unit = global.units[g.range(0, 15)];
        if (g.chance(50)) unit.id = static_cast<uint16_t>(g.range(1, 383));
        fcl::setRecord(at<EncycRecord>(kScratchRecord), unit);
        int32_t overwrite = g.range(0, 1);
        return Pair{[=] { return norm(ps2CompendiumRecords_00216910(kScratchRecord, sx(overwrite))); },
                    [=] { return norm(fcl::recordCopy(at<EncycRecord>(kScratchRecord), overwrite != 0)); }};
    });
    add("CompareUnitToRecord", [](Gen& g) {
        uint32_t u = unitAddress(g.range(0, 15));
        uint32_t r = g.chance(30) ? recordAddress(g.range(0, 30)) : kScratchRecord;
        if (r == kScratchRecord) {   // the unit's own snapshot with one difference (or none)
            EncycRecord& rec = at<EncycRecord>(r);
            fcl::setRecord(rec, unitAt(u));
            int lane = g.range(0, 5);
            switch (g.below(12)) {
            case 0: rec.param[lane] += 1; break;
            case 1: rec.skillparam[lane] += 1; break;
            case 2: rec.mitamaparam[lane] += 1; break;
            case 3: rec.levelupparam[lane] += 1; break;
            case 4: rec.flag ^= g.chance(50) ? 0x40 : 0x200; break;
            case 5: rec.maxhp += 1; break;
            case 6: rec.exp += 1; break;
            case 7: if (rec.skillcnt > 1) std::swap(rec.skill[0], rec.skill[rec.skillcnt - 1]); break;
            case 8: if (rec.skillcnt) rec.skill[g.below(rec.skillcnt)] += 1; break;
            case 9: rec.preEvolutionId += 1; break;
            case 10: rec.skillcnt += 1; break;
            default: break;
            }
        }
        return Pair{[=] { return norm(ps2CompendiumRestore_0021A308(u, r)); }, [=] { return norm(fcl::compareToRecord(unitAt(u), at<EncycRecord>(r))); }};
    });
    add("GetValidUnitIndex", [](Gen& g) {
        bool list = g.chance(70);
        return Pair{[=] { return norm(ps2CompendiumRestore_00219318(list ? kList : 0)); },
                    [=] { return norm(fcl::outdatedUnits(list ? &at<uint8_t>(kList) : nullptr)); }};
    });
    add("fclEncycCheckRegistable", [](Gen&) {
        return Pair{[] { return norm(ps2CompendiumRestore_00216BF0()); }, [] { return norm(fcl::anyOutdated()); }};
    });
    add("RegistAll", [](Gen& g) {
        auto& list = at<fcl::RegisterList>(kList);
        list.count = g.range(0, 12);
        for (uint8_t& unit : list.unit) unit = static_cast<uint8_t>(g.range(0, 15));
        return Pair{[] { return norm(ps2CompendiumRecords_00219400(kList)); }, [] { return norm(fcl::recordAll(at<fcl::RegisterList>(kList))); }};
    });
    add("fclEncycDebugRegist", [none](Gen&) {
        return Pair{none([] { ps2CompendiumRecords_00216C08(); }), none([] { fcl::debugRecordStock(); })};
    });
    add("SetRecordToUnit", [none](Gen& g) {
        GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
        int32_t id = global.encyc_count ? global.encyc_records[g.below(static_cast<uint32_t>(global.encyc_count))].id : 1;
        return Pair{none([=] { ps2CompendiumRestore_0021A0B8(kScratchUnit, sx(id)); }), none([=] { fcl::restore(unitAt(kScratchUnit), id); })};
    });
    add("SetRecordToUnitCore", [none](Gen& g) {
        uint32_t r = recordAddress(g.range(0, 40));
        return Pair{none([=] { ps2CompendiumRestore_0021A118(kScratchUnit, r); }), none([=] { fcl::restoreFromRecord(unitAt(kScratchUnit), at<EncycRecord>(r)); })};
    });
    add("FillIndex", [none](Gen& g) {
        int32_t n = g.range(-1, 184);
        return Pair{none([=] { ps2CompendiumRecords_00219DC0(kList, sx(n)); }), none([=] { fcl::fillIndex(&at<int16_t>(kList), n); })};
    });
    auto compare = [&add](const char* name, auto legacy, auto rewrite) {
        add(name, [=](Gen& g) {
            GlobalWork& global = at<GlobalWork>(FW_GLOBAL);
            int32_t n = global.encyc_count ? global.encyc_count : 1;
            int16_t* pair = &at<int16_t>(kList);
            pair[0] = static_cast<int16_t>(g.below(static_cast<uint32_t>(n)));
            pair[1] = static_cast<int16_t>(g.below(static_cast<uint32_t>(n)));
            return Pair{[=] { return norm(legacy(kList, kList + 2)); }, [=] { return norm(rewrite(&at<int16_t>(kList), &at<int16_t>(kList + 2))); }};
        });
    };
    compare("cmbRaceSortCallback", ps2CompendiumRecords_00219C40, fcl::compareByRace);
    compare("cmbLevelSortCallback", ps2CompendiumRecords_00219D00, fcl::compareByLevel);
    add("CreateSortIndexByRace", [none](Gen&) {
        return Pair{none([] { ps2CompendiumRecords_00219BA0(kList); }), none([] { fcl::sortByRace(&at<int16_t>(kList)); })};
    });
    add("CreateSortIndexByLevel", [none](Gen&) {
        return Pair{none([] { ps2CompendiumRecords_00219BF0(kList); }), none([] { fcl::sortByLevel(&at<int16_t>(kList)); })};
    });
}

} // namespace difftest
