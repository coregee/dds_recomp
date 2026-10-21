#ifndef NOCTURNE_BATTLE_AI_ACTIONS_H
#define NOCTURNE_BATTLE_AI_ACTIONS_H
#include <stdint.h>
uint64_t nbCommand_AI_ACT_ATTACK(void);
uint64_t nbCommand_AI_ACT_ESCAPE(void);
uint64_t nbCommand_AI_ACT_SKILL(void);
uint64_t nbCommand_AI_SET_CRITICAL(void);
void nbSetNormalSkill0(uint64_t unit);
uint64_t nbGetSelectBit(uint64_t main);
uint64_t nbCommand_BTL_AI_ROT_CLR(void);
uint64_t nbCommand_BTL_AI_ROT_NEXT(void);
uint64_t nbCommand_BTL_AI_ROT_GET(void);
uint64_t nbCommand_BTL_PNL_ON(void);
uint64_t nbCommand_BTL_CAM_ORG(void);
void *nocturneResolveBattleAiActionsAddress(uint32_t address);
#endif
