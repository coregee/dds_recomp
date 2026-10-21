// Unit stats and state (original unit: datCalc).
#include "nocturne/data/unit.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/external.hpp"

namespace nocturne::dat {

namespace {

bool isAilment(const UnitWork& unit, Ailment ailment) { return unit.ailment() == static_cast<uint16_t>(ailment); }

uint32_t addClamped(uint16_t& current, uint16_t maximum, int32_t amount)
{
    int32_t next = static_cast<int32_t>(static_cast<uint32_t>(current) + static_cast<uint32_t>(amount));
    if (next < 0) next = 0;
    if (next > maximum) next = maximum;
    current = static_cast<uint16_t>(next);
    return static_cast<uint32_t>(next);
}

} // namespace

// datGetBaseParam @ 0x00243E78
int32_t baseParam(const UnitWork& unit, Param stat)
{
    int i = static_cast<int>(stat);
    int32_t value = unit.param[i] + unit.skillparam[i];
    if (!unit.isPlayerCharacter())   // the Demi-fiend has no Mitama bonus
        value += unit.mitamaparam[i];
    if (value < 1) value = 1;
    return value > 40 ? 40 : value;
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

// datGetMagicHitPow @ 0x00242CB0: 2 Ma + Lv + (Lu + 5) / 2 + 15
int32_t magicAccuracy(const UnitWork& unit)
{
    int32_t magic = param(unit, Param::Magic);
    int32_t luck = param(unit, Param::Luck) + 5;
    return magic * 2 + unit.level + luck / 2 + 15;
}

// datGetSakePow @ 0x00242D50: 1.5 (Ag + 5) + (Lu + 5) + (Lv + 5), in the
// game's software double precision.
int32_t evasionPower(const UnitWork& unit)
{
    int32_t agility = param(unit, Param::Agility);
    int32_t luck = param(unit, Param::Luck);
    ee::Double value = ee::Double::fromInt(agility + 5) * ee::Double::fromBits(0x3ff8000000000000);   // 1.5
    value = value + ee::Double::fromInt(luck + 5);
    value = value + ee::Double::fromInt(unit.level + 5);
    return value.toInt();
}

// datGetBaseMaxHp @ 0x00242A88: capped at 999 except for enemies.
int32_t baseMaxHp(const UnitWork& unit)
{
    int32_t value = (unit.level + param(unit, Param::Vitality)) * 6;
    return !unit.isEnemy() && value > 999 ? 999 : value;
}

// datGetBaseMaxMp @ 0x00242AE8. The original computes 2 (Lv + Ma) x 1.5 in
// software double precision; the result is always the exact integer below.
int32_t baseMaxMp(const UnitWork& unit)
{
    int32_t value = (unit.level + param(unit, Param::Magic)) * 3;
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
    int32_t row = unit.isPlayerCharacter() ? 0 : devilFormat(unit.id).aisyoid;
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

// datGetSkillCost @ 0x002459E8
//
// costtype 1: HP, cost% of max HP + costbase (at least 1); free for enemies
// and for species with DevilFlag::NoHpCost. costtype 2: MP, a fixed cost;
// free for species with DevilFlag::NoMpCost.
int32_t skillCost(const UnitWork& unit, int32_t skill)
{
    const NormalSkill& s = normalSkill(skill);
    if (s.costtype == 1) {
        if (!unit.isPlayerCharacter()) {
            if (devilFormat(unit.id).flag & DevilFlag::NoHpCost) return 0;
            if (unit.isEnemy()) return 0;
        }
        int32_t product = static_cast<int32_t>(static_cast<uint32_t>(unit.maxhp) * s.cost);
        int32_t cost = product / 100 + s.costbase;
        return cost > 0 ? cost : 1;
    }
    if (s.costtype == 2) {
        if (!unit.isPlayerCharacter() && (devilFormat(unit.id).flag & DevilFlag::NoMpCost))
            return 0;
        return s.cost;
    }
    return 0;
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

// datAddHp @ 0x00243E28
uint32_t addHp(UnitWork& unit, int32_t amount) { return addClamped(unit.hp, unit.maxhp, amount); }

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
