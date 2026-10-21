/* Original battle support scaling and packed affinity selection. */
#include "battle_affinity.h"
#include "battle_support_access.h"
#include "battle_work_access.h"
#include "battle_targeting.h"
#include "nocturne.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleAffinityAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t lh(uint32_t a){uint32_t v=r16(a);return v&0x8000u?v|0xffff0000u:v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}

/* 00267F58: word addition/difference, full64 type and preview guards.
 * Bounds are queried again when clamping, as in the original call sequence. */
uint64_t nbSetHojoAddCounter(uint64_t formation,uint64_t type,uint64_t delta,uint64_t preview){
 uint64_t party=nbGetPartyFromFormindex(formation);if(!party)return 0;
 uint32_t address=(uint32_t)party+8u+(uint32_t)type*2u;
 uint32_t old=lh(address);uint64_t value=sx(old+(uint32_t)delta);
 if(!less(type,0)&&less(type,20)){
  if(less(nbGetHojoCounterMax(type),value))value=nbGetHojoCounterMax(type);
  if(less(value,nbGetHojoCounterMin(type)))value=nbGetHojoCounterMin(type);
 }
 if(!preview){uint16_t stored=(uint16_t)value;memcpy(at(address),&stored,2);}
 return sx((uint32_t)value-old);
}

/* 002684B0: native COP1 values, including moon adjustment for unit125,
 * reversed support types6/7 and the type4 counter15 multiplier. */
float nbGetHojoRitu(uint64_t formation,uint64_t type){
 uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(formation);
 uint64_t counter=nbGetHojoCounter(formation,type);uint32_t result=0x3f800000u;
 if(r16(unit+4)==0x125){
  uint32_t moon=evtGetAgeOfMoon()-4u;moon+=moon>>31;
  moon=(moon>>1)|(moon&0x80000000u);
  counter=sx((uint32_t)counter+moon);
 }
 if(counter){
  uint32_t word=(uint32_t)counter;
  if(!less(type,6)&&less(type,8))word=less(counter,0)?(0u-word)*2u:0u-word;
  else if(!less(counter,0))word*=2u;
  result=EE_FPU_MUL_S(EE_FPU_ADD_S(EE_FPU_CVT_S_W(word),0x41000000u),0x3e000000u);
 }
 if(type==4&&less(0,nbGetHojoCounter(formation,15)))result=EE_FPU_MUL_S(result,0x40200000u);
 float value;memcpy(&value,&result,4);return value;
}

/* 00267890: party-local packed affinities, temporary effects and passives.
 * LW and LUI sign extension is retained in the final raw64 result. The scaled
 * rate is a signed word quotient and is not masked back to sixteen bits. */
uint64_t nbGetAisyo(uint64_t skill,uint64_t target,uint64_t attribute){
 uint64_t unit=nbGetUnitWorkFromFormindex(target);
 if(!less(target,16))return datGetAisyo(unit,attribute);
 uint64_t party=nbGetPartyFromFormindex(target);
 if(attribute==UINT64_MAX)return 0;
 if(!less(attribute,12)&&less(attribute,16))return 100;
 uint32_t offset=(uint32_t)attribute*4u;
 uint64_t packed=sx(r32((uint32_t)party+0x30u+offset));
 uint64_t row=nbGetHojoCounter(target,19);
 if(less(0,row))packed=sx(r32(0x3a7fe0u+((uint32_t)row*16u+(uint32_t)attribute)*4u));
 uint32_t status=r16((uint32_t)unit+0xe)&0xfffu;
 if(status==0x200)packed=sx(r32(0x3abda0u+offset));
 else if(status==0x400)packed=sx(r32(0x3abd60u+offset));
 uint64_t support=attribute==1?10:attribute==2?9:attribute==6?12:attribute==7?11:UINT64_MAX;
 if(support!=UINT64_MAX&&less(0,nbGetHojoCounter(target,support)))packed|=0x10000u;
 if(!less(skill,0)&&attribute!=5&&attribute!=11){
  uint32_t kind=*at(0x3d799au+(uint32_t)skill*60u);
  if(kind<2&&less(0,nbGetHojoCounter(target,kind?13:14)))packed|=0x20000u;
 }
 uint64_t rate=packed&0xffffu;
 if(attribute<11&&attribute!=5){
  uint32_t a=(uint32_t)attribute;
  datUnitWork_PS2 *work=(datUnitWork_PS2 *)at((uint32_t)unit);
  if(nbHatudoCheckSkill(work,(int32_t)((a<5?0x143u:0x142u)+a)))packed|=0x10000u;
  if(a<5){
   if(nbHatudoCheckSkill(work,(int32_t)(0x14du+a)))packed|=0x40000u;
   if(nbHatudoCheckSkill(work,(int32_t)(0x152u+a)))packed|=0x20000u;
  }
  uint32_t passive=a<5?0x139u+a:0x138u+a;
  if(nbHatudoCheckSkill(work,(int32_t)passive)){
   uint32_t index=a<5?a:a-1u;
   uint32_t product=lh(0x3dc268u+index*8u)*(uint32_t)rate;
   int64_t signed_product=product&0x80000000u?(int64_t)product-INT64_C(0x100000000):(int64_t)product;
   rate=sx((uint32_t)(signed_product/100));
  }
 }
 return (packed&UINT64_C(0xffffffffffff0000))|rate;
}

/* 00268EB8: source formation is unused; 20000 precedes40000 then10000. */
uint64_t nbGetVirtualAisyo(uint64_t skill,uint64_t source,uint64_t target){
 (void)source;uint64_t attribute=nbGetNormalSkillAttr(skill);
 if(attribute==UINT64_MAX||(!less(attribute,12)&&less(attribute,15)))return 0;
 uint64_t packed=nbGetAisyo(skill,target,attribute);
 return packed&0x20000u?0x20000u:packed&0x40000u?0x40000u:packed&0x10000u?0x10000u:0;
}
