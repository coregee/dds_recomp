#ifndef NOCTURNE_MODEL_PLACEMENT_SIMPLE_H
#define NOCTURNE_MODEL_PLACEMENT_SIMPLE_H
#include <stdint.h>
void ps2ModelPlaceReferenceMeshes(uint64_t surfaces,uint64_t root);
void *nocturneResolveModelPlacementAddress(uint32_t address);
uint32_t nocturneModelPlacementFrameAddress(void);
void nocturneModelPlacementSubmit(uint32_t callback,uint64_t surface,uint64_t chain);
#endif
