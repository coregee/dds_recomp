#ifndef NOCTURNE_BATTLE_REWARD_RAW_H
#define NOCTURNE_BATTLE_REWARD_RAW_H
#include "battle_native_flow.h"
#include "battle_action_formula_frames.h"
void nocturneEffectHostCpuRead(unsigned,uint32_t[4]);
void nocturneEffectHostCpuWrite(unsigned,const uint32_t[4]);
_Noreturn void nocturneBattleRewardBoundary(uint32_t,uint32_t,uint64_t);
uint32_t nocturneBattleRewardRawConfigure(const NocturneWakeupMachine *,const uint32_t *,uint32_t,uint64_t);
const NocturneWakeupMachine *nocturneBattleRewardRawState(void);
const NocturneWakeupStop *nocturneBattleRewardRawStop(void);
uint32_t nocturneBattleRewardRawOwns(uint32_t);
void nocturneBattleRewardRawCall(uint32_t,uint32_t);
void nocturneBattleRewardRawSyscall(uint32_t,uint64_t);
uint64_t nocturneBattleRewardRawKernel(uint64_t,uint32_t,const uint64_t *);
#endif
