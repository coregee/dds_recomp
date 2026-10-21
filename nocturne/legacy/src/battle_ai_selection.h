#pragma once
#include <stdint.h>
uint64_t nbSetSingleTarget2(uint64_t context,uint64_t selector,uint64_t parameter);
uint64_t nbSetGroupTarget2(uint64_t context,uint64_t selector,uint64_t parameter);
uint64_t nbSetAiTarget(uint64_t context,uint64_t selector,uint64_t parameter);
uint64_t nbCommand_AI_TAR_AI(void);
void *nocturneResolveBattleAiSelectionAddress(uint32_t address);
