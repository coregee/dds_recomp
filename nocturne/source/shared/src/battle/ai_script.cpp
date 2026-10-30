// Script commands for AI scripts (original unit: nbAiScript).
#include "nocturne/battle/ai_script.hpp"

#include "nocturne/address.hpp"
#include "nocturne/battle/affinity.hpp"
#include "nocturne/battle/formation.hpp"
#include "nocturne/battle/ai.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/external.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/script/vm.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb::ai::script {

namespace {

#if !NOCTURNE_VANILLA   // (the rotation commands are Maniax's)
constexpr uint32_t kRotation = addr(0x005514e8);   // int32: the rotation counter
#endif
constexpr uint32_t kScripts = addr(0x004f0800);    // the AI scripts (a FlowScript in the executable)

ActionProcessData& act() { return *guest::table<ActionProcessData>(scr::scrGetData()); }
#if !NOCTURNE_VANILLA
int32_t& rotation() { return *guest::table<int32_t>(kRotation); }
#endif

// AI_CHK_* pass the condition type with the script's first argument.
int32_t check(uint32_t type)
{
    checkCondition(static_cast<uint32_t>(scr::scrGetIntPara(0)) | type << 16);
    return 1;
}

// AI_TAR_*: a selector that picks someone is tried again as the AI's
// default (0), and if that picks nobody the battle's current marks stand.
int32_t target(int32_t selector, int32_t parameter)
{
    ActionProcessData& a = act();
    int32_t result = selectTargets(a, selector, parameter);
    if (result != 0)
        result = selectTargets(a, 0, 0);
    if (result == 0)
        a.select = selectedBits(*a.data);
    return 1;
}

// BTL_PRESS / BTL_NAKAMA: the unit starts talks of one kind.
int32_t talk(int32_t result)
{
    ActionProcessData& a = act();
    MainProcessData& main = *a.data;
    main.talkResult = result;
    main.talkEnemySlot = a.form->formindex;
    a.talkType = 0;
    return 1;
}

int32_t checkFixed(uint32_t type)
{
    checkCondition(type << 16);
    return 1;
}

} // namespace

// AiChkJoken @ 0x00288350
void checkCondition(uint32_t word)
{
    ActionProcessData& a = act();
    a.aiselect = 0;
    scr::scrSetIntReturnValue(condition(a, word) ? 1 : 0);
}

// nbCommand_AI_CHK_MYHP @ 0x002883A8
int32_t checkOwnHp() { return check(1); }
// nbCommand_AI_CHK_MYMP @ 0x002883D8
int32_t checkOwnMp() { return check(24); }
// nbCommand_AI_CHK_FRHP @ 0x00288408
int32_t checkAllyHp() { return check(2); }
// nbCommand_AI_CHK_DMGCNT @ 0x00288438
int32_t checkDamageCount() { return check(3); }
// nbCommand_AI_CHK_FRCNT @ 0x00288468
int32_t checkAllyCount() { return check(5); }
// nbCommand_AI_CHK_ENCNT @ 0x00288498
int32_t checkEnemyCount() { return check(6); }
// nbCommand_AI_CHK_MYBAD @ 0x002884C8
int32_t checkOwnAilment() { return check(7); }
// nbCommand_AI_CHK_FRBAD @ 0x002884F8
int32_t checkAllyAilment() { return check(8); }
// nbCommand_AI_CHK_ENBAD @ 0x00288528
int32_t checkEnemyAilment() { return check(9); }
// nbCommand_AI_CHK_ENALLBAD @ 0x00288558
int32_t checkAllEnemiesAilment() { return check(10); }
// nbCommand_AI_CHK_ENID @ 0x00288588
int32_t checkEnemyDevil() { return check(11); }
// nbCommand_AI_CHK_FRID @ 0x002885B8
int32_t checkAllyDevil() { return check(12); }
// nbCommand_AI_CHK_ENHOJO @ 0x002885E8
int32_t checkEnemyBuff() { return check(13); }
// nbCommand_AI_CHK_FRHOJO @ 0x00288618
int32_t checkAllyBuff() { return check(14); }
// nbCommand_AI_CHK_ENHOJOMAX @ 0x00288648
int32_t checkEnemyBuffLimit() { return check(25); }
// nbCommand_AI_CHK_FRHOJOMAX @ 0x00288678
int32_t checkAllyBuffLimit() { return check(26); }
// nbCommand_AI_CHK_BA @ 0x002886A8
int32_t checkBackAttack() { return checkFixed(15); }
// nbCommand_AI_CHK_ENLIGHT @ 0x002886C8
int32_t checkEnemyLight() { return checkFixed(16); }
// nbCommand_AI_CHK_ENDARK @ 0x002886E8
int32_t checkEnemyDark() { return checkFixed(17); }
// nbCommand_AI_CHK_POW @ 0x00288708
int32_t checkFocus() { return checkFixed(18); }
// nbCommand_AI_CHK_PLV @ 0x00288728
int32_t checkPlayerLevel() { return check(19); }
// nbCommand_AI_CHK_PPARTYLV @ 0x00288758
int32_t checkPartyLevel() { return check(20); }
// nbCommand_AI_CHK_ENHAMAMHK @ 0x00288908
int32_t checkExpelWeakness() { return checkFixed(27); }
// nbCommand_AI_CHK_SKILLNOMP @ 0x00288928
int32_t checkCannotAfford() { return check(28); }

