/* Complete15 original result lifecycle and battle-return-file input/control owners; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_reward_lifecycle_native.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveBattleRewardLifecycleNativeAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattleRewardLifecycleNativeCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneBattleRewardLifecycleNativeCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneBattleRewardLifecycleNativeCpuWrite(r,q);if(r==29u)nocturneBattleRewardLifecycleNativeSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}









#include "ee_fpu_sqrt.h"
#include "ee_vu_rotation.h"









static void body_00127368(void);
static void body_00127378(void);
static void body_00127510(void);
static void body_00127580(void);
static void body_00128408(void);
static void body_00136628(void);
static void body_001e1770(void);
static void body_0024bf40(void);
static void body_0024c1d0(void);
static void body_0024c3c8(void);
static void body_0024cbb8(void);
static void body_0028dd50(void);
static void body_0028dda8(void);
static void body_002969a0(void);
static void body_00297890(void);
static void body_00127368(void){
uint64_t incoming=cpu(31);
/* 00127368: sw a0,-0x557c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffaa84)),(uint32_t)cpu(4));
/* 0012736c: jr ra */ {uint64_t target=cpu(31);/* delay 00127370 */ sw(ea(28,(int32_t)UINT32_C(0xffffaa88)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_00127378(void){
uint64_t incoming=cpu(31);
/* 00127378: addiu sp,sp,-0xc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff40)));
/* 0012737c: sd s2,0xa0(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 00127380: lw s2,-0x557c(gp) */ lw(18,ea(28,(int32_t)UINT32_C(0xffffaa84)));
/* 00127384: sd s3,0xa8(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 00127388: sd s0,0x90(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0012738c: sd s1,0x98(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00127390: sd ra,0xb0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 00127394: bne s2,zero,0x001273a4 */ {int taken=(cpu(18)!=cpu(0));/* delay 00127398 */ lw(19,ea(28,(int32_t)UINT32_C(0xffffaa88)));if(taken){goto L_001273a4;}}
/* 0012739c: beq s3,zero,0x00127400 */ {int taken=(cpu(19)==cpu(0));/* delay 001273a0 */ set(2,cpu(0));if(taken){goto L_00127400;}}
L_001273a4:;
/* 001273a4: jal 0x00127510 */ set(31,UINT64_C(0x001273ac));/* delay 001273a8 */ set(16,sx(UINT32_C(0x00300000)));body_00127510();
/* 001273ac: addiu s0,s0,-0x4080 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffbf80)));
/* 001273b0: move a0,sp */ set(4,cpu(29));
/* 001273b4: sw s2,0x88(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000088)),(uint32_t)cpu(18));
/* 001273b8: move a1,s2 */ set(5,cpu(18));
/* 001273bc: sw s3,0x8c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000008c)),(uint32_t)cpu(19));
/* 001273c0: jal 0x00128408 */ set(31,UINT64_C(0x001273c8));/* delay 001273c4 */ set(6,sx(UINT32_C(0x00000001)));body_00128408();
/* 001273c8: lui a1,0x53 */ set(5,sx(UINT32_C(0x00530000)));
/* 001273cc: addiu s1,sp,0x40 */ set(17,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
/* 001273d0: addiu a1,a1,0x1a40 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001a40)));
/* 001273d4: move a3,s2 */ set(7,cpu(18));
/* 001273d8: move t0,s3 */ set(8,cpu(19));
/* 001273dc: move a2,sp */ set(6,cpu(29));
/* 001273e0: jal 0x002d5690 */ set(31,UINT64_C(0x001273e8));/* delay 001273e4 */ set(4,cpu(17));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x001273e0));
/* 001273e8: jal 0x002969a0 */ set(31,UINT64_C(0x001273f0));/* delay 001273ec */ set(4,cpu(17));body_002969a0();
/* 001273f0: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 001273f4: sw v1,0x84(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000084)),(uint32_t)cpu(3));
/* 001273f8: sw v0,-0x55b8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffaa48)),(uint32_t)cpu(2));
/* 001273fc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_00127400:;
/* 00127400: ld s0,0x90(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 00127404: ld s1,0x98(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00127408: ld s2,0xa0(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0012740c: ld s3,0xa8(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 00127410: ld ra,0xb0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 00127414: jr ra */ {uint64_t target=cpu(31);/* delay 00127418 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000c0)));checkReturn(target,incoming);return;}
}
static void body_00127510(void){
uint64_t incoming=cpu(31);
/* 00127510: lw a0,-0x55b8(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffaa48)));
/* 00127514: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00127518: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012751c: beq a0,zero,0x00127554 */ {int taken=(cpu(4)==cpu(0));/* delay 00127520 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_00127554;}}
/* 00127524: lw s0,0x60(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000060)));
/* 00127528: beq s0,zero,0x00127548 */ {int taken=(cpu(16)==cpu(0));/* delay 0012752c */ if(taken){goto L_00127548;}}
L_00127530:;
/* 00127530: jal 0x002a9650 */ set(31,UINT64_C(0x00127538));/* delay 00127534 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a9650),UINT32_C(0x00127530));
/* 00127538: lw s0,0x0(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0012753c: bne s0,zero,0x00127530 */ {int taken=(cpu(16)!=cpu(0));/* delay 00127540 */ if(taken){goto L_00127530;}}
/* 00127544: lw a0,-0x55b8(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffaa48)));
L_00127548:;
/* 00127548: jal 0x002966a8 */ set(31,UINT64_C(0x00127550));/* delay 0012754c */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002966a8),UINT32_C(0x00127548));
/* 00127550: sw zero,-0x55b8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffaa48)),(uint32_t)cpu(0));
L_00127554:;
/* 00127554: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 00127558: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012755c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00127560: addiu v0,v0,-0x4080 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffbf80)));
/* 00127564: sw zero,-0x557c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffaa84)),(uint32_t)cpu(0));
/* 00127568: sw zero,-0x5578(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffaa88)),(uint32_t)cpu(0));
/* 0012756c: sw zero,0x84(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000084)),(uint32_t)cpu(0));
/* 00127570: sw zero,0x88(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000088)),(uint32_t)cpu(0));
/* 00127574: sw zero,0x8c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000008c)),(uint32_t)cpu(0));
/* 00127578: jr ra */ {uint64_t target=cpu(31);/* delay 0012757c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00127580(void){
uint64_t incoming=cpu(31);
/* 00127580: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00127584: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 00127588: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012758c: addiu s0,v0,-0x4080 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffbf80)));
/* 00127590: lw v1,0x84(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000084)));
/* 00127594: beq v1,zero,0x001275b8 */ {int taken=(cpu(3)==cpu(0));/* delay 00127598 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_001275b8;}}
/* 0012759c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001275a0: bnel v1,v0,0x001275bc */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 001275a4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001275bc;}}
/* 001275a8: jal 0x00296b08 */ set(31,UINT64_C(0x001275b0));/* delay 001275ac */ lw(4,ea(28,(int32_t)UINT32_C(0xffffaa48)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00296b08),UINT32_C(0x001275a8));
/* 001275b0: bnel v0,zero,0x001275b8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001275b4 */ sw(ea(16,(int32_t)UINT32_C(0x00000084)),(uint32_t)cpu(0));goto L_001275b8;}}
L_001275b8:;
/* 001275b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001275bc:;
/* 001275bc: move v0,zero */ set(2,cpu(0));
/* 001275c0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001275c4: jr ra */ {uint64_t target=cpu(31);/* delay 001275c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00128408(void){
uint64_t incoming=cpu(31);
/* 00128408: move v1,a1 */ set(3,cpu(5));
/* 0012840c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00128410: slti v0,v1,0xc8 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x000000c8));
/* 00128414: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00128418: move a2,v1 */ set(6,cpu(3));
/* 0012841c: beq v0,zero,0x00128438 */ {int taken=(cpu(2)==cpu(0));/* delay 00128420 */ set(5,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x000001f4));if(taken){goto L_00128438;}}
/* 00128424: lui a1,0x53 */ set(5,sx(UINT32_C(0x00530000)));
/* 00128428: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012842c: addiu a1,a1,0x1ad8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001ad8)));
/* 00128430: j 0x002d5690 */ /* delay 00128434 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x00128430));return;
L_00128438:;
/* 00128438: beq a1,zero,0x00128458 */ {int taken=(cpu(5)==cpu(0));/* delay 0012843c */ set(5,sx(UINT32_C(0x00530000)));if(taken){goto L_00128458;}}
/* 00128440: lui a1,0x53 */ set(5,sx(UINT32_C(0x00530000)));
/* 00128444: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00128448: move a2,v1 */ set(6,cpu(3));
/* 0012844c: addiu a1,a1,0x1ae8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001ae8)));
/* 00128450: j 0x002d5690 */ /* delay 00128454 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x00128450));return;
L_00128458:;
/* 00128458: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012845c: move a2,v1 */ set(6,cpu(3));
/* 00128460: addiu a1,a1,0x1af8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001af8)));
/* 00128464: j 0x002d5690 */ /* delay 00128468 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x00128464));return;
}
static void body_00136628(void){
uint64_t incoming=cpu(31);
/* 00136628: jr ra */ {uint64_t target=cpu(31);/* delay 0013662c */ sw(ea(28,(int32_t)UINT32_C(0xffffabb8)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_001e1770(void){
uint64_t incoming=cpu(31);
/* 001e1770: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001e1774: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001e1778: jal 0x0010e588 */ set(31,UINT64_C(0x001e1780));/* delay 001e177c */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x0010e588),UINT32_C(0x001e1778));
/* 001e1780: beq v0,zero,0x001e1798 */ {int taken=(cpu(2)==cpu(0));/* delay 001e1784 */ set(4,cpu(2));if(taken){goto L_001e1798;}}
/* 001e1788: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001e178c: j 0x0010e610 */ /* delay 001e1790 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x0010e610),UINT32_C(0x001e178c));return;
L_001e1798:;
/* 001e1798: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001e179c: jr ra */ {uint64_t target=cpu(31);/* delay 001e17a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0024bf40(void){
uint64_t incoming=cpu(31);
/* 0024bf40: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024bf44: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024bf48: move s0,zero */ set(16,cpu(0));
/* 0024bf4c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024bf50: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024bf54: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024bf58: jal 0x002469a0 */ set(31,UINT64_C(0x0024bf60));/* delay 0024bf5c */ set(17,sx(UINT32_C(0x0000001f)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002469a0),UINT32_C(0x0024bf58));
/* 0024bf60: move s2,v0 */ set(18,cpu(2));
/* 0024bf64: lw a1,0x0(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000000)));
L_0024bf68:;
/* 0024bf68: addu v1,s0,a1 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 0024bf6c: lw v0,0x78(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000078)));
/* 0024bf70: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0024bf74: beq v0,zero,0x0024bfa0 */ {int taken=(cpu(2)==cpu(0));/* delay 0024bf78 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));if(taken){goto L_0024bfa0;}}
/* 0024bf7c: lw v0,0xb4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x000000b4)));
/* 0024bf80: beq v0,zero,0x0024bf9c */ {int taken=(cpu(2)==cpu(0));/* delay 0024bf84 */ set(4,cpu(2));if(taken){goto L_0024bf9c;}}
/* 0024bf88: jal 0x002966a8 */ set(31,UINT64_C(0x0024bf90));/* delay 0024bf8c */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002966a8),UINT32_C(0x0024bf88));
/* 0024bf90: lw a1,0x0(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0024bf94: addu v0,s0,a1 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 0024bf98: sw zero,0xb4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x000000b4)),(uint32_t)cpu(0));
L_0024bf9c:;
/* 0024bf9c: addu v0,s0,a1 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
L_0024bfa0:;
/* 0024bfa0: addiu s0,s0,0xf0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000000f0)));
/* 0024bfa4: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
/* 0024bfa8: bgez s1,0x0024bf68 */ {int taken=((int64_t)cpu(17)>=0);/* delay 0024bfac */ sw(ea(2,(int32_t)UINT32_C(0x00000078)),(uint32_t)cpu(0));if(taken){goto L_0024bf68;}}
/* 0024bfb0: lw v1,0x10(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 0024bfb4: li s1,0xd */ set(17,sx(UINT32_C(0x0000000d)));
L_0024bfb8:;
/* 0024bfb8: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 0024bfbc: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
/* 0024bfc0: ori v0,v0,0x28 */ set(2,cpu(2)|UINT32_C(0x00000028));
/* 0024bfc4: sh v0,0x0(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));
/* 0024bfc8: nop  */ 
/* 0024bfcc: bgez s1,0x0024bfb8 */ {int taken=((int64_t)cpu(17)>=0);/* delay 0024bfd0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000080)));if(taken){goto L_0024bfb8;}}
/* 0024bfd4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024bfd8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024bfdc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024bfe0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024bfe4: j 0x001e1770 */ /* delay 0024bfe8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_001e1770();return;
}
static void body_0024c1d0(void){
uint64_t incoming=cpu(31);
/* 0024c1d0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024c1d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c1d8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c1dc: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024c1e0: jal 0x00101aa0 */ set(31,UINT64_C(0x0024c1e8));/* delay 0024c1e4 */ set(16,cpu(4));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00101aa0),UINT32_C(0x0024c1e0));
/* 0024c1e8: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 0024c1ec: bne v0,v1,0x0024c1fc */ {int taken=(cpu(2)!=cpu(3));/* delay 0024c1f0 */ if(taken){goto L_0024c1fc;}}
/* 0024c1f4: jal 0x00105048 */ set(31,UINT64_C(0x0024c1fc));/* delay 0024c1f8 */ set(4,sx(UINT32_C(0x0000000a)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00105048),UINT32_C(0x0024c1f4));
L_0024c1fc:;
/* 0024c1fc: jal 0x00101aa0 */ set(31,UINT64_C(0x0024c204));/* delay 0024c200 */ set(4,cpu(16));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00101aa0),UINT32_C(0x0024c1fc));
/* 0024c204: sltiu v0,v0,0x10 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0024c208: bne v0,zero,0x0024c228 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c20c */ if(taken){goto L_0024c228;}}
/* 0024c210: jal 0x0010e548 */ set(31,UINT64_C(0x0024c218));/* delay 0024c214 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x0010e548),UINT32_C(0x0024c210));
/* 0024c218: beq v0,zero,0x0024c228 */ {int taken=(cpu(2)==cpu(0));/* delay 0024c21c */ if(taken){goto L_0024c228;}}
/* 0024c220: jal 0x0024bf40 */ set(31,UINT64_C(0x0024c228));/* delay 0024c224 */ body_0024bf40();
L_0024c228:;
/* 0024c228: jal 0x002469a0 */ set(31,UINT64_C(0x0024c230));/* delay 0024c22c */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002469a0),UINT32_C(0x0024c228));
/* 0024c230: move a0,s0 */ set(4,cpu(16));
/* 0024c234: jal 0x00101aa0 */ set(31,UINT64_C(0x0024c23c));/* delay 0024c238 */ set(17,cpu(2));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00101aa0),UINT32_C(0x0024c234));
/* 0024c23c: li v1,0x14 */ set(3,sx(UINT32_C(0x00000014)));
/* 0024c240: bnel v0,v1,0x0024c258 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 0024c244 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf70)));goto L_0024c258;}}
/* 0024c248: jal 0x00127378 */ set(31,UINT64_C(0x0024c250));/* delay 0024c24c */ body_00127378();
/* 0024c250: sw v0,-0x3090(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf70)),(uint32_t)cpu(2));
/* 0024c254: lw v0,-0x3090(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf70)));
L_0024c258:;
/* 0024c258: beq v0,zero,0x0024c288 */ {int taken=(cpu(2)==cpu(0));/* delay 0024c25c */ if(taken){goto L_0024c288;}}
/* 0024c260: jal 0x00127580 */ set(31,UINT64_C(0x0024c268));/* delay 0024c264 */ body_00127580();
/* 0024c268: jal 0x001275d0 */ set(31,UINT64_C(0x0024c270));/* delay 0024c26c */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x001275d0),UINT32_C(0x0024c268));
/* 0024c270: bne v0,zero,0x0024c288 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c274 */ if(taken){goto L_0024c288;}}
/* 0024c278: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 0024c27c: sw zero,-0x3090(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf70)),(uint32_t)cpu(0));
/* 0024c280: jal 0x002d4748 */ set(31,UINT64_C(0x0024c288));/* delay 0024c284 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000035f8)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x0024c280));
L_0024c288:;
/* 0024c288: jal 0x00101aa0 */ set(31,UINT64_C(0x0024c290));/* delay 0024c28c */ set(4,cpu(16));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x00101aa0),UINT32_C(0x0024c288));
/* 0024c290: sltiu v0,v0,0x15 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000015));
/* 0024c294: bne v0,zero,0x0024c2f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c298 */ set(16,sx(UINT32_C(0x002f0000)));if(taken){goto L_0024c2f8;}}
/* 0024c29c: addiu v1,s0,0x5810 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00005810)));
/* 0024c2a0: lb v0,0x21(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000021))));
/* 0024c2a4: bne v0,zero,0x0024c2b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c2a8 */ if(taken){goto L_0024c2b8;}}
/* 0024c2ac: lb v0,0x23(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000023))));
/* 0024c2b0: beq v0,zero,0x0024c2c0 */ {int taken=(cpu(2)==cpu(0));/* delay 0024c2b4 */ if(taken){goto L_0024c2c0;}}
L_0024c2b8:;
/* 0024c2b8: jal 0x0024ae70 */ set(31,UINT64_C(0x0024c2c0));/* delay 0024c2bc */ set(4,cpu(17));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x0024ae70),UINT32_C(0x0024c2b8));
L_0024c2c0:;
/* 0024c2c0: jal 0x0024afa0 */ set(31,UINT64_C(0x0024c2c8));/* delay 0024c2c4 */ set(4,cpu(17));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x0024afa0),UINT32_C(0x0024c2c0));
/* 0024c2c8: slti v0,v0,0xf */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x0000000f));
/* 0024c2cc: bne v0,zero,0x0024c2f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c2d0 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00005810)));if(taken){goto L_0024c2f8;}}
/* 0024c2d4: lb v0,0x21(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000021))));
/* 0024c2d8: bne v0,zero,0x0024c2ec */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c2dc */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf68)));if(taken){goto L_0024c2ec;}}
/* 0024c2e0: lb v0,0x23(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000023))));
/* 0024c2e4: beq v0,zero,0x0024c2f8 */ {int taken=(cpu(2)==cpu(0));/* delay 0024c2e8 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf68)));if(taken){goto L_0024c2f8;}}
L_0024c2ec:;
/* 0024c2ec: bne v0,zero,0x0024c2f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c2f0 */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_0024c2f8;}}
/* 0024c2f4: sw v1,-0x3098(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf68)),(uint32_t)cpu(3));
L_0024c2f8:;
/* 0024c2f8: jal 0x0024b010 */ set(31,UINT64_C(0x0024c300));/* delay 0024c2fc */ set(4,cpu(17));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x0024b010),UINT32_C(0x0024c2f8));
/* 0024c300: lw v1,-0x3098(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf68)));
/* 0024c304: blez v1,0x0024c364 */ {int taken=((int64_t)cpu(3)<=0);/* delay 0024c308 */ set(2,cpu(0));if(taken){goto L_0024c364;}}
/* 0024c30c: slti v0,v1,0x64 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000064));
/* 0024c310: beq v0,zero,0x0024c324 */ {int taken=(cpu(2)==cpu(0));/* delay 0024c314 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000010));if(taken){goto L_0024c324;}}
/* 0024c318: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0024c31c: sw v1,-0x3098(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf68)),(uint32_t)cpu(3));
/* 0024c320: slti v0,v1,0x10 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000010));
L_0024c324:;
/* 0024c324: bne v0,zero,0x0024c364 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c328 */ set(2,cpu(0));if(taken){goto L_0024c364;}}
/* 0024c32c: lw v0,-0x3090(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf70)));
/* 0024c330: bne v0,zero,0x0024c364 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c334 */ set(2,cpu(0));if(taken){goto L_0024c364;}}
/* 0024c338: jal 0x0024c060 */ set(31,UINT64_C(0x0024c340));/* delay 0024c33c */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x0024c060),UINT32_C(0x0024c338));
/* 0024c340: jal 0x0028dda8 */ set(31,UINT64_C(0x0024c348));/* delay 0024c344 */ body_0028dda8();
/* 0024c348: lw v0,0x70(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000070)));
/* 0024c34c: sltiu v0,v0,0x367 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000367));
/* 0024c350: bnel v0,zero,0x0024c364 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0024c354 */ set(2,sx(UINT32_C(0xffffffff)));goto L_0024c364;}}
/* 0024c358: jal 0x0028dd50 */ set(31,UINT64_C(0x0024c360));/* delay 0024c35c */ body_0028dd50();
/* 0024c360: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
L_0024c364:;
/* 0024c364: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c368: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c36c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024c370: jr ra */ {uint64_t target=cpu(31);/* delay 0024c374 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0024c3c8(void){
uint64_t incoming=cpu(31);
/* 0024c3c8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0024c3cc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c3d0: jal 0x002469a0 */ set(31,UINT64_C(0x0024c3d8));/* delay 0024c3d4 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002469a0),UINT32_C(0x0024c3d0));
/* 0024c3d8: jal 0x0024a258 */ set(31,UINT64_C(0x0024c3e0));/* delay 0024c3dc */ sw(ea(2,(int32_t)UINT32_C(0x000000c8)),(uint32_t)cpu(0));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x0024a258),UINT32_C(0x0024c3d8));
/* 0024c3e0: move a0,zero */ set(4,cpu(0));
/* 0024c3e4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c3e8: j 0x0024cbb8 */ /* delay 0024c3ec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0024cbb8();return;
}
static void body_0024cbb8(void){
uint64_t incoming=cpu(31);
/* 0024cbb8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0024cbbc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024cbc0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024cbc4: j 0x00136628 */ /* delay 0024cbc8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00136628();return;
}
static void body_0028dd50(void){
uint64_t incoming=cpu(31);
/* 0028dd50: lw v0,-0x2c40(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd3c0)));
/* 0028dd54: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0028dd58: jr ra */ {uint64_t target=cpu(31);/* delay 0028dd5c */ sw(ea(28,(int32_t)UINT32_C(0xffffd3c0)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_0028dda8(void){
uint64_t incoming=cpu(31);
/* 0028dda8: lw a0,-0x2c4c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd3b4)));
/* 0028ddac: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0028ddb0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028ddb4: jal 0x002c2070 */ set(31,UINT64_C(0x0028ddbc));/* delay 0028ddb8 */ nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002c2070),UINT32_C(0x0028ddb4));
/* 0028ddbc: lw a0,-0x2c44(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd3bc)));
/* 0028ddc0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028ddc4: j 0x002c2070 */ /* delay 0028ddc8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002c2070),UINT32_C(0x0028ddc4));return;
}
static void body_002969a0(void){
uint64_t incoming=cpu(31);
/* 002969a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002969a4: move a1,zero */ set(5,cpu(0));
/* 002969a8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002969ac: move a2,zero */ set(6,cpu(0));
/* 002969b0: move a3,zero */ set(7,cpu(0));
/* 002969b4: move t0,zero */ set(8,cpu(0));
/* 002969b8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002969bc: j 0x002968f8 */ /* delay 002969c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002968f8),UINT32_C(0x002969bc));return;
}
static void body_00297890(void){
uint64_t incoming=cpu(31);
/* 00297890: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00297894: move a1,zero */ set(5,cpu(0));
/* 00297898: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029789c: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 002978a0: addiu s0,s0,0x5618 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00005618)));
/* 002978a4: li a2,0x40 */ set(6,sx(UINT32_C(0x00000040)));
/* 002978a8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002978ac: jal 0x002d4558 */ set(31,UINT64_C(0x002978b4));/* delay 002978b0 */ set(4,cpu(16));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002d4558),UINT32_C(0x002978ac));
/* 002978b4: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 002978b8: sb v1,0x7(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000007)),(uint8_t)cpu(3));
/* 002978bc: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 002978c0: move a2,zero */ set(6,cpu(0));
/* 002978c4: jal 0x002a8080 */ set(31,UINT64_C(0x002978cc));/* delay 002978c8 */ set(4,sx(UINT32_C(0x00000001)));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a8080),UINT32_C(0x002978c4));
/* 002978cc: lui a0,0x4 */ set(4,sx(UINT32_C(0x00040000)));
/* 002978d0: jal 0x002a9038 */ set(31,UINT64_C(0x002978d8));/* delay 002978d4 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a9038),UINT32_C(0x002978d0));
/* 002978d8: jal 0x002a9688 */ set(31,UINT64_C(0x002978e0));/* delay 002978dc */ set(4,cpu(2));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x002a9688),UINT32_C(0x002978d8));
/* 002978e0: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 002978e4: sw v0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 002978e8: lui t0,0x29 */ set(8,sx(UINT32_C(0x00290000)));
/* 002978ec: addiu a0,a0,0x1650 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00001650)));
/* 002978f0: addiu t0,t0,0x7870 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00007870)));
/* 002978f4: li a1,0x384 */ set(5,sx(UINT32_C(0x00000384)));
/* 002978f8: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 002978fc: move a3,zero */ set(7,cpu(0));
/* 00297900: move t1,zero */ set(9,cpu(0));
/* 00297904: jal 0x001015b0 */ set(31,UINT64_C(0x0029790c));/* delay 00297908 */ set(10,cpu(0));nocturneBattleRewardLifecycleNativeExternal(UINT32_C(0x001015b0),UINT32_C(0x00297904));
/* 0029790c: lui v1,0x29 */ set(3,sx(UINT32_C(0x00290000)));
/* 00297910: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297914: addiu v1,v1,0x76c0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000076c0)));
/* 00297918: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0029791c: sw v1,-0x2798(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd868)),(uint32_t)cpu(3));
/* 00297920: jr ra */ {uint64_t target=cpu(31);/* delay 00297924 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleRewardLifecycleNativeBody(uint32_t entry){switch(entry){
case UINT32_C(0x00127368):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00127368();return 1u;case UINT32_C(0x00127378):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00127378();return 1u;case UINT32_C(0x00127510):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00127510();return 1u;case UINT32_C(0x00127580):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00127580();return 1u;case UINT32_C(0x00128408):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00128408();return 1u;case UINT32_C(0x00136628):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00136628();return 1u;case UINT32_C(0x001e1770):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001e1770();return 1u;case UINT32_C(0x0024bf40):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024bf40();return 1u;case UINT32_C(0x0024c1d0):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024c1d0();return 1u;case UINT32_C(0x0024c3c8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024c3c8();return 1u;case UINT32_C(0x0024cbb8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024cbb8();return 1u;case UINT32_C(0x0028dd50):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0028dd50();return 1u;case UINT32_C(0x0028dda8):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0028dda8();return 1u;case UINT32_C(0x002969a0):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002969a0();return 1u;case UINT32_C(0x00297890):if(nocturneBattleRewardLifecycleNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00297890();return 1u;
default:return 0u;}}
void ps2BattleRewardLifecycleNative_00127368(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_00127368();}
uint64_t ps2BattleRewardLifecycleNative_00127378(void){body_00127378();return cpu(2);}
void ps2BattleRewardLifecycleNative_00127510(void){body_00127510();}
uint64_t ps2BattleRewardLifecycleNative_00127580(void){body_00127580();return cpu(2);}
uint64_t ps2BattleRewardLifecycleNative_00128408(uint64_t a0,uint64_t a1,uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_00128408();return cpu(2);}
void ps2BattleRewardLifecycleNative_00136628(uint64_t a0){set(4,a0);body_00136628();}
void ps2BattleRewardLifecycleNative_001E1770(void){body_001e1770();}
void ps2BattleRewardLifecycleNative_0024BF40(void){body_0024bf40();}
uint64_t ps2BattleRewardLifecycleNative_0024C1D0(uint64_t a0){set(4,a0);body_0024c1d0();return cpu(2);}
uint64_t ps2BattleRewardLifecycleNative_0024C3C8(uint64_t a0){set(4,a0);body_0024c3c8();return cpu(2);}
void ps2BattleRewardLifecycleNative_0024CBB8(uint64_t a0){set(4,a0);body_0024cbb8();}
void ps2BattleRewardLifecycleNative_0028DD50(void){body_0028dd50();}
void ps2BattleRewardLifecycleNative_0028DDA8(void){body_0028dda8();}
uint64_t ps2BattleRewardLifecycleNative_002969A0(uint64_t a0){set(4,a0);body_002969a0();return cpu(2);}
void ps2BattleRewardLifecycleNative_00297890(void){body_00297890();}
