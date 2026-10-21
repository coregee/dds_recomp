// Magatama (original units: cmb, cmp, rst, dat).
#include "nocturne/data/magatama.hpp"

#include <cstddef>

#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/growth.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::magatama {

namespace {

constexpr uint32_t kItemMagatama = 0x0053d6e8;   // int8_t[25]: Magatama for items 0x40..0x58

GlobalWork& global() { return dat::globalWork(); }

void appendUpcoming(UpcomingSkills& list, int8_t level, uint16_t skill)
{
    int32_t index = list.skillcnt;
    list.targetlevel[index] = static_cast<uint8_t>(level);
    list.skillcnt = static_cast<int8_t>(list.skillcnt + 1);
    list.skill[index] = skill;
}

} // namespace

// ===========================================================================
// Ownership
// ===========================================================================

// cmbChkGetHearts @ 0x00221DD8
bool owns(int8_t id)
{
    for (int i = 0; i < global().hearts_owned_count; ++i)
        if (global().hearts_owned[i] == id)
            return true;
    return false;
}

// cmpChkHaveHearts @ 0x002328C8
bool hasMagatama(int8_t id)
{
    return owns(id);
}

// cmpChkHaveNormalHeartsAll @ 0x00232880
bool ownsAllNormal()
{
    for (int8_t id = 1; id <= 24; ++id)
        if (!hasMagatama(id))
            return false;
    return true;
}

// datAddHearts @ 0x002452C8: compared as a full int, stored as a byte.
bool add(int32_t id)
{
    GlobalWork& g = global();
    for (int i = 0; i < g.hearts_owned_count; ++i)
        if (g.hearts_owned[i] == id)
            return false;
    g.hearts_owned[g.hearts_owned_count++] = static_cast<uint8_t>(id);
    g.hearts_skill_state[id] = 0;
    if (ownsAllNormal())
        evt::BitOn(0x860);
    learnStartingSkills(static_cast<uint8_t>(id), g.units[0]);
    return true;
}

// fclChkItemHearts @ 0x002138C0
int8_t fromItem(uint16_t item)
{
    uint16_t index = static_cast<uint16_t>(item - 0x40);
    return index < 25 ? guest::table<const int8_t>(kItemMagatama)[index] : 0;
}

// ===========================================================================
// Stat bonuses
// ===========================================================================

// cmbGetHeartsDefaultParam @ 0x002222C0
int8_t baseParam(int8_t id, int8_t stat, bool mastered)
{
    const MagatamaData& data = dat::magatama(id);
    return mastered ? data.mastergrowparam[stat] : data.growparam[stat];
}

// cmbGetHeartsParamEx @ 0x00222318
int8_t paramWithUpgrades(int8_t id, int8_t stat, bool mastered)
{
    return static_cast<int8_t>(baseParam(id, stat, mastered) + global().hearts_param_upgrades[id][stat]);
}

// cmbGetHeartsParam @ 0x002223A0
int8_t param(int8_t id, int8_t stat)
{
    return paramWithUpgrades(id, stat, isMastered(static_cast<uint8_t>(id)));
}

// ps2HeartsAddParam @ 0x00222408
void addParams(uint8_t id, UnitWork& unit)
{
    for (int8_t i = 0; i < 6; ++i)
        unit.param[i] = static_cast<int8_t>(unit.param[i] + param(static_cast<int8_t>(id), i));
}

// cmbSubHeartsParam @ 0x00222470
void removeParams(uint8_t id, UnitWork& unit)
{
    for (int8_t i = 0; i < 6; ++i)
        unit.param[i] = static_cast<int8_t>(unit.param[i] - param(static_cast<int8_t>(id), i));
}

// cmbGetHeartsAisyo @ 0x00222290
int16_t affinityRow(uint8_t id)
{
    return id == 0 ? 0 : dat::magatama(id).aisyoid;
}

// cmbGetParamBase @ 0x00221D00
int32_t paramWithoutMagatama(const UnitWork& unit, int32_t stat)
{
    if (unit.id != 0)
        return dat::param(unit, static_cast<Param>(stat));
    int32_t value = unit.param[stat];
    if (uint8_t equipped = global().hearts_equipped)
        value -= param(static_cast<int8_t>(equipped), static_cast<int8_t>(stat));
    return value;
}

// ===========================================================================
// Skills and mastery
// ===========================================================================

// cmbGetHeartsSkillNums @ 0x002220C0
int16_t skillCount(uint8_t id)
{
    int8_t count = 0;
    if (id != 0)
        for (const MagatamaSkill& skill : dat::magatama(id).skill)
            if (skill.id != 0)
                ++count;
    return count;
}

// 0x00222210 (unnamed): the skill in a slot; a negative index reads the
// bytes before the list.
uint16_t skillAt(uint8_t id, int8_t index)
{
    if (index >= 8)
        return 0;
    uint32_t slot = dat::address::Magatama + id * static_cast<uint32_t>(sizeof(MagatamaData))
                  + static_cast<uint32_t>(offsetof(MagatamaData, skill)) + static_cast<uint32_t>(index * 4);
    return guest::table<const MagatamaSkill>(slot)->id;
}

// cmbGetHeartsAfterSkillNums @ 0x002221D0
int8_t learnedCount(uint8_t id)
{
    return static_cast<int8_t>(global().hearts_skill_state[id] & 0x0f);
}