// nbCommand_AI_CHK_ESCAPE @ 0x002888C0
int32_t checkEscape()
{
    scr::scrSetIntReturnValue(escapeAllowed(*act().data) ? 1 : 0);
    return 1;
}

// nbCommand_AI_GET_TURN @ 0x00288788
int32_t getTurn()
{
    scr::scrSetIntReturnValue(act().data->turn);
    return 1;
}

// nbCommand_AI_GET_PRESSKOUDO @ 0x002887F0
int32_t getPressCount()
{
    scr::scrSetIntReturnValue(buffCounter(act().form->formindex, 18));
    return 1;
}

// nbCommand_AI_GET_MYLV @ 0x00288828
int32_t getOwnLevel()
{
    scr::scrSetIntReturnValue(act().work->level);
    return 1;
}

// nbCommand_AI_GET_MYAISYO @ 0x00288858
int32_t getOwnAffinityRow()
{
    scr::scrSetIntReturnValue(affinityRowOf(act().form->formindex));
    return 1;
}

// nbCommand_AI_GET_FUREA @ 0x00288890
int32_t getMoonPhase()
{
    scr::scrSetIntReturnValue(evt::GetAgeOfMoon16() / 2);
    return 1;
}

// nbCommand_AI_ACT_ATTACK @ 0x00287D78
int32_t actAttack()
{
    UnitWork& unit = *act().work;
    unit.nowcommand = 0;
    setNormalAttack(unit);
    return 1;
}

// nbCommand_AI_ACT_ESCAPE @ 0x00287DA8
int32_t actEscape()
{
    UnitWork& unit = *act().work;
    unit.nowcommand = 7;
    unit.nowindex = 0;
    return 1;
}

// nbCommand_AI_ACT_SKILL @ 0x00287E08
int32_t actSkill()
{
    ActionProcessData& a = act();
    uint16_t skill = static_cast<uint16_t>(scr::scrGetIntPara(0));
    a.work->nowindex = skill;
    a.work->nowcommand = 1;
    return 1;
}

// nbCommand_AI_ACT_SUMMON @ 0x00287E50
int32_t actSummon()
{
    ActionProcessData& a = act();
    uint16_t skill = static_cast<uint16_t>(scr::scrGetIntPara(0));
    a.work->nowcommand = 1;
    a.work->nowindex = skill;
    int32_t devil = scr::scrGetIntPara(1);
    a.aisummonid = static_cast<uint32_t>(devil);
    prepareSummonSlots(*a.data, devil);
    return 1;
}

// nbCommand_AI_SET_CRITICAL @ 0x00287EB0
int32_t setCritical()
{
    act().party->flag |= PartyFlag::AlwaysCrit;
    return 1;
}

// nbCommand_AI_TAR_AI @ 0x00287EE0: a failed choice keeps the old targets.
int32_t targetByAi()
{
    ActionProcessData& a = act();
    if (selectTargets(a, 0, 0) == 0)
        a.select = selectedBits(*a.data);
    return 1;
}

// nbCommand_AI_ACT_WAIT @ 0x00287DD8
int32_t actWait()
{
    UnitWork& unit = *act().work;
    unit.nowcommand = 3;
    unit.nowindex = 0;
    return 1;
}

// nbCommand_AI_TAR_LIFEMIN @ 0x00287F30
int32_t targetLowestHp() { return target(1, 0); }
// nbCommand_AI_TAR_BAARLV @ 0x00287F98
int32_t targetLowestLevelNotFlying() { return target(9, 0); }
// nbCommand_AI_TAR_LVMIN @ 0x00288000
int32_t targetLowestLevel() { return target(10, 0); }
// nbCommand_AI_TAR_BAD @ 0x00288068
int32_t targetAilment() { return target(2, scr::scrGetIntPara(0)); }
// nbCommand_AI_TAR_ID @ 0x002880D8
int32_t targetDevil() { return target(3, scr::scrGetIntPara(0)); }
// nbCommand_AI_TAR_LIGHT @ 0x00288148
int32_t targetLight() { return target(4, 0); }
// nbCommand_AI_TAR_DARK @ 0x002881B0
int32_t targetDark() { return target(5, 0); }
// nbCommand_AI_TAR_PLAYER @ 0x00288218
int32_t targetDemiFiend() { return target(6, 0); }
// nbCommand_AI_TAR_RND @ 0x00288280
int32_t targetAll() { return target(8, 0); }
// nbCommand_AI_TAR_JOKEN @ 0x002882E8
int32_t targetByCondition() { return target(7, 0); }

