// Battle calculations (original unit: nbCalc).
//
// Rewritten from the validated legacy C in legacy/src/combat_calculation.c. Each
// function notes its original name and PS2 address. Behaviour is meant to be
// identical, including the order of RNG draws, which tests/differential
// checks against the legacy code.
#include "nocturne/battle/calc.hpp"

#include <cstdlib>

#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

using ee::Float;

namespace {

// Two constants in the executable were rounded toward zero by the original
// toolchain, so they sit one ulp below the host's 0.1f / 0.001f.
const Float kTenPercent = Float::fromBits(0x3dcccccc);
const Float kLuckRatioEpsilon = Float::fromBits(0x3a83126e);

bool hasAilment(const UnitWork& unit, Ailment ailment)
{
    return unit.ailment() == static_cast<uint16_t>(ailment);
}

bool isNormalDifficulty() { return evt::BitCheck(EventBit::NormalDifficulty); }

bool percentRoll(int32_t chance) { return sdf::GetRandInt(100) < chance; }

// Agility relative to level, x100. Used for physical accuracy.
int32_t agilityScore(const UnitWork& unit)
{
    return dat::param(unit, Param::Agility) / (unit.level / 5 + 3) * 100;
}

// Base accuracy of a physical skill: 100 - failpoint, nudged by 1/16 of the
// agility-score difference between attacker and defender.
Float physicalAccuracy(const NormalSkill& skill, const UnitWork& attacker, const UnitWork& defender)
{
    int32_t attackerAgility = agilityScore(attacker);
    int32_t defenderAgility = agilityScore(defender);
    Float base = Float::fromInt(100 - skill.failpoint);
    return base + (Float::fromInt(attackerAgility) - Float::fromInt(defenderAgility)) * 0.0625f;
}

// The entry of the area encounter table this battle was rolled from.
const EncountRitu& encounterSlot(const MainProcessData& data, int32_t index)
{
    return dat::encountPack(data.encpackno).enctable[data.packno].ritu[index];
}

// Level + Luck/2 + Agility of the Demi-fiend, compared against the enemy
// averages by the first-strike and ambush rolls.
struct InitiativeStats {
    int32_t playerLevel, playerAgility, playerLuck;
    int32_t enemyLevel, enemyAgility, enemyLuck;
};

InitiativeStats initiativeStats(MainProcessData& data)
{
    InitiativeStats s;
    s.enemyLevel = averageLevel(data, Side::Enemy);
    s.enemyAgility = averageEncounterParam(data, Side::Enemy, Param::Agility);
    s.enemyLuck = averageEncounterParam(data, Side::Enemy, Param::Luck);
    const UnitWork& demiFiend = dat::globalWork().units[0];
    s.playerLevel = demiFiend.level;
    s.playerAgility = dat::param(demiFiend, Param::Agility);
    s.playerLuck = dat::param(demiFiend, Param::Luck);
    return s;
}

} // namespace

// ===========================================================================
// Hit resolution
// ===========================================================================

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
    if ((action.data->form[target].stat & FormationStat::Unknown2000) && !isNormalDifficulty())
        multiplier = 100.0f;

    // Might: normal attacks crit n/100 times as often (n = 300).
    bool mightFired = false;
    if (skill == skill::NormalAttack && passiveActive(attacker, skill::Might)) {
        mightFired = true;
        multiplier = multiplier * (Float::fromInt(dat::specialSkill(skill::Might).n) / 100.0f);
    }

    const NormalSkill& s = dat::normalSkill(skill);
    if (s.koukatype != 0)
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

    if (!percentRoll(threshold))
        return HitType::Normal;
    if (mightFired)
        action.autoskill = skill::Might;
    return HitType::Critical;
}

// nbGet3Zokusei @ 0x00265868
AlignmentClass alignmentClass(int32_t formindex)
{
    switch (dat::alignment(*GetUnitWorkFromFormindex(formindex))) {
    case -1: return AlignmentClass::Minus;
    case 1:  return AlignmentClass::Plus;
    default: return AlignmentClass::Neutral;
    }
}

