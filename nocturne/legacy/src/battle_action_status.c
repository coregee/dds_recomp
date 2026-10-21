/* Original CHECK1 prerequisites. Native array addressing uses low32 while
 * SLTI/equality operands retain all64 bits. No managed array guards added. */
#include "battle_action_status.h"
#include "battle_work_access.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveBattleActionStatusAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t r8(uint32_t a){return *at(a);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t signed_form(uint32_t a){return sx((uint32_t)(int32_t)(int16_t)r16(a+0x92));}

/* 002515D8: HP is unsigned16, including values above32767. */
uint64_t nbActionGetTimeListHp(uint64_t c,uint64_t f){return r16((uint32_t)c+0x8c+(uint32_t)f*8);}
/* 002515E8: zero timeline HP is insufficient for flag100 immortality. */
uint64_t nbActionCheckTimeListDead(uint64_t c,uint64_t f){
 if(r16((uint32_t)c+0x8c+(uint32_t)f*8))return 0;
 return !(nbGetDevilFormatFlag(f)&0x100);
}
/* 00251628: the native enemy group has ten physical forms, indices4..13. */
uint64_t nbActionCheckTimeListDeadEnemyParty(uint64_t c,uint64_t f){
 uint32_t first=(f<4||(f>>63))?4:0,end=first?14:4;
 for(uint32_t k=first;k<end;k++){
  uint32_t forms=r32(r32((uint32_t)c));
  if((r32(forms+k*240+0x78)&1)&&!nbActionCheckTimeListDead(c,k))return 0;
 }
 return 1;
}
/* 002516E8: ADDU signs the low32 sum; positive overflow wraps on SH. */
uint64_t nbActionAddTimeListHp(uint64_t c,uint64_t f,uint64_t delta){
 if(r32(r32((uint32_t)c)+0x60)&0x20000)return 0;
 uint32_t a=(uint32_t)c+0x8c+(uint32_t)f*8,v=r16(a)+(uint32_t)delta;
 if(v&0x80000000u){w16(a,0);return 1;}
 w16(a,(uint16_t)v);return 0;
}
/* 00251760,00251858,00251890: fixed32-row, unsigned16 timer fields. */
uint64_t nbActionGetEndTime(uint64_t c,uint64_t f){return r16((uint32_t)c+0x8a+(uint32_t)f*8);}
uint64_t nbActionGetAllEndTime(uint64_t c){
 uint16_t maximum=0;for(uint32_t k=0;k<32;k++){uint16_t v=r16((uint32_t)c+0x8a+k*8);if(v>maximum)maximum=v;}return maximum;
}
uint64_t nbActionGetAllUnlockTime(uint64_t c){
 uint16_t maximum=0;for(uint32_t k=0;k<32;k++){uint16_t v=r16((uint32_t)c+0x88+k*8);if(v>maximum)maximum=v;}return maximum;
}
/* 0026A7D0: descriptor flag is a signed LW result, not an unsigned word. */
uint64_t nbGetDevilFormatFlag(uint64_t f){
 uint32_t w=(uint32_t)nbGetUnitWorkFromFormindex(f);
 if(!w||(r32(w)&4))return 0;
 return sx(r32(0x3497c0+r16(w+4)*60u));
}
static uint64_t kuisibari(uint64_t f,uint32_t skill){
 uint32_t w=(uint32_t)nbGetUnitWorkFromFormindex(f);
 if(!datCheckSyojiSkill((datUnitWork_PS2 *)at(w),skill))return 0;
 uint32_t p=(uint32_t)nbGetPartyFromFormindex(f);uint16_t flags=r16(p);
 if(flags&0x400)return 0;
 w16(p,(uint16_t)(flags|0x200));return 1;
}
/* 0026A2D8,0026A338: actual skill lookup, then native party consumption gate. */
uint64_t nbCheckKuisibariSkill(uint64_t f){return kuisibari(f,0x159);}
uint64_t nbCheckKuisibari2Skill(uint64_t f){return kuisibari(f,0x168);}
/* 0026A398: absence tolerated here; flag200 marks use and flag400 prevents reuse. */
void nbSetKuisibariStop(uint64_t f){
 uint32_t p=(uint32_t)nbGetPartyFromFormindex(f);if(!p)return;
 uint16_t flags=r16(p);if(flags&0x200)w16(p,(uint16_t)(flags|0x400));
}
/* 00259A30: masked condition200 overrides even a flag4 player ID with255. */
uint64_t nbGetUnitID(uint64_t work){
 uint32_t w=(uint32_t)work,id=(r32(w)&4)?0:r16(w+4);
 return (r16(w+14)&0xfff)==0x200?255:id;
}
/* 00259AB0,00259B10,00259B70: A4-byte AI record+ A0/A2, unsigned LHU. */
uint64_t nbCheckEventDead(uint64_t form){
 uint32_t id=(uint32_t)nbGetUnitID(nbGetUnitWorkFromFormindex(signed_form((uint32_t)form)));
 if(!id)return 0;
 uint32_t a=0x398a80+id*164;return r16(a)||r16(a+2);
}
uint64_t nbCheckDeadScript(uint64_t form){
 uint32_t id=(uint32_t)nbGetUnitID(nbGetUnitWorkFromFormindex(signed_form((uint32_t)form)));
 return id?r16(0x398a80+id*164):0;
}
uint64_t nbCheckDeadEvent(uint64_t form){
 uint32_t id=(uint32_t)nbGetUnitID(nbGetUnitWorkFromFormindex(signed_form((uint32_t)form)));
 return id?r16(0x398a82+id*164):0;
}
/* 002584C8: twelve signed byte indices; no native upper-bound guard. */
void nbUpdateOrder(void){
 uint32_t m=(uint32_t)nbGetMainProcessData();
 for(uint32_t k=0;k<12;k++){
  uint8_t index=r8(m+0x48+k);if(index&0x80)continue;
  uint16_t flags=r16(r32(m+0x10)+(uint32_t)index*128);
  if(!(flags&1)||(flags&0x20))*at(m+0x48+k)=0xff;
 }
}
/* 00280528: writes in original order. */
void nbPanelAnalyzeEnd(void){w32(0x551224,0);w32(0x551220,4);}
/* 002444A8: exact single-condition values; combinations take default1. */
uint64_t datCheckTalk(uint64_t work){
 switch(r16((uint32_t)work+14)&0xfff){case 1:case 2:case 4:case 8:case 16:case 512:case 1024:return 0;default:return 1;}
}
/* 00244530:16 physical stock slots; full raw64 ID equality. */
uint64_t datSearchDevilStock(uint64_t id){
 uint32_t base=r32(0x54ea20);
 for(uint32_t k=0;k<16;k++){
  uint32_t w=base+0xa54+k*236,flags=r32(w);
  if((flags&1)&&!(flags&4)&&r16(w+4)==id)return k;
 }
 return UINT64_MAX;
}
/* 002457F0: alternating empty/count sentinels, preserving adjacent fields. */
void datClearCommMemory(uint64_t work){uint32_t w=(uint32_t)work;w16(w+0x72,0);w16(w+0x78,0xffff);w16(w+0x74,0);w16(w+0x76,0xffff);}
/* 00247ED8: cache base once, reload count before every store and increment.
 * Backed aliases can move later fields to a different action record. */
void nbPushAction(uint64_t type,uint64_t from,uint64_t to,uint64_t data){
 uint32_t m=(uint32_t)nbGetMainProcessData(),base=r32(m+0x3c);
 w32(base+(r32(m+0x40)<<4),(uint32_t)type);
 w32(base+(r32(m+0x40)<<4)+4,(uint32_t)from);
 w32(base+(r32(m+0x40)<<4)+8,(uint32_t)to);
 w32(base+(r32(m+0x40)<<4)+12,(uint32_t)data);
 w32(m+0x40,r32(m+0x40)+1);
}