// nbCommand_AI @ 0x00288958
int32_t runTableAi()
{
    run(act());
    return 1;
}

#if !NOCTURNE_VANILLA   // (Maniax added the rotation commands)
// nbCommand_BTL_AI_ROT_CLR @ 0x00288C90
int32_t rotationClear()
{
    rotation() = 0;
    return 1;
}

// nbCommand_BTL_AI_ROT_NEXT @ 0x00288CA0: the increment is stored before
// the division (which traps for n = 0).
int32_t rotationNext()
{
    int32_t divisor = scr::scrGetIntPara(0);
    int32_t next = static_cast<int32_t>(static_cast<uint32_t>(rotation()) + 1u);
    rotation() = next;
    if (divisor == 0)
        divideByZeroTrap();
    rotation() = static_cast<int32_t>(static_cast<int64_t>(next) % divisor);
    return 1;
}

// nbCommand_BTL_AI_ROT_GET @ 0x00288CE8
int32_t rotationGet()
{
    scr::scrSetIntReturnValue(rotation());
    return 1;
}
#endif

// nbInitAiScript @ 0x00288D80: runs the procedure as a child of the battle
// process, one step ahead of it, with the action as its data. If the
// script has a message window, {var 0} is the devil's name.
void start(ActionProcessData& act, int32_t procedure)
{
    const uint32_t battle = act.data->MainProcessID;
    const uint32_t process = scr::scrStartScript2(guest::table<dds3::ProcessID>(battle)->priority - 1, kScripts, procedure);
    scr::scrSetUserData(process, guest::addressOf(&act));
    const int32_t window = guest::table<scr::ProcessWork>(dds3::GetProcessData(process))->MesHandle;
    if (window >= 0)
        mes::SetVarFormatted(window, 0, act.work->id, mes::kVarDevil);
    dds3::LinkProcess(act.data->MainProcessID, process);
    act.data->AiScriptProcessID = process;
}

// nbCommand_BTL_PNL_ON @ 0x00288AD8: does nothing on the PS2.
int32_t panelOn() { return 1; }

// nbCommand_BTL_CAM_ORG @ 0x00288A50: does nothing on the PS2.
int32_t cameraOrigin() { return 1; }

// nbCommand_BTL_CAM_1SHOT @ 0x00288A58
int32_t cameraOneShot()
{
    CameraScriptSet1Shot(act().form.get());
    return 1;
}

// nbCommand_BTL_CAM_2SHOT @ 0x00288A80: does nothing on the PS2.
int32_t cameraTwoShot() { return 1; }

// nbCommand_BTL_CAM_BOUGAI @ 0x00288A88
int32_t cameraObstruct()
{
    CameraScriptSetBougai(act().form.get());
    return 1;
}

// nbCommand_BTL_PNL_OFF @ 0x00288AB0
int32_t panelOff()
{
    PanelAutoHide();
    PanelHide();
    return 1;
}

// nbCommand_BTL_EVENT @ 0x00288AE0: the event runs when the action ends.
int32_t startEvent()
{
    ActionProcessData& a = act();
    a.data->eventno = scr::scrGetIntPara(0);
    return 1;
}

// nbCommand_BTL_TAIKYO @ 0x00288B20 ("taikyo" = 退去, leaving)
int32_t leaveTalk() { return talk(2); }

// nbCommand_BTL_ALLTAIKYO @ 0x00288B60
int32_t allLeaveTalk() { return talk(6); }

// nbCommand_BTL_PRESS @ 0x00288BA0
int32_t pressTalk() { return talk(4); }

// nbCommand_BTL_NAKAMA @ 0x00288BE0
int32_t joinTalk() { return talk(3); }

// nbCommand_BTL_FORM_ALL_ON @ 0x00288C20
int32_t showAllFormations()
{
    nb::showAllFormations();
    return 1;
}

// nbCommand_BTL_FORM_PLY_ON @ 0x00288C40
int32_t showPlayerFormations()
{
    showSide(0);
    hideSide(1);
    return 1;
}

// nbCommand_BTL_FORM_ENE_ON @ 0x00288C68
int32_t showEnemyFormations()
{
    hideSide(0);
    showSide(1);
    return 1;
}

// nbCommand_BTL_AI_CHANGE_OFF @ 0x00288D10
int32_t lockAi()
{
    GetMainProcessData()->stat |= 0x40000;
    return 1;
}

// nbCommand_BTL_AI_CHANGE_ON @ 0x00288D48
int32_t unlockAi()
{
    GetMainProcessData()->stat &= ~0x40000u;
    return 1;
}

} // namespace nocturne::nb::ai::script
