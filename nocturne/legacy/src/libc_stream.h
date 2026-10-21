#ifndef NOCTURNE_LIBC_STREAM_H
#define NOCTURNE_LIBC_STREAM_H
#include <stdint.h>
void ps2LibcStreamRecordInitialize(uint64_t stream,uint64_t flags,uint64_t descriptor,uint64_t context);
void ps2LibcStreamsInitialize(uint64_t context);
uint64_t ps2LibcLocaleRecord(uint64_t context);
uint64_t ps2LibcLocaleConvention(void);
uint64_t ps2LibcIsatty(uint64_t descriptor);
uint64_t ps2LibcFstatStub(uint64_t descriptor,uint64_t output);
uint64_t ps2LibcFstatReentrant(uint64_t context,uint64_t descriptor,uint64_t output);
uint64_t ps2LibcCloseUnsupported(uint64_t descriptor);
uint64_t ps2LibcSeekUnsupported(uint64_t descriptor,uint64_t offset,uint64_t origin);
uint64_t ps2LibcCloseReentrant(uint64_t context,uint64_t descriptor);
uint64_t ps2LibcSeekReentrant(uint64_t context,uint64_t descriptor,uint64_t offset,uint64_t origin);
uint64_t ps2LibcStreamClose(uint64_t cookie);
uint64_t ps2LibcStreamSeek(uint64_t cookie,uint64_t offset,uint64_t origin);
uint64_t ps2LibcFlush(uint64_t stream);
uint64_t ps2LibcStreamWalk(uint64_t context,uint64_t callback);
uint64_t ps2LibcStreamsCleanup(uint64_t context);
void ps2LibcMakeBuffer(uint64_t stream);
uint64_t ps2LibcPrepareWrite(uint64_t stream);
void *nocturneResolveLibcStreamAddress(uint32_t address);
uint64_t nocturneLibcStreamCallback(uint32_t callback,uint32_t argc,const uint64_t *args);
uint32_t nocturneLibcStreamLocalAddress(void *buffer,uint32_t bytes);
void nocturneLibcStreamEndLocal(void);
#endif
