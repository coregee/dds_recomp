#ifndef NOCTURNE_PS2_SDK_NEIGHBORS_H
#define NOCTURNE_PS2_SDK_NEIGHBORS_H

#include <stdint.h>

/* At original 0054b551. This points 128 bytes into the complete 384-byte
 * backing captured in character-class-bytes.bin. The loop uses indexes
 * -128..127, including original preceding data; its final comparison uses
 * indexes 0..255. The pointer and backing remain stable during a call. */
extern const uint8_t *g_ps2CharacterClasses;

/* Host pointer corresponding to the original 32-bit slot at 0052be28.
 * The getter loads this slot once and does not access its target. */
extern uint8_t *g_ps2RuntimeState;

int32_t ps2Strcasecmp(const char *left, const char *right);
float ps2AbsFloat(float value);
float ps2CopySignFloat(float magnitude, float sign);
uint32_t ps2CountRuntimeRangeRecords(const void *records);
const void *ps2FindRuntimeRangeRecord(const void *records, uint32_t address);
uint8_t *ps2GetRuntimeState(void);

/* Ordinary stable backed RAM; no device, concurrent or PS2 address-wrap
 * behavior is claimed. Strings may have any byte alignment and may alias.
 * A terminating left string and enough right backing for the bytes actually
 * read are required. There is no NULL fallback or speculative block access.
 * Case folding is a class-bit-0 test plus 32, not host locale conversion.
 * The final result is the exact unsigned folded-byte difference, including
 * the original signed-loop versus unsigned-final classification difference.
 *
 * Float leaves transport raw 32-bit encodings via memcpy and perform no
 * floating arithmetic. Original Abs ABI: F12 input, F0 output. CopySign ABI:
 * F12 magnitude, F13 sign, F0 output. Both also touch their original private
 * 16-byte stack frames. Exponent-255 values, signed zero and payload bits are
 * preserved except for the requested sign bit. FCSR is not accessed.
 *
 * Record chains begin at a 4-byte-aligned length word and end at length 0.
 * Each next record is current + low32(length + 4), with a signed displacement
 * in this ordinary-RAM representation. A finite chain whose steps stay in
 * one backed object is required; backwards steps are supported. Every word
 * actually loaded must be backed/aligned. A nonzero length loads word +4;
 * only nonzero +4 loads +8; Find only nonzero +8 loads +12. The +4 field is
 * solely a nonzero discriminator. Count does not load +12. Find tests
 * low32(address - word_at_8) < unsigned_word_at_12, including wraparound.
 * It returns the first matching record, or NULL after the zero terminator.
 * The recovered names describe proved behavior, not a claimed compiler ABI.
 */

#endif
