// The battle's result (original unit: nbResultProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/result.hpp"

#include "nocturne/battle/calc.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/fusion/growth.hpp"

namespace nocturne::nb {

// GetAddExp @ 0x0024BFF0
int32_t cappedExp(int32_t index, int32_t exp)
{
    const GlobalWork& global = dat::globalWork();
    const uint32_t ceiling = cmb::expForLevel(global.units[index & 0xff], 0x100);
    int32_t room = static_cast<int32_t>(ceiling - 1 - static_cast<uint32_t>(global.units[index].exp));
    if (room < 0)
        room = 0;
    return exp < room ? exp : room;
}

// nbResultAddExp @ 0x0024C060
void grantSpoils(MainProcessData& main)
{
    for (int32_t i = 0; i < 4; ++i)
        if (main.item[i] != 0 && main.itemcnt[i] != 0)
            dat::addItem(main.item[i], main.itemcnt[i]);
    dat::addMacca(earnedMacca(main));
    for (int32_t i = 0; i < 16; ++i) {
        int32_t exp = earnedExp(main);
        UnitWork& unit = dat::globalWork().units[i];
        if (!(unit.flag & UnitFlag::Valid))
            continue;
        if (!(unit.flag & UnitFlag::InParty) && !stockExpShare(unit, exp))
            continue;
        if (unit.ailment() == static_cast<uint16_t>(Ailment::Dead) || unit.hp == 0)
            continue;
        dat::addExp(unit, cappedExp(i, exp));
    }
}

} // namespace nocturne::nb
