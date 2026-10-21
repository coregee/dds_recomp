#ifndef NOCTURNE_BATTLE_REWARD_PHASE_RECYCLER_H
#define NOCTURNE_BATTLE_REWARD_PHASE_RECYCLER_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneBattleRewardPhaseRecyclerBody(uint32_t entry);
void nocturneBattleRewardPhaseRecyclerExternal(uint32_t target,uint32_t pc);
void nocturneBattleRewardPhaseRecyclerIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneBattleRewardPhaseRecyclerTrap(uint32_t code,uint32_t pc);
void nocturneBattleRewardPhaseRecyclerCpuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardPhaseRecyclerCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneBattleRewardPhaseRecyclerVuRead(unsigned reg,uint32_t words[4]);
void nocturneBattleRewardPhaseRecyclerVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattleRewardPhaseRecyclerStackPointer(void);
void nocturneBattleRewardPhaseRecyclerSetStackPointer(uint32_t address);
uint32_t nocturneBattleRewardPhaseRecyclerFcsr(void);
void *nocturneResolveBattleRewardPhaseRecyclerAddress(uint32_t address);
void ps2BattleRewardPhaseRecycler_001C6068(uint64_t a0);
void ps2BattleRewardPhaseRecycler_001C6E50(uint64_t a0);
uint64_t ps2BattleRewardPhaseRecycler_001C6F08(uint64_t a0);
uint64_t ps2BattleRewardPhaseRecycler_001C80B8(void);
void ps2BattleRewardPhaseRecycler_001C99C0(uint64_t a0);
uint64_t ps2BattleRewardPhaseRecycler_001CAC00(uint64_t a0,uint64_t a1);
#endif
