#ifndef NOCTURNE_SDK_DEBUG_H
#define NOCTURNE_SDK_DEBUG_H
#include <stdint.h>
uint64_t ps2SdkSerialPutchar(uint64_t character);
uint64_t ps2SdkSerialPutcharNewline(uint64_t character);
void ps2SdkBufferedPutchar(uint64_t character);
uint64_t ps2KernelCommandRaw(uint64_t command,const void *parameters);
uint64_t ps2SdkKernelDebugString(uint64_t string);
void ps2SdkFormatFloat(uint64_t bits);
void ps2SdkVprintf(uint64_t format,const void *arguments);
void ps2SdkPrintfDefault(uint64_t format,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7);
void ps2SdkPrintf(uint64_t format,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7);
void *nocturneResolveSdkDebugAddress(uint32_t address);
uint32_t nocturneSdkDebugSerialRead(void);
void nocturneSdkDebugSerialWrite(uint8_t character);
uint64_t nocturneSdkDebugKernel(uint64_t command,const void *parameters);
void nocturneSdkDebugCallback(uint32_t callback,uint64_t character);
uint32_t nocturneSdkDebugFloatZero(uint32_t bits);
#endif
