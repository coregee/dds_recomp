/* Complete5 original result-phase/background/graphics owners; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_reward_phase_native.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveBattleRewardPhaseNativeAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}

static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattleRewardPhaseNativeCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneBattleRewardPhaseNativeCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneBattleRewardPhaseNativeCpuWrite(r,q);if(r==29u)nocturneBattleRewardPhaseNativeSetStackPointer(q[0]);
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









static void body_00128fd0(void);
static void body_00129098(void);
static void body_001291b0(void);
static void body_00129c08(void);
static void body_0024b010(void);
static void body_00128fd0(void){
uint64_t incoming=cpu(31);
/* 00128fd0: jr ra */ {uint64_t target=cpu(31);/* delay 00128fd4 */ sw(ea(28,(int32_t)UINT32_C(0xffffaad0)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_00129098(void){
uint64_t incoming=cpu(31);
/* 00129098: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 0012909c: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001290a0: move s8,a0 */ set(30,cpu(4));
/* 001290a4: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 001290a8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001290ac: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001290b0: move s1,t1 */ set(17,cpu(9));
/* 001290b4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001290b8: move s2,t0 */ set(18,cpu(8));
/* 001290bc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001290c0: move s3,a3 */ set(19,cpu(7));
/* 001290c4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001290c8: move s4,a1 */ set(20,cpu(5));
/* 001290cc: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001290d0: move s5,a2 */ set(21,cpu(6));
/* 001290d4: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001290d8: move s0,t3 */ set(16,cpu(11));
/* 001290dc: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001290e0: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001290e4: jal 0x002acb50 */ set(31,UINT64_C(0x001290ec));/* delay 001290e8 */ set(21,sx((uint32_t)cpu(21)<<4));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb50),UINT32_C(0x001290e4));
/* 001290ec: move s6,v0 */ set(22,cpu(2));
/* 001290f0: sll s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)<<1));
/* 001290f4: move a0,s6 */ set(4,cpu(22));
/* 001290f8: jal 0x002acb90 */ set(31,UINT64_C(0x00129100));/* delay 001290fc */ set(16,sx((uint32_t)cpu(16)<<17));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb90),UINT32_C(0x001290f8));
/* 00129100: jal 0x002acb50 */ set(31,UINT64_C(0x00129108));/* delay 00129104 */ set(4,sx(UINT32_C(0x00000030)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb50),UINT32_C(0x00129100));
/* 00129108: li a1,0x30 */ set(5,sx(UINT32_C(0x00000030)));
/* 0012910c: move s7,v0 */ set(23,cpu(2));
/* 00129110: sll s2,s2,0xe */ set(18,sx((uint32_t)cpu(18)<<14));
/* 00129114: move a0,s7 */ set(4,cpu(23));
/* 00129118: jal 0x002b9d38 */ set(31,UINT64_C(0x00129120));/* delay 0012911c */ set(17,sx((uint32_t)cpu(17)<<15));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002b9d38),UINT32_C(0x00129118));
/* 00129120: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 00129124: sll s3,s3,0xc */ set(19,sx((uint32_t)cpu(19)<<12));
/* 00129128: or s2,s2,s5 */ set(18,cpu(18)|cpu(21));
/* 0012912c: or s3,s3,s4 */ set(19,cpu(19)|cpu(20));
/* 00129130: or s0,s0,s8 */ set(16,cpu(16)|cpu(30));
/* 00129134: or s1,s1,v1 */ set(17,cpu(17)|cpu(3));
/* 00129138: li v1,0x47 */ set(3,sx(UINT32_C(0x00000047)));
/* 0012913c: or s1,s1,s3 */ set(17,cpu(17)|cpu(19));
/* 00129140: or s0,s0,s2 */ set(16,cpu(16)|cpu(18));
/* 00129144: or s0,s0,s1 */ set(16,cpu(16)|cpu(17));
/* 00129148: sd v1,0x28(v0) */ save(3,ea(2,(int32_t)UINT32_C(0x00000028)));
/* 0012914c: sd s0,0x20(v0) */ save(16,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 00129150: move a1,s7 */ set(5,cpu(23));
/* 00129154: jal 0x002acbb8 */ set(31,UINT64_C(0x0012915c));/* delay 00129158 */ set(4,cpu(22));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acbb8),UINT32_C(0x00129154));
/* 0012915c: lw a0,-0x5530(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffaad0)));
/* 00129160: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00129164: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00129168: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 0012916c: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00129170: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00129174: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0012917c));/* delay 00129178 */ set(5,cpu(22));nocturneBattleRewardPhaseNativeIndirect(target,UINT32_C(0x00129174));}
/* 0012917c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00129180: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00129184: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00129188: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0012918c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00129190: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00129194: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00129198: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0012919c: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001291a0: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001291a4: jr ra */ {uint64_t target=cpu(31);/* delay 001291a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_001291b0(void){
uint64_t incoming=cpu(31);
/* 001291b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001291b4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001291b8: move s0,a0 */ set(16,cpu(4));
/* 001291bc: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 001291c0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001291c4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001291c8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001291cc: jal 0x002acb50 */ set(31,UINT64_C(0x001291d4));/* delay 001291d0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb50),UINT32_C(0x001291cc));
/* 001291d4: move s1,v0 */ set(17,cpu(2));
/* 001291d8: jal 0x002acb90 */ set(31,UINT64_C(0x001291e0));/* delay 001291dc */ set(4,cpu(17));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb90),UINT32_C(0x001291d8));
/* 001291e0: jal 0x002acb50 */ set(31,UINT64_C(0x001291e8));/* delay 001291e4 */ set(4,sx(UINT32_C(0x00000030)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb50),UINT32_C(0x001291e0));
/* 001291e8: li a1,0x30 */ set(5,sx(UINT32_C(0x00000030)));
/* 001291ec: move s2,v0 */ set(18,cpu(2));
/* 001291f0: jal 0x002b9d38 */ set(31,UINT64_C(0x001291f8));/* delay 001291f4 */ set(4,cpu(18));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002b9d38),UINT32_C(0x001291f0));
/* 001291f8: move a0,v0 */ set(4,cpu(2));
/* 001291fc: sltiu v0,s0,0x14 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000014));
/* 00129200: beq v0,zero,0x00129264 */ {int taken=(cpu(2)==cpu(0));/* delay 00129204 */ set(2,sx(UINT32_C(0x00000044)));if(taken){goto L_00129264;}}
/* 00129208: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 0012920c: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 00129210: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00129214: lw v1,0x1b60(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00001b60)));
/* 00129218: jr v1 */ {uint64_t target=cpu(3);/* delay 0012921c */ switch((uint32_t)target){case UINT32_C(0x00129220):goto L_00129220;case UINT32_C(0x00129228):goto L_00129228;case UINT32_C(0x00129230):goto L_00129230;case UINT32_C(0x00129238):goto L_00129238;case UINT32_C(0x00129240):goto L_00129240;case UINT32_C(0x00129248):goto L_00129248;case UINT32_C(0x00129250):goto L_00129250;case UINT32_C(0x00129258):goto L_00129258;case UINT32_C(0x00129260):goto L_00129260;default:abort();}}
L_00129220:;
/* 00129220: b 0x00129264 */ /* delay 00129224 */ set(2,sx(UINT32_C(0x00000048)));goto L_00129264;
L_00129228:;
/* 00129228: b 0x00129264 */ /* delay 0012922c */ set(2,sx(UINT32_C(0x00000042)));goto L_00129264;
L_00129230:;
/* 00129230: b 0x00129264 */ /* delay 00129234 */ set(2,sx(UINT32_C(0x00000084)));goto L_00129264;
L_00129238:;
/* 00129238: b 0x00129264 */ /* delay 0012923c */ set(2,sx(UINT32_C(0x00000006)));goto L_00129264;
L_00129240:;
/* 00129240: b 0x00129264 */ /* delay 00129244 */ set(2,sx(UINT32_C(0x00000089)));goto L_00129264;
L_00129248:;
/* 00129248: b 0x00129264 */ /* delay 0012924c */ set(2,sx(UINT32_C(0x00000042)));goto L_00129264;
L_00129250:;
/* 00129250: b 0x00129264 */ /* delay 00129254 */ set(2,sx(UINT32_C(0x0000002a)));goto L_00129264;
L_00129258:;
/* 00129258: b 0x00129264 */ /* delay 0012925c */ set(2,sx(UINT32_C(0x0000004a)));goto L_00129264;
L_00129260:;
/* 00129260: li v0,0x44 */ set(2,sx(UINT32_C(0x00000044)));
L_00129264:;
/* 00129264: sd v0,0x20(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 00129268: li v0,0x42 */ set(2,sx(UINT32_C(0x00000042)));
/* 0012926c: move a1,s2 */ set(5,cpu(18));
/* 00129270: sd v0,0x28(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 00129274: jal 0x002acbb8 */ set(31,UINT64_C(0x0012927c));/* delay 00129278 */ set(4,cpu(17));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acbb8),UINT32_C(0x00129274));
/* 0012927c: lw a0,-0x5530(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffaad0)));
/* 00129280: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00129284: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00129288: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 0012928c: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00129290: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00129294: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0012929c));/* delay 00129298 */ set(5,cpu(17));nocturneBattleRewardPhaseNativeIndirect(target,UINT32_C(0x00129294));}
/* 0012929c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001292a0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001292a4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001292a8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001292ac: jr ra */ {uint64_t target=cpu(31);/* delay 001292b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00129c08(void){
uint64_t incoming=cpu(31);
/* 00129c08: move v0,a0 */ set(2,cpu(4));
/* 00129c0c: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 00129c10: addu a2,v0,a2 */ set(6,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00129c14: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 00129c18: addu a3,a1,a3 */ set(7,sx((uint32_t)cpu(5)+(uint32_t)cpu(7)));
/* 00129c1c: sll a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)<<4));
/* 00129c20: addiu sp,sp,-0xa0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff60)));
/* 00129c24: sll a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)<<4));
/* 00129c28: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 00129c2c: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00129c30: sd s1,0x58(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00129c34: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00129c38: sd s3,0x68(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00129c3c: sd s4,0x70(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 00129c40: sd s5,0x78(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00129c44: sd s6,0x80(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00129c48: move s6,t0 */ set(22,cpu(8));
/* 00129c4c: sd s7,0x88(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 00129c50: move s7,t2 */ set(23,cpu(10));
/* 00129c54: sd s8,0x90(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 00129c58: dsll32 s6,s6,0x0 */ set(22,cpu(22)<<32);
/* 00129c5c: sw a1,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(5));
/* 00129c60: dsll32 s7,s7,0x0 */ set(23,cpu(23)<<32);
/* 00129c64: sw a2,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(6));
/* 00129c68: dsrl32 s6,s6,0x0 */ set(22,cpu(22)>>32);
/* 00129c6c: sw t1,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(9));
/* 00129c70: dsrl32 s7,s7,0x0 */ set(23,cpu(23)>>32);
/* 00129c74: sw a3,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(7));
/* 00129c78: sw t3,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(11));
/* 00129c7c: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 00129c80: sw a2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 00129c84: sw a3,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(7));
/* 00129c88: lw s5,0xa0(sp) */ lw(21,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 00129c8c: lw s4,0xb0(sp) */ lw(20,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 00129c90: lw s3,0xc0(sp) */ lw(19,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 00129c94: dsll32 s5,s5,0x0 */ set(21,cpu(21)<<32);
/* 00129c98: lw s2,0xd0(sp) */ lw(18,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 00129c9c: dsll32 s4,s4,0x0 */ set(20,cpu(20)<<32);
/* 00129ca0: lw s1,0xe0(sp) */ lw(17,ea(29,(int32_t)UINT32_C(0x000000e0)));
/* 00129ca4: dsll32 s3,s3,0x0 */ set(19,cpu(19)<<32);
/* 00129ca8: lw s0,0xf0(sp) */ lw(16,ea(29,(int32_t)UINT32_C(0x000000f0)));
/* 00129cac: dsll32 s2,s2,0x0 */ set(18,cpu(18)<<32);
/* 00129cb0: sd ra,0x98(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00129cb4: dsll32 s1,s1,0x0 */ set(17,cpu(17)<<32);
/* 00129cb8: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 00129cbc: dsll32 s0,s0,0x0 */ set(16,cpu(16)<<32);
/* 00129cc0: jal 0x002acb50 */ set(31,UINT64_C(0x00129cc8));/* delay 00129cc4 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb50),UINT32_C(0x00129cc0));
/* 00129cc8: move a0,v0 */ set(4,cpu(2));
/* 00129ccc: jal 0x002acb90 */ set(31,UINT64_C(0x00129cd4));/* delay 00129cd0 */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb90),UINT32_C(0x00129ccc));
/* 00129cd4: li a0,0x2 */ set(4,sx(UINT32_C(0x00000002)));
/* 00129cd8: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 00129cdc: jal 0x002b9d68 */ set(31,UINT64_C(0x00129ce4));/* delay 00129ce0 */ set(21,cpu(21)>>32);nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002b9d68),UINT32_C(0x00129cdc));
/* 00129ce4: dsrl32 s4,s4,0x0 */ set(20,cpu(20)>>32);
/* 00129ce8: move a0,v0 */ set(4,cpu(2));
/* 00129cec: jal 0x002acb50 */ set(31,UINT64_C(0x00129cf4));/* delay 00129cf0 */ set(19,cpu(19)>>32);nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acb50),UINT32_C(0x00129cec));
/* 00129cf4: li a1,0x4d */ set(5,sx(UINT32_C(0x0000004d)));
/* 00129cf8: move s8,v0 */ set(30,cpu(2));
/* 00129cfc: li a2,0x2 */ set(6,sx(UINT32_C(0x00000002)));
/* 00129d00: li a3,0x41 */ set(7,sx(UINT32_C(0x00000041)));
/* 00129d04: li t0,0x4 */ set(8,sx(UINT32_C(0x00000004)));
/* 00129d08: move a0,s8 */ set(4,cpu(30));
/* 00129d0c: jal 0x002b9d80 */ set(31,UINT64_C(0x00129d14));/* delay 00129d10 */ set(18,cpu(18)>>32);nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002b9d80),UINT32_C(0x00129d0c));
/* 00129d14: jal 0x002b9d78 */ set(31,UINT64_C(0x00129d1c));/* delay 00129d18 */ set(4,cpu(30));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002b9d78),UINT32_C(0x00129d14));
/* 00129d1c: move a3,zero */ set(7,cpu(0));
/* 00129d20: lw v1,0x30(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00129d24: move a1,v0 */ set(5,cpu(2));
/* 00129d28: lw t4,0xa8(sp) */ lw(12,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 00129d2c: dsrl32 s1,s1,0x0 */ set(17,cpu(17)>>32);
/* 00129d30: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00129d34: dsll32 t3,v1,0x0 */ set(11,cpu(3)<<32);
/* 00129d38: dsll32 t2,t4,0x0 */ set(10,cpu(12)<<32);
/* 00129d3c: lw t4,0xd8(sp) */ lw(12,ea(29,(int32_t)UINT32_C(0x000000d8)));
/* 00129d40: lw v1,0xc8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 00129d44: dsll32 t1,v0,0x0 */ set(9,cpu(2)<<32);
/* 00129d48: dsll32 a0,t4,0x0 */ set(4,cpu(12)<<32);
/* 00129d4c: lw t4,0xf8(sp) */ lw(12,ea(29,(int32_t)UINT32_C(0x000000f8)));
/* 00129d50: dsll32 a2,v1,0x0 */ set(6,cpu(3)<<32);
/* 00129d54: lw v1,0xe8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000e8)));
/* 00129d58: lw v0,0xb8(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 00129d5c: dsrl32 s0,s0,0x0 */ set(16,cpu(16)>>32);
/* 00129d60: or s5,s5,t2 */ set(21,cpu(21)|cpu(10));
/* 00129d64: li t2,0x2 */ set(10,sx(UINT32_C(0x00000002)));
/* 00129d68: dsll32 t0,v0,0x0 */ set(8,cpu(2)<<32);
/* 00129d6c: dsll32 v0,v1,0x0 */ set(2,cpu(3)<<32);
/* 00129d70: dsll32 v1,t4,0x0 */ set(3,cpu(12)<<32);
/* 00129d74: li t4,0x1 */ set(12,sx(UINT32_C(0x00000001)));
/* 00129d78: or s4,s4,t0 */ set(20,cpu(20)|cpu(8));
/* 00129d7c: lui t0,0xff */ set(8,sx(UINT32_C(0x00ff0000)));
/* 00129d80: ori t0,t0,0xffff */ set(8,cpu(8)|UINT32_C(0x0000ffff));
/* 00129d84: or s3,s3,a2 */ set(19,cpu(19)|cpu(6));
/* 00129d88: move a2,sp */ set(6,cpu(29));
/* 00129d8c: or t1,s6,t1 */ set(9,cpu(22)|cpu(9));
/* 00129d90: or t3,s7,t3 */ set(11,cpu(23)|cpu(11));
/* 00129d94: or s2,s2,a0 */ set(18,cpu(18)|cpu(4));
/* 00129d98: or s1,s1,v0 */ set(17,cpu(17)|cpu(2));
/* 00129d9c: or s0,s0,v1 */ set(16,cpu(16)|cpu(3));
L_00129da0:;
/* 00129da0: bne a3,zero,0x00129db8 */ {int taken=(cpu(7)!=cpu(0));/* delay 00129da4 */ if(taken){goto L_00129db8;}}
/* 00129da8: sd t1,0x0(a1) */ save(9,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00129dac: b 0x00129dec */ /* delay 00129db0 */ save(11,ea(5,(int32_t)UINT32_C(0x00000008)));goto L_00129dec;
L_00129db8:;
/* 00129db8: bne a3,t4,0x00129dd0 */ {int taken=(cpu(7)!=cpu(12));/* delay 00129dbc */ if(taken){goto L_00129dd0;}}
/* 00129dc0: sd s5,0x0(a1) */ save(21,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00129dc4: b 0x00129dec */ /* delay 00129dc8 */ save(20,ea(5,(int32_t)UINT32_C(0x00000008)));goto L_00129dec;
L_00129dd0:;
/* 00129dd0: bnel a3,t2,0x00129de8 */ {int taken=(cpu(7)!=cpu(10));if(taken){/* delay 00129dd4 */ save(17,ea(5,(int32_t)UINT32_C(0x00000000)));goto L_00129de8;}}
/* 00129dd8: sd s3,0x0(a1) */ save(19,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00129ddc: b 0x00129dec */ /* delay 00129de0 */ save(18,ea(5,(int32_t)UINT32_C(0x00000008)));goto L_00129dec;
L_00129de8:;
/* 00129de8: sd s0,0x8(a1) */ save(16,ea(5,(int32_t)UINT32_C(0x00000008)));
L_00129dec:;
/* 00129dec: lw v0,0x0(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 00129df0: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 00129df4: lw v1,0x4(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 00129df8: addiu a2,a2,0x8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000008)));
/* 00129dfc: addiu v0,v0,0x7000 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00007000)));
/* 00129e00: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 00129e04: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 00129e08: addiu v1,v1,0x7900 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00007900)));
/* 00129e0c: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 00129e10: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 00129e14: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00129e18: slti a0,a3,0x4 */ set(4,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 00129e1c: sd v0,0x0(a1) */ save(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00129e20: sd t0,0x8(a1) */ save(8,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00129e24: bne a0,zero,0x00129da0 */ {int taken=(cpu(4)!=cpu(0));/* delay 00129e28 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));if(taken){goto L_00129da0;}}
/* 00129e2c: lw a0,0x40(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00129e30: jal 0x002acbb8 */ set(31,UINT64_C(0x00129e38));/* delay 00129e34 */ set(5,cpu(30));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002acbb8),UINT32_C(0x00129e30));
/* 00129e38: lw a0,-0x5530(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffaad0)));
/* 00129e3c: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00129e40: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00129e44: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 00129e48: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00129e4c: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00129e50: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00129e58));/* delay 00129e54 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000040)));nocturneBattleRewardPhaseNativeIndirect(target,UINT32_C(0x00129e50));}
/* 00129e58: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00129e5c: ld s1,0x58(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00129e60: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00129e64: ld s3,0x68(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00129e68: ld s4,0x70(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 00129e6c: ld s5,0x78(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00129e70: ld s6,0x80(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00129e74: ld s7,0x88(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 00129e78: ld s8,0x90(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 00129e7c: ld ra,0x98(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00129e80: jr ra */ {uint64_t target=cpu(31);/* delay 00129e84 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000a0)));checkReturn(target,incoming);return;}
}
static void body_0024b010(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0024b010: lwc1 f1,-0x5cbc(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa344)));
/* 0024b014: addiu sp,sp,-0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff00)));
/* 0024b018: lwc1 f0,-0x3070(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffcf90)));
/* 0024b01c: lui v1,0xa09d */ set(3,sx(UINT32_C(0xa09d0000)));
/* 0024b020: lw v0,-0x30a0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf60)));
/* 0024b024: ori v1,v1,0xc300 */ set(3,cpu(3)|UINT32_C(0x0000c300));
/* 0024b028: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 0024b02c: sw a0,0x90(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000090)),(uint32_t)cpu(4));
/* 0024b030: addiu a1,v0,0x1 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0024b034: li a0,0x47 */ set(4,sx(UINT32_C(0x00000047)));
/* 0024b038: sd s0,0xa0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0024b03c: sd s1,0xa8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0024b040: sd s2,0xb0(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0024b044: sd s3,0xb8(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0024b048: sd s4,0xc0(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 0024b04c: sd s5,0xc8(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 0024b050: sd s6,0xd0(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 0024b054: sd s7,0xd8(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x000000d8)));
/* 0024b058: sd s8,0xe0(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x000000e0)));
/* 0024b05c: sd ra,0xe8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000e8)));
/* 0024b060: swc1 f20,0xf0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000f0)),f[20]);
/* 0024b064: sw zero,0x94(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000094)),(uint32_t)cpu(0));
/* 0024b068: sw v1,0x98(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000098)),(uint32_t)cpu(3));
/* 0024b06c: swc1 f0,-0x3070(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf90)),f[0]);
/* 0024b070: jal 0x002797b0 */ set(31,UINT64_C(0x0024b078));/* delay 0024b074 */ sw(ea(28,(int32_t)UINT32_C(0xffffcf60)),(uint32_t)cpu(5));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002797b0),UINT32_C(0x0024b070));
/* 0024b078: move a1,zero */ set(5,cpu(0));
/* 0024b07c: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0024b080: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 0024b084: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 0024b088: move t0,zero */ set(8,cpu(0));
/* 0024b08c: move t1,zero */ set(9,cpu(0));
/* 0024b090: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024b094: jal 0x00279868 */ set(31,UINT64_C(0x0024b09c));/* delay 0024b098 */ set(11,sx(UINT32_C(0x00000001)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279868),UINT32_C(0x0024b094));
/* 0024b09c: jal 0x00279980 */ set(31,UINT64_C(0x0024b0a4));/* delay 0024b0a0 */ set(4,cpu(0));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279980),UINT32_C(0x0024b09c));
/* 0024b0a4: lw a1,-0x30a0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffcf60)));
/* 0024b0a8: blez a1,0x0024b244 */ {int taken=((int64_t)cpu(5)<=0);/* delay 0024b0ac */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000009));if(taken){goto L_0024b244;}}
/* 0024b0b0: li s1,0xa */ set(17,sx(UINT32_C(0x0000000a)));
/* 0024b0b4: slti v1,a1,0xa */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 0024b0b8: move s5,s1 */ set(21,cpu(17));
/* 0024b0bc: li v0,0xa */ set(2,sx(UINT32_C(0x0000000a)));
/* 0024b0c0: movn s5,a1,v1 */ if(cpu(3)!=0){set(21,cpu(5));}
/* 0024b0c4: move a1,zero */ set(5,cpu(0));
/* 0024b0c8: sll v1,s5,0x7 */ set(3,sx((uint32_t)cpu(21)<<7));
/* 0024b0cc: beql v0,zero,0x0024b0d4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024b0d0 */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x0024b0d0));goto L_0024b0d4;}}
L_0024b0d4:;
/* 0024b0d4: div v1,s1 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(17),1,0);
/* 0024b0d8: lw v0,-0x3064(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf9c)));
/* 0024b0dc: lui t4,0x8000 */ set(12,sx(UINT32_C(0x80000000)));
/* 0024b0e0: move a0,zero */ set(4,cpu(0));
/* 0024b0e4: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b0e8: li a2,0x200 */ set(6,sx(UINT32_C(0x00000200)));
/* 0024b0ec: li a3,0x1c0 */ set(7,sx(UINT32_C(0x000001c0)));
/* 0024b0f0: move t0,zero */ set(8,cpu(0));
/* 0024b0f4: move t1,zero */ set(9,cpu(0));
/* 0024b0f8: li t2,0x100 */ set(10,sx(UINT32_C(0x00000100)));
/* 0024b0fc: li t3,0x100 */ set(11,sx(UINT32_C(0x00000100)));
/* 0024b100: sll s0,s5,0x3 */ set(16,sx((uint32_t)cpu(21)<<3));
/* 0024b104: lui s2,0x1000 */ set(18,sx(UINT32_C(0x10000000)));
/* 0024b108: mflo v1 */ set(3,nocturneEffectHostLo());
/* 0024b10c: move s3,v1 */ set(19,cpu(3));
/* 0024b110: sll v0,s3,0x10 */ set(2,sx((uint32_t)cpu(19)<<16));
/* 0024b114: sll v1,s3,0x8 */ set(3,sx((uint32_t)cpu(19)<<8));
/* 0024b118: or v0,v0,s3 */ set(2,cpu(2)|cpu(19));
/* 0024b11c: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 0024b120: or s4,v0,t4 */ set(20,cpu(2)|cpu(12));
/* 0024b124: jal 0x00279a88 */ set(31,UINT64_C(0x0024b12c));/* delay 0024b128 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b124));
/* 0024b12c: subu v1,s0,s5 */ set(3,sx((uint32_t)cpu(16)-(uint32_t)cpu(21)));
/* 0024b130: addu s0,s0,s5 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));
/* 0024b134: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 0024b138: li v0,0xa */ set(2,sx(UINT32_C(0x0000000a)));
/* 0024b13c: div v1,s1 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(17),1,0);
/* 0024b140: beql v0,zero,0x0024b148 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024b144 */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x0024b144));goto L_0024b148;}}
L_0024b148:;
/* 0024b148: lw v0,-0x3064(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf9c)));
/* 0024b14c: li a0,-0x2 */ set(4,sx(UINT32_C(0xfffffffe)));
/* 0024b150: li a1,-0x2 */ set(5,sx(UINT32_C(0xfffffffe)));
/* 0024b154: li a2,0x204 */ set(6,sx(UINT32_C(0x00000204)));
/* 0024b158: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b15c: li a3,0x1c4 */ set(7,sx(UINT32_C(0x000001c4)));
/* 0024b160: move t0,zero */ set(8,cpu(0));
/* 0024b164: move t1,zero */ set(9,cpu(0));
/* 0024b168: li t2,0x100 */ set(10,sx(UINT32_C(0x00000100)));
/* 0024b16c: li t3,0x100 */ set(11,sx(UINT32_C(0x00000100)));
/* 0024b170: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0024b174: mflo v1 */ set(3,nocturneEffectHostLo());
/* 0024b178: move s3,v1 */ set(19,cpu(3));
/* 0024b17c: sll v0,s3,0x10 */ set(2,sx((uint32_t)cpu(19)<<16));
/* 0024b180: sll v1,s3,0x8 */ set(3,sx((uint32_t)cpu(19)<<8));
/* 0024b184: or v0,v0,s3 */ set(2,cpu(2)|cpu(19));
/* 0024b188: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 0024b18c: or s4,v0,s2 */ set(20,cpu(2)|cpu(18));
/* 0024b190: jal 0x00279a88 */ set(31,UINT64_C(0x0024b198));/* delay 0024b194 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b190));
/* 0024b198: div s0,s1 */ nativeDivide((uint32_t)cpu(16),(uint32_t)cpu(17),1,0);
/* 0024b19c: li v0,0xa */ set(2,sx(UINT32_C(0x0000000a)));
/* 0024b1a0: beql v0,zero,0x0024b1a8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024b1a4 */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x0024b1a4));goto L_0024b1a8;}}
L_0024b1a8:;
/* 0024b1a8: lw v0,-0x3064(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf9c)));
/* 0024b1ac: li a0,-0x4 */ set(4,sx(UINT32_C(0xfffffffc)));
/* 0024b1b0: li a1,-0x4 */ set(5,sx(UINT32_C(0xfffffffc)));
/* 0024b1b4: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b1b8: li a2,0x208 */ set(6,sx(UINT32_C(0x00000208)));
/* 0024b1bc: li a3,0x1c8 */ set(7,sx(UINT32_C(0x000001c8)));
/* 0024b1c0: move t0,zero */ set(8,cpu(0));
/* 0024b1c4: move t1,zero */ set(9,cpu(0));
/* 0024b1c8: li t2,0x100 */ set(10,sx(UINT32_C(0x00000100)));
/* 0024b1cc: li t3,0x100 */ set(11,sx(UINT32_C(0x00000100)));
/* 0024b1d0: mflo s0 */ set(16,nocturneEffectHostLo());
/* 0024b1d4: move s3,s0 */ set(19,cpu(16));
/* 0024b1d8: sll v0,s3,0x10 */ set(2,sx((uint32_t)cpu(19)<<16));
/* 0024b1dc: sll v1,s3,0x8 */ set(3,sx((uint32_t)cpu(19)<<8));
/* 0024b1e0: or v0,v0,s3 */ set(2,cpu(2)|cpu(19));
/* 0024b1e4: sll s3,s5,0x4 */ set(19,sx((uint32_t)cpu(21)<<4));
/* 0024b1e8: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 0024b1ec: or s4,v0,s2 */ set(20,cpu(2)|cpu(18));
/* 0024b1f0: jal 0x00279a88 */ set(31,UINT64_C(0x0024b1f8));/* delay 0024b1f4 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b1f0));
/* 0024b1f8: sll v0,s5,0x14 */ set(2,sx((uint32_t)cpu(21)<<20));
/* 0024b1fc: sll v1,s5,0xc */ set(3,sx((uint32_t)cpu(21)<<12));
/* 0024b200: or v0,v0,s3 */ set(2,cpu(2)|cpu(19));
/* 0024b204: lw t4,-0x3064(gp) */ lw(12,ea(28,(int32_t)UINT32_C(0xffffcf9c)));
/* 0024b208: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 0024b20c: li a1,-0x6 */ set(5,sx(UINT32_C(0xfffffffa)));
/* 0024b210: or s4,v0,s2 */ set(20,cpu(2)|cpu(18));
/* 0024b214: li a0,-0x6 */ set(4,sx(UINT32_C(0xfffffffa)));
/* 0024b218: li a2,0x20c */ set(6,sx(UINT32_C(0x0000020c)));
/* 0024b21c: li a3,0x1cc */ set(7,sx(UINT32_C(0x000001cc)));
/* 0024b220: move t0,zero */ set(8,cpu(0));
/* 0024b224: move t1,zero */ set(9,cpu(0));
/* 0024b228: li t2,0x100 */ set(10,sx(UINT32_C(0x00000100)));
/* 0024b22c: li t3,0x100 */ set(11,sx(UINT32_C(0x00000100)));
/* 0024b230: sw s4,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));
/* 0024b234: jal 0x00279a88 */ set(31,UINT64_C(0x0024b23c));/* delay 0024b238 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(12));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b234));
/* 0024b23c: lw a1,-0x30a0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffcf60)));
/* 0024b240: slti v0,a1,0x9 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000009));
L_0024b244:;
/* 0024b244: bne v0,zero,0x0024b5ac */ {int taken=(cpu(2)!=cpu(0));/* delay 0024b248 */ set(4,cpu(0));if(taken){goto L_0024b5ac;}}
/* 0024b24c: slti v0,a1,0x17 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000017));
/* 0024b250: beql v0,zero,0x0024b260 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024b254 */ set(21,cpu(0));goto L_0024b260;}}
/* 0024b258: li v0,0x17 */ set(2,sx(UINT32_C(0x00000017)));
/* 0024b25c: subu s5,v0,a1 */ set(21,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
L_0024b260:;
/* 0024b260: lw v0,-0x3068(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024b264: lui s0,0x8080 */ set(16,sx(UINT32_C(0x80800000)));
/* 0024b268: ori s0,s0,0x8080 */ set(16,cpu(16)|UINT32_C(0x00008080));
/* 0024b26c: move a0,zero */ set(4,cpu(0));
/* 0024b270: li a1,0x36 */ set(5,sx(UINT32_C(0x00000036)));
/* 0024b274: li a2,0xfc */ set(6,sx(UINT32_C(0x000000fc)));
/* 0024b278: li a3,0x1c */ set(7,sx(UINT32_C(0x0000001c)));
/* 0024b27c: li t0,0x2 */ set(8,sx(UINT32_C(0x00000002)));
/* 0024b280: li t1,0x53 */ set(9,sx(UINT32_C(0x00000053)));
/* 0024b284: li t2,0xfc */ set(10,sx(UINT32_C(0x000000fc)));
/* 0024b288: li t3,0x1c */ set(11,sx(UINT32_C(0x0000001c)));
/* 0024b28c: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b290: jal 0x00279a88 */ set(31,UINT64_C(0x0024b298));/* delay 0024b294 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b290));
/* 0024b298: lw v0,-0x3068(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024b29c: li a0,0xfc */ set(4,sx(UINT32_C(0x000000fc)));
/* 0024b2a0: li a1,0x36 */ set(5,sx(UINT32_C(0x00000036)));
/* 0024b2a4: li a2,0x104 */ set(6,sx(UINT32_C(0x00000104)));
/* 0024b2a8: li a3,0x1c */ set(7,sx(UINT32_C(0x0000001c)));
/* 0024b2ac: li t0,0xfd */ set(8,sx(UINT32_C(0x000000fd)));
/* 0024b2b0: li t1,0x53 */ set(9,sx(UINT32_C(0x00000053)));
/* 0024b2b4: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024b2b8: li t3,0x1c */ set(11,sx(UINT32_C(0x0000001c)));
/* 0024b2bc: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b2c0: jal 0x00279a88 */ set(31,UINT64_C(0x0024b2c8));/* delay 0024b2c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b2c0));
/* 0024b2c8: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b2cc: move a0,zero */ set(4,cpu(0));
/* 0024b2d0: li a1,0x56 */ set(5,sx(UINT32_C(0x00000056)));
/* 0024b2d4: li a2,0x13 */ set(6,sx(UINT32_C(0x00000013)));
/* 0024b2d8: li a3,0x66 */ set(7,sx(UINT32_C(0x00000066)));
/* 0024b2dc: li t0,0xe7 */ set(8,sx(UINT32_C(0x000000e7)));
/* 0024b2e0: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b2e4: li t2,0x13 */ set(10,sx(UINT32_C(0x00000013)));
/* 0024b2e8: li t3,0x66 */ set(11,sx(UINT32_C(0x00000066)));
/* 0024b2ec: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b2f0: jal 0x00279a88 */ set(31,UINT64_C(0x0024b2f8));/* delay 0024b2f4 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b2f0));
/* 0024b2f8: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b2fc: li a0,0x13 */ set(4,sx(UINT32_C(0x00000013)));
/* 0024b300: li a1,0x56 */ set(5,sx(UINT32_C(0x00000056)));
/* 0024b304: li a2,0x1ed */ set(6,sx(UINT32_C(0x000001ed)));
/* 0024b308: li a3,0x66 */ set(7,sx(UINT32_C(0x00000066)));
/* 0024b30c: li t0,0xf9 */ set(8,sx(UINT32_C(0x000000f9)));
/* 0024b310: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b314: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024b318: li t3,0x66 */ set(11,sx(UINT32_C(0x00000066)));
/* 0024b31c: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b320: jal 0x00279a88 */ set(31,UINT64_C(0x0024b328));/* delay 0024b324 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b320));
/* 0024b328: lw v0,-0x3068(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024b32c: move a0,zero */ set(4,cpu(0));
/* 0024b330: li a1,0xc0 */ set(5,sx(UINT32_C(0x000000c0)));
/* 0024b334: li a2,0xfc */ set(6,sx(UINT32_C(0x000000fc)));
/* 0024b338: li a3,0x5 */ set(7,sx(UINT32_C(0x00000005)));
/* 0024b33c: li t0,0x2 */ set(8,sx(UINT32_C(0x00000002)));
/* 0024b340: li t1,0x6f */ set(9,sx(UINT32_C(0x0000006f)));
/* 0024b344: li t2,0xfc */ set(10,sx(UINT32_C(0x000000fc)));
/* 0024b348: li t3,0x5 */ set(11,sx(UINT32_C(0x00000005)));
/* 0024b34c: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b350: jal 0x00279a88 */ set(31,UINT64_C(0x0024b358));/* delay 0024b354 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b350));
/* 0024b358: lw v0,-0x3068(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024b35c: li a2,0x104 */ set(6,sx(UINT32_C(0x00000104)));
/* 0024b360: li a3,0x5 */ set(7,sx(UINT32_C(0x00000005)));
/* 0024b364: li t0,0xfd */ set(8,sx(UINT32_C(0x000000fd)));
/* 0024b368: li t1,0x6f */ set(9,sx(UINT32_C(0x0000006f)));
/* 0024b36c: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024b370: li t3,0x5 */ set(11,sx(UINT32_C(0x00000005)));
/* 0024b374: li a1,0xc0 */ set(5,sx(UINT32_C(0x000000c0)));
/* 0024b378: li a0,0xfc */ set(4,sx(UINT32_C(0x000000fc)));
/* 0024b37c: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b380: jal 0x00279a88 */ set(31,UINT64_C(0x0024b388));/* delay 0024b384 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b380));
/* 0024b388: lwc1 f0,-0x3070(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffcf90)));
/* 0024b38c: li s6,0x15 */ set(22,sx(UINT32_C(0x00000015)));
/* 0024b390: lwc1 f12,-0x5cb8(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffa348)));
/* 0024b394: li s2,0x3a */ set(18,sx(UINT32_C(0x0000003a)));
/* 0024b398: jal 0x002c0060 */ set(31,UINT64_C(0x0024b3a0));/* delay 0024b39c */ f[12]=EE_FPU_MUL_S(f[0],f[12]);nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002c0060),UINT32_C(0x0024b398));
/* 0024b3a0: lui at,0x41c0 */ set(1,sx(UINT32_C(0x41c00000)));
/* 0024b3a4: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0024b3a8: lui a1,0x8000 */ set(5,sx(UINT32_C(0x80000000)));
/* 0024b3ac: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0024b3b0: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0024b3b4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0024b3b8: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0024b3bc: addiu t6,v0,0x70 */ set(14,sx((uint32_t)cpu(2)+UINT32_C(0x00000070)));
/* 0024b3c0: sll v1,t6,0x8 */ set(3,sx((uint32_t)cpu(14)<<8));
/* 0024b3c4: sll v0,t6,0x10 */ set(2,sx((uint32_t)cpu(14)<<16));
/* 0024b3c8: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 0024b3cc: or a1,t6,a1 */ set(5,cpu(14)|cpu(5));
/* 0024b3d0: jal 0x00279980 */ set(31,UINT64_C(0x0024b3d8));/* delay 0024b3d4 */ set(20,cpu(5)|cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279980),UINT32_C(0x0024b3d0));
/* 0024b3d8: lw v0,-0x3068(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024b3dc: li a1,0x30 */ set(5,sx(UINT32_C(0x00000030)));
/* 0024b3e0: li a2,0x9c */ set(6,sx(UINT32_C(0x0000009c)));
/* 0024b3e4: li a3,0x2c */ set(7,sx(UINT32_C(0x0000002c)));
/* 0024b3e8: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b3ec: li t1,0x25 */ set(9,sx(UINT32_C(0x00000025)));
/* 0024b3f0: li t2,0x9c */ set(10,sx(UINT32_C(0x0000009c)));
/* 0024b3f4: li t3,0x2c */ set(11,sx(UINT32_C(0x0000002c)));
/* 0024b3f8: move a0,zero */ set(4,cpu(0));
/* 0024b3fc: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b400: jal 0x00279a88 */ set(31,UINT64_C(0x0024b408));/* delay 0024b404 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b400));
/* 0024b408: li v1,0xf */ set(3,sx(UINT32_C(0x0000000f)));
/* 0024b40c: sll v0,s5,0x7 */ set(2,sx((uint32_t)cpu(21)<<7));
/* 0024b410: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 0024b414: move a0,zero */ set(4,cpu(0));
/* 0024b418: beql v1,zero,0x0024b420 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0024b41c */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x0024b41c));goto L_0024b420;}}
L_0024b420:;
/* 0024b420: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024b424: jal 0x00279980 */ set(31,UINT64_C(0x0024b42c));/* delay 0024b428 */ set(19,cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279980),UINT32_C(0x0024b424));
/* 0024b42c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b430: li a0,0x15 */ set(4,sx(UINT32_C(0x00000015)));
/* 0024b434: li a1,0x3a */ set(5,sx(UINT32_C(0x0000003a)));
/* 0024b438: li a2,0x63 */ set(6,sx(UINT32_C(0x00000063)));
/* 0024b43c: li a3,0x15 */ set(7,sx(UINT32_C(0x00000015)));
/* 0024b440: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b444: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b448: li t2,0x63 */ set(10,sx(UINT32_C(0x00000063)));
/* 0024b44c: li t3,0x15 */ set(11,sx(UINT32_C(0x00000015)));
/* 0024b450: sw s0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 0024b454: jal 0x00279a88 */ set(31,UINT64_C(0x0024b45c));/* delay 0024b458 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b454));
/* 0024b45c: blez s3,0x0024b5ac */ {int taken=((int64_t)cpu(19)<=0);/* delay 0024b460 */ set(4,cpu(0));if(taken){goto L_0024b5ac;}}
/* 0024b464: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0024b468: jal 0x00279980 */ set(31,UINT64_C(0x0024b470));/* delay 0024b46c */ set(17,sx((uint32_t)cpu(19)<<24));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279980),UINT32_C(0x0024b468));
/* 0024b470: addiu a0,s5,0x3 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x00000003)));
/* 0024b474: slti v1,s5,0x0 */ set(3,(int64_t)cpu(21)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 0024b478: move v0,s5 */ set(2,cpu(21));
/* 0024b47c: movn v0,a0,v1 */ if(cpu(3)!=0){set(2,cpu(4));}
/* 0024b480: lui t4,0xc0 */ set(12,sx(UINT32_C(0x00c00000)));
/* 0024b484: sra a0,v0,0x2 */ set(4,sx((uint32_t)((int32_t)cpu(2)>>2)));
/* 0024b488: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b48c: sll a2,a0,0x1 */ set(6,sx((uint32_t)cpu(4)<<1));
/* 0024b490: ori t4,t4,0xc0c0 */ set(12,cpu(12)|UINT32_C(0x0000c0c0));
/* 0024b494: or t4,s1,t4 */ set(12,cpu(17)|cpu(12));
/* 0024b498: subu a1,s2,a0 */ set(5,sx((uint32_t)cpu(18)-(uint32_t)cpu(4)));
/* 0024b49c: addiu a3,a2,0x15 */ set(7,sx((uint32_t)cpu(6)+UINT32_C(0x00000015)));
/* 0024b4a0: addiu a2,a2,0x63 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000063)));
/* 0024b4a4: subu a0,s6,a0 */ set(4,sx((uint32_t)cpu(22)-(uint32_t)cpu(4)));
/* 0024b4a8: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b4ac: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b4b0: li t2,0x63 */ set(10,sx(UINT32_C(0x00000063)));
/* 0024b4b4: li t3,0x15 */ set(11,sx(UINT32_C(0x00000015)));
/* 0024b4b8: sw t4,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 0024b4bc: jal 0x00279a88 */ set(31,UINT64_C(0x0024b4c4));/* delay 0024b4c0 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b4bc));
/* 0024b4c4: srl v0,s5,0x1f */ set(2,sx((uint32_t)cpu(21)>>31));
/* 0024b4c8: lui v1,0x90 */ set(3,sx(UINT32_C(0x00900000)));
/* 0024b4cc: addu v0,s5,v0 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(2)));
/* 0024b4d0: lw t4,-0x306c(gp) */ lw(12,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b4d4: sra a0,v0,0x1 */ set(4,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 0024b4d8: ori v1,v1,0x9090 */ set(3,cpu(3)|UINT32_C(0x00009090));
/* 0024b4dc: sll a2,a0,0x1 */ set(6,sx((uint32_t)cpu(4)<<1));
/* 0024b4e0: or v1,s1,v1 */ set(3,cpu(17)|cpu(3));
/* 0024b4e4: subu a1,s2,a0 */ set(5,sx((uint32_t)cpu(18)-(uint32_t)cpu(4)));
/* 0024b4e8: subu a0,s6,a0 */ set(4,sx((uint32_t)cpu(22)-(uint32_t)cpu(4)));
/* 0024b4ec: addiu a3,a2,0x15 */ set(7,sx((uint32_t)cpu(6)+UINT32_C(0x00000015)));
/* 0024b4f0: addiu a2,a2,0x63 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000063)));
/* 0024b4f4: sll s0,s5,0x1 */ set(16,sx((uint32_t)cpu(21)<<1));
/* 0024b4f8: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b4fc: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b500: li t2,0x63 */ set(10,sx(UINT32_C(0x00000063)));
/* 0024b504: li t3,0x15 */ set(11,sx(UINT32_C(0x00000015)));
/* 0024b508: sw v1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 0024b50c: jal 0x00279a88 */ set(31,UINT64_C(0x0024b514));/* delay 0024b510 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(12));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b50c));
/* 0024b514: addu v0,s0,s5 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));
/* 0024b518: lui t4,0x60 */ set(12,sx(UINT32_C(0x00600000)));
/* 0024b51c: addiu a0,v0,0x3 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000003)));
/* 0024b520: move v1,v0 */ set(3,cpu(2));
/* 0024b524: slti v0,v0,0x0 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 0024b528: lw t5,-0x306c(gp) */ lw(13,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b52c: movn v1,a0,v0 */ if(cpu(2)!=0){set(3,cpu(4));}
/* 0024b530: ori t4,t4,0x6060 */ set(12,cpu(12)|UINT32_C(0x00006060));
/* 0024b534: sra a0,v1,0x2 */ set(4,sx((uint32_t)((int32_t)cpu(3)>>2)));
/* 0024b538: or t4,s1,t4 */ set(12,cpu(17)|cpu(12));
/* 0024b53c: sll a2,a0,0x1 */ set(6,sx((uint32_t)cpu(4)<<1));
/* 0024b540: subu a1,s2,a0 */ set(5,sx((uint32_t)cpu(18)-(uint32_t)cpu(4)));
/* 0024b544: addiu a3,a2,0x15 */ set(7,sx((uint32_t)cpu(6)+UINT32_C(0x00000015)));
/* 0024b548: addiu a2,a2,0x63 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000063)));
/* 0024b54c: subu a0,s6,a0 */ set(4,sx((uint32_t)cpu(22)-(uint32_t)cpu(4)));
/* 0024b550: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b554: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b558: li t2,0x63 */ set(10,sx(UINT32_C(0x00000063)));
/* 0024b55c: li t3,0x15 */ set(11,sx(UINT32_C(0x00000015)));
/* 0024b560: sw t4,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 0024b564: jal 0x00279a88 */ set(31,UINT64_C(0x0024b56c));/* delay 0024b568 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(13));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b564));
/* 0024b56c: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0024b570: lw v1,-0x306c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b574: ori v0,v0,0x3030 */ set(2,cpu(2)|UINT32_C(0x00003030));
/* 0024b578: subu a1,s2,s5 */ set(5,sx((uint32_t)cpu(18)-(uint32_t)cpu(21)));
/* 0024b57c: or s1,s1,v0 */ set(17,cpu(17)|cpu(2));
/* 0024b580: subu a0,s6,s5 */ set(4,sx((uint32_t)cpu(22)-(uint32_t)cpu(21)));
/* 0024b584: addiu a3,s0,0x15 */ set(7,sx((uint32_t)cpu(16)+UINT32_C(0x00000015)));
/* 0024b588: addiu a2,s0,0x63 */ set(6,sx((uint32_t)cpu(16)+UINT32_C(0x00000063)));
/* 0024b58c: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b590: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b594: li t2,0x63 */ set(10,sx(UINT32_C(0x00000063)));
/* 0024b598: li t3,0x15 */ set(11,sx(UINT32_C(0x00000015)));
/* 0024b59c: sw s1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 0024b5a0: jal 0x00279a88 */ set(31,UINT64_C(0x0024b5a8));/* delay 0024b5a4 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b5a0));
/* 0024b5a8: move a0,zero */ set(4,cpu(0));
L_0024b5ac:;
/* 0024b5ac: jal 0x00279980 */ set(31,UINT64_C(0x0024b5b4));/* delay 0024b5b0 */ set(22,cpu(0));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279980),UINT32_C(0x0024b5ac));
/* 0024b5b4: move s1,zero */ set(17,cpu(0));
/* 0024b5b8: lw v0,0x90(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0024b5bc: addiu a2,sp,0x80 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));
/* 0024b5c0: sw zero,0x70(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000070)),(uint32_t)cpu(0));
/* 0024b5c4: sw zero,0x74(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000074)),(uint32_t)cpu(0));
/* 0024b5c8: addiu t1,v0,0x8 */ set(9,sx((uint32_t)cpu(2)+UINT32_C(0x00000008)));
/* 0024b5cc: sw zero,0x78(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000078)),(uint32_t)cpu(0));
/* 0024b5d0: addiu t0,v0,0xc */ set(8,sx((uint32_t)cpu(2)+UINT32_C(0x0000000c)));
/* 0024b5d4: sw zero,0x80(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000080)),(uint32_t)cpu(0));
/* 0024b5d8: sw zero,0x84(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000084)),(uint32_t)cpu(0));
/* 0024b5dc: sw zero,0x88(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000088)),(uint32_t)cpu(0));
/* 0024b5e0: addiu a1,s1,0x90 */ set(5,sx((uint32_t)cpu(17)+UINT32_C(0x00000090)));
/* 0024b5e4: nop  */ 
L_0024b5e8:;
/* 0024b5e8: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 0024b5ec: addu a0,t1,a1 */ set(4,sx((uint32_t)cpu(9)+(uint32_t)cpu(5)));
/* 0024b5f0: slti a3,s1,0x3 */ set(7,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 0024b5f4: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 0024b5f8: beq v0,zero,0x0024b630 */ {int taken=(cpu(2)==cpu(0));/* delay 0024b5fc */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x000000c0)));if(taken){goto L_0024b630;}}
/* 0024b600: andi v0,v1,0xff */ set(2,cpu(3)&UINT32_C(0x000000ff));
/* 0024b604: sltiu v0,v0,0x19 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000019));
/* 0024b608: bne v0,zero,0x0024b630 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024b60c */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_0024b630;}}
/* 0024b610: lbu a0,0x0(a0) */ set(4,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 0024b614: sw v1,0x94(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000094)),(uint32_t)cpu(3));
/* 0024b618: addu v0,t0,a1 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(5)));
/* 0024b61c: addiu s6,s6,0x1 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000001)));
/* 0024b620: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 0024b624: sw a0,-0x10(a2) */ sw(ea(6,(int32_t)UINT32_C(0xfffffff0)),(uint32_t)cpu(4));
/* 0024b628: sw v1,0x0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 0024b62c: addiu a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000004)));
L_0024b630:;
/* 0024b630: bne a3,zero,0x0024b5e8 */ {int taken=(cpu(7)!=cpu(0));/* delay 0024b634 */ set(5,sx((uint32_t)cpu(17)+UINT32_C(0x00000090)));if(taken){goto L_0024b5e8;}}
/* 0024b638: lw a1,-0x30a0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffcf60)));
/* 0024b63c: slti v0,a1,0x9 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 0024b640: bne v0,zero,0x0024b9ac */ {int taken=(cpu(2)!=cpu(0));/* delay 0024b644 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000018));if(taken){goto L_0024b9ac;}}
/* 0024b648: slti v0,a1,0x17 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000017));
/* 0024b64c: beql v0,zero,0x0024b65c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024b650 */ set(21,cpu(0));goto L_0024b65c;}}
/* 0024b654: li v0,0x17 */ set(2,sx(UINT32_C(0x00000017)));
/* 0024b658: subu s5,v0,a1 */ set(21,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
L_0024b65c:;
/* 0024b65c: li v0,0xf */ set(2,sx(UINT32_C(0x0000000f)));
/* 0024b660: sll v1,s5,0x7 */ set(3,sx((uint32_t)cpu(21)<<7));
/* 0024b664: div v1,v0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(2),1,0);
/* 0024b668: li t5,0x80 */ set(13,sx(UINT32_C(0x00000080)));
/* 0024b66c: beql v0,zero,0x0024b674 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024b670 */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x0024b670));goto L_0024b674;}}
L_0024b674:;
/* 0024b674: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b678: lui t4,0x80 */ set(12,sx(UINT32_C(0x00800000)));
/* 0024b67c: li a0,0x5c */ set(4,sx(UINT32_C(0x0000005c)));
/* 0024b680: ori t4,t4,0x8080 */ set(12,cpu(12)|UINT32_C(0x00008080));
/* 0024b684: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b688: li a1,0x64 */ set(5,sx(UINT32_C(0x00000064)));
/* 0024b68c: li a2,0x37 */ set(6,sx(UINT32_C(0x00000037)));
/* 0024b690: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0024b694: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b698: li t1,0x17 */ set(9,sx(UINT32_C(0x00000017)));
/* 0024b69c: li t2,0x37 */ set(10,sx(UINT32_C(0x00000037)));
/* 0024b6a0: li t3,0x16 */ set(11,sx(UINT32_C(0x00000016)));
/* 0024b6a4: mflo v1 */ set(3,nocturneEffectHostLo());
/* 0024b6a8: subu s3,t5,v1 */ set(19,sx((uint32_t)cpu(13)-(uint32_t)cpu(3)));
/* 0024b6ac: sll v0,s3,0x18 */ set(2,sx((uint32_t)cpu(19)<<24));
/* 0024b6b0: or s4,v0,t4 */ set(20,cpu(2)|cpu(12));
/* 0024b6b4: jal 0x00279a88 */ set(31,UINT64_C(0x0024b6bc));/* delay 0024b6b8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b6b4));
/* 0024b6bc: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b6c0: li a0,0x93 */ set(4,sx(UINT32_C(0x00000093)));
/* 0024b6c4: li a1,0x64 */ set(5,sx(UINT32_C(0x00000064)));
/* 0024b6c8: li a2,0x36 */ set(6,sx(UINT32_C(0x00000036)));
/* 0024b6cc: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0024b6d0: li t0,0x39 */ set(8,sx(UINT32_C(0x00000039)));
/* 0024b6d4: li t1,0x17 */ set(9,sx(UINT32_C(0x00000017)));
/* 0024b6d8: li t2,0x36 */ set(10,sx(UINT32_C(0x00000036)));
/* 0024b6dc: li t3,0x16 */ set(11,sx(UINT32_C(0x00000016)));
/* 0024b6e0: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b6e4: jal 0x00279a88 */ set(31,UINT64_C(0x0024b6ec));/* delay 0024b6e8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b6e4));
/* 0024b6ec: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b6f0: li a0,0x5c */ set(4,sx(UINT32_C(0x0000005c)));
/* 0024b6f4: li a1,0x84 */ set(5,sx(UINT32_C(0x00000084)));
/* 0024b6f8: li a2,0x37 */ set(6,sx(UINT32_C(0x00000037)));
/* 0024b6fc: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0024b700: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b704: li t1,0x17 */ set(9,sx(UINT32_C(0x00000017)));
/* 0024b708: li t2,0x37 */ set(10,sx(UINT32_C(0x00000037)));
/* 0024b70c: li t3,0x16 */ set(11,sx(UINT32_C(0x00000016)));
/* 0024b710: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b714: jal 0x00279a88 */ set(31,UINT64_C(0x0024b71c));/* delay 0024b718 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b714));
/* 0024b71c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b720: li a0,0x93 */ set(4,sx(UINT32_C(0x00000093)));
/* 0024b724: li a1,0x84 */ set(5,sx(UINT32_C(0x00000084)));
/* 0024b728: li a2,0x36 */ set(6,sx(UINT32_C(0x00000036)));
/* 0024b72c: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0024b730: li t0,0x39 */ set(8,sx(UINT32_C(0x00000039)));
/* 0024b734: li t1,0x17 */ set(9,sx(UINT32_C(0x00000017)));
/* 0024b738: li t2,0x36 */ set(10,sx(UINT32_C(0x00000036)));
/* 0024b73c: li t3,0x16 */ set(11,sx(UINT32_C(0x00000016)));
/* 0024b740: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b744: jal 0x00279a88 */ set(31,UINT64_C(0x0024b74c));/* delay 0024b748 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b744));
/* 0024b74c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b750: li a0,0x30 */ set(4,sx(UINT32_C(0x00000030)));
/* 0024b754: li a1,0x68 */ set(5,sx(UINT32_C(0x00000068)));
/* 0024b758: li a2,0x27 */ set(6,sx(UINT32_C(0x00000027)));
/* 0024b75c: li a3,0x10 */ set(7,sx(UINT32_C(0x00000010)));
/* 0024b760: li t0,0x97 */ set(8,sx(UINT32_C(0x00000097)));
/* 0024b764: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b768: li t2,0x27 */ set(10,sx(UINT32_C(0x00000027)));
/* 0024b76c: li t3,0x10 */ set(11,sx(UINT32_C(0x00000010)));
/* 0024b770: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b774: jal 0x00279a88 */ set(31,UINT64_C(0x0024b77c));/* delay 0024b778 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b774));
/* 0024b77c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b780: li a0,0x49 */ set(4,sx(UINT32_C(0x00000049)));
/* 0024b784: li a1,0x88 */ set(5,sx(UINT32_C(0x00000088)));
/* 0024b788: li a2,0xe */ set(6,sx(UINT32_C(0x0000000e)));
/* 0024b78c: li a3,0x10 */ set(7,sx(UINT32_C(0x00000010)));
/* 0024b790: li t0,0x9d */ set(8,sx(UINT32_C(0x0000009d)));
/* 0024b794: li t1,0x12 */ set(9,sx(UINT32_C(0x00000012)));
/* 0024b798: li t2,0xe */ set(10,sx(UINT32_C(0x0000000e)));
/* 0024b79c: li t3,0x10 */ set(11,sx(UINT32_C(0x00000010)));
/* 0024b7a0: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b7a4: jal 0x00279a88 */ set(31,UINT64_C(0x0024b7ac));/* delay 0024b7a8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b7a4));
/* 0024b7ac: lw v0,0x94(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000094)));
/* 0024b7b0: beq v0,zero,0x0024b9a4 */ {int taken=(cpu(2)==cpu(0));/* delay 0024b7b4 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));if(taken){goto L_0024b9a4;}}
/* 0024b7b8: li a0,0xdc */ set(4,sx(UINT32_C(0x000000dc)));
/* 0024b7bc: li a1,0x68 */ set(5,sx(UINT32_C(0x00000068)));
/* 0024b7c0: li a2,0x31 */ set(6,sx(UINT32_C(0x00000031)));
/* 0024b7c4: li a3,0x10 */ set(7,sx(UINT32_C(0x00000010)));
/* 0024b7c8: li t0,0x65 */ set(8,sx(UINT32_C(0x00000065)));
/* 0024b7cc: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024b7d0: li t2,0x31 */ set(10,sx(UINT32_C(0x00000031)));
/* 0024b7d4: li t3,0x12 */ set(11,sx(UINT32_C(0x00000012)));
/* 0024b7d8: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b7dc: jal 0x00279a88 */ set(31,UINT64_C(0x0024b7e4));/* delay 0024b7e0 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b7dc));
/* 0024b7e4: li s0,0x64 */ set(16,sx(UINT32_C(0x00000064)));
/* 0024b7e8: li s1,0x2 */ set(17,sx(UINT32_C(0x00000002)));
/* 0024b7ec: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
L_0024b7f0:;
/* 0024b7f0: move a1,s0 */ set(5,cpu(16));
/* 0024b7f4: li a0,0x111 */ set(4,sx(UINT32_C(0x00000111)));
/* 0024b7f8: li a2,0x37 */ set(6,sx(UINT32_C(0x00000037)));
/* 0024b7fc: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0024b800: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024b804: li t1,0x17 */ set(9,sx(UINT32_C(0x00000017)));
/* 0024b808: li t2,0x37 */ set(10,sx(UINT32_C(0x00000037)));
/* 0024b80c: li t3,0x16 */ set(11,sx(UINT32_C(0x00000016)));
/* 0024b810: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b814: jal 0x00279a88 */ set(31,UINT64_C(0x0024b81c));/* delay 0024b818 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b814));
/* 0024b81c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b820: move a1,s0 */ set(5,cpu(16));
/* 0024b824: li a0,0x148 */ set(4,sx(UINT32_C(0x00000148)));
/* 0024b828: li a2,0x53 */ set(6,sx(UINT32_C(0x00000053)));
/* 0024b82c: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0024b830: li t0,0x37 */ set(8,sx(UINT32_C(0x00000037)));
/* 0024b834: li t1,0x17 */ set(9,sx(UINT32_C(0x00000017)));
/* 0024b838: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024b83c: li t3,0x16 */ set(11,sx(UINT32_C(0x00000016)));
/* 0024b840: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b844: jal 0x00279a88 */ set(31,UINT64_C(0x0024b84c));/* delay 0024b848 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b844));
/* 0024b84c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b850: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
/* 0024b854: move a1,s0 */ set(5,cpu(16));
/* 0024b858: addiu s0,s0,0x1a */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x0000001a)));
/* 0024b85c: li a0,0x19b */ set(4,sx(UINT32_C(0x0000019b)));
/* 0024b860: li a2,0x36 */ set(6,sx(UINT32_C(0x00000036)));
/* 0024b864: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0024b868: li t0,0x39 */ set(8,sx(UINT32_C(0x00000039)));
/* 0024b86c: li t1,0x17 */ set(9,sx(UINT32_C(0x00000017)));
/* 0024b870: li t2,0x36 */ set(10,sx(UINT32_C(0x00000036)));
/* 0024b874: li t3,0x16 */ set(11,sx(UINT32_C(0x00000016)));
/* 0024b878: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b87c: jal 0x00279a88 */ set(31,UINT64_C(0x0024b884));/* delay 0024b880 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b87c));
/* 0024b884: bgez s1,0x0024b7f0 */ {int taken=((int64_t)cpu(17)>=0);/* delay 0024b888 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));if(taken){goto L_0024b7f0;}}
/* 0024b88c: li a0,0x13 */ set(4,sx(UINT32_C(0x00000013)));
/* 0024b890: jal 0x001c6160 */ set(31,UINT64_C(0x0024b898));/* delay 0024b894 */ set(17,cpu(0));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c6160),UINT32_C(0x0024b890));
/* 0024b898: blez s6,0x0024b99c */ {int taken=((int64_t)cpu(22)<=0);/* delay 0024b89c */ set(2,sx(UINT32_C(0x003f0000)));if(taken){goto L_0024b99c;}}
/* 0024b8a0: addiu s8,sp,0x70 */ set(30,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));
/* 0024b8a4: addiu s7,v0,-0x7e90 */ set(23,sx((uint32_t)cpu(2)+UINT32_C(0xffff8170)));
/* 0024b8a8: li s4,0x348 */ set(20,sx(UINT32_C(0x00000348)));
/* 0024b8ac: li s3,0x338 */ set(19,sx(UINT32_C(0x00000338)));
/* 0024b8b0: move s2,zero */ set(18,cpu(0));
/* 0024b8b4: lui s5,0x55 */ set(21,sx(UINT32_C(0x00550000)));
L_0024b8b8:;
/* 0024b8b8: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 0024b8bc: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 0024b8c0: addu v0,s8,s0 */ set(2,sx((uint32_t)cpu(30)+(uint32_t)cpu(16)));
/* 0024b8c4: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0024b8c8: beq v1,zero,0x0024b988 */ {int taken=(cpu(3)==cpu(0));/* delay 0024b8cc */ set(2,sx((uint32_t)cpu(3)<<2));if(taken){goto L_0024b988;}}
/* 0024b8d0: addu v0,v0,s7 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(23)));
/* 0024b8d4: lui a3,0xa09d */ set(7,sx(UINT32_C(0xa09d0000)));
/* 0024b8d8: lw t0,0x0(v0) */ lw(8,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0024b8dc: move a1,s3 */ set(5,cpu(19));
/* 0024b8e0: move a2,zero */ set(6,cpu(0));
/* 0024b8e4: ori a3,a3,0xc380 */ set(7,cpu(7)|UINT32_C(0x0000c380));
/* 0024b8e8: move t1,zero */ set(9,cpu(0));
/* 0024b8ec: jal 0x001ca258 */ set(31,UINT64_C(0x0024b8f4));/* delay 0024b8f0 */ set(4,sx(UINT32_C(0x00001210)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001ca258),UINT32_C(0x0024b8ec));
/* 0024b8f4: move a0,v0 */ set(4,cpu(2));
/* 0024b8f8: jal 0x001c7e00 */ set(31,UINT64_C(0x0024b900));/* delay 0024b8fc */ sw(ea(28,(int32_t)UINT32_C(0xffffde50)),(uint32_t)cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c7e00),UINT32_C(0x0024b8f8));
/* 0024b900: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024b908));/* delay 0024b904 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde50)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024b900));
/* 0024b908: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
/* 0024b90c: lw v0,-0x306c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf94)));
/* 0024b910: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 0024b914: li t2,0xb */ set(10,sx(UINT32_C(0x0000000b)));
/* 0024b918: li t3,0xb */ set(11,sx(UINT32_C(0x0000000b)));
/* 0024b91c: li a3,0xb */ set(7,sx(UINT32_C(0x0000000b)));
/* 0024b920: li t0,0xac */ set(8,sx(UINT32_C(0x000000ac)));
/* 0024b924: li t1,0x12 */ set(9,sx(UINT32_C(0x00000012)));
/* 0024b928: addiu a1,s2,0x6b */ set(5,sx((uint32_t)cpu(18)+UINT32_C(0x0000006b)));
/* 0024b92c: li a0,0x197 */ set(4,sx(UINT32_C(0x00000197)));
/* 0024b930: li a2,0xb */ set(6,sx(UINT32_C(0x0000000b)));
/* 0024b934: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0024b938: jal 0x00279a88 */ set(31,UINT64_C(0x0024b940));/* delay 0024b93c */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024b938));
/* 0024b940: addu v0,sp,s0 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(16)));
/* 0024b944: addiu a0,sp,0x60 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 0024b948: lw a2,0x80(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x00000080)));
/* 0024b94c: jal 0x002d5690 */ set(31,UINT64_C(0x0024b954));/* delay 0024b950 */ set(5,sx((uint32_t)cpu(21)+UINT32_C(0x000010f0)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x0024b94c));
/* 0024b954: li a0,0x1ac0 */ set(4,sx(UINT32_C(0x00001ac0)));
/* 0024b958: lui a3,0xa09d */ set(7,sx(UINT32_C(0xa09d0000)));
/* 0024b95c: move a1,s4 */ set(5,cpu(20));
/* 0024b960: move a2,zero */ set(6,cpu(0));
/* 0024b964: ori a3,a3,0xc380 */ set(7,cpu(7)|UINT32_C(0x0000c380));
/* 0024b968: addiu t0,sp,0x60 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 0024b96c: jal 0x001ca430 */ set(31,UINT64_C(0x0024b974));/* delay 0024b970 */ set(9,cpu(0));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001ca430),UINT32_C(0x0024b96c));
/* 0024b974: move a0,v0 */ set(4,cpu(2));
/* 0024b978: jal 0x001c7e00 */ set(31,UINT64_C(0x0024b980));/* delay 0024b97c */ sw(ea(28,(int32_t)UINT32_C(0xffffde50)),(uint32_t)cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c7e00),UINT32_C(0x0024b978));
/* 0024b980: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024b988));/* delay 0024b984 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde50)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024b980));
L_0024b988:;
/* 0024b988: slt v0,s1,s6 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(22));
/* 0024b98c: addiu s4,s4,0xd0 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x000000d0)));
/* 0024b990: addiu s3,s3,0xd0 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x000000d0)));
/* 0024b994: bne v0,zero,0x0024b8b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024b998 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x0000001a)));if(taken){goto L_0024b8b8;}}
L_0024b99c:;
/* 0024b99c: jal 0x001c6160 */ set(31,UINT64_C(0x0024b9a4));/* delay 0024b9a0 */ set(4,sx(UINT32_C(0xffffffff)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c6160),UINT32_C(0x0024b99c));
L_0024b9a4:;
/* 0024b9a4: lw a1,-0x30a0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffcf60)));
/* 0024b9a8: slti v0,a1,0x18 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000018));
L_0024b9ac:;
/* 0024b9ac: bne v0,zero,0x0024bb10 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024b9b0 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000001d));if(taken){goto L_0024bb10;}}
/* 0024b9b4: lwc1 f12,-0x3070(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffcf90)));
/* 0024b9b8: addiu v1,a1,-0x17 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0xffffffe9)));
/* 0024b9bc: slti v0,a1,0x1f */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000001f));
/* 0024b9c0: lui at,0x4180 */ set(1,sx(UINT32_C(0x41800000)));
/* 0024b9c4: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 0024b9c8: add.S f12,f12,f12 */ f[12]=EE_FPU_ADD_S(f[12],f[12]);
/* 0024b9cc: li s5,0x8 */ set(21,sx(UINT32_C(0x00000008)));
/* 0024b9d0: movn s5,v1,v0 */ if(cpu(2)!=0){set(21,cpu(3));}
/* 0024b9d4: jal 0x002c0060 */ set(31,UINT64_C(0x0024b9dc));/* delay 0024b9d8 */ set(16,sx((uint32_t)cpu(21)<<28));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002c0060),UINT32_C(0x0024b9d4));
/* 0024b9dc: lw v1,-0x3068(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024b9e0: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 0024b9e4: li a0,0x27 */ set(4,sx(UINT32_C(0x00000027)));
/* 0024b9e8: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 0024b9ec: li a1,0x5e */ set(5,sx(UINT32_C(0x0000005e)));
/* 0024b9f0: li a2,0x37 */ set(6,sx(UINT32_C(0x00000037)));
/* 0024b9f4: li a3,0x23 */ set(7,sx(UINT32_C(0x00000023)));
/* 0024b9f8: li t0,0x21 */ set(8,sx(UINT32_C(0x00000021)));
/* 0024b9fc: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024ba00: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0024ba04: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0024ba08: li t3,0x23 */ set(11,sx(UINT32_C(0x00000023)));
/* 0024ba0c: li t2,0x37 */ set(10,sx(UINT32_C(0x00000037)));
/* 0024ba10: addiu t6,v0,0x70 */ set(14,sx((uint32_t)cpu(2)+UINT32_C(0x00000070)));
/* 0024ba14: sll t4,t6,0x8 */ set(12,sx((uint32_t)cpu(14)<<8));
/* 0024ba18: sll v0,t6,0x10 */ set(2,sx((uint32_t)cpu(14)<<16));
/* 0024ba1c: or v0,v0,t4 */ set(2,cpu(2)|cpu(12));
/* 0024ba20: or v1,t6,s0 */ set(3,cpu(14)|cpu(16));
/* 0024ba24: or s4,v1,v0 */ set(20,cpu(3)|cpu(2));
/* 0024ba28: jal 0x00279a88 */ set(31,UINT64_C(0x0024ba30));/* delay 0024ba2c */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024ba28));
/* 0024ba30: lwc1 f12,-0x3070(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffcf90)));
/* 0024ba34: lwc1 f0,-0x5cb4(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa34c)));
/* 0024ba38: add.S f12,f12,f12 */ f[12]=EE_FPU_ADD_S(f[12],f[12]);
/* 0024ba3c: jal 0x002c0060 */ set(31,UINT64_C(0x0024ba44));/* delay 0024ba40 */ f[12]=EE_FPU_ADD_S(f[12],f[0]);nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002c0060),UINT32_C(0x0024ba3c));
/* 0024ba44: lw v1,-0x3068(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024ba48: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 0024ba4c: li a0,0x3f */ set(4,sx(UINT32_C(0x0000003f)));
/* 0024ba50: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 0024ba54: li a1,0x80 */ set(5,sx(UINT32_C(0x00000080)));
/* 0024ba58: li a2,0x1f */ set(6,sx(UINT32_C(0x0000001f)));
/* 0024ba5c: li a3,0x1f */ set(7,sx(UINT32_C(0x0000001f)));
/* 0024ba60: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0024ba64: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024ba68: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0024ba6c: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0024ba70: li t3,0x1f */ set(11,sx(UINT32_C(0x0000001f)));
/* 0024ba74: li t2,0x1f */ set(10,sx(UINT32_C(0x0000001f)));
/* 0024ba78: addiu t6,v0,0x70 */ set(14,sx((uint32_t)cpu(2)+UINT32_C(0x00000070)));
/* 0024ba7c: sll t4,t6,0x8 */ set(12,sx((uint32_t)cpu(14)<<8));
/* 0024ba80: sll v0,t6,0x10 */ set(2,sx((uint32_t)cpu(14)<<16));
/* 0024ba84: or v0,v0,t4 */ set(2,cpu(2)|cpu(12));
/* 0024ba88: or v1,t6,s0 */ set(3,cpu(14)|cpu(16));
/* 0024ba8c: or s4,v1,v0 */ set(20,cpu(3)|cpu(2));
/* 0024ba90: jal 0x00279a88 */ set(31,UINT64_C(0x0024ba98));/* delay 0024ba94 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024ba90));
/* 0024ba98: lw v0,0x94(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000094)));
/* 0024ba9c: beq v0,zero,0x0024bb08 */ {int taken=(cpu(2)==cpu(0));/* delay 0024baa0 */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffcf90)));if(taken){goto L_0024bb08;}}
/* 0024baa4: lwc1 f0,-0x5cb0(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa350)));
/* 0024baa8: add.S f12,f12,f12 */ f[12]=EE_FPU_ADD_S(f[12],f[12]);
/* 0024baac: jal 0x002c0060 */ set(31,UINT64_C(0x0024bab4));/* delay 0024bab0 */ f[12]=EE_FPU_ADD_S(f[12],f[0]);nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002c0060),UINT32_C(0x0024baac));
/* 0024bab4: lw v1,-0x3068(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf98)));
/* 0024bab8: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 0024babc: li a1,0x5e */ set(5,sx(UINT32_C(0x0000005e)));
/* 0024bac0: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 0024bac4: li a0,0xd1 */ set(4,sx(UINT32_C(0x000000d1)));
/* 0024bac8: li a2,0x45 */ set(6,sx(UINT32_C(0x00000045)));
/* 0024bacc: li a3,0x23 */ set(7,sx(UINT32_C(0x00000023)));
/* 0024bad0: li t0,0x59 */ set(8,sx(UINT32_C(0x00000059)));
/* 0024bad4: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0024bad8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0024badc: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0024bae0: li t3,0x23 */ set(11,sx(UINT32_C(0x00000023)));
/* 0024bae4: li t2,0x45 */ set(10,sx(UINT32_C(0x00000045)));
/* 0024bae8: addiu t6,v0,0x70 */ set(14,sx((uint32_t)cpu(2)+UINT32_C(0x00000070)));
/* 0024baec: sll t4,t6,0x8 */ set(12,sx((uint32_t)cpu(14)<<8));
/* 0024baf0: sll v0,t6,0x10 */ set(2,sx((uint32_t)cpu(14)<<16));
/* 0024baf4: or v0,v0,t4 */ set(2,cpu(2)|cpu(12));
/* 0024baf8: or v1,t6,s0 */ set(3,cpu(14)|cpu(16));
/* 0024bafc: or s4,v1,v0 */ set(20,cpu(3)|cpu(2));
/* 0024bb00: jal 0x00279a88 */ set(31,UINT64_C(0x0024bb08));/* delay 0024bb04 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024bb00));
L_0024bb08:;
/* 0024bb08: lw a1,-0x30a0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffcf60)));
/* 0024bb0c: slti v0,a1,0x1d */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000001d));
L_0024bb10:;
/* 0024bb10: bne v0,zero,0x0024bbf4 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024bb14 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000015));if(taken){goto L_0024bbf4;}}
/* 0024bb18: li v1,0xf */ set(3,sx(UINT32_C(0x0000000f)));
/* 0024bb1c: addiu a0,a1,-0x1c */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0xffffffe4)));
/* 0024bb20: slti v0,a1,0x2b */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000002b));
/* 0024bb24: li a1,0xf */ set(5,sx(UINT32_C(0x0000000f)));
/* 0024bb28: move s5,v1 */ set(21,cpu(3));
/* 0024bb2c: beql a1,zero,0x0024bb34 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 0024bb30 */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x0024bb30));goto L_0024bb34;}}
L_0024bb34:;
/* 0024bb34: movn s5,a0,v0 */ if(cpu(2)!=0){set(21,cpu(4));}
/* 0024bb38: lw a0,0x90(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0024bb3c: sll v0,s5,0x7 */ set(2,sx((uint32_t)cpu(21)<<7));
/* 0024bb40: lui s0,0x55 */ set(16,sx(UINT32_C(0x00550000)));
/* 0024bb44: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 0024bb48: lw v1,0x98(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0024bb4c: addiu s0,s0,0x10f8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000010f8)));
/* 0024bb50: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024bb54: jal 0x0026a840 */ set(31,UINT64_C(0x0024bb5c));/* delay 0024bb58 */ set(20,cpu(3)|cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x0026a840),UINT32_C(0x0024bb54));
/* 0024bb5c: addiu a0,sp,0x60 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 0024bb60: move a2,v0 */ set(6,cpu(2));
/* 0024bb64: jal 0x002d5690 */ set(31,UINT64_C(0x0024bb6c));/* delay 0024bb68 */ set(5,cpu(16));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x0024bb64));
/* 0024bb6c: li a0,0x7a0 */ set(4,sx(UINT32_C(0x000007a0)));
/* 0024bb70: addiu t0,sp,0x60 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 0024bb74: move a3,s4 */ set(7,cpu(20));
/* 0024bb78: move t1,zero */ set(9,cpu(0));
/* 0024bb7c: move a2,zero */ set(6,cpu(0));
/* 0024bb80: jal 0x001ca430 */ set(31,UINT64_C(0x0024bb88));/* delay 0024bb84 */ set(5,sx(UINT32_C(0x00000348)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001ca430),UINT32_C(0x0024bb80));
/* 0024bb88: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0024bb8c: move a0,v0 */ set(4,cpu(2));
/* 0024bb90: jal 0x001c7e18 */ set(31,UINT64_C(0x0024bb98));/* delay 0024bb94 */ sw(ea(28,(int32_t)UINT32_C(0xffffde50)),(uint32_t)cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c7e18),UINT32_C(0x0024bb90));
/* 0024bb98: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024bba0));/* delay 0024bb9c */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde50)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024bb98));
/* 0024bba0: jal 0x0026a870 */ set(31,UINT64_C(0x0024bba8));/* delay 0024bba4 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000090)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x0026a870),UINT32_C(0x0024bba0));
/* 0024bba8: move a1,s0 */ set(5,cpu(16));
/* 0024bbac: addiu a0,sp,0x60 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 0024bbb0: jal 0x002d5690 */ set(31,UINT64_C(0x0024bbb8));/* delay 0024bbb4 */ set(6,cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002d5690),UINT32_C(0x0024bbb0));
/* 0024bbb8: li a0,0x7a0 */ set(4,sx(UINT32_C(0x000007a0)));
/* 0024bbbc: move a3,s4 */ set(7,cpu(20));
/* 0024bbc0: move a2,zero */ set(6,cpu(0));
/* 0024bbc4: addiu t0,sp,0x60 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 0024bbc8: move t1,zero */ set(9,cpu(0));
/* 0024bbcc: jal 0x001ca430 */ set(31,UINT64_C(0x0024bbd4));/* delay 0024bbd0 */ set(5,sx(UINT32_C(0x00000448)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001ca430),UINT32_C(0x0024bbcc));
/* 0024bbd4: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0024bbd8: move a0,v0 */ set(4,cpu(2));
/* 0024bbdc: jal 0x001c7e18 */ set(31,UINT64_C(0x0024bbe4));/* delay 0024bbe0 */ sw(ea(28,(int32_t)UINT32_C(0xffffde50)),(uint32_t)cpu(2));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c7e18),UINT32_C(0x0024bbdc));
/* 0024bbe4: jal 0x001c6ff8 */ set(31,UINT64_C(0x0024bbec));/* delay 0024bbe8 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffde50)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x001c6ff8),UINT32_C(0x0024bbe4));
/* 0024bbec: lw a1,-0x30a0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffcf60)));
/* 0024bbf0: slti v0,a1,0x15 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000015));
L_0024bbf4:;
/* 0024bbf4: bne v0,zero,0x0024bc64 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024bbf8 */ sw(ea(28,(int32_t)UINT32_C(0xffffcf74)),(uint32_t)cpu(0));if(taken){goto L_0024bc64;}}
/* 0024bbfc: addiu v0,a1,-0x32 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0xffffffce)));
/* 0024bc00: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 0024bc04: sw v0,-0x309c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf64)),(uint32_t)cpu(2));
/* 0024bc08: addiu s0,v1,0x4e80 */ set(16,sx((uint32_t)cpu(3)+UINT32_C(0x00004e80)));
/* 0024bc0c: move s1,zero */ set(17,cpu(0));
/* 0024bc10: li s3,0xd0 */ set(19,sx(UINT32_C(0x000000d0)));
/* 0024bc14: move s2,zero */ set(18,cpu(0));
L_0024bc18:;
/* 0024bc18: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0024bc1c: beq v0,zero,0x0024bc4c */ {int taken=(cpu(2)==cpu(0));/* delay 0024bc20 */ lw(7,ea(28,(int32_t)UINT32_C(0xffffcf60)));if(taken){goto L_0024bc4c;}}
/* 0024bc24: sll v0,s2,0x1 */ set(2,sx((uint32_t)cpu(18)<<1));
/* 0024bc28: lw t0,0x14(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 0024bc2c: move a0,s1 */ set(4,cpu(17));
/* 0024bc30: subu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)-(uint32_t)cpu(2)));
/* 0024bc34: lw t1,0x10(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0024bc38: lw t2,0x90(sp) */ lw(10,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0024bc3c: addiu a3,a3,-0x14 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffec)));
/* 0024bc40: move a2,s3 */ set(6,cpu(19));
/* 0024bc44: jal 0x0024a440 */ set(31,UINT64_C(0x0024bc4c));/* delay 0024bc48 */ set(5,sx(UINT32_C(0x0000003f)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x0024a440),UINT32_C(0x0024bc44));
L_0024bc4c:;
/* 0024bc4c: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 0024bc50: addiu s3,s3,0x28 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000028)));
/* 0024bc54: slti v0,s1,0x4 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0024bc58: addiu s0,s0,0x34 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000034)));
/* 0024bc5c: bne v0,zero,0x0024bc18 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024bc60 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000003)));if(taken){goto L_0024bc18;}}
L_0024bc64:;
/* 0024bc64: lw v1,-0x308c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf74)));
/* 0024bc68: andi v0,v1,0x1 */ set(2,cpu(3)&UINT32_C(0x00000001));
/* 0024bc6c: beq v0,zero,0x0024bc90 */ {int taken=(cpu(2)==cpu(0));/* delay 0024bc70 */ set(4,sx(UINT32_C(0x00000005)));if(taken){goto L_0024bc90;}}
/* 0024bc74: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 0024bc78: jal 0x002c18d8 */ set(31,UINT64_C(0x0024bc80));/* delay 0024bc7c */ set(6,sx(UINT32_C(0x0000003f)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002c18d8),UINT32_C(0x0024bc78));
/* 0024bc80: lw v0,-0x3074(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf8c)));
/* 0024bc84: lw v1,-0x308c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffcf74)));
/* 0024bc88: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0024bc8c: sw v0,-0x3074(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffcf8c)),(uint32_t)cpu(2));
L_0024bc90:;
/* 0024bc90: andi v0,v1,0x2 */ set(2,cpu(3)&UINT32_C(0x00000002));
/* 0024bc94: beq v0,zero,0x0024bca8 */ {int taken=(cpu(2)==cpu(0));/* delay 0024bc98 */ set(4,sx(UINT32_C(0x00000011)));if(taken){goto L_0024bca8;}}
/* 0024bc9c: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 0024bca0: jal 0x002c18d8 */ set(31,UINT64_C(0x0024bca8));/* delay 0024bca4 */ set(6,sx(UINT32_C(0x0000003f)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002c18d8),UINT32_C(0x0024bca0));
L_0024bca8:;
/* 0024bca8: jal 0x0024a2e8 */ set(31,UINT64_C(0x0024bcb0));/* delay 0024bcac */ nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x0024a2e8),UINT32_C(0x0024bca8));
/* 0024bcb0: lw a1,-0x30a0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffcf60)));
/* 0024bcb4: blez a1,0x0024bda0 */ {int taken=((int64_t)cpu(5)<=0);/* delay 0024bcb8 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf68)));if(taken){goto L_0024bda0;}}
/* 0024bcbc: li v1,0xa */ set(3,sx(UINT32_C(0x0000000a)));
/* 0024bcc0: slti v0,a1,0xa */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 0024bcc4: move s5,v1 */ set(21,cpu(3));
/* 0024bcc8: li a0,0x47 */ set(4,sx(UINT32_C(0x00000047)));
/* 0024bccc: movn s5,a1,v0 */ if(cpu(2)!=0){set(21,cpu(5));}
/* 0024bcd0: li a1,0xa */ set(5,sx(UINT32_C(0x0000000a)));
/* 0024bcd4: sll v0,s5,0x7 */ set(2,sx((uint32_t)cpu(21)<<7));
/* 0024bcd8: beql a1,zero,0x0024bce0 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 0024bcdc */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x0024bcdc));goto L_0024bce0;}}
L_0024bce0:;
/* 0024bce0: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 0024bce4: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024bce8: jal 0x00128fd0 */ set(31,UINT64_C(0x0024bcf0));/* delay 0024bcec */ set(19,cpu(2));body_00128fd0();
/* 0024bcf0: move a1,zero */ set(5,cpu(0));
/* 0024bcf4: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 0024bcf8: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 0024bcfc: move t0,zero */ set(8,cpu(0));
/* 0024bd00: move t1,zero */ set(9,cpu(0));
/* 0024bd04: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024bd08: li t3,0x1 */ set(11,sx(UINT32_C(0x00000001)));
/* 0024bd0c: jal 0x00129098 */ set(31,UINT64_C(0x0024bd14));/* delay 0024bd10 */ set(4,sx(UINT32_C(0x00000001)));body_00129098();
/* 0024bd14: jal 0x001291b0 */ set(31,UINT64_C(0x0024bd1c));/* delay 0024bd18 */ set(4,sx(UINT32_C(0x00000001)));body_001291b0();
/* 0024bd1c: sll t3,s3,0x2 */ set(11,sx((uint32_t)cpu(19)<<2));
/* 0024bd20: addu t3,t3,s3 */ set(11,sx((uint32_t)cpu(11)+(uint32_t)cpu(19)));
/* 0024bd24: li v0,0x64 */ set(2,sx(UINT32_C(0x00000064)));
/* 0024bd28: sll t3,t3,0x4 */ set(11,sx((uint32_t)cpu(11)<<4));
/* 0024bd2c: li t4,0x2f */ set(12,sx(UINT32_C(0x0000002f)));
/* 0024bd30: div t3,v0 */ nativeDivide((uint32_t)cpu(11),(uint32_t)cpu(2),1,0);
/* 0024bd34: li v1,0x4c */ set(3,sx(UINT32_C(0x0000004c)));
/* 0024bd38: move a0,zero */ set(4,cpu(0));
/* 0024bd3c: move a1,zero */ set(5,cpu(0));
/* 0024bd40: li a2,0x200 */ set(6,sx(UINT32_C(0x00000200)));
/* 0024bd44: li a3,0x96 */ set(7,sx(UINT32_C(0x00000096)));
/* 0024bd48: move t0,zero */ set(8,cpu(0));
/* 0024bd4c: li t1,0x2f */ set(9,sx(UINT32_C(0x0000002f)));
/* 0024bd50: li t2,0x4c */ set(10,sx(UINT32_C(0x0000004c)));
/* 0024bd54: beql v0,zero,0x0024bd5c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024bd58 */ nocturneBattleRewardPhaseNativeTrap(7u,UINT32_C(0x0024bd58));goto L_0024bd5c;}}
L_0024bd5c:;
/* 0024bd5c: sw t4,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(12));
/* 0024bd60: sw v1,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
/* 0024bd64: sw zero,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0024bd68: sw t4,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(12));
/* 0024bd6c: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 0024bd70: sw zero,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 0024bd74: sw zero,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 0024bd78: sw t4,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(12));
/* 0024bd7c: sw v1,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(3));
/* 0024bd80: sw zero,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(0));
/* 0024bd84: sw zero,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));
/* 0024bd88: mflo t3 */ set(11,nocturneEffectHostLo());
/* 0024bd8c: jal 0x00129c08 */ set(31,UINT64_C(0x0024bd94));/* delay 0024bd90 */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(0));body_00129c08();
/* 0024bd94: jal 0x001291b0 */ set(31,UINT64_C(0x0024bd9c));/* delay 0024bd98 */ set(4,cpu(0));body_001291b0();
/* 0024bd9c: lw v0,-0x3098(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf68)));
L_0024bda0:;
/* 0024bda0: blezl v0,0x0024be58 */ {int taken=((int64_t)cpu(2)<=0);if(taken){/* delay 0024bda4 */ restore(16,ea(29,(int32_t)UINT32_C(0x000000a0)));goto L_0024be58;}}
/* 0024bda8: jal 0x002797b0 */ set(31,UINT64_C(0x0024bdb0));/* delay 0024bdac */ set(4,sx(UINT32_C(0x00000048)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002797b0),UINT32_C(0x0024bda8));
/* 0024bdb0: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0024bdb4: move a1,zero */ set(5,cpu(0));
/* 0024bdb8: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 0024bdbc: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 0024bdc0: move t0,zero */ set(8,cpu(0));
/* 0024bdc4: move t1,zero */ set(9,cpu(0));
/* 0024bdc8: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0024bdcc: jal 0x00279868 */ set(31,UINT64_C(0x0024bdd4));/* delay 0024bdd0 */ set(11,sx(UINT32_C(0x00000001)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279868),UINT32_C(0x0024bdcc));
/* 0024bdd4: jal 0x00279980 */ set(31,UINT64_C(0x0024bddc));/* delay 0024bdd8 */ set(4,cpu(0));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279980),UINT32_C(0x0024bdd4));
/* 0024bddc: lw v0,-0x3098(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffcf68)));
/* 0024bde0: li a0,0x80 */ set(4,sx(UINT32_C(0x00000080)));
/* 0024bde4: lw t4,-0x3064(gp) */ lw(12,ea(28,(int32_t)UINT32_C(0xffffcf9c)));
/* 0024bde8: sll v1,v0,0x3 */ set(3,sx((uint32_t)cpu(2)<<3));
/* 0024bdec: slti v0,v0,0x10 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0024bdf0: move s3,a0 */ set(19,cpu(4));
/* 0024bdf4: subu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(3)));
/* 0024bdf8: movn s3,v1,v0 */ if(cpu(2)!=0){set(19,cpu(3));}
/* 0024bdfc: xori a1,v0,0x0 */ set(5,cpu(2)^UINT32_C(0x00000000));
/* 0024be00: sll s4,s3,0x18 */ set(20,sx((uint32_t)cpu(19)<<24));
/* 0024be04: move s3,zero */ set(19,cpu(0));
/* 0024be08: movn s3,a0,a1 */ if(cpu(5)!=0){set(19,cpu(4));}
/* 0024be0c: move a0,zero */ set(4,cpu(0));
/* 0024be10: sll v1,s3,0x10 */ set(3,sx((uint32_t)cpu(19)<<16));
/* 0024be14: sll v0,s3,0x8 */ set(2,sx((uint32_t)cpu(19)<<8));
/* 0024be18: or v1,s4,v1 */ set(3,cpu(20)|cpu(3));
/* 0024be1c: or v0,s3,v0 */ set(2,cpu(19)|cpu(2));
/* 0024be20: or s4,v1,v0 */ set(20,cpu(3)|cpu(2));
/* 0024be24: move a1,zero */ set(5,cpu(0));
/* 0024be28: li a2,0x200 */ set(6,sx(UINT32_C(0x00000200)));
/* 0024be2c: li a3,0x1c0 */ set(7,sx(UINT32_C(0x000001c0)));
/* 0024be30: move t0,zero */ set(8,cpu(0));
/* 0024be34: move t1,zero */ set(9,cpu(0));
/* 0024be38: li t2,0x100 */ set(10,sx(UINT32_C(0x00000100)));
/* 0024be3c: li t3,0x100 */ set(11,sx(UINT32_C(0x00000100)));
/* 0024be40: sw s4,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));
/* 0024be44: jal 0x00279a88 */ set(31,UINT64_C(0x0024be4c));/* delay 0024be48 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(12));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x00279a88),UINT32_C(0x0024be44));
/* 0024be4c: jal 0x002797b0 */ set(31,UINT64_C(0x0024be54));/* delay 0024be50 */ set(4,sx(UINT32_C(0x00000047)));nocturneBattleRewardPhaseNativeExternal(UINT32_C(0x002797b0),UINT32_C(0x0024be4c));
/* 0024be54: ld s0,0xa0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x000000a0)));
L_0024be58:;
/* 0024be58: ld s1,0xa8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0024be5c: ld s2,0xb0(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0024be60: ld s3,0xb8(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0024be64: ld s4,0xc0(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 0024be68: ld s5,0xc8(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 0024be6c: ld s6,0xd0(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 0024be70: ld s7,0xd8(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x000000d8)));
/* 0024be74: ld s8,0xe0(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x000000e0)));
/* 0024be78: ld ra,0xe8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000e8)));
/* 0024be7c: lwc1 f20,0xf0(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x000000f0)));
/* 0024be80: jr ra */ {uint64_t target=cpu(31);/* delay 0024be84 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleRewardPhaseNativeBody(uint32_t entry){switch(entry){
case UINT32_C(0x00128fd0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00128fd0();return 1u;case UINT32_C(0x00129098):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00129098();return 1u;case UINT32_C(0x001291b0):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001291b0();return 1u;case UINT32_C(0x00129c08):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00129c08();return 1u;case UINT32_C(0x0024b010):if(nocturneBattleRewardPhaseNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0024b010();return 1u;
default:return 0u;}}
void ps2BattleRewardPhaseNative_00128FD0(uint64_t a0){set(4,a0);body_00128fd0();}
void ps2BattleRewardPhaseNative_00129098(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);set(10,a6);set(11,a7);body_00129098();}
void ps2BattleRewardPhaseNative_001291B0(uint64_t a0){set(4,a0);body_001291b0();}
void ps2BattleRewardPhaseNative_00129C08(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);set(10,a6);set(11,a7);body_00129c08();}
void ps2BattleRewardPhaseNative_0024B010(uint64_t a0){set(4,a0);body_0024b010();}
