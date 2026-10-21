/* Recovered from original SLUS_209.11 instructions; see inheritance_queries.h. */
#include "inheritance_queries.h"

static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128 ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}

/* Interpret the low word without an out-of-range cast or signed overflow. */
static int32_t signed_word(uint32_t bits)
{
    if (bits <= (uint32_t)INT32_MAX) return (int32_t)bits;
    return -1 - (int32_t)(UINT32_MAX - bits);
}

/* 001fedf0: first exact match across all 24 inherited slots, including zero. */
int8_t cmbChkKeisyoSkillOwner(uint16_t skill, const datUnitWork_PS2 *unit)
{
    for (uint32_t i = 0; i < PS2_INHERITED_QUERY_SLOTS; ++i)
        if (unit->keisyoskill[i] == skill) return (int8_t)i;
    return -1;
}

/* 001fee30: count every nonzero inherited slot, including entries after holes. */
int8_t cmbChkKeisyoSkillNums(const datUnitWork_PS2 *unit)
{
    int8_t count = 0;
    for (uint32_t i = 0; i < PS2_INHERITED_QUERY_SLOTS; ++i)
        if (unit->keisyoskill[i] != 0) ++count;
    return count;
}

/* 00222970: matching rows with a set event bit do not end the search. */
int8_t cmbChkEvoNeedFlag(uint16_t devil_id)
{
    for (uint32_t i = 0; i < PS2_EVO_FLAG_REQUIREMENTS; ++i) {
        const cmbEvoFlagRequirement_PS2 *requirement =
            &g_cmbEvoFlagRequirements[i];
        if (requirement->devil_id == devil_id
            && evtBitCheck((int32_t)requirement->event_bit) == 0)
            return 1;
    }
    return 0;
}

/* 00222cf0: fixed 37-element ushort membership table. */
int8_t cmbChkDarkDevil(uint16_t devil_id)
{
    for (uint32_t i = 0; i < PS2_DARK_DEVIL_IDS; ++i)
        if (g_cmbDarkDevilIds[i] == devil_id) return 1;
    return 0;
}

/* 00222d38: count occupied non-flag4 dark units, returning signed low8. */
int8_t cmbChkStockDarkDevilNums(const datUnitWork_PS2 *units, uint8_t count)
{
    uint8_t result = 0;
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t flag = units[i].flag;
        if ((flag & UINT32_C(1)) != 0 && (flag & UINT32_C(4)) == 0
            && cmbChkDarkDevil(units[i].id) != 0)
            result = (uint8_t)(result + 1u);
    }
    return signed_byte(result);
}

/* 00223398: signed minimum of the evolution gap and wrapped event limit.
 * Negative event levels leave stock unread and use the original limit 255. */
int32_t cmbChkEvoDevilLev(const datUnitWork_PS2 *player,
    const datUnitWork_PS2 *stock, const datUnitWork_PS2 *evolved,
    int32_t event_level)
{
    int32_t limit = 255;
    if (event_level >= 0) {
        uint32_t difference = (uint32_t)stock->level - (uint32_t)event_level;
        limit = signed_word(UINT32_C(99) - difference);
    }
    int32_t player_level = (int32_t)player->level;
    int32_t evolved_level = (int32_t)evolved->level;
    int32_t gap = evolved_level - player_level - 4;
    return limit < gap ? limit : gap;
}

/* 002234e0: first source equality across 55 pairs; absent source returns zero. */
uint16_t cmbGetPowerUpSkill(uint16_t skill)
{
    for (uint32_t i = 0; i < PS2_POWER_UP_SKILLS; ++i)
        if (g_cmbPowerUpSkills[i].skill == skill)
            return g_cmbPowerUpSkills[i].target_skill;
    return 0;
}
