// Script commands for AI scripts (original unit: nbAiScript).
//
// Devils with DevilAI::scriptid run a flowscript instead of the table AI.
// These are the commands it calls; the script's data is the acting unit's
// ActionProcessData. Each command returns 1 (done). Condition commands
// return their result to the script.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb::ai::script {

// Starts an AI script procedure for the action (nbInitAiScript).
void start(ActionProcessData& act, int32_t procedure);

void checkCondition(uint32_t condition);   // nbAiScriptChkJoken

// AI_CHK_*: conditions (see ai.hpp), parameter from the script.
int32_t checkOwnHp();          // nbCommand_AI_CHK_MYHP
int32_t checkOwnMp();          // nbCommand_AI_CHK_MYMP
int32_t checkAllyHp();         // nbCommand_AI_CHK_FRHP
int32_t checkDamageCount();    // nbCommand_AI_CHK_DMGCNT
int32_t checkAllyCount();      // nbCommand_AI_CHK_FRCNT
int32_t checkEnemyCount();     // nbCommand_AI_CHK_ENCNT
int32_t checkOwnAilment();     // nbCommand_AI_CHK_MYBAD
int32_t checkAllyAilment();    // nbCommand_AI_CHK_FRBAD
int32_t checkEnemyAilment();   // nbCommand_AI_CHK_ENBAD
int32_t checkAllEnemiesAilment(); // nbCommand_AI_CHK_ENALLBAD
int32_t checkEnemyDevil();     // nbCommand_AI_CHK_ENID
int32_t checkAllyDevil();      // nbCommand_AI_CHK_FRID
int32_t checkEnemyBuff();      // nbCommand_AI_CHK_ENHOJO
int32_t checkAllyBuff();       // nbCommand_AI_CHK_FRHOJO
int32_t checkEnemyBuffLimit(); // nbCommand_AI_CHK_ENHOJOMAX
int32_t checkAllyBuffLimit();  // nbCommand_AI_CHK_FRHOJOMAX
int32_t checkBackAttack();     // nbCommand_AI_CHK_BA
int32_t checkEnemyLight();     // nbCommand_AI_CHK_ENLIGHT
int32_t checkEnemyDark();      // nbCommand_AI_CHK_ENDARK
int32_t checkFocus();          // nbCommand_AI_CHK_POW
int32_t checkPlayerLevel();    // nbCommand_AI_CHK_PLV
int32_t checkPartyLevel();     // nbCommand_AI_CHK_PPARTYLV
int32_t checkExpelWeakness();  // nbCommand_AI_CHK_ENHAMAMHK
int32_t checkCannotAfford();   // nbCommand_AI_CHK_SKILLNOMP
int32_t checkEscape();         // nbCommand_AI_CHK_ESCAPE: may the enemies flee

// AI_GET_*: values for the script.
int32_t getTurn();             // nbCommand_AI_GET_TURN
int32_t getPressCount();       // nbCommand_AI_GET_PRESSKOUDO (buff counter 18)
int32_t getOwnLevel();         // nbCommand_AI_GET_MYLV
int32_t getOwnAffinityRow();   // nbCommand_AI_GET_MYAISYO
int32_t getMoonPhase();        // nbCommand_AI_GET_FUREA: Kagutsuchi phase (sixteenths / 2)

// AI_ACT_* / AI_TAR_*: choose the action and targets.
int32_t actAttack();           // nbCommand_AI_ACT_ATTACK
int32_t actEscape();           // nbCommand_AI_ACT_ESCAPE
int32_t actSkill();            // nbCommand_AI_ACT_SKILL
int32_t actSummon();           // nbCommand_AI_ACT_SUMMON: skill, devil
int32_t setCritical();         // nbCommand_AI_SET_CRITICAL: next hit is critical
int32_t targetByAi();          // nbCommand_AI_TAR_AI
int32_t actWait();             // nbCommand_AI_ACT_WAIT: the unit passes
// AI_TAR_*: the targets by one rule (the AI's selectors, nbSetAiTarget)
int32_t targetLowestHp();      // nbCommand_AI_TAR_LIFEMIN
int32_t targetLowestLevelNotFlying(); // nbCommand_AI_TAR_BAARLV
int32_t targetLowestLevel();   // nbCommand_AI_TAR_LVMIN
int32_t targetAilment();       // nbCommand_AI_TAR_BAD (argument: the ailment)
int32_t targetDevil();         // nbCommand_AI_TAR_ID (argument: the devil)
int32_t targetLight();         // nbCommand_AI_TAR_LIGHT
int32_t targetDark();          // nbCommand_AI_TAR_DARK
int32_t targetDemiFiend();     // nbCommand_AI_TAR_PLAYER
int32_t targetAll();           // nbCommand_AI_TAR_RND
int32_t targetByCondition();   // nbCommand_AI_TAR_JOKEN: those the last AI_CHK_* matched
int32_t runTableAi();          // nbCommand_AI: the table AI

// BTL_*: a counter for rotating through actions, and two no-ops.
int32_t rotationClear();       // nbCommand_BTL_AI_ROT_CLR
int32_t rotationNext();        // nbCommand_BTL_AI_ROT_NEXT: (counter + 1) mod n
int32_t rotationGet();         // nbCommand_BTL_AI_ROT_GET
int32_t panelOn();             // nbCommand_BTL_PNL_ON
int32_t panelOff();            // nbCommand_BTL_PNL_OFF
int32_t startEvent();          // nbCommand_BTL_EVENT (argument: the event)
int32_t pressTalk();           // nbCommand_BTL_PRESS: the unit talks to press for more
int32_t joinTalk();            // nbCommand_BTL_NAKAMA: the unit talks to join
int32_t leaveTalk();           // nbCommand_BTL_TAIKYO: the unit leaves (talk result 2)
int32_t allLeaveTalk();        // nbCommand_BTL_ALLTAIKYO: the enemies all leave (6)
int32_t showPlayerFormations(); // nbCommand_BTL_FORM_PLY_ON: the player's side only
int32_t cameraTwoShot();       // nbCommand_BTL_CAM_2SHOT: does nothing on the PS2
int32_t showAllFormations();   // nbCommand_BTL_FORM_ALL_ON
int32_t showEnemyFormations(); // nbCommand_BTL_FORM_ENE_ON: the enemies only
int32_t lockAi();              // nbCommand_BTL_AI_CHANGE_OFF: no AI changes (stat 0x40000)
int32_t unlockAi();            // nbCommand_BTL_AI_CHANGE_ON
int32_t cameraOneShot();       // nbCommand_BTL_CAM_1SHOT: a camera shot on the unit
int32_t cameraObstruct();      // nbCommand_BTL_CAM_BOUGAI
int32_t cameraOrigin();        // nbCommand_BTL_CAM_ORG

} // namespace nocturne::nb::ai::script
