/* Complete5 registered Moon/RNG/command13 state owners; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "field_movement_encounter.h"
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
static uint8_t *at(uint32_t a){return nocturneResolveFieldMovementAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}

static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneFieldMovementCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneFieldMovementCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneFieldMovementCpuWrite(r,q);if(r==29u)nocturneFieldMovementSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}
static void nativeDivide(uint32_t n,uint32_t d,int isSigned,int secondary){
 uint32_t q,r;if(secondary)abort();
 if(!d){q=isSigned&&(int32_t)n<0?1u:UINT32_MAX;r=n;}
 else if(isSigned&&n==UINT32_C(0x80000000)&&d==UINT32_MAX){q=n;r=0;}
 else if(isSigned){q=(uint32_t)((int32_t)n/(int32_t)d);r=(uint32_t)((int32_t)n%(int32_t)d);}
 else{q=n/d;r=n%d;}
 nocturneEffectHostSetHilo(sx(q),sx(r));
}



void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}






















static void body_001eac20(void);
static void body_002c0c60(void);
static void body_002c0ba8(void);
static void body_00102848(void);
static void body_00102800(void);
static void body_001eac20(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 001eac20: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001eac24: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001eac28: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001eac2c: lbu v0,0xa40(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000a40))));
/* 001eac30: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 001eac34: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 001eac38: beq v0,zero,0x001eadd0 */ {int taken=(cpu(2)==cpu(0));/* delay 001eac3c */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001eadd0;}}
/* 001eac40: lwc1 f0,0xa44(v1) */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000a44)));
/* 001eac44: lwc1 f1,-0x5da8(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa258)));
/* 001eac48: add.S f0,f0,f12 */ f[0]=EE_FPU_ADD_S(f[0],f[12]);
/* 001eac4c: c.lt.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],1)!=0);
/* 001eac50: bc1f 0x001eadd0 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 001eac54 */ sw(ea(3,(int32_t)UINT32_C(0x00000a44)),f[0]);if(taken){goto L_001eadd0;}}
/* 001eac58: lbu a0,0xa41(v1) */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000a41))));
/* 001eac5c: sw zero,0xa44(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000a44)),(uint32_t)cpu(0));
/* 001eac60: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 001eac64: jal 0x001e99d0 */ set(31,UINT64_C(0x001eac6c));/* delay 001eac68 */ set(4,cpu(4)&UINT32_C(0x0000000f));nocturneFieldMovementCall(UINT32_C(0x001e99d0),UINT32_C(0x001eac64));
/* 001eac6c: li v0,0x1e */ set(2,sx(UINT32_C(0x0000001e)));
/* 001eac70: jal 0x001e9998 */ set(31,UINT64_C(0x001eac78));/* delay 001eac74 */ sw(ea(28,(int32_t)UINT32_C(0xffffb5f0)),(uint32_t)cpu(2));nocturneFieldMovementCall(UINT32_C(0x001e9998),UINT32_C(0x001eac70));
/* 001eac78: bne v0,zero,0x001eaca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 001eac7c */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_001eaca4;}}
/* 001eac80: jal 0x00123828 */ set(31,UINT64_C(0x001eac88));/* delay 001eac84 */ nocturneFieldMovementCall(UINT32_C(0x00123828),UINT32_C(0x001eac80));
/* 001eac88: jal 0x00123760 */ set(31,UINT64_C(0x001eac90));/* delay 001eac8c */ nocturneFieldMovementCall(UINT32_C(0x00123760),UINT32_C(0x001eac88));
/* 001eac90: jal 0x001236a0 */ set(31,UINT64_C(0x001eac98));/* delay 001eac94 */ nocturneFieldMovementCall(UINT32_C(0x001236a0),UINT32_C(0x001eac90));
/* 001eac98: jal 0x001234b0 */ set(31,UINT64_C(0x001eaca0));/* delay 001eac9c */ nocturneFieldMovementCall(UINT32_C(0x001234b0),UINT32_C(0x001eac98));
/* 001eaca0: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
L_001eaca4:;
/* 001eaca4: move a0,zero */ set(4,cpu(0));
/* 001eaca8: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 001eacac: lbu v0,0xa42(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000a42))));
/* 001eacb0: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001eacb4: jal 0x002c0c60 */ set(31,UINT64_C(0x001eacbc));/* delay 001eacb8 */ sb(ea(3,(int32_t)UINT32_C(0x00000a42)),(uint8_t)cpu(2));body_002c0c60();
/* 001eacbc: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001eacc0: addiu v0,v0,0xc */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000000c)));
/* 001eacc4: lbu v1,0xa42(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000a42))));
/* 001eacc8: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 001eaccc: bnel v0,zero,0x001eacd4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001eacd0 */ sb(ea(4,(int32_t)UINT32_C(0x00000a42)),(uint8_t)cpu(0));goto L_001eacd4;}}
L_001eacd4:;
/* 001eacd4: jal 0x001e0f50 */ set(31,UINT64_C(0x001eacdc));/* delay 001eacd8 */ set(4,sx(UINT32_C(0x00000502)));nocturneFieldMovementCall(UINT32_C(0x001e0f50),UINT32_C(0x001eacd4));
/* 001eacdc: beq v0,zero,0x001eadb0 */ {int taken=(cpu(2)==cpu(0));/* delay 001eace0 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_001eadb0;}}
/* 001eace4: lui a1,0x1 */ set(5,sx(UINT32_C(0x00010000)));
/* 001eace8: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 001eacec: lw a1,0x1a7c(a1) */ lw(5,ea(5,(int32_t)UINT32_C(0x00001a7c)));
/* 001eacf0: slti v0,a1,0xf0 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x000000f0));
/* 001eacf4: beq v0,zero,0x001ead14 */ {int taken=(cpu(2)==cpu(0));/* delay 001eacf8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_001ead14;}}
/* 001eacfc: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 001ead00: lui at,0x1 */ set(1,sx(UINT32_C(0x00010000)));
/* 001ead04: addu at,at,v1 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(3)));
/* 001ead08: sw a1,0x1a7c(at) */ sw(ea(1,(int32_t)UINT32_C(0x00001a7c)),(uint32_t)cpu(5));
/* 001ead0c: jal 0x002d4748 */ set(31,UINT64_C(0x001ead14));/* delay 001ead10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffb1e0)));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x001ead0c));
L_001ead14:;
/* 001ead14: jal 0x001e0f50 */ set(31,UINT64_C(0x001ead1c));/* delay 001ead18 */ set(4,sx(UINT32_C(0x00000504)));nocturneFieldMovementCall(UINT32_C(0x001e0f50),UINT32_C(0x001ead14));
/* 001ead1c: beq v0,zero,0x001ead60 */ {int taken=(cpu(2)==cpu(0));/* delay 001ead20 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_001ead60;}}
/* 001ead24: li v1,0x30 */ set(3,sx(UINT32_C(0x00000030)));
/* 001ead28: lui v0,0x1 */ set(2,sx(UINT32_C(0x00010000)));
/* 001ead2c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001ead30: lw v0,0x1a7c(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00001a7c)));
/* 001ead34: bne v0,v1,0x001ead48 */ {int taken=(cpu(2)!=cpu(3));/* delay 001ead38 */ if(taken){goto L_001ead48;}}
/* 001ead3c: jal 0x001e0ed0 */ set(31,UINT64_C(0x001ead44));/* delay 001ead40 */ set(4,sx(UINT32_C(0x00000505)));nocturneFieldMovementCall(UINT32_C(0x001e0ed0),UINT32_C(0x001ead3c));
/* 001ead44: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
L_001ead48:;
/* 001ead48: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 001ead4c: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001ead50: lw v1,0x1a7c(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00001a7c)));
/* 001ead54: b 0x001ead94 */ /* delay 001ead58 */ set(2,sx(UINT32_C(0x00000070)));goto L_001ead94;
L_001ead60:;
/* 001ead60: li v1,0x30 */ set(3,sx(UINT32_C(0x00000030)));
/* 001ead64: lui v0,0x1 */ set(2,sx(UINT32_C(0x00010000)));
/* 001ead68: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001ead6c: lw v0,0x1a7c(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00001a7c)));
/* 001ead70: bne v0,v1,0x001ead84 */ {int taken=(cpu(2)!=cpu(3));/* delay 001ead74 */ if(taken){goto L_001ead84;}}
/* 001ead78: jal 0x001e0ed0 */ set(31,UINT64_C(0x001ead80));/* delay 001ead7c */ set(4,sx(UINT32_C(0x00000505)));nocturneFieldMovementCall(UINT32_C(0x001e0ed0),UINT32_C(0x001ead78));
/* 001ead80: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
L_001ead84:;
/* 001ead84: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 001ead88: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001ead8c: lw v1,0x1a7c(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00001a7c)));
/* 001ead90: li v0,0xa0 */ set(2,sx(UINT32_C(0x000000a0)));
L_001ead94:;
/* 001ead94: bne v1,v0,0x001eadd0 */ {int taken=(cpu(3)!=cpu(2));/* delay 001ead98 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001eadd0;}}
/* 001ead9c: jal 0x001e0ed0 */ set(31,UINT64_C(0x001eada4));/* delay 001eada0 */ set(4,sx(UINT32_C(0x00000506)));nocturneFieldMovementCall(UINT32_C(0x001e0ed0),UINT32_C(0x001ead9c));
/* 001eada4: b 0x001eadd0 */ /* delay 001eada8 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001eadd0;
L_001eadb0:;
/* 001eadb0: jal 0x001e0f50 */ set(31,UINT64_C(0x001eadb8));/* delay 001eadb4 */ set(4,sx(UINT32_C(0x00000503)));nocturneFieldMovementCall(UINT32_C(0x001e0f50),UINT32_C(0x001eadb0));
/* 001eadb8: bne v0,zero,0x001eadd0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001eadbc */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001eadd0;}}
/* 001eadc0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001eadc4: lui at,0x1 */ set(1,sx(UINT32_C(0x00010000)));
/* 001eadc8: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 001eadcc: sw zero,0x1a7c(at) */ sw(ea(1,(int32_t)UINT32_C(0x00001a7c)),(uint32_t)cpu(0));
L_001eadd0:;
/* 001eadd0: jr ra */ {uint64_t target=cpu(31);/* delay 001eadd4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002c0c60(void){
uint64_t incoming=cpu(31);
/* 002c0c60: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c0c64: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0c68: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0c6c: jal 0x002c0ba8 */ set(31,UINT64_C(0x002c0c74));/* delay 002c0c70 */ set(16,cpu(5));body_002c0ba8();
/* 002c0c74: divu v0,s0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(16),0,0);
/* 002c0c78: beql s0,zero,0x002c0c80 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 002c0c7c */ nocturneFieldMovementTrap(7u,UINT32_C(0x002c0c7c));goto L_002c0c80;}}
L_002c0c80:;
/* 002c0c80: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0c84: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0c88: mfhi v0 */ set(2,nocturneEffectHostHi());
/* 002c0c8c: jr ra */ {uint64_t target=cpu(31);/* delay 002c0c90 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002c0ba8(void){
uint64_t incoming=cpu(31);
/* 002c0ba8: move t1,a0 */ set(9,cpu(4));
/* 002c0bac: bnel t1,zero,0x002c0bc0 */ {int taken=(cpu(9)!=cpu(0));if(taken){/* delay 002c0bb0 */ lw(7,ea(9,(int32_t)UINT32_C(0x00000000)));goto L_002c0bc0;}}
/* 002c0bb4: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002c0bb8: addiu t1,v0,-0x6428 */ set(9,sx((uint32_t)cpu(2)+UINT32_C(0xffff9bd8)));
/* 002c0bbc: lw a3,0x0(t1) */ lw(7,ea(9,(int32_t)UINT32_C(0x00000000)));
L_002c0bc0:;
/* 002c0bc0: lw t0,0x4(t1) */ lw(8,ea(9,(int32_t)UINT32_C(0x00000004)));
/* 002c0bc4: lw a2,0x8(t1) */ lw(6,ea(9,(int32_t)UINT32_C(0x00000008)));
/* 002c0bc8: srl a0,a3,0x1e */ set(4,sx((uint32_t)cpu(7)>>30));
/* 002c0bcc: lw v1,0xc(t1) */ lw(3,ea(9,(int32_t)UINT32_C(0x0000000c)));
/* 002c0bd0: sll v0,t0,0x2 */ set(2,sx((uint32_t)cpu(8)<<2));
/* 002c0bd4: srl a1,a2,0x1f */ set(5,sx((uint32_t)cpu(6)>>31));
/* 002c0bd8: or v0,v0,a0 */ set(2,cpu(2)|cpu(4));
/* 002c0bdc: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 002c0be0: sw a2,0xc(t1) */ sw(ea(9,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(6));
/* 002c0be4: or v1,v1,a1 */ set(3,cpu(3)|cpu(5));
/* 002c0be8: sw a3,0x4(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(7));
/* 002c0bec: xor v0,v0,v1 */ set(2,cpu(2)^cpu(3));
/* 002c0bf0: sw t0,0x8(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
/* 002c0bf4: jr ra */ {uint64_t target=cpu(31);/* delay 002c0bf8 */ sw(ea(9,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_00102848(void){
uint64_t incoming=cpu(31);
/* 00102848: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0010284c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00102850: move s2,a1 */ set(18,cpu(5));
/* 00102854: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00102858: move s1,a2 */ set(17,cpu(6));
/* 0010285c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00102860: move s3,a0 */ set(19,cpu(4));
/* 00102864: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00102868: move s4,a3 */ set(20,cpu(7));
/* 0010286c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00102870: beq s2,zero,0x00102884 */ {int taken=(cpu(18)==cpu(0));/* delay 00102874 */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_00102884;}}
/* 00102878: sltiu v0,s1,0x101 */ set(2,cpu(17)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000101));
/* 0010287c: beq v0,zero,0x00102928 */ {int taken=(cpu(2)==cpu(0));/* delay 00102880 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00102928;}}
L_00102884:;
/* 00102884: jal 0x00102800 */ set(31,UINT64_C(0x0010288c));/* delay 00102888 */ body_00102800();
/* 0010288c: li a1,-0x9 */ set(5,sx(UINT32_C(0xfffffff7)));
/* 00102890: move s0,v0 */ set(16,cpu(2));
/* 00102894: lui v1,0xfffe */ set(3,sx(UINT32_C(0xfffe0000)));
/* 00102898: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0010289c: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 001028a0: lw a2,0x1c(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001028a4: li a0,0x2 */ set(4,sx(UINT32_C(0x00000002)));
/* 001028a8: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 001028ac: sb s3,0x9(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000009)),(uint8_t)cpu(19));
/* 001028b0: and v0,v0,a1 */ set(2,cpu(2)&cpu(5));
/* 001028b4: sb a0,0x21(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000021)),(uint8_t)cpu(4));
/* 001028b8: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001028bc: beq a2,zero,0x001028d4 */ {int taken=(cpu(6)==cpu(0));/* delay 001028c0 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_001028d4;}}
/* 001028c4: jal 0x002a8bd8 */ set(31,UINT64_C(0x001028cc));/* delay 001028c8 */ set(4,cpu(6));nocturneFieldMovementCall(UINT32_C(0x002a8bd8),UINT32_C(0x001028c4));
/* 001028cc: sw zero,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 001028d0: sb zero,0x20(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000020)),(uint8_t)cpu(0));
L_001028d4:;
/* 001028d4: beql s2,zero,0x00102900 */ {int taken=(cpu(18)==cpu(0));if(taken){/* delay 001028d8 */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));goto L_00102900;}}
/* 001028dc: jal 0x002a8af8 */ set(31,UINT64_C(0x001028e4));/* delay 001028e0 */ set(4,cpu(17));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x001028dc));
/* 001028e4: move a1,s2 */ set(5,cpu(18));
/* 001028e8: sw v0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 001028ec: move a0,v0 */ set(4,cpu(2));
/* 001028f0: jal 0x002d43a4 */ set(31,UINT64_C(0x001028f8));/* delay 001028f4 */ set(6,cpu(17));nocturneFieldMovementCall(UINT32_C(0x002d43a4),UINT32_C(0x001028f0));
/* 001028f8: b 0x00102904 */ /* delay 001028fc */ sb(ea(16,(int32_t)UINT32_C(0x00000020)),(uint8_t)cpu(17));goto L_00102904;
L_00102900:;
/* 00102900: sb zero,0x20(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000020)),(uint8_t)cpu(0));
L_00102904:;
/* 00102904: beq s4,zero,0x00102918 */ {int taken=(cpu(20)==cpu(0));/* delay 00102908 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00102918;}}
/* 0010290c: b 0x00102920 */ /* delay 00102910 */ set(2,cpu(2)|UINT32_C(0x00000004));goto L_00102920;
L_00102918:;
/* 00102918: li v1,-0x5 */ set(3,sx(UINT32_C(0xfffffffb)));
/* 0010291c: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
L_00102920:;
/* 00102920: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00102924: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00102928:;
/* 00102928: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010292c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00102930: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00102934: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00102938: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0010293c: jr ra */ {uint64_t target=cpu(31);/* delay 00102940 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00102800(void){
uint64_t incoming=cpu(31);
/* 00102800: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 00102804: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00102808: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010280c: jal 0x00101898 */ set(31,UINT64_C(0x00102814));/* delay 00102810 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffe8c8)));nocturneFieldMovementCall(UINT32_C(0x00101898),UINT32_C(0x0010280c));
/* 00102814: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00102818: move a0,v0 */ set(4,cpu(2));
/* 0010281c: j 0x00101ab0 */ /* delay 00102820 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneFieldMovementCall(UINT32_C(0x00101ab0),UINT32_C(0x0010281c));return;
}
uint32_t nocturneFieldMovementStateBody(uint32_t entry){switch(entry){
case UINT32_C(0x001eac20):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001eac20();return 1u;case UINT32_C(0x002c0c60):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002c0c60();return 1u;case UINT32_C(0x002c0ba8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002c0ba8();return 1u;case UINT32_C(0x00102848):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00102848();return 1u;case UINT32_C(0x00102800):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00102800();return 1u;
default:return 0u;}}
