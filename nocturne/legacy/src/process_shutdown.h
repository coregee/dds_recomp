#ifndef NOCTURNE_PROCESS_SHUTDOWN_H
#define NOCTURNE_PROCESS_SHUTDOWN_H
#include <stdint.h>
void dds3KillProcessNow(uint64_t process);
void dds3EndProcess(uint64_t process);
void dds3EndingProcesses(void);
uint64_t dds3KillProcess(uint64_t process,uint64_t delay);
void dds3UnlinkProcess(uint64_t process);
void ps2MoonShutdown(uint64_t process);
void ps2TextureDeferredRelease(uint64_t texture);
void *nocturneResolveProcessShutdownAddress(uint32_t address);
void nocturneProcessDiagnostic(uint32_t format,uint64_t process);
void nocturneProcessShutdownCallback(uint32_t callback,uint64_t process);
#endif