// nbCheckKoukaJyoken @ 0x002658B8 ("jyoken" = 条件, condition)
//
// NormalSkill::hittype is a mask of which targets the skill can affect:
// bit 0 = anyone, bits 1..3 = targets of alignment class Minus/Neutral/Plus.
bool meetsSkillCondition(int32_t skill, int32_t /*source, unused*/, int32_t target)
{
    uint8_t mask = dat::normalSkill(skill).hittype;
    AlignmentClass alignment = alignmentClass(target);
    return (mask & 1)
        || ((mask & 2) && alignment == AlignmentClass::Minus)
        || ((mask & 4) && alignment == AlignmentClass::Neutral)
        || ((mask & 8) && alignment == AlignmentClass::Plus);
}

// nbGetKoukaType @ 0x00265948
//
// Resolves how a skill lands on one target: affinity (repel/drain/null),
// special-case programs, ailment immunity, and finally the accuracy roll.
EffectResult resolveEffect(int32_t skill, int32_t source, int32_t target)
{
    MainProcessData& data = *GetMainProcessData();
    const NormalSkill& s = dat::normalSkill(skill);

    // Programs whose outcome is decided elsewhere.
    switch (s.program) {
    case 1:          return EffectResult::Special7;
    case 2: case 3:  return EffectResult::Special6;
    case 4:          return EffectResult::Special8;
    case 5:          return EffectResult::Special9;
    case 7:          return EffectResult::Special10;
    case 12:         return EffectResult::Special12;
    case 13:         return EffectResult::Special13;
    case 14:         return EffectResult::Special14;
    default:         break;
    }

    UnitWork& attacker = *GetUnitWorkFromFormindex(source);
    UnitWork& defender = *GetUnitWorkFromFormindex(target);
    uint32_t formatFlag = devilFormatFlag(target);

    if (data.stat & BattleStat::DebugAlwaysRepel) return EffectResult::Repel;
    if (data.stat & BattleStat::DebugAlwaysHit)   return EffectResult::Hit;

    if (skill == skill::HolyMelody && (data.stat & BattleStat::BossBattle) && data.encno != 0x408 && defender.isEnemy())
        return EffectResult::Fail;
    if (skill == skill::EvilMelody && (data.stat & BattleStat::BossBattle) && defender.isEnemy())
        return EffectResult::Fail;

    // Affinity. Classes 12..14 have none.
    Attribute attr = skillAttribute(skill);
    if (attr != Attribute::None && (attr < Attribute(12) || attr > Attribute(14))) {
        Affinity targetAffinity = affinity(skill, target, attr);
        // A frozen target loses physical Null/Repel/Drain.
        if (hasAilment(defender, Ailment::Freeze) && s.koukatype == 0)
            targetAffinity.raw &= ~(Affinity::Null | Affinity::Repel | Affinity::Drain);
        if (targetAffinity.has(Affinity::Repel))
            return EffectResult::Repel;
        // Pierce lets physical skills through Null and Drain (not Repel).
        if (dat::hasSkill(attacker, skill::Pierce) && s.koukatype == 0) {
            if (targetAffinity.raw & (Affinity::Null | Affinity::Drain))
                data.piercedResistance = 1;
        } else {
            if (targetAffinity.has(Affinity::Drain)) return EffectResult::Drain;
            if (targetAffinity.has(Affinity::Null))  return EffectResult::Null;
        }
    }

    if ((data.stat & BattleStat::Unknown400) && defender.isEnemy()) {
        if (s.targettype == 0) {
            if (data.form[target].stat & FormationStat::Unknown1000)
                return EffectResult::Special11;
        } else if (attr != Attribute(14) && data.enemypcnt != 1) {
            return EffectResult::Fail;
        }
    }

    // Program 6 (Eternal Rest) only works on sleepers; program 15 on the poisoned.
    if (s.program == 6) {
        if (!hasAilment(defender, Ailment::Sleep)) return EffectResult::Fail;
    } else if (s.program == 15 && !hasAilment(defender, Ailment::Poison)) {
        return EffectResult::Fail;
    }

    // A target that cannot move cannot dodge.
    switch (static_cast<Ailment>(defender.ailment())) {
    case Ailment::Sleep: case Ailment::Stun: case Ailment::Bind:
    case Ailment::Stone: case Ailment::Shock: case Ailment::Freeze:
        return EffectResult::Hit;
    default:
        break;
    }

    if (!meetsSkillCondition(skill, source, target)) {
        diag::print(diag::Message::Miss);
        return EffectResult::Fail;
    }
    if (s.hitlevel == 0xff)
        return EffectResult::Hit;

    Float hitRate = Float::fromInt(s.hitlevel) * 0.01f;
    // Normal difficulty: hptype 3 / hpn 1 skills (e.g. Evil Gaze) are less
    // accurate against the player's side.
    if (isNormalDifficulty() && s.hptype == 3 && s.hpn == 1 && !defender.isEnemy())
        hitRate = hitRate * 0.7f;

    Float attackerAccuracyBuff = buffMultiplier(source, 8);
    Float defenderEvasionBuff = buffMultiplier(target, 6);

    Float accuracy;
    if (s.koukatype == 0) {
        accuracy = physicalAccuracy(s, attacker, defender);
    } else if (s.koukatype == 1) {
        // Magic: evasion as a percentage of the caster's magic accuracy,
        // halved, on top of 100 (95 for enemy casters).
        Float base = attacker.isEnemy() ? 95.0f : 100.0f;
        int32_t evasion = dat::evasionPower(defender);
        int32_t magicAccuracy = dat::magicAccuracy(attacker);
        if (magicAccuracy == 0)
            divideByZeroTrap();
        int32_t evasionPercent = evasion * 100 / magicAccuracy;
        accuracy = Float::fromInt(100 - evasionPercent) * 0.5f + base;
    } else {
        return EffectResult::Hit;
    }

    accuracy = accuracy * attackerAccuracyBuff * defenderEvasionBuff * hitRate;
    if (accuracy < 50.0f)  accuracy = 50.0f;
    if (accuracy > 100.0f) accuracy = 100.0f;
    // A stunned attacker hits a quarter as often (this is applied after the
    // 50% floor).
    if (badStat(source) == static_cast<uint32_t>(Ailment::Stun))
        accuracy = accuracy * 0.25f;

    int32_t threshold = accuracy.toInt();
    diag::print(s.koukatype == 0 ? diag::Message::PhysicalHitRate : diag::Message::MagicHitRate, threshold);
    if (percentRoll(threshold))
        return EffectResult::Hit;
    return (formatFlag & 0x800) ? EffectResult::Fail : EffectResult::Miss;
}

