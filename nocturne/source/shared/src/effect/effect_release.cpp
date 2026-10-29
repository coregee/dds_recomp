// The effect library's deletion by kind (dds3EffectDelete and its tables),
// billboards and particles, and the particle effects that hold effect parts.
// Rewritten from the original instructions; a kind's delete not rewritten
// yet runs as original code (guest::callOriginal).
#include "nocturne/effect/particles.hpp"

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

namespace {

// The kinds' tables of functions (each row's first is its delete).
constexpr uint32_t kEffectFamilies = addr(0x00316ef8);   // 48-byte rows, by the effect's family (+0)
constexpr uint32_t kPartKinds = addr(0x0031de48);        // 40-byte rows, by the part's kind (+0, halfword)
constexpr uint32_t kParticleEffectKinds = addr(0x0031df98);   // 40-byte rows, by the effect's kind (+0)
constexpr uint32_t kBillboardKinds = addr(0x00317088);   // 12-byte rows, by the billboard's kind (+0x2C, halfword)
constexpr uint32_t kParticleKinds = addr(0x00317278);    // 12-byte rows, by the particle's kind (+0x140, halfword)

uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }
uint16_t half(uint32_t address) { return *guest::table<uint16_t>(address); }

// A kind's delete from its table, as original code.
void deleteByTable(uint32_t table, uint32_t row, uint32_t kind, uint32_t argument)
{
    guest::callOriginal(word(table + row * kind), argument);
}

} // namespace

// dds3EffectDelete @ 0x0015AB58: an effect (particles, polygons, Magatama
// smoke, a part) by its family, then its handle.
void deleteEffect(uint32_t effect)
{
    deleteByTable(kEffectFamilies, 48, word(effect), word(effect + 8));
    mem::PoolRelease(effect);
}

// dds3EffectPartDelete @ 0x00175A08: an effect part by its kind, then its
// handle.
void deletePart(uint32_t part)
{
    deleteByTable(kPartKinds, 40, half(part), word(part + 4));
    mem::PoolRelease(part);
}

// dds3EffectPCPDelete @ 0x00175FB8: a particle effect by its kind, then its
// handle.
void deleteParticleEffect(uint32_t handle)
{
    deleteByTable(kParticleEffectKinds, 40, word(handle), word(handle + 8));
    mem::PoolRelease(handle);
}

// BillboardFreeTex @ 0x0015B2C8: one user fewer; the last lets the texture
// and its memory go (with a note).
void releaseBillboardTexture(uint32_t resource)
{
    if (--word(resource + 8) != 0)
        return;
    diag::print(diag::Message::BillboardFreeTexture);
    tex::DeferredRelease(word(resource));
    mem::HandleFree(word(resource + 0x40));
}

// dds3BillAnimFreeP2A @ 0x0015CCC8: one user fewer; the last lets each of
// its textures go, then its memory.
void releaseBillboardAnimation(uint32_t animation)
{
    if (--word(animation + 0x14) != 0)
        return;
    diag::print(diag::Message::BillboardFreeAnimation);
    for (int32_t k = 0; k < static_cast<int32_t>(word(animation + 0x10)); ++k)
        releaseBillboardTexture(word(word(animation + 0x18) + 4u * static_cast<uint32_t>(k)));
    mem::HandleFree(word(animation));
}

// dds3Billboard_NormalDelete @ 0x0015C280
void deleteNormalBillboard(uint32_t billboard)
{
    releaseBillboardTexture(word(billboard + 0x30));
    mem::PoolRelease(billboard);
}

// dds3Billboard_P2ADelete @ 0x0015C3D0
void deleteAnimatedBillboard(uint32_t billboard)
{
    releaseBillboardAnimation(word(billboard + 0x30));
    mem::PoolRelease(billboard);
}

// dds3BillboardDelete @ 0x0015CF40: by its kind (0 a plain one, 1 an
// animated one).
void deleteBillboard(uint32_t billboard)
{
    switch (const uint16_t kind = half(billboard + 0x2c)) {
    case 0: deleteNormalBillboard(billboard); break;
    case 1: deleteAnimatedBillboard(billboard); break;
    default: deleteByTable(kBillboardKinds, 12, kind, billboard); break;
    }
}

