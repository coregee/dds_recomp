/* Eighteen whole original negotiation predicates/phase producers.
 * PS2 instruction widths/order are authoritative; HD corroborates roles.
 * Semantic/callee-save/declared-RAM profile excludes guest private/save-frame
 * aliases, full volatile banks and HI/LO. Queued commands remain data.
 */
#include "negotiation_phases.h"
#include "negotiation_flow.h"
#include "battle_action_status.h"
#include "battle_work_access.h"
#include "battle_targeting.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveNegotiationPhasesAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t lh(uint32_t a){uint32_t v=r16(a);return v&0x8000u?v|0xffff0000u:v;}
static int less(uint32_t a,uint32_t b){return (a^0x80000000u)<(b^0x80000000u);}
static int32_t i32(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t source(uint32_t c){return r32(c+0x158u);}
static uint32_t target(uint32_t c){return r32(c+0x15cu);}
static uint32_t race(uint32_t u){return (uint32_t)datGetRace((datUnitWork_PS2 *)at(u));}
static void queue(uint64_t c,uint32_t a,uint32_t b){(void)ps2NegotiationFlowQueue_0026A8A0(c,a);(void)ps2NegotiationFlowQueue_0026A8A0(c,b);}
static void outcome(uint32_t c,uint32_t offset){uint32_t v=r32(c+offset);w32(c+0x1cu,v);}
static uint32_t message(uint32_t c){uint32_t index=r32(c+0x184u);return r32(c+0x1b0u+(index<<2));}
static void display(uint64_t raw,uint32_t mode){(void)ps2NegotiationFlowMessage_0026A998(raw,sx(message((uint32_t)raw)),mode,0);}
static int special(uint32_t id){switch(id){case 3:case 4:case 5:case 8:case 10:case 13:case 16:case 24:case 29:case 30:case 150:case 153:return 1;default:return 0;}}

/* 0026BEA0: first enabled pair in64 rows; compared IDs are original LHU. */
uint64_t ps2NegotiationPhaseSpecialPair_0026BEA0(uint64_t raw){
 uint32_t c=(uint32_t)raw;
 for(uint32_t i=0;i<64;i++){
  uint32_t row=0x3e3158u+60u*i;
  if(!r16(row))continue;
  uint32_t s=source(c),wanted=r16(row+2u);
  if(r16(s+4u)!=wanted)continue;
  uint32_t t=target(c);wanted=r16(row+4u);
  if(r16(t+4u)==wanted)return i;
 }
 return UINT64_MAX;
}

uint64_t ps2NegotiationPhaseFlow1_03_0026CD80(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x10005u,0x1001fu);
 uint32_t s=source(c);w32(c+0x68u,0x10004u);
 uint64_t talk=datCheckTalk(sx(s));
 uint32_t selected=0x24u;
 if(!talk&&(r32(r32(c+4u)+4u)&0x20u))selected=0x28u;
 outcome(c,selected);return 0;
}
uint64_t ps2NegotiationPhaseFlow1_04_0026CDF8(uint64_t raw){
 uint32_t c=(uint32_t)raw,state=r32(c+0x18u);
 if(!state){w32(c+0x10u,30);return 0;}
 if(state!=1u)return 0;
 uint32_t id=r16(target(c)+4u),mode=0x111u;
 if(!special(id)&&evtGetAgeOfMoon()==8u)mode=0x98u;
 display(raw,mode);return 1;
}
uint64_t ps2NegotiationPhaseFlow1_07_0026D028(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x10008u,0x10003u);
 uint64_t talk=datCheckTalk(sx(target(c)));outcome(c,talk?0x28u:0x24u);return 0;
}
uint64_t ps2NegotiationPhaseFlow1_33_0026D300(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x1000cu,0x1001fu);
 uint32_t sid=r16(source(c)+4u),tid=r16(target(c)+4u);
 w32(c+0x68u,0x10020u);
 if(sid==tid){outcome(c,0x24u);return 0;}
 uint32_t r=race(target(c));
 int restricted=r==0x13u;
 if(!restricted){r=race(target(c));restricted=r==0x12u||r16(target(c)+4u)==0x9au;}
 if(restricted&&!r32(c+0x12cu)){outcome(c,0x28u);return 0;}
 uint64_t alignment=datGet3Zokusei(sx(target(c)));
 outcome(c,(alignment>>63)&&r32(c+0x130u)!=0x1a5u?0x28u:0x24u);return 0;
}
uint64_t ps2NegotiationPhaseFlow1_32_0026D3F0(uint64_t raw){
 static const uint16_t ids[12]={3,4,5,8,10,13,16,24,29,30,150,153};
 uint32_t c=(uint32_t)raw;
 for(uint32_t i=0;i<12;i++)if(r16(target(c)+4u)==ids[i]&&r16(source(c)+4u)==ids[i]){
  w32(c+0x10u,15);display(raw,0x74u+i);return 2;
 }
 uint32_t mode=0x80u;
 if(!special(r16(target(c)+4u))){
  uint32_t r=race(target(c));int restricted=r==0x13u;
  if(!restricted){r=race(target(c));restricted=r==0x12u||r16(target(c)+4u)==0x9au;}
  mode=restricted&&!r32(c+0x12cu)?0x127u:0x20u;
 }
 w32(c+0x10u,15);display(raw,mode);return 1;
}
uint64_t ps2NegotiationPhaseFlow1_18_0026DAB0(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x10021u,0x1001fu);w32(c+0x68u,0x20001u);
 if(special(r16(target(c)+4u))){outcome(c,0x28u);return 0;}
 uint32_t r=race(target(c));
 outcome(c,r==0x21u||evtGetAgeOfMoon()!=8u?0x24u:0x28u);return 0;
}
uint64_t ps2NegotiationPhaseFlow1_20_0026DC78(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x10015u,0x1001fu);
 uint32_t selected=r32(c+0x24u);w32(c+0x68u,0x30001u);w32(c+0x1cu,selected);
 uint32_t t=target(c);
 if(!(r32(t)&4u)){
  uint64_t index=datSearchDevilStock(r16(t+4u));
  if(!(index>>63)&&!r32(c+0x12cu)){selected=r32(c+0x28u);w32(c+0xa8u,0);w32(c+0x1cu,selected);}
 }
 return 0;
}
uint64_t ps2NegotiationPhaseFlow1_22_0026DD88(uint64_t raw){
 uint32_t c=(uint32_t)raw,candidates[10],count=0;queue(raw,0x10018u,0x10017u);outcome(c,0x24u);
 for(uint32_t i=4;i<14;i++){
  uint32_t main=r32(c),form=r32(main+0x10u)+128u*i,flags=r16(form);
  if(!(flags&1u)||!(flags&2u)||(flags&0x38u)||sx(i)==sx(r32(c+0x174u)))continue;
  uint32_t work=(uint32_t)nbGetUnitWorkPointer(sx(main),sx(form));
  if(!datCheckTalk(sx(work)))continue;
  if(*at(0x3dcb40u+48u*r16(work+4u))==1u)candidates[count++]=i;
 }
 if(count){uint32_t choice=sdfGetRandInt(NULL,count),selected=r32(c+0x28u);w32(c+0x1cu,selected);w32(c+0x19cu,candidates[choice]);}
 return 0;
}
uint64_t ps2NegotiationPhaseFlow1_24_0026DFA8(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x1001bu,0x10019u);
 uint32_t selected=r32(c+0x24u),main=r32(c);w32(c+0x1cu,selected);
 int32_t divisor=i32(lh(main+0x1au)-1u);
 if(!divisor)nocturne_break(7); /* Original BREAK stops this profile. */
 int32_t threshold=50/divisor;
 for(uint32_t i=4;i<14;i++){
  main=r32(c);uint32_t form=r32(main+0x10u)+128u*i,flags=r16(form);
  if(!(flags&1u)||!(flags&2u)||(flags&0x38u)||sx(i)==sx(r32(c+0x174u)))continue;
  uint32_t work=(uint32_t)nbGetUnitWorkPointer(sx(main),sx(form));
  if(!datCheckTalk(sx(work))||*at(0x3dcb40u+48u*r16(work+4u))==2u)continue;
  uint32_t roll=sdfGetRandInt(NULL,100u);
  if(less(roll,(uint32_t)threshold)){selected=r32(c+0x28u);w32(c+0x19cu,i);w32(c+0x1cu,selected);return 0;}
 }
 return 0;
}
uint64_t ps2NegotiationPhaseFlow1_26_0026E218(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x10012u,0x1001fu);w32(c+0x68u,0x50001u);
 if(evtGetAgeOfMoon()==8u){outcome(c,0x24u);return 0;}
 uint64_t index=ps2NegotiationPhaseSpecialPair_0026BEA0(raw);
 if(index==UINT64_MAX){outcome(c,0x24u);return 0;}
 uint32_t selected=r32(c+0x28u);w32(c+0x188u,(uint32_t)index);w32(c+0xa8u,0);w32(c+0x1cu,selected);return 0;
}
uint64_t ps2NegotiationPhaseFlow1_28_0026E338(uint64_t raw){
 uint32_t c=(uint32_t)raw,kind=r32(c+0x0cu);
 queue(raw,0x1001du,kind==3u?0x1001eu:0x1001fu);outcome(c,0x28u);w32(c+0x68u,0x1001eu);
 if(!datCheckDying((datUnitWork_PS2 *)at(target(c)))){uint32_t roll=sdfGetRandInt(NULL,100u);if(roll<50u)outcome(c,0x24u);}
 return 0;
}
uint64_t ps2NegotiationPhaseFlow1_35_0026E808(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x10024u,0x10025u);
 uint32_t level=(uint32_t)datGetPlayerLevel(),id=r16(target(c)+4u);
 outcome(c,less(level,*at(0x3497c5u+60u*id))?0x24u:0x28u);return 0;
}

