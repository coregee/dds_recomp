// Skills used outside battle, and the field's hazards to the party
// (original unit: datCalc). Rewritten from legacy/src/field_skill.c and the
// original instructions.
#include "nocturne/data/field_skill.hpp"

#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/external.hpp"

namespace nocturne::dat {

using ee::Double;
using ee::Float;
using ee::literal;

namespace {

bool isEnemy(const UnitWork& unit) { return (unit.flag & UnitFlag::Enemy) != 0; }

// The magic formula's double-precision factor (0.8 rounded toward zero).
const Double kMagicFactor = Double::fromBits(0x3fe9999999999999);

} // namespace

// GetButuriAttack @ 0x00242E00
//   (2 Lv + 2 St) x 1.33 (normal attack) or x power / 23.2 (skill), then
//   x 0.6 for enemies, which also lose 48 (50 for skills) / (Lv + 10);
//   x 0.8 for the player's side.
int32_t fieldPhysicalPower(int32_t skill, UnitWork& source, UnitWork& target, int32_t power)
{
    // The original also computes datGetNormalAtkPow(source) and
    // datGetDefPow(target) and discards both.
    (void)target;
    const Float strength = Float::fromInt(param(source, Param::Strength));
    const Float level = Float::fromInt(source.level);
    Float value = (level + level) + (strength + strength);
    value = skill == skill::NormalAttack ? value * literal(1.33) : value * Float::fromInt(power) / literal(23.2);
    if (isEnemy(source)) {
        const uint32_t penalty = (skill ? 50u : 48u) / (source.level + 10u);
        value = value * literal(0.6) - Float::fromInt(static_cast<int32_t>(penalty));
    } else {
        value = value * literal(0.8);
    }
    return value.toInt();
}

// GetButuriKaifuku @ 0x00242FE0: physical healing uses the same formula.
int32_t fieldPhysicalHealPower(int32_t skill, UnitWork& source, UnitWork& target, int32_t power)
{
    return fieldPhysicalPower(skill, source, target, power);
}

// GetMagicAttack @ 0x00242FF8
//   base = magicbase + 2 Lv power / 21, capped at magiclimit
//   (base + base/100 x 2.5 (Ma - (Lv/5 + 4))) x 0.8 in double precision;
//   enemies then x 0.75 - 50 / (Lv + 10).
// Unlike the battle formula, the level isn't capped at 160.
int32_t fieldMagicPower(int32_t skill, UnitWork& source, UnitWork& /*target*/, int32_t power)
{
    const NormalSkill& s = normalSkill(skill);
    const uint32_t product = static_cast<uint32_t>(source.level) * static_cast<uint32_t>(power);
    Float value = Float::fromInt(s.magicbase) + Float::fromInt(static_cast<int32_t>(product << 1)) / 21.0f;
    const Float cap = Float::fromInt(s.magiclimit);
    if (cap < value)
        value = cap;
    const Float magic = Float::fromInt(param(source, Param::Magic));
    const Float expected = Float::fromInt(source.level) / 5.0f + 4.0f;
    const Float corrected = value + value / 100.0f * ((magic - expected) * 2.5f);
    value = (Double::fromFloat(corrected) * kMagicFactor).toFloat();
    if (isEnemy(source))
        value = value * 0.75f - 50.0f / Float::fromInt(source.level + 10);
    return value.toInt();
}

// GetMagicKaifuku @ 0x00243170: (4 Ma + Lv + rand(8)) / 10 x power.
int32_t fieldMagicHealPower(int32_t /*skill*/, UnitWork& source, UnitWork& /*target*/, int32_t power)
{
    const uint32_t magic = static_cast<uint32_t>(param(source, Param::Magic));
    const uint32_t roll = static_cast<uint32_t>(sdf::GetRandInt(8));
    const uint32_t points = (magic << 2) + source.level + roll;
    return (Float::fromInt(static_cast<int32_t>(points)) / 10.0f * Float::fromInt(power)).toInt();
}

// GetMaxHpWazaPoint @ 0x00243200: max HP / 69.6 x power; enemies use their
// base max HP, x 0.6 - 50 / (Lv + 10).
int32_t fieldMaxHpPower(int32_t /*skill*/, UnitWork& source, UnitWork& /*target*/, int32_t power)
{
    if (!isEnemy(source))
        return (Float::fromInt(source.maxhp) / literal(69.6) * Float::fromInt(power)).toInt();
    Float value = Float::fromInt(baseMaxHp(source)) / literal(69.6) * Float::fromInt(power) * literal(0.6);
    return (value - 50.0f / Float::fromInt(source.level + 10)).toInt();
}

// GetAisyoRitu @ 0x002432D0: the target's damage rate for the skill's
// element as a fraction; 1 for no element and for elements 12..14.
Float fieldAffinityRate(int32_t skill, UnitWork& /*source*/, UnitWork& target)
{
    const int32_t attr = skillInfo(skill).skillattr;
    if (attr == -1 || (attr >= 12 && attr < 15))
        return 1.0f;
    const uint32_t rate = affinity(target, static_cast<Attribute>(attr)) & 0xffff;
    return Float::fromInt(static_cast<int32_t>(rate)) * literal(0.01);
}

// datGetSkillKouka @ 0x00243368
// The amount by the skill's hptype / mptype (as in battle, see
// battle/damage.cpp), then a +-5% spread and the affinity for damage from
// power, the affinity for healing from power. Quirks kept: the spread and
// affinity step always follows hptype, even for MP; type 0 returns 0 at
// once; damage is never 0; and when neither damage nor healing was set
// (hptype 3 that doesn't lower anything, or an unused type) the result is 1.
int32_t fieldSkillEffect(int32_t skill, int32_t type, UnitWork& source, UnitWork& target)
{
    const Float rate = fieldAffinityRate(skill, source, target);
    const NormalSkill& s = normalSkill(skill);
    int32_t current = 0, maximum = 0, power = 0, offset = 0;
    uint32_t mode = 0;
    if (type == 0) {
        maximum = target.maxhp;
        current = target.hp;
        mode = s.hptype;
        power = s.hpn;
        offset = s.hpbase;
    } else if (type == 1) {
        maximum = target.maxmp;
        current = target.mp;
        offset = s.mpbase;
        mode = s.mptype;
        power = s.mpn;
    }
    auto add = [](int32_t a, int32_t b) { return static_cast<int32_t>(static_cast<uint32_t>(a) + static_cast<uint32_t>(b)); };
    auto percent = [&](int32_t of) {
        return add(static_cast<int32_t>(static_cast<uint32_t>(of) * static_cast<uint32_t>(power)) / 100, offset);
    };

    int32_t healing = -1, damage = -1;
    switch (mode) {
    case 0:
        return 0;
    case 1: case 12: case 14: {   // damage from power
        int32_t amount = 0;
        if (s.koukatype == 0) {
            amount = fieldPhysicalPower(skill, source, target, power);
            const uint16_t ailment = source.badstat & kAilmentMask;
            if (ailment == ailment::Poison || ailment == ailment::Fly)
                amount /= 2;
        } else if (s.koukatype == 1) {
            amount = fieldMagicPower(skill, source, target, power);
        }
        damage = add(amount, offset);
        break;
    }
    case 2: {                     // healing from power
        int32_t amount = 0;
        if (s.koukatype == 0)
            amount = fieldPhysicalHealPower(skill, source, target, power);
        else if (s.koukatype == 1)
            amount = fieldMagicHealPower(skill, source, target, power);
        healing = add(amount, offset);
        break;
    }
    case 3:                       // down to power + offset
        if (add(power, offset) < current)
            damage = current - add(power, offset);
        break;
    case 4: case 13: damage = add(power, offset); break;
    case 5: healing = add(power, offset); break;
    case 6: damage = add(fieldMaxHpPower(skill, source, target, power), offset); break;
    case 7: healing = add(fieldMaxHpPower(skill, source, target, power), offset); break;
    case 8: damage = percent(current); break;
    case 10: damage = percent(maximum); break;
    case 9: case 11:
        healing = percent(mode == 9 ? current : maximum);
        if (healing <= 0)
            healing = 1;
        break;
    case 15: healing = add(sdf::GetRandInt(power), offset); break;
    default: break;
    }

    switch (s.hptype) {
    case 1: case 6: case 12:      // damage from power: spread, then affinity
        if (damage > 0) {
            Float jitter = sdf::GetRandFloat() - 0.5f;
            jitter = (jitter + jitter) * literal(0.05);
            const Float value = Float::fromInt(damage);
            damage = (value + value * jitter).toInt();
            if (damage < 0)
                damage = 0;
            damage = (Float::fromInt(damage) * rate).toInt();
        }
        break;
    case 2: case 7:               // healing from power: affinity
        if (healing > 0)
            healing = (Float::fromInt(healing) * rate).toInt();
        break;
    default: break;
    }
    if (damage == 0)
        damage = 1;
    return healing < 0 ? static_cast<int32_t>(0u - static_cast<uint32_t>(damage)) : healing;
}

// datGetSkillBadKouka @ 0x00243760
// badtype 3 picks one of the skill's ailments at random; badtype 1 (inflict)
// scales the chance by the target's affinity to the ailment's element and
// only replaces a lesser ailment. Enemies' chances are x0.7.
uint32_t fieldSkillAilment(int32_t skill, UnitWork& source, UnitWork& target)
{
    const NormalSkill& s = normalSkill(skill);
    uint32_t status = s.badstatus & kAilmentMask;
    if (s.badtype == 3) {
        uint32_t bits[12] = {};
        int32_t count = 0;
        for (uint32_t bit = 0; bit < 12; ++bit)
            if (status & (1u << bit))
                bits[count++] = bit;
        status = 1u << (bits[sdf::GetRandInt(count)] & 31);
    }
    Float resistance = 1.0f;
    if (s.badtype == 1) {
        const uint32_t aff = affinity(target, ailmentElement(status));
        resistance = 0.0f;
        if (!(aff & 0x00170000))   // not Null / Repel / Drain / 0x100000
            resistance = Float::fromInt(static_cast<int32_t>(aff & 0xffff)) / 100.0f;
    }
    if (s.badlevel != 0xff) {
        Float chance = Float::fromInt(s.badlevel) / 100.0f * resistance * 100.0f;
        if (isEnemy(source))
            chance = chance * literal(0.7);
        if (sdf::GetRandInt(100) >= chance.toInt())
            return 0;
    }
    if (s.badtype == 1 && !(static_cast<uint32_t>(target.badstat & kAilmentMask) < status))
        return 0;
    return status;
}

// datExecSkill @ 0x00243998
// HP, MP and ailment on the target (a unit brought to 0 HP dies); skills
// with program 8..11 also set a bit of the global work (whether or not
// there was a source and target).
int32_t useFieldSkill(int32_t skill, UnitWork* source, UnitWork* target)
{
    const NormalSkill& s = normalSkill(skill);
    if (source && target) {
        const int32_t hp = fieldSkillEffect(skill, 0, *source, *target);
        const int32_t mp = fieldSkillEffect(skill, 1, *source, *target);
        const uint32_t status = fieldSkillAilment(skill, *source, *target);
        if (!hp && !mp && !status)
            return 0;
        if (status) {
            if (s.badtype == 1 || s.badtype == 3)
                setAilment(*target, status);
            else
                clearAilment(*target, status);
        }
        if (mp)
            addMp(*target, mp);
        if (hp) {
            addHp(*target, hp);
            if (!target->hp)
                setAilment(*target, ailment::Dead);
        }
    }
    const int32_t program = static_cast<int32_t>(s.program);
    if (program >= 8 && program <= 11)
        globalWork().fieldskills |= 1u << (program - 8);
    return 1;
}

// ===========================================================================
// The party on the field
// ===========================================================================

namespace {

bool hurtable(const UnitWork& unit) { return (unit.flag & UnitFlag::InParty) && unit.hp; }

// Damage that leaves at least 1 HP; triple on Hard.
void hurt(UnitWork& unit, uint32_t damage)
{
    const uint32_t hp = unit.hp;
    if (!evt::BitCheck(EventBit::NormalDifficulty))
        damage *= 3;
    if (!damage)
        damage = 1;
    const int32_t remaining = static_cast<int32_t>(hp - damage);
    unit.hp = static_cast<uint16_t>(remaining > 0 ? remaining : 1);
}

// The same without the difficulty.
void hurtPlainly(UnitWork& unit, uint32_t damage)
{
    if (!damage)
        damage = 1;
    const int32_t remaining = static_cast<int32_t>(unit.hp - damage);
    unit.hp = static_cast<uint16_t>(remaining > 0 ? remaining : 1);
}

uint32_t threePercent(uint32_t hp) { return (hp * 3) / 100; }

} // namespace

// datPartyDamage @ 0x002447C0
void partyDamage(int32_t mode)
{
    UnitWork* units = globalWork().units;
    if (mode == 1 || mode == 4 || mode == 5 || mode == 6)
        for (int i = 0; i < 16; ++i)
            if (hurtable(units[i]))
                hurt(units[i], units[i].hp / 10u);
    if (mode == 2)
        for (int i = 0; i < 16; ++i)
            if (hurtable(units[i]))
                hurt(units[i], units[i].hp >> 1);
    if (mode == 3)
        for (int i = 0; i < 16; ++i)
            if (units[i].id != devil::Dante && hurtable(units[i]))
                units[i].hp = 1;
    if (mode >= 4 && mode <= 6) {
        const uint16_t inflicted = mode == 4 ? ailment::Poison : mode == 5 ? ailment::Stun : ailment::Mute;
        for (int i = 0; i < 16; ++i)
            if (hurtable(units[i]))
                setAilment(units[i], inflicted);
    }
}

// datPartyDamageFld @ 0x00244A38
void partyFieldDamage(int32_t mode)
{
    UnitWork* units = globalWork().units;
    for (int i = 0; i < 16; ++i) {
        UnitWork& unit = units[i];
        if (!hurtable(unit))
            continue;
        switch (mode) {
        case 1:
            if (unit.badstat & ailment::Poison)
                hurt(unit, threePercent(unit.hp));
            break;
        case 2: hurt(unit, threePercent(unit.hp)); break;
        case 3: {
            const uint32_t roll = static_cast<uint32_t>(sdf::GetRandInt(2));
            hurtPlainly(unit, unit.hp * (roll + 1) / 100u);
            break;
        }
        case 4: hurtPlainly(unit, unit.hp >> 1u); break;
        default: break;
        }
    }
}

// datPartyDamagePipe @ 0x00244CC0
void partyPipeDamage(int32_t big, int32_t small)
{
    if (!big && !small)
        return;
    for (UnitWork& unit : globalWork().units) {
        if (!hurtable(unit))
            continue;
        const uint32_t tenth = unit.hp / 10u, three = threePercent(unit.hp);
        hurt(unit, tenth * static_cast<uint32_t>(big) + three * static_cast<uint32_t>(small));
    }
}

// datPartyKaifuku @ 0x00244DD8: every unit in the stock.
void partyRecover()
{
    for (UnitWork& unit : globalWork().units) {
        if (!(unit.flag & UnitFlag::Valid))
            continue;
        addHp(unit, 9999);
        addMp(unit, 9999);
        unit.badstat = 0;
    }
}

} // namespace nocturne::dat
