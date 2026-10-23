// One unit's action as a process (original unit: nbActionProcess).
// Rewritten from the original instructions.
#include "nocturne/battle/action.hpp"

#include "nocturne/battle/ai.hpp"
#include "nocturne/battle/ai_script.hpp"
#include "nocturne/battle/bad_ai.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

// ---- the time list -----------------------------------------------------------------------------

// ClearTimeList @ 0x002514F0
void ClearTimeList(ActionProcessData& a)
{
    for (TimeList& t : a.timelist) {
        t.lockframe = 0;
        t.endframe = 0;
        t.hp = 0;
    }
}

// SetHpForTimeList @ 0x00251538: the HP now of each slot's unit (0 for an
// empty slot). Sixteen slots are read, two past the formation array.
void SetHpForTimeList(ActionProcessData& a)
{
    for (int i = 0; i < 16; ++i) {
        MainProcessData& main = *a.data;
        a.timelist[i].hp = 0;
        const Formation& form = main.form[i];
        if ((form.stat & FormationStat::Present) && (form.stat & FormationStat::CheckParty))
            a.timelist[i].hp = GetUnitWorkPointer(main, main.party[form.partyindex])->hp;
    }
}

// GetTimeListHp @ 0x002515D8
int32_t GetTimeListHp(ActionProcessData& a, int32_t formindex) { return a.timelist[formindex].hp; }

// CheckTimeListDead @ 0x002515E8: at 0 HP, unless the devil can't die (format flag 0x100).
bool CheckTimeListDead(ActionProcessData& a, int32_t formindex)
{
    return a.timelist[formindex].hp == 0 && !(devilFormatFlag(formindex) & 0x100);
}

// CheckTimeListDeadEnemyParty @ 0x00251628: every unit on the other side
// of `formindex` dead.
bool CheckTimeListDeadEnemyParty(ActionProcessData& a, int32_t formindex)
{
    const int32_t first = formindex < kPlayerFormations ? kFirstEnemyFormation : 0;
    const int32_t count = formindex < kPlayerFormations ? 10 : 4;
    for (int32_t i = first; i < first + count; ++i)
        if ((a.data->form[i].stat & FormationStat::Present) && !CheckTimeListDead(a, i))
            return false;
    return true;
}

// nbAddTimeListHp @ 0x002516E8: true when the unit's HP reached 0. Nothing
// changes while the battle's stat bit 0x20000 is set.
bool nbAddTimeListHp(ActionProcessData& a, int32_t formindex, int32_t add)
{
    if (a.data->stat & 0x20000)
        return false;
    uint16_t& hp = a.timelist[formindex].hp;
    const int32_t value = hp + add;
    if (value < 0) {
        hp = 0;
        return true;
    }
    hp = static_cast<uint16_t>(value);
    return false;
}

// AddTimeListHp @ 0x00251738
bool AddTimeListHp(ActionProcessData& a, int32_t formindex, int32_t add) { return nbAddTimeListHp(a, formindex, add); }

// GetUnlockTime @ 0x00251750
int32_t GetUnlockTime(ActionProcessData& a, int32_t formindex) { return a.timelist[formindex].lockframe; }

// GetEndTime @ 0x00251760
int32_t GetEndTime(ActionProcessData& a, int32_t formindex) { return a.timelist[formindex].endframe; }

// OverwriteTimeList @ 0x00251770: the unit is busy until start + locktime
// and done at start + endtime (negative: unchanged), never earlier than
// before; done is never before free.
void OverwriteTimeList(ActionProcessData& a, int32_t formindex, int32_t start, int32_t locktime, int32_t endtime)
{
    TimeList& t = a.timelist[formindex];
    if (locktime >= 0 && t.lockframe < start + locktime)
        t.lockframe = static_cast<uint16_t>(start + locktime);
    if (endtime >= 0) {
        if (t.endframe < start + endtime)
            t.endframe = static_cast<uint16_t>(start + endtime);
        if (t.endframe < t.lockframe)
            t.endframe = t.lockframe;
    }
}

// SetTimeList @ 0x002517E0: the same, starting no earlier than the unit is free.
void SetTimeList(ActionProcessData& a, int32_t formindex, int32_t start, int32_t locktime, int32_t endtime)
{
    TimeList& t = a.timelist[formindex];
    if (start < t.lockframe)
        start = t.lockframe;
    if (locktime >= 0 && t.lockframe < start + locktime)
        t.lockframe = static_cast<uint16_t>(start + locktime);
    if (endtime >= 0) {
        if (t.endframe < start + endtime)
            t.endframe = static_cast<uint16_t>(start + endtime);
        if (t.endframe < t.lockframe)
            t.endframe = t.lockframe;
    }
}

