#ifndef NOCTURNE_BATTLE_REWARD_LEVELUP_NATIVE_H
#define NOCTURNE_BATTLE_REWARD_LEVELUP_NATIVE_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneBattleRewardLevelupNativeBody(uint32_t entry);
void nocturneBattleRewardLevelupNativeExternal(uint32_t target,uint32_t pc);
void nocturneBattleRewardLevelupNativeIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattleRewardLevelupNativeTrap(uint32_t code,uint32_t pc);
void nocturneBattleRewardLevelupNativeCpuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardLevelupNativeCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneBattleRewardLevelupNativeVuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardLevelupNativeVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattleRewardLevelupNativeStackPointer(void);
void nocturneBattleRewardLevelupNativeSetStackPointer(uint32_t address);
uint32_t nocturneBattleRewardLevelupNativeFcsr(void);
void *nocturneResolveBattleRewardLevelupNativeAddress(uint32_t address);
uint64_t ps2BattleRewardLevelupNative_001CA0D0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7);
uint64_t ps2BattleRewardLevelupNative_001CA258(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5);
uint64_t ps2BattleRewardLevelupNative_001C7E00(uint64_t a0);
uint64_t ps2BattleRewardLevelupNative_001C7E18(uint64_t a0,uint64_t a1);
void ps2BattleRewardLevelupNative_0024A2E8(void);
void ps2BattleRewardLevelupNative_0024A440(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5);
#endif
