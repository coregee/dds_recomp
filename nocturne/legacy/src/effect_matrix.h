#pragma once
#include <stdint.h>
void sdfMultiplyEffectVuMatrices(void);
void ps2ParticleSetMatrix(uint64_t object,uint64_t matrix);
void ps2ExpParticleSetMatrix(uint64_t object,uint64_t matrix);
void ps2SpecialPolygonSetMatrix(uint64_t object,uint64_t matrix);
void ps2TrackBundleSetMatrix(uint64_t object,uint64_t matrix);
void ps2TrackType2SetMatrix(uint64_t object,uint64_t matrix);
void ps2TrackType3SetMatrix(uint64_t object,uint64_t matrix);
void ps2TrackType4SetMatrix(uint64_t object,uint64_t matrix);
void ps2EffectPartSetMatrix(uint64_t object,uint64_t matrix);
void ps2ModelPartSetMatrix(uint64_t object,uint64_t matrix);
void ps2PcpWrapperSetMatrix(uint64_t object,uint64_t matrix);
void ps2EffectSetMatrix(uint64_t object,uint64_t matrix);
void ps2MaterialBillboardSetMatrix(uint64_t object,uint64_t matrix);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveEffectMatrixAddress(uint32_t address);
void nocturneEffectMatrixCall(uint32_t target,uint64_t object,uint64_t matrix);
#endif
