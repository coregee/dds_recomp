#ifndef NOCTURNE_PIB_CHUNK_LEAVES_H
#define NOCTURNE_PIB_CHUNK_LEAVES_H
#include <stdint.h>

/* Recovered original 001DEA60/001DEAE8/001DEB00/001DEA68 interfaces;
 * complete original-instruction comparisons include nonempty lookup paths.
 * A complete readable header includes bytes 12..13; first-item access needs
 * a readable word at +8; next-item stride and target word must be fully backed.
 * Ordinary stable RAM, without PS2 address wrap or concurrent mutation. */
uint32_t mdlPibGetChunkCount(const void *header);
void *mdlPibGetFirstChunkItem(void *chunk);
void *mdlPibGetNextChunkItem(void *item);
/* Original handle bytes +C contain a 32-bit model-data address, whose +A4
 * word points to the PIB header or is zero. Read-only ordinary RAM mapping
 * resolves these addresses on a wide-pointer host; it supplies no game result.
 * On a 32-bit PS2 build original addresses are direct pointers. */
void *mdlPibGetChunk(const void *handle,int32_t group);
#if UINTPTR_MAX > UINT32_MAX
const void *nocturneResolvePibAddress(uint32_t address);
#endif
#endif
