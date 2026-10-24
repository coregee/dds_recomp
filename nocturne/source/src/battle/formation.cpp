// The battle's formations (original unit: nbFormation). Rewritten from the
// original instructions; names by the HD remaster's order (tentative).
#include "nocturne/battle/formation.hpp"

#include "nocturne/external.hpp"

namespace nocturne::nb {

// nbFormDispOff2 @ 0x00289BB8 (tentative name)
void hideFormation(const Formation& form) { FormDispOff(form.formindex); }

// nbFormDispOn2 @ 0x00289C60 (tentative name)
void showFormation(const Formation& form) { FormDispOn(form.formindex); }

// nbResetFormPosRot @ 0x0028A238 (tentative name): a present formation
// (stat bit 1) back at its original position and rotation.
void resetFormationPlace(Formation& form)
{
    if (form.stat & 1) {
        SetFormPos(form, form.orgpos);
        SetFormRot(form, form.orgrot);
    }
}

} // namespace nocturne::nb
