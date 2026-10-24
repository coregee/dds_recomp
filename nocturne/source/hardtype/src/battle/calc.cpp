// Battle calculations (original unit: nbCalc): Hardtype's own (shared/src/battle/calc.cpp has the rest).
#include "nocturne/battle/calc.hpp"

#include <cstdlib>

#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/hardtype.hpp"

#include "nocturne/guest.hpp"

namespace nocturne::nb {

using ee::Float;

namespace {

constexpr uint32_t kModelOf = 0x002fe8e0;   // uint8_t by devil ID, used for 0xE0..0xFE

} // namespace

// 0x00259A60 (unnamed, and 0x2FE560): devils 0xE0..0xFE borrow another's
// model record: 0xE0..0xE5 those of Momunofu, Metatron, Beelzebub (Fly),
// Lucifer, Ose and Shikigami (0x3C, 0x9C, 0x9D, 0x9E, 0x6B, 0x3D); the rest
// record 0.
int32_t visualModel(int32_t id)
{
    if (id < 0xe0 || id >= 0xff)
        return id;
    return *guest::table<uint8_t>(kModelOf + static_cast<uint32_t>(id));
}

// nbCheckEscape @ 0x00269E98: attempts and the stat ratio weigh 15; the
// chance doubles on Normal only, and Hard rolls it too.
int32_t escapeWeight() { return 15; }
bool escapeDifficulty(int32_t& chance, bool normal)
{
    if (normal)
        chance *= 2;
    return true;
}

// nbGetMakaBaramaki @ 0x0026A4B0: the party's side scatters 1/50 of its Macca.
ee::Float maccaShareDivisor() { return ee::Float::fromInt(50); }

// nbGetHitType @ 0x002654B8 (and 0x2FE190, 0x2FF2F0)
//
// As US Maniax's, but:
// - Bright Might and Dark Might no longer crit outright: they are noted, and
//   then count as Might at n/60 (Might itself n/100);
// - the chance compares 2 Lu + Ag (attacker) with Lu + 2 Ag (defender):
//     criticalpoint + (A - D) 2 criticalpoint / ((A + D) 2 + 100)
//   times the multiplier, + 1/2 (a multiplier of 100 or more crits outright);
// - the noted passive is cleared unless Might crits. (A crit with Might over a noted
//   passive returns past restoring its caller's s0, leaving the threshold
//   there; its one caller, SetAllPacket, sets s0 before reading it.)
HitType rollCritical(ActionProcessData& action, int32_t skill, int32_t source, int32_t target)
{
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    UnitWork& defender = *GetUnitWorkFromFormindex(target);

    Attribute attr = skillAttribute(skill);
    if (attr == Attribute::None || (attr >= Attribute(12) && attr <= Attribute(15)))
        return HitType::Normal;
    Affinity targetAffinity = affinity(skill, target, attr);

    if (skill == skill::NormalAttack) {
        if (passiveActive(attacker, skill::BrightMight))
            action.autoskill = skill::BrightMight;
        else if (passiveActive(attacker, skill::DarkMight))
            action.autoskill = skill::DarkMight;
    }

    if (targetAffinity.has(Affinity::Weak))
        return HitType::Weakness;
    if (GetPartyFromFormindex(source)->flag & PartyFlag::AlwaysCrit)
        return HitType::Critical;

    Float multiplier = 1.0f;
    switch (static_cast<Ailment>(defender.ailment())) {
    case Ailment::Shock: case Ailment::Freeze: multiplier = 100.0f; break;
    case Ailment::Sleep: case Ailment::Bind:   multiplier = 8.0f;   break;
    default: break;
    }
    if ((action.data->form[target].stat & FormationStat::Unknown2000) && !evt::BitCheck(EventBit::NormalDifficulty))
        multiplier = 100.0f;

    bool mightFired = false;
    if (skill == skill::NormalAttack) {
        int32_t per = 0;
        if (passiveActive(attacker, skill::Might))
            per = 100;
        else if (action.autoskill != 0)
            per = 60;
        if (per != 0) {
            mightFired = true;
            multiplier = multiplier * (Float::fromInt(dat::specialSkill(skill::Might).n) / Float::fromInt(per));
        }
    }

    const NormalSkill& s = dat::normalSkill(skill);
    if (s.damageClass != 0)
        return HitType::Normal;

    const int32_t a = 2 * dat::param(attacker, Param::Luck) + dat::param(attacker, Param::Agility);
    const int32_t d = 2 * dat::param(defender, Param::Agility) + dat::param(defender, Param::Luck);
    const Float point = Float::fromInt(s.criticalpoint);
    Float chance = Float::fromInt((a - d) * 2) * point / Float::fromInt((a + d) * 2 + 100) + point;
    chance = chance * multiplier + 0.5f;
    int32_t threshold = multiplier.toInt();
    if (threshold < 100)
        threshold = chance.toInt();
    diag::print(diag::Message::Critical, s.criticalpoint, 100, threshold);

    if (sdf::GetRandInt(100) >= threshold) {
        action.autoskill = 0;
        return HitType::Normal;
    }
    if (!mightFired)
        action.autoskill = 0;
    else if (action.autoskill == 0)
        action.autoskill = skill::Might;
    return HitType::Critical;
}

// nbGetKoukaType @ 0x00265948 (and 0x2FE140, 0x2FE2B0): skill 0xA1 meets
// Repel and Drain as Null. Pierce or Son's Oath work for the elements up to
// Almighty (SkillInfo's 0..5): Physical through Null and Drain, the others
// through Null only.
bool affinityOutcome(int32_t skill, const NormalSkill&, const UnitWork& attacker, Affinity affinity, MainProcessData& data,
                     EffectResult& outcome)
{
    if (skill == 0xa1 && (affinity.raw & (Affinity::Repel | Affinity::Drain)))
        affinity.raw = Affinity::Null;
    const bool pierce = dat::hasSkill(attacker, skill::Pierce) || dat::hasSkill(attacker, skill::SonsOath);
    if (affinity.has(Affinity::Repel)) {
        outcome = EffectResult::Repel;
        return true;
    }
    if (pierce) {
        const uint8_t element = static_cast<uint8_t>(dat::skillInfo(skill).skillattr);
        const uint32_t unpierced = element == 0 ? Affinity::Repel : Affinity::Repel | Affinity::Drain;
        if (element < 6 && !(affinity.raw & unpierced)) {
            if (affinity.raw & (Affinity::Null | Affinity::Drain))
                data.piercedResistance = 1;
            return false;
        }
    }
    if (affinity.has(Affinity::Drain)) {
        outcome = EffectResult::Drain;
        return true;
    }
    if (affinity.has(Affinity::Null)) {
        outcome = EffectResult::Null;
        return true;
    }
    return false;
}

// ... (and 0x2FE4E0): physical, the agility of both,
//   100 - failpoint + (A - D) 140 / (4 (A + D) + 100) + 1/2;
// magic, the caster's magic accuracy against the target's evasion power,
//   100 + (acc - eva) 200 / ((acc + eva - 74) 4 + 100)
// (95 no longer for enemies); then the hit rate, and the buffs (their
// product above 1 counting a fifth). (A branch scaling failpoint for
// single-target skills with a cost is never taken: its address check tests
// a register the next instruction overwrote.)
Float hitAccuracy(const NormalSkill& s, const UnitWork& attacker, const UnitWork& defender, Float hitRate,
                  Float accuracyBuff, Float evasionBuff)
{
    Float accuracy;
    if (s.damageClass == 0) {
        const int32_t a = dat::param(attacker, Param::Agility), d = dat::param(defender, Param::Agility);
        accuracy = Float::fromInt(a - d) * Float::fromInt(140) / Float::fromInt(4 * d + 4 * a + 100);
        accuracy = accuracy + Float::fromInt(100 - s.failpoint) + 0.5f;
    } else {
        const int32_t evasion = dat::evasionPower(defender), magic = dat::magicAccuracy(attacker);
        accuracy = Float::fromInt((magic - evasion) * 2) * 100.0f / (Float::fromInt((magic + evasion - 74) * 4) + 100.0f) + 100.0f;
    }
    accuracy = accuracy * hitRate;
    Float buffs = accuracyBuff * evasionBuff;
    if ((buffs * 100.0f).toInt() >= 100)
        buffs = (buffs - 1.0f) / 5.0f + 1.0f;
    return accuracy * buffs;
}

// nbCheckSensei @ 0x00269AD8 (and 0x2FEEF0): 70 scaled by the area's entry,
// then (if not 0) plus half the difference of Level + 3 Luck + 4 Agility,
// within 0..85; no level gap exempts the Demi-fiend.
int32_t firstStrikeChance(const InitiativeStats& s, uint8_t table, const Float* coefficients)
{
    const int32_t player = s.playerLevel + 3 * s.playerLuck + 4 * s.playerAgility;
    const int32_t enemy = s.enemyLevel + 3 * s.enemyLuck + 4 * s.enemyAgility;
    const int32_t half = (player - enemy) >> 1;
    if (table >= 6)   // (the original reads past the six-entry table)
        std::abort();
    int32_t chance = (Float::fromInt(70) * coefficients[table]).toInt();
    if (chance == 0)
        return 0;
    chance += half;
    if (chance < 0) chance = 0;
    if (chance > 85) chance = 85;
    return chance;
}

// nbCheckBackAttack @ 0x00269D20: Level + 8 Luck + 4 Agility + 40.
int32_t initiativeScore(int32_t level, int32_t luck, int32_t agility) { return level + 8 * luck + 4 * agility + 40; }

} // namespace nocturne::nb
