// One unit's action as a process (original unit: nbActionProcess).
// Rewritten from the original instructions.

#include <cstring>

#include "nocturne/address.hpp"
#include "nocturne/battle/action.hpp"
#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/ai.hpp"
#include "nocturne/battle/ai_script.hpp"
#include "nocturne/battle/bad_ai.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/comm_select.hpp"
#include "nocturne/battle/damage.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/order.hpp"
#include "nocturne/battle/pad.hpp"
#include "nocturne/battle/skill_error.hpp"
#include "nocturne/battle/sound.hpp"
#include "nocturne/battle/target_select.hpp"
#include "nocturne/battle/targeting.hpp"
#include "nocturne/build.hpp"
#include "nocturne/data/devil_ai.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/effect/boss.hpp"
#include "nocturne/effect/cut.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"
#include "nocturne/interface/font.hpp"
#include <algorithm>
#include <cstdio>
#include <utility>

namespace nocturne::nb {

// ---- the time list -----------------------------------------------------------------------------

// ClearTimeList @ 0x002514F0
void clearTimeList(ActionProcessData& a)
{
    for (TimeList& t : a.timelist) {
        t.lockframe = 0;
        t.endframe = 0;
        t.hp = 0;
    }
}

// SetHpForTimeList @ 0x00251538: the HP now of each slot's unit (0 for an
// empty slot). Sixteen slots are read, two past the formation array.
void initTimeListHp(ActionProcessData& a)
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
int32_t timeListHp(ActionProcessData& a, int32_t formindex) { return a.timelist[formindex].hp; }

// CheckTimeListDead @ 0x002515E8: at 0 HP, unless the devil can't die (format flag 0x100).
bool timeListDead(ActionProcessData& a, int32_t formindex)
{
    return a.timelist[formindex].hp == 0 && !(devilFormatFlag(formindex) & 0x100);
}

// CheckTimeListDeadEnemyParty @ 0x00251628: every unit on the other side
// of `formindex` dead.
bool otherSideAllDead(ActionProcessData& a, int32_t formindex)
{
    const int32_t first = formindex < kPlayerFormations ? kFirstEnemyFormation : 0;
    const int32_t count = formindex < kPlayerFormations ? 10 : 4;
    for (int32_t i = first; i < first + count; ++i)
        if ((a.data->form[i].stat & FormationStat::Present) && !timeListDead(a, i))
            return false;
    return true;
}

// nbAddTimeListHp @ 0x002516E8: true when the unit's HP reached 0. Nothing
// changes while the battle's stat bit 0x20000 is set.
bool addTimeListHp(ActionProcessData& a, int32_t formindex, int32_t add)
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
bool addTimeListHpAt(ActionProcessData& a, int32_t formindex, int32_t add) { return addTimeListHp(a, formindex, add); }

// GetUnlockTime @ 0x00251750
int32_t freeFrame(ActionProcessData& a, int32_t formindex) { return a.timelist[formindex].lockframe; }

// GetEndTime @ 0x00251760
int32_t doneFrame(ActionProcessData& a, int32_t formindex) { return a.timelist[formindex].endframe; }

// OverwriteTimeList @ 0x00251770: the unit is busy until start + locktime
// and done at start + endtime (negative: unchanged), never earlier than
// before; done is never before free.
void overwriteTimeList(ActionProcessData& a, int32_t formindex, int32_t start, int32_t locktime, int32_t endtime)
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
void setTimeList(ActionProcessData& a, int32_t formindex, int32_t start, int32_t locktime, int32_t endtime)
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
int32_t lastDoneFrame(ActionProcessData& a)
{
    uint16_t latest = 0;
    for (const TimeList& t : a.timelist)
        if (latest < t.endframe)
            latest = t.endframe;
    return latest;
}

// GetAllUnlockTime @ 0x00251890: when the last unit is free.
int32_t lastFreeFrame(ActionProcessData& a)
{
    uint16_t latest = 0;
    for (const TimeList& t : a.timelist)
        if (latest < t.lockframe)
            latest = t.lockframe;
    return latest;
}

// ---- an action's results ---------------------------------------------------------------------

namespace {

int32_t uniqueOf(ActionProcessData& a) { return static_cast<int32_t>(guest::addressOf(&a)); }
Formation& formAt(ActionProcessData& a, int32_t formindex) { return a.data->form[formindex]; }

constexpr uint16_t kPartyGone = 0x20;   // tentative: the unit has left the battle

} // namespace

// UnitKyoseiDisp @ 0x0024F420: a hidden unit fades back in.
void fadeInHiddenUnit(ActionProcessData& a, int32_t start)
{
    if (a.form->motionend == 2) {
        makeFadeInPackets(start, uniqueOf(a), a.form.get(), 0, 2, 4, 4);
        a.form->motionend = 0;
    }
}

// SetDeadPacket @ 0x0024F478: a unit dies when its last packet ends; an
// enemy leaves its rewards.
void queueDeath(ActionProcessData& a, int32_t formindex)
{
    Party& party = a.data->party[formAt(a, formindex).partyindex];
    if (party.flag & kPartyGone)
        return;
    const int32_t start = doneFrame(a, formindex);
    const UnitWork& unit = *GetUnitWorkPointer(*a.data, party);
    if (unit.isEnemy())
        addDefeatRewards(unit);
    makeDeathPackets(start, uniqueOf(a), formAt(a, formindex), 0);
}

// SetPress @ 0x0024F548: the action's press turn cost, the worst result
// kept. Below -1 (more than a whole icon) the larger loss wins; above -1 a
// larger value wins unless more than an icon is already lost; -1 or a
// smaller gain only fills an empty (0) cost.
void setPressCost(ActionProcessData& a, ee::Float press)
{
    const ee::Float one = ee::Float::fromInt(-1);
    if (press < one) {
        if (press < a.press)
            a.press = press;
        return;
    }
    if (one < press) {
        if (!(one <= a.press))
            return;
        if (a.press < press) {
            a.press = press;
            return;
        }
    }
    if (a.press == ee::Float::fromBits(0))
        a.press = press;
}

// SetNewPress @ 0x0024F5B0: the press turn result type, the highest kept.
void setPressResult(ActionProcessData& a, int32_t presstype)
{
    if (a.newpresstype < presstype)
        a.newpresstype = presstype;
}

// SetHitStopFrame @ 0x0024F5C8: the earliest hit, plus 7 frames.
void setHitStopFrame(ActionProcessData& a, int32_t frame)
{
    const int32_t stop = frame + 7;
    if (a.hitstopframe == 0 || stop < a.hitstopframe)
        a.hitstopframe = stop;
}

// SetEnemyEscapePacket @ 0x0024F5F0: an enemy runs away.
void queueEnemyEscape(ActionProcessData& a, int32_t dformindex, int32_t sframe)
{
    makeReturnPackets(sframe, uniqueOf(a), *GetPartyFromFormindex(dformindex));
    setTimeList(a, dformindex, sframe, 30, 30);
}

// SetAuroraPacket @ 0x0024F658: turns the unit's affinities through rows
// 0xF8 .. 0xFB of the affinity table (buff counter 19); other rows stay.
void queueAurora(ActionProcessData& a, int32_t dformindex, int32_t)
{
    GetPartyFromFormindex(dformindex);
    const int32_t type = static_cast<int32_t>(BuffKind::AffinityRow);
    int32_t row = buffCounter(dformindex, type);
    switch (row) {
    case 0: row = 0xf8; break;
    case 0xf8: row = 0xf9; break;
    case 0xf9: row = 0xfa; break;
    case 0xfa: row = 0xfb; break;
    case 0xfb: row = 0xf8; break;
    default: break;
    }
    setBuffCounter(dformindex, type, row);
    setStatusMessage(a, 0x5a, 1, GetUnitWorkFromFormindex(dformindex)->id);
}

// SetAddPressPacket @ 0x0024F728: a skill that grants press turns
// (program 13): 2, 3 or 4 icons (hojopoint) are result types 15, 17, 16.
void queueExtraPress(ActionProcessData& a, int32_t nskill)
{
    const NormalSkill& skill = dat::normalSkill(nskill);
    if (skill.program != 13)
        return;
    switch (skill.buffAmount) {
    case 2: a.newaddpresstype = 15; break;
    case 3: a.newaddpresstype = 17; break;
    case 4: a.newaddpresstype = 16; break;
    default: break;
    }
}

// SetAddFlareChargePacket @ 0x0024F7B8
void queueFlareCharge(ActionProcessData& a, int32_t start) { addFlareChargePacket(start, uniqueOf(a), 2); }

// SetMakaPacket @ 0x0024F7E0: Macca thrown (BadMaka): the player's side
// loses it (no more than it has), an enemy's throw gives it.
void queueMaccaThrow(ActionProcessData& a, int32_t, int32_t sframe)
{
    int32_t amount = scatteredMacca(*a.work);
    if (isPlayerSide(a.form->formindex) && dat::globalWork().macca < amount)
        amount = dat::globalWork().macca;
    setTimeList(a, a.form->formindex, sframe, 30, 30);
#if !NOCTURNE_US && !NOCTURNE_CHRONICLE   // (JP Maniax's debug print)
    diag::print(diag::Message::MaccaScattered, amount);
#endif
    setStatusMessage(a, 0x2c, 0, amount);
    dat::addMacca(isPlayerSide(a.form->formindex) ? -amount : amount);
}

// SetTorafuPacket @ 0x0024F8A8: a Trafuri-like escape: the unit fades out
// and the battle ends (endtype 3).
void queueTrafuri(ActionProcessData& a, int32_t dformindex, int32_t sframe)
{
    Formation& form = formAt(a, dformindex);
    makeFadeOutPackets(sframe, uniqueOf(a), &form, 0, 6, 6, 6);
    addFormationShowPacket(sframe + 12, uniqueOf(a), &form, 0);
    a.data->endtype = 3;
}

// SetAnalyzePacket @ 0x0024F938
void queueAnalyze(ActionProcessData& a, int32_t dformindex, int32_t sframe)
{
    addAnalyzePacket(sframe + 2, uniqueOf(a), &formAt(a, dformindex));
    nb::PanelAnalyzeStart();
    a.stat |= 0x10;
}

// SetPlayerSummonPacket @ 0x0024F990: a devil called into slot dformindex.
// An enemy calls one of its kind into a new enemy unit (one fewer call
// allowed); the player's side summons a stock devil, or a random one for
// skill 0xDF (none: "no one answered", message 0x3E, and false).
int32_t queuePlayerSummon(ActionProcessData& a, int32_t, int32_t, int32_t dformindex, int32_t sframe)
{
    const bool enemy = (a.party->flag & PartyFlag::EnemySide) != 0;
    int32_t stock;
    if (enemy) {
        stock = addEnemyUnit(*a.data, static_cast<int32_t>(a.aisummonid));
        if (a.data->summonallowed > 0)
            --a.data->summonallowed;
    } else {
        const UnitWork& unit = *a.work;
        stock = unit.nowindex;
        if (unit.nowcommand == 1 && unit.nowindex == 0xdf) {
            stock = randomSummonableStock();
            if (stock < 0) {
                setStatusMessage(a, 0x3e, -1, 0);
                return 0;
            }
        }
    }
    makeSummonPackets(sframe, uniqueOf(a), enemy ? 1 : 0, static_cast<int16_t>(stock), static_cast<int16_t>(dformindex));
    setTimeList(a, a.form->formindex, sframe, 15, 20);
    const uint32_t units = enemy ? a.data->enemyunit.address : guest::addressOf(&dat::globalWork().units[0]);
    const UnitWork& summoned = *guest::table<UnitWork>(units + static_cast<uint32_t>(stock) * sizeof(UnitWork));
    a.timelist[dformindex].hp = summoned.hp;
    setStatusMessage(a, enemy ? 0x40 : 8, 1, summoned.id);
    return 1;
}

// SetSakePacket @ 0x0024FB38: a dodge: two press turn icons lost; a
// single-target skill says "dodged" (message 2 on the player's side, 4 on
// the enemy's).
void queueDodge(ActionProcessData& a, int32_t nskill, int32_t, int32_t dformindex, int32_t, int32_t frame)
{
    addDodgePacket(frame, uniqueOf(a), formAt(a, dformindex));
    setHitStopFrame(a, frame);
    setTimeList(a, dformindex, frame, 10, 20);
    if (isSingleTargetSkill(nskill))
        setStatusMessage(a, isPlayerSide(dformindex) ? 2 : 4, -1, 0);
    setPressCost(a, ee::Float::fromInt(-2));
    setPressResult(a, 4);
}

// SetMissPacket @ 0x0024FC28: a miss ("Miss", word 3): two icons lost.
void queueMiss(ActionProcessData& a, int32_t, int32_t, int32_t dformindex, int32_t, int32_t frame)
{
    addWordPacket(frame, 0x2d, uniqueOf(a), &formAt(a, dformindex), 3);
    setTimeList(a, dformindex, frame, 10, 20);
    setPressCost(a, ee::Float::fromInt(-2));
    setPressResult(a, 4);
}

// SetOngShadowPacket @ 0x0024FCC0: an attack found the real Ongyo-Ki
// among his clones ("Miss" shown as word 4): he leaves and dies, and the
// clones stagger (motion 14). Two icons lost (result type 14).
void queueOngyokiFound(ActionProcessData& a, int32_t, int32_t, int32_t dformindex, int32_t, int32_t frame)
{
#if !NOCTURNE_US && !NOCTURNE_CHRONICLE   // (JP Maniax's debug print)
    diag::print(diag::Message::OngyoKiShadowOne);
#endif
    Formation& form = formAt(a, dformindex);
    addWordPacket(frame, 0x2d, uniqueOf(a), &form, 4);
    addOngyokiOutPacket(frame, uniqueOf(a), &form);
    addUnitAlphaPacket(frame + 1, uniqueOf(a), &form, 0, 0);
    makeDeathPackets(frame + eff::ongyokiEffectLength(), uniqueOf(a), form, 1);
    setTimeList(a, dformindex, frame, 30, 30);
    const int32_t after = frame + eff::ongyokiEffectLength();
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        if (f == dformindex)
            continue;
        Formation& clone = formAt(a, f);
        if ((clone.stat & FormationStat::Present) && (clone.stat & FormationStat::Shadow)) {
            addMotionPacket(after, uniqueOf(a), &clone, 14);
            setTimeList(a, f, after, 20, 20);
        }
    }
    setPressCost(a, ee::Float::fromInt(-2));
    setPressResult(a, 14);
}

