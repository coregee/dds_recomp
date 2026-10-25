// Constants that differ by version (US Maniax's; Hardtype keeps them).
// Another version has its own copy of this header
// (source/<version>/include/nocturne/version_constants.hpp).
#pragma once

#include <cstddef>
#include <cstdint>

namespace nocturne {

// How much lower than US Maniax's the global work's fields sit: from the
// event bits on, and from the options on (data/records.hpp).
inline constexpr std::size_t kGlobalWorkShift = 0;
inline constexpr std::size_t kGlobalWorkTailShift = 0;

// The music RunSeKouka stops when the event boss's repelled skill 0x107
// ends (an effect MIDI).
inline constexpr uint32_t kRepelledSkillMusic = 0x1c070000;

} // namespace nocturne
