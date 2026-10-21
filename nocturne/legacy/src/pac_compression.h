#ifndef NOCTURNE_PAC_COMPRESSION_H
#define NOCTURNE_PAC_COMPRESSION_H
#include <stdint.h>
uint64_t ps2MemoryHandleAllocateHigh(uint64_t size);
void ps2MemoryHandleClearSlot(uint64_t slot);
void ps2PacCompressionInitialize(uint64_t work,uint64_t destination);
uint64_t ps2PacCompressionDecode(uint64_t work,uint64_t input,uint64_t count);
void *nocturneResolvePacCompressionAddress(uint32_t address);
#endif
