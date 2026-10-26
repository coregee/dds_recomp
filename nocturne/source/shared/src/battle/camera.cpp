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
constexpr uint32_t PlayerFormRequest = addr(0x0054f38c);  // uint8 (gp-relative)
constexpr uint32_t ProcessName = addr(0x005345c8);        // "nb_camera"
constexpr uint32_t DrawProcessName = addr(0x005345d8);    // "nb_camera_draw"
constexpr uint32_t Step = addr(0x001b1d78), Shutdown = addr(0x001b2098);   // (no C here yet)
// nbCameraDraw (0x1B2090, returns 0): the 8 bytes before nbCameraShutdown in every
// build (not in the function list, so placed by its neighbour).
constexpr uint32_t DrawStep = Shutdown - 8;
constexpr uint32_t SetAllShot = addr(0x001b6a00);         // nbCameraShot_All_Set (no C here yet)
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

// nbInitCameraProcess @ 0x001B20B8
void startCameraProcess(MainProcessData& main)
{
    const uint32_t process = dds3::StartProcess(address::ProcessName, 0x3fb, 2, 1, address::Step, address::Shutdown, 0);
    dds3::LinkProcess(main.MainProcessID, process);
    main.CameraProcessID = process;
    dds3::LinkProcess(process, dds3::StartProcess(address::DrawProcessName, 0x2b0e, 1, 1, address::DrawStep, 0, 0));
    initCamera();
}

// nbCameraInit @ 0x001B1BD8: every shot set up, and no state.
void initCamera()
{
    guest::callOriginal(address::SetAllShot, address::CameraCurrent);
    Camera& camera = *guest::table<Camera>(address::CameraCurrent);
    camera.state_change = 0;
    camera.state = 0;
    camera.previousState2 = 0;
    camera.previousState = 0;
}

// nbCameraCRSetPlayerFormRequest @ 0x001BA1E8 (name from smt3-decomp)
void requestPlayerFormCamera() { *guest::table<uint8_t>(address::PlayerFormRequest) = 1; }

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
