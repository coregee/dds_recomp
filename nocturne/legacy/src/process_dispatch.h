#ifndef NOCTURNE_PROCESS_DISPATCH_H
#define NOCTURNE_PROCESS_DISPATCH_H
#include <stdint.h>
uint64_t dds3RunProcess(uint64_t process);
void dds3RunningProcess(void);
void *nocturneResolveProcessDispatchAddress(uint32_t address);
uint64_t nocturneProcessRunCallback(uint32_t callback,uint64_t process);
#endif
