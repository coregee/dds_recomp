// The enemy AI (original unit: nbAi): US Maniax's own (shared/src/battle/ai.cpp has the rest).
#include "nocturne/battle/ai.hpp"

namespace nocturne::nb::ai {

// nbAiChkJoken @ 0x00286730: types 1..28 only.
bool versionCondition(int32_t, int32_t, bool&) { return false; }

// ... a holding condition narrows the AI's selection.
uint32_t& selectionAfterCondition(ActionProcessData& act, int32_t) { return act.aiselect; }

// nbAiAiChk @ 0x002867A8: the selection cleared.
void clearSelectionForCheck(ActionProcessData& act, int32_t) { act.aiselect = 0; }

// nbRunAiSub @ 0x00287B40: the drawn action's targets.
int32_t targetedAction(const ActionProcessData&, int32_t action) { return action; }

} // namespace nocturne::nb::ai
