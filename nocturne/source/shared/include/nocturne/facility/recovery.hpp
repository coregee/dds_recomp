// The recovery spring (original unit: fclRecoverCalc): what each treatment
// of a demon in stock costs, and the treatments. Names are the HD
// remaster's.
#pragma once

#include <cstdint>

#include "nocturne/data/records.hpp"

namespace nocturne::fcl {

// The treatments, as the spring's menu asks for them (RCV_ATTR).
enum RecoveryTreatment : uint32_t {
    kRecover = 1,       // HP and MP
    kStatusRecover = 2, // the ailments it cures
    kRevive = 4,
    kAllRecover = 7,
};

// rcvCalcPriceRecover (0x20DBF0): 1 Macca per HP and 2.5 per MP missing (a
// dead demon's HP from the tenth it revives with).
int32_t recoverPrice(const UnitWork& unit);
// rcvCalcPriceStatusRecover (0x20DCC0): 100 for Mute, Poison or Stun.
int32_t statusRecoverPrice(const UnitWork& unit);
// rcvCalcPriceRevive (0x20DCE8): 400 for a dead demon.
int32_t revivePrice(const UnitWork& unit);
// rcvCalcPriceDispel (0x20DD00): 400.
int32_t dispelPrice();
// rcvCalcPriceAllRecover (0x20DD08): the three together.
int32_t allRecoverPrice(const UnitWork& unit);
// rcvCalcPrice (0x20DD50): a treatment's price; -1 for another.
int32_t treatmentPrice(const UnitWork& unit, uint8_t treatment);

// rcvAppRecover (0x20DDD8): full HP and MP. Returns 1.
int32_t recover(UnitWork& unit);
// rcvAppStatusRecover (0x20DE10): Mute, Poison and Stun cured.
void cureStatus(UnitWork& unit);
// rcvAppRevive (0x20DE20): alive again, with a tenth of its HP.
void revive(UnitWork& unit);
// rcvAppDispel (0x20DE70): the curse lifted.
void dispel(UnitWork& unit);
// rcvAppAllRecover (0x20DE80): revived, recovered and cured.
void recoverAll(UnitWork& unit);
// rcvGetDevilAttr (0x20DEB0): the treatments it needs (RecoveryTreatment).
uint32_t neededTreatments(const UnitWork& unit);

} // namespace nocturne::fcl
