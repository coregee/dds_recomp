#ifndef NOCTURNE_EE_FPU_H
#define NOCTURNE_EE_FPU_H
#include <stdint.h>

/* Raw COP1 instruction boundaries, in original operand order. These are
 * processor primitives, not recovered ELF function entries. An EE target
 * implements them with the corresponding hardware instructions; host tests
 * use the separately licensed software value model in tests/ee_fpu_values.c.
 * The host model compares register values only and excludes FCSR effects. */
uint32_t EE_FPU_CVT_S_W(uint32_t signed_word_bits);
uint32_t EE_FPU_CVT_W_S(uint32_t single_bits);
uint32_t EE_FPU_MUL_S(uint32_t left_bits, uint32_t right_bits);
uint32_t EE_FPU_ADD_S(uint32_t left_bits, uint32_t right_bits);
uint32_t EE_FPU_SUB_S(uint32_t left_bits, uint32_t right_bits);
uint32_t EE_FPU_DIV_S(uint32_t left_bits, uint32_t right_bits);
#endif
