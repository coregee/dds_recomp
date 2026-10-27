// The level-up screen after a battle (original unit: rstinit). Rewritten from
// the original instructions.
#include "nocturne/result/level_up.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/fusion/growth.hpp"

namespace nocturne::rst {

// rstChkLevelUpTarget @ 0x0021F788
bool levelUpDue(const UnitWork& unit)
{
    if (!(unit.flag & UnitFlag::Valid) || (unit.badstat & static_cast<uint16_t>(Ailment::Dead)))
        return false;
    return cmb::levelUpCount(unit, 0) > 0;
}

// rstChkResultEntry @ 0x0021F7D8
bool anyLevelUpDue()
{
    for (const UnitWork& unit : dat::globalWork().units)
        if (levelUpDue(unit))
            return true;
    return false;
}

} // namespace nocturne::rst
