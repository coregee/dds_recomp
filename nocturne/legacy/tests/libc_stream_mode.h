#ifndef NOCTURNE_LIBC_STREAM_MODE_H
#define NOCTURNE_LIBC_STREAM_MODE_H
#include "../src/libc_stream.h"
extern uint32_t g_libcStreamActive;
uint64_t nocturneLibcStreamKernel(uint64_t selector,uint32_t argc,const uint64_t *args);
void nocturneLibcStreamInterrupt(uint32_t operation);
void nocturneLibcStreamSync(uint32_t type);
#endif
