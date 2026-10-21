#ifndef NOCTURNE_LIBM_INVERSE_TRANSPORT_H
#define NOCTURNE_LIBM_INVERSE_TRANSPORT_H
#include <stdint.h>
/* ABI-only raw carriers. Float slots use their low32 encodings, return F0 is
 * zero-extended32. Kernel mode retains all64 bits. No arithmetic is done here. */
uint64_t nocturneLibmInverseBits_002CF6B8(uint64_t x);
uint64_t nocturneLibmInverseBits_002CF730(uint64_t x);
uint64_t nocturneLibmInverseBits_002CF748(uint64_t y,uint64_t x);
uint64_t nocturneLibmInverseBits_002CF760(uint64_t x);
uint64_t nocturneLibmInverseBits_002CFB88(uint64_t y,uint64_t x);
uint64_t nocturneLibmInverseBits_002D0118(uint64_t x);
uint64_t nocturneLibmInverseBits_002D0CA8(uint64_t x,uint64_t tail,uint64_t mode);
uint64_t nocturneLibmInverseBits_002D0F30(uint64_t x);
void *nocturneResolveLibmInverseAddress(uint32_t address);
uint32_t nocturneLibmInverseStackPointer(void);
void nocturneLibmInverseSetStackPointer(uint32_t address);
#endif
