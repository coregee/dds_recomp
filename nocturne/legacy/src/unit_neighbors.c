/* Unit construction and evolution neighbors, SLUS_209.11.  */
#include "unit_neighbors.h"

static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128 ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}

static int32_t signed_word(uint32_t value)
{
    return value <= INT32_MAX ? (int32_t)value
        : (int32_t)((int64_t)value - INT64_C(4294967296));
}

static const uint8_t *devil_descriptor_bytes(uint16_t id)
{
    return (const uint8_t *)g_datDevilSkillTable + (uint32_t)id * 0x3c;
}

/* 00222828: unsigned level filter, unlike the signed future-skill builder.
 * Clear only the existing callee's24 bytes; append skill0 and duplicates. */
void ps2CreateLevelSkill(uint16_t devil_id, uint8_t level,
    datUnitWork_PS2 *unit)
{
    cmbClearSkill(unit);
    const cmbDemonSkillRow_PS2 *row = &g_cmbDemonSkillRows[devil_id];
    for (uint32_t i = 0; i < 24; ++i) {
        const cmbDemonSkillEntry_PS2 *entry = &row->entries[i];
        if (entry->type == 1 && (uint8_t)entry->level <= level) {
            uint16_t index = unit->skillcnt;
            unit->skillcnt = (uint16_t)(index + 1);
            unit->skill[index] = entry->skill;
        }
    }
}

/* 002230a0: first type7 entry whose unsigned level <= LOW BYTE of unit level. */
int8_t cmbChkEvoAttention(const datUnitWork_PS2 *unit)
{
    uint8_t level = (uint8_t)unit->level;
    const cmbDemonSkillRow_PS2 *row = &g_cmbDemonSkillRows[unit->id];
    for (uint32_t i = 0; i < 24; ++i)
        if (row->entries[i].type == 7 && (uint8_t)row->entries[i].level <= level)
            return (int8_t)i;
    return -1;
}

/* 00223110: first type5 entry STRICTLY below the low-byte unit level. */
int8_t cmbChkCancelEvo(const datUnitWork_PS2 *unit)
{
    uint8_t level = (uint8_t)unit->level;
    const cmbDemonSkillRow_PS2 *row = &g_cmbDemonSkillRows[unit->id];
    for (uint32_t i = 0; i < 24; ++i)
        if (row->entries[i].type == 5 && (uint8_t)row->entries[i].level < level)
            return (int8_t)i;
    return -1;
}

/* 00223180: first type5's parameter selects a TARGET demon descriptor.
 * Return its signed level byte, without checking the unit's current level. */
int8_t cmbChkDevilEvo(const datUnitWork_PS2 *unit)
{
    const cmbDemonSkillRow_PS2 *row = &g_cmbDemonSkillRows[unit->id];
    for (uint32_t i = 0; i < 24; ++i)
        if (row->entries[i].type == 5)
            return signed_byte(devil_descriptor_bytes(row->entries[i].skill)[5]);
    return -1;
}

/* 002231f8: first type5's signed required-level byte, not the target's level. */
int8_t cmbGetDevilEvoLevel(const datUnitWork_PS2 *unit)
{
    const cmbDemonSkillRow_PS2 *row = &g_cmbDemonSkillRows[unit->id];
    for (uint32_t i = 0; i < 24; ++i)
        if (row->entries[i].type == 5) return row->entries[i].level;
    return -1;
}

/* 001ff050: tail-call byte fill of the entire236-byte inline unit. */
void ps2ClearUnitWork(datUnitWork_PS2 *unit)
{
    unsigned char *bytes = (unsigned char *)unit;
    for (uint32_t i = 0; i < 0xec; ++i) bytes[i] = 0;
}

/* 001fee68: direct descriptor level/default params; both resources filled.
 * Store maxHP/currentHP before computing MP, then build supplied-ID skills. */
void cmbCopyDefaultDevilToStock(uint16_t devil_id, datUnitWork_PS2 *unit)
{
    ps2ClearUnitWork(unit);
    const uint8_t *descriptor = devil_descriptor_bytes(devil_id);
    unit->flag = 1;
    unit->id = devil_id;
    unit->level = descriptor[5];
    for (uint32_t i = 0; i < 6; ++i)
        unit->param[i] = signed_byte(descriptor[0x10 + i]);
    uint16_t maximum = (uint16_t)datGetMaxHp(unit);
    unit->maxhp = maximum;
    unit->hp = maximum;
    maximum = (uint16_t)datGetMaxMp(unit);
    unit->maxmp = maximum;
    unit->mp = maximum;
    cmbCreateDefaultSkill(devil_id, unit);
}

/* 002233d0: inherit every old skill whose computed rate is NONZERO. There
 * is no random draw or percentage trial. The partial clear intentionally
 * leaves the evolved unit's upper12 skill slots in scratch until overwritten. */
void cmbCopyEvoDevilToStock(datUnitWork_PS2 *unit,
    const datUnitWork_PS2 *evolved_unit)
{
    _Alignas(16) datUnitWork_PS2 scratch;
    cmbCopyCustomDevilToStock(&scratch, evolved_unit);
    cmbClearSkill(&scratch);
    if ((scratch.flag & UINT32_C(0x200)) != 0)
        unit->flag |= UINT32_C(0x200);
    scratch.hensinmae = unit->hensinmae != 0 ? unit->hensinmae : unit->id;
    int32_t old_exp = unit->exp;
    scratch.flag = unit->flag;
    scratch.uniqueid = unit->uniqueid;
    scratch.exp = signed_word((uint32_t)scratch.exp + (uint32_t)old_exp);
    scratch.hensinmaeexp = old_exp;
    for (uint32_t i = 0; i < unit->skillcnt; ++i) {
        if (cmbCalcKeisyoSkillRate(&scratch, unit->skill[i]) != 0) {
            uint16_t index = scratch.skillcnt;
            scratch.skillcnt = (uint16_t)(index + 1);
            scratch.skill[index] = unit->skill[i];
        }
    }
    cmbCopyCustomDevilToStock(unit, &scratch);
    unit->hp = unit->maxhp;
    unit->mp = unit->maxmp;
}
