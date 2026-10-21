#ifndef NOCTURNE_MODEL_RENDER_STREAMS_H
#define NOCTURNE_MODEL_RENDER_STREAMS_H
#include <stdint.h>
void ps2RenderTransformWeightedPointsOddLoop(uint64_t control,uint64_t count,uint64_t matrix,uint64_t positions);
void ps2RenderAccumulateWeightedPoints(uint64_t output,uint64_t count,uint64_t matrix,uint64_t positions);
void ps2RenderCopyPackedVectors(uint64_t output,uint64_t count,uint64_t vectors);
void ps2RenderCopyPackedVectorPairs(uint64_t output,uint64_t count,uint64_t positions,uint64_t normals);
void ps2RenderBlendPackedVectorPairs(uint64_t output,uint64_t count,uint64_t positions,uint64_t normals,float weight);
void ps2RenderBlendPackedVectors(uint64_t output,uint64_t count,uint64_t vectors,float weight);
void ps2RenderNormalizeNormals(uint64_t output,uint64_t count);
void *nocturneResolveRenderStreamsAddress(uint32_t address);
/* MFC1 writes signed low64 and retains the incoming CPU upper64. */
void EE_RENDER_STREAMS_FLOAT_TO_VU(unsigned vf,unsigned gpr,uint32_t bits);
#endif
