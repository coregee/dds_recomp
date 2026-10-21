#ifndef NOCTURNE_MOVIE_STREAM_H
#define NOCTURNE_MOVIE_STREAM_H
#include <stdint.h>
void ps2MovieOrdinaryReadPump(uint64_t control);
uint64_t ps2MovieOrdinaryFileCallback(uint64_t job,uint64_t event,uint64_t buffer,uint64_t result,uint64_t control);
uint64_t ps2MovieOrdinaryConsume(uint64_t decoder,uint64_t control,uint64_t event,uint64_t buffer,uint64_t bytes);
void ps2MovieIpsReadPump(uint64_t control);
uint64_t ps2MovieIpsFileCallback(uint64_t job,uint64_t event,uint64_t buffer,uint64_t result,uint64_t control);
uint64_t ps2MovieIpsConsume(uint64_t decoder,uint64_t control,uint64_t event,uint64_t buffer,uint64_t bytes);
uint64_t ps2MovieIpsCopy(uint64_t output,uint64_t input,uint64_t bytes);
#endif
