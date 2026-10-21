#include "vif_reset.h"

/* 002c8348: VIF1 reset, VU1 reset request, two live quadword transfers,
 * then the GIF reset store from the original JR delay slot. */
void ps2VifGifResetPath(void)
{
    nocturneVifResetWrite32(UINT32_C(0x10003c10), 1);
    nocturneVifResetWrite32(UINT32_C(0x10003c20), 2);
    nocturneVifResetSync(0);
    uint32_t control = nocturneVifResetReadControl(12);
    nocturneVifResetWriteControl(12, control | UINT32_C(0x200));
    nocturneVifResetSync(16);
    NocturneQuadword packet = nocturneVifResetRead128(UINT32_C(0x529f30));
    nocturneVifResetWrite128(UINT32_C(0x10005000), packet);
    packet = nocturneVifResetRead128(UINT32_C(0x529f40));
    nocturneVifResetWrite128(UINT32_C(0x10005000), packet);
    nocturneVifResetWrite32(UINT32_C(0x10003000), 1);
}
