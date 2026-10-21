/* Original scalar kouka constructors and list queries. FPR values are copied
 * bit for bit; packet fields retain native widths and store order. */
#include "battle_kouka_packets.h"
#include "battle_action_finish.h"
#include "battle_action_process.h"
#include "battle_work_access.h"
#include "process_lists.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveBattleKoukaPacketsAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t bits(float value){uint32_t v;memcpy(&v,&value,4);return v;}
static uint64_t add(uint64_t frame,uint64_t context){return nbAddKoukaPacket(nbGetKoukaProcessData(),frame,0,context);}
static uint64_t tagged(uint64_t packet,uint8_t kind){*at((uint32_t)packet+4)=kind;return packet;}
uint64_t nbAddHatudoEffectEndPacket(uint64_t f,uint64_t c){return tagged(add(f,c),0x3a);}
uint64_t nbAddUnitHomeColKoukaPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t time){uint64_t p=add(f,c);w32((uint32_t)p+40,(uint32_t)time);w32((uint32_t)p+20,(uint32_t)form);return tagged(p,6);}
uint64_t nbAddUnitHomeAKoukaPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t time){uint64_t p=add(f,c);w32((uint32_t)p+40,(uint32_t)time);w32((uint32_t)p+20,(uint32_t)form);return tagged(p,8);}
uint64_t nbAddMotionStopClearPacket(uint64_t f,uint64_t c,uint64_t form){uint64_t p=add(f,c);w32((uint32_t)p+20,(uint32_t)form);return tagged(p,0x21);}
uint64_t nbAddMotionKoukaPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t motion){uint64_t p=add(f,c);w32((uint32_t)p+40,(uint32_t)motion);w32((uint32_t)p+20,(uint32_t)form);return tagged(p,0x1b);}
uint64_t nbAddDmgMotKoukaPacket(float ratio,uint64_t f,uint64_t c,uint64_t form,uint64_t motion){uint64_t p=add(f,c);w32((uint32_t)p+44,(uint32_t)motion);w32((uint32_t)p+20,(uint32_t)form);w32((uint32_t)p+40,bits(ratio));return tagged(p,9);}
uint64_t nbAddEasyDmgMotKoukaPacket(float ratio,uint64_t f,uint64_t c,uint64_t form){uint64_t p=add(f,c);w32((uint32_t)p+40,bits(ratio));w32((uint32_t)p+20,(uint32_t)form);return tagged(p,0x35);}
uint64_t nbAddBadDmgMotKoukaPacket(float ratio,uint64_t f,uint64_t c,uint64_t form,uint64_t motion){uint64_t p=add(f,c);w32((uint32_t)p+44,(uint32_t)motion);w32((uint32_t)p+20,(uint32_t)form);w32((uint32_t)p+40,bits(ratio));return tagged(p,10);}
uint64_t nbAddBadEffKaifukuPacket(uint64_t f,uint64_t c,uint64_t form){uint64_t p=add(f,c);w32((uint32_t)p+20,(uint32_t)form);return tagged(p,0x18);}
uint64_t nbAddHpMpKoukaPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t flags,uint64_t time){uint64_t p=add(f,c);w32((uint32_t)p+44,(uint32_t)flags);w32((uint32_t)p+20,(uint32_t)form);w32((uint32_t)p+40,(uint32_t)time);return tagged(p,0x11);}
uint64_t nbAddBadStatKoukaPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t flags,uint64_t time){uint64_t p=add(f,c);w32((uint32_t)p+44,(uint32_t)flags);w32((uint32_t)p+20,(uint32_t)form);w32((uint32_t)p+40,(uint32_t)time);return tagged(p,0x13);}
uint64_t nbAddBadMotKaifukuPacket(uint64_t f,uint64_t c,uint64_t form){uint64_t p=add(f,c);w32((uint32_t)p+20,(uint32_t)form);return tagged(p,0x14);}
/* 00262C18: missing party suppresses allocation; original type200 maps toFF. */
uint64_t nbAddDeadPcmPacket(uint64_t f,uint64_t c,uint64_t form){
 uint64_t party=nbGetUnitWorkFromFormindex((uint64_t)(int64_t)(int16_t)r16((uint32_t)form+0x92));
 if(!party)return 0;
 uint64_t p=add(f,c);tagged(p,0x24);w32((uint32_t)p+20,(uint32_t)form);
 w32((uint32_t)p+40,(r16((uint32_t)party+14)&0xfff)==0x200?255:r16((uint32_t)party+4));return p;
}
/* 00262CC0: suppress sounds already present in the native signed-frame window. */
uint64_t nbAddSePacket(uint64_t f,uint64_t c,uint64_t sound){if(nbCheckSePacket(f,sound,5))return 0;uint64_t p=add(f,c);w32((uint32_t)p+40,(uint32_t)sound);return tagged(p,0x19);}
uint64_t nbAddSkillNamePacket(uint64_t f,uint64_t c,uint64_t skill){uint64_t p=add(f,c);w32((uint32_t)p+40,(uint32_t)skill);return tagged(p,0x31);}
uint64_t nbAddFormOnOffPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t flags){uint64_t p=add(f,c);w32((uint32_t)p+40,(uint32_t)flags);w32((uint32_t)p+20,(uint32_t)form);return tagged(p,0x26);}
uint64_t nbAddFlyKoukaPacket(uint64_t f,uint64_t c,uint64_t form){uint64_t p=add(f,c);w32((uint32_t)p+20,(uint32_t)form);tagged(p,0x2d);w32((uint32_t)p+40,0);return p;}
/* 00263350: read the packet's initialized time before replacing it. Retain
 * live main/packet aliases and native order of stores, not HD field guesses. */
uint64_t nbAddDeadEventKoukaPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t value){
 uint64_t data=nbGetKoukaProcessData(),p=nbAddKoukaPacket(data,f,0,c);uint32_t m=r32((uint32_t)data);
 w32(m+64,0);w32((uint32_t)p+20,(uint32_t)form);uint32_t previous=r32((uint32_t)p+40);
 w32(m+68,7);w32(m+136,previous);w32((uint32_t)p+40,(uint32_t)value);return tagged(p,0x2e);
}
uint64_t nbAddFadeOutKoukaPacket(uint64_t f,uint64_t c,uint64_t value,uint64_t time){uint64_t p=add(f,c);w32((uint32_t)p+44,(uint32_t)time);w32((uint32_t)p+40,(uint32_t)value);return tagged(p,0x2f);}
uint64_t nbAddFadeInKoukaPacket(uint64_t f,uint64_t c,uint64_t value,uint64_t time){uint64_t p=add(f,c);w32((uint32_t)p+44,(uint32_t)time);w32((uint32_t)p+40,(uint32_t)value);return tagged(p,0x30);}
uint64_t nbAddPadShockPacket(uint64_t f,uint64_t c,uint64_t first,uint64_t second,uint64_t time){uint64_t p=add(f,c);w16((uint32_t)p+44,(uint16_t)time);w16((uint32_t)p+40,(uint16_t)first);w16((uint32_t)p+42,(uint16_t)second);return tagged(p,0x34);}
uint64_t nbAddPanelStockFadeOutPacket(uint64_t f,uint64_t c){return tagged(add(f,c),0x38);}
uint64_t nbAddPanelStockEndPacket(uint64_t f,uint64_t c){return tagged(add(f,c),0x39);}
uint64_t nbMakeUnitFadeInPacket(uint64_t f,uint64_t c,uint64_t form,uint64_t flags,uint64_t delta,uint64_t firstTime,uint64_t secondTime){
 (void)nbAddUnitColKoukaPacket(f,c,form,flags,0);(void)nbAddUnitHomeAKoukaPacket(f,c,form,firstTime);
 (void)nbAddUnitHomeColKoukaPacket(sx((uint32_t)f+(uint32_t)delta),c,form,secondTime);return 1;
}
uint64_t nbMakeFlyBadPacket(uint64_t f,uint64_t c,uint64_t form){(void)nbAddFlyKoukaPacket(f,c,form);return 1;}
/* 0025EE78: signed byte compared to full kind64; snapshot successor before
 * the flag write and interpret enabled across the complete argument. */
void nbOnOffKoukaPacketFlag(uint64_t kind,uint64_t mask,uint64_t enabled){
 uint32_t process=r32((uint32_t)nbGetMainProcessData()+0xf4);if(!process)return;
 uint32_t data=(uint32_t)dds3GetProcessData(sx(process)),node=r32(data+8);
 while(node){uint32_t next=r32(node+12);if((uint64_t)(int64_t)(int8_t)*at(node+4)==kind){uint8_t v=*at(node+5);*at(node+5)=(uint8_t)(enabled?v|mask:v&~mask);}node=next;}
}
/* 0025EF10: frame-window subtraction is SUBU/SX32; both comparisons are
 * signed64. Kind25/28/29 and sign-extended sound word compare to full sound. */
uint64_t nbCheckSePacket(uint64_t frame,uint64_t sound,uint64_t window){
 uint32_t main=(uint32_t)nbGetMainProcessData(),data=(uint32_t)dds3GetProcessData(sx(r32(main+0xf4))),node=r32(data+8);
 int64_t lower=(int64_t)sx((uint32_t)frame-(uint32_t)window);
 while(node){int64_t start=(int16_t)r16(node);if((int64_t)frame>=start&&lower<start){int kind=(int8_t)*at(node+4);if((kind==25||kind==28||kind==29)&&sx(r32(node+40))==sound)return 1;}node=r32(node+12);}return 0;
}
