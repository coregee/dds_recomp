/* Original PS2 effect scoring and summon eligibility. Unity supplies named
 * roles; native word operations, call order and selection quirks govern C. */
#include "battle_ai_estimates.h"
#include "battle_effects.h"
#include "battle_affinity.h"
#include "battle_work_access.h"
#include "libc_printf.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleAiEstimatesAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r8(uint32_t a){return *at(a);}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint64_t lh(uint32_t a){uint32_t v=r16(a);return sx(v&0x8000u?v|0xffff0000u:v);}
static uint64_t lb(uint32_t a){uint32_t v=r8(a);return sx(v&0x80u?v|0xffffff00u:v);}
static int less(uint32_t a,uint32_t b){return (a^0x80000000u)<(b^0x80000000u);}
static int positive(uint64_t v){return !(v>>63)&&v!=0;}
/* 00268F68: preview mode retains actual RNG and support-clear side effects. */
uint64_t nbGetVirtualKoukaPoint(uint64_t skill,uint64_t source,uint64_t target){
 (void)nbGetUnitWorkFromFormindex(source);
 uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(target);
 float ratio=nbGetAisyoRitu(skill,source,target);
 uint64_t bad=nbGetKoukaBadDamage(ratio,skill,source,target,1);
 uint64_t cure=nbGetKoukaBadKaifuku(ratio,skill,source,target,1);
 uint64_t hp_damage=nbGetKoukaHp(ratio,1,skill,source,target,1);
 uint64_t hp_heal=nbGetKoukaHp(ratio,0,skill,source,target,1);
 if(positive(hp_heal)){
  uint32_t missing=r16(unit+8)-r16(unit+6);
  if((sx(missing)^UINT64_C(0x8000000000000000))<(hp_heal^UINT64_C(0x8000000000000000)))hp_heal=sx(missing);
 }
 uint64_t mp_damage=nbGetKoukaMp(ratio,1,skill,source,target,1);
 uint64_t mp_heal=nbGetKoukaMp(ratio,0,skill,source,target,1);
 if(positive(mp_heal)){
  uint32_t missing=r16(unit+12)-r16(unit+10);
  if((sx(missing)^UINT64_C(0x8000000000000000))<(mp_heal^UINT64_C(0x8000000000000000)))mp_heal=sx(missing);
 }
 uint32_t record=0x3d7998u+(uint32_t)skill*60u;
 uint64_t hojo=0,flags=sx(r32(record+0x28));
 if(flags)hojo=nbSetHojoKouka(target,flags,lb(record+0x2c),1);
 uint32_t score=(bad!=0)+(cure!=0);
 if(positive(hp_damage)&&hp_damage>=2)score+=(uint32_t)hp_damage;
 if(positive(hp_heal)&&hp_heal>=2)score+=(uint32_t)hp_heal;
 if(positive(mp_damage)&&mp_damage>=2)score+=(uint32_t)mp_damage;
 if(positive(mp_heal)&&mp_heal>=2)score+=(uint32_t)mp_heal;
 return sx(score+(uint32_t)hojo);
}
/* 00286B68: compact score ordinals are deliberately remapped across every
 * eligible slot, including mode2 candidates skipped before scoring. */
uint64_t nbAiSelAi(uint64_t context,uint64_t unused,uint64_t group){
 uint32_t ctx=(uint32_t)context,unit=r32(ctx+0x2c);
 uint32_t mode=r16(0x3989e2u+r16(unit+4)*164u),skill=0,scores[16],count=0;
 uint64_t action=lh(unit+0x6a);
 (void)unused;
 if(action==1)skill=r16(unit+0x6c);
 else if(action){(void)ps2LibcPrintf(0x5457d8);return 0;}
 if(mode==0){
  uint32_t slots=r32(r32(ctx));
  for(uint32_t i=0;i<16;i++){uint32_t a=slots+i*240u+0x78,flags=r32(a);if(flags&4)w32(a,flags|8);}
  return 0;
 }
 if(mode>2)return 0;
 for(uint32_t i=0;i<16;i++){
  if(!(r32(r32(r32(ctx))+i*240u+0x78)&4))continue;
  uint64_t source=lh(r32(ctx+0x28)+0x92);
  if(mode==2){uint64_t affinity=nbGetVirtualAisyo(skill,source,i);if(affinity==0x20000||affinity==0x10000||affinity==0x40000)continue;}
  /* Native source is reloaded after the virtual-affinity call. */
  uint64_t score=nbGetVirtualKoukaPoint(skill,lh(r32(ctx+0x28)+0x92),i);
  if(mode==1||score)scores[count++]=(uint32_t)score;
 }
 if(!count){(void)ps2LibcPrintf(0x5457e8);return UINT64_MAX;}
 uint32_t slots=r32(r32(ctx));
 if((uint32_t)group){
  for(uint32_t i=0;i<16;i++){uint32_t a=slots+i*240u+0x78,flags=r32(a);if(flags&4)w32(a,flags|8);}
  return 0;
 }
 uint32_t best=0,ordinal=0;
 for(uint32_t i=0;i<count;i++)if(less(best,scores[i])){best=scores[i];ordinal=i;}
 uint32_t eligible=0;
 for(uint32_t i=0;i<16;i++){
  uint32_t a=slots+i*240u+0x78,flags=r32(a);
  if((flags&4)&&eligible++==ordinal){w32(a,flags|8);break;}
 }
 return 0;
}
/* 0028B528: ten old marks clear before the availability check. The count
 * is an unsigned byte and the subsequent loop is not clamped to ten. */
uint64_t nbSetEnemySummonFormation(uint64_t main,uint64_t devil){
 uint32_t work=(uint32_t)main,slots=r32(work);
 for(uint32_t i=4;i<14;i++){uint32_t a=slots+i*240u+0x78;w32(a,r32(a)&~0x800u);}
 uint32_t count=r8(0x3af002u+r32(work+0x34)*38u);
 if(!r32(work+0x84)||!count)return 0;
 uint32_t model=0x34f1f0u+(uint32_t)devil*784u,result=0;
 for(uint32_t i=0;i<count;i++){
  uint32_t slot=slots+(i+4)*240u,flags=r32(slot+0x78);
  if(flags&1)continue;
  w32(slot+0x78,flags|0x800u);
  if(positive(devil))w32(slot+0x50,EE_FPU_MUL_S(r32(model),r32(model+8)));
  result=1;
 }
 return result;
}
