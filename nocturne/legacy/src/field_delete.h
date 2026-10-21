#ifndef NOCTURNE_FIELD_DELETE_H
#define NOCTURNE_FIELD_DELETE_H

#include "field_neighbors.h"

_Static_assert(offsetof(datUnitWork_PS2, param) == 0x16,
               "selected signed parameter byte offset");
_Static_assert(offsetof(datUnitWork_PS2, id) == 4, "selected unsigned ID offset");
_Static_assert(offsetof(datUnitWork_PS2, hp) == 6, "eligibility HP offset");
_Static_assert(sizeof(datUnitWork_PS2) == 0xec, "fixed scan stride");
_Static_assert(offsetof(datGlobalWork_PS2, event_bits) == 0x840,
               "real event-bit dependency offset");

/* Stable, word-aligned, complete original global-work backing; distinct field
 * state binding. Use a fixed sixteen-unit scan bound, stopping at the selected
 * ordinal, without a stored count gate.
 * Eligibility is flag1 set, flags4/10/800 clear, HP nonzero. Negative/stale
 * indices simply fail the bounded ordinal scan; no index repair is added.
 *
 * Before removing the selected ID, signed param[0] >=21 sets event bit0x504,
 * then the original work binding is reloaded for the selected ID read. A failed
 * stock removal does not undo the event bit. State index/count remain untouched.
 * The real datDelDevil/stock-list/packing dependencies execute; deletion is by
 * first listed ID match, which can differ from the selected physical record.
 * Their ordinary backed list contracts apply: positive count at most 16 and
 * all used byte indexes in 0..15; nonpositive counts take the no-removal path.
 * No fabricated NULL fallback, aliasing globals, device or concurrent contract.
 * This int32 interface preserves PS2 V0 removal success 0/1 rather than proving
 * the historical declared return type; its HD counterpart declares void.
 * The script wrapper ignores that value and always returns 1. */
int32_t fldAnahoriSelectDel(void);
int32_t fldCommand_FLD_ANAHORI_DEL(void);

#endif
