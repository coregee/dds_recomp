// The battle panel (original unit: nbPanelProcess), as far as rewritten.
// Its drawing is still the original's (external.hpp).
#pragma once

#include <cstdint>

#include "nocturne/ee/float.hpp"

namespace nocturne::nb {

// The party's panel shown or hidden (names by the HD remaster's order,
// tentative).
void panelPartyShow();                 // nbPanelPartyShow
void panelPartyHide();                 // nbPanelPartyHide

// The press turn panel's state (0x551190; HD names from smt3-decomp): the
// gauge of press icons, and the animations that start each side's turn.
struct PressPanel {
    int32_t gaugeNumber;           // (HD: nbPanelPGNumber)
    int32_t gaugeTurn;             // the turn the gauge shows (HD: nbPanelPGTurn)
    int32_t gaugeTurnShown;        // ... when the turn's animation last started (HD: nbPanelPGTurnOld)
    int32_t gaugeFrame;            // (HD: nbPanelPGFrame)
    int32_t gaugeBirthWait;        // (HD: nbPanelPGBirthWait)
    uint8_t gaugeStarted;          // (HD: nbPanelPGStart)
    uint8_t gaugeShown;            // (HD: nbPanelPGShow)
    uint8_t gaugeEncounter;        // hidden for the encounter's opening (HD: nbPanelPGEncount)
    uint8_t unknown_17;
    uint32_t unknown_18;
    int8_t skipNextStart;          // the next turn's start animations skipped (HD: nbPanelPTOmit)
    uint8_t unknown_1d[3];
    int32_t turn1Running, turn1Frame;    // three animation tracks (HD: nbPanelPT_1_Process, _Frame)
    int32_t turn2Running, turn2Frame;
    ee::Float turn2Rate;
    int32_t turn3Running, turn3Frame;
    ee::Float turn3Rate;
    int32_t icons0Frame, icons0Running;  // (HD: nbPanelPTP_0_Frame, _Process)
    uint32_t unknown_48;
    int32_t icons1Frame, icons1Running;  // (HD: nbPanelPTP_1_Frame, _Process)
    uint32_t unknown_54;
    int32_t turnCountRunning, turnCountFrame;   // (HD: nbPanelPTAProcess, nbPanelPTAFrame)
    uint32_t unknown_60, unknown_64;
    uint8_t turnCountOnly;         // (HD: nbPanelPTAOnly)
};
PressPanel& pressPanel();

void skipNextPressPanel();         // nbPanelPressTurnOmit (0x27D8E0)
void startPressPanel();            // nbPanelPressTurnStart (0x27D8F0): the turn's start animations
void startPressGauge();            // nbPanelPressGaugeStart (0x27C268)
void hidePressGaugeForEncounter(); // nbPanelPressGaugeEncountHide (0x27C340)

} // namespace nocturne::nb
