// The battle's system effects (original unit: effBattleSystem): the ailment,
// hit and talk effects a formation shows, by family, as far as rewritten:
// their lengths. Creating, running and drawing them is the effect library's
// part (external.hpp). Type and family names from smt3-decomp's
// effBattleSystem.c (effBTLSystemHandle_t, effBTLSys_<family>_*).
#pragma once

#include <cstdint>

namespace nocturne::eff {

// A system effect's family: its row in the family table (0x31BF00, 56 bytes
// a row: create, end, ... and getLength at +0x14). 1..11 follow the ailments'
// order.
enum class SystemFamily : int32_t {
    Shock = 1,
    Freeze = 2,
    Sleep = 3,
    Panic = 4,
    Bind = 5,
    Mute = 6,          // Close
    Poison = 7,
    Charm = 8,
    Stun = 9,          // Paralyze
    Fly = 10,
    Stone = 11,
    Curse = 12,
    CurseCamp = 13,    // CurseCAMP
    StoneShatter = 14, // Stone_Dead
    Repel = 17,        // Hansya
    Drain = 18,        // Kyusyuu
    Return = 20,
    Attack = 24,
    AttackC = 25,      // (tentatively the critical's)
    Encounter = 26,
    TalkHeal = 27,     // Nego_Kaihuku
    TalkDrain = 28,    // Nego_Kyusyu
    TalkStone = 29,    // Nego_Stone
};

// A playing system effect (effBTLSystemHandle_t).
struct SystemEffect {
    int32_t family;
    uint32_t effect;       // the family's own effect
    uint32_t pFormation;   // the formation it plays on
};

// A family's effect's length in frames (its getLength).
uint32_t familyLength(SystemFamily family, uint32_t effect);

// effBTLSystemGetLength (0x173EF0): a system effect's length in frames; 0
// for a family with no length.
uint32_t systemEffectLength(const SystemEffect& effect);

} // namespace nocturne::eff
