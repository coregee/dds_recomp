#ifndef NOCTURNE_PS2_MEMORY_H
#define NOCTURNE_PS2_MEMORY_H

#include <stdint.h>

/* Recovered leaf routines from SLUS_209.11. Counts and lengths use the
 * original low 32-bit ABI; pointer results retain the original destination.
 * These aliases avoid replacing the host C library's symbols. */
int32_t ps2Memcmp(const void *left, const void *right, uint32_t count);
void *ps2Memcpy(void *destination, const void *source, uint32_t count);
void *ps2Memmove(void *destination, const void *source, uint32_t count);
void *ps2Memset(void *destination, int32_t value, uint32_t count);
int32_t ps2Strcmp(const char *left, const char *right);
char *ps2Strcpy(char *destination, const char *source);
uint32_t ps2Strlen(const char *source);

/* Ordinary byte-addressed RAM with backed ranges and no PS2 address wrap.
 * Every byte alignment is supported. The four count-based routines perform
 * no memory access at count == 0, including NULL arguments. At positive
 * counts, their complete ranges must be backed.
 *
 * Memmove supports arbitrary overlap. Memcpy preserves the original forward
 * byte/chunk order, including self-alias and partial overlap; it does not
 * substitute memmove. Strcpy likewise preserves forward writes, without an
 * overlap fallback: its evolving source must terminate inside backed storage.
 *
 * String routines require a terminating NUL. Their 8-/16-byte aligned paths
 * read whole blocks, including the block containing NUL. Those complete
 * blocks must be readable; Strcpy writes only through the terminating NUL.
 * Unaligned string paths read individual bytes. NULL strings are invalid.
 *
 * The source preserves the ordering of original load/store stages by taking
 * block snapshots before stores and using explicit byte accesses. Portable
 * C11 does not reproduce atomic EE LD/LQ/SD/SQ bus transactions; MMIO,
 * concurrently mutated memory, and volatile device semantics are excluded. */

#endif
