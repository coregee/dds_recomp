#ifndef NOCTURNE_LIBC_CONSOLE_H
#define NOCTURNE_LIBC_CONSOLE_H
#include <stdint.h>
uint64_t ps2LibcStreamRead(uint64_t cookie,uint64_t buffer,uint64_t count);
uint64_t ps2LibcStreamWrite(uint64_t cookie,uint64_t buffer,uint64_t count);
uint64_t ps2LibcReadReentrant(uint64_t context,uint64_t descriptor,uint64_t buffer,uint64_t count);
uint64_t ps2LibcWriteReentrant(uint64_t context,uint64_t descriptor,uint64_t buffer,uint64_t count);
uint64_t ps2LibcConsoleRead(uint64_t descriptor,uint64_t buffer,uint64_t count);
uint64_t ps2LibcConsoleWrite(uint64_t descriptor,uint64_t buffer,uint64_t count);
uint64_t ps2ConsoleInitialize(void);
uint64_t ps2ConsoleWrite(uint64_t buffer,uint64_t count);
uint64_t ps2ConsoleRead(uint64_t buffer,uint64_t count);
uint64_t ps2ConsoleRingInitialize(uint64_t capacity);
void ps2ConsoleRingProduce(uint64_t ring);
void ps2ConsoleRingConsume(uint64_t ring);
void ps2ConsoleCommandCallback(uint64_t operation,uint64_t amount,uint64_t state);
uint64_t ps2ConsoleRegisterCommand(uint64_t service,uint64_t context,uint64_t callback);
uint64_t ps2ConsoleSendCommand(uint64_t channel,uint64_t command);
uint64_t ps2ConsolePollCommand(uint64_t channel);
uint64_t ps2ConsoleReceiveBytes(uint64_t channel,uint64_t buffer,uint64_t count);
uint64_t ps2ConsoleSendBytes(uint64_t channel,uint64_t buffer,uint64_t count);
void *nocturneResolveLibcConsoleAddress(uint32_t address);
uint32_t nocturneLibcConsoleReadAvailable(uint32_t address);
#endif
