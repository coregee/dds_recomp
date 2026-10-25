// What the Hardtype rebalance adds to US Maniax (docs/hardtype.md).
//
// Hardtype's own code reads the global work at the fixed address where the
// game allocates it, 0x1248500, rather than through its pointer (inferred:
// the Demi-fiend's unit, its units[0], is what Hardtype compares against
// 0x1248F54, and its other addresses fall on fields that fit). It also tells
// the battle's enemy units (allocated at 0x116xxxx) from the party and stock
// (above 0x1200000) by their addresses.
#pragma once

#include <cstdint>

#include "nocturne/guest.hpp"
#include "nocturne/variant.hpp"

namespace nocturne {
struct UnitWork;
}

namespace nocturne::hardtype {

inline constexpr uint32_t kGlobalWork = 0x01248500;           // where the game allocates the global work
inline constexpr uint32_t kMoonPhase = kGlobalWork + 0xa41;    // GlobalWork::moon_phase (AI condition 29)
inline constexpr uint32_t kMoonMoveBits = kGlobalWork + 0xa44; // GlobalWork::moon_move_bits (bit 1: accuracy, evasion)
inline constexpr uint32_t kHeart24 = kGlobalWork + 0x1d13;     // GlobalWork::hearts_owned[24]
inline constexpr uint32_t kDemiFiend = kGlobalWork + 0xa54;    // GlobalWork::units[0]
inline constexpr uint32_t kOptions = 0x002ff388;               // a byte no code writes (Hardtype's optional patches, presumably)

inline uint8_t byteAt(uint32_t address) { return *guest::table<uint8_t>(address); }

// Hardtype's own functions (src/data/hardtype.cpp).
bool hasSkill(const UnitWork& unit, uint32_t skill);   // (0x2FE240) among its first eight
bool aiCondition(int32_t type, int32_t n);             // its AI condition types 29 (0x2FEA30: the moon's phase), 60 (0x2FEA10), 61 (0x2FE9F0)
uint32_t pressGaugeRegister();                         // what types 60 and 61 leave in s0: the gauge's second count << 4

// Hardtype's own state, kept among its added code (0x2FDC20..0x2FF388).
inline uint16_t& hpBeforeChange() { return *guest::table<uint16_t>(0x002fe1d8); }   // the HP datAddHp last started from
// Stand-ins: a skill Hardtype adds or changes can be shown as another
// (0x2FE3E0: pairs of skill and stand-in, up to a 0). The action's READY
// state notes the pair it uses: the acting skill, which its costs and checks
// follow, and the stand-in, whose effect, targets and motion are played.
// (Nothing clears the pair: an action that notes none keeps the last.)
inline constexpr uint32_t kStandIns = 0x002fe3e0;
inline uint16_t& actingSkill() { return *guest::table<uint16_t>(0x002fe91c); }
inline uint16_t& standInSkill() { return *guest::table<uint16_t>(0x002fe91e); }
uint16_t standInFor(uint16_t skill);                   // (0x2FE8D0) the skill itself if it has none

// Registers Hardtype's code leaves for later code to read: t7, the last
// result of nbGetAisyo (which nbGetKoukaHp reads). (A register: each test of
// a function on its own starts it at 0, as the interpreter does.)
uint32_t& affinityRegister();
// What GetUnitWorkFromFormindex leaves in a0: for a slot past 15, the slot
// less 16; for a unit in battle, the battle's record; else its formation's
// bit 1.
uint32_t unitLookupRegister(int32_t formindex);

} // namespace nocturne::hardtype
