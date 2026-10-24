// Unit stats and state (original unit: datCalc). What differs by version is in
// source/<version>/src/data/unit.cpp.
#include "nocturne/data/unit.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/external.hpp"

namespace nocturne::dat {

namespace {

bool isAilment(const UnitWork& unit, Ailment ailment) { return unit.ailment() == static_cast<uint16_t>(ailment); }

} // namespace

uint32_t addClamped(uint16_t& current, uint16_t maximum, int32_t amount)
{
    int32_t next = static_cast<int32_t>(static_cast<uint32_t>(current) + static_cast<uint32_t>(amount));
    if (next < 0) next = 0;
    if (next > maximum) next = maximum;
    current = static_cast<uint16_t>(next);
    return static_cast<uint32_t>(next);
}

// datGetParam @ 0x00243EE0
int32_t param(const UnitWork& unit, Param stat)
{
    int32_t value = baseParam(unit, stat);
    if (isAilment(unit, Ailment::Fly) && stat != Param::Agility)
        value = 1;
    return value > 0 ? value : 1;
}

// datGetNormalAtkPow @ 0x00242B68
int32_t attackPower(const UnitWork& unit)
{
    int32_t power = (param(unit, Param::Strength) + unit.level) * 2;
    if (isAilment(unit, Ailment::Poison))
        power /= 2;
    return power;
}

// datGetDefPow @ 0x00242D18
int32_t defensePower(const UnitWork& unit)
{
    return (param(unit, Param::Vitality) + unit.level) * 2;
}

// datGetBaseMaxHp @ 0x00242A88: capped at 999 except for enemies.
int32_t baseMaxHp(const UnitWork& unit)
{
    int32_t value = (unit.level + param(unit, Param::Vitality)) * 6;
    return !unit.isEnemy() && value > 999 ? 999 : value;
}

// datGetMaxHp @ 0x00243C28: Life Bonus/Gain/Surge add 10/20/30% each,
// each rounded down separately.
uint32_t maxHp(const UnitWork& unit)
{
    uint32_t base = static_cast<uint32_t>(baseMaxHp(unit)), bonus = 0;
    if (hasSkill(unit, skill::LifeBonus)) bonus += base * 10 / 100;
    if (hasSkill(unit, skill::LifeGain))  bonus += base * 20 / 100;
    if (hasSkill(unit, skill::LifeSurge)) bonus += base * 30 / 100;
    uint32_t value = base + bonus;
    return !unit.isEnemy() && value > 999 ? 999 : value;
}

// datGetMaxMp @ 0x00243D28: Mana Bonus/Gain/Surge likewise.
uint32_t maxMp(const UnitWork& unit)
{
    uint32_t base = static_cast<uint32_t>(baseMaxMp(unit)), bonus = 0;
    if (hasSkill(unit, skill::ManaBonus)) bonus += base * 10 / 100;
    if (hasSkill(unit, skill::ManaGain))  bonus += base * 20 / 100;
    if (hasSkill(unit, skill::ManaSurge)) bonus += base * 30 / 100;
    uint32_t value = base + bonus;
    return !unit.isEnemy() && value > 999 ? 999 : value;
}

// datGetPlayerLevel @ 0x00244598
int32_t playerLevel()
{
    return globalWork().units[0].level;
}

// datGetRace @ 0x00244470
Race race(const UnitWork& unit)
{
    return unit.isPlayerCharacter() ? Race::None : devilFormat(unit.id).race;
}

// datGetAisyo @ 0x00243FE8
//
// Demons use their species' affinity row; the Demi-fiend uses row 0 (his
// battle affinities come from the Magatama via Party::aisyo instead).
// Petrified units always use the Stone row.
uint32_t affinity(const UnitWork& unit, Attribute attr)
{
    if (attr == Attribute::None)
        return 0;
    int32_t column = static_cast<int32_t>(attr);
    int32_t row = unit.isPlayerCharacter() ? 0 : devilFormat(unit.id).affinityId;
    uint32_t value = affinityRow(row)[column];
    if (isAilment(unit, Ailment::Stone))
        value = affinityRow(kStoneAffinityRow)[column];
    return value;
}

// datGet3Zokusei @ 0x00244E68
int32_t alignment(const UnitWork& unit)
{
    if (unit.isPlayerCharacter())
        return 0;
    uint32_t flags = devilFormat(unit.id).flag;
    if (flags & DevilFlag::AlignmentPlus) return 1;
    if (flags & DevilFlag::AlignmentMinus) return -1;
    return 0;
}

// datCheckSyojiSkill @ 0x00243F40
//
// Enemies use their species' eight skills; everyone else their own list.
bool hasSkill(const UnitWork& unit, int32_t skill)
{
    const uint16_t* skills = unit.skill;
    uint32_t count = unit.skillcnt;
    if (unit.isEnemy()) {
        skills = devilFormat(unit.id).skill;
        count = 8;
    }
    for (uint32_t i = 0; i < count; ++i)
        if (skills[i] == static_cast<uint32_t>(skill))
            return true;
    return false;
}

// datCheckSkillInParty @ 0x00245638: any active party member.
bool partyHasSkill(int32_t skill)
{
    for (const UnitWork& unit : globalWork().units) {
        if ((unit.flag & (UnitFlag::Valid | UnitFlag::InParty)) == (UnitFlag::Valid | UnitFlag::InParty)
            && hasSkill(unit, skill))
            return true;
    }
    return false;
}

// datSetBadStat @ 0x00243BD0
//
// Curse (0x8000) is a flag and always sticks. An ailment only replaces the
// current one if its value is higher: the value order is the priority.
void setAilment(UnitWork& unit, uint32_t badstat)
{
    if (badstat == kBadStatCurse)
        unit.badstat |= kBadStatCurse;
    else if (unit.ailment() < badstat)
        unit.badstat = static_cast<uint16_t>((unit.badstat & 0xf000) | (badstat & kAilmentMask));
}

// datResetBadStat @ 0x00243C10
void clearAilment(UnitWork& unit, uint32_t badstat)
{
    unit.badstat &= static_cast<uint16_t>(~badstat);
}

// datOverwriteBadStat @ 0x00243B98: like setAilment, without the priority check.
void overwriteAilment(UnitWork& unit, uint32_t badstat)
{
    if (badstat == kBadStatCurse)
        unit.badstat |= kBadStatCurse;
    else
        unit.badstat = static_cast<uint16_t>((unit.badstat & 0xf000) | (badstat & kAilmentMask));
}

// datGetBadStatusAttr @ 0x002440C0
Attribute ailmentElement(uint32_t badstat)
{
    switch (badstat) {
    case ailment::Shock:  return Attribute::Elec;
    case ailment::Freeze: return Attribute::Ice;
    case ailment::Sleep: case ailment::Panic: case ailment::Charm: return Attribute::Mind;
    case ailment::Bind: case ailment::Stun: return Attribute::Nerve;
    case ailment::Mute: case ailment::Poison: return Attribute::Curse;
    case ailment::Fly: case 0x1000: case 0x2000: case 0x4000: return Attribute::Almighty;
    case ailment::Stone: return Attribute::Death;
    default: return Attribute::None;
    }
}

// datAddMp @ 0x00243E50
uint32_t addMp(UnitWork& unit, int32_t amount) { return addClamped(unit.mp, unit.maxmp, amount); }

// datCheckDying @ 0x00244200
bool isDying(const UnitWork& unit)
{
    if (unit.maxhp == 0)
        divideByZeroTrap();
    return static_cast<uint32_t>(unit.hp) * 100 / unit.maxhp < 25;
}

} // namespace nocturne::dat
