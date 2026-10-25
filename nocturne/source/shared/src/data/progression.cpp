// The save game's party and the Demi-fiend's progress (original unit: datCalc).
#include "nocturne/data/progression.hpp"

#include <cstring>

#include "nocturne/address.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/magatama.hpp"
#include "nocturne/facility/compendium.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/growth.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/build.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::dat {

namespace {

// The EE's DIV: dividing by zero doesn't trap (the compiler only inserts a
// check where the source divided by a variable it couldn't prove nonzero);
// it yields -1, or 1 for a negative dividend.
int32_t eeDivide(int32_t numerator, int32_t denominator)
{
    if (denominator == 0)
        return numerator < 0 ? 1 : -1;
    return static_cast<int32_t>(static_cast<int64_t>(numerator) / denominator);
}

int32_t wrappingMultiply(int32_t a, int32_t b)
{
    return static_cast<int32_t>(static_cast<uint32_t>(static_cast<int64_t>(a) * b));
}

// x * ratio / 1024 for a 10-bit fixed-point ratio, rounding toward zero.
uint16_t scaleBy1024(int32_t value)
{
    if (value < 0)
        value += 0x3ff;
    return static_cast<uint16_t>(value >> 10);
}

UnitWork& player() { return globalWork().units[0]; }

bool inActiveParty(const UnitWork& unit)
{
    return (unit.flag & (UnitFlag::Valid | UnitFlag::InParty)) == (UnitFlag::Valid | UnitFlag::InParty);
}

// The species' level, stats and level-0 skills. Max HP/MP are computed
// before the skill count is updated, so they use the unit's *old* count over
// the new skill list (for a cleared unit: no skills).
void setSpeciesDefaults(uint16_t devil, UnitWork& unit)
{
    const DevilFormat& format = devilFormat(devil);
    unit.level = format.level;
    for (int i = 0; i < 6; ++i)
        unit.param[i] = format.param[i];
    uint16_t count = 0;
    for (const GrowthEvent& event : devilGrowth(devil).event)
        if (event.targetlevel == 0 && event.type == GrowthEventType::Skill)
            unit.skill[count++] = event.param;
    unit.hp = unit.maxhp = static_cast<uint16_t>(maxHp(unit));
    uint16_t mp = static_cast<uint16_t>(maxMp(unit));
    unit.skillcnt = count;
    unit.mp = unit.maxmp = mp;
}

} // namespace

// ===========================================================================
// One unit
// ===========================================================================

// cmpSetMaxHPMP @ 0x00240A98
void rescaleHpMp(UnitWork& unit)
{
    if (unit.maxhp == 0)
        divideByZeroTrap();
    int32_t hpRatio = eeDivide(unit.hp << 10, unit.maxhp);
    int32_t mpRatio = eeDivide(unit.mp << 10, unit.maxmp);   // maxmp 0: ratio -1, no trap
    unit.maxhp = static_cast<uint16_t>(maxHp(unit));
    unit.maxmp = static_cast<uint16_t>(maxMp(unit));
    unit.mp = scaleBy1024(wrappingMultiply(unit.maxmp, mpRatio));
    unit.hp = scaleBy1024(wrappingMultiply(unit.maxhp, hpRatio));
}

// datGetAisyoFlag @ 0x00244098
uint32_t affinityFlags(const UnitWork& unit, Attribute attr)
{
    return affinity(unit, attr) & 0xffff0000u;
}

// 0x00244078 (no original name): datGetAisyo's low half.
uint32_t affinityRate(const UnitWork& unit, Attribute attr) { return affinity(unit, attr) & 0xffff; }

// datCheckTalk @ 0x002444A8: no talking while shocked, frozen, asleep,
// panicked, bound, flying or stoned.
bool canTalk(const UnitWork& unit)
{
    switch (unit.badstat & kAilmentMask) {
    case ailment::Shock: case ailment::Freeze: case ailment::Sleep: case ailment::Panic:
    case ailment::Bind: case ailment::Fly: case ailment::Stone:
        return false;
    default:
        return true;
    }
}

// datGetLevelForDraw @ 0x00245D18
int32_t levelForDraw(const UnitWork& unit) { return unit.level > 99 ? 99 : unit.level; }

// datAddExp @ 0x002452B8
void addExp(UnitWork& unit, int32_t exp)
{
    unit.exp = static_cast<int32_t>(static_cast<uint32_t>(unit.exp) + static_cast<uint32_t>(exp));
}

// datClearCommMemory @ 0x002457F0
void clearCommandMemory(UnitWork& unit)
{
    unit.prevcommand = 0;
    unit.prevtform = -1;
    unit.previndex = 0;
    unit.prevtarea = -1;
}

