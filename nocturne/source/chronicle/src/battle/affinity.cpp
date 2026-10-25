// Affinities (original unit: nbCalc): the JP Chronicle Edition's own
// (shared/src/battle/affinity.cpp has the rest).
#include "nocturne/battle/affinity.hpp"

#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"

namespace nocturne::nb {

// nbGetAisyo @ 0x00267890: the Void / Anti families cover all elements but
// Almighty, so from Expel on their IDs are one lower; Drain / Repel cover
// Physical..Force only. Anti-X scales the rate (n = 50).
uint32_t passiveAffinity(const UnitWork& unit, int32_t element, uint32_t packed)
{
    int32_t rate = static_cast<int32_t>(packed & 0xffff);
    const int32_t familyOffset = element < 5 ? element : element - 1;
    if (passiveActive(unit, skill::VoidPhys + familyOffset))
        packed |= Affinity::Null;
    if (element < 5) {
        if (passiveActive(unit, skill::PhysDrain + element)) packed |= Affinity::Drain;
        if (passiveActive(unit, skill::PhysRepel + element)) packed |= Affinity::Repel;
    }
    const int32_t anti = skill::AntiPhys + familyOffset;
    if (passiveActive(unit, anti))
        rate = dat::specialSkill(anti).n * rate / 100;
    return (packed & 0xffff0000u) | static_cast<uint32_t>(rate & 0xffff);
}

// nbGetAisyoRitu @ 0x00266130 (Chronicle 0x265228): Pierce or, here, Son's Oath,
// for physical skills.
bool piercesResistance(const UnitWork& attacker, int32_t skill)
{
    return (dat::hasSkill(attacker, skill::Pierce) || dat::hasSkill(attacker, skill::SonsOath)) &&
           dat::normalSkill(skill).damageClass == 0;
}

// ... Son's Oath boosts everything x1.5; Fire/Ice/Elec/Force Boost their element.
ee::Float boostedRatio(const UnitWork& attacker, int32_t, Attribute attr, ee::Float ratio)
{
    bool boost = dat::hasSkill(attacker, skill::SonsOath);
    if (!boost && attr >= Attribute::Fire && attr <= Attribute::Force)
        boost = passiveActive(attacker, skill::FireBoost - 1 + static_cast<int32_t>(attr));
    return boost ? ratio * 1.5f : ratio;
}

// nbGetAisyo @ 0x00267890: nothing kept.
Affinity noteAffinity(Affinity result) { return result; }

} // namespace nocturne::nb
