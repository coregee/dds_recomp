/* Native CHECK1 prerequisites, including live packet-window clipping and
 * unsigned death-event fields reached through signed32 DIV remainder. */
#include "battle_check1_packets.h"
#include "battle_action_status.h"
#include "battle_kouka_packets.h"
#include "battle_action_finish.h"
#include "battle_action_process.h"
#include "battle_work_access.h"
#include "battle_support_access.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveBattleCheck1PacketsAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t lh(uint32_t a){return (uint64_t)(int64_t)(int16_t)r16(a);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
/* 001DD5A8: signed LH group equality retains the complete incoming operand. */
uint64_t mdlGetMotionCtrlr(uint64_t model,uint64_t group){
 uint32_t p=r32(r32((uint32_t)model+0x18)+0x14);
 while(p){if(lh(p+0x28)==group)return sx(p);p=r32(p);}return 0;
}
/* 001DDBA8: HD's fixed E903 stub and Unity animator query are different roles. */
uint64_t ps2ModelMotionLength(uint64_t model,uint64_t group){uint32_t p=(uint32_t)mdlGetMotionCtrlr(model,group);return p?r16(r32(p+8)):0;}
/* 00262670: only individual bits1..400 map to effect slots1..11. */
uint64_t nbAddBadEffKoukaPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t bad){
 uint64_t p=nbAddKoukaPacket(nbGetKoukaProcessData(),f,0,c);uint32_t type=0;
 for(uint32_t k=0;k<11;k++)if(bad==(UINT64_C(1)<<k)){type=k+1;break;}
 *at((uint32_t)p+4)=0x17;w32((uint32_t)p+0x14,(uint32_t)form);w32((uint32_t)p+0x28,type);return p;
}
static void clip(uint32_t data,uint8_t kind,uint64_t frame,uint64_t c,uint64_t form){
 for(uint32_t p=r32(data+8);p;){
  uint32_t next=r32(p+12);
  if((int8_t)*at(p+4)==kind&&sx(r32(p+8))==c&&sx(r32(p+20))==form){
   uint64_t end=sx((uint32_t)(int32_t)(int16_t)r16(p)+(uint32_t)(int32_t)(int16_t)r16(p+2));
   if((int64_t)frame<(int64_t)end){uint32_t difference=(uint32_t)frame-r16(p);w16(p+2,(uint16_t)difference);if(difference&0x8000)w16(p+2,0);}
  }
  p=next;
 }
}
/* 002627C0: snapshot successor before clipping, then append original kind10. */
void nbAddNumEffKoukaPacket(uint64_t f,uint64_t duration,uint64_t c,uint64_t form,uint64_t first,uint64_t second,uint64_t type){
 uint64_t data=nbGetKoukaProcessData();clip((uint32_t)data,16,f,c,form);
 uint32_t p=(uint32_t)nbAddKoukaPacket(data,f,duration,c);
 w32(p+0x20,(uint32_t)second);w32(p+0x14,(uint32_t)form);w32(p+0x28,(uint32_t)type);w32(p+0x2c,(uint32_t)first);*at(p+4)=16;
}
/* 002628D0: type4 emits original sound1000A through real de-duplication. */
void nbAddMojiEffKoukaPacket(uint64_t f,uint64_t duration,uint64_t c,uint64_t form,uint64_t type){
 uint64_t data=nbGetKoukaProcessData();clip((uint32_t)data,22,f,c,form);
 if(type==4)(void)nbAddSePacket(f,c,0x1000a);
 uint32_t p=(uint32_t)nbAddKoukaPacket(data,f,duration,c);w32(p+0x28,(uint32_t)type);w32(p+0x14,(uint32_t)form);*at(p+4)=22;
}
/* 002641F8: work cached before marking party flags30; event query follows. */
uint64_t nbMakeDeadPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t force){
 uint64_t main=nbGetMainProcessData();uint32_t a=(uint32_t)form,flags=r32(a+0x78);
 if((flags&1)&&(flags&0x40)){
  uint32_t party=r32((uint32_t)main+16)+(uint32_t)lh(a+0x90)*128;
  uint32_t work=(uint32_t)nbGetUnitWorkPointer(main,sx(party));w16(party,(uint16_t)(r16(party)|0x30));
  uint64_t event=nbCheckEventDead(form);
  if((!event&&!(r32(work)&4))||force==1)(void)nbAddReturnKoukaPacket(f,c,sx(party),1);
 }
 return 1;
}
/* 00264528: actual float32 F12 constant17.0, effect and status packets. */
uint64_t nbMakeBadDamagePacket(uint64_t f,uint64_t c,uint64_t form,uint64_t bad){
 (void)nbAddBadDmgMotKoukaPacket(17.0f,f,c,form,bad);(void)nbAddBadEffKoukaPacket(f,c,form,bad);(void)nbAddBadStatKoukaPacket(f,c,form,bad,1);return 1;
}
/* 002645A8: cache signed form eligibility and actual masked bad status. */
uint64_t nbMakeBadKaifukuPacket(uint64_t f,uint64_t c,uint64_t form){
 uint64_t index=lh((uint32_t)form+0x92),bad=nbGetBadStat(index);
 if(bad)(void)nbAddBadStatKoukaPacket(f,c,form,0xfff,0);
 if((int64_t)index>=16)return 1;
 for(uint32_t k=0;k<12;k++)if(bad==(UINT64_C(1)<<k)){
  (void)nbAddBadMotKaifukuPacket(f,c,form);(void)nbAddBadEffKaifukuPacket(f,c,form);break;
 }
 return 1;
}
static uint64_t event_field(uint64_t event,uint32_t offset){int32_t rem=(int32_t)(uint32_t)event%100;return r16(0x527274u+(uint32_t)rem*28u+offset);}
/* 0028FC38/70/A8/E0: negative remainders read the backed table prefix. */
uint64_t nbGetDeadEventFadeTime(uint64_t event){return event_field(event,0);}
uint64_t nbGetDeadEventFadeOutFrame(uint64_t event){return event_field(event,2);}
uint64_t nbGetDeadEventFadeInFrame(uint64_t event){return event_field(event,6);}
uint64_t nbGetDeadEventFadeStopFrame(uint64_t event){return event_field(event,4);}
/* 00252C28: original type5 gate and actual enemy4..13 death/script queries. */
void nbActionQueueDeadScripts(uint64_t c){
 uint32_t context=(uint32_t)c;if(sx(r32(context+0x34))==5)return;
 for(uint32_t k=4;k<14;k++){
  uint32_t form=r32(r32(context))+k*240;
  if((r32(form+0x78)&1)&&nbActionCheckTimeListDead(c,k)){
   uint64_t script=nbCheckDeadScript(sx(form));if(script)nbPushAction(5,lh(form+0x90),0,script);
  }
 }
}
