#ifndef NOCTURNE_DRAW_CONSUMER_SUPPORT_H
#define NOCTURNE_DRAW_CONSUMER_SUPPORT_H
#include <stdint.h>
/* Raw EE integer interfaces; kernel implementation remains external. */
void ps2DrawPrepareFrameState(uint64_t frame, uint64_t mode);
void ps2DrawCompleteFrameState(uint64_t queued, uint64_t frame, uint64_t half);
uint64_t ps2DmaNormalizeAddress(uint64_t address);
uint64_t ps2DmaGetChannel(uint64_t index);
uint64_t ps2GsSwapInterruptMask(uint64_t mask);
uint64_t ps2GsReadInterruptMask(void);
uint64_t ps2KernelSleepThread(void);
uint64_t ps2KernelFlushCache(uint64_t mode);
uint64_t ps2KernelGetGsIMR(void);
uint64_t ps2KernelPutGsIMR(uint64_t mask);
void *nocturneResolveDrawSupportAddress(uint32_t address);
uint64_t nocturneDrawSupportKernelValue(uint32_t selector, uint32_t has_argument, uint64_t argument);
#endif
