#ifndef NOCTURNE_GRAPHICS_SYNC_H
#define NOCTURNE_GRAPHICS_SYNC_H
#include <stdint.h>
/* Raw EE integer interfaces. Controller reads and VU control are external. */
uint64_t ps2DmaWaitOrStatus(uint64_t channel, uint64_t mode);
void ps2DmaSendNormal(uint64_t channel, uint64_t buffer, uint64_t count);
uint64_t ps2GsSyncPath(uint64_t mode);
uint32_t nocturneGraphicsReadVuControl(uint32_t index);
void nocturneGraphicsDiagnostic(uint32_t format, uint32_t has_argument, uint64_t argument);
#endif
