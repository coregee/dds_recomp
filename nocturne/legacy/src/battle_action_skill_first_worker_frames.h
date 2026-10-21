#ifndef NOCTURNE_SKILL_FIRST_WORKER_FRAMES_H
#define NOCTURNE_SKILL_FIRST_WORKER_FRAMES_H
#include <stdint.h>
void nocturneBattleActionSkillCall(uint32_t target);
/* Site-aware real-code callback admission is external. No supplied result.
 * Until reviewed, reject before callback execution. Never truncate rawTarget. */
void nocturneBattleActionSkillFirstWorkerIndirect(uint32_t site,uint64_t rawTarget);
/* Handled flag only; native game V0/F0 remains in the shared bank. */
uint32_t nocturneBattleActionSkillFirstWorkerBody(uint32_t entry);
#endif
