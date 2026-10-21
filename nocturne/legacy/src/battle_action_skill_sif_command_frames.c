/* Whole native SIF command/descriptor algorithms and119 leaf.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_sif_command_frames.h"
#include "battle_action_consumer.h"
#include "battle_action_formula_frames.h"
#include "effect_host_bindings.h"
#include "pcp_effect_helpers.h"
#include "magatuhi_helpers.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "compiler_numeric.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#pragma warning(disable:4102)
#endif
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneEffectHostHi(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}

static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}

static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}


static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
/* Genuine EE word division is defined even before a late native BREAK.
 * Primary and secondary banks are distinct; use the existing Formula bank
 * for cross-unit secondary state rather than a private or primary substitute.
 */



extern uint64_t nocturneLibcStreamKernel(uint64_t,unsigned,const uint64_t *);

static void body_002de2b0(void);
static void body_002de178(void);
static void body_002dc260(void);
static void body_002de2b0(void){
nocturneEffectAxisNoteEntry(0x002de2b0u);
uint64_t incoming=cpu(31);
/* 002de2b0: move v0,a2 */ set(2,cpu(6));
/* 002de2b4: move v1,a3 */ set(3,cpu(7));
/* 002de2b8: move t3,t0 */ set(11,cpu(8));
/* 002de2bc: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002de2c0: move t2,t1 */ set(10,cpu(9));
/* 002de2c4: move a2,a1 */ set(6,cpu(5));
/* 002de2c8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de2cc: move a3,v0 */ set(7,cpu(2));
/* 002de2d0: move t0,v1 */ set(8,cpu(3));
/* 002de2d4: move t1,t3 */ set(9,cpu(11));
/* 002de2d8: jal 0x002de178 */ set(31,0x002de2e0u);/* delay 002de2dc */ set(5,cpu(0));body_002de178();
/* 002de2e0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de2e4: jr ra */ {uint64_t target=cpu(31);/* delay 002de2e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002de178(void){
nocturneEffectAxisNoteEntry(0x002de178u);
uint64_t incoming=cpu(31);
/* 002de178: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
/* 002de17c: sd s1,0x30(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002de180: sd s4,0x60(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002de184: move s1,a3 */ set(17,cpu(7));
/* 002de188: sd s3,0x50(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002de18c: move s4,a0 */ set(20,cpu(4));
/* 002de190: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de194: addiu v0,s1,-0x10 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0xfffffff0)));
/* 002de198: move s3,a1 */ set(19,cpu(5));
/* 002de19c: sd ra,0x70(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002de1a0: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002de1a4: move s0,a2 */ set(16,cpu(6));
/* 002de1a8: move a0,t0 */ set(4,cpu(8));
/* 002de1ac: sltiu v0,v0,0x61 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000061));
/* 002de1b0: bne v0,zero,0x002de1c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002de1b4 */ set(5,cpu(10));if(taken){goto L_002de1c0;}}
/* 002de1b8: b 0x002de28c */ /* delay 002de1bc */ set(2,cpu(0));goto L_002de28c;
L_002de1c0:;
/* 002de1c0: blez a1,0x002de208 */ {int taken=((int64_t)cpu(5)<=0);/* delay 002de1c4 */ set(18,cpu(0));if(taken){goto L_002de208;}}
/* 002de1c8: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002de1cc: sll v1,a1,0x8 */ set(3,sx((uint32_t)cpu(5)<<8));
/* 002de1d0: sw t1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(9));
/* 002de1d4: li s2,0x1 */ set(18,sx(UINT32_C(0x00000001)));
/* 002de1d8: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002de1dc: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002de1e0: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002de1e4: andi v1,s3,0x4 */ set(3,cpu(19)&UINT32_C(0x00000004));
/* 002de1e8: sw t1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(9));
/* 002de1ec: sw a1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 002de1f0: beq v1,zero,0x002de214 */ {int taken=(cpu(3)==cpu(0));/* delay 002de1f4 */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));if(taken){goto L_002de214;}}
/* 002de1f8: jal 0x002de458 */ set(31,0x002de200u);/* delay 002de1fc */ nocturneBattleActionSkillCall(0x002de458u);
/* 002de200: b 0x002de218 */ /* delay 002de204 */ set(5,sx((uint32_t)cpu(18)<<4));goto L_002de218;
L_002de208:;
/* 002de208: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002de20c: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002de210: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002de214:;
/* 002de214: sll a1,s2,0x4 */ set(5,sx((uint32_t)cpu(18)<<4));
L_002de218:;
/* 002de218: lui v0,0x5a */ set(2,sx(UINT32_C(0x005a0000)));
/* 002de21c: lw a0,-0x4560(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0xffffbaa0)));
/* 002de220: addu v1,sp,a1 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(5)));
/* 002de224: sw s0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002de228: addiu v0,sp,0x4 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000004)));
/* 002de22c: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002de230: addiu v1,sp,0x8 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000008)));
/* 002de234: sw a0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002de238: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 002de23c: sw s1,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002de240: addiu a0,sp,0xc */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x0000000c)));
/* 002de244: addu a0,a0,a1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 002de248: sw s4,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));
/* 002de24c: sb s1,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
/* 002de250: li v0,0x44 */ set(2,sx(UINT32_C(0x00000044)));
/* 002de254: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002de258: move a1,s1 */ set(5,cpu(17));
/* 002de25c: move a0,s0 */ set(4,cpu(16));
/* 002de260: jal 0x002de458 */ set(31,0x002de268u);/* delay 002de264 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002de458u);
/* 002de268: andi v0,s3,0x1 */ set(2,cpu(19)&UINT32_C(0x00000001));
/* 002de26c: beq v0,zero,0x002de284 */ {int taken=(cpu(2)==cpu(0));/* delay 002de270 */ set(5,cpu(18));if(taken){goto L_002de284;}}
/* 002de274: jal 0x002dc270 */ set(31,0x002de27cu);/* delay 002de278 */ set(4,cpu(29));nocturneBattleActionSkillCall(0x002dc270u);
/* 002de27c: b 0x002de290 */ /* delay 002de280 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000070)));goto L_002de290;
L_002de284:;
/* 002de284: jal 0x002dc260 */ set(31,0x002de28cu);/* delay 002de288 */ set(4,cpu(29));body_002dc260();
L_002de28c:;
/* 002de28c: ld ra,0x70(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000070)));
L_002de290:;
/* 002de290: ld s4,0x60(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002de294: ld s3,0x50(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002de298: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002de29c: ld s1,0x30(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002de2a0: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de2a4: jr ra */ {uint64_t target=cpu(31);/* delay 002de2a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));checkReturn(target,incoming);return;}
}
static void body_002dc260(void){
nocturneEffectAxisNoteEntry(0x002dc260u);
uint64_t incoming=cpu(31);
/* 002dc260: li v1,0x77 */ set(3,sx(UINT32_C(0x00000077)));
/* 002dc264: syscall 0x0 */ {uint64_t a[2]={cpu(4),cpu(5)};set(2,nocturneLibcStreamKernel(cpu(3),2,a));}
/* 002dc268: jr ra */ {uint64_t target=cpu(31);/* delay 002dc26c */ checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleActionSkillSifCommandBody(uint32_t e){switch(e){
case 0x002de2b0u:body_002de2b0();return 1;
case 0x002de178u:body_002de178();return 1;
case 0x002dc260u:body_002dc260();return 1;
default:return 0;}}
