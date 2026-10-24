// Fusion rules (original unit: fclCombineCalcCore).
#include "nocturne/fusion/rules.hpp"

#include <vector>

#include "nocturne/data/ids.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/accident.hpp"
#include "nocturne/fusion/sort.hpp"
#include "nocturne/fusion/stock.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::cmb {

namespace {

uint8_t raceOf(uint16_t devil) { return static_cast<uint8_t>(dat::devilFormat(devil).race); }

// Fusion never produces these through the general rules.
bool isFusible(uint16_t devil)
{
    return !isSpecialPairResult(devil) && !isSacrificePatternResult(devil) && !isEventLocked(devil)
        && !isSpecialFusionOnly(devil);
}

// All devils, by race and then level, highest first.
std::vector<DevilSortEntry> devilsByRace()
{
    std::vector<DevilSortEntry> list(dat::devilCount());
    sortDevilsByRace(list.data(), static_cast<uint16_t>(list.size()));
    return list;
}

} // namespace

// ===========================================================================
// Table lookups
// ===========================================================================

// cmbChkExtPattern @ 0x001FE1A0 (either order)
uint16_t specialPairResult(uint16_t devil1, uint16_t devil2)
{
    for (int pass = 0; pass < 2; ++pass) {
        for (const FusionPair& pair : dat::kExtPatternTbl)
            if (pair.devil1 == devil1 && pair.devil2 == devil2 && !isEventLocked(pair.birth))
                return pair.birth;
        uint16_t swap = devil1;
        devil1 = devil2;
        devil2 = swap;
    }
    return 0;
}

// cmbChkExtPatternBirthDevil @ 0x001FE280
bool isSpecialPairResult(uint16_t devil)
{
    for (const FusionPair& pair : dat::kExtPatternTbl)
        if (pair.birth == devil)
            return true;
    return false;
}

// cmbChkIkenieExtPatternBirthDevil @ 0x001FDA08
bool isSacrificePatternResult(uint16_t devil)
{
    for (const SacrificeDevilPattern& p : dat::kIkenieExtPatternDevTbl)
        if (p.birth == devil) return true;
    for (const SacrificeResultPattern& p : dat::kIkenieExtPatternDev2Tbl)
        if (p.birth == devil) return true;
    for (const SacrificeDevilRacePattern& p : dat::kIkenieExtPatternDevRaceTbl)
        if (p.birth == devil) return true;
    return false;
}

// cmbGetBirthSpirit @ 0x001FDD18 (either order)
uint16_t mitamaFromElements(uint16_t element1, uint16_t element2)
{
    for (const FusionPair& pair : dat::kBirthSpiritTbl) {
        if ((pair.devil1 == element1 && pair.devil2 == element2) || (pair.devil2 == element1 && pair.devil1 == element2))
            return pair.birth;
    }
    return 0;
}

// cmbGetRankUpDown @ 0x001FDCA0
int8_t elementRankShift(uint16_t element, Race race)
{
    for (const SpiritRankTable& table : dat::kRankUpDownTbl) {
        if (table.devil != element)
            continue;
        for (const RankShift& shift : table.base)
            if (shift.race == static_cast<uint8_t>(race))
                return static_cast<int8_t>(shift.flag);
    }
    return -1;
}

// cmbGetBirthDevilRace @ 0x001FDDE8: the tables are triangular, indexed
// [lower race - 1][higher race - 1].
uint8_t resultRace(uint16_t devil1, uint16_t devil2, bool cursed)
{
    uint8_t a = raceOf(devil1), b = raceOf(devil2);
    if (a == static_cast<uint8_t>(Race::Fiend)) a = static_cast<uint8_t>(Race::Tyrant);
    if (b == static_cast<uint8_t>(Race::Fiend)) b = static_cast<uint8_t>(Race::Tyrant);
    uint8_t high = a > b ? a : b, low = a > b ? b : a;
    // As raw addresses: a race of 0 reads the bytes before the table.
    uint32_t table = cursed ? dat::address::CombineCurseTbl : dat::address::CombineTbl;
    return *guest::table<const uint8_t>(table + (low - 1u) * 32u + (high - 1u));
}

// cmbGetAverageLevel @ 0x001FDEC0: two devils (a + b + 1) / 2 + 1, three
// (a + b + c + 2) / 3. A sacrifice of level 0 counts as none.
int32_t averageLevel(const UnitWork& devil1, const UnitWork& devil2, const UnitWork* sacrifice, bool unitLevels)
{
    auto levelOf = [unitLevels](const UnitWork& unit) -> uint32_t {
        return unitLevels ? unit.level : dat::devilFormat(unit.id).level;
    };
    uint32_t a = levelOf(devil1), b = levelOf(devil2);
    uint32_t c = sacrifice ? levelOf(*sacrifice) : 0;
    if (c != 0)
        return static_cast<int32_t>((a + b + c + 2) / 3);
    return (static_cast<int32_t>(a + b + 1) >> 1) + 1;
}

