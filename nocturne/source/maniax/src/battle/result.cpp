// The battle's result (original unit: nbResultProcess): US Maniax's own (shared/src/battle/result.cpp has the rest).
#include "nocturne/battle/result.hpp"

#include "nocturne/data/ids.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

// nbResultAddExp @ 0x0024C060: only a stock demon with skill 0x162 shares,
// 1/n of the experience (n: that skill's).
bool stockExpShare(const UnitWork& unit, int32_t& exp)
{
    if (!dat::hasSkill(unit, 0x162))
        return false;
    if (exp > 0) {
        const int32_t n = dat::specialSkill(0x162).n;
        if (n == 0)
            divideByZeroTrap();
        exp /= n;
    }
    return true;
}

} // namespace nocturne::nb
