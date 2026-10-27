// The engine's trigonometry (original unit: sdf's math). Rewritten from the
// original instructions.
#include "nocturne/kernel/math.hpp"

#include "nocturne/address.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::sdf {

namespace {

// The executable's constants (gp-relative), in the order the code uses them.
struct Constants {
    ee::Float turnsPerRadian;      // 1 / (2 pi)
    ee::Float radiansPerTurn;      // 2 pi
    ee::Float sine[5];             // x, x^3, x^5, x^7, x^9
    ee::Float quarterTurn;         // pi / 2
    ee::Float arctangent[3];       // x, x^3, x^5
};
const Constants& constants() { return *guest::table<const Constants>(addr(0x0054e758)); }

const ee::Float kHalf = ee::Float::fromBits(0x3f000000), kQuarter = ee::Float::fromBits(0x3e800000);
const ee::Float kOne = ee::Float::fromBits(0x3f800000);

} // namespace

// sdfSin @ 0x002C0060: the angle in turns, its whole turns dropped, folded
// into -1/4..1/4 of a turn, and back in radians for the polynomial.
ee::Float sine(ee::Float radians)
{
    const Constants& c = constants();
    ee::Float x = radians * c.turnsPerRadian;
    x = x - ee::Float::fromInt(x.toInt());
    if (kHalf < x)
        x = x - kOne;
    else if (x < ee::Float::fromBits(0xbf000000))
        x = x + kOne;
    if (kQuarter < x)
        x = kHalf - x;
    else if (x < ee::Float::fromBits(0xbe800000))
        x = ee::Float::fromBits(0xbf000000) - x;
    x = x * c.radiansPerTurn;
    const ee::Float square = x * x;
    ee::Float result = x * c.sine[0];
    ee::Float power = square * x;
    for (int k = 1; k < 5; ++k) {
        result = result + power * c.sine[k];
        if (k < 4)
            power = power * square;
    }
    return result;
}

// sdfCos @ 0x002C0160
ee::Float cosine(ee::Float radians) { return sine(radians + constants().quarterTurn); }

// sdfAtan @ 0x002C0228
ee::Float arctangent(ee::Float x)
{
    const Constants& c = constants();
    const ee::Float square = x * x;
    const ee::Float first = x * c.arctangent[0];
    const ee::Float cube = square * x;
    return (first + cube * c.arctangent[1]) + (square * cube) * c.arctangent[2];
}

// Mult @ 0x002C0488 (VU0): the vector part through the accumulator (a x b,
// then b a.w, then a b.w), w as a.w b.w less each of a.x b.x, a.y b.y,
// a.z b.z in turn.
dds3::Vector4 quaternionMultiply(const dds3::Vector4& a, const dds3::Vector4& b)
{
    const ee::Float one = ee::Float::fromBits(0x3f800000);   // vf0.w
    const dds3::Vector4 product{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    ee::Float x = a.y * b.z, y = a.z * b.x, z = a.x * b.y;          // VOPMULA
    x = x + b.x * a.w; y = y + b.y * a.w; z = z + b.z * a.w;         // VMADDAw
    x = x + a.x * b.w; y = y + a.y * b.w; z = z + a.z * b.w;         // VMADDAw
    x = x - b.y * a.z; y = y - b.z * a.x; z = z - b.x * a.y;         // VOPMSUB
    ee::Float w = a.w * b.w;
    w = w - one * product.x;
    w = w - one * product.y;
    w = w - one * product.z;
    return {x, y, z, w};
}

} // namespace nocturne::sdf
