/* Original work access and the enemy-record-to-BF startup bridge. */
#include "battle_work_access.h"
#include "battle_ai_startup.h"
#include "process_lists.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleWorkAccessAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t lh(uint32_t a){uint32_t v=r16(a);return v&0x8000u?v|0xffff0000u:v;}
/* Raw signed64 SLTI without a host signed conversion. */
static int below16(uint64_t v){return v<16 || (v>>63)!=0;}

/* 00101978: delayed-start, active, delayed-destroy queue order. LW priority
 * is sign extended before the full64 comparison; the input is not narrowed. */
uint64_t dds3SearchProcessPriority(uint64_t priority){
 static const uint32_t heads[]={0x54e850,0x54e868,0x54e85c};
 for(unsigned k=0;k<3;k++)for(uint32_t p=r32(heads[k]);p;p=r32(p+0x3c))
  if(sx(r32(p+0x20))==priority)return sx(p);
 return 0;
}
/* 002469A0: the PS2 tail calls GetProcessData even when the search returns0. */
uint64_t nbGetMainProcessData(void){return dds3GetProcessData(dds3SearchProcessPriority(0x3fa));}
/* 002469C0: flag2 takes precedence over flag4; signed16 unit index. */
uint64_t nbGetUnitWorkPointer(uint64_t main_data,uint64_t party){
 uint32_t p=(uint32_t)party,flags=r16(p);
 if(!(flags&1))return 0;
 if(flags&2)return sx(r32((uint32_t)main_data+8)+lh(p+4)*236u);
 if(flags&4)return 0;
 return sx(r32(0x54ea20)+lh(p+4)*236u+0xa54u);
}
/* 00246A40: negative form indices are not rejected by the original guard. */
uint64_t nbGetPartyFromFormindex(uint64_t index){
 if(!below16(index))return 0;
 uint32_t main_data=(uint32_t)nbGetMainProcessData();
 uint32_t slot=r32(main_data)+(uint32_t)index*240u,flags=r32(slot+0x78);
 if(!(flags&1)||!(flags&0x40))return 0;
 return sx(r32(main_data+0x10)+lh(slot+0x90)*128u);
}
/* 00246AB8: below16 resolves main data twice through the real party getter. */
uint64_t nbGetUnitWorkFromFormindex(uint64_t index){
 if(!below16(index))return sx(r32(0x54ea20)+((uint32_t)index-16u)*236u+0xa54u);
 uint64_t main_data=nbGetMainProcessData(),party=nbGetPartyFromFormindex(index);
 if(!party||!(r16((uint32_t)party)&1))return 0;
 return nbGetUnitWorkPointer(main_data,party);
}
/* 00253C40: the community AI base+0 is the procedure halfword. Stores clear
 * the previous action before reading it and entering the actual BF startup. */
void ps2BattleStartActorAi(uint64_t context){
 uint32_t unit=r32((uint32_t)context+0x2c),id=r16(unit+4);
 w16(unit+0x6a,0xffff);w16(unit+0x6c,0);
 nbInitAiScript(context,r16(0x3989e0+id*164u));
}
