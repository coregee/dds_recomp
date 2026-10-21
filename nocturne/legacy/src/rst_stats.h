#ifndef NOCTURNE_RST_STATS_H
#define NOCTURNE_RST_STATS_H

/* SLUS_209.11 routines.
 * Reuse the existing inline PS2 views and menu-list declaration. */
#include "hearts_menu.h"

/* Caller contracts: valid global/table bindings; logical Hearts IDs0..25;
 * unit parameter indexes0..5; valid complete unit objects. The tier output
 * alone may be NULL. Copy source/destination are4-byte aligned (residues0
 * or4 modulo8), with disjoint buffers or exact self-alias. Arbitrary byte
 * misalignment and partial overlap are outside the comparison contract.
 * No new index or unit-null behavior is added. */
uint8_t cmbChkMasterHeartsStatNums(uint8_t *tier);
uint8_t cmbGetPlayerRaceID(datUnitWork_PS2 *unused_unit);
int32_t cmbGetParamBase(datUnitWork_PS2 *unit, int32_t index);
int32_t cmbGetParam(datUnitWork_PS2 *unit, int32_t index);
void cmbCopyCustomDevilToStock(datUnitWork_PS2 *destination,
    const datUnitWork_PS2 *source);
/* Non-NULL unit required: the original NULL path reads uninitialized scratch. */
int8_t rstChkBeforeSkillOwner(uint16_t skill, int8_t level_offset,
    datUnitWork_PS2 *unit);

#endif
