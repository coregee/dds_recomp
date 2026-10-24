// Which version of the game this build is (variants/README.md).
//
// The source is US Maniax (SLUS_209.11). Another version builds from the
// same source with its delta from variants/<name>/: files there replace the
// base files of the same path (generated data tables, whole units that
// differ), and smaller differences test kVariant at the point they apply:
//
//     if constexpr (kVariant == Variant::Hardtype) ...
//
// The build defines NOCTURNE_VARIANT (build.cmd: set NOCTURNE_VARIANT=hardtype).
#pragma once

namespace nocturne {

enum class Variant {
    Maniax,     // US Shin Megami Tensei III: Nocturne (Maniax), SLUS_209.11: the base
    Hardtype,   // the fan rebalance "Hardtype" 1.5.1, a patch of US Maniax (the same addresses)
    Chronicle,  // JP Shin Megami Tensei III: Nocturne Maniax Chronicle Edition, SLPM_666.81
    Vanilla,    // JP Shin Megami Tensei III: Nocturne (the first release), SLPM_652.42
};

#ifndef NOCTURNE_VARIANT
#define NOCTURNE_VARIANT Maniax
#endif
inline constexpr Variant kVariant = Variant::NOCTURNE_VARIANT;

} // namespace nocturne
