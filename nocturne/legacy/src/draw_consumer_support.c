#include <stdint.h>
#include <string.h>
#include "draw_consumer_support.h"

extern void *nocturneResolveDrawSupportAddress(uint32_t address);
extern uint64_t nocturneDrawSupportKernelValue(uint32_t selector,
                                             uint32_t has_argument,
                                             uint64_t argument);
static uint8_t byte_at(uint32_t address)
{
    uint8_t value;
    memcpy(&value, nocturneResolveDrawSupportAddress(address), 1);
    return value;
}
static void put_byte(uint32_t address, uint8_t value)
{
    memcpy(nocturneResolveDrawSupportAddress(address), &value, 1);
}
static uint64_t signed_byte(uint8_t value)
{
    return value < 128 ? value : UINT64_MAX - (255u - value);
}
static uint64_t signed_word(uint32_t value)
{
    return value < UINT32_C(0x80000000) ? value
        : UINT64_C(0xffffffff00000000) | value;
}

/* 002a9f90, 52 bytes: LB comparison is full 64 bits; writes are ordered. */
void ps2DrawPrepareFrameState(uint64_t frame, uint64_t mode)
{
    uint8_t next = (uint8_t)(frame ^ 1);
    if (signed_byte(byte_at(UINT32_C(0x551858))) == frame)
        put_byte(UINT32_C(0x551858), next);
    if (signed_byte(byte_at(UINT32_C(0x551859))) == frame)
        put_byte(UINT32_C(0x551859), next);
    put_byte(UINT32_C(0x55185a), (uint8_t)mode);
}

/* 002a9fc8, 48 bytes: ADDU wraps the indexed GP address as a word. */
void ps2DrawCompleteFrameState(uint64_t queued, uint64_t frame, uint64_t half)
{
    if (queued == 0) {
        put_byte(UINT32_C(0x551859), (uint8_t)frame);
        put_byte(UINT32_C(0x551858), (uint8_t)frame);
    } else {
        put_byte(UINT32_C(0x551858) + (uint32_t)half, (uint8_t)frame);
    }
    put_byte(UINT32_C(0x55185a), UINT8_C(0xff));
}

/* 002c9840, 40 bytes: the selected LUI value sign extends to 64 bits. */
uint64_t ps2DmaNormalizeAddress(uint64_t address)
{
    if (((uint32_t)address >> 28) == 7)
        address = (address & UINT64_C(0x0fffffff))
                | UINT64_C(0xffffffff80000000);
    return address;
}

/* 002c98a0, 40 bytes: SLTIU tests the full register; LW sign extends. */
uint64_t ps2DmaGetChannel(uint64_t index)
{
    uint32_t value;
    if (index >= 10) return 0;
    memcpy(&value, nocturneResolveDrawSupportAddress(
        UINT32_C(0x529f70) + ((uint32_t)index << 2)), 4);
    return signed_word(value);
}

/* Four 16-byte wrappers. Selectors below are HEX, as in original ASM. */
uint64_t ps2KernelSleepThread(void)
{
    return nocturneDrawSupportKernelValue(UINT32_C(0x32), 0, 0);
}
uint64_t ps2KernelFlushCache(uint64_t mode)
{
    return nocturneDrawSupportKernelValue(UINT32_C(0x64), 1, mode);
}
uint64_t ps2KernelGetGsIMR(void)
{
    return nocturneDrawSupportKernelValue(UINT32_C(0x70), 0, 0);
}
uint64_t ps2KernelPutGsIMR(uint64_t mask)
{
    return nocturneDrawSupportKernelValue(UINT32_C(0x71), 1, mask);
}

/* 002c96e8, 60 bytes: preserve the first syscall's complete V0 value. */
uint64_t ps2GsSwapInterruptMask(uint64_t mask)
{
    uint64_t previous = ps2KernelGetGsIMR();
    (void)ps2KernelPutGsIMR(mask);
    return previous;
}
/* 002c9728, 28 bytes: real wrapper calls the real syscall wrapper. */
uint64_t ps2GsReadInterruptMask(void)
{
    return ps2KernelGetGsIMR();
}
