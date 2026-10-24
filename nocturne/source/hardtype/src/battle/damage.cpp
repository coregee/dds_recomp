// Damage (original unit: nbCalc): Hardtype's own (shared/src/battle/damage.cpp has the rest).
#include "nocturne/battle/damage.hpp"

#include "nocturne/battle/buffs.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

using ee::Float;
using ee::literal;

// nbGetMaxHpWazaPoint @ 0x00268D60 (and 0x2FF240): an enemy's power is
// further x0.91015625 (0x3F690000). For the party's side it is no longer the
// user's max HP but 6 x (level + Strength), times how full its HP was before
// the hit, (HP + max HP) / (2 x max HP), or 1.59375 less that for skill
// 0x97. (The original tests its caller's s6 for 0x97 x 16: nbGetKoukaHp's
// skill x 16, as here.)
int32_t maxHpPower(int32_t skill, int32_t source, int32_t target, int32_t power)
{
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    Float attackBuff = buffMultiplier(source, BuffKind::Attack);
    Float defenseBuff = buffMultiplier(target, BuffKind::Defense);
    Float value;
    if (attacker.isEnemy()) {
        value = Float::fromInt(dat::baseMaxHp(attacker)) / literal(69.6) * Float::fromInt(power);
        value = value * literal(0.6) * Float::fromBits(0x3f690000);
        value = value - 50.0f / Float::fromInt(attacker.level + 10);
        if (!evt::BitCheck(EventBit::NormalDifficulty))
            value = value * literal(1.34);
    } else {
        const Float maxHp = Float::fromInt(attacker.maxhp);
        Float fullness = (Float::fromInt(hardtype::hpBeforeChange()) * 0.5f + maxHp * 0.5f) / maxHp;
        if (skill == 0x97)
            fullness = Float::fromBits(0x3fcc0000) - fullness;
        const Float scaled = fullness * Float::fromInt(power);
        const int32_t base = 6 * ((attacker.level & 0xff) + dat::baseParam(attacker, Param::Strength));
        value = Float::fromInt(base) * scaled / literal(69.6) * literal(0.8);
    }
    return (value * attackBuff * defenseBuff).toInt();
}

// nbGetMagicAttack @ 0x002688D0 (and 0x2FDD50, 0x2FE960):
//   base = (magicbase + 2 Lv power) / 210, capped at magiclimit, halved
//          (as unsigned) for power under 200
//   base + base/100 * 2.5 (Ma - (L/5 + 6)),  L = Lv up to 49, else 50
// then x0.8 in double precision. From level 50 a magicbase of 256 or more
// raises the cap by (Lv + 40) / 90. Levels above 100 aren't retried.
Float magicBase(const UnitWork& unit, const NormalSkill& skill, int32_t power)
{
    const uint32_t level = unit.level;
    int32_t cap = skill.magiclimit;
    if (power < 200)
        cap = static_cast<int32_t>(static_cast<uint32_t>(cap) >> 1);
    Float capValue = Float::fromInt(cap);
    uint32_t statLevel = level;
    if (level >= 50) {
        if (skill.magicbase >= 256)
            capValue = capValue * Float::fromInt(static_cast<int32_t>(level + 40)) / 90.0f;
        statLevel = 50;
    }
    Float value = (Float::fromInt(skill.magicbase) + Float::fromInt(static_cast<int32_t>(level * static_cast<uint32_t>(power) * 2))) /
                  210.0f;
    if (capValue < value)
        value = capValue;
    Float magic = Float::fromInt(dat::param(unit, Param::Magic));
    Float expected = Float::fromInt(static_cast<int32_t>(statLevel)) / 5.0f + 6.0f;
    Float adjustment = (magic - expected) * 2.5f;
    Float corrected = value + value / 100.0f * adjustment;
    return (ee::Double::fromFloat(corrected) * ee::Double::fromBits(0x3fe9999999999999)).toFloat();
}
bool magicRetriesHighLevels() { return false; }

// nbGetMagicKaifuku @ 0x00268C60 (and 0x2FEF20): a caster outside the global
// work (the enemies) heals (its level, as a signed byte, + 15) / 20 as much.
Float healPointsScale(const UnitWork& caster, Float points)
{
    if (guest::addressOf(&caster) >> 16 == 0x124)
        return points;
    const int32_t level = static_cast<int8_t>(caster.level & 0xff);
    return Float::fromInt(level + 15) * points / 20.0f;
}

