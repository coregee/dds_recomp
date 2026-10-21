#ifndef NOCTURNE_BATTLE_STATUS_PAIRS_NATIVE_H
#define NOCTURNE_BATTLE_STATUS_PAIRS_NATIVE_H
#include <stdint.h>
/* Actual shared CPU128/FPR/VU/RAM/SP. Host handled status is not V0.
 * External routes execute real callee bodies and retain all clobbers. */
uint32_t nocturneBattleStatusPairsNativeBody(uint32_t entry);
void nocturneBattleStatusPairsNativeExternal(uint32_t target,uint32_t pc);
uint32_t nocturneBattleStatusPairsNativeFcsr(void);
void ps2BattleStatusPairsNative_00253DE0(void);
uint64_t ps2BattleStatusPairsNative_00253E00(uint64_t argument);
void ps2BattleStatusPairsNative_00254010(uint64_t argument);
uint64_t ps2BattleStatusPairsNative_00254058(uint64_t argument);
void ps2BattleStatusPairsNative_00254178(uint64_t argument);
uint64_t ps2BattleStatusPairsNative_00254190(uint64_t argument);
void ps2BattleStatusPairsNative_00254360(uint64_t argument);
uint64_t ps2BattleStatusPairsNative_002543A0(uint64_t argument);
#endif
