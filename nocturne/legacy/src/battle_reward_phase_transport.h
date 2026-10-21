#ifndef NOCTURNE_BATTLE_REWARD_PHASE_TRANSPORT_H
#define NOCTURNE_BATTLE_REWARD_PHASE_TRANSPORT_H
#include "battle_reward_phase_native.h"
#include "battle_reward_phase_raw.h"
#include "battle_panel_renderer_bundle.h"
void nocturneBattleRewardPhaseCall(uint32_t target,uint32_t pc);
void nocturneBattleRewardPhaseBaseCall(uint32_t target,uint32_t pc);
uint32_t nocturneBattleRewardPhaseRun(uint32_t entry);
const NocturneBattlePanelRendererStop *nocturneBattleRewardPhaseLastStop(void);
#endif
