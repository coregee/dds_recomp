/* Reconstruction of the original libdma wait/stop/send/receive path.
 * Volatile reads/writes and printf output are explicit platform boundaries.
 * Actual recovered address-normalization and interrupt helpers are called. */
#include <stdint.h>
#include "draw_consumer_support.h"
#include "material_fiveword_pool.h"
#include "draw_dma.h"
extern uint32_t nocturneDmaRead32(uint32_t address);
extern void nocturneDmaWrite32(uint32_t address, uint32_t value);
extern void nocturneDmaTimeoutDiagnostic(uint32_t format_address);

static uint64_t sign_word(uint32_t value)
{
    return (value & UINT32_C(0x80000000))
        ? UINT64_C(0xffffffff00000000) | value : value;
}

/* 002c9ee0, 152 bytes. Even the otherwise unused DMAC control read occurs. */
uint64_t ps2DmaStop(uint64_t channel)
{
    uint32_t address = (uint32_t)channel;
    uint32_t enabled = ps2KernelDisableInterrupts();
    uint32_t saved = nocturneDmaRead32(UINT32_C(0x1000f520));
    if (!(saved & UINT32_C(0x10000)))
        nocturneDmaWrite32(UINT32_C(0x1000f590), saved | UINT32_C(0x10000));
    (void)nocturneDmaRead32(UINT32_C(0x1000e000));
    uint32_t control = nocturneDmaRead32(address);
    nocturneDmaWrite32(address, control & UINT32_C(0xfffffeff));
    nocturneDmaWrite32(UINT32_C(0x1000f590), saved);
    if (enabled) (void)ps2KernelEnableInterrupts();
    return sign_word(control);
}

/* 002c9748, 112 bytes. ADDIU countdown wraps and sign extends as a word.
 * Full timeout branch is reconstructed; bounded fixtures do not claim to have
 * executed the sixteen-million-read timeout or the original printf library. */
void ps2DmaWait(uint64_t channel)
{
    uint32_t address = (uint32_t)channel;
    if (nocturneDmaRead32(address) & UINT32_C(0x100)) {
        uint32_t remaining = UINT32_C(0xffffff);
        for (;;) {
            if (remaining & UINT32_C(0x80000000)) {
                nocturneDmaTimeoutDiagnostic(UINT32_C(0x54a8f0));
                (void)ps2DmaStop(channel);
            }
            uint32_t busy = nocturneDmaRead32(address) & UINT32_C(0x100);
            remaining--;
            if (!busy) break;
        }
    }
}

/* 002c9bd0, 104 bytes. Sentinel check precedes the control reload. */
void ps2DmaSendChain(uint64_t channel, uint64_t tag_address)
{
    uint32_t address = (uint32_t)channel;
    uint32_t normalized = (uint32_t)ps2DmaNormalizeAddress(tag_address);
    ps2DmaWait(channel);
    if (nocturneDmaRead32(address + 0x30) != UINT32_MAX)
        nocturneDmaWrite32(address + 0x30, normalized);
    uint32_t control = nocturneDmaRead32(address);
    nocturneDmaWrite32(address + 0x20, 0);
    nocturneDmaWrite32(address, (control & UINT32_C(0xfffffff3)) | UINT32_C(0x105));
}

/* 002c9d70, 124 bytes. Count stores its low word; direction bit0 is cleared. */
void ps2DmaReceive(uint64_t channel, uint64_t buffer, uint64_t count)
{
    uint32_t address = (uint32_t)channel;
    uint32_t normalized = (uint32_t)ps2DmaNormalizeAddress(buffer);
    ps2DmaWait(channel);
    if (nocturneDmaRead32(address + 0x10) != UINT32_MAX)
        nocturneDmaWrite32(address + 0x10, normalized);
    uint32_t control = nocturneDmaRead32(address);
    nocturneDmaWrite32(address + 0x20, (uint32_t)count);
    nocturneDmaWrite32(address, (control & UINT32_C(0xfffffff2)) | UINT32_C(0x100));
}
