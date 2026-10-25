// Affinity in battle (original unit: nbCalc).
#include "nocturne/battle/affinity.hpp"

#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/build.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

using ee::Float;

namespace {

bool isNonElemental(Attribute attr) { return attr >= Attribute(12) && attr <= Attribute(15); }

// Temporary null counter for an element, if there is one.
int32_t nullCounterFor(Attribute attr)
{
    switch (attr) {
    case Attribute::Fire:  return static_cast<int32_t>(BuffKind::NullFire);
    case Attribute::Ice:   return static_cast<int32_t>(BuffKind::NullIce);
    case Attribute::Expel: return static_cast<int32_t>(BuffKind::NullExpel);
    case Attribute::Death: return static_cast<int32_t>(BuffKind::NullDeath);
    default:               return -1;
    }
}

} // namespace

namespace {

// The body of nbGetAisyo (affinity, below).
Affinity computeAffinity(int32_t skill, int32_t formindex, Attribute attr)
{
    UnitWork* unitPointer = GetUnitWorkFromFormindex(formindex);
    if (formindex >= 16)
        return Affinity{dat::affinity(*unitPointer, attr)};

    Party& party = *GetPartyFromFormindex(formindex);
    if (attr == Attribute::None)
        return Affinity{0};
    if (isNonElemental(attr))
        return Affinity{100};

    UnitWork& unit = *unitPointer;
    int32_t column = static_cast<int32_t>(attr);
    uint32_t packed = party.affinities[column];
    int32_t row = buffCounter(formindex, static_cast<int32_t>(BuffKind::AffinityRow));
    if (row > 0)
        packed = dat::affinityRow(row)[column];
    if (unit.ailment() == ailment::Fly)
        packed = dat::affinityRow(dat::kFlyAffinityRow)[column];
    else if (unit.ailment() == ailment::Stone)
        packed = dat::affinityRow(dat::kStoneAffinityRow)[column];

    int32_t nullCounter = nullCounterFor(attr);
    if (nullCounter >= 0 && buffCounter(formindex, nullCounter) > 0)
        packed |= Affinity::Null;

    // Tetrakarn / Makarakarn reflect physical / magic skills of any element
    // except Almighty.
    if (skill >= 0 && attr != Attribute::Almighty && attr != Attribute(11)) {
        uint8_t kind = dat::normalSkill(skill).damageClass;
        if (kind < 2) {
            BuffKind karn = kind == 1 ? BuffKind::RepelMagic : BuffKind::RepelPhysical;
            if (buffCounter(formindex, static_cast<int32_t>(karn)) > 0)
                packed |= Affinity::Repel;
        }
    }

    if (attr >= Attribute(11) || attr == Attribute::Almighty)
        return Affinity{packed};
    return Affinity{passiveAffinity(unit, column, packed)};
}

} // namespace

// nbGetAisyo @ 0x00267890
Affinity affinity(int32_t skill, int32_t formindex, Attribute attr)
{
    return noteAffinity(computeAffinity(skill, formindex, attr));
}

// nbGetVirtualAisyo @ 0x00268EB8 (source unused)
uint32_t virtualAffinity(int32_t skill, int32_t /*source*/, int32_t target)
{
    Attribute attr = skillAttribute(skill);
    if (attr == Attribute::None || (attr >= Attribute(12) && attr <= Attribute(14)))
        return 0;
    Affinity a = affinity(skill, target, attr);
    if (a.has(Affinity::Repel)) return Affinity::Repel;
    if (a.has(Affinity::Drain)) return Affinity::Drain;
    if (a.has(Affinity::Null))  return Affinity::Null;
    return 0;
}

// nbGetAisyoTable @ 0x002677E8
int32_t affinityRowOf(int32_t formindex)
{
    UnitWork& unit = *GetUnitWorkFromFormindex(formindex);
    int32_t row = unit.isPlayerCharacter() ? 0 : dat::devilFormat(unit.id).affinityId;
    int32_t override = buffCounter(formindex, static_cast<int32_t>(BuffKind::AffinityRow));
    if (override > 0)
        row = override;
    if (unit.ailment() == ailment::Fly)   return dat::kFlyAffinityRow;
    if (unit.ailment() == ailment::Stone) return dat::kStoneAffinityRow;
    return row;
}

// nbGetAisyoRitu @ 0x00266130
//
// Repel/Drain entries with no rate count as 100%. Against a frozen target,
// or with Pierce, physical skills ignore resistance (rate < 100 -> 100);
// Pierce also flags the battle so the result shows it.
Float damageRatio(int32_t skill, int32_t source, int32_t target)
{
    MainProcessData& data = *GetMainProcessData();
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    UnitWork& defender = *GetUnitWorkFromFormindex(target);
    Attribute attr = skillAttribute(skill);
    const NormalSkill& s = dat::normalSkill(skill);

    Float ratio = 1.0f;
    if (attr != Attribute::None && !(attr >= Attribute(12) && attr <= Attribute(14))) {
        Affinity a = affinity(skill, target, attr);
        int32_t rate = a.ratePercent();
        if ((a.raw & (Affinity::Repel | Affinity::Drain)) && rate == 0)
            rate = 100;
        bool physical = s.damageClass == 0;
        if (defender.ailment() == ailment::Freeze && physical && rate < 100)
            rate = 100;
        if (piercesResistance(attacker, skill) && rate < 100) {
            rate = 100;
            data.piercedResistance = 1;
        }
        ratio = Float::fromInt(rate) * ee::literal(0.01);
    }
    return boostedRatio(attacker, skill, attr, ratio);
}

} // namespace nocturne::nb

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::nb {

#if NOCTURNE_HARDTYPE
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
#endif

#if NOCTURNE_HARDTYPE
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
#else
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
#endif

#if NOCTURNE_HARDTYPE
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
#elif NOCTURNE_CHRONICLE
// nbGetAisyoRitu @ 0x00266130 (Chronicle 0x265228): Pierce or, here, Son's Oath,
// for physical skills.
bool piercesResistance(const UnitWork& attacker, int32_t skill)
{
    return (dat::hasSkill(attacker, skill::Pierce) || dat::hasSkill(attacker, skill::SonsOath)) &&
           dat::normalSkill(skill).damageClass == 0;
}
#else
// nbGetAisyoRitu @ 0x00266130: Pierce, for physical skills.
bool piercesResistance(const UnitWork& attacker, int32_t skill)
{
    return dat::hasSkill(attacker, skill::Pierce) && dat::normalSkill(skill).damageClass == 0;
}
#endif

#if NOCTURNE_HARDTYPE
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
#else
// ... Son's Oath boosts everything x1.5; Fire/Ice/Elec/Force Boost their element.
ee::Float boostedRatio(const UnitWork& attacker, int32_t, Attribute attr, ee::Float ratio)
{
    bool boost = dat::hasSkill(attacker, skill::SonsOath);
    if (!boost && attr >= Attribute::Fire && attr <= Attribute::Force)
        boost = passiveActive(attacker, skill::FireBoost - 1 + static_cast<int32_t>(attr));
    return boost ? ratio * 1.5f : ratio;
}
#endif

#if NOCTURNE_HARDTYPE
// nbGetAisyo @ 0x00267890: the result is also left in t7 (hardtype.hpp).
Affinity noteAffinity(Affinity result)
{
    hardtype::affinityRegister() = result.raw;
    return result;
}
#else
// nbGetAisyo @ 0x00267890: nothing kept.
Affinity noteAffinity(Affinity result) { return result; }
#endif

} // namespace nocturne::nb
