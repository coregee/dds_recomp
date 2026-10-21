/* Complete sixteen Full Moon phase bodies. The adjacent unchecked
 * dispatcher remains separate; these functions never invent callbacks. */
#include "negotiation_fullmoon.h"
#include "negotiation_question.h"
#include "negotiation_flow.h"
#include "unit_progression.h"
#include "battle_action_status.h"
#include "nocturne.h"
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
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t i32(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static int less(uint32_t a,uint32_t b){return(a^0x80000000u)<(b^0x80000000u);}
static uint32_t race(uint32_t c){return(uint32_t)datGetRace((datUnitWork_PS2 *)at(r32(c+0x15c)));}
static uint32_t param(uint32_t unit){return(uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),1);}
static void queue(uint64_t c,uint32_t command){(void)ps2NegotiationFlowQueue_0026A8A0(c,command);}
static void message(uint64_t raw,uint32_t id,uint32_t mode){(void)ps2NegotiationFlowMessage_0026A998(raw,sx(id),mode,0);}
static uint32_t indexed_message(uint32_t c){return r32(c+0x1b0+(r32(c+0x184)<<2));}

uint64_t ps2NegoFullMoon2_1_00274228(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;queue(raw,0x20003);queue(raw,0x20002);queue(raw,0x10020);
    uint32_t id=r16(r32(c+0x15c)+4),offset;
    if(id==0x96||id==0x1d||id==3||id==8||id==13||id==10||id==5||id==4||id==16||id==24||id==30||id==0x99)offset=0x2c;
    else if(race(c)==0x13||race(c)==0x12)offset=0x28;
    else{
        id=r16(r32(c+0x15c)+4);
        if(id==0x9a||(uint16_t)(id-0x24u)<4u||id==0x6e||id==0x90||race(c)==7||race(c)==8)offset=0x28;
        else offset=less(sdfGetRandInt(NULL,100),50)?0x28u:0x24u;
    }
    w32(c+0x1c,r32(c+offset));return 0;
}
uint64_t ps2NegoFullMoon2_2_002743E8(uint64_t raw)
{
    uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
    if(phase==0){uint32_t id=r16(r32(c+0x15c)+4);
        if((uint16_t)(id-0x24u)>3u&&id!=0x6e&&id!=0x90&&id!=0x9a){w32(c+0x10,(uint32_t)ps2NegoNoMotion_0026BDE0(raw,sx(r32(c+0x16c))));return 0;}}
    else if(phase!=1)return 0;
    uint32_t mode=sdfGetRandInt(NULL,2)+0x1au;message(raw,indexed_message(c),mode);return 1;
}
uint64_t ps2NegoFullMoon2_3_002744B8(uint64_t raw){queue(raw,0x20004);return 0;}
uint64_t ps2NegoFullMoon2_4_002744E0(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;queue(raw,0x20005);
    uint32_t kind=(uint32_t)ps2NegotiationQuestionCategory_0026B7C8(sx(r32(c+0x15c)));w32(c+0x150,kind);
    uint32_t counter=r32(0x54ea20)+kind+0x1ce8,value=r8(counter);
    if(value<255u)*(uint8_t *)at(counter)=(uint8_t)(value+1u);return 0;
}
uint64_t ps2NegoFullMoon2_5_00274540(uint64_t raw)
{
    uint32_t c=(uint32_t)raw,phase=r32(c+0x18),mode=0;
    if(phase==0){uint32_t kind=r32(c+0x150);w32(c+0x154,0);
        if(kind==0){uint32_t q=sdfGetRandInt(NULL,2);w32(c+0x154,q);mode=q?0x11u:0xbu;}
        else if(kind==1)mode=5;else if(kind==2)mode=7;else if(kind==3)mode=3;
        message(raw,r32(c+0x22c),mode);return 0;}
    if(phase!=1)return 0;
    uint32_t kind=r32(c+0x150);
    if(kind==0)mode=r32(c+0x154)?0x12u:0xcu;else if(kind==1)mode=6;else if(kind==2)mode=8;else if(kind==3)mode=4;
    (void)ps2NegotiationFlowMessage_0026A998(raw,sx(r32(c+0x22c)),mode,1);queue(raw,0x20006);return 0;
}
uint64_t ps2NegoFullMoon2_6_00274690(uint64_t raw)
{
    uint32_t c=(uint32_t)raw,chance=50,type=0;queue(raw,0x20007);queue(raw,0x2000d);
    uint32_t kind=r32(c+0x150);
    if(kind==0){uint32_t record=0x3e2538u+(r32(c+0x184)*7u+r32(c+0x154))*4u;
        uint32_t selector=r16(record),a=r8(record+2),b=r8(record+3);type=a;
        if(selector==0||selector==1){int lower;
            if(selector==0){uint32_t s=param(r32(c+0x158)),t=param(r32(c+0x15c));lower=less(s,t);}
            else{uint32_t s=r32(c+0x158),t=r32(c+0x15c);lower=r16(s+0x14)<r16(t+0x14);}
            chance=lower?b:a;if(r32(c+0x58))chance=100u-chance;}}
    else if(kind<4u){uint32_t s=param(r32(c+0x158)),t=param(r32(c+0x15c));chance=less(s,t)?30u:70u;}
    uint32_t roll=sdfGetRandInt(NULL,100);kind=r32(c+0x150);
    if(kind>=1u&&kind<=3u){uint32_t base=kind==1u?0x3e28a6u:kind==2u?0x3e28acu:0x3e28a0u;
        uint32_t value=r8(base+(r32(c+0x184)*36u+r32(c+0x58))*2u);type=value<128u?value:value|0xffffff00u;
        ps2UnitAddReasonPoints_00245890(sx(type),1);}
    w32(c+0x1c,r32(c+(less(roll,chance)?0x24u:0x28u)));return 0;
}
uint64_t ps2NegoFullMoon2_7_00274908(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0x20008);w32(c+0x10,(uint32_t)ps2NegoYesMotion_0026BE40(raw,sx(r32(c+0x16c))));return 0;}
uint64_t ps2NegoFullMoon2_8_00274948(uint64_t raw){queue(raw,0x20009);return 0;}
static uint32_t response_mode(uint32_t c,int response)
{
    uint32_t kind=r32(c+0x150);if(kind!=0)return kind<4u?(response?10u:9u):0;
    uint32_t mode=r32(c+0x154)?(response?20u:19u):(response?14u:13u);if(r32(c+0x58))mode+=2u;return mode;
}
uint64_t ps2NegoFullMoon2_9_00274970(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0x2000a);message(raw,r32(c+0x22c),response_mode(c,0));return 0;}
uint64_t ps2NegoFullMoon2_10_00274A10(uint64_t raw)
{
    uint32_t c=(uint32_t)raw,chance=70;queue(raw,0x2000b);queue(raw,0x2000c);
    if(race(c)==0x15||race(c)==0x16||race(c)==0x17)chance=0;
    if(!(datSearchDevilStock(r16(r32(c+0x15c)+4))>>63))chance=100;
    if(datCheckStockFull())chance=100;
    uint32_t target_level=r16(r32(c+0x15c)+0x14);if(less((uint32_t)datGetPlayerLevel(),target_level))chance=100;
    if(race(c)==0x13||race(c)==0x12){message(raw,indexed_message(c),0x29);w32(c+0x1c,r32(c+0x24));return 0;}
    uint32_t roll=sdfGetRandInt(NULL,100);int selected=less(roll,chance);
    message(raw,indexed_message(c),selected?0x29u:0x2au);w32(c+0x1c,r32(c+(selected?0x24u:0x28u)));return 0;
}
uint64_t ps2NegoFullMoon2_11_00274B98(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;queue(raw,0xa001c);
    uint64_t amount=ps2NegoMoneyReward_0026AC00(raw,sx(r32(c+0x158)),sx(r32(c+0x15c)));w32(c+0x1a0,(uint32_t)amount);
    ps2NegoSetMoneyVariable_0026A918(sx(r32(c+0x328)),amount);message(raw,r32(c+0x328),3);datAddMaka(i32(r32(c+0x1a0)));return 0;
}
uint64_t ps2NegoFullMoon2_12_00274C08(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0x90007);message(raw,r32(c+0x328),9);return 0;}
uint64_t ps2NegoFullMoon2_13_00274C50(uint64_t raw)
{
    uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
    if(phase==0)w32(c+0x10,(uint32_t)ps2NegoNoMotion_0026BDE0(raw,sx(r32(c+0x16c))));
    else if(phase==1){queue(raw,0x2000e);message(raw,r32(c+0x22c),response_mode(c,1));}return 0;
}
uint64_t ps2NegoFullMoon2_14_00274D18(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;queue(raw,0x2000f);queue(raw,0x20010);ps2NegoCameraTarget_001B1810(sx(r32(c+0x16c)));
    uint32_t roll=sdfGetRandInt(NULL,2);message(raw,indexed_message(c),roll?0x2eu:0x2fu);w32(c+0x1c,r32(c+(roll?0x24u:0x28u)));return 0;
}
uint64_t ps2NegoFullMoon2_15_00274DB8(uint64_t raw){uint32_t c=(uint32_t)raw;queue(raw,0xa001d);message(raw,r32(c+0x328),1);return 0;}
uint64_t ps2NegoFullMoon2_16_00274E00(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;if(r32(c+0x130)!=0x18b||r16(r32(c+0x158)+6)==0)return 4;
    queue(raw,0xa0021);w32(c+0x18c,4);return 0;
}
