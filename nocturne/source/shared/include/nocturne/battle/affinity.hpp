// Affinity in battle (original unit: nbCalc).
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/ee/float.hpp"

namespace nocturne::nb {

// nbGetAisyo: a combatant's affinity to an element right now: the party's
// affinities, overridden by Stone/Fly, plus temporary nulls, Tetrakarn /
// Makarakarn (for physical/magic skills) and passive Void/Drain/Repel/Anti
// skills. skill may be -1 (no skill: Tetrakarn/Makarakarn are ignored).
Affinity affinity(int32_t skill, int32_t formindex, Attribute attr);
// [version] ... the unit's passive skills for an element 0..10 but Almighty
// (source/<version>/src/battle/affinity.cpp).
uint32_t passiveAffinity(const UnitWork& unit, int32_t element, uint32_t packed);
// [version] nbGetAisyoRitu: whether the attacker's skill ignores resistance,
// and the ratio after its boosts.
bool piercesResistance(const UnitWork& attacker, int32_t skill);
Affinity noteAffinity(Affinity result);   // what a version keeps of each nbGetAisyo result
ee::Float boostedRatio(const UnitWork& attacker, int32_t skill, Attribute attr, ee::Float ratio);

// nbGetVirtualAisyo: how the skill would resolve against the target:
// Affinity::Repel, Drain or Null, or 0. Used by the AI.
uint32_t virtualAffinity(int32_t skill, int32_t source, int32_t target);

// nbGetAisyoTable: which affinity-table row applies to the combatant (its
// species row, the override counter, or the Fly/Stone rows). Used by AI.
int32_t affinityRowOf(int32_t formindex);

// nbGetAisyoRitu: the damage multiplier from affinity (rate / 100), after
// Freeze and Pierce, times 1.5 for Son's Oath or an element Boost.
ee::Float damageRatio(int32_t skill, int32_t source, int32_t target);

} // namespace nocturne::nb
