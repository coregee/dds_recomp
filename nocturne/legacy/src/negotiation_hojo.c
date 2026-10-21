/* Complete SLUS_209.11 negotiation Hojo-work routines.
 * Original fixed-width reads, table cases, dependency calls and write order
 * determine behavior. HD corroborates roles, not the PS2 memory layout.
 * Semantic/callee-save/declared-RAM profile excludes private guest save/local
 * frames, volatile banks, HI/LO transport and stack aliases into these locals.
 */
#include "negotiation_hojo.h"
#include "battle_work_access.h"
#include "battle_action_status.h"
#include "nocturne.h"
#include <string.h>

static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveNegotiationHojoAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint16_t r16(uint32_t address){uint16_t v;memcpy(&v,at(address),2);return v;}
static uint32_t r32(uint32_t address){uint32_t v;memcpy(&v,at(address),4);return v;}
static void w16(uint32_t address,uint16_t value){memcpy(at(address),&value,2);}
static uint64_t sx(uint32_t value)
{return value&UINT32_C(0x80000000)?UINT64_C(0xffffffff00000000)|value:value;}
static uint32_t unit(uint32_t main,uint32_t form)
{return (uint32_t)nbGetUnitWorkPointer(sx(main),sx(form));}

/* 0026B1E0. Every one of fourteen records is cleared, even ineligible ones.
 * Native T1 is an uncapped output offset: more than eight matching skills
 * really writes beyond the eight initially cleared halfwords. */
uint64_t ps2NegotiationHojoSetAll_0026B1E0(uint64_t raw_context)
{
    uint32_t context=(uint32_t)raw_context;
    for(uint32_t i=0;i<14;i++){
        uint32_t main=r32(context),form_offset=i*128u;
        uint32_t clear=r32(main+0x10u)+form_offset+0x70u;
        for(uint32_t k=0;k<8;k++)w16(clear+2u*k,0);
        uint32_t form=r32(main+0x10u)+form_offset;
        uint16_t flags=(uint16_t)(r16(form)&0xff7fu);
        w16(form,flags);
        if(i>=4||!(flags&1u)||sx(i)==sx(r32(context+0x170u)))continue;
        uint32_t work=unit(main,form);
        if(!datCheckTalk(sx(work)))continue;
        uint32_t count=r16(work+0x38u),offset=0x70u;
        for(uint32_t k=0;k<count;k++){
            uint32_t skill=r16(work+0x3au+2u*k);
            if(*at(0x003d6999u+8u*skill)!=2u)continue;
            if(r32(0x003d7738u+104u*skill)!=7u)continue;
            /* Native reloads both pointers for each successful append and
             * reloads the source count after SH, preserving backed aliases. */
            uint32_t destination=r32(r32(context)+0x10u)+form_offset+offset;
            offset+=2u;
            w16(destination,(uint16_t)skill);
            count=r16(work+0x38u);
        }
    }
    return 0; /* Final SLTI V0,S3,14 is false; HD's void role omits this. */
}

/* 0026B368. Exactly four forms and eight slots; used form excludes all slots. */
uint64_t ps2NegotiationHojoCount_0026B368(uint64_t raw_context)
{
    uint32_t main=r32((uint32_t)raw_context),forms=r32(main+0x10u),count=0;
    for(uint32_t i=0;i<4;i++){
        uint16_t flags=r16(forms+128u*i);
        if(!(flags&1u)||(flags&0x80u))continue;
        uint32_t slots=r32(main+0x10u)+128u*i+0x70u;
        for(uint32_t k=0;k<8;k++){
            uint16_t skill=r16(slots+2u*k);
            if(skill&&!(skill&0x8000u))count++;
        }
    }
    return count;
}

/* 0026B5D4..0026B6F8. Full64 type equality is deliberate: dirty upper bits
 * do not select the clean low32 type. The original nine-word guarded table
 * at544E10 is fixed code data, as required by the interfaces input contract.
 * Underflowed ADDIU(skill,-19C) fails unsigned SLTIU<9 before the table read. */
static int accepts(uint32_t context,uint32_t work,uint32_t skill,uint64_t type)
{
    if(type==0)return skill==0x199u;
    if(type==1)return skill==0x19au||skill==0x1a2u||skill==0x1a3u;
    if(type==2)return skill==0x19bu||skill==0x1a3u;
    if(type!=3||sx(skill-0x19cu)>=9u)return 0;
    switch(skill-0x19cu){
    case 0:{
        uint32_t target=r32(context+0x15cu);
        uint32_t candidate_id=r16(work+4u),target_id=r16(target+4u);
        uint8_t candidate_race=*at(0x003497c4u+60u*candidate_id);
        uint8_t target_race=*at(0x003497c4u+60u*target_id);
        return candidate_race==target_race;
    }
    case 6:return 0; /* Table019C+6 ->26B6FC, explicit no-append path. */
    default:return 1; /* Seven table entries ->26B6EC. */
    }
}

/* 0026B3F8. Preserve the original i/j swap sequence rather than substituting
 * a stable sort: indirect swaps can reverse equal-valued candidates. */
uint64_t ps2NegotiationHojoSearch_0026B3F8(uint64_t raw_context,uint64_t type)
{
    uint32_t context=(uint32_t)raw_context,indices[4],candidate_count=0;
    uint32_t forms=r32(r32(context)+0x10u);
    for(uint32_t i=0;i<4;i++){
        if(!(r16(forms+128u*i)&1u))continue;
        if(sx(i)==sx(r32(context+0x170u)))continue;
        indices[candidate_count++]=i;
    }
    for(uint32_t i=0;i+1u<candidate_count;i++){
        for(uint32_t j=i+1u;j<candidate_count;j++){
            uint32_t main=r32(context);
            uint32_t first=unit(main,r32(main+0x10u)+128u*indices[i]);
            main=r32(context);
            uint32_t second=unit(main,r32(main+0x10u)+128u*indices[j]);
            int32_t first_param=datGetParam((datUnitWork_PS2 *)at(first),4);
            int32_t second_param=datGetParam((datUnitWork_PS2 *)at(second),4);
            if(first_param<second_param){
                uint32_t temporary=indices[i];indices[i]=indices[j];indices[j]=temporary;
            }
        }
    }
    for(uint32_t i=0;i<candidate_count;i++){
        uint32_t main=r32(context),form=r32(main+0x10u)+128u*indices[i];
        uint32_t work=unit(main,form); /* Executes even when form is used. */
        if(r16(form)&0x80u)continue;
        uint32_t skills[8],accepted=0;
        for(uint32_t k=0;k<8;k++){
            uint32_t skill=r16(form+0x70u+2u*k);
            if(!skill||(skill&0x8000u))continue;
            if(accepts(context,work,skill,type))skills[accepted++]=skill;
        }
        if(!accepted)continue;
        uint32_t chosen=skills[sdfGetRandInt(NULL,accepted)];
        for(uint32_t k=0;k<8;k++){
            uint32_t address=form+0x70u+2u*k;
            if(r16(address)==chosen)w16(address,(uint16_t)(chosen|0x8000u));
        }
        w16(form,(uint16_t)(r16(form)|0x80u));
        return sx((indices[i]<<16)|chosen);
    }
    return 0;
}
