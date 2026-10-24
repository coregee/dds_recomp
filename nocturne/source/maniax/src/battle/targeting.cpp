// Targeting (original unit: nbAction): US Maniax's own (shared/src/battle/targeting.cpp has the rest).
#include "nocturne/battle/targeting.hpp"

namespace nocturne::nb {

// nbGetTargetTypeRuleArea @ 0x00258DE8: a skill's target type and rule as
// its record has them.
void adjustSkillTarget(int32_t, bool, uint8_t&, uint8_t&) {}

// ... a summon targets the empty party slots (rule 12) while the party has
// fewer than four, else rule 2.
int32_t summonRule(const UnitWork&, const MainProcessData& main) { return main.playerpcnt < 4 ? 12 : 2; }

} // namespace nocturne::nb
