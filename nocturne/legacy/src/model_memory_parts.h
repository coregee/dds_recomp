#pragma once
#include <stdint.h>
void ps2ModelBundleLoadMemory(uint64_t group,uint64_t id,uint64_t flags,uint64_t data,uint64_t size);
void ps2PacSetReferenceFlag(uint64_t parser);
uint64_t ps2ModelPartFromBundle(uint64_t blob);
void ps2ModelPartInitialize(uint64_t context);
void ps2ModelSetPositionVu(uint64_t context);
void ps2ModelSetRotationVu(uint64_t context);
void ps2ModelSetScaleVu(uint64_t context);
void ps2ModelSetColor(uint64_t context,uint64_t color);
void ps2ModelSetAttachedColor(uint64_t context,uint64_t color);
void ps2ModelSetEffectColor(uint64_t context,uint64_t node,uint64_t color);
void ps2EffectSetColor(uint64_t effect,uint64_t color);
void ps2BillboardSetColor(uint64_t billboard,uint64_t color);
uint64_t ps2MaterialBillboardCreate(uint64_t source);
void ps2MaterialBillboardSetColor(uint64_t object,uint64_t color);
void ps2ModelPartSetColor(uint64_t object,uint64_t color);
void ps2ParticleSetColor(uint64_t object,uint64_t color);
void ps2ExpParticleSetColor(uint64_t object,uint64_t color);
void ps2SpecialPolygonSetColor(uint64_t object,uint64_t color);
void ps2TrackBundleSetColor(uint64_t object,uint64_t color);
void ps2EffectPartSetColor(uint64_t object,uint64_t color);
void ps2PcpWrapperSetColor(uint64_t object,uint64_t color);
void ps2TrackType2SetColor(uint64_t object,uint64_t color);
void ps2TrackType3SetColor(uint64_t object,uint64_t color);
void ps2TrackType4SetColor(uint64_t object,uint64_t color);
void ps2PcpType0SetColor(uint64_t object,uint64_t color);
void ps2PcpType1SetColor(uint64_t object,uint64_t color);
void ps2PcpType2SetColor(uint64_t object,uint64_t color);
void ps2PcpType3SetColor(uint64_t object,uint64_t color);
void ps2PcpType4SetColor(uint64_t object,uint64_t color);
void ps2PcpType5SetColor(uint64_t object,uint64_t color);
void ps2PcpType6SetColor(uint64_t object,uint64_t color);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelMemoryPartsAddress(uint32_t address);
uint32_t nocturneModelMemoryParserLocal(void *buffer,uint32_t bytes);
void nocturneModelMemoryParserEnd(void);
void nocturneModelMemoryColorCall(uint32_t target,uint64_t object,uint64_t color);
#endif
