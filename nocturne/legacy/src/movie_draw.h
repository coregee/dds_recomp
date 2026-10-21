#ifndef NOCTURNE_MOVIE_DRAW_H
#define NOCTURNE_MOVIE_DRAW_H
#include <stdint.h>
uint64_t ps2MovieDrawProcess(void);
void ps2MovieBuildDrawPacket(uint64_t control,uint64_t ordering);
uint64_t ps2MovieRegisterCommandCallback(uint64_t callback);
uint64_t ps2MovieSetOutputMode(uint64_t mode);
uint64_t ps2MovieCommandEnqueue(uint64_t command,uint64_t flags,uint64_t source,uint64_t bytes);
uint64_t ps2MovieCommandPump(void);
void ps2MovieCommandTokenIgnore(uint64_t token);
uint64_t ps2MovieCommandSubmit(uint64_t command,uint64_t flags,uint64_t source,uint64_t bytes);
uint64_t ps2MovieControlCheckEnd(uint64_t control);
uint64_t ps2MovieCheckEnd(void);
uint64_t ps2MovieCheckDrawState(void);
uint64_t ps2DrawChainCreate(uint64_t allocator);
uint64_t ps2KernelWakeupThreadRaw(uint64_t thread);
uint64_t nocturneMovieDrawAllocate(uint32_t entry,uint64_t bytes);
void nocturneMovieDrawInvoke(uint32_t entry,uint64_t ordering,uint64_t chain);
#endif
