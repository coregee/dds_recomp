#ifndef NOCTURNE_CD_STREAM_H
#define NOCTURNE_CD_STREAM_H
#include <stdint.h>
uint64_t ps2CdNPreflight(uint64_t command);
uint64_t ps2CdSPreflight(uint64_t command);
uint64_t ps2CdNWait(uint64_t mode);
uint64_t ps2CdSWait(uint64_t mode);
uint64_t ps2CdStreamCommand(uint64_t sector,uint64_t count,uint64_t buffer,uint64_t operation,uint64_t mode);
uint64_t ps2CdStreamStart(uint64_t sector,uint64_t mode);
uint64_t ps2CdStreamStop(void);
uint64_t ps2CdStreamRead(uint64_t count,uint64_t buffer,uint64_t mode,uint64_t error);
uint64_t ps2CdGetError(void);
void *nocturneResolveCdStreamAddress(uint32_t address);
#endif
