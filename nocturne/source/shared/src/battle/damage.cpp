// Damage, healing and ailment effects (original unit: nbCalc).
//
// Rewritten from legacy/src/battle_power.c and battle_effects.c.
#include "nocturne/battle/damage.hpp"

#include <initializer_list>

#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/external.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/build.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

using ee::Double;
using ee::Float;
using ee::literal;

namespace {

bool isNormalDifficulty() { return evt::BitCheck(EventBit::NormalDifficulty); }

bool hasAilment(const UnitWork& unit, uint16_t ailment) { return unit.ailment() == ailment; }

// Magic scaling factor, a double constant (0.8 rounded toward zero).

void printRatios(Float attackBuff, Float defenseBuff)
{
    diag::print(diag::Message::AttackRatio, static_cast<int64_t>(Double::fromFloat(attackBuff).bits()));
    diag::print(diag::Message::DefenseRatio, static_cast<int64_t>(Double::fromFloat(defenseBuff).bits()));
}

// Poisoned attackers do half physical damage; flies a tenth.
int32_t weakenPhysical(const UnitWork& attacker, int32_t amount)
{
    if (hasAilment(attacker, ailment::Poison)) return amount / 2;
    if (hasAilment(attacker, ailment::Fly))    return amount / 10;
    return amount;
}

} // namespace

// ===========================================================================
// Power
// ===========================================================================

// nbGetButuriAttack @ 0x00268620
//
//   value = 2 Lv + 2 St
//   normal attack: x 1.33 x k        skill: x power / 23.2 x k
// with k = 0.8 for the player's side and 0.6 for enemies. Enemies also lose
// 48/(Lv+10) (50 for skills) and gain x1.34 on Hard.
int32_t physicalPower(int32_t skill, int32_t source, int32_t target, int32_t power)
{
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    Float attackBuff = buffMultiplier(source, BuffKind::Attack);
    Float defenseBuff = buffMultiplier(target, BuffKind::Defense);
    // The original also computes datGetNormalAtkPow(attacker) and
    // datGetDefPow(defender) here, and discards both.

    Float strength = Float::fromInt(dat::param(attacker, Param::Strength));
    Float level = Float::fromInt(attacker.level);
    Float value = (level + level) + (strength + strength);
    if (attacker.isEnemy()) {
        uint32_t levelPenalty = (skill ? 50u : 48u) / (attacker.level + 10u);
        if (skill == skill::NormalAttack)
            value = value * literal(1.33) * literal(0.6);
        else
            value = value * Float::fromInt(power) / literal(23.2) * literal(0.6);
        value = value - Float::fromInt(static_cast<int32_t>(levelPenalty));
        if (!isNormalDifficulty())
            value = value * literal(1.34);
    } else if (skill == skill::NormalAttack) {
        value = value * literal(1.33) * literal(0.8);
    } else {
        value = value * Float::fromInt(power) / literal(23.2) * literal(0.8);
    }
    printRatios(attackBuff, defenseBuff);
    return (value * attackBuff * defenseBuff).toInt();
}

// nbGetButuriKaifuku @ 0x002688B8: physical healing uses the same formula.
int32_t physicalHealPower(int32_t skill, int32_t source, int32_t target, int32_t power)
{
    return physicalPower(skill, source, target, power);
}

// nbGetMagicAttack @ 0x002688D0
//
// Enemies: x0.75 - 50/(Lv+10), and x1.34 on Hard.
int32_t magicPower(int32_t skill, int32_t source, int32_t target, int32_t power)
{
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    Float magicBuff = buffMultiplier(source, BuffKind::Magic);
    Float defenseBuff = buffMultiplier(target, BuffKind::Defense);
    const NormalSkill& s = dat::normalSkill(skill);

    Float value = magicBase(attacker, s, power);
    // Player units above level 100 (unreachable in normal play): the
    // original loops once per level above 100, but every pass computes the
    // same value from the current level, so one comparison is equivalent.
    if (magicRetriesHighLevels() && !attacker.isEnemy() && attacker.level > 100) {
        Float candidate = magicBase(attacker, s, power);
        if (value < candidate)
            value = candidate;
    }
    if (attacker.isEnemy()) {
        value = value * 0.75f - 50.0f / Float::fromInt(attacker.level + 10);
        if (!isNormalDifficulty())
            value = value * literal(1.34);
    }
    printRatios(magicBuff, defenseBuff);
    return (value * magicBuff * defenseBuff).toInt();
}

