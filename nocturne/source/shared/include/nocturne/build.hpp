// What sets this build of the game apart: its traits (docs/versions.md).
//
// Code that differs by version tests a trait, not the build's name:
//
//     if constexpr (kBuild.japanese) ...        a step that differs
//     #if NOCTURNE_JAPANESE ... #else ... #endif   whole alternatives, side by side
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
// NOCTURNE_JAPANESE   the JP releases: Japanese text and their font engine,
//                     their global work and window layout, their own addresses
//                     (vanilla's are assumed, not yet checked)
// NOCTURNE_CHRONICLE  the Chronicle Edition's own changes (Raidou, balance)
// NOCTURNE_HARDTYPE   the Hardtype rebalance patch (on the US release)
#define NOCTURNE_JAPANESE_Vanilla 1
#define NOCTURNE_JAPANESE_Maniax 1
#define NOCTURNE_JAPANESE_Chronicle 1
#define NOCTURNE_CHRONICLE_Chronicle 1
#define NOCTURNE_HARDTYPE_Hardtype 1

#define NOCTURNE_PASTE2(a, b) a##b
#define NOCTURNE_PASTE(a, b) NOCTURNE_PASTE2(a, b)
// Each is 1 for the builds above, 0 (undefined in #if) for the others.
#define NOCTURNE_JAPANESE NOCTURNE_PASTE(NOCTURNE_JAPANESE_, NOCTURNE_VARIANT)
#define NOCTURNE_CHRONICLE NOCTURNE_PASTE(NOCTURNE_CHRONICLE_, NOCTURNE_VARIANT)
#define NOCTURNE_HARDTYPE NOCTURNE_PASTE(NOCTURNE_HARDTYPE_, NOCTURNE_VARIANT)

namespace nocturne {

struct Build {
    Variant variant;
    bool japanese;    // NOCTURNE_JAPANESE
    bool chronicle;   // NOCTURNE_CHRONICLE
    bool hardtype;    // NOCTURNE_HARDTYPE
};

inline constexpr Build kBuild = {
    kVariant,
#if NOCTURNE_JAPANESE
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
