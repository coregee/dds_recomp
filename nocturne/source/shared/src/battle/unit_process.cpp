// The units' process (original unit: nbUnitProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/unit_process.hpp"

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x00551118);   // "nb_unit"
constexpr uint32_t kDrawName = addr(0x00543768);      // "nb_unitdraw"
constexpr uint32_t kStep = addr(0x0024f0b0), kShutdown = addr(0x0024f368);   // nbUnitProcess2, nbUnitShutdown (no C here yet)
constexpr uint32_t kDraw = addr(0x0024e670);          // nbUnitDrawProcess1 (no C here yet)

} // namespace

// nbInitUnitProcess @ 0x0024F388
void startUnitProcess(MainProcessData& main)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kStep, kShutdown, 0);
    dds3::LinkProcess(main.MainProcessID, process);
    main.UnitProcessID = process;
    dds3::LinkProcess(process, dds3::StartProcess(kDrawName, 0x2b0e, 1, 1, kDraw, 0, 0));
}

} // namespace nocturne::nb
