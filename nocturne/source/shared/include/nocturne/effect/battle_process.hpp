// The battle's effect process (original unit: effBattle), as far as
// rewritten: its start.
#pragma once

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbInitEffectProcess (0x16C528): the effects' process ("nb_effect") under
// the battle's and their drawing ("nb_effect_draw") under it; the skills'
// effects, the field's colour, the point lights, the shown models and the
// effect parts set up.
void startEffectProcess(MainProcessData& main);

} // namespace nocturne::nb
