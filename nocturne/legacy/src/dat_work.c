#include "nocturne.h"

/* PS2 0x00243b98. 0x8000 is a distinct high-bit operation. */
void datOverwriteBadStat(datUnitWork_PS2 *work, uint32_t badstat)
{
    if (badstat == 0x8000) work->badstat |= 0x8000;
    else work->badstat = (uint16_t)((work->badstat & 0xf000) | (badstat & 0xfff));
}

/* PS2 0x00243bd0. Preserve the numeric priority comparison; this is
 * not an unconditional bitwise OR of status flags. */
void datSetBadStat(datUnitWork_PS2 *work, uint32_t badstat)
{
    if (badstat == 0x8000) work->badstat |= 0x8000;
    else if ((uint32_t)(work->badstat & 0xfff) < badstat)
        work->badstat = (uint16_t)((work->badstat & 0xf000) | (badstat & 0xfff));
}

/* PS2 0x00243c10. */
void datResetBadStat(datUnitWork_PS2 *work, uint32_t badstat)
{
    work->badstat &= (uint16_t)~badstat;
}

/* Preserve ADDU's 32-bit wrapping addition before the signed clamps. */
static uint32_t add_resource(uint16_t *current, uint16_t maximum, int32_t amount)
{
    int32_t next = (int32_t)((uint32_t)*current + (uint32_t)amount);
    if (next < 0) next = 0;
    if (next > maximum) next = maximum;
    *current = (uint16_t)next;
    return (uint32_t)next;
}

/* PS2 0x00243e28 / 0x00243e50. */
uint32_t datAddHp(datUnitWork_PS2 *work, int32_t hp)
{
    return add_resource(&work->hp, work->maxhp, hp);
}

uint32_t datAddMp(datUnitWork_PS2 *work, int32_t mp)
{
    return add_resource(&work->mp, work->maxmp, mp);
}

/* PS2 0x00245d18. */
int32_t datGetLevelForDraw(datUnitWork_PS2 *work)
{
    return work->level > 99 ? 99 : work->level;
}

/* PS2 0x00244238. */
void datAddMaka(int32_t addmaka)
{
    int32_t next = (int32_t)((uint32_t)g_datGlobalWork->maka + (uint32_t)addmaka);
    if (next < 0) next = 0;
    if (next > 9999999) next = 9999999;
    g_datGlobalWork->maka = next;
}

/* PS2 0x002442c8. */
int32_t datCheckMaka(int32_t maka)
{
    return g_datGlobalWork->maka >= maka;
}
