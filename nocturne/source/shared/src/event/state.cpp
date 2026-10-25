#include "nocturne/event/state.hpp"

#include "nocturne/address.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::evt {

namespace {

constexpr uint32_t kMoonFade = addr(0x0054f75c);   // float (gp-relative): the moon's draw alpha

// Kagutsuchi's flags in the global work.
constexpr uint8_t kMoonCycles = 1;   // the phase advances
constexpr uint8_t kMoonDrawn = 2;

GlobalWork& work() { return dat::globalWork(); }

// A flag's word: flag / 32 as the original divides (toward zero).
uint32_t& flagWord(int32_t flag) { return work().event_bits[flag / 32]; }
uint32_t flagBit(int32_t flag) { return 1u << (static_cast<uint32_t>(flag) & 31); }

void setMoonFade(ee::Float fade) { *guest::table<uint32_t>(kMoonFade) = fade.bits(); }

} // namespace

// evtBitAllOff @ 0x001E0E38
void clearAllFlags()
{
    for (uint32_t& word : work().event_bits)
        word = 0;
}

// evtBitOn @ 0x001E0ED0
void setFlag(int32_t flag) { flagWord(flag) |= flagBit(flag); }

// evtBitOff @ 0x001E0F10
void clearFlag(int32_t flag) { flagWord(flag) &= ~flagBit(flag); }

// evtBitCheck @ 0x001E0F50
bool isFlagSet(int32_t flag) { return (flagWord(flag) & flagBit(flag)) != 0; }

// evtGetAgeOfMoon @ 0x001E9998: phases past full count back down (9 is 7).
uint32_t moonAge()
{
    const uint32_t phase = work().moon_phase;
    return phase > 8 ? 8 - (phase & 7) : phase;
}

// evtGetAgeOfMoon16 @ 0x001E99C0
uint32_t moonPhase() { return work().moon_phase; }

// evtSetAgeOfMoon @ 0x001E99D0
void setMoonPhase(int32_t phase)
{
    work().moon_phase = static_cast<uint8_t>(static_cast<uint32_t>(phase) & 15);
    work().moon_move_bits = 0;
}

// evtEnableMoonCalc @ 0x001E99E8
void enableMoonCycle() { work().moon_flags |= kMoonCycles; }

// 0x001E9A00 (no original name; the HD remaster's evtDisableMoonCalc, whose
// body it protects, is the likely match)
void disableMoonCycle() { work().moon_flags &= static_cast<uint8_t>(~kMoonCycles); }

// evtEnableMoonDraw @ 0x001E9A18
void showMoon()
{
    work().moon_flags |= kMoonDrawn;
    setMoonFade(ee::Float::fromInt(1));
}

// evtDisableMoonDraw @ 0x001E9A38
void hideMoon()
{
    work().moon_flags &= static_cast<uint8_t>(~kMoonDrawn);
    setMoonFade(ee::Float::fromBits(0));
}

// evtEnableMoonDraw2 @ 0x001E9A50
void showMoonKeepFade() { work().moon_flags |= kMoonDrawn; }

// evtDisableMoonDraw2 @ 0x001E9A68
void hideMoonKeepFade() { work().moon_flags &= static_cast<uint8_t>(~kMoonDrawn); }

} // namespace nocturne::evt
