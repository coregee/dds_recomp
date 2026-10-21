/* Original post-effect ownership and distortion particle initialization.
 * Existing allocator,texture,RNG and other post-effect constructors remain real callees. */
#include "script_distortion_owner.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "battle_effect_copy.h"
#include "battle_action_consumer.h"
#include "battle_action_status_resources.h"
#include "compiler_numeric.h"
#include "nocturne.h"
#include "ee_fpu.h"
#include <string.h>

static void *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveScriptDistortionOwnerAddress(address);
#else
    return (void *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address)
{ uint32_t value;memcpy(&value,at(address),4);return value; }
static void w32(uint32_t address,uint32_t value)
{ memcpy(at(address),&value,4); }
static uint64_t sx(uint32_t value)
{ return value&0x80000000u?UINT64_C(0xffffffff00000000)|value:value; }
static uint32_t fbits(float value)
{ uint32_t result;memcpy(&result,&value,4);return result; }
static uint32_t placement(uint32_t area,uint32_t value)
{
    value=EE_FPU_SUB_S(value,0x3f000000u);
    value=EE_FPU_ADD_S(value,value);
    return EE_FPU_CVT_W_S(EE_FPU_MUL_S(area,value));
}
void ps2DistBlurInitializeParticle_001A21C0(uint64_t raw_owner,uint64_t raw_particle)
{
    uint32_t owner=(uint32_t)raw_owner,particle=(uint32_t)raw_particle;
    uint32_t random=sdfGetRand((uint32_t *)at(0x316fe0));
    uint32_t divisor=r32(owner+4)+1u;
    /* Native DIVU precedes its zero-divisor BREAK7. This value profile
     * retains the real exception after the RNG draw; final HI/LO is separate. */
    if(!divisor)nocturneCompilerArithmeticTrap(7);
    w32(particle+4,r32(0x54c9e0));
    w32(particle+0x10,r32(owner+0x14));
    w32(particle,random%divisor);
    w32(particle+8,r32(owner+0xc));
    w32(particle+0xc,r32(owner+0x10));
    uint32_t area=EE_FPU_CVT_S_W(r32(owner+0x24));
    uint32_t width=r32(owner+0x28),half=(width>>1)|(width&0x80000000u);
    uint32_t draw=fbits(sdfGetRandFloat((uint32_t *)at(0x316fe0)));
    uint32_t x=r32(owner+0x1c)+placement(area,draw);
    w32(particle+0x18,x);
    draw=fbits(sdfGetRandFloat((uint32_t *)at(0x316fe0)));
    uint32_t y_base=r32(owner+0x20);
    x=r32(particle+0x18);
    w32(particle+0x28,x+0x100u+half);
    w32(particle+0x20,x+0x100u-half);
    uint32_t y=y_base+placement(area,draw);
    w32(particle+0x1c,y);
    w32(particle+0x2c,y+0xe0u+half);
    w32(particle+0x24,y+0xe0u-half);
}
uint64_t ps2DistBlurCreate_001A22F0(uint64_t raw_source)
{
    uint32_t source=(uint32_t)raw_source,handle=ps2MemoryHandleAllocate(0x12f8);
    uint32_t age=r32(0x54c9e4),owner=ps2MemoryHandleAcquirePointer(handle);
    uint8_t first[32],last[12];
    memcpy(first,at(source),32);memcpy(at(owner),first,32);
    memcpy(last,at(source+32),12);memcpy(at(owner+32),last,12);
    w32(owner+0x30,handle);w32(owner+0x34,owner+0x38);
    w32(owner+0x2c,(uint32_t)ps2BillboardTextureBase(2));
    uint32_t particle=r32(owner+0x34);
    for(unsigned i=0;i<100;i++,particle+=0x30) {
        ps2DistBlurInitializeParticle_001A21C0(sx(owner),sx(particle));
        w32(particle+4,age);
    }
    return sx(owner);
}
uint64_t ps2PostEffectFourthOwner_001AD4A0(void)
{ return sx(r32(0x551df4)); }
void ps2PostEffectInitializeOwners_001AD5F0(void)
{
    w32(0x551dec,(uint32_t)ps2EffectCopy_001a1ff8(0x320228));
    w32(0x551de8,(uint32_t)ps2DistBlurCreate_001A22F0(0x3201f8));
    w32(0x551df0,(uint32_t)ps2BattleAction_001A2E28(0x320270));
    w32(0x551df4,(uint32_t)ps2BattleAction_001A27A8(0x320298));
    w32((uint32_t)ps2PostEffectFourthOwner_001AD4A0(),4);
}
