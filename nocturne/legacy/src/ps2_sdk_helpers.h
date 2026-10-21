#ifndef NOCTURNE_PS2_SDK_HELPERS_H
#define NOCTURNE_PS2_SDK_HELPERS_H

#include "ps2_memory.h"

/* Original SLUS_209.11 string helpers and bytewise integer decoders.
 * Pointer results retain their original ABI identity; search targets narrow
 * to low8, bounded counts to low32, and comparison results are exact LBU
 * differences rather than normalized signs. No restrict qualifiers. */
char *ps2Strcat(char *destination, const char *source);
char *ps2Strchr(const char *source, int32_t value);
int32_t ps2Strncmp(const char *left, const char *right, uint32_t count);
char *ps2Strncpy(char *destination, const char *source, uint32_t count);
char *ps2Strrchr(const char *source, int32_t value);
char *ps2Strstr(const char *source, const char *needle);
const uint8_t *ps2ReadUleb128(const uint8_t *source, uint32_t *result);
const uint8_t *ps2ReadSleb128(const uint8_t *source, int32_t *result);

/* Ordinary backed RAM, no PS2 address wrap or concurrent/device semantics.
 * Every string/source byte alignment is supported. Whole aligned blocks
 * actually probed must be readable, even when NUL occurs near their start.
 *
 * Strncmp/Strncpy accept either/both NULL at count0 and access no memory.
 * Strncmp's aligned16 continuation reads the next LEFT16 block even when
 * only1..15 comparison bytes remain. Back this speculative block as well as
 * the ordinary counted spans; the right tail is read bytewise.
 * Strncpy writes exactly count bytes. It has the original first16 detector
 * and subsequent8-byte stages, including redundant loads; its source need
 * not terminate if count readable bytes exist. A NUL triggers zero padding.
 * Both retain original forward behavior for every finite backed alias case.
 *
 * Strcat requires a terminating destination, readable full blocks used by its
 * destination scan, and enough writable space for the appended source/NUL.
 * Its call to recovered Strcpy retains that helper's block/alias contract;
 * source overlap that overwrites the evolving terminator need not terminate.
 * Search routines require terminated readable strings and add no NULL
 * fallback. Strchr uses full aligned8/16 probes; Strrchr/Strstr use bytes.
 *
 * Decoders read through a byte with continuation bit clear, then write one
 * complete4-byte result and return the next source pointer. Result must be
 * valid4-byte-aligned storage. Source/result may overlap: all input reads
 * precede the final store. Overlong encodings retain EE shift-count wrapping;
 * no bounds, overflow, canonical-encoding or length fallback is invented.
 *
 * Explicit accesses and block snapshots retain original load/store stage
 * order. Portable C11 does not reproduce atomic EE bus widths; the existing
 * ps2_memory ordinary-RAM limitation applies. */

#endif
