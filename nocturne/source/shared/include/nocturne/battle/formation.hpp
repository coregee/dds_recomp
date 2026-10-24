// The battle's formations (original unit: nbFormation), as far as
// rewritten: the models shown and hidden, and put in their places.
#pragma once

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

void hideFormationModel(int32_t formindex);   // nbFormDispOff: hidden, if its model is shown
void showFormationModel(int32_t formindex);   // nbFormDispOn
void hideFormation(const Formation& form);    // nbFormDispOff2: ... by the formation
void showFormation(const Formation& form);    // nbFormDispOn2
void hideSide(int32_t side);                  // nbGroupFormDispOff: 0 the party, 1 the enemies, 2 the extra slots
void showSide(int32_t side);                  // nbGroupFormDispOn
void hideAllFormations();                     // (no original name)
void showAllFormations();                     // nbAllFormDispOn
void showOnly(const Formation& form);         // nbSingleFormExceptedDispOff
void showOnly(const Formation& form, const Formation& other);   // (no original name)

void setFormationPosition(Formation& form, const Vec4& pos);    // nbSetFormPos
void setFormationPlace(Formation& form, const Vec4& pos, const Vec4& rot);   // nbSetFormPosRot
void resetFormationPlace(Formation& form);    // nbResetFormPosRot: back to its place, if present
void resetAllFormationPlaces();               // nbResetAllFormPosRot

ee::Float partyDistance();                    // nbGetPartyDistance: 800
ee::Float summonInterval();                   // nbGetSummonInterval: 50
ee::Float defaultRadius();                    // nbFormationGetRadiusDef: 100
ee::Float enemyInterval();                    // nbGetEnemyInterval

} // namespace nocturne::nb
