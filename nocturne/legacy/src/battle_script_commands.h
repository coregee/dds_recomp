#pragma once
#include <stdint.h>
uint64_t scrCommand_RND(void);
uint64_t nbCommand_AI_ACT_WAIT(void);
uint64_t nbCommand_AI_TAR_LIFEMIN(void);
uint64_t nbCommand_AI_TAR_BAARLV(void);
uint64_t nbCommand_AI_TAR_LVMIN(void);
uint64_t nbCommand_AI_TAR_BAD(void);
uint64_t nbCommand_AI_TAR_ID(void);
uint64_t nbCommand_AI_TAR_LIGHT(void);
uint64_t nbCommand_AI_TAR_DARK(void);
uint64_t nbCommand_AI_TAR_PLAYER(void);
uint64_t nbCommand_AI_TAR_RND(void);
uint64_t nbCommand_AI_TAR_JOKEN(void);
void *nocturneResolveBattleScriptCommandsAddress(uint32_t address);
