// Buffs (original unit: nbCalc): Hardtype's own (shared/src/battle/buffs.cpp has the rest).
#include "nocturne/battle/buffs.hpp"

namespace nocturne::nb {

namespace {

// Presumably meant to tell the sides apart by the address of their counters:
// at or past 0xDB00 in the low half, raised stats reach 4 and lowered ones
// stop at -2; below, 2 and -4. But the sum is of two registers each caller
// leaves differently: nbSetHojoAddCounter the counters' address plus the new
// value, CheckHojo the party's address plus the number of parties, and the
// AI's checks (nbAiChkEnHojoMax, nbAiChkFrHojoMax) 128 x the slot plus 1,
// always below.
bool highKey(uint32_t callerKey) { return (callerKey & 0xffff) >= 0xdb00; }

} // namespace

// nbGetHojoCounterMax @ 0x00267EC8 (and 0x2FF210)
int32_t statBuffMax(uint32_t callerKey) { return highKey(callerKey) ? 4 : 2; }

// nbGetHojoCounterMin @ 0x00267F18 (and 0x2FF1E0)
int32_t statBuffMin(uint32_t callerKey) { return highKey(callerKey) ? -2 : -4; }

} // namespace nocturne::nb
