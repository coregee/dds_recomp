/* Complete original reward/frame registered dependencies.
 * Shared live CPU/FPR/RAM, true guest frames and native volatile carry into
 * printf are preserved. No expected data, stack patch or game-result provider.
 */
#include "battle_action_reward_frames.h"
#include "battle_action_packet_frames.h"
#include "battle_action_formula_frames.h"
#include "ee_fpu.h"
#include "pcp_effect_helpers.h"
#include "battle_action_consumer.h"
#include "battle_action_scale_lookup_frames.h"
#include "effect_host_bindings.h"
#include "effect_model_child_dependency_frames.h"
#include "effect_random_frames.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
extern uint64_t nocturneEffectHostHi(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}

static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}

static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


extern uint64_t nocturneEffectHostLo(void);
/* Distinct real secondary state is shared with Formula49; no primary-bank
 * substitution or capture-supplied quotient. Native DIV1 is followed by a
 * primary DIV and late guard before MFLO1; no intervening callee exists. */
static void nativeDivide(uint32_t n,uint32_t d,int isSigned,int secondary){
 uint32_t q,r;
 if(!d){q=isSigned&&((int32_t)n<0)?1u:UINT32_MAX;r=n;}
 else if(isSigned&&n==UINT32_C(0x80000000)&&d==UINT32_MAX){q=n;r=0;}
 else if(isSigned){q=(uint32_t)((int32_t)n/(int32_t)d);r=(uint32_t)((int32_t)n%(int32_t)d);}
 else{q=n/d;r=n%d;}
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx(q),sx(r));
 else EE_PCP_EFFECT_DIV_STATE(q,r);
}

