#ifndef NOCTURNE_BATTLE_FORMATION_PRINTF_CANDIDATE_H
#define NOCTURNE_BATTLE_FORMATION_PRINTF_CANDIDATE_H
#include <stdint.h>
/* SOURCE-ONLY candidate, not wired into Formation, a probe or canonical build.
 * Publish only source-defined A0/SP/RA for fixed literal diagnostic sites.
 * Existing actual native printf owns every guest-frame write and return. */
#define NOCTURNE_FORMATION_PRINTF_CANDIDATE_GPR_MASK UINT32_C(0xa0000010)
#define NOCTURNE_FORMATION_PRINTF_CANDIDATE_FPR_MASK UINT32_C(0)
uint64_t nocturneFormationPrintfCandidate(uint32_t call_pc,uint64_t format,
    uint64_t source_sp,uint64_t source_ra);
#endif
