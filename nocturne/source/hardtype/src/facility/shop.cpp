// Hardtype's shop prices.
#include "nocturne/facility/shop.hpp"

namespace nocturne::fcl {

// Hard doubles the buy price (US Maniax triples it; shpCalcItemPrice,
// 0x00207480).
uint32_t hardBuyPrice(uint32_t price) { return price * 2; }

} // namespace nocturne::fcl
