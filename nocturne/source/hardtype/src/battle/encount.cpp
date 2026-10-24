// Random encounters (original unit: nbEncount): Hardtype's own (shared/src/battle/encount.cpp has the rest).
#include "nocturne/battle/encount.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

// 0x002FEB00 (in place of nbGetEncountJoken for nbGetEncountMax and
// nbEncountCalc): the moon table is looked at only when the table chosen
// without it has a first entry with a weight.
int32_t encounterTable(int32_t pack)
{
    const int32_t plain = encounterTableIn(pack, false);
    const uint32_t firstWeight = dat::address::EncountPack + static_cast<uint32_t>(pack) * sizeof(EncountPack) + 26 +
                                 dat::kEncounterTableSize * static_cast<uint32_t>(plain);
    return encounterTableIn(pack, *guest::table<uint16_t>(firstWeight) != 0);
}

// nbGetEncountMax @ 0x0028CB68 (and 0x2FDE30): in Kagutsuchi's phase 8 the
// threshold is at least 420 (210 for a base under 227).
int32_t adjustThreshold(int32_t rolled, int32_t base)
{
    if (hardtype::byteAt(hardtype::kMoonPhase) != 8)
        return rolled;
    const int32_t floor = base < 227 ? 210 : 420;
    return rolled < floor ? floor : rolled;
}

// nbCheckEncountLevel @ 0x0028CEE0 (and 0x2FDE80): the group's average must
// be above half the Demi-fiend's level plus 1 (at most 100), or above twice
// it once he holds 25 Magatama.
bool levelAllowsEncounter(int32_t average, int32_t player)
{
    uint32_t level = static_cast<uint32_t>(player + 1);
    if (static_cast<int32_t>(level) >= 100)
        level = 100;
    level <<= 1;
    if (hardtype::byteAt(hardtype::kHeart24) == 0)
        level >>= 2;
    return static_cast<int32_t>(level) < average;
}

} // namespace nocturne::nb
