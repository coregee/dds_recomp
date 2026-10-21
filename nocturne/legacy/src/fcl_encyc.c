/* Reviewed SLUS_209.11 compendium functions; HD names are reference evidence.
 * 00219df0 SetElem; 00216b20 Search; 00216b78 GetNum;
 * 00216b90 GetRatio2; 00216a18 Regist. */
#include "nocturne.h"
#include <string.h>

void fclEncyc_SetElem(fclEncycElem_PS2 *elem, datUnitWork_PS2 *unit)
{
    memset(elem, 0, sizeof(*elem));
    elem->id = unit->id;
    elem->maxhp = unit->maxhp;
    elem->maxmp = unit->maxmp;
    elem->exp = unit->exp;
    elem->level = unit->level;
    memcpy(elem->param, unit->param, sizeof(elem->param));
    memcpy(elem->skill, unit->skill, sizeof(elem->skill));
    memcpy(elem->skillparam, unit->skillparam, sizeof(elem->skillparam));
    elem->skillcnt = unit->skillcnt;
    memcpy(elem->mitamaparam, unit->mitamaparam, sizeof(elem->mitamaparam));
    memcpy(elem->levelupparam, unit->levelupparam, sizeof(elem->levelupparam));
    memcpy(elem->keisyoskill, unit->keisyoskill, sizeof(elem->keisyoskill));
    memcpy(elem->keiattr, unit->keiattr, sizeof(elem->keiattr));
    elem->hensinmae = unit->hensinmae;
    elem->flag = unit->flag & 0x240;
    elem->hensinmaeexp = unit->hensinmaeexp;
}

int32_t fclEncycSearch(int32_t id)
{
    for (int32_t i = 0; i < g_datGlobalWork->encyc_count; ++i)
        if (id == g_datGlobalWork->encyc_records[i].id)
            return i;
    return -1;
}

int32_t fclEncycGetNum(void)
{
    return g_datGlobalWork->encyc_count;
}

int32_t fclEncycGetRatio2(void)
{
    int32_t count = fclEncycGetNum();
    int32_t ratio = (int32_t)((uint32_t)count * 100u) / 184;
    return count > 0 && ratio < 1 ? 1 : ratio;
}

int32_t fclEncycRegist(datUnitWork_PS2 *unit, int32_t overwrite)
{
    int32_t index = fclEncycSearch(unit->id);
    int32_t result = 1;
    if (index < 0) {
        index = g_datGlobalWork->encyc_count;
        if (index >= 184) {
            nocturne_diagnostic_printf("****** FATAL!! The encyclopedia record is bound to burst!!!\n");
            return -1;
        }
        g_datGlobalWork->encyc_count = index + 1;
        result = 0;
    } else if (overwrite == 0) {
        return -1;
    }
    fclEncyc_SetElem(&g_datGlobalWork->encyc_records[index], unit);
    if (fclEncycGetRatio2() < 100)
        evtBitOff(0x913);
    else
        evtBitOn(0x913);
    return result;
}