// nbCheckStoneDead @ 0x00267390
//
// A petrified target hit by Physical or Force may shatter (instant death).
// Luck resists: chance = 100 - Luck / ((Level + 20) / 5) * k, at least 20,
// with k = 40 for the Demi-fiend and 20 for demons.
bool rollStoneShatter(int32_t skill, int32_t target)
{
    UnitWork* unit = GetUnitWorkFromFormindex(target);
    if (!unit || badStat(target) != static_cast<uint32_t>(Ailment::Stone))
        return false;
    Attribute attr = skillAttribute(skill);
    if (attr != Attribute::Physical && attr != Attribute::Force)
        return false;

    int32_t luck = dat::param(*unit, Param::Luck);
    Float luckDivisor = (Float::fromInt(unit->level) + 20.0f) / 5.0f;
    Float resistance = Float::fromInt(luck) / luckDivisor * (unit->isPlayerCharacter() ? 40.0f : 20.0f);
    int32_t chance = (Float(100.0f) - resistance).toInt();
    if (chance < 20)
        chance = 20;
    diag::print(diag::Message::StoneShatterRate, chance);
    return percentRoll(chance);
}

// nbCheckBadKaifuku @ 0x00267530
bool checkAilment(const UnitWork* unit, AilmentCheck check)
{
    if (!unit || !(unit->flag & UnitFlag::Valid))
        return false;
    auto ailment = static_cast<Ailment>(unit->ailment());

    switch (check) {
    case AilmentCheck::IsBound:  return ailment == Ailment::Bind;
    case AilmentCheck::IsAsleep: return ailment == Ailment::Sleep;
    case AilmentCheck::HasCurable:
        switch (ailment) {
        case Ailment::Shock: case Ailment::Freeze: case Ailment::Sleep: case Ailment::Panic:
        case Ailment::Bind: case Ailment::Charm: case Ailment::Fly: case Ailment::Stone:
            return true;
        default:
            return false;
        }
    case AilmentCheck::TurnEndRecovery:
        break;
    default:
        return false;
    }

    // Shock and Freeze always wear off after a turn.
    if (ailment == Ailment::Shock || ailment == Ailment::Freeze)
        return true;

    // Sleep/Panic/Bind/Charm: chance = k * Luck / ((Level + 20) / 5),
    // with k = 20 for Sleep, 30 for Panic and Bind, 40 for Charm.
    Float k;
    switch (ailment) {
    case Ailment::Sleep:                     k = 20.0f; break;
    case Ailment::Panic: case Ailment::Bind: k = 30.0f; break;
    case Ailment::Charm:                     k = 40.0f; break;
    default: return false;
    }
    int32_t luck = dat::param(*unit, Param::Luck);
    int32_t luckDivisor = (unit->level + 20) / 5;
    Float luckRatio = Float::fromInt(luck) / Float::fromInt(luckDivisor);
    int32_t chance = (k * luckRatio).toInt();
    diag::print(diag::Message::AilmentRecovery, chance);
    return percentRoll(chance);
}

