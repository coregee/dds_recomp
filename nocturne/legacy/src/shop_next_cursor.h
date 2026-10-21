#ifndef NOCTURNE_SHOP_NEXT_CURSOR_H
#define NOCTURNE_SHOP_NEXT_CURSOR_H
#include <stdint.h>

void *nocturneResolveShopNextCursorAddress(uint32_t address);
void ps2ShopCursorEffectsInitialize_002416D0(uint64_t cursor);
void ps2ShopCursorEffectSet_00241728(uint64_t target,uint64_t type,uint64_t speed,uint64_t effect);
uint64_t ps2ShopCursorEffectTimer_00241768(uint64_t target,uint64_t effect);
uint64_t ps2ShopCursorEffectType_00241780(uint64_t target,uint64_t effect);
void ps2ShopCursorEffectsUpdate_00241798(uint64_t cursor);
/* Native V0 inherits the real memset destination cursor+8; the original
 * source return typedef is unresolved despite the authenticated HD VOID role. */
uint64_t ps2ShopCursorGeometryInitialize_00241820(uint64_t cursor,uint64_t x,uint64_t y,
    uint64_t width,uint64_t height,uint64_t stepY);
void ps2ShopCursorInitialize_002418B8(uint64_t cursor,uint64_t count,uint64_t shiftMax,uint64_t strings);
void ps2ShopCursorListCountChange_00242118(uint64_t count,uint64_t cursor);
#endif
