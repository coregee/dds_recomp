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
void initFormation(MainProcessData& main, int32_t index);   // (0x28B0B8) slot `index` cleared and set up
void copyFormation(MainProcessData& main, int32_t from, int32_t to);   // nbCopyFormation: a unit into another slot
void moveFormation(MainProcessData& main, int32_t from, int32_t to);   // nbMoveFormation: ... and its old slot cleared
void closePartyGaps(MainProcessData& main);   // nbUpdateFormation: the party's units moved forward into empty slots
void showOnly(const Formation& form, const Formation& other);   // (no original name)

void setFormationPosition(Formation& form, const Vec4& pos);    // nbSetFormPos
void setFormationPlace(Formation& form, const Vec4& pos, const Vec4& rot);   // nbSetFormPosRot
void resetFormationPlace(Formation& form);    // nbResetFormPosRot: back to its place, if present
void resetAllFormationPlaces();               // nbResetAllFormPosRot

ee::Float partyDistance();                    // nbGetPartyDistance: 800
ee::Float summonInterval();                   // nbGetSummonInterval: 50
ee::Float defaultRadius();                    // nbFormationGetRadiusDef: 100
ee::Float enemyInterval();                    // nbGetEnemyInterval

// The encounter's formation type (Encount::formationtype), named after the
// debug prints (ENC_FORMATION_*): the bosses whose enemies stand apart.
enum class EncounterFormation : uint32_t {
    Normal, Arsiel, Girimehkala, Mara, Fates, Albion, Angels, Baal, Noah, Ahriman, Kagutsuchi, Ahriman2, Beelzebub, Lucifer,
};
void setEnemyFormation(MainProcessData& main);       // nbSetEnemyFormation (0x28A758)
int32_t formationModelId(const Formation* form);     // effBTLModelGetID (0x16E560): the devil a slot shows

} // namespace nocturne::nb
