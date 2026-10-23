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

// ---- the state ----
int32_t nbGetActionSeq(uint32_t process);   // of an action process, 0 for none
int32_t nbGetPrevActionSeq();               // of the action before the current one, -1 for none
void SetNextActionSeq(ActionProcessData& a, int32_t nextseq);

void SetAction_NON(ActionProcessData& a);
void SetAction_AI(ActionProcessData& a);
int32_t CheckAction_AI(ActionProcessData& a);
void SetAction_AISCR(ActionProcessData& a);
int32_t CheckAction_AISCR(ActionProcessData& a);
int32_t CheckAction_BAD(ActionProcessData& a);
void SetAction_BADWAIT(ActionProcessData& a);
int32_t CheckAction_BADWAIT(ActionProcessData& a);
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
