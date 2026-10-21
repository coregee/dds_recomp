/* Native effect estimates. HD names identify roles; original readers, branch
 * conditions, word arithmetic, random calls and COP1 order supply behavior. */
#include "battle_effects.h"
#include "battle_power.h"
#include "battle_affinity.h"
#include "battle_support_access.h"
#include "battle_work_access.h"
#include "nocturne.h"
#include "ee_fpu.h"
#include "libc_printf.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleEffectsAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r8(uint32_t a){return *at(a);}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t lh(uint32_t a){uint32_t v=r16(a);return v&0x8000u?v|0xffff0000u:v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int negative(uint32_t v){return (v>>31)!=0;}
static int less(uint32_t a,uint32_t b){return (a^0x80000000u)<(b^0x80000000u);}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float as_float(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint32_t cvt(uint32_t v){return EE_FPU_CVT_S_W(v);}
static uint32_t truncs(uint32_t v){return EE_FPU_CVT_W_S(v);}
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t mul(uint32_t a,uint32_t b){return EE_FPU_MUL_S(a,b);}
static uint32_t divs(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
static uint32_t sub(uint32_t a,uint32_t b){return EE_FPU_SUB_S(a,b);}
/* EE signed division works on the low words even when the branch guard used
 * all64 bits. Retain BREAK7 for a dirty high lane with zero low divisor. */
static uint32_t quotient(uint32_t a,uint32_t b){
 if(!b)nocturne_break(7);
 uint32_t ua=negative(a)?0u-a:a,ub=negative(b)?0u-b:b,q=ua/ub;
 return negative(a)!=negative(b)?0u-q:q;
}
/* 00266130: reflection/drain zero rates, frozen targets and Pierce are
 * processed before universal/elemental boosts. Pierce also writes main14C. */
float nbGetAisyoRitu(uint64_t skill,uint64_t source,uint64_t target){
 uint32_t main=(uint32_t)nbGetMainProcessData();
 uint32_t attacker=(uint32_t)nbGetUnitWorkFromFormindex(source);
 uint32_t defender=(uint32_t)nbGetUnitWorkFromFormindex(target);
 uint64_t attribute=nbGetNormalSkillAttr(skill);uint32_t ratio=0x3f800000u;
 uint32_t descriptor=0x3d7998u+(uint32_t)skill*60u;
 if(attribute!=UINT64_MAX&&!(attribute>=12&&attribute<15)){
  uint32_t packed=(uint32_t)nbGetAisyo(skill,target,attribute),rate=packed&0xffffu;
  if((packed&0x60000u)&&!rate)rate=100;
  if((r16(defender+0xe)&0xfffu)==2&&!r8(descriptor+2)&&rate<100)rate=100;
  if(datCheckSyojiSkill((datUnitWork_PS2 *)at(attacker),0x165)&&!r8(descriptor+2)&&rate<100){
   uint32_t one=1;rate=100;memcpy(at(main+0x14c),&one,4);
  }
  ratio=mul(cvt(rate),r32(0x54e530));
 }
 int boost=datCheckSyojiSkill((datUnitWork_PS2 *)at(attacker),0x169);
 if(!boost&&attribute>=1&&attribute<=4)boost=nbHatudoCheckSkill((datUnitWork_PS2 *)at(attacker),(int32_t)(0x134u+(uint32_t)attribute));
 return as_float(boost?mul(ratio,0x3fc00000u):ratio);
}
/* 00266350 / 00266878: kept separate entries with shared exact arithmetic.
 * HP has physical-status reduction and a final zero->one rule. MP does not.
 * The first argument is stored/reloaded as a low word; count remains raw64. */
static uint64_t kouka(int mp,uint32_t ratio,uint64_t damage,uint64_t skill,uint64_t source,uint64_t target,uint64_t count){
 uint32_t attacker=(uint32_t)nbGetUnitWorkFromFormindex(source);
 uint32_t defender=(uint32_t)nbGetUnitWorkFromFormindex(target);
 uint32_t d=0x3d7998u+(uint32_t)skill*60u;
 uint32_t type=r16(d+(mp?0x1a:0x16)),power=lh(d+(mp?0x1c:0x18)),offset=lh(d+(mp?0x20:0x1e));
 uint32_t harm=0xffffffffu,heal=0xffffffffu,result=0;
 uint32_t current=defender+(mp?0xa:6),maximum=defender+(mp?0xc:8);
 switch(type){
 case 0:break;
 case 2:{
  uint32_t kind=r8(d+2);heal=offset;
  if(kind==0)result=(uint32_t)nbGetButuriKaifuku(skill,source,target,sx(power));
  else if(kind==1)result=(uint32_t)nbGetMagicKaifuku(skill,source,target,sx(power));
  else break;
  heal=result+offset;break;
 }
 case 3:{uint32_t total=power+offset;if(less(total,r16(current)))harm=r16(current)-total;break;}
 case 4:case 13:harm=power+offset;break;
 case 5:heal=power+offset;break;
 case 6:case 7:{
  result=(uint32_t)nbGetMaxHpWazaPoint(skill,source,target,sx(power));
  if(type==7){heal=result+offset;break;}
  if(!mp){uint32_t status=r16(attacker+0xe)&0xfffu;if(status==0x40)result=quotient(result,2);else if(status==0x200)result=quotient(result,10);}
  harm=result+offset;break;
 }
 case 8:case 10:harm=quotient(r16(type==8?current:maximum)*power,100)+offset;break;
 case 9:case 11:heal=quotient(r16(type==9?current:maximum)*power,100)+offset;if(!mp&&!less(0,heal))heal=1;break;
 case 15:heal=sdfGetRandInt(NULL,power)+offset;break;
 default:
  if(type>=16)break;
  if(!r8(d+2)){
   result=(uint32_t)nbGetButuriAttack(skill,source,target,sx(power));
   if(!mp){uint32_t status=r16(attacker+0xe)&0xfffu;if(status==0x40)result=quotient(result,2);else if(status==0x200)result=quotient(result,10);}
  }else if(r8(d+2)==1)result=(uint32_t)nbGetMagicAttack(skill,source,target,sx(power));
  /* The MP default block retains its native type6 conversion, even though
   * retail switch entry6 goes directly to the HP-based evaluator above. */
  if(mp&&type==6)result=truncs(cvt(result));
  harm=result+offset;
  if(type==14&&(count^UINT64_C(0x8000000000000000))>(UINT64_C(1)^UINT64_C(0x8000000000000000)))harm=quotient(harm,(uint32_t)count);
  break;
 }
 type=r16(d+(mp?0x1a:0x16));
 if(type==1||type==2||type==6||type==7||type==12||type==14){
  if(less(0,harm)){
   uint32_t kind=r8(d+2);
   if(kind==0||kind==1){
    uint32_t random=bits(sdfGetRandFloat(NULL)),value=cvt(harm);
    uint32_t delta=sub(random,0x3f000000u);delta=add(delta,delta);
    delta=mul(delta,r32(mp?0x54e540:(kind?0x54e538:0x54e534)));
    harm=truncs(add(value,mul(value,delta)));
   }
   if(negative(harm))harm=0;
   harm=truncs(mul(cvt(harm),ratio));
   if(evtBitCheck(0xaf2)&&!nbCheckFormationPlayerSide(source))harm=truncs(mul(cvt(harm),r32(mp?0x54e544:0x54e53c)));
  }
 }
 if(!mp&&!harm)harm=1;
 if((uint32_t)damage){
  if(mp){uint32_t available=r16(current);if(less(available,harm))harm=available;}
  else if(type>=12&&type<14){uint32_t available=r16(maximum);if(less(available,harm))harm=available;}
  return sx(harm);
 }
 return sx(heal);
}
uint64_t nbGetKoukaHp(float ratio,uint64_t damage,uint64_t skill,uint64_t source,uint64_t target,uint64_t count){return kouka(0,bits(ratio),damage,skill,source,target,count);}
uint64_t nbGetKoukaMp(float ratio,uint64_t damage,uint64_t skill,uint64_t source,uint64_t target,uint64_t count){return kouka(1,bits(ratio),damage,skill,source,target,count);}

/* 00266D60: special skills use full64 guards. Random status selection scans
 * bits0..13, while ordinary masks retain15 bits. Numeric status precedence
 * is an original signed comparison, not a modern bitset containment test. */
uint64_t nbGetKoukaBadDamage(float ratio,uint64_t skill,uint64_t source,uint64_t target,uint64_t preview){
 uint32_t main=(uint32_t)nbGetMainProcessData(),d=0x3d7998u+(uint32_t)skill*60u;
 if(r8(d+0x24)!=1&&r8(d+0x24)!=3)return 0;
 (void)nbGetUnitWorkFromFormindex(source);uint32_t defender=(uint32_t)nbGetUnitWorkFromFormindex(target);
 uint32_t bad=r16(d+0x26)&0x7fffu;
 if(skill==0x110){uint32_t r=sdfGetRandInt(NULL,100);bad=r<40?0x1000:r<60?0x2000:r<70?0x4000:r<80?0x20:r<90?0x100:0x40;}
 else if(r8(d+0x24)==3){
  uint32_t choices[14],n=0;for(uint32_t bit=0;bit<14;bit++)if((bad>>bit)&1u)choices[n++]=bit;
  /* Original empty masks reach the RNG zero-limit trap. */
  bad=1u<<choices[sdfGetRandInt(NULL,n)];
 }
 uint64_t attribute=sx((uint32_t)datGetBadStatusAttr((int32_t)bad));
 uint32_t affinity=(uint32_t)nbGetAisyo(skill,target,attribute);if(affinity&0x170000u)return 0;
 uint32_t rate=bad==0x800?bits(ratio):divs(cvt(affinity&0xffffu),0x42c80000u);
 if(skill==0x10a&&(r32(main+0x60)&1u)&&(r32(defender)&0x20u)){ps2LibcPrintf(0x544b48);return 0;}
 if((uint32_t)((uint32_t)skill-0x103u)<2&&((uint32_t)nbGetAisyo(UINT64_MAX,target,7)&0x70000u)){ps2LibcPrintf(0x544b68);return 0;}
 if(skill==0x4f&&!(r16(defender+0xe)&0x40u)){ps2LibcPrintf(0x544b88);return 0;}
 if(r8(d+0x25)!=255&&!preview){
  uint32_t chance=cvt(r8(d+0x25)),threshold=mul(mul(divs(chance,0x42c80000u),rate),0x42c80000u);
  uint32_t event=evtBitCheck(0xaf2),flags=r32(defender);
  if(!(flags&0x20u)){
   if(event){if(bad==0x800)threshold=mul(threshold,flags&4u?0x3f000000u:r32(0x54e548));else threshold=mul(threshold,r32(0x54e54c));}
   else if(bad==0x800)threshold=mul(threshold,flags&4u?r32(0x54e550):0x3fc00000u);
  }
  uint32_t random=sdfGetRandInt(NULL,100),limit=truncs(threshold);
  uint32_t percent=mul(rate,0x42c80000u);
  ps2LibcPrintf(0x544ba8,sx(truncs(chance)),sx(truncs(percent)),sx(limit),sx(random));
  if(!less(random,limit))return 0;
 }
 return (int64_t)nbGetBadStat(target)<(int64_t)bad?bad:0;
}
/* 00267180: both native branches require overlap. Preview bypasses the
 * probability calculation, diagnostic and original random draw. */
uint64_t nbGetKoukaBadKaifuku(float ratio,uint64_t skill,uint64_t source,uint64_t target,uint64_t preview){
 uint32_t d=0x3d7998u+(uint32_t)skill*60u;if(r8(d+0x24)!=2)return 0;
 uint32_t attacker=(uint32_t)nbGetUnitWorkFromFormindex(source),defender=(uint32_t)nbGetUnitWorkFromFormindex(target),bad=r16(d+0x26)&0xfffu;
 if(r8(d+0x25)!=255&&!preview){
  uint32_t chance=cvt(r8(d+0x25));
  uint32_t a=(uint32_t)datGetParam((datUnitWork_PS2 *)at(attacker),2);
  uint32_t b=(uint32_t)datGetParam((datUnitWork_PS2 *)at(attacker),5);a+=quotient(b,4);chance=mul(chance,cvt(a));
  uint32_t c=(uint32_t)datGetParam((datUnitWork_PS2 *)at(defender),2);
  uint32_t v=(uint32_t)datGetParam((datUnitWork_PS2 *)at(defender),5);c+=quotient(v,4);
  chance=divs(chance,0x42c80000u);uint32_t scaled=mul(bits(ratio),0x42c80000u);scaled=divs(scaled,cvt(c));chance=mul(chance,scaled);
  ps2LibcPrintf(0x544be8,ps2SoftDoubleFromFloat(as_float(chance)));
  uint32_t random=sdfGetRandInt(NULL,100);if(!less(random,truncs(chance)))return 0;
 }
 uint32_t overlap=bad&r16(defender+0xe)&0xfffu;
 return overlap?bad:0;
}
/* 00268030: add/sub effects follow bit order and can see previous writes.
 * Counter-clearing flags400/40000 write unconditionally, even in preview. */
uint64_t nbSetHojoKouka(uint64_t formation,uint64_t mask,uint64_t point,uint64_t preview){
 uint32_t total=0;
 for(uint32_t bit=0;bit<10;bit++)if(mask&(UINT64_C(1)<<bit)){
  uint64_t delta=bit&1u?sx(0u-(uint32_t)point):point;
  uint32_t value=(uint32_t)nbSetHojoAddCounter(formation,4+bit/2,delta,preview);total+=negative(value)?0u-value:value;
 }
 for(uint32_t bit=12;bit<18;bit++)if(mask&(UINT64_C(1)<<bit)){
  uint32_t value=(uint32_t)nbSetHojoAddCounter(formation,9+bit-12,point,preview);total+=negative(value)?0u-value:value;
 }
 if(mask&0x1000000u){uint32_t value=(uint32_t)nbSetHojoAddCounter(formation,15,point,preview);total+=negative(value)?0u-value:value;}
 for(uint32_t pass=0;pass<2;pass++)if(mask&(pass?0x40000u:0x400u))for(uint32_t type=4;type<=8;type++){
  uint64_t value=nbGetHojoCounter(formation,type);
  if((!pass&&(int64_t)value>0)||(pass&&(int64_t)value<0)){total=pass?total-(uint32_t)value:total+(uint32_t)value;nbSetHojoCounter(formation,type,0);}
 }
 return sx(total);
}
