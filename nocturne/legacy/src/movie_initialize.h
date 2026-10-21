#ifndef NOCTURNE_MOVIE_INITIALIZE_H
#define NOCTURNE_MOVIE_INITIALIZE_H
#include <stdint.h>
void ps2MovieControlInitialize(uint64_t control,uint64_t parameters,uint64_t filename);
void ps2MovieDecoderClear(uint64_t decoder,uint64_t configuration);
void ps2MovieDecoderCreate(uint64_t decoder,uint64_t configuration,uint64_t callback,uint64_t payload);
void ps2MovieDecoderInitialize(uint64_t decoder,uint64_t configuration,uint64_t callback,uint64_t payload,uint64_t field);
void ps2MovieDecoderListAppend(uint64_t decoder);
void ps2MovieDecoderListRemove(uint64_t decoder);
uint64_t ps2MovieDecoderQueueRemove(uint64_t decoder,uint64_t interrupts_disabled);
void ps2MovieStopDecoderCommand(void);
#endif
