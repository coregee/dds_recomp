/* Complete four SLUS_209.11 negotiation Flow6 seed algorithms.
 * Semantic/callee-save/declared-RAM profile excludes private guest frames,
 * volatile banks and HI/LO. Queue entries/continuation addresses remain data;
 * these bodies execute no invented VM, dialogue, renderer or OS service.
 */
#include "negotiation_flow.h"
#include "nocturne.h"
#include <string.h>

static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveNegotiationFlowAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint16_t r16(uint32_t address){uint16_t v;memcpy(&v,at(address),2);return v;}
static uint32_t r32(uint32_t address){uint32_t v;memcpy(&v,at(address),4);return v;}
static void w32(uint32_t address,uint32_t value){memcpy(at(address),&value,4);}
static uint64_t sx(uint32_t value)
{return value&UINT32_C(0x80000000)?UINT64_C(0xffffffff00000000)|value:value;}
static int32_t i32(uint32_t value)
{return value<=INT32_MAX?(int32_t)value:-1-(int32_t)(UINT32_MAX-value);}
static int less32(uint32_t a,uint32_t b)
{return (a^UINT32_C(0x80000000))<(b^UINT32_C(0x80000000));}
static uint32_t param(uint32_t work)
{return (uint32_t)datGetParam((datUnitWork_PS2 *)at(work),1);}
static uint32_t race(uint32_t work)
{return (uint32_t)datGetRace((datUnitWork_PS2 *)at(work));}

/* 0026A8A0. Signed SLTI admits negative counts. In particular count=-1
 * writes the count field itself before the native reload and increment.
 * No nonnegative-index guard or capacity repair is introduced. */
uint64_t ps2NegotiationFlowQueue_0026A8A0(uint64_t raw_context,uint64_t command)
{
    uint32_t context=(uint32_t)raw_context,count=r32(context+0x20u);
    if(!less32(count,8u))return 0;
    w32(context+0x24u+(count<<2),(uint32_t)command);
    uint32_t next=r32(context+0x20u)+1u;
    w32(context+0x20u,next);
    return sx(next);
}

/* 0026A998. Flag is compared as the entire raw64 register, while each SW
 * stores low32. The zero-flag branch alone writes context+4C. */
uint64_t ps2NegotiationFlowMessage_0026A998(uint64_t raw_context,uint64_t message,uint64_t mode,uint64_t flag)
{
    uint32_t context=(uint32_t)raw_context;
    w32(context+0x44u,(uint32_t)message);
    w32(context+0x48u,(uint32_t)mode);
    w32(context+0x58u,0);
    uint32_t flags=r32(context+8u);
    if(flag){
        flags|=4u;w32(context+8u,flags);
    }else{
        w32(context+0x4cu,(uint32_t)mode);
        flags&=~4u;w32(context+8u,flags);
    }
    return sx(flags);
}

/* 00270110. Enqueue before payment; re-read kind after both genuine queue
 * calls. Native item/Hearts and signed currency algorithms remain actual
 * canonical callees, including their unusual quantity=-1 Hearts behavior. */
uint64_t ps2NegotiationFlow6_22_00270110(uint64_t raw_context)
{
    uint32_t context=(uint32_t)raw_context,kind=r32(context+0x7cu);
    if(kind==0u||kind==1u||kind==5u){
        (void)ps2NegotiationFlowQueue_0026A8A0(raw_context,kind==5u?0x80001u:0x60018u);
        (void)ps2NegotiationFlowQueue_0026A8A0(raw_context,0x60017u);
        kind=r32(context+0x7cu);
    }
    if(kind==1u||kind==5u){
        uint32_t amount=r32(context+0x80u);
        if(datCheckMaka(i32(amount))){
            uint32_t continuation=r32(context+0x24u);
            amount=r32(context+0x80u);
            w32(context+0x1cu,continuation);
            datAddMaka(i32(0u-amount));
        }else w32(context+0x1cu,r32(context+0x28u));
    }else if(kind==0u){
        uint32_t item=r32(context+0x80u);
        if(datCheckItem(i32(item),1)){
            uint32_t continuation=r32(context+0x24u);
            item=r32(context+0x80u);
            w32(context+0x1cu,continuation);
            datAddItem(i32(item),-1);
        }else w32(context+0x1cu,r32(context+0x28u));
    }
    return 0;
}

/* 00270300. All original early exits, adjustments and actual RNG calls.
 * Weights remain wrapping signed words; neither their sum nor negatives are
 * normalized. Inclusive cumulative comparisons and bucket4->2 are native.
 */