// SetOngShadowPacket2 @ 0x0024FE40: the other clones vanish; the battle
// notes it (stat bit 0x4000) when there were any.
void queueOngyokiClonesVanish(ActionProcessData& a, int32_t dformindex, int32_t frame)
{
#if !NOCTURNE_US && !NOCTURNE_CHRONICLE   // (JP Maniax's debug print)
    diag::print(diag::Message::OngyoKiShadowAll);
#endif
    int32_t gone = 0;
    for (int32_t f = kFirstEnemyFormation; f < kFormationCount; ++f) {
        if (f == dformindex)
            continue;
        Formation& clone = formAt(a, f);
        if ((clone.stat & FormationStat::Present) && (clone.stat & FormationStat::Shadow)) {
            ++gone;
            addUnitAlphaPacket(frame + 1, uniqueOf(a), &clone, 0, 0);
            makeDeathPackets(frame + eff::ongyokiEffect2Length() + 1, uniqueOf(a), clone, 1);
            addOngyokiOutPacket2(frame, uniqueOf(a), &clone);
            setTimeList(a, f, frame, 30, 30);
        }
    }
    if (gone > 0)
        a.data->stat |= 0x4000;
}

// SetDamagePacket @ 0x002532A8: damage to the acting unit itself (the
// curse's), after its last unit is free. Endure, or Never Yield while it
// lasts, leaves the unit at 1 HP once.
void queueDamage(ActionProcessData& a, int32_t hp)
{
    const int32_t start = lastFreeFrame(a);
    const int32_t self = a.form->formindex;
    const bool endure = checkEndure(self);
    if (endure || checkNeverYield(self)) {
        if (hp > 0 && timeListHp(a, self) <= hp) {
            hp = timeListHp(a, self) - 1;
            addSkillNamePacket(start, uniqueOf(a), endure ? skill::Endure : skill::NeverYield);
            markEndureUsed(self);
        }
    }
    addTimeListHpAt(a, self, -hp);
    const bool dead = timeListDead(a, self);
    makeDamagePackets(start, uniqueOf(a), *a.form, 3, hp, -1, 0, false, dead, 0, true, 0);
    setTimeList(a, self, start, 30, 30);
    if (dead) {
        queueDeath(a, self);
        setTimeList(a, self, start, 20, 20);
    }
}

// ---- the state ------------------------------------------------------------------------------

// nbGetActionSeq @ 0x00257BF8
int32_t actionState(uint32_t process)
{
    if (!process)
        return 0;
    return guest::table<ActionProcessData>(dds3::GetProcessData(process))->seq;
}

// nbGetPrevActionSeq @ 0x00257C20: the action processes form a ring of 4.
int32_t previousActionState()
{
    const MainProcessData& main = *GetMainProcessData();
    int32_t prev = main.NowActionProcess - 1;
    if (prev < 0)
        prev = 3;
    const uint32_t process = main.ActionProcessID[prev];
    return process ? actionState(process) : -1;
}

namespace {

constexpr uint32_t kActionProcessName = addr(0x00544120);   // "nb_action"
constexpr uint32_t kActionStep = addr(0x00257cd0);          // nbActionProcess1 (runActionProcess's original)
constexpr uint32_t kActionShutdown = addr(0x00257e30);      // (no C here yet)

// The state table (0x3FA7C0): each state's SetAction_* and CheckAction_*.
// The rewrite runs the rewritten ones itself and calls the others' original
// code by address.
struct StateEntry {
    uint32_t set, check;
};
constexpr uint32_t kStateTable = addr(0x003fa7c0);

struct StateFunctions {
    void (*set)(ActionProcessData&);
    int32_t (*check)(ActionProcessData&);
};
constexpr StateFunctions kStates[24] = {
    {enterNone, updateNone},                        // 0 NON
    {enterCommand, updateCommand},                  // 1 COMM
    {enterAi, updateAi},                            // 2 AI
    {enterAiScript, updateAiScript},                // 3 AISCR
    {enterAilment, updateAilment},                  // 4 BAD
    {enterTargetSelect, updateTargetSelect},        // 5 TARSEL
    {enterStockSelect, updateStockSelect},          // 6 STKSEL
    {enterReady, updateReady},                      // 7 READY
    {enterSkill, updateSkill},                      // 8 SKILL
    {enterTalk, updateTalk},                        // 9 NEGO
    {enterTalkResult, updateTalkResult},            // 10 NEGORESULT
    {enterAilmentWait, updateAilmentWait},          // 11 BADWAIT
    {enterWait, updateWait},                        // 12 WAIT
    {enterEscape, updateEscape},                    // 13 ESCAPE
    {enterReturn, updateReturn},                    // 14 RETURN
    {enterInvisible, updateInvisible},              // 15 INVISIBLE
    {nullptr, nullptr},                             // 16 (unused)
    {nullptr, nullptr},                             // 17 (unused)
    {enterAftermath, updateAftermath},              // 18 CHECK1
    {enterDeathScript, updateDeathScript},          // 19 DEADSCRIPT
    {enterPlayOut, updatePlayOut},                  // 20 CHECK3
    {enterCleanup, updateCleanup},                  // 21 ATO
    {enterEnd, updateEnd},                          // 22 END
    {nullptr, nullptr},                             // 23 (unused)
};

const StateEntry& stateEntry(int32_t seq) { return guest::table<const StateEntry>(kStateTable)[seq]; }

void callEnter(ActionProcessData& a, int32_t seq)
{
    if (seq >= 0 && seq < 24 && kStates[seq].set)
        kStates[seq].set(a);
    else
        guest::callActionSet(stateEntry(seq).set, guest::addressOf(&a));
}

int32_t callUpdate(ActionProcessData& a, int32_t seq)
{
    if (seq >= 0 && seq < 24 && kStates[seq].check)
        return kStates[seq].check(a);
    return guest::callActionCheck(stateEntry(seq).check, guest::addressOf(&a));
}

} // namespace

// SetActionSeq @ 0x00257C80 (nbActionSetSeq): a new state starts with its
// counters cleared and no next state chosen.
void enterState(ActionProcessData& a, int32_t seq)
{
    a.seq = static_cast<int8_t>(seq);
    a.nextseq = 0;
    a.seqcnt = 0;
    a.seqtime = 0;
    callEnter(a, static_cast<int8_t>(seq));
}

// InitActionProcessData @ 0x00257EB0: a new action's record (its address):
// who acts (a party entry; one sitting the turn out has no formation), the
// action's kind, its target and value, no press icon spent yet.
uint32_t newActionData(MainProcessData& main, int32_t type, int32_t from, int32_t to, int32_t data)
{
    const uint32_t address = mem::PoolAllocate(sizeof(ActionProcessData));
    std::memset(guest::table<ActionProcessData>(address), 0, sizeof(ActionProcessData));
    ActionProcessData& a = *guest::table<ActionProcessData>(address);
    a.seq = 0;
    a.data.address = guest::addressOf(&main);
    Party& party = main.party[from];
    a.party.address = guest::addressOf(&party);
    a.form.address = (party.flag & 0x8) ? 0 : guest::addressOf(&main.form[party.formindex]);   // (Party flag 8: sitting the turn out)
    a.work.address = guest::addressOf(GetUnitWorkPointer(main, party));
    a.partyindex = from;
    a.type = type;
    a.target = to;
    a.adata = data;
    a.press = ee::Float::fromBits(0xbf800000);   // -1
    a.newpresstype = 0;
    clearTimeList(a);
    return address;
}

// nbInitActionProcess @ 0x00257FA8: the next of the four action processes
// ("nb_action") runs the action, under the battle's process.
void startAction(MainProcessData& main, int32_t type, int32_t from, int32_t to, int32_t data)
{
    main.NowActionProcess = (main.NowActionProcess + 1) % 4;
    const uint32_t record = newActionData(main, type, from, to, data);
    const uint32_t process = dds3::StartProcess(kActionProcessName, 0x3f8, 1, 1, kActionStep, kActionShutdown, record);
    dds3::LinkProcess(main.MainProcessID, process);
    main.ActionProcessID[main.NowActionProcess] = process;
}

// nbActionProcess1 @ 0x00257CD0: each frame, the state's check runs until
// it reports done (stat bit 2); the next frame enters the state it chose.
// END's next frame ends the process (-1). An action at READY waits for the
// action before it to reach state 19 or later (or for there to be none),
// and stops a streamed voice. Stat bit 0x40 holds the action; bit 0x400
// keeps the stock panel's selection.
int32_t runActionProcess(uint32_t process)
{
    ActionProcessData& a = *guest::table<ActionProcessData>(dds3::GetProcessData(process));
    if (a.stat & 0x400)
        nb::PanelStockSelect(*a.data, 0);
    const int32_t previous = previousActionState();
    bool go = true;
    if (((a.stat & 2) ? a.nextseq : a.seq) == kActionReady) {
        go = static_cast<uint32_t>(previous) >= 19;
        if (movie::CheckAdpcmFlag()) {
            diag::print(diag::Message::AdpcmPlaying);
            movie::StopAdpcm();
        }
    }
    if ((a.stat & 0x40) || !go)
        return 0;
    if (a.stat & 2) {
        if (a.seq == kActionEnd)
            return -1;
        enterState(a, a.nextseq);
        a.stat &= ~2u;
        return 0;
    }
    if (callUpdate(a, a.seq))
        a.stat |= 2;
    if (a.seqtime <= 0xfffe)
        ++a.seqtime;
    return 0;
}

// SetNextActionSeq @ 0x00257CC8
void setNextState(ActionProcessData& a, int32_t nextseq) { a.nextseq = static_cast<int8_t>(nextseq); }

// SetAction_NON @ 0x00253488
void enterNone(ActionProcessData&) {}

// SetAction_AI @ 0x00253BF8: the table AI chooses the unit's command.
void enterAi(ActionProcessData& a)
{
    UnitWork& unit = *a.work;
    unit.nowcommand = -1;
    unit.nowindex = 0;
    ai::run(a);
}

// CheckAction_AI @ 0x00253C20: the AI has chosen; on to READY.
int32_t updateAi(ActionProcessData& a)
{
    setNextState(a, kActionReady);
    return 1;
}

// SetAction_AISCR @ 0x00253C40: the devil's AI script chooses instead.
void enterAiScript(ActionProcessData& a)
{
    UnitWork& unit = *a.work;
    unit.nowcommand = -1;
    unit.nowindex = 0;
    ai::script::start(a, dat::aiRecord(unit.id).script());
}

// CheckAction_AISCR @ 0x00253C88: waits for the script to end; on to
// READY, or to the talks' result if it started talks.
int32_t updateAiScript(ActionProcessData& a)
{
    if (dds3::ExistProcess(a.data->AiScriptProcessID))
        return 0;
    MainProcessData& main = *a.data;
    main.AiScriptProcessID = 0;
    if (!main.talkResult) {
        setNextState(a, kActionReady);
    } else {
        clearTimeList(a);
        initTimeListHp(a);
        setNextState(a, kActionTalkResult);
    }
    return 1;
}

// CheckAction_BAD @ 0x00253E00: the unit's ailment at the start of its
// turn. Shock, freeze, sleep, bind and stone cost the turn (a press turn
// icon): shock and freeze then wear off, and sleep restores an eighth of HP
// and MP. A charmed or panicked unit, or a cursed one, acts by the ailment AI
// (bad_ai.hpp) and goes on to BADWAIT; otherwise the unit acts normally.
int32_t updateAilment(ActionProcessData& a)
{
    clearTimeList(a);
    initTimeListHp(a);
    a.statusMessage = 0;
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    const auto loseTurn = [&] {
        makePressPackets(0, uniqueid, ee::Float::fromInt(-1));
        makePressResultPackets(0, uniqueid, 0);
    };
    switch (badStat(a.form->formindex)) {
    case static_cast<uint32_t>(Ailment::Panic):
    case static_cast<uint32_t>(Ailment::Charm):
        runAilmentAi(a);
        setNextState(a, kActionAilmentWait);
        return 1;
    case static_cast<uint32_t>(Ailment::Shock):
    case static_cast<uint32_t>(Ailment::Freeze):
        loseTurn();
        makeAilmentCurePackets(5, uniqueid, *a.form);
        break;
    case static_cast<uint32_t>(Ailment::Sleep):
        loseTurn();
        nb::MakeHealPackets(10, uniqueid, a.form.get(), 0, a.work->maxhp >> 3, a.work->maxmp >> 3, 0);
        break;
    case static_cast<uint32_t>(Ailment::Bind):
    case static_cast<uint32_t>(Ailment::Stone):
        loseTurn();
        break;
    default:
        if (isCursed(a.form->formindex)) {
            runAilmentAi(a);
            setNextState(a, kActionAilmentWait);
        }
        return 1;
    }
    if (a.data->stat & BattleStat::EnemyTurn)
        setCameraState(kCameraEnemyBad);
    setTimeList(a, a.form->formindex, 0, 30, 30);
    setNextState(a, kActionAftermath);
    return 1;
}

// ---- choosing: the command menu, targets, the stock ----------------------------------------

namespace {

constexpr uint32_t kStatAutoBattle = 0x40;      // MainProcessData::stat: the party fights on its own
constexpr uint32_t kActAuto = 0x80;             // ActionProcessData::stat: this unit acts on its own
constexpr uint32_t kDebugPad = addr(0x0054e824);      // int32: the debug shortcuts on the pad are on
constexpr uint32_t kStockChoice = addr(0x00551120);   // int32: the stock demon chosen (-1 none yet, -2 cancelled)

int32_t& stockChoice() { return guest::table<int32_t>(kStockChoice)[0]; }
int8_t padByte(int32_t button) { return guest::table<const int8_t>(pad::kAddress)[button]; }

// Summoning: the slot next to the party and the enemies' empty slots.
void prepareSummon(MainProcessData& main)
{
    ai::prepareAllySummonSlot(main);
    ai::prepareSummonSlots(main, 0);
}

void clearSelected(MainProcessData& main)
{
    for (int32_t i = 0; i < 16; ++i)
        guest::table<Formation>(main.form.address)[i].stat &= ~FormationStat::Selected;
}

constexpr uint16_t kPartyHidden = 0x8;          // Party::flag (tentative): the unit sits the turn out (INVISIBLE)
constexpr uint32_t kStatTalkSettled = 0x4000;   // MainProcessData::stat, cleared each turn (tentative)
constexpr uint32_t kStatPadControl = 0x10000000;   // ... with the debug pad: the player gives enemies commands
constexpr uint16_t kTalkSkill = 0x182;          // the talk "skill" a talk's command carries

// A talk the unit opens: command 4 on a target, played from READY.
int32_t openTalk(ActionProcessData& a, int32_t talkType, uint16_t index)
{
    a.work->nowcommand = 4;
    a.work->nowindex = index;
    a.talkType = talkType;
    return kActionReady;
}

} // namespace