// dds3Particle_PhysicsDelete @ 0x0015DF40
void deleteParticlePhysics(uint32_t physics) { mem::HandleFree(word(physics)); }

// dds3Particle_BlurDelete @ 0x001644F0
void deleteParticleBlur(uint32_t blur) { mem::HandleFree(word(blur + 0xc)); }

// Eff_ModelTrackPolyListDelete @ 0x001A35B0
void deleteModelTrackPolyList(uint32_t list)
{
    const uint32_t count = word(list + 4);
    for (uint32_t k = 0; k < count; ++k)
        ModelTrackPolyDelete(word(word(list) + 4u * k));
    mem::HandleFree(word(list + 8));
}

// dds3Particle_BasicDelete @ 0x0015E138: what its drawing (+0x30) holds,
// its billboard and its physics.
void deleteParticleBasics(uint32_t particle)
{
    switch (half(particle + 0x30)) {
    case 1: deleteParticleBlur(word(particle + 0x38)); break;           // a blur trail
    case 2: TrackPolyDelete(word(particle + 0x40)); break;              // crossed strips
    case 3: TrackPolyDelete(word(particle + 0x44)); break;              // crossed triangles
    case 4: deleteModelTrackPolyList(word(particle + 0x44)); break;     // track polygons
    default: break;
    }
    deleteBillboard(word(particle + 0xf4));
    deleteParticlePhysics(word(particle + 0xf8));
}

// dds3Particle_SmokeOffsetDelete @ 0x00163060
void deleteSmokeOffsetParticle(uint32_t particle)
{
    mem::HandleFree(word(particle + 0x17c));
    deleteParticleBasics(particle);
    mem::PoolRelease(particle);
}

// dds3Particle_SphereSpiral2Delete @ 0x00163780
void deleteSphereSpiral2Particle(uint32_t particle)
{
    if (word(particle + 0x174))
        mem::HandleFree(word(particle + 0x174));
    deleteParticleBasics(particle);
    mem::PoolRelease(particle);
}

// dds3ParticleDelete @ 0x00164BD8
// dds3ParticleExpDelete @ 0x00165180
// A particle effect (of the engine's) by its kind (+0x140).
void deleteParticle(uint32_t particle) { deleteByTable(kParticleKinds, 12, half(particle + 0x140), particle); }

// effPCPHamaCardSpiralDelete @ 0x00183CF8
void deleteHamaCardSpiral(uint32_t effect)
{
    if (word(effect + 0x90)) {
        const uint32_t count = word(effect + 0x88);
        for (uint32_t k = 0; k < count; ++k)
            deletePart(word(word(effect + 0x8c) + 4u * k));
        mem::HandleFree(word(effect + 0x90));
    }
    deleteScatterPolyList(word(effect + 0x80));
    mem::HandleFree(word(effect + 0x84));
}

// effPCPHamaCardSphereDelete @ 0x00184950
void deleteHamaCardSphere(uint32_t effect)
{
    if (word(effect + 0x80)) {
        const uint32_t count = word(effect + 0x78);
        for (uint32_t k = 0; k < count; ++k)
            deletePart(word(word(effect + 0x7c) + 4u * k));
        mem::HandleFree(word(effect + 0x80));
    }
    deleteScatterPolyList(word(effect + 0x70));
    mem::HandleFree(word(effect + 0x74));
}

// effPCPHama01Delete @ 0x0018A5D8: eight parts and eight pairs.
void deleteHama01(uint32_t effect)
{
    for (uint32_t k = 0; k < 8; ++k) {
        deletePart(word(effect + 0x5c + 4 * k));
        deletePart(word(effect + 0x20 + 8 * k));
        deletePart(word(effect + 0x1c + 8 * k));
    }
    mem::PoolRelease(effect);
}

// effPCPHama02Delete @ 0x0018AAB0: eight pairs of parts.
void deleteHama02(uint32_t effect)
{
    for (uint32_t k = 0; k < 8; ++k) {
        deletePart(word(effect + 0x38 + 8 * k));
        deletePart(word(effect + 0x3c + 8 * k));
    }
    mem::PoolRelease(effect);
}

