#ifndef NOCTURNE_DISPLAY_CONTROL_H
#define NOCTURNE_DISPLAY_CONTROL_H
#include <stdint.h>
/* Raw EE interfaces. Display arguments are explicitly truncated in the body. */
void ps2GsSetDisplayMode(uint64_t mode, uint64_t interlace, uint64_t video_mode, uint64_t field);
uint64_t ps2GsGetControlState(void);
uint64_t ps2KernelSetGsCrt(uint64_t interlace, uint64_t video_mode, uint64_t field);
uint64_t ps2KernelRemoveIntcHandler(uint64_t cause, uint64_t handler);
uint64_t ps2KernelDisableIntcRaw(uint64_t cause);
uint64_t ps2KernelEnableDmacRaw(uint64_t channel);
uint64_t ps2KernelCancelWakeupThread(uint64_t thread);
uint64_t ps2KernelDisableIntc(uint64_t cause);
uint64_t ps2KernelEnableDmac(uint64_t channel);

uint64_t nocturneDisplayKernel(uint64_t selector, uint32_t argc, const uint64_t *args);
uint64_t nocturneDisplayLoad(uint32_t address, uint32_t width);
void nocturneDisplayStore(uint32_t address, uint32_t width, uint64_t value);
void nocturneDisplaySync(uint32_t type);
#endif
