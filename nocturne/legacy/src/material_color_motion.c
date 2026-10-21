#include <stdint.h>
#include <string.h>
#include "ee_fpu.h"
#include "motion_callback_leaves.h"
#include "motion_key_search.h"
#include "material_motion_scalars.h"
#include "material_setter_leaves.h"
#include "material_color_motion.h"
/* Primitive value provider, separate from recovered game-function totals.
 * VU MAC result priority is ps2f_madd(acc,s,t,0), not raw MUL then ADD. */
extern uint32_t EE_VU_MADD(uint32_t acc,uint32_t s,uint32_t t);
static uint32_t load32(const void *p) { uint32_t v;memcpy(&v,p,4);return v; }
static const uint8_t *resolve_original(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveMotionAddress(address);
#else
    return (const uint8_t *)(uintptr_t)address;
#endif
}
/* The packed lanes are low-to-high bytes. Do not replace the ordered VU
 * arithmetic with a host lerp: bias, truncation and overflow priority matter. */
static uint32_t blend_packed(uint32_t previous,uint32_t next,uint32_t alpha)
{
    uint32_t inverse=EE_FPU_SUB_S(UINT32_C(0x3f800000),alpha),out=0;
    for(unsigned lane=0;lane<4;++lane) {
        uint32_t p=EE_FPU_CVT_S_W((previous>>(lane*8))&255);
        uint32_t n=EE_FPU_CVT_S_W((next>>(lane*8))&255);
        uint32_t acc=EE_VU_MADD(UINT32_C(0x3f000000),p,inverse);
        uint32_t value=EE_VU_MADD(acc,n,alpha);
        out|=(EE_FPU_CVT_W_S(value)&255)<<(lane*8);
    }
    return out;
}
/* 002B42B0: preserve pointer/value/alpha load order from the original words. */
uint32_t ps2MotionInterpolateColor(const void *key_pair)
{
    const uint8_t *key=key_pair;
    uint32_t previous_address=load32(key),next_address=load32(key+4);
    uint32_t previous=load32(resolve_original(previous_address));
    uint32_t alpha=load32(key+8);
    uint32_t next=load32(resolve_original(next_address));
    return blend_packed(previous,next,alpha);
}
/* Every callback executes the real recovered key lookup and color helper.
 * The blended callbacks load the saved word after interpolation and the
 * material pointer after the second packing operation, before the setter. */
#define NOCTURNE_COLOR_CALLBACKS(role,setter) \
void ps2MotionApplyMaterial##role(void *node,uint32_t frame_bits) \
{ uint32_t key[3];sdfMotGetKey(node,frame_bits,key); \
  uint32_t color=ps2MotionInterpolateColor(key); \
  uint32_t material=load32((const uint8_t *)node+0xc); \
  setter((void *)resolve_original(material),color); } \
void ps2MotionBlendMaterial##role(void *node,uint32_t frame_bits,uint32_t blend_bits) \
{ uint32_t key[3];sdfMotGetKey(node,frame_bits,key); \
  uint32_t color=ps2MotionInterpolateColor(key); \
  uint32_t previous=load32((const uint8_t *)node+0x10); \
  uint32_t value=blend_packed(previous,color,blend_bits); \
  uint32_t material=load32((const uint8_t *)node+0xc); \
  setter((void *)resolve_original(material),value); }
NOCTURNE_COLOR_CALLBACKS(Diffuse,sdfMatSetDiffuse)
NOCTURNE_COLOR_CALLBACKS(Ambient,sdfMatSetAmbient)
NOCTURNE_COLOR_CALLBACKS(Specular,sdfMatSetSpecular)
NOCTURNE_COLOR_CALLBACKS(Word28,ps2MatSetWord28)
NOCTURNE_COLOR_CALLBACKS(Word18,ps2MatSetWord18)
#undef NOCTURNE_COLOR_CALLBACKS
