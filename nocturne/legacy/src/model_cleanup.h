#ifndef NOCTURNE_MODEL_CLEANUP_H
#define NOCTURNE_MODEL_CLEANUP_H
#include <stdint.h>
uint64_t dds3AreaBasicTypeToItemType(uint64_t type);
void dds3AreaBasicReleaseItem(uint64_t area,uint64_t item);
uint64_t dds3AreaBasicGetItemArray(uint64_t area,uint64_t type);
void mdlFreeBlur(uint64_t handle);
uint64_t mdlGetMajorNum(uint64_t handle);
uint64_t mdlGetMinorNum(uint64_t handle);
uint64_t ps2ModelNeedsSpecialRelease(uint64_t handle);
uint64_t evtDeleteUnitHandle(uint64_t handle);
void ps2MemoryHandleDeferredRelease(uint64_t handle);
void ps2ModelRootRelease(uint64_t root,uint64_t deferred,uint64_t releaseMaterials);
void ps2ModelTextureListRelease(uint64_t list,uint64_t releaseItems);
void ps2MaterialDeferredRelease(uint64_t material);
void sdfMotionNodeFree(uint64_t node);
void sdfMotionCtrlrFree(uint64_t controller);
void ps2MotionNodePoolDestroy(uint64_t node);
/* Execute the selected original destructor through an address adaptation. */
void nocturneCallMotionNodeDestructor(uint32_t entry,uint64_t node);
#endif
