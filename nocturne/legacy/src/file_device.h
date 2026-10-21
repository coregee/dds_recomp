#ifndef NOCTURNE_FILE_DEVICE_H
#define NOCTURNE_FILE_DEVICE_H
#include <stdint.h>
uint64_t ps2FileHostRoot(void);
uint64_t ps2FileNormalizePath(uint64_t path,uint64_t device);
uint64_t ps2FileResolvePath(uint64_t path,uint32_t *output);
uint64_t ps2KernelCreateThread(const void *parameters);
uint64_t ps2KernelStartThread(uint64_t id,uint64_t parameters);
uint64_t ps2ThreadCreateWithStack(uint64_t entry,uint64_t stack,uint64_t bytes,uint64_t priority);
uint64_t ps2ThreadCreateAllocated(uint64_t entry,uint64_t bytes,uint64_t priority);
void ps2FileDeviceInitialize(uint64_t device);
void ps2FileJobEnqueue(uint64_t job);
uint64_t ps2FileRequestRead(uint64_t path,uint64_t callback,uint64_t payload);
uint64_t ps2FileRequestStream(uint64_t path,uint64_t callback,uint64_t payload,uint64_t bytes);
#endif
