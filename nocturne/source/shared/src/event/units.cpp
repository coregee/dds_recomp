// The event units (original unit: evtUnitManager). Rewritten from the
// original instructions.
#include "nocturne/event/units.hpp"

namespace nocturne::evt {

// evtSetUnitMotion @ 0x001E3CC0
void setUnitMotion(EventUnit& unit, int32_t motion, int32_t blendStart, int32_t blendEnd, int32_t mode)
{
    uint32_t flags = unit.flags & ~(UnitFlag::PlayOnce | UnitFlag::Repeat | UnitFlag::Hold | UnitFlag::Unknown400000 |
                                    UnitFlag::Unknown800000);
    unit.motionState = 2;
    unit.motion = static_cast<int16_t>(motion);
    unit.motionBlendStart = static_cast<int16_t>(blendStart);
    unit.motionBlendEnd = static_cast<int16_t>(blendEnd);
    flags |= UnitFlag::MotionSet;
    unit.motionTicks = 0;
    unit.motionCallback = 0;
    switch (mode) {
    case 0: flags |= UnitFlag::Repeat; break;
    case 1: flags |= UnitFlag::PlayOnce; break;
    case 3: flags |= UnitFlag::Hold; break;
    default: break;
    }
    unit.flags = flags;
}

// evtSetWaitMotion @ 0x001E3B68
void setWaitMotion(EventUnit& unit, int32_t motion) { unit.waitMotion = static_cast<int16_t>(motion); }

// evtSetWaitMotionSpeed @ 0x001E3B70
void setWaitSpeed(EventUnit& unit, ee::Float speed) { unit.waitSpeed = speed; }

// evtSetWaitHokanFrame @ 0x001E3B78
void setWaitBlend(EventUnit& unit, int32_t blendStart, int32_t blendEnd)
{
    unit.waitBlendEnd = static_cast<int16_t>(blendEnd);
    unit.waitBlendStart = static_cast<int16_t>(blendStart);
}

} // namespace nocturne::evt
