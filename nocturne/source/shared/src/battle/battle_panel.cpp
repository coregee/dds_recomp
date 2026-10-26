// The battle panel (original unit: nbPanelProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/battle_panel.hpp"

#include <cstddef>
#include <cstdint>

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kPartyShown = addr(0x0055123d);   // uint8 (gp-relative): the party's panel shown
constexpr uint32_t kPressPanel = addr(0x00551190);   // PressPanel (gp-relative)
constexpr uint32_t kTenth = addr(0x0054e5b4);        // float (gp-relative): 0.1 (0x3DCCCCCC)

static_assert(offsetof(PressPanel, skipNextStart) == 0x1c && offsetof(PressPanel, turnCountRunning) == 0x58 &&
              offsetof(PressPanel, turnCountOnly) == 0x68);

} // namespace

// nbPanelPartyShow @ 0x00282258 (tentative name: by the HD remaster's order)
void panelPartyShow() { *guest::table<uint8_t>(kPartyShown) = 1; }

// nbPanelPartyHide @ 0x00282268 (tentative name: by the HD remaster's order)
void panelPartyHide() { *guest::table<uint8_t>(kPartyShown) = 0; }

PressPanel& pressPanel() { return *guest::table<PressPanel>(kPressPanel); }

// nbPanelPressTurnOmit @ 0x0027D8E0
void skipNextPressPanel() { pressPanel().skipNextStart = 1; }

// nbPanelPressTurnStart @ 0x0027D8F0: the three tracks from their start;
// the turn count's animation only when the turn has changed.
void startPressPanel()
{
    diag::print(diag::Message::PressTurnStart);
    GetMainProcessData();   // (its result unused)
    PressPanel& p = pressPanel();
    if (p.skipNextStart != 0) {
        p.skipNextStart = 0;
        return;
    }
    const ee::Float tenth = *guest::table<const ee::Float>(kTenth);
    p.turn3Rate = tenth;
    p.turn1Running = 1;
    p.turn1Frame = 0;
    p.turn2Running = 1;
    p.turn2Frame = 0;
    p.turn2Rate = tenth;
    p.turn3Running = 1;
    p.turn3Frame = 0;
    p.icons0Frame = 0;
    p.icons0Running = 0;
    p.icons1Frame = 0;
    p.icons1Running = 0;
    if (p.gaugeTurn != p.gaugeTurnShown) {
        p.turnCountRunning = 1;
        p.turnCountFrame = 0;
        p.turnCountOnly = 0;
    }
    p.gaugeTurnShown = p.gaugeTurn;
}

// nbPanelPressGaugeStart @ 0x0027C268
void startPressGauge()
{
    PressPanel& p = pressPanel();
    p.gaugeStarted = 1;
    p.gaugeTurnShown = -1;
    p.gaugeNumber = 0;
    p.gaugeFrame = 0;
    p.gaugeBirthWait = 0;
    p.gaugeTurn = -1;
}

// nbPanelPressGaugeEncountHide @ 0x0027C340
void hidePressGaugeForEncounter()
{
    pressPanel().gaugeShown = 0;
    pressPanel().gaugeEncounter = 1;
}

} // namespace nocturne::nb
