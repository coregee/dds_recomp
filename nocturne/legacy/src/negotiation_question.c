/* Whole original Question category/phase bodies. Native category-index
 * comparisons, signed point-table bytes and overlapping queues are retained. */
#include "negotiation_question.h"
#include "negotiation_flow.h"
#include "unit_progression.h"
#include "nocturne.h"
#include <string.h>
static void *at(uint32_t a)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveNegotiationQuestionAddress(a);
#else
    return (void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w8(uint32_t a,uint32_t v){*(uint8_t *)at(a)=(uint8_t)v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int less(uint32_t a,uint32_t b){return(a^0x80000000u)<(b^0x80000000u);}
static int32_t signed_byte(uint32_t v){return v<128u?(int32_t)v:(int32_t)v-256;}
static uint32_t parameter(uint32_t u){return(uint32_t)datGetParam((datUnitWork_PS2 *)at(u),1);}

uint64_t ps2NegotiationQuestionCategory_0026B7C8(uint64_t raw)
{
    uint32_t unit=(uint32_t)raw,descriptor=0x3dcb38u+r16(unit+4u)*48u;
    uint32_t weights[3]={r32(0x544e38),r32(0x544e3c),r32(0x544e40)};
    uint32_t work=r32(0x54ea20);
    if(r8(descriptor+13u)==1u){
        uint32_t kind=r8(descriptor+14u),roll=sdfGetRandInt(NULL,100),sum=0;
        for(uint32_t index=0;index<4;index++){
            sum+=r8(0x3e2508u+kind*4u+index);
            if(less(roll,sum))return index;
        }
        return 0;
    }
    uint32_t sum=r8(work+0x1ce9u)+r8(work+0x1ceau)+r8(work+0x1cebu);
    uint32_t roll;
    if(less(r8(work+0x1ce8u),sum*2u)){
        roll=sdfGetRandInt(NULL,2);if(roll!=0)return 0;
    }else{
        roll=sdfGetRandInt(NULL,100);if(!less(roll,80))return 0;
    }
    work=r32(0x54ea20);
    uint32_t first=1,second=2,third=3;
    if(r8(work+0x1ce9u)<r8(work+0x1ceau)){first=2;second=1;}
    uint32_t count3=r8(work+0x1cebu);
    if(r8(work+0x1ce8u+first)<count3){uint32_t tmp=first;first=second;second=tmp;}
    if(r8(work+0x1ce8u+second)<count3){third=second;second=3;}
    /* Original comparisons are of the indices, not their counter values. */
    if(first==second&&second==third){weights[0]=33;weights[1]=33;weights[2]=34;}
    else if(first==second&&third<second){weights[0]=15;weights[1]=15;weights[2]=70;}
    else if(second<first&&second==third){weights[0]=0;weights[1]=50;weights[2]=50;}
    else{weights[0]=0;weights[1]=30;weights[2]=70;}
    roll=sdfGetRandInt(NULL,100);
    return less(roll,weights[0])?1u:less(roll,weights[0]+weights[1])?2u:3u;
}

uint64_t ps2NegotiationQuestionFlow7_1_00275DF8(uint64_t raw)
{(void)ps2NegotiationFlowQueue_0026A8A0(raw,0x70003);return 0;}

uint64_t ps2NegotiationQuestionFlow7_3_00275E20(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x7000f);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x7000b);
    uint32_t kind=(uint32_t)ps2NegotiationQuestionCategory_0026B7C8(sx(r32(c+0x15c)));
    w32(c+0x150,kind);
    uint32_t counter=r32(0x54ea20)+kind+0x1ce8u,value=r8(counter);
    if(value<255u)w8(counter,value+1u);
    kind=r32(c+0x150);
    uint32_t question=sdfGetRandInt(NULL,kind?2u:5u);
    uint32_t continuation=r32(c+(kind?0x28u:0x24u));
    w32(c+0x154,question);w32(c+0x1c,continuation);return 0;
}

uint64_t ps2NegotiationQuestionFlow7_11_00275EC8(uint64_t raw)
{
    uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
    if(phase!=0&&phase!=1)return 0;
    uint32_t kind=r32(c+0x150),mode=0;
    if(kind>=1u&&kind<=3u){mode=kind==1u?0x1fu:kind==2u?0x23u:0x1bu;if(r32(c+0x154))mode+=2u;mode+=phase;}
    (void)ps2NegotiationFlowMessage_0026A998(raw,sx(r32(c+0x22c)),mode,phase);
    if(phase)(void)ps2NegotiationFlowQueue_0026A8A0(raw,0x70016);
    return 0;
}

uint64_t ps2NegotiationQuestionFlow7_15_00276018(uint64_t raw)
{
    uint32_t c=(uint32_t)raw,phase=r32(c+0x18);
    if(phase!=0&&phase!=1)return 0;
    uint32_t question=r32(c+0x154),mode=question<5u?0x29u+6u*question+phase:0;
    (void)ps2NegotiationFlowMessage_0026A998(raw,sx(r32(c+0x22c)),mode,phase);
    if(phase)(void)ps2NegotiationFlowQueue_0026A8A0(raw,0x70014);
    return 0;
}

uint64_t ps2NegotiationQuestionFlow7_20_00276130(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x70017);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x70018);
    uint32_t record=0x3e2540u+(r32(c+0x184)*7u+r32(c+0x154))*4u;
    uint32_t type=r16(record),a=r8(record+2u),b=r8(record+3u),chance=50;
    if(type==0u||type==1u){
        int lower;
        if(type==0u){uint32_t source=parameter(r32(c+0x158));uint32_t target=parameter(r32(c+0x15c));lower=less(source,target);}
        else{uint32_t source=r32(c+0x158),target=r32(c+0x15c);lower=r16(source+0x14u)<r16(target+0x14u);}
        chance=lower?b:a;if(r32(c+0x58))chance=100u-chance;
    }
    uint32_t roll=sdfGetRandInt(NULL,100);
    w32(c+0x1c,r32(c+(less(roll,chance)?0x24u:0x28u)));return 0;
}

uint64_t ps2NegotiationQuestionFlow7_22_00276260(uint64_t raw)
{
    uint32_t c=(uint32_t)raw;
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x70019);
    (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x7001a);
    uint32_t source=parameter(r32(c+0x158)),target=parameter(r32(c+0x15c));
    uint32_t chance=less(source,target)?30u:70u,mood=r32(c+0x134);
    if(mood==1u)chance=80;else if(mood==2u)chance=20;
    uint32_t kind=r32(c+0x150);int32_t point_type=0;
    if(kind>=1u&&kind<=3u){
        uint32_t base=kind==1u?0x3e28beu:kind==2u?0x3e28cau:0x3e28b2u;
        uint32_t index=r32(c+0x154)*3u+r32(c+0x184)*36u+r32(c+0x58);
        point_type=signed_byte(r8(base+index*2u));
        ps2UnitAddReasonPoints_00245890(sx((uint32_t)point_type),1);
    }
    uint32_t roll=sdfGetRandInt(NULL,100);
    w32(c+0x1c,r32(c+(less(roll,chance)?0x24u:0x28u)));return 0;
}