// cmbAddHeartsSkill @ 0x002224D8: the increment is on the whole state byte.
void recordLearned(int8_t id, uint16_t skill)
{
    uint8_t index = static_cast<uint8_t>(id);
    global().hearts_learned_skills[index][static_cast<uint8_t>(learnedCount(index))] = skill;
    global().hearts_skill_state[index] += 1;
}

// cmbCreateDefaultHeartsSkill @ 0x00222550: the level-0 skills.
int8_t learnStartingSkills(uint8_t id, UnitWork& unit)
{
    if (id == 0)
        return 0;
    for (const MagatamaSkill& skill : dat::magatama(id).skill) {
        if (skill.id != 0 && skill.targetlevel == 0) {
            unit.skill[unit.skillcnt++] = skill.id;
            recordLearned(static_cast<int8_t>(id), skill.id);
        }
    }
    return static_cast<int8_t>(unit.skillcnt);
}

// cmbChkGetHeartsSkill @ 0x002226B8: skills are learned in
// order, so the search starts after the ones already learned.
uint16_t nextSkill(uint8_t id, const UnitWork& unit)
{
    const MagatamaData& data = dat::magatama(id);
    for (int32_t i = learnedCount(id); i < 8; ++i) {
        const MagatamaSkill& skill = data.skill[i];
        int8_t level = static_cast<int8_t>(skill.targetlevel);
        if (skill.id != 0 && level != 0 && unit.level >= level && cmb::findSkill(skill.id, unit) < 0)
            return skill.id;
    }
    return 0;
}

// rstCreateBeforeSkillList @ 0x00220508. The Demi-fiend's list ignores the
// level; a demon's lists growth skills above level + levelOffset (event type
// 1, or 6 once it has evolved).
void upcomingSkills(int8_t id, const UnitWork* unit, int8_t levelOffset, UpcomingSkills& list)
{
    if (!unit)
        return;
    list.skillcnt = 0;
    if (unit->id == 0) {
        if (id == 0)
            return;
        const MagatamaData& data = dat::magatama(id);
        for (int32_t i = learnedCount(static_cast<uint8_t>(id)); i < 8; ++i) {
            const MagatamaSkill& skill = data.skill[i];
            if (skill.id != 0 && cmb::findSkill(skill.id, *unit) < 0)
                appendUpcoming(list, static_cast<int8_t>(skill.targetlevel), skill.id);
        }
    } else {
        uint8_t type = unit->hensinmae == 0 ? 1 : 6;
        for (const GrowthEvent& event : dat::devilGrowth(unit->id).event) {
            if (event.type == type && unit->level + levelOffset < event.targetlevel
                && cmb::findSkill(event.param, *unit) < 0)
                appendUpcoming(list, event.targetlevel, event.param);
        }
    }
}

// cmbChkHeartsMaster @ 0x00222140
bool isMastered(uint8_t id)
{
    return (global().hearts_skill_state[id] & 0x80) != 0;
}

// cmbGetMasterHeartsNums @ 0x00222160
int8_t masteredCount()
{
    int32_t count = 0;
    for (int i = 0; i < global().hearts_owned_count; ++i)
        count += isMastered(global().hearts_owned[i]);
    return static_cast<int8_t>(count);
}

// cmbSetHeartsMaster @ 0x002221E8
void setMastered(int8_t id)
{
    global().hearts_skill_state[id] |= 0x80;
}

// ===========================================================================
// The Demi-fiend's race
// ===========================================================================

// cmbChkHeartsStat @ 0x00221EF8
uint8_t statClass(int8_t id)
{
    return dat::magatama(id).flag & 7;
}

// cmbChkMasterHeartsStatNums @ 0x00221F20. Counts mastered Magatama of
// classes 1, 0 and 4 (as bytes). Class 1 or 4 wins if it has more than the
// other and isn't beaten by class 0 in a three-way comparison; otherwise 0.
// Tier: half the mastered count below 6, then 3 below 12, 4, and 5 for all 25.
uint8_t masteredStatClass(uint8_t* tier)
{
    uint8_t classOne = 0, classZero = 0, classFour = 0;
    for (int i = 0; i < global().hearts_owned_count; ++i) {
        int8_t id = static_cast<int8_t>(global().hearts_owned[i]);
        if (!isMastered(static_cast<uint8_t>(id)))
            continue;
        switch (statClass(id)) {
        case 1: ++classOne; break;
        case 0: ++classZero; break;
        case 4: ++classFour; break;
        default: break;
        }
    }
    int32_t one = static_cast<int8_t>(classOne), zero = static_cast<int8_t>(classZero), four = static_cast<int8_t>(classFour);
    uint8_t result = 0;
    if (one != four && !(one < zero && four < zero))
        result = one < four ? 4 : 1;

    int32_t mastered = masteredCount();
    int32_t amount;
    if (mastered < 6) amount = mastered / 2;
    else if (mastered == 25) amount = 5;
    else amount = mastered < 12 ? 3 : 4;
    if (tier)
        *tier = static_cast<uint8_t>(amount);
    return result;
}

// cmbGetPlayerRaceID @ 0x00221E70 (its unit argument is unused)
uint8_t playerRace()
{
    uint8_t tier;
    uint8_t stat = masteredStatClass(&tier);
    if (tier == 0)
        return 0;
    uint32_t suffix = stat == 1 ? 1 : stat == 4 ? 3 : 2;
    return static_cast<uint8_t>(static_cast<uint8_t>(tier - 1) * 3u + suffix);
}

} // namespace nocturne::magatama
