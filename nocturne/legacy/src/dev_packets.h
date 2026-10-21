#ifndef NOCTURNE_DEV_PACKETS_H
#define NOCTURNE_DEV_PACKETS_H
#include <stdint.h>
uint64_t ps2TextureGetRegister(uint64_t texture);
void ps2DevFlushPackets(uint64_t handle);
void ps2DevBackgroundPacket(uint64_t node, uint64_t handle);
void ps2DevInitializePackets(uint64_t handle, uint64_t buffer, uint64_t size);
/* Original-address relocation and the SYNC 0 instruction boundary. */
void *nocturneResolveDevPacketAddress(uint32_t address);
void nocturneDevPacketSync(void);
#endif
