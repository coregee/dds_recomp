// A talk's opening (original unit: nbNegoProcess): Hardtype's own (shared/src/battle/talk_opening.cpp has the rest).
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/data/tables.hpp"

namespace nocturne::nb {

// Flow1_10 @ 0x0026D190 (and 0x2FEF80): a boss battle (stat 1), or an
// encounter with flag 0x40.
bool battleRefusesTalk(const MainProcessData& data)
{
    return (dat::encount(data.encno).flag & 0x40) || (data.stat & 1);
}

} // namespace nocturne::nb
