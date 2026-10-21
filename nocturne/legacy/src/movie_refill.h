#ifndef NOCTURNE_MOVIE_REFILL_H
#define NOCTURNE_MOVIE_REFILL_H
#include <stdint.h>
void ps2MovieDecoderRefill(uint64_t decoder);
uint64_t ps2MovieInputDmaInterrupt(void);
uint64_t ps2MovieOutputDmaInterrupt(void);
void ps2MovieDecoderCompletionThread(void);
void ps2MovieDecoderFrameConsumed(uint64_t decoder);
uint64_t ps2MovieAudioReserve(uint64_t bytes);
uint64_t nocturneMovieDecoderConsume(uint32_t entry,const uint64_t *arguments);
#endif
