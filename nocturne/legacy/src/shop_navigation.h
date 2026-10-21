#ifndef NOCTURNE_SHOP_NAVIGATION_H
#define NOCTURNE_SHOP_NAVIGATION_H
#include <stdint.h>
void *nocturneResolveShopNavigationAddress(uint32_t address);
void ps2ShopCursorInvisibleMove_00241958(uint64_t cursor,uint64_t direction);
void ps2ShopCursorPositionSet_00241AF0(uint64_t position,uint64_t cursor);
void ps2ShopCursorReset_00241B10(uint64_t cursor);
uint64_t ps2ShopCursorIndexSelectable_00241B60(uint64_t cursor);
uint64_t ps2ShopCursorAtTop_00241B90(uint64_t cursor);
uint64_t ps2ShopCursorAtBottom_00241C00(uint64_t cursor);
uint64_t ps2ShopCursorMoveEx_00241C90(uint64_t cursor,uint64_t direction,uint64_t margin);
void ps2ShopCursorActiveEffectUpdate_00241FA8(uint64_t cursor);
uint64_t ps2ShopCursorMove_00241FD0(uint64_t cursor,uint64_t direction);
uint64_t ps2ShopCursorMoveIgnore_00242028(uint64_t cursor);
uint64_t ps2ShopCursorMove2_00242050(uint64_t cursor,uint64_t direction);
void ps2ShopCursorListEnd_00242238(uint64_t cursor);
uint64_t ps2ShopCursorPadMask_00242258(uint64_t cursor,uint64_t pad,uint64_t target);
#endif
