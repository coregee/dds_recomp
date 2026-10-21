/* Compiler-support routines recovered from the original SLUS_209.11
 * instructions. Chosen names describe behavior; library/version unconfirmed.
 * Host IEEE operations would alter truncation and subnormal behavior. */
#include "nocturne.h"
#include <limits.h>

/* 002d34a0: class0/1 NaN,2 zero,3 finite,4 infinity. */
uint64_t ps2SoftDoublePack(const ps2SoftDoubleParts *parts)
{
    uint64_t fraction = parts->fraction, exponent = 0;
    if (parts->fpclass < 2) {
        exponent = 0x7ff;
        fraction |= UINT64_C(0x8000000000000);
    } else if (parts->fpclass == 4) {
        exponent = 0x7ff;
        fraction = 0;
    } else if (parts->fpclass == 2 || fraction == 0 || parts->exponent < -1022) {
        fraction = 0;
    } else if (parts->exponent >= 1024) {
        exponent = 0x7ff;
        fraction = 0;
    } else {
        exponent = (uint32_t)(parts->exponent + 1023);
        fraction >>= 8;
    }
    return (fraction & UINT64_C(0xfffffffffffff)) |
           ((exponent & 0x7ff) << 52) | ((uint64_t)parts->sign << 63);
}

/* 002d3578: exponent-zero inputs flush to zero. Only class/sign are written
 * on that branch; preserve exponent, fraction and padding exactly. */
void ps2SoftDoubleUnpack(const uint64_t *bits, ps2SoftDoubleParts *parts)
{
    uint64_t input = *bits, fraction = input & UINT64_C(0xfffffffffffff);
    uint32_t exponent = (uint32_t)(input >> 52) & 0x7ff;
    parts->sign = (uint32_t)(input >> 63);
    if (exponent == 0) {
        parts->fpclass = 2;
    } else if (exponent != 0x7ff) {
        parts->fraction = (fraction << 8) | UINT64_C(0x1000000000000000);
        parts->exponent = (int32_t)exponent - 1023;
        parts->fpclass = 3;
    } else {
        parts->exponent = 1023;
        if (fraction == 0) {
            parts->fraction = UINT64_C(0x1000000000000000);
            parts->fpclass = 4;
        } else {
            parts->fpclass = (fraction & UINT64_C(0x8000000000000)) ? 1 : 0;
            parts->fraction = fraction;
        }
    }
}

/* 002d1b88: signed32 input is sign-extended by the caller's EE ABI. */
uint64_t ps2SoftDoubleFromInt(int32_t value)
{
    ps2SoftDoubleParts parts = {0};
    parts.sign = value < 0;
    if (value == 0) parts.fpclass = 2;
    else {
        parts.fpclass = 3;
        parts.fraction = value < 0 ? 0u - (uint32_t)value : (uint32_t)value;
        parts.exponent = 60;
        while (parts.fraction < UINT64_C(0x1000000000000000)) {
            parts.fraction <<= 1;
            --parts.exponent;
        }
    }
    return ps2SoftDoublePack(&parts);
}

/* 002d1c40: truncate normals; saturate large values/infinity; NaN/zero=>0. */
int32_t ps2SoftDoubleToInt(uint64_t bits)
{
    ps2SoftDoubleParts parts = {0};
    ps2SoftDoubleUnpack(&bits, &parts);
    if (parts.fpclass <= 2) return 0;
    if (parts.fpclass != 4) {
        if (parts.exponent < 0) return 0;
        if (parts.exponent < 31) {
            uint32_t magnitude = (uint32_t)(parts.fraction >> (60 - parts.exponent));
            return (int32_t)(parts.sign ? 0u - magnitude : magnitude);
        }
    }
    return parts.sign ? INT32_MIN : INT32_MAX;
}

/* 002d3398: low64 bits of unsigned product, regardless of input high words. */
uint64_t ps2Mul64(uint64_t left, uint64_t right)
{
    return left * right;
}

