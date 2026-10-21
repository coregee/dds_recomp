#ifndef NOCTURNE_PROCESS_CREATION_H
#define NOCTURNE_PROCESS_CREATION_H
#include <stdint.h>
uint64_t dds3StartProcess(uint64_t name,uint64_t priority,uint64_t startdelay,
    uint64_t shutdowndelay,uint64_t processfunc,uint64_t shutdownfunc,uint64_t data);
void evtInitMoonProcess(void);
void *nocturneResolveProcessCreationAddress(uint32_t address);
#endif
