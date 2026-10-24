// Combatants (original unit: nbAction): Hardtype's own (shared/src/battle/combatant.cpp has the rest).
#include "nocturne/battle/combatant.hpp"

#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

// nbCheckSkillCost @ 0x00269170 (and 0x2FE080, 0x2FE110), nbCheckSkillUse @
// 0x00269280 (and 0x2FDC20): the acting skill noted, if any (hardtype.hpp).
int32_t checkedSkill(int32_t skill)
{
    const uint16_t acting = hardtype::actingSkill();
    return acting != 0 ? acting : skill;
}

} // namespace nocturne::nb
