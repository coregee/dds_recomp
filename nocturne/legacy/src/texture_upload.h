#ifndef NOCTURNE_TEXTURE_UPLOAD_H
#define NOCTURNE_TEXTURE_UPLOAD_H
#include <stdint.h>
uint64_t ps2TextureImageQwc(uint64_t format,uint64_t width,uint64_t height);
uint64_t ps2TextureQueueUpload(uint64_t record);
uint64_t ps2TextureImageTransfer(uint64_t address,uint64_t width,uint64_t height,uint64_t format,uint64_t source,uint64_t referenceMode);
uint64_t ps2TexturePaletteTransfer(uint64_t texture,uint64_t address,uint64_t source,uint64_t referenceMode);
uint64_t ps2TextureTmxCreate(uint64_t header,uint64_t referenceMode);
uint64_t ps2TextureTmxCopy(uint64_t header);
uint64_t ps2TextureTmxReference(uint64_t header);
void *nocturneResolveTextureUploadAddress(uint32_t address);
/* Ambient EE stack operand: the transfer's handle word is unassigned for
 * reference/pool ownership. Preserve that word rather than inventing zero. */
uint32_t nocturneTextureImageScratchWord(void);
#endif