// datSetDevilWork @ 0x00244EF8
void initDevil(uint16_t devil, UnitWork& unit)
{
    std::memset(&unit, 0, sizeof unit);
    unit.flag = UnitFlag::Valid;
    unit.id = devil;
    unit.exp = 0;
    setSpeciesDefaults(devil, unit);
}

// datCopyDevilWork @ 0x00245D30: the other fields (flags, ailment, unique ID,
// inherited skills ...) are kept, and so are skills past the default ones.
void resetToSpecies(uint16_t devil, UnitWork& unit)
{
    setSpeciesDefaults(devil, unit);
    diag::print(diag::Message::ResetLevel, unit.level);
    uint32_t exp = cmb::expForLevel(unit, unit.level);
    unit.exp = static_cast<int32_t>(exp);
    diag::print(diag::Message::ResetExp, static_cast<int32_t>(exp));
    fcl::record(unit, false);
}

// ===========================================================================
// The Demi-fiend
// ===========================================================================

// datGetPlayerParam @ 0x002445C0
int32_t playerParam(Param stat)
{
    int32_t index = static_cast<int32_t>(stat);
    int32_t value = player().param[index];
    if (uint8_t equipped = globalWork().hearts_equipped)
        value -= magatama::param(static_cast<int8_t>(equipped), static_cast<int8_t>(index));
    return value;
}

// datAddPlayerParam @ 0x00244610
void addPlayerParam(Param stat, int32_t amount)
{
    int8_t& param = player().param[static_cast<int32_t>(stat)];
    int32_t value = static_cast<int32_t>(static_cast<uint32_t>(param) + static_cast<uint32_t>(amount));
    if (value >= 41)
        value = 40;
    param = static_cast<int8_t>(value);
    rescaleHpMp(player());
    player().hp = player().maxhp;
    player().mp = player().maxmp;
}

// datGetPlayerLND @ 0x002446B0 ("LND" = Law / Neutral / Dark)
int32_t playerAlignment()
{
    uint8_t race = magatama::playerRace();
    return race ? (race - 1) % 3 : 1;
}

// datCheckPlayerDead @ 0x002445A8
bool isPlayerDead() { return (player().badstat & kAilmentMask) == ailment::Dead; }

// datAddMaka @ 0x00244238
void addMacca(int32_t amount)
{
    GlobalWork& global = globalWork();
    int32_t macca = static_cast<int32_t>(static_cast<uint32_t>(global.macca) + static_cast<uint32_t>(amount));
    if (macca < 0)
        macca = 0;
    if (macca > 9999999)
        macca = 9999999;
    global.macca = macca;
}

// datCheckMaka @ 0x002442C8
bool hasMacca(int32_t amount) { return amount <= globalWork().macca; }

// datInitPlayer @ 0x00245B10: the Demi-fiend from the template at 0x3493C0.
void initPlayer()
{
    GlobalWork& global = globalWork();
    std::memset(global.units, 0, sizeof global.units);
    std::memcpy(&global.units[0], guest::table<uint8_t>(addr(0x003493c0)), 0xe8);
    global.stock_list[0] = 0;
    global.stock_count = 1;
    global.macca = 0;
    for (uint8_t& count : global.item_counts)
        count = 0;
    evt::BitOn(0xc04);
}

// datAddMakaPar @ 0x00244268: change Macca by a percentage (32-bit math).
void addMaccaPercent(int32_t percent)
{
    GlobalWork& global = globalWork();
    uint32_t macca = static_cast<uint32_t>(global.macca);
    uint32_t magnitude = percent < 0 ? 0u - static_cast<uint32_t>(percent) : static_cast<uint32_t>(percent);
    uint32_t change = static_cast<uint32_t>(eeDivide(wrappingMultiply(static_cast<int32_t>(macca), static_cast<int32_t>(magnitude)), 100));
    uint32_t result = percent < 0 ? macca - change : macca + change;
    if (result & 0x80000000u)
        result = 0;
    if (result > 9999999u)
        result = 9999999u;
    global.macca = static_cast<int32_t>(result);
}

// datRemoveHearts @ 0x00245380 (an empty hook at 0x221558 followed the
// parameter change)
void removeMagatama()
{
    GlobalWork& global = globalWork();
    if (!global.hearts_owned_count)
        return;
    magatama::removeParams(global.hearts_equipped, player());
    global.hearts_equipped = 0;
    rescaleHpMp(player());
}

