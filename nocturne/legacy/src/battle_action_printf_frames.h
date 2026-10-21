#ifndef NOCTURNE_BATTLE_ACTION_PRINTF_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_PRINTF_FRAMES_H
#include <stdint.h>
/* Registered native variants, zero new identity credit. Printf is callable
 * only from genuine native-bank callers: A1..T3 and F12..F19 must already
 * hold original incoming values. It sets A0=format and spills those shared
 * banks into the real guest frame; a host variadic cursor is never read. */
uint64_t ps2BattleActionPrintf_002D4748(uint64_t format, ...);
uint64_t ps2BattleActionVfprintfStream_002D6600(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionVfprintf_002D6678(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionLocaleConvention_002DA340(void);
uint64_t ps2BattleActionLocaleRecord_002DA308(uint64_t a0);
uint64_t ps2BattleActionWidenByte_002DA4B8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionSprint_002D6500(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionWriteVectors_002D9E00(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionMemmove_002D4454(uint64_t a0, uint64_t a1, uint64_t a2);
#endif
