/* Original selector dispatch and BF automatic-target command. */
#include "battle_ai_selection.h"
#include "battle_ai_estimates.h"
#include "battle_ai_filters.h"
#include "battle_ai_actions.h"
#include "battle_targeting.h"
#include "script_core.h"
#include "nocturne.h"
#include "libc_stream.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleAiSelectionAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint64_t lh(uint32_t a){uint32_t v=r16(a);return sx(v&0x8000u?v|0xffff0000u:v);}
static uint32_t slots(uint32_t context){return r32(r32(context));}
static int marked(uint32_t main){
 for(uint32_t i=0;i<16;i++)if(r32(r32(main)+i*240u+0x78)&8)return 1;
 return 0;
}
/* 00287508: bounds use unsigned full64. Original table545800 fixes leaf
 * selector numbers. Existing marks participate even without eligibility. */
uint64_t nbSetSingleTarget2(uint64_t context,uint64_t selector,uint64_t parameter){
 uint32_t ctx=(uint32_t)context;uint64_t result=0;
 if(selector>=11)selector=0;
 switch((uint32_t)selector){
 case 1:nbAiSelLifeMin(context);break;
 case 2:nbAiSelBad(context,parameter);break;
 case 3:nbAiSelId(context,parameter);break;
 case 4:nbAiSelLight(context);break;
 case 5:nbAiSelDark(context);break;
 case 6:nbAiSelPlayer(context);break;
 case 7:nbAiSelJoken(context);break;
 case 8:nbAiSelRnd(context);break;
 case 9:nbAiSelBaarLv(context);break;
 case 10:nbAiSelLvMin(context);break;
 default:break;
 }
 if(!marked(r32(ctx))){selector=0;parameter=0;}
 if(!selector)result=nbAiSelAi(context,parameter,0);
 uint8_t candidates[16];uint32_t count=0,main=r32(ctx);
 for(uint32_t i=0;i<16;i++)if(r32(r32(main)+i*240u+0x78)&8)candidates[count++]=(uint8_t)i;
 if(count){
  uint32_t chosen=candidates[sdfGetRandInt(NULL,count)];
  for(uint32_t i=0;i<16;i++)if(i!=chosen){uint32_t a=slots(ctx)+i*240u+0x78;w32(a,r32(a)&~8u);}
 }
 return result;
}
/* 00287778: positive selectors1..10 mark all eligible slots, without
 * invoking their single-target filters. Out-of-range/negative selects AI. */
uint64_t nbSetGroupTarget2(uint64_t context,uint64_t selector,uint64_t parameter){
 uint32_t ctx=(uint32_t)context;
 if(selector&&selector<11){
  uint32_t base=slots(ctx);
  for(uint32_t i=0;i<16;i++){uint32_t a=base+i*240u+0x78,flags=r32(a);if(flags&4)w32(a,flags|8);}
 }else selector=0;
 if(!marked(r32(ctx))){selector=0;parameter=0;}
 return selector?0:nbAiSelAi(context,parameter,1);
}
/* 002879F0: signed action0/1/5 only. Target outputs are original private
 * stack words; the hosted local-address bridge supplies storage, not values. */
uint64_t nbSetAiTarget(uint64_t context,uint64_t selector,uint64_t parameter){
 uint32_t ctx=(uint32_t)context,unit=r32(ctx+0x2c);uint64_t action=lh(unit+0x6a);
 if(action!=0&&action!=1&&action!=5)return 0;
 if(action==1){
  uint32_t skill=r16(unit+0x6c);
  if(skill==0xde||(skill>=0xe2&&skill<0xe7)||skill==0xfc){
   (void)nbSetEnemySummonFormation(sx(r32(ctx)),sx(r32(ctx+0x1a0)));
   selector=8;unit=r32(ctx+0x2c);
  }
 }
 uint32_t outputs[3],local;
#if UINTPTR_MAX > UINT32_MAX
 local=nocturneLibcStreamLocalAddress(outputs,sizeof outputs);
#else
 local=(uint32_t)(uintptr_t)outputs;
#endif
 nbGetTargetTypeRuleArea(context,sx(unit),local,local+4,local+8,0);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 (void)nbSetSelectOkMark(sx(r32(ctx+0x30)),sx(outputs[0]),sx(outputs[1]),sx(outputs[2]));
 uint64_t result=0;
 if(!outputs[0])result=nbSetSingleTarget2(context,selector,parameter);
 else if(outputs[0]<3)result=nbSetGroupTarget2(context,selector,parameter);
 if(result){unit=r32(ctx+0x2c);w16(unit+0x6a,3);w16(unit+0x6c,0);}
 return result;
}
/* 00287EE0: community command52/AI_TAR_AI. A failed target leaves the
 * prior target bitset intact; successful targeting writes the actual bits. */
uint64_t nbCommand_AI_TAR_AI(void){
 uint64_t context=scrGetData();
 if(!nbSetAiTarget(context,0,0))w32((uint32_t)context+0x3c,(uint32_t)nbGetSelectBit(sx(r32((uint32_t)context))));
 return 1;
}
