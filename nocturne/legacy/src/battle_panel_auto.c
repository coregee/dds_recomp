/* Complete5 Auto owner/initializer bodies plus4 registered variants; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_panel_auto.h"
#include "ee_vu_rotation.h"
#include "effect_ftoi0.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveBattlePanelAutoAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}

static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelAutoSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}






















static void body_0027a4e0(void);
static void body_00281e10(void);
static void body_00281e28(void);
static void body_00281e30(void);
static void body_00281e38(void);
static void body_00281e60(void);
static void body_002af0f8(void);
static void body_002af210(void);
static void body_002c0060(void);
static void body_0027a4e0(void){
uint64_t incoming=cpu(31);
/* 0027a4e0: addiu sp,sp,-0xa0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff60)));
/* 0027a4e4: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027a4e8: sd s1,0x58(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027a4ec: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027a4f0: move s2,a2 */ set(18,cpu(6));
/* 0027a4f4: sd s3,0x68(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027a4f8: move s3,a0 */ set(19,cpu(4));
/* 0027a4fc: sd s4,0x70(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027a500: move s4,a3 */ set(20,cpu(7));
/* 0027a504: sd s5,0x78(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027a508: move s5,a1 */ set(21,cpu(5));
/* 0027a50c: sd s6,0x80(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0027a510: sd s7,0x88(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0027a514: move s7,t0 */ set(23,cpu(8));
/* 0027a518: sd s8,0x90(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0027a51c: move s8,t1 */ set(30,cpu(9));
/* 0027a520: sd ra,0x98(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0027a524: jal 0x00117b08 */ set(31,UINT64_C(0x0027a52c));/* delay 0027a528 */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(10));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00117b08)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x00117b08),UINT32_C(0x0027a524));
/* 0027a52c: sw v0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 0027a530: move a0,s4 */ set(4,cpu(20));
/* 0027a534: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027a538: lw s1,0x0(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0027a53c: lw s0,0x4(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0027a540: lw s4,0x10(s2) */ lw(20,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 0027a544: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 0027a548: jal 0x001abc88 */ set(31,UINT64_C(0x0027a550));/* delay 0027a54c */ lw(19,ea(18,(int32_t)UINT32_C(0x0000000c)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027a548));
/* 0027a550: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027a554: move a0,s7 */ set(4,cpu(23));
/* 0027a558: move s6,v0 */ set(22,cpu(2));
/* 0027a55c: jal 0x001abc88 */ set(31,UINT64_C(0x0027a564));/* delay 0027a560 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027a55c));
/* 0027a564: move a0,s8 */ set(4,cpu(30));
/* 0027a568: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027a56c: move s2,v0 */ set(18,cpu(2));
/* 0027a570: sll s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)<<4));
/* 0027a574: jal 0x001abc88 */ set(31,UINT64_C(0x0027a57c));/* delay 0027a578 */ set(16,sx((uint32_t)cpu(16)<<3));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027a574));
/* 0027a57c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027a580: lw a0,0x40(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027a584: addiu s1,s1,0x7000 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00007000)));
/* 0027a588: move s5,v0 */ set(21,cpu(2));
/* 0027a58c: jal 0x001abc88 */ set(31,UINT64_C(0x0027a594));/* delay 0027a590 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00007900)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027a58c));
/* 0027a594: move a3,s0 */ set(7,cpu(16));
/* 0027a598: sll s3,s3,0x4 */ set(19,sx((uint32_t)cpu(19)<<4));
/* 0027a59c: lw a0,0x44(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 0027a5a0: addu s3,s1,s3 */ set(19,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 0027a5a4: sll s4,s4,0x3 */ set(20,sx((uint32_t)cpu(20)<<3));
/* 0027a5a8: addu s0,s0,s4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(20)));
/* 0027a5ac: move a2,s1 */ set(6,cpu(17));
/* 0027a5b0: move t0,s6 */ set(8,cpu(22));
/* 0027a5b4: move t1,s3 */ set(9,cpu(19));
/* 0027a5b8: move t3,s2 */ set(11,cpu(18));
/* 0027a5bc: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 0027a5c0: move t2,a3 */ set(10,cpu(7));
/* 0027a5c4: li a1,0x14c */ set(5,sx(UINT32_C(0x0000014c)));
/* 0027a5c8: sw s5,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(21));
/* 0027a5cc: sw s0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(16));
/* 0027a5d0: sw v0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));
/* 0027a5d4: sw s1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 0027a5d8: sw s0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));
/* 0027a5dc: sw s3,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(19));
/* 0027a5e0: sw v1,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(3));
/* 0027a5e4: jal 0x002af210 */ set(31,UINT64_C(0x0027a5ec));/* delay 0027a5e8 */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(0));body_002af210();
/* 0027a5ec: lui a0,0x2f */ set(4,sx(UINT32_C(0x002f0000)));
/* 0027a5f0: addiu a0,a0,0x67f8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000067f8)));
/* 0027a5f4: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0027a5f8: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0027a600));/* delay 0027a5fc */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));if(target==UINT64_C(0x002acd40)){if(!nocturneBattlePanelOwnerRun(UINT32_C(0x002acd40)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x002acd40),UINT32_C(0x0027a5f8));}else{nocturneBattlePanelAutoIndirectStop(target,UINT32_C(0x0027a5f8));}}
/* 0027a600: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027a604: ld s1,0x58(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027a608: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027a60c: ld s3,0x68(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027a610: ld s4,0x70(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027a614: ld s5,0x78(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027a618: ld s6,0x80(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0027a61c: ld s7,0x88(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0027a620: ld s8,0x90(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0027a624: ld ra,0x98(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0027a628: jr ra */ {uint64_t target=cpu(31);/* delay 0027a62c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000a0)));checkReturn(target,incoming);return;}
}
static void body_00281e10(void){
uint64_t incoming=cpu(31);
/* 00281e10: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
/* 00281e14: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00281e18: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 00281e1c: sb v1,-0x2f34(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffd0cc)),(uint8_t)cpu(3));
/* 00281e20: jr ra */ {uint64_t target=cpu(31);/* delay 00281e24 */ sw(ea(28,(int32_t)UINT32_C(0xffffd0c8)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_00281e28(void){
uint64_t incoming=cpu(31);
/* 00281e28: jr ra */ {uint64_t target=cpu(31);/* delay 00281e2c */ sb(ea(28,(int32_t)UINT32_C(0xffffd0cc)),(uint8_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_00281e30(void){
uint64_t incoming=cpu(31);
/* 00281e30: jr ra */ {uint64_t target=cpu(31);/* delay 00281e34 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffd0cc))));checkReturn(target,incoming);return;}
}
static void body_00281e38(void){
uint64_t incoming=cpu(31);
/* 00281e38: lui v0,0x4080 */ set(2,sx(UINT32_C(0x40800000)));
/* 00281e3c: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
/* 00281e40: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 00281e44: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 00281e48: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00281e4c: sw v0,-0x2f3c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0c4)),(uint32_t)cpu(2));
/* 00281e50: sw v1,-0x2f38(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0c8)),(uint32_t)cpu(3));
/* 00281e54: jr ra */ {uint64_t target=cpu(31);/* delay 00281e58 */ sb(ea(28,(int32_t)UINT32_C(0xffffd0cc)),(uint8_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_00281e60(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00281e60: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 00281e64: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00281e68: move s5,a0 */ set(21,cpu(4));
/* 00281e6c: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00281e70: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00281e74: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00281e78: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00281e7c: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00281e80: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00281e84: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00281e88: lb v0,0x69(s5) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(21,(int32_t)UINT32_C(0x00000069))));
/* 00281e8c: slti v0,v0,0x3 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00281e90: beq v0,zero,0x00281ea8 */ {int taken=(cpu(2)==cpu(0));/* delay 00281e94 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd0c4)));if(taken){goto L_00281ea8;}}
/* 00281e98: lui v0,0x4080 */ set(2,sx(UINT32_C(0x40800000)));
/* 00281e9c: b 0x00281ec0 */ /* delay 00281ea0 */ set(2,cpu(2)|UINT32_C(0x00008080));goto L_00281ec0;
L_00281ea8:;
/* 00281ea8: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
/* 00281eac: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 00281eb0: beq v1,v0,0x00281ec8 */ {int taken=(cpu(3)==cpu(2));/* delay 00281eb4 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffd0cc))));if(taken){goto L_00281ec8;}}
/* 00281eb8: lui v0,0x400 */ set(2,sx(UINT32_C(0x04000000)));
/* 00281ebc: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
L_00281ec0:;
/* 00281ec0: sw v0,-0x2f3c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0c4)),(uint32_t)cpu(2));
/* 00281ec4: lb v0,-0x2f34(gp) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffd0cc))));
L_00281ec8:;
/* 00281ec8: bne v0,zero,0x00281ee8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00281ecc */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd0c8)));if(taken){goto L_00281ee8;}}
/* 00281ed0: lui v0,0xff00 */ set(2,sx(UINT32_C(0xff000000)));
/* 00281ed4: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 00281ed8: beq v0,zero,0x002821d8 */ {int taken=(cpu(2)==cpu(0));/* delay 00281edc */ set(2,sx(UINT32_C(0xf0000000)));if(taken){goto L_002821d8;}}
/* 00281ee0: b 0x00281f04 */ /* delay 00281ee4 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));goto L_00281f04;
L_00281ee8:;
/* 00281ee8: lui v0,0xff00 */ set(2,sx(UINT32_C(0xff000000)));
/* 00281eec: lui v1,0x8000 */ set(3,sx(UINT32_C(0x80000000)));
/* 00281ef0: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 00281ef4: beq v0,v1,0x00281f08 */ {int taken=(cpu(2)==cpu(3));/* delay 00281ef8 */ if(taken){goto L_00281f08;}}
/* 00281efc: lui at,0x1000 */ set(1,sx(UINT32_C(0x10000000)));
/* 00281f00: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
L_00281f04:;
/* 00281f04: sw a0,-0x2f38(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0c8)),(uint32_t)cpu(4));
L_00281f08:;
/* 00281f08: jal 0x00279c00 */ set(31,UINT64_C(0x00281f10));/* delay 00281f0c */ if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279c00)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x00279c00),UINT32_C(0x00281f08));
/* 00281f10: jal 0x00279980 */ set(31,UINT64_C(0x00281f18));/* delay 00281f14 */ set(4,cpu(0));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x00279980),UINT32_C(0x00281f10));
/* 00281f18: lw v0,0x60(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000060)));
/* 00281f1c: andi v0,v0,0x40 */ set(2,cpu(2)&UINT32_C(0x00000040));
/* 00281f20: beq v0,zero,0x00282108 */ {int taken=(cpu(2)==cpu(0));/* delay 00281f24 */ lw(22,ea(28,(int32_t)UINT32_C(0xffffd0c4)));if(taken){goto L_00282108;}}
/* 00281f28: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 00281f2c: lui s0,0x4f */ set(16,sx(UINT32_C(0x004f0000)));
/* 00281f30: addiu s0,s0,0x5ec */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000005ec)));
/* 00281f34: move a0,s6 */ set(4,cpu(22));
/* 00281f38: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 00281f3c: lw s2,0x124(s5) */ lw(18,ea(21,(int32_t)UINT32_C(0x00000124)));
/* 00281f40: jal 0x001abc88 */ set(31,UINT64_C(0x00281f48));/* delay 00281f44 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xfffffe80)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x00281f40));
/* 00281f48: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00281f4c: lw a1,0x4(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00281f50: lw a3,0x10(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 00281f54: addiu a0,a0,0x1c1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000001c1)));
/* 00281f58: lw t3,0xc(s1) */ lw(11,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 00281f5c: addiu a1,a1,0x12 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000012)));
/* 00281f60: lw a2,0xc(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 00281f64: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00281f68: lw t1,0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 00281f6c: lw t2,0x8(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 00281f70: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00281f74: jal 0x00279a88 */ set(31,UINT64_C(0x00281f7c));/* delay 00281f78 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x00281f74));
/* 00281f7c: lw v0,0x70(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000070)));
/* 00281f80: bltz v0,0x00281f98 */ {int taken=((int64_t)cpu(2)<0);/* delay 00281f84 */ set(3,sx((uint32_t)cpu(2)>>1));if(taken){goto L_00281f98;}}
/* 00281f88: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00281f8c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00281f90: b 0x00281fac */ /* delay 00281f94 */ goto L_00281fac;
L_00281f98:;
/* 00281f98: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 00281f9c: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00281fa0: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00281fa4: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00281fa8: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
L_00281fac:;
/* 00281fac: lwc1 f12,-0x5b44(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffa4bc)));
/* 00281fb0: lui s0,0x4f */ set(16,sx(UINT32_C(0x004f0000)));
/* 00281fb4: addiu s0,s0,0x614 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000614)));
/* 00281fb8: jal 0x002c0060 */ set(31,UINT64_C(0x00281fc0));/* delay 00281fbc */ f[12]=EE_FPU_MUL_S(f[0],f[12]);body_002c0060();
/* 00281fc0: lui at,0x4280 */ set(1,sx(UINT32_C(0x42800000)));
/* 00281fc4: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00281fc8: srl a1,s6,0x18 */ set(5,sx((uint32_t)cpu(22)>>24));
/* 00281fcc: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 00281fd0: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00281fd4: mfc1 a0,f1 */ set(4,sx(f[1]));
/* 00281fd8: jal 0x001abc88 */ set(31,UINT64_C(0x00281fe0));/* delay 00281fdc */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000050)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x00281fd8));
/* 00281fe0: lui v1,0x48 */ set(3,sx(UINT32_C(0x00480000)));
/* 00281fe4: ori v1,v1,0x3902 */ set(3,cpu(3)|UINT32_C(0x00003902));
/* 00281fe8: sll v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)<<24));
/* 00281fec: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00281ff0: move a3,v1 */ set(7,cpu(3));
/* 00281ff4: move t0,v0 */ set(8,cpu(2));
/* 00281ff8: move t1,a3 */ set(9,cpu(7));
/* 00281ffc: move t2,t0 */ set(10,cpu(8));
/* 00282000: li a0,0x1c1 */ set(4,sx(UINT32_C(0x000001c1)));
/* 00282004: li a1,0x12 */ set(5,sx(UINT32_C(0x00000012)));
/* 00282008: jal 0x0027a4e0 */ set(31,UINT64_C(0x00282010));/* delay 0028200c */ set(6,cpu(16));body_0027a4e0();
/* 00282010: li a0,0x1c1 */ set(4,sx(UINT32_C(0x000001c1)));
/* 00282014: lui a3,0x48 */ set(7,sx(UINT32_C(0x00480000)));
/* 00282018: lui t0,0x6048 */ set(8,sx(UINT32_C(0x60480000)));
/* 0028201c: ori a3,a3,0x3902 */ set(7,cpu(7)|UINT32_C(0x00003902));
/* 00282020: ori t0,t0,0x3902 */ set(8,cpu(8)|UINT32_C(0x00003902));
/* 00282024: addiu a2,s0,-0x14 */ set(6,sx((uint32_t)cpu(16)+UINT32_C(0xffffffec)));
/* 00282028: li a1,0x12 */ set(5,sx(UINT32_C(0x00000012)));
/* 0028202c: move t1,a3 */ set(9,cpu(7));
/* 00282030: jal 0x0027a4e0 */ set(31,UINT64_C(0x00282038));/* delay 00282034 */ set(10,cpu(8));body_0027a4e0();
/* 00282038: lw v0,0x70(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000070)));
/* 0028203c: bltz v0,0x00282058 */ {int taken=((int64_t)cpu(2)<0);/* delay 00282040 */ set(3,sx((uint32_t)cpu(2)>>1));if(taken){goto L_00282058;}}
/* 00282044: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00282048: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0028204c: b 0x0028206c */ /* delay 00282050 */ goto L_0028206c;
L_00282058:;
/* 00282058: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0028205c: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00282060: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00282064: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00282068: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
L_0028206c:;
/* 0028206c: lwc1 f12,-0x5b40(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffa4c0)));
/* 00282070: lui s0,0x4f */ set(16,sx(UINT32_C(0x004f0000)));
/* 00282074: addiu s0,s0,0x5d8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000005d8)));
/* 00282078: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 0028207c: mul.S f12,f0,f12 */ f[12]=EE_FPU_MUL_S(f[0],f[12]);
/* 00282080: jal 0x002c0060 */ set(31,UINT64_C(0x00282088));/* delay 00282084 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xfffffe70)));body_002c0060();
/* 00282088: lui at,0x4240 */ set(1,sx(UINT32_C(0x42400000)));
/* 0028208c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00282090: lui a2,0xff00 */ set(6,sx(UINT32_C(0xff000000)));
/* 00282094: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 00282098: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0028209c: and a2,s6,a2 */ set(6,cpu(22)&cpu(6));
/* 002820a0: lw s2,0x128(s5) */ lw(18,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 002820a4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 002820a8: mfc1 a0,f1 */ set(4,sx(f[1]));
/* 002820ac: addiu a0,a0,0xa0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000000a0)));
/* 002820b0: sll v1,a0,0x8 */ set(3,sx((uint32_t)cpu(4)<<8));
/* 002820b4: sll v0,a0,0x10 */ set(2,sx((uint32_t)cpu(4)<<16));
/* 002820b8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002820bc: addu a0,a0,a2 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(6)));
/* 002820c0: jal 0x001abc88 */ set(31,UINT64_C(0x002820c8));/* delay 002820c4 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x002820c0));
/* 002820c8: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002820cc: lw a1,0x4(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002820d0: lw a3,0x10(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002820d4: addiu a0,a0,0x1c1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000001c1)));
/* 002820d8: lw t3,0xc(s1) */ lw(11,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002820dc: addiu a1,a1,0x12 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000012)));
/* 002820e0: lw a2,0xc(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002820e4: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002820e8: lw t1,0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002820ec: lw t2,0x8(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002820f0: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002820f4: jal 0x00279a88 */ set(31,UINT64_C(0x002820fc));/* delay 002820f8 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x002820f4));
/* 002820fc: b 0x002821a8 */ /* delay 00282100 */ goto L_002821a8;
L_00282108:;
/* 00282108: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0028210c: lui s0,0x4f */ set(16,sx(UINT32_C(0x004f0000)));
/* 00282110: addiu s0,s0,0x5ec */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000005ec)));
/* 00282114: move a0,s6 */ set(4,cpu(22));
/* 00282118: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 0028211c: lw s4,0x124(s5) */ lw(20,ea(21,(int32_t)UINT32_C(0x00000124)));
/* 00282120: jal 0x001abc88 */ set(31,UINT64_C(0x00282128));/* delay 00282124 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xfffffe80)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x00282120));
/* 00282128: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0028212c: addiu s2,s0,-0x14 */ set(18,sx((uint32_t)cpu(16)+UINT32_C(0xffffffec)));
/* 00282130: lw a1,0x4(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00282134: addiu s3,s1,-0x20 */ set(19,sx((uint32_t)cpu(17)+UINT32_C(0xffffffe0)));
/* 00282138: lw a2,0xc(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0028213c: addiu a0,a0,0x1c1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000001c1)));
/* 00282140: lw a3,0x10(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 00282144: addiu a1,a1,0x12 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000012)));
/* 00282148: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0028214c: lw t1,0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 00282150: lw t2,0x8(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 00282154: lw t3,0xc(s1) */ lw(11,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 00282158: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0028215c: jal 0x00279a88 */ set(31,UINT64_C(0x00282164));/* delay 00282160 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0028215c));
/* 00282164: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 00282168: move a0,s6 */ set(4,cpu(22));
/* 0028216c: jal 0x001abc88 */ set(31,UINT64_C(0x00282174));/* delay 00282170 */ lw(16,ea(21,(int32_t)UINT32_C(0x00000128)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0028216c));
/* 00282174: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00282178: lw a1,0x4(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0028217c: lw a3,0x10(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 00282180: addiu a0,a0,0x1c1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000001c1)));
/* 00282184: lw t3,0xc(s3) */ lw(11,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 00282188: addiu a1,a1,0x12 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000012)));
/* 0028218c: lw a2,0xc(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 00282190: lw t0,0x0(s3) */ lw(8,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 00282194: lw t1,0x4(s3) */ lw(9,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 00282198: lw t2,0x8(s3) */ lw(10,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 0028219c: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002821a0: jal 0x00279a88 */ set(31,UINT64_C(0x002821a8));/* delay 002821a4 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x002821a0));
L_002821a8:;
/* 002821a8: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 002821ac: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002821b0: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002821b4: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002821b8: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002821bc: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002821c0: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002821c4: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002821c8: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002821cc: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002821d0: j 0x00279c00 */ /* delay 002821d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(cpu(31),incoming);if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279c00)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x00279c00),UINT32_C(0x002821d0));return;
L_002821d8:;
/* 002821d8: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002821dc: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002821e0: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002821e4: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002821e8: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002821ec: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002821f0: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002821f4: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002821f8: jr ra */ {uint64_t target=cpu(31);/* delay 002821fc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_002af0f8(void){
uint64_t incoming=cpu(31);
/* 002af0f8: lw t4,0x0(sp) */ lw(12,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002af0fc: sll a3,a3,0x10 */ set(7,sx((uint32_t)cpu(7)<<16));
/* 002af100: lw t5,0x8(sp) */ lw(13,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002af104: andi a2,a2,0xffff */ set(6,cpu(6)&UINT32_C(0x0000ffff));
/* 002af108: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002af10c: andi t1,t1,0xffff */ set(9,cpu(9)&UINT32_C(0x0000ffff));
/* 002af110: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002af114: sll t2,t2,0x10 */ set(10,sx((uint32_t)cpu(10)<<16));
/* 002af118: andi t4,t4,0xffff */ set(12,cpu(12)&UINT32_C(0x0000ffff));
/* 002af11c: sll t5,t5,0x10 */ set(13,sx((uint32_t)cpu(13)<<16));
/* 002af120: sll v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)<<16));
/* 002af124: andi v1,v1,0xffff */ set(3,cpu(3)&UINT32_C(0x0000ffff));
/* 002af128: lw t6,0x10(sp) */ lw(14,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002af12c: or a2,a2,a3 */ set(6,cpu(6)|cpu(7));
/* 002af130: lw t7,0x28(sp) */ lw(15,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002af134: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002af138: or t1,t1,t2 */ set(9,cpu(9)|cpu(10));
/* 002af13c: or t4,t4,t5 */ set(12,cpu(12)|cpu(13));
/* 002af140: lw a3,0x30(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002af144: ori a1,a1,0x10c */ set(5,cpu(5)|UINT32_C(0x0000010c));
/* 002af148: dsll32 t0,t0,0x0 */ set(8,cpu(8)<<32);
/* 002af14c: dsll32 a2,a2,0x0 */ set(6,cpu(6)<<32);
/* 002af150: dsll32 t3,t3,0x0 */ set(11,cpu(11)<<32);
/* 002af154: dsll32 t1,t1,0x0 */ set(9,cpu(9)<<32);
/* 002af158: dsll32 t6,t6,0x0 */ set(14,cpu(14)<<32);
/* 002af15c: dsll32 t4,t4,0x0 */ set(12,cpu(12)<<32);
/* 002af160: dsll32 t7,t7,0x0 */ set(15,cpu(15)<<32);
/* 002af164: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002af168: dsll32 a3,a3,0x0 */ set(7,cpu(7)<<32);
/* 002af16c: ori v0,zero,0xfe00 */ set(2,cpu(0)|UINT32_C(0x0000fe00));
/* 002af170: dsll32 v0,v0,0xe */ set(2,cpu(2)<<46);
/* 002af174: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002af178: dsrl32 t0,t0,0x0 */ set(8,cpu(8)>>32);
/* 002af17c: dsrl32 a2,a2,0x0 */ set(6,cpu(6)>>32);
/* 002af180: dsrl32 t3,t3,0x0 */ set(11,cpu(11)>>32);
/* 002af184: dsrl32 t1,t1,0x0 */ set(9,cpu(9)>>32);
/* 002af188: dsrl32 t6,t6,0x0 */ set(14,cpu(14)>>32);
/* 002af18c: dsrl32 t4,t4,0x0 */ set(12,cpu(12)>>32);
/* 002af190: dsrl32 t7,t7,0x0 */ set(15,cpu(15)>>32);
/* 002af194: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002af198: or t7,t7,v0 */ set(15,cpu(15)|cpu(2));
/* 002af19c: or v1,v1,a3 */ set(3,cpu(3)|cpu(7));
/* 002af1a0: or t0,t0,v0 */ set(8,cpu(8)|cpu(2));
/* 002af1a4: or a2,a2,a3 */ set(6,cpu(6)|cpu(7));
/* 002af1a8: or t3,t3,v0 */ set(11,cpu(11)|cpu(2));
/* 002af1ac: or t1,t1,a3 */ set(9,cpu(9)|cpu(7));
/* 002af1b0: or t6,t6,v0 */ set(14,cpu(14)|cpu(2));
/* 002af1b4: or t4,t4,a3 */ set(12,cpu(12)|cpu(7));
/* 002af1b8: li a3,0xf5 */ set(7,sx(UINT32_C(0x000000f5)));
/* 002af1bc: dsll a3,a3,0x10 */ set(7,cpu(7)<<16);
/* 002af1c0: ori a3,a3,0x1515 */ set(7,cpu(7)|UINT32_C(0x00001515));
/* 002af1c4: dsll a3,a3,0x10 */ set(7,cpu(7)<<16);
/* 002af1c8: ori a3,a3,0x1510 */ set(7,cpu(7)|UINT32_C(0x00001510));
/* 002af1cc: dsrl32 a1,a1,0x0 */ set(5,cpu(5)>>32);
/* 002af1d0: lui v0,0xa400 */ set(2,sx(UINT32_C(0xa4000000)));
/* 002af1d4: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002af1d8: ori v0,v0,0x8001 */ set(2,cpu(2)|UINT32_C(0x00008001));
/* 002af1dc: sd v1,0x50(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000050)));
/* 002af1e0: sd v0,0x0(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002af1e4: sd a3,0x8(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002af1e8: sd a1,0x10(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002af1ec: sd t0,0x18(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002af1f0: sd a2,0x20(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002af1f4: sd t3,0x28(a0) */ save(11,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002af1f8: sd t1,0x30(a0) */ save(9,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002af1fc: sd t6,0x38(a0) */ save(14,ea(4,(int32_t)UINT32_C(0x00000038)));
/* 002af200: sd t4,0x40(a0) */ save(12,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 002af204: jr ra */ {uint64_t target=cpu(31);/* delay 002af208 */ save(15,ea(4,(int32_t)UINT32_C(0x00000048)));checkReturn(target,incoming);return;}
}
static void body_002af210(void){
uint64_t incoming=cpu(31);
/* 002af210: addiu sp,sp,-0xb0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff50)));
/* 002af214: lw v1,0xb8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 002af218: lw v0,0xe8(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000000e8)));
/* 002af21c: sw v1,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(3));
/* 002af220: lw v1,0xc0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 002af224: sd s1,0x68(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002af228: move s1,a1 */ set(17,cpu(5));
/* 002af22c: sw v1,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(3));
/* 002af230: lw v1,0xc8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 002af234: sd s2,0x70(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002af238: move s2,a2 */ set(18,cpu(6));
/* 002af23c: sw v1,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(3));
/* 002af240: lw v1,0xd0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 002af244: sd s3,0x78(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002af248: move s3,a3 */ set(19,cpu(7));
/* 002af24c: sw v1,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
/* 002af250: lw v1,0xd8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000d8)));
/* 002af254: sd s4,0x80(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002af258: move s4,t0 */ set(20,cpu(8));
/* 002af25c: sw v1,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(3));
/* 002af260: lw v1,0xe0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000e0)));
/* 002af264: sd s5,0x88(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002af268: move s5,t1 */ set(21,cpu(9));
/* 002af26c: sd s6,0x90(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002af270: move s6,t2 */ set(22,cpu(10));
/* 002af274: sd s7,0x98(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002af278: move s7,t3 */ set(23,cpu(11));
/* 002af27c: sd s8,0xa0(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002af280: sw a0,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(4));
/* 002af284: li a0,0x70 */ set(4,sx(UINT32_C(0x00000070)));
/* 002af288: sd s0,0x60(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002af28c: sd ra,0xa8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002af290: lw s8,0xb0(sp) */ lw(30,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 002af294: bne v0,zero,0x002af2a4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002af298 */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(3));if(taken){goto L_002af2a4;}}
/* 002af29c: lui v0,0x2b */ set(2,sx(UINT32_C(0x002b0000)));
/* 002af2a0: addiu v0,v0,-0x34b0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffcb50)));
L_002af2a4:;
/* 002af2a4: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002af2ac));/* delay 002af2a8 */ if(target==UINT64_C(0x002acb50)){if(!nocturneBattlePanelOwnerRun(UINT32_C(0x002acb50)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x002acb50),UINT32_C(0x002af2a4));}else{nocturneBattlePanelAutoIndirectStop(target,UINT32_C(0x002af2a4));}}
/* 002af2ac: lui v1,0x5000 */ set(3,sx(UINT32_C(0x50000000)));
/* 002af2b0: ori v1,v1,0x6 */ set(3,cpu(3)|UINT32_C(0x00000006));
/* 002af2b4: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002af2b8: ori v1,v1,0x1000 */ set(3,cpu(3)|UINT32_C(0x00001000));
/* 002af2bc: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002af2c0: move s0,v0 */ set(16,cpu(2));
/* 002af2c4: lui v0,0x2000 */ set(2,sx(UINT32_C(0x20000000)));
/* 002af2c8: ori v0,v0,0x6 */ set(2,cpu(2)|UINT32_C(0x00000006));
/* 002af2cc: sd v0,0x0(s0) */ save(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002af2d0: move a1,s1 */ set(5,cpu(17));
/* 002af2d4: sd v1,0x8(s0) */ save(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002af2d8: move a2,s2 */ set(6,cpu(18));
/* 002af2dc: move a3,s3 */ set(7,cpu(19));
/* 002af2e0: move t0,s4 */ set(8,cpu(20));
/* 002af2e4: lw v0,0x44(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002af2e8: move t1,s5 */ set(9,cpu(21));
/* 002af2ec: lw v1,0x48(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002af2f0: move t2,s6 */ set(10,cpu(22));
/* 002af2f4: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002af2f8: move t3,s7 */ set(11,cpu(23));
/* 002af2fc: lw v0,0x4c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002af300: addiu a0,s0,0x10 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002af304: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 002af308: lw v1,0x50(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002af30c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002af310: sw v1,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
/* 002af314: lw v0,0x54(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 002af318: lw v1,0x58(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002af31c: sw s8,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(30));
/* 002af320: sw v0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));
/* 002af324: jal 0x002af0f8 */ set(31,UINT64_C(0x002af32c));/* delay 002af328 */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(3));body_002af0f8();
/* 002af32c: lw a0,0x40(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002af330: move a1,s0 */ set(5,cpu(16));
/* 002af334: ld s1,0x68(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002af338: ld s0,0x60(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002af33c: ld s2,0x70(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002af340: ld s3,0x78(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002af344: ld s4,0x80(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002af348: ld s5,0x88(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002af34c: ld s6,0x90(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002af350: ld s7,0x98(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002af354: ld s8,0xa0(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002af358: ld ra,0xa8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002af35c: j 0x002acbb8 */ /* delay 002af360 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000b0)));checkReturn(cpu(31),incoming);if(!nocturneBattlePanelOwnerRun(UINT32_C(0x002acbb8)))nocturneBattlePanelAutoDependencyStop(UINT32_C(0x002acbb8),UINT32_C(0x002af35c));return;
}
static void body_002c0060(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 002c0060: lwc1 f0,-0x5a18(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa5e8)));
/* 002c0064: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 002c0068: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 002c006c: mul.S f12,f12,f0 */ f[12]=EE_FPU_MUL_S(f[12],f[0]);
/* 002c0070: cvt.w.S f0,f12 */ f[0]=EE_FPU_CVT_W_S(f[12]);
/* 002c0074: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 002c0078: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 002c007c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002c0080: sub.S f12,f12,f0 */ f[12]=EE_FPU_SUB_S(f[12],f[0]);
/* 002c0084: c.lt.S f1,f12 */ (void)(EE_FPU_COMPARE_S(f[1],f[12],1)!=0);
/* 002c0088: bc1f 0x002c00a0 */ {int taken=(((nocturneBattlePanelAutoFcsr()>>23)&1u)==0);/* delay 002c008c */ if(taken){goto L_002c00a0;}}
/* 002c0090: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002c0094: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c0098: b 0x002c00c0 */ /* delay 002c009c */ f[12]=EE_FPU_SUB_S(f[12],f[0]);goto L_002c00c0;
L_002c00a0:;
/* 002c00a0: lui at,0xbf00 */ set(1,sx(UINT32_C(0xbf000000)));
/* 002c00a4: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c00a8: c.lt.S f12,f0 */ (void)(EE_FPU_COMPARE_S(f[12],f[0],1)!=0);
/* 002c00ac: bc1f 0x002c00c0 */ {int taken=(((nocturneBattlePanelAutoFcsr()>>23)&1u)==0);/* delay 002c00b0 */ if(taken){goto L_002c00c0;}}
/* 002c00b4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002c00b8: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c00bc: add.S f12,f12,f0 */ f[12]=EE_FPU_ADD_S(f[12],f[0]);
L_002c00c0:;
/* 002c00c0: lui at,0x3e80 */ set(1,sx(UINT32_C(0x3e800000)));
/* 002c00c4: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c00c8: c.lt.S f0,f12 */ (void)(EE_FPU_COMPARE_S(f[0],f[12],1)!=0);
/* 002c00cc: bc1f 0x002c00e8 */ {int taken=(((nocturneBattlePanelAutoFcsr()>>23)&1u)==0);/* delay 002c00d0 */ if(taken){goto L_002c00e8;}}
/* 002c00d4: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 002c00d8: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c00dc: b 0x002c0108 */ /* delay 002c00e0 */ f[12]=EE_FPU_SUB_S(f[0],f[12]);goto L_002c0108;
L_002c00e8:;
/* 002c00e8: lui at,0xbe80 */ set(1,sx(UINT32_C(0xbe800000)));
/* 002c00ec: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c00f0: c.lt.S f12,f0 */ (void)(EE_FPU_COMPARE_S(f[12],f[0],1)!=0);
/* 002c00f4: bc1f 0x002c0108 */ {int taken=(((nocturneBattlePanelAutoFcsr()>>23)&1u)==0);/* delay 002c00f8 */ if(taken){goto L_002c0108;}}
/* 002c00fc: lui at,0xbf00 */ set(1,sx(UINT32_C(0xbf000000)));
/* 002c0100: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c0104: sub.S f12,f0,f12 */ f[12]=EE_FPU_SUB_S(f[0],f[12]);
L_002c0108:;
/* 002c0108: lwc1 f0,-0x5a14(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa5ec)));
/* 002c010c: lwc1 f1,-0x5a10(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa5f0)));
/* 002c0110: mul.S f0,f12,f0 */ f[0]=EE_FPU_MUL_S(f[12],f[0]);
/* 002c0114: lwc1 f3,-0x5a0c(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa5f4)));
/* 002c0118: lwc1 f4,-0x5a08(gp) */ f[4]=word(ea(28,(int32_t)UINT32_C(0xffffa5f8)));
/* 002c011c: lwc1 f5,-0x5a04(gp) */ f[5]=word(ea(28,(int32_t)UINT32_C(0xffffa5fc)));
/* 002c0120: lwc1 f6,-0x5a00(gp) */ f[6]=word(ea(28,(int32_t)UINT32_C(0xffffa600)));
/* 002c0124: mul.S f2,f0,f0 */ f[2]=EE_FPU_MUL_S(f[0],f[0]);
/* 002c0128: mul.S f1,f0,f1 */ f[1]=EE_FPU_MUL_S(f[0],f[1]);
/* 002c012c: mul.S f0,f2,f0 */ f[0]=EE_FPU_MUL_S(f[2],f[0]);
/* 002c0130: mul.S f3,f0,f3 */ f[3]=EE_FPU_MUL_S(f[0],f[3]);
/* 002c0134: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 002c0138: add.S f1,f1,f3 */ f[1]=EE_FPU_ADD_S(f[1],f[3]);
/* 002c013c: mul.S f4,f0,f4 */ f[4]=EE_FPU_MUL_S(f[0],f[4]);
/* 002c0140: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 002c0144: add.S f1,f1,f4 */ f[1]=EE_FPU_ADD_S(f[1],f[4]);
/* 002c0148: mul.S f5,f0,f5 */ f[5]=EE_FPU_MUL_S(f[0],f[5]);
/* 002c014c: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 002c0150: add.S f1,f1,f5 */ f[1]=EE_FPU_ADD_S(f[1],f[5]);
/* 002c0154: mul.S f0,f0,f6 */ f[0]=EE_FPU_MUL_S(f[0],f[6]);
/* 002c0158: jr ra */ {uint64_t target=cpu(31);/* delay 002c015c */ f[0]=EE_FPU_ADD_S(f[1],f[0]);checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelAutoBody(uint32_t entry){switch(entry){
case UINT32_C(0x0027a4e0):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_0027a4e0();return 1u;case UINT32_C(0x00281e10):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_00281e10();return 1u;case UINT32_C(0x00281e28):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_00281e28();return 1u;case UINT32_C(0x00281e30):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_00281e30();return 1u;case UINT32_C(0x00281e38):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_00281e38();return 1u;case UINT32_C(0x00281e60):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_00281e60();return 1u;case UINT32_C(0x002af0f8):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_002af0f8();return 1u;case UINT32_C(0x002af210):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_002af210();return 1u;case UINT32_C(0x002c0060):if(nocturneBattlePanelAutoStackPointer()!=(uint32_t)cpu(29))abort();body_002c0060();return 1u;
default:return 0u;}}

void ps2BattlePanelDrawGradientRect_0027A4E0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6){
set(4u,a0);
set(5u,a1);
set(6u,a2);
set(7u,a3);
set(8u,a4);
set(9u,a5);
set(10u,a6);
body_0027a4e0();
return;
}

void nbPanelAutoShow(void){
body_00281e10();
return;
}

uint64_t nbPanelAutoCheckShow(void){
body_00281e30();
return cpu(2);
}

void nbPanelAutoInit(void){
body_00281e38();
return;
}

void ps2BattlePanelDrawAutoIndicator_00281E60(uint64_t a0){
set(4u,a0);
body_00281e60();
return;
}
