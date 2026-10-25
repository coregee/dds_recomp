// The battle's result (original unit: nbResultProcess): the spoils and the
// experience the party earns.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"

namespace nocturne::nb {

// GetAddExp: `exp`, but no more than takes unit `index` (in the global work)
// to one short of its experience for level 256.
int32_t cappedExp(int32_t index, int32_t exp);

// nbResultAddExp: the items and Macca won, and each living unit's
// experience: the party's in full, the stock's by version.
void grantSpoils(MainProcessData& main);

// [version] A stock demon's share of `exp` (false: none)
//.
bool stockExpShare(const UnitWork& unit, int32_t& exp);

} // namespace nocturne::nb
