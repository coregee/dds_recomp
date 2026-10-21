/* Complete6 original deferred font recycling owners; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_reward_phase_recycler.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveBattleRewardPhaseRecyclerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattleRewardPhaseRecyclerCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneBattleRewardPhaseRecyclerCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneBattleRewardPhaseRecyclerCpuWrite(r,q);if(r==29u)nocturneBattleRewardPhaseRecyclerSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);

static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}









#include "ee_fpu_sqrt.h"
#include "ee_vu_rotation.h"









static void body_001c6068(void);
static void body_001c6e50(void);
static void body_001c6f08(void);
static void body_001c80b8(void);
static void body_001c99c0(void);
static void body_001cac00(void);
static void body_001c6068(void){
uint64_t incoming=cpu(31);
/* 001c6068: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c606c: addiu v1,v1,-0x4998 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffb668)));
/* 001c6070: lw a1,0x1c(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x0000001c)));
/* 001c6074: lw v0,0x18(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 001c6078: lw a2,0x1c(a1) */ lw(6,ea(5,(int32_t)UINT32_C(0x0000001c)));
/* 001c607c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c6080: sw a1,0x18(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(5));
/* 001c6084: sw a2,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(6));
/* 001c6088: sw v0,0x18(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 001c608c: sw a0,0x1c(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(4));
/* 001c6090: jr ra */ {uint64_t target=cpu(31);/* delay 001c6094 */ sw(ea(6,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_001c6e50(void){
uint64_t incoming=cpu(31);
/* 001c6e50: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c6e54: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c6e58: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c6e5c: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001c6e60: beq a2,zero,0x001c6ebc */ {int taken=(cpu(6)==cpu(0));/* delay 001c6e64 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001c6ebc;}}
/* 001c6e68: lhu v0,0x4(a2) */ set(2,half(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 001c6e6c: bnel v0,zero,0x001c6ec0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c6e70 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));goto L_001c6ec0;}}
/* 001c6e74: lbu v1,0x15(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000015))));
/* 001c6e78: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 001c6e7c: addiu s0,s0,-0x45d0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffba30)));
/* 001c6e80: lhu a1,0x0(a2) */ set(5,half(ea(6,(int32_t)UINT32_C(0x00000000))));
/* 001c6e84: sll v0,v1,0x3 */ set(2,sx((uint32_t)cpu(3)<<3));
/* 001c6e88: lw a0,0x8(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x00000008)));
/* 001c6e8c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c6e90: sll a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)<<2));
/* 001c6e94: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c6e98: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c6e9c: lw v1,0x18(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 001c6ea0: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 001c6ea4: jal 0x001c6068 */ set(31,UINT64_C(0x001c6eac));/* delay 001c6ea8 */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));body_001c6068();
/* 001c6eac: lw v1,0x144(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000144)));
/* 001c6eb0: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 001c6eb4: sw v1,0x144(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000144)),(uint32_t)cpu(3));
/* 001c6eb8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001c6ebc:;
/* 001c6ebc: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
L_001c6ec0:;
/* 001c6ec0: jr ra */ {uint64_t target=cpu(31);/* delay 001c6ec4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c6f08(void){
uint64_t incoming=cpu(31);
/* 001c6f08: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c6f0c: move v0,zero */ set(2,cpu(0));
/* 001c6f10: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c6f14: move s1,a0 */ set(17,cpu(4));
/* 001c6f18: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c6f1c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c6f20: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c6f24: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c6f28: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c6f2c: beq s1,zero,0x001c6fd0 */ {int taken=(cpu(17)==cpu(0));/* delay 001c6f30 */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_001c6fd0;}}
/* 001c6f34: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 001c6f38: move s5,v0 */ set(21,cpu(2));
/* 001c6f3c: addiu s4,v0,-0x45d0 */ set(20,sx((uint32_t)cpu(2)+UINT32_C(0xffffba30)));
L_001c6f40:;
/* 001c6f40: lw s0,0x1c(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 001c6f44: beql s0,zero,0x001c6fac */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 001c6f48 */ lw(5,ea(20,(int32_t)UINT32_C(0x00000154)));goto L_001c6fac;}}
/* 001c6f4c: addiu s2,s5,-0x45d0 */ set(18,sx((uint32_t)cpu(21)+UINT32_C(0xffffba30)));
L_001c6f50:;
/* 001c6f50: lw v0,0x20(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 001c6f54: bne v0,zero,0x001c6f80 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c6f58 */ lw(19,ea(16,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_001c6f80;}}
/* 001c6f5c: lw v1,0x1c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001c6f60: move a0,s0 */ set(4,cpu(16));
/* 001c6f64: lhu v0,0x4(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000004))));
/* 001c6f68: ori at,zero,0xffff */ set(1,cpu(0)|UINT32_C(0x0000ffff));
/* 001c6f6c: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 001c6f70: jal 0x001c6e50 */ set(31,UINT64_C(0x001c6f78));/* delay 001c6f74 */ sh(ea(3,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(2));body_001c6e50();
/* 001c6f78: b 0x001c6f8c */ /* delay 001c6f7c */ lw(5,ea(18,(int32_t)UINT32_C(0x00000150)));goto L_001c6f8c;
L_001c6f80:;
/* 001c6f80: jal 0x001c99c0 */ set(31,UINT64_C(0x001c6f88));/* delay 001c6f84 */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));body_001c99c0();
/* 001c6f88: lw a1,0x150(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000150)));
L_001c6f8c:;
/* 001c6f8c: move a0,s0 */ set(4,cpu(16));
/* 001c6f90: jal 0x001cac00 */ set(31,UINT64_C(0x001c6f98));/* delay 001c6f94 */ set(16,cpu(19));body_001cac00();
/* 001c6f98: lw v1,0x148(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000148)));
/* 001c6f9c: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 001c6fa0: bne s0,zero,0x001c6f50 */ {int taken=(cpu(16)!=cpu(0));/* delay 001c6fa4 */ sw(ea(18,(int32_t)UINT32_C(0x00000148)),(uint32_t)cpu(3));if(taken){goto L_001c6f50;}}
/* 001c6fa8: lw a1,0x154(s4) */ lw(5,ea(20,(int32_t)UINT32_C(0x00000154)));
L_001c6fac:;
/* 001c6fac: move a0,s1 */ set(4,cpu(17));
/* 001c6fb0: jal 0x001cac00 */ set(31,UINT64_C(0x001c6fb8));/* delay 001c6fb4 */ lw(16,ea(17,(int32_t)UINT32_C(0x00000024)));body_001cac00();
/* 001c6fb8: lw v1,0x14c(s4) */ lw(3,ea(20,(int32_t)UINT32_C(0x0000014c)));
/* 001c6fbc: move s1,s0 */ set(17,cpu(16));
/* 001c6fc0: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 001c6fc4: bne s1,zero,0x001c6f40 */ {int taken=(cpu(17)!=cpu(0));/* delay 001c6fc8 */ sw(ea(20,(int32_t)UINT32_C(0x0000014c)),(uint32_t)cpu(3));if(taken){goto L_001c6f40;}}
/* 001c6fcc: move v0,zero */ set(2,cpu(0));
L_001c6fd0:;
/* 001c6fd0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c6fd4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c6fd8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c6fdc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c6fe0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c6fe4: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c6fe8: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c6fec: jr ra */ {uint64_t target=cpu(31);/* delay 001c6ff0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c80b8(void){
uint64_t incoming=cpu(31);
/* 001c80b8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c80bc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c80c0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c80c4: jal 0x00100418 */ set(31,UINT64_C(0x001c80cc));/* delay 001c80c8 */ nocturneBattleRewardPhaseRecyclerExternal(UINT32_C(0x00100418),UINT32_C(0x001c80c4));
/* 001c80cc: andi s0,v0,0xff */ set(16,cpu(2)&UINT32_C(0x000000ff));
/* 001c80d0: sltiu s0,s0,0x1 */ set(16,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
/* 001c80d4: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001c80d8: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c80dc: addiu at,at,-0x45d0 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffba30)));
/* 001c80e0: addu s0,at,s0 */ set(16,sx((uint32_t)cpu(1)+(uint32_t)cpu(16)));
/* 001c80e4: addiu s0,s0,0x194 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000194)));
/* 001c80e8: jal 0x001c6f08 */ set(31,UINT64_C(0x001c80f0));/* delay 001c80ec */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));body_001c6f08();
/* 001c80f0: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001c80f4: move v0,zero */ set(2,cpu(0));
/* 001c80f8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c80fc: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c8100: jr ra */ {uint64_t target=cpu(31);/* delay 001c8104 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c99c0(void){
uint64_t incoming=cpu(31);
/* 001c99c0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c99c4: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c99c8: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c99cc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c99d0: sra s2,a0,0x18 */ set(18,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c99d4: addiu v1,v1,0xc */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x0000000c)));
/* 001c99d8: sll v0,s2,0x1 */ set(2,sx((uint32_t)cpu(18)<<1));
/* 001c99dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c99e0: addu a1,v0,v1 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c99e4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c99e8: sll a0,s2,0x2 */ set(4,sx((uint32_t)cpu(18)<<2));
/* 001c99ec: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c99f0: move v0,a1 */ set(2,cpu(5));
/* 001c99f4: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c99f8: addiu at,at,-0x42b0 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffbd50)));
/* 001c99fc: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 001c9a00: lbu a2,0x6570(v0) */ set(6,byte(ea(2,(int32_t)UINT32_C(0x00006570))));
/* 001c9a04: lbu v1,0x6571(a1) */ set(3,byte(ea(5,(int32_t)UINT32_C(0x00006571))));
/* 001c9a08: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001c9a0c: beq v0,zero,0x001c9a80 */ {int taken=(cpu(2)==cpu(0));/* delay 001c9a10 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(3)));if(taken){goto L_001c9a80;}}
/* 001c9a14: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 001c9a18: bne v0,zero,0x001c9a80 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c9a1c */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_001c9a80;}}
/* 001c9a20: beq a2,zero,0x001c9a60 */ {int taken=(cpu(6)==cpu(0));/* delay 001c9a24 */ set(5,cpu(18));if(taken){goto L_001c9a60;}}
/* 001c9a28: sll v0,s2,0x6 */ set(2,sx((uint32_t)cpu(18)<<6));
/* 001c9a2c: move s1,a2 */ set(17,cpu(6));
/* 001c9a30: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 001c9a34: addiu s0,s0,-0x43b0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffbc50)));
/* 001c9a38: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001c9a3c: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
L_001c9a40:;
/* 001c9a40: beq v0,zero,0x001c9a50 */ {int taken=(cpu(2)==cpu(0));/* delay 001c9a44 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000004)));if(taken){goto L_001c9a50;}}
/* 001c9a48: jal 0x001c6068 */ set(31,UINT64_C(0x001c9a50));/* delay 001c9a4c */ lw(4,ea(2,(int32_t)UINT32_C(0x00000008)));body_001c6068();
L_001c9a50:;
/* 001c9a50: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
/* 001c9a54: bnel s1,zero,0x001c9a40 */ {int taken=(cpu(17)!=cpu(0));if(taken){/* delay 001c9a58 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_001c9a40;}}
/* 001c9a5c: move a1,s2 */ set(5,cpu(18));
L_001c9a60:;
/* 001c9a60: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9a64: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 001c9a68: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9a6c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9a70: addiu a0,a0,0x59b0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000059b0)));
/* 001c9a74: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9a78: j 0x002d4748 */ /* delay 001c9a7c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleRewardPhaseRecyclerExternal(UINT32_C(0x002d4748),UINT32_C(0x001c9a78));return;
L_001c9a80:;
/* 001c9a80: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9a84: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9a88: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9a8c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9a90: jr ra */ {uint64_t target=cpu(31);/* delay 001c9a94 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001cac00(void){
uint64_t incoming=cpu(31);
/* 001cac00: addiu a2,a0,-0x8 */ set(6,sx((uint32_t)cpu(4)+UINT32_C(0xfffffff8)));
/* 001cac04: beq a0,zero,0x001cac28 */ {int taken=(cpu(4)==cpu(0));/* delay 001cac08 */ set(2,cpu(0));if(taken){goto L_001cac28;}}
/* 001cac0c: lw v1,0x4(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 001cac10: bne v1,zero,0x001cac28 */ {int taken=(cpu(3)!=cpu(0));/* delay 001cac14 */ if(taken){goto L_001cac28;}}
/* 001cac18: lw v1,0x4(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 001cac1c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001cac20: sw v1,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001cac24: sw a2,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));
L_001cac28:;
/* 001cac28: jr ra */ {uint64_t target=cpu(31);/* delay 001cac2c */ checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleRewardPhaseRecyclerBody(uint32_t entry){switch(entry){
case UINT32_C(0x001c6068):if(nocturneBattleRewardPhaseRecyclerStackPointer()!=(uint32_t)cpu(29))abort();body_001c6068();return 1u;case UINT32_C(0x001c6e50):if(nocturneBattleRewardPhaseRecyclerStackPointer()!=(uint32_t)cpu(29))abort();body_001c6e50();return 1u;case UINT32_C(0x001c6f08):if(nocturneBattleRewardPhaseRecyclerStackPointer()!=(uint32_t)cpu(29))abort();body_001c6f08();return 1u;case UINT32_C(0x001c80b8):if(nocturneBattleRewardPhaseRecyclerStackPointer()!=(uint32_t)cpu(29))abort();body_001c80b8();return 1u;case UINT32_C(0x001c99c0):if(nocturneBattleRewardPhaseRecyclerStackPointer()!=(uint32_t)cpu(29))abort();body_001c99c0();return 1u;case UINT32_C(0x001cac00):if(nocturneBattleRewardPhaseRecyclerStackPointer()!=(uint32_t)cpu(29))abort();body_001cac00();return 1u;
default:return 0u;}}
void ps2BattleRewardPhaseRecycler_001C6068(uint64_t a0){set(4,a0);body_001c6068();}
void ps2BattleRewardPhaseRecycler_001C6E50(uint64_t a0){set(4,a0);body_001c6e50();}
uint64_t ps2BattleRewardPhaseRecycler_001C6F08(uint64_t a0){set(4,a0);body_001c6f08();return cpu(2);}
uint64_t ps2BattleRewardPhaseRecycler_001C80B8(void){body_001c80b8();return cpu(2);}
void ps2BattleRewardPhaseRecycler_001C99C0(uint64_t a0){set(4,a0);body_001c99c0();}
uint64_t ps2BattleRewardPhaseRecycler_001CAC00(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_001cac00();return cpu(2);}
