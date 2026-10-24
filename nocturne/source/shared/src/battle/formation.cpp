// The battle's formations (original unit: nbFormation). Rewritten from the
// original instructions; names by the HD remaster's order (tentative where
// marked).
#include "nocturne/battle/formation.hpp"

#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kObjectHidden = 0x1000;   // dds3ObjectBase flag

Formation& formAt(int32_t index) { return guest::table<Formation>(GetMainProcessData()->form.address)[index]; }

// A shown model (stat bits 1 and 2) with its object: its unit's draw flag
// (through the handle) and the object's hidden flag.
bool hasModel(const Formation& form) { return (form.stat & 1) && (form.stat & 2) && form.basic != 0; }

uint32_t& drawFlags(const Formation& form) { return *guest::table<uint32_t>(*guest::table<uint32_t>(form.hunit + 0x8c)); }

} // namespace

// nbFormDispOff @ 0x00289B30
void hideFormationModel(int32_t formindex)
{
    const Formation& form = formAt(formindex);
    if (hasModel(form)) {
        drawFlags(form) |= 1;
        dds3::ObjectBaseOnFlag(form.basic, kObjectHidden);
    }
}

// nbFormDispOff2 @ 0x00289BB8 (tentative name)
void hideFormation(const Formation& form) { hideFormationModel(form.formindex); }

// nbFormDispOn @ 0x00289BD0
void showFormationModel(int32_t formindex)
{
    const Formation& form = formAt(formindex);
    if (hasModel(form)) {
        drawFlags(form) &= ~1u;
        dds3::ObjectBaseOffFlag(form.basic, kObjectHidden);
    }
}

// nbFormDispOn2 @ 0x00289C60 (tentative name)
void showFormation(const Formation& form) { showFormationModel(form.formindex); }

namespace {

// A side's formations: the party 0..3, the enemies 4..13, 14 and 15 the
// two extra slots.
void sideRange(int32_t side, int32_t& first, int32_t& end)
{
    first = end = 0;
    if (side == 0)
        end = 4;
    else if (side == 1)
        first = 4, end = 14;
    else if (side == 2)
        first = 14, end = 16;
}

} // namespace

// nbGroupFormDispOff @ 0x00289C78
void hideSide(int32_t side)
{
    int32_t i, end;
    sideRange(side, i, end);
    for (; i < end; ++i)
        hideFormationModel(i);
}

// nbGroupFormDispOn @ 0x00289D30
void showSide(int32_t side)
{
    int32_t i, end;
    sideRange(side, i, end);
    for (; i < end; ++i)
        showFormationModel(i);
}

// 0x00289DE8 (no original name)
void hideAllFormations()
{
    for (int32_t i = 0; i < 16; ++i)
        hideFormationModel(i);
}

// nbAllFormDispOn @ 0x00289E28
void showAllFormations()
{
    for (int32_t i = 0; i < 16; ++i)
        showFormationModel(i);
}

// nbSingleFormExceptedDispOff @ 0x00289E68: only `form` shown.
void showOnly(const Formation& form)
{
    for (int32_t i = 0; i < 16; ++i) {
        if (i == form.formindex)
            showFormationModel(i);
        else
            hideFormationModel(i);
    }
}

// 0x00289ED0 (no original name): only the two shown.
void showOnly(const Formation& form, const Formation& other)
{
    for (int32_t i = 0; i < 16; ++i) {
        if (i == form.formindex || i == other.formindex)
            showFormationModel(i);
        else
            hideFormationModel(i);
    }
}

// nbSetFormPos @ 0x0028A0E8: the model moved too, if shown.
void setFormationPosition(Formation& form, const Vec4& pos)
{
    form.pos = pos;
    if ((form.stat & 1) && (form.stat & 2) && form.basic != 0) {
        dds3::SetPosPoseSet(form.basic, guest::addressOf(&pos));
        form.pos = pos;
    }
}

// nbSetFormPosRot @ 0x0028A200
void setFormationPlace(Formation& form, const Vec4& pos, const Vec4& rot)
{
    setFormationPosition(form, pos);
    SetFormRot(form, rot);
}

// nbResetFormPosRot @ 0x0028A238 (tentative name): a present formation
// (stat bit 1) back at its original position and rotation.
void resetFormationPlace(Formation& form)
{
    if (form.stat & 1) {
        setFormationPosition(form, form.orgpos);
        SetFormRot(form, form.orgrot);
    }
}

// nbResetAllFormPosRot @ 0x0028A288: all sixteen slots.
void resetAllFormationPlaces()
{
    for (int32_t i = 0; i < 16; ++i)
        resetFormationPlace(formAt(i));
}

// nbGetPartyDistance @ 0x0028A300
ee::Float partyDistance() { return ee::Float::fromBits(0x44480000); }   // 800.0
// nbGetSummonInterval @ 0x0028A310
ee::Float summonInterval() { return ee::Float::fromBits(0x42480000); }  // 50.0
// nbFormationGetRadiusDef @ 0x0028A320
ee::Float defaultRadius() { return ee::Float::fromBits(0x42c80000); }   // 100.0
// nbGetEnemyInterval @ 0x0028A338: a setting (gp global 0x5514FC).
ee::Float enemyInterval() { return *guest::table<ee::Float>(0x005514fc); }

} // namespace nocturne::nb
