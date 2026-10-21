#include "ps2_sdk_neighbors.h"

#include <float.h>
#include <stddef.h>
#include <string.h>

_Static_assert(sizeof(float) == sizeof(uint32_t), "32-bit float transport");
_Static_assert(FLT_RADIX == 2 && FLT_MANT_DIG == 24 && FLT_MAX_EXP == 128,
    "binary32 host float representation");

static int32_t signed_byte(uint8_t value)
{
    return value < 128u ? (int32_t)value : (int32_t)value - 256;
}

static uint32_t load_word(const uint8_t *address)
{
    uint32_t result;
    memcpy(&result, address, sizeof(result));
    return result;
}

static const uint8_t *next_record(const uint8_t *record, uint32_t length)
{
    uint32_t step = length + 4u;
    int64_t displacement = step <= INT32_MAX ? (int64_t)step :
        (int64_t)step - INT64_C(0x100000000);
    return record + (ptrdiff_t)displacement;
}

int32_t ps2Strcasecmp(const char *left, const char *right)
{
    const uint8_t *left_bytes = (const uint8_t *)left;
    const uint8_t *right_bytes = (const uint8_t *)right;
    int32_t left_signed = signed_byte(*left_bytes);

    while (left_signed != 0) {
        int32_t right_signed = signed_byte(*right_bytes);
        uint8_t left_class = g_ps2CharacterClasses[left_signed];
        uint8_t right_class = g_ps2CharacterClasses[right_signed];
        int32_t left_folded = left_signed;
        int32_t right_folded = right_signed;
        if ((left_class & 1u) != 0u) left_folded += 32;
        if ((right_class & 1u) != 0u) right_folded += 32;
        if (left_folded != right_folded) break;
        ++left_bytes;
        ++right_bytes;
        left_signed = signed_byte(*left_bytes);
    }

    /* The original rereads both terminal/differing bytes with LBU. */
    {
        uint32_t left_value = *left_bytes;
        uint32_t right_value = *right_bytes;
        uint8_t left_class = g_ps2CharacterClasses[left_value];
        uint8_t right_class = g_ps2CharacterClasses[right_value];
        if ((left_class & 1u) != 0u) left_value += 32u;
        if ((right_class & 1u) != 0u) right_value += 32u;
        return (int32_t)left_value - (int32_t)right_value;
    }
}

float ps2AbsFloat(float value)
{
    uint32_t bits;
    float result;
    memcpy(&bits, &value, sizeof(bits));
    bits &= UINT32_C(0x7fffffff);
    memcpy(&result, &bits, sizeof(result));
    return result;
}

float ps2CopySignFloat(float magnitude, float sign)
{
    uint32_t magnitude_bits;
    uint32_t sign_bits;
    float result;
    memcpy(&magnitude_bits, &magnitude, sizeof(magnitude_bits));
    memcpy(&sign_bits, &sign, sizeof(sign_bits));
    magnitude_bits = (magnitude_bits & UINT32_C(0x7fffffff)) |
        (sign_bits & UINT32_C(0x80000000));
    memcpy(&result, &magnitude_bits, sizeof(result));
    return result;
}

uint32_t ps2CountRuntimeRangeRecords(const void *records)
{
    const uint8_t *record = (const uint8_t *)records;
    uint32_t length = load_word(record);
    uint32_t count = 0;
    while (length != 0u) {
        uint32_t discriminator = load_word(record + 4);
        if (discriminator != 0u) {
            uint32_t start = load_word(record + 8);
            if (start != 0u) ++count;
        }
        record = next_record(record, length);
        length = load_word(record);
    }
    return count;
}

const void *ps2FindRuntimeRangeRecord(const void *records, uint32_t address)
{
    const uint8_t *record = (const uint8_t *)records;
    uint32_t length = load_word(record);
    while (length != 0u) {
        uint32_t discriminator = load_word(record + 4);
        if (discriminator != 0u) {
            uint32_t start = load_word(record + 8);
            if (start != 0u) {
                uint32_t size = load_word(record + 12);
                if (address - start < size) return record;
            }
        }
        record = next_record(record, length);
        length = load_word(record);
    }
    return NULL;
}

uint8_t *ps2GetRuntimeState(void)
{
    return g_ps2RuntimeState;
}
