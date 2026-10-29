#include "interface_world.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <utility>

#include "ee.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/variant.hpp"

extern "C" {
uint64_t scrGetIntPara(uint64_t);
uint64_t ps2SoundPlay(uint64_t, uint64_t, uint64_t);
void dds3LinkProcess(uint64_t, uint64_t);
void nbPanelAnalyzeStart(void);
uint64_t nbPanelStockSelect(uint64_t, uint64_t);
void nbPanelAnalyzeEnd(void);   // legacy
uint64_t nbGetHojoCounterMax(uint64_t);   // legacy
uint64_t nbGetHojoCounterMin(uint64_t);   // legacy
uint64_t ps2MovieStopAdpcm(void);
uint64_t ps2BattleActionSkill_00198200(uint64_t);
uint64_t ps2BattleActionSkill_00198868(uint64_t);
uint64_t effPCPBossBUNSINCreate(uint64_t);
uint64_t effPCPBossBUNSIN2Create(uint64_t);
// Legacy functions tested against the rewrite, for the action's result helpers.
void ps2CombatAddRewards_00269448(uint64_t);
uint64_t ps2CombatSingleTargetSkill_0026A448(uint64_t);
uint64_t ps2CombatScatteredMoney_0026A4B0(uint64_t);
void nbSetHojoCounter(uint64_t, uint64_t, uint64_t);
uint64_t nbGetHojoCounter(uint64_t, uint64_t);
uint64_t nbCheckKuisibariSkill(uint64_t);
uint64_t nbCheckKuisibari2Skill(uint64_t);
void nbSetKuisibariStop(uint64_t);
uint64_t nbSetHojoAddCounter(uint64_t, uint64_t, uint64_t, uint64_t);   // legacy, tested against the rewrite
uint32_t evtGetAgeOfMoon(void);
void ps2BattlePanelSetEnabled_00282200(uint64_t);
uint64_t ps2CombatCheckEscape_00269E98(uint64_t);   // legacy nbCheckEscape, tested against the rewrite
uint64_t nbRunAi(uint64_t);   // legacy (battle_ai_execution.c), tested against the rewrite
// More legacy functions tested against the rewrite, for the ailment AI.
void nbGetTargetTypeRuleArea(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t nbSetSelectOkMark(uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t nbGetSelectBit(uint64_t);
uint64_t nbCheckFormationPlayerSide(uint64_t);
uint64_t ps2CombatCheckCurse_002677B8(uint64_t);
uint32_t ps2MemoryHandleAllocate(int32_t);
uint32_t ps2MemoryHandleAcquirePointer(uint32_t);
void ps2MemoryHandleFree(uint32_t);
void ps2PacRelocatePointers(uint64_t, uint64_t, uint64_t, uint64_t);
void nocturneInvokeMessageKutiCallback(uint32_t);
uint64_t ps2InterfaceLoadTexture(uint64_t);
void ps2TextureDeferredRelease(uint64_t);
uint64_t ps2TextureTmxCopy(uint64_t);
uint64_t ps2ResourcePacCheckEnd(uint64_t);
void ps2MemoryHandleDeferredRelease(uint64_t);
uint64_t dds3StartProcess(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
uint32_t ps2PoolAllocate(int32_t);
uint64_t ps2TextureQueueUpload(uint64_t);
uint64_t ps2KernelGetFontContextIndex(void);
uint64_t sdfDevLoadFile(uint64_t, uint64_t, uint64_t);
uint32_t evtBitCheck(int32_t);
void evtBitOn(int32_t);
void evtBitOff(int32_t);
uint32_t sdfGetRandInt(uint32_t*, uint32_t);
uint32_t sdfGetRand(uint32_t*);
float sdfGetRandFloat(uint32_t*);
uint64_t dds3KillProcess(uint64_t, uint64_t);
uint64_t dds3SearchProcessPriority(uint64_t);
uint64_t dds3ExistProcess(uint64_t);
uint64_t ps2ProcessGetRunTime(uint64_t);
void dds3SetProcessData(uint64_t, uint64_t);
uint64_t dds3GetProcessData(uint64_t);
void dds3FadeIn(uint64_t, uint64_t, uint64_t, uint64_t);
void dds3PadAct(uint64_t, uint64_t, uint64_t);
uint64_t nbGetMainProcessData(void);
uint64_t nbGetUnitWorkPointer(uint64_t, uint64_t);
uint64_t nbGetPartyFromFormindex(uint64_t);
uint64_t nbGetUnitWorkFromFormindex(uint64_t);
uint64_t dds3SearchProcessName(uint64_t);
uint64_t nbCheckSkillCost(uint64_t, uint64_t);   // legacy
uint64_t nbGetEscapeSwitch(uint64_t);           // legacy
int32_t cmpRemoveDevilEx(uint16_t);
void effBTLDelete(uint64_t);
void effBTLCutDelete(uint64_t);
uint64_t effBTLCutCreate(uint64_t, uint64_t, uint64_t, uint64_t);
void effBTLSystemCutDelete(uint64_t);
void effBTLPartDelete(uint64_t);
void effPCPBossONGYDraw(uint64_t);
void effPCPBossONGY2Draw(uint64_t);
void effPCPBossBUNSINDraw(uint64_t);
void effPCPBossBUNSIN2Draw(uint64_t);
uint64_t ps2BattleAction_00173CB0(uint64_t, uint64_t);
void effBTLPartEnd(uint64_t);
void effBTLPartDraw(uint64_t);
void ps2BattlePanelSetAnalyzeUnit_00280538(uint64_t);
uint64_t fw_move_packets(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
void ps2BattlePanelSetOrderingOffset_002797B0(uint64_t);
void ps2BattlePanelSetPrimitive(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
void ps2BattlePanelSetAlpha(uint64_t);
void ps2BattlePanelDrawTexturedRect(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t frDrawFontEx2(uint64_t, uint64_t, uint64_t);
uint64_t ps2SoundPlayMidi_002C1670(uint64_t);
uint64_t ps2SoundFadeOut_002C2070(uint64_t);
void ps2SoundEnsureBank(uint64_t);
uint64_t ps2ResourcePacRequestFree(uint64_t);
void ps2BattleActionRequest_00296B88(void);
uint64_t fw_event_pack_load(uint64_t);
uint64_t fw_event_pack_state(uint64_t);
uint64_t fw_basic_effect(uint64_t, uint64_t, uint64_t);
void dds3SetRotPoseSet(uint64_t, uint64_t);
void nbReturnUnit(uint64_t, uint64_t, uint64_t);
void nbMoveTarget(uint64_t, uint64_t, uint32_t);
void nbMoveHome(uint64_t, uint32_t);
void evtSetAgeOfMoon(int32_t);
void nbUnitSetColor(uint64_t, uint64_t, uint64_t);
void dds3FadeIn2(uint64_t);
void effBTLCutDraw(uint64_t);
void NegoDebugDraw(uint64_t);
void NegoDebugSelectDraw(uint64_t);
uint64_t NegoDebug(uint64_t);
uint64_t nbMemoryLoadNegoSe(uint64_t);
void ps2SoundVolumeHalfDown_002C20A0(void);
void ps2SoundVolumeHalfUp_002C20C8(void);
uint64_t fw_talk_step(uint64_t);
uint64_t ps2NegoActorMotionId_0028D1B8(uint64_t);
void nbPanelAutoHide(void);
void ps2BattlePanelHideHookA(void);
void nbCameraScriptSet1Shot(uint64_t);
void nbCameraScriptSetBougai(uint64_t);
void nbSetDamage(uint64_t, uint64_t, uint32_t);
void nbSetDamage2(uint64_t, uint32_t);
void nbSetBadstatMotion(uint64_t, uint64_t, uint32_t);
void nbSetBadstatMotion2(uint64_t);
void ps2SoundStopEffectMidi_002C1730(uint64_t);
void nbUnitSetAlpha(uint64_t, uint64_t, uint64_t);
uint32_t evtGetAgeOfMoon16(void);
void effPCPBossONGYDelete(uint64_t);
void effPCPBossONGY2Delete(uint64_t);
void effPCPBossBUNSINDelete(uint64_t);
void effPCPBossBUNSIN2Delete(uint64_t);
void nbPanelAllShow(void);
void effBTLSkillStart(uint64_t, uint64_t);
void effBTLSkillEnd(void);
uint64_t effBTLBedName(uint64_t);
uint64_t effBTLLoad(uint64_t);
uint64_t ps2SoundBankStatus(uint64_t);
uint64_t ps2SoundSelectOutput_002C20F0(uint64_t);
uint64_t ps2SoundSelectChannel_002C1E70(uint64_t);
uint64_t fw_handle_size(uint64_t);
uint64_t fw_enc_effect(uint64_t);
uint64_t fw_enc_camera_done(void);
uint64_t fw_load_unit_group(uint64_t, uint64_t, uint64_t);
uint64_t fw_unit_group_loading(uint64_t);
void dds3ObjectBaseOnFlag(uint64_t, uint64_t);
void dds3ObjectBaseOffFlag(uint64_t, uint64_t);
void dds3SetPosPoseSet(uint64_t, uint64_t);
uint64_t fw_fade_query(void);
uint64_t fw_fade_set(uint64_t);
void ps2SoundSetBankSource(uint64_t, uint64_t);
uint64_t fileRequest(uint64_t);
uint64_t fileCheckEnd(uint64_t);
uint64_t fileGetMemHandle(uint64_t);
uint64_t fileGetLoadSize(uint64_t);
void ps2ResourceRequestRelease(uint64_t);
void nbStopMotionSe(void);
uint64_t nbGetMotionSeNo(uint64_t, uint64_t);
uint64_t nbMemoryLoadMotionSe(uint64_t, uint64_t);
void nbMakeSkillEffectPacket(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
void nbMakeTargetPacket(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint32_t);
void effBTLSkillSetFormationInfo(uint64_t, uint64_t);
void nbInitNegoProcess(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
void nbPanelPressGaugeShow(void);
void nbPanelStockSelectInit(void);
void nbPanelStockEnd(void);
void dds3FadeOut(uint64_t, uint64_t, uint64_t, uint64_t);
void ps2PoolRelease(uint32_t);
}

namespace difftest::iface {

namespace {

namespace fr = nocturne::fr;
namespace mes = nocturne::mes;

constexpr uint32_t kKuti = 0x001d1640;   // ps2MessageKutiDiagnostic
// Where the four fonts go: US Maniax's in FW_FONTS, the JP builds' (larger)
// in FW_JP_FONTS.
#if NOCTURNE_US
constexpr uint32_t kFontBase = FW_FONTS;
constexpr uint32_t kFontOffset[4] = {0x00000, 0x18000, 0x2e000, 0x33000};
#else
constexpr uint32_t kFontBase = FW_JP_FONTS;
constexpr uint32_t kFontOffset[4] = {0x00000, 0x5e000, 0x81600, 0x85e00};
#endif

std::vector<std::vector<uint8_t>> gTables;
std::vector<uint8_t> gFonts[4];
std::vector<std::vector<uint8_t>> gScripts;

// The original code around the interface, the script VM and the data it
// changes; the commands read the script work at FW_SCRIPT (script_bridge.cpp).
ee::Interpreter makeOriginal()
{
    ee::Interpreter e;
    if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype)
        e.interpret(0x002fdc20, 0x002ff388);   // Hardtype's own code, which its patched functions jump to
    e.interpret(0x001c6018, 0x001cae58);   // the font engine (frFont)
    e.interpret(0x001cae58, 0x001caf88);   // itfMiscLink*
    e.interpret(0x001cd2e0, 0x001d1108);   // the message manager (itfMesManager)
    e.interpret(0x00158940, 0x00158948);   // an empty function (HD: the UI's open / close hook)
    e.interpret(0x001097e8, 0x0010d730);   // the script VM, scrCommonCommand and scrParameterCommand
    e.interpret(0x00104d38, 0x00104da0);   // dds3SetQuake, dds3StopQuake
    e.interpret(0x00105580, 0x001062e0);   // dds3KernelDraw: the camera, the screen blur and the event effects
    e.interpret(0x001070d0, 0x00107310);   // dds3SetLightColor, dds3SetLightDir
    e.interpret(0x00106ee0, 0x001070d0);   // dds3RotationArc
    e.interpret(0x002c04e8, 0x002c050c);   // ps2QuaternionNormalize
    e.interpret(0x00107310, 0x001074f0);   // dds3SetAmbientColor, dds3SetFogColor, dds3SetFogPara
    e.interpret(0x00107af0, 0x00107b40);   // dds3SetSoftenBias
    e.interpret(0x001ad230, 0x001ad5c8);
    e.interpret(0x00242a88, 0x002460b0);   // datCalc
    e.interpret(0x0025e8e0, 0x0025eaf0);   // nbKoukaProcess: the queue
    e.interpret(0x0025eaf0, 0x0025edc0);   // DelKoukaPacket .. nbDelAllMojiNumEffectKoukaPacket
    e.interpret(0x0028b448, 0x0028b628);   // nbSetPlayerSummonFormation, nbSetEnemySummonFormation
    e.interpret(0x00259c48, 0x00259c90);   // nbGetItemSkillNo
    e.interpret(0x00253830, 0x00253bf8);   // SetAction_COMM, CheckAction_COMM
    e.interpret(0x00256a98, 0x00256b88);   // SetAction_NEGO
    e.interpret(0x00254488, 0x00255650);   // SetAction_READY, CheckAction_READY
    e.interpret(0x00255650, 0x00256a98);   // SetAction_SKILL, CheckAction_SKILL
    e.interpret(0x0016ab70, 0x0016abcc);   // effBTLGetMotionChangeFrame, effBTLGetCutEndFrame
    e.interpret(0x0016aec0, 0x0016af20);   // effBTLCut: motion change and end frames, the draw end
    e.interpret(0x0016b090, 0x0016b0f0);   // effBTLCutSetCameraState
    e.interpret(0x0016ba40, 0x0016ba68);   // effBTLSkillSetState
    e.interpret(0x0016aea0, 0x0016aec0);   // effBTLCutGetFrame, effBTLCutSetCutEndFrame
    e.interpret(0x0025edc0, 0x0025ee78);   // nbDelUnEventKoukaPacket
    e.interpret(0x0025efd0, 0x00261500);   // the kouka process: its players, nbKoukaProcess1, shutdown, init
    e.interpret(0x0024df58, 0x0024df80);   // nbSetSakeMotion's step
    e.interpret(0x0027fa88, 0x0027fa98);   // the stock panel's fade out
    e.interpret(0x00100448, 0x00100488);   // dds3Stop, dds3SlowOn
    e.interpret(0x002518c8, 0x00251ef0);   // GetKoukaList
    e.interpret(0x0024ff60, 0x00251428);   // SetAllPacket
    e.interpret(0x002654b8, 0x0026a840);   // nbCalc (its hooks still win)
    e.interpret(0x0024d310, 0x0024d550);   // nbGetMotionEndType, EndData, Actframe, Speed, No
    e.interpret(0x00259a60, 0x00259ab0);   // nbGetUnitVisual
    e.interpret(0x00269280, 0x00269314);   // nbCheckSkillUse
    e.interpret(0x0026a688, 0x0026a6d8);   // nbCheckBadPanicAction
    e.interpret(0x00259018, 0x00259180);   // nbSetNormalSkill0
    e.interpret(0x0026a3d8, 0x0026a448);   // nbHatudoCheckSkill
    e.interpret(0x00256c00, 0x00257098);   // SetAction_NEGORESULT
    e.interpret(0x001b17e0, 0x001b1810);   // nbCameraSetTaizi
    e.interpret(0x00253de0, 0x00253e00);   // SetAction_BAD
    e.interpret(0x00254190, 0x00254488);   // CheckAction_TARSEL, the STKSEL pair
    e.interpret(0x0025ee78, 0x0025efd0);
    e.interpret(0x00261500, 0x00264710);   // nbMakePacket
    e.interpret(0x00259a30, 0x00259a5c);   // nbGetUnitID
    e.interpret(0x00259ab0, 0x00259bd0);   // nbCheckEventDead, nbCheckDeadScript, nbCheckDeadEvent
    e.interpret(0x00267788, 0x002677b4);   // nbGetBadStat
    e.interpret(0x002514f0, 0x002518c8);   // nbActionProcess: the time list
    e.interpret(0x0026a7d0, 0x0026a824);   // nbGetDevilFormatFlag
    e.interpret(0x00253488, 0x00253830);   // SetAction_NON, CheckAction_NON
    e.interpret(0x00253bf8, 0x00253de0);   // SetAction_AI .. CheckAction_DEADSCRIPT
    e.interpret(0x00288d80, 0x00288e18);   // nbInitAiScript
    e.interpret(0x00288e18, 0x002894e0);   // nbHelpProcess: nbDispText .. nbHelpOff
    e.interpret(0x002898c0, 0x002899fc);   // nbHelpShutdown, InitHelpProcessData, nbInitHelpProcess
    e.interpret(0x0028e3c8, 0x0028f218);   // nbBadAi
    e.interpret(0x00253e00, 0x00254178);   // CheckAction_BAD, the BADWAIT pair
    e.interpret(0x001b1740, 0x001b1770);   // nbCameraSetState
    e.interpret(0x001b17a0, 0x001b17e0);   // nbCameraSetBougai
    e.interpret(0x001b1810, 0x001b18c4);   // nbCameraSetTarget, nbCameraSetHojo, the event target's
    e.interpret(0x0016b940, 0x0016b984);   // effBTLSkillGetInvokeFormation
    e.interpret(0x00272718, 0x002731a8);   // the talks' group 9 (NbNegoFlowOk)
    e.interpret(0x00274e90, 0x00274f38);   // group 3 (NbNegoFlowStock)
    e.interpret(0x002773b8, 0x002774a8);   // group 14 (NbNegoFlowBinjo)
    e.interpret(0x00278748, 0x00278cb8);   // group 13 (NbNegoFlowSensei)
    e.interpret(0x00275df8, 0x00276760);   // group 7 (NbNegoFlowQuestion)
    e.interpret(0x00274228, 0x00274e90);   // group 2 (NbNegoFlowFullMoon)
    e.interpret(0x0026cd80, 0x0026eb08);   // group 1 (NbNegoFlowOne)
    e.interpret(0x00274f38, 0x00275780);   // group 4 (NbNegoFlowDouchara)
    e.interpret(0x00278cb8, 0x002794b0);   // group 15 (NbNegoFlowInoti)
    e.interpret(0x00276760, 0x00276d08);   // group 8 (NbNegoFlowFight)
    e.interpret(0x00275780, 0x00275df8);   // group 5 (NbNegoFlowInnen)
    e.interpret(0x002731a8, 0x00274228);   // group 10 (NbNegoFlowNg)
    e.interpret(0x002774a8, 0x00278748);   // group 12 (NbNegoFlowMukan)
    e.interpret(0x00276d08, 0x002773b8);   // group 11 (NbNegoFlowDrain)
    e.interpret(0x00282258, 0x00282270);   // nbPanelPartyShow, nbPanelPartyHide
    e.interpret(0x002794b0, 0x00279690);   // group 16 (NbNegoFlowKoketa)
    e.interpret(0x002592b0, 0x00259318);   // nbSetJyokyoMes, nbGetJyokyoMes
    e.interpret(0x00257b08, 0x00257bf0);   // SetAction_END
    e.interpret(0x00257098, 0x00257488);   // NEGORESULT's check, WAIT, ESCAPE, RETURN, INVISIBLE
    e.interpret(0x00257488, 0x00257a68);   // CHECK1
    e.interpret(0x0025d690, 0x0025d948);   // nbTarSelProcess: the record, its state, AnimeTargetCursor
    e.interpret(0x0025de40, 0x0025e8e0);   // nbTarSelProcess: SetCursor .. nbInitTarSelProcess
    e.interpret(0x0028c9ec, 0x0028e3c8);   // nbEncount (Hardtype's nbGetEncountJoken starts a word early), nbSound (with nbPlaySe), nbEncProcess
    e.interpret(0x00259c90, 0x00259d20);   // nbCommSelProcess: GetCommListCnt, GetCommSelProcessData
    e.interpret(0x0025b408, 0x0025b598);   // AnimeCommandList
    e.interpret(0x0025c190, 0x0025c908);   // CheckSelectError .. nbCloseCommSel
    e.interpret(0x0025cb40, 0x0025d690);   // nbCommSelShutdown .. nbInitCommSelProcess
    e.interpret(0x00290048, 0x00290b20);   // nbSkillError
    e.interpret(0x0029ba80, 0x0029bb08);   // dds3CheckConfigBit
    e.interpret(0x001e0e38, 0x001e0e6c);   // evtBitAllOff (its callers get the fake; origOwn tests it)
    e.interpret(0x001e0ed0, 0x001e0f80);   // evtBitOn, evtBitOff, evtBitCheck (the same)
    e.interpret(0x001e9998, 0x001e9a7c);   // the moon's phase and switches (the same)
    e.interpret(0x00251428, 0x002514f0);   // SetTarget
    e.interpret(0x00254178, 0x00254190);   // SetAction_TARSEL
    e.interpret(0x00256b88, 0x00256c00);   // CheckAction_NEGO
    e.interpret(0x0024f420, 0x0024f990);   // UnitKyoseiDisp .. SetAnalyzePacket
    e.interpret(0x0024fb38, 0x0024fcc0);   // SetSakePacket, SetMissPacket
    e.interpret(0x00251ef0, 0x002532a8);   // SetTargetPlayer .. SetNowActionStat: side events
    e.interpret(0x0028fa80, 0x0028fad8);   // the first enemy slot with someone in it
    e.interpret(0x002532a8, 0x00253488);   // SetDamagePacket
    e.interpret(0x0024f990, 0x0024fb38);   // SetPlayerSummonPacket
    e.interpret(0x0024fcc0, 0x0024ff60);   // SetOngShadowPacket, SetOngShadowPacket2
    e.interpret(0x00263110, 0x00263350);   // Ongyo-Ki's packets
    e.interpret(0x00198860, 0x00198868);   // effPCPBossONGYGetLength
    e.interpret(0x00198ff8, 0x00199000);   // effPCPBossONGY2GetLength
    e.interpret(0x00199b08, 0x00199b10);   // effPCPBossBUNSINGetLength
    e.interpret(0x00199cb0, 0x00199cd0);   // effPCPBossBUNSIN2GetLength
    e.interpret(0x00259180, 0x002592b0);   // nbGetNakama, nbSetDevilNameMes
    e.interpret(0x002594b0, 0x002596d0);   // nbAppendEnemyDevilWork, nbGetRandamStock, nbSetEncounterAndReset
    e.interpret(0x002596d0, 0x00259740);   // nbClearCommandMemeoyRenzoku
    e.interpret(0x00257a68, 0x00257b08);   // CHECK3, ATO
    e.interpret(0x00257bf0, 0x00257c80);   // CheckAction_END, nbGetActionSeq, nbGetPrevActionSeq
    e.interpret(0x00257c80, 0x00257cc8);   // nbActionSetSeq
    e.interpret(0x00257cd0, 0x00257e30);   // nbActionProcess1
    e.interpret(0x002c2178, 0x002c2180);   // ps2MovieCheckAdpcmFlag
    e.interpret(0x00257cc8, 0x00257cd0);   // SetNextActionSeq
    e.interpret(0x00223628, 0x00223668);   // cmpCalcLevelUpBaseExp
    e.interpret(0x00223668, 0x00223728);   // cmbCalcLevelUpExp
    if (version::active())
        e.interpret(0x00223728, 0x00223744);   // cmbChkLevelUpExp (the JP builds' cmbCalcIkenieExp calls it)
    e.interpret(0x00222160, 0x002221cc);   // cmbGetMasterHeartsNums
    e.interpret(0x00221f20, 0x002220c0);   // cmbChkMasterHeartsStatNums
    e.interpret(0x00221e70, 0x00221ef4);   // cmbGetPlayerRaceID
    e.interpret(0x002071e0, 0x002074c0);   // the shop: item, pack, count, price
    e.interpret(0x002d4860, 0x002d5250);   // the C library's qsort (its epilogue past the size Ghidra gives it)
    e.interpret(0x00213230, 0x0021327c);   // cmbDevilSortCallback (qsort's test sorts with it)
    e.interpret(0x00216b78, 0x00216b90);   // fclEncycGetNum
    e.interpret(0x00216b90, 0x00216bec);   // fclEncycGetRatio2
    e.interpret(0x00219df0, 0x00219fbc);   // fclEncyc_SetElem
    e.interpret(0x00216b20, 0x00216b78);   // ps2CompendiumRestore_00216B20
    e.interpret(0x00216a18, 0x00216b20);   // ps2CompendiumRecords_00216A18
    e.interpret(0x00221550, 0x00221558);   // ps2UnitMagatamaEquipHook_00221550
    e.interpret(0x00222408, 0x0022246c);   // ps2HeartsAddParam
    e.interpret(0x00240a98, 0x00240b48);   // ps2UnitRecalculateMaxHpMp_00240A98
    e.interpret(0x00221558, 0x00221560);   // ps2UnitMagatamaUnequipHook_00221558
    e.interpret(0x002222c0, 0x00222318);   // cmbGetHeartsDefaultParam
    e.interpret(0x00222318, 0x0022239c);   // cmbGetHeartsParamEx
    e.interpret(0x00222140, 0x0022215c);   // cmbChkHeartsMaster
    e.interpret(0x002223a0, 0x00222404);   // cmbGetHeartsParam
    e.interpret(0x00222470, 0x002224d4);   // cmbSubHeartsParam
    e.interpret(0x00222550, 0x00222610);   // cmbCreateDefaultHeartsSkill
    // Fusion functions a version changes (variant_tests.cpp).
    e.interpret(0x001fd3b0, 0x001fd428);   // cmbChkEventDevil
    e.interpret(0x001fe880, 0x001fe9e4);   // cmbCalcIkenieExp
    e.interpret(0x001feda0, 0x001fedf0);   // cmbChkSkillOwner
    e.interpret(0x001fef20, 0x001ff050);   // cmbCopyCustomDevilToStock
    e.interpret(0x00221d70, 0x00221dac);   // cmbGetParam
    e.interpret(0x00222aa0, 0x00222cf4);   // cmbGetKeisyoSkillScore, Motion, Level, cmbCalcKeisyoSkillRate
    e.interpret(0x00222e00, 0x0022307c);   // cmbAddLevelUpParamEx
    e.interpret(0x00223520, 0x0022362c);   // cmbGetMutationSkill
    e.interpret(0x00223728, 0x00223748);   // cmbChkLevelUpExp
    e.interpret(0x00223928, 0x002239b0);   // cmbGetLevelUpCount
    // sdfGetRand: the fake's value, and the carry bit the real one leaves in
    // a1 (the default state's third word, which the fake doesn't advance).
    // It also leaves in a3 the old first state word, which becomes the
    // second: the second as the fake leaves it (Hardtype's SetCommList reads it).
    e.hook(0x002c0ba8, [](ee::Cpu& c) {
        c.r[5] = *nocturne::guest::table<uint32_t>(version::dataOrDie(0x00529be0)) >> 31;
        c.r[7] = *nocturne::guest::table<uint32_t>(version::dataOrDie(0x00529bdc));
        return uint64_t{sdfGetRand(nullptr)};
    });
    e.interpret(0x002328c8, 0x00232920);   // cmpChkHaveHearts
    e.interpret(0x00232880, 0x002328c8);   // cmpChkHaveNormalHeartsAll
    e.interpret(0x002138c0, 0x00213934);   // fclChkItemHearts   // effEvent: the event effects' switches and settings
    e.interpret(0x001caf78, 0x001caff4);   // itfMiscSetRatioRGB
    e.interpret(0x001cc080, 0x001cc2b8);   // itfPanel: registering, releasing, placing, colouring
    e.interpret(0x001cc358, 0x001cc9a0);   // itfPanel: the vertex and colour builders
    e.interpret(0x002d1550, 0x002d1d68);   // libgcc soft double
    e.interpret(0x002d3398, 0x002d3810);
    auto a = [](ee::Cpu& c, int i) { return c.arg(i); };
    auto none = [](auto) { return uint64_t{0}; };
    (void)none;
    e.hook(0x002c18d8, [=](ee::Cpu& c) { return ps2SoundPlay(a(c, 0), a(c, 1), a(c, 2)); });
    e.hook(0x00101af8, [=](ee::Cpu& c) { dds3LinkProcess(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x00280518, [](ee::Cpu&) { nbPanelAnalyzeStart(); return uint64_t{0}; });
    e.hook(0x0027fd18, [=](ee::Cpu& c) { return nbPanelStockSelect(a(c, 0), a(c, 1)); });
    e.hookUs(0x00280528, [](ee::Cpu&) { nbPanelAnalyzeEnd(); return uint64_t{0}; });
    e.interpret(0x00267ec8, 0x00267f14);   // nbGetHojoCounterMax (Hardtype patches it)
    e.interpret(0x00267f18, 0x00267f54);   // nbGetHojoCounterMin (Hardtype patches it)
    e.interpret(0x00258048, 0x00258534);   // the turn order (nbAddOrder .. nbUpdateOrder)
    e.hook(0x002c2180, [](ee::Cpu&) { return ps2MovieStopAdpcm(); });
    e.hook(0x00198200, [=](ee::Cpu& c) { return ps2BattleActionSkill_00198200(a(c, 0)); });
    e.hook(0x00198868, [=](ee::Cpu& c) { return ps2BattleActionSkill_00198868(a(c, 0)); });
    e.hook(0x00199000, [=](ee::Cpu& c) { return effPCPBossBUNSINCreate(a(c, 0)); });
    e.hook(0x00199b10, [=](ee::Cpu& c) { return effPCPBossBUNSIN2Create(a(c, 0)); });
    e.hookUs(0x00269448, [=](ee::Cpu& c) { ps2CombatAddRewards_00269448(a(c, 0)); return uint64_t{0}; });
    e.hookUs(0x0026a448, [=](ee::Cpu& c) { return ps2CombatSingleTargetSkill_0026A448(a(c, 0)); });
    e.interpret(0x0026a4b0, 0x0026a684);   // nbGetMakaBaramaki (Hardtype patches it)
    e.hookUs(0x00267e50, [=](ee::Cpu& c) { nbSetHojoCounter(a(c, 0), a(c, 1), a(c, 2)); return uint64_t{0}; });
    e.hookUs(0x00267e90, [=](ee::Cpu& c) { return nbGetHojoCounter(a(c, 0), a(c, 1)); });
    e.hookUs(0x0026a2d8, [=](ee::Cpu& c) { return nbCheckKuisibariSkill(a(c, 0)); });
    e.hookUs(0x0026a338, [=](ee::Cpu& c) { return nbCheckKuisibari2Skill(a(c, 0)); });
    e.hookUs(0x0026a398, [=](ee::Cpu& c) { nbSetKuisibariStop(a(c, 0)); return uint64_t{0}; });
    e.interpret(0x00267f58, 0x00268030);   // nbSetHojoAddCounter (through Hardtype's limits)
    e.hook(0x001e9998, [](ee::Cpu&) { return uint64_t{evtGetAgeOfMoon()}; });
    e.hook(0x00282200, [=](ee::Cpu& c) { ps2BattlePanelSetEnabled_00282200(a(c, 0)); return uint64_t{0}; });
    e.interpret(0x00269e98, 0x0026a110);   // nbCheckEscape (Hardtype patches it)
    e.interpret(0x00269170, 0x0026927c);   // nbCheckSkillCost (Hardtype patches it)
    e.hookUs(0x0026a110, [=](ee::Cpu& c) { return nbGetEscapeSwitch(a(c, 0)); });
    e.interpret(0x002853d8, 0x00287d78);   // the enemy AI (nbAi*, nbRunAi)
    e.interpret(0x00258de8, 0x00259018);   // nbGetTargetTypeRuleArea
    e.hookUs(0x0025dc00, [=](ee::Cpu& c) { return nbSetSelectOkMark(a(c, 0), a(c, 1), a(c, 2), a(c, 3)); });
    if (version::active())
        e.interpret(0x0025da78, 0x0025dc00);   // CheckFormCursor, which nbSetSelectOkMark calls
    e.hookUs(0x00246b68, [=](ee::Cpu& c) { return nbGetSelectBit(a(c, 0)); });
    e.hookUs(0x0026a468, [=](ee::Cpu& c) { return nbCheckFormationPlayerSide(a(c, 0)); });
    e.hookUs(0x002677b8, [=](ee::Cpu& c) { return ps2CombatCheckCurse_002677B8(a(c, 0)); });
    e.hook(0x002a9038, [=](ee::Cpu& c) { return uint64_t{ps2MemoryHandleAllocate(static_cast<int32_t>(a(c, 0)))}; });
    e.hook(0x002a9688, [=](ee::Cpu& c) { return uint64_t{ps2MemoryHandleAcquirePointer(static_cast<uint32_t>(a(c, 0)))}; });
    e.hook(0x002a9558, [=](ee::Cpu& c) { ps2MemoryHandleFree(static_cast<uint32_t>(a(c, 0))); return uint64_t{0}; });
    e.hook(0x002c39c8, [=](ee::Cpu& c) { ps2PacRelocatePointers(a(c, 0), a(c, 1), a(c, 2), a(c, 3)); return uint64_t{0}; });
    e.hook(0x002d4748, [=](ee::Cpu& c) {
        int64_t args[5];
        for (int i = 0; i < 5; ++i)
            args[i] = static_cast<int64_t>(a(c, i + 1));
        fw_record_print(static_cast<uint32_t>(a(c, 0)), args);
        return uint64_t{0};
    });
    e.hook(0x001cb0d8, [=](ee::Cpu& c) { return ps2InterfaceLoadTexture(a(c, 0)); });
    e.hook(0x002ab8f0, [=](ee::Cpu& c) { ps2TextureDeferredRelease(a(c, 0)); return uint64_t{0}; });
    e.hook(0x001015b0, [=](ee::Cpu& c) { return dds3StartProcess(a(c, 0), a(c, 1), a(c, 2), a(c, 3), a(c, 4), a(c, 5), a(c, 6)); });
    e.hook(0x002a8af8, [=](ee::Cpu& c) { return uint64_t{ps2PoolAllocate(static_cast<int32_t>(a(c, 0)))}; });
    e.hook(0x002aa9e0, [=](ee::Cpu& c) { return ps2TextureQueueUpload(a(c, 0)); });
    e.hook(0x00100418, [](ee::Cpu&) { return ps2KernelGetFontContextIndex(); });
    e.hook(0x002c3718, [=](ee::Cpu& c) { return sdfDevLoadFile(a(c, 0), a(c, 1), a(c, 2)); });
    e.hook(0x001e0f50, [=](ee::Cpu& c) { return uint64_t{evtBitCheck(static_cast<int32_t>(a(c, 0)))}; });
    e.hook(0x001e0ed0, [=](ee::Cpu& c) { evtBitOn(static_cast<int32_t>(a(c, 0))); return uint64_t{0}; });
    e.hook(0x001e0f10, [=](ee::Cpu& c) { evtBitOff(static_cast<int32_t>(a(c, 0))); return uint64_t{0}; });
    // sdfGetRandInt: as sdfGetRand above, with the registers sdfGetRand leaves.
    e.hook(0x002c0c60, [=](ee::Cpu& c) {
        const uint32_t state = a(c, 0) ? static_cast<uint32_t>(a(c, 0)) : version::dataOrDie(0x00529bd8);
        const uint32_t range = static_cast<uint32_t>(a(c, 1));
        c.r[5] = *nocturne::guest::table<uint32_t>(state + 8) >> 31;
        c.r[7] = *nocturne::guest::table<uint32_t>(state + 4);
        return uint64_t{sdfGetRandInt(nullptr, range)};
    });
    e.hook(0x00101738, [=](ee::Cpu& c) { return dds3KillProcess(a(c, 0), a(c, 1)); });
    e.hook(0x00101978, [=](ee::Cpu& c) { return dds3SearchProcessPriority(a(c, 0)); });
    e.hook(0x00101a08, [=](ee::Cpu& c) { return dds3ExistProcess(a(c, 0)); });
    e.hook(0x00101aa0, [=](ee::Cpu& c) { return ps2ProcessGetRunTime(a(c, 0)); });
    e.hook(0x00101aa8, [=](ee::Cpu& c) { dds3SetProcessData(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x00101ab0, [=](ee::Cpu& c) { return dds3GetProcessData(a(c, 0)); });
    e.hook(0x00104fe0, [=](ee::Cpu& c) { dds3FadeIn(a(c, 0), a(c, 1), a(c, 2), a(c, 3)); return uint64_t{0}; });
    e.hook(0x00105098, [=](ee::Cpu& c) { dds3FadeOut(a(c, 0), a(c, 1), a(c, 2), a(c, 3)); return uint64_t{0}; });
    e.hook(0x002c0c00, [](ee::Cpu& c) { c.f[0] = static_cast<uint32_t>(floatBits(sdfGetRandFloat(nullptr))); return uint64_t{0}; });
    e.hook(0x0016ab10, [=](ee::Cpu& c) { effBTLDelete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x0016ae08, [=](ee::Cpu& c) { effBTLCutDelete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x0016ac70, [=](ee::Cpu& c) { return effBTLCutCreate(a(c, 0), a(c, 1), a(c, 2), a(c, 3)); });
    // The kouka process's engine calls.
    e.hook(0x001982c8, [=](ee::Cpu& c) { effPCPBossONGYDraw(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00198930, [=](ee::Cpu& c) { effPCPBossONGY2Draw(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00199600, [=](ee::Cpu& c) { effPCPBossBUNSINDraw(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00199c08, [=](ee::Cpu& c) { effPCPBossBUNSIN2Draw(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00173cb0, [=](ee::Cpu& c) { return ps2BattleAction_00173CB0(a(c, 0), a(c, 1)); });
    e.hook(0x00173d28, [=](ee::Cpu& c) { effBTLPartEnd(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00173dc8, [=](ee::Cpu& c) { effBTLPartDraw(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00280538, [=](ee::Cpu& c) { ps2BattlePanelSetAnalyzeUnit_00280538(a(c, 0)); return uint64_t{0}; });
    e.interpret(0x0028a158, 0x0028a200);   // nbSetFormRot
    e.hook(0x0010ded8, [=](ee::Cpu& c) { dds3SetRotPoseSet(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.interpret(0x0028f218, 0x0028f7e8);   // nbMakaProcess (the Macca window)
    e.interpret(0x001ca508, 0x001ca5dc);   // the font's short string request
    e.hook(0x002797b0, [=](ee::Cpu& c) { ps2BattlePanelSetOrderingOffset_002797B0(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00279868, [=](ee::Cpu& c) {
        ps2BattlePanelSetPrimitive(a(c, 0), a(c, 1), a(c, 2), a(c, 3), a(c, 4), a(c, 5), a(c, 6), a(c, 7));
        return uint64_t{0};
    });
    e.hook(0x00279980, [=](ee::Cpu& c) { ps2BattlePanelSetAlpha(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00279a88, [=](ee::Cpu& c) {   // (arguments 9 and 10 on the stack, 8 bytes each)
        const uint32_t sp = static_cast<uint32_t>(c.r[29]);
        uint64_t color, texture;
        std::memcpy(&color, fw_resolve(sp), 8);
        std::memcpy(&texture, fw_resolve(sp + 8), 8);
        ps2BattlePanelDrawTexturedRect(a(c, 0), a(c, 1), a(c, 2), a(c, 3), a(c, 4), a(c, 5), a(c, 6), a(c, 7),
                                       static_cast<uint32_t>(color), static_cast<uint32_t>(texture));
        return uint64_t{0};
    });
    e.hook(0x001c7e38, [=](ee::Cpu& c) { return frDrawFontEx2(a(c, 0), a(c, 1), a(c, 2)); });
    e.interpret(0x0028f7e8, 0x00290048);   // nbEventProcess
    e.interpret(0x00115060, 0x00115074);   // (marks a basic effect)
    e.hook(0x002c1670, [=](ee::Cpu& c) { return ps2SoundPlayMidi_002C1670(a(c, 0)); });
    e.hook(0x002c2070, [=](ee::Cpu& c) { return ps2SoundFadeOut_002C2070(a(c, 0)); });
    e.hook(0x002c1ca0, [=](ee::Cpu& c) { ps2SoundEnsureBank(a(c, 0)); return uint64_t{0}; });
    e.hook(0x002966a8, [=](ee::Cpu& c) { return ps2ResourcePacRequestFree(a(c, 0)); });
    e.hook(0x00296b88, [](ee::Cpu&) { ps2BattleActionRequest_00296B88(); return uint64_t{0}; });
    e.hook(0x001fac78, [=](ee::Cpu& c) { return fw_event_pack_load(a(c, 0)); });
    e.hook(0x001fa1f0, [=](ee::Cpu& c) { return fw_event_pack_state(a(c, 0)); });
    e.hook(0x00114770, [=](ee::Cpu& c) { return fw_basic_effect(a(c, 0), a(c, 1), a(c, 2)); });
    e.interpret(0x0026eb08, 0x00272718);   // group 6 (NbNegoFlowTwo) and its affinity checks
    for (const uint32_t mover : {0x00265130u, 0x00265298u, 0x002653a0u})
        e.hook(mover, [=](ee::Cpu& c) { return fw_move_packets(version::code(mover), a(c, 0), a(c, 1), a(c, 2), a(c, 3)); });
    e.hook(0x0024d980, [=](ee::Cpu& c) { nbReturnUnit(a(c, 0), a(c, 1), a(c, 2)); return uint64_t{0}; });
    e.hook(0x0024dd10, [=](ee::Cpu& c) { nbMoveTarget(a(c, 0), a(c, 1), static_cast<uint32_t>(c.f[12])); return uint64_t{0}; });
    e.hook(0x0024de40, [=](ee::Cpu& c) { nbMoveHome(a(c, 0), static_cast<uint32_t>(c.f[12])); return uint64_t{0}; });
    e.hook(0x001e99c0, [](ee::Cpu&) { return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(evtGetAgeOfMoon16()))); });
    e.hook(0x001e99d0, [=](ee::Cpu& c) { evtSetAgeOfMoon(static_cast<int32_t>(a(c, 0))); return uint64_t{0}; });
    e.interpret(0x0028a340, 0x0028a758);   // nbSetPartyFormation
    e.interpret(0x0028a758, 0x0028b0a0);   // nbSetEnemyFormation
    e.interpret(0x0028a2e0, 0x0028a2f0);   // nbLoadUnitPos
    e.interpret(0x0016e560, 0x0016e5ac);   // effBTLModelGetID
    e.interpret(0x002c0060, 0x002c017c);   // sdfSin, sdfCos
    e.interpret(0x002c0228, 0x002c0258);   // sdfAtan
    e.interpret(0x002c0488, 0x002c04b8);   // Mult (the quaternion product)
    e.hook(0x002c1730, [=](ee::Cpu& c) { ps2SoundStopEffectMidi_002C1730(a(c, 0)); return uint64_t{0}; });
    e.interpret(0x0028b0a0, 0x0028b0b8);   // nbSetPlayerFormation
    e.hook(0x0024df78, [=](ee::Cpu& c) { nbSetDamage(a(c, 0), a(c, 1), static_cast<uint32_t>(c.f[12])); return uint64_t{0}; });
    e.hook(0x0024e020, [=](ee::Cpu& c) { nbSetDamage2(a(c, 0), static_cast<uint32_t>(c.f[12])); return uint64_t{0}; });
    e.hook(0x0024e040, [=](ee::Cpu& c) { nbSetBadstatMotion(a(c, 0), a(c, 1), static_cast<uint32_t>(c.f[12])); return uint64_t{0}; });
    e.hook(0x0024e0e8, [=](ee::Cpu& c) { nbSetBadstatMotion2(a(c, 0)); return uint64_t{0}; });
    e.hook(0x0026bf00, [=](ee::Cpu& c) { NegoDebugDraw(a(c, 0)); return uint64_t{0}; });
    e.hook(0x0026c0d8, [=](ee::Cpu& c) { NegoDebugSelectDraw(a(c, 0)); return uint64_t{0}; });
    e.hook(0x0026c2d8, [=](ee::Cpu& c) { return NegoDebug(a(c, 0)); });
    e.hook(0x002c20a0, [](ee::Cpu&) { ps2SoundVolumeHalfDown_002C20A0(); return uint64_t{0}; });
    e.hook(0x002c20c8, [](ee::Cpu&) { ps2SoundVolumeHalfUp_002C20C8(); return uint64_t{0}; });
    e.hook(0x00777300, [=](ee::Cpu& c) { return fw_talk_step(a(c, 0)); });   // the tests' talk step
    e.interpret(0x0024cf70, 0x0024cff8);   // the demon's talking pose
    e.interpret(0x0024bff0, 0x0024c1d0);   // GetAddExp, nbResultAddExp
    // The result screen (nbResultProcess): what is rewritten; what follows
    // it and the stage's release logged.
    e.hook(0x002abe08, [=](ee::Cpu& c) { return ps2TextureTmxCopy(a(c, 0)); });
    e.interpret(0x0024a060, 0x0024a2e8);   // nbResultLoad, nbResultTexDel, nbResultLvupAnmAdd
    e.interpret(0x0024ae70, 0x0024b010);   // nbResultSkip, nbResultFinWaitChk
    // The battle's close (nb_ato, battle/closing.hpp) and its callees.
    e.interpret(0x00249c28, 0x0024a000);   // its endings, step, start and end
    e.interpret(0x001ddb78, 0x001ddb84);   // mdlGetMinorNum
    e.interpret(0x001221f0, 0x0012221c);   // the field's work let go
    e.interpret(0x00245f68, 0x00246034);   // datBossRashUpdRec
    e.interpret(0x00289e68, 0x00289ecc);   // nbSingleFormExceptedDispOff
    e.interpret(0x00289310, 0x00289448);   // nbDispMsgHelp
    e.interpret(0x0028dda8, 0x0028ddcc);   // nbBgmFadeOut
    e.interpret(0x001e3cc0, 0x001e3d80);   // evtSetUnitMotion
    e.interpret(0x001e3b68, 0x001e3b88);   // evtSetWaitMotion, evtSetWaitMotionSpeed, evtSetWaitHokanFrame
    e.interpret(0x0024ce78, 0x0024cf70);   // GetDyingBadWaitMotion
    e.interpret(0x0024cff8, 0x0024d310);   // nbSetUnitMotion, nbSetWaitMotion
    e.hook(0x001ddba8, [=](ee::Cpu& c) {   // mdlGetNumOfCut: the fake model's animation count (its +4)
        return uint64_t{*nocturne::guest::table<const uint32_t>(static_cast<uint32_t>(a(c, 0)) + 4)};
    });
    // The battle's opening (nb_mae, battle/opening.hpp).
    e.interpret(0x00249a38, 0x00249c28);   // its steps, start and end
    e.interpret(0x0024c6c8, 0x0024c6f0);   // the stage requested
    e.interpret(0x0024c718, 0x0024c728);   // nbGetStageData
    e.interpret(0x001abbd0, 0x001abc88);   // effColorBlend
    e.interpret(0x002497a0, 0x00249850);   // SetFlag
    e.interpret(0x00249640, 0x002497a0);   // nbInitMainProcessData
    e.interpret(0x00249850, 0x00249a38);   // nbInitMainProcess and the battle's end
    e.interpret(0x00246998, 0x002469a0);   // (empty)
    e.interpret(0x00249258, 0x00249320);   // the passive skills' effect, ClearLocalBit
    e.interpret(0x001e9528, 0x001e95a0);   // the moon's texture
    e.interpret(0x00249320, 0x002493a8);   // the main process's end
    e.interpret(0x00247d60, 0x002481e8);   // the checks at the start and between actions, the action stack
    e.interpret(0x00248c88, 0x00248cb0);   // nbSetNextPhase
    e.interpret(0x002481e8, 0x00248c88);   // the phases' entries
    e.interpret(0x00248cb0, 0x00249258);   // nbSetPhase, nbMainProcess1
    // What the phases call that isn't rewritten yet: each call logged with
    // its arguments, as many as it takes (rstChkResultEntry's answer is the
    // case's).
    const std::pair<uint32_t, int> notRewritten[] = {
        {0x001b6a00, 1}, {0x0016b770, 0}, {0x0016ba78, 0}, {0x0016f490, 0}, {0x0016de10, 0}, {0x00174490, 0},
        {0x00279708, 1}, {0x0027fa48, 0}, {0x00280508, 0}, {0x00281e38, 0},
        {0x00246f10, 1}, {0x00247980, 1}, {0x00246d08, 1}};
    for (const auto& [entry, count] : notRewritten) {
        e.hook(entry, [=](ee::Cpu& c) {
            uint32_t args[5] = {};
            for (int i = 0; i < count; ++i)
                args[i] = static_cast<uint32_t>(a(c, i));
            fw_mes_log(159, entry ^ args[0] << 24, args[1] ^ args[2] << 8 ^ args[3] << 16 ^ args[4] << 24);
            return uint64_t{0};
        });
    }
    e.interpret(0x0021f788, 0x0021f838);   // rstChkLevelUpTarget, rstChkResultEntry
    e.interpret(0x0024d550, 0x0024d938);   // nbAddUnitStock, nbSummonUnit
    e.interpret(0x0024e178, 0x0024e1e0);   // nbInitUnitEffect
    e.interpret(0x002852c0, 0x002853d8);   // nbDebugShutdown, InitDebugProcessData, nbInitDebugProcess
    e.interpret(0x00246bf8, 0x00246d08);   // nbDebugSelect
    e.interpret(0x00220000, 0x00220020);   // rstGetEquipHeartsAisyo
    e.interpret(0x00222290, 0x002222c0);   // cmbGetHeartsAisyo
    e.interpret(0x001ba6e0, 0x001ba828);   // the press turn camera (nbCameraPress)
    e.hook(0x00102848, [=](ee::Cpu& c) {   // dds3AdminiCallSequence: the sequence, its flag and its data's first word
        const uint32_t data = static_cast<uint32_t>(a(c, 1));
        fw_mes_log(161, static_cast<uint32_t>(a(c, 0)) ^ static_cast<uint32_t>(a(c, 3)) << 16 ^ static_cast<uint32_t>(a(c, 2)) << 24,
                   data ? *nocturne::guest::table<uint32_t>(data) : 0xffffffffu);
        return uint64_t{0};
    });
    e.interpret(0x0028d778, 0x0028d8b0);   // nbFreeSound1, nbFreeSound
    e.interpret(0x001cdb38, 0x001cdb7c);   // itfMesMngRelease
    e.interpret(0x00290bc8, 0x00290c18);   // the flight model's release
    e.interpret(0x0028b0b8, 0x0028b198);   // a formation set up (its delay slot one past Ghidra's size)
    e.interpret(0x0028b198, 0x0028b448);   // nbCopyFormation, nbMoveFormation, nbUpdateFormation (to its return)
    e.interpret(0x00173f40, 0x00173f48);   // effBTLSystemGetID
    // The particle effects' setters (effPCP*Set*).
    for (const auto& [entry, size] : std::initializer_list<std::pair<uint32_t, uint32_t>>{
             {0x00179118u, 44u}, {0x00179148u, 8u}, {0x0017d228u, 16u}, {0x0017d238u, 8u}, {0x0017d240u, 8u},
             {0x0017d8d8u, 16u}, {0x0017d8e8u, 8u}, {0x0017e290u, 16u}, {0x0017e2a0u, 8u}, {0x0017eab8u, 16u},
             {0x0017eac8u, 8u}, {0x0017f3b8u, 16u}, {0x0017f3c8u, 8u}, {0x00184528u, 16u}, {0x00184538u, 8u},
             {0x00184540u, 40u}, {0x00185138u, 16u}, {0x00185148u, 8u}, {0x00185150u, 28u}, {0x0018a340u, 16u},
             {0x0018a350u, 8u}, {0x0018b630u, 16u}, {0x0018b648u, 8u}, {0x0018bcf0u, 16u}, {0x0018bd00u, 8u},
             {0x0018c180u, 16u}, {0x0018c198u, 8u}, {0x0018c5f8u, 16u}, {0x0018c610u, 8u}, {0x0018ca90u, 16u},
             {0x0018caa8u, 8u}, {0x0018cf08u, 16u}, {0x0018cf20u, 8u}, {0x0018d278u, 16u}, {0x0018d290u, 8u},
             {0x0018d5e8u, 16u}, {0x0018d600u, 8u}, {0x0018d838u, 16u}, {0x0018d850u, 8u}, {0x0018dcd0u, 16u},
             {0x0018dce8u, 8u}, {0x0018df18u, 16u}, {0x0018df30u, 8u}, {0x0018e190u, 20u}, {0x0018e1a8u, 12u},
             {0x0018e370u, 16u}, {0x0018e380u, 8u}, {0x0018e6b8u, 16u}, {0x0018e6c8u, 8u}, {0x0018ea10u, 16u},
             {0x0018ea20u, 8u}, {0x0018ec20u, 8u}, {0x0018ee40u, 8u}, {0x0018f1a0u, 16u}, {0x0018f1b0u, 8u},
             {0x0018f7e0u, 16u}, {0x0018f7f8u, 8u}, {0x0018fa88u, 16u}, {0x0018faa0u, 8u}, {0x0018fef8u, 20u},
             {0x0018ff10u, 8u}, {0x001904e8u, 16u}, {0x001904f8u, 8u}, {0x00192420u, 16u}, {0x00192430u, 8u},
             {0x00192438u, 8u}, {0x00192440u, 44u}, {0x00192720u, 16u}, {0x00192730u, 8u}, {0x00192738u, 8u},
             {0x00192740u, 44u}, {0x00192a20u, 16u}, {0x00192a30u, 8u}, {0x00192a38u, 8u}, {0x00192a40u, 44u},
             {0x00176520u, 16u}, {0x00179b38u, 16u}, {0x0018a898u, 16u}, {0x0018ad18u, 16u}, {0x0018b2a8u, 16u},
             {0x00178618u, 44u}, {0x0018bb38u, 20u}, {0x0018bb50u, 8u}, {0x0018a8a8u, 8u}, {0x0018ad28u, 8u},
             {0x0018b2b8u, 8u}, {0x0018a358u, 8u}, {0x0018e1b8u, 12u}, {0x0018e388u, 8u}, {0x0018e6d0u, 8u}})
        e.interpret(entry, entry + size);
    e.interpret(0x00173ef0, 0x00173f40);   // effBTLSystemGetLength
    // The families' getLength (effBTLSys_*_GetLength), 8 bytes each but the
    // five that ask a cut.
    for (const uint32_t entry : {0x00170150u, 0x001703a8u, 0x00170590u, 0x00170778u, 0x00170960u, 0x00170c00u,
                                 0x00170e00u, 0x00171060u, 0x00171268u, 0x001713d0u, 0x00171578u, 0x00171728u,
                                 0x00171978u, 0x00171c40u, 0x001720f0u, 0x00172590u, 0x00172d18u, 0x001735e0u})
        e.interpret(entry, entry + 8);
    for (const uint32_t entry : {0x00172718u, 0x00173768u, 0x001738f8u, 0x00173a88u, 0x00173c18u})
        e.interpret(entry, entry + 24);
    e.interpret(0x00259bd0, 0x00259c44);   // nbAddKagututiMoon
    e.interpret(0x0027c268, 0x0027c28c);   // nbPanelPressGaugeStart
    e.interpret(0x0027c340, 0x0027c350);   // nbPanelPressGaugeEncountHide
    e.interpret(0x0027d8e0, 0x0027d980);   // nbPanelPressTurnOmit, nbPanelPressTurnStart
    e.interpret(0x001ba1e8, 0x001ba1f4);   // nbCameraCRSetPlayerFormRequest
    e.interpret(0x00289ac8, 0x00289b2c);   // nbInitAutoCommProcess
    e.interpret(0x0024f388, 0x0024f420);   // nbInitUnitProcess
    e.interpret(0x0024cac8, 0x0024cbb4);   // nbInitStageProcess
    e.interpret(0x001b20b8, 0x001b2154);   // nbInitCameraProcess
    e.interpret(0x001b1bd8, 0x001b1c14);   // nbCameraInit
    e.interpret(0x0016c528, 0x0016c5e4);   // nbInitEffectProcess
    e.interpret(0x00259740, 0x00259a30);   // nbSetupBattleUnits, nbSetPlayerStartData
    e.interpret(0x00257eb0, 0x00258048);   // InitActionProcessData, nbInitActionProcess
    e.interpret(0x00282900, 0x00282a28);   // nbInitPanelProcess
    e.interpret(0x0027d868, 0x0027d888);   // nbPanelPressTurnInit
    e.interpret(0x0027c230, 0x0027c268);   // nbPanelPressGaugeInit
    e.interpret(0x0028d8b0, 0x0028d918);   // nbInitSound
    e.interpret(0x002493a8, 0x00249640);   // nbMainProcess_SetDebugFlag (to the next function)
    e.interpret(0x001cda40, 0x001cdb34);   // itfMesMngInitialize
    e.interpret(0x001741a0, 0x001741bc);   // effBTLEncountStart
    e.interpret(0x00290b20, 0x00290bc8);   // the flight model's pack
    e.interpret(0x00101bf0, 0x00101c4c);   // a process's flags set and cleared
    e.hook(0x00100f78, [=](ee::Cpu& c) {
        fw_mes_log(155, static_cast<uint32_t>(a(c, 0)) ^ static_cast<uint32_t>(a(c, 3)) << 8, static_cast<uint32_t>(a(c, 1)) ^ static_cast<uint32_t>(a(c, 2)) << 20);
        return uint64_t{0};
    });
    e.hook(0x00290c30, [=](ee::Cpu& c) { fw_mes_log(156, static_cast<uint32_t>(a(c, 0)), 0); return uint64_t{fw_hash(156, 0, 0) % 4 == 0 ? 0u : 0x1000u + fw_hash(157, 0, 0) % 0x100}; });
    e.interpret(0x0021f838, 0x0021f898);   // rstCalcLevelFromExp
    e.interpret(0x0024be88, 0x0024bff0);   // ShutdownProcess, ClearStage
    e.interpret(0x0024c1d0, 0x0024c458);   // nbResultProcess2, nbResultProcess1, nbResultShutdown, nbInitResultProcess
    // ... its callees not yet rewritten: the active scene, the next field's
    // pack loading (logged, with answers by hash), and its drawing.
    e.hook(0x00127378, [](ee::Cpu&) { fw_mes_log(149, 0, 0); return uint64_t{fw_hash(149, 0, 0) % 3}; });
    // The next area's loader (field/next_area.hpp) and the active scene.
    e.interpret(0x0010e548, 0x0010e564);   // dds3GetActiveScene
    e.interpret(0x00127368, 0x00127378);   // the area to load next
    e.interpret(0x00127510, 0x001279e8);   // its release, poll, status, readiness, the three parts and the shared pack's name
    e.interpret(0x00127b70, 0x00127bc8);   // the shared pack's release
    e.interpret(0x00128408, 0x0012846c);   // the area's folder
    e.hook(0x00296b08, [=](ee::Cpu& c) { return ps2ResourcePacCheckEnd(a(c, 0)); });
    e.hook(0x002a9650, [=](ee::Cpu& c) { ps2MemoryHandleDeferredRelease(a(c, 0)); return uint64_t{0}; });
    e.hook(0x0024b010, [=](ee::Cpu& c) { fw_mes_log(152, static_cast<uint32_t>(a(c, 0)), 0); return uint64_t{0}; });
    e.hook(0x0024cbb8, [=](ee::Cpu& c) { fw_mes_log(145, static_cast<uint32_t>(a(c, 0)), 0); return uint64_t{0}; });  // after the result
    e.hook(0x001e1770, [](ee::Cpu&) { fw_mes_log(146, 0, 0); return uint64_t{0}; });          // the stage's release
    e.interpret(0x0021f898, 0x0021f8d0);   // rstCalcExpFromLevel
    e.interpret(0x0026a840, 0x0026a8a0);   // nbGetKakutokuExp, nbGetKakutokuMaka
    e.interpret(0x0026c390, 0x0026cd80);   // the talk process
    e.hook(0x00279c58, [](ee::Cpu&) { nbPanelAutoHide(); return uint64_t{0}; });
    e.hook(0x00281e28, [](ee::Cpu&) { ps2BattlePanelHideHookA(); return uint64_t{0}; });
    e.hook(0x001b18c8, [=](ee::Cpu& c) { nbCameraScriptSet1Shot(a(c, 0)); return uint64_t{0}; });
    e.hook(0x001b1928, [=](ee::Cpu& c) { nbCameraScriptSetBougai(a(c, 0)); return uint64_t{0}; });
    e.interpret(0x00288a58, 0x00288d80);   // the battle script commands (nbCommand_BTL_*)
    e.interpret(0x0026a8a0, 0x0026b1e0);   // the talks' helpers (nbNegoProcess)
    e.interpret(0x0026ba28, 0x0026bf00);
    e.interpret(0x0026b1e0, 0x0026b3f8);   // nbSetAllHojoSkillWork, nbGetHojoSkillWorkCnt
    e.interpret(0x0026b3f8, 0x0026ba28);   // nbSearchHojoSkillWork, nbGetQuestionType
    e.hook(0x0016b0f0, [=](ee::Cpu& c) { effBTLCutDraw(a(c, 0)); return uint64_t{0}; });
    e.interpret(0x001740a0, 0x001740b4);   // effBTLSystemCut1Draw
    e.hook(0x00105048, [=](ee::Cpu& c) { dds3FadeIn2(a(c, 0)); return uint64_t{0}; });
    e.hook(0x001e3700, [=](ee::Cpu& c) { nbUnitSetColor(a(c, 0), a(c, 1), a(c, 2)); return uint64_t{0}; });
    e.hook(0x001e37e8, [=](ee::Cpu& c) { nbUnitSetAlpha(a(c, 0), a(c, 1), a(c, 2)); return uint64_t{0}; });
    e.hook(0x001740b8, [=](ee::Cpu& c) { effBTLSystemCutDelete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00173d78, [=](ee::Cpu& c) { effBTLPartDelete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00198298, [=](ee::Cpu& c) { effPCPBossONGYDelete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00198900, [=](ee::Cpu& c) { effPCPBossONGY2Delete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x001990f0, [=](ee::Cpu& c) { effPCPBossBUNSINDelete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00199bc8, [=](ee::Cpu& c) { effPCPBossBUNSIN2Delete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x00279c30, [](ee::Cpu&) { nbPanelAllShow(); return uint64_t{0}; });
    e.hook(0x0016b7a8, [=](ee::Cpu& c) { effBTLSkillStart(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x0016b850, [](ee::Cpu&) { effBTLSkillEnd(); return uint64_t{0}; });
    e.hook(0x001748a0, [=](ee::Cpu& c) { return effBTLBedName(a(c, 0)); });
    e.hook(0x0016a9c0, [=](ee::Cpu& c) { return effBTLLoad(a(c, 0)); });
    e.hook(0x002c1c20, [=](ee::Cpu& c) { return ps2SoundBankStatus(a(c, 0)); });
    e.hook(0x002c20f0, [=](ee::Cpu& c) { return ps2SoundSelectOutput_002C20F0(a(c, 0)); });
    e.hook(0x002c1e70, [=](ee::Cpu& c) { return ps2SoundSelectChannel_002C1E70(a(c, 0)); });
    e.hook(0x002a8fe8, [=](ee::Cpu& c) { return fw_handle_size(a(c, 0)); });
    e.hook(0x001741c0, [](ee::Cpu&) { return fw_enc_effect(1); });
    e.hook(0x001b33f8, [](ee::Cpu&) { return fw_enc_camera_done(); });
    e.hook(0x0024e1e0, [=](ee::Cpu& c) { return fw_load_unit_group(a(c, 0), a(c, 1), a(c, 2)); });
    e.hook(0x0024e2e0, [=](ee::Cpu& c) { return fw_unit_group_loading(a(c, 0)); });
    e.hook(0x00110138, [=](ee::Cpu& c) { dds3ObjectBaseOnFlag(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x00110168, [=](ee::Cpu& c) { dds3ObjectBaseOffFlag(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x0010dea8, [=](ee::Cpu& c) { dds3SetPosPoseSet(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.interpret(0x00289b30, 0x00289f50);   // nbFormation: the models shown and hidden
    e.interpret(0x0028a0e8, 0x0028a158);   // ... nbSetFormPos
    e.interpret(0x0028a200, 0x0028a340);   // ... nbSetFormPosRot, the resets, the distances
    e.hook(0x0012c148, [](ee::Cpu&) { return fw_fade_query(); });
    e.hook(0x0012c150, [=](ee::Cpu& c) { return fw_fade_set(a(c, 0)); });
    e.interpret(0x00100410, 0x00100418);   // the kernel's frame counter
    e.hook(0x002c1db0, [=](ee::Cpu& c) { ps2SoundSetBankSource(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x00296a68, [=](ee::Cpu& c) { return fileRequest(a(c, 0)); });
    e.hook(0x00296ac8, [=](ee::Cpu& c) { return fileCheckEnd(a(c, 0)); });
    e.hook(0x00296aa8, [=](ee::Cpu& c) { return fileGetMemHandle(a(c, 0)); });
    e.hook(0x00296ab8, [=](ee::Cpu& c) { return fileGetLoadSize(a(c, 0)); });
    e.hook(0x002966c0, [=](ee::Cpu& c) { ps2ResourceRequestRelease(a(c, 0)); return uint64_t{0}; });
    e.hook(0x002617a8, [=](ee::Cpu& c) {
        nbMakeSkillEffectPacket(a(c, 0), a(c, 1), a(c, 2), a(c, 3), a(c, 4), a(c, 5), a(c, 6));
        return uint64_t{0};
    });
    e.hook(0x002648c0, [=](ee::Cpu& c) { nbMakeTargetPacket(a(c, 0), a(c, 1), a(c, 2), a(c, 3), a(c, 4), c.f[12]); return uint64_t{0}; });
    e.hook(0x0016b8a8, [=](ee::Cpu& c) { effBTLSkillSetFormationInfo(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x0026ccf0, [=](ee::Cpu& c) { nbInitNegoProcess(a(c, 0), a(c, 1), a(c, 2), a(c, 3), a(c, 4)); return uint64_t{0}; });
    e.hook(0x0027c2c0, [](ee::Cpu&) { nbPanelPressGaugeShow(); return uint64_t{0}; });
    e.hook(0x0027fa98, [](ee::Cpu&) { nbPanelStockSelectInit(); return uint64_t{0}; });
    e.hook(0x0027fa78, [](ee::Cpu&) { nbPanelStockEnd(); return uint64_t{0}; });
    e.hook(0x0022e168, [=](ee::Cpu& c) { return static_cast<uint64_t>(static_cast<int64_t>(cmpRemoveDevilEx(static_cast<uint16_t>(a(c, 0))))); });
    e.hook(0x002469a0, [](ee::Cpu&) { return nbGetMainProcessData(); });
    // The unit lookups, with what the real ones leave in a3 (Hardtype's
    // SetCommList reads it): GetUnitWork the party flag's bit 2; for a battle
    // slot nbGetPartyFromFormindex the battle's record, and
    // GetUnitWorkFromFormindex then GetUnitWork's for an active party entry.
    auto partyFlagBit = [](uint64_t party) { return uint64_t{*nocturne::guest::table<uint16_t>(static_cast<uint32_t>(party)) & 2u}; };
    e.hook(0x002469c0, [=](ee::Cpu& c) {
        const uint64_t party = a(c, 1);
        c.r[7] = partyFlagBit(party);
        return nbGetUnitWorkPointer(a(c, 0), party);
    });
    e.hook(0x00246a40, [=](ee::Cpu& c) {
        if (static_cast<int32_t>(a(c, 0)) < 16)
            c.r[7] = nbGetMainProcessData();
        return nbGetPartyFromFormindex(a(c, 0));
    });
    // (and in a0: for a slot past 15 the slot less 16; for a unit in battle
    // the battle's record; else its formation's bit 1; Hardtype reads it)
    e.hook(0x00246ab8, [=](ee::Cpu& c) {
        const int32_t formindex = static_cast<int32_t>(a(c, 0));
        const uint64_t unit = nbGetUnitWorkFromFormindex(a(c, 0));
        if (formindex >= 16) {
            c.r[4] = static_cast<uint64_t>(static_cast<int64_t>(formindex - 16));
        } else {
            const uint64_t main = nbGetMainProcessData();
            c.r[7] = main;
            const uint64_t party = nbGetPartyFromFormindex(a(c, 0));
            if (party && (*nocturne::guest::table<uint16_t>(static_cast<uint32_t>(party)) & 1)) {
                c.r[7] = partyFlagBit(party);
                c.r[4] = main;
            } else {
                const uint32_t forms = *nocturne::guest::table<uint32_t>(static_cast<uint32_t>(main));
                c.r[4] = *nocturne::guest::table<uint32_t>(forms + 0xf0u * static_cast<uint32_t>(formindex) + 0x78) & 1;
            }
        }
        return unit;
    });
    e.hook(0x00101898, [=](ee::Cpu& c) { return dds3SearchProcessName(a(c, 0)); });
    e.hook(0x001040a8, [=](ee::Cpu& c) { dds3PadAct(a(c, 0), a(c, 1), a(c, 2)); return uint64_t{0}; });
    e.hook(0x002a8bd8, [=](ee::Cpu& c) { ps2PoolRelease(static_cast<uint32_t>(a(c, 0))); return uint64_t{0}; });
    // The C library: plain host versions on guest memory.
    auto checked = [](ee::Cpu& c, uint64_t address) -> char* {
        if (static_cast<uint32_t>(address) >= FW_RAM_SIZE) {
            std::fprintf(stderr, "C library call from %08x with address %08x\n", static_cast<uint32_t>(c.r[31]),
                         static_cast<uint32_t>(address));
            std::abort();
        }
        return &at<char>(static_cast<uint32_t>(address));
    };
    e.hook(0x002d5d0c, [=](ee::Cpu& c) { return uint64_t{std::strlen(checked(c, a(c, 0)))}; });
    e.hook(0x002d5ab4, [=](ee::Cpu& c) {   // strcmp: the difference of the first bytes that differ
        const unsigned char* x = reinterpret_cast<const unsigned char*>(checked(c, a(c, 0)));
        const unsigned char* y = reinterpret_cast<const unsigned char*>(checked(c, a(c, 1)));
        while (*x && *x == *y)
            ++x, ++y;
        return static_cast<uint64_t>(static_cast<int64_t>(*x - *y));
    });
    e.hook(0x002d43a4, [=](ee::Cpu& c) {
        std::memcpy(checked(c, a(c, 0)), checked(c, a(c, 1)), static_cast<uint32_t>(a(c, 2)));
        return a(c, 0);
    });
    e.hook(0x002d4558, [=](ee::Cpu& c) {
        std::memset(checked(c, a(c, 0)), static_cast<int>(a(c, 1)), static_cast<uint32_t>(a(c, 2)));
        return a(c, 0);
    });
    e.hook(0x002d5690, [=](ee::Cpu& c) {   // sprintf, as used here: "%d" and the skill's sound file
        const char* format = checked(c, a(c, 1));
        if (std::strcmp(format, "%d") == 0)
            return uint64_t(std::snprintf(checked(c, a(c, 0)), 16, "%d", static_cast<int32_t>(a(c, 2))));
        if (std::strncmp(format, "/fld/", 5) == 0 && std::strcmp(format + 6, "/f%03d/") == 0)   // an area's folder
            return uint64_t(std::snprintf(checked(c, a(c, 0)), 16, format, static_cast<int32_t>(a(c, 2))));
        if (std::strncmp(format, "%sf%03d_", 8) == 0 && std::strcmp(format + std::strlen(format) - 3, ".LB") == 0)   // an area's pack
            return uint64_t(std::snprintf(checked(c, a(c, 0)), 32, format, checked(c, a(c, 2)), static_cast<int32_t>(a(c, 3))));
        if (std::strcmp(format, "/sound/MIDI%04X.SMG") == 0)
            return uint64_t(std::snprintf(checked(c, a(c, 0)), 32, "/sound/MIDI%04X.SMG", static_cast<uint32_t>(a(c, 2))));
        std::abort();
    });
    e.hook(kKuti, [](ee::Cpu&) { nocturneInvokeMessageKutiCallback(version::code(kKuti)); return uint64_t{0}; });
    return e;
}

ee::Interpreter& original()
{
    static ee::Interpreter e = makeOriginal();
    return e;
}

// The guest stack starts zeroed, as the rewrite's local buffers are: the
// original copies a few bytes past a string's end from its stack buffer.
// The interpreter's stack, cleared (below anything host code has staged there).
void clearStack()
{
    const uint32_t top = fw_stack_top();
    std::memset(fw_ram + top - 0x2000, 0, 0x2000 + (top == FW_STACK_TOP ? 0x40u : 0u));
}

uint64_t call(uint32_t entry, std::initializer_list<uint64_t> args, bool /*vm*/ = false,
              std::initializer_list<uint32_t> floatArgs = {})
{
    clearStack();
    return original().call(entry, args, floatArgs);
}

std::vector<uint8_t> readFile(const std::string& path)
{
    std::ifstream f(path, std::ios::binary);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

// The message section of a FlowScript (section type 3).
std::vector<uint8_t> scriptMessages(const std::vector<uint8_t>& script)
{
    if (script.size() < 0x20)
        return {};
    uint32_t count;
    std::memcpy(&count, script.data() + 0x10, 4);
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t s[4];
        std::memcpy(s, script.data() + 0x20 + 16 * i, 16);
        if (s[0] == 3)
            return std::vector<uint8_t>(script.begin() + s[3], script.begin() + s[3] + s[1] * s[2]);
    }
    return {};
}

uint32_t poolString(const char* s)
{
    uint32_t length = static_cast<uint32_t>(std::strlen(s)) + 1;
    uint32_t p = ps2PoolAllocate(static_cast<int32_t>(length));
    std::memcpy(fw_ram + p, s, length);
    return p;
}

} // namespace

uint32_t guestString(const char* s) { return poolString(s); }

uint64_t orig(uint32_t entry, std::initializer_list<uint64_t> args) { return norm(call(version::codeOrDie(entry), args)); }
uint64_t origVm(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> floatArgs)
{
    return norm(call(version::codeOrDie(entry), args, true, floatArgs));
}
uint64_t origVmVoid(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> floatArgs)
{
    call(version::codeOrDie(entry), args, true, floatArgs);
    return 0;
}
uint64_t origVmAt(uint32_t entry, std::initializer_list<uint64_t> args) { return norm(call(entry, args, true)); }
uint64_t origVmVoidAt(uint32_t entry, std::initializer_list<uint64_t> args)
{
    call(entry, args, true);
    return 0;
}
uint64_t origOwn(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> callees)
{
    clearStack();
    std::vector<uint32_t> own{version::codeOrDie(entry)};
    for (uint32_t callee : callees)
        own.push_back(version::codeOrDie(callee));
    return norm(original().call(own[0], args, {}, own));
}
uint32_t origVmFloat() { return original().cpu.f[0]; }
std::array<uint32_t, 4> origVmVector(uint32_t entry, const uint32_t (&vf10)[4], const uint32_t (&vf11)[4])
{
    original().presetVf(10, vf10);
    original().presetVf(11, vf11);
    call(version::codeOrDie(entry), {}, true);
    const ee::Cpu& c = original().cpu;
    return {c.vf[10][0], c.vf[10][1], c.vf[10][2], c.vf[10][3]};
}
uint64_t interpretedCalls() { return ee::Interpreter::calls(); }
uint64_t origVoid(uint32_t entry, std::initializer_list<uint64_t> args) { call(version::codeOrDie(entry), args); return 0; }

const std::vector<std::vector<uint8_t>>& messageTables() { return gTables; }
const std::vector<std::vector<uint8_t>>& scriptFiles() { return gScripts; }

void loadData(const char* elfPath)
{
    std::string root(elfPath);
    root = root.substr(0, root.find_last_of("/\\") + 1) + "dds3/";
    for (const char* name : {"event/e600/e601/scr/e601.bf", "facility/scr/combine/message.bf", "event/e600/e602/scr/e602.bf",
                             "fld/f/f015/f015.bf", "fld/f/f041/f041.bf"}) {
        std::vector<uint8_t> table = scriptMessages(readFile(root + name));
        if (!table.empty() && table.size() <= 0x10000)
            gTables.push_back(std::move(table));
    }
    // The first release has no f041.bf; f001.bf's table also has messages at
    // the help line's indexes (0x42, 0x46).
    if (readFile(root + "fld/f/f041/f041.bf").empty())
        if (std::vector<uint8_t> table = scriptMessages(readFile(root + "fld/f/f001/f001.bf")); !table.empty())
            gTables.push_back(std::move(table));
    for (int i = 0; i < 4; ++i)   // US Maniax's in EngFont/, the JP builds' in font/
        gFonts[i] = readFile(root + "font/EngFont/font" + std::to_string(i) + ".fnt");
    if (gFonts[0].empty())
        for (int i = 0; i < 4; ++i)
            gFonts[i] = readFile(root + "font/font" + std::to_string(i) + ".fnt");
    for (const char* name : {"event/e600/e601/scr/e601.bf", "event/e600/e602/scr/e602.bf", "facility/scr/combine/message.bf"})
        gScripts.push_back(readFile(root + name));
    if (gTables.empty() || gFonts[0].empty())
        std::fprintf(stderr, "no message tables or fonts under %s; interface tests will fail\n", root.c_str());
}

static void putTable(const std::vector<uint8_t>& t, bool relocate)
{
    std::memset(fw_ram + FW_MES_TABLE, 0, 0x10000);
    std::memcpy(fw_ram + FW_MES_TABLE, t.data(), t.size());
    if (relocate) {
        mes::FileHeader& f = at<mes::FileHeader>(FW_MES_TABLE);
        ps2PacRelocatePointers(FW_MES_TABLE + 0x20, FW_MES_TABLE + 0x20, FW_MES_TABLE + f.ofs_addrinfo, f.size_addrinfo);
        f.resolveaddress = 1;
    }
}

void loadTable(Gen& g, bool relocate) { putTable(gTables[g.below(static_cast<uint32_t>(gTables.size()))], relocate); }

void fontWorld(Gen& g)
{
    // Fonts. US Maniax's style 1 shares style 0's file (as its frLoadStyle
    // does); the JP builds' has its own.
    for (int i = 0; i < 4; ++i)
        std::memcpy(fw_ram + kFontBase + kFontOffset[i], gFonts[i].data(), gFonts[i].size());
    std::memset(&fr::style(0), 0, 9 * sizeof(fr::Style));
    fr::BindStyle(0, 0, kFontBase + 1);
#if NOCTURNE_US
    fr::BindStyle(1, 0, kFontBase + 1);
#else
    fr::BindStyle(1, 0, kFontBase + kFontOffset[1] + 1);
#endif
    fr::BindStyle(2, 0, kFontBase + kFontOffset[2] + 1);
    fr::BindStyle(3, 0, kFontBase + kFontOffset[3] + 1);
    if (g.chance(40))
        fr::BindStyle(8, kFontBase + kFontOffset[1], 0);
#if NOCTURNE_US
    for (int i = 0; i < 9; ++i)   // the styles loaded once
        at<int32_t>(0x003261e8 + 4u * static_cast<uint32_t>(i)) = i < 4 && g.chance(80) ? 1 : 0;
#endif

    fr::Settings& s = fr::settings();
    s.result = g.chance(50) ? g.below(8) : 0xffffffffu;
    s.space = static_cast<int8_t>(g.pick<int32_t>({3, 3, 0, 1, 2, -1}));
    s.step = g.chance(70) ? 0x14 : g.range(12, 28);
#if NOCTURNE_US
    s.base_width = g.chance(70) ? 0x14 : g.range(14, 24);
    s.space_width = g.range(0, 4);
#endif
    s.mode = static_cast<uint8_t>(g.chance(50) ? 0x16 : g.below(32));
    s.style = static_cast<uint8_t>(g.below(4));
    at<uint8_t>(version::dataOrDie(0x0054f430)) = 0;   // the empty strings
    at<uint8_t>(version::dataOrDie(0x0054f448)) = 0;

    // Pools and counters (after the styles).
    fr::Tables& tables = fr::tables();
    std::memset(&tables, 0, sizeof tables);
    tables.text_pool.address = fw_address_of(fr::PoolCreate(0x2c, 2000));
    tables.request_pool.address = fw_address_of(fr::PoolCreate(0x30, 400));
    tables.texture_width = 0x200;
    tables.texture_base = 0x1a40 + static_cast<int32_t>(g.below(4));

    // Texture cells: a ring of 400 behind the anchor (cell 0), each with a glyph record.
    constexpr uint32_t kCells = 400;
    const uint32_t cells = ps2PoolAllocate((kCells + 1) * 0x20), glyphs = ps2PoolAllocate((kCells + 1) * 12);
    std::memset(fw_ram + cells, 0, (kCells + 1) * 0x20);
    std::memset(fw_ram + glyphs, 0, (kCells + 1) * 12);
    for (uint32_t k = 0; k <= kCells; ++k) {
        fr::TextureCell& c = at<fr::TextureCell>(cells + 0x20 * k);
        c.index = static_cast<int32_t>(k);
        c.x = static_cast<int32_t>(k % 21) * 24 * 16;
        c.y = static_cast<int32_t>(k / 21) * 24 * 16;
        c.x2 = c.x + 24 * 16;
        c.glyph.address = glyphs + 12 * k;
        c.next.address = cells + 0x20 * (k == kCells ? 0 : k + 1);
        c.prev.address = cells + 0x20 * (k == 0 ? kCells : k - 1);
    }
    fr::TextureCells& tc = at<fr::TextureCells>(version::dataOrDie(0x0056b668));
    std::memset(&tc, 0, sizeof tc);
    tc.free = kCells;
    tc.ring.address = cells;
    tc.count = kCells + 1;

    at<uint32_t>(version::dataOrDie(0x0056bbc4)) = 0;   // the requests to free after each frame
    at<uint32_t>(version::dataOrDie(0x0056bbc4) + 4) = 0;
    at<int32_t>(version::dataOrDie(0x00551b80)) = static_cast<int32_t>(g.below(2));
    at<uint32_t>(version::dataOrDie(0x0054ea20)) = FW_GLOBAL;   // the save data, with the entered names

#if NOCTURNE_US
    at<uint16_t>(0x0054ea00) = static_cast<uint16_t>(g.chance(50) ? 'A' + g.below(26) : 0x8020 + g.below(0x40));

    // {var n} strings.
    static const char* const strings[] = {"123", "Pixie", "B2F", "Jack Frost", "\x81\x40\x81\x41", "R"};
    for (uint32_t i = 0; i < 32; ++i)
        at<uint32_t>(0x0056bbd0 + 4 * i) = g.chance(50) ? poolString(strings[g.below(6)]) : 0;

    // Entered names: letter codes, bitmaps and lengths, 16 letters to a name.
    for (uint32_t bank = 0; bank < 4; ++bank) {
        const uint32_t family = g.range(1, 6), given = g.range(1, 6);   // entered names have letters
        fw_ram[FW_GLOBAL + 0x657c + 2 * bank] = static_cast<uint8_t>(family);
        fw_ram[FW_GLOBAL + 0x657d + 2 * bank] = static_cast<uint8_t>(given);
        for (uint32_t k = 0; k < 16; ++k) {
            fw_ram[FW_GLOBAL + 0x6584 + 32 * bank + 2 * k] = 0;
            fw_ram[FW_GLOBAL + 0x6585 + 32 * bank + 2 * k] = static_cast<uint8_t>('A' + g.below(26));
        }
        for (uint32_t k = 0; k < 0x1200; k += 4)
            at<uint32_t>(FW_GLOBAL + 0x1d7c + bank * 0x1200 + k) = static_cast<uint32_t>(g.rng());
        for (uint32_t k = 0; k < 10; ++k) {
            fw_ram[FW_GLOBAL + 0x6604 + 20 * bank + 2 * k] = 0;
            fw_ram[FW_GLOBAL + 0x6605 + 20 * bank + 2 * k] = static_cast<uint8_t>('a' + g.below(26));
        }
        fw_ram[FW_GLOBAL + 0x6654 + bank] = static_cast<uint8_t>(g.range(0, 10));
        at<int32_t>(0x0056bd50 + 4 * bank) = 0;
    }
    std::memset(fw_ram + 0x0056bc50, 0, 0x100);
#else
    // {var n} strings: 2-byte characters (an odd length reads the end mark).
    static const char* const strings[] = {"\x82\xa0\x82\xa2", "\x83\x73\x83\x4e\x83\x56\x81\x5b", "\x82\x50\x82\x51\x82\x52",
                                          "\x88\xa0", "\x82\xa0x", ""};
    for (uint32_t i = 0; i < 32; ++i)
        at<uint32_t>(version::dataOrDie(0x0056bbd0) + 4 * i) = g.chance(50) ? poolString(strings[g.below(6)]) : 0;

    // Entered names: lengths, letter codes (8 to a name), bitmaps; one name as text.
    for (uint32_t bank = 0; bank < 4; ++bank) {
        const uint32_t family = g.range(1, 4), given = g.range(1, 4);
        fw_ram[FW_GLOBAL + 0x4178 + 2 * bank] = static_cast<uint8_t>(family);
        fw_ram[FW_GLOBAL + 0x4179 + 2 * bank] = static_cast<uint8_t>(given);
        for (uint32_t k = 0; k < 8; ++k) {   // kana, kanji, and codes past 0x83C5
            const uint16_t code = static_cast<uint16_t>(g.pick<int32_t>({0x82a0, 0x8340, 0x83c5, 0x8890, 0x82f0}) + g.below(0x30));
            fw_ram[FW_GLOBAL + 0x4180 + 16 * bank + 2 * k] = static_cast<uint8_t>(code >> 8);
            fw_ram[FW_GLOBAL + 0x4181 + 16 * bank + 2 * k] = static_cast<uint8_t>(code);
        }
        for (uint32_t k = 0; k < 0x900; k += 4)
            at<uint32_t>(FW_GLOBAL + 0x1d78 + bank * 0x900 + k) = static_cast<uint32_t>(g.rng());
        at<int32_t>(version::dataOrDie(0x0056bd50) + 4 * bank) = 0;
    }
    const uint32_t letters = g.range(0, 8);
    fw_ram[FW_GLOBAL + 0x4200] = static_cast<uint8_t>(letters);
    for (uint32_t k = 0; k < letters; ++k) {
        fw_ram[FW_GLOBAL + 0x41c0 + 2 * k] = 0x82;
        fw_ram[FW_GLOBAL + 0x41c1 + 2 * k] = static_cast<uint8_t>(0xa0 + g.below(0x50));
    }
    std::memset(fw_ram + version::dataOrDie(0x0056bc50), 0, 0x80);
#endif
}

uint32_t someText(Gen& g)
{
    const mes::FileHeader& f = at<mes::FileHeader>(FW_MES_TABLE);
    if (f.resolveaddress && f.numtypeheader && g.chance(80)) {
        for (int attempt = 0; attempt < 8; ++attempt) {
            const mes::TypeHeader& h = at<mes::TypeHeader>(FW_MES_TABLE + 0x20 + 8 * g.below(f.numtypeheader));
            if (h.type == 0) {
                const mes::MesHeader& m = at<mes::MesHeader>(h.ptr);
                if (m.page > 0)
                    return m.addr[g.below(static_cast<uint32_t>(m.page))];
            }
        }
    }
    static const char* const pages[] = {
        "\xF2\x08\xFF\xFF\xF2\x07\x07\xFFHello there.\nHow are you?\n\xF1\x04",
        "\xF2\x08\xFF\xFF\xF1\x12I see... \xF2\x0B\x01\xFF \xF2\x0C\x01\xFF!\n\xF1\x04",
        "\xF2\x08\xFF\xFF\xF2\x02\x05\xFF\xF2\x03\x02\xFF\xF2\x02\x01\xFF Macca\n\xF1\x10",
        "\xF2\x08\xFF\xFF\xF2\x0A\x01\xFF and \xF2\x0D\x02\xFF\xF1\x0F...^\xF1\x13x",
        "Line one\nLine two\nLine three",
    };
    return poolString(pages[g.below(5)]);
}

fr::Request* chain(Gen& g, int32_t x, int32_t y)
{
    return fr::MessageRequest(x, y, static_cast<uint8_t>(g.below(4)), static_cast<uint8_t>(g.below(6)),
                              static_cast<uint8_t>(g.below(3)), static_cast<uint8_t>(g.below(140)), someText(g), nullptr);
}

// Whether table `t` has messages at the indexes the caller shows.
bool tableFits(const std::vector<uint8_t>& t, std::initializer_list<int32_t> needed)
{
    const uint32_t count = *reinterpret_cast<const uint32_t*>(t.data() + 0x18);   // numtypeheader
    for (int32_t n : needed)
        if (static_cast<uint32_t>(n) >= count || *reinterpret_cast<const uint32_t*>(t.data() + 0x20 + 8 * n) != 0)
            return false;
    return true;
}

bool messageTableHas(std::initializer_list<int32_t> needed)
{
    for (const std::vector<uint8_t>& t : gTables)
        if (tableFits(t, needed))
            return true;
    return false;
}

HelpWorld helpWorld(Gen& g, std::initializer_list<int32_t> needed)
{
    std::vector<const std::vector<uint8_t>*> tables;
    for (const std::vector<uint8_t>& t : gTables)
        if (tableFits(t, needed))
            tables.push_back(&t);
    if (tables.empty()) {
        std::fprintf(stderr, "no message table has messages at the indexes asked for\n");
        std::exit(1);
    }
    putTable(*tables[g.below(static_cast<uint32_t>(tables.size()))], true);
    fontWorld(g);

    HelpWorld w{};
    const mes::FileHeader& f = at<mes::FileHeader>(FW_MES_TABLE);
    for (uint32_t k = 0; k < f.numtypeheader; ++k)
        if (at<mes::TypeHeader>(FW_MES_TABLE + 0x20 + 8 * k).type == 0)
            w.messages.push_back(static_cast<int32_t>(k));

    // One message window on it.
    mes::Manager& m = mes::manager();
    std::memset(&m, 0, sizeof m);
    nocturne::itf::MiscLinkInit(m.list, addr(m.nodes), 0x80, sizeof(nocturne::itf::LinkNode));
    for (int n = g.range(0, 3); n > 0; --n)   // (not always the first)
        nocturne::itf::MiscLinkTake(m.list);
    nocturne::itf::LinkNode& node = *nocturne::itf::MiscLinkTake(m.list);
    node.instance.address = FW_MES_INSTANCE;
    node.handle = 0x00777000;
    m.count = 1;
    w.id = node.id;
    mes::Instance& p = at<mes::Instance>(FW_MES_INSTANCE);
    std::memset(&p, 0, sizeof p);
    p.pdata.address = FW_MES_TABLE;
    p.z = g.below(0x1000000);
    p.otindex = 0x47;
    if (g.chance(50))
        p.message.pfont.address = addr(chain(g, 0, 0));

    // What the line shows now.
    static const char* const names[] = {"Pixie", "Jack Frost", "Fiend", "Agi"};
    auto someName = [&] { return g.chance(80) ? guestString(names[g.below(4)]) : 0u; };
    nocturne::nb::HelpLine& h = at<nocturne::nb::HelpLine>(FW_HELP);
    h.type = g.pick<int32_t>({0, 1, 1, 2, 4});
    h.text1 = someName();
    h.text2 = someName();
    h.textframe = g.range(0, 60);
    h.textmax = g.range(-1, 45);
    h.texthandle.address = 0;
    h.textwidth = g.range(0, 300);
    h.nextwidth = g.range(0, 300);
    h.textcol = static_cast<uint32_t>(g.rng());
    h.msgid = g.chance(60) ? w.id : -1;   // the window, or none
    h.msgno = w.messages.empty() ? 0 : w.messages[g.below(static_cast<uint32_t>(w.messages.size()))];
    h.reqmsgid = w.id;
    h.reqmsgno = h.msgno;
    h.alpha = g.range(0, 0x80);
    return w;
}

} // namespace difftest::iface
