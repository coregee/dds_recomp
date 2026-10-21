#ifndef NOCTURNE_SKILL_SIF_KERNEL_TRANSPORT_H
#define NOCTURNE_SKILL_SIF_KERNEL_TRANSPORT_H
#include "battle_action_skill_sif_dmac_kernel_v2.h"
#include "battle_action_skill_sif_kernel_policy.h"
typedef struct NocturneSkillSifKernelWorldStateV2 {
    NocturneSkillSifDmacWorldStateV2 initial_protocol;
    NocturneSkillSifKernelState kernel;
    uint32_t accepted_count,kernel_event_count;
} NocturneSkillSifKernelWorldStateV2;
typedef struct NocturneSkillSifKernelEventV2 {
    NocturneSkillSifKernelReceipt receipt;
    uint64_t context;
    uint32_t kernel_position,kernel_trace_words,status,primitive_counts[4],reserved;
} NocturneSkillSifKernelEventV2;
_Static_assert(sizeof(NocturneSkillSifKernelWorldStateV2)==760,"kernel world760");
_Static_assert(sizeof(NocturneSkillSifKernelEventV2)==488,"kernel effect event488");
uint32_t nocturneBattleActionSkillWorkerKernelBeginSifKernelWorldV2(const NocturneSkillWorkerKernelInputV2 *,uint32_t,const NocturneSkillCacheReplyConfig *,const NocturneSkillSifDmacConfig *,const NocturneSkillSifKernelConfig *);
uint32_t nocturneBattleActionSkillSifKernelWorldStateV2(NocturneSkillSifKernelWorldStateV2 *);
uint32_t nocturneBattleActionSkillSifKernelEventV2(uint32_t,NocturneSkillSifKernelEventV2 *);
uint32_t nocturneBattleActionSkillSifKernelStartupDeviceEventV2(uint32_t,NocturneSkillSifDmacEventV2 *);
#endif
