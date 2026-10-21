#ifndef NOCTURNE_RST_RNG_FRONTIER_H
#define NOCTURNE_RST_RNG_FRONTIER_H

#include "rst_stats.h"
#include "stat_neighbors.h"
#include "inheritance_queries.h"

/* Recovered from complete original bodies; native names provide counterparts.
 * Behavior counts require a fresh original-instruction comparison.
 * Ordinary stable fully backed distinct table/global bindings are required.
 * Units must be complete, aligned objects. The three RNG drafts reuse existing
 * bindings; the partial result view below uses its original pointer slot.
 */
uint16_t rstRndGetPowerUpSkill(const datUnitWork_PS2 *unit, int8_t *index);
uint16_t cmbGetMutationSkill(uint16_t skill, datUnitWork_PS2 *unit);
int8_t cmbAddLevelUpParamEx(datUnitWork_PS2 *unit, int8_t mode);

/* Additional result-work view, proved only through the reads at002201A0.
 * This is an access extent, not a complete object or allocation size. */
typedef struct rstResourceWork_PS2 {
    uint8_t unknown_0000[0x26];
    int8_t refill_requested;
    uint8_t unknown_0027[0x129f - 0x27];
    uint8_t parameter_delta[6];
} rstResourceWork_PS2;
_Static_assert(offsetof(rstResourceWork_PS2, refill_requested) == 0x26,
    "original refill gate byte");
_Static_assert(offsetof(rstResourceWork_PS2, parameter_delta) == 0x129f,
    "original six parameter delta bytes");
_Static_assert(sizeof(rstResourceWork_PS2) == 0x12a5, "partial accessed extent");
/* Host adaptation for the original pointer slot00551F88. */
extern const rstResourceWork_PS2 *g_rstResourceWork;
void rstSetMaxHpMp(int8_t mode, datUnitWork_PS2 *unit);
/* Chosen descriptive alias; historical spelling is not established. */
int8_t ps2AddLevelUpParam(datUnitWork_PS2 *unit);

/* Resource update requires a complete aligned unit and distinct backed result,
 * descriptor and global objects. The real custom-copy/resource calls execute
 * with their original order; private scratch receives the parameter deltas.
 * Mode0 and a nonzero result flag refill current resources before final clamps.
 * Other paths update maxima and clamp existing current values. */

/* Power-up: the original unsigned16 normal skill count must be at most24.
 * The optional index byte may be NULL or alias writable unit storage. It is
 * written only after every candidate read and the actual RNG call, before
 * returning the selected scratch candidate. No candidates leave index/RNG
 * untouched. Duplicate upgrade candidates remain separate weighted entries.
 *
 * Mutation: the existing227-row inheritance level table and every dependency's
 * score/descriptor/skill backing must cover all drawn/original ushort IDs.
 * All64 attempts and actual RNG state changes are retained. No NULL-unit
 * contract is invented; the real ownership/rate dependencies execute.
 *
 * Parameter selection reads unsigned growth bytes from the six-byte demon
 * skill row prefix at00333cf8, or equipped Hearts row+12hex. Index1 is always
 * excluded. The real cmbGetParam low8 result equal40 also excludes a lane.
 * The supported deterministic interface requires that the minimum quotient
 * among eligible lanes is not-1: original excluded lanes have quotient-1 but
 * uninitialized private weights, which become observed if the minimum is-1.
 * Nonnegative signed level-up parameters satisfy that condition. No fallback
 * weight or memset of the original private arrays is introduced.
 * The caller must back the selected table row; tables must not alias mutable
 * unit/global/RNG backing. A nonzero mode skips the final parameter-byte write.
 * Return6 is possible after low8 cumulative-weight wrapping; no repair/clamp.
 */

#endif
