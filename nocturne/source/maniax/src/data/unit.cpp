// Unit stats (original unit: datCalc): US Maniax's own (shared/src/data/unit.cpp has the rest).
#include "nocturne/data/unit.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/ee/double.hpp"

namespace nocturne::dat {

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

// datGetBaseMaxMp @ 0x00242AE8. The original computes 2 (Lv + Ma) x 1.5 in
// software double precision; the result is always the exact integer below.
int32_t baseMaxMp(const UnitWork& unit)
{
    int32_t value = (unit.level + param(unit, Param::Magic)) * 3;
    return !unit.isEnemy() && value > 999 ? 999 : value;
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

// datAddHp @ 0x00243E28
uint32_t addHp(UnitWork& unit, int32_t amount) { return addClamped(unit.hp, unit.maxhp, amount); }

} // namespace nocturne::dat
