#include "field_delete.h"

static int flag_qualified(const datUnitWork_PS2 *unit)
{
    uint32_t flags = unit->flag;
    return (flags & UINT32_C(1)) != 0
        && (flags & UINT32_C(4)) == 0
        && (flags & UINT32_C(0x10)) == 0
        && (flags & UINT32_C(0x800)) == 0;
}

/* PS2 00123a30. The native named method is void; the original retains the
 * real datDelDevil removal result, including zero when no ordinal matches. */
int32_t fldAnahoriSelectDel(void)
{
    datGlobalWork_PS2 *work = g_datGlobalWork;
    int32_t ordinal = 0;
    for (unsigned slot = 0; slot < 16; ++slot) {
        const datUnitWork_PS2 *unit = &work->units[slot];
        if (flag_qualified(unit)) {
            uint16_t hp = unit->hp;
            /* LW index is the HP-zero branch's delay slot, so even HP0
             * reads it. No stored eligible_count gate occurs in this body. */
            int32_t wanted = g_fldAnahoriState->index;
            if (hp == 0) continue;
            if (wanted == ordinal) {
                if (unit->param[0] >= 21) {
                    evtBitOn(0x504);
                    work = g_datGlobalWork;
                }
                return datDelDevil((int32_t)work->units[slot].id);
            }
            ++ordinal;
        }
    }
    return 0;
}

/* PS2 0015a688: ignore deletion result and report script-command success. */
int32_t fldCommand_FLD_ANAHORI_DEL(void)
{
    (void)fldAnahoriSelectDel();
    return 1;
}
