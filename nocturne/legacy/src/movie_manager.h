#ifndef NOCTURNE_MOVIE_MANAGER_H
#define NOCTURNE_MOVIE_MANAGER_H
#include <stdint.h>
void ps2MoviePlayFile(uint64_t filename,uint64_t parameters);
void ps2MoviePlayIndex(uint64_t index);
void ps2MovieStop(void);
void ps2MovieDecoderQueueAppend(uint64_t decoder,uint64_t interrupts_disabled);
#endif
