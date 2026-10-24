// US Maniax's rows for the tables whose layout differs by version
// (data/tables.hpp declares the tables themselves).
#pragma once

#include "nocturne/data/records.hpp"

namespace nocturne::dat {

using InheritanceLevelRow = InheritanceLevel;   // fclKeisyoSkillLevel
inline constexpr int kInheritanceLevelCount = 227;
using EventDevilRow = EventDevil;               // fclEventDevilTbl
inline constexpr int kEventDevilCount = 34;
// datEncountPack: four tables of 12 entries each.
inline constexpr int32_t kEncounterEntries = 12;
inline constexpr uint32_t kEncounterTableSize = sizeof(EncountTbl);

} // namespace nocturne::dat
