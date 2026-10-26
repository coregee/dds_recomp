// The units' process (original unit: nbUnitProcess), as far as rewritten:
// its start.
#pragma once

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbInitUnitProcess (0x24F388): the units' process ("nb_unit") under the
// battle's, and their drawing ("nb_unitdraw") under it.
void startUnitProcess(MainProcessData& main);

} // namespace nocturne::nb
