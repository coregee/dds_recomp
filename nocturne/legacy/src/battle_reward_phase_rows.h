#ifndef NOCTURNE_BATTLE_REWARD_PHASE_ROWS_H
#define NOCTURNE_BATTLE_REWARD_PHASE_ROWS_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneBattleRewardPhaseRowsBody(uint32_t entry);
void nocturneBattleRewardPhaseNativeExternal(uint32_t target,uint32_t pc);
void nocturneBattleRewardPhaseNativeIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattleRewardPhaseNativeTrap(uint32_t code,uint32_t pc);
void nocturneBattleRewardPhaseNativeCpuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardPhaseNativeCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneBattleRewardPhaseNativeVuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardPhaseNativeVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattleRewardPhaseNativeStackPointer(void);
void nocturneBattleRewardPhaseNativeSetStackPointer(uint32_t address);
uint32_t nocturneBattleRewardPhaseNativeFcsr(void);
void *nocturneResolveBattleRewardPhaseNativeAddress(uint32_t address);
uint64_t ps2BattleRewardPhaseRows_001CA0D0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7);
uint64_t ps2BattleRewardPhaseRows_001CA258(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5);
uint64_t ps2BattleRewardPhaseRows_001C7E00(uint64_t a0);
uint64_t ps2BattleRewardPhaseRows_001C7E18(uint64_t a0,uint64_t a1);
void ps2BattleRewardPhaseRows_0024A2E8(void);
void ps2BattleRewardPhaseRows_0024A440(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5);
#endif