// nbGetCriticalPow @ 0x0026A828: criticals do 1.5x damage.
ee::Float criticalPower(int32_t /*source, unused*/, ee::Float power)
{
    return power * 1.5f;
}

// ===========================================================================
// Skill data queries
// ===========================================================================

// nbGetHpDrainRitu @ 0x00266C90
Float hpDrainRate(int32_t skill)
{
    uint16_t type = dat::normalSkill(skill).hptype;
    return (type == 12 || type == 13) ? 1.0f : 0.0f;
}

// nbGetMpDrainRitu @ 0x00266CD8
Float mpDrainRate(int32_t skill)
{
    uint16_t type = dat::normalSkill(skill).mptype;
    return (type == 12 || type == 13) ? 1.0f : 0.0f;
}

// nbGetGensyoRitu @ 0x00266D20 ("gensyo" = 減少, reduction)
Float reductionRate(int32_t skill)
{
    return Float::fromInt(dat::normalSkill(skill).minus) / 100.0f;
}

// nbCheckHitEffect @ 0x00267370
bool hasHitEffect(int32_t skill)
{
    return guest::table<const uint8_t>(dat::address::SkillHitEffect)[skill * 4 + 3] == 0;
}

// nbGetDeadType @ 0x00267388 (identity tentative: a bare "return 0").
int32_t deadType() { return 0; }

// nbCheckSingleTargetSkill @ 0x0026A448
bool isSingleTargetSkill(int32_t skill)
{
    return dat::normalSkill(skill).targettype == 0;
}

// ===========================================================================
// Unit state
// ===========================================================================

// nbAddHpMp @ 0x002660C0
void addHpMp(int32_t formindex, Resource resource, int32_t amount)
{
    UnitWork* unit = GetUnitWorkFromFormindex(formindex);
    if (!unit)
        return;
    if (resource == Resource::Hp)
        dat::addHp(*unit, amount);
    else if (resource == Resource::Mp)
        dat::addMp(*unit, amount);
}

// nbSetBadStat @ 0x002674D0
void setAilment(int32_t formindex, bool set, uint32_t badstat)
{
    UnitWork* unit = GetUnitWorkFromFormindex(formindex);
    if (!unit)
        return;
    if (set)
        dat::setAilment(*unit, badstat);
    else
        dat::clearAilment(*unit, badstat);
}

// nbCheckBadCurse @ 0x002677B8
bool isCursed(int32_t formindex)
{
    UnitWork* unit = GetUnitWorkFromFormindex(formindex);
    return unit && (unit->badstat & kBadStatCurse);
}

// nbCheckFormationFriend @ 0x0026A470
bool sameSide(int32_t formindex1, int32_t formindex2)
{
    return isPlayerSide(formindex1) == isPlayerSide(formindex2);
}

// nbCheckBadPanicAction @ 0x0026A688
//
// True with 90% probability for enemy demons, 70% for everyone else.
bool rollPanicAction(const UnitWork& unit)
{
    int32_t threshold = (!unit.isPlayerCharacter() && unit.isEnemy()) ? 10 : 30;
    return !percentRoll(threshold);
}

