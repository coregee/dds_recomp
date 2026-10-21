/* Eleven complete original registered length-query bodies, zero new credit.
 * Real guest frame saves/restores and tail-delay SP changes are retained.
 * Constants are the actual JR delay instructions, never supplied results.
 */
#include "battle_action_hit_length_frames.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){uint32_t v;memcpy(&v,at(a),4);set(r,sx(v));}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}

static void body_0016aee8(void);
static void body_0016aee8(void){
nocturneEffectAxisNoteEntry(0x0016aee8u);
uint64_t incoming=cpu(31);
/* 0016aee8: jr ra */ {uint64_t target=cpu(31);/* delay 0016aeec */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionHitLength_0016AEE8(uint64_t object){set(4,object);body_0016aee8();return cpu(2);}
static void body_00171c40(void){
nocturneEffectAxisNoteEntry(0x00171c40u);
uint64_t incoming=cpu(31);
/* 00171c40: jr ra */ {uint64_t target=cpu(31);/* delay 00171c44 */ set(2,UINT64_C(0x0000000000000032));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionHitLength_00171C40(uint64_t object){set(4,object);body_00171c40();return cpu(2);}
static void body_001720f0(void){
nocturneEffectAxisNoteEntry(0x001720f0u);
uint64_t incoming=cpu(31);
/* 001720f0: jr ra */ {uint64_t target=cpu(31);/* delay 001720f4 */ set(2,UINT64_C(0x000000000000000f));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionHitLength_001720F0(uint64_t object){set(4,object);body_001720f0();return cpu(2);}
static void body_00172590(void){
nocturneEffectAxisNoteEntry(0x00172590u);
uint64_t incoming=cpu(31);
/* 00172590: jr ra */ {uint64_t target=cpu(31);/* delay 00172594 */ set(2,UINT64_C(0x0000000000000019));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionHitLength_00172590(uint64_t object){set(4,object);body_00172590();return cpu(2);}
static void body_00172718(void){
nocturneEffectAxisNoteEntry(0x00172718u);
uint64_t incoming=cpu(31);
/* 00172718: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0017271c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00172720: lw a0,0x8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00172724: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00172728: j 0x0016aee8 */ /* delay 0017272c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0016aee8();return;
}
uint64_t ps2BattleActionHitLength_00172718(uint64_t object){set(4,object);body_00172718();return cpu(2);}
static void body_00172d18(void){
nocturneEffectAxisNoteEntry(0x00172d18u);
uint64_t incoming=cpu(31);
/* 00172d18: jr ra */ {uint64_t target=cpu(31);/* delay 00172d1c */ set(2,UINT64_C(0x0000000000000014));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionHitLength_00172D18(uint64_t object){set(4,object);body_00172d18();return cpu(2);}
static void body_001735e0(void){
nocturneEffectAxisNoteEntry(0x001735e0u);
uint64_t incoming=cpu(31);
/* 001735e0: jr ra */ {uint64_t target=cpu(31);/* delay 001735e4 */ set(2,UINT64_C(0x0000000000000014));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionHitLength_001735E0(uint64_t object){set(4,object);body_001735e0();return cpu(2);}
static void body_00173768(void){
nocturneEffectAxisNoteEntry(0x00173768u);
uint64_t incoming=cpu(31);
/* 00173768: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0017376c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173770: lw a0,0x8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00173774: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173778: j 0x0016aee8 */ /* delay 0017377c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0016aee8();return;
}
uint64_t ps2BattleActionHitLength_00173768(uint64_t object){set(4,object);body_00173768();return cpu(2);}
static void body_001738f8(void){
nocturneEffectAxisNoteEntry(0x001738f8u);
uint64_t incoming=cpu(31);
/* 001738f8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001738fc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173900: lw a0,0x8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00173904: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173908: j 0x0016aee8 */ /* delay 0017390c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0016aee8();return;
}
uint64_t ps2BattleActionHitLength_001738F8(uint64_t object){set(4,object);body_001738f8();return cpu(2);}
static void body_00173a88(void){
nocturneEffectAxisNoteEntry(0x00173a88u);
uint64_t incoming=cpu(31);
/* 00173a88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00173a8c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173a90: lw a0,0x8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00173a94: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173a98: j 0x0016aee8 */ /* delay 00173a9c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0016aee8();return;
}
uint64_t ps2BattleActionHitLength_00173A88(uint64_t object){set(4,object);body_00173a88();return cpu(2);}
static void body_00173c18(void){
nocturneEffectAxisNoteEntry(0x00173c18u);
uint64_t incoming=cpu(31);
/* 00173c18: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00173c1c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173c20: lw a0,0x8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00173c24: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173c28: j 0x0016aee8 */ /* delay 00173c2c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0016aee8();return;
}
uint64_t ps2BattleActionHitLength_00173C18(uint64_t object){set(4,object);body_00173c18();return cpu(2);}
