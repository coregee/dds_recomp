#ifndef NOCTURNE_TEXTURE_ENVIRONMENT_H
#define NOCTURNE_TEXTURE_ENVIRONMENT_H
#include <stdint.h>
void ps2DrawBuildTextureRegisterGroup(uint32_t dst,uint32_t width,uint32_t height,uint32_t address,uint32_t format,uint64_t palette,uint64_t paletteMode,uint64_t functionMode,uint32_t filter,uint32_t filterValue,uint32_t clamp,uint32_t context);
void ps2DrawUpdateEnvironmentRecord(uint32_t record,uint32_t index);
#endif
