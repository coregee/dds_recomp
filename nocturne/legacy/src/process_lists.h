#ifndef NOCTURNE_PROCESS_LISTS_H
#define NOCTURNE_PROCESS_LISTS_H
#include <stdint.h>
/* Raw PS2 addresses and EE register lanes; managed HD IDs are different. */
void dds3DeleteProcessList(uint64_t process);
void dds3AddProcessList(uint64_t process);
void dds3StartReadyProcess(uint64_t process);
void dds3StartingProcesses(void);
void dds3SetProcessData(uint64_t process, uint64_t data);
uint64_t dds3GetProcessData(uint64_t process);
void *nocturneResolveProcessAddress(uint32_t address);
#endif
