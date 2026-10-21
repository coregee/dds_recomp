/* Complete fixed native guest-frame variants of eight registered hit/cut
 * bodies. Original load/store/alias and delay-slot ordering are authoritative.
 * These replace no whole body with captured results and add no new identity.
 * Other registered semantic dependencies keep explicit volatile/frame limits.
 */
#include "battle_action_hit_frames.h"
#include "battle_action_consumer.h"
#include "battle_action_copy_frames.h"
#include "battle_action_activation.h"
#include "battle_effect_copy.h"
#include "libc_printf.h"
#include "../analysis/drafts/model-context-anchor/effect_host_bindings.h"
#include "../analysis/drafts/model-context-anchor/effect_model_child_dependency_frames.h"
#include "../analysis/drafts/model-context-anchor/effect_billboard_dependency_frames.h"
#include <stdlib.h>
#include <string.h>
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t *fpr(void){return nocturneEffectHostFpr();}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t ea(uint64_t base,uint32_t delta){return (uint32_t)base+delta;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint8_t r8(uint32_t a){return *at(a);}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t r64(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w64(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint32_t bits(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static float real(uint32_t b){float v;memcpy(&v,&b,4);return v;}
static void checkReturn(uint64_t incoming,uint64_t target){if((uint32_t)incoming!=(uint32_t)target)abort();}

uint64_t ps2BattleActionCutCreate_0016AC70(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectAxisNoteEntry(0x0016ac70u);
uint64_t incoming=cpu(31);
/* 0016ac70: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 0016ac74: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
/* 0016ac78: move s0,a0 */ set(16,cpu(4));
/* 0016ac7c: li a0,0x120 */ set(4,sx(UINT32_C(0x00000120)));
/* 0016ac80: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
/* 0016ac84: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
/* 0016ac88: andi s1,a1,0xffff */ set(17,cpu(5)&UINT32_C(0x0000ffff));
/* 0016ac8c: sd s3,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(19));
/* 0016ac90: move s3,a3 */ set(19,cpu(7));
/* 0016ac94: sd s4,0x20(sp) */ w64(ea(cpu(29),UINT32_C(0x00000020)),(uint64_t)cpu(20));
/* 0016ac98: sd s5,0x28(sp) */ w64(ea(cpu(29),UINT32_C(0x00000028)),(uint64_t)cpu(21));
/* 0016ac9c: sd s6,0x30(sp) */ w64(ea(cpu(29),UINT32_C(0x00000030)),(uint64_t)cpu(22));
/* 0016aca0: sd s7,0x38(sp) */ w64(ea(cpu(29),UINT32_C(0x00000038)),(uint64_t)cpu(23));
/* 0016aca4: sd ra,0x40(sp) */ w64(ea(cpu(29),UINT32_C(0x00000040)),(uint64_t)cpu(31));
/* 0016aca8: jal 0x002a8af8 */ set(31,0x0016acb0u);/* delay 0016acac */ set(20,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0016acb0: move s2,v0 */ set(18,cpu(2));
/* 0016acb4: move a1,zero */ set(5,cpu(0));
/* 0016acb8: move a0,s2 */ set(4,cpu(18));
/* 0016acbc: jal 0x002d4558 */ set(31,0x0016acc4u);/* delay 0016acc0 */ set(6,sx(UINT32_C(0x00000120)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 0016acc4: sw s0,0x4(s2) */ w32(ea(cpu(18),UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 0016acc8: sltiu v0,s1,0x2 */ set(2,cpu(17)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0016accc: addiu v1,s0,0x620 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000620)));
/* 0016acd0: addiu a2,s0,0x8 */ set(6,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));
/* 0016acd4: lw a0,0xc40(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000c40)))));
/* 0016acd8: movz a2,v1,v0 */ if(cpu(2)==0)set(6,cpu(3));
/* 0016acdc: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 0016ace0: lw v0,0x0(a2) */ set(2,sx(r32(ea(cpu(6),UINT32_C(0x00000000)))));
/* 0016ace4: sw a0,0x11c(s2) */ w32(ea(cpu(18),UINT32_C(0x0000011c)),(uint32_t)cpu(4));
/* 0016ace8: sw v0,0xc(s2) */ w32(ea(cpu(18),UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 0016acec: sw s2,0xc40(s0) */ w32(ea(cpu(16),UINT32_C(0x00000c40)),(uint32_t)cpu(18));
/* 0016acf0: sh s1,0x14(s2) */ w16(ea(cpu(18),UINT32_C(0x00000014)),(uint16_t)cpu(17));
/* 0016acf4: bne s1,a1,0x0016ad08 */ {int taken=(cpu(17)!=cpu(5));/* delay 0016acf8 */ w32(ea(cpu(18),UINT32_C(0x0000001c)),(uint32_t)cpu(6));if(taken){goto L_0016ad08;}}
/* 0016acfc: b 0x0016ad0c */ /* delay 0016ad00 */ set(2,sx(r32(ea(cpu(6),UINT32_C(0x00000000)))));goto L_0016ad0c;
L_0016ad08:;
/* 0016ad08: lw v0,0x70(a2) */ set(2,sx(r32(ea(cpu(6),UINT32_C(0x00000070)))));
L_0016ad0c:;
/* 0016ad0c: sw v0,0x10(s2) */ w32(ea(cpu(18),UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 0016ad10: lw v0,0x1c(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x0000001c)))));
/* 0016ad14: addiu s1,s2,0x20 */ set(17,sx((uint32_t)cpu(18)+UINT32_C(0x00000020)));
/* 0016ad18: sw s3,0x18(s2) */ w32(ea(cpu(18),UINT32_C(0x00000018)),(uint32_t)cpu(19));
/* 0016ad1c: sw s4,0x0(s2) */ w32(ea(cpu(18),UINT32_C(0x00000000)),(uint32_t)cpu(20));
/* 0016ad20: addiu s0,v0,0x78 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0x00000078)));
/* 0016ad24: lhu v1,0x6c(v0) */ set(3,r16(ea(cpu(2),UINT32_C(0x0000006c))));
/* 0016ad28: beq v1,zero,0x0016ada8 */ {int taken=(cpu(3)==cpu(0));/* delay 0016ad2c */ set(21,r8(ea(cpu(2),UINT32_C(0x00000074))));if(taken){goto L_0016ada8;}}
/* 0016ad30: move s3,v1 */ set(19,cpu(3));
/* 0016ad34: ori s7,zero,0xfffe */ set(23,cpu(0)|UINT32_C(0x0000fffe));
/* 0016ad38: li s6,0x4 */ set(22,sx(UINT32_C(0x00000004)));
/* 0016ad3c: nop  */ ;
L_0016ad40:;
/* 0016ad40: lhu v0,0x0(s0) */ set(2,r16(ea(cpu(16),UINT32_C(0x00000000))));
/* 0016ad44: beql v0,s7,0x0016ad98 */ {int taken=(cpu(2)==cpu(23));if(taken){/* delay 0016ad48 */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(0));goto L_0016ad98;}}
/* 0016ad4c: jal 0x00175a88 */ set(31,0x0016ad54u);/* delay 0016ad50 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000004)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 0016ad54: beq s5,zero,0x0016ad98 */ {int taken=(cpu(21)==cpu(0));/* delay 0016ad58 */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_0016ad98;}}
/* 0016ad5c: beql s4,zero,0x0016ad9c */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 0016ad60 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));goto L_0016ad9c;}}
/* 0016ad64: lbu v0,0x8(s0) */ set(2,r8(ea(cpu(16),UINT32_C(0x00000008))));
/* 0016ad68: beq v0,zero,0x0016ad78 */ {int taken=(cpu(2)==cpu(0));/* delay 0016ad6c */ ;if(taken){goto L_0016ad78;}}
/* 0016ad70: bnel v0,s6,0x0016ad9c */ {int taken=(cpu(2)!=cpu(22));if(taken){/* delay 0016ad74 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));goto L_0016ad9c;}}
L_0016ad78:;
/* 0016ad78: jal 0x0016e698 */ set(31,0x0016ad80u);/* delay 0016ad7c */ set(4,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));fpr()[0]=bits(effBTLPartGetScalePtr(cpu(4)));
/* 0016ad80: lw a0,0x0(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000000)))));
/* 0016ad84: jal 0x00175b38 */ set(31,0x0016ad8cu);/* delay 0016ad88 */ fpr()[12]=fpr()[0];ps2BattleActionPartScale_00175B38(cpu(4),real(fpr()[12]));
/* 0016ad8c: b 0x0016ad9c */ /* delay 0016ad90 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));goto L_0016ad9c;
L_0016ad98:;
/* 0016ad98: addiu s3,s3,-0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));
L_0016ad9c:;
/* 0016ad9c: addiu s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
/* 0016ada0: bne s3,zero,0x0016ad40 */ {int taken=(cpu(19)!=cpu(0));/* delay 0016ada4 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000018)));if(taken){goto L_0016ad40;}}
L_0016ada8:;
/* 0016ada8: lw a2,0x4(s2) */ set(6,sx(r32(ea(cpu(18),UINT32_C(0x00000004)))));
/* 0016adac: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0016adb0: sw zero,0x8(s2) */ w32(ea(cpu(18),UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 0016adb4: addiu a0,a0,0x2e50 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00002e50)));
/* 0016adb8: lhu a1,0x14(s2) */ set(5,r16(ea(cpu(18),UINT32_C(0x00000014))));
/* 0016adbc: jal 0x002d4748 */ set(31,0x0016adc4u);/* delay 0016adc0 */ set(7,sx(r32(ea(cpu(6),UINT32_C(0x00000c3c)))));set(2,ps2LibcPrintf(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 0016adc4: lw a0,0x4(s2) */ set(4,sx(r32(ea(cpu(18),UINT32_C(0x00000004)))));
/* 0016adc8: move v0,s2 */ set(2,cpu(18));
/* 0016adcc: lw v1,0xc3c(a0) */ set(3,sx(r32(ea(cpu(4),UINT32_C(0x00000c3c)))));
/* 0016add0: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
/* 0016add4: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
/* 0016add8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0016addc: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
/* 0016ade0: ld s3,0x18(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000018))));
/* 0016ade4: ld s4,0x20(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x00000020))));
/* 0016ade8: ld s5,0x28(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x00000028))));
/* 0016adec: ld s6,0x30(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x00000030))));
/* 0016adf0: ld s7,0x38(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x00000038))));
/* 0016adf4: ld ra,0x40(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000040))));
/* 0016adf8: sw v1,0xc3c(a0) */ w32(ea(cpu(4),UINT32_C(0x00000c3c)),(uint32_t)cpu(3));
/* 0016adfc: jr ra */ {uint64_t target=cpu(31);/* delay 0016ae00 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(incoming,target);return cpu(2);}
}
uint64_t ps2BattleActionHitCreate20_00172618(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00172618u);
uint64_t incoming=cpu(31);
/* 00172618: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0017261c: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
/* 00172620: move s0,a0 */ set(16,cpu(4));
/* 00172624: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
/* 00172628: sd ra,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(31));
/* 0017262c: jal 0x002a8af8 */ set(31,0x00172634u);/* delay 00172630 */ set(4,sx(UINT32_C(0x0000000c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00172634: move s1,v0 */ set(17,cpu(2));
/* 00172638: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 0017263c: sw s0,0x0(s1) */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 00172640: move a2,s0 */ set(6,cpu(16));
/* 00172644: sw zero,0x4(s1) */ w32(ea(cpu(17),UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 00172648: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 0017264c: lw a0,-0x42dc(v0) */ set(4,sx(r32(ea(cpu(2),UINT32_C(0xffffbd24)))));
/* 00172650: jal 0x0016ac70 */ set(31,0x00172658u);/* delay 00172654 */ set(7,cpu(0));set(2,ps2BattleActionCutCreate_0016AC70(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 00172658: sw v0,0x8(s1) */ w32(ea(cpu(17),UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0017265c: move v0,s1 */ set(2,cpu(17));
/* 00172660: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
/* 00172664: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
/* 00172668: ld ra,0x10(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000010))));
/* 0017266c: jr ra */ {uint64_t target=cpu(31);/* delay 00172670 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(incoming,target);return cpu(2);}
}
uint64_t ps2BattleActionHitCreate24_001727B0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001727b0u);
uint64_t incoming=cpu(31);
/* 001727b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001727b4: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
/* 001727b8: move s2,a0 */ set(18,cpu(4));
/* 001727bc: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 001727c0: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
/* 001727c4: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
/* 001727c8: sd ra,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(31));
/* 001727cc: jal 0x002a8af8 */ set(31,0x001727d4u);/* delay 001727d0 */ set(16,sx(UINT32_C(0x00320000)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 001727d4: move s1,v0 */ set(17,cpu(2));
/* 001727d8: addiu s0,s0,-0x42d0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffbd30)));
/* 001727dc: sw s2,0x0(s1) */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(18));
/* 001727e0: lw a0,0x10(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000010)))));
/* 001727e4: jal 0x00175a88 */ set(31,0x001727ecu);/* delay 001727e8 */ w32(ea(cpu(17),UINT32_C(0x00000004)),(uint32_t)cpu(0));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 001727ec: sw v0,0x8(s1) */ w32(ea(cpu(17),UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001727f0: jal 0x00175a88 */ set(31,0x001727f8u);/* delay 001727f4 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x0000002c)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 001727f8: sw v0,0xc(s1) */ w32(ea(cpu(17),UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001727fc: jal 0x00175a88 */ set(31,0x00172804u);/* delay 00172800 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000048)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172804: sw v0,0x10(s1) */ w32(ea(cpu(17),UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 00172808: jal 0x00175a88 */ set(31,0x00172810u);/* delay 0017280c */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000064)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172810: sw v0,0x14(s1) */ w32(ea(cpu(17),UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 00172814: jal 0x00175a88 */ set(31,0x0017281cu);/* delay 00172818 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000080)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 0017281c: sw v0,0x18(s1) */ w32(ea(cpu(17),UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 00172820: jal 0x00175a88 */ set(31,0x00172828u);/* delay 00172824 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x0000009c)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172828: sw v0,0x1c(s1) */ w32(ea(cpu(17),UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 0017282c: move v0,s1 */ set(2,cpu(17));
/* 00172830: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
/* 00172834: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
/* 00172838: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
/* 0017283c: ld ra,0x18(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000018))));
/* 00172840: jr ra */ {uint64_t target=cpu(31);/* delay 00172844 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(incoming,target);return cpu(2);}
}
uint64_t ps2BattleActionHitCreate25_00172DA0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00172da0u);
uint64_t incoming=cpu(31);
/* 00172da0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00172da4: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
/* 00172da8: move s2,a0 */ set(18,cpu(4));
/* 00172dac: li a0,0x38 */ set(4,sx(UINT32_C(0x00000038)));
/* 00172db0: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
/* 00172db4: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
/* 00172db8: sd ra,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(31));
/* 00172dbc: jal 0x002a8af8 */ set(31,0x00172dc4u);/* delay 00172dc0 */ set(16,sx(UINT32_C(0x00320000)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00172dc4: move s1,v0 */ set(17,cpu(2));
/* 00172dc8: addiu s0,s0,-0x42d0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffbd30)));
/* 00172dcc: sw s2,0x0(s1) */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(18));
/* 00172dd0: lw a0,0x10(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000010)))));
/* 00172dd4: jal 0x00175a88 */ set(31,0x00172ddcu);/* delay 00172dd8 */ w32(ea(cpu(17),UINT32_C(0x00000004)),(uint32_t)cpu(0));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172ddc: sw v0,0x8(s1) */ w32(ea(cpu(17),UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 00172de0: jal 0x00175a88 */ set(31,0x00172de8u);/* delay 00172de4 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x0000002c)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172de8: sw v0,0xc(s1) */ w32(ea(cpu(17),UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 00172dec: jal 0x00175a88 */ set(31,0x00172df4u);/* delay 00172df0 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000048)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172df4: sw v0,0x10(s1) */ w32(ea(cpu(17),UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 00172df8: jal 0x00175a88 */ set(31,0x00172e00u);/* delay 00172dfc */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000064)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e00: sw v0,0x14(s1) */ w32(ea(cpu(17),UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 00172e04: jal 0x00175a88 */ set(31,0x00172e0cu);/* delay 00172e08 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000080)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e0c: sw v0,0x18(s1) */ w32(ea(cpu(17),UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 00172e10: lw a0,0x9c(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x0000009c)))));
/* 00172e14: lui s0,0x32 */ set(16,sx(UINT32_C(0x00320000)));
/* 00172e18: jal 0x00175a88 */ set(31,0x00172e20u);/* delay 00172e1c */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffbdd8)));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e20: sw v0,0x1c(s1) */ w32(ea(cpu(17),UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 00172e24: jal 0x00175a88 */ set(31,0x00172e2cu);/* delay 00172e28 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000010)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e2c: sw v0,0x20(s1) */ w32(ea(cpu(17),UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 00172e30: jal 0x00175a88 */ set(31,0x00172e38u);/* delay 00172e34 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x0000002c)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e38: sw v0,0x24(s1) */ w32(ea(cpu(17),UINT32_C(0x00000024)),(uint32_t)cpu(2));
/* 00172e3c: jal 0x00175a88 */ set(31,0x00172e44u);/* delay 00172e40 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000048)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e44: sw v0,0x28(s1) */ w32(ea(cpu(17),UINT32_C(0x00000028)),(uint32_t)cpu(2));
/* 00172e48: jal 0x00175a88 */ set(31,0x00172e50u);/* delay 00172e4c */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000064)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e50: sw v0,0x2c(s1) */ w32(ea(cpu(17),UINT32_C(0x0000002c)),(uint32_t)cpu(2));
/* 00172e54: jal 0x00175a88 */ set(31,0x00172e5cu);/* delay 00172e58 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000080)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e5c: sw v0,0x30(s1) */ w32(ea(cpu(17),UINT32_C(0x00000030)),(uint32_t)cpu(2));
/* 00172e60: jal 0x00175a88 */ set(31,0x00172e68u);/* delay 00172e64 */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x0000009c)))));set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));
/* 00172e68: sw v0,0x34(s1) */ w32(ea(cpu(17),UINT32_C(0x00000034)),(uint32_t)cpu(2));
/* 00172e6c: move v0,s1 */ set(2,cpu(17));
/* 00172e70: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
/* 00172e74: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
/* 00172e78: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
/* 00172e7c: ld ra,0x18(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000018))));
/* 00172e80: jr ra */ {uint64_t target=cpu(31);/* delay 00172e84 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(incoming,target);return cpu(2);}
}
uint64_t ps2BattleActionHitCreate26_00173668(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00173668u);
uint64_t incoming=cpu(31);
/* 00173668: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0017366c: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
/* 00173670: move s0,a0 */ set(16,cpu(4));
/* 00173674: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
/* 00173678: sd ra,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(31));
/* 0017367c: jal 0x002a8af8 */ set(31,0x00173684u);/* delay 00173680 */ set(4,sx(UINT32_C(0x0000000c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00173684: move s1,v0 */ set(17,cpu(2));
/* 00173688: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 0017368c: sw s0,0x0(s1) */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 00173690: move a2,s0 */ set(6,cpu(16));
/* 00173694: sw zero,0x4(s1) */ w32(ea(cpu(17),UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 00173698: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 0017369c: lw a0,-0x416c(v0) */ set(4,sx(r32(ea(cpu(2),UINT32_C(0xffffbe94)))));
/* 001736a0: jal 0x0016ac70 */ set(31,0x001736a8u);/* delay 001736a4 */ set(7,cpu(0));set(2,ps2BattleActionCutCreate_0016AC70(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 001736a8: sw v0,0x8(s1) */ w32(ea(cpu(17),UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001736ac: move v0,s1 */ set(2,cpu(17));
/* 001736b0: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
/* 001736b4: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
/* 001736b8: ld ra,0x10(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000010))));
/* 001736bc: jr ra */ {uint64_t target=cpu(31);/* delay 001736c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(incoming,target);return cpu(2);}
}
uint64_t ps2BattleActionHitCreate27_00173800(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00173800u);
uint64_t incoming=cpu(31);
/* 00173800: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00173804: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
/* 00173808: move s0,a0 */ set(16,cpu(4));
/* 0017380c: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
/* 00173810: sd ra,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(31));
/* 00173814: jal 0x002a8af8 */ set(31,0x0017381cu);/* delay 00173818 */ set(4,sx(UINT32_C(0x0000000c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0017381c: move s1,v0 */ set(17,cpu(2));
/* 00173820: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 00173824: sw s0,0x0(s1) */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 00173828: move a2,s0 */ set(6,cpu(16));
/* 0017382c: sw zero,0x4(s1) */ w32(ea(cpu(17),UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 00173830: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 00173834: lw a0,-0x414c(v0) */ set(4,sx(r32(ea(cpu(2),UINT32_C(0xffffbeb4)))));
/* 00173838: jal 0x0016ac70 */ set(31,0x00173840u);/* delay 0017383c */ set(7,cpu(0));set(2,ps2BattleActionCutCreate_0016AC70(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 00173840: sw v0,0x8(s1) */ w32(ea(cpu(17),UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 00173844: move v0,s1 */ set(2,cpu(17));
/* 00173848: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
/* 0017384c: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
/* 00173850: ld ra,0x10(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000010))));
/* 00173854: jr ra */ {uint64_t target=cpu(31);/* delay 00173858 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(incoming,target);return cpu(2);}
}
uint64_t ps2BattleActionHitCreate28_00173990(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00173990u);
uint64_t incoming=cpu(31);
/* 00173990: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00173994: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
/* 00173998: move s0,a0 */ set(16,cpu(4));
/* 0017399c: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
/* 001739a0: sd ra,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(31));
/* 001739a4: jal 0x002a8af8 */ set(31,0x001739acu);/* delay 001739a8 */ set(4,sx(UINT32_C(0x0000000c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 001739ac: move s1,v0 */ set(17,cpu(2));
/* 001739b0: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001739b4: sw s0,0x0(s1) */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 001739b8: move a2,s0 */ set(6,cpu(16));
/* 001739bc: sw zero,0x4(s1) */ w32(ea(cpu(17),UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001739c0: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 001739c4: lw a0,-0x412c(v0) */ set(4,sx(r32(ea(cpu(2),UINT32_C(0xffffbed4)))));
/* 001739c8: jal 0x0016ac70 */ set(31,0x001739d0u);/* delay 001739cc */ set(7,cpu(0));set(2,ps2BattleActionCutCreate_0016AC70(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 001739d0: sw v0,0x8(s1) */ w32(ea(cpu(17),UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001739d4: move v0,s1 */ set(2,cpu(17));
/* 001739d8: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
/* 001739dc: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
/* 001739e0: ld ra,0x10(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000010))));
/* 001739e4: jr ra */ {uint64_t target=cpu(31);/* delay 001739e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(incoming,target);return cpu(2);}
}
uint64_t ps2BattleActionHitCreate29_00173B20(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00173b20u);
uint64_t incoming=cpu(31);
/* 00173b20: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00173b24: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
/* 00173b28: move s0,a0 */ set(16,cpu(4));
/* 00173b2c: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
/* 00173b30: sd ra,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(31));
/* 00173b34: jal 0x002a8af8 */ set(31,0x00173b3cu);/* delay 00173b38 */ set(4,sx(UINT32_C(0x0000000c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00173b3c: move s1,v0 */ set(17,cpu(2));
/* 00173b40: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 00173b44: sw s0,0x0(s1) */ w32(ea(cpu(17),UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 00173b48: move a2,s0 */ set(6,cpu(16));
/* 00173b4c: sw zero,0x4(s1) */ w32(ea(cpu(17),UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 00173b50: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 00173b54: lw a0,-0x410c(v0) */ set(4,sx(r32(ea(cpu(2),UINT32_C(0xffffbef4)))));
/* 00173b58: jal 0x0016ac70 */ set(31,0x00173b60u);/* delay 00173b5c */ set(7,cpu(0));set(2,ps2BattleActionCutCreate_0016AC70(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 00173b60: sw v0,0x8(s1) */ w32(ea(cpu(17),UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 00173b64: move v0,s1 */ set(2,cpu(17));
/* 00173b68: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
/* 00173b6c: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
/* 00173b70: ld ra,0x10(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000010))));
/* 00173b74: jr ra */ {uint64_t target=cpu(31);/* delay 00173b78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(incoming,target);return cpu(2);}
}
