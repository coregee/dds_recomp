#include <stdint.h>
#include <string.h>
#include "ee_fpu.h"
#include "motion_callback_leaves.h"
#include "motion_key_search.h"
#include "material_motion_scalars.h"
static uint32_t load32(const uint8_t *p) { uint32_t v;memcpy(&v,p,4);return v; }
static void store32(uint8_t *p,uint32_t v) { memcpy(p,&v,4); }
static const uint8_t *resolve_original(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveMotionAddress(address);
#else
    return (const uint8_t *)(uintptr_t)address;
#endif
}
/* Read the old flags before the original word store; SB is the JR delay slot. */
void sdfMatSetAmbient(void *material,uint32_t value)
{ uint8_t *p=material;uint8_t flags=p[6];store32(p+0x10,value);p[6]=(uint8_t)(flags|3); }
void sdfMatSetDiffuse(void *material,uint32_t value)
{ uint8_t *p=material;uint8_t flags=p[6];store32(p+0x14,value);p[6]=(uint8_t)(flags|3); }
void sdfMatSetSpecular(void *material,uint32_t value)
{ uint8_t *p=material;uint8_t flags=p[6];store32(p+0x20,value);p[6]=(uint8_t)(flags|3); }
void sdfMatSetConstant(void *material,uint32_t value_bits)
{ uint8_t *p=material;uint8_t flags=p[6];store32(p+0x1c,value_bits);p[6]=(uint8_t)(flags|3); }
/* 002B4230: preserve operand and operation order, including final delay SUB. */
uint32_t ps2MotionInterpolateScalar(const void *key_pair)
{
    const uint8_t *key=key_pair;
    uint32_t next_address=load32(key+4),alpha=load32(key+8);
    uint32_t next=load32(resolve_original(next_address));
    uint32_t previous_address=load32(key);
    uint32_t next_product=EE_FPU_MUL_S(next,alpha);
    uint32_t previous=load32(resolve_original(previous_address));
    uint32_t previous_product=EE_FPU_MUL_S(previous,alpha);
    uint32_t sum=EE_FPU_ADD_S(previous,next_product);
    return EE_FPU_SUB_S(sum,previous_product);
}
/* 002B52F0: execute real key search and interpolation before loading material. */
void ps2MotionApplyMaterialConstant(void *node,uint32_t frame_bits)
{
    uint32_t key[3];sdfMotGetKey(node,frame_bits,key);
    uint32_t value=ps2MotionInterpolateScalar(key);
    uint32_t material=load32((const uint8_t *)node+0xc);
    sdfMatSetConstant((void *)resolve_original(material),value);
}
/* 002B5330: saved previous value is node+10; F20 contains the blend argument.
 * Original loads material between the two multiplies, before the last ADD/SUB. */
void ps2MotionBlendMaterialConstant(void *node,uint32_t frame_bits,uint32_t blend_bits)
{
    uint32_t key[3];sdfMotGetKey(node,frame_bits,key);
    uint32_t value=ps2MotionInterpolateScalar(key);
    uint32_t previous=load32((const uint8_t *)node+0x10);
    uint32_t next_product=EE_FPU_MUL_S(value,blend_bits);
    uint32_t material=load32((const uint8_t *)node+0xc);
    uint32_t previous_product=EE_FPU_MUL_S(previous,blend_bits);
    uint32_t sum=EE_FPU_ADD_S(previous,next_product);
    uint32_t result=EE_FPU_SUB_S(sum,previous_product);
    sdfMatSetConstant((void *)resolve_original(material),result);
}
