#pragma once
#include <stdint.h>
void ps2ModelCreateCopiedEffects(uint64_t model,uint64_t record,uint64_t group,uint64_t type,uint64_t copyTarget);
void mdlCreateEffect_TRACK(uint64_t model,uint64_t record,uint64_t group);
void ps2ModelCreateCachedResourceEffect(uint64_t model,uint64_t record,uint64_t group);
void mdlCreateEffect(uint64_t model,uint64_t record,uint64_t group);
void mdlGenEffect(uint64_t model,uint64_t cut,uint64_t group);
void mdlFreeEffect(uint64_t node);
void ps2ModelUnlinkEffectGroup(uint64_t model,uint64_t group);
void ps2ModelChangeMotionEffects(uint64_t model,uint64_t motion,uint64_t cut,uint64_t type,float lead,float duration);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveModelEffectCreationAddress(uint32_t address);
uint32_t nocturneOriginalModelEffectCreationAddress(const void *host);
uint64_t nocturneCallModelEffectCopy(uint32_t target,uint64_t resource);
uint64_t nocturneCreateAttachedModelTrack(const uint32_t parameters[13]);
#endif
