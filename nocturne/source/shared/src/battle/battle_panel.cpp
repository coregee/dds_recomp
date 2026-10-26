// The battle panel (original unit: nbPanelProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/battle_panel.hpp"

#include <cstddef>
#include <cstdint>
#include <span>

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kPartyShown = addr(0x0055123d);   // uint8 (gp-relative): the party's panel shown
constexpr uint32_t kPressPanel = addr(0x00551190);   // PressPanel (gp-relative)
constexpr uint32_t kTenth = addr(0x0054e5b4);        // float (gp-relative): 0.1 (0x3DCCCCCC)

constexpr uint32_t kProcessName = addr(0x00545488);  // "nb_panel"
constexpr uint32_t kDrawName = addr(0x00545498);
// nbPanelRunProcess (0x282240): not in the function list, so placed by its
// neighbour, nbPanelPartyShow, 0x18 bytes on in every build.
constexpr uint32_t kStep = addr(0x00282258) - 0x18;
constexpr uint32_t kShutdown = addr(0x002828c8), kDraw = addr(0x002827c0);   // nbPanelShutdown, nbPanelDrawProcess (no C here yet)
constexpr uint32_t kDrawOn = addr(0x0055116c);       // uint32 (gp-relative) (HD: nbPnlDrawFlag)
constexpr uint32_t kFrames = addr(0x00551170);       // float (gp-relative): the panel's time, advanced each frame (HD: nbPnlCnt)
constexpr uint32_t kBaseColours = addr(0x00551180);  // uint32[2] (gp-relative) (HD: nbPanelBaseRGBA, nbPanelBaseABGR)
constexpr uint32_t kLayout = addr(0x005753a0);       // PanelLayout[4] (HD: nbPanelLayoutTable2)

// What the start sets up (names from smt3-decomp; no C here yet).
constexpr uint32_t kSetTextures = addr(0x00279708);  // nbPnlTexSet
constexpr uint32_t kStockInit = addr(0x0027fa48);    // nbPanelStockInit
constexpr uint32_t kAnalyzeInit = addr(0x00280508);  // nbPanelAnalyzeInit
constexpr uint32_t kAutoInit = addr(0x00281e38);     // nbPanelAutoInit

// A row of the panel's layout (meanings not known yet).
struct PanelLayout {
    int32_t value[6];
};
static_assert(sizeof(PanelLayout) == 0x18);

static_assert(offsetof(PressPanel, skipNextStart) == 0x1c && offsetof(PressPanel, turnCountRunning) == 0x58 &&
              offsetof(PressPanel, turnCountOnly) == 0x68);

} // namespace

// nbPanelPartyShow @ 0x00282258 (tentative name: by the HD remaster's order)
void panelPartyShow() { *guest::table<uint8_t>(kPartyShown) = 1; }

// nbPanelPartyHide @ 0x00282268 (tentative name: by the HD remaster's order)
void panelPartyHide() { *guest::table<uint8_t>(kPartyShown) = 0; }

PressPanel& pressPanel() { return *guest::table<PressPanel>(kPressPanel); }

// nbInitPanelProcess @ 0x00282900
void startPanelProcess(MainProcessData& main)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kStep, kShutdown, 0);
    dds3::LinkProcess(main.MainProcessID, process);
    main.PanelProcessID = process;
    dds3::LinkProcess(process, dds3::StartProcess(kDrawName, 0x2b0e, 1, 1, kDraw, 0, 0));
    guest::callOriginal(kSetTextures, guest::addressOf(&main));
    *guest::table<uint32_t>(kFrames) = 0;
    *guest::table<uint32_t>(kDrawOn) = 1;
    for (PanelLayout& row : std::span(guest::table<PanelLayout>(kLayout), 4))
        row = PanelLayout{{0, 0, -1, -1, 0, 0}};
    initPressPanel();
    initPressGauge();
    guest::callOriginal(kStockInit);
    guest::callOriginal(kAnalyzeInit);
    guest::callOriginal(kAutoInit);
    PanelAllShow();
    guest::table<uint32_t>(kBaseColours)[1] = 0x80808080;
    guest::table<uint32_t>(kBaseColours)[0] = 0x80808080;
}

// nbPanelPressTurnInit @ 0x0027D868
void initPressPanel()
{
    PressPanel& p = pressPanel();
    p.turn1Running = 0;
    p.turn2Running = 0;
    p.turn3Running = 0;
    p.turnCountRunning = 0;
    p.icons1Running = 0;
    p.turnCountOnly = 0;
    p.skipNextStart = 0;
}

// nbPanelPressGaugeInit @ 0x0027C230
void initPressGauge()
{
    PressPanel& p = pressPanel();
    p.gaugeShown = 1;
    p.gaugeTurnShown = -1;
    p.gaugeColour = 0x80808080;
    p.gaugeNumber = 0;
    p.gaugeFrame = 0;
    p.gaugeBirthWait = 0;
    p.gaugeStarted = 0;
    p.gaugeEncounter = 0;
    p.gaugeTurn = -1;
}

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
