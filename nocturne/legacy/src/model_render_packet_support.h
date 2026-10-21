#ifndef NOCTURNE_MODEL_RENDER_PACKET_SUPPORT_H
#define NOCTURNE_MODEL_RENDER_PACKET_SUPPORT_H
#include <stdint.h>
void ps2RenderRelightRecords(uint64_t output,uint64_t count);
void ps2RenderTransformUVRecords(uint64_t output,uint64_t count,uint64_t uv,uint64_t matrix);
void ps2RenderInterpolateClippedUV(uint64_t head);
void ps2RenderInterpolateClippedUVColour(uint64_t head);
void ps2RenderRebuildRecordColours(uint64_t context,uint64_t lighting);
void ps2RenderFillRecordColours(uint64_t context,uint64_t colour);
void ps2RenderInterpolateClippedEdge(uint64_t output,uint64_t first,uint64_t second);
uint64_t ps2RenderFinalizePacket(uint64_t context);
void *nocturneResolveRenderPacketAddress(uint32_t address);
void EE_RENDER_PACKET_LD_TO_VU(unsigned vf,unsigned gpr,uint64_t value);
void EE_RENDER_PACKET_WORD_TO_VU(unsigned vf,unsigned gpr,uint32_t value);
void EE_RENDER_PACKET_CPU_QUAD(unsigned gpr,const uint32_t value[4]);
uint32_t EE_RENDER_PACKET_DIV(uint32_t left,uint32_t right);
#endif
