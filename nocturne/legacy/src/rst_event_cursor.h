#ifndef NOCTURNE_RST_EVENT_CURSOR_H
#define NOCTURNE_RST_EVENT_CURSOR_H
#include "rst_level_chain.h"
#include "unit_batch.h"

/* Partial view of the same original551F88 owner. No allocation claim.
 * All result views share one backing allocation. Embedded addresses remain32bits. */
typedef struct rstCursorWork_PS2 {
    uint8_t unknown_0000[0x1c];
    uint32_t event_address;
    int8_t event_count, event_index;
    uint16_t proposed_skill;
    uint8_t unknown_0024[0x72-0x24];
    int8_t stock_cursor;
    uint8_t unknown_0073[0x16c-0x73];
    uint32_t unit_address;
    datUnitWork_PS2 preview;
} rstCursorWork_PS2;
_Static_assert(offsetof(rstCursorWork_PS2,event_address)==0x1c,"event address32");
_Static_assert(offsetof(rstCursorWork_PS2,event_index)==0x21,"event byte index");
_Static_assert(offsetof(rstCursorWork_PS2,stock_cursor)==0x72,"signed stock cursor");
_Static_assert(offsetof(rstCursorWork_PS2,unit_address)==0x16c,"unit address32");
_Static_assert(offsetof(rstCursorWork_PS2,preview)==0x170,"inline preview");
extern rstCursorWork_PS2 *g_rstCursorWork;

int32_t rstChkLevelUpTarget(const datUnitWork_PS2 *unit);
int8_t rstChkResultEntry(void);
uint8_t rstCalcLevelFromExp(uint8_t index,uint32_t exp);
uint32_t rstCalcExpFromLevel(uint8_t index,int32_t level);
int8_t rstSetCurrentDevil(void);
int8_t rstCalcEventInfo(uint16_t *parameter);
int8_t rstGetDefaultSkill(void);

/* Original-instruction evidence is versioned independently from this source.
 * EXP/copy/resource contracts apply only on paths which read those owners.
 * Physical index0..15; stock cursor0..16, signed list entries negative or0..15.
 * Current unit may be exact preview self or a backed physical/standalone unit.
 * Event addresses and both signed-index accesses must select complete backed
 * four-byte records in the existing demon-event owner, including any cross-row
 * accesses actually permitted by the original byte arithmetic. Output is NULL
 * or a complete aligned ushort; proposal22 alias allowed, pointer/count/index
 * fields and dependency tables cannot overlap output. No cursor/count clamp.
 */
#endif
