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
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


extern uint64_t nocturneEffectHostLo(void);
/* The retained semantic profile does not expose secondary HI1/LO1 through
 * the shared host ABI. Keep its actual state separate from primary HI/LO;
 * MFLO1 and native RD consume it at their original instruction positions.
 * This is not a claim of externally observed volatile HI1 equivalence. */
static uint64_t secondaryLo,secondaryHi;
uint64_t nocturneBattleActionFormulaSecondaryLo(void){return secondaryLo;}
uint64_t nocturneBattleActionFormulaSecondaryHi(void){return secondaryHi;}
void nocturneBattleActionFormulaSecondaryWrite(uint64_t loValue,uint64_t hiValue){secondaryLo=loValue;secondaryHi=hiValue;}
static float real(uint32_t u){float v;memcpy(&v,&u,4);return v;}
static void nativeDivide(uint32_t a,uint32_t d,int isSigned,int secondary){
 uint32_t q,r;
 if(!d){q=isSigned&&((int32_t)a<0)?1u:UINT32_MAX;r=a;}
 else if(isSigned&&a==UINT32_C(0x80000000)&&d==UINT32_MAX){q=a;r=0;}
 else if(isSigned){q=(uint32_t)((int32_t)a/(int32_t)d);r=(uint32_t)((int32_t)a%(int32_t)d);}
 else{q=a/d;r=a%d;}
 if(secondary){secondaryLo=sx(q);secondaryHi=sx(r);}else EE_PCP_EFFECT_DIV_STATE(q,r);
}
static void nativeMultiply(unsigned rd,uint32_t a,uint32_t v,int isSigned,int secondary){
 uint64_t product=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)v):(uint64_t)a*v;
 if(secondary){secondaryLo=sx((uint32_t)product);secondaryHi=sx((uint32_t)(product>>32));}else EE_MAGATUHI_MULT_STATE(product);
 if(rd)set(rd,sx((uint32_t)product));
}

