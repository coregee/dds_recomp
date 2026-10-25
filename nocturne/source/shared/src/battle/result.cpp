// The battle's result (original unit: nbResultProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/result.hpp"

#include "nocturne/battle/calc.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/fusion/growth.hpp"
#include "nocturne/build.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"

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

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::nb {

#if NOCTURNE_HARDTYPE
// nbResultAddExp @ 0x0024C060 (in place): every stock demon shares, in full
// with skill 0x162 and three quarters without.
bool stockExpShare(const UnitWork& unit, int32_t& exp)
{
    const bool skill = dat::hasSkill(unit, 0x162);
    if (exp > 0 && !skill)
        exp = static_cast<int32_t>(static_cast<uint32_t>(exp) * 3u) >> 2;
    return true;
}
#else
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
#endif

} // namespace nocturne::nb
