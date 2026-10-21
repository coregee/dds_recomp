#ifndef NOCTURNE_SCRIPT_DISTORTION_OWNER_H
#define NOCTURNE_SCRIPT_DISTORTION_OWNER_H
#include <stdint.h>
void *nocturneResolveScriptDistortionOwnerAddress(uint32_t address);
void ps2DistBlurInitializeParticle_001A21C0(uint64_t owner,uint64_t particle);
uint64_t ps2DistBlurCreate_001A22F0(uint64_t source);
uint64_t ps2PostEffectFourthOwner_001AD4A0(void);
void ps2PostEffectInitializeOwners_001AD5F0(void);
#endif
