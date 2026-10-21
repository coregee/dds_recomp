#ifndef NOCTURNE_MATERIAL_CONSTRUCTION_RELEASE_DRAFT_H
#define NOCTURNE_MATERIAL_CONSTRUCTION_RELEASE_DRAFT_H
#include <stdint.h>
void ps2MatSetFiveScalars38(void *material,uint32_t a,uint32_t b,uint32_t c,uint32_t d,uint32_t e);
void ps2MatSetFiveScalars3C(void *material,uint32_t a,uint32_t b,uint32_t c,uint32_t d,uint32_t e);
void ps2MatSetScalars40And44(void *material,uint32_t a,uint32_t b);
void ps2MotionBindMaterialNode(void *node,uint32_t source,uint32_t table,uint32_t index);
uint32_t ps2MotionCreateMaterialFiveWords38Node(uint32_t source,uint32_t index);
uint32_t ps2MotionCreateMaterialFiveWords3CNode(uint32_t source,uint32_t index);
uint32_t ps2MotionCreateMaterialWord18Node(uint32_t source,uint32_t index);
uint32_t ps2PoolAllocateZeroed(int32_t size);
uint32_t ps2ZeroQuadwords(uint32_t address,int32_t count);
void ps2PoolRelease(uint32_t slot);
uint32_t ps2MatCreate(void);
#endif