// nbCheckBadStatusGameOver @ 0x0026A6D8
//
// The battle is lost when everyone in the party (empty slots aside) is stone.
bool isPartyPetrified()
{
    for (int32_t i = 0; i < kPlayerFormations; ++i) {
        UnitWork* unit = GetUnitWorkFromFormindex(i);
        if (unit && !hasAilment(*unit, Ailment::Stone))
            return false;
    }
    return true;
}

// 0x00259A60 (unnamed): the model record for a unit.
const UnitVisual& unitVisual(const UnitWork& unit)
{
    int32_t id = unitModelId(unit);
    if (id == 0)
        return *guest::table<const UnitVisual>(dat::address::DefaultUnitVisual);
    return guest::table<const UnitVisual>(dat::address::UnitVisual)[id];
}

// nbSetHpScale @ 0x0026A740
//
// Wounded combatants shrink: scale goes linearly from the model's base scale
// at full HP down to 0.5 at zero HP.
void updateHpModelScale(Formation& form)
{
    UnitWork* unit = GetUnitWorkFromFormindex(form.formindex);
    if (!unit || unit->hp == 0)
        return;
    Float hpRatio = Float::fromInt(unit->hp) / Float::fromInt(unit->maxhp);
    Float baseScale = unitVisual(*unit).scale;
    form.scl = (baseScale - 0.5f) * hpRatio + 0.5f;
}

// ===========================================================================
// Encounter flow
// ===========================================================================

// 0x00259658 (unnamed): switch the battle to another encounter and reset
// per-encounter state.
void setEncounter(int32_t encno)
{
    MainProcessData& data = *GetMainProcessData();
    data.encno = encno;
    data.formationtype = dat::encount(encno).formationtype;
    data.previndex = -1;
    data.esccnt = 0;
    data.endtype = 0;
    data.activeunit = -1;
    data.orderindex = -1;
    data.prevcommand = 0;
    data.prevcommind = 0;
    data.prevflag = 0;
    data.turn = 0;
    data.nextphase = 0;
}

// nbGetLvAvg2 @ 0x002697D8
//
// Player side: active stock members. Enemy side: the encounter's demons, at
// their species level.
int32_t averageLevel(MainProcessData& data, Side side)
{
    int32_t sum = 0, count = 0;
    if (side == Side::Player) {
        for (const UnitWork& unit : dat::globalWork().units) {
            if ((unit.flag & (UnitFlag::Valid | UnitFlag::InParty)) == (UnitFlag::Valid | UnitFlag::InParty)) {
                sum += unit.level;
                ++count;
            }
        }
    } else {
        for (uint16_t devil : dat::encount(data.encno).devil) {
            if (devil) {
                sum += dat::devilFormat(devil).level;
                ++count;
            }
        }
    }
    return count ? sum / count : 0;
}

// nbGetParamAvg @ 0x002698C0: a stat averaged over one side's combatants.
int32_t averageParam(MainProcessData& data, Side side, Param stat)
{
    int32_t sum = 0, count = 0;
    for (int32_t i = 0; i < kFormationCount; ++i) {
        Party& party = data.party[i];
        uint16_t flags = static_cast<uint16_t>(party.flag);
        if (!(flags & PartyFlag::Active) || (flags & PartyFlag::Inactive))
            continue;
        bool enemy = (flags & PartyFlag::EnemySide) != 0;
        if (enemy != (side == Side::Enemy))
            continue;
        sum += dat::param(*GetUnitWorkPointer(data, party), stat);
        ++count;
    }
    return count ? sum / count : 0;
}

// nbGetParamAvg2 @ 0x002699B0: like averageLevel, for a stat.
int32_t averageEncounterParam(MainProcessData& data, Side side, Param stat)
{
    int32_t sum = 0, count = 0;
    if (side == Side::Player) {
        for (const UnitWork& unit : dat::globalWork().units) {
            if ((unit.flag & (UnitFlag::Valid | UnitFlag::InParty)) == (UnitFlag::Valid | UnitFlag::InParty)) {
                sum += dat::param(unit, stat);
                ++count;
            }
        }
    } else {
        for (uint16_t devil : dat::encount(data.encno).devil) {
            if (devil) {
                sum += dat::devilFormat(devil).param[static_cast<int32_t>(stat)];
                ++count;
            }
        }
    }
    return count ? sum / count : 0;
}

