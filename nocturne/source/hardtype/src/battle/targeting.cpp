// Targeting (original unit: nbAction): Hardtype's own (shared/src/battle/targeting.cpp has the rest).
#include "nocturne/battle/targeting.hpp"

#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb {

// nbGetTargetTypeRuleArea @ 0x00258DE8 (and 0x2FEAB0, 0x2FEA60): called by
// the AI's target choice (its return address 0x287AAC), skills 0x45 and 0x46
// have their type and rule flipped by bit 1 of the option byte.
void adjustSkillTarget(int32_t skill, bool fromAi, uint8_t& targettype, uint8_t& targetrule)
{
    if (!fromAi || (skill != 0x45 && skill != 0x46))
        return;
    const uint8_t flip = static_cast<uint8_t>(hardtype::byteAt(hardtype::kOptions) >> 1);
    targettype ^= flip;
    targetrule ^= flip;
}

// ... (and 0x2FE2F0) a summon by anyone but the Demi-fiend (his unit in the
// global work) targets rule 1.
int32_t summonRule(const UnitWork& unit, const MainProcessData& main)
{
    if (guest::addressOf(&unit) != hardtype::kDemiFiend)
        return 1;
    return main.playerpcnt < 4 ? 12 : 2;
}

} // namespace nocturne::nb
