#ifndef NOCTURNE_SKILL_SIF_KERNEL_POLICY_H
#define NOCTURNE_SKILL_SIF_KERNEL_POLICY_H
#include <stdint.h>
#include <stddef.h>
#include "battle_action_skill_worker_kernel_v2.h"
/* Explicit initial external kernel state. No implicit BIOS/reset values. */
typedef struct NocturneSkillSifKernelWord { uint32_t address,value; } NocturneSkillSifKernelWord;
typedef struct NocturneSkillSifKernelConfig {
    uint32_t version,d5_chcr,d5_qwc,reserved;
    NocturneSkillSifKernelWord words[14];
} NocturneSkillSifKernelConfig;
typedef struct NocturneSkillSifKernelState {
    NocturneSkillSifKernelConfig initial;
    uint32_t version,stage,accepted_count,event_limit;
    NocturneSkillSifKernelWord words[14];
    uint32_t d5_chcr,d5_qwc;
} NocturneSkillSifKernelState;
typedef struct NocturneSkillSifKernelRequest {
    uint64_t selector;
    uint32_t pc,argc;
    uint64_t arguments[3],a3,gp;
    uint32_t status,reserved;
    uint64_t v1_upper;
} NocturneSkillSifKernelRequest;
typedef struct NocturneSkillSifKernelWrite { uint32_t pc,address,before,after; } NocturneSkillSifKernelWrite;
typedef struct NocturneSkillSifKernelDeviceEffect { uint32_t kind,pc,address,before,after; } NocturneSkillSifKernelDeviceEffect;
enum { NOCTURNE_SIF_KERNEL_AT=0,NOCTURNE_SIF_KERNEL_V0,NOCTURNE_SIF_KERNEL_V1,
    NOCTURNE_SIF_KERNEL_A0,NOCTURNE_SIF_KERNEL_A1,NOCTURNE_SIF_KERNEL_A2,
    NOCTURNE_SIF_KERNEL_T0,NOCTURNE_SIF_KERNEL_HI,NOCTURNE_SIF_KERNEL_LO };
typedef struct NocturneSkillSifKernelReceipt {
    uint32_t version,ordinal,selector,pc;
    NocturneSkillWorkerKernelInputV2 record;
    uint32_t cpu_mask,memory_count,device_count,reserved;
    uint64_t cpu_low[9];
    NocturneSkillSifKernelWrite memory[12];
    NocturneSkillSifKernelDeviceEffect device[4];
} NocturneSkillSifKernelReceipt;
typedef struct NocturneSkillSifKernelPreview {
    uint32_t version,reserved;
    NocturneSkillSifKernelState before,proposed;
    NocturneSkillSifKernelRequest request;
    NocturneSkillSifKernelReceipt receipt;
    uint64_t seal;
} NocturneSkillSifKernelPreview;
typedef struct NocturneSkillSifKernelSession { NocturneSkillSifKernelState state;uint32_t busy,reserved;uint64_t token; } NocturneSkillSifKernelSession;
enum { NOCTURNE_SIF_KERNEL_API=1,NOCTURNE_SIF_KERNEL_STATE=2,NOCTURNE_SIF_KERNEL_ORDER=3,
    NOCTURNE_SIF_KERNEL_REQUEST=4,NOCTURNE_SIF_KERNEL_UNSUPPORTED=5,NOCTURNE_SIF_KERNEL_TRANSACTION=6,
    NOCTURNE_SIF_KERNEL_REENTERED=7,NOCTURNE_SIF_KERNEL_BUDGET=8 };
_Static_assert(sizeof(NocturneSkillSifKernelConfig)==128,"kernel config128");
_Static_assert(sizeof(NocturneSkillSifKernelState)==264,"kernel state264");
_Static_assert(sizeof(NocturneSkillSifKernelRequest)==72,"kernel request72");
_Static_assert(sizeof(NocturneSkillSifKernelReceipt)==448,"kernel receipt448");
_Static_assert(sizeof(NocturneSkillSifKernelPreview)==1064,"kernel preview1064");
_Static_assert(sizeof(NocturneSkillSifKernelSession)==280,"kernel session280");
uint32_t nocturneSkillSifKernelInit(NocturneSkillSifKernelState *,const NocturneSkillSifKernelConfig *);
uint32_t nocturneSkillSifKernelPreview(const NocturneSkillSifKernelState *,const NocturneSkillSifKernelRequest *,NocturneSkillSifKernelPreview *);
uint32_t nocturneSkillSifKernelCommit(NocturneSkillSifKernelState *,const NocturneSkillSifKernelPreview *);
uint32_t nocturneSkillSifKernelSessionInit(NocturneSkillSifKernelSession *,const NocturneSkillSifKernelConfig *);
uint32_t nocturneSkillSifKernelReserve(NocturneSkillSifKernelSession *,const NocturneSkillSifKernelRequest *,NocturneSkillSifKernelPreview *);
uint32_t nocturneSkillSifKernelCommitReserved(NocturneSkillSifKernelSession *,const NocturneSkillSifKernelPreview *);
uint32_t nocturneSkillSifKernelCancel(NocturneSkillSifKernelSession *,const NocturneSkillSifKernelPreview *);
/* Transport must preflight all trace/effect capacity before commit. These APIs
 * never write CPU, guest RAM or MMIO. Merge cpu_low only into low64; retain each
 * live upper64. record.v1_result includes the actual supplied V1 upper64. K0,
 * CP0 timing/exception scratch and BIOS private stack are outside this world. */
#endif
