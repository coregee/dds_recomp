// Hardtype's rows for the tables whose layout differs by version: it packs
// more rows into the same space (data/tables.hpp declares the tables).
#pragma once

#include <cstdint>

namespace nocturne {

struct InheritanceLevelPacked {   // fclKeisyoSkillLevel: 3-byte rows, the skill unaligned
    uint8_t skill[2];             // low byte, high byte
    uint8_t level;
    uint16_t skillId() const { return static_cast<uint16_t>(skill[0] | skill[1] << 8); }
};
static_assert(sizeof(InheritanceLevelPacked) == 3);

struct EventDevilShort {          // fclEventDevilTbl: twice the rows of US Maniax's
    uint16_t devil;
    uint16_t eventflag;
};

namespace dat {

using InheritanceLevelRow = InheritanceLevelPacked;
inline constexpr int kInheritanceLevelCount = 302;
using EventDevilRow = EventDevilShort;
inline constexpr int kEventDevilCount = 68;
// datEncountPack: the tables are read 188 bytes apart with 24 entries each,
// so a table's last entry overlaps the start of the next (the packs keep
// US Maniax's size and fields).
inline constexpr int32_t kEncounterEntries = 24;
inline constexpr uint32_t kEncounterTableSize = 188;

} // namespace dat

} // namespace nocturne
