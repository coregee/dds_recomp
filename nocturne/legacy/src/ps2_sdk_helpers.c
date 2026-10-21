#include "ps2_sdk_helpers.h"

#include <limits.h>

_Static_assert(CHAR_BIT == 8, "PS2 byte width");

static uint8_t read_byte(const uint8_t *source)
{
    return *(const volatile uint8_t *)source;
}

static void write_byte(uint8_t *destination, uint8_t value)
{
    *(volatile uint8_t *)destination = value;
}

static void read_block(uint8_t block[16], const uint8_t *source,
    uint32_t width)
{
    for (uint32_t i = 0; i < width; ++i)
        block[i] = read_byte(source + i);
}

static void write_block(uint8_t *destination, const uint8_t block[16],
    uint32_t width)
{
    for (uint32_t i = 0; i < width; ++i)
        write_byte(destination + i, block[i]);
}

static int blocks_equal(const uint8_t left[16], const uint8_t right[16],
    uint32_t width)
{
    for (uint32_t i = 0; i < width; ++i)
        if (left[i] != right[i]) return 0;
    return 1;
}

static int block_has_zero(const uint8_t block[16], uint32_t width)
{
    if (width == 16) {
        for (uint32_t i = 0; i < 16; ++i) {
            uint8_t difference = (uint8_t)(block[i] - 1u);
            if ((difference & (uint8_t)~block[i] & 0x80u) != 0)
                return 1;
        }
        return 0;
    }
    uint64_t word = 0;
    for (uint32_t i = 0; i < 8; ++i)
        word |= (uint64_t)block[i] << (i * 8u);
    return ((word - UINT64_C(0x0101010101010101)) & ~word &
        UINT64_C(0x8080808080808080)) != 0;
}

static int block_has_byte(const uint8_t block[16], uint8_t value,
    uint32_t width)
{
    uint8_t difference[16];
    for (uint32_t i = 0; i < width; ++i)
        difference[i] = (uint8_t)(block[i] ^ value);
    return block_has_zero(difference, width);
}

/* 002d57f8: destination scan includes an initial LD before its first LQ.
 * The source is read only by the existing original Strcpy helper. */
char *ps2Strcat(char *destination, const char *source)
{
    uint8_t *a = (uint8_t *)destination;
    if (((uintptr_t)a & 7u) == 0) {
        uint8_t block[16];
        uint32_t width = ((uintptr_t)a & 15u) == 0 ? 16u : 8u;
        read_block(block, a, 8);
        if (width == 16)
            read_block(block, a, 16);
        while (!block_has_zero(block, width)) {
            a += width;
            read_block(block, a, width);
        }
    }
    while (read_byte(a) != 0)
        ++a;
    ps2Strcpy((char *)a, source);
    return destination;
}

/* 002d5924: find low8 value, with NUL taking priority in a probed block. */
char *ps2Strchr(const char *source, int32_t value)
{
    const uint8_t *a = (const uint8_t *)source;
    uint8_t target = (uint8_t)value;
    if (((uintptr_t)a & 7u) == 0) {
        uint8_t block[16];
        uint32_t width = ((uintptr_t)a & 15u) == 0 ? 16u : 8u;
        for (;;) {
            read_block(block, a, width);
            if (block_has_zero(block, width) ||
                block_has_byte(block, target, width))
                break;
            a += width;
        }
    }
    for (;;) {
        uint8_t byte = read_byte(a);
        if (byte == 0 || byte == target) {
            /* Original LBU rechecks the selected byte before MOVZ. */
            uint8_t again = read_byte(a);
            return again == target ? (char *)a : (char *)0;
        }
        ++a;
    }
}

/* 002d5e48: bounded compare, preserving left-side tail speculation and
 * rereading every equal full block before its zero check. */
int32_t ps2Strncmp(const char *left, const char *right, uint32_t count)
{
    const uint8_t *a = (const uint8_t *)left;
    const uint8_t *b = (const uint8_t *)right;
    if (count == 0) return 0;
    uintptr_t alignment = (uintptr_t)a | (uintptr_t)b;
    if ((alignment & 7u) == 0) {
        uint8_t a_block[16], b_block[16];
        uint32_t width = (alignment & 15u) == 0 && count >= 16 ? 16u : 8u;
        if (count >= width) {
            read_block(a_block, a, width);
            read_block(b_block, b, width);
            if (blocks_equal(a_block, b_block, width)) {
                count -= width;
                for (;;) {
                    if (count == 0) return 0;
                    read_block(a_block, a, width);
                    if (block_has_zero(a_block, width)) return 0;
                    a += width;
                    b += width;
                    if (width == 16) {
                        /* 002d5f04 loads LEFT16 before testing tail count. */
                        read_block(a_block, a, 16);
                        if (count < 16) break;
                    } else {
                        if (count < 8) break;
                        read_block(a_block, a, 8);
                    }
                    read_block(b_block, b, width);
                    if (!blocks_equal(a_block, b_block, width)) break;
                    count -= width;
                }
            }
        }
    }
    uint8_t a_byte = read_byte(a);
    --count;
    for (;;) {
        uint8_t b_byte = read_byte(b);
        uint8_t a_again = read_byte(a); /* LBU in the BEQ delay slot. */
        if (a_byte != b_byte) {
            /* The final original operands are loaded right, then left. */
            uint8_t b_final = read_byte(b);
            uint8_t a_final = read_byte(a);
            return (int32_t)a_final - (int32_t)b_final;
        }
        if (count == 0 || a_again == 0) return 0;
        ++a;
        ++b;
        a_byte = read_byte(a);
        --count;
    }
}

