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
int32_t runTableAi();          // nbCommand_AI: the table AI

// BTL_*: a counter for rotating through actions, and two no-ops.
int32_t rotationClear();       // nbCommand_BTL_AI_ROT_CLR
int32_t rotationNext();        // nbCommand_BTL_AI_ROT_NEXT: (counter + 1) mod n
int32_t rotationGet();         // nbCommand_BTL_AI_ROT_GET
int32_t panelOn();             // nbCommand_BTL_PNL_ON
int32_t cameraOrigin();        // nbCommand_BTL_CAM_ORG

} // namespace nocturne::nb::ai::script
