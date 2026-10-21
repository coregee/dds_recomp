#pragma once
#include <stdint.h>
uint64_t ps2PcpSpawnOnceCreate(uint64_t descriptor);
uint64_t ps2PcpSpawnOnceCopy(uint64_t source);
void ps2ModelMapPositionRecordToVu(uint64_t root,uint64_t record);
uint64_t ps2ModelMapPositionToVu(uint64_t root,uint64_t index);
void ps2ModelPartSetPosition(uint64_t context,uint64_t vector);
void ps2EffectPartSetPosition(uint64_t part,uint64_t vector);
#if UINTPTR_MAX > UINT32_MAX
void nocturneSpawnOncePositionCall(uint32_t target,uint64_t object,uint64_t vector);
#endif
