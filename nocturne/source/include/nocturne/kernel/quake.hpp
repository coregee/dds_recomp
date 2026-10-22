// The screen quake (original unit: dds3KernelDraw): a shake of the whole
// view for a number of frames, started by the scripts' QUAKE_ON.
#pragma once

#include <cstdint>

namespace nocturne::dds3 {

// The quake state (0x54E970); names are the HD remaster's.
struct Quake {
    uint16_t dds3QuakeFlag;      // shaking
    int16_t dds3QuakeFrame;      // frames left, or -1 until stopped
    uint16_t dds3QuakeXRange;
    uint16_t dds3QuakeYRange;
};
static_assert(sizeof(Quake) == 8);

Quake& quake();

void dds3SetQuake(int32_t frame, uint32_t range);
void dds3StopQuake();

} // namespace nocturne::dds3
