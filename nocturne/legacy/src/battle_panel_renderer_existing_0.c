#include "battle_panel_renderer_bundle.h"
#include "battle_panel_color_native.h"
#include "battle_panel_color_privileged.h"
/* Complete fixed original formula/helper49 native dependencies.
 * Shared live CPU/FPR/RAM, true guest frames and native volatile carry into
 * printf are preserved. No expected data, stack patch or game-result provider.
 */
#include "battle_action_formula_frames.h"
#include "battle_action_packet_frames.h"
#include "battle_action_printf_frames.h"
#include "effect_soft_double_frames.h"
#include "effect_soft_double_adaptive_frames.h"
#include "magatuhi_helpers.h"
#include "pcp_effect_helpers.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "battle_action_consumer.h"
#include "battle_action_scale_lookup_frames.h"
#include "effect_host_bindings.h"
#include "effect_model_child_dependency_frames.h"
#include "effect_random_frames.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include "nocturne.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
extern uint64_t nocturneEffectHostHi(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattlePanelColorAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}


static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}


static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelColorSetStackPointer(q[0]);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}

static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


extern uint64_t nocturneEffectHostLo(void);
/* Secondary HI1/LO1 uses the actual canonical Formula owner only. */






static void nativeMultiply(unsigned rd,uint32_t a,uint32_t v,int isSigned,int secondary){
 uint64_t product=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)v):(uint64_t)a*v;
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)product),sx((uint32_t)(product>>32)));else EE_MAGATUHI_MULT_STATE(product);
 if(rd)set(rd,sx((uint32_t)product));
}


void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);

