#ifndef NOCTURNE_ORDERING_FLUSH_H
#define NOCTURNE_ORDERING_FLUSH_H
#include <stdint.h>
/* Raw PS2 addresses; indirect targets use an explicit host relocation boundary. */
void ps2DrawTagPrependStateReferences(uint32_t a0);
uint32_t ps2DrawOrderingFlush(uint32_t a0);
void ps2DrawNodeListInitialize(uint32_t a0);
void ps2DrawNodeListAppend(uint32_t a0,uint32_t a1);
void ps2DrawPacketListInitialize(uint32_t a0);
void ps2DrawPacketListAppend(uint32_t a0,uint32_t a1);
void nocturneCallDrawOrdering(uint32_t callback,uint32_t record,uint32_t mode,uint32_t tag);
#endif
