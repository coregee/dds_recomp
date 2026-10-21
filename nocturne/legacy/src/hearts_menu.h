#ifndef NOCTURNE_HEARTS_MENU_H
#define NOCTURNE_HEARTS_MENU_H

/* Partial views for SLUS_209.11.
 * Reuse the established unit/global/Hearts/position views and dependencies.
 * No managed HD layout or table constants are used here. */
#include "nocturne.h"

typedef struct rstSkillInfo_PS2 {
    int8_t skillcnt;
    uint8_t target_level[24];
    uint8_t unknown_19;
    uint16_t skill[24];
} rstSkillInfo_PS2;

/* Packed row at00333cf8+unitID*102. The prefix is not read by these routines;
 * the HD reference calls it GrowParamTbl, but retain it as unknown here. */
typedef struct cmbDemonSkillEntry_PS2 {
    int8_t level;
    uint8_t type;
    uint16_t skill;
} cmbDemonSkillEntry_PS2;
typedef struct cmbDemonSkillRow_PS2 {
    uint8_t unknown_00[6];
    cmbDemonSkillEntry_PS2 entries[24];
} cmbDemonSkillRow_PS2;

/* Names/types correspond to the reviewed HD fields; offsets and raw writes
 * come from PS2 instructions. Padding is deliberately exposed and preserved. */
typedef struct cmpHeartsIcon_PS2 {
    int8_t stat, icon_type;
    uint8_t unknown_02[2];
    uint32_t icon_color;
    int8_t move_type, axis;
    uint8_t unknown_0a[2];
    int32_t axis_chg, wait1st, wait;
    float angle, def_ang, dist_ang;
    int32_t def_cnt, cnt, timer, timer_spd;
} cmpHeartsIcon_PS2;

/* Selected menu fields only. This extent covers the25 initialized icons and
 * is not a recovered allocation size for the complete menu work. */
typedef struct cmpDataDH_PS2 {
    uint8_t unknown_0000[0x31];
    int8_t select_pos;
    uint8_t unknown_0032[0x1278 - 0x32];
    cmpHeartsIcon_PS2 hearts_icon[25];
} cmpDataDH_PS2;

enum { PS2_HEARTS_EQUIPPED_OFFSET = 0x1cfa };

_Static_assert(sizeof(rstSkillInfo_PS2) == 0x4a, "future-skill info extent");
_Static_assert(offsetof(rstSkillInfo_PS2, target_level) == 1, "future skill levels");
_Static_assert(offsetof(rstSkillInfo_PS2, skill) == 0x1a, "future skill IDs");
_Static_assert(sizeof(cmbDemonSkillEntry_PS2) == 4, "demon skill entry stride");
_Static_assert(offsetof(cmbDemonSkillEntry_PS2, type) == 1, "demon event type");
_Static_assert(offsetof(cmbDemonSkillEntry_PS2, skill) == 2, "demon skill ID");
_Static_assert(sizeof(cmbDemonSkillRow_PS2) == 102, "demon skill row stride");
_Static_assert(offsetof(cmbDemonSkillRow_PS2, entries) == 6, "demon skill entries");
_Static_assert(sizeof(cmpHeartsIcon_PS2) == 0x34, "Hearts icon stride");
_Static_assert(offsetof(cmpHeartsIcon_PS2, icon_color) == 4, "icon color");
_Static_assert(offsetof(cmpHeartsIcon_PS2, move_type) == 8, "icon movement type");
_Static_assert(offsetof(cmpHeartsIcon_PS2, axis_chg) == 0xc, "icon axis change");
_Static_assert(offsetof(cmpHeartsIcon_PS2, wait1st) == 0x10, "icon first wait");
_Static_assert(offsetof(cmpHeartsIcon_PS2, wait) == 0x14, "icon wait");
_Static_assert(offsetof(cmpHeartsIcon_PS2, angle) == 0x18, "icon angle");
_Static_assert(offsetof(cmpHeartsIcon_PS2, def_ang) == 0x1c, "icon default angle");
_Static_assert(offsetof(cmpHeartsIcon_PS2, dist_ang) == 0x20, "icon distance angle");
_Static_assert(offsetof(cmpHeartsIcon_PS2, def_cnt) == 0x24, "icon default count");
_Static_assert(offsetof(cmpHeartsIcon_PS2, cnt) == 0x28, "icon count");
_Static_assert(offsetof(cmpHeartsIcon_PS2, timer) == 0x2c, "icon timer");
_Static_assert(offsetof(cmpHeartsIcon_PS2, timer_spd) == 0x30, "icon timer speed");
_Static_assert(offsetof(cmpDataDH_PS2, select_pos) == 0x31, "Hearts selection");
_Static_assert(offsetof(cmpDataDH_PS2, hearts_icon) == 0x1278, "Hearts icon array");
_Static_assert(sizeof(cmpDataDH_PS2) == 0x178c, "partial Hearts menu extent");
_Static_assert(PS2_HEARTS_EQUIPPED_OFFSET < sizeof(datGlobalWork_PS2),
    "equipped byte inside established global view");

/* Host binding supplies immutable PS2 table bytes starting at00333cf8, not the distinct
 * datDevilSkillRecord_PS2 table at003497c0. The logical row count is unproved;
 * the caller must supply a backing row for every nonzero unit->id it uses.
 * Logical table capacity is unproved; each accessed row must be backed. */
extern const cmbDemonSkillRow_PS2 *g_cmbDemonSkillRows;

/* Existing bindings required through nocturne.h:
 * g_datGlobalWork (slot0054ea20): units[0] at+a54, equipped byte at+1cfa,
 * ownership list/count at+1cfb/+1d7b, skill-state bytes at+1d3b;
 * g_cmbHeartsRecords: table00339e00, stride66; flag at+0;
 * g_cmpHeartsPositions: table00345e58,27 consumed stride8 rows;
 * g_sdfDefaultState: default four-word RNG at00529bd8, via sdfGetRand(NULL).
 * Existing callees: cmbGetHeartsAfterSkillNums, cmbChkSkillOwner,
 * cmpGetHeartsFromPos, cmpGetHeartsIconTypeFromPos,
 * cmpGetHeartsIconColorFromPos, cmpChkHaveHearts, evtBitCheck, sdfGetRand.
 *
 * Inferred caller contracts: logical descriptor IDs0..25; valid referenced
 * demon rows; unit skill counts within the established24-slot view; output
 * info/menu pointers valid and not overlapping unit/table/global inputs.
 * NULL unit is handled by the builder; it then leaves even output count alone.
 * The menu routines require g_datGlobalWork and25 icon payloads. The selection
 * routine consumes all27 position rows, including physical IDs26/27. */
uint8_t cmbChkHeartsStat(int8_t id);
void rstCreateBeforeSkillList(int8_t id, datUnitWork_PS2 *unit,
    int8_t level_offset, rstSkillInfo_PS2 *info);
void cmpSetEquipHeartsSelectPos(cmpDataDH_PS2 *data);
void cmpInitHeartsIcon(cmpDataDH_PS2 *data);

#endif
