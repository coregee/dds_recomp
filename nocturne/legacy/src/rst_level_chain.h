#ifndef NOCTURNE_RST_LEVEL_CHAIN_H
#define NOCTURNE_RST_LEVEL_CHAIN_H
#include "rst_power_chain.h"
#include "exp.h"
#include "unit_neighbors.h"
#include "ps2_memory.h"

/* Partial view of result slot551F88. These offsets are original PS2 bytes.
 * Accessed extent12A5 is not an allocation claim; natural structure alignment
 * can add host tail padding. The inline preview is a complete236-byte record. */
typedef struct rstLevelWork_PS2 {
    uint8_t unknown_0000[0x18];
    uint8_t point_count;
    uint8_t mirrored_count;
    uint8_t original_level;
    uint8_t level_difference;
    uint8_t unknown_001c[4];
    uint8_t preview_state;
    uint8_t unknown_0021;
    uint16_t devil_destroy_skill;
    uint16_t player_destroy_skill;
    uint8_t unknown_0026[0x16c - 0x26];
    uint32_t unit_address;
    datUnitWork_PS2 preview;
    uint8_t unknown_025c[0x129f - 0x25c];
    int8_t parameter_delta[6];
} rstLevelWork_PS2;
_Static_assert(offsetof(rstLevelWork_PS2, point_count) == 0x18, "result point byte");
_Static_assert(offsetof(rstLevelWork_PS2, original_level) == 0x1a, "original low8 level");
_Static_assert(offsetof(rstLevelWork_PS2, level_difference) == 0x1b, "difference byte");
_Static_assert(offsetof(rstLevelWork_PS2, preview_state) == 0x20, "preview state byte");
_Static_assert(offsetof(rstLevelWork_PS2, devil_destroy_skill) == 0x22, "devil proposal");
_Static_assert(offsetof(rstLevelWork_PS2, player_destroy_skill) == 0x24, "player proposal");
_Static_assert(offsetof(rstLevelWork_PS2, unit_address) == 0x16c, "32bit original pointer");
_Static_assert(offsetof(rstLevelWork_PS2, preview) == 0x170, "inline unit");
_Static_assert(offsetof(rstLevelWork_PS2, parameter_delta) == 0x129f, "delta array");

extern rstLevelWork_PS2 *g_rstLevelWork;
/* External formatter adaptation captures all four original argument words.
 * SDK stdout rendering is outside the recovered game function contract. */
int32_t nocturne_result_printf(const char *format, uint32_t skill,
    uint32_t hp_delta, uint32_t mp_delta);

void rstAddLevel(int32_t value, datUnitWork_PS2 *unit);
uint8_t rstChkAddSkill(uint16_t skill);
int16_t rstGetEquipHeartsAisyo(void);
void rstSetDestroySkillMaxHpMp(void);
int32_t rstChkParamLimitAll(datUnitWork_PS2 *unit);
uint8_t rstSetLevelUpCount(datUnitWork_PS2 *unit);
void rstInitWorkStock(int8_t sacrifice_check);
void *ps2ClearResultParamDeltas(void *result);
void rstAutoAsignDevilParam(void);

/* Recovered original bodies; behavior evidence is versioned separately.
 * Ordinary aligned complete stable unit/result/work/table owners, normal
 * counts<=24 and source rows completely backed. Exact preview self is allowed;
 * unit cannot overlap the other accessed result fields or dependency tables.
 * Auto assignment inherits minimum-not-minus1 and excludes returned lane6,
 * whose following original parameter access is outside existing array ABI.
 * Native extra UI, null checks and edition-specific operations do not transfer.
 */
#endif
