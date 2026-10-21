#ifndef NOCTURNE_SHOP_TRANSACTION_H
#define NOCTURNE_SHOP_TRANSACTION_H
#include <stdint.h>
void *nocturneResolveShopTransactionAddress(uint32_t address);
uint64_t ps2ShopItemId_002071E0(uint64_t index,uint64_t mode);
uint64_t ps2ShopPackId_00207210(uint64_t place);
uint64_t ps2ShopItemCount_00207290(uint64_t place);
uint64_t ps2ShopCreateBuyList_002072F8(uint64_t data);
uint64_t ps2ShopItemPrice_002073D8(uint64_t index,uint64_t mode);
uint64_t ps2ShopAffordableQuantity_002074C0(uint64_t index,uint64_t mode);
uint64_t ps2ShopChoiceMaximum_002075B8(uint64_t index,uint64_t mode,uint64_t preserve);
uint64_t ps2ShopFacilityValue_002143C8(uint64_t index,uint64_t value);
void ps2ShopCreateInventoryList_00213C10(uint64_t list,uint64_t mode);
uint64_t ps2ShopItemEligible_00242A18(uint64_t item,uint64_t mode);
#endif
