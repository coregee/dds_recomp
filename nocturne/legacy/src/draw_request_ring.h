#ifndef NOCTURNE_DRAW_REQUEST_RING_H
#define NOCTURNE_DRAW_REQUEST_RING_H
#include <stdint.h>
uint32_t ps2ReadDrawCounterWord(void);
uint32_t ps2ReadDrawCounterDelta(uint32_t start);
void ps2DrawPublishRequest(uint64_t tag_chain, uint64_t pre_draw_links);
void *nocturneResolveDrawRequestAddress(uint32_t address);
#endif
