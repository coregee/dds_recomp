#include "nocturne.h"

/* 00243e78: signed byte parameters, with mitama excluded by flag4. */
int32_t datGetBaseParam(datUnitWork_PS2 *work, int32_t paratype)
{
    int32_t value = work->param[paratype] + work->skillparam[paratype];
    if ((work->flag & 4) == 0) value += work->mitamaparam[paratype];
    if (value < 1) value = 1;
    return value > 40 ? 40 : value;
}

/* 00243ee0: status200 leaves parameter4 unchanged. */
int32_t datGetParam(datUnitWork_PS2 *work, int32_t paratype)
{
    int32_t value = datGetBaseParam(work, paratype);
    if ((work->badstat & 0xfff) == 0x200 && paratype != 4) value = 1;
    return value > 0 ? value : 1;
}

/* 002440c0: map individual status values, not arbitrary bit combinations. */
int32_t datGetBadStatusAttr(int32_t bad)
{
    switch (bad) {
    case 1: return 3;
    case 2: return 2;
    case 4: case 8: case 0x80: return 10;
    case 0x10: case 0x100: return 9;
    case 0x20: case 0x40: return 8;
    case 0x200: case 0x1000: case 0x2000: case 0x4000: return 5;
    case 0x400: return 7;
    default: return -1;
    }
}

/* 00244200: integer percentage strictly below25; zero denominator BREAK7. */
int32_t datCheckDying(datUnitWork_PS2 *work)
{
    if (work->maxhp == 0) nocturne_break(7);
    return (uint32_t)work->hp * 100u / work->maxhp < 25u;
}

/* 002443f8 / 00244410: callers supply valid item indexes. */
int32_t datCheckItem(int32_t id, int32_t num)
{
    return num <= g_datGlobalWork->item_counts[id];
}

int32_t datCheckItemFull(int32_t id)
{
    uint8_t count = g_datGlobalWork->item_counts[id];
    return id < 0x70 ? count >= 99 : count != 0;
}

/* 00244598: the player is unit slot0. */
int32_t datGetPlayerLevel(void)
{
    return g_datGlobalWork->units[0].level;
}

/* 00244eb8: capacity comparison counts flag1 in physical slots4..15. */
int32_t datCheckStockFull(void)
{
    int32_t count = 0;
    for (int32_t i = 4; i < 16; ++i)
        count += g_datGlobalWork->units[i].flag & 1;
    return g_datGlobalWork->stock_capacity <= count;
}

/* 00245250: first active non-flag4 unit with flag400 and matching unique ID. */
int32_t datGetUniqueDevilId(int32_t uid)
{
    for (int32_t i = 0; i < 16; ++i) {
        datUnitWork_PS2 *work = &g_datGlobalWork->units[i];
        if ((work->flag & 1) != 0 && (work->flag & 4) == 0 &&
            (work->flag & 0x400) != 0 && work->uniqueid == uid)
            return work->id;
    }
    return -1;
}
