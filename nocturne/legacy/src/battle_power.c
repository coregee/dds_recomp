/* Original battle power evaluators, including real libc diagnostics. */
#include "battle_power.h"
#include "battle_affinity.h"
#include "battle_work_access.h"
#include "battle_targeting.h"
#include "nocturne.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "libc_printf.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattlePowerAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t r64(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static uint32_t lh(uint32_t a){uint32_t v=r16(a);return v&0x8000u?v|0xffff0000u:v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float as_float(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint32_t cvt(uint32_t v){return EE_FPU_CVT_S_W(v);}
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t mul(uint32_t a,uint32_t b){return EE_FPU_MUL_S(a,b);}
static uint32_t divs(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
static uint32_t sub(uint32_t a,uint32_t b){return EE_FPU_SUB_S(a,b);}
static void print_ratios(uint32_t source,uint32_t target){
 uint64_t value=ps2SoftDoubleFromFloat(as_float(source));ps2LibcPrintf(UINT64_C(0x544d00),value);
 value=ps2SoftDoubleFromFloat(as_float(target));ps2LibcPrintf(UINT64_C(0x544d10),value);
}
static uint64_t finish(uint32_t value,uint32_t source,uint32_t target){return sx(EE_FPU_CVT_W_S(mul(mul(value,source),target)));}

/* 00268620: both discarded attack/defense queries still execute. Each COP1
 * operation retains its original order. The integer divisor is LHUlevel+10
 * and therefore nonzero for every native level. */
uint64_t nbGetButuriAttack(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(source);
 uint64_t defender=nbGetUnitWorkFromFormindex(target);
 uint32_t sr=bits(nbGetHojoRitu(source,4)),dr=bits(nbGetHojoRitu(target,7));
 (void)datGetNormalAtkPow(unit);(void)datGetDefPow(defender);
 uint32_t enemy=r32(unit)&0x20u;
 uint32_t stat=cvt((uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),0)),level=cvt(r16(unit+0x14));
 uint32_t value=add(add(level,level),add(stat,stat));
 if(enemy){
  uint32_t integer_quotient=(skill?50u:48u)/(r16(unit+0x14)+10u);
  if(!skill)value=mul(mul(value,r32(0x54e554)),r32(0x54e558));
  else value=mul(divs(mul(value,cvt((uint32_t)power)),r32(0x54e55c)),r32(0x54e560));
  value=sub(value,cvt(integer_quotient));
  if(!evtBitCheck(0xaf2))value=mul(value,r32(0x54e564));
 }else if(!skill)value=mul(mul(value,r32(0x54e568)),r32(0x54e56c));
 else value=mul(divs(mul(value,cvt((uint32_t)power)),r32(0x54e570)),r32(0x54e574));
 print_ratios(sr,dr);return finish(value,sr,dr);
}
/* 002688B8 is an unconditional tail call to the physical evaluator. */
uint64_t nbGetButuriKaifuku(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){return nbGetButuriAttack(skill,source,target,power);}

static uint32_t magic_rate(uint32_t unit,uint32_t descriptor,uint64_t power,uint32_t factor_address){
 uint32_t level=r16(unit+0x14);
 uint32_t value=add(cvt(lh(descriptor+0x38)),divs(cvt(level*(uint32_t)power*2u),0x41a80000u));
 uint32_t cap=cvt(lh(descriptor+0x3a));if(EE_FPU_COMPARE_S(cap,value,1))value=cap;
 uint32_t stat=cvt((uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),2));
 uint32_t adjusted=sub(stat,add(divs(cvt(level>160?160:level),0x40a00000u),0x40800000u));
 adjusted=mul(adjusted,0x40200000u);
 uint32_t corrected=add(value,mul(divs(value,0x42c80000u),adjusted));
 uint64_t wide=ps2SoftDoubleFromFloat(as_float(corrected));
 wide=ps2SoftDoubleMul(wide,r64(factor_address));return bits(ps2SoftDoubleToFloat(wide));
}
/* 002688D0: the native loop counter starts100, but each iteration reads the
 * CURRENT unit level for power/stat adjustment. It does not use the counter
 * as a hypothetical level, unlike the managed HD implementation. */
uint64_t nbGetMagicAttack(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(source);(void)nbGetUnitWorkFromFormindex(target);
 uint32_t sr=bits(nbGetHojoRitu(source,5)),dr=bits(nbGetHojoRitu(target,7));
 uint32_t descriptor=0x3d7998u+(uint32_t)skill*60u;
 uint32_t value=magic_rate(unit,descriptor,power,0x544d20);
 uint32_t flags=r32(unit);
 if(!(flags&0x20u)&&r16(unit+0x14)>100){
  uint32_t iteration=100;
  if(iteration<r16(unit+0x14)){
   do{
    uint32_t candidate=magic_rate(unit,descriptor,power,0x544d28);
    if(EE_FPU_COMPARE_S(value,candidate,1))value=candidate;
    ++iteration;
   }while(iteration<r16(unit+0x14));
   flags=r32(unit);
  }
 }
 if(flags&0x20u){
  value=sub(mul(value,0x3f400000u),divs(0x42480000u,cvt(r16(unit+0x14)+10u)));
  if(!evtBitCheck(0xaf2))value=mul(value,r32(0x54e578));
 }
 print_ratios(sr,dr);return finish(value,sr,dr);
}
/* 00268C60: consume the real default RNG before the wrapping numerator.
 * Diagnostic varargs contain the raw power, software-double ratio and SXword
 * result in that order. Its target getter executes despite the unused value. */
uint64_t nbGetMagicKaifuku(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 (void)skill;uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(source);(void)nbGetUnitWorkFromFormindex(target);
 uint32_t ratio=bits(nbGetHojoRitu(source,5));
 uint32_t stat=(uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),2);
 uint32_t random=sdfGetRandInt(NULL,8),numerator=stat*4u+r16(unit+0x14)+random;
 uint32_t value=mul(divs(cvt(numerator),0x41200000u),cvt((uint32_t)power));
 uint64_t wide=ps2SoftDoubleFromFloat(as_float(ratio));value=mul(value,ratio);
 uint64_t result=sx(EE_FPU_CVT_W_S(value));ps2LibcPrintf(UINT64_C(0x544d30),power,wide,result);return result;
}
/* 00268D60: flag20 chooses computed baseHP; other units use stored maxHP.
 * The enemy correction uses floating50/(LHUlevel+10), not integer division. */
uint64_t nbGetMaxHpWazaPoint(uint64_t skill,uint64_t source,uint64_t target,uint64_t power){
 (void)skill;uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(source);(void)nbGetUnitWorkFromFormindex(target);
 uint32_t sr=bits(nbGetHojoRitu(source,4)),dr=bits(nbGetHojoRitu(target,7)),value;
 if(r32(unit)&0x20u){
  value=cvt((uint32_t)datGetBaseMaxHp((datUnitWork_PS2 *)at(unit)));
  value=mul(divs(value,r32(0x54e57c)),cvt((uint32_t)power));value=mul(value,r32(0x54e580));
  value=sub(value,divs(0x42480000u,cvt(r16(unit+0x14)+10u)));
  if(!evtBitCheck(0xaf2))value=mul(value,r32(0x54e584));
 }else value=mul(mul(divs(cvt(r16(unit+8)),r32(0x54e588)),cvt((uint32_t)power)),r32(0x54e58c));
 return finish(value,sr,dr);
}
