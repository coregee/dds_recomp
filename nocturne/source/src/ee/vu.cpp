// The VU0's float primitives beyond the COP1 ones (legacy/tests/ee_fpu_values.c),
// from the same PS2 float model (third_party/ps2float).
#include <cstdint>

#include "../../../third_party/ps2float/ps2float.h"

// VRSQRT: Q = a / sqrt(|b|), with the PS2's rounding and no NaN or infinity.
extern "C" uint32_t EE_FPU_RSQRT_S(uint32_t a, uint32_t b) { return ps2f_raw(ps2f_rsqrt(a, b)); }
