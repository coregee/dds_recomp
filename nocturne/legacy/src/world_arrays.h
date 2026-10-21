#ifndef NOCTURNE_WORLD_ARRAYS_H
#define NOCTURNE_WORLD_ARRAYS_H
#include <stdint.h>
uint64_t dds3GetBasicArrayHandle(uint64_t count);
void dds3FreeBasicArrayHandle(uint64_t handle);
void dds3DeleteBasicArray(uint64_t handle);
void dds3DeleteAllBasicArray(uint64_t handle);
uint64_t dds3SearchDeleteBasicArray(uint64_t handle,uint64_t basic,uint64_t mode);
uint64_t dds3SetSearchNextBasicArray(uint64_t handle,uint64_t basic);
uint64_t dds3AddBasicArray(uint64_t handle,uint64_t count);
uint64_t dds3GetBasicArrayCount(uint64_t handle);
uint64_t dds3SetBasicArray(uint64_t handle,uint64_t basic);
uint64_t dds3GetBasicArray(uint64_t handle);
uint64_t dds3SetFirstBasicArray(uint64_t handle);
uint64_t dds3SetNextBasicArray(uint64_t handle);
uint64_t dds3ObjectBaseInitControlWorkData(uint64_t basic);
void dds3ObjectBaseOnFlag(uint64_t basic,uint64_t flags);
void dds3ObjectBaseOffFlag(uint64_t basic,uint64_t flags);
uint64_t dds3ObjectBaseCheckFlag(uint64_t basic,uint64_t flags);
uint64_t dds3ObjectBaseBasicTypeToItemType(uint64_t type);
uint64_t dds3ObjectBaseSetControlBasic(uint64_t basic,uint64_t control);
uint64_t dds3ObjectBaseSetControlBasicType(uint64_t basic,uint64_t control,uint64_t type);
void dds3ObjectBaseSetControlBasicSvs(uint64_t basic,uint64_t svs);
uint64_t ps2ObjectBaseGetControlBasicSvs(uint64_t basic);
void dds3MoverBasicFreePath(uint64_t mover);
uint64_t dds3MoverBasicConstructor(uint64_t basic);
#endif