// ===========================================================================
// Choosing the devil
// ===========================================================================

// cmbGetTargetDevil @ 0x001FDF78
uint16_t targetDevil(uint8_t race, uint8_t level)
{
    if (race == 0)
        return 0;
    std::vector<uint16_t> candidates;   // highest level first
    for (const DevilSortEntry& entry : devilsByRace())
        if (static_cast<uint8_t>(entry.format->race) == race && isFusible(entry.devil))
            candidates.push_back(entry.devil);
    if (candidates.empty())
        return 0;
    for (size_t i = 0; i < candidates.size(); ++i)
        if (dat::devilFormat(candidates[i]).level < level)
            return i ? candidates[i - 1] : candidates[0];
    return candidates.back();
}

// cmbGetRankUpDownDevil @ 0x001FDAC0. The first devil of the sorted list is
// never a result. A shift other than 1 or 2 doesn't move: it returns the
// devil itself if fusible, and otherwise never returns (no data reaches that).
uint16_t rankShiftedDevil(uint16_t devil, uint8_t shift)
{
    std::vector<DevilSortEntry> list = devilsByRace();
    int32_t count = static_cast<int32_t>(list.size());
    uint8_t race = raceOf(devil);
    int32_t index = -1;
    for (int32_t i = 0; i < count; ++i) {
        if (list[i].devil == devil) {
            index = i;
            break;
        }
    }
    if (index < 0 || shift == 0)
        return 0;
    int32_t step = shift == 1 ? -1 : shift == 2 ? 1 : 0;   // the list runs highest level first
    for (;;) {
        index += step;
        if (index < 1 || index >= count || static_cast<uint8_t>(list[index].format->race) != race)
            return 0;
        if (isFusible(list[index].devil))
            return list[index].devil;
    }
}

// cmbCalcNormal2 @ 0x001FE5F0. Devil 0xCD (Sakahagi) only comes from cursed fusion.
uint16_t normalFusion(const UnitWork& devil1, const UnitWork& devil2, bool cursed, bool unitLevels)
{
    uint8_t race = resultRace(devil1.id, devil2.id, cursed);
    uint8_t level = static_cast<uint8_t>(averageLevel(devil1, devil2, nullptr, unitLevels));
    uint16_t result = targetDevil(race, level);
    if (result == devil::Sakahagi && !cursed)
        return 0;
    return result;
}

// cmbCalcDevil2 @ 0x001FE690
uint16_t twoDevilFusion(const UnitWork& devil1, const UnitWork& devil2, bool cursed, bool unitLevels,
                        const uint16_t ids[2], const uint8_t races[2], FusionType* type)
{
    constexpr uint8_t kElement = static_cast<uint8_t>(Race::Element);
    constexpr uint8_t kMitama = static_cast<uint8_t>(Race::Mitama);
    constexpr uint8_t kFiend = static_cast<uint8_t>(Race::Fiend);

    uint16_t result = specialPairResult(ids[0], ids[1]);
    FusionType kind = FusionType::SpecialPair;
    if (result == 0) {
        uint8_t a = races[0], b = races[1];
        if ((a == kElement || b == kElement) && a != kFiend && b != kFiend) {
            if (a == b) {
                result = mitamaFromElements(ids[0], ids[1]);
                kind = FusionType::Mitama;
            } else {
                int other = a == kElement ? 1 : 0;   // the non-Element
                uint8_t shift = static_cast<uint8_t>(elementRankShift(ids[1 - other], static_cast<Race>(races[other])));
                if (cursed)
                    shift = shift == 1 ? 2 : shift == 2 ? 1 : shift;
                result = rankShiftedDevil(ids[other], shift);
                kind = shift == 2 ? FusionType::RankDown : FusionType::RankUp;
            }
        } else if ((a == kMitama || b == kMitama) && a != b) {
            result = a == kMitama ? ids[1] : ids[0];
            kind = FusionType::MitamaBoost;
        } else if (a != b) {
            result = normalFusion(devil1, devil2, cursed, unitLevels);
            kind = FusionType::Normal;
        } else {
            result = resultRace(ids[0], ids[1], cursed);
            kind = FusionType::Element;
        }
    }
    if (type)
        *type = kind;
    return result;
}

// ===========================================================================
// Sacrificial fusion
// ===========================================================================

