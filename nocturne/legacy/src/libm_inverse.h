#ifndef NOCTURNE_LIBM_INVERSE_H
#define NOCTURNE_LIBM_INVERSE_H
#include <stdint.h>
/* Ordinary guest RAM and the same provider-owned SP used by imported
 * functions; resolver does not return data-dependent math answers. */
void *nocturneResolveLibmInverseAddress(uint32_t address);
uint32_t nocturneLibmInverseStackPointer(void);
void nocturneLibmInverseSetStackPointer(uint32_t address);
float ps2LibmInverse_002CF6B8(float p0);
float ps2LibmInverse_002CF730(float p0);
float ps2LibmInverse_002CF748(float p0,float p1);
float ps2LibmInverse_002CF760(float p0);
float ps2LibmInverse_002CFB88(float p0,float p1);
float ps2LibmInverse_002D0118(float p0);
float ps2LibmInverse_002D0CA8(float p0,float p1,uint64_t p2);
float ps2LibmInverse_002D0F30(float p0);
/* F12/F13 float carriers preserve raw bits via memcpy; kernel tangent
 * mode is the full raw64 A0 slot, not a float or low-word parameter.
 * FCSR condition uses the existing EE compare primitive. Arithmetic
 * exception flags and full volatile/private-frame equality excluded. */
#endif
