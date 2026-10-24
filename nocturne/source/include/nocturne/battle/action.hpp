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
enum ActionState : int8_t {
    kActionNone = 0, kActionCommand = 1, kActionAi = 2, kActionAiScript = 3, kActionAilment = 4, kActionTargetSelect = 5,
    kActionStockSelect = 6, kActionReady = 7, kActionSkill = 8, kActionTalk = 9, kActionTalkResult = 10,
    kActionAilmentWait = 11, kActionWait = 12, kActionEscape = 13, kActionReturn = 14, kActionInvisible = 15,
    kActionAftermath = 18, kActionDeathScript = 19, kActionPlayOut = 20, kActionCleanup = 21, kActionEnd = 22,
};

// ---- the time list (by formation index) ----
void clearTimeList(ActionProcessData& a);
void initTimeListHp(ActionProcessData& a);
int32_t timeListHp(ActionProcessData& a, int32_t formindex);
bool timeListDead(ActionProcessData& a, int32_t formindex);
bool otherSideAllDead(ActionProcessData& a, int32_t formindex);
bool addTimeListHp(ActionProcessData& a, int32_t formindex, int32_t add);
bool addTimeListHpAt(ActionProcessData& a, int32_t formindex, int32_t add);
int32_t freeFrame(ActionProcessData& a, int32_t formindex);
int32_t doneFrame(ActionProcessData& a, int32_t formindex);
void overwriteTimeList(ActionProcessData& a, int32_t formindex, int32_t start, int32_t locktime, int32_t endtime);
void setTimeList(ActionProcessData& a, int32_t formindex, int32_t start, int32_t locktime, int32_t endtime);
int32_t lastDoneFrame(ActionProcessData& a);
int32_t lastFreeFrame(ActionProcessData& a);

// ---- an action's results: packets, press turns, messages ----
void fadeInHiddenUnit(ActionProcessData& a, int32_t start);
void queueDeath(ActionProcessData& a, int32_t formindex);
void setPressCost(ActionProcessData& a, ee::Float press);
void setPressResult(ActionProcessData& a, int32_t presstype);
void setHitStopFrame(ActionProcessData& a, int32_t frame);
// The hit order (koukalist): a formation index (-1 ends) and its hits.
struct HitOrderEntry {
    int8_t formindex;
    int8_t count;
};
void hitOrder(ActionProcessData& a, HitOrderEntry* list, uint32_t select, int32_t nskill);        // 32 entries
void queueHitResult(ActionProcessData& a, int32_t koukatype, int32_t nskill, int32_t sformindex, int32_t dformindex, int32_t cnt,
                  int32_t frame, ee::Float koukaritu);
void queueEnemyEscape(ActionProcessData& a, int32_t dformindex, int32_t sframe);
void queueAurora(ActionProcessData& a, int32_t dformindex, int32_t sframe);
void queueExtraPress(ActionProcessData& a, int32_t nskill);
void queueFlareCharge(ActionProcessData& a, int32_t start);
void queueMaccaThrow(ActionProcessData& a, int32_t dformindex, int32_t sframe);
void queueTrafuri(ActionProcessData& a, int32_t dformindex, int32_t sframe);
void queueAnalyze(ActionProcessData& a, int32_t dformindex, int32_t sframe);
int32_t queuePlayerSummon(ActionProcessData& a, int32_t nskill, int32_t sformindex, int32_t dformindex,
                              int32_t sframe);
void queueDodge(ActionProcessData& a, int32_t nskill, int32_t sformindex, int32_t dformindex, int32_t cnt, int32_t frame);
void queueOngyokiFound(ActionProcessData& a, int32_t nskill, int32_t sformindex, int32_t dformindex, int32_t cnt,
                        int32_t frame);
void queueOngyokiClonesVanish(ActionProcessData& a, int32_t dformindex, int32_t frame);
void queueMiss(ActionProcessData& a, int32_t nskill, int32_t sformindex, int32_t dformindex, int32_t cnt, int32_t frame);
void queueDamage(ActionProcessData& a, int32_t hp);

// ---- side events: counters, talks, death scripts (action_events.cpp) ----
void setTarget(ActionProcessData& a);
void enterTargetSelect(ActionProcessData& a);
void targetDemiFiend(ActionProcessData& a);
void targetPartySlot(ActionProcessData& a, int32_t partyindex);
bool checkAhrimanCounter(ActionProcessData& a);
bool checkCounter(ActionProcessData& a, int32_t from, int32_t to);
bool checkLastEnemyTalks(ActionProcessData& a);
bool checkAmbushTalk(ActionProcessData& a);
bool checkBegForLife(ActionProcessData& a);
bool checkAskToJoin(ActionProcessData& a);
void checkDeathScripts(ActionProcessData& a);
bool checkFreeActionAfterEscape(ActionProcessData& a);
void debugEndPressTurns(ActionProcessData& a);
void debugWinBattle(ActionProcessData& a);
void noteActionKind(ActionProcessData& a, int32_t comm, int32_t nskill);

// ---- the state ----
int32_t actionState(uint32_t process);      // of an action process, 0 for none
int32_t previousActionState();              // of the action before the current one, -1 for none
void setNextState(ActionProcessData& a, int32_t nextseq);
void enterState(ActionProcessData& a, int32_t seq);     // enters a state
int32_t runActionProcess(uint32_t process);               // the action process, each frame

void enterNone(ActionProcessData& a);
void enterCommand(ActionProcessData& a);
int32_t updateCommand(ActionProcessData& a);
void enterAilment(ActionProcessData& a);
int32_t updateTargetSelect(ActionProcessData& a);
void enterStockSelect(ActionProcessData& a);
void enterReady(ActionProcessData& a);
int32_t updateReady(ActionProcessData& a);
void enterSkill(ActionProcessData& a);
int32_t updateSkill(ActionProcessData& a);
int32_t updateStockSelect(ActionProcessData& a);
void enterAi(ActionProcessData& a);
int32_t updateAi(ActionProcessData& a);
void enterAiScript(ActionProcessData& a);
int32_t updateAiScript(ActionProcessData& a);
int32_t updateAilment(ActionProcessData& a);
void enterAilmentWait(ActionProcessData& a);
int32_t updateAilmentWait(ActionProcessData& a);
void enterAftermath(ActionProcessData& a);
int32_t updateAftermath(ActionProcessData& a);
void enterDeathScript(ActionProcessData& a);
int32_t updateDeathScript(ActionProcessData& a);
void enterWait(ActionProcessData& a);
int32_t updateWait(ActionProcessData& a);
void enterEscape(ActionProcessData& a);
int32_t updateEscape(ActionProcessData& a);
void enterReturn(ActionProcessData& a);
int32_t updateReturn(ActionProcessData& a);
void enterInvisible(ActionProcessData& a);
int32_t updateInvisible(ActionProcessData& a);
void enterTalk(ActionProcessData& a);
int32_t updateTalk(ActionProcessData& a);
void enterTalkResult(ActionProcessData& a);
int32_t updateTalkResult(ActionProcessData& a);
void enterPlayOut(ActionProcessData& a);
int32_t updatePlayOut(ActionProcessData& a);
void enterCleanup(ActionProcessData& a);
int32_t updateCleanup(ActionProcessData& a);
void enterEnd(ActionProcessData& a);
int32_t updateEnd(ActionProcessData& a);

} // namespace nocturne::nb
