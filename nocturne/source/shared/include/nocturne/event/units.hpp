// The event units (original unit: evtUnitManager), as far as rewritten: the
// motion requests a unit's owner makes. A battle slot's unit is one
// (Formation::hunit).
#pragma once

#include <cstdint>

#include "nocturne/ee/float.hpp"

namespace nocturne::evt {

// evtUnit_t, as far as known (field names follow smt3-decomp's where they
// have them; the rest is unknown).
struct EventUnit {
    uint8_t unknown_00[0x8c];
    uint32_t model;           // the unit's model (mdlObj_t*): +0 its draw flags, +0x12 the motion playing, +0x1C its motion control
    uint32_t linkedUnit;
    uint32_t motionCallback;  // called as the motion runs (a function address; 0 none)
    uint8_t unknown_98[0xc];
    uint32_t flags;           // UnitFlag bits
    int16_t motionState;      // 2: a motion was asked for (tentative)
    uint8_t unknown_aa[4];
    int16_t motionTicks;      // frames into the motion
    uint8_t unknown_b0[4];
    ee::Float waitSpeed;      // the wait (idle) motion's speed
    int16_t waitMotion;       // ... the model's animation for it
    int16_t waitBlendStart;   // ... and its blend frames (tentative)
    int16_t waitBlendEnd;
    int16_t motion;           // the motion asked for: the model's animation
    int16_t motionBlendStart; // ... its blend frames (tentative)
    int16_t motionBlendEnd;
};
static_assert(sizeof(EventUnit) == 0xc4);

namespace UnitFlag {
inline constexpr uint32_t PlayOnce   = 0x000001; // set by motion mode 1 (tentative)
inline constexpr uint32_t Repeat     = 0x000020; // ... mode 0 (tentative)
inline constexpr uint32_t Hold       = 0x000040; // ... mode 3 (tentative)
inline constexpr uint32_t MotionSet  = 0x000080; // a motion was asked for
inline constexpr uint32_t Unknown400000 = 0x400000, Unknown800000 = 0x800000;   // cleared by a new motion
} // namespace UnitFlag

// evtSetUnitMotion (0x1E3CC0): the unit plays the model's animation `motion`,
// blended over the two frame counts; `mode` 0..3 picks how it plays (above;
// 2 none of them, others no flag).
void setUnitMotion(EventUnit& unit, int32_t motion, int32_t blendStart, int32_t blendEnd, int32_t mode);
// evtSetWaitMotion (0x1E3B68), evtSetWaitMotionSpeed (0x1E3B70),
// evtSetWaitHokanFrame (0x1E3B78): the motion it returns to when idle.
void setWaitMotion(EventUnit& unit, int32_t motion);
void setWaitSpeed(EventUnit& unit, ee::Float speed);
void setWaitBlend(EventUnit& unit, int32_t blendStart, int32_t blendEnd);

} // namespace nocturne::evt
