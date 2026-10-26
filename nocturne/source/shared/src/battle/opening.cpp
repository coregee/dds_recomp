// The battle's opening (original unit: nbMainProcess's "before" process,
// nb_mae). Rewritten from the original instructions.
#include "nocturne/battle/opening.hpp"

#include "nocturne/address.hpp"
#include "nocturne/build.hpp"
#include "nocturne/battle/event_process.hpp"
#include "nocturne/battle/sound.hpp"
#include "nocturne/effect/cut.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x005510c0);   // "nb_mae"
constexpr uint32_t kRequestStage = addr(0x00249b68), kLoadPacks = addr(0x00249b18), kWaitPacks = addr(0x00249ab0),
                   kLoadMusic = addr(0x00249a88), kWaitMusic = addr(0x00249a58), kPlayMusic = addr(0x00249a38),
                   kEnd = addr(0x00249ba0);
constexpr uint32_t kStageRequest = addr(0x00575350);   // the stage to show (tentative)
constexpr uint32_t kProcessFlags = addr(0x00100f78);   // (no C yet) a process's flags set (1) or cleared (0), by scope
constexpr uint32_t kFlightPackRequest = addr(0x00290c30);   // (no C yet) the flight model's pack requested
constexpr int32_t kFlightEncounter = 0x14d;
constexpr uint32_t kStageHidden = 0x20;                // a process flag: the stage held back while the packs load (tentative)

// dds3 process flags (0x101BF0 sets, 0x101C20 clears; scope 0).
void setProcessFlags(uint32_t process, uint32_t flags) { guest::callOriginal(kProcessFlags, 1, process, flags, 0); }
void clearProcessFlags(uint32_t process, uint32_t flags) { guest::callOriginal(kProcessFlags, 0, process, flags, 0); }

} // namespace

// 0x0024C6C8 (no original name)
void requestStage(int16_t major, int16_t minor)
{
    uint8_t* record = guest::table<uint8_t>(kStageRequest);
    *reinterpret_cast<uint32_t*>(record + 8) = 0x80;
    *reinterpret_cast<int16_t*>(record + 4) = major;
    *reinterpret_cast<int16_t*>(record + 6) = minor;
    record[1] = 2;
    record[0] = 0;
}

// 0x00290B20 (no original name)
void requestFlightPack(MainProcessData& data)
{
    if (data.encno == kFlightEncounter && data.flyh == 0)
        data.flyh = guest::callOriginal(kFlightPackRequest, 0xff);
}

// 0x00290B68 (no original name)
bool flightPackLoaded(MainProcessData& data)
{
    if (data.encno != kFlightEncounter)
        return true;
    if (kBuild.vanilla) {   // (the first release loads it as a plain file)
        if (!file::CheckEnd(data.flyh))
            return false;
        data.flymem = file::GetMemHandle(data.flyh);
        file::RequestRelease(data.flyh);
    } else {
        if (!file::PacCheckEnd(data.flyh))
            return false;
        data.flymem = *guest::table<const uint32_t>(*guest::table<const uint32_t>(data.flyh + 0x60) + 8);
        file::PacRequestFree(data.flyh);
    }
    data.flyh = 0;
    return true;
}

// 0x00249BC0 (no original name)
void startOpening(MainProcessData& data)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kRequestStage, kEnd, 0);
    dds3::LinkProcess(data.MainProcessID, process);
    data.BeforeProcessID = process;
}

// 0x00249BA0 (no original name)
void endOpening(uint32_t) { GetMainProcessData()->BeforeProcessID = 0; }

// 0x00249B68 (no original name): the stage (from +0x7C, +0x7E) and the effect.
uint32_t openingRequestStage(uint32_t)
{
    const MainProcessData& main = *GetMainProcessData();
    requestStage(main.press4_repel, main.press4_miss);
    eff::startEncounterEffect();
    return kLoadPacks;
}

// 0x00249B18 (no original name): the packs requested, the stage held back.
uint32_t openingLoadPacks(uint32_t)
{
    MainProcessData& main = *GetMainProcessData();
    loadEventPacks(main);
    requestFlightPack(main);
    setProcessFlags(main.StageProcessID, kStageHidden);
    return kWaitPacks;
}

// 0x00249AB0 (no original name): with the packs in, the stage shown.
uint32_t openingWaitPacks(uint32_t)
{
    MainProcessData& main = *GetMainProcessData();
    if (!eventPacksLoaded(main) || !flightPackLoaded(main))
        return 0;
    clearProcessFlags(main.StageProcessID, kStageHidden);
    return kLoadMusic;
}

// 0x00249A88 (no original name)
uint32_t openingLoadMusic(uint32_t)
{
    loadMusic(0);
    return kWaitMusic;
}

// 0x00249A58 (no original name)
uint32_t openingWaitMusic(uint32_t) { return musicLoaded() ? kPlayMusic : 0; }

// 0x00249A38 (no original name)
uint32_t openingPlayMusic(uint32_t)
{
    playMusic();
    return static_cast<uint32_t>(-1);
}

} // namespace nocturne::nb
