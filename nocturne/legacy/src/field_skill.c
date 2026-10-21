/* Complete field-skill/party-hazard algorithms from SLUS_209.11.
 * Original instructions, not HD formulas, determine arithmetic and read order.
 * COP1 uses raw-bit instruction primitives; software-double calls remain real.
 * This source-only draft has no behavior-validation or registration credit.
 * Scope excludes original guest save frames/private-stack aliases, volatile
 * register banks and primary/secondary HI/LO transport. Native MULT/MULT1/DIV
 * values below are retained with defined fixed-width arithmetic. */
#include "field_skill.h"
#include "battle_targeting.h"
#include "nocturne.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "script_movie.h"
#include "sound_bank_flow.h"
#include <stdlib.h>
#include <string.h>

static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveFieldSkillAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t r64(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t lh(uint32_t a){uint32_t v=r16(a);return v&0x8000u?v|0xffff0000u:v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int64_t signed64(uint64_t v){return v<=INT64_MAX?(int64_t)v:-1-(int64_t)(UINT64_MAX-v);}
static int32_t signed32(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint32_t asr(uint32_t v,unsigned n){return n?((v>>n)|((v&0x80000000u)?UINT32_MAX<<(32u-n):0)):v;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float as_float(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint32_t cvt(uint32_t v){return EE_FPU_CVT_S_W(v);}
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t sub(uint32_t a,uint32_t b){return EE_FPU_SUB_S(a,b);}
static uint32_t mul(uint32_t a,uint32_t b){return EE_FPU_MUL_S(a,b);}
static uint32_t divs(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
static uint64_t finish(uint32_t v){return sx(EE_FPU_CVT_W_S(v));}
static uint32_t mult_word(uint32_t a,uint32_t b){return (uint32_t)((int64_t)signed32(a)*(int64_t)signed32(b));}
static uint32_t quotient(uint32_t a,uint32_t b){
 /* Actual R5900 signed32 quotient, including the instruction's zero-divisor
  * result before a caller's delayed BREAK. No signed C overflow is invoked. */
 int64_t n=signed32(a),d=signed32(b);
 if(!d)return n<0?1u:UINT32_MAX;
 return (uint32_t)(n/d);
}
static uint32_t record(uint64_t skill){return 0x003d7998u+(uint32_t)skill*60u;}
static uint32_t global_work(void){return r32(0x0054ea20u);}

/* 00242E00: both otherwise-unused native attack/defense queries execute
 * before the source flags are reloaded. Integer division precedes the final
 * floating conversion/subtraction; the level-derived divisor cannot be0. */
uint64_t ps2FieldSkillPhysicalPower_00242E00(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 uint32_t unit=(uint32_t)source;
 (void)datGetNormalAtkPow(source);(void)datGetDefPow(target);
 uint32_t enemy=r32(unit)&0x20u,value;
 uint32_t stat_word=(uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),0);
 uint32_t level=r16(unit+0x14),stat=cvt(stat_word),lv=cvt(level);
 if(enemy){
  uint32_t q=quotient(skill?50u:48u,level+10u);
  if(!skill){
   uint32_t scale=r32(0x54e47c),factor=r32(0x54e480);
   stat=add(stat,stat);value=add(lv,lv);value=add(value,stat);
   value=mul(value,scale);value=mul(value,factor);
  }else{
   uint32_t p=cvt((uint32_t)power),scale=r32(0x54e484),factor;
   stat=add(stat,stat);factor=r32(0x54e488);value=add(lv,lv);
   value=add(value,stat);value=mul(value,p);value=divs(value,scale);value=mul(value,factor);
  }
  value=sub(value,cvt(q));
 }else if(!skill){
  uint32_t scale=r32(0x54e48c),factor=r32(0x54e490);
  stat=add(stat,stat);value=add(lv,lv);value=add(value,stat);
  value=mul(value,scale);value=mul(value,factor);
 }else{
  uint32_t scale=r32(0x54e494),factor=r32(0x54e498),p=cvt((uint32_t)power);
  stat=add(stat,stat);value=add(lv,lv);value=add(value,stat);
  value=mul(value,p);value=divs(value,scale);value=mul(value,factor);
 }
 return finish(value);
}
/* 00242FE0: the native16-byte wrapper releases its frame before the tail. */
uint64_t ps2FieldSkillPhysicalRecovery_00242FE0(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 return ps2FieldSkillPhysicalPower_00242E00(skill,source,target,power);
}

/* 00242FF8: only A1's unit and the low word of A0/A3 enter the formula.
 * Keep the real float->software-double->multiply->float call sequence. */
uint64_t ps2FieldSkillMagicPower_00242FF8(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 (void)target;uint32_t unit=(uint32_t)source,desc=record(skill);
 uint32_t level=r16(unit+0x14),cap=lh(desc+0x3a),product=mult_word(level,(uint32_t)power),base=lh(desc+0x38);
 uint32_t limit=cvt(cap),v=cvt(base),scaled=cvt(product<<1);
 scaled=divs(scaled,0x41a80000u);v=add(v,scaled);
 if(EE_FPU_COMPARE_S(limit,v,1))v=limit;
 uint32_t stat_word=(uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),2);
 level=r16(unit+0x14);uint32_t stat=cvt(stat_word);
 uint32_t lv=cvt(level),ratio=divs(v,0x42c80000u);
 lv=divs(lv,0x40a00000u);lv=add(lv,0x40800000u);stat=sub(stat,lv);stat=mul(stat,0x40200000u);
 ratio=mul(ratio,stat);ratio=add(v,ratio);
 uint64_t wide=ps2SoftDoubleFromFloat(as_float(ratio));
 wide=ps2SoftDoubleMul(wide,r64(0x5430c0));v=bits(ps2SoftDoubleToFloat(wide));
 if(r32(unit)&0x20u){
  uint32_t denominator=cvt(level+10u);uint32_t corrected=mul(v,0x3f400000u);
  v=divs(0x42480000u,denominator);v=sub(corrected,v);
 }
 return finish(v);
}

/* 00243170: consume actual default RNG even when power is0. The level is
 * loaded after that call, and both ADDU operations wrap before CVT.S.W. */
uint64_t ps2FieldSkillMagicRecovery_00243170(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 (void)skill;(void)target;uint32_t unit=(uint32_t)source;
 uint32_t stat=(uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),2);
 uint32_t random=sdfGetRandInt(NULL,8),level=r16(unit+0x14),value=stat<<2;
 uint32_t p=cvt((uint32_t)power);value+=level;value+=random;
 return finish(mul(divs(cvt(value),0x41200000u),p));
}

/* 00243200: native enemy correction uses floating50/(level+10).
 * The skill and target slots are not read by this original body. */
uint64_t ps2FieldSkillMaxHpPower_00243200(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 (void)skill;(void)target;uint32_t unit=(uint32_t)source,value;
 if(r32(unit)&0x20u){
  uint32_t base=(uint32_t)datGetBaseMaxHp((datUnitWork_PS2 *)at(unit));
  uint32_t scale=r32(0x54e49c),v=cvt(base),level=r16(unit+0x14),p=cvt((uint32_t)power);
  uint32_t factor=r32(0x54e4a0),denominator=cvt(level+10u);
  v=divs(v,scale);uint32_t correction=divs(0x42480000u,denominator);
  v=mul(v,p);v=mul(v,factor);value=sub(v,correction);
 }else{
  uint32_t maximum=r16(unit+8),p=cvt((uint32_t)power),scale=r32(0x54e4a4);
  value=cvt(maximum);value=divs(value,scale);value=mul(value,p);
 }
 return finish(value);
}

/* 002432D0: incoming A1 is unused. Attribute-1 and12..14 return exact1;
 * other signed byte attributes really call the registered affinity lookup. */
float ps2FieldSkillAffinityRate_002432D0(uint64_t skill,uint64_t source,uint64_t target){
 (void)source;uint32_t raw=*at(0x3d6998u+((uint32_t)skill<<3));
 int32_t attribute=raw<128u?(int32_t)raw:(int32_t)raw-256;
 if(attribute==-1||(attribute>=12&&attribute<15))return as_float(0x3f800000u);
 uint64_t affinity=datGetAisyo(target,sx((uint32_t)attribute));
 uint64_t value=(uint32_t)affinity&0xffffu;
 /* 243330 BLTZ is unreachable after ANDIffff; retain the native unsigned
  * conversion shape rather than importing HD affinity/status special cases. */
 uint32_t v;
 if(signed64(value)<0){uint32_t folded=((uint32_t)value&1u)|((uint32_t)value>>1);v=cvt(folded);v=add(v,v);}
 else v=cvt((uint32_t)value);
 return as_float(mul(v,r32(0x54e4a8)));
}

/* 00243368: the first live jump table selects the complete HP/MP formula.
 * In the second dispatch the original reload is ALWAYS the HP mode at+16,
 * even for incoming type1 (MP). Tables are actual guest RAM reads, not an HD
 * enum remapping. Unknown executable targets fail as an unbound code domain. */
uint64_t ps2FieldSkillEffectAmount_00243368(uint64_t skill,uint64_t type,uint64_t source,uint64_t target){
 uint32_t rate=bits(ps2FieldSkillAffinityRate_002432D0(skill,source,target));
 uint32_t desc=record(skill),unit=(uint32_t)target,current=0,maximum=0,mode=0,parameter=0,extra=0;
 uint64_t healing=UINT64_MAX,damage=UINT64_MAX;
 if(type==0){
  maximum=r16(unit+8);current=r16(unit+6);mode=r16(desc+0x16);parameter=lh(desc+0x18);extra=lh(desc+0x1e);
 }else if(type==1){
  maximum=r16(unit+0xc);current=r16(unit+0xa);extra=lh(desc+0x20);mode=r16(desc+0x1a);parameter=lh(desc+0x1c);
 }
 if(mode<16){
  uint32_t destination=r32(0x5430d0u+mode*4u);
  switch(destination){
  case 0x243470:return 0;
  case 0x243478:healing=sx(parameter+extra);break;
  case 0x243480:healing=sx(sdfGetRandInt(NULL,parameter)+extra);break;
  case 0x243498:case 0x2434a0:{
   uint32_t product=mult_word(destination==0x243498?current:maximum,parameter);
   healing=sx(quotient(product,100)+extra);
   if(signed64(healing)<=0)healing=1;
   break;
  }
  case 0x2434d0:{
   uint32_t category=*at(desc+2);uint64_t amount=0;
   if(category==0)amount=ps2FieldSkillPhysicalRecovery_00242FE0(skill,source,target,sx(parameter));
   else if(category==1)amount=ps2FieldSkillMagicRecovery_00243170(skill,source,target,sx(parameter));
   healing=sx((uint32_t)amount+extra);break;
  }
  case 0x243538:healing=sx((uint32_t)ps2FieldSkillMaxHpPower_00243200(skill,source,target,sx(parameter))+extra);break;
  case 0x243558:damage=sx(parameter+extra);break;
  case 0x243560:case 0x243568:{
   uint32_t product=mult_word(destination==0x243560?current:maximum,parameter);
   damage=sx(quotient(product,100)+extra);break;
  }
  case 0x243590:{
   uint32_t category=*at(desc+2);uint64_t amount=0;
   if(category==0){
    amount=ps2FieldSkillPhysicalPower_00242E00(skill,source,target,sx(parameter));
    uint32_t status=r16((uint32_t)source+0xe)&0xfffu;
    if(status==0x40||status==0x200){uint32_t word=(uint32_t)amount;amount=sx(asr(word+(word>>31),1));}
   }else if(category==1)amount=ps2FieldSkillMagicPower_00242FF8(skill,source,target,sx(parameter));
   damage=sx((uint32_t)amount+extra);break;
  }
  case 0x243620:damage=sx((uint32_t)ps2FieldSkillMaxHpPower_00243200(skill,source,target,sx(parameter))+extra);break;
  case 0x243640:{
   uint64_t value=sx(parameter+extra);if(less(value,current))damage=sx(current-(uint32_t)value);break;
  }
  default:abort();
  }
 }
 uint32_t post=(uint32_t)r16(desc+0x16)-1u;
 if(post<12){
  switch(r32(0x543110u+post*4u)){
  case 0x243698:
   if(signed64(damage)>0){
    uint32_t random=bits(sdfGetRandFloat(NULL));
    uint32_t value=cvt((uint32_t)damage),scale=r32(0x54e4ac);
    random=sub(random,0x3f000000u);random=add(random,random);random=mul(random,scale);
    random=mul(value,random);value=add(value,random);
    damage=sx(EE_FPU_CVT_W_S(value));if(signed64(damage)<0)damage=0;
    damage=finish(mul(cvt((uint32_t)damage),rate));
   }
   break;
  case 0x243700:
   if(signed64(healing)>0)healing=finish(mul(cvt((uint32_t)healing),rate));
   break;
  case 0x24371c:break;
  default:abort();
  }
 }
 if(damage==0)damage=1;
 return signed64(healing)<0?sx(0u-(uint32_t)damage):healing;
}

/* 00243760: random-status selection enumerates bits0..11 into the original
 * twelve-word logical list and consumes RNG even for an empty mask (the real
 * zero-limit callee traps). The host array does not claim guest-stack aliases.
 * Status-equality/rate and source-flag corrections follow the native order. */
uint64_t ps2FieldSkillStatus_00243760(uint64_t skill,uint64_t source,uint64_t target){
 uint32_t desc=record(skill),effect=r16(desc+0x26),category=*at(desc+0x24),status=effect&0xfffu;
 if(category==3){
  uint32_t list[12],count=0;
  for(uint32_t bit=0;bit<12;bit++)if(status&(1u<<bit))list[count++]=bit;
  uint32_t choice=sdfGetRandInt(NULL,count);status=1u<<(list[choice]&31u);
 }
 uint32_t resistance;
 if(*at(desc+0x24)==1){
  uint64_t attribute=sx((uint32_t)datGetBadStatusAttr((int32_t)status));
  uint32_t affinity=(uint32_t)datGetAisyo(target,attribute);
  resistance=0;
  if(!(affinity&0x00170000u))resistance=divs(cvt(affinity&0xffffu),0x42c80000u);
 }else resistance=0x3f800000u;
 uint32_t chance=*at(desc+0x25);uint64_t apply=1;
 if(chance!=0xffu){
  uint32_t source_flags=r32((uint32_t)source);
  chance=*at(desc+0x25);uint32_t value=cvt(chance),rate;
  if(source_flags&0x20u){
   uint32_t scale=r32(0x54e4b0);rate=divs(value,0x42c80000u);rate=mul(rate,resistance);
   rate=mul(rate,0x42c80000u);rate=mul(rate,scale);
  }else{
   rate=divs(value,0x42c80000u);rate=mul(rate,resistance);rate=mul(rate,0x42c80000u);
  }
  uint64_t random=sx(sdfGetRandInt(NULL,100));
  uint64_t threshold=sx(EE_FPU_CVT_W_S(rate));apply=less(random,threshold);
 }
 if(!apply)return 0;
 if(*at(desc+0x24)==1){
  uint32_t existing=r16((uint32_t)target+0xe)&0xfffu;
  if(!(existing<status))apply=0;
 }
 return apply?status:0;
}

/* 00243998: null source/target skip the three effect calculations, but never
 * skip the later literal descriptor program8..11 global-flag operations.
 * Every post-call unit/global read remains live for aliased input graphs. */
uint64_t ps2FieldSkillExecute_00243998(uint64_t skill,uint64_t source,uint64_t target){
 uint64_t hp=0,mp=0,status=0;
 uint32_t target_word=(uint32_t)target,desc=record(skill);
 if(source&&target){
  hp=ps2FieldSkillEffectAmount_00243368(skill,0,source,target);
  mp=ps2FieldSkillEffectAmount_00243368(skill,1,source,target);
  status=ps2FieldSkillStatus_00243760(skill,source,target);
  if(!(hp||mp||status))return 0;
  if(status){
   uint32_t category=*at(desc+0x24);
   if(category==1||category==3)datSetBadStat((datUnitWork_PS2 *)at(target_word),(uint32_t)status);
   else datResetBadStat((datUnitWork_PS2 *)at(target_word),(uint32_t)status);
  }
  if(mp)(void)datAddMp((datUnitWork_PS2 *)at(target_word),signed32((uint32_t)mp));
  if(hp){
   (void)datAddHp((datUnitWork_PS2 *)at(target_word),signed32((uint32_t)hp));
   if(!r16(target_word+6))datSetBadStat((datUnitWork_PS2 *)at(target_word),0x800);
  }
 }
 uint64_t program=sx(r32(desc+0x30));
 if(program>=8&&program<=11){
  uint32_t work=global_work();
  uint32_t flags=r32(work+0xa4c);flags|=1u<<((uint32_t)program-8u);w32(work+0xa4c,flags);
 }
 return 1;
}

/* Shared arithmetic, not a collapsed party pass: AF2 is queried separately
 * for every eligible member, then the CURRENT global pointer is reloaded for
 * the HP store. Both source HP and damage remain cached across the call. */
static void difficulty_damage(uint32_t offset,uint32_t hp,uint32_t damage){
 uint32_t difficulty=evtBitCheck(0xaf2);
 uint32_t doubled=damage<<1;
 if(!difficulty)damage=doubled+damage;
 if(!damage)damage=1;
 uint32_t work=global_work(),remaining=hp-damage;
 if(!less(0,sx(remaining)))remaining=1;
 w16(work+offset+0xa,(uint16_t)remaining);
}

/* 002447C0: the cursor is global+A50, FOUR bytes before datUnitWork.
 * The first full16 pass runs for types1/2/4/5/6; types4..6 then perform a
 * separate status pass, with freshly loaded pointers/flags/HP at each slot. */
void ps2FieldSkillPartyDamage_002447C0(uint64_t type){
 if(type==1||type==4||type==5||type==6){
  for(uint32_t offset=0xa50;offset<0xa50+16u*0xecu;offset+=0xec){
   uint32_t cursor=global_work()+offset;
   if(!(r32(cursor+4)&2))continue;
   uint32_t hp=r16(cursor+0xa);if(!hp)continue;
   difficulty_damage(offset,hp,quotient(hp,10));
  }
 }
 if(type==2){
  for(uint32_t offset=0xa50;offset<0xa50+16u*0xecu;offset+=0xec){
   uint32_t cursor=global_work()+offset;
   if(!(r32(cursor+4)&2))continue;
   uint32_t hp=r16(cursor+0xa);if(!hp)continue;
   difficulty_damage(offset,hp,hp>>1);
  }
 }
 if(type==3){
  uint32_t cursor=global_work()+0xa50;
  for(unsigned slot=0;slot<16;slot++,cursor+=0xec){
   if(r16(cursor+8)==0xc0)continue;
   if(!(r32(cursor+4)&2))continue;
   if(r16(cursor+0xa))w16(cursor+0xa,1);
  }
 }
 /* Original ADDIU and SLTIU operate on the sign-extended word difference. */
 if(sx((uint32_t)type-4u)<3){
  for(uint32_t offset=0;offset<16u*0xecu;offset+=0xec){
   uint32_t work=global_work(),cursor=work+offset+0xa50;
   if(!(r32(cursor+4)&2)||!r16(cursor+0xa))continue;
   if(type==4)datSetBadStat((datUnitWork_PS2 *)at(work+offset+0xa54),0x40);
   if(type==5)datSetBadStat((datUnitWork_PS2 *)at(global_work()+offset+0xa54),0x100);
   if(type==6)datSetBadStat((datUnitWork_PS2 *)at(global_work()+offset+0xa54),0x20);
  }
 }
}

/* 00244A38: type1 requires status40; type2 applies the same3-percent damage
 * to every present, alive unit; type3 consumes independent RNG per unit and
 * unsigned division; type4 halves HP without any event/RNG dependency. */
void ps2FieldSkillPartyStatusDamage_00244A38(uint64_t type){
 if(type==1){
  for(uint32_t offset=0xa50;offset<0xa50+16u*0xecu;offset+=0xec){
   uint32_t cursor=global_work()+offset;
   if(!(r32(cursor+4)&2)||!(r16(cursor+0x12)&0x40))continue;
   uint32_t hp=r16(cursor+0xa);if(!hp)continue;
   uint32_t numerator=(hp<<1)+hp;
   difficulty_damage(offset,hp,quotient(numerator,100));
  }
 }
 if(type==2){
  for(uint32_t offset=0xa50;offset<0xa50+16u*0xecu;offset+=0xec){
   uint32_t cursor=global_work()+offset;
   if(!(r32(cursor+4)&2))continue;
   uint32_t hp=r16(cursor+0xa);if(!hp)continue;
   uint32_t numerator=(hp<<1)+hp;
   difficulty_damage(offset,hp,quotient(numerator,100));
  }
 }
 if(type==3){
  for(uint32_t offset=0xa50;offset<0xa50+16u*0xecu;offset+=0xec){
   uint32_t cursor=global_work()+offset;
   if(!(r32(cursor+4)&2))continue;
   uint32_t hp=r16(cursor+0xa);if(!hp)continue;
   uint32_t random=sdfGetRandInt(NULL,2),product=mult_word(hp,random+1u);
   uint32_t work=global_work(),damage=product/100u;
   if(!damage)damage=1;
   uint32_t remaining=hp-damage;if(!less(0,sx(remaining)))remaining=1;
   w16(work+offset+0xa,(uint16_t)remaining);
  }
 }
 if(type==4){
  uint32_t cursor=global_work()+0xa50;
  for(unsigned slot=0;slot<16;slot++,cursor+=0xec){
   if(!(r32(cursor+4)&2))continue;
   uint32_t hp=r16(cursor+0xa);if(!hp)continue;
   uint32_t damage=hp>>1;if(!damage)damage=1;
   uint32_t remaining=hp-damage;if(!less(0,sx(remaining)))remaining=1;
   w16(cursor+0xa,(uint16_t)remaining);
  }
 }
}

/* 00244CC0: preserve the TWO distinct native signed32 products, including
 * MULT1's low-word result, before ADDU wraps. HI/LO and HI1/LO1 are native
 * hidden-state obligations beyond this readable algorithm's proof scope. */
void ps2FieldSkillPartyPipeDamage_00244CC0(uint64_t first,uint64_t second){
 if(!(first||second))return;
 for(uint32_t offset=0xa50;offset<0xa50+16u*0xecu;offset+=0xec){
  uint32_t cursor=global_work()+offset;
  if(!(r32(cursor+4)&2))continue;
  uint32_t hp=r16(cursor+0xa);if(!hp)continue;
  uint32_t tenth=quotient(hp,10),numerator=(hp<<1)+hp,three_percent=quotient(numerator,100);
  uint32_t primary=mult_word(tenth,(uint32_t)first);
  uint32_t secondary=mult_word(three_percent,(uint32_t)second); /* 244D64 MULT1. */
  difficulty_damage(offset,hp,primary+secondary);
 }
}

/* 00244DD8: flag1 selects slots; max-clamp routines really execute, in HP
 * then MP order. The final status SH uses a fresh global pointer, not the
 * initial work or either callee's input pointer. */
void ps2FieldSkillPartyRecover_00244DD8(void){
 for(uint32_t offset=0;offset<16u*0xecu;offset+=0xec){
  uint32_t work=global_work(),cursor=work+offset+0xa50;
  if(!(r32(cursor+4)&1))continue;
  (void)datAddHp((datUnitWork_PS2 *)at(work+offset+0xa54),9999);
  work=global_work();(void)datAddMp((datUnitWork_PS2 *)at(work+offset+0xa54),9999);
  work=global_work();w16(work+offset+0xa62,0);
 }
}

/* Native BF314/374/390 wrappers. Script parameters and sound are their real
 * registered dependencies, with no host result stubs or suppressed effects. */
uint64_t ps2FieldSkillScriptPartyDamage_0010D078(void){
 uint64_t type=scrGetIntPara(0);ps2FieldSkillPartyDamage_002447C0(type);return 1;
}
uint64_t ps2FieldSkillScriptPartyRecover_0010D0A0(void){
 ps2FieldSkillPartyRecover_00244DD8();(void)ps2SoundPlay(0x10,0x7f,0x3f);return 1;
}
uint64_t ps2FieldSkillScriptPartyRecoverSilent_0010D0D0(void){
 ps2FieldSkillPartyRecover_00244DD8();return 1;
}
