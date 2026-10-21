#ifndef NOCTURNE_INTERRUPT_LIFECYCLE_H
#define NOCTURNE_INTERRUPT_LIFECYCLE_H
#include <stdint.h>
uint64_t ps2KernelRemoveSbusHandler(uint64_t cause);
void ps2InterruptHandlerRemove(uint64_t handler);
void ps2InterruptHandlersClear(void);
uint64_t ps2MovieSystemInitialize(void);
uint64_t ps2MovieUpdateProcess(void);
#endif