static void body_002d18b0(void){
nocturneEffectAxisNoteEntry(0x002d18b0u);
uint64_t incoming=cpu(31);
/* 002d18b0: addiu sp,sp,-0xb0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff50)));
/* 002d18b4: sd a0,0x60(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d18b8: addiu a0,sp,0x60 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 002d18bc: sd a1,0x68(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002d18c0: sd s0,0x70(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d18c4: sd s1,0x78(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d18c8: sd s2,0x80(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002d18cc: sd s3,0x88(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002d18d0: sd s4,0x90(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002d18d4: sd s5,0x98(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002d18d8: sd s6,0xa0(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002d18dc: sd ra,0xa8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002d18e0: jal 0x002d3578 */ set(31,0x002d18e8u);/* delay 002d18e4 */ set(5,cpu(29));nocturneBattlePanelRendererCall(UINT32_C(0x002d3578),UINT32_C(0x002d18e0));
/* 002d18e8: addiu s0,sp,0x20 */ set(16,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d18ec: addiu a0,sp,0x68 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000068)));
/* 002d18f0: jal 0x002d3578 */ set(31,0x002d18f8u);/* delay 002d18f4 */ set(5,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d3578),UINT32_C(0x002d18f0));
/* 002d18f8: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d18fc: sltiu v0,a0,0x2 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d1900: bne v0,zero,0x002d1964 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d1904 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_002d1964;}}
/* 002d1908: lw v1,0x20(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d190c: sltiu v0,v1,0x2 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d1910: bnel v0,zero,0x002d198c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d1914 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000024)));goto L_002d198c;}}
/* 002d1918: xori v0,a0,0x4 */ set(2,cpu(4)^UINT32_C(0x00000004));
/* 002d191c: bne v0,zero,0x002d1938 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d1920 */ set(2,cpu(3)^UINT32_C(0x00000004));if(taken){goto L_002d1938;}}
/* 002d1924: xori v0,v1,0x2 */ set(2,cpu(3)^UINT32_C(0x00000002));
/* 002d1928: bnel v0,zero,0x002d1964 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d192c */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));goto L_002d1964;}}
/* 002d1930: b 0x002d194c */ /* delay 002d1934 */ set(2,sx(UINT32_C(0x00550000)));goto L_002d194c;
L_002d1938:;
/* 002d1938: bne v0,zero,0x002d1958 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d193c */ set(2,cpu(4)^UINT32_C(0x00000002));if(taken){goto L_002d1958;}}
/* 002d1940: bnel v0,zero,0x002d198c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d1944 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000024)));goto L_002d198c;}}
/* 002d1948: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
L_002d194c:;
/* 002d194c: b 0x002d1b04 */ /* delay 002d1950 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0xffffb460)));goto L_002d1b04;
L_002d1958:;
/* 002d1958: bne v0,zero,0x002d1980 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d195c */ set(2,cpu(3)^UINT32_C(0x00000002));if(taken){goto L_002d1980;}}
/* 002d1960: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
L_002d1964:;
/* 002d1964: move a0,sp */ set(4,cpu(29));
/* 002d1968: lw v1,0x24(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 002d196c: xor v0,v0,v1 */ set(2,cpu(2)^cpu(3));
/* 002d1970: sltu v0,zero,v0 */ set(2,cpu(0)<cpu(2));
/* 002d1974: b 0x002d1b04 */ /* delay 002d1978 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002d1b04;
L_002d1980:;
/* 002d1980: bne v0,zero,0x002d19a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d1984 */ restore(19,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002d19a8;}}
/* 002d1988: lw v1,0x24(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000024)));
L_002d198c:;
/* 002d198c: move a0,s0 */ set(4,cpu(16));
/* 002d1990: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002d1994: xor v0,v0,v1 */ set(2,cpu(2)^cpu(3));
/* 002d1998: sltu v0,zero,v0 */ set(2,cpu(0)<cpu(2));
/* 002d199c: b 0x002d1b04 */ /* delay 002d19a0 */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));goto L_002d1b04;
L_002d19a8:;
/* 002d19a8: lui s5,0xffff */ set(21,sx(UINT32_C(0xffff0000)));
/* 002d19ac: dsrl32 s5,s5,0x0 */ set(21,cpu(21)>>32);
/* 002d19b0: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d19b4: and s0,s3,s5 */ set(16,cpu(19)&cpu(21));
/* 002d19b8: dsrl32 s3,s3,0x0 */ set(19,cpu(19)>>32);
/* 002d19bc: and s6,s2,s5 */ set(22,cpu(18)&cpu(21));
/* 002d19c0: dsrl32 s2,s2,0x0 */ set(18,cpu(18)>>32);
/* 002d19c4: move a1,s0 */ set(5,cpu(16));
/* 002d19c8: jal 0x002d3398 */ set(31,0x002d19d0u);/* delay 002d19cc */ set(4,cpu(22));nocturneBattlePanelRendererCall(UINT32_C(0x002d3398),UINT32_C(0x002d19c8));
/* 002d19d0: move a0,s2 */ set(4,cpu(18));
/* 002d19d4: move a1,s0 */ set(5,cpu(16));
/* 002d19d8: jal 0x002d3398 */ set(31,0x002d19e0u);/* delay 002d19dc */ set(20,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002d3398),UINT32_C(0x002d19d8));
/* 002d19e0: move a0,s6 */ set(4,cpu(22));
/* 002d19e4: move a1,s3 */ set(5,cpu(19));
/* 002d19e8: jal 0x002d3398 */ set(31,0x002d19f0u);/* delay 002d19ec */ set(17,cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002d3398),UINT32_C(0x002d19e8));
/* 002d19f0: move a0,s2 */ set(4,cpu(18));
/* 002d19f4: move s0,v0 */ set(16,cpu(2));
/* 002d19f8: move a1,s3 */ set(5,cpu(19));
/* 002d19fc: jal 0x002d3398 */ set(31,0x002d1a04u);/* delay 002d1a00 */ set(16,cpu(17)+cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d3398),UINT32_C(0x002d19fc));
/* 002d1a04: sltu s1,s0,s1 */ set(17,cpu(16)<cpu(17));
/* 002d1a08: dsll32 a2,s0,0x0 */ set(6,cpu(16)<<32);
/* 002d1a0c: dsrl32 s0,s0,0x0 */ set(16,cpu(16)>>32);
/* 002d1a10: daddu a2,s4,a2 */ set(6,cpu(20)+cpu(6));
/* 002d1a14: and s0,s0,s5 */ set(16,cpu(16)&cpu(21));
/* 002d1a18: dsll32 s1,s1,0x0 */ set(17,cpu(17)<<32);
/* 002d1a1c: daddu s0,s0,v0 */ set(16,cpu(16)+cpu(2));
/* 002d1a20: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002d1a24: sltu s4,a2,s4 */ set(20,cpu(6)<cpu(20));
/* 002d1a28: lw a0,0x8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d1a2c: lw a3,0x28(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d1a30: daddu s1,s1,s4 */ set(17,cpu(17)+cpu(20));
/* 002d1a34: lw a1,0x24(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 002d1a38: daddu s1,s1,s0 */ set(17,cpu(17)+cpu(16));
/* 002d1a3c: addu a0,a0,a3 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 002d1a40: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002d1a44: dsrl v1,v1,0x3 */ set(3,cpu(3)>>3);
/* 002d1a48: xor v0,v0,a1 */ set(2,cpu(2)^cpu(5));
/* 002d1a4c: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 002d1a50: sltu v0,zero,v0 */ set(2,cpu(0)<cpu(2));
/* 002d1a54: sltu v1,v1,s1 */ set(3,cpu(3)<cpu(17));
/* 002d1a58: sw v0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 002d1a5c: beq v1,zero,0x002d1aa4 */ {int taken=(cpu(3)==cpu(0));/* delay 002d1a60 */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(4));if(taken){goto L_002d1aa4;}}
/* 002d1a64: ori a3,zero,0x8000 */ set(7,cpu(0)|UINT32_C(0x00008000));
/* 002d1a68: dsll32 a3,a3,0x10 */ set(7,cpu(7)<<48);
/* 002d1a6c: li a1,-0x1 */ set(5,sx(UINT32_C(0xffffffff)));
/* 002d1a70: dsrl a1,a1,0x3 */ set(5,cpu(5)>>3);
/* 002d1a74: andi v0,s1,0x1 */ set(2,cpu(17)&UINT32_C(0x00000001));
L_002d1a78:;
/* 002d1a78: dsrl s1,s1,0x1 */ set(17,cpu(17)>>1);
/* 002d1a7c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d1a80: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d1a84: sltu v1,a1,s1 */ set(3,cpu(5)<cpu(17));
/* 002d1a88: beq v0,zero,0x002d1a98 */ {int taken=(cpu(2)==cpu(0));/* delay 002d1a8c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));if(taken){goto L_002d1a98;}}
/* 002d1a90: dsrl a2,a2,0x1 */ set(6,cpu(6)>>1);
/* 002d1a94: or a2,a2,a3 */ set(6,cpu(6)|cpu(7));
L_002d1a98:;
/* 002d1a98: bne v1,zero,0x002d1a78 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d1a9c */ set(2,cpu(17)&UINT32_C(0x00000001));if(taken){goto L_002d1a78;}}
/* 002d1aa0: sw a0,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(4));
L_002d1aa4:;
/* 002d1aa4: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d1aa8: dsrl v0,v0,0x4 */ set(2,cpu(2)>>4);
/* 002d1aac: sltu v0,v0,s1 */ set(2,cpu(2)<cpu(17));
/* 002d1ab0: bne v0,zero,0x002d1af8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d1ab4 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002d1af8;}}
/* 002d1ab8: lw a0,0x48(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d1abc: ori t0,zero,0x8000 */ set(8,cpu(0)|UINT32_C(0x00008000));
/* 002d1ac0: dsll32 t0,t0,0x10 */ set(8,cpu(8)<<48);
/* 002d1ac4: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 002d1ac8: li a1,-0x1 */ set(5,sx(UINT32_C(0xffffffff)));
/* 002d1acc: dsrl a1,a1,0x4 */ set(5,cpu(5)>>4);
L_002d1ad0:;
/* 002d1ad0: dsll s1,s1,0x1 */ set(17,cpu(17)<<1);
/* 002d1ad4: and v1,a2,t0 */ set(3,cpu(6)&cpu(8));
/* 002d1ad8: or v0,s1,a3 */ set(2,cpu(17)|cpu(7));
/* 002d1adc: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 002d1ae0: movn s1,v0,v1 */ if(cpu(3)!=0){set(17,cpu(2));}
/* 002d1ae4: sltu v0,a1,s1 */ set(2,cpu(5)<cpu(17));
/* 002d1ae8: beq v0,zero,0x002d1ad0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d1aec */ set(6,cpu(6)<<1);if(taken){goto L_002d1ad0;}}
/* 002d1af0: sw a0,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(4));
/* 002d1af4: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
L_002d1af8:;
/* 002d1af8: sd s1,0x50(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d1afc: sw v0,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
/* 002d1b00: addiu a0,sp,0x40 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
L_002d1b04:;
/* 002d1b04: jal 0x002d34a0 */ set(31,0x002d1b0cu);/* delay 002d1b08 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d34a0),UINT32_C(0x002d1b04));
/* 002d1b0c: ld s0,0x70(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d1b10: ld s1,0x78(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d1b14: ld s2,0x80(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002d1b18: ld s3,0x88(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002d1b1c: ld s4,0x90(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002d1b20: ld s5,0x98(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002d1b24: ld s6,0xa0(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002d1b28: ld ra,0xa8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002d1b2c: jr ra */ {uint64_t target=cpu(31);/* delay 002d1b30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000b0)));checkReturn(target,incoming);return;}
}
static void body_002d3398(void){
nocturneEffectAxisNoteEntry(0x002d3398u);
uint64_t incoming=cpu(31);
/* 002d3398: dsll32 v0,a1,0x0 */ set(2,cpu(5)<<32);
/* 002d339c: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d33a0: dsra32 a1,a1,0x0 */ set(5,(uint64_t)((int64_t)cpu(5)>>32));
/* 002d33a4: dsll32 v1,a0,0x0 */ set(3,cpu(4)<<32);
/* 002d33a8: dsra32 v1,v1,0x0 */ set(3,(uint64_t)((int64_t)cpu(3)>>32));
/* 002d33ac: multu v1,v0 */ nativeMultiply(0,(uint32_t)cpu(3),(uint32_t)cpu(2),0,0);
/* 002d33b0: mflo a2 */ set(6,nocturneEffectHostLo());
/* 002d33b4: mfhi t0 */ set(8,nocturneEffectHostHi());
/* 002d33b8: dsll32 a2,a2,0x0 */ set(6,cpu(6)<<32);
/* 002d33bc: dsra32 a0,a0,0x0 */ set(4,(uint64_t)((int64_t)cpu(4)>>32));
/* 002d33c0: mult v1,v1,a1 */ nativeMultiply(3,(uint32_t)cpu(3),(uint32_t)cpu(5),1,0);
/* 002d33c4: li a1,-0x1 */ set(5,sx(UINT32_C(0xffffffff)));
/* 002d33c8: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002d33cc: mult1 a0,a0,v0 */ nativeMultiply(4,(uint32_t)cpu(4),(uint32_t)cpu(2),1,1);
/* 002d33d0: dsrl32 a2,a2,0x0 */ set(6,cpu(6)>>32);
/* 002d33d4: and t1,t1,a1 */ set(9,cpu(9)&cpu(5));
/* 002d33d8: lui a3,0xffff */ set(7,sx(UINT32_C(0xffff0000)));
/* 002d33dc: dsrl32 a3,a3,0x0 */ set(7,cpu(7)>>32);
/* 002d33e0: or t1,t1,a2 */ set(9,cpu(9)|cpu(6));
/* 002d33e4: dsll32 t0,t0,0x0 */ set(8,cpu(8)<<32);
/* 002d33e8: and t1,t1,a3 */ set(9,cpu(9)&cpu(7));
/* 002d33ec: or t1,t1,t0 */ set(9,cpu(9)|cpu(8));
/* 002d33f0: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002d33f4: dsra32 v0,t1,0x0 */ set(2,(uint64_t)((int64_t)cpu(9)>>32));
/* 002d33f8: and a3,t1,a3 */ set(7,cpu(9)&cpu(7));
/* 002d33fc: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002d3400: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d3404: jr ra */ {uint64_t target=cpu(31);/* delay 002d3408 */ set(2,cpu(7)|cpu(2));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelRendererExisting0(uint32_t entry){switch(entry){case UINT32_C(0x002d18b0):(void)body_002d18b0();return 1u;case UINT32_C(0x002d3398):(void)body_002d3398();return 1u;default:return 0u;}}
