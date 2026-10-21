#pragma once
#include <stdint.h>
#define EMITTER_KIND_DECL(k) void ps2ParticleKind##k##Reset(uint64_t work);uint64_t ps2ParticleKind##k##Copy(uint64_t source);
EMITTER_KIND_DECL(0) EMITTER_KIND_DECL(1) EMITTER_KIND_DECL(2) EMITTER_KIND_DECL(3)
EMITTER_KIND_DECL(4) EMITTER_KIND_DECL(5) EMITTER_KIND_DECL(6) EMITTER_KIND_DECL(7)
EMITTER_KIND_DECL(8) EMITTER_KIND_DECL(10) EMITTER_KIND_DECL(11) EMITTER_KIND_DECL(12)
#undef EMITTER_KIND_DECL
uint64_t ps2ParticleKind9Copy(uint64_t source);
void ps2ParticleRadiateInitializeSlot(uint64_t work,uint64_t index);
uint64_t dds3ParticleCopy(uint64_t source);
uint64_t dds3ParticleExpCopy(uint64_t source);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveEmitterCopyAddress(uint32_t address);
uint64_t nocturneCallEmitterCopy(uint32_t target,uint64_t source);
void nocturneEmitterCopyFrame(uint32_t object,uint32_t count,unsigned extraAllocation);
void nocturneEmitterCopyObjectInput(uint64_t object);
#endif
