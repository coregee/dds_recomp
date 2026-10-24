// Random encounters (original unit: nbEncount): US Maniax's own (shared/src/battle/encount.cpp has the rest).
#include "nocturne/battle/encount.hpp"

namespace nocturne::nb {

// nbGetEncountJoken @ 0x0028C9F0: Kagutsuchi's phase first.
int32_t encounterTable(int32_t pack) { return encounterTableIn(pack, true); }

// nbGetEncountMax @ 0x0028CB68: as rolled.
int32_t adjustThreshold(int32_t rolled, int32_t) { return rolled; }

// nbCheckEncountLevel @ 0x0028CEE0: the Demi-fiend's level is at most the
// group's average plus a quarter of his own.
bool levelAllowsEncounter(int32_t average, int32_t player) { return player <= average + player / 4; }

} // namespace nocturne::nb
