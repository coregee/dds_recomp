#include "nocturne.h"

/* 00242a88 / 00242ae8: parameter3 HP, parameter2 MP; flag20 bypasses999.
 * MP's original software-double sequence converts2*(level+param), multiplies
 * by1.5, then truncates to int. Every possible ushort-level/clamped-param
 * input yields an exactly represented integral3*(level+param). */
int32_t datGetBaseMaxHp(datUnitWork_PS2 *work)
{
    int32_t value = ((int32_t)work->level + datGetParam(work, 3)) * 6;
    return (work->flag & 0x20) == 0 && value > 999 ? 999 : value;
}

int32_t datGetBaseMaxMp(datUnitWork_PS2 *work)
{
    int32_t value = ((int32_t)work->level + datGetParam(work, 2)) * 3;
    return (work->flag & 0x20) == 0 && value > 999 ? 999 : value;
}

/* 00243c28 / 00243d28: add each owned skill bonus separately after division.
 * Combining percentages before dividing would change truncation behavior. */
uint32_t datGetMaxHp(datUnitWork_PS2 *work)
{
    uint32_t base = (uint32_t)datGetBaseMaxHp(work), bonus = 0;
    if (datCheckSyojiSkill(work, 0x122)) bonus += base * 10 / 100;
    if (datCheckSyojiSkill(work, 0x123)) bonus += base * 20 / 100;
    if (datCheckSyojiSkill(work, 0x124)) bonus += base * 30 / 100;
    uint32_t value = base + bonus;
    return (work->flag & 0x20) == 0 && value > 999 ? 999 : value;
}

uint32_t datGetMaxMp(datUnitWork_PS2 *work)
{
    uint32_t base = (uint32_t)datGetBaseMaxMp(work), bonus = 0;
    if (datCheckSyojiSkill(work, 0x125)) bonus += base * 10 / 100;
    if (datCheckSyojiSkill(work, 0x126)) bonus += base * 20 / 100;
    if (datCheckSyojiSkill(work, 0x127)) bonus += base * 30 / 100;
    uint32_t value = base + bonus;
    return (work->flag & 0x20) == 0 && value > 999 ? 999 : value;
}

/* 00244470: flag4 suppresses descriptor race lookup. */
int32_t datGetRace(datUnitWork_PS2 *work)
{
    return (work->flag & 4) != 0 ? 0 : g_datDevilSkillTable[work->id].race;
}
