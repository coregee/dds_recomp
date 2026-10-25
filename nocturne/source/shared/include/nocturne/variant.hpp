// Which version of the game this build is (docs/versions.md).
//
// Code doesn't test it: where versions differ it tests a trait of the build
// (nocturne/build.hpp).
//
// The build defines NOCTURNE_VARIANT (build.cmd: set NOCTURNE_VARIANT=hardtype).
#pragma once

namespace nocturne {

enum class Variant {
    Maniax,     // JP Shin Megami Tensei III: Nocturne Maniax (Dante, 2004), SLPM_654.62: the reference
    Vanilla,    // JP Shin Megami Tensei III: Nocturne (the first release, 2003), SLPM_652.42
    Chronicle,  // JP Nocturne Maniax Chronicle Edition (Raidou, 2008), SLPM_666.81
    Us,         // US Shin Megami Tensei III: Nocturne (Maniax), SLUS_209.11
    Hardtype,   // the fan rebalance "Hardtype" 1.5.1, a patch of the US release (the same addresses)
};

#ifndef NOCTURNE_VARIANT
#define NOCTURNE_VARIANT Maniax
#endif
inline constexpr Variant kVariant = Variant::NOCTURNE_VARIANT;

} // namespace nocturne
