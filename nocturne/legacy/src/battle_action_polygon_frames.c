/* Complete original SLUS_209.11 resource/instance algorithms.
 * Each fixed C statement is tied to an original instruction. There is no
 * runtime instruction decoder, game-result provider, or expected-state input.
 * Guest frames are real shared RAM; only original stores initialize slots.
 */
#include "battle_action_consumer.h"
#include "battle_action_rotation_frame.h"
#include "effect_host_bindings.h"
#include "effect_model_child_dependency_frames.h"
#include "effect_packet_native_frames.h"
#include "effect_movie_native.h"
#include "effect_billboard_dependency_frames.h"
#include "effect_particle_camera_frames.h"
#include "effect_special_polygon_dependency_frames.h"
#include "effect_table_trig_frames.h"
#include "special_polygon_steps.h"
#include "battle_effect_copy.h"
#include "pcp_construction.h"
#include "model_pac_loading.h"
#include "model_loading_completion.h"
#include "resource_request_lifecycle.h"
#include "material_motion_scalars.h"
#include "libm_trig.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include <stdlib.h>
#include <string.h>

static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static float real(uint32_t u){float v;memcpy(&v,&u,4);return v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */
static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_polygon_frames.h"
#include "battle_action_status_resources.h"
#include "effect_particle_reset_frames.h"
#include "anchor_callbacks.h"
#include "magatuhi_helpers.h"
#include "compiler_numeric.h"
#include "effect_random_frames.h"
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneEffectHostHi(void);
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void polygonDivide(uint32_t a,uint32_t d,int signedDivide){
 uint32_t q,r;if(signedDivide){int64_t n=(int32_t)a,v=(int32_t)d;q=v?(uint32_t)(n/v):(n<0?1u:UINT32_MAX);r=v?(uint32_t)(n%v):a;}
 else{q=d?a/d:UINT32_MAX;r=d?a%d:a;}
 EE_ANCHOR_DIVU_STATE(q,r);
}

uint64_t ps2BattleActionPcpType0Create_001762F8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001762f8u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001762f8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001762fc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00176300: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00176304: move s1,a0 */ set(17,cpu(4));
/* 00176308: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0017630c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00176310: lw v0,0x14(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 00176314: sll a0,v0,0x1 */ set(4,sx((uint32_t)cpu(2)<<1));
/* 00176318: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0017631c: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00176320: subu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(2)));
/* 00176324: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00176328: jal 0x002a9038 */ set(31,0x00176330u);/* delay 0017632c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000064)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 00176330: move s2,v0 */ set(18,cpu(2));
/* 00176334: jal 0x002a9688 */ set(31,0x0017633cu);/* delay 00176338 */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 0017633c: move v1,s1 */ set(3,cpu(17));
/* 00176340: move s0,v0 */ set(16,cpu(2));
/* 00176344: or v0,s1,s0 */ set(2,cpu(17)|cpu(16));
/* 00176348: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
/* 0017634c: beq v0,zero,0x001763b8 */ {int taken=(cpu(2)==cpu(0));/* delay 00176350 */ set(4,cpu(16));if(taken){goto L_001763b8;}}
/* 00176354: addiu v0,s1,0x40 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000040)));
L_00176358:;
/* 00176358: ldl a1,0x7(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000007)),1);
/* 0017635c: ldr a1,0x0(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000000)),0);
/* 00176360: ldl a2,0xf(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
/* 00176364: ldr a2,0x8(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x00000008)),0);
/* 00176368: ldl a3,0x17(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000017)),1);
/* 0017636c: ldr a3,0x10(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000010)),0);
/* 00176370: ldl t0,0x1f(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x0000001f)),1);
/* 00176374: ldr t0,0x18(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x00000018)),0);
/* 00176378: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
/* 0017637c: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
/* 00176380: sdl a2,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),6,1);
/* 00176384: sdr a2,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),6,0);
/* 00176388: sdl a3,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),7,1);
/* 0017638c: sdr a3,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),7,0);
/* 00176390: sdl t0,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),8,1);
/* 00176394: sdr t0,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),8,0);
/* 00176398: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 0017639c: nop  */ 
/* 001763a0: nop  */ 
/* 001763a4: bne v1,v0,0x00176358 */ {int taken=(cpu(3)!=cpu(2));/* delay 001763a8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_00176358;}}
/* 001763ac: b 0x001763f0 */ /* delay 001763b0 */ goto L_001763f0;
L_001763b8:;
/* 001763b8: addiu v0,s1,0x40 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000040)));
L_001763bc:;
/* 001763bc: ld a1,0x0(v1) */ restore(5,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001763c0: ld a2,0x8(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001763c4: ld a3,0x10(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 001763c8: ld t0,0x18(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 001763cc: sd a1,0x0(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001763d0: sd a2,0x8(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 001763d4: sd a3,0x10(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 001763d8: sd t0,0x18(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001763dc: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001763e0: nop  */ 
/* 001763e4: nop  */ 
/* 001763e8: bne v1,v0,0x001763bc */ {int taken=(cpu(3)!=cpu(2));/* delay 001763ec */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_001763bc;}}
L_001763f0:;
/* 001763f0: ldl v0,0x7(v1) */ loadPartial(2,ea(3,(int32_t)UINT32_C(0x00000007)),1);
/* 001763f4: ldr v0,0x0(v1) */ loadPartial(2,ea(3,(int32_t)UINT32_C(0x00000000)),0);
/* 001763f8: lw a1,0x8(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001763fc: sdl v0,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),2,1);
/* 00176400: sdr v0,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),2,0);
/* 00176404: sw a1,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 00176408: addiu v0,s0,0x64 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000064)));
/* 0017640c: sw v0,0x4c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
/* 00176410: move a2,zero */ set(6,cpu(0));
/* 00176414: lwc1 f0,0x1c(s1) */ f[0]=word(ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 00176418: li a3,0x4 */ set(7,sx(UINT32_C(0x00000004)));
/* 0017641c: lw a0,0x14(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 00176420: swc1 f0,0x54(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000054)),f[0]);
/* 00176424: lhu a1,0x30(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000030))));
/* 00176428: lwc1 f0,0x20(s1) */ f[0]=word(ea(17,(int32_t)UINT32_C(0x00000020)));
/* 0017642c: sw s2,0x60(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(18));
/* 00176430: jal 0x00165eb8 */ set(31,0x00176438u);/* delay 00176434 */ sw(ea(16,(int32_t)UINT32_C(0x00000058)),f[0]);set(2,ps2BattleActionPolygonCreate_00165EB8(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 00176438: lw a1,0x38(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 0017643c: sw v0,0x5c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(2));
/* 00176440: move a0,v0 */ set(4,cpu(2));
/* 00176444: lw a2,0x40(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000040)));
/* 00176448: jal 0x00167710 */ set(31,0x00176450u);/* delay 0017644c */ lw(7,ea(16,(int32_t)UINT32_C(0x00000048)));ps2BattleActionPolygonSetColours_00167710(cpu(4),cpu(5),cpu(6),cpu(7));
/* 00176450: lw a0,0x5c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000005c)));
/* 00176454: jal 0x00167890 */ set(31,0x0017645cu);/* delay 00176458 */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000010))));ps2BattleActionPolygonSetMode_00167890(cpu(4),cpu(5));
/* 0017645c: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 00176460: beq v0,zero,0x00176490 */ {int taken=(cpu(2)==cpu(0));/* delay 00176464 */ set(4,cpu(0));if(taken){goto L_00176490;}}
/* 00176468: lw v1,0x4c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000004c)));
/* 0017646c: nop  */ 
L_00176470:;
/* 00176470: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 00176474: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00176478: sw zero,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 0017647c: sw zero,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 00176480: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 00176484: sltu v0,a0,v0 */ set(2,cpu(4)<cpu(2));
/* 00176488: bne v0,zero,0x00176470 */ {int taken=(cpu(2)!=cpu(0));/* delay 0017648c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x0000002c)));if(taken){goto L_00176470;}}
L_00176490:;
/* 00176490: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
/* 00176494: move v0,s0 */ set(2,cpu(16));
/* 00176498: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 0017649c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001764a0: sw v1,0x50(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
/* 001764a4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001764a8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001764ac: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001764b0: jr ra */ {uint64_t target=cpu(31);/* delay 001764b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPolygonCreate_00165EB8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectAxisNoteEntry(0x00165eb8u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00165eb8: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 00165ebc: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 00165ec0: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00165ec4: move s7,a3 */ set(23,cpu(7));
/* 00165ec8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00165ecc: move s3,a1 */ set(19,cpu(5));
/* 00165ed0: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00165ed4: move s5,a2 */ set(21,cpu(6));
/* 00165ed8: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00165edc: move s6,a0 */ set(22,cpu(4));
/* 00165ee0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00165ee4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00165ee8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00165eec: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00165ef0: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00165ef4: bne s7,v0,0x00165f10 */ {int taken=(cpu(23)!=cpu(2));/* delay 00165ef8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));if(taken){goto L_00165f10;}}
/* 00165efc: sll v0,s3,0x2 */ set(2,sx((uint32_t)cpu(19)<<2));
/* 00165f00: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 00165f04: b 0x00165fa0 */ /* delay 00165f08 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00000005)));goto L_00165fa0;
L_00165f10:;
/* 00165f10: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 00165f14: bne s7,v0,0x00165f28 */ {int taken=(cpu(23)!=cpu(2));/* delay 00165f18 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_00165f28;}}
/* 00165f1c: sll v0,s3,0x2 */ set(2,sx((uint32_t)cpu(19)<<2));
/* 00165f20: b 0x00165fa0 */ /* delay 00165f24 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));goto L_00165fa0;
L_00165f28:;
/* 00165f28: bne s7,v0,0x00165f40 */ {int taken=(cpu(23)!=cpu(2));/* delay 00165f2c */ set(2,sx((uint32_t)cpu(19)<<1));if(taken){goto L_00165f40;}}
/* 00165f30: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 00165f34: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00165f38: b 0x00165fa0 */ /* delay 00165f3c */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00000006)));goto L_00165fa0;
L_00165f40:;
/* 00165f40: beq s5,zero,0x00165f84 */ {int taken=(cpu(21)==cpu(0));/* delay 00165f44 */ set(19,sx((uint32_t)cpu(19)<<1));if(taken){goto L_00165f84;}}
/* 00165f48: div s3,s5 */ polygonDivide((uint32_t)cpu(19),(uint32_t)cpu(21),1);
/* 00165f4c: beql s5,zero,0x00165f54 */ {int taken=(cpu(21)==cpu(0));if(taken){/* delay 00165f50 */ nocturneCompilerArithmeticTrap(7u);goto L_00165f54;}}
L_00165f54:;
/* 00165f54: mfhi v0 */ set(2,nocturneEffectHostHi());
/* 00165f58: mflo a1 */ set(5,nocturneEffectHostLo());
/* 00165f5c: beq v0,zero,0x00165f78 */ {int taken=(cpu(2)==cpu(0));/* delay 00165f60 */ if(taken){goto L_00165f78;}}
/* 00165f64: beql s5,zero,0x00165f6c */ {int taken=(cpu(21)==cpu(0));if(taken){/* delay 00165f68 */ nocturneCompilerArithmeticTrap(7u);goto L_00165f6c;}}
L_00165f6c:;
/* 00165f6c: b 0x00165f84 */ /* delay 00165f70 */ set(19,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));goto L_00165f84;
L_00165f78:;
/* 00165f78: beql s5,zero,0x00165f80 */ {int taken=(cpu(21)==cpu(0));if(taken){/* delay 00165f7c */ nocturneCompilerArithmeticTrap(7u);goto L_00165f80;}}
L_00165f80:;
/* 00165f80: move s3,a1 */ set(19,cpu(5));
L_00165f84:;
/* 00165f84: li v0,-0x2 */ set(2,sx(UINT32_C(0xfffffffe)));
/* 00165f88: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00165f8c: and s3,s3,v0 */ set(19,cpu(19)&cpu(2));
/* 00165f90: bne s7,v1,0x00165fa0 */ {int taken=(cpu(23)!=cpu(3));/* delay 00165f94 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000002)));if(taken){goto L_00165fa0;}}
/* 00165f98: sra v0,s3,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(19)>>1)));
/* 00165f9c: addu s3,s3,v0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(2)));
L_00165fa0:;
/* 00165fa0: mult s2,s6,s3 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(22)*(int64_t)(int32_t)(uint32_t)cpu(19));EE_MAGATUHI_MULT_STATE(product);set(18,sx((uint32_t)product));}
/* 00165fa4: move s4,zero */ set(20,cpu(0));
/* 00165fa8: addu v0,s2,s6 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(22)));
/* 00165fac: sll s1,v0,0x2 */ set(17,sx((uint32_t)cpu(2)<<2));
/* 00165fb0: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 00165fb4: sll s1,s1,0x2 */ set(17,sx((uint32_t)cpu(17)<<2));
/* 00165fb8: jal 0x002a9038 */ set(31,0x00165fc0u);/* delay 00165fbc */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x0000002c)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 00165fc0: move s8,v0 */ set(30,cpu(2));
/* 00165fc4: jal 0x002a9688 */ set(31,0x00165fccu);/* delay 00165fc8 */ set(4,cpu(30));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 00165fcc: move a1,zero */ set(5,cpu(0));
/* 00165fd0: move s0,v0 */ set(16,cpu(2));
/* 00165fd4: li a2,0x2c */ set(6,sx(UINT32_C(0x0000002c)));
/* 00165fd8: addu s1,s0,s1 */ set(17,sx((uint32_t)cpu(16)+(uint32_t)cpu(17)));
/* 00165fdc: jal 0x002d4558 */ set(31,0x00165fe4u);/* delay 00165fe0 */ set(4,cpu(17));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 00165fe4: sw s0,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(16));
/* 00165fe8: sll v0,s2,0x4 */ set(2,sx((uint32_t)cpu(18)<<4));
/* 00165fec: sll s2,s2,0x2 */ set(18,sx((uint32_t)cpu(18)<<2));
/* 00165ff0: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00165ff4: sw s0,0x1c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(16));
/* 00165ff8: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 00165ffc: blez s6,0x00166058 */ {int taken=((int64_t)cpu(22)<=0);/* delay 00166000 */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(16));if(taken){goto L_00166058;}}
/* 00166004: move s0,zero */ set(16,cpu(0));
/* 00166008: move s2,zero */ set(18,cpu(0));
/* 0016600c: lw a2,0x18(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000018)));
L_00166010:;
/* 00166010: sll a1,s0,0x4 */ set(5,sx((uint32_t)cpu(16)<<4));
/* 00166014: lw v1,0x1c(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 00166018: sll a0,s0,0x2 */ set(4,sx((uint32_t)cpu(16)<<2));
/* 0016601c: lw v0,0x14(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 00166020: addu a2,a2,a1 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 00166024: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 00166028: move a0,s1 */ set(4,cpu(17));
/* 0016602c: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 00166030: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 00166034: sw v1,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 00166038: move a1,s4 */ set(5,cpu(20));
/* 0016603c: sw a2,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
/* 00166040: addiu s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
/* 00166044: jal 0x00166100 */ set(31,0x0016604cu);/* delay 00166048 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));ps2EffectParticlePolygonReset_00166100(cpu(4),cpu(5));
/* 0016604c: slt v0,s4,s6 */ set(2,(int64_t)cpu(20)<(int64_t)cpu(22));
/* 00166050: bnel v0,zero,0x00166010 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00166054 */ lw(6,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_00166010;}}
L_00166058:;
/* 00166058: jal 0x002b31e8 */ set(31,0x00166060u);/* delay 0016605c */ set(2,ps2EffectMatCreate_002B31E8());
/* 00166060: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00166064: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 00166068: sw v0,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 0016606c: jal 0x002b2ed8 */ set(31,0x00166074u);/* delay 00166070 */ set(4,cpu(2));ps2BattleActionMaterialSetConstant_002B2ED8(cpu(4),real(f[12]));
/* 00166074: sh s7,0x0(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(23));
/* 00166078: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0016607c: sw s6,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(22));
/* 00166080: sh v0,0x2(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));
/* 00166084: move v0,s1 */ set(2,cpu(17));
/* 00166088: sw s3,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));
/* 0016608c: sw s5,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(21));
/* 00166090: sw s8,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(30));
/* 00166094: sw zero,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 00166098: sw zero,0x28(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 0016609c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001660a0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001660a4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001660a8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001660ac: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001660b0: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001660b4: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001660b8: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001660bc: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001660c0: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001660c4: jr ra */ {uint64_t target=cpu(31);/* delay 001660c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionPolygonSetColours_00167710(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectAxisNoteEntry(0x00167710u);
uint64_t incoming=cpu(31);
uint32_t secondaryLo=0,secondaryHi=0; /* Actual DIVU1 always precedes MFLO1. */
/* 00167710: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00167714: move t1,a0 */ set(9,cpu(4));
/* 00167718: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016771c: li t0,0x5 */ set(8,sx(UINT32_C(0x00000005)));
/* 00167720: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00167724: lui v1,0xff00 */ set(3,sx(UINT32_C(0xff000000)));
/* 00167728: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0016772c: and s2,a2,v1 */ set(18,cpu(6)&cpu(3));
/* 00167730: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00167734: and s3,a1,v1 */ set(19,cpu(5)&cpu(3));
/* 00167738: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0016773c: and s4,a3,v1 */ set(20,cpu(7)&cpu(3));
/* 00167740: lui v0,0xff */ set(2,sx(UINT32_C(0x00ff0000)));
/* 00167744: beql t0,zero,0x0016774c */ {int taken=(cpu(8)==cpu(0));if(taken){/* delay 00167748 */ nocturneCompilerArithmeticTrap(7u);goto L_0016774c;}}
L_0016774c:;
/* 0016774c: lw a0,0x8(t1) */ lw(4,ea(9,(int32_t)UINT32_C(0x00000008)));
/* 00167750: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 00167754: lw t3,0x4(t1) */ lw(11,ea(9,(int32_t)UINT32_C(0x00000004)));
/* 00167758: and a1,a1,v0 */ set(5,cpu(5)&cpu(2));
/* 0016775c: div a0,t0 */ polygonDivide((uint32_t)cpu(4),(uint32_t)cpu(8),1);
/* 00167760: and a2,a2,v0 */ set(6,cpu(6)&cpu(2));
/* 00167764: and a3,a3,v0 */ set(7,cpu(7)&cpu(2));
/* 00167768: mflo a0 */ set(4,nocturneEffectHostLo());
/* 0016776c: sra t2,a0,0x1 */ set(10,sx((uint32_t)((int32_t)cpu(4)>>1)));
/* 00167770: divu s3,t2 */ polygonDivide((uint32_t)cpu(19),(uint32_t)cpu(10),0);
/* 00167774: divu1 s2,t2 */ {uint32_t n=(uint32_t)cpu(18),d=(uint32_t)cpu(10);secondaryLo=d?n/d:UINT32_MAX;secondaryHi=d?n%d:n;}
/* 00167778: mflo s1 */ set(17,nocturneEffectHostLo());
/* 0016777c: divu s4,t2 */ polygonDivide((uint32_t)cpu(20),(uint32_t)cpu(10),0);
/* 00167780: mflo1 s0 */ set(16,sx(secondaryLo));
/* 00167784: mflo t9 */ set(25,nocturneEffectHostLo());
/* 00167788: blezl t3,0x00167874 */ {int taken=((int64_t)cpu(11)<=0);if(taken){/* delay 0016778c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00167874;}}
/* 00167790: lw v0,0x14(t1) */ lw(2,ea(9,(int32_t)UINT32_C(0x00000014)));
/* 00167794: move t8,t3 */ set(24,cpu(11));
/* 00167798: addiu t7,v0,0x4 */ set(15,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 0016779c: nop  */ 
L_001677a0:;
/* 001677a0: lw t0,0x0(t7) */ lw(8,ea(15,(int32_t)UINT32_C(0x00000000)));
/* 001677a4: move t5,zero */ set(13,cpu(0));
/* 001677a8: move t4,zero */ set(12,cpu(0));
/* 001677ac: blez t2,0x00167804 */ {int taken=((int64_t)cpu(10)<=0);/* delay 001677b0 */ set(11,cpu(0));if(taken){goto L_00167804;}}
/* 001677b4: lui t6,0xff00 */ set(14,sx(UINT32_C(0xff000000)));
/* 001677b8: move t1,t2 */ set(9,cpu(10));
/* 001677bc: nop  */ 
L_001677c0:;
/* 001677c0: and a0,t3,t6 */ set(4,cpu(11)&cpu(14));
/* 001677c4: addu t3,t3,t9 */ set(11,sx((uint32_t)cpu(11)+(uint32_t)cpu(25)));
/* 001677c8: and v1,t4,t6 */ set(3,cpu(12)&cpu(14));
/* 001677cc: addu t4,t4,s0 */ set(12,sx((uint32_t)cpu(12)+(uint32_t)cpu(16)));
/* 001677d0: and v0,t5,t6 */ set(2,cpu(13)&cpu(14));
/* 001677d4: addu t5,t5,s1 */ set(13,sx((uint32_t)cpu(13)+(uint32_t)cpu(17)));
/* 001677d8: or a0,a3,a0 */ set(4,cpu(7)|cpu(4));
/* 001677dc: or v1,a2,v1 */ set(3,cpu(6)|cpu(3));
/* 001677e0: or v0,a1,v0 */ set(2,cpu(5)|cpu(2));
/* 001677e4: addiu t1,t1,-0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xffffffff)));
/* 001677e8: sw v0,0x8(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001677ec: sw v1,0xc(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 001677f0: sw a0,0x10(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(4));
/* 001677f4: sw a0,0x0(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001677f8: sw v1,0x4(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001677fc: bne t1,zero,0x001677c0 */ {int taken=(cpu(9)!=cpu(0));/* delay 00167800 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000014)));if(taken){goto L_001677c0;}}
L_00167804:;
/* 00167804: move t5,s3 */ set(13,cpu(19));
/* 00167808: move t4,s2 */ set(12,cpu(18));
/* 0016780c: blez t2,0x00167864 */ {int taken=((int64_t)cpu(10)<=0);/* delay 00167810 */ set(11,cpu(20));if(taken){goto L_00167864;}}
/* 00167814: lui t6,0xff00 */ set(14,sx(UINT32_C(0xff000000)));
/* 00167818: move t1,t2 */ set(9,cpu(10));
/* 0016781c: nop  */ 
L_00167820:;
/* 00167820: subu t5,t5,s1 */ set(13,sx((uint32_t)cpu(13)-(uint32_t)cpu(17)));
/* 00167824: subu t4,t4,s0 */ set(12,sx((uint32_t)cpu(12)-(uint32_t)cpu(16)));
/* 00167828: subu t3,t3,t9 */ set(11,sx((uint32_t)cpu(11)-(uint32_t)cpu(25)));
/* 0016782c: and a0,t4,t6 */ set(4,cpu(12)&cpu(14));
/* 00167830: and v1,t3,t6 */ set(3,cpu(11)&cpu(14));
/* 00167834: and v0,t5,t6 */ set(2,cpu(13)&cpu(14));
/* 00167838: or v1,a3,v1 */ set(3,cpu(7)|cpu(3));
/* 0016783c: or a0,a2,a0 */ set(4,cpu(6)|cpu(4));
/* 00167840: or v0,a1,v0 */ set(2,cpu(5)|cpu(2));
/* 00167844: addiu t1,t1,-0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xffffffff)));
/* 00167848: sw v0,0x8(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0016784c: sw a0,0xc(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
/* 00167850: sw v1,0x10(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 00167854: sw v1,0x0(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 00167858: sw a0,0x4(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 0016785c: bne t1,zero,0x00167820 */ {int taken=(cpu(9)!=cpu(0));/* delay 00167860 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000014)));if(taken){goto L_00167820;}}
L_00167864:;
/* 00167864: addiu t8,t8,-0x1 */ set(24,sx((uint32_t)cpu(24)+UINT32_C(0xffffffff)));
/* 00167868: bne t8,zero,0x001677a0 */ {int taken=(cpu(24)!=cpu(0));/* delay 0016786c */ set(15,sx((uint32_t)cpu(15)+UINT32_C(0x00000014)));if(taken){goto L_001677a0;}}
/* 00167870: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00167874:;
/* 00167874: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00167878: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0016787c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00167880: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00167884: jr ra */ {uint64_t target=cpu(31);/* delay 00167888 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
(void)secondaryHi; /* Final HI1 publication is outside current semantic profile. */
}
void ps2BattleActionPolygonSetMode_00167890(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x00167890u);
uint64_t incoming=cpu(31);
/* 00167890: jr ra */ {uint64_t target=cpu(31);/* delay 00167894 */ sh(ea(4,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(5));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionPcpType1Create_00178430(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00178430u);
uint64_t incoming=cpu(31);
/* 00178430: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00178434: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00178438: move s0,a0 */ set(16,cpu(4));
/* 0017843c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00178440: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00178444: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00178448: lw v0,0x24(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000024)));
/* 0017844c: sll a0,v0,0x1 */ set(4,sx((uint32_t)cpu(2)<<1));
/* 00178450: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00178454: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00178458: jal 0x002a9038 */ set(31,0x00178460u);/* delay 0017845c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000068)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 00178460: move s2,v0 */ set(18,cpu(2));
/* 00178464: jal 0x002a9688 */ set(31,0x0017846cu);/* delay 00178468 */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 0017846c: move s1,v0 */ set(17,cpu(2));
/* 00178470: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
/* 00178474: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
/* 00178478: beq v0,zero,0x001784e0 */ {int taken=(cpu(2)==cpu(0));/* delay 0017847c */ set(3,cpu(17));if(taken){goto L_001784e0;}}
/* 00178480: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_00178484:;
/* 00178484: ldl a0,0x7(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000007)),1);
/* 00178488: ldr a0,0x0(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000000)),0);
/* 0017848c: ldl a1,0xf(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
/* 00178490: ldr a1,0x8(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000008)),0);
/* 00178494: ldl a2,0x17(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000017)),1);
/* 00178498: ldr a2,0x10(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000010)),0);
/* 0017849c: ldl a3,0x1f(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
/* 001784a0: ldr a3,0x18(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000018)),0);
/* 001784a4: sdl a0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),4,1);
/* 001784a8: sdr a0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),4,0);
/* 001784ac: sdl a1,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),5,1);
/* 001784b0: sdr a1,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),5,0);
/* 001784b4: sdl a2,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),6,1);
/* 001784b8: sdr a2,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),6,0);
/* 001784bc: sdl a3,0x1f(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000001f)),7,1);
/* 001784c0: sdr a3,0x18(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000018)),7,0);
/* 001784c4: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
/* 001784c8: nop  */ 
/* 001784cc: nop  */ 
/* 001784d0: bne s0,v0,0x00178484 */ {int taken=(cpu(16)!=cpu(2));/* delay 001784d4 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(taken){goto L_00178484;}}
/* 001784d8: b 0x00178518 */ /* delay 001784dc */ goto L_00178518;
L_001784e0:;
/* 001784e0: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_001784e4:;
/* 001784e4: ld a0,0x0(s0) */ restore(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001784e8: ld a1,0x8(s0) */ restore(5,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001784ec: ld a2,0x10(s0) */ restore(6,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 001784f0: ld a3,0x18(s0) */ restore(7,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001784f4: sd a0,0x0(v1) */ save(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001784f8: sd a1,0x8(v1) */ save(5,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001784fc: sd a2,0x10(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 00178500: sd a3,0x18(v1) */ save(7,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 00178504: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
/* 00178508: nop  */ 
/* 0017850c: nop  */ 
/* 00178510: bne s0,v0,0x001784e4 */ {int taken=(cpu(16)!=cpu(2));/* delay 00178514 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(taken){goto L_001784e4;}}
L_00178518:;
/* 00178518: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
/* 0017851c: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
/* 00178520: ldl a0,0xf(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
/* 00178524: ldr a0,0x8(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000008)),0);
/* 00178528: lw a1,0x10(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0017852c: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
/* 00178530: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
/* 00178534: sdl a0,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),4,1);
/* 00178538: sdr a0,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),4,0);
/* 0017853c: li a3,0x4 */ set(7,sx(UINT32_C(0x00000004)));
/* 00178540: sw a1,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));
/* 00178544: addiu v0,s1,0x68 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000068)));
/* 00178548: sw v0,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));
/* 0017854c: move a2,zero */ set(6,cpu(0));
/* 00178550: lhu a1,0x38(s1) */ set(5,half(ea(17,(int32_t)UINT32_C(0x00000038))));
/* 00178554: move s0,zero */ set(16,cpu(0));
/* 00178558: lw a0,0x24(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 0017855c: sw s2,0x64(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000064)),(uint32_t)cpu(18));
/* 00178560: sll a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)<<1));
/* 00178564: jal 0x00165eb8 */ set(31,0x0017856cu);/* delay 00178568 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));set(2,ps2BattleActionPolygonCreate_00165EB8(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 0017856c: lw a1,0x40(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000040)));
/* 00178570: sw v0,0x60(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(2));
/* 00178574: move a0,v0 */ set(4,cpu(2));
/* 00178578: lw a2,0x48(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000048)));
/* 0017857c: jal 0x00167710 */ set(31,0x00178584u);/* delay 00178580 */ lw(7,ea(17,(int32_t)UINT32_C(0x00000050)));ps2BattleActionPolygonSetColours_00167710(cpu(4),cpu(5),cpu(6),cpu(7));
/* 00178584: lw a0,0x60(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000060)));
/* 00178588: jal 0x00167890 */ set(31,0x00178590u);/* delay 0017858c */ set(5,half(ea(17,(int32_t)UINT32_C(0x00000020))));ps2BattleActionPolygonSetMode_00167890(cpu(4),cpu(5));
/* 00178590: lw v0,0x24(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 00178594: beq v0,zero,0x001785bc */ {int taken=(cpu(2)==cpu(0));/* delay 00178598 */ set(5,cpu(16));if(taken){goto L_001785bc;}}
/* 0017859c: nop  */ 
L_001785a0:;
/* 001785a0: addiu s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
/* 001785a4: jal 0x001786d0 */ set(31,0x001785acu);/* delay 001785a8 */ set(4,cpu(17));ps2BattleActionPcpType1Reset_001786D0(cpu(4),cpu(5));
/* 001785ac: lw v0,0x24(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 001785b0: sltu v0,s0,v0 */ set(2,cpu(16)<cpu(2));
/* 001785b4: bne v0,zero,0x001785a0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001785b8 */ set(5,cpu(16));if(taken){goto L_001785a0;}}
L_001785bc:;
/* 001785bc: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
/* 001785c0: move v0,s1 */ set(2,cpu(17));
/* 001785c4: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 001785c8: sw zero,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(0));
/* 001785cc: sw v1,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(3));
/* 001785d0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001785d4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001785d8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001785dc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001785e0: jr ra */ {uint64_t target=cpu(31);/* delay 001785e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionPcpType1Reset_001786D0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x001786d0u);
uint64_t incoming=cpu(31);
/* 001786d0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001786d4: sll v0,a1,0x1 */ set(2,sx((uint32_t)cpu(5)<<1));
/* 001786d8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001786dc: lui s0,0x31 */ set(16,sx(UINT32_C(0x00310000)));
/* 001786e0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001786e4: move s2,a0 */ set(18,cpu(4));
/* 001786e8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001786ec: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 001786f0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001786f4: addiu s0,s0,0x6fe0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00006fe0)));
/* 001786f8: move a0,s0 */ set(4,cpu(16));
/* 001786fc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00178700: lw s1,0x54(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000054)));
/* 00178704: jal 0x002c0ba8 */ set(31,0x0017870cu);/* delay 00178708 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));set(2,ps2EffectRandomWord_002C0BA8(cpu(4)));
/* 0017870c: lw v1,0x30(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000030)));
/* 00178710: move a0,s0 */ set(4,cpu(16));
/* 00178714: divu v0,v1 */ polygonDivide((uint32_t)cpu(2),(uint32_t)cpu(3),0);
/* 00178718: beql v1,zero,0x00178720 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0017871c */ nocturneCompilerArithmeticTrap(7u);goto L_00178720;}}
L_00178720:;
/* 00178720: mfhi a1 */ set(5,nocturneEffectHostHi());
/* 00178724: jal 0x002c0ba8 */ set(31,0x0017872cu);/* delay 00178728 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));set(2,ps2EffectRandomWord_002C0BA8(cpu(4)));
/* 0017872c: lw v1,0x34(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000034)));
/* 00178730: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 00178734: divu v0,v1 */ polygonDivide((uint32_t)cpu(2),(uint32_t)cpu(3),0);
/* 00178738: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0017873c: beql v1,zero,0x00178744 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00178740 */ nocturneCompilerArithmeticTrap(7u);goto L_00178744;}}
L_00178744:;
/* 00178744: sw a0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 00178748: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0017874c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00178750: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00178754: mfhi a1 */ set(5,nocturneEffectHostHi());
/* 00178758: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0017875c: sw a1,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 00178760: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00178764: jr ra */ {uint64_t target=cpu(31);/* delay 00178768 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
