#include "rst_rng_frontier.h"

static int8_t signed_byte(uint32_t value)
{
    uint8_t byte = (uint8_t)value;
    return byte < 128u ? (int8_t)byte : (int8_t)((int32_t)byte - 256);
}

/* 00220d58 -> native1822810b0. Gather first; RNG only when candidates exist.
 * This original output pointer is optional, unlike the managed ref contract. */
uint16_t rstRndGetPowerUpSkill(const datUnitWork_PS2 *unit, int8_t *index)
{
    uint16_t candidates[24];
    uint8_t positions[24];
    int32_t count = 0;
    for (int32_t slot = 0; slot < unit->skillcnt; ++slot) {
        uint16_t skill = unit->skill[slot];
        if (skill != 0) {
            uint16_t upgraded = cmbGetPowerUpSkill(skill);
            if (upgraded != 0) {
                candidates[count] = upgraded;
                positions[count] = (uint8_t)slot;
                count = signed_byte((uint32_t)count + 1u);
            }
        }
    }
    if (count != 0) {
        uint32_t selected = sdfGetRand(NULL) % (uint32_t)count;
        int32_t position = signed_byte(selected);
        if (index != NULL) *index = signed_byte(positions[position]);
        return candidates[position];
    }
    return 0;
}

/* 00223520 -> native18227b6b0. Original LBU dependency returns remain0..255;
 * the exported parent pseudocode's signed-char level casts are unsupported. */
uint16_t cmbGetMutationSkill(uint16_t skill, datUnitWork_PS2 *unit)
{
    for (uint32_t attempt = 0; attempt < 64u; ++attempt) {
        uint32_t row = sdfGetRand(NULL) % PS2_INHERITANCE_LEVEL_ROWS;
        uint16_t candidate = g_cmbInheritanceLevelRecords[row].skill;
        uint32_t level = cmbGetKeisyoSkillLevel(candidate);
        if (cmbChkSkillOwner(candidate, unit) < 0
            && cmbCalcKeisyoSkillRate(unit, candidate) != 0
            && skill != candidate) {
            uint32_t original_level = cmbGetKeisyoSkillLevel(skill);
            if (level <= original_level + 1u) {
                original_level = cmbGetKeisyoSkillLevel(skill);
                if (original_level + 1u <= level) return candidate;
            }
        }
    }
    return 0;
}

/* 00222e00 -> native182277dc0. Private excluded weights stay uninitialized;
 * the header excludes the original non-deterministic minimum-1 interface. */
int8_t cmbAddLevelUpParamEx(datUnitWork_PS2 *unit, int8_t mode)
{
    int16_t quotients[6];
    uint16_t weights[6];
    int32_t minimum = 0x1000;
    uint16_t id = unit->id;
    for (int32_t lane = 0; lane < 6; ++lane) {
        uint32_t growth;
        if (id == 0) {
            uint8_t equipped = g_datGlobalWork->hearts_equipped;
            const unsigned char *record = (const unsigned char *)&g_cmbHeartsRecords[equipped];
            growth = record[0x12 + lane];
        } else {
            growth = g_cmbDemonSkillRows[id].unknown_00[lane];
        }
        if (lane == 1) growth = 0;
        uint32_t parameter = (uint32_t)cmbGetParam(unit, lane) & 0xffu;
        if (growth == 0 || parameter == 40u) {
            quotients[lane] = -1;
        } else {
            int32_t value = unit->levelupparam[lane];
            quotients[lane] = (int16_t)(value / (int32_t)growth);
            weights[lane] = (uint16_t)((int32_t)growth - value % (int32_t)growth);
            if (quotients[lane] < minimum) minimum = quotients[lane];
        }
    }
    uint32_t count = 0, total = 0;
    for (int32_t lane = 0; lane < 6; ++lane) {
        if (quotients[lane] == minimum) {
            count = (count + 1u) & 0xffu;
            total = (total + weights[lane]) & 0xffffu;
        }
    }
    if (count == 0) return -1;
    /* At most five defined weights, each<=382, so total cannot sign-wrap.
     * The original DIVU denominator is nonzero under this defined interface. */
    uint32_t threshold = (sdfGetRand(NULL) % total) & 0xffu;
    uint32_t cumulative = 0;
    for (int32_t lane = 0; lane < 6; ++lane) {
        if (quotients[lane] == minimum) {
            cumulative = (cumulative + (uint8_t)weights[lane]) & 0xffu;
            if (threshold <= cumulative) {
                if (mode == 0) unit->levelupparam[lane] =
                    signed_byte((uint32_t)(uint8_t)unit->levelupparam[lane] + 1u);
                return (int8_t)lane;
            }
        }
    }
    return 6;
}

/* 002201a0 -> native182281880. The private full copy and its resource calls
 * happen before loading the result binding and adding its six raw byte deltas. */
void rstSetMaxHpMp(int8_t mode, datUnitWork_PS2 *unit)
{
    datUnitWork_PS2 scratch;
    cmbCopyCustomDevilToStock(&scratch, unit);
    const rstResourceWork_PS2 *result = g_rstResourceWork;
    for (uint32_t lane = 0; lane < 6u; ++lane) {
        scratch.param[lane] = signed_byte((uint32_t)(uint8_t)scratch.param[lane]
            + result->parameter_delta[lane]);
    }
    if (mode == 0 && result->refill_requested != 0) {
        uint16_t hp = (uint16_t)datGetMaxHp(&scratch);
        unit->maxhp = hp;
        unit->hp = hp;
        uint16_t mp = (uint16_t)datGetMaxMp(&scratch);
        unit->maxmp = mp;
        unit->mp = mp;
    } else {
        unit->maxhp = (uint16_t)datGetMaxHp(&scratch);
        unit->maxmp = (uint16_t)datGetMaxMp(&scratch);
    }
    if (unit->maxhp < unit->hp) unit->hp = unit->maxhp;
    if (unit->maxmp < unit->mp) unit->mp = unit->maxmp;
}

/* 00223080: chosen PS2 alias; full seven-word body calls mode0. */
int8_t ps2AddLevelUpParam(datUnitWork_PS2 *unit)
{
    return cmbAddLevelUpParamEx(unit, 0);
}
