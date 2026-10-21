#ifndef NOCTURNE_MOTION_KEY_SEARCH_H
#define NOCTURNE_MOTION_KEY_SEARCH_H
#include <stdint.h>
/* Original A0=node,F12=raw frame,A1=direct12-byte output. This C declaration
 * expresses the raw value contract; target compilation must bind that ABI.
 * Output preserves32-bit previous/next addresses and raw interpolation bits.
 * Stable backed ordinary RAM, original load alignments and no address wrap. */
void sdfMotGetKey(const void *node,uint32_t frame_bits,void *output);
#endif
