#ifndef NOCTURNE_FILE_OPERATIONS_H
#define NOCTURNE_FILE_OPERATIONS_H
#include <stdint.h>
uint64_t ps2FileRpcOpen(uint64_t path,uint64_t flags,uint64_t mode);
uint64_t ps2FileRpcClose(uint64_t descriptor);
uint64_t ps2FileRpcSeek(uint64_t descriptor,uint64_t offset,uint64_t origin);
uint64_t ps2FileRpcRead(uint64_t descriptor,uint64_t buffer,uint64_t bytes);
uint64_t ps2FileRpcWrite(uint64_t descriptor,uint64_t buffer,uint64_t bytes);
void *nocturneResolveFileOperationsAddress(uint32_t address);
uint32_t nocturneFileOperationResultAddress(uint32_t frame_bytes);
#endif
