#pragma once
#include <stdint.h>
void ps2MagatuhiResetValueSlot(uint64_t work,uint64_t index);
uint64_t ps2MagatuhiValueCreate(uint64_t count,uint64_t history,uint64_t mode,float scale,float t);
uint64_t ps2MagatuhiHistoryOwnerCreate(uint64_t parameters);
void ps2MagatuhiFillColorTable(uint64_t work,uint64_t first,uint64_t second);
uint64_t ps2EffectMathSlotArrayCreate(uint64_t count);
uint64_t ps2MagatuhiSmokeConvCreate(uint64_t parameters);
uint64_t ps2MagatuhiPoint4Create(uint64_t parameters);
uint64_t ps2MagatuhiCylinderCreate(uint64_t parameters);
uint64_t ps2MagatuhiSpiralCreate(uint64_t parameters);
uint64_t ps2MagatuhiSmokeCreate(uint64_t parameters);
uint64_t dds3MagatuhiParCreate(uint64_t kind,uint64_t parameters);
uint64_t dds3MagatuhiParCopy(uint64_t work);
uint64_t dds3EffectCopy(uint64_t work);
uint64_t mdlEffectDupGeneric(uint64_t resource);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveMagatuhiCreationAddress(uint32_t address);
uint64_t nocturneCallMagatuhiFactory(uint32_t target,uint64_t parameters);
uint64_t nocturneCallGenericEffectCopy(uint32_t target,uint64_t object,uint64_t kind);
#endif
