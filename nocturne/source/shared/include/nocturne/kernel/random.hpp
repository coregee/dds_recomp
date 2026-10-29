// The engine's random numbers (original unit: sdfRandom): seeding. The
// draws themselves (sdfGetRandInt ...) are still the original's
// (external.hpp).
#pragma once

#include <cstdint>

namespace nocturne::sdf {

// sdfRandomize (0x2C0C98): seeds a generator's four state words (the
// default generator's, at 0x529BD8, for a `state` of 0).
void randomize(uint32_t state, uint32_t seed);

} // namespace nocturne::sdf
