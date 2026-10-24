// The command menu (original unit: nbCommSel): Hardtype's own (shared/src/battle/comm_select.cpp has the rest).
#include "nocturne/battle/comm_select.hpp"

#include <algorithm>

#include "nocturne/battle/combatant.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kStatDebugAllSkills = 0x4000000;   // (as in shared/src/battle/comm_select.cpp)
constexpr uint32_t kRandomState = 0x00529bd8;         // the RNG's state words (0x2C0BA8)

// GetUnitWorkFromFormindex @ 0x00246AB8 leaves in the register: for a
// battle slot, the battle's record (nbGetPartyFromFormindex's), then for an
// active party entry its flag's bit 2 (GetUnitWork's).
uint32_t afterUnitLookup(int32_t formindex, uint32_t leftover)
{
    if (formindex >= 16)
        return leftover;
    leftover = guest::addressOf(GetMainProcessData());
    const Party* party = GetPartyFromFormindex(formindex);
    if (party && (party->flag & 1))
        leftover = static_cast<uint32_t>(party->flag & 2);
    return leftover;
}

// Whether nbCheckSkillCost goes on to datGetSkillCost (which leaves the unit).
bool readsSkillCost(const UnitWork& unit, int32_t skill)
{
    const NormalSkill& s = dat::normalSkill(checkedSkill(skill));
    if (s.damageClass == 1 && unit.ailment() == ailment::Mute)
        return false;
    if (s.flag & 4)
        return false;
    return s.costtype == 1 || s.costtype == 2;
}

// What SetCommList's skill list leaves in the register Hardtype reads: the
// last of the calls that set it, replayed in the list's order.
uint32_t leftoverAfterSkills(CommandMenu& d, Party& my)
{
    MainProcessData& main = *d.data;
    uint32_t leftover = static_cast<uint32_t>(my.flag & 2);   // GetUnitWork
    const UnitWork& unit = *GetUnitWorkPointer(main, my);
    const auto& units = dat::globalWork().units;
    const int32_t skills = (main.stat & kStatDebugAllSkills) ? 0x200 : unit.skillcnt;
    for (int32_t i = 0; i < skills; ++i) {
        const int32_t skill = (main.stat & kStatDebugAllSkills) ? i : unit.skill[i];
        if (skill == 0 || dat::skillInfo(skill).type != 0 || !(dat::normalSkill(skill).use & 2))
            continue;
        leftover = afterUnitLookup(my.formindex, leftover);   // nbCheckSkillCost
        const UnitWork* user = GetUnitWorkFromFormindex(my.formindex);
        if (user && readsSkillCost(*user, skill))
            leftover = guest::addressOf(user);
        if (skill == 0xdf && main.playerpcnt < 4) {
            // nbGetRandomStockUnit: its loop counter, then the RNG's old state word
            leftover = 16;
            if (std::any_of(std::begin(units), std::end(units), summonableStock))
                leftover = *guest::table<uint32_t>(kRandomState + 4);
        }
    }
    return leftover;
}

} // namespace

// SetCommList @ 0x0025CB80 (and 0x2FE320): every unit gets the demons to
// summon. The items are meant for the Demi-fiend only (devil ID 0), but the
// ID is read through a register left over from the skill list: it holds
// the unit only if a skill's cost was looked up last, else a small number
// or an address, so the halfword 4 past it decides.
bool listsItems(CommandMenu& d, Party& my, bool)
{
    return *guest::table<uint16_t>(leftoverAfterSkills(d, my) + 4) == 0;
}
bool listsSummons(bool) { return true; }

} // namespace nocturne::nb
