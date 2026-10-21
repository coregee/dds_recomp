/* Original sixteen-slot candidate filters; selector dispatch owns the RNG. */
#include "battle_ai_filters.h"
#include "battle_work_access.h"
#include "battle_targeting.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleAiFiltersAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address){uint32_t v;memcpy(&v,at(address),4);return v;}
static uint16_t r16(uint32_t address){uint16_t v;memcpy(&v,at(address),2);return v;}
static void w32(uint32_t address,uint32_t v){memcpy(at(address),&v,4);}
static uint32_t slot(uint32_t context,uint32_t index){return r32(r32(context))+index*240u;}
static void mark(uint32_t context,uint32_t index){uint32_t p=slot(context,index)+0x78;w32(p,r32(p)|8u);}

/* 00286EC0 / 00286F88 / 00287070: strict minimum below10000, first tie wins.
 * No existing flag8 is cleared. Unit resolution uses actual queue/party code. */
static void minimum(uint64_t raw,uint32_t offset,int exclude_petrified){
 uint32_t context=(uint32_t)raw,best=UINT32_MAX,value=10000;
 for(uint32_t i=0;i<16;i++){
  if(!(r32(slot(context,i)+0x78)&4u))continue;
  uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(i);
  if(exclude_petrified&&(r16(unit+0xe)&0xfffu)==0x200u)continue;
  uint32_t candidate=r16(unit+offset);
  if(candidate<value){value=candidate;best=i;}
 }
 if(best!=UINT32_MAX)mark(context,best);
}
void nbAiSelLifeMin(uint64_t context){minimum(context,6,0);}
void nbAiSelBaarLv(uint64_t context){minimum(context,0x14,1);}
void nbAiSelLvMin(uint64_t context){minimum(context,0x14,0);}

/* 00287138: ANDI yields a zero-extended status; input equality stays64 bits. */
void nbAiSelBad(uint64_t raw,uint64_t status){
 uint32_t context=(uint32_t)raw;
 for(uint32_t i=0;i<16;i++)if(r32(slot(context,i)+0x78)&4u){
  uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(i);
  if((uint64_t)(r16(unit+0xe)&0xfffu)==status)mark(context,i);
 }
}
/* 002871D8: flag4 units are skipped; LHU demon ID compares with raw64 input. */
void nbAiSelId(uint64_t raw,uint64_t id){
 uint32_t context=(uint32_t)raw;
 for(uint32_t i=0;i<16;i++)if(r32(slot(context,i)+0x78)&4u){
  uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(i);
  if(!(r32(unit)&4u)&&(uint64_t)r16(unit+4)==id)mark(context,i);
 }
}
/* 00287288 / 00287338: use the actual complete alignment reader. */
static void alignment(uint64_t raw,uint64_t wanted){
 uint32_t context=(uint32_t)raw;
 for(uint32_t i=0;i<16;i++)if(r32(slot(context,i)+0x78)&4u){
  uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(i);
  if(!(r32(unit)&4u)&&datGet3Zokusei(unit)==wanted)mark(context,i);
 }
}
void nbAiSelLight(uint64_t context){alignment(context,1);}
void nbAiSelDark(uint64_t context){alignment(context,UINT64_MAX);}
/* 002873E8: player means unit flag4 here, rather than formation index<4. */
void nbAiSelPlayer(uint64_t raw){
 uint32_t context=(uint32_t)raw;
 for(uint32_t i=0;i<16;i++)if(r32(slot(context,i)+0x78)&4u){
  uint32_t unit=(uint32_t)nbGetUnitWorkFromFormindex(i);
  if(r32(unit)&4u)mark(context,i);
 }
}
/* 00287478: slot base is cached; the condition word is reloaded per slot.
 * In particular, a backed mask alias can observe earlier flag writes. */
void nbAiSelJoken(uint64_t raw){
 uint32_t context=(uint32_t)raw,p=r32(r32(context));
 for(uint32_t i=0;i<16;i++,p+=240u){
  uint32_t flags=r32(p+0x78);
  if((flags&4u)&&(r32(context+0x190)&(UINT32_C(1)<<i)))w32(p+0x78,flags|8u);
 }
}
/* 002874C8: mark every eligible candidate, retaining all other flag bits. */
void nbAiSelRnd(uint64_t raw){
 uint32_t p=r32(r32((uint32_t)raw));
 for(uint32_t i=0;i<16;i++,p+=240u){uint32_t flags=r32(p+0x78);if(flags&4u)w32(p+0x78,flags|8u);}
}
