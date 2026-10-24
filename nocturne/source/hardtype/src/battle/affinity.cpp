// Affinities (original unit: nbCalc): Hardtype's own (shared/src/battle/affinity.cpp has the rest).
#include "nocturne/battle/affinity.hpp"

#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

namespace {

// Hardtype's own passives.
constexpr int32_t kAntiElements = 0x16b;   // Fire, Ice, Elec, Force: as the element's Anti-X
constexpr int32_t kAntiMind = 0x16d;       // Curse, Nerve, Mind: as the element's Anti-X
constexpr int32_t kVoidMind = 0x16f;       // Curse, Nerve, Mind: Null
constexpr int32_t kQuarter = 0x171;        // Expel..Mind: a quarter
constexpr int32_t kFireMight = 0x173;      // Fire boosted (x1.5 for the normal attack)
constexpr int32_t kElecBoost = 0x174;      // Elec boosted
constexpr int32_t kAllBoost = 0x177;       // Ice, Elec, Force boosted (and Fire without 0x173)
const ee::Float kBoost = ee::Float::fromBits(0x3fa70000);   // 1.3046875

} // namespace

// nbGetAisyo @ 0x00267890 (and 0x2FEC60, 0x2FEBE0, 0x2FDDA0): US Maniax's
// families, with Hardtype's own passives beside them. A rate under 100%
// also clears the weakness bit and scales the whole affinity word, so the
// flags' bits spill into the rate (0x10000 x 50% is 0x8000).
uint32_t passiveAffinity(const UnitWork& unit, int32_t element, uint32_t packed)
{
    auto has = [&](int32_t s) { return passiveActive(unit, s); };
    const int32_t familyOffset = element < 5 ? element : element - 1;
    if (has(skill::VoidPhys + familyOffset) || (element >= 8 && has(kVoidMind)))
        packed |= Affinity::Null;
    if (element < 5) {
        if (has(skill::PhysDrain + element)) packed |= Affinity::Drain;
        if (has(skill::PhysRepel + element)) packed |= Affinity::Repel;
    }
    const int32_t anti = skill::AntiPhys + familyOffset;
    int32_t n = -1;   // no rate
    if (element < 5) {
        if (has(anti) || (element >= 1 && has(kAntiElements)))
            n = dat::specialSkill(anti).n;
    } else if (element < 8) {
        if (has(kQuarter))
            n = 25;
        else if (has(anti))
            n = dat::specialSkill(anti).n;
    } else {
        if (has(anti))
            n = dat::specialSkill(anti).n;
        else if (has(kQuarter))
            n = 25;
        else if (has(kAntiMind))
            n = dat::specialSkill(anti).n;
    }
    if (n < 0)
        return packed;
    uint32_t rate = packed & 0xffff;
    if (n < 100) {
        packed &= 0x7fffffffu;
        rate = packed;
    }
    rate = static_cast<uint32_t>(static_cast<int32_t>(rate * static_cast<uint32_t>(n)) / 100);
    return (packed & 0xffff0000u) | rate;
}

// nbGetAisyoRitu @ 0x00266130 (and 0x2FE140): Pierce or Son's Oath, for
// skills of the elements up to Almighty (SkillInfo's, 0..5). (Its check
// for skill 0xA1 tests drain and repel bits in a rate already masked to its
// low half, and does nothing.)
bool piercesResistance(const UnitWork& attacker, int32_t skill)
{
    if (!dat::hasSkill(attacker, skill::Pierce) && !dat::hasSkill(attacker, skill::SonsOath))
        return false;
    return static_cast<uint8_t>(dat::skillInfo(skill).skillattr) < 6;
}

// ... (and 0x2FE600, 0x2FE630, 0x2FE660) boosts are x1.3046875: Son's Oath
// for everything; Fire by 0x173 (x1.5 for the normal attack), else Fire
// Boost or 0x177; Ice, Force their Boost or 0x177; Elec its Boost, or 0x174
// or 0x177.
ee::Float boostedRatio(const UnitWork& attacker, int32_t skill, Attribute attr, ee::Float ratio)
{
    auto has = [&](int32_t s) { return passiveActive(attacker, s); };
    if (dat::hasSkill(attacker, skill::SonsOath))
        return ratio * kBoost;
    const int32_t boost = skill::FireBoost - 1 + static_cast<int32_t>(attr);
    switch (attr) {
    case Attribute::Fire:
        if (has(kFireMight))
            return ratio * (skill == 0 ? ee::Float::fromBits(0x3fc00000) : kBoost);
        return has(boost) || has(kAllBoost) ? ratio * kBoost : ratio;
    case Attribute::Elec:
        if (has(boost))
            return ratio * kBoost;
        return has(kElecBoost) || has(kAllBoost) ? ratio * kBoost : ratio;
    case Attribute::Ice:
    case Attribute::Force:
        return has(boost) || has(kAllBoost) ? ratio * kBoost : ratio;
    default:
        return ratio;
    }
}

// nbGetAisyo @ 0x00267890: the result is also left in t7 (hardtype.hpp).
Affinity noteAffinity(Affinity result)
{
    hardtype::affinityRegister() = result.raw;
    return result;
}

} // namespace nocturne::nb
