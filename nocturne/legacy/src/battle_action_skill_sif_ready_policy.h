#ifndef NOCTURNE_SKILL_SIF_READY_POLICY_H
#define NOCTURNE_SKILL_SIF_READY_POLICY_H
#include "battle_action_skill_sif_kernel_policy.h"
/* Explicit current D_STAT and readonly software-word inputs, not fixed replies. */
typedef struct NocturneSkillSifReadyConfig { uint32_t version,d_stat,software_reg0,reserved; } NocturneSkillSifReadyConfig;
typedef struct NocturneSkillSifReadyState { NocturneSkillSifReadyConfig initial;uint32_t version,stage,accepted_count,d_stat; } NocturneSkillSifReadyState;
typedef NocturneSkillSifKernelRequest NocturneSkillSifReadyRequest;
typedef NocturneSkillSifKernelReceipt NocturneSkillSifReadyReceipt;
typedef struct NocturneSkillSifReadyPreview {
    uint32_t version,reserved;NocturneSkillSifReadyState before,proposed;
    NocturneSkillSifReadyRequest request;NocturneSkillSifReadyReceipt receipt;uint64_t seal;
} NocturneSkillSifReadyPreview;
typedef struct NocturneSkillSifReadySession { NocturneSkillSifReadyState state;uint32_t busy,reserved;uint64_t token; } NocturneSkillSifReadySession;
enum { NOCTURNE_SIF_READY_API=1,NOCTURNE_SIF_READY_STATE=2,NOCTURNE_SIF_READY_ORDER=3,NOCTURNE_SIF_READY_REQUEST=4,
    NOCTURNE_SIF_READY_UNSUPPORTED=5,NOCTURNE_SIF_READY_TRANSACTION=6,NOCTURNE_SIF_READY_REENTERED=7,NOCTURNE_SIF_READY_BUDGET=8 };
_Static_assert(sizeof(NocturneSkillSifReadyConfig)==16,"ready config16");
_Static_assert(sizeof(NocturneSkillSifReadyState)==32,"ready state32");
_Static_assert(sizeof(NocturneSkillSifReadyPreview)==600,"ready preview600");
_Static_assert(sizeof(NocturneSkillSifReadySession)==48,"ready session48");
uint32_t nocturneSkillSifReadyInit(NocturneSkillSifReadyState *,const NocturneSkillSifReadyConfig *);
uint32_t nocturneSkillSifReadyPreview(const NocturneSkillSifReadyState *,const NocturneSkillSifReadyRequest *,NocturneSkillSifReadyPreview *);
uint32_t nocturneSkillSifReadyCommit(NocturneSkillSifReadyState *,const NocturneSkillSifReadyPreview *);
uint32_t nocturneSkillSifReadySessionInit(NocturneSkillSifReadySession *,const NocturneSkillSifReadyConfig *);
uint32_t nocturneSkillSifReadyReserve(NocturneSkillSifReadySession *,const NocturneSkillSifReadyRequest *,NocturneSkillSifReadyPreview *);
uint32_t nocturneSkillSifReadyCommitReserved(NocturneSkillSifReadySession *,const NocturneSkillSifReadyPreview *);
uint32_t nocturneSkillSifReadyCancel(NocturneSkillSifReadySession *,const NocturneSkillSifReadyPreview *);
/* Receipt CPUmask7 modifies low64 AT/V0/V1 only; caller merges live upper64.
 * Device kind1=read32,2=write32,3=external readonly software-table read32.
 * kind3 address8001E080 is kernel external state, never a fake guest RAM pointer.
 * Transport preflights all capacity/context then commits and publishes effects.
 * No CPU/RAM/MMIO publication, exception scratch, DMA or IOP work here. */
#endif
