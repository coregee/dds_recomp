#include "dev_console.h"
#include "ps2_memory.h"
#include <string.h>

static uint32_t word(uint32_t address)
{
    uint32_t value;
    memcpy(&value, nocturneResolveDevConsoleAddress(address), sizeof value);
    return value;
}
static uint16_t half(uint32_t address)
{
    uint16_t value;
    memcpy(&value, nocturneResolveDevConsoleAddress(address), sizeof value);
    return value;
}
static void put_word(uint32_t address, uint32_t value)
{
    memcpy(nocturneResolveDevConsoleAddress(address), &value, sizeof value);
}
static void put_half(uint32_t address, uint16_t value)
{
    memcpy(nocturneResolveDevConsoleAddress(address), &value, sizeof value);
}
static void put_doubleword(uint32_t address, uint64_t value)
{
    memcpy(nocturneResolveDevConsoleAddress(address), &value, sizeof value);
}
static uint64_t sign_word(uint32_t value)
{
    return (value & UINT32_C(0x80000000)) ? UINT64_C(0xffffffff00000000) | value : value;
}
static int32_t signed_half(uint16_t value)
{
    return (value & UINT16_C(0x8000)) ? (int32_t)value - 65536 : (int32_t)value;
}
static uint32_t arithmetic_right3(uint32_t value)
{
    return (value >> 3) | ((value & UINT32_C(0x80000000)) ? UINT32_C(0xe0000000) : 0);
}

/* 002bd300: SLL/ADDU word wrapping, table load before return-delay store. */
void sdfDevSetPrintAttr(uint64_t control, uint64_t attribute)
{
    uint32_t value = word(UINT32_C(0x529a80) + ((uint32_t)attribute << 2));
    put_word((uint32_t)control + 12, value);
}

/* 002bd318: original order is x,z,y, then a real tail call to the setter.
 * The fifth EE argument is in t0, not a4. */
void sdfDevSetPrintCB(uint64_t control, uint64_t x, uint64_t y,
                     uint64_t z, uint64_t attribute)
{
    uint32_t address = (uint32_t)control;
    put_word(address, (uint32_t)x);
    put_word(address + 8, (uint32_t)z);
    put_word(address + 4, (uint32_t)y);
    sdfDevSetPrintAttr(control, attribute);
}

/* 002bcad0: signed word count and quotient, including negative raw counts. */
void ps2DevFinalizeGlyphPacket(uint64_t handle)
{
    uint32_t address = (uint32_t)handle;
    uint32_t current = word(address);
    uint32_t segment = word(address + 8);
    uint32_t count = arithmetic_right3(current - segment) - 2;
    if (!count) return;
    if (count & 1) current += 8;
    int64_t signed_count = (count & UINT32_C(0x80000000))
        ? (int64_t)count - INT64_C(0x100000000) : count;
    uint64_t quotient = sign_word((uint32_t)(signed_count / 5));
    put_word(address, current + 16);
    put_word(address + 8, current);
    put_doubleword(segment, UINT64_C(0x5400000000008000) | quotient);
    put_doubleword(segment + 8, UINT64_C(0x53531));
}

/* 002bc680: both links are loaded before either neighboring store. */
void ps2DevUnlinkConsole(uint64_t node)
{
    uint32_t address = (uint32_t)node;
    uint32_t previous = word(address);
    uint32_t next = word(address + 4);
    if (previous) put_word(previous + 4, next);
    else put_word(UINT32_C(0x5518f8), next);
    if (next) put_word(next, previous);
}

/* 002bc6e0: ordered cursor resets and signed-halfword product before memset.
 * The tail callee's original sign-extended pointer result is retained. */
uint64_t ps2DevClearConsole(uint64_t node)
{
    uint32_t address = (uint32_t)node;
    put_half(address + 16, 0);
    int32_t width = signed_half(half(address + 12));
    int32_t height = signed_half(half(address + 14));
    put_half(address + 18, 0);
    uint32_t count = (uint32_t)((int64_t)width * height) << 1;
    uint32_t buffer = word(address + 28);
    (void)ps2Memset(nocturneResolveDevConsoleAddress(buffer), 0, count);
    return sign_word(buffer);
}

/* 002bc7e0: scroll through actual recovered memmove/memset implementations. */
void ps2DevAdvanceConsoleLine(uint64_t node)
{
    uint32_t address = (uint32_t)node;
    int32_t height = signed_half(half(address + 14));
    int32_t row = signed_half(half(address + 18));
    uint16_t old_row = half(address + 18);
    if ((uint32_t)row == (uint32_t)height - 1) {
        uint32_t stride = (uint32_t)signed_half(half(address + 12)) << 1;
        uint32_t offset = stride * (uint32_t)row;
        if (row > 0) {
            uint32_t buffer = word(address + 28);
            (void)ps2Memmove(nocturneResolveDevConsoleAddress(buffer),
                            nocturneResolveDevConsoleAddress(buffer + stride), offset);
        }
        uint32_t buffer = word(address + 28);
        (void)ps2Memset(nocturneResolveDevConsoleAddress(buffer + offset), 0, stride);
    } else {
        put_half(address + 18, (uint16_t)(old_row + 1));
    }
    put_half(address + 16, 0);
}
