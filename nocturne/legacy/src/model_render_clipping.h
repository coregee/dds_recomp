#ifndef NOCTURNE_MODEL_RENDER_CLIPPING_H
#define NOCTURNE_MODEL_RENDER_CLIPPING_H
#include <stdint.h>
void ps2RenderBuildDeferredTriangles(uint64_t context);
void ps2RenderBuildFrontTriangles(uint64_t context);
void ps2RenderBuildBackTriangles(uint64_t context);
void ps2RenderBuildPacket(uint64_t context);
void *nocturneResolveRenderClippingAddress(uint32_t address);
uint32_t nocturneRenderClippingFrameAddress(void);
void EE_RENDER_CLIPPING_CPU_QUAD(unsigned gpr,const uint32_t value[4]);
void EE_RENDER_CLIPPING_LD_TO_VU(unsigned vf,unsigned gpr,uint64_t value);
#endif
