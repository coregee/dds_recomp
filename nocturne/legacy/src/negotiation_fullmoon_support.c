/* Complete native prerequisites for the Full Moon phase family.
 * Packets, windows, formation selection and money arithmetic use actual
 * registered implementations; no supplied game-call return values. */
#include "negotiation_fullmoon.h"
#include "nocturne.h"
#include "battle_work_access.h"
#include "battle_action_status.h"
#include "battle_action_packet_frames.h"
#include "battle_presentation.h"
#include "battle_ai_startup.h"
#include "message_commands.h"
#include "ee_fpu.h"
#include <string.h>
static void *at(uint32_t a)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveNegotiationFullMoonAddress(a);
#else
    return(void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t i32(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint64_t sh(uint32_t v){return sx(v&0x8000u?v|0xffff0000u:v);}

void ps2NegoCameraTarget_001B1810(uint64_t actor)
{
    uint32_t current=(uint32_t)effBTLSkillGetInvokeFormation();
    uint64_t index=sh(r16(current+0x92));
    uint32_t mask=1u<<(r16((uint32_t)actor+0x92)&31u);
    effBTLSkillSetFormationInfo(index,sx(mask));nbCameraSetState(15);
}
uint64_t ps2NegoResourcePacket_00262D38(uint64_t side,uint64_t owner,uint64_t resource)
{
    if(ps2BattleActionPacket_0025EF10(side,resource,5))return 0;
    uint64_t data=ps2BattleActionPacket_0025E8E0();
    uint64_t packet=ps2BattleActionPacket_0025EA48(data,side,0,owner);
    w32((uint32_t)packet+0x28,(uint32_t)resource);
    *(uint8_t *)at((uint32_t)packet+4)=0x1c;return packet;
}
void ps2NegoSetMoneyVariable_0026A918(uint64_t window,uint64_t amount)
{itfMesMngSetVar(window,3,amount,0);}
void ps2NegoCloseWindow_0026A958(uint64_t raw)
{
    uint32_t c=(uint32_t)raw,window=r32(c+0x50);
    if((window&0x80000000u)==0){itfMesMngMsgWndCls(sx(window));w32(c+0x50,UINT32_MAX);}
}
uint64_t ps2NegoMoneyRewardBase_0026AC78(uint64_t context,uint64_t source,uint64_t target)
{
    (void)context;(void)source;
    uint32_t roll=sdfGetRandInt(NULL,10);
    uint32_t product=r16((uint32_t)target+0x14)*(roll+21u);
    uint32_t value=EE_FPU_CVT_W_S(EE_FPU_MUL_S(EE_FPU_CVT_S_W(product),r32(0x54e5a0)));
    value=(uint32_t)(i32(value+5u)/10)*10u;
    return sx(value?value:1u);
}
uint64_t ps2NegoMoneyReward_0026AC00(uint64_t context,uint64_t source,uint64_t target)
{
    uint32_t base=(uint32_t)ps2NegoMoneyRewardBase_0026AC78(context,source,target);
    uint32_t product=base*(sdfGetRandInt(NULL,30)+40u);
    uint32_t value=(uint32_t)(i32(product)/100);
    value=(uint32_t)(i32(value+5u)/10)*10u;return sx(value?value:1u);
}
uint64_t ps2NegoActorUnitId_0028D070(uint64_t actor)
{return nbGetUnitID(nbGetUnitWorkFromFormindex(sh(r16((uint32_t)actor+0x92))));}
uint64_t ps2NegoPackMotionId_0028D1A8(uint64_t unit_id)
{return sx(((uint32_t)unit_id+0x500u)<<16);}
uint64_t ps2NegoActorMotionId_0028D1B8(uint64_t actor)
{return ps2NegoPackMotionId_0028D1A8(ps2NegoActorUnitId_0028D070(actor));}
static uint64_t motion(uint64_t raw,uint64_t actor,uint32_t number,int no)
{
    uint32_t c=(uint32_t)raw;ps2NegoCloseWindow_0026A958(raw);
    (void)ps2BattleActionPacket_00261FF0(0,sx(r32(c+4)),actor,number);
    uint32_t id=(uint32_t)ps2NegoActorMotionId_0028D1B8(actor)+(uint32_t)no;
    (void)ps2NegoResourcePacket_00262D38(0,sx(r32(c+4)),sx(id));return 15;
}
uint64_t ps2NegoNoMotion_0026BDE0(uint64_t c,uint64_t actor){return motion(c,actor,15,1);}
uint64_t ps2NegoYesMotion_0026BE40(uint64_t c,uint64_t actor){return motion(c,actor,14,0);}
