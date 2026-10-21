/* Original instructions at001ff0c8..001ff170 determine behavior. */
#include "stock_compaction.h"

void ps2CompactStockUnits(datUnitWork_PS2 *units, uint8_t count)
{
    uint8_t write_index = 0;
    for (uint32_t read_index = 0; read_index < (uint32_t)count; ++read_index) {
        datUnitWork_PS2 *source = &units[read_index];
        if (source->id != 0) {
            if ((uint32_t)write_index < read_index) {
                cmbCopyCustomDevilToStock(&units[write_index], source);
                ps2ClearUnitWork(source);
            }
            write_index = (uint8_t)((uint32_t)write_index + UINT32_C(1));
        }
    }
}
