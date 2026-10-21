/* Original INF event/NPC selection and fast-panel graph, with real WAP
 * classification. The current-index alias gate deliberately reads the old
 * selection; it does not test the alias's destination row. */
#include "field_inf_graph.h"
#include "event_kuti.h"
#include "scene_lookup.h"
#include "nocturne.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveFieldInfGraphAddress(p);}
static uint16_t r16(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static uint32_t r32(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void w32(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t lb(uint32_t p){uint32_t v=*at(p);return v&0x80u?v|0xffffff00u:v;}
static uint32_t lh(uint32_t p){uint32_t v=r16(p);return v&0x8000u?v|0xffff0000u:v;}
static int below(uint64_t v,uint64_t bound){return(v>>63)!=0||v<bound;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static int same(uint64_t name,uint32_t p){return ps2Strcmp((const char *)at((uint32_t)name),(const char *)at(p))==0;}
void ps2FieldInfImport_00140C38(uint64_t source)
{
    uint32_t from=(uint32_t)source,to=0x2ff420u,end=from+0x3b80u;
    do{uint8_t group[32];memcpy(group,at(from),32);memcpy(at(to),group,32);from+=32;to+=32;}while(from!=end);
}
static uint64_t find(uint64_t name,unsigned mode)
{
    if(!name)return 0;
    for(uint32_t i=0;i<8;i++){
        uint32_t pack=0x2ff420u+i*84u;if(!r32(pack))continue;
        for(uint32_t j=0;j<5;j++){
            uint32_t alias=pack+4u+j*16u;
            if(sx(lb(alias))!=sx(r32(0x2fbf88u)+1u)||!same(name,alias+1u))continue;
            if(mode<2&&lh(0x2ffee0u+r32(0x54edd8u)*312u)!=mode)continue;
            w32(0x54edd8u,r32(pack));return 0x2ff3e0u;
        }
    }
    for(uint32_t i=0;i<40;i++){
        uint32_t row=0x2ffee0u+i*312u;
        if(mode<2?lh(row)!=mode:r16(row)>=2)continue;
        if(sx(lb(row+2u))==sx(r32(0x2fbf88u)+1u)&&same(name,row+4u)){
            w32(0x54edd8u,i);return 0x2ff3e0u;
        }
    }
    return 0;
}
uint64_t ps2FieldInfFindEvent_0013FD28(uint64_t name){return find(name,1);}
uint64_t ps2FieldInfFindNpc_0013FF20(uint64_t name){return find(name,0);}
uint64_t ps2FieldInfFindAny_00140108(uint64_t name){return find(name,2);}
uint64_t ps2FieldInfGet_00140B10(uint64_t line,uint64_t column)
{
    uint32_t row=0x2fff00u+((uint32_t)line-10u)*14u+r32(0x54edd8u)*312u;
    if(!column)return sx(lh(row));
    if(column==1)return sx(lh(row+2u));
    return 0;
}
uint64_t ps2FieldInfFindWarp_00140F48(uint64_t name)
{
    if(!name)return 0;
    for(uint32_t i=0;i<256;i++){
        uint32_t p=0x3030f0u+i*100u,flag=lh(p+2u);
        if(flag&&!evtBitCheck(si(flag)))continue;
        if(sx(lh(p+4u))!=sx(r32(0x2fbf88u)+1u)||!same(name,p+6u))continue;
        w32(0x54ee04u,i);
        uint32_t code,label;
        switch(lb(p)){
        case 1:
            if(si(r32(0x2fbf84u))<10){code=7;label=0x303010u;}
            else if(!*at(p+0x30u)&&lh(p+0x32u)&&si(lh(p+0x32u))<10){code=6;label=0x303000u;}
            else{code=0;label=0x302fa0u;}
            break;
        case 2:code=1;label=0x302fb0u;break;
        case 3:code=2;label=0x302fc0u;break;
        case 4:code=si(r32(0x2fbf84u))<40?3u:9u;label=code==3?0x302fd0u:0x303030u;break;
        case 5:code=5;label=0x302ff0u;break;
        case 10:code=0;label=0x303020u;break;
        default:continue;
        }
        w32(0x54ee08u,code);return label;
    }
    return 0;
}
uint64_t ps2FieldInfLadderQuery_00142A88(uint64_t mode)
{
    uint32_t p=0x3030f0u+r32(0x54ee04u)*100u;
    if(mode==1){
        uint64_t object=dds3SceneBasicSearchName(dds3GetActiveScene(),p+0x18u);
        if(object)return sx(r32((uint32_t)object+4u));
    }else if(below(mode,2)){
        return mode?0:sx(lh(p+0x12u));
    }else if(mode!=2)return 0;
    uint64_t object=dds3SceneBasicSearchName(dds3GetActiveScene(),p+0x24u);
    return object?sx(r32((uint32_t)object+4u)):0;
}
uint64_t ps2FieldInfFastPanel_001402D0(uint64_t line)
{
    uint32_t index=r32(0x54edd8u);
    for(;;){
        uint32_t value;
        if(below(line,10)){
            uint32_t branch=(uint32_t)line-1u,p=0x2ffef0u+index*312u+branch*4u,event=lh(p);
            if(!event)value=lb(p+2u);
            else{
                uint32_t yes=evtBitCheck(si(event));index=r32(0x54edd8u);
                value=lb(0x2ffef0u+index*312u+branch*4u+(yes?3u:2u));
            }
        }else value=lb(0x2fff04u+index*312u+((uint32_t)line-10u)*14u);
        uint64_t next=sx(value);
        if(next==102)return 102;
        if(below(next,103)){
            if(next==100){
                uint32_t object=r32(0x2fcda0u+r32(0x54eddcu)*4u);
                (void)ps2FieldInfFindAny_00140108(sx(r32(object+8u)));
                if(!*at(0x2ffee3u+r32(0x54edd8u)*312u))return 199;
                object=r32(0x2fcda0u+r32(0x54eddcu)*4u);
                (void)ps2FieldInfFindWarp_00140F48(sx(r32(object+8u)));
                switch(r32(0x54ee08u)){
                case 3:return 102;
                case 5:return ps2FieldInfLadderQuery_00142A88(0)?105:104;
                case 6:return 106;
                case 7:return 107;
                default:return 100;
                }
            }
            if(!below(next,101))return next;
            if(!next)return 0;
        }else if(next==104||below(next,104)||next==105)return next;
        if(!below(next,10)){
            uint32_t p=0x2fff00u+index*312u+(value-10u)*14u,type=lh(p);
            if(type!=UINT32_MAX){
                if(r16(p)>=2)return 0;
                switch(lb(0x2ffee3u+index*312u)){
                case 0:return 199;
                case 1:return 2;
                case 2:return 100;
                case 3:return 1;
                default:return 0;
                }
            }
        }
        line=next;
    }
}