// datEquipHearts @ 0x002453E8 (empty hook at 0x221550)
void equipMagatama(uint8_t id)
{
    GlobalWork& global = globalWork();
    if (!global.hearts_owned_count || global.hearts_equipped == id)
        return;
    removeMagatama();
    global.hearts_equipped = id;
    magatama::addParams(global.hearts_equipped, player());
    rescaleHpMp(player());
}

// ===========================================================================
// The party and stock
// ===========================================================================

// datGetNakamaParam @ 0x00244668: the stat of a demon in the stock (units
// 1..15, empty or not; the last match wins).
int32_t companionParam(uint16_t devil, Param stat)
{
    int32_t value = 0;
    for (int i = 1; i < 16; ++i)
        if (globalWork().units[i].id == devil)
            value = globalWork().units[i].param[static_cast<int32_t>(stat)];
    return value;
}

// datDeadNakama @ 0x002446F8
void killCompanion(uint16_t devil)
{
    for (int i = 1; i < 16; ++i) {
        UnitWork& unit = globalWork().units[i];
        if (!(unit.flag & UnitFlag::Valid) || unit.id != devil)
            continue;
        if (unit.hp) {
            unit.hp = 0;
            setAilment(unit, ailment::Dead);
        }
        unit.flag &= ~UnitFlag::InParty;
    }
}

// datAddDevil @ 0x00245020
int32_t addDevil(int32_t devil, bool joinParty)
{
    bool registerInCompendium = devil >= 0;
    devil &= 0x7fffffff;
    GlobalWork& global = globalWork();

    int partySize = 0;
    for (const UnitWork& unit : global.units)
        if (inActiveParty(unit))
            ++partySize;

    // Demons occupy units[4 ..]; stock_capacity counts those slots.
    int32_t slot = 0;
    while (slot < global.stock_capacity && (global.units[4 + slot].flag & UnitFlag::Valid))
        ++slot;
    if (slot == global.stock_capacity)
        return -1;

    UnitWork& unit = global.units[4 + slot];
    initDevil(static_cast<uint16_t>(devil), unit);
    if (registerInCompendium)
        fcl::record(unit, false);
    if (joinParty && partySize < 4)
        unit.flag |= UnitFlag::InParty;
    global.stock_list[global.stock_count] = static_cast<uint8_t>(slot + 4);
    global.stock_count += 1;
    return slot + 4;
}

// datAddUniqueDevil @ 0x00245180: a story demon with a unique ID (1 is
// also flagged 0x1000). There is no check for a full stock: the result -1
// then writes into the 0xEC bytes before units[0].
void addUniqueDevil(int32_t devil, bool joinParty, int32_t uniqueId)
{
    int32_t index = addDevil(devil, joinParty);
    uint32_t address = guest::addressOf(&globalWork().units[0]) + static_cast<uint32_t>(index) * sizeof(UnitWork);
    UnitWork& unit = *guest::table<UnitWork>(address);
    uint32_t flag = unit.flag;
    unit.uniqueid = static_cast<uint16_t>(uniqueId);
    unit.flag = flag | 0x400;
    if (uniqueId == 1)
        unit.flag = flag | 0x1400;
}

// datSearchUniqueDevilStock @ 0x002451F0
int32_t findUniqueDevil(int32_t uniqueId)
{
    for (int i = 0; i < 16; ++i) {
        const UnitWork& unit = globalWork().units[i];
        if ((unit.flag & UnitFlag::Valid) && !(unit.flag & UnitFlag::PlayerCharacter) && (unit.flag & 0x400)
            && unit.uniqueid == uniqueId)
            return i;
    }
    return -1;
}

// datGetUniqueDevilId @ 0x00245250
int32_t uniqueDevilId(int32_t uniqueId)
{
    const int32_t index = findUniqueDevil(uniqueId);
    return index < 0 ? -1 : globalWork().units[index].id;
}

// datSearchDevilStock @ 0x00244530: a demon (not the Demi-fiend) of that species.
int32_t findDevil(int32_t devil)
{
    for (int i = 0; i < 16; ++i) {
        const UnitWork& unit = globalWork().units[i];
        if ((unit.flag & UnitFlag::Valid) && !(unit.flag & UnitFlag::PlayerCharacter) && unit.id == devil)
            return i;
    }
    return -1;
}

// datCheckStockFull @ 0x00244EB8: as many demons as the stock holds.
bool isStockFull()
{
    int32_t count = 0;
    for (int i = 4; i < 16; ++i)
        count += globalWork().units[i].flag & UnitFlag::Valid;
    return globalWork().stock_capacity <= count;
}

// datDelDevil @ 0x00245C78
int32_t removeDevil(int32_t devil) { return cmp::RemoveDevilEx(static_cast<uint16_t>(devil)); }

