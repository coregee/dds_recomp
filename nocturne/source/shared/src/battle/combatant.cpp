// Questions about one combatant (original unit: nbCalc).
#include "nocturne/battle/combatant.hpp"

#include "nocturne/battle/calc.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/devil_ai.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/facility/compendium.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/build.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

// nbGetBadStat @ 0x00267788
uint32_t badStat(int32_t formindex)
{
    UnitWork* unit = GetUnitWorkFromFormindex(formindex);
    return unit ? unit->ailment() : 0;
}

// nbGetNormalSkillAttr @ 0x00267E38
Attribute skillAttribute(int32_t skill)
{
    return static_cast<Attribute>(dat::skillInfo(skill).skillattr);
}

// nbCheckFormationPlayerSide @ 0x0026A468 (a signed compare: negative
// indexes count as player side)
bool isPlayerSide(int32_t formindex)
{
    return formindex < kPlayerFormations;
}

// nbHatudoCheckSkill @ 0x0026A3D8
//
// Bright Might works only under a full Kagutsuchi, Dark Might only under a
// new one; every other passive works whenever it is owned.
bool passiveActive(const UnitWork& unit, int32_t skill)
{
    if (!dat::hasSkill(unit, skill))
        return false;
    if (skill == skill::BrightMight) return evt::GetAgeOfMoon() == kMoonFull;
    if (skill == skill::DarkMight)   return evt::GetAgeOfMoon() == 0;
    return true;
}

// nbGetDevilFormatFlag @ 0x0026A7D0
uint32_t devilFormatFlag(int32_t formindex)
{
    UnitWork* unit = GetUnitWorkFromFormindex(formindex);
    if (!unit || unit->isPlayerCharacter())
        return 0;
    return dat::devilFormat(unit->id).flag;
}

// nbGetUnitID @ 0x00259A30
int32_t unitModelId(const UnitWork& unit)
{
    int32_t id = unit.isPlayerCharacter() ? 0 : unit.id;
    return unit.ailment() == ailment::Fly ? 255 : id;
}

// nbCheckSkillCost @ 0x00269170
//
// Muted units can't cast magic. Skills with NormalSkill::flag 4 cost
// nothing. HP skills need more HP than they cost (they can't kill the user).
SkillCheck checkSkillCost(int32_t formindex, int32_t skill)
{
    UnitWork& unit = *GetUnitWorkFromFormindex(formindex);
    skill = checkedSkill(skill);
    const NormalSkill& s = dat::normalSkill(skill);
    if (s.damageClass == 1 && unit.ailment() == ailment::Mute)
        return SkillCheck::Muted;
    if (s.flag & 4)
        return SkillCheck::Ok;
    if (s.costtype == 1)
        return dat::skillCost(unit, skill) >= unit.hp ? SkillCheck::NotEnoughHp : SkillCheck::Ok;
    if (s.costtype == 2)
        return unit.mp < dat::skillCost(unit, skill) ? SkillCheck::NotEnoughMp : SkillCheck::Ok;
    return SkillCheck::Ok;
}

// nbCheckSkillUse @ 0x00269280
int32_t checkSkillUse(int32_t formindex, int32_t skill)
{
    UnitWork& unit = *GetUnitWorkFromFormindex(formindex);
    skill = checkedSkill(skill);
    if (unit.ailment() == ailment::Mute && dat::normalSkill(skill).damageClass == 1)
        return 1;
    switch (checkSkillCost(formindex, skill)) {
    case SkillCheck::NotEnoughHp: return 2;
    case SkillCheck::NotEnoughMp: return 3;
    default:                      return 0;
    }
}

namespace {

// Shared by Endure and Never Yield. The party flags record that the skill
// fired (0x200) and that it is spent for this battle (0x400).
bool checkEndureSkill(int32_t formindex, int32_t skill)
{
    UnitWork& unit = *GetUnitWorkFromFormindex(formindex);
    if (!dat::hasSkill(unit, skill))
        return false;
    Party& party = *GetPartyFromFormindex(formindex);
    if (party.flag & PartyFlag::EndureSpent)
        return false;
    party.flag = static_cast<int16_t>(party.flag | PartyFlag::EndureFired);
    return true;
}

} // namespace

// nbCheckKuisibariSkill @ 0x0026A2D8 ("kuisibari" = 食いしばり, gritting one's teeth)
bool checkEndure(int32_t formindex) { return checkEndureSkill(formindex, skill::Endure); }

// nbCheckKuisibari2Skill @ 0x0026A338
bool checkNeverYield(int32_t formindex) { return checkEndureSkill(formindex, skill::NeverYield); }

// nbSetKuisibariStop @ 0x0026A398
void markEndureUsed(int32_t formindex)
{
    Party* party = GetPartyFromFormindex(formindex);
    if (party && (party->flag & PartyFlag::EndureFired))
        party->flag = static_cast<int16_t>(party->flag | PartyFlag::EndureSpent);
}

