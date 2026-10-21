#pragma once
#include <stdint.h>
uint64_t nbSetHojoAddCounter(uint64_t formation,uint64_t type,uint64_t delta,uint64_t preview);
float nbGetHojoRitu(uint64_t formation,uint64_t type);
uint64_t nbGetAisyo(uint64_t skill,uint64_t target,uint64_t attribute);
uint64_t nbGetVirtualAisyo(uint64_t skill,uint64_t source,uint64_t target);
void *nocturneResolveBattleAffinityAddress(uint32_t address);
