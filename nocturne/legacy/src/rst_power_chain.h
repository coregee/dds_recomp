#ifndef NOCTURNE_RST_POWER_CHAIN_H
#define NOCTURNE_RST_POWER_CHAIN_H

#include "rst_rng_frontier.h"

/* Another partial view of the SAME original result pointer at00551F88.
 * Keep the embedded PS2 pointer as a32-bit address, even in a64-bit host build.
 * None of these byte offsets is copied from the native managed object. */
typedef struct rstSkillPowerWork_PS2 {
    uint8_t unknown_0000[0x1b];
    uint8_t level_difference;
    uint8_t unknown_001c[0x74 - 0x1c];
    int8_t selected_slot;
    uint8_t unknown_0075;
    uint16_t selected_skill;
    uint8_t unknown_0078[0x16c - 0x78];
    uint32_t unit_address;
} rstSkillPowerWork_PS2;
_Static_assert(offsetof(rstSkillPowerWork_PS2, level_difference) == 0x1b, "result level byte");
_Static_assert(offsetof(rstSkillPowerWork_PS2, selected_slot) == 0x74, "selected slot byte");
_Static_assert(offsetof(rstSkillPowerWork_PS2, selected_skill) == 0x76, "selected skill ushort");
_Static_assert(offsetof(rstSkillPowerWork_PS2, unit_address) == 0x16c, "original unit address word");
_Static_assert(sizeof(rstSkillPowerWork_PS2) == 0x170, "partial accessed extent");

extern rstSkillPowerWork_PS2 *g_rstSkillPowerWork;
#if UINTPTR_MAX > UINT32_MAX
/* Host-only address translation. It must resolve original RAM addresses to
 * the same complete backing allocations. It supplies no game behavior or
 * dependency result. A32-bit PS2 build uses the original address directly. */
datUnitWork_PS2 *nocturneResolveRstUnitAddress(uint32_t address);
#endif

uint8_t rstChkSkillPowerUp1(void);
uint8_t rstChkSkillPowerUp2(void);
uint8_t rstChkDevilSkillPowerUp(const datUnitWork_PS2 *unit);
uint8_t rstChkPartyDevilSkillPowerUp(void);
uint8_t rstCalcSkillPowerUpCore(void);
uint8_t rstCalcSkillPowerUp(void);

/* Recovered from complete original bodies; behavior evidence is separately versioned.
 * Ordinary stable, aligned complete work/result/unit/table objects are required.
 * The first gate below global player level7 does not read the embedded unit
 * address; that conditional path permits an invalid embedded address.
 * Selected original unit must have normal skill count<=24. Result output bytes
 * must not alias unit/table/RNG backing; inherited dependency contracts apply.
 * rstChkBeforeSkillOwner requires an initialized private before-skill list: unit
 * is non-NULL, source rows fully backed and list appends do not overflow24.
 * Level difference negates and narrows to signed8; no range repair is added.
 * The party query returns the LAST qualifying unit's flag40, not an OR across
 * the party. Original conditional branches never stop the fixed16-slot scan.
 */
#endif
