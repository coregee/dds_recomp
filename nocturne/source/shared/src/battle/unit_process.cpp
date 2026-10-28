// The units' process (original unit: nbUnitProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/unit_process.hpp"

#include "nocturne/address.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/result/level_up.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x00551118);   // "nb_unit"
constexpr uint32_t kDrawName = addr(0x00543768);      // "nb_unitdraw"
constexpr uint32_t kStep = addr(0x0024f0b0), kShutdown = addr(0x0024f368);   // nbUnitProcess2, nbUnitShutdown (no C here yet)
constexpr uint32_t kDraw = addr(0x0024e670);          // nbUnitDrawProcess1 (no C here yet)

// The first party entry from `first` to before `last` not in use, or -1.
int32_t freeEntry(MainProcessData& main, int32_t first, int32_t last)
{
    for (int32_t i = first; i < last; ++i)
        if (!(main.party[i].flag & PartyFlag::Active))
            return i;
    return -1;
}

} // namespace

// nbInitUnitProcess @ 0x0024F388
void startUnitProcess(MainProcessData& main)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kStep, kShutdown, 0);
    dds3::LinkProcess(main.MainProcessID, process);
    main.UnitProcessID = process;
    dds3::LinkProcess(process, dds3::StartProcess(kDrawName, 0x2b0e, 1, 1, kDraw, 0, 0));
}

// nbAddUnitStock @ 0x0024D550
int32_t addUnitToSlot(MainProcessData& main, int32_t side, int32_t stockno, int32_t formindex)
{
    const bool playerSide = side == 0;
    const int32_t entry = playerSide ? freeEntry(main, 0, 4) : freeEntry(main, 4, 14);
    UnitWork* unit = playerSide ? &dat::globalWork().units[stockno] : &main.enemyunit[stockno];
    // (Its record as the unit stood before it was marked an enemy below.)
    const UnitVisual& visual = unitVisual(*unit);
    int16_t flag;
    if (playerSide) {
        flag = PartyFlag::Active;
        ++main.playerpcnt;
        unit->flag |= UnitFlag::InParty;
    } else {
        flag = PartyFlag::Active | PartyFlag::EnemySide;
        ++main.enemypcnt;
        unit->flag |= UnitFlag::InParty | UnitFlag::Enemy;
    }
    Party& party = main.party[entry];
    party.flag = flag;
    party.statindex = static_cast<int16_t>(stockno);
    party.formindex = static_cast<int16_t>(formindex);
    for (int16_t& counter : party.count)
        counter = 0;
    const int32_t heartsRow = (unit->flag & UnitFlag::PlayerCharacter) ? rst::equippedHeartsAffinity() : 0;
    for (int32_t k = 0; k < 16; ++k)
        party.affinities[k] = heartsRow != 0 ? dat::affinityRow(heartsRow)[k] : dat::affinity(*unit, static_cast<Attribute>(k));

    Formation& form = main.form[formindex];
    form.stat = FormationStat::Present | FormationStat::CheckParty |
                (formindex < 4 ? FormationStat::PartySlot : formindex < 14 ? FormationStat::EnemySlot : FormationStat::ExtraSlot);
    if (visual.setupFlag == 1)
        form.stat |= 0x80;
    form.partyindex = static_cast<int16_t>(entry);
    form.formindex = static_cast<int16_t>(formindex);
    form.r = visual.size;
    form.cr = ee::Float::fromBits(0);
    form.center = Vec4{visual.center[0], visual.center[1], visual.center[2], visual.center[3]};
    form.scl = visual.scale;
    form.h = visual.height;
    form.oneshotr = visual.oneShotRadius;
    form.ailmentEffect = 0;
    form.allshotr = visual.allShotRadius;
    return prepareMotion(form, 0);
}

} // namespace nocturne::nb
