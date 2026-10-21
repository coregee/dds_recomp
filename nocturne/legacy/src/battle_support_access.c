/* Original support-counter and scoring input access. */
#include "battle_support_access.h"
#include "battle_work_access.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleSupportAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 00267788: actual resolution may return0; ANDI status is zero extended. */
uint64_t nbGetBadStat(uint64_t index){uint64_t unit=nbGetUnitWorkFromFormindex(index);return unit?r16((uint32_t)unit+0xe)&0xfffu:0;}
/* 00267E38: LB from the8-byte native action-attribute descriptor. */
uint64_t nbGetNormalSkillAttr(uint64_t skill){uint32_t v=*at(0x3d6998+(uint32_t)skill*8u);return v&128u?UINT64_MAX-(255u-v):v;}
/* 00267E50 / 00267E90: low16 store versus signed LH return; no type bound. */
void nbSetHojoCounter(uint64_t index,uint64_t type,uint64_t point){
 uint64_t party=nbGetPartyFromFormindex(index);if(party){uint16_t value=(uint16_t)point;memcpy(at((uint32_t)party+(uint32_t)type*2u+8u),&value,2);}
}
uint64_t nbGetHojoCounter(uint64_t index,uint64_t type){
 uint64_t party=nbGetPartyFromFormindex(index);if(!party)return 0;
 uint32_t value=r16((uint32_t)party+(uint32_t)type*2u+8u);return sx(value&0x8000u?value|0xffff0000u:value);
}
/* 00267EC8 / 00267F18: original full64 unsigned guard for twenty types. */
uint64_t nbGetHojoCounterMax(uint64_t type){
 if(type>=20)return 0;
 if(type<4||(type>=16&&type<19))return 127;
 if(type<9)return 4;
 return type==19?32767:1;
}
uint64_t nbGetHojoCounterMin(uint64_t type){return type>=4&&type<9?UINT64_C(0xfffffffffffffffc):0;}
/* 0026A468: original signed64 SLTI4 accepts negative formation indices. */
uint64_t nbCheckFormationPlayerSide(uint64_t index){return index<4||(index>>63)!=0;}
