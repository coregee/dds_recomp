/* Complete native battle-effect teardown and action-completion dependencies.
 * Native pointers, list ownership and integer operation widths are retained. */
#include "battle_action_finish.h"
#include "battle_action_process.h"
#include "battle_action_sequence.h"
#include "battle_panel_support.h"
#include "effect_recursive_release.h"
#include "script_construction.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "libc_printf.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveBattlePanelSupportAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
/* 0016AC28: retain complete raw64 equality, including dirty upper lanes. */
void effBTLCutListRelease(uint64_t cut){
 uint32_t link=r32((uint32_t)cut+4)+0xc40,node=r32(link);
 while(node){if(sx(node)==cut){w32(link,r32(node+0x11c));return;}link=node+0x11c;node=r32(link);}
}
/* 0016AE08: sixty part slots, unlink, decrement owner count, diagnose, free. */
void effBTLCutDelete(uint64_t cut){
 uint32_t c=(uint32_t)cut;
 for(unsigned k=0;k<60;k++){uint32_t child=r32(c+0x20+k*4);if(child)dds3EffectPartDeleteO(sx(child));}
 effBTLCutListRelease(cut);
 uint32_t owner=r32(c+4),count=r32(owner+0xc3c)-1u;
 w32(owner+0xc3c,count);(void)ps2LibcPrintf(0x532e78,r16(c+0x14),sx(owner),sx(count));
 ps2PoolRelease(c);
}
/* 0016B6C8: two inline part arrays; FFFE slots are intentionally skipped. */
void effBTLPartDelete(uint64_t effect){
 uint32_t e=(uint32_t)effect;
 for(unsigned bank=0;bank<2;bank++){
  unsigned count=r16(e+0x74+bank*0x618);
  for(unsigned k=0;k<count;k++){uint32_t row=e+bank*0x618+0x80+k*24;if(r16(row)!=0xfffe)dds3EffectPartDeleteO(sx(r32(row+4)));}
 }
}
/* 0016AB10: capture each successor before its cut destructor executes.
 * This body releases the memory handle but does not free the effect itself. */
void effBTLDelete(uint64_t effect){
 uint32_t e=(uint32_t)effect,node=r32(e+0xc40);
 while(node){uint32_t next=r32(node+0x11c);effBTLCutDelete(sx(node));node=next;}
 effBTLPartDelete(effect);ps2MemoryHandleFree(r32(e+0xc38));(void)ps2LibcPrintf(0x532e38);
}
/* 00257AC0: actual destruction before clearing the published effect handle. */
uint64_t nbActionCheckAfter(uint64_t context){
 uint32_t c=(uint32_t)context,effect=r32(c+0x74);
 if(effect){effBTLDelete(sx(effect));w32(c+0x74,0);}
 nbActionSetNextSeq(context,22);return 1;
}
/* 0025E9C8: do not invent a previous-link initialization on the empty path. */
void nbLinkKoukaPacket(uint64_t data,uint64_t packet){
 uint32_t d=(uint32_t)data,p=(uint32_t)packet;
 if(!r32(d+8))w32(d+8,p);
 uint32_t tail=r32(d+12);
 if(!tail)w32(d+12,p);
 else{w32(tail+12,p);tail=r32(d+12);w32(p+16,tail);w32(d+12,p);}
 w32(d+4,r32(d+4)+1u);
}
/* 0025EA48: actual64-byte allocation, original partial initialization. */
uint64_t nbAddKoukaPacket(uint64_t data,uint64_t frame,uint64_t type,uint64_t context){
 uint32_t p=ps2PoolAllocate(64);
 w16(p,(uint16_t)frame);w16(p+2,(uint16_t)type);w32(p+8,(uint32_t)context);w32(p+0x20,UINT32_MAX);
 *at(p+4)=0;*at(p+5)=0;w16(p+6,0);
 for(unsigned offset=12;offset<=44;offset+=4)if(offset!=32)w32(p+offset,0);
 nbLinkKoukaPacket(data,sx(p));return sx(p);
}
static uint64_t queueKind(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t time,uint8_t kind){
 uint64_t packet=nbAddKoukaPacket(nbGetKoukaProcessData(),frame,0,context);uint32_t p=(uint32_t)packet;
 w32(p+44,(uint32_t)flags);w32(p+20,(uint32_t)form);w32(p+40,(uint32_t)time);*at(p+4)=kind;return packet;
}
uint64_t nbAddUnitColKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t time){return queueKind(frame,context,form,flags,time,5);}
uint64_t nbAddUnitAKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t time){return queueKind(frame,context,form,flags,time,7);}
/* 002622D0: kind11 publishes its data pointer at+1C, not kind5/7's+14. */
uint64_t nbAddReturnKoukaPacket(uint64_t frame,uint64_t context,uint64_t data,uint64_t time){
 uint64_t packet=nbAddKoukaPacket(nbGetKoukaProcessData(),frame,0,context);uint32_t p=(uint32_t)packet;
 w32(p+40,(uint32_t)time);w32(p+28,(uint32_t)data);*at(p+4)=11;return packet;
}
uint64_t nbMakeUnitFadeOutPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t delta,uint64_t firstTime,uint64_t secondTime){
 (void)nbAddUnitColKoukaPacket(frame,context,form,flags,firstTime);
 (void)nbAddUnitAKoukaPacket(sx((uint32_t)frame+(uint32_t)delta),context,form,0,secondTime);return 1;
}
/* 002517E0: signed raw64 comparisons precede32-bit sign-extended ADDU.
 * Halfword stores wrap; reload both final halfwords before the ordering fix. */
void nbActionSetTimeList(uint64_t context,uint64_t form,uint64_t start,uint64_t lock,uint64_t end){
 uint32_t a=(uint32_t)context+0x88+(uint32_t)form*8u,b=a+2;uint64_t current=r16(a);
 if((int64_t)start<(int64_t)current)start=current;
 if((int64_t)lock>=0){uint64_t next=sx((uint32_t)start+(uint32_t)lock);if((int64_t)current<(int64_t)next)w16(a,(uint16_t)next);}
 if((int64_t)end>=0){uint64_t next=sx((uint32_t)start+(uint32_t)end);if((int64_t)r16(b)<(int64_t)next)w16(b,(uint16_t)next);if(r16(b)<r16(a))w16(b,r16(a));}
}
/* 00253D38: queue the actual death pair/data packet and timeline updates. */
uint64_t nbActionCheckDeadScript(uint64_t context){
 uint32_t c=(uint32_t)context,main=r32(c);
 if(dds3ExistProcess(sx(r32(main+0x104))))return 0;
 w32(r32(c)+0x104,0);
 (void)nbMakeUnitFadeOutPacket(0,context,sx(r32(c+0x28)),0,10,10,10);
 (void)nbAddReturnKoukaPacket(25,context,sx(r32(c+0x24)),1);
 uint32_t slot=r32(c+0x28);uint64_t index=(uint64_t)(int64_t)(int16_t)r16(slot+0x92);
 nbActionSetTimeList(context,index,0,30,30);nbActionSetNextSeq(context,18);return 1;
}
