#ifndef NOCTURNE_BATTLE_ACTION_SKILL_WORKER_BOOTSTRAP_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_SKILL_WORKER_BOOTSTRAP_FRAMES_H
#include <stdint.h>
/* Pure code-address endpoint: genuine native callees, never supplied results. */
void nocturneBattleActionSkillCall(uint32_t target);
/* Shared bank/guest-frame entry; return is handled1 or unknown0, never V0.
 * No zero-formal native ABI or new identity is inferred from this router. */
uint32_t nocturneBattleActionSkillWorkerBootstrapBody(uint32_t entry);
#endif
