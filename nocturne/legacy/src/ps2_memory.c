#include "ps2_memory.h"

#include <limits.h>
#if defined(NOCTURNE_MODEL_CONTEXT_CHILD_PROFILE)
#include "model_renderer.h"
extern uint32_t g_modelContextChildActive;
extern void nocturneModelContextChildMemsetCpu(uint32_t byte,uint32_t count);
static void copyCpu(unsigned gpr,const uint8_t block[16])
{
    if(g_modelContextChildActive){
        uint32_t words[4]={0,0,0,0};
        for(unsigned k=0;k<16;k++)words[k/4]|=(uint32_t)block[k]<<((k%4)*8);
        EE_RENDERER_CPU_QUAD(gpr,words);
    }
}
#else
#define copyCpu(gpr,block) ((void)0)
#endif

_Static_assert(CHAR_BIT == 8, "PS2 byte width");

/* Explicit accesses keep the compiler from folding these recovered loops
 * into host libc calls or eliminating original redundant loads/self stores.
 * A snapshot represents one EE LD/LQ stage; it is complete before its SD/SQ
 * stage. Access widths/atomicity are outside the ordinary-RAM contract. */
static uint8_t ps2ReadByte(const uint8_t *source)
{
    return *(const volatile uint8_t *)source;
}

static void ps2WriteByte(uint8_t *destination, uint8_t value)
{
    *(volatile uint8_t *)destination = value;
}

static void ps2ReadBlock(uint8_t block[16], const uint8_t *source,
    uint32_t width)
{
    for (uint32_t i = 0; i < width; ++i)
        block[i] = ps2ReadByte(source + i);
}

static void ps2WriteBlock(uint8_t *destination, const uint8_t block[16],
    uint32_t width)
{
    for (uint32_t i = 0; i < width; ++i)
        ps2WriteByte(destination + i, block[i]);
}

static int ps2BlocksEqual(const uint8_t left[16], const uint8_t right[16],
    uint32_t width)
{
    for (uint32_t i = 0; i < width; ++i) {
        if (left[i] != right[i])
            return 0;
    }
    return 1;
}

static int ps2BlockHasZero(const uint8_t block[16], uint32_t width)
{
    if (width == 16) {
        /* PSUBB is bytewise wrapping subtraction, followed by ~x & 0x80.
         * No borrow crosses a byte lane in the original 128-bit detector. */
        for (uint32_t i = 0; i < 16; ++i) {
            uint8_t difference = (uint8_t)(block[i] - 1u);
            if ((difference & (uint8_t)~block[i] & 0x80u) != 0)
                return 1;
        }
        return 0;
    }

    /* The LD path instead uses one wrapping 64-bit subtraction. */
    uint64_t word = 0;
    for (uint32_t i = 0; i < 8; ++i)
        word |= (uint64_t)block[i] << (i * 8u);
    return ((word - UINT64_C(0x0101010101010101)) & ~word &
        UINT64_C(0x8080808080808080)) != 0;
}

/* Shared only by the identical forward sections of 002d43a4/002d4454.
 * The 8-byte tail is available ONLY after entering the aligned >=32 path. */
static void ps2CopyForward(uint8_t *destination, const uint8_t *source,
    uint32_t count)
{
    if (count >= 32 &&
        (((uintptr_t)destination | (uintptr_t)source) & 15u) == 0) {
        uint8_t block[16];
        do {
            ps2ReadBlock(block, source, 16);
            copyCpu(3,block);
            ps2WriteBlock(destination, block, 16);
            source += 16;
            destination += 16;

            /* The second load follows the first store, including overlap. */
            ps2ReadBlock(block, source, 16);
            copyCpu(2,block);
            ps2WriteBlock(destination, block, 16);
            source += 16;
            destination += 16;
            count -= 32;
        } while (count >= 32);

        while (count >= 8) {
            ps2ReadBlock(block, source, 8);
            ps2WriteBlock(destination, block, 8);
            source += 8;
            destination += 8;
            count -= 8;
        }
    }

    while (count != 0) {
        uint8_t value = ps2ReadByte(source);
        ps2WriteByte(destination, value);
        ++source;
        ++destination;
        --count;
    }
}

/* 002d4310: aligned 16-byte equality probes, then unsigned byte difference. */
int32_t ps2Memcmp(const void *left, const void *right, uint32_t count)
{
    const uint8_t *a = (const uint8_t *)left;
    const uint8_t *b = (const uint8_t *)right;
    if (count >= 16 && (((uintptr_t)a | (uintptr_t)b) & 15u) == 0) {
        uint8_t a_block[16], b_block[16];
        do {
            ps2ReadBlock(a_block, a, 16);
            ps2ReadBlock(b_block, b, 16);
            if (!ps2BlocksEqual(a_block, b_block, 16))
                break; /* Original rewinds A0 and leaves A1/count in place. */
            a += 16;
            b += 16;
            count -= 16;
        } while (count >= 16);
    }

    while (count != 0) {
        uint8_t a_byte = ps2ReadByte(a);
        uint8_t b_byte = ps2ReadByte(b);
        if (a_byte != b_byte)
            return (int32_t)a_byte - (int32_t)b_byte;
        ++a;
        ++b;
        --count;
    }
    return 0;
}

/* 002d43a4: always forward, with original per-block overlap behavior. */
void *ps2Memcpy(void *destination, const void *source, uint32_t count)
{
    ps2CopyForward((uint8_t *)destination, (const uint8_t *)source, count);
    return destination;
}