/* Exact first LQ detector at 002d6050..6080. The input is complemented
 * BEFORE PSUBB, then ANDed with that same complemented input. It finds NUL
 * plus conservative false positives for other bytes 01..7e. Do not replace
 * this first detector with the later ordinary zero detector. */
static int first_copy_block_stops(const uint8_t block[16])
{
    for (uint32_t i = 0; i < 16; ++i) {
        uint8_t inverse = (uint8_t)~block[i];
        uint8_t difference = (uint8_t)(inverse - 1u);
        if ((difference & inverse & 0x80u) != 0) return 1;
    }
    return 0;
}

/* 002d6000: one possible first16 store, then original8-byte stages. */
char *ps2Strncpy(char *destination, const char *source, uint32_t count)
{
    uint8_t *a = (uint8_t *)destination;
    const uint8_t *b = (const uint8_t *)source;
    uintptr_t alignment = (uintptr_t)a | (uintptr_t)b;
    uint8_t block[16];
    int copy_eight = 0;
    if ((alignment & 7u) == 0) {
        if ((alignment & 15u) == 0 && count >= 16) {
            read_block(block, b, 16);
            if (!first_copy_block_stops(block)) {
                read_block(block, b, 16);
                write_block(a, block, 16);
                a += 16;
                b += 16;
                count -= 16;
                if (count >= 16) {
                    read_block(block, b, 16);
                    if (!block_has_zero(block, 16)) {
                        read_block(block, b, 16);
                        copy_eight = 1; /* Branches into SD path at 002d6130. */
                    }
                }
            }
        } else if ((alignment & 15u) != 0 && count >= 8) {
            read_block(block, b, 8);
            if (!block_has_zero(block, 8)) {
                read_block(block, b, 8);
                copy_eight = 1;
            }
        }
    }
    while (copy_eight) {
        write_block(a, block, 8);
        a += 8;
        b += 8;
        count -= 8;
        if (count < 8) break;
        read_block(block, b, 8);
        if (block_has_zero(block, 8)) break;
        read_block(block, b, 8);
    }
    while (count != 0) {
        uint8_t value = read_byte(b);
        ++b;
        write_byte(a, value);
        ++a;
        --count;
        if (value == 0) {
            while (count != 0) {
                write_byte(a, 0);
                ++a;
                --count;
            }
            break;
        }
    }
    return destination;
}

/* 002d61c0: scalar last-match search; target0 returns the terminating NUL. */
char *ps2Strrchr(const char *source, int32_t value)
{
    const uint8_t *a = (const uint8_t *)source;
    const uint8_t *last = (const uint8_t *)0;
    uint8_t target = (uint8_t)value;
    for (;;) {
        uint8_t byte = read_byte(a);
        if (byte == 0) return target == 0 ? (char *)a : (char *)last;
        if (byte == target) last = a;
        ++a;
    }
}

/* 002d6210: naïve byte search; each failed candidate rereads needle[0]. */
char *ps2Strstr(const char *source, const char *needle)
{
    const uint8_t *a = (const uint8_t *)source;
    const uint8_t *b = (const uint8_t *)needle;
    uint8_t current = read_byte(a);
    uint8_t first = read_byte(b); /* Executed even when source is empty. */
    if (current == 0) return first == 0 ? (char *)a : (char *)0;
    if (first == 0) return (char *)a;
    for (;;) {
        current = read_byte(a);
        if (current == first) {
            uint32_t index = 1;
            for (;;) {
                uint8_t wanted = read_byte(b + index);
                if (wanted == 0) return (char *)a;
                current = read_byte(a + index);
                if (current != wanted) break;
                ++index;
            }
        }
        ++a;
        current = read_byte(a);
        if (current == 0) return (char *)0;
        first = read_byte(b);
    }
}

/* 002d1e08: output store follows all continuation reads; shifts mask to5bits. */
const uint8_t *ps2ReadUleb128(const uint8_t *source, uint32_t *result)
{
    uint32_t value = 0, shift = 0;
    uint8_t byte;
    do {
        byte = read_byte(source);
        ++source;
        value |= (uint32_t)(byte & 0x7fu) << (shift & 31u);
        shift += 7;
    } while ((byte & 0x80u) != 0);
    *result = value;
    return source;
}

static int32_t signed_word(uint32_t bits)
{
    return bits <= (uint32_t)INT32_MAX ? (int32_t)bits :
        -1 - (int32_t)(UINT32_MAX - bits);
}

/* 002d1e50: sign extension only if total shift<32 and final byte bit6 set. */
const uint8_t *ps2ReadSleb128(const uint8_t *source, int32_t *result)
{
    uint32_t value = 0, shift = 0;
    uint8_t byte;
    do {
        byte = read_byte(source);
        ++source;
        value |= (uint32_t)(byte & 0x7fu) << (shift & 31u);
        shift += 7;
    } while ((byte & 0x80u) != 0);
    if (shift < 32 && (byte & 0x40u) != 0)
        value |= UINT32_MAX << shift;
    *result = signed_word(value);
    return source;
}
