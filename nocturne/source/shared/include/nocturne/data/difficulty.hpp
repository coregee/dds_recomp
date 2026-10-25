// The difficulty, as the battle formulas and the field's damage test it.
//
// The Maniax releases set event flag 0xAF2 (EventBit::NormalDifficulty) when
// "Normal" is chosen and play the harder formulas while it's clear. The first
// release has no difficulty menu; the same formulas play harder while its
// flag 0x8A0 is set (what sets it is not yet traced). Its shop has no harder
// prices at all (facility/shop.cpp).
#pragma once

#include "nocturne/build.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/external.hpp"

namespace nocturne::dat {

inline bool isNormalDifficulty()
{
    return kBuild.vanilla ? !evt::BitCheck(EventBit::VanillaHarder) : evt::BitCheck(EventBit::NormalDifficulty);
}

} // namespace nocturne::dat
