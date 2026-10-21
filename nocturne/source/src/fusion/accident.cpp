// Fusion accidents (original unit: cmb).
#include "nocturne/fusion/accident.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/stock.hpp"

namespace nocturne::cmb {

namespace {

bool inStock(uint16_t devil)
{
    return findStockDevil(devil, dat::globalWork().units, 16) >= 0;
}

} // namespace

// cmbChkEventDevil @ 0x001FD3B0
bool isEventLocked(uint16_t devil)
{
    for (const EventDevil& row : dat::kEventDevilTbl)
        if (row.devil == devil && !evt::BitCheck(static_cast<int32_t>(row.eventflag)))
            return true;
    return false;
}

// cmbChkMetaOnlyDevil @ 0x001FE2C8
bool isSpecialFusionOnly(uint16_t devil)
{
    return (dat::devilFormat(devil).flag & 0x2) != 0;
}

// cmbChkAccident @ 0x001FE2F0
bool rollAccident()
{
    uint32_t moon = evt::GetAgeOfMoon();
    uint32_t roll = sdf::GetRand();
    return (roll & (moon == 0 || moon == 8 ? 0x0f : 0xff)) == 0;
}

// cmbChkAccidentType @ 0x001FE368: only one kind of accident remains.
int8_t rollAccidentType()
{
    sdf::GetRand();
    return 0;
}

// cmbGetAccidentFailDevil @ 0x001FE388: the last devil of the fallback list
// that is neither in the stock nor `excluded`; failing that, the first.
uint16_t accidentFallbackDevil(uint16_t excluded)
{
    uint16_t devil = 0;
    for (int i = 13; i >= 0; --i) {
        devil = dat::kAccidentFailTbl[i];
        if (!inStock(devil) && devil != excluded)
            return devil;
    }
    return devil;
}

// cmbRndGetAccidentBirthDevil @ 0x001FE410: up to 16 random picks from
// devils 1..168 at most 3 levels above and 15 below the Demi-fiend.
uint16_t randomAccidentDevil(uint16_t excluded)
{
    const UnitWork& player = dat::globalWork().units[0];
    for (int attempt = 0; attempt < 16; ++attempt) {
        uint16_t devil = static_cast<uint16_t>(sdf::GetRand() % 168 + 1);
        UnitWork candidate;
        copyDefaultDevil(devil, candidate);
        if (dat::devilFormat(devil).race == Race::Corpus)
            continue;
        if (isEventLocked(devil))
            continue;
        int32_t level = player.level;
        if (level + 3 < candidate.level || candidate.level < level - 15)
            continue;
        if (inStock(devil) || isSpecialFusionOnly(devil))
            continue;
        if (devil != excluded)
            return devil;
    }
    return accidentFallbackDevil(excluded);
}

// cmbAddParamAccidentBirthDevil @ 0x001FE570
void boostAccidentDevil(UnitWork& unit)
{
    for (int8_t& param : unit.param)
        param = static_cast<int8_t>(param + param / 5);
    unit.hp = unit.maxhp = static_cast<uint16_t>(dat::maxHp(unit));
    unit.mp = unit.maxmp = static_cast<uint16_t>(dat::maxMp(unit));
}

} // namespace nocturne::cmb
