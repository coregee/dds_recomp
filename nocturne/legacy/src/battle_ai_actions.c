/* Original PS2 action commands. Community names corroborated by Unity roles;
 * original work offsets, store order and exception boundary are preserved. */
#include "battle_ai_actions.h"
#include "script_core.h"
#include "script_movie.h"
#include "compiler_numeric.h"
#include "libc_printf.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleAiActionsAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static int64_t signed32(uint32_t v){return v&0x80000000u?(int64_t)v-INT64_C(0x100000000):v;}

/* 00287E08: parameter is fetched before reloading the actor pointer. */
uint64_t nbCommand_AI_ACT_SKILL(void){
 uint32_t data=(uint32_t)scrGetData();uint16_t skill=(uint16_t)scrGetIntPara(0);
 uint32_t unit=r32(data+0x2c);w16(unit+0x6c,skill);w16(unit+0x6a,1);return 1;
}
uint64_t nbCommand_AI_ACT_ESCAPE(void){
 uint32_t unit=r32((uint32_t)scrGetData()+0x2c);w16(unit+0x6a,7);w16(unit+0x6c,0);return 1;
}
uint64_t nbCommand_AI_SET_CRITICAL(void){
 uint32_t flags=r32((uint32_t)scrGetData()+0x24);w16(flags,(uint16_t)(r16(flags)|0x100));return 1;
}
uint64_t nbCommand_AI_ACT_ATTACK(void){
 uint32_t unit=r32((uint32_t)scrGetData()+0x2c);w16(unit+0x6a,0);nbSetNormalSkill0(unit);return 1;
}

/* 00259018: only attack or skills164..167 rewrite these live descriptors.
 * The diagnostic bytes are native EUC-JP and the actual printf executes. */
void nbSetNormalSkill0(uint64_t raw){
 uint32_t unit=(uint32_t)raw,kind=r16(unit+0x6a),base=0,skill;
 if(kind==0){
  base=0;*at(0x3d79a0)=(uint8_t)(nbHatudoCheckSkill((datUnitWork_PS2 *)at(unit),0x130)!=0);
 }else if(kind==1){
  skill=r16(unit+0x6c);if(skill<0xa4||skill>=0xa8)return;base=skill;
 }else return;
 uint8_t element=0,animation=1;
 if(!(r32(unit)&4)){uint32_t record=0x3497f0+r16(unit+4)*60u;element=*at(record+8);animation=*at(record+9);}
 *at(0x3d6998+base*8u)=element;
 *at(0x3d7998+base*60u+0x15)=animation;
 *at(0x3d7998+base*60u+0x14)=animation;
 *at(0x3dbd20+base*4u+1)=0;
 (void)ps2LibcPrintf(0x544170,0,0,0,0,0,0,0);
}

/* 00246B68: flags are spaced240 bytes apart, sixteen physical slots. */
uint64_t nbGetSelectBit(uint64_t raw){
 uint32_t p=r32((uint32_t)raw)+0x78,bits=0;
 for(unsigned i=0;i<16;i++,p+=0xf0)if(r32(p)&8)bits|=1u<<i;
 return bits;
}
uint64_t nbCommand_BTL_AI_ROT_CLR(void){w32(0x5514e8,0);return 1;}
uint64_t nbCommand_BTL_AI_ROT_NEXT(void){
 uint32_t divisor=(uint32_t)scrGetIntPara(0),next=r32(0x5514e8)+1u;
 w32(0x5514e8,next); /* Increment is visible even when the original BREAK7 fires. */
 if(!divisor)nocturneCompilerArithmeticTrap(7);
 w32(0x5514e8,(uint32_t)(signed32(next)%signed32(divisor)));return 1;
}
uint64_t nbCommand_BTL_AI_ROT_GET(void){
 uint32_t v=r32(0x5514e8);scrSetIntReturnValue((uint64_t)signed32(v));return 1;
}
/* These two PS2 bodies really are unconditional completion commands. */
uint64_t nbCommand_BTL_PNL_ON(void){return 1;}
uint64_t nbCommand_BTL_CAM_ORG(void){return 1;}
