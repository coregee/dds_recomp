#pragma once
#include <stdint.h>
void ps2PcpWrapperSetPosition(uint64_t object,uint64_t vector);
void ps2PcpWrapperSetDirection(uint64_t object,uint64_t matrix);
void ps2PcpWrapperSetArea(float area,uint64_t object);
void ps2PcpType0SetPosition(uint64_t object,uint64_t vector);
void ps2PcpType1SetPosition(uint64_t object,uint64_t vector);
void ps2PcpType2SetPosition(uint64_t object,uint64_t vector);
void ps2PcpType3SetPosition(uint64_t object,uint64_t vector);
void ps2PcpType4SetPosition(uint64_t object,uint64_t vector);
void ps2PcpType5SetPosition(uint64_t object,uint64_t vector);
void ps2PcpType6SetPosition(uint64_t object,uint64_t vector);
void ps2PcpType3SetScale(float scale,uint64_t object);
void ps2PcpType4SetScale(float scale,uint64_t object);
void ps2PcpType5SetScale(float scale,uint64_t object);
void ps2PcpType6SetScale(float scale,uint64_t object);
void ps2PcpType10SetArea(float area,uint64_t object);
void ps2PcpType13SetArea(float area,uint64_t object);
void ps2PcpType26SetArea(float area,uint64_t object);
void ps2PcpSharedSetArea(float area);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolvePcpControlsAddress(uint32_t address);
void nocturnePcpControlsVectorCall(uint32_t target,uint64_t object,uint64_t vector);
void nocturnePcpControlsFloatCall(uint32_t target,float value,uint64_t object);
#endif