// GetAllEndTime @ 0x00251858: when the last unit is done.
int32_t GetAllEndTime(ActionProcessData& a)
{
    uint16_t latest = 0;
    for (const TimeList& t : a.timelist)
        if (latest < t.endframe)
            latest = t.endframe;
    return latest;
}

// GetAllUnlockTime @ 0x00251890: when the last unit is free.
int32_t GetAllUnlockTime(ActionProcessData& a)
{
    uint16_t latest = 0;
    for (const TimeList& t : a.timelist)
        if (latest < t.lockframe)
            latest = t.lockframe;
    return latest;
}

// ---- the state ------------------------------------------------------------------------------

// nbGetActionSeq @ 0x00257BF8
int32_t nbGetActionSeq(uint32_t process)
{
    if (!process)
        return 0;
    return guest::table<ActionProcessData>(dds3::GetProcessData(process))->seq;
}

// nbGetPrevActionSeq @ 0x00257C20: the action processes form a ring of 4.
int32_t nbGetPrevActionSeq()
{
    const MainProcessData& main = *GetMainProcessData();
    int32_t prev = main.NowActionProcess - 1;
    if (prev < 0)
        prev = 3;
    const uint32_t process = main.ActionProcessID[prev];
    return process ? nbGetActionSeq(process) : -1;
}

// SetNextActionSeq @ 0x00257CC8
void SetNextActionSeq(ActionProcessData& a, int32_t nextseq) { a.nextseq = static_cast<int8_t>(nextseq); }

// SetAction_NON @ 0x00253488
void SetAction_NON(ActionProcessData&) {}

// SetAction_AI @ 0x00253BF8: the table AI chooses the unit's command.
void SetAction_AI(ActionProcessData& a)
{
    UnitWork& unit = *a.work;
    unit.nowcommand = -1;
    unit.nowindex = 0;
    ai::run(a);
}

// CheckAction_AI @ 0x00253C20: the AI has chosen; on to READY.
int32_t CheckAction_AI(ActionProcessData& a)
{
    SetNextActionSeq(a, kActionReady);
    return 1;
}

// SetAction_AISCR @ 0x00253C40: the devil's AI script chooses instead.
void SetAction_AISCR(ActionProcessData& a)
{
    UnitWork& unit = *a.work;
    unit.nowcommand = -1;
    unit.nowindex = 0;
    ai::script::start(a, dat::devilAI(unit.id).scriptid);
}

// CheckAction_AISCR @ 0x00253C88: waits for the script to end; on to
// READY, or to the talks' result if it started talks.
int32_t CheckAction_AISCR(ActionProcessData& a)
{
    if (dds3::ExistProcess(a.data->AiScriptProcessID))
        return 0;
    MainProcessData& main = *a.data;
    main.AiScriptProcessID = 0;
    if (!main.negoresult) {
        SetNextActionSeq(a, kActionReady);
    } else {
        ClearTimeList(a);
        SetHpForTimeList(a);
        SetNextActionSeq(a, kActionNegoResult);
    }
    return 1;
}

// CheckAction_BAD @ 0x00253E00: the unit's ailment at the start of its
// turn. Shock, freeze, sleep, bind and stone cost the turn (a press turn
// icon): shock and freeze then wear off, and sleep restores an eighth of HP
// and MP. A charmed or panicked unit, or a cursed one, acts by the ailment AI
// (bad_ai.hpp) and goes on to BADWAIT; otherwise the unit acts normally.
int32_t CheckAction_BAD(ActionProcessData& a)
{
    ClearTimeList(a);
    SetHpForTimeList(a);
    a.jyokyomes = 0;
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    const auto loseTurn = [&] {
        nbMakePressPacket(0, uniqueid, ee::Float::fromInt(-1));
        nbMakeNewPressPacket(0, uniqueid, 0);
    };
    switch (badStat(a.form->formindex)) {
    case static_cast<uint32_t>(Ailment::Panic):
    case static_cast<uint32_t>(Ailment::Charm):
        nbRunBadAi(a);
        SetNextActionSeq(a, kActionBadWait);
        return 1;
    case static_cast<uint32_t>(Ailment::Shock):
    case static_cast<uint32_t>(Ailment::Freeze):
        loseTurn();
        nbMakeBadKaifukuPacket(5, uniqueid, *a.form);
        break;
    case static_cast<uint32_t>(Ailment::Sleep):
        loseTurn();
        nb::MakeKaifukuPacket(10, uniqueid, a.form.get(), 0, a.work->maxhp >> 3, a.work->maxmp >> 3, 0);
        break;
    case static_cast<uint32_t>(Ailment::Bind):
    case static_cast<uint32_t>(Ailment::Stone):
        loseTurn();
        break;
    default:
        if (isCursed(a.form->formindex)) {
            nbRunBadAi(a);
            SetNextActionSeq(a, kActionBadWait);
        }
        return 1;
    }
    if (a.data->stat & BattleStat::InitiativeRolled)
        nbCameraSetState(kCameraEnemyBad);
    SetTimeList(a, a.form->formindex, 0, 30, 30);
    SetNextActionSeq(a, kActionCheck1);
    return 1;
}

