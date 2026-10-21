#ifndef NOCTURNE_SCRIPT_FPU_H
#define NOCTURNE_SCRIPT_FPU_H
#include <stdint.h>
/* Original EE NEG.S primitive. An EE implementation executes NEG.S, including
 * its FCSR cause-flag effects. Host comparisons model only the raw result. */
uint32_t EE_FPU_NEG_S(uint32_t single_bits);
#endif
