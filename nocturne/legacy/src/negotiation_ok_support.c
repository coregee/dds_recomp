/* Complete successful-negotiation reward and information prerequisites.
 * Original tables, live RNG/event predicates and real formatter/heap own all
 * outputs. The information record's three signed event halfwords are retained. */
#include "negotiation_ok.h"
#include "nocturne.h"
#include "battle_ai_startup.h"
#include "libc_printf.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveNegotiationOkAddress(a);
#else
 return(void *)(uintptr_t)a;
#endif
}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r8(uint32_t a){return *(uint8_t *)at(a);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint64_t lh(uint32_t a){uint32_t v=r16(a);return sx(v&0x8000u?v|0xffff0000u:v);}
void ps2NegotiationOkItemVariable_0026A938(uint64_t window,uint64_t item){itfMesMngSetVar(window,2,item,3);}
uint64_t ps2NegotiationOkMoneyReward_0026AB80(uint64_t context,uint64_t source,uint64_t target){
 (void)context;(void)source;
 uint32_t roll=sdfGetRandInt(NULL,4),base=r16(0x3497eau+r16((uint32_t)target+4)*60u);
 uint32_t value=((base*(roll+5u)+5u)/10u)*10u;return sx(value?value:1u);
}
static uint64_t item(uint64_t target,uint32_t base){
 uint32_t roll=sdfGetRandInt(NULL,100),p=base+r16((uint32_t)target+4)*48u,total=0;
 for(uint32_t i=0;i<4;i++,p+=2){total+=r8(p-1);if(roll<total)return r8(p);}return 0;
}
uint64_t ps2NegotiationOkItemRewardA_0026BA28(uint64_t target){return item(target,0x3dcb4f);}
uint64_t ps2NegotiationOkItemRewardB_0026BB48(uint64_t target){return item(target,0x3dcb5f);}
uint64_t ps2NegotiationOkInfoEligible_0026BD50(uint64_t index){
 uint32_t p=0x3e4058u+(uint32_t)index*204u;uint64_t flag=lh(p);if(!flag)return 0;
 for(uint32_t i=0;i<3;i++){
  if(!evtBitCheck((uint32_t)flag))return 0;
  if(i==2)return 1;
  p+=2;flag=lh(p);if(!flag)return 1;
 }
 return 0;
}
uint64_t ps2NegotiationOkInfoSelect_0026BBD8(uint64_t type){
 uint32_t base[60],gated[60],start=type==2?30u:0u,plain_count=0,gated_count=0,selected;
 for(uint32_t i=0;i<30;i++)if(!r16(0x3e4058u+(start+i)*204u))base[plain_count++]=start+i;
 for(uint32_t i=0;i<30;i++)if(ps2NegotiationOkInfoEligible_0026BD50(sx(start+i))==1)gated[gated_count++]=start+i;
 uint32_t use_gated=0;if(gated_count)use_gated=sdfGetRandInt(NULL,10)>1;
 if(use_gated)selected=gated[sdfGetRandInt(NULL,gated_count)];
 else selected=base[sdfGetRandInt(NULL,plain_count)];
 (void)ps2LibcPrintf(0x544e48,(uint64_t)use_gated,sx(selected));
 (void)ps2LibcPrintf(0x544e70,(uint64_t)plain_count,(uint64_t)gated_count);return sx(selected);
}
