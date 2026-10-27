// The battle's debug tools (original units: nbDebugProcess, nbMainProcess).
// Rewritten from the original instructions.
#include "nocturne/battle/debug.hpp"

#include <cstring>

#include "nocturne/address.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x00545728);   // "nb_debug"
constexpr uint32_t kStep = addr(0x00285018);          // nbDebugProcess1 (no C here yet)
constexpr uint32_t kShutdown = addr(0x002852c0);      // nbDebugShutdown (shutdownDebugProcess)
constexpr uint32_t kMenuCursor = addr(0x005512d8);    // int32 (gp-relative): the menu's cursor (menucur)
constexpr uint32_t kPadState = addr(0x002f5810);      // the pad's bytes as the debug tools read them (negative: pressed)
constexpr int32_t kStatToggleButton = 0x28, kDisplayButton = 0x33;   // (byte offsets: buttons 8 and 19 of 0x2F5830)
constexpr int32_t kShakeTestFlag = 0xc11;             // debug event bit: test the death cry and the pad's shake

bool pressed(int32_t button) { return guest::table<const int8_t>(kPadState)[button] < 0; }

// The third slot's death cry and a pad shake, one time in five.
void maybeShake(MainProcessData& main)
{
    if (sdf::GetRandInt(5) != 0)
        return;
    addDeathVoicePacket(0, 0, main.form[2]);
    addPadShockPacket(0, 0, 1, 150, 20);
}

} // namespace

// InitDebugProcessData @ 0x00285308
uint32_t newDebugData(MainProcessData& main)
{
    const uint32_t address = mem::PoolAllocate(sizeof(DebugProcessData));
    std::memset(guest::table<uint8_t>(address), 0, sizeof(DebugProcessData));
    DebugProcessData& d = *guest::table<DebugProcessData>(address);
    d.data.address = guest::addressOf(&main);
    d.seq = 0;
    d.formindex = 0;
    d.form.address = 0;
    *guest::table<int32_t>(kMenuCursor) = 0;
    return address;
}

// nbInitDebugProcess @ 0x00285368
void startDebugProcess(MainProcessData& main)
{
    const uint32_t data = newDebugData(main);
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kStep, kShutdown, data);
    dds3::LinkProcess(main.MainProcessID, process);
    main.DebugProcessID = process;
}

// nbDebugShutdown @ 0x002852C0
void shutdownDebugProcess(uint32_t process)
{
    MainProcessData* main = GetMainProcessData();
    mem::PoolRelease(dds3::GetProcessData(process));
    main->DebugProcessID = 0;
}

// nbDebugSelect @ 0x00246BF8
void debugPadToggles(MainProcessData& main)
{
    if (pressed(kStatToggleButton))
        main.stat ^= BattleStat::DebugToggle;
    if (pressed(kDisplayButton))
        main.debug = static_cast<uint16_t>((main.debug + 1) % 2);
    if (!(main.stat & BattleStat::EnemyTurn) || !evt::BitCheck(kShakeTestFlag))
        return;
    maybeShake(main);
    maybeShake(main);
}

} // namespace nocturne::nb
