/* Retail predicate callbacks and the original packed-condition dispatcher. */
#include "battle_ai_conditions.h"
#include "battle_support_access.h"
#include "battle_targeting.h"
#include "battle_work_access.h"
#include "script_core.h"
#include "script_movie.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleAiConditionsAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint64_t lh(uint32_t a){uint32_t v=r16(a);return sx(v&0x8000u?v|0xffff0000u:v);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint32_t bit(uint64_t index){return UINT32_C(1)<<((uint32_t)index&31u);}
static void self(uint32_t ctx){w32(ctx+0x190,bit(lh(r32(ctx+0x28)+0x92)));}
static uint32_t party(uint32_t ctx,uint32_t k){return r32(r32(ctx)+0x10)+k*128u;}
static int active(uint32_t p){uint32_t flags=r16(p);return (flags&1)&&!(flags&0x38);}
static void mark(uint32_t ctx,uint32_t k){w32(ctx+0x190,r32(ctx+0x190)|bit(lh(party(ctx,k)+2)));}
static uint64_t unit(uint32_t ctx,uint32_t p){return nbGetUnitWorkPointer(sx(r32(ctx)),sx(p));}
/* 002459E8: MULT/DIV1 use the signed wrapped word product for HP cost. */
uint64_t datGetSkillCost(uint64_t raw,uint64_t skill){
 uint32_t u=(uint32_t)raw,d=0x3d7998+(uint32_t)skill*60u,type=*at(d+3),flags=r32(u);
 if(type==1){
  if(!(flags&4)){
   if(r32(0x3497c0+r16(u+4)*60u)&0x200)return 0;
   if(flags&0x20)return 0;
  }
  uint32_t product=r16(u+8)*(uint32_t)r16(d+4);
  int32_t signed_product;memcpy(&signed_product,&product,4);
  uint32_t cost=(uint32_t)(signed_product/100)+r16(d+6);
  return less(0,sx(cost))?sx(cost):1;
 }
 if(type==2){
  if(!(flags&4)&&(r32(0x3497c0+r16(u+4)*60u)&0x400))return 0;
  return r16(d+4);
 }
 return 0;
}
/* 00269170: returns0,1,2,3; nonzero is not exclusively an MP failure. */
uint64_t nbCheckSkillCost(uint64_t index,uint64_t skill){
 uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(index),d=0x3d7998+(uint32_t)skill*60u;
 if(*at(d+2)==1&&(r16(u+0xe)&0xfffu)==0x20)return 3;
 if(*at(d)&4)return 0;
 uint32_t type=*at(d+3);
 if(type==1)return !less(datGetSkillCost(sx(u),skill),r16(u+6));
 if(type==2)return less(r16(u+0xa),datGetSkillCost(sx(u),skill))?2:0;
 return 0;
}
/* 002696F8: fourteen party records; flag2 chooses side, flag4 excludes. */
uint64_t nbGetLvAvg(uint64_t raw,uint64_t side){
 uint32_t main=(uint32_t)raw,sum=0,count=0;
 for(uint32_t k=0;k<14;k++){
  uint32_t p=r32(main+0x10)+k*128u,flags=r16(p);
  if(!(flags&1)||(flags&4)||(side?!((flags&2)!=0):(flags&2)!=0))continue;
  uint32_t u=(uint32_t)nbGetUnitWorkPointer(raw,sx(p));count++;sum+=r16(u+0x14);
 }
 return count?sx(sum/count):0;
}
uint64_t nbAiChkMyHp(uint64_t raw,uint64_t n){
 uint32_t ctx=(uint32_t)raw,u=r32(ctx+0x2c),maximum=r16(u+8);
 if(!maximum)nocturne_break(7);
 if(less(n,r16(u+6)*100u/maximum))return 0;
 self(ctx);return 1;
}
uint64_t nbAiChkMyMp(uint64_t raw,uint64_t n){uint32_t ctx=(uint32_t)raw;if(less(n,r16(r32(ctx+0x2c)+0xa)))return 0;self(ctx);return 1;}
uint64_t nbAiChkFrHp(uint64_t raw,uint64_t n){
 uint32_t ctx=(uint32_t)raw;
 for(uint32_t k=4;k<14;k++){
  uint32_t p=party(ctx,k);if(!active(p))continue;
  uint32_t u=(uint32_t)unit(ctx,p),maximum=r16(u+8);if(!maximum)nocturne_break(7);
  if(!less(n,r16(u+6)*100u/maximum))mark(ctx,k);
 }
 return r32(ctx+0x190)!=0;
}
uint64_t nbAiChkDmgCnt(uint64_t raw,uint64_t n){uint32_t ctx=(uint32_t)raw;if(less(nbGetHojoCounter(lh(r32(ctx+0x28)+0x92),0),n))return 0;self(ctx);return 1;}
uint64_t nbAiChkChkCnt(uint64_t raw,uint64_t n){
 uint32_t ctx=(uint32_t)raw;uint64_t type=sx(r32(ctx+0x194)+1u),index=lh(r32(ctx+0x28)+0x92);
 uint64_t value=nbGetHojoCounter(index,type);if(less(value,127))value=sx((uint32_t)value+1u);
 nbSetHojoCounter(lh(r32(ctx+0x28)+0x92),sx(r32(ctx+0x194)+1u),value);
 if(less(value,n))return 0;self(ctx);return 1;
}
static void markRange(uint32_t ctx,uint32_t first,uint32_t end){for(uint32_t k=first;k<end;k++)if(active(party(ctx,k)))mark(ctx,k);}
uint64_t nbAiChkFrCnt(uint64_t raw,uint64_t n){uint32_t ctx=(uint32_t)raw;if(less(n,lh(r32(ctx)+0x1a)))return 0;markRange(ctx,4,14);return 1;}
uint64_t nbAiChkEnCnt(uint64_t raw,uint64_t n){uint32_t ctx=(uint32_t)raw;if(less(n,lh(r32(ctx)+0x18)))return 0;markRange(ctx,0,4);return 1;}
uint64_t nbAiChkMyBad(uint64_t raw,uint64_t n){uint32_t ctx=(uint32_t)raw;if((r16(r32(ctx+0x2c)+0xe)&0xfffu)!=n)return 0;self(ctx);return 1;}
static uint64_t checkBad(uint32_t ctx,uint64_t n,uint32_t first,uint32_t end){
 for(uint32_t k=first;k<end;k++){uint32_t p=party(ctx,k);if(active(p)&&(r16((uint32_t)unit(ctx,p)+0xe)&0xfffu)==n)mark(ctx,k);}
 return r32(ctx+0x190)!=0;
}
uint64_t nbAiChkFrBad(uint64_t raw,uint64_t n){return checkBad((uint32_t)raw,n,4,14);}
uint64_t nbAiChkEnBad(uint64_t raw,uint64_t n){return checkBad((uint32_t)raw,n,0,4);}
uint64_t nbAiChkEnAllBad(uint64_t raw,uint64_t n){
 uint32_t ctx=(uint32_t)raw,bits=0,count=0;
 for(uint32_t k=0;k<4;k++){uint32_t p=party(ctx,k);if(active(p)&&(r16((uint32_t)unit(ctx,p)+0xe)&0xfffu)==n){count++;bits|=bit(lh(party(ctx,k)+2));}}
 if(sx(count)!=lh(r32(ctx)+0x18))return 0;w32(ctx+0x190,bits);return 1;
}
uint64_t nbAiChkEnId(uint64_t raw,uint64_t n){
 uint32_t ctx=(uint32_t)raw;
 for(uint32_t k=0;k<4;k++){uint32_t p=party(ctx,k);if(!active(p))continue;uint32_t u=(uint32_t)unit(ctx,p);if(!(r32(u)&4)&&r16(u+4)==n)mark(ctx,k);}
 return r32(ctx+0x190)!=0;
}
uint64_t nbAiChkFrId(uint64_t raw,uint64_t n){
 uint32_t ctx=(uint32_t)raw;
 for(uint32_t k=4;k<14;k++){if(sx(k)==sx(r32(ctx+0x30)))continue;uint32_t p=party(ctx,k);if(active(p)&&r16((uint32_t)unit(ctx,p)+4)==n)mark(ctx,k);}
 return r32(ctx+0x190)!=0;
}
/* Original tables545740/545790: code10 is default, other codes0..17
 * map to support fields4..15. Signed counters may exceed their bounds. */
