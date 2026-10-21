#pragma once
#include <stdint.h>
uint64_t nbGetButuriAttack(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
uint64_t nbGetButuriKaifuku(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
uint64_t nbGetMagicAttack(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
uint64_t nbGetMagicKaifuku(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
uint64_t nbGetMaxHpWazaPoint(uint64_t skill,uint64_t source,uint64_t target,uint64_t power);
void *nocturneResolveBattlePowerAddress(uint32_t address);
