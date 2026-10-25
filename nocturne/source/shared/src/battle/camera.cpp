// The battle camera (original unit: nbCameraProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/camera.hpp"

#include "nocturne/address.hpp"
#include "nocturne/effect/cut.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

namespace address {
constexpr uint32_t CameraCurrent = addr(0x00320e40);      // Camera
constexpr uint32_t CameraStateTable = addr(0x00320c50);   // CameraStateTable[]
} // namespace address

} // namespace

// nbCameraSetState @ 0x001B1740: a state that restarts (rep, read as a
// signed byte) begins again from 0.
void setCameraState(uint16_t state)
{
    Camera& camera = *guest::table<Camera>(address::CameraCurrent);
    camera.state_change = state;
    if (static_cast<int8_t>(guest::table<CameraStateTable>(address::CameraStateTable)[state].rep))
        camera.state = 0;
}

// nbCameraSetTaizi @ 0x001B17E0: the talks' camera (state NEGO_TAIZI) on
// two slots facing each other.
void cameraOnPair(const Formation& from, const Formation& to)
{
    eff::BTLSkillSetFormationInfo(from.formindex, 1u << (to.formindex & 31));
    setCameraState(kCameraNegoTaizi);
}

namespace {

uint32_t bit(const Formation& form) { return 1u << (form.formindex & 31); }

void cameraFromInvoker(const Formation& target, uint16_t state)
{
    eff::BTLSkillSetFormationInfo(eff::skillInvoker().formindex, bit(target));
    setCameraState(state);
}

} // namespace

// nbCameraSetBougai @ 0x001B17A0
void cameraOnObstructor(const Formation& target) { cameraFromInvoker(target, kCameraNegoBougai); }

// nbCameraSetTarget @ 0x001B1810
void cameraOnTalkTarget(const Formation& target) { cameraFromInvoker(target, kCameraTalkTarget); }

// nbCameraSetHojo @ 0x001B1850
void cameraOnHelper(const Formation& helper, const Formation& a, const Formation& b)
{
    eff::BTLSkillSetFormationInfo(helper.formindex, bit(a) | bit(b));
    setCameraState(kCameraTalkBuff);
}

// nbCameraSetEveTarget @ 0x001B1888 (no original name)
void cameraOnEventTarget(const Formation& target) { cameraFromInvoker(target, kCameraEveTarget); }

} // namespace nocturne::nb
