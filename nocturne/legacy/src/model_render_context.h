#ifndef NOCTURNE_MODEL_RENDER_CONTEXT_H
#define NOCTURNE_MODEL_RENDER_CONTEXT_H
#include <stdint.h>
void ps2RenderConfigureBuffers(uint64_t output,uint64_t count);
void ps2RenderReadDefinition(uint64_t output,uint64_t definition,uint64_t mask);
void ps2RenderComposeNormalBasis(uint64_t basis);
void ps2RenderBuildLighting(uint64_t output,uint64_t context,uint64_t colour0,uint64_t colour1,uint64_t colour2,float blend,float range,float phase);
void ps2RenderUpdateLighting(uint64_t output,uint64_t material,uint64_t colour,float rangeBias,float phaseBias);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveRenderContextAddress(uint32_t address);
#endif
/* Raw QMTC2 after a signed32 MFC1/LUI write preserves the GPR's upper64.
 * These are processor state inputs, not replacement game-function results. */
void EE_RENDER_CONTEXT_WORD_TO_VU(unsigned vf,unsigned gpr,uint32_t bits);
#endif
