#ifndef NOCTURNE_PS2_SDK_FRONTIER_H
#define NOCTURNE_PS2_SDK_FRONTIER_H

#include <stdint.h>

/* Behavioral aliases for complete original SDK/runtime leaves. No original
 * library symbol, compiler version or HD counterpart is asserted. */
int32_t ps2WidenByte(const void *ignored_state, uint32_t *output,
    const uint8_t *source, uint64_t available);
const void *ps2Memchr(const void *source, int32_t value, uint32_t count);
uint32_t ps2CountLeadingZeroBits(int32_t value);
uint32_t ps2RemoveTrailingZeroBits(uint32_t *word);
int32_t ps2CompareLimbArrays(const void *left, const void *right);
uint32_t ps2IsDoubleInfBits(uint64_t bits);
uint32_t ps2IsDoubleNaNBits(uint64_t bits);

/* Stable ordinary backed little-endian RAM, with no PS2 address wrap,
 * concurrent/device semantics or atomic bus-width claim. uint32 storage and
 * limb headers must be 4-byte aligned. Character accesses may have any byte
 * alignment. No restrict qualifiers or invented malformed-input fallback.
 *
 * WidenByte ignores A0; the chosen original raw-register ABI has output A1,
 * source A2 and all 64 bits of available in A3. Future original prototypes
 * must preserve that explicit fourth-register storage. It reads no memory
 * when source is NULL (return 0), or source is non-NULL and available is 0
 * (return -1). Otherwise it reads one unsigned byte, stores it as one complete
 * word to output (or its private scratch when output is NULL), then rereads
 * source and returns whether the reread byte is nonzero. Writable output may
 * alias source: this final return can change after the word store.
 *
 * Memchr narrows value to low8 and count to the qualified uint32 argument.
 * Count 0 permits NULL and accesses no memory. At 16-byte alignment with at
 * least 16 remaining bytes it loads the entire LQ16 block before inspecting
 * it, then rescans a matching block bytewise. Every probed block must be
 * readable. Other paths use bytes; it returns the first matching pointer
 * or NULL. Read-only aliases are valid.
 *
 * LeadingZeroBits requires the original canonical sign extension of int32
 * into A0. Inconsistent/zero-extended high-bit raw registers are a different
 * original interface: the full64 BLTZ can produce different values. Under
 * the declared signed-word ABI it counts leading zero bits of the low32
 * encoding, with zero returning 32. TrailingZeroBits reads one word, returns
 * 32 for zero and 0 for odd values without a store; a nonzero even value is
 * replaced by its logical shift to an odd word, returning the shift count.
 *
 * Limb arrays have opaque bytes +0..+15, count word at +16 and least-significant
 * first limbs at +20. Unequal counts return their exact low32 SUBU difference
 * interpreted as signed32. Equal positive counts compare from the last limb
 * down using unsigned word values, returning -1/0/1. Equal zero counts reread
 * the two count words as the original do-while path does. Unequal count words
 * may contain any 32 bits: only the two header words are read. Equal counts
 * must be nonnegative with their actual spans fully backed and no pointer wrap.
 * These fields establish an interface, not an asserted full runtime layout.
 *
 * Double predicates consume all 64 raw encoding bits in A0 and return exact
 * 0/1 in V0. They use integer instructions only, never a host float/double
 * conversion, NaN interpretation, floating flags or FCSR access. */

#endif
