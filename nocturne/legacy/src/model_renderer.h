#ifndef NOCTURNE_MODEL_RENDERER_H
#define NOCTURNE_MODEL_RENDERER_H
#include <stdint.h>
#ifndef NOCTURNE_RENDERER_BINDING_API
#define NOCTURNE_RENDERER_BINDING_API
#endif
/* Complete2372-byte original span, with bounded instruction comparisons.
 * Six raw64 integer inputs and two COP1 words; V0 is the finalizer result. */
uint64_t ps2RenderMesh(uint64_t model,uint64_t mesh,uint64_t mask,uint64_t colour,uint64_t frame,uint64_t reverse,float rangeBias,float phaseBias);
NOCTURNE_RENDERER_BINDING_API void *nocturneResolveModelRendererAddress(uint32_t address);
NOCTURNE_RENDERER_BINDING_API uint32_t nocturneModelRendererFrameAddress(void);
void EE_RENDERER_CPU_QUAD(unsigned gpr,const uint32_t words[4]);
void EE_RENDERER_LD_SQ(unsigned gpr,uint64_t low,uint32_t destination);
void EE_RENDERER_DMA_SYNC(void);
void EE_RENDERER_DMA_FINISH(void);
/* Host processor-profile transport. These preserve current CPU upper halves. */
void EE_RENDERER_LD_TO_VU(unsigned vf,unsigned gpr,uint64_t low);
void EE_RENDERER_WORD_TO_VU(unsigned vf,unsigned gpr,uint32_t bits);
#if defined(NOCTURNE_MODEL_RENDERER_PROFILE)
NOCTURNE_RENDERER_BINDING_API extern uint32_t g_modelRendererActive;
#endif
#endif
