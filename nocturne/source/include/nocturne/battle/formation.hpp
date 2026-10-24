// The battle's formations (original unit: nbFormation), as far as
// rewritten: a formation's model shown, and put back in its place.
#pragma once

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

void hideFormation(const Formation& form);    // nbFormDispOff2: nbFormDispOff by the formation
void showFormation(const Formation& form);    // nbFormDispOn2: nbFormDispOn by the formation
void resetFormationPlace(Formation& form);    // nbResetFormPosRot: back to its place, if present

} // namespace nocturne::nb
