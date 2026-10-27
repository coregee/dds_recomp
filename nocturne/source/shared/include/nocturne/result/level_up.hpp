// The level-up screen after a battle (original unit: rstinit), as far as
// rewritten: whether anyone is due.
#pragma once

#include "nocturne/data/records.hpp"

namespace nocturne::rst {

// rstChkLevelUpTarget (0x21F788): a valid unit, not dead, with EXP for at
// least one level.
bool levelUpDue(const UnitWork& unit);
// rstChkResultEntry (0x21F7D8): any of the sixteen stock units (by slot, not
// the stock's order).
bool anyLevelUpDue();

// rstGetEquipHeartsAisyo (0x220000, original unit rstcalc): the affinity row
// of the Magatama the Demi-fiend has on (0 for none).
int16_t equippedHeartsAffinity();

} // namespace nocturne::rst
