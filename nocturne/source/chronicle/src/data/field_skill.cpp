// Field skills and party damage: the JP Chronicle Edition's own
// (shared/src/data/field_skill.cpp has the rest).
#include "nocturne/data/field_skill.hpp"

namespace nocturne::dat {

// datPartyDamage @ 0x002447C0 (Chronicle 0x243C98): mode 3 spares no one;
// the check for devil 0xC0 (Dante in US Maniax) is gone.
bool sparedFromLastHp(const UnitWork&) { return false; }

} // namespace nocturne::dat
