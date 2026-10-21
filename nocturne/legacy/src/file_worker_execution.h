#ifndef NOCTURNE_FILE_WORKER_EXECUTION_H
#define NOCTURNE_FILE_WORKER_EXECUTION_H
#include <stdint.h>
uint64_t ps2FileWorkerCloseDetach(uint64_t job);
void ps2FileWorkerError(uint64_t job,uint64_t error);
/* The original thread entry never returns. */
void ps2FileWorkerRun(uint64_t worker);
void nocturneFileWorkerInvoke(uint32_t entry,uint64_t job,uint64_t event,
                             uint64_t buffer,uint64_t result,uint64_t payload);
#endif
