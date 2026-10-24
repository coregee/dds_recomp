// A skill's effect (original unit: effBTL) and its cuts, as far as
// rewritten: the frame queries and setters the battle action uses.
// Creating, running and drawing them is the effect library's part
// (external.hpp).
//
// A skill effect (effBTL_t) holds two cut descriptions, 0x618 bytes apart:
// cut 1 (and 0) and cut 2. A cut (effBTLCutHandle_t, 0x120 bytes) is one
// playing instance of a description. Names are the HD remaster's.
#pragma once

#include <cstdint>

namespace nocturne::nb {
struct Formation;
}

namespace nocturne::eff {

// A playing cut (effBTLCutHandle_t), the fields read here.
struct BattleCut {
    uint32_t pFormation;   // the formation it plays on
    uint32_t effect;       // its effBTL_t
    uint32_t frame;
    uint32_t cutEndFrame;
    uint32_t drawEndFrame; // tentative: when it stops drawing
    uint16_t cutNo;        // which description: 1 (or 0), 2, or a system cut
    uint16_t unknown_16;
    uint32_t stat;
    uint32_t description;  // the description (in the effect) it plays
};

// A description's frames: when the motion changes (the hit) and when it ends.
uint32_t motionChangeFrame(uint32_t effect, uint16_t cutNo);
uint32_t cutEndFrame(uint32_t effect, uint16_t cutNo);

// The same for a playing cut, and the frame it has reached.
uint32_t motionChangeFrame(const BattleCut& cut);
uint32_t cutEndFrame(const BattleCut& cut);
uint32_t frame(const BattleCut& cut);

// Ends the cut at `frame` (a cut 0 also stops drawing there).
void setCutEndFrame(BattleCut& cut, uint32_t frame);

// Stops drawing the cut at `frame` (cut 1 only ever earlier).
void setDrawEndFrame(BattleCut& cut, uint32_t frame);

// A frame of a system cut (effBTLSystemCut1Draw): drawn as any cut.
void drawSystemCut(uint32_t cut);

// The battle camera takes the cut's camera state.
void setCutCameraState(const BattleCut& cut);

// What the skill did to its targets, for the effect (repelled, drained, ...).
void setSkillState(uint32_t state);
// effBTLSkillGetInvokeFormation: the unit using the skill (the battle's
// first formation, with a complaint, when none is).
nb::Formation& skillInvoker();

} // namespace nocturne::eff
