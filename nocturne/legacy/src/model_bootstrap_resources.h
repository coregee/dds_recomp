#pragma once
#include <stdint.h>
uint64_t ps2ModelTextureListClone(uint64_t list);
uint64_t ps2TextureDescriptorClone(uint64_t texture);
void ps2TextureRefreshPalette(uint64_t texture);
uint64_t ps2ModelFindRegisteredResource(uint64_t major,uint64_t minor);
uint64_t ps2ModelIsPending(uint64_t major,uint64_t minor);
void ps2ModelMarkPending(uint64_t major,uint64_t minor);
uint64_t ps2ModelResourceListCreate(uint64_t capacity);
void ps2ModelResourceAppendBillboard(uint64_t list,uint64_t source);
void ps2ModelResourceAppendEffect(uint64_t list,uint64_t source);
void ps2ModelResourceAppendMovie(uint64_t list,uint64_t first,uint64_t handle,uint64_t callback);
void ps2ModelMovieResourceRelease(uint64_t object);
void ps2ModelResourceListRelease(uint64_t list);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelBootstrapAddress(uint32_t address);
#endif