// CheckAction_NON @ 0x00253490: a new turn's first state. It clears the
// talks' slots and last turn's flags and rolls the skill item 1 would give
// (massuruid); a hidden unit sits the turn out (INVISIBLE). Then by the
// turn's type: 1..3 a talk (types 4, 3 and 5) at `target`, 4 the skill
// `adata` at `target` (and stat bit 4), 5 the unit's death script;
// otherwise the unit's counters 0x11 and 0x12 tick, an ailing unit (Shock,
// Freeze, Sleep, Bind, Charm, Stone) goes to BAD, the party's side to COMM
// (or ATO, if inactive), and an enemy to a talk of its own (CheckMukanNego,
// CheckSenseiNego) or its AI (script or table; COMM under the debug pad's
// control).
int32_t updateNone(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    main.talkResult = 0;
    main.talkPlayerSlot = 0;
    main.stat &= ~kStatTalkSettled;
    main.talkEnemySlot = 0;
    a.massuruid = dat::itemSkill(1);
    a.form->motionend = 0;
    const uint16_t flag = a.party->flag;
    a.party->flag = static_cast<int16_t>(flag & ~PartyFlag::AlwaysCrit);
    if (flag & kPartyHidden) {
        setNextState(a, kActionInvisible);
        return 1;
    }

    int32_t next;
    switch (a.type) {
    case 1:
    case 2:
    case 3:
        next = openTalk(a, a.type == 1 ? 4 : a.type == 2 ? 3 : 5, a.type == 2 ? main.prevcommind : kTalkSkill);
        targetPartySlot(a, a.target);
        a.select = ai::selectedBits(main);
        break;
    case 4:
        a.work->nowcommand = 1;
        a.work->nowindex = static_cast<uint16_t>(a.adata);
        targetPartySlot(a, a.target);
        a.select = ai::selectedBits(main);
        next = kActionReady;
        a.stat |= 4;
        break;
    case 5:
        next = kActionDeathScript;
        break;
    default: {
        const int32_t slot = a.form->formindex;
        addBuff(slot, 0x11, 1, false);
        addBuff(slot, 0x12, 1, false);
        switch (static_cast<Ailment>(badStat(a.form->formindex))) {
        case Ailment::Shock: case Ailment::Freeze: case Ailment::Sleep:
        case Ailment::Bind: case Ailment::Charm: case Ailment::Stone:
            next = kActionAilment;
            break;
        default:
            if (!(a.party->flag & PartyFlag::EnemySide)) {
                next = (a.party->flag & PartyFlag::Inactive) ? kActionCleanup : kActionCommand;
            } else if (checkLastEnemyTalks(a)) {
                next = openTalk(a, 1, kTalkSkill);
                targetDemiFiend(a);
                a.select = ai::selectedBits(main);
            } else if (checkAmbushTalk(a)) {
                next = openTalk(a, 2, kTalkSkill);
                targetDemiFiend(a);
                a.select = ai::selectedBits(main);
            } else if (guest::table<const int32_t>(kDebugPad)[0] == 1 && (main.stat & kStatPadControl)) {
                next = kActionCommand;
            } else {
                next = dat::aiRecord(a.work->id).script() == 0 ? kActionAi : kActionAiScript;
            }
            break;
        }
        break;
    }
    }
    setNextState(a, next);
    return 1;
}

// SetAction_COMM @ 0x00253830: the command menu opens (in an auto battle
// the unit chooses by itself), with the battle panel and press gauge.
void enterCommand(ActionProcessData& a)
{
    if (a.data->stat & kStatAutoBattle)
        a.stat |= kActAuto;
    else
        deletePacketsOfType(kFormOnOff);
    nb::PanelAllShow();
    nb::PanelPressGaugeShow();
    startCommandMenu(*a.data, *a.party, a);
}

// CheckAction_COMM @ 0x002538A0: waits for a command. Attack and talk go
// to choosing a target (5); skills and items too, or to choosing from the
// stock (6) for a skill aimed at it (target area bit 1 without 4 or 8)
// unless the party is flagged 2 or 4; summoning prepares the slots first.
// Escape, pass, return and command 8 go straight to READY (7) and close the
// menu. A skill that would do nothing (nbCheckBattleSkillError1) says so
// and keeps the menu. With the debug shortcuts on, two pad combinations
// win the battle or force a press at once.
int32_t updateCommand(ActionProcessData& a)
{
    if (guest::table<const int32_t>(kDebugPad)[0] != 0) {
        if (padByte(9) != 0 && padByte(11) != 0) {
            debugWinBattle(a);
            a.packettime = 60;
            setNextState(a, kActionPlayOut);
            return 1;
        }
        if (padByte(9) != 0 && padByte(pad::kCancel) != 0) {
            debugEndPressTurns(a);
            a.packettime = 60;
            setNextState(a, kActionPlayOut);
            return 1;
        }
    }
    if ((a.data->stat & kStatAutoBattle) && !(a.stat & kActAuto)) {
        a.stat |= kActAuto;
        setAutoCommand();
    }
    if (commandMenuState() != 3)
        return 0;

    int32_t se = 8, result = 0;
    bool close = false;
    UnitWork& unit = *GetUnitWorkPointer(*a.data, *a.party);
    switch (unit.nowcommand) {
    case 0:   // attack
        setNextState(a, kActionTargetSelect);
        result = 1;
        break;
    case 1:   // a skill
    case 5: { // an item
        if (unit.nowcommand == 1) {
            switch (unit.nowindex) {
            case 0xde:   // (not a summon in the first release)
                if (!kBuild.vanilla)
                    prepareSummon(*a.data);
                break;
            case 0xdf: case 0xe2: case 0xe3: case 0xe4: case 0xe5: case 0xe6: case 0xfc:   // summons
                prepareSummon(*a.data);
                break;
            default: break;
            }
        }
        int32_t nskill = unit.nowindex;
        if (unit.nowcommand != 1) {
            nskill = itemSkillFor(a, unit.nowindex);
            diag::print(diag::Message::ItemNo, unit.nowindex);
            diag::print(diag::Message::SkillNo, nskill);
        }
        const int32_t err = reviveError(nskill);
        if (err != 0 && !(a.stat & kActAuto)) {
            se = -1;
            showSkillError(err);
            setCommandMenuState(2);
            break;
        }
        const uint8_t area = dat::normalSkill(nskill).targetarea;
        const bool stock = !(a.party->flag & 6) && (area & 1) && !(area & 0xc);
        setNextState(a, stock ? kActionStockSelect : kActionTargetSelect);
        result = 1;
        break;
    }
    case 4:   // talk
        a.talkType = 0;
        result = 1;
        setNextState(a, kActionTargetSelect);
        break;
    case 6:   // summon
        result = 1;
        prepareSummon(*a.data);
        setNextState(a, kActionTargetSelect);
        break;
    case 2:
    case 3:
    case 7:
    case 8:   // escape, pass, return
        setNextState(a, kActionReady);
        close = true;
        result = 1;
        break;
    default: break;
    }
    if (se >= 0 && !(a.stat & kActAuto))
        playBattleSound(se);
    if (close)
        closeCommandMenu();
    return result;
}

// SetAction_BAD @ 0x00253DE0: the battle panel and press gauge show.
void enterAilment(ActionProcessData&)
{
    nb::PanelAllShow();
    nb::PanelPressGaugeShow();
}

// CheckAction_TARSEL @ 0x00254190: waits for a target. Chosen: a skill or
// item that would do nothing there (nbCheckBattleSkillError2) says so and
// keeps choosing; otherwise the targets are kept and on to READY.
// Cancelled: back to the command menu (state 1, entered without resetting
// the counters). An auto battle starting meanwhile also goes back, the
// menu choosing by itself.
int32_t updateTargetSelect(ActionProcessData& a)
{
    if ((a.data->stat & kStatAutoBattle) && !(a.stat & kActAuto)) {
        a.stat |= kActAuto;
        setCommandMenuState(2);
        setAutoCommand();
        a.seq = kActionCommand;
        return 0;
    }
    switch (targetCursorState()) {
    case 0: {
        const uint32_t select = ai::selectedBits(*a.data);
        if (!(a.stat & kActAuto)) {
            int32_t nskill = -1;
            if (a.work->nowcommand == 1)
                nskill = a.work->nowindex;
            else if (a.work->nowcommand == 5)
                nskill = itemSkillFor(a, a.work->nowindex);
            if (nskill >= 0) {
                if (const int32_t err = targetSkillError(nskill, select)) {
                    showSkillError(err);
                    if (err == 4)
                        setTargetNameDelay(29);
                    setTargetCursorState(1);
                    return 0;
                }
            }
            playBattleSound(8);
        }
        closeCommandMenu();
        a.select = select;
        setNextState(a, kActionReady);
        return 1;
    }
    case 2:
        clearSelected(*a.data);
        setCommandMenuState(2);
        a.seq = kActionCommand;
        return 0;
    default:
        return 0;
    }
}

// SetAction_STKSEL @ 0x00254360: choosing a stock demon on the battle panel.
void enterStockSelect(ActionProcessData& a)
{
    a.select = 0;
    nb::PanelStockSelectInit();
    nb::PanelStockSelect(*a.data, 0);
    stockChoice() = -1;
}

// CheckAction_STKSEL @ 0x002543A0: the panel's answer. A demon: it is the
// target (bit 16 + its stock index) and on to READY. Cancelled: back to the
// command menu.
int32_t updateStockSelect(ActionProcessData& a)
{
    if (stockChoice() == -2) {
        clearSelected(*a.data);
        setCommandMenuState(2);
        a.seq = kActionCommand;
        playBattleSound(10);
        nb::PanelStockEnd();
        return 0;
    }
    if (stockChoice() == -1) {
        stockChoice() = static_cast<int32_t>(nb::PanelStockSelect(*a.data, 1));
        return 0;
    }
    nb::PanelStockSelect(*a.data, 0);
    closeCommandMenu();
    a.select = 1u << ((stockChoice() + 16) & 31);
    setNextState(a, kActionReady);
    a.stat |= 0x400;
    playBattleSound(8);
    return 1;
}

// SkillHitEffect (0x3DBD20): 4 bytes per skill.
uint8_t hitEffectByte(int32_t skill, int32_t n)
{
    return guest::table<const uint8_t>(dat::address::SkillHitEffect + 4u * static_cast<uint32_t>(skill))[n];
}

// GetKoukaList @ 0x002518C8: who the skill hits and how often (list:
// formation index and hits, -1 ending). Units already down or leaving are
// left out. A random-target skill (targetrandom 1) spreads its hit count
// (targetcntmin..max) at random, never the same target twice in a row and
// at most one or two more hits than there are targets on any one; skills
// 0x9E and 0x9F hit the target with the lowest share of its HP once (a
// random one of those tied; not in the first release); others hit each target once with the count, in
// slot order, reverse order or shuffled, by the skill's hit-effect kind
// (0..7, 8..11, 12..15). On the enemies' turn skill 0xCC's kinds 4..11 hit
// in reverse.
void hitOrder(ActionProcessData& a, HitOrderEntry* list, uint32_t select, int32_t nskill)
{
    for (int32_t i = 0; i < 32; ++i)
        list[i] = {-1, 0};
    if (a.runerr != 0)
        return;
    const NormalSkill& ns = dat::normalSkill(nskill);
    int32_t count = ns.targetcntmin;
    if (ns.targetcntmin < ns.targetcntmax)
        count = ns.targetcntmin + sdf::GetRandInt(ns.targetcntmax - ns.targetcntmin + 1);
    diag::print(diag::Message::HitCount, count, static_cast<int32_t>(select));
    MainProcessData& main = *a.data;
    for (int32_t i = 0; i < 16; ++i) {
        if (!(select & 1u << i))
            continue;
        const Formation& form = guest::table<const Formation>(main.form.address)[i];
        if ((form.stat & 1) && (form.stat & 0x40) &&
            ((main.party[form.partyindex].flag & 0x20) || timeListDead(a, i)))
            select &= ~(1u << i);
    }

    if (ns.targetrandom == 1) {
        HitOrderEntry candidates[32];
        int32_t n = 0;
        for (int32_t i = 0; i < 32; ++i)
            if (select & 1u << i)
                candidates[n++] = {static_cast<int8_t>(i), 0};
        if (n == 0)
            return;
        const int32_t limit = n + sdf::GetRandInt(2);
        int32_t entries = 0;
        int8_t previous = -1;
        for (int32_t hit = 0; hit < count; ++hit) {
            int32_t pick;
            int8_t target;
            do {
                pick = sdf::GetRandInt(n);
                target = candidates[pick].formindex;
            } while (n > 1 && target == previous);
            previous = target;
            HitOrderEntry& c = candidates[pick];
            if (c.count >= limit)
                continue;
            ++c.count;
            int32_t k = 0;
            if (entries > 0 && list[0].formindex != target) {
                k = 1;
                while (k < entries && list[k].formindex != target)
                    ++k;
            }
            if (k == entries)
                list[entries++] = {target, 1};
            else
                ++list[k].count;
        }
        return;
    }

    if (!kBuild.vanilla && (nskill == 0x9e || nskill == 0x9f)) {
        int8_t lowest[32] = {};
        int32_t n = 0;
        uint32_t best = 101;
        for (int32_t i = 0; i < 16; ++i) {
            if (!(select & 1u << i))
                continue;
            const Formation& form = guest::table<const Formation>(main.form.address)[i];
            if (!(form.stat & 1) || !(form.stat & 0x40))
                continue;
            const UnitWork& unit = *GetUnitWorkFromFormindex(form.formindex);
            if (unit.hp == 0)
                continue;
            const uint32_t ratio = static_cast<uint32_t>(unit.hp) * 100 / unit.maxhp;
            if (ratio < best) {
                best = ratio;
                lowest[0] = static_cast<int8_t>(i);
                n = 1;
            } else if (ratio == best) {
                lowest[n++] = static_cast<int8_t>(i);
            }
        }
        const int32_t k = n < 1 ? 0 : sdf::GetRandInt(n * 10) % n;
        list[0] = {lowest[k], 1};
        return;
    }

    uint32_t kind = hitEffectByte(nskill, 1);
    if ((main.stat & BattleStat::EnemyTurn) && nskill == 0xcc && kind - 4 <= 7)
        kind = 11;
    if (kind >= 16)
        return;
    const int8_t count8 = static_cast<int8_t>(count);
    int32_t entries = 0;
    if (kind < 8 || kind >= 12) {
        for (int32_t i = 0; i < 32; ++i)
            if (select & 1u << i)
                list[entries++] = {static_cast<int8_t>(i), count8};
    } else {
        for (int32_t i = 31; i >= 0; --i)
            if (select & 1u << i)
                list[entries++] = {static_cast<int8_t>(i), count8};
    }
    if (kind >= 12 && entries > 1) {
        for (int32_t swap = 0; swap < 32; ++swap) {
            const int32_t x = sdf::GetRandInt(entries), y = sdf::GetRandInt(entries);
            std::swap(list[x], list[y]);
        }
    }
}

