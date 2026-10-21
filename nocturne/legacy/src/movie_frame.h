#ifndef NOCTURNE_MOVIE_FRAME_H
#define NOCTURNE_MOVIE_FRAME_H
#include <stdint.h>
uint64_t ps2VramFormatBits(uint64_t format);
uint64_t ps2VramAllocateFront(uint64_t size,uint64_t category);
uint64_t ps2VramSurfaceAllocate(uint64_t width,uint64_t height,uint64_t format,uint64_t category,uint64_t front);
void ps2MovieDecoderAllocateFrames(uint64_t decoder);
void ps2MovieDecoderBuildUploadPackets(uint64_t decoder);
void ps2MovieDecoderReadStreamHeader(uint64_t decoder);
void ps2MovieUploadQueueAppend(uint64_t packet,uint64_t end);
uint64_t ps2MovieDecoderDeliverFrame(uint64_t decoder);
void ps2MovieDecoderUpdate(uint64_t delta);
#endif
