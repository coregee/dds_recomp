#ifndef NOCTURNE_BATTLE_EFFECT_COPY_H
#define NOCTURNE_BATTLE_EFFECT_COPY_H
#include <stdint.h>
uint64_t effBTLCutCreate(uint64_t effect,uint64_t cut,uint64_t form,uint64_t state);
uint64_t effBTLCutGetCutEndFrame(uint64_t cut);
uint64_t effBTLSkillGetID(void);
uint64_t effBTLModelGetID(uint64_t form);
float effBTLPartGetScalePtrSub(uint64_t form);
float effBTLPartGetScalePtr(uint64_t form);
float effBTLSystem_GetScalePtr(uint64_t form);
uint64_t dds3EffectPartGetHandle(uint64_t part);
uint64_t dds3EffectPartCopy(uint64_t part);
void dds3EffectPartSetScale(float scale,uint64_t part);
uint64_t dds3EffectPCPCopy(uint64_t pcp);
void dds3EffectPCPSetScale(float scale,uint64_t pcp);
void ps2EffectPCPScale_00176538(float scale,uint64_t object);
uint64_t ps2EffectPCP43Create(uint64_t object);
uint64_t ps2EffectPCP43Copy(uint64_t object);
uint64_t ps2BillboardTextureBase(uint64_t kind);
uint64_t ps2EffectCopy_001a1ff8(uint64_t source);
uint64_t ps2EffectCreate_0018e1c8(uint64_t source);
#define EFFECT_ROOT(kind) uint64_t ps2HitEffectCreate##kind(uint64_t form);uint64_t ps2HitEffectLength##kind(uint64_t object)
EFFECT_ROOT(20);EFFECT_ROOT(24);EFFECT_ROOT(25);EFFECT_ROOT(26);EFFECT_ROOT(27);EFFECT_ROOT(28);EFFECT_ROOT(29);
#undef EFFECT_ROOT
uint64_t ps2HitEffectLength14(uint64_t object);
uint64_t ps2HitEffectLength17(uint64_t object);
uint64_t ps2HitEffectLength18(uint64_t object);
void *nocturneResolveBattleEffectCopyAddress(uint32_t address);
uint64_t nocturneCallEffectCopy(uint32_t entry,uint64_t source);
void nocturneCallEffectScale(uint32_t entry,uint64_t object,uint32_t scale);
uint64_t nocturneEffectScaleSubBits(uint64_t form);
uint64_t nocturneEffectScaleBits(uint64_t form);
uint64_t nocturneEffectSystemScaleBits(uint64_t form);
void nocturneEffectPartScaleBits(uint64_t scale,uint64_t part);
void nocturneEffectPCPScaleBits(uint64_t scale,uint64_t pcp);
void nocturneEffectPCP0ScaleBits(uint64_t scale,uint64_t object);
#endif
