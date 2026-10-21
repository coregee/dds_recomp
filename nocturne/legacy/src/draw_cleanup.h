#ifndef NOCTURNE_DRAW_CLEANUP_H
#define NOCTURNE_DRAW_CLEANUP_H
#include <stdint.h>
void ps2DrawCleanupCompleted(void);
void *nocturneResolveDrawCleanupAddress(uint32_t address);
#endif
