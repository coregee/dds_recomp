#ifndef NOCTURNE_CD_SERVICES_H
#define NOCTURNE_CD_SERVICES_H
#include <stdint.h>
uint64_t ps2CdSearchFileExtended(uint64_t output,uint64_t path,uint64_t layer);
uint64_t ps2CdSearchFile(uint64_t output,uint64_t path);
uint64_t ps2CdDiskReady(uint64_t mode);
uint64_t ps2CdNCommand14(void);
uint64_t ps2CdSCommand22(uint64_t mode);
uint64_t ps2CdGetDiskType(void);
uint64_t ps2CdSCommand21OutputWord(uint64_t output);
uint64_t ps2CdReadClock(uint64_t output);
uint64_t ps2CdStreamInitialize(uint64_t a0,uint64_t a1,uint64_t a2);
uint64_t ps2CdStreamSeekFast(uint64_t sector);
uint64_t ps2CdStreamSeek(uint64_t sector);
uint64_t ps2CdStreamPause(void);
uint64_t ps2CdStreamResume(void);
uint64_t ps2CdStreamStatus(void);
#endif