// nbGetMagicKaifuku @ 0x00268C60: (4 Ma + Lv + rand(8)) / 10 x power x Magic buff.
int32_t magicHealPower(int32_t /*skill*/, int32_t source, int32_t /*target*/, int32_t power)
{
    UnitWork& caster = *GetUnitWorkFromFormindex(source);
    Float magicBuff = buffMultiplier(source, BuffKind::Magic);
    int32_t magic = dat::param(caster, Param::Magic);
    int32_t roll = sdf::GetRandInt(8);
    int32_t points = magic * 4 + caster.level + roll;
    Float value = healPointsScale(caster, Float::fromInt(points) / 10.0f) * Float::fromInt(power);
    value = value * magicBuff;
    int32_t amount = value.toInt();
    diag::print(diag::Message::MagicHeal, power, static_cast<int64_t>(Double::fromFloat(magicBuff).bits()), amount);
    return amount;
}

// ===========================================================================
// HP / MP effect
// ===========================================================================

namespace {

// hptype / mptype values (NormalSkill). The amounts use hpn/mpn ("power")
// and hpbase/mpbase ("offset").
//   0       none
//   1, 12   damage from the attacker's power (12: drain, capped at max HP)
//   2       heal from the caster's power
//   3       reduce to power + offset (e.g. Evil Gaze: to 1)
//   4, 13   fixed damage
//   5       fixed heal
//   6, 7    damage / heal from the user's max HP
//   8, 10   damage: power% of current / max
//   9, 11   heal: power% of current / max
//   14      damage split between `count` targets
//   15      heal rand(power)
int32_t effectAmount(bool mp, Float ratio, bool damage, int32_t skill, int32_t source, int32_t target, int32_t count)
{
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    UnitWork& defender = *GetUnitWorkFromFormindex(target);
    const NormalSkill& s = dat::normalSkill(skill);
    uint32_t type = mp ? s.mptype : s.hptype;
    int32_t power = mp ? s.mpn : hpPower(skill, s.hpn);
    int32_t offset = mp ? s.mpbase : s.hpbase;
    int32_t current = mp ? defender.mp : defender.hp;
    int32_t maximum = mp ? defender.maxmp : defender.maxhp;

    int32_t harm = -1, heal = -1;
    switch (type) {
    case 0:
        break;
    case 2:
        heal = offset;
        if (s.damageClass == 0)      heal = physicalHealPower(skill, source, target, power) + offset;
        else if (s.damageClass == 1) heal = magicHealPower(skill, source, target, power) + offset;
        break;
    case 3:
        if (power + offset < current)
            harm = current - (power + offset);
        break;
    case 4: case 13:
        harm = power + offset;
        break;
    case 5:
        heal = power + offset;
        break;
    case 6: case 7: {
        int32_t amount = maxHpPower(skill, source, target, power);
        if (type == 7) {
            heal = amount + offset;
            break;
        }
        if (!mp)
            amount = weakenPhysical(attacker, amount);
        harm = amount + offset;
        break;
    }
    case 8: case 10: {
        const int32_t base = type == 8 ? current : maximum;
        harm = (mp ? base * power / 100 : hpPercentDamage(base, power)) + offset;
        break;
    }
    case 9: case 11:
        heal = (type == 9 ? current : maximum) * power / 100 + offset;
        if (!mp && heal <= 0)
            heal = 1;
        break;
    case 15:
        heal = sdf::GetRandInt(power) + offset;
        break;
    default: {   // 1, 12, 14
        if (type >= 16)
            break;
        int32_t amount = 0;
        if (s.damageClass == 0) {
            amount = physicalPower(skill, source, target, power);
            if (!mp)
                amount = weakenPhysical(attacker, amount);
        } else if (s.damageClass == 1) {
            amount = magicPower(skill, source, target, power);
        }
        harm = amount + offset;
        if (type == 14 && count > 1)
            harm /= count;
        break;
    }
    }

    // Damage from power: random spread, affinity, and Normal-mode mercy.
    bool fromPower = type == 1 || type == 2 || type == 6 || type == 7 || type == 12 || type == 14;
    if (fromPower && harm > 0) {
        if (s.damageClass == 0 || s.damageClass == 1) {
            // +-5% (physical, MP) or +-10% (magic) spread.
            Float spread = mp ? literal(0.05) : (s.damageClass ? literal(0.1) : literal(0.05));
            Float jitter = sdf::GetRandFloat() - 0.5f;
            jitter = (jitter + jitter) * spread;
            Float value = Float::fromInt(harm);
            harm = (value + value * jitter).toInt();
        }
        if (harm < 0)
            harm = 0;
        harm = (Float::fromInt(harm) * ratio).toInt();
        if (isNormalDifficulty() && !isPlayerSide(source))
            harm = (Float::fromInt(harm) * literal(0.7)).toInt();   // Normal: enemies do 70%
    }

    if (!mp && harm == 0)
        harm = 1;   // HP damage is never 0
    if (!damage)
        return heal;
    if (mp) {
        if (current < harm) harm = current;     // can't drain more MP than there is
    } else if (type == 12 || type == 13) {
        if (maximum < harm) harm = maximum;
    }
    return harm;
}

} // namespace