// effPCPHamaonDelete @ 0x0018AFD8: a part, then four threes.
void deleteHamaon(uint32_t effect)
{
    deletePart(word(effect + 0x18));
    for (uint32_t k = 0; k < 4; ++k)
        for (uint32_t j = 0; j < 3; ++j)
            deletePart(word(effect + 0x1c + 12 * k + 4 * j));
    mem::PoolRelease(effect);
}

// effPCPMHanma01Delete @ 0x0018B430: six pairs of parts.
void deleteMahama01(uint32_t effect)
{
    for (uint32_t k = 0; k < 6; ++k) {
        deletePart(word(effect + 0x18 + 8 * k));
        deletePart(word(effect + 0x1c + 8 * k));
    }
    mem::PoolRelease(effect);
}

// effPCPMudoDelete @ 0x0018B708
void deleteMudo(uint32_t effect)
{
    deletePart(word(effect + 0x134c));
    deletePart(word(effect + 0x1348));
    mem::HandleFree(word(effect + 0x1350));
}

// effPCPHwave01Delete @ 0x0018BBD0
void deleteHwave01(uint32_t effect)
{
    deletePart(word(effect + 0x14));
    deletePart(word(effect + 0x18));
    mem::PoolRelease(effect);
}

// effPCPBreathDelete @ 0x0018FC70
void deleteBreath(uint32_t effect)
{
    if (word(effect + 0x74))
        deleteEffect(word(effect + 0x74));
    mem::PoolRelease(effect);
}

// effPCPAgiraoFireDelete @ 0x001902C8: seven threes of effects.
void deleteAgilaoFire(uint32_t effect)
{
    for (uint32_t k = 0; k < 7; ++k) {
        deleteEffect(word(effect + 0x90 + 4 * k));
        deleteEffect(word(effect + 0x74 + 4 * k));
        deleteEffect(word(effect + 0x58 + 4 * k));
    }
    mem::PoolRelease(effect);
}

// effPCPAgiFireballDelete @ 0x00190BF0: unless it is another's copy
// (+0x108), its head part, five parts, three trails (their parts, so many
// per track, and their memory), five more parts and its tail part.
void deleteAgilaoFireball(uint32_t effect)
{
    if (word(effect + 0x108) == 0) {
        deletePart(word(effect + 0xc0));
        for (uint32_t k = 0; k < 5; ++k)
            deletePart(word(effect + 0xc4 + 4 * k));
        for (uint32_t trail = 0; trail < 3; ++trail) {
            const uint32_t memory = effect + 0xfc + 4 * trail;
            if (word(memory) == 0)
                continue;
            const uint32_t count = word(effect + 0xb4) * word(effect + 0x7c + 4 * trail);   // per track
            for (uint32_t k = 0; k < count; ++k)
                if (const uint32_t part = word(word(effect + 0xd8 + 4 * trail) + 4u * k))
                    deletePart(part);
            mem::HandleFree(word(memory));
        }
        for (uint32_t k = 0; k < 5; ++k)
            deletePart(word(effect + 0xe4 + 4 * k));
        deletePart(word(effect + 0xf8));
    }
    mem::PoolRelease(effect);
}

// effPCPBufuIceDelete @ 0x00192348
void deleteBufuIce(uint32_t effect)
{
    deletePart(word(effect + 0x60));
    mem::PoolRelease(effect);
}

// effPCPBufuraIceDelete @ 0x001925E8
// effPCPBufudnIceDelete @ 0x001928E8
void deleteBufulaIce(uint32_t effect)
{
    deletePart(word(effect + 0x64));
    deletePart(word(effect + 0x60));
    mem::PoolRelease(effect);
}

// effPCPRadiateThunderDelete @ 0x001948E0: its bolts (one every 0x18
// bytes), four parts each, then its memory.
void deleteRadiateThunder(uint32_t effect)
{
    const uint32_t bolts = word(effect + 0x58);
    for (uint32_t k = 0; k < bolts; ++k)
        deleteThunderPoly(word(word(effect + 0x164) + 0x18 * k));
    if (const uint32_t parts = word(effect + 0x174)) {
        for (uint32_t k = 0; k < bolts * 4; ++k)
            if (const uint32_t part = word(parts + 4 * k))
                deletePart(part);
        mem::HandleFree(word(effect + 0x178));
    }
    mem::HandleFree(word(effect + 0x17c));
}

} // namespace nocturne::eff
