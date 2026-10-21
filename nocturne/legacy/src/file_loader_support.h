#ifndef NOCTURNE_FILE_LOADER_SUPPORT_H
#define NOCTURNE_FILE_LOADER_SUPPORT_H
#include <stdint.h>
uint64_t ps2MemoryHandleTryAllocate(uint64_t size);
uint64_t ps2FileJobCreate(uint64_t path,uint64_t device,uint64_t mode,uint64_t callback,uint64_t payload);
void ps2FileJobRelease(uint64_t job);
uint64_t ps2FileJobReleaseIfTerminal(uint64_t job);
uint64_t ps2FilePathClone(uint64_t path);
#endif
