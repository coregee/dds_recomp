// The battle camera (original unit: nbCameraProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/camera.hpp"

#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

namespace address {
constexpr uint32_t CameraCurrent = 0x00320e40;      // Camera
constexpr uint32_t CameraStateTable = 0x00320c50;   // CameraStateTable[]
} // namespace address

} // namespace

// nbCameraSetState @ 0x001B1740: a state that restarts (rep, read as a
// signed byte) begins again from 0.
void nbCameraSetState(uint16_t state)
{
    Camera& camera = *guest::table<Camera>(address::CameraCurrent);
    camera.state_change = state;
    if (static_cast<int8_t>(guest::table<CameraStateTable>(address::CameraStateTable)[state].rep))
        camera.state = 0;
}

} // namespace nocturne::nb
