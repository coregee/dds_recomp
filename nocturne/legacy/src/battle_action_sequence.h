#pragma once
#include <stdint.h>

uint64_t dds3ExistProcess(uint64_t process);
void nbActionClearTimeList(uint64_t context);
void nbActionSetHpForTimeList(uint64_t context);
uint64_t nbActionCheckAiScript(uint64_t context);
void nbActionSetDeadScript(uint64_t context);
uint64_t nbGetActionSeq(uint64_t process);
uint64_t nbGetPrevActionSeq(void);
void nbActionSetNextSeq(uint64_t context,uint64_t state);
void *nocturneResolveBattleActionSequenceAddress(uint32_t address);
