#ifndef NOCTURNE_MODEL_RENDER_CLIP_H
#define NOCTURNE_MODEL_RENDER_CLIP_H
#include <stdint.h>
void ps2RenderLightClipPacked(uint64_t output,uint64_t count,uint64_t positions,uint64_t normals);
void ps2RenderLightClipRecords(uint64_t output,uint64_t count);
void ps2RenderLightClipPackedUV(uint64_t output,uint64_t count,uint64_t positions,uint64_t normals,uint64_t uv,uint64_t transform);
void ps2RenderLightClipRecordsUV(uint64_t output,uint64_t count,uint64_t uv,uint64_t transform);
void *nocturneResolveRenderClipAddress(uint32_t address);
/* CPU LD retains upper64; packed PCPYLD replaces V0 upper64 with Z/sign. */
void EE_RENDER_CLIP_LD_TO_VU(unsigned vf,unsigned gpr,uint64_t low);
void EE_RENDER_CLIP_PACKED_TO_VU(unsigned vf,const uint32_t words[4]);
#endif
