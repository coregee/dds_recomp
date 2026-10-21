/* Complete5 gauge owner/initializer bodies with actual native dependencies; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_panel_next.h"
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
static uint8_t *at(uint32_t a){return nocturneResolveBattlePanelNextAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelNextSetStackPointer(q[0]);
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






















static void body_00279f10(void);
static void body_0027c230(void);
static void body_0027c350(void);
static void body_0027d8d0(void);
static void body_0027d980(void);
static void body_00279f10(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00279f10: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 00279f14: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279f18: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279f1c: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279f20: move s4,a3 */ set(20,cpu(7));
/* 00279f24: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279f28: move s5,t2 */ set(21,cpu(10));
/* 00279f2c: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279f30: move s6,a0 */ set(22,cpu(4));
/* 00279f34: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00279f38: move s7,a1 */ set(23,cpu(5));
/* 00279f3c: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00279f40: move a0,t0 */ set(4,cpu(8));
/* 00279f44: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279f48: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279f4c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 00279f50: lw v1,0x0(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 00279f54: lw t3,0x4(a2) */ lw(11,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 00279f58: lw t4,0x10(a2) */ lw(12,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 00279f5c: lw v0,0xc(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x0000000c)));
/* 00279f60: lw s3,0x4(t1) */ lw(19,ea(9,(int32_t)UINT32_C(0x00000004)));
/* 00279f64: addu t4,t3,t4 */ set(12,sx((uint32_t)cpu(11)+(uint32_t)cpu(12)));
/* 00279f68: lw s2,0x0(t1) */ lw(18,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 00279f6c: addu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00279f70: subu t4,t4,s3 */ set(12,sx((uint32_t)cpu(12)-(uint32_t)cpu(19)));
/* 00279f74: subu t3,t3,s3 */ set(11,sx((uint32_t)cpu(11)-(uint32_t)cpu(19)));
/* 00279f78: subu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(18)));
/* 00279f7c: subu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 00279f80: mtc1 t4,f0 */ f[0]=(uint32_t)cpu(12);
/* 00279f84: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00279f88: mtc1 v1,f3 */ f[3]=(uint32_t)cpu(3);
/* 00279f8c: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 00279f90: mtc1 t3,f2 */ f[2]=(uint32_t)cpu(11);
/* 00279f94: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 00279f98: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00279f9c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00279fa0: mul.S f0,f0,f12 */ f[0]=EE_FPU_MUL_S(f[0],f[12]);
/* 00279fa4: mul.S f3,f3,f12 */ f[3]=EE_FPU_MUL_S(f[3],f[12]);
/* 00279fa8: mul.S f2,f2,f12 */ f[2]=EE_FPU_MUL_S(f[2],f[12]);
/* 00279fac: mul.S f1,f1,f12 */ f[1]=EE_FPU_MUL_S(f[1],f[12]);
/* 00279fb0: cvt.w.S f4,f3 */ f[4]=EE_FPU_CVT_W_S(f[3]);
/* 00279fb4: mfc1 v0,f4 */ set(2,sx(f[4]));
/* 00279fb8: cvt.w.S f3,f2 */ f[3]=EE_FPU_CVT_W_S(f[2]);
/* 00279fbc: mfc1 v1,f3 */ set(3,sx(f[3]));
/* 00279fc0: cvt.w.S f2,f1 */ f[2]=EE_FPU_CVT_W_S(f[1]);
/* 00279fc4: mfc1 s0,f2 */ set(16,sx(f[2]));
/* 00279fc8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00279fcc: mfc1 s1,f1 */ set(17,sx(f[1]));
/* 00279fd0: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 00279fd4: addu s3,s3,v1 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(3)));
/* 00279fd8: subu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(2)));
/* 00279fdc: jal 0x001abc88 */ set(31,UINT64_C(0x00279fe4));/* delay 00279fe0 */ set(17,sx((uint32_t)cpu(17)-(uint32_t)cpu(3)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x00279fdc));
/* 00279fe4: lw t3,0xc(s4) */ lw(11,ea(20,(int32_t)UINT32_C(0x0000000c)));
/* 00279fe8: addu a0,s2,s6 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(22)));
/* 00279fec: lw t0,0x0(s4) */ lw(8,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 00279ff0: addu a1,s3,s7 */ set(5,sx((uint32_t)cpu(19)+(uint32_t)cpu(23)));
/* 00279ff4: lw t1,0x4(s4) */ lw(9,ea(20,(int32_t)UINT32_C(0x00000004)));
/* 00279ff8: move a2,s0 */ set(6,cpu(16));
/* 00279ffc: lw t2,0x8(s4) */ lw(10,ea(20,(int32_t)UINT32_C(0x00000008)));
/* 0027a000: move a3,s1 */ set(7,cpu(17));
/* 0027a004: sw s5,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(21));
/* 0027a008: jal 0x00279a88 */ set(31,UINT64_C(0x0027a010));/* delay 0027a00c */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027a008));
/* 0027a010: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027a014: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027a018: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027a01c: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0027a020: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0027a024: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027a028: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027a02c: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027a030: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027a034: jr ra */ {uint64_t target=cpu(31);/* delay 0027a038 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_0027c230(void){
uint64_t incoming=cpu(31);
/* 0027c230: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
/* 0027c234: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 0027c238: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0027c23c: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027c240: sb v1,-0x2fcb(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffd035)),(uint8_t)cpu(3));
/* 0027c244: sw a0,-0x2fd8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd028)),(uint32_t)cpu(4));
/* 0027c248: sw v0,-0x2fc8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd038)),(uint32_t)cpu(2));
/* 0027c24c: sw zero,-0x2fe0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd020)),(uint32_t)cpu(0));
/* 0027c250: sw zero,-0x2fd4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd02c)),(uint32_t)cpu(0));
/* 0027c254: sw zero,-0x2fd0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd030)),(uint32_t)cpu(0));
/* 0027c258: sb zero,-0x2fcc(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffd034)),(uint8_t)cpu(0));
/* 0027c25c: sb zero,-0x2fca(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffd036)),(uint8_t)cpu(0));
/* 0027c260: jr ra */ {uint64_t target=cpu(31);/* delay 0027c264 */ sw(ea(28,(int32_t)UINT32_C(0xffffd024)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_0027c350(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 0027c350: addiu sp,sp,-0xc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff40)));
/* 0027c354: sd s5,0x48(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027c358: move s5,a0 */ set(21,cpu(4));
/* 0027c35c: li a0,0x47 */ set(4,sx(UINT32_C(0x00000047)));
/* 0027c360: sd s6,0x50(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027c364: sd s7,0x58(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027c368: move s7,zero */ set(23,cpu(0));
/* 0027c36c: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027c370: li s6,0x15d */ set(22,sx(UINT32_C(0x0000015d)));
/* 0027c374: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0027c378: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0027c37c: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027c380: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027c384: sd s8,0x60(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027c388: sd ra,0x68(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027c38c: swc1 f29,0xb8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b8)),f[29]);
/* 0027c390: swc1 f28,0xb0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b0)),f[28]);
/* 0027c394: swc1 f27,0xa8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000a8)),f[27]);
/* 0027c398: swc1 f26,0xa0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000a0)),f[26]);
/* 0027c39c: swc1 f25,0x98(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000098)),f[25]);
/* 0027c3a0: swc1 f24,0x90(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000090)),f[24]);
/* 0027c3a4: swc1 f23,0x88(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000088)),f[23]);
/* 0027c3a8: swc1 f22,0x80(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000080)),f[22]);
/* 0027c3ac: swc1 f21,0x78(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000078)),f[21]);
/* 0027c3b0: jal 0x002797b0 */ set(31,UINT64_C(0x0027c3b8));/* delay 0027c3b4 */ sw(ea(29,(int32_t)UINT32_C(0x00000070)),f[20]);if(!nocturneBattlePanelOwnerRun(UINT32_C(0x002797b0)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x002797b0),UINT32_C(0x0027c3b0));
/* 0027c3b8: jal 0x00279980 */ set(31,UINT64_C(0x0027c3c0));/* delay 0027c3bc */ set(4,cpu(0));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027c3b8));
/* 0027c3c0: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0027c3c4: move a1,zero */ set(5,cpu(0));
/* 0027c3c8: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 0027c3cc: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 0027c3d0: move t0,zero */ set(8,cpu(0));
/* 0027c3d4: move t1,zero */ set(9,cpu(0));
/* 0027c3d8: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0027c3dc: li t3,0x1 */ set(11,sx(UINT32_C(0x00000001)));
/* 0027c3e0: jal 0x00279868 */ set(31,UINT64_C(0x0027c3e8));/* delay 0027c3e4 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279868)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279868),UINT32_C(0x0027c3e0));
/* 0027c3e8: lbu v0,-0x2fcc(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffd034))));
/* 0027c3ec: beq v0,zero,0x0027c40c */ {int taken=(cpu(2)==cpu(0));/* delay 0027c3f0 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));if(taken){goto L_0027c40c;}}
/* 0027c3f4: lh v0,0x7a(s5) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(21,(int32_t)UINT32_C(0x0000007a))));
/* 0027c3f8: beql v0,zero,0x0027d814 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027c3fc */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));goto L_0027d814;}}
/* 0027c400: jal 0x0027d980 */ set(31,UINT64_C(0x0027c408));/* delay 0027c404 */ body_0027d980();
/* 0027c408: sb zero,-0x2fcc(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffd034)),(uint8_t)cpu(0));
L_0027c40c:;
/* 0027c40c: lw v0,-0x2fd4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd02c)));
/* 0027c410: bnel v0,zero,0x0027c430 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027c414 */ lw(2,ea(21,(int32_t)UINT32_C(0x00000060)));goto L_0027c430;}}
/* 0027c418: lh v0,0x78(s5) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(21,(int32_t)UINT32_C(0x00000078))));
/* 0027c41c: lh v1,0x7a(s5) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(21,(int32_t)UINT32_C(0x0000007a))));
/* 0027c420: sw v0,-0x218c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffde74)),(uint32_t)cpu(2));
/* 0027c424: sw v1,-0x2190(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffde70)),(uint32_t)cpu(3));
/* 0027c428: sw v1,-0x2188(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffde78)),(uint32_t)cpu(3));
/* 0027c42c: lw v0,0x60(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000060)));
L_0027c430:;
/* 0027c430: lw v1,-0x2fdc(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd024)));
/* 0027c434: andi a0,v0,0x8 */ set(4,cpu(2)&UINT32_C(0x00000008));
/* 0027c438: beq v1,a0,0x0027c448 */ {int taken=(cpu(3)==cpu(4));/* delay 0027c43c */ set(2,sx(UINT32_C(0x0000000c)));if(taken){goto L_0027c448;}}
/* 0027c440: sw a0,-0x2fdc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd024)),(uint32_t)cpu(4));
/* 0027c444: sw v0,-0x2fd0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd030)),(uint32_t)cpu(2));
L_0027c448:;
/* 0027c448: lb v0,-0x2fcb(gp) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffd035))));
/* 0027c44c: bne v0,zero,0x0027c470 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027c450 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd038)));if(taken){goto L_0027c470;}}
/* 0027c454: lui v0,0xff00 */ set(2,sx(UINT32_C(0xff000000)));
/* 0027c458: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 0027c45c: beq v0,zero,0x0027d810 */ {int taken=(cpu(2)==cpu(0));/* delay 0027c460 */ set(2,sx(UINT32_C(0xf0000000)));if(taken){goto L_0027d810;}}
/* 0027c464: b 0x0027c48c */ /* delay 0027c468 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));goto L_0027c48c;
L_0027c470:;
/* 0027c470: lui v0,0xff00 */ set(2,sx(UINT32_C(0xff000000)));
/* 0027c474: lui v1,0x8000 */ set(3,sx(UINT32_C(0x80000000)));
/* 0027c478: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 0027c47c: beq v0,v1,0x0027c490 */ {int taken=(cpu(2)==cpu(3));/* delay 0027c480 */ if(taken){goto L_0027c490;}}
/* 0027c484: lui at,0x1000 */ set(1,sx(UINT32_C(0x10000000)));
/* 0027c488: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
L_0027c48c:;
/* 0027c48c: sw a0,-0x2fc8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd038)),(uint32_t)cpu(4));
L_0027c490:;
/* 0027c490: jal 0x00279c00 */ set(31,UINT64_C(0x0027c498));/* delay 0027c494 */ if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279c00)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279c00),UINT32_C(0x0027c490));
/* 0027c498: lw v0,-0x2fe4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd01c)));
/* 0027c49c: beq v0,zero,0x0027c4b0 */ {int taken=(cpu(2)==cpu(0));/* delay 0027c4a0 */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027c4b0;}}
/* 0027c4a4: b 0x0027c4b8 */ /* delay 0027c4a8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000070)));goto L_0027c4b8;
L_0027c4b0:;
/* 0027c4b0: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027c4b4: addiu v0,v0,0x88 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000088)));
L_0027c4b8:;
/* 0027c4b8: jal 0x0027d8d0 */ set(31,UINT64_C(0x0027c4c0));/* delay 0027c4bc */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));body_0027d8d0();
/* 0027c4c0: bne v0,zero,0x0027c590 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027c4c4 */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd020)));if(taken){goto L_0027c590;}}
/* 0027c4c8: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027c4cc: lui s3,0x4f */ set(19,sx(UINT32_C(0x004f0000)));
/* 0027c4d0: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027c4d4: lui s0,0x4f */ set(16,sx(UINT32_C(0x004f0000)));
/* 0027c4d8: lw s1,0x0(v0) */ lw(17,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027c4dc: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027c4e0: addiu s0,s0,-0x8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff8)));
/* 0027c4e4: addiu s3,s3,-0x530 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xfffffad0)));
/* 0027c4e8: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027c4ec: sll s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)<<4));
/* 0027c4f0: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 0027c4f4: jal 0x001abc88 */ set(31,UINT64_C(0x0027c4fc));/* delay 0027c4f8 */ lw(20,ea(21,(int32_t)UINT32_C(0x0000012c)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027c4f4));
/* 0027c4fc: lw t3,0xc(s1) */ lw(11,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027c500: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027c504: addiu s2,s0,0x14 */ set(18,sx((uint32_t)cpu(16)+UINT32_C(0x00000014)));
/* 0027c508: lw a1,0x4(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027c50c: lw a2,0xc(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027c510: addiu a0,a0,0x15d */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000015d)));
/* 0027c514: lw a3,0x10(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0027c518: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027c51c: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027c520: lw t1,0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027c524: lw t2,0x8(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 0027c528: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027c52c: jal 0x00279a88 */ set(31,UINT64_C(0x0027c534));/* delay 0027c530 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027c52c));
/* 0027c534: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027c538: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027c53c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027c540: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027c544: lw s0,0x4(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0027c548: jal 0x001abc88 */ set(31,UINT64_C(0x0027c550));/* delay 0027c54c */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027c548));
/* 0027c550: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027c554: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0027c558: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 0027c55c: lw a1,0x4(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0027c560: lw a3,0x10(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 0027c564: addiu a0,a0,0x15d */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000015d)));
/* 0027c568: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027c56c: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027c570: lw a2,0xc(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 0027c574: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027c578: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027c57c: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027c580: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027c584: jal 0x00279a88 */ set(31,UINT64_C(0x0027c58c));/* delay 0027c588 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027c584));
/* 0027c58c: lw a2,-0x2fe0(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd020)));
L_0027c590:;
/* 0027c590: lw a1,-0x2190(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffde70)));
/* 0027c594: sltu v0,a2,a1 */ set(2,cpu(6)<cpu(5));
/* 0027c598: beq v0,zero,0x0027c9f0 */ {int taken=(cpu(2)==cpu(0));/* delay 0027c59c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffde74)));if(taken){goto L_0027c9f0;}}
/* 0027c5a0: lw v0,-0x2fd0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd030)));
/* 0027c5a4: bne v0,zero,0x0027c9d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027c5a8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));if(taken){goto L_0027c9d8;}}
/* 0027c5ac: beq a2,zero,0x0027c6a4 */ {int taken=(cpu(6)==cpu(0));/* delay 0027c5b0 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));if(taken){goto L_0027c6a4;}}
/* 0027c5b4: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027c5b8: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027c5bc: addiu s2,a0,0x20 */ set(18,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 0027c5c0: addiu s4,v0,-0x530 */ set(20,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027c5c4: addiu s3,s2,0x28 */ set(19,sx((uint32_t)cpu(18)+UINT32_C(0x00000028)));
/* 0027c5c8: lw a3,0x1c(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027c5cc: nop  */ 
L_0027c5d0:;
/* 0027c5d0: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027c5d4: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027c5d8: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027c5dc: lw s0,0x8(a3) */ lw(16,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 0027c5e0: jal 0x001abc88 */ set(31,UINT64_C(0x0027c5e8));/* delay 0027c5e4 */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027c5e0));
/* 0027c5e8: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027c5ec: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027c5f0: addu s0,s0,s4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(20)));
/* 0027c5f4: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027c5f8: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027c5fc: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 0027c600: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0027c604: lw a1,0x4(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0027c608: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027c60c: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027c610: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027c614: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027c618: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027c61c: lw a2,0xc(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 0027c620: lw a3,0x10(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 0027c624: sw s1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));
/* 0027c628: jal 0x00279a88 */ set(31,UINT64_C(0x0027c630));/* delay 0027c62c */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027c628));
/* 0027c630: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027c634: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027c638: lw s0,0x10(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0027c63c: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027c640: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027c644: lw s1,0x128(s5) */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027c648: jal 0x001abc88 */ set(31,UINT64_C(0x0027c650));/* delay 0027c64c */ set(16,sx((uint32_t)cpu(16)<<4));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027c648));
/* 0027c650: addu s0,s0,s4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(20)));
/* 0027c654: lw a0,0x0(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0027c658: lw a1,0x4(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 0027c65c: lw a3,0x10(s3) */ lw(7,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 0027c660: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027c664: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027c668: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027c66c: lw a2,0xc(s3) */ lw(6,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 0027c670: addiu s6,s6,-0x2e */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0xffffffd2)));
/* 0027c674: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027c678: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027c67c: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027c680: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027c684: jal 0x00279a88 */ set(31,UINT64_C(0x0027c68c));/* delay 0027c688 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027c684));
/* 0027c68c: lw a3,0x10(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027c690: lw v0,-0x2fe0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd020)));
/* 0027c694: sltu v0,a3,v0 */ set(2,cpu(7)<cpu(2));
/* 0027c698: bne v0,zero,0x0027c5d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027c69c */ lw(7,ea(29,(int32_t)UINT32_C(0x0000001c)));if(taken){goto L_0027c5d0;}}
/* 0027c6a0: lw a1,-0x2190(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffde70)));
L_0027c6a4:;
/* 0027c6a4: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027c6a8: slt v0,v1,a1 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(5));
/* 0027c6ac: beq v0,zero,0x0027c998 */ {int taken=(cpu(2)==cpu(0));/* delay 0027c6b0 */ if(taken){goto L_0027c998;}}
/* 0027c6b4: lui s3,0x80 */ set(19,sx(UINT32_C(0x00800000)));
/* 0027c6b8: lui at,0x3e80 */ set(1,sx(UINT32_C(0x3e800000)));
/* 0027c6bc: mtc1 at,f26 */ f[26]=(uint32_t)cpu(1);
/* 0027c6c0: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027c6c4: mtc1 at,f25 */ f[25]=(uint32_t)cpu(1);
/* 0027c6c8: lui s4,0x8000 */ set(20,sx(UINT32_C(0x80000000)));
/* 0027c6cc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027c6d0: mtc1 at,f23 */ f[23]=(uint32_t)cpu(1);
/* 0027c6d4: ori s3,s3,0x8080 */ set(19,cpu(19)|UINT32_C(0x00008080));
L_0027c6d8:;
/* 0027c6d8: lw a0,0x10(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027c6dc: lw v1,-0x2fd4(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd02c)));
/* 0027c6e0: sll v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)<<1));
/* 0027c6e4: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 0027c6e8: bltz v1,0x0027c984 */ {int taken=((int64_t)cpu(3)<0);/* delay 0027c6ec */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_0027c984;}}
/* 0027c6f0: beql v0,zero,0x0027c750 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027c6f4 */ set(23,sx((uint32_t)cpu(3)+UINT32_C(0xfffffffc)));goto L_0027c750;}}
/* 0027c6f8: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 0027c6fc: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027c700: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027c704: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027c708: lwc1 f20,-0x5bc4(gp) */ f[20]=word(ea(28,(int32_t)UINT32_C(0xffffa43c)));
/* 0027c70c: mul.S f21,f0,f26 */ f[21]=EE_FPU_MUL_S(f[0],f[26]);
/* 0027c710: mul.S f0,f21,f25 */ f[0]=EE_FPU_MUL_S(f[21],f[25]);
/* 0027c714: c.le.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],2)!=0);
/* 0027c718: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027c71c: mfc1 v0,f2 */ set(2,sx(f[2]));
/* 0027c720: bc1f 0x0027c73c */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027c724 */ set(3,sx((uint32_t)cpu(2)<<24));if(taken){goto L_0027c73c;}}
/* 0027c728: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 0027c72c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027c730: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0027c734: or v0,v0,s4 */ set(2,cpu(2)|cpu(20));
/* 0027c738: sll v1,v0,0x18 */ set(3,sx((uint32_t)cpu(2)<<24));
L_0027c73c:;
/* 0027c73c: lui at,0x4000 */ set(1,sx(UINT32_C(0x40000000)));
/* 0027c740: mtc1 at,f24 */ f[24]=(uint32_t)cpu(1);
/* 0027c744: b 0x0027c818 */ /* delay 0027c748 */ set(30,cpu(3)|cpu(19));goto L_0027c818;
L_0027c750:;
/* 0027c750: slti a0,s7,0x6 */ set(4,(int64_t)cpu(23)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0027c754: beq a0,zero,0x0027c7c0 */ {int taken=(cpu(4)==cpu(0));/* delay 0027c758 */ if(taken){goto L_0027c7c0;}}
/* 0027c75c: mtc1 s7,f2 */ f[2]=(uint32_t)cpu(23);
/* 0027c760: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0027c764: lui at,0x40c0 */ set(1,sx(UINT32_C(0x40c00000)));
/* 0027c768: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027c76c: lwc1 f3,-0x5bc0(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa440)));
/* 0027c770: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027c774: mtc1 at,f5 */ f[5]=(uint32_t)cpu(1);
/* 0027c778: nop  */ 
/* 0027c77c: nop  */ 
/* 0027c780: div.S f21,f2,f1 */ f[21]=EE_FPU_DIV_S(f[2],f[1]);
/* 0027c784: sub.S f0,f23,f21 */ f[0]=EE_FPU_SUB_S(f[23],f[21]);
/* 0027c788: mul.S f4,f0,f25 */ f[4]=EE_FPU_MUL_S(f[0],f[25]);
/* 0027c78c: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 0027c790: c.le.S f5,f4 */ (void)(EE_FPU_COMPARE_S(f[5],f[4],2)!=0);
/* 0027c794: cvt.w.S f1,f4 */ f[1]=EE_FPU_CVT_W_S(f[4]);
/* 0027c798: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0027c79c: bc1f 0x0027c7b4 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027c7a0 */ f[20]=EE_FPU_ADD_S(f[0],f[23]);if(taken){goto L_0027c7b4;}}
/* 0027c7a4: sub.S f0,f4,f5 */ f[0]=EE_FPU_SUB_S(f[4],f[5]);
/* 0027c7a8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027c7ac: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0027c7b0: or v0,v0,s4 */ set(2,cpu(2)|cpu(20));
L_0027c7b4:;
/* 0027c7b4: sll v1,v0,0x18 */ set(3,sx((uint32_t)cpu(2)<<24));
/* 0027c7b8: b 0x0027c7d0 */ /* delay 0027c7bc */ set(30,cpu(3)|cpu(19));goto L_0027c7d0;
L_0027c7c0:;
/* 0027c7c0: lui s8,0x8080 */ set(30,sx(UINT32_C(0x80800000)));
/* 0027c7c4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027c7c8: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 0027c7cc: ori s8,s8,0x8080 */ set(30,cpu(30)|UINT32_C(0x00008080));
L_0027c7d0:;
/* 0027c7d0: slti v0,s7,0x2 */ set(2,(int64_t)cpu(23)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0027c7d4: beq v0,zero,0x0027c7f0 */ {int taken=(cpu(2)==cpu(0));/* delay 0027c7d8 */ set(16,sx((uint32_t)cpu(23)+UINT32_C(0xfffffffe)));if(taken){goto L_0027c7f0;}}
/* 0027c7dc: lui at,0x4000 */ set(1,sx(UINT32_C(0x40000000)));
/* 0027c7e0: mtc1 at,f24 */ f[24]=(uint32_t)cpu(1);
/* 0027c7e4: b 0x0027c81c */ /* delay 0027c7e8 */ goto L_0027c81c;
L_0027c7f0:;
/* 0027c7f0: beq a0,zero,0x0027c810 */ {int taken=(cpu(4)==cpu(0));/* delay 0027c7f4 */ if(taken){goto L_0027c810;}}
/* 0027c7f8: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 0027c7fc: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027c800: mul.S f21,f0,f26 */ f[21]=EE_FPU_MUL_S(f[0],f[26]);
/* 0027c804: sub.S f1,f23,f21 */ f[1]=EE_FPU_SUB_S(f[23],f[21]);
/* 0027c808: b 0x0027c81c */ /* delay 0027c80c */ f[24]=EE_FPU_ADD_S(f[1],f[23]);goto L_0027c81c;
L_0027c810:;
/* 0027c810: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027c814: mtc1 at,f24 */ f[24]=(uint32_t)cpu(1);
L_0027c818:;
/* 0027c818: addiu s0,s7,-0x2 */ set(16,sx((uint32_t)cpu(23)+UINT32_C(0xfffffffe)));
L_0027c81c:;
/* 0027c81c: c.eq.S f20,f23 */ (void)(EE_FPU_COMPARE_S(f[20],f[23],0)!=0);
/* 0027c820: bc1f 0x0027c838 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027c824 */ if(taken){goto L_0027c838;}}
/* 0027c828: jal 0x00279980 */ set(31,UINT64_C(0x0027c830));/* delay 0027c82c */ set(4,cpu(0));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027c828));
/* 0027c830: b 0x0027c844 */ /* delay 0027c834 */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));goto L_0027c844;
L_0027c838:;
/* 0027c838: jal 0x00279980 */ set(31,UINT64_C(0x0027c840));/* delay 0027c83c */ set(4,sx(UINT32_C(0x00000001)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027c838));
/* 0027c840: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
L_0027c844:;
/* 0027c844: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027c848: addiu v1,v1,-0x530 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xfffffad0)));
/* 0027c84c: lw t1,0x128(s5) */ lw(9,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027c850: lw a3,0x8(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 0027c854: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027c858: move t0,s8 */ set(8,cpu(30));
/* 0027c85c: mov.S f12,f20 */ f[12]=f[20];
/* 0027c860: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027c864: move a0,s6 */ set(4,cpu(22));
/* 0027c868: addu a3,a3,v1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(3)));
/* 0027c86c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027c870: jal 0x00279d30 */ set(31,UINT64_C(0x0027c878));/* delay 0027c874 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279d30)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279d30),UINT32_C(0x0027c870));
/* 0027c878: c.eq.S f24,f23 */ (void)(EE_FPU_COMPARE_S(f[24],f[23],0)!=0);
/* 0027c87c: bc1f 0x0027c898 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027c880 */ if(taken){goto L_0027c898;}}
/* 0027c884: jal 0x00279980 */ set(31,UINT64_C(0x0027c88c));/* delay 0027c888 */ set(4,cpu(0));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027c884));
/* 0027c88c: b 0x0027c8a4 */ /* delay 0027c890 */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));goto L_0027c8a4;
L_0027c898:;
/* 0027c898: jal 0x00279980 */ set(31,UINT64_C(0x0027c8a0));/* delay 0027c89c */ set(4,sx(UINT32_C(0x00000001)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027c898));
/* 0027c8a0: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
L_0027c8a4:;
/* 0027c8a4: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027c8a8: lw t1,0x128(s5) */ lw(9,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027c8ac: addiu a0,a0,-0x530 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffad0)));
/* 0027c8b0: lw a3,0x10(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0027c8b4: lui s2,0x4f */ set(18,sx(UINT32_C(0x004f0000)));
/* 0027c8b8: lui t0,0x8080 */ set(8,sx(UINT32_C(0x80800000)));
/* 0027c8bc: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027c8c0: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027c8c4: addiu a2,s2,0x48 */ set(6,sx((uint32_t)cpu(18)+UINT32_C(0x00000048)));
/* 0027c8c8: addu a3,a3,a0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(4)));
/* 0027c8cc: move a0,s6 */ set(4,cpu(22));
/* 0027c8d0: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027c8d4: jal 0x00279d30 */ set(31,UINT64_C(0x0027c8dc));/* delay 0027c8d8 */ f[12]=f[24];if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279d30)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279d30),UINT32_C(0x0027c8d4));
/* 0027c8dc: jal 0x00279980 */ set(31,UINT64_C(0x0027c8e4));/* delay 0027c8e0 */ set(4,sx(UINT32_C(0x00000001)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027c8dc));
/* 0027c8e4: slti v0,s0,0x5 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000005));
/* 0027c8e8: bne v0,zero,0x0027c8f4 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027c8ec */ set(2,sx(UINT32_C(0x00000008)));if(taken){goto L_0027c8f4;}}
/* 0027c8f0: subu s0,v0,s0 */ set(16,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
L_0027c8f4:;
/* 0027c8f4: blez s0,0x0027c980 */ {int taken=((int64_t)cpu(16)<=0);/* delay 0027c8f8 */ lw(5,ea(28,(int32_t)UINT32_C(0xffffde70)));if(taken){goto L_0027c980;}}
/* 0027c8fc: slti v1,s0,0x5 */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000005));
/* 0027c900: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 0027c904: lui at,0x4000 */ set(1,sx(UINT32_C(0x40000000)));
/* 0027c908: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027c90c: movz s0,v0,v1 */ if(cpu(3)==0){set(16,cpu(2));}
/* 0027c910: mov.S f20,f24 */ f[20]=f[24];
/* 0027c914: mtc1 s0,f1 */ f[1]=(uint32_t)cpu(16);
/* 0027c918: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027c91c: sub.S f0,f0,f20 */ f[0]=EE_FPU_SUB_S(f[0],f[20]);
/* 0027c920: nop  */ 
/* 0027c924: nop  */ 
/* 0027c928: div.S f22,f0,f1 */ f[22]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027c92c: blezl s0,0x0027c984 */ {int taken=((int64_t)cpu(16)<=0);if(taken){/* delay 0027c930 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0xffffffd2)));goto L_0027c984;}}
/* 0027c934: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027c938: move s1,s0 */ set(17,cpu(16));
/* 0027c93c: addiu s0,v0,-0x530 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
L_0027c940:;
/* 0027c940: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027c944: lui t0,0x3080 */ set(8,sx(UINT32_C(0x30800000)));
/* 0027c948: lw t1,0x128(s5) */ lw(9,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027c94c: mov.S f12,f20 */ f[12]=f[20];
/* 0027c950: lw a3,0x10(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 0027c954: move a0,s6 */ set(4,cpu(22));
/* 0027c958: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027c95c: addiu a2,s2,0x48 */ set(6,sx((uint32_t)cpu(18)+UINT32_C(0x00000048)));
/* 0027c960: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027c964: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027c968: addu a3,a3,s0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(16)));
/* 0027c96c: jal 0x00279d30 */ set(31,UINT64_C(0x0027c974));/* delay 0027c970 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279d30)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279d30),UINT32_C(0x0027c96c));
/* 0027c974: bne s1,zero,0x0027c940 */ {int taken=(cpu(17)!=cpu(0));/* delay 0027c978 */ f[20]=EE_FPU_ADD_S(f[20],f[22]);if(taken){goto L_0027c940;}}
/* 0027c97c: lw a1,-0x2190(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffde70)));
L_0027c980:;
/* 0027c980: addiu s6,s6,-0x2e */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0xffffffd2)));
L_0027c984:;
/* 0027c984: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027c988: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027c98c: slt v0,v1,a1 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(5));
/* 0027c990: bne v0,zero,0x0027c6d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027c994 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));if(taken){goto L_0027c6d8;}}
L_0027c998:;
/* 0027c998: jal 0x00279980 */ set(31,UINT64_C(0x0027c9a0));/* delay 0027c99c */ set(4,cpu(0));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027c998));
/* 0027c9a0: lw a1,-0x2190(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffde70)));
/* 0027c9a4: lw a2,-0x2fe0(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd020)));
/* 0027c9a8: lw v0,-0x2fd4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd02c)));
/* 0027c9ac: subu v1,a1,a2 */ set(3,sx((uint32_t)cpu(5)-(uint32_t)cpu(6)));
/* 0027c9b0: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 0027c9b4: addiu a0,v0,0x1 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027c9b8: addiu v1,v1,0xd */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x0000000d)));
/* 0027c9bc: slt v0,a0,v1 */ set(2,(int64_t)cpu(4)<(int64_t)cpu(3));
/* 0027c9c0: bnel v0,zero,0x0027cecc */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027c9c4 */ sw(ea(28,(int32_t)UINT32_C(0xffffd02c)),(uint32_t)cpu(4));goto L_0027cecc;}}
/* 0027c9c8: move a2,a1 */ set(6,cpu(5));
/* 0027c9cc: sw zero,-0x2fd4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd02c)),(uint32_t)cpu(0));
/* 0027c9d0: b 0x0027cecc */ /* delay 0027c9d4 */ sw(ea(28,(int32_t)UINT32_C(0xffffd020)),(uint32_t)cpu(6));goto L_0027cecc;
L_0027c9d8:;
/* 0027c9d8: bne v0,zero,0x0027cecc */ {int taken=(cpu(2)!=cpu(0));/* delay 0027c9dc */ sw(ea(28,(int32_t)UINT32_C(0xffffd030)),(uint32_t)cpu(2));if(taken){goto L_0027cecc;}}
/* 0027c9e0: lw v0,0x60(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000060)));
/* 0027c9e4: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 0027c9e8: b 0x0027cecc */ /* delay 0027c9ec */ sw(ea(28,(int32_t)UINT32_C(0xffffd01c)),(uint32_t)cpu(2));goto L_0027cecc;
L_0027c9f0:;
/* 0027c9f0: blez v0,0x0027cae0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0027c9f4 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));if(taken){goto L_0027cae0;}}
/* 0027c9f8: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027c9fc: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027ca00: addiu s2,a0,0x20 */ set(18,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 0027ca04: addiu s4,v0,-0x530 */ set(20,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027ca08: addiu s3,s2,0x28 */ set(19,sx((uint32_t)cpu(18)+UINT32_C(0x00000028)));
/* 0027ca0c: lw a3,0x1c(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x0000001c)));
L_0027ca10:;
/* 0027ca10: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027ca14: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027ca18: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027ca1c: lw s0,0x8(a3) */ lw(16,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 0027ca20: jal 0x001abc88 */ set(31,UINT64_C(0x0027ca28));/* delay 0027ca24 */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027ca20));
/* 0027ca28: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027ca2c: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027ca30: addu s0,s0,s4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(20)));
/* 0027ca34: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027ca38: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027ca3c: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 0027ca40: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0027ca44: lw a1,0x4(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0027ca48: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027ca4c: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027ca50: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027ca54: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027ca58: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027ca5c: lw a2,0xc(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 0027ca60: lw a3,0x10(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 0027ca64: sw s1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));
/* 0027ca68: jal 0x00279a88 */ set(31,UINT64_C(0x0027ca70));/* delay 0027ca6c */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027ca68));
/* 0027ca70: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027ca74: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027ca78: lw s0,0x10(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0027ca7c: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027ca80: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027ca84: lw s1,0x128(s5) */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027ca88: jal 0x001abc88 */ set(31,UINT64_C(0x0027ca90));/* delay 0027ca8c */ set(16,sx((uint32_t)cpu(16)<<4));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027ca88));
/* 0027ca90: addu s0,s0,s4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(20)));
/* 0027ca94: lw a0,0x0(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0027ca98: lw a1,0x4(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 0027ca9c: lw a3,0x10(s3) */ lw(7,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 0027caa0: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027caa4: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027caa8: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027caac: lw a2,0xc(s3) */ lw(6,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 0027cab0: addiu s6,s6,-0x2e */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0xffffffd2)));
/* 0027cab4: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027cab8: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027cabc: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027cac0: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027cac4: jal 0x00279a88 */ set(31,UINT64_C(0x0027cacc));/* delay 0027cac8 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027cac4));
/* 0027cacc: lw a3,0x10(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027cad0: lw v0,-0x218c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffde74)));
/* 0027cad4: slt v0,a3,v0 */ set(2,(int64_t)cpu(7)<(int64_t)cpu(2));
/* 0027cad8: bne v0,zero,0x0027ca10 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027cadc */ lw(7,ea(29,(int32_t)UINT32_C(0x0000001c)));if(taken){goto L_0027ca10;}}
L_0027cae0:;
/* 0027cae0: lw v0,-0x2188(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffde78)));
/* 0027cae4: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027cae8: slt v0,v1,v0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(2));
/* 0027caec: beq v0,zero,0x0027cec8 */ {int taken=(cpu(2)==cpu(0));/* delay 0027caf0 */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd020)));if(taken){goto L_0027cec8;}}
/* 0027caf4: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027caf8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027cafc: mtc1 at,f27 */ f[27]=(uint32_t)cpu(1);
/* 0027cb00: lui at,0x3fa0 */ set(1,sx(UINT32_C(0x3fa00000)));
/* 0027cb04: mtc1 at,f29 */ f[29]=(uint32_t)cpu(1);
/* 0027cb08: addiu s8,a0,0x20 */ set(30,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 0027cb0c: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0027cb10: mtc1 at,f28 */ f[28]=(uint32_t)cpu(1);
/* 0027cb14: lw a3,0x1c(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x0000001c)));
L_0027cb18:;
/* 0027cb18: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027cb1c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027cb20: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027cb24: lw s0,0x8(a3) */ lw(16,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 0027cb28: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027cb2c: addiu v0,v0,-0x530 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027cb30: lw s1,0x128(s5) */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027cb34: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027cb38: jal 0x001abc88 */ set(31,UINT64_C(0x0027cb40));/* delay 0027cb3c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027cb38));
/* 0027cb40: lw a0,0x0(s8) */ lw(4,ea(30,(int32_t)UINT32_C(0x00000000)));
/* 0027cb44: lw a1,0x4(s8) */ lw(5,ea(30,(int32_t)UINT32_C(0x00000004)));
/* 0027cb48: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027cb4c: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027cb50: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027cb54: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027cb58: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027cb5c: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027cb60: lw a2,0xc(s8) */ lw(6,ea(30,(int32_t)UINT32_C(0x0000000c)));
/* 0027cb64: lw a3,0x10(s8) */ lw(7,ea(30,(int32_t)UINT32_C(0x00000010)));
/* 0027cb68: sw s1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));
/* 0027cb6c: jal 0x00279a88 */ set(31,UINT64_C(0x0027cb74));/* delay 0027cb70 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027cb6c));
/* 0027cb74: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027cb78: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027cb7c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027cb80: lui a3,0x4f */ set(7,sx(UINT32_C(0x004f0000)));
/* 0027cb84: lw s0,0x10(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0027cb88: addiu a3,a3,-0x530 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffad0)));
/* 0027cb8c: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027cb90: lw s1,0x128(s5) */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027cb94: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027cb98: jal 0x001abc88 */ set(31,UINT64_C(0x0027cba0));/* delay 0027cb9c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(7)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027cb98));
/* 0027cba0: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027cba4: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027cba8: addiu v1,v1,0x48 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000048)));
/* 0027cbac: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027cbb0: lw a0,0x0(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0027cbb4: lw a1,0x4(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0027cbb8: lw a2,0xc(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 0027cbbc: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027cbc0: lw a3,0x10(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0027cbc4: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027cbc8: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027cbcc: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027cbd0: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027cbd4: jal 0x00279a88 */ set(31,UINT64_C(0x0027cbdc));/* delay 0027cbd8 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027cbd4));
/* 0027cbdc: jal 0x00279980 */ set(31,UINT64_C(0x0027cbe4));/* delay 0027cbe0 */ set(4,sx(UINT32_C(0x00000001)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027cbdc));
/* 0027cbe4: lw v1,0x70(s5) */ lw(3,ea(21,(int32_t)UINT32_C(0x00000070)));
/* 0027cbe8: li v0,0xb */ set(2,sx(UINT32_C(0x0000000b)));
/* 0027cbec: divu v1,v0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(2),0,0);
/* 0027cbf0: beql v0,zero,0x0027cbf8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027cbf4 */ nocturneBattlePanelNextTrap(7u,UINT32_C(0x0027cbf4));goto L_0027cbf8;}}
L_0027cbf8:;
/* 0027cbf8: mfhi s0 */ set(16,nocturneEffectHostHi());
/* 0027cbfc: slti v1,s0,0x5 */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000005));
/* 0027cc00: beq v1,zero,0x0027cc30 */ {int taken=(cpu(3)==cpu(0));/* delay 0027cc04 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0xfffffffb)));if(taken){goto L_0027cc30;}}
/* 0027cc08: mtc1 s0,f1 */ f[1]=(uint32_t)cpu(16);
/* 0027cc0c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027cc10: lui at,0x40a0 */ set(1,sx(UINT32_C(0x40a00000)));
/* 0027cc14: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027cc18: nop  */ 
/* 0027cc1c: nop  */ 
/* 0027cc20: div.S f23,f1,f0 */ f[23]=EE_FPU_DIV_S(f[1],f[0]);
/* 0027cc24: b 0x0027cc54 */ /* delay 0027cc28 */ set(3,sx(UINT32_C(0x004f0000)));goto L_0027cc54;
L_0027cc30:;
/* 0027cc30: lui at,0x40c0 */ set(1,sx(UINT32_C(0x40c00000)));
/* 0027cc34: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027cc38: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0027cc3c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027cc40: nop  */ 
/* 0027cc44: nop  */ 
/* 0027cc48: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027cc4c: sub.S f23,f27,f0 */ f[23]=EE_FPU_SUB_S(f[27],f[0]);
/* 0027cc50: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
L_0027cc54:;
/* 0027cc54: sll s3,s0,0x4 */ set(19,sx((uint32_t)cpu(16)<<4));
/* 0027cc58: addiu v1,v1,0x628 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000628)));
/* 0027cc5c: lui s2,0x80 */ set(18,sx(UINT32_C(0x00800000)));
/* 0027cc60: addu v0,s3,v1 */ set(2,sx((uint32_t)cpu(19)+(uint32_t)cpu(3)));
/* 0027cc64: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027cc68: lwc1 f1,0x4(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000004)));
/* 0027cc6c: mov.S f21,f23 */ f[21]=f[23];
/* 0027cc70: lui at,0x4240 */ set(1,sx(UINT32_C(0x42400000)));
/* 0027cc74: mtc1 at,f26 */ f[26]=(uint32_t)cpu(1);
/* 0027cc78: lui s7,0x8000 */ set(23,sx(UINT32_C(0x80000000)));
/* 0027cc7c: sub.S f1,f1,f27 */ f[1]=EE_FPU_SUB_S(f[1],f[27]);
/* 0027cc80: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027cc84: mtc1 at,f24 */ f[24]=(uint32_t)cpu(1);
/* 0027cc88: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0027cc8c: mtc1 at,f25 */ f[25]=(uint32_t)cpu(1);
/* 0027cc90: ori s2,s2,0x8080 */ set(18,cpu(18)|UINT32_C(0x00008080));
/* 0027cc94: addiu s4,a0,-0x530 */ set(20,sx((uint32_t)cpu(4)+UINT32_C(0xfffffad0)));
/* 0027cc98: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
/* 0027cc9c: mul.S f1,f1,f29 */ f[1]=EE_FPU_MUL_S(f[1],f[29]);
/* 0027cca0: add.S f20,f1,f27 */ f[20]=EE_FPU_ADD_S(f[1],f[27]);
/* 0027cca4: sub.S f0,f20,f27 */ f[0]=EE_FPU_SUB_S(f[20],f[27]);
/* 0027cca8: mul.S f22,f0,f28 */ f[22]=EE_FPU_MUL_S(f[0],f[28]);
/* 0027ccac: nop  */ 
L_0027ccb0:;
/* 0027ccb0: mul.S f0,f21,f26 */ f[0]=EE_FPU_MUL_S(f[21],f[26]);
/* 0027ccb4: c.le.S f24,f0 */ (void)(EE_FPU_COMPARE_S(f[24],f[0],2)!=0);
/* 0027ccb8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027ccbc: mfc1 t0,f1 */ set(8,sx(f[1]));
/* 0027ccc0: bc1f 0x0027ccd8 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027ccc4 */ f[21]=EE_FPU_MUL_S(f[21],f[25]);if(taken){goto L_0027ccd8;}}
/* 0027ccc8: sub.S f0,f0,f24 */ f[0]=EE_FPU_SUB_S(f[0],f[24]);
/* 0027cccc: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027ccd0: mfc1 t0,f1 */ set(8,sx(f[1]));
/* 0027ccd4: or t0,t0,s7 */ set(8,cpu(8)|cpu(23));
L_0027ccd8:;
/* 0027ccd8: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027ccdc: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027cce0: sll t0,t0,0x18 */ set(8,sx((uint32_t)cpu(8)<<24));
/* 0027cce4: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027cce8: lw a3,0x8(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 0027ccec: mov.S f12,f20 */ f[12]=f[20];
/* 0027ccf0: or t0,t0,s2 */ set(8,cpu(8)|cpu(18));
/* 0027ccf4: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027ccf8: move a0,s6 */ set(4,cpu(22));
/* 0027ccfc: addu a3,a3,s4 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(20)));
/* 0027cd00: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027cd04: addiu a2,v1,0x20 */ set(6,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 0027cd08: addiu t1,gp,-0x2ff8 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027cd0c: jal 0x00279f10 */ set(31,UINT64_C(0x0027cd14));/* delay 0027cd10 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));body_00279f10();
/* 0027cd14: bgez s1,0x0027ccb0 */ {int taken=((int64_t)cpu(17)>=0);/* delay 0027cd18 */ f[20]=EE_FPU_SUB_S(f[20],f[22]);if(taken){goto L_0027ccb0;}}
/* 0027cd1c: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
/* 0027cd20: bne s0,a0,0x0027cd70 */ {int taken=(cpu(16)!=cpu(4));/* delay 0027cd24 */ set(3,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027cd70;}}
/* 0027cd28: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027cd2c: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027cd30: lui t0,0x3080 */ set(8,sx(UINT32_C(0x30800000)));
/* 0027cd34: addiu v1,v1,-0x530 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xfffffad0)));
/* 0027cd38: lw a3,0x8(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 0027cd3c: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027cd40: lui at,0x3fa0 */ set(1,sx(UINT32_C(0x3fa00000)));
/* 0027cd44: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0027cd48: move a0,s6 */ set(4,cpu(22));
/* 0027cd4c: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027cd50: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027cd54: addu a3,a3,v1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(3)));
/* 0027cd58: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027cd5c: addiu a2,v0,0x20 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 0027cd60: addiu t1,gp,-0x2ff8 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027cd64: jal 0x00279f10 */ set(31,UINT64_C(0x0027cd6c));/* delay 0027cd68 */ set(8,cpu(8)|UINT32_C(0x00008080));body_00279f10();
/* 0027cd6c: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
L_0027cd70:;
/* 0027cd70: lui s2,0x80 */ set(18,sx(UINT32_C(0x00800000)));
/* 0027cd74: addiu v1,v1,0x628 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000628)));
/* 0027cd78: mov.S f21,f23 */ f[21]=f[23];
/* 0027cd7c: addu v0,s3,v1 */ set(2,sx((uint32_t)cpu(19)+(uint32_t)cpu(3)));
/* 0027cd80: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027cd84: lwc1 f1,0x0(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027cd88: lui s4,0x8000 */ set(20,sx(UINT32_C(0x80000000)));
/* 0027cd8c: lui at,0x4240 */ set(1,sx(UINT32_C(0x42400000)));
/* 0027cd90: mtc1 at,f25 */ f[25]=(uint32_t)cpu(1);
/* 0027cd94: ori s2,s2,0x8080 */ set(18,cpu(18)|UINT32_C(0x00008080));
/* 0027cd98: sub.S f1,f1,f27 */ f[1]=EE_FPU_SUB_S(f[1],f[27]);
/* 0027cd9c: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027cda0: mtc1 at,f23 */ f[23]=(uint32_t)cpu(1);
/* 0027cda4: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0027cda8: mtc1 at,f24 */ f[24]=(uint32_t)cpu(1);
/* 0027cdac: addiu s3,a0,-0x530 */ set(19,sx((uint32_t)cpu(4)+UINT32_C(0xfffffad0)));
/* 0027cdb0: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
/* 0027cdb4: mul.S f1,f1,f29 */ f[1]=EE_FPU_MUL_S(f[1],f[29]);
/* 0027cdb8: add.S f20,f1,f27 */ f[20]=EE_FPU_ADD_S(f[1],f[27]);
/* 0027cdbc: sub.S f0,f20,f27 */ f[0]=EE_FPU_SUB_S(f[20],f[27]);
/* 0027cdc0: mul.S f22,f0,f28 */ f[22]=EE_FPU_MUL_S(f[0],f[28]);
/* 0027cdc4: nop  */ 
L_0027cdc8:;
/* 0027cdc8: mul.S f0,f21,f25 */ f[0]=EE_FPU_MUL_S(f[21],f[25]);
/* 0027cdcc: c.le.S f23,f0 */ (void)(EE_FPU_COMPARE_S(f[23],f[0],2)!=0);
/* 0027cdd0: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027cdd4: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0027cdd8: bc1f 0x0027cdf0 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027cddc */ f[21]=EE_FPU_MUL_S(f[21],f[24]);if(taken){goto L_0027cdf0;}}
/* 0027cde0: sub.S f0,f0,f23 */ f[0]=EE_FPU_SUB_S(f[0],f[23]);
/* 0027cde4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027cde8: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0027cdec: or v0,v0,s4 */ set(2,cpu(2)|cpu(20));
L_0027cdf0:;
/* 0027cdf0: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027cdf4: sll v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)<<24));
/* 0027cdf8: or v0,v0,s2 */ set(2,cpu(2)|cpu(18));
/* 0027cdfc: mov.S f12,f20 */ f[12]=f[20];
/* 0027ce00: lw a3,0x10(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0027ce04: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 0027ce08: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027ce0c: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027ce10: move a0,s6 */ set(4,cpu(22));
/* 0027ce14: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027ce18: addu a3,a3,s3 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(19)));
/* 0027ce1c: lw t0,0x14(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027ce20: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027ce24: addiu a2,v0,0x48 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00000048)));
/* 0027ce28: addiu t1,gp,-0x2ff8 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027ce2c: jal 0x00279f10 */ set(31,UINT64_C(0x0027ce34));/* delay 0027ce30 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));body_00279f10();
/* 0027ce34: bgez s1,0x0027cdc8 */ {int taken=((int64_t)cpu(17)>=0);/* delay 0027ce38 */ f[20]=EE_FPU_SUB_S(f[20],f[22]);if(taken){goto L_0027cdc8;}}
/* 0027ce3c: li v1,0x6 */ set(3,sx(UINT32_C(0x00000006)));
/* 0027ce40: bne s0,v1,0x0027ce9c */ {int taken=(cpu(16)!=cpu(3));/* delay 0027ce44 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_0027ce9c;}}
/* 0027ce48: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027ce4c: lui t0,0x3080 */ set(8,sx(UINT32_C(0x30800000)));
/* 0027ce50: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027ce54: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027ce58: lw a3,0x10(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0027ce5c: move a0,s6 */ set(4,cpu(22));
/* 0027ce60: sw t0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(8));
/* 0027ce64: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027ce68: addiu v0,v0,-0x530 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027ce6c: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027ce70: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027ce74: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 0027ce78: lui at,0x3fa0 */ set(1,sx(UINT32_C(0x3fa00000)));
/* 0027ce7c: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0027ce80: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027ce84: move v0,t0 */ set(2,cpu(8));
/* 0027ce88: addiu a2,v1,0x48 */ set(6,sx((uint32_t)cpu(3)+UINT32_C(0x00000048)));
/* 0027ce8c: addiu t1,gp,-0x2ff8 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027ce90: jal 0x00279f10 */ set(31,UINT64_C(0x0027ce98));/* delay 0027ce94 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));body_00279f10();
/* 0027ce98: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
L_0027ce9c:;
/* 0027ce9c: move a0,zero */ set(4,cpu(0));
/* 0027cea0: addiu s6,s6,-0x2e */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0xffffffd2)));
/* 0027cea4: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027cea8: jal 0x00279980 */ set(31,UINT64_C(0x0027ceb0));/* delay 0027ceac */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027cea8));
/* 0027ceb0: lw a0,0x10(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027ceb4: lw v0,-0x2188(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffde78)));
/* 0027ceb8: slt v0,a0,v0 */ set(2,(int64_t)cpu(4)<(int64_t)cpu(2));
/* 0027cebc: bne v0,zero,0x0027cb18 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027cec0 */ lw(7,ea(29,(int32_t)UINT32_C(0x0000001c)));if(taken){goto L_0027cb18;}}
/* 0027cec4: lw a2,-0x2fe0(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd020)));
L_0027cec8:;
/* 0027cec8: lw a1,-0x2190(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffde70)));
L_0027cecc:;
/* 0027cecc: sltu v0,a1,a2 */ set(2,cpu(5)<cpu(6));
/* 0027ced0: beq v0,zero,0x0027d7b0 */ {int taken=(cpu(2)==cpu(0));/* delay 0027ced4 */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));if(taken){goto L_0027d7b0;}}
/* 0027ced8: bne a1,v0,0x0027d350 */ {int taken=(cpu(5)!=cpu(2));/* delay 0027cedc */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd02c)));if(taken){goto L_0027d350;}}
/* 0027cee0: slti v0,a1,0x8 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0027cee4: beq v0,zero,0x0027cf60 */ {int taken=(cpu(2)==cpu(0));/* delay 0027cee8 */ set(4,cpu(5));if(taken){goto L_0027cf60;}}
/* 0027ceec: mtc1 a1,f3 */ f[3]=(uint32_t)cpu(5);
/* 0027cef0: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027cef4: lui at,0x3e00 */ set(1,sx(UINT32_C(0x3e000000)));
/* 0027cef8: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027cefc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027cf00: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027cf04: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027cf08: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027cf0c: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027cf10: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027cf14: mul.S f21,f3,f1 */ f[21]=EE_FPU_MUL_S(f[3],f[1]);
/* 0027cf18: sub.S f0,f0,f21 */ f[0]=EE_FPU_SUB_S(f[0],f[21]);
/* 0027cf1c: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0027cf20: c.le.S f4,f0 */ (void)(EE_FPU_COMPARE_S(f[4],f[0],2)!=0);
/* 0027cf24: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027cf28: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027cf2c: bc1f 0x0027cf4c */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027cf30 */ set(2,sx(UINT32_C(0x00800000)));if(taken){goto L_0027cf4c;}}
/* 0027cf34: sub.S f0,f0,f4 */ f[0]=EE_FPU_SUB_S(f[0],f[4]);
/* 0027cf38: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027cf3c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027cf40: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027cf44: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027cf48: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
L_0027cf4c:;
/* 0027cf4c: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 0027cf50: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027cf54: b 0x0027cf64 */ /* delay 0027cf58 */ set(30,cpu(3)|cpu(2));goto L_0027cf64;
L_0027cf60:;
/* 0027cf60: move s8,zero */ set(30,cpu(0));
L_0027cf64:;
/* 0027cf64: slti v0,a0,0x6 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0027cf68: beq v0,zero,0x0027cfe8 */ {int taken=(cpu(2)==cpu(0));/* delay 0027cf6c */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffb)));if(taken){goto L_0027cfe8;}}
/* 0027cf70: mtc1 a0,f0 */ f[0]=(uint32_t)cpu(4);
/* 0027cf74: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027cf78: lui at,0x40a0 */ set(1,sx(UINT32_C(0x40a00000)));
/* 0027cf7c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027cf80: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027cf84: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027cf88: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027cf8c: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027cf90: nop  */ 
/* 0027cf94: nop  */ 
/* 0027cf98: div.S f21,f0,f1 */ f[21]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027cf9c: mul.S f0,f21,f2 */ f[0]=EE_FPU_MUL_S(f[21],f[2]);
/* 0027cfa0: c.le.S f3,f0 */ (void)(EE_FPU_COMPARE_S(f[3],f[0],2)!=0);
/* 0027cfa4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027cfa8: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027cfac: bc1f 0x0027cfcc */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027cfb0 */ set(2,sx(UINT32_C(0x00800000)));if(taken){goto L_0027cfcc;}}
/* 0027cfb4: sub.S f0,f0,f3 */ f[0]=EE_FPU_SUB_S(f[0],f[3]);
/* 0027cfb8: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027cfbc: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027cfc0: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027cfc4: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027cfc8: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
L_0027cfcc:;
/* 0027cfcc: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 0027cfd0: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027cfd4: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027cfd8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027cfdc: mtc1 at,f24 */ f[24]=(uint32_t)cpu(1);
/* 0027cfe0: b 0x0027d06c */ /* delay 0027cfe4 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));goto L_0027d06c;
L_0027cfe8:;
/* 0027cfe8: lui at,0x4140 */ set(1,sx(UINT32_C(0x41400000)));
/* 0027cfec: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027cff0: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 0027cff4: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027cff8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027cffc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027d000: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027d004: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027d008: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027d00c: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027d010: nop  */ 
/* 0027d014: nop  */ 
/* 0027d018: div.S f21,f1,f3 */ f[21]=EE_FPU_DIV_S(f[1],f[3]);
/* 0027d01c: sub.S f0,f0,f21 */ f[0]=EE_FPU_SUB_S(f[0],f[21]);
/* 0027d020: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0027d024: c.le.S f4,f0 */ (void)(EE_FPU_COMPARE_S(f[4],f[0],2)!=0);
/* 0027d028: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d02c: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d030: bc1f 0x0027d050 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027d034 */ set(2,sx(UINT32_C(0x00800000)));if(taken){goto L_0027d050;}}
/* 0027d038: sub.S f0,f0,f4 */ f[0]=EE_FPU_SUB_S(f[0],f[4]);
/* 0027d03c: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027d040: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d044: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d048: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027d04c: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
L_0027d050:;
/* 0027d050: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027d054: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027d058: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 0027d05c: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027d060: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027d064: sub.S f24,f0,f21 */ f[24]=EE_FPU_SUB_S(f[0],f[21]);
/* 0027d068: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
L_0027d06c:;
/* 0027d06c: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027d070: sltu v0,v1,a2 */ set(2,cpu(3)<cpu(6));
/* 0027d074: beq v0,zero,0x0027d344 */ {int taken=(cpu(2)==cpu(0));/* delay 0027d078 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_0027d344;}}
/* 0027d07c: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
L_0027d080:;
/* 0027d080: lui a3,0x4f */ set(7,sx(UINT32_C(0x004f0000)));
/* 0027d084: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027d088: addiu a3,a3,-0x530 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffad0)));
/* 0027d08c: lw s0,0x8(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 0027d090: move a0,s8 */ set(4,cpu(30));
/* 0027d094: lw s1,0x128(s5) */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d098: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027d09c: jal 0x001abc88 */ set(31,UINT64_C(0x0027d0a4));/* delay 0027d0a0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(7)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027d09c));
/* 0027d0a4: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027d0a8: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027d0ac: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 0027d0b0: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027d0b4: lw a0,0x0(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0027d0b8: lw a1,0x4(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0027d0bc: lw a2,0xc(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 0027d0c0: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027d0c4: lw a3,0x10(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0027d0c8: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027d0cc: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027d0d0: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027d0d4: sw s1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));
/* 0027d0d8: jal 0x00279a88 */ set(31,UINT64_C(0x0027d0e0));/* delay 0027d0dc */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027d0d8));
/* 0027d0e0: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d0e4: lui a3,0x4f */ set(7,sx(UINT32_C(0x004f0000)));
/* 0027d0e8: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027d0ec: addiu a3,a3,-0x530 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffad0)));
/* 0027d0f0: lw s0,0x10(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0027d0f4: move a0,s8 */ set(4,cpu(30));
/* 0027d0f8: lw s1,0x128(s5) */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d0fc: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027d100: jal 0x001abc88 */ set(31,UINT64_C(0x0027d108));/* delay 0027d104 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(7)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027d100));
/* 0027d108: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027d10c: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027d110: addiu v1,v1,0x48 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000048)));
/* 0027d114: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027d118: lw a0,0x0(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0027d11c: lw a1,0x4(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0027d120: lw a2,0xc(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 0027d124: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027d128: lw a3,0x10(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0027d12c: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027d130: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027d134: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027d138: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027d13c: jal 0x00279a88 */ set(31,UINT64_C(0x0027d144));/* delay 0027d140 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027d13c));
/* 0027d144: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d148: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027d14c: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027d150: lw t0,0x18(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027d154: lw a3,0xc(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 0027d158: move a0,s6 */ set(4,cpu(22));
/* 0027d15c: addiu v0,v0,-0x530 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027d160: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 0027d164: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d168: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027d16c: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 0027d170: addiu a2,v1,0x14 */ set(6,sx((uint32_t)cpu(3)+UINT32_C(0x00000014)));
/* 0027d174: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027d178: addiu t1,gp,-0x2ff8 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027d17c: jal 0x00279f10 */ set(31,UINT64_C(0x0027d184));/* delay 0027d180 */ f[12]=f[24];body_00279f10();
/* 0027d184: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d188: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d18c: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027d190: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027d194: addiu v0,v0,-0x530 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027d198: lw a3,0x14(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000014)));
/* 0027d19c: move a0,s6 */ set(4,cpu(22));
/* 0027d1a0: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 0027d1a4: lw t0,0x18(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027d1a8: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027d1ac: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027d1b0: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 0027d1b4: addiu a2,v1,0x3c */ set(6,sx((uint32_t)cpu(3)+UINT32_C(0x0000003c)));
/* 0027d1b8: addiu t1,gp,-0x2ff8 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027d1bc: jal 0x00279f10 */ set(31,UINT64_C(0x0027d1c4));/* delay 0027d1c0 */ f[12]=f[24];body_00279f10();
/* 0027d1c4: jal 0x00279980 */ set(31,UINT64_C(0x0027d1cc));/* delay 0027d1c8 */ set(4,sx(UINT32_C(0x00000001)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027d1c4));
/* 0027d1cc: lw v0,-0x2fd4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd02c)));
/* 0027d1d0: addiu s0,v0,-0x5 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffb)));
/* 0027d1d4: blez s0,0x0027d314 */ {int taken=((int64_t)cpu(16)<=0);/* delay 0027d1d8 */ lw(7,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_0027d314;}}
/* 0027d1dc: slti v0,s0,0x5 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000005));
/* 0027d1e0: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 0027d1e4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027d1e8: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027d1ec: movz s0,v1,v0 */ if(cpu(2)==0){set(16,cpu(3));}
/* 0027d1f0: mtc1 s0,f23 */ f[23]=(uint32_t)cpu(16);
/* 0027d1f4: cvt.s.W f23,f23 */ f[23]=EE_FPU_CVT_S_W(f[23]);
/* 0027d1f8: mov.S f20,f24 */ f[20]=f[24];
/* 0027d1fc: sub.S f0,f0,f24 */ f[0]=EE_FPU_SUB_S(f[0],f[24]);
/* 0027d200: nop  */ 
/* 0027d204: nop  */ 
/* 0027d208: div.S f22,f0,f23 */ f[22]=EE_FPU_DIV_S(f[0],f[23]);
/* 0027d20c: blez s0,0x0027d314 */ {int taken=((int64_t)cpu(16)<=0);/* delay 0027d210 */ set(17,cpu(0));if(taken){goto L_0027d314;}}
/* 0027d214: lui v0,0xff */ set(2,sx(UINT32_C(0x00ff0000)));
/* 0027d218: lw a0,0x18(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027d21c: lui a3,0x4f */ set(7,sx(UINT32_C(0x004f0000)));
/* 0027d220: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027d224: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 0027d228: addiu a3,a3,0x20 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000020)));
/* 0027d22c: lui at,0x4d80 */ set(1,sx(UINT32_C(0x4d800000)));
/* 0027d230: mtc1 at,f25 */ f[25]=(uint32_t)cpu(1);
/* 0027d234: and s7,a0,v0 */ set(23,cpu(4)&cpu(2));
/* 0027d238: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027d23c: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 0027d240: addiu s4,v1,-0x530 */ set(20,sx((uint32_t)cpu(3)+UINT32_C(0xfffffad0)));
/* 0027d244: addiu s3,a3,0x14 */ set(19,sx((uint32_t)cpu(7)+UINT32_C(0x00000014)));
/* 0027d248: addiu s2,gp,-0x2ff8 */ set(18,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027d24c: subu v0,s0,s1 */ set(2,sx((uint32_t)cpu(16)-(uint32_t)cpu(17)));
L_0027d250:;
/* 0027d250: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0027d254: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027d258: mul.S f0,f0,f25 */ f[0]=EE_FPU_MUL_S(f[0],f[25]);
/* 0027d25c: nop  */ 
/* 0027d260: nop  */ 
/* 0027d264: div.S f0,f0,f23 */ f[0]=EE_FPU_DIV_S(f[0],f[23]);
/* 0027d268: c.le.S f21,f0 */ (void)(EE_FPU_COMPARE_S(f[21],f[0],2)!=0);
/* 0027d26c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d270: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0027d274: bc1f 0x0027d290 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027d278 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));if(taken){goto L_0027d290;}}
/* 0027d27c: sub.S f0,f0,f21 */ f[0]=EE_FPU_SUB_S(f[0],f[21]);
/* 0027d280: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d284: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 0027d288: lui v1,0x8000 */ set(3,sx(UINT32_C(0x80000000)));
/* 0027d28c: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
L_0027d290:;
/* 0027d290: lui v1,0xff00 */ set(3,sx(UINT32_C(0xff000000)));
/* 0027d294: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d298: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 0027d29c: mov.S f12,f20 */ f[12]=f[20];
/* 0027d2a0: or v0,v0,s7 */ set(2,cpu(2)|cpu(23));
/* 0027d2a4: lw a3,0xc(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 0027d2a8: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 0027d2ac: move t0,v0 */ set(8,cpu(2));
/* 0027d2b0: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027d2b4: move a0,s6 */ set(4,cpu(22));
/* 0027d2b8: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d2bc: addu a3,a3,s4 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(20)));
/* 0027d2c0: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027d2c4: move a2,s3 */ set(6,cpu(19));
/* 0027d2c8: jal 0x00279f10 */ set(31,UINT64_C(0x0027d2d0));/* delay 0027d2cc */ set(9,cpu(18));body_00279f10();
/* 0027d2d0: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d2d4: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d2d8: mov.S f12,f20 */ f[12]=f[20];
/* 0027d2dc: lw t0,0x14(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027d2e0: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027d2e4: lw a3,0x14(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000014)));
/* 0027d2e8: move a0,s6 */ set(4,cpu(22));
/* 0027d2ec: addiu a2,s3,0x28 */ set(6,sx((uint32_t)cpu(19)+UINT32_C(0x00000028)));
/* 0027d2f0: move t1,s2 */ set(9,cpu(18));
/* 0027d2f4: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027d2f8: add.S f20,f20,f22 */ f[20]=EE_FPU_ADD_S(f[20],f[22]);
/* 0027d2fc: jal 0x00279f10 */ set(31,UINT64_C(0x0027d304));/* delay 0027d300 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(20)));body_00279f10();
/* 0027d304: slt v0,s1,s0 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(16));
/* 0027d308: bne v0,zero,0x0027d250 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027d30c */ set(2,sx((uint32_t)cpu(16)-(uint32_t)cpu(17)));if(taken){goto L_0027d250;}}
/* 0027d310: lw a3,0x10(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000010)));
L_0027d314:;
/* 0027d314: move a0,zero */ set(4,cpu(0));
/* 0027d318: addiu s6,s6,-0x2e */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0xffffffd2)));
/* 0027d31c: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 0027d320: jal 0x00279980 */ set(31,UINT64_C(0x0027d328));/* delay 0027d324 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(7));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027d320));
/* 0027d328: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027d32c: lw v0,-0x2fe0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd020)));
/* 0027d330: sltu v0,v1,v0 */ set(2,cpu(3)<cpu(2));
/* 0027d334: bnel v0,zero,0x0027d080 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027d338 */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));goto L_0027d080;}}
/* 0027d33c: lw a1,-0x2fd4(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd02c)));
/* 0027d340: addiu a0,a1,0x1 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
L_0027d344:;
/* 0027d344: b 0x0027d79c */ /* delay 0027d348 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000011));goto L_0027d79c;
L_0027d350:;
/* 0027d350: slti v0,a1,0x8 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0027d354: beq v0,zero,0x0027d3d0 */ {int taken=(cpu(2)==cpu(0));/* delay 0027d358 */ set(4,cpu(5));if(taken){goto L_0027d3d0;}}
/* 0027d35c: mtc1 a1,f3 */ f[3]=(uint32_t)cpu(5);
/* 0027d360: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027d364: lui at,0x3e00 */ set(1,sx(UINT32_C(0x3e000000)));
/* 0027d368: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027d36c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027d370: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027d374: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027d378: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027d37c: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027d380: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0027d384: mul.S f21,f3,f1 */ f[21]=EE_FPU_MUL_S(f[3],f[1]);
/* 0027d388: sub.S f0,f0,f21 */ f[0]=EE_FPU_SUB_S(f[0],f[21]);
/* 0027d38c: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0027d390: c.le.S f12,f0 */ (void)(EE_FPU_COMPARE_S(f[12],f[0],2)!=0);
/* 0027d394: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d398: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d39c: bc1f 0x0027d3bc */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027d3a0 */ set(2,sx(UINT32_C(0x00800000)));if(taken){goto L_0027d3bc;}}
/* 0027d3a4: sub.S f0,f0,f12 */ f[0]=EE_FPU_SUB_S(f[0],f[12]);
/* 0027d3a8: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027d3ac: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d3b0: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d3b4: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027d3b8: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
L_0027d3bc:;
/* 0027d3bc: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 0027d3c0: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027d3c4: b 0x0027d3d4 */ /* delay 0027d3c8 */ set(30,cpu(3)|cpu(2));goto L_0027d3d4;
L_0027d3d0:;
/* 0027d3d0: move s8,zero */ set(30,cpu(0));
L_0027d3d4:;
/* 0027d3d4: slti v0,a0,0x6 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0027d3d8: beq v0,zero,0x0027d458 */ {int taken=(cpu(2)==cpu(0));/* delay 0027d3dc */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffb)));if(taken){goto L_0027d458;}}
/* 0027d3e0: mtc1 a0,f0 */ f[0]=(uint32_t)cpu(4);
/* 0027d3e4: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027d3e8: lui at,0x40a0 */ set(1,sx(UINT32_C(0x40a00000)));
/* 0027d3ec: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027d3f0: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027d3f4: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027d3f8: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027d3fc: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027d400: nop  */ 
/* 0027d404: nop  */ 
/* 0027d408: div.S f21,f0,f1 */ f[21]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027d40c: mul.S f0,f21,f2 */ f[0]=EE_FPU_MUL_S(f[21],f[2]);
/* 0027d410: c.le.S f3,f0 */ (void)(EE_FPU_COMPARE_S(f[3],f[0],2)!=0);
/* 0027d414: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d418: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d41c: bc1f 0x0027d43c */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027d420 */ set(2,sx(UINT32_C(0x00800000)));if(taken){goto L_0027d43c;}}
/* 0027d424: sub.S f0,f0,f3 */ f[0]=EE_FPU_SUB_S(f[0],f[3]);
/* 0027d428: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027d42c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d430: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d434: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027d438: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
L_0027d43c:;
/* 0027d43c: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 0027d440: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027d444: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027d448: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027d44c: mtc1 at,f24 */ f[24]=(uint32_t)cpu(1);
/* 0027d450: b 0x0027d540 */ /* delay 0027d454 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));goto L_0027d540;
L_0027d458:;
/* 0027d458: lui at,0x3e80 */ set(1,sx(UINT32_C(0x3e800000)));
/* 0027d45c: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027d460: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 0027d464: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027d468: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027d46c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027d470: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027d474: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027d478: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027d47c: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027d480: mul.S f21,f1,f3 */ f[21]=EE_FPU_MUL_S(f[1],f[3]);
/* 0027d484: sub.S f0,f0,f21 */ f[0]=EE_FPU_SUB_S(f[0],f[21]);
/* 0027d488: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0027d48c: c.le.S f4,f0 */ (void)(EE_FPU_COMPARE_S(f[4],f[0],2)!=0);
/* 0027d490: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d494: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d498: bc1f 0x0027d4b4 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027d49c */ if(taken){goto L_0027d4b4;}}
/* 0027d4a0: sub.S f0,f0,f4 */ f[0]=EE_FPU_SUB_S(f[0],f[4]);
/* 0027d4a4: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027d4a8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d4ac: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d4b0: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
L_0027d4b4:;
/* 0027d4b4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027d4b8: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027d4bc: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
/* 0027d4c0: lui at,0x42c0 */ set(1,sx(UINT32_C(0x42c00000)));
/* 0027d4c4: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027d4c8: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027d4cc: sub.S f0,f0,f21 */ f[0]=EE_FPU_SUB_S(f[0],f[21]);
/* 0027d4d0: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027d4d4: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027d4d8: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 0027d4dc: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027d4e0: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 0027d4e4: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0027d4e8: c.le.S f2,f0 */ (void)(EE_FPU_COMPARE_S(f[2],f[0],2)!=0);
/* 0027d4ec: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d4f0: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d4f4: bc1f 0x0027d510 */ {int taken=(((nocturneBattlePanelNextFcsr()>>23)&1u)==0);/* delay 0027d4f8 */ if(taken){goto L_0027d510;}}
/* 0027d4fc: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
/* 0027d500: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027d504: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027d508: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027d50c: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
L_0027d510:;
/* 0027d510: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0027d514: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027d518: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 0027d51c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027d520: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027d524: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
/* 0027d528: mul.S f0,f21,f0 */ f[0]=EE_FPU_MUL_S(f[21],f[0]);
/* 0027d52c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 0027d530: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027d534: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027d538: sw v1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 0027d53c: add.S f24,f0,f1 */ f[24]=EE_FPU_ADD_S(f[0],f[1]);
L_0027d540:;
/* 0027d540: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027d544: sltu v0,v1,a2 */ set(2,cpu(3)<cpu(6));
/* 0027d548: beq v0,zero,0x0027d798 */ {int taken=(cpu(2)==cpu(0));/* delay 0027d54c */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_0027d798;}}
/* 0027d550: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027d554: addiu s4,a0,0x20 */ set(20,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 0027d558: addiu s7,s4,0x28 */ set(23,sx((uint32_t)cpu(20)+UINT32_C(0x00000028)));
/* 0027d55c: nop  */ 
L_0027d560:;
/* 0027d560: lw a3,0x1c(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d564: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027d568: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027d56c: move a0,s8 */ set(4,cpu(30));
/* 0027d570: lw s0,0x8(a3) */ lw(16,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 0027d574: addiu v0,v0,-0x530 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027d578: lw s1,0x128(s5) */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d57c: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027d580: jal 0x001abc88 */ set(31,UINT64_C(0x0027d588));/* delay 0027d584 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027d580));
/* 0027d588: lw a0,0x0(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 0027d58c: lw a1,0x4(s4) */ lw(5,ea(20,(int32_t)UINT32_C(0x00000004)));
/* 0027d590: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027d594: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027d598: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027d59c: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027d5a0: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027d5a4: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027d5a8: lw a2,0xc(s4) */ lw(6,ea(20,(int32_t)UINT32_C(0x0000000c)));
/* 0027d5ac: lw a3,0x10(s4) */ lw(7,ea(20,(int32_t)UINT32_C(0x00000010)));
/* 0027d5b0: sw s1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));
/* 0027d5b4: jal 0x00279a88 */ set(31,UINT64_C(0x0027d5bc));/* delay 0027d5b8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027d5b4));
/* 0027d5bc: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d5c0: lui a3,0x4f */ set(7,sx(UINT32_C(0x004f0000)));
/* 0027d5c4: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027d5c8: addiu a3,a3,-0x530 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffad0)));
/* 0027d5cc: lw s0,0x10(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0027d5d0: move a0,s8 */ set(4,cpu(30));
/* 0027d5d4: lw s1,0x128(s5) */ lw(17,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d5d8: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027d5dc: jal 0x001abc88 */ set(31,UINT64_C(0x0027d5e4));/* delay 0027d5e0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(7)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x001abc88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x001abc88),UINT32_C(0x0027d5dc));
/* 0027d5e4: lw a0,0x0(s7) */ lw(4,ea(23,(int32_t)UINT32_C(0x00000000)));
/* 0027d5e8: lw a1,0x4(s7) */ lw(5,ea(23,(int32_t)UINT32_C(0x00000004)));
/* 0027d5ec: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027d5f0: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
/* 0027d5f4: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027d5f8: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027d5fc: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027d600: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027d604: lw a2,0xc(s7) */ lw(6,ea(23,(int32_t)UINT32_C(0x0000000c)));
/* 0027d608: lw a3,0x10(s7) */ lw(7,ea(23,(int32_t)UINT32_C(0x00000010)));
/* 0027d60c: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027d610: jal 0x00279a88 */ set(31,UINT64_C(0x0027d618));/* delay 0027d614 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279a88)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279a88),UINT32_C(0x0027d610));
/* 0027d618: jal 0x00279980 */ set(31,UINT64_C(0x0027d620));/* delay 0027d61c */ set(4,sx(UINT32_C(0x00000001)));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027d618));
/* 0027d620: lw v0,-0x2fd4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd02c)));
/* 0027d624: addiu s0,v0,-0x5 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffb)));
/* 0027d628: blez s0,0x0027d708 */ {int taken=((int64_t)cpu(16)<=0);/* delay 0027d62c */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));if(taken){goto L_0027d708;}}
/* 0027d630: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0027d634: jal 0x00279980 */ set(31,UINT64_C(0x0027d63c));/* delay 0027d638 */ f[20]=f[24];if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027d634));
/* 0027d63c: slti v1,s0,0x3 */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 0027d640: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0027d644: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027d648: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027d64c: movz s0,v0,v1 */ if(cpu(3)==0){set(16,cpu(2));}
/* 0027d650: sub.S f1,f1,f24 */ f[1]=EE_FPU_SUB_S(f[1],f[24]);
/* 0027d654: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 0027d658: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027d65c: nop  */ 
/* 0027d660: nop  */ 
/* 0027d664: div.S f22,f1,f0 */ f[22]=EE_FPU_DIV_S(f[1],f[0]);
/* 0027d668: blez s0,0x0027d6f4 */ {int taken=((int64_t)cpu(16)<=0);/* delay 0027d66c */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027d6f4;}}
/* 0027d670: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027d674: move s1,s0 */ set(17,cpu(16));
/* 0027d678: addiu s0,gp,-0x2ff8 */ set(16,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027d67c: addiu s3,v0,0x34 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00000034)));
/* 0027d680: addiu s2,v1,-0x530 */ set(18,sx((uint32_t)cpu(3)+UINT32_C(0xfffffad0)));
/* 0027d684: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
L_0027d688:;
/* 0027d688: mov.S f12,f20 */ f[12]=f[20];
/* 0027d68c: lw t0,0x18(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027d690: move a0,s6 */ set(4,cpu(22));
/* 0027d694: lw a3,0xc(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 0027d698: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027d69c: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d6a0: move a2,s3 */ set(6,cpu(19));
/* 0027d6a4: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027d6a8: move t1,s0 */ set(9,cpu(16));
/* 0027d6ac: addu a3,a3,s2 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(18)));
/* 0027d6b0: jal 0x00279f10 */ set(31,UINT64_C(0x0027d6b8));/* delay 0027d6b4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));body_00279f10();
/* 0027d6b8: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d6bc: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d6c0: mov.S f12,f20 */ f[12]=f[20];
/* 0027d6c4: lw t0,0x14(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027d6c8: move a0,s6 */ set(4,cpu(22));
/* 0027d6cc: lw a3,0x14(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000014)));
/* 0027d6d0: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027d6d4: addiu a2,s3,0x28 */ set(6,sx((uint32_t)cpu(19)+UINT32_C(0x00000028)));
/* 0027d6d8: move t1,s0 */ set(9,cpu(16));
/* 0027d6dc: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027d6e0: add.S f20,f20,f22 */ f[20]=EE_FPU_ADD_S(f[20],f[22]);
/* 0027d6e4: jal 0x00279f10 */ set(31,UINT64_C(0x0027d6ec));/* delay 0027d6e8 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(18)));body_00279f10();
/* 0027d6ec: bne s1,zero,0x0027d688 */ {int taken=(cpu(17)!=cpu(0));/* delay 0027d6f0 */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));if(taken){goto L_0027d688;}}
L_0027d6f4:;
/* 0027d6f4: jal 0x00279980 */ set(31,UINT64_C(0x0027d6fc));/* delay 0027d6f8 */ set(4,cpu(0));if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279980)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279980),UINT32_C(0x0027d6f4));
/* 0027d6fc: b 0x0027d778 */ /* delay 0027d700 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_0027d778;
L_0027d708:;
/* 0027d708: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027d70c: addiu v0,v0,-0x530 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027d710: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d714: lw a3,0xc(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 0027d718: move a0,s6 */ set(4,cpu(22));
/* 0027d71c: lw t0,0x18(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027d720: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027d724: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027d728: addiu a2,s4,0x14 */ set(6,sx((uint32_t)cpu(20)+UINT32_C(0x00000014)));
/* 0027d72c: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 0027d730: addiu t1,gp,-0x2ff8 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027d734: jal 0x00279f10 */ set(31,UINT64_C(0x0027d73c));/* delay 0027d738 */ f[12]=f[24];body_00279f10();
/* 0027d73c: lw t2,0x128(s5) */ lw(10,ea(21,(int32_t)UINT32_C(0x00000128)));
/* 0027d740: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027d744: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027d748: addiu v0,v0,-0x530 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027d74c: lw t0,0x18(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027d750: lw a3,0x14(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000014)));
/* 0027d754: move a0,s6 */ set(4,cpu(22));
/* 0027d758: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027d75c: addiu a2,s4,0x3c */ set(6,sx((uint32_t)cpu(20)+UINT32_C(0x0000003c)));
/* 0027d760: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027d764: addiu t1,gp,-0x2ff8 */ set(9,sx((uint32_t)cpu(28)+UINT32_C(0xffffd008)));
/* 0027d768: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 0027d76c: jal 0x00279f10 */ set(31,UINT64_C(0x0027d774));/* delay 0027d770 */ f[12]=f[24];body_00279f10();
/* 0027d774: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
L_0027d778:;
/* 0027d778: addiu s6,s6,-0x2e */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0xffffffd2)));
/* 0027d77c: lw v0,-0x2fe0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd020)));
/* 0027d780: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027d784: sltu v0,v1,v0 */ set(2,cpu(3)<cpu(2));
/* 0027d788: bne v0,zero,0x0027d560 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027d78c */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));if(taken){goto L_0027d560;}}
/* 0027d790: lw a1,-0x2fd4(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd02c)));
/* 0027d794: addiu a0,a1,0x1 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
L_0027d798:;
/* 0027d798: slti v0,a0,0xa */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x0000000a));
L_0027d79c:;
/* 0027d79c: bnel v0,zero,0x0027d7b0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027d7a0 */ sw(ea(28,(int32_t)UINT32_C(0xffffd02c)),(uint32_t)cpu(4));goto L_0027d7b0;}}
/* 0027d7a4: lw a2,-0x2190(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffde70)));
/* 0027d7a8: sw zero,-0x2fd4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd02c)),(uint32_t)cpu(0));
/* 0027d7ac: sw a2,-0x2fe0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd020)),(uint32_t)cpu(6));
L_0027d7b0:;
/* 0027d7b0: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027d7b4: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027d7b8: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0027d7bc: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027d7c0: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0027d7c4: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027d7c8: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027d7cc: ld s5,0x48(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027d7d0: ld s6,0x50(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027d7d4: ld s7,0x58(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027d7d8: ld s8,0x60(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027d7dc: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027d7e0: lwc1 f29,0xb8(sp) */ f[29]=word(ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0027d7e4: lwc1 f28,0xb0(sp) */ f[28]=word(ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0027d7e8: lwc1 f27,0xa8(sp) */ f[27]=word(ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0027d7ec: lwc1 f26,0xa0(sp) */ f[26]=word(ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0027d7f0: lwc1 f25,0x98(sp) */ f[25]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0027d7f4: lwc1 f24,0x90(sp) */ f[24]=word(ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0027d7f8: lwc1 f23,0x88(sp) */ f[23]=word(ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0027d7fc: lwc1 f22,0x80(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0027d800: lwc1 f21,0x78(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027d804: lwc1 f20,0x70(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027d808: j 0x00279c00 */ /* delay 0027d80c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000c0)));checkReturn(cpu(31),incoming);if(!nocturneBattlePanelOwnerRun(UINT32_C(0x00279c00)))nocturneBattlePanelNextDependencyStop(UINT32_C(0x00279c00),UINT32_C(0x0027d808));return;
L_0027d810:;
/* 0027d810: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
L_0027d814:;
/* 0027d814: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0027d818: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0027d81c: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027d820: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027d824: ld s5,0x48(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027d828: ld s6,0x50(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027d82c: ld s7,0x58(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027d830: ld s8,0x60(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027d834: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027d838: lwc1 f29,0xb8(sp) */ f[29]=word(ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0027d83c: lwc1 f28,0xb0(sp) */ f[28]=word(ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0027d840: lwc1 f27,0xa8(sp) */ f[27]=word(ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0027d844: lwc1 f26,0xa0(sp) */ f[26]=word(ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0027d848: lwc1 f25,0x98(sp) */ f[25]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0027d84c: lwc1 f24,0x90(sp) */ f[24]=word(ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0027d850: lwc1 f23,0x88(sp) */ f[23]=word(ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0027d854: lwc1 f22,0x80(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0027d858: lwc1 f21,0x78(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027d85c: lwc1 f20,0x70(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027d860: jr ra */ {uint64_t target=cpu(31);/* delay 0027d864 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000c0)));checkReturn(target,incoming);return;}
}
static void body_0027d8d0(void){
uint64_t incoming=cpu(31);
/* 0027d8d0: lw v0,-0x2f88(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd078)));
/* 0027d8d4: jr ra */ {uint64_t target=cpu(31);/* delay 0027d8d8 */ set(2,cpu(0)<cpu(2));checkReturn(target,incoming);return;}
}
static void body_0027d980(void){
uint64_t incoming=cpu(31);
/* 0027d980: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0027d984: sw zero,-0x2fc0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd040)),(uint32_t)cpu(0));
/* 0027d988: sb v0,-0x2f78(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffd088)),(uint8_t)cpu(2));
/* 0027d98c: sw zero,-0x2fb8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd048)),(uint32_t)cpu(0));
/* 0027d990: sw zero,-0x2fac(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd054)),(uint32_t)cpu(0));
/* 0027d994: sw v0,-0x2f88(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd078)),(uint32_t)cpu(2));
/* 0027d998: jr ra */ {uint64_t target=cpu(31);/* delay 0027d99c */ sw(ea(28,(int32_t)UINT32_C(0xffffd07c)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelNextBody(uint32_t entry){switch(entry){
case UINT32_C(0x00279f10):if(nocturneBattlePanelNextStackPointer()!=(uint32_t)cpu(29))abort();body_00279f10();return 1u;case UINT32_C(0x0027c230):if(nocturneBattlePanelNextStackPointer()!=(uint32_t)cpu(29))abort();body_0027c230();return 1u;case UINT32_C(0x0027c350):if(nocturneBattlePanelNextStackPointer()!=(uint32_t)cpu(29))abort();body_0027c350();return 1u;case UINT32_C(0x0027d8d0):if(nocturneBattlePanelNextStackPointer()!=(uint32_t)cpu(29))abort();body_0027d8d0();return 1u;case UINT32_C(0x0027d980):if(nocturneBattlePanelNextStackPointer()!=(uint32_t)cpu(29))abort();body_0027d980();return 1u;
default:return 0u;}}

void ps2BattlePanelDrawPivotScaledTexture_00279F10(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,float f12){
set(4u,a0);
set(5u,a1);
set(6u,a2);
set(7u,a3);
set(8u,a4);
set(9u,a5);
set(10u,a6);
memcpy(&nocturneEffectHostFpr()[12u],&f12,4);
body_00279f10();
return;
}

void nbPanelPressGaugeInit(void){
body_0027c230();
return;
}

void nbPanelPressGauge(uint64_t a0){
set(4u,a0);
body_0027c350();
return;
}

uint64_t nbPanelPressTurnGaugeRun(void){
body_0027d8d0();
return cpu(2);
}

void ps2BattlePanelStartPTAOnly_0027D980(void){
body_0027d980();
return;
}
