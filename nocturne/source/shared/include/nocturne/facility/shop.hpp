// The shops (original unit: fclShopCalc): what a shop sells and at what
// price.
//
// A shop place (0x32F650, 6 bytes each) names two item packs; event bit
// `pack_bit` (if not negative) picks the second. A pack (0x32F680, 0x82
// bytes each) lists up to 32 items, each with a price rate in percent (0:
// the pack's own rate). The open shop's work, at the word gp-0x2244, holds
// the place and the lists the menus show.
#pragma once

#include <cstdint>

#include "nocturne/address.hpp"

namespace nocturne::fcl {

struct ShopPlace {
    uint16_t unknown0;
    int16_t pack_bit;                  // event bit choosing pack[1]; negative: always pack[0]
    uint8_t pack[2];
};
static_assert(sizeof(ShopPlace) == 6);

struct ShopPack {
    uint16_t rate;                     // percent of the item's price, for items without their own
    struct Entry {
        uint16_t item;                 // 0: none
        uint16_t rate;
    } entries[32];
};
static_assert(sizeof(ShopPack) == 0x82);

namespace address {
inline constexpr uint32_t ShopPlace = addr(0x0032f650);
inline constexpr uint32_t ShopPack = addr(0x0032f680);
inline constexpr uint32_t ShopWorkPointer = addr(0x00551f2c);   // gp-0x2244
} // namespace address

namespace shop {
inline constexpr uint32_t Place = 0x19;       // int8: the shop place
inline constexpr uint32_t BuyList = 0x2200;   // uint16[32]: item IDs on sale
inline constexpr uint32_t SellList = 0x2244;  // uint16[]: the party's items to sell
} // namespace shop

// shpGetItemID: the item at `index` of the buy list (or, `selling`, the
// sell list).
uint16_t listedItem(int32_t index, bool selling);
// shpGetPackID: the pack shop place `place` sells from.
uint8_t packOf(int32_t place);
// shpGetShopItemNums: how many items the place's pack lists.
int32_t packItemCount(int32_t place);
// shpCalcItemPrice: what the item at `index` costs to buy (the item's price
// at the pack's rate for that slot; more on Hard, by version), or fetches
// when sold (half its price).
uint32_t itemPrice(int32_t index, bool selling);

// [version] The buy price on Hard (source/<version>/src/facility/shop.cpp).
uint32_t hardBuyPrice(uint32_t price);

} // namespace nocturne::fcl
