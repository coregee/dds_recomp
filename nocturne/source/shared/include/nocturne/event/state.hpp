// The story's state in the global work (original unit: evt): the event
// flags and Kagutsuchi's phase.
//
// The rest of the rewrite still reaches these through external.hpp
// (evt::BitCheck, evt::GetAgeOfMoon ...), which the differential tests fake;
// these are the functions themselves, proven against the original's own.
#pragma once

#include <cstdint>

namespace nocturne::evt {

// The event flags: 4096 bits, 32 to a word. A flag's word is flag / 32
// (rounding toward zero) and its bit flag & 31; nothing checks the range.
void clearAllFlags();          // evtBitAllOff
void setFlag(int32_t flag);    // evtBitOn
void clearFlag(int32_t flag);  // evtBitOff
bool isFlagSet(int32_t flag);  // evtBitCheck

// Kagutsuchi's phase: 0..15 as stored (0 new, 8 full), and as the waxing and
// waning count 0..8 ... 0 that phase-dependent rules use.
uint32_t moonAge();            // evtGetAgeOfMoon: 0..8, 8 at full
uint32_t moonPhase();          // evtGetAgeOfMoon16: 0..15
void setMoonPhase(int32_t phase);   // evtSetAgeOfMoon: the low four bits; stops the moon's movement

// Whether the phase advances as the player walks, and whether the moon is
// drawn (the first pair also sets its fade fully in or out).
void enableMoonCycle();        // evtEnableMoonCalc
void disableMoonCycle();       // (0x1E9A00, no original name)
void showMoon();               // evtEnableMoonDraw
void hideMoon();               // evtDisableMoonDraw
void showMoonKeepFade();       // evtEnableMoonDraw2
void hideMoonKeepFade();       // evtDisableMoonDraw2

// The moon's own texture ("/fld/f/bin/moon_07.tmx"), for a battle that shows it
// (not in the first release).
void loadMoonTexture();        // (0x1E9528, no original name)
void releaseMoonTexture();     // (0x1E9570, no original name)

} // namespace nocturne::evt
