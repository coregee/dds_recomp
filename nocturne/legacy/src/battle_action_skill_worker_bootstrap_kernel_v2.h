#ifndef NOCTURNE_SKILL_WORKER_BOOTSTRAP_KERNEL_V2_H
#define NOCTURNE_SKILL_WORKER_BOOTSTRAP_KERNEL_V2_H
#include "battle_action_skill_worker_kernel_v2.h"
#include "battle_action_skill_worker_bootstrap_world_policy.h"

/* Separate versioned state. Balanced covers the heap/registry locks only;
 * deferred registration never claims worker execution or file completion. */
typedef struct NocturneSkillWorkerBootstrapWorldStateV2 {
    uint32_t version,enabled,accepted_count,fixed_count,fixed_consumed;
    uint32_t request_limit,heap_and_registry_balanced,execution_deferred;
    NocturneSkillWorkerBootstrapPolicyState policy;
} NocturneSkillWorkerBootstrapWorldStateV2;
_Static_assert(sizeof(NocturneSkillWorkerBootstrapWorldStateV2)==296,"Bootstrap state V2 size");
_Static_assert(offsetof(NocturneSkillWorkerBootstrapWorldStateV2,policy)==32,"Bootstrap policy offset");

uint32_t nocturneBattleActionSkillWorkerKernelBeginBootstrapWorldV2(const NocturneSkillWorkerKernelInputV2 *,uint32_t);
uint32_t nocturneBattleActionSkillWorkerKernelEnabledV2(void);
uint32_t nocturneBattleActionSkillWorkerKernelPolicyFaultV2(void);
uint32_t nocturneBattleActionSkillWorkerBootstrapWorldStateV2(NocturneSkillWorkerBootstrapWorldStateV2 *);
uint32_t nocturneBattleActionSkillWorkerBootstrapSemaphoreCountV2(uint32_t,uint32_t *);
#endif
