#ifndef NOCTURNE_BATTLE_ACTION_SKILL_WORKER_KERNEL_V2_H
#define NOCTURNE_BATTLE_ACTION_SKILL_WORKER_KERNEL_V2_H
#include <stdint.h>
#include <stddef.h>

/* Separate external-input ABI. Never pass this record to the historical64B API.
 * There are no guest-memory patches, callback results or scheduler decisions. */
typedef struct NocturneSkillWorkerKernelInputV2 {
    uint64_t selector;
    uint32_t pc, argc;
    uint64_t arguments[3];
    uint64_t result;
    uint64_t v1_result[2];
    uint32_t output_flags, reserved;
} NocturneSkillWorkerKernelInputV2;
_Static_assert(sizeof(NocturneSkillWorkerKernelInputV2)==72,"Worker kernel V2 size");
_Static_assert(offsetof(NocturneSkillWorkerKernelInputV2,result)==40,"V2 result");
_Static_assert(offsetof(NocturneSkillWorkerKernelInputV2,v1_result)==48,"V2 V1");
_Static_assert(offsetof(NocturneSkillWorkerKernelInputV2,output_flags)==64,"V2 flags");
_Static_assert(offsetof(NocturneSkillWorkerKernelInputV2,reserved)==68,"V2 reserved");

/* Passive event context is a caller-selected host token, not a guest thread ID
 * inferred here. SetContext neither switches registers nor executes a callback. */
typedef struct NocturneSkillWorkerKernelEventV2 {
    NocturneSkillWorkerKernelInputV2 input;
    uint64_t context;
    uint32_t ordinal, status;
} NocturneSkillWorkerKernelEventV2;
uint32_t nocturneBattleActionSkillWorkerKernelBeginV2(const NocturneSkillWorkerKernelInputV2 *,uint32_t);
uint32_t nocturneBattleActionSkillWorkerKernelTakeV2(uint64_t,uint32_t,uint32_t,const uint64_t *,uint64_t *);
uint64_t nocturneBattleActionSkillWorkerKernelValueV2(uint64_t,uint32_t,uint32_t,const uint64_t *);
uint32_t nocturneBattleActionSkillWorkerKernelFinishV2(void);
uint32_t nocturneBattleActionSkillWorkerKernelFaultV2(void);
uint32_t nocturneBattleActionSkillWorkerKernelPositionV2(void);
uint32_t nocturneBattleActionSkillWorkerKernelTraceV2(uint32_t,NocturneSkillWorkerKernelInputV2 *);
uint32_t nocturneBattleActionSkillWorkerKernelSetContextV2(uint64_t);
uint32_t nocturneBattleActionSkillWorkerKernelEventV2(uint32_t,NocturneSkillWorkerKernelEventV2 *);
uint32_t nocturneBattleActionSkillWorkerKernelEnterV2(void);
uint32_t nocturneBattleActionSkillWorkerKernelCompleteV2(void);
/* Future isolated observer supplies these. No old observer/context is reused
 * implicitly, and no symbol is interposed by this unlinked unit. */
uint32_t nocturneBattleActionSkillWorkerObservationActiveV2(void);
_Noreturn void nocturneBattleActionSkillWorkerKernelRejectV2(void);
#endif
