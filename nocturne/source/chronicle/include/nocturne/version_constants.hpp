// Constants that differ by version: the JP Chronicle Edition's
// (source/maniax/include/nocturne/version_constants.hpp has US Maniax's).
#pragma once

#include <cstddef>
#include <cstdint>

namespace nocturne {

// The global work is 4 bytes shorter before the event bits, so every field
// after sits 4 lower; the block before the options (the entered names'
// bitmaps among it) is shorter still: from the options on, fields sit
// 0x2450 lower (data/records.hpp).
inline constexpr std::size_t kGlobalWorkShift = 4;
inline constexpr std::size_t kGlobalWorkTailShift = 0x2450;

// The music RunSeKouka stops when the event boss's repelled skill 0x107
// ends (an effect MIDI; US Maniax 0x1C070000).
inline constexpr uint32_t kRepelledSkillMusic = 0x1c040000;

} // namespace nocturne
