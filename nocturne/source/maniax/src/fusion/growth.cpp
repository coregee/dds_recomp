// Mutations (original unit: cmbCombine): US Maniax's own (shared/src/fusion/growth.cpp has the rest).
#include "nocturne/fusion/growth.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/inheritance.hpp"

namespace nocturne::cmb {

// cmbGetMutationSkill @ 0x00223520: up to 64 tries to find a skill one
// inheritance level above `skill` that the unit can learn and doesn't own.
uint16_t mutationSkill(uint16_t skill, UnitWork& unit)
{
    const InheritanceLevel* levels = dat::tableAt<InheritanceLevel>(dat::address::InheritanceLevel);
    for (int attempt = 0; attempt < 64; ++attempt) {
        uint16_t candidate = levels[sdf::GetRand() % 227].skill;
        uint32_t candidateLevel = inheritLevel(candidate);
        if (findSkill(candidate, unit) < 0 && inheritRate(unit, candidate) != 0 && skill != candidate) {
            uint32_t level = inheritLevel(skill);
            if (candidateLevel <= level + 1 && level + 1 <= candidateLevel)
                return candidate;
        }
    }
    return 0;
}

} // namespace nocturne::cmb
