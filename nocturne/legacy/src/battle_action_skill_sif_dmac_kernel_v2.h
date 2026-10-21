#ifndef NOCTURNE_SKILL_SIF_DMAC_KERNEL_V2_H
#define NOCTURNE_SKILL_SIF_DMAC_KERNEL_V2_H
#include "battle_action_skill_cache_boundary_kernel_v2.h"
#include "battle_action_skill_sif_dmac_policy.h"
typedef struct NocturneSkillSifDmacWorldStateV2 {
    NocturneSkillCacheBoundaryWorldStateV2 cache;
    NocturneSkillSifDmacState device;
    uint32_t activated,event_count;
} NocturneSkillSifDmacWorldStateV2;
typedef struct NocturneSkillSifDmacEventV2 {
    NocturneSkillSifDmacEvent device;
    uint64_t context;
    uint32_t kernel_position,kernel_trace_words,status,primitive_counts[4],reserved;
} NocturneSkillSifDmacEventV2;
_Static_assert(sizeof(NocturneSkillSifDmacWorldStateV2)==488,"SIF DMAC world488");
_Static_assert(sizeof(NocturneSkillSifDmacEventV2)==80,"SIF DMAC event80");
uint32_t nocturneBattleActionSkillWorkerKernelBeginSifDmacWorldV2(const NocturneSkillWorkerKernelInputV2 *,uint32_t,const NocturneSkillCacheReplyConfig *,const NocturneSkillSifDmacConfig *);
uint32_t nocturneBattleActionSkillSifDmacWorldStateV2(NocturneSkillSifDmacWorldStateV2 *);
uint32_t nocturneBattleActionSkillSifDmacEventV2(uint32_t,NocturneSkillSifDmacEventV2 *);
uint32_t nocturneSkillSifDmacRead32(uint32_t);
void nocturneSkillSifDmacWrite32(uint32_t,uint32_t);
#endif
