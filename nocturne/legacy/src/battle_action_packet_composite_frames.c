/* Whole original registered packet composite variants, zero new identity.
 * Actual live shared CPU128 bank and guest frames; no expected stack data.
 */
#include "battle_action_packet_composite_frames.h"
#include "battle_action_consumer.h"
#include "battle_action_packet_frames.h"
#include "battle_action_scale_lookup_frames.h"
#include "effect_host_bindings.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}

static uint64_t body_00263810(void);
static uint64_t body_00261e10(void);
static uint64_t body_002641f8(void);
static uint64_t body_002622d0(void);
static uint64_t body_00263810(void){
nocturneEffectAxisNoteEntry(0x00263810u);
uint64_t incoming=cpu(31);
/* 00263810: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00263814: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263818: move s0,a2 */ set(16,cpu(6));
/* 0026381c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263820: move s1,a0 */ set(17,cpu(4));
/* 00263824: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263828: move s2,a1 */ set(18,cpu(5));
/* 0026382c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263830: move s4,t1 */ set(20,cpu(9));
/* 00263834: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00263838: move s5,t0 */ set(21,cpu(8));
/* 0026383c: move t0,zero */ set(8,cpu(0));
/* 00263840: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263844: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00263848: jal 0x00261ca0 */ set(31,0x00263850u);/* delay 0026384c */ set(19,cpu(10));ps2BattleActionPacket_00261CA0(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
/* 00263850: move a0,s1 */ set(4,cpu(17));
/* 00263854: move a1,s2 */ set(5,cpu(18));
/* 00263858: move a2,s0 */ set(6,cpu(16));
/* 0026385c: jal 0x00261e10 */ set(31,0x00263864u);/* delay 00263860 */ set(7,cpu(20));body_00261e10();
/* 00263864: addu a0,s1,s5 */ set(4,sx((uint32_t)cpu(17)+(uint32_t)cpu(21)));
/* 00263868: move a1,s2 */ set(5,cpu(18));
/* 0026386c: move a2,s0 */ set(6,cpu(16));
/* 00263870: jal 0x00261d20 */ set(31,0x00263878u);/* delay 00263874 */ set(7,cpu(19));ps2BattleActionPacket_00261D20(cpu(4),cpu(5),cpu(6),cpu(7));
/* 00263878: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0026387c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263880: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263884: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263888: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026388c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263890: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00263894: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00263898: jr ra */ {uint64_t target=cpu(31);/* delay 0026389c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacketComposite_00263810(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);set(10,a6);
return body_00263810();
}
static uint64_t body_00261e10(void){
nocturneEffectAxisNoteEntry(0x00261e10u);
uint64_t incoming=cpu(31);
/* 00261e10: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00261e14: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261e18: move s0,a0 */ set(16,cpu(4));
/* 00261e1c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261e20: move s1,a1 */ set(17,cpu(5));
/* 00261e24: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261e28: move s2,a3 */ set(18,cpu(7));
/* 00261e2c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261e30: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261e34: jal 0x0025e8e0 */ set(31,0x00261e3cu);/* delay 00261e38 */ set(19,cpu(6));ps2BattleActionPacket_0025E8E0();
/* 00261e3c: move a0,v0 */ set(4,cpu(2));
/* 00261e40: move a1,s0 */ set(5,cpu(16));
/* 00261e44: move a3,s1 */ set(7,cpu(17));
/* 00261e48: jal 0x0025ea48 */ set(31,0x00261e50u);/* delay 00261e4c */ set(6,cpu(0));ps2BattleActionPacket_0025EA48(cpu(4),cpu(5),cpu(6),cpu(7));
/* 00261e50: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 00261e54: move v1,v0 */ set(3,cpu(2));
/* 00261e58: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261e5c: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00261e60: sw s3,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 00261e64: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261e68: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261e6c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261e70: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261e74: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00261e78: jr ra */ {uint64_t target=cpu(31);/* delay 00261e7c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacketComposite_00261E10(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_00261e10();
}
static uint64_t body_002641f8(void){
nocturneEffectAxisNoteEntry(0x002641f8u);
uint64_t incoming=cpu(31);
/* 002641f8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002641fc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00264200: move s1,a2 */ set(17,cpu(6));
/* 00264204: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00264208: move s3,a0 */ set(19,cpu(4));
/* 0026420c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00264210: move s4,a1 */ set(20,cpu(5));
/* 00264214: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00264218: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026421c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00264220: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00264224: jal 0x002469a0 */ set(31,0x0026422cu);/* delay 00264228 */ set(21,cpu(7));ps2BattleActionScaleLookup_002469A0();
/* 0026422c: lw v1,0x78(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000078)));
/* 00264230: move a1,v0 */ set(5,cpu(2));
/* 00264234: andi a0,v1,0x40 */ set(4,cpu(3)&UINT32_C(0x00000040));
/* 00264238: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 0026423c: beq v1,zero,0x002642b8 */ {int taken=(cpu(3)==cpu(0));/* delay 00264240 */ set(2,sx(UINT32_C(0x00000001)));if(taken)goto L_002642b8;}
/* 00264244: beq a0,zero,0x002642b8 */ {int taken=(cpu(4)==cpu(0));/* delay 00264248 */ set(4,cpu(5));if(taken)goto L_002642b8;}
/* 0026424c: lh v0,0x90(s1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000090))));
/* 00264250: lw s0,0x10(a1) */ lw(16,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 00264254: sll v0,v0,0x7 */ set(2,sx((uint32_t)cpu(2)<<7));
/* 00264258: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0026425c: jal 0x002469c0 */ set(31,0x00264264u);/* delay 00264260 */ set(5,cpu(16));ps2BattleActionScaleLookup_002469C0(cpu(4),cpu(5));
/* 00264264: move a0,s1 */ set(4,cpu(17));
/* 00264268: move s2,v0 */ set(18,cpu(2));
/* 0026426c: lhu v0,0x0(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 00264270: ori v0,v0,0x30 */ set(2,cpu(2)|UINT32_C(0x00000030));
/* 00264274: jal 0x00259ab0 */ set(31,0x0026427cu);/* delay 00264278 */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));ps2BattleActionPacket_00259AB0(cpu(4));
/* 0026427c: move a0,s3 */ set(4,cpu(19));
/* 00264280: move a1,s4 */ set(5,cpu(20));
/* 00264284: move a2,s0 */ set(6,cpu(16));
/* 00264288: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0026428c: bne v0,zero,0x002642a4 */ {int taken=(cpu(2)!=cpu(0));/* delay 00264290 */ set(7,sx(UINT32_C(0x00000001)));if(taken)goto L_002642a4;}
/* 00264294: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00264298: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 0026429c: beq v0,zero,0x002642ac */ {int taken=(cpu(2)==cpu(0));/* delay 002642a0 */ if(taken)goto L_002642ac;}
L_002642a4:;
/* 002642a4: bne s5,v1,0x002642b8 */ {int taken=(cpu(21)!=cpu(3));/* delay 002642a8 */ set(2,sx(UINT32_C(0x00000001)));if(taken)goto L_002642b8;}
L_002642ac:;
/* 002642ac: jal 0x002622d0 */ set(31,0x002642b4u);/* delay 002642b0 */ body_002622d0();
/* 002642b4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002642b8:;
/* 002642b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002642bc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002642c0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002642c4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002642c8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002642cc: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002642d0: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002642d4: jr ra */ {uint64_t target=cpu(31);/* delay 002642d8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacketComposite_002641F8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_002641f8();
}
static uint64_t body_002622d0(void){
nocturneEffectAxisNoteEntry(0x002622d0u);
uint64_t incoming=cpu(31);
/* 002622d0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002622d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002622d8: move s0,a0 */ set(16,cpu(4));
/* 002622dc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002622e0: move s1,a1 */ set(17,cpu(5));
/* 002622e4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002622e8: move s2,a3 */ set(18,cpu(7));
/* 002622ec: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002622f0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002622f4: jal 0x0025e8e0 */ set(31,0x002622fcu);/* delay 002622f8 */ set(19,cpu(6));ps2BattleActionPacket_0025E8E0();
/* 002622fc: move a0,v0 */ set(4,cpu(2));
/* 00262300: move a1,s0 */ set(5,cpu(16));
/* 00262304: move a3,s1 */ set(7,cpu(17));
/* 00262308: jal 0x0025ea48 */ set(31,0x00262310u);/* delay 0026230c */ set(6,cpu(0));ps2BattleActionPacket_0025EA48(cpu(4),cpu(5),cpu(6),cpu(7));
/* 00262310: li a0,0xb */ set(4,sx(UINT32_C(0x0000000b)));
/* 00262314: move v1,v0 */ set(3,cpu(2));
/* 00262318: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026231c: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00262320: sw s3,0x1c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(19));
/* 00262324: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262328: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026232c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262330: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262334: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262338: jr ra */ {uint64_t target=cpu(31);/* delay 0026233c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacketComposite_002622D0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_002622d0();
}
