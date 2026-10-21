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

namespace nocturne::nb {

using ee::Double;
using ee::Float;
using ee::literal;

namespace {

bool isNormalDifficulty() { return evt::BitCheck(EventBit::NormalDifficulty); }

bool hasAilment(const UnitWork& unit, uint16_t ailment) { return unit.ailment() == ailment; }

// Magic scaling factor, a double constant (0.8 rounded toward zero).
const Double kMagicFactor = Double::fromBits(0x3fe9999999999999);

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

// The magic formula before buffs:
//   base = magicbase + 2 Lv power / 21, capped at magiclimit
//   base + base/100 * 2.5 (Ma - (min(Lv, 160)/5 + 4))
// then x0.8 in double precision.
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
    return (Double::fromFloat(corrected) * kMagicFactor).toFloat();
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
    Float attackBuff = buffMultiplier(source, Hojo::Attack);
    Float defenseBuff = buffMultiplier(target, Hojo::Defense);
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
    Float magicBuff = buffMultiplier(source, Hojo::Magic);
    Float defenseBuff = buffMultiplier(target, Hojo::Defense);
    const NormalSkill& s = dat::normalSkill(skill);

    Float value = magicBase(attacker, s, power);
    // Player units above level 100 (unreachable in normal play): the
    // original loops once per level above 100, but every pass computes the
    // same value from the current level, so one comparison is equivalent.
    if (!attacker.isEnemy() && attacker.level > 100) {
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
    Float magicBuff = buffMultiplier(source, Hojo::Magic);
    int32_t magic = dat::param(caster, Param::Magic);
    int32_t roll = sdf::GetRandInt(8);
    int32_t points = magic * 4 + caster.level + roll;
    Float value = Float::fromInt(points) / 10.0f * Float::fromInt(power);
    value = value * magicBuff;
    int32_t amount = value.toInt();
    diag::print(diag::Message::MagicHeal, power, static_cast<int64_t>(Double::fromFloat(magicBuff).bits()), amount);
    return amount;
}

// nbGetMaxHpWazaPoint @ 0x00268D60: skills based on the user's max HP.
int32_t maxHpPower(int32_t /*skill*/, int32_t source, int32_t target, int32_t power)
{
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    Float attackBuff = buffMultiplier(source, Hojo::Attack);
    Float defenseBuff = buffMultiplier(target, Hojo::Defense);
    Float value;
    if (attacker.isEnemy()) {
        value = Float::fromInt(dat::baseMaxHp(attacker)) / literal(69.6) * Float::fromInt(power);
        value = value * literal(0.6);
        value = value - 50.0f / Float::fromInt(attacker.level + 10);
        if (!isNormalDifficulty())
            value = value * literal(1.34);
    } else {
        value = Float::fromInt(attacker.maxhp) / literal(69.6) * Float::fromInt(power) * literal(0.8);
    }
    return (value * attackBuff * defenseBuff).toInt();
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
    int32_t power = mp ? s.mpn : s.hpn;
    int32_t offset = mp ? s.mpbase : s.hpbase;
    int32_t current = mp ? defender.mp : defender.hp;
    int32_t maximum = mp ? defender.maxmp : defender.maxhp;

    int32_t harm = -1, heal = -1;
    switch (type) {
    case 0:
        break;
    case 2:
        heal = offset;
        if (s.koukatype == 0)      heal = physicalHealPower(skill, source, target, power) + offset;
        else if (s.koukatype == 1) heal = magicHealPower(skill, source, target, power) + offset;
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
    case 8: case 10:
        harm = (type == 8 ? current : maximum) * power / 100 + offset;
        break;
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
        if (s.koukatype == 0) {
            amount = physicalPower(skill, source, target, power);
            if (!mp)
                amount = weakenPhysical(attacker, amount);
        } else if (s.koukatype == 1) {
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
        if (s.koukatype == 0 || s.koukatype == 1) {
            // +-5% (physical, MP) or +-10% (magic) spread.
            Float spread = mp ? literal(0.05) : (s.koukatype ? literal(0.1) : literal(0.05));
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
    int32_t buffChange = s.hojotype ? applyBuffs(target, s.hojotype, s.hojopoint, true) : 0;

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
        bool normal = isNormalDifficulty();
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