// nbCheckSensei @ 0x00269AD8 ("sensei" = 先制, first strike)
//
// True when the enemies act first. The player keeps the initiative with
// chance/128, where chance = 72 + (Demi-fiend score - enemy score) clamped
// to 70..85 and score = Level + Luck/2 + Agility. Unless the Demi-fiend
// outlevels the enemies by 15+, the area's table entry scales the chance
// (x1, 0.9, 0.8, 0.6, 0 or 3). On Normal a failed roll gets a second,
// 50/50 chance.
bool rollEnemiesFirst(MainProcessData& data)
{
    const Float* coefficients = guest::table<const Float>(dat::address::SenseiCoefficient);

    uint16_t flags = dat::encount(data.encno).flag;
    if (flags & EncountFlag::PlayerAlwaysFirst)  return false;
    if (flags & EncountFlag::EnemiesAlwaysFirst) return true;

    InitiativeStats s = initiativeStats(data);
    int32_t playerScore = s.playerLevel + s.playerLuck / 2 + s.playerAgility;
    int32_t enemyScore = s.enemyLevel + s.enemyLuck / 2 + s.enemyAgility;
    int32_t chance = playerScore - enemyScore + 72;
    if (chance < 70) chance = 70;
    if (chance > 85) chance = 85;

    uint8_t table = encounterSlot(data, data.packindex).sensei;
    if (s.playerLevel < s.enemyLevel + 15) {
        // The original reads past the six-entry table for larger indexes.
        if (table >= 6)
            std::abort();
        chance = (Float::fromInt(chance) * coefficients[table]).toInt();
    }

    int32_t draw = sdf::GetRandInt(128);
    diag::print(diag::Message::FirstStrike, s.playerLevel, s.enemyLevel, table, chance, draw);
    if (draw < chance)
        return false;
    if (isNormalDifficulty() && (sdf::GetRandInt(128) & 1))
        return false;
    return true;
}

// nbCheckBackAttack @ 0x00269D20
//
// Only rolled after the enemies won the initiative. The chance is a flat
// 12% (4% with Mind's Eye in the party); the level/stat scores are computed
// but only reach the debug print.
bool rollBackAttack(MainProcessData& data)
{
    int8_t mode = dat::encount(data.encno).backattack;
    if (mode == -1) return false;
    if (mode == 1)  return true;

    InitiativeStats s = initiativeStats(data);
    int32_t draw = sdf::GetRandInt(100);
    int32_t enemyScore = s.enemyLevel + s.enemyLuck / 2 + s.enemyAgility + 10;
    int32_t playerScore = s.playerLevel + s.playerLuck / 2 + s.playerAgility + 10;

    int32_t chance = 12;
    if (dat::partyHasSkill(skill::MindsEye)) {
        int32_t divisor = dat::specialSkill(skill::MindsEye).n;
        if (divisor == 0)
            divideByZeroTrap();
        chance = 12 / divisor;
    }
    diag::print(diag::Message::BackAttack, playerScore, enemyScore, chance, draw);
    return draw < chance;
}

// nbCheckEscape @ 0x00269E98
//
// True when the party escapes (the caller then ends the battle with
// endtype 3). Escape is certain from always-escapable encounters or when no
// enemy can act. Otherwise:
//   chance = 2 * (20 * attempts + 20 * party (Ag+Lu) / enemy (Ag+Lu))
// (x1.5 with Fast Retreat). On Hard, escape fails outright. Under a full
// Kagutsuchi a successful roll must also pass a 5/8 check.
bool rollEscape(MainProcessData& data)
{
    if (dat::encount(data.encno).flag & EncountFlag::AlwaysEscapable)
        return true;

    bool anyEnemyCanAct = false;
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        UnitWork* unit = GetUnitWorkFromFormindex(f);
        if (!unit)
            continue;
        switch (static_cast<Ailment>(unit->ailment())) {
        case Ailment::Shock: case Ailment::Freeze: case Ailment::Sleep:
        case Ailment::Bind: case Ailment::Stun: case Ailment::Stone:
            break;
        default:
            anyEnemyCanAct = true;
        }
    }
    if (!anyEnemyCanAct)
        return true;

    int32_t partyAgility = averageParam(data, Side::Player, Param::Agility);
    int32_t partyLuck = averageParam(data, Side::Player, Param::Luck);
    int32_t enemyAgility = averageParam(data, Side::Enemy, Param::Agility);
    int32_t enemyLuck = averageParam(data, Side::Enemy, Param::Luck);
    Float statRatio = Float::fromInt(partyAgility + partyLuck) / Float::fromInt(enemyAgility + enemyLuck) * 20.0f;
    int32_t chance = (Float::fromInt(data.esccnt * 20) + statRatio).toInt();
    if (dat::partyHasSkill(skill::FastRetreat))
        chance = chance * dat::specialSkill(skill::FastRetreat).n / 100;

    bool normal = isNormalDifficulty();
    chance *= 2;
    if (!normal)
        return false;
    diag::print(diag::Message::EscapeRate, chance);

    if (chance < sdf::GetRandInt(100))
        return false;
    if (evt::GetAgeOfMoon() != kMoonFull)
        return true;
    if (sdf::GetRandInt(4) == 1)
        return true;
    // Always Normal at this point, so this is a plain coin flip.
    if (isNormalDifficulty() && (sdf::GetRandInt(2) & 1))
        return true;
    return false;
}

