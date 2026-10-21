#ifndef NOCTURNE_BATTLE_TARGETING_H
#define NOCTURNE_BATTLE_TARGETING_H
#include <stdint.h>
uint64_t datGetNormalAtkPow(uint64_t unit);
uint64_t datGetDefPow(uint64_t unit);
uint64_t datGetAisyo(uint64_t unit,uint64_t attribute);
uint64_t datGet3Zokusei(uint64_t unit);
uint64_t datGetItemSkillNo(uint64_t item);
uint64_t nbGetItemSkillNo(uint64_t context,uint64_t item);
void nbGetTargetTypeRuleArea(uint64_t context,uint64_t unit,uint64_t type_out,
 uint64_t rule_out,uint64_t area_out,uint64_t reverse);
uint64_t GetTarSelProcessData(void);
uint64_t CheckFormCursor(uint64_t self,uint64_t type,uint64_t rule,uint64_t area,uint64_t target);
uint64_t nbSetSelectOkMark(uint64_t party_index,uint64_t type,uint64_t rule,uint64_t area);
void *nocturneResolveBattleTargetingAddress(uint32_t address);
#endif