namespace {

// SetAction_SKILL: what a target's result was, named in a debug print (JP
// Maniax's only; the hits and misses aren't named).
void printResultKind([[maybe_unused]] int32_t kind)
{
#if !NOCTURNE_US && !NOCTURNE_CHRONICLE
    switch (kind) {
    case 6: diag::print(diag::Message::SummonKind); break;
    case 7: diag::print(diag::Message::AnalyzeKind); break;
    case 8: diag::print(diag::Message::EscapeKind); break;
    case 9: diag::print(diag::Message::MaccaKind); break;
    case 10: diag::print(diag::Message::EnemyEscapeKind); break;
    case 12: diag::print(diag::Message::AuroraKind); break;
    case 13: diag::print(diag::Message::ExtraPressKind); break;
    case 14: diag::print(diag::Message::FlareChargeKind); break;
    default: break;
    }
#endif
}

// SetAllPacket's press result, named in a debug print (JP Maniax's only;
// a result against the unit's own side isn't named).
void printPressResult([[maybe_unused]] int32_t type)
{
#if !NOCTURNE_US && !NOCTURNE_CHRONICLE
    switch (type) {
    case 0: diag::print(diag::Message::NormalHit); break;
    case 3: diag::print(diag::Message::CriticalHit); break;
    case 2: diag::print(diag::Message::WeakHit); break;
    case 6: diag::print(diag::Message::RepelHit); break;
    case 7: diag::print(diag::Message::DrainHit); break;
    case 5: diag::print(diag::Message::NullHit); break;
    default: break;
    }
#endif
}

} // namespace

// SetAllPacket @ 0x0024FF60: one target's result of a skill (koukatype:
// how nbGetKoukaType resolved it) as packets from `frame`: `cnt` hits of
// damage or healing, the ailment inflicted or cured, deaths (Endure and
// Never Yield leave 1 HP), HP and MP drained, the buff shown, a counter,
// and the press turns it costs.
//  - The event boss's skills 0x106..0x108 (Dante's; Raidou's in the
//    Chronicle Edition, with their own lengths; none in the first release)
//    start the result later.
//  - Repel (1): the result hits the user instead, who may null or resist
//    the ailment; Drain (2): the target heals what it would have lost;
//    Null (3): nothing happens. Each is one hit.
//  - A hit that does nothing shows "MISS" and ends the hits; the hits'
//    ratio (koukaritu x affinity, criticals x1.5) shrinks each hit by the
//    skill's reduction rate.
void queueHitResult(ActionProcessData& a, int32_t koukatype, int32_t nskill, int32_t sformindex, int32_t dformindex, int32_t cnt,
                  int32_t frame, ee::Float koukaritu)
{
    MainProcessData& main = *a.data;
    const NormalSkill& ns = dat::normalSkill(nskill);
    ee::Float ritu = damageRatio(nskill, sformindex, dformindex) * koukaritu;
    bool ownHits = true;   // damage counts toward the action's totals (allhpdamage)
    bool drain = false, nulled = false, counter = false;
    uint32_t outbad = 0;
    int32_t hpTotal = 0, mpTotal = 0, healHp = 0, healMp = 0, drainHp = 0, drainMp = 0;
    bool dead = false;
    int32_t deadtype = 0;
    uint32_t bad = rollAilmentInflict(ritu, nskill, sformindex, dformindex, false);
    const uint32_t cure = rollAilmentCure(ritu, nskill, sformindex, dformindex, false);
    const int32_t savedAutoskill = a.autoskill;
    int32_t hittype = static_cast<int32_t>(rollCritical(a, nskill, sformindex, dformindex));
    if (koukatype == static_cast<int32_t>(EffectResult::Repel))
        a.autoskill = savedAutoskill;
    if (hittype == static_cast<int32_t>(HitType::Critical))
        ritu = criticalPower(sformindex, ritu);
    const ee::Float speed = ee::Float::fromInt((a.stat & 0x100) ? 3 : 1);

    int32_t target = dformindex;
    switch (koukatype) {
    case 2: {   // drained
        if (!kBuild.vanilla) {
            if (nskill == 0x106)
                frame += kBuild.chronicle ? 0x35 : 8;
            if (nskill == 0x107)
                frame += kBuild.chronicle ? 0x7d : 0x3c;
            if (nskill == 0x108)
                frame += kBuild.chronicle ? 0x2d : 0x5a;
        }
        if (target < 16)
            addHitEffectPacket(frame, uniqueOf(a), formAt(a, target), 2);
        setHitStopFrame(a, frame);
        setTimeList(a, target, frame, 15, 30);
        frame += 13;
        bad = 0;
        cnt = 1;
        ownHits = false;
        drain = true;
        break;
    }
    case 1: {   // repelled: the user takes it
        if (!kBuild.vanilla) {
            if (nskill == 0x107) {
                frame += 8;
                main.d31_repel107 = 1;
            }
            if (nskill == 0x108)
                frame += kBuild.chronicle ? 0x2d : 0x5a;
            if (nskill == 0x113)
                main.d31_repel113 = 1;
        }
        if (dformindex < 16)
            addHitEffectPacket(frame, uniqueOf(a), formAt(a, dformindex), 1);
        setHitStopFrame(a, frame);
        target = sformindex;
        setTimeList(a, dformindex, frame, 15, 30);
        frame += 13;
        cnt = 1;
        ownHits = false;
        if (affinity(-1, sformindex, skillAttribute(nskill)).raw & (Affinity::Null | Affinity::Repel | Affinity::Drain)) {
            bad = 0;
            nulled = true;
        }
        switch (bad) {
        case 0x1000: case 0x2000: case 0x4000:   // (the first release has no such effects)
            if (kBuild.vanilla)
                break;
            [[fallthrough]];
        case 0x1: case 0x2: case 0x4: case 0x8: case 0x10: case 0x20: case 0x40: case 0x80:
        case 0x100: case 0x200: case 0x400: case 0x800:
            if (affinity(nskill, sformindex, dat::ailmentElement(bad)).raw &
                (Affinity::Null | Affinity::Repel | Affinity::Drain | Affinity::Unknown100000))
                bad = 0;
            break;
        default: break;
        }
        if ((main.stat & 0x400) && !isPlayerSide(sformindex)) {
            bad = 0;
            nulled = true;
        }
        if (nskill == 0xd4) {
            bad = 0;
            nulled = true;
        }
        hittype = 0;
        break;
    }
    case 3:   // nulled
        setHitStopFrame(a, frame);
        cnt = 1;
        bad = 0;
        ownHits = false;
        nulled = true;
        break;
    default: break;
    }
    const bool inRange = target < 16;
    if (inRange && (main.party[formAt(a, target).partyindex].flag & 0x20))
        cnt = 0;   // already gone
    if (frame < freeFrame(a, target))
        frame = freeFrame(a, target);
    if (koukatype == static_cast<int32_t>(EffectResult::Repel) && !nulled)
        fadeInHiddenUnit(a, frame);

    for (int32_t i = 0; i < cnt; ++i) {
        dead = false;
        if (bad == static_cast<uint32_t>(Ailment::Dead)) {
            dead = true;
            deadtype = deadType();
        }
        int32_t hp = hpEffect(ritu, true, nskill, sformindex, target, cnt);
        int32_t heal = hpEffect(ritu, false, nskill, sformindex, target, cnt);
        // Ailments that take a share of HP (not in the first release).
        if (!kBuild.vanilla && (bad == 0x4000 || bad == 0x2000 || bad == 0x1000)) {
            const int32_t now = GetUnitWorkFromFormindex(target)->hp;
            if (bad == 0x1000) {
                hp = now >> 1;
            } else {
                hp = now - (bad == 0x4000 ? now / 10 : now >> 2);
                if (!(hp < now))
                    hp = now - 1;
                hp = std::max(hp, 0);
            }
            bad = 0;
        }
        diag::print(diag::Message::HitHp, hp, heal);
        int32_t mp = mpEffect(ritu, true, nskill, sformindex, target, cnt);
        int32_t healmp = mpEffect(ritu, false, nskill, sformindex, target, cnt);
        diag::print(diag::Message::HitMp, mp, healmp);
        if (drain) {
            if (hp >= 0)
                heal = heal >= 0 ? heal + hp : hp;
            if (mp >= 0)
                healmp = healmp >= 0 ? healmp + mp : mp;
            hp = -1;
            mp = -1;
            dead = false;
        }
        bool shown = false;
        if (nulled) {
            if (inRange) {
                addWordPacket(frame, 0x2d, uniqueOf(a), &formAt(a, target), 4);   // "Null"
                shown = true;
            }
            hp = -1;
            mp = -1;
            dead = false;
        }
        const bool hiteff = hasHitEffect(nskill);
        bool hit = false;
        if (i == cnt - 1 && bad != 0) {
            outbad = bad;
            hit = true;
        } else if (hp >= 0 || mp >= 0) {
            outbad = 0;
            hit = true;
        }
        if (dead) {
            outbad = 0;
            hit = true;
        }

        if (hit) {
            if (koukatype == 0 && ns.damageClass == 0)
                counter = true;   // a physical hit landed
            // Never Yield (0x168) and Endure (0x159) leave the unit 1 HP.
            if (dead) {
                int32_t saved = 0;
                if (checkNeverYield(target))
                    saved = skill::NeverYield;
                else if (checkEndure(target))
                    saved = skill::Endure;
                if (saved) {
                    dead = false;
                    if (outbad == static_cast<uint32_t>(Ailment::Dead))
                        outbad = 0;
                    hp = timeListHp(a, target) - 1;
                    addSkillNamePacket(frame, uniqueOf(a), saved);
                }
            } else if (hp > 0 && hp >= timeListHp(a, target)) {
                if (checkEndure(target)) {
                    hp = timeListHp(a, target) - 1;
                    addSkillNamePacket(frame, uniqueOf(a), skill::Endure);
                } else if (checkNeverYield(target)) {
                    hp = timeListHp(a, target) - 1;
                    addSkillNamePacket(frame, uniqueOf(a), skill::NeverYield);
                }
            }
            if (hp > 0) {
                if (ownHits)
                    hpTotal += std::min(hp, timeListHp(a, target));
                const ee::Float rate = hpDrainRate(nskill);
                if (ee::Float::fromBits(0) < rate)
                    drainHp += (ee::Float::fromInt(hp) * rate).toInt();
                addTimeListHp(a, target, -hp);
                if (timeListDead(a, target)) {
                    dead = true;
                    deadtype = deadType();
                    if (badStat(target) == static_cast<uint32_t>(Ailment::Stone))
                        deadtype = 1;   // shattered
                } else if (rollStoneShatter(nskill, target)) {
                    dead = true;
                    deadtype = 1;
                }
            }
            if (mp > 0) {
                if (ownHits)
                    mpTotal += mp;
                const ee::Float rate = mpDrainRate(nskill);
                if (ee::Float::fromBits(0) < rate)
                    drainMp += (ee::Float::fromInt(mp) * rate).toInt();
            }
            if (main.stat & 0x20000)
                dead = false;
            if (devilFormatFlag(target) & 0x100)
                dead = false;   // can't die
            makeDamagePackets(frame, uniqueOf(a), formAt(a, target), hittype, hp, mp, outbad, hiteff, dead, deadtype, true,
                              koukatype == 1 ? 2 : 0);
            if (koukatype == 1) {
                addSoundPacket(frame, uniqueOf(a), 0x10002);
            } else if (koukatype != 2 && (nskill == 0 || (nskill >= 0xa4 && nskill <= 0xa6))) {   // attacks
                addSoundPacket(frame, uniqueOf(a), hittype == static_cast<int32_t>(HitType::Critical) ? 0x10003 : 0x10002);
            }
            if (dead) {
                setTimeList(a, target, frame, 0x1e, 0x1e);
                frame += 0x1e;
                addTimeListHp(a, target, -timeListHp(a, target));
            } else {
                // The hit's stagger: the attacker's attack interval for a
                // demon's attack, else 10 frames; at least 5.
                const UnitWork& user = *a.work;
                int32_t wait = 10;
                if (!(user.flag & UnitFlag::PlayerCharacter) &&
                    (user.nowcommand == 0 || (user.nowcommand == 1 && user.nowindex >= 0xa4 && user.nowindex <= 0xa7)))
                    wait = dat::devilFormat(user.id).attackinterval;
                wait = std::max((ee::Float::fromInt(wait) / speed).toInt(), 5);
                setTimeList(a, target, frame, wait, wait);
                frame += wait;
            }
            if (!dead && outbad == 0 && inRange && hitWakes(GetUnitWorkFromFormindex(target), nskill))
                makeAilmentCurePackets(frame, uniqueOf(a), formAt(a, target));   // the hit wakes it
        }
        healHp += heal > 0 ? heal : 0;
        healMp += healmp > 0 ? healmp : 0;
        ritu = ritu * reductionRate(nskill);
        if (dead)
            break;
        if (!hit && heal <= 0 && healmp <= 0 && ns.buffKinds == 0 && !shown && cure == 0) {
            hittype = 0;
            diag::print(diag::Message::HitMiss);
            addWordPacket(frame, 0x2d, uniqueOf(a), &formAt(a, target), 3);   // "Miss"
            setHitStopFrame(a, frame);
            break;
        }
    }

    a.allhpdamage += hpTotal;
    a.allmpdamage += mpTotal;
    int32_t drainFrame = frame;
    if (!dead) {
        if (healHp > 0 || healMp > 0 || cure != 0) {
            const int32_t hpv = healHp > 0 ? healHp : -1, mpv = healMp > 0 ? healMp : -1;
            nb::MakeHealPackets(frame, uniqueOf(a), &formAt(a, target), 0, hpv, mpv, cure);
            if (cure != 0)
                setAilment(target, false, cure);
            if (hpv > 0)
                addTimeListHp(a, target, hpv);
            setTimeList(a, target, frame, 15, 20);
            frame += 15;
        }
        if (inRange && ns.buffKinds != 0) {
            addBuffPacket(frame, uniqueOf(a), &formAt(a, target), ns.buffKinds, static_cast<int8_t>(ns.buffAmount));
            setTimeList(a, target, frame, 10, 15);
        }
    }
    if ((drainHp > 0 || drainMp > 0) && ownHits) {
        drainFrame += 5;
        const int32_t hpv = drainHp > 0 ? drainHp : -1, mpv = drainMp > 0 ? drainMp : -1;
        nb::MakeHealPackets(drainFrame + 10, uniqueOf(a), &formAt(a, sformindex), 2, hpv, mpv, 0);
        if (hpv > 0)
            addTimeListHp(a, sformindex, hpv);
        setTimeList(a, sformindex, drainFrame, 15, 20);
    }
    if (!dead && counter && a.type == 0)
        checkCounter(a, target, sformindex);
    markEndureUsed(target);
    if (dead)
        queueDeath(a, target);
    const UnitWork& unit = *GetUnitWorkFromFormindex(target);
    if (nskill == 0x31 || nskill == 0x32)
        setStatusMessage(a, 0x4e, 1, unit.id); // revived
    else if (nskill == 0xe0)
        setStatusMessage(a, 0x58, 1, unit.id);

    // The press turns.
    // (a critical or weak hit costs half an icon; an enemy's repel or drain
    // all of them, a null two)
    const ee::Float half = ee::Float::fromBits(0xbf000000), one = ee::Float::fromInt(-1);
    const ee::Float two = ee::Float::fromInt(-2), four = ee::Float::fromInt(-4);
    const auto press = [&](ee::Float cost, int32_t type, bool named = true) {
        if (named)
            printPressResult(type);
        setPressCost(a, cost);
        setPressResult(a, type);
    };
    switch (koukatype) {
    case 0:
        if (hittype == static_cast<int32_t>(HitType::Critical))
            press(half, 3);
        else if (hittype == static_cast<int32_t>(HitType::Normal))
            press(one, 0);
        else if (hittype == static_cast<int32_t>(HitType::Weakness))
            press(half, 2);
        break;
    case 1:
        if (sameSide(sformindex, dformindex))
            press(one, 0, false);
        else
            press(four, 6);
        break;
    case 2:
        if (sameSide(sformindex, dformindex))
            press(one, 0, false);
        else
            press(four, 7);
        break;
    case 3:
        if (sameSide(sformindex, dformindex))
            press(one, 0, false);
        else
            press(two, 5);
        break;
    default: break;
    }
}