// nbCheckRenzokuEncount @ 0x0026A158 ("renzoku" = 連続, consecutive)
//
// After a battle, possibly start another one straight away. Each area table
// entry has its own chance and follow-up entry.
bool rollConsecutiveEncounter(MainProcessData& data)
{
    if (dat::encount(data.encno).flag & EncountFlag::ForcedFollowUp) {
        data.encno = 0x149;
        data.packindex = 1;
        setEncounter(data.encno);
        return true;
    }
    if (data.encpackno <= 0)
        return false;

    const EncountRitu& slot = encounterSlot(data, data.packindex);
    int32_t chance = slot.renzokuritu;
    int32_t next = slot.renzokuindex;
    if (dat::globalWork().unknown_0a4c & 2)
        chance *= 5;
    diag::print(diag::Message::ConsecutiveRate, chance, next);
    if (!percentRoll(chance))
        return false;

    data.packindex = next;
    data.encno = encounterSlot(data, next).encountid;
    setEncounter(data.encno);
    return true;
}

// ===========================================================================
// Rewards
// ===========================================================================

namespace {

// Add `count` of `item` to the battle spoils. Returns false when all four
// slots hold other items.
bool addSpoils(MainProcessData& data, uint8_t item, uint8_t count)
{
    for (int i = 0; i < 4; ++i) {
        if (data.item[i] == item) {
            data.itemcnt[i] = static_cast<uint8_t>(data.itemcnt[i] + count);
            return true;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (!data.item[i]) {
            data.item[i] = item;
            data.itemcnt[i] = count;
            return true;
        }
    }
    return false;
}

} // namespace

// nbGetEncountTableItem @ 0x00269318
//
// The encounter's guaranteed item. If the spoils are full it is pushed to
// the front and the last item is dropped.
void addEncounterItem(MainProcessData& data)
{
    if (data.encno <= 0 || dat::BossRashChk(data.encno))
        return;
    const Encount& e = dat::encount(data.encno);
    if (!e.item || !e.itemcnt)
        return;
    if (addSpoils(data, e.item, e.itemcnt))
        return;
    for (int i = 3; i > 0; --i) {
        data.item[i] = data.item[i - 1];
        data.itemcnt[i] = data.itemcnt[i - 1];
    }
    data.item[0] = e.item;
    data.itemcnt[0] = e.itemcnt;
}

// nbGetExpMakaItem @ 0x00269448
//
// EXP, Macca and item drops for one defeated enemy.
void addDefeatRewards(const UnitWork& defeated)
{
    if (defeated.isPlayerCharacter())
        return;
    MainProcessData& data = *GetMainProcessData();
    bool bossRefight = dat::BossRashChk(data.encno);
    const DevilFormat& devil = dat::devilFormat(defeated.id);

    // EXP shrinks when the Demi-fiend outlevels the enemy: /1.3 at 6..11
    // levels above, /1.8 at 12+. Enemies of level 70+ only get the /1.3,
    // from 6 levels up.
    int32_t exp = devil.dropexp;
    int32_t levelGap = dat::playerLevel() - defeated.level;
    Float divisor;
    bool reduced = false;
    if (defeated.level < 70) {
        if (levelGap >= 6 && levelGap <= 11) { divisor = 1.3f; reduced = true; }
        else if (levelGap > 11)              { divisor = 1.8f; reduced = true; }
    } else if (levelGap > 5) {
        divisor = 1.3f; reduced = true;
    }
    if (reduced)
        exp = (Float::fromInt(exp) / divisor).toInt();

    int32_t macca = devil.dropmakka;
    if (bossRefight) {
        exp /= 10;
        macca /= 10;
    }
    data.exp += exp;
    data.maka += macca;
    if (bossRefight)
        return;

    // At most one item: the special drop (if its event bit is set), else
    // the ordinary drops in order, else a Bead, else a Life Stone.
    uint8_t drop = 0;
    if (devil.specialbit == 0 || evt::BitCheck(devil.specialbit)) {
        if (devil.specialitem && percentRoll(devil.specialpoint))
            drop = devil.specialitem;
    }
    if (!drop) {
        for (int i = 0; i < 2 && !drop; ++i) {
            if (devil.dropitem[i] && percentRoll(devil.droppoint[i]))
                drop = devil.dropitem[i];
        }
    }
    // The Bead and Life Stone rolls happen even when an item already dropped.
    bool bead = percentRoll(devil.hougyokupoint);
    if (bead && !drop) drop = item::Bead;
    bool lifeStone = percentRoll(devil.masekipoint);
    if (lifeStone && !drop) drop = item::LifeStone;

    if (drop)
        addSpoils(data, drop, 1);   // lost if the spoils are full
}

// nbGetMakaBaramaki @ 0x0026A4B0 ("baramaki" = ばら撒き, scattering)
//
// Macca scattered by a unit. For an enemy: its Macca drop scaled by the
// Demi-fiend's luck. For the player's side: 1/20 of the party's Macca,
// divided by the unit's luck ratio, then /10 on Normal. Either way +-10%
// jitter and at least 1.
int32_t scatteredMacca(const UnitWork& unit)
{
    GlobalWork& global = dat::globalWork();
    Float cashShare = Float::fromInt(global.maka) / 20.0f;

    int32_t base;
    if (unit.isEnemy()) {
        const UnitWork& demiFiend = global.units[0];
        Float luckDivisor = Float::fromInt(demiFiend.level) / 5.0f + 4.0f;
        int32_t luck = dat::param(demiFiend, Param::Luck);
        Float luckRatio = Float::fromInt(luck) / luckDivisor;
        base = (Float::fromInt(dat::devilFormat(unit.id).dropmakka) * luckRatio).toInt();
    } else {
        Float luckDivisor = Float::fromInt(unit.level) / 5.0f + 4.0f;
        int32_t luck = dat::param(unit, Param::Luck);
        Float luckRatio = Float::fromInt(luck) / luckDivisor;
        base = (kLuckRatioEpsilon <= luckRatio.abs()) ? (cashShare / luckRatio).toInt() : 0;
    }

    Float jitter = sdf::GetRandFloat() - 0.5f;   // -0.5 .. 0.5
    jitter = jitter + jitter;                    // -1 .. 1
    jitter = jitter * kTenPercent;               // -0.1 .. 0.1
    Float amount = Float::fromInt(base);
    int32_t value = (amount + amount * jitter).toInt();

    if (isNormalDifficulty() && !unit.isEnemy())
        value /= 10;
    return value > 0 ? value : 1;
}

// nbGetKakutokuExp @ 0x0026A840 ("kakutoku" = 獲得, earned)
//
// Two encounters (0x10B, 0x11C) cap EXP at 20000 and Macca at 10000.
int32_t earnedExp(const MainProcessData& data)
{
    int32_t exp = static_cast<int32_t>(data.exp);
    if ((data.encno == 0x10b || data.encno == 0x11c) && exp > 20000)
        exp = 20000;
    return exp;
}

// nbGetKakutokuMaka @ 0x0026A870
int32_t earnedMacca(const MainProcessData& data)
{
    int32_t macca = static_cast<int32_t>(data.maka);
    if ((data.encno == 0x10b || data.encno == 0x11c) && macca > 10000)
        macca = 10000;
    return macca;
}

} // namespace nocturne::nb
