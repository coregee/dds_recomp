#include "battle_panel_renderer_bundle.h"
#include "battle_panel_color_native.h"
#include "battle_panel_color_privileged.h"
/* Whole original libc heap/CVT/dtoa/bigint29 native variants.
 * Fixed statements and real guest frames; no host formatter, opcode loop,
 * allocator result provider, expected output or spill/stack repair.
 */
#include "battle_action_libc_frames.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include "battle_action_formula_frames.h"
#include "battle_action_request_frames.h"
#include "battle_action_skill_bridge_frames.h"
#include "effect_soft_double_frames.h"
#include "effect_soft_double_adaptive_frames.h"
#include "effect_billboard_dependency_frames.h"
#include "material_fiveword_pool.h"
#include "magatuhi_helpers.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#pragma warning(disable:4102)
#endif
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneEffectHostHi(void);
extern uint64_t nocturneLibcStreamKernel(uint64_t selector,uint32_t argc,const uint64_t *arguments);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattlePanelColorAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelColorSetStackPointer(q[0]);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void pkLq(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneEffectHostCpuWrite(r,q);}
static void sq(unsigned r,uint32_t a){uint32_t q[4];nocturneEffectHostCpuRead(r,q);memcpy(at(a&~15u),q,16);}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}
static void divideUnsigned(uint32_t n,uint32_t d){EE_ANCHOR_DIVU_STATE(d?n/d:UINT32_MAX,d?n%d:n);}
static void multiply(unsigned rd,uint32_t n,uint32_t m,int secondary){
 uint64_t product=(uint64_t)((int64_t)(int32_t)n*(int64_t)(int32_t)m);
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)product),sx((uint32_t)(product>>32)));
 else EE_MAGATUHI_MULT_STATE(product);
 if(rd)set(rd,sx((uint32_t)product));
}


