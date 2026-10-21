#ifndef NOCTURNE_BATTLE_SUPPORT_ACCESS_H
#define NOCTURNE_BATTLE_SUPPORT_ACCESS_H
#include <stdint.h>
uint64_t nbGetBadStat(uint64_t form_index);
uint64_t nbGetNormalSkillAttr(uint64_t skill);
void nbSetHojoCounter(uint64_t form_index,uint64_t type,uint64_t point);
uint64_t nbGetHojoCounter(uint64_t form_index,uint64_t type);
uint64_t nbGetHojoCounterMax(uint64_t type);
uint64_t nbGetHojoCounterMin(uint64_t type);
uint64_t nbCheckFormationPlayerSide(uint64_t form_index);
void *nocturneResolveBattleSupportAddress(uint32_t address);
#endif
