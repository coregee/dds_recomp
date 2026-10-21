#pragma once
#include <stdint.h>
uint64_t ps2BillboardTextureResourceCreate(uint64_t texture);
void dds3BillboardBasicInit(uint64_t billboard);
uint64_t ps2BillboardNormalAllocate(uint64_t texture);
uint64_t dds3BillboardP2ACopy(uint64_t source);
void ps2BillboardP2ABindFrame(uint64_t resource,uint64_t index,uint64_t output);
void dds3BillboardP2ASetNumber(uint64_t billboard,uint64_t index);
uint64_t dds3BillboardCopy(uint64_t source);
uint64_t mdlEffectDupBillboard(uint64_t resource);
