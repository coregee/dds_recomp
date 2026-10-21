/* Whole four original first-worker/RPC-open/lock algorithms.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_first_worker_frames.h"
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

static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}

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



static void body_002be8c8(void);
static void body_002dfd70(void);
static void body_002df9d0(void);
static void body_002df980(void);
static void body_002be8c8(void){
nocturneEffectAxisNoteEntry(0x002be8c8u);
/* 002be8c8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002be8cc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002be8d0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be8d4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002be8d8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002be8dc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002be8e0: move s3,a0 */ set(19,cpu(4));
/* 002be8e4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002be8e8: lui s4,0x55 */ set(20,sx(UINT32_C(0x00550000)));
/* 002be8ec: nop  */ 
L_002be8f0:;
/* 002be8f0: jal 0x002dbee0 */ set(31,0x002be8f8u);/* delay 002be8f4 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000004)));nocturneBattleActionSkillCall(0x002dbee0u);
/* 002be8f8: lw s0,0x8(s3) */ lw(16,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 002be8fc: beq s0,zero,0x002be8f0 */ {int taken=(cpu(16)==cpu(0));/* delay 002be900 */ if(taken){goto L_002be8f0;}}
/* 002be904: lbu v1,0x15(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000015))));
/* 002be908: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 002be90c: sltiu v0,v1,0x9 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000009));
/* 002be910: beq v0,zero,0x002be8f0 */ {int taken=(cpu(2)==cpu(0));/* delay 002be914 */ sb(ea(16,(int32_t)UINT32_C(0x00000015)),(uint8_t)cpu(0));if(taken){goto L_002be8f0;}}
/* 002be918: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 002be91c: addiu v1,s4,-0x6990 */ set(3,sx((uint32_t)cpu(20)+UINT32_C(0xffff9670)));
/* 002be920: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002be924: lw a0,0x0(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002be928: jr a0 */ {uint64_t target=cpu(4);/* delay 002be92c */ switch(target){case 0x002be930u:goto L_002be930;case 0x002be978u:goto L_002be978;case 0x002be9c0u:goto L_002be9c0;case 0x002bea08u:goto L_002bea08;case 0x002beaa0u:goto L_002beaa0;case 0x002beaf0u:goto L_002beaf0;case 0x002beb50u:goto L_002beb50;case 0x002beba8u:goto L_002beba8;case 0x002bec80u:goto L_002bec80;default:abort();}}
L_002be930:;
/* 002be930: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002be934: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002be938: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002be93c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002be940: jal 0x002dfd70 */ set(31,0x002be948u);/* delay 002be944 */ set(6,cpu(0));body_002dfd70();
/* 002be948: move v1,v0 */ set(3,cpu(2));
/* 002be94c: bltz v1,0x002beca4 */ {int taken=((int64_t)cpu(3)<0);/* delay 002be950 */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_002beca4;}}
/* 002be954: lw t1,0x38(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002be958: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002be95c: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 002be960: beq t1,zero,0x002be8f0 */ {int taken=(cpu(9)==cpu(0));/* delay 002be964 */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));if(taken){goto L_002be8f0;}}
/* 002be968: move a0,s0 */ set(4,cpu(16));
/* 002be96c: b 0x002beb90 */ /* delay 002be970 */ set(5,sx(UINT32_C(0x00000002)));goto L_002beb90;
L_002be978:;
/* 002be978: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002be97c: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002be980: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002be984: li a1,0x202 */ set(5,sx(UINT32_C(0x00000202)));
/* 002be988: jal 0x002dfd70 */ set(31,0x002be990u);/* delay 002be98c */ lw(6,ea(16,(int32_t)UINT32_C(0x00000024)));body_002dfd70();
/* 002be990: move v1,v0 */ set(3,cpu(2));
/* 002be994: bltz v1,0x002beca4 */ {int taken=((int64_t)cpu(3)<0);/* delay 002be998 */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_002beca4;}}
/* 002be99c: lw t1,0x38(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002be9a0: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002be9a4: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 002be9a8: beq t1,zero,0x002be8f0 */ {int taken=(cpu(9)==cpu(0));/* delay 002be9ac */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));if(taken){goto L_002be8f0;}}
/* 002be9b0: move a0,s0 */ set(4,cpu(16));
/* 002be9b4: b 0x002beb90 */ /* delay 002be9b8 */ set(5,sx(UINT32_C(0x00000002)));goto L_002beb90;
L_002be9c0:;
/* 002be9c0: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002be9c4: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002be9c8: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002be9cc: lw a1,0x18(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 002be9d0: jal 0x002e0178 */ set(31,0x002be9d8u);/* delay 002be9d4 */ lw(6,ea(16,(int32_t)UINT32_C(0x00000024)));nocturneBattleActionSkillCall(0x002e0178u);
/* 002be9d8: move s2,v0 */ set(18,cpu(2));
/* 002be9dc: bltz s2,0x002bea44 */ {int taken=((int64_t)cpu(18)<0);/* delay 002be9e0 */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_002bea44;}}
/* 002be9e4: lw t1,0x38(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002be9e8: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002be9ec: beq t1,zero,0x002be8f0 */ {int taken=(cpu(9)==cpu(0));/* delay 002be9f0 */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(18));if(taken){goto L_002be8f0;}}
/* 002be9f4: move a0,s0 */ set(4,cpu(16));
/* 002be9f8: move a3,s2 */ set(7,cpu(18));
/* 002be9fc: lw t0,0x3c(a0) */ lw(8,ea(4,(int32_t)UINT32_C(0x0000003c)));
/* 002bea00: b 0x002bea90 */ /* delay 002bea04 */ set(5,sx(UINT32_C(0x00000003)));goto L_002bea90;
L_002bea08:;
/* 002bea08: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002bea0c: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002bea10: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002bea14: move a1,zero */ set(5,cpu(0));
/* 002bea18: jal 0x002e0178 */ set(31,0x002bea20u);/* delay 002bea1c */ set(6,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002e0178u);
/* 002bea20: move s1,v0 */ set(17,cpu(2));
/* 002bea24: bltz s1,0x002bece4 */ {int taken=((int64_t)cpu(17)<0);/* delay 002bea28 */ set(5,cpu(0));if(taken){goto L_002bece4;}}
/* 002bea2c: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002bea30: jal 0x002e0178 */ set(31,0x002bea38u);/* delay 002bea34 */ set(6,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x002e0178u);
/* 002bea38: move s2,v0 */ set(18,cpu(2));
/* 002bea3c: bgezl s2,0x002bea58 */ {int taken=((int64_t)cpu(18)>=0);if(taken){/* delay 002bea40 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));goto L_002bea58;}}
L_002bea44:;
/* 002bea44: move a0,s0 */ set(4,cpu(16));
/* 002bea48: jal 0x002be878 */ set(31,0x002bea50u);/* delay 002bea4c */ set(5,cpu(18));nocturneBattleActionSkillCall(0x002be878u);
/* 002bea50: b 0x002be8f0 */ /* delay 002bea54 */ goto L_002be8f0;
L_002bea58:;
/* 002bea58: move a1,s1 */ set(5,cpu(17));
/* 002bea5c: jal 0x002e0178 */ set(31,0x002bea64u);/* delay 002bea60 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x002e0178u);
/* 002bea64: move a1,v0 */ set(5,cpu(2));
/* 002bea68: bltz a1,0x002bec14 */ {int taken=((int64_t)cpu(5)<0);/* delay 002bea6c */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_002bec14;}}
/* 002bea70: lw t1,0x38(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002bea74: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002bea78: beq t1,zero,0x002be8f0 */ {int taken=(cpu(9)==cpu(0));/* delay 002bea7c */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(18));if(taken){goto L_002be8f0;}}
/* 002bea80: move a0,s0 */ set(4,cpu(16));
/* 002bea84: move a3,s2 */ set(7,cpu(18));
/* 002bea88: lw t0,0x3c(a0) */ lw(8,ea(4,(int32_t)UINT32_C(0x0000003c)));
/* 002bea8c: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
L_002bea90:;
/* 002bea90: jalr t1 */ {uint64_t target=cpu(9);set(31,0x002bea98u);/* delay 002bea94 */ set(6,cpu(0));nocturneBattleActionSkillFirstWorkerIndirect(0x002bea90u,target);}
/* 002bea98: b 0x002be8f0 */ /* delay 002bea9c */ goto L_002be8f0;
L_002beaa0:;
/* 002beaa0: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 002beaa4: lw a1,0x20(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002beaa8: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002beaac: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002beab0: jal 0x002e03b0 */ set(31,0x002beab8u);/* delay 002beab4 */ lw(6,ea(16,(int32_t)UINT32_C(0x0000001c)));nocturneBattleActionSkillCall(0x002e03b0u);
/* 002beab8: move a1,v0 */ set(5,cpu(2));
/* 002beabc: bltz a1,0x002bec14 */ {int taken=((int64_t)cpu(5)<0);/* delay 002beac0 */ set(3,sx(UINT32_C(0x00000007)));if(taken){goto L_002bec14;}}
/* 002beac4: lw v0,0x30(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000030)));
/* 002beac8: lw t1,0x38(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002beacc: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002bead0: sb v1,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(3));
/* 002bead4: beq t1,zero,0x002be8f0 */ {int taken=(cpu(9)==cpu(0));/* delay 002bead8 */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));if(taken){goto L_002be8f0;}}
/* 002beadc: move a0,s0 */ set(4,cpu(16));
/* 002beae0: move a3,a1 */ set(7,cpu(5));
/* 002beae4: lw a2,0x20(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002beae8: b 0x002beb3c */ /* delay 002beaec */ set(5,sx(UINT32_C(0x00000005)));goto L_002beb3c;
L_002beaf0:;
/* 002beaf0: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 002beaf4: lw a1,0x20(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002beaf8: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002beafc: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002beb00: jal 0x002e0620 */ set(31,0x002beb08u);/* delay 002beb04 */ lw(6,ea(16,(int32_t)UINT32_C(0x0000001c)));nocturneBattleActionSkillCall(0x002e0620u);
/* 002beb08: move a1,v0 */ set(5,cpu(2));
/* 002beb0c: bltz a1,0x002bec14 */ {int taken=((int64_t)cpu(5)<0);/* delay 002beb10 */ set(3,sx(UINT32_C(0x00000007)));if(taken){goto L_002bec14;}}
/* 002beb14: lw v0,0x30(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000030)));
/* 002beb18: lw t1,0x38(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002beb1c: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002beb20: sb v1,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(3));
/* 002beb24: beq t1,zero,0x002be8f0 */ {int taken=(cpu(9)==cpu(0));/* delay 002beb28 */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));if(taken){goto L_002be8f0;}}
/* 002beb2c: move a0,s0 */ set(4,cpu(16));
/* 002beb30: move a3,a1 */ set(7,cpu(5));
/* 002beb34: lw a2,0x20(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002beb38: li a1,0x6 */ set(5,sx(UINT32_C(0x00000006)));
L_002beb3c:;
/* 002beb3c: jalr t1 */ {uint64_t target=cpu(9);set(31,0x002beb44u);/* delay 002beb40 */ lw(8,ea(4,(int32_t)UINT32_C(0x0000003c)));nocturneBattleActionSkillFirstWorkerIndirect(0x002beb3cu,target);}
/* 002beb44: b 0x002be8f0 */ /* delay 002beb48 */ goto L_002be8f0;
L_002beb50:;
/* 002beb50: li v0,0x6 */ set(2,sx(UINT32_C(0x00000006)));
/* 002beb54: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002beb58: jal 0x002dfff8 */ set(31,0x002beb60u);/* delay 002beb5c */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));nocturneBattleActionSkillCall(0x002dfff8u);
/* 002beb60: move a1,v0 */ set(5,cpu(2));
/* 002beb64: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002beb68: bltz a1,0x002bec14 */ {int taken=((int64_t)cpu(5)<0);/* delay 002beb6c */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));if(taken){goto L_002bec14;}}
/* 002beb70: jal 0x002be720 */ set(31,0x002beb78u);/* delay 002beb74 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002be720u);
/* 002beb78: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002beb7c: lw t1,0x38(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002beb80: beq t1,zero,0x002be8f0 */ {int taken=(cpu(9)==cpu(0));/* delay 002beb84 */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));if(taken){goto L_002be8f0;}}
/* 002beb88: move a0,s0 */ set(4,cpu(16));
/* 002beb8c: li a1,0x7 */ set(5,sx(UINT32_C(0x00000007)));
L_002beb90:;
/* 002beb90: lw t0,0x3c(a0) */ lw(8,ea(4,(int32_t)UINT32_C(0x0000003c)));
/* 002beb94: move a2,zero */ set(6,cpu(0));
/* 002beb98: jalr t1 */ {uint64_t target=cpu(9);set(31,0x002beba0u);/* delay 002beb9c */ set(7,cpu(0));nocturneBattleActionSkillFirstWorkerIndirect(0x002beb98u,target);}
/* 002beba0: b 0x002be8f0 */ /* delay 002beba4 */ goto L_002be8f0;
L_002beba8:;
/* 002beba8: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002bebac: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002bebb0: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002bebb4: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002bebb8: jal 0x002dfd70 */ set(31,0x002bebc0u);/* delay 002bebbc */ set(6,cpu(0));body_002dfd70();
/* 002bebc0: move v1,v0 */ set(3,cpu(2));
/* 002bebc4: bltz v1,0x002beca8 */ {int taken=((int64_t)cpu(3)<0);/* delay 002bebc8 */ set(4,cpu(16));if(taken){goto L_002beca8;}}
/* 002bebcc: lw s1,0x1c(s0) */ lw(17,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 002bebd0: bgez s1,0x002bec28 */ {int taken=((int64_t)cpu(17)>=0);/* delay 002bebd4 */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));if(taken){goto L_002bec28;}}
/* 002bebd8: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002bebdc: move a0,v1 */ set(4,cpu(3));
/* 002bebe0: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002bebe4: move a1,zero */ set(5,cpu(0));
/* 002bebe8: jal 0x002e0178 */ set(31,0x002bebf0u);/* delay 002bebec */ set(6,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x002e0178u);
/* 002bebf0: move s1,v0 */ set(17,cpu(2));
/* 002bebf4: bltz s1,0x002bece4 */ {int taken=((int64_t)cpu(17)<0);/* delay 002bebf8 */ set(5,cpu(0));if(taken){goto L_002bece4;}}
/* 002bebfc: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002bec00: jal 0x002e0178 */ set(31,0x002bec08u);/* delay 002bec04 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x002e0178u);
/* 002bec08: move a1,v0 */ set(5,cpu(2));
/* 002bec0c: bgez a1,0x002bec28 */ {int taken=((int64_t)cpu(5)>=0);/* delay 002bec10 */ if(taken){goto L_002bec28;}}
L_002bec14:;
/* 002bec14: jal 0x002be878 */ set(31,0x002bec1cu);/* delay 002bec18 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002be878u);
/* 002bec1c: b 0x002be8f0 */ /* delay 002bec20 */ goto L_002be8f0;
L_002bec28:;
/* 002bec28: beq s1,zero,0x002becfc */ {int taken=(cpu(17)==cpu(0));/* delay 002bec2c */ set(2,sx(UINT32_C(0x00000006)));if(taken){goto L_002becfc;}}
/* 002bec30: lw a1,0x20(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002bec34: bne a1,zero,0x002bec54 */ {int taken=(cpu(5)!=cpu(0));/* delay 002bec38 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_002bec54;}}
/* 002bec3c: jal 0x002a9038 */ set(31,0x002bec44u);/* delay 002bec40 */ set(4,cpu(17));nocturneBattleActionSkillCall(0x002a9038u);
/* 002bec44: jal 0x002a9688 */ set(31,0x002bec4cu);/* delay 002bec48 */ set(4,cpu(2));nocturneBattleActionSkillCall(0x002a9688u);
/* 002bec4c: move a1,v0 */ set(5,cpu(2));
/* 002bec50: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
L_002bec54:;
/* 002bec54: sw a1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(5));
/* 002bec58: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002bec5c: move a2,s1 */ set(6,cpu(17));
/* 002bec60: jal 0x002e03b0 */ set(31,0x002bec68u);/* delay 002bec64 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));nocturneBattleActionSkillCall(0x002e03b0u);
/* 002bec68: move s1,v0 */ set(17,cpu(2));
/* 002bec6c: bltz s1,0x002bece4 */ {int taken=((int64_t)cpu(17)<0);/* delay 002bec70 */ set(2,sx(UINT32_C(0x00000006)));if(taken){goto L_002bece4;}}
/* 002bec74: b 0x002bed00 */ /* delay 002bec78 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));goto L_002bed00;
L_002bec80:;
/* 002bec80: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002bec84: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002bec88: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002bec8c: li a1,0x202 */ set(5,sx(UINT32_C(0x00000202)));
/* 002bec90: jal 0x002dfd70 */ set(31,0x002bec98u);/* delay 002bec94 */ lw(6,ea(16,(int32_t)UINT32_C(0x00000024)));body_002dfd70();
/* 002bec98: move v1,v0 */ set(3,cpu(2));
/* 002bec9c: bgezl v1,0x002becb8 */ {int taken=((int64_t)cpu(3)>=0);if(taken){/* delay 002beca0 */ lw(17,ea(16,(int32_t)UINT32_C(0x0000001c)));goto L_002becb8;}}
L_002beca4:;
/* 002beca4: move a0,s0 */ set(4,cpu(16));
L_002beca8:;
/* 002beca8: jal 0x002be878 */ set(31,0x002becb0u);/* delay 002becac */ set(5,cpu(3));nocturneBattleActionSkillCall(0x002be878u);
/* 002becb0: b 0x002be8f0 */ /* delay 002becb4 */ goto L_002be8f0;
L_002becb8:;
/* 002becb8: beq s1,zero,0x002becf8 */ {int taken=(cpu(17)==cpu(0));/* delay 002becbc */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));if(taken){goto L_002becf8;}}
/* 002becc0: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 002becc4: lw a1,0x20(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002becc8: sb v0,0x16(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));
/* 002beccc: move a2,s1 */ set(6,cpu(17));
/* 002becd0: jal 0x002e0620 */ set(31,0x002becd8u);/* delay 002becd4 */ set(4,cpu(3));nocturneBattleActionSkillCall(0x002e0620u);
/* 002becd8: move s1,v0 */ set(17,cpu(2));
/* 002becdc: bgez s1,0x002becfc */ {int taken=((int64_t)cpu(17)>=0);/* delay 002bece0 */ set(2,sx(UINT32_C(0x00000006)));if(taken){goto L_002becfc;}}
L_002bece4:;
/* 002bece4: move a0,s0 */ set(4,cpu(16));
/* 002bece8: jal 0x002be878 */ set(31,0x002becf0u);/* delay 002becec */ set(5,cpu(17));nocturneBattleActionSkillCall(0x002be878u);
/* 002becf0: b 0x002be8f0 */ /* delay 002becf4 */ goto L_002be8f0;
L_002becf8:;
/* 002becf8: li v0,0x6 */ set(2,sx(UINT32_C(0x00000006)));
L_002becfc:;
/* 002becfc: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
L_002bed00:;
/* 002bed00: jal 0x002dfff8 */ set(31,0x002bed08u);/* delay 002bed04 */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));nocturneBattleActionSkillCall(0x002dfff8u);
/* 002bed08: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002bed0c: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 002bed10: jal 0x002be720 */ set(31,0x002bed18u);/* delay 002bed14 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002be720u);
/* 002bed18: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002bed1c: lw t1,0x38(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002bed20: beq t1,zero,0x002bed40 */ {int taken=(cpu(9)==cpu(0));/* delay 002bed24 */ sb(ea(16,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(2));if(taken){goto L_002bed40;}}
/* 002bed28: move a0,s0 */ set(4,cpu(16));
/* 002bed2c: move a3,s1 */ set(7,cpu(17));
/* 002bed30: lw a2,0x20(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002bed34: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
/* 002bed38: jalr t1 */ {uint64_t target=cpu(9);set(31,0x002bed40u);/* delay 002bed3c */ lw(8,ea(4,(int32_t)UINT32_C(0x0000003c)));nocturneBattleActionSkillFirstWorkerIndirect(0x002bed38u,target);}
L_002bed40:;
/* 002bed40: jal 0x002dbec0 */ set(31,0x002bed48u);/* delay 002bed44 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000004)));nocturneBattleActionSkillCall(0x002dbec0u);
/* 002bed48: b 0x002be8f0 */ /* delay 002bed4c */ goto L_002be8f0;
}
static void body_002dfd70(void){
nocturneEffectAxisNoteEntry(0x002dfd70u);
uint64_t incoming=cpu(31);
/* 002dfd70: addiu sp,sp,-0x150 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffeb0)));
/* 002dfd74: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002dfd78: sd s7,0xb0(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 002dfd7c: move s0,a0 */ set(16,cpu(4));
/* 002dfd80: sd s8,0xc0(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 002dfd84: move s7,a1 */ set(23,cpu(5));
/* 002dfd88: sd s1,0x50(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002dfd8c: move a0,zero */ set(4,cpu(0));
/* 002dfd90: sd ra,0xd0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 002dfd94: lui s8,0x5a */ set(30,sx(UINT32_C(0x005a0000)));
/* 002dfd98: sd s6,0xa0(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002dfd9c: addiu s1,s8,-0x2b40 */ set(17,sx((uint32_t)cpu(30)+UINT32_C(0xffffd4c0)));
/* 002dfda0: sd s5,0x90(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002dfda4: sd s4,0x80(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002dfda8: sd s3,0x70(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002dfdac: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002dfdb0: sd a2,0x120(sp) */ save(6,ea(29,(int32_t)UINT32_C(0x00000120)));
/* 002dfdb4: sd a3,0x128(sp) */ save(7,ea(29,(int32_t)UINT32_C(0x00000128)));
/* 002dfdb8: sd t0,0x130(sp) */ save(8,ea(29,(int32_t)UINT32_C(0x00000130)));
/* 002dfdbc: sd t1,0x138(sp) */ save(9,ea(29,(int32_t)UINT32_C(0x00000138)));
/* 002dfdc0: sd t2,0x140(sp) */ save(10,ea(29,(int32_t)UINT32_C(0x00000140)));
/* 002dfdc4: jal 0x002df9d0 */ set(31,0x002dfdccu);/* delay 002dfdc8 */ save(11,ea(29,(int32_t)UINT32_C(0x00000148)));body_002df9d0();
/* 002dfdcc: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002dfdd0: lw v0,-0x3cc0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0xffffc340)));
/* 002dfdd4: bne v0,zero,0x002dfde4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002dfdd8 */ if(taken){goto L_002dfde4;}}
/* 002dfddc: jal 0x002dfad8 */ set(31,0x002dfde4u);/* delay 002dfde0 */ nocturneBattleActionSkillCall(0x002dfad8u);
L_002dfde4:;
/* 002dfde4: jal 0x002dfca8 */ set(31,0x002dfdecu);/* delay 002dfde8 */ nocturneBattleActionSkillCall(0x002dfca8u);
/* 002dfdec: beq v0,zero,0x002dfe08 */ {int taken=(cpu(2)==cpu(0));/* delay 002dfdf0 */ if(taken){goto L_002dfe08;}}
/* 002dfdf4: jal 0x002dfa00 */ set(31,0x002dfdfcu);/* delay 002dfdf8 */ nocturneBattleActionSkillCall(0x002dfa00u);
/* 002dfdfc: lui v0,0xfffe */ set(2,sx(UINT32_C(0xfffe0000)));
/* 002dfe00: b 0x002dffc4 */ /* delay 002dfe04 */ set(2,cpu(2)|UINT32_C(0x0000fffc));goto L_002dffc4;
L_002dfe08:;
/* 002dfe08: jal 0x002df4c8 */ set(31,0x002dfe10u);/* delay 002dfe0c */ nocturneBattleActionSkillCall(0x002df4c8u);
/* 002dfe10: move s3,v0 */ set(19,cpu(2));
/* 002dfe14: bnel s3,zero,0x002dfe2c */ {int taken=(cpu(19)!=cpu(0));if(taken){/* delay 002dfe18 */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000000))));goto L_002dfe2c;}}
/* 002dfe1c: jal 0x002dfa00 */ set(31,0x002dfe24u);/* delay 002dfe20 */ nocturneBattleActionSkillCall(0x002dfa00u);
/* 002dfe24: b 0x002dffc4 */ /* delay 002dfe28 */ set(2,sx(UINT32_C(0xffffffed)));goto L_002dffc4;
L_002dfe2c:;
/* 002dfe2c: move a1,zero */ set(5,cpu(0));
/* 002dfe30: lw a3,0x120(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000120)));
/* 002dfe34: sll v0,v1,0x18 */ set(2,sx((uint32_t)cpu(3)<<24));
/* 002dfe38: beq v0,zero,0x002dfe84 */ {int taken=(cpu(2)==cpu(0));/* delay 002dfe3c */ sb(ea(17,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(3));if(taken){goto L_002dfe84;}}
/* 002dfe40: lui a2,0x5a */ set(6,sx(UINT32_C(0x005a0000)));
/* 002dfe44: addiu s2,sp,0x30 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 002dfe48: lui s6,0x5a */ set(22,sx(UINT32_C(0x005a0000)));
/* 002dfe4c: lui s4,0x5a */ set(20,sx(UINT32_C(0x005a0000)));
/* 002dfe50: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002dfe54: nop  */ 
L_002dfe58:;
/* 002dfe58: slti v0,a1,0x400 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000400));
/* 002dfe5c: beq v0,zero,0x002dfe94 */ {int taken=(cpu(2)==cpu(0));/* delay 002dfe60 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));if(taken){goto L_002dfe94;}}
/* 002dfe64: addu a0,s1,a1 */ set(4,sx((uint32_t)cpu(17)+(uint32_t)cpu(5)));
/* 002dfe68: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002dfe6c: sb v1,0x14(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(3));
/* 002dfe70: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 002dfe74: bnel v1,zero,0x002dfe58 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002dfe78 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));goto L_002dfe58;}}
/* 002dfe7c: b 0x002dfe98 */ /* delay 002dfe80 */ set(2,sx(UINT32_C(0x00000400)));goto L_002dfe98;
L_002dfe84:;
/* 002dfe84: lui a2,0x5a */ set(6,sx(UINT32_C(0x005a0000)));
/* 002dfe88: addiu s2,sp,0x30 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 002dfe8c: lui s6,0x5a */ set(22,sx(UINT32_C(0x005a0000)));
/* 002dfe90: lui s4,0x5a */ set(20,sx(UINT32_C(0x005a0000)));
L_002dfe94:;
/* 002dfe94: li v0,0x400 */ set(2,sx(UINT32_C(0x00000400)));
L_002dfe98:;
/* 002dfe98: beql a1,v0,0x002dfea0 */ {int taken=(cpu(5)==cpu(2));if(taken){/* delay 002dfe9c */ sb(ea(17,(int32_t)UINT32_C(0x00000413)),(uint8_t)cpu(0));goto L_002dfea0;}}
L_002dfea0:;
/* 002dfea0: addiu v0,a2,-0x1a80 */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0xffffe580)));
/* 002dfea4: lui v1,0x6fff */ set(3,sx(UINT32_C(0x6fff0000)));
/* 002dfea8: subu v0,s3,v0 */ set(2,sx((uint32_t)cpu(19)-(uint32_t)cpu(2)));
/* 002dfeac: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002dfeb0: sra s5,v0,0x4 */ set(21,sx((uint32_t)((int32_t)cpu(2)>>4)));
/* 002dfeb4: and v1,s7,v1 */ set(3,cpu(23)&cpu(3));
/* 002dfeb8: sw v1,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 002dfebc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002dfec0: sw a3,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(7));
/* 002dfec4: addiu a0,sp,0x10 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002dfec8: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 002dfecc: addiu s4,s4,-0x1f00 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffe100)));
/* 002dfed0: sw s5,0x414(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000414)),(uint32_t)cpu(21));
/* 002dfed4: sw zero,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 002dfed8: jal 0x002dbea0 */ set(31,0x002dfee0u);/* delay 002dfedc */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));nocturneBattleActionSkillCall(0x002dbea0u);
/* 002dfee0: move s0,v0 */ set(16,cpu(2));
/* 002dfee4: sw s2,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(18));
/* 002dfee8: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 002dfeec: sw s0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002dfef0: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002dfef4: addiu a0,s6,-0x1880 */ set(4,sx((uint32_t)cpu(22)+UINT32_C(0xffffe780)));
/* 002dfef8: addiu a3,s8,-0x2b40 */ set(7,sx((uint32_t)cpu(30)+UINT32_C(0xffffd4c0)));
/* 002dfefc: move a1,zero */ set(5,cpu(0));
/* 002dff00: sw zero,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002dff04: move a2,zero */ set(6,cpu(0));
/* 002dff08: li t0,0x418 */ set(8,sx(UINT32_C(0x00000418)));
/* 002dff0c: move t1,s4 */ set(9,cpu(20));
/* 002dff10: li t2,0x4 */ set(10,sx(UINT32_C(0x00000004)));
/* 002dff14: jal 0x002ded48 */ set(31,0x002dff1cu);/* delay 002dff18 */ set(11,cpu(0));nocturneBattleActionSkillCall(0x002ded48u);
/* 002dff1c: bgez v0,0x002dff3c */ {int taken=((int64_t)cpu(2)>=0);/* delay 002dff20 */ set(2,sx(UINT32_C(0x20000000)));if(taken){goto L_002dff3c;}}
/* 002dff24: jal 0x002dbeb0 */ set(31,0x002dff2cu);/* delay 002dff28 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002dbeb0u);
/* 002dff2c: jal 0x002dfa00 */ set(31,0x002dff34u);/* delay 002dff30 */ nocturneBattleActionSkillCall(0x002dfa00u);
/* 002dff34: b 0x002dffc4 */ /* delay 002dff38 */ set(2,sx(UINT32_C(0xfffffff5)));goto L_002dffc4;
L_002dff3c:;
/* 002dff3c: or v0,s4,v0 */ set(2,cpu(20)|cpu(2));
/* 002dff40: jal 0x002dfa00 */ set(31,0x002dff48u);/* delay 002dff44 */ lw(17,ea(2,(int32_t)UINT32_C(0x00000000)));nocturneBattleActionSkillCall(0x002dfa00u);
/* 002dff48: bne s1,zero,0x002dff60 */ {int taken=(cpu(17)!=cpu(0));/* delay 002dff4c */ if(taken){goto L_002dff60;}}
/* 002dff50: jal 0x002dbeb0 */ set(31,0x002dff58u);/* delay 002dff54 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002dbeb0u);
/* 002dff58: b 0x002dffc4 */ /* delay 002dff5c */ set(2,sx(UINT32_C(0xfffffff5)));goto L_002dffc4;
L_002dff60:;
/* 002dff60: jal 0x002dbee0 */ set(31,0x002dff68u);/* delay 002dff64 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002dbee0u);
/* 002dff68: jal 0x002dbeb0 */ set(31,0x002dff70u);/* delay 002dff6c */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002dbeb0u);
/* 002dff70: lw v1,0x30(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dff74: bgez v1,0x002dff98 */ {int taken=((int64_t)cpu(3)>=0);/* delay 002dff78 */ set(16,sx(UINT32_C(0x00530000)));if(taken){goto L_002dff98;}}
/* 002dff7c: jal 0x002dbee0 */ set(31,0x002dff84u);/* delay 002dff80 */ lw(4,ea(16,(int32_t)UINT32_C(0xffffc348)));nocturneBattleActionSkillCall(0x002dbee0u);
/* 002dff84: sw zero,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002dff88: jal 0x002dbec0 */ set(31,0x002dff90u);/* delay 002dff8c */ lw(4,ea(16,(int32_t)UINT32_C(0xffffc348)));nocturneBattleActionSkillCall(0x002dbec0u);
/* 002dff90: b 0x002dffc4 */ /* delay 002dff94 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000030)));goto L_002dffc4;
L_002dff98:;
/* 002dff98: move s1,s5 */ set(17,cpu(21));
/* 002dff9c: jal 0x002dbee0 */ set(31,0x002dffa4u);/* delay 002dffa0 */ lw(4,ea(16,(int32_t)UINT32_C(0xffffc348)));nocturneBattleActionSkillCall(0x002dbee0u);
/* 002dffa4: lw v1,0x4(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 002dffa8: lw v0,0x30(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dffac: lw a0,-0x3cb8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0xffffc348)));
/* 002dffb0: or v1,v1,s7 */ set(3,cpu(3)|cpu(23));
/* 002dffb4: sw v1,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002dffb8: jal 0x002dbec0 */ set(31,0x002dffc0u);/* delay 002dffbc */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x002dbec0u);
/* 002dffc0: move v0,s1 */ set(2,cpu(17));
L_002dffc4:;
/* 002dffc4: ld ra,0xd0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 002dffc8: ld s8,0xc0(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 002dffcc: ld s7,0xb0(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 002dffd0: ld s6,0xa0(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002dffd4: ld s5,0x90(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002dffd8: ld s4,0x80(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002dffdc: ld s3,0x70(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002dffe0: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002dffe4: ld s1,0x50(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002dffe8: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002dffec: jr ra */ {uint64_t target=cpu(31);/* delay 002dfff0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000150)));checkReturn(target,incoming);return;}
}
static void body_002df9d0(void){
nocturneEffectAxisNoteEntry(0x002df9d0u);
uint64_t incoming=cpu(31);
/* 002df9d0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002df9d4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002df9d8: jal 0x002df980 */ set(31,0x002df9e0u);/* delay 002df9dc */ body_002df980();
/* 002df9e0: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002df9e4: jal 0x002dbee0 */ set(31,0x002df9ecu);/* delay 002df9e8 */ lw(4,ea(2,(int32_t)UINT32_C(0xffffc344)));nocturneBattleActionSkillCall(0x002dbee0u);
/* 002df9ec: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002df9f0: move v0,zero */ set(2,cpu(0));
/* 002df9f4: jr ra */ {uint64_t target=cpu(31);/* delay 002df9f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002df980(void){
nocturneEffectAxisNoteEntry(0x002df980u);
uint64_t incoming=cpu(31);
/* 002df980: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002df984: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002df988: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002df98c: lui s0,0x53 */ set(16,sx(UINT32_C(0x00530000)));
/* 002df990: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002df994: lw v0,-0x3cbc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0xffffc344)));
/* 002df998: bne v0,v1,0x002df9c0 */ {int taken=(cpu(2)!=cpu(3));/* delay 002df99c */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_002df9c0;}}
/* 002df9a0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002df9a4: sw zero,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002df9a8: sw v0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002df9ac: move a0,sp */ set(4,cpu(29));
/* 002df9b0: jal 0x002dbea0 */ set(31,0x002df9b8u);/* delay 002df9b4 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x002dbea0u);
/* 002df9b8: sw v0,-0x3cbc(s0) */ sw(ea(16,(int32_t)UINT32_C(0xffffc344)),(uint32_t)cpu(2));
/* 002df9bc: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
L_002df9c0:;
/* 002df9c0: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002df9c4: jr ra */ {uint64_t target=cpu(31);/* delay 002df9c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleActionSkillFirstWorkerBody(uint32_t entry){switch(entry){
case 0x002be8c8u:body_002be8c8();
case 0x002dfd70u:body_002dfd70();return 1u;
case 0x002df9d0u:body_002df9d0();return 1u;
case 0x002df980u:body_002df980();return 1u;
default:return 0u;}}
