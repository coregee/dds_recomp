// A talk's opening (original unit: nbNegoProcess): US Maniax's own (shared/src/battle/talk_opening.cpp has the rest).
#include "nocturne/battle/talk_flow.hpp"

namespace nocturne::nb {

// Flow1_10 @ 0x0026D190: a boss battle (stat 1).
bool battleRefusesTalk(const MainProcessData& data) { return (data.stat & 1) != 0; }

} // namespace nocturne::nb
