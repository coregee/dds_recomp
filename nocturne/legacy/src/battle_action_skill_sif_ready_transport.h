#ifndef NOCTURNE_SKILL_SIF_READY_TRANSPORT_H
#define NOCTURNE_SKILL_SIF_READY_TRANSPORT_H
#include "battle_action_skill_sif_kernel_transport.h"
#include "battle_action_skill_sif_ready_policy.h"
typedef struct NocturneSkillSifReadyWorldV2 {
    NocturneSkillSifKernelWorldStateV2 prefix;
    NocturneSkillSifReadyState ready;
    uint32_t accepted_count,ready_event_count,cache_event_count,reserved;
} NocturneSkillSifReadyWorldV2;
typedef struct NocturneSkillSifReadyCacheEventV2 {
    uint32_t version,ordinal,pc,operation;
    uint64_t raw_address,context;
    uint32_t kernel_position,kernel_trace_words,status,reserved,primitive_counts[4];
} NocturneSkillSifReadyCacheEventV2;
_Static_assert(sizeof(NocturneSkillSifReadyWorldV2)==808,"ready world808");
_Static_assert(sizeof(NocturneSkillSifReadyCacheEventV2)==64,"cache event64");
uint32_t nocturneBattleActionSkillWorkerKernelBeginSifReadyWorldV2(const NocturneSkillWorkerKernelInputV2 *,uint32_t,const NocturneSkillCacheReplyConfig *,const NocturneSkillSifDmacConfig *,const NocturneSkillSifKernelConfig *,const NocturneSkillSifReadyConfig *);
uint32_t nocturneBattleActionSkillSifReadyWorldStateV2(NocturneSkillSifReadyWorldV2 *);
uint32_t nocturneBattleActionSkillSifReadyEventV2(uint32_t,NocturneSkillSifKernelEventV2 *);
uint32_t nocturneBattleActionSkillSifReadyCacheEventV2(uint32_t,NocturneSkillSifReadyCacheEventV2 *);
void nocturneBattleActionSkillSifReadyCacheValue(uint32_t,uint32_t,uint64_t);
#endif
