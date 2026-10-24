// The kernel's main loop (original unit: dds3KernelMain), as far as
// rewritten: stopping the game's frames for a moment and slow motion (the
// battle's hit stop). The loop itself runs the processes once a frame unless
// stopped. Names are the HD remaster's.
#pragma once

#include <cstdint>

namespace nocturne::dds3 {

// The game's processes skip `frames` frames (the screen keeps drawing).
void stop(int32_t frames);

// Slow motion: the processes run every `period`th frame for `frames` frames.
void slowOn(int32_t period, int32_t frames);

} // namespace nocturne::dds3
