// The shops (original unit: fclShopCalc). Rewritten from the original
// instructions.
#include "nocturne/facility/shop.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/build.hpp"

namespace nocturne::fcl {

namespace {

uint32_t shopWork() { return guest::table<const uint32_t>(address::ShopWorkPointer)[0]; }
int32_t openPlace() { return guest::table<const int8_t>(shopWork() + shop::Place)[0]; }
const ShopPack& pack(int32_t place) { return guest::table<const ShopPack>(address::ShopPack)[packOf(place)]; }

} // namespace

// ps2ShopItemId_002071E0 @ 0x002071E0
uint16_t listedItem(int32_t index, bool selling)
{
    return guest::table<const uint16_t>(shopWork() + (selling ? shop::SellList : shop::BuyList))[index];
}

// ps2ShopPackId_00207210 @ 0x00207210
uint8_t packOf(int32_t place)
{
    const ShopPlace& p = guest::table<const ShopPlace>(address::ShopPlace)[place];
    const bool second = p.pack_bit >= 0 && evt::BitCheck(p.pack_bit) != 0;
    return p.pack[second ? 1 : 0];
}

// ps2ShopItemCount_00207290 @ 0x00207290
int32_t packItemCount(int32_t place)
{
    int32_t count = 0;
    for (const ShopPack::Entry& entry : pack(place).entries)
        if (entry.item != 0)
            ++count;
    return count;
}

// ps2ShopItemPrice_002073D8 @ 0x002073D8. The buy rate is the pack slot's
// at the list's index, though the list skips Magatama already owned.
uint32_t itemPrice(int32_t index, bool selling)
{
    const uint32_t price = dat::item(listedItem(index, selling)).price;
    if (selling)
        return price >> 1;
    const ShopPack& p = pack(openPlace());
    const uint16_t rate = p.entries[index].rate != 0 ? p.entries[index].rate : p.rate;
    const uint32_t buy = price * rate / 100;
    return evt::BitCheck(EventBit::NormalDifficulty) ? buy : hardBuyPrice(buy);
}

} // namespace nocturne::fcl

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::fcl {

#if NOCTURNE_HARDTYPE
// Hard doubles the buy price (US Maniax triples it; shpCalcItemPrice,
// 0x00207480).
uint32_t hardBuyPrice(uint32_t price) { return price * 2; }
#else
// Hard triples the buy price (shpCalcItemPrice, 0x00207480).
uint32_t hardBuyPrice(uint32_t price) { return price * 3; }
#endif

} // namespace nocturne::fcl
