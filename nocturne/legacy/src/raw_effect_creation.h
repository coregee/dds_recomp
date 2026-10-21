#pragma once
#include <stdint.h>
uint64_t dds3ParticleCreate(uint64_t type,uint64_t source);
uint64_t dds3ParticleExpCreate(uint64_t type,uint64_t source);
uint64_t dds3SpPolyCreate(uint64_t type,uint64_t source);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveRawEffectAddress(uint32_t address);
#endif
