// Skill inheritance (original unit: cmbCombine): US Maniax's own (shared/src/fusion/inheritance.cpp has the rest).
#include "nocturne/fusion/inheritance.hpp"

#include "nocturne/data/tables.hpp"

namespace nocturne::cmb {

// cmbGetKeisyoSkillLevel @ 0x00222BB0: 1 for skills not in the table. (The
// counter is Hardtype's; US Maniax always starts from the first row.)
uint8_t inheritLevel(uint16_t skill, uint32_t, uint32_t* counterOut)
{
    const InheritanceLevel* levels = dat::tableAt<InheritanceLevel>(dat::address::InheritanceLevel);
    for (int i = 0; i < 227; ++i) {
        if (levels[i].skill == skill) {
            if (counterOut)
                *counterOut = static_cast<uint32_t>(i);
            return levels[i].level;
        }
    }
    if (counterOut)
        *counterOut = 227;
    return 1;
}

} // namespace nocturne::cmb
