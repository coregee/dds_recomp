#include "dev_packets.h"
#include "dev_console.h"
#include "graphics_sync.h"
#include "draw_dma.h"
#include "draw_consumer_support.h"
#include <string.h>

static uint32_t word(uint32_t address)
{
    uint32_t value;
    memcpy(&value, nocturneResolveDevPacketAddress(address), 4);
    return value;
}
static uint16_t half(uint32_t address)
{
    uint16_t value;
    memcpy(&value, nocturneResolveDevPacketAddress(address), 2);
    return value;
}
static uint8_t byte(uint32_t address)
{
    return *(uint8_t *)nocturneResolveDevPacketAddress(address);
}
static void put_word(uint32_t address, uint32_t value)
{
    memcpy(nocturneResolveDevPacketAddress(address), &value, 4);
}
static void put_half(uint32_t address, uint16_t value)
{
    memcpy(nocturneResolveDevPacketAddress(address), &value, 2);
}
static void put_qword(uint32_t address, uint64_t value)
{
    memcpy(nocturneResolveDevPacketAddress(address), &value, 8);
}
static int64_t signed_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? (int64_t)value - INT64_C(0x100000000) : value;
}
static int32_t signed_half(uint16_t value)
{
    return value & UINT16_C(0x8000) ? (int32_t)value - 65536 : value;
}
static uint32_t shift_word(uint32_t value, uint32_t bits)
{
    return (value >> bits) | ((value & UINT32_C(0x80000000)) ? UINT32_MAX << (32 - bits) : 0);
}

/* 002ab0c8: load the pointer before the return-delay qword read. */
uint64_t ps2TextureGetRegister(uint64_t texture)
{
    uint32_t record = word((uint32_t)texture + 40);
    uint64_t value;
    memcpy(&value, nocturneResolveDevPacketAddress(record + 32), 8);
    return value;
}

/* 002bcb40: the delta is cached before DMA, base and buffer selection are late.
 * Callers ignore the incidental original V0, including the empty return. */
void ps2DevFlushPackets(uint64_t handle)
{
    uint32_t address = (uint32_t)handle;
    ps2DevFinalizeGlyphPacket(handle);
    uint32_t delta = word(address + 8) - word(address + 4);
    if (!shift_word(delta, 3)) return;
    uint32_t channel = word(address + 12);
    (void)ps2DmaWaitOrStatus((uint64_t)signed_word(channel), 0);
    uint32_t control = nocturneDmaRead32(channel);
    nocturneDmaWrite32(channel, control | UINT32_C(0x40));
    nocturneDevPacketSync();
    uint32_t base = word(address + 4);
    ps2DmaSendNormal((uint64_t)signed_word(channel), base & UINT32_C(0x0fffffff),
                    (uint64_t)signed_word(shift_word(delta, 4)));
    uint32_t selection = half(address + 28) ^ 1;
    put_half(address + 28, (uint16_t)selection);
    uint32_t next = word(address + 16 + (selection << 2));
    put_word(address + 4, next);
    put_word(address, next + 16);
    put_word(address + 8, next);
    (void)ps2GsSyncPath(0);
}

/* 002bcc10: finalizer/flush are real callees. Coordinates wrap as words and
 * are zero-extended only after packing. Handle writes precede packet writes. */
void ps2DevBackgroundPacket(uint64_t node, uint64_t handle)
{
    uint32_t address = (uint32_t)handle, object = (uint32_t)node;
    ps2DevFinalizeGlyphPacket(handle);
    uint32_t segment = word(address + 8);
    uint32_t required = segment - word(address + 4) + 128;
    if (signed_word(word(address + 24)) < signed_word(required)) {
        ps2DevFlushPackets(handle);
        segment = word(address + 8);
    }
    int32_t width = signed_half(half(object + 12));
    int32_t height = signed_half(half(object + 14));
    uint32_t line_height = half(address + 30);
    uint32_t y = half(object + 10);
    uint32_t x = half(object + 8);
    uint32_t flags = byte(object + 20);
    uint32_t width_pixels = ((uint32_t)width * 3) << 6;
    uint32_t row_pixels = (uint32_t)height * line_height;
    uint32_t start = ((x + UINT32_C(0xffd0)) & UINT32_C(0xffff)) | (y << 16);
    uint32_t extent = ((width_pixels + 112) & UINT32_C(0xffff)) | (row_pixels << 16);
    if (flags & 4) {
        extent += UINT32_C(0x00700000);
        start += UINT32_C(0xffd00000);
    } else {
        extent += UINT32_C(0x00380000);
        start += UINT32_C(0xffe80000);
    }
    uint32_t end = start + extent;
    put_word(address, segment + 80);
    put_word(address + 8, segment + 64);
    put_qword(segment, UINT64_C(0x5400000000008001));
    put_qword(segment + 8, UINT64_C(0x5510));
    put_qword(segment + 16, UINT64_C(0x146));
    put_qword(segment + 24, UINT64_C(0x30000000));
    put_qword(segment + 32, start);
    put_qword(segment + 40, end);
    put_qword(segment + 48, UINT64_C(0x156));
}

/* 002bcee8: uncached-address word construction and signed word halving.
 * Texture/header loads and stores retain their original order. */
void ps2DevInitializePackets(uint64_t handle, uint64_t buffer, uint64_t size)
{
    uint32_t address = (uint32_t)handle;
    uint32_t base = ((uint32_t)buffer & UINT32_C(0x0fffffff)) | UINT32_C(0x30000000);
    uint32_t half_size = shift_word((uint32_t)size, 1);
    put_word(address + 24, half_size);
    put_word(address + 16, base);
    put_word(address + 20, base + half_size);
    put_word(address + 4, base);
    put_half(address + 28, 0);
    uint64_t texture = ps2TextureGetRegister((uint64_t)signed_word(word(UINT32_C(0x5520e4))));
    put_qword(base, UINT64_C(0x10ab400000008005));
    put_word(address + 8, base + 96);
    put_qword(base + 8, 14);
    put_word(address, base + 112);
    put_qword(base + 16, 68);
    put_qword(base + 24, 66);
    put_qword(base + 32, UINT64_C(0x3000d));
    put_qword(base + 40, 71);
    put_qword(base + 48, 0);
    put_qword(base + 56, 8);
    put_qword(base + 64, 1);
    put_qword(base + 72, 20);
    put_qword(base + 80, texture);
    put_qword(base + 88, 6);
    put_word(address + 12, (uint32_t)ps2DmaGetChannel(2));
}
