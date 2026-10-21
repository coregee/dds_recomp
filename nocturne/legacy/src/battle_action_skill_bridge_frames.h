#ifndef NOCTURNE_BATTLE_ACTION_SKILL_BRIDGE_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_SKILL_BRIDGE_FRAMES_H
#include <stdint.h>
void nocturneBattleActionSkillCall(uint32_t target);
/* Actual original bank inputs/outputs; returns transport handled flag only.
 * No zero-formal ABI, game result or new identity is claimed by this router. */
uint32_t nocturneBattleActionSkillBridgeBody(uint32_t entry);
#endif
