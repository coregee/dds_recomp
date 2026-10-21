/* Connected Magatama mastery, parameters and skill eligibility, SLUS_209.11.
 * Caller contract: Hearts IDs0..25, parameter indexes0..5, skill slots0..7,
 * position indexes0..26 and valid unit skill count. No capacity checks added. */
#include "nocturne.h"

/* 00221dd8: separate owned-Hearts predicate in the recovery module. */
int8_t cmbChkGetHearts(int8_t id)
{
    for (uint32_t i = 0; i < g_datGlobalWork->hearts_owned_count; ++i)
        if ((int32_t)g_datGlobalWork->hearts_owned[i] == id) return 1;
    return 0;
}

/* 002220c0: count nonzero IDs regardless of required level; ID0 is special. */
int16_t cmbGetHeartsSkillNums(uint8_t id)
{
    int8_t count = 0;
    if (id != 0)
        for (uint32_t i = 0; i < 8; ++i)
            if (g_cmbHeartsRecords[id].skills[i].skill != 0) ++count;
    return count;
}

/* 00222140/00222160/002221e8: bit7 is mastery; bits4..6 stay unspecified. */
int8_t cmbChkHeartsMaster(uint8_t id)
{
    return (g_datGlobalWork->hearts_skill_state[id] & 0x80) != 0;
}

int8_t cmbGetMasterHeartsNums(void)
{
    int32_t count = 0;
    for (uint32_t i = 0; i < g_datGlobalWork->hearts_owned_count; ++i)
        count += cmbChkHeartsMaster(g_datGlobalWork->hearts_owned[i]);
    return (int8_t)count;
}

void cmbSetHeartsMaster(int8_t id)
{
    g_datGlobalWork->hearts_skill_state[id] |= 0x80;
}

/* 00222210: chosen alias, no reviewed native HD counterpart. Signed index
 * comparison is retained; callers supplying negative indexes are unvalidated. */
uint16_t ps2HeartsSkillAt(uint8_t id, int8_t index)
{
    return index < 8 ? g_cmbHeartsRecords[id].skills[index].skill : 0;
}

/* 00222290: signed16 affinity from descriptor+2, except ID0 returns0. */
int16_t cmbGetHeartsAisyo(uint8_t id)
{
    return id == 0 ? 0 : g_cmbHeartsRecords[id].aisyo;
}

/* 002222c0: normal six signed bytes at+6, mastered six at+12. */
int8_t cmbGetHeartsDefaultParam(int8_t id, int8_t index, int8_t type)
{
    return type != 0 ? g_cmbHeartsRecords[id].master_param[index]
                    : g_cmbHeartsRecords[id].param[index];
}

/* 00222318: unsigned upgrade byte plus signed base, then signed8 wrap. */
int8_t cmbGetHeartsParamEx(int8_t id, int8_t index, int8_t mode)
{
    int32_t base = cmbGetHeartsDefaultParam(id, index, mode != 0);
    return (int8_t)(base + g_datGlobalWork->hearts_param_upgrades[id][index]);
}

/* 002223a0: choose the mastered table automatically; preserve V0 result. */
int8_t cmbGetHeartsParam(int8_t id, int8_t index)
{
    return cmbGetHeartsParamEx(id, index, cmbChkHeartsMaster((uint8_t)id));
}

/* 00222408: chosen alias; native HD AddHeartsParam body is opaque. The PS2
 * explicitly sign-extends low8 of its unsigned interface before the callee. */
void ps2HeartsAddParam(uint8_t id, datUnitWork_PS2 *unit)
{
    for (int8_t i = 0; i < 6; ++i)
        unit->param[i] = (int8_t)(unit->param[i] + cmbGetHeartsParam((int8_t)id, i));
}

/* 00222470: subtract the same effective parameters with byte wrapping. */
void cmbSubHeartsParam(uint8_t id, datUnitWork_PS2 *unit)
{
    for (int8_t i = 0; i < 6; ++i)
        unit->param[i] = (int8_t)(unit->param[i] - cmbGetHeartsParam((int8_t)id, i));
}

/* 001feda0: ushort equality; first signed8 index, or -1 for no match. */
int8_t cmbChkSkillOwner(uint16_t skill, datUnitWork_PS2 *unit)
{
    for (uint32_t i = 0; i < unit->skillcnt; ++i)
        if (unit->skill[i] == skill) return (int8_t)i;
    return -1;
}

/* 002226b8: start at the global learned count, return the first nonzero skill
 * with nonzero signed required level <= unit level and no existing ownership. */
uint16_t cmbChkGetHeartsSkill(uint8_t id, datUnitWork_PS2 *unit)
{
    for (int32_t i = cmbGetHeartsAfterSkillNums(id); i < 8; ++i) {
        const cmbHeartsSkillEntry_PS2 *entry = &g_cmbHeartsRecords[id].skills[i];
        if (entry->skill != 0 && entry->level != 0 && unit->level >= entry->level
            && cmbChkSkillOwner(entry->skill, unit) < 0)
            return entry->skill;
    }
    return 0;
}

/* 00232998/002329b8/002329d8: original immutable position table345e58. */
int8_t cmpGetHeartsFromPos(int8_t index)
{
    return g_cmpHeartsPositions[index].id;
}

int8_t cmpGetHeartsIconTypeFromPos(int8_t index)
{
    return g_cmpHeartsPositions[index].icon_type;
}

uint32_t cmpGetHeartsIconColorFromPos(int8_t index)
{
    return g_cmpHeartsPositions[index].icon_color;
}
