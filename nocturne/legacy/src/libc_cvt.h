#ifndef NOCTURNE_LIBC_CVT_H
#define NOCTURNE_LIBC_CVT_H
#include <stdint.h>
uint64_t ps2LibcCvt(uint64_t context,uint64_t bits,uint64_t precision,
    uint64_t flags,uint64_t signByte,uint64_t decimalPoint,
    uint64_t format,uint64_t length);
#endif