// SetAction_BADWAIT @ 0x00254010: the camera on the ailing unit.
void SetAction_BADWAIT(ActionProcessData& a)
{
    a.stat |= 0x20;
    nbCameraSetState((a.data->stat & BattleStat::InitiativeRolled) ? kCameraEnemyBad : kCameraCommandBad);
}

// CheckAction_BADWAIT @ 0x00254058: shows the ailment AI's status line at
// frame 5 and waits, then on to READY: until frame 31 for a lost turn (8)
// or the curse's damage (10), else until the status line has gone or frame
// 41.
int32_t CheckAction_BADWAIT(ActionProcessData& a)
{
    if (a.seqtime == 5 && a.jyokyomes > 0)
        nb::DispJyokyoHelp(a.data->jyokyomsgid, a.jyokyomes, a.jyo_varid, a.jyo_varind);
    bool done;
    switch (a.work->nowcommand) {
    case 8:
    case 10: done = a.seqtime >= 31; break;
    default: done = a.seqtime >= 41 || a.jyokyomes == 0; break;
    }
    if (done) {
        SetNextActionSeq(a, kActionReady);
        a.jyokyomes = 0;
    }
    return done ? 1 : 0;
}

// SetAction_DEADSCRIPT @ 0x00253D00: runs a dying unit's script (the
// procedure is in adata).
void SetAction_DEADSCRIPT(ActionProcessData& a)
{
    ClearTimeList(a);
    SetHpForTimeList(a);
    ai::script::start(a, a.adata);
}

// CheckAction_DEADSCRIPT @ 0x00253D38: once the script ends, the unit
// fades out and leaves; on to CHECK1.
int32_t CheckAction_DEADSCRIPT(ActionProcessData& a)
{
    if (dds3::ExistProcess(a.data->AiScriptProcessID))
        return 0;
    a.data->AiScriptProcessID = 0;
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    nbMakeUnitFadeOutPacket(0, uniqueid, a.form.get(), 0, 10, 10, 10);
    nbAddReturnKoukaPacket(25, uniqueid, a.party.get(), 1);
    SetTimeList(a, a.form->formindex, 0, 30, 30);
    SetNextActionSeq(a, kActionCheck1);
    return 1;
}

// SetAction_WAIT @ 0x002570B8: the unit passes (half a press turn icon),
// loses its turn to an ailment, or takes the curse's damage (15% of its
// maximum HP).
void SetAction_WAIT(ActionProcessData& a)
{
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    switch (a.work->nowcommand) {
    case 3:   // pass
        nbMakePressPacket(0, uniqueid, ee::Float::fromBits(0xbf000000));   // -0.5
        nbMakeNewPressPacket(0, uniqueid, 1);
        SetTimeList(a, a.form->formindex, 0, 5, 5);
        break;
    case 8:   // an ailment took the turn
        nbMakePressPacket(0, uniqueid, ee::Float::fromInt(-1));
        nbMakeNewPressPacket(0, uniqueid, 0);
        SetTimeList(a, a.form->formindex, 0, 5, 5);
        break;
    case 10:  // the curse's damage
        nb::SetDamagePacket(a, static_cast<int32_t>(static_cast<uint32_t>(a.work->maxhp) * 15u / 100u));
        nbMakePressPacket(0, uniqueid, ee::Float::fromInt(-1));
        nbMakeNewPressPacket(0, uniqueid, 0);
        break;
    default:
        break;
    }
}

// CheckAction_WAIT @ 0x00257210
int32_t CheckAction_WAIT(ActionProcessData& a)
{
    SetNextActionSeq(a, kActionCheck1);
    return 1;
}

// SetAction_ESCAPE @ 0x00257230: one more attempt; all the press turns go.
// A successful escape ends the battle (endtype 3); a failed one may give an
// enemy a free action.
void SetAction_ESCAPE(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    if (main.esccnt != 0xff)
        ++main.esccnt;
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    nbMakePressPacket(0, uniqueid, ee::Float::fromInt(-10));
    nbMakeNewPressPacket(0, uniqueid, 8);
    if (rollEscape(*a.data))
        a.data->endtype = 3;
    else
        nb::EscapeFailed(a);
}

