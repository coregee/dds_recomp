#ifndef NOCTURNE_RENDER_CHAIN_H
#define NOCTURNE_RENDER_CHAIN_H
#include <stdint.h>
/* Raw PS2 addresses; explicit packet store order preserves RAM aliases. */
void ps2DrawTagAppendReference(uint32_t a0,uint32_t a1);
void ps2DrawTagAppendPacket48(uint32_t a0,uint32_t a1);
void ps2DrawTagAppendCall(uint32_t a0,uint32_t a1);
void ps2DrawChainPrepend(uint32_t a0,uint32_t a1);
void ps2DrawChainAppend(uint32_t a0,uint32_t a1);
void ps2DrawChainPrependOnMode1(uint32_t a0,uint32_t a1,uint32_t a2);
void ps2DrawOrderingInitialize(uint32_t a0,uint32_t a1);
uint32_t ps2DrawBuildReferencePacket(uint32_t a0);
uint32_t ps2DrawLinkReferencePacket(uint32_t a0,uint32_t a1);
void ps2DrawTagLinkState(uint32_t a0,uint32_t a1);
#endif
