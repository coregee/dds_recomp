// The pad as the battle menus read it: a byte per button at 0x2F5830. Bit 7
// is set on the frame the button goes down, bit 1 also while it repeats
// (which bit is which is tentative: bit 7 wraps a cursor around, bit 1
// stops it at the ends).
#pragma once

#include <cstdint>

#include "nocturne/address.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb::pad {

inline constexpr uint32_t kAddress = addr(0x002f5830);

enum Button {
    kPass = 0,         // in the command menu: choose Pass at once
    kConfirm = 1,
    kCancel = 3,
    kLeft = 4,
    kRight = 5,
    kUp = 6,
    kDown = 7,
    kDebugMenu = 10,   // with the debug pad: the battle's debug menu
    kHelpToggle = 13,  // the command menu's help panel on / off (event bit 0xC0E)
};

inline bool pressed(Button b) { return guest::table<const int8_t>(kAddress)[b] < 0; }
inline bool repeating(Button b) { return (guest::table<const uint8_t>(kAddress)[b] & 2) != 0; }

} // namespace nocturne::nb::pad
