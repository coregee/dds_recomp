// Mutations (original unit: cmbCombine): Hardtype's own (shared/src/fusion/growth.cpp has the rest).
#include "nocturne/fusion/growth.hpp"

#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/fusion/inheritance.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::cmb {

// cmbGetMutationSkill @ 0x00223520: up to 64 tries to find a skill one
// inheritance level above `skill` that the unit can learn and doesn't own.
// The candidates are still the first 227 of the 302 packed rows, and the
// level lookups start their row counters from what the calls before left in
// the register (see inheritLevel): the RNG's carry bit, then the unit's
// level less its devil's base level (from inheritRate), then where the
// previous lookup stopped.
uint16_t mutationSkill(uint16_t skill, UnitWork& unit)
{
    const InheritanceLevelPacked* levels = dat::tableAt<InheritanceLevelPacked>(dat::address::InheritanceLevel);
    for (int attempt = 0; attempt < 64; ++attempt) {
        const uint32_t carry = *guest::table<uint32_t>(0x00529be0) >> 31;   // the default RNG's third word
        const uint16_t candidate = levels[sdf::GetRand() % 227].skillId();
        const uint32_t candidateLevel = inheritLevel(candidate, carry);
        if (findSkill(candidate, unit) >= 0 || inheritRate(unit, candidate) == 0 || skill == candidate)
            continue;
        uint32_t counter = static_cast<uint32_t>(unit.level - dat::devilFormat(unit.id).level);
        if (inheritLevel(skill, counter, &counter) + 1u < candidateLevel)
            continue;
        if (!(candidateLevel < inheritLevel(skill, counter) + 1u))
            return candidate;
    }
    return 0;
}

} // namespace nocturne::cmb
