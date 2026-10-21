#ifndef NOCTURNE_STOCK_COMPACTION_H
#define NOCTURNE_STOCK_COMPACTION_H

/* PS2-only semantic name; no supported native HD identity was established. */
#include "unit_neighbors.h"

_Static_assert(sizeof(datUnitWork_PS2) == 0xec, "original stock stride");
_Static_assert(offsetof(datUnitWork_PS2, id) == 4, "selection reads ushort ID");
_Static_assert(sizeof(((datUnitWork_PS2 *)0)->id) == 2, "unsigned ID read");

/* 001ff0c8. Back count complete, four-byte-aligned consecutive EC-byte units.
 * Count is unsigned8; count0 permits NULL and performs no unit/table access.
 * Every moved source must satisfy cmbCopyCustomDevilToStock's real resource
 * dependency contracts: valid skill backing/count and any selected descriptor
 * row. No partial record overlap is introduced: copies target distinct earlier
 * array elements. Unmoved records do not invoke resource copy or clearing.
 * No global stock-list/count repair or full zero-fill of the tail is performed.
 */
void ps2CompactStockUnits(datUnitWork_PS2 *units, uint8_t count);

#endif
