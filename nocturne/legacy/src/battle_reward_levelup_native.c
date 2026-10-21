/* Complete4 original result-row/level-up-animation/name-request owners and2 existing draw wrappers; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_reward_levelup_native.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveBattleRewardLevelupNativeAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattleRewardLevelupNativeCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneBattleRewardLevelupNativeCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneBattleRewardLevelupNativeCpuWrite(r,q);if(r==29u)nocturneBattleRewardLevelupNativeSetStackPointer(q[0]);
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










#include "ee_fpu_sqrt.h"
#include "ee_vu_rotation.h"









static void body_001c7e00(void);
static void body_001c7e18(void);
static void body_001ca0d0(void);
static void body_001ca258(void);
static void body_0024a2e8(void);
static void body_0024a440(void);
static void body_001c7e00(void){
uint64_t incoming=cpu(31);
/* 001c7e00: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c7e04: move a1,zero */ set(5,cpu(0));
/* 001c7e08: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7e0c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7e10: j 0x001c7e18 */ /* delay 001c7e14 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001c7e18();return;
}
static void body_001c7e18(void){
uint64_t incoming=cpu(31);
/* 001c7e18: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c7e1c: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c7e20: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7e24: sra a1,a1,0x18 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c7e28: lw a2,-0x4d50(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffb2b0)));
/* 001c7e2c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7e30: j 0x001c7e38 */ /* delay 001c7e34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7e38),UINT32_C(0x001c7e30));return;
}
static void body_001ca0d0(void){
uint64_t incoming=cpu(31);
/* 001ca0d0: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 001ca0d4: sll t2,t2,0x18 */ set(10,sx((uint32_t)cpu(10)<<24));
/* 001ca0d8: sd s5,0x48(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001ca0dc: move s5,t0 */ set(21,cpu(8));
/* 001ca0e0: sll t1,t1,0x18 */ set(9,sx((uint32_t)cpu(9)<<24));
/* 001ca0e4: sw a0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(4));
/* 001ca0e8: sra t2,t2,0x18 */ set(10,sx((uint32_t)((int32_t)cpu(10)>>24)));
/* 001ca0ec: move a0,s5 */ set(4,cpu(21));
/* 001ca0f0: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001ca0f4: move s0,a2 */ set(16,cpu(6));
/* 001ca0f8: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001ca0fc: move s1,zero */ set(17,cpu(0));
/* 001ca100: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001ca104: move s2,t3 */ set(18,cpu(11));
/* 001ca108: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001ca10c: sd s7,0x58(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001ca110: sra s7,t1,0x18 */ set(23,sx((uint32_t)((int32_t)cpu(9)>>24)));
/* 001ca114: sd s8,0x60(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001ca118: move s8,a3 */ set(30,cpu(7));
/* 001ca11c: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001ca120: sd s6,0x50(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001ca124: sd ra,0x68(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001ca128: sw t2,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(10));
/* 001ca12c: jal 0x002d5d0c */ set(31,UINT64_C(0x001ca134));/* delay 001ca130 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(5));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002d5d0c),UINT32_C(0x001ca12c));
/* 001ca134: move s4,v0 */ set(20,cpu(2));
/* 001ca138: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001ca13c: bne v0,zero,0x001ca14c */ {int taken=(cpu(2)!=cpu(0));/* delay 001ca140 */ if(taken){goto L_001ca14c;}}
/* 001ca144: jal 0x001c7c00 */ set(31,UINT64_C(0x001ca14c));/* delay 001ca148 */ set(4,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7c00),UINT32_C(0x001ca144));
L_001ca14c:;
/* 001ca14c: jal 0x001c7c10 */ set(31,UINT64_C(0x001ca154));/* delay 001ca150 */ set(4,sx(UINT32_C(0x00000002)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7c10),UINT32_C(0x001ca14c));
/* 001ca154: blez s4,0x001ca208 */ {int taken=((int64_t)cpu(20)<=0);/* delay 001ca158 */ set(3,sx((uint32_t)cpu(21)+(uint32_t)cpu(17)));if(taken){goto L_001ca208;}}
/* 001ca15c: sll s6,s0,0x4 */ set(22,sx((uint32_t)cpu(16)<<4));
L_001ca160:;
/* 001ca160: lb v0,0x0(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001ca164: bltz v0,0x001ca180 */ {int taken=((int64_t)cpu(2)<0);/* delay 001ca168 */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_001ca180;}}
/* 001ca16c: sb a0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 001ca170: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
/* 001ca174: b 0x001ca194 */ /* delay 001ca178 */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));goto L_001ca194;
L_001ca180:;
/* 001ca180: lbu v0,0x1(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000001))));
/* 001ca184: li s3,0x2 */ set(19,sx(UINT32_C(0x00000002)));
/* 001ca188: sb a0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 001ca18c: sb zero,0x2(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(0));
/* 001ca190: sb v0,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
L_001ca194:;
/* 001ca194: move a0,sp */ set(4,cpu(29));
/* 001ca198: move a2,zero */ set(6,cpu(0));
/* 001ca19c: move a3,zero */ set(7,cpu(0));
/* 001ca1a0: move t0,zero */ set(8,cpu(0));
/* 001ca1a4: jal 0x001c7828 */ set(31,UINT64_C(0x001ca1ac));/* delay 001ca1a8 */ set(5,cpu(23));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7828),UINT32_C(0x001ca1a4));
/* 001ca1ac: move a1,s6 */ set(5,cpu(22));
/* 001ca1b0: move s0,v0 */ set(16,cpu(2));
/* 001ca1b4: jal 0x001c7b40 */ set(31,UINT64_C(0x001ca1bc));/* delay 001ca1b8 */ set(4,cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7b40),UINT32_C(0x001ca1b4));
/* 001ca1bc: move a0,s0 */ set(4,cpu(16));
/* 001ca1c0: jal 0x001c7ba8 */ set(31,UINT64_C(0x001ca1c8));/* delay 001ca1c4 */ set(5,cpu(30));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7ba8),UINT32_C(0x001ca1c0));
/* 001ca1c8: move a0,s0 */ set(4,cpu(16));
/* 001ca1cc: jal 0x001c7a88 */ set(31,UINT64_C(0x001ca1d4));/* delay 001ca1d0 */ set(5,sx(UINT32_C(0x00000003)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7a88),UINT32_C(0x001ca1cc));
/* 001ca1d4: move a0,s2 */ set(4,cpu(18));
/* 001ca1d8: jal 0x001c8108 */ set(31,UINT64_C(0x001ca1e0));/* delay 001ca1dc */ set(5,cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c8108),UINT32_C(0x001ca1d8));
/* 001ca1e0: bne s1,zero,0x001ca1f0 */ {int taken=(cpu(17)!=cpu(0));/* delay 001ca1e4 */ set(18,cpu(2));if(taken){goto L_001ca1f0;}}
/* 001ca1e8: lw v0,0x10(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001ca1ec: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_001ca1f0:;
/* 001ca1f0: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 001ca1f4: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 001ca1f8: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001ca1fc: slt v0,s1,s4 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(20));
/* 001ca200: bne v0,zero,0x001ca160 */ {int taken=(cpu(2)!=cpu(0));/* delay 001ca204 */ set(3,sx((uint32_t)cpu(21)+(uint32_t)cpu(17)));if(taken){goto L_001ca160;}}
L_001ca208:;
/* 001ca208: jal 0x001c7c00 */ set(31,UINT64_C(0x001ca210));/* delay 001ca20c */ set(4,sx(UINT32_C(0x00000002)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7c00),UINT32_C(0x001ca208));
/* 001ca210: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001ca214: bnel v0,zero,0x001ca228 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001ca218 */ set(2,cpu(18));goto L_001ca228;}}
/* 001ca21c: jal 0x001c7c10 */ set(31,UINT64_C(0x001ca224));/* delay 001ca220 */ set(4,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7c10),UINT32_C(0x001ca21c));
/* 001ca224: move v0,s2 */ set(2,cpu(18));
L_001ca228:;
/* 001ca228: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001ca22c: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001ca230: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001ca234: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001ca238: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001ca23c: ld s5,0x48(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001ca240: ld s6,0x50(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001ca244: ld s7,0x58(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001ca248: ld s8,0x60(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001ca24c: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001ca250: jr ra */ {uint64_t target=cpu(31);/* delay 001ca254 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
static void body_001ca258(void){
uint64_t incoming=cpu(31);
/* 001ca258: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001ca25c: move t3,t1 */ set(11,cpu(9));
/* 001ca260: move t2,zero */ set(10,cpu(0));
/* 001ca264: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ca268: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001ca26c: jal 0x001ca0d0 */ set(31,UINT64_C(0x001ca274));/* delay 001ca270 */ set(9,sx(UINT32_C(0x00000001)));body_001ca0d0();
/* 001ca274: move s0,v0 */ set(16,cpu(2));
/* 001ca278: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 001ca27c: jal 0x001c7a88 */ set(31,UINT64_C(0x001ca284));/* delay 001ca280 */ set(4,cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7a88),UINT32_C(0x001ca27c));
/* 001ca284: move v0,s0 */ set(2,cpu(16));
/* 001ca288: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001ca28c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ca290: jr ra */ {uint64_t target=cpu(31);/* delay 001ca294 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0024a2e8(void){
uint64_t incoming=cpu(31);
/* 0024a2e8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0024a2ec: li a0,0x48 */ set(4,sx(UINT32_C(0x00000048)));
/* 0024a2f0: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024a2f4: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024a2f8: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a2fc: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024a300: jal 0x002797b0 */ set(31,UINT64_C(0x0024a308));/* delay 0024a304 */ set(18,cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002797b0),UINT32_C(0x0024a300));
/* 0024a308: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0024a30c: move a1,zero */ set(5,cpu(0));
/* 0024a310: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 0024a314: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 0024a318: move t0,zero */ set(8,cpu(0));
/* 0024a31c: move t1,zero */ set(9,cpu(0));
/* 0024a320: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024a324: jal 0x00279868 */ set(31,UINT64_C(0x0024a32c));/* delay 0024a328 */ set(11,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279868),UINT32_C(0x0024a324));
/* 0024a32c: jal 0x00279980 */ set(31,UINT64_C(0x0024a334));/* delay 0024a330 */ set(4,cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279980),UINT32_C(0x0024a32c));
/* 0024a334: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 0024a338: addiu s0,v0,0x4f50 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0x00004f50)));
/* 0024a33c: addiu s1,s0,0xc */ set(17,sx((uint32_t)cpu(16)+UINT32_C(0x0000000c)));
L_0024a340:;
/* 0024a340: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0024a344: beql v0,zero,0x0024a410 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024a348 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));goto L_0024a410;}}
/* 0024a34c: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024a350: addiu v1,v0,-0x1 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 0024a354: bgtz v1,0x0024a368 */ {int taken=((int64_t)cpu(3)>0);/* delay 0024a358 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_0024a368;}}
/* 0024a35c: b 0x0024a40c */ /* delay 0024a360 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));goto L_0024a40c;
L_0024a368:;
/* 0024a368: li v0,0x14 */ set(2,sx(UINT32_C(0x00000014)));
/* 0024a36c: lw t0,0x8(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0024a370: subu a2,v0,v1 */ set(6,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 0024a374: lw a0,-0x8(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0xfffffff8)));
/* 0024a378: addiu v1,a2,-0xa */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0xfffffff6)));
/* 0024a37c: slti a1,a2,0xb */ set(5,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x0000000b));
/* 0024a380: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 0024a384: li t1,0x80 */ set(9,sx(UINT32_C(0x00000080)));
/* 0024a388: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0024a38c: slti v1,a2,0x4 */ set(3,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0024a390: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0024a394: sll t2,a2,0x2 */ set(10,sx((uint32_t)cpu(6)<<2));
/* 0024a398: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024a39c: bne a1,zero,0x0024a3b0 */ {int taken=(cpu(5)!=cpu(0));/* delay 0024a3a0 */ set(8,sx((uint32_t)cpu(8)-(uint32_t)cpu(6)));if(taken){goto L_0024a3b0;}}
/* 0024a3a4: subu t1,t1,v0 */ set(9,sx((uint32_t)cpu(9)-(uint32_t)cpu(2)));
/* 0024a3a8: slti v0,t1,0x0 */ set(2,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 0024a3ac: movn t1,zero,v0 */ if(cpu(2)!=0){set(9,cpu(0));}
L_0024a3b0:;
/* 0024a3b0: beq v1,zero,0x0024a3d8 */ {int taken=(cpu(3)==cpu(0));/* delay 0024a3b4 */ set(2,sx(UINT32_C(0x00800000)));if(taken){goto L_0024a3d8;}}
/* 0024a3b8: addu a3,t2,a2 */ set(7,sx((uint32_t)cpu(10)+(uint32_t)cpu(6)));
/* 0024a3bc: li v0,0x16 */ set(2,sx(UINT32_C(0x00000016)));
/* 0024a3c0: subu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(7)));
/* 0024a3c4: srl v1,v0,0x1f */ set(3,sx((uint32_t)cpu(2)>>31));
/* 0024a3c8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0024a3cc: sra v0,v0,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 0024a3d0: addu t0,t0,v0 */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(2)));
/* 0024a3d4: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
L_0024a3d8:;
/* 0024a3d8: sll v1,t1,0x18 */ set(3,sx((uint32_t)cpu(9)<<24));
/* 0024a3dc: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0024a3e0: lw t4,-0x306c(gp) */ lw(12,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a3e4: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0024a3e8: move a1,t0 */ set(5,cpu(8));
/* 0024a3ec: li a2,0x5c */ set(6,sx(UINT32_C(0x0000005c)));
/* 0024a3f0: li t1,0x68 */ set(9,sx(UINT32_C(0x00000068)));
/* 0024a3f4: li t0,0xa0 */ set(8,sx(UINT32_C(0x000000a0)));
/* 0024a3f8: li t2,0x5f */ set(10,sx(UINT32_C(0x0000005f)));
/* 0024a3fc: li t3,0x16 */ set(11,sx(UINT32_C(0x00000016)));
/* 0024a400: sw v1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 0024a404: jal 0x00279a88 */ set(31,UINT64_C(0x0024a40c));/* delay 0024a408 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(12));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a404));
L_0024a40c:;
/* 0024a40c: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
L_0024a410:;
/* 0024a410: addiu s0,s0,0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 0024a414: slti v0,s2,0x40 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000040));
/* 0024a418: bne v0,zero,0x0024a340 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024a41c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));if(taken){goto L_0024a340;}}
/* 0024a420: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024a424: li a0,0x47 */ set(4,sx(UINT32_C(0x00000047)));
/* 0024a428: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024a42c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a430: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024a434: j 0x002797b0 */ /* delay 0024a438 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002797b0),UINT32_C(0x0024a434));return;
}
static void body_0024a440(void){
uint64_t incoming=cpu(31);
/* 0024a440: addiu sp,sp,-0xa0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff60)));
/* 0024a444: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024a448: sd s5,0x78(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0024a44c: move s5,a1 */ set(21,cpu(5));
/* 0024a450: sd s6,0x80(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0024a454: move s6,a3 */ set(22,cpu(7));
/* 0024a458: sd s7,0x88(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0024a45c: move s7,a2 */ set(23,cpu(6));
/* 0024a460: sw a0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(4));
/* 0024a464: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0024a468: move a1,zero */ set(5,cpu(0));
/* 0024a46c: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 0024a470: sw t0,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(8));
/* 0024a474: move t0,zero */ set(8,cpu(0));
/* 0024a478: sw t1,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(9));
/* 0024a47c: move t1,zero */ set(9,cpu(0));
/* 0024a480: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 0024a484: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0024a488: sd s3,0x68(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0024a48c: sd s4,0x70(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0024a490: sd s8,0x90(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0024a494: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0024a498: sd s1,0x58(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0024a49c: sd ra,0x98(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0024a4a0: jal 0x00279868 */ set(31,UINT64_C(0x0024a4a8));/* delay 0024a4a4 */ set(11,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279868),UINT32_C(0x0024a4a0));
/* 0024a4a8: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a4ac: move a0,zero */ set(4,cpu(0));
/* 0024a4b0: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0024a4b4: jal 0x00279980 */ set(31,UINT64_C(0x0024a4bc));/* delay 0024a4b8 */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279980),UINT32_C(0x0024a4b4));
/* 0024a4bc: lw v1,0x40(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0024a4c0: lui a1,0x57 */ set(5,sx(UINT32_C(0x00570000)));
/* 0024a4c4: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a4c8: lui a3,0xa09d */ set(7,sx(UINT32_C(0xa09d0000)));
/* 0024a4cc: addiu s2,a1,0x4e80 */ set(18,sx((uint32_t)cpu(5)+UINT32_C(0x00004e80)));
/* 0024a4d0: ori a3,a3,0xc300 */ set(7,cpu(7)|UINT32_C(0x0000c300));
/* 0024a4d4: addu v0,v1,a0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0024a4d8: addiu v1,s2,0x8 */ set(3,sx((uint32_t)cpu(18)+UINT32_C(0x00000008)));
/* 0024a4dc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024a4e0: sw a3,0x3c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(7));
/* 0024a4e4: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0024a4e8: sll s4,v0,0x2 */ set(20,sx((uint32_t)cpu(2)<<2));
/* 0024a4ec: addiu s8,s4,0x20 */ set(30,sx((uint32_t)cpu(20)+UINT32_C(0x00000020)));
/* 0024a4f0: addu s3,s8,v1 */ set(19,sx((uint32_t)cpu(30)+(uint32_t)cpu(3)));
/* 0024a4f4: lw v0,0x0(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0024a4f8: blez v0,0x0024a508 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0024a4fc */ set(8,sx(UINT32_C(0x00800000)));if(taken){goto L_0024a508;}}
/* 0024a500: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 0024a504: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_0024a508:;
/* 0024a508: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0024a50c: blez s6,0x0024a5f8 */ {int taken=((int64_t)cpu(22)<=0);/* delay 0024a510 */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(8));if(taken){goto L_0024a5f8;}}
/* 0024a514: addiu t4,s2,0x4 */ set(12,sx((uint32_t)cpu(18)+UINT32_C(0x00000004)));
/* 0024a518: li a2,0x64 */ set(6,sx(UINT32_C(0x00000064)));
/* 0024a51c: addu t4,s8,t4 */ set(12,sx((uint32_t)cpu(30)+(uint32_t)cpu(12)));
/* 0024a520: slti a1,s6,0x8 */ set(5,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0024a524: lw v1,0x0(t4) */ lw(3,ea(12,(int32_t)UINT32_C(0x00000000)));
/* 0024a528: sll a0,s6,0x4 */ set(4,sx((uint32_t)cpu(22)<<4));
/* 0024a52c: li s0,0x80 */ set(16,sx(UINT32_C(0x00000080)));
/* 0024a530: beql a2,zero,0x0024a538 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 0024a534 */ nocturneBattleRewardLevelupNativeTrap(7u,UINT32_C(0x0024a534));goto L_0024a538;}}
L_0024a538:;
/* 0024a538: sll v0,v1,0x3 */ set(2,sx((uint32_t)cpu(3)<<3));
/* 0024a53c: movn s0,a0,a1 */ if(cpu(5)!=0){set(16,cpu(4));}
/* 0024a540: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0024a544: sll s0,s0,0x18 */ set(16,sx((uint32_t)cpu(16)<<24));
/* 0024a548: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024a54c: lw a0,-0x306c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a550: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 0024a554: or s0,s0,t0 */ set(16,cpu(16)|cpu(8));
/* 0024a558: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0024a55c: sw a0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 0024a560: div v0,a2 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(6),1,0);
/* 0024a564: li a2,0x25 */ set(6,sx(UINT32_C(0x00000025)));
/* 0024a568: sw s0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 0024a56c: move a1,s7 */ set(5,cpu(23));
/* 0024a570: li a3,0x22 */ set(7,sx(UINT32_C(0x00000022)));
/* 0024a574: li t0,0xbf */ set(8,sx(UINT32_C(0x000000bf)));
/* 0024a578: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024a57c: li t2,0x25 */ set(10,sx(UINT32_C(0x00000025)));
/* 0024a580: li t3,0x22 */ set(11,sx(UINT32_C(0x00000022)));
/* 0024a584: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024a588: addu s1,s5,v0 */ set(17,sx((uint32_t)cpu(21)+(uint32_t)cpu(2)));
/* 0024a58c: sw v0,0x0(t4) */ sw(ea(12,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0024a590: jal 0x00279a88 */ set(31,UINT64_C(0x0024a598));/* delay 0024a594 */ set(4,cpu(17));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a590));
/* 0024a598: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a59c: addiu a0,s1,0x25 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000025)));
/* 0024a5a0: move a1,s7 */ set(5,cpu(23));
/* 0024a5a4: li a2,0x11f */ set(6,sx(UINT32_C(0x0000011f)));
/* 0024a5a8: li a3,0x22 */ set(7,sx(UINT32_C(0x00000022)));
/* 0024a5ac: li t0,0xe3 */ set(8,sx(UINT32_C(0x000000e3)));
/* 0024a5b0: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024a5b4: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024a5b8: li t3,0x22 */ set(11,sx(UINT32_C(0x00000022)));
/* 0024a5bc: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024a5c0: jal 0x00279a88 */ set(31,UINT64_C(0x0024a5c8));/* delay 0024a5c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a5c0));
/* 0024a5c8: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a5cc: addiu a0,s1,0x144 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000144)));
/* 0024a5d0: move a1,s7 */ set(5,cpu(23));
/* 0024a5d4: li a2,0x78 */ set(6,sx(UINT32_C(0x00000078)));
/* 0024a5d8: li a3,0x22 */ set(7,sx(UINT32_C(0x00000022)));
/* 0024a5dc: li t0,0x6a */ set(8,sx(UINT32_C(0x0000006a)));
/* 0024a5e0: li t1,0x2e */ set(9,sx(UINT32_C(0x0000002e)));
/* 0024a5e4: li t2,0x78 */ set(10,sx(UINT32_C(0x00000078)));
/* 0024a5e8: li t3,0x22 */ set(11,sx(UINT32_C(0x00000022)));
/* 0024a5ec: sw s0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 0024a5f0: jal 0x00279a88 */ set(31,UINT64_C(0x0024a5f8));/* delay 0024a5f4 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a5f0));
L_0024a5f8:;
/* 0024a5f8: slti v0,s6,0xd */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x0000000d));
/* 0024a5fc: bne v0,zero,0x0024ae40 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024a600 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));if(taken){goto L_0024ae40;}}
/* 0024a604: lw v0,-0x309c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf64)));
/* 0024a608: blez v0,0x0024a66c */ {int taken=((int64_t)cpu(2)<=0);/* delay 0024a60c */ lw(8,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_0024a66c;}}
/* 0024a610: lw v0,0x0(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0024a614: bne v0,zero,0x0024a670 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024a618 */ set(3,sx(UINT32_C(0x00570000)));if(taken){goto L_0024a670;}}
/* 0024a61c: addiu v0,s2,0x4 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000004)));
/* 0024a620: addu a0,s4,s2 */ set(4,sx((uint32_t)cpu(20)+(uint32_t)cpu(18)));
/* 0024a624: addu a3,s4,v0 */ set(7,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 0024a628: lw a1,0x30(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 0024a62c: lw v1,0x0(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 0024a630: addu a2,s2,s8 */ set(6,sx((uint32_t)cpu(18)+(uint32_t)cpu(30)));
/* 0024a634: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0024a638: sw v1,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 0024a63c: lw a1,0x24(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 0024a640: lw a0,0xc(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x0000000c)));
/* 0024a644: lw v0,0x10(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 0024a648: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0024a64c: sltu v1,v1,v0 */ set(3,cpu(3)<cpu(2));
/* 0024a650: bnel v1,zero,0x0024a660 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0024a654 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf74)));goto L_0024a660;}}
/* 0024a658: b 0x0024a668 */ /* delay 0024a65c */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_0024a668;
L_0024a660:;
/* 0024a660: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 0024a664: sw v0,-0x308c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf74)),(uint32_t)cpu(2));
L_0024a668:;
/* 0024a668: lw t0,0x20(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000020)));
L_0024a66c:;
/* 0024a66c: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
L_0024a670:;
/* 0024a670: lw a3,0x40(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0024a674: addiu a2,v1,0x4e80 */ set(6,sx((uint32_t)cpu(3)+UINT32_C(0x00004e80)));
/* 0024a678: addiu v1,a2,0x8 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0x00000008)));
/* 0024a67c: addu v0,a3,t0 */ set(2,sx((uint32_t)cpu(7)+(uint32_t)cpu(8)));
/* 0024a680: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024a684: addu v0,v0,t0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(8)));
/* 0024a688: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024a68c: addiu a0,v0,0x10 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 0024a690: addu a1,a0,v1 */ set(5,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 0024a694: lw v0,0x0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0024a698: beq v0,zero,0x0024a6c0 */ {int taken=(cpu(2)==cpu(0));/* delay 0024a69c */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0x0000000c)));if(taken){goto L_0024a6c0;}}
/* 0024a6a0: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0024a6a4: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0024a6a8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0024a6ac: slti v0,v1,0x10 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0024a6b0: bne v0,zero,0x0024a6c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024a6b4 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_0024a6c0;}}
/* 0024a6b8: sw zero,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0024a6bc: sw zero,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
L_0024a6c0:;
/* 0024a6c0: lw a1,0x20(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a6c4: lui a3,0x57 */ set(7,sx(UINT32_C(0x00570000)));
/* 0024a6c8: lw a0,0x40(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0024a6cc: addiu s4,a3,0x4e80 */ set(20,sx((uint32_t)cpu(7)+UINT32_C(0x00004e80)));
/* 0024a6d0: lw t0,0x28(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024a6d4: addiu s8,s4,0x8 */ set(30,sx((uint32_t)cpu(20)+UINT32_C(0x00000008)));
/* 0024a6d8: addu v0,a0,a1 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 0024a6dc: addiu s0,s4,0x4 */ set(16,sx((uint32_t)cpu(20)+UINT32_C(0x00000004)));
/* 0024a6e0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024a6e4: andi s1,t0,0xff */ set(17,cpu(8)&UINT32_C(0x000000ff));
/* 0024a6e8: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0024a6ec: move a0,s1 */ set(4,cpu(17));
/* 0024a6f0: sll s2,v0,0x2 */ set(18,sx((uint32_t)cpu(2)<<2));
/* 0024a6f4: addu s3,s2,s8 */ set(19,sx((uint32_t)cpu(18)+(uint32_t)cpu(30)));
/* 0024a6f8: addu s0,s2,s0 */ set(16,sx((uint32_t)cpu(18)+(uint32_t)cpu(16)));
/* 0024a6fc: jal 0x0021f898 */ set(31,UINT64_C(0x0024a704));/* delay 0024a700 */ lw(5,ea(19,(int32_t)UINT32_C(0x00000000)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0021f898),UINT32_C(0x0024a6fc));
/* 0024a704: move a0,s1 */ set(4,cpu(17));
/* 0024a708: sw v0,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));
/* 0024a70c: lw a1,0x0(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0024a710: jal 0x0021f898 */ set(31,UINT64_C(0x0024a718));/* delay 0024a714 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0021f898),UINT32_C(0x0024a710));
/* 0024a718: move a0,s1 */ set(4,cpu(17));
/* 0024a71c: sw v0,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(2));
/* 0024a720: lw s0,0x0(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0024a724: move a1,s0 */ set(5,cpu(16));
/* 0024a728: jal 0x0021f838 */ set(31,UINT64_C(0x0024a730));/* delay 0024a72c */ sw(ea(29,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0021f838),UINT32_C(0x0024a728));
/* 0024a730: move t3,v0 */ set(11,cpu(2));
/* 0024a734: lw v0,0x0(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0024a738: slt v0,v0,t3 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(11));
/* 0024a73c: beq v0,zero,0x0024a794 */ {int taken=(cpu(2)==cpu(0));/* delay 0024a740 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000022));if(taken){goto L_0024a794;}}
/* 0024a744: lw a2,-0x308c(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffcf74)));
/* 0024a748: addiu v0,s4,0xc */ set(2,sx((uint32_t)cpu(20)+UINT32_C(0x0000000c)));
/* 0024a74c: addiu v1,s2,0x10 */ set(3,sx((uint32_t)cpu(18)+UINT32_C(0x00000010)));
/* 0024a750: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024a754: addu t2,v1,v0 */ set(10,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0024a758: addu v1,v1,s8 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(30)));
/* 0024a75c: ori a2,a2,0x2 */ set(6,cpu(6)|UINT32_C(0x00000002));
/* 0024a760: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 0024a764: move t0,s3 */ set(8,cpu(19));
/* 0024a768: li a3,0xf */ set(7,sx(UINT32_C(0x0000000f)));
/* 0024a76c: sw t1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(9));
/* 0024a770: addiu a0,s5,0xfe */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x000000fe)));
/* 0024a774: sw t3,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(11));
/* 0024a778: addiu a1,s7,0x13 */ set(5,sx((uint32_t)cpu(23)+UINT32_C(0x00000013)));
/* 0024a77c: sw a3,0x20(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(7));
/* 0024a780: sw t1,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(9));
/* 0024a784: sw a2,-0x308c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf74)),(uint32_t)cpu(6));
/* 0024a788: jal 0x0024a298 */ set(31,UINT64_C(0x0024a790));/* delay 0024a78c */ sw(ea(10,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0024a298),UINT32_C(0x0024a788));
/* 0024a790: slti v0,s6,0x22 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000022));
L_0024a794:;
/* 0024a794: beq v0,zero,0x0024a7bc */ {int taken=(cpu(2)==cpu(0));/* delay 0024a798 */ set(19,sx(UINT32_C(0x00000080)));if(taken){goto L_0024a7bc;}}
/* 0024a79c: sll v0,s6,0x1 */ set(2,sx((uint32_t)cpu(22)<<1));
/* 0024a7a0: addu v0,v0,s6 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(22)));
/* 0024a7a4: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0024a7a8: addiu s3,v0,-0x48 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0xffffffb8)));
/* 0024a7ac: slti v1,s3,0x81 */ set(3,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000081));
/* 0024a7b0: bne v1,zero,0x0024a7c0 */ {int taken=(cpu(3)!=cpu(0));/* delay 0024a7b4 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000038)));if(taken){goto L_0024a7c0;}}
/* 0024a7b8: li s3,0x80 */ set(19,sx(UINT32_C(0x00000080)));
L_0024a7bc:;
/* 0024a7bc: lw v1,0x38(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000038)));
L_0024a7c0:;
/* 0024a7c0: addiu s0,s7,0x18 */ set(16,sx((uint32_t)cpu(23)+UINT32_C(0x00000018)));
/* 0024a7c4: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a7c8: sll s2,s3,0x18 */ set(18,sx((uint32_t)cpu(19)<<24));
/* 0024a7cc: or s1,v1,s2 */ set(17,cpu(3)|cpu(18));
/* 0024a7d0: addiu a0,s5,0x17 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x00000017)));
/* 0024a7d4: move a1,s0 */ set(5,cpu(16));
/* 0024a7d8: li a2,0x8 */ set(6,sx(UINT32_C(0x00000008)));
/* 0024a7dc: li a3,0x7 */ set(7,sx(UINT32_C(0x00000007)));
/* 0024a7e0: li t0,0x98 */ set(8,sx(UINT32_C(0x00000098)));
/* 0024a7e4: li t1,0x23 */ set(9,sx(UINT32_C(0x00000023)));
/* 0024a7e8: li t2,0x8 */ set(10,sx(UINT32_C(0x00000008)));
/* 0024a7ec: li t3,0x7 */ set(11,sx(UINT32_C(0x00000007)));
/* 0024a7f0: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024a7f4: jal 0x00279a88 */ set(31,UINT64_C(0x0024a7fc));/* delay 0024a7f8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a7f4));
/* 0024a7fc: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a800: addiu a0,s5,0x1f */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x0000001f)));
/* 0024a804: move a1,s0 */ set(5,cpu(16));
/* 0024a808: li a2,0xaa */ set(6,sx(UINT32_C(0x000000aa)));
/* 0024a80c: li a3,0x7 */ set(7,sx(UINT32_C(0x00000007)));
/* 0024a810: li t0,0x9f */ set(8,sx(UINT32_C(0x0000009f)));
/* 0024a814: li t1,0x23 */ set(9,sx(UINT32_C(0x00000023)));
/* 0024a818: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024a81c: li t3,0x7 */ set(11,sx(UINT32_C(0x00000007)));
/* 0024a820: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024a824: jal 0x00279a88 */ set(31,UINT64_C(0x0024a82c));/* delay 0024a828 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a824));
/* 0024a82c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a830: move a1,s0 */ set(5,cpu(16));
/* 0024a834: addiu a0,s5,0xc9 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x000000c9)));
/* 0024a838: li a3,0x7 */ set(7,sx(UINT32_C(0x00000007)));
/* 0024a83c: li t0,0xa1 */ set(8,sx(UINT32_C(0x000000a1)));
/* 0024a840: li a2,0x8 */ set(6,sx(UINT32_C(0x00000008)));
/* 0024a844: li t1,0x23 */ set(9,sx(UINT32_C(0x00000023)));
/* 0024a848: li t2,0x8 */ set(10,sx(UINT32_C(0x00000008)));
/* 0024a84c: li t3,0x7 */ set(11,sx(UINT32_C(0x00000007)));
/* 0024a850: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024a854: jal 0x00279a88 */ set(31,UINT64_C(0x0024a85c));/* delay 0024a858 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a854));
/* 0024a85c: lw a0,0x40(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0024a860: lui a3,0x57 */ set(7,sx(UINT32_C(0x00570000)));
/* 0024a864: lw a1,0x20(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a868: lw t0,0x20(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a86c: addu v0,a0,a1 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 0024a870: addiu a1,a3,0x4e80 */ set(5,sx((uint32_t)cpu(7)+UINT32_C(0x00004e80)));
/* 0024a874: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024a878: addu v0,v0,t0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(8)));
/* 0024a87c: sll a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)<<2));
/* 0024a880: addu v1,a1,a0 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 0024a884: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 0024a888: beq v0,zero,0x0024a8f8 */ {int taken=(cpu(2)==cpu(0));/* delay 0024a88c */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_0024a8f8;}}
/* 0024a890: addiu a0,s5,0x20 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x00000020)));
/* 0024a894: lw t4,-0x3068(gp) */ lw(12,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024a898: addiu s6,s7,0x8 */ set(22,sx((uint32_t)cpu(23)+UINT32_C(0x00000008)));
/* 0024a89c: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
/* 0024a8a0: addu s0,v1,a1 */ set(16,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0024a8a4: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0024a8a8: li a2,0x34 */ set(6,sx(UINT32_C(0x00000034)));
/* 0024a8ac: move a1,s6 */ set(5,cpu(22));
/* 0024a8b0: li a3,0x1e */ set(7,sx(UINT32_C(0x0000001e)));
/* 0024a8b4: li t0,0x9f */ set(8,sx(UINT32_C(0x0000009f)));
/* 0024a8b8: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024a8bc: li t2,0x34 */ set(10,sx(UINT32_C(0x00000034)));
/* 0024a8c0: li t3,0x1e */ set(11,sx(UINT32_C(0x0000001e)));
/* 0024a8c4: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0024a8c8: li s3,0x80 */ set(19,sx(UINT32_C(0x00000080)));
/* 0024a8cc: jal 0x00279a88 */ set(31,UINT64_C(0x0024a8d4));/* delay 0024a8d0 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(12));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a8cc));
/* 0024a8d4: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0024a8d8: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0024a8dc: slti v1,v0,0x9 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 0024a8e0: bne v1,zero,0x0024a900 */ {int taken=(cpu(3)!=cpu(0));/* delay 0024a8e4 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_0024a900;}}
/* 0024a8e8: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 0024a8ec: lui s2,0x8000 */ set(18,sx(UINT32_C(0x80000000)));
/* 0024a8f0: b 0x0024a904 */ /* delay 0024a8f4 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_0024a904;
L_0024a8f8:;
/* 0024a8f8: b 0x0024a904 */ /* delay 0024a8fc */ set(22,sx((uint32_t)cpu(23)+UINT32_C(0x00000008)));goto L_0024a904;
L_0024a900:;
/* 0024a900: lui s2,0x8000 */ set(18,sx(UINT32_C(0x80000000)));
L_0024a904:;
/* 0024a904: lw v1,0x38(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0024a908: addiu s8,s7,0x11 */ set(30,sx((uint32_t)cpu(23)+UINT32_C(0x00000011)));
/* 0024a90c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a910: li t2,0x12 */ set(10,sx(UINT32_C(0x00000012)));
/* 0024a914: or s2,v1,s2 */ set(18,cpu(3)|cpu(18));
/* 0024a918: li t1,0x1e */ set(9,sx(UINT32_C(0x0000001e)));
/* 0024a91c: li t3,0xc */ set(11,sx(UINT32_C(0x0000000c)));
/* 0024a920: li a3,0xc */ set(7,sx(UINT32_C(0x0000000c)));
/* 0024a924: li t0,0xac */ set(8,sx(UINT32_C(0x000000ac)));
/* 0024a928: addiu a0,s5,0x27 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x00000027)));
/* 0024a92c: move a1,s8 */ set(5,cpu(30));
/* 0024a930: li a2,0x12 */ set(6,sx(UINT32_C(0x00000012)));
/* 0024a934: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024a938: jal 0x00279a88 */ set(31,UINT64_C(0x0024a940));/* delay 0024a93c */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a938));
/* 0024a940: lw a1,0x20(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a944: lui a3,0x57 */ set(7,sx(UINT32_C(0x00570000)));
/* 0024a948: lw a0,0x40(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0024a94c: addiu a3,a3,0x4e80 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00004e80)));
/* 0024a950: addiu s1,a3,0x8 */ set(17,sx((uint32_t)cpu(7)+UINT32_C(0x00000008)));
/* 0024a954: lw t0,0x3c(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x0000003c)));
/* 0024a958: addu s0,a0,a1 */ set(16,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 0024a95c: addiu a0,sp,0x10 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0024a960: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 0024a964: li a2,0x63 */ set(6,sx(UINT32_C(0x00000063)));
/* 0024a968: addu s0,s0,a1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 0024a96c: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 0024a970: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 0024a974: addiu a1,a1,0x10f0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000010f0)));
/* 0024a978: addu v0,s0,s1 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(17)));
/* 0024a97c: addiu s0,s0,0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 0024a980: lw t3,0x0(v0) */ lw(11,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0024a984: or s4,t0,s3 */ set(20,cpu(8)|cpu(19));
/* 0024a988: addu s1,s0,s1 */ set(17,sx((uint32_t)cpu(16)+(uint32_t)cpu(17)));
/* 0024a98c: slti v0,t3,0x64 */ set(2,(int64_t)cpu(11)<(int64_t)(int32_t)UINT32_C(0x00000064));
/* 0024a990: jal 0x002d5690 */ set(31,UINT64_C(0x0024a998));/* delay 0024a994 */ if(cpu(2)!=0){set(6,cpu(11));}nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x0024a990));
/* 0024a998: addiu a0,s5,0x3c */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x0000003c)));
/* 0024a99c: addiu a1,s7,0x10 */ set(5,sx((uint32_t)cpu(23)+UINT32_C(0x00000010)));
/* 0024a9a0: addiu t0,sp,0x10 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0024a9a4: move a2,zero */ set(6,cpu(0));
/* 0024a9a8: move a3,s4 */ set(7,cpu(20));
/* 0024a9ac: move t1,zero */ set(9,cpu(0));
/* 0024a9b0: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 0024a9b4: jal 0x001ca430 */ set(31,UINT64_C(0x0024a9bc));/* delay 0024a9b8 */ set(5,sx((uint32_t)cpu(5)<<3));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001ca430),UINT32_C(0x0024a9b4));
/* 0024a9bc: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0024a9c0: move a0,v0 */ set(4,cpu(2));
/* 0024a9c4: jal 0x001c7e18 */ set(31,UINT64_C(0x0024a9cc));/* delay 0024a9c8 */ sw(ea(28,(int32_t)UINT32_C(0xffffde4c)),(uint32_t)cpu(2));body_001c7e18();
/* 0024a9cc: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024a9d4));/* delay 0024a9d0 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde4c)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024a9cc));
/* 0024a9d4: lw v1,-0x306c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a9d8: addiu a0,s5,0xca */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x000000ca)));
/* 0024a9dc: move a1,s7 */ set(5,cpu(23));
/* 0024a9e0: li a2,0x9b */ set(6,sx(UINT32_C(0x0000009b)));
/* 0024a9e4: li a3,0x1f */ set(7,sx(UINT32_C(0x0000001f)));
/* 0024a9e8: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024a9ec: li t1,0x51 */ set(9,sx(UINT32_C(0x00000051)));
/* 0024a9f0: li t2,0x9b */ set(10,sx(UINT32_C(0x0000009b)));
/* 0024a9f4: li t3,0x1f */ set(11,sx(UINT32_C(0x0000001f)));
/* 0024a9f8: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 0024a9fc: jal 0x00279a88 */ set(31,UINT64_C(0x0024aa04));/* delay 0024aa00 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024a9fc));
/* 0024aa04: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024aa08: move a1,s6 */ set(5,cpu(22));
/* 0024aa0c: addiu a0,s5,0xd6 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x000000d6)));
/* 0024aa10: li a2,0x27 */ set(6,sx(UINT32_C(0x00000027)));
/* 0024aa14: li a3,0x18 */ set(7,sx(UINT32_C(0x00000018)));
/* 0024aa18: li t0,0x70 */ set(8,sx(UINT32_C(0x00000070)));
/* 0024aa1c: li t1,0x12 */ set(9,sx(UINT32_C(0x00000012)));
/* 0024aa20: li t2,0x27 */ set(10,sx(UINT32_C(0x00000027)));
/* 0024aa24: li t3,0x18 */ set(11,sx(UINT32_C(0x00000018)));
/* 0024aa28: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024aa2c: jal 0x00279a88 */ set(31,UINT64_C(0x0024aa34));/* delay 0024aa30 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024aa2c));
/* 0024aa34: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024aa38: beq v0,zero,0x0024aae8 */ {int taken=(cpu(2)==cpu(0));/* delay 0024aa3c */ set(3,sx(UINT32_C(0x00570000)));if(taken){goto L_0024aae8;}}
/* 0024aa40: addiu v1,v1,0x4e80 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00004e80)));
/* 0024aa44: addu v0,v1,s0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 0024aa48: lw v0,0xc(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 0024aa4c: slti v1,v0,0x6 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0024aa50: bne v1,zero,0x0024ab44 */ {int taken=(cpu(3)!=cpu(0));/* delay 0024aa54 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_0024ab44;}}
/* 0024aa58: sll v0,v0,0x7 */ set(2,sx((uint32_t)cpu(2)<<7));
/* 0024aa5c: li v1,0xa */ set(3,sx(UINT32_C(0x0000000a)));
/* 0024aa60: addiu v0,v0,-0x280 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffd80)));
/* 0024aa64: lw a3,0x34(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000034)));
/* 0024aa68: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 0024aa6c: lw t0,0x2c(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x0000002c)));
/* 0024aa70: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 0024aa74: addiu a0,sp,0x10 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0024aa78: subu a2,a3,t0 */ set(6,sx((uint32_t)cpu(7)-(uint32_t)cpu(8)));
/* 0024aa7c: addiu a1,a1,0x10f8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000010f8)));
/* 0024aa80: beql v1,zero,0x0024aa88 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0024aa84 */ nocturneBattleRewardLevelupNativeTrap(7u,UINT32_C(0x0024aa84));goto L_0024aa88;}}
L_0024aa88:;
/* 0024aa88: lui s4,0xa09d */ set(20,sx(UINT32_C(0xa09d0000)));
/* 0024aa8c: ori s4,s4,0xc380 */ set(20,cpu(20)|UINT32_C(0x0000c380));
/* 0024aa90: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024aa94: jal 0x002d5690 */ set(31,UINT64_C(0x0024aa9c));/* delay 0024aa98 */ set(19,cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x0024aa94));
/* 0024aa9c: lw v0,0x3c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000003c)));
/* 0024aaa0: addiu a0,s5,0x11d */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x0000011d)));
/* 0024aaa4: addiu a1,s7,0x7 */ set(5,sx((uint32_t)cpu(23)+UINT32_C(0x00000007)));
/* 0024aaa8: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 0024aaac: or a3,v0,s3 */ set(7,cpu(2)|cpu(19));
/* 0024aab0: li s3,0x80 */ set(19,sx(UINT32_C(0x00000080)));
/* 0024aab4: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 0024aab8: move a2,zero */ set(6,cpu(0));
/* 0024aabc: addiu t0,sp,0x10 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0024aac0: jal 0x001ca430 */ set(31,UINT64_C(0x0024aac8));/* delay 0024aac4 */ set(9,cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001ca430),UINT32_C(0x0024aac0));
/* 0024aac8: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0024aacc: move a0,v0 */ set(4,cpu(2));
/* 0024aad0: jal 0x001c7e18 */ set(31,UINT64_C(0x0024aad8));/* delay 0024aad4 */ sw(ea(28,(int32_t)UINT32_C(0xffffde4c)),(uint32_t)cpu(2));body_001c7e18();
/* 0024aad8: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024aae0));/* delay 0024aadc */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde4c)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024aad8));
/* 0024aae0: b 0x0024ab44 */ /* delay 0024aae4 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));goto L_0024ab44;
L_0024aae8:;
/* 0024aae8: lw a3,0x2c(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x0000002c)));
/* 0024aaec: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 0024aaf0: lw v1,0x34(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000034)));
/* 0024aaf4: addiu a0,sp,0x10 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0024aaf8: addiu a1,a1,0x10f8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000010f8)));
/* 0024aafc: jal 0x002d5690 */ set(31,UINT64_C(0x0024ab04));/* delay 0024ab00 */ set(6,sx((uint32_t)cpu(3)-(uint32_t)cpu(7)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x0024aafc));
/* 0024ab04: addiu a0,s5,0x11d */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x0000011d)));
/* 0024ab08: addiu a1,s7,0x7 */ set(5,sx((uint32_t)cpu(23)+UINT32_C(0x00000007)));
/* 0024ab0c: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 0024ab10: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 0024ab14: move a2,zero */ set(6,cpu(0));
/* 0024ab18: move a3,s4 */ set(7,cpu(20));
/* 0024ab1c: addiu t0,sp,0x10 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0024ab20: jal 0x001ca430 */ set(31,UINT64_C(0x0024ab28));/* delay 0024ab24 */ set(9,cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001ca430),UINT32_C(0x0024ab20));
/* 0024ab28: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0024ab2c: move a0,v0 */ set(4,cpu(2));
/* 0024ab30: jal 0x001c7e18 */ set(31,UINT64_C(0x0024ab38));/* delay 0024ab34 */ sw(ea(28,(int32_t)UINT32_C(0xffffde4c)),(uint32_t)cpu(2));body_001c7e18();
/* 0024ab38: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024ab40));/* delay 0024ab3c */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde4c)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024ab38));
/* 0024ab40: lw v1,0x20(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));
L_0024ab44:;
/* 0024ab44: lui a0,0x57 */ set(4,sx(UINT32_C(0x00570000)));
/* 0024ab48: lw t0,0x40(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0024ab4c: addiu a1,a0,0x4e80 */ set(5,sx((uint32_t)cpu(4)+UINT32_C(0x00004e80)));
/* 0024ab50: addu v0,t0,v1 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(3)));
/* 0024ab54: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024ab58: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0024ab5c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024ab60: addiu a0,v0,0x10 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 0024ab64: addu v1,a1,a0 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 0024ab68: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0024ab6c: beq v0,zero,0x0024ac78 */ {int taken=(cpu(2)==cpu(0));/* delay 0024ab70 */ set(2,cpu(3));if(taken){goto L_0024ac78;}}
/* 0024ab74: lw s0,0xc(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 0024ab78: slti v1,s0,0x2 */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0024ab7c: beq v1,zero,0x0024abf0 */ {int taken=(cpu(3)==cpu(0));/* delay 0024ab80 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x0000000b));if(taken){goto L_0024abf0;}}
/* 0024ab84: sll v0,s0,0x3 */ set(2,sx((uint32_t)cpu(16)<<3));
/* 0024ab88: li a0,0xe */ set(4,sx(UINT32_C(0x0000000e)));
/* 0024ab8c: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 0024ab90: lui v1,0x80 */ set(3,sx(UINT32_C(0x00800000)));
/* 0024ab94: subu s0,a0,v0 */ set(16,sx((uint32_t)cpu(4)-(uint32_t)cpu(2)));
/* 0024ab98: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024ab9c: srl a1,s0,0x1f */ set(5,sx((uint32_t)cpu(16)>>31));
/* 0024aba0: sll t4,s3,0x18 */ set(12,sx((uint32_t)cpu(19)<<24));
/* 0024aba4: addu a1,s0,a1 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 0024aba8: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 0024abac: sra a1,a1,0x1 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>1)));
/* 0024abb0: or t4,t4,v1 */ set(12,cpu(12)|cpu(3));
/* 0024abb4: subu a1,s7,a1 */ set(5,sx((uint32_t)cpu(23)-(uint32_t)cpu(5)));
/* 0024abb8: move a3,s0 */ set(7,cpu(16));
/* 0024abbc: addiu a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000018)));
/* 0024abc0: addiu a0,s5,0xf9 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x000000f9)));
/* 0024abc4: li a2,0x68 */ set(6,sx(UINT32_C(0x00000068)));
/* 0024abc8: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024abcc: li t1,0x2e */ set(9,sx(UINT32_C(0x0000002e)));
/* 0024abd0: li t2,0x68 */ set(10,sx(UINT32_C(0x00000068)));
/* 0024abd4: li t3,0xe */ set(11,sx(UINT32_C(0x0000000e)));
/* 0024abd8: sw t4,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 0024abdc: jal 0x00279a88 */ set(31,UINT64_C(0x0024abe4));/* delay 0024abe0 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024abdc));
/* 0024abe4: b 0x0024ad78 */ /* delay 0024abe8 */ goto L_0024ad78;
L_0024abf0:;
/* 0024abf0: bne v0,zero,0x0024ad78 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024abf4 */ set(2,sx((uint32_t)cpu(16)<<3));if(taken){goto L_0024ad78;}}
/* 0024abf8: li v1,0x5 */ set(3,sx(UINT32_C(0x00000005)));
/* 0024abfc: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 0024ac00: lui a0,0x80 */ set(4,sx(UINT32_C(0x00800000)));
/* 0024ac04: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0024ac08: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0024ac0c: addiu v0,v0,-0x8c */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffff74)));
/* 0024ac10: sll a1,s3,0x18 */ set(5,sx((uint32_t)cpu(19)<<24));
/* 0024ac14: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 0024ac18: or a1,a1,a0 */ set(5,cpu(5)|cpu(4));
/* 0024ac1c: beql v1,zero,0x0024ac24 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0024ac20 */ nocturneBattleRewardLevelupNativeTrap(7u,UINT32_C(0x0024ac20));goto L_0024ac24;}}
L_0024ac24:;
/* 0024ac24: lw v1,-0x306c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024ac28: sw a1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
/* 0024ac2c: addiu a0,s5,0xf9 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x000000f9)));
/* 0024ac30: li a2,0x68 */ set(6,sx(UINT32_C(0x00000068)));
/* 0024ac34: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024ac38: li t1,0x3d */ set(9,sx(UINT32_C(0x0000003d)));
/* 0024ac3c: li t2,0x68 */ set(10,sx(UINT32_C(0x00000068)));
/* 0024ac40: li t3,0xe */ set(11,sx(UINT32_C(0x0000000e)));
/* 0024ac44: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 0024ac48: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024ac4c: move s0,v0 */ set(16,cpu(2));
/* 0024ac50: srl a1,s0,0x1f */ set(5,sx((uint32_t)cpu(16)>>31));
/* 0024ac54: move a3,s0 */ set(7,cpu(16));
/* 0024ac58: addu a1,s0,a1 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 0024ac5c: sra a1,a1,0x1 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>1)));
/* 0024ac60: subu a1,s7,a1 */ set(5,sx((uint32_t)cpu(23)-(uint32_t)cpu(5)));
/* 0024ac64: jal 0x00279a88 */ set(31,UINT64_C(0x0024ac6c));/* delay 0024ac68 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000018)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024ac64));
/* 0024ac6c: b 0x0024ad78 */ /* delay 0024ac70 */ goto L_0024ad78;
L_0024ac78:;
/* 0024ac78: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
/* 0024ac7c: sll v1,s3,0x18 */ set(3,sx((uint32_t)cpu(19)<<24));
/* 0024ac80: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0024ac84: lw t4,-0x306c(gp) */ lw(12,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024ac88: addiu s2,s5,0xf9 */ set(18,sx((uint32_t)cpu(21)+UINT32_C(0x000000f9)));
/* 0024ac8c: or s0,v1,v0 */ set(16,cpu(3)|cpu(2));
/* 0024ac90: move a0,s2 */ set(4,cpu(18));
/* 0024ac94: move a1,s8 */ set(5,cpu(30));
/* 0024ac98: li a2,0x68 */ set(6,sx(UINT32_C(0x00000068)));
/* 0024ac9c: li a3,0xe */ set(7,sx(UINT32_C(0x0000000e)));
/* 0024aca0: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024aca4: li t1,0x3d */ set(9,sx(UINT32_C(0x0000003d)));
/* 0024aca8: li t2,0x68 */ set(10,sx(UINT32_C(0x00000068)));
/* 0024acac: li t3,0xe */ set(11,sx(UINT32_C(0x0000000e)));
/* 0024acb0: sw t4,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(12));
/* 0024acb4: jal 0x00279a88 */ set(31,UINT64_C(0x0024acbc));/* delay 0024acb8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024acb4));
/* 0024acbc: lw v0,0x2c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000002c)));
/* 0024acc0: lw a0,0x30(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024acc4: lw a1,0x34(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000034)));
/* 0024acc8: subu v1,v0,a0 */ set(3,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0024accc: lw a3,0x30(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024acd0: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 0024acd4: subu a0,a1,a0 */ set(4,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));
/* 0024acd8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0024acdc: lw t0,0x2c(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x0000002c)));
/* 0024ace0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024ace4: li a1,0x68 */ set(5,sx(UINT32_C(0x00000068)));
/* 0024ace8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0024acec: slt a2,a3,t0 */ set(6,(int64_t)cpu(7)<(int64_t)cpu(8));
/* 0024acf0: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0024acf4: beql a0,zero,0x0024acfc */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0024acf8 */ nocturneBattleRewardLevelupNativeTrap(7u,UINT32_C(0x0024acf8));goto L_0024acfc;}}
L_0024acfc:;
/* 0024acfc: div v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),1,0);
/* 0024ad00: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024ad04: move a3,v0 */ set(7,cpu(2));
/* 0024ad08: slti v1,a3,0x0 */ set(3,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 0024ad0c: movn a3,zero,v1 */ if(cpu(3)!=0){set(7,cpu(0));}
/* 0024ad10: slti v0,a3,0x69 */ set(2,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x00000069));
/* 0024ad14: beq a2,zero,0x0024ad28 */ {int taken=(cpu(6)==cpu(0));/* delay 0024ad18 */ if(cpu(2)==0){set(7,cpu(5));}if(taken){goto L_0024ad28;}}
/* 0024ad1c: slti v1,a3,0x2 */ set(3,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0024ad20: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0024ad24: movn a3,v0,v1 */ if(cpu(3)!=0){set(7,cpu(2));}
L_0024ad28:;
/* 0024ad28: lw v1,0x2c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000002c)));
/* 0024ad2c: lw a0,0x34(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000034)));
/* 0024ad30: slt v0,v1,a0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(4));
/* 0024ad34: beq v0,zero,0x0024ad4c */ {int taken=(cpu(2)==cpu(0));/* delay 0024ad38 */ set(6,cpu(7));if(taken){goto L_0024ad4c;}}
/* 0024ad3c: slti v1,a3,0x68 */ set(3,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x00000068));
/* 0024ad40: li v0,0x67 */ set(2,sx(UINT32_C(0x00000067)));
/* 0024ad44: movz a3,v0,v1 */ if(cpu(3)==0){set(7,cpu(2));}
/* 0024ad48: move a2,a3 */ set(6,cpu(7));
L_0024ad4c:;
/* 0024ad4c: li a3,0xe */ set(7,sx(UINT32_C(0x0000000e)));
/* 0024ad50: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024ad54: move a0,s2 */ set(4,cpu(18));
/* 0024ad58: move a1,s8 */ set(5,cpu(30));
/* 0024ad5c: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024ad60: li t1,0x2e */ set(9,sx(UINT32_C(0x0000002e)));
/* 0024ad64: move t2,a2 */ set(10,cpu(6));
/* 0024ad68: li t3,0xe */ set(11,sx(UINT32_C(0x0000000e)));
/* 0024ad6c: sw s0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 0024ad70: jal 0x00279a88 */ set(31,UINT64_C(0x0024ad78));/* delay 0024ad74 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024ad70));
L_0024ad78:;
/* 0024ad78: jal 0x001c6160 */ set(31,UINT64_C(0x0024ad80));/* delay 0024ad7c */ set(4,sx(UINT32_C(0x00000014)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c6160),UINT32_C(0x0024ad78));
/* 0024ad80: lw a1,0x24(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 0024ad84: lw v0,0x0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0024ad88: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 0024ad8c: beq v0,zero,0x0024ade8 */ {int taken=(cpu(2)==cpu(0));/* delay 0024ad90 */ set(7,cpu(0));if(taken){goto L_0024ade8;}}
/* 0024ad94: move a0,zero */ set(4,cpu(0));
/* 0024ad98: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0024ad9c: jal 0x001c9d60 */ set(31,UINT64_C(0x0024ada4));/* delay 0024ada0 */ set(6,cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c9d60),UINT32_C(0x0024ad9c));
/* 0024ada4: addiu a1,s5,0x59 */ set(5,sx((uint32_t)cpu(21)+UINT32_C(0x00000059)));
/* 0024ada8: addiu a2,s7,0xc */ set(6,sx((uint32_t)cpu(23)+UINT32_C(0x0000000c)));
/* 0024adac: move a0,v0 */ set(4,cpu(2));
/* 0024adb0: sll a2,a2,0x3 */ set(6,sx((uint32_t)cpu(6)<<3));
/* 0024adb4: sll a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)<<4));
/* 0024adb8: jal 0x001c7b30 */ set(31,UINT64_C(0x0024adc0));/* delay 0024adbc */ sw(ea(28,(int32_t)UINT32_C(0xffffde4c)),(uint32_t)cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7b30),UINT32_C(0x0024adb8));
/* 0024adc0: lw a0,-0x21b4(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde4c)));
/* 0024adc4: jal 0x001c7ba8 */ set(31,UINT64_C(0x0024adcc));/* delay 0024adc8 */ set(5,cpu(20));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c7ba8),UINT32_C(0x0024adc4));
/* 0024adcc: jal 0x001c7e00 */ set(31,UINT64_C(0x0024add4));/* delay 0024add0 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde4c)));body_001c7e00();
/* 0024add4: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024addc));/* delay 0024add8 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde4c)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024add4));
/* 0024addc: b 0x0024ae34 */ /* delay 0024ade0 */ goto L_0024ae34;
L_0024ade8:;
/* 0024ade8: lw a3,0x24(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 0024adec: addiu a0,s5,0x59 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x00000059)));
/* 0024adf0: addiu a1,s7,0xc */ set(5,sx((uint32_t)cpu(23)+UINT32_C(0x0000000c)));
/* 0024adf4: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 0024adf8: lhu v0,0x4(a3) */ set(2,half(ea(7,(int32_t)UINT32_C(0x00000004))));
/* 0024adfc: move a3,s4 */ set(7,cpu(20));
/* 0024ae00: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 0024ae04: move a2,zero */ set(6,cpu(0));
/* 0024ae08: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024ae0c: lui t0,0x3e */ set(8,sx(UINT32_C(0x003e0000)));
/* 0024ae10: addu t0,t0,v0 */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(2)));
/* 0024ae14: lw t0,0x7328(t0) */ lw(8,ea(8,(int32_t)UINT32_C(0x00007328)));
/* 0024ae18: jal 0x001ca258 */ set(31,UINT64_C(0x0024ae20));/* delay 0024ae1c */ set(9,cpu(0));body_001ca258();
/* 0024ae20: move a0,v0 */ set(4,cpu(2));
/* 0024ae24: jal 0x001c7e00 */ set(31,UINT64_C(0x0024ae2c));/* delay 0024ae28 */ sw(ea(28,(int32_t)UINT32_C(0xffffde4c)),(uint32_t)cpu(2));body_001c7e00();
/* 0024ae2c: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024ae34));/* delay 0024ae30 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde4c)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024ae2c));
L_0024ae34:;
/* 0024ae34: jal 0x001c6160 */ set(31,UINT64_C(0x0024ae3c));/* delay 0024ae38 */ set(4,sx(UINT32_C(0xffffffff)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001c6160),UINT32_C(0x0024ae34));
/* 0024ae3c: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
L_0024ae40:;
/* 0024ae40: ld s1,0x58(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0024ae44: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0024ae48: ld s3,0x68(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0024ae4c: ld s4,0x70(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0024ae50: ld s5,0x78(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0024ae54: ld s6,0x80(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0024ae58: ld s7,0x88(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0024ae5c: ld s8,0x90(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0024ae60: ld ra,0x98(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0024ae64: jr ra */ {uint64_t target=cpu(31);/* delay 0024ae68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000a0)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleRewardLevelupNativeBody(uint32_t entry){switch(entry){
case UINT32_C(0x001c7e00):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001c7e00();return 1u;case UINT32_C(0x001c7e18):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001c7e18();return 1u;case UINT32_C(0x001ca0d0):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001ca0d0();return 1u;case UINT32_C(0x001ca258):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001ca258();return 1u;case UINT32_C(0x0024a2e8):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024a2e8();return 1u;case UINT32_C(0x0024a440):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024a440();return 1u;
default:return 0u;}}
uint64_t ps2BattleRewardLevelupNative_001CA0D0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);set(10,a6);set(11,a7);body_001ca0d0();return cpu(2);}
uint64_t ps2BattleRewardLevelupNative_001CA258(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);body_001ca258();return cpu(2);}
uint64_t ps2BattleRewardLevelupNative_001C7E00(uint64_t a0){set(4,a0);body_001c7e00();return cpu(2);}
uint64_t ps2BattleRewardLevelupNative_001C7E18(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_001c7e18();return cpu(2);}
void ps2BattleRewardLevelupNative_0024A2E8(void){body_0024a2e8();}
void ps2BattleRewardLevelupNative_0024A440(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);body_0024a440();}
