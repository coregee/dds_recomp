/* Original SLUS_209.11 instructions determine behavior. */
#include "unit_batch.h"

static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128 ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}

static uint16_t low_half(uint32_t value)
{
    return (uint16_t)value;
}

static int32_t signed_word(uint32_t value)
{
    return value <= (uint32_t)INT32_MAX ? (int32_t)value
        : -1 - (int32_t)(UINT32_MAX - value);
}

static uint32_t read_word_le(const unsigned char *bytes)
{
    return (uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8)
        | ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[3] << 24);
}

/* 001fdda8: first zero among all24 inherited slots, independent of count. */
int8_t cmbGetKeisyoSkillEndIndex(const datUnitWork_PS2 *unit)
{
    for (uint32_t i = 0; i < PS2_UNIT_BATCH_INHERITED_SKILLS; ++i)
        if (unit->keisyoskill[i] == 0) return signed_byte(i);
    return -1;
}

/* 001ff0a8: clear48 bytes; leave the following inheritance attributes intact. */
void cmbClearKeisyoSkill(datUnitWork_PS2 *unit)
{
    ps2Memset(unit->keisyoskill, 0, PS2_UNIT_BATCH_INHERITED_BYTES);
}

/* 001fed00: owner check precedes the fixed first8-slot insertion scan. */
int8_t cmbAddSkill(uint16_t skill, datUnitWork_PS2 *unit)
{
    if (cmbChkSkillOwner(skill, unit) >= 0) return -2;
    for (uint32_t i = 0; i < PS2_UNIT_BATCH_INSERT_SKILLS; ++i) {
        if (unit->skill[i] == 0) {
            unit->skill[i] = skill;
            unit->skillcnt = low_half((uint32_t)unit->skillcnt + UINT32_C(1));
            return signed_byte(i);
        }
    }
    return -1;
}

/* 001fea98: the entire flag word must be zero, regardless of stored ID. */
int8_t cmbGetEmptyStockIndex(const datUnitWork_PS2 *units, uint8_t count)
{
    for (uint32_t i = 0; i < count; ++i)
        if (units[i].flag == 0) return signed_byte(i);
    return -1;
}

/* 001fead8: any nonzero flag word qualifies, including flag4 alone. */
int8_t cmbGetStockDevilIndex(uint16_t devil_id,
    const datUnitWork_PS2 *units, uint8_t count)
{
    for (uint32_t i = 0; i < count; ++i)
        if (units[i].flag != 0 && units[i].id == devil_id)
            return signed_byte(i);
    return -1;
}

/* 001ff178: write before re-reading source; always decrement count once. */
void cmbDeleteUnitFromStockList(int8_t unit_index)
{
    datGlobalWork_PS2 *work = g_datGlobalWork;
    int32_t count = work->stock_count;
    int8_t read_index = 0, write_index = 0;
    if (count > 0) {
        do {
            uint8_t value = work->stock_list[read_index];
            work->stock_list[write_index] = value;
            work = g_datGlobalWork;
            value = work->stock_list[read_index];
            if ((int32_t)value != (int32_t)unit_index)
                write_index = signed_byte((uint32_t)(int32_t)write_index + UINT32_C(1));
            count = work->stock_count;
            read_index = signed_byte((uint32_t)(int32_t)read_index + UINT32_C(1));
        } while ((int32_t)read_index < count);
        count = work->stock_count;
    }
    work->stock_count = signed_word((uint32_t)count - UINT32_C(1));
}

/* 001ff1f8: byte append occurs before the wrapped count store. */
void cmbAddUnitToStockList(int8_t unit_index)
{
    datGlobalWork_PS2 *work = g_datGlobalWork;
    int32_t count = work->stock_count;
    work->stock_list[count] = (uint8_t)unit_index;
    work->stock_count = signed_word((uint32_t)count + UINT32_C(1));
}

/* 001ff218: flag1 search, list deletion, full unit clear; success returns-1. */
int8_t cmbDeleteDevilFromStock(uint16_t devil_id,
    datUnitWork_PS2 *units, uint8_t count)
{
    int8_t index = cmbChkStockDevil(devil_id, units, count);
    if (index < 0) return 0;
    int8_t list_index = signed_byte((uint32_t)(int32_t)index
        - (uint32_t)count + UINT32_C(16));
    cmbDeleteUnitFromStockList(list_index);
    ps2ClearUnitWork(&units[index]);
    return -1;
}

/* 001ff298: append list byte before constructing the selected default unit. */
int8_t cmbAddDefaultDevilToStock(uint16_t devil_id,
    datUnitWork_PS2 *units, uint8_t count)
{
    int8_t index = cmbGetEmptyStockIndex(units, count);
    if (index < 0) return -1;
    int8_t list_index = signed_byte((uint32_t)(int32_t)index
        - (uint32_t)count + UINT32_C(16));
    cmbAddUnitToStockList(list_index);
    cmbCopyDefaultDevilToStock(devil_id, &units[index]);
    return index;
}

/* 001ff328: failed search does not read source; success uses the real copy. */
int8_t cmbAddCustomDevilToStock(const datUnitWork_PS2 *source,
    datUnitWork_PS2 *units, uint8_t count)
{
    int8_t index = cmbGetEmptyStockIndex(units, count);
    if (index < 0) return -1;
    int8_t list_index = signed_byte((uint32_t)(int32_t)index
        - (uint32_t)count + UINT32_C(16));
    cmbAddUnitToStockList(list_index);
    cmbCopyCustomDevilToStock(&units[index], source);
    return index;
}

/* 001ff3b8: skip zeros, count duplicates, and add unsigned8 rate results. */
int32_t cmbCalcTotalKeisyoSkillRate(const datUnitWork_PS2 *unit)
{
    int32_t total = 0;
    for (uint32_t i = 0; i < PS2_UNIT_BATCH_INHERITED_SKILLS; ++i) {
        uint16_t skill = unit->keisyoskill[i];
        if (skill != 0) total += (int32_t)cmbCalcKeisyoSkillRate(unit, skill);
    }
    return total;
}

/* 00222a28: raw level equality; return first entry and count every match. */
const cmbDemonSkillEntry_PS2 *cmbChkLevelUpEvent(
    const datUnitWork_PS2 *unit, int8_t *event_count)
{
    uint16_t devil_id = unit->id;
    uint8_t level = (uint8_t)unit->level;
    const cmbDemonSkillRow_PS2 *row = &g_cmbDemonSkillRows[devil_id];
    const cmbDemonSkillEntry_PS2 *first = NULL;
    uint8_t count = 0;
    for (uint32_t i = 0; i < PS2_UNIT_BATCH_INHERITED_SKILLS; ++i) {
        const cmbDemonSkillEntry_PS2 *entry = &row->entries[i];
        if ((uint8_t)entry->level == level) {
            count = (uint8_t)((uint32_t)count + UINT32_C(1));
            if (count == 1) first = entry;
        }
    }
    if (event_count != NULL) *event_count = signed_byte(count);
    return first;
}

/* 001fe9e0: race0 is excluded; otherwise inspect flag20 in existing bytes. */
int8_t cmbChkIkenieIllegalDevil(uint16_t devil_id)
{
    const unsigned char *descriptor = (const unsigned char *)&g_datDevilSkillTable[devil_id];
    if (descriptor[offsetof(datDevilSkillRecord_PS2, race)] == 0) return 1;
    uint32_t flags = read_word_le(descriptor);
    return (int8_t)((flags & UINT32_C(0x20)) != 0);
}