uint64_t nbAiChkHojo(uint64_t index,uint64_t n){
 if(n>=18||n==10)return 0;
 uint64_t type=n<10?4+n/2:n-2,value=nbGetHojoCounter(index,type);
 return n<10&&(n&1)?less(value,0):less(0,value);
}
uint64_t nbAiChkHojoMax(uint64_t index,uint64_t n){
 if(n>=18||n==10)return 0;
 uint64_t type=n<10?4+n/2:n-2,value=nbGetHojoCounter(index,type);
 return n<10&&(n&1)?!less(nbGetHojoCounterMin(type),value):!less(value,nbGetHojoCounterMax(type));
}
static uint64_t checkHojo(uint32_t ctx,uint64_t n,uint32_t first,uint32_t end,int maximum){
 for(uint32_t k=first;k<end;k++){
  uint32_t p=party(ctx,k);if(!active(p))continue;uint64_t index=lh(p+2);
  if(maximum?nbAiChkHojoMax(index,n):nbAiChkHojo(index,n))mark(ctx,k);
 }
 return r32(ctx+0x190)!=0;
}
uint64_t nbAiChkEnHojo(uint64_t raw,uint64_t n){return checkHojo((uint32_t)raw,n,0,4,0);}
uint64_t nbAiChkFrHojo(uint64_t raw,uint64_t n){return checkHojo((uint32_t)raw,n,4,14,0);}
uint64_t nbAiChkEnHojoMax(uint64_t raw,uint64_t n){return checkHojo((uint32_t)raw,n,0,4,1);}
uint64_t nbAiChkFrHojoMax(uint64_t raw,uint64_t n){return checkHojo((uint32_t)raw,n,4,14,1);}
uint64_t nbAiChkBa(uint64_t raw,uint64_t n){(void)n;uint32_t ctx=(uint32_t)raw;if(!(r32(r32(ctx)+0x60)&0x10))return 0;markRange(ctx,0,4);return 1;}
uint64_t nbAiChkSensei(uint64_t raw,uint64_t n){(void)n;uint32_t ctx=(uint32_t)raw;if(!(r32(r32(ctx)+0x60)&0x80))return 0;markRange(ctx,0,4);return 1;}
static uint64_t checkAlignment(uint32_t ctx,uint64_t alignment){
 for(uint32_t k=0;k<4;k++){uint32_t p=party(ctx,k);if(!active(p))continue;uint64_t u=unit(ctx,p);if(!(r32((uint32_t)u)&4)&&datGet3Zokusei(u)==alignment)mark(ctx,k);}
 return r32(ctx+0x190)!=0;
}
uint64_t nbAiChkEnLight(uint64_t raw,uint64_t n){(void)n;return checkAlignment((uint32_t)raw,1);}
uint64_t nbAiChkEnDark(uint64_t raw,uint64_t n){(void)n;return checkAlignment((uint32_t)raw,UINT64_MAX);}
uint64_t nbAiChkPow(uint64_t raw,uint64_t n){(void)n;uint32_t ctx=(uint32_t)raw;if(!nbAiChkHojo(lh(r32(ctx+0x28)+0x92),17))return 0;self(ctx);return 1;}
uint64_t nbAiChkPlv(uint64_t raw,uint64_t n){(void)raw;return !less(sx((uint32_t)datGetPlayerLevel()),n);}
uint64_t nbAiChkPPartyLv(uint64_t raw,uint64_t n){return !less(nbGetLvAvg(sx(r32((uint32_t)raw)),0),n);}
uint64_t nbAiChkTurn(uint64_t raw,uint64_t n){return !less(*at(r32((uint32_t)raw)+0x68),n);}
uint64_t nbAiChkEnHamamHk(uint64_t raw,uint64_t n){
 (void)n;uint32_t ctx=(uint32_t)raw;
 for(uint32_t k=0;k<4;k++){uint32_t p=party(ctx,k);if(active(p)&&!(datGetAisyo(unit(ctx,p),6)&0x70000u))mark(ctx,k);}
 return r32(ctx+0x190)!=0;
}
uint64_t nbAiChkSkillNoMp(uint64_t raw,uint64_t n){uint32_t ctx=(uint32_t)raw;if(!nbCheckSkillCost(lh(r32(ctx+0x28)+0x92),n))return 0;self(ctx);return 1;}
/* 00286730: SRL extracts the low-word upper half, not a full64 shift.
 * No index guard exists; the original table supplies the actual callback. */