/* 002d18b0: 128-bit fractional product via four32-bit limb products.
 * Preserve the original guard-bit normalization; do not add host rounding. */
uint64_t ps2SoftDoubleMul(uint64_t left, uint64_t right)
{
    ps2SoftDoubleParts a = {0}, b = {0}, result = {0};
    ps2SoftDoubleUnpack(&left, &a);
    ps2SoftDoubleUnpack(&right, &b);
    uint32_t sign = a.sign != b.sign;
    if (a.fpclass < 2) { a.sign = sign; return ps2SoftDoublePack(&a); }
    if (b.fpclass < 2) { b.sign = sign; return ps2SoftDoublePack(&b); }
    if ((a.fpclass == 4 && b.fpclass == 2) || (b.fpclass == 4 && a.fpclass == 2))
        /* Immutable original parts at54b460 are all zero; packing makes qNaN. */
        return UINT64_C(0x7ff8000000000000);
    if (a.fpclass == 4 || a.fpclass == 2) { a.sign = sign; return ps2SoftDoublePack(&a); }
    if (b.fpclass == 4 || b.fpclass == 2) { b.sign = sign; return ps2SoftDoublePack(&b); }

    uint64_t p00 = ps2Mul64((uint32_t)b.fraction, (uint32_t)a.fraction);
    uint64_t p10 = ps2Mul64(b.fraction >> 32, (uint32_t)a.fraction);
    uint64_t p01 = ps2Mul64((uint32_t)b.fraction, a.fraction >> 32);
    uint64_t p11 = ps2Mul64(b.fraction >> 32, a.fraction >> 32);
    uint64_t cross = p10 + p01, low = p00 + (cross << 32);
    uint64_t high = ((uint64_t)(cross < p10) << 32) + (low < p00) + (cross >> 32) + p11;
    result.exponent = a.exponent + b.exponent + 4;
    result.sign = sign;
    while (high > UINT64_C(0x1fffffffffffffff)) {
        uint64_t odd = high & 1;
        high >>= 1;
        ++result.exponent;
        if (odd) low = (low >> 1) | UINT64_C(0x8000000000000000);
    }
    while (high < UINT64_C(0x1000000000000000)) {
        high <<= 1;
        --result.exponent;
        if (low & UINT64_C(0x8000000000000000)) high |= 1;
        low <<= 1;
    }
    result.fpclass = 3;
    result.fraction = high;
    return ps2SoftDoublePack(&result);
}

/* 002d1590: return an operand, the output, or immutable invalid-operation
 * parts. Inputs have the normalized fractions produced by unpacking. The
 * zero+zero branch copies all24 bytes; arithmetic leaves padding untouched. */
const ps2SoftDoubleParts *ps2SoftDoubleAddParts(const ps2SoftDoubleParts *left,
    const ps2SoftDoubleParts *right, ps2SoftDoubleParts *output)
{
    static const ps2SoftDoubleParts invalid = {0}; /* Original at0054b460. */
    if (left->fpclass < 2) return left;
    if (right->fpclass < 2) return right;
    if (left->fpclass == 4) {
        if (right->fpclass == 4 && left->sign != right->sign) return &invalid;
        return left;
    }
    if (right->fpclass == 4) return right;
    if (right->fpclass == 2) {
        if (left->fpclass != 2) return left;
        *output = *left;
        output->sign = left->sign & right->sign;
        return output;
    }
    if (left->fpclass == 2) return right;

    int32_t exponent = left->exponent;
    int32_t difference = left->exponent - right->exponent;
    uint64_t a = left->fraction, b = right->fraction;
    if (difference >= 64) b = 0;
    else if (difference <= -64) { a = 0; exponent = right->exponent; }
    else if (difference > 0) {
        while (difference-- > 0) b = (b & 1) | (b >> 1);
    } else {
        while (difference++ < 0) a = (a & 1) | (a >> 1);
        exponent = right->exponent;
    }
    uint64_t fraction;
    if (left->sign == right->sign) {
        fraction = a + b;
        output->sign = left->sign;
    } else {
        /* Normalized magnitudes fit the signed64 subtraction in the ELF. */
        int64_t difference64 = left->sign ? (int64_t)b - (int64_t)a : (int64_t)a - (int64_t)b;
        output->sign = difference64 < 0;
        fraction = difference64 < 0 ? (uint64_t)-difference64 : (uint64_t)difference64;
        while (fraction > 0 && fraction < UINT64_C(0x1000000000000000)) {
            fraction <<= 1;
            --exponent;
        }
    }
    output->fpclass = 3;
    if (fraction > UINT64_C(0x1fffffffffffffff)) {
        fraction = (fraction & 1) | (fraction >> 1);
        ++exponent;
    }
    output->exponent = exponent;
    output->fraction = fraction;
    return output;
}

