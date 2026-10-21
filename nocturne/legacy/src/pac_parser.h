#ifndef NOCTURNE_PAC_PARSER_H
#define NOCTURNE_PAC_PARSER_H
#include <stdint.h>
void ps2PacInitialize(uint64_t parser,uint64_t callback);
void ps2PacSetFlag2(uint64_t parser);
void ps2PacReleaseRecords(uint64_t parser);
void ps2PacStop(uint64_t parser);
void ps2PacAdvanceBuffer(uint64_t parser,uint64_t count);
void ps2PacReadHeader(uint64_t parser);
void ps2PacFinishRecord(uint64_t parser);
uint64_t ps2PacDecodeChunk(uint64_t parser,uint64_t input,uint64_t count);
uint64_t ps2PacAppendRecord(uint64_t parser,uint64_t header);
void *nocturneResolvePacAddress(uint32_t address);
uint64_t nocturnePacHeaderCallback(uint32_t callback,uint64_t parser,uint64_t phase,uint64_t header);
void nocturnePacDataCallback(uint32_t callback,uint64_t parser);
#endif
