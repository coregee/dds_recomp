#ifndef NOCTURNE_BATTLE_REWARD_NATIVE_H
#define NOCTURNE_BATTLE_REWARD_NATIVE_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneBattleRewardNativeBody(uint32_t entry);
void nocturneBattleRewardNativeExternal(uint32_t target,uint32_t pc);
void nocturneBattleRewardNativeIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattleRewardNativeTrap(uint32_t code,uint32_t pc);
void nocturneBattleRewardNativeCpuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardNativeCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneBattleRewardNativeVuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardNativeVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattleRewardNativeStackPointer(void);
void nocturneBattleRewardNativeSetStackPointer(uint32_t address);
uint32_t nocturneBattleRewardNativeFcsr(void);
void *nocturneResolveBattleRewardNativeAddress(uint32_t address);
void ps2BattleRewardNative_0024A060(void);
void ps2BattleRewardNative_0024A258(void);
void ps2BattleRewardNative_0024A298(uint64_t a0,uint64_t a1);
void ps2BattleRewardNative_0024AE70(void);
uint64_t ps2BattleRewardNative_0024AFA0(void);
void ps2BattleRewardNative_0024BE88(void);
uint64_t ps2BattleRewardNative_0024BFF0(uint64_t a0,uint64_t a1);
void ps2BattleRewardNative_0024C060(void);
uint64_t ps2BattleRewardNative_0024C378(void);
void ps2BattleRewardNative_0024C3F0(uint64_t a0);
void ps2BattleRewardNative_002AAD88(uint64_t a0);
void ps2BattleRewardNative_002AAF20(void);
uint64_t ps2BattleRewardNative_002A8080(uint64_t a0,uint64_t a1,uint64_t a2);
void ps2BattleRewardNative_002AB8F0(uint64_t a0);
void ps2BattleRewardNative_002AC760(uint64_t a0,uint64_t a1);
void ps2BattleRewardNative_002AC7B0(uint64_t a0,uint64_t a1);
#endif
