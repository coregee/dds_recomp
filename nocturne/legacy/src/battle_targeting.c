/* Native battle targeting and its complete data-query prerequisites. */
#include "battle_targeting.h"
#include "event_camera.h"
#include "process_lists.h"
#include "nocturne.h"
#include "script_compare.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleTargetingAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t lh(uint32_t a){uint32_t v=r16(a);return v&0x8000u?v|0xffff0000u:v;}
static int32_t lb(uint32_t a){uint32_t v=*at(a);return v&128u?(int32_t)v-256:(int32_t)v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}

/* 00242B68 / 00242D18: actual parameter reader and unsigned16 level. */
uint64_t datGetNormalAtkPow(uint64_t raw){
 uint32_t unit=(uint32_t)raw;
 uint32_t power=((uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),0)+r16(unit+0x14))*2u;
 if((r16(unit+0xe)&0xfffu)==0x40){
  uint32_t corrected=power+(power>>31);
  power=(corrected>>1)|(corrected&0x80000000u);
 }
 return sx(power);
}
uint64_t datGetDefPow(uint64_t raw){
 uint32_t unit=(uint32_t)raw;
 return sx(((uint32_t)datGetParam((datUnitWork_PS2 *)at(unit),3)+r16(unit+0x14))*2u);
}
/* 00243FE8: full64 -1 sentinel, signed demon affinity row and LW result. */
uint64_t datGetAisyo(uint64_t raw,uint64_t attribute){
 if(attribute==UINT64_MAX)return 0;
 uint32_t unit=(uint32_t)raw,index=(uint32_t)attribute;
 if(!(r32(unit)&4))index+=lh(0x3497ce+r16(unit+4)*60u)*16u;
 uint32_t value=r32(0x3a7fe0+index*4u);
 if((r16(unit+0xe)&0xfffu)==0x400)value=r32(0x3abd60+(uint32_t)attribute*4u);
 return sx(value);
}
/* 00244E68: bit40 precedes bit80; flag4 units bypass demon data. */
uint64_t datGet3Zokusei(uint64_t raw){
 uint32_t unit=(uint32_t)raw;if(r32(unit)&4)return 0;
 uint32_t flags=r32(0x3497c0+r16(unit+4)*60u);
 return flags&0x40?1:flags&0x80?UINT64_MAX:0;
}
/* 00245C90: read all six literal words before the item1 RNG dependency. */
uint64_t datGetItemSkillNo(uint64_t item){
 uint32_t choices[6];for(unsigned i=0;i<6;i++)choices[i]=r32(0x543170+i*4);
 if(item==1)return sx(choices[sdfGetRandInt(NULL,6)]);
 return r16(0x3dc4a2+(uint32_t)item*8u);
}
/* 00259C48: item1 consumes RNG before taking the cached context word. */
uint64_t nbGetItemSkillNo(uint64_t context,uint64_t item){
 uint64_t value=datGetItemSkillNo(item);
 return item==1?sx(r32((uint32_t)context+0x64)):value;
}
/* 00258DE8: outputs commit only after all dependencies and descriptor reads,
 * in type/rule/area order. Null tests retain full64 inputs and aliases. */
void nbGetTargetTypeRuleArea(uint64_t context,uint64_t raw,uint64_t type_out,
 uint64_t rule_out,uint64_t area_out,uint64_t reverse){
 uint32_t unit=(uint32_t)raw,type=0,rule=0,area=0,action=lh(unit+0x6a);
 switch(action){
 case 0:
  rule=reverse?2u:0u;area=reverse?1u:2u;
  if(nbHatudoCheckSkill((datUnitWork_PS2 *)at(unit),0x130)&&!reverse)type=1;
  break;
 case 1:case 5:{
  uint64_t skill=action==1?r16(unit+0x6c):nbGetItemSkillNo(context,r16(unit+0x6c));
  uint32_t record=0x3d7998+(uint32_t)skill*60u;
  uint32_t mode=*at(record+8);if(mode<3)type=mode;
  uint32_t sides=*at(record+9);if(sides&1)area=reverse?2u:1u;
  area|=sides&2;rule=*at(record+10)&15u;break;
 }
 case 4:area=2;break;
 case 6:{
  uint32_t main=r32((uint32_t)context);
  if(!(r32(main+0x60)&8)){rule=less(sx(lh(main+0x18)),4)?12u:2u;area=1;}
  break;
 }
 default:break;
 }
 if(type_out)w32((uint32_t)type_out,type);
 if(rule_out)w32((uint32_t)rule_out,rule);
 if(area_out)w32((uint32_t)area_out,area);
}
/* 0025D690: original name lookup and unconditional process-data tail call. */
uint64_t GetTarSelProcessData(void){return dds3GetProcessData(dds3SearchProcessName(0x5442b8));}
/* 0025DA78: type2 bypasses side selection; comparisons retain raw64 self and
 * target, whereas address/target-minus4 arithmetic wraps at32 bits. */
