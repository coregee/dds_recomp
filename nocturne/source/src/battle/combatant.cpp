// Questions about one combatant (original unit: nbCalc).
#include "nocturne/battle/combatant.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

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
    const NormalSkill& s = dat::normalSkill(skill);
    if (s.koukatype == 1 && unit.ailment() == ailment::Mute)
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
    if (unit.ailment() == ailment::Mute && dat::normalSkill(skill).koukatype == 1)
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

} // namespace nocturne::nb
