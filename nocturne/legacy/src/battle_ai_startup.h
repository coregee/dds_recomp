#ifndef NOCTURNE_BATTLE_AI_STARTUP_H
#define NOCTURNE_BATTLE_AI_STARTUP_H
#include <stdint.h>
void nbInitAiScript(uint64_t context,uint64_t procedure);
void dds3LinkProcess(uint64_t parent,uint64_t target);
void itfMesMngSetVar(uint64_t id,uint64_t index,uint64_t number,uint64_t type);
uint64_t itfMesMngSetVarScr(void);
void itfMesMngSetVariableString(uint64_t id,uint64_t index,uint64_t string);
void itfMesMngSetVariableBytes(uint64_t id,uint64_t index,uint64_t string,uint64_t bytes);
uint64_t itfMesSetVar(uint64_t instance,uint64_t index,uint64_t string,uint64_t bytes);
uint64_t ps2MessageWriteDecimal(uint64_t number,uint64_t output);
void ps2MessageBuildCharacterName(uint64_t index);
void *nocturneResolveBattleAiStartupAddress(uint32_t address);
/* Host-only input boundary for observable untouched bytes in the native
 * private message setter frame. It supplies memory, never a gameplay result. */
void nocturneBattleAiMessageAmbientFrame(void *frame,uint32_t bytes);
#endif