uint64_t ps2NegotiationFlow6_24_00270300(uint64_t raw_context)
{
    uint32_t context=(uint32_t)raw_context;
    (void)ps2NegotiationFlowQueue_0026A8A0(raw_context,0x90001u);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw_context,0x60019u);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw_context,0x60025u);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw_context,0x6002bu);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw_context,0xa000du);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw_context,0x6004au);
    uint32_t attempt=r32(context+0x8cu),skill=r32(context+0x130u);
    w32(context+0x8cu,attempt+1u);
    uint32_t table=0x003d773cu+104u*skill,weights[4];
    for(uint32_t i=0;i<4;i++)weights[i]=*at(table+i);
    uint32_t target_race=race(r32(context+0x15cu));
    uint32_t mood=r32(context+0x134u);
    if(mood==1u){
        uint32_t adjustment=target_race==0x13u?5u:10u;
        weights[3]-=adjustment;weights[2]-=adjustment;weights[0]+=2u*adjustment;
    }else if(mood==2u){
        weights[3]+=10u;weights[2]+=10u;weights[0]-=20u;
    }
    /* The second real race call is not replaced by the earlier result. */
    target_race=race(r32(context+0x15cu));
    if(target_race!=0x13u){
        uint32_t source_param=param(r32(context+0x158u));
        uint32_t target_param=param(r32(context+0x15cu));
        if(less32(target_param+5u,source_param)){
            weights[3]-=5u;weights[2]-=5u;weights[0]+=10u;
        }else if(less32(source_param,target_param-5u)){
            weights[3]+=5u;weights[2]+=5u;weights[0]-=10u;
        }
    }
    if(r32(context+0x0cu)==3u){weights[0]=70u;weights[1]=20u;weights[2]=5u;weights[3]=5u;}
    if(r32(context+0x90u)==1u)goto outcome_success;
    if(r32(context+0x7cu)==2u){weights[2]+=weights[3];weights[3]=0;}
    attempt=r32(context+0x8cu);
    if(less32(attempt,2u)){
        if(evtBitCheck(8))goto outcome_refusal;
        attempt=r32(context+0x8cu);
        if(less32(attempt,2u)&&!r32(context+0x12cu))goto outcome_refusal;
    }
    /* The native level loads precede the later attempt-limit early exits. */
    uint32_t source=r32(context+0x158u),target=r32(context+0x15cu);
    uint32_t source_level=r16(source+0x14u),target_level=r16(target+0x14u);
    if(less32(attempt,3u)){
        if(evtBitCheck(8)&&!less32(target_level,source_level-10u)){
            weights[2]+=weights[0];weights[0]=0;
        }
        attempt=r32(context+0x8cu);
    }
    if(!less32(attempt,4u))goto outcome_success;
    if(r32(context+0x12cu)&&!less32(attempt,2u))goto outcome_success;
    uint32_t target_id=r16(r32(context+0x15cu)+4u);
    if(target_id==0x5cu||target_id==0x3du||target_id==0x61u||target_id==0x5bu){
        if(!evtBitCheck(8)&&!r32(context+0x12cu)&&!less32(r32(context+0x8cu),2u)){
            weights[0]+=weights[3];weights[0]+=weights[2];weights[3]=0;weights[2]=0;
        }
    }
    target=r32(context+0x15cu);source=r32(context+0x158u);
    target_level=r16(target+0x14u);source_level=r16(source+0x14u);
    if(!less32(source_level-17u,target_level)){
        uint32_t roll=sdfGetRandInt(NULL,100u);
        if(roll<4u){weights[2]+=weights[3];weights[3]=0;}
    }
    uint32_t roll=sdfGetRandInt(NULL,100u),bucket=0,cumulative=0;
    if(less32(weights[0],roll)){
        do{
            cumulative+=weights[bucket];bucket++;
            if(bucket>=4u)break;
        }while(less32(cumulative+weights[bucket],roll));
    }
    if(bucket==4u)bucket=2u;
    w32(context+0x1cu,r32(context+0x24u+4u*bucket));
    if(bucket!=3u)return 0;
    if(less32(r32(context+0x8cu),2u)||r32(context+0x12cu))return 0;
    roll=sdfGetRandInt(NULL,10u);
    if(roll>=6u)return 0;
    uint32_t index=r32(context+0x184u);
    uint32_t message=r32(context+0x1b0u+(index<<2));
    (void)ps2NegotiationFlowMessage_0026A998(raw_context,sx(message),99u,0);
    w32(context+0x1cu,r32(context+0x34u));
    return 0;
outcome_refusal:
    w32(context+0x1cu,r32(context+0x2cu));return 0;
outcome_success:
    w32(context+0x1cu,r32(context+0x24u));return 0;
}