/* 0026EB08. The three special masks are signextended LUI/ORI values and
 * compare to the whole incoming64. Normal checks visit only bits0..30. */
uint64_t ps2NegotiationPhaseCheckCompatibility_0026EB08(uint64_t raw_source,uint64_t raw_target,uint64_t mask,uint64_t flag){
 uint32_t s=(uint32_t)raw_source,t=(uint32_t)raw_target;
 if(mask==sx(0x80000000u)){
  if(evtGetAgeOfMoon())return 0;
  return *at(0x3497c4u+60u*r16(t+4u))!=0x13u;
 }
 if(mask==sx(0x80000001u)){
  uint32_t tl=r16(t+0x14u),sl=r16(s+0x14u);
  if(less(tl-10u,sl))return 0;
  return sdfGetRandInt(NULL,100u)<70u;
 }
 if(mask==sx(0x80000002u)){
  if(flag)return 0;
  return (r32(0x3dcb3cu+48u*r16(t+4u))&2u)!=0;
 }
 uint32_t source_flags=r32(s),traits=(source_flags&4u)?0x14u:r32(0x3dcb3cu+48u*r16(s+4u));
 for(uint32_t k=0;k<31;k++){
  uint32_t bit=1u<<k;if(!(mask&bit))continue;
  switch(bit){
  case 2:case 4:case 8:case 16:case 32:if(!(traits&bit))return 0;break;
  case 0x40:if(less(r16(s+0x14u),r16(t+0x14u)+10u))return 0;break;
  case 0x80:if(less(r16(t+0x14u)-10u,r16(s+0x14u)))return 0;break;
  case 0x100:
   if((source_flags&4u)||(r32(t)&4u))return 0;
   if(*at(0x3497c4u+60u*r16(s+4u))!=*at(0x3497c4u+60u*r16(t+4u)))return 0;
   break;
  case 0x200:if(r16(s+4u)!=0x8fu)return 0;break;
  case 0x400:if(r16(s+4u)!=0x14u)return 0;break;
  default:break;
  }
 }
 return 1;
}
uint64_t ps2NegotiationPhaseFlow6_02_0026F1F0(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x60009u,0x60050u);
 if(datCheckSyojiSkill((datUnitWork_PS2 *)at(source(c)),0x163)==1){outcome(c,0x28u);return 0;}
 uint32_t mode;
 do{mode=sdfGetRandInt(NULL,4u)+0x1cu;}while(sx(mode)==sx(r32(c+0x9cu)));
 display(raw,mode);w32(c+0x9cu,mode);outcome(c,0x24u);return 0;
}
uint64_t ps2NegotiationPhaseFlow6_13_0026F980(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x60010u,0x6000eu);outcome(c,0x24u);
 if(datCheckDying((datUnitWork_PS2 *)at(target(c)))){uint32_t roll=sdfGetRandInt(NULL,100u);if(roll<70u)outcome(c,0x28u);}
 return 0;
}
uint64_t ps2NegotiationPhaseFlow6_28_00270960(uint64_t raw){
 uint32_t c=(uint32_t)raw;queue(raw,0x90001u,0x60024u);
 uint32_t attempt=r32(c+0x8cu);
 if(less(attempt,2u)&&evtBitCheck(8)){outcome(c,0x28u);return 0;}
 attempt=r32(c+0x8cu);
 uint32_t sl=r16(source(c)+0x14u),tl=r16(target(c)+0x14u);
 if(attempt==3u){
  if(evtBitCheck(8)&&!less(sl-17u,tl)){outcome(c,0x24u);return 0;}
  attempt=r32(c+0x8cu);
 }
 sl=r16(source(c)+0x14u);tl=r16(target(c)+0x14u);
 if(less(attempt,3u)&&evtBitCheck(8)&&!less(tl,sl-10u)){outcome(c,0x28u);return 0;}
 uint32_t roll=sdfGetRandInt(NULL,10u);outcome(c,roll<2u?0x24u:0x28u);return 0;
}
uint64_t ps2NegotiationPhaseFlow6_65_00272450(uint64_t raw){
 uint32_t c=(uint32_t)raw;int32_t threshold=50;
 (void)ps2NegotiationFlowQueue_0026A8A0(raw,0xa0001u);
 (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x60042u);
 (void)ps2NegotiationFlowQueue_0026A8A0(raw,0x90001u);
 uint32_t r=race(target(c)),mood=r32(c+0x134u);
 if(mood==1u)threshold=r==0x13u?40:30;else if(mood==2u)threshold=70;
 r=race(target(c));
 if(r!=0x13u){
  int32_t sp=datGetParam((datUnitWork_PS2 *)at(source(c)),1);
  int32_t tp=datGetParam((datUnitWork_PS2 *)at(target(c)),1);
  if(tp+5<sp)threshold-=5;else if(sp<tp-5)threshold+=5;
 }
 if(r32(c+0x90u)){outcome(c,0x24u);return 0;}
 if(less(r32(c+0x8cu),4u)){
  uint32_t roll=sdfGetRandInt(NULL,100u);outcome(c,less(roll,(uint32_t)threshold)?0x24u:0x28u);
 }else{
  uint32_t roll=sdfGetRandInt(NULL,10u);
  if(roll<3u)outcome(c,0x28u);
  else{display(raw,0x129u);outcome(c,0x2cu);}
 }
 return 0;
}
