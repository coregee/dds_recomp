/* Reconstructed from all288 original instructions at002adb98.
 * Hardware register and kernel value boundaries remain external. */
#include "draw_consumer.h"
#include "draw_cleanup.h"
#include "draw_consumer_support.h"
#include "draw_dma.h"
#include "heap_queue.h"
#include "dev_renderer.h"
#include "deferred_drain.h"
#include <string.h>
static uint32_t word(uint32_t address)
{
    uint32_t value;
    memcpy(&value, nocturneResolveDrawConsumerAddress(address), 4);
    return value;
}
static uint8_t byte(uint32_t address)
{
    return *(uint8_t *)nocturneResolveDrawConsumerAddress(address);
}
static void put_word(uint32_t address, uint32_t value)
{
    memcpy(nocturneResolveDrawConsumerAddress(address), &value, 4);
}
static void put_byte(uint32_t address, uint8_t value)
{
    memcpy(nocturneResolveDrawConsumerAddress(address), &value, 1);
}
static uint64_t sign_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000) | value : value;
}
static int64_t signed_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? (int64_t)value - INT64_C(0x100000000) : value;
}
static int aborted(void) { return byte(UINT32_C(0x551884)) != 0; }
void ps2DrawConsumeRequest(void)
{
    nocturneDrawConsumerFrameEnter(UINT32_C(0x60));
    uint32_t record = UINT32_C(0x5293f8) + (word(UINT32_C(0x551890)) << 4);
    uint32_t chain = word(record);
    if (!chain || byte(record + 8) == 2) {
        (void)ps2KernelSignalSema(word(UINT32_C(0x551854)));
    } else {
        uint8_t half = byte(record + 8) ? byte(record + 11) : byte(UINT32_C(0x551839));
        half ^= 1;
        put_byte(UINT32_C(0x55188a), half);
        put_byte(record + 11, half);
        uint8_t frame = byte(UINT32_C(0x551889));
        put_byte(record + 10, frame);
        ps2DrawPrepareFrameState(frame, byte(record + 9));
        (void)ps2KernelSignalSema(word(UINT32_C(0x551854)));
        if (byte(UINT32_C(0x5520b5))) {
            put_byte(UINT32_C(0x5520b5), 0);
            ps2DrawCleanupCompleted();
        }
        uint32_t node = word(record + 4);
        while (node) {
            uint32_t callback = word(node + 4);
            nocturneDrawConsumerCallback(callback, sign_word(node), byte(record + 10));
            node = word(node);
        }
        (void)ps2KernelFlushCache(0);
        uint64_t channel = ps2DmaGetChannel(1);
        uint32_t port = (uint32_t)channel;
        uint32_t control = nocturneDmaRead32(port);
        nocturneDmaWrite32(port, control | UINT32_C(0xc0));
        put_byte(UINT32_C(0x551849), 3);
        ps2DmaSendChain(channel, word(chain + 4) & UINT32_C(0x0fffffff));
        put_word(UINT32_C(0x551894), word(chain + 4));
        for (;;) {
            (void)ps2KernelSleepThread();
            if (aborted()) goto exit_early;
            if ((nocturneDrawConsumerRead16(port + 2) & UINT16_C(0x7000)) == UINT16_C(0x7000)) break;
            uint32_t saved_mask = (uint32_t)ps2GsReadInterruptMask();
            (void)ps2GsSwapInterruptMask(saved_mask | UINT32_C(0x200));
            nocturneDrawConsumerWrite64(UINT32_C(0x12001000), 2);
            control = nocturneDmaRead32(port);
            nocturneDmaWrite32(port, control | UINT32_C(0x100));
            (void)ps2KernelSleepThread();
            uint64_t csr = nocturneDrawConsumerRead64(UINT32_C(0x12001000));
            while (!(csr & 2)) {
                if (aborted()) {
                    (void)ps2GsSwapInterruptMask(saved_mask);
                    goto exit_early;
                }
                csr = nocturneDrawConsumerRead64(UINT32_C(0x12001000));
            }
            nocturneDrawConsumerWrite64(UINT32_C(0x12001000), 0);
            (void)ps2GsSwapInterruptMask(saved_mask);
            control = nocturneDmaRead32(port);
            nocturneDmaWrite32(port, control | UINT32_C(0x100));
            (void)ps2KernelSleepThread();
            uint64_t resume_tag = sign_word(nocturneDmaRead32(port + UINT32_C(0x30)));
            uint32_t vif = nocturneDmaRead32(UINT32_C(0x10003c00));
            uint32_t receive = nocturneDmaRead32(port + UINT32_C(0x10));
            while (vif & 3) {
                if (aborted()) goto exit_early;
                vif = nocturneDmaRead32(UINT32_C(0x10003c00));
            }
            uint32_t gif = nocturneDmaRead32(UINT32_C(0x10003020));
            while (gif & UINT32_C(0x80)) {
                if (aborted()) goto exit_early;
                gif = nocturneDmaRead32(UINT32_C(0x10003020));
            }
            nocturneDmaWrite32(UINT32_C(0x10003000), 8);
            nocturneDmaWrite32(UINT32_C(0x10003c00), UINT32_C(0x800000));
            nocturneDrawConsumerWrite64(UINT32_C(0x12001040), 1);
            nocturneDmaWrite32(UINT32_C(0x10003000), 0);
            uint32_t remaining = word(receive), cursor = word(receive + 4);
            while (signed_word(remaining) > 0) {
                uint32_t chunk = signed_word(remaining) > INT64_C(0xf000) ? UINT32_C(0xf000) : remaining;
                remaining -= chunk;
                ps2DmaReceive(channel, sign_word(cursor), sign_word(chunk));
                (void)ps2KernelSleepThread();
                int stop = aborted();
                cursor += chunk << 4;
                if (stop) break;
            }
            nocturneDmaWrite32(UINT32_C(0x10003c00), 0);
            control = nocturneDmaRead32(port);
            nocturneDrawConsumerWrite64(UINT32_C(0x12001040), 0);
            int stop = aborted();
            nocturneDmaWrite32(port, control & UINT32_C(0xfffffffe));
            if (stop) goto exit_early;
            uint32_t callback = word(receive + 8);
            if (callback) nocturneDrawConsumerCallback(callback, sign_word(word(receive + 12)), resume_tag);
            ps2DmaSendChain(channel, resume_tag);
        }
        while (nocturneDmaRead32(UINT32_C(0x10003c00)) & 3) { }
        while (nocturneDmaRead32(UINT32_C(0x10003020)) & UINT32_C(0x180)) { }
        ps2DrawCompleteFrameState(byte(record + 8), byte(record + 10), byte(record + 11));
        uint8_t queued = byte(record + 8);
        uint8_t next_frame = byte(UINT32_C(0x551889));
        put_byte(UINT32_C(0x551838), 1);
        put_byte(record + 8, (uint8_t)(queued + 1));
        put_byte(UINT32_C(0x551889), (uint8_t)(next_frame ^ 1));
    }
    put_byte(UINT32_C(0x551888), 1);
    if (byte(UINT32_C(0x551838))) ps2DevRenderConsoleList();
    nocturneDrawConsumerFrameLeave(UINT32_C(0x60));
    ps2DeferredQueueAdvance();
    return;
exit_early:
    nocturneDrawConsumerFrameLeave(UINT32_C(0x60));
}
