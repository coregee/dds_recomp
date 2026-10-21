#ifndef NOCTURNE_LIBC_BIGINT_H
#define NOCTURNE_LIBC_BIGINT_H
#include <stdint.h>
/* Native dtoa records: next0,k4,maxwds8,sign12,wds16,limbs20.
 * Reentrancy cache: powers-of-five72, sixteen free-list heads at pointer76.
 * Raw EE argument lanes; pointers and word arithmetic wrap at32 bits.
 * Ordinary backed finite records; allocator failure is handled only where
 * the original does so. No host bigint or host floating-point conversion. */
uint64_t ps2LibcCallocReentrant(uint64_t context,uint64_t count,uint64_t size);
uint64_t ps2LibcBigintAllocate(uint64_t context,uint64_t k);
void ps2LibcBigintFree(uint64_t context,uint64_t bigint);
uint64_t ps2LibcBigintMultiplyAdd(uint64_t context,uint64_t bigint,uint64_t multiplier,uint64_t addend);
uint64_t ps2LibcBigintFromWord(uint64_t context,uint64_t value);
uint64_t ps2LibcBigintMultiply(uint64_t context,uint64_t left,uint64_t right);
uint64_t ps2LibcBigintPowerOfFive(uint64_t context,uint64_t bigint,uint64_t exponent);
uint64_t ps2LibcBigintShiftLeft(uint64_t context,uint64_t bigint,uint64_t shift);
uint64_t ps2LibcBigintDifference(uint64_t context,uint64_t left,uint64_t right);
uint64_t ps2LibcBigintFromDoubleBits(uint64_t context,uint64_t bits,uint64_t exponent,uint64_t significantBits);
uint64_t ps2LibcBigintQuotientRemainder(uint64_t numerator,uint64_t denominator);
#endif
