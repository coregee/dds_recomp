// Enemy AI (original unit: nbAi).
//
// Each devil has a datDevilAI record (dat::devilAI): three checks, each two
// conditions and an action table; the first check whose conditions hold picks
// its table (else table 0). An action is drawn from the table by weight, set
// as the unit's command, and given targets; an action that can't be paid for
// or finds no target is struck off and another is drawn. Devils with an AI
// script run it instead; the script uses the same pieces (ai_script.cpp).
//
// Conditions are (type << 16) | parameter. They also pick targets: a
// condition that holds marks the matching combatants in
// ActionProcessData::aiselect (one bit per formation index), which the
// "condition" target selector then uses. "Enemies" here are the player's
// side (formations 0..3) and "allies" the AI's (4..13).
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb::ai {

// ---- Conditions (Chk_*) ------------------------------------------------------------

bool ownHpAtMost(ActionProcessData& act, int32_t percent);          // nbAiChkMyHp (1)
bool ownMpAtMost(ActionProcessData& act, int32_t mp);               // nbAiChkMyMp (24)
bool allyHpAtMost(ActionProcessData& act, int32_t percent);         // nbAiChkFrHp (2)
bool damageCountAtLeast(ActionProcessData& act, int32_t count);     // nbAiChkDmgCnt (3)
bool checkedAtLeast(ActionProcessData& act, int32_t count);         // nbAiChkChkCnt (4, 21): counts each check
bool allyCountAtMost(ActionProcessData& act, int32_t count);        // nbAiChkFrCnt (5)
bool enemyCountAtMost(ActionProcessData& act, int32_t count);       // nbAiChkEnCnt (6)
bool ownAilment(ActionProcessData& act, int32_t ailment);           // nbAiChkMyBad (7)
bool allyAilment(ActionProcessData& act, int32_t ailment);          // nbAiChkFrBad (8)
bool enemyAilment(ActionProcessData& act, int32_t ailment);         // nbAiChkEnBad (9)
bool allEnemiesAilment(ActionProcessData& act, int32_t ailment);    // nbAiChkEnAllBad (10)
bool enemyIsDevil(ActionProcessData& act, int32_t devil);           // nbAiChkEnId (11)
bool allyIsDevil(ActionProcessData& act, int32_t devil);            // nbAiChkFrId (12)
// ChkAiHojo: buff codes 0..9 are -kaja (even) / -nda (odd) on counters
// 4..8; 11..17 counters 9..15 set. ChkAiHojoMax: at the limit.
bool hasBuff(int32_t formindex, int32_t code);                      // nbAiChkHojo
bool buffAtLimit(int32_t formindex, int32_t code, uint32_t callerKey);   // nbAiChkHojoMax (buffMax's key)
bool enemyBuff(ActionProcessData& act, int32_t code);               // nbAiChkEnHojo (13)
bool allyBuff(ActionProcessData& act, int32_t code);                // nbAiChkFrHojo (14)
bool enemyBuffAtLimit(ActionProcessData& act, int32_t code);        // nbAiChkEnHojoMax (25)
bool allyBuffAtLimit(ActionProcessData& act, int32_t code);         // nbAiChkFrHojoMax (26)
bool backAttack(ActionProcessData& act, int32_t);                   // nbAiChkBa (15)
bool enemiesStruckFirst(ActionProcessData& act, int32_t);           // nbAiChkSensei (23)
bool enemyIsLight(ActionProcessData& act, int32_t);                 // nbAiChkEnLight (16)
bool enemyIsDark(ActionProcessData& act, int32_t);                  // nbAiChkEnDark (17)
bool ownFocus(ActionProcessData& act, int32_t);                     // nbAiChkPow (18)
bool playerLevelAtLeast(ActionProcessData& act, int32_t level);     // nbAiChkPlv (19)
bool partyLevelAtLeast(ActionProcessData& act, int32_t level);      // nbAiChkPPartyLv (20)
bool turnAtLeast(ActionProcessData& act, int32_t turn);             // nbAiChkTurn (22)
bool enemyNotImmuneToExpel(ActionProcessData& act, int32_t);        // nbAiChkEnHamamHk (27)
bool cannotAfford(ActionProcessData& act, int32_t skill);           // nbAiChkSkillNoMp (28)
// nbAiChkJoken: a condition word; 0 always holds. A condition that holds
// narrows the targets an earlier one picked.
bool condition(ActionProcessData& act, uint32_t condition);

// [version] Where versions differ (source/<version>/src/battle/ai.cpp):
bool versionCondition(int32_t type, int32_t n, bool& holds);   // a condition type of the version's own (false: none)
uint32_t& selectionAfterCondition(ActionProcessData& act, int32_t type);   // what a holding condition narrows
void clearSelectionForCheck(ActionProcessData& act, int32_t index);        // nbAiAiChk's start
int32_t targetedAction(const ActionProcessData& act, int32_t action);      // nbRunAiSub: whose targets it takes

// ---- Choosing an action ------------------------------------------------------------

bool check(ActionProcessData& act, int32_t index);                  // nbAiAiChk: AI check 0..2
int32_t drawAction(ActionProcessData& act, uint32_t table);         // nbAiGetKoudou: -1 if none left
void setAction(ActionProcessData& act, uint32_t table, int32_t action); // nbAiSetKoudou
bool costBlocks(ActionProcessData& act);                            // nbAiChkCost
// nbAiChkClose: true to go on to targets (usable, or the AI level ignores cost).
bool canProceed(ActionProcessData& act);
int32_t runTable(ActionProcessData& act, uint32_t table);           // nbRunAiSub
int32_t run(ActionProcessData& act);                                // nbRunAi

// ---- Choosing targets --------------------------------------------------------------
// The filters mark FormationStat::Selected on Selectable slots.

void selectLowestHp(ActionProcessData& act);                        // nbAiSelLifeMin
void selectLowestLevelNotFlying(ActionProcessData& act);            // nbAiSelBaarLv
void selectLowestLevel(ActionProcessData& act);                     // nbAiSelLvMin
void selectAilment(ActionProcessData& act, int32_t ailment);        // nbAiSelBad
void selectDevil(ActionProcessData& act, int32_t devil);            // nbAiSelId
void selectLight(ActionProcessData& act);                           // nbAiSelLight
void selectDark(ActionProcessData& act);                            // nbAiSelDark
void selectDemiFiend(ActionProcessData& act);                       // nbAiSelPlayer
void selectByCondition(ActionProcessData& act);                     // nbAiSelJoken: the conditions' picks
void selectAll(ActionProcessData& act);                             // nbAiSelRnd
// nbAiSelAi: by the devil's AI level: anyone (0), the best estimated effect
// (1), or the best among those not immune (2). -1 if none qualifies.
int32_t selectBest(ActionProcessData& act, int32_t unused, bool group);
int32_t selectSingleTarget(ActionProcessData& act, int32_t selector, int32_t parameter); // nbSetSingleTarget2
int32_t selectGroupTarget(ActionProcessData& act, int32_t selector, int32_t parameter);  // nbSetGroupTarget2
// nbSetAiTarget: 0 on success; otherwise the unit passes (command 3).
int32_t selectTargets(ActionProcessData& act, int32_t selector, int32_t parameter);
bool prepareSummonSlots(MainProcessData& main, int32_t devil);      // nbSetEnemySummonFormation
void prepareAllySummonSlot(MainProcessData& main);                  // nbSetPlayerSummonFormation
uint32_t selectedBits(const MainProcessData& main);                 // nbGetSelectBit

// nbSetNormalSkill0: rewrite the normal attack's data (skill 0) for this
// unit: element, hit count, Attack All. Also for skills 0xA4..0xA7.
void setNormalAttack(UnitWork& unit);

} // namespace nocturne::nb::ai
