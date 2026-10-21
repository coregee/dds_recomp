#include "dev_renderer.h"
#include "dev_packets.h"
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
static uint64_t sign_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000) | value : value;
}
static uint64_t sign_half(uint16_t value)
{
    return value & UINT16_C(0x8000) ? UINT64_C(0xffffffffffff0000) | value : value;
}
static int64_t signed_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? (int64_t)value - INT64_C(0x100000000) : value;
}

/* 002bcd40: dimensions are loaded late after each cell/row, including skips.
 * Coordinate DADDU/DADDIU operations are full64; buffer arithmetic wraps32. */
void ps2DevRenderGlyphCells(uint64_t node, uint64_t handle)
{
    uint32_t object = (uint32_t)node, address = (uint32_t)handle;
    uint8_t flags = byte(object + 20);
    if (flags & 1) return;
    put_half(address + 30, (flags & 4) ? 192 : 96);
    if (byte(object + 20) & 2) ps2DevBackgroundPacket(node, handle);
    uint32_t advance = ((uint32_t)half(address + 30) << 16) | UINT32_C(0xc0);
    uint32_t current = word(address);
    uint32_t base = word(address + 4);
    uint32_t glyph = word(object + 28);
    uint32_t y = half(object + 10), row = 0;
    do {
        uint32_t column = 0;
        uint64_t start = half(object + 8) | (y << 16);
        uint64_t end = start + sign_word(advance);
        do {
            uint32_t character = byte(glyph), attribute = byte(glyph + 1);
            glyph += 2;
            if (character >= 32) {
                if (signed_word(word(address + 24)) < signed_word(current - base + 80)) {
                    put_word(address, current);
                    ps2DevFlushPackets(handle);
                    current = word(address);
                    base = word(address + 4);
                }
                uint64_t uv = word(UINT32_C(0x529880) + (character << 2));
                uint64_t color = word(UINT32_C(0x529a80) + (attribute << 2));
                put_qword(current, color);
                put_qword(current + 8, uv);
                put_qword(current + 16, start);
                put_qword(current + 24, uv + UINT64_C(0x00c000c0));
                put_qword(current + 32, end);
                current += 40;
            }
            ++column;
            end += 192;
            start += 192;
        } while (sign_word(column) != sign_half(half(object + 12)));
        uint32_t line_height = half(address + 30);
        ++row;
        uint16_t height = half(object + 14);
        y += line_height;
        if (sign_word(row) == sign_half(height)) break;
    } while (1);
    put_word(address, current);
}

/* 002bcfd0: global head is reloaded after actual initialization, next is loaded
 * after rendering each node. Original-address stack relocation retains the
 * handle+1040 and buffer+30 layout and observable DMA addresses. */
void ps2DevRenderConsoleList(void)
{
    uint32_t head = word(UINT32_C(0x5518f8));
    uint32_t frame = nocturneDevRendererFrameEnter(UINT32_C(0x1080));
    if (head) {
        uint32_t handle = frame + UINT32_C(0x1040);
        ps2DevInitializePackets(handle, frame + UINT32_C(0x30), UINT32_C(0x1000));
        head = word(UINT32_C(0x5518f8));
        while (head) {
            ps2DevRenderGlyphCells(sign_word(head), sign_word(handle));
            head = word(head + 4);
        }
        ps2DevFlushPackets(sign_word(handle));
    }
    nocturneDevRendererFrameLeave(frame, UINT32_C(0x1080));
}
