// Damage (original unit: nbCalc): US Maniax's own (shared/src/battle/damage.cpp has the rest).
#include "nocturne/battle/damage.hpp"

#include "nocturne/battle/buffs.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

using ee::Float;
using ee::literal;

// nbGetMaxHpWazaPoint @ 0x00268D60: skills based on the user's max HP.
int32_t maxHpPower(int32_t /*skill*/, int32_t source, int32_t target, int32_t power)
{
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    Float attackBuff = buffMultiplier(source, BuffKind::Attack);
    Float defenseBuff = buffMultiplier(target, BuffKind::Defense);
    Float value;
    if (attacker.isEnemy()) {
        value = Float::fromInt(dat::baseMaxHp(attacker)) / literal(69.6) * Float::fromInt(power);
        value = value * literal(0.6);
        value = value - 50.0f / Float::fromInt(attacker.level + 10);
        if (!evt::BitCheck(EventBit::NormalDifficulty))
            value = value * literal(1.34);
    } else {
        value = Float::fromInt(attacker.maxhp) / literal(69.6) * Float::fromInt(power) * literal(0.8);
    }
    return (value * attackBuff * defenseBuff).toInt();
}

// nbGetMagicAttack @ 0x002688D0: the magic formula before buffs:
//   base = magicbase + 2 Lv power / 21, capped at magiclimit
//   base + base/100 * 2.5 (Ma - (min(Lv, 160)/5 + 4))
// then x0.8 in double precision; levels above 100 are retried.
Float magicBase(const UnitWork& unit, const NormalSkill& skill, int32_t power)
{
    uint32_t level = unit.level;
    Float value = Float::fromInt(skill.magicbase)
                + Float::fromInt(static_cast<int32_t>(level * static_cast<uint32_t>(power) * 2)) / 21.0f;
    Float cap = Float::fromInt(skill.magiclimit);
    if (cap < value)
        value = cap;
    Float magic = Float::fromInt(dat::param(unit, Param::Magic));
    Float expected = Float::fromInt(static_cast<int32_t>(level > 160 ? 160 : level)) / 5.0f + 4.0f;
    Float adjustment = (magic - expected) * 2.5f;
    Float corrected = value + value / 100.0f * adjustment;
    return (ee::Double::fromFloat(corrected) * ee::Double::fromBits(0x3fe9999999999999)).toFloat();
}
bool magicRetriesHighLevels() { return true; }

// nbGetMagicKaifuku @ 0x00268C60: the points as they are.
Float healPointsScale(const UnitWork&, Float points) { return points; }

// nbGetKoukaHp @ 0x00266350: the skill's power; power% of the HP.
int32_t hpPower(int32_t, int32_t power) { return power; }
int32_t hpPercentDamage(int32_t base, int32_t power) { return base * power / 100; }

// nbGetKoukaBadDamage @ 0x00266D60
//
// badtype 1: the skill's ailment; 3: one of the ailments in its mask, at
// random. Blocked by Null/Repel/Drain on the ailment's element. Chance =
// badlevel% x affinity rate (Death ailments use the damage ratio), then
// against the player's side: x0.7 on Normal (x0.5 for instant death on the
// Demi-fiend), and for instant death on Hard x1.5 (x1.3 on the Demi-fiend).
// The ailment only lands if it outranks the target's current one.
uint32_t rollAilmentInflict(Float ratio, int32_t skill, [[maybe_unused]] int32_t source, int32_t target, bool preview)
{   // (the original looks up the source unit and never uses it)
    MainProcessData& data = *GetMainProcessData();
    const NormalSkill& s = dat::normalSkill(skill);
    if (s.badtype != 1 && s.badtype != 3)
        return 0;
    UnitWork& defender = *GetUnitWorkFromFormindex(target);

    uint32_t bad = s.badstatus & 0x7fff;
    if (skill == 0x110) {
        // Fixed distribution: 0x1000 40%, 0x2000 20%, 0x4000 10%,
        // Mute 10%, Stun 10%, Poison 10%.
        uint32_t roll = static_cast<uint32_t>(sdf::GetRandInt(100));
        bad = roll < 40 ? 0x1000 : roll < 60 ? 0x2000 : roll < 70 ? 0x4000
            : roll < 80 ? ailment::Mute : roll < 90 ? ailment::Stun : ailment::Poison;
    } else if (s.badtype == 3) {
        uint32_t choices[14], count = 0;
        for (uint32_t bit = 0; bit < 14; ++bit)
            if (bad & (1u << bit))
                choices[count++] = bit;
        bad = 1u << choices[sdf::GetRandInt(static_cast<int32_t>(count))];
    }

    Affinity resist = affinity(skill, target, dat::ailmentElement(bad));
    if (resist.raw & (Affinity::Null | Affinity::Repel | Affinity::Drain | Affinity::Unknown100000))
        return 0;
    Float rate = bad == ailment::Dead ? ratio : Float::fromInt(resist.ratePercent()) / 100.0f;

    if (skill == skill::Stinger && (data.stat & BattleStat::BossBattle) && defender.isEnemy()) {
        diag::print(diag::Message::StingerVsBoss);
        return 0;
    }
    if (static_cast<uint32_t>(skill - 0x103) < 2
        && (affinity(-1, target, Attribute::Death).raw & (Affinity::Null | Affinity::Repel | Affinity::Drain))) {
        diag::print(diag::Message::CurseKillBlocked);
        return 0;
    }
    if (skill == 0x4f && !(defender.badstat & ailment::Poison)) {
        diag::print(diag::Message::PestilenceNoPoison);
        return 0;
    }

    if (s.badlevel != 255 && !preview) {
        Float chance = Float::fromInt(s.badlevel);
        Float threshold = chance / 100.0f * rate * 100.0f;
        bool normal = evt::BitCheck(EventBit::NormalDifficulty);
        if (!defender.isEnemy()) {
            if (normal) {
                if (bad == ailment::Dead)
                    threshold = threshold * (defender.isPlayerCharacter() ? Float(0.5f) : literal(0.7));
                else
                    threshold = threshold * literal(0.7);
            } else if (bad == ailment::Dead) {
                threshold = threshold * (defender.isPlayerCharacter() ? literal(1.3) : Float(1.5f));
            }
        }
        int32_t roll = sdf::GetRandInt(100);
        int32_t limit = threshold.toInt();
        Float percent = rate * 100.0f;
        diag::print(diag::Message::AilmentChance, chance.toInt(), percent.toInt(), limit, roll);
        if (roll >= limit)
            return 0;
    }
    return badStat(target) < bad ? bad : 0;
}

} // namespace nocturne::nb
