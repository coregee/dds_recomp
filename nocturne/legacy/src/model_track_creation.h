#pragma once
#include <stdint.h>
uint64_t ps2TrackPolyAllocateHistory(uint64_t length,uint64_t steps);
void ps2TrackPolySetDrawKind(uint64_t data,uint64_t kind);
void ps2TrackPolyFillGradient(uint64_t data,uint64_t gradient);
uint64_t ps2EffectBlendColor(uint64_t first,uint64_t second,float amount);
uint64_t ps2SpecialTrackBundleCreate(uint64_t parameters);
uint64_t ps2ModelTrackPolyCreate(uint64_t parameters);
void ps2ModelCreateColorTransition(uint64_t model,uint64_t frames,uint64_t count,uint64_t end,uint64_t start);
void ps2ModelCreateColorTransitionRecord(uint64_t model,uint64_t record,uint64_t slot);
uint64_t nocturneEffectBlendColorBits(uint64_t first,uint64_t second,uint64_t amount);
