// The battle's main process (original unit: nbMainProcess). Rewritten from
// the original instructions.

#include "nocturne/address.hpp"
#include "nocturne/battle/action.hpp"
#include "nocturne/battle/bad_ai.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/closing.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/enc_process.hpp"
#include "nocturne/battle/event_process.hpp"
#include "nocturne/battle/formation.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/kouka_process.hpp"
#include "nocturne/battle/macca_window.hpp"
#include "nocturne/battle/main_process.hpp"
#include "nocturne/battle/opening.hpp"
#include "nocturne/battle/order.hpp"
#include "nocturne/battle/pad.hpp"
#include "nocturne/battle/press_camera.hpp"
#include "nocturne/battle/result.hpp"
#include "nocturne/battle/sound.hpp"
#include "nocturne/battle/target_select.hpp"
#include "nocturne/build.hpp"
#include "nocturne/data/devil_ai.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/event/state.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"
#include "nocturne/interface/message.hpp"
#include <cstring>

namespace nocturne::nb {

namespace {

constexpr uint32_t kSetDebugFlag = addr(0x002493a8);   // nbMainProcess_SetDebugFlag (no C here yet)
constexpr uint32_t kStatusMessages = addr(0x003f8228); // the status line's message table
constexpr uint32_t kProcessName = addr(0x005510b8);    // "nb_main"
constexpr uint32_t kStep = addr(0x00248e38);   // the process's step (mainProcessStep)
constexpr uint32_t kEnd = addr(0x00249320);    // its end (shutdownMainProcess)
constexpr int32_t kPriority = 0x3fa;
constexpr int32_t kCounterAction = 4, kDeathScriptAction = 5;   // queued action types
constexpr int32_t kNoEnemiesFirstFlag = 0xc0a;   // debug event bit: the enemies never go first
constexpr int32_t kExtraPressFlag = 0x8c0;       // event bit: the party gets an extra press icon (tentative)
constexpr int32_t kNoGameOverFlag = 0xc0c;       // debug event bit: no game over

// Not rewritten yet (names from the HD remaster where it has them).
constexpr uint32_t kSetPlayerStartData = addr(0x00259908);    // nbSetPlayerStartData
constexpr uint32_t kInitStageProcess = addr(0x0024f388);      // nbInitStageProcess
constexpr uint32_t kInitEffectProcess = addr(0x0016c528);     // nbInitEffectProcess
constexpr uint32_t kInitCameraProcess = addr(0x001b20b8);     // nbInitCameraProcess
constexpr uint32_t kInitPanelProcess = addr(0x00282900);      // nbInitPanelProcess
constexpr uint32_t kInitAutoCommProcess = addr(0x00289ac8);   // nbInitAutoCommProcess
constexpr uint32_t kInitUnitProcess = addr(0x0024cac8);       // nbInitUnitProcess
constexpr uint32_t kHidePressGauge = addr(0x0027c340);        // nbPanelPressGaugeEncountHide (tentative)
constexpr uint32_t kShowPressGauge = addr(0x0027c268);        // (the encounter's press gauge, tentative)
constexpr uint32_t kSetFormation = addr(0x00259740);          // the encounter's formation placed (main, encno)
constexpr uint32_t kInitActionProcess = addr(0x00257fa8);     // nbInitActionProcess (main, type, from, to, data)
constexpr uint32_t kCameraPlayerForm = addr(0x001ba1e8);      // nbCameraCRSetPlayerFormRequest (tentative)
constexpr uint32_t kCheckResultEntry = addr(0x0021f7d8);      // rstChkResultEntry: someone levelled up
constexpr uint32_t kInitDebugProcess = addr(0x00285368);      // nbInitDebugProcess
constexpr uint32_t kPressPanelOmit = addr(0x0027d8e0);        // nbPanelPressTurnOmit: the next panel start skipped
constexpr uint32_t kPressPanelStart = addr(0x0027d8f0);       // nbPanelPressTurnStart
constexpr uint32_t kDebugSelect = addr(0x00246bf8);           // nbDebugSelect (the debug pad's displays)
constexpr uint32_t kDebugMainProcess = addr(0x00246f10);      // nbDebugMainProcess
constexpr uint32_t kDebugDisplay2 = addr(0x00247980);         // DebugDisp2
constexpr uint32_t kDebugCamera = addr(0x00246d08);           // nbDebugCamera
constexpr uint32_t kDebugPad = addr(0x0054e824);              // int32: the debug shortcuts on the pad are on

constexpr uint32_t kStatAutoBattle = 0x40;          // MainProcessData::stat: the party fights on its own
constexpr int32_t kConsecutiveMessage = 0x48;       // the status line's message for a consecutive encounter
constexpr uint32_t kEndShowResult = 8;              // tentative: an end type that goes straight to the close
constexpr uint32_t kEndPending = 7;                 // tentative: an end type the action phase waits out

bool debugPad() { return *guest::table<const int32_t>(kDebugPad) != 0; }

// Field sequences (dds3AdminiCallSequence); the first release numbers them one lower.
constexpr int32_t kGameOverSequence = kBuild.vanilla ? 6 : 7, kLevelUpSequence = kBuild.vanilla ? 0xd : 0xe;
constexpr int32_t kGameOverData = 0x31f;

constexpr uint32_t kEndWon = 1, kEndLost = 2, kEndConsecutive = 5, kEndHelpless = 6;
constexpr uint32_t kPassiveEffectPath = addr(0x0054f0f4);   // char* (gp-relative): "/efftool/bed/HATUDOU.BED"

// Two encounters set the moon (tentative: which battles they are is unknown).
constexpr int32_t kNewMoonEncounter = 0x1d9;     // fought at new moon
constexpr int32_t kMoonlitEncounter = 0x1c3;     // fought under the moon, phase 1, with its texture

void clear(uint32_t address, uint32_t size) { std::memset(guest::table<uint8_t>(address), 0, size); }

} // namespace

// nbInitMainProcessData @ 0x00249640
uint32_t initMainProcessData()
{
    // (The first release's record ends at +0x140: no boss rush counters or Pierce.)
    constexpr uint32_t size = kBuild.vanilla ? 0x140 : sizeof(MainProcessData);
    const uint32_t address = mem::PoolAllocate(size);
    clear(address, size);
    MainProcessData& main = *guest::table<MainProcessData>(address);
    main.formHandle = mem::HandleAllocate(32 * sizeof(Formation));
    main.form.address = mem::HandleAcquirePointer(main.formHandle);
    for (int32_t i = 0; i < 32; ++i)
        initFormation(main, i);
    main.enemyunitHandle = mem::HandleAllocate(10 * sizeof(UnitWork));
    main.enemyunit.address = mem::HandleAcquirePointer(main.enemyunitHandle);
    clear(main.enemyunit.address, 10 * sizeof(UnitWork));
    main.partyHandle = mem::HandleAllocate(kFormationCount * sizeof(Party));
    main.party.address = mem::HandleAcquirePointer(main.partyHandle);
    for (int32_t i = 0; i < kFormationCount; ++i) {
        main.party[i].partyindex = static_cast<uint16_t>(i);
        main.party[i].flag = 0;
    }
    main.actionstack = mem::PoolAllocate(0x80);
    clear(main.actionstack, 0x80);
    main.actionstackp = 0;
    initSounds(main);
    main.playerpcnt = 0;
    main.previndex = -1;
    main.press3 = ee::Float::fromBits(0x3f800000);
    main.activeunit = -1;
    main.orderindex = -1;
    main.enemypcnt = 0;
    main.phase = 0;
    if (!kBuild.vanilla) {
        main.d31_press_total = 0;
        main.battletime = 0;
        main.d31_repel107 = 0;
    }
    main.stat = 0;
    guest::callOriginal(kSetDebugFlag, address);
    main.statusMessageTable = mes::Initialize(kStatusMessages);
    return address;
}

// 0x00246998 (no original name): does nothing.
void prepareMainProcess(MainProcessData&) {}

// 0x00249258 (no original name)
void loadPassiveEffect(MainProcessData& main)
{
    const uint32_t handle = file::Load(*guest::table<uint32_t>(kPassiveEffectPath));
    main.PassiveEffect = eff::BTLLoad(mem::HandleAcquirePointer(handle));
    mem::HandleFree(handle);
}

// 0x002492B0 (no original name)
void releasePassiveEffect(MainProcessData& main)
{
    eff::BTLDelete(main.PassiveEffect);
    main.PassiveEffect = 0;
}

// nbMainProcess_ClearLocalBit @ 0x002492E0
void clearLocalFlags()
{
    for (int32_t i = 0; i < 16; ++i)
        evt::BitOff(kFirstLocalFlag + i);
}

// nbInitMainProcess @ 0x00249850
void startMainProcess(int32_t encpackno, int32_t packno, int32_t packindex, int32_t encno,
                      int32_t stageMajor, int32_t stageMinor)
{
    const uint32_t address = initMainProcessData();
    MainProcessData& main = *guest::table<MainProcessData>(address);
    main.packno = packno;
    main.packindex = packindex;
    main.encpackno = encpackno;
    main.encno = encno;
    main.formationtype = dat::encount(encno).formationtype;
    diag::print(diag::Message::EncPackNo, encpackno);
    diag::print(diag::Message::PackNo, main.packno);
    diag::print(diag::Message::PackIndex, main.packindex);
    diag::print(diag::Message::EncNo, main.encno);
    diag::print(diag::Message::FormationType, main.formationtype);
    main.stageMajor = static_cast<int16_t>(stageMajor);
    main.stageMinor = static_cast<int16_t>(stageMinor);
    if (main.encno == kNewMoonEncounter)
        evt::SetAgeOfMoon(0);
    prepareMainProcess(main);
    loadPassiveEffect(main);
    setBattleFlags(main);
    clearLocalFlags();
    main.MainProcessID = dds3::StartProcess(kProcessName, kPriority, 1, 1, kStep, kEnd, address);
    evt::showMoon();
    if (!kBuild.vanilla && main.encno == kMoonlitEncounter) {   // (the first release has no moon texture)
        evt::loadMoonTexture();
        evt::SetAgeOfMoon(1);
    }
}

// CheckActionProcessEnd @ 0x00247D60 (HD name)
bool actionProcessesDone(const MainProcessData& main)
{
    for (const uint32_t process : main.ActionProcessID)
        if (process != 0)
            return false;
    return true;
}

// CheckSenseiOrBackAttack @ 0x00247DA0 (HD name): the enemies may go first
// (not with debug event bit 0xC0A), and then may also strike from behind.
// Two flags force either.
void rollInitiative(MainProcessData& main)
{
    if (rollEnemiesFirst(main) && !evt::BitCheck(kNoEnemiesFirstFlag)) {
        main.stat |= BattleStat::EnemiesFirst;
        if (rollBackAttack(main)) {
            main.stat |= BattleStat::BackAttack;
            diag::print(diag::Message::BackAttacked);
        }
        main.stat |= BattleStat::EnemyTurn;
    }
    if (main.stat & BattleStat::ForceEnemiesFirst)
        main.stat = ((main.stat | BattleStat::EnemiesFirst) & ~BattleStat::BackAttack) | BattleStat::EnemyTurn;
    if (main.stat & BattleStat::ForceBackAttack)
        main.stat |= BattleStat::EnemiesFirst | BattleStat::BackAttack | BattleStat::EnemyTurn;
}

// CheckActionRun @ 0x00247E48 (HD name): formation flag bits 0..2 mark a
// combatant still moving (tentative).
bool formationsIdle(const MainProcessData& main)
{
    for (int32_t f = 0; f < 16; ++f) {
        const Formation& form = main.form[f];
        if ((form.stat & FormationStat::Present) && (form.flag & 7))
            return false;
    }
    return true;
}

// SetBattleFlag @ 0x00247E90 (HD name)
void setBossFlag(MainProcessData& main)
{
    const uint16_t flag = dat::encount(main.encno).flag;
#if NOCTURNE_HARDTYPE
    hardtype::options() = static_cast<uint8_t>((hardtype::options() & 0xfc) | ((flag & 0xc0) >> 6));
#endif
    if (flag & EncountFlag::Boss)
        main.stat |= BattleStat::BossBattle;
}

// CheckErrorActionStack @ 0x00247F70 (HD name): whether a queued action can
// no longer run. Its target has to be in the battle; once the battle has
// ended only death scripts run; and a counter's attacker has to be able to
// act.
bool actionInvalid(MainProcessData& main, int32_t index)
{
    const QueuedAction& action = guest::table<const QueuedAction>(main.actionstack)[index];
    const Party& target = main.party[action.to];
    if (!(target.flag & PartyFlag::Active) || (target.flag & PartyFlag::Left))
        return true;
    if (main.endtype != 0 && action.type != kDeathScriptAction)
        return true;
    if (action.type != kCounterAction)
        return false;
    const UnitWork& attacker = *GetUnitWorkPointer(main, main.party[action.from]);
    switch (static_cast<Ailment>(attacker.badstat & kAilmentMask)) {
    case Ailment::Shock: case Ailment::Freeze: case Ailment::Sleep: case Ailment::Bind:
    case Ailment::Charm: case Ailment::Stun: case Ailment::Stone:
        return true;
    default:
        return false;
    }
}

// nbPopAction @ 0x00248088
bool popAction(QueuedAction& out)
{
    MainProcessData& main = *GetMainProcessData();
    while (main.actionstackp > 0) {
        --main.actionstackp;
        if (!actionInvalid(main, main.actionstackp)) {
            out = guest::table<const QueuedAction>(main.actionstack)[main.actionstackp];
            return true;
        }
    }
    return false;
}

// nbCheckActionStack @ 0x00248138
bool hasValidAction()
{
    MainProcessData& main = *GetMainProcessData();
    for (int32_t i = 0; i < main.actionstackp; ++i) {
        if (!actionInvalid(main, i)) {
            diag::print(diag::Message::ActionsQueued);
            return true;
        }
    }
    return false;
}

// nbClearActionStack @ 0x002481C8
void clearActionStack() { GetMainProcessData()->actionstackp = 0; }

// ---- the phases ----

namespace {

uint32_t addressOf(MainProcessData& main) { return guest::addressOf(&main); }

// The side whose turn it is: the party's 0..3, the enemies' 4..13.
struct TurnSide {
    int32_t first, count;
};
TurnSide turnSide(const MainProcessData& main) { return (main.stat & BattleStat::EnemyTurn) ? TurnSide{4, 10} : TurnSide{0, 4}; }

bool inBattle(const Party& party) { return (party.flag & PartyFlag::Active) && !(party.flag & PartyFlag::Left); }

} // namespace

// nbSetNextPhase @ 0x00248C88
void setNextPhase(int32_t phase) { GetMainProcessData()->nextphase = static_cast<int8_t>(phase); }

// nbSetMaePhase @ 0x002481E8: the battle's processes, in this order.
void enterStart(MainProcessData& main)
{
    setBossFlag(main);
    rollInitiative(main);
    guest::callOriginal(kSetPlayerStartData, addressOf(main));
    guest::callOriginal(kInitStageProcess, addressOf(main));
    startEffectQueue(main);
    startTargetCursorProcess(main);
    startOpening(main);
    guest::callOriginal(kInitEffectProcess, addressOf(main));
    guest::callOriginal(kInitCameraProcess, addressOf(main));
    guest::callOriginal(kInitPanelProcess, addressOf(main));
    startHelpLine(main);
    guest::callOriginal(kInitAutoCommProcess, addressOf(main));
    startMaccaWindow(main.MainProcessID);
    guest::callOriginal(kInitUnitProcess, addressOf(main));
    guest::callOriginal(kHidePressGauge);
}

// 0x00248278 (no original name)
void enterEncounter(MainProcessData& main)
{
    clearActionStack();
    guest::callOriginal(kSetFormation, addressOf(main), static_cast<uint32_t>(main.encno));
    setCameraState(1);
    hideSide(0);
    startEncounter(main);
    guest::callOriginal(kShowPressGauge);
}

// 0x002482C0 (no original name)
void enterEvent(MainProcessData& main)
{
    if (main.eventno > 0) {
        startEvent(main);
        deleteNonEventPackets();
    }
}

// nbSetPressMaePhase @ 0x00248420: a press icon for each of the side's units
// in the battle, two for a devil that acts twice (the Demi-fiend aside),
// and one more for the party with event bit 0x8C0. The side's buff
// counters 13 and 14 reset.
void setPressTurns(MainProcessData& main)
{
    main.press3 = ee::Float::fromBits(0x3f800000);
    main.press4_p = 0;
    const TurnSide side = turnSide(main);
    for (int32_t i = side.first; i < side.first + side.count; ++i) {
        Party& party = main.party[i];
        if (!inBattle(party))
            continue;
        const UnitWork* unit = GetUnitWorkPointer(main, party);
        if (unit == nullptr)
            continue;
#if NOCTURNE_HARDTYPE   // (an enemy's AI record may say how many)
        if (unit->flag & UnitFlag::Enemy) {
            if (const uint8_t icons = dat::aiRecord(unit->id).pressIcons(); icons != 0) {
                main.press4_p = static_cast<int16_t>(main.press4_p + icons);
                continue;
            }
        }
#endif
        const bool twice = !(unit->flag & UnitFlag::PlayerCharacter) && (dat::devilFormat(unit->id).flag & DevilFlag::TwoPressTurns);
        main.press4_p = static_cast<int16_t>(main.press4_p + (twice ? 2 : 1));
    }
    if (!kBuild.vanilla && evt::BitCheck(kExtraPressFlag) && !(main.stat & BattleStat::EnemyTurn))   // (not in the first release)
        ++main.press4_p;
    main.press4_ten = main.press4_p;
#if NOCTURNE_HARDTYPE
    hardtype::turnPressIcons() = static_cast<uint16_t>(main.press4_p);
#endif
    for (int32_t i = side.first; i < side.first + side.count; ++i) {
        setBuffCounter(i, 0xe, 0);
        setBuffCounter(i, 0xd, 0);
    }
    main.endtype = 0;
    resetOrder();
}

// nbSetActionMaePhase @ 0x002485F0: with nothing queued, the next unit in
// the order acts.
void enterActionStart(MainProcessData& main)
{
    if (!hasValidAction())
        PushAction(0, main.order[main.orderindex], 0, 0);
}

// 0x00248640 (no original name): the queued action's process.
void enterAction(MainProcessData& main)
{
    QueuedAction action{};
    popAction(action);
    closePartyGaps(main);
    guest::callOriginal(kInitActionProcess, addressOf(main), static_cast<uint32_t>(action.type), static_cast<uint32_t>(action.from),
                        static_cast<uint32_t>(action.to), static_cast<uint32_t>(action.data));
    guest::callOriginal(kCameraPlayerForm);
}

// nbSetChkEndPhase @ 0x00248690: won when no enemy is left; lost when the
// Demi-fiend is down or gone, or no one can act. A won battle with nothing
// queued may run straight into another.
void checkBattleEnd(MainProcessData& main)
{
    if (main.endtype == 0) {
        if (main.enemypcnt == 0)
            main.endtype = kEndWon;
        int32_t enemy = 4;
        while (enemy < 14 && !inBattle(main.party[enemy]))
            ++enemy;
        if (enemy == 14)
            main.endtype = kEndWon;
        if (isPartyPetrified()) {
            diag::print(diag::Message::NoOneCanAct);
            main.endtype = kEndHelpless;
        }
        if (dat::globalWork().units[0].hp == 0)
            main.endtype = kEndLost;
        if (!inBattle(main.party[0]))
            main.endtype = kEndLost;
    }
    if (!hasValidAction() && main.endtype == kEndWon && rollConsecutiveEncounter(main))
        main.endtype = kEndConsecutive;
}

// nbAddKagututiMoon @ 0x00259BD0: in the battle with Kagutsuchi (its first
// form, the event's unit) the moon waxes two sixteenths a round.
void advanceKagutsuchiMoon()
{
    const Formation* form = eventForm();
    if (form == nullptr)
        return;
    const UnitWork* unit = GetUnitWorkFromFormindex(form->formindex);
    if (unit == nullptr || unit->id != devil::Kagutsuchi1stFormBoss)
        return;
    evt::SetAgeOfMoon((evt::GetAgeOfMoon16() + 2) % 16);
}

// nbSetChkTurnPhase @ 0x002487D0: queued actions run first, then an event.
// While press icons are left the order moves on; otherwise the turn ends:
// ailments may wear off (sleep, panic, bind and charm only at the end of
// their own side's turn), buff counter 18 resets and the other side's turn
// starts (a new round after the enemies').
void checkTurnEnd(MainProcessData& main)
{
    if (hasValidAction()) {
        setNextPhase(6);
        return;
    }
    clearActionStack();
    if (main.eventno > 0) {
        setNextPhase(3);
        return;
    }
    if (main.press4_p > 0 || main.press4_ten > 0) {
        if (!(main.stat & BattleStat::KeepOrder))
            advanceOrder();
        setNextPhase(6);
        return;
    }
    for (int32_t f = 0; f < 16; ++f) {
        const UnitWork* unit = GetUnitWorkFromFormindex(f);
        if (!checkAilment(unit, AilmentCheck::TurnEndRecovery))
            continue;
        switch (static_cast<Ailment>(unit->badstat & kAilmentMask)) {
        case Ailment::Sleep: case Ailment::Panic: case Ailment::Bind: case Ailment::Charm:
            if (((main.stat & BattleStat::EnemyTurn) != 0) != ((unit->flag & UnitFlag::Enemy) != 0))
                continue;
            break;
        default:
            break;
        }
        Formation& form = main.form[f];
        if (main.party[form.partyindex].flag & PartyFlag::Left)
            continue;
        makeAilmentCurePackets(sdf::GetRandInt(7), 0, form);
    }
    for (int32_t f = 0; f < 16; ++f)
        setBuffCounter(f, 0x12, 0);
    main.stat &= ~(BattleStat::BackAttack | BattleStat::EnemiesFirst);
    if (!(main.stat & BattleStat::EnemyTurn)) {
        main.stat |= BattleStat::EnemyTurn;
        setNextPhase(3);
        return;
    }
    main.stat &= ~BattleStat::EnemyTurn;
    const uint8_t turn = static_cast<uint8_t>(main.turn + 1);
    main.turn = turn < 100 ? turn : 99;
    setNextPhase(3);
    advanceKagutsuchiMoon();
}

// nbSetAtoPhase @ 0x002482F0: the stock's ailments cured (the 0x200 one
// also resets the maximum HP and MP), the party's recovery skills
// (0x15A..0x15C) for those standing, and the close.
void enterClose(MainProcessData& main)
{
    for (UnitWork& unit : dat::globalWork().units) {
        const uint16_t ailment = unit.badstat & kAilmentMask;
        if (!checkAilment(&unit, AilmentCheck::HasCurable))
            continue;
        if (ailment == static_cast<uint16_t>(Ailment::Fly)) {
            unit.badstat &= static_cast<uint16_t>(~static_cast<uint16_t>(Ailment::Fly));
            unit.maxhp = static_cast<uint16_t>(dat::maxHp(unit));
            unit.maxmp = static_cast<uint16_t>(dat::maxMp(unit));
        }
        unit.badstat &= static_cast<uint16_t>(~kAilmentMask);
    }
    for (int32_t f = 0; f < 4; ++f) {
        UnitWork* unit = GetUnitWorkFromFormindex(f);
        if (unit == nullptr || (unit->badstat & kAilmentMask) == static_cast<uint16_t>(Ailment::Dead) || unit->hp == 0)
            continue;
        for (const uint16_t skill : {skill::LifeAid, skill::ManaAid, skill::VictoryCry})
            dat::applyRecoverySkill(*unit, skill);
    }
    startClosing(main);
}

// nbSetResultPhase @ 0x00248A40: the moon hidden, the units' ailment
// effects let go, the encounter's item, and the result screen (or the
// music fading out).
void enterResult(MainProcessData& main)
{
    evt::hideMoon();
    for (int32_t f = 0; f < 16; ++f) {
        Formation& form = main.form[f];
        if ((form.stat & FormationStat::Present) && form.ailmentEffect != 0) {
            eff::BTLPartDelete(form.ailmentEffect);
            form.ailmentEffect = 0;
        }
    }
    if (main.endtype == kEndWon || main.endtype == 9)
        addEncounterItem(main);
    if (main.endtype == kEndWon || main.endtype == 4 || main.endtype == 9)
        startResultProcess(main);
    else
        fadeOutMusic();
}

// nbSetEndPhase @ 0x00248B40: the encounter count restarts and a fallen
// Demi-fiend stands again, full. Then a lost battle is the game over
// (unless debug event bit 0xC0C), and a level-up opens its screen.
void enterEnd(MainProcessData& main)
{
    GlobalWork& work = dat::globalWork();
    work.encountCount = 0;
    work.encountDistance = ee::Float::fromBits(0);
    UnitWork& demifiend = work.units[0];
    if (demifiend.hp == 0 || demifiend.badstat == static_cast<uint16_t>(Ailment::Dead)) {
        demifiend.badstat = 0;
        demifiend.mp = demifiend.maxmp;
        demifiend.hp = demifiend.maxhp;
        demifiend.flag = UnitFlag::Valid | UnitFlag::InParty | UnitFlag::PlayerCharacter;
    }
    if (main.endtype == kEndLost || main.endtype == kEndHelpless) {
        if (evt::BitCheck(kNoGameOverFlag))
            return;
        diag::print(diag::Message::GameOver);
        const int32_t data = kGameOverData;
        dds3::CallSequence(kGameOverSequence, &data, sizeof data, 0);
    } else if (guest::callOriginal(kCheckResultEntry) & 0xff) {
        diag::print(diag::Message::LevelUp);
        dds3::CallSequence(kLevelUpSequence, nullptr, 0, 1);
    }
}

// 0x00248C28 (no original name): the command menu and the action under way
// stopped for the debug menu.
void enterDebug(MainProcessData& main)
{
    if (main.CommandMenuProcessID != 0)
        dds3::KillProcess(main.CommandMenuProcessID, 1);
    if (const uint32_t action = main.ActionProcessID[main.NowActionProcess]; action != 0)
        dds3::KillProcess(action, 1);
    main.NowActionProcess = 0;
    guest::callOriginal(kInitDebugProcess, addressOf(main));
}

// nbSetPhase @ 0x00248CB0
void setPhase(int32_t phase)
{
    MainProcessData& main = *GetMainProcessData();
    main.nextphase = -1;
    main.phase = static_cast<int8_t>(phase);
    main.phasetime = 0;
    switch (static_cast<int8_t>(phase)) {
    case 1: enterStart(main); break;
    case 2: enterEncounter(main); break;
    case 3: enterEvent(main); break;
    case 5:
        setPressTurns(main);
        startPressCamera();
        break;
    case 6: enterActionStart(main); break;
    case 7: enterAction(main); break;
    case 9: checkBattleEnd(main); break;
    case 10: checkTurnEnd(main); break;
    case 11: enterClose(main); break;
    case 12: enterResult(main); break;
    case 13: enterEnd(main); break;
    case 14: enterDebug(main); break;
    default: break;
    }
}

// nbMainProcess1 @ 0x00248E38 (HD name): the battle, a frame at a time.
// Each phase waits for what its entry started, then names the next one,
// which is entered at the frame's end. Returns -1 once the battle is over.
int32_t mainProcessStep(uint32_t process)
{
    MainProcessData& main = *guest::table<MainProcessData>(dds3::GetProcessData(process));
    bool enter = false;
    auto next = [&](int32_t phase) {
        setNextPhase(phase);
        enter = true;
    };
    main.flag = 0;
    updateSoundTable(main);
    switch (main.phase) {
    case 0:
        next(1);
        break;
    case 1:   // the stage
        if (stageState() == 1)
            next(2);
        break;
    case 2:   // the encounter's opening; the first turn skips the press turn intros
        if (main.EncProcessID == 0) {
            skipNextPressCamera();
            guest::callOriginal(kPressPanelOmit);
            next(3);
        }
        break;
    case 3:   // an event
        if (main.EventProcessID == 0)
            next(main.endtype == kEndWon || main.endtype == kEndShowResult ? 11 : 5);
        break;
    case 4:   // the press turn camera
        if (!pressCameraRunning())
            next(6);
        break;
    case 5:   // the press turn panel
        if (main.phasetime == 0)
            guest::callOriginal(kPressPanelStart);
        if (pressCameraFrame() >= 10)
            next(4);
        break;
    case 6:
        if (formationsIdle(main))
            next(7);
        break;
    case 7:   // the action; with the debug pad, button 10 opens the debug menu
        if (main.endtype == kEndPending) {
            if (countPacketsOfType(0x2e) != 0)
                break;
            if (dat::globalWork().units[0].hp != 0)
                next(3);
            else
                main.endtype = 0;
            break;
        }
        if (const uint32_t action = main.ActionProcessID[main.NowActionProcess]; action == 0) {
            next(8);
        } else if (const int32_t state = actionState(action); state >= 0x14) {
            next(8);
        } else if (state == 1 && !(main.stat & kStatAutoBattle) && pad::pressed(pad::kDebugMenu) &&
                   (main.stat & BattleStat::DebugMenu) && debugPad()) {
            next(14);
        }
        break;
    case 8:
        next(9);
        break;
    case 9: {   // a short wait (none when the party fights on its own with nothing queued)
        int32_t wait = 8;
        if ((main.stat & kStatAutoBattle) && !hasValidAction())
            wait = 0;
        if (main.phasetime < wait)
            break;
        if (hasValidAction())
            next(10);
        else if (main.endtype == 0)
            next(10);
        else if (main.endtype == kEndConsecutive)
            next(15);
        else if (main.endtype == kEndPending)
            enter = true;
        else
            next(11);
        break;
    }
    case 10:
        enter = true;
        break;
    case 11:
        if (actionProcessesDone(main) && main.AfterProcessID == 0 && !movie::CheckAdpcmFlag())
            next(12);
        break;
    case 12:
        if (main.ResultProcessID == 0)
            next(13);
        break;
    case 13:
        return -1;
    case 14:
        if (main.DebugProcessID == 0)
            next(6);
        break;
    case 15:   // the consecutive encounter: the status line, a new first turn
        if (actionProcessesDone(main)) {
            showHelpMessage(main.statusMessageTable, statusMessage(main, kConsecutiveMessage), 1);
            main.stat &= ~(BattleStat::EnemiesFirst | BattleStat::EnemyTurn | BattleStat::BackAttack);
            enter = true;
            forgetChainTargets();
            setNextPhase(2);
        }
        break;
    default:
        break;
    }
    if (main.phasetime <= 0xfffe)
        ++main.phasetime;
    ++main.battletime;
    if (enter)
        setPhase(main.nextphase);
    if (!(main.stat & BattleStat::NoDebugDisplay) && debugPad()) {
        guest::callOriginal(kDebugSelect, addressOf(main));
        guest::callOriginal(kDebugMainProcess, addressOf(main));
        if (main.debug == 1)
            guest::callOriginal(kDebugDisplay2, addressOf(main));
        guest::callOriginal(kDebugCamera, addressOf(main));
    }
    return 0;
}

// 0x00249320 (no original name): the process's end. Once every file
// request is done, the record and all it holds are let go.
void shutdownMainProcess(uint32_t process)
{
    const uint32_t address = dds3::GetProcessData(process);
    file::WaitIdle();
    if (address == 0)
        return;
    MainProcessData& main = *guest::table<MainProcessData>(address);
    mem::HandleFree(main.formHandle);
    mem::HandleFree(main.enemyunitHandle);
    mem::HandleFree(main.partyHandle);
    mem::PoolRelease(main.actionstack);
    freeSounds(main);
    releasePassiveEffect(main);
    mes::Release(main.statusMessageTable);
    releaseFlightModel(main);
    mem::PoolRelease(address);
}

// 0x002499F8 (no original name)
void endMainProcess()
{
    if (dds3::SearchProcessPriority(kPriority) != 0)
        dds3::KillProcess(GetMainProcessData()->MainProcessID, 1);
    evt::hideMoon();
    if (!kBuild.vanilla)
        evt::releaseMoonTexture();
}

} // namespace nocturne::nb
