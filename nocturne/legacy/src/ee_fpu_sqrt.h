#ifndef NOCTURNE_EE_FPU_SQRT_H
#define NOCTURNE_EE_FPU_SQRT_H
#include <stdint.h>
/* Original EE SQRT.S value boundary. Target execution uses COP1; the separate
 * host value implementation uses the pinned integer PS2Float digit algorithm.
 * Result bits only: FCSR exceptions/sticky flags and timing are not modeled. */
uint32_t EE_FPU_SQRT_S(uint32_t input_bits);
#endif