/* 002d4454: reverse bytes iff source < destination < source + count. */
void *ps2Memmove(void *destination, const void *source, uint32_t count)
{
    uint8_t *a = (uint8_t *)destination;
    const uint8_t *b = (const uint8_t *)source;
    uintptr_t a_address = (uintptr_t)a;
    uintptr_t b_address = (uintptr_t)b;
    if (b_address < a_address && a_address < b_address + count) {
        a += count;
        b += count;
        while (count != 0) {
            --a;
            --b;
            uint8_t value = ps2ReadByte(b);
            ps2WriteByte(a, value);
            --count;
        }
    } else {
        ps2CopyForward(a, b, count);
    }
    return destination;
}

/* 002d4558: truncate value to one byte; aligned SQ pairs then SDs then SBs. */
void *ps2Memset(void *destination, int32_t value, uint32_t count)
{
    uint8_t *a = (uint8_t *)destination;
    uint8_t byte = (uint8_t)value;
    if (count >= 8 && ((uintptr_t)a & 15u) == 0) {
#if defined(NOCTURNE_MODEL_CONTEXT_CHILD_PROFILE)
        if(g_modelContextChildActive)nocturneModelContextChildMemsetCpu(byte,count);
#endif
        uint8_t block[16];
        for (uint32_t i = 0; i < 16; ++i)
            block[i] = byte;
        while (count >= 32) {
            ps2WriteBlock(a, block, 16);
            a += 16;
            ps2WriteBlock(a, block, 16);
            a += 16;
            count -= 32;
        }
        while (count >= 8) {
            ps2WriteBlock(a, block, 8);
            a += 8;
            count -= 8;
        }
    }
    while (count != 0) {
        ps2WriteByte(a, byte);
        ++a;
        --count;
    }
    return destination;
}

/* 002d5ab4: signed LB equality tests; final LBU difference is unsigned. */
int32_t ps2Strcmp(const char *left, const char *right)
{
    const uint8_t *a = (const uint8_t *)left;
    const uint8_t *b = (const uint8_t *)right;
    uintptr_t alignment = (uintptr_t)a | (uintptr_t)b;
    if ((alignment & 7u) == 0) {
        uint8_t a_block[16], b_block[16];
        uint32_t width = (alignment & 15u) == 0 ? 16u : 8u;

        /* The branch delay slot reads B's first 8 bytes on both fast paths. */
        ps2ReadBlock(b_block, b, 8);
        ps2ReadBlock(a_block, a, width);
        if (width == 16)
            ps2ReadBlock(b_block, b, 16);
        if (ps2BlocksEqual(a_block, b_block, width)) {
            /* Initial equal block is read again for the zero detector. */
            ps2ReadBlock(a_block, a, width);
            for (;;) {
                if (ps2BlockHasZero(a_block, width))
                    return 0;
                a += width;
                b += width;
                ps2ReadBlock(a_block, a, width);
                ps2ReadBlock(b_block, b, width);
                if (!ps2BlocksEqual(a_block, b_block, width))
                    break;
            }
        }
    }

    /* Preserve scalar rereads: initial LB, LBU in the branch delay slot,
     * right LB on nonzero left, and final LBU operands on a mismatch. Equality
     * of signed bytes is identical to equality of their unsigned raw bytes. */
    uint8_t a_byte = ps2ReadByte(a);
    for (;;) {
        uint8_t a_again = ps2ReadByte(a);
        if (a_byte == 0) {
            uint8_t b_final = ps2ReadByte(b);
            return (int32_t)a_again - (int32_t)b_final;
        }
        uint8_t b_byte = ps2ReadByte(b);
        if (a_again != b_byte) {
            uint8_t a_final = ps2ReadByte(a);
            uint8_t b_final = ps2ReadByte(b);
            return (int32_t)a_final - (int32_t)b_final;
        }
        ++a;
        ++b;
        a_byte = ps2ReadByte(a);
    }
}

/* 002d5bf8: full nonzero blocks, then scalar copy through the first NUL. */
char *ps2Strcpy(char *destination, const char *source)
{
    uint8_t *a = (uint8_t *)destination;
    const uint8_t *b = (const uint8_t *)source;
    uintptr_t alignment = (uintptr_t)a | (uintptr_t)b;
    if ((alignment & 7u) == 0) {
        uint8_t block[16];
        uint32_t width = (alignment & 15u) == 0 ? 16u : 8u;
        for (;;) {
            ps2ReadBlock(block, b, width);
            if (ps2BlockHasZero(block, width))
                break;
            ps2WriteBlock(a, block, width);
            a += width;
            b += width;
        }
    }
    for (;;) {
        uint8_t value = ps2ReadByte(b);
        ++b;
        ps2WriteByte(a, value);
        ++a;
        if (value == 0)
            return destination;
    }
}

/* 002d5d0c: path selection is fixed from the original pointer alignment. */
uint32_t ps2Strlen(const char *source)
{
    const uint8_t *a = (const uint8_t *)source;
    uint32_t length = 0;
    if (((uintptr_t)a & 7u) == 0) {
        uint8_t block[16];
        uint32_t width = ((uintptr_t)a & 15u) == 0 ? 16u : 8u;
        for (;;) {
            ps2ReadBlock(block, a, width);
            if (ps2BlockHasZero(block, width))
                break;
            a += width;
            length += width;
        }
    }
    while (ps2ReadByte(a) != 0) {
        ++a;
        ++length;
    }
    return length;
}
