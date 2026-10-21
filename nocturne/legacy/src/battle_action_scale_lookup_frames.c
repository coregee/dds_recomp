/* Complete fixed original scale/actor/process lookup algorithms.
 * Actual shared CPU/FPR/RAM frames and original dynamic loads, no frame shim,
 * callback result input, expected-state seed or runtime instruction executor.
 */
#include "battle_action_scale_lookup_frames.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t mul(uint32_t a,uint32_t b){return EE_FPU_MUL_S(a,b);}
static float real(uint32_t bits){float value;memcpy(&value,&bits,4);return value;}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}

float ps2BattleActionScaleLookup_0016FCF0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0016fcf0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0016fcf0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0016fcf4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016fcf8: lw v0,0x8c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000008c)));
/* 0016fcfc: beq v0,zero,0x0016fd10 */ {int taken=(cpu(2)==cpu(0));/* delay 0016fd00 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0016fd10;}}
/* 0016fd04: j 0x0016e698 */ /* delay 0016fd08 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionScaleLookup_0016E698(cpu(4));return real(f[0]);
L_0016fd10:;
/* 0016fd10: j 0x0016e638 */ /* delay 0016fd14 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionScaleLookup_0016E638(cpu(4));return real(f[0]);
}
float ps2BattleActionScaleLookup_0016E698(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0016e698u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0016e698: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0016e69c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016e6a0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0016e6a4: jal 0x0016e560 */ set(31,0x0016e6acu);/* delay 0016e6a8 */ set(16,cpu(4));set(2,ps2BattleActionScaleLookup_0016E560(cpu(4)));
/* 0016e6ac: addiu v1,v0,-0x102 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xfffffefe)));
/* 0016e6b0: sltiu v0,v1,0x57 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000057));
/* 0016e6b4: beq v0,zero,0x0016e6fc */ {int taken=(cpu(2)==cpu(0));/* delay 0016e6b8 */ set(4,cpu(16));if(taken){goto L_0016e6fc;}}
/* 0016e6bc: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 0016e6c0: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 0016e6c4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0016e6c8: lw v1,0x3080(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003080)));
/* 0016e6cc: jr v1 */ {uint64_t target=cpu(3);/* delay 0016e6d0 */ switch((uint32_t)target){case 0x0016e6d8u:goto L_0016e6d8;case 0x0016e6e8u:goto L_0016e6e8;case 0x0016e6f8u:goto L_0016e6f8;default:abort();}}
L_0016e6d8:;
/* 0016e6d8: lwc1 f0,-0x7af4(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff850c)));
/* 0016e6dc: b 0x0016e710 */ /* delay 0016e6e0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0016e710;
L_0016e6e8:;
/* 0016e6e8: lui at,0x4040 */ set(1,sx(UINT32_C(0x40400000)));
/* 0016e6ec: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0016e6f0: b 0x0016e710 */ /* delay 0016e6f4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0016e710;
L_0016e6f8:;
/* 0016e6f8: move a0,s0 */ set(4,cpu(16));
L_0016e6fc:;
/* 0016e6fc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016e700: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0016e704: j 0x0016e638 */ /* delay 0016e708 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionScaleLookup_0016E638(cpu(4));return real(f[0]);
L_0016e710:;
/* 0016e710: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0016e714: jr ra */ {uint64_t target=cpu(31);/* delay 0016e718 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return real(f[0]);}
}
float ps2BattleActionScaleLookup_0016E638(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0016e638u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 0016e638: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0016e63c: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0016e640: lwc1 f1,0x54(a0) */ f[1]=word(ea(4,(int32_t)UINT32_C(0x00000054)));
/* 0016e644: lwc1 f0,0x50(a0) */ f[0]=word(ea(4,(int32_t)UINT32_C(0x00000050)));
/* 0016e648: mul.S f1,f1,f4 */ f[1]=mul(f[1],f[4]);
/* 0016e64c: lwc1 f2,0x5c(a0) */ f[2]=word(ea(4,(int32_t)UINT32_C(0x0000005c)));
/* 0016e650: lwc1 f3,-0x7afc(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffff8504)));
/* 0016e654: lui at,0x4000 */ set(1,sx(UINT32_C(0x40000000)));
/* 0016e658: mtc1 at,f5 */ f[5]=(uint32_t)cpu(1);
/* 0016e65c: add.S f0,f0,f1 */ f[0]=add(f[0],f[1]);
/* 0016e660: mul.S f0,f0,f4 */ f[0]=mul(f[0],f[4]);
/* 0016e664: mul.S f0,f0,f2 */ f[0]=mul(f[0],f[2]);
/* 0016e668: mul.S f0,f0,f3 */ f[0]=mul(f[0],f[3]);
/* 0016e66c: c.lt.S f5,f0 */ condition=EE_FPU_COMPARE_S(f[5],f[0],1);
/* 0016e670: bc1f 0x0016e680 */ {int taken=(condition==0);/* delay 0016e674 */ if(taken){goto L_0016e680;}}
/* 0016e678: jr ra */ {uint64_t target=cpu(31);/* delay 0016e67c */ f[0]=f[5];checkReturn(target,incoming);return real(f[0]);}
L_0016e680:;
/* 0016e680: lwc1 f1,-0x7af8(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffff8508)));
/* 0016e684: c.lt.S f0,f1 */ condition=EE_FPU_COMPARE_S(f[0],f[1],1);
/* 0016e688: bc1tl 0x0016e690 */ {int taken=(condition!=0);if(taken){/* delay 0016e68c */ f[0]=f[1];goto L_0016e690;}}
L_0016e690:;
/* 0016e690: jr ra */ {uint64_t target=cpu(31);/* delay 0016e694 */ checkReturn(target,incoming);return real(f[0]);}
}
uint64_t ps2BattleActionScaleLookup_0016E560(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0016e560u);
uint64_t incoming=cpu(31);
/* 0016e560: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0016e564: li v0,0x200 */ set(2,sx(UINT32_C(0x00000200)));
/* 0016e568: beq a0,zero,0x0016e5a0 */ {int taken=(cpu(4)==cpu(0));/* delay 0016e56c */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0016e5a0;}}
/* 0016e570: lw v1,0x78(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000078)));
/* 0016e574: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 0016e578: beql v1,zero,0x0016e5a4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0016e57c */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0016e5a4;}}
/* 0016e580: jal 0x00246ab8 */ set(31,0x0016e588u);/* delay 0016e584 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000092))));set(2,ps2BattleActionScaleLookup_00246AB8(cpu(4)));
/* 0016e588: move a0,v0 */ set(4,cpu(2));
/* 0016e58c: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0016e590: andi v1,v1,0x4 */ set(3,cpu(3)&UINT32_C(0x00000004));
/* 0016e594: bne v1,zero,0x0016e5a0 */ {int taken=(cpu(3)!=cpu(0));/* delay 0016e598 */ set(2,cpu(0));if(taken){goto L_0016e5a0;}}
/* 0016e59c: lhu v0,0x4(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000004))));
L_0016e5a0:;
/* 0016e5a0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0016e5a4:;
/* 0016e5a4: jr ra */ {uint64_t target=cpu(31);/* delay 0016e5a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionScaleLookup_00246AB8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00246ab8u);
uint64_t incoming=cpu(31);
/* 00246ab8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00246abc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00246ac0: move s0,a0 */ set(16,cpu(4));
/* 00246ac4: addiu a0,s0,-0x10 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 00246ac8: slti v0,s0,0x10 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00246acc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246ad0: sll v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)<<4));
/* 00246ad4: bne v0,zero,0x00246b00 */ {int taken=(cpu(2)!=cpu(0));/* delay 00246ad8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_00246b00;}}
/* 00246adc: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 00246ae0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00246ae4: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00246ae8: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 00246aec: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00246af0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00246af4: b 0x00246b50 */ /* delay 00246af8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000a54)));goto L_00246b50;
L_00246b00:;
/* 00246b00: jal 0x002469a0 */ set(31,0x00246b08u);/* delay 00246b04 */ set(2,ps2BattleActionScaleLookup_002469A0());
/* 00246b08: move a0,s0 */ set(4,cpu(16));
/* 00246b0c: jal 0x00246a40 */ set(31,0x00246b14u);/* delay 00246b10 */ set(17,cpu(2));set(2,ps2BattleActionScaleLookup_00246A40(cpu(4)));
/* 00246b14: move a1,v0 */ set(5,cpu(2));
/* 00246b18: beq a1,zero,0x00246b54 */ {int taken=(cpu(5)==cpu(0));/* delay 00246b1c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00246b54;}}
/* 00246b20: lhu v1,0x0(a1) */ set(3,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 00246b24: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 00246b28: andi v1,v1,0xffff */ set(3,cpu(3)&UINT32_C(0x0000ffff));
/* 00246b2c: beq v1,zero,0x00246b54 */ {int taken=(cpu(3)==cpu(0));/* delay 00246b30 */ set(2,cpu(0));if(taken){goto L_00246b54;}}
/* 00246b34: move a0,s1 */ set(4,cpu(17));
/* 00246b38: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246b3c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00246b40: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00246b44: j 0x002469c0 */ /* delay 00246b48 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);set(2,ps2BattleActionScaleLookup_002469C0(cpu(4),cpu(5)));return cpu(2);
L_00246b50:;
/* 00246b50: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00246b54:;
/* 00246b54: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246b58: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00246b5c: jr ra */ {uint64_t target=cpu(31);/* delay 00246b60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionScaleLookup_00246A40(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00246a40u);
uint64_t incoming=cpu(31);
/* 00246a40: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00246a44: move v0,zero */ set(2,cpu(0));
/* 00246a48: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00246a4c: move s0,a0 */ set(16,cpu(4));
/* 00246a50: slti v1,s0,0x10 */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00246a54: beq v1,zero,0x00246aa8 */ {int taken=(cpu(3)==cpu(0));/* delay 00246a58 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_00246aa8;}}
/* 00246a5c: jal 0x002469a0 */ set(31,0x00246a64u);/* delay 00246a60 */ set(2,ps2BattleActionScaleLookup_002469A0());
/* 00246a64: sll v1,s0,0x4 */ set(3,sx((uint32_t)cpu(16)<<4));
/* 00246a68: move a3,v0 */ set(7,cpu(2));
/* 00246a6c: lw a1,0x0(a3) */ lw(5,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 00246a70: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 00246a74: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 00246a78: addu v1,a1,v1 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 00246a7c: lw a0,0x78(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000078)));
/* 00246a80: andi a2,a0,0x40 */ set(6,cpu(4)&UINT32_C(0x00000040));
/* 00246a84: andi a0,a0,0x1 */ set(4,cpu(4)&UINT32_C(0x00000001));
/* 00246a88: beq a0,zero,0x00246aa8 */ {int taken=(cpu(4)==cpu(0));/* delay 00246a8c */ set(2,cpu(0));if(taken){goto L_00246aa8;}}
/* 00246a90: beq a2,zero,0x00246aac */ {int taken=(cpu(6)==cpu(0));/* delay 00246a94 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00246aac;}}
/* 00246a98: lh v0,0x90(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000090))));
/* 00246a9c: lw v1,0x10(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000010)));
/* 00246aa0: sll v0,v0,0x7 */ set(2,sx((uint32_t)cpu(2)<<7));
/* 00246aa4: addu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
L_00246aa8:;
/* 00246aa8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00246aac:;
/* 00246aac: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246ab0: jr ra */ {uint64_t target=cpu(31);/* delay 00246ab4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionScaleLookup_002469C0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002469c0u);
uint64_t incoming=cpu(31);
/* 002469c0: lhu a2,0x0(a1) */ set(6,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002469c4: move v0,zero */ set(2,cpu(0));
/* 002469c8: andi v1,a2,0x1 */ set(3,cpu(6)&UINT32_C(0x00000001));
/* 002469cc: andi v1,v1,0xffff */ set(3,cpu(3)&UINT32_C(0x0000ffff));
/* 002469d0: beq v1,zero,0x00246a34 */ {int taken=(cpu(3)==cpu(0));/* delay 002469d4 */ set(7,cpu(6)&UINT32_C(0x00000002));if(taken){goto L_00246a34;}}
/* 002469d8: beq a3,zero,0x00246a08 */ {int taken=(cpu(7)==cpu(0));/* delay 002469dc */ set(3,cpu(6)&UINT32_C(0x00000004));if(taken){goto L_00246a08;}}
/* 002469e0: lh v1,0x4(a1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000004))));
/* 002469e4: lw a0,0x8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002469e8: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 002469ec: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002469f0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002469f4: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002469f8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002469fc: jr ra */ {uint64_t target=cpu(31);/* delay 00246a00 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));checkReturn(target,incoming);return cpu(2);}
L_00246a08:;
/* 00246a08: bne v1,zero,0x00246a34 */ {int taken=(cpu(3)!=cpu(0));/* delay 00246a0c */ set(2,cpu(0));if(taken){goto L_00246a34;}}
/* 00246a10: lh v1,0x4(a1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000004))));
/* 00246a14: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00246a18: sll a0,v1,0x4 */ set(4,sx((uint32_t)cpu(3)<<4));
/* 00246a1c: subu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(3)));
/* 00246a20: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00246a24: subu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(3)));
/* 00246a28: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00246a2c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00246a30: addiu v0,v0,0xa54 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000a54)));
L_00246a34:;
/* 00246a34: jr ra */ {uint64_t target=cpu(31);/* delay 00246a38 */ checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionScaleLookup_002469A0(void){
nocturneEffectAxisNoteEntry(0x002469a0u);
uint64_t incoming=cpu(31);
/* 002469a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002469a4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002469a8: jal 0x00101978 */ set(31,0x002469b0u);/* delay 002469ac */ set(4,sx(UINT32_C(0x000003fa)));set(2,ps2BattleActionScaleLookup_00101978(cpu(4)));
/* 002469b0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002469b4: move a0,v0 */ set(4,cpu(2));
/* 002469b8: j 0x00101ab0 */ /* delay 002469bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);set(2,ps2BattleActionScaleLookup_00101AB0(cpu(4)));return cpu(2);
}
uint64_t ps2BattleActionScaleLookup_00101978(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00101978u);
uint64_t incoming=cpu(31);
/* 00101978: move a1,zero */ set(5,cpu(0));
/* 0010197c: move a2,zero */ set(6,cpu(0));
/* 00101980: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 00101984: li a3,0x2 */ set(7,sx(UINT32_C(0x00000002)));
L_00101988:;
/* 00101988: beq a2,t0,0x001019b8 */ {int taken=(cpu(6)==cpu(8));/* delay 0010198c */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_001019b8;}}
/* 00101990: beq v0,zero,0x001019a8 */ {int taken=(cpu(2)==cpu(0));/* delay 00101994 */ if(taken){goto L_001019a8;}}
/* 00101998: beql a2,zero,0x001019bc */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 0010199c */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6e0)));goto L_001019bc;}}
/* 001019a0: b 0x001019bc */ /* delay 001019a4 */ goto L_001019bc;
L_001019a8:;
/* 001019a8: beql a2,a3,0x001019bc */ {int taken=(cpu(6)==cpu(7));if(taken){/* delay 001019ac */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6ec)));goto L_001019bc;}}
/* 001019b0: b 0x001019bc */ /* delay 001019b4 */ goto L_001019bc;
L_001019b8:;
/* 001019b8: lw a1,-0x5908(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6f8)));
L_001019bc:;
/* 001019bc: beql a1,zero,0x001019f0 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 001019c0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));goto L_001019f0;}}
/* 001019c4: lw v1,0x20(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000020)));
L_001019c8:;
/* 001019c8: beq v1,a0,0x001019fc */ {int taken=(cpu(3)==cpu(4));/* delay 001019cc */ set(2,cpu(5));if(taken){goto L_001019fc;}}
/* 001019d0: lw a1,0x3c(a1) */ lw(5,ea(5,(int32_t)UINT32_C(0x0000003c)));
/* 001019d4: nop  */ 
/* 001019d8: nop  */ 
/* 001019dc: nop  */ 
/* 001019e0: nop  */ 
/* 001019e4: bnel a1,zero,0x001019c8 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 001019e8 */ lw(3,ea(5,(int32_t)UINT32_C(0x00000020)));goto L_001019c8;}}
/* 001019ec: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
L_001019f0:;
/* 001019f0: slti v0,a2,0x3 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 001019f4: bne v0,zero,0x00101988 */ {int taken=(cpu(2)!=cpu(0));/* delay 001019f8 */ set(2,cpu(0));if(taken){goto L_00101988;}}
L_001019fc:;
/* 001019fc: jr ra */ {uint64_t target=cpu(31);/* delay 00101a00 */ checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionScaleLookup_00101AB0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00101ab0u);
uint64_t incoming=cpu(31);
/* 00101ab0: jr ra */ {uint64_t target=cpu(31);/* delay 00101ab4 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000038)));checkReturn(target,incoming);return cpu(2);}
}