static void body_00269448(void);
static uint64_t body_00246038(void);
static uint64_t body_00244598(void);
static void body_00269448(void){
nocturneEffectAxisNoteEntry(0x00269448u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00269448: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 0026944c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00269450: move s1,a0 */ set(17,cpu(4));
/* 00269454: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00269458: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026945c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00269460: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00269464: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00269468: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0026946c: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00269470: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00269474: bne v0,zero,0x002696d4 */ {int taken=(cpu(2)!=cpu(0));/* delay 00269478 */ set(20,cpu(0));if(taken){goto L_002696d4;}}
/* 0026947c: jal 0x002469a0 */ set(31,0x00269484u);/* delay 00269480 */ ps2BattleActionScaleLookup_002469A0();
/* 00269484: move s5,v0 */ set(21,cpu(2));
/* 00269488: jal 0x00246038 */ set(31,0x00269490u);/* delay 0026948c */ lw(4,ea(21,(int32_t)UINT32_C(0x00000034)));body_00246038();
/* 00269490: lhu v1,0x4(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 00269494: move s2,v0 */ set(18,cpu(2));
/* 00269498: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 0026949c: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002694a0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002694a4: lui s3,0x35 */ set(19,sx(UINT32_C(0x00350000)));
/* 002694a8: addiu s3,s3,-0x6840 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffff97c0)));
/* 002694ac: addu s3,s3,v0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(2)));
/* 002694b0: jal 0x00244598 */ set(31,0x002694b8u);/* delay 002694b4 */ set(16,half(ea(19,(int32_t)UINT32_C(0x0000002c))));body_00244598();
/* 002694b8: lhu v1,0x14(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 002694bc: sltiu a0,v1,0x46 */ set(4,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000046));
/* 002694c0: beq a0,zero,0x00269528 */ {int taken=(cpu(4)==cpu(0));/* delay 002694c4 */ set(3,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));if(taken){goto L_00269528;}}
/* 002694c8: addiu v0,v1,-0x6 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xfffffffa)));
/* 002694cc: sltiu v0,v0,0x6 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000006));
/* 002694d0: bne v0,zero,0x00269534 */ {int taken=(cpu(2)!=cpu(0));/* delay 002694d4 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000c));if(taken){goto L_00269534;}}
/* 002694d8: bne v0,zero,0x00269554 */ {int taken=(cpu(2)!=cpu(0));/* delay 002694dc */ if(taken){goto L_00269554;}}
/* 002694e0: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 002694e4: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 002694e8: lwc1 f1,-0x5be0(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa420)));
/* 002694ec: b 0x00269540 */ /* delay 002694f0 */ goto L_00269540;
L_002694f8:;
/* 002694f8: addiu v1,s5,0xc */ set(3,sx((uint32_t)cpu(21)+UINT32_C(0x0000000c)));
/* 002694fc: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00269500: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00269504: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00269508: b 0x002696d4 */ /* delay 0026950c */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002696d4;
L_00269510:;
/* 00269510: addu v1,s5,v1 */ set(3,sx((uint32_t)cpu(21)+(uint32_t)cpu(3)));
/* 00269514: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00269518: sb s4,0x0(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(20));
/* 0026951c: b 0x002696d4 */ /* delay 00269520 */ sb(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(2));goto L_002696d4;
L_00269528:;
/* 00269528: slti v0,v1,0x6 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0026952c: bne v0,zero,0x00269554 */ {int taken=(cpu(2)!=cpu(0));/* delay 00269530 */ if(taken){goto L_00269554;}}
L_00269534:;
/* 00269534: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 00269538: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0026953c: lwc1 f1,-0x5bdc(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa424)));
L_00269540:;
/* 00269540: nop  */ 
/* 00269544: nop  */ 
/* 00269548: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 0026954c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00269550: mfc1 s0,f1 */ set(16,sx(f[1]));
L_00269554:;
/* 00269554: beq s2,zero,0x00269580 */ {int taken=(cpu(18)==cpu(0));/* delay 00269558 */ set(5,half(ea(19,(int32_t)UINT32_C(0x0000002a))));if(taken){goto L_00269580;}}
/* 0026955c: li v0,0xa */ set(2,sx(UINT32_C(0x0000000a)));
/* 00269560: li a0,0xa */ set(4,sx(UINT32_C(0x0000000a)));
/* 00269564: div1 s0,v0 */ nativeDivide((uint32_t)cpu(16),(uint32_t)cpu(2),1,1);
/* 00269568: div a1,v0 */ nativeDivide((uint32_t)cpu(5),(uint32_t)cpu(2),1,0);
/* 0026956c: beql v0,zero,0x00269574 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00269570 */ nocturneCompilerArithmeticTrap(7u);goto L_00269574;}}
L_00269574:;
/* 00269574: mflo1 v1 */ set(3,nocturneBattleActionFormulaSecondaryLo());
/* 00269578: mflo a1 */ set(5,nocturneEffectHostLo());
/* 0026957c: move s0,v1 */ set(16,cpu(3));
L_00269580:;
/* 00269580: lw v0,0xa4(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x000000a4)));
/* 00269584: lw v1,0xa0(s5) */ lw(3,ea(21,(int32_t)UINT32_C(0x000000a0)));
/* 00269588: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 0026958c: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00269590: sw v0,0xa4(s5) */ sw(ea(21,(int32_t)UINT32_C(0x000000a4)),(uint32_t)cpu(2));
/* 00269594: bne s2,zero,0x002696d4 */ {int taken=(cpu(18)!=cpu(0));/* delay 00269598 */ sw(ea(21,(int32_t)UINT32_C(0x000000a0)),(uint32_t)cpu(3));if(taken){goto L_002696d4;}}
/* 0026959c: lhu v0,0x32(s3) */ set(2,half(ea(19,(int32_t)UINT32_C(0x00000032))));
/* 002695a0: beql v0,zero,0x002695bc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002695a4 */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000034))));goto L_002695bc;}}
/* 002695a8: jal 0x001e0f50 */ set(31,0x002695b0u);/* delay 002695ac */ set(4,cpu(2));ps2BattleActionFormula_001E0F50(cpu(4));
/* 002695b0: beq v0,zero,0x002695dc */ {int taken=(cpu(2)==cpu(0));/* delay 002695b4 */ if(taken){goto L_002695dc;}}
/* 002695b8: lbu v0,0x34(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000034))));
L_002695bc:;
/* 002695bc: beq v0,zero,0x002695dc */ {int taken=(cpu(2)==cpu(0));/* delay 002695c0 */ set(4,cpu(0));if(taken){goto L_002695dc;}}
/* 002695c4: jal 0x002c0c60 */ set(31,0x002695ccu);/* delay 002695c8 */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 002695cc: lbu v1,0x35(s3) */ set(3,byte(ea(19,(int32_t)UINT32_C(0x00000035))));
/* 002695d0: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 002695d4: bnel v0,zero,0x002695dc */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002695d8 */ set(20,byte(ea(19,(int32_t)UINT32_C(0x00000034))));goto L_002695dc;}}
L_002695dc:;
/* 002695dc: bne s4,zero,0x0026962c */ {int taken=(cpu(20)!=cpu(0));/* delay 002695e0 */ set(17,cpu(0));if(taken){goto L_0026962c;}}
/* 002695e4: addiu s2,s3,0x30 */ set(18,sx((uint32_t)cpu(19)+UINT32_C(0x00000030)));
/* 002695e8: addiu s0,s3,0x2e */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0x0000002e)));
/* 002695ec: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
L_002695f0:;
/* 002695f0: beq v0,zero,0x00269610 */ {int taken=(cpu(2)==cpu(0));/* delay 002695f4 */ set(4,cpu(0));if(taken){goto L_00269610;}}
/* 002695f8: jal 0x002c0c60 */ set(31,0x00269600u);/* delay 002695fc */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00269600: lbu v1,0x0(s2) */ set(3,byte(ea(18,(int32_t)UINT32_C(0x00000000))));
/* 00269604: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 00269608: bnel v0,zero,0x00269610 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0026960c */ set(20,byte(ea(16,(int32_t)UINT32_C(0x00000000))));goto L_00269610;}}
L_00269610:;
/* 00269610: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 00269614: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 00269618: slti v0,s1,0x2 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0026961c: beq v0,zero,0x0026962c */ {int taken=(cpu(2)==cpu(0));/* delay 00269620 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));if(taken){goto L_0026962c;}}
/* 00269624: beql s4,zero,0x002695f0 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00269628 */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));goto L_002695f0;}}
L_0026962c:;
/* 0026962c: move a0,zero */ set(4,cpu(0));
/* 00269630: jal 0x002c0c60 */ set(31,0x00269638u);/* delay 00269634 */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00269638: lbu v1,0x36(s3) */ set(3,byte(ea(19,(int32_t)UINT32_C(0x00000036))));
/* 0026963c: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 00269640: beq v0,zero,0x00269650 */ {int taken=(cpu(2)==cpu(0));/* delay 00269644 */ set(4,cpu(0));if(taken){goto L_00269650;}}
/* 00269648: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 0026964c: movz s4,v0,s4 */ if(cpu(20)==0){set(20,cpu(2));}
L_00269650:;
/* 00269650: jal 0x002c0c60 */ set(31,0x00269658u);/* delay 00269654 */ set(5,sx(UINT32_C(0x00000064)));ps2BattleActionPacket_002C0C60(cpu(4),cpu(5));
/* 00269658: lbu v1,0x37(s3) */ set(3,byte(ea(19,(int32_t)UINT32_C(0x00000037))));
/* 0026965c: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 00269660: beq v0,zero,0x0026966c */ {int taken=(cpu(2)==cpu(0));/* delay 00269664 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_0026966c;}}
/* 00269668: movz s4,v0,s4 */ if(cpu(20)==0){set(20,cpu(2));}
L_0026966c:;
/* 0026966c: beq s4,zero,0x002696d4 */ {int taken=(cpu(20)==cpu(0));/* delay 00269670 */ set(17,cpu(0));if(taken){goto L_002696d4;}}
/* 00269674: addiu a2,s5,0x8 */ set(6,sx((uint32_t)cpu(21)+UINT32_C(0x00000008)));
/* 00269678: addiu a0,s5,0x98 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x00000098)));
/* 0026967c: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
L_00269680:;
/* 00269680: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00269684: addiu a1,s1,0x90 */ set(5,sx((uint32_t)cpu(17)+UINT32_C(0x00000090)));
/* 00269688: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 0026968c: beq v0,s4,0x002694f8 */ {int taken=(cpu(2)==cpu(20));/* delay 00269690 */ set(3,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_002694f8;}}
/* 00269694: nop  */ 
/* 00269698: nop  */ 
/* 0026969c: bnel v1,zero,0x00269680 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002696a0 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_00269680;}}
/* 002696a4: addiu a2,a2,0x90 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000090)));
/* 002696a8: move s1,zero */ set(17,cpu(0));
/* 002696ac: move a1,a2 */ set(5,cpu(6));
L_002696b0:;
/* 002696b0: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002696b4: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002696b8: addiu v1,s1,0x90 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000090)));
/* 002696bc: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 002696c0: beq v0,zero,0x00269510 */ {int taken=(cpu(2)==cpu(0));/* delay 002696c4 */ set(4,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_00269510;}}
/* 002696c8: nop  */ 
/* 002696cc: bne a0,zero,0x002696b0 */ {int taken=(cpu(4)!=cpu(0));/* delay 002696d0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));if(taken){goto L_002696b0;}}
L_002696d4:;
/* 002696d4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002696d8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002696dc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002696e0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002696e4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002696e8: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002696ec: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002696f0: jr ra */ {uint64_t target=cpu(31);/* delay 002696f4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionReward_00269448(uint64_t a0){
set(4,a0);
body_00269448();
}
static uint64_t body_00246038(void){
nocturneEffectAxisNoteEntry(0x00246038u);
uint64_t incoming=cpu(31);
/* 00246038: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024603c: lui v0,0x40 */ set(2,sx(UINT32_C(0x00400000)));
/* 00246040: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00246044: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00246048: addiu s0,v0,-0x5bd0 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffa430)));
/* 0024604c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246050: move s1,zero */ set(17,cpu(0));
/* 00246054: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00246058: move s2,a0 */ set(18,cpu(4));
/* 0024605c: nop  */ 
L_00246060:;
/* 00246060: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00246064: bnel v0,s2,0x00246088 */ {int taken=(cpu(2)!=cpu(18));if(taken){/* delay 00246068 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00246088;}}
/* 0024606c: jal 0x001e0f50 */ set(31,0x00246074u);/* delay 00246070 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));ps2BattleActionFormula_001E0F50(cpu(4));
/* 00246074: beq v0,zero,0x00246088 */ {int taken=(cpu(2)==cpu(0));/* delay 00246078 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));if(taken){goto L_00246088;}}
/* 0024607c: b 0x00246098 */ /* delay 00246080 */ set(2,sx(UINT32_C(0x00000001)));goto L_00246098;
L_00246088:;
/* 00246088: slti v0,s1,0x28 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000028));
/* 0024608c: bne v0,zero,0x00246060 */ {int taken=(cpu(2)!=cpu(0));/* delay 00246090 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));if(taken){goto L_00246060;}}
/* 00246094: move v0,zero */ set(2,cpu(0));
L_00246098:;
/* 00246098: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024609c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002460a0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002460a4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002460a8: jr ra */ {uint64_t target=cpu(31);/* delay 002460ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionReward_00246038(uint64_t a0){
set(4,a0);
return body_00246038();
}
static uint64_t body_00244598(void){
nocturneEffectAxisNoteEntry(0x00244598u);
uint64_t incoming=cpu(31);
/* 00244598: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024459c: jr ra */ {uint64_t target=cpu(31);/* delay 002445a0 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000a68))));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionReward_00244598(void){

return body_00244598();
}