uint64_t nbAiChkJoken(uint64_t raw,uint64_t condition){
 uint32_t ctx=(uint32_t)raw,type=(uint32_t)condition>>16;
 if(type){
  uint32_t previous=r32(ctx+0x190),target=r32(0x4f0788+type*4u);
  w32(ctx+0x190,0);uint64_t result;
#if UINTPTR_MAX > UINT32_MAX
  result=nocturneInvokeBattleAiCondition(target,raw,condition&0xffffu);
#else
  result=((uint64_t (*)(uint64_t,uint64_t))(uintptr_t)target)(raw,condition&0xffffu);
#endif
  if(!result)return 0;if(previous)w32(ctx+0x190,r32(ctx+0x190)&previous);
 }
 return 1;
}
/* 00288350: clear the mask first, then set the real VM integer return. */
void nbAiScriptChkJoken(uint64_t condition){uint64_t ctx=scrGetData();w32((uint32_t)ctx+0x190,0);scrSetIntReturnValue(nbAiChkJoken(ctx,condition)!=0);}

/* Original script wrappers OR their fixed type without clamping parameter0. */
uint64_t nbCommand_AI_CHK_MYHP(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x10000));return 1;}
uint64_t nbCommand_AI_CHK_FRHP(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x20000));return 1;}
uint64_t nbCommand_AI_CHK_DMGCNT(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x30000));return 1;}
uint64_t nbCommand_AI_CHK_FRCNT(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x50000));return 1;}
uint64_t nbCommand_AI_CHK_ENCNT(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x60000));return 1;}
uint64_t nbCommand_AI_CHK_MYBAD(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x70000));return 1;}
uint64_t nbCommand_AI_CHK_FRBAD(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x80000));return 1;}
uint64_t nbCommand_AI_CHK_ENBAD(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x90000));return 1;}
uint64_t nbCommand_AI_CHK_ENALLBAD(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0xa0000));return 1;}
uint64_t nbCommand_AI_CHK_ENID(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0xb0000));return 1;}
uint64_t nbCommand_AI_CHK_FRID(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0xc0000));return 1;}
uint64_t nbCommand_AI_CHK_ENHOJO(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0xd0000));return 1;}
uint64_t nbCommand_AI_CHK_FRHOJO(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0xe0000));return 1;}
uint64_t nbCommand_AI_CHK_BA(void){nbAiScriptChkJoken(UINT64_C(0xf0000));return 1;}
uint64_t nbCommand_AI_CHK_ENLIGHT(void){nbAiScriptChkJoken(UINT64_C(0x100000));return 1;}
uint64_t nbCommand_AI_CHK_ENDARK(void){nbAiScriptChkJoken(UINT64_C(0x110000));return 1;}
uint64_t nbCommand_AI_CHK_POW(void){nbAiScriptChkJoken(UINT64_C(0x120000));return 1;}
uint64_t nbCommand_AI_CHK_PLV(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x130000));return 1;}
uint64_t nbCommand_AI_CHK_PPARTYLV(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x140000));return 1;}
uint64_t nbCommand_AI_CHK_MYMP(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x180000));return 1;}
uint64_t nbCommand_AI_CHK_ENHOJOMAX(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x190000));return 1;}
uint64_t nbCommand_AI_CHK_FRHOJOMAX(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x1a0000));return 1;}
uint64_t nbCommand_AI_CHK_ENHAMAMHK(void){nbAiScriptChkJoken(UINT64_C(0x1b0000));return 1;}
uint64_t nbCommand_AI_CHK_SKILLNOMP(void){nbAiScriptChkJoken(scrGetIntPara(0)|UINT64_C(0x1c0000));return 1;}
