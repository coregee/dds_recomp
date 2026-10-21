#ifndef NOCTURNE_MODEL_MATERIAL_UPDATE_H
#define NOCTURNE_MODEL_MATERIAL_UPDATE_H
#include <stdint.h>
void ps2MaterialUpdateList(uint64_t definition,uint64_t frame);
void ps2MaterialUpdateFrame(uint64_t material,uint64_t frame);
void ps2MaterialCopyBase(uint64_t material,uint64_t output);
void ps2MaterialUpdatePrimaryUV(uint64_t material,uint64_t output);
void ps2MaterialUpdateSecondaryUV(uint64_t material,uint64_t output);
void ps2MaterialBuildUVTransform(uint64_t output,uint64_t input);
void *nocturneResolveMaterialUpdateAddress(uint32_t address);
#endif
