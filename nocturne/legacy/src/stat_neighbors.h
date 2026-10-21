#ifndef NOCTURNE_STAT_NEIGHBORS_H
#define NOCTURNE_STAT_NEIGHBORS_H

/* Partial inline PS2 views from the reviewed original instructions. */
#include "nocturne.h"
#include "hearts_menu.h"

/* New partial immutable skill view at003d6998, stride8. Logical capacity is
 * unproved; every requested ushort ID must have a backed entry. */
typedef struct cmbInheritanceSkillRecord_PS2 {
    int8_t attribute;
    uint8_t unknown_01[3];
    uint16_t form;
    uint8_t unknown_06[2];
} cmbInheritanceSkillRecord_PS2;

/* Additional known fields of the existing003497c0/stride3c demon table.
 * The C reads these via the byte representation of the existing
 * g_datDevilSkillTable binding, avoiding a second pointer/type alias. */
typedef struct cmbInheritanceDevilView_PS2 {
    uint8_t unknown_00[4];
    uint8_t race, level;
    uint8_t unknown_06[0x20];
    int16_t inheritance_type;
    uint16_t form;
    uint8_t unknown_2a[0x12];
} cmbInheritanceDevilView_PS2;

/* Fixed227-row rule table at00339658. Fourth byte remains unknown. */
typedef struct cmbInheritanceLevelRecord_PS2 {
    uint16_t skill;
    uint8_t level, unknown_03;
} cmbInheritanceLevelRecord_PS2;

enum {
    PS2_INHERITANCE_LEVEL_ROWS = 227,
    PS2_INHERITANCE_SCORE_BACKING_BYTES = 512
};

_Static_assert(sizeof(cmbInheritanceSkillRecord_PS2) == 8, "skill descriptor stride");
_Static_assert(offsetof(cmbInheritanceSkillRecord_PS2, attribute) == 0, "skill attribute");
_Static_assert(offsetof(cmbInheritanceSkillRecord_PS2, form) == 4, "skill form");
_Static_assert(sizeof(cmbInheritanceDevilView_PS2) == 0x3c, "demon descriptor stride");
_Static_assert(sizeof(cmbInheritanceDevilView_PS2) == sizeof(datDevilSkillRecord_PS2),
    "same backing as existing demon skill descriptor");
_Static_assert(offsetof(cmbInheritanceDevilView_PS2, level) == 5, "descriptor level");
_Static_assert(offsetof(cmbInheritanceDevilView_PS2, inheritance_type) == 0x26,
    "inheritance type");
_Static_assert(offsetof(cmbInheritanceDevilView_PS2, form) == 0x28, "demon form");
_Static_assert(sizeof(cmbInheritanceLevelRecord_PS2) == 4, "inheritance level stride");
_Static_assert(offsetof(cmbInheritanceLevelRecord_PS2, level) == 2, "inheritance level");

/* Host binding names, not recovered original symbols. The raw score backing
 * starts003399e8:13 legitimate17-short rows occupy442 bytes, followed by6
 * padding bytes and an adjacent table. Original missing-header paths can
 * read up to offset510, so require the entire512-byte span. Do not construct
 * an HD-style fallback or declare these adjacent bytes as extra score rows. */
extern const cmbInheritanceSkillRecord_PS2 *g_cmbInheritanceSkillRecords;
extern const cmbInheritanceLevelRecord_PS2 *g_cmbInheritanceLevelRecords;
extern const uint8_t *g_cmbInheritanceScoreBytes;

/* Dependencies from current canonical headers:
 * g_datDevilSkillTable at003497c0, stride3c;
 * g_cmbDemonSkillRows at00333cf8, stride102;
 * nocturne_break(7) for the original rate's zero-divisor trap.
 *
 * Units/output pointers must be valid. Query arrays may be NULL for count0;
 * otherwise they must back `count` full
 * EC-byte units, with ordinary observed global callers using count<=16.
 * Default builder scans its supplied unsigned16 descriptor ID, regardless
 * of unit ID; it appends at most24 skills and does not reject skill0.
 * Score arguments are signed16 scalar keys, not array indexes: negative
 * attribute -1 is a legitimate shipped header. Missing keys retain original
 * reads into the supplied512-byte backing. There is no full-width signed
 * user index in these eight interfaces. Stock/skill IDs narrow to ushort,
 * counts to unsigned8, and all query return widths follow original masks.
 * No NULL-unit fallback, global mutation or managed HD offset is introduced.
 */
void cmbClearSkill(datUnitWork_PS2 *unit);
void cmbCreateDefaultSkill(uint16_t devil_id, datUnitWork_PS2 *unit);
int8_t cmbChkStockDevil(uint16_t devil_id, const datUnitWork_PS2 *units,
    uint8_t count);
int8_t cmbChkStockDevilNums(const datUnitWork_PS2 *units, uint8_t count);
uint8_t cmbGetKeisyoSkillScore(int16_t skill_attribute, int16_t inheritance_type);
uint8_t cmbGetKeisyoSkillMotion(uint16_t skill_form, uint16_t devil_form);
uint8_t cmbGetKeisyoSkillLevel(uint16_t skill_id);
uint8_t cmbCalcKeisyoSkillRate(const datUnitWork_PS2 *unit, uint16_t skill_id);

#endif
