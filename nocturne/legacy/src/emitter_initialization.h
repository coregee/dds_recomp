#pragma once
#include <stdint.h>
uint64_t ps2BillAnimationResourceCreate(uint64_t source);
uint64_t ps2BillAnimationAllocate(uint64_t source);
uint64_t dds3BillboardCreate(uint64_t kind,uint64_t source);
uint64_t ps2BillboardCloneCached(uint64_t index);
void dds3BillboardSetScale(uint64_t billboard,float x,float y);
void dds3BillboardSetMode(uint64_t billboard,uint64_t mode);
void dds3BillboardSetAnimColorAdvMode(uint64_t billboard);
void ps2ParticleBasicInitialize(uint64_t work);
void ps2ParticleKindReset(uint64_t kindState,uint64_t index);
void ps2EffectPointHistoryReset(uint64_t history,uint64_t index);
uint64_t Eff_ModelTrackPolyListCreate(uint64_t parameters,uint64_t count);
void Eff_ModelTrackPolyListReset(uint64_t list,uint64_t index);
void Eff_ModelTrackPolyReset(uint64_t work);
void ps2HermitianTrackPolyReset(uint64_t record);
void ps2SpecialTrackBundleReset(uint64_t bundle);
/* Reads original unassigned private-frame bytes; this is an input boundary,
 * not a game routine or a substitute model/track-constructor result. */
void nocturneEmitterIncomingFramePrefix(uint32_t words[5]);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveEmitterInitializationAddress(uint32_t address);
uint64_t nocturneCallBillboardFactory(uint32_t target,uint64_t source);
uint64_t nocturneEmitterTrackListFromFrame(const uint32_t words[13],uint64_t count);
#endif