static void body_001e0f50(void);
static void body_001e9998(void);
static void body_00242a88(void);
static void body_00242b68(void);
static void body_00242d18(void);
static void body_00243bd0(void);
static void body_00243c10(void);
static void body_00243e78(void);
static void body_00243ee0(void);
static void body_00243f40(void);
static void body_00243fe8(void);
static void body_002440c0(void);
static void body_002515d8(void);
static void body_002516e8(void);
static void body_002517e0(void);
static void body_00262f58(void);
static void body_002654b8(void);
static void body_00266130(void);
static void body_00266350(void);
static void body_00266878(void);
static void body_00266c90(void);
static void body_00266cd8(void);
static void body_00266d20(void);
static void body_00266d60(void);
static void body_00267180(void);
static void body_00267370(void);
static void body_00267388(void);
static void body_00267390(void);
static void body_002674d0(void);
static void body_00267530(void);
static void body_00267890(void);
static void body_00267e38(void);
static void body_00267e90(void);
static void body_002684b0(void);
static void body_00268620(void);
static void body_002688b8(void);
static void body_002688d0(void);
static void body_00268c60(void);
static void body_00268d60(void);
static void body_0026a2d8(void);
static void body_0026a338(void);
static void body_0026a398(void);
static void body_0026a3d8(void);
static void body_0026a468(void);
static void body_0026a470(void);
static void body_0026a828(void);
static void body_002c0c00(void);
static void body_002d18b0(void);
static void body_002d3398(void);
static void body_001e0f50(void){
nocturneEffectAxisNoteEntry(0x001e0f50u);
uint64_t incoming=cpu(31);
/* 001e0f50: slti v0,a0,0x0 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001e0f54: addiu a1,a0,0x1f */ set(5,sx((uint32_t)cpu(4)+UINT32_C(0x0000001f)));
/* 001e0f58: move v1,a0 */ set(3,cpu(4));
/* 001e0f5c: lw a2,-0x5750(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e0f60: movn v1,a1,v0 */ if(cpu(2)!=0){set(3,cpu(5));}
/* 001e0f64: sra v1,v1,0x5 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>5)));
/* 001e0f68: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001e0f6c: addu v1,v1,a2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
/* 001e0f70: lw v0,0x840(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000840)));
/* 001e0f74: srav v0,v0,a0 */ set(2,sx((uint32_t)((int32_t)(uint32_t)cpu(2)>>((uint32_t)cpu(4)&31u))));
/* 001e0f78: jr ra */ {uint64_t target=cpu(31);/* delay 001e0f7c */ set(2,cpu(2)&UINT32_C(0x00000001));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_001E0F50(uint64_t a0){
set(4,a0);
body_001e0f50();
return cpu(2);
}
static void body_001e9998(void){
nocturneEffectAxisNoteEntry(0x001e9998u);
uint64_t incoming=cpu(31);
/* 001e9998: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e999c: lbu v0,0xa41(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0x00000a41))));
/* 001e99a0: slti v1,v0,0x9 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 001e99a4: bne v1,zero,0x001e99b4 */ {int taken=(cpu(3)!=cpu(0));/* delay 001e99a8 */ set(4,cpu(2)&UINT32_C(0x00000007));if(taken){goto L_001e99b4;}}
/* 001e99ac: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 001e99b0: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
L_001e99b4:;
/* 001e99b4: jr ra */ {uint64_t target=cpu(31);/* delay 001e99b8 */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_001E9998(void){

body_001e9998();
return cpu(2);
}
static void body_00242a88(void){
nocturneEffectAxisNoteEntry(0x00242a88u);
uint64_t incoming=cpu(31);
/* 00242a88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00242a8c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242a90: move s0,a0 */ set(16,cpu(4));
/* 00242a94: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00242a98: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242a9c: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00242aa0: jal 0x00243ee0 */ set(31,0x00242aa8u);/* delay 00242aa4 */ set(5,sx(UINT32_C(0x00000003)));body_00243ee0();
/* 00242aa8: lhu v1,0x14(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 00242aac: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00242ab0: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 00242ab4: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00242ab8: sll a1,v0,0x1 */ set(5,sx((uint32_t)cpu(2)<<1));
/* 00242abc: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00242ac0: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00242ac4: bne v0,zero,0x00242ad8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00242ac8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00242ad8;}}
/* 00242acc: slti v1,a1,0x3e8 */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x000003e8));
/* 00242ad0: li v0,0x3e7 */ set(2,sx(UINT32_C(0x000003e7)));
/* 00242ad4: movz a1,v0,v1 */ if(cpu(3)==0){set(5,cpu(2));}
L_00242ad8:;
/* 00242ad8: move v0,a1 */ set(2,cpu(5));
/* 00242adc: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242ae0: jr ra */ {uint64_t target=cpu(31);/* delay 00242ae4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00242A88(uint64_t a0){
set(4,a0);
body_00242a88();
return cpu(2);
}
static void body_00242b68(void){
nocturneEffectAxisNoteEntry(0x00242b68u);
uint64_t incoming=cpu(31);
/* 00242b68: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00242b6c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242b70: move s0,a0 */ set(16,cpu(4));
/* 00242b74: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00242b78: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242b7c: andi v1,v0,0x20 */ set(3,cpu(2)&UINT32_C(0x00000020));
/* 00242b80: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00242b84: jal 0x00243ee0 */ set(31,0x00242b8cu);/* delay 00242b88 */ set(5,cpu(0));body_00243ee0();
/* 00242b8c: lhu v1,0x14(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 00242b90: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00242b94: sll a1,v0,0x1 */ set(5,sx((uint32_t)cpu(2)<<1));
/* 00242b98: lhu v0,0xe(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 00242b9c: li v1,0x40 */ set(3,sx(UINT32_C(0x00000040)));
/* 00242ba0: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 00242ba4: bne v0,v1,0x00242bb8 */ {int taken=(cpu(2)!=cpu(3));/* delay 00242ba8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00242bb8;}}
/* 00242bac: srl v0,a1,0x1f */ set(2,sx((uint32_t)cpu(5)>>31));
/* 00242bb0: addu v0,a1,v0 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 00242bb4: sra a1,v0,0x1 */ set(5,sx((uint32_t)((int32_t)cpu(2)>>1)));
L_00242bb8:;
/* 00242bb8: move v0,a1 */ set(2,cpu(5));
/* 00242bbc: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242bc0: jr ra */ {uint64_t target=cpu(31);/* delay 00242bc4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00242B68(uint64_t a0){
set(4,a0);
body_00242b68();
return cpu(2);
}
static void body_00242d18(void){
nocturneEffectAxisNoteEntry(0x00242d18u);
uint64_t incoming=cpu(31);
/* 00242d18: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00242d1c: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 00242d20: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242d24: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242d28: jal 0x00243ee0 */ set(31,0x00242d30u);/* delay 00242d2c */ set(16,cpu(4));body_00243ee0();
/* 00242d30: lhu v1,0x14(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 00242d34: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242d38: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00242d3c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242d40: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00242d44: jr ra */ {uint64_t target=cpu(31);/* delay 00242d48 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00242D18(uint64_t a0){
set(4,a0);
body_00242d18();
return cpu(2);
}
static void body_00243bd0(void){
nocturneEffectAxisNoteEntry(0x00243bd0u);
uint64_t incoming=cpu(31);
/* 00243bd0: ori v0,zero,0x8000 */ set(2,cpu(0)|UINT32_C(0x00008000));
/* 00243bd4: bne a1,v0,0x00243be8 */ {int taken=(cpu(5)!=cpu(2));/* delay 00243bd8 */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000000e))));if(taken){goto L_00243be8;}}
/* 00243bdc: ori v0,v0,0x8000 */ set(2,cpu(2)|UINT32_C(0x00008000));
/* 00243be0: jr ra */ {uint64_t target=cpu(31);/* delay 00243be4 */ sh(ea(4,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(2));checkReturn(target,incoming);return;}
L_00243be8:;
/* 00243be8: andi v1,v0,0xf000 */ set(3,cpu(2)&UINT32_C(0x0000f000));
/* 00243bec: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 00243bf0: sltu v0,v0,a1 */ set(2,cpu(2)<cpu(5));
/* 00243bf4: beq v0,zero,0x00243c04 */ {int taken=(cpu(2)==cpu(0));/* delay 00243bf8 */ set(2,cpu(5)&UINT32_C(0x00000fff));if(taken){goto L_00243c04;}}
/* 00243bfc: or v0,v1,v0 */ set(2,cpu(3)|cpu(2));
/* 00243c00: sh v0,0xe(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(2));
L_00243c04:;
/* 00243c04: jr ra */ {uint64_t target=cpu(31);/* delay 00243c08 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionFormula_00243BD0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00243bd0();
return;
}
static void body_00243c10(void){
nocturneEffectAxisNoteEntry(0x00243c10u);
uint64_t incoming=cpu(31);
/* 00243c10: lhu v0,0xe(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000000e))));
/* 00243c14: nor a1,zero,a1 */ set(5,~(cpu(0)|cpu(5)));
/* 00243c18: and v0,v0,a1 */ set(2,cpu(2)&cpu(5));
/* 00243c1c: jr ra */ {uint64_t target=cpu(31);/* delay 00243c20 */ sh(ea(4,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(2));checkReturn(target,incoming);return;}
}
void ps2BattleActionFormula_00243C10(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00243c10();
return;
}
static void body_00243e78(void){
nocturneEffectAxisNoteEntry(0x00243e78u);
uint64_t incoming=cpu(31);
/* 00243e78: addiu v0,a1,0x10 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 00243e7c: addu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 00243e80: addu t0,a0,v0 */ set(8,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00243e84: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00243e88: move a3,t0 */ set(7,cpu(8));
/* 00243e8c: move a2,a3 */ set(6,cpu(7));
/* 00243e90: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00243e94: beq v0,zero,0x00243eb0 */ {int taken=(cpu(2)==cpu(0));/* delay 00243e98 */ set(3,cpu(6));if(taken){goto L_00243eb0;}}
/* 00243e9c: lb v1,0x6(a2) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000006))));
/* 00243ea0: lb v0,0xc(t0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(8,(int32_t)UINT32_C(0x0000000c))));
/* 00243ea4: b 0x00243ec4 */ /* delay 00243ea8 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));goto L_00243ec4;
L_00243eb0:;
/* 00243eb0: lb v0,0x6(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000006))));
/* 00243eb4: lb v1,0xc(a3) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(7,(int32_t)UINT32_C(0x0000000c))));
/* 00243eb8: lb a0,0x7a(a1) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x0000007a))));
/* 00243ebc: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00243ec0: addu a2,v0,a0 */ set(6,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
L_00243ec4:;
/* 00243ec4: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00243ec8: slt a0,zero,a2 */ set(4,(int64_t)cpu(0)<(int64_t)cpu(6));
/* 00243ecc: movz a2,a1,a0 */ if(cpu(4)==0){set(6,cpu(5));}
/* 00243ed0: li v0,0x28 */ set(2,sx(UINT32_C(0x00000028)));
/* 00243ed4: slti v1,a2,0x29 */ set(3,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000029));
/* 00243ed8: jr ra */ {uint64_t target=cpu(31);/* delay 00243edc */ if(cpu(3)!=0){set(2,cpu(6));}checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00243E78(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00243e78();
return cpu(2);
}
static void body_00243ee0(void){
nocturneEffectAxisNoteEntry(0x00243ee0u);
uint64_t incoming=cpu(31);
/* 00243ee0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00243ee4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243ee8: move s0,a0 */ set(16,cpu(4));
/* 00243eec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243ef0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243ef4: jal 0x00243e78 */ set(31,0x00243efcu);/* delay 00243ef8 */ set(17,cpu(5));body_00243e78();
/* 00243efc: move a0,v0 */ set(4,cpu(2));
/* 00243f00: lhu v0,0xe(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 00243f04: li v1,0x200 */ set(3,sx(UINT32_C(0x00000200)));
/* 00243f08: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 00243f0c: bne v0,v1,0x00243f1c */ {int taken=(cpu(2)!=cpu(3));/* delay 00243f10 */ set(17,cpu(17)^UINT32_C(0x00000004));if(taken){goto L_00243f1c;}}
/* 00243f14: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00243f18: movn a0,v0,s1 */ if(cpu(17)!=0){set(4,cpu(2));}
L_00243f1c:;
/* 00243f1c: slt v1,zero,a0 */ set(3,(int64_t)cpu(0)<(int64_t)cpu(4));
/* 00243f20: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00243f24: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243f28: movn v0,a0,v1 */ if(cpu(3)!=0){set(2,cpu(4));}
/* 00243f2c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243f30: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243f34: jr ra */ {uint64_t target=cpu(31);/* delay 00243f38 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00243EE0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00243ee0();
return cpu(2);
}
static void body_00243f40(void){
nocturneEffectAxisNoteEntry(0x00243f40u);
uint64_t incoming=cpu(31);
/* 00243f40: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00243f44: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00243f48: bnel v0,zero,0x00243f98 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00243f4c */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000004))));goto L_00243f98;}}
/* 00243f50: lhu v0,0x38(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000038))));
/* 00243f54: beq v0,zero,0x00243fdc */ {int taken=(cpu(2)==cpu(0));/* delay 00243f58 */ set(6,cpu(0));if(taken){goto L_00243fdc;}}
/* 00243f5c: move a3,v0 */ set(7,cpu(2));
/* 00243f60: addiu a0,a0,0x3a */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000003a)));
/* 00243f64: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
L_00243f68:;
/* 00243f68: addiu a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));
/* 00243f6c: beq v1,a1,0x00243fe0 */ {int taken=(cpu(3)==cpu(5));/* delay 00243f70 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00243fe0;}}
/* 00243f74: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 00243f78: slt v0,a2,a3 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(7));
/* 00243f7c: nop  */ 
/* 00243f80: nop  */ 
/* 00243f84: bnel v0,zero,0x00243f68 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00243f88 */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_00243f68;}}
/* 00243f8c: jr ra */ {uint64_t target=cpu(31);/* delay 00243f90 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_00243f98:;
/* 00243f98: move a2,zero */ set(6,cpu(0));
/* 00243f9c: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 00243fa0: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 00243fa4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00243fa8: lui a0,0x35 */ set(4,sx(UINT32_C(0x00350000)));
/* 00243fac: addiu a0,a0,-0x682a */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffff97d6)));
/* 00243fb0: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00243fb4: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
L_00243fb8:;
/* 00243fb8: addiu a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));
/* 00243fbc: beq v1,a1,0x00243fe0 */ {int taken=(cpu(3)==cpu(5));/* delay 00243fc0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00243fe0;}}
/* 00243fc4: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 00243fc8: slti v0,a2,0x8 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 00243fcc: nop  */ 
/* 00243fd0: nop  */ 
/* 00243fd4: bnel v0,zero,0x00243fb8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00243fd8 */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_00243fb8;}}
L_00243fdc:;
/* 00243fdc: move v0,zero */ set(2,cpu(0));
L_00243fe0:;
/* 00243fe0: jr ra */ {uint64_t target=cpu(31);/* delay 00243fe4 */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00243F40(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00243f40();
return cpu(2);
}
static void body_00243fe8(void){
nocturneEffectAxisNoteEntry(0x00243fe8u);
uint64_t incoming=cpu(31);
/* 00243fe8: move a2,a1 */ set(6,cpu(5));
/* 00243fec: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 00243ff0: beq a2,v1,0x00244070 */ {int taken=(cpu(6)==cpu(3));/* delay 00243ff4 */ set(2,cpu(0));if(taken){goto L_00244070;}}
/* 00243ff8: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00243ffc: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00244000: beq v0,zero,0x00244010 */ {int taken=(cpu(2)==cpu(0));/* delay 00244004 */ set(2,sx((uint32_t)cpu(6)<<2));if(taken){goto L_00244010;}}
/* 00244008: b 0x0024403c */ /* delay 0024400c */ set(7,sx(UINT32_C(0x003a0000)));goto L_0024403c;
L_00244010:;
/* 00244010: lhu v0,0x4(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 00244014: lui a3,0x3a */ set(7,sx(UINT32_C(0x003a0000)));
/* 00244018: sll v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)<<4));
/* 0024401c: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 00244020: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00244024: lui v0,0x35 */ set(2,sx(UINT32_C(0x00350000)));
/* 00244028: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0024402c: lh v0,-0x6832(v0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0xffff97ce))));
/* 00244030: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 00244034: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00244038: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
L_0024403c:;
/* 0024403c: lui a1,0x3a */ set(5,sx(UINT32_C(0x003a0000)));
/* 00244040: addu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 00244044: lw a1,0x7fe0(a1) */ lw(5,ea(5,(int32_t)UINT32_C(0x00007fe0)));
/* 00244048: lhu v0,0xe(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000000e))));
/* 0024404c: li v1,0x400 */ set(3,sx(UINT32_C(0x00000400)));
/* 00244050: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 00244054: bnel v0,v1,0x00244070 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 00244058 */ set(2,cpu(5));goto L_00244070;}}
/* 0024405c: addiu v1,a3,0x7fe0 */ set(3,sx((uint32_t)cpu(7)+UINT32_C(0x00007fe0)));
/* 00244060: sll v0,a2,0x2 */ set(2,sx((uint32_t)cpu(6)<<2));
/* 00244064: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00244068: lw a1,0x3d80(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00003d80)));
/* 0024406c: move v0,a1 */ set(2,cpu(5));
L_00244070:;
/* 00244070: jr ra */ {uint64_t target=cpu(31);/* delay 00244074 */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00243FE8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00243fe8();
return cpu(2);
}
static void body_002440c0(void){
nocturneEffectAxisNoteEntry(0x002440c0u);
uint64_t incoming=cpu(31);
/* 002440c0: li v0,0x80 */ set(2,sx(UINT32_C(0x00000080)));
/* 002440c4: beq a0,v0,0x002441f0 */ {int taken=(cpu(4)==cpu(2));/* delay 002440c8 */ set(3,sx(UINT32_C(0xffffffff)));if(taken){goto L_002441f0;}}
/* 002440cc: slti v0,a0,0x81 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000081));
/* 002440d0: beq v0,zero,0x00244168 */ {int taken=(cpu(2)==cpu(0));/* delay 002440d4 */ set(2,sx(UINT32_C(0x00000800)));if(taken){goto L_00244168;}}
/* 002440d8: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002440dc: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 002440e0 */ set(3,sx(UINT32_C(0x0000000a)));goto L_002441f4;}}
/* 002440e4: slti v0,a0,0x9 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 002440e8: beq v0,zero,0x00244130 */ {int taken=(cpu(2)==cpu(0));/* delay 002440ec */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_00244130;}}
/* 002440f0: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002440f4: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 002440f8 */ set(3,sx(UINT32_C(0x00000002)));goto L_002441f4;}}
/* 002440fc: slti v0,a0,0x3 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00244100: beq v0,zero,0x00244120 */ {int taken=(cpu(2)==cpu(0));/* delay 00244104 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_00244120;}}
/* 00244108: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0024410c: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 00244110 */ set(3,sx(UINT32_C(0x00000003)));goto L_002441f4;}}
/* 00244114: jr ra */ {uint64_t target=cpu(31);/* delay 00244118 */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_00244120:;
/* 00244120: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 00244124 */ set(3,sx(UINT32_C(0x0000000a)));goto L_002441f4;}}
/* 00244128: jr ra */ {uint64_t target=cpu(31);/* delay 0024412c */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_00244130:;
/* 00244130: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 00244134 */ set(3,sx(UINT32_C(0x00000008)));goto L_002441f4;}}
/* 00244138: slti v0,a0,0x21 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000021));
/* 0024413c: beq v0,zero,0x00244158 */ {int taken=(cpu(2)==cpu(0));/* delay 00244140 */ set(2,sx(UINT32_C(0x00000040)));if(taken){goto L_00244158;}}
/* 00244144: li v0,0x10 */ set(2,sx(UINT32_C(0x00000010)));
/* 00244148: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 0024414c */ set(3,sx(UINT32_C(0x00000009)));goto L_002441f4;}}
/* 00244150: jr ra */ {uint64_t target=cpu(31);/* delay 00244154 */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_00244158:;
/* 00244158: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 0024415c */ set(3,sx(UINT32_C(0x00000008)));goto L_002441f4;}}
/* 00244160: jr ra */ {uint64_t target=cpu(31);/* delay 00244164 */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_00244168:;
/* 00244168: beq a0,v0,0x002441f8 */ {int taken=(cpu(4)==cpu(2));/* delay 0024416c */ set(2,cpu(3));if(taken){goto L_002441f8;}}
/* 00244170: slti v0,a0,0x801 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000801));
/* 00244174: beq v0,zero,0x002441b8 */ {int taken=(cpu(2)==cpu(0));/* delay 00244178 */ set(2,sx(UINT32_C(0x00002000)));if(taken){goto L_002441b8;}}
/* 0024417c: li v0,0x200 */ set(2,sx(UINT32_C(0x00000200)));
/* 00244180: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 00244184 */ set(3,sx(UINT32_C(0x00000005)));goto L_002441f4;}}
/* 00244188: slti v0,a0,0x201 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000201));
/* 0024418c: beq v0,zero,0x002441a8 */ {int taken=(cpu(2)==cpu(0));/* delay 00244190 */ set(2,sx(UINT32_C(0x00000400)));if(taken){goto L_002441a8;}}
/* 00244194: li v0,0x100 */ set(2,sx(UINT32_C(0x00000100)));
/* 00244198: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 0024419c */ set(3,sx(UINT32_C(0x00000009)));goto L_002441f4;}}
/* 002441a0: jr ra */ {uint64_t target=cpu(31);/* delay 002441a4 */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_002441a8:;
/* 002441a8: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 002441ac */ set(3,sx(UINT32_C(0x00000007)));goto L_002441f4;}}
/* 002441b0: jr ra */ {uint64_t target=cpu(31);/* delay 002441b4 */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_002441b8:;
/* 002441b8: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 002441bc */ set(3,sx(UINT32_C(0x00000005)));goto L_002441f4;}}
/* 002441c0: slti v0,a0,0x2001 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00002001));
/* 002441c4: beq v0,zero,0x002441e0 */ {int taken=(cpu(2)==cpu(0));/* delay 002441c8 */ set(2,sx(UINT32_C(0x00004000)));if(taken){goto L_002441e0;}}
/* 002441cc: li v0,0x1000 */ set(2,sx(UINT32_C(0x00001000)));
/* 002441d0: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 002441d4 */ set(3,sx(UINT32_C(0x00000005)));goto L_002441f4;}}
/* 002441d8: jr ra */ {uint64_t target=cpu(31);/* delay 002441dc */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_002441e0:;
/* 002441e0: beql a0,v0,0x002441f4 */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 002441e4 */ set(3,sx(UINT32_C(0x00000005)));goto L_002441f4;}}
/* 002441e8: jr ra */ {uint64_t target=cpu(31);/* delay 002441ec */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_002441f0:;
/* 002441f0: li v1,0xa */ set(3,sx(UINT32_C(0x0000000a)));
L_002441f4:;
/* 002441f4: move v0,v1 */ set(2,cpu(3));
L_002441f8:;
/* 002441f8: jr ra */ {uint64_t target=cpu(31);/* delay 002441fc */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_002440C0(uint64_t a0){
set(4,a0);
body_002440c0();
return cpu(2);
}
static void body_002515d8(void){
nocturneEffectAxisNoteEntry(0x002515d8u);
uint64_t incoming=cpu(31);
/* 002515d8: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 002515dc: addu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 002515e0: jr ra */ {uint64_t target=cpu(31);/* delay 002515e4 */ set(2,half(ea(5,(int32_t)UINT32_C(0x0000008c))));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_002515D8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002515d8();
return cpu(2);
}
static void body_002516e8(void){
nocturneEffectAxisNoteEntry(0x002516e8u);
uint64_t incoming=cpu(31);
/* 002516e8: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002516ec: lui a3,0x2 */ set(7,sx(UINT32_C(0x00020000)));
/* 002516f0: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 002516f4: lw v1,0x60(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000060)));
/* 002516f8: move v0,zero */ set(2,cpu(0));
/* 002516fc: addu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 00251700: and v1,v1,a3 */ set(3,cpu(3)&cpu(7));
/* 00251704: bne v1,zero,0x0025172c */ {int taken=(cpu(3)!=cpu(0));/* delay 00251708 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x0000008c)));if(taken){goto L_0025172c;}}
/* 0025170c: lhu v0,0x0(a1) */ set(2,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 00251710: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00251714: bgezl v0,0x00251728 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 00251718 */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));goto L_00251728;}}
/* 0025171c: sh zero,0x0(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(0));
/* 00251720: jr ra */ {uint64_t target=cpu(31);/* delay 00251724 */ set(2,sx(UINT32_C(0x00000001)));checkReturn(target,incoming);return;}
L_00251728:;
/* 00251728: move v0,zero */ set(2,cpu(0));
L_0025172c:;
/* 0025172c: jr ra */ {uint64_t target=cpu(31);/* delay 00251730 */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_002516E8(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_002516e8();
return cpu(2);
}
static void body_002517e0(void){
nocturneEffectAxisNoteEntry(0x002517e0u);
uint64_t incoming=cpu(31);
/* 002517e0: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 002517e4: addiu v1,a0,0xa */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x0000000a)));
/* 002517e8: addiu v0,a1,0x80 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000080)));
/* 002517ec: addiu a0,a0,0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
/* 002517f0: addu t1,a0,v0 */ set(9,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002517f4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002517f8: move a0,t1 */ set(4,cpu(9));
/* 002517fc: lhu a1,0x0(a0) */ set(5,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00251800: slt v0,a2,a1 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(5));
/* 00251804: bltz a3,0x0025181c */ {int taken=((int64_t)cpu(7)<0);/* delay 00251808 */ if(cpu(2)!=0){set(6,cpu(5));}if(taken){goto L_0025181c;}}
/* 0025180c: addu a3,a2,a3 */ set(7,sx((uint32_t)cpu(6)+(uint32_t)cpu(7)));
/* 00251810: slt v0,a1,a3 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(7));
/* 00251814: bnel v0,zero,0x0025181c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251818 */ sh(ea(4,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(7));goto L_0025181c;}}
L_0025181c:;
/* 0025181c: bltz t0,0x0025184c */ {int taken=((int64_t)cpu(8)<0);/* delay 00251820 */ if(taken){goto L_0025184c;}}
/* 00251824: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00251828: addu a2,a2,t0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(8)));
/* 0025182c: slt v0,v0,a2 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(6));
/* 00251830: bnel v0,zero,0x00251838 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251834 */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(6));goto L_00251838;}}
L_00251838:;
/* 00251838: lhu a0,0x0(t1) */ set(4,half(ea(9,(int32_t)UINT32_C(0x00000000))));
/* 0025183c: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00251840: sltu v0,v0,a0 */ set(2,cpu(2)<cpu(4));
/* 00251844: bnel v0,zero,0x0025184c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251848 */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));goto L_0025184c;}}
L_0025184c:;
/* 0025184c: jr ra */ {uint64_t target=cpu(31);/* delay 00251850 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionFormula_002517E0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
body_002517e0();
return;
}
static void body_00262f58(void){
nocturneEffectAxisNoteEntry(0x00262f58u);
uint64_t incoming=cpu(31);
/* 00262f58: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262f5c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262f60: move s0,a0 */ set(16,cpu(4));
/* 00262f64: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262f68: move s1,a1 */ set(17,cpu(5));
/* 00262f6c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262f70: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262f74: jal 0x0025e8e0 */ set(31,0x00262f7cu);/* delay 00262f78 */ set(18,cpu(6));ps2BattleActionPacket_0025E8E0();
/* 00262f7c: move a0,v0 */ set(4,cpu(2));
/* 00262f80: move a1,s0 */ set(5,cpu(16));
/* 00262f84: move a3,s1 */ set(7,cpu(17));
/* 00262f88: jal 0x0025ea48 */ set(31,0x00262f90u);/* delay 00262f8c */ set(6,cpu(0));ps2BattleActionPacket_0025EA48(cpu(4),cpu(5),cpu(6),cpu(7));
/* 00262f90: li a0,0x31 */ set(4,sx(UINT32_C(0x00000031)));
/* 00262f94: move v1,v0 */ set(3,cpu(2));
/* 00262f98: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262f9c: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00262fa0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262fa4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262fa8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262fac: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262fb0: jr ra */ {uint64_t target=cpu(31);/* delay 00262fb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00262F58(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00262f58();
return cpu(2);
}
static void body_002654b8(void){
nocturneEffectAxisNoteEntry(0x002654b8u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 002654b8: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002654bc: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002654c0: move s5,a2 */ set(21,cpu(6));
/* 002654c4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002654c8: move s2,a3 */ set(18,cpu(7));
/* 002654cc: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002654d0: move s6,a0 */ set(22,cpu(4));
/* 002654d4: move a0,s5 */ set(4,cpu(21));
/* 002654d8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002654dc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002654e0: move s3,a1 */ set(19,cpu(5));
/* 002654e4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002654e8: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002654ec: move s8,zero */ set(30,cpu(0));
/* 002654f0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002654f4: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002654f8: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002654fc: swc1 f21,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),f[21]);
/* 00265500: jal 0x00246ab8 */ set(31,0x00265508u);/* delay 00265504 */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),f[20]);ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00265508: move a0,s2 */ set(4,cpu(18));
/* 0026550c: jal 0x00246ab8 */ set(31,0x00265514u);/* delay 00265510 */ set(16,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00265514: move a0,s3 */ set(4,cpu(19));
/* 00265518: jal 0x00267e38 */ set(31,0x00265520u);/* delay 0026551c */ set(20,cpu(2));body_00267e38();
/* 00265520: move a2,v0 */ set(6,cpu(2));
/* 00265524: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 00265528: beq a2,v0,0x00265828 */ {int taken=(cpu(6)==cpu(2));/* delay 0026552c */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0xffffffff));if(taken){goto L_00265828;}}
/* 00265530: bne v0,zero,0x00265550 */ {int taken=(cpu(2)!=cpu(0));/* delay 00265534 */ set(4,cpu(19));if(taken){goto L_00265550;}}
/* 00265538: slti v0,a2,0x10 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0026553c: beq v0,zero,0x00265550 */ {int taken=(cpu(2)==cpu(0));/* delay 00265540 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x0000000c));if(taken){goto L_00265550;}}
/* 00265544: beq v0,zero,0x0026582c */ {int taken=(cpu(2)==cpu(0));/* delay 00265548 */ set(2,cpu(0));if(taken){goto L_0026582c;}}
/* 0026554c: move a0,s3 */ set(4,cpu(19));
L_00265550:;
/* 00265550: jal 0x00267890 */ set(31,0x00265558u);/* delay 00265554 */ set(5,cpu(18));body_00267890();
/* 00265558: bne s3,zero,0x00265598 */ {int taken=(cpu(19)!=cpu(0));/* delay 0026555c */ set(17,cpu(2));if(taken){goto L_00265598;}}
/* 00265560: move a0,s0 */ set(4,cpu(16));
/* 00265564: jal 0x0026a3d8 */ set(31,0x0026556cu);/* delay 00265568 */ set(5,sx(UINT32_C(0x0000012c)));body_0026a3d8();
/* 0026556c: bne v0,zero,0x00265588 */ {int taken=(cpu(2)!=cpu(0));/* delay 00265570 */ set(3,sx(UINT32_C(0x0000012c)));if(taken){goto L_00265588;}}
/* 00265574: move a0,s0 */ set(4,cpu(16));
/* 00265578: jal 0x0026a3d8 */ set(31,0x00265580u);/* delay 0026557c */ set(5,sx(UINT32_C(0x0000012d)));body_0026a3d8();
/* 00265580: beq v0,zero,0x00265598 */ {int taken=(cpu(2)==cpu(0));/* delay 00265584 */ set(3,sx(UINT32_C(0x0000012d)));if(taken){goto L_00265598;}}
L_00265588:;
/* 00265588: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0026558c: b 0x0026582c */ /* delay 00265590 */ sw(ea(22,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(3));goto L_0026582c;
L_00265598:;
/* 00265598: bltz s1,0x0026582c */ {int taken=((int64_t)cpu(17)<0);/* delay 0026559c */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_0026582c;}}
/* 002655a0: jal 0x00246a40 */ set(31,0x002655a8u);/* delay 002655a4 */ set(4,cpu(21));ps2BattleActionScaleLookup_00246A40(cpu(4));
/* 002655a8: lhu v1,0x0(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002655ac: andi v1,v1,0x100 */ set(3,cpu(3)&UINT32_C(0x00000100));
/* 002655b0: bne v1,zero,0x0026582c */ {int taken=(cpu(3)!=cpu(0));/* delay 002655b4 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0026582c;}}
/* 002655b8: lhu v0,0xe(s4) */ set(2,half(ea(20,(int32_t)UINT32_C(0x0000000e))));
/* 002655bc: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 002655c0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002655c4: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 002655c8: andi a0,v0,0xfff */ set(4,cpu(2)&UINT32_C(0x00000fff));
/* 002655cc: beq a0,v1,0x00265608 */ {int taken=(cpu(4)==cpu(3));/* delay 002655d0 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000005));if(taken){goto L_00265608;}}
/* 002655d4: beq v0,zero,0x00265600 */ {int taken=(cpu(2)==cpu(0));/* delay 002655d8 */ set(2,sx(UINT32_C(0x00000010)));if(taken){goto L_00265600;}}
/* 002655dc: slti v0,a0,0x3 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 002655e0: beq v0,zero,0x00265614 */ {int taken=(cpu(2)==cpu(0));/* delay 002655e4 */ lw(3,ea(22,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00265614;}}
/* 002655e8: beq a0,zero,0x00265614 */ {int taken=(cpu(4)==cpu(0));/* delay 002655ec */ if(taken){goto L_00265614;}}
/* 002655f0: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 002655f4: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 002655f8: b 0x00265618 */ /* delay 002655fc */ set(2,sx((uint32_t)cpu(18)<<4));goto L_00265618;
L_00265600:;
/* 00265600: bnel a0,v0,0x00265614 */ {int taken=(cpu(4)!=cpu(2));if(taken){/* delay 00265604 */ lw(3,ea(22,(int32_t)UINT32_C(0x00000000)));goto L_00265614;}}
L_00265608:;
/* 00265608: lui at,0x4100 */ set(1,sx(UINT32_C(0x41000000)));
/* 0026560c: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 00265610: lw v1,0x0(s6) */ lw(3,ea(22,(int32_t)UINT32_C(0x00000000)));
L_00265614:;
/* 00265614: sll v0,s2,0x4 */ set(2,sx((uint32_t)cpu(18)<<4));
L_00265618:;
/* 00265618: subu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 0026561c: lw a0,0x0(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00265620: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 00265624: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00265628: lw v1,0x78(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000078)));
/* 0026562c: andi v1,v1,0x2000 */ set(3,cpu(3)&UINT32_C(0x00002000));
/* 00265630: beq v1,zero,0x00265650 */ {int taken=(cpu(3)==cpu(0));/* delay 00265634 */ if(taken){goto L_00265650;}}
/* 00265638: jal 0x001e0f50 */ set(31,0x00265640u);/* delay 0026563c */ set(4,sx(UINT32_C(0x00000af2)));body_001e0f50();
/* 00265640: bne v0,zero,0x00265650 */ {int taken=(cpu(2)!=cpu(0));/* delay 00265644 */ if(taken){goto L_00265650;}}
/* 00265648: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 0026564c: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
L_00265650:;
/* 00265650: bne s3,zero,0x00265698 */ {int taken=(cpu(19)!=cpu(0));/* delay 00265654 */ set(21,sx((uint32_t)cpu(19)<<4));if(taken){goto L_00265698;}}
/* 00265658: move a0,s0 */ set(4,cpu(16));
/* 0026565c: jal 0x0026a3d8 */ set(31,0x00265664u);/* delay 00265660 */ set(5,sx(UINT32_C(0x0000012b)));body_0026a3d8();
/* 00265664: beq v0,zero,0x00265694 */ {int taken=(cpu(2)==cpu(0));/* delay 00265668 */ set(2,sx(UINT32_C(0x003e0000)));if(taken){goto L_00265694;}}
/* 0026566c: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00265670: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00265674: lh v1,-0x3e08(v0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0xffffc1f8))));
/* 00265678: li s8,0x1 */ set(30,sx(UINT32_C(0x00000001)));
/* 0026567c: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00265680: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00265684: nop  */ 
/* 00265688: nop  */ 
/* 0026568c: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 00265690: mul.S f21,f21,f0 */ f[21]=EE_FPU_MUL_S(f[21],f[0]);
L_00265694:;
/* 00265694: sll s5,s3,0x4 */ set(21,sx((uint32_t)cpu(19)<<4));
L_00265698:;
/* 00265698: lui s7,0x3d */ set(23,sx(UINT32_C(0x003d0000)));
/* 0026569c: subu v1,s5,s3 */ set(3,sx((uint32_t)cpu(21)-(uint32_t)cpu(19)));
/* 002656a0: addiu s2,s7,0x7998 */ set(18,sx((uint32_t)cpu(23)+UINT32_C(0x00007998)));
/* 002656a4: sll s1,v1,0x2 */ set(17,sx((uint32_t)cpu(3)<<2));
/* 002656a8: addu v0,s1,s2 */ set(2,sx((uint32_t)cpu(17)+(uint32_t)cpu(18)));
/* 002656ac: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 002656b0: bne v1,zero,0x00265828 */ {int taken=(cpu(3)!=cpu(0));/* delay 002656b4 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00265828;}}
/* 002656b8: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002656bc: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 002656c0: move a0,s0 */ set(4,cpu(16));
/* 002656c4: jal 0x00243ee0 */ set(31,0x002656ccu);/* delay 002656c8 */ set(5,sx(UINT32_C(0x00000004)));body_00243ee0();
/* 002656cc: lhu a2,0x14(s0) */ set(6,half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 002656d0: li s0,0x5 */ set(16,sx(UINT32_C(0x00000005)));
/* 002656d4: move a0,s4 */ set(4,cpu(20));
/* 002656d8: divu a2,s0 */ nativeDivide((uint32_t)cpu(6),(uint32_t)cpu(16),0,0);
/* 002656dc: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 002656e0: beql s0,zero,0x002656e8 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 002656e4 */ nocturneCompilerArithmeticTrap(7u);goto L_002656e8;}}
L_002656e8:;
/* 002656e8: mflo a2 */ set(6,nocturneEffectHostLo());
/* 002656ec: addiu a2,a2,0x3 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000003)));
/* 002656f0: div v0,a2 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(6),1,0);
/* 002656f4: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002656f8: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 002656fc: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00265700: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00265704: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00265708: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0026570c: mtc1 v1,f20 */ f[20]=(uint32_t)cpu(3);
/* 00265710: cvt.s.W f20,f20 */ f[20]=EE_FPU_CVT_S_W(f[20]);
/* 00265714: jal 0x00243ee0 */ set(31,0x0026571cu);/* delay 00265718 */ body_00243ee0();
/* 0026571c: lhu v1,0x14(s4) */ set(3,half(ea(20,(int32_t)UINT32_C(0x00000014))));
/* 00265720: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 00265724: beql a1,zero,0x0026572c */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 00265728 */ nocturneCompilerArithmeticTrap(7u);goto L_0026572c;}}
L_0026572c:;
/* 0026572c: addiu a0,s1,0x30 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000030)));
/* 00265730: divu v1,s0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(16),0,0);
/* 00265734: addu a3,a0,s2 */ set(7,sx((uint32_t)cpu(4)+(uint32_t)cpu(18)));
/* 00265738: li a2,0x64 */ set(6,sx(UINT32_C(0x00000064)));
/* 0026573c: lui at,0x3d80 */ set(1,sx(UINT32_C(0x3d800000)));
/* 00265740: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00265744: lui at,0x4248 */ set(1,sx(UINT32_C(0x42480000)));
/* 00265748: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0026574c: mflo v1 */ set(3,nocturneEffectHostLo());
/* 00265750: addiu v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000003)));
/* 00265754: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 00265758: lh a0,0x6(a3) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x00000006))));
/* 0026575c: subu a2,a2,a0 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(4)));
/* 00265760: mtc1 a2,f3 */ f[3]=(uint32_t)cpu(6);
/* 00265764: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 00265768: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0026576c: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 00265770: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00265774: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00265778: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0026577c: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00265780: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00265784: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00265788: sub.S f0,f20,f0 */ f[0]=EE_FPU_SUB_S(f[20],f[0]);
/* 0026578c: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 00265790: add.S f2,f3,f0 */ f[2]=EE_FPU_ADD_S(f[3],f[0]);
/* 00265794: c.lt.S f2,f4 */ condition=EE_FPU_COMPARE_S(f[2],f[4],1)!=0;
/* 00265798: bc1tl 0x002657a0 */ {int taken=(condition!=0);if(taken){/* delay 0026579c */ f[2]=f[4];goto L_002657a0;}}
L_002657a0:;
/* 002657a0: nop  */ 
/* 002657a4: nop  */ 
/* 002657a8: div.S f0,f2,f3 */ f[0]=EE_FPU_DIV_S(f[2],f[3]);
/* 002657ac: lh v0,0x4(a3) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x00000004))));
/* 002657b0: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 002657b4: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 002657b8: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 002657bc: mul.S f0,f0,f21 */ f[0]=EE_FPU_MUL_S(f[0],f[21]);
/* 002657c0: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 002657c4: mfc1 s0,f1 */ set(16,sx(f[1]));
/* 002657c8: subu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)-(uint32_t)cpu(19)));
/* 002657cc: cvt.w.S f0,f2 */ f[0]=EE_FPU_CVT_W_S(f[2]);
/* 002657d0: mfc1 a2,f0 */ set(6,sx(f[0]));
/* 002657d4: addiu v1,s7,0x7998 */ set(3,sx((uint32_t)cpu(23)+UINT32_C(0x00007998)));
/* 002657d8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002657dc: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 002657e0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002657e4: addiu a0,a0,0x49c0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000049c0)));
/* 002657e8: lh a1,0x34(v0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000034))));
/* 002657ec: jal 0x002d4748 */ set(31,0x002657f4u);/* delay 002657f0 */ set(7,cpu(16));ps2BattleActionPrintf_002D4748(cpu(4));
/* 002657f4: move a0,zero */ set(4,cpu(0));
/* 002657f8: jal 0x002c0c60 */ set(31,0x00265800u);/* delay 002657fc */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00265800: slt v0,v0,s0 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(16));
/* 00265804: beql v0,zero,0x0026582c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00265808 */ set(2,cpu(0));goto L_0026582c;}}
/* 0026580c: beql s8,zero,0x0026582c */ {int taken=(cpu(30)==cpu(0));if(taken){/* delay 00265810 */ set(2,sx(UINT32_C(0x00000001)));goto L_0026582c;}}
/* 00265814: li v0,0x12b */ set(2,sx(UINT32_C(0x0000012b)));
/* 00265818: sw v0,0x58(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(2));
/* 0026581c: b 0x0026582c */ /* delay 00265820 */ set(2,sx(UINT32_C(0x00000001)));goto L_0026582c;
L_00265828:;
/* 00265828: move v0,zero */ set(2,cpu(0));
L_0026582c:;
/* 0026582c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00265830: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00265834: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00265838: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026583c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00265840: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00265844: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00265848: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0026584c: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00265850: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00265854: lwc1 f21,0x58(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00265858: lwc1 f20,0x50(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0026585c: jr ra */ {uint64_t target=cpu(31);/* delay 00265860 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_002654B8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_002654b8();
return cpu(2);
}
static void body_00266130(void){
nocturneEffectAxisNoteEntry(0x00266130u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00266130: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 00266134: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00266138: move s0,a1 */ set(16,cpu(5));
/* 0026613c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00266140: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00266144: move s2,a0 */ set(18,cpu(4));
/* 00266148: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026614c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00266150: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00266154: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00266158: swc1 f20,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),f[20]);
/* 0026615c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00266160: jal 0x002469a0 */ set(31,0x00266168u);/* delay 00266164 */ set(20,cpu(6));ps2BattleActionScaleLookup_002469A0();
/* 00266168: move a0,s0 */ set(4,cpu(16));
/* 0026616c: jal 0x00246ab8 */ set(31,0x00266174u);/* delay 00266170 */ set(22,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00266174: move a0,s4 */ set(4,cpu(20));
/* 00266178: jal 0x00246ab8 */ set(31,0x00266180u);/* delay 0026617c */ set(19,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00266180: move a0,s2 */ set(4,cpu(18));
/* 00266184: jal 0x00267e38 */ set(31,0x0026618cu);/* delay 00266188 */ set(21,cpu(2));body_00267e38();
/* 0026618c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00266190: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 00266194: move s1,v0 */ set(17,cpu(2));
/* 00266198: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 0026619c: beq s1,v0,0x00266278 */ {int taken=(cpu(17)==cpu(2));/* delay 002661a0 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0xffffffff));if(taken){goto L_00266278;}}
/* 002661a4: bne v0,zero,0x002661c8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002661a8 */ set(5,cpu(20));if(taken){goto L_002661c8;}}
/* 002661ac: slti v0,s1,0xf */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x0000000f));
/* 002661b0: beq v0,zero,0x002661cc */ {int taken=(cpu(2)==cpu(0));/* delay 002661b4 */ set(4,cpu(18));if(taken){goto L_002661cc;}}
/* 002661b8: slti v0,s1,0xc */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 002661bc: beq v0,zero,0x0026627c */ {int taken=(cpu(2)==cpu(0));/* delay 002661c0 */ set(4,cpu(19));if(taken){goto L_0026627c;}}
/* 002661c4: move a1,s4 */ set(5,cpu(20));
L_002661c8:;
/* 002661c8: move a0,s2 */ set(4,cpu(18));
L_002661cc:;
/* 002661cc: jal 0x00267890 */ set(31,0x002661d4u);/* delay 002661d0 */ set(6,cpu(17));body_00267890();
/* 002661d4: lui v1,0x6 */ set(3,sx(UINT32_C(0x00060000)));
/* 002661d8: and v1,v0,v1 */ set(3,cpu(2)&cpu(3));
/* 002661dc: beq v1,zero,0x002661ec */ {int taken=(cpu(3)==cpu(0));/* delay 002661e0 */ set(16,cpu(2)&UINT32_C(0x0000ffff));if(taken){goto L_002661ec;}}
/* 002661e4: li v0,0x64 */ set(2,sx(UINT32_C(0x00000064)));
/* 002661e8: movz s0,v0,s0 */ if(cpu(16)==0){set(16,cpu(2));}
L_002661ec:;
/* 002661ec: lhu v0,0xe(s5) */ set(2,half(ea(21,(int32_t)UINT32_C(0x0000000e))));
/* 002661f0: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
/* 002661f4: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 002661f8: bne v0,v1,0x0026622c */ {int taken=(cpu(2)!=cpu(3));/* delay 002661fc */ set(4,cpu(19));if(taken){goto L_0026622c;}}
/* 00266200: sll v0,s2,0x4 */ set(2,sx((uint32_t)cpu(18)<<4));
/* 00266204: subu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 00266208: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0026620c: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 00266210: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00266214: lbu v1,0x799a(v1) */ set(3,byte(ea(3,(int32_t)UINT32_C(0x0000799a))));
/* 00266218: bne v1,zero,0x0026622c */ {int taken=(cpu(3)!=cpu(0));/* delay 0026621c */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000064));if(taken){goto L_0026622c;}}
/* 00266220: li v0,0x64 */ set(2,sx(UINT32_C(0x00000064)));
/* 00266224: movn s0,v0,v1 */ if(cpu(3)!=0){set(16,cpu(2));}
/* 00266228: move a0,s3 */ set(4,cpu(19));
L_0026622c:;
/* 0026622c: jal 0x00243f40 */ set(31,0x00266234u);/* delay 00266230 */ set(5,sx(UINT32_C(0x00000165)));body_00243f40();
/* 00266234: beq v0,zero,0x00266268 */ {int taken=(cpu(2)==cpu(0));/* delay 00266238 */ set(2,sx((uint32_t)cpu(18)<<4));if(taken){goto L_00266268;}}
/* 0026623c: subu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 00266240: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266244: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 00266248: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0026624c: lbu v1,0x799a(v1) */ set(3,byte(ea(3,(int32_t)UINT32_C(0x0000799a))));
/* 00266250: bne v1,zero,0x00266268 */ {int taken=(cpu(3)!=cpu(0));/* delay 00266254 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000064));if(taken){goto L_00266268;}}
/* 00266258: beq v0,zero,0x00266268 */ {int taken=(cpu(2)==cpu(0));/* delay 0026625c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00266268;}}
/* 00266260: li s0,0x64 */ set(16,sx(UINT32_C(0x00000064)));
/* 00266264: sw v0,0x14c(s6) */ sw(ea(22,(int32_t)UINT32_C(0x0000014c)),(uint32_t)cpu(2));
L_00266268:;
/* 00266268: mtc1 s0,f1 */ f[1]=(uint32_t)cpu(16);
/* 0026626c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00266270: lwc1 f0,-0x5c40(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa3c0)));
/* 00266274: mul.S f20,f1,f0 */ f[20]=EE_FPU_MUL_S(f[1],f[0]);
L_00266278:;
/* 00266278: move a0,s3 */ set(4,cpu(19));
L_0026627c:;
/* 0026627c: jal 0x00243f40 */ set(31,0x00266284u);/* delay 00266280 */ set(5,sx(UINT32_C(0x00000169)));body_00243f40();
/* 00266284: bne v0,zero,0x00266310 */ {int taken=(cpu(2)!=cpu(0));/* delay 00266288 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_00266310;}}
/* 0026628c: beq s1,v0,0x002662d8 */ {int taken=(cpu(17)==cpu(2));/* delay 00266290 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_002662d8;}}
/* 00266294: beq v0,zero,0x002662b0 */ {int taken=(cpu(2)==cpu(0));/* delay 00266298 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002662b0;}}
/* 0026629c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002662a0: beq s1,v0,0x002662c8 */ {int taken=(cpu(17)==cpu(2));/* delay 002662a4 */ f[0]=f[20];if(taken){goto L_002662c8;}}
/* 002662a8: b 0x00266324 */ /* delay 002662ac */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00266324;
L_002662b0:;
/* 002662b0: beq s1,v0,0x002662e8 */ {int taken=(cpu(17)==cpu(2));/* delay 002662b4 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_002662e8;}}
/* 002662b8: beq s1,v0,0x002662f8 */ {int taken=(cpu(17)==cpu(2));/* delay 002662bc */ f[0]=f[20];if(taken){goto L_002662f8;}}
/* 002662c0: b 0x00266324 */ /* delay 002662c4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00266324;
L_002662c8:;
/* 002662c8: move a0,s3 */ set(4,cpu(19));
/* 002662cc: b 0x00266300 */ /* delay 002662d0 */ set(5,sx(UINT32_C(0x00000135)));goto L_00266300;
L_002662d8:;
/* 002662d8: move a0,s3 */ set(4,cpu(19));
/* 002662dc: b 0x00266300 */ /* delay 002662e0 */ set(5,sx(UINT32_C(0x00000136)));goto L_00266300;
L_002662e8:;
/* 002662e8: move a0,s3 */ set(4,cpu(19));
/* 002662ec: b 0x00266300 */ /* delay 002662f0 */ set(5,sx(UINT32_C(0x00000137)));goto L_00266300;
L_002662f8:;
/* 002662f8: move a0,s3 */ set(4,cpu(19));
/* 002662fc: li a1,0x138 */ set(5,sx(UINT32_C(0x00000138)));
L_00266300:;
/* 00266300: jal 0x0026a3d8 */ set(31,0x00266308u);/* delay 00266304 */ body_0026a3d8();
/* 00266308: beq v0,zero,0x00266320 */ {int taken=(cpu(2)==cpu(0));/* delay 0026630c */ f[0]=f[20];if(taken){goto L_00266320;}}
L_00266310:;
/* 00266310: lui at,0x3fc0 */ set(1,sx(UINT32_C(0x3fc00000)));
/* 00266314: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00266318: mul.S f20,f20,f0 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);
/* 0026631c: mov.S f0,f20 */ f[0]=f[20];
L_00266320:;
/* 00266320: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00266324:;
/* 00266324: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00266328: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026632c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00266330: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00266334: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00266338: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0026633c: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00266340: lwc1 f20,0x40(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00266344: jr ra */ {uint64_t target=cpu(31);/* delay 00266348 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
float ps2BattleActionFormula_00266130(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00266130();
return real(nocturneEffectHostFpr()[0]);
}
static void body_00266350(void){
nocturneEffectAxisNoteEntry(0x00266350u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00266350: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 00266354: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00266358: move s5,a2 */ set(21,cpu(6));
/* 0026635c: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00266360: move s1,a3 */ set(17,cpu(7));
/* 00266364: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 00266368: move a0,s5 */ set(4,cpu(21));
/* 0026636c: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00266370: li s0,-0x1 */ set(16,sx(UINT32_C(0xffffffff)));
/* 00266374: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00266378: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026637c: move s3,a1 */ set(19,cpu(5));
/* 00266380: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00266384: move s4,t0 */ set(20,cpu(8));
/* 00266388: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0026638c: sll s6,s3,0x4 */ set(22,sx((uint32_t)cpu(19)<<4));
/* 00266390: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00266394: li s7,-0x1 */ set(23,sx(UINT32_C(0xffffffff)));
/* 00266398: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0026639c: swc1 f20,0x60(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),f[20]);
/* 002663a0: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002663a4: jal 0x00246ab8 */ set(31,0x002663acu);/* delay 002663a8 */ f[20]=f[12];ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002663ac: move a0,s1 */ set(4,cpu(17));
/* 002663b0: jal 0x00246ab8 */ set(31,0x002663b8u);/* delay 002663b4 */ set(30,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002663b8: move a2,zero */ set(6,cpu(0));
/* 002663bc: sw v0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002663c0: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 002663c4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002663c8: lui at,0x3d */ set(1,sx(UINT32_C(0x003d0000)));
/* 002663cc: addiu at,at,0x79a8 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x000079a8)));
/* 002663d0: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 002663d4: lhu a0,0x6(v0) */ set(4,half(ea(2,(int32_t)UINT32_C(0x00000006))));
/* 002663d8: lh a1,0x8(v0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000008))));
/* 002663dc: sltiu v1,a0,0x10 */ set(3,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002663e0: beq v1,zero,0x002666b8 */ {int taken=(cpu(3)==cpu(0));/* delay 002663e4 */ set(18,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x0000000e))));if(taken){goto L_002666b8;}}
/* 002663e8: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 002663ec: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002663f0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002663f4: lw v1,0x4a50(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004a50)));
/* 002663f8: jr v1 */ {uint64_t target=cpu(3);/* delay 002663fc */ switch((uint32_t)target){case 0x00266400u:goto L_00266400;case 0x00266408u:goto L_00266408;case 0x00266418u:goto L_00266418;case 0x00266428u:goto L_00266428;case 0x00266460u:goto L_00266460;case 0x002664d0u:goto L_002664d0;case 0x002664f0u:goto L_002664f0;case 0x002664f8u:goto L_002664f8;case 0x00266508u:goto L_00266508;case 0x00266530u:goto L_00266530;case 0x00266630u:goto L_00266630;case 0x002666a0u:goto L_002666a0;case 0x002666b8u:goto L_002666b8;default:abort();}}
L_00266400:;
/* 00266400: b 0x002666b8 */ /* delay 00266404 */ set(23,sx((uint32_t)cpu(5)+(uint32_t)cpu(18)));goto L_002666b8;
L_00266408:;
/* 00266408: jal 0x002c0c60 */ set(31,0x00266410u);/* delay 0026640c */ set(4,cpu(0));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00266410: b 0x002666b8 */ /* delay 00266414 */ set(23,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));goto L_002666b8;
L_00266418:;
/* 00266418: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0026641c: b 0x00266430 */ /* delay 00266420 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000006))));goto L_00266430;
L_00266428:;
/* 00266428: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0026642c: lhu v0,0x8(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000008))));
L_00266430:;
/* 00266430: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00266434: beql v1,zero,0x0026643c */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00266438 */ nocturneCompilerArithmeticTrap(7u);goto L_0026643c;}}
L_0026643c:;
/* 0026643c: mult v0,v0,a1 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(5),1,0);
/* 00266440: div1 v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,1);
/* 00266444: mflo1 v0 */ set(2,secondaryLo);
/* 00266448: addu s7,v0,s2 */ set(23,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 0026644c: blezl s7,0x002666b8 */ {int taken=((int64_t)cpu(23)<=0);if(taken){/* delay 00266450 */ set(23,sx(UINT32_C(0x00000001)));goto L_002666b8;}}
/* 00266454: b 0x002666bc */ /* delay 00266458 */ set(3,sx(UINT32_C(0x003d0000)));goto L_002666bc;
L_00266460:;
/* 00266460: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 00266464: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00266468: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
/* 0026646c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266470: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00266474: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00266478: beq v1,zero,0x00266490 */ {int taken=(cpu(3)==cpu(0));/* delay 0026647c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00266490;}}
/* 00266480: beq v1,v0,0x002664b0 */ {int taken=(cpu(3)==cpu(2));/* delay 00266484 */ set(23,sx((uint32_t)cpu(6)+(uint32_t)cpu(18)));if(taken){goto L_002664b0;}}
/* 00266488: b 0x002666bc */ /* delay 0026648c */ set(3,sx(UINT32_C(0x003d0000)));goto L_002666bc;
L_00266490:;
/* 00266490: move a2,s1 */ set(6,cpu(17));
/* 00266494: move a3,a1 */ set(7,cpu(5));
/* 00266498: move a0,s3 */ set(4,cpu(19));
/* 0026649c: jal 0x002688b8 */ set(31,0x002664a4u);/* delay 002664a0 */ set(5,cpu(21));body_002688b8();
/* 002664a4: b 0x002664c8 */ /* delay 002664a8 */ set(6,cpu(2));goto L_002664c8;
L_002664b0:;
/* 002664b0: move a2,s1 */ set(6,cpu(17));
/* 002664b4: move a3,a1 */ set(7,cpu(5));
/* 002664b8: move a0,s3 */ set(4,cpu(19));
/* 002664bc: jal 0x00268c60 */ set(31,0x002664c4u);/* delay 002664c0 */ set(5,cpu(21));body_00268c60();
/* 002664c4: move a2,v0 */ set(6,cpu(2));
L_002664c8:;
/* 002664c8: b 0x002666b8 */ /* delay 002664cc */ set(23,sx((uint32_t)cpu(6)+(uint32_t)cpu(18)));goto L_002666b8;
L_002664d0:;
/* 002664d0: move a3,a1 */ set(7,cpu(5));
/* 002664d4: move a1,s5 */ set(5,cpu(21));
/* 002664d8: move a2,s1 */ set(6,cpu(17));
/* 002664dc: jal 0x00268d60 */ set(31,0x002664e4u);/* delay 002664e0 */ set(4,cpu(19));body_00268d60();
/* 002664e4: b 0x002666b8 */ /* delay 002664e8 */ set(23,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));goto L_002666b8;
L_002664f0:;
/* 002664f0: b 0x002666b8 */ /* delay 002664f4 */ set(16,sx((uint32_t)cpu(5)+(uint32_t)cpu(18)));goto L_002666b8;
L_002664f8:;
/* 002664f8: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002664fc: b 0x00266510 */ /* delay 00266500 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000006))));goto L_00266510;
L_00266508:;
/* 00266508: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0026650c: lhu v0,0x8(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000008))));
L_00266510:;
/* 00266510: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00266514: beql v1,zero,0x0026651c */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00266518 */ nocturneCompilerArithmeticTrap(7u);goto L_0026651c;}}
L_0026651c:;
/* 0026651c: mult v0,v0,a1 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(5),1,0);
/* 00266520: div1 v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,1);
/* 00266524: mflo1 v0 */ set(2,secondaryLo);
/* 00266528: b 0x002666b8 */ /* delay 0026652c */ set(16,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));goto L_002666b8;
L_00266530:;
/* 00266530: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 00266534: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00266538: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
/* 0026653c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266540: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00266544: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00266548: beq v1,zero,0x00266560 */ {int taken=(cpu(3)==cpu(0));/* delay 0026654c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00266560;}}
/* 00266550: beq v1,v0,0x002665d0 */ {int taken=(cpu(3)==cpu(2));/* delay 00266554 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));if(taken){goto L_002665d0;}}
/* 00266558: b 0x002665f4 */ /* delay 0026655c */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));goto L_002665f4;
L_00266560:;
/* 00266560: move a2,s1 */ set(6,cpu(17));
/* 00266564: move a3,a1 */ set(7,cpu(5));
/* 00266568: move a0,s3 */ set(4,cpu(19));
/* 0026656c: jal 0x00268620 */ set(31,0x00266574u);/* delay 00266570 */ set(5,cpu(21));body_00268620();
/* 00266574: li v1,0x40 */ set(3,sx(UINT32_C(0x00000040)));
/* 00266578: move a2,v0 */ set(6,cpu(2));
/* 0026657c: lhu v0,0xe(s8) */ set(2,half(ea(30,(int32_t)UINT32_C(0x0000000e))));
/* 00266580: andi a0,v0,0xfff */ set(4,cpu(2)&UINT32_C(0x00000fff));
/* 00266584: beq a0,v1,0x002665a0 */ {int taken=(cpu(4)==cpu(3));/* delay 00266588 */ set(2,sx(UINT32_C(0x00000200)));if(taken){goto L_002665a0;}}
/* 0026658c: beq a0,v0,0x002665b0 */ {int taken=(cpu(4)==cpu(2));/* delay 00266590 */ set(4,sx(UINT32_C(0x003d0000)));if(taken){goto L_002665b0;}}
/* 00266594: b 0x002665f0 */ /* delay 00266598 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));goto L_002665f0;
L_002665a0:;
/* 002665a0: srl v0,a2,0x1f */ set(2,sx((uint32_t)cpu(6)>>31));
/* 002665a4: addu v0,a2,v0 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 002665a8: b 0x002665e8 */ /* delay 002665ac */ set(6,sx((uint32_t)((int32_t)cpu(2)>>1)));goto L_002665e8;
L_002665b0:;
/* 002665b0: li v0,0xa */ set(2,sx(UINT32_C(0x0000000a)));
/* 002665b4: div a2,v0 */ nativeDivide((uint32_t)cpu(6),(uint32_t)cpu(2),1,0);
/* 002665b8: beql v0,zero,0x002665c0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002665bc */ nocturneCompilerArithmeticTrap(7u);goto L_002665c0;}}
L_002665c0:;
/* 002665c0: mflo v1 */ set(3,nocturneEffectHostLo());
/* 002665c4: b 0x002665e8 */ /* delay 002665c8 */ set(6,cpu(3));goto L_002665e8;
L_002665d0:;
/* 002665d0: move a2,s1 */ set(6,cpu(17));
/* 002665d4: move a3,a1 */ set(7,cpu(5));
/* 002665d8: move a0,s3 */ set(4,cpu(19));
/* 002665dc: jal 0x002688d0 */ set(31,0x002665e4u);/* delay 002665e0 */ set(5,cpu(21));body_002688d0();
/* 002665e4: move a2,v0 */ set(6,cpu(2));
L_002665e8:;
/* 002665e8: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 002665ec: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
L_002665f0:;
/* 002665f0: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
L_002665f4:;
/* 002665f4: li a0,0xe */ set(4,sx(UINT32_C(0x0000000e)));
/* 002665f8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002665fc: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00266600: lhu v1,0x16(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000016))));
/* 00266604: bne v1,a0,0x002666b8 */ {int taken=(cpu(3)!=cpu(4));/* delay 00266608 */ set(16,sx((uint32_t)cpu(6)+(uint32_t)cpu(18)));if(taken){goto L_002666b8;}}
/* 0026660c: slti v0,s4,0x2 */ set(2,(int64_t)cpu(20)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00266610: bne v0,zero,0x002666bc */ {int taken=(cpu(2)!=cpu(0));/* delay 00266614 */ set(3,sx(UINT32_C(0x003d0000)));if(taken){goto L_002666bc;}}
/* 00266618: div s0,s4 */ nativeDivide((uint32_t)cpu(16),(uint32_t)cpu(20),1,0);
/* 0026661c: beql s4,zero,0x00266624 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00266620 */ nocturneCompilerArithmeticTrap(7u);goto L_00266624;}}
L_00266624:;
/* 00266624: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00266628: b 0x002666b8 */ /* delay 0026662c */ set(16,cpu(2));goto L_002666b8;
L_00266630:;
/* 00266630: move a3,a1 */ set(7,cpu(5));
/* 00266634: move a1,s5 */ set(5,cpu(21));
/* 00266638: move a0,s3 */ set(4,cpu(19));
/* 0026663c: jal 0x00268d60 */ set(31,0x00266644u);/* delay 00266640 */ set(6,cpu(17));body_00268d60();
/* 00266644: li v1,0x40 */ set(3,sx(UINT32_C(0x00000040)));
/* 00266648: move s0,v0 */ set(16,cpu(2));
/* 0026664c: lhu v0,0xe(s8) */ set(2,half(ea(30,(int32_t)UINT32_C(0x0000000e))));
/* 00266650: andi a0,v0,0xfff */ set(4,cpu(2)&UINT32_C(0x00000fff));
/* 00266654: beq a0,v1,0x00266670 */ {int taken=(cpu(4)==cpu(3));/* delay 00266658 */ set(2,sx(UINT32_C(0x00000200)));if(taken){goto L_00266670;}}
/* 0026665c: beq a0,v0,0x00266680 */ {int taken=(cpu(4)==cpu(2));/* delay 00266660 */ set(2,sx(UINT32_C(0x0000000a)));if(taken){goto L_00266680;}}
/* 00266664: b 0x002666b8 */ /* delay 00266668 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));goto L_002666b8;
L_00266670:;
/* 00266670: srl v0,s0,0x1f */ set(2,sx((uint32_t)cpu(16)>>31));
/* 00266674: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00266678: b 0x00266694 */ /* delay 0026667c */ set(16,sx((uint32_t)((int32_t)cpu(2)>>1)));goto L_00266694;
L_00266680:;
/* 00266680: div s0,v0 */ nativeDivide((uint32_t)cpu(16),(uint32_t)cpu(2),1,0);
/* 00266684: beql v0,zero,0x0026668c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00266688 */ nocturneCompilerArithmeticTrap(7u);goto L_0026668c;}}
L_0026668c:;
/* 0026668c: mflo v1 */ set(3,nocturneEffectHostLo());
/* 00266690: move s0,v1 */ set(16,cpu(3));
L_00266694:;
/* 00266694: b 0x002666b8 */ /* delay 00266698 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));goto L_002666b8;
L_002666a0:;
/* 002666a0: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002666a4: lhu v0,0x6(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000006))));
/* 002666a8: addu v1,a1,s2 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(18)));
/* 002666ac: subu a0,v0,v1 */ set(4,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002666b0: slt v1,v1,v0 */ set(3,(int64_t)cpu(3)<(int64_t)cpu(2));
/* 002666b4: movn s0,a0,v1 */ if(cpu(3)!=0){set(16,cpu(4));}
L_002666b8:;
/* 002666b8: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
L_002666bc:;
/* 002666bc: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 002666c0: addiu a0,v1,0x7998 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00007998)));
/* 002666c4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002666c8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002666cc: lhu v1,0x16(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000016))));
/* 002666d0: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 002666d4: sltiu v0,v1,0xe */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 002666d8: beq v0,zero,0x002667e8 */ {int taken=(cpu(2)==cpu(0));/* delay 002666dc */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002667e8;}}
/* 002666e0: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 002666e4: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002666e8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002666ec: lw v1,0x4a90(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004a90)));
/* 002666f0: jr v1 */ {uint64_t target=cpu(3);/* delay 002666f4 */ switch((uint32_t)target){case 0x002666f8u:goto L_002666f8;case 0x002667e4u:goto L_002667e4;default:abort();}}
L_002666f8:;
/* 002666f8: blez s0,0x002667e8 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002666fc */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002667e8;}}
/* 00266700: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 00266704: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00266708: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
/* 0026670c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266710: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00266714: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00266718: beq v1,zero,0x00266730 */ {int taken=(cpu(3)==cpu(0));/* delay 0026671c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00266730;}}
/* 00266720: beq v1,v0,0x00266758 */ {int taken=(cpu(3)==cpu(2));/* delay 00266724 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000000));if(taken){goto L_00266758;}}
/* 00266728: b 0x00266798 */ /* delay 0026672c */ if(cpu(2)!=0){set(16,cpu(0));}goto L_00266798;
L_00266730:;
/* 00266730: jal 0x002c0c00 */ set(31,0x00266738u);/* delay 00266734 */ set(4,cpu(0));body_002c0c00();
/* 00266738: mtc1 s0,f1 */ f[1]=(uint32_t)cpu(16);
/* 0026673c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00266740: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 00266744: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00266748: lwc1 f3,-0x5c3c(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa3c4)));
/* 0026674c: b 0x00266778 */ /* delay 00266750 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);goto L_00266778;
L_00266758:;
/* 00266758: jal 0x002c0c00 */ set(31,0x00266760u);/* delay 0026675c */ set(4,cpu(0));body_002c0c00();
/* 00266760: mtc1 s0,f1 */ f[1]=(uint32_t)cpu(16);
/* 00266764: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00266768: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0026676c: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00266770: lwc1 f3,-0x5c38(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa3c8)));
/* 00266774: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
L_00266778:;
/* 00266778: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 0026677c: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 00266780: mul.S f0,f1,f0 */ f[0]=EE_FPU_MUL_S(f[1],f[0]);
/* 00266784: add.S f1,f1,f0 */ f[1]=EE_FPU_ADD_S(f[1],f[0]);
/* 00266788: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0026678c: mfc1 s0,f0 */ set(16,sx(f[0]));
/* 00266790: slti v0,s0,0x0 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00266794: movn s0,zero,v0 */ if(cpu(2)!=0){set(16,cpu(0));}
L_00266798:;
/* 00266798: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 0026679c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002667a0: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 002667a4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 002667a8: mfc1 s0,f1 */ set(16,sx(f[1]));
/* 002667ac: jal 0x001e0f50 */ set(31,0x002667b4u);/* delay 002667b0 */ set(4,sx(UINT32_C(0x00000af2)));body_001e0f50();
/* 002667b4: beql v0,zero,0x002667e8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002667b8 */ set(2,sx(UINT32_C(0x00000001)));goto L_002667e8;}}
/* 002667bc: jal 0x0026a468 */ set(31,0x002667c4u);/* delay 002667c0 */ set(4,cpu(21));body_0026a468();
/* 002667c4: bne v0,zero,0x002667e8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002667c8 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002667e8;}}
/* 002667cc: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 002667d0: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002667d4: lwc1 f1,-0x5c34(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa3cc)));
/* 002667d8: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 002667dc: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 002667e0: mfc1 s0,f1 */ set(16,sx(f[1]));
L_002667e4:;
/* 002667e4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002667e8:;
/* 002667e8: movz s0,v0,s0 */ if(cpu(16)==0){set(16,cpu(2));}
/* 002667ec: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002667f0: beq v0,zero,0x00266840 */ {int taken=(cpu(2)==cpu(0));/* delay 002667f4 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));if(taken){goto L_00266840;}}
/* 002667f8: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 002667fc: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
/* 00266800: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266804: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00266808: lhu v0,0x16(v0) */ set(2,half(ea(2,(int32_t)UINT32_C(0x00000016))));
/* 0026680c: slti v1,v0,0xe */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 00266810: beql v1,zero,0x00266844 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00266814 */ set(2,cpu(16));goto L_00266844;}}
/* 00266818: slti v0,v0,0xc */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 0026681c: bnel v0,zero,0x00266844 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00266820 */ set(2,cpu(16));goto L_00266844;}}
/* 00266824: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 00266828: lhu v1,0x8(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000008))));
/* 0026682c: slt v0,v1,s0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(16));
/* 00266830: movn s0,v1,v0 */ if(cpu(2)!=0){set(16,cpu(3));}
/* 00266834: b 0x00266844 */ /* delay 00266838 */ set(2,cpu(16));goto L_00266844;
L_00266840:;
/* 00266840: move v0,s7 */ set(2,cpu(23));
L_00266844:;
/* 00266844: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00266848: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026684c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00266850: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00266854: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00266858: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0026685c: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00266860: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00266864: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00266868: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0026686c: lwc1 f20,0x60(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00266870: jr ra */ {uint64_t target=cpu(31);/* delay 00266874 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00266350(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
nocturneEffectHostFpr()[12]=bits(f12);
body_00266350();
return cpu(2);
}
static void body_00266878(void){
nocturneEffectAxisNoteEntry(0x00266878u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00266878: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 0026687c: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00266880: move s5,a2 */ set(21,cpu(6));
/* 00266884: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00266888: move s0,a3 */ set(16,cpu(7));
/* 0026688c: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 00266890: move a0,s5 */ set(4,cpu(21));
/* 00266894: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00266898: li s1,-0x1 */ set(17,sx(UINT32_C(0xffffffff)));
/* 0026689c: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002668a0: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002668a4: move s3,a1 */ set(19,cpu(5));
/* 002668a8: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002668ac: move s4,t0 */ set(20,cpu(8));
/* 002668b0: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002668b4: sll s6,s3,0x4 */ set(22,sx((uint32_t)cpu(19)<<4));
/* 002668b8: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002668bc: li s7,-0x1 */ set(23,sx(UINT32_C(0xffffffff)));
/* 002668c0: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002668c4: swc1 f20,0x60(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),f[20]);
/* 002668c8: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002668cc: jal 0x00246ab8 */ set(31,0x002668d4u);/* delay 002668d0 */ f[20]=f[12];ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002668d4: jal 0x00246ab8 */ set(31,0x002668dcu);/* delay 002668d8 */ set(4,cpu(16));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002668dc: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 002668e0: move s8,v0 */ set(30,cpu(2));
/* 002668e4: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 002668e8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002668ec: addiu a0,v1,0x7998 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00007998)));
/* 002668f0: addiu v1,v0,0x10 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 002668f4: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002668f8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002668fc: lh s2,0x20(v0) */ set(18,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000020))));
/* 00266900: lhu a0,0xa(v1) */ set(4,half(ea(3,(int32_t)UINT32_C(0x0000000a))));
/* 00266904: move a2,zero */ set(6,cpu(0));
/* 00266908: sltiu v0,a0,0x10 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0026690c: beq v0,zero,0x00266b44 */ {int taken=(cpu(2)==cpu(0));/* delay 00266910 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x0000000c))));if(taken){goto L_00266b44;}}
/* 00266914: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00266918: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 0026691c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00266920: lw v1,0x4ad0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004ad0)));
/* 00266924: jr v1 */ {uint64_t target=cpu(3);/* delay 00266928 */ switch((uint32_t)target){case 0x00266930u:goto L_00266930;case 0x00266938u:goto L_00266938;case 0x00266948u:goto L_00266948;case 0x00266950u:goto L_00266950;case 0x00266978u:goto L_00266978;case 0x002669e8u:goto L_002669e8;case 0x00266a08u:goto L_00266a08;case 0x00266a10u:goto L_00266a10;case 0x00266a18u:goto L_00266a18;case 0x00266a40u:goto L_00266a40;case 0x00266b10u:goto L_00266b10;case 0x00266b30u:goto L_00266b30;case 0x00266b44u:goto L_00266b44;default:abort();}}
L_00266930:;
/* 00266930: b 0x00266b44 */ /* delay 00266934 */ set(23,sx((uint32_t)cpu(5)+(uint32_t)cpu(18)));goto L_00266b44;
L_00266938:;
/* 00266938: jal 0x002c0c60 */ set(31,0x00266940u);/* delay 0026693c */ set(4,cpu(0));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00266940: b 0x00266b44 */ /* delay 00266944 */ set(23,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));goto L_00266b44;
L_00266948:;
/* 00266948: b 0x00266954 */ /* delay 0026694c */ set(2,half(ea(30,(int32_t)UINT32_C(0x0000000a))));goto L_00266954;
L_00266950:;
/* 00266950: lhu v0,0xc(s8) */ set(2,half(ea(30,(int32_t)UINT32_C(0x0000000c))));
L_00266954:;
/* 00266954: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00266958: beql v1,zero,0x00266960 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0026695c */ nocturneCompilerArithmeticTrap(7u);goto L_00266960;}}
L_00266960:;
/* 00266960: mult v0,v0,a1 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(5),1,0);
/* 00266964: div1 v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,1);
/* 00266968: mflo1 v0 */ set(2,secondaryLo);
/* 0026696c: b 0x00266b44 */ /* delay 00266970 */ set(23,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));goto L_00266b44;
L_00266978:;
/* 00266978: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 0026697c: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00266980: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
/* 00266984: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266988: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0026698c: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00266990: beq v1,zero,0x002669a8 */ {int taken=(cpu(3)==cpu(0));/* delay 00266994 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002669a8;}}
/* 00266998: beq v1,v0,0x002669c8 */ {int taken=(cpu(3)==cpu(2));/* delay 0026699c */ set(23,sx((uint32_t)cpu(6)+(uint32_t)cpu(18)));if(taken){goto L_002669c8;}}
/* 002669a0: b 0x00266b48 */ /* delay 002669a4 */ set(3,sx(UINT32_C(0x003d0000)));goto L_00266b48;
L_002669a8:;
/* 002669a8: move a2,s0 */ set(6,cpu(16));
/* 002669ac: move a3,a1 */ set(7,cpu(5));
/* 002669b0: move a0,s3 */ set(4,cpu(19));
/* 002669b4: jal 0x002688b8 */ set(31,0x002669bcu);/* delay 002669b8 */ set(5,cpu(21));body_002688b8();
/* 002669bc: b 0x002669e0 */ /* delay 002669c0 */ set(6,cpu(2));goto L_002669e0;
L_002669c8:;
/* 002669c8: move a2,s0 */ set(6,cpu(16));
/* 002669cc: move a3,a1 */ set(7,cpu(5));
/* 002669d0: move a0,s3 */ set(4,cpu(19));
/* 002669d4: jal 0x00268c60 */ set(31,0x002669dcu);/* delay 002669d8 */ set(5,cpu(21));body_00268c60();
/* 002669dc: move a2,v0 */ set(6,cpu(2));
L_002669e0:;
/* 002669e0: b 0x00266b44 */ /* delay 002669e4 */ set(23,sx((uint32_t)cpu(6)+(uint32_t)cpu(18)));goto L_00266b44;
L_002669e8:;
/* 002669e8: move a3,a1 */ set(7,cpu(5));
/* 002669ec: move a1,s5 */ set(5,cpu(21));
/* 002669f0: move a2,s0 */ set(6,cpu(16));
/* 002669f4: jal 0x00268d60 */ set(31,0x002669fcu);/* delay 002669f8 */ set(4,cpu(19));body_00268d60();
/* 002669fc: b 0x00266b44 */ /* delay 00266a00 */ set(23,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));goto L_00266b44;
L_00266a08:;
/* 00266a08: b 0x00266b44 */ /* delay 00266a0c */ set(17,sx((uint32_t)cpu(5)+(uint32_t)cpu(18)));goto L_00266b44;
L_00266a10:;
/* 00266a10: b 0x00266a1c */ /* delay 00266a14 */ set(2,half(ea(30,(int32_t)UINT32_C(0x0000000a))));goto L_00266a1c;
L_00266a18:;
/* 00266a18: lhu v0,0xc(s8) */ set(2,half(ea(30,(int32_t)UINT32_C(0x0000000c))));
L_00266a1c:;
/* 00266a1c: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00266a20: beql v1,zero,0x00266a28 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00266a24 */ nocturneCompilerArithmeticTrap(7u);goto L_00266a28;}}
L_00266a28:;
/* 00266a28: mult v0,v0,a1 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(5),1,0);
/* 00266a2c: div1 v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,1);
/* 00266a30: mflo1 v0 */ set(2,secondaryLo);
/* 00266a34: b 0x00266b44 */ /* delay 00266a38 */ set(17,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));goto L_00266b44;
L_00266a40:;
/* 00266a40: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 00266a44: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00266a48: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
/* 00266a4c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266a50: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00266a54: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00266a58: beq v1,zero,0x00266a70 */ {int taken=(cpu(3)==cpu(0));/* delay 00266a5c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00266a70;}}
/* 00266a60: beq v1,v0,0x00266a90 */ {int taken=(cpu(3)==cpu(2));/* delay 00266a64 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));if(taken){goto L_00266a90;}}
/* 00266a68: b 0x00266ab4 */ /* delay 00266a6c */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));goto L_00266ab4;
L_00266a70:;
/* 00266a70: move a2,s0 */ set(6,cpu(16));
/* 00266a74: move a3,a1 */ set(7,cpu(5));
/* 00266a78: move a0,s3 */ set(4,cpu(19));
/* 00266a7c: jal 0x00268620 */ set(31,0x00266a84u);/* delay 00266a80 */ set(5,cpu(21));body_00268620();
/* 00266a84: b 0x00266aa8 */ /* delay 00266a88 */ set(6,cpu(2));goto L_00266aa8;
L_00266a90:;
/* 00266a90: move a2,s0 */ set(6,cpu(16));
/* 00266a94: move a3,a1 */ set(7,cpu(5));
/* 00266a98: move a0,s3 */ set(4,cpu(19));
/* 00266a9c: jal 0x002688d0 */ set(31,0x00266aa4u);/* delay 00266aa0 */ set(5,cpu(21));body_002688d0();
/* 00266aa4: move a2,v0 */ set(6,cpu(2));
L_00266aa8:;
/* 00266aa8: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00266aac: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 00266ab0: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
L_00266ab4:;
/* 00266ab4: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
/* 00266ab8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266abc: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00266ac0: lhu v1,0x1a(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x0000001a))));
/* 00266ac4: bne v1,a0,0x00266ae0 */ {int taken=(cpu(3)!=cpu(4));/* delay 00266ac8 */ set(2,sx(UINT32_C(0x0000000e)));if(taken){goto L_00266ae0;}}
/* 00266acc: mtc1 a2,f0 */ f[0]=(uint32_t)cpu(6);
/* 00266ad0: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00266ad4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00266ad8: mfc1 a2,f1 */ set(6,sx(f[1]));
/* 00266adc: li v0,0xe */ set(2,sx(UINT32_C(0x0000000e)));
L_00266ae0:;
/* 00266ae0: bne v1,v0,0x00266b44 */ {int taken=(cpu(3)!=cpu(2));/* delay 00266ae4 */ set(17,sx((uint32_t)cpu(6)+(uint32_t)cpu(18)));if(taken){goto L_00266b44;}}
/* 00266ae8: slti v0,s4,0x2 */ set(2,(int64_t)cpu(20)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00266aec: bne v0,zero,0x00266b48 */ {int taken=(cpu(2)!=cpu(0));/* delay 00266af0 */ set(3,sx(UINT32_C(0x003d0000)));if(taken){goto L_00266b48;}}
/* 00266af4: div s1,s4 */ nativeDivide((uint32_t)cpu(17),(uint32_t)cpu(20),1,0);
/* 00266af8: beql s4,zero,0x00266b00 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00266afc */ nocturneCompilerArithmeticTrap(7u);goto L_00266b00;}}
L_00266b00:;
/* 00266b00: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00266b04: b 0x00266b44 */ /* delay 00266b08 */ set(17,cpu(2));goto L_00266b44;
L_00266b10:;
/* 00266b10: move a3,a1 */ set(7,cpu(5));
/* 00266b14: move a1,s5 */ set(5,cpu(21));
/* 00266b18: move a2,s0 */ set(6,cpu(16));
/* 00266b1c: jal 0x00268d60 */ set(31,0x00266b24u);/* delay 00266b20 */ set(4,cpu(19));body_00268d60();
/* 00266b24: b 0x00266b44 */ /* delay 00266b28 */ set(17,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));goto L_00266b44;
L_00266b30:;
/* 00266b30: lhu v0,0xa(s8) */ set(2,half(ea(30,(int32_t)UINT32_C(0x0000000a))));
/* 00266b34: addu v1,a1,s2 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(18)));
/* 00266b38: subu a0,v0,v1 */ set(4,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 00266b3c: slt v1,v1,v0 */ set(3,(int64_t)cpu(3)<(int64_t)cpu(2));
/* 00266b40: movn s1,a0,v1 */ if(cpu(3)!=0){set(17,cpu(4));}
L_00266b44:;
/* 00266b44: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
L_00266b48:;
/* 00266b48: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 00266b4c: addiu a0,v1,0x7998 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00007998)));
/* 00266b50: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266b54: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00266b58: lhu v1,0x1a(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x0000001a))));
/* 00266b5c: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 00266b60: sltiu v0,v1,0xe */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 00266b64: beq v0,zero,0x00266c48 */ {int taken=(cpu(2)==cpu(0));/* delay 00266b68 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00266c48;}}
/* 00266b6c: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 00266b70: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00266b74: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00266b78: lw v1,0x4b10(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004b10)));
/* 00266b7c: jr v1 */ {uint64_t target=cpu(3);/* delay 00266b80 */ switch((uint32_t)target){case 0x00266b88u:goto L_00266b88;case 0x00266c44u:goto L_00266c44;default:abort();}}
L_00266b88:;
/* 00266b88: blez s1,0x00266c48 */ {int taken=((int64_t)cpu(17)<=0);/* delay 00266b8c */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00266c48;}}
/* 00266b90: subu v0,s6,s3 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(19)));
/* 00266b94: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00266b98: addiu v1,a0,0x7998 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00007998)));
/* 00266b9c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266ba0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00266ba4: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00266ba8: beq v1,zero,0x00266bb8 */ {int taken=(cpu(3)==cpu(0));/* delay 00266bac */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00266bb8;}}
/* 00266bb0: bne v1,v0,0x00266bf4 */ {int taken=(cpu(3)!=cpu(2));/* delay 00266bb4 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000000));if(taken){goto L_00266bf4;}}
L_00266bb8:;
/* 00266bb8: jal 0x002c0c00 */ set(31,0x00266bc0u);/* delay 00266bbc */ set(4,cpu(0));body_002c0c00();
/* 00266bc0: mtc1 s1,f1 */ f[1]=(uint32_t)cpu(17);
/* 00266bc4: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00266bc8: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 00266bcc: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00266bd0: lwc1 f3,-0x5c30(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa3d0)));
/* 00266bd4: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
/* 00266bd8: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 00266bdc: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 00266be0: mul.S f0,f1,f0 */ f[0]=EE_FPU_MUL_S(f[1],f[0]);
/* 00266be4: add.S f1,f1,f0 */ f[1]=EE_FPU_ADD_S(f[1],f[0]);
/* 00266be8: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 00266bec: mfc1 s1,f0 */ set(17,sx(f[0]));
/* 00266bf0: slti v0,s1,0x0 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000000));
L_00266bf4:;
/* 00266bf4: movn s1,zero,v0 */ if(cpu(2)!=0){set(17,cpu(0));}
/* 00266bf8: mtc1 s1,f0 */ f[0]=(uint32_t)cpu(17);
/* 00266bfc: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00266c00: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 00266c04: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00266c08: mfc1 s1,f1 */ set(17,sx(f[1]));
/* 00266c0c: jal 0x001e0f50 */ set(31,0x00266c14u);/* delay 00266c10 */ set(4,sx(UINT32_C(0x00000af2)));body_001e0f50();
/* 00266c14: beql v0,zero,0x00266c48 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00266c18 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00266c48;}}
/* 00266c1c: jal 0x0026a468 */ set(31,0x00266c24u);/* delay 00266c20 */ set(4,cpu(21));body_0026a468();
/* 00266c24: bne v0,zero,0x00266c48 */ {int taken=(cpu(2)!=cpu(0));/* delay 00266c28 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00266c48;}}
/* 00266c2c: mtc1 s1,f0 */ f[0]=(uint32_t)cpu(17);
/* 00266c30: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00266c34: lwc1 f1,-0x5c2c(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa3d4)));
/* 00266c38: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 00266c3c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00266c40: mfc1 s1,f1 */ set(17,sx(f[1]));
L_00266c44:;
/* 00266c44: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00266c48:;
/* 00266c48: beql v0,zero,0x00266c5c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00266c4c */ set(2,cpu(23));goto L_00266c5c;}}
/* 00266c50: lhu v0,0xa(s8) */ set(2,half(ea(30,(int32_t)UINT32_C(0x0000000a))));
/* 00266c54: slt v1,v0,s1 */ set(3,(int64_t)cpu(2)<(int64_t)cpu(17));
/* 00266c58: movz v0,s1,v1 */ if(cpu(3)==0){set(2,cpu(17));}
L_00266c5c:;
/* 00266c5c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00266c60: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00266c64: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00266c68: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00266c6c: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00266c70: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00266c74: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00266c78: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00266c7c: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00266c80: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00266c84: lwc1 f20,0x60(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00266c88: jr ra */ {uint64_t target=cpu(31);/* delay 00266c8c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00266878(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
nocturneEffectHostFpr()[12]=bits(f12);
body_00266878();
return cpu(2);
}
static void body_00266c90(void){
nocturneEffectAxisNoteEntry(0x00266c90u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00266c90: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 00266c94: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 00266c98: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266c9c: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 00266ca0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00266ca4: lhu v1,0x79ae(v1) */ set(3,half(ea(3,(int32_t)UINT32_C(0x000079ae))));
/* 00266ca8: slti v0,v1,0xc */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 00266cac: slti v1,v1,0xe */ set(3,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 00266cb0: beq v1,zero,0x00266cc8 */ {int taken=(cpu(3)==cpu(0));/* delay 00266cb4 */ if(taken){goto L_00266cc8;}}
/* 00266cb8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00266cbc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00266cc0: beq v0,zero,0x00266ccc */ {int taken=(cpu(2)==cpu(0));/* delay 00266cc4 */ if(taken){goto L_00266ccc;}}
L_00266cc8:;
/* 00266cc8: clear f0 */ f[0]=0;
L_00266ccc:;
/* 00266ccc: jr ra */ {uint64_t target=cpu(31);/* delay 00266cd0 */ checkReturn(target,incoming);return;}
}
float ps2BattleActionFormula_00266C90(uint64_t a0){
set(4,a0);
body_00266c90();
return real(nocturneEffectHostFpr()[0]);
}
static void body_00266cd8(void){
nocturneEffectAxisNoteEntry(0x00266cd8u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00266cd8: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 00266cdc: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 00266ce0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266ce4: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 00266ce8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00266cec: lhu v1,0x79b2(v1) */ set(3,half(ea(3,(int32_t)UINT32_C(0x000079b2))));
/* 00266cf0: slti v0,v1,0xc */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 00266cf4: slti v1,v1,0xe */ set(3,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 00266cf8: beq v1,zero,0x00266d10 */ {int taken=(cpu(3)==cpu(0));/* delay 00266cfc */ if(taken){goto L_00266d10;}}
/* 00266d00: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00266d04: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00266d08: beq v0,zero,0x00266d14 */ {int taken=(cpu(2)==cpu(0));/* delay 00266d0c */ if(taken){goto L_00266d14;}}
L_00266d10:;
/* 00266d10: clear f0 */ f[0]=0;
L_00266d14:;
/* 00266d14: jr ra */ {uint64_t target=cpu(31);/* delay 00266d18 */ checkReturn(target,incoming);return;}
}
float ps2BattleActionFormula_00266CD8(uint64_t a0){
set(4,a0);
body_00266cd8();
return real(nocturneEffectHostFpr()[0]);
}
static void body_00266d20(void){
nocturneEffectAxisNoteEntry(0x00266d20u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00266d20: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 00266d24: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00266d28: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00266d2c: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 00266d30: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266d34: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 00266d38: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00266d3c: lhu v1,0x79ba(v1) */ set(3,half(ea(3,(int32_t)UINT32_C(0x000079ba))));
/* 00266d40: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00266d44: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00266d48: nop  */ 
/* 00266d4c: nop  */ 
/* 00266d50: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 00266d54: jr ra */ {uint64_t target=cpu(31);/* delay 00266d58 */ checkReturn(target,incoming);return;}
}
float ps2BattleActionFormula_00266D20(uint64_t a0){
set(4,a0);
body_00266d20();
return real(nocturneEffectHostFpr()[0]);
}
static void body_00266d60(void){
nocturneEffectAxisNoteEntry(0x00266d60u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00266d60: addiu sp,sp,-0xb0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff50)));
/* 00266d64: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00266d68: move s0,a0 */ set(16,cpu(4));
/* 00266d6c: sd s1,0x48(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00266d70: move s1,a1 */ set(17,cpu(5));
/* 00266d74: sd s3,0x58(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00266d78: sll s3,s0,0x4 */ set(19,sx((uint32_t)cpu(16)<<4));
/* 00266d7c: sd s4,0x60(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00266d80: move s4,a2 */ set(20,cpu(6));
/* 00266d84: sd s5,0x68(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00266d88: sd s7,0x78(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00266d8c: move s7,a3 */ set(23,cpu(7));
/* 00266d90: sd s8,0x80(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00266d94: lui s8,0x3d */ set(30,sx(UINT32_C(0x003d0000)));
/* 00266d98: swc1 f20,0x90(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000090)),f[20]);
/* 00266d9c: mov.S f20,f12 */ f[20]=f[12];
/* 00266da0: sd s2,0x50(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00266da4: sd s6,0x70(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 00266da8: sd ra,0x88(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 00266dac: swc1 f22,0xa0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000a0)),f[22]);
/* 00266db0: jal 0x002469a0 */ set(31,0x00266db8u);/* delay 00266db4 */ sw(ea(29,(int32_t)UINT32_C(0x00000098)),f[21]);ps2BattleActionScaleLookup_002469A0();
/* 00266db8: move s5,v0 */ set(21,cpu(2));
/* 00266dbc: subu v0,s3,s0 */ set(2,sx((uint32_t)cpu(19)-(uint32_t)cpu(16)));
/* 00266dc0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266dc4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00266dc8: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00266dcc: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00266dd0: lbu a0,0x79bc(a0) */ set(4,byte(ea(4,(int32_t)UINT32_C(0x000079bc))));
/* 00266dd4: beq a0,v1,0x00266de4 */ {int taken=(cpu(4)==cpu(3));/* delay 00266dd8 */ set(3,sx(UINT32_C(0x00000003)));if(taken){goto L_00266de4;}}
/* 00266ddc: bne a0,v1,0x00267140 */ {int taken=(cpu(4)!=cpu(3));/* delay 00266de0 */ set(2,cpu(0));if(taken){goto L_00267140;}}
L_00266de4:;
/* 00266de4: jal 0x00246ab8 */ set(31,0x00266decu);/* delay 00266de8 */ set(4,cpu(17));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00266dec: move a0,s4 */ set(4,cpu(20));
/* 00266df0: jal 0x00246ab8 */ set(31,0x00266df8u);/* delay 00266df4 */ set(22,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00266df8: move s1,v0 */ set(17,cpu(2));
/* 00266dfc: subu v0,s3,s0 */ set(2,sx((uint32_t)cpu(19)-(uint32_t)cpu(16)));
/* 00266e00: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266e04: addiu a0,s8,0x7998 */ set(4,sx((uint32_t)cpu(30)+UINT32_C(0x00007998)));
/* 00266e08: addiu v0,v0,0x20 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 00266e0c: li a1,0x110 */ set(5,sx(UINT32_C(0x00000110)));
/* 00266e10: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00266e14: lhu v1,0x6(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000006))));
/* 00266e18: bne s0,a1,0x00266e78 */ {int taken=(cpu(16)!=cpu(5));/* delay 00266e1c */ set(18,cpu(3)&UINT32_C(0x00007fff));if(taken){goto L_00266e78;}}
/* 00266e20: move a0,zero */ set(4,cpu(0));
/* 00266e24: jal 0x002c0c60 */ set(31,0x00266e2cu);/* delay 00266e28 */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00266e2c: move v1,v0 */ set(3,cpu(2));
/* 00266e30: slti v0,v1,0x28 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000028));
/* 00266e34: bne v0,zero,0x00266edc */ {int taken=(cpu(2)!=cpu(0));/* delay 00266e38 */ set(18,sx(UINT32_C(0x00001000)));if(taken){goto L_00266edc;}}
/* 00266e3c: slti v0,v1,0x3c */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000003c));
/* 00266e40: bne v0,zero,0x00266edc */ {int taken=(cpu(2)!=cpu(0));/* delay 00266e44 */ set(18,sx(UINT32_C(0x00002000)));if(taken){goto L_00266edc;}}
/* 00266e48: slti v0,v1,0x46 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000046));
/* 00266e4c: bne v0,zero,0x00266edc */ {int taken=(cpu(2)!=cpu(0));/* delay 00266e50 */ set(18,sx(UINT32_C(0x00004000)));if(taken){goto L_00266edc;}}
/* 00266e54: slti v0,v1,0x50 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000050));
/* 00266e58: bne v0,zero,0x00266edc */ {int taken=(cpu(2)!=cpu(0));/* delay 00266e5c */ set(18,sx(UINT32_C(0x00000020)));if(taken){goto L_00266edc;}}
/* 00266e60: slti v1,v1,0x5a */ set(3,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000005a));
/* 00266e64: li v0,0x40 */ set(2,sx(UINT32_C(0x00000040)));
/* 00266e68: li s2,0x100 */ set(18,sx(UINT32_C(0x00000100)));
/* 00266e6c: b 0x00266edc */ /* delay 00266e70 */ if(cpu(3)==0){set(18,cpu(2));}goto L_00266edc;
L_00266e78:;
/* 00266e78: lbu v1,0x4(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 00266e7c: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 00266e80: bne v1,v0,0x00266edc */ {int taken=(cpu(3)!=cpu(2));/* delay 00266e84 */ set(5,cpu(0));if(taken){goto L_00266edc;}}
/* 00266e88: move v1,zero */ set(3,cpu(0));
/* 00266e8c: move a0,sp */ set(4,cpu(29));
/* 00266e90: srav v0,s2,v1 */ set(2,sx((uint32_t)((int32_t)(uint32_t)cpu(18)>>((uint32_t)cpu(3)&31u))));
/* 00266e94: nop  */ 
L_00266e98:;
/* 00266e98: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 00266e9c: beql v0,zero,0x00266eb4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00266ea0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));goto L_00266eb4;}}
/* 00266ea4: sw v1,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 00266ea8: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 00266eac: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 00266eb0: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
L_00266eb4:;
/* 00266eb4: slti v0,v1,0xe */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 00266eb8: bnel v0,zero,0x00266e98 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00266ebc */ set(2,sx((uint32_t)((int32_t)(uint32_t)cpu(18)>>((uint32_t)cpu(3)&31u))));goto L_00266e98;}}
/* 00266ec0: jal 0x002c0c60 */ set(31,0x00266ec8u);/* delay 00266ec4 */ set(4,cpu(0));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00266ec8: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00266ecc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266ed0: addu v1,sp,v0 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(2)));
/* 00266ed4: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00266ed8: sllv s2,a0,v0 */ set(18,sx((uint32_t)((uint32_t)cpu(4)<<((uint32_t)cpu(2)&31u))));
L_00266edc:;
/* 00266edc: jal 0x002440c0 */ set(31,0x00266ee4u);/* delay 00266ee0 */ set(4,cpu(18));body_002440c0();
/* 00266ee4: move a0,s0 */ set(4,cpu(16));
/* 00266ee8: move a1,s4 */ set(5,cpu(20));
/* 00266eec: jal 0x00267890 */ set(31,0x00266ef4u);/* delay 00266ef0 */ set(6,cpu(2));body_00267890();
/* 00266ef4: lui v1,0x17 */ set(3,sx(UINT32_C(0x00170000)));
/* 00266ef8: move a0,v0 */ set(4,cpu(2));
/* 00266efc: and v1,a0,v1 */ set(3,cpu(4)&cpu(3));
/* 00266f00: bne v1,zero,0x00267140 */ {int taken=(cpu(3)!=cpu(0));/* delay 00266f04 */ set(2,cpu(0));if(taken){goto L_00267140;}}
/* 00266f08: li v0,0x800 */ set(2,sx(UINT32_C(0x00000800)));
/* 00266f0c: beq s2,v0,0x00266f34 */ {int taken=(cpu(18)==cpu(2));/* delay 00266f10 */ f[22]=f[20];if(taken){goto L_00266f34;}}
/* 00266f14: andi v0,a0,0xffff */ set(2,cpu(4)&UINT32_C(0x0000ffff));
/* 00266f18: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00266f1c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00266f20: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00266f24: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00266f28: nop  */ 
/* 00266f2c: nop  */ 
/* 00266f30: div.S f22,f0,f1 */ f[22]=EE_FPU_DIV_S(f[0],f[1]);
L_00266f34:;
/* 00266f34: li v0,0x10a */ set(2,sx(UINT32_C(0x0000010a)));
/* 00266f38: bne s0,v0,0x00266f74 */ {int taken=(cpu(16)!=cpu(2));/* delay 00266f3c */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0xfffffefd)));if(taken){goto L_00266f74;}}
/* 00266f40: lw v0,0x60(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000060)));
/* 00266f44: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 00266f48: beq v0,zero,0x00266f74 */ {int taken=(cpu(2)==cpu(0));/* delay 00266f4c */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0xfffffefd)));if(taken){goto L_00266f74;}}
/* 00266f50: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00266f54: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00266f58: beq v0,zero,0x00266f70 */ {int taken=(cpu(2)==cpu(0));/* delay 00266f5c */ set(4,sx(UINT32_C(0x00540000)));if(taken){goto L_00266f70;}}
/* 00266f60: jal 0x002d4748 */ set(31,0x00266f68u);/* delay 00266f64 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004b48)));ps2BattleActionPrintf_002D4748(cpu(4));
/* 00266f68: b 0x00267140 */ /* delay 00266f6c */ set(2,cpu(0));goto L_00267140;
L_00266f70:;
/* 00266f70: addiu v0,s0,-0x103 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0xfffffefd)));
L_00266f74:;
/* 00266f74: sltiu v0,v0,0x2 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00266f78: beql v0,zero,0x00266fb4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00266f7c */ set(2,sx(UINT32_C(0x0000004f)));goto L_00266fb4;}}
/* 00266f80: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 00266f84: move a1,s4 */ set(5,cpu(20));
/* 00266f88: jal 0x00267890 */ set(31,0x00266f90u);/* delay 00266f8c */ set(6,sx(UINT32_C(0x00000007)));body_00267890();
/* 00266f90: lui v1,0x7 */ set(3,sx(UINT32_C(0x00070000)));
/* 00266f94: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 00266f98: beq v0,zero,0x00266fb0 */ {int taken=(cpu(2)==cpu(0));/* delay 00266f9c */ set(4,sx(UINT32_C(0x00540000)));if(taken){goto L_00266fb0;}}
/* 00266fa0: jal 0x002d4748 */ set(31,0x00266fa8u);/* delay 00266fa4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004b68)));ps2BattleActionPrintf_002D4748(cpu(4));
/* 00266fa8: b 0x00267140 */ /* delay 00266fac */ set(2,cpu(0));goto L_00267140;
L_00266fb0:;
/* 00266fb0: li v0,0x4f */ set(2,sx(UINT32_C(0x0000004f)));
L_00266fb4:;
/* 00266fb4: bne s0,v0,0x00266fe0 */ {int taken=(cpu(16)!=cpu(2));/* delay 00266fb8 */ set(2,sx((uint32_t)cpu(19)-(uint32_t)cpu(16)));if(taken){goto L_00266fe0;}}
/* 00266fbc: lhu v0,0xe(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 00266fc0: andi v0,v0,0x40 */ set(2,cpu(2)&UINT32_C(0x00000040));
/* 00266fc4: bnel v0,zero,0x00266fe0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00266fc8 */ set(2,sx((uint32_t)cpu(19)-(uint32_t)cpu(16)));goto L_00266fe0;}}
/* 00266fcc: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00266fd0: jal 0x002d4748 */ set(31,0x00266fd8u);/* delay 00266fd4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004b88)));ps2BattleActionPrintf_002D4748(cpu(4));
/* 00266fd8: b 0x00267140 */ /* delay 00266fdc */ set(2,cpu(0));goto L_00267140;
L_00266fe0:;
/* 00266fe0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00266fe4: addiu a0,s8,0x7998 */ set(4,sx((uint32_t)cpu(30)+UINT32_C(0x00007998)));
/* 00266fe8: addiu v0,v0,0x20 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 00266fec: li a1,0xff */ set(5,sx(UINT32_C(0x000000ff)));
/* 00266ff0: addu a0,v0,a0 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00266ff4: lbu v1,0x5(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000005))));
/* 00266ff8: beq v1,a1,0x00267120 */ {int taken=(cpu(3)==cpu(5));/* delay 00266ffc */ set(16,sx(UINT32_C(0x00000001)));if(taken){goto L_00267120;}}
/* 00267000: bne s7,zero,0x00267120 */ {int taken=(cpu(23)!=cpu(0));/* delay 00267004 */ if(taken){goto L_00267120;}}
/* 00267008: lw v0,0x0(s6) */ lw(2,ea(22,(int32_t)UINT32_C(0x00000000)));
/* 0026700c: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00267010: mtc1 v1,f21 */ f[21]=(uint32_t)cpu(3);
/* 00267014: cvt.s.W f21,f21 */ f[21]=EE_FPU_CVT_S_W(f[21]);
/* 00267018: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 0026701c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00267020: nop  */ 
/* 00267024: nop  */ 
/* 00267028: div.S f0,f21,f1 */ f[0]=EE_FPU_DIV_S(f[21],f[1]);
/* 0026702c: mul.S f0,f0,f22 */ f[0]=EE_FPU_MUL_S(f[0],f[22]);
/* 00267030: mul.S f20,f0,f1 */ f[20]=EE_FPU_MUL_S(f[0],f[1]);
/* 00267034: jal 0x001e0f50 */ set(31,0x0026703cu);/* delay 00267038 */ set(4,sx(UINT32_C(0x00000af2)));body_001e0f50();
/* 0026703c: beq v0,zero,0x00267098 */ {int taken=(cpu(2)==cpu(0));/* delay 00267040 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00267098;}}
/* 00267044: andi v0,v1,0x20 */ set(2,cpu(3)&UINT32_C(0x00000020));
/* 00267048: bnel v0,zero,0x002670d8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0026704c */ set(4,cpu(0));goto L_002670d8;}}
/* 00267050: li v0,0x800 */ set(2,sx(UINT32_C(0x00000800)));
/* 00267054: bne s2,v0,0x00267088 */ {int taken=(cpu(18)!=cpu(2));/* delay 00267058 */ set(2,cpu(3)&UINT32_C(0x00000004));if(taken){goto L_00267088;}}
/* 0026705c: beq v0,zero,0x00267078 */ {int taken=(cpu(2)==cpu(0));/* delay 00267060 */ if(taken){goto L_00267078;}}
/* 00267064: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 00267068: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0026706c: b 0x002670d4 */ /* delay 00267070 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);goto L_002670d4;
L_00267078:;
/* 00267078: lwc1 f0,-0x5c28(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa3d8)));
/* 0026707c: b 0x002670d4 */ /* delay 00267080 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);goto L_002670d4;
L_00267088:;
/* 00267088: lwc1 f0,-0x5c24(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa3dc)));
/* 0026708c: b 0x002670d4 */ /* delay 00267090 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);goto L_002670d4;
L_00267098:;
/* 00267098: andi v0,v1,0x20 */ set(2,cpu(3)&UINT32_C(0x00000020));
/* 0026709c: bne v0,zero,0x002670d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002670a0 */ set(4,cpu(0));if(taken){goto L_002670d8;}}
/* 002670a4: li v0,0x800 */ set(2,sx(UINT32_C(0x00000800)));
/* 002670a8: bne s2,v0,0x002670d8 */ {int taken=(cpu(18)!=cpu(2));/* delay 002670ac */ set(2,cpu(3)&UINT32_C(0x00000004));if(taken){goto L_002670d8;}}
/* 002670b0: beq v0,zero,0x002670c8 */ {int taken=(cpu(2)==cpu(0));/* delay 002670b4 */ if(taken){goto L_002670c8;}}
/* 002670b8: lwc1 f0,-0x5c20(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa3e0)));
/* 002670bc: b 0x002670d8 */ /* delay 002670c0 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);goto L_002670d8;
L_002670c8:;
/* 002670c8: lui at,0x3fc0 */ set(1,sx(UINT32_C(0x3fc00000)));
/* 002670cc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002670d0: mul.S f20,f20,f0 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);
L_002670d4:;
/* 002670d4: move a0,zero */ set(4,cpu(0));
L_002670d8:;
/* 002670d8: jal 0x002c0c60 */ set(31,0x002670e0u);/* delay 002670dc */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 002670e0: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 002670e4: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 002670e8: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002670ec: move s1,v0 */ set(17,cpu(2));
/* 002670f0: cvt.w.S f1,f20 */ f[1]=EE_FPU_CVT_W_S(f[20]);
/* 002670f4: mfc1 s0,f1 */ set(16,sx(f[1]));
/* 002670f8: addiu a0,a0,0x4ba8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004ba8)));
/* 002670fc: mul.S f0,f22,f0 */ f[0]=EE_FPU_MUL_S(f[22],f[0]);
/* 00267100: move t0,s1 */ set(8,cpu(17));
/* 00267104: cvt.w.S f1,f21 */ f[1]=EE_FPU_CVT_W_S(f[21]);
/* 00267108: mfc1 a1,f1 */ set(5,sx(f[1]));
/* 0026710c: move a3,s0 */ set(7,cpu(16));
/* 00267110: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00267114: mfc1 a2,f1 */ set(6,sx(f[1]));
/* 00267118: jal 0x002d4748 */ set(31,0x00267120u);/* delay 0026711c */ set(16,(int64_t)cpu(17)<(int64_t)cpu(16));ps2BattleActionPrintf_002D4748(cpu(4));
L_00267120:;
/* 00267120: beq s0,zero,0x00267140 */ {int taken=(cpu(16)==cpu(0));/* delay 00267124 */ set(2,cpu(0));if(taken){goto L_00267140;}}
/* 00267128: jal 0x00267788 */ set(31,0x00267130u);/* delay 0026712c */ set(4,cpu(20));ps2BattleActionPacket_00267788(cpu(4));
/* 00267130: slt v1,v0,s2 */ set(3,(int64_t)cpu(2)<(int64_t)cpu(18));
/* 00267134: bne v1,zero,0x00267140 */ {int taken=(cpu(3)!=cpu(0));/* delay 00267138 */ set(2,cpu(18));if(taken){goto L_00267140;}}
/* 0026713c: move v0,zero */ set(2,cpu(0));
L_00267140:;
/* 00267140: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00267144: ld s1,0x48(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00267148: ld s2,0x50(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0026714c: ld s3,0x58(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00267150: ld s4,0x60(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00267154: ld s5,0x68(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00267158: ld s6,0x70(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0026715c: ld s7,0x78(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00267160: ld s8,0x80(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00267164: ld ra,0x88(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 00267168: lwc1 f22,0xa0(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0026716c: lwc1 f21,0x98(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00267170: lwc1 f20,0x90(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000090)));
/* 00267174: jr ra */ {uint64_t target=cpu(31);/* delay 00267178 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000b0)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00266D60(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
nocturneEffectHostFpr()[12]=bits(f12);
body_00266d60();
return cpu(2);
}
static void body_00267180(void){
nocturneEffectAxisNoteEntry(0x00267180u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00267180: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 00267184: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 00267188: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0026718c: move a0,a1 */ set(4,cpu(5));
/* 00267190: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267194: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00267198: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026719c: move s1,a2 */ set(17,cpu(6));
/* 002671a0: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002671a4: move s5,a3 */ set(21,cpu(7));
/* 002671a8: swc1 f22,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),f[22]);
/* 002671ac: mov.S f22,f12 */ f[22]=f[12];
/* 002671b0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002671b4: lui s0,0x3d */ set(16,sx(UINT32_C(0x003d0000)));
/* 002671b8: addiu s0,s0,0x79b8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000079b8)));
/* 002671bc: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002671c0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002671c4: li t0,0x2 */ set(8,sx(UINT32_C(0x00000002)));
/* 002671c8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002671cc: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002671d0: swc1 f21,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),f[21]);
/* 002671d4: swc1 f20,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[20]);
/* 002671d8: lbu v1,0x4(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000004))));
/* 002671dc: bne v1,t0,0x0026733c */ {int taken=(cpu(3)!=cpu(8));/* delay 002671e0 */ set(2,cpu(0));if(taken){goto L_0026733c;}}
/* 002671e4: jal 0x00246ab8 */ set(31,0x002671ecu);/* delay 002671e8 */ ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002671ec: move a0,s1 */ set(4,cpu(17));
/* 002671f0: jal 0x00246ab8 */ set(31,0x002671f8u);/* delay 002671f4 */ set(20,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002671f8: move s2,v0 */ set(18,cpu(2));
/* 002671fc: lhu v0,0x6(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 00267200: lbu a0,0x5(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000005))));
/* 00267204: li v1,0xff */ set(3,sx(UINT32_C(0x000000ff)));
/* 00267208: andi s3,v0,0xfff */ set(19,cpu(2)&UINT32_C(0x00000fff));
/* 0026720c: beq a0,v1,0x002672f8 */ {int taken=(cpu(4)==cpu(3));/* delay 00267210 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002672f8;}}
/* 00267214: bne s5,zero,0x002672f8 */ {int taken=(cpu(21)!=cpu(0));/* delay 00267218 */ if(taken){goto L_002672f8;}}
/* 0026721c: lbu v0,0x5(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000005))));
/* 00267220: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 00267224: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00267228: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 0026722c: mtc1 v0,f20 */ f[20]=(uint32_t)cpu(2);
/* 00267230: cvt.s.W f20,f20 */ f[20]=EE_FPU_CVT_S_W(f[20]);
/* 00267234: jal 0x00243ee0 */ set(31,0x0026723cu);/* delay 00267238 */ set(4,cpu(20));body_00243ee0();
/* 0026723c: move a0,s4 */ set(4,cpu(20));
/* 00267240: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 00267244: jal 0x00243ee0 */ set(31,0x0026724cu);/* delay 00267248 */ set(16,cpu(2));body_00243ee0();
/* 0026724c: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00267250: addiu a1,v0,0x3 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000003)));
/* 00267254: movn v0,a1,v1 */ if(cpu(3)!=0){set(2,cpu(5));}
/* 00267258: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 0026725c: sra v0,v0,0x2 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>2)));
/* 00267260: move a0,s2 */ set(4,cpu(18));
/* 00267264: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00267268: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 0026726c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00267270: lui s0,0x54 */ set(16,sx(UINT32_C(0x00540000)));
/* 00267274: addiu s0,s0,0x4be8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00004be8)));
/* 00267278: jal 0x00243ee0 */ set(31,0x00267280u);/* delay 0026727c */ f[20]=EE_FPU_MUL_S(f[20],f[0]);body_00243ee0();
/* 00267280: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 00267284: move a0,s2 */ set(4,cpu(18));
/* 00267288: jal 0x00243ee0 */ set(31,0x00267290u);/* delay 0026728c */ set(17,cpu(2));body_00243ee0();
/* 00267290: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00267294: addiu a0,v0,0x3 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000003)));
/* 00267298: movn v0,a0,v1 */ if(cpu(3)!=0){set(2,cpu(4));}
/* 0026729c: nop  */ 
/* 002672a0: nop  */ 
/* 002672a4: div.S f20,f20,f21 */ f[20]=EE_FPU_DIV_S(f[20],f[21]);
/* 002672a8: sra v0,v0,0x2 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>2)));
/* 002672ac: mul.S f21,f22,f21 */ f[21]=EE_FPU_MUL_S(f[22],f[21]);
/* 002672b0: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002672b4: mtc1 s1,f0 */ f[0]=(uint32_t)cpu(17);
/* 002672b8: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002672bc: nop  */ 
/* 002672c0: nop  */ 
/* 002672c4: div.S f21,f21,f0 */ f[21]=EE_FPU_DIV_S(f[21],f[0]);
/* 002672c8: mul.S f20,f20,f21 */ f[20]=EE_FPU_MUL_S(f[20],f[21]);
/* 002672cc: jal 0x002d1550 */ set(31,0x002672d4u);/* delay 002672d0 */ f[12]=f[20];ps2EffectSoftDoubleFromFloat_002D1550(real(f[12]));
/* 002672d4: move a1,v0 */ set(5,cpu(2));
/* 002672d8: jal 0x002d4748 */ set(31,0x002672e0u);/* delay 002672dc */ set(4,cpu(16));ps2BattleActionPrintf_002D4748(cpu(4));
/* 002672e0: move a0,zero */ set(4,cpu(0));
/* 002672e4: jal 0x002c0c60 */ set(31,0x002672ecu);/* delay 002672e8 */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 002672ec: cvt.w.S f0,f20 */ f[0]=EE_FPU_CVT_W_S(f[20]);
/* 002672f0: mfc1 v1,f0 */ set(3,sx(f[0]));
/* 002672f4: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
L_002672f8:;
/* 002672f8: beql v0,zero,0x0026733c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002672fc */ set(2,cpu(0));goto L_0026733c;}}
/* 00267300: beql s5,zero,0x00267328 */ {int taken=(cpu(21)==cpu(0));if(taken){/* delay 00267304 */ set(3,half(ea(18,(int32_t)UINT32_C(0x0000000e))));goto L_00267328;}}
/* 00267308: lhu v0,0xe(s2) */ set(2,half(ea(18,(int32_t)UINT32_C(0x0000000e))));
/* 0026730c: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 00267310: and v0,s3,v0 */ set(2,cpu(19)&cpu(2));
/* 00267314: beq v0,zero,0x00267338 */ {int taken=(cpu(2)==cpu(0));/* delay 00267318 */ set(2,cpu(19));if(taken){goto L_00267338;}}
/* 0026731c: b 0x00267340 */ /* delay 00267320 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00267340;
L_00267328:;
/* 00267328: andi v1,v1,0xfff */ set(3,cpu(3)&UINT32_C(0x00000fff));
/* 0026732c: and v1,s3,v1 */ set(3,cpu(19)&cpu(3));
/* 00267330: bne v1,zero,0x0026733c */ {int taken=(cpu(3)!=cpu(0));/* delay 00267334 */ set(2,cpu(19));if(taken){goto L_0026733c;}}
L_00267338:;
/* 00267338: move v0,zero */ set(2,cpu(0));
L_0026733c:;
/* 0026733c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00267340:;
/* 00267340: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00267344: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00267348: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026734c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00267350: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00267354: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00267358: lwc1 f22,0x48(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0026735c: lwc1 f21,0x40(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00267360: lwc1 f20,0x38(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00267364: jr ra */ {uint64_t target=cpu(31);/* delay 00267368 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00267180(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
nocturneEffectHostFpr()[12]=bits(f12);
body_00267180();
return cpu(2);
}
static void body_00267370(void){
nocturneEffectAxisNoteEntry(0x00267370u);
uint64_t incoming=cpu(31);
/* 00267370: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00267374: lui v0,0x3e */ set(2,sx(UINT32_C(0x003e0000)));
/* 00267378: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0026737c: lbu v0,-0x42dd(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0xffffbd23))));
/* 00267380: jr ra */ {uint64_t target=cpu(31);/* delay 00267384 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00267370(uint64_t a0){
set(4,a0);
body_00267370();
return cpu(2);
}
static void body_00267388(void){
nocturneEffectAxisNoteEntry(0x00267388u);
uint64_t incoming=cpu(31);
/* 00267388: jr ra */ {uint64_t target=cpu(31);/* delay 0026738c */ set(2,cpu(0));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00267388(void){

body_00267388();
return cpu(2);
}
static void body_00267390(void){
nocturneEffectAxisNoteEntry(0x00267390u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00267390: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00267394: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267398: move s0,a1 */ set(16,cpu(5));
/* 0026739c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002673a0: move s2,a0 */ set(18,cpu(4));
/* 002673a4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002673a8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002673ac: jal 0x00246ab8 */ set(31,0x002673b4u);/* delay 002673b0 */ set(4,cpu(16));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002673b4: move s1,v0 */ set(17,cpu(2));
/* 002673b8: beq s1,zero,0x002674b4 */ {int taken=(cpu(17)==cpu(0));/* delay 002673bc */ set(4,cpu(16));if(taken){goto L_002674b4;}}
/* 002673c0: jal 0x00267788 */ set(31,0x002673c8u);/* delay 002673c4 */ ps2BattleActionPacket_00267788(cpu(4));
/* 002673c8: li v1,0x400 */ set(3,sx(UINT32_C(0x00000400)));
/* 002673cc: beq v0,v1,0x002673e0 */ {int taken=(cpu(2)==cpu(3));/* delay 002673d0 */ set(4,cpu(18));if(taken){goto L_002673e0;}}
/* 002673d4: b 0x002674b4 */ /* delay 002673d8 */ set(2,cpu(0));goto L_002674b4;
L_002673e0:;
/* 002673e0: jal 0x00267e38 */ set(31,0x002673e8u);/* delay 002673e4 */ body_00267e38();
/* 002673e8: li a0,0x4 */ set(4,sx(UINT32_C(0x00000004)));
/* 002673ec: move v1,v0 */ set(3,cpu(2));
/* 002673f0: move v0,zero */ set(2,cpu(0));
/* 002673f4: beq v1,zero,0x00267404 */ {int taken=(cpu(3)==cpu(0));/* delay 002673f8 */ set(5,sx(UINT32_C(0x00000005)));if(taken){goto L_00267404;}}
/* 002673fc: bne v1,a0,0x002674b8 */ {int taken=(cpu(3)!=cpu(4));/* delay 00267400 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002674b8;}}
L_00267404:;
/* 00267404: jal 0x00243ee0 */ set(31,0x0026740cu);/* delay 00267408 */ set(4,cpu(17));body_00243ee0();
/* 0026740c: lhu v1,0x14(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 00267410: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 00267414: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 00267418: mtc1 v0,f2 */ f[2]=(uint32_t)cpu(2);
/* 0026741c: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 00267420: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00267424: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00267428: lui at,0x40a0 */ set(1,sx(UINT32_C(0x40a00000)));
/* 0026742c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00267430: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00267434: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00267438: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 0026743c: add.S f0,f0,f3 */ f[0]=EE_FPU_ADD_S(f[0],f[3]);
/* 00267440: nop  */ 
/* 00267444: nop  */ 
/* 00267448: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 0026744c: nop  */ 
/* 00267450: nop  */ 
/* 00267454: div.S f2,f2,f0 */ f[2]=EE_FPU_DIV_S(f[2],f[0]);
/* 00267458: beq v0,zero,0x00267478 */ {int taken=(cpu(2)==cpu(0));/* delay 0026745c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004bf8)));if(taken){goto L_00267478;}}
/* 00267460: lui at,0x4220 */ set(1,sx(UINT32_C(0x42200000)));
/* 00267464: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00267468: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 0026746c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00267470: b 0x00267484 */ /* delay 00267474 */ f[1]=EE_FPU_MUL_S(f[2],f[1]);goto L_00267484;
L_00267478:;
/* 00267478: mul.S f1,f2,f3 */ f[1]=EE_FPU_MUL_S(f[2],f[3]);
/* 0026747c: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00267480: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
L_00267484:;
/* 00267484: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 00267488: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0026748c: mfc1 s0,f1 */ set(16,sx(f[1]));
/* 00267490: slti v1,s0,0x14 */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000014));
/* 00267494: li v0,0x14 */ set(2,sx(UINT32_C(0x00000014)));
/* 00267498: movn s0,v0,v1 */ if(cpu(3)!=0){set(16,cpu(2));}
/* 0026749c: jal 0x002d4748 */ set(31,0x002674a4u);/* delay 002674a0 */ set(5,cpu(16));ps2BattleActionPrintf_002D4748(cpu(4));
/* 002674a4: move a0,zero */ set(4,cpu(0));
/* 002674a8: jal 0x002c0c60 */ set(31,0x002674b0u);/* delay 002674ac */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 002674b0: slt v0,v0,s0 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(16));
L_002674b4:;
/* 002674b4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002674b8:;
/* 002674b8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002674bc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002674c0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002674c4: jr ra */ {uint64_t target=cpu(31);/* delay 002674c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00267390(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00267390();
return cpu(2);
}
static void body_002674d0(void){
nocturneEffectAxisNoteEntry(0x002674d0u);
uint64_t incoming=cpu(31);
/* 002674d0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002674d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002674d8: move s0,a1 */ set(16,cpu(5));
/* 002674dc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002674e0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002674e4: jal 0x00246ab8 */ set(31,0x002674ecu);/* delay 002674e8 */ set(17,cpu(6));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002674ec: beql v0,zero,0x0026751c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002674f0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0026751c;}}
/* 002674f4: beq s0,zero,0x00267510 */ {int taken=(cpu(16)==cpu(0));/* delay 002674f8 */ set(4,cpu(2));if(taken){goto L_00267510;}}
/* 002674fc: jal 0x00243bd0 */ set(31,0x00267504u);/* delay 00267500 */ set(5,cpu(17));body_00243bd0();
/* 00267504: b 0x0026751c */ /* delay 00267508 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0026751c;
L_00267510:;
/* 00267510: jal 0x00243c10 */ set(31,0x00267518u);/* delay 00267514 */ set(5,cpu(17));body_00243c10();
/* 00267518: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0026751c:;
/* 0026751c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00267520: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00267524: jr ra */ {uint64_t target=cpu(31);/* delay 00267528 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionFormula_002674D0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_002674d0();
return;
}
static void body_00267530(void){
nocturneEffectAxisNoteEntry(0x00267530u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00267530: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00267534: move v0,zero */ set(2,cpu(0));
/* 00267538: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026753c: move s1,a0 */ set(17,cpu(4));
/* 00267540: swc1 f20,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);
/* 00267544: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267548: clear f20 */ f[20]=0;
/* 0026754c: beq s1,zero,0x00267770 */ {int taken=(cpu(17)==cpu(0));/* delay 00267550 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_00267770;}}
/* 00267554: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00267558: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 0026755c: beq v1,zero,0x00267770 */ {int taken=(cpu(3)==cpu(0));/* delay 00267560 */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_00267770;}}
/* 00267564: lhu v0,0xe(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 00267568: beq a1,v1,0x002676f8 */ {int taken=(cpu(5)==cpu(3));/* delay 0026756c */ set(16,cpu(2)&UINT32_C(0x00000fff));if(taken){goto L_002676f8;}}
/* 00267570: slti v0,a1,0x2 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00267574: beq v0,zero,0x00267590 */ {int taken=(cpu(2)==cpu(0));/* delay 00267578 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_00267590;}}
/* 0026757c: beq a1,zero,0x002675b0 */ {int taken=(cpu(5)==cpu(0));/* delay 00267580 */ set(2,cpu(0));if(taken){goto L_002675b0;}}
/* 00267584: b 0x00267774 */ /* delay 00267588 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00267774;
L_00267590:;
/* 00267590: beq a1,v0,0x00267764 */ {int taken=(cpu(5)==cpu(2));/* delay 00267594 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_00267764;}}
/* 00267598: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 0026759c: beq a1,v0,0x00267700 */ {int taken=(cpu(5)==cpu(2));/* delay 002675a0 */ set(2,cpu(0));if(taken){goto L_00267700;}}
/* 002675a4: b 0x00267774 */ /* delay 002675a8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00267774;
L_002675b0:;
/* 002675b0: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 002675b4: beq s0,v0,0x00267610 */ {int taken=(cpu(16)==cpu(2));/* delay 002675b8 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));if(taken){goto L_00267610;}}
/* 002675bc: beq v0,zero,0x002675e0 */ {int taken=(cpu(2)==cpu(0));/* delay 002675c0 */ set(2,sx(UINT32_C(0x00000010)));if(taken){goto L_002675e0;}}
/* 002675c4: sltiu v0,s0,0x3 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 002675c8: beq v0,zero,0x00267770 */ {int taken=(cpu(2)==cpu(0));/* delay 002675cc */ set(2,cpu(0));if(taken){goto L_00267770;}}
/* 002675d0: beq s0,zero,0x00267774 */ {int taken=(cpu(16)==cpu(0));/* delay 002675d4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00267774;}}
/* 002675d8: b 0x00267774 */ /* delay 002675dc */ set(2,sx(UINT32_C(0x00000001)));goto L_00267774;
L_002675e0:;
/* 002675e0: beq s0,v0,0x00267610 */ {int taken=(cpu(16)==cpu(2));/* delay 002675e4 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000011));if(taken){goto L_00267610;}}
/* 002675e8: beq v0,zero,0x00267608 */ {int taken=(cpu(2)==cpu(0));/* delay 002675ec */ set(2,sx(UINT32_C(0x00000080)));if(taken){goto L_00267608;}}
/* 002675f0: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002675f4: beq s0,v0,0x00267610 */ {int taken=(cpu(16)==cpu(2));/* delay 002675f8 */ set(2,cpu(0));if(taken){goto L_00267610;}}
/* 002675fc: b 0x00267774 */ /* delay 00267600 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00267774;
L_00267608:;
/* 00267608: bne s0,v0,0x00267770 */ {int taken=(cpu(16)!=cpu(2));/* delay 0026760c */ set(2,cpu(0));if(taken){goto L_00267770;}}
L_00267610:;
/* 00267610: move a0,s1 */ set(4,cpu(17));
/* 00267614: jal 0x00243ee0 */ set(31,0x0026761cu);/* delay 00267618 */ set(5,sx(UINT32_C(0x00000005)));body_00243ee0();
/* 0026761c: lhu v1,0x14(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 00267620: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 00267624: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00267628: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0026762c: addiu v1,v1,0x14 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000014)));
/* 00267630: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 00267634: div v1,a0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(4),1,0);
/* 00267638: beql a0,zero,0x00267640 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0026763c */ nocturneCompilerArithmeticTrap(7u);goto L_00267640;}}
L_00267640:;
/* 00267640: mflo v1 */ set(3,nocturneEffectHostLo());
/* 00267644: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00267648: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0026764c: nop  */ 
/* 00267650: nop  */ 
/* 00267654: div.S f0,f1,f0 */ f[0]=EE_FPU_DIV_S(f[1],f[0]);
/* 00267658: beq s0,v0,0x002676b0 */ {int taken=(cpu(16)==cpu(2));/* delay 0026765c */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000009));if(taken){goto L_002676b0;}}
/* 00267660: beq v0,zero,0x00267680 */ {int taken=(cpu(2)==cpu(0));/* delay 00267664 */ set(2,sx(UINT32_C(0x00000010)));if(taken){goto L_00267680;}}
/* 00267668: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 0026766c: beq s0,v0,0x002676a0 */ {int taken=(cpu(16)==cpu(2));/* delay 00267670 */ if(taken){goto L_002676a0;}}
/* 00267674: b 0x002676bc */ /* delay 00267678 */ f[0]=EE_FPU_MUL_S(f[20],f[0]);goto L_002676bc;
L_00267680:;
/* 00267680: beq s0,v0,0x002676b0 */ {int taken=(cpu(16)==cpu(2));/* delay 00267684 */ set(2,sx(UINT32_C(0x00000080)));if(taken){goto L_002676b0;}}
/* 00267688: bnel s0,v0,0x002676bc */ {int taken=(cpu(16)!=cpu(2));if(taken){/* delay 0026768c */ f[0]=EE_FPU_MUL_S(f[20],f[0]);goto L_002676bc;}}
/* 00267690: lui at,0x4220 */ set(1,sx(UINT32_C(0x42200000)));
/* 00267694: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 00267698: b 0x002676bc */ /* delay 0026769c */ f[0]=EE_FPU_MUL_S(f[20],f[0]);goto L_002676bc;
L_002676a0:;
/* 002676a0: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 002676a4: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 002676a8: b 0x002676bc */ /* delay 002676ac */ f[0]=EE_FPU_MUL_S(f[20],f[0]);goto L_002676bc;
L_002676b0:;
/* 002676b0: lui at,0x41f0 */ set(1,sx(UINT32_C(0x41f00000)));
/* 002676b4: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 002676b8: mul.S f0,f20,f0 */ f[0]=EE_FPU_MUL_S(f[20],f[0]);
L_002676bc:;
/* 002676bc: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 002676c0: addiu a0,a0,0x4c10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004c10)));
/* 002676c4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 002676c8: mfc1 s0,f1 */ set(16,sx(f[1]));
/* 002676cc: jal 0x002d4748 */ set(31,0x002676d4u);/* delay 002676d0 */ set(5,cpu(16));ps2BattleActionPrintf_002D4748(cpu(4));
/* 002676d4: move a0,zero */ set(4,cpu(0));
/* 002676d8: jal 0x002c0c60 */ set(31,0x002676e0u);/* delay 002676dc */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 002676e0: slt v0,v0,s0 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(16));
/* 002676e4: beql v0,zero,0x00267770 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002676e8 */ set(2,cpu(0));goto L_00267770;}}
/* 002676ec: b 0x00267770 */ /* delay 002676f0 */ set(2,sx(UINT32_C(0x00000001)));goto L_00267770;
L_002676f8:;
/* 002676f8: b 0x00267764 */ /* delay 002676fc */ set(2,sx(UINT32_C(0x00000010)));goto L_00267764;
L_00267700:;
/* 00267700: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 00267704: beq s0,v0,0x00267770 */ {int taken=(cpu(16)==cpu(2));/* delay 00267708 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00267770;}}
/* 0026770c: sltiu v0,s0,0x9 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000009));
/* 00267710: beq v0,zero,0x00267738 */ {int taken=(cpu(2)==cpu(0));/* delay 00267714 */ set(2,sx(UINT32_C(0x00000080)));if(taken){goto L_00267738;}}
/* 00267718: beq s0,zero,0x00267770 */ {int taken=(cpu(16)==cpu(0));/* delay 0026771c */ set(2,cpu(0));if(taken){goto L_00267770;}}
/* 00267720: sltiu v0,s0,0x3 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00267724: bnel v0,zero,0x00267770 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00267728 */ set(2,sx(UINT32_C(0x00000001)));goto L_00267770;}}
/* 0026772c: b 0x00267764 */ /* delay 00267730 */ set(2,sx(UINT32_C(0x00000004)));goto L_00267764;
L_00267738:;
/* 00267738: beq s0,v0,0x00267770 */ {int taken=(cpu(16)==cpu(2));/* delay 0026773c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00267770;}}
/* 00267740: sltiu v0,s0,0x81 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000081));
/* 00267744: beql v0,zero,0x00267758 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00267748 */ set(2,sx(UINT32_C(0x00000200)));goto L_00267758;}}
/* 0026774c: b 0x00267764 */ /* delay 00267750 */ set(2,sx(UINT32_C(0x00000010)));goto L_00267764;
L_00267758:;
/* 00267758: beq s0,v0,0x00267770 */ {int taken=(cpu(16)==cpu(2));/* delay 0026775c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00267770;}}
/* 00267760: li v0,0x400 */ set(2,sx(UINT32_C(0x00000400)));
L_00267764:;
/* 00267764: beq s0,v0,0x00267770 */ {int taken=(cpu(16)==cpu(2));/* delay 00267768 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00267770;}}
/* 0026776c: move v0,zero */ set(2,cpu(0));
L_00267770:;
/* 00267770: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00267774:;
/* 00267774: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00267778: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026777c: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00267780: jr ra */ {uint64_t target=cpu(31);/* delay 00267784 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00267530(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00267530();
return cpu(2);
}
static void body_00267890(void){
nocturneEffectAxisNoteEntry(0x00267890u);
uint64_t incoming=cpu(31);
/* 00267890: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00267894: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00267898: move s3,a1 */ set(19,cpu(5));
/* 0026789c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002678a0: move s5,a0 */ set(21,cpu(4));
/* 002678a4: move a0,s3 */ set(4,cpu(19));
/* 002678a8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002678ac: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002678b0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002678b4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002678b8: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002678bc: jal 0x00246ab8 */ set(31,0x002678c4u);/* delay 002678c0 */ set(18,cpu(6));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002678c4: move s1,v0 */ set(17,cpu(2));
/* 002678c8: slti v0,s3,0x10 */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002678cc: bne v0,zero,0x00267900 */ {int taken=(cpu(2)!=cpu(0));/* delay 002678d0 */ set(5,cpu(18));if(taken){goto L_00267900;}}
/* 002678d4: move a0,s1 */ set(4,cpu(17));
/* 002678d8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002678dc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002678e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002678e4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002678e8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002678ec: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002678f0: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002678f4: j 0x00243fe8 */ /* delay 002678f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);body_00243fe8();return;
L_00267900:;
/* 00267900: jal 0x00246a40 */ set(31,0x00267908u);/* delay 00267904 */ set(4,cpu(19));ps2BattleActionScaleLookup_00246A40(cpu(4));
/* 00267908: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 0026790c: move a1,v0 */ set(5,cpu(2));
/* 00267910: beq s2,v1,0x00267e10 */ {int taken=(cpu(18)==cpu(3));/* delay 00267914 */ set(2,cpu(0));if(taken){goto L_00267e10;}}
/* 00267918: slti v0,s2,-0x1 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0xffffffff));
/* 0026791c: bne v0,zero,0x00267940 */ {int taken=(cpu(2)!=cpu(0));/* delay 00267920 */ set(20,sx((uint32_t)cpu(18)<<2));if(taken){goto L_00267940;}}
/* 00267924: slti v0,s2,0x10 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00267928: beql v0,zero,0x00267944 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0026792c */ set(4,cpu(19));goto L_00267944;}}
/* 00267930: slti v1,s2,0xc */ set(3,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 00267934: beq v1,zero,0x00267e10 */ {int taken=(cpu(3)==cpu(0));/* delay 00267938 */ set(2,sx(UINT32_C(0x00000064)));if(taken){goto L_00267e10;}}
/* 0026793c: sll s4,s2,0x2 */ set(20,sx((uint32_t)cpu(18)<<2));
L_00267940:;
/* 00267940: move a0,s3 */ set(4,cpu(19));
L_00267944:;
/* 00267944: addu v0,s4,a1 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(5)));
/* 00267948: li a1,0x13 */ set(5,sx(UINT32_C(0x00000013)));
/* 0026794c: jal 0x00267e90 */ set(31,0x00267954u);/* delay 00267950 */ lw(16,ea(2,(int32_t)UINT32_C(0x00000030)));body_00267e90();
/* 00267954: blezl v0,0x00267978 */ {int taken=((int64_t)cpu(2)<=0);if(taken){/* delay 00267958 */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000e))));goto L_00267978;}}
/* 0026795c: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 00267960: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00267964: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00267968: lui s0,0x3a */ set(16,sx(UINT32_C(0x003a0000)));
/* 0026796c: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00267970: lw s0,0x7fe0(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00007fe0)));
/* 00267974: lhu v0,0xe(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000e))));
L_00267978:;
/* 00267978: li v1,0x200 */ set(3,sx(UINT32_C(0x00000200)));
/* 0026797c: andi a0,v0,0xfff */ set(4,cpu(2)&UINT32_C(0x00000fff));
/* 00267980: beq a0,v1,0x002679a8 */ {int taken=(cpu(4)==cpu(3));/* delay 00267984 */ set(2,sx(UINT32_C(0x00000400)));if(taken){goto L_002679a8;}}
/* 00267988: bne a0,v0,0x002679b8 */ {int taken=(cpu(4)!=cpu(2));/* delay 0026798c */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_002679b8;}}
/* 00267990: lui s0,0x3b */ set(16,sx(UINT32_C(0x003b0000)));
/* 00267994: addu s0,s0,s4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(20)));
/* 00267998: lw s0,-0x42a0(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0xffffbd60)));
/* 0026799c: b 0x002679b8 */ /* delay 002679a0 */ goto L_002679b8;
L_002679a8:;
/* 002679a8: lui s0,0x3b */ set(16,sx(UINT32_C(0x003b0000)));
/* 002679ac: addu s0,s0,s4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(20)));
/* 002679b0: lw s0,-0x4260(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0xffffbda0)));
/* 002679b4: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
L_002679b8:;
/* 002679b8: beq s2,v0,0x00267a00 */ {int taken=(cpu(18)==cpu(2));/* delay 002679bc */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_00267a00;}}
/* 002679c0: beq v0,zero,0x002679e0 */ {int taken=(cpu(2)==cpu(0));/* delay 002679c4 */ set(2,sx(UINT32_C(0x00000006)));if(taken){goto L_002679e0;}}
/* 002679c8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002679cc: beq s2,v0,0x002679f8 */ {int taken=(cpu(18)==cpu(2));/* delay 002679d0 */ set(4,cpu(19));if(taken){goto L_002679f8;}}
/* 002679d4: b 0x00267a38 */ /* delay 002679d8 */ goto L_00267a38;
L_002679e0:;
/* 002679e0: beq s2,v0,0x00267a10 */ {int taken=(cpu(18)==cpu(2));/* delay 002679e4 */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_00267a10;}}
/* 002679e8: beq s2,v0,0x00267a20 */ {int taken=(cpu(18)==cpu(2));/* delay 002679ec */ set(4,cpu(19));if(taken){goto L_00267a20;}}
/* 002679f0: b 0x00267a38 */ /* delay 002679f4 */ goto L_00267a38;
L_002679f8:;
/* 002679f8: b 0x00267a24 */ /* delay 002679fc */ set(5,sx(UINT32_C(0x0000000a)));goto L_00267a24;
L_00267a00:;
/* 00267a00: move a0,s3 */ set(4,cpu(19));
/* 00267a04: b 0x00267a24 */ /* delay 00267a08 */ set(5,sx(UINT32_C(0x00000009)));goto L_00267a24;
L_00267a10:;
/* 00267a10: move a0,s3 */ set(4,cpu(19));
/* 00267a14: b 0x00267a24 */ /* delay 00267a18 */ set(5,sx(UINT32_C(0x0000000c)));goto L_00267a24;
L_00267a20:;
/* 00267a20: li a1,0xb */ set(5,sx(UINT32_C(0x0000000b)));
L_00267a24:;
/* 00267a24: jal 0x00267e90 */ set(31,0x00267a2cu);/* delay 00267a28 */ body_00267e90();
/* 00267a2c: blez v0,0x00267a38 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00267a30 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267a38;}}
/* 00267a34: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267a38:;
/* 00267a38: bltz s5,0x00267ab0 */ {int taken=((int64_t)cpu(21)<0);/* delay 00267a3c */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_00267ab0;}}
/* 00267a40: beq s2,v0,0x00267ab0 */ {int taken=(cpu(18)==cpu(2));/* delay 00267a44 */ set(2,sx(UINT32_C(0x0000000b)));if(taken){goto L_00267ab0;}}
/* 00267a48: beq s2,v0,0x00267ab0 */ {int taken=(cpu(18)==cpu(2));/* delay 00267a4c */ set(2,sx((uint32_t)cpu(21)<<4));if(taken){goto L_00267ab0;}}
/* 00267a50: subu v0,v0,s5 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(21)));
/* 00267a54: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00267a58: lui a0,0x3d */ set(4,sx(UINT32_C(0x003d0000)));
/* 00267a5c: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00267a60: lbu a0,0x799a(a0) */ set(4,byte(ea(4,(int32_t)UINT32_C(0x0000799a))));
/* 00267a64: beq a0,zero,0x00267a80 */ {int taken=(cpu(4)==cpu(0));/* delay 00267a68 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00267a80;}}
/* 00267a6c: beq a0,v0,0x00267a90 */ {int taken=(cpu(4)==cpu(2));/* delay 00267a70 */ set(2,cpu(18)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000b));if(taken){goto L_00267a90;}}
/* 00267a74: b 0x00267ab4 */ /* delay 00267a78 */ goto L_00267ab4;
L_00267a80:;
/* 00267a80: move a0,s3 */ set(4,cpu(19));
/* 00267a84: b 0x00267a98 */ /* delay 00267a88 */ set(5,sx(UINT32_C(0x0000000e)));goto L_00267a98;
L_00267a90:;
/* 00267a90: move a0,s3 */ set(4,cpu(19));
/* 00267a94: li a1,0xd */ set(5,sx(UINT32_C(0x0000000d)));
L_00267a98:;
/* 00267a98: jal 0x00267e90 */ set(31,0x00267aa0u);/* delay 00267a9c */ body_00267e90();
/* 00267aa0: blez v0,0x00267ab4 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00267aa4 */ set(2,cpu(18)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000b));if(taken){goto L_00267ab4;}}
/* 00267aa8: lui v0,0x2 */ set(2,sx(UINT32_C(0x00020000)));
/* 00267aac: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267ab0:;
/* 00267ab0: sltiu v0,s2,0xb */ set(2,cpu(18)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000b));
L_00267ab4:;
/* 00267ab4: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267ab8 */ set(18,cpu(16)&UINT32_C(0x0000ffff));if(taken){goto L_00267e04;}}
/* 00267abc: lui v0,0x54 */ set(2,sx(UINT32_C(0x00540000)));
/* 00267ac0: addu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(20)));
/* 00267ac4: lw v0,0x4c30(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00004c30)));
/* 00267ac8: jr v0 */ {uint64_t target=cpu(2);/* delay 00267acc */ switch((uint32_t)target){case 0x00267ad0u:goto L_00267ad0;case 0x00267b38u:goto L_00267b38;case 0x00267ba0u:goto L_00267ba0;case 0x00267c08u:goto L_00267c08;case 0x00267c70u:goto L_00267c70;case 0x00267cd8u:goto L_00267cd8;case 0x00267d10u:goto L_00267d10;case 0x00267d48u:goto L_00267d48;case 0x00267d80u:goto L_00267d80;case 0x00267db8u:goto L_00267db8;case 0x00267e04u:goto L_00267e04;default:abort();}}
L_00267ad0:;
/* 00267ad0: move a0,s1 */ set(4,cpu(17));
/* 00267ad4: jal 0x0026a3d8 */ set(31,0x00267adcu);/* delay 00267ad8 */ set(5,sx(UINT32_C(0x00000143)));body_0026a3d8();
/* 00267adc: beq v0,zero,0x00267ae8 */ {int taken=(cpu(2)==cpu(0));/* delay 00267ae0 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267ae8;}}
/* 00267ae4: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267ae8:;
/* 00267ae8: move a0,s1 */ set(4,cpu(17));
/* 00267aec: jal 0x0026a3d8 */ set(31,0x00267af4u);/* delay 00267af0 */ set(5,sx(UINT32_C(0x0000014d)));body_0026a3d8();
/* 00267af4: beq v0,zero,0x00267b00 */ {int taken=(cpu(2)==cpu(0));/* delay 00267af8 */ set(2,sx(UINT32_C(0x00040000)));if(taken){goto L_00267b00;}}
/* 00267afc: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267b00:;
/* 00267b00: move a0,s1 */ set(4,cpu(17));
/* 00267b04: jal 0x0026a3d8 */ set(31,0x00267b0cu);/* delay 00267b08 */ set(5,sx(UINT32_C(0x00000152)));body_0026a3d8();
/* 00267b0c: beq v0,zero,0x00267b18 */ {int taken=(cpu(2)==cpu(0));/* delay 00267b10 */ set(2,sx(UINT32_C(0x00020000)));if(taken){goto L_00267b18;}}
/* 00267b14: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267b18:;
/* 00267b18: move a0,s1 */ set(4,cpu(17));
/* 00267b1c: jal 0x0026a3d8 */ set(31,0x00267b24u);/* delay 00267b20 */ set(5,sx(UINT32_C(0x00000139)));body_0026a3d8();
/* 00267b24: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267b28 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267b2c: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267b30: b 0x00267dec */ /* delay 00267b34 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc268))));goto L_00267dec;
L_00267b38:;
/* 00267b38: move a0,s1 */ set(4,cpu(17));
/* 00267b3c: jal 0x0026a3d8 */ set(31,0x00267b44u);/* delay 00267b40 */ set(5,sx(UINT32_C(0x00000144)));body_0026a3d8();
/* 00267b44: beq v0,zero,0x00267b50 */ {int taken=(cpu(2)==cpu(0));/* delay 00267b48 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267b50;}}
/* 00267b4c: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267b50:;
/* 00267b50: move a0,s1 */ set(4,cpu(17));
/* 00267b54: jal 0x0026a3d8 */ set(31,0x00267b5cu);/* delay 00267b58 */ set(5,sx(UINT32_C(0x0000014e)));body_0026a3d8();
/* 00267b5c: beq v0,zero,0x00267b68 */ {int taken=(cpu(2)==cpu(0));/* delay 00267b60 */ set(2,sx(UINT32_C(0x00040000)));if(taken){goto L_00267b68;}}
/* 00267b64: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267b68:;
/* 00267b68: move a0,s1 */ set(4,cpu(17));
/* 00267b6c: jal 0x0026a3d8 */ set(31,0x00267b74u);/* delay 00267b70 */ set(5,sx(UINT32_C(0x00000153)));body_0026a3d8();
/* 00267b74: beq v0,zero,0x00267b80 */ {int taken=(cpu(2)==cpu(0));/* delay 00267b78 */ set(2,sx(UINT32_C(0x00020000)));if(taken){goto L_00267b80;}}
/* 00267b7c: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267b80:;
/* 00267b80: move a0,s1 */ set(4,cpu(17));
/* 00267b84: jal 0x0026a3d8 */ set(31,0x00267b8cu);/* delay 00267b88 */ set(5,sx(UINT32_C(0x0000013a)));body_0026a3d8();
/* 00267b8c: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267b90 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267b94: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267b98: b 0x00267dec */ /* delay 00267b9c */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc270))));goto L_00267dec;
L_00267ba0:;
/* 00267ba0: move a0,s1 */ set(4,cpu(17));
/* 00267ba4: jal 0x0026a3d8 */ set(31,0x00267bacu);/* delay 00267ba8 */ set(5,sx(UINT32_C(0x00000145)));body_0026a3d8();
/* 00267bac: beq v0,zero,0x00267bb8 */ {int taken=(cpu(2)==cpu(0));/* delay 00267bb0 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267bb8;}}
/* 00267bb4: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267bb8:;
/* 00267bb8: move a0,s1 */ set(4,cpu(17));
/* 00267bbc: jal 0x0026a3d8 */ set(31,0x00267bc4u);/* delay 00267bc0 */ set(5,sx(UINT32_C(0x0000014f)));body_0026a3d8();
/* 00267bc4: beq v0,zero,0x00267bd0 */ {int taken=(cpu(2)==cpu(0));/* delay 00267bc8 */ set(2,sx(UINT32_C(0x00040000)));if(taken){goto L_00267bd0;}}
/* 00267bcc: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267bd0:;
/* 00267bd0: move a0,s1 */ set(4,cpu(17));
/* 00267bd4: jal 0x0026a3d8 */ set(31,0x00267bdcu);/* delay 00267bd8 */ set(5,sx(UINT32_C(0x00000154)));body_0026a3d8();
/* 00267bdc: beq v0,zero,0x00267be8 */ {int taken=(cpu(2)==cpu(0));/* delay 00267be0 */ set(2,sx(UINT32_C(0x00020000)));if(taken){goto L_00267be8;}}
/* 00267be4: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267be8:;
/* 00267be8: move a0,s1 */ set(4,cpu(17));
/* 00267bec: jal 0x0026a3d8 */ set(31,0x00267bf4u);/* delay 00267bf0 */ set(5,sx(UINT32_C(0x0000013b)));body_0026a3d8();
/* 00267bf4: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267bf8 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267bfc: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267c00: b 0x00267dec */ /* delay 00267c04 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc278))));goto L_00267dec;
L_00267c08:;
/* 00267c08: move a0,s1 */ set(4,cpu(17));
/* 00267c0c: jal 0x0026a3d8 */ set(31,0x00267c14u);/* delay 00267c10 */ set(5,sx(UINT32_C(0x00000146)));body_0026a3d8();
/* 00267c14: beq v0,zero,0x00267c20 */ {int taken=(cpu(2)==cpu(0));/* delay 00267c18 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267c20;}}
/* 00267c1c: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267c20:;
/* 00267c20: move a0,s1 */ set(4,cpu(17));
/* 00267c24: jal 0x0026a3d8 */ set(31,0x00267c2cu);/* delay 00267c28 */ set(5,sx(UINT32_C(0x00000150)));body_0026a3d8();
/* 00267c2c: beq v0,zero,0x00267c38 */ {int taken=(cpu(2)==cpu(0));/* delay 00267c30 */ set(2,sx(UINT32_C(0x00040000)));if(taken){goto L_00267c38;}}
/* 00267c34: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267c38:;
/* 00267c38: move a0,s1 */ set(4,cpu(17));
/* 00267c3c: jal 0x0026a3d8 */ set(31,0x00267c44u);/* delay 00267c40 */ set(5,sx(UINT32_C(0x00000155)));body_0026a3d8();
/* 00267c44: beq v0,zero,0x00267c50 */ {int taken=(cpu(2)==cpu(0));/* delay 00267c48 */ set(2,sx(UINT32_C(0x00020000)));if(taken){goto L_00267c50;}}
/* 00267c4c: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267c50:;
/* 00267c50: move a0,s1 */ set(4,cpu(17));
/* 00267c54: jal 0x0026a3d8 */ set(31,0x00267c5cu);/* delay 00267c58 */ set(5,sx(UINT32_C(0x0000013c)));body_0026a3d8();
/* 00267c5c: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267c60 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267c64: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267c68: b 0x00267dec */ /* delay 00267c6c */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc280))));goto L_00267dec;
L_00267c70:;
/* 00267c70: move a0,s1 */ set(4,cpu(17));
/* 00267c74: jal 0x0026a3d8 */ set(31,0x00267c7cu);/* delay 00267c78 */ set(5,sx(UINT32_C(0x00000147)));body_0026a3d8();
/* 00267c7c: beq v0,zero,0x00267c88 */ {int taken=(cpu(2)==cpu(0));/* delay 00267c80 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267c88;}}
/* 00267c84: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267c88:;
/* 00267c88: move a0,s1 */ set(4,cpu(17));
/* 00267c8c: jal 0x0026a3d8 */ set(31,0x00267c94u);/* delay 00267c90 */ set(5,sx(UINT32_C(0x00000151)));body_0026a3d8();
/* 00267c94: beq v0,zero,0x00267ca0 */ {int taken=(cpu(2)==cpu(0));/* delay 00267c98 */ set(2,sx(UINT32_C(0x00040000)));if(taken){goto L_00267ca0;}}
/* 00267c9c: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267ca0:;
/* 00267ca0: move a0,s1 */ set(4,cpu(17));
/* 00267ca4: jal 0x0026a3d8 */ set(31,0x00267cacu);/* delay 00267ca8 */ set(5,sx(UINT32_C(0x00000156)));body_0026a3d8();
/* 00267cac: beq v0,zero,0x00267cb8 */ {int taken=(cpu(2)==cpu(0));/* delay 00267cb0 */ set(2,sx(UINT32_C(0x00020000)));if(taken){goto L_00267cb8;}}
/* 00267cb4: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267cb8:;
/* 00267cb8: move a0,s1 */ set(4,cpu(17));
/* 00267cbc: jal 0x0026a3d8 */ set(31,0x00267cc4u);/* delay 00267cc0 */ set(5,sx(UINT32_C(0x0000013d)));body_0026a3d8();
/* 00267cc4: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267cc8 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267ccc: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267cd0: b 0x00267dec */ /* delay 00267cd4 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc288))));goto L_00267dec;
L_00267cd8:;
/* 00267cd8: move a0,s1 */ set(4,cpu(17));
/* 00267cdc: jal 0x0026a3d8 */ set(31,0x00267ce4u);/* delay 00267ce0 */ set(5,sx(UINT32_C(0x00000148)));body_0026a3d8();
/* 00267ce4: beq v0,zero,0x00267cf0 */ {int taken=(cpu(2)==cpu(0));/* delay 00267ce8 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267cf0;}}
/* 00267cec: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267cf0:;
/* 00267cf0: move a0,s1 */ set(4,cpu(17));
/* 00267cf4: jal 0x0026a3d8 */ set(31,0x00267cfcu);/* delay 00267cf8 */ set(5,sx(UINT32_C(0x0000013e)));body_0026a3d8();
/* 00267cfc: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267d00 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267d04: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267d08: b 0x00267dec */ /* delay 00267d0c */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc290))));goto L_00267dec;
L_00267d10:;
/* 00267d10: move a0,s1 */ set(4,cpu(17));
/* 00267d14: jal 0x0026a3d8 */ set(31,0x00267d1cu);/* delay 00267d18 */ set(5,sx(UINT32_C(0x00000149)));body_0026a3d8();
/* 00267d1c: beq v0,zero,0x00267d28 */ {int taken=(cpu(2)==cpu(0));/* delay 00267d20 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267d28;}}
/* 00267d24: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267d28:;
/* 00267d28: move a0,s1 */ set(4,cpu(17));
/* 00267d2c: jal 0x0026a3d8 */ set(31,0x00267d34u);/* delay 00267d30 */ set(5,sx(UINT32_C(0x0000013f)));body_0026a3d8();
/* 00267d34: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267d38 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267d3c: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267d40: b 0x00267dec */ /* delay 00267d44 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc298))));goto L_00267dec;
L_00267d48:;
/* 00267d48: move a0,s1 */ set(4,cpu(17));
/* 00267d4c: jal 0x0026a3d8 */ set(31,0x00267d54u);/* delay 00267d50 */ set(5,sx(UINT32_C(0x0000014a)));body_0026a3d8();
/* 00267d54: beq v0,zero,0x00267d60 */ {int taken=(cpu(2)==cpu(0));/* delay 00267d58 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267d60;}}
/* 00267d5c: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267d60:;
/* 00267d60: move a0,s1 */ set(4,cpu(17));
/* 00267d64: jal 0x0026a3d8 */ set(31,0x00267d6cu);/* delay 00267d68 */ set(5,sx(UINT32_C(0x00000140)));body_0026a3d8();
/* 00267d6c: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267d70 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267d74: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267d78: b 0x00267dec */ /* delay 00267d7c */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc2a0))));goto L_00267dec;
L_00267d80:;
/* 00267d80: move a0,s1 */ set(4,cpu(17));
/* 00267d84: jal 0x0026a3d8 */ set(31,0x00267d8cu);/* delay 00267d88 */ set(5,sx(UINT32_C(0x0000014b)));body_0026a3d8();
/* 00267d8c: beq v0,zero,0x00267d98 */ {int taken=(cpu(2)==cpu(0));/* delay 00267d90 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267d98;}}
/* 00267d94: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267d98:;
/* 00267d98: move a0,s1 */ set(4,cpu(17));
/* 00267d9c: jal 0x0026a3d8 */ set(31,0x00267da4u);/* delay 00267da0 */ set(5,sx(UINT32_C(0x00000141)));body_0026a3d8();
/* 00267da4: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267da8 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267dac: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267db0: b 0x00267dec */ /* delay 00267db4 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc2a8))));goto L_00267dec;
L_00267db8:;
/* 00267db8: move a0,s1 */ set(4,cpu(17));
/* 00267dbc: jal 0x0026a3d8 */ set(31,0x00267dc4u);/* delay 00267dc0 */ set(5,sx(UINT32_C(0x0000014c)));body_0026a3d8();
/* 00267dc4: beq v0,zero,0x00267dd0 */ {int taken=(cpu(2)==cpu(0));/* delay 00267dc8 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_00267dd0;}}
/* 00267dcc: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
L_00267dd0:;
/* 00267dd0: move a0,s1 */ set(4,cpu(17));
/* 00267dd4: jal 0x0026a3d8 */ set(31,0x00267ddcu);/* delay 00267dd8 */ set(5,sx(UINT32_C(0x00000142)));body_0026a3d8();
/* 00267ddc: beq v0,zero,0x00267e04 */ {int taken=(cpu(2)==cpu(0));/* delay 00267de0 */ set(4,sx(UINT32_C(0x003e0000)));if(taken){goto L_00267e04;}}
/* 00267de4: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00267de8: lh v0,-0x3d50(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0xffffc2b0))));
L_00267dec:;
/* 00267dec: beql v1,zero,0x00267df4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00267df0 */ nocturneCompilerArithmeticTrap(7u);goto L_00267df4;}}
L_00267df4:;
/* 00267df4: mult v0,s2,v0 */ nativeMultiply(2,(uint32_t)cpu(18),(uint32_t)cpu(2),1,0);
/* 00267df8: div1 v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,1);
/* 00267dfc: mflo1 v0 */ set(2,secondaryLo);
/* 00267e00: move s2,v0 */ set(18,cpu(2));
L_00267e04:;
/* 00267e04: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 00267e08: and v0,s0,v0 */ set(2,cpu(16)&cpu(2));
/* 00267e0c: or v0,v0,s2 */ set(2,cpu(2)|cpu(18));
L_00267e10:;
/* 00267e10: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267e14: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00267e18: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00267e1c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00267e20: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00267e24: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00267e28: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00267e2c: jr ra */ {uint64_t target=cpu(31);/* delay 00267e30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00267890(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00267890();
return cpu(2);
}
static void body_00267e38(void){
nocturneEffectAxisNoteEntry(0x00267e38u);
uint64_t incoming=cpu(31);
/* 00267e38: sll a0,a0,0x3 */ set(4,sx((uint32_t)cpu(4)<<3));
/* 00267e3c: lui v0,0x3d */ set(2,sx(UINT32_C(0x003d0000)));
/* 00267e40: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00267e44: lb v0,0x6998(v0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00006998))));
/* 00267e48: jr ra */ {uint64_t target=cpu(31);/* delay 00267e4c */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00267E38(uint64_t a0){
set(4,a0);
body_00267e38();
return cpu(2);
}
static void body_00267e90(void){
nocturneEffectAxisNoteEntry(0x00267e90u);
uint64_t incoming=cpu(31);
/* 00267e90: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00267e94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267e98: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00267e9c: jal 0x00246a40 */ set(31,0x00267ea4u);/* delay 00267ea0 */ set(16,cpu(5));ps2BattleActionScaleLookup_00246A40(cpu(4));
/* 00267ea4: move v1,v0 */ set(3,cpu(2));
/* 00267ea8: beq v1,zero,0x00267eb8 */ {int taken=(cpu(3)==cpu(0));/* delay 00267eac */ set(16,sx((uint32_t)cpu(16)<<1));if(taken){goto L_00267eb8;}}
/* 00267eb0: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00267eb4: lh v0,0x8(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000008))));
L_00267eb8:;
/* 00267eb8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267ebc: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00267ec0: jr ra */ {uint64_t target=cpu(31);/* delay 00267ec4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00267E90(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00267e90();
return cpu(2);
}
static void body_002684b0(void){
nocturneEffectAxisNoteEntry(0x002684b0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002684b0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002684b4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002684b8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002684bc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002684c0: move s2,a1 */ set(18,cpu(5));
/* 002684c4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002684c8: swc1 f20,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 002684cc: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002684d0: jal 0x00246ab8 */ set(31,0x002684d8u);/* delay 002684d4 */ set(19,cpu(4));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 002684d8: move s0,v0 */ set(16,cpu(2));
/* 002684dc: move a0,s3 */ set(4,cpu(19));
/* 002684e0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002684e4: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 002684e8: jal 0x00267e90 */ set(31,0x002684f0u);/* delay 002684ec */ set(5,cpu(18));body_00267e90();
/* 002684f0: lhu v1,0x4(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000004))));
/* 002684f4: move s1,v0 */ set(17,cpu(2));
/* 002684f8: li v0,0x125 */ set(2,sx(UINT32_C(0x00000125)));
/* 002684fc: bnel v1,v0,0x00268524 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 00268500 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000008));goto L_00268524;}}
/* 00268504: jal 0x001e9998 */ set(31,0x0026850cu);/* delay 00268508 */ body_001e9998();
/* 0026850c: addiu v0,v0,-0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffc)));
/* 00268510: srl v1,v0,0x1f */ set(3,sx((uint32_t)cpu(2)>>31));
/* 00268514: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00268518: sra v0,v0,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 0026851c: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 00268520: slti v0,s2,0x8 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000008));
L_00268524:;
/* 00268524: beq v0,zero,0x00268570 */ {int taken=(cpu(2)==cpu(0));/* delay 00268528 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000006));if(taken){goto L_00268570;}}
/* 0026852c: bne v0,zero,0x00268570 */ {int taken=(cpu(2)!=cpu(0));/* delay 00268530 */ if(taken){goto L_00268570;}}
/* 00268534: bgez s1,0x00268560 */ {int taken=((int64_t)cpu(17)>=0);/* delay 00268538 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(17)));if(taken){goto L_00268560;}}
/* 0026853c: lui at,0x4100 */ set(1,sx(UINT32_C(0x41000000)));
/* 00268540: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00268544: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00268548: lui at,0x3e00 */ set(1,sx(UINT32_C(0x3e000000)));
/* 0026854c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00268550: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00268554: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00268558: b 0x002685c8 */ /* delay 0026855c */ f[0]=EE_FPU_ADD_S(f[0],f[2]);goto L_002685c8;
L_00268560:;
/* 00268560: blezl s1,0x002685d0 */ {int taken=((int64_t)cpu(17)<=0);if(taken){/* delay 00268564 */ set(2,sx(UINT32_C(0x00000004)));goto L_002685d0;}}
/* 00268568: b 0x002685ac */ /* delay 0026856c */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(17)));goto L_002685ac;
L_00268570:;
/* 00268570: bgez s1,0x002685a0 */ {int taken=((int64_t)cpu(17)>=0);/* delay 00268574 */ if(taken){goto L_002685a0;}}
/* 00268578: mtc1 s1,f0 */ f[0]=(uint32_t)cpu(17);
/* 0026857c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00268580: lui at,0x4100 */ set(1,sx(UINT32_C(0x41000000)));
/* 00268584: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00268588: lui at,0x3e00 */ set(1,sx(UINT32_C(0x3e000000)));
/* 0026858c: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00268590: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 00268594: b 0x002685cc */ /* delay 00268598 */ f[20]=EE_FPU_MUL_S(f[0],f[2]);goto L_002685cc;
L_002685a0:;
/* 002685a0: blez s1,0x002685d0 */ {int taken=((int64_t)cpu(17)<=0);/* delay 002685a4 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_002685d0;}}
/* 002685a8: sll v0,s1,0x1 */ set(2,sx((uint32_t)cpu(17)<<1));
L_002685ac:;
/* 002685ac: lui at,0x4100 */ set(1,sx(UINT32_C(0x41000000)));
/* 002685b0: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 002685b4: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 002685b8: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002685bc: lui at,0x3e00 */ set(1,sx(UINT32_C(0x3e000000)));
/* 002685c0: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 002685c4: add.S f0,f0,f2 */ f[0]=EE_FPU_ADD_S(f[0],f[2]);
L_002685c8:;
/* 002685c8: mul.S f20,f0,f1 */ f[20]=EE_FPU_MUL_S(f[0],f[1]);
L_002685cc:;
/* 002685cc: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
L_002685d0:;
/* 002685d0: bne s2,v0,0x002685fc */ {int taken=(cpu(18)!=cpu(2));/* delay 002685d4 */ f[0]=f[20];if(taken){goto L_002685fc;}}
/* 002685d8: move a0,s3 */ set(4,cpu(19));
/* 002685dc: jal 0x00267e90 */ set(31,0x002685e4u);/* delay 002685e0 */ set(5,sx(UINT32_C(0x0000000f)));body_00267e90();
/* 002685e4: blez v0,0x002685fc */ {int taken=((int64_t)cpu(2)<=0);/* delay 002685e8 */ f[0]=f[20];if(taken){goto L_002685fc;}}
/* 002685ec: lui at,0x4020 */ set(1,sx(UINT32_C(0x40200000)));
/* 002685f0: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002685f4: mul.S f20,f20,f0 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);
/* 002685f8: mov.S f0,f20 */ f[0]=f[20];
L_002685fc:;
/* 002685fc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00268600: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00268604: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00268608: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026860c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00268610: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00268614: jr ra */ {uint64_t target=cpu(31);/* delay 00268618 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
float ps2BattleActionFormula_002684B0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002684b0();
return real(nocturneEffectHostFpr()[0]);
}
static void body_00268620(void){
nocturneEffectAxisNoteEntry(0x00268620u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00268620: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 00268624: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00268628: move s0,a1 */ set(16,cpu(5));
/* 0026862c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00268630: move s1,a2 */ set(17,cpu(6));
/* 00268634: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00268638: move s4,a0 */ set(20,cpu(4));
/* 0026863c: move a0,s0 */ set(4,cpu(16));
/* 00268640: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00268644: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00268648: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026864c: move s5,a3 */ set(21,cpu(7));
/* 00268650: swc1 f22,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),f[22]);
/* 00268654: swc1 f21,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),f[21]);
/* 00268658: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0026865c: jal 0x00246ab8 */ set(31,0x00268664u);/* delay 00268660 */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[20]);ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00268664: move a0,s1 */ set(4,cpu(17));
/* 00268668: jal 0x00246ab8 */ set(31,0x00268670u);/* delay 0026866c */ set(19,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00268670: move a0,s0 */ set(4,cpu(16));
/* 00268674: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 00268678: jal 0x002684b0 */ set(31,0x00268680u);/* delay 0026867c */ set(18,cpu(2));body_002684b0();
/* 00268680: move a0,s1 */ set(4,cpu(17));
/* 00268684: li a1,0x7 */ set(5,sx(UINT32_C(0x00000007)));
/* 00268688: jal 0x002684b0 */ set(31,0x00268690u);/* delay 0026868c */ f[22]=f[0];body_002684b0();
/* 00268690: move a0,s3 */ set(4,cpu(19));
/* 00268694: jal 0x00242b68 */ set(31,0x0026869cu);/* delay 00268698 */ f[21]=f[0];body_00242b68();
/* 0026869c: jal 0x00242d18 */ set(31,0x002686a4u);/* delay 002686a0 */ set(4,cpu(18));body_00242d18();
/* 002686a4: lw v1,0x0(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 002686a8: andi v1,v1,0x20 */ set(3,cpu(3)&UINT32_C(0x00000020));
/* 002686ac: beq v1,zero,0x002687a8 */ {int taken=(cpu(3)==cpu(0));/* delay 002686b0 */ if(taken){goto L_002687a8;}}
/* 002686b4: bne s4,zero,0x00268718 */ {int taken=(cpu(20)!=cpu(0));/* delay 002686b8 */ set(4,cpu(19));if(taken){goto L_00268718;}}
/* 002686bc: jal 0x00243ee0 */ set(31,0x002686c4u);/* delay 002686c0 */ set(5,cpu(0));body_00243ee0();
/* 002686c4: lhu a0,0x14(s3) */ set(4,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 002686c8: li v1,0x30 */ set(3,sx(UINT32_C(0x00000030)));
/* 002686cc: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 002686d0: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 002686d4: addiu v0,a0,0xa */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x0000000a)));
/* 002686d8: mtc1 a0,f0 */ f[0]=(uint32_t)cpu(4);
/* 002686dc: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002686e0: div v1,v0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(2),1,0);
/* 002686e4: lwc1 f2,-0x5c1c(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffa3e4)));
/* 002686e8: lwc1 f3,-0x5c18(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa3e8)));
/* 002686ec: beql v0,zero,0x002686f4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002686f0 */ nocturneCompilerArithmeticTrap(7u);goto L_002686f4;}}
L_002686f4:;
/* 002686f4: add.S f1,f1,f1 */ f[1]=EE_FPU_ADD_S(f[1],f[1]);
/* 002686f8: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 002686fc: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 00268700: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 00268704: mflo v1 */ set(3,nocturneEffectHostLo());
/* 00268708: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 0026870c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00268710: b 0x00268784 */ /* delay 00268714 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);goto L_00268784;
L_00268718:;
/* 00268718: jal 0x00243ee0 */ set(31,0x00268720u);/* delay 0026871c */ set(5,cpu(0));body_00243ee0();
/* 00268720: lhu v1,0x14(s3) */ set(3,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 00268724: li a0,0x32 */ set(4,sx(UINT32_C(0x00000032)));
/* 00268728: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 0026872c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00268730: addiu v0,v1,0xa */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x0000000a)));
/* 00268734: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00268738: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0026873c: div a0,v0 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(2),1,0);
/* 00268740: mtc1 s5,f3 */ f[3]=(uint32_t)cpu(21);
/* 00268744: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 00268748: lwc1 f4,-0x5c14(gp) */ f[4]=word(ea(28,(int32_t)UINT32_C(0xffffa3ec)));
/* 0026874c: beql v0,zero,0x00268754 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00268750 */ nocturneCompilerArithmeticTrap(7u);goto L_00268754;}}
L_00268754:;
/* 00268754: add.S f1,f1,f1 */ f[1]=EE_FPU_ADD_S(f[1],f[1]);
/* 00268758: lwc1 f2,-0x5c10(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffa3f0)));
/* 0026875c: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 00268760: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 00268764: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 00268768: nop  */ 
/* 0026876c: nop  */ 
/* 00268770: div.S f0,f0,f4 */ f[0]=EE_FPU_DIV_S(f[0],f[4]);
/* 00268774: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 00268778: mflo a0 */ set(4,nocturneEffectHostLo());
/* 0026877c: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
/* 00268780: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
L_00268784:;
/* 00268784: sub.S f20,f0,f1 */ f[20]=EE_FPU_SUB_S(f[0],f[1]);
/* 00268788: jal 0x001e0f50 */ set(31,0x00268790u);/* delay 0026878c */ set(4,sx(UINT32_C(0x00000af2)));body_001e0f50();
/* 00268790: bne v0,zero,0x00268840 */ {int taken=(cpu(2)!=cpu(0));/* delay 00268794 */ f[12]=f[22];if(taken){goto L_00268840;}}
/* 00268798: lwc1 f0,-0x5c0c(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa3f4)));
/* 0026879c: b 0x00268840 */ /* delay 002687a0 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);goto L_00268840;
L_002687a8:;
/* 002687a8: bne s4,zero,0x002687f0 */ {int taken=(cpu(20)!=cpu(0));/* delay 002687ac */ set(4,cpu(19));if(taken){goto L_002687f0;}}
/* 002687b0: jal 0x00243ee0 */ set(31,0x002687b8u);/* delay 002687b4 */ set(5,cpu(0));body_00243ee0();
/* 002687b8: lhu v1,0x14(s3) */ set(3,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 002687bc: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 002687c0: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 002687c4: lwc1 f3,-0x5c08(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa3f8)));
/* 002687c8: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 002687cc: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002687d0: lwc1 f2,-0x5c04(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffa3fc)));
/* 002687d4: add.S f1,f1,f1 */ f[1]=EE_FPU_ADD_S(f[1],f[1]);
/* 002687d8: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 002687dc: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 002687e0: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 002687e4: b 0x0026883c */ /* delay 002687e8 */ f[20]=EE_FPU_MUL_S(f[0],f[2]);goto L_0026883c;
L_002687f0:;
/* 002687f0: jal 0x00243ee0 */ set(31,0x002687f8u);/* delay 002687f4 */ set(5,cpu(0));body_00243ee0();
/* 002687f8: lhu v1,0x14(s3) */ set(3,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 002687fc: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00268800: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00268804: lwc1 f4,-0x5c00(gp) */ f[4]=word(ea(28,(int32_t)UINT32_C(0xffffa400)));
/* 00268808: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 0026880c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00268810: lwc1 f3,-0x5bfc(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa404)));
/* 00268814: mtc1 s5,f2 */ f[2]=(uint32_t)cpu(21);
/* 00268818: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0026881c: add.S f1,f1,f1 */ f[1]=EE_FPU_ADD_S(f[1],f[1]);
/* 00268820: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 00268824: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 00268828: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0026882c: nop  */ 
/* 00268830: nop  */ 
/* 00268834: div.S f0,f0,f4 */ f[0]=EE_FPU_DIV_S(f[0],f[4]);
/* 00268838: mul.S f20,f0,f3 */ f[20]=EE_FPU_MUL_S(f[0],f[3]);
L_0026883c:;
/* 0026883c: mov.S f12,f22 */ f[12]=f[22];
L_00268840:;
/* 00268840: jal 0x002d1550 */ set(31,0x00268848u);/* delay 00268844 */ set(16,sx(UINT32_C(0x00540000)));ps2EffectSoftDoubleFromFloat_002D1550(real(f[12]));
/* 00268848: addiu s0,s0,0x4d00 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00004d00)));
/* 0026884c: move a0,s0 */ set(4,cpu(16));
/* 00268850: lui s0,0x54 */ set(16,sx(UINT32_C(0x00540000)));
/* 00268854: move a1,v0 */ set(5,cpu(2));
/* 00268858: jal 0x002d4748 */ set(31,0x00268860u);/* delay 0026885c */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00004d10)));ps2BattleActionPrintf_002D4748(cpu(4));
/* 00268860: jal 0x002d1550 */ set(31,0x00268868u);/* delay 00268864 */ f[12]=f[21];ps2EffectSoftDoubleFromFloat_002D1550(real(f[12]));
/* 00268868: move a1,v0 */ set(5,cpu(2));
/* 0026886c: jal 0x002d4748 */ set(31,0x00268874u);/* delay 00268870 */ set(4,cpu(16));ps2BattleActionPrintf_002D4748(cpu(4));
/* 00268874: mul.S f0,f20,f22 */ f[0]=EE_FPU_MUL_S(f[20],f[22]);
/* 00268878: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026887c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00268880: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00268884: mul.S f20,f0,f21 */ f[20]=EE_FPU_MUL_S(f[0],f[21]);
/* 00268888: lwc1 f21,0x40(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0026888c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00268890: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00268894: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00268898: cvt.w.S f0,f20 */ f[0]=EE_FPU_CVT_W_S(f[20]);
/* 0026889c: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 002688a0: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002688a4: lwc1 f22,0x48(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002688a8: lwc1 f20,0x38(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002688ac: jr ra */ {uint64_t target=cpu(31);/* delay 002688b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00268620(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_00268620();
return cpu(2);
}
static void body_002688b8(void){
nocturneEffectAxisNoteEntry(0x002688b8u);
uint64_t incoming=cpu(31);
/* 002688b8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002688bc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002688c0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002688c4: j 0x00268620 */ /* delay 002688c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00268620();return;
}
uint64_t ps2BattleActionFormula_002688B8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_002688b8();
return cpu(2);
}
static void body_002688d0(void){
nocturneEffectAxisNoteEntry(0x002688d0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 002688d0: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 002688d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002688d8: move s0,a1 */ set(16,cpu(5));
/* 002688dc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002688e0: move s1,a2 */ set(17,cpu(6));
/* 002688e4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002688e8: move s2,a0 */ set(18,cpu(4));
/* 002688ec: move a0,s0 */ set(4,cpu(16));
/* 002688f0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002688f4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002688f8: move s4,a3 */ set(20,cpu(7));
/* 002688fc: swc1 f25,0x60(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),f[25]);
/* 00268900: swc1 f24,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),f[24]);
/* 00268904: swc1 f23,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),f[23]);
/* 00268908: swc1 f20,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[20]);
/* 0026890c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00268910: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00268914: swc1 f22,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),f[22]);
/* 00268918: jal 0x00246ab8 */ set(31,0x00268920u);/* delay 0026891c */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),f[21]);ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00268920: move a0,s1 */ set(4,cpu(17));
/* 00268924: jal 0x00246ab8 */ set(31,0x0026892cu);/* delay 00268928 */ set(19,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 0026892c: move a0,s0 */ set(4,cpu(16));
/* 00268930: lui at,0x41a8 */ set(1,sx(UINT32_C(0x41a80000)));
/* 00268934: mtc1 at,f23 */ f[23]=(uint32_t)cpu(1);
/* 00268938: jal 0x002684b0 */ set(31,0x00268940u);/* delay 0026893c */ set(5,sx(UINT32_C(0x00000005)));body_002684b0();
/* 00268940: move a0,s1 */ set(4,cpu(17));
/* 00268944: li a1,0x7 */ set(5,sx(UINT32_C(0x00000007)));
/* 00268948: jal 0x002684b0 */ set(31,0x00268950u);/* delay 0026894c */ f[25]=f[0];body_002684b0();
/* 00268950: sll v0,s2,0x4 */ set(2,sx((uint32_t)cpu(18)<<4));
/* 00268954: lhu a1,0x14(s3) */ set(5,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 00268958: mov.S f24,f0 */ f[24]=f[0];
/* 0026895c: subu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 00268960: mult v1,a1,s4 */ nativeMultiply(3,(uint32_t)cpu(5),(uint32_t)cpu(20),1,0);
/* 00268964: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00268968: lui s2,0x3d */ set(18,sx(UINT32_C(0x003d0000)));
/* 0026896c: addiu s2,s2,0x79c8 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x000079c8)));
/* 00268970: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 00268974: lh a0,0x8(s2) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(18,(int32_t)UINT32_C(0x00000008))));
/* 00268978: lh v0,0xa(s2) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(18,(int32_t)UINT32_C(0x0000000a))));
/* 0026897c: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 00268980: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
/* 00268984: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00268988: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 0026898c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00268990: mtc1 v0,f2 */ f[2]=(uint32_t)cpu(2);
/* 00268994: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 00268998: nop  */ 
/* 0026899c: nop  */ 
/* 002689a0: div.S f0,f0,f23 */ f[0]=EE_FPU_DIV_S(f[0],f[23]);
/* 002689a4: add.S f20,f1,f0 */ f[20]=EE_FPU_ADD_S(f[1],f[0]);
/* 002689a8: c.lt.S f2,f20 */ condition=EE_FPU_COMPARE_S(f[2],f[20],1)!=0;
/* 002689ac: bc1tl 0x002689b4 */ {int taken=(condition!=0);if(taken){/* delay 002689b0 */ f[20]=f[2];goto L_002689b4;}}
L_002689b4:;
/* 002689b4: move s0,a1 */ set(16,cpu(5));
/* 002689b8: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 002689bc: li v1,0xa0 */ set(3,sx(UINT32_C(0x000000a0)));
/* 002689c0: slti v0,s0,0xa1 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x000000a1));
/* 002689c4: movz s0,v1,v0 */ if(cpu(2)==0){set(16,cpu(3));}
/* 002689c8: jal 0x00243ee0 */ set(31,0x002689d0u);/* delay 002689cc */ set(4,cpu(19));body_00243ee0();
/* 002689d0: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 002689d4: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002689d8: lui at,0x40a0 */ set(1,sx(UINT32_C(0x40a00000)));
/* 002689dc: mtc1 at,f22 */ f[22]=(uint32_t)cpu(1);
/* 002689e0: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 002689e4: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 002689e8: lui at,0x4080 */ set(1,sx(UINT32_C(0x40800000)));
/* 002689ec: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 002689f0: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 002689f4: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 002689f8: nop  */ 
/* 002689fc: nop  */ 
/* 00268a00: div.S f0,f0,f22 */ f[0]=EE_FPU_DIV_S(f[0],f[22]);
/* 00268a04: lui at,0x4020 */ set(1,sx(UINT32_C(0x40200000)));
/* 00268a08: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00268a0c: nop  */ 
/* 00268a10: nop  */ 
/* 00268a14: div.S f12,f20,f12 */ f[12]=EE_FPU_DIV_S(f[20],f[12]);
/* 00268a18: add.S f0,f0,f3 */ f[0]=EE_FPU_ADD_S(f[0],f[3]);
/* 00268a1c: sub.S f1,f1,f0 */ f[1]=EE_FPU_SUB_S(f[1],f[0]);
/* 00268a20: mul.S f0,f1,f2 */ f[0]=EE_FPU_MUL_S(f[1],f[2]);
/* 00268a24: mul.S f12,f12,f0 */ f[12]=EE_FPU_MUL_S(f[12],f[0]);
/* 00268a28: jal 0x002d1550 */ set(31,0x00268a30u);/* delay 00268a2c */ f[12]=EE_FPU_ADD_S(f[20],f[12]);ps2EffectSoftDoubleFromFloat_002D1550(real(f[12]));
/* 00268a30: lui at,0x54 */ set(1,sx(UINT32_C(0x00540000)));
/* 00268a34: ld a1,0x4d20(at) */ restore(5,ea(1,(int32_t)UINT32_C(0x00004d20)));
/* 00268a38: move a0,v0 */ set(4,cpu(2));
/* 00268a3c: jal 0x002d18b0 */ set(31,0x00268a44u);/* delay 00268a40 */ body_002d18b0();
/* 00268a44: move a0,v0 */ set(4,cpu(2));
/* 00268a48: jal 0x002d1d10 */ set(31,0x00268a50u);/* delay 00268a4c */ ps2EffectSoftDoubleToFloat_002D1D10(cpu(4));
/* 00268a50: lw v1,0x0(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 00268a54: andi v0,v1,0x20 */ set(2,cpu(3)&UINT32_C(0x00000020));
/* 00268a58: bne v0,zero,0x00268b90 */ {int taken=(cpu(2)!=cpu(0));/* delay 00268a5c */ f[21]=f[0];if(taken){goto L_00268b90;}}
/* 00268a60: lhu v0,0x14(s3) */ set(2,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 00268a64: sltiu v0,v0,0x65 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000065));
/* 00268a68: bne v0,zero,0x00268b88 */ {int taken=(cpu(2)!=cpu(0));/* delay 00268a6c */ set(2,cpu(3)&UINT32_C(0x00000020));if(taken){goto L_00268b88;}}
/* 00268a70: lhu a1,0x14(s3) */ set(5,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 00268a74: li s1,0x64 */ set(17,sx(UINT32_C(0x00000064)));
/* 00268a78: slt v0,s1,a1 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(5));
/* 00268a7c: beq v0,zero,0x00268b88 */ {int taken=(cpu(2)==cpu(0));/* delay 00268a80 */ set(2,cpu(3)&UINT32_C(0x00000020));if(taken){goto L_00268b88;}}
/* 00268a84: li s5,0xa0 */ set(21,sx(UINT32_C(0x000000a0)));
/* 00268a88: mult v0,a1,s4 */ nativeMultiply(2,(uint32_t)cpu(5),(uint32_t)cpu(20),1,0);
/* 00268a8c: nop  */ 
L_00268a90:;
/* 00268a90: lh v1,0x8(s2) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(18,(int32_t)UINT32_C(0x00000008))));
/* 00268a94: lh a0,0xa(s2) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(18,(int32_t)UINT32_C(0x0000000a))));
/* 00268a98: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 00268a9c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00268aa0: mtc1 a0,f2 */ f[2]=(uint32_t)cpu(4);
/* 00268aa4: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 00268aa8: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00268aac: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00268ab0: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00268ab4: nop  */ 
/* 00268ab8: nop  */ 
/* 00268abc: div.S f0,f0,f23 */ f[0]=EE_FPU_DIV_S(f[0],f[23]);
/* 00268ac0: add.S f20,f1,f0 */ f[20]=EE_FPU_ADD_S(f[1],f[0]);
/* 00268ac4: c.lt.S f2,f20 */ condition=EE_FPU_COMPARE_S(f[2],f[20],1)!=0;
/* 00268ac8: bc1tl 0x00268ad0 */ {int taken=(condition!=0);if(taken){/* delay 00268acc */ f[20]=f[2];goto L_00268ad0;}}
L_00268ad0:;
/* 00268ad0: slti v0,a1,0xa1 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x000000a1));
/* 00268ad4: move s0,s5 */ set(16,cpu(21));
/* 00268ad8: movn s0,a1,v0 */ if(cpu(2)!=0){set(16,cpu(5));}
/* 00268adc: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 00268ae0: jal 0x00243ee0 */ set(31,0x00268ae8u);/* delay 00268ae4 */ set(4,cpu(19));body_00243ee0();
/* 00268ae8: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 00268aec: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00268af0: lui at,0x4080 */ set(1,sx(UINT32_C(0x40800000)));
/* 00268af4: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00268af8: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00268afc: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00268b00: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00268b04: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 00268b08: lui at,0x4020 */ set(1,sx(UINT32_C(0x40200000)));
/* 00268b0c: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 00268b10: nop  */ 
/* 00268b14: nop  */ 
/* 00268b18: div.S f0,f0,f22 */ f[0]=EE_FPU_DIV_S(f[0],f[22]);
/* 00268b1c: nop  */ 
/* 00268b20: nop  */ 
/* 00268b24: div.S f12,f20,f12 */ f[12]=EE_FPU_DIV_S(f[20],f[12]);
/* 00268b28: add.S f0,f0,f2 */ f[0]=EE_FPU_ADD_S(f[0],f[2]);
/* 00268b2c: sub.S f1,f1,f0 */ f[1]=EE_FPU_SUB_S(f[1],f[0]);
/* 00268b30: mul.S f0,f1,f3 */ f[0]=EE_FPU_MUL_S(f[1],f[3]);
/* 00268b34: mul.S f12,f12,f0 */ f[12]=EE_FPU_MUL_S(f[12],f[0]);
/* 00268b38: jal 0x002d1550 */ set(31,0x00268b40u);/* delay 00268b3c */ f[12]=EE_FPU_ADD_S(f[20],f[12]);ps2EffectSoftDoubleFromFloat_002D1550(real(f[12]));
/* 00268b40: lui at,0x54 */ set(1,sx(UINT32_C(0x00540000)));
/* 00268b44: ld a1,0x4d28(at) */ restore(5,ea(1,(int32_t)UINT32_C(0x00004d28)));
/* 00268b48: move a0,v0 */ set(4,cpu(2));
/* 00268b4c: jal 0x002d18b0 */ set(31,0x00268b54u);/* delay 00268b50 */ body_002d18b0();
/* 00268b54: move a0,v0 */ set(4,cpu(2));
/* 00268b58: jal 0x002d1d10 */ set(31,0x00268b60u);/* delay 00268b5c */ ps2EffectSoftDoubleToFloat_002D1D10(cpu(4));
/* 00268b60: c.lt.S f21,f0 */ condition=EE_FPU_COMPARE_S(f[21],f[0],1)!=0;
/* 00268b64: bc1tl 0x00268b6c */ {int taken=(condition!=0);if(taken){/* delay 00268b68 */ f[21]=f[0];goto L_00268b6c;}}
L_00268b6c:;
/* 00268b6c: lhu a1,0x14(s3) */ set(5,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 00268b70: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 00268b74: slt v0,s1,a1 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(5));
/* 00268b78: bne v0,zero,0x00268a90 */ {int taken=(cpu(2)!=cpu(0));/* delay 00268b7c */ nativeMultiply(2,(uint32_t)cpu(5),(uint32_t)cpu(20),1,0);if(taken){goto L_00268a90;}}
/* 00268b80: lw v1,0x0(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 00268b84: andi v0,v1,0x20 */ set(2,cpu(3)&UINT32_C(0x00000020));
L_00268b88:;
/* 00268b88: beq v0,zero,0x00268bdc */ {int taken=(cpu(2)==cpu(0));/* delay 00268b8c */ f[12]=f[25];if(taken){goto L_00268bdc;}}
L_00268b90:;
/* 00268b90: lhu v0,0x14(s3) */ set(2,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 00268b94: li a0,0xaf2 */ set(4,sx(UINT32_C(0x00000af2)));
/* 00268b98: lui at,0x4248 */ set(1,sx(UINT32_C(0x42480000)));
/* 00268b9c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00268ba0: addiu v0,v0,0xa */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000000a)));
/* 00268ba4: lui at,0x3f40 */ set(1,sx(UINT32_C(0x3f400000)));
/* 00268ba8: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00268bac: mtc1 v0,f2 */ f[2]=(uint32_t)cpu(2);
/* 00268bb0: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 00268bb4: mul.S f0,f21,f0 */ f[0]=EE_FPU_MUL_S(f[21],f[0]);
/* 00268bb8: nop  */ 
/* 00268bbc: nop  */ 
/* 00268bc0: div.S f1,f1,f2 */ f[1]=EE_FPU_DIV_S(f[1],f[2]);
/* 00268bc4: jal 0x001e0f50 */ set(31,0x00268bccu);/* delay 00268bc8 */ f[21]=EE_FPU_SUB_S(f[0],f[1]);body_001e0f50();
/* 00268bcc: bne v0,zero,0x00268bdc */ {int taken=(cpu(2)!=cpu(0));/* delay 00268bd0 */ f[12]=f[25];if(taken){goto L_00268bdc;}}
/* 00268bd4: lwc1 f0,-0x5bf8(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa408)));
/* 00268bd8: mul.S f21,f21,f0 */ f[21]=EE_FPU_MUL_S(f[21],f[0]);
L_00268bdc:;
/* 00268bdc: jal 0x002d1550 */ set(31,0x00268be4u);/* delay 00268be0 */ set(16,sx(UINT32_C(0x00540000)));ps2EffectSoftDoubleFromFloat_002D1550(real(f[12]));
/* 00268be4: addiu s0,s0,0x4d00 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00004d00)));
/* 00268be8: move a0,s0 */ set(4,cpu(16));
/* 00268bec: lui s0,0x54 */ set(16,sx(UINT32_C(0x00540000)));
/* 00268bf0: move a1,v0 */ set(5,cpu(2));
/* 00268bf4: jal 0x002d4748 */ set(31,0x00268bfcu);/* delay 00268bf8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00004d10)));ps2BattleActionPrintf_002D4748(cpu(4));
/* 00268bfc: jal 0x002d1550 */ set(31,0x00268c04u);/* delay 00268c00 */ f[12]=f[24];ps2EffectSoftDoubleFromFloat_002D1550(real(f[12]));
/* 00268c04: move a1,v0 */ set(5,cpu(2));
/* 00268c08: jal 0x002d4748 */ set(31,0x00268c10u);/* delay 00268c0c */ set(4,cpu(16));ps2BattleActionPrintf_002D4748(cpu(4));
/* 00268c10: mul.S f0,f21,f25 */ f[0]=EE_FPU_MUL_S(f[21],f[25]);
/* 00268c14: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00268c18: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00268c1c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00268c20: mul.S f21,f0,f24 */ f[21]=EE_FPU_MUL_S(f[0],f[24]);
/* 00268c24: lwc1 f24,0x58(sp) */ f[24]=word(ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00268c28: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00268c2c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00268c30: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00268c34: cvt.w.S f0,f21 */ f[0]=EE_FPU_CVT_W_S(f[21]);
/* 00268c38: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 00268c3c: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00268c40: lwc1 f25,0x60(sp) */ f[25]=word(ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00268c44: lwc1 f23,0x50(sp) */ f[23]=word(ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00268c48: lwc1 f22,0x48(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00268c4c: lwc1 f21,0x40(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00268c50: lwc1 f20,0x38(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00268c54: jr ra */ {uint64_t target=cpu(31);/* delay 00268c58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_002688D0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_002688d0();
return cpu(2);
}
static void body_00268c60(void){
nocturneEffectAxisNoteEntry(0x00268c60u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00268c60: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00268c64: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00268c68: move s1,a1 */ set(17,cpu(5));
/* 00268c6c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00268c70: move s0,a2 */ set(16,cpu(6));
/* 00268c74: move a0,s1 */ set(4,cpu(17));
/* 00268c78: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00268c7c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00268c80: move s3,a3 */ set(19,cpu(7));
/* 00268c84: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00268c88: swc1 f21,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[21]);
/* 00268c8c: jal 0x00246ab8 */ set(31,0x00268c94u);/* delay 00268c90 */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00268c94: move a0,s0 */ set(4,cpu(16));
/* 00268c98: jal 0x00246ab8 */ set(31,0x00268ca0u);/* delay 00268c9c */ set(18,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00268ca0: move a0,s1 */ set(4,cpu(17));
/* 00268ca4: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 00268ca8: jal 0x002684b0 */ set(31,0x00268cb0u);/* delay 00268cac */ set(17,sx(UINT32_C(0x00540000)));body_002684b0();
/* 00268cb0: move a0,s2 */ set(4,cpu(18));
/* 00268cb4: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 00268cb8: jal 0x00243ee0 */ set(31,0x00268cc0u);/* delay 00268cbc */ f[21]=f[0];body_00243ee0();
/* 00268cc0: move a0,zero */ set(4,cpu(0));
/* 00268cc4: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
/* 00268cc8: jal 0x002c0c60 */ set(31,0x00268cd0u);/* delay 00268ccc */ set(16,cpu(2));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00268cd0: lhu v1,0x14(s2) */ set(3,half(ea(18,(int32_t)UINT32_C(0x00000014))));
/* 00268cd4: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 00268cd8: lui at,0x4120 */ set(1,sx(UINT32_C(0x41200000)));
/* 00268cdc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00268ce0: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 00268ce4: mtc1 s3,f1 */ f[1]=(uint32_t)cpu(19);
/* 00268ce8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00268cec: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00268cf0: mov.S f12,f21 */ f[12]=f[21];
/* 00268cf4: mtc1 s0,f20 */ f[20]=(uint32_t)cpu(16);
/* 00268cf8: cvt.s.W f20,f20 */ f[20]=EE_FPU_CVT_S_W(f[20]);
/* 00268cfc: addiu s1,s1,0x4d30 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00004d30)));
/* 00268d00: nop  */ 
/* 00268d04: nop  */ 
/* 00268d08: div.S f20,f20,f0 */ f[20]=EE_FPU_DIV_S(f[20],f[0]);
/* 00268d0c: jal 0x002d1550 */ set(31,0x00268d14u);/* delay 00268d10 */ f[20]=EE_FPU_MUL_S(f[20],f[1]);ps2EffectSoftDoubleFromFloat_002D1550(real(f[12]));
/* 00268d14: move a2,v0 */ set(6,cpu(2));
/* 00268d18: move a0,s1 */ set(4,cpu(17));
/* 00268d1c: move a1,s3 */ set(5,cpu(19));
/* 00268d20: mul.S f20,f20,f21 */ f[20]=EE_FPU_MUL_S(f[20],f[21]);
/* 00268d24: cvt.w.S f0,f20 */ f[0]=EE_FPU_CVT_W_S(f[20]);
/* 00268d28: mfc1 s0,f0 */ set(16,sx(f[0]));
/* 00268d2c: jal 0x002d4748 */ set(31,0x00268d34u);/* delay 00268d30 */ set(7,cpu(16));ps2BattleActionPrintf_002D4748(cpu(4));
/* 00268d34: move v0,s0 */ set(2,cpu(16));
/* 00268d38: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00268d3c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00268d40: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00268d44: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00268d48: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00268d4c: lwc1 f21,0x30(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00268d50: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00268d54: jr ra */ {uint64_t target=cpu(31);/* delay 00268d58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00268C60(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_00268c60();
return cpu(2);
}
static void body_00268d60(void){
nocturneEffectAxisNoteEntry(0x00268d60u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00268d60: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00268d64: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00268d68: move s0,a1 */ set(16,cpu(5));
/* 00268d6c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00268d70: move s1,a2 */ set(17,cpu(6));
/* 00268d74: move a0,s0 */ set(4,cpu(16));
/* 00268d78: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00268d7c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00268d80: move s3,a3 */ set(19,cpu(7));
/* 00268d84: swc1 f22,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[22]);
/* 00268d88: swc1 f21,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[21]);
/* 00268d8c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00268d90: jal 0x00246ab8 */ set(31,0x00268d98u);/* delay 00268d94 */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00268d98: move a0,s1 */ set(4,cpu(17));
/* 00268d9c: jal 0x00246ab8 */ set(31,0x00268da4u);/* delay 00268da0 */ set(18,cpu(2));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00268da4: move a0,s0 */ set(4,cpu(16));
/* 00268da8: jal 0x002684b0 */ set(31,0x00268db0u);/* delay 00268dac */ set(5,sx(UINT32_C(0x00000004)));body_002684b0();
/* 00268db0: move a0,s1 */ set(4,cpu(17));
/* 00268db4: li a1,0x7 */ set(5,sx(UINT32_C(0x00000007)));
/* 00268db8: jal 0x002684b0 */ set(31,0x00268dc0u);/* delay 00268dbc */ f[22]=f[0];body_002684b0();
/* 00268dc0: move a0,s2 */ set(4,cpu(18));
/* 00268dc4: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00268dc8: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00268dcc: beq v0,zero,0x00268e50 */ {int taken=(cpu(2)==cpu(0));/* delay 00268dd0 */ f[21]=f[0];if(taken){goto L_00268e50;}}
/* 00268dd4: jal 0x00242a88 */ set(31,0x00268ddcu);/* delay 00268dd8 */ body_00242a88();
/* 00268ddc: lwc1 f1,-0x5bf4(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa40c)));
/* 00268de0: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00268de4: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00268de8: lhu v0,0x14(s2) */ set(2,half(ea(18,(int32_t)UINT32_C(0x00000014))));
/* 00268dec: mtc1 s3,f3 */ f[3]=(uint32_t)cpu(19);
/* 00268df0: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 00268df4: lui at,0x4248 */ set(1,sx(UINT32_C(0x42480000)));
/* 00268df8: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00268dfc: addiu v0,v0,0xa */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000000a)));
/* 00268e00: lwc1 f4,-0x5bf0(gp) */ f[4]=word(ea(28,(int32_t)UINT32_C(0xffffa410)));
/* 00268e04: li a0,0xaf2 */ set(4,sx(UINT32_C(0x00000af2)));
/* 00268e08: nop  */ 
/* 00268e0c: nop  */ 
/* 00268e10: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 00268e14: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00268e18: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00268e1c: nop  */ 
/* 00268e20: nop  */ 
/* 00268e24: div.S f2,f2,f1 */ f[2]=EE_FPU_DIV_S(f[2],f[1]);
/* 00268e28: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 00268e2c: mul.S f0,f0,f4 */ f[0]=EE_FPU_MUL_S(f[0],f[4]);
/* 00268e30: jal 0x001e0f50 */ set(31,0x00268e38u);/* delay 00268e34 */ f[20]=EE_FPU_SUB_S(f[0],f[2]);body_001e0f50();
/* 00268e38: bnel v0,zero,0x00268e84 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00268e3c */ f[0]=EE_FPU_MUL_S(f[20],f[22]);goto L_00268e84;}}
/* 00268e40: lwc1 f0,-0x5bec(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa414)));
/* 00268e44: b 0x00268e80 */ /* delay 00268e48 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);goto L_00268e80;
L_00268e50:;
/* 00268e50: lhu v0,0x8(s2) */ set(2,half(ea(18,(int32_t)UINT32_C(0x00000008))));
/* 00268e54: mtc1 s3,f2 */ f[2]=(uint32_t)cpu(19);
/* 00268e58: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 00268e5c: lwc1 f1,-0x5be8(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa418)));
/* 00268e60: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00268e64: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00268e68: nop  */ 
/* 00268e6c: nop  */ 
/* 00268e70: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 00268e74: lwc1 f1,-0x5be4(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa41c)));
/* 00268e78: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 00268e7c: mul.S f20,f0,f1 */ f[20]=EE_FPU_MUL_S(f[0],f[1]);
L_00268e80:;
/* 00268e80: mul.S f0,f20,f22 */ f[0]=EE_FPU_MUL_S(f[20],f[22]);
L_00268e84:;
/* 00268e84: lwc1 f22,0x38(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00268e88: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00268e8c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00268e90: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00268e94: mul.S f20,f0,f21 */ f[20]=EE_FPU_MUL_S(f[0],f[21]);
/* 00268e98: lwc1 f21,0x30(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00268e9c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00268ea0: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00268ea4: cvt.w.S f0,f20 */ f[0]=EE_FPU_CVT_W_S(f[20]);
/* 00268ea8: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 00268eac: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00268eb0: jr ra */ {uint64_t target=cpu(31);/* delay 00268eb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_00268D60(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_00268d60();
return cpu(2);
}
static void body_0026a2d8(void){
nocturneEffectAxisNoteEntry(0x0026a2d8u);
uint64_t incoming=cpu(31);
/* 0026a2d8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026a2dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a2e0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a2e4: jal 0x00246ab8 */ set(31,0x0026a2ecu);/* delay 0026a2e8 */ set(16,cpu(4));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 0026a2ec: move a0,v0 */ set(4,cpu(2));
/* 0026a2f0: jal 0x00243f40 */ set(31,0x0026a2f8u);/* delay 0026a2f4 */ set(5,sx(UINT32_C(0x00000159)));body_00243f40();
/* 0026a2f8: beq v0,zero,0x0026a328 */ {int taken=(cpu(2)==cpu(0));/* delay 0026a2fc */ set(4,cpu(16));if(taken){goto L_0026a328;}}
/* 0026a300: jal 0x00246a40 */ set(31,0x0026a308u);/* delay 0026a304 */ ps2BattleActionScaleLookup_00246A40(cpu(4));
/* 0026a308: move a1,v0 */ set(5,cpu(2));
/* 0026a30c: lhu v1,0x0(a1) */ set(3,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 0026a310: ori a0,v1,0x200 */ set(4,cpu(3)|UINT32_C(0x00000200));
/* 0026a314: andi v1,v1,0x400 */ set(3,cpu(3)&UINT32_C(0x00000400));
/* 0026a318: bne v1,zero,0x0026a328 */ {int taken=(cpu(3)!=cpu(0));/* delay 0026a31c */ set(2,cpu(0));if(taken){goto L_0026a328;}}
/* 0026a320: sh a0,0x0(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));
/* 0026a324: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_0026a328:;
/* 0026a328: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a32c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a330: jr ra */ {uint64_t target=cpu(31);/* delay 0026a334 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_0026A2D8(uint64_t a0){
set(4,a0);
body_0026a2d8();
return cpu(2);
}
static void body_0026a338(void){
nocturneEffectAxisNoteEntry(0x0026a338u);
uint64_t incoming=cpu(31);
/* 0026a338: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026a33c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a340: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a344: jal 0x00246ab8 */ set(31,0x0026a34cu);/* delay 0026a348 */ set(16,cpu(4));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 0026a34c: move a0,v0 */ set(4,cpu(2));
/* 0026a350: jal 0x00243f40 */ set(31,0x0026a358u);/* delay 0026a354 */ set(5,sx(UINT32_C(0x00000168)));body_00243f40();
/* 0026a358: beq v0,zero,0x0026a388 */ {int taken=(cpu(2)==cpu(0));/* delay 0026a35c */ set(4,cpu(16));if(taken){goto L_0026a388;}}
/* 0026a360: jal 0x00246a40 */ set(31,0x0026a368u);/* delay 0026a364 */ ps2BattleActionScaleLookup_00246A40(cpu(4));
/* 0026a368: move a1,v0 */ set(5,cpu(2));
/* 0026a36c: lhu v1,0x0(a1) */ set(3,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 0026a370: ori a0,v1,0x200 */ set(4,cpu(3)|UINT32_C(0x00000200));
/* 0026a374: andi v1,v1,0x400 */ set(3,cpu(3)&UINT32_C(0x00000400));
/* 0026a378: bne v1,zero,0x0026a388 */ {int taken=(cpu(3)!=cpu(0));/* delay 0026a37c */ set(2,cpu(0));if(taken){goto L_0026a388;}}
/* 0026a380: sh a0,0x0(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));
/* 0026a384: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_0026a388:;
/* 0026a388: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a38c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a390: jr ra */ {uint64_t target=cpu(31);/* delay 0026a394 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_0026A338(uint64_t a0){
set(4,a0);
body_0026a338();
return cpu(2);
}
static void body_0026a398(void){
nocturneEffectAxisNoteEntry(0x0026a398u);
uint64_t incoming=cpu(31);
/* 0026a398: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026a39c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a3a0: jal 0x00246a40 */ set(31,0x0026a3a8u);/* delay 0026a3a4 */ ps2BattleActionScaleLookup_00246A40(cpu(4));
/* 0026a3a8: move v1,v0 */ set(3,cpu(2));
/* 0026a3ac: beq v1,zero,0x0026a3cc */ {int taken=(cpu(3)==cpu(0));/* delay 0026a3b0 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0026a3cc;}}
/* 0026a3b4: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 0026a3b8: ori a0,v0,0x400 */ set(4,cpu(2)|UINT32_C(0x00000400));
/* 0026a3bc: andi v0,v0,0x200 */ set(2,cpu(2)&UINT32_C(0x00000200));
/* 0026a3c0: bnel v0,zero,0x0026a3cc */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0026a3c4 */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));goto L_0026a3cc;}}
/* 0026a3c8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0026a3cc:;
/* 0026a3cc: jr ra */ {uint64_t target=cpu(31);/* delay 0026a3d0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionFormula_0026A398(uint64_t a0){
set(4,a0);
body_0026a398();
return;
}
static void body_0026a3d8(void){
nocturneEffectAxisNoteEntry(0x0026a3d8u);
uint64_t incoming=cpu(31);
/* 0026a3d8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026a3dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a3e0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a3e4: jal 0x00243f40 */ set(31,0x0026a3ecu);/* delay 0026a3e8 */ set(16,cpu(5));body_00243f40();
/* 0026a3ec: beq v0,zero,0x0026a434 */ {int taken=(cpu(2)==cpu(0));/* delay 0026a3f0 */ set(3,sx(UINT32_C(0x0000012c)));if(taken){goto L_0026a434;}}
/* 0026a3f4: beq s0,v1,0x0026a410 */ {int taken=(cpu(16)==cpu(3));/* delay 0026a3f8 */ set(2,sx(UINT32_C(0x0000012d)));if(taken){goto L_0026a410;}}
/* 0026a3fc: beq s0,v0,0x0026a428 */ {int taken=(cpu(16)==cpu(2));/* delay 0026a400 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0026a428;}}
/* 0026a404: b 0x0026a438 */ /* delay 0026a408 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0026a438;
L_0026a410:;
/* 0026a410: jal 0x001e9998 */ set(31,0x0026a418u);/* delay 0026a414 */ body_001e9998();
/* 0026a418: xori v0,v0,0x8 */ set(2,cpu(2)^UINT32_C(0x00000008));
/* 0026a41c: b 0x0026a434 */ /* delay 0026a420 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));goto L_0026a434;
L_0026a428:;
/* 0026a428: jal 0x001e9998 */ set(31,0x0026a430u);/* delay 0026a42c */ body_001e9998();
/* 0026a430: sltiu v0,v0,0x1 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_0026a434:;
/* 0026a434: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0026a438:;
/* 0026a438: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a43c: jr ra */ {uint64_t target=cpu(31);/* delay 0026a440 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_0026A3D8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_0026a3d8();
return cpu(2);
}
static void body_0026a468(void){
nocturneEffectAxisNoteEntry(0x0026a468u);
uint64_t incoming=cpu(31);
/* 0026a468: jr ra */ {uint64_t target=cpu(31);/* delay 0026a46c */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000004));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_0026A468(uint64_t a0){
set(4,a0);
body_0026a468();
return cpu(2);
}
static void body_0026a470(void){
nocturneEffectAxisNoteEntry(0x0026a470u);
uint64_t incoming=cpu(31);
/* 0026a470: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0026a474: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a478: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a47c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026a480: jal 0x0026a468 */ set(31,0x0026a488u);/* delay 0026a484 */ set(17,cpu(5));body_0026a468();
/* 0026a488: move a0,s1 */ set(4,cpu(17));
/* 0026a48c: jal 0x0026a468 */ set(31,0x0026a494u);/* delay 0026a490 */ set(16,cpu(2));body_0026a468();
/* 0026a494: xor s0,s0,v0 */ set(16,cpu(16)^cpu(2));
/* 0026a498: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a49c: sltiu v0,s0,0x1 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
/* 0026a4a0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a4a4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026a4a8: jr ra */ {uint64_t target=cpu(31);/* delay 0026a4ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionFormula_0026A470(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_0026a470();
return cpu(2);
}
static void body_0026a828(void){
nocturneEffectAxisNoteEntry(0x0026a828u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0026a828: slti a0,a0,0x4 */ set(4,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0026a82c: lui at,0x3fc0 */ set(1,sx(UINT32_C(0x3fc00000)));
/* 0026a830: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0026a834: mul.S f12,f12,f0 */ f[12]=EE_FPU_MUL_S(f[12],f[0]);
/* 0026a838: jr ra */ {uint64_t target=cpu(31);/* delay 0026a83c */ f[0]=f[12];checkReturn(target,incoming);return;}
}
float ps2BattleActionFormula_0026A828(uint64_t a0, float f12){
set(4,a0);
nocturneEffectHostFpr()[12]=bits(f12);
body_0026a828();
return real(nocturneEffectHostFpr()[0]);
}
static void body_002c0c00(void){
nocturneEffectAxisNoteEntry(0x002c0c00u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002c0c00: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c0c04: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0c08: jal 0x002c0ba8 */ set(31,0x002c0c10u);/* delay 002c0c0c */ ps2EffectRandomWord_002C0BA8(cpu(4));
/* 002c0c10: lui v1,0xff */ set(3,sx(UINT32_C(0x00ff0000)));
/* 002c0c14: andi a0,v0,0x1 */ set(4,cpu(2)&UINT32_C(0x00000001));
/* 002c0c18: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002c0c1c: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002c0c20: bltz v0,0x002c0c38 */ {int taken=((int64_t)cpu(2)<0);/* delay 002c0c24 */ set(3,sx((uint32_t)cpu(2)>>1));if(taken){goto L_002c0c38;}}
/* 002c0c28: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 002c0c2c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 002c0c30: b 0x002c0c48 */ /* delay 002c0c34 */ goto L_002c0c48;
L_002c0c38:;
/* 002c0c38: or a0,a0,v1 */ set(4,cpu(4)|cpu(3));
/* 002c0c3c: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
/* 002c0c40: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 002c0c44: add.S f1,f1,f1 */ f[1]=EE_FPU_ADD_S(f[1],f[1]);
L_002c0c48:;
/* 002c0c48: lui at,0x3380 */ set(1,sx(UINT32_C(0x33800000)));
/* 002c0c4c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c0c50: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0c54: mul.S f0,f1,f0 */ f[0]=EE_FPU_MUL_S(f[1],f[0]);
/* 002c0c58: jr ra */ {uint64_t target=cpu(31);/* delay 002c0c5c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
float ps2BattleActionFormula_002C0C00(uint64_t a0){
set(4,a0);
body_002c0c00();
return real(nocturneEffectHostFpr()[0]);
}
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
/* 002d18e0: jal 0x002d3578 */ set(31,0x002d18e8u);/* delay 002d18e4 */ set(5,cpu(29));ps2EffectSoftDoubleUnpack_002D3578(cpu(4),cpu(5));
/* 002d18e8: addiu s0,sp,0x20 */ set(16,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d18ec: addiu a0,sp,0x68 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000068)));
/* 002d18f0: jal 0x002d3578 */ set(31,0x002d18f8u);/* delay 002d18f4 */ set(5,cpu(16));ps2EffectSoftDoubleUnpack_002D3578(cpu(4),cpu(5));
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
/* 002d19c8: jal 0x002d3398 */ set(31,0x002d19d0u);/* delay 002d19cc */ set(4,cpu(22));body_002d3398();
/* 002d19d0: move a0,s2 */ set(4,cpu(18));
/* 002d19d4: move a1,s0 */ set(5,cpu(16));
/* 002d19d8: jal 0x002d3398 */ set(31,0x002d19e0u);/* delay 002d19dc */ set(20,cpu(2));body_002d3398();
/* 002d19e0: move a0,s6 */ set(4,cpu(22));
/* 002d19e4: move a1,s3 */ set(5,cpu(19));
/* 002d19e8: jal 0x002d3398 */ set(31,0x002d19f0u);/* delay 002d19ec */ set(17,cpu(2));body_002d3398();
/* 002d19f0: move a0,s2 */ set(4,cpu(18));
/* 002d19f4: move s0,v0 */ set(16,cpu(2));
/* 002d19f8: move a1,s3 */ set(5,cpu(19));
/* 002d19fc: jal 0x002d3398 */ set(31,0x002d1a04u);/* delay 002d1a00 */ set(16,cpu(17)+cpu(16));body_002d3398();
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
/* 002d1b04: jal 0x002d34a0 */ set(31,0x002d1b0cu);/* delay 002d1b08 */ ps2EffectSoftDoublePack_002D34A0(cpu(4));
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
uint64_t ps2BattleActionFormula_002D18B0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002d18b0();
return cpu(2);
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
uint64_t ps2BattleActionFormula_002D3398(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002d3398();
return cpu(2);
}
static int bridgePointer(const void *p,unsigned reg){return p?at((uint32_t)cpu(reg))==(const uint8_t *)p:cpu(reg)==0;}
float ps2BattleActionFormulaLegacy_sdfGetRandFloat(uint32_t *state){if(!bridgePointer(state,4))abort();body_002c0c00();return real(nocturneEffectHostFpr()[0]);}
uint32_t ps2BattleActionFormulaLegacy_evtBitCheck(int32_t no){if((uint32_t)no!=(uint32_t)cpu(4))abort();body_001e0f50();return (uint32_t)(uint32_t)cpu(2);}
uint32_t ps2BattleActionFormulaLegacy_evtGetAgeOfMoon(void){if(0)abort();body_001e9998();return (uint32_t)(uint32_t)cpu(2);}
int32_t ps2BattleActionFormulaLegacy_datGetBaseMaxHp(datUnitWork_PS2 *work){if(!bridgePointer(work,4))abort();body_00242a88();return (int32_t)(uint32_t)cpu(2);}
void ps2BattleActionFormulaLegacy_datSetBadStat(datUnitWork_PS2 *work,uint32_t status){if(!bridgePointer(work,4)||status!=(uint32_t)cpu(5))abort();body_00243bd0();return;}
void ps2BattleActionFormulaLegacy_datResetBadStat(datUnitWork_PS2 *work,uint32_t status){if(!bridgePointer(work,4)||status!=(uint32_t)cpu(5))abort();body_00243c10();return;}
int32_t ps2BattleActionFormulaLegacy_datGetBaseParam(datUnitWork_PS2 *work,int32_t selector){if(!bridgePointer(work,4)||(uint32_t)selector!=(uint32_t)cpu(5))abort();body_00243e78();return (int32_t)(uint32_t)cpu(2);}
int32_t ps2BattleActionFormulaLegacy_datGetParam(datUnitWork_PS2 *work,int32_t selector){if(!bridgePointer(work,4)||(uint32_t)selector!=(uint32_t)cpu(5))abort();body_00243ee0();return (int32_t)(uint32_t)cpu(2);}
int32_t ps2BattleActionFormulaLegacy_datGetBadStatusAttr(int32_t status){if((uint32_t)status!=(uint32_t)cpu(4))abort();body_002440c0();return (int32_t)(uint32_t)cpu(2);}
int32_t ps2BattleActionFormulaLegacy_datCheckSyojiSkill(datUnitWork_PS2 *work,uint32_t skill){if(!bridgePointer(work,4)||skill!=(uint32_t)cpu(5))abort();body_00243f40();return (int32_t)(uint32_t)cpu(2);}
int32_t ps2BattleActionFormulaLegacy_nbHatudoCheckSkill(datUnitWork_PS2 *work,int32_t skill){if(!bridgePointer(work,4)||(uint32_t)skill!=(uint32_t)cpu(5))abort();body_0026a3d8();return (int32_t)(uint32_t)cpu(2);}
