#pragma once
#include <stdint.h>

void nbActionSetNone(uint64_t context);
void nbActionSetAi(uint64_t context);
uint64_t nbActionCheckAi(uint64_t context);
void nbActionSetSeq(uint64_t context,uint64_t state);
void *nocturneResolveBattleActionEntryAddress(uint32_t address);
void nocturneInvokeBattleActionEntry(uint32_t entry,uint64_t context);
