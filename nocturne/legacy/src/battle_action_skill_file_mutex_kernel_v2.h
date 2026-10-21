#ifndef NOCTURNE_SKILL_FILE_MUTEX_KERNEL_V2_H
#define NOCTURNE_SKILL_FILE_MUTEX_KERNEL_V2_H
#include "battle_action_skill_worker_bootstrap_kernel_v2.h"
#include "battle_action_skill_sdk_file_mutex_policy.h"
typedef struct NocturneSkillFileMutexWorldStateV2 {
    uint32_t version,enabled,accepted_count,fixed_count,fixed_consumed;
    uint32_t request_limit,heap_and_registry_balanced,execution_deferred;
    NocturneSkillSdkFileMutexState policy;
} NocturneSkillFileMutexWorldStateV2;
_Static_assert(sizeof(NocturneSkillFileMutexWorldStateV2)==348,"File mutex world348");
_Static_assert(offsetof(NocturneSkillFileMutexWorldStateV2,policy)==32,"File mutex policy32");
uint32_t nocturneBattleActionSkillWorkerKernelBeginFileMutexWorldV2(const NocturneSkillWorkerKernelInputV2 *,uint32_t);
uint32_t nocturneBattleActionSkillFileMutexWorldStateV2(NocturneSkillFileMutexWorldStateV2 *);
uint32_t nocturneBattleActionSkillFileMutexSemaphoreCountV2(uint32_t,uint32_t *);
#endif
