#ifndef NOCTURNE_DEFERRED_DRAIN_H
#define NOCTURNE_DEFERRED_DRAIN_H
#include <stdint.h>
/* Ordinary RAM behavior; kernel values and indirect calls use explicit boundaries. */
uint32_t ps2DeferredQueueDetachActive(void);
void ps2DeferredQueueDrain(uint32_t a0);
void ps2DeferredQueueAdvance(void);
uint32_t ps2DeferredQueueIsBusy(void);
uint32_t ps2DeferredQueueIsBusyAtomic(void);
void ps2WorkBufferReplace(uint32_t a0);
void ps2WorkBufferSelect(uint32_t a0);
uint32_t ps2WorkBufferTake(uint32_t a0);
uint32_t ps2WorkBufferGetCursor(void);
void ps2WorkBufferSetCursor(uint32_t a0);
void ps2DmaChainInitialize(uint32_t a0);
void ps2DmaChainAppend(uint32_t a0,uint32_t a1);
void ps2DmaChainAppendWithTail(uint32_t a0,uint32_t a1,uint32_t a2);
uint32_t ps2WorkBufferGetRemaining(void);
void nocturneCallDeferredRelease(uint32_t callback,uint32_t value);
#endif
