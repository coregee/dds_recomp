#ifndef NOCTURNE_BATTLE_REWARD_LEVELUP_RAW_H
#define NOCTURNE_BATTLE_REWARD_LEVELUP_RAW_H
#include "battle_native_flow.h"
#include "battle_action_formula_frames.h"
void nocturneEffectHostCpuRead(unsigned,uint32_t[4]);
void nocturneEffectHostCpuWrite(unsigned,const uint32_t[4]);
_Noreturn void nocturneBattleRewardLevelupBoundary(uint32_t,uint32_t,uint64_t);
uint32_t nocturneBattleRewardLevelupRawConfigure(const NocturneWakeupMachine *,const uint32_t *,uint32_t,uint64_t);
const NocturneWakeupMachine *nocturneBattleRewardLevelupRawState(void);
const NocturneWakeupStop *nocturneBattleRewardLevelupRawStop(void);
uint32_t nocturneBattleRewardLevelupRawOwns(uint32_t);
void nocturneBattleRewardLevelupRawCall(uint32_t,uint32_t);
void nocturneBattleRewardLevelupRawSyscall(uint32_t,uint64_t);
uint64_t nocturneBattleRewardLevelupRawKernel(uint64_t,uint32_t,const uint64_t *);
#endif
