// The battle panel (original unit: nbPanelProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/battle_panel.hpp"

#include <cstdint>

#include "nocturne/address.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kPartyShown = addr(0x0055123d);   // uint8 (gp-relative): the party's panel shown

} // namespace

// nbPanelPartyShow @ 0x00282258 (tentative name: by the HD remaster's order)
void panelPartyShow() { *guest::table<uint8_t>(kPartyShown) = 1; }

// nbPanelPartyHide @ 0x00282268 (tentative name: by the HD remaster's order)
void panelPartyHide() { *guest::table<uint8_t>(kPartyShown) = 0; }

} // namespace nocturne::nb
