#ifndef NOCTURNE_VIF_RESET_H
#define NOCTURNE_VIF_RESET_H
#include <stdint.h>

typedef struct NocturneQuadword {
    uint64_t low;
    uint64_t high;
} NocturneQuadword;

void ps2VifGifResetPath(void);
/* Platform boundaries. FIFO transfers retain their original 128-bit width.
 * CTC2 device effects and SYNC timing belong to the platform implementation. */
void nocturneVifResetWrite32(uint32_t address, uint32_t value);
void nocturneVifResetSync(uint32_t type);
uint32_t nocturneVifResetReadControl(uint32_t index);
void nocturneVifResetWriteControl(uint32_t index, uint32_t value);
NocturneQuadword nocturneVifResetRead128(uint32_t address);
void nocturneVifResetWrite128(uint32_t address, NocturneQuadword value);
#endif
