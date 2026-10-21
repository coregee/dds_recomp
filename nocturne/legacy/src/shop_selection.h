#ifndef NOCTURNE_SHOP_SELECTION_H
#define NOCTURNE_SHOP_SELECTION_H
#include <stdint.h>
void *nocturneResolveShopSelectionAddress(uint32_t address);
uint64_t ps2ShopCommonInput_002411B0(uint64_t control);
void ps2ShopInputSound_002413A0(uint64_t type);
void ps2ShopInputSoundMode_002413B8(uint64_t type,uint64_t mode);
void ps2ShopListCursorMove_002135E0(uint64_t list,uint64_t direction);
void ps2ShopBuyUpdate_00208A90(void);
void ps2ShopSellUpdate_00208C70(void);
void ps2ShopBuyQuantityUpdate_00208DE8(void);
void ps2ShopSellQuantityUpdate_00208FC8(void);
#endif