// nbGetKoukaHp @ 0x00266350 (and 0x2FDEB0): skill -1's power doubles (once a
// count at 0x551190 reaches a threshold Hardtype reads at 0x2FDF80, where
// its code has a 0, so always).
int32_t hpPower(int32_t skill, int32_t power) { return skill == -1 ? power * 2 : power; }

// ... (and 0x2FEC40) power% of the HP is scaled by t7, the last affinity
// word nbGetAisyo left (hardtype.hpp), out of 10000, and can't kill: at
// most HP - 1.
int32_t hpPercentDamage(int32_t base, int32_t power)
{
    const uint32_t product = static_cast<uint32_t>(base) * hardtype::affinityRegister() * static_cast<uint32_t>(power);
    const int32_t amount = static_cast<int32_t>(product) / 10000;
    return amount < base ? amount : base - 1;
}

// nbGetKoukaBadDamage @ 0x00266D60 (and 0x2FE0A0, 0x2FDDD0, 0x2FEC00,
// 0x2FE6A0, 0x2FEE70): as US Maniax's, with these changes:
// - the normal attack of devil 0x156 in the enemy unit at 0x116CF80 inflicts
//   ailment 0x20; the fixed distribution is skill 0x1FF's (none);
// - skill 0x110 is blocked by Death resistance as 0x103 and 0x104 are;
// - the chance (badlevel) is halved for 0x400 and Death against the
//   Demi-fiend; for ailments 1 and 2 (and Stinger) it doubles with the
//   attacker's 0x174, is at most 100, and the target's 0x171 halves it
//   (quarters for Death); and it is shifted right by the flags of the last
//   affinity looked up (t7 >> 21, hardtype.hpp), but for Death with 0x171;
// - the luck of both decides with it, instead of the chance as a percent:
//     ((A - D) chance 5 / (4 (A + D) + 100) + chance + 1/2) x rate
// - a chance equal to the shift it took (by a register the shift reuses)
//   lands as surely as badlevel 255.
uint32_t rollAilmentInflict(Float ratio, int32_t skill, int32_t source, int32_t target, bool preview)
{
    MainProcessData& data = *GetMainProcessData();
    const NormalSkill& s = dat::normalSkill(skill);
    if (s.badtype != 1 && s.badtype != 3)
        return 0;
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    UnitWork& defender = *GetUnitWorkFromFormindex(target);

    uint32_t badstatus = s.badstatus;
    if (skill == 0 && guest::addressOf(&attacker) == 0x0116cf80 && attacker.id == 0x156)
        badstatus = 0x20;
    uint32_t bad = badstatus & 0x7fff;
    if (skill == 0x1ff) {
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
    if ((static_cast<uint32_t>(skill - 0x103) < 2 || skill == 0x110)
        && (affinity(-1, target, Attribute::Death).raw & (Affinity::Null | Affinity::Repel | Affinity::Drain))) {
        diag::print(diag::Message::CurseKillBlocked);
        return 0;
    }
    if (skill == 0x4f && !(defender.badstat & ailment::Poison)) {
        diag::print(diag::Message::PestilenceNoPoison);
        return 0;
    }

    uint32_t chance = s.badlevel;
    bool lands = chance == 255;
    if (!lands) {
        if ((bad & 0xc00) && guest::addressOf(&defender) == hardtype::kDemiFiend)
            chance >>= 1;
        uint32_t shift = hardtype::affinityRegister() >> 21;
        if (skill == skill::Stinger || (bad & 3)) {
            if ((bad & 1) && hardtype::hasSkill(attacker, 0x174))
                chance = static_cast<uint32_t>(static_cast<int32_t>(chance << 2) >> 1);
            const bool quarter = hardtype::hasSkill(defender, 0x171);
            if (static_cast<int32_t>(chance) >= 100)
                chance = 100;
            if (quarter) {
                if (bad == ailment::Dead)
                    shift = 2;
                else
                    chance >>= 1;
            }
        }
        chance >>= (shift & 31);
        lands = chance == shift;
    }
    if (!lands && preview)
        lands = true;
    if (!lands) {
        const Float base = Float::fromInt(static_cast<int32_t>(chance));
        const int32_t a = dat::param(attacker, Param::Luck), d = dat::param(defender, Param::Luck);
        Float threshold = Float::fromInt(a - d) * base * 5.0f / Float::fromInt(4 * d + 4 * a + 100) + base + 0.5f;
        threshold = threshold * rate;
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
        diag::print(diag::Message::AilmentChance, base.toInt(), percent.toInt(), limit, roll);
        lands = roll < limit;
    }
    if (!lands)
        return 0;
    return badStat(target) < bad ? bad : 0;
}

} // namespace nocturne::nb
