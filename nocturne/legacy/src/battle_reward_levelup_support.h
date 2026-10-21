#ifndef NOCTURNE_BATTLE_REWARD_LEVELUP_SUPPORT_H
#define NOCTURNE_BATTLE_REWARD_LEVELUP_SUPPORT_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneBattleRewardLevelupSupportBody(uint32_t entry);
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
void ps2BattleRewardLevelupSupport_0024A060(void);
void ps2BattleRewardLevelupSupport_0024A258(void);
void ps2BattleRewardLevelupSupport_0024A298(uint64_t a0,uint64_t a1);
void ps2BattleRewardLevelupSupport_0024AE70(void);
uint64_t ps2BattleRewardLevelupSupport_0024AFA0(void);
void ps2BattleRewardLevelupSupport_0024BE88(void);
uint64_t ps2BattleRewardLevelupSupport_0024BFF0(uint64_t a0,uint64_t a1);
void ps2BattleRewardLevelupSupport_0024C060(void);
uint64_t ps2BattleRewardLevelupSupport_0024C378(void);
void ps2BattleRewardLevelupSupport_0024C3F0(uint64_t a0);
void ps2BattleRewardLevelupSupport_002AAD88(uint64_t a0);
void ps2BattleRewardLevelupSupport_002AAF20(void);
uint64_t ps2BattleRewardLevelupSupport_002A8080(uint64_t a0,uint64_t a1,uint64_t a2);
void ps2BattleRewardLevelupSupport_002AB8F0(uint64_t a0);
void ps2BattleRewardLevelupSupport_002AC760(uint64_t a0,uint64_t a1);
void ps2BattleRewardLevelupSupport_002AC7B0(uint64_t a0,uint64_t a1);
#endif
