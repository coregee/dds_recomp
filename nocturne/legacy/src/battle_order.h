#ifndef NOCTURNE_BATTLE_ORDER_H
#define NOCTURNE_BATTLE_ORDER_H
#include <stdint.h>
/* Actual ordinary guest RAM/SP, shared with real process and sort code. */
void *nocturneResolveBattleOrderAddress(uint32_t address);
uint32_t nocturneBattleOrderStackPointer(void);
void nocturneBattleOrderSetStackPointer(uint32_t address);
void ps2BattleOrder_00258048(uint64_t p0);
void ps2BattleOrder_00258280(uint64_t p0);
void ps2BattleOrder_002583D8(void);
void ps2BattleOrder_00258418(void);
/* All four roles are genuinely VOID. Actor index stays raw64 until native
 * word multiplication/address arithmetic. Side tests all64 bits against0.
 * Native private/save frames and full volatile CPU state are not the
 * semantic typed-call assertion profile. No NULL Main fallback exists. */
#endif
