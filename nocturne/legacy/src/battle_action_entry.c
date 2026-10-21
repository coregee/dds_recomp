/* Native entry-side action dispatch. Original table indices remain unchecked. */
#include "battle_action_entry.h"
#include "battle_action_sequence.h"
#include "battle_ai_execution.h"
#include <string.h>

static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleActionEntryAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address){uint32_t value;memcpy(&value,at(address),4);return value;}
static void w16(uint32_t address,uint16_t value){memcpy(at(address),&value,2);}
static void w32(uint32_t address,uint32_t value){memcpy(at(address),&value,4);}

/* 00253488: the original state0 enter callback has no instructions with effects. */
void nbActionSetNone(uint64_t context){(void)context;}
/* 00253BF8: reset action/skill before the real decision runner, then tail-call it.
 * Its integer return register is not a defined result of this void wrapper. */
void nbActionSetAi(uint64_t context){
 uint32_t unit=r32((uint32_t)context+0x2c);
 w16(unit+0x6a,0xffff);
 w16(unit+0x6c,0);
 (void)nbRunAi(context);
}
/* 00253C20: ordinary AI has already made its decision at entry. */
uint64_t nbActionCheckAi(uint64_t context){nbActionSetNextSeq(context,7);return 1;}
/* 00257C80: preserve the store order and the signed-byte table displacement.
 * There is no native index clamp or null-target guard, including states16/17. */
void nbActionSetSeq(uint64_t context,uint64_t state){
 uint32_t c=(uint32_t)context,index=(uint8_t)state;
 *at(c+8)=(uint8_t)state;
 *at(c+9)=0;
 w32(c+0xc,0);
 w16(c+0xa,0);
 if(index&0x80u)index|=0xffffff00u;
 uint32_t entry=r32(0x3fa7c0u+index*8u);
#if UINTPTR_MAX > UINT32_MAX
 nocturneInvokeBattleActionEntry(entry,context);
#else
 ((void (*)(uint64_t))(uintptr_t)entry)(context);
#endif
}
