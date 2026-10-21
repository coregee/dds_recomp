#ifndef NOCTURNE_UNIT_BATCH_H
#define NOCTURNE_UNIT_BATCH_H

/* Isolated drafts for thirteen reviewed SLUS_209.11 routines. Existing
 * canonical headers supply every unit, table, binding and dependency. */
#include "unit_neighbors.h"
#include "ps2_memory.h"
#include <limits.h>

enum {
    PS2_UNIT_BATCH_INSERT_SKILLS = 8,
    PS2_UNIT_BATCH_INHERITED_SKILLS = 24,
    PS2_UNIT_BATCH_INHERITED_BYTES = 48
};

_Static_assert(CHAR_BIT == 8, "eight-bit byte representation");
_Static_assert(INT8_MIN == -128 && INT8_MAX == 127, "signed byte range");
_Static_assert(UINT16_MAX == 65535, "unsigned halfword range");
_Static_assert(sizeof(datUnitWork_PS2) == 0xec, "stock unit stride");
_Static_assert(offsetof(datUnitWork_PS2, flag) == 0, "whole stock flag word");
_Static_assert(offsetof(datUnitWork_PS2, id) == 4, "stock ID offset");
_Static_assert(offsetof(datUnitWork_PS2, level) == 0x14, "unit level offset");
_Static_assert(offsetof(datUnitWork_PS2, skillcnt) == 0x38, "normal skill count");
_Static_assert(sizeof(((datUnitWork_PS2 *)0)->skillcnt) == 2,
    "unsigned normal skill count store");
_Static_assert(offsetof(datUnitWork_PS2, skill) == 0x3a, "normal skill slots");
_Static_assert(offsetof(datUnitWork_PS2, keisyoskill) == 0x86,
    "inherited skill slots");
_Static_assert(sizeof(((datUnitWork_PS2 *)0)->keisyoskill)
    == PS2_UNIT_BATCH_INHERITED_BYTES, "24 inherited halfwords");
_Static_assert(offsetof(datUnitWork_PS2, keiattr) == 0xb6,
    "attribute bytes after inherited skills");
_Static_assert(offsetof(datGlobalWork_PS2, stock_list) == 0x1914,
    "global byte stock list");
_Static_assert(sizeof(((datGlobalWork_PS2 *)0)->stock_list) == 16,
    "established stock-list backing");
_Static_assert(offsetof(datGlobalWork_PS2, stock_count) == 0x1924,
    "global signed stock count");
_Static_assert(sizeof(((datGlobalWork_PS2 *)0)->stock_count) == 4,
    "32-bit stock count store");
_Static_assert(sizeof(datDevilSkillRecord_PS2) == 0x3c,
    "existing immutable descriptor stride");
_Static_assert(offsetof(datDevilSkillRecord_PS2, unknown_00) == 0,
    "descriptor flag bytes at zero");
_Static_assert(sizeof(((datDevilSkillRecord_PS2 *)0)->unknown_00) == 4,
    "descriptor flag word backing");
_Static_assert(offsetof(datDevilSkillRecord_PS2, race) == 4,
    "descriptor race byte");
_Static_assert(sizeof(cmbDemonSkillRow_PS2) == 102, "event row stride");
_Static_assert(offsetof(cmbDemonSkillRow_PS2, entries) == 6,
    "event entries after prefix");
_Static_assert(sizeof(cmbDemonSkillEntry_PS2) == 4, "event entry stride");
_Static_assert(offsetof(cmbDemonSkillEntry_PS2, level) == 0,
    "raw event level byte");
_Static_assert(sizeof(((cmbDemonSkillRow_PS2 *)0)->entries) == 24 * 4,
    "24 event entries");

/* Require complete four-byte-aligned units and backing for every accessed
 * immutable descriptor/event/rate row. No new tables or host bindings exist.
 * Tables cannot overlap mutable unit, list or event-count output storage.
 * Pure lookups allow NULL stock at count0; otherwise back count EC-byte units.
 * Count is unsigned8, independent of the global16-unit capacity, and lookup
 * results are signed low8 indexes. Normal counts consumed by cmbAddSkill and
 * existing custom-copy dependencies must initially fit24 slots. */
int8_t cmbGetKeisyoSkillEndIndex(const datUnitWork_PS2 *unit);
void cmbClearKeisyoSkill(datUnitWork_PS2 *unit);
int8_t cmbAddSkill(uint16_t skill, datUnitWork_PS2 *unit);
int8_t cmbGetEmptyStockIndex(const datUnitWork_PS2 *units, uint8_t count);
int8_t cmbGetStockDevilIndex(uint16_t devil_id,
    const datUnitWork_PS2 *units, uint8_t count);

/* Append needs global count0..15. Deletion needs count1..16 when positive;
 * zero/negative counts perform only the wrapped decrement. Count>=128 can
 * make the original signed-byte loop nonterminating; any access beyond the
 * established16-byte list is outside this implementation's contract. Deletion always
 * decrements once and does not clear the stale tail or repair duplicates. */
void cmbDeleteUnitFromStockList(int8_t unit_index);
void cmbAddUnitToStockList(int8_t unit_index);

/* Successful wrappers require the applicable list backing and real copy/
 * clear dependencies. The original relative list byte is index-count+16;
 * there is no PS2 top/offset argument. Failed insertion does not read source,
 * and count0 permits NULL units/source. Copies support complete disjoint units
 * or exact self-alias, including source equal to another stock record; partial
 * byte overlap and arbitrary byte misalignment remain excluded. */
int8_t cmbDeleteDevilFromStock(uint16_t devil_id,
    datUnitWork_PS2 *units, uint8_t count);
int8_t cmbAddDefaultDevilToStock(uint16_t devil_id,
    datUnitWork_PS2 *units, uint8_t count);
int8_t cmbAddCustomDevilToStock(const datUnitWork_PS2 *source,
    datUnitWork_PS2 *units, uint8_t count);
int32_t cmbCalcTotalKeisyoSkillRate(const datUnitWork_PS2 *unit);

/* Event query returns the first matching inline entry or NULL. It stores
 * count0..24 to the optional byte output after all unit/table reads. That
 * output may alias one mutable unit byte; no restrict promise is made. */
const cmbDemonSkillEntry_PS2 *cmbChkLevelUpEvent(
    const datUnitWork_PS2 *unit, int8_t *event_count);
int8_t cmbChkIkenieIllegalDevil(uint16_t devil_id);

#endif
