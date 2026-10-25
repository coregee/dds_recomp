// The battle's result (original unit: nbResultProcess): Hardtype's own (shared/src/battle/result.cpp has the rest).
#include "nocturne/battle/result.hpp"

#include "nocturne/data/unit.hpp"

namespace nocturne::nb {

// nbResultAddExp @ 0x0024C060 (in place): every stock demon shares, in full
// with skill 0x162 and three quarters without.
bool stockExpShare(const UnitWork& unit, int32_t& exp)
{
    const bool skill = dat::hasSkill(unit, 0x162);
    if (exp > 0 && !skill)
        exp = static_cast<int32_t>(static_cast<uint32_t>(exp) * 3u) >> 2;
    return true;
}

} // namespace nocturne::nb
