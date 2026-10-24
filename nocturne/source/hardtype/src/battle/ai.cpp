// The enemy AI (original unit: nbAi): Hardtype's own (shared/src/battle/ai.cpp has the rest).
#include "nocturne/battle/ai.hpp"

#include "nocturne/battle/combatant.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/hardtype.hpp"

namespace nocturne::nb::ai {

// nbAiChkJoken @ 0x00286730: Hardtype adds types 29 (Kagutsuchi's phase is
// n), 60 and 61 (the press turn gauge is at least / at most n), through its
// dispatch table's empty slots.
bool versionCondition(int32_t type, int32_t n, bool& holds)
{
    if (type != 29 && type != 60 && type != 61)
        return false;
    holds = hardtype::aiCondition(type, n);
    return true;
}

// ... types 60 and 61 overwrite the register that held the action, so the
// selection's mask lands in low memory instead.
uint32_t& selectionAfterCondition(ActionProcessData& act, int32_t type)
{
    if (type == 60 || type == 61)
        return *guest::table<uint32_t>(hardtype::pressGaugeRegister() + 0x190);
    return act.aiselect;
}

// nbAiAiChk @ 0x002867A8 (and 0x2FDD20): the selection is cleared through a
// register before it is set, so the zero goes to its caller's loop counter
// (index + 1) + 0x190 in low memory, and the selection stays.
void clearSelectionForCheck(ActionProcessData&, int32_t index) { *guest::table<uint32_t>(static_cast<uint32_t>(index + 1) + 0x190) = 0; }

// nbRunAiSub @ 0x00287B40: the targets are read with the action index taken
// from the wrong register, which still holds what nbAiChkClose last computed:
// the command when it isn't a skill, the skill check's 0 when the skill is
// usable (so the first action's targets), or the devil ID times 4 when it
// isn't (targets read from far past the table).
int32_t targetedAction(const ActionProcessData& act, int32_t)
{
    const UnitWork& unit = *act.work;
    const int16_t command = unit.nowcommand;
    if (command != 0 && command != 1 && command != 5)
        return command;
    const int32_t skill = command == 0 ? 0 : unit.nowindex;
    if (checkSkillUse(act.form->formindex, skill) <= 0)
        return 0;
    return 4 * unit.id;
}

} // namespace nocturne::nb::ai
