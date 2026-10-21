#pragma once
#include <stdint.h>
void ps2MotionChange(uint64_t controller,uint64_t cut,uint64_t type);
void ps2MotionSampleFrame(uint64_t controller,float frame);
uint64_t ps2MotionAdvanceFrame(uint64_t controller);
#if UINTPTR_MAX > UINT32_MAX
void nocturneCallMotionSample(uint32_t target,uint64_t node,uint32_t frame,uint32_t weight,int blend);
#endif
