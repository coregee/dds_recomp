#pragma once
#include <stdint.h>
void ps2ResourceRequestInitialize(uint64_t request,uint64_t kind,uint64_t path,uint64_t callback,uint64_t parameter);
uint64_t ps2ResourceReadRequestCreate(uint64_t path,uint64_t high,uint64_t callback,uint64_t parameter);
uint64_t ps2ResourcePacRequestCreate(uint64_t path,uint64_t flag,uint64_t headerCallback,uint64_t callback,uint64_t parameter);
uint64_t ps2ResourcePacRequestRelease(uint64_t request);
uint64_t ps2ResourcePacRequestFree(uint64_t request);
uint64_t ps2ResourceRequestRelease(uint64_t request);
uint64_t ps2ResourceWait(uint64_t request);
uint64_t ps2ResourcePacWait(uint64_t request);
void ps2ModelRemovePending(uint64_t major,uint64_t minor);
uint64_t ps2ModelBuildPrefixedPath(uint64_t destination,uint64_t filename);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveRequestLifecycleAddress(uint32_t address);
#endif
