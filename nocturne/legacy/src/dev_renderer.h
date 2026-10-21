#ifndef NOCTURNE_DEV_RENDERER_H
#define NOCTURNE_DEV_RENDERER_H
#include <stdint.h>
void ps2DevRenderGlyphCells(uint64_t node, uint64_t handle);
void ps2DevRenderConsoleList(void);
/* Host relocation for an original stack frame, not a game-function hook. */
uint32_t nocturneDevRendererFrameEnter(uint32_t size);
void nocturneDevRendererFrameLeave(uint32_t frame, uint32_t size);
void *nocturneResolveDevRendererAddress(uint32_t address);
#endif
