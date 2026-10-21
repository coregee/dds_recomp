#ifndef NOCTURNE_DRAW_DMA_H
#define NOCTURNE_DRAW_DMA_H
#include <stdint.h>
/* Raw EE register interfaces; low words address the platform registers. */
void ps2DmaWait(uint64_t channel);
uint64_t ps2DmaStop(uint64_t channel);
void ps2DmaSendChain(uint64_t channel, uint64_t tag_address);
void ps2DmaReceive(uint64_t channel, uint64_t buffer, uint64_t count);
uint32_t nocturneDmaRead32(uint32_t address);
void nocturneDmaWrite32(uint32_t address, uint32_t value);
void nocturneDmaTimeoutDiagnostic(uint32_t format_address);
#endif
