#ifndef NOCTURNE_LIBC_DTOA_H
#define NOCTURNE_LIBC_DTOA_H
#include <stdint.h>
/* Raw double bits and EE slots; guest output words. Original modes0..9,
 * precision semantics, reentrancy64/68 output cache and72/76 bigint caches.
 * Ordinary backed bounded records; original allocator failure dereferences
 * and malformed pointers remain outside returning-call comparison evidence. */
uint64_t ps2LibcDtoa(uint64_t context,uint64_t bits,uint64_t mode,uint64_t precision,uint64_t decimalPoint,uint64_t sign,uint64_t endPointer);
#endif
