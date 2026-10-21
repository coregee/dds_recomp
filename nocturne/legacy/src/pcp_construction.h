#pragma once
#include <stdint.h>
uint64_t ps2PcpDescriptorKind(uint64_t data);
uint64_t ps2PcpDescriptorNumber(uint64_t data);
uint64_t ps2PcpDescriptorPartData(uint64_t data,uint64_t index);
uint64_t ps2PcpDescriptorPartType(uint64_t data,uint64_t index);
uint64_t ps2PcpDescriptorCreatePart(uint64_t data,uint64_t index);
uint64_t ps2PcpWrapperCreate(uint64_t data);
uint64_t ps2PcpType0Create(uint64_t data);
uint64_t ps2PcpType1Create(uint64_t data);
uint64_t ps2PcpType2Create(uint64_t data);
uint64_t ps2PcpType3Create(uint64_t data);
uint64_t ps2PcpType4Create(uint64_t data);
uint64_t ps2PcpType5Create(uint64_t data);
uint64_t ps2PcpType6Create(uint64_t data);
void ps2PolygonFiveColorRiseFall(uint64_t system,uint64_t first,uint64_t second,uint64_t third);
void ps2PolygonSixColorFade(uint64_t system,uint64_t first,uint64_t second,uint64_t third);
void ps2PcpType1InitializeRecord(uint64_t object,uint64_t index);
void ps2PcpType2InitializeRecord(uint64_t object,uint64_t index);
void ps2PcpType3InitializePair(uint64_t object,uint64_t index);
void ps2PcpType4InitializePair(uint64_t object,uint64_t index);
void ps2PcpType5InitializePart(uint64_t object,uint64_t group,uint64_t index);
void ps2PcpType6Reset(uint64_t object);
void ps2ModelChangeMotionSingle(uint64_t context,uint64_t group,uint64_t cut);
uint64_t ps2ModelPartClone(uint64_t context);
uint64_t ps2MaterialBillboardClone(uint64_t source);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolvePcpConstructionAddress(uint32_t address);
uint64_t nocturnePcpConstructorCall(uint32_t target,uint64_t data);
#endif