// nbGetKoukaHp @ 0x00266350
int32_t hpEffect(Float ratio, bool damage, int32_t skill, int32_t source, int32_t target, int32_t count)
{
    return effectAmount(false, ratio, damage, skill, source, target, count);
}

// nbGetKoukaMp @ 0x00266878
int32_t mpEffect(Float ratio, bool damage, int32_t skill, int32_t source, int32_t target, int32_t count)
{
    return effectAmount(true, ratio, damage, skill, source, target, count);
}

// nbGetVirtualKoukaPoint @ 0x00268F68
int32_t estimateEffect(int32_t skill, int32_t source, int32_t target)
{
    UnitWork& unit = *GetUnitWorkFromFormindex(target);
    Float ratio = damageRatio(skill, source, target);
    uint32_t inflicts = rollAilmentInflict(ratio, skill, source, target, true);
    uint32_t cures = rollAilmentCure(ratio, skill, source, target, true);

    int32_t hpDamage = hpEffect(ratio, true, skill, source, target, 1);
    int32_t hpHeal = hpEffect(ratio, false, skill, source, target, 1);
    if (hpHeal > 0) {
        int32_t missing = unit.maxhp - unit.hp;
        if (missing < hpHeal) hpHeal = missing;
    }
    int32_t mpDamage = mpEffect(ratio, true, skill, source, target, 1);
    int32_t mpHeal = mpEffect(ratio, false, skill, source, target, 1);
    if (mpHeal > 0) {
        int32_t missing = unit.maxmp - unit.mp;
        if (missing < mpHeal) mpHeal = missing;
    }

    const NormalSkill& s = dat::normalSkill(skill);
    int32_t buffChange = s.buffKinds ? applyBuffs(target, s.buffKinds, s.buffAmount, true) : 0;

    // Amounts of 0 or 1 don't count: 1 is the minimum "chip" damage.
    int32_t score = (inflicts != 0) + (cures != 0);
    for (int32_t amount : {hpDamage, hpHeal, mpDamage, mpHeal})
        if (amount >= 2)
            score += amount;
    return score + buffChange;
}

