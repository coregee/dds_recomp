#include "rst_level_chain.h"

static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128u ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}
static datUnitWork_PS2 *result_unit(const rstLevelWork_PS2 *result)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveRstUnitAddress(result->unit_address);
#else
    return (datUnitWork_PS2 *)(uintptr_t)result->unit_address;
#endif
}

/* 0021fd98 ->18227c150: preexisting unsigned level<255 qualifies the write;
 * there is no clamp of the resulting low16 sum and no original NULL check. */
void rstAddLevel(int32_t value, datUnitWork_PS2 *unit)
{
    uint16_t level = unit->level;
    if (level < 255u) unit->level = (uint16_t)((uint32_t)level + (uint32_t)value);
}

/* 0021ffb8 ->18227f940: real ownership first, then unsigned count<8. */
uint8_t rstChkAddSkill(uint16_t skill)
{
    if (cmbChkSkillOwner(skill, result_unit(g_rstLevelWork)) >= 0) return 0;
    return result_unit(g_rstLevelWork)->skillcnt < 8u ? 1u : 2u;
}

/* 00220000 ->182280930: real accessor retains its equipped-ID0 shortcut. */
int16_t rstGetEquipHeartsAisyo(void)
{
    return cmbGetHeartsAisyo(g_datGlobalWork->hearts_equipped);
}

/* 00220020 ->182281440: plain original236-byte private copy, not custom-copy
 * resource repair. Four actual maximum-resource calls, then modular ushort
 * additions to current maxima only. Current HP/MP and skill list stay intact. */
void rstSetDestroySkillMaxHpMp(void)
{
    rstLevelWork_PS2 *result = g_rstLevelWork;
    datUnitWork_PS2 *unit = result_unit(result);
    uint16_t skill = unit->id == 0 ? result->player_destroy_skill : result->devil_destroy_skill;
    datUnitWork_PS2 scratch;
    unsigned char *destination = (unsigned char *)&scratch;
    const unsigned char *source = (const unsigned char *)unit;
    for (uint32_t i = 0; i < sizeof scratch; ++i) destination[i] = source[i];
    scratch.skillcnt = 0;
    uint32_t old_hp = datGetMaxHp(&scratch);
    uint32_t old_mp = datGetMaxMp(&scratch);
    scratch.skill[0] = skill;
    scratch.skillcnt = 1;
    uint32_t hp_delta = datGetMaxHp(&scratch) - old_hp;
    uint32_t mp_delta = datGetMaxMp(&scratch) - old_mp;
    unit->maxhp = (uint16_t)((uint32_t)unit->maxhp + hp_delta);
    unit->maxmp = (uint16_t)((uint32_t)unit->maxmp + mp_delta);
    (void)nocturne_result_printf("New skill : %03x MAXHP+%d MAXMP+%d\n", skill, hp_delta, mp_delta);
}

/* 00220288 ->1822800b0: original always calls mode0 resource updater after
 * all five non-lane1 bases>=40. HD adds a second optional-update argument. */
int32_t rstChkParamLimitAll(datUnitWork_PS2 *unit)
{
    for (int32_t lane = 0; lane < 6; ++lane)
        if (lane != 1 && cmbGetParamBase(unit, lane) < 40) return 0;
    rstSetMaxHpMp(0, unit);
    return 1;
}

/* 002202f8 ->182281680: initial level/count copies use low8 bytes. Real
 * level-count/custom/default/resource dependencies execute in original order.
 * Status800 returns0 AFTER level addition. No HD point-animation call exists. */
uint8_t rstSetLevelUpCount(datUnitWork_PS2 *unit)
{
    g_rstLevelWork->original_level = (uint8_t)unit->level;
    uint32_t count = (uint32_t)cmbGetLevelUpCount(unit, 0);
    g_rstLevelWork->level_difference = (uint8_t)count;
    rstLevelWork_PS2 *result = g_rstLevelWork;
    uint8_t byte = result->level_difference;
    result->point_count = byte;
    result->mirrored_count = byte;
    int32_t excess = 0;
    if ((unit->flag & 0x200u) != 0) {
        datUnitWork_PS2 scratch;
        cmbCopyDefaultDevilToStock(unit->id, &scratch);
        excess = (int32_t)unit->level - (int32_t)scratch.level;
    }
    rstAddLevel(signed_byte(g_rstLevelWork->level_difference), unit);
    if ((unit->badstat & 0x800u) != 0) return 0;
    result = g_rstLevelWork;
    if (signed_byte(result->level_difference) == 0) return 0;
    result->level_difference = (uint8_t)((uint32_t)result->level_difference + (uint32_t)excess);
    result = g_rstLevelWork;
    result->original_level = (uint8_t)((uint32_t)result->original_level - (uint32_t)excess);
    rstSetMaxHpMp(0, unit);
    return 1;
}

/* 00220480 ->182280b40: inline preview custom copy and signed low8 old-level
 * plus1. Nonzero mode+flag200 substitutes real default descriptor level. */
void rstInitWorkStock(int8_t sacrifice_check)
{
    g_rstLevelWork->preview_state = 0;
    rstLevelWork_PS2 *result = g_rstLevelWork;
    cmbCopyCustomDevilToStock(&result->preview, result_unit(result));
    result = g_rstLevelWork;
    result->preview.level = (uint16_t)((int32_t)signed_byte(result->original_level) + 1);
    if (sacrifice_check != 0) {
        datUnitWork_PS2 *unit = result_unit(result);
        if ((unit->flag & 0x200u) != 0) {
            datUnitWork_PS2 scratch;
            cmbCopyDefaultDevilToStock(unit->id, &scratch);
            g_rstLevelWork->preview.level = scratch.level;
        }
    }
}

/* 0021f8d0: chosen PS2-only alias, full tail-call returns real memset result. */
void *ps2ClearResultParamDeltas(void *result)
{
    return ps2Memset((unsigned char *)result + 0x129f, 0, 6);
}

/* 002207a8 ->18227c180: real six-byte clear, custom copy and growth call per
 * signed positive count. Scratch level-up stats mutate, parameter base does
 * not; compare real parameter+signed accumulated output before increment. */
void rstAutoAsignDevilParam(void)
{
    (void)ps2ClearResultParamDeltas(g_rstLevelWork);
    datUnitWork_PS2 scratch;
    cmbCopyCustomDevilToStock(&scratch, result_unit(g_rstLevelWork));
    for (int32_t iteration = 0; iteration < signed_byte(g_rstLevelWork->point_count); ++iteration) {
        int8_t lane = cmbAddLevelUpParamEx(&scratch, 0);
        if (lane >= 0) {
            int32_t parameter = datGetParam(&scratch, lane);
            rstLevelWork_PS2 *result = g_rstLevelWork;
            int32_t delta = result->parameter_delta[lane];
            uint8_t raw = (uint8_t)result->parameter_delta[lane];
            if (parameter + delta < 40)
                result->parameter_delta[lane] = signed_byte((uint32_t)raw + 1u);
        }
    }
}
