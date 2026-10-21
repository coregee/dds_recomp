/* Original PS2 timeline, process membership and AI completion boundaries. */
#include "battle_action_sequence.h"
#include "battle_work_access.h"
#include "battle_ai_startup.h"
#include "process_lists.h"
#include <string.h>

static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleActionSequenceAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address){uint32_t value;memcpy(&value,at(address),4);return value;}
static uint16_t r16(uint32_t address){uint16_t value;memcpy(&value,at(address),2);return value;}
static void w32(uint32_t address,uint32_t value){memcpy(at(address),&value,4);}
static void w16(uint32_t address,uint16_t value){memcpy(at(address),&value,2);}
static uint64_t sx(uint32_t value){return value&0x80000000u?UINT64_C(0xffffffff00000000)|value:value;}
static uint32_t lh(uint32_t address){uint32_t value=r16(address);return value&0x8000u?value|0xffff0000u:value;}

/* 00101A08: compare the complete EE pointer lane against each signed LW.
 * A null argument never matches an empty queue. Queue order is significant. */
uint64_t dds3ExistProcess(uint64_t process){
 static const uint32_t heads[]={0x54e850,0x54e868,0x54e85c};
 for(unsigned k=0;k<3;k++)for(uint32_t node=r32(heads[k]);node;node=r32(node+0x3c))
  if(sx(node)==process)return 1;
 return 0;
}
/* 002514F0: thirty-two eight-byte records; leave each final halfword intact. */
void nbActionClearTimeList(uint64_t context){
 uint32_t first=(uint32_t)context+0x88;
 for(unsigned k=0;k<32;k++){uint32_t row=first+k*8u;w16(row,0);w16(row+2,0);w16(row+4,0);}
}
/* 00251538: sixteen slots only. Zero before testing flags, and reload main
 * each iteration; native party/unit indices are signed halfwords. */
void nbActionSetHpForTimeList(uint64_t context){
 uint32_t c=(uint32_t)context;
 for(unsigned k=0;k<16;k++){
  uint32_t main=r32(c),destination=c+0x8c+k*8u;
  w16(destination,0);
  uint32_t slot=r32(main)+k*240u,flags=r32(slot+0x78);
  if((flags&1)&&(flags&0x40)){
   uint32_t party=r32(main+0x10)+lh(slot+0x90)*128u;
   uint32_t unit=(uint32_t)nbGetUnitWorkPointer(sx(main),sx(party));
   w16(destination,r16(unit+6));
  }
 }
}
/* 00253C88: only membership in an original scheduler queue keeps AI alive. */
uint64_t nbActionCheckAiScript(uint64_t context){
 uint32_t c=(uint32_t)context;
 if(dds3ExistProcess(sx(r32(r32(c)+0x104))))return 0;
 uint32_t main=r32(c),pending=r32(main+0x94);
 w32(main+0x104,0);
 if(!pending)nbActionSetNextSeq(context,7);
 else{nbActionClearTimeList(context);nbActionSetHpForTimeList(context);nbActionSetNextSeq(context,10);}
 return 1;
}
/* 00253D00: original BF startup; no HD alternate resource/event-bit branch. */
void nbActionSetDeadScript(uint64_t context){
 nbActionClearTimeList(context);
 nbActionSetHpForTimeList(context);
 nbInitAiScript(context,sx(r32((uint32_t)context+0x54)));
}
/* 00257BF8: zero process returns zero; otherwise LB sign extends all 64 bits. */
uint64_t nbGetActionSeq(uint64_t process){
 if(!process)return 0;
 uint32_t c=(uint32_t)dds3GetProcessData(process),value=*at(c+8);
 return value&0x80u?UINT64_C(0xffffffffffffff00)|value:value;
}
/* 00257C20: subtract in 32 bits, then use the signed-negative wrap to slot3.
 * Other indices remain unchecked, including values greater than three. */
uint64_t nbGetPrevActionSeq(void){
 uint32_t main=(uint32_t)nbGetMainProcessData(),index=r32(main+0xe4)-1u;
 if(index&0x80000000u)index=3;
 uint32_t process=r32(main+0xd4+index*4u);
 return process?nbGetActionSeq(sx(process)):UINT64_MAX;
}
/* 00257CC8: request a transition by storing exactly the low byte. */
void nbActionSetNextSeq(uint64_t context,uint64_t state){*at((uint32_t)context+9)=(uint8_t)state;}
