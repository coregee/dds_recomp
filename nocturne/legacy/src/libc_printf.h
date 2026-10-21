#ifndef NOCTURNE_LIBC_PRINTF_H
#define NOCTURNE_LIBC_PRINTF_H
#include <stdint.h>
/* Variadic arguments occupy original raw64 EE slots, including caller-stack
 * arguments after the seven saved register slots. */
uint64_t ps2LibcPrintf(uint64_t format,...);
#endif
