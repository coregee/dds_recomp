// The functions the Hardtype rebalance adds (in US Maniax's empty space at
// 0x2FDC20..0x2FF388), used by its patches of the base functions. Built in
// every version; only the Hardtype build calls them.
#include "nocturne/hardtype.hpp"

#include "nocturne/battle/process.hpp"
#include "nocturne/external.hpp"

#include "nocturne/data/records.hpp"
#include "nocturne/data/tables.hpp"

namespace nocturne::hardtype {

// 0x002FE240 (Hardtype's): one of the first eight skills. The units Hardtype
// finds at 0x116xxxx (the battle's enemies, where the game allocates them)
// are checked by their devil's own list instead.
bool hasSkill(const UnitWork& unit, uint32_t skill)
{
    const uint16_t* skills = (guest::addressOf(&unit) >> 16) == 0x116 ? dat::devilFormat(unit.id).skill : unit.skill;
    for (int32_t i = 0; i < 8; ++i)
        if (skills[i] == skill)
            return true;
    return false;
}

namespace {

// The press turn gauge's two counts (nbPanelPressGauge's words at 0x551FE0
// and 0x551FE4; tentatively whole and flashing icons), as signed bytes.
int32_t pressGaugeValue()
{
    return *guest::table<const int8_t>(0x00551fe0) + (*guest::table<const int8_t>(0x00551fe4) << 4);
}

} // namespace

uint32_t pressGaugeRegister() { return static_cast<uint32_t>(*guest::table<const int8_t>(0x00551fe4) << 4); }

// 0x002FEA30, 0x002FEA10, 0x002FE9F0 (Hardtype's)
uint32_t& affinityRegister()
{
    static uint32_t t7 = 0;
    return t7;
}

uint32_t unitLookupRegister(int32_t formindex)
{
    if (formindex >= 16)
        return static_cast<uint32_t>(formindex - 16);
    nb::MainProcessData& main = *nb::GetMainProcessData();
    const nb::Party* party = nb::GetPartyFromFormindex(formindex);
    if (party && (party->flag & 1))
        return guest::addressOf(&main);
    return guest::table<nb::Formation>(main.form.address)[formindex].stat & 1;
}

uint16_t standInFor(uint16_t skill)
{
    for (const uint16_t* pair = guest::table<const uint16_t>(kStandIns); pair[0] != 0; pair += 2)
        if (pair[0] == skill)
            return pair[1];
    return skill;
}

bool aiCondition(int32_t type, int32_t n)
{
    switch (type) {
    case 29: return static_cast<int8_t>(byteAt(kMoonPhase)) == n;
    case 60: return !(pressGaugeValue() < n);
    case 61: return pressGaugeValue() < n + 1;
    default: return false;
    }
}

} // namespace nocturne::hardtype
