#ifndef NOCTURNE_BATTLE_REWARD_PHASE_RAW_H
#define NOCTURNE_BATTLE_REWARD_PHASE_RAW_H
#include "battle_native_flow.h"
#include "battle_action_formula_frames.h"
void nocturneEffectHostCpuRead(unsigned,uint32_t[4]);
void nocturneEffectHostCpuWrite(unsigned,const uint32_t[4]);
_Noreturn void nocturneBattleRewardPhaseBoundary(uint32_t,uint32_t,uint64_t);
uint32_t nocturneBattleRewardPhaseRawConfigure(const NocturneWakeupMachine *,const uint32_t *,uint32_t,uint64_t);
const NocturneWakeupMachine *nocturneBattleRewardPhaseRawState(void);
const NocturneWakeupStop *nocturneBattleRewardPhaseRawStop(void);
uint32_t nocturneBattleRewardPhaseRawOwns(uint32_t);
void nocturneBattleRewardPhaseRawCall(uint32_t,uint32_t);
void nocturneBattleRewardPhaseRawSyscall(uint32_t,uint64_t);
uint64_t nocturneBattleRewardPhaseRawKernel(uint64_t,uint32_t,const uint64_t *);
#endif

int nocturneBattleRewardPhaseRawCache(uint32_t,uint32_t,uint32_t);
int nocturneBattleRewardPhaseRawTagLo(uint32_t *);
