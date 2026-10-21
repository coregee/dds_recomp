#ifndef NOCTURNE_SKILL_CACHE_BOUNDARY_KERNEL_V2_H
#define NOCTURNE_SKILL_CACHE_BOUNDARY_KERNEL_V2_H
#include "battle_action_skill_file_mutex_kernel_v2.h"
#include "battle_action_skill_cache_boundary_policy.h"
typedef struct NocturneSkillCacheBoundaryWorldStateV2 {
    uint32_t version,enabled,accepted_count,fixed_count,fixed_consumed;
    uint32_t request_limit,heap_and_registry_balanced,execution_deferred;
    NocturneSkillCacheBoundaryState policy;
} NocturneSkillCacheBoundaryWorldStateV2;
typedef struct NocturneSkillCacheMmioRequestV2 {
    uint32_t version,pc,address,width;
    uint64_t context;
    uint32_t accepted_count,reserved;
} NocturneSkillCacheMmioRequestV2;
_Static_assert(sizeof(NocturneSkillCacheBoundaryWorldStateV2)==432,"Cache world432");
_Static_assert(sizeof(NocturneSkillCacheMmioRequestV2)==32,"MMIO request32");
uint32_t nocturneBattleActionSkillWorkerKernelBeginCacheBoundaryWorldV2(const NocturneSkillWorkerKernelInputV2 *,uint32_t,const NocturneSkillCacheReplyConfig *);
uint32_t nocturneBattleActionSkillCacheBoundaryWorldStateV2(NocturneSkillCacheBoundaryWorldStateV2 *);
uint32_t nocturneBattleActionSkillCacheBoundaryMmioRequestV2(NocturneSkillCacheMmioRequestV2 *);
void *nocturneSkillCacheBoundaryResolve(uint32_t);
#endif
