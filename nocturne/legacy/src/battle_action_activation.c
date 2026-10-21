/* Complete original SLUS_209.11 resource/instance algorithms.
 * Each fixed C statement is tied to an original instruction. There is no
 * runtime instruction decoder, game-result provider, or expected-state input.
 * Guest frames are real shared RAM; only original stores initialize slots.
 */
#include "battle_action_consumer.h"
#include "battle_action_rotation_frame.h"
#include "battle_action_status_resources.h"
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
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
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


#include "battle_action_activation.h"
#include "battle_action_copy_frames.h"
#include "d3p_loading.h"
#include "libc_printf.h"
#include "compiler_numeric.h"
#include "anchor_callbacks.h"
/* Pure code-address dispatch to actual recovered functions. These endpoints
 * supply no game results; their unsupported targets must be rejected. */
extern uint64_t nocturneBattleActionPartCreation(uint32_t target,uint64_t source);
extern uint64_t nocturneBattleActionPcpConstructorCall(uint32_t target,uint64_t source);
extern void nocturneBattleActionEffectScale(uint32_t target,uint64_t object,uint32_t scale);
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneEffectHostHi(void);
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void activationDivu(uint32_t a,uint32_t b){uint32_t q=b?a/b:UINT32_MAX,r=b?a%b:a;EE_ANCHOR_DIVU_STATE(q,r);}


