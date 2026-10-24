// The kernel's main loop (original unit: dds3KernelMain): stop and slow
// motion. Rewritten from the original instructions.
#include "nocturne/kernel/main_loop.hpp"

#include "nocturne/guest.hpp"

namespace nocturne::dds3 {

namespace {

// The loop's state (gp-relative words).
constexpr uint32_t kRunCount = 0x0054e804;    // frames run so far (dds3RunCount)
constexpr uint32_t kPauseSign = 0x0054e80c;   // processes stopped
constexpr uint32_t kPauseTime = 0x0054e810;   // ... for this many more frames (0: until resumed)
constexpr uint32_t kSlowSign = 0x0054e814;    // slow motion on
constexpr uint32_t kSlowTime = 0x0054e818;    // ... running every this many frames
constexpr uint32_t kSlowRunCount = 0x0054e81c;   // ... since this run count
constexpr uint32_t kSlowEndCount = 0x0054e820;   // ... for this many frames

uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }

} // namespace

// dds3Stop @ 0x00100448
void stop(int32_t frames)
{
    word(kPauseTime) = static_cast<uint32_t>(frames);
    word(kPauseSign) = 1;
    word(kSlowSign) = 0;
}

// dds3SlowOn @ 0x00100460
void slowOn(int32_t period, int32_t frames)
{
    word(kSlowSign) = 1;
    word(kSlowTime) = static_cast<uint32_t>(period);
    word(kSlowRunCount) = word(kRunCount);
    word(kSlowEndCount) = static_cast<uint32_t>(frames);
    word(kPauseSign) = 0;
    word(kPauseTime) = 0;
}

} // namespace nocturne::dds3
