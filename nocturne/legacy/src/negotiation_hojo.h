#ifndef NOCTURNE_NEGOTIATION_HOJO_H
#define NOCTURNE_NEGOTIATION_HOJO_H
#include <stdint.h>
/* Guest pointers and original full64 register arguments. All three define V0. */
uint64_t ps2NegotiationHojoSetAll_0026B1E0(uint64_t context);
uint64_t ps2NegotiationHojoCount_0026B368(uint64_t context);
uint64_t ps2NegotiationHojoSearch_0026B3F8(uint64_t context,uint64_t type);
void *nocturneResolveNegotiationHojoAddress(uint32_t address);
#endif
