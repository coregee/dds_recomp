#ifndef NOCTURNE_LIBC_VECTOR_H
#define NOCTURNE_LIBC_VECTOR_H
#include <stdint.h>
uint64_t ps2LibcWriteVectors(uint64_t stream,uint64_t vectors);
uint64_t ps2LibcSprint(uint64_t stream,uint64_t vectors);
uint64_t ps2LibcFormatExponent(uint64_t output,uint64_t exponent,uint64_t marker);
#endif
