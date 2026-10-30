// The recovery spring (original unit: fclRecoverCalc). Rewritten from the
// original instructions.
#include "nocturne/facility/recovery.hpp"

#include "nocturne/data/types.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/ee/float.hpp"

namespace nocturne::fcl {

namespace {

// The lasting ailments the spring cures (a demon in stock keeps them).
constexpr uint16_t kCurable = static_cast<uint16_t>(Ailment::Mute) | static_cast<uint16_t>(Ailment::Poison) |
                              static_cast<uint16_t>(Ailment::Stun);
constexpr uint16_t kDead = static_cast<uint16_t>(Ailment::Dead);

bool dead(const UnitWork& unit) { return (unit.badstat & kDead) != 0; }

// The HP a revived demon has: a tenth of its maximum, rounded up.
uint32_t revivedHp(const UnitWork& unit) { return (dat::maxHp(unit) + 9) / 10; }

// An unsigned value as a float, as the compiler converts one: one past
// 2^31 halved (its low bit kept) and doubled.
ee::Float fromUnsigned(uint32_t value)
{
    if (static_cast<int32_t>(value) >= 0)
        return ee::Float::fromInt(static_cast<int32_t>(value));
    const ee::Float half = ee::Float::fromInt(static_cast<int32_t>((value >> 1) | (value & 1)));
    return half + half;
}

} // namespace

// rcvCalcPriceRecover @ 0x0020DBF0
int32_t recoverPrice(const UnitWork& unit)
{
    const uint32_t revived = dead(unit) ? revivedHp(unit) : 0;
    const uint32_t hp = dat::maxHp(unit) - (unit.hp + revived);
    const uint32_t mp = dat::maxMp(unit) - unit.mp;
    const ee::Float price = ee::Float::fromInt(static_cast<int32_t>(hp)) + fromUnsigned(mp) * ee::Float::fromBits(0x40200000);   // 2.5
    return price.toInt();
}

// rcvCalcPriceStatusRecover @ 0x0020DCC0
int32_t statusRecoverPrice(const UnitWork& unit) { return (unit.badstat & kCurable) ? 100 : 0; }

// rcvCalcPriceRevive @ 0x0020DCE8
int32_t revivePrice(const UnitWork& unit) { return dead(unit) ? 400 : 0; }

// rcvCalcPriceDispel @ 0x0020DD00
int32_t dispelPrice() { return 400; }

// rcvCalcPriceAllRecover @ 0x0020DD08
int32_t allRecoverPrice(const UnitWork& unit)
{
    const uint32_t recovering = static_cast<uint32_t>(recoverPrice(unit)) + static_cast<uint32_t>(statusRecoverPrice(unit));
    return static_cast<int32_t>(recovering + static_cast<uint32_t>(revivePrice(unit)));
}

// rcvCalcPrice @ 0x0020DD50
int32_t treatmentPrice(const UnitWork& unit, uint8_t treatment)
{
    switch (treatment) {
    case kRecover: return recoverPrice(unit);
    case kStatusRecover: return statusRecoverPrice(unit);
    case kRevive: return revivePrice(unit);
    case kAllRecover: return allRecoverPrice(unit);
    default: return -1;
    }
}

// rcvAppRecover @ 0x0020DDD8
int32_t recover(UnitWork& unit)
{
    unit.hp = static_cast<uint16_t>(dat::maxHp(unit));
    unit.mp = static_cast<uint16_t>(dat::maxMp(unit));
    return 1;
}

// rcvAppStatusRecover @ 0x0020DE10
void cureStatus(UnitWork& unit) { unit.badstat = static_cast<uint16_t>(unit.badstat & ~kCurable); }

// rcvAppRevive @ 0x0020DE20
void revive(UnitWork& unit)
{
    unit.badstat = static_cast<uint16_t>(unit.badstat & ~kDead);
    unit.hp = static_cast<uint16_t>(revivedHp(unit));
}

// rcvAppDispel @ 0x0020DE70
void dispel(UnitWork& unit) { unit.badstat = static_cast<uint16_t>(unit.badstat & ~kBadStatCurse); }

// rcvAppAllRecover @ 0x0020DE80
void recoverAll(UnitWork& unit)
{
    revive(unit);
    recover(unit);
    cureStatus(unit);
}

// rcvGetDevilAttr @ 0x0020DEB0
uint32_t neededTreatments(const UnitWork& unit)
{
    const bool hurt = unit.hp < dat::maxHp(unit) || unit.mp < dat::maxMp(unit);
    uint32_t needs = hurt ? kRecover : 0;
    if (unit.badstat & kCurable)
        needs |= kStatusRecover;
    if (dead(unit))
        needs |= kRevive;
    return needs;
}

} // namespace nocturne::fcl
