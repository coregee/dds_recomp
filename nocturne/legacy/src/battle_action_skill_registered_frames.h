#ifndef NOCTURNE_BATTLE_ACTION_SKILL_REGISTERED_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_SKILL_REGISTERED_FRAMES_H
#include <stdint.h>
/* Pure real-code router; registers/FPR/VU/SP hold actual original inputs. */
void nocturneBattleActionSkillCall(uint32_t target);
/* Returns whether a body was dispatched, never a game result. Existing93
 * native variants keep their actual original bank inputs/outputs. This
 * entry dispatcher makes no zero-formal ABI claim for the original bodies. */
uint32_t nocturneBattleActionSkillRegisteredBody(uint32_t entry);
#endif
