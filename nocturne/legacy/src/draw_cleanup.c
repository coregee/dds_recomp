#include "draw_cleanup.h"
#include "draw_interrupt.h"
#include "draw_consumer_support.h"
#include "draw_dma.h"
#include "heap_queue.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include <string.h>
static uint32_t word(uint32_t address)
{
    uint32_t value;
    memcpy(&value, nocturneResolveDrawCleanupAddress(address), 4);
    return value;
}
static uint64_t sign_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000) | value : value;
}
static void put_qword(uint32_t address, uint64_t value)
{
    memcpy(nocturneResolveDrawCleanupAddress(address), &value, 8);
}
/* 002aadc8: cache work under its semaphore; retain tag store order, real DMA
 * and handlers, then load each next link before real payload/node releases. */
void ps2DrawCleanupCompleted(void)
{
    const uint32_t record = UINT32_C(0x581018);
    (void)ps2KernelWaitSema(word(record));
    uint32_t list = word(record + 4);
    uint32_t packet = word(record + 12);
    uint32_t tag = word(record + 16);
    ps2DrawResetCompletedRecord(record);
    (void)ps2KernelSignalSema(word(record));
    if (packet) {
        uint64_t thread = sign_word(ps2KernelGetThreadId());
        uint64_t handler = ps2KernelAddDmaHandler(1, UINT64_C(0x2aada0), 0, thread);
        put_qword(tag + 8, 0);
        put_qword(tag, UINT64_C(0x005293a020000000));
        uint64_t channel = ps2DmaGetChannel(1);
        uint32_t control = nocturneDmaRead32((uint32_t)channel);
        nocturneDmaWrite32((uint32_t)channel, control | UINT32_C(0x40));
        (void)ps2KernelFlushCache(0);
        ps2DmaSendChain(channel, sign_word(packet));
        (void)ps2KernelSleepThread();
        (void)ps2KernelRemoveDmaHandler(1, handler);
    }
    while (list) {
        uint32_t type = *(uint8_t *)nocturneResolveDrawCleanupAddress(list + 12);
        uint32_t next = word(list);
        if (type == 1) ps2MemoryHandleFree(word(list + 8));
        else if (type == 2) ps2PoolRelease(word(list + 4));
        ps2PoolRelease(list);
        list = next;
    }
}
