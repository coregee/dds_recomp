// The effect library's colours and the particle effects' placement by kind
// (dds3*SetRGBA, dds3EffectPCPSet*), and a model's colour (mdlSetColor).
// Rewritten from the original instructions; a kind's setter runs from its
// table as original code (guest::callOriginal).
#include "nocturne/effect/particles.hpp"

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

namespace {

// The kinds' tables (effect_release.cpp has their deletes): the column of
// the setter each function calls.
constexpr uint32_t kEffectRgba = addr(0x00316f0c);        // 48-byte rows, by the effect's family
constexpr uint32_t kPartColor = addr(0x0031de5c);         // 40-byte rows, by the part's kind
constexpr uint32_t kParticleEffectPosition = addr(0x0031dfa0);   // 40-byte rows, by the effect's kind
constexpr uint32_t kParticleEffectColor = addr(0x0031dfac);
constexpr uint32_t kParticleEffectDirection = addr(0x0031dfb0);
constexpr uint32_t kMagatamaRgba = addr(0x00320050);      // 24-byte rows, by the Magatama effect's kind

uint32_t& word(uint32_t address) { return *guest::table<uint32_t>(address); }
uint16_t half(uint32_t address) { return *guest::table<uint16_t>(address); }

// A kind's setter from its column, as original code; none for an empty one.
void setByTable(uint32_t column, uint32_t row, uint32_t kind, uint32_t handle, uint32_t value)
{
    if (const uint32_t setter = word(column + row * kind))
        guest::callOriginal(setter, handle, value);
}

} // namespace

// dds3EffectSetRGBA @ 0x0015ACF0 (no check for an empty column)
void setEffectRgba(uint32_t effect, uint32_t rgba)
{
    guest::callOriginal(word(kEffectRgba + 48 * word(effect)), word(effect + 8), rgba);
}

// dds3BillboardSetRGBA @ 0x0015D048
void setBillboardRgba(uint32_t billboard, uint32_t rgba) { word(billboard + 0x24) = rgba; }

// dds3P2APolygonSetRGBA @ 0x0015D818
void setP2APolygonRgba(uint32_t polygon, uint32_t rgba) { setBillboardRgba(word(polygon + 0x80), rgba); }

// dds3ParticleSetRGBA @ 0x00164F70
// dds3ParticleExpSetRGBA @ 0x001655A8
void setParticleRgba(uint32_t particle, uint32_t rgba) { word(particle + 0xf0) = rgba; }

// dds3SpPolySetRGBA @ 0x00169EF0
void setSpPolyRgba(uint32_t polygon, uint32_t rgba) { word(polygon + 0x60) = rgba; }

// dds3EffectPartSetColor @ 0x00175BB8
void setPartColor(uint32_t part, uint32_t rgba) { setByTable(kPartColor, 40, half(part), word(part + 4), rgba); }

// dds3EffectPartModelSetColor @ 0x00175EF0
void setPartModelColor(uint32_t model, uint32_t rgba) { setModelColor(model, rgba); }

// dds3EffectPCPSetPosition @ 0x001760E0
void setParticleEffectPosition(uint32_t handle, uint32_t position)
{
    setByTable(kParticleEffectPosition, 40, word(handle), word(handle + 8), position);
}

// dds3EffectPCPSetDirection @ 0x001761A0
void setParticleEffectDirection(uint32_t handle, uint32_t direction)
{
    setByTable(kParticleEffectDirection, 40, word(handle), word(handle + 8), direction);
}

// dds3EffectPCPSetColor @ 0x001761E0
void setParticleEffectColor(uint32_t handle, uint32_t rgba)
{
    setByTable(kParticleEffectColor, 40, word(handle), word(handle + 8), rgba);
}

// effMagaCylinderSetRGBA @ 0x001A7720
void setMagatamaCylinderRgba(uint32_t effect, uint32_t rgba) { word(effect + 0x124) = rgba; }

// effMagaSpiralSetRGBA @ 0x001A7F70
void setMagatamaSpiralRgba(uint32_t effect, uint32_t rgba) { word(effect + 0x128) = rgba; }

// effMagaSmokeSetRGBA @ 0x001A88C8
void setMagatamaSmokeRgba(uint32_t effect, uint32_t rgba) { word(effect + 0x120) = rgba; }

// dds3MagatuhiParSetRGBA @ 0x001A8D60: a Magatama effect by its kind.
void setMagatamaRgba(uint32_t handle, uint32_t rgba) { setByTable(kMagatamaRgba, 24, word(handle), word(handle + 4), rgba); }

// mdlSetEffectColorSub @ 0x001DFCF8: an effect on a model (+4: 0 a
// billboard, 1 an effect, else nothing).
void setModelEffectColor(uint32_t, uint32_t node, uint32_t rgba)
{
    switch (half(node + 4)) {
    case 0: setBillboardRgba(word(node + 8), rgba); break;
    case 1: setEffectRgba(word(node + 8), rgba); break;
    default: break;
    }
}

// mdlSetEffectColor @ 0x001DD7E8: each effect on the model (a list from
// +0x14).
void setModelEffectsColor(uint32_t model, uint32_t rgba)
{
    for (uint32_t node = word(model + 0x14); node != 0; node = word(node))
        setModelEffectColor(model, node, rgba);
}

// mdlSetColor @ 0x001DD840: the model's colour (its object's +0x1C), and its
// effects' in mid grey with the colour's alpha.
void setModelColor(uint32_t model, uint32_t rgba)
{
    word(word(model + 0x18) + 0x1c) = rgba;
    setModelEffectsColor(model, (rgba & 0xff000000u) | 0x00808080u);
}

} // namespace nocturne::eff
