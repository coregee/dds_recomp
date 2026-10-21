#include "nocturne.h"

/* 00243f40: flag20 selects eight immutable descriptor skills. Other units
 * use their own skill count and inline skills. No incoming-ID truncation. */
int32_t datCheckSyojiSkill(datUnitWork_PS2 *work, uint32_t skill)
{
    const uint16_t *skills = work->skill;
    uint32_t count = work->skillcnt;
    if ((work->flag & 0x20) != 0) {
        skills = g_datDevilSkillTable[work->id].skill;
        count = 8;
    }
    for (uint32_t i = 0; i < count; ++i)
        if (skills[i] == skill) return 1;
    return 0;
}

/* 00245638: active units with party flag2 across all sixteen physical slots. */
int32_t datCheckSkillInParty(int32_t skillid)
{
    for (int32_t i = 0; i < 16; ++i) {
        datUnitWork_PS2 *work = &g_datGlobalWork->units[i];
        if ((work->flag & 3) == 3 && datCheckSyojiSkill(work, (uint32_t)skillid))
            return 1;
    }
    return 0;
}
