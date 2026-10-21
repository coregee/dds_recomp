#ifndef NOCTURNE_UNIT_NEIGHBORS_H
#define NOCTURNE_UNIT_NEIGHBORS_H

/* Recovered unit construction/evolution, with existing table bindings. */
#include "stat_neighbors.h"
#include "rst_stats.h"

/* Extra proved fields of the existing003497c0/stride3c descriptor. Reads use
 * its byte representation instead of aliasing the existing binding type. */
typedef struct cmbUnitDevilView_PS2 {
    uint8_t unknown_00[5];
    uint8_t level;
    uint8_t unknown_06[10];
    int8_t default_param[6];
    uint8_t unknown_16[0x26];
} cmbUnitDevilView_PS2;

_Static_assert(sizeof(cmbUnitDevilView_PS2) == 0x3c, "demon descriptor stride");
_Static_assert(sizeof(cmbUnitDevilView_PS2) == sizeof(datDevilSkillRecord_PS2),
    "existing descriptor binding extent");
_Static_assert(offsetof(cmbUnitDevilView_PS2, level) == 5, "descriptor level");
_Static_assert(offsetof(cmbUnitDevilView_PS2, default_param) == 0x10,
    "descriptor default parameters");

/* Chosen aliases: no reviewed distinct native declaration for the level-
 * filtered builder; the clear's native array dimensions are protected. */
void ps2CreateLevelSkill(uint16_t devil_id, uint8_t level,
    datUnitWork_PS2 *unit);
void ps2ClearUnitWork(datUnitWork_PS2 *unit);

int8_t cmbChkEvoAttention(const datUnitWork_PS2 *unit);
int8_t cmbChkCancelEvo(const datUnitWork_PS2 *unit);
int8_t cmbChkDevilEvo(const datUnitWork_PS2 *unit);
int8_t cmbGetDevilEvoLevel(const datUnitWork_PS2 *unit);
void cmbCopyDefaultDevilToStock(uint16_t devil_id, datUnitWork_PS2 *unit);
void cmbCopyEvoDevilToStock(datUnitWork_PS2 *unit,
    const datUnitWork_PS2 *evolved_unit);

/* Require valid4-byte-aligned full units and backed descriptor/event rows.
 * Existing immutable tables must not overlap mutable unit buffers. Skill
 * counts must fit24 slots; no new capacity/NULL/index fallback is added.
 * Copy inputs are disjoint or exact self-alias; arbitrary partial overlap
 * and byte misalignment remain outside the current comparison contract. */
#endif
