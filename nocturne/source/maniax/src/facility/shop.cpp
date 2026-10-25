// US Maniax's shop prices.
#include "nocturne/facility/shop.hpp"

namespace nocturne::fcl {

// Hard triples the buy price (shpCalcItemPrice, 0x00207480).
uint32_t hardBuyPrice(uint32_t price) { return price * 3; }

} // namespace nocturne::fcl
