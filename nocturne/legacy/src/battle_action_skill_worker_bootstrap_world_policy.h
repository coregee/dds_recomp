#ifndef NOCTURNE_SKILL_WORKER_BOOTSTRAP_WORLD_POLICY_H
#define NOCTURNE_SKILL_WORKER_BOOTSTRAP_WORLD_POLICY_H
#include "battle_action_skill_worker_kernel_v2.h"
#include <stdint.h>
#include <stddef.h>

enum {
    NOCTURNE_SKILL_WORKER_POLICY_OK=0,
    NOCTURNE_SKILL_WORKER_POLICY_UNSUPPORTED=1,
    NOCTURNE_SKILL_WORKER_POLICY_BLOCKED=2,
    NOCTURNE_SKILL_WORKER_POLICY_FULL=3,
    NOCTURNE_SKILL_WORKER_POLICY_BUDGET=4,
    NOCTURNE_SKILL_WORKER_POLICY_EXTRA_CREATE=5,
    NOCTURNE_SKILL_WORKER_POLICY_PACKET=6,
    NOCTURNE_SKILL_WORKER_POLICY_RESTART=7,
    NOCTURNE_SKILL_WORKER_POLICY_API=0x100,
    NOCTURNE_SKILL_WORKER_POLICY_CONTRACT=0x101,
    NOCTURNE_SKILL_WORKER_POLICY_DOMAIN=0x102,
    NOCTURNE_SKILL_WORKER_POLICY_MEMORY=0x103,
    NOCTURNE_SKILL_WORKER_POLICY_STATE=0x104,
    NOCTURNE_SKILL_WORKER_POLICY_TRANSACTION=0x105
};
#define NOCTURNE_SKILL_WORKER_POLICY_LIMIT 4096u
/* Read only actual authored physical guest bytes. The callback must fill all
 * requested bytes and return1, or return0; it must never patch guest state. */
typedef uint32_t (*NocturneSkillWorkerBootstrapPolicyReadBytes)(
    void *context,uint32_t physical,uint32_t size,uint8_t *output);

/* Version1, distinct from the historical68B heap state. All fields are raw
 * host observation/policy metadata. Semaphore slots are7,10,21,22,23,24;
 * packet slots are21,22,23,24. A registered thread remains unexecuted. */
typedef struct NocturneSkillWorkerBootstrapPolicyState {
    uint32_t version,accepted_count,created_heap_semaphores,created_worker_semaphores;
    uint32_t present[6],counts[6],max_counts[6];
    uint32_t thread_created,thread_start_registered;
    uint32_t semaphore_packet_addresses[4];
    uint8_t semaphore_packets[4][24];
    uint32_t thread_packet_address,worker_stack;
    uint8_t thread_packet[48];
} NocturneSkillWorkerBootstrapPolicyState;

/* Preview changes neither input state nor guest bytes. Transport compares its
 * fixed candidate and preflights record/event/trace capacity before Commit.
 * The integrity seal detects accidental preview mutation, not hostile code. */
typedef struct NocturneSkillWorkerBootstrapPolicyPreview {
    uint32_t version,reserved;
    NocturneSkillWorkerBootstrapPolicyState before,proposed;
    NocturneSkillWorkerKernelInputV2 record;
    uint64_t seal;
} NocturneSkillWorkerBootstrapPolicyPreview;
_Static_assert(sizeof(NocturneSkillWorkerBootstrapPolicyState)==264,"Policy state V1 size");
_Static_assert(sizeof(NocturneSkillWorkerBootstrapPolicyPreview)==616,"Policy preview V1 size");
_Static_assert(offsetof(NocturneSkillWorkerBootstrapPolicyPreview,record)==536,"Preview V2 record");
_Static_assert(offsetof(NocturneSkillWorkerBootstrapPolicyPreview,seal)==608,"Preview seal");

uint32_t nocturneSkillWorkerBootstrapPolicyInit(NocturneSkillWorkerBootstrapPolicyState *);
uint32_t nocturneSkillWorkerBootstrapPolicyPreview(
    const NocturneSkillWorkerBootstrapPolicyState *,
    NocturneSkillWorkerBootstrapPolicyReadBytes,void *reader_context,
    uint64_t selector,uint32_t pc,uint32_t argc,const uint64_t *arguments,
    NocturneSkillWorkerBootstrapPolicyPreview *);
uint32_t nocturneSkillWorkerBootstrapPolicyCommit(NocturneSkillWorkerBootstrapPolicyState *,
    const NocturneSkillWorkerBootstrapPolicyPreview *);
uint32_t nocturneSkillWorkerBootstrapPolicyIsStop(uint32_t code);
/* Normal-session invariant only for heap7/21/22 and registry10. It never
 * treats deferred manager/worker semaphore counts as worker completion. */
uint32_t nocturneSkillWorkerBootstrapPolicyHeapBalanced(const NocturneSkillWorkerBootstrapPolicyState *);
#endif
