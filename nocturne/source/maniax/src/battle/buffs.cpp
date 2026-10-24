// Buffs (original unit: nbCalc): US Maniax's own (shared/src/battle/buffs.cpp has the rest).
#include "nocturne/battle/buffs.hpp"

namespace nocturne::nb {

// nbGetHojoCounterMax @ 0x00267EC8, nbGetHojoCounterMin @ 0x00267F18: the
// stat counters go from -4 to 4.
int32_t statBuffMax(uint32_t) { return 4; }
int32_t statBuffMin(uint32_t) { return -4; }

} // namespace nocturne::nb
