#ifndef NOCTURNE_DISC_PLATFORM_H
#define NOCTURNE_DISC_PLATFORM_H
#include <stdint.h>
uint64_t ps2SifRpcIsBusy(uint64_t client);
void ps2CdInitializeSemaphores(void);
uint64_t ps2KernelPollSema(uint64_t semaphore);
uint64_t ps2KernelReferThreadStatus(uint64_t thread, uint64_t status);
uint64_t ps2KernelSetAlarmRaw(uint64_t delay, uint64_t callback, uint64_t argument);
void ps2CdAlarmSignal(uint64_t alarm, uint64_t time, uint64_t semaphore);
uint64_t ps2CdDelay(uint64_t delay);
uint64_t ps2FileAlarmWakeThread(uint64_t alarm, uint64_t time, uint64_t thread);
uint64_t ps2FileDelay(uint64_t delay);
/* Relocate original addresses on a host; kernel values remain external. */
void *nocturneResolveDiscPlatformAddress(uint32_t address);
uint64_t nocturneDiscPlatformKernel(uint64_t selector, uint32_t argc, const uint64_t *args);
#endif
