/* Host-only COP1 value provider. Arithmetic low words use PCSX2/libretro's
 * LGPL-3.0-or-later reference, vendored separately with its license and pin.
 * This adapter is not recovered game code and does not model FCSR flags. */
#include "../src/ee_fpu.h"
#include "../../third_party/ps2float/ps2float.h"

uint32_t EE_FPU_CVT_S_W(uint32_t bits)
{
    uint32_t sign = bits & UINT32_C(0x80000000);
    uint32_t magnitude = sign ? UINT32_C(0) - bits : bits;
    if (magnitude == 0) return 0;
    uint32_t top = 0;
    for (uint32_t value = magnitude; value > 1; value >>= 1) ++top;
    uint32_t significand = top > 23 ? magnitude >> (top - 23)
                                   : magnitude << (23 - top);
    return sign | ((top + 127) << 23) | (significand & UINT32_C(0x007fffff));
}

uint32_t EE_FPU_CVT_W_S(uint32_t bits)
{
    uint32_t sign = bits >> 31;
    uint32_t exponent = (bits >> 23) & 255;
    if (exponent < 127) return 0;
    if (exponent >= 158) return sign ? UINT32_C(0x80000000) : UINT32_C(0x7fffffff);
    uint32_t magnitude = (bits & UINT32_C(0x007fffff)) | UINT32_C(0x00800000);
    if (exponent >= 150) magnitude <<= exponent - 150;
    else magnitude >>= 150 - exponent;
    return sign ? UINT32_C(0) - magnitude : magnitude;
}

uint32_t EE_FPU_ADD_S(uint32_t a, uint32_t b) { return ps2f_raw(ps2f_add(a,b)); }
uint32_t EE_FPU_SUB_S(uint32_t a, uint32_t b) { return ps2f_raw(ps2f_sub(a,b)); }
uint32_t EE_FPU_MUL_S(uint32_t a, uint32_t b) { return ps2f_raw(ps2f_mul(a,b)); }

uint32_t EE_FPU_DIV_S(uint32_t a, uint32_t b) { return ps2f_raw(ps2f_div(a,b)); }
