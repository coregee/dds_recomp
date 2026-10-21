/* Whole original unsigned64 divide/remainder; no output or stack provider. */
#include "battle_action_u64_numeric_frames.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include "magatuhi_helpers.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
extern uint64_t nocturneEffectHostHi(void);
extern uint64_t nocturneEffectHostLo(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint8_t byte(uint32_t a){return *at(a);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
static void nativeDivide(uint32_t a,uint32_t d,int isSigned,int secondary){if(isSigned||secondary)abort();EE_ANCHOR_DIVU_STATE(d?a/d:UINT32_MAX,d?a%d:a);}
static void nativeMultiply(unsigned rd,uint32_t a,uint32_t v,int isSigned,int secondary){if(secondary)abort();uint64_t p=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)v):(uint64_t)a*v;EE_MAGATUHI_MULT_STATE(p);if(rd)set(rd,sx((uint32_t)p));}

static void body_002e6048(void);
static void body_002e65c8(void);
static void body_002e6048(void){
nocturneEffectAxisNoteEntry(0x002e6048u);
uint64_t incoming=cpu(31);
/* 002e6048: dsra32 t0,a1,0x0 */ set(8,(uint64_t)((int64_t)cpu(5)>>32));
/* 002e604c: dsra32 t2,a0,0x0 */ set(10,(uint64_t)((int64_t)cpu(4)>>32));
/* 002e6050: dsll32 t1,a1,0x0 */ set(9,cpu(5)<<32);
/* 002e6054: dsra32 t1,t1,0x0 */ set(9,(uint64_t)((int64_t)cpu(9)>>32));
/* 002e6058: dsll32 t3,a0,0x0 */ set(11,cpu(4)<<32);
/* 002e605c: dsra32 t3,t3,0x0 */ set(11,(uint64_t)((int64_t)cpu(11)>>32));
/* 002e6060: bne t0,zero,0x002e63e8 */ {int taken=(cpu(8)!=cpu(0));/* delay 002e6064 */ set(2,cpu(10)<cpu(8));if(taken){goto L_002e63e8;}}
/* 002e6068: sltu v0,t2,t1 */ set(2,cpu(10)<cpu(9));
/* 002e606c: beq v0,zero,0x002e61a8 */ {int taken=(cpu(2)==cpu(0));/* delay 002e6070 */ set(2,cpu(0)|UINT32_C(0x0000ffff));if(taken){goto L_002e61a8;}}
/* 002e6074: sltu v0,v0,t1 */ set(2,cpu(2)<cpu(9));
/* 002e6078: bne v0,zero,0x002e6090 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e607c */ set(2,sx(UINT32_C(0x00ff0000)));if(taken){goto L_002e6090;}}
/* 002e6080: sltiu v0,t1,0x100 */ set(2,cpu(9)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000100));
/* 002e6084: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 002e6088: b 0x002e60a4 */ /* delay 002e608c */ if(cpu(2)!=0){set(4,cpu(0));}goto L_002e60a4;
L_002e6090:;
/* 002e6090: li v1,0x18 */ set(3,sx(UINT32_C(0x00000018)));
/* 002e6094: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002e6098: li a0,0x10 */ set(4,sx(UINT32_C(0x00000010)));
/* 002e609c: sltu v0,v0,t1 */ set(2,cpu(2)<cpu(9));
/* 002e60a0: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002e60a4:;
/* 002e60a4: srlv v1,t1,a0 */ set(3,sx((uint32_t)cpu(9)>>((uint32_t)cpu(4)&31u)));
/* 002e60a8: li a1,0x20 */ set(5,sx(UINT32_C(0x00000020)));
/* 002e60ac: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002e60b0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002e60b4: lbu v0,-0x4088(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0xffffbf78))));
/* 002e60b8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002e60bc: subu a2,a1,v0 */ set(6,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));
/* 002e60c0: beq a2,zero,0x002e60dc */ {int taken=(cpu(6)==cpu(0));/* delay 002e60c4 */ set(2,sx((uint32_t)cpu(5)-(uint32_t)cpu(6)));if(taken){goto L_002e60dc;}}
/* 002e60c8: sllv v1,t2,a2 */ set(3,sx((uint32_t)((uint32_t)cpu(10)<<((uint32_t)cpu(6)&31u))));
/* 002e60cc: srlv v0,t3,v0 */ set(2,sx((uint32_t)cpu(11)>>((uint32_t)cpu(2)&31u)));
/* 002e60d0: sllv t3,t3,a2 */ set(11,sx((uint32_t)((uint32_t)cpu(11)<<((uint32_t)cpu(6)&31u))));
/* 002e60d4: or t2,v1,v0 */ set(10,cpu(3)|cpu(2));
/* 002e60d8: sllv t1,t1,a2 */ set(9,sx((uint32_t)((uint32_t)cpu(9)<<((uint32_t)cpu(6)&31u))));
L_002e60dc:;
/* 002e60dc: srl a2,t1,0x10 */ set(6,sx((uint32_t)cpu(9)>>16));
/* 002e60e0: andi t0,t1,0xffff */ set(8,cpu(9)&UINT32_C(0x0000ffff));
/* 002e60e4: divu t2,a2 */ nativeDivide((uint32_t)cpu(10),(uint32_t)cpu(6),0,0);
/* 002e60e8: srl a0,t3,0x10 */ set(4,sx((uint32_t)cpu(11)>>16));
/* 002e60ec: beql a2,zero,0x002e60f4 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e60f0 */ nocturneCompilerArithmeticTrap(7u);goto L_002e60f4;}}
L_002e60f4:;
/* 002e60f4: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e60f8: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e60fc: move a3,v0 */ set(7,cpu(2));
/* 002e6100: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e6104: mult a1,a3,t0 */ nativeMultiply(5,(uint32_t)cpu(7),(uint32_t)cpu(8),1,0);
/* 002e6108: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e610c: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e6110: beql v0,zero,0x002e6144 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e6114 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));goto L_002e6144;}}
/* 002e6118: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e611c: sltu v0,v1,t1 */ set(2,cpu(3)<cpu(9));
/* 002e6120: bne v0,zero,0x002e6140 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6124 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));if(taken){goto L_002e6140;}}
/* 002e6128: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e612c: beql v0,zero,0x002e6144 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e6130 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));goto L_002e6144;}}
/* 002e6134: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002e6138: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e613c: nop  */ 
L_002e6140:;
/* 002e6140: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
L_002e6144:;
/* 002e6144: beql a2,zero,0x002e614c */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e6148 */ nocturneCompilerArithmeticTrap(7u);goto L_002e614c;}}
L_002e614c:;
/* 002e614c: divu v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),0,0);
/* 002e6150: andi a0,t3,0xffff */ set(4,cpu(11)&UINT32_C(0x0000ffff));
/* 002e6154: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e6158: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e615c: move a2,v0 */ set(6,cpu(2));
/* 002e6160: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e6164: mult a1,a2,t0 */ nativeMultiply(5,(uint32_t)cpu(6),(uint32_t)cpu(8),1,0);
/* 002e6168: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e616c: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e6170: beq v0,zero,0x002e619c */ {int taken=(cpu(2)==cpu(0));/* delay 002e6174 */ set(2,sx((uint32_t)cpu(7)<<16));if(taken){goto L_002e619c;}}
/* 002e6178: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e617c: sltu v0,v1,t1 */ set(2,cpu(3)<cpu(9));
/* 002e6180: bne v0,zero,0x002e6198 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6184 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));if(taken){goto L_002e6198;}}
/* 002e6188: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e618c: addiu v1,a2,-0x1 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002e6190: xori v0,v0,0x0 */ set(2,cpu(2)^UINT32_C(0x00000000));
/* 002e6194: movn a2,v1,v0 */ if(cpu(2)!=0){set(6,cpu(3));}
L_002e6198:;
/* 002e6198: sll v0,a3,0x10 */ set(2,sx((uint32_t)cpu(7)<<16));
L_002e619c:;
/* 002e619c: b 0x002e6590 */ /* delay 002e61a0 */ set(6,cpu(2)|cpu(6));goto L_002e6590;
L_002e61a8:;
/* 002e61a8: bne t1,zero,0x002e61d0 */ {int taken=(cpu(9)!=cpu(0));/* delay 002e61ac */ set(2,cpu(2)<cpu(9));if(taken){goto L_002e61d0;}}
/* 002e61b0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002e61b4: beql t1,zero,0x002e61bc */ {int taken=(cpu(9)==cpu(0));if(taken){/* delay 002e61b8 */ nocturneCompilerArithmeticTrap(7u);goto L_002e61bc;}}
L_002e61bc:;
/* 002e61bc: divu v0,t0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(8),0,0);
/* 002e61c0: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e61c4: move t1,v0 */ set(9,cpu(2));
/* 002e61c8: ori v0,zero,0xffff */ set(2,cpu(0)|UINT32_C(0x0000ffff));
/* 002e61cc: sltu v0,v0,t1 */ set(2,cpu(2)<cpu(9));
L_002e61d0:;
/* 002e61d0: bne v0,zero,0x002e61e8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e61d4 */ set(2,sx(UINT32_C(0x00ff0000)));if(taken){goto L_002e61e8;}}
/* 002e61d8: sltiu v0,t1,0x100 */ set(2,cpu(9)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000100));
/* 002e61dc: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 002e61e0: b 0x002e61fc */ /* delay 002e61e4 */ if(cpu(2)!=0){set(4,cpu(0));}goto L_002e61fc;
L_002e61e8:;
/* 002e61e8: li v1,0x18 */ set(3,sx(UINT32_C(0x00000018)));
/* 002e61ec: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002e61f0: li a0,0x10 */ set(4,sx(UINT32_C(0x00000010)));
/* 002e61f4: sltu v0,v0,t1 */ set(2,cpu(2)<cpu(9));
/* 002e61f8: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002e61fc:;
/* 002e61fc: srlv v1,t1,a0 */ set(3,sx((uint32_t)cpu(9)>>((uint32_t)cpu(4)&31u)));
/* 002e6200: li a1,0x20 */ set(5,sx(UINT32_C(0x00000020)));
/* 002e6204: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002e6208: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002e620c: lbu v0,-0x4088(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0xffffbf78))));
/* 002e6210: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002e6214: subu a2,a1,v0 */ set(6,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));
/* 002e6218: bne a2,zero,0x002e6238 */ {int taken=(cpu(6)!=cpu(0));/* delay 002e621c */ set(7,sx((uint32_t)cpu(5)-(uint32_t)cpu(6)));if(taken){goto L_002e6238;}}
/* 002e6220: subu t2,t2,t1 */ set(10,sx((uint32_t)cpu(10)-(uint32_t)cpu(9)));
/* 002e6224: li t5,0x1 */ set(13,sx(UINT32_C(0x00000001)));
/* 002e6228: srl t0,t1,0x10 */ set(8,sx((uint32_t)cpu(9)>>16));
/* 002e622c: b 0x002e6320 */ /* delay 002e6230 */ set(12,cpu(9)&UINT32_C(0x0000ffff));goto L_002e6320;
L_002e6238:;
/* 002e6238: sllv v1,t2,a2 */ set(3,sx((uint32_t)((uint32_t)cpu(10)<<((uint32_t)cpu(6)&31u))));
/* 002e623c: srlv v0,t3,a3 */ set(2,sx((uint32_t)cpu(11)>>((uint32_t)cpu(7)&31u)));
/* 002e6240: sllv t3,t3,a2 */ set(11,sx((uint32_t)((uint32_t)cpu(11)<<((uint32_t)cpu(6)&31u))));
/* 002e6244: srlv a0,t2,a3 */ set(4,sx((uint32_t)cpu(10)>>((uint32_t)cpu(7)&31u)));
/* 002e6248: or t2,v1,v0 */ set(10,cpu(3)|cpu(2));
/* 002e624c: sllv t1,t1,a2 */ set(9,sx((uint32_t)((uint32_t)cpu(9)<<((uint32_t)cpu(6)&31u))));
/* 002e6250: srl t0,t1,0x10 */ set(8,sx((uint32_t)cpu(9)>>16));
/* 002e6254: divu a0,t0 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(8),0,0);
/* 002e6258: srl a0,t2,0x10 */ set(4,sx((uint32_t)cpu(10)>>16));
/* 002e625c: andi t4,t1,0xffff */ set(12,cpu(9)&UINT32_C(0x0000ffff));
/* 002e6260: move a2,t0 */ set(6,cpu(8));
/* 002e6264: beql a2,zero,0x002e626c */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e6268 */ nocturneCompilerArithmeticTrap(7u);goto L_002e626c;}}
L_002e626c:;
/* 002e626c: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e6270: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e6274: move a3,v0 */ set(7,cpu(2));
/* 002e6278: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e627c: mult a1,a3,t4 */ nativeMultiply(5,(uint32_t)cpu(7),(uint32_t)cpu(12),1,0);
/* 002e6280: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e6284: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e6288: beq v0,zero,0x002e62b8 */ {int taken=(cpu(2)==cpu(0));/* delay 002e628c */ set(13,cpu(12));if(taken){goto L_002e62b8;}}
/* 002e6290: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e6294: sltu v0,v1,t1 */ set(2,cpu(3)<cpu(9));
/* 002e6298: bne v0,zero,0x002e62b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e629c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));if(taken){goto L_002e62b8;}}
/* 002e62a0: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e62a4: beql v0,zero,0x002e62bc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e62a8 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));goto L_002e62bc;}}
/* 002e62ac: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002e62b0: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e62b4: nop  */ 
L_002e62b8:;
/* 002e62b8: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
L_002e62bc:;
/* 002e62bc: beql a2,zero,0x002e62c4 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e62c0 */ nocturneCompilerArithmeticTrap(7u);goto L_002e62c4;}}
L_002e62c4:;
/* 002e62c4: divu v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),0,0);
/* 002e62c8: andi a0,t2,0xffff */ set(4,cpu(10)&UINT32_C(0x0000ffff));
/* 002e62cc: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e62d0: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e62d4: move a2,v0 */ set(6,cpu(2));
/* 002e62d8: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e62dc: mult a1,a2,t5 */ nativeMultiply(5,(uint32_t)cpu(6),(uint32_t)cpu(13),1,0);
/* 002e62e0: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e62e4: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e62e8: beq v0,zero,0x002e6318 */ {int taken=(cpu(2)==cpu(0));/* delay 002e62ec */ set(2,sx((uint32_t)cpu(7)<<16));if(taken){goto L_002e6318;}}
/* 002e62f0: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e62f4: sltu v0,v1,t1 */ set(2,cpu(3)<cpu(9));
/* 002e62f8: bne v0,zero,0x002e6314 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e62fc */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));if(taken){goto L_002e6314;}}
/* 002e6300: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e6304: beq v0,zero,0x002e6318 */ {int taken=(cpu(2)==cpu(0));/* delay 002e6308 */ set(2,sx((uint32_t)cpu(7)<<16));if(taken){goto L_002e6318;}}
/* 002e630c: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002e6310: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
L_002e6314:;
/* 002e6314: sll v0,a3,0x10 */ set(2,sx((uint32_t)cpu(7)<<16));
L_002e6318:;
/* 002e6318: subu t2,v1,a1 */ set(10,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
/* 002e631c: or t5,v0,a2 */ set(13,cpu(2)|cpu(6));
L_002e6320:;
/* 002e6320: move a2,t0 */ set(6,cpu(8));
/* 002e6324: move t0,t4 */ set(8,cpu(12));
/* 002e6328: divu t2,a2 */ nativeDivide((uint32_t)cpu(10),(uint32_t)cpu(6),0,0);
/* 002e632c: srl a0,t3,0x10 */ set(4,sx((uint32_t)cpu(11)>>16));
/* 002e6330: beql a2,zero,0x002e6338 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e6334 */ nocturneCompilerArithmeticTrap(7u);goto L_002e6338;}}
L_002e6338:;
/* 002e6338: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e633c: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e6340: move a3,v0 */ set(7,cpu(2));
/* 002e6344: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e6348: mult a1,a3,t0 */ nativeMultiply(5,(uint32_t)cpu(7),(uint32_t)cpu(8),1,0);
/* 002e634c: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e6350: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e6354: beql v0,zero,0x002e6384 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e6358 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));goto L_002e6384;}}
/* 002e635c: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e6360: sltu v0,v1,t1 */ set(2,cpu(3)<cpu(9));
/* 002e6364: bne v0,zero,0x002e6380 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6368 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));if(taken){goto L_002e6380;}}
/* 002e636c: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e6370: beql v0,zero,0x002e6384 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e6374 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));goto L_002e6384;}}
/* 002e6378: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002e637c: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
L_002e6380:;
/* 002e6380: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
L_002e6384:;
/* 002e6384: beql a2,zero,0x002e638c */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e6388 */ nocturneCompilerArithmeticTrap(7u);goto L_002e638c;}}
L_002e638c:;
/* 002e638c: divu v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),0,0);
/* 002e6390: andi a0,t3,0xffff */ set(4,cpu(11)&UINT32_C(0x0000ffff));
/* 002e6394: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e6398: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e639c: move a2,v0 */ set(6,cpu(2));
/* 002e63a0: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e63a4: mult a1,a2,t0 */ nativeMultiply(5,(uint32_t)cpu(6),(uint32_t)cpu(8),1,0);
/* 002e63a8: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e63ac: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e63b0: beq v0,zero,0x002e63dc */ {int taken=(cpu(2)==cpu(0));/* delay 002e63b4 */ set(2,sx((uint32_t)cpu(7)<<16));if(taken){goto L_002e63dc;}}
/* 002e63b8: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e63bc: sltu v0,v1,t1 */ set(2,cpu(3)<cpu(9));
/* 002e63c0: bne v0,zero,0x002e63d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e63c4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));if(taken){goto L_002e63d8;}}
/* 002e63c8: sltu v0,v1,a1 */ set(2,cpu(3)<cpu(5));
/* 002e63cc: addiu v1,a2,-0x1 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002e63d0: xori v0,v0,0x0 */ set(2,cpu(2)^UINT32_C(0x00000000));
/* 002e63d4: movn a2,v1,v0 */ if(cpu(2)!=0){set(6,cpu(3));}
L_002e63d8:;
/* 002e63d8: sll v0,a3,0x10 */ set(2,sx((uint32_t)cpu(7)<<16));
L_002e63dc:;
/* 002e63dc: b 0x002e6594 */ /* delay 002e63e0 */ set(6,cpu(2)|cpu(6));goto L_002e6594;
L_002e63e8:;
/* 002e63e8: beql v0,zero,0x002e63f8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e63ec */ set(2,cpu(0)|UINT32_C(0x0000ffff));goto L_002e63f8;}}
/* 002e63f0: b 0x002e6590 */ /* delay 002e63f4 */ set(6,cpu(0));goto L_002e6590;
L_002e63f8:;
/* 002e63f8: sltu v0,v0,t0 */ set(2,cpu(2)<cpu(8));
/* 002e63fc: bne v0,zero,0x002e6418 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6400 */ set(2,sx(UINT32_C(0x00ff0000)));if(taken){goto L_002e6418;}}
/* 002e6404: sltiu v0,t0,0x100 */ set(2,cpu(8)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000100));
/* 002e6408: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 002e640c: b 0x002e642c */ /* delay 002e6410 */ if(cpu(2)!=0){set(4,cpu(0));}goto L_002e642c;
L_002e6418:;
/* 002e6418: li v1,0x18 */ set(3,sx(UINT32_C(0x00000018)));
/* 002e641c: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002e6420: li a0,0x10 */ set(4,sx(UINT32_C(0x00000010)));
/* 002e6424: sltu v0,v0,t0 */ set(2,cpu(2)<cpu(8));
/* 002e6428: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002e642c:;
/* 002e642c: srlv v1,t0,a0 */ set(3,sx((uint32_t)cpu(8)>>((uint32_t)cpu(4)&31u)));
/* 002e6430: li a1,0x20 */ set(5,sx(UINT32_C(0x00000020)));
/* 002e6434: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002e6438: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002e643c: lbu v0,-0x4088(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0xffffbf78))));
/* 002e6440: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002e6444: subu a2,a1,v0 */ set(6,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));
/* 002e6448: bne a2,zero,0x002e6470 */ {int taken=(cpu(6)!=cpu(0));/* delay 002e644c */ set(7,sx((uint32_t)cpu(5)-(uint32_t)cpu(6)));if(taken){goto L_002e6470;}}
/* 002e6450: sltu v0,t0,t2 */ set(2,cpu(8)<cpu(10));
/* 002e6454: bne v0,zero,0x002e6590 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6458 */ set(6,sx(UINT32_C(0x00000001)));if(taken){goto L_002e6590;}}
/* 002e645c: sltu v0,t3,t1 */ set(2,cpu(11)<cpu(9));
/* 002e6460: bne v0,zero,0x002e6590 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6464 */ set(6,cpu(0));if(taken){goto L_002e6590;}}
/* 002e6468: b 0x002e6590 */ /* delay 002e646c */ set(6,sx(UINT32_C(0x00000001)));goto L_002e6590;
L_002e6470:;
/* 002e6470: sllv a0,t0,a2 */ set(4,sx((uint32_t)((uint32_t)cpu(8)<<((uint32_t)cpu(6)&31u))));
/* 002e6474: srlv a1,t3,a3 */ set(5,sx((uint32_t)cpu(11)>>((uint32_t)cpu(7)&31u)));
/* 002e6478: sllv t3,t3,a2 */ set(11,sx((uint32_t)((uint32_t)cpu(11)<<((uint32_t)cpu(6)&31u))));
/* 002e647c: srlv v0,t1,a3 */ set(2,sx((uint32_t)cpu(9)>>((uint32_t)cpu(7)&31u)));
/* 002e6480: sllv t1,t1,a2 */ set(9,sx((uint32_t)((uint32_t)cpu(9)<<((uint32_t)cpu(6)&31u))));
/* 002e6484: sllv v1,t2,a2 */ set(3,sx((uint32_t)((uint32_t)cpu(10)<<((uint32_t)cpu(6)&31u))));
/* 002e6488: or t0,a0,v0 */ set(8,cpu(4)|cpu(2));
/* 002e648c: srlv a0,t2,a3 */ set(4,sx((uint32_t)cpu(10)>>((uint32_t)cpu(7)&31u)));
/* 002e6490: or t2,v1,a1 */ set(10,cpu(3)|cpu(5));
/* 002e6494: srl a1,t0,0x10 */ set(5,sx((uint32_t)cpu(8)>>16));
/* 002e6498: divu a0,a1 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(5),0,0);
/* 002e649c: srl a0,t2,0x10 */ set(4,sx((uint32_t)cpu(10)>>16));
/* 002e64a0: andi t4,t0,0xffff */ set(12,cpu(8)&UINT32_C(0x0000ffff));
/* 002e64a4: beql a1,zero,0x002e64ac */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 002e64a8 */ nocturneCompilerArithmeticTrap(7u);goto L_002e64ac;}}
L_002e64ac:;
/* 002e64ac: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e64b0: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e64b4: move a3,v0 */ set(7,cpu(2));
/* 002e64b8: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e64bc: mult a2,a3,t4 */ nativeMultiply(6,(uint32_t)cpu(7),(uint32_t)cpu(12),1,0);
/* 002e64c0: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e64c4: sltu v0,v1,a2 */ set(2,cpu(3)<cpu(6));
/* 002e64c8: beql v0,zero,0x002e64fc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e64cc */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(6)));goto L_002e64fc;}}
/* 002e64d0: addu v1,v1,t0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(8)));
/* 002e64d4: sltu v0,v1,t0 */ set(2,cpu(3)<cpu(8));
/* 002e64d8: bne v0,zero,0x002e64f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e64dc */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));if(taken){goto L_002e64f8;}}
/* 002e64e0: sltu v0,v1,a2 */ set(2,cpu(3)<cpu(6));
/* 002e64e4: beql v0,zero,0x002e64fc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e64e8 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(6)));goto L_002e64fc;}}
/* 002e64ec: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002e64f0: addu v1,v1,t0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(8)));
/* 002e64f4: nop  */ 
L_002e64f8:;
/* 002e64f8: subu v1,v1,a2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(6)));
L_002e64fc:;
/* 002e64fc: beql a1,zero,0x002e6504 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 002e6500 */ nocturneCompilerArithmeticTrap(7u);goto L_002e6504;}}
L_002e6504:;
/* 002e6504: divu v1,a1 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(5),0,0);
/* 002e6508: andi a0,t2,0xffff */ set(4,cpu(10)&UINT32_C(0x0000ffff));
/* 002e650c: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e6510: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e6514: move a1,v0 */ set(5,cpu(2));
/* 002e6518: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e651c: mult a2,a1,t4 */ nativeMultiply(6,(uint32_t)cpu(5),(uint32_t)cpu(12),1,0);
/* 002e6520: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e6524: sltu v0,v1,a2 */ set(2,cpu(3)<cpu(6));
/* 002e6528: beq v0,zero,0x002e6558 */ {int taken=(cpu(2)==cpu(0));/* delay 002e652c */ set(2,sx((uint32_t)cpu(7)<<16));if(taken){goto L_002e6558;}}
/* 002e6530: addu v1,v1,t0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(8)));
/* 002e6534: sltu v0,v1,t0 */ set(2,cpu(3)<cpu(8));
/* 002e6538: bne v0,zero,0x002e6554 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e653c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));if(taken){goto L_002e6554;}}
/* 002e6540: sltu v0,v1,a2 */ set(2,cpu(3)<cpu(6));
/* 002e6544: beq v0,zero,0x002e6558 */ {int taken=(cpu(2)==cpu(0));/* delay 002e6548 */ set(2,sx((uint32_t)cpu(7)<<16));if(taken){goto L_002e6558;}}
/* 002e654c: addu v1,v1,t0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(8)));
/* 002e6550: addiu a1,a1,-0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
L_002e6554:;
/* 002e6554: sll v0,a3,0x10 */ set(2,sx((uint32_t)cpu(7)<<16));
L_002e6558:;
/* 002e6558: subu v1,v1,a2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(6)));
/* 002e655c: or a2,v0,a1 */ set(6,cpu(2)|cpu(5));
/* 002e6560: multu a2,t1 */ nativeMultiply(0,(uint32_t)cpu(6),(uint32_t)cpu(9),0,0);
/* 002e6564: mfhi a3 */ set(7,nocturneEffectHostHi());
/* 002e6568: mflo a0 */ set(4,nocturneEffectHostLo());
/* 002e656c: sltu v0,v1,a3 */ set(2,cpu(3)<cpu(7));
/* 002e6570: bnel v0,zero,0x002e6590 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002e6574 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));goto L_002e6590;}}
/* 002e6578: bne a3,v1,0x002e6594 */ {int taken=(cpu(7)!=cpu(3));/* delay 002e657c */ set(13,cpu(0));if(taken){goto L_002e6594;}}
/* 002e6580: sltu v0,t3,a0 */ set(2,cpu(11)<cpu(4));
/* 002e6584: beq v0,zero,0x002e6594 */ {int taken=(cpu(2)==cpu(0));/* delay 002e6588 */ if(taken){goto L_002e6594;}}
/* 002e658c: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
L_002e6590:;
/* 002e6590: move t5,zero */ set(13,cpu(0));
L_002e6594:;
/* 002e6594: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002e6598: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002e659c: dsll32 v0,a2,0x0 */ set(2,cpu(6)<<32);
/* 002e65a0: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002e65a4: and t6,t6,v1 */ set(14,cpu(14)&cpu(3));
/* 002e65a8: or t6,t6,v0 */ set(14,cpu(14)|cpu(2));
/* 002e65ac: dsll32 v0,t5,0x0 */ set(2,cpu(13)<<32);
/* 002e65b0: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 002e65b4: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002e65b8: and t6,t6,v1 */ set(14,cpu(14)&cpu(3));
/* 002e65bc: jr ra */ {uint64_t target=cpu(31);/* delay 002e65c0 */ set(2,cpu(14)|cpu(2));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionU64Numeric_002E6048(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002e6048();
return cpu(2);
}
static void body_002e65c8(void){
nocturneEffectAxisNoteEntry(0x002e65c8u);
uint64_t incoming=cpu(31);
/* 002e65c8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002e65cc: dsra32 t1,a1,0x0 */ set(9,(uint64_t)((int64_t)cpu(5)>>32));
/* 002e65d0: dsra32 t2,a0,0x0 */ set(10,(uint64_t)((int64_t)cpu(4)>>32));
/* 002e65d4: dsll32 a3,a1,0x0 */ set(7,cpu(5)<<32);
/* 002e65d8: dsra32 a3,a3,0x0 */ set(7,(uint64_t)((int64_t)cpu(7)>>32));
/* 002e65dc: dsll32 t5,a0,0x0 */ set(13,cpu(4)<<32);
/* 002e65e0: dsra32 t5,t5,0x0 */ set(13,(uint64_t)((int64_t)cpu(13)>>32));
/* 002e65e4: bne t1,zero,0x002e68a8 */ {int taken=(cpu(9)!=cpu(0));/* delay 002e65e8 */ set(24,cpu(29));if(taken){goto L_002e68a8;}}
/* 002e65ec: sltu v0,t2,a3 */ set(2,cpu(10)<cpu(7));
/* 002e65f0: beq v0,zero,0x002e6670 */ {int taken=(cpu(2)==cpu(0));/* delay 002e65f4 */ set(2,cpu(0)|UINT32_C(0x0000ffff));if(taken){goto L_002e6670;}}
/* 002e65f8: sltu v0,v0,a3 */ set(2,cpu(2)<cpu(7));
/* 002e65fc: bne v0,zero,0x002e6618 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6600 */ set(2,sx(UINT32_C(0x00ff0000)));if(taken){goto L_002e6618;}}
/* 002e6604: sltiu v0,a3,0x100 */ set(2,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000100));
/* 002e6608: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 002e660c: b 0x002e662c */ /* delay 002e6610 */ if(cpu(2)!=0){set(4,cpu(0));}goto L_002e662c;
L_002e6618:;
/* 002e6618: li v1,0x18 */ set(3,sx(UINT32_C(0x00000018)));
/* 002e661c: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002e6620: li a0,0x10 */ set(4,sx(UINT32_C(0x00000010)));
/* 002e6624: sltu v0,v0,a3 */ set(2,cpu(2)<cpu(7));
/* 002e6628: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002e662c:;
/* 002e662c: srlv v1,a3,a0 */ set(3,sx((uint32_t)cpu(7)>>((uint32_t)cpu(4)&31u)));
/* 002e6630: li a1,0x20 */ set(5,sx(UINT32_C(0x00000020)));
/* 002e6634: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002e6638: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002e663c: lbu v0,-0x3f88(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0xffffc078))));
/* 002e6640: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002e6644: subu t4,a1,v0 */ set(12,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));
/* 002e6648: beq t4,zero,0x002e6664 */ {int taken=(cpu(12)==cpu(0));/* delay 002e664c */ set(2,sx((uint32_t)cpu(5)-(uint32_t)cpu(12)));if(taken){goto L_002e6664;}}
/* 002e6650: sllv v1,t2,t4 */ set(3,sx((uint32_t)((uint32_t)cpu(10)<<((uint32_t)cpu(12)&31u))));
/* 002e6654: srlv v0,t5,v0 */ set(2,sx((uint32_t)cpu(13)>>((uint32_t)cpu(2)&31u)));
/* 002e6658: sllv t5,t5,t4 */ set(13,sx((uint32_t)((uint32_t)cpu(13)<<((uint32_t)cpu(12)&31u))));
/* 002e665c: or t2,v1,v0 */ set(10,cpu(3)|cpu(2));
/* 002e6660: sllv a3,a3,t4 */ set(7,sx((uint32_t)((uint32_t)cpu(7)<<((uint32_t)cpu(12)&31u))));
L_002e6664:;
/* 002e6664: srl a2,a3,0x10 */ set(6,sx((uint32_t)cpu(7)>>16));
/* 002e6668: b 0x002e67d0 */ /* delay 002e666c */ set(9,cpu(7)&UINT32_C(0x0000ffff));goto L_002e67d0;
L_002e6670:;
/* 002e6670: bne a3,zero,0x002e6698 */ {int taken=(cpu(7)!=cpu(0));/* delay 002e6674 */ set(2,cpu(2)<cpu(7));if(taken){goto L_002e6698;}}
/* 002e6678: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002e667c: beql a3,zero,0x002e6684 */ {int taken=(cpu(7)==cpu(0));if(taken){/* delay 002e6680 */ nocturneCompilerArithmeticTrap(7u);goto L_002e6684;}}
L_002e6684:;
/* 002e6684: divu v0,t1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(9),0,0);
/* 002e6688: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e668c: move a3,v0 */ set(7,cpu(2));
/* 002e6690: ori v0,zero,0xffff */ set(2,cpu(0)|UINT32_C(0x0000ffff));
/* 002e6694: sltu v0,v0,a3 */ set(2,cpu(2)<cpu(7));
L_002e6698:;
/* 002e6698: bne v0,zero,0x002e66b0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e669c */ set(2,sx(UINT32_C(0x00ff0000)));if(taken){goto L_002e66b0;}}
/* 002e66a0: sltiu v0,a3,0x100 */ set(2,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000100));
/* 002e66a4: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 002e66a8: b 0x002e66c4 */ /* delay 002e66ac */ if(cpu(2)!=0){set(4,cpu(0));}goto L_002e66c4;
L_002e66b0:;
/* 002e66b0: li v1,0x18 */ set(3,sx(UINT32_C(0x00000018)));
/* 002e66b4: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002e66b8: li a0,0x10 */ set(4,sx(UINT32_C(0x00000010)));
/* 002e66bc: sltu v0,v0,a3 */ set(2,cpu(2)<cpu(7));
/* 002e66c0: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002e66c4:;
/* 002e66c4: srlv v1,a3,a0 */ set(3,sx((uint32_t)cpu(7)>>((uint32_t)cpu(4)&31u)));
/* 002e66c8: li a1,0x20 */ set(5,sx(UINT32_C(0x00000020)));
/* 002e66cc: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002e66d0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002e66d4: lbu v0,-0x3f88(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0xffffc078))));
/* 002e66d8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002e66dc: subu t4,a1,v0 */ set(12,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));
/* 002e66e0: bne t4,zero,0x002e66f8 */ {int taken=(cpu(12)!=cpu(0));/* delay 002e66e4 */ set(15,sx((uint32_t)cpu(5)-(uint32_t)cpu(12)));if(taken){goto L_002e66f8;}}
/* 002e66e8: subu t2,t2,a3 */ set(10,sx((uint32_t)cpu(10)-(uint32_t)cpu(7)));
/* 002e66ec: srl a1,a3,0x10 */ set(5,sx((uint32_t)cpu(7)>>16));
/* 002e66f0: b 0x002e67c8 */ /* delay 002e66f4 */ set(14,cpu(7)&UINT32_C(0x0000ffff));goto L_002e67c8;
L_002e66f8:;
/* 002e66f8: sllv v1,t2,t4 */ set(3,sx((uint32_t)((uint32_t)cpu(10)<<((uint32_t)cpu(12)&31u))));
/* 002e66fc: srlv v0,t5,t7 */ set(2,sx((uint32_t)cpu(13)>>((uint32_t)cpu(15)&31u)));
/* 002e6700: sllv t5,t5,t4 */ set(13,sx((uint32_t)((uint32_t)cpu(13)<<((uint32_t)cpu(12)&31u))));
/* 002e6704: srlv a0,t2,t7 */ set(4,sx((uint32_t)cpu(10)>>((uint32_t)cpu(15)&31u)));
/* 002e6708: or t2,v1,v0 */ set(10,cpu(3)|cpu(2));
/* 002e670c: sllv a3,a3,t4 */ set(7,sx((uint32_t)((uint32_t)cpu(7)<<((uint32_t)cpu(12)&31u))));
/* 002e6710: srl a1,a3,0x10 */ set(5,sx((uint32_t)cpu(7)>>16));
/* 002e6714: divu a0,a1 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(5),0,0);
/* 002e6718: srl a0,t2,0x10 */ set(4,sx((uint32_t)cpu(10)>>16));
/* 002e671c: andi t6,a3,0xffff */ set(14,cpu(7)&UINT32_C(0x0000ffff));
/* 002e6720: move t1,a1 */ set(9,cpu(5));
/* 002e6724: beql t1,zero,0x002e672c */ {int taken=(cpu(9)==cpu(0));if(taken){/* delay 002e6728 */ nocturneCompilerArithmeticTrap(7u);goto L_002e672c;}}
L_002e672c:;
/* 002e672c: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e6730: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e6734: mult t0,v0,t6 */ nativeMultiply(8,(uint32_t)cpu(2),(uint32_t)cpu(14),1,0);
/* 002e6738: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e673c: or a2,v1,a0 */ set(6,cpu(3)|cpu(4));
/* 002e6740: sltu v0,a2,t0 */ set(2,cpu(6)<cpu(8));
/* 002e6744: beq v0,zero,0x002e6770 */ {int taken=(cpu(2)==cpu(0));/* delay 002e6748 */ set(15,cpu(14));if(taken){goto L_002e6770;}}
/* 002e674c: addu a2,a2,a3 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(7)));
/* 002e6750: sltu v0,a2,a3 */ set(2,cpu(6)<cpu(7));
/* 002e6754: bnel v0,zero,0x002e6774 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002e6758 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(8)));goto L_002e6774;}}
/* 002e675c: sltu v0,a2,t0 */ set(2,cpu(6)<cpu(8));
/* 002e6760: addu v1,a2,a3 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(7)));
/* 002e6764: xori v0,v0,0x0 */ set(2,cpu(2)^UINT32_C(0x00000000));
/* 002e6768: movn a2,v1,v0 */ if(cpu(2)!=0){set(6,cpu(3));}
/* 002e676c: nop  */ 
L_002e6770:;
/* 002e6770: subu a2,a2,t0 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(8)));
L_002e6774:;
/* 002e6774: andi a0,t2,0xffff */ set(4,cpu(10)&UINT32_C(0x0000ffff));
/* 002e6778: divu a2,t1 */ nativeDivide((uint32_t)cpu(6),(uint32_t)cpu(9),0,0);
/* 002e677c: beql t1,zero,0x002e6784 */ {int taken=(cpu(9)==cpu(0));if(taken){/* delay 002e6780 */ nocturneCompilerArithmeticTrap(7u);goto L_002e6784;}}
L_002e6784:;
/* 002e6784: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e6788: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e678c: mult t0,v0,t7 */ nativeMultiply(8,(uint32_t)cpu(2),(uint32_t)cpu(15),1,0);
/* 002e6790: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e6794: or a0,v1,a0 */ set(4,cpu(3)|cpu(4));
/* 002e6798: sltu v0,a0,t0 */ set(2,cpu(4)<cpu(8));
/* 002e679c: beq v0,zero,0x002e67c8 */ {int taken=(cpu(2)==cpu(0));/* delay 002e67a0 */ set(10,sx((uint32_t)cpu(4)-(uint32_t)cpu(8)));if(taken){goto L_002e67c8;}}
/* 002e67a4: addu a0,a0,a3 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 002e67a8: sltu v0,a0,a3 */ set(2,cpu(4)<cpu(7));
/* 002e67ac: bne v0,zero,0x002e67c8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e67b0 */ set(10,sx((uint32_t)cpu(4)-(uint32_t)cpu(8)));if(taken){goto L_002e67c8;}}
/* 002e67b4: sltu v0,a0,t0 */ set(2,cpu(4)<cpu(8));
/* 002e67b8: addu v1,a0,a3 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 002e67bc: xori v0,v0,0x0 */ set(2,cpu(2)^UINT32_C(0x00000000));
/* 002e67c0: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
/* 002e67c4: subu t2,a0,t0 */ set(10,sx((uint32_t)cpu(4)-(uint32_t)cpu(8)));
L_002e67c8:;
/* 002e67c8: move a2,a1 */ set(6,cpu(5));
/* 002e67cc: move t1,t6 */ set(9,cpu(14));
L_002e67d0:;
/* 002e67d0: divu t2,a2 */ nativeDivide((uint32_t)cpu(10),(uint32_t)cpu(6),0,0);
/* 002e67d4: srl a0,t5,0x10 */ set(4,sx((uint32_t)cpu(13)>>16));
/* 002e67d8: beql a2,zero,0x002e67e0 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e67dc */ nocturneCompilerArithmeticTrap(7u);goto L_002e67e0;}}
L_002e67e0:;
/* 002e67e0: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e67e4: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e67e8: mult t0,v0,t1 */ nativeMultiply(8,(uint32_t)cpu(2),(uint32_t)cpu(9),1,0);
/* 002e67ec: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e67f0: or a1,v1,a0 */ set(5,cpu(3)|cpu(4));
/* 002e67f4: sltu v0,a1,t0 */ set(2,cpu(5)<cpu(8));
/* 002e67f8: beql v0,zero,0x002e6824 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e67fc */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(8)));goto L_002e6824;}}
/* 002e6800: addu a1,a1,a3 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(7)));
/* 002e6804: sltu v0,a1,a3 */ set(2,cpu(5)<cpu(7));
/* 002e6808: bnel v0,zero,0x002e6824 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002e680c */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(8)));goto L_002e6824;}}
/* 002e6810: sltu v0,a1,t0 */ set(2,cpu(5)<cpu(8));
/* 002e6814: addu v1,a1,a3 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(7)));
/* 002e6818: xori v0,v0,0x0 */ set(2,cpu(2)^UINT32_C(0x00000000));
/* 002e681c: movn a1,v1,v0 */ if(cpu(2)!=0){set(5,cpu(3));}
/* 002e6820: subu a1,a1,t0 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(8)));
L_002e6824:;
/* 002e6824: andi a0,t5,0xffff */ set(4,cpu(13)&UINT32_C(0x0000ffff));
/* 002e6828: divu a1,a2 */ nativeDivide((uint32_t)cpu(5),(uint32_t)cpu(6),0,0);
/* 002e682c: beql a2,zero,0x002e6834 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e6830 */ nocturneCompilerArithmeticTrap(7u);goto L_002e6834;}}
L_002e6834:;
/* 002e6834: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e6838: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e683c: mult t0,v0,t1 */ nativeMultiply(8,(uint32_t)cpu(2),(uint32_t)cpu(9),1,0);
/* 002e6840: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e6844: or a0,v1,a0 */ set(4,cpu(3)|cpu(4));
/* 002e6848: sltu v0,a0,t0 */ set(2,cpu(4)<cpu(8));
/* 002e684c: beq v0,zero,0x002e6870 */ {int taken=(cpu(2)==cpu(0));/* delay 002e6850 */ if(taken){goto L_002e6870;}}
/* 002e6854: addu a0,a0,a3 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 002e6858: sltu v0,a0,a3 */ set(2,cpu(4)<cpu(7));
/* 002e685c: bne v0,zero,0x002e6870 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6860 */ set(2,cpu(4)<cpu(8));if(taken){goto L_002e6870;}}
/* 002e6864: addu v1,a0,a3 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 002e6868: xori v0,v0,0x0 */ set(2,cpu(2)^UINT32_C(0x00000000));
/* 002e686c: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002e6870:;
/* 002e6870: beq t8,zero,0x002e6b24 */ {int taken=(cpu(24)==cpu(0));/* delay 002e6874 */ set(13,sx((uint32_t)cpu(4)-(uint32_t)cpu(8)));if(taken){goto L_002e6b24;}}
/* 002e6878: srlv v0,t5,t4 */ set(2,sx((uint32_t)cpu(13)>>((uint32_t)cpu(12)&31u)));
/* 002e687c: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002e6880: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002e6884: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002e6888: and t3,t3,v1 */ set(11,cpu(11)&cpu(3));
/* 002e688c: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002e6890: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 002e6894: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002e6898: or t3,t3,v0 */ set(11,cpu(11)|cpu(2));
/* 002e689c: b 0x002e6b20 */ /* delay 002e68a0 */ set(11,cpu(11)&cpu(3));goto L_002e6b20;
L_002e68a8:;
/* 002e68a8: sltu v0,t2,t1 */ set(2,cpu(10)<cpu(9));
/* 002e68ac: beq v0,zero,0x002e68e8 */ {int taken=(cpu(2)==cpu(0));/* delay 002e68b0 */ set(2,cpu(0)|UINT32_C(0x0000ffff));if(taken){goto L_002e68e8;}}
/* 002e68b4: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002e68b8: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002e68bc: dsll32 v0,t5,0x0 */ set(2,cpu(13)<<32);
/* 002e68c0: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002e68c4: and t3,t3,v1 */ set(11,cpu(11)&cpu(3));
/* 002e68c8: or t3,t3,v0 */ set(11,cpu(11)|cpu(2));
/* 002e68cc: dsll32 v0,t2,0x0 */ set(2,cpu(10)<<32);
/* 002e68d0: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 002e68d4: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002e68d8: and t3,t3,v1 */ set(11,cpu(11)&cpu(3));
/* 002e68dc: or t3,t3,v0 */ set(11,cpu(11)|cpu(2));
/* 002e68e0: b 0x002e6b24 */ /* delay 002e68e4 */ save(11,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002e6b24;
L_002e68e8:;
/* 002e68e8: sltu v0,v0,t1 */ set(2,cpu(2)<cpu(9));
/* 002e68ec: bne v0,zero,0x002e6908 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e68f0 */ set(2,sx(UINT32_C(0x00ff0000)));if(taken){goto L_002e6908;}}
/* 002e68f4: sltiu v0,t1,0x100 */ set(2,cpu(9)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000100));
/* 002e68f8: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 002e68fc: b 0x002e691c */ /* delay 002e6900 */ if(cpu(2)!=0){set(4,cpu(0));}goto L_002e691c;
L_002e6908:;
/* 002e6908: li v1,0x18 */ set(3,sx(UINT32_C(0x00000018)));
/* 002e690c: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002e6910: li a0,0x10 */ set(4,sx(UINT32_C(0x00000010)));
/* 002e6914: sltu v0,v0,t1 */ set(2,cpu(2)<cpu(9));
/* 002e6918: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002e691c:;
/* 002e691c: srlv v1,t1,a0 */ set(3,sx((uint32_t)cpu(9)>>((uint32_t)cpu(4)&31u)));
/* 002e6920: li a1,0x20 */ set(5,sx(UINT32_C(0x00000020)));
/* 002e6924: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002e6928: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002e692c: lbu v0,-0x3f88(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0xffffc078))));
/* 002e6930: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002e6934: subu t4,a1,v0 */ set(12,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));
/* 002e6938: bne t4,zero,0x002e69a0 */ {int taken=(cpu(12)!=cpu(0));/* delay 002e693c */ set(15,sx((uint32_t)cpu(5)-(uint32_t)cpu(12)));if(taken){goto L_002e69a0;}}
/* 002e6940: sltu v0,t1,t2 */ set(2,cpu(9)<cpu(10));
/* 002e6944: bne v0,zero,0x002e6958 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6948 */ set(2,sx((uint32_t)cpu(13)-(uint32_t)cpu(7)));if(taken){goto L_002e6958;}}
/* 002e694c: sltu v0,t5,a3 */ set(2,cpu(13)<cpu(7));
/* 002e6950: bne v0,zero,0x002e6968 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6954 */ set(2,sx((uint32_t)cpu(13)-(uint32_t)cpu(7)));if(taken){goto L_002e6968;}}
L_002e6958:;
/* 002e6958: subu a0,t2,t1 */ set(4,sx((uint32_t)cpu(10)-(uint32_t)cpu(9)));
/* 002e695c: sltu v1,t5,v0 */ set(3,cpu(13)<cpu(2));
/* 002e6960: move t5,v0 */ set(13,cpu(2));
/* 002e6964: subu t2,a0,v1 */ set(10,sx((uint32_t)cpu(4)-(uint32_t)cpu(3)));
L_002e6968:;
/* 002e6968: beq t8,zero,0x002e6b24 */ {int taken=(cpu(24)==cpu(0));/* delay 002e696c */ set(2,cpu(13)<<32);if(taken){goto L_002e6b24;}}
/* 002e6970: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002e6974: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002e6978: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002e697c: and t3,t3,v1 */ set(11,cpu(11)&cpu(3));
/* 002e6980: or t3,t3,v0 */ set(11,cpu(11)|cpu(2));
/* 002e6984: dsll32 v0,t2,0x0 */ set(2,cpu(10)<<32);
/* 002e6988: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 002e698c: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002e6990: and t3,t3,v1 */ set(11,cpu(11)&cpu(3));
/* 002e6994: b 0x002e6b20 */ /* delay 002e6998 */ set(11,cpu(11)|cpu(2));goto L_002e6b20;
L_002e69a0:;
/* 002e69a0: sllv a1,t2,t4 */ set(5,sx((uint32_t)((uint32_t)cpu(10)<<((uint32_t)cpu(12)&31u))));
/* 002e69a4: sllv a0,t1,t4 */ set(4,sx((uint32_t)((uint32_t)cpu(9)<<((uint32_t)cpu(12)&31u))));
/* 002e69a8: srlv v0,a3,t7 */ set(2,sx((uint32_t)cpu(7)>>((uint32_t)cpu(15)&31u)));
/* 002e69ac: srlv v1,t5,t7 */ set(3,sx((uint32_t)cpu(13)>>((uint32_t)cpu(15)&31u)));
/* 002e69b0: sllv t5,t5,t4 */ set(13,sx((uint32_t)((uint32_t)cpu(13)<<((uint32_t)cpu(12)&31u))));
/* 002e69b4: or t1,a0,v0 */ set(9,cpu(4)|cpu(2));
/* 002e69b8: srlv a0,t2,t7 */ set(4,sx((uint32_t)cpu(10)>>((uint32_t)cpu(15)&31u)));
/* 002e69bc: sllv a3,a3,t4 */ set(7,sx((uint32_t)((uint32_t)cpu(7)<<((uint32_t)cpu(12)&31u))));
/* 002e69c0: or t2,a1,v1 */ set(10,cpu(5)|cpu(3));
/* 002e69c4: srl a2,t1,0x10 */ set(6,sx((uint32_t)cpu(9)>>16));
/* 002e69c8: divu a0,a2 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(6),0,0);
/* 002e69cc: srl a0,t2,0x10 */ set(4,sx((uint32_t)cpu(10)>>16));
/* 002e69d0: andi a1,t1,0xffff */ set(5,cpu(9)&UINT32_C(0x0000ffff));
/* 002e69d4: beql a2,zero,0x002e69dc */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e69d8 */ nocturneCompilerArithmeticTrap(7u);goto L_002e69dc;}}
L_002e69dc:;
/* 002e69dc: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e69e0: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e69e4: move t6,v0 */ set(14,cpu(2));
/* 002e69e8: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e69ec: mult t0,t6,a1 */ nativeMultiply(8,(uint32_t)cpu(14),(uint32_t)cpu(5),1,0);
/* 002e69f0: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002e69f4: sltu v0,v1,t0 */ set(2,cpu(3)<cpu(8));
/* 002e69f8: beql v0,zero,0x002e6a2c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e69fc */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(8)));goto L_002e6a2c;}}
/* 002e6a00: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e6a04: sltu v0,v1,t1 */ set(2,cpu(3)<cpu(9));
/* 002e6a08: bne v0,zero,0x002e6a28 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6a0c */ set(14,sx((uint32_t)cpu(14)+UINT32_C(0xffffffff)));if(taken){goto L_002e6a28;}}
/* 002e6a10: sltu v0,v1,t0 */ set(2,cpu(3)<cpu(8));
/* 002e6a14: beql v0,zero,0x002e6a2c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e6a18 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(8)));goto L_002e6a2c;}}
/* 002e6a1c: addiu t6,t6,-0x1 */ set(14,sx((uint32_t)cpu(14)+UINT32_C(0xffffffff)));
/* 002e6a20: addu v1,v1,t1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(9)));
/* 002e6a24: nop  */ 
L_002e6a28:;
/* 002e6a28: subu v1,v1,t0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(8)));
L_002e6a2c:;
/* 002e6a2c: beql a2,zero,0x002e6a34 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002e6a30 */ nocturneCompilerArithmeticTrap(7u);goto L_002e6a34;}}
L_002e6a34:;
/* 002e6a34: divu v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),0,0);
/* 002e6a38: andi a0,t2,0xffff */ set(4,cpu(10)&UINT32_C(0x0000ffff));
/* 002e6a3c: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002e6a40: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 002e6a44: move a2,v0 */ set(6,cpu(2));
/* 002e6a48: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002e6a4c: mult t0,a2,a1 */ nativeMultiply(8,(uint32_t)cpu(6),(uint32_t)cpu(5),1,0);
/* 002e6a50: or a1,v1,a0 */ set(5,cpu(3)|cpu(4));
/* 002e6a54: sltu v0,a1,t0 */ set(2,cpu(5)<cpu(8));
/* 002e6a58: beql v0,zero,0x002e6a88 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e6a5c */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(8)));goto L_002e6a88;}}
/* 002e6a60: addu a1,a1,t1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(9)));
/* 002e6a64: sltu v0,a1,t1 */ set(2,cpu(5)<cpu(9));
/* 002e6a68: bne v0,zero,0x002e6a84 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6a6c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));if(taken){goto L_002e6a84;}}
/* 002e6a70: sltu v0,a1,t0 */ set(2,cpu(5)<cpu(8));
/* 002e6a74: beql v0,zero,0x002e6a88 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002e6a78 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(8)));goto L_002e6a88;}}
/* 002e6a7c: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002e6a80: addu a1,a1,t1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(9)));
L_002e6a84:;
/* 002e6a84: subu a1,a1,t0 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(8)));
L_002e6a88:;
/* 002e6a88: sll v0,t6,0x10 */ set(2,sx((uint32_t)cpu(14)<<16));
/* 002e6a8c: or v0,v0,a2 */ set(2,cpu(2)|cpu(6));
/* 002e6a90: move t2,a1 */ set(10,cpu(5));
/* 002e6a94: multu v0,a3 */ nativeMultiply(0,(uint32_t)cpu(2),(uint32_t)cpu(7),0,0);
/* 002e6a98: mfhi a2 */ set(6,nocturneEffectHostHi());
/* 002e6a9c: mflo t0 */ set(8,nocturneEffectHostLo());
/* 002e6aa0: sltu v1,t2,a2 */ set(3,cpu(10)<cpu(6));
/* 002e6aa4: bne v1,zero,0x002e6ac0 */ {int taken=(cpu(3)!=cpu(0));/* delay 002e6aa8 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(7)));if(taken){goto L_002e6ac0;}}
/* 002e6aac: bne a2,t2,0x002e6ad0 */ {int taken=(cpu(6)!=cpu(10));/* delay 002e6ab0 */ set(2,cpu(13)<cpu(8));if(taken){goto L_002e6ad0;}}
/* 002e6ab4: beq v0,zero,0x002e6ad0 */ {int taken=(cpu(2)==cpu(0));/* delay 002e6ab8 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(7)));if(taken){goto L_002e6ad0;}}
/* 002e6abc: nop  */ 
L_002e6ac0:;
/* 002e6ac0: subu a0,a2,t1 */ set(4,sx((uint32_t)cpu(6)-(uint32_t)cpu(9)));
/* 002e6ac4: sltu v1,t0,v0 */ set(3,cpu(8)<cpu(2));
/* 002e6ac8: move t0,v0 */ set(8,cpu(2));
/* 002e6acc: subu a2,a0,v1 */ set(6,sx((uint32_t)cpu(4)-(uint32_t)cpu(3)));
L_002e6ad0:;
/* 002e6ad0: beq t8,zero,0x002e6b24 */ {int taken=(cpu(24)==cpu(0));/* delay 002e6ad4 */ set(4,sx((uint32_t)cpu(13)-(uint32_t)cpu(8)));if(taken){goto L_002e6b24;}}
/* 002e6ad8: subu a1,a1,a2 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(6)));
/* 002e6adc: sltu v1,t5,a0 */ set(3,cpu(13)<cpu(4));
/* 002e6ae0: subu t2,a1,v1 */ set(10,sx((uint32_t)cpu(5)-(uint32_t)cpu(3)));
/* 002e6ae4: sllv v0,t2,t7 */ set(2,sx((uint32_t)((uint32_t)cpu(10)<<((uint32_t)cpu(15)&31u))));
/* 002e6ae8: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002e6aec: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002e6af0: srlv a0,a0,t4 */ set(4,sx((uint32_t)cpu(4)>>((uint32_t)cpu(12)&31u)));
/* 002e6af4: and t3,t3,v1 */ set(11,cpu(11)&cpu(3));
/* 002e6af8: or v0,v0,a0 */ set(2,cpu(2)|cpu(4));
/* 002e6afc: lui a0,0xffff */ set(4,sx(UINT32_C(0xffff0000)));
/* 002e6b00: dsrl32 a0,a0,0x0 */ set(4,cpu(4)>>32);
/* 002e6b04: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002e6b08: srlv v1,t2,t4 */ set(3,sx((uint32_t)cpu(10)>>((uint32_t)cpu(12)&31u)));
/* 002e6b0c: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002e6b10: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002e6b14: or t3,t3,v0 */ set(11,cpu(11)|cpu(2));
/* 002e6b18: and t3,t3,a0 */ set(11,cpu(11)&cpu(4));
/* 002e6b1c: or t3,t3,v1 */ set(11,cpu(11)|cpu(3));
L_002e6b20:;
/* 002e6b20: sd t3,0x0(t8) */ save(11,ea(24,(int32_t)UINT32_C(0x00000000)));
L_002e6b24:;
/* 002e6b24: ld v0,0x0(sp) */ restore(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002e6b28: jr ra */ {uint64_t target=cpu(31);/* delay 002e6b2c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionU64Numeric_002E65C8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002e65c8();
return cpu(2);
}

