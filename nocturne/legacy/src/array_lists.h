#ifndef NOCTURNE_ARRAY_LISTS_H
#define NOCTURNE_ARRAY_LISTS_H
#include <stdint.h>
uint32_t ps2ArrayCreate(int32_t capacity,int32_t stride,int32_t growth);
void ps2ArrayFree(uint32_t array);
void ps2ArrayGrow(uint32_t array);
void ps2ArrayResize(uint32_t array,int32_t capacity);
uint32_t ps2MatListCreate(int32_t capacity);
void ps2MatListFreeMaterials(uint32_t list);
void ps2MatListGrow(uint32_t list);
void ps2MatListAppend(uint32_t list,uint32_t material);
uint32_t ps2MatListMake(uint32_t textures,uint32_t definitions);
#endif