// ---- READY: everything an action needs before it plays -------------------------------------

namespace {

constexpr uint32_t kMidiPath = addr(0x00575360);   // char[]: the skill's sound file name

} // namespace

// SetAction_READY @ 0x00254488: sets up the action the unit chose. A
// panicked unit may act by the ailment instead, and a cursed one, one time
// in four, goes to BAD (4); command -1 goes straight to CHECK1. A skill that
// can't be used now (nbCheckSkillUse) or a command with no target notes an
// error (runerr) and its status line. Then: an item used up leaves the
// stock; a skill, item or summon starts loading its effect file (.BED) and
// its sound bank (/sound/MIDIxxxx.SMG); the unit's motion starts (an auto
// battle's attacks three times as fast), its HP or MP cost is paid, the
// effect, target and buff packets are queued, and the help line names the
// action.
void enterReady(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    switchMusic();
    a.press = ee::Float::fromBits(0);
    a.form->motionenddata = 0;
    a.form->motionend = 0;
    a.runerr = 0;
    a.statusMessage = 0;
    a.skilltime = 0;
    a.autoskill = 0;
    a.allhpdamage = 0;
    a.allmpdamage = 0;
    clearTimeList(a);
    initTimeListHp(a);
    const UnitVisual& visual = unitVisual(*a.work);
    if (!configOption(2) && (a.stat & kActAuto) && a.work->nowcommand == 0)
        a.stat |= 0x100;   // fast
    ee::Float speed = ee::Float::fromInt(1), targetSpeed = ee::Float::fromInt(1);
    if (a.stat & 0x100) {
        targetSpeed = ee::Float::fromBits(0x3fc00000);   // 1.5
        // (Dante, devil 0xC0, keeps his own speed; the Chronicle Edition's
        // Raidou in his place doesn't, nor the first release's devil 0xC0)
        if (kBuild.chronicle || kBuild.vanilla || a.work->id != 0xc0)
            speed = ee::Float::fromInt(3);
    }

    // Once per turn: the ailments that take over.
    if (!(a.stat & 4)) {
        a.stat |= 4;
        if (badStat(a.form->formindex) == static_cast<uint32_t>(Ailment::Panic) && a.type != 3 && rollPanicAction(*a.work)) {
            enterState(a, kActionAilment);
            return;
        }
        if (isCursed(a.form->formindex) && sdf::GetRandInt(4) == 0) {
            enterState(a, kActionAilment);
            return;
        }
    }

    int32_t skill = 0;
    switch (a.work->nowcommand) {
    case -1:
        enterState(a, kActionAftermath);
        return;
    case 1:
        skill = readySkill(a.work->nowindex);
        switch (checkSkillUse(a.form->formindex, skill)) {
        case 1: a.runerr = 1; setStatusMessage(a, 0x3c, -1, 0); break; // muted
        case 2: a.runerr = 1; setStatusMessage(a, 0xe, -1, 0); break;  // not enough HP
        case 3: a.runerr = 1; setStatusMessage(a, 0xc, -1, 0); break;  // not enough MP
        default: break;
        }
        break;
    case 5: skill = itemSkillFor(a, a.work->nowindex); break;
    case 6: skill = 0xff; break;
    default: break;
    }
    const int16_t command = a.work->nowcommand;
    if ((command == 0 || command == 1 || (command >= 4 && command <= 6)) && a.select == 0) {
        a.runerr = 3;   // no target
        setStatusMessage(a, 0x3e, -1, 0);
    }
    if (command == 5 && (dat::item(a.work->nowindex).flag & 4))
        dat::addItem(a.work->nowindex, -1);
    a.stat &= ~1u;

    // The effect file and the sound bank.
    if (command == 1 || command == 5 || command == 6) {
        a.hBed = 0;
        if (hitEffectByte(skill, 3) != 0) {
            if constexpr (diag::kept(diag::Message::BedName))   // (the Chronicle Edition has no such print)
                diag::print(diag::Message::BedName, skill, eff::BTLBedName(skill));
            a.hBed = file::Request(eff::BTLBedName(skill));
        }
        a.hSkillSe = 0;
        std::snprintf(guest::table<char>(kMidiPath), 32, "/sound/MIDI%04X.SMG", static_cast<uint32_t>(skill + 0x200));
        diag::print(diag::Message::MidiName, kMidiPath);
        a.hSkillSe = file::Request(kMidiPath);
        a.skillmidi = static_cast<uint32_t>(skill + 0x200) << 16;
    }

    // The unit's motion.
    int32_t motionType = -1;
    switch (command) {
    case 0: motionType = 3; break;
    case 1: motionType = skillMotionType(*a.work); break;
    case 5: motionType = 0x19; break;
    case 6: motionType = summonMotionType(*a.work); break;
    default: break;
    }
    int32_t motion = -1;
    if (motionType >= 0) {
        deleteNumberWordPackets(a.form.get());
        addFormationFlagPacket(0, uniqueOf(a), a.form.get(), 0, 0x2000);
        a.form->stat &= ~0x4000u;
        a.form->motionend = static_cast<int16_t>(motionEndType(*a.form, motionType));
        a.form->motionenddata = static_cast<int16_t>(motionEndData(*a.form, motionType));
        motion = prepareMotion(*a.form, motionType);
        addSkillMotionPacket(0, uniqueOf(a), a.form.get(), static_cast<int16_t>(motionType), a.form->motionend, speed);
        if (a.form->motionend == 2 && a.form->motionenddata >= 0) {   // the unit fades out at the end
            const ee::Float rate = motionSpeed(*a.form, motionType, speed);
            makeFadeOutPackets((ee::Float::fromInt(a.form->motionenddata) / rate).toInt(), uniqueOf(a), a.form.get(), 0, 2,
                                    4, 4);
        }
    }
    a.form->motiontype = static_cast<int16_t>(motionType);
    a.motion = motion;
    if (!(a.stat & 0x100))
        a.motionSound = loadMotionSound(*a.form, motion) ? 1 : 0;

    // When the hit lands (timer), and how the target packets aim.
    int16_t targeting = 0;
    switch (command) {
    case 0:
    case 1:
    case 5:
    case 6:
        a.timer = static_cast<uint32_t>(motionActFrame(*a.form, motionType, speed));
        targeting = visual.motion[motionType].targeting;
        if (command == 1 && skill == 0x73)
            targeting = 2;
        break;
    case 4:   // talk
        switch (a.talkType) {
        case 1:
        case 3:
        case 4:
        case 2:
            a.timer = 0x23;
            setCameraState(a.talkType == 2 ? kCameraEnemySide : kCameraCommandBad);
            addWordPacket(0, 0x1e, uniqueOf(a), a.form.get(), 0);
            break;
        case 0:
        case 5:
        case 6:
            a.timer = 0;
            break;
        default: break;
        }
        break;
    default:
        a.timer = 0;
        break;
    }
    diag::print(diag::Message::ActTime, static_cast<int32_t>(a.timer));

    // The skill's cost.
    if (a.runerr == 0 && command == 1) {
        const NormalSkill& ns = dat::normalSkill(checkedSkill(skill));
        if (ns.costtype == 1) {   // HP
            const int32_t cost = dat::skillCost(*a.work, checkedSkill(skill));
            int32_t hp;
            if (ns.flag & 8) {   // all of it, once the hit lands
                const int32_t delay = (skill >= 0x73 && skill < 0x75) ? 0x53 : 0x3c;
                addHpMpPacket(static_cast<int32_t>(a.timer) + delay, uniqueOf(a), a.form.get(), -0x7fff, 0);
                hp = -0x7fff;
            } else {
                hp = -cost;
                addHpMpPacket(1, uniqueOf(a), a.form.get(), hp, 0);
            }
            addTimeListHp(a, a.form->formindex, hp);
        } else if (ns.costtype == 2) {   // MP
            addHpMpPacket(1, uniqueOf(a), a.form.get(), -dat::skillCost(*a.work, checkedSkill(skill)), 1);
        }
    }

    switch (command) {
    case 1:
    case 5:
    case 6:
        nb::MakeSkillEffectPacket(0, static_cast<int32_t>(a.timer), a, *a.form, hitEffectByte(effectSkill(skill), 2), a.form->motiontype, skill);
        break;
    case 7:
        addHitEffectPacket(0, uniqueOf(a), *a.form, 5);
        break;
    default: break;
    }
    switch (command) {
    case 0:
    case 1:
    case 5:
    case 6:
        ai::setNormalAttack(*a.work);
        deletePacketsOfType(kSkillColorOff);
        eff::BTLSkillEnd();
        eff::BTLSkillSetFormationInfo(a.party->formindex, a.select & 0xffff);
        eff::BTLSkillStart(command == 0 ? 0 : effectStartSkill(skill), 0);
        break;
    case 3:
        setCameraState(kCameraCommandBad);
        break;
    default: break;
    }
    diag::print(diag::Message::SelectBits, a.party->formindex, static_cast<int32_t>(a.select));

    // The targets.
    if (command != 4) {
        if (targeting == 2 && (command == 1 || command == 5)) {
            const uint8_t type = dat::normalSkill(skill).targettype;
            if (type == 0)
                targeting = 4;
            else if (type < 3)
                targeting = 5;
        }
        nb::MakeTargetPacket(targetSpeed, 1, a, *a.form, a.select & 0xffff, targeting);
    }
    for (int32_t i = 0; i < 16; ++i) {
        if (!(a.select & 1u << i))
            continue;
        Formation& target = guest::table<Formation>(main.form.address)[i];
        if (a.work->nowcommand == 4) {
            nb::MakeTargetPacket(ee::Float::fromInt(1), 0, a, target, 1u << (a.form->formindex & 31), 1);
        } else if (a.work->nowcommand == 6 && (target.stat & 0x41) == 0x41) {   // a summon slot taken
            makeReturnPackets(0, uniqueOf(a), main.party[target.partyindex]);
            addHitEffectPacket(0, uniqueOf(a), target, 5);
        }
    }

    // A unit taking its turn ends the other side's guard (buff 0x10).
    if (a.runerr == 0) {
        const bool enemy = (a.party->flag & PartyFlag::EnemySide) != 0;
        for (int32_t i = enemy ? 0 : 4; i < (enemy ? 4 : 14); ++i) {
            const uint32_t stat = guest::table<const Formation>(main.form.address)[i].stat;
            if ((stat & 1) && (stat & 0x40) && (stat & 8))
                addBuff(i, 0x10, 1, false);
        }
    }
    nb::PanelAllShow();
    nb::PanelPressGaugeShow();
    if (command == 3 && (main.stat & BattleStat::EnemyTurn))
        setCameraState(kCameraEnemyBad);

    // The help line.
    if (!kBuild.vanilla)
        fr::frSetBaseWidth(0x14);
    switch (a.work->nowcommand) {
    case 0:
        if (passiveActive(*a.work, skill::AttackAll))
            showSkillName(skill::AttackAll);
        else
            showCommandName(a.work->nowcommand);
        break;
    case 1: {
        // Four bosses' skill 0xE2 has a name of its own (not in the first
        // release).
        const uint16_t id = a.work->id;
        if (!kBuild.vanilla && id >= 0x159 && id <= 0x15c && a.work->nowindex == 0xe2) {
            static constexpr int32_t kNames[] = {0x1f3, 0x1f0, 0x1f1, 0x1f2};
            showSkillName(kNames[id - 0x159]);
        } else if (a.work->nowindex != 0xf7) {
            showSkillName(a.work->nowindex);
        }
        break;
    }
    case 2:
    case 3:
    case 6:
        showCommandName(a.work->nowcommand);
        break;
    case 4:
        if (a.talkType == 0)
            showSkillName(a.work->nowindex);
        break;
    case 5:
        showItemName(a.work->nowindex);
        break;
    case 7:
        if (isPlayerSide(a.form->formindex)) {
            if (a.stat & 0x20)
                setStatusMessage(a, 0x32, 1, a.work->id);
            else
                showCommandName(a.work->nowcommand);
        } else {
            setStatusMessage(a, (a.stat & 0x20) ? 0x34 : 0xa, 1, a.work->id);
        }
        break;
    default: break;
    }
    fr::frSetBaseWidth(-1);
}

// CheckAction_READY @ 0x00255260: waits for what READY started loading
// (seqcnt): the motion's sound bank (0), the skill's sound file (1) and its
// bank (2), the effect file (3); then (5) for the hit's frame, and goes on
// by command: attacks, skills, items and summons to SKILL (8), escape to
// ESCAPE (13), pass and others to WAIT (12), talk to NEGO (9), command 7 to
// RETURN (14), showing a pending status line.
int32_t updateReady(ActionProcessData& a)
{
    switch (a.seqcnt) {
    case 0:
        ++a.skilltime;
        if (a.motionSound != 0) {
            if (!snd::BankReady(formationMotionBank(*a.form, a.motion))) {
                diag::print(diag::Message::MotionSoundWait);
                return 0;
            }
            a.data->stat &= ~0x200u;
            addSoundPacket2(0, uniqueOf(a), formationMotionBank(*a.form, a.motion));
        }
        a.hEffBTL = 0;
        a.seqcnt = a.hSkillSe ? 1 : a.hBed ? 3 : 5;
        return 0;
    case 1: {
        ++a.skilltime;
        if (!file::CheckEnd(a.hSkillSe)) {
            diag::print(diag::Message::LoadSeOrBed);
            return 0;
        }
        a.hSkillMem = file::GetMemHandle(a.hSkillSe);
        const int32_t size = file::GetLoadSize(a.hSkillSe);
        const uint32_t data = mem::HandleAcquirePointer(a.hSkillMem);
        diag::print(diag::Message::SeSize, size);
        if (!snd::BankReady(a.skillmidi)) {
            snd::SetBankSource(data, size);
            a.data->stat |= 0x200;
        }
        a.seqcnt = 2;
        return 0;
    }
    case 2:
        ++a.skilltime;
        if (!snd::BankReady(a.skillmidi)) {
            diag::print(diag::Message::SeWait2);
            return 0;
        }
        diag::print(diag::Message::SeOk, static_cast<int32_t>(a.skillmidi));
        mem::HandleFree(a.hSkillMem);
        file::RequestRelease(a.hSkillSe);
        a.seqcnt = a.hBed ? 3 : 5;
        a.data->stat &= ~0x200u;
        return 0;
    case 3: {
        ++a.skilltime;
        if (!file::CheckEnd(a.hBed)) {
            diag::print(diag::Message::LoadBed);
            return 0;
        }
        diag::print(diag::Message::BedOk);
        const uint32_t handle = file::GetMemHandle(a.hBed);
        a.hEffBTL = eff::BTLLoad(mem::HandleAcquirePointer(handle));
        mem::HandleFree(handle);
        file::RequestRelease(a.hBed);
        a.seqcnt = 5;
        return 0;
    }
    case 5:
        if (a.timer != 0 && a.seqtime < a.timer)
            return 0;
        switch (a.work->nowcommand) {
        case 0: case 1: case 5: case 6: setNextState(a, kActionSkill); break;
        case 2: setNextState(a, kActionEscape); break;
        case 3: case 8: case 9: case 10: setNextState(a, kActionWait); break;
        case 4: setNextState(a, kActionTalk); break;
        case 7: setNextState(a, kActionReturn); break;
        default: break;
        }
        if (a.statusMessage > 0) {
            showStatusMessage(a.data->statusMessageTable, a.statusMessage, a.statusVarType, a.statusVarValue);
            a.statusMessage = 0;
        }
        return 1;
    default:
        return 0;
    }
}