// CheckAction_ESCAPE @ 0x002572C0: at frame 15 a failed escape is done; at
// frame 30 a successful one fades the screen to white with a sound.
int32_t CheckAction_ESCAPE(ActionProcessData& a)
{
    switch (a.seqtime / 15) {
    case 1:
        if (a.data->endtype == 3)
            return 0;
        a.packettime = 0;
        break;
    case 2:
        if (a.data->endtype != 3)
            return 0;
        a.packettime = 30;
        dds3::FadeOut(255, 255, 255, 20);
        nbAddSePacket(0, static_cast<int32_t>(guest::addressOf(&a)), 0x10000);
        SetTimeList(a, a.form->formindex, 0, 17, 17);
        break;
    default:
        return 0;
    }
    SetNextActionSeq(a, kActionCheck1);
    return 1;
}

// SetAction_RETURN @ 0x002573A8: a devil goes back to the stock (half a
// press turn icon).
void SetAction_RETURN(ActionProcessData& a)
{
    diag::print(diag::Message::Returning);
    if (a.data->stat & BattleStat::InitiativeRolled)
        nbCameraSetState(kCameraEnemySide);
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    nbMakeReturnPacket(0, uniqueid, *a.party);
    SetTimeList(a, a.form->formindex, 0, 40, 40);
    nbMakePressPacket(10, uniqueid, ee::Float::fromBits(0xbf000000));   // -0.5
    nbMakeNewPressPacket(10, uniqueid, 9);
}

// CheckAction_RETURN @ 0x00257440
int32_t CheckAction_RETURN(ActionProcessData& a)
{
    SetNextActionSeq(a, kActionCheck1);
    return 1;
}

// CheckAction_NEGO @ 0x00256B88: waits for the talks to end; on to their
// result (a dead Demi-fiend's talks end with result 8).
int32_t CheckAction_NEGO(ActionProcessData& a)
{
    if (a.data->NegoProcessID)
        return 0;
    diag::print(diag::Message::NegoResult, a.data->negoresult);
    SetNextActionSeq(a, kActionNegoResult);
    nb::PanelSetEnabled(true);
    if (dat::isPlayerDead())
        a.data->negoresult = 8;
    return 1;
}

// CheckAction_NEGORESULT @ 0x00257098
int32_t CheckAction_NEGORESULT(ActionProcessData& a)
{
    SetNextActionSeq(a, kActionCheck1);
    return 1;
}

// SetAction_INVISIBLE @ 0x00257460
void SetAction_INVISIBLE(ActionProcessData&) {}

// CheckAction_INVISIBLE @ 0x00257468
int32_t CheckAction_INVISIBLE(ActionProcessData& a)
{
    SetNextActionSeq(a, kActionCheck1);
    return 1;
}

// SetAction_CHECK3 @ 0x00257A68
void SetAction_CHECK3(ActionProcessData&) {}

// CheckAction_CHECK3 @ 0x00257A70: waits until the action's packets are all played.
int32_t CheckAction_CHECK3(ActionProcessData& a)
{
    if (nbGetUniqueIdKoukaPacketCnt(static_cast<int32_t>(guest::addressOf(&a))) > 0)
        return 0;
    SetNextActionSeq(a, kActionAto);
    return 1;
}

// SetAction_ATO @ 0x00257AB8 ("ato": after)
void SetAction_ATO(ActionProcessData&) {}

// CheckAction_ATO @ 0x00257AC0: frees the skill's effect.
int32_t CheckAction_ATO(ActionProcessData& a)
{
    if (a.hEffBTL) {
        eff::BTLDelete(a.hEffBTL);
        a.hEffBTL = 0;
    }
    SetNextActionSeq(a, kActionEnd);
    return 1;
}

// SetAction_END @ 0x00257B08: debug messages for what the action did
// (its stat bits 0x10000 .. 0x200000).
void SetAction_END(ActionProcessData& a)
{
    static constexpr diag::Message messages[] = {
        diag::Message::DidPhysical, diag::Message::DidMagicAttack, diag::Message::DidHeal,
        diag::Message::DidMagic,    diag::Message::DidItem,        diag::Message::DidSummon,
    };
    for (int i = 0; i < 6; ++i)
        if (a.stat & 0x10000u << i)
            diag::print(messages[i]);
}

// CheckAction_END @ 0x00257BF0
int32_t CheckAction_END(ActionProcessData&) { return 1; }

} // namespace nocturne::nb
