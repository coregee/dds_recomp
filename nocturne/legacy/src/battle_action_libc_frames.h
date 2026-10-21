#ifndef NOCTURNE_BATTLE_ACTION_LIBC_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_LIBC_FRAMES_H
#include <stdint.h>
/* Raw bank-only complete-body dispatch. Return is a handled flag, never V0. */
uint32_t nocturneBattleActionLibcBody(uint32_t entry);
/* Exact old CVT8 and Compare2 C signatures for genuine native-bank callers.
 * Only their actual formals are published; all other live lanes are retained. */
uint64_t ps2BattleActionLibcCvt_002D7CE8(uint64_t context,uint64_t bits,uint64_t precision,uint64_t flags,uint64_t signByte,uint64_t decimalPoint,uint64_t format,uint64_t length);
int32_t ps2BattleActionLibcCompare_002D1B38(uint64_t left,uint64_t right);
#endif
