#ifndef NOCTURNE_MODEL_RENDER_DMA_H
#define NOCTURNE_MODEL_RENDER_DMA_H
#include <stdint.h>
uint64_t ps2RenderConsumeDmaVertices(uint64_t output,uint64_t stream,uint64_t count,uint64_t overhead,uint64_t stride);
void *nocturneResolveRenderDmaAddress(uint32_t address);
/* Processor/device instruction boundaries, not supplied game results. Host
 * validation must execute the original VIF stream and resident VU program. */
void EE_RENDER_DMA_WRITE32(uint32_t address,uint32_t value);
uint32_t EE_RENDER_DMA_READ32(uint32_t address);
void EE_RENDER_DMA_CTC2I(unsigned vi,uint32_t value);
void EE_RENDER_DMA_LQI(unsigned vf,unsigned vi);
void EE_RENDER_DMA_ILWR(unsigned destination,unsigned address_vi,unsigned lane);
uint32_t EE_RENDER_DMA_CFC2(unsigned vi);
void EE_RENDER_DMA_CPU_QUAD(unsigned gpr,const uint32_t value[4]);
void EE_RENDER_DMA_VU_READ(unsigned vf,uint32_t value[4]);
#endif
