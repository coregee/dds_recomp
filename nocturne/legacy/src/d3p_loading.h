#pragma once
#include <stdint.h>
uint64_t dds3EffectCreate(uint64_t major,uint64_t minor,uint64_t source);
uint64_t dds3EffectLoad(uint64_t descriptor);
void dds3EffectDataRevision(uint64_t descriptor);
uint64_t dds3EffectPartCreate(uint64_t type,uint64_t source);
uint64_t ps2EffectPartBillboardNormalCreate(uint64_t source);
uint64_t ps2EffectPartBillboardAnimationCreate(uint64_t source);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveD3PLoadingAddress(uint32_t address);
uint64_t nocturneCallEffectCreation(uint32_t target,uint64_t type,uint64_t source);
uint64_t nocturneCallEffectPartCreation(uint32_t target,uint64_t source);
#endif
