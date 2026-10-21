#ifndef NOCTURNE_DEV_CONSOLE_H
#define NOCTURNE_DEV_CONSOLE_H
#include <stdint.h>
/* Raw EE interfaces: original RAM operations address the low word. */
void sdfDevSetPrintAttr(uint64_t control, uint64_t attribute);
void sdfDevSetPrintCB(uint64_t control, uint64_t x, uint64_t y,
                     uint64_t z, uint64_t attribute);
void ps2DevFinalizeGlyphPacket(uint64_t handle);
void ps2DevUnlinkConsole(uint64_t node);
uint64_t ps2DevClearConsole(uint64_t node);
void ps2DevAdvanceConsoleLine(uint64_t node);
void *nocturneResolveDevConsoleAddress(uint32_t address);
#endif
