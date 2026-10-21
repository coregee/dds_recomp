#ifndef NOCTURNE_INHERITANCE_QUERIES_H
#define NOCTURNE_INHERITANCE_QUERIES_H

/* Seven reviewed PS2 queries, compared with original-
 * instruction execution. Resolve the canonical src header on the include
 * path. Native HD names support the identities, not its managed layouts. */
#include "nocturne.h"

typedef struct cmbEvoFlagRequirement_PS2 {
    uint16_t devil_id;
    uint16_t event_bit;
} cmbEvoFlagRequirement_PS2;

typedef struct cmbPowerUpSkill_PS2 {
    uint16_t skill;
    uint16_t target_skill;
} cmbPowerUpSkill_PS2;

enum {
    PS2_INHERITED_QUERY_SLOTS = 24,
    PS2_EVO_FLAG_REQUIREMENTS = 6,
    PS2_DARK_DEVIL_IDS = 37,
    PS2_POWER_UP_SKILLS = 55
};

_Static_assert(sizeof(cmbEvoFlagRequirement_PS2) == 4, "evolution flag row stride");
_Static_assert(offsetof(cmbEvoFlagRequirement_PS2, devil_id) == 0,
    "evolution flag devil ID offset");
_Static_assert(offsetof(cmbEvoFlagRequirement_PS2, event_bit) == 2,
    "evolution flag event bit offset");
_Static_assert(sizeof(cmbPowerUpSkill_PS2) == 4, "power-up skill row stride");
_Static_assert(offsetof(cmbPowerUpSkill_PS2, skill) == 0, "source skill offset");
_Static_assert(offsetof(cmbPowerUpSkill_PS2, target_skill) == 2,
    "target skill offset");
_Static_assert(sizeof(datUnitWork_PS2) == 0xec, "stock unit stride");
_Static_assert(offsetof(datUnitWork_PS2, flag) == 0, "stock flags offset");
_Static_assert(offsetof(datUnitWork_PS2, id) == 4, "stock ID offset");
_Static_assert(offsetof(datUnitWork_PS2, level) == 0x14, "unit level offset");
_Static_assert(offsetof(datUnitWork_PS2, keisyoskill) == 0x86,
    "inherited skill array offset");
_Static_assert(sizeof(((datUnitWork_PS2 *)0)->keisyoskill) == 48,
    "24 inherited ushort slots");

/* Proposed read-only host bindings, not recovered original symbols:
 * 00339640: six pairs of ushort devil ID/event bit, 24 bytes.
 * 00339ba8: 37 ushort dark-devil IDs, 74 bytes.
 * 00339c20: 55 pairs of ushort source/target skills, 220 bytes.
 * Each accessed binding must back its entire fixed scan. The dark table
 * extends beyond the existing score backing and needs its own binding. */
extern const cmbEvoFlagRequirement_PS2 *g_cmbEvoFlagRequirements;
extern const uint16_t *g_cmbDarkDevilIds;
extern const cmbPowerUpSkill_PS2 *g_cmbPowerUpSkills;

/* All queries preserve unit, table and global bytes. Unit pointers may alias
 * one another; no restrict/disjointness requirement is imposed. Unit reads
 * require valid complete objects. Dark-stock count accepts NULL when count
 * is zero; otherwise back count full EC-byte units, independently of the
 * observed global stock capacity. IDs narrow to ushort and count to byte.
 * Inherited queries scan all 24 slots, independent of normal skill count.
 * Event requirements use existing evtBitCheck and its backed event-bit range.
 * No new NULL, bounds, capacity, table fallback or edition remap is added. */
int8_t cmbChkKeisyoSkillOwner(uint16_t skill, const datUnitWork_PS2 *unit);
int8_t cmbChkKeisyoSkillNums(const datUnitWork_PS2 *unit);
int8_t cmbChkEvoNeedFlag(uint16_t devil_id);
int8_t cmbChkDarkDevil(uint16_t devil_id);
int8_t cmbChkStockDarkDevilNums(const datUnitWork_PS2 *units, uint8_t count);

/* Full signed32 event_level. Negative values skip the stock pointer entirely,
 * so stock may then be NULL. Player/evolved must always be valid. The other
 * branch forms a signed low32 limit using original modular subtraction;
 * there is no lower clamp. Read-only pointer aliases are allowed. */
int32_t cmbChkEvoDevilLev(const datUnitWork_PS2 *player,
    const datUnitWork_PS2 *stock, const datUnitWork_PS2 *evolved,
    int32_t event_level);
uint16_t cmbGetPowerUpSkill(uint16_t skill);

#endif
