/* Complete11 original reward/queue owners and5 existing native variants; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_reward_levelup_support.h"

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











#include "ee_fpu_sqrt.h"
#include "ee_vu_rotation.h"









static void body_0024a060(void);
static void body_0024a258(void);
static void body_0024a298(void);
static void body_0024ae70(void);
static void body_0024afa0(void);
static void body_0024be88(void);
static void body_0024bff0(void);
static void body_0024c060(void);
static void body_0024c378(void);
static void body_0024c3f0(void);
static void body_002a8080(void);
static void body_002aad88(void);
static void body_002aaf20(void);
static void body_002ab8f0(void);
static void body_002ac760(void);
static void body_002ac7b0(void);
static void body_0024a060(void){
uint64_t incoming=cpu(31);
/* 0024a060: lw a0,-0x21a0(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde60)));
/* 0024a064: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0024a068: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024a06c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024a070: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024a074: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024a078: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a07c: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024a080: jal 0x002abe08 */ set(31,UINT64_C(0x0024a088));/* delay 0024a084 */ set(18,sx(UINT32_C(0x00000003)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002abe08),UINT32_C(0x0024a080));
/* 0024a088: lw a0,-0x219c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde64)));
/* 0024a08c: jal 0x002abe08 */ set(31,UINT64_C(0x0024a094));/* delay 0024a090 */ sw(ea(28,(int32_t)UINT32_C(0xffffcf94)),(uint32_t)cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002abe08),UINT32_C(0x0024a08c));
/* 0024a094: lw a0,-0x2198(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde68)));
/* 0024a098: jal 0x002abe08 */ set(31,UINT64_C(0x0024a0a0));/* delay 0024a09c */ sw(ea(28,(int32_t)UINT32_C(0xffffcf98)),(uint32_t)cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002abe08),UINT32_C(0x0024a098));
/* 0024a0a0: sw zero,-0x30a0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf60)),(uint32_t)cpu(0));
/* 0024a0a4: sw v0,-0x3064(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf9c)),(uint32_t)cpu(2));
/* 0024a0a8: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 0024a0ac: sw zero,-0x309c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf64)),(uint32_t)cpu(0));
/* 0024a0b0: addiu v0,v0,0x4e80 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00004e80)));
/* 0024a0b4: sw zero,-0x3098(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf68)),(uint32_t)cpu(0));
L_0024a0b8:;
/* 0024a0b8: addiu s2,s2,-0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));
/* 0024a0bc: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0024a0c0: sw zero,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 0024a0c4: sw zero,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 0024a0c8: sw zero,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 0024a0cc: sw zero,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 0024a0d0: sw zero,0x14(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 0024a0d4: sw zero,0x18(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 0024a0d8: sw zero,0x1c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 0024a0dc: sw zero,0x20(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 0024a0e0: sw zero,0x24(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 0024a0e4: sw zero,0x28(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 0024a0e8: bgez s2,0x0024a0b8 */ {int taken=((int64_t)cpu(18)>=0);/* delay 0024a0ec */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000034)));if(taken){goto L_0024a0b8;}}
/* 0024a0f0: lw a3,-0x5750(gp) */ lw(7,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024a0f4: move s2,zero */ set(18,cpu(0));
/* 0024a0f8: move a1,a3 */ set(5,cpu(7));
/* 0024a0fc: lw v0,0x1924(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00001924)));
/* 0024a100: blez v0,0x0024a20c */ {int taken=((int64_t)cpu(2)<=0);/* delay 0024a104 */ set(19,cpu(0));if(taken){goto L_0024a20c;}}
/* 0024a108: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 0024a10c: li s1,0x2d */ set(17,sx(UINT32_C(0x0000002d)));
/* 0024a110: addiu v0,v0,0x4e80 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00004e80)));
/* 0024a114: addiu s0,v0,0x30 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0x00000030)));
/* 0024a118: addiu a0,a1,0x4 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000004)));
/* 0024a11c: nop  */ 
L_0024a120:;
/* 0024a120: addu v1,s3,a0 */ set(3,sx((uint32_t)cpu(19)+(uint32_t)cpu(4)));
/* 0024a124: lbu t2,0x1910(v1) */ set(10,byte(ea(3,(int32_t)UINT32_C(0x00001910))));
/* 0024a128: sll v0,t2,0x4 */ set(2,sx((uint32_t)cpu(10)<<4));
/* 0024a12c: subu v0,v0,t2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(10)));
/* 0024a130: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024a134: subu v0,v0,t2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(10)));
/* 0024a138: sll a2,v0,0x2 */ set(6,sx((uint32_t)cpu(2)<<2));
/* 0024a13c: addu v1,a2,a0 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(4)));
/* 0024a140: lw v0,0xa50(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000a50)));
/* 0024a144: andi v1,v0,0x2 */ set(3,cpu(2)&UINT32_C(0x00000002));
/* 0024a148: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0024a14c: beq v0,zero,0x0024a1f8 */ {int taken=(cpu(2)==cpu(0));/* delay 0024a150 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));if(taken){goto L_0024a1f8;}}
/* 0024a154: beq v1,zero,0x0024a1f8 */ {int taken=(cpu(3)==cpu(0));/* delay 0024a158 */ set(8,sx(UINT32_C(0x000000c0)));if(taken){goto L_0024a1f8;}}
/* 0024a15c: addiu v1,a2,0xa60 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0x00000a60)));
/* 0024a160: addu a2,a1,a2 */ set(6,sx((uint32_t)cpu(5)+(uint32_t)cpu(6)));
/* 0024a164: li s4,0x1 */ set(20,sx(UINT32_C(0x00000001)));
/* 0024a168: addu t1,a1,v1 */ set(9,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 0024a16c: lw a1,-0x3088(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffcf78)));
/* 0024a170: addu v1,a0,v1 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 0024a174: sw s4,-0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffffd0)),(uint32_t)cpu(20));
/* 0024a178: addiu a2,a2,0xa54 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000a54)));
/* 0024a17c: lhu a3,0x8(t1) */ set(7,half(ea(9,(int32_t)UINT32_C(0x00000008))));
/* 0024a180: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0024a184: move a0,t2 */ set(4,cpu(10));
/* 0024a188: sw a2,-0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffffe4)),(uint32_t)cpu(6));
/* 0024a18c: sw v0,-0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffffd4)),(uint32_t)cpu(2));
/* 0024a190: sw a3,-0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffffd8)),(uint32_t)cpu(7));
/* 0024a194: sw t0,-0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0xfffffff4)),(uint32_t)cpu(8));
/* 0024a198: sw zero,-0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffffdc)),(uint32_t)cpu(0));
/* 0024a19c: sw t2,-0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffffe0)),(uint32_t)cpu(10));
/* 0024a1a0: sw zero,-0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffffe8)),(uint32_t)cpu(0));
/* 0024a1a4: sw zero,-0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffffec)),(uint32_t)cpu(0));
/* 0024a1a8: jal 0x0024bff0 */ set(31,UINT64_C(0x0024a1b0));/* delay 0024a1ac */ sw(ea(16,(int32_t)UINT32_C(0xfffffff0)),(uint32_t)cpu(0));body_0024bff0();
/* 0024a1b0: div v0,s1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(17),1,0);
/* 0024a1b4: sw v0,-0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0xfffffffc)),(uint32_t)cpu(2));
/* 0024a1b8: beql s1,zero,0x0024a1c0 */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 0024a1bc */ nocturneBattleRewardLevelupNativeTrap(7u,UINT32_C(0x0024a1bc));goto L_0024a1c0;}}
L_0024a1c0:;
/* 0024a1c0: mflo v1 */ set(3,nocturneEffectHostLo());
/* 0024a1c4: mfhi a0 */ set(4,nocturneEffectHostHi());
/* 0024a1c8: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 0024a1cc: blez a0,0x0024a1d8 */ {int taken=((int64_t)cpu(4)<=0);/* delay 0024a1d0 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));if(taken){goto L_0024a1d8;}}
/* 0024a1d4: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_0024a1d8:;
/* 0024a1d8: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0024a1dc: blezl v0,0x0024a1e4 */ {int taken=((int64_t)cpu(2)<=0);if(taken){/* delay 0024a1e0 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));goto L_0024a1e4;}}
L_0024a1e4:;
/* 0024a1e4: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 0024a1e8: slti v0,s2,0x4 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0024a1ec: beq v0,zero,0x0024a20c */ {int taken=(cpu(2)==cpu(0));/* delay 0024a1f0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000034)));if(taken){goto L_0024a20c;}}
/* 0024a1f4: lw a3,-0x5750(gp) */ lw(7,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
L_0024a1f8:;
/* 0024a1f8: move a1,a3 */ set(5,cpu(7));
/* 0024a1fc: lw v0,0x1924(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00001924)));
/* 0024a200: slt v0,s3,v0 */ set(2,(int64_t)cpu(19)<(int64_t)cpu(2));
/* 0024a204: bne v0,zero,0x0024a120 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024a208 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000004)));if(taken){goto L_0024a120;}}
L_0024a20c:;
/* 0024a20c: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 0024a210: li t2,0x3f */ set(10,sx(UINT32_C(0x0000003f)));
/* 0024a214: addiu v0,v0,0x4f50 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00004f50)));
L_0024a218:;
/* 0024a218: addiu t2,t2,-0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0xffffffff)));
/* 0024a21c: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0024a220: sw zero,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 0024a224: sw zero,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 0024a228: sw zero,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 0024a22c: bgez t2,0x0024a218 */ {int taken=((int64_t)cpu(10)>=0);/* delay 0024a230 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));if(taken){goto L_0024a218;}}
/* 0024a234: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024a238: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024a23c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024a240: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024a244: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024a248: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024a24c: jr ra */ {uint64_t target=cpu(31);/* delay 0024a250 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_0024a258(void){
uint64_t incoming=cpu(31);
/* 0024a258: lw a0,-0x306c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024a25c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0024a260: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024a264: jal 0x002ab8f0 */ set(31,UINT64_C(0x0024a26c));/* delay 0024a268 */ body_002ab8f0();
/* 0024a26c: jal 0x002ab8f0 */ set(31,UINT64_C(0x0024a274));/* delay 0024a270 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcf98)));body_002ab8f0();
/* 0024a274: jal 0x002ab8f0 */ set(31,UINT64_C(0x0024a27c));/* delay 0024a278 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcf9c)));body_002ab8f0();
/* 0024a27c: sw zero,-0x306c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf94)),(uint32_t)cpu(0));
/* 0024a280: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024a284: sw zero,-0x3068(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf98)),(uint32_t)cpu(0));
/* 0024a288: sw zero,-0x3064(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf9c)),(uint32_t)cpu(0));
/* 0024a28c: jr ra */ {uint64_t target=cpu(31);/* delay 0024a290 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0024a298(void){
uint64_t incoming=cpu(31);
/* 0024a298: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 0024a29c: move a2,zero */ set(6,cpu(0));
/* 0024a2a0: addiu v1,v0,0x4f50 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00004f50)));
/* 0024a2a4: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024a2a8: li a3,0x14 */ set(7,sx(UINT32_C(0x00000014)));
/* 0024a2ac: nop  */ 
L_0024a2b0:;
/* 0024a2b0: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0024a2b4: bnel v0,zero,0x0024a2d0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0024a2b8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));goto L_0024a2d0;}}
/* 0024a2bc: sw a3,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
/* 0024a2c0: sw t0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(8));
/* 0024a2c4: sw a0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 0024a2c8: jr ra */ {uint64_t target=cpu(31);/* delay 0024a2cc */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
L_0024a2d0:;
/* 0024a2d0: slti v0,a2,0x40 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000040));
/* 0024a2d4: bne v0,zero,0x0024a2b0 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024a2d8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));if(taken){goto L_0024a2b0;}}
/* 0024a2dc: jr ra */ {uint64_t target=cpu(31);/* delay 0024a2e0 */ checkReturn(target,incoming);return;}
}
static void body_0024ae70(void){
uint64_t incoming=cpu(31);
/* 0024ae70: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 0024ae74: li v0,0x384 */ set(2,sx(UINT32_C(0x00000384)));
/* 0024ae78: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 0024ae7c: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0024ae80: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024ae84: addiu s7,v1,0x4e80 */ set(23,sx((uint32_t)cpu(3)+UINT32_C(0x00004e80)));
/* 0024ae88: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024ae8c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024ae90: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0024ae94: sw v0,-0x30a0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf60)),(uint32_t)cpu(2));
/* 0024ae98: sw zero,-0x308c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf74)),(uint32_t)cpu(0));
/* 0024ae9c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024aea0: addiu s3,s7,0x4 */ set(19,sx((uint32_t)cpu(23)+UINT32_C(0x00000004)));
/* 0024aea4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024aea8: move s4,zero */ set(20,cpu(0));
/* 0024aeac: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024aeb0: li s5,0x3 */ set(21,sx(UINT32_C(0x00000003)));
/* 0024aeb4: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024aeb8: li s6,0xe3 */ set(22,sx(UINT32_C(0x000000e3)));
/* 0024aebc: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0024aec0: li s8,0x1 */ set(30,sx(UINT32_C(0x00000001)));
/* 0024aec4: nop  */ 
L_0024aec8:;
/* 0024aec8: lw v0,-0x4(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0xfffffffc)));
/* 0024aecc: beq v0,zero,0x0024af38 */ {int taken=(cpu(2)==cpu(0));/* delay 0024aed0 */ set(18,sx((uint32_t)cpu(23)+UINT32_C(0x0000000c)));if(taken){goto L_0024af38;}}
/* 0024aed4: lbu s0,0xc(s3) */ set(16,byte(ea(19,(int32_t)UINT32_C(0x0000000c))));
/* 0024aed8: lw a1,0x0(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0024aedc: jal 0x0021f838 */ set(31,UINT64_C(0x0024aee4));/* delay 0024aee0 */ set(4,cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0021f838),UINT32_C(0x0024aedc));
/* 0024aee4: lw a1,0x10(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 0024aee8: addu a2,s4,s2 */ set(6,sx((uint32_t)cpu(20)+(uint32_t)cpu(18)));
/* 0024aeec: move s1,v0 */ set(17,cpu(2));
/* 0024aef0: lw v1,0x10(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 0024aef4: move a0,s0 */ set(4,cpu(16));
/* 0024aef8: lw v0,0x20(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000020)));
/* 0024aefc: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0024af00: move a1,v1 */ set(5,cpu(3));
/* 0024af04: jal 0x0021f838 */ set(31,UINT64_C(0x0024af0c));/* delay 0024af08 */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0021f838),UINT32_C(0x0024af04));
/* 0024af0c: addu v1,s4,s2 */ set(3,sx((uint32_t)cpu(20)+(uint32_t)cpu(18)));
/* 0024af10: slt s1,s1,v0 */ set(17,(int64_t)cpu(17)<(int64_t)cpu(2));
/* 0024af14: move a1,s6 */ set(5,cpu(22));
/* 0024af18: li a0,0x13d */ set(4,sx(UINT32_C(0x0000013d)));
/* 0024af1c: beq s1,zero,0x0024af38 */ {int taken=(cpu(17)==cpu(0));/* delay 0024af20 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_0024af38;}}
/* 0024af24: lw v0,-0x308c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf74)));
/* 0024af28: sw s8,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(30));
/* 0024af2c: ori v0,v0,0x2 */ set(2,cpu(2)|UINT32_C(0x00000002));
/* 0024af30: jal 0x0024a298 */ set(31,UINT64_C(0x0024af38));/* delay 0024af34 */ sw(ea(28,(int32_t)UINT32_C(0xffffcf74)),(uint32_t)cpu(2));body_0024a298();
L_0024af38:;
/* 0024af38: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
/* 0024af3c: addiu s6,s6,0x28 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000028)));
/* 0024af40: addiu s3,s3,0x34 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000034)));
/* 0024af44: bgez s5,0x0024aec8 */ {int taken=((int64_t)cpu(21)>=0);/* delay 0024af48 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000034)));if(taken){goto L_0024aec8;}}
/* 0024af4c: lw v0,-0x308c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf74)));
/* 0024af50: andi v0,v0,0x2 */ set(2,cpu(2)&UINT32_C(0x00000002));
/* 0024af54: beq v0,zero,0x0024af68 */ {int taken=(cpu(2)==cpu(0));/* delay 0024af58 */ set(4,sx(UINT32_C(0x00000011)));if(taken){goto L_0024af68;}}
/* 0024af5c: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 0024af60: jal 0x002c18d8 */ set(31,UINT64_C(0x0024af68));/* delay 0024af64 */ set(6,sx(UINT32_C(0x0000003f)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002c18d8),UINT32_C(0x0024af60));
L_0024af68:;
/* 0024af68: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024af6c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024af70: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024af74: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024af78: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024af7c: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024af80: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024af84: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0024af88: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0024af8c: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0024af90: sw zero,-0x308c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf74)),(uint32_t)cpu(0));
/* 0024af94: jr ra */ {uint64_t target=cpu(31);/* delay 0024af98 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_0024afa0(void){
uint64_t incoming=cpu(31);
/* 0024afa0: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 0024afa4: move t0,zero */ set(8,cpu(0));
/* 0024afa8: addiu a2,v0,0x4e80 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00004e80)));
/* 0024afac: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024afb0: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 0024afb4: nop  */ 
L_0024afb8:;
/* 0024afb8: lw v0,0x0(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 0024afbc: beq v0,zero,0x0024afe0 */ {int taken=(cpu(2)==cpu(0));/* delay 0024afc0 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));if(taken){goto L_0024afe0;}}
/* 0024afc4: lw a0,0x14(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x00000014)));
/* 0024afc8: lw a1,0x2c(a2) */ lw(5,ea(6,(int32_t)UINT32_C(0x0000002c)));
/* 0024afcc: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0024afd0: lw v1,0x4(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 0024afd4: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0024afd8: sltu v1,v1,v0 */ set(3,cpu(3)<cpu(2));
/* 0024afdc: movn t0,t1,v1 */ if(cpu(3)!=0){set(8,cpu(9));}
L_0024afe0:;
/* 0024afe0: bgez a3,0x0024afb8 */ {int taken=((int64_t)cpu(7)>=0);/* delay 0024afe4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000034)));if(taken){goto L_0024afb8;}}
/* 0024afe8: bne t0,zero,0x0024b004 */ {int taken=(cpu(8)!=cpu(0));/* delay 0024afec */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf6c)));if(taken){goto L_0024b004;}}
/* 0024aff0: slti v0,v1,0x3c */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000003c));
/* 0024aff4: beq v0,zero,0x0024b004 */ {int taken=(cpu(2)==cpu(0));/* delay 0024aff8 */ if(taken){goto L_0024b004;}}
/* 0024affc: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0024b000: sw v1,-0x3094(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf6c)),(uint32_t)cpu(3));
L_0024b004:;
/* 0024b004: jr ra */ {uint64_t target=cpu(31);/* delay 0024b008 */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
static void body_0024be88(void){
uint64_t incoming=cpu(31);
/* 0024be88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0024be8c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024be90: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024be94: jal 0x002469a0 */ set(31,UINT64_C(0x0024be9c));/* delay 0024be98 */ nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002469a0),UINT32_C(0x0024be94));
/* 0024be9c: move s0,v0 */ set(16,cpu(2));
/* 0024bea0: lw a0,0x110(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000110)));
/* 0024bea4: beql a0,zero,0x0024bebc */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0024bea8 */ lw(4,ea(16,(int32_t)UINT32_C(0x000000fc)));goto L_0024bebc;}}
/* 0024beac: jal 0x00101738 */ set(31,UINT64_C(0x0024beb4));/* delay 0024beb0 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00101738),UINT32_C(0x0024beac));
/* 0024beb4: sw zero,0x110(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000110)),(uint32_t)cpu(0));
/* 0024beb8: lw a0,0xfc(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000fc)));
L_0024bebc:;
/* 0024bebc: beql a0,zero,0x0024bed4 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0024bec0 */ lw(4,ea(16,(int32_t)UINT32_C(0x000000f0)));goto L_0024bed4;}}
/* 0024bec4: jal 0x00101738 */ set(31,UINT64_C(0x0024becc));/* delay 0024bec8 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00101738),UINT32_C(0x0024bec4));
/* 0024becc: sw zero,0xfc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000fc)),(uint32_t)cpu(0));
/* 0024bed0: lw a0,0xf0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000f0)));
L_0024bed4:;
/* 0024bed4: beql a0,zero,0x0024beec */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0024bed8 */ lw(4,ea(16,(int32_t)UINT32_C(0x000000d0)));goto L_0024beec;}}
/* 0024bedc: jal 0x00101738 */ set(31,UINT64_C(0x0024bee4));/* delay 0024bee0 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00101738),UINT32_C(0x0024bedc));
/* 0024bee4: sw zero,0xf0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000f0)),(uint32_t)cpu(0));
/* 0024bee8: lw a0,0xd0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000d0)));
L_0024beec:;
/* 0024beec: beql a0,zero,0x0024bf04 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0024bef0 */ lw(4,ea(16,(int32_t)UINT32_C(0x0000010c)));goto L_0024bf04;}}
/* 0024bef4: jal 0x00101738 */ set(31,UINT64_C(0x0024befc));/* delay 0024bef8 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00101738),UINT32_C(0x0024bef4));
/* 0024befc: sw zero,0xd0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000d0)),(uint32_t)cpu(0));
/* 0024bf00: lw a0,0x10c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000010c)));
L_0024bf04:;
/* 0024bf04: beql a0,zero,0x0024bf1c */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0024bf08 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000108)));goto L_0024bf1c;}}
/* 0024bf0c: jal 0x00101738 */ set(31,UINT64_C(0x0024bf14));/* delay 0024bf10 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00101738),UINT32_C(0x0024bf0c));
/* 0024bf14: sw zero,0x10c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000010c)),(uint32_t)cpu(0));
/* 0024bf18: lw a0,0x108(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000108)));
L_0024bf1c:;
/* 0024bf1c: beql a0,zero,0x0024bf34 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0024bf20 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0024bf34;}}
/* 0024bf24: jal 0x00101738 */ set(31,UINT64_C(0x0024bf2c));/* delay 0024bf28 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00101738),UINT32_C(0x0024bf24));
/* 0024bf2c: sw zero,0x108(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000108)),(uint32_t)cpu(0));
/* 0024bf30: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0024bf34:;
/* 0024bf34: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024bf38: jr ra */ {uint64_t target=cpu(31);/* delay 0024bf3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0024bff0(void){
uint64_t incoming=cpu(31);
/* 0024bff0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024bff4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024bff8: move s0,a0 */ set(16,cpu(4));
/* 0024bffc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c000: move s1,a1 */ set(17,cpu(5));
/* 0024c004: andi a0,s0,0xff */ set(4,cpu(16)&UINT32_C(0x000000ff));
/* 0024c008: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024c00c: jal 0x0021f898 */ set(31,UINT64_C(0x0024c014));/* delay 0024c010 */ set(5,sx(UINT32_C(0x00000100)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0021f898),UINT32_C(0x0024c00c));
/* 0024c014: sll v1,s0,0x4 */ set(3,sx((uint32_t)cpu(16)<<4));
/* 0024c018: lw a1,-0x5750(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024c01c: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 0024c020: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 0024c024: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0024c028: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024c02c: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 0024c030: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c034: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0024c038: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0024c03c: lw a0,0xa64(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000a64)));
/* 0024c040: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0024c044: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 0024c048: movn v0,zero,v1 */ if(cpu(3)!=0){set(2,cpu(0));}
/* 0024c04c: slt a0,s1,v0 */ set(4,(int64_t)cpu(17)<(int64_t)cpu(2));
/* 0024c050: movn v0,s1,a0 */ if(cpu(4)!=0){set(2,cpu(17));}
/* 0024c054: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c058: jr ra */ {uint64_t target=cpu(31);/* delay 0024c05c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0024c060(void){
uint64_t incoming=cpu(31);
/* 0024c060: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 0024c064: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c068: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c06c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024c070: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024c074: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024c078: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024c07c: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024c080: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0024c084: jal 0x002469a0 */ set(31,UINT64_C(0x0024c08c));/* delay 0024c088 */ set(18,cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002469a0),UINT32_C(0x0024c084));
/* 0024c08c: move s3,v0 */ set(19,cpu(2));
/* 0024c090: addiu s1,s3,0x8 */ set(17,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 0024c094: addiu s0,s3,0xc */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0x0000000c)));
/* 0024c098: addiu v1,s2,0x90 */ set(3,sx((uint32_t)cpu(18)+UINT32_C(0x00000090)));
/* 0024c09c: nop  */ 
L_0024c0a0:;
/* 0024c0a0: addu a1,s0,v1 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 0024c0a4: addu v1,s1,v1 */ set(3,sx((uint32_t)cpu(17)+(uint32_t)cpu(3)));
/* 0024c0a8: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 0024c0ac: beq v0,zero,0x0024c0cc */ {int taken=(cpu(2)==cpu(0));/* delay 0024c0b0 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));if(taken){goto L_0024c0cc;}}
/* 0024c0b4: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 0024c0b8: beql v0,zero,0x0024c0d0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024c0bc */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000004));goto L_0024c0d0;}}
/* 0024c0c0: lbu a0,0x0(v1) */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 0024c0c4: jal 0x002442e0 */ set(31,UINT64_C(0x0024c0cc));/* delay 0024c0c8 */ set(5,cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002442e0),UINT32_C(0x0024c0c4));
L_0024c0cc:;
/* 0024c0cc: slti v0,s2,0x4 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000004));
L_0024c0d0:;
/* 0024c0d0: bne v0,zero,0x0024c0a0 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c0d4 */ set(3,sx((uint32_t)cpu(18)+UINT32_C(0x00000090)));if(taken){goto L_0024c0a0;}}
/* 0024c0d8: move a0,s3 */ set(4,cpu(19));
/* 0024c0dc: jal 0x0026a870 */ set(31,UINT64_C(0x0024c0e4));/* delay 0024c0e0 */ set(18,cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0026a870),UINT32_C(0x0024c0dc));
/* 0024c0e4: li s6,0x800 */ set(22,sx(UINT32_C(0x00000800)));
/* 0024c0e8: move a0,v0 */ set(4,cpu(2));
/* 0024c0ec: jal 0x00244238 */ set(31,UINT64_C(0x0024c0f4));/* delay 0024c0f0 */ set(20,cpu(0));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00244238),UINT32_C(0x0024c0ec));
/* 0024c0f4: lui v0,0x3e */ set(2,sx(UINT32_C(0x003e0000)));
/* 0024c0f8: addiu s5,v0,-0x3e60 */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0xffffc1a0)));
/* 0024c0fc: nop  */ 
L_0024c100:;
/* 0024c100: jal 0x0026a840 */ set(31,UINT64_C(0x0024c108));/* delay 0024c104 */ set(4,cpu(19));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0026a840),UINT32_C(0x0024c100));
/* 0024c108: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024c10c: move s1,v0 */ set(17,cpu(2));
/* 0024c110: addu v1,v1,s4 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(20)));
/* 0024c114: addiu s0,v1,0xa54 */ set(16,sx((uint32_t)cpu(3)+UINT32_C(0x00000a54)));
/* 0024c118: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0024c11c: andi v1,v0,0x2 */ set(3,cpu(2)&UINT32_C(0x00000002));
/* 0024c120: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0024c124: beq v0,zero,0x0024c19c */ {int taken=(cpu(2)==cpu(0));/* delay 0024c128 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x000000ec)));if(taken){goto L_0024c19c;}}
/* 0024c12c: bnel v1,zero,0x0024c16c */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0024c130 */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000e))));goto L_0024c16c;}}
/* 0024c134: move a0,s0 */ set(4,cpu(16));
/* 0024c138: jal 0x00243f40 */ set(31,UINT64_C(0x0024c140));/* delay 0024c13c */ set(5,sx(UINT32_C(0x00000162)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00243f40),UINT32_C(0x0024c138));
/* 0024c140: beql v0,zero,0x0024c1a0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024c144 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));goto L_0024c1a0;}}
/* 0024c148: blezl s1,0x0024c16c */ {int taken=((int64_t)cpu(17)<=0);if(taken){/* delay 0024c14c */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000e))));goto L_0024c16c;}}
/* 0024c150: lh v0,0x210(s5) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(21,(int32_t)UINT32_C(0x00000210))));
/* 0024c154: div s1,v0 */ nativeDivide((uint32_t)cpu(17),(uint32_t)cpu(2),1,0);
/* 0024c158: beql v0,zero,0x0024c160 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024c15c */ nocturneBattleRewardLevelupNativeTrap(7u,UINT32_C(0x0024c15c));goto L_0024c160;}}
L_0024c160:;
/* 0024c160: mflo v1 */ set(3,nocturneEffectHostLo());
/* 0024c164: move s1,v1 */ set(17,cpu(3));
/* 0024c168: lhu v0,0xe(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000e))));
L_0024c16c:;
/* 0024c16c: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 0024c170: beql v0,s6,0x0024c1a0 */ {int taken=(cpu(2)==cpu(22));if(taken){/* delay 0024c174 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));goto L_0024c1a0;}}
/* 0024c178: lhu v0,0x6(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 0024c17c: beql v0,zero,0x0024c1a0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024c180 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));goto L_0024c1a0;}}
/* 0024c184: move a1,s1 */ set(5,cpu(17));
/* 0024c188: jal 0x0024bff0 */ set(31,UINT64_C(0x0024c190));/* delay 0024c18c */ set(4,cpu(18));body_0024bff0();
/* 0024c190: move a0,s0 */ set(4,cpu(16));
/* 0024c194: jal 0x002452b8 */ set(31,UINT64_C(0x0024c19c));/* delay 0024c198 */ set(5,cpu(2));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002452b8),UINT32_C(0x0024c194));
L_0024c19c:;
/* 0024c19c: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
L_0024c1a0:;
/* 0024c1a0: slti v0,s2,0x10 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0024c1a4: bne v0,zero,0x0024c100 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024c1a8 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));if(taken){goto L_0024c100;}}
/* 0024c1ac: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c1b0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c1b4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024c1b8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024c1bc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024c1c0: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024c1c4: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024c1c8: jr ra */ {uint64_t target=cpu(31);/* delay 0024c1cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_0024c378(void){
uint64_t incoming=cpu(31);
/* 0024c378: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0024c37c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c380: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c384: jal 0x002469a0 */ set(31,UINT64_C(0x0024c38c));/* delay 0024c388 */ nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002469a0),UINT32_C(0x0024c384));
/* 0024c38c: jal 0x0024be88 */ set(31,UINT64_C(0x0024c394));/* delay 0024c390 */ set(16,cpu(2));body_0024be88();
/* 0024c394: jal 0x0026a840 */ set(31,UINT64_C(0x0024c39c));/* delay 0024c398 */ set(4,cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x0026a840),UINT32_C(0x0024c394));
/* 0024c39c: jal 0x0024a060 */ set(31,UINT64_C(0x0024c3a4));/* delay 0024c3a0 */ sw(ea(28,(int32_t)UINT32_C(0xffffcf78)),(uint32_t)cpu(2));body_0024a060();
/* 0024c3a4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c3a8: lui v0,0x25 */ set(2,sx(UINT32_C(0x00250000)));
/* 0024c3ac: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c3b0: addiu v0,v0,-0x3e30 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffc1d0)));
/* 0024c3b4: sw zero,-0x3074(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf8c)),(uint32_t)cpu(0));
/* 0024c3b8: sw zero,-0x3094(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf6c)),(uint32_t)cpu(0));
/* 0024c3bc: sw zero,-0x3090(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf70)),(uint32_t)cpu(0));
/* 0024c3c0: jr ra */ {uint64_t target=cpu(31);/* delay 0024c3c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0024c3f0(void){
uint64_t incoming=cpu(31);
/* 0024c3f0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024c3f4: lui v0,0x54 */ set(2,sx(UINT32_C(0x00540000)));
/* 0024c3f8: lui t0,0x25 */ set(8,sx(UINT32_C(0x00250000)));
/* 0024c3fc: lui t1,0x25 */ set(9,sx(UINT32_C(0x00250000)));
/* 0024c400: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c404: move s1,a0 */ set(17,cpu(4));
/* 0024c408: addiu t0,t0,-0x3c88 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0xffffc378)));
/* 0024c40c: addiu t1,t1,-0x3c38 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xffffc3c8)));
/* 0024c410: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 0024c414: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 0024c418: move t2,zero */ set(10,cpu(0));
/* 0024c41c: addiu a0,v0,0x3608 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00003608)));
/* 0024c420: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c424: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024c428: jal 0x001015b0 */ set(31,UINT64_C(0x0024c430));/* delay 0024c42c */ set(5,sx(UINT32_C(0x000003f9)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x001015b0),UINT32_C(0x0024c428));
/* 0024c430: move s0,v0 */ set(16,cpu(2));
/* 0024c434: lw a0,0xbc(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x000000bc)));
/* 0024c438: jal 0x00101af8 */ set(31,UINT64_C(0x0024c440));/* delay 0024c43c */ set(5,cpu(16));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x00101af8),UINT32_C(0x0024c438));
/* 0024c440: sw s0,0xc8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000c8)),(uint32_t)cpu(16));
/* 0024c444: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024c448: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024c44c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024c450: jr ra */ {uint64_t target=cpu(31);/* delay 0024c454 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002a8080(void){
uint64_t incoming=cpu(31);
/* 002a8080: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002a8084: sw a0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 002a8088: move a0,sp */ set(4,cpu(29));
/* 002a808c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a8090: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 002a8094: jal 0x002dbea0 */ set(31,UINT64_C(0x002a809c));/* delay 002a8098 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(6));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002dbea0),UINT32_C(0x002a8094));
/* 002a809c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a80a0: jr ra */ {uint64_t target=cpu(31);/* delay 002a80a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002aad88(void){
uint64_t incoming=cpu(31);
/* 002aad88: sw zero,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002aad8c: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002aad90: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002aad94: jr ra */ {uint64_t target=cpu(31);/* delay 002aad98 */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_002aaf20(void){
uint64_t incoming=cpu(31);
/* 002aaf20: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002aaf24: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002aaf28: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aaf2c: lui s0,0x58 */ set(16,sx(UINT32_C(0x00580000)));
/* 002aaf30: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 002aaf34: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aaf38: jal 0x002a8080 */ set(31,UINT64_C(0x002aaf40));/* delay 002aaf3c */ set(6,cpu(0));body_002a8080();
/* 002aaf40: addiu s0,s0,0x1018 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00001018)));
/* 002aaf44: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aaf48: move a0,s0 */ set(4,cpu(16));
/* 002aaf4c: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002aaf50: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aaf54: j 0x002aad88 */ /* delay 002aaf58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002aad88();return;
}
static void body_002ab8f0(void){
uint64_t incoming=cpu(31);
/* 002ab8f0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ab8f4: move a1,a0 */ set(5,cpu(4));
/* 002ab8f8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab8fc: addiu a0,gp,-0x20d0 */ set(4,sx((uint32_t)cpu(28)+UINT32_C(0xffffdf30)));
/* 002ab900: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab904: j 0x002ac7b0 */ /* delay 002ab908 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002ac7b0();return;
}
static void body_002ac760(void){
uint64_t incoming=cpu(31);
/* 002ac760: lw v0,-0x290c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6f4)));
/* 002ac764: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002ac768: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac76c: move s0,a0 */ set(16,cpu(4));
/* 002ac770: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac774: move s1,a1 */ set(17,cpu(5));
/* 002ac778: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac77c: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002ac780: bgez v0,0x002ac794 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002ac784 */ set(5,sx(UINT32_C(0x0000007f)));if(taken){goto L_002ac794;}}
/* 002ac788: jal 0x002a8080 */ set(31,UINT64_C(0x002ac790));/* delay 002ac78c */ set(6,cpu(0));body_002a8080();
/* 002ac790: sw v0,-0x290c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd6f4)),(uint32_t)cpu(2));
L_002ac794:;
/* 002ac794: sw s1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002ac798: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002ac79c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac7a0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac7a4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac7a8: jr ra */ {uint64_t target=cpu(31);/* delay 002ac7ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002ac7b0(void){
uint64_t incoming=cpu(31);
/* 002ac7b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002ac7b4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac7b8: move s2,a1 */ set(18,cpu(5));
/* 002ac7bc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac7c0: move s1,a0 */ set(17,cpu(4));
/* 002ac7c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac7c8: beq s2,zero,0x002ac868 */ {int taken=(cpu(18)==cpu(0));/* delay 002ac7cc */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002ac868;}}
/* 002ac7d0: jal 0x002dbee0 */ set(31,UINT64_C(0x002ac7d8));/* delay 002ac7d4 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd6f4)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002dbee0),UINT32_C(0x002ac7d0));
/* 002ac7d8: lw s0,0x4(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002ac7dc: bne s0,zero,0x002ac80c */ {int taken=(cpu(16)!=cpu(0));/* delay 002ac7e0 */ set(4,sx(UINT32_C(0x00000010)));if(taken){goto L_002ac80c;}}
/* 002ac7e4: jal 0x002a8af8 */ set(31,UINT64_C(0x002ac7ec));/* delay 002ac7e8 */ nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002ac7e4));
/* 002ac7ec: move s0,v0 */ set(16,cpu(2));
/* 002ac7f0: lw v0,-0x20c0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdf40)));
/* 002ac7f4: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002ac7f8: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002ac7fc: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002ac800: sw s0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002ac804: sw s1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 002ac808: sw s0,-0x20c0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdf40)),(uint32_t)cpu(16));
L_002ac80c:;
/* 002ac80c: lw a1,0xc(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002ac810: bne a1,zero,0x002ac830 */ {int taken=(cpu(5)!=cpu(0));/* delay 002ac814 */ lw(17,ea(16,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002ac830;}}
/* 002ac818: jal 0x002a8af8 */ set(31,UINT64_C(0x002ac820));/* delay 002ac81c */ set(4,sx(UINT32_C(0x00000100)));nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x002ac818));
/* 002ac820: li a1,0x3f */ set(5,sx(UINT32_C(0x0000003f)));
/* 002ac824: sw s1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002ac828: move s1,v0 */ set(17,cpu(2));
/* 002ac82c: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_002ac830:;
/* 002ac830: li v0,0x3f */ set(2,sx(UINT32_C(0x0000003f)));
/* 002ac834: addiu v1,a1,-0x1 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 002ac838: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 002ac83c: lw a0,-0x290c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd6f4)));
/* 002ac840: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002ac844: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ac848: addu v0,s1,v0 */ set(2,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002ac84c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac850: sw s2,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(18));
/* 002ac854: sw v1,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 002ac858: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac85c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac860: j 0x002dbec0 */ /* delay 002ac864 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleRewardLevelupNativeExternal(UINT32_C(0x002dbec0),UINT32_C(0x002ac860));return;
L_002ac868:;
/* 002ac868: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac86c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac870: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac874: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ac878: jr ra */ {uint64_t target=cpu(31);/* delay 002ac87c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleRewardLevelupSupportBody(uint32_t entry){switch(entry){
case UINT32_C(0x0024a060):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024a060();return 1u;case UINT32_C(0x0024a258):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024a258();return 1u;case UINT32_C(0x0024a298):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024a298();return 1u;case UINT32_C(0x0024ae70):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024ae70();return 1u;case UINT32_C(0x0024afa0):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024afa0();return 1u;case UINT32_C(0x0024be88):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024be88();return 1u;case UINT32_C(0x0024bff0):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024bff0();return 1u;case UINT32_C(0x0024c060):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024c060();return 1u;case UINT32_C(0x0024c378):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024c378();return 1u;case UINT32_C(0x0024c3f0):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024c3f0();return 1u;case UINT32_C(0x002a8080):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002a8080();return 1u;case UINT32_C(0x002aad88):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002aad88();return 1u;case UINT32_C(0x002aaf20):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002aaf20();return 1u;case UINT32_C(0x002ab8f0):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002ab8f0();return 1u;case UINT32_C(0x002ac760):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002ac760();return 1u;case UINT32_C(0x002ac7b0):if(nocturneBattleRewardLevelupNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002ac7b0();return 1u;
default:return 0u;}}
void ps2BattleRewardLevelupSupport_0024A060(void){body_0024a060();}
void ps2BattleRewardLevelupSupport_0024A258(void){body_0024a258();}
void ps2BattleRewardLevelupSupport_0024A298(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_0024a298();}
void ps2BattleRewardLevelupSupport_0024AE70(void){body_0024ae70();}
uint64_t ps2BattleRewardLevelupSupport_0024AFA0(void){body_0024afa0();return cpu(2);}
void ps2BattleRewardLevelupSupport_0024BE88(void){body_0024be88();}
uint64_t ps2BattleRewardLevelupSupport_0024BFF0(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_0024bff0();return cpu(2);}
void ps2BattleRewardLevelupSupport_0024C060(void){body_0024c060();}
uint64_t ps2BattleRewardLevelupSupport_0024C378(void){body_0024c378();return cpu(2);}
void ps2BattleRewardLevelupSupport_0024C3F0(uint64_t a0){set(4,a0);body_0024c3f0();}
void ps2BattleRewardLevelupSupport_002AAD88(uint64_t a0){set(4,a0);body_002aad88();}
void ps2BattleRewardLevelupSupport_002AAF20(void){body_002aaf20();}
uint64_t ps2BattleRewardLevelupSupport_002A8080(uint64_t a0,uint64_t a1,uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002a8080();return cpu(2);}
void ps2BattleRewardLevelupSupport_002AB8F0(uint64_t a0){set(4,a0);body_002ab8f0();}
void ps2BattleRewardLevelupSupport_002AC760(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_002ac760();}
void ps2BattleRewardLevelupSupport_002AC7B0(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_002ac7b0();}