uint64_t ps2BattleAction_0016A9C0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0016a9c0);
 uint64_t incomingRa=cpu(31);
 /* 0016a9c0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 0016a9c4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0016a9c8: move s2,a0 */ set(18,cpu(4));
 /* 0016a9cc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0016a9d0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0016a9d4: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0016a9d8: jal 0x002a9038 */ set(31,sx(UINT32_C(0x0016a9e0)));/* delay 0016a9dc */ set(4,sx(UINT32_C(0x00000c44)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 0016a9e0: move s0,v0 */ set(16,cpu(2));
 /* 0016a9e4: jal 0x002a9688 */ set(31,sx(UINT32_C(0x0016a9ec)));/* delay 0016a9e8 */ set(4,cpu(16));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 0016a9ec: move v1,s2 */ set(3,cpu(18));
 /* 0016a9f0: move s1,v0 */ set(17,cpu(2));
 /* 0016a9f4: or v0,s2,s1 */ set(2,cpu(18)|cpu(17));
 /* 0016a9f8: sw s0,0xc38(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000c38)),(uint32_t)cpu(16));
 /* 0016a9fc: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 0016aa00: beq v0,zero,0x0016aa68 */ {int take=(cpu(2)==cpu(0));/* delay 0016aa04 */ set(4,cpu(17));if(take){goto L_0016aa68;}}
 /* 0016aa08: addiu v0,s2,0xc20 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000c20)));
L_0016aa0c:;
 /* 0016aa0c: ldl a1,0x7(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000007)),1);
 /* 0016aa10: ldr a1,0x0(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000000)),0);
 /* 0016aa14: ldl a2,0xf(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0016aa18: ldr a2,0x8(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x00000008)),0);
 /* 0016aa1c: ldl a3,0x17(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000017)),1);
 /* 0016aa20: ldr a3,0x10(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000010)),0);
 /* 0016aa24: ldl t0,0x1f(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0016aa28: ldr t0,0x18(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x00000018)),0);
 /* 0016aa2c: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
 /* 0016aa30: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
 /* 0016aa34: sdl a2,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),6,1);
 /* 0016aa38: sdr a2,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),6,0);
 /* 0016aa3c: sdl a3,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),7,1);
 /* 0016aa40: sdr a3,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),7,0);
 /* 0016aa44: sdl t0,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),8,1);
 /* 0016aa48: sdr t0,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),8,0);
 /* 0016aa4c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
 /* 0016aa50: nop  */ 
 /* 0016aa54: nop  */ 
 /* 0016aa58: bne v1,v0,0x0016aa0c */ {int take=(cpu(3)!=cpu(2));/* delay 0016aa5c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(take){goto L_0016aa0c;}}
 /* 0016aa60: b 0x0016aaa0 */ /* delay 0016aa64 */ goto L_0016aaa0;
L_0016aa68:;
 /* 0016aa68: addiu v0,s2,0xc20 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000c20)));
L_0016aa6c:;
 /* 0016aa6c: ld a1,0x0(v1) */ restore(5,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 0016aa70: ld a2,0x8(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 0016aa74: ld a3,0x10(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 0016aa78: ld t0,0x18(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 0016aa7c: sd a1,0x0(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000000)));
 /* 0016aa80: sd a2,0x8(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000008)));
 /* 0016aa84: sd a3,0x10(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000010)));
 /* 0016aa88: sd t0,0x18(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000018)));
 /* 0016aa8c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
 /* 0016aa90: nop  */ 
 /* 0016aa94: nop  */ 
 /* 0016aa98: bne v1,v0,0x0016aa6c */ {int take=(cpu(3)!=cpu(2));/* delay 0016aa9c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(take){goto L_0016aa6c;}}
L_0016aaa0:;
 /* 0016aaa0: ldl v0,0x7(v1) */ loadPartial(2,ea(3,(int32_t)UINT32_C(0x00000007)),1);
 /* 0016aaa4: ldr v0,0x0(v1) */ loadPartial(2,ea(3,(int32_t)UINT32_C(0x00000000)),0);
 /* 0016aaa8: ldl a1,0xf(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0016aaac: ldr a1,0x8(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000008)),0);
 /* 0016aab0: ldl a2,0x17(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x00000017)),1);
 /* 0016aab4: ldr a2,0x10(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x00000010)),0);
 /* 0016aab8: sdl v0,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 0016aabc: sdr v0,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 0016aac0: sdl a1,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),5,1);
 /* 0016aac4: sdr a1,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),5,0);
 /* 0016aac8: sdl a2,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),6,1);
 /* 0016aacc: sdr a2,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),6,0);
 /* 0016aad0: move a1,s2 */ set(5,cpu(18));
 /* 0016aad4: jal 0x0016b588 */ set(31,sx(UINT32_C(0x0016aadc)));/* delay 0016aad8 */ set(4,cpu(17));ps2BattleAction_0016B588(cpu(4),cpu(5));
 /* 0016aadc: sw zero,0xc3c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000c3c)),(uint32_t)cpu(0));
 /* 0016aae0: sw zero,0xc40(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000c40)),(uint32_t)cpu(0));
 /* 0016aae4: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
 /* 0016aae8: jal 0x002d4748 */ set(31,sx(UINT32_C(0x0016aaf0)));/* delay 0016aaec */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00002e20)));set(2,ps2LibcPrintf(cpu(4)));
 /* 0016aaf0: move v0,s1 */ set(2,cpu(17));
 /* 0016aaf4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0016aaf8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0016aafc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0016ab00: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0016ab04: jr ra */ {uint64_t target=cpu(31);/* delay 0016ab08 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

void ps2BattleAction_0016B588(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x0016b588);
 uint64_t incomingRa=cpu(31);
 /* 0016b588: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
 /* 0016b58c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 0016b590: move s5,a0 */ set(21,cpu(4));
 /* 0016b594: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0016b598: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0016b59c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0016b5a0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0016b5a4: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
 /* 0016b5a8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0016b5ac: addiu s4,s5,0x74 */ set(20,sx((uint32_t)cpu(21)+UINT32_C(0x00000074)));
 /* 0016b5b0: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 0016b5b4: move s6,a1 */ set(22,cpu(5));
 /* 0016b5b8: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
 /* 0016b5bc: li s7,0x1 */ set(23,sx(UINT32_C(0x00000001)));
 /* 0016b5c0: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
 /* 0016b5c4: move s8,zero */ set(30,cpu(0));
L_0016b5c8:;
 /* 0016b5c8: lhu v1,0x0(s4) */ set(3,half(ea(20,(int32_t)UINT32_C(0x00000000))));
 /* 0016b5cc: addu v0,s5,s8 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(30)));
 /* 0016b5d0: beq v1,zero,0x0016b684 */ {int take=(cpu(3)==cpu(0));/* delay 0016b5d4 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00000080)));if(take){goto L_0016b684;}}
 /* 0016b5d8: move s2,v1 */ set(18,cpu(3));
 /* 0016b5dc: li s3,0x3c */ set(19,sx(UINT32_C(0x0000003c)));
L_0016b5e0:;
 /* 0016b5e0: lhu v0,0x0(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x00000000))));
 /* 0016b5e4: ori v1,zero,0xfffe */ set(3,cpu(0)|UINT32_C(0x0000fffe));
 /* 0016b5e8: beq v0,v1,0x0016b678 */ {int take=(cpu(2)==cpu(3));/* delay 0016b5ec */ set(3,cpu(0)|UINT32_C(0x0000ffff));if(take){goto L_0016b678;}}
 /* 0016b5f0: bnel v0,v1,0x0016b650 */ {int take=(cpu(2)!=cpu(3));if(take){/* delay 0016b5f4 */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));goto L_0016b650;}}
 /* 0016b5f8: lw v1,0x4(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000004)));
 /* 0016b5fc: beql s3,zero,0x0016b604 */ {int take=(cpu(19)==cpu(0));if(take){/* delay 0016b600 */ nocturneCompilerArithmeticTrap(7u);goto L_0016b604;}}
L_0016b604:;
 /* 0016b604: divu v1,s3 */ activationDivu((uint32_t)cpu(3),(uint32_t)cpu(19));
 /* 0016b608: mflo v1 */ set(3,nocturneEffectHostLo());
 /* 0016b60c: mfhi a0 */ set(4,nocturneEffectHostHi());
 /* 0016b610: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
 /* 0016b614: sll s0,a0,0x1 */ set(16,sx((uint32_t)cpu(4)<<1));
 /* 0016b618: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
 /* 0016b61c: addu s0,s0,a0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(4)));
 /* 0016b620: sll v1,v0,0x6 */ set(3,sx((uint32_t)cpu(2)<<6));
 /* 0016b624: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
 /* 0016b628: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
 /* 0016b62c: sll s0,s0,0x3 */ set(16,sx((uint32_t)cpu(16)<<3));
 /* 0016b630: addu s0,s0,s5 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));
 /* 0016b634: addiu s0,s0,0x80 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000080)));
 /* 0016b638: jal 0x00175a88 */ set(31,sx(UINT32_C(0x0016b640)));/* delay 0016b63c */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
 /* 0016b640: lhu v1,0x0(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000000))));
 /* 0016b644: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
 /* 0016b648: b 0x0016b660 */ /* delay 0016b64c */ sh(ea(17,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));goto L_0016b660;
L_0016b650:;
 /* 0016b650: lhu a0,0x0(s1) */ set(4,half(ea(17,(int32_t)UINT32_C(0x00000000))));
 /* 0016b654: jal 0x00175998 */ set(31,sx(UINT32_C(0x0016b65c)));/* delay 0016b658 */ set(5,sx((uint32_t)cpu(22)+(uint32_t)cpu(5)));set(2,ps2BattleActionPartCreate_00175998(cpu(4),cpu(5)));
 /* 0016b65c: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_0016b660:;
 /* 0016b660: lhu v0,0x0(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x00000000))));
 /* 0016b664: bnel v0,zero,0x0016b67c */ {int take=(cpu(2)!=cpu(0));if(take){/* delay 0016b668 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));goto L_0016b67c;}}
 /* 0016b66c: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0016b670: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
 /* 0016b674: sw v0,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
L_0016b678:;
 /* 0016b678: addiu s2,s2,-0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));
L_0016b67c:;
 /* 0016b67c: bne s2,zero,0x0016b5e0 */ {int take=(cpu(18)!=cpu(0));/* delay 0016b680 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));if(take){goto L_0016b5e0;}}
L_0016b684:;
 /* 0016b684: addiu s7,s7,-0x1 */ set(23,sx((uint32_t)cpu(23)+UINT32_C(0xffffffff)));
 /* 0016b688: addiu s4,s4,0x618 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000618)));
 /* 0016b68c: bgez s7,0x0016b5c8 */ {int take=((int64_t)cpu(23)>=0);/* delay 0016b690 */ set(30,sx((uint32_t)cpu(30)+UINT32_C(0x00000618)));if(take){goto L_0016b5c8;}}
 /* 0016b694: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0016b698: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0016b69c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0016b6a0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0016b6a4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0016b6a8: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 0016b6ac: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 0016b6b0: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
 /* 0016b6b4: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
 /* 0016b6b8: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
 /* 0016b6bc: jr ra */ {uint64_t target=cpu(31);/* delay 0016b6c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incomingRa);return;}
}

void ps2BattleAction_0016FE88(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x0016fe88);
 uint64_t incomingRa=cpu(31);
 /* 0016fe88: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
 /* 0016fe8c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0016fe90: move s1,a1 */ set(17,cpu(5));
 /* 0016fe94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0016fe98: move s0,a0 */ set(16,cpu(4));
 /* 0016fe9c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0016fea0: move s2,zero */ set(18,cpu(0));
 /* 0016fea4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0016fea8: beq s1,zero,0x0016ff10 */ {int take=(cpu(17)==cpu(0));/* delay 0016feac */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(take){goto L_0016ff10;}}
 /* 0016feb0: ori s3,zero,0xfffd */ set(19,cpu(0)|UINT32_C(0x0000fffd));
 /* 0016feb4: nop  */ 
L_0016feb8:;
 /* 0016feb8: lhu v1,0xc(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
 /* 0016febc: bnel v1,zero,0x0016fefc */ {int take=(cpu(3)!=cpu(0));if(take){/* delay 0016fec0 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));goto L_0016fefc;}}
 /* 0016fec4: lhu v0,0x0(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000000))));
 /* 0016fec8: beq v0,s3,0x0016fee8 */ {int take=(cpu(2)==cpu(19));/* delay 0016fecc */ if(take){goto L_0016fee8;}}
 /* 0016fed0: lw a1,0x8(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000008)));
 /* 0016fed4: jal 0x00175998 */ set(31,sx(UINT32_C(0x0016fedc)));/* delay 0016fed8 */ set(4,cpu(2));set(2,ps2BattleActionPartCreate_00175998(cpu(4),cpu(5)));
 /* 0016fedc: lhu v1,0xc(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
 /* 0016fee0: b 0x0016fef8 */ /* delay 0016fee4 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));goto L_0016fef8;
L_0016fee8:;
 /* 0016fee8: jal 0x0016a9c0 */ set(31,sx(UINT32_C(0x0016fef0)));/* delay 0016feec */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));set(2,ps2BattleAction_0016A9C0(cpu(4)));
 /* 0016fef0: lhu v1,0xc(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
 /* 0016fef4: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
L_0016fef8:;
 /* 0016fef8: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
L_0016fefc:;
 /* 0016fefc: addiu v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
 /* 0016ff00: sltu v1,s2,s1 */ set(3,cpu(18)<cpu(17));
 /* 0016ff04: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
 /* 0016ff08: bne v1,zero,0x0016feb8 */ {int take=(cpu(3)!=cpu(0));/* delay 0016ff0c */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x0000001c)));if(take){goto L_0016feb8;}}
L_0016ff10:;
 /* 0016ff10: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0016ff14: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0016ff18: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0016ff1c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0016ff20: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0016ff24: jr ra */ {uint64_t target=cpu(31);/* delay 0016ff28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incomingRa);return;}
}

uint64_t ps2BattleActionPartCreate_00175998(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x00175998);
 uint64_t incomingRa=cpu(31);
 /* 00175998: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 0017599c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001759a0: andi s0,a0,0xffff */ set(16,cpu(4)&UINT32_C(0x0000ffff));
 /* 001759a4: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
 /* 001759a8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001759ac: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001759b0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001759b4: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x001759bc)));/* delay 001759b8 */ set(18,cpu(5));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 001759bc: sll v1,s0,0x2 */ set(3,sx((uint32_t)cpu(16)<<2));
 /* 001759c0: move s1,v0 */ set(17,cpu(2));
 /* 001759c4: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
 /* 001759c8: sh s0,0x0(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(16));
 /* 001759cc: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
 /* 001759d0: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
 /* 001759d4: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
 /* 001759d8: lw v0,-0x21c0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffffde40)));
 /* 001759dc: jalr v0 */ {uint64_t target=cpu(2);set(31,sx(UINT32_C(0x001759e4)));/* delay 001759e0 */ set(4,cpu(18));set(2,nocturneBattleActionPartCreation((uint32_t)target,cpu(4)));}
 /* 001759e4: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
 /* 001759e8: move v0,s1 */ set(2,cpu(17));
 /* 001759ec: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001759f0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001759f4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001759f8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001759fc: jr ra */ {uint64_t target=cpu(31);/* delay 00175a00 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

void ps2BattleActionPartScale_00175B38(uint64_t a0, float f12){
set(4,a0);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectAxisNoteEntry(0x00175b38);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00175b38: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 00175b3c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00175b40: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
 /* 00175b44: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
 /* 00175b48: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
 /* 00175b4c: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
 /* 00175b50: lui at,0x32 */ set(1,sx(UINT32_C(0x00320000)));
 /* 00175b54: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
 /* 00175b58: lw v0,-0x21ac(at) */ lw(2,ea(1,(int32_t)UINT32_C(0xffffde54)));
 /* 00175b5c: beql v0,zero,0x00175b70 */ {int take=(cpu(2)==cpu(0));if(take){/* delay 00175b60 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00175b70;}}
 /* 00175b64: jalr v0 */ {uint64_t target=cpu(2);set(31,sx(UINT32_C(0x00175b6c)));/* delay 00175b68 */ lw(4,ea(4,(int32_t)UINT32_C(0x00000004)));nocturneBattleActionEffectScale((uint32_t)target,cpu(4),f[12]);}
 /* 00175b6c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00175b70:;
 /* 00175b70: jr ra */ {uint64_t target=cpu(31);/* delay 00175b74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incomingRa);return;}
}

uint64_t ps2BattleActionPcpCreate_00175F08(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00175f08);
 uint64_t incomingRa=cpu(31);
 /* 00175f08: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 00175f0c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00175f10: move s0,a0 */ set(16,cpu(4));
 /* 00175f14: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00175f18: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00175f1c: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x00175f24)));/* delay 00175f20 */ set(4,sx(UINT32_C(0x0000000c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 00175f24: move a0,s0 */ set(4,cpu(16));
 /* 00175f28: jal 0x00176260 */ set(31,sx(UINT32_C(0x00175f30)));/* delay 00175f2c */ set(17,cpu(2));set(2,ps2PcpDescriptorKind(cpu(4)));
 /* 00175f30: move a0,s0 */ set(4,cpu(16));
 /* 00175f34: jal 0x00176268 */ set(31,sx(UINT32_C(0x00175f3c)));/* delay 00175f38 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));set(2,ps2PcpDescriptorNumber(cpu(4)));
 /* 00175f3c: move a0,s0 */ set(4,cpu(16));
 /* 00175f40: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
 /* 00175f44: lui a1,0x32 */ set(5,sx(UINT32_C(0x00320000)));
 /* 00175f48: addiu a1,a1,-0x2070 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffdf90)));
 /* 00175f4c: sll t1,v0,0x2 */ set(9,sx((uint32_t)cpu(2)<<2));
 /* 00175f50: sll a3,v1,0x2 */ set(7,sx((uint32_t)cpu(3)<<2));
 /* 00175f54: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
 /* 00175f58: addu v1,a3,v1 */ set(3,sx((uint32_t)cpu(7)+(uint32_t)cpu(3)));
 /* 00175f5c: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
 /* 00175f60: addu t0,v1,a1 */ set(8,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
 /* 00175f64: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
 /* 00175f68: lw v0,0xc(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x0000000c)));
 /* 00175f6c: bne v0,zero,0x00175f90 */ {int take=(cpu(2)!=cpu(0));/* delay 00175f70 */ set(6,cpu(8));if(take){goto L_00175f90;}}
 /* 00175f74: lui v1,0x32 */ set(3,sx(UINT32_C(0x00320000)));
 /* 00175f78: addu v1,v1,a3 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
 /* 00175f7c: lw v1,-0x2230(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffddd0)));
 /* 00175f80: lw v0,0x0(t0) */ lw(2,ea(8,(int32_t)UINT32_C(0x00000000)));
 /* 00175f84: addu v1,t1,v1 */ set(3,sx((uint32_t)cpu(9)+(uint32_t)cpu(3)));
 /* 00175f88: b 0x00175f94 */ /* delay 00175f8c */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_00175f94;
L_00175f90:;
 /* 00175f90: lw v0,0x0(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000000)));
L_00175f94:;
 /* 00175f94: jalr v0 */ {uint64_t target=cpu(2);set(31,sx(UINT32_C(0x00175f9c)));/* delay 00175f98 */ set(2,nocturneBattleActionPcpConstructorCall((uint32_t)target,cpu(4)));}
 /* 00175f9c: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
 /* 00175fa0: move v0,s1 */ set(2,cpu(17));
 /* 00175fa4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00175fa8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00175fac: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00175fb0: jr ra */ {uint64_t target=cpu(31);/* delay 00175fb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

void ps2BattleActionPcpScale_00176120(uint64_t a0, float f12){
set(4,a0);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectAxisNoteEntry(0x00176120);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00176120: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 00176124: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00176128: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
 /* 0017612c: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
 /* 00176130: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
 /* 00176134: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
 /* 00176138: lui at,0x32 */ set(1,sx(UINT32_C(0x00320000)));
 /* 0017613c: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
 /* 00176140: lw v0,-0x205c(at) */ lw(2,ea(1,(int32_t)UINT32_C(0xffffdfa4)));
 /* 00176144: beql v0,zero,0x00176158 */ {int take=(cpu(2)==cpu(0));if(take){/* delay 00176148 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00176158;}}
 /* 0017614c: jalr v0 */ {uint64_t target=cpu(2);set(31,sx(UINT32_C(0x00176154)));/* delay 00176150 */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));nocturneBattleActionEffectScale((uint32_t)target,cpu(4),f[12]);}
 /* 00176154: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00176158:;
 /* 00176158: jr ra */ {uint64_t target=cpu(31);/* delay 0017615c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incomingRa);return;}
}
