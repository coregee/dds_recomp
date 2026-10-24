// Battle calculations (original unit: nbCalc): US Maniax's own (shared/src/battle/calc.cpp has the rest).
#include "nocturne/battle/calc.hpp"

#include <cstdlib>

#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

using ee::Float;

// 0x00259A60 (unnamed): each devil has its own model record.
int32_t visualModel(int32_t id) { return id; }

// nbCheckEscape @ 0x00269E98: attempts and the stat ratio weigh 20; the
// chance doubles, and on Hard escape fails.
int32_t escapeWeight() { return 20; }
bool escapeDifficulty(int32_t& chance, bool normal)
{
    chance *= 2;
    return normal;
}

// nbGetMakaBaramaki @ 0x0026A4B0: the party's side scatters 1/20 of its Macca.
ee::Float maccaShareDivisor() { return ee::Float::fromInt(20); }

// nbGetHitType @ 0x002654B8
//
// Decides whether an attack that connects is a critical or weakness hit
// (both earn a half press turn). Only physical skills can crit.
HitType rollCritical(ActionProcessData& action, int32_t skill, int32_t source, int32_t target)
{
    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    UnitWork& defender = *GetUnitWorkFromFormindex(target);

    Attribute attr = skillAttribute(skill);
    if (attr == Attribute::None || (attr >= Attribute(12) && attr <= Attribute(15)))
        return HitType::Normal;
    Affinity targetAffinity = affinity(skill, target, attr);

    // Bright Might / Dark Might: guaranteed critical when they activate.
    if (skill == skill::NormalAttack) {
        if (passiveActive(attacker, skill::BrightMight)) {
            action.autoskill = skill::BrightMight;
            return HitType::Critical;
        }
        if (passiveActive(attacker, skill::DarkMight)) {
            action.autoskill = skill::DarkMight;
            return HitType::Critical;
        }
    }

    if (targetAffinity.has(Affinity::Weak))
        return HitType::Weakness;

    if (GetPartyFromFormindex(source)->flag & PartyFlag::AlwaysCrit)
        return HitType::Critical;

    // Helpless targets are easy to crit: Shocked and Frozen effectively always.
    Float multiplier = 1.0f;
    switch (static_cast<Ailment>(defender.ailment())) {
    case Ailment::Shock: case Ailment::Freeze: multiplier = 100.0f; break;
    case Ailment::Sleep: case Ailment::Bind:   multiplier = 8.0f;   break;
    default: break;
    }
    if ((action.data->form[target].stat & FormationStat::Unknown2000) && !evt::BitCheck(EventBit::NormalDifficulty))
        multiplier = 100.0f;

    // Might: normal attacks crit n/100 times as often (n = 300).
    bool mightFired = false;
    if (skill == skill::NormalAttack && passiveActive(attacker, skill::Might)) {
        mightFired = true;
        multiplier = multiplier * (Float::fromInt(dat::specialSkill(skill::Might).n) / 100.0f);
    }

    const NormalSkill& s = dat::normalSkill(skill);
    if (s.damageClass != 0)
        return HitType::Normal;

    // Crit chance = criticalpoint, scaled by how far agility pushed accuracy
    // above the skill's base, with accuracy floored at 50.
    Float base = Float::fromInt(100 - s.failpoint);
    Float accuracy = physicalAccuracy(s, attacker, defender);
    if (accuracy < 50.0f)
        accuracy = 50.0f;
    Float chance = accuracy / base * Float::fromInt(s.criticalpoint) * multiplier;
    int32_t threshold = chance.toInt();
    diag::print(diag::Message::Critical, s.criticalpoint, accuracy.toInt(), threshold);

    if (!(sdf::GetRandInt(100) < threshold))
        return HitType::Normal;
    if (mightFired)
        action.autoskill = skill::Might;
    return HitType::Critical;
}

// nbGetKoukaType @ 0x00265948: Repel, then Drain and Null, which Pierce lets
// physical skills through (flagging it).
bool affinityOutcome(int32_t, const NormalSkill& s, const UnitWork& attacker, Affinity affinity, MainProcessData& data,
                     EffectResult& outcome)
{
    if (affinity.has(Affinity::Repel)) {
        outcome = EffectResult::Repel;
        return true;
    }
    if (dat::hasSkill(attacker, skill::Pierce) && s.damageClass == 0) {
        if (affinity.raw & (Affinity::Null | Affinity::Drain))
            data.piercedResistance = 1;
        return false;
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

// ... physical, the agility scores; magic, evasion as
// a percentage of the caster's magic accuracy, halved, on top of 100 (95 for
// enemy casters); then the buffs and the skill's hit rate.
Float hitAccuracy(const NormalSkill& s, const UnitWork& attacker, const UnitWork& defender, Float hitRate,
                  Float accuracyBuff, Float evasionBuff)
{
    Float accuracy;
    if (s.damageClass == 0) {
        accuracy = physicalAccuracy(s, attacker, defender);
    } else {
        Float base = attacker.isEnemy() ? 95.0f : 100.0f;
        int32_t evasion = dat::evasionPower(defender);
        int32_t magicAccuracy = dat::magicAccuracy(attacker);
        if (magicAccuracy == 0)
            divideByZeroTrap();
        int32_t evasionPercent = evasion * 100 / magicAccuracy;
        accuracy = Float::fromInt(100 - evasionPercent) * 0.5f + base;
    }
    return accuracy * accuracyBuff * evasionBuff * hitRate;
}

// nbCheckSensei @ 0x00269AD8: 72 + (Demi-fiend score - enemy score), score =
// Level + Luck/2 + Agility, clamped to 70..85; unless the Demi-fiend outlevels
// the enemies by 15+, the area's entry scales it (x1, 0.9, 0.8, 0.6, 0 or 3).
int32_t firstStrikeChance(const InitiativeStats& s, uint8_t table, const Float* coefficients)
{
    int32_t playerScore = s.playerLevel + s.playerLuck / 2 + s.playerAgility;
    int32_t enemyScore = s.enemyLevel + s.enemyLuck / 2 + s.enemyAgility;
    int32_t chance = playerScore - enemyScore + 72;
    if (chance < 70) chance = 70;
    if (chance > 85) chance = 85;
    if (s.playerLevel < s.enemyLevel + 15) {
        // The original reads past the six-entry table for larger indexes.
        if (table >= 6)
            std::abort();
        chance = (Float::fromInt(chance) * coefficients[table]).toInt();
    }
    return chance;
}

// nbCheckBackAttack @ 0x00269D20: Level + Luck/2 + Agility + 10.
int32_t initiativeScore(int32_t level, int32_t luck, int32_t agility) { return level + luck / 2 + agility + 10; }

} // namespace nocturne::nb
