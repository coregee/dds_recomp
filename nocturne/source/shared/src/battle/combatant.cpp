// Questions about one combatant (original unit: nbCalc).
#include "nocturne/battle/combatant.hpp"

#include "nocturne/battle/calc.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/devil_ai.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/event/units.hpp"
#include "nocturne/external.hpp"
#include "nocturne/facility/compendium.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/build.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

namespace {
constexpr uint32_t kDemiFiendAnimation = addr(0x003493a0);   // uint8 per motion: the Demi-fiend model's animation
constexpr uint32_t kDevilAnimation = addr(0x0034f1c0);       // ... a devil model's
constexpr uint32_t kAnimationCount = addr(0x001ddba8);       // mdlGetNumOfCut: a model's animations (no C here yet)

constexpr int32_t kStand = 0, kAilingPose = 2, kTalkPose = 0xd, kSlump = 0x16, kSlumpAnimations = 0x17;

int32_t animationOf(const UnitWork& unit, int32_t motion)
{
    return guest::table<const uint8_t>(unitModelId(unit) == 0 ? kDemiFiendAnimation : kDevilAnimation)[motion];
}

evt::EventUnit& eventUnit(const Formation& form) { return *guest::table<evt::EventUnit>(form.hunit); }

// The model's motion control: +0x12 the animation playing, +0x1C its
// controller (+0x20 the speed).
int16_t playingAnimation(uint32_t model) { return *guest::table<const int16_t>(model + 0x12); }
ee::Float& playingSpeed(uint32_t model) { return *guest::table<ee::Float>(*guest::table<const uint32_t>(model + 0x1c) + 0x20); }
} // namespace

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

// nbCheckKuisibari2Skill @ 0x0026A338 (the first release has no Never Yield;
// its callers check Endure alone)
bool checkNeverYield(int32_t formindex) { return !kBuild.vanilla && checkEndureSkill(formindex, skill::NeverYield); }

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

// nbGetMotionSpeed @ 0x0024D428
ee::Float motionSpeed(const Formation& form, int32_t motion, ee::Float rate)
{
    const ee::Float speed = unitVisual(*GetUnitWorkFromFormindex(form.formindex)).motion[motion].speed;
    return rate == ee::Float::fromInt(1) ? speed : speed * rate;
}

// nbGetMotionActframe @ 0x0024D3A0
int32_t motionActFrame(const Formation& form, int32_t motion, ee::Float rate)
{
    const int32_t frame = unitVisual(*GetUnitWorkFromFormindex(form.formindex)).motion[motion].actframe;
    return (ee::Float::fromInt(frame) / motionSpeed(form, motion, rate)).toInt();
}

// nbGetMotionNo @ 0x0024D490
int32_t prepareMotion(Formation& form, int32_t motion)
{
    const UnitWork& unit = *GetUnitWorkFromFormindex(form.formindex);
    const UnitMotion& m = unitVisual(unit).motion[motion];
    form.cr = m.radius * form.scl;
    form.movey = m.movey;
    form.movez = m.movez;
    return animationOf(unit, motion);   // (the Demi-fiend's model numbers them its own way)
}

// GetDyingBadWaitMotion @ 0x0024CE78
int32_t posedMotion(const Formation& form, int32_t motion, const UnitWork& unit)
{
    if (GetMainProcessData()->stat & BattleStat::FixedPoses)
        return motion;
    if (dat::isDying(unit) && motion == kStand &&
        static_cast<int32_t>(guest::callOriginal(kAnimationCount, eventUnit(form).model, 0)) >= kSlumpAnimations)
        return kSlump;
    if (motion != kStand)
        return motion;
    switch (unit.badstat & 0xfff) {
    case ailment::Sleep:
    case ailment::Panic:
    case ailment::Mute:
    case ailment::Poison:
    case ailment::Charm:
    case ailment::Stun: return kAilingPose;
    default: return motion;
    }
}

// nbSetUnitMotion @ 0x0024CFF8
void startMotion(Formation& form, int32_t motion, int32_t mode, ee::Float rate)
{
    MainProcessData& main = *GetMainProcessData();
    const UnitWork& unit = *GetUnitWorkPointer(main, main.party[form.partyindex]);
    evt::EventUnit& handle = eventUnit(form);
    if (form.anime & 0x80)
        return;
    const UnitVisual& visual = unitVisual(unit);
    motion = posedMotion(form, motion, unit);
    const ee::Float speed = motionSpeed(form, motion, rate);
    const int32_t animation = prepareMotion(form, motion);

    // Blending in: the standing, ailing, talking, slumped and two other
    // motions from the frames left by the last; motion 1 over a frame, 0xE and
    // 0xF over 15 frames, the rest none.
    int32_t blendStart = 0, blendEnd = 0;
    switch (motion) {
    case 0: case 2: case 0xd: case 0x16: case 0x17:
        blendStart = form.blendStart;
        blendEnd = form.blendEnd;
        break;
    case 1: blendEnd = 1; break;
    case 0xe: case 0xf: blendEnd = 0xf; break;
    default: break;
    }
    const bool restartable = !(motion == kStand || motion == kAilingPose || motion == kTalkPose || motion == kSlump);
    if (restartable || playingAnimation(handle.model) != animation)
        evt::setUnitMotion(handle, animation, blendStart, blendEnd, mode);
    playingSpeed(handle.model) = speed;
    form.motionSpeed = speed;
    form.blendEnd = static_cast<int16_t>(visual.motion[motion].blendEnd);
    form.blendStart = static_cast<int16_t>(visual.motion[motion].blendStart);
    if (mode == 0 || mode == 3) {
        evt::setWaitBlend(handle, form.blendStart, form.blendEnd);
        form.blendEnd = static_cast<int16_t>(visual.motion[form.waitMotion].blendEnd);
        form.blendStart = static_cast<int16_t>(visual.motion[form.waitMotion].blendStart);
    }
}

// nbSetWaitMotion @ 0x0024D238
void setWaitMotion(Formation& form, int32_t motion, ee::Float rate)
{
    const UnitWork& unit = *GetUnitWorkFromFormindex(form.formindex);
    motion = posedMotion(form, motion, unit);
    const int32_t animation = animationOf(unit, motion);
    const ee::Float speed = unitVisual(unit).motion[motion].speed * rate;
    evt::setWaitMotion(eventUnit(form), animation);
    evt::setWaitSpeed(eventUnit(form), speed);
    form.waitMotion = static_cast<int16_t>(motion);
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