// SetAction_SKILL @ 0x00255650: the action's result, queued as packets. The
// skill's effect plays its first cut on the user (or, with no effect, the
// user waits 10 frames); then for each target in hit order (GetKoukaList):
// how the skill lands (nbGetKoukaType), its effect's second cut on the
// target, and the result (damage and the rest, a dodge, a miss, a summon,
// an escape, ...), each target a few frames after the last by the skill's
// hit spacing. After the targets: Drain Attack's (0x12E) share of an
// attack's damage, the user's own healing skills, its death if the skill
// killed it, Ahriman's counter, the status line, the press turns used, and
// the hit stop.
void enterSkill(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    const int32_t uid = uniqueOf(a);
    const int32_t self = a.form->formindex;
    const ee::Float speed = ee::Float::fromInt((a.stat & 0x100) ? 3 : 1);
    const int32_t wait10 = (ee::Float::fromInt(10) / speed).toInt();
    a.newpresstype = 0;
    if (!kBuild.vanilla)
        main.piercedResistance = 0;

    // The first cut, on the user.
    uint32_t cut = 0;
    int32_t frame = 0;   // where the targets' results start
    if (a.hEffBTL == 0 || a.runerr != 0) {
        setTimeList(a, self, 0, wait10, wait10);
    } else {
        cut = eff::BTLCutCreate(a.hEffBTL, 1, a.form.get(), 1);
        eff::BattleCut& c = *guest::table<eff::BattleCut>(cut);
        const uint32_t motion = eff::motionChangeFrame(c);
        frame = static_cast<int32_t>(eff::cutEndFrame(c));
        diag::print(diag::Message::SkillMotionCut, static_cast<int32_t>(motion), frame);
        setTimeList(a, self, 0, frame, frame);
    }
    // A motion that ends by holding: the user is busy until it ends.
    if (a.form->motionend == 2 && a.form->motiontype >= 0 && a.form->motionenddata >= 0) {
        const ee::Float rate = motionSpeed(*a.form, a.form->motiontype, speed);
        const int32_t actframe = motionActFrame(*a.form, a.form->motiontype, speed);
        const int32_t busy = (ee::Float::fromInt(a.form->motionenddata) / rate).toInt() - actframe + wait10;
        overwriteTimeList(a, self, 0, busy, busy);
    }

    int32_t skill = 0;
    switch (a.work->nowcommand) {
    case 1: skill = skillPlayed(a.work->nowindex); break;
    case 5: skill = itemSkillFor(a, a.work->nowindex); break;
    case 6: skill = 0xff; break;
    default: break;
    }
    noteActionKind(a, a.work->nowcommand, skill);

    // (By version the hits follow the acting skill: checkedSkill.)
    HitOrderEntry order[32];
    hitOrder(a, order, a.select, checkedSkill(skill));
    ee::Float ratio = ee::Float::fromInt(1);   // shrinks hit by hit (nbGetGensyoRitu)
    int32_t start = frame;                     // the last target's start
    int32_t cutLength = 0;                     // cut 2's length
    uint32_t results = 0;                      // for the effect: repelled 4, drained 8, nulled 0x10, dodged 0x20, missed 0x40
    int32_t targets = 0;
    bool showEffect = false, summoned = true, allRepelled = true, allDrained = true, anyLanded = false, anyHit = false;
    int32_t lastKind = 0;   // (with no target: what the process scheduler leaves; 0 in the tests)
    for (int32_t i = 0; i < 32 && order[i].formindex >= 0; ++i) {
        const int32_t target = order[i].formindex;
        start = std::max<int32_t>(a.timelist[target].lockframe, frame);
        int32_t kind = static_cast<int32_t>(resolveEffect(checkedSkill(skill), self, target));
        diag::print(diag::Message::SkillEffectResult, kind);
        if (a.type == 4 && kind > 0 && kind < 3)
            kind = 3;   // (type 4 can't be repelled or drained: nulled)
        lastKind = kind;
        // Repelled and drained results show no second cut.
        const bool deflected = kind < 3;
        int32_t hitFrame = 0;
        if (a.hEffBTL != 0 && i < 16 && (kind == 0 || (kind > 0 && kind <= 14 && !deflected))) {
            hitFrame = static_cast<int32_t>(eff::motionChangeFrame(a.hEffBTL, 2));
            cutLength = static_cast<int32_t>(eff::cutEndFrame(a.hEffBTL, 2));
            diag::print(diag::Message::SkillCut3Frames, hitFrame, cutLength);
            setTimeList(a, target, start, 0, cutLength + 1);
        }
        start += hitFrame;
        addFormationFlagPacket(start, uid, &formAt(a, target), 0, 0x2000);
        if (kind != 1 && kind != 2)
            allRepelled = false;
        if (kind != 2)
            allDrained = false;
        if (kind == 0 || kind == 2 || kind == 3)
            anyLanded = true;
        if (kind == 0)
            anyHit = true;

        const int32_t count = order[i].count;
        switch (kind) {
        case 0: case 1: case 2: case 3: queueHitResult(a, kind, checkedSkill(skill), self, target, count, start, ratio); break;
        case 4: queueDodge(a, skill, self, target, count, start); break;
        case 5: queueMiss(a, skill, self, target, count, start); break;
        case 6:
            if (queuePlayerSummon(a, skill, self, target, start) == 0)
                summoned = false;
            break;
        case 7: queueAnalyze(a, target, start); break;
        case 8: queueTrafuri(a, target, start); break;
        case 9: queueMaccaThrow(a, target, start); break;
        case 10: queueEnemyEscape(a, target, start); break;
        case 11: queueOngyokiFound(a, skill, self, target, count, start); break;
        case 12: queueAurora(a, target, start); break;
        case 13: queueExtraPress(a, extraPressSkill(skill)); break;
        case 14: queueFlareCharge(a, start); break;
        default: break;
        }
        printResultKind(kind);
        // Against Ongyo-Ki's clones a hit on an enemy (but not attribute 14) shows them up.
        if (kind == 0 && (main.stat & 0x400) && target >= 4 && target < 14 &&
            static_cast<int32_t>(skillAttribute(skill)) != 14)
            queueOngyokiClonesVanish(a, target, start + 5);

        if (a.hEffBTL != 0 && i < 16 && summoned && (kind == 0 || (kind > 0 && kind < 15 && !deflected)) &&
            !(!kBuild.vanilla && kind == 3 && skill == 0x107)) {
            int16_t look = 1;   // the cut's look on the target: hit, dodged or missed (0x20), dead (3)
            const bool dead = timeListDead(a, target);
            if (kind == 4 || kind == 5)
                look = 0x20;
            if (dead)
                look = 3;
            addSkillEffectPacket2(start - hitFrame, cutLength, uid, a.hEffBTL, 2, &formAt(a, target), look);
            addSoundPacket(start - hitFrame, uid, static_cast<uint32_t>(skill + 0x200) << 16 | 1);
        }
        ratio = ratio * reductionRate(skill);
        if (clearsFocus(skill))
            setBuffCounter(self, 0xf, 0);
        if (kind == 3) {   // nulled: the attribute's guard is spent
            switch (skillAttribute(skill)) {
            case Attribute::Ice: setBuffCounter(target, 9, 0); break;
            case Attribute::Fire: setBuffCounter(target, 10, 0); break;
            case Attribute::Expel: setBuffCounter(target, 0xc, 0); break;
            case Attribute::Death: setBuffCounter(target, 0xb, 0); break;
            default: break;
            }
        }
        if (!kBuild.vanilla && (skill == 0x103 || skill == 0x104))
            setBuffCounter(target, 0xb, 0);
        if (kind == 1)
            addPassiveEffectEndPacket(start, uid);
        // The skill's hit spacing (read for each target: by version the
        // acting skill's, which a result can clear).
        switch (hitEffectByte(checkedSkill(skill), 1)) {
        case 1: case 5: case 9: case 13: frame += 5; break;
        case 2: case 6: case 10: case 14: frame += 8; break;
        case 3: case 7: case 11: case 15: frame += 10; break;
        case 4: case 8: case 12: frame += 1; break;
        default: break;
        }
        switch (kind) {
        case 1: results |= 4; break;
        case 2: results |= 8; break;
        case 3: results |= 0x10; break;
        case 4: results |= 0x20; break;
        case 5: results |= 0x40; break;
        default: break;
        }
        if (!deflected || kind < 1)
            showEffect = true;
        ++targets;
    }
    if (!kBuild.vanilla && allRepelled && skill == 0x108)
        showEffect = true;
    if (!kBuild.vanilla && allDrained && (skill == 0x106 || skill == 0x107))
        showEffect = true;

    // Drain Attack: an attack heals the user a share of the damage it did.
    const int32_t drainMark = skill == 0 ? drainAttackMark(a.autoskill) : -1;
    if (drainMark >= 0 && passiveActive(*a.work, skill::DrainAttack) && !timeListDead(a, self)) {
        a.autoskill = drainMark;
        const int32_t at = lastDoneFrame(a);
        const SpecialSkill& drain = dat::specialSkill(skill::DrainAttack);
        if (drain.n == 0)
            divideByZeroTrap();
        const int32_t hpShare = a.allhpdamage / drain.n, mpShare = a.allmpdamage / drain.m;
        const int32_t hp = hpShare != 0 ? hpShare : -1, mp = mpShare != 0 ? mpShare : -1;
        if (hp > 0 || mp > 0) {
            nb::MakeHealPackets(at, uid, a.form.get(), 3, hp, mp, 0);
            if (hp > 0)
                addTimeListHp(a, self, hp);
            const int32_t wait = (ee::Float::fromInt(20) / speed).toInt();
            setTimeList(a, self, at, wait, wait);
        }
    }
    // Skills that heal the user a share of its maximum HP (0x11E) or MP (0x109;
    // neither in the first release).
    if (!kBuild.vanilla && skill == 0x11e && a.autoskill == 0 && !timeListDead(a, self) && a.runerr == 0) {
        a.autoskill = skill::DrainAttack;   // (only for lastDoneFrame)
        const int32_t at = lastDoneFrame(a);
        a.autoskill = 0;
        const int32_t share = static_cast<int32_t>(a.work->maxhp * static_cast<uint32_t>(selfHealPercent(*a.work, dat::normalSkill(0x11e).buffAmount))) / 100;
        const int32_t hp = share != 0 ? share : -1;
        if (hp > 0) {
            nb::MakeHealPackets(at, uid, a.form.get(), 0, hp, -1, 0);
            addTimeListHp(a, self, hp);
            const int32_t wait = (ee::Float::fromInt(20) / speed).toInt();
            setTimeList(a, self, at, wait, wait);
        }
    }
    if (!kBuild.vanilla && skill == 0x109 && a.autoskill == 0 && !timeListDead(a, self) && a.runerr == 0) {
        a.autoskill = skill::DrainAttack;
        const int32_t at = lastDoneFrame(a);
        a.autoskill = 0;
        const int32_t share = static_cast<int32_t>(a.work->maxmp * static_cast<uint32_t>(dat::normalSkill(0x109).mpn)) / 100;
        const int32_t mp = share != 0 ? share : -1;
        if (mp > 0) {
            nb::MakeHealPackets(at, uid, a.form.get(), 0, -1, mp, 0);
            const int32_t wait = (ee::Float::fromInt(20) / speed).toInt();
            setTimeList(a, self, at, wait, wait);
        }
    }

    eff::setSkillState(results);
    const int32_t end = lastDoneFrame(a);
    overwriteTimeList(a, self, 0, (ee::Float::fromInt(end) * ee::Float::fromBits(0x3f4ccccc)).toInt(), -1);   // x0.8
    if (timeListDead(a, self) && !(a.party->flag & kPartyGone)) {   // the skill killed its user
        makeDeathVisualPackets(start, uid, *a.form, 0, 1);
        setTimeList(a, self, start, 0x1e, 0x1e);
        queueDeath(a, self);
    }
    if (!timeListDead(a, self) && a.type == 0)
        checkAhrimanCounter(a);
    diag::print(diag::Message::SkillTotalDamage, a.allhpdamage, a.allmpdamage);
    diag::print(diag::Message::SkillEndFrame, end);
    diag::print(diag::Message::SkillFreeFrame, lastFreeFrame(a));

    // The status line.
    bool holdLine = false;
    if (a.runerr == 0) {
        if (a.autoskill >= skill::Might && a.autoskill <= skill::DrainAttack)
            showSkillName(a.autoskill);   // the passive that fired
        const int32_t lineSkill = statusSkill(skill);
        int32_t message = versionStatusMessage(lineSkill, lastKind);
        if (message == 0) switch (lineSkill) {
        case 0x34: message = 0x10; break;
        case 0x35: message = 0x14; break;
        case 0x36: message = 0x12; break;
        case 0x39: message = 0x16; break;
        case 0x40: message = 0x18; break;
        case 0x41: message = 0x1a; break;
        case 0x42: message = 0x1c; break;
        case 0x43: message = 0x1e; break;
        case 0x44: message = 0x20; break;
        case 0x45: message = 0x24; break;
        case 0x46: message = 0x22; break;
        case 0x4d: message = 0x5c; break;
        case 0xcb: message = 0x50; break;
        case 0xcc: message = 0x52; break;
        case 0xcd: message = 0x54; break;
        case 0xce: message = 0x56; break;
        // (the first release has none of these, nor Pierce)
        case 0x109: message = kBuild.vanilla ? 0 : 0x54; break;
        case 0x110: message = kBuild.vanilla ? 0 : 0x60; break;
        case 0x112: message = kBuild.vanilla ? 0 : 0x5c; break;
        case 0x114: message = kBuild.vanilla ? 0 : 0x62; break;
        case 0x11a: message = !kBuild.vanilla && anyLanded ? 0x16 : 0; break;
        default:
            if (!kBuild.vanilla && (anyHit || !pierceNeedsHit()) && main.piercedResistance != 0)
                message = 100;   // Pierce
            break;
        }
        if (message != 0)
            setStatusMessage(a, message, -1, 0);
        if (buffSkillError(lineSkill, a.select) != 0) {
            diag::print(diag::Message::NoBuffEffect);
            setStatusMessage(a, 0x44, -1, 0);
        }
        skill = skillAfterStatus(lineSkill);
        holdLine = holdsStatusLine(a.statusMessage);
        if (!holdLine && a.statusMessage > 0 && (a.stat & 0x20))
            a.statusMessage += (a.statusMessage & 1) ? -1 : 1;   // the other side's wording
    }
    if (!holdLine && a.statusMessage > 0) {
        if (skill == 0x31 || skill == 0x32) {   // revivals: after the user waits
            start += 0x14;
            setTimeList(a, self, start, 0x28, 0x28);
        }
        addStatusMessagePacket(start, uid, static_cast<int16_t>(a.statusMessage), static_cast<int16_t>(a.statusVarType),
                               a.statusVarValue);
        a.statusMessage = 0;
    }

    // The first cut ends with the action.
    if (cut != 0) {
        eff::BattleCut& c = *guest::table<eff::BattleCut>(cut);
        eff::setDrawEndFrame(c, static_cast<uint32_t>(end));
        addSkillColorOffPacket(end, uid);
        if (!showEffect) {
            eff::setCutCameraState(c);
        } else {
            addSkillEffectPacket(0, end, uid, cut);
            addSoundPacket(0, uid, !kBuild.vanilla && allDrained && skill == 0x106 ? 0x3060001u : static_cast<uint32_t>(skill + 0x200) << 16);
        }
    } else {
        addSkillColorOffPacket(end, uid);
    }
    if (a.form->motionend == 1)
        addMotionStopClearPacket(end * 0x3c / 100, uid, a.form.get());

    // The press turns.
    if (targets < 1) {
        makePressPackets(start, uid, ee::Float::fromInt(-1));
        makePressResultPackets(start, uid, 0, skill);
    } else if (a.type == 0) {
        makePressPackets(start, uid, a.press);
        makePressResultPackets(start, uid, a.newpresstype, skill);
        diag::print(diag::Message::SkillPress, static_cast<int64_t>(ee::Double::fromFloat(a.press).bits()));
    }
    if (a.newaddpresstype > 0)
        makePressResultPackets(start + 0x14, uid, a.newaddpresstype, skill);

    // A hit stop, when the turn's last press icon goes.
    if (a.hitstopframe > 0 && evt::BitCheck(0xc09)) {
        const int32_t side = (main.stat & 8) ? main.enemypcnt : main.playerpcnt;
        const int32_t left = ((main.press3 + a.press / ee::Float::fromInt(side)) * ee::Float::fromInt(100)).toInt();
        if (left < 1)
            addHitStopPacket(a.hitstopframe, uid);
    }
}