/* 002d17f0 and002d1848 return the packed bits in V0. */
uint64_t ps2SoftDoubleAdd(uint64_t left, uint64_t right)
{
    ps2SoftDoubleParts a = {0}, b = {0}, output = {0};
    ps2SoftDoubleUnpack(&left, &a);
    ps2SoftDoubleUnpack(&right, &b);
    return ps2SoftDoublePack(ps2SoftDoubleAddParts(&a, &b, &output));
}

uint64_t ps2SoftDoubleSub(uint64_t left, uint64_t right)
{
    ps2SoftDoubleParts a = {0}, b = {0}, output = {0};
    ps2SoftDoubleUnpack(&left, &a);
    ps2SoftDoubleUnpack(&right, &b);
    b.sign ^= 1;
    return ps2SoftDoublePack(ps2SoftDoubleAddParts(&a, &b, &output));
}

/* 002d1d68: negative, zero, NaN=>0; positive overflow/infinity=>UINT32_MAX. */
uint32_t ps2SoftDoubleToUint(uint64_t bits)
{
    ps2SoftDoubleParts parts = {0};
    ps2SoftDoubleUnpack(&bits, &parts);
    if (parts.fpclass <= 2 || parts.sign != 0) return 0;
    if (parts.fpclass == 4 || parts.exponent >= 32) return UINT32_MAX;
    if (parts.exponent < 0) return 0;
    return (uint32_t)(parts.fraction >> (60 - parts.exponent));
}

/* 002d3638: ordered result -1/0/1; either NaN returns1. Zero signs
 * compare equal and unpacking has already flushed subnormal operands. */
int32_t ps2SoftDoubleCompareParts(const ps2SoftDoubleParts *left, const ps2SoftDoubleParts *right)
{
    if (left->fpclass < 2 || right->fpclass < 2) return 1;
    if (left->fpclass == 4) {
        if (right->fpclass == 4) return (int32_t)right->sign - (int32_t)left->sign;
        return left->sign ? -1 : 1;
    }
    if (right->fpclass == 4) return right->sign ? 1 : -1;
    if (left->fpclass == 2) {
        if (right->fpclass == 2) return 0;
        return right->sign ? 1 : -1;
    }
    if (right->fpclass == 2 || left->sign != right->sign) return left->sign ? -1 : 1;
    int32_t order;
    if (left->exponent != right->exponent) order = left->exponent > right->exponent ? 1 : -1;
    else if (left->fraction != right->fraction) order = left->fraction > right->fraction ? 1 : -1;
    else return 0;
    return left->sign ? -order : order;
}

/* 002d1b38: comparison result is returned in the low32 bits of V0. */
int32_t ps2SoftDoubleCompare(uint64_t left, uint64_t right)
{
    ps2SoftDoubleParts a = {0}, b = {0};
    ps2SoftDoubleUnpack(&left, &a);
    ps2SoftDoubleUnpack(&right, &b);
    return ps2SoftDoubleCompareParts(&a, &b);
}
