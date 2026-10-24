// The presentation queue (original unit: nbKoukaProcess): US Maniax's own (shared/src/battle/kouka.cpp has the rest).
#include "nocturne/battle/kouka.hpp"

namespace nocturne::nb {

// nbMakeNewPressPacket @ 0x00264368: none.
bool versionPressResult(int32_t&, int32_t, int32_t&, int32_t&) { return false; }

// nbMakeBadKaifukuPacket @ 0x002645A8: the unit's.
uint32_t curedAilment(int32_t, uint32_t bad) { return bad; }

} // namespace nocturne::nb
