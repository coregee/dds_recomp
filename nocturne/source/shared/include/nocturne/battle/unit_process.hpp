// The units' process (original unit: nbUnitProcess), as far as rewritten:
// its start.
#pragma once

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbInitUnitProcess (0x24F388): the units' process ("nb_unit") under the
// battle's, and their drawing ("nb_unitdraw") under it.
void startUnitProcess(MainProcessData& main);

// nbAddUnitStock (0x24D550): a unit into the battle at formation slot
// `formindex`: side 0 a stock unit (globalWork().units[stockno]) in the
// party's first free entry, side 1 an enemy (main.enemyunit[stockno]) in the
// enemies'. The entry's buffs cleared, its affinities set (the Demi-fiend's
// from his Magatama), the slot set up from the unit's visual record; returns
// its standing motion (nbGetMotionNo). Other sides aren't used.
int32_t addUnitToSlot(MainProcessData& main, int32_t side, int32_t stockno, int32_t formindex);

} // namespace nocturne::nb
