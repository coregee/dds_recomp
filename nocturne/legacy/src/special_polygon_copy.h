#pragma once
#include <stdint.h>
uint64_t ps2SpecialPolygonOldRingCopy(uint64_t source);
uint64_t ps2SpecialPolygonRingCopy(uint64_t source);
uint64_t ps2SpecialPolygonRollRingCopy(uint64_t source);
uint64_t ps2SpecialPolygonSphereRingCopy(uint64_t source);
void ps2SpecialPolygonOldRingReset(uint64_t work);
void ps2SpecialPolygonRingReset(uint64_t work);
void ps2SpecialPolygonRollRingReset(uint64_t work);
void ps2SpecialPolygonSphereRingReset(uint64_t work);
uint64_t dds3SpPolyCopy(uint64_t source);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveSpecialPolygonCopyAddress(uint32_t address);
uint64_t nocturneCallSpecialPolygonCopy(uint32_t target,uint64_t source);
#endif
