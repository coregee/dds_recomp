/* Four complete original Mukan phase producers; HD names identify roles.
 * Queue entries and chosen continuation words remain data, not invented calls. */
#include "negotiation_mukan.h"
#include "negotiation_flow.h"
#include "nocturne.h"
#include <string.h>
static void *at(uint32_t a)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveNegotiationMukanAddress(a);
#else
    return (void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int less(uint32_t a,uint32_t b){return(a^0x80000000u)<(b^0x80000000u);}
uint64_t ps2NegotiationMukanFlow12_1_002774A8(uint64_t raw)
{
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x1001f);
    w32((uint32_t)raw+0x68,0xc0002);return 0;
}
uint64_t ps2NegotiationMukanFlow12_2_002774E8(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0xc0003);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0xc0004);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0xc0018);
    uint32_t kind=r16(0x3dcb4cu+r16(r32(c+0x15c)+4)*48u);
    uint32_t roll=sdfGetRandInt(NULL,100),table=0x3e2470u+kind*3u;
    if(less(roll,r8(table))){w32(c+0x1c,r32(c+0x24));return 0;}
    uint32_t cumulative=0,index=0;
    do{
        cumulative+=r8(table+index);index++;
        if(index>=3)return 0;
    }while(!less(roll,cumulative+r8(table+index)));
    w32(c+0x1c,r32(c+0x24+(index<<2)));return 0;
}
static uint64_t reaction(uint64_t raw,uint32_t first,uint32_t initial_message,uint32_t response_message)
{
    uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
    if(phase==0||phase==1){
        uint32_t index=r32(c+0x184),message=r32(c+0x1b0+(index<<2));
        (void)ps2NegotiationFlowMessage_0026A998(raw,sx(message),phase?response_message:initial_message,phase);
        return 0;
    }
    if(phase!=2)return 0;
    for(uint32_t i=0;i<4;i++)(void)ps2NegotiationFlowQueue_0026A8A0(raw,first+i);
    uint32_t source=r32(c+0x158),source_level=r16(source+0x14);
    uint32_t source_param=(uint32_t)datGetParam((datUnitWork_PS2 *)at(source),1);
    uint32_t target=r32(c+0x15c),target_level=r16(target+0x14);
    uint32_t target_param=(uint32_t)datGetParam((datUnitWork_PS2 *)at(target),1);
    uint32_t chance=source_level<target_level?(less(source_param,target_param)?20u:60u):(less(source_param,target_param)?40u:80u);
    uint32_t mode=r32(c+0x58),roll=sdfGetRandInt(NULL,100);
    uint32_t offset=mode?(less(roll,100u-chance)?0x2cu:0x30u):(less(roll,chance)?0x24u:0x28u);
    w32(c+0x1c,r32(c+offset));return 0;
}
uint64_t ps2NegotiationMukanFlow12_3_00277600(uint64_t raw)
{return reaction(raw,0xc0010,0xeb,0xd5);}
uint64_t ps2NegotiationMukanFlow12_4_00277798(uint64_t raw)
{return reaction(raw,0xc0014,0xec,0xd6);}
