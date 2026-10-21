// The demon compendium (original unit: fclEncyc).
//
// GlobalWork::encyc_records holds up to 184 snapshots of demons, one per
// devil ID, in registration order; a demon can be summoned back from its
// snapshot. Event bit 0x913 is set while the compendium is 100% complete.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"

namespace nocturne::fcl {

inline constexpr int32_t kCompendiumSize = 184;

// ---- Records -------------------------------------------------------------------------

void setRecord(EncycRecord& record, const UnitWork& unit);              // fclEncyc_SetElem
void copyRecord(EncycRecord& destination, const EncycRecord& source);   // (fclencyceelem_t, 0x219FC0)
void restoreFromRecord(UnitWork& unit, const EncycRecord& record);      // SetRecordToUnitCore: summon
void restore(UnitWork& unit, int32_t devil);                            // SetRecordToUnit
// CompareUnitToRecord: 0 if the unit matches its record, else which field
// differs first (1 flags ... 13 pre-evolution EXP).
int32_t compareToRecord(const UnitWork& unit, const EncycRecord& record);

// ---- Registering -----------------------------------------------------------------------

int32_t find(int32_t devil);                                            // fclEncycSearch: index or -1
int32_t count();                                                        // fclEncycGetNum
int32_t completionPercent();                                            // fclEncycGetRatio2: at least 1 once started
// fclEncycRegist: 0 for a new entry, 1 for an update, -1 if the entry exists
// and `overwrite` is false, or the compendium is full.
int32_t record(const UnitWork& unit, bool overwrite);
int32_t recordCopy(const EncycRecord& source, bool overwrite);          // fclEncycRegist2: the same, from a record
// GetValidUnitIndex: stock demons (units 4..15, alive, not flagged 0x10)
// whose record is missing or out of date, written to `units` (or, with
// none, stopping at the first); returns how many.
int32_t outdatedUnits(uint8_t* units);
int32_t anyOutdated();                                                  // fclEncycCheckRegistable

// The compendium menu's list of units to register (a partial view).
struct RegisterList {
    uint8_t unknown_00[0x70];
    int32_t count;
    uint8_t unit[12];
};
int32_t recordAll(const RegisterList& list);                            // RegistAll: how many were updated
void debugRecordStock();                                                // fclEncycDebugRegist

// ---- Sorting ------------------------------------------------------------------------------

void fillIndex(int16_t* indexes, int32_t count);                        // FillIndex: 0, 1, 2 ...
int compareByRace(const void* left, const void* right);                 // cmbRaceSortCallback
int compareByLevel(const void* left, const void* right);                // cmbLevelSortCallback
void sortByRace(int16_t* indexes);                                      // CreateSortIndexByRace
void sortByLevel(int16_t* indexes);                                     // CreateSortIndexByLevel

} // namespace nocturne::fcl
