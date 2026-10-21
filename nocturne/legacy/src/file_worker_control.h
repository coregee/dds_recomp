#ifndef NOCTURNE_FILE_WORKER_CONTROL_H
#define NOCTURNE_FILE_WORKER_CONTROL_H
#include <stdint.h>
uint64_t ps2FileJobComplete(uint64_t job);
uint64_t ps2FileCommandSeek(uint64_t job,uint64_t offset,uint64_t origin);
uint64_t ps2FileCommandSize(uint64_t job);
uint64_t ps2FileCommandRead(uint64_t job,uint64_t buffer,uint64_t bytes);
uint64_t ps2FileCommandWrite(uint64_t job,uint64_t buffer,uint64_t bytes);
uint64_t ps2FileCommandRetry(uint64_t job);
uint64_t ps2FileCommandClose(uint64_t job);
uint64_t ps2FileRequestLoad(uint64_t path,uint64_t buffer,uint64_t bytes,uint64_t callback,uint64_t payload);
uint64_t ps2FileRequestStore(uint64_t path,uint64_t buffer,uint64_t bytes,uint64_t callback,uint64_t payload,uint64_t stream_bytes);
uint64_t ps2KernelChangeThreadPriority(uint64_t id,uint64_t priority);
void ps2FileWorkerPriority(uint64_t priority);
void ps2FileWorkerMoviePriority(void);
void ps2FileWorkerDefaultPriority(void);
void ps2FileWorkerPriorityTick(void);
#endif
