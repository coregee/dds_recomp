#pragma once
#include <stdint.h>
uint64_t nbGetVirtualKoukaPoint(uint64_t skill,uint64_t source,uint64_t target);
uint64_t nbAiSelAi(uint64_t context,uint64_t unused,uint64_t group);
uint64_t nbSetEnemySummonFormation(uint64_t main,uint64_t devil);
void *nocturneResolveBattleAiEstimatesAddress(uint32_t address);
