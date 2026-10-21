#ifndef NOCTURNE_BATTLE_REWARD_PHASE_SUPPORT_H
#define NOCTURNE_BATTLE_REWARD_PHASE_SUPPORT_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneBattleRewardPhaseSupportBody(uint32_t entry);
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
void ps2BattleRewardPhaseSupport_0024A060(void);
void ps2BattleRewardPhaseSupport_0024A258(void);
void ps2BattleRewardPhaseSupport_0024A298(uint64_t a0,uint64_t a1);
void ps2BattleRewardPhaseSupport_0024AE70(void);
uint64_t ps2BattleRewardPhaseSupport_0024AFA0(void);
void ps2BattleRewardPhaseSupport_0024BE88(void);
uint64_t ps2BattleRewardPhaseSupport_0024BFF0(uint64_t a0,uint64_t a1);
void ps2BattleRewardPhaseSupport_0024C060(void);
uint64_t ps2BattleRewardPhaseSupport_0024C378(void);
void ps2BattleRewardPhaseSupport_0024C3F0(uint64_t a0);
void ps2BattleRewardPhaseSupport_002AAD88(uint64_t a0);
void ps2BattleRewardPhaseSupport_002AAF20(void);
uint64_t ps2BattleRewardPhaseSupport_002A8080(uint64_t a0,uint64_t a1,uint64_t a2);
void ps2BattleRewardPhaseSupport_002AB8F0(uint64_t a0);
void ps2BattleRewardPhaseSupport_002AC760(uint64_t a0,uint64_t a1);
void ps2BattleRewardPhaseSupport_002AC7B0(uint64_t a0,uint64_t a1);
#endif
