#pragma once
#include <stdint.h>
float nbGetAisyoRitu(uint64_t skill,uint64_t source,uint64_t target);
uint64_t nbGetKoukaHp(float ratio,uint64_t damage,uint64_t skill,uint64_t source,uint64_t target,uint64_t count);
uint64_t nbGetKoukaMp(float ratio,uint64_t damage,uint64_t skill,uint64_t source,uint64_t target,uint64_t count);
uint64_t nbGetKoukaBadDamage(float ratio,uint64_t skill,uint64_t source,uint64_t target,uint64_t preview);
uint64_t nbGetKoukaBadKaifuku(float ratio,uint64_t skill,uint64_t source,uint64_t target,uint64_t preview);
uint64_t nbSetHojoKouka(uint64_t formation,uint64_t mask,uint64_t point,uint64_t preview);
void *nocturneResolveBattleEffectsAddress(uint32_t address);