// nbGetNakama @ 0x00259180: the devil enters the stock (unit 4, or the
// first free one after it) and the compendium, and goes last in the
// stock's order. False when the stock is full. (The original also looks
// the devil up in the stock and ignores the answer.)
bool recruitDevil(const UnitWork& s)
{
    if (dat::isStockFull())
        return false;
    GlobalWork& global = dat::globalWork();
    int32_t slot = 4;
    UnitWork* unit = &global.units[slot];
    if (unit->flag & UnitFlag::Valid) {
        unit = nullptr;
        for (slot = 5; slot < 16; ++slot) {
            if (!(global.units[slot].flag & UnitFlag::Valid)) {
                unit = &global.units[slot];
                break;
            }
        }
    }
    dat::initDevil(s.id, *unit);
    fcl::record(*unit, false);
    global.stock_list[global.stock_count] = static_cast<uint8_t>(slot);
    ++global.stock_count;
    return true;
}

// nbSetDevilNameMes @ 0x00259268
void setDevilNameVariable(int32_t hmsg, int32_t no, const UnitWork& work)
{
    if (work.id == 0)
        mes::SetVarFormatted(hmsg, 0, 0, mes::kVarCharacter);
    else
        mes::SetVarFormatted(hmsg, no, work.id, mes::kVarDevil);
}

// nbAppendEnemyDevilWork @ 0x002594B0: the first free of the 10 enemy
// units becomes the devil, in the party, with its HP and MP from its
// format.
int32_t addEnemyUnit(MainProcessData& data, int32_t id)
{
    int32_t index = 0;
    while (index < 10 && (data.enemyunit.get()[index].flag & UnitFlag::Valid))
        ++index;
    if (index == 10)
        return -1;
    UnitWork& unit = data.enemyunit.get()[index];
    dat::initDevil(static_cast<uint16_t>(id), unit);
    const DevilFormat& format = dat::devilFormat(id);
    unit.flag |= UnitFlag::InParty;
    unit.maxhp = format.maxhp;
    unit.hp = format.hp;
    unit.maxmp = format.maxmp;
    unit.mp = format.mp;
    return index;
}

// nbGetRandamStock @ 0x002595A0: a stock devil not in the party, not
// already out (flag 0x10), alive and with HP left.
bool summonableStock(const UnitWork& unit)
{
    return (unit.flag & UnitFlag::Valid) && !(unit.flag & UnitFlag::InParty) && !(unit.flag & 0x10) &&
           unit.ailment() != static_cast<uint16_t>(Ailment::Dead) && unit.hp != 0;
}

int32_t randomSummonableStock()
{
    int32_t candidates[16];
    uint32_t count = 0;
    const GlobalWork& global = dat::globalWork();
    for (int32_t i = 0; i < 16; ++i)
        if (summonableStock(global.units[i]))
            candidates[count++] = i;
    return count ? candidates[sdf::GetRandInt(static_cast<int32_t>(count))] : -1;
}

// nbClearCommandMemeoyRenzoku @ 0x002596D0: before a consecutive battle
// ("renzoku"), the party's remembered targets on the other side are
// forgotten.
void forgetChainTargets()
{
    for (int32_t formindex = 0; formindex < 4; ++formindex) {
        UnitWork* unit = GetUnitWorkFromFormindex(formindex);
        if (unit && unit->prevtarea == 2) {
            unit->prevtform = -1;
            unit->prevtarea = -1;
        }
    }
}

// nbCheckEventDead @ 0x00259AB0
bool diesByEvent(const Formation& form)
{
    const int32_t id = unitModelId(*GetUnitWorkFromFormindex(form.formindex));
    if (id == 0)
        return false;
    return dat::aiRecord(id).deathScript() != 0 || dat::aiRecord(id).deathEvent() != 0;
}

// nbCheckDeadScript @ 0x00259B10
int32_t hasDeathScript(const Formation& form)
{
    const int32_t id = unitModelId(*GetUnitWorkFromFormindex(form.formindex));
    return id == 0 ? 0 : dat::aiRecord(id).deathScript();
}

// nbCheckDeadEvent @ 0x00259B70
int32_t hasDeathEvent(const Formation& form)
{
    const int32_t id = unitModelId(*GetUnitWorkFromFormindex(form.formindex));
    return id == 0 ? 0 : dat::aiRecord(id).deathEvent();
}

// nbGetMotionEndType @ 0x0024D310: how one of the slot's unit's motions ends.
int32_t motionEndType(const Formation& form, int32_t motion)
{
    return unitVisual(*GetUnitWorkFromFormindex(form.formindex)).motion[motion].endtype;
}

// nbGetMotionEndData @ 0x0024D358
int32_t motionEndData(const Formation& form, int32_t motion)
{
    return unitVisual(*GetUnitWorkFromFormindex(form.formindex)).motion[motion].enddata;
}

} // namespace nocturne::nb

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::nb {

#if NOCTURNE_HARDTYPE
// nbCheckSkillCost @ 0x00269170 (and 0x2FE080, 0x2FE110), nbCheckSkillUse @
// 0x00269280 (and 0x2FDC20): the acting skill noted, if any (hardtype.hpp).
int32_t checkedSkill(int32_t skill)
{
    const uint16_t acting = hardtype::actingSkill();
    return acting != 0 ? acting : skill;
}
#else
// nbCheckSkillCost @ 0x00269170, nbCheckSkillUse @ 0x00269280: the skill asked about.
int32_t checkedSkill(int32_t skill) { return skill; }
#endif

} // namespace nocturne::nb
