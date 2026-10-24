// How devils grow (original unit: cmb).
#include "nocturne/fusion/growth.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/inheritance.hpp"
#include "nocturne/fusion/stock.hpp"

namespace nocturne::cmb {

using ee::Float;
using ee::literal;

namespace {

void appendSkill(UnitWork& unit, uint16_t skill)
{
    unit.skill[unit.skillcnt] = skill;
    unit.skillcnt += 1;
}

// The first event of the given type, or null.
const GrowthEvent* firstEvent(const UnitWork& unit, uint8_t type)
{
    for (const GrowthEvent& event : dat::devilGrowth(unit.id).event)
        if (event.type == type)
            return &event;
    return nullptr;
}

} // namespace

// ===========================================================================
// Skills
// ===========================================================================

// cmbClearSkill @ 0x001FF070: only the first 12 of the 24 slots are cleared.
void clearSkills(UnitWork& unit)
{
    for (int i = 0; i < 12; ++i)
        unit.skill[i] = 0;
    unit.skillcnt = 0;
}

// cmbCreateDefaultSkill @ 0x00222788
void createDefaultSkills(uint16_t devil, UnitWork& unit)
{
    clearSkills(unit);
    for (const GrowthEvent& event : dat::devilGrowth(devil).event)
        if (event.type == GrowthEventType::Skill && event.targetlevel == 0)
            appendSkill(unit, event.param);
}

// ps2CreateLevelSkill @ 0x00222828 (level compared unsigned)
void createLevelSkills(uint16_t devil, uint8_t level, UnitWork& unit)
{
    clearSkills(unit);
    for (const GrowthEvent& event : dat::devilGrowth(devil).event)
        if (event.type == GrowthEventType::Skill && static_cast<uint8_t>(event.targetlevel) <= level)
            appendSkill(unit, event.param);
}

// cmbChkSkillOwner @ 0x001FEDA0
int8_t findSkill(uint16_t skill, const UnitWork& unit)
{
    for (int i = 0; i < unit.skillcnt; ++i)
        if (unit.skill[i] == skill)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbAddSkill @ 0x001FED00: into the first empty slot of the first 8.
int8_t addSkill(uint16_t skill, UnitWork& unit)
{
    if (findSkill(skill, unit) >= 0)
        return -2;
    for (int i = 0; i < 8; ++i) {
        if (unit.skill[i] == 0) {
            unit.skill[i] = skill;
            unit.skillcnt += 1;
            return static_cast<int8_t>(i);
        }
    }
    return -1;
}

// cmbChkLevelUpEvent @ 0x00222A28
const GrowthEvent* levelUpEvents(const UnitWork& unit, int8_t* count)
{
    uint8_t level = static_cast<uint8_t>(unit.level);
    const GrowthEvent* first = nullptr;
    uint8_t n = 0;
    for (const GrowthEvent& event : dat::devilGrowth(unit.id).event) {
        if (static_cast<uint8_t>(event.targetlevel) == level) {
            if (++n == 1)
                first = &event;
        }
    }
    if (count)
        *count = static_cast<int8_t>(n);
    return first;
}

// ===========================================================================
// EXP
// ===========================================================================

// cmpCalcLevelUpBaseExp @ 0x00223628
uint32_t baseExpForLevel(int32_t level)
{
    uint32_t l = static_cast<uint32_t>(level);
    uint32_t cube = l * l * l;   // wraps for absurd levels, as the original
    int32_t exp = (Float::fromInt(static_cast<int32_t>(cube)) * literal(1.42) + Float(-5.0f)).toInt();
    return exp < 0 ? 0 : static_cast<uint32_t>(exp);
}

// cmbCalcLevelUpExp @ 0x00223668
uint32_t expForLevel(const UnitWork& unit, int32_t level)
{
    uint32_t base = baseExpForLevel(level);
    if (unit.isPlayerCharacter())
        return base;
    uint8_t speciesLevel = dat::devilFormat(unit.id).level;
    Float factor = literal(2.7) - Float::fromInt(speciesLevel) * literal(0.017);
    int32_t scaled = (Float::fromInt(static_cast<int32_t>(base)) * factor).toInt();
    uint32_t speciesBase = baseExpForLevel(speciesLevel);
    int32_t exp = (Float::fromInt(scaled) - Float::fromInt(static_cast<int32_t>(speciesBase)) * factor).toInt();
    return static_cast<uint32_t>(exp) + unit.preEvolutionExp;
}

// cmbChkLevelUpExp @ 0x00223728
uint32_t expForNextLevel(const UnitWork& unit)
{
    return expForLevel(unit, unit.level + 1);
}

// cmbGetLevelUpCount @ 0x00223928: levels gained from extra EXP (cap 255).
int32_t levelUpCount(const UnitWork& unit, int32_t addedExp)
{
    UnitWork scratch;
    copyCustomDevil(scratch, unit);
    scratch.exp = static_cast<int32_t>(static_cast<uint32_t>(scratch.exp) + static_cast<uint32_t>(addedExp));
    int32_t count = 0;
    for (;;) {
        if (static_cast<uint32_t>(scratch.exp) < expForNextLevel(scratch))
            return count;
        uint16_t previous = scratch.level;
        scratch.level = static_cast<uint16_t>(previous + 1);
        if (previous >= 255)
            return count;
        ++count;
    }
}

// ===========================================================================
// Level-up stats
// ===========================================================================

// cmbGetParam @ 0x00221D70
int32_t growthParam(const UnitWork& unit, int32_t stat)
{
    return unit.id == 0 ? unit.param[stat] : dat::param(unit, static_cast<Param>(stat));
}

// cmbAddLevelUpParamEx @ 0x00222E00
//
// Each stat has a weight (the species' growparam, or the equipped
// Magatama's autoasignparam for the Demi-fiend; slot 1 is never raised) and a
// progress counter (UnitWork::levelupparam). The stats furthest behind
// (fewest completed weight cycles) compete, each in proportion to what it
// still lacks of its current cycle. Maxed stats (40) don't compete.
int8_t rollLevelUpStat(UnitWork& unit, int8_t mode)
{
    int16_t cycles[6];
    uint16_t lacking[6] = {};   // the original leaves excluded lanes uninitialised
    int32_t fewest = 0x1000;
    for (int lane = 0; lane < 6; ++lane) {
        uint32_t weight = unit.id == 0
            ? static_cast<uint8_t>(dat::magatama(dat::globalWork().hearts_equipped).autoasignparam[lane])
            : static_cast<uint8_t>(dat::devilGrowth(unit.id).growparam[lane]);
        if (lane == 1)
            weight = 0;
        uint32_t current = static_cast<uint32_t>(growthParam(unit, lane)) & 0xff;
        if (weight == 0 || current == 40) {
            cycles[lane] = -1;
            continue;
        }
        int32_t progress = unit.levelupparam[lane];
        cycles[lane] = static_cast<int16_t>(progress / static_cast<int32_t>(weight));
        lacking[lane] = static_cast<uint16_t>(static_cast<int32_t>(weight) - progress % static_cast<int32_t>(weight));
        if (cycles[lane] < fewest)
            fewest = cycles[lane];
    }

    uint32_t count = 0, total = 0;
    for (int lane = 0; lane < 6; ++lane) {
        if (cycles[lane] == fewest) {
            count = (count + 1) & 0xff;
            total = (total + lacking[lane]) & 0xffff;
        }
    }
    if (count == 0)
        return -1;

    uint32_t roll = (sdf::GetRand() % total) & 0xff;
    uint32_t cumulative = 0;
    for (int lane = 0; lane < 6; ++lane) {
        if (cycles[lane] != fewest)
            continue;
        cumulative = (cumulative + static_cast<uint8_t>(lacking[lane])) & 0xff;
        if (roll <= cumulative) {
            if (mode == 0)
                unit.levelupparam[lane] = static_cast<int8_t>(static_cast<uint8_t>(unit.levelupparam[lane]) + 1);
            return static_cast<int8_t>(lane);
        }
    }
    return 6;
}

// ps2AddLevelUpParam @ 0x00223080
int8_t addLevelUpStat(UnitWork& unit)
{
    return rollLevelUpStat(unit, 0);
}

// ===========================================================================
// Evolution
// ===========================================================================

// cmbChkEvoAttention @ 0x002230A0: index of the evolution notice due at the
// unit's level (levels compared as bytes), or -1.
int8_t evolutionNotice(const UnitWork& unit)
{
    uint8_t level = static_cast<uint8_t>(unit.level);
    const auto& events = dat::devilGrowth(unit.id).event;
    for (int i = 0; i < 24; ++i)
        if (events[i].type == GrowthEventType::EvolveNotice && static_cast<uint8_t>(events[i].targetlevel) <= level)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbChkCancelEvo @ 0x00223110: index of an evolution whose level is
// already behind the unit, or -1.
int8_t evolutionPassed(const UnitWork& unit)
{
    uint8_t level = static_cast<uint8_t>(unit.level);
    const auto& events = dat::devilGrowth(unit.id).event;
    for (int i = 0; i < 24; ++i)
        if (events[i].type == GrowthEventType::Evolve && static_cast<uint8_t>(events[i].targetlevel) < level)
            return static_cast<int8_t>(i);
    return -1;
}

// cmbChkDevilEvo @ 0x00223180: the base level of the species it evolves into.
int8_t evolvedSpeciesLevel(const UnitWork& unit)
{
    const GrowthEvent* event = firstEvent(unit, GrowthEventType::Evolve);
    return event ? static_cast<int8_t>(dat::devilFormat(event->param).level) : -1;
}

// cmbGetDevilEvoLevel @ 0x002231F8: the level at which it evolves.
int8_t evolutionLevel(const UnitWork& unit)
{
    const GrowthEvent* event = firstEvent(unit, GrowthEventType::Evolve);
    return event ? event->targetlevel : -1;
}

// cmbChkEvoNeedFlag @ 0x00222970: blocked until a story event.
bool evolutionNeedsEvent(uint16_t devil)
{
    const EvolutionRequirement* requirements = dat::tableAt<EvolutionRequirement>(dat::address::EvolutionRequirement);
    for (int i = 0; i < 6; ++i)
        if (requirements[i].devil == devil && !evt::BitCheck(requirements[i].eventbit))
            return true;
    return false;
}

// cmbChkEvoDevilLev @ 0x00223398
int32_t evolutionLevelLimit(const UnitWork& player, const UnitWork& stock, const UnitWork& evolved, int32_t eventLevel)
{
    int32_t limit = 255;
    if (eventLevel >= 0)
        limit = static_cast<int32_t>(99u - (static_cast<uint32_t>(stock.level) - static_cast<uint32_t>(eventLevel)));
    int32_t gap = evolved.level - player.level - 4;
    return limit < gap ? limit : gap;
}

// cmbCopyEvoDevilToStock @ 0x002233D0
//
// The evolved devil keeps the old one's flags, unique ID and EXP (also
// remembered as hensinmaeexp), remembers the original species, and keeps
// every old skill it could inherit (rate > 0; no random roll). It ends at
// full HP/MP.
void copyEvolvedDevil(UnitWork& unit, const UnitWork& evolved)
{
    UnitWork next;
    copyCustomDevil(next, evolved);
    clearSkills(next);
    if (next.flag & 0x200)
        unit.flag |= 0x200;
    next.preEvolutionId = unit.preEvolutionId ? unit.preEvolutionId : unit.id;
    int32_t oldExp = unit.exp;
    next.flag = unit.flag;
    next.uniqueid = unit.uniqueid;
    next.exp = static_cast<int32_t>(static_cast<uint32_t>(next.exp) + static_cast<uint32_t>(oldExp));
    next.preEvolutionExp = static_cast<uint32_t>(oldExp);
    for (int i = 0; i < unit.skillcnt; ++i)
        if (inheritRate(next, unit.skill[i]) != 0)
            appendSkill(next, unit.skill[i]);
    copyCustomDevil(unit, next);
    unit.hp = unit.maxhp;
    unit.mp = unit.maxmp;
}

// ===========================================================================
// Skill power-ups and mutation
// ===========================================================================

// cmbGetPowerUpSkill @ 0x002234E0
uint16_t powerUpSkill(uint16_t skill)
{
    const SkillPowerUp* powerUps = dat::tableAt<SkillPowerUp>(dat::address::SkillPowerUp);
    for (int i = 0; i < 55; ++i)
        if (powerUps[i].skill == skill)
            return powerUps[i].target;
    return 0;
}

// rstRndGetPowerUpSkill @ 0x00220D58: one of the unit's skills that has a
// stronger version, at random; returns that version and its slot.
uint16_t randomPowerUpSkill(const UnitWork& unit, int8_t* slot)
{
    uint16_t candidates[24];
    uint8_t slots[24];
    int32_t count = 0;
    for (int i = 0; i < unit.skillcnt; ++i) {
        uint16_t skill = unit.skill[i];
        if (!skill)
            continue;
        if (uint16_t stronger = powerUpSkill(skill)) {
            candidates[count] = stronger;
            slots[count] = static_cast<uint8_t>(i);
            count = static_cast<int8_t>(count + 1);
        }
    }
    if (count == 0)
        return 0;
    int32_t pick = static_cast<int8_t>(sdf::GetRand() % static_cast<uint32_t>(count));
    if (slot)
        *slot = static_cast<int8_t>(slots[pick]);
    return candidates[pick];
}

// cmbGetMutationSkill @ 0x00223520: up to 64 tries to find a skill one
// inheritance level above `skill` that the unit can learn and doesn't own.
uint16_t mutationSkill(uint16_t skill, UnitWork& unit)
{
    const InheritanceLevel* levels = dat::tableAt<InheritanceLevel>(dat::address::InheritanceLevel);
    for (int attempt = 0; attempt < 64; ++attempt) {
        uint16_t candidate = levels[sdf::GetRand() % 227].skill;
        uint32_t candidateLevel = inheritLevel(candidate);
        if (findSkill(candidate, unit) < 0 && inheritRate(unit, candidate) != 0 && skill != candidate) {
            uint32_t level = inheritLevel(skill);
            if (candidateLevel <= level + 1 && level + 1 <= candidateLevel)
                return candidate;
        }
    }
    return 0;
}

} // namespace nocturne::cmb
