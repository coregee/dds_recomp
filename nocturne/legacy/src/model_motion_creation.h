#pragma once
#include <stdint.h>
uint64_t mdlCreateMotion(uint64_t model,uint64_t group);
uint64_t sdfMotGenNode(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t sdfMotionCtrlrNew(uint64_t model,uint64_t book);
void sdfMotionChangeBlend(uint64_t controller,uint64_t cut,uint64_t type,float lead,float duration);
uint64_t ps2MotionModelFactory(uint64_t controller,uint64_t command,uint64_t argument);
void sdfMotGenModelInit(uint64_t node,uint64_t controller,uint64_t vtable,uint64_t argument);
uint64_t sdfMotGenModelLinerPos(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t sdfMotGenModelLinerRotXYZ(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t sdfMotGenModelLinerScale(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t sdfMotGenModelLerpRotQuat(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t sdfMotGenModelVisible(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t sdfModelSearchNode(uint64_t model,uint64_t index);
uint64_t mdlCreateEffectCtrlr(uint64_t model,uint64_t type,uint64_t group);
uint64_t mdlGetEffectResrc(uint64_t model,uint64_t index);
uint64_t ps2ModelActiveMotionCut(uint64_t model,uint64_t group);
uint64_t ps2ModelResourceFind(uint64_t id);
uint64_t ps2ModelTagFind(uint64_t start,uint64_t tag);
uint64_t ps2ModelRootTagFind(uint64_t root,uint64_t tag);
uint64_t ps2ModelPositionFind(uint64_t root,uint64_t index);
void nocturneMotionChangeBlendBits(uint64_t controller,uint64_t cut,uint64_t type,uint64_t lead,uint64_t duration);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelMotionCreationAddress(uint32_t address);
uint64_t nocturneCallMotionFactory(uint32_t target,uint64_t controller,uint64_t command,uint64_t argument);
void nocturneCallMotionCapture(uint32_t target,uint64_t node);
void nocturneCallMotionBind(uint32_t target,uint64_t node,uint64_t track);
#endif
