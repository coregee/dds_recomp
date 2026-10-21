/* Whole three original SDK file/SIF RPC/command initialization algorithms.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_sif_startup_frames.h"
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


static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}


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



#include "ee_vu_rotation.h"
/* Each partial-word instruction performs its own original merge/store.
 * Preserve upper128 CPU lanes. LWL always sign-extends; EE LWR preserves
 * bits63:32 except at aligned offset0, where it sign-extends the full word.
 */
static void loadPartial32(unsigned r,uint32_t a,int left){uint8_t d[4],s[4];uint64_t old=cpu(r);uint32_t value=(uint32_t)old;memcpy(d,&value,4);memcpy(s,at(a&~3u),4);unsigned o=a&3u;if(left){for(unsigned i=0;i<=o;i++)d[3u-o+i]=s[i];}else{for(unsigned i=o;i<4;i++)d[i-o]=s[i];}memcpy(&value,d,4);set(r,left||!o?sx(value):(old&UINT64_C(0xffffffff00000000))|value);}
static void storePartial32(uint32_t a,unsigned r,int left){uint8_t s[4];uint32_t value=(uint32_t)cpu(r);memcpy(s,&value,4);uint8_t *d=at(a&~3u);unsigned o=a&3u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[3u-o+i];}else{for(unsigned i=o;i<4;i++)d[i]=s[i-o];}}

