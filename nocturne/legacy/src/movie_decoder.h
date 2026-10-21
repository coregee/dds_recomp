#ifndef NOCTURNE_MOVIE_DECODER_H
#define NOCTURNE_MOVIE_DECODER_H
#include <stdint.h>
uint64_t ps2PoolContainsPointer(uint64_t pointer);
uint64_t ps2MemoryHandleFindPointer(uint64_t pointer);
void ps2MemoryPointerFree(uint64_t pointer);
void ps2PoolOrMemoryPointerFree(uint64_t pointer);
void ps2MovieDeferPointerFree(uint64_t pointer);
void ps2MemoryHandleDeferFree(uint64_t handle);
uint64_t ps2MovieIpuFromDmaControl(uint64_t control);
uint64_t ps2MovieIpuToDmaControl(uint64_t control);
void ps2MovieIpuSaveContext(uint64_t context);
void ps2MovieIpuRestoreContext(uint64_t context);
uint64_t ps2MovieIpuWait(uint64_t mode);
void ps2MovieDecoderInputDma(uint64_t decoder);
uint64_t ps2MovieIpuReadHeader(void);
void ps2MovieDecoderStart(uint64_t decoder);
void ps2MovieDecoderSchedule(uint64_t interrupts_disabled);
void ps2MovieDecoderDestroy(uint64_t decoder);
void ps2MovieClosePollHook(void);
void ps2MovieControlClose(uint64_t control);
/* Host relocation and external MMIO/IOP arrival boundaries. */
uint32_t nocturneMovieDecoderMmioRead(uint32_t address);
void nocturneMovieDecoderMmioWrite(uint32_t address,uint32_t value);
void nocturneMovieClosePollArrival(void);
#endif
