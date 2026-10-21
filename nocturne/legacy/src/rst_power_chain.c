#include "rst_power_chain.h"

static datUnitWork_PS2 *result_unit(const rstSkillPowerWork_PS2 *result)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveRstUnitAddress(result->unit_address);
#else
    return (datUnitWork_PS2 *)(uintptr_t)result->unit_address;
#endif
}

static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128u ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}

/* 00220c50 ->182280220: global player level gate precedes result/unit reads.
 * Player ID0 still CONSUMES a draw before returning1, even when ignored. */
uint8_t rstChkSkillPowerUp1(void)
{
    if (g_datGlobalWork->units[0].level < 7u) return 0;
    uint16_t id = result_unit(g_rstSkillPowerWork)->id;
    uint32_t draw = sdfGetRand(NULL);
    return id == 0 ? 1u : (uint8_t)((draw & 3u) == 0);
}

/* 00220cb0 ->182280340: PS2 thresholds compare zero-based remainder.
 * HD adds1 before its thresholds. Return2 branches are retained even though
 * modulo254 bounds make them unreachable under this ordinary interface. */
uint8_t rstChkSkillPowerUp2(void)
{
    uint16_t id = result_unit(g_rstSkillPowerWork)->id;
    uint32_t draw = sdfGetRand(NULL) % 254u;
    if (id == 0) {
        if (draw < 112u) return 0;
        if (draw - 112u < 142u) return 1;
    } else {
        if (draw < 128u) return 0;
        if (draw - 128u < 126u) return 1;
    }
    return 2;
}

/* 00220e68 ->18227fb20: full flag word, exact bit40 Boolean. */
uint8_t rstChkDevilSkillPowerUp(const datUnitWork_PS2 *unit)
{
    return (uint8_t)((unit->flag & 0x40u) != 0);
}

/* 00220e78 ->182280150: 00220ED0 is MOVE A2,V0, not a bitwise OR.
 * A later qualifying unmarked unit clears a previous positive result.
 * The native port instead accumulates OR. */
uint8_t rstChkPartyDevilSkillPowerUp(void)
{
    uint8_t result = 0;
    for (uint32_t index = 0; index < 16u; ++index) {
        const datUnitWork_PS2 *unit = &g_datGlobalWork->units[index];
        uint32_t flag = unit->flag;
        if ((flag & 1u) != 0 && (flag & 4u) == 0 && (flag & 2u) != 0)
            result = rstChkDevilSkillPowerUp(unit);
    }
    return result;
}

/* 00220ef8 ->18227e100: original dependency calls/read/store order retained.
 * The chosen candidate is recorded even when a later eligibility gate fails. */
uint8_t rstCalcSkillPowerUpCore(void)
{
    rstSkillPowerWork_PS2 *result = g_rstSkillPowerWork;
    uint16_t skill = rstRndGetPowerUpSkill(result_unit(result), &result->selected_slot);
    result = g_rstSkillPowerWork;
    result->selected_skill = skill;
    if (skill == 0) return 0;
    int8_t level_offset = signed_byte(0u - result->level_difference);
    if (rstChkBeforeSkillOwner(result->selected_skill, level_offset, result_unit(result)) != 0)
        return 0;
    uint8_t kind = rstChkSkillPowerUp2();
    if (kind == 0) {
        result = g_rstSkillPowerWork;
        int8_t owner = cmbChkSkillOwner(result->selected_skill, result_unit(result));
        result = g_rstSkillPowerWork;
        kind = (uint8_t)(owner >= 0);
        if (rstChkDevilSkillPowerUp(result_unit(result)) != 0) return 0;
        if (rstChkPartyDevilSkillPowerUp() != 0) kind = 1;
        result = g_rstSkillPowerWork;
        if (kind == 0) {
            datUnitWork_PS2 *unit = result_unit(result);
            unit->flag |= 0x40u;
            return 1;
        }
    }
    if (kind != 1) return 3;
    result = g_rstSkillPowerWork;
    datUnitWork_PS2 *unit = result_unit(result);
    uint16_t original = unit->skill[result->selected_slot];
    skill = cmbGetMutationSkill(original, unit);
    result = g_rstSkillPowerWork;
    if (skill == 0) return 3;
    result->selected_skill = skill;
    return 2;
}

/* 00221018 ->18227e5f0: call the gate first, call the full core only when1. */
uint8_t rstCalcSkillPowerUp(void)
{
    if (rstChkSkillPowerUp1() == 0) return 0;
    return rstCalcSkillPowerUpCore();
}
