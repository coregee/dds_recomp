#ifndef NOCTURNE_PAC_TEXTURE_H
#define NOCTURNE_PAC_TEXTURE_H
#include <stdint.h>
void ps2PacTexturePrepare(uint64_t parser,uint64_t header,uint64_t work);
void ps2PacTextureRawStream(uint64_t parser);
void ps2PacTextureReferenceStream(uint64_t parser);
void ps2PacTextureCompressedStream(uint64_t parser);
void ps2PacTextureComplete(uint64_t parser);
void ps2PacTextureRecordInitialize(uint64_t parser,uint64_t header);
#endif
