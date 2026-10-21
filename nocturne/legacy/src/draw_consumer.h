#ifndef NOCTURNE_DRAW_CONSUMER_H
#define NOCTURNE_DRAW_CONSUMER_H
#include <stdint.h>
/* Raw PS2 address model; explicit external register/callback/frame boundaries. */
void ps2DrawConsumeRequest(void);
void *nocturneResolveDrawConsumerAddress(uint32_t address);
uint16_t nocturneDrawConsumerRead16(uint32_t address);
uint64_t nocturneDrawConsumerRead64(uint32_t address);
void nocturneDrawConsumerWrite64(uint32_t address, uint64_t value);
void nocturneDrawConsumerCallback(uint32_t callback, uint64_t first, uint64_t second);
/* Original-address frame relocation for the nested console renderer. */
void nocturneDrawConsumerFrameEnter(uint32_t size);
void nocturneDrawConsumerFrameLeave(uint32_t size);
#endif
