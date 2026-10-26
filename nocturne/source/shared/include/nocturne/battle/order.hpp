// The turn order (original unit: nbMisc): the side whose turn it is acts in
// order of Agility (ties by formation slot), main.order[] holding party
// indexes (-1 for none) and main.orderindex the one acting.
#pragma once

#include <cstdint>

namespace nocturne::nb {

void addToOrder(int32_t formindex);   // nbAddOrder (0x258048): a newly present unit, after the one acting
void sortOrder(int32_t start);        // nbSortOrder (0x2580E8): from `start`, by Agility
void buildOrder(int32_t side);        // nbSetOrderSide (0x258280): 0 the party's, 1 the enemies'; the first acts
void resetOrder();                    // nbSetOrder (0x2583D8): the order of the side whose turn it is
void advanceOrder();                  // nbSetNextOrder (0x258418): the next to act (the order rebuilt past the end)
void updateOrder();                   // nbUpdateOrder (0x2584C8): units out of the battle dropped

} // namespace nocturne::nb
