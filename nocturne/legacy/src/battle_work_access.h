#ifndef NOCTURNE_BATTLE_WORK_ACCESS_H
#define NOCTURNE_BATTLE_WORK_ACCESS_H
#include <stdint.h>
uint64_t dds3SearchProcessPriority(uint64_t priority);
uint64_t nbGetMainProcessData(void);
uint64_t nbGetUnitWorkPointer(uint64_t main_data,uint64_t party);
uint64_t nbGetPartyFromFormindex(uint64_t formindex);
uint64_t nbGetUnitWorkFromFormindex(uint64_t formindex);
void ps2BattleStartActorAi(uint64_t context);
void *nocturneResolveBattleWorkAccessAddress(uint32_t address);
#endif
