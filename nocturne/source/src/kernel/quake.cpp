// The screen quake (original unit: dds3KernelDraw).
#include "nocturne/kernel/quake.hpp"

#include "nocturne/guest.hpp"

namespace nocturne::dds3 {

Quake& quake() { return *guest::table<Quake>(0x0054e970); }

// dds3SetQuake @ 0x00104D38
// Shakes the view for `frame` frames (0: until stopped). The vertical range
// is `range` tenths; the horizontal one is 0.4 of it.
void dds3SetQuake(int32_t frame, uint32_t range)
{
    Quake& q = quake();
    if (range == 0) {
        q.dds3QuakeFlag = 0;
        return;
    }
    q.dds3QuakeFlag = 1;
    q.dds3QuakeFrame = static_cast<int16_t>(frame ? frame : -1);
    const uint16_t y = static_cast<uint16_t>(range * 10);
    q.dds3QuakeYRange = y;
    q.dds3QuakeXRange = static_cast<uint16_t>(y * 4 / 10);
}

// dds3StopQuake @ 0x00104D98
void dds3StopQuake() { quake().dds3QuakeFlag = 0; }

} // namespace nocturne::dds3
