#pragma once
#include <stdint.h>
uint64_t ps2ModelBoundsClipMask(uint64_t bounds);
void ps2ModelLoadComposeVuMatrix(uint64_t matrix);
uint64_t ps2ModelWriteNodeMatrixReference(uint64_t node,uint64_t packet,uint64_t frame);
void ps2ModelDrawStoreWord(uint64_t value);
void ps2ModelDrawCacheVector(uint64_t object);
void ps2ModelDrawStoreFloat(float value);
void nocturneModelDrawStoreFloatBits(uint64_t value);
void ps2ModelSetDrawSurfaces(uint64_t table,uint64_t first,uint64_t second,uint64_t third,uint64_t fourth);
void ps2ModelInitializeSurfaceCallbacks(uint64_t surface);
void *nocturneResolveModelDrawAddress(uint32_t address);
