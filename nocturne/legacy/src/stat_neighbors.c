/* Stock construction and inherited-skill algorithms, SLUS_209.11. */
#include "stat_neighbors.h"

static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128 ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}

static uint16_t read_ushort_le(const uint8_t *bytes)
{
    return (uint16_t)((uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8));
}

static int16_t read_short_le(const uint8_t *bytes)
{
    uint16_t value = read_ushort_le(bytes);
    return value < 32768 ? (int16_t)value : (int16_t)((int32_t)value - 65536);
}

/* 001ff070: clear24 BYTES (12 ushort skills), then ushort count. */
void cmbClearSkill(datUnitWork_PS2 *unit)
{
    for (uint32_t i = 0; i < 12; ++i) unit->skill[i] = 0;
    unit->skillcnt = 0;
}

/* 00222788: argument ID selects direct102-byte row, type1/level0 only.
 * Upper12 skill slots retain clear's original bytes unless overwritten by
 * this append loop; skill0 and duplicate entries are appended normally. */
void cmbCreateDefaultSkill(uint16_t devil_id, datUnitWork_PS2 *unit)
{
    cmbClearSkill(unit);
    const cmbDemonSkillRow_PS2 *row = &g_cmbDemonSkillRows[devil_id];
    for (uint32_t i = 0; i < 24; ++i) {
        const cmbDemonSkillEntry_PS2 *entry = &row->entries[i];
        if (entry->type == 1 && entry->level == 0) {
            uint16_t index = unit->skillcnt;
            unit->skillcnt = (uint16_t)(index + 1);
            unit->skill[index] = entry->skill;
        }
    }
}

/* 002228d8: relative first index, bit1 only; flag4 does not exclude it. */
int8_t cmbChkStockDevil(uint16_t devil_id, const datUnitWork_PS2 *units,
    uint8_t count)
{
    for (uint32_t i = 0; i < count; ++i)
        if ((units[i].flag & 1) != 0 && units[i].id == devil_id)
            return signed_byte(i);
    return -1;
}

/* 00222928: occupied and non-flag4; signed8 return of wrapped byte count. */
int8_t cmbChkStockDevilNums(const datUnitWork_PS2 *units, uint8_t count)
{
    uint8_t result = 0;
    for (uint32_t i = 0; i < count; ++i)
        if ((units[i].flag & 1) != 0 && (units[i].flag & 4) == 0)
            result = (uint8_t)(result + 1);
    return signed_byte(result);
}

/* 00222aa0: signed-short key lookup; absent column16 / absent row13 are
 * original raw backing reads, not HD's final-row/final-column fallbacks.
 * Row12 can match the zero padding after the12 legitimate data rows. */
uint8_t cmbGetKeisyoSkillScore(int16_t skill_attribute, int16_t inheritance_type)
{
    uint32_t column = 0, row = 0;
    while (column < 16
        && read_short_le(g_cmbInheritanceScoreBytes + 2 + 2 * column)
            != skill_attribute)
        ++column;
    while (row < 13
        && read_short_le(g_cmbInheritanceScoreBytes + 0x22 + 0x22 * row)
            != inheritance_type)
        ++row;
    return g_cmbInheritanceScoreBytes[0x24 + 2 * column + 0x22 * row];
}

/* 00222b70: only the lowest set skill-form bit decides compatibility. */
uint8_t cmbGetKeisyoSkillMotion(uint16_t skill_form, uint16_t devil_form)
{
    for (uint32_t bit = 0; bit < 16; ++bit)
        if (((uint32_t)skill_form & (UINT32_C(1) << bit)) != 0)
            return (uint8_t)(((uint32_t)devil_form >> bit) & 1);
    return 0;
}

/* 00222bb0: fixed227-row first-match lookup, absent skill defaults to1. */
uint8_t cmbGetKeisyoSkillLevel(uint16_t skill_id)
{
    for (uint32_t i = 0; i < PS2_INHERITANCE_LEVEL_ROWS; ++i)
        if (g_cmbInheritanceLevelRecords[i].skill == skill_id)
            return g_cmbInheritanceLevelRecords[i].level;
    return 1;
}

/* 00222bf0: compute score before motion gate. Original DIVU with level0
 * traps at break7; negative signed totals wrap on return, upper totals cap99. */
uint8_t cmbCalcKeisyoSkillRate(const datUnitWork_PS2 *unit, uint16_t skill_id)
{
    const cmbInheritanceSkillRecord_PS2 *skill = &g_cmbInheritanceSkillRecords[skill_id];
    const uint8_t *devil = (const uint8_t *)&g_datDevilSkillTable[unit->id];
    int16_t inheritance_type = read_short_le(devil
        + offsetof(cmbInheritanceDevilView_PS2, inheritance_type));
    uint16_t devil_form = read_ushort_le(devil
        + offsetof(cmbInheritanceDevilView_PS2, form));
    uint8_t score = cmbGetKeisyoSkillScore(skill->attribute, inheritance_type);
    if (cmbGetKeisyoSkillMotion(skill->form, devil_form) == 0) return 0;
    uint8_t divisor = cmbGetKeisyoSkillLevel(skill_id);
    if (divisor == 0) nocturne_break(7);
    uint8_t quotient = (uint8_t)((uint32_t)score / divisor);
    int32_t result = (int32_t)quotient + (int32_t)unit->level
        - (int32_t)devil[offsetof(cmbInheritanceDevilView_PS2, level)] + 1;
    if (result >= 100) result = 99;
    return (uint8_t)result;
}