// ===========================================================================
// Ailments
// ===========================================================================

// nbGetKoukaBadKaifuku @ 0x00267180
//
// Chance = badlevel% x (caster Ma + Lu/4) / (target Ma + Lu/4) x ratio.
uint32_t rollAilmentCure(Float ratio, int32_t skill, int32_t source, int32_t target, bool preview)
{
    const NormalSkill& s = dat::normalSkill(skill);
    if (s.badtype != 2)
        return 0;
    UnitWork& caster = *GetUnitWorkFromFormindex(source);
    UnitWork& patient = *GetUnitWorkFromFormindex(target);
    uint32_t cures = s.badstatus & kAilmentMask;

    if (s.badlevel != 255 && !preview) {
        Float chance = Float::fromInt(s.badlevel);
        int32_t casterMagic = dat::param(caster, Param::Magic);
        int32_t casterLuck = dat::param(caster, Param::Luck);
        chance = chance * Float::fromInt(casterMagic + casterLuck / 4);
        int32_t patientMagic = dat::param(patient, Param::Magic);
        int32_t patientLuck = dat::param(patient, Param::Luck);
        int32_t resistance = patientMagic + patientLuck / 4;
        chance = chance / 100.0f;
        Float scaled = ratio * 100.0f;
        scaled = scaled / Float::fromInt(resistance);
        chance = chance * scaled;
        diag::print(diag::Message::AilmentCureRate, static_cast<int64_t>(Double::fromFloat(chance).bits()));
        if (sdf::GetRandInt(100) >= chance.toInt())
            return 0;
    }
    return (cures & patient.ailment()) ? cures : 0;
}

} // namespace nocturne::nb

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::nb {

using ee::Float;

using ee::literal;

#if NOCTURNE_HARDTYPE
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
#else
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
#endif

#if NOCTURNE_HARDTYPE
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
#else
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
#endif

#if NOCTURNE_HARDTYPE
bool magicRetriesHighLevels() { return false; }
#else
bool magicRetriesHighLevels() { return true; }
#endif

#if NOCTURNE_HARDTYPE
// nbGetMagicKaifuku @ 0x00268C60 (and 0x2FEF20): a caster outside the global
// work (the enemies) heals (its level, as a signed byte, + 15) / 20 as much.
Float healPointsScale(const UnitWork& caster, Float points)
{
    if (guest::addressOf(&caster) >> 16 == 0x124)
        return points;
    const int32_t level = static_cast<int8_t>(caster.level & 0xff);
    return Float::fromInt(level + 15) * points / 20.0f;
}
#else
// nbGetMagicKaifuku @ 0x00268C60: the points as they are.
Float healPointsScale(const UnitWork&, Float points) { return points; }
#endif

#if NOCTURNE_HARDTYPE
// nbGetKoukaHp @ 0x00266350 (and 0x2FDEB0): skill -1's power doubles (once a
// count at 0x551190 reaches a threshold Hardtype reads at 0x2FDF80, where
// its code has a 0, so always).
int32_t hpPower(int32_t skill, int32_t power) { return skill == -1 ? power * 2 : power; }
#else
// nbGetKoukaHp @ 0x00266350: the skill's power; power% of the HP.
int32_t hpPower(int32_t, int32_t power) { return power; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FEC40) power% of the HP is scaled by t7, the last affinity
// word nbGetAisyo left (hardtype.hpp), out of 10000, and can't kill: at
// most HP - 1.
int32_t hpPercentDamage(int32_t base, int32_t power)
{
    const uint32_t product = static_cast<uint32_t>(base) * hardtype::affinityRegister() * static_cast<uint32_t>(power);
    const int32_t amount = static_cast<int32_t>(product) / 10000;
    return amount < base ? amount : base - 1;
}
#else
int32_t hpPercentDamage(int32_t base, int32_t power) { return base * power / 100; }
#endif

#if NOCTURNE_HARDTYPE
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
#else
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
#endif

} // namespace nocturne::nb
