// The party's automatic commands (original unit: nbAutoCommProcess).
// Rewritten from the original instructions.
#include "nocturne/battle/auto_command.hpp"

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x005458a0);   // "nb_autocomm"
constexpr uint32_t kStep = addr(0x00289a00);          // nbAutoCommProcess1 (no C here yet)

} // namespace

// nbInitAutoCommProcess @ 0x00289AC8
void startAutoCommandProcess(MainProcessData& main)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x2b0e, 1, 1, kStep, 0, guest::addressOf(&main));
    dds3::LinkProcess(main.MainProcessID, process);
    main.AutoCommProcessID = process;
}

} // namespace nocturne::nb
