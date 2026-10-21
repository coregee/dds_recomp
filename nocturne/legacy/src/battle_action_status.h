#ifndef NOCTURNE_BATTLE_ACTION_STATUS_H
#define NOCTURNE_BATTLE_ACTION_STATUS_H
#include <stdint.h>
uint64_t nbActionGetTimeListHp(uint64_t context,uint64_t form);
uint64_t nbActionCheckTimeListDead(uint64_t context,uint64_t form);
uint64_t nbActionCheckTimeListDeadEnemyParty(uint64_t context,uint64_t form);
uint64_t nbActionAddTimeListHp(uint64_t context,uint64_t form,uint64_t delta);
uint64_t nbActionGetEndTime(uint64_t context,uint64_t form);
uint64_t nbActionGetAllEndTime(uint64_t context);
uint64_t nbActionGetAllUnlockTime(uint64_t context);
uint64_t nbGetDevilFormatFlag(uint64_t form);
uint64_t nbCheckKuisibariSkill(uint64_t form);
uint64_t nbCheckKuisibari2Skill(uint64_t form);
void nbSetKuisibariStop(uint64_t form);
uint64_t nbGetUnitID(uint64_t work);
uint64_t nbCheckEventDead(uint64_t form);
uint64_t nbCheckDeadScript(uint64_t form);
uint64_t nbCheckDeadEvent(uint64_t form);
void nbUpdateOrder(void);
void nbPanelAnalyzeEnd(void);
uint64_t datCheckTalk(uint64_t work);
uint64_t datSearchDevilStock(uint64_t id);
void datClearCommMemory(uint64_t work);
void nbPushAction(uint64_t type,uint64_t from,uint64_t to,uint64_t data);
void *nocturneResolveBattleActionStatusAddress(uint32_t address);
#endif
