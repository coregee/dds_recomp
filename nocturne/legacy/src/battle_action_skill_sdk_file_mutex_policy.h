#ifndef NOCTURNE_SKILL_SDK_FILE_MUTEX_POLICY_H
#define NOCTURNE_SKILL_SDK_FILE_MUTEX_POLICY_H
#include "battle_action_skill_worker_bootstrap_world_policy.h"
/* Opt-in ABI, never substitute for unchanged264B/616B bootstrap policy. */
typedef struct NocturneSkillSdkFileMutexState {
    uint32_t version,accepted_count,sdk_accepted_count,created,count,packet_address,worker_wait_accepted;
    uint8_t packet[24];
    NocturneSkillWorkerBootstrapPolicyState base;
} NocturneSkillSdkFileMutexState;
typedef struct NocturneSkillSdkFileMutexPreview {
    uint32_t version,kind;
    NocturneSkillSdkFileMutexState before,proposed;
    NocturneSkillWorkerBootstrapPolicyPreview delegated;
    NocturneSkillWorkerKernelInputV2 record;
    uint64_t seal;
} NocturneSkillSdkFileMutexPreview;
_Static_assert(sizeof(NocturneSkillSdkFileMutexState)==316,"SDK state316");
_Static_assert(offsetof(NocturneSkillSdkFileMutexState,base)==52,"SDK base52");
_Static_assert(sizeof(NocturneSkillSdkFileMutexPreview)==1336,"SDK preview1336");
_Static_assert(offsetof(NocturneSkillSdkFileMutexPreview,record)==1256,"SDK record1256");
_Static_assert(offsetof(NocturneSkillSdkFileMutexPreview,seal)==1328,"SDK seal1328");
uint32_t nocturneSkillSdkFileMutexInit(NocturneSkillSdkFileMutexState *);
uint32_t nocturneSkillSdkFileMutexPreview(const NocturneSkillSdkFileMutexState *,NocturneSkillWorkerBootstrapPolicyReadBytes,void *,uint64_t,uint32_t,uint32_t,const uint64_t *,NocturneSkillSdkFileMutexPreview *);
uint32_t nocturneSkillSdkFileMutexCommit(NocturneSkillSdkFileMutexState *,const NocturneSkillSdkFileMutexPreview *);
uint32_t nocturneSkillSdkFileMutexIsStop(uint32_t);
/* Pure preview has no global busy state: future transport must hold its existing
 * reentry guard, compare fixed records and preflight traces BEFORE Commit. */
#endif
