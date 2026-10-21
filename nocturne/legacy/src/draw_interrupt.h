#ifndef NOCTURNE_DRAW_INTERRUPT_H
#define NOCTURNE_DRAW_INTERRUPT_H
#include <stdint.h>
void ps2DrawResetCompletedRecord(uint64_t record);
uint64_t ps2DrawDmaInterrupt(uint64_t channel, uint64_t thread);
uint64_t ps2DrawWakeThread(uint64_t thread);
uint64_t ps2KernelInterruptWakeThread(uint64_t thread);
uint64_t ps2KernelInterruptSignalSema(uint64_t semaphore);
uint64_t ps2KernelAddDmaHandler(uint64_t channel, uint64_t callback,
                              uint64_t next, uint64_t argument);
uint64_t ps2KernelRemoveDmaHandler(uint64_t channel, uint64_t handler);
/* Original-address and raw syscall/SYNC0 value boundaries. */
void *nocturneResolveDrawInterruptAddress(uint32_t address);
uint64_t nocturneDrawInterruptKernelValue(uint64_t selector, uint32_t argc,
                                        const uint64_t *args);
void nocturneDrawInterruptSync(void);
#endif
