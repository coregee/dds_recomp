#ifndef NOCTURNE_SIF_INITIALIZATION_H
#define NOCTURNE_SIF_INITIALIZATION_H
#include <stdint.h>
uint64_t ps2KernelSifSetDChain(void);
uint64_t ps2KernelSifGetRegister(uint64_t id);
uint64_t ps2KernelSifSetRegister(uint64_t id,uint64_t value);
uint64_t ps2KernelAddDmacHandler(uint64_t channel,uint64_t handler,uint64_t next);
uint64_t ps2SifReadCommandRegister(uint64_t id);
void ps2SifAddCommandHandler(uint64_t command,uint64_t handler,uint64_t parameter);
void ps2SifCommandInitialize(void);
void ps2SifRpcInitialize(void);
uint64_t ps2FileRpcInitialize(void);
void *nocturneResolveSifInitializationAddress(uint32_t address);
uint64_t nocturneSifInitializationKernel(uint32_t selector,uint32_t argc,const uint64_t *args);
uint32_t nocturneSifInitializationMmioRead(uint32_t address);
void nocturneSifInitializationMmioWrite(uint32_t address,uint32_t value);
#endif
