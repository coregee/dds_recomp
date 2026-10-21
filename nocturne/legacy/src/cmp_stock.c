#include "nocturne.h"
#include <string.h>

/* PS2 0x00240a50. No bounds check occurs in the original. */
void cmpAddStockListGBWK(int8_t index)
{
    g_datGlobalWork->stock_list[g_datGlobalWork->stock_count++] = (uint8_t)index;
}

/* PS2 0x002409f0. The vacated final byte is not cleared after shifting. */
void cmpDeleteStockListGBWK(int8_t index)
{
    g_datGlobalWork->stock_list[index] = 0;
    for (int32_t i = (int32_t)index + 1; i < g_datGlobalWork->stock_count; ++i)
        g_datGlobalWork->stock_list[i - 1] = g_datGlobalWork->stock_list[i];
    --g_datGlobalWork->stock_count;
}

/* PS2 0x00240808. Preserve the original stop counter, which increments
 * when an empty slot is removed. It is not a count of occupied slots. */
void cmpReplaceStockGBWK(void)
{
    int8_t removed = 0;
    for (int32_t i = 4; i < 16 && removed != g_datGlobalWork->stock_count; ++i) {
        if ((g_datGlobalWork->units[i].flag & 1) == 0) {
            for (int32_t j = i; j < 15; ++j)
                memcpy(&g_datGlobalWork->units[j], &g_datGlobalWork->units[j + 1], sizeof(datUnitWork_PS2));
            memset(&g_datGlobalWork->units[15], 0, sizeof(datUnitWork_PS2));
            for (int32_t j = 0; j < g_datGlobalWork->stock_count; ++j)
                if (g_datGlobalWork->stock_list[j] >= i) --g_datGlobalWork->stock_list[j];
            ++removed;
        }
    }
}

/* PS2 0x0022e168. This searches listed unit IDs rather than all 16 slots. */
int32_t cmpRemoveDevilEx(uint16_t id)
{
    for (int32_t i = 0; i < g_datGlobalWork->stock_count; ++i) {
        datUnitWork_PS2 *work = &g_datGlobalWork->units[g_datGlobalWork->stock_list[i]];
        if (work->id == id) {
            memset(work, 0, sizeof(*work));
            cmpDeleteStockListGBWK((int8_t)i);
            cmpReplaceStockGBWK();
            return 1;
        }
    }
    return 0;
}

/* PS2 0x00245c78. Unlike HD, return the tail-called removal result. */
int32_t datDelDevil(int32_t id)
{
    return cmpRemoveDevilEx((uint16_t)id);
}
