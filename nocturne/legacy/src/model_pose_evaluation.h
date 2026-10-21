#pragma once
#include <stdint.h>
void sdfModelMakeLocalTm(uint64_t node);
void ps2ModelNodeBaseSet(uint64_t node,uint64_t definition);
uint64_t sdfModelMakeEarly(uint64_t textures,uint64_t definition);
void sdfModelEvalNode(uint64_t node,uint64_t parentMatrix,uint64_t frame);
void sdfModelEvalTm2(uint64_t root,uint64_t frame);
void sdfModelEvalTm(uint64_t root);
void ps2ModelComposeVuMatrices(void);
void ps2ModelWriteLightingPacket(uint64_t packet);
/* Original COP1 RSQRT.S value boundary; exception flags/timing are separate. */
uint32_t EE_MODEL_CPU_RSQRT(uint32_t numerator,uint32_t denominator);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelPoseAddress(uint32_t address);
#endif
