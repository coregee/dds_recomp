#ifndef NOCTURNE_MOVIE_PRELOADED_H
#define NOCTURNE_MOVIE_PRELOADED_H
#include <stdint.h>
void ps2MovieDecoderBuildInputChain(uint64_t decoder,uint64_t payload,uint64_t bytes);
void ps2MovieDecoderInitializePreloaded(uint64_t decoder,uint64_t configuration,uint64_t image,uint64_t bytes);
void ps2MovieDecoderPreloadedCreate(uint64_t decoder,uint64_t configuration,uint64_t image,uint64_t bytes,uint64_t display);
void ps2MovieDecoderPreloadedFromTexture(uint64_t decoder,uint64_t configuration,uint64_t image,uint64_t bytes,uint64_t texture);
#endif
