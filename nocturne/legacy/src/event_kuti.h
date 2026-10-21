#ifndef NOCTURNE_EVENT_KUTI_H
#define NOCTURNE_EVENT_KUTI_H
#include <stdint.h>
uint64_t dds3GetActiveScene(void);
uint64_t dds3SearchSceneBasic(uint64_t scene,uint64_t serial,uint64_t type);
uint64_t evtGetUnitHandle(uint64_t serial);
void evtSetUnitExMotion(uint64_t unit,uint64_t group,uint64_t motion,uint64_t before,uint64_t smooth,uint64_t mode);
void evtSetUnitKutiMotion(uint64_t unit,uint64_t group,uint64_t motion);
void evtRunUnitKutiMotion(uint64_t unit);
void evtCommandKutiFunction(void);
uint64_t evtCommand_KUTISET(void);
uint64_t evtCommand_KUTI(void);
#endif
