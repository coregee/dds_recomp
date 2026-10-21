#pragma once
#include <stdint.h>
void ps2ModelRegisterResource(uint64_t group,uint64_t id,uint64_t flags,uint64_t textures,uint64_t definition,uint64_t handle);
void ps2ModelDestroyResource(uint64_t resource);
void ps2ModelRemoveRegisteredResource(uint64_t group,uint64_t id);
void ps2ModelReleaseContextMotion(uint64_t context,uint64_t motion);
void ps2ModelReleaseContextSlot(uint64_t context,uint64_t slot);
void ps2ModelReleaseResourceSlot(uint64_t resource,uint64_t slot);
void ps2ModelConfigureResourceSlot(uint64_t group,uint64_t id,uint64_t flags,uint64_t cut,uint64_t slot,uint64_t index,uint64_t motion,uint64_t handle);
void ps2ModelRegisterLoadedFields(uint64_t group,uint64_t id,uint64_t flags,uint64_t fields);
void ps2ModelCompleteLoading(uint64_t loading);
void ps2ModelTextureLoadComplete(uint64_t request,uint64_t loading);
void ps2ModelDefinitionLoadComplete(uint64_t request,uint64_t loading);
void ps2ModelMotionLoadComplete(uint64_t request,uint64_t loading);
void ps2ModelUnlinkContext(uint64_t context);
void ps2ModelContextRelease(uint64_t context);
uint64_t ps2ModelTextureBookRead(uint64_t book);
uint64_t ps2ModelDefinitionBookRead(uint64_t book);
uint64_t ps2ModelMotionBookRead(uint64_t book);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelLoadingCompletionAddress(uint32_t address);
#endif
