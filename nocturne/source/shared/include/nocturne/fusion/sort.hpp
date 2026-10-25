// Sorting for fusion (original unit: fclStockSort).
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::cmb {

// cmbSortKeisyoSkill: sort the inherited-skill list by skill ID (empty slots
// last), keeping each skill's keiattr byte with it.
void sortInheritedSkills(UnitWork& unit);

// One entry of the devil list built by sortDevilsByRace.
struct DevilSortEntry {
    uint16_t devil;
    uint16_t unused;                     // left as it was
    Ptr32<const DevilFormat> format;
};
static_assert(sizeof(DevilSortEntry) == 8);

// (0x213230) sortDevilsByRace's comparison of two entries.
int compareDevils(const void* left, const void* right);

// (0x2133A0) devils 0..count-1 sorted by race, then by level, highest first.
void sortDevilsByRace(DevilSortEntry* entries, uint16_t count);

} // namespace nocturne::cmb
