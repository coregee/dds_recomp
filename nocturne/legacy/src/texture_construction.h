#ifndef NOCTURNE_TEXTURE_CONSTRUCTION_H
#define NOCTURNE_TEXTURE_CONSTRUCTION_H
#include <stdint.h>
uint64_t ps2VramAllocate(uint64_t size,uint64_t category);
void ps2TextureRegister(uint64_t texture);
uint64_t ps2TextureDescriptorCreate(uint64_t width,uint64_t height,uint64_t format,uint64_t mip,uint64_t base,uint64_t paletteFormat,uint64_t paletteEntries,uint64_t palette);
uint64_t ps2TexturePaletteVramCreate(uint64_t format,uint64_t paletteFormat,uint64_t unused);
uint64_t ps2TextureMipCreate(uint64_t width,uint64_t height,uint64_t format,uint64_t mip,uint64_t paletteFormat,uint64_t paletteEntries);
uint64_t ps2TexturePaletteCount(uint64_t texture);
uint64_t ps2TexturePaletteAddress(uint64_t texture);
uint64_t ps2TextureBaseAddress(uint64_t texture);
uint64_t ps2TextureFormatBits(uint64_t format);
uint64_t ps2TexturePaletteBytes(uint64_t format,uint64_t paletteFormat,uint64_t count);
uint64_t ps2TextureStagingAllocate(uint64_t size);
void ps2TexturePaletteStagingAllocate(uint64_t texture);
uint64_t ps2TexturePaletteCopy(uint64_t texture,uint64_t source);
uint64_t ps2TextureRegisterCacheCreate(uint64_t texture,uint64_t context);
void ps2TextureDefaultCacheCreate(uint64_t texture);
void *nocturneResolveTextureAddress(uint32_t address);
void nocturneVramErrorCallback(uint32_t callback,uint64_t size,uint64_t category);
#endif