// CheckAction_SKILL @ 0x00256A78: on to the aftermath (CHECK1, 0x12).
int32_t updateSkill(ActionProcessData& a)
{
    setNextState(a, kActionAftermath);
    return 1;
}

// SetAction_BADWAIT @ 0x00254010: the camera on the ailing unit.
void enterAilmentWait(ActionProcessData& a)
{
    a.stat |= 0x20;
    setCameraState((a.data->stat & BattleStat::EnemyTurn) ? kCameraEnemyBad : kCameraCommandBad);
}

// CheckAction_BADWAIT @ 0x00254058: shows the ailment AI's status line at
// frame 5 and waits, then on to READY: until frame 31 for a lost turn (8)
// or the curse's damage (10), else until the status line has gone or frame
// 41.
int32_t updateAilmentWait(ActionProcessData& a)
{
    if (a.seqtime == 5 && a.statusMessage > 0)
        showStatusMessage(a.data->statusMessageTable, a.statusMessage, a.statusVarType, a.statusVarValue);
    bool done;
    switch (a.work->nowcommand) {
    case 8:
    case 10: done = a.seqtime >= 31; break;
    default: done = a.seqtime >= 41 || a.statusMessage == 0; break;
    }
    if (done) {
        setNextState(a, kActionReady);
        a.statusMessage = 0;
    }
    return done ? 1 : 0;
}

// SetAction_CHECK1 @ 0x00257488: the action's aftermath. A poisoned unit
// still standing loses an eighth of its HP (not after using item 1, nor once
// its enemies are all down or the battle has ended). Every unit the action
// killed dies, after the last unit is free. A hidden unit (form field 0xA4 =
// 2) reappears once the action is over. The passive skills' effects end at
// 70% of the action and the stock panel fades out at its end.
void enterAftermath(ActionProcessData& a)
{
    const int32_t self = a.form->formindex;
    if (!timeListDead(a, self) && badStat(self) == static_cast<uint32_t>(Ailment::Poison) &&
        !otherSideAllDead(a, self) && a.data->endtype == 0) {
        const UnitWork& unit = *a.work;
        if (!(unit.nowcommand == 5 && unit.nowindex == 1) && !(a.party->flag & 0x20))
            queueDamage(a, unit.maxhp >> 3);
    }
    const int32_t free = lastFreeFrame(a);
    for (int32_t f = 0; f < 16; ++f) {
        Formation& form = formAt(a, f);
        if (!(form.stat & FormationStat::Present) || !(form.stat & FormationStat::CheckParty) || !timeListDead(a, f))
            continue;
        if (a.data->party[form.partyindex].flag & 0x20)
            continue;
        diag::print(diag::Message::DeadFormindex, f);
        makeDeathVisualPackets(free, uniqueOf(a), form, 0, 1);
        setTimeList(a, f, free, 30, 30);
        queueDeath(a, f);
        setTimeList(a, f, free, 20, 20);
    }
    if (!timeListDead(a, a.form->formindex)) {
        int32_t start = lastDoneFrame(a);
        lastFreeFrame(a);
        Formation& form = *a.form;
        const int32_t delay = (form.motionend != 2 && !(a.stat & 0x100)) ? 3 : 0;
        if (form.stat & 0x10) {
            if (form.motionend == 2)
                setTimeList(a, form.formindex, start, 6, 6);
            else
                setTimeList(a, form.formindex, start, delay + 1, delay + 1);
            start += delay;
            if (a.form->motionend == 2) {
                makeFadeInPackets(start, uniqueOf(a), a.form.get(), 0, 2, 4, 4);
                addFormationShowPacket(start, uniqueOf(a), a.form.get(), 0);
                if (a.form->motionend == 2)
                    addMotionStopClearPacket(start, uniqueOf(a), a.form.get());
            }
        }
    }
    a.packettime = static_cast<uint32_t>(lastDoneFrame(a));
    addPassiveEffectEndPacket(static_cast<int32_t>(a.packettime * 70u / 100u), uniqueOf(a));
    if (a.stat & 0x400) {
        const int32_t fade = static_cast<int32_t>(a.packettime) - 10;
        addStockPanelFadeOutPacket(fade < 0 ? 0 : fade, uniqueOf(a));
        addStockPanelEndPacket(static_cast<int32_t>(a.packettime) - 1, uniqueOf(a));
    }
    diag::print(diag::Message::AllFrame, a.packettime);
}

// CheckAction_CHECK1 @ 0x002577D8: waits for an Analyze to be dismissed
// (either button, pad bytes 0x2F5831 / 0x2F5833) and for the action's
// packets to be within 15 frames of their end. Then the turn order moves on,
// the talk checks and death scripts run, and the unit's command is
// remembered for the next turn (for the battle, and for an attack, a skill
// or a pass, the unit; skills 0x31 and 0x32 and other commands forget it;
// the counters and throwing Macca leave it as it was). On to CHECK3.
int32_t updateAftermath(ActionProcessData& a)
{
    if (a.stat & 0x10) {
        const int8_t* pad = guest::table<const int8_t>(addr(0x002f5830));
        if (pad[1] >= 0 && pad[3] >= 0) {
            setPacketTypeFlag(14, 2, 1);
            return 0;
        }
        a.stat &= ~0x10u;
        nb::PanelAnalyzeEnd();
        a.packettime = 21;
        setPacketTypeFlag(14, 2, 0);
        return 0;
    }
    if (a.packettime >= 16) {
        --a.packettime;
        return 0;
    }
    nb::updateOrder();
    if (!timeListDead(a, a.form->formindex))
        checkBegForLife(a);
    if (!timeListDead(a, a.form->formindex))
        checkAskToJoin(a);
    if (!timeListDead(a, a.form->formindex) && a.form->motionend == 3)
        a.form->stat |= 0x4000;
    checkDeathScripts(a);
    MainProcessData& main = *a.data;
    UnitWork* unit = GetUnitWorkPointer(main, *a.party);
    if (!unit) {
        main.prevflag = 0;
        main.previndex = 0;
        main.prevcommand = 0;
        main.prevcommind = 0;
    } else {
        main.previndex = static_cast<int16_t>(a.partyindex);
        main.prevcommand = static_cast<uint16_t>(unit->nowcommand);
        main.prevcommind = unit->nowindex;
        diag::print(diag::Message::PrevCommind, unit->nowindex);
        main.prevflag = (a.stat & 8) ? 1 : 0;
        bool remember = false;
        switch (unit->nowcommand) {
        case 0:   // attack
        case 3:   // pass
            remember = true;
            break;
        case 1:   // a skill
            if (unit->nowindex == 0x31 || unit->nowindex == 0x32)
                dat::clearCommandMemory(*unit);
            else
                remember = !(unit->nowindex >= 0xa4 && unit->nowindex <= 0xa6) && unit->nowindex != 0xf7;
            break;
        default:
            dat::clearCommandMemory(*unit);
            break;
        }
        if (remember) {
            unit->prevcommand = unit->nowcommand;
            unit->prevtform = unit->nowtform;
            unit->previndex = unit->nowindex;
            unit->prevtarea = unit->nowtarea;
        }
    }
    setNextState(a, kActionPlayOut);
    return 1;
}

// SetAction_DEADSCRIPT @ 0x00253D00: runs a dying unit's script (the
// procedure is in adata).
void enterDeathScript(ActionProcessData& a)
{
    clearTimeList(a);
    initTimeListHp(a);
    ai::script::start(a, a.adata);
}

// CheckAction_DEADSCRIPT @ 0x00253D38: once the script ends, the unit
// fades out and leaves; on to CHECK1.
int32_t updateDeathScript(ActionProcessData& a)
{
    if (dds3::ExistProcess(a.data->AiScriptProcessID))
        return 0;
    a.data->AiScriptProcessID = 0;
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    makeFadeOutPackets(0, uniqueid, a.form.get(), 0, 10, 10, 10);
    addReturnPacket(25, uniqueid, a.party.get(), 1);
    setTimeList(a, a.form->formindex, 0, 30, 30);
    setNextState(a, kActionAftermath);
    return 1;
}

// SetAction_WAIT @ 0x002570B8: the unit passes (half a press turn icon),
// loses its turn to an ailment, or takes the curse's damage (15% of its
// maximum HP).
void enterWait(ActionProcessData& a)
{
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    switch (a.work->nowcommand) {
    case 3:   // pass
        makePressPackets(0, uniqueid, ee::Float::fromBits(0xbf000000));    // -0.5
        makePressResultPackets(0, uniqueid, 1);
        setTimeList(a, a.form->formindex, 0, 5, 5);
        break;
    case 8:   // an ailment took the turn
        makePressPackets(0, uniqueid, ee::Float::fromInt(-1));
        makePressResultPackets(0, uniqueid, 0);
        setTimeList(a, a.form->formindex, 0, 5, 5);
        break;
    case 10:  // the curse's damage
        queueDamage(a, static_cast<int32_t>(static_cast<uint32_t>(a.work->maxhp) * 15u / 100u));
        makePressPackets(0, uniqueid, ee::Float::fromInt(-1));
        makePressResultPackets(0, uniqueid, 0);
        break;
    default:
        break;
    }
}

// CheckAction_WAIT @ 0x00257210
int32_t updateWait(ActionProcessData& a)
{
    setNextState(a, kActionAftermath);
    return 1;
}

// SetAction_ESCAPE @ 0x00257230: one more attempt; all the press turns go.
// A successful escape ends the battle (endtype 3); a failed one may give an
// enemy a free action.
void enterEscape(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    if (main.esccnt != 0xff)
        ++main.esccnt;
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    makePressPackets(0, uniqueid, ee::Float::fromInt(-10));
    makePressResultPackets(0, uniqueid, 8);
    if (rollEscape(*a.data))
        a.data->endtype = 3;
    else
        checkFreeActionAfterEscape(a);
}

// CheckAction_ESCAPE @ 0x002572C0: at frame 15 a failed escape is done; at
// frame 30 a successful one fades the screen to white with a sound.
int32_t updateEscape(ActionProcessData& a)
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
        addSoundPacket(0, static_cast<int32_t>(guest::addressOf(&a)), 0x10000);
        setTimeList(a, a.form->formindex, 0, 17, 17);
        break;
    default:
        return 0;
    }
    setNextState(a, kActionAftermath);
    return 1;
}

// SetAction_RETURN @ 0x002573A8: a devil goes back to the stock (half a
// press turn icon).
void enterReturn(ActionProcessData& a)
{
    diag::print(diag::Message::Returning);
    if (a.data->stat & BattleStat::EnemyTurn)
        setCameraState(kCameraEnemySide);
    const int32_t uniqueid = static_cast<int32_t>(guest::addressOf(&a));
    makeReturnPackets(0, uniqueid, *a.party);
    setTimeList(a, a.form->formindex, 0, 40, 40);
    makePressPackets(10, uniqueid, ee::Float::fromBits(0xbf000000));    // -0.5
    makePressResultPackets(10, uniqueid, 9);
}

// CheckAction_RETURN @ 0x00257440
int32_t updateReturn(ActionProcessData& a)
{
    setNextState(a, kActionAftermath);
    return 1;
}

// SetAction_NEGO @ 0x00256A98: talks start between the first slot marked
// as the talks' player side (formation stat 0x100) or enemy side (0x200)
// and the acting unit's own slot, which wins for its side; the battle
// panel stops taking input.
void enterTalk(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    int32_t player = -1, enemy = -1;
    for (int32_t i = 0; i < 16; ++i) {
        const uint32_t stat = guest::table<const Formation>(main.form.address)[i].stat;
        if (!(stat & FormationStat::Present) || !(stat & FormationStat::Selected))
            continue;
        if (stat & 0x100) {
            player = i;
            break;
        }
        if (stat & 0x200) {
            enemy = i;
            break;
        }
    }
    if (a.form->stat & 0x100)
        player = a.form->formindex;
    else if (a.form->stat & 0x200)
        enemy = a.form->formindex;
    diag::print(diag::Message::TalkSides, player, enemy);
    nb::PanelSetEnabled(false);
    main.talkEnemySlot = static_cast<int16_t>(enemy);
    main.talkPlayerSlot = static_cast<int16_t>(player);
    nb::StartTalkProcess(a, player, enemy, a.talkType, a.work->nowindex);
}

