// What sets this build of the game apart: its traits (docs/versions.md).
//
// The source reads as JP Maniax, the reference: the release the others
// differ from least. Code that differs by version tests a trait (a
// departure from JP Maniax), not the build's name:
//
//     if constexpr (kBuild.us) ...                 a step that differs
//     #if NOCTURNE_US ... #else ... #endif         whole alternatives, side by side,
//                                                  the reference's in #else
//
// The preprocessor form is for alternatives that name addresses or types
// only some builds have (an addr() key with no counterpart is a compile
// error even in code a build never runs); both forms come from the table
// below. The build defines NOCTURNE_VARIANT (nocturne/variant.hpp).
//
// A declaration marked [version] has an alternative per version in its
// unit's "By version" section.
#pragma once

#include "nocturne/variant.hpp"

// ---- the traits, by build ---------------------------------------------------------------
//
// NOCTURNE_US         the US release and what's built on it: English text and
//                     its font engine, its global work and window layout, its
//                     constants (Hardtype has it too)
// NOCTURNE_VANILLA    the first release (2003): none of what Maniax added
//                     (Dante, Amala, the Fiends; their script commands)
// NOCTURNE_CHRONICLE  the Chronicle Edition's own changes (Raidou, balance)
// NOCTURNE_HARDTYPE   the Hardtype rebalance patch (on the US release)
#define NOCTURNE_US_Us 1
#define NOCTURNE_US_Hardtype 1
#define NOCTURNE_VANILLA_Vanilla 1
#define NOCTURNE_CHRONICLE_Chronicle 1
#define NOCTURNE_HARDTYPE_Hardtype 1

#define NOCTURNE_PASTE2(a, b) a##b
#define NOCTURNE_PASTE(a, b) NOCTURNE_PASTE2(a, b)
// Each is 1 for the builds above, 0 (undefined in #if) for the others.
#define NOCTURNE_US NOCTURNE_PASTE(NOCTURNE_US_, NOCTURNE_VARIANT)
#define NOCTURNE_VANILLA NOCTURNE_PASTE(NOCTURNE_VANILLA_, NOCTURNE_VARIANT)
#define NOCTURNE_CHRONICLE NOCTURNE_PASTE(NOCTURNE_CHRONICLE_, NOCTURNE_VARIANT)
#define NOCTURNE_HARDTYPE NOCTURNE_PASTE(NOCTURNE_HARDTYPE_, NOCTURNE_VARIANT)

namespace nocturne {

struct Build {
    Variant variant;
    bool us;          // NOCTURNE_US
    bool vanilla;     // NOCTURNE_VANILLA
    bool chronicle;   // NOCTURNE_CHRONICLE
    bool hardtype;    // NOCTURNE_HARDTYPE
};

inline constexpr Build kBuild = {
    kVariant,
#if NOCTURNE_US
    true,
#else
    false,
#endif
#if NOCTURNE_VANILLA
    true,
#else
    false,
#endif
#if NOCTURNE_CHRONICLE
    true,
#else
    false,
#endif
#if NOCTURNE_HARDTYPE
    true,
#else
    false,
#endif
};

} // namespace nocturne