uint64_t CheckFormCursor(uint64_t self,uint64_t type,uint64_t rule,uint64_t area,uint64_t target){
 uint32_t manager=(uint32_t)GetTarSelProcessData(),main=r32(manager);
 uint32_t slot=r32(main)+(uint32_t)target*240u,flipped=r32(main+0x60)&8;
 uint32_t allowed=1;
 if(type!=2&&(area&3)!=3){
  allowed=0;
  if(area&1)allowed=flipped?sx((uint32_t)target-4u)<10u:(uint32_t)less(target,4);
  else if(area&2)allowed=flipped?(uint32_t)less(target,4):sx((uint32_t)target-4u)<10u;
 }
 if(!allowed)return 0;
 if((rule&1)&&self!=target)return 0;
 if((rule&2)&&self==target)return 0;
 uint32_t flags=r32(slot+0x78);
 if(!(flags&1))allowed=(rule&4)&&(flags&0x800);
 if(!allowed)return 0;
 if((rule&8)&&(flags&1))return 0;
 if(flags&0x40){uint32_t party=r32(main+0x10)+lh(slot+0x90)*128u;if(r16(party)&0x38)return 0;}
 return 1;
}
/* 0025DC00: mark all16 physical slots, list only0..13, and sort the enemy
 * list by repeated strict COP1 comparisons/swaps. This is not a stable sort. */
uint64_t nbSetSelectOkMark(uint64_t party_index,uint64_t type,uint64_t rule,uint64_t area){
 uint32_t manager=(uint32_t)GetTarSelProcessData();*at(manager+0x12)=0;*at(manager+0x13)=0;
 for(uint32_t candidate=0;candidate<16;candidate++){
  uint32_t main=r32(manager),slot=r32(main)+candidate*240u;
  uint64_t self=sx(lh(r32(main+0x10)+(uint32_t)party_index*128u+2));
  w32(slot+0x78,r32(slot+0x78)&~12u);
  if(CheckFormCursor(self,type,rule,area,candidate)){
   main=r32(manager);slot=r32(main)+candidate*240u;w32(slot+0x78,r32(slot+0x78)|4);
   if(candidate<14){
    uint32_t own=(candidate<4)==((r32(main+0x60)&8)==0);
    uint32_t count=manager+(own?0x12u:0x13u),list=manager+(own?0x14u:0x20u);
    *at(list+(uint32_t)lb(count))=(uint8_t)candidate;
    *at(count)=(uint8_t)(*at(count)+1u);
   }
  }
 }
 uint32_t count=*at(manager+0x13);
 for(int32_t i=0;i<(int32_t)(int8_t)count-1;i++){
  for(int32_t j=i+1;j<(int32_t)(int8_t)count;j++){
   uint32_t first=manager+0x20u+(uint32_t)i,next=manager+0x20u+(uint32_t)j;
   uint32_t slots=r32(r32(manager));int32_t first_index=lb(first),next_index=lb(next);
   uint32_t a=r32(slots+(uint32_t)next_index*240u),b=r32(slots+(uint32_t)first_index*240u);
   if(EE_FPU_COMPARE_S(a,b,1)){
    uint8_t next_value=*at(next);*at(first)=next_value;*at(next)=(uint8_t)first_index;count=*at(manager+0x13);
   }
  }
 }
 return lb(manager+0x12)+(int32_t)(int8_t)count!=0;
}
