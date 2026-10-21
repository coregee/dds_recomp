#include "graphics_sync.h"
#include "draw_dma.h"
#include "draw_consumer_support.h"

static uint64_t sign_word(uint32_t value)
{
    return (value & UINT32_C(0x80000000)) ? UINT64_C(0xffffffff00000000) | value : value;
}

/* 002c9e70: mode comparison consumes the complete EE register. */
uint64_t ps2DmaWaitOrStatus(uint64_t channel, uint64_t mode)
{
    if (mode == 1) return (nocturneDmaRead32((uint32_t)channel) >> 8) & 1;
    ps2DmaWait(channel);
    return 0;
}

/* 002c9c38: normal send keeps a late control read after the address sentinel. */
void ps2DmaSendNormal(uint64_t channel, uint64_t buffer, uint64_t count)
{
    uint32_t address = (uint32_t)channel;
    uint32_t normalized = (uint32_t)ps2DmaNormalizeAddress(buffer);
    ps2DmaWait(channel);
    if (nocturneDmaRead32(address + 16) != UINT32_MAX)
        nocturneDmaWrite32(address + 16, normalized);
    uint32_t control = nocturneDmaRead32(address);
    nocturneDmaWrite32(address + 32, (uint32_t)count);
    nocturneDmaWrite32(address, (control & UINT32_C(0xfffffff3)) | UINT32_C(0x101));
}

static uint32_t stage_value(uint32_t stage)
{
    static const uint32_t addresses[5] = {0x10009000,0x1000a000,0x10003c00,0,0x10003020};
    return stage == 3 ? nocturneGraphicsReadVuControl(13) : nocturneDmaRead32(addresses[stage]);
}

static void timeout_diagnostics(uint32_t stage)
{
    static const uint32_t formats[5] = {0x54a428,0x54a508,0x54a538,0x54a568,0x54a590};
    static const uint32_t registers[10] = {0x10009000,0x10009030,0x10009010,0x10009020,
        0x1000a000,0x1000a030,0x1000a010,0x1000a020,0x10003c00,0x10003020};
    static const uint32_t detail_formats[10] = {0x54a458,0x54a468,0x54a478,0x54a488,
        0x54a498,0x54a4a8,0x54a4b8,0x54a4c8,0x54a4d8,0x54a4f0};
    nocturneGraphicsDiagnostic(formats[stage], 0, 0);
    for (uint32_t i = 0; i < 10; ++i)
        nocturneGraphicsDiagnostic(detail_formats[i], 1, sign_word(nocturneDmaRead32(registers[i])));
}

/* 002c8898: common ADDIU word counter survives transitions between stages.
 * The timeout branch is reconstructed; bounded comparisons do not execute its
 * sixteen-million-poll wait or the original printf formatter. */
uint64_t ps2GsSyncPath(uint64_t mode)
{
    static const uint32_t masks[5] = {0x100,0x100,0x1f000003,0x100,0xc00};
    if (mode) {
        uint32_t result = 0;
        for (uint32_t i = 0; i < 5; ++i)
            if (stage_value(i) & masks[i]) result |= UINT32_C(1) << i;
        return result;
    }
    uint32_t polls = 0;
    for (uint32_t i = 0; i < 5; ++i) {
        uint32_t value = stage_value(i);
        while (value & masks[i]) {
            uint32_t expired = sign_word(polls) > UINT64_C(0x1000000);
            ++polls; /* Delay slot runs even when the timeout branch is taken. */
            if (expired) {
                timeout_diagnostics(i);
                return UINT64_MAX;
            }
            value = stage_value(i);
        }
    }
    return 0;
}