// cmbChkIkenieExtPattern @ 0x001FD610: a result race for three races (the
// first two in either order), 0 if none.
uint8_t sacrificeRacePattern(uint16_t devil1, uint16_t devil2, uint16_t sacrifice)
{
    uint8_t a = raceOf(devil1), b = raceOf(devil2), c = raceOf(sacrifice);
    const SacrificeRacePattern& p = dat::kIkenieExtPatternTbl[0];
    for (int pass = 0; pass < 2; ++pass) {
        if (p.race1 == a && p.race2 == b && p.race3 == c)
            return p.birthrace;
        uint8_t swap = a;
        a = b;
        b = swap;
    }
    return 0;
}

// cmbChkMetato @ 0x001FD708: Metatron can't make Metatron.
bool isMetatronPair(uint16_t devil1, uint16_t devil2, uint16_t birth)
{
    return birth == devil::Metatron && (devil1 == devil::Metatron || devil2 == devil::Metatron);
}

// cmbChkIkenieExtPatternDevRace @ 0x001FD730: a devil, a race and a
// sacrifice race. The second pass swaps the devils but keeps only the low
// byte of the first ID.
uint16_t sacrificeDevilRacePattern(uint16_t devil1, uint16_t devil2, uint16_t sacrifice)
{
    uint8_t sacrificeRace = raceOf(sacrifice);
    uint16_t devil = devil1, other = devil2;
    for (int pass = 0; pass < 2; ++pass) {
        uint8_t otherRace = raceOf(other);
        for (const SacrificeDevilRacePattern& p : dat::kIkenieExtPatternDevRaceTbl) {
            if (p.devil == devil && p.race1 == otherRace && p.race2 == sacrificeRace
                && !isEventLocked(p.birth) && !isMetatronPair(devil, other, p.birth))
                return p.birth;
        }
        uint16_t previous = devil;
        devil = other;
        other = previous & 0xff;
    }
    return 0;
}

// cmbChkIkenieExtPatternDev @ 0x001FD878: fixed trios, then the normal result
// with this sacrifice.
uint16_t sacrificeDevilPattern(const UnitWork& devil1, const UnitWork& devil2, const UnitWork& sacrifice,
                               bool cursed, bool unitLevels)
{
    uint16_t a = devil1.id, b = devil2.id;
    for (int pass = 0; pass < 2; ++pass) {
        for (const SacrificeDevilPattern& p : dat::kIkenieExtPatternDevTbl)
            if (p.devil1 == a && p.devil2 == b && p.devil3 == sacrifice.id && !isEventLocked(p.birth))
                return p.birth;
        uint16_t swap = a;
        a = b;
        b = swap;
    }
    uint16_t normal = normalFusion(devil1, devil2, cursed, unitLevels);
    for (const SacrificeResultPattern& p : dat::kIkenieExtPatternDev2Tbl)
        if (p.devil1 == normal && p.devil2 == sacrifice.id && !isEventLocked(p.birth))
            return p.birth;
    return 0;
}

// cmbCalcIkenie @ 0x001FEA20: the two-devil result, unless that is a Mitama
// boost or a devil that can't come from a sacrifice. (The original also built
// the devil in a scratch unit and discarded it.)
uint16_t sacrificeFusion(const UnitWork& devil1, const UnitWork& devil2, const UnitWork&, bool cursed,
                         bool unitLevels, const uint16_t ids[2], const uint8_t races[2])
{
    FusionType type;
    uint16_t result = twoDevilFusion(devil1, devil2, cursed, unitLevels, ids, races, &type);
    if (type == FusionType::MitamaBoost)
        return 0;
    if (cannotBeSacrificed(result))
        return 0;
    return result;
}

// ===========================================================================
// Others
// ===========================================================================

// cmbCalcCombineManin @ 0x001FF648: with a Deathstone, the Fiend for this
// race and Kagutsuchi phase.
uint16_t fiendFusion(uint16_t devil)
{
    int32_t moon = static_cast<int32_t>(evt::GetAgeOfMoon());
    int32_t phase = -1, race = -1;
    for (int i = 0; i < 5; ++i)
        if (dat::kCombineManinKagTbl[i].min <= moon && moon <= dat::kCombineManinKagTbl[i].max)
            phase = i;
    for (int i = 0; i < 4; ++i)
        if (dat::kCombineManinRaceTbl[i] == raceOf(devil))
            race = i;
    if (!dat::hasItem(item::Deathstone, 1))
        return 0;
    if (phase < 0 || race < 0)
        return 0;
    uint16_t fiend = dat::kCombineManinTbl[race][phase];
    return isEventLocked(fiend) ? 0 : fiend;
}

// cmbChkDante @ 0x001FF758: Dante can't be fused.
bool involvesDante(const UnitWork& devil1, const UnitWork& devil2, const UnitWork* sacrifice)
{
    return devil1.id == devil::Dante || devil2.id == devil::Dante || (sacrifice && sacrifice->id == devil::Dante);
}

} // namespace nocturne::cmb
