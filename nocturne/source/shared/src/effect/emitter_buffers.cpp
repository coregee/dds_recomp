// A particle emitter's buffers made ready (dds3Particle_*AllBuffInit): each
// particle's slot (0x40 bytes, from the emitter's physics +4) marked not yet
// born. Rewritten from the original instructions.
#include "nocturne/effect/particles.hpp"

#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

namespace {

constexpr uint32_t kUnborn = 0xf0000001u;   // a particle's age (+0x20) before it starts

uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }

uint32_t slots(uint32_t emitter) { return word(word(emitter + 0xf8) + 4); }
uint32_t count(uint32_t emitter) { return word(emitter + 0x20); }   // (read again for each)

// Each group of so many particles (`group`: the emitter's word there) a step
// (+0x154) later than the last; a group of 0 traps, as the division.
void resetInWaves(uint32_t emitter, uint32_t group)
{
    uint32_t slot = slots(emitter), age = kUnborn;
    for (uint32_t k = 0; k < count(emitter);) {
        word(slot + 0x20) = age;
        slot += 0x40;
        ++k;
        const uint32_t size = word(emitter + group);
        if (size == 0)
            divideByZeroTrap();
        if (k % size == 0)
            age -= word(emitter + 0x154);
    }
}

} // namespace

// dds3Particle_SmokeAllBuffInit @ 0x0015E860
// dds3Particle_SparkAllBuffInit @ 0x0015EEB0
// dds3Particle_SphereSpiralAllBuffInit @ 0x00160048
// dds3Particle_SphereSmokeAllBuffInit @ 0x00160748
// dds3Particle_Spark2AllBuffInit @ 0x001613B0
// dds3Particle_SparkOffsetAllBuffInit @ 0x00162400
// dds3Particle_SmokeOffsetAllBuffInit @ 0x00162F30
// dds3Particle_SphereSpiral2AllBuffInit @ 0x001635A0
void resetParticles(uint32_t emitter)
{
    uint32_t slot = slots(emitter);
    for (uint32_t k = 0; k < count(emitter); ++k, slot += 0x40)
        word(slot + 0x20) = kUnborn;
}

// dds3Particle_SphereAtomAllBuffInit @ 0x00161958: each slot also takes the
// emitter's size (+0x158) at +0x34.
void resetAtomParticles(uint32_t emitter)
{
    uint32_t slot = slots(emitter);
    for (uint32_t k = 0; k < count(emitter); ++k, slot += 0x40) {
        word(slot + 0x20) = kUnborn;
        word(slot + 0x34) = word(emitter + 0x158);
    }
}

// dds3Particle_SpiralAllBuffInit @ 0x0015E1E8: born in waves (each group of
// +0x15C particles a step, +0x154, later than the last).
void resetParticleWaves(uint32_t emitter) { resetInWaves(emitter, 0x15c); }

// dds3Particle_SphereRingAllBuffInit @ 0x00160DF8: the same, its group at
// +0x160.
void resetRingParticleWaves(uint32_t emitter) { resetInWaves(emitter, 0x160); }

} // namespace nocturne::eff
