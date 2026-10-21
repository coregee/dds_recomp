#ifndef NOCTURNE_BATTLE_REWARD_LEVELUP_TRANSPORT_H
#define NOCTURNE_BATTLE_REWARD_LEVELUP_TRANSPORT_H
#include "battle_reward_levelup_native.h"
#include "battle_reward_levelup_raw.h"
#include "battle_panel_renderer_bundle.h"
void nocturneBattleRewardLevelupCall(uint32_t target,uint32_t pc);
void nocturneBattleRewardLevelupBaseCall(uint32_t target,uint32_t pc);
uint32_t nocturneBattleRewardLevelupRun(uint32_t entry);
const NocturneBattlePanelRendererStop *nocturneBattleRewardLevelupLastStop(void);
#endif
