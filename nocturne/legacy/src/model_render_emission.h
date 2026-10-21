#ifndef NOCTURNE_MODEL_RENDER_EMISSION_H
#define NOCTURNE_MODEL_RENDER_EMISSION_H
#include <stdint.h>
void ps2RenderEmitTexturedTriangles(uint64_t context);
void ps2RenderEmitStateTriangles(uint64_t context,uint64_t state0,uint64_t state1,uint64_t state2,uint64_t state3,uint64_t disable);
void ps2RenderEmitColourTriangles(uint64_t context);
void ps2RenderEmitBaseTriangles(uint64_t context);
void ps2RenderEmitMaterialPass(uint64_t context);
void ps2RenderEmitAuxiliaryPass(uint64_t context);
void ps2RenderEmitAllPasses(uint64_t context);
void *nocturneResolveRenderEmissionAddress(uint32_t address);
uint32_t nocturneRenderEmissionFrameAddress(void);
void EE_RENDER_EMISSION_CPU_QUAD(unsigned gpr,const uint32_t value[4]);
void EE_RENDER_EMISSION_LD_TO_VU(unsigned vf,unsigned gpr,uint64_t value);
void EE_RENDER_EMISSION_WORD_TO_VU(unsigned vf,unsigned gpr,uint32_t value);
#endif
