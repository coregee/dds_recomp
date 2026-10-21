#include "display_control.h"
#include "draw_consumer_support.h"
#include "material_fiveword_pool.h"

static uint64_t sign_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000) | value : value;
}
uint64_t ps2GsGetControlState(void) { return UINT64_C(0x529f20); } /* 002c8338 */
uint64_t ps2KernelSetGsCrt(uint64_t interlace, uint64_t video_mode, uint64_t field)
{
    uint64_t args[3] = {interlace, video_mode, field};
    return nocturneDisplayKernel(2, 3, args); /* 002dbaa0 */
}
uint64_t ps2KernelRemoveIntcHandler(uint64_t cause, uint64_t handler)
{
    uint64_t args[2] = {cause, handler};
    return nocturneDisplayKernel(UINT64_C(0x11), 2, args); /* 002dbba0 */
}
uint64_t ps2KernelDisableIntcRaw(uint64_t cause)
{
    return nocturneDisplayKernel(UINT64_C(0x15), 1, &cause); /* 002dbbf0 */
}
uint64_t ps2KernelEnableDmacRaw(uint64_t channel)
{
    return nocturneDisplayKernel(UINT64_C(0x16), 1, &channel); /* 002dbc00 */
}
uint64_t ps2KernelCancelWakeupThread(uint64_t thread)
{
    return nocturneDisplayKernel(UINT64_C(0x35), 1, &thread); /* 002dbdf0 */
}

/* 002dc980/002dcab8: restore interrupts according to entry Status, while
 * preserving the kernel's complete V0 through real enable/disable callees. */
uint64_t ps2KernelDisableIntc(uint64_t cause)
{
    uint32_t enabled = EE_SYSTEM_READ_STATUS() & UINT32_C(0x10000);
    if (enabled) (void)ps2KernelDisableInterrupts();
    uint64_t result = ps2KernelDisableIntcRaw(cause);
    nocturneDisplaySync(0);
    if (enabled) (void)ps2KernelEnableInterrupts();
    return result;
}
uint64_t ps2KernelEnableDmac(uint64_t channel)
{
    uint32_t enabled = EE_SYSTEM_READ_STATUS() & UINT32_C(0x10000);
    if (enabled) (void)ps2KernelDisableInterrupts();
    uint64_t result = ps2KernelEnableDmacRaw(channel);
    nocturneDisplaySync(0);
    if (enabled) (void)ps2KernelEnableInterrupts();
    return result;
}

/* 002c81a8: SLL/SRA narrow all four arguments to signed halfwords.
 * Stores use their low16 bits; field presence and field parity differ. */
void ps2GsSetDisplayMode(uint64_t mode, uint64_t interlace, uint64_t video_mode, uint64_t field)
{
    uint16_t selected = (uint16_t)mode;
    uint16_t a = (uint16_t)interlace, b = (uint16_t)video_mode, c = (uint16_t)field;
    if (selected == 1) {
        nocturneDisplayStore(UINT32_C(0x12001000), 8, UINT64_C(0x100));
        return;
    }
    if (selected != 0 && selected != 5) return;
    uint32_t state = (uint32_t)ps2GsGetControlState();
    uint64_t csr;
    if (selected == 0) {
        nocturneDisplayStore(UINT32_C(0x12001000), 8, UINT64_C(0x200));
        nocturneDisplayStore(state, 2, a);
        csr = nocturneDisplayLoad(UINT32_C(0x12001000), 8);
        nocturneDisplayStore(state + 2, 2, b);
        nocturneDisplayStore(state + 6, 2, (csr >> 16) & UINT64_C(0xff));
        (void)ps2KernelPutGsIMR(UINT64_C(0xff00));
        uint32_t installed = (uint32_t)nocturneDisplayLoad(state + 8, 4);
        nocturneDisplayStore(state + 4, 2, c != 0);
        if (installed) {
            (void)ps2KernelDisableIntc(2);
            uint64_t handler = sign_word((uint32_t)nocturneDisplayLoad(state + 12, 4));
            (void)ps2KernelRemoveIntcHandler(2, handler);
            nocturneDisplayStore(state + 12, 4, 0);
            nocturneDisplayStore(state + 8, 4, 0);
        }
    } else {
        csr = nocturneDisplayLoad(UINT32_C(0x12001000), 8);
        nocturneDisplayStore(state + 4, 2, c != 0);
        nocturneDisplayStore(state, 2, a);
        nocturneDisplayStore(state + 2, 2, b);
        nocturneDisplayStore(state + 6, 2, (csr >> 16) & UINT64_C(0xff));
    }
    (void)ps2KernelSetGsCrt(a & 1u, b & 255u, c & 1u);
}
