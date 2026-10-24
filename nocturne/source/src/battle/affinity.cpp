// Affinity in battle (original unit: nbCalc).
#include "nocturne/battle/affinity.hpp"

#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

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

// nbGetAisyo @ 0x00267890
Affinity affinity(int32_t skill, int32_t formindex, Attribute attr)
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

    // Passive skills. The Void/Anti families cover all elements but
    // Almighty, so from Expel on their IDs are one lower; Drain/Repel cover
    // Physical..Force only.
    int32_t rate = static_cast<int32_t>(packed & 0xffff);
    if (attr < Attribute(11) && attr != Attribute::Almighty) {
        int32_t a = column;
        int32_t familyOffset = a < 5 ? a : a - 1;
        if (passiveActive(unit, skill::VoidPhys + familyOffset))
            packed |= Affinity::Null;
        if (a < 5) {
            if (passiveActive(unit, skill::PhysDrain + a)) packed |= Affinity::Drain;
            if (passiveActive(unit, skill::PhysRepel + a)) packed |= Affinity::Repel;
        }
        int32_t anti = skill::AntiPhys + familyOffset;
        if (passiveActive(unit, anti))
            rate = dat::specialSkill(anti).n * rate / 100;   // Anti-X: n = 50
    }
    return Affinity{(packed & 0xffff0000u) | static_cast<uint32_t>(rate & 0xffff)};
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
        if (dat::hasSkill(attacker, skill::Pierce) && physical && rate < 100) {
            rate = 100;
            data.piercedResistance = 1;
        }
        ratio = Float::fromInt(rate) * ee::literal(0.01);
    }

    // Son's Oath boosts everything; Fire/Ice/Elec/Force Boost their element.
    bool boost = dat::hasSkill(attacker, skill::SonsOath);
    if (!boost && attr >= Attribute::Fire && attr <= Attribute::Force)
        boost = passiveActive(attacker, skill::FireBoost - 1 + static_cast<int32_t>(attr));
    return boost ? ratio * 1.5f : ratio;
}

} // namespace nocturne::nb
