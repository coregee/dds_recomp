// The press turn camera (original unit: nbCameraPress). Rewritten from the
// original instructions.
#include "nocturne/battle/press_camera.hpp"

#include "nocturne/address.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kRunning = addr(0x0054f394);   // int8 (gp-relative)
constexpr uint32_t kSkip = addr(0x0054f398);      // uint32 (gp-relative): skip the next start
constexpr uint32_t kFrame = addr(0x00551e54);     // uint32 (gp-relative)

// The colour (+0x10) of the camera shot records the turn's side uses: the
// party's at 0x325960, the enemies' at 0x325988 (tentative: read by
// nbCameraShot_AllParty_Set and its kin).
constexpr uint32_t kPartyShotColour = addr(0x00325970);
constexpr uint32_t kEnemyShotColour = addr(0x00325998);
constexpr uint32_t kGrey = 0x00808080, kGreyShown = 0x60808080;

constexpr int32_t kFadeFrames = 3, kFadeEnd = 10, kEnd = 21;

int8_t& running() { return *guest::table<int8_t>(kRunning); }
uint32_t& skip() { return *guest::table<uint32_t>(kSkip); }
uint32_t& frame() { return *guest::table<uint32_t>(kFrame); }

} // namespace

// nbCameraPressProcessRun @ 0x001BA6E0
void runPressCamera()
{
    if (running() == 0)
        return;
    const MainProcessData* main = GetMainProcessData();
    if (main == nullptr)
        return;
    if (frame() < static_cast<uint32_t>(kFadeEnd)) {
        const uint32_t colour = (main->stat & BattleStat::EnemyTurn) ? kEnemyShotColour : kPartyShotColour;
        const int32_t f = static_cast<int32_t>(frame());
        ee::Float rate = ee::Float::fromBits(0x3f800000);
        if (f < kFadeFrames)
            rate = ee::Float::fromInt(f) / ee::Float::fromInt(kFadeFrames);
        else if (kFadeEnd - f < kFadeFrames + 1)
            rate = ee::Float::fromInt(kFadeEnd - f) / ee::Float::fromInt(kFadeFrames);
        *guest::table<uint32_t>(colour) = eff::ColorBlend(kGrey, kGreyShown, rate);
    }
    ++frame();
    if (static_cast<int32_t>(frame()) >= kEnd)
        running() = 0;
}

// nbCameraPressProcessInit @ 0x001BA7D8
void startPressCamera()
{
    if (skip() != 0) {
        running() = 0;
        skip() = 0;
        frame() = 100;
        return;
    }
    frame() = 0;
    running() = 1;
}

// nbCameraPressProcessCheckRun @ 0x001BA808
bool pressCameraRunning() { return running() != 0; }

// nbCameraPressProcessGetFrame @ 0x001BA810
int32_t pressCameraFrame() { return static_cast<int32_t>(frame()); }

// nbCameraPressProcessThrough @ 0x001BA818
void skipNextPressCamera() { skip() = 1; }

} // namespace nocturne::nb
