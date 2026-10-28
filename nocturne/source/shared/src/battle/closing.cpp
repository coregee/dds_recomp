// The battle's close (original unit: nbMainProcess's "after" process,
// nb_ato). Rewritten from the original instructions.
#include "nocturne/battle/closing.hpp"

#include "nocturne/address.hpp"
#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/formation.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/battle/sound.hpp"
#include "nocturne/build.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/event/units.hpp"
#include "nocturne/external.hpp"
#include "nocturne/field/next_area.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/kernel/model.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x005510c8);   // "nb_ato"
constexpr uint32_t kStep = addr(0x00249e58), kEnd = addr(0x00249f78);
constexpr uint32_t kWhiteOut = addr(0x00249e00), kDemifiendAlone = addr(0x00249d00), kWithMessage = addr(0x00249c28);
constexpr uint32_t kUnitModelMotion = 0x8c;       // a unit handle's model (as kouka_process.cpp)

// The end types (MainProcessData::endtype) the close tells apart (tentative).
constexpr uint32_t kEndWon = 1, kEndScene = 2, kEndMessage = 6;

Formation& demifiend(MainProcessData& main) { return guest::table<Formation>(main.form.address)[0]; }

void fadeToWhite() { dds3::FadeOut(0xff, 0xff, 0xff, 0x1e); }

} // namespace

// 0x00249F98 (no original name)
void startClosing(MainProcessData& data)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kStep, kEnd, 0);
    dds3::LinkProcess(data.MainProcessID, process);
    data.AfterProcessID = process;
}

// 0x00249F78 (no original name)
void endClosing(uint32_t) { GetMainProcessData()->AfterProcessID = 0; }

// 0x00249E58 (no original name): a win updates the boss rush's record;
// end types 2 and 6 turn the panels off and fade the music, then 6 shows
// a message and 2 the Demi-fiend (unless his model's minor number is set:
// only a white fade). Any other ends after a frame.
uint32_t closingStep(uint32_t process)
{
    MainProcessData& main = *GetMainProcessData();
#if !NOCTURNE_VANILLA   // (the first release has no boss rush)
    if (main.endtype == kEndWon)
        dat::updateBossPressRecord(main.encno, static_cast<int32_t>(main.d31_press_total));
#endif
    if (main.endtype == kEndScene || main.endtype == kEndMessage) {
        PanelSetEnabled(false);
        fadeOutMusic();
    }
    switch (main.endtype) {
    case kEndMessage:
        fld::releaseFieldWork();
        return kWithMessage;
    case kEndScene: {
        fld::releaseFieldWork();
        const uint32_t unit = demifiend(main).hunit;
        return mdl::GetMinorNum(*guest::table<const uint32_t>(unit + kUnitModelMotion)) != 0 ? kWhiteOut : kDemifiendAlone;
    }
    default:
        return dds3::GetRunTime(process) != 0 ? static_cast<uint32_t>(-1) : 0;
    }
}

// 0x00249E00 (no original name)
uint32_t closingWhiteOut(uint32_t process)
{
    const int32_t frame = dds3::GetRunTime(process);
    if (frame == 10)
        fadeToWhite();
    return frame == 40 ? static_cast<uint32_t>(-1) : 0;
}

// 0x00249D00 (no original name): at frame 1 the Demi-fiend alone, his
// colour and alpha reset and motion 0x17 playing, the camera on him; 50 a white
// fade; 80 the end.
uint32_t closingDemifiendAlone(uint32_t process)
{
    const int32_t frame = dds3::GetRunTime(process);
    MainProcessData& main = *GetMainProcessData();
    if (frame == 1) {
        Formation& form = demifiend(main);
        showOnly(form);
        UnitSetColor(form.hunit, 0, 0x80808080);
        UnitSetAlpha(form.hunit, 0, 0x80808080);
        const uint32_t model = *guest::table<const uint32_t>(form.hunit + kUnitModelMotion);
        *guest::table<uint32_t>(*guest::table<const uint32_t>(model + 0x1c) + 0x20) = 0x3f800000;   // its motion speed 1.0
        evt::setUnitMotion(*guest::table<evt::EventUnit>(form.hunit), 0x17, 0, 0, 2);
        cameraOnObstructor(form);
        return 0;
    }
    if (frame == 50)
        fadeToWhite();
    return frame == 80 ? static_cast<uint32_t>(-1) : 0;
}

// 0x00249C28 (no original name): frame 10 the camera (state 20); 30 the
// status line's message 0x3A naming the Demi-fiend; 70 a white fade; 100
// the end.
uint32_t closingWithMessage(uint32_t process)
{
    const int32_t frame = dds3::GetRunTime(process);
    MainProcessData& main = *GetMainProcessData();
    switch (frame) {
    case 10:
        setCameraState(0x14);
        return 0;
    case 30:
        setDevilNameVariable(main.statusMessageTable, 0, dat::globalWork().units[0]);
        showHelpMessage(main.statusMessageTable, 0x3a, 1);
        return 0;
    case 70:
        fadeToWhite();
        return 0;
    case 100:
        return static_cast<uint32_t>(-1);
    default:
        return 0;
    }
}

} // namespace nocturne::nb
