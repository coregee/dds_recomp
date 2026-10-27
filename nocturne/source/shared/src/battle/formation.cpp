// The battle's formations (original unit: nbFormation). Rewritten from the
// original instructions; names by the HD remaster's order (tentative where
// marked).
#include "nocturne/battle/formation.hpp"

#include <cstring>
#include <iterator>

#include "nocturne/address.hpp"
#include "nocturne/build.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/records.hpp"
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

// 0x0028B0B8 (no original name): slot `index` cleared; its radii 100 and
// scale 1, its index, its side (players 0..3, enemies 4..13, beyond: 0x400)
// and its place and turn the defaults (0x526420, 0x526430), as found and
// as now.
void initFormation(MainProcessData& main, int32_t index)
{
    Formation& form = guest::table<Formation>(main.form.address)[index];
    std::memset(&form, 0, sizeof form);
    form.cr = ee::Float::fromBits(0x42c80000);   // 100
    form.scl = ee::Float::fromBits(0x3f800000);  // 1
    form.r = ee::Float::fromBits(0x42c80000);
    form.formindex = static_cast<int16_t>(index);
    form.stat |= index < 4 ? FormationStat::PartySlot : index < 14 ? FormationStat::EnemySlot : FormationStat::ExtraSlot;
    const Vec4& place = *guest::table<const Vec4>(addr(0x00526420));
    const Vec4& turn = *guest::table<const Vec4>(addr(0x00526430));
    form.pos = place;
    form.orgpos = place;
    form.rot = turn;
    form.orgrot = turn;
}

// nbCopyFormation @ 0x0028B198: the unit in slot `from` copied to slot `to`.
// Its ailment effect is let go and made again on the new slot, and its party
// entry follows it.
void copyFormation(MainProcessData& main, int32_t from, int32_t to)
{
    if (from == to)
        return;
    Formation& source = main.form[from];
    Formation& destination = main.form[to];
    int32_t effect = -1;
    if (source.ailmentEffect != 0) {
        effect = *guest::table<const int32_t>(source.ailmentEffect);   // effBTLSystemGetID: the part's effect
        eff::BTLPartDelete(source.ailmentEffect);
        source.ailmentEffect = 0;
    }
    if (source.stat & FormationStat::CheckParty)
        main.party[source.partyindex].formindex = static_cast<int16_t>(to);
    std::memcpy(&destination, &source, sizeof destination);
    destination.formindex = static_cast<int16_t>(to);
    if (effect >= 0)
        destination.ailmentEffect = eff::BTLPartCreate(&destination, effect);
}

// nbMoveFormation @ 0x0028B330: ... and slot `from` cleared.
void moveFormation(MainProcessData& main, int32_t from, int32_t to)
{
    if (from == to)
        return;
    copyFormation(main, from, to);
    initFormation(main, from);
}

