#ifndef NOCTURNE_BATTLE_REWARD_LIFECYCLE_NATIVE_H
#define NOCTURNE_BATTLE_REWARD_LIFECYCLE_NATIVE_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneBattleRewardLifecycleNativeBody(uint32_t entry);
void nocturneBattleRewardLifecycleNativeExternal(uint32_t target,uint32_t pc);
void nocturneBattleRewardLifecycleNativeIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattleRewardLifecycleNativeTrap(uint32_t code,uint32_t pc);
void nocturneBattleRewardLifecycleNativeCpuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardLifecycleNativeCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneBattleRewardLifecycleNativeVuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardLifecycleNativeVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattleRewardLifecycleNativeStackPointer(void);
void nocturneBattleRewardLifecycleNativeSetStackPointer(uint32_t address);
uint32_t nocturneBattleRewardLifecycleNativeFcsr(void);
void *nocturneResolveBattleRewardLifecycleNativeAddress(uint32_t address);
void ps2BattleRewardLifecycleNative_00127368(uint64_t a0,uint64_t a1);
uint64_t ps2BattleRewardLifecycleNative_00127378(void);
void ps2BattleRewardLifecycleNative_00127510(void);
uint64_t ps2BattleRewardLifecycleNative_00127580(void);
uint64_t ps2BattleRewardLifecycleNative_00128408(uint64_t a0,uint64_t a1,uint64_t a2);
void ps2BattleRewardLifecycleNative_00136628(uint64_t a0);
void ps2BattleRewardLifecycleNative_001E1770(void);
void ps2BattleRewardLifecycleNative_0024BF40(void);
uint64_t ps2BattleRewardLifecycleNative_0024C1D0(uint64_t a0);
uint64_t ps2BattleRewardLifecycleNative_0024C3C8(uint64_t a0);
void ps2BattleRewardLifecycleNative_0024CBB8(uint64_t a0);
void ps2BattleRewardLifecycleNative_0028DD50(void);
void ps2BattleRewardLifecycleNative_0028DDA8(void);
uint64_t ps2BattleRewardLifecycleNative_002969A0(uint64_t a0);
void ps2BattleRewardLifecycleNative_00297890(void);
#endif
