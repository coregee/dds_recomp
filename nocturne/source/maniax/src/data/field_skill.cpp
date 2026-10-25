// Field skills and party damage: US Maniax's own
// (shared/src/data/field_skill.cpp has the rest).
#include "nocturne/data/field_skill.hpp"

#include "nocturne/data/ids.hpp"

namespace nocturne::dat {

// datPartyDamage @ 0x002447C0: mode 3 leaves Dante's HP.
bool sparedFromLastHp(const UnitWork& unit) { return unit.id == devil::Dante; }

} // namespace nocturne::dat
