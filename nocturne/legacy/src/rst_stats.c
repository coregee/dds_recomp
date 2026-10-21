/* Connected classification, parameters and custom-copy helpers, SLUS_209.11.
 * Algorithm and field widths recovered from original instructions. */
#include "rst_stats.h"

/* Explicit two's-complement low8 conversion for original signed LB/SRA24. */
static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128 ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}

/* 00221f20: exactly three byte counters; comparisons use signed LB.
 * Classes other than1/0/4 do not increment a bucket, but every mastered
 * ownership entry still contributes to the separate mastery-count call. */
uint8_t cmbChkMasterHeartsStatNums(uint8_t *tier)
{
    uint8_t counts[3] = {0, 0, 0};
    for (uint32_t i = 0; i < g_datGlobalWork->hearts_owned_count; ++i) {
        int8_t id = signed_byte(g_datGlobalWork->hearts_owned[i]);
        if (cmbChkHeartsMaster((uint8_t)id) != 0) {
            uint8_t stat = cmbChkHeartsStat(id);
            if (stat == 1) counts[0] = (uint8_t)(counts[0] + 1u);
            else if (stat == 0) counts[1] = (uint8_t)(counts[1] + 1u);
            else if (stat == 4) counts[2] = (uint8_t)(counts[2] + 1u);
        }
    }

    int32_t count1 = signed_byte(counts[0]);
    int32_t count0 = signed_byte(counts[1]);
    int32_t count4 = signed_byte(counts[2]);
    uint8_t stat = 0;
    if (count1 != count4 && !(count1 < count0 && count4 < count0))
        stat = count1 < count4 ? 4 : 1;

    int32_t mastered = cmbGetMasterHeartsNums();
    int32_t amount;
    if (mastered < 6) amount = mastered / 2;
    else if (mastered == 25) amount = 5;
    else amount = mastered < 12 ? 3 : 4;
    if (tier != NULL) *tier = (uint8_t)amount;
    return stat;
}

/* 00221e70: original callers pass the player unit, but A0 is unused.
 * All nonzero exits explicitly mask the result to unsigned8. */
uint8_t cmbGetPlayerRaceID(datUnitWork_PS2 *unused_unit)
{
    uint8_t tier;
    uint8_t stat;
    (void)unused_unit;
    stat = cmbChkMasterHeartsStatNums(&tier);
    if (tier == 0) return 0;
    uint32_t base = (uint8_t)(tier - 1u);
    uint32_t suffix = stat == 1 ? 1u : (stat == 4 ? 3u : 2u);
    return (uint8_t)(base * 3u + suffix);
}

/* 00221d00: player raw signed parameter minus equipped Hearts parameter.
 * The raw access uses full index; only the Hearts accessor receives low8.
 * The subtraction returns Int32 without a final byte conversion/clamp. */
int32_t cmbGetParamBase(datUnitWork_PS2 *unit, int32_t index)
{
    if (unit->id != 0) return datGetParam(unit, index);
    int32_t value = unit->param[index];
    uint8_t equipped = g_datGlobalWork->hearts_equipped;
    if (equipped != 0)
        value -= cmbGetHeartsParam(signed_byte(equipped),
            signed_byte((uint32_t)index));
    return value;
}

/* 00221d70: player raw signed parameter, otherwise canonical datGetParam. */
int32_t cmbGetParam(datUnitWork_PS2 *unit, int32_t index)
{
    return unit->id == 0 ? (int32_t)unit->param[index] : datGetParam(unit, index);
}

/* 001fef20: seven32-byte load-before-store chunks, then twelve tail bytes.
 * The8-byte aligned and4-byte aligned EE paths transfer these same bytes. Keeping
 * the chunk snapshots preserves the observed copy partition; this is not
 * a newly defined general partial-overlap or memmove contract. */
void cmbCopyCustomDevilToStock(datUnitWork_PS2 *destination,
    const datUnitWork_PS2 *source)
{
    unsigned char *dst = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;
    unsigned char chunk[32];
    for (uint32_t offset = 0; offset < 0xe0; offset += 32) {
        for (uint32_t i = 0; i < 32; ++i) chunk[i] = src[offset + i];
        for (uint32_t i = 0; i < 32; ++i) dst[offset + i] = chunk[i];
    }
    for (uint32_t i = 0; i < 12; ++i) chunk[i] = src[0xe0 + i];
    for (uint32_t i = 0; i < 12; ++i) dst[0xe0 + i] = chunk[i];

    destination->maxhp = (uint16_t)datGetMaxHp(destination);
    destination->maxmp = (uint16_t)datGetMaxMp(destination);
    if (destination->maxhp < destination->hp)
        destination->hp = destination->maxhp;
    if (destination->maxmp < destination->mp)
        destination->mp = destination->maxmp;
    destination->flag |= UINT32_C(1);
}

/* 00220728: LB equipped ID; ushort skill search in the signed count prefix.
 * Scratch is deliberately uninitialized: a NULL-unit builder leaves it alone. */
int8_t rstChkBeforeSkillOwner(uint16_t skill, int8_t level_offset,
    datUnitWork_PS2 *unit)
{
    rstSkillInfo_PS2 info;
    uint8_t equipped = g_datGlobalWork->hearts_equipped;
    int8_t id = equipped < 128 ? (int8_t)equipped
                              : (int8_t)((int32_t)equipped - 256);
    rstCreateBeforeSkillList(id, unit, level_offset, &info);
    int32_t count = info.skillcnt;
    for (int32_t i = 0; i < count; ++i)
        if (info.skill[i] == skill) return 1;
    return 0;
}
