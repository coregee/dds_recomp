#ifndef NOCTURNE_PAC_TEXTURE_ARRAY_H
#define NOCTURNE_PAC_TEXTURE_ARRAY_H
#include <stdint.h>
uint64_t ps2PointerArrayCreate(int32_t capacity);
void ps2PointerArrayAppend(uint64_t array,uint64_t value);
void ps2PacTextureArrayHeaderReady(uint64_t parser);
void ps2PacTextureArrayReadHeader(uint64_t parser);
void ps2PacTextureArrayCompleteItem(uint64_t parser);
void ps2PacTextureArraySkipTable(uint64_t parser);
void ps2PacTextureArrayReadCount(uint64_t parser);
void ps2PacTextureArrayRecordInitialize(uint64_t parser,uint64_t header);
uint64_t ps2PacDefaultHeaderCallback(uint64_t parser,uint64_t phase,uint64_t header);
#endif
