/* Routines from SLUS_209.11. Float-facing signatures preserve F12/F0
 * interfaces; operations below use encodings, not host float arithmetic. */
#include "nocturne.h"
#include <string.h>

/* 002d3410: exponent-zero writes only class/sign. Exponent255 is finite,
 * unlike the binary64 unpacker; keep that PS2 behavior for widening. */
void ps2SoftFloatUnpack(const uint32_t *bits, ps2SoftFloatParts *parts)
{
    uint32_t input = *bits, exponent = (input >> 23) & 0xff;
    parts->sign = input >> 31;
    if (exponent == 0) parts->fpclass = 2;
    else {
        parts->exponent = (int32_t)exponent - 127;
        parts->fpclass = 3;
        parts->fraction = ((input & 0x7fffff) << 7) | 0x40000000;
    }
}

/* 002d3758: seven guard bits discarded; exponent128 retains a fraction
 * unless its bit31 is set. There is no class0/1/4 special handling here. */
float ps2SoftFloatPack(const ps2SoftFloatParts *parts)
{
    uint32_t fraction = parts->fraction, exponent = 0;
    if (parts->fpclass == 2 || fraction == 0 || parts->exponent < -126) fraction = 0;
    else if (parts->exponent > 128 || (parts->exponent == 128 && (fraction & 0x80000000))) {
        exponent = 0xff;
        fraction = 0;
    } else {
        exponent = (uint32_t)(parts->exponent + 127);
        fraction >>= 7;
    }
    uint32_t bits = (fraction & 0x7fffff) | ((exponent & 0xff) << 23) | (parts->sign << 31);
    float result;
    memcpy(&result, &bits, sizeof(result));
    return result;
}

/* 002d1ce0: integer A0/A1/A2 and64-bit A3, packed result in V0. */
uint64_t ps2SoftDoublePackFields(uint32_t fpclass, uint32_t sign, int32_t exponent, uint64_t fraction)
{
    ps2SoftDoubleParts parts = {0};
    parts.fpclass = fpclass;
    parts.sign = sign;
    parts.exponent = exponent;
    parts.fraction = fraction;
    return ps2SoftDoublePack(&parts);
}

/* 002d3470: four integer arguments; float result in F0. */
float ps2SoftFloatPackFields(uint32_t fpclass, uint32_t sign, int32_t exponent, uint32_t fraction)
{
    ps2SoftFloatParts parts = {fpclass, sign, exponent, fraction};
    return ps2SoftFloatPack(&parts);
}

/* 002d1550: original SWC1 F12 spills input encoding, then widens the
 * unpacked fraction by30 bits. Exponent-zero values become signed zero. */
uint64_t ps2SoftDoubleFromFloat(float value)
{
    uint32_t bits;
    ps2SoftFloatParts parts = {0};
    memcpy(&bits, &value, sizeof(bits));
    ps2SoftFloatUnpack(&bits, &parts);
    return ps2SoftDoublePackFields(parts.fpclass, parts.sign, parts.exponent, (uint64_t)parts.fraction << 30);
}

/* 002d1d10: take fraction bits30..61 and preserve a sticky low bit
 * before packing. No host double/float cast or rounding is substituted. */
float ps2SoftDoubleToFloat(uint64_t bits)
{
    ps2SoftDoubleParts parts = {0};
    ps2SoftDoubleUnpack(&bits, &parts);
    uint32_t fraction = (uint32_t)(parts.fraction >> 30);
    if (parts.fraction & UINT64_C(0x3fffffff)) fraction |= 1;
    return ps2SoftFloatPackFields(parts.fpclass, parts.sign, parts.exponent, fraction);
}
