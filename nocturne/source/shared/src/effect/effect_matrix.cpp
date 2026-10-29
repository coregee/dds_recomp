// The effect library's rotation by kind (dds3*SetRotateMatrix): particles and
// polygons turn their own matrix by it, the rest keep it. Rewritten from the
// original instructions; a kind's setter runs from its table as original
// code (guest::callOriginal).
#include "nocturne/effect/particles.hpp"

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

namespace {

constexpr uint32_t kEffectRotation = addr(0x00316f08);     // 48-byte rows, by the effect's family
constexpr uint32_t kPartRotation = addr(0x0031de58);       // 40-byte rows, by the part's kind
constexpr uint32_t kParticleEffectRotation = addr(0x0031dfa8);   // 40-byte rows, by the effect's kind
constexpr uint32_t kMagatamaRotation = addr(0x00320054);   // 24-byte rows, by the Magatama effect's kind

uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }
uint16_t half(uint32_t address) { return *guest::table<uint16_t>(address); }
Matrix& matrix(uint32_t address) { return *guest::table<Matrix>(address); }

void setByTable(uint32_t column, uint32_t row, uint32_t kind, uint32_t handle, uint32_t rotation)
{
    if (const uint32_t setter = word(column + row * kind))
        guest::callOriginal(setter, handle, rotation);
}

// a x b, row by row, as VU0 sums them (sdfMultiplyEffectVuMatrices,
// 0x2B6550: each row's terms in order through the accumulator).
Matrix multiply(const Matrix& a, const Matrix& b)
{
    Matrix out;
    for (int i = 0; i < 4; ++i) {
        const ee::Float scale[4] = {a.row[i].x, a.row[i].y, a.row[i].z, a.row[i].w};
        auto lane = [&](ee::Float dds3::Vector4::*l) {
            ee::Float sum = b.row[0].*l * scale[0];
            for (int j = 1; j < 4; ++j)
                sum = sum + b.row[j].*l * scale[j];
            return sum;
        };
        out.row[i] = {lane(&dds3::Vector4::x), lane(&dds3::Vector4::y), lane(&dds3::Vector4::z), lane(&dds3::Vector4::w)};
    }
    return out;
}

} // namespace

// dds3EffectSetRotateMatrix @ 0x0015ACB8 (no check for an empty column)
void setEffectRotation(uint32_t effect, uint32_t rotation)
{
    guest::callOriginal(word(kEffectRotation + 48 * word(effect)), word(effect + 8), rotation);
}

// dds3P2APolygonSetRotateMatrix @ 0x0015D7E8
void setP2APolygonRotation(uint32_t polygon, uint32_t rotation) { matrix(polygon + 0x40) = matrix(rotation); }

// dds3ParticleSetRotateMatrix @ 0x00164F10
// dds3ParticleExpSetRotateMatrix @ 0x00165590
// Its matrix (+0xB0): its own (+0x100) turned by `rotation`.
void setParticleRotation(uint32_t particle, uint32_t rotation)
{
    matrix(particle + 0xb0) = multiply(matrix(particle + 0x100), matrix(rotation));
}

// dds3SpPolySetRotateMatrix @ 0x00169E90: its matrix (+0x20), its own
// (+0x70) turned by `rotation`.
void setSpPolyRotation(uint32_t polygon, uint32_t rotation)
{
    matrix(polygon + 0x20) = multiply(matrix(polygon + 0x70), matrix(rotation));
}

// dds3EffectPartSetRotateMatrix @ 0x00175B78
void setPartRotation(uint32_t part, uint32_t rotation) { setByTable(kPartRotation, 40, half(part), word(part + 4), rotation); }

// dds3EffectPartModelSetRotateMatrix @ 0x00175EB0: the rotation's first
// three rows into the model's object (+0x20, +0x30, +0x40).
void setPartModelRotation(uint32_t model, uint32_t rotation)
{
    const Matrix m = matrix(rotation);
    for (uint32_t k = 0; k < 3; ++k)
        *guest::table<dds3::Vector4>(word(model + 0x18) + 0x20 + 0x10 * k) = m.row[k];
}

// dds3EffectPCPSetRotateMatrix @ 0x00176160
void setParticleEffectRotation(uint32_t handle, uint32_t rotation)
{
    setByTable(kParticleEffectRotation, 40, word(handle), word(handle + 8), rotation);
}

// effMagaCylinderSetRotateMatrix @ 0x001A7728
// effMagaSpiralSetRotateMatrix @ 0x001A7F78
// effMagaSmokeSetRotateMatrix @ 0x001A88D0
// The Magatama effects keep their rotation at the start of their work.
void setMagatamaEffectRotation(uint32_t effect, uint32_t rotation) { matrix(effect) = matrix(rotation); }

// dds3MagatuhiParSetRotateMatrix @ 0x001A8D20
void setMagatamaRotation(uint32_t handle, uint32_t rotation)
{
    setByTable(kMagatamaRotation, 24, word(handle), word(handle + 4), rotation);
}

} // namespace nocturne::eff