static void body_002dfad8(void);
static void body_002de508(void);
static void body_002dde38(void);
static void body_002dfad8(void){
nocturneEffectAxisNoteEntry(0x002dfad8u);
uint64_t incoming=cpu(31);
/* 002dfad8: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 002dfadc: move a0,zero */ set(4,cpu(0));
/* 002dfae0: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dfae4: lui s0,0x5a */ set(16,sx(UINT32_C(0x005a0000)));
/* 002dfae8: sd s1,0x20(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dfaec: sd ra,0x60(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002dfaf0: addiu s1,s0,-0x1800 */ set(17,sx((uint32_t)cpu(16)+UINT32_C(0xffffe800)));
/* 002dfaf4: sd s4,0x50(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002dfaf8: sd s3,0x40(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002dfafc: jal 0x002de508 */ set(31,0x002dfb04u);/* delay 002dfb00 */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));body_002de508();
/* 002dfb04: sw zero,-0x1800(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffe800)),(uint32_t)cpu(0));
/* 002dfb08: jal 0x002e4070 */ set(31,0x002dfb10u);/* delay 002dfb0c */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));nocturneBattleActionSkillCall(0x002e4070u);
/* 002dfb10: lui a1,0x2e */ set(5,sx(UINT32_C(0x002e0000)));
/* 002dfb14: lui a2,0x5a */ set(6,sx(UINT32_C(0x005a0000)));
/* 002dfb18: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002dfb1c: move s0,v0 */ set(16,cpu(2));
/* 002dfb20: addiu a1,a1,-0xa40 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xfffff5c0)));
/* 002dfb24: addiu a2,a2,-0x1840 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffe7c0)));
/* 002dfb28: jal 0x002de120 */ set(31,0x002dfb30u);/* delay 002dfb2c */ set(4,cpu(4)|UINT32_C(0x00000011));nocturneBattleActionSkillCall(0x002de120u);
/* 002dfb30: lui a1,0x2e */ set(5,sx(UINT32_C(0x002e0000)));
/* 002dfb34: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002dfb38: addiu a1,a1,-0x558 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xfffffaa8)));
/* 002dfb3c: move a2,s1 */ set(6,cpu(17));
/* 002dfb40: jal 0x002de120 */ set(31,0x002dfb48u);/* delay 002dfb44 */ set(4,cpu(4)|UINT32_C(0x00000013));nocturneBattleActionSkillCall(0x002de120u);
/* 002dfb48: beq s0,zero,0x002dfb84 */ {int taken=(cpu(16)==cpu(0));/* delay 002dfb4c */ set(19,sx(UINT32_C(0x005a0000)));if(taken){goto L_002dfb84;}}
/* 002dfb50: jal 0x002e40b8 */ set(31,0x002dfb58u);/* delay 002dfb54 */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0xffffe780)));nocturneBattleActionSkillCall(0x002e40b8u);
/* 002dfb58: b 0x002dfb88 */ /* delay 002dfb5c */ goto L_002dfb88;
L_002dfb60:;
/* 002dfb60: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002dfb64: nop  */ 
L_002dfb68:;
/* 002dfb68: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002dfb6c: nop  */ 
/* 002dfb70: nop  */ 
/* 002dfb74: nop  */ 
/* 002dfb78: nop  */ 
/* 002dfb7c: bne v0,v1,0x002dfb68 */ {int taken=(cpu(2)!=cpu(3));/* delay 002dfb80 */ if(taken){goto L_002dfb68;}}
L_002dfb84:;
/* 002dfb84: addiu s0,s3,-0x1880 */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0xffffe780)));
L_002dfb88:;
/* 002dfb88: lui a1,0x8000 */ set(5,sx(UINT32_C(0x80000000)));
/* 002dfb8c: move a0,s0 */ set(4,cpu(16));
/* 002dfb90: ori a1,a1,0x1 */ set(5,cpu(5)|UINT32_C(0x00000001));
/* 002dfb94: jal 0x002deb78 */ set(31,0x002dfb9cu);/* delay 002dfb98 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x002deb78u);
/* 002dfb9c: bltz v0,0x002dfc88 */ {int taken=((int64_t)cpu(2)<0);/* delay 002dfba0 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002dfc88;}}
/* 002dfba4: lw v0,0x24(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000024)));
/* 002dfba8: beq v0,zero,0x002dfb60 */ {int taken=(cpu(2)==cpu(0));/* delay 002dfbac */ set(2,sx(UINT32_C(0x00100000)));if(taken){goto L_002dfb60;}}
/* 002dfbb0: jal 0x002df468 */ set(31,0x002dfbb8u);/* delay 002dfbb4 */ set(20,sx(UINT32_C(0x00530000)));nocturneBattleActionSkillCall(0x002df468u);
/* 002dfbb8: jal 0x002dbee0 */ set(31,0x002dfbc0u);/* delay 002dfbbc */ lw(4,ea(20,(int32_t)UINT32_C(0xffffc348)));nocturneBattleActionSkillCall(0x002dbee0u);
/* 002dfbc0: lui v1,0x5a */ set(3,sx(UINT32_C(0x005a0000)));
/* 002dfbc4: addiu v1,v1,-0x1a80 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffe580)));
/* 002dfbc8: addiu a0,v1,0x200 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000200)));
/* 002dfbcc: sltu v0,v1,a0 */ set(2,cpu(3)<cpu(4));
/* 002dfbd0: beq v0,zero,0x002dfc04 */ {int taken=(cpu(2)==cpu(0));/* delay 002dfbd4 */ set(18,sx(UINT32_C(0x005a0000)));if(taken){goto L_002dfc04;}}
/* 002dfbd8: lui s1,0x5a */ set(17,sx(UINT32_C(0x005a0000)));
/* 002dfbdc: lui s0,0x5a */ set(16,sx(UINT32_C(0x005a0000)));
L_002dfbe0:;
/* 002dfbe0: sw zero,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002dfbe4: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002dfbe8: sltu v0,v1,a0 */ set(2,cpu(3)<cpu(4));
/* 002dfbec: nop  */ 
/* 002dfbf0: nop  */ 
/* 002dfbf4: bne v0,zero,0x002dfbe0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002dfbf8 */ if(taken){goto L_002dfbe0;}}
/* 002dfbfc: b 0x002dfc10 */ /* delay 002dfc00 */ lw(4,ea(20,(int32_t)UINT32_C(0xffffc348)));goto L_002dfc10;
L_002dfc04:;
/* 002dfc04: lui s1,0x5a */ set(17,sx(UINT32_C(0x005a0000)));
/* 002dfc08: lui s0,0x5a */ set(16,sx(UINT32_C(0x005a0000)));
/* 002dfc0c: lw a0,-0x3cb8(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0xffffc348)));
L_002dfc10:;
/* 002dfc10: jal 0x002dbec0 */ set(31,0x002dfc18u);/* delay 002dfc14 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffe100)));nocturneBattleActionSkillCall(0x002dbec0u);
/* 002dfc18: addiu v1,s1,-0x1ec0 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0xffffe140)));
/* 002dfc1c: addiu a0,s3,-0x1880 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffe780)));
/* 002dfc20: sw v1,-0x2b80(s2) */ sw(ea(18,(int32_t)UINT32_C(0xffffd480)),(uint32_t)cpu(3));
/* 002dfc24: addiu a3,s2,-0x2b80 */ set(7,sx((uint32_t)cpu(18)+UINT32_C(0xffffd480)));
/* 002dfc28: sw zero,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002dfc2c: li a1,0xff */ set(5,sx(UINT32_C(0x000000ff)));
/* 002dfc30: move a2,zero */ set(6,cpu(0));
/* 002dfc34: li t0,0x4 */ set(8,sx(UINT32_C(0x00000004)));
/* 002dfc38: move t1,s0 */ set(9,cpu(16));
/* 002dfc3c: li t2,0x4 */ set(10,sx(UINT32_C(0x00000004)));
/* 002dfc40: jal 0x002ded48 */ set(31,0x002dfc48u);/* delay 002dfc44 */ set(11,cpu(0));nocturneBattleActionSkillCall(0x002ded48u);
/* 002dfc48: bgezl v0,0x002dfc5c */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 002dfc4c */ set(2,sx(UINT32_C(0x20000000)));goto L_002dfc5c;}}
/* 002dfc50: lui v0,0xfffe */ set(2,sx(UINT32_C(0xfffe0000)));
/* 002dfc54: b 0x002dfc88 */ /* delay 002dfc58 */ set(2,cpu(2)|UINT32_C(0x0000ffff));goto L_002dfc88;
L_002dfc5c:;
/* 002dfc5c: lui a1,0x5a */ set(5,sx(UINT32_C(0x005a0000)));
/* 002dfc60: or v0,s0,v0 */ set(2,cpu(16)|cpu(2));
/* 002dfc64: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 002dfc68: addiu t1,a1,-0x1858 */ set(9,sx((uint32_t)cpu(5)+UINT32_C(0xffffe7a8)));
/* 002dfc6c: lwl a2,0x3(v0) */ loadPartial32(6,ea(2,(int32_t)UINT32_C(0x00000003)),1);
/* 002dfc70: lwr a2,0x0(v0) */ loadPartial32(6,ea(2,(int32_t)UINT32_C(0x00000000)),0);
/* 002dfc74: swl a2,0x3(t1) */ storePartial32(ea(9,(int32_t)UINT32_C(0x00000003)),6,1);
/* 002dfc78: swr a2,0x0(t1) */ storePartial32(ea(9,(int32_t)UINT32_C(0x00000000)),6,0);
/* 002dfc7c: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002dfc80: sw v1,-0x3cc0(a0) */ sw(ea(4,(int32_t)UINT32_C(0xffffc340)),(uint32_t)cpu(3));
/* 002dfc84: move v0,zero */ set(2,cpu(0));
L_002dfc88:;
/* 002dfc88: ld ra,0x60(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002dfc8c: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002dfc90: ld s3,0x40(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002dfc94: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dfc98: ld s1,0x20(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dfc9c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dfca0: jr ra */ {uint64_t target=cpu(31);/* delay 002dfca4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
static void body_002de508(void){
nocturneEffectAxisNoteEntry(0x002de508u);
uint64_t incoming=cpu(31);
/* 002de508: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002de50c: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002de510: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de514: sd s1,0x10(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002de518: jal 0x002e4070 */ set(31,0x002de520u);/* delay 002de51c */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));nocturneBattleActionSkillCall(0x002e4070u);
/* 002de520: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002de524: lw v0,-0x3d44(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0xffffc2bc)));
/* 002de528: beq v0,zero,0x002de548 */ {int taken=(cpu(2)==cpu(0));/* delay 002de52c */ set(17,sx(UINT32_C(0x00000001)));if(taken){goto L_002de548;}}
/* 002de530: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002de534: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de538: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002de53c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de540: j 0x002e40b8 */ /* delay 002de544 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002e40b8u);return;
L_002de548:;
/* 002de548: jal 0x002e40b8 */ set(31,0x002de550u);/* delay 002de54c */ sw(ea(3,(int32_t)UINT32_C(0xffffc2bc)),(uint32_t)cpu(17));nocturneBattleActionSkillCall(0x002e40b8u);
/* 002de550: jal 0x002dde38 */ set(31,0x002de558u);/* delay 002de554 */ body_002dde38();
/* 002de558: jal 0x002e4070 */ set(31,0x002de560u);/* delay 002de55c */ nocturneBattleActionSkillCall(0x002e4070u);
/* 002de560: lui v1,0x5a */ set(3,sx(UINT32_C(0x005a0000)));
/* 002de564: lui t0,0x5a */ set(8,sx(UINT32_C(0x005a0000)));
/* 002de568: addiu s2,v1,-0x43c0 */ set(18,sx((uint32_t)cpu(3)+UINT32_C(0xffffbc40)));
/* 002de56c: lui a2,0x5a */ set(6,sx(UINT32_C(0x005a0000)));
/* 002de570: lui a3,0x5a */ set(7,sx(UINT32_C(0x005a0000)));
/* 002de574: addiu s0,t0,-0x2bc0 */ set(16,sx((uint32_t)cpu(8)+UINT32_C(0xffffd440)));
/* 002de578: li v1,0x20 */ set(3,sx(UINT32_C(0x00000020)));
/* 002de57c: lui v0,0x2000 */ set(2,sx(UINT32_C(0x20000000)));
/* 002de580: addiu a2,a2,-0x3bc0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffc440)));
/* 002de584: addiu a3,a3,-0x33c0 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffcc40)));
/* 002de588: or a2,a2,v0 */ set(6,cpu(6)|cpu(2));
/* 002de58c: or a3,a3,v0 */ set(7,cpu(7)|cpu(2));
/* 002de590: sw v1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
/* 002de594: or v0,s2,v0 */ set(2,cpu(18)|cpu(2));
/* 002de598: sw s1,-0x2bc0(t0) */ sw(ea(8,(int32_t)UINT32_C(0xffffd440)),(uint32_t)cpu(17));
/* 002de59c: lui a1,0x2e */ set(5,sx(UINT32_C(0x002e0000)));
/* 002de5a0: sw a2,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(6));
/* 002de5a4: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de5a8: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002de5ac: addiu a1,a1,-0x17f8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe808)));
/* 002de5b0: sw a3,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(7));
/* 002de5b4: ori a0,a0,0x8 */ set(4,cpu(4)|UINT32_C(0x00000008));
/* 002de5b8: move a2,s0 */ set(6,cpu(16));
/* 002de5bc: sw v1,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002de5c0: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002de5c4: sw zero,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002de5c8: sw v1,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002de5cc: jal 0x002de120 */ set(31,0x002de5d4u);/* delay 002de5d0 */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));nocturneBattleActionSkillCall(0x002de120u);
/* 002de5d4: lui a1,0x2e */ set(5,sx(UINT32_C(0x002e0000)));
/* 002de5d8: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de5dc: addiu a1,a1,-0x1538 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffeac8)));
/* 002de5e0: ori a0,a0,0x9 */ set(4,cpu(4)|UINT32_C(0x00000009));
/* 002de5e4: jal 0x002de120 */ set(31,0x002de5ecu);/* delay 002de5e8 */ set(6,cpu(16));nocturneBattleActionSkillCall(0x002de120u);
/* 002de5ec: lui a1,0x2e */ set(5,sx(UINT32_C(0x002e0000)));
/* 002de5f0: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de5f4: addiu a1,a1,-0x1348 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffecb8)));
/* 002de5f8: ori a0,a0,0xa */ set(4,cpu(4)|UINT32_C(0x0000000a));
/* 002de5fc: jal 0x002de120 */ set(31,0x002de604u);/* delay 002de600 */ set(6,cpu(16));nocturneBattleActionSkillCall(0x002de120u);
/* 002de604: lui a1,0x2e */ set(5,sx(UINT32_C(0x002e0000)));
/* 002de608: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de60c: addiu a1,a1,-0x1740 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe8c0)));
/* 002de610: move a2,s0 */ set(6,cpu(16));
/* 002de614: jal 0x002de120 */ set(31,0x002de61cu);/* delay 002de618 */ set(4,cpu(4)|UINT32_C(0x0000000c));nocturneBattleActionSkillCall(0x002de120u);
/* 002de61c: jal 0x002e40b8 */ set(31,0x002de624u);/* delay 002de620 */ nocturneBattleActionSkillCall(0x002e40b8u);
/* 002de624: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de628: jal 0x002dc2b0 */ set(31,0x002de630u);/* delay 002de62c */ set(4,cpu(4)|UINT32_C(0x00000002));nocturneBattleActionSkillCall(0x002dc2b0u);
/* 002de630: bne v0,zero,0x002de690 */ {int taken=(cpu(2)!=cpu(0));/* delay 002de634 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_002de690;}}
/* 002de638: addiu a1,s2,0x40 */ set(5,sx((uint32_t)cpu(18)+UINT32_C(0x00000040)));
/* 002de63c: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de640: sw s1,0xc(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(17));
/* 002de644: ori a0,a0,0x2 */ set(4,cpu(4)|UINT32_C(0x00000002));
/* 002de648: li a2,0x10 */ set(6,sx(UINT32_C(0x00000010)));
/* 002de64c: move a3,zero */ set(7,cpu(0));
/* 002de650: move t0,zero */ set(8,cpu(0));
/* 002de654: jal 0x002de2b0 */ set(31,0x002de65cu);/* delay 002de658 */ set(9,cpu(0));nocturneBattleActionSkillCall(0x002de2b0u);
/* 002de65c: nop  */ 
L_002de660:;
/* 002de660: jal 0x002dddf0 */ set(31,0x002de668u);/* delay 002de664 */ set(4,cpu(0));nocturneBattleActionSkillCall(0x002dddf0u);
/* 002de668: beq v0,zero,0x002de660 */ {int taken=(cpu(2)==cpu(0));/* delay 002de66c */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_002de660;}}
/* 002de670: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de674: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de678: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002de67c: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002de680: ori a0,a0,0x2 */ set(4,cpu(4)|UINT32_C(0x00000002));
/* 002de684: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de688: j 0x002dc2a0 */ /* delay 002de68c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002dc2a0u);return;
L_002de690:;
/* 002de690: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de694: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002de698: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de69c: jr ra */ {uint64_t target=cpu(31);/* delay 002de6a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002dde38(void){
nocturneEffectAxisNoteEntry(0x002dde38u);
uint64_t incoming=cpu(31);
/* 002dde38: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002dde3c: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002dde40: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002dde44: sd s3,0x30(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dde48: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dde4c: sd s1,0x10(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dde50: jal 0x002e4070 */ set(31,0x002dde58u);/* delay 002dde54 */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));nocturneBattleActionSkillCall(0x002e4070u);
/* 002dde58: lui t2,0x53 */ set(10,sx(UINT32_C(0x00530000)));
/* 002dde5c: lw v0,-0x3d48(t2) */ lw(2,ea(10,(int32_t)UINT32_C(0xffffc2b8)));
/* 002dde60: beq v0,zero,0x002dde88 */ {int taken=(cpu(2)==cpu(0));/* delay 002dde64 */ set(19,sx(UINT32_C(0x005a0000)));if(taken){goto L_002dde88;}}
/* 002dde68: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002dde6c: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002dde70: ld s3,0x30(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dde74: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dde78: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dde7c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dde80: j 0x002e40b8 */ /* delay 002dde84 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002e40b8u);return;
L_002dde88:;
/* 002dde88: lui a1,0x5a */ set(5,sx(UINT32_C(0x005a0000)));
/* 002dde8c: lui v0,0x2000 */ set(2,sx(UINT32_C(0x20000000)));
/* 002dde90: addiu a1,a1,-0x45c0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffba40)));
/* 002dde94: addiu a2,s3,-0x4640 */ set(6,sx((uint32_t)cpu(19)+UINT32_C(0xffffb9c0)));
/* 002dde98: lui s2,0x5a */ set(18,sx(UINT32_C(0x005a0000)));
/* 002dde9c: or a1,a1,v0 */ set(5,cpu(5)|cpu(2));
/* 002ddea0: or a2,a2,v0 */ set(6,cpu(6)|cpu(2));
/* 002ddea4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002ddea8: lui t1,0x5a */ set(9,sx(UINT32_C(0x005a0000)));
/* 002ddeac: lui a0,0x5a */ set(4,sx(UINT32_C(0x005a0000)));
/* 002ddeb0: addiu v0,s2,-0x4568 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0xffffba98)));
/* 002ddeb4: sw v1,-0x3d48(t2) */ sw(ea(10,(int32_t)UINT32_C(0xffffc2b8)),(uint32_t)cpu(3));
/* 002ddeb8: addiu t0,t1,-0x4540 */ set(8,sx((uint32_t)cpu(9)+UINT32_C(0xffffbac0)));
/* 002ddebc: sw a2,-0x4568(s2) */ sw(ea(18,(int32_t)UINT32_C(0xffffba98)),(uint32_t)cpu(6));
/* 002ddec0: addiu a0,a0,-0x4440 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffbbc0)));
/* 002ddec4: li a3,0x20 */ set(7,sx(UINT32_C(0x00000020)));
/* 002ddec8: sw a0,0x1c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(4));
/* 002ddecc: sw a1,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 002dded0: move v1,t0 */ set(3,cpu(8));
/* 002dded4: sw a3,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(7));
/* 002dded8: lui s4,0x5a */ set(20,sx(UINT32_C(0x005a0000)));
/* 002ddedc: sw zero,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002ddee0: li s0,0x1f */ set(16,sx(UINT32_C(0x0000001f)));
/* 002ddee4: sw t0,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(8));
/* 002ddee8: sw zero,0x14(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002ddeec: sw zero,0x18(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
L_002ddef0:;
/* 002ddef0: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002ddef4: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 002ddef8: sw zero,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002ddefc: addiu v1,v1,0x8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 002ddf00: nop  */ 
/* 002ddf04: bgez s0,0x002ddef0 */ {int taken=((int64_t)cpu(16)>=0);/* delay 002ddf08 */ if(taken){goto L_002ddef0;}}
/* 002ddf0c: lui v0,0x5a */ set(2,sx(UINT32_C(0x005a0000)));
/* 002ddf10: li s0,0x1f */ set(16,sx(UINT32_C(0x0000001f)));
/* 002ddf14: addiu v0,v0,-0x4440 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffbbc0)));
/* 002ddf18: addiu v0,v0,0x7c */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000007c)));
/* 002ddf1c: nop  */ 
L_002ddf20:;
/* 002ddf20: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002ddf24: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 002ddf28: addiu v0,v0,-0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffc)));
/* 002ddf2c: nop  */ 
/* 002ddf30: nop  */ 
/* 002ddf34: bgez s0,0x002ddf20 */ {int taken=((int64_t)cpu(16)>=0);/* delay 002ddf38 */ if(taken){goto L_002ddf20;}}
/* 002ddf3c: lui v0,0x2e */ set(2,sx(UINT32_C(0x002e0000)));
/* 002ddf40: lui v1,0x2e */ set(3,sx(UINT32_C(0x002e0000)));
/* 002ddf44: addiu v0,v0,-0x2220 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffdde0)));
/* 002ddf48: addiu a0,t1,-0x4540 */ set(4,sx((uint32_t)cpu(9)+UINT32_C(0xffffbac0)));
/* 002ddf4c: addiu v1,v1,-0x2240 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffddc0)));
/* 002ddf50: addiu s1,s2,-0x4568 */ set(17,sx((uint32_t)cpu(18)+UINT32_C(0xffffba98)));
/* 002ddf54: sw v0,-0x4540(t1) */ sw(ea(9,(int32_t)UINT32_C(0xffffbac0)),(uint32_t)cpu(2));
/* 002ddf58: li s0,0x20 */ set(16,sx(UINT32_C(0x00000020)));
/* 002ddf5c: sw v1,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002ddf60: sw s1,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(17));
/* 002ddf64: jal 0x002e40b8 */ set(31,0x002ddf6cu);/* delay 002ddf68 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));nocturneBattleActionSkillCall(0x002e40b8u);
/* 002ddf6c: jal 0x002dc120 */ set(31,0x002ddf74u);/* delay 002ddf70 */ set(4,cpu(0));nocturneBattleActionSkillCall(0x002dc120u);
/* 002ddf74: lui v0,0x1000 */ set(2,sx(UINT32_C(0x10000000)));
/* 002ddf78: ori v0,v0,0xe010 */ set(2,cpu(2)|UINT32_C(0x0000e010));
/* 002ddf7c: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002ddf80: andi v1,v1,0x20 */ set(3,cpu(3)&UINT32_C(0x00000020));
/* 002ddf84: beq v1,zero,0x002ddf98 */ {int taken=(cpu(3)==cpu(0));/* delay 002ddf88 */ set(2,sx(UINT32_C(0x10000000)));if(taken){goto L_002ddf98;}}
/* 002ddf8c: lui at,0x1001 */ set(1,sx(UINT32_C(0x10010000)));
/* 002ddf90: sw s0,-0x1ff0(at) */ sw(ea(1,(int32_t)UINT32_C(0xffffe010)),(uint32_t)cpu(16));
/* 002ddf94: lui v0,0x1000 */ set(2,sx(UINT32_C(0x10000000)));
L_002ddf98:;
/* 002ddf98: ori v0,v0,0xc000 */ set(2,cpu(2)|UINT32_C(0x0000c000));
/* 002ddf9c: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002ddfa0: andi v1,v1,0x100 */ set(3,cpu(3)&UINT32_C(0x00000100));
/* 002ddfa4: bne v1,zero,0x002ddfb8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002ddfa8 */ set(5,sx(UINT32_C(0x002e0000)));if(taken){goto L_002ddfb8;}}
/* 002ddfac: jal 0x002dc280 */ set(31,0x002ddfb4u);/* delay 002ddfb0 */ nocturneBattleActionSkillCall(0x002dc280u);
/* 002ddfb4: lui a1,0x2e */ set(5,sx(UINT32_C(0x002e0000)));
L_002ddfb8:;
/* 002ddfb8: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 002ddfbc: addiu a1,a1,-0x1cd0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffe330)));
/* 002ddfc0: jal 0x002dbbb0 */ set(31,0x002ddfc8u);/* delay 002ddfc4 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x002dbbb0u);
/* 002ddfc8: lui v1,0x5a */ set(3,sx(UINT32_C(0x005a0000)));
/* 002ddfcc: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 002ddfd0: jal 0x002dcab8 */ set(31,0x002ddfd8u);/* delay 002ddfd4 */ sw(ea(3,(int32_t)UINT32_C(0xffffba94)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x002dcab8u);
/* 002ddfd8: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002ddfdc: jal 0x002dc2b0 */ set(31,0x002ddfe4u);/* delay 002ddfe0 */ nocturneBattleActionSkillCall(0x002dc2b0u);
/* 002ddfe4: beq v0,zero,0x002de02c */ {int taken=(cpu(2)==cpu(0));/* delay 002ddfe8 */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002de02c;}}
/* 002ddfec: addiu a1,s4,-0x4580 */ set(5,sx((uint32_t)cpu(20)+UINT32_C(0xffffba80)));
/* 002ddff0: addiu v0,s3,-0x4640 */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0xffffb9c0)));
/* 002ddff4: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002ddff8: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002ddffc: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002de000: li a2,0x14 */ set(6,sx(UINT32_C(0x00000014)));
/* 002de004: ld s3,0x30(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002de008: move a3,zero */ set(7,cpu(0));
/* 002de00c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de010: move t0,zero */ set(8,cpu(0));
/* 002de014: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002de018: move t1,zero */ set(9,cpu(0));
/* 002de01c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de020: sw v0,0x10(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002de024: j 0x002de2b0 */ /* delay 002de028 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002de2b0u);return;
L_002de02c:;
/* 002de02c: lui s0,0x2 */ set(16,sx(UINT32_C(0x00020000)));
L_002de030:;
/* 002de030: jal 0x002dc2b0 */ set(31,0x002de038u);/* delay 002de034 */ set(4,sx(UINT32_C(0x00000004)));nocturneBattleActionSkillCall(0x002dc2b0u);
/* 002de038: and v0,v0,s0 */ set(2,cpu(2)&cpu(16));
/* 002de03c: beq v0,zero,0x002de030 */ {int taken=(cpu(2)==cpu(0));/* delay 002de040 */ set(4,sx(UINT32_C(0x00000002)));if(taken){goto L_002de030;}}
/* 002de044: jal 0x002dc2b0 */ set(31,0x002de04cu);/* delay 002de048 */ set(16,sx((uint32_t)cpu(18)+UINT32_C(0xffffba98)));nocturneBattleActionSkillCall(0x002dc2b0u);
/* 002de04c: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002de050: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de054: jal 0x002dc2a0 */ set(31,0x002de05cu);/* delay 002de058 */ set(5,cpu(2));nocturneBattleActionSkillCall(0x002dc2a0u);
/* 002de05c: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de060: move a1,s0 */ set(5,cpu(16));
/* 002de064: jal 0x002dc2a0 */ set(31,0x002de06cu);/* delay 002de068 */ set(4,cpu(4)|UINT32_C(0x00000001));nocturneBattleActionSkillCall(0x002dc2a0u);
/* 002de06c: addiu v1,s4,-0x4580 */ set(3,sx((uint32_t)cpu(20)+UINT32_C(0xffffba80)));
/* 002de070: addiu v0,s3,-0x4640 */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0xffffb9c0)));
/* 002de074: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002de078: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002de07c: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002de080: move a1,v1 */ set(5,cpu(3));
/* 002de084: ld s3,0x30(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002de088: ori a0,a0,0x2 */ set(4,cpu(4)|UINT32_C(0x00000002));
/* 002de08c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de090: li a2,0x14 */ set(6,sx(UINT32_C(0x00000014)));
/* 002de094: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002de098: move a3,zero */ set(7,cpu(0));
/* 002de09c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de0a0: move t0,zero */ set(8,cpu(0));
/* 002de0a4: sw v0,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002de0a8: move t1,zero */ set(9,cpu(0));
/* 002de0ac: sw zero,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002de0b0: j 0x002de2b0 */ /* delay 002de0b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002de2b0u);return;
}
uint32_t nocturneBattleActionSkillSifStartupBody(uint32_t entry){switch(entry){
case 0x002dfad8u:body_002dfad8();return 1u;
case 0x002de508u:body_002de508();return 1u;
case 0x002dde38u:body_002dde38();return 1u;
default:return 0u;}}
