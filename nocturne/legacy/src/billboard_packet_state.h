#ifndef NOCTURNE_BILLBOARD_PACKET_STATE_H
#define NOCTURNE_BILLBOARD_PACKET_STATE_H

#include <stdint.h>

/* Raw EE A0/V0 are 64 bits. Loads and word arithmetic return sign-extended
 * low words; the single algorithm definition is shared with the staged build. */
uint64_t ps2BillboardTextureSource(uint64_t texture);                 /* 002AAF60 */
uint64_t ps2BillboardTextureSourceBytes(uint64_t texture);            /* 002AAF68 */
uint64_t ps2BillboardPaletteSourceBytes(uint64_t texture);            /* 002AAFC8 */
uint64_t ps2BillboardGeometryPacketSize(uint64_t count);              /* 002BB0E0 */
uint64_t ps2MaterialBillboardGeometryPacketSize(uint64_t count);      /* 002BB4A8 */

/* Host transport only: the three texture getters read actual guest RAM. */
void *nocturneResolveBillboardPacketsAddress(uint32_t address);

#endif
