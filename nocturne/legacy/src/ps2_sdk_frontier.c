#include "ps2_sdk_frontier.h"

#include <limits.h>
#include <stddef.h>
#include <string.h>

_Static_assert(CHAR_BIT == 8 && sizeof(uint32_t) == 4 && sizeof(uint64_t) == 8,
    "original byte and word widths");

static uint32_t load_word(const uint8_t *source)
{
    uint32_t value;
    memcpy(&value, source, sizeof(value));
    return value;
}

static void store_word(void *destination, uint32_t value)
{
    memcpy(destination, &value, sizeof(value));
}

static int32_t signed_word(uint32_t value)
{
    return value <= INT32_MAX ? (int32_t)value :
        (int32_t)((int64_t)value - INT64_C(0x100000000));
}

int32_t ps2WidenByte(const void *ignored_state, uint32_t *output,
    const uint8_t *source, uint64_t available)
{
    uint32_t scratch;
    uint32_t value;
    uint32_t *destination = output != NULL ? output : &scratch;
    (void)ignored_state;
    if (source == NULL) return 0;
    if (available == 0) return -1;
    value = *source;
    store_word(destination, value);
    return *source != 0 ? 1 : 0;
}

const void *ps2Memchr(const void *source, int32_t value, uint32_t count)
{
    const uint8_t *cursor = (const uint8_t *)source;
    uint8_t target = (uint8_t)value;
    if (count >= 16u && ((uintptr_t)cursor & 15u) == 0u) {
        do {
            uint8_t block[16];
            uint32_t lane;
            int match = 0;
            memcpy(block, cursor, sizeof(block));
            for (lane = 0; lane < 16u; ++lane) {
                if (block[lane] == target) match = 1;
            }
            if (match != 0) break;
            count -= 16u;
            cursor += 16;
        } while (count >= 16u);
    }
    while (count != 0u) {
        if (*cursor == target) return cursor;
        --count;
        ++cursor;
    }
    return NULL;
}

uint32_t ps2CountLeadingZeroBits(int32_t value)
{
    uint32_t bits = (uint32_t)value;
    uint32_t count = 0;
    while (count < 32u && (bits & UINT32_C(0x80000000)) == 0u) {
        bits <<= 1;
        ++count;
    }
    return count;
}

uint32_t ps2RemoveTrailingZeroBits(uint32_t *word)
{
    uint32_t bits = load_word((const uint8_t *)word);
    uint32_t count = 0;
    if (bits == 0u) return 32;
    if ((bits & 1u) != 0u) return 0;
    do {
        bits >>= 1;
        ++count;
    } while ((bits & 1u) == 0u);
    store_word(word, bits);
    return count;
}

int32_t ps2CompareLimbArrays(const void *left, const void *right)
{
    const uint8_t *left_bytes = (const uint8_t *)left;
    const uint8_t *right_bytes = (const uint8_t *)right;
    uint32_t left_count = load_word(left_bytes + 16);
    uint32_t right_count = load_word(right_bytes + 16);
    uint32_t difference = left_count - right_count;
    size_t offset;
    if (difference != 0u) return signed_word(difference);
    offset = 16u + (size_t)left_count * 4u;
    do {
        uint32_t left_limb = load_word(left_bytes + offset);
        uint32_t right_limb = load_word(right_bytes + offset);
        if (left_limb != right_limb) return left_limb < right_limb ? -1 : 1;
        if (offset <= 20u) break;
        offset -= 4u;
    } while (1);
    return 0;
}

uint32_t ps2IsDoubleInfBits(uint64_t bits)
{
    return (bits & UINT64_C(0x7fffffffffffffff)) ==
        UINT64_C(0x7ff0000000000000) ? 1u : 0u;
}

uint32_t ps2IsDoubleNaNBits(uint64_t bits)
{
    uint64_t magnitude = bits & UINT64_C(0x7fffffffffffffff);
    return magnitude > UINT64_C(0x7ff0000000000000) ? 1u : 0u;
}