// datAllClearCommMemory @ 0x00245808
void clearPartyCommandMemory()
{
    for (UnitWork& unit : globalWork().units)
        clearCommandMemory(unit);
}

// ===========================================================================
// Items
// ===========================================================================

// datCheckItem @ 0x002443F8
bool hasItem(int32_t item, int32_t count)
{
    return count <= globalWork().item_counts[item];
}

// datCheckItemFull @ 0x00244410: items below 0x70 stack to 99; the rest are one-off.
bool isItemFull(int32_t item)
{
    const uint8_t count = globalWork().item_counts[item];
    return item < 0x70 ? count >= 99 : count != 0;
}

// datAddItem @ 0x002442E0
void addItem(int32_t item, int32_t count)
{
    if (int8_t given = magatama::fromItem(static_cast<uint16_t>(item))) {
        magatama::add(given);
        return;
    }
    uint8_t* held = &globalWork().item_counts[0] + item;
    if (item < 0x70) {
        int32_t sum = static_cast<int32_t>(static_cast<uint32_t>(*held) + static_cast<uint32_t>(count));
        *held = static_cast<uint8_t>(sum < 0 ? 0 : sum > 99 ? 99 : sum);
        return;
    }
    evt::BitOn(item + 0x360);
    if (item != item::Deathstone || count == 0)
        return;
    int32_t sum = static_cast<int32_t>(static_cast<uint32_t>(*held) + static_cast<uint32_t>(count));
    if (count > 0) {
        if (sum >= 100)
            sum = 99;
    } else if (sum <= 0) {
        evt::BitOff(0x3ed);   // no Deathstone left
        sum = 0;
    }
    *held = static_cast<uint8_t>(sum);
}

// fclAddItem @ 0x00213938
int32_t receiveItem(uint16_t item, int32_t count)
{
    if (int8_t given = magatama::fromItem(item))
        magatama::add(given);
    else
        addItem(item, count);
    return 1;
}

// ===========================================================================
// Skills outside battle
// ===========================================================================

// datSetAutoKaifukuSkill @ 0x00245478. The divisors come from the skill's
// SpecialSkill record: Life Aid / Life Refill restore max HP / n, Mana Aid /
// Mana Refill max MP / n, Victory Cry max HP / n and max MP / m.
void applyRecoverySkill(UnitWork& unit, uint16_t skill)
{
    if (!hasSkill(unit, skill) || skill < skill::LifeAid || skill > skill::ManaRefill)
        return;
    int32_t hp = 0, mp = 0;
    const SpecialSkill& divisors = specialSkill(skill);
    switch (skill) {
    case skill::LifeAid:
    case skill::LifeRefill:
        if (divisors.n > 0) hp = unit.maxhp / divisors.n;
        break;
    case skill::ManaAid:
    case skill::ManaRefill:
        if (divisors.n > 0) mp = unit.maxmp / divisors.n;
        break;
    case skill::VictoryCry:
        if (divisors.n > 0) hp = unit.maxhp / divisors.n;
        if (divisors.m > 0) mp = unit.maxmp / divisors.m;
        break;
    default:
        break;
    }
    if (hp > 0)
        addHp(unit, hp);
    if (mp > 0)
        addMp(unit, mp);
}

// datFieldSkillKaifuku @ 0x002455B8: each step on the field map.
void recoverPartyWhileWalking()
{
    for (UnitWork& unit : globalWork().units) {
        if (inActiveParty(unit)) {
            applyRecoverySkill(unit, skill::LifeRefill);
            applyRecoverySkill(unit, skill::ManaRefill);
        }
    }
}

// datCheckSkillTakaraSagasi @ 0x002456D0 ("takara sagasi" = treasure
// hunting): whether a party member's Lucky Find turns up an extra item.
// Chance per owner: (Luck x 128 / 100) + 1 in 32, using the raw Luck stat.
// An optional event bit (0 in the shipped game) can disable it.
uint16_t luckyFindOwner()
{
    int32_t requiredEvent = *guest::table<const int32_t>(addr(0x003dc920));
    if (requiredEvent && !evt::BitCheck(requiredEvent))
        return 0;
    for (const UnitWork& unit : globalWork().units) {
        if (!inActiveParty(unit))
            continue;
        int32_t threshold = eeDivide(unit.param[static_cast<int32_t>(Param::Luck)] << 7, 100);
        if (!hasSkill(unit, skill::LuckyFind))
            continue;
        int32_t roll = sdf::GetRandInt(32);
        if (threshold >= roll)
            return unit.id;
    }
    return 0;
}

