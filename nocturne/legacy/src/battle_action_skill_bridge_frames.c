/* Whole sixteen SKILL bridge variants; twelve registered, four recognized pending; no new identities.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_bridge_frames.h"
#include "battle_action_skill_kernel.h"
#include "battle_action_consumer.h"
#include "battle_action_formula_frames.h"
#include "effect_host_bindings.h"
#include "pcp_effect_helpers.h"
#include "magatuhi_helpers.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "compiler_numeric.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#pragma warning(disable:4102)
#endif
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneEffectHostHi(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}


static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
/* Genuine EE word division is defined even before a late native BREAK.
 * Primary and secondary banks are distinct; use the existing Formula bank
 * for cross-unit secondary state rather than a private or primary substitute.
 */



static void body_002a81b0(void);
static void body_002a8d18(void);
static void body_002a95f8(void);
static void body_002a96c0(void);
static void body_002d17f0(void);
static void body_002d1b88(void);
static void body_002d1c40(void);
static void body_001cf100(void);
static void body_00257c80(void);
static void body_002aa888(void);
static void body_002a9aa8(void);
static void body_002a9b38(void);
static void body_002a9b80(void);
static void body_002ac760(void);
static void body_002a8080(void);
static void body_002dbea0(void);
static void body_002a81b0(void){
nocturneEffectAxisNoteEntry(0x002a81b0u);
uint64_t incoming=cpu(31);
/* 002a81b0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a81b4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a81b8: move s0,a0 */ set(16,cpu(4));
/* 002a81bc: beq s0,zero,0x002a81f0 */ {int taken=(cpu(16)==cpu(0));/* delay 002a81c0 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002a81f0;}}
/* 002a81c4: jal 0x002a8d18 */ set(31,0x002a81ccu);/* delay 002a81c8 */ body_002a8d18();
/* 002a81cc: beq v0,zero,0x002a81e8 */ {int taken=(cpu(2)==cpu(0));/* delay 002a81d0 */ set(4,cpu(16));if(taken){goto L_002a81e8;}}
/* 002a81d4: jal 0x002a8bd8 */ set(31,0x002a81dcu);/* delay 002a81d8 */ nocturneBattleActionSkillCall(0x002a8bd8u);
/* 002a81dc: b 0x002a81f4 */ /* delay 002a81e0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002a81f4;
L_002a81e8:;
/* 002a81e8: jal 0x002a95f8 */ set(31,0x002a81f0u);/* delay 002a81ec */ set(4,cpu(16));body_002a95f8();
L_002a81f0:;
/* 002a81f0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002a81f4:;
/* 002a81f4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a81f8: jr ra */ {uint64_t target=cpu(31);/* delay 002a81fc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002a8d18(void){
nocturneEffectAxisNoteEntry(0x002a8d18u);
uint64_t incoming=cpu(31);
/* 002a8d18: lw v0,-0x2110(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdef0)));
/* 002a8d1c: slt v0,a0,v0 */ set(2,(int64_t)cpu(4)<(int64_t)cpu(2));
/* 002a8d20: bne v0,zero,0x002a8d30 */ {int taken=(cpu(2)!=cpu(0));/* delay 002a8d24 */ set(3,cpu(0));if(taken){goto L_002a8d30;}}
/* 002a8d28: lw v0,-0x210c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdef4)));
/* 002a8d2c: slt v1,a0,v0 */ set(3,(int64_t)cpu(4)<(int64_t)cpu(2));
L_002a8d30:;
/* 002a8d30: jr ra */ {uint64_t target=cpu(31);/* delay 002a8d34 */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
static void body_002a95f8(void){
nocturneEffectAxisNoteEntry(0x002a95f8u);
uint64_t incoming=cpu(31);
/* 002a95f8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a95fc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9600: jal 0x002a96c0 */ set(31,0x002a9608u);/* delay 002a9604 */ body_002a96c0();
/* 002a9608: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a960c: move a0,v0 */ set(4,cpu(2));
/* 002a9610: j 0x002a9558 */ /* delay 002a9614 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002a9558u);return;
}
static void body_002a96c0(void){
nocturneEffectAxisNoteEntry(0x002a96c0u);
uint64_t incoming=cpu(31);
/* 002a96c0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002a96c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a96c8: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 002a96cc: addiu s0,s0,0x7f18 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00007f18)));
/* 002a96d0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a96d4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a96d8: move s2,a0 */ set(18,cpu(4));
/* 002a96dc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a96e0: li s3,0x2 */ set(19,sx(UINT32_C(0x00000002)));
/* 002a96e4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a96e8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002a96ec: jal 0x002e4070 */ set(31,0x002a96f4u);/* delay 002a96f0 */ set(20,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002e4070u);
/* 002a96f4: lw s0,0x4(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002a96f8: move s1,v0 */ set(17,cpu(2));
/* 002a96fc: nop  */ 
L_002a9700:;
/* 002a9700: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002a9704: beql v0,s4,0x002a9750 */ {int taken=(cpu(2)==cpu(20));if(taken){/* delay 002a9708 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_002a9750;}}
/* 002a970c: nop  */ 
/* 002a9710: nop  */ 
/* 002a9714: nop  */ 
/* 002a9718: nop  */ 
/* 002a971c: bnel v0,s3,0x002a9700 */ {int taken=(cpu(2)!=cpu(19));if(taken){/* delay 002a9720 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a9700;}}
/* 002a9724: nop  */ 
/* 002a9728: nop  */ 
/* 002a972c: nop  */ 
/* 002a9730: nop  */ 
/* 002a9734: beql s1,zero,0x002a9700 */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 002a9738 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a9700;}}
/* 002a973c: jal 0x002e40b8 */ set(31,0x002a9744u);/* delay 002a9740 */ nocturneBattleActionSkillCall(0x002e40b8u);
/* 002a9744: b 0x002a9700 */ /* delay 002a9748 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a9700;
L_002a9750:;
/* 002a9750: bnel v0,s2,0x002a9700 */ {int taken=(cpu(2)!=cpu(18));if(taken){/* delay 002a9754 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a9700;}}
/* 002a9758: beql s1,zero,0x002a976c */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 002a975c */ set(2,cpu(16));goto L_002a976c;}}
/* 002a9760: jal 0x002e40b8 */ set(31,0x002a9768u);/* delay 002a9764 */ nocturneBattleActionSkillCall(0x002e40b8u);
/* 002a9768: move v0,s0 */ set(2,cpu(16));
L_002a976c:;
/* 002a976c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9770: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9774: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a9778: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a977c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a9780: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002a9784: jr ra */ {uint64_t target=cpu(31);/* delay 002a9788 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002d17f0(void){
nocturneEffectAxisNoteEntry(0x002d17f0u);
uint64_t incoming=cpu(31);
/* 002d17f0: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
/* 002d17f4: sd a0,0x60(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d17f8: addiu a0,sp,0x60 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 002d17fc: sd a1,0x68(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002d1800: sd s0,0x70(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d1804: sd ra,0x78(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d1808: jal 0x002d3578 */ set(31,0x002d1810u);/* delay 002d180c */ set(5,cpu(29));nocturneBattleActionSkillCall(0x002d3578u);
/* 002d1810: addiu s0,sp,0x20 */ set(16,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d1814: addiu a0,sp,0x68 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000068)));
/* 002d1818: jal 0x002d3578 */ set(31,0x002d1820u);/* delay 002d181c */ set(5,cpu(16));nocturneBattleActionSkillCall(0x002d3578u);
/* 002d1820: move a1,s0 */ set(5,cpu(16));
/* 002d1824: move a0,sp */ set(4,cpu(29));
/* 002d1828: jal 0x002d1590 */ set(31,0x002d1830u);/* delay 002d182c */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));nocturneBattleActionSkillCall(0x002d1590u);
/* 002d1830: jal 0x002d34a0 */ set(31,0x002d1838u);/* delay 002d1834 */ set(4,cpu(2));nocturneBattleActionSkillCall(0x002d34a0u);
/* 002d1838: ld s0,0x70(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d183c: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d1840: jr ra */ {uint64_t target=cpu(31);/* delay 002d1844 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));checkReturn(target,incoming);return;}
}
static void body_002d1b88(void){
nocturneEffectAxisNoteEntry(0x002d1b88u);
uint64_t incoming=cpu(31);
/* 002d1b88: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002d1b8c: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002d1b90: srl v1,a0,0x1f */ set(3,sx((uint32_t)cpu(4)>>31));
/* 002d1b94: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d1b98: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d1b9c: bne a0,zero,0x002d1bb0 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d1ba0 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));if(taken){goto L_002d1bb0;}}
/* 002d1ba4: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002d1ba8: b 0x002d1c2c */ /* delay 002d1bac */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_002d1c2c;
L_002d1bb0:;
/* 002d1bb0: li v0,0x3c */ set(2,sx(UINT32_C(0x0000003c)));
/* 002d1bb4: beq v1,zero,0x002d1be0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d1bb8 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002d1be0;}}
/* 002d1bbc: lui v1,0x8000 */ set(3,sx(UINT32_C(0x80000000)));
/* 002d1bc0: ori v0,zero,0xc1e0 */ set(2,cpu(0)|UINT32_C(0x0000c1e0));
/* 002d1bc4: dsll32 v0,v0,0x10 */ set(2,cpu(2)<<48);
/* 002d1bc8: beq a0,v1,0x002d1c38 */ {int taken=(cpu(4)==cpu(3));/* delay 002d1bcc */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002d1c38;}}
/* 002d1bd0: subu v0,zero,a0 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
/* 002d1bd4: b 0x002d1be4 */ /* delay 002d1bd8 */ save(2,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_002d1be4;
L_002d1be0:;
/* 002d1be0: sd a0,0x10(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000010)));
L_002d1be4:;
/* 002d1be4: ld a0,0x10(sp) */ restore(4,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d1be8: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d1bec: dsrl v0,v0,0x4 */ set(2,cpu(2)>>4);
/* 002d1bf0: sltu v0,v0,a0 */ set(2,cpu(2)<cpu(4));
/* 002d1bf4: bne v0,zero,0x002d1c2c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d1bf8 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002d1c2c;}}
/* 002d1bfc: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 002d1c00: dsrl a2,a2,0x4 */ set(6,cpu(6)>>4);
/* 002d1c04: nop  */ 
L_002d1c08:;
/* 002d1c08: dsll v1,a0,0x1 */ set(3,cpu(4)<<1);
/* 002d1c0c: addiu a1,a1,-0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 002d1c10: sltu v0,a2,v1 */ set(2,cpu(6)<cpu(3));
/* 002d1c14: nop  */ 
/* 002d1c18: nop  */ 
/* 002d1c1c: beq v0,zero,0x002d1c08 */ {int taken=(cpu(2)==cpu(0));/* delay 002d1c20 */ set(4,cpu(3));if(taken){goto L_002d1c08;}}
/* 002d1c24: sw a1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 002d1c28: sd v1,0x10(sp) */ save(3,ea(29,(int32_t)UINT32_C(0x00000010)));
L_002d1c2c:;
/* 002d1c2c: jal 0x002d34a0 */ set(31,0x002d1c34u);/* delay 002d1c30 */ set(4,cpu(29));nocturneBattleActionSkillCall(0x002d34a0u);
/* 002d1c34: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
L_002d1c38:;
/* 002d1c38: jr ra */ {uint64_t target=cpu(31);/* delay 002d1c3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002d1c40(void){
nocturneEffectAxisNoteEntry(0x002d1c40u);
uint64_t incoming=cpu(31);
/* 002d1c40: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002d1c44: sd a0,0x20(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d1c48: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d1c4c: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d1c50: jal 0x002d3578 */ set(31,0x002d1c58u);/* delay 002d1c54 */ set(5,cpu(29));nocturneBattleActionSkillCall(0x002d3578u);
/* 002d1c58: move v0,zero */ set(2,cpu(0));
/* 002d1c5c: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d1c60: xori v1,a0,0x2 */ set(3,cpu(4)^UINT32_C(0x00000002));
/* 002d1c64: beq v1,zero,0x002d1cd0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d1c68 */ set(5,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_002d1cd0;}}
/* 002d1c6c: bne a1,zero,0x002d1cd4 */ {int taken=(cpu(5)!=cpu(0));/* delay 002d1c70 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_002d1cd4;}}
/* 002d1c74: xori v0,a0,0x4 */ set(2,cpu(4)^UINT32_C(0x00000004));
/* 002d1c78: beq v0,zero,0x002d1c9c */ {int taken=(cpu(2)==cpu(0));/* delay 002d1c7c */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_002d1c9c;}}
/* 002d1c80: lw a1,0x8(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d1c84: move v0,zero */ set(2,cpu(0));
/* 002d1c88: bltz a1,0x002d1cd4 */ {int taken=((int64_t)cpu(5)<0);/* delay 002d1c8c */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000001f));if(taken){goto L_002d1cd4;}}
/* 002d1c90: bne v1,zero,0x002d1cb0 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d1c94 */ set(3,sx(UINT32_C(0x0000003c)));if(taken){goto L_002d1cb0;}}
/* 002d1c98: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
L_002d1c9c:;
/* 002d1c9c: lui v0,0x7fff */ set(2,sx(UINT32_C(0x7fff0000)));
/* 002d1ca0: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002d1ca4: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d1ca8: b 0x002d1cd0 */ /* delay 002d1cac */ if(cpu(3)!=0){set(2,cpu(4));}goto L_002d1cd0;
L_002d1cb0:;
/* 002d1cb0: ld v0,0x10(sp) */ restore(2,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d1cb4: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
/* 002d1cb8: lw a0,0x4(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002d1cbc: dsrlv v0,v0,v1 */ set(2,cpu(2)>>((unsigned)cpu(3)&63u));
/* 002d1cc0: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d1cc4: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d1cc8: subu v1,zero,v0 */ set(3,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));
/* 002d1ccc: movn v0,v1,a0 */ if(cpu(4)!=0){set(2,cpu(3));}
L_002d1cd0:;
/* 002d1cd0: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
L_002d1cd4:;
/* 002d1cd4: jr ra */ {uint64_t target=cpu(31);/* delay 002d1cd8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001cf100(void){
nocturneEffectAxisNoteEntry(0x001cf100u);
uint64_t incoming=cpu(31);
/* 001cf100: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001cf104: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf108: move s0,a0 */ set(16,cpu(4));
/* 001cf10c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf110: addiu a0,s0,0x20 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
/* 001cf114: lbu v0,0x1c(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x0000001c))));
/* 001cf118: bne v0,zero,0x001cf138 */ {int taken=(cpu(2)!=cpu(0));/* delay 001cf11c */ set(5,cpu(4));if(taken){goto L_001cf138;}}
/* 001cf120: lw a2,0x10(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 001cf124: lw a3,0x14(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001cf128: jal 0x002c39c8 */ set(31,0x001cf130u);/* delay 001cf12c */ set(6,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));nocturneBattleActionSkillCall(0x002c39c8u);
/* 001cf130: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001cf134: sb v0,0x1c(s0) */ sb(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(2));
L_001cf138:;
/* 001cf138: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf13c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf140: jr ra */ {uint64_t target=cpu(31);/* delay 001cf144 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00257c80(void){
nocturneEffectAxisNoteEntry(0x00257c80u);
uint64_t incoming=cpu(31);
/* 00257c80: move v1,a0 */ set(3,cpu(4));
/* 00257c84: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00257c88: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00257c8c: sb a1,0x8(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000008)),(uint8_t)cpu(5));
/* 00257c90: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 00257c94: sb zero,0x9(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000009)),(uint8_t)cpu(0));
/* 00257c98: sra a1,a1,0x15 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>21)));
/* 00257c9c: sw zero,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 00257ca0: sh zero,0xa(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(0));
/* 00257ca4: lui v0,0x40 */ set(2,sx(UINT32_C(0x00400000)));
/* 00257ca8: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 00257cac: lw v0,-0x5840(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffffa7c0)));
/* 00257cb0: jalr v0 */ {uint64_t target=cpu(2);set(31,0x00257cb8u);/* delay 00257cb4 */ nocturneBattleActionSkillCall((uint32_t)target);}
/* 00257cb8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00257cbc: jr ra */ {uint64_t target=cpu(31);/* delay 00257cc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002aa888(void){
nocturneEffectAxisNoteEntry(0x002aa888u);
uint64_t incoming=cpu(31);
/* 002aa888: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002aa88c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa890: jal 0x002a8af8 */ set(31,0x002aa898u);/* delay 002aa894 */ set(4,sx(UINT32_C(0x0000001c)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 002aa898: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa89c: lui a1,0x2b */ set(5,sx(UINT32_C(0x002b0000)));
/* 002aa8a0: lui v1,0x10 */ set(3,sx(UINT32_C(0x00100000)));
/* 002aa8a4: addiu a1,a1,-0x5810 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffa7f0)));
/* 002aa8a8: addiu a0,gp,-0x20d8 */ set(4,sx((uint32_t)cpu(28)+UINT32_C(0xffffdf28)));
/* 002aa8ac: sw v1,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 002aa8b0: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002aa8b4: sw zero,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002aa8b8: sw zero,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002aa8bc: sw zero,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002aa8c0: sw v0,-0x20dc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdf24)),(uint32_t)cpu(2));
/* 002aa8c4: sw v0,-0x20e0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdf20)),(uint32_t)cpu(2));
/* 002aa8c8: j 0x002ac760 */ /* delay 002aa8cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002ac760();return;
}
static void body_002a9aa8(void){
nocturneEffectAxisNoteEntry(0x002a9aa8u);
uint64_t incoming=cpu(31);
/* 002a9aa8: sll v0,a1,0x1 */ set(2,sx((uint32_t)cpu(5)<<1));
/* 002a9aac: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002a9ab0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002a9ab4: lui at,0x53 */ set(1,sx(UINT32_C(0x00530000)));
/* 002a9ab8: addiu at,at,-0x6ca8 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffff9358)));
/* 002a9abc: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 002a9ac0: beq a2,zero,0x002a9ad4 */ {int taken=(cpu(6)==cpu(0));/* delay 002a9ac4 */ set(10,cpu(4));if(taken){goto L_002a9ad4;}}
/* 002a9ac8: sw zero,0x8(t2) */ sw(ea(10,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002a9acc: sw zero,0xc(t2) */ sw(ea(10,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002a9ad0: sw zero,0x10(t2) */ sw(ea(10,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
L_002a9ad4:;
/* 002a9ad4: lhu t1,0x8(v0) */ set(9,half(ea(2,(int32_t)UINT32_C(0x00000008))));
/* 002a9ad8: lh v1,0x0(v0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002a9adc: lh a0,0x2(v0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 002a9ae0: lh a1,0x4(v0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 002a9ae4: lhu a2,0x6(v0) */ set(6,half(ea(2,(int32_t)UINT32_C(0x00000006))));
/* 002a9ae8: sh v1,0x0(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002a9aec: sh a0,0x2(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(4));
/* 002a9af0: sh a1,0x4(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(5));
/* 002a9af4: sb a2,0x6(t2) */ sb(ea(10,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(6));
/* 002a9af8: jr ra */ {uint64_t target=cpu(31);/* delay 002a9afc */ sb(ea(10,(int32_t)UINT32_C(0x00000007)),(uint8_t)cpu(9));checkReturn(target,incoming);return;}
}
static void body_002a9b38(void){
nocturneEffectAxisNoteEntry(0x002a9b38u);
uint64_t incoming=cpu(31);
/* 002a9b38: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a9b3c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9b40: move s0,a0 */ set(16,cpu(4));
/* 002a9b44: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9b48: jal 0x002aa7f0 */ set(31,0x002a9b50u);/* delay 002a9b4c */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));nocturneBattleActionSkillCall(0x002aa7f0u);
/* 002a9b50: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002a9b54: jal 0x002aa7f0 */ set(31,0x002a9b5cu);/* delay 002a9b58 */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));nocturneBattleActionSkillCall(0x002aa7f0u);
/* 002a9b5c: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002a9b60: jal 0x002aa7f0 */ set(31,0x002a9b68u);/* delay 002a9b64 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));nocturneBattleActionSkillCall(0x002aa7f0u);
/* 002a9b68: sw zero,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002a9b6c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9b70: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9b74: jr ra */ {uint64_t target=cpu(31);/* delay 002a9b78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002a9b80(void){
nocturneEffectAxisNoteEntry(0x002a9b80u);
uint64_t incoming=cpu(31);
/* 002a9b80: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002a9b84: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9b88: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9b8c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a9b90: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a9b94: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a9b98: jal 0x002a9b38 */ set(31,0x002a9ba0u);/* delay 002a9b9c */ set(16,cpu(4));body_002a9b38();
/* 002a9ba0: lh s1,0x0(s0) */ set(17,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002a9ba4: lh s2,0x4(s0) */ set(18,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000004))));
/* 002a9ba8: lbu a2,0x7(s0) */ set(6,byte(ea(16,(int32_t)UINT32_C(0x00000007))));
/* 002a9bac: move a0,s1 */ set(4,cpu(17));
/* 002a9bb0: jal 0x002aa8d0 */ set(31,0x002a9bb8u);/* delay 002a9bb4 */ set(5,cpu(18));nocturneBattleActionSkillCall(0x002aa8d0u);
/* 002a9bb8: lbu s3,0x6(s0) */ set(19,byte(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 002a9bbc: sw v0,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002a9bc0: move a0,s1 */ set(4,cpu(17));
/* 002a9bc4: move a1,s2 */ set(5,cpu(18));
/* 002a9bc8: jal 0x002aa8d0 */ set(31,0x002a9bd0u);/* delay 002a9bcc */ set(6,cpu(19));nocturneBattleActionSkillCall(0x002aa8d0u);
/* 002a9bd0: move a0,s1 */ set(4,cpu(17));
/* 002a9bd4: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002a9bd8: move a1,s2 */ set(5,cpu(18));
/* 002a9bdc: jal 0x002aa8d0 */ set(31,0x002a9be4u);/* delay 002a9be0 */ set(6,cpu(19));nocturneBattleActionSkillCall(0x002aa8d0u);
/* 002a9be4: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002a9be8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9bec: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9bf0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a9bf4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a9bf8: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a9bfc: jr ra */ {uint64_t target=cpu(31);/* delay 002a9c00 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002ac760(void){
nocturneEffectAxisNoteEntry(0x002ac760u);
uint64_t incoming=cpu(31);
/* 002ac760: lw v0,-0x290c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6f4)));
/* 002ac764: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002ac768: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac76c: move s0,a0 */ set(16,cpu(4));
/* 002ac770: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac774: move s1,a1 */ set(17,cpu(5));
/* 002ac778: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac77c: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002ac780: bgez v0,0x002ac794 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002ac784 */ set(5,sx(UINT32_C(0x0000007f)));if(taken){goto L_002ac794;}}
/* 002ac788: jal 0x002a8080 */ set(31,0x002ac790u);/* delay 002ac78c */ set(6,cpu(0));body_002a8080();
/* 002ac790: sw v0,-0x290c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd6f4)),(uint32_t)cpu(2));
L_002ac794:;
/* 002ac794: sw s1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002ac798: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002ac79c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac7a0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac7a4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac7a8: jr ra */ {uint64_t target=cpu(31);/* delay 002ac7ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002a8080(void){
nocturneEffectAxisNoteEntry(0x002a8080u);
uint64_t incoming=cpu(31);
/* 002a8080: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002a8084: sw a0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 002a8088: move a0,sp */ set(4,cpu(29));
/* 002a808c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a8090: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 002a8094: jal 0x002dbea0 */ set(31,0x002a809cu);/* delay 002a8098 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(6));body_002dbea0();
/* 002a809c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a80a0: jr ra */ {uint64_t target=cpu(31);/* delay 002a80a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002dbea0(void){
nocturneEffectAxisNoteEntry(0x002dbea0u);
uint64_t incoming=cpu(31);
/* 002dbea0: li v1,0x40 */ set(3,sx(UINT32_C(0x00000040)));
/* 002dbea4: syscall 0x0 */ {const uint64_t arguments[1]={cpu(4)};set(2,nocturneBattleActionSkillKernelValue(cpu(3),0x002dbea4u,1u,arguments));}
/* 002dbea8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbeac */ checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleActionSkillBridgeBody(uint32_t entry){switch(entry){
case 0x002a81b0u:body_002a81b0();return 1u;
case 0x002a8d18u:body_002a8d18();return 1u;
case 0x002a95f8u:body_002a95f8();return 1u;
case 0x002a96c0u:body_002a96c0();return 1u;
case 0x002d17f0u:body_002d17f0();return 1u;
case 0x002d1b88u:body_002d1b88();return 1u;
case 0x002d1c40u:body_002d1c40();return 1u;
case 0x001cf100u:body_001cf100();return 1u;
case 0x00257c80u:body_00257c80();return 1u;
case 0x002aa888u:body_002aa888();return 1u;
case 0x002a9aa8u:body_002a9aa8();return 1u;
case 0x002a9b38u:body_002a9b38();return 1u;
case 0x002a9b80u:body_002a9b80();return 1u;
case 0x002ac760u:body_002ac760();return 1u;
case 0x002a8080u:body_002a8080();return 1u;
case 0x002dbea0u:body_002dbea0();return 1u;
default:return 0u;}}
