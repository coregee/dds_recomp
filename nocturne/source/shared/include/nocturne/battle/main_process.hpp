// The battle's main process (original unit: nbMainProcess): its record and
// what it starts. Only what is rewritten so far.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbInitMainProcessData (0x249640): a new battle record (its address): 32
// formations, ten enemy units and the parties allocated and set up, the
// action stack, the sounds, the debug flags and the status line's messages.
uint32_t initMainProcessData();

// nbInitMainProcess (0x249850): the battle begins: its record for the
// encounter (where it came from, its formation, its stage), the passive
// skills' effect, the battle's flags, the "nb_main" process and the moon.
void startMainProcess(int32_t encpackno, int32_t packno, int32_t packindex, int32_t encno,
                      int32_t stageMajor, int32_t stageMinor);
// (0x249320) The process's end: the record and everything it holds freed.
void shutdownMainProcess(uint32_t process);
// 0x2499F8: the battle's end: the process killed, the moon hidden and its
// texture released.
void endMainProcess();

// Checks and flags at the battle's start and between actions.
bool actionProcessesDone(const MainProcessData& main);   // CheckActionProcessEnd (0x247D60): no action process left
void rollInitiative(MainProcessData& main);   // CheckSenseiOrBackAttack (0x247DA0): who goes first, and an ambush
bool formationsIdle(const MainProcessData& main);   // CheckActionRun (0x247E48): no combatant still moving
void setBossFlag(MainProcessData& main);      // SetBattleFlag (0x247E90): the encounter's boss flag

// The queue of actions waiting to run (main.actionstack, actionstackp
// entries), taken from the top.
bool actionInvalid(MainProcessData& main, int32_t index);   // CheckErrorActionStack (0x247F70)
bool popAction(QueuedAction& out);    // nbPopAction (0x248088): the next valid one, dropping invalid ones
bool hasValidAction();                // nbCheckActionStack (0x248138)
void clearActionStack();              // nbClearActionStack (0x2481C8)

// The battle's phases (main.phase). Each step names the next (nbSetNextPhase),
// and entering one runs its entry (nbSetPhase):
//   1 the start (nbSetMaePhase): every process of the battle started
//   2 the encounter: the formation placed, the encounter's opening
//   3 an event, if one is due
//   5 a turn's start (nbSetPressMaePhase): the press icons
//   6 an action's start (nbSetActionMaePhase): the next unit's, unless one is queued
//   7 the action (the queued one's process)
//   9 the check for the battle's end (nbSetChkEndPhase)
//  10 the check for the turn's end (nbSetChkTurnPhase)
//  11 the close (nbSetAtoPhase): ailments cured, recovery skills
//  12 the result (nbSetResultPhase)
//  13 the end (nbSetEndPhase): game over or the level-up screen
//  14 the debug menu
// The battle's end types (main.endtype) it sets: 1 won, 2 lost (the
// Demi-fiend fell), 5 won into a consecutive encounter, 6 lost (no one can
// act); 3 is escaped, and 4 and 9 also show the result.
// nbMainProcess1 (0x248E38): the battle process's step: a phase waits for
// what its entry started, then names the next, entered at the frame's end.
// Returns -1 once the battle is over.
int32_t mainProcessStep(uint32_t process);
void setNextPhase(int32_t phase);     // nbSetNextPhase (0x248C88)
void setPhase(int32_t phase);         // nbSetPhase (0x248CB0)
void enterStart(MainProcessData& main);        // nbSetMaePhase (0x2481E8)
void bringPartyIn(MainProcessData& main);      // nbSetPlayerStartData (0x259908): the party into the first slots
void enterEncounter(MainProcessData& main);    // (0x248278)
void enterEvent(MainProcessData& main);        // (0x2482C0)
void setPressTurns(MainProcessData& main);     // nbSetPressMaePhase (0x248420)
void enterActionStart(MainProcessData& main);  // nbSetActionMaePhase (0x2485F0)
void enterAction(MainProcessData& main);       // (0x248640)
void checkBattleEnd(MainProcessData& main);    // nbSetChkEndPhase (0x248690)
void checkTurnEnd(MainProcessData& main);      // nbSetChkTurnPhase (0x2487D0)
void advanceKagutsuchiMoon();                  // nbAddKagututiMoon (0x259BD0): a round's end in the battle with Kagutsuchi
void enterClose(MainProcessData& main);        // nbSetAtoPhase (0x2482F0)
void enterResult(MainProcessData& main);       // nbSetResultPhase (0x248A40)
void enterEnd(MainProcessData& main);          // nbSetEndPhase (0x248B40)
void enterDebug(MainProcessData& main);        // (0x248C28)

// Its pieces.
void prepareMainProcess(MainProcessData& main);   // (0x246998) does nothing
void loadPassiveEffect(MainProcessData& main);    // (0x249258) HATUDOU.BED, the passive skills' effect
void releasePassiveEffect(MainProcessData& main); // (0x2492B0)
void clearLocalFlags();                           // nbMainProcess_ClearLocalBit: event flags 0xBF0..0xBFF
inline constexpr int32_t kFirstLocalFlag = 0xbf0;

} // namespace nocturne::nb
