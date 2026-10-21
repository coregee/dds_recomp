#ifndef NOCTURNE_MATERIAL_LISTS_DRAFT_H
#define NOCTURNE_MATERIAL_LISTS_DRAFT_H
#include <stdint.h>
/* Draft descriptive aliases. Not yet included in the recovery checkpoint. */
uint32_t ps2MatReadDefinition(uint32_t material,uint32_t textures,uint32_t definition);
void ps2MatRelease(uint32_t material);
uint32_t ps2MatWritePacketHeader(uint32_t commands,uint32_t output,uint32_t index);
void ps2MatCopyScalars40And44(uint32_t material,uint32_t output);
uint32_t ps2MemoryHandleAcquirePointer(uint32_t handle);
uint32_t ps2MemoryHandleReleasePointer(uint32_t handle);
#endif
