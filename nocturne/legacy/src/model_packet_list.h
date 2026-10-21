#ifndef NOCTURNE_MODEL_PACKET_LIST_H
#define NOCTURNE_MODEL_PACKET_LIST_H
#include <stdint.h>
void ps2ModelAppendWeightedMeshPackets(uint64_t node,uint64_t command,uint64_t chain,uint64_t frame);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelPacketListAddress(uint32_t address);
uint32_t nocturneModelPacketListFrameAddress(void);
#endif
#endif
