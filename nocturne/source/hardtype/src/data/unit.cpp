// Unit stats (original unit: datCalc): Hardtype's own (shared/src/data/unit.cpp has the rest).
#include "nocturne/data/unit.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::dat {

// datGetBaseParam @ 0x00243E78 (and 0x2FF320): a demon's Mitama bonus is at
// most a quarter of its own stat, and the cap of 40 holds only for the units
// found at or above 0x1200000 (the global work's party and stock): the
// battle's enemies, lower in memory, may pass it.
int32_t baseParam(const UnitWork& unit, Param stat)
{
    int i = static_cast<int>(stat);
    if (unit.isPlayerCharacter()) {
        int32_t value = unit.param[i] + unit.skillparam[i];
        if (value < 1) value = 1;
        return value > 40 ? 40 : value;
    }
    const int32_t own = static_cast<uint8_t>(unit.param[i]);
    const int32_t mitama = unit.mitamaparam[i] < own >> 2 ? unit.mitamaparam[i] : own >> 2;
    int32_t value = unit.skillparam[i] + own + mitama;
    if (value <= 0)
        value = 1;
    const uint32_t at = guest::addressOf(&unit.param[i]);
    if (static_cast<int32_t>(((at >> 16) - 0x120) << 16) < 0)
        return value;
    return value > 40 ? 40 : value;
}

// datGetMagicHitPow @ 0x00242CB0 (and 0x2FE7D0): 2 Lu + (Ag + bit 1 of the
// moon move bits) / 2 + 39.
int32_t magicAccuracy(const UnitWork& unit)
{
    const int32_t luck = param(unit, Param::Luck);
    const int32_t agility = param(unit, Param::Agility) + ((hardtype::byteAt(hardtype::kMoonMoveBits) >> 1) & 1);
    return luck * 2 + agility / 2 + 39;
}

// datGetSakePow @ 0x00242D50 (and 0x2FE800): 1.5 (Lu + 5) + (Ag + 5) + 25
// (+1 with bit 1 of the moon move bits), in the game's software double
// precision; the level left out.
int32_t evasionPower(const UnitWork& unit)
{
    const int32_t luck = param(unit, Param::Luck);
    const int32_t agility = param(unit, Param::Agility);
    const int32_t moon = (hardtype::byteAt(hardtype::kMoonMoveBits) >> 1) & 1;
    ee::Double value = ee::Double::fromInt(luck + 5) * ee::Double::fromBits(0x3ff8000000000000);   // 1.5
    value = value + ee::Double::fromInt(agility + 5);
    value = value + ee::Double::fromInt(20 + moon + 5);
    return value.toInt();
}

// datGetBaseMaxMp @ 0x00242AE8 (and 0x2FEE40): (Lv + Ma) x 3, and the
// party's (not the enemies') 4/3 of that before the cap.
int32_t baseMaxMp(const UnitWork& unit)
{
    int32_t value = (unit.level + param(unit, Param::Magic)) * 3;
    if (unit.isEnemy())
        return value;
    value = value * 4 / 3;
    return value > 999 ? 999 : value;
}

// datGetSkillCost @ 0x002459E8 (and 0x2FE200), as US Maniax's but skill
// 0x179 halves an HP cost.
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
        if (hardtype::hasSkill(unit, 0x179))
            cost = static_cast<int32_t>(static_cast<uint32_t>(cost) >> 1);
        return cost > 0 ? cost : 1;
    }
    if (s.costtype == 2) {
        if (!unit.isPlayerCharacter() && (devilFormat(unit.id).flag & DevilFlag::NoMpCost))
            return 0;
        return s.cost;
    }
    return 0;
}

// datAddHp @ 0x00243E28 (and 0x2FE1C0): the HP it starts from noted.
uint32_t addHp(UnitWork& unit, int32_t amount)
{
    hardtype::hpBeforeChange() = unit.hp;
    return addClamped(unit.hp, unit.maxhp, amount);
}

} // namespace nocturne::dat
