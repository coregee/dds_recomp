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