static void body_002d3990(void){
nocturneEffectAxisNoteEntry(0x002d3990u);
uint64_t incoming=cpu(31);
/* 002d3990: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002d3994: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d3998: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d399c: addiu s7,v0,-0x41d0 */ set(23,sx((uint32_t)cpu(2)+UINT32_C(0xffffbe30)));
/* 002d39a0: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d39a4: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002d39a8: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d39ac: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d39b0: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d39b4: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002d39b8: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d39bc: dsrl32 a1,a1,0x0 */ set(5,cpu(5)>>32);
/* 002d39c0: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d39c4: li s5,-0x1 */ set(21,sx(UINT32_C(0xffffffff)));
/* 002d39c8: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d39cc: addiu s6,v0,-0x3db8 */ set(22,sx((uint32_t)cpu(2)+UINT32_C(0xffffc248)));
/* 002d39d0: lw s4,0x8(s7) */ lw(20,ea(23,(int32_t)UINT32_C(0x00000008)));
/* 002d39d4: li v0,-0x4 */ set(2,sx(UINT32_C(0xfffffffc)));
/* 002d39d8: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d39dc: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d39e0: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002d39e4: ld v1,-0x3dc0(a2) */ restore(3,ea(6,(int32_t)UINT32_C(0xffffc240)));
/* 002d39e8: lw a2,0x4(s4) */ lw(6,ea(20,(int32_t)UINT32_C(0x00000004)));
/* 002d39ec: daddu a1,a1,v1 */ set(5,cpu(5)+cpu(3));
/* 002d39f0: lw v1,0x0(s6) */ lw(3,ea(22,(int32_t)UINT32_C(0x00000000)));
/* 002d39f4: and s3,a2,v0 */ set(19,cpu(6)&cpu(2));
/* 002d39f8: daddiu a1,a1,0x10 */ set(5,cpu(5)+(uint64_t)INT64_C(16));
/* 002d39fc: dsll32 s2,a1,0x0 */ set(18,cpu(5)<<32);
/* 002d3a00: dsra32 s2,s2,0x0 */ set(18,(uint64_t)((int64_t)cpu(18)>>32));
/* 002d3a04: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002d3a08: beq v1,s5,0x002d3a2c */ {int taken=(cpu(3)==cpu(21));/* delay 002d3a0c */ set(16,sx((uint32_t)cpu(20)+(uint32_t)cpu(19)));if(taken){goto L_002d3a2c;}}
/* 002d3a10: dsll32 v0,s2,0x0 */ set(2,cpu(18)<<32);
/* 002d3a14: li v1,-0x1000 */ set(3,sx(UINT32_C(0xfffff000)));
/* 002d3a18: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002d3a1c: daddiu v0,v0,0xfff */ set(2,cpu(2)+(uint64_t)INT64_C(4095));
/* 002d3a20: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d3a24: dsll32 s2,v0,0x0 */ set(18,cpu(2)<<32);
/* 002d3a28: dsra32 s2,s2,0x0 */ set(18,(uint64_t)((int64_t)cpu(18)>>32));
L_002d3a2c:;
/* 002d3a2c: jal 0x002d5250 */ set(31,0x002d3a34u);/* delay 002d3a30 */ set(5,cpu(18));nocturneBattlePanelRendererCall(UINT32_C(0x002d5250),UINT32_C(0x002d3a2c));
/* 002d3a34: move s1,v0 */ set(17,cpu(2));
/* 002d3a38: beq s1,s5,0x002d3bb8 */ {int taken=(cpu(17)==cpu(21));/* delay 002d3a3c */ set(2,cpu(17)<cpu(16));if(taken){goto L_002d3bb8;}}
/* 002d3a40: beq v0,zero,0x002d3a54 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3a44 */ set(30,sx(UINT32_C(0x00530000)));if(taken){goto L_002d3a54;}}
/* 002d3a48: bnel s4,s7,0x002d3bbc */ {int taken=(cpu(20)!=cpu(23));if(taken){/* delay 002d3a4c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_002d3bbc;}}
/* 002d3a50: lui s8,0x53 */ set(30,sx(UINT32_C(0x00530000)));
L_002d3a54:;
/* 002d3a54: addiu a0,s8,-0x3da0 */ set(4,sx((uint32_t)cpu(30)+UINT32_C(0xffffc260)));
/* 002d3a58: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d3a5c: addu v1,v0,s2 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 002d3a60: bne s1,s0,0x002d3a80 */ {int taken=(cpu(17)!=cpu(16));/* delay 002d3a64 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_002d3a80;}}
/* 002d3a68: addu a0,s2,s3 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(19)));
/* 002d3a6c: lw v1,0x8(s7) */ lw(3,ea(23,(int32_t)UINT32_C(0x00000008)));
/* 002d3a70: ori v0,a0,0x1 */ set(2,cpu(4)|UINT32_C(0x00000001));
/* 002d3a74: b 0x002d3b84 */ /* delay 002d3a78 */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002d3b84;
L_002d3a80:;
/* 002d3a80: lw v0,0x0(s6) */ lw(2,ea(22,(int32_t)UINT32_C(0x00000000)));
/* 002d3a84: bne v0,s5,0x002d3a98 */ {int taken=(cpu(2)!=cpu(21));/* delay 002d3a88 */ set(2,sx((uint32_t)cpu(17)-(uint32_t)cpu(16)));if(taken){goto L_002d3a98;}}
/* 002d3a8c: b 0x002d3aa0 */ /* delay 002d3a90 */ sw(ea(22,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));goto L_002d3aa0;
L_002d3a98:;
/* 002d3a98: addu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002d3a9c: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002d3aa0:;
/* 002d3aa0: addiu v0,s1,0x8 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000008)));
/* 002d3aa4: andi a1,v0,0xf */ set(5,cpu(2)&UINT32_C(0x0000000f));
/* 002d3aa8: beq a1,zero,0x002d3ac0 */ {int taken=(cpu(5)==cpu(0));/* delay 002d3aac */ set(2,sx(UINT32_C(0x00000010)));if(taken){goto L_002d3ac0;}}
/* 002d3ab0: subu s0,v0,a1 */ set(16,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 002d3ab4: b 0x002d3ac4 */ /* delay 002d3ab8 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(16)));goto L_002d3ac4;
L_002d3ac0:;
/* 002d3ac0: move s0,zero */ set(16,cpu(0));
L_002d3ac4:;
/* 002d3ac4: addu v0,s1,s2 */ set(2,sx((uint32_t)cpu(17)+(uint32_t)cpu(18)));
/* 002d3ac8: li v1,0x1000 */ set(3,sx(UINT32_C(0x00001000)));
/* 002d3acc: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 002d3ad0: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d3ad4: dsubu v1,v1,v0 */ set(3,cpu(3)-cpu(2));
/* 002d3ad8: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d3adc: dsra32 v1,v1,0x0 */ set(3,(uint64_t)((int64_t)cpu(3)>>32));
/* 002d3ae0: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 002d3ae4: jal 0x002d5250 */ set(31,0x002d3aecu);/* delay 002d3ae8 */ set(5,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d5250),UINT32_C(0x002d3ae4));
/* 002d3aec: move a0,v0 */ set(4,cpu(2));
/* 002d3af0: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d3af4: beq a0,v0,0x002d3bb8 */ {int taken=(cpu(4)==cpu(2));/* delay 002d3af8 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(17)));if(taken){goto L_002d3bb8;}}
/* 002d3afc: addiu a1,s8,-0x3da0 */ set(5,sx((uint32_t)cpu(30)+UINT32_C(0xffffc260)));
/* 002d3b00: lw v0,0x0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d3b04: addu a0,a0,s0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(16)));
/* 002d3b08: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002d3b0c: ori a0,a0,0x1 */ set(4,cpu(4)|UINT32_C(0x00000001));
/* 002d3b10: addiu v1,a2,-0x41d0 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0xffffbe30)));
/* 002d3b14: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d3b18: sw v0,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d3b1c: sw s1,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));
/* 002d3b20: beq s4,v1,0x002d3b84 */ {int taken=(cpu(20)==cpu(3));/* delay 002d3b24 */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));if(taken){goto L_002d3b84;}}
/* 002d3b28: sltiu v0,s3,0x10 */ set(2,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d3b2c: beql v0,zero,0x002d3b48 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d3b30 */ lw(2,ea(20,(int32_t)UINT32_C(0x00000004)));goto L_002d3b48;}}
/* 002d3b34: move v1,s1 */ set(3,cpu(17));
/* 002d3b38: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d3b3c: b 0x002d3bb8 */ /* delay 002d3b40 */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002d3bb8;
L_002d3b48:;
/* 002d3b48: addiu a0,s3,-0xc */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xfffffff4)));
/* 002d3b4c: li v1,-0x10 */ set(3,sx(UINT32_C(0xfffffff0)));
/* 002d3b50: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 002d3b54: and s3,a0,v1 */ set(19,cpu(4)&cpu(3));
/* 002d3b58: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002d3b5c: addu v1,s4,s3 */ set(3,sx((uint32_t)cpu(20)+(uint32_t)cpu(19)));
/* 002d3b60: or v0,v0,s3 */ set(2,cpu(2)|cpu(19));
/* 002d3b64: sltiu a0,s3,0x10 */ set(4,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d3b68: sw v0,0x4(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d3b6c: sw a1,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 002d3b70: bne a0,zero,0x002d3b84 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d3b74 */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));if(taken){goto L_002d3b84;}}
/* 002d3b78: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d3b7c: jal 0x002d9998 */ set(31,0x002d3b84u);/* delay 002d3b80 */ set(5,sx((uint32_t)cpu(20)+UINT32_C(0x00000008)));nocturneBattlePanelRendererCall(UINT32_C(0x002d9998),UINT32_C(0x002d3b7c));
L_002d3b84:;
/* 002d3b84: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002d3b88: lw a1,-0x3da0(s8) */ lw(5,ea(30,(int32_t)UINT32_C(0xffffc260)));
/* 002d3b8c: addiu v1,v1,-0x3db0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffc250)));
/* 002d3b90: ld v0,0x0(v1) */ restore(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002d3b94: sltu v0,v0,a1 */ set(2,cpu(2)<cpu(5));
/* 002d3b98: bnel v0,zero,0x002d3ba0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d3b9c */ save(5,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_002d3ba0;}}
L_002d3ba0:;
/* 002d3ba0: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002d3ba4: addiu v1,v1,-0x3da8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffc258)));
/* 002d3ba8: ld v0,0x0(v1) */ restore(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002d3bac: sltu v0,v0,a1 */ set(2,cpu(2)<cpu(5));
/* 002d3bb0: bnel v0,zero,0x002d3bb8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d3bb4 */ save(5,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_002d3bb8;}}
L_002d3bb8:;
/* 002d3bb8: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
L_002d3bbc:;
/* 002d3bbc: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d3bc0: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d3bc4: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d3bc8: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d3bcc: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d3bd0: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d3bd4: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d3bd8: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d3bdc: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002d3be0: jr ra */ {uint64_t target=cpu(31);/* delay 002d3be4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_002d3be8(void){
nocturneEffectAxisNoteEntry(0x002d3be8u);
uint64_t incoming=cpu(31);
/* 002d3be8: addiu v1,a1,0x13 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000013)));
/* 002d3bec: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002d3bf0: sltiu v0,v1,0x1f */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000001f));
/* 002d3bf4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d3bf8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d3bfc: move s3,a0 */ set(19,cpu(4));
/* 002d3c00: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d3c04: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d3c08: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d3c0c: bne v0,zero,0x002d3c20 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3c10 */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_002d3c20;}}
/* 002d3c14: li v0,-0x10 */ set(2,sx(UINT32_C(0xfffffff0)));
/* 002d3c18: b 0x002d3c24 */ /* delay 002d3c1c */ set(17,cpu(3)&cpu(2));goto L_002d3c24;
L_002d3c20:;
/* 002d3c20: li s1,0x10 */ set(17,sx(UINT32_C(0x00000010)));
L_002d3c24:;
/* 002d3c24: jal 0x002d4618 */ set(31,0x002d3c2cu);/* delay 002d3c28 */ set(4,cpu(19));nocturneBattlePanelRendererCall(UINT32_C(0x002d4618),UINT32_C(0x002d3c24));
/* 002d3c2c: sltiu v0,s1,0x1f8 */ set(2,cpu(17)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x000001f8));
/* 002d3c30: beq v0,zero,0x002d3c90 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3c34 */ set(3,sx((uint32_t)cpu(17)>>9));if(taken){goto L_002d3c90;}}
/* 002d3c38: lui t7,0x53 */ set(15,sx(UINT32_C(0x00530000)));
/* 002d3c3c: addiu v0,t7,-0x41c8 */ set(2,sx((uint32_t)cpu(15)+UINT32_C(0xffffbe38)));
/* 002d3c40: addiu v0,v0,-0x8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffff8)));
/* 002d3c44: addu a0,s1,v0 */ set(4,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002d3c48: lw s0,0xc(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002d3c4c: beq s0,a0,0x002d3c88 */ {int taken=(cpu(16)==cpu(4));/* delay 002d3c50 */ set(10,sx((uint32_t)cpu(17)>>3));if(taken){goto L_002d3c88;}}
/* 002d3c54: lw v1,0x4(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002d3c58: li v0,-0x4 */ set(2,sx(UINT32_C(0xfffffffc)));
/* 002d3c5c: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002d3c60: move a0,s3 */ set(4,cpu(19));
/* 002d3c64: and a2,v1,v0 */ set(6,cpu(3)&cpu(2));
/* 002d3c68: lw t0,0x8(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002d3c6c: addu v1,s0,a2 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));
/* 002d3c70: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002d3c74: sw t3,0xc(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(11));
/* 002d3c78: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 002d3c7c: sw t0,0x8(t3) */ sw(ea(11,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
/* 002d3c80: b 0x002d42e4 */ /* delay 002d3c84 */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002d42e4;
L_002d3c88:;
/* 002d3c88: b 0x002d3d6c */ /* delay 002d3c8c */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000002)));goto L_002d3d6c;
L_002d3c90:;
/* 002d3c90: beq v1,zero,0x002d3cf8 */ {int taken=(cpu(3)==cpu(0));/* delay 002d3c94 */ set(10,sx((uint32_t)cpu(17)>>3));if(taken){goto L_002d3cf8;}}
/* 002d3c98: sltiu v0,v1,0x5 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 002d3c9c: beq v0,zero,0x002d3cb0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3ca0 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000015));if(taken){goto L_002d3cb0;}}
/* 002d3ca4: srl v0,s1,0x6 */ set(2,sx((uint32_t)cpu(17)>>6));
/* 002d3ca8: b 0x002d3cf8 */ /* delay 002d3cac */ set(10,sx((uint32_t)cpu(2)+UINT32_C(0x00000038)));goto L_002d3cf8;
L_002d3cb0:;
/* 002d3cb0: bne v0,zero,0x002d3cf8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3cb4 */ set(10,sx((uint32_t)cpu(3)+UINT32_C(0x0000005b)));if(taken){goto L_002d3cf8;}}
/* 002d3cb8: sltiu v0,v1,0x55 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000055));
/* 002d3cbc: beq v0,zero,0x002d3cd0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3cc0 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000155));if(taken){goto L_002d3cd0;}}
/* 002d3cc4: srl v0,s1,0xc */ set(2,sx((uint32_t)cpu(17)>>12));
/* 002d3cc8: b 0x002d3cf8 */ /* delay 002d3ccc */ set(10,sx((uint32_t)cpu(2)+UINT32_C(0x0000006e)));goto L_002d3cf8;
L_002d3cd0:;
/* 002d3cd0: beq v0,zero,0x002d3ce8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3cd4 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000555));if(taken){goto L_002d3ce8;}}
/* 002d3cd8: srl v0,s1,0xf */ set(2,sx((uint32_t)cpu(17)>>15));
/* 002d3cdc: b 0x002d3cf8 */ /* delay 002d3ce0 */ set(10,sx((uint32_t)cpu(2)+UINT32_C(0x00000077)));goto L_002d3cf8;
L_002d3ce8:;
/* 002d3ce8: beql v0,zero,0x002d3cf8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d3cec */ set(10,sx(UINT32_C(0x0000007e)));goto L_002d3cf8;}}
/* 002d3cf0: srl v0,s1,0x12 */ set(2,sx((uint32_t)cpu(17)>>18));
/* 002d3cf4: addiu t2,v0,0x7c */ set(10,sx((uint32_t)cpu(2)+UINT32_C(0x0000007c)));
L_002d3cf8:;
/* 002d3cf8: lui t7,0x53 */ set(15,sx(UINT32_C(0x00530000)));
/* 002d3cfc: sll v1,t2,0x3 */ set(3,sx((uint32_t)cpu(10)<<3));
/* 002d3d00: addiu v0,t7,-0x41c8 */ set(2,sx((uint32_t)cpu(15)+UINT32_C(0xffffbe38)));
/* 002d3d04: li a0,-0x4 */ set(4,sx(UINT32_C(0xfffffffc)));
/* 002d3d08: addiu v0,v0,-0x8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffff8)));
/* 002d3d0c: addu a1,v1,v0 */ set(5,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002d3d10: b 0x002d3d24 */ /* delay 002d3d14 */ lw(16,ea(5,(int32_t)UINT32_C(0x0000000c)));goto L_002d3d24;
L_002d3d18:;
/* 002d3d18: bgez t0,0x002d4210 */ {int taken=((int64_t)cpu(8)>=0);/* delay 002d3d1c */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));if(taken){goto L_002d4210;}}
/* 002d3d20: lw s0,0xc(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x0000000c)));
L_002d3d24:;
/* 002d3d24: beql s0,a1,0x002d3d6c */ {int taken=(cpu(16)==cpu(5));if(taken){/* delay 002d3d28 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000001)));goto L_002d3d6c;}}
/* 002d3d2c: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002d3d30: and a2,v0,a0 */ set(6,cpu(2)&cpu(4));
/* 002d3d34: subu v1,s1,a2 */ set(3,sx((uint32_t)cpu(17)-(uint32_t)cpu(6)));
/* 002d3d38: subu v0,a2,s1 */ set(2,sx((uint32_t)cpu(6)-(uint32_t)cpu(17)));
/* 002d3d3c: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d3d40: dsll32 a3,v0,0x0 */ set(7,cpu(2)<<32);
/* 002d3d44: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002d3d48: sltu v0,a2,s1 */ set(2,cpu(6)<cpu(17));
/* 002d3d4c: bne v0,zero,0x002d3d58 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3d50 */ set(8,cpu(0)-cpu(3));if(taken){goto L_002d3d58;}}
/* 002d3d54: dsrl32 t0,a3,0x0 */ set(8,cpu(7)>>32);
L_002d3d58:;
/* 002d3d58: slti v0,t0,0x10 */ set(2,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d3d5c: bne v0,zero,0x002d3d18 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3d60 */ if(taken){goto L_002d3d18;}}
/* 002d3d64: addiu t2,t2,-0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0xffffffff)));
/* 002d3d68: addiu t2,t2,0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000001)));
L_002d3d6c:;
/* 002d3d6c: addiu v0,t7,-0x41c8 */ set(2,sx((uint32_t)cpu(15)+UINT32_C(0xffffbe38)));
/* 002d3d70: lw s0,0x8(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 002d3d74: beq s0,v0,0x002d3f78 */ {int taken=(cpu(16)==cpu(2));/* delay 002d3d78 */ set(3,sx(UINT32_C(0xfffffffc)));if(taken){goto L_002d3f78;}}
/* 002d3d7c: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002d3d80: and a2,v0,v1 */ set(6,cpu(2)&cpu(3));
/* 002d3d84: sltu a0,a2,s1 */ set(4,cpu(6)<cpu(17));
/* 002d3d88: beq a0,zero,0x002d3da8 */ {int taken=(cpu(4)==cpu(0));/* delay 002d3d8c */ set(2,sx((uint32_t)cpu(6)-(uint32_t)cpu(17)));if(taken){goto L_002d3da8;}}
/* 002d3d90: subu v0,s1,a2 */ set(2,sx((uint32_t)cpu(17)-(uint32_t)cpu(6)));
/* 002d3d94: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d3d98: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002d3d9c: b 0x002d3db0 */ /* delay 002d3da0 */ set(8,cpu(0)-cpu(2));goto L_002d3db0;
L_002d3da8:;
/* 002d3da8: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d3dac: dsrl32 t0,v0,0x0 */ set(8,cpu(2)>>32);
L_002d3db0:;
/* 002d3db0: slti v0,t0,0x10 */ set(2,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d3db4: bnel v0,zero,0x002d3e08 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d3db8 */ set(4,sx((uint32_t)cpu(15)+UINT32_C(0xffffbe38)));goto L_002d3e08;}}
/* 002d3dbc: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002d3dc0: addu t1,s0,s1 */ set(9,sx((uint32_t)cpu(16)+(uint32_t)cpu(17)));
/* 002d3dc4: dsll32 a3,t0,0x0 */ set(7,cpu(8)<<32);
/* 002d3dc8: dsra32 a3,a3,0x0 */ set(7,(uint64_t)((int64_t)cpu(7)>>32));
/* 002d3dcc: or v1,t0,v1 */ set(3,cpu(8)|cpu(3));
/* 002d3dd0: addiu a1,t7,-0x41c8 */ set(5,sx((uint32_t)cpu(15)+UINT32_C(0xffffbe38)));
/* 002d3dd4: ori v0,s1,0x1 */ set(2,cpu(17)|UINT32_C(0x00000001));
/* 002d3dd8: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d3ddc: dsra32 v1,v1,0x0 */ set(3,(uint64_t)((int64_t)cpu(3)>>32));
/* 002d3de0: addu a2,t1,a3 */ set(6,sx((uint32_t)cpu(9)+(uint32_t)cpu(7)));
/* 002d3de4: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d3de8: move a0,s3 */ set(4,cpu(19));
/* 002d3dec: sw t1,0xc(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(9));
/* 002d3df0: sw t1,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(9));
/* 002d3df4: sw v1,0x4(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d3df8: sw a1,0x8(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 002d3dfc: sw a3,0x0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));
/* 002d3e00: b 0x002d42e4 */ /* delay 002d3e04 */ sw(ea(9,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(5));goto L_002d42e4;
L_002d3e08:;
/* 002d3e08: sw a0,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
/* 002d3e0c: bltz t0,0x002d3e30 */ {int taken=((int64_t)cpu(8)<0);/* delay 002d3e10 */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));if(taken){goto L_002d3e30;}}
/* 002d3e14: addu v1,s0,a2 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));
/* 002d3e18: move a0,s3 */ set(4,cpu(19));
/* 002d3e1c: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002d3e20: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 002d3e24: b 0x002d42e4 */ /* delay 002d3e28 */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002d42e4;
L_002d3e30:;
/* 002d3e30: sltiu v0,a2,0x200 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000200));
/* 002d3e34: beq v0,zero,0x002d3e80 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3e38 */ set(3,sx((uint32_t)cpu(6)>>9));if(taken){goto L_002d3e80;}}
/* 002d3e3c: srl a1,a2,0x3 */ set(5,sx((uint32_t)cpu(6)>>3));
/* 002d3e40: addiu a0,a0,-0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffff8)));
/* 002d3e44: sll v1,a1,0x3 */ set(3,sx((uint32_t)cpu(5)<<3));
/* 002d3e48: srl a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)>>2));
/* 002d3e4c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d3e50: addu t3,v1,a0 */ set(11,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002d3e54: dsllv v0,v0,a1 */ set(2,cpu(2)<<(cpu(5)&63u));
/* 002d3e58: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 002d3e5c: lw t0,0x8(t3) */ lw(8,ea(11,(int32_t)UINT32_C(0x00000008)));
/* 002d3e60: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d3e64: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d3e68: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002d3e6c: sw t3,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(11));
/* 002d3e70: sw t0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
/* 002d3e74: b 0x002d3f70 */ /* delay 002d3e78 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));goto L_002d3f70;
L_002d3e80:;
/* 002d3e80: beq v1,zero,0x002d3ee8 */ {int taken=(cpu(3)==cpu(0));/* delay 002d3e84 */ set(5,sx((uint32_t)cpu(6)>>3));if(taken){goto L_002d3ee8;}}
/* 002d3e88: sltiu v0,v1,0x5 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 002d3e8c: beq v0,zero,0x002d3ea0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3e90 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000015));if(taken){goto L_002d3ea0;}}
/* 002d3e94: srl v0,a2,0x6 */ set(2,sx((uint32_t)cpu(6)>>6));
/* 002d3e98: b 0x002d3ee8 */ /* delay 002d3e9c */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000038)));goto L_002d3ee8;
L_002d3ea0:;
/* 002d3ea0: bne v0,zero,0x002d3ee8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3ea4 */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0x0000005b)));if(taken){goto L_002d3ee8;}}
/* 002d3ea8: sltiu v0,v1,0x55 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000055));
/* 002d3eac: beq v0,zero,0x002d3ec0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3eb0 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000155));if(taken){goto L_002d3ec0;}}
/* 002d3eb4: srl v0,a2,0xc */ set(2,sx((uint32_t)cpu(6)>>12));
/* 002d3eb8: b 0x002d3ee8 */ /* delay 002d3ebc */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x0000006e)));goto L_002d3ee8;
L_002d3ec0:;
/* 002d3ec0: beq v0,zero,0x002d3ed8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3ec4 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000555));if(taken){goto L_002d3ed8;}}
/* 002d3ec8: srl v0,a2,0xf */ set(2,sx((uint32_t)cpu(6)>>15));
/* 002d3ecc: b 0x002d3ee8 */ /* delay 002d3ed0 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000077)));goto L_002d3ee8;
L_002d3ed8:;
/* 002d3ed8: beql v0,zero,0x002d3ee8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d3edc */ set(5,sx(UINT32_C(0x0000007e)));goto L_002d3ee8;}}
/* 002d3ee0: srl v0,a2,0x12 */ set(2,sx((uint32_t)cpu(6)>>18));
/* 002d3ee4: addiu a1,v0,0x7c */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x0000007c)));
L_002d3ee8:;
/* 002d3ee8: addiu v0,t7,-0x41c8 */ set(2,sx((uint32_t)cpu(15)+UINT32_C(0xffffbe38)));
/* 002d3eec: sll v1,a1,0x3 */ set(3,sx((uint32_t)cpu(5)<<3));
/* 002d3ef0: addiu a3,v0,-0x8 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0xfffffff8)));
/* 002d3ef4: addu t3,v1,a3 */ set(11,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 002d3ef8: lw t0,0x8(t3) */ lw(8,ea(11,(int32_t)UINT32_C(0x00000008)));
/* 002d3efc: bnel t0,t3,0x002d3f38 */ {int taken=(cpu(8)!=cpu(11));if(taken){/* delay 002d3f00 */ lw(2,ea(8,(int32_t)UINT32_C(0x00000004)));goto L_002d3f38;}}
/* 002d3f04: addiu a0,a1,0x3 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000003)));
/* 002d3f08: slti v1,a1,0x0 */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 002d3f0c: movn a1,a0,v1 */ if(cpu(3)!=0){set(5,cpu(4));}
/* 002d3f10: lw v1,0x4(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 002d3f14: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d3f18: sra a0,a1,0x2 */ set(4,sx((uint32_t)((int32_t)cpu(5)>>2)));
/* 002d3f1c: dsllv v0,v0,a0 */ set(2,cpu(2)<<(cpu(4)&63u));
/* 002d3f20: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d3f24: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d3f28: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002d3f2c: b 0x002d3f68 */ /* delay 002d3f30 */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));goto L_002d3f68;
L_002d3f38:;
/* 002d3f38: b 0x002d3f4c */ /* delay 002d3f3c */ set(3,sx(UINT32_C(0xfffffffc)));goto L_002d3f4c;
L_002d3f40:;
/* 002d3f40: beql t0,t3,0x002d3f68 */ {int taken=(cpu(8)==cpu(11));if(taken){/* delay 002d3f44 */ lw(11,ea(8,(int32_t)UINT32_C(0x0000000c)));goto L_002d3f68;}}
/* 002d3f48: lw v0,0x4(t0) */ lw(2,ea(8,(int32_t)UINT32_C(0x00000004)));
L_002d3f4c:;
/* 002d3f4c: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d3f50: sltu v0,a2,v0 */ set(2,cpu(6)<cpu(2));
/* 002d3f54: nop  */ 
/* 002d3f58: nop  */ 
/* 002d3f5c: bnel v0,zero,0x002d3f40 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d3f60 */ lw(8,ea(8,(int32_t)UINT32_C(0x00000008)));goto L_002d3f40;}}
/* 002d3f64: lw t3,0xc(t0) */ lw(11,ea(8,(int32_t)UINT32_C(0x0000000c)));
L_002d3f68:;
/* 002d3f68: sw t3,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(11));
/* 002d3f6c: sw t0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
L_002d3f70:;
/* 002d3f70: sw s0,0x8(t3) */ sw(ea(11,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));
/* 002d3f74: sw s0,0xc(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(16));
L_002d3f78:;
/* 002d3f78: slti v0,t2,0x0 */ set(2,(int64_t)cpu(10)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 002d3f7c: addiu a1,t2,0x3 */ set(5,sx((uint32_t)cpu(10)+UINT32_C(0x00000003)));
/* 002d3f80: move a0,t2 */ set(4,cpu(10));
/* 002d3f84: lui s4,0x53 */ set(20,sx(UINT32_C(0x00530000)));
/* 002d3f88: movn a0,a1,v0 */ if(cpu(2)!=0){set(4,cpu(5));}
/* 002d3f8c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d3f90: addiu v1,s4,-0x41d0 */ set(3,sx((uint32_t)cpu(20)+UINT32_C(0xffffbe30)));
/* 002d3f94: sra a0,a0,0x2 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>2)));
/* 002d3f98: lwu a2,0x4(v1) */ set(6,word(ea(3,(int32_t)UINT32_C(0x00000004))));
/* 002d3f9c: dsllv t1,v0,a0 */ set(9,cpu(2)<<(cpu(4)&63u));
/* 002d3fa0: sltu v1,a2,t1 */ set(3,cpu(6)<cpu(9));
/* 002d3fa4: bnel v1,zero,0x002d412c */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d3fa8 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0xffffbe30)));goto L_002d412c;}}
/* 002d3fac: and v0,t1,a2 */ set(2,cpu(9)&cpu(6));
/* 002d3fb0: bne v0,zero,0x002d3ff8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3fb4 */ set(2,sx(UINT32_C(0x00530000)));if(taken){goto L_002d3ff8;}}
/* 002d3fb8: li v0,-0x4 */ set(2,sx(UINT32_C(0xfffffffc)));
/* 002d3fbc: dsll t1,t1,0x1 */ set(9,cpu(9)<<1);
/* 002d3fc0: and v0,t2,v0 */ set(2,cpu(10)&cpu(2));
/* 002d3fc4: and v1,t1,a2 */ set(3,cpu(9)&cpu(6));
/* 002d3fc8: bne v1,zero,0x002d3ff4 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d3fcc */ set(10,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));if(taken){goto L_002d3ff4;}}
/* 002d3fd0: move v1,a2 */ set(3,cpu(6));
/* 002d3fd4: nop  */ 
L_002d3fd8:;
/* 002d3fd8: dsll t1,t1,0x1 */ set(9,cpu(9)<<1);
/* 002d3fdc: and v0,t1,v1 */ set(2,cpu(9)&cpu(3));
/* 002d3fe0: nop  */ 
/* 002d3fe4: nop  */ 
/* 002d3fe8: nop  */ 
/* 002d3fec: beq v0,zero,0x002d3fd8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d3ff0 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000004)));if(taken){goto L_002d3fd8;}}
L_002d3ff4:;
/* 002d3ff4: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
L_002d3ff8:;
/* 002d3ff8: addiu t5,v0,-0x41d0 */ set(13,sx((uint32_t)cpu(2)+UINT32_C(0xffffbe30)));
/* 002d3ffc: move t6,v0 */ set(14,cpu(2));
/* 002d4000: move s2,t5 */ set(18,cpu(13));
/* 002d4004: sll v0,t2,0x3 */ set(2,sx((uint32_t)cpu(10)<<3));
L_002d4008:;
/* 002d4008: move t3,t2 */ set(11,cpu(10));
/* 002d400c: addu a0,v0,t5 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(13)));
/* 002d4010: move a1,a0 */ set(5,cpu(4));
/* 002d4014: lw s0,0xc(a1) */ lw(16,ea(5,(int32_t)UINT32_C(0x0000000c)));
L_002d4018:;
/* 002d4018: beq s0,a1,0x002d4074 */ {int taken=(cpu(16)==cpu(5));/* delay 002d401c */ set(2,(int64_t)cpu(10)<(int64_t)(int32_t)UINT32_C(0x0000003f));if(taken){goto L_002d4074;}}
/* 002d4020: li t4,-0x4 */ set(12,sx(UINT32_C(0xfffffffc)));
/* 002d4024: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
L_002d4028:;
/* 002d4028: and a2,v0,t4 */ set(6,cpu(2)&cpu(12));
/* 002d402c: subu v1,s1,a2 */ set(3,sx((uint32_t)cpu(17)-(uint32_t)cpu(6)));
/* 002d4030: subu v0,a2,s1 */ set(2,sx((uint32_t)cpu(6)-(uint32_t)cpu(17)));
/* 002d4034: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d4038: dsll32 a3,v0,0x0 */ set(7,cpu(2)<<32);
/* 002d403c: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002d4040: sltu v0,a2,s1 */ set(2,cpu(6)<cpu(17));
/* 002d4044: bne v0,zero,0x002d4050 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4048 */ set(8,cpu(0)-cpu(3));if(taken){goto L_002d4050;}}
/* 002d404c: dsrl32 t0,a3,0x0 */ set(8,cpu(7)>>32);
L_002d4050:;
/* 002d4050: slti v0,t0,0x10 */ set(2,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d4054: beql v0,zero,0x002d4238 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d4058 */ set(3,sx(UINT32_C(0x00000001)));goto L_002d4238;}}
/* 002d405c: bgezl t0,0x002d4290 */ {int taken=((int64_t)cpu(8)>=0);if(taken){/* delay 002d4060 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));goto L_002d4290;}}
/* 002d4064: lw s0,0xc(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002d4068: bnel s0,a1,0x002d4028 */ {int taken=(cpu(16)!=cpu(5));if(taken){/* delay 002d406c */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002d4028;}}
/* 002d4070: slti v0,t2,0x3f */ set(2,(int64_t)cpu(10)<(int64_t)(int32_t)UINT32_C(0x0000003f));
L_002d4074:;
/* 002d4074: beq v0,zero,0x002d4084 */ {int taken=(cpu(2)==cpu(0));/* delay 002d4078 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));if(taken){goto L_002d4084;}}
/* 002d407c: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 002d4080: addiu t2,t2,0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000001)));
L_002d4084:;
/* 002d4084: addiu t2,t2,0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000001)));
/* 002d4088: andi v0,t2,0x3 */ set(2,cpu(10)&UINT32_C(0x00000003));
/* 002d408c: bnel v0,zero,0x002d4018 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d4090 */ lw(16,ea(5,(int32_t)UINT32_C(0x0000000c)));goto L_002d4018;}}
/* 002d4094: dsll32 v0,t1,0x0 */ set(2,cpu(9)<<32);
/* 002d4098: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d409c: addiu a1,t6,-0x41d0 */ set(5,sx((uint32_t)cpu(14)+UINT32_C(0xffffbe30)));
/* 002d40a0: nor v1,zero,v0 */ set(3,~(cpu(0)|cpu(2)));
/* 002d40a4: andi v0,t3,0x3 */ set(2,cpu(11)&UINT32_C(0x00000003));
L_002d40a8:;
/* 002d40a8: bne v0,zero,0x002d40c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d40ac */ set(11,sx((uint32_t)cpu(11)+UINT32_C(0xffffffff)));if(taken){goto L_002d40c0;}}
/* 002d40b0: lw v0,0x4(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d40b4: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d40b8: b 0x002d40d4 */ /* delay 002d40bc */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002d40d4;
L_002d40c0:;
/* 002d40c0: addiu a0,a0,-0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffff8)));
/* 002d40c4: lw v0,0x8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002d40c8: nop  */ 
/* 002d40cc: beq v0,a0,0x002d40a8 */ {int taken=(cpu(2)==cpu(4));/* delay 002d40d0 */ set(2,cpu(11)&UINT32_C(0x00000003));if(taken){goto L_002d40a8;}}
L_002d40d4:;
/* 002d40d4: lwu v1,0x4(t5) */ set(3,word(ea(13,(int32_t)UINT32_C(0x00000004))));
/* 002d40d8: dsll t1,t1,0x1 */ set(9,cpu(9)<<1);
/* 002d40dc: sltu v0,v1,t1 */ set(2,cpu(3)<cpu(9));
/* 002d40e0: bnel v0,zero,0x002d412c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d40e4 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0xffffbe30)));goto L_002d412c;}}
/* 002d40e8: beq t1,zero,0x002d4128 */ {int taken=(cpu(9)==cpu(0));/* delay 002d40ec */ set(2,cpu(9)&cpu(3));if(taken){goto L_002d4128;}}
/* 002d40f0: bne v0,zero,0x002d4008 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d40f4 */ set(2,sx((uint32_t)cpu(10)<<3));if(taken){goto L_002d4008;}}
/* 002d40f8: lwu v1,0x4(s2) */ set(3,word(ea(18,(int32_t)UINT32_C(0x00000004))));
/* 002d40fc: nop  */ 
L_002d4100:;
/* 002d4100: dsll t1,t1,0x1 */ set(9,cpu(9)<<1);
/* 002d4104: and v0,t1,v1 */ set(2,cpu(9)&cpu(3));
/* 002d4108: nop  */ 
/* 002d410c: nop  */ 
/* 002d4110: nop  */ 
/* 002d4114: beq v0,zero,0x002d4100 */ {int taken=(cpu(2)==cpu(0));/* delay 002d4118 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000004)));if(taken){goto L_002d4100;}}
/* 002d411c: b 0x002d4008 */ /* delay 002d4120 */ set(2,sx((uint32_t)cpu(10)<<3));goto L_002d4008;
L_002d4128:;
/* 002d4128: addiu a0,s4,-0x41d0 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0xffffbe30)));
L_002d412c:;
/* 002d412c: li a1,-0x4 */ set(5,sx(UINT32_C(0xfffffffc)));
/* 002d4130: lw v0,0x8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002d4134: lw v1,0x4(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 002d4138: and v1,v1,a1 */ set(3,cpu(3)&cpu(5));
/* 002d413c: sltu v0,v1,s1 */ set(2,cpu(3)<cpu(17));
/* 002d4140: beq v0,zero,0x002d4160 */ {int taken=(cpu(2)==cpu(0));/* delay 002d4144 */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));if(taken){goto L_002d4160;}}
/* 002d4148: subu v0,s1,v1 */ set(2,sx((uint32_t)cpu(17)-(uint32_t)cpu(3)));
/* 002d414c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d4150: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002d4154: b 0x002d4168 */ /* delay 002d4158 */ set(8,cpu(0)-cpu(2));goto L_002d4168;
L_002d4160:;
/* 002d4160: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d4164: dsrl32 t0,v0,0x0 */ set(8,cpu(2)>>32);
L_002d4168:;
/* 002d4168: addiu s0,s4,-0x41d0 */ set(16,sx((uint32_t)cpu(20)+UINT32_C(0xffffbe30)));
/* 002d416c: li s2,-0x4 */ set(18,sx(UINT32_C(0xfffffffc)));
/* 002d4170: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002d4174: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002d4178: and v0,v0,s2 */ set(2,cpu(2)&cpu(18));
/* 002d417c: sltu v0,v0,s1 */ set(2,cpu(2)<cpu(17));
/* 002d4180: bne v0,zero,0x002d4198 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4184 */ set(4,cpu(19));if(taken){goto L_002d4198;}}
/* 002d4188: slti v0,t0,0x10 */ set(2,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d418c: beq v0,zero,0x002d42b8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d4190 */ set(6,sx((uint32_t)cpu(20)+UINT32_C(0xffffbe30)));if(taken){goto L_002d42b8;}}
/* 002d4194: move a0,s3 */ set(4,cpu(19));
L_002d4198:;
/* 002d4198: jal 0x002d3990 */ set(31,0x002d41a0u);/* delay 002d419c */ set(5,cpu(17));nocturneBattlePanelRendererCall(UINT32_C(0x002d3990),UINT32_C(0x002d4198));
/* 002d41a0: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002d41a4: lw v1,0x4(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 002d41a8: and v1,v1,s2 */ set(3,cpu(3)&cpu(18));
/* 002d41ac: sltu v0,v1,s1 */ set(2,cpu(3)<cpu(17));
/* 002d41b0: beq v0,zero,0x002d41d0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d41b4 */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));if(taken){goto L_002d41d0;}}
/* 002d41b8: subu v0,s1,v1 */ set(2,sx((uint32_t)cpu(17)-(uint32_t)cpu(3)));
/* 002d41bc: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d41c0: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002d41c4: b 0x002d41d8 */ /* delay 002d41c8 */ set(8,cpu(0)-cpu(2));goto L_002d41d8;
L_002d41d0:;
/* 002d41d0: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d41d4: dsrl32 t0,v0,0x0 */ set(8,cpu(2)>>32);
L_002d41d8:;
/* 002d41d8: addiu a0,s4,-0x41d0 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0xffffbe30)));
/* 002d41dc: li a1,-0x4 */ set(5,sx(UINT32_C(0xfffffffc)));
/* 002d41e0: lw v1,0x8(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002d41e4: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002d41e8: and v0,v0,a1 */ set(2,cpu(2)&cpu(5));
/* 002d41ec: sltu v0,v0,s1 */ set(2,cpu(2)<cpu(17));
/* 002d41f0: bne v0,zero,0x002d4200 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d41f4 */ set(2,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000010));if(taken){goto L_002d4200;}}
/* 002d41f8: beq v0,zero,0x002d42b8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d41fc */ set(6,sx((uint32_t)cpu(20)+UINT32_C(0xffffbe30)));if(taken){goto L_002d42b8;}}
L_002d4200:;
/* 002d4200: jal 0x002d4698 */ set(31,0x002d4208u);/* delay 002d4204 */ set(4,cpu(19));nocturneBattlePanelRendererCall(UINT32_C(0x002d4698),UINT32_C(0x002d4200));
/* 002d4208: b 0x002d42f0 */ /* delay 002d420c */ set(2,cpu(0));goto L_002d42f0;
L_002d4210:;
/* 002d4210: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002d4214: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002d4218: move a0,s3 */ set(4,cpu(19));
/* 002d421c: lw t0,0x8(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002d4220: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 002d4224: sw v0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d4228: sw t3,0xc(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(11));
/* 002d422c: b 0x002d42e4 */ /* delay 002d4230 */ sw(ea(11,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));goto L_002d42e4;
L_002d4238:;
/* 002d4238: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002d423c: addu t1,s0,s1 */ set(9,sx((uint32_t)cpu(16)+(uint32_t)cpu(17)));
/* 002d4240: dsll32 a3,t0,0x0 */ set(7,cpu(8)<<32);
/* 002d4244: dsra32 a3,a3,0x0 */ set(7,(uint64_t)((int64_t)cpu(7)>>32));
/* 002d4248: or v1,t0,v1 */ set(3,cpu(8)|cpu(3));
/* 002d424c: lw t0,0x8(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002d4250: addiu a1,t7,-0x41c8 */ set(5,sx((uint32_t)cpu(15)+UINT32_C(0xffffbe38)));
/* 002d4254: ori v0,s1,0x1 */ set(2,cpu(17)|UINT32_C(0x00000001));
/* 002d4258: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d425c: dsra32 v1,v1,0x0 */ set(3,(uint64_t)((int64_t)cpu(3)>>32));
/* 002d4260: addu a2,t1,a3 */ set(6,sx((uint32_t)cpu(9)+(uint32_t)cpu(7)));
/* 002d4264: sw t3,0xc(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(11));
/* 002d4268: move a0,s3 */ set(4,cpu(19));
/* 002d426c: sw t0,0x8(t3) */ sw(ea(11,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
/* 002d4270: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d4274: sw t1,0xc(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(9));
/* 002d4278: sw t1,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(9));
/* 002d427c: sw v1,0x4(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d4280: sw a1,0x8(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 002d4284: sw a3,0x0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));
/* 002d4288: b 0x002d42e4 */ /* delay 002d428c */ sw(ea(9,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(5));goto L_002d42e4;
L_002d4290:;
/* 002d4290: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002d4294: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002d4298: move a0,s3 */ set(4,cpu(19));
/* 002d429c: lw t0,0x8(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002d42a0: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 002d42a4: sw v0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d42a8: sw t3,0xc(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(11));
/* 002d42ac: b 0x002d42e4 */ /* delay 002d42b0 */ sw(ea(11,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));goto L_002d42e4;
L_002d42b8:;
/* 002d42b8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d42bc: lw s0,0x8(a2) */ lw(16,ea(6,(int32_t)UINT32_C(0x00000008)));
/* 002d42c0: or v0,t0,v0 */ set(2,cpu(8)|cpu(2));
/* 002d42c4: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d42c8: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d42cc: ori v1,s1,0x1 */ set(3,cpu(17)|UINT32_C(0x00000001));
/* 002d42d0: addu a1,s0,s1 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(17)));
/* 002d42d4: sw v1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d42d8: sw a1,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 002d42dc: move a0,s3 */ set(4,cpu(19));
/* 002d42e0: sw v0,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002d42e4:;
/* 002d42e4: jal 0x002d4698 */ set(31,0x002d42ecu);/* delay 002d42e8 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d4698),UINT32_C(0x002d42e4));
/* 002d42ec: addiu v0,s0,0x8 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));
L_002d42f0:;
/* 002d42f0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d42f4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d42f8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d42fc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d4300: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d4304: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d4308: jr ra */ {uint64_t target=cpu(31);/* delay 002d430c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002d43a4(void){
nocturneEffectAxisNoteEntry(0x002d43a4u);
uint64_t incoming=cpu(31);
/* 002d43a4: move t0,a0 */ set(8,cpu(4));
/* 002d43a8: sltiu v0,a2,0x20 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d43ac: bne v0,zero,0x002d4420 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d43b0 */ set(3,cpu(8));if(taken){goto L_002d4420;}}
/* 002d43b4: or v0,a1,t0 */ set(2,cpu(5)|cpu(8));
/* 002d43b8: andi v0,v0,0xf */ set(2,cpu(2)&UINT32_C(0x0000000f));
/* 002d43bc: bnel v0,zero,0x002d4424 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d43c0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));goto L_002d4424;}}
/* 002d43c4: move a3,t0 */ set(7,cpu(8));
L_002d43c8:;
/* 002d43c8: lq v1,0x0(a1) */ pkLq(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d43cc: addiu a2,a2,-0x20 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffe0)));
/* 002d43d0: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d43d4: sltiu a0,a2,0x20 */ set(4,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d43d8: sq v1,0x0(a3) */ sq(3,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d43dc: addiu a3,a3,0x10 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));
/* 002d43e0: lq v0,0x0(a1) */ pkLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d43e4: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d43e8: sq v0,0x0(a3) */ sq(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d43ec: beq a0,zero,0x002d43c8 */ {int taken=(cpu(4)==cpu(0));/* delay 002d43f0 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));if(taken){goto L_002d43c8;}}
/* 002d43f4: sltiu v0,a2,0x8 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d43f8: bne v0,zero,0x002d4420 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d43fc */ set(3,cpu(7));if(taken){goto L_002d4420;}}
L_002d4400:;
/* 002d4400: ld v1,0x0(a1) */ restore(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d4404: addiu a2,a2,-0x8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xfffffff8)));
/* 002d4408: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 002d440c: sltiu v0,a2,0x8 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d4410: sd v1,0x0(a3) */ save(3,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d4414: beq v0,zero,0x002d4400 */ {int taken=(cpu(2)==cpu(0));/* delay 002d4418 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000008)));if(taken){goto L_002d4400;}}
/* 002d441c: move v1,a3 */ set(3,cpu(7));
L_002d4420:;
/* 002d4420: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
L_002d4424:;
/* 002d4424: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d4428: beq a2,v0,0x002d444c */ {int taken=(cpu(6)==cpu(2));/* delay 002d442c */ set(4,cpu(2));if(taken){goto L_002d444c;}}
L_002d4430:;
/* 002d4430: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d4434: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d4438: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002d443c: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d4440: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d4444: bne a2,a0,0x002d4430 */ {int taken=(cpu(6)!=cpu(4));/* delay 002d4448 */ if(taken){goto L_002d4430;}}
L_002d444c:;
/* 002d444c: jr ra */ {uint64_t target=cpu(31);/* delay 002d4450 */ set(2,cpu(8));checkReturn(target,incoming);return;}
}
static void body_002d4618(void){
nocturneEffectAxisNoteEntry(0x002d4618u);
uint64_t incoming=cpu(31);
/* 002d4618: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002d461c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d4620: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d4624: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d4628: jal 0x002dbd90 */ set(31,0x002d4630u);/* delay 002d462c */ nocturneBattlePanelRendererCall(UINT32_C(0x002dbd90),UINT32_C(0x002d4628));
/* 002d4630: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002d4634: move s0,v0 */ set(16,cpu(2));
/* 002d4638: addiu s1,v1,-0x3d78 */ set(17,sx((uint32_t)cpu(3)+UINT32_C(0xffffc288)));
/* 002d463c: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d4640: addiu a0,v0,-0x3d74 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0xffffc28c)));
/* 002d4644: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002d4648: bne v0,s0,0x002d4660 */ {int taken=(cpu(2)!=cpu(16));/* delay 002d464c */ set(2,sx(UINT32_C(0x00530000)));if(taken){goto L_002d4660;}}
/* 002d4650: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d4654: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d4658: b 0x002d4680 */ /* delay 002d465c */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_002d4680;
L_002d4660:;
/* 002d4660: jal 0x002dbee0 */ set(31,0x002d4668u);/* delay 002d4664 */ lw(4,ea(2,(int32_t)UINT32_C(0xffffc378)));nocturneBattlePanelRendererCall(UINT32_C(0x002dbee0),UINT32_C(0x002d4660));
/* 002d4668: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002d466c: sw s0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002d4670: addiu v1,v1,-0x3d74 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffc28c)));
/* 002d4674: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002d4678: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d467c: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002d4680:;
/* 002d4680: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d4684: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d4688: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d468c: jr ra */ {uint64_t target=cpu(31);/* delay 002d4690 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002d4698(void){
nocturneEffectAxisNoteEntry(0x002d4698u);
uint64_t incoming=cpu(31);
/* 002d4698: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002d469c: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002d46a0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d46a4: addiu v1,v1,-0x3d74 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffc28c)));
/* 002d46a8: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002d46ac: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002d46b0: bne v0,zero,0x002d46d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d46b4 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_002d46d8;}}
/* 002d46b8: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d46bc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d46c0: lw a0,-0x3c88(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0xffffc378)));
/* 002d46c4: lui a1,0x53 */ set(5,sx(UINT32_C(0x00530000)));
/* 002d46c8: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002d46cc: sw v1,-0x3d78(a1) */ sw(ea(5,(int32_t)UINT32_C(0xffffc288)),(uint32_t)cpu(3));
/* 002d46d0: j 0x002dbec0 */ checkReturn(cpu(31),incoming);/* delay 002d46d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002dbec0),UINT32_C(0x002d46d0));return;
L_002d46d8:;
/* 002d46d8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d46dc: jr ra */ {uint64_t target=cpu(31);/* delay 002d46e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002d5250(void){
nocturneEffectAxisNoteEntry(0x002d5250u);
uint64_t incoming=cpu(31);
/* 002d5250: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002d5254: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d5258: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d525c: move s0,a0 */ set(16,cpu(4));
/* 002d5260: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d5264: addiu s1,v0,0x2178 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00002178)));
/* 002d5268: move a0,a1 */ set(4,cpu(5));
/* 002d526c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d5270: jal 0x002dc5a0 */ set(31,0x002d5278u);/* delay 002d5274 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002dc5a0),UINT32_C(0x002d5270));
/* 002d5278: move a0,v0 */ set(4,cpu(2));
/* 002d527c: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002d5280: bnel a0,v1,0x002d5298 */ {int taken=(cpu(4)!=cpu(3));if(taken){/* delay 002d5284 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002d5298;}}
/* 002d5288: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002d528c: bnel v1,zero,0x002d5294 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d5290 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));goto L_002d5294;}}
L_002d5294:;
/* 002d5294: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002d5298:;
/* 002d5298: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d529c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d52a0: jr ra */ {uint64_t target=cpu(31);/* delay 002d52a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002d7ce8(void){
nocturneEffectAxisNoteEntry(0x002d7ce8u);
uint64_t incoming=cpu(31);
/* 002d7ce8: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002d7cec: li v0,0x66 */ set(2,sx(UINT32_C(0x00000066)));
/* 002d7cf0: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7cf4: move s1,t2 */ set(17,cpu(10));
/* 002d7cf8: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d7cfc: move s0,t0 */ set(16,cpu(8));
/* 002d7d00: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d7d04: move s2,a1 */ set(18,cpu(5));
/* 002d7d08: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d7d0c: move s3,a2 */ set(19,cpu(6));
/* 002d7d10: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d7d14: li s4,0x3 */ set(20,sx(UINT32_C(0x00000003)));
/* 002d7d18: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d7d1c: move s5,t1 */ set(21,cpu(9));
/* 002d7d20: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d7d24: move s6,a0 */ set(22,cpu(4));
/* 002d7d28: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d7d2c: move s7,a3 */ set(23,cpu(7));
/* 002d7d30: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d7d34: move s8,t3 */ set(30,cpu(11));
/* 002d7d38: beq s1,v0,0x002d7d5c */ {int taken=(cpu(17)==cpu(2));/* delay 002d7d3c */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));if(taken){goto L_002d7d5c;}}
/* 002d7d40: li v0,0x65 */ set(2,sx(UINT32_C(0x00000065)));
/* 002d7d44: beq s1,v0,0x002d7d54 */ {int taken=(cpu(17)==cpu(2));/* delay 002d7d48 */ set(2,sx(UINT32_C(0x00000045)));if(taken){goto L_002d7d54;}}
/* 002d7d4c: bne s1,v0,0x002d7d5c */ {int taken=(cpu(17)!=cpu(2));/* delay 002d7d50 */ set(20,sx(UINT32_C(0x00000002)));if(taken){goto L_002d7d5c;}}
L_002d7d54:;
/* 002d7d54: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002d7d58: li s4,0x2 */ set(20,sx(UINT32_C(0x00000002)));
L_002d7d5c:;
/* 002d7d5c: move v0,s2 */ set(2,cpu(18));
/* 002d7d60: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d7d64: bgezl v0,0x002d7d88 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 002d7d68 */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));goto L_002d7d88;}}
/* 002d7d6c: move a1,s2 */ set(5,cpu(18));
/* 002d7d70: move a0,zero */ set(4,cpu(0));
/* 002d7d74: jal 0x002d1848 */ set(31,0x002d7d7cu);/* delay 002d7d78 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d7d74));
/* 002d7d7c: move s2,v0 */ set(18,cpu(2));
/* 002d7d80: li v0,0x2d */ set(2,sx(UINT32_C(0x0000002d)));
/* 002d7d84: sb v0,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
L_002d7d88:;
/* 002d7d88: move a2,s4 */ set(6,cpu(20));
/* 002d7d8c: move a0,s6 */ set(4,cpu(22));
/* 002d7d90: move a1,s2 */ set(5,cpu(18));
/* 002d7d94: move a3,s3 */ set(7,cpu(19));
/* 002d7d98: move t0,s5 */ set(8,cpu(21));
/* 002d7d9c: move t1,sp */ set(9,cpu(29));
/* 002d7da0: jal 0x002d8378 */ set(31,0x002d7da8u);/* delay 002d7da4 */ set(10,sx((uint32_t)cpu(29)+UINT32_C(0x00000004)));nocturneBattlePanelRendererCall(UINT32_C(0x002d8378),UINT32_C(0x002d7da0));
/* 002d7da8: move s4,v0 */ set(20,cpu(2));
/* 002d7dac: li v0,0x67 */ set(2,sx(UINT32_C(0x00000067)));
/* 002d7db0: beq s1,v0,0x002d7dc0 */ {int taken=(cpu(17)==cpu(2));/* delay 002d7db4 */ set(2,sx(UINT32_C(0x00000047)));if(taken){goto L_002d7dc0;}}
/* 002d7db8: bne s1,v0,0x002d7dcc */ {int taken=(cpu(17)!=cpu(2));/* delay 002d7dbc */ set(2,sx(UINT32_C(0x00000066)));if(taken){goto L_002d7dcc;}}
L_002d7dc0:;
/* 002d7dc0: andi v0,s7,0x1 */ set(2,cpu(23)&UINT32_C(0x00000001));
/* 002d7dc4: beq v0,zero,0x002d7e68 */ {int taken=(cpu(2)==cpu(0));/* delay 002d7dc8 */ set(2,sx(UINT32_C(0x00000066)));if(taken){goto L_002d7e68;}}
L_002d7dcc:;
/* 002d7dcc: bne s1,v0,0x002d7e0c */ {int taken=(cpu(17)!=cpu(2));/* delay 002d7dd0 */ set(16,sx((uint32_t)cpu(20)+(uint32_t)cpu(19)));if(taken){goto L_002d7e0c;}}
/* 002d7dd4: lb v1,0x0(s4) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(20,(int32_t)UINT32_C(0x00000000))));
/* 002d7dd8: li v0,0x30 */ set(2,sx(UINT32_C(0x00000030)));
/* 002d7ddc: bnel v1,v0,0x002d7e08 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 002d7de0 */ lw(2,ea(21,(int32_t)UINT32_C(0x00000000)));goto L_002d7e08;}}
/* 002d7de4: move a0,s2 */ set(4,cpu(18));
/* 002d7de8: move a1,zero */ set(5,cpu(0));
/* 002d7dec: jal 0x002d1b38 */ set(31,0x002d7df4u);/* delay 002d7df0 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d7dec));
/* 002d7df4: beq v0,zero,0x002d7e04 */ {int taken=(cpu(2)==cpu(0));/* delay 002d7df8 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002d7e04;}}
/* 002d7dfc: subu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(19)));
/* 002d7e00: sw v0,0x0(s5) */ sw(ea(21,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002d7e04:;
/* 002d7e04: lw v0,0x0(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000000)));
L_002d7e08:;
/* 002d7e08: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
L_002d7e0c:;
/* 002d7e0c: move a0,s2 */ set(4,cpu(18));
/* 002d7e10: move a1,zero */ set(5,cpu(0));
/* 002d7e14: jal 0x002d1b38 */ set(31,0x002d7e1cu);/* delay 002d7e18 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d7e14));
/* 002d7e1c: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002d7e20: xori v0,v0,0x0 */ set(2,cpu(2)^UINT32_C(0x00000000));
/* 002d7e24: movz v1,s0,v0 */ if(cpu(2)==0){set(3,cpu(16));}
/* 002d7e28: sltu v0,v1,s0 */ set(2,cpu(3)<cpu(16));
/* 002d7e2c: sw v1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d7e30: beq v0,zero,0x002d7e6c */ {int taken=(cpu(2)==cpu(0));/* delay 002d7e34 */ set(4,cpu(3));if(taken){goto L_002d7e6c;}}
/* 002d7e38: li a1,0x30 */ set(5,sx(UINT32_C(0x00000030)));
/* 002d7e3c: nop  */ 
L_002d7e40:;
/* 002d7e40: addiu v1,a0,0x1 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002d7e44: sb a1,0x0(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(5));
/* 002d7e48: sltu v0,v1,s0 */ set(2,cpu(3)<cpu(16));
/* 002d7e4c: sw v1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d7e50: nop  */ 
/* 002d7e54: bne v0,zero,0x002d7e40 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7e58 */ set(4,cpu(3));if(taken){goto L_002d7e40;}}
/* 002d7e5c: b 0x002d7e70 */ /* delay 002d7e60 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(20)));goto L_002d7e70;
L_002d7e68:;
/* 002d7e68: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
L_002d7e6c:;
/* 002d7e6c: subu v1,v1,s4 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(20)));
L_002d7e70:;
/* 002d7e70: move v0,s4 */ set(2,cpu(20));
/* 002d7e74: sw v1,0x0(s8) */ sw(ea(30,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002d7e78: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d7e7c: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7e80: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d7e84: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d7e88: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d7e8c: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d7e90: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d7e94: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d7e98: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d7e9c: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002d7ea0: jr ra */ {uint64_t target=cpu(31);/* delay 002d7ea4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_002d8148(void){
nocturneEffectAxisNoteEntry(0x002d8148u);
uint64_t incoming=cpu(31);
/* 002d8148: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002d814c: move t6,a1 */ set(14,cpu(5));
/* 002d8150: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8154: move s4,a0 */ set(20,cpu(4));
/* 002d8158: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d815c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d8160: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d8164: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d8168: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d816c: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d8170: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d8174: lw s0,0x10(t6) */ lw(16,ea(14,(int32_t)UINT32_C(0x00000010)));
/* 002d8178: lw v1,0x10(s4) */ lw(3,ea(20,(int32_t)UINT32_C(0x00000010)));
/* 002d817c: slt v1,v1,s0 */ set(3,(int64_t)cpu(3)<(int64_t)cpu(16));
/* 002d8180: bne v1,zero,0x002d834c */ {int taken=(cpu(3)!=cpu(0));/* delay 002d8184 */ set(2,cpu(0));if(taken){goto L_002d834c;}}
/* 002d8188: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 002d818c: addiu t3,t6,0x14 */ set(11,sx((uint32_t)cpu(14)+UINT32_C(0x00000014)));
/* 002d8190: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002d8194: addiu s1,s4,0x14 */ set(17,sx((uint32_t)cpu(20)+UINT32_C(0x00000014)));
/* 002d8198: addu s3,t3,v0 */ set(19,sx((uint32_t)cpu(11)+(uint32_t)cpu(2)));
/* 002d819c: addu t1,s1,v0 */ set(9,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002d81a0: lw v1,0x0(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 002d81a4: move s6,t3 */ set(22,cpu(11));
/* 002d81a8: lw t5,0x0(t1) */ lw(13,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 002d81ac: move t2,s1 */ set(10,cpu(17));
/* 002d81b0: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d81b4: divu t5,v1 */ divideUnsigned((uint32_t)cpu(13),(uint32_t)cpu(3));
/* 002d81b8: beql v1,zero,0x002d81c0 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002d81bc */ nocturneBattlePanelRendererTrap(7u,UINT32_C(0x002d81bc));goto L_002d81c0;}}
L_002d81c0:;
/* 002d81c0: mflo s5 */ set(21,nocturneEffectHostLo());
/* 002d81c4: move s2,s5 */ set(18,cpu(21));
/* 002d81c8: beq s2,zero,0x002d8278 */ {int taken=(cpu(18)==cpu(0));/* delay 002d81cc */ set(12,cpu(0));if(taken){goto L_002d8278;}}
/* 002d81d0: move v1,zero */ set(3,cpu(0));
/* 002d81d4: nop  */ 
L_002d81d8:;
/* 002d81d8: lw a0,0x0(t3) */ lw(4,ea(11,(int32_t)UINT32_C(0x00000000)));
/* 002d81dc: addiu t3,t3,0x4 */ set(11,sx((uint32_t)cpu(11)+UINT32_C(0x00000004)));
/* 002d81e0: lw a2,0x0(t2) */ lw(6,ea(10,(int32_t)UINT32_C(0x00000000)));
/* 002d81e4: sltu a3,s3,t3 */ set(7,cpu(19)<cpu(11));
/* 002d81e8: andi v0,a0,0xffff */ set(2,cpu(4)&UINT32_C(0x0000ffff));
/* 002d81ec: srl a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)>>16));
/* 002d81f0: mult a1,v0,s2 */ multiply(5,(uint32_t)cpu(2),(uint32_t)cpu(18),0);
/* 002d81f4: mult a0,a0,s2 */ multiply(4,(uint32_t)cpu(4),(uint32_t)cpu(18),0);
/* 002d81f8: addu v0,a1,v1 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 002d81fc: andi v1,a2,0xffff */ set(3,cpu(6)&UINT32_C(0x0000ffff));
/* 002d8200: andi a1,v0,0xffff */ set(5,cpu(2)&UINT32_C(0x0000ffff));
/* 002d8204: srl v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)>>16));
/* 002d8208: addu t0,a0,v0 */ set(8,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002d820c: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
/* 002d8210: addu v1,v1,t4 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(12)));
/* 002d8214: srl a2,a2,0x10 */ set(6,sx((uint32_t)cpu(6)>>16));
/* 002d8218: andi v0,t0,0xffff */ set(2,cpu(8)&UINT32_C(0x0000ffff));
/* 002d821c: sra t4,v1,0x10 */ set(12,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 002d8220: subu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(2)));
/* 002d8224: sh v1,0x0(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002d8228: addu a1,a2,t4 */ set(5,sx((uint32_t)cpu(6)+(uint32_t)cpu(12)));
/* 002d822c: srl v1,t0,0x10 */ set(3,sx((uint32_t)cpu(8)>>16));
/* 002d8230: sh a1,0x2(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(5));
/* 002d8234: addiu t2,t2,0x4 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000004)));
/* 002d8238: beq a3,zero,0x002d81d8 */ {int taken=(cpu(7)==cpu(0));/* delay 002d823c */ set(12,sx((uint32_t)((int32_t)cpu(5)>>16)));if(taken){goto L_002d81d8;}}
/* 002d8240: bnel t5,zero,0x002d827c */ {int taken=(cpu(13)!=cpu(0));if(taken){/* delay 002d8244 */ set(5,cpu(14));goto L_002d827c;}}
/* 002d8248: b 0x002d8254 */ /* delay 002d824c */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xfffffffc)));goto L_002d8254;
L_002d8250:;
/* 002d8250: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
L_002d8254:;
/* 002d8254: sltu v0,s1,t1 */ set(2,cpu(17)<cpu(9));
/* 002d8258: beql v0,zero,0x002d8278 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d825c */ sw(ea(20,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(16));goto L_002d8278;}}
/* 002d8260: lw v0,0x0(t1) */ lw(2,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 002d8264: nop  */ 
/* 002d8268: nop  */ 
/* 002d826c: beql v0,zero,0x002d8250 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d8270 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xfffffffc)));goto L_002d8250;}}
/* 002d8274: sw s0,0x10(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(16));
L_002d8278:;
/* 002d8278: move a1,t6 */ set(5,cpu(14));
L_002d827c:;
/* 002d827c: jal 0x002daec0 */ set(31,0x002d8284u);/* delay 002d8280 */ set(4,cpu(20));nocturneBattlePanelRendererCall(UINT32_C(0x002daec0),UINT32_C(0x002d827c));
/* 002d8284: bltz v0,0x002d8348 */ {int taken=((int64_t)cpu(2)<0);/* delay 002d8288 */ set(11,cpu(22));if(taken){goto L_002d8348;}}
/* 002d828c: addiu s2,s5,0x1 */ set(18,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));
/* 002d8290: move t4,zero */ set(12,cpu(0));
/* 002d8294: move v1,zero */ set(3,cpu(0));
/* 002d8298: move t2,s1 */ set(10,cpu(17));
/* 002d829c: nop  */ 
L_002d82a0:;
/* 002d82a0: lw a0,0x0(t3) */ lw(4,ea(11,(int32_t)UINT32_C(0x00000000)));
/* 002d82a4: addiu t3,t3,0x4 */ set(11,sx((uint32_t)cpu(11)+UINT32_C(0x00000004)));
/* 002d82a8: lw a1,0x0(t2) */ lw(5,ea(10,(int32_t)UINT32_C(0x00000000)));
/* 002d82ac: sltu a3,s3,t3 */ set(7,cpu(19)<cpu(11));
/* 002d82b0: andi v0,a0,0xffff */ set(2,cpu(4)&UINT32_C(0x0000ffff));
/* 002d82b4: srl a2,a0,0x10 */ set(6,sx((uint32_t)cpu(4)>>16));
/* 002d82b8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002d82bc: andi v1,a1,0xffff */ set(3,cpu(5)&UINT32_C(0x0000ffff));
/* 002d82c0: andi a0,v0,0xffff */ set(4,cpu(2)&UINT32_C(0x0000ffff));
/* 002d82c4: srl v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)>>16));
/* 002d82c8: addu t0,a2,v0 */ set(8,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 002d82cc: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 002d82d0: addu v1,v1,t4 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(12)));
/* 002d82d4: srl a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)>>16));
/* 002d82d8: andi v0,t0,0xffff */ set(2,cpu(8)&UINT32_C(0x0000ffff));
/* 002d82dc: sra t4,v1,0x10 */ set(12,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 002d82e0: subu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));
/* 002d82e4: sh v1,0x0(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002d82e8: addu a1,a1,t4 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(12)));
/* 002d82ec: srl v1,t0,0x10 */ set(3,sx((uint32_t)cpu(8)>>16));
/* 002d82f0: sh a1,0x2(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(5));
/* 002d82f4: addiu t2,t2,0x4 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000004)));
/* 002d82f8: beq a3,zero,0x002d82a0 */ {int taken=(cpu(7)==cpu(0));/* delay 002d82fc */ set(12,sx((uint32_t)((int32_t)cpu(5)>>16)));if(taken){goto L_002d82a0;}}
/* 002d8300: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002d8304: addu t1,s1,v0 */ set(9,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002d8308: lw v1,0x0(t1) */ lw(3,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 002d830c: bne v1,zero,0x002d834c */ {int taken=(cpu(3)!=cpu(0));/* delay 002d8310 */ set(2,cpu(18));if(taken){goto L_002d834c;}}
/* 002d8314: b 0x002d8324 */ /* delay 002d8318 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xfffffffc)));goto L_002d8324;
L_002d8320:;
/* 002d8320: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
L_002d8324:;
/* 002d8324: sltu v0,s1,t1 */ set(2,cpu(17)<cpu(9));
/* 002d8328: beql v0,zero,0x002d8348 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d832c */ sw(ea(20,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(16));goto L_002d8348;}}
/* 002d8330: lw v0,0x0(t1) */ lw(2,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 002d8334: nop  */ 
/* 002d8338: nop  */ 
/* 002d833c: beql v0,zero,0x002d8320 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d8340 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xfffffffc)));goto L_002d8320;}}
/* 002d8344: sw s0,0x10(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(16));
L_002d8348:;
/* 002d8348: move v0,s2 */ set(2,cpu(18));
L_002d834c:;
/* 002d834c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d8350: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d8354: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d8358: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d835c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8360: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d8364: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d8368: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d836c: jr ra */ {uint64_t target=cpu(31);/* delay 002d8370 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002d8378(void){
nocturneEffectAxisNoteEntry(0x002d8378u);
uint64_t incoming=cpu(31);
/* 002d8378: addiu sp,sp,-0xb0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff50)));
/* 002d837c: sd s0,0x60(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d8380: move s0,t1 */ set(16,cpu(9));
/* 002d8384: sd s4,0x80(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002d8388: move s4,a1 */ set(20,cpu(5));
/* 002d838c: sd s7,0x98(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002d8390: move s7,a0 */ set(23,cpu(4));
/* 002d8394: sd s1,0x68(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002d8398: sd s2,0x70(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d839c: sd s3,0x78(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d83a0: sd s5,0x88(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002d83a4: sd s6,0x90(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002d83a8: sd s8,0xa0(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002d83ac: sd ra,0xa8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002d83b0: sw a2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 002d83b4: lw t3,0x40(s7) */ lw(11,ea(23,(int32_t)UINT32_C(0x00000040)));
/* 002d83b8: sw a3,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
/* 002d83bc: sw t0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(8));
/* 002d83c0: beq t3,zero,0x002d83ec */ {int taken=(cpu(11)==cpu(0));/* delay 002d83c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(10));if(taken){goto L_002d83ec;}}
/* 002d83c8: lw a2,0x44(s7) */ lw(6,ea(23,(int32_t)UINT32_C(0x00000044)));
/* 002d83cc: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002d83d0: move a1,t3 */ set(5,cpu(11));
/* 002d83d4: sw a2,0x4(t3) */ sw(ea(11,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));
/* 002d83d8: lw v0,0x44(s7) */ lw(2,ea(23,(int32_t)UINT32_C(0x00000044)));
/* 002d83dc: sllv v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)<<(cpu(2)&31u)));
/* 002d83e0: jal 0x002da678 */ set(31,0x002d83e8u);/* delay 002d83e4 */ sw(ea(11,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002d83e0));
/* 002d83e8: sw zero,0x40(s7) */ sw(ea(23,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));
L_002d83ec:;
/* 002d83ec: dsrl32 v0,s4,0x0 */ set(2,cpu(20)>>32);
/* 002d83f0: dsll32 a0,v0,0x0 */ set(4,cpu(2)<<32);
/* 002d83f4: dsra32 a0,a0,0x0 */ set(4,(uint64_t)((int64_t)cpu(4)>>32));
/* 002d83f8: bgezl a0,0x002d842c */ {int taken=((int64_t)cpu(4)>=0);if(taken){/* delay 002d83fc */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));goto L_002d842c;}}
/* 002d8400: lui v0,0x7fff */ set(2,sx(UINT32_C(0x7fff0000)));
/* 002d8404: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 002d8408: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002d840c: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d8410: and s4,s4,v1 */ set(20,cpu(20)&cpu(3));
/* 002d8414: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 002d8418: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002d841c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d8420: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002d8424: or s4,s4,v0 */ set(20,cpu(20)|cpu(2));
/* 002d8428: dsrl32 v0,s4,0x0 */ set(2,cpu(20)>>32);
L_002d842c:;
/* 002d842c: dsll32 s0,v0,0x0 */ set(16,cpu(2)<<32);
/* 002d8430: dsra32 s0,s0,0x0 */ set(16,(uint64_t)((int64_t)cpu(16)>>32));
/* 002d8434: lui v1,0x7ff0 */ set(3,sx(UINT32_C(0x7ff00000)));
/* 002d8438: and v0,s0,v1 */ set(2,cpu(16)&cpu(3));
/* 002d843c: bne v0,v1,0x002d8498 */ {int taken=(cpu(2)!=cpu(3));/* delay 002d8440 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002d8498;}}
/* 002d8444: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d8448: dsrl v0,v0,0xc */ set(2,cpu(2)>>12);
/* 002d844c: li v1,0x270f */ set(3,sx(UINT32_C(0x0000270f)));
/* 002d8450: and v0,s4,v0 */ set(2,cpu(20)&cpu(2));
/* 002d8454: bne v0,zero,0x002d8468 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d8458 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_002d8468;}}
/* 002d845c: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d8460: b 0x002d8470 */ /* delay 002d8464 */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0xffffb880)));goto L_002d8470;
L_002d8468:;
/* 002d8468: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d846c: addiu s5,v0,-0x4770 */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0xffffb890)));
L_002d8470:;
/* 002d8470: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d8474: beq v0,zero,0x002d84d8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d8478 */ set(3,sx((uint32_t)cpu(21)+UINT32_C(0x00000008)));if(taken){goto L_002d84d8;}}
/* 002d847c: lb v0,0x3(s5) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(21,(int32_t)UINT32_C(0x00000003))));
/* 002d8480: addiu a0,s5,0x3 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x00000003)));
/* 002d8484: movz v1,a0,v0 */ if(cpu(2)==0){set(3,cpu(4));}
/* 002d8488: lw a0,0x14(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d848c: b 0x002d84d8 */ /* delay 002d8490 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));goto L_002d84d8;
L_002d8498:;
/* 002d8498: move a0,s4 */ set(4,cpu(20));
/* 002d849c: move a1,zero */ set(5,cpu(0));
/* 002d84a0: jal 0x002d1b38 */ set(31,0x002d84a8u);/* delay 002d84a4 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d84a0));
/* 002d84a8: bne v0,zero,0x002d84e0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d84ac */ set(4,cpu(23));if(taken){goto L_002d84e0;}}
/* 002d84b0: lw a0,0x10(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d84b4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d84b8: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002d84bc: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d84c0: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d84c4: beq v0,zero,0x002d84d8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d84c8 */ set(21,sx((uint32_t)cpu(3)+UINT32_C(0xffffb898)));if(taken){goto L_002d84d8;}}
/* 002d84cc: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d84d0: addiu v0,s5,0x1 */ set(2,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));
/* 002d84d4: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002d84d8:;
/* 002d84d8: b 0x002d95ac */ /* delay 002d84dc */ set(2,cpu(21));goto L_002d95ac;
L_002d84e0:;
/* 002d84e0: move a1,s4 */ set(5,cpu(20));
/* 002d84e4: move a2,sp */ set(6,cpu(29));
/* 002d84e8: jal 0x002db320 */ set(31,0x002d84f0u);/* delay 002d84ec */ set(7,sx((uint32_t)cpu(29)+UINT32_C(0x00000004)));nocturneBattlePanelRendererCall(UINT32_C(0x002db320),UINT32_C(0x002d84e8));
/* 002d84f0: sw v0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 002d84f4: srl v0,s0,0x14 */ set(2,sx((uint32_t)cpu(16)>>20));
/* 002d84f8: andi s3,v0,0x7ff */ set(19,cpu(2)&UINT32_C(0x000007ff));
/* 002d84fc: beq s3,zero,0x002d8550 */ {int taken=(cpu(19)==cpu(0));/* delay 002d8500 */ set(2,sx(UINT32_C(0x000f0000)));if(taken){goto L_002d8550;}}
/* 002d8504: move s6,s4 */ set(22,cpu(20));
/* 002d8508: dsra32 v1,s6,0x0 */ set(3,(uint64_t)((int64_t)cpu(22)>>32));
/* 002d850c: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d8510: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 002d8514: lui a1,0xffff */ set(5,sx(UINT32_C(0xffff0000)));
/* 002d8518: dsrl32 a1,a1,0x0 */ set(5,cpu(5)>>32);
/* 002d851c: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d8520: and s6,s6,a1 */ set(22,cpu(22)&cpu(5));
/* 002d8524: or s6,s6,v1 */ set(22,cpu(22)|cpu(3));
/* 002d8528: lui a0,0x3ff0 */ set(4,sx(UINT32_C(0x3ff00000)));
/* 002d852c: dsra32 v0,s6,0x0 */ set(2,(uint64_t)((int64_t)cpu(22)>>32));
/* 002d8530: and s6,s6,a1 */ set(22,cpu(22)&cpu(5));
/* 002d8534: or v0,v0,a0 */ set(2,cpu(2)|cpu(4));
/* 002d8538: addiu s3,s3,-0x3ff */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xfffffc01)));
/* 002d853c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d8540: sw zero,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));
/* 002d8544: or s6,s6,v0 */ set(22,cpu(22)|cpu(2));
/* 002d8548: b 0x002d85f0 */ /* delay 002d854c */ lw(18,ea(29,(int32_t)UINT32_C(0x00000004)));goto L_002d85f0;
L_002d8550:;
/* 002d8550: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d8554: lw s2,0x4(sp) */ lw(18,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002d8558: addu a0,s2,v0 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 002d855c: addiu s3,a0,0x432 */ set(19,sx((uint32_t)cpu(4)+UINT32_C(0x00000432)));
/* 002d8560: slti v0,s3,0x21 */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000021));
/* 002d8564: bne v0,zero,0x002d8590 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d8568 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(19)));if(taken){goto L_002d8590;}}
/* 002d856c: addiu a0,a0,0x412 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000412)));
/* 002d8570: subu v1,zero,s3 */ set(3,sx((uint32_t)cpu(0)-(uint32_t)cpu(19)));
/* 002d8574: dsll32 v0,s4,0x0 */ set(2,cpu(20)<<32);
/* 002d8578: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d857c: sllv v1,s0,v1 */ set(3,sx((uint32_t)cpu(16)<<(cpu(3)&31u)));
/* 002d8580: srlv v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)>>(cpu(4)&31u)));
/* 002d8584: b 0x002d859c */ /* delay 002d8588 */ set(16,cpu(3)|cpu(2));goto L_002d859c;
L_002d8590:;
/* 002d8590: dsll32 v1,s4,0x0 */ set(3,cpu(20)<<32);
/* 002d8594: dsra32 v1,v1,0x0 */ set(3,(uint64_t)((int64_t)cpu(3)>>32));
/* 002d8598: sllv s0,v1,v0 */ set(16,sx((uint32_t)cpu(3)<<(cpu(2)&31u)));
L_002d859c:;
/* 002d859c: jal 0x002d1b88 */ set(31,0x002d85a4u);/* delay 002d85a0 */ set(4,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b88),UINT32_C(0x002d859c));
/* 002d85a4: bgez s0,0x002d85c0 */ {int taken=((int64_t)cpu(16)>=0);/* delay 002d85a8 */ if(taken){goto L_002d85c0;}}
/* 002d85ac: ori a1,zero,0x83e0 */ set(5,cpu(0)|UINT32_C(0x000083e0));
/* 002d85b0: dsll32 a1,a1,0xf */ set(5,cpu(5)<<47);
/* 002d85b4: move a0,v0 */ set(4,cpu(2));
/* 002d85b8: jal 0x002d17f0 */ set(31,0x002d85c0u);/* delay 002d85bc */ nocturneBattlePanelRendererCall(UINT32_C(0x002d17f0),UINT32_C(0x002d85b8));
L_002d85c0:;
/* 002d85c0: move s6,v0 */ set(22,cpu(2));
/* 002d85c4: lui v0,0xfe10 */ set(2,sx(UINT32_C(0xfe100000)));
/* 002d85c8: dsra32 v1,s6,0x0 */ set(3,(uint64_t)((int64_t)cpu(22)>>32));
/* 002d85cc: lui a0,0xffff */ set(4,sx(UINT32_C(0xffff0000)));
/* 002d85d0: dsrl32 a0,a0,0x0 */ set(4,cpu(4)>>32);
/* 002d85d4: and s6,s6,a0 */ set(22,cpu(22)&cpu(4));
/* 002d85d8: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002d85dc: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002d85e0: sw a0,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(4));
/* 002d85e4: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d85e8: addiu s3,s3,-0x433 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xfffffbcd)));
/* 002d85ec: or s6,s6,v1 */ set(22,cpu(22)|cpu(3));
L_002d85f0:;
/* 002d85f0: ori a1,zero,0xffe0 */ set(5,cpu(0)|UINT32_C(0x0000ffe0));
/* 002d85f4: dsll32 a1,a1,0xe */ set(5,cpu(5)<<46);
/* 002d85f8: move a0,s6 */ set(4,cpu(22));
/* 002d85fc: jal 0x002d1848 */ set(31,0x002d8604u);/* delay 002d8600 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d85fc));
/* 002d8604: lui at,0x55 */ set(1,sx(UINT32_C(0x00550000)));
/* 002d8608: ld a1,-0x4760(at) */ restore(5,ea(1,(int32_t)UINT32_C(0xffffb8a0)));
/* 002d860c: move a0,v0 */ set(4,cpu(2));
/* 002d8610: jal 0x002d18b0 */ set(31,0x002d8618u);/* delay 002d8614 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8610));
/* 002d8618: lui at,0x55 */ set(1,sx(UINT32_C(0x00550000)));
/* 002d861c: ld a1,-0x4758(at) */ restore(5,ea(1,(int32_t)UINT32_C(0xffffb8a8)));
/* 002d8620: move a0,v0 */ set(4,cpu(2));
/* 002d8624: jal 0x002d17f0 */ set(31,0x002d862cu);/* delay 002d8628 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d17f0),UINT32_C(0x002d8624));
/* 002d862c: move s0,v0 */ set(16,cpu(2));
/* 002d8630: jal 0x002d1b88 */ set(31,0x002d8638u);/* delay 002d8634 */ set(4,cpu(19));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b88),UINT32_C(0x002d8630));
/* 002d8638: lui at,0x55 */ set(1,sx(UINT32_C(0x00550000)));
/* 002d863c: ld a1,-0x4750(at) */ restore(5,ea(1,(int32_t)UINT32_C(0xffffb8b0)));
/* 002d8640: move a0,v0 */ set(4,cpu(2));
/* 002d8644: jal 0x002d18b0 */ set(31,0x002d864cu);/* delay 002d8648 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8644));
/* 002d864c: move a0,s0 */ set(4,cpu(16));
/* 002d8650: move a1,v0 */ set(5,cpu(2));
/* 002d8654: jal 0x002d17f0 */ set(31,0x002d865cu);/* delay 002d8658 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d17f0),UINT32_C(0x002d8654));
/* 002d865c: move s1,v0 */ set(17,cpu(2));
/* 002d8660: move a0,s1 */ set(4,cpu(17));
/* 002d8664: jal 0x002d1c40 */ set(31,0x002d866cu);/* delay 002d8668 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1c40),UINT32_C(0x002d8664));
/* 002d866c: move a0,s1 */ set(4,cpu(17));
/* 002d8670: move a1,zero */ set(5,cpu(0));
/* 002d8674: jal 0x002d1b38 */ set(31,0x002d867cu);/* delay 002d8678 */ set(30,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8674));
/* 002d867c: bgez v0,0x002d86a8 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002d8680 */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_002d86a8;}}
/* 002d8684: jal 0x002d1b88 */ set(31,0x002d868cu);/* delay 002d8688 */ set(4,cpu(30));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b88),UINT32_C(0x002d8684));
/* 002d868c: move a0,s1 */ set(4,cpu(17));
/* 002d8690: move a1,v0 */ set(5,cpu(2));
/* 002d8694: jal 0x002d1b38 */ set(31,0x002d869cu);/* delay 002d8698 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8694));
/* 002d869c: addiu v1,s8,-0x1 */ set(3,sx((uint32_t)cpu(30)+UINT32_C(0xffffffff)));
/* 002d86a0: movn s8,v1,v0 */ if(cpu(2)!=0){set(30,cpu(3));}
/* 002d86a4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
L_002d86a8:;
/* 002d86a8: sltiu v0,s8,0x17 */ set(2,cpu(30)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000017));
/* 002d86ac: beq v0,zero,0x002d86dc */ {int taken=(cpu(2)==cpu(0));/* delay 002d86b0 */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(3));if(taken){goto L_002d86dc;}}
/* 002d86b4: sll v0,s8,0x3 */ set(2,sx((uint32_t)cpu(30)<<3));
/* 002d86b8: move a0,s4 */ set(4,cpu(20));
/* 002d86bc: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 002d86c0: addu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 002d86c4: ld a1,-0x46d0(a1) */ restore(5,ea(5,(int32_t)UINT32_C(0xffffb930)));
/* 002d86c8: jal 0x002d1b38 */ set(31,0x002d86d0u);/* delay 002d86cc */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d86c8));
/* 002d86d0: addiu v1,s8,-0x1 */ set(3,sx((uint32_t)cpu(30)+UINT32_C(0xffffffff)));
/* 002d86d4: slti v0,v0,0x0 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 002d86d8: movn s8,v1,v0 */ if(cpu(2)!=0){set(30,cpu(3));}
L_002d86dc:;
/* 002d86dc: subu v0,s2,s3 */ set(2,sx((uint32_t)cpu(18)-(uint32_t)cpu(19)));
/* 002d86e0: addiu s0,v0,-0x1 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002d86e4: bltzl s0,0x002d86f8 */ {int taken=((int64_t)cpu(16)<0);if(taken){/* delay 002d86e8 */ set(16,sx((uint32_t)cpu(0)-(uint32_t)cpu(16)));goto L_002d86f8;}}
/* 002d86ec: sw s0,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(16));
/* 002d86f0: b 0x002d8700 */ /* delay 002d86f4 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));goto L_002d8700;
L_002d86f8:;
/* 002d86f8: sw zero,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(0));
/* 002d86fc: sw s0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(16));
L_002d8700:;
/* 002d8700: bltz s8,0x002d8720 */ {int taken=((int64_t)cpu(30)<0);/* delay 002d8704 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000038)));if(taken){goto L_002d8720;}}
/* 002d8708: sw zero,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 002d870c: addu a0,a0,s8 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(30)));
/* 002d8710: sw s8,0x3c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(30));
/* 002d8714: b 0x002d8738 */ /* delay 002d8718 */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(4));goto L_002d8738;
L_002d8720:;
/* 002d8720: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d8724: subu v1,zero,s8 */ set(3,sx((uint32_t)cpu(0)-(uint32_t)cpu(30)));
/* 002d8728: sw v1,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(3));
/* 002d872c: subu v0,v0,s8 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(30)));
/* 002d8730: sw zero,0x3c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));
/* 002d8734: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
L_002d8738:;
/* 002d8738: lw a0,0x8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d873c: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
/* 002d8740: sltiu v1,a0,0xa */ set(3,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 002d8744: movz a0,zero,v1 */ if(cpu(3)==0){set(4,cpu(0));}
/* 002d8748: slti v0,a0,0x6 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 002d874c: bne v0,zero,0x002d8760 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d8750 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));if(taken){goto L_002d8760;}}
/* 002d8754: addiu a0,a0,-0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffc)));
/* 002d8758: move s1,zero */ set(17,cpu(0));
/* 002d875c: sw a0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
L_002d8760:;
/* 002d8760: lw v1,0x8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d8764: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002d8768: sw a0,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(4));
/* 002d876c: sltiu v0,v1,0x6 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000006));
/* 002d8770: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002d8774: sw v1,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 002d8778: beq v0,zero,0x002d87fc */ {int taken=(cpu(2)==cpu(0));/* delay 002d877c */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));if(taken){goto L_002d87fc;}}
/* 002d8780: lw a0,0x8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d8784: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 002d8788: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002d878c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002d8790: lw v1,-0x4740(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffb8c0)));
/* 002d8794: jr v1 */ {uint64_t target=cpu(3);/* delay 002d8798 */ switch((uint32_t)target){case 0x002d87a0u:goto L_002d87a0;case 0x002d87b0u:goto L_002d87b0;case 0x002d87b4u:goto L_002d87b4;case 0x002d87d8u:goto L_002d87d8;case 0x002d87dcu:goto L_002d87dc;default:abort();}}
L_002d87a0:;
/* 002d87a0: li s3,0x12 */ set(19,sx(UINT32_C(0x00000012)));
/* 002d87a4: b 0x002d87fc */ /* delay 002d87a8 */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));goto L_002d87fc;
L_002d87b0:;
/* 002d87b0: sw zero,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(0));
L_002d87b4:;
/* 002d87b4: lw v1,0xc(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000000c)));
/* 002d87b8: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
/* 002d87bc: slt v0,zero,v1 */ set(2,(int64_t)cpu(0)<(int64_t)cpu(3));
/* 002d87c0: movn s3,v1,v0 */ if(cpu(2)!=0){set(19,cpu(3));}
/* 002d87c4: sw s3,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(19));
/* 002d87c8: sw s3,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(19));
/* 002d87cc: b 0x002d87fc */ /* delay 002d87d0 */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(19));goto L_002d87fc;
L_002d87d8:;
/* 002d87d8: sw zero,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(0));
L_002d87dc:;
/* 002d87dc: lw a0,0xc(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000000c)));
/* 002d87e0: addu v0,a0,s8 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(30)));
/* 002d87e4: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002d87e8: addiu s3,v0,0x1 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d87ec: sw v0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));
/* 002d87f0: slt v1,zero,s3 */ set(3,(int64_t)cpu(0)<(int64_t)cpu(19));
/* 002d87f4: sw s3,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(19));
/* 002d87f8: movz s3,a0,v1 */ if(cpu(3)==0){set(19,cpu(4));}
L_002d87fc:;
/* 002d87fc: sltiu v0,s3,0x18 */ set(2,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000018));
/* 002d8800: sw zero,0x44(s7) */ sw(ea(23,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(0));
/* 002d8804: bne v0,zero,0x002d8830 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d8808 */ set(16,sx(UINT32_C(0x00000004)));if(taken){goto L_002d8830;}}
/* 002d880c: move v1,zero */ set(3,cpu(0));
L_002d8810:;
/* 002d8810: sll s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)<<1));
/* 002d8814: addiu v0,s0,0x14 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000014)));
/* 002d8818: sltu v0,s3,v0 */ set(2,cpu(19)<cpu(2));
/* 002d881c: nop  */ 
/* 002d8820: nop  */ 
/* 002d8824: beq v0,zero,0x002d8810 */ {int taken=(cpu(2)==cpu(0));/* delay 002d8828 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));if(taken){goto L_002d8810;}}
/* 002d882c: sw v1,0x44(s7) */ sw(ea(23,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(3));
L_002d8830:;
/* 002d8830: lw a1,0x44(s7) */ lw(5,ea(23,(int32_t)UINT32_C(0x00000044)));
/* 002d8834: jal 0x002da5d0 */ set(31,0x002d883cu);/* delay 002d8838 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002d8834));
/* 002d883c: sw v0,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));
/* 002d8840: lw v1,0x20(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8844: lw a0,0x54(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 002d8848: sltiu v0,v1,0xf */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000f));
/* 002d884c: sw a0,0x40(s7) */ sw(ea(23,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(4));
/* 002d8850: beq v0,zero,0x002d8ca0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d8854 */ lw(21,ea(29,(int32_t)UINT32_C(0x00000054)));if(taken){goto L_002d8ca0;}}
/* 002d8858: beql s1,zero,0x002d8ca4 */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 002d885c */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002d8ca4;}}
/* 002d8860: move s6,s4 */ set(22,cpu(20));
/* 002d8864: sw s8,0x2c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(30));
/* 002d8868: sw v1,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(3));
/* 002d886c: blez s8,0x002d8908 */ {int taken=((int64_t)cpu(30)<=0);/* delay 002d8870 */ set(19,sx(UINT32_C(0x00000002)));if(taken){goto L_002d8908;}}
/* 002d8874: andi v0,s8,0xf */ set(2,cpu(30)&UINT32_C(0x0000000f));
/* 002d8878: sra s0,s8,0x4 */ set(16,sx((uint32_t)((int32_t)cpu(30)>>4)));
/* 002d887c: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 002d8880: andi v1,s0,0x10 */ set(3,cpu(16)&UINT32_C(0x00000010));
/* 002d8884: lui s1,0x55 */ set(17,sx(UINT32_C(0x00550000)));
/* 002d8888: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002d888c: ld s1,-0x46d0(s1) */ restore(17,ea(17,(int32_t)UINT32_C(0xffffb930)));
/* 002d8890: beq v1,zero,0x002d88b0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d8894 */ set(2,sx(UINT32_C(0x00550000)));if(taken){goto L_002d88b0;}}
/* 002d8898: move a0,s4 */ set(4,cpu(20));
/* 002d889c: ld a1,-0x45e8(v0) */ restore(5,ea(2,(int32_t)UINT32_C(0xffffba18)));
/* 002d88a0: andi s0,s0,0xf */ set(16,cpu(16)&UINT32_C(0x0000000f));
/* 002d88a4: jal 0x002e6c48 */ set(31,0x002d88acu);/* delay 002d88a8 */ set(19,sx(UINT32_C(0x00000003)));nocturneBattlePanelRendererCall(UINT32_C(0x002e6c48),UINT32_C(0x002d88a4));
/* 002d88ac: move s4,v0 */ set(20,cpu(2));
L_002d88b0:;
/* 002d88b0: beq s0,zero,0x002d88ec */ {int taken=(cpu(16)==cpu(0));/* delay 002d88b4 */ set(2,sx(UINT32_C(0x00550000)));if(taken){goto L_002d88ec;}}
/* 002d88b8: addiu s2,v0,-0x4608 */ set(18,sx((uint32_t)cpu(2)+UINT32_C(0xffffb9f8)));
/* 002d88bc: nop  */ 
L_002d88c0:;
/* 002d88c0: andi v0,s0,0x1 */ set(2,cpu(16)&UINT32_C(0x00000001));
/* 002d88c4: beql v0,zero,0x002d88e4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d88c8 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>1)));goto L_002d88e4;}}
/* 002d88cc: ld a1,0x0(s2) */ restore(5,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 002d88d0: move a0,s1 */ set(4,cpu(17));
/* 002d88d4: jal 0x002d18b0 */ set(31,0x002d88dcu);/* delay 002d88d8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d88d4));
/* 002d88dc: move s1,v0 */ set(17,cpu(2));
/* 002d88e0: sra s0,s0,0x1 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>1)));
L_002d88e4:;
/* 002d88e4: bne s0,zero,0x002d88c0 */ {int taken=(cpu(16)!=cpu(0));/* delay 002d88e8 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000008)));if(taken){goto L_002d88c0;}}
L_002d88ec:;
/* 002d88ec: move a0,s4 */ set(4,cpu(20));
/* 002d88f0: move a1,s1 */ set(5,cpu(17));
/* 002d88f4: jal 0x002e6c48 */ set(31,0x002d88fcu);/* delay 002d88f8 */ nocturneBattlePanelRendererCall(UINT32_C(0x002e6c48),UINT32_C(0x002d88f4));
/* 002d88fc: b 0x002d896c */ /* delay 002d8900 */ set(20,cpu(2));goto L_002d896c;
L_002d8908:;
/* 002d8908: subu s1,zero,s8 */ set(17,sx((uint32_t)cpu(0)-(uint32_t)cpu(30)));
/* 002d890c: beq s1,zero,0x002d896c */ {int taken=(cpu(17)==cpu(0));/* delay 002d8910 */ set(2,cpu(17)&UINT32_C(0x0000000f));if(taken){goto L_002d896c;}}
/* 002d8914: move a1,s4 */ set(5,cpu(20));
/* 002d8918: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 002d891c: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 002d8920: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002d8924: ld a0,-0x46d0(a0) */ restore(4,ea(4,(int32_t)UINT32_C(0xffffb930)));
/* 002d8928: jal 0x002d18b0 */ set(31,0x002d8930u);/* delay 002d892c */ set(16,sx((uint32_t)((int32_t)cpu(17)>>4)));nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8928));
/* 002d8930: beq s0,zero,0x002d896c */ {int taken=(cpu(16)==cpu(0));/* delay 002d8934 */ set(20,cpu(2));if(taken){goto L_002d896c;}}
/* 002d8938: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d893c: addiu s1,v0,-0x4608 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0xffffb9f8)));
L_002d8940:;
/* 002d8940: andi v0,s0,0x1 */ set(2,cpu(16)&UINT32_C(0x00000001));
/* 002d8944: beql v0,zero,0x002d8964 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d8948 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>1)));goto L_002d8964;}}
/* 002d894c: ld a0,0x0(s1) */ restore(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002d8950: move a1,s4 */ set(5,cpu(20));
/* 002d8954: jal 0x002d18b0 */ set(31,0x002d895cu);/* delay 002d8958 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8954));
/* 002d895c: move s4,v0 */ set(20,cpu(2));
/* 002d8960: sra s0,s0,0x1 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>1)));
L_002d8964:;
/* 002d8964: bne s0,zero,0x002d8940 */ {int taken=(cpu(16)!=cpu(0));/* delay 002d8968 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000008)));if(taken){goto L_002d8940;}}
L_002d896c:;
/* 002d896c: lw v0,0x30(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d8970: beq v0,zero,0x002d89c8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d8974 */ if(taken){goto L_002d89c8;}}
/* 002d8978: ori a1,zero,0xffc0 */ set(5,cpu(0)|UINT32_C(0x0000ffc0));
/* 002d897c: dsll32 a1,a1,0xe */ set(5,cpu(5)<<46);
/* 002d8980: move a0,s4 */ set(4,cpu(20));
/* 002d8984: jal 0x002d1b38 */ set(31,0x002d898cu);/* delay 002d8988 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8984));
/* 002d898c: bgez v0,0x002d89c8 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002d8990 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002d89c8;}}
/* 002d8994: blez v1,0x002d89c8 */ {int taken=((int64_t)cpu(3)<=0);/* delay 002d8998 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_002d89c8;}}
/* 002d899c: blez a0,0x002d8c90 */ {int taken=((int64_t)cpu(4)<=0);/* delay 002d89a0 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000024)));if(taken){goto L_002d8c90;}}
/* 002d89a4: lw v0,0x28(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d89a8: move a1,s4 */ set(5,cpu(20));
/* 002d89ac: ori a0,zero,0x8048 */ set(4,cpu(0)|UINT32_C(0x00008048));
/* 002d89b0: dsll32 a0,a0,0xf */ set(4,cpu(4)<<47);
/* 002d89b4: addiu s8,s8,-0x1 */ set(30,sx((uint32_t)cpu(30)+UINT32_C(0xffffffff)));
/* 002d89b8: sw v0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 002d89bc: jal 0x002d18b0 */ set(31,0x002d89c4u);/* delay 002d89c0 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d89bc));
/* 002d89c4: move s4,v0 */ set(20,cpu(2));
L_002d89c8:;
/* 002d89c8: jal 0x002d1b88 */ set(31,0x002d89d0u);/* delay 002d89cc */ set(4,cpu(19));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b88),UINT32_C(0x002d89c8));
/* 002d89d0: move a1,s4 */ set(5,cpu(20));
/* 002d89d4: move a0,v0 */ set(4,cpu(2));
/* 002d89d8: jal 0x002d18b0 */ set(31,0x002d89e0u);/* delay 002d89dc */ nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d89d8));
/* 002d89e0: ori a1,zero,0x8038 */ set(5,cpu(0)|UINT32_C(0x00008038));
/* 002d89e4: dsll32 a1,a1,0xf */ set(5,cpu(5)<<47);
/* 002d89e8: move a0,v0 */ set(4,cpu(2));
/* 002d89ec: jal 0x002d17f0 */ set(31,0x002d89f4u);/* delay 002d89f0 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d17f0),UINT32_C(0x002d89ec));
/* 002d89f4: lui a0,0xffff */ set(4,sx(UINT32_C(0xffff0000)));
/* 002d89f8: dsrl32 a0,a0,0x0 */ set(4,cpu(4)>>32);
/* 002d89fc: move s2,v0 */ set(18,cpu(2));
/* 002d8a00: lui v0,0xfcc0 */ set(2,sx(UINT32_C(0xfcc00000)));
/* 002d8a04: dsra32 v1,s2,0x0 */ set(3,(uint64_t)((int64_t)cpu(18)>>32));
/* 002d8a08: and s2,s2,a0 */ set(18,cpu(18)&cpu(4));
/* 002d8a0c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002d8a10: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d8a14: or s2,s2,v1 */ set(18,cpu(18)|cpu(3));
/* 002d8a18: lw v1,0x20(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8a1c: bne v1,zero,0x002d8a88 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d8a20 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000034)));if(taken){goto L_002d8a88;}}
/* 002d8a24: ori a1,zero,0x8028 */ set(5,cpu(0)|UINT32_C(0x00008028));
/* 002d8a28: dsll32 a1,a1,0xf */ set(5,cpu(5)<<47);
/* 002d8a2c: move a0,s4 */ set(4,cpu(20));
/* 002d8a30: sw zero,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));
/* 002d8a34: jal 0x002d1848 */ set(31,0x002d8a3cu);/* delay 002d8a38 */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d8a34));
/* 002d8a3c: move s0,v0 */ set(16,cpu(2));
/* 002d8a40: move a1,s2 */ set(5,cpu(18));
/* 002d8a44: move a0,s0 */ set(4,cpu(16));
/* 002d8a48: jal 0x002d1b38 */ set(31,0x002d8a50u);/* delay 002d8a4c */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8a48));
/* 002d8a50: bgtz v0,0x002d91e0 */ {int taken=((int64_t)cpu(2)>0);/* delay 002d8a54 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000054)));if(taken){goto L_002d91e0;}}
/* 002d8a58: move a1,s2 */ set(5,cpu(18));
/* 002d8a5c: move a0,zero */ set(4,cpu(0));
/* 002d8a60: jal 0x002d1848 */ set(31,0x002d8a68u);/* delay 002d8a64 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d8a60));
/* 002d8a68: move a0,s0 */ set(4,cpu(16));
/* 002d8a6c: move a1,v0 */ set(5,cpu(2));
/* 002d8a70: jal 0x002d1b38 */ set(31,0x002d8a78u);/* delay 002d8a74 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8a70));
/* 002d8a78: bltz v0,0x002d91d0 */ {int taken=((int64_t)cpu(2)<0);/* delay 002d8a7c */ lw(2,ea(29,(int32_t)UINT32_C(0x00000024)));if(taken){goto L_002d91d0;}}
/* 002d8a80: b 0x002d8c90 */ /* delay 002d8a84 */ goto L_002d8c90;
L_002d8a88:;
/* 002d8a88: beq a0,zero,0x002d8b88 */ {int taken=(cpu(4)==cpu(0));/* delay 002d8a8c */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002d8b88;}}
/* 002d8a90: ori a0,zero,0xff80 */ set(4,cpu(0)|UINT32_C(0x0000ff80));
/* 002d8a94: dsll32 a0,a0,0xe */ set(4,cpu(4)<<46);
/* 002d8a98: sll v0,v1,0x3 */ set(2,sx((uint32_t)cpu(3)<<3));
/* 002d8a9c: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 002d8aa0: addu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 002d8aa4: ld a1,-0x46d8(a1) */ restore(5,ea(5,(int32_t)UINT32_C(0xffffb928)));
/* 002d8aa8: jal 0x002e6c48 */ set(31,0x002d8ab0u);/* delay 002d8aac */ set(19,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002e6c48),UINT32_C(0x002d8aa8));
/* 002d8ab0: move a1,s2 */ set(5,cpu(18));
/* 002d8ab4: move a0,v0 */ set(4,cpu(2));
/* 002d8ab8: jal 0x002d1848 */ set(31,0x002d8ac0u);/* delay 002d8abc */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d8ab8));
/* 002d8ac0: b 0x002d8af4 */ /* delay 002d8ac4 */ set(18,cpu(2));goto L_002d8af4;
L_002d8ac8:;
/* 002d8ac8: ori a0,zero,0x8048 */ set(4,cpu(0)|UINT32_C(0x00008048));
/* 002d8acc: dsll32 a0,a0,0xf */ set(4,cpu(4)<<47);
/* 002d8ad0: move a1,s2 */ set(5,cpu(18));
/* 002d8ad4: jal 0x002d18b0 */ set(31,0x002d8adcu);/* delay 002d8ad8 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8ad4));
/* 002d8adc: ori a0,zero,0x8048 */ set(4,cpu(0)|UINT32_C(0x00008048));
/* 002d8ae0: dsll32 a0,a0,0xf */ set(4,cpu(4)<<47);
/* 002d8ae4: move a1,s1 */ set(5,cpu(17));
/* 002d8ae8: jal 0x002d18b0 */ set(31,0x002d8af0u);/* delay 002d8aec */ set(18,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8ae8));
/* 002d8af0: move s4,v0 */ set(20,cpu(2));
L_002d8af4:;
/* 002d8af4: move a0,s4 */ set(4,cpu(20));
/* 002d8af8: jal 0x002d1c40 */ set(31,0x002d8b00u);/* delay 002d8afc */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1c40),UINT32_C(0x002d8af8));
/* 002d8b00: move s0,v0 */ set(16,cpu(2));
/* 002d8b04: jal 0x002d1b88 */ set(31,0x002d8b0cu);/* delay 002d8b08 */ set(4,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b88),UINT32_C(0x002d8b04));
/* 002d8b0c: move a0,s4 */ set(4,cpu(20));
/* 002d8b10: move a1,v0 */ set(5,cpu(2));
/* 002d8b14: jal 0x002d1848 */ set(31,0x002d8b1cu);/* delay 002d8b18 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d8b14));
/* 002d8b1c: move a1,s2 */ set(5,cpu(18));
/* 002d8b20: move s1,v0 */ set(17,cpu(2));
/* 002d8b24: addiu v0,s0,0x30 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));
/* 002d8b28: sb v0,0x0(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d8b2c: move a0,s1 */ set(4,cpu(17));
/* 002d8b30: jal 0x002d1b38 */ set(31,0x002d8b38u);/* delay 002d8b34 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8b30));
/* 002d8b38: bltz v0,0x002d9584 */ {int taken=((int64_t)cpu(2)<0);/* delay 002d8b3c */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));if(taken){goto L_002d9584;}}
/* 002d8b40: ori a0,zero,0xffc0 */ set(4,cpu(0)|UINT32_C(0x0000ffc0));
/* 002d8b44: dsll32 a0,a0,0xe */ set(4,cpu(4)<<46);
/* 002d8b48: move a1,s1 */ set(5,cpu(17));
/* 002d8b4c: jal 0x002d1848 */ set(31,0x002d8b54u);/* delay 002d8b50 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d8b4c));
/* 002d8b54: move a1,s2 */ set(5,cpu(18));
/* 002d8b58: move a0,v0 */ set(4,cpu(2));
/* 002d8b5c: jal 0x002d1b38 */ set(31,0x002d8b64u);/* delay 002d8b60 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8b5c));
/* 002d8b64: bltz v0,0x002d8dcc */ {int taken=((int64_t)cpu(2)<0);/* delay 002d8b68 */ set(3,sx(UINT32_C(0x00000039)));if(taken){goto L_002d8dcc;}}
/* 002d8b6c: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8b70: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002d8b74: slt v0,s3,a0 */ set(2,(int64_t)cpu(19)<(int64_t)cpu(4));
/* 002d8b78: bne v0,zero,0x002d8ac8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d8b7c */ lw(2,ea(29,(int32_t)UINT32_C(0x00000024)));if(taken){goto L_002d8ac8;}}
/* 002d8b80: b 0x002d8c90 */ /* delay 002d8b84 */ goto L_002d8c90;
L_002d8b88:;
/* 002d8b88: move a1,s2 */ set(5,cpu(18));
/* 002d8b8c: sll v0,v1,0x3 */ set(2,sx((uint32_t)cpu(3)<<3));
/* 002d8b90: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 002d8b94: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002d8b98: ld a0,-0x46d8(a0) */ restore(4,ea(4,(int32_t)UINT32_C(0xffffb928)));
/* 002d8b9c: jal 0x002d18b0 */ set(31,0x002d8ba4u);/* delay 002d8ba0 */ set(19,sx(UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8b9c));
/* 002d8ba4: move s2,v0 */ set(18,cpu(2));
L_002d8ba8:;
/* 002d8ba8: move a0,s4 */ set(4,cpu(20));
/* 002d8bac: jal 0x002d1c40 */ set(31,0x002d8bb4u);/* delay 002d8bb0 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1c40),UINT32_C(0x002d8bac));
/* 002d8bb4: move s0,v0 */ set(16,cpu(2));
/* 002d8bb8: jal 0x002d1b88 */ set(31,0x002d8bc0u);/* delay 002d8bbc */ set(4,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b88),UINT32_C(0x002d8bb8));
/* 002d8bc0: move a0,s4 */ set(4,cpu(20));
/* 002d8bc4: move a1,v0 */ set(5,cpu(2));
/* 002d8bc8: jal 0x002d1848 */ set(31,0x002d8bd0u);/* delay 002d8bcc */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d8bc8));
/* 002d8bd0: move s1,v0 */ set(17,cpu(2));
/* 002d8bd4: addiu v0,s0,0x30 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));
/* 002d8bd8: sb v0,0x0(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d8bdc: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8be0: bne s3,a0,0x002d8c70 */ {int taken=(cpu(19)!=cpu(4));/* delay 002d8be4 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));if(taken){goto L_002d8c70;}}
/* 002d8be8: ori a0,zero,0xff80 */ set(4,cpu(0)|UINT32_C(0x0000ff80));
/* 002d8bec: dsll32 a0,a0,0xe */ set(4,cpu(4)<<46);
/* 002d8bf0: move a1,s2 */ set(5,cpu(18));
/* 002d8bf4: jal 0x002d17f0 */ set(31,0x002d8bfcu);/* delay 002d8bf8 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d17f0),UINT32_C(0x002d8bf4));
/* 002d8bfc: move a0,s1 */ set(4,cpu(17));
/* 002d8c00: move a1,v0 */ set(5,cpu(2));
/* 002d8c04: jal 0x002d1b38 */ set(31,0x002d8c0cu);/* delay 002d8c08 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8c04));
/* 002d8c0c: bgtz v0,0x002d8dcc */ {int taken=((int64_t)cpu(2)>0);/* delay 002d8c10 */ set(3,sx(UINT32_C(0x00000039)));if(taken){goto L_002d8dcc;}}
/* 002d8c14: ori a0,zero,0xff80 */ set(4,cpu(0)|UINT32_C(0x0000ff80));
/* 002d8c18: dsll32 a0,a0,0xe */ set(4,cpu(4)<<46);
/* 002d8c1c: move a1,s2 */ set(5,cpu(18));
/* 002d8c20: jal 0x002d1848 */ set(31,0x002d8c28u);/* delay 002d8c24 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d8c20));
/* 002d8c28: move a0,s1 */ set(4,cpu(17));
/* 002d8c2c: move a1,v0 */ set(5,cpu(2));
/* 002d8c30: jal 0x002d1b38 */ set(31,0x002d8c38u);/* delay 002d8c34 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8c30));
/* 002d8c38: bgez v0,0x002d8c90 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002d8c3c */ lw(2,ea(29,(int32_t)UINT32_C(0x00000024)));if(taken){goto L_002d8c90;}}
/* 002d8c40: li v1,0x30 */ set(3,sx(UINT32_C(0x00000030)));
/* 002d8c44: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
L_002d8c48:;
/* 002d8c48: lb v0,0x0(s5) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(21,(int32_t)UINT32_C(0x00000000))));
/* 002d8c4c: nop  */ 
/* 002d8c50: nop  */ 
/* 002d8c54: nop  */ 
/* 002d8c58: nop  */ 
/* 002d8c5c: beql v0,v1,0x002d8c48 */ {int taken=(cpu(2)==cpu(3));if(taken){/* delay 002d8c60 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));goto L_002d8c48;}}
/* 002d8c64: b 0x002d9580 */ /* delay 002d8c68 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));goto L_002d9580;
L_002d8c70:;
/* 002d8c70: ori a0,zero,0x8048 */ set(4,cpu(0)|UINT32_C(0x00008048));
/* 002d8c74: dsll32 a0,a0,0xf */ set(4,cpu(4)<<47);
/* 002d8c78: move a1,s1 */ set(5,cpu(17));
/* 002d8c7c: jal 0x002d18b0 */ set(31,0x002d8c84u);/* delay 002d8c80 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8c7c));
/* 002d8c84: b 0x002d8ba8 */ /* delay 002d8c88 */ set(20,cpu(2));goto L_002d8ba8;
L_002d8c90:;
/* 002d8c90: move s4,s6 */ set(20,cpu(22));
/* 002d8c94: lw s8,0x2c(sp) */ lw(30,ea(29,(int32_t)UINT32_C(0x0000002c)));
/* 002d8c98: sw v0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 002d8c9c: lw s5,0x54(sp) */ lw(21,ea(29,(int32_t)UINT32_C(0x00000054)));
L_002d8ca0:;
/* 002d8ca0: lw v1,0x0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002d8ca4:;
/* 002d8ca4: bltz v1,0x002d8e50 */ {int taken=((int64_t)cpu(3)<0);/* delay 002d8ca8 */ set(2,(int64_t)cpu(30)<(int64_t)(int32_t)UINT32_C(0x0000000f));if(taken){goto L_002d8e50;}}
/* 002d8cac: beq v0,zero,0x002d8e54 */ {int taken=(cpu(2)==cpu(0));/* delay 002d8cb0 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002d8e54;}}
/* 002d8cb4: lw v1,0xc(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000000c)));
/* 002d8cb8: sll v0,s8,0x3 */ set(2,sx((uint32_t)cpu(30)<<3));
/* 002d8cbc: lui s1,0x55 */ set(17,sx(UINT32_C(0x00550000)));
/* 002d8cc0: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002d8cc4: ld s1,-0x46d0(s1) */ restore(17,ea(17,(int32_t)UINT32_C(0xffffb930)));
/* 002d8cc8: bgez v1,0x002d8d20 */ {int taken=((int64_t)cpu(3)>=0);/* delay 002d8ccc */ set(19,sx(UINT32_C(0x00000001)));if(taken){goto L_002d8d20;}}
/* 002d8cd0: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8cd4: bgtz a0,0x002d8d20 */ {int taken=((int64_t)cpu(4)>0);/* delay 002d8cd8 */ if(taken){goto L_002d8d20;}}
/* 002d8cdc: sw zero,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));
/* 002d8ce0: bltz a0,0x002d91d0 */ {int taken=((int64_t)cpu(4)<0);/* delay 002d8ce4 */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(0));if(taken){goto L_002d91d0;}}
/* 002d8ce8: ori a1,zero,0x8028 */ set(5,cpu(0)|UINT32_C(0x00008028));
/* 002d8cec: dsll32 a1,a1,0xf */ set(5,cpu(5)<<47);
/* 002d8cf0: move a0,s1 */ set(4,cpu(17));
/* 002d8cf4: jal 0x002d18b0 */ set(31,0x002d8cfcu);/* delay 002d8cf8 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8cf4));
/* 002d8cfc: move a0,s4 */ set(4,cpu(20));
/* 002d8d00: move a1,v0 */ set(5,cpu(2));
/* 002d8d04: jal 0x002d1b38 */ set(31,0x002d8d0cu);/* delay 002d8d08 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8d04));
/* 002d8d0c: blez v0,0x002d91d4 */ {int taken=((int64_t)cpu(2)<=0);/* delay 002d8d10 */ lw(2,ea(29,(int32_t)UINT32_C(0x0000000c)));if(taken){goto L_002d91d4;}}
/* 002d8d14: b 0x002d91e0 */ /* delay 002d8d18 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000054)));goto L_002d91e0;
L_002d8d20:;
/* 002d8d20: move a1,s1 */ set(5,cpu(17));
/* 002d8d24: move a0,s4 */ set(4,cpu(20));
/* 002d8d28: jal 0x002e6c48 */ set(31,0x002d8d30u);/* delay 002d8d2c */ nocturneBattlePanelRendererCall(UINT32_C(0x002e6c48),UINT32_C(0x002d8d28));
/* 002d8d30: move a0,v0 */ set(4,cpu(2));
/* 002d8d34: jal 0x002d1c40 */ set(31,0x002d8d3cu);/* delay 002d8d38 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1c40),UINT32_C(0x002d8d34));
/* 002d8d3c: move s0,v0 */ set(16,cpu(2));
/* 002d8d40: jal 0x002d1b88 */ set(31,0x002d8d48u);/* delay 002d8d44 */ set(4,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d1b88),UINT32_C(0x002d8d40));
/* 002d8d48: move a1,s1 */ set(5,cpu(17));
/* 002d8d4c: move a0,v0 */ set(4,cpu(2));
/* 002d8d50: jal 0x002d18b0 */ set(31,0x002d8d58u);/* delay 002d8d54 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8d50));
/* 002d8d58: move a0,s4 */ set(4,cpu(20));
/* 002d8d5c: move a1,v0 */ set(5,cpu(2));
/* 002d8d60: jal 0x002d1848 */ set(31,0x002d8d68u);/* delay 002d8d64 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1848),UINT32_C(0x002d8d60));
/* 002d8d68: move a1,v0 */ set(5,cpu(2));
/* 002d8d6c: addiu v0,s0,0x30 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));
/* 002d8d70: sb v0,0x0(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d8d74: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8d78: bne s3,v0,0x002d8e18 */ {int taken=(cpu(19)!=cpu(2));/* delay 002d8d7c */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));if(taken){goto L_002d8e18;}}
/* 002d8d80: move a0,a1 */ set(4,cpu(5));
/* 002d8d84: jal 0x002d17f0 */ set(31,0x002d8d8cu);/* delay 002d8d88 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d17f0),UINT32_C(0x002d8d84));
/* 002d8d8c: move a1,s1 */ set(5,cpu(17));
/* 002d8d90: move s2,v0 */ set(18,cpu(2));
/* 002d8d94: move a0,s2 */ set(4,cpu(18));
/* 002d8d98: jal 0x002d1b38 */ set(31,0x002d8da0u);/* delay 002d8d9c */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8d98));
/* 002d8da0: bgtz v0,0x002d8dcc */ {int taken=((int64_t)cpu(2)>0);/* delay 002d8da4 */ set(3,sx(UINT32_C(0x00000039)));if(taken){goto L_002d8dcc;}}
/* 002d8da8: move a0,s2 */ set(4,cpu(18));
/* 002d8dac: move a1,s1 */ set(5,cpu(17));
/* 002d8db0: jal 0x002d1b38 */ set(31,0x002d8db8u);/* delay 002d8db4 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8db0));
/* 002d8db8: bne v0,zero,0x002d9584 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d8dbc */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));if(taken){goto L_002d9584;}}
/* 002d8dc0: andi v0,s0,0x1 */ set(2,cpu(16)&UINT32_C(0x00000001));
/* 002d8dc4: beq v0,zero,0x002d9584 */ {int taken=(cpu(2)==cpu(0));/* delay 002d8dc8 */ set(3,sx(UINT32_C(0x00000039)));if(taken){goto L_002d9584;}}
L_002d8dcc:;
/* 002d8dcc: li a1,0x30 */ set(5,sx(UINT32_C(0x00000030)));
/* 002d8dd0: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
/* 002d8dd4: nop  */ 
L_002d8dd8:;
/* 002d8dd8: lb v0,0x0(s5) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(21,(int32_t)UINT32_C(0x00000000))));
/* 002d8ddc: bne v0,v1,0x002d8e08 */ {int taken=(cpu(2)!=cpu(3));/* delay 002d8de0 */ set(4,byte(ea(21,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_002d8e08;}}
/* 002d8de4: lw a0,0x54(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 002d8de8: nop  */ 
/* 002d8dec: nop  */ 
/* 002d8df0: nop  */ 
/* 002d8df4: bnel s5,a0,0x002d8dd8 */ {int taken=(cpu(21)!=cpu(4));if(taken){/* delay 002d8df8 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));goto L_002d8dd8;}}
/* 002d8dfc: sb a1,0x0(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(5));
/* 002d8e00: move a0,a1 */ set(4,cpu(5));
/* 002d8e04: addiu s8,s8,0x1 */ set(30,sx((uint32_t)cpu(30)+UINT32_C(0x00000001)));
L_002d8e08:;
/* 002d8e08: addiu v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002d8e0c: sb v0,0x0(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d8e10: b 0x002d9580 */ /* delay 002d8e14 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));goto L_002d9580;
L_002d8e18:;
/* 002d8e18: ori a0,zero,0x8048 */ set(4,cpu(0)|UINT32_C(0x00008048));
/* 002d8e1c: dsll32 a0,a0,0xf */ set(4,cpu(4)<<47);
/* 002d8e20: jal 0x002d18b0 */ set(31,0x002d8e28u);/* delay 002d8e24 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d18b0),UINT32_C(0x002d8e20));
/* 002d8e28: move a1,zero */ set(5,cpu(0));
/* 002d8e2c: move a0,v0 */ set(4,cpu(2));
/* 002d8e30: move s4,v0 */ set(20,cpu(2));
/* 002d8e34: jal 0x002d1b38 */ set(31,0x002d8e3cu);/* delay 002d8e38 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d8e34));
/* 002d8e3c: beq v0,zero,0x002d9580 */ {int taken=(cpu(2)==cpu(0));/* delay 002d8e40 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));if(taken){goto L_002d9580;}}
/* 002d8e44: b 0x002d8d20 */ /* delay 002d8e48 */ goto L_002d8d20;
L_002d8e50:;
/* 002d8e50: lw v0,0x8(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000008)));
L_002d8e54:;
/* 002d8e54: lw a0,0x34(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000034)));
/* 002d8e58: lw s1,0x18(sp) */ lw(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d8e5c: slti s6,v0,0x2 */ set(22,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d8e60: lw s2,0x1c(sp) */ lw(18,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 002d8e64: sw zero,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 002d8e68: beq a0,zero,0x002d8f0c */ {int taken=(cpu(4)==cpu(0));/* delay 002d8e6c */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));if(taken){goto L_002d8f0c;}}
/* 002d8e70: beql s6,zero,0x002d8e98 */ {int taken=(cpu(22)==cpu(0));if(taken){/* delay 002d8e74 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));goto L_002d8e98;}}
/* 002d8e78: lw v0,0x40(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d8e7c: bne v0,zero,0x002d8ee4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d8e80 */ set(19,sx((uint32_t)cpu(3)+UINT32_C(0x00000433)));if(taken){goto L_002d8ee4;}}
/* 002d8e84: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002d8e88: li v0,0x36 */ set(2,sx(UINT32_C(0x00000036)));
/* 002d8e8c: b 0x002d8ee4 */ /* delay 002d8e90 */ set(19,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));goto L_002d8ee4;
L_002d8e98:;
/* 002d8e98: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 002d8e9c: addiu s0,v1,-0x1 */ set(16,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 002d8ea0: slt v0,a0,s0 */ set(2,(int64_t)cpu(4)<(int64_t)cpu(16));
/* 002d8ea4: beq v0,zero,0x002d8ecc */ {int taken=(cpu(2)==cpu(0));/* delay 002d8ea8 */ set(18,sx((uint32_t)cpu(4)-(uint32_t)cpu(16)));if(taken){goto L_002d8ecc;}}
/* 002d8eac: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 002d8eb0: move s2,zero */ set(18,cpu(0));
/* 002d8eb4: lw v1,0x3c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000003c)));
/* 002d8eb8: subu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(2)));
/* 002d8ebc: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d8ec0: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 002d8ec4: sw v0,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 002d8ec8: sw v1,0x3c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(3));
L_002d8ecc:;
/* 002d8ecc: lw s3,0x20(sp) */ lw(19,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d8ed0: bgez s3,0x002d8ee8 */ {int taken=((int64_t)cpu(19)>=0);/* delay 002d8ed4 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000038)));if(taken){goto L_002d8ee8;}}
/* 002d8ed8: lw a0,0x18(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d8edc: subu s1,a0,s3 */ set(17,sx((uint32_t)cpu(4)-(uint32_t)cpu(19)));
/* 002d8ee0: move s3,zero */ set(19,cpu(0));
L_002d8ee4:;
/* 002d8ee4: lw v0,0x38(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000038)));
L_002d8ee8:;
/* 002d8ee8: move a0,s7 */ set(4,cpu(23));
/* 002d8eec: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002d8ef0: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 002d8ef4: jal 0x002daa20 */ set(31,0x002d8efcu);/* delay 002d8ef8 */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002daa20),UINT32_C(0x002d8ef4));
/* 002d8efc: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d8f00: sw v0,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
/* 002d8f04: addu v1,v1,s3 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(19)));
/* 002d8f08: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
L_002d8f0c:;
/* 002d8f0c: blez s1,0x002d8f44 */ {int taken=((int64_t)cpu(17)<=0);/* delay 002d8f10 */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));if(taken){goto L_002d8f44;}}
/* 002d8f14: lw a0,0x38(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d8f18: blez a0,0x002d8f44 */ {int taken=((int64_t)cpu(4)<=0);/* delay 002d8f1c */ set(19,cpu(4));if(taken){goto L_002d8f44;}}
/* 002d8f20: slt v0,s1,s3 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(19));
/* 002d8f24: movn s3,s1,v0 */ if(cpu(2)!=0){set(19,cpu(17));}
/* 002d8f28: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d8f2c: subu a0,a0,s3 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(19)));
/* 002d8f30: subu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)-(uint32_t)cpu(19)));
/* 002d8f34: subu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(19)));
/* 002d8f38: sw a0,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(4));
/* 002d8f3c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d8f40: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
L_002d8f44:;
/* 002d8f44: blez v1,0x002d8fd4 */ {int taken=((int64_t)cpu(3)<=0);/* delay 002d8f48 */ set(4,cpu(23));if(taken){goto L_002d8fd4;}}
/* 002d8f4c: lw a0,0x34(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000034)));
/* 002d8f50: beq a0,zero,0x002d8fc0 */ {int taken=(cpu(4)==cpu(0));/* delay 002d8f54 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));if(taken){goto L_002d8fc0;}}
/* 002d8f58: blez s2,0x002d8f9c */ {int taken=((int64_t)cpu(18)<=0);/* delay 002d8f5c */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));if(taken){goto L_002d8f9c;}}
/* 002d8f60: lw a1,0x4c(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002d8f64: move a0,s7 */ set(4,cpu(23));
/* 002d8f68: jal 0x002dac68 */ set(31,0x002d8f70u);/* delay 002d8f6c */ set(6,cpu(18));nocturneBattlePanelRendererCall(UINT32_C(0x002dac68),UINT32_C(0x002d8f68));
/* 002d8f70: move a0,s7 */ set(4,cpu(23));
/* 002d8f74: lw a2,0x44(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d8f78: move a1,v0 */ set(5,cpu(2));
/* 002d8f7c: jal 0x002daa58 */ set(31,0x002d8f84u);/* delay 002d8f80 */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002daa58),UINT32_C(0x002d8f7c));
/* 002d8f84: move a0,s7 */ set(4,cpu(23));
/* 002d8f88: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d8f8c: jal 0x002da678 */ set(31,0x002d8f94u);/* delay 002d8f90 */ set(16,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002d8f8c));
/* 002d8f94: sw s0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(16));
/* 002d8f98: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
L_002d8f9c:;
/* 002d8f9c: subu s0,v0,s2 */ set(16,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 002d8fa0: beql s0,zero,0x002d8fd4 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 002d8fa4 */ set(4,cpu(23));goto L_002d8fd4;}}
/* 002d8fa8: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d8fac: move a2,s0 */ set(6,cpu(16));
/* 002d8fb0: jal 0x002dac68 */ set(31,0x002d8fb8u);/* delay 002d8fb4 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002dac68),UINT32_C(0x002d8fb0));
/* 002d8fb8: b 0x002d8fd0 */ /* delay 002d8fbc */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));goto L_002d8fd0;
L_002d8fc0:;
/* 002d8fc0: move a0,s7 */ set(4,cpu(23));
/* 002d8fc4: jal 0x002dac68 */ set(31,0x002d8fccu);/* delay 002d8fc8 */ lw(6,ea(29,(int32_t)UINT32_C(0x0000001c)));nocturneBattlePanelRendererCall(UINT32_C(0x002dac68),UINT32_C(0x002d8fc4));
/* 002d8fcc: sw v0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
L_002d8fd0:;
/* 002d8fd0: move a0,s7 */ set(4,cpu(23));
L_002d8fd4:;
/* 002d8fd4: jal 0x002daa20 */ set(31,0x002d8fdcu);/* delay 002d8fd8 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002daa20),UINT32_C(0x002d8fd4));
/* 002d8fdc: lw v1,0x3c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000003c)));
/* 002d8fe0: blez v1,0x002d8ffc */ {int taken=((int64_t)cpu(3)<=0);/* delay 002d8fe4 */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(2));if(taken){goto L_002d8ffc;}}
/* 002d8fe8: move a1,v0 */ set(5,cpu(2));
/* 002d8fec: move a0,s7 */ set(4,cpu(23));
/* 002d8ff0: jal 0x002dac68 */ set(31,0x002d8ff8u);/* delay 002d8ff4 */ set(6,cpu(3));nocturneBattlePanelRendererCall(UINT32_C(0x002dac68),UINT32_C(0x002d8ff0));
/* 002d8ff8: sw v0,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(2));
L_002d8ffc:;
/* 002d8ffc: beq s6,zero,0x002d9044 */ {int taken=(cpu(22)==cpu(0));/* delay 002d9000 */ set(16,cpu(0));if(taken){goto L_002d9044;}}
/* 002d9004: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d9008: dsrl v0,v0,0xc */ set(2,cpu(2)>>12);
/* 002d900c: and v0,s4,v0 */ set(2,cpu(20)&cpu(2));
/* 002d9010: bne v0,zero,0x002d9048 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9014 */ lw(3,ea(29,(int32_t)UINT32_C(0x0000003c)));if(taken){goto L_002d9048;}}
/* 002d9018: dsra32 v0,s4,0x0 */ set(2,(uint64_t)((int64_t)cpu(20)>>32));
/* 002d901c: lui v1,0x7ff0 */ set(3,sx(UINT32_C(0x7ff00000)));
/* 002d9020: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d9024: beq v0,zero,0x002d9044 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9028 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002d9044;}}
/* 002d902c: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
/* 002d9030: lw v0,0x38(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d9034: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002d9038: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d903c: sw a0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(4));
/* 002d9040: sw v0,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(2));
L_002d9044:;
/* 002d9044: lw v1,0x3c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000003c)));
L_002d9048:;
/* 002d9048: beq v1,zero,0x002d9070 */ {int taken=(cpu(3)==cpu(0));/* delay 002d904c */ lw(4,ea(29,(int32_t)UINT32_C(0x00000050)));if(taken){goto L_002d9070;}}
/* 002d9050: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002d9054: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002d9058: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002d905c: jal 0x002da8e0 */ set(31,0x002d9064u);/* delay 002d9060 */ lw(4,ea(2,(int32_t)UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002da8e0),UINT32_C(0x002d905c));
/* 002d9064: lw v1,0x38(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d9068: b 0x002d9078 */ /* delay 002d906c */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));goto L_002d9078;
L_002d9070:;
/* 002d9070: lw a0,0x38(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d9074: addiu v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
L_002d9078:;
/* 002d9078: andi s3,v0,0x1f */ set(19,cpu(2)&UINT32_C(0x0000001f));
/* 002d907c: beq s3,zero,0x002d9088 */ {int taken=(cpu(19)==cpu(0));/* delay 002d9080 */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_002d9088;}}
/* 002d9084: subu s3,v0,s3 */ set(19,sx((uint32_t)cpu(2)-(uint32_t)cpu(19)));
L_002d9088:;
/* 002d9088: slti v0,s3,0x5 */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000005));
/* 002d908c: bne v0,zero,0x002d90b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9090 */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_002d90b8;}}
/* 002d9094: lw v0,0x38(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d9098: addiu s3,s3,-0x4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xfffffffc)));
/* 002d909c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d90a0: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 002d90a4: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 002d90a8: addu v1,v1,s3 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(19)));
/* 002d90ac: sw v0,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(2));
/* 002d90b0: b 0x002d90e0 */ /* delay 002d90b4 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));goto L_002d90e0;
L_002d90b8:;
/* 002d90b8: beq v0,zero,0x002d90e4 */ {int taken=(cpu(2)==cpu(0));/* delay 002d90bc */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002d90e4;}}
/* 002d90c0: lw a0,0x38(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d90c4: addiu s3,s3,0x1c */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x0000001c)));
/* 002d90c8: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d90cc: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 002d90d0: addu a0,a0,s3 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(19)));
/* 002d90d4: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 002d90d8: sw a0,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(4));
/* 002d90dc: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
L_002d90e0:;
/* 002d90e0: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
L_002d90e4:;
/* 002d90e4: blezl v1,0x002d9104 */ {int taken=((int64_t)cpu(3)<=0);if(taken){/* delay 002d90e8 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000038)));goto L_002d9104;}}
/* 002d90ec: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d90f0: move a2,v1 */ set(6,cpu(3));
/* 002d90f4: jal 0x002dad68 */ set(31,0x002d90fcu);/* delay 002d90f8 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002dad68),UINT32_C(0x002d90f4));
/* 002d90fc: sw v0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 002d9100: lw a0,0x38(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000038)));
L_002d9104:;
/* 002d9104: blez a0,0x002d9124 */ {int taken=((int64_t)cpu(4)<=0);/* delay 002d9108 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_002d9124;}}
/* 002d910c: lw a1,0x50(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d9110: move a2,a0 */ set(6,cpu(4));
/* 002d9114: jal 0x002dad68 */ set(31,0x002d911cu);/* delay 002d9118 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002dad68),UINT32_C(0x002d9114));
/* 002d911c: sw v0,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(2));
/* 002d9120: lw v0,0x30(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000030)));
L_002d9124:;
/* 002d9124: beq v0,zero,0x002d9180 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9128 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000044)));if(taken){goto L_002d9180;}}
/* 002d912c: jal 0x002daec0 */ set(31,0x002d9134u);/* delay 002d9130 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));nocturneBattlePanelRendererCall(UINT32_C(0x002daec0),UINT32_C(0x002d912c));
/* 002d9134: bgezl v0,0x002d9184 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 002d9138 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));goto L_002d9184;}}
/* 002d913c: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d9140: move a0,s7 */ set(4,cpu(23));
/* 002d9144: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 002d9148: jal 0x002da6a8 */ set(31,0x002d9150u);/* delay 002d914c */ set(7,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002d9148));
/* 002d9150: addiu s8,s8,-0x1 */ set(30,sx((uint32_t)cpu(30)+UINT32_C(0xffffffff)));
/* 002d9154: lw v1,0x34(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000034)));
/* 002d9158: beq v1,zero,0x002d9178 */ {int taken=(cpu(3)==cpu(0));/* delay 002d915c */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));if(taken){goto L_002d9178;}}
/* 002d9160: lw a1,0x4c(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002d9164: move a0,s7 */ set(4,cpu(23));
/* 002d9168: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 002d916c: jal 0x002da6a8 */ set(31,0x002d9174u);/* delay 002d9170 */ set(7,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002d916c));
/* 002d9174: sw v0,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
L_002d9178:;
/* 002d9178: lw a0,0x28(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d917c: sw a0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(4));
L_002d9180:;
/* 002d9180: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
L_002d9184:;
/* 002d9184: bgtz v0,0x002d91f8 */ {int taken=((int64_t)cpu(2)>0);/* delay 002d9188 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000034)));if(taken){goto L_002d91f8;}}
/* 002d918c: lw v1,0x8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9190: slti v0,v1,0x3 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 002d9194: bne v0,zero,0x002d91f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9198 */ if(taken){goto L_002d91f8;}}
/* 002d919c: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d91a0: bltz a0,0x002d91d0 */ {int taken=((int64_t)cpu(4)<0);/* delay 002d91a4 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));if(taken){goto L_002d91d0;}}
/* 002d91a8: move a0,s7 */ set(4,cpu(23));
/* 002d91ac: li a2,0x5 */ set(6,sx(UINT32_C(0x00000005)));
/* 002d91b0: jal 0x002da6a8 */ set(31,0x002d91b8u);/* delay 002d91b4 */ set(7,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002d91b0));
/* 002d91b8: lw a0,0x44(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d91bc: move a1,v0 */ set(5,cpu(2));
/* 002d91c0: jal 0x002daec0 */ set(31,0x002d91c8u);/* delay 002d91c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002daec0),UINT32_C(0x002d91c0));
/* 002d91c8: bgtzl v0,0x002d91e0 */ {int taken=((int64_t)cpu(2)>0);if(taken){/* delay 002d91cc */ lw(3,ea(29,(int32_t)UINT32_C(0x00000054)));goto L_002d91e0;}}
L_002d91d0:;
/* 002d91d0: lw v0,0xc(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000000c)));
L_002d91d4:;
/* 002d91d4: b 0x002d9544 */ /* delay 002d91d8 */ set(30,~(cpu(0)|cpu(2)));goto L_002d9544;
L_002d91e0:;
/* 002d91e0: li v0,0x31 */ set(2,sx(UINT32_C(0x00000031)));
/* 002d91e4: addiu s8,s8,0x1 */ set(30,sx((uint32_t)cpu(30)+UINT32_C(0x00000001)));
/* 002d91e8: addiu s5,v1,0x1 */ set(21,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d91ec: b 0x002d9544 */ /* delay 002d91f0 */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002d9544;
L_002d91f8:;
/* 002d91f8: beq a0,zero,0x002d9464 */ {int taken=(cpu(4)==cpu(0));/* delay 002d91fc */ set(19,sx(UINT32_C(0x00000001)));if(taken){goto L_002d9464;}}
/* 002d9200: blez s1,0x002d9220 */ {int taken=((int64_t)cpu(17)<=0);/* delay 002d9204 */ lw(2,ea(29,(int32_t)UINT32_C(0x0000004c)));if(taken){goto L_002d9220;}}
/* 002d9208: lw a1,0x4c(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002d920c: move a2,s1 */ set(6,cpu(17));
/* 002d9210: jal 0x002dad68 */ set(31,0x002d9218u);/* delay 002d9214 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002dad68),UINT32_C(0x002d9210));
/* 002d9218: sw v0,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
/* 002d921c: lw v0,0x4c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000004c)));
L_002d9220:;
/* 002d9220: beq s0,zero,0x002d9268 */ {int taken=(cpu(16)==cpu(0));/* delay 002d9224 */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(2));if(taken){goto L_002d9268;}}
/* 002d9228: lw a1,0x4(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 002d922c: jal 0x002da5d0 */ set(31,0x002d9234u);/* delay 002d9230 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002d922c));
/* 002d9234: lw v1,0x48(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d9238: addiu a0,v0,0xc */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x0000000c)));
/* 002d923c: sw v0,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
/* 002d9240: addiu a1,v1,0xc */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0x0000000c)));
/* 002d9244: lw a2,0x10(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 002d9248: sll a2,a2,0x2 */ set(6,sx((uint32_t)cpu(6)<<2));
/* 002d924c: jal 0x002d43a4 */ set(31,0x002d9254u);/* delay 002d9250 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000008)));nocturneBattlePanelRendererCall(UINT32_C(0x002d43a4),UINT32_C(0x002d924c));
/* 002d9254: move a0,s7 */ set(4,cpu(23));
/* 002d9258: lw a1,0x4c(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002d925c: jal 0x002dad68 */ set(31,0x002d9264u);/* delay 002d9260 */ set(6,sx(UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002dad68),UINT32_C(0x002d925c));
/* 002d9264: sw v0,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
L_002d9268:;
/* 002d9268: dsll32 v0,s4,0x0 */ set(2,cpu(20)<<32);
/* 002d926c: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d9270: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
/* 002d9274: b 0x002d92f8 */ /* delay 002d9278 */ set(22,cpu(2)&UINT32_C(0x00000001));goto L_002d92f8;
L_002d9280:;
/* 002d9280: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d9284: move a0,s7 */ set(4,cpu(23));
/* 002d9288: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 002d928c: jal 0x002da6a8 */ set(31,0x002d9294u);/* delay 002d9290 */ set(7,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002d928c));
/* 002d9294: sw v0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 002d9298: lw a0,0x48(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d929c: lw v0,0x4c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002d92a0: bne a0,v0,0x002d92c8 */ {int taken=(cpu(4)!=cpu(2));/* delay 002d92a4 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000048)));if(taken){goto L_002d92c8;}}
/* 002d92a8: move a1,v0 */ set(5,cpu(2));
/* 002d92ac: move a0,s7 */ set(4,cpu(23));
/* 002d92b0: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 002d92b4: jal 0x002da6a8 */ set(31,0x002d92bcu);/* delay 002d92b8 */ set(7,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002d92b4));
/* 002d92bc: sw v0,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
/* 002d92c0: b 0x002d92f4 */ /* delay 002d92c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(2));goto L_002d92f4;
L_002d92c8:;
/* 002d92c8: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 002d92cc: move a3,zero */ set(7,cpu(0));
/* 002d92d0: jal 0x002da6a8 */ set(31,0x002d92d8u);/* delay 002d92d4 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002d92d0));
/* 002d92d8: move a0,s7 */ set(4,cpu(23));
/* 002d92dc: lw a1,0x4c(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002d92e0: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 002d92e4: move a3,zero */ set(7,cpu(0));
/* 002d92e8: jal 0x002da6a8 */ set(31,0x002d92f0u);/* delay 002d92ec */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002d92e8));
/* 002d92f0: sw v0,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
L_002d92f4:;
/* 002d92f4: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
L_002d92f8:;
/* 002d92f8: lw a0,0x44(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d92fc: jal 0x002d8148 */ set(31,0x002d9304u);/* delay 002d9300 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));nocturneBattlePanelRendererCall(UINT32_C(0x002d8148),UINT32_C(0x002d92fc));
/* 002d9304: lw a0,0x44(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d9308: addiu s4,v0,0x30 */ set(20,sx((uint32_t)cpu(2)+UINT32_C(0x00000030)));
/* 002d930c: jal 0x002daec0 */ set(31,0x002d9314u);/* delay 002d9310 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000048)));nocturneBattlePanelRendererCall(UINT32_C(0x002daec0),UINT32_C(0x002d930c));
/* 002d9314: move a0,s7 */ set(4,cpu(23));
/* 002d9318: lw a1,0x50(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d931c: move s0,v0 */ set(16,cpu(2));
/* 002d9320: jal 0x002daf28 */ set(31,0x002d9328u);/* delay 002d9324 */ lw(6,ea(29,(int32_t)UINT32_C(0x0000004c)));nocturneBattlePanelRendererCall(UINT32_C(0x002daf28),UINT32_C(0x002d9320));
/* 002d9328: move s2,v0 */ set(18,cpu(2));
/* 002d932c: lw v0,0xc(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 002d9330: bne v0,zero,0x002d9348 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9334 */ set(17,sx(UINT32_C(0x00000001)));if(taken){goto L_002d9348;}}
/* 002d9338: lw a0,0x44(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d933c: jal 0x002daec0 */ set(31,0x002d9344u);/* delay 002d9340 */ set(5,cpu(18));nocturneBattlePanelRendererCall(UINT32_C(0x002daec0),UINT32_C(0x002d933c));
/* 002d9344: move s1,v0 */ set(17,cpu(2));
L_002d9348:;
/* 002d9348: move a1,s2 */ set(5,cpu(18));
/* 002d934c: jal 0x002da678 */ set(31,0x002d9354u);/* delay 002d9350 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002d934c));
/* 002d9354: bne s1,zero,0x002d9380 */ {int taken=(cpu(17)!=cpu(0));/* delay 002d9358 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002d9380;}}
/* 002d935c: bne v1,zero,0x002d9380 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d9360 */ if(taken){goto L_002d9380;}}
/* 002d9364: bne s6,zero,0x002d9380 */ {int taken=(cpu(22)!=cpu(0));/* delay 002d9368 */ set(4,sx(UINT32_C(0x00000039)));if(taken){goto L_002d9380;}}
/* 002d936c: beq s4,a0,0x002d9414 */ {int taken=(cpu(20)==cpu(4));/* delay 002d9370 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(16));if(taken){goto L_002d9414;}}
/* 002d9374: addu s4,s4,v0 */ set(20,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 002d9378: b 0x002d9540 */ /* delay 002d937c */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(20));goto L_002d9540;
L_002d9380:;
/* 002d9380: bltz s0,0x002d93a0 */ {int taken=((int64_t)cpu(16)<0);/* delay 002d9384 */ if(taken){goto L_002d93a0;}}
/* 002d9388: bne s0,zero,0x002d9400 */ {int taken=(cpu(16)!=cpu(0));/* delay 002d938c */ lw(2,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002d9400;}}
/* 002d9390: bne v0,zero,0x002d9400 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9394 */ if(taken){goto L_002d9400;}}
/* 002d9398: bne s6,zero,0x002d9400 */ {int taken=(cpu(22)!=cpu(0));/* delay 002d939c */ if(taken){goto L_002d9400;}}
L_002d93a0:;
/* 002d93a0: blezl s1,0x002d9540 */ {int taken=((int64_t)cpu(17)<=0);if(taken){/* delay 002d93a4 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(20));goto L_002d9540;}}
/* 002d93a8: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d93ac: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 002d93b0: jal 0x002dad68 */ set(31,0x002d93b8u);/* delay 002d93b4 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002dad68),UINT32_C(0x002d93b0));
/* 002d93b8: lw a1,0x50(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d93bc: move a0,v0 */ set(4,cpu(2));
/* 002d93c0: jal 0x002daec0 */ set(31,0x002d93c8u);/* delay 002d93c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002daec0),UINT32_C(0x002d93c0));
/* 002d93c8: move s1,v0 */ set(17,cpu(2));
/* 002d93cc: bgtzl s1,0x002d93ec */ {int taken=((int64_t)cpu(17)>0);if(taken){/* delay 002d93d0 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));goto L_002d93ec;}}
/* 002d93d4: bnel s1,zero,0x002d9540 */ {int taken=(cpu(17)!=cpu(0));if(taken){/* delay 002d93d8 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(20));goto L_002d9540;}}
/* 002d93dc: andi v0,s4,0x1 */ set(2,cpu(20)&UINT32_C(0x00000001));
/* 002d93e0: beql v0,zero,0x002d9540 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d93e4 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(20));goto L_002d9540;}}
/* 002d93e8: addiu s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
L_002d93ec:;
/* 002d93ec: li v0,0x3a */ set(2,sx(UINT32_C(0x0000003a)));
/* 002d93f0: beql s4,v0,0x002d9418 */ {int taken=(cpu(20)==cpu(2));if(taken){/* delay 002d93f4 */ set(4,sx(UINT32_C(0x00000039)));goto L_002d9418;}}
/* 002d93f8: b 0x002d9540 */ /* delay 002d93fc */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(20));goto L_002d9540;
L_002d9400:;
/* 002d9400: blezl s1,0x002d9430 */ {int taken=((int64_t)cpu(17)<=0);if(taken){/* delay 002d9404 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(20));goto L_002d9430;}}
/* 002d9408: li v1,0x39 */ set(3,sx(UINT32_C(0x00000039)));
/* 002d940c: bne s4,v1,0x002d9428 */ {int taken=(cpu(20)!=cpu(3));/* delay 002d9410 */ set(2,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));if(taken){goto L_002d9428;}}
L_002d9414:;
/* 002d9414: li a0,0x39 */ set(4,sx(UINT32_C(0x00000039)));
L_002d9418:;
/* 002d9418: sb a0,0x0(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 002d941c: b 0x002d94c8 */ /* delay 002d9420 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));goto L_002d94c8;
L_002d9428:;
/* 002d9428: b 0x002d9540 */ /* delay 002d942c */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002d9540;
L_002d9430:;
/* 002d9430: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d9434: bne s3,v0,0x002d9280 */ {int taken=(cpu(19)!=cpu(2));/* delay 002d9438 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));if(taken){goto L_002d9280;}}
/* 002d943c: b 0x002d948c */ /* delay 002d9440 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));goto L_002d948c;
L_002d9448:;
/* 002d9448: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d944c: move a0,s7 */ set(4,cpu(23));
/* 002d9450: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 002d9454: jal 0x002da6a8 */ set(31,0x002d945cu);/* delay 002d9458 */ set(7,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002d9454));
/* 002d945c: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002d9460: sw v0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
L_002d9464:;
/* 002d9464: lw a0,0x44(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002d9468: jal 0x002d8148 */ set(31,0x002d9470u);/* delay 002d946c */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));nocturneBattlePanelRendererCall(UINT32_C(0x002d8148),UINT32_C(0x002d9468));
/* 002d9470: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d9474: addiu s4,v0,0x30 */ set(20,sx((uint32_t)cpu(2)+UINT32_C(0x00000030)));
/* 002d9478: sb s4,0x0(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(20));
/* 002d947c: slt v1,s3,a0 */ set(3,(int64_t)cpu(19)<(int64_t)cpu(4));
/* 002d9480: bne v1,zero,0x002d9448 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d9484 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));if(taken){goto L_002d9448;}}
/* 002d9488: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
L_002d948c:;
/* 002d948c: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 002d9490: jal 0x002dad68 */ set(31,0x002d9498u);/* delay 002d9494 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002dad68),UINT32_C(0x002d9490));
/* 002d9498: lw a1,0x50(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d949c: move a0,v0 */ set(4,cpu(2));
/* 002d94a0: jal 0x002daec0 */ set(31,0x002d94a8u);/* delay 002d94a4 */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002daec0),UINT32_C(0x002d94a0));
/* 002d94a8: move s0,v0 */ set(16,cpu(2));
/* 002d94ac: bgtzl s0,0x002d94cc */ {int taken=((int64_t)cpu(16)>0);if(taken){/* delay 002d94b0 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));goto L_002d94cc;}}
/* 002d94b4: bne s0,zero,0x002d9520 */ {int taken=(cpu(16)!=cpu(0));/* delay 002d94b8 */ set(3,sx(UINT32_C(0x00000030)));if(taken){goto L_002d9520;}}
/* 002d94bc: andi v0,s4,0x1 */ set(2,cpu(20)&UINT32_C(0x00000001));
/* 002d94c0: beql v0,zero,0x002d9524 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d94c4 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));goto L_002d9524;}}
L_002d94c8:;
/* 002d94c8: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
L_002d94cc:;
/* 002d94cc: b 0x002d94e8 */ /* delay 002d94d0 */ set(3,sx(UINT32_C(0x00000039)));goto L_002d94e8;
L_002d94d8:;
/* 002d94d8: lw v0,0x54(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 002d94dc: beql s5,v0,0x002d9508 */ {int taken=(cpu(21)==cpu(2));if(taken){/* delay 002d94e0 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000054)));goto L_002d9508;}}
/* 002d94e4: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
L_002d94e8:;
/* 002d94e8: lb v0,0x0(s5) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(21,(int32_t)UINT32_C(0x00000000))));
/* 002d94ec: nop  */ 
/* 002d94f0: nop  */ 
/* 002d94f4: beq v0,v1,0x002d94d8 */ {int taken=(cpu(2)==cpu(3));/* delay 002d94f8 */ set(4,byte(ea(21,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_002d94d8;}}
/* 002d94fc: addiu v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002d9500: b 0x002d9540 */ /* delay 002d9504 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002d9540;
L_002d9508:;
/* 002d9508: li v0,0x31 */ set(2,sx(UINT32_C(0x00000031)));
/* 002d950c: addiu s8,s8,0x1 */ set(30,sx((uint32_t)cpu(30)+UINT32_C(0x00000001)));
/* 002d9510: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d9514: b 0x002d9544 */ /* delay 002d9518 */ set(21,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));goto L_002d9544;
L_002d9520:;
/* 002d9520: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
L_002d9524:;
/* 002d9524: lb v0,0x0(s5) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(21,(int32_t)UINT32_C(0x00000000))));
/* 002d9528: nop  */ 
/* 002d952c: nop  */ 
/* 002d9530: nop  */ 
/* 002d9534: nop  */ 
/* 002d9538: beql v0,v1,0x002d9524 */ {int taken=(cpu(2)==cpu(3));if(taken){/* delay 002d953c */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));goto L_002d9524;}}
L_002d9540:;
/* 002d9540: addiu s5,s5,0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));
L_002d9544:;
/* 002d9544: lw a1,0x50(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d9548: jal 0x002da678 */ set(31,0x002d9550u);/* delay 002d954c */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002d9548));
/* 002d9550: lw a0,0x4c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002d9554: beq a0,zero,0x002d9580 */ {int taken=(cpu(4)==cpu(0));/* delay 002d9558 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000048)));if(taken){goto L_002d9580;}}
/* 002d955c: beq v0,zero,0x002d9578 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9560 */ lw(5,ea(29,(int32_t)UINT32_C(0x0000004c)));if(taken){goto L_002d9578;}}
/* 002d9564: beq v0,a0,0x002d9574 */ {int taken=(cpu(2)==cpu(4));/* delay 002d9568 */ set(5,cpu(2));if(taken){goto L_002d9574;}}
/* 002d956c: jal 0x002da678 */ set(31,0x002d9574u);/* delay 002d9570 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002d956c));
L_002d9574:;
/* 002d9574: lw a1,0x4c(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x0000004c)));
L_002d9578:;
/* 002d9578: jal 0x002da678 */ set(31,0x002d9580u);/* delay 002d957c */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002d9578));
L_002d9580:;
/* 002d9580: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
L_002d9584:;
/* 002d9584: jal 0x002da678 */ set(31,0x002d958cu);/* delay 002d9588 */ set(4,cpu(23));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002d9584));
/* 002d958c: sb zero,0x0(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 002d9590: addiu v0,s8,0x1 */ set(2,sx((uint32_t)cpu(30)+UINT32_C(0x00000001)));
/* 002d9594: lw v1,0x10(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d9598: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d959c: lw a0,0x14(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d95a0: bnel a0,zero,0x002d95a8 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 002d95a4 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));goto L_002d95a8;}}
L_002d95a8:;
/* 002d95a8: lw v0,0x54(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000054)));
L_002d95ac:;
/* 002d95ac: ld s0,0x60(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d95b0: ld s1,0x68(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002d95b4: ld s2,0x70(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d95b8: ld s3,0x78(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d95bc: ld s4,0x80(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002d95c0: ld s5,0x88(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002d95c4: ld s6,0x90(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002d95c8: ld s7,0x98(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002d95cc: ld s8,0xa0(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002d95d0: ld ra,0xa8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002d95d4: jr ra */ {uint64_t target=cpu(31);/* delay 002d95d8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000b0)));checkReturn(target,incoming);return;}
}
static void body_002d9998(void){
nocturneEffectAxisNoteEntry(0x002d9998u);
uint64_t incoming=cpu(31);
/* 002d9998: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002d999c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d99a0: move s0,a1 */ set(16,cpu(5));
/* 002d99a4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d99a8: move s1,a0 */ set(17,cpu(4));
/* 002d99ac: beq s0,zero,0x002d9c78 */ {int taken=(cpu(16)==cpu(0));/* delay 002d99b0 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002d9c78;}}
/* 002d99b4: jal 0x002d4618 */ set(31,0x002d99bcu);/* delay 002d99b8 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d4618),UINT32_C(0x002d99b4));
/* 002d99bc: addiu t1,s0,-0x8 */ set(9,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff8)));
/* 002d99c0: lw a2,0x4(t1) */ lw(6,ea(9,(int32_t)UINT32_C(0x00000004)));
/* 002d99c4: li v0,-0x2 */ set(2,sx(UINT32_C(0xfffffffe)));
/* 002d99c8: lui t4,0x53 */ set(12,sx(UINT32_C(0x00530000)));
/* 002d99cc: li a0,-0x4 */ set(4,sx(UINT32_C(0xfffffffc)));
/* 002d99d0: and t0,a2,v0 */ set(8,cpu(6)&cpu(2));
/* 002d99d4: addiu t2,t4,-0x41d0 */ set(10,sx((uint32_t)cpu(12)+UINT32_C(0xffffbe30)));
/* 002d99d8: addu a1,t1,t0 */ set(5,sx((uint32_t)cpu(9)+(uint32_t)cpu(8)));
/* 002d99dc: lw v1,0x8(t2) */ lw(3,ea(10,(int32_t)UINT32_C(0x00000008)));
/* 002d99e0: lw v0,0x4(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d99e4: bne a1,v1,0x002d9a60 */ {int taken=(cpu(5)!=cpu(3));/* delay 002d99e8 */ set(4,cpu(2)&cpu(4));if(taken){goto L_002d9a60;}}
/* 002d99ec: andi v0,a2,0x1 */ set(2,cpu(6)&UINT32_C(0x00000001));
/* 002d99f0: bne v0,zero,0x002d9a14 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d99f4 */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(4)));if(taken){goto L_002d9a14;}}
/* 002d99f8: lw v1,0x0(t1) */ lw(3,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 002d99fc: subu t1,t1,v1 */ set(9,sx((uint32_t)cpu(9)-(uint32_t)cpu(3)));
/* 002d9a00: addu t0,t0,v1 */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(3)));
/* 002d9a04: lw a3,0xc(t1) */ lw(7,ea(9,(int32_t)UINT32_C(0x0000000c)));
/* 002d9a08: lw a2,0x8(t1) */ lw(6,ea(9,(int32_t)UINT32_C(0x00000008)));
/* 002d9a0c: sw a3,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
/* 002d9a10: sw a2,0x8(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
L_002d9a14:;
/* 002d9a14: ori v1,t0,0x1 */ set(3,cpu(8)|UINT32_C(0x00000001));
/* 002d9a18: sw t1,0x8(t2) */ sw(ea(10,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(9));
/* 002d9a1c: sw v1,0x4(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d9a20: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 002d9a24: dsll32 v0,t0,0x0 */ set(2,cpu(8)<<32);
/* 002d9a28: ld v1,-0x3dc8(a0) */ restore(3,ea(4,(int32_t)UINT32_C(0xffffc238)));
/* 002d9a2c: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002d9a30: sltu v0,v0,v1 */ set(2,cpu(2)<cpu(3));
/* 002d9a34: bne v0,zero,0x002d9a4c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9a38 */ set(4,cpu(17));if(taken){goto L_002d9a4c;}}
/* 002d9a3c: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d9a40: jal 0x002d9c90 */ set(31,0x002d9a48u);/* delay 002d9a44 */ lw(5,ea(2,(int32_t)UINT32_C(0xffffc240)));nocturneBattlePanelRendererCall(UINT32_C(0x002d9c90),UINT32_C(0x002d9a40));
/* 002d9a48: move a0,s1 */ set(4,cpu(17));
L_002d9a4c:;
/* 002d9a4c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9a50: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9a54: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d9a58: j 0x002d4698 */ checkReturn(cpu(31),incoming);/* delay 002d9a5c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));nocturneBattlePanelRendererCall(UINT32_C(0x002d4698),UINT32_C(0x002d9a58));return;
L_002d9a60:;
/* 002d9a60: andi v0,a2,0x1 */ set(2,cpu(6)&UINT32_C(0x00000001));
/* 002d9a64: sw a0,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002d9a68: bne v0,zero,0x002d9aa4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9a6c */ set(11,cpu(0));if(taken){goto L_002d9aa4;}}
/* 002d9a70: lw v1,0x0(t1) */ lw(3,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 002d9a74: addiu v0,t2,0x8 */ set(2,sx((uint32_t)cpu(10)+UINT32_C(0x00000008)));
/* 002d9a78: subu t1,t1,v1 */ set(9,sx((uint32_t)cpu(9)-(uint32_t)cpu(3)));
/* 002d9a7c: addu t0,t0,v1 */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(3)));
/* 002d9a80: lw v1,0x8(t1) */ lw(3,ea(9,(int32_t)UINT32_C(0x00000008)));
/* 002d9a84: bnel v1,v0,0x002d9a98 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 002d9a88 */ lw(7,ea(9,(int32_t)UINT32_C(0x0000000c)));goto L_002d9a98;}}
/* 002d9a8c: b 0x002d9aa4 */ /* delay 002d9a90 */ set(11,sx(UINT32_C(0x00000001)));goto L_002d9aa4;
L_002d9a98:;
/* 002d9a98: move a2,v1 */ set(6,cpu(3));
/* 002d9a9c: sw a3,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
/* 002d9aa0: sw a2,0x8(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
L_002d9aa4:;
/* 002d9aa4: addu v1,a1,a0 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 002d9aa8: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002d9aac: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002d9ab0: bne v0,zero,0x002d9b08 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9ab4 */ set(2,cpu(8)|UINT32_C(0x00000001));if(taken){goto L_002d9b08;}}
/* 002d9ab8: bne t3,zero,0x002d9af0 */ {int taken=(cpu(11)!=cpu(0));/* delay 002d9abc */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(4)));if(taken){goto L_002d9af0;}}
/* 002d9ac0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d9ac4: lw v1,0x8(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 002d9ac8: addiu v0,v0,-0x41c0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffbe40)));
/* 002d9acc: addiu v0,v0,-0x8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffff8)));
/* 002d9ad0: bnel v1,v0,0x002d9af8 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 002d9ad4 */ lw(7,ea(5,(int32_t)UINT32_C(0x0000000c)));goto L_002d9af8;}}
/* 002d9ad8: sw t1,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(9));
/* 002d9adc: li t3,0x1 */ set(11,sx(UINT32_C(0x00000001)));
/* 002d9ae0: sw t1,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(9));
/* 002d9ae4: sw v1,0x8(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002d9ae8: b 0x002d9b04 */ /* delay 002d9aec */ sw(ea(9,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));goto L_002d9b04;
L_002d9af0:;
/* 002d9af0: lw v1,0x8(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 002d9af4: lw a3,0xc(a1) */ lw(7,ea(5,(int32_t)UINT32_C(0x0000000c)));
L_002d9af8:;
/* 002d9af8: move a2,v1 */ set(6,cpu(3));
/* 002d9afc: sw a3,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
/* 002d9b00: sw a2,0x8(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
L_002d9b04:;
/* 002d9b04: ori v0,t0,0x1 */ set(2,cpu(8)|UINT32_C(0x00000001));
L_002d9b08:;
/* 002d9b08: addu v1,t1,t0 */ set(3,sx((uint32_t)cpu(9)+(uint32_t)cpu(8)));
/* 002d9b0c: sw v0,0x4(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d9b10: bne t3,zero,0x002d9c60 */ {int taken=(cpu(11)!=cpu(0));/* delay 002d9b14 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(8));if(taken){goto L_002d9c60;}}
/* 002d9b18: sltiu v0,t0,0x200 */ set(2,cpu(8)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000200));
/* 002d9b1c: beql v0,zero,0x002d9b68 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d9b20 */ set(3,sx((uint32_t)cpu(8)>>9));goto L_002d9b68;}}
/* 002d9b24: srl a1,t0,0x3 */ set(5,sx((uint32_t)cpu(8)>>3));
/* 002d9b28: addiu a0,t4,-0x41d0 */ set(4,sx((uint32_t)cpu(12)+UINT32_C(0xffffbe30)));
/* 002d9b2c: sll v1,a1,0x3 */ set(3,sx((uint32_t)cpu(5)<<3));
/* 002d9b30: srl a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)>>2));
/* 002d9b34: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d9b38: addu a3,v1,a0 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002d9b3c: dsllv v0,v0,a1 */ set(2,cpu(2)<<(cpu(5)&63u));
/* 002d9b40: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 002d9b44: lw a2,0x8(a3) */ lw(6,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 002d9b48: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d9b4c: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d9b50: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002d9b54: sw a3,0xc(t1) */ sw(ea(9,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
/* 002d9b58: sw a2,0x8(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 002d9b5c: b 0x002d9c58 */ /* delay 002d9b60 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));goto L_002d9c58;
L_002d9b68:;
/* 002d9b68: beq v1,zero,0x002d9bd0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d9b6c */ set(5,sx((uint32_t)cpu(8)>>3));if(taken){goto L_002d9bd0;}}
/* 002d9b70: sltiu v0,v1,0x5 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 002d9b74: beq v0,zero,0x002d9b88 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9b78 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000015));if(taken){goto L_002d9b88;}}
/* 002d9b7c: srl v0,t0,0x6 */ set(2,sx((uint32_t)cpu(8)>>6));
/* 002d9b80: b 0x002d9bd0 */ /* delay 002d9b84 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000038)));goto L_002d9bd0;
L_002d9b88:;
/* 002d9b88: bne v0,zero,0x002d9bd0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9b8c */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0x0000005b)));if(taken){goto L_002d9bd0;}}
/* 002d9b90: sltiu v0,v1,0x55 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000055));
/* 002d9b94: beq v0,zero,0x002d9ba8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9b98 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000155));if(taken){goto L_002d9ba8;}}
/* 002d9b9c: srl v0,t0,0xc */ set(2,sx((uint32_t)cpu(8)>>12));
/* 002d9ba0: b 0x002d9bd0 */ /* delay 002d9ba4 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x0000006e)));goto L_002d9bd0;
L_002d9ba8:;
/* 002d9ba8: beq v0,zero,0x002d9bc0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9bac */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000555));if(taken){goto L_002d9bc0;}}
/* 002d9bb0: srl v0,t0,0xf */ set(2,sx((uint32_t)cpu(8)>>15));
/* 002d9bb4: b 0x002d9bd0 */ /* delay 002d9bb8 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000077)));goto L_002d9bd0;
L_002d9bc0:;
/* 002d9bc0: beql v0,zero,0x002d9bd0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d9bc4 */ set(5,sx(UINT32_C(0x0000007e)));goto L_002d9bd0;}}
/* 002d9bc8: srl v0,t0,0x12 */ set(2,sx((uint32_t)cpu(8)>>18));
/* 002d9bcc: addiu a1,v0,0x7c */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x0000007c)));
L_002d9bd0:;
/* 002d9bd0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d9bd4: sll v1,a1,0x3 */ set(3,sx((uint32_t)cpu(5)<<3));
/* 002d9bd8: addiu v0,v0,-0x41c8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffbe38)));
/* 002d9bdc: addiu t2,v0,-0x8 */ set(10,sx((uint32_t)cpu(2)+UINT32_C(0xfffffff8)));
/* 002d9be0: addu a3,v1,t2 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(10)));
/* 002d9be4: lw a2,0x8(a3) */ lw(6,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 002d9be8: bnel a2,a3,0x002d9c20 */ {int taken=(cpu(6)!=cpu(7));if(taken){/* delay 002d9bec */ lw(2,ea(6,(int32_t)UINT32_C(0x00000004)));goto L_002d9c20;}}
/* 002d9bf0: addiu a0,a1,0x3 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000003)));
/* 002d9bf4: slti v1,a1,0x0 */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 002d9bf8: movn a1,a0,v1 */ if(cpu(3)!=0){set(5,cpu(4));}
/* 002d9bfc: lw v1,0x4(t2) */ lw(3,ea(10,(int32_t)UINT32_C(0x00000004)));
/* 002d9c00: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d9c04: sra a0,a1,0x2 */ set(4,sx((uint32_t)((int32_t)cpu(5)>>2)));
/* 002d9c08: dsllv v0,v0,a0 */ set(2,cpu(2)<<(cpu(4)&63u));
/* 002d9c0c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d9c10: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d9c14: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002d9c18: b 0x002d9c50 */ /* delay 002d9c1c */ sw(ea(10,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));goto L_002d9c50;
L_002d9c20:;
/* 002d9c20: b 0x002d9c34 */ /* delay 002d9c24 */ set(3,sx(UINT32_C(0xfffffffc)));goto L_002d9c34;
L_002d9c28:;
/* 002d9c28: beql a2,a3,0x002d9c50 */ {int taken=(cpu(6)==cpu(7));if(taken){/* delay 002d9c2c */ lw(7,ea(6,(int32_t)UINT32_C(0x0000000c)));goto L_002d9c50;}}
/* 002d9c30: lw v0,0x4(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000004)));
L_002d9c34:;
/* 002d9c34: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d9c38: sltu v0,t0,v0 */ set(2,cpu(8)<cpu(2));
/* 002d9c3c: nop  */ 
/* 002d9c40: nop  */ 
/* 002d9c44: bnel v0,zero,0x002d9c28 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d9c48 */ lw(6,ea(6,(int32_t)UINT32_C(0x00000008)));goto L_002d9c28;}}
/* 002d9c4c: lw a3,0xc(a2) */ lw(7,ea(6,(int32_t)UINT32_C(0x0000000c)));
L_002d9c50:;
/* 002d9c50: sw a3,0xc(t1) */ sw(ea(9,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
/* 002d9c54: sw a2,0x8(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
L_002d9c58:;
/* 002d9c58: sw t1,0x8(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(9));
/* 002d9c5c: sw t1,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(9));
L_002d9c60:;
/* 002d9c60: move a0,s1 */ set(4,cpu(17));
/* 002d9c64: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9c68: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9c6c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d9c70: j 0x002d4698 */ checkReturn(cpu(31),incoming);/* delay 002d9c74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));nocturneBattlePanelRendererCall(UINT32_C(0x002d4698),UINT32_C(0x002d9c70));return;
L_002d9c78:;
/* 002d9c78: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9c7c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9c80: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d9c84: jr ra */ {uint64_t target=cpu(31);/* delay 002d9c88 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002d9c90(void){
nocturneEffectAxisNoteEntry(0x002d9c90u);
uint64_t incoming=cpu(31);
/* 002d9c90: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002d9c94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9c98: move s0,a1 */ set(16,cpu(5));
/* 002d9c9c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9ca0: move s1,a0 */ set(17,cpu(4));
/* 002d9ca4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d9ca8: dsll32 s0,s0,0x0 */ set(16,cpu(16)<<32);
/* 002d9cac: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d9cb0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d9cb4: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d9cb8: jal 0x002d4618 */ set(31,0x002d9cc0u);/* delay 002d9cbc */ set(16,cpu(16)>>32);nocturneBattlePanelRendererCall(UINT32_C(0x002d4618),UINT32_C(0x002d9cb8));
/* 002d9cc0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d9cc4: li a2,-0x4 */ set(6,sx(UINT32_C(0xfffffffc)));
/* 002d9cc8: addiu s4,v0,-0x41d0 */ set(20,sx((uint32_t)cpu(2)+UINT32_C(0xffffbe30)));
/* 002d9ccc: move a0,s1 */ set(4,cpu(17));
/* 002d9cd0: lw v1,0x8(s4) */ lw(3,ea(20,(int32_t)UINT32_C(0x00000008)));
/* 002d9cd4: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002d9cd8: and v0,v0,a2 */ set(2,cpu(2)&cpu(6));
/* 002d9cdc: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d9ce0: dsrl32 s2,v0,0x0 */ set(18,cpu(2)>>32);
/* 002d9ce4: dsubu s0,s2,s0 */ set(16,cpu(18)-cpu(16));
/* 002d9ce8: daddiu s0,s0,0xfef */ set(16,cpu(16)+(uint64_t)INT64_C(4079));
/* 002d9cec: dsrl s0,s0,0xc */ set(16,cpu(16)>>12);
/* 002d9cf0: daddiu s0,s0,-0x1 */ set(16,cpu(16)+(uint64_t)INT64_C(-1));
/* 002d9cf4: dsll s0,s0,0xc */ set(16,cpu(16)<<12);
/* 002d9cf8: slti v0,s0,0x1000 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00001000));
/* 002d9cfc: bne v0,zero,0x002d9d98 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9d00 */ set(5,cpu(0));if(taken){goto L_002d9d98;}}
/* 002d9d04: jal 0x002d5250 */ set(31,0x002d9d0cu);/* delay 002d9d08 */ set(4,cpu(17));nocturneBattlePanelRendererCall(UINT32_C(0x002d5250),UINT32_C(0x002d9d04));
/* 002d9d0c: lw v1,0x8(s4) */ lw(3,ea(20,(int32_t)UINT32_C(0x00000008)));
/* 002d9d10: dsll32 a1,s2,0x0 */ set(5,cpu(18)<<32);
/* 002d9d14: dsra32 a1,a1,0x0 */ set(5,(uint64_t)((int64_t)cpu(5)>>32));
/* 002d9d18: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 002d9d1c: bne v0,v1,0x002d9d98 */ {int taken=(cpu(2)!=cpu(3));/* delay 002d9d20 */ set(4,cpu(17));if(taken){goto L_002d9d98;}}
/* 002d9d24: dsll32 s3,s0,0x0 */ set(19,cpu(16)<<32);
/* 002d9d28: dsra32 s3,s3,0x0 */ set(19,(uint64_t)((int64_t)cpu(19)>>32));
/* 002d9d2c: move a0,s1 */ set(4,cpu(17));
/* 002d9d30: jal 0x002d5250 */ set(31,0x002d9d38u);/* delay 002d9d34 */ set(5,sx((uint32_t)cpu(0)-(uint32_t)cpu(19)));nocturneBattlePanelRendererCall(UINT32_C(0x002d5250),UINT32_C(0x002d9d30));
/* 002d9d38: move a0,s1 */ set(4,cpu(17));
/* 002d9d3c: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002d9d40: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 002d9d44: move a1,zero */ set(5,cpu(0));
/* 002d9d48: bne v0,a2,0x002d9da8 */ {int taken=(cpu(2)!=cpu(6));/* delay 002d9d4c */ set(7,sx((uint32_t)cpu(3)+UINT32_C(0xffffc260)));if(taken){goto L_002d9da8;}}
/* 002d9d50: jal 0x002d5250 */ set(31,0x002d9d58u);/* delay 002d9d54 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d5250),UINT32_C(0x002d9d50));
/* 002d9d58: lw a2,0x8(s4) */ lw(6,ea(20,(int32_t)UINT32_C(0x00000008)));
/* 002d9d5c: move a3,v0 */ set(7,cpu(2));
/* 002d9d60: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d9d64: subu s2,a3,a2 */ set(18,sx((uint32_t)cpu(7)-(uint32_t)cpu(6)));
/* 002d9d68: or v0,s2,v0 */ set(2,cpu(18)|cpu(2));
/* 002d9d6c: slti v1,s2,0x10 */ set(3,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d9d70: dsll32 a1,v0,0x0 */ set(5,cpu(2)<<32);
/* 002d9d74: dsra32 a1,a1,0x0 */ set(5,(uint64_t)((int64_t)cpu(5)>>32));
/* 002d9d78: bne v1,zero,0x002d9d98 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d9d7c */ set(4,cpu(17));if(taken){goto L_002d9d98;}}
/* 002d9d80: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d9d84: lw v1,-0x3db8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0xffffc248)));
/* 002d9d88: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d9d8c: subu v1,a3,v1 */ set(3,sx((uint32_t)cpu(7)-(uint32_t)cpu(3)));
/* 002d9d90: sw v1,-0x3da0(v0) */ sw(ea(2,(int32_t)UINT32_C(0xffffc260)),(uint32_t)cpu(3));
/* 002d9d94: sw a1,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
L_002d9d98:;
/* 002d9d98: jal 0x002d4698 */ set(31,0x002d9da0u);/* delay 002d9d9c */ nocturneBattlePanelRendererCall(UINT32_C(0x002d4698),UINT32_C(0x002d9d98));
/* 002d9da0: b 0x002d9ddc */ /* delay 002d9da4 */ set(2,cpu(0));goto L_002d9ddc;
L_002d9da8:;
/* 002d9da8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d9dac: dsubu v1,s2,s0 */ set(3,cpu(18)-cpu(16));
/* 002d9db0: lw a1,0x8(s4) */ lw(5,ea(20,(int32_t)UINT32_C(0x00000008)));
/* 002d9db4: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002d9db8: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002d9dbc: dsra32 v1,v1,0x0 */ set(3,(uint64_t)((int64_t)cpu(3)>>32));
/* 002d9dc0: move a0,s1 */ set(4,cpu(17));
/* 002d9dc4: sw v1,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d9dc8: lw v0,0x0(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d9dcc: subu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(19)));
/* 002d9dd0: jal 0x002d4698 */ set(31,0x002d9dd8u);/* delay 002d9dd4 */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002d4698),UINT32_C(0x002d9dd0));
/* 002d9dd8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002d9ddc:;
/* 002d9ddc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9de0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9de4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d9de8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d9dec: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d9df0: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d9df4: jr ra */ {uint64_t target=cpu(31);/* delay 002d9df8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002da5d0(void){
nocturneEffectAxisNoteEntry(0x002da5d0u);
uint64_t incoming=cpu(31);
/* 002da5d0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002da5d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002da5d8: move s0,a0 */ set(16,cpu(4));
/* 002da5dc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002da5e0: move s1,a1 */ set(17,cpu(5));
/* 002da5e4: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002da5e8: lw v1,0x4c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000004c)));
/* 002da5ec: bne v1,zero,0x002da608 */ {int taken=(cpu(3)!=cpu(0));/* delay 002da5f0 */ set(5,sx(UINT32_C(0x00000004)));if(taken){goto L_002da608;}}
/* 002da5f4: jal 0x002db840 */ set(31,0x002da5fcu);/* delay 002da5f8 */ set(6,sx(UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002db840),UINT32_C(0x002da5f4));
/* 002da5fc: move v1,v0 */ set(3,cpu(2));
/* 002da600: beq v1,zero,0x002da660 */ {int taken=(cpu(3)==cpu(0));/* delay 002da604 */ sw(ea(16,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(3));if(taken){goto L_002da660;}}
L_002da608:;
/* 002da608: sll v0,s1,0x2 */ set(2,sx((uint32_t)cpu(17)<<2));
/* 002da60c: addu a0,v0,v1 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002da610: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002da614: beq v1,zero,0x002da628 */ {int taken=(cpu(3)==cpu(0));/* delay 002da618 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002da628;}}
/* 002da61c: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002da620: b 0x002da654 */ /* delay 002da624 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_002da654;
L_002da628:;
/* 002da628: move a0,s0 */ set(4,cpu(16));
/* 002da62c: sllv s0,v0,s1 */ set(16,sx((uint32_t)cpu(2)<<(cpu(17)&31u)));
/* 002da630: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002da634: sll a2,s0,0x2 */ set(6,sx((uint32_t)cpu(16)<<2));
/* 002da638: jal 0x002db840 */ set(31,0x002da640u);/* delay 002da63c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000014)));nocturneBattlePanelRendererCall(UINT32_C(0x002db840),UINT32_C(0x002da638));
/* 002da640: move v1,v0 */ set(3,cpu(2));
/* 002da644: beql v1,zero,0x002da664 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002da648 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002da664;}}
/* 002da64c: sw s1,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 002da650: sw s0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));
L_002da654:;
/* 002da654: sw zero,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002da658: move v0,v1 */ set(2,cpu(3));
/* 002da65c: sw zero,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
L_002da660:;
/* 002da660: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002da664:;
/* 002da664: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002da668: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002da66c: jr ra */ {uint64_t target=cpu(31);/* delay 002da670 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002da678(void){
nocturneEffectAxisNoteEntry(0x002da678u);
uint64_t incoming=cpu(31);
/* 002da678: beq a1,zero,0x002da69c */ {int taken=(cpu(5)==cpu(0));/* delay 002da67c */ if(taken){goto L_002da69c;}}
/* 002da680: lw v0,0x4(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002da684: lw a0,0x4c(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x0000004c)));
/* 002da688: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002da68c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002da690: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002da694: sw v1,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002da698: sw a1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
L_002da69c:;
/* 002da69c: jr ra */ {uint64_t target=cpu(31);/* delay 002da6a0 */ checkReturn(target,incoming);return;}
}
static void body_002da6a8(void){
nocturneEffectAxisNoteEntry(0x002da6a8u);
uint64_t incoming=cpu(31);
/* 002da6a8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002da6ac: move t0,a2 */ set(8,cpu(6));
/* 002da6b0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002da6b4: move s1,a1 */ set(17,cpu(5));
/* 002da6b8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002da6bc: move s3,a3 */ set(19,cpu(7));
/* 002da6c0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002da6c4: move s4,a0 */ set(20,cpu(4));
/* 002da6c8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002da6cc: addiu a3,s1,0x14 */ set(7,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));
/* 002da6d0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002da6d4: move t1,zero */ set(9,cpu(0));
/* 002da6d8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002da6dc: lw s2,0x10(s1) */ lw(18,ea(17,(int32_t)UINT32_C(0x00000010)));
L_002da6e0:;
/* 002da6e0: lw v1,0x0(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002da6e4: addiu t1,t1,0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000001)));
/* 002da6e8: slt a2,t1,s2 */ set(6,(int64_t)cpu(9)<(int64_t)cpu(18));
/* 002da6ec: andi a0,v1,0xffff */ set(4,cpu(3)&UINT32_C(0x0000ffff));
/* 002da6f0: srl v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)>>16));
/* 002da6f4: mult v0,a0,t0 */ multiply(2,(uint32_t)cpu(4),(uint32_t)cpu(8),0);
/* 002da6f8: mult v1,v1,t0 */ multiply(3,(uint32_t)cpu(3),(uint32_t)cpu(8),0);
/* 002da6fc: addu a0,v0,s3 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 002da700: srl a1,a0,0x10 */ set(5,sx((uint32_t)cpu(4)>>16));
/* 002da704: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 002da708: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 002da70c: sll v0,v1,0x10 */ set(2,sx((uint32_t)cpu(3)<<16));
/* 002da710: srl s3,v1,0x10 */ set(19,sx((uint32_t)cpu(3)>>16));
/* 002da714: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002da718: sw v0,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002da71c: bne a2,zero,0x002da6e0 */ {int taken=(cpu(6)!=cpu(0));/* delay 002da720 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000004)));if(taken){goto L_002da6e0;}}
/* 002da724: beq s3,zero,0x002da790 */ {int taken=(cpu(19)==cpu(0));/* delay 002da728 */ set(2,cpu(17));if(taken){goto L_002da790;}}
/* 002da72c: lw v0,0x8(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002da730: slt v0,s2,v0 */ set(2,(int64_t)cpu(18)<(int64_t)cpu(2));
/* 002da734: bne v0,zero,0x002da77c */ {int taken=(cpu(2)!=cpu(0));/* delay 002da738 */ set(2,sx((uint32_t)cpu(18)<<2));if(taken){goto L_002da77c;}}
/* 002da73c: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002da740: move a0,s4 */ set(4,cpu(20));
/* 002da744: jal 0x002da5d0 */ set(31,0x002da74cu);/* delay 002da748 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002da744));
/* 002da74c: lw a2,0x10(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002da750: move s0,v0 */ set(16,cpu(2));
/* 002da754: addiu a1,s1,0xc */ set(5,sx((uint32_t)cpu(17)+UINT32_C(0x0000000c)));
/* 002da758: sll a2,a2,0x2 */ set(6,sx((uint32_t)cpu(6)<<2));
/* 002da75c: addiu a0,s0,0xc */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x0000000c)));
/* 002da760: jal 0x002d43a4 */ set(31,0x002da768u);/* delay 002da764 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000008)));nocturneBattlePanelRendererCall(UINT32_C(0x002d43a4),UINT32_C(0x002da760));
/* 002da768: move a0,s4 */ set(4,cpu(20));
/* 002da76c: move a1,s1 */ set(5,cpu(17));
/* 002da770: jal 0x002da678 */ set(31,0x002da778u);/* delay 002da774 */ set(17,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002da770));
/* 002da778: sll v0,s2,0x2 */ set(2,sx((uint32_t)cpu(18)<<2));
L_002da77c:;
/* 002da77c: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 002da780: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 002da784: sw s3,0x14(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 002da788: sw s2,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 002da78c: move v0,s1 */ set(2,cpu(17));
L_002da790:;
/* 002da790: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002da794: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002da798: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002da79c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002da7a0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002da7a4: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002da7a8: jr ra */ {uint64_t target=cpu(31);/* delay 002da7ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002da8e0(void){
nocturneEffectAxisNoteEntry(0x002da8e0u);
uint64_t incoming=cpu(31);
/* 002da8e0: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 002da8e4: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 002da8e8: bne v0,zero,0x002da8f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da8ec */ set(5,cpu(0));if(taken){goto L_002da8f8;}}
/* 002da8f0: li a1,0x10 */ set(5,sx(UINT32_C(0x00000010)));
/* 002da8f4: sll a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)<<16));
L_002da8f8:;
/* 002da8f8: lui v0,0xff00 */ set(2,sx(UINT32_C(0xff000000)));
/* 002da8fc: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 002da900: bne v0,zero,0x002da910 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da904 */ set(2,sx(UINT32_C(0xf0000000)));if(taken){goto L_002da910;}}
/* 002da908: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 002da90c: sll a0,a0,0x8 */ set(4,sx((uint32_t)cpu(4)<<8));
L_002da910:;
/* 002da910: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 002da914: bne v0,zero,0x002da924 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da918 */ set(2,sx(UINT32_C(0xc0000000)));if(taken){goto L_002da924;}}
/* 002da91c: addiu a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000004)));
/* 002da920: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
L_002da924:;
/* 002da924: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 002da928: bne v0,zero,0x002da938 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da92c */ if(taken){goto L_002da938;}}
/* 002da930: addiu a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 002da934: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
L_002da938:;
/* 002da938: bltz a0,0x002da958 */ {int taken=((int64_t)cpu(4)<0);/* delay 002da93c */ set(2,cpu(5));if(taken){goto L_002da958;}}
/* 002da940: lui v1,0x4000 */ set(3,sx(UINT32_C(0x40000000)));
/* 002da944: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002da948: and v1,a0,v1 */ set(3,cpu(4)&cpu(3));
/* 002da94c: beq v1,zero,0x002da958 */ {int taken=(cpu(3)==cpu(0));/* delay 002da950 */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_002da958;}}
/* 002da954: move v0,a1 */ set(2,cpu(5));
L_002da958:;
/* 002da958: jr ra */ {uint64_t target=cpu(31);/* delay 002da95c */ checkReturn(target,incoming);return;}
}
static void body_002da960(void){
nocturneEffectAxisNoteEntry(0x002da960u);
uint64_t incoming=cpu(31);
/* 002da960: lw a1,0x0(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002da964: andi v0,a1,0x7 */ set(2,cpu(5)&UINT32_C(0x00000007));
/* 002da968: beq v0,zero,0x002da9a0 */ {int taken=(cpu(2)==cpu(0));/* delay 002da96c */ set(3,cpu(5)&UINT32_C(0x00000001));if(taken){goto L_002da9a0;}}
/* 002da970: bne v1,zero,0x002daa14 */ {int taken=(cpu(3)!=cpu(0));/* delay 002da974 */ set(2,cpu(0));if(taken){goto L_002daa14;}}
/* 002da978: andi v0,a1,0x2 */ set(2,cpu(5)&UINT32_C(0x00000002));
/* 002da97c: beq v0,zero,0x002da990 */ {int taken=(cpu(2)==cpu(0));/* delay 002da980 */ set(3,sx((uint32_t)cpu(5)>>1));if(taken){goto L_002da990;}}
/* 002da984: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002da988: jr ra */ {uint64_t target=cpu(31);/* delay 002da98c */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
L_002da990:;
/* 002da990: srl v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)>>2));
/* 002da994: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002da998: jr ra */ {uint64_t target=cpu(31);/* delay 002da99c */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
L_002da9a0:;
/* 002da9a0: andi v0,a1,0xffff */ set(2,cpu(5)&UINT32_C(0x0000ffff));
/* 002da9a4: bne v0,zero,0x002da9b4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da9a8 */ set(3,cpu(0));if(taken){goto L_002da9b4;}}
/* 002da9ac: li v1,0x10 */ set(3,sx(UINT32_C(0x00000010)));
/* 002da9b0: srl a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)>>16));
L_002da9b4:;
/* 002da9b4: andi v0,a1,0xff */ set(2,cpu(5)&UINT32_C(0x000000ff));
/* 002da9b8: bne v0,zero,0x002da9cc */ {int taken=(cpu(2)!=cpu(0));/* delay 002da9bc */ set(2,cpu(5)&UINT32_C(0x0000000f));if(taken){goto L_002da9cc;}}
/* 002da9c0: addiu v1,v1,0x8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 002da9c4: srl a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)>>8));
/* 002da9c8: andi v0,a1,0xf */ set(2,cpu(5)&UINT32_C(0x0000000f));
L_002da9cc:;
/* 002da9cc: bne v0,zero,0x002da9e0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da9d0 */ set(2,cpu(5)&UINT32_C(0x00000003));if(taken){goto L_002da9e0;}}
/* 002da9d4: addiu v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000004)));
/* 002da9d8: srl a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)>>4));
/* 002da9dc: andi v0,a1,0x3 */ set(2,cpu(5)&UINT32_C(0x00000003));
L_002da9e0:;
/* 002da9e0: bne v0,zero,0x002da9f4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da9e4 */ set(2,cpu(5)&UINT32_C(0x00000001));if(taken){goto L_002da9f4;}}
/* 002da9e8: addiu v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000002)));
/* 002da9ec: srl a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)>>2));
/* 002da9f0: andi v0,a1,0x1 */ set(2,cpu(5)&UINT32_C(0x00000001));
L_002da9f4:;
/* 002da9f4: bnel v0,zero,0x002daa10 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002da9f8 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));goto L_002daa10;}}
/* 002da9fc: srl a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)>>1));
/* 002daa00: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002daa04: beq a1,zero,0x002daa14 */ {int taken=(cpu(5)==cpu(0));/* delay 002daa08 */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_002daa14;}}
/* 002daa0c: sw a1,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
L_002daa10:;
/* 002daa10: move v0,v1 */ set(2,cpu(3));
L_002daa14:;
/* 002daa14: jr ra */ {uint64_t target=cpu(31);/* delay 002daa18 */ checkReturn(target,incoming);return;}
}
static void body_002daa20(void){
nocturneEffectAxisNoteEntry(0x002daa20u);
uint64_t incoming=cpu(31);
/* 002daa20: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002daa24: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002daa28: move s0,a1 */ set(16,cpu(5));
/* 002daa2c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002daa30: jal 0x002da5d0 */ set(31,0x002daa38u);/* delay 002daa34 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002daa30));
/* 002daa38: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002daa3c: move a0,v0 */ set(4,cpu(2));
/* 002daa40: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002daa44: sw s0,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(16));
/* 002daa48: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002daa4c: sw v1,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 002daa50: jr ra */ {uint64_t target=cpu(31);/* delay 002daa54 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002daa58(void){
nocturneEffectAxisNoteEntry(0x002daa58u);
uint64_t incoming=cpu(31);
/* 002daa58: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002daa5c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002daa60: move s0,a1 */ set(16,cpu(5));
/* 002daa64: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002daa68: move s2,a2 */ set(18,cpu(6));
/* 002daa6c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002daa70: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002daa74: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002daa78: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002daa7c: lw s3,0x10(s0) */ lw(19,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002daa80: lw s1,0x10(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002daa84: slt v0,s3,s1 */ set(2,(int64_t)cpu(19)<(int64_t)cpu(17));
/* 002daa88: beql v0,zero,0x002daaa8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002daa8c */ lw(5,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_002daaa8;}}
/* 002daa90: move t8,s0 */ set(24,cpu(16));
/* 002daa94: move s0,s2 */ set(16,cpu(18));
/* 002daa98: move s2,t8 */ set(18,cpu(24));
/* 002daa9c: move s3,s1 */ set(19,cpu(17));
/* 002daaa0: lw s1,0x10(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002daaa4: lw a1,0x8(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000008)));
L_002daaa8:;
/* 002daaa8: addu s4,s3,s1 */ set(20,sx((uint32_t)cpu(19)+(uint32_t)cpu(17)));
/* 002daaac: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002daab0: slt a1,a1,s4 */ set(5,(int64_t)cpu(5)<(int64_t)cpu(20));
/* 002daab4: jal 0x002da5d0 */ set(31,0x002daabcu);/* delay 002daab8 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002daab4));
/* 002daabc: sll t9,s4,0x2 */ set(25,sx((uint32_t)cpu(20)<<2));
/* 002daac0: move t8,v0 */ set(24,cpu(2));
/* 002daac4: addiu t7,t8,0x14 */ set(15,sx((uint32_t)cpu(24)+UINT32_C(0x00000014)));
/* 002daac8: addu t5,t7,t9 */ set(13,sx((uint32_t)cpu(15)+(uint32_t)cpu(25)));
/* 002daacc: sltu v0,t7,t5 */ set(2,cpu(15)<cpu(13));
/* 002daad0: beq v0,zero,0x002daafc */ {int taken=(cpu(2)==cpu(0));/* delay 002daad4 */ set(8,cpu(15));if(taken){goto L_002daafc;}}
/* 002daad8: sw zero,0x0(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002daadc: nop  */ 
L_002daae0:;
/* 002daae0: addiu t0,t0,0x4 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));
/* 002daae4: sltu v0,t0,t5 */ set(2,cpu(8)<cpu(13));
/* 002daae8: nop  */ 
/* 002daaec: nop  */ 
/* 002daaf0: nop  */ 
/* 002daaf4: bnel v0,zero,0x002daae0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002daaf8 */ sw(ea(8,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));goto L_002daae0;}}
L_002daafc:;
/* 002daafc: addiu t3,s2,0x14 */ set(11,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 002dab00: sll v0,s1,0x2 */ set(2,sx((uint32_t)cpu(17)<<2));
/* 002dab04: addu s1,t3,v0 */ set(17,sx((uint32_t)cpu(11)+(uint32_t)cpu(2)));
/* 002dab08: sll v0,s3,0x2 */ set(2,sx((uint32_t)cpu(19)<<2));
/* 002dab0c: addiu t5,s0,0x14 */ set(13,sx((uint32_t)cpu(16)+UINT32_C(0x00000014)));
/* 002dab10: sltu v1,t3,s1 */ set(3,cpu(11)<cpu(17));
/* 002dab14: addu t6,t5,v0 */ set(14,sx((uint32_t)cpu(13)+(uint32_t)cpu(2)));
/* 002dab18: beq v1,zero,0x002dac14 */ {int taken=(cpu(3)==cpu(0));/* delay 002dab1c */ set(12,cpu(15));if(taken){goto L_002dac14;}}
L_002dab20:;
/* 002dab20: lw v0,0x0(t3) */ lw(2,ea(11,(int32_t)UINT32_C(0x00000000)));
/* 002dab24: andi t1,v0,0xffff */ set(9,cpu(2)&UINT32_C(0x0000ffff));
/* 002dab28: beq t1,zero,0x002dab90 */ {int taken=(cpu(9)==cpu(0));/* delay 002dab2c */ set(7,cpu(12));if(taken){goto L_002dab90;}}
/* 002dab30: move t0,t5 */ set(8,cpu(13));
/* 002dab34: move t2,zero */ set(10,cpu(0));
L_002dab38:;
/* 002dab38: lw v1,0x0(t0) */ lw(3,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 002dab3c: addiu t0,t0,0x4 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));
/* 002dab40: lw a1,0x0(a3) */ lw(5,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002dab44: sltu a2,t0,t6 */ set(6,cpu(8)<cpu(14));
/* 002dab48: andi v0,v1,0xffff */ set(2,cpu(3)&UINT32_C(0x0000ffff));
/* 002dab4c: srl v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)>>16));
/* 002dab50: mult v0,v0,t1 */ multiply(2,(uint32_t)cpu(2),(uint32_t)cpu(9),0);
/* 002dab54: mult1 v1,v1,t1 */ multiply(3,(uint32_t)cpu(3),(uint32_t)cpu(9),1);
/* 002dab58: andi a0,a1,0xffff */ set(4,cpu(5)&UINT32_C(0x0000ffff));
/* 002dab5c: srl a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)>>16));
/* 002dab60: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002dab64: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 002dab68: addu v0,v0,t2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(10)));
/* 002dab6c: srl t2,v0,0x10 */ set(10,sx((uint32_t)cpu(2)>>16));
/* 002dab70: sh v0,0x0(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));
/* 002dab74: addu v0,v1,t2 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(10)));
/* 002dab78: sh v0,0x2(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));
/* 002dab7c: addiu a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000004)));
/* 002dab80: bne a2,zero,0x002dab38 */ {int taken=(cpu(6)!=cpu(0));/* delay 002dab84 */ set(10,sx((uint32_t)cpu(2)>>16));if(taken){goto L_002dab38;}}
/* 002dab88: sw t2,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(10));
/* 002dab8c: lw v0,0x0(t3) */ lw(2,ea(11,(int32_t)UINT32_C(0x00000000)));
L_002dab90:;
/* 002dab90: srl t1,v0,0x10 */ set(9,sx((uint32_t)cpu(2)>>16));
/* 002dab94: beq t1,zero,0x002dac04 */ {int taken=(cpu(9)==cpu(0));/* delay 002dab98 */ set(7,cpu(12));if(taken){goto L_002dac04;}}
/* 002dab9c: move t0,t5 */ set(8,cpu(13));
/* 002daba0: lw v0,0x0(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002daba4: move t2,zero */ set(10,cpu(0));
/* 002daba8: move a0,v0 */ set(4,cpu(2));
/* 002dabac: nop  */ 
L_002dabb0:;
/* 002dabb0: lw v1,0x0(t0) */ lw(3,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 002dabb4: addiu t0,t0,0x4 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));
/* 002dabb8: sh v0,0x0(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));
/* 002dabbc: srl a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)>>16));
/* 002dabc0: andi v0,v1,0xffff */ set(2,cpu(3)&UINT32_C(0x0000ffff));
/* 002dabc4: srl v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)>>16));
/* 002dabc8: mult v0,v0,t1 */ multiply(2,(uint32_t)cpu(2),(uint32_t)cpu(9),0);
/* 002dabcc: mult1 v1,v1,t1 */ multiply(3,(uint32_t)cpu(3),(uint32_t)cpu(9),1);
/* 002dabd0: sltu a1,t0,t6 */ set(5,cpu(8)<cpu(14));
/* 002dabd4: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002dabd8: addu v0,v0,t2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(10)));
/* 002dabdc: sh v0,0x2(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));
/* 002dabe0: addiu a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000004)));
/* 002dabe4: lw a0,0x0(a3) */ lw(4,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002dabe8: srl t2,v0,0x10 */ set(10,sx((uint32_t)cpu(2)>>16));
/* 002dabec: andi v0,a0,0xffff */ set(2,cpu(4)&UINT32_C(0x0000ffff));
/* 002dabf0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002dabf4: addu v0,v1,t2 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(10)));
/* 002dabf8: bne a1,zero,0x002dabb0 */ {int taken=(cpu(5)!=cpu(0));/* delay 002dabfc */ set(10,sx((uint32_t)cpu(2)>>16));if(taken){goto L_002dabb0;}}
/* 002dac00: sw v0,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002dac04:;
/* 002dac04: addiu t3,t3,0x4 */ set(11,sx((uint32_t)cpu(11)+UINT32_C(0x00000004)));
/* 002dac08: sltu v0,t3,s1 */ set(2,cpu(11)<cpu(17));
/* 002dac0c: bne v0,zero,0x002dab20 */ {int taken=(cpu(2)!=cpu(0));/* delay 002dac10 */ set(12,sx((uint32_t)cpu(12)+UINT32_C(0x00000004)));if(taken){goto L_002dab20;}}
L_002dac14:;
/* 002dac14: addu a3,t7,t9 */ set(7,sx((uint32_t)cpu(15)+(uint32_t)cpu(25)));
L_002dac18:;
/* 002dac18: blezl s4,0x002dac40 */ {int taken=((int64_t)cpu(20)<=0);if(taken){/* delay 002dac1c */ sw(ea(24,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(20));goto L_002dac40;}}
/* 002dac20: addiu a3,a3,-0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffffc)));
/* 002dac24: lw v0,0x0(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002dac28: nop  */ 
/* 002dac2c: nop  */ 
/* 002dac30: nop  */ 
/* 002dac34: beql v0,zero,0x002dac18 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002dac38 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffffff)));goto L_002dac18;}}
/* 002dac3c: sw s4,0x10(t8) */ sw(ea(24,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(20));
L_002dac40:;
/* 002dac40: move v0,t8 */ set(2,cpu(24));
/* 002dac44: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dac48: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002dac4c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dac50: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002dac54: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dac58: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002dac5c: jr ra */ {uint64_t target=cpu(31);/* delay 002dac60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002dac68(void){
nocturneEffectAxisNoteEntry(0x002dac68u);
uint64_t incoming=cpu(31);
/* 002dac68: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002dac6c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002dac70: move s1,a2 */ set(17,cpu(6));
/* 002dac74: andi v0,s1,0x3 */ set(2,cpu(17)&UINT32_C(0x00000003));
/* 002dac78: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dac7c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002dac80: move s3,a0 */ set(19,cpu(4));
/* 002dac84: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dac88: move s2,a1 */ set(18,cpu(5));
/* 002dac8c: beq v0,zero,0x002dacb0 */ {int taken=(cpu(2)==cpu(0));/* delay 002dac90 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002dacb0;}}
/* 002dac94: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002dac98: lui a2,0x55 */ set(6,sx(UINT32_C(0x00550000)));
/* 002dac9c: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 002daca0: lw a2,-0x46e4(a2) */ lw(6,ea(6,(int32_t)UINT32_C(0xffffb91c)));
/* 002daca4: jal 0x002da6a8 */ set(31,0x002dacacu);/* delay 002daca8 */ set(7,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002da6a8),UINT32_C(0x002daca4));
/* 002dacac: move s2,v0 */ set(18,cpu(2));
L_002dacb0:;
/* 002dacb0: sra s1,s1,0x2 */ set(17,sx((uint32_t)((int32_t)cpu(17)>>2)));
/* 002dacb4: beq s1,zero,0x002dad48 */ {int taken=(cpu(17)==cpu(0));/* delay 002dacb8 */ set(2,cpu(18));if(taken){goto L_002dad48;}}
/* 002dacbc: lw s0,0x48(s3) */ lw(16,ea(19,(int32_t)UINT32_C(0x00000048)));
/* 002dacc0: bne s0,zero,0x002dad14 */ {int taken=(cpu(16)!=cpu(0));/* delay 002dacc4 */ set(2,cpu(17)&UINT32_C(0x00000001));if(taken){goto L_002dad14;}}
/* 002dacc8: move a0,s3 */ set(4,cpu(19));
/* 002daccc: jal 0x002daa20 */ set(31,0x002dacd4u);/* delay 002dacd0 */ set(5,sx(UINT32_C(0x00000271)));nocturneBattlePanelRendererCall(UINT32_C(0x002daa20),UINT32_C(0x002daccc));
/* 002dacd4: move s0,v0 */ set(16,cpu(2));
/* 002dacd8: sw v0,0x48(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(2));
/* 002dacdc: b 0x002dad10 */ /* delay 002dace0 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));goto L_002dad10;
L_002dace8:;
/* 002dace8: bnel v1,zero,0x002dad10 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002dacec */ set(16,cpu(3));goto L_002dad10;}}
/* 002dacf0: move a1,s0 */ set(5,cpu(16));
/* 002dacf4: move a2,s0 */ set(6,cpu(16));
/* 002dacf8: jal 0x002daa58 */ set(31,0x002dad00u);/* delay 002dacfc */ set(4,cpu(19));nocturneBattlePanelRendererCall(UINT32_C(0x002daa58),UINT32_C(0x002dacf8));
/* 002dad00: move v1,v0 */ set(3,cpu(2));
/* 002dad04: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002dad08: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002dad0c: move s0,v1 */ set(16,cpu(3));
L_002dad10:;
/* 002dad10: andi v0,s1,0x1 */ set(2,cpu(17)&UINT32_C(0x00000001));
L_002dad14:;
/* 002dad14: beq v0,zero,0x002dad3c */ {int taken=(cpu(2)==cpu(0));/* delay 002dad18 */ set(17,sx((uint32_t)((int32_t)cpu(17)>>1)));if(taken){goto L_002dad3c;}}
/* 002dad1c: move a1,s2 */ set(5,cpu(18));
/* 002dad20: move a0,s3 */ set(4,cpu(19));
/* 002dad24: jal 0x002daa58 */ set(31,0x002dad2cu);/* delay 002dad28 */ set(6,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002daa58),UINT32_C(0x002dad24));
/* 002dad2c: move a0,s3 */ set(4,cpu(19));
/* 002dad30: move a1,s2 */ set(5,cpu(18));
/* 002dad34: jal 0x002da678 */ set(31,0x002dad3cu);/* delay 002dad38 */ set(18,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002dad34));
L_002dad3c:;
/* 002dad3c: bnel s1,zero,0x002dace8 */ {int taken=(cpu(17)!=cpu(0));if(taken){/* delay 002dad40 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002dace8;}}
/* 002dad44: move v0,s2 */ set(2,cpu(18));
L_002dad48:;
/* 002dad48: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dad4c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002dad50: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dad54: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002dad58: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dad5c: jr ra */ {uint64_t target=cpu(31);/* delay 002dad60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002dad68(void){
nocturneEffectAxisNoteEntry(0x002dad68u);
uint64_t incoming=cpu(31);
/* 002dad68: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002dad6c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dad70: move s0,a2 */ set(16,cpu(6));
/* 002dad74: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002dad78: sra s1,s0,0x5 */ set(17,sx((uint32_t)((int32_t)cpu(16)>>5)));
/* 002dad7c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dad80: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002dad84: move s3,a1 */ set(19,cpu(5));
/* 002dad88: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002dad8c: move s5,a0 */ set(21,cpu(4));
/* 002dad90: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dad94: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dad98: lw v1,0x10(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 002dad9c: lw a2,0x8(s3) */ lw(6,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 002dada0: addu v1,s1,v1 */ set(3,sx((uint32_t)cpu(17)+(uint32_t)cpu(3)));
/* 002dada4: addiu s2,v1,0x1 */ set(18,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002dada8: slt v0,a2,s2 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(18));
/* 002dadac: beq v0,zero,0x002dadd4 */ {int taken=(cpu(2)==cpu(0));/* delay 002dadb0 */ lw(5,ea(19,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_002dadd4;}}
/* 002dadb4: nop  */ 
L_002dadb8:;
/* 002dadb8: sll a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)<<1));
/* 002dadbc: slt v0,a2,s2 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(18));
/* 002dadc0: nop  */ 
/* 002dadc4: nop  */ 
/* 002dadc8: nop  */ 
/* 002dadcc: bne v0,zero,0x002dadb8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002dadd0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_002dadb8;}}
L_002dadd4:;
/* 002dadd4: jal 0x002da5d0 */ set(31,0x002daddcu);/* delay 002dadd8 */ set(4,cpu(21));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002dadd4));
/* 002daddc: move s4,v0 */ set(20,cpu(2));
/* 002dade0: blez s1,0x002dae0c */ {int taken=((int64_t)cpu(17)<=0);/* delay 002dade4 */ set(7,sx((uint32_t)cpu(20)+UINT32_C(0x00000014)));if(taken){goto L_002dae0c;}}
/* 002dade8: move a2,s1 */ set(6,cpu(17));
/* 002dadec: nop  */ 
L_002dadf0:;
/* 002dadf0: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002dadf4: sw zero,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002dadf8: nop  */ 
/* 002dadfc: nop  */ 
/* 002dae00: nop  */ 
/* 002dae04: bne a2,zero,0x002dadf0 */ {int taken=(cpu(6)!=cpu(0));/* delay 002dae08 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000004)));if(taken){goto L_002dadf0;}}
L_002dae0c:;
/* 002dae0c: lw v0,0x10(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 002dae10: addiu a0,s3,0x14 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00000014)));
/* 002dae14: andi s0,s0,0x1f */ set(16,cpu(16)&UINT32_C(0x0000001f));
/* 002dae18: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002dae1c: beq s0,zero,0x002dae68 */ {int taken=(cpu(16)==cpu(0));/* delay 002dae20 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));if(taken){goto L_002dae68;}}
/* 002dae24: li v0,0x20 */ set(2,sx(UINT32_C(0x00000020)));
/* 002dae28: move v1,zero */ set(3,cpu(0));
/* 002dae2c: subu a1,v0,s0 */ set(5,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
L_002dae30:;
/* 002dae30: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002dae34: sllv v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)<<(cpu(16)&31u)));
/* 002dae38: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002dae3c: sw v0,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002dae40: addiu a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000004)));
/* 002dae44: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002dae48: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 002dae4c: sltu v0,a0,a2 */ set(2,cpu(4)<cpu(6));
/* 002dae50: bne v0,zero,0x002dae30 */ {int taken=(cpu(2)!=cpu(0));/* delay 002dae54 */ set(3,sx((uint32_t)cpu(3)>>(cpu(5)&31u)));if(taken){goto L_002dae30;}}
/* 002dae58: beq v1,zero,0x002dae84 */ {int taken=(cpu(3)==cpu(0));/* delay 002dae5c */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_002dae84;}}
/* 002dae60: b 0x002dae84 */ /* delay 002dae64 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));goto L_002dae84;
L_002dae68:;
/* 002dae68: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002dae6c: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 002dae70: sltu v1,a0,a2 */ set(3,cpu(4)<cpu(6));
/* 002dae74: sw v0,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002dae78: nop  */ 
/* 002dae7c: bne v1,zero,0x002dae68 */ {int taken=(cpu(3)!=cpu(0));/* delay 002dae80 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000004)));if(taken){goto L_002dae68;}}
L_002dae84:;
/* 002dae84: addiu v0,s2,-0x1 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));
/* 002dae88: move a0,s5 */ set(4,cpu(21));
/* 002dae8c: sw v0,0x10(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002dae90: jal 0x002da678 */ set(31,0x002dae98u);/* delay 002dae94 */ set(5,cpu(19));nocturneBattlePanelRendererCall(UINT32_C(0x002da678),UINT32_C(0x002dae90));
/* 002dae98: move v0,s4 */ set(2,cpu(20));
/* 002dae9c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002daea0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002daea4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002daea8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002daeac: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002daeb0: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002daeb4: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002daeb8: jr ra */ {uint64_t target=cpu(31);/* delay 002daebc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002daec0(void){
nocturneEffectAxisNoteEntry(0x002daec0u);
uint64_t incoming=cpu(31);
/* 002daec0: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002daec4: lw v1,0x10(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 002daec8: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002daecc: bne v0,zero,0x002daf20 */ {int taken=(cpu(2)!=cpu(0));/* delay 002daed0 */ if(taken){goto L_002daf20;}}
/* 002daed4: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 002daed8: addiu t2,a0,0x14 */ set(10,sx((uint32_t)cpu(4)+UINT32_C(0x00000014)));
/* 002daedc: addiu v0,a1,0x14 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000014)));
/* 002daee0: addu a3,t2,v1 */ set(7,sx((uint32_t)cpu(10)+(uint32_t)cpu(3)));
/* 002daee4: addu t1,v0,v1 */ set(9,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002daee8: addiu a3,a3,-0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffffc)));
/* 002daeec: nop  */ 
L_002daef0:;
/* 002daef0: addiu t1,t1,-0x4 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xfffffffc)));
/* 002daef4: lw a1,0x0(a3) */ lw(5,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002daef8: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 002daefc: lw a0,0x0(t1) */ lw(4,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 002daf00: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002daf04: sltu t0,t2,a3 */ set(8,cpu(10)<cpu(7));
/* 002daf08: sltu v1,a1,a0 */ set(3,cpu(5)<cpu(4));
/* 002daf0c: bne a1,a0,0x002daf20 */ {int taken=(cpu(5)!=cpu(4));/* delay 002daf10 */ if(cpu(3)==0){set(2,cpu(6));}if(taken){goto L_002daf20;}}
/* 002daf14: bnel t0,zero,0x002daef0 */ {int taken=(cpu(8)!=cpu(0));if(taken){/* delay 002daf18 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffffc)));goto L_002daef0;}}
/* 002daf1c: move v0,zero */ set(2,cpu(0));
L_002daf20:;
/* 002daf20: jr ra */ {uint64_t target=cpu(31);/* delay 002daf24 */ checkReturn(target,incoming);return;}
}
static void body_002daf28(void){
nocturneEffectAxisNoteEntry(0x002daf28u);
uint64_t incoming=cpu(31);
/* 002daf28: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002daf2c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002daf30: move s1,a1 */ set(17,cpu(5));
/* 002daf34: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002daf38: move s2,a2 */ set(18,cpu(6));
/* 002daf3c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002daf40: move s3,a0 */ set(19,cpu(4));
/* 002daf44: move a1,s2 */ set(5,cpu(18));
/* 002daf48: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002daf4c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002daf50: jal 0x002daec0 */ set(31,0x002daf58u);/* delay 002daf54 */ set(4,cpu(17));nocturneBattlePanelRendererCall(UINT32_C(0x002daec0),UINT32_C(0x002daf50));
/* 002daf58: move s0,v0 */ set(16,cpu(2));
/* 002daf5c: bne s0,zero,0x002daf80 */ {int taken=(cpu(16)!=cpu(0));/* delay 002daf60 */ set(4,cpu(19));if(taken){goto L_002daf80;}}
/* 002daf64: jal 0x002da5d0 */ set(31,0x002daf6cu);/* delay 002daf68 */ set(5,cpu(0));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002daf64));
/* 002daf6c: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002daf70: move t3,v0 */ set(11,cpu(2));
/* 002daf74: sw v1,0x10(t3) */ sw(ea(11,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 002daf78: b 0x002db09c */ /* delay 002daf7c */ sw(ea(11,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));goto L_002db09c;
L_002daf80:;
/* 002daf80: bgezl s0,0x002daf98 */ {int taken=((int64_t)cpu(16)>=0);if(taken){/* delay 002daf84 */ set(16,cpu(0));goto L_002daf98;}}
/* 002daf88: move t3,s1 */ set(11,cpu(17));
/* 002daf8c: move s1,s2 */ set(17,cpu(18));
/* 002daf90: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
/* 002daf94: move s2,t3 */ set(18,cpu(11));
L_002daf98:;
/* 002daf98: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002daf9c: jal 0x002da5d0 */ set(31,0x002dafa4u);/* delay 002dafa0 */ set(4,cpu(19));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002daf9c));
/* 002dafa4: addiu t0,s1,0x14 */ set(8,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));
/* 002dafa8: move t3,v0 */ set(11,cpu(2));
/* 002dafac: addiu t1,s2,0x14 */ set(9,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 002dafb0: sw s0,0xc(t3) */ sw(ea(11,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(16));
/* 002dafb4: addiu a3,t3,0x14 */ set(7,sx((uint32_t)cpu(11)+UINT32_C(0x00000014)));
/* 002dafb8: move t2,zero */ set(10,cpu(0));
/* 002dafbc: lw t4,0x10(s1) */ lw(12,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002dafc0: lw v0,0x10(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002dafc4: sll v1,t4,0x2 */ set(3,sx((uint32_t)cpu(12)<<2));
/* 002dafc8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002dafcc: addu t5,t0,v1 */ set(13,sx((uint32_t)cpu(8)+(uint32_t)cpu(3)));
/* 002dafd0: addu a2,t1,v0 */ set(6,sx((uint32_t)cpu(9)+(uint32_t)cpu(2)));
/* 002dafd4: nop  */ 
L_002dafd8:;
/* 002dafd8: lw a1,0x0(t0) */ lw(5,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 002dafdc: addiu t0,t0,0x4 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));
/* 002dafe0: lw v0,0x0(t1) */ lw(2,ea(9,(int32_t)UINT32_C(0x00000000)));
/* 002dafe4: addiu t1,t1,0x4 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000004)));
/* 002dafe8: andi v1,a1,0xffff */ set(3,cpu(5)&UINT32_C(0x0000ffff));
/* 002dafec: srl a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)>>16));
/* 002daff0: andi a0,v0,0xffff */ set(4,cpu(2)&UINT32_C(0x0000ffff));
/* 002daff4: srl v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)>>16));
/* 002daff8: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 002daffc: subu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(2)));
/* 002db000: addu v1,v1,t2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(10)));
/* 002db004: sltu v0,t1,a2 */ set(2,cpu(9)<cpu(6));
/* 002db008: sra t2,v1,0x10 */ set(10,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 002db00c: sh v1,0x0(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002db010: addu a1,a1,t2 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(10)));
/* 002db014: sh a1,0x2(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(5));
/* 002db018: addiu a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000004)));
/* 002db01c: bne v0,zero,0x002dafd8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002db020 */ set(10,sx((uint32_t)((int32_t)cpu(5)>>16)));if(taken){goto L_002dafd8;}}
/* 002db024: sltu v0,t0,t5 */ set(2,cpu(8)<cpu(13));
/* 002db028: beql v0,zero,0x002db068 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002db02c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffffc)));goto L_002db068;}}
L_002db030:;
/* 002db030: lw v0,0x0(t0) */ lw(2,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 002db034: addiu t0,t0,0x4 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));
/* 002db038: sltu a0,t0,t5 */ set(4,cpu(8)<cpu(13));
/* 002db03c: andi v1,v0,0xffff */ set(3,cpu(2)&UINT32_C(0x0000ffff));
/* 002db040: srl v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)>>16));
/* 002db044: addu v1,v1,t2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(10)));
/* 002db048: sra t2,v1,0x10 */ set(10,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 002db04c: sh v1,0x0(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002db050: addu a1,v0,t2 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(10)));
/* 002db054: sh a1,0x2(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(5));
/* 002db058: addiu a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000004)));
/* 002db05c: bne a0,zero,0x002db030 */ {int taken=(cpu(4)!=cpu(0));/* delay 002db060 */ set(10,sx((uint32_t)((int32_t)cpu(5)>>16)));if(taken){goto L_002db030;}}
/* 002db064: addiu a3,a3,-0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffffc)));
L_002db068:;
/* 002db068: lw v0,0x0(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002db06c: bnel v0,zero,0x002db098 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002db070 */ sw(ea(11,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(12));goto L_002db098;}}
/* 002db074: nop  */ 
L_002db078:;
/* 002db078: addiu a3,a3,-0x4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xfffffffc)));
/* 002db07c: lw v0,0x0(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002db080: nop  */ 
/* 002db084: nop  */ 
/* 002db088: nop  */ 
/* 002db08c: beq v0,zero,0x002db078 */ {int taken=(cpu(2)==cpu(0));/* delay 002db090 */ set(12,sx((uint32_t)cpu(12)+UINT32_C(0xffffffff)));if(taken){goto L_002db078;}}
/* 002db094: sw t4,0x10(t3) */ sw(ea(11,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(12));
L_002db098:;
/* 002db098: move v0,t3 */ set(2,cpu(11));
L_002db09c:;
/* 002db09c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002db0a0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002db0a4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002db0a8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002db0ac: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002db0b0: jr ra */ {uint64_t target=cpu(31);/* delay 002db0b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002db320(void){
nocturneEffectAxisNoteEntry(0x002db320u);
uint64_t incoming=cpu(31);
/* 002db320: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002db324: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002db328: move s0,a1 */ set(16,cpu(5));
/* 002db32c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002db330: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002db334: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002db338: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002db33c: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002db340: move s4,a2 */ set(20,cpu(6));
/* 002db344: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002db348: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002db34c: jal 0x002da5d0 */ set(31,0x002db354u);/* delay 002db350 */ set(21,cpu(7));nocturneBattlePanelRendererCall(UINT32_C(0x002da5d0),UINT32_C(0x002db34c));
/* 002db354: move s3,v0 */ set(19,cpu(2));
/* 002db358: lui v0,0x7fff */ set(2,sx(UINT32_C(0x7fff0000)));
/* 002db35c: dsra32 a0,s0,0x0 */ set(4,(uint64_t)((int64_t)cpu(16)>>32));
/* 002db360: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002db364: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 002db368: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002db36c: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 002db370: and s0,s0,v1 */ set(16,cpu(16)&cpu(3));
/* 002db374: lui v1,0xf */ set(3,sx(UINT32_C(0x000f0000)));
/* 002db378: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002db37c: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002db380: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
/* 002db384: and a0,a0,v1 */ set(4,cpu(4)&cpu(3));
/* 002db388: dsrl32 s2,s0,0x14 */ set(18,cpu(16)>>52);
/* 002db38c: sw a0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002db390: beq s2,zero,0x002db3a4 */ {int taken=(cpu(18)==cpu(0));/* delay 002db394 */ set(17,sx((uint32_t)cpu(19)+UINT32_C(0x00000014)));if(taken){goto L_002db3a4;}}
/* 002db398: lui v0,0x10 */ set(2,sx(UINT32_C(0x00100000)));
/* 002db39c: or v0,a0,v0 */ set(2,cpu(4)|cpu(2));
/* 002db3a0: sw v0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002db3a4:;
/* 002db3a4: dsll32 a1,s0,0x0 */ set(5,cpu(16)<<32);
/* 002db3a8: dsra32 a1,a1,0x0 */ set(5,(uint64_t)((int64_t)cpu(5)>>32));
/* 002db3ac: beq a1,zero,0x002db418 */ {int taken=(cpu(5)==cpu(0));/* delay 002db3b0 */ set(4,cpu(29));if(taken){goto L_002db418;}}
/* 002db3b4: jal 0x002da960 */ set(31,0x002db3bcu);/* delay 002db3b8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));nocturneBattlePanelRendererCall(UINT32_C(0x002da960),UINT32_C(0x002db3b4));
/* 002db3bc: move a1,v0 */ set(5,cpu(2));
/* 002db3c0: beq a1,zero,0x002db3f0 */ {int taken=(cpu(5)==cpu(0));/* delay 002db3c4 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_002db3f0;}}
/* 002db3c8: subu a0,zero,a1 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(5)));
/* 002db3cc: lw v1,0x0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002db3d0: sllv v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)<<(cpu(4)&31u)));
/* 002db3d4: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002db3d8: sw v1,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002db3dc: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002db3e0: srlv v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)>>(cpu(5)&31u)));
/* 002db3e4: b 0x002db3f8 */ /* delay 002db3e8 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002db3f8;
L_002db3f0:;
/* 002db3f0: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002db3f4: sw v0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002db3f8:;
/* 002db3f8: lw a0,0x4(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002db3fc: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002db400: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002db404: movz v0,v1,a0 */ if(cpu(4)==0){set(2,cpu(3));}
/* 002db408: sw a0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002db40c: move s0,v0 */ set(16,cpu(2));
/* 002db410: b 0x002db438 */ /* delay 002db414 */ sw(ea(19,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));goto L_002db438;
L_002db418:;
/* 002db418: addiu a0,sp,0x4 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000004)));
/* 002db41c: jal 0x002da960 */ set(31,0x002db424u);/* delay 002db420 */ set(16,sx(UINT32_C(0x00000001)));nocturneBattlePanelRendererCall(UINT32_C(0x002da960),UINT32_C(0x002db41c));
/* 002db424: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002db428: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002db42c: addiu a1,v0,0x20 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 002db430: sw v1,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002db434: sw a0,0x10(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(4));
L_002db438:;
/* 002db438: beq s2,zero,0x002db458 */ {int taken=(cpu(18)==cpu(0));/* delay 002db43c */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(5)));if(taken){goto L_002db458;}}
/* 002db440: li v1,0x35 */ set(3,sx(UINT32_C(0x00000035)));
/* 002db444: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
/* 002db448: addiu v0,v0,-0x433 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffbcd)));
/* 002db44c: b 0x002db478 */ /* delay 002db450 */ sw(ea(20,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_002db478;
L_002db458:;
/* 002db458: addiu v1,a1,-0x432 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0xfffffbce)));
/* 002db45c: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002db460: sw v1,0x0(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002db464: addu v0,s1,v0 */ set(2,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002db468: jal 0x002da8e0 */ set(31,0x002db470u);/* delay 002db46c */ lw(4,ea(2,(int32_t)UINT32_C(0xfffffffc)));nocturneBattlePanelRendererCall(UINT32_C(0x002da8e0),UINT32_C(0x002db468));
/* 002db470: sll v1,s0,0x5 */ set(3,sx((uint32_t)cpu(16)<<5));
/* 002db474: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
L_002db478:;
/* 002db478: sw v1,0x0(s5) */ sw(ea(21,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002db47c: move v0,s3 */ set(2,cpu(19));
/* 002db480: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002db484: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002db488: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002db48c: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002db490: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002db494: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002db498: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002db49c: jr ra */ {uint64_t target=cpu(31);/* delay 002db4a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_002db840(void){
nocturneEffectAxisNoteEntry(0x002db840u);
uint64_t incoming=cpu(31);
/* 002db840: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002db844: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002db848: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002db84c: jal 0x002d3be8 */ set(31,0x002db854u);/* delay 002db850 */ multiply(5,(uint32_t)cpu(5),(uint32_t)cpu(6),0);nocturneBattlePanelRendererCall(UINT32_C(0x002d3be8),UINT32_C(0x002db84c));
/* 002db854: move s0,v0 */ set(16,cpu(2));
/* 002db858: beq s0,zero,0x002db8e4 */ {int taken=(cpu(16)==cpu(0));/* delay 002db85c */ set(3,sx(UINT32_C(0xfffffffc)));if(taken){goto L_002db8e4;}}
/* 002db860: lw v0,-0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0xfffffffc)));
/* 002db864: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002db868: addiu a3,v0,-0x4 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffc)));
/* 002db86c: move a1,zero */ set(5,cpu(0));
/* 002db870: sltiu v0,a3,0x25 */ set(2,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000025));
/* 002db874: move a2,a3 */ set(6,cpu(7));
/* 002db878: move a0,s0 */ set(4,cpu(16));
/* 002db87c: beq v0,zero,0x002db8d8 */ {int taken=(cpu(2)==cpu(0));/* delay 002db880 */ set(8,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000014));if(taken){goto L_002db8d8;}}
/* 002db884: bne t0,zero,0x002db8c0 */ {int taken=(cpu(8)!=cpu(0));/* delay 002db888 */ set(3,cpu(16));if(taken){goto L_002db8c0;}}
/* 002db88c: sltiu v0,a3,0x1c */ set(2,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000001c));
/* 002db890: sw zero,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002db894: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002db898: bne v0,zero,0x002db8c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002db89c */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));if(taken){goto L_002db8c0;}}
/* 002db8a0: sltiu v0,a3,0x24 */ set(2,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000024));
/* 002db8a4: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002db8a8: addiu v1,s0,0x10 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002db8ac: bne v0,zero,0x002db8c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002db8b0 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));if(taken){goto L_002db8c0;}}
/* 002db8b4: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002db8b8: addiu v1,s0,0x18 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000018)));
/* 002db8bc: sw zero,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
L_002db8c0:;
/* 002db8c0: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002db8c4: addiu v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000004)));
/* 002db8c8: sw zero,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002db8cc: b 0x002db8e0 */ /* delay 002db8d0 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));goto L_002db8e0;
L_002db8d8:;
/* 002db8d8: jal 0x002d4558 */ set(31,0x002db8e0u);/* delay 002db8dc */ nocturneBattlePanelRendererCall(UINT32_C(0x002d4558),UINT32_C(0x002db8d8));
L_002db8e0:;
/* 002db8e0: move v0,s0 */ set(2,cpu(16));
L_002db8e4:;
/* 002db8e4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002db8e8: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002db8ec: jr ra */ {uint64_t target=cpu(31);/* delay 002db8f0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002dbd90(void){
nocturneEffectAxisNoteEntry(0x002dbd90u);
uint64_t incoming=cpu(31);
/* 002dbd90: li v1,0x2f */ set(3,sx(UINT32_C(0x0000002f)));
/* 002dbd94: syscall 0x0 */ nocturneBattlePanelRendererSyscall(UINT32_C(0x002dbd94),cpu(3),0,NULL);
/* 002dbd98: jr ra */ {uint64_t target=cpu(31);/* delay 002dbd9c */ checkReturn(target,incoming);return;}
}
static void body_002dbe80(void){
nocturneEffectAxisNoteEntry(0x002dbe80u);
uint64_t incoming=cpu(31);
/* 002dbe80: li v1,0x3e */ set(3,sx(UINT32_C(0x0000003e)));
/* 002dbe84: syscall 0x0 */ nocturneBattlePanelRendererSyscall(UINT32_C(0x002dbe84),cpu(3),0,NULL);
/* 002dbe88: jr ra */ {uint64_t target=cpu(31);/* delay 002dbe8c */ checkReturn(target,incoming);return;}
}
static void body_002dc5a0(void){
nocturneEffectAxisNoteEntry(0x002dc5a0u);
uint64_t incoming=cpu(31);
/* 002dc5a0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002dc5a4: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dc5a8: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dc5ac: sd s1,0x10(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dc5b0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dc5b4: mfc0 s1,Status */ set(17,sx(nocturneBattlePanelColorReadStatus(UINT32_C(0x002dc5b4))));
/* 002dc5b8: lui v0,0x1 */ set(2,sx(UINT32_C(0x00010000)));
/* 002dc5bc: and s1,s1,v0 */ set(17,cpu(17)&cpu(2));
/* 002dc5c0: beq s1,zero,0x002dc5ec */ {int taken=(cpu(17)==cpu(0));/* delay 002dc5c4 */ set(18,sx(UINT32_C(0x00530000)));if(taken){goto L_002dc5ec;}}
L_002dc5c8:;
/* 002dc5c8: di  */ nocturneBattlePanelColorDisableInterrupts(UINT32_C(0x002dc5c8));
/* 002dc5cc: sync 0x10 */ nocturneBattlePanelColorSync(16u,UINT32_C(0x002dc5cc));
/* 002dc5d0: mfc0 v0,Status */ set(2,sx(nocturneBattlePanelColorReadStatus(UINT32_C(0x002dc5d0))));
/* 002dc5d4: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 002dc5d8: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002dc5dc: bne v0,zero,0x002dc5c8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002dc5e0 */ if(taken){goto L_002dc5c8;}}
/* 002dc5e4: b 0x002dc5f0 */ /* delay 002dc5e8 */ lw(2,ea(18,(int32_t)UINT32_C(0xffffc2a8)));goto L_002dc5f0;
L_002dc5ec:;
/* 002dc5ec: lw v0,-0x3d58(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0xffffc2a8)));
L_002dc5f0:;
/* 002dc5f0: jal 0x002dbe80 */ set(31,0x002dc5f8u);/* delay 002dc5f4 */ set(16,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));nocturneBattlePanelRendererCall(UINT32_C(0x002dbe80),UINT32_C(0x002dc5f0));
/* 002dc5f8: sltu v0,v0,s0 */ set(2,cpu(2)<cpu(16));
/* 002dc5fc: beq v0,zero,0x002dc628 */ {int taken=(cpu(2)==cpu(0));/* delay 002dc600 */ lw(2,ea(18,(int32_t)UINT32_C(0xffffc2a8)));if(taken){goto L_002dc628;}}
/* 002dc604: jal 0x002e6e30 */ set(31,0x002dc60cu);/* delay 002dc608 */ nocturneBattlePanelRendererCall(UINT32_C(0x002e6e30),UINT32_C(0x002dc604));
/* 002dc60c: li v1,0xc */ set(3,sx(UINT32_C(0x0000000c)));
/* 002dc610: beq s1,zero,0x002dc61c */ {int taken=(cpu(17)==cpu(0));/* delay 002dc614 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_002dc61c;}}
/* 002dc618: ei  */ nocturneBattlePanelColorEnableInterrupts(UINT32_C(0x002dc618));
L_002dc61c:;
/* 002dc61c: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 002dc620: b 0x002dc634 */ /* delay 002dc624 */ set(2,cpu(2)|UINT32_C(0x0000ffff));goto L_002dc634;
L_002dc628:;
/* 002dc628: beq s1,zero,0x002dc634 */ {int taken=(cpu(17)==cpu(0));/* delay 002dc62c */ sw(ea(18,(int32_t)UINT32_C(0xffffc2a8)),(uint32_t)cpu(16));if(taken){goto L_002dc634;}}
/* 002dc630: ei  */ nocturneBattlePanelColorEnableInterrupts(UINT32_C(0x002dc630));
L_002dc634:;
/* 002dc634: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dc638: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dc63c: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dc640: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dc644: jr ra */ {uint64_t target=cpu(31);/* delay 002dc648 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002e6c48(void){
nocturneEffectAxisNoteEntry(0x002e6c48u);
uint64_t incoming=cpu(31);
/* 002e6c48: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002e6c4c: sd a0,0x40(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002e6c50: addiu a0,sp,0x40 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
/* 002e6c54: sd a1,0x48(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002e6c58: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002e6c5c: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002e6c60: jal 0x002d3578 */ set(31,0x002e6c68u);/* delay 002e6c64 */ set(5,cpu(29));nocturneBattlePanelRendererCall(UINT32_C(0x002d3578),UINT32_C(0x002e6c60));
/* 002e6c68: addiu s0,sp,0x20 */ set(16,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002e6c6c: addiu a0,sp,0x48 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000048)));
/* 002e6c70: jal 0x002d3578 */ set(31,0x002e6c78u);/* delay 002e6c74 */ set(5,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d3578),UINT32_C(0x002e6c70));
/* 002e6c78: lw a2,0x0(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002e6c7c: move t0,sp */ set(8,cpu(29));
/* 002e6c80: sltiu v0,a2,0x2 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002e6c84: bne v0,zero,0x002e6d70 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6c88 */ set(4,cpu(29));if(taken){goto L_002e6d70;}}
/* 002e6c8c: lw a1,0x20(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002e6c90: sltiu v0,a1,0x2 */ set(2,cpu(5)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002e6c94: bne v0,zero,0x002e6d70 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6c98 */ set(4,cpu(16));if(taken){goto L_002e6d70;}}
/* 002e6c9c: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002e6ca0: xori a0,a2,0x4 */ set(4,cpu(6)^UINT32_C(0x00000004));
/* 002e6ca4: lw v1,0x24(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 002e6ca8: xor v0,v0,v1 */ set(2,cpu(2)^cpu(3));
/* 002e6cac: beq a0,zero,0x002e6cc0 */ {int taken=(cpu(4)==cpu(0));/* delay 002e6cb0 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_002e6cc0;}}
/* 002e6cb4: xori v0,a2,0x2 */ set(2,cpu(6)^UINT32_C(0x00000002));
/* 002e6cb8: bne v0,zero,0x002e6cd8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e6cbc */ set(2,cpu(5)^UINT32_C(0x00000004));if(taken){goto L_002e6cd8;}}
L_002e6cc0:;
/* 002e6cc0: bnel a2,a1,0x002e6d70 */ {int taken=(cpu(6)!=cpu(5));if(taken){/* delay 002e6cc4 */ set(4,cpu(29));goto L_002e6d70;}}
/* 002e6cc8: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002e6ccc: b 0x002e6d70 */ /* delay 002e6cd0 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0xffffb460)));goto L_002e6d70;
L_002e6cd8:;
/* 002e6cd8: bnel v0,zero,0x002e6cf0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002e6cdc */ set(2,cpu(5)^UINT32_C(0x00000002));goto L_002e6cf0;}}
/* 002e6ce0: sd zero,0x10(sp) */ save(0,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002e6ce4: move a0,sp */ set(4,cpu(29));
/* 002e6ce8: b 0x002e6d70 */ /* delay 002e6cec */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));goto L_002e6d70;
L_002e6cf0:;
/* 002e6cf0: bnel v0,zero,0x002e6d08 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002e6cf4 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000008)));goto L_002e6d08;}}
/* 002e6cf8: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 002e6cfc: move a0,sp */ set(4,cpu(29));
/* 002e6d00: b 0x002e6d70 */ /* delay 002e6d04 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_002e6d70;
L_002e6d08:;
/* 002e6d08: lw v0,0x28(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002e6d0c: ld a0,0x10(sp) */ restore(4,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002e6d10: ld a2,0x30(sp) */ restore(6,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002e6d14: subu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 002e6d18: sltu a1,a0,a2 */ set(5,cpu(4)<cpu(6));
/* 002e6d1c: beq a1,zero,0x002e6d34 */ {int taken=(cpu(5)==cpu(0));/* delay 002e6d20 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002e6d34;}}
/* 002e6d24: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002e6d28: dsll a0,a0,0x1 */ set(4,cpu(4)<<1);
/* 002e6d2c: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002e6d30: sltu a1,a0,a2 */ set(5,cpu(4)<cpu(6));
L_002e6d34:;
/* 002e6d34: ori v1,zero,0x8000 */ set(3,cpu(0)|UINT32_C(0x00008000));
/* 002e6d38: dsll32 v1,v1,0xd */ set(3,cpu(3)<<45);
/* 002e6d3c: move a3,zero */ set(7,cpu(0));
L_002e6d40:;
/* 002e6d40: bne a1,zero,0x002e6d58 */ {int taken=(cpu(5)!=cpu(0));/* delay 002e6d44 */ set(2,cpu(4)<<1);if(taken){goto L_002e6d58;}}
/* 002e6d48: dsubu a0,a0,a2 */ set(4,cpu(4)-cpu(6));
/* 002e6d4c: or a3,a3,v1 */ set(7,cpu(7)|cpu(3));
/* 002e6d50: dsll v0,a0,0x1 */ set(2,cpu(4)<<1);
/* 002e6d54: nop  */ 
L_002e6d58:;
/* 002e6d58: dsrl v1,v1,0x1 */ set(3,cpu(3)>>1);
/* 002e6d5c: sltu a1,v0,a2 */ set(5,cpu(2)<cpu(6));
/* 002e6d60: bne v1,zero,0x002e6d40 */ {int taken=(cpu(3)!=cpu(0));/* delay 002e6d64 */ set(4,cpu(2));if(taken){goto L_002e6d40;}}
/* 002e6d68: sd a3,0x10(t0) */ save(7,ea(8,(int32_t)UINT32_C(0x00000010)));
/* 002e6d6c: move a0,t0 */ set(4,cpu(8));
L_002e6d70:;
/* 002e6d70: jal 0x002d34a0 */ set(31,0x002e6d78u);/* delay 002e6d74 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d34a0),UINT32_C(0x002e6d70));
/* 002e6d78: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002e6d7c: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002e6d80: jr ra */ {uint64_t target=cpu(31);/* delay 002e6d84 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_002e6e30(void){
nocturneEffectAxisNoteEntry(0x002e6e30u);
uint64_t incoming=cpu(31);
/* 002e6e30: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002e6e34: jr ra */ {uint64_t target=cpu(31);/* delay 002e6e38 */ lw(2,ea(3,(int32_t)UINT32_C(0xffffbe28)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelRendererExisting1(uint32_t entry){switch(entry){case UINT32_C(0x002d3990):(void)body_002d3990();return 1u;case UINT32_C(0x002d3be8):(void)body_002d3be8();return 1u;case UINT32_C(0x002d43a4):(void)body_002d43a4();return 1u;case UINT32_C(0x002d4618):(void)body_002d4618();return 1u;case UINT32_C(0x002d4698):(void)body_002d4698();return 1u;case UINT32_C(0x002d5250):(void)body_002d5250();return 1u;case UINT32_C(0x002d7ce8):(void)body_002d7ce8();return 1u;case UINT32_C(0x002d8148):(void)body_002d8148();return 1u;case UINT32_C(0x002d8378):(void)body_002d8378();return 1u;case UINT32_C(0x002d9998):(void)body_002d9998();return 1u;case UINT32_C(0x002d9c90):(void)body_002d9c90();return 1u;case UINT32_C(0x002da5d0):(void)body_002da5d0();return 1u;case UINT32_C(0x002da678):(void)body_002da678();return 1u;case UINT32_C(0x002da6a8):(void)body_002da6a8();return 1u;case UINT32_C(0x002da8e0):(void)body_002da8e0();return 1u;case UINT32_C(0x002da960):(void)body_002da960();return 1u;case UINT32_C(0x002daa20):(void)body_002daa20();return 1u;case UINT32_C(0x002daa58):(void)body_002daa58();return 1u;case UINT32_C(0x002dac68):(void)body_002dac68();return 1u;case UINT32_C(0x002dad68):(void)body_002dad68();return 1u;case UINT32_C(0x002daec0):(void)body_002daec0();return 1u;case UINT32_C(0x002daf28):(void)body_002daf28();return 1u;case UINT32_C(0x002db320):(void)body_002db320();return 1u;case UINT32_C(0x002db840):(void)body_002db840();return 1u;case UINT32_C(0x002dbd90):(void)body_002dbd90();return 1u;case UINT32_C(0x002dbe80):(void)body_002dbe80();return 1u;case UINT32_C(0x002dc5a0):(void)body_002dc5a0();return 1u;case UINT32_C(0x002e6c48):(void)body_002e6c48();return 1u;case UINT32_C(0x002e6e30):(void)body_002e6e30();return 1u;default:return 0u;}}
