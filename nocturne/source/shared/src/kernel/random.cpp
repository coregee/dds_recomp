// The engine's random numbers: seeding. Rewritten from the original
// instructions.
#include "nocturne/kernel/random.hpp"

#include <bit>

#include "nocturne/address.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::sdf {

namespace {

constexpr uint32_t kDefaultState = addr(0x00529bd8);   // uint32[4]: the default generator

} // namespace

// sdfRandomize @ 0x002C0C98: each word the last one, mixed with a constant
// and turned 8 bits right.
void randomize(uint32_t state, uint32_t seed)
{
    uint32_t* words = guest::table<uint32_t>(state != 0 ? state : kDefaultState);
    words[0] = seed ^ 0x0aed1a0cu;
    words[1] = std::rotr(words[0], 8);
    words[2] = std::rotr(words[1] ^ 0xaa5a02feu, 8);
    words[3] = std::rotr(words[2] ^ 0x11be81c7u, 8);
}

} // namespace nocturne::sdf
