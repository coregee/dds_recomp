// Buffs and debuffs ("hojo" = 補助, support) (original unit: nbCalc).
//
// Each combatant's Party record holds 20 counters. The stat counters run
// from -4 to +4: one step per -kaja (buff) or -nda (debuff) cast.
#pragma once

#include <cstdint>

#include "nocturne/ee/float.hpp"

namespace nocturne::nb {

// Party::count indexes.
enum class BuffKind : int32_t {
    Attack        = 4,   // Tarukaja / Tarunda
    Magic         = 5,   // Makakaja / Makanda
    Evasion       = 6,   // Sukukaja / Sukunda (with Accuracy)
    Defense       = 7,   // Rakukaja / Rakunda
    Accuracy      = 8,
    NullIce       = 9,   // temporary elemental nulls
    NullFire      = 10,
    NullDeath     = 11,  // Tetraja covers Death and Expel
    NullExpel     = 12,
    RepelMagic    = 13,  // Makarakarn
    RepelPhysical = 14,  // Tetrakarn
    Focus         = 15,  // next physical attack x2.5
    AffinityRow   = 19,  // > 0: use this affinity-table row instead of the party's affinities
};
// Counters 0..3 and 16..18 exist (limit 127) but their use is not yet known.

int32_t buffCounter(int32_t formindex, int32_t type);              // nbGetHojoCounter
void setBuffCounter(int32_t formindex, int32_t type, int32_t value);  // nbSetHojoCounter
int32_t buffMax(int32_t type);                                     // nbGetHojoCounterMax
int32_t buffMin(int32_t type);                                     // nbGetHojoCounterMin

// nbSetHojoAddCounter: add to a counter, clamped. Returns the change
// actually made. With preview set, nothing is written.
int32_t addBuff(int32_t formindex, int32_t type, int32_t delta, bool preview);

// nbSetHojoKouka: apply a skill's NormalSkill::hojotype mask. Returns the
// total size of all changes (used by the AI to score buff skills).
int32_t applyBuffs(int32_t formindex, uint32_t mask, int32_t amount, bool preview);

// nbGetHojoRitu: the damage/accuracy multiplier from one counter.
ee::Float buffMultiplier(int32_t formindex, int32_t type);
inline ee::Float buffMultiplier(int32_t formindex, BuffKind type) { return buffMultiplier(formindex, static_cast<int32_t>(type)); }

} // namespace nocturne::nb