// SetAction_NEGORESULT @ 0x00256C00: what the talks' result (negoresult)
// does. 1 and 4: the side loses press (1, or 10 for 4: the talks went
// wrong) and the enemy's motions reset; 2: the enemy leaves; 3: it joins
// (nbGetNakama) and leaves the field; 5: it and every other enemy of its
// kind leave; 6 and 9: every enemy leaves (9: it joins first); 7: only the
// motions reset; 8: nothing, not even the camera. The press packets come
// only for talks the Demi-fiend started, or for an ailment's talks (type 1,
// 2) with results 2..4 and the other types (3, 4) with result 4. With no
// enemy left the battle ends (endtype 9).
void enterTalkResult(ActionProcessData& a)
{
    MainProcessData& main = *a.data;
    bool press = false, motion = false, camera = true;
    int32_t ptype = 0;
    // Every active enemy (of the talker's kind for result 5) walks off at a
    // random frame within 20.
    auto leave = [&](int32_t only) {
        for (int32_t i = 4; i < 14; ++i) {
            Party& party = main.party[i];
            if (!(party.flag & PartyFlag::Active) || !(party.flag & PartyFlag::EnemySide) || (party.flag & 0x20))
                continue;
            if (only >= 0 && GetUnitWorkPointer(main, party)->id != only)
                continue;
            const int32_t start = sdf::GetRandInt(20);
            makeReturnPackets(start, uniqueOf(a), main.party[i]);
            if (!(main.party[i].flag & 8))
                setTimeList(a, main.party[i].formindex, start, 40, 40);
        }
    };
    switch (main.talkResult) {
    case 1:
        press = true;
        ptype = 0xc;
        motion = true;
        a.press = ee::Float::fromInt(-1);
        break;
    case 2:
    case 3: {
        press = true;
        ptype = main.talkResult == 2 ? 0xc : 0xb;
        Party* party = GetPartyFromFormindex(main.talkEnemySlot);
        if (main.talkResult == 3)
            recruitDevil(*GetUnitWorkFromFormindex(main.talkEnemySlot));
        makeReturnPackets(0, uniqueOf(a), *party);
        setTimeList(a, main.talkEnemySlot, 0, 40, 40);
        a.press = ee::Float::fromInt(-1);
        break;
    }
    case 4:
        press = true;
        ptype = 0xd;
        motion = true;
        a.press = ee::Float::fromInt(-10);
        break;
    case 5:
        leave(GetUnitWorkFromFormindex(main.talkEnemySlot)->id);
        press = true;
        ptype = 0xc;
        a.press = ee::Float::fromInt(-1);
        break;
    case 6:
    case 9:
        if (main.talkResult == 9)
            recruitDevil(*GetUnitWorkFromFormindex(main.talkEnemySlot));
        leave(-1);
        break;
    case 7:
        motion = true;
        break;
    case 8:
        camera = false;
        break;
    default:
        break;
    }
    switch (a.talkType) {
    case 1:
    case 2:
        if (main.talkResult >= 5 || main.talkResult < 2)
            press = false;
        break;
    case 3:
    case 4:
        if (main.talkResult != 4)
            press = false;
        break;
    default:
        break;
    }
    if (press) {
        makePressPackets(0, uniqueOf(a), a.press);
        makePressResultPackets(0, uniqueOf(a), ptype);
    }
    Formation& enemy = guest::table<Formation>(main.form.address)[main.talkEnemySlot];
    if (motion) {
        GetUnitWorkFromFormindex(main.talkEnemySlot);
        setWaitMotion(enemy, 0, ee::Float::fromInt(1));
        startMotion(enemy, 0, 1, ee::Float::fromInt(1));
    }
    if (camera && a.talkType == 0 && (a.form->stat & 0x10))
        cameraOnPair(*a.form, enemy);
    int32_t enemies = 0;
    for (int32_t i = 4; i < 14; ++i)
        if ((main.party[i].flag & PartyFlag::Active) && !(main.party[i].flag & 0x20))
            ++enemies;
    if (enemies == 0)
        main.endtype = 9;
}

// CheckAction_NEGO @ 0x00256B88: waits for the talks to end; on to their
// result (a dead Demi-fiend's talks end with result 8).
int32_t updateTalk(ActionProcessData& a)
{
    if (a.data->TalkProcessID)
        return 0;
    diag::print(diag::Message::TalkResult, a.data->talkResult);
    setNextState(a, kActionTalkResult);
    nb::PanelSetEnabled(true);
    if (dat::isPlayerDead())
        a.data->talkResult = 8;
    return 1;
}

// CheckAction_NEGORESULT @ 0x00257098
int32_t updateTalkResult(ActionProcessData& a)
{
    setNextState(a, kActionAftermath);
    return 1;
}

// SetAction_INVISIBLE @ 0x00257460
void enterInvisible(ActionProcessData&) {}

// CheckAction_INVISIBLE @ 0x00257468
int32_t updateInvisible(ActionProcessData& a)
{
    setNextState(a, kActionAftermath);
    return 1;
}

// SetAction_CHECK3 @ 0x00257A68
void enterPlayOut(ActionProcessData&) {}

// CheckAction_CHECK3 @ 0x00257A70: waits until the action's packets are all played.
int32_t updatePlayOut(ActionProcessData& a)
{
    if (countActionPackets(static_cast<int32_t>(guest::addressOf(&a))) > 0)
        return 0;
    setNextState(a, kActionCleanup);
    return 1;
}

// SetAction_ATO @ 0x00257AB8 ("ato": after)
void enterCleanup(ActionProcessData&) {}

// CheckAction_ATO @ 0x00257AC0: frees the skill's effect.
int32_t updateCleanup(ActionProcessData& a)
{
    if (a.hEffBTL) {
        eff::BTLDelete(a.hEffBTL);
        a.hEffBTL = 0;
    }
    setNextState(a, kActionEnd);
    return 1;
}

// SetAction_END @ 0x00257B08: debug messages for what the action did
// (its stat bits 0x10000 .. 0x200000).
void enterEnd(ActionProcessData& a)
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
int32_t updateEnd(ActionProcessData&) { return 1; }

} // namespace nocturne::nb

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::nb {

#if NOCTURNE_HARDTYPE
namespace {

// Skills shown with another motion type by every devil but the two that
// have it (0x2FE920: skill, two devils, the motion type; up to a 0).
struct MotionException {
    uint16_t skill, devil, otherDevil, motionType;
};
constexpr uint32_t kMotionExceptions = 0x002fe920;

// The effect a pair starts as instead of its stand-in (0x2FDC80: acting
// skill, stand-in, the effect; up to a 0).
struct EffectStart {
    uint16_t acting, standIn, effect, unused;
};
constexpr uint32_t kEffectStarts = 0x002fdc80;

// Status lines of Hardtype's skills, shown when the last target was hit
// (0x2FF140: skill, message; up to a 0).
struct StatusLine {
    uint16_t skill, message;
};
constexpr uint32_t kStatusLines = 0x002ff140;

uint16_t acting() { return hardtype::actingSkill(); }
uint16_t standIn() { return hardtype::standInSkill(); }

} // namespace
#endif

#if NOCTURNE_HARDTYPE
// SetAction_READY @ 0x00254488 (and 0x2FE8D0): a chosen skill plays as its
// stand-in, and the pair is noted (hardtype.hpp); skills 0xA4..0xA6 play as
// themselves and note nothing.
int32_t readySkill(int32_t skill)
{
    if (skill >= 0xa4 && skill < 0xa7)
        return skill;
    const uint16_t standIn = hardtype::standInFor(static_cast<uint16_t>(skill));
    hardtype::actingSkill() = static_cast<uint16_t>(skill);
    hardtype::standInSkill() = standIn;
    return standIn;
}
#else
// SetAction_READY @ 0x00254488: every skill plays as itself; a skill's
// motion is its hit effect's, a summon's type 0x18.
int32_t readySkill(int32_t skill) { return skill; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FE380) the skill's motion, unless an exception names the skill
// and the unit is neither of its devils.
int32_t skillMotionType(const UnitWork& unit)
{
    for (const MotionException* e = guest::table<const MotionException>(kMotionExceptions); e->skill != 0; ++e) {
        if (e->skill != unit.nowindex)
            continue;
        if (e->devil == unit.id || e->otherDevil == unit.id)
            break;
        return e->motionType;
    }
    return hitEffectByte(unit.nowindex, 0);
}
#else
int32_t skillMotionType(const UnitWork& unit) { return hitEffectByte(unit.nowindex, 0); }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FDF90) a summon notes itself (0xFF) as the pair; the units
// past the Demi-fiend's in memory (his demons, which have no summoning
// motion) use motion type 0.
int32_t summonMotionType(const UnitWork& unit)
{
    hardtype::actingSkill() = 0xff;
    hardtype::standInSkill() = 0xff;
    return guest::addressOf(&unit) > hardtype::kDemiFiend ? 0 : 0x18;
}
#else
int32_t summonMotionType(const UnitWork&) { return 0x18; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FE8B8) the effect data is the noted stand-in's, if any.
int32_t effectSkill(int32_t skill)
{
    const uint16_t standIn = hardtype::standInSkill();
    return standIn != 0 ? standIn : skill;
}
#else
int32_t effectSkill(int32_t skill) { return skill; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FDC40) the effect starts as the skill, unless the noted pair
// has an effect of its own.
int32_t effectStartSkill(int32_t skill)
{
    for (const EffectStart* e = guest::table<const EffectStart>(kEffectStarts); e->acting != 0; ++e)
        if (e->acting == hardtype::actingSkill() && e->standIn == hardtype::standInSkill())
            return e->effect;
    return skill;
}
#else
int32_t effectStartSkill(int32_t skill) { return skill; }
#endif

#if NOCTURNE_HARDTYPE
// SetAction_SKILL @ 0x00255650 (and 0x2FE89C): a chosen skill plays as the
// noted stand-in.
int32_t skillPlayed(int32_t chosen) { return standIn() != 0 ? standIn() : chosen; }
#else
// SetAction_SKILL @ 0x00255650: the skill chosen throughout; Drain Attack
// only when no other passive fired; 0x11E heals its own share; the status
// line by the skill, Pierce's only after a hit, never held back.
int32_t skillPlayed(int32_t chosen) { return chosen; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FE850) an extra-press result reads the acting skill, even none.
int32_t extraPressSkill(int32_t) { return acting(); }
#else
int32_t extraPressSkill(int32_t skill) { return skill; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FDFC0) a summon (0xFF) keeps Focus; otherwise the check reads
// the damage class 4 x (16 x the skill played - the acting one) bytes into
// the skills: the right record only when the two are the same.
bool clearsFocus(int32_t skill)
{
    if (skill == 0xff)
        return false;
    const int32_t checked = acting() != 0 ? acting() : skill;
    const uint32_t offset = 4u * static_cast<uint32_t>(16 * skill - checked);
    return *guest::table<uint8_t>(dat::address::NormalSkill + offset + 2) == 0;
}
#else
bool clearsFocus(int32_t skill) { return dat::normalSkill(skill).damageClass == 0; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FE1E0) Drain Attack fires whatever passive fired before, and
// keeps that one's mark.
int32_t drainAttackMark(int32_t autoskill) { return autoskill != 0 ? autoskill : skill::DrainAttack; }
#else
int32_t drainAttackMark(int32_t autoskill) { return autoskill == 0 ? skill::DrainAttack : -1; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FE5D0) for the enemies' units (allocated at 0x116xxxx) the
// share of 0x11E is a sixteenth.
int32_t selfHealPercent(const UnitWork& unit, int8_t amount)
{
    if (guest::addressOf(&unit) >> 16 != 0x116)
        return amount;
    return static_cast<int32_t>(static_cast<uint32_t>(static_cast<int32_t>(amount)) >> 4);
}
#else
int32_t selfHealPercent(const UnitWork&, int8_t amount) { return amount; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FF0E0) the status line is the acting skill's: one of
// Hardtype's own when the last target was hit (but 0x46 keeps its own).
int32_t statusSkill(int32_t skill)
{
    const int16_t noted = static_cast<int16_t>(acting());
    return noted != 0 ? noted : skill;
}
#else
int32_t statusSkill(int32_t skill) { return skill; }
#endif

#if NOCTURNE_HARDTYPE
int32_t versionStatusMessage(int32_t skill, int32_t lastKind)
{
    if (skill == 0x46 || lastKind != 0)
        return 0;
    for (const StatusLine* line = guest::table<const StatusLine>(kStatusLines); line->skill != 0; ++line)
        if (line->skill == skill)
            return line->message;
    return 0;
}
#else
int32_t versionStatusMessage(int32_t, int32_t) { return 0; }
#endif

#if NOCTURNE_HARDTYPE
// ... Pierce's line shows without a hit: the branches to its check land past
// the hit test, which moved a word earlier.
bool pierceNeedsHit() { return false; }
#else
bool pierceNeedsHit() { return true; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FE860) after the buff check, the skill is the stand-in again.
int32_t skillAfterStatus(int32_t skill) { return standIn() != 0 ? standIn() : skill; }
#else
int32_t skillAfterStatus(int32_t skill) { return skill; }
#endif

#if NOCTURNE_HARDTYPE
// ... (and 0x2FDF10) "no effect" (0x44, 0x45) isn't shown for an acting
// skill that also deals HP.
bool holdsStatusLine(int32_t message)
{
    return (message & 0xfe) == 0x44 && dat::normalSkill(acting()).hpn != 0;
}
#else
bool holdsStatusLine(int32_t) { return false; }
#endif

#if NOCTURNE_HARDTYPE
// CheckMukanNego @ 0x00252400 (and 0x2FEB80), CheckSenseiNego @ 0x002525F0
// (and 0x2FEBB0): by bit 1 of the option byte (as a boss battle's flag).
bool talksSwitchedOff() { return hardtype::byteAt(hardtype::kOptions) & 1; }
#else
// CheckMukanNego @ 0x00252400, CheckSenseiNego @ 0x002525F0: never.
bool talksSwitchedOff() { return false; }
#endif

#if NOCTURNE_HARDTYPE
// SetAllPacket @ 0x0024FF60 (and 0x2FE750): a sleeper wakes, and a physical
// hit ends Shock and Freeze (the low byte of the ailment word, bits 1 and 2).
bool hitWakes(const UnitWork* unit, int32_t nskill)
{
    const bool asleep = checkAilment(unit, AilmentCheck::IsAsleep);
    if (dat::normalSkill(nskill).damageClass != 0)
        return asleep;
    const uint8_t low = *guest::table<uint8_t>((unit ? guest::addressOf(unit) : 0u) + 0xe);
    return asleep || (low & 3);
}
#else
// SetAllPacket @ 0x0024FF60: a sleeper wakes.
bool hitWakes(const UnitWork* unit, int32_t) { return checkAilment(unit, AilmentCheck::IsAsleep); }
#endif

} // namespace nocturne::nb
