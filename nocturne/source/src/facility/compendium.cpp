// The demon compendium (original unit: fclEncyc).
#include "nocturne/facility/compendium.hpp"

#include <cstring>

#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/stock.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/libc/qsort.hpp"

namespace nocturne::fcl {

namespace {

GlobalWork& global() { return dat::globalWork(); }

// A record by index, as the original addresses it: index -1 (not found)
// reads the 0xB0 bytes before the array.
EncycRecord& recordAt(int32_t index)
{
    uint32_t base = guest::addressOf(global().encyc_records);
    return *guest::table<EncycRecord>(base + static_cast<uint32_t>(index) * sizeof(EncycRecord));
}

void updateCompleteFlag()
{
    if (completionPercent() < 100)
        evt::BitOff(0x913);
    else
        evt::BitOn(0x913);
}

// The slot for a new or existing entry, or -1 (see record()).
int32_t claimSlot(uint16_t devil, bool overwrite, int32_t* result)
{
    int32_t index = find(devil);
    *result = 1;
    if (index < 0) {
        index = global().encyc_count;
        if (index >= kCompendiumSize) {
            diag::print(diag::Message::CompendiumFull);
            return -1;
        }
        global().encyc_count = index + 1;
        *result = 0;
    } else if (!overwrite) {
        *result = -1;
        return -1;
    }
    return index;
}

uint8_t raceOf(const EncycRecord& record) { return static_cast<uint8_t>(dat::devilFormat(record.id).race); }

} // namespace

// ===========================================================================
// Records
// ===========================================================================

// fclEncyc_SetElem @ 0x00219DF0
void setRecord(EncycRecord& record, const UnitWork& unit)
{
    std::memset(&record, 0, sizeof record);
    record.id = unit.id;
    record.maxhp = unit.maxhp;
    record.maxmp = unit.maxmp;
    record.exp = unit.exp;
    record.level = unit.level;
    std::memcpy(record.param, unit.param, sizeof record.param);
    std::memcpy(record.skill, unit.skill, sizeof record.skill);
    std::memcpy(record.skillparam, unit.skillparam, sizeof record.skillparam);
    record.skillcnt = unit.skillcnt;
    std::memcpy(record.mitamaparam, unit.mitamaparam, sizeof record.mitamaparam);
    std::memcpy(record.levelupparam, unit.levelupparam, sizeof record.levelupparam);
    std::memcpy(record.keisyoskill, unit.keisyoskill, sizeof record.keisyoskill);
    std::memcpy(record.keiattr, unit.keiattr, sizeof record.keiattr);
    record.hensinmae = unit.hensinmae;
    record.flag = unit.flag & 0x240;
    record.hensinmaeexp = unit.hensinmaeexp;
}

// facility_H.fclencyceelem_t.Clear @ 0x00219FC0 (HD lead): clears, then copies.
void copyRecord(EncycRecord& destination, const EncycRecord& source)
{
    std::memset(&destination, 0, sizeof destination);
    std::memcpy(&destination, &source, sizeof destination);
}

// SetRecordToUnitCore @ 0x0021A118: a fresh devil of the species with the
// recorded stats, skills and flags.
void restoreFromRecord(UnitWork& unit, const EncycRecord& record)
{
    std::memset(&unit, 0, sizeof unit);
    cmb::copyDefaultDevil(record.id, unit);
    unit.exp = record.exp;
    unit.hp = unit.maxhp = record.maxhp;
    unit.mp = unit.maxmp = record.maxmp;
    unit.level = record.level;
    std::memcpy(unit.param, record.param, sizeof unit.param);
    std::memcpy(unit.skill, record.skill, sizeof unit.skill);
    std::memcpy(unit.skillparam, record.skillparam, sizeof unit.skillparam);
    unit.skillcnt = record.skillcnt;
    std::memcpy(unit.mitamaparam, record.mitamaparam, sizeof unit.mitamaparam);
    std::memcpy(unit.levelupparam, record.levelupparam, sizeof unit.levelupparam);
    std::memcpy(unit.keisyoskill, record.keisyoskill, sizeof unit.keisyoskill);
    std::memcpy(unit.keiattr, record.keiattr, sizeof unit.keiattr);
    unit.flag &= ~0x240u;
    unit.hensinmae = record.hensinmae;
    unit.flag |= record.flag;
    unit.hensinmaeexp = record.hensinmaeexp;
}

// SetRecordToUnit @ 0x0021A0B8
void restore(UnitWork& unit, int32_t devil)
{
    restoreFromRecord(unit, recordAt(find(devil)));
}

// CompareUnitToRecord @ 0x0021A308. Stat 1 (unused) isn't compared, and the
// skills are compared as sets of the recorded count.
int32_t compareToRecord(const UnitWork& unit, const EncycRecord& record)
{
    static const int8_t kStats[] = {0, 2, 3, 4, 5};   // the table at 0x3322C0
    if (record.flag != (unit.flag & 0x240)) return 1;
    if (record.maxhp != unit.maxhp) return 2;
    if (record.maxmp != unit.maxmp) return 3;
    if (static_cast<uint32_t>(record.exp) != static_cast<uint32_t>(unit.exp)) return 4;
    if (record.level != unit.level) return 5;
    for (int8_t stat : kStats) {
        if (record.param[stat] != unit.param[stat]) return 6;
        if (record.skillparam[stat] != unit.skillparam[stat]) return 7;
        if (record.mitamaparam[stat] != unit.mitamaparam[stat]) return 8;
        if (record.levelupparam[stat] != unit.levelupparam[stat]) return 9;
    }
    if (record.skillcnt != unit.skillcnt) return 10;
    int32_t skills = record.skillcnt;
    for (int32_t i = 0; i < skills; ++i) {
        bool found = false;
        for (int32_t j = 0; j < skills && !found; ++j)
            found = record.skill[i] == unit.skill[j];
        if (!found) return 11;
    }
    if (record.hensinmae != unit.hensinmae) return 12;
    if (record.hensinmaeexp != unit.hensinmaeexp) return 13;
    return 0;
}

// ===========================================================================
// Registering
// ===========================================================================

// fclEncycSearch @ 0x00216B20
int32_t find(int32_t devil)
{
    for (int32_t i = 0; i < global().encyc_count; ++i)
        if (devil == global().encyc_records[i].id)
            return i;
    return -1;
}

// fclEncycGetNum @ 0x00216B78
int32_t count()
{
    return global().encyc_count;
}

// fclEncycGetRatio2 @ 0x00216B90
int32_t completionPercent()
{
    int32_t entries = count();
    int32_t ratio = static_cast<int32_t>(static_cast<uint32_t>(entries) * 100u) / kCompendiumSize;
    return entries > 0 && ratio < 1 ? 1 : ratio;
}

// fclEncycRegist @ 0x00216A18
int32_t record(const UnitWork& unit, bool overwrite)
{
    int32_t result;
    int32_t index = claimSlot(unit.id, overwrite, &result);
    if (index < 0)
        return -1;
    setRecord(global().encyc_records[index], unit);
    updateCompleteFlag();
    return result;
}

// fclEncycRegist2 @ 0x00216910
int32_t recordCopy(const EncycRecord& source, bool overwrite)
{
    int32_t result;
    int32_t index = claimSlot(source.id, overwrite, &result);
    if (index < 0)
        return -1;
    copyRecord(global().encyc_records[index], source);
    updateCompleteFlag();
    return result;
}

// GetValidUnitIndex @ 0x00219318. A demon without a record is compared with
// whatever precedes the array.
int32_t outdatedUnits(uint8_t* units)
{
    bool countOnly = units == nullptr;
    int32_t found = 0;
    for (int i = 4; i < 16; ++i) {
        const UnitWork& unit = global().units[i];
        if (!(unit.flag & UnitFlag::Valid) || (unit.flag & 0x10) || (unit.badstat & 0x800))
            continue;
        if (compareToRecord(unit, recordAt(find(unit.id))) != 0) {
            ++found;
            if (countOnly)
                return found;
            *units++ = static_cast<uint8_t>(i);
        }
    }
    return found;
}

// fclEncycCheckRegistable @ 0x00216BF0
int32_t anyOutdated()
{
    return outdatedUnits(nullptr);
}

// RegistAll @ 0x00219400
int32_t recordAll(const RegisterList& list)
{
    int32_t updated = 0;
    for (int32_t i = 0; i < list.count; ++i)
        if (record(global().units[list.unit[i]], true) == 1)
            ++updated;
    return updated;
}

// fclEncycDebugRegist @ 0x00216C08: registers the stock (not the
// Demi-fiend), each with Strength one lower, without overwriting.
void debugRecordStock()
{
    int32_t entries = global().stock_count;
    for (int32_t i = 0; i < entries; ++i) {
        const UnitWork& unit = global().units[global().stock_list[i]];
        if (unit.flag & UnitFlag::PlayerCharacter)
            continue;
        UnitWork copy = unit;
        if (copy.param[0] > 0)
            copy.param[0] -= 1;
        record(copy, false);
    }
}

// ===========================================================================
// Sorting
// ===========================================================================

// FillIndex @ 0x00219DC0
void fillIndex(int16_t* indexes, int32_t count)
{
    for (int16_t i = 0; i < count; ++i)
        indexes[i] = i;
}

// cmbRaceSortCallback @ 0x00219C40: race, then highest level first.
int compareByRace(const void* left, const void* right)
{
    const EncycRecord& a = recordAt(*static_cast<const int16_t*>(left));
    const EncycRecord& b = recordAt(*static_cast<const int16_t*>(right));
    if (raceOf(a) != raceOf(b))
        return raceOf(a) < raceOf(b) ? -1 : 1;
    if (a.level != b.level)
        return a.level > b.level ? -1 : 1;
    return 0;
}

// cmbLevelSortCallback @ 0x00219D00: highest level first, then race.
int compareByLevel(const void* left, const void* right)
{
    const EncycRecord& a = recordAt(*static_cast<const int16_t*>(left));
    const EncycRecord& b = recordAt(*static_cast<const int16_t*>(right));
    if (a.level != b.level)
        return a.level > b.level ? -1 : 1;
    if (raceOf(a) != raceOf(b))
        return raceOf(a) < raceOf(b) ? -1 : 1;
    return 0;
}

// CreateSortIndexByRace @ 0x00219BA0
void sortByRace(int16_t* indexes)
{
    int32_t entries = count();
    fillIndex(indexes, entries);
    libc::qsort(indexes, static_cast<uint32_t>(entries), 2, compareByRace);
}

// CreateSortIndexByLevel @ 0x00219BF0
void sortByLevel(int16_t* indexes)
{
    int32_t entries = count();
    fillIndex(indexes, entries);
    libc::qsort(indexes, static_cast<uint32_t>(entries), 2, compareByLevel);
}

} // namespace nocturne::fcl
