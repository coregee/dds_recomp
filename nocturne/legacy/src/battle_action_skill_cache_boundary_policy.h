#ifndef NOCTURNE_SKILL_CACHE_BOUNDARY_POLICY_H
#define NOCTURNE_SKILL_CACHE_BOUNDARY_POLICY_H
#include "battle_action_skill_sdk_file_mutex_policy.h"
/* NEW opt-in chosen external world. No default cache response, no device model. */
typedef struct NocturneSkillCacheReplyConfig {
    uint32_t version,effect_mode;
    uint64_t v0_low,v1_low,t0_low,t1_low;
} NocturneSkillCacheReplyConfig;
#define NOCTURNE_SKILL_CACHE_LOW64_ONLY 1u
typedef struct NocturneSkillCacheExtraOutputs { uint32_t mode,register_mask; uint64_t t0_low,t1_low; } NocturneSkillCacheExtraOutputs;
typedef struct NocturneSkillCacheBoundaryState {
    uint32_t version,accepted_count,local_accepted_count,cache_count,held25_accepted,worker_seen;
    uint64_t held25_context,last_context;
    NocturneSkillCacheReplyConfig config;
    NocturneSkillSdkFileMutexState base;
    uint32_t reserved;
} NocturneSkillCacheBoundaryState;
typedef struct NocturneSkillCacheBoundaryPreview {
    uint32_t version,kind;
    NocturneSkillCacheBoundaryState before,proposed;
    NocturneSkillSdkFileMutexPreview delegated;
    NocturneSkillWorkerKernelInputV2 record;
    NocturneSkillCacheExtraOutputs extra_outputs;
    uint64_t context,incoming_v1_upper,seal;
} NocturneSkillCacheBoundaryPreview;
_Static_assert(sizeof(NocturneSkillCacheReplyConfig)==40,"Cache config40");
_Static_assert(sizeof(NocturneSkillCacheBoundaryState)==400,"Cache state400");
_Static_assert(offsetof(NocturneSkillCacheBoundaryState,base)==80,"Cache SDK base80");
_Static_assert(sizeof(NocturneSkillCacheBoundaryPreview)==2264,"Cache preview2264");
_Static_assert(offsetof(NocturneSkillCacheBoundaryPreview,record)==2144,"Cache record2144");
_Static_assert(offsetof(NocturneSkillCacheBoundaryPreview,extra_outputs)==2216,"Cache explicit outputs2216");
_Static_assert(offsetof(NocturneSkillCacheBoundaryPreview,context)==2240,"Cache context2240");
_Static_assert(offsetof(NocturneSkillCacheBoundaryPreview,seal)==2256,"Cache seal2256");
uint32_t nocturneSkillCacheBoundaryInit(NocturneSkillCacheBoundaryState *,const NocturneSkillCacheReplyConfig *);
uint32_t nocturneSkillCacheBoundaryPreview(const NocturneSkillCacheBoundaryState *,uint64_t trusted_context,
    NocturneSkillWorkerBootstrapPolicyReadBytes,void *,uint64_t selector,uint32_t pc,uint32_t argc,
    const uint64_t *,uint64_t actual_incoming_v1_upper,NocturneSkillCacheBoundaryPreview *);
uint32_t nocturneSkillCacheBoundaryCommit(NocturneSkillCacheBoundaryState *,const NocturneSkillCacheBoundaryPreview *);
uint32_t nocturneSkillCacheBoundaryIsStop(uint32_t);
/* Context0 means foreground31; context41 requires actual accepted thread/start.
 * Transport holds its busy guard, validates fixed72B record and all trace bounds,
 * and keeps context stable before Commit. Policy never writes CPU/RAM. A future
 * transport must separately preflight/publish extra_outputs only for kind2;
 * the historical72B record cannot represent these additional T0/T1 outputs.
 * mode1/register_mask3 means replace LOW64 only; retain actual upper64. The
 * cache V1 record merges actual_incoming_v1_upper before fixed validation. */
#endif
