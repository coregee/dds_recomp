// The save game's party and the Demi-fiend's progress (original unit: datCalc).
#include "nocturne/data/progression.hpp"

#include <cstring>

#include "nocturne/data/ids.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/growth.hpp"
#include "nocturne/guest.hpp"

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
    fcl::EncycRegist(unit, false);
}

// ===========================================================================
// The Demi-fiend
// ===========================================================================

// datGetPlayerParam @ 0x002445C0
int32_t playerParam(Param stat)
{
    int32_t index = static_cast<int32_t>(stat);
    int32_t value = player().param[index];
    if (uint8_t magatama = globalWork().hearts_equipped)
        value -= cmb::GetHeartsParam(static_cast<int8_t>(magatama), static_cast<int8_t>(index));
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
    uint8_t race = cmb::GetPlayerRaceID(player());
    return race ? (race - 1) % 3 : 1;
}

// datAddMakaPar @ 0x00244268: change Macca by a percentage (32-bit math).
void addMaccaPercent(int32_t percent)
{
    GlobalWork& global = globalWork();
    uint32_t macca = static_cast<uint32_t>(global.maka);
    uint32_t magnitude = percent < 0 ? 0u - static_cast<uint32_t>(percent) : static_cast<uint32_t>(percent);
    uint32_t change = static_cast<uint32_t>(eeDivide(wrappingMultiply(static_cast<int32_t>(macca), static_cast<int32_t>(magnitude)), 100));
    uint32_t result = percent < 0 ? macca - change : macca + change;
    if (result & 0x80000000u)
        result = 0;
    if (result > 9999999u)
        result = 9999999u;
    global.maka = static_cast<int32_t>(result);
}

// datRemoveHearts @ 0x00245380 (an empty hook at 0x221558 followed the
// parameter change)
void removeMagatama()
{
    GlobalWork& global = globalWork();
    if (!global.hearts_owned_count)
        return;
    cmb::SubHeartsParam(global.hearts_equipped, player());
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
    cmb::HeartsAddParam(global.hearts_equipped, player());
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
        fcl::EncycRegist(unit, false);
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
    int32_t requiredEvent = *guest::table<const int32_t>(0x003dc920);
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

} // namespace nocturne::dat
