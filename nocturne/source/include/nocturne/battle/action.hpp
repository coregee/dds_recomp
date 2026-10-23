// One unit's action as a process (original unit: nbActionProcess): its
// state machine and the time list that schedules the units it touches.
//
// Names are the HD remaster's.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// The action's states (the table of SetAction_* / CheckAction_* pairs at
// 0x3FA7C0). Each pair's code follows the HD remaster's order of the
// states, and what the pairs do confirms it; 16, 17 and 23 are unused.
enum ActionSeq : int8_t {
    kActionNon = 0, kActionComm = 1, kActionAi = 2, kActionAiScript = 3, kActionBad = 4, kActionTarSel = 5,
    kActionStkSel = 6, kActionReady = 7, kActionSkill = 8, kActionNego = 9, kActionNegoResult = 10,
    kActionBadWait = 11, kActionWait = 12, kActionEscape = 13, kActionReturn = 14, kActionInvisible = 15,
    kActionCheck1 = 18, kActionDeadScript = 19, kActionCheck3 = 20, kActionAto = 21, kActionEnd = 22,
};

// ---- the time list (by formation index) ----
void ClearTimeList(ActionProcessData& a);
void SetHpForTimeList(ActionProcessData& a);
int32_t GetTimeListHp(ActionProcessData& a, int32_t formindex);
bool CheckTimeListDead(ActionProcessData& a, int32_t formindex);
bool CheckTimeListDeadEnemyParty(ActionProcessData& a, int32_t formindex);
bool nbAddTimeListHp(ActionProcessData& a, int32_t formindex, int32_t add);
bool AddTimeListHp(ActionProcessData& a, int32_t formindex, int32_t add);
int32_t GetUnlockTime(ActionProcessData& a, int32_t formindex);
int32_t GetEndTime(ActionProcessData& a, int32_t formindex);
void OverwriteTimeList(ActionProcessData& a, int32_t formindex, int32_t start, int32_t locktime, int32_t endtime);
void SetTimeList(ActionProcessData& a, int32_t formindex, int32_t start, int32_t locktime, int32_t endtime);
int32_t GetAllEndTime(ActionProcessData& a);
int32_t GetAllUnlockTime(ActionProcessData& a);

// ---- an action's results: packets, press turns, messages ----
void UnitKyoseiDisp(ActionProcessData& a, int32_t start);
void SetDeadPacket(ActionProcessData& a, int32_t formindex);
void SetPress(ActionProcessData& a, ee::Float press);
void SetNewPress(ActionProcessData& a, int32_t presstype);
void SetHitStopFrame(ActionProcessData& a, int32_t frame);
void SetEnemyEscapePacket(ActionProcessData& a, int32_t dformindex, int32_t sframe);
void SetAuroraPacket(ActionProcessData& a, int32_t dformindex, int32_t sframe);
void SetAddPressPacket(ActionProcessData& a, int32_t nskill);
void SetAddFlareChargePacket(ActionProcessData& a, int32_t start);
void SetMakaPacket(ActionProcessData& a, int32_t dformindex, int32_t sframe);
void SetTorafuPacket(ActionProcessData& a, int32_t dformindex, int32_t sframe);
void SetAnalyzePacket(ActionProcessData& a, int32_t dformindex, int32_t sframe);
int32_t SetPlayerSummonPacket(ActionProcessData& a, int32_t nskill, int32_t sformindex, int32_t dformindex,
                              int32_t sframe);
void SetSakePacket(ActionProcessData& a, int32_t nskill, int32_t sformindex, int32_t dformindex, int32_t cnt, int32_t frame);
void SetOngShadowPacket(ActionProcessData& a, int32_t nskill, int32_t sformindex, int32_t dformindex, int32_t cnt,
                        int32_t frame);
void SetOngShadowPacket2(ActionProcessData& a, int32_t dformindex, int32_t frame);
void SetMissPacket(ActionProcessData& a, int32_t nskill, int32_t sformindex, int32_t dformindex, int32_t cnt, int32_t frame);
void SetDamagePacket(ActionProcessData& a, int32_t hp);

// ---- side events: counters, talks, death scripts (action_events.cpp) ----
void SetTarget(ActionProcessData& a);
void SetAction_TARSEL(ActionProcessData& a);
void SetTargetPlayer(ActionProcessData& a);
void SetTargetParty(ActionProcessData& a, int32_t partyindex);
bool CheckArrCounter(ActionProcessData& a);
bool CheckCounter(ActionProcessData& a, int32_t from, int32_t to);
bool CheckMukanNego(ActionProcessData& a);
bool CheckSenseiNego(ActionProcessData& a);
bool CheckInotiNego(ActionProcessData& a);
bool CheckBinjoNego(ActionProcessData& a);
void CheckDeadScript(ActionProcessData& a);
bool CheckKoketaNego(ActionProcessData& a);
void KyouseiPress(ActionProcessData& a);
void DokodemoPoa(ActionProcessData& a);
void SetNowActionStat(ActionProcessData& a, int32_t comm, int32_t nskill);

// ---- the state ----
int32_t nbGetActionSeq(uint32_t process);   // of an action process, 0 for none
int32_t nbGetPrevActionSeq();               // of the action before the current one, -1 for none
void SetNextActionSeq(ActionProcessData& a, int32_t nextseq);
void SetActionSeq(ActionProcessData& a, int32_t seq);   // enters a state
int32_t nbActionProcess1(uint32_t process);               // the action process, each frame

void SetAction_NON(ActionProcessData& a);
void SetAction_AI(ActionProcessData& a);
int32_t CheckAction_AI(ActionProcessData& a);
void SetAction_AISCR(ActionProcessData& a);
int32_t CheckAction_AISCR(ActionProcessData& a);
int32_t CheckAction_BAD(ActionProcessData& a);
void SetAction_BADWAIT(ActionProcessData& a);
int32_t CheckAction_BADWAIT(ActionProcessData& a);
void SetAction_CHECK1(ActionProcessData& a);
int32_t CheckAction_CHECK1(ActionProcessData& a);
void SetAction_DEADSCRIPT(ActionProcessData& a);
int32_t CheckAction_DEADSCRIPT(ActionProcessData& a);
void SetAction_WAIT(ActionProcessData& a);
int32_t CheckAction_WAIT(ActionProcessData& a);
void SetAction_ESCAPE(ActionProcessData& a);
int32_t CheckAction_ESCAPE(ActionProcessData& a);
void SetAction_RETURN(ActionProcessData& a);
int32_t CheckAction_RETURN(ActionProcessData& a);
void SetAction_INVISIBLE(ActionProcessData& a);
int32_t CheckAction_INVISIBLE(ActionProcessData& a);
int32_t CheckAction_NEGO(ActionProcessData& a);
int32_t CheckAction_NEGORESULT(ActionProcessData& a);
void SetAction_CHECK3(ActionProcessData& a);
int32_t CheckAction_CHECK3(ActionProcessData& a);
void SetAction_ATO(ActionProcessData& a);
int32_t CheckAction_ATO(ActionProcessData& a);
void SetAction_END(ActionProcessData& a);
int32_t CheckAction_END(ActionProcessData& a);

} // namespace nocturne::nb
