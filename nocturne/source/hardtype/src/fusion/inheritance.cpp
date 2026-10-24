// Skill inheritance (original unit: cmbCombine): Hardtype's own (shared/src/fusion/inheritance.cpp has the rest).
#include "nocturne/fusion/inheritance.hpp"

#include "nocturne/data/tables.hpp"

namespace nocturne::cmb {

// cmbGetKeisyoSkillLevel @ 0x00222BB0: 1 for skills not in the table, which
// Hardtype packs into 3-byte rows. It no longer clears its row counter, so
// it counts from what the caller left there: it searches 302 - counter rows
// from the first (just the first when that is none), and leaves the counter
// where it stopped.
uint8_t inheritLevel(uint16_t skill, uint32_t counter, uint32_t* counterOut)
{
    const InheritanceLevelPacked* levels = dat::tableAt<InheritanceLevelPacked>(dat::address::InheritanceLevel);
    for (int i = 0;; ++i) {
        if (levels[i].skillId() == skill) {
            if (counterOut)
                *counterOut = counter;
            return levels[i].level;
        }
        if (++counter >= static_cast<uint32_t>(dat::kInheritanceLevelCount))
            break;
    }
    if (counterOut)
        *counterOut = counter;
    return 1;
}

} // namespace nocturne::cmb
