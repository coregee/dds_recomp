// The battle's debug tools (original units: nbDebugProcess, and the debug
// pad's part of nbMainProcess), as far as rewritten: the debug menu's
// process start and end, and the pad's toggles.
#pragma once

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbDebugProcessData: the debug menu's state.
struct DebugProcessData {
    Ptr32<MainProcessData> data;
    int32_t seq;              // the menu's page
    uint8_t unknown_08[0xc];
    int32_t formindex;        // the slot the menu works on
    Ptr32<Formation> form;    // ... and its formation
    uint8_t unknown_1c[0x14];
};
static_assert(sizeof(DebugProcessData) == 0x30);

// InitDebugProcessData (0x285308): a cleared record (its address) on the
// first page and slot, the menu's cursor back at the top.
uint32_t newDebugData(MainProcessData& main);
// nbInitDebugProcess (0x285368): the debug menu's process ("nb_debug") under
// the battle's.
void startDebugProcess(MainProcessData& main);
// nbDebugShutdown (0x2852C0): its record released, the battle told.
void shutdownDebugProcess(uint32_t process);

// nbDebugSelect (0x246BF8), each frame with the debug pad: button 8 toggles
// BattleStat::DebugToggle, button 19 the second display (main.debug). On the
// enemies' turn, with event bit 0xC11, two one-in-five chances each of the
// third slot's death cry and a pad shake (a test of the two).
void debugPadToggles(MainProcessData& main);

} // namespace nocturne::nb