// ===========================================================================
// Reason (Kotowari)
// ===========================================================================

// datAddKotowariPoint @ 0x00245890
void addReasonPoints(int32_t reason, int32_t amount)
{
    if (reason == 0)
        return;
    uint8_t& points = globalWork().reason_points[reason];
    int32_t value = static_cast<int32_t>(static_cast<uint32_t>(points) + static_cast<uint32_t>(amount));
    if (value < 0)
        value = 0;
    if (value > 128)
        value = 128;
    points = static_cast<uint8_t>(value);
}

// datGetKotowariLank @ 0x002458D0: the Reasons 1..3 sorted by points, most
// first; ties are broken by a coin flip each time they are compared.
int32_t reasonRank(int32_t rank)
{
    int32_t order[3] = {1, 2, 3};
    const uint8_t* points = globalWork().reason_points;
    for (int i = 0; i < 2; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            uint8_t right = points[order[j]], left = points[order[i]];
            if (right < left)
                continue;
            if (right == left && sdf::GetRandInt(100) < 50)
                continue;
            int32_t swap = order[i];
            order[i] = order[j];
            order[j] = swap;
        }
    }
    return order[rank];
}

// ===========================================================================
// Boss refights
// ===========================================================================

namespace {

const BossPress* bossPresses() { return guest::table<const BossPress>(addr(0x003fa430)); }
constexpr int kBossPresses = 40;

} // namespace

// datInitBossPress @ 0x00245C40
void initBossPress()
{
    for (auto& record : globalWork().boss_records) {
        record[0] = -1;
        record[1] = -1;
    }
}

// datBossRashGetRec @ 0x00245E60
// The last fight's record needs the refight open; a closed entry for the
// same encounter is skipped and the search goes on.
int32_t bossPressRecord(int32_t encounter, int32_t type)
{
    for (int i = 0; i < kBossPresses; ++i) {
        const BossPress& boss = bossPresses()[i];
        if (boss.encid != encounter)
            continue;
        const int16_t* record = globalWork().boss_records[i];
        if (type == 0)
            return record[0] < 1 ? 999 : record[0];
        if (type != 1)
            return boss.dbest;
        if (evt::BitCheck(boss.flag))
            return record[1] == 0 ? 1 : record[1];
    }
    return 0;
}

// datBossRashUpdRec @ 0x00245F68
// A refight's press turns (at least 1); a new best also sets the entry's
// second event bit. Two story fights count as their refights' encounters.
void updateBossPressRecord(int32_t encounter, int32_t press)
{
    if (encounter == 0x3e1)
        encounter = 0x1d8;
    if (encounter == 0x3e0)
        encounter = 0x14e;
    if (press == 0)
        press = 1;
    int i = 0;
    while (bossPresses()[i].encid != encounter)
        if (++i >= kBossPresses)
            return;
    const BossPress& boss = bossPresses()[i];
    if (!evt::BitCheck(boss.flag))
        return;
    globalWork().boss_records[i][1] = static_cast<int16_t>(press);
    if (bossPressRecord(encounter, 0) <= press)
        return;
    globalWork().boss_records[i][0] = static_cast<int16_t>(press);
    evt::BitOn(boss.flag2);
}

// datBossRashChk @ 0x00246038: an open refight of that encounter.
bool isBossRefight(int32_t encounter)
{
    for (int i = 0; i < kBossPresses; ++i)
        if (bossPresses()[i].encid == encounter && evt::BitCheck(bossPresses()[i].flag))
            return true;
    return false;
}

} // namespace nocturne::dat

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::dat {

#if NOCTURNE_HARDTYPE
// datGetItemSkillNo @ 0x00245C90 (and 0x2FDDF0): as US Maniax's, but an
// item with skill 0x89 gives its stand-in 0xDC, and notes the pair.
int32_t itemSkill(int32_t item)
{
    const int32_t* choices = guest::table<const int32_t>(0x00543170);
    if (item == 1)
        return choices[sdf::GetRandInt(6)];
    const uint16_t skill = dat::item(item).skillid;
    if (skill != 0x89)
        return skill;
    hardtype::actingSkill() = skill;
    hardtype::standInSkill() = 0xdc;
    return 0xdc;
}
#else
// datGetItemSkillNo @ 0x00245C90 (the six choices are the words at 0x543170)
int32_t itemSkill(int32_t item)
{
    const int32_t* choices = guest::table<const int32_t>(addr(0x00543170));
    if (item == 1)
        return choices[sdf::GetRandInt(6)];
    return dat::item(item).skillid;
}
#endif

} // namespace nocturne::dat
