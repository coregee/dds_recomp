// The battle's close (original unit: nbMainProcess's "after" process,
// nb_ato): by how the battle ended, a boss rush's record, the panels and
// music let go, and for two endings a short scene before the field
// returns. Each step runs a frame and names the next (0 to stay, -1 at the
// end). Names are descriptive.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

void startClosing(MainProcessData& data);   // 0x249F98: as the battle's child (AfterProcessID)
void endClosing(uint32_t process);          // 0x249F78: its shutdown
uint32_t closingStep(uint32_t process);     // 0x249E58: by the end type
uint32_t closingWhiteOut(uint32_t process);       // 0x249E00: frame 10 a white fade, 40 the end
uint32_t closingDemifiendAlone(uint32_t process); // 0x249D00: the Demi-fiend alone, then a white fade
uint32_t closingWithMessage(uint32_t process);    // 0x249C28: a message naming the Demi-fiend, then a white fade

} // namespace nocturne::nb
