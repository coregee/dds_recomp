#ifndef NOCTURNE_MODEL_MICRO_SKINNING_H
#define NOCTURNE_MODEL_MICRO_SKINNING_H
#include <stdint.h>
void ps2RenderTransformWeightedVertices(uint64_t output,uint64_t count,uint64_t matrices,uint64_t positions,uint64_t normals);
void ps2RenderAccumulateWeightedVertices(uint64_t output,uint64_t count,uint64_t matrices,uint64_t positions,uint64_t normals);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelMicroSkinningAddress(uint32_t address);
#endif
#endif