// nbUpdateFormation @ 0x0028B388: the party's units moved forward into empty
// slots, so slots 0..3 have no gaps.
void closePartyGaps(MainProcessData& main)
{
    for (int32_t i = 0; i < 3; ++i) {
        if (main.form[i].stat & FormationStat::Present)
            continue;
        for (int32_t j = i + 1; j < 4; ++j) {
            if (main.form[j].stat & FormationStat::Present) {
                moveFormation(main, j, i);
                break;
            }
        }
    }
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
        dds3::SetPosPoseSet(form.basic, pos);
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
ee::Float enemyInterval() { return *guest::table<ee::Float>(addr(0x005514fc)); }

// effBTLModelGetID @ 0x0016E560: the devil a present slot's unit shows (0 for
// the Demi-fiend), 0x200 for an empty slot or none.
int32_t formationModelId(const Formation* form)
{
    if (form == nullptr || !(form->stat & FormationStat::Present))
        return 0x200;
    // (a slot without a unit reads one at guest address 0, as the original does)
    const uint32_t address = guest::addressOf(GetUnitWorkFromFormindex(form->formindex));
    const UnitWork& unit = *guest::table<const UnitWork>(address);
    return (unit.flag & UnitFlag::PlayerCharacter) ? 0 : unit.id;
}

namespace {

ee::Float bits(uint32_t value) { return ee::Float::fromBits(value); }

// A slot's unit placed at `pos`, which becomes its place to return to.
void placeAt(Formation& form, const Vec4& pos)
{
    setFormationPosition(form, pos);
    form.orgpos = pos;
}

// Every enemy present moved back by `distance`.
void moveEnemiesBack(MainProcessData& main, ee::Float distance)
{
    for (int32_t i = 0; i < 10; ++i) {
        Formation& form = main.form[4 + i];
        if (!(form.stat & FormationStat::Present))
            continue;
        Vec4 pos = form.pos;   // (nbLoadUnitPos)
        pos.z = pos.z + distance;
        placeAt(form, pos);
    }
}

// The box the camera and targeting see a boss by (centre, radius, height).
void setTargetBox(Formation& form, ee::Float x, ee::Float y, ee::Float z, ee::Float r, ee::Float h)
{
    form.r = r;
    form.center.z = z;
    form.h = h;
    form.center.x = x;
    form.center.y = y;
}

// The same, every part divided by the model's scale (in this order).
void setScaledTargetBox(Formation& form, uint32_t x, uint32_t y, uint32_t z, uint32_t r, uint32_t h)
{
    const ee::Float scale = form.scl;
    form.r = bits(r) / scale;
    form.h = bits(h) / scale;
    form.center.z = bits(z) / scale;
    form.center.x = bits(x) / scale;
    form.center.y = bits(y) / scale;
}

constexpr uint32_t kFormationNames[] = {   // the debug prints' formats, by formation type
    addr(0x005458e8), addr(0x00545918), addr(0x00545948), addr(0x00545978), addr(0x005459a0), addr(0x005459d0), addr(0x00545a00),
    addr(0x00545a30), addr(0x00545a58), addr(0x00545a80), addr(0x00545aa8), addr(0x00545a80), optionalAddr(0x00545ad0), optionalAddr(0x00545af8)};

} // namespace

// nbSetEnemyFormation @ 0x0028A758: after the party's formation (group
// 0x200), the encounter's formation type moves its enemies: back for the
// Arsiel and Mara types, the Fates around the middle one, Albion's
// Emanations by devil, and fixed places (with the box the camera targets
// them by) for Baal, Noah, Ahriman, Metatron, Kagutsuchi and Lucifer. Where the original reads its own local before
// setting it (Net's w, Kagutsuchi's z and every coordinate for another
// model), it reads what an earlier call left on the stack; the rewrite
// reads 0, as in the test interpreter.
void setEnemyFormation(MainProcessData& main)
{
    // (The first release has the first eleven types: no Ahriman2, Beelzebub or Lucifer.)
    const uint32_t types = kBuild.vanilla ? 11 : static_cast<uint32_t>(std::size(kFormationNames));
    const uint32_t type = static_cast<uint32_t>(main.formationtype);
    if (type >= types)
        return;
    diag::print(static_cast<diag::Message>(kFormationNames[type]));
    SetPartyFormation(main, 0x200);
    Formation& first = main.form[4];
    switch (static_cast<EncounterFormation>(type)) {
    case EncounterFormation::Arsiel:
        moveEnemiesBack(main, bits(0x43960000));   // 300
        break;
    case EncounterFormation::Mara:
        SetPartyFormation(main, 0x200);
        moveEnemiesBack(main, bits(0x43d20000));   // 420
        break;
    case EncounterFormation::Fates: {
        // The middle sister (slot 5) stands; the others either side of her,
        // or the third beside the first when she is gone.
        Formation& middle = main.form[5];
        Formation& left = main.form[4];
        Formation& right = main.form[6];
        if (middle.stat & FormationStat::Present) {
            const Vec4 centre = middle.pos;
            if (left.stat & FormationStat::Present) {
                Vec4 pos = left.pos;
                pos.x = centre.x - bits(0x43670000);   // 231
                pos.z = centre.z;
                placeAt(left, pos);
            }
            if (right.stat & FormationStat::Present) {
                Vec4 pos = right.pos;
                pos.x = centre.x + bits(0x43864000);   // 268.5
                pos.z = centre.z;
                placeAt(right, pos);
            }
        } else {
            const Vec4 from = left.pos;
            if (!(left.stat & FormationStat::Present))
                break;
            if (right.stat & FormationStat::Present) {
                Vec4 pos = right.pos;
                pos.x = from.x + bits(0x43ac8000);   // 345
                pos.z = from.z;
                placeAt(right, pos);
            }
        }
        break;
    }
    case EncounterFormation::Albion:
        // Albion behind, its four Emanations around it.
        for (int32_t i = 0; i < 10; ++i) {
            Formation& form = main.form[4 + i];
            if (!(form.stat & FormationStat::Present))
                continue;
            const uint32_t unit = guest::addressOf(GetUnitWorkFromFormindex(form.formindex));
            Vec4 pos = form.pos;
            switch (guest::table<const UnitWork>(unit)->id) {
            case devil::AlbionBoss: pos.z = pos.z + bits(0x44610000); break;   // +900
            case devil::LuvahBoss: pos.z = pos.z + bits(0x44160000); pos.x = pos.x - bits(0x42c80000); break;   // +600, -100
            case devil::UrizenBoss: pos.z = pos.z + bits(0x44160000); pos.x = pos.x - bits(0x43480000); break;   // +600, -200
            case devil::TharmasBoss: pos.z = pos.z + bits(0x44160000); pos.x = pos.x + bits(0x43480000); break;   // +600, +200
            case devil::UrthonaBoss: pos.z = pos.z + bits(0x44160000); pos.x = pos.x + bits(0x42c80000); break;   // +600, +100
            default: break;
            }
            placeAt(form, pos);
        }
        break;
    case EncounterFormation::Baal:
        if (first.stat & FormationStat::Present) {
            Vec4 pos = first.pos;
            pos.x = pos.x - bits(0x42f00000);   // 120
            placeAt(first, pos);
        }
        break;
    case EncounterFormation::Noah: {
        if (!(first.stat & FormationStat::Present))
            break;
        const ee::Float x = bits(0x43cd0000);   // 410
        placeAt(first, Vec4{x, bits(0), bits(0x44160000), bits(0)});   // (410, 0, 600)
        const int32_t model = formationModelId(&first);
        if (model == devil::Noah2ndFormBoss)
            setTargetBox(first, x, bits(0xc3e10000), bits(0xc3160000), bits(0x43c80000), bits(0x44430000));   // (410, -450, -150), 400, 780
        else if (model == devil::Noah1stFormBoss)
            setTargetBox(first, x, bits(0xc3e10000), bits(0xc35c0000), bits(0x43c80000), bits(0x44430000));   // (410, -450, -220), 400, 780
        break;
    }
    case EncounterFormation::Ahriman:
    case EncounterFormation::Ahriman2: {
        if (!(first.stat & FormationStat::Present))
            break;
        placeAt(first, Vec4{bits(0), bits(0), bits(0x44160000), bits(0)});   // (0, 0, 600)
        const int32_t model = formationModelId(&first);
        if (model == devil::Ahriman1stFormBoss) {
            setTargetBox(first, bits(0), bits(0xc4228000), bits(0xc3660000), bits(0x43af0000), bits(0x443b8000));   // (0, -650, -230), 350, 750
        } else if (model == devil::Ahriman2ndFormBoss) {
            setTargetBox(first, bits(0), bits(0xc3c30000), bits(0xc3160000), bits(0x43af0000), bits(0x44228000));   // (0, -390, -150), 350, 650
        } else if (!kBuild.vanilla && model == devil::MetatronBoss) {   // (not in the first release)
            placeAt(first, Vec4{bits(0), bits(0), bits(0x447a0000), bits(0)});   // (0, 0, 1000)
            const ee::Float scale = first.scl;   // (its centre's x stays 0, unscaled)
            setTargetBox(first, bits(0), bits(0xc3bb8000) / scale, bits(0x437a0000) / scale, bits(0x43480000) / scale,
                         bits(0x442f0000) / scale);   // (0, -375, 250), 200, 700, by the scale
        }
        break;
    }
    case EncounterFormation::Kagutsuchi: {
        if (!(first.stat & FormationStat::Present))
            break;
        const int32_t model = formationModelId(&first);
        Vec4 pos{bits(0), bits(0), bits(0), bits(0)};
        if (model == devil::Kagutsuchi2ndFormBoss) {
            pos.z = pos.z + bits(0x44b54000);   // 1450
            setTargetBox(first, bits(0), bits(0xc4480000), bits(0x43160000), bits(0x43fa0000), bits(0x447a0000));   // (0, -800, 150), 500, 1000
        } else if (model == devil::Kagutsuchi1stFormBoss) {
            pos.y = bits(0xc424ffff);   // about -660
            pos.z = pos.z + bits(0x44700000);   // 960
            setTargetBox(first, bits(0), bits(0x43960000), bits(0x42c80000), bits(0x44160000), bits(0x44610000));   // (0, 300, 100), 600, 900
        }
        placeAt(first, pos);
        break;
    }
    case EncounterFormation::Lucifer: {
        Vec4 pos = first.pos;
        pos.z = pos.z + bits(0x442f0000);   // 700
        pos.y = pos.y - bits(0x43480000);   // 200
        placeAt(first, pos);
        setScaledTargetBox(first, 0, 0xc4480000, 0x43960000, 0x43480000, 0x44bb8000);   // (0, -800, 300), 200, 1500
        break;
    }
    default:   // Normal, Girimehkala, the angels, Beelzebub: the party's formation only
        break;
    }
}

} // namespace nocturne::nb
