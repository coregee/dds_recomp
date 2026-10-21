#include "draw_interrupt.h"
#include "material_fiveword_pool.h"
#include <string.h>

static uint32_t word(uint32_t address)
{
    uint32_t value;
    memcpy(&value, nocturneResolveDrawInterruptAddress(address), 4);
    return value;
}
static void put_word(uint32_t address, uint32_t value)
{
    memcpy(nocturneResolveDrawInterruptAddress(address), &value, 4);
}
static uint64_t sign_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000) | value : value;
}

/* 002aad88: clear tag/list/current/packet in the actual store order. */
void ps2DrawResetCompletedRecord(uint64_t record)
{
    uint32_t address = (uint32_t)record;
    put_word(address + 16, 0);
    put_word(address + 4, 0);
    put_word(address + 8, 0);
    put_word(address + 12, 0);
}

/* 002dbde0 and002dbed0: negative LI selectors retain sign extension. */
uint64_t ps2KernelInterruptWakeThread(uint64_t thread)
{
    return nocturneDrawInterruptKernelValue(UINT64_C(0xffffffffffffffcc), 1, &thread);
}
uint64_t ps2KernelInterruptSignalSema(uint64_t semaphore)
{
    return nocturneDrawInterruptKernelValue(UINT64_C(0xffffffffffffffbd), 1, &semaphore);
}

/* 002dbbc0/002dbbd0: raw EE argument/return lanes, selectors12/13hex. */
uint64_t ps2KernelAddDmaHandler(uint64_t channel, uint64_t callback,
                              uint64_t next, uint64_t argument)
{
    uint64_t args[4] = {channel, callback, next, argument};
    return nocturneDrawInterruptKernelValue(UINT64_C(0x12), 4, args);
}
uint64_t ps2KernelRemoveDmaHandler(uint64_t channel, uint64_t handler)
{
    uint64_t args[2] = {channel, handler};
    return nocturneDrawInterruptKernelValue(UINT64_C(0x13), 2, args);
}

/* 002dcd50: thread equality and SLTIU consume full64 values. Queue writes
 * use the old masked index, then store index+1 without masking again. */
uint64_t ps2DrawWakeThread(uint64_t thread)
{
    uint64_t current = nocturneDrawInterruptKernelValue(UINT64_C(0xffffffffffffffd1), 0, NULL);
    if (current != thread) return ps2KernelInterruptWakeThread(thread);
    if (current >= 256 || !word(UINT32_C(0x52c2ac))) return UINT64_MAX;
    uint64_t semaphore = sign_word(word(UINT32_C(0x59b170)));
    uint32_t index = word(UINT32_C(0x59b17c)) & UINT32_C(0x1ff);
    uint32_t pair = UINT32_C(0x59b180) + (index << 1);
    put_word(UINT32_C(0x59b17c), index + 1);
    *(uint8_t *)nocturneResolveDrawInterruptAddress(pair) = 0;
    *(uint8_t *)nocturneResolveDrawInterruptAddress(pair + 1) = (uint8_t)current;
    (void)ps2KernelInterruptSignalSema(semaphore);
    return current;
}

/* 002aada0: raw A1 is the thread; SYNC0 and EI execute on every path. */
uint64_t ps2DrawDmaInterrupt(uint64_t channel, uint64_t thread)
{
    (void)channel;
    (void)ps2DrawWakeThread(thread);
    nocturneDrawInterruptSync();
    EE_SYSTEM_EI();
    return UINT64_MAX;
}
