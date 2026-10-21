#ifndef NOCTURNE_SKILL_SIF_DMAC_POLICY_H
#define NOCTURNE_SKILL_SIF_DMAC_POLICY_H
#include <stdint.h>
#include <stddef.h>
/* Explicit external device inputs. No implicit boot/reset/IOP state. */
typedef struct NocturneSkillSifDmacConfig { uint32_t version,d_stat,d5_chcr,reserved; } NocturneSkillSifDmacConfig;
typedef struct NocturneSkillSifDmacState {
    uint32_t version,stage,accepted_count,event_limit;
    NocturneSkillSifDmacConfig initial;
    uint32_t d_stat,d5_chcr,reserved0,reserved1;
} NocturneSkillSifDmacState;
typedef struct NocturneSkillSifDmacEvent {
    uint32_t version,ordinal,kind,pc,address,width,value,before,after,reserved;
} NocturneSkillSifDmacEvent;
typedef struct NocturneSkillSifDmacPreview {
    uint32_t version,reserved;
    NocturneSkillSifDmacState before,proposed;
    NocturneSkillSifDmacEvent event;
    uint64_t seal;
} NocturneSkillSifDmacPreview;
typedef struct NocturneSkillSifDmacSession {
    NocturneSkillSifDmacState state;
    uint32_t busy,reserved;
    uint64_t token;
} NocturneSkillSifDmacSession;
enum { NOCTURNE_SIF_DMAC_READ32=1,NOCTURNE_SIF_DMAC_WRITE32=2 };
enum { NOCTURNE_SIF_DMAC_API=1,NOCTURNE_SIF_DMAC_STATE=2,NOCTURNE_SIF_DMAC_ORDER=3,
    NOCTURNE_SIF_DMAC_PC=4,NOCTURNE_SIF_DMAC_ADDRESS=5,NOCTURNE_SIF_DMAC_WIDTH=6,
    NOCTURNE_SIF_DMAC_VALUE=7,NOCTURNE_SIF_DMAC_BUDGET=8,NOCTURNE_SIF_DMAC_TRANSACTION=9,
    NOCTURNE_SIF_DMAC_REENTERED=10 };
_Static_assert(sizeof(NocturneSkillSifDmacConfig)==16,"DMAC config16");
_Static_assert(sizeof(NocturneSkillSifDmacState)==48,"DMAC state48");
_Static_assert(sizeof(NocturneSkillSifDmacEvent)==40,"DMAC event40");
_Static_assert(sizeof(NocturneSkillSifDmacPreview)==152,"DMAC preview152");
_Static_assert(sizeof(NocturneSkillSifDmacSession)==64,"DMAC session64");
uint32_t nocturneSkillSifDmacInit(NocturneSkillSifDmacState *,const NocturneSkillSifDmacConfig *);
uint32_t nocturneSkillSifDmacPreview(const NocturneSkillSifDmacState *,uint32_t kind,uint32_t pc,uint32_t address,uint32_t width,uint32_t write_value,NocturneSkillSifDmacPreview *);
uint32_t nocturneSkillSifDmacCommit(NocturneSkillSifDmacState *,const NocturneSkillSifDmacPreview *);
/* Optional reservation wrapper: no device state changes until CommitReserved.
 * Transport must preflight fixed events/trace capacity before commit; cancel
 * the reservation on rejection. Never cast these values into fake RAM pointers. */
uint32_t nocturneSkillSifDmacSessionInit(NocturneSkillSifDmacSession *,const NocturneSkillSifDmacConfig *);
uint32_t nocturneSkillSifDmacReserve(NocturneSkillSifDmacSession *,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,NocturneSkillSifDmacPreview *);
uint32_t nocturneSkillSifDmacCommitReserved(NocturneSkillSifDmacSession *,const NocturneSkillSifDmacPreview *);
uint32_t nocturneSkillSifDmacCancel(NocturneSkillSifDmacSession *,const NocturneSkillSifDmacPreview *);
#endif
