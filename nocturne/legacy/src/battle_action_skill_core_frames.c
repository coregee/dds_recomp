/* Whole original39 SKILL core/packet/timeline algorithms.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_core_frames.h"
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
static float real(uint32_t u){float v;memcpy(&v,&u,4);return v;}
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
/* Genuine EE word division is defined even before a late native BREAK.
 * Primary and secondary banks are distinct; use the existing Formula bank
 * for cross-unit secondary state rather than a private or primary substitute.
 */
static void nativeDivide(uint32_t n,uint32_t d,int isSigned,int secondary){
 uint32_t q,r;
 if(!d){q=isSigned&&((int32_t)n<0)?1u:UINT32_MAX;r=n;}
 else if(isSigned&&n==UINT32_C(0x80000000)&&d==UINT32_MAX){q=n;r=0;}
 else if(isSigned){q=(uint32_t)((int32_t)n/(int32_t)d);r=(uint32_t)((int32_t)n%(int32_t)d);}
 else{q=n/d;r=n%d;}
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx(q),sx(r));
 else EE_PCP_EFFECT_DIV_STATE(q,r);
}
static void nativeMultiply(unsigned rd,uint32_t a,uint32_t v,int isSigned,int secondary){
 uint64_t product=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)v):(uint64_t)a*v;
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)product),sx((uint32_t)(product>>32)));
 else EE_MAGATUHI_MULT_STATE(product);
 if(rd)set(rd,sx((uint32_t)product));
}

static void body_0024d3a0(void);
static void body_0024d428(void);
static void body_0024f5f0(void);
static void body_0024f658(void);
static void body_0024f728(void);
static void body_0024f7b8(void);
static void body_0024f7e0(void);
static void body_0024f8a8(void);
static void body_0024f938(void);
static void body_0024f990(void);
static void body_0024fb38(void);
static void body_0024fc28(void);
static void body_0024fcc0(void);
static void body_0024fe40(void);
static void body_00251770(void);
static void body_002518c8(void);
static void body_00252060(void);
static void body_00252fb8(void);
static void body_00255650(void);
static void body_002594b0(void);
static void body_002595a0(void);
static void body_00261500(void);
static void body_00261638(void);
static void body_00261e80(void);
static void body_00262340(void);
static void body_00262430(void);
static void body_00262a68(void);
static void body_00262ac8(void);
static void body_00262e28(void);
static void body_00262e78(void);
static void body_00262ed8(void);
static void body_00263028(void);
static void body_00263250(void);
static void body_002632d0(void);
static void body_00263548(void);
static void body_002636c8(void);
static void body_00263778(void);
static void body_002642e0(void);
static void body_00264368(void);
static void body_0024d3a0(void){
nocturneEffectAxisNoteEntry(0x0024d3a0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0024d3a0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024d3a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024d3a8: move s0,a1 */ set(16,cpu(5));
/* 0024d3ac: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024d3b0: move s1,a0 */ set(17,cpu(4));
/* 0024d3b4: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024d3b8: swc1 f20,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);
/* 0024d3bc: mov.S f20,f12 */ f[20]=f[12];
/* 0024d3c0: jal 0x00246ab8 */ set(31,0x0024d3c8u);/* delay 0024d3c4 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x00246ab8u);
/* 0024d3c8: jal 0x00259a60 */ set(31,0x0024d3d0u);/* delay 0024d3cc */ set(4,cpu(2));nocturneBattleActionSkillCall(0x00259a60u);
/* 0024d3d0: sll v1,s0,0x3 */ set(3,sx((uint32_t)cpu(16)<<3));
/* 0024d3d4: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 0024d3d8: move a1,s0 */ set(5,cpu(16));
/* 0024d3dc: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0024d3e0: move a0,s1 */ set(4,cpu(17));
/* 0024d3e4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0024d3e8: mov.S f12,f20 */ f[12]=f[20];
/* 0024d3ec: jal 0x0024d428 */ set(31,0x0024d3f4u);/* delay 0024d3f0 */ set(16,half(ea(3,(int32_t)UINT32_C(0x0000002e))));body_0024d428();
/* 0024d3f4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024d3f8: mtc1 s0,f1 */ f[1]=(uint32_t)cpu(16);
/* 0024d3fc: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0024d400: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024d404: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024d408: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024d40c: nop  */ 
/* 0024d410: nop  */ 
/* 0024d414: div.S f1,f1,f0 */ f[1]=EE_FPU_DIV_S(f[1],f[0]);
/* 0024d418: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0024d41c: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 0024d420: jr ra */ {uint64_t target=cpu(31);/* delay 0024d424 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_0024D3A0(uint64_t a0, uint64_t a1, float f12){
set(4,a0);set(5,a1);
nocturneEffectHostFpr()[12]=bits(f12);
body_0024d3a0();
return cpu(2);
}
static void body_0024d428(void){
nocturneEffectAxisNoteEntry(0x0024d428u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 0024d428: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024d42c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024d430: move s0,a1 */ set(16,cpu(5));
/* 0024d434: swc1 f20,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[20]);
/* 0024d438: mov.S f20,f12 */ f[20]=f[12];
/* 0024d43c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024d440: jal 0x00246ab8 */ set(31,0x0024d448u);/* delay 0024d444 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x00246ab8u);
/* 0024d448: jal 0x00259a60 */ set(31,0x0024d450u);/* delay 0024d44c */ set(4,cpu(2));nocturneBattleActionSkillCall(0x00259a60u);
/* 0024d450: sll v1,s0,0x3 */ set(3,sx((uint32_t)cpu(16)<<3));
/* 0024d454: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0024d458: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0024d45c: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 0024d460: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0024d464: c.eq.S f20,f0 */ condition=EE_FPU_COMPARE_S(f[20],f[0],0)!=0;
/* 0024d468: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0024d46c: bc1t 0x0024d478 */ {int taken=(condition!=0);/* delay 0024d470 */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000034)));if(taken){goto L_0024d478;}}
/* 0024d474: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
L_0024d478:;
/* 0024d478: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024d47c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024d480: lwc1 f20,0x10(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024d484: jr ra */ {uint64_t target=cpu(31);/* delay 0024d488 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
float ps2BattleActionSkill_0024D428(uint64_t a0, uint64_t a1, float f12){
set(4,a0);set(5,a1);
nocturneEffectHostFpr()[12]=bits(f12);
body_0024d428();
return real(nocturneEffectHostFpr()[0]);
}
static void body_0024f5f0(void){
nocturneEffectAxisNoteEntry(0x0024f5f0u);
uint64_t incoming=cpu(31);
/* 0024f5f0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024f5f4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f5f8: move s0,a1 */ set(16,cpu(5));
/* 0024f5fc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f600: move s1,a0 */ set(17,cpu(4));
/* 0024f604: move a0,s0 */ set(4,cpu(16));
/* 0024f608: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f60c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024f610: jal 0x00246a40 */ set(31,0x0024f618u);/* delay 0024f614 */ set(18,cpu(6));nocturneBattleActionSkillCall(0x00246a40u);
/* 0024f618: move a0,s2 */ set(4,cpu(18));
/* 0024f61c: move a1,s1 */ set(5,cpu(17));
/* 0024f620: jal 0x00263778 */ set(31,0x0024f628u);/* delay 0024f624 */ set(6,cpu(2));body_00263778();
/* 0024f628: move a0,s1 */ set(4,cpu(17));
/* 0024f62c: move a1,s0 */ set(5,cpu(16));
/* 0024f630: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f634: move a2,s2 */ set(6,cpu(18));
/* 0024f638: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f63c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f640: li a3,0x1e */ set(7,sx(UINT32_C(0x0000001e)));
/* 0024f644: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024f648: li t0,0x1e */ set(8,sx(UINT32_C(0x0000001e)));
/* 0024f64c: j 0x002517e0 */ /* delay 0024f650 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002517e0u);return;
}
void ps2BattleActionSkill_0024F5F0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_0024f5f0();
return;
}
static void body_0024f658(void){
nocturneEffectAxisNoteEntry(0x0024f658u);
uint64_t incoming=cpu(31);
/* 0024f658: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024f65c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f660: move s0,a1 */ set(16,cpu(5));
/* 0024f664: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f668: move s1,a0 */ set(17,cpu(4));
/* 0024f66c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f670: jal 0x00246a40 */ set(31,0x0024f678u);/* delay 0024f674 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x00246a40u);
/* 0024f678: move a0,s0 */ set(4,cpu(16));
/* 0024f67c: jal 0x00267e90 */ set(31,0x0024f684u);/* delay 0024f680 */ set(5,sx(UINT32_C(0x00000013)));nocturneBattleActionSkillCall(0x00267e90u);
/* 0024f684: move a2,v0 */ set(6,cpu(2));
/* 0024f688: li v0,0xf9 */ set(2,sx(UINT32_C(0x000000f9)));
/* 0024f68c: beq a2,v0,0x0024f6d8 */ {int taken=(cpu(6)==cpu(2));/* delay 0024f690 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x000000fa));if(taken){goto L_0024f6d8;}}
/* 0024f694: beq v0,zero,0x0024f6b8 */ {int taken=(cpu(2)==cpu(0));/* delay 0024f698 */ set(2,sx(UINT32_C(0x000000fa)));if(taken){goto L_0024f6b8;}}
/* 0024f69c: beq a2,zero,0x0024f6e8 */ {int taken=(cpu(6)==cpu(0));/* delay 0024f6a0 */ set(2,sx(UINT32_C(0x000000f8)));if(taken){goto L_0024f6e8;}}
/* 0024f6a4: beq a2,v0,0x0024f6d0 */ {int taken=(cpu(6)==cpu(2));/* delay 0024f6a8 */ set(5,sx(UINT32_C(0x00000013)));if(taken){goto L_0024f6d0;}}
/* 0024f6ac: b 0x0024f6f0 */ /* delay 0024f6b0 */ goto L_0024f6f0;
L_0024f6b8:;
/* 0024f6b8: beq a2,v0,0x0024f6e0 */ {int taken=(cpu(6)==cpu(2));/* delay 0024f6bc */ set(2,sx(UINT32_C(0x000000fb)));if(taken){goto L_0024f6e0;}}
/* 0024f6c0: beq a2,v0,0x0024f6e8 */ {int taken=(cpu(6)==cpu(2));/* delay 0024f6c4 */ set(5,sx(UINT32_C(0x00000013)));if(taken){goto L_0024f6e8;}}
/* 0024f6c8: b 0x0024f6f0 */ /* delay 0024f6cc */ goto L_0024f6f0;
L_0024f6d0:;
/* 0024f6d0: b 0x0024f6ec */ /* delay 0024f6d4 */ set(6,sx(UINT32_C(0x000000f9)));goto L_0024f6ec;
L_0024f6d8:;
/* 0024f6d8: b 0x0024f6ec */ /* delay 0024f6dc */ set(6,sx(UINT32_C(0x000000fa)));goto L_0024f6ec;
L_0024f6e0:;
/* 0024f6e0: b 0x0024f6ec */ /* delay 0024f6e4 */ set(6,sx(UINT32_C(0x000000fb)));goto L_0024f6ec;
L_0024f6e8:;
/* 0024f6e8: li a2,0xf8 */ set(6,sx(UINT32_C(0x000000f8)));
L_0024f6ec:;
/* 0024f6ec: li a1,0x13 */ set(5,sx(UINT32_C(0x00000013)));
L_0024f6f0:;
/* 0024f6f0: jal 0x00267e50 */ set(31,0x0024f6f8u);/* delay 0024f6f4 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x00267e50u);
/* 0024f6f8: jal 0x00246ab8 */ set(31,0x0024f700u);/* delay 0024f6fc */ set(4,cpu(16));nocturneBattleActionSkillCall(0x00246ab8u);
/* 0024f700: move a0,s1 */ set(4,cpu(17));
/* 0024f704: lhu a3,0x4(v0) */ set(7,half(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 0024f708: li a1,0x5a */ set(5,sx(UINT32_C(0x0000005a)));
/* 0024f70c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f710: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 0024f714: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f718: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f71c: j 0x002592b0 */ /* delay 0024f720 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002592b0u);return;
}
void ps2BattleActionSkill_0024F658(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_0024f658();
return;
}
static void body_0024f728(void){
nocturneEffectAxisNoteEntry(0x0024f728u);
uint64_t incoming=cpu(31);
/* 0024f728: sll v0,a1,0x4 */ set(2,sx((uint32_t)cpu(5)<<4));
/* 0024f72c: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 0024f730: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 0024f734: li a1,0xd */ set(5,sx(UINT32_C(0x0000000d)));
/* 0024f738: sll a2,v0,0x2 */ set(6,sx((uint32_t)cpu(2)<<2));
/* 0024f73c: addiu a3,v1,0x7998 */ set(7,sx((uint32_t)cpu(3)+UINT32_C(0x00007998)));
/* 0024f740: addu v1,a2,a3 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(7)));
/* 0024f744: lw v0,0x30(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000030)));
/* 0024f748: bne v0,a1,0x0024f774 */ {int taken=(cpu(2)!=cpu(5));/* delay 0024f74c */ set(2,cpu(3));if(taken){goto L_0024f774;}}
/* 0024f750: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 0024f754: lb a1,0x2c(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x0000002c))));
/* 0024f758: beq a1,v1,0x0024f798 */ {int taken=(cpu(5)==cpu(3));/* delay 0024f75c */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_0024f798;}}
/* 0024f760: beq v0,zero,0x0024f780 */ {int taken=(cpu(2)==cpu(0));/* delay 0024f764 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_0024f780;}}
/* 0024f768: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0024f76c: beql a1,v0,0x0024f790 */ {int taken=(cpu(5)==cpu(2));if(taken){/* delay 0024f770 */ set(2,sx(UINT32_C(0x0000000f)));goto L_0024f790;}}
L_0024f774:;
/* 0024f774: jr ra */ {uint64_t target=cpu(31);/* delay 0024f778 */ checkReturn(target,incoming);return;}
L_0024f780:;
/* 0024f780: beql a1,v0,0x0024f7a8 */ {int taken=(cpu(5)==cpu(2));if(taken){/* delay 0024f784 */ set(2,sx(UINT32_C(0x00000010)));goto L_0024f7a8;}}
/* 0024f788: jr ra */ {uint64_t target=cpu(31);/* delay 0024f78c */ checkReturn(target,incoming);return;}
L_0024f790:;
/* 0024f790: jr ra */ {uint64_t target=cpu(31);/* delay 0024f794 */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
L_0024f798:;
/* 0024f798: li v0,0x11 */ set(2,sx(UINT32_C(0x00000011)));
/* 0024f79c: jr ra */ {uint64_t target=cpu(31);/* delay 0024f7a0 */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
L_0024f7a8:;
/* 0024f7a8: sw v0,0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 0024f7ac: jr ra */ {uint64_t target=cpu(31);/* delay 0024f7b0 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_0024F728(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_0024f728();
return;
}
static void body_0024f7b8(void){
nocturneEffectAxisNoteEntry(0x0024f7b8u);
uint64_t incoming=cpu(31);
/* 0024f7b8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0024f7bc: move v0,a0 */ set(2,cpu(4));
/* 0024f7c0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f7c4: li a2,0x2 */ set(6,sx(UINT32_C(0x00000002)));
/* 0024f7c8: move a0,a1 */ set(4,cpu(5));
/* 0024f7cc: move a1,v0 */ set(5,cpu(2));
/* 0024f7d0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f7d4: j 0x00263548 */ /* delay 0024f7d8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00263548();return;
}
uint64_t ps2BattleActionSkill_0024F7B8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_0024f7b8();
return cpu(2);
}
static void body_0024f7e0(void){
nocturneEffectAxisNoteEntry(0x0024f7e0u);
uint64_t incoming=cpu(31);
/* 0024f7e0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024f7e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f7e8: move s0,a2 */ set(16,cpu(6));
/* 0024f7ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f7f0: move s1,a0 */ set(17,cpu(4));
/* 0024f7f4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f7f8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024f7fc: jal 0x0026a4b0 */ set(31,0x0024f804u);/* delay 0024f800 */ lw(4,ea(17,(int32_t)UINT32_C(0x0000002c)));nocturneBattleActionSkillCall(0x0026a4b0u);
/* 0024f804: move s2,v0 */ set(18,cpu(2));
/* 0024f808: lw v0,0x28(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 0024f80c: jal 0x0026a468 */ set(31,0x0024f814u);/* delay 0024f810 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x0026a468u);
/* 0024f814: move a0,s1 */ set(4,cpu(17));
/* 0024f818: move a2,s0 */ set(6,cpu(16));
/* 0024f81c: li a3,0x1e */ set(7,sx(UINT32_C(0x0000001e)));
/* 0024f820: beq v0,zero,0x0024f838 */ {int taken=(cpu(2)==cpu(0));/* delay 0024f824 */ set(8,sx(UINT32_C(0x0000001e)));if(taken){goto L_0024f838;}}
/* 0024f828: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024f82c: lw a1,0xa48(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000a48)));
/* 0024f830: slt v1,a1,s2 */ set(3,(int64_t)cpu(5)<(int64_t)cpu(18));
/* 0024f834: movn s2,a1,v1 */ if(cpu(3)!=0){set(18,cpu(5));}
L_0024f838:;
/* 0024f838: lw v0,0x28(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 0024f83c: jal 0x002517e0 */ set(31,0x0024f844u);/* delay 0024f840 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002517e0u);
/* 0024f844: move a0,s1 */ set(4,cpu(17));
/* 0024f848: li a1,0x2c */ set(5,sx(UINT32_C(0x0000002c)));
/* 0024f84c: move a2,zero */ set(6,cpu(0));
/* 0024f850: jal 0x002592b0 */ set(31,0x0024f858u);/* delay 0024f854 */ set(7,cpu(18));nocturneBattleActionSkillCall(0x002592b0u);
/* 0024f858: lw v0,0x28(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 0024f85c: jal 0x0026a468 */ set(31,0x0024f864u);/* delay 0024f860 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x0026a468u);
/* 0024f864: beq v0,zero,0x0024f888 */ {int taken=(cpu(2)==cpu(0));/* delay 0024f868 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(18)));if(taken){goto L_0024f888;}}
/* 0024f86c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f870: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f874: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f878: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024f87c: j 0x00244238 */ /* delay 0024f880 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x00244238u);return;
L_0024f888:;
/* 0024f888: move a0,s2 */ set(4,cpu(18));
/* 0024f88c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f890: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f894: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f898: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024f89c: j 0x00244238 */ /* delay 0024f8a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x00244238u);return;
}
void ps2BattleActionSkill_0024F7E0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_0024f7e0();
return;
}
static void body_0024f8a8(void){
nocturneEffectAxisNoteEntry(0x0024f8a8u);
uint64_t incoming=cpu(31);
/* 0024f8a8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024f8ac: sll v0,a1,0x4 */ set(2,sx((uint32_t)cpu(5)<<4));
/* 0024f8b0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f8b4: move s1,a0 */ set(17,cpu(4));
/* 0024f8b8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f8bc: move s2,a2 */ set(18,cpu(6));
/* 0024f8c0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024f8c4: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 0024f8c8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f8cc: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 0024f8d0: move a0,s2 */ set(4,cpu(18));
/* 0024f8d4: move a1,s1 */ set(5,cpu(17));
/* 0024f8d8: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024f8dc: li t0,0x6 */ set(8,sx(UINT32_C(0x00000006)));
/* 0024f8e0: li t1,0x6 */ set(9,sx(UINT32_C(0x00000006)));
/* 0024f8e4: li t2,0x6 */ set(10,sx(UINT32_C(0x00000006)));
/* 0024f8e8: lw s0,0x0(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0024f8ec: move a3,zero */ set(7,cpu(0));
/* 0024f8f0: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0024f8f4: jal 0x002638a0 */ set(31,0x0024f8fcu);/* delay 0024f8f8 */ set(6,cpu(16));nocturneBattleActionSkillCall(0x002638a0u);
/* 0024f8fc: addiu a0,s2,0xc */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x0000000c)));
/* 0024f900: move a2,s0 */ set(6,cpu(16));
/* 0024f904: move a1,s1 */ set(5,cpu(17));
/* 0024f908: jal 0x00262fb8 */ set(31,0x0024f910u);/* delay 0024f90c */ set(7,cpu(0));nocturneBattleActionSkillCall(0x00262fb8u);
/* 0024f910: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024f914: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f918: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 0024f91c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f920: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f924: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024f928: sw v0,0x44(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 0024f92c: jr ra */ {uint64_t target=cpu(31);/* delay 0024f930 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_0024F8A8(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_0024f8a8();
return;
}
static void body_0024f938(void){
nocturneEffectAxisNoteEntry(0x0024f938u);
uint64_t incoming=cpu(31);
/* 0024f938: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0024f93c: sll v0,a1,0x4 */ set(2,sx((uint32_t)cpu(5)<<4));
/* 0024f940: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f944: move s0,a0 */ set(16,cpu(4));
/* 0024f948: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f94c: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 0024f950: addiu a0,a2,0x2 */ set(4,sx((uint32_t)cpu(6)+UINT32_C(0x00000002)));
/* 0024f954: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 0024f958: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0024f95c: move a1,s0 */ set(5,cpu(16));
/* 0024f960: lw a2,0x0(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0024f964: jal 0x00262e78 */ set(31,0x0024f96cu);/* delay 0024f968 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));body_00262e78();
/* 0024f96c: jal 0x00280518 */ set(31,0x0024f974u);/* delay 0024f970 */ nocturneBattleActionSkillCall(0x00280518u);
/* 0024f974: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0024f978: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f97c: ori v0,v0,0x10 */ set(2,cpu(2)|UINT32_C(0x00000010));
/* 0024f980: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 0024f984: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f988: jr ra */ {uint64_t target=cpu(31);/* delay 0024f98c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_0024F938(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_0024f938();
return;
}
static void body_0024f990(void){
nocturneEffectAxisNoteEntry(0x0024f990u);
uint64_t incoming=cpu(31);
/* 0024f990: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0024f994: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024f998: move s1,a0 */ set(17,cpu(4));
/* 0024f99c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024f9a0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024f9a4: move s3,a3 */ set(19,cpu(7));
/* 0024f9a8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024f9ac: move s4,t0 */ set(20,cpu(8));
/* 0024f9b0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024f9b4: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024f9b8: lw v1,0x24(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 0024f9bc: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 0024f9c0: andi v0,v0,0x2 */ set(2,cpu(2)&UINT32_C(0x00000002));
/* 0024f9c4: sltu s2,zero,v0 */ set(18,cpu(0)<cpu(2));
/* 0024f9c8: bne s2,zero,0x0024fa28 */ {int taken=(cpu(18)!=cpu(0));/* delay 0024f9cc */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0024fa28;}}
/* 0024f9d0: lw a3,0x2c(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x0000002c)));
/* 0024f9d4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0024f9d8: lh v0,0x6a(a3) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x0000006a))));
/* 0024f9dc: bnel v0,v1,0x0024fa50 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 0024f9e0 */ set(16,half(ea(7,(int32_t)UINT32_C(0x0000006c))));goto L_0024fa50;}}
/* 0024f9e4: lhu v1,0x6c(a3) */ set(3,half(ea(7,(int32_t)UINT32_C(0x0000006c))));
/* 0024f9e8: li v0,0xdf */ set(2,sx(UINT32_C(0x000000df)));
/* 0024f9ec: bnel v1,v0,0x0024fa50 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 0024f9f0 */ set(16,half(ea(7,(int32_t)UINT32_C(0x0000006c))));goto L_0024fa50;}}
/* 0024f9f4: jal 0x002595a0 */ set(31,0x0024f9fcu);/* delay 0024f9f8 */ body_002595a0();
/* 0024f9fc: move s0,v0 */ set(16,cpu(2));
/* 0024fa00: bgez s0,0x0024fa54 */ {int taken=((int64_t)cpu(16)>=0);/* delay 0024fa04 */ set(4,cpu(20));if(taken){goto L_0024fa54;}}
/* 0024fa08: move a0,s1 */ set(4,cpu(17));
/* 0024fa0c: li a1,0x3e */ set(5,sx(UINT32_C(0x0000003e)));
/* 0024fa10: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 0024fa14: jal 0x002592b0 */ set(31,0x0024fa1cu);/* delay 0024fa18 */ set(7,cpu(0));nocturneBattleActionSkillCall(0x002592b0u);
/* 0024fa1c: b 0x0024fb18 */ /* delay 0024fa20 */ set(2,cpu(0));goto L_0024fb18;
L_0024fa28:;
/* 0024fa28: lw a1,0x1a0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x000001a0)));
/* 0024fa2c: jal 0x002594b0 */ set(31,0x0024fa34u);/* delay 0024fa30 */ set(6,cpu(19));body_002594b0();
/* 0024fa34: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fa38: move s0,v0 */ set(16,cpu(2));
/* 0024fa3c: lw v0,0x84(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000084)));
/* 0024fa40: blez v0,0x0024fa54 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0024fa44 */ set(4,cpu(20));if(taken){goto L_0024fa54;}}
/* 0024fa48: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 0024fa4c: sw v0,0x84(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000084)),(uint32_t)cpu(2));
L_0024fa50:;
/* 0024fa50: move a0,s4 */ set(4,cpu(20));
L_0024fa54:;
/* 0024fa54: move a1,s1 */ set(5,cpu(17));
/* 0024fa58: move a2,s2 */ set(6,cpu(18));
/* 0024fa5c: move a3,s0 */ set(7,cpu(16));
/* 0024fa60: jal 0x002636c8 */ set(31,0x0024fa68u);/* delay 0024fa64 */ set(8,cpu(19));body_002636c8();
/* 0024fa68: lw v1,0x28(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 0024fa6c: move a2,s4 */ set(6,cpu(20));
/* 0024fa70: move a0,s1 */ set(4,cpu(17));
/* 0024fa74: lh a1,0x92(v1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));
/* 0024fa78: li a3,0xf */ set(7,sx(UINT32_C(0x0000000f)));
/* 0024fa7c: jal 0x002517e0 */ set(31,0x0024fa84u);/* delay 0024fa80 */ set(8,sx(UINT32_C(0x00000014)));nocturneBattleActionSkillCall(0x002517e0u);
/* 0024fa84: bne s2,zero,0x0024fab0 */ {int taken=(cpu(18)!=cpu(0));/* delay 0024fa88 */ set(2,sx((uint32_t)cpu(16)<<4));if(taken){goto L_0024fab0;}}
/* 0024fa8c: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024fa90: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 0024fa94: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024fa98: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 0024fa9c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024faa0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0024faa4: b 0x0024facc */ /* delay 0024faa8 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000a54)));goto L_0024facc;
L_0024fab0:;
/* 0024fab0: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fab4: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 0024fab8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024fabc: lw a0,0x8(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0024fac0: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 0024fac4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0024fac8: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
L_0024facc:;
/* 0024facc: sll v0,s3,0x3 */ set(2,sx((uint32_t)cpu(19)<<3));
/* 0024fad0: lhu v1,0x6(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000006))));
/* 0024fad4: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 0024fad8: bne s2,zero,0x0024fb00 */ {int taken=(cpu(18)!=cpu(0));/* delay 0024fadc */ sh(ea(2,(int32_t)UINT32_C(0x0000008c)),(uint16_t)cpu(3));if(taken){goto L_0024fb00;}}
/* 0024fae0: lhu a3,0x4(a0) */ set(7,half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 0024fae4: move a0,s1 */ set(4,cpu(17));
/* 0024fae8: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
/* 0024faec: jal 0x002592b0 */ set(31,0x0024faf4u);/* delay 0024faf0 */ set(6,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002592b0u);
/* 0024faf4: b 0x0024fb18 */ /* delay 0024faf8 */ set(2,sx(UINT32_C(0x00000001)));goto L_0024fb18;
L_0024fb00:;
/* 0024fb00: lhu a3,0x4(a0) */ set(7,half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 0024fb04: move a0,s1 */ set(4,cpu(17));
/* 0024fb08: li a1,0x40 */ set(5,sx(UINT32_C(0x00000040)));
/* 0024fb0c: jal 0x002592b0 */ set(31,0x0024fb14u);/* delay 0024fb10 */ set(6,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002592b0u);
/* 0024fb14: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_0024fb18:;
/* 0024fb18: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024fb1c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024fb20: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024fb24: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024fb28: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024fb2c: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024fb30: jr ra */ {uint64_t target=cpu(31);/* delay 0024fb34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_0024F990(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);
body_0024f990();
return cpu(2);
}
static void body_0024fb38(void){
nocturneEffectAxisNoteEntry(0x0024fb38u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0024fb38: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0024fb3c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024fb40: move s0,t1 */ set(16,cpu(9));
/* 0024fb44: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024fb48: move s1,a3 */ set(17,cpu(7));
/* 0024fb4c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024fb50: move s2,a1 */ set(18,cpu(5));
/* 0024fb54: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024fb58: move s3,a0 */ set(19,cpu(4));
/* 0024fb5c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024fb60: sll a2,s1,0x4 */ set(6,sx((uint32_t)cpu(17)<<4));
/* 0024fb64: subu a2,a2,s1 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(17)));
/* 0024fb68: move a1,s3 */ set(5,cpu(19));
/* 0024fb6c: lw v0,0x0(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0024fb70: sll a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)<<4));
/* 0024fb74: move a0,s0 */ set(4,cpu(16));
/* 0024fb78: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0024fb7c: jal 0x00261e80 */ set(31,0x0024fb84u);/* delay 0024fb80 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));body_00261e80();
/* 0024fb84: move a0,s3 */ set(4,cpu(19));
/* 0024fb88: jal 0x0024f5c8 */ set(31,0x0024fb90u);/* delay 0024fb8c */ set(5,cpu(16));nocturneBattleActionSkillCall(0x0024f5c8u);
/* 0024fb90: move a0,s3 */ set(4,cpu(19));
/* 0024fb94: move a1,s1 */ set(5,cpu(17));
/* 0024fb98: move a2,s0 */ set(6,cpu(16));
/* 0024fb9c: li a3,0xa */ set(7,sx(UINT32_C(0x0000000a)));
/* 0024fba0: jal 0x002517e0 */ set(31,0x0024fba8u);/* delay 0024fba4 */ set(8,sx(UINT32_C(0x00000014)));nocturneBattleActionSkillCall(0x002517e0u);
/* 0024fba8: jal 0x0026a448 */ set(31,0x0024fbb0u);/* delay 0024fbac */ set(4,cpu(18));nocturneBattleActionSkillCall(0x0026a448u);
/* 0024fbb0: beq v0,zero,0x0024fbf0 */ {int taken=(cpu(2)==cpu(0));/* delay 0024fbb4 */ set(4,cpu(17));if(taken){goto L_0024fbf0;}}
/* 0024fbb8: jal 0x0026a468 */ set(31,0x0024fbc0u);/* delay 0024fbbc */ nocturneBattleActionSkillCall(0x0026a468u);
/* 0024fbc0: beq v0,zero,0x0024fbe0 */ {int taken=(cpu(2)==cpu(0));/* delay 0024fbc4 */ set(4,cpu(19));if(taken){goto L_0024fbe0;}}
/* 0024fbc8: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 0024fbcc: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 0024fbd0: jal 0x002592b0 */ set(31,0x0024fbd8u);/* delay 0024fbd4 */ set(7,cpu(0));nocturneBattleActionSkillCall(0x002592b0u);
/* 0024fbd8: b 0x0024fbf0 */ /* delay 0024fbdc */ goto L_0024fbf0;
L_0024fbe0:;
/* 0024fbe0: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 0024fbe4: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 0024fbe8: jal 0x002592b0 */ set(31,0x0024fbf0u);/* delay 0024fbec */ set(7,cpu(0));nocturneBattleActionSkillCall(0x002592b0u);
L_0024fbf0:;
/* 0024fbf0: lui at,0xc000 */ set(1,sx(UINT32_C(0xc0000000)));
/* 0024fbf4: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0024fbf8: jal 0x0024f548 */ set(31,0x0024fc00u);/* delay 0024fbfc */ set(4,cpu(19));nocturneBattleActionSkillCall(0x0024f548u);
/* 0024fc00: move a0,s3 */ set(4,cpu(19));
/* 0024fc04: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024fc08: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 0024fc0c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024fc10: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024fc14: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024fc18: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024fc1c: j 0x0024f5b0 */ /* delay 0024fc20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x0024f5b0u);return;
}
void ps2BattleActionSkill_0024FB38(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);set(9,t1);
body_0024fb38();
return;
}
static void body_0024fc28(void){
nocturneEffectAxisNoteEntry(0x0024fc28u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0024fc28: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0024fc2c: li t0,0x3 */ set(8,sx(UINT32_C(0x00000003)));
/* 0024fc30: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024fc34: move s0,a3 */ set(16,cpu(7));
/* 0024fc38: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024fc3c: move s1,a0 */ set(17,cpu(4));
/* 0024fc40: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024fc44: move s2,t1 */ set(18,cpu(9));
/* 0024fc48: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024fc4c: sll a3,s0,0x4 */ set(7,sx((uint32_t)cpu(16)<<4));
/* 0024fc50: subu a3,a3,s0 */ set(7,sx((uint32_t)cpu(7)-(uint32_t)cpu(16)));
/* 0024fc54: move a0,s2 */ set(4,cpu(18));
/* 0024fc58: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fc5c: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0024fc60: move a2,s1 */ set(6,cpu(17));
/* 0024fc64: li a1,0x2d */ set(5,sx(UINT32_C(0x0000002d)));
/* 0024fc68: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0024fc6c: jal 0x002628d0 */ set(31,0x0024fc74u);/* delay 0024fc70 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));nocturneBattleActionSkillCall(0x002628d0u);
/* 0024fc74: move a0,s1 */ set(4,cpu(17));
/* 0024fc78: move a1,s0 */ set(5,cpu(16));
/* 0024fc7c: move a2,s2 */ set(6,cpu(18));
/* 0024fc80: li a3,0xa */ set(7,sx(UINT32_C(0x0000000a)));
/* 0024fc84: jal 0x002517e0 */ set(31,0x0024fc8cu);/* delay 0024fc88 */ set(8,sx(UINT32_C(0x00000014)));nocturneBattleActionSkillCall(0x002517e0u);
/* 0024fc8c: lui at,0xc000 */ set(1,sx(UINT32_C(0xc0000000)));
/* 0024fc90: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0024fc94: jal 0x0024f548 */ set(31,0x0024fc9cu);/* delay 0024fc98 */ set(4,cpu(17));nocturneBattleActionSkillCall(0x0024f548u);
/* 0024fc9c: move a0,s1 */ set(4,cpu(17));
/* 0024fca0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024fca4: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 0024fca8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024fcac: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024fcb0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024fcb4: j 0x0024f5b0 */ /* delay 0024fcb8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x0024f5b0u);return;
}
void ps2BattleActionSkill_0024FC28(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);set(9,t1);
body_0024fc28();
return;
}
static void body_0024fcc0(void){
nocturneEffectAxisNoteEntry(0x0024fcc0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0024fcc0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 0024fcc4: li t0,0x4 */ set(8,sx(UINT32_C(0x00000004)));
/* 0024fcc8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024fccc: li a1,0x2d */ set(5,sx(UINT32_C(0x0000002d)));
/* 0024fcd0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024fcd4: move s1,a0 */ set(17,cpu(4));
/* 0024fcd8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024fcdc: move s2,t1 */ set(18,cpu(9));
/* 0024fce0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024fce4: li s3,0x4 */ set(19,sx(UINT32_C(0x00000004)));
/* 0024fce8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024fcec: move s4,a3 */ set(20,cpu(7));
/* 0024fcf0: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024fcf4: li s5,0x3c0 */ set(21,sx(UINT32_C(0x000003c0)));
/* 0024fcf8: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024fcfc: sll s0,s4,0x4 */ set(16,sx((uint32_t)cpu(20)<<4));
/* 0024fd00: subu s0,s0,s4 */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(20)));
/* 0024fd04: move a0,s2 */ set(4,cpu(18));
/* 0024fd08: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fd0c: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0024fd10: move a2,s1 */ set(6,cpu(17));
/* 0024fd14: lw a3,0x0(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0024fd18: jal 0x002628d0 */ set(31,0x0024fd20u);/* delay 0024fd1c */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(16)));nocturneBattleActionSkillCall(0x002628d0u);
/* 0024fd20: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fd24: move a0,s2 */ set(4,cpu(18));
/* 0024fd28: move a1,s1 */ set(5,cpu(17));
/* 0024fd2c: lw a2,0x0(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0024fd30: jal 0x00263250 */ set(31,0x0024fd38u);/* delay 0024fd34 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(16)));body_00263250();
/* 0024fd38: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fd3c: addiu a0,s2,0x1 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 0024fd40: move t0,zero */ set(8,cpu(0));
/* 0024fd44: lw a2,0x0(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0024fd48: move a1,s1 */ set(5,cpu(17));
/* 0024fd4c: move a3,zero */ set(7,cpu(0));
/* 0024fd50: jal 0x00261d90 */ set(31,0x0024fd58u);/* delay 0024fd54 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(16)));nocturneBattleActionSkillCall(0x00261d90u);
/* 0024fd58: jal 0x00198860 */ set(31,0x0024fd60u);/* delay 0024fd5c */ nocturneBattleActionSkillCall(0x00198860u);
/* 0024fd60: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fd64: addu a0,s2,v0 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 0024fd68: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 0024fd6c: move a1,s1 */ set(5,cpu(17));
/* 0024fd70: lw a2,0x0(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0024fd74: jal 0x002641f8 */ set(31,0x0024fd7cu);/* delay 0024fd78 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(16)));nocturneBattleActionSkillCall(0x002641f8u);
/* 0024fd7c: move a0,s1 */ set(4,cpu(17));
/* 0024fd80: move a2,s2 */ set(6,cpu(18));
/* 0024fd84: move a1,s4 */ set(5,cpu(20));
/* 0024fd88: li a3,0x1e */ set(7,sx(UINT32_C(0x0000001e)));
/* 0024fd8c: jal 0x002517e0 */ set(31,0x0024fd94u);/* delay 0024fd90 */ set(8,sx(UINT32_C(0x0000001e)));nocturneBattleActionSkillCall(0x002517e0u);
/* 0024fd94: jal 0x00198860 */ set(31,0x0024fd9cu);/* delay 0024fd98 */ nocturneBattleActionSkillCall(0x00198860u);
/* 0024fd9c: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_0024fda0:;
/* 0024fda0: beql s3,s4,0x0024fdf8 */ {int taken=(cpu(19)==cpu(20));if(taken){/* delay 0024fda4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));goto L_0024fdf8;}}
/* 0024fda8: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fdac: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0024fdb0: addu a2,v1,s5 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(21)));
/* 0024fdb4: lw v0,0x78(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000078)));
/* 0024fdb8: andi a0,v0,0x2 */ set(4,cpu(2)&UINT32_C(0x00000002));
/* 0024fdbc: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0024fdc0: beql v0,zero,0x0024fdf8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024fdc4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));goto L_0024fdf8;}}
/* 0024fdc8: beq a0,zero,0x0024fdf4 */ {int taken=(cpu(4)==cpu(0));/* delay 0024fdcc */ set(7,sx(UINT32_C(0x0000000e)));if(taken){goto L_0024fdf4;}}
/* 0024fdd0: move a0,s2 */ set(4,cpu(18));
/* 0024fdd4: jal 0x00261ff0 */ set(31,0x0024fddcu);/* delay 0024fdd8 */ set(5,cpu(17));nocturneBattleActionSkillCall(0x00261ff0u);
/* 0024fddc: move a0,s1 */ set(4,cpu(17));
/* 0024fde0: move a1,s3 */ set(5,cpu(19));
/* 0024fde4: move a2,s2 */ set(6,cpu(18));
/* 0024fde8: li a3,0x14 */ set(7,sx(UINT32_C(0x00000014)));
/* 0024fdec: jal 0x002517e0 */ set(31,0x0024fdf4u);/* delay 0024fdf0 */ set(8,sx(UINT32_C(0x00000014)));nocturneBattleActionSkillCall(0x002517e0u);
L_0024fdf4:;
/* 0024fdf4: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
L_0024fdf8:;
/* 0024fdf8: slti v0,s3,0xe */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 0024fdfc: bne v0,zero,0x0024fda0 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024fe00 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x000000f0)));if(taken){goto L_0024fda0;}}
/* 0024fe04: lui at,0xc000 */ set(1,sx(UINT32_C(0xc0000000)));
/* 0024fe08: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0024fe0c: jal 0x0024f548 */ set(31,0x0024fe14u);/* delay 0024fe10 */ set(4,cpu(17));nocturneBattleActionSkillCall(0x0024f548u);
/* 0024fe14: move a0,s1 */ set(4,cpu(17));
/* 0024fe18: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024fe1c: li a1,0xe */ set(5,sx(UINT32_C(0x0000000e)));
/* 0024fe20: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024fe24: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024fe28: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024fe2c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024fe30: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024fe34: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024fe38: j 0x0024f5b0 */ /* delay 0024fe3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x0024f5b0u);return;
}
void ps2BattleActionSkill_0024FCC0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);set(9,t1);
body_0024fcc0();
return;
}
static void body_0024fe40(void){
nocturneEffectAxisNoteEntry(0x0024fe40u);
uint64_t incoming=cpu(31);
/* 0024fe40: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 0024fe44: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024fe48: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0024fe4c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024fe50: move s1,a0 */ set(17,cpu(4));
/* 0024fe54: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024fe58: move s2,a2 */ set(18,cpu(6));
/* 0024fe5c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024fe60: li s3,0x4 */ set(19,sx(UINT32_C(0x00000004)));
/* 0024fe64: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024fe68: li s4,0x3c0 */ set(20,sx(UINT32_C(0x000003c0)));
/* 0024fe6c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024fe70: move s5,zero */ set(21,cpu(0));
/* 0024fe74: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024fe78: move s6,a1 */ set(22,cpu(5));
/* 0024fe7c: nop  */ 
L_0024fe80:;
/* 0024fe80: beql s3,s6,0x0024ff14 */ {int taken=(cpu(19)==cpu(22));if(taken){/* delay 0024fe84 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));goto L_0024ff14;}}
/* 0024fe88: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024fe8c: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0024fe90: addu s0,v1,s4 */ set(16,sx((uint32_t)cpu(3)+(uint32_t)cpu(20)));
/* 0024fe94: lw v0,0x78(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000078)));
/* 0024fe98: andi v1,v0,0x2 */ set(3,cpu(2)&UINT32_C(0x00000002));
/* 0024fe9c: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0024fea0: beql v0,zero,0x0024ff14 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0024fea4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));goto L_0024ff14;}}
/* 0024fea8: beq v1,zero,0x0024ff10 */ {int taken=(cpu(3)==cpu(0));/* delay 0024feac */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));if(taken){goto L_0024ff10;}}
/* 0024feb0: move t0,zero */ set(8,cpu(0));
/* 0024feb4: move a1,s1 */ set(5,cpu(17));
/* 0024feb8: move a2,s0 */ set(6,cpu(16));
/* 0024febc: move a3,zero */ set(7,cpu(0));
/* 0024fec0: jal 0x00261d90 */ set(31,0x0024fec8u);/* delay 0024fec4 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x00261d90u);
/* 0024fec8: jal 0x00198ff8 */ set(31,0x0024fed0u);/* delay 0024fecc */ nocturneBattleActionSkillCall(0x00198ff8u);
/* 0024fed0: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 0024fed4: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 0024fed8: addiu a0,v0,0x1 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0024fedc: move a1,s1 */ set(5,cpu(17));
/* 0024fee0: jal 0x002641f8 */ set(31,0x0024fee8u);/* delay 0024fee4 */ set(6,cpu(16));nocturneBattleActionSkillCall(0x002641f8u);
/* 0024fee8: move a0,s2 */ set(4,cpu(18));
/* 0024feec: move a1,s1 */ set(5,cpu(17));
/* 0024fef0: jal 0x002632d0 */ set(31,0x0024fef8u);/* delay 0024fef4 */ set(6,cpu(16));body_002632d0();
/* 0024fef8: move a0,s1 */ set(4,cpu(17));
/* 0024fefc: move a1,s3 */ set(5,cpu(19));
/* 0024ff00: move a2,s2 */ set(6,cpu(18));
/* 0024ff04: li a3,0x1e */ set(7,sx(UINT32_C(0x0000001e)));
/* 0024ff08: jal 0x002517e0 */ set(31,0x0024ff10u);/* delay 0024ff0c */ set(8,sx(UINT32_C(0x0000001e)));nocturneBattleActionSkillCall(0x002517e0u);
L_0024ff10:;
/* 0024ff10: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
L_0024ff14:;
/* 0024ff14: slti v0,s3,0xe */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 0024ff18: bne v0,zero,0x0024fe80 */ {int taken=(cpu(2)!=cpu(0));/* delay 0024ff1c */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x000000f0)));if(taken){goto L_0024fe80;}}
/* 0024ff20: blez s5,0x0024ff38 */ {int taken=((int64_t)cpu(21)<=0);/* delay 0024ff24 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0024ff38;}}
/* 0024ff28: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024ff2c: lw v0,0x60(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000060)));
/* 0024ff30: ori v0,v0,0x4000 */ set(2,cpu(2)|UINT32_C(0x00004000));
/* 0024ff34: sw v0,0x60(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(2));
L_0024ff38:;
/* 0024ff38: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0024ff3c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024ff40: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0024ff44: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024ff48: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0024ff4c: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0024ff50: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0024ff54: jr ra */ {uint64_t target=cpu(31);/* delay 0024ff58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_0024FE40(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_0024fe40();
return;
}
static void body_00251770(void){
nocturneEffectAxisNoteEntry(0x00251770u);
uint64_t incoming=cpu(31);
/* 00251770: sll v0,a1,0x3 */ set(2,sx((uint32_t)cpu(5)<<3));
/* 00251774: addiu v1,a0,0xa */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x0000000a)));
/* 00251778: move a1,v0 */ set(5,cpu(2));
/* 0025177c: addiu v0,v0,0x80 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000080)));
/* 00251780: addu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 00251784: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00251788: addu t1,a2,a3 */ set(9,sx((uint32_t)cpu(6)+(uint32_t)cpu(7)));
/* 0025178c: addu a2,a2,t0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(8)));
/* 00251790: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00251794: bltz a3,0x002517ac */ {int taken=((int64_t)cpu(7)<0);/* delay 00251798 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000088)));if(taken){goto L_002517ac;}}
/* 0025179c: lhu v0,0x0(a1) */ set(2,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002517a0: slt v0,v0,t1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(9));
/* 002517a4: bnel v0,zero,0x002517ac */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002517a8 */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(9));goto L_002517ac;}}
L_002517ac:;
/* 002517ac: bltz t0,0x002517d8 */ {int taken=((int64_t)cpu(8)<0);/* delay 002517b0 */ if(taken){goto L_002517d8;}}
/* 002517b4: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 002517b8: slt v0,v0,a2 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(6));
/* 002517bc: bnel v0,zero,0x002517c4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002517c0 */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(6));goto L_002517c4;}}
L_002517c4:;
/* 002517c4: lhu a0,0x8(a0) */ set(4,half(ea(4,(int32_t)UINT32_C(0x00000008))));
/* 002517c8: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 002517cc: sltu v0,v0,a0 */ set(2,cpu(2)<cpu(4));
/* 002517d0: bnel v0,zero,0x002517d8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002517d4 */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));goto L_002517d8;}}
L_002517d8:;
/* 002517d8: jr ra */ {uint64_t target=cpu(31);/* delay 002517dc */ checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00251770(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);
body_00251770();
return;
}
static void body_002518c8(void){
nocturneEffectAxisNoteEntry(0x002518c8u);
uint64_t incoming=cpu(31);
/* 002518c8: addiu sp,sp,-0xa0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff60)));
/* 002518cc: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002518d0: sd s5,0x78(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002518d4: move s5,a1 */ set(21,cpu(5));
/* 002518d8: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002518dc: move v0,s5 */ set(2,cpu(21));
/* 002518e0: sd s4,0x70(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002518e4: sd s6,0x80(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002518e8: sd ra,0x98(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002518ec: sd s1,0x58(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002518f0: li s1,0x1f */ set(17,sx(UINT32_C(0x0000001f)));
/* 002518f4: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002518f8: move s2,a2 */ set(18,cpu(6));
/* 002518fc: sd s3,0x68(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00251900: move s3,a0 */ set(19,cpu(4));
/* 00251904: sd s7,0x88(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 00251908: move s7,a3 */ set(23,cpu(7));
/* 0025190c: sd s8,0x90(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 00251910: li s8,0x65 */ set(30,sx(UINT32_C(0x00000065)));
/* 00251914: nop  */ 
L_00251918:;
/* 00251918: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
/* 0025191c: sb v1,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
/* 00251920: sb zero,0x1(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));
/* 00251924: nop  */ 
/* 00251928: nop  */ 
/* 0025192c: bgez s1,0x00251918 */ {int taken=((int64_t)cpu(17)>=0);/* delay 00251930 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));if(taken){goto L_00251918;}}
/* 00251934: lw v0,0x44(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000044)));
/* 00251938: bne v0,zero,0x00251ec0 */ {int taken=(cpu(2)!=cpu(0));/* delay 0025193c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));if(taken){goto L_00251ec0;}}
/* 00251940: sll v0,s7,0x4 */ set(2,sx((uint32_t)cpu(23)<<4));
/* 00251944: sw v0,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 00251948: subu v0,v0,s7 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(23)));
/* 0025194c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00251950: lui at,0x3d */ set(1,sx(UINT32_C(0x003d0000)));
/* 00251954: addiu at,at,0x79a8 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x000079a8)));
/* 00251958: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 0025195c: lbu a1,0x5(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000005))));
/* 00251960: lbu s0,0x4(v0) */ set(16,byte(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 00251964: slt v1,s0,a1 */ set(3,(int64_t)cpu(16)<(int64_t)cpu(5));
/* 00251968: beq v1,zero,0x00251984 */ {int taken=(cpu(3)==cpu(0));/* delay 0025196c */ set(22,cpu(16));if(taken){goto L_00251984;}}
/* 00251970: subu a1,a1,s0 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(16)));
/* 00251974: move a0,zero */ set(4,cpu(0));
/* 00251978: jal 0x002c0c60 */ set(31,0x00251980u);/* delay 0025197c */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002c0c60u);
/* 00251980: addu s6,s0,v0 */ set(22,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
L_00251984:;
/* 00251984: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00251988: move a1,s6 */ set(5,cpu(22));
/* 0025198c: addiu a0,a0,0x37f8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000037f8)));
/* 00251990: jal 0x002d4748 */ set(31,0x00251998u);/* delay 00251994 */ set(6,cpu(18));nocturneBattleActionSkillCall(0x002d4748u);
/* 00251998: move s1,zero */ set(17,cpu(0));
/* 0025199c: move s4,zero */ set(20,cpu(0));
L_002519a0:;
/* 002519a0: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002519a4: sllv s0,v1,s1 */ set(16,sx((uint32_t)((uint32_t)cpu(3)<<((uint32_t)cpu(17)&31u))));
/* 002519a8: and v0,s2,s0 */ set(2,cpu(18)&cpu(16));
/* 002519ac: beql v0,zero,0x00251a14 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002519b0 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00251a14;}}
/* 002519b4: lw a1,0x0(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 002519b8: lw v0,0x0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002519bc: addu a0,s4,v0 */ set(4,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 002519c0: lw v1,0x78(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000078)));
/* 002519c4: andi v0,v1,0x1 */ set(2,cpu(3)&UINT32_C(0x00000001));
/* 002519c8: beq v0,zero,0x00251a10 */ {int taken=(cpu(2)==cpu(0));/* delay 002519cc */ set(2,cpu(3)&UINT32_C(0x00000040));if(taken){goto L_00251a10;}}
/* 002519d0: beql v0,zero,0x00251a14 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002519d4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00251a14;}}
/* 002519d8: lh v0,0x90(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000090))));
/* 002519dc: lw a0,0x10(a1) */ lw(4,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 002519e0: sll v0,v0,0x7 */ set(2,sx((uint32_t)cpu(2)<<7));
/* 002519e4: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002519e8: lhu v1,0x0(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002519ec: andi v1,v1,0x20 */ set(3,cpu(3)&UINT32_C(0x00000020));
/* 002519f0: bne v1,zero,0x00251a0c */ {int taken=(cpu(3)!=cpu(0));/* delay 002519f4 */ set(2,~(cpu(0)|cpu(16)));if(taken){goto L_00251a0c;}}
/* 002519f8: move a0,s3 */ set(4,cpu(19));
/* 002519fc: jal 0x002515e8 */ set(31,0x00251a04u);/* delay 00251a00 */ set(5,cpu(17));nocturneBattleActionSkillCall(0x002515e8u);
/* 00251a04: beq v0,zero,0x00251a10 */ {int taken=(cpu(2)==cpu(0));/* delay 00251a08 */ set(2,~(cpu(0)|cpu(16)));if(taken){goto L_00251a10;}}
L_00251a0c:;
/* 00251a0c: and s2,s2,v0 */ set(18,cpu(18)&cpu(2));
L_00251a10:;
/* 00251a10: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00251a14:;
/* 00251a14: slti v0,s1,0x10 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00251a18: bne v0,zero,0x002519a0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00251a1c */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x000000f0)));if(taken){goto L_002519a0;}}
/* 00251a20: lw a1,0x44(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 00251a24: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 00251a28: addiu v1,v1,0x7998 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00007998)));
/* 00251a2c: subu v0,a1,s7 */ set(2,sx((uint32_t)cpu(5)-(uint32_t)cpu(23)));
/* 00251a30: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00251a34: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00251a38: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00251a3c: lbu a0,0xb(v0) */ set(4,byte(ea(2,(int32_t)UINT32_C(0x0000000b))));
/* 00251a40: bne a0,a1,0x00251ba8 */ {int taken=(cpu(4)!=cpu(5));/* delay 00251a44 */ set(2,sx((uint32_t)cpu(23)+UINT32_C(0xffffff62)));if(taken){goto L_00251ba8;}}
/* 00251a48: move s4,zero */ set(20,cpu(0));
/* 00251a4c: move s1,zero */ set(17,cpu(0));
/* 00251a50: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00251a54: move v1,sp */ set(3,cpu(29));
/* 00251a58: sllv v0,a0,s1 */ set(2,sx((uint32_t)((uint32_t)cpu(4)<<((uint32_t)cpu(17)&31u))));
/* 00251a5c: nop  */ 
L_00251a60:;
/* 00251a60: and v0,s2,v0 */ set(2,cpu(18)&cpu(2));
/* 00251a64: beql v0,zero,0x00251a80 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00251a68 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00251a80;}}
/* 00251a6c: sb s1,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
/* 00251a70: addiu s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
/* 00251a74: sb zero,0x1(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));
/* 00251a78: addiu v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000002)));
/* 00251a7c: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00251a80:;
/* 00251a80: slti v0,s1,0x20 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000020));
/* 00251a84: bnel v0,zero,0x00251a60 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251a88 */ set(2,sx((uint32_t)((uint32_t)cpu(4)<<((uint32_t)cpu(17)&31u))));goto L_00251a60;}}
/* 00251a8c: beql s4,zero,0x00251ec0 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00251a90 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_00251ec0;}}
/* 00251a94: move a0,zero */ set(4,cpu(0));
/* 00251a98: jal 0x002c0c60 */ set(31,0x00251aa0u);/* delay 00251a9c */ set(5,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x002c0c60u);
/* 00251aa0: li s8,-0x1 */ set(30,sx(UINT32_C(0xffffffff)));
/* 00251aa4: addu v0,s4,v0 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 00251aa8: move s3,zero */ set(19,cpu(0));
/* 00251aac: sw v0,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
/* 00251ab0: blez s6,0x00251ebc */ {int taken=((int64_t)cpu(22)<=0);/* delay 00251ab4 */ set(18,cpu(0));if(taken){goto L_00251ebc;}}
/* 00251ab8: slti s7,s4,0x2 */ set(23,(int64_t)cpu(20)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00251abc: move s1,s5 */ set(17,cpu(21));
/* 00251ac0: move a0,zero */ set(4,cpu(0));
/* 00251ac4: nop  */ 
L_00251ac8:;
/* 00251ac8: jal 0x002c0c60 */ set(31,0x00251ad0u);/* delay 00251acc */ set(5,cpu(20));nocturneBattleActionSkillCall(0x002c0c60u);
/* 00251ad0: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 00251ad4: addu v0,sp,v1 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(3)));
/* 00251ad8: bne s7,zero,0x00251ae8 */ {int taken=(cpu(23)!=cpu(0));/* delay 00251adc */ set(16,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_00251ae8;}}
/* 00251ae0: beq s8,s0,0x00251ac8 */ {int taken=(cpu(30)==cpu(16));/* delay 00251ae4 */ set(4,cpu(0));if(taken){goto L_00251ac8;}}
L_00251ae8:;
/* 00251ae8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 00251aec: lw a1,0x40(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00251af0: addu v1,sp,v1 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(3)));
/* 00251af4: move s8,s0 */ set(30,cpu(16));
/* 00251af8: lb v0,0x0(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00251afc: slt v0,v0,a1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(5));
/* 00251b00: beq v0,zero,0x00251b8c */ {int taken=(cpu(2)==cpu(0));/* delay 00251b04 */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_00251b8c;}}
/* 00251b08: addiu v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00251b0c: move a1,zero */ set(5,cpu(0));
/* 00251b10: blez s3,0x00251b54 */ {int taken=((int64_t)cpu(19)<=0);/* delay 00251b14 */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));if(taken){goto L_00251b54;}}
/* 00251b18: lb v0,0x0(s5) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(21,(int32_t)UINT32_C(0x00000000))));
/* 00251b1c: beq v0,s0,0x00251b54 */ {int taken=(cpu(2)==cpu(16));/* delay 00251b20 */ if(taken){goto L_00251b54;}}
/* 00251b24: move a0,s5 */ set(4,cpu(21));
/* 00251b28: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 00251b2c: nop  */ 
L_00251b30:;
/* 00251b30: slt v0,a1,s3 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(19));
/* 00251b34: beq v0,zero,0x00251b54 */ {int taken=(cpu(2)==cpu(0));/* delay 00251b38 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));if(taken){goto L_00251b54;}}
/* 00251b3c: lb v0,0x0(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00251b40: nop  */ 
/* 00251b44: nop  */ 
/* 00251b48: nop  */ 
/* 00251b4c: bnel v0,s0,0x00251b30 */ {int taken=(cpu(2)!=cpu(16));if(taken){/* delay 00251b50 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));goto L_00251b30;}}
L_00251b54:;
/* 00251b54: bnel a1,s3,0x00251b78 */ {int taken=(cpu(5)!=cpu(19));if(taken){/* delay 00251b58 */ set(3,sx((uint32_t)cpu(5)<<1));goto L_00251b78;}}
/* 00251b5c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00251b60: sb s0,0x0(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(16));
/* 00251b64: sb v0,0x1(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
/* 00251b68: addiu s1,s1,0x2 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000002)));
/* 00251b6c: b 0x00251b8c */ /* delay 00251b70 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));goto L_00251b8c;
L_00251b78:;
/* 00251b78: addu v1,v1,s5 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(21)));
/* 00251b7c: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 00251b80: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00251b84: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00251b88: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
L_00251b8c:;
/* 00251b8c: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 00251b90: slt v0,s2,s6 */ set(2,(int64_t)cpu(18)<(int64_t)cpu(22));
/* 00251b94: bnel v0,zero,0x00251ac8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251b98 */ set(4,cpu(0));goto L_00251ac8;}}
/* 00251b9c: b 0x00251ec0 */ /* delay 00251ba0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_00251ec0;
L_00251ba8:;
/* 00251ba8: sltiu v0,v0,0x2 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00251bac: beql v0,zero,0x00251cd0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00251bb0 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));goto L_00251cd0;}}
/* 00251bb4: sb zero,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 00251bb8: move s4,zero */ set(20,cpu(0));
/* 00251bbc: move s1,zero */ set(17,cpu(0));
/* 00251bc0: li s6,0x1 */ set(22,sx(UINT32_C(0x00000001)));
/* 00251bc4: move s0,zero */ set(16,cpu(0));
L_00251bc8:;
/* 00251bc8: sllv v0,s6,s1 */ set(2,sx((uint32_t)((uint32_t)cpu(22)<<((uint32_t)cpu(17)&31u))));
/* 00251bcc: and v0,s2,v0 */ set(2,cpu(18)&cpu(2));
/* 00251bd0: beql v0,zero,0x00251c74 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00251bd4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00251c74;}}
/* 00251bd8: lw v0,0x0(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 00251bdc: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00251be0: addu a0,s0,v1 */ set(4,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 00251be4: lw v1,0x78(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000078)));
/* 00251be8: andi v0,v1,0x1 */ set(2,cpu(3)&UINT32_C(0x00000001));
/* 00251bec: beq v0,zero,0x00251c70 */ {int taken=(cpu(2)==cpu(0));/* delay 00251bf0 */ set(2,cpu(3)&UINT32_C(0x00000040));if(taken){goto L_00251c70;}}
/* 00251bf4: beql v0,zero,0x00251c74 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00251bf8 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00251c74;}}
/* 00251bfc: jal 0x00246ab8 */ set(31,0x00251c04u);/* delay 00251c00 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x00246ab8u);
/* 00251c04: move a0,v0 */ set(4,cpu(2));
/* 00251c08: lhu v0,0x6(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000006))));
/* 00251c0c: beq v0,zero,0x00251c70 */ {int taken=(cpu(2)==cpu(0));/* delay 00251c10 */ set(3,cpu(2));if(taken){goto L_00251c70;}}
/* 00251c14: lhu a0,0x8(a0) */ set(4,half(ea(4,(int32_t)UINT32_C(0x00000008))));
/* 00251c18: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 00251c1c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00251c20: beql a0,zero,0x00251c28 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00251c24 */ nocturneCompilerArithmeticTrap(7u);goto L_00251c28;}}
L_00251c28:;
/* 00251c28: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00251c2c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00251c30: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00251c34: div v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),1,0);
/* 00251c38: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00251c3c: slt v1,v0,s8 */ set(3,(int64_t)cpu(2)<(int64_t)cpu(30));
/* 00251c40: beq v1,zero,0x00251c58 */ {int taken=(cpu(3)==cpu(0));/* delay 00251c44 */ if(taken){goto L_00251c58;}}
/* 00251c48: move s8,v0 */ set(30,cpu(2));
/* 00251c4c: sb s1,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
/* 00251c50: b 0x00251c70 */ /* delay 00251c54 */ set(20,sx(UINT32_C(0x00000001)));goto L_00251c70;
L_00251c58:;
/* 00251c58: bnel s8,v0,0x00251c74 */ {int taken=(cpu(30)!=cpu(2));if(taken){/* delay 00251c5c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00251c74;}}
/* 00251c60: sll v1,s4,0x1 */ set(3,sx((uint32_t)cpu(20)<<1));
/* 00251c64: addiu s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
/* 00251c68: addu v0,sp,v1 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(3)));
/* 00251c6c: sb s1,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
L_00251c70:;
/* 00251c70: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00251c74:;
/* 00251c74: slti v0,s1,0x10 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00251c78: bne v0,zero,0x00251bc8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00251c7c */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000000f0)));if(taken){goto L_00251bc8;}}
/* 00251c80: blezl s4,0x00251cb0 */ {int taken=((int64_t)cpu(20)<=0);if(taken){/* delay 00251c84 */ set(17,cpu(0));goto L_00251cb0;}}
/* 00251c88: sll a1,s4,0x2 */ set(5,sx((uint32_t)cpu(20)<<2));
/* 00251c8c: move a0,zero */ set(4,cpu(0));
/* 00251c90: addu a1,a1,s4 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(20)));
/* 00251c94: jal 0x002c0c60 */ set(31,0x00251c9cu);/* delay 00251c98 */ set(5,sx((uint32_t)cpu(5)<<1));nocturneBattleActionSkillCall(0x002c0c60u);
/* 00251c9c: beql s4,zero,0x00251ca4 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00251ca0 */ nocturneCompilerArithmeticTrap(7u);goto L_00251ca4;}}
L_00251ca4:;
/* 00251ca4: div v0,s4 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(20),1,0);
/* 00251ca8: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 00251cac: move s1,v1 */ set(17,cpu(3));
L_00251cb0:;
/* 00251cb0: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00251cb4: sll v0,s1,0x1 */ set(2,sx((uint32_t)cpu(17)<<1));
/* 00251cb8: sb v1,0x1(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(3));
/* 00251cbc: addu a0,sp,v0 */ set(4,sx((uint32_t)cpu(29)+(uint32_t)cpu(2)));
/* 00251cc0: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00251cc4: b 0x00251ebc */ /* delay 00251cc8 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_00251ebc;
L_00251cd0:;
/* 00251cd0: sll v1,s7,0x2 */ set(3,sx((uint32_t)cpu(23)<<2));
/* 00251cd4: lui at,0x3e */ set(1,sx(UINT32_C(0x003e0000)));
/* 00251cd8: addu at,at,v1 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(3)));
/* 00251cdc: lbu v1,-0x42df(at) */ set(3,byte(ea(1,(int32_t)UINT32_C(0xffffbd21))));
/* 00251ce0: lw v0,0x60(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000060)));
/* 00251ce4: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 00251ce8: beq v0,zero,0x00251d5c */ {int taken=(cpu(2)==cpu(0));/* delay 00251cec */ set(2,sx(UINT32_C(0x000000cc)));if(taken){goto L_00251d5c;}}
/* 00251cf0: bne s7,v0,0x00251d60 */ {int taken=(cpu(23)!=cpu(2));/* delay 00251cf4 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));if(taken){goto L_00251d60;}}
/* 00251cf8: addiu a0,v1,-0x4 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0xfffffffc)));
/* 00251cfc: sltiu v0,a0,0x8 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));
/* 00251d00: beq v0,zero,0x00251d60 */ {int taken=(cpu(2)==cpu(0));/* delay 00251d04 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));if(taken){goto L_00251d60;}}
/* 00251d08: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00251d0c: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00251d10: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00251d14: lw v1,0x3820(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003820)));
/* 00251d18: jr v1 */ {uint64_t target=cpu(3);/* delay 00251d1c */ switch((uint32_t)target){case 0x00251d20u:goto L_00251d20;case 0x00251d28u:goto L_00251d28;case 0x00251d30u:goto L_00251d30;case 0x00251d38u:goto L_00251d38;case 0x00251d40u:goto L_00251d40;case 0x00251d48u:goto L_00251d48;case 0x00251d50u:goto L_00251d50;case 0x00251d58u:goto L_00251d58;default:abort();}}
L_00251d20:;
/* 00251d20: b 0x00251d5c */ /* delay 00251d24 */ set(3,sx(UINT32_C(0x00000008)));goto L_00251d5c;
L_00251d28:;
/* 00251d28: b 0x00251d5c */ /* delay 00251d2c */ set(3,sx(UINT32_C(0x00000009)));goto L_00251d5c;
L_00251d30:;
/* 00251d30: b 0x00251d5c */ /* delay 00251d34 */ set(3,sx(UINT32_C(0x0000000a)));goto L_00251d5c;
L_00251d38:;
/* 00251d38: b 0x00251d5c */ /* delay 00251d3c */ set(3,sx(UINT32_C(0x0000000b)));goto L_00251d5c;
L_00251d40:;
/* 00251d40: b 0x00251d5c */ /* delay 00251d44 */ set(3,sx(UINT32_C(0x00000004)));goto L_00251d5c;
L_00251d48:;
/* 00251d48: b 0x00251d5c */ /* delay 00251d4c */ set(3,sx(UINT32_C(0x00000005)));goto L_00251d5c;
L_00251d50:;
/* 00251d50: b 0x00251d5c */ /* delay 00251d54 */ set(3,sx(UINT32_C(0x00000006)));goto L_00251d5c;
L_00251d58:;
/* 00251d58: li v1,0x7 */ set(3,sx(UINT32_C(0x00000007)));
L_00251d5c:;
/* 00251d5c: sltiu v0,v1,0x10 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
L_00251d60:;
/* 00251d60: beq v0,zero,0x00251ec0 */ {int taken=(cpu(2)==cpu(0));/* delay 00251d64 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));if(taken){goto L_00251ec0;}}
/* 00251d68: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 00251d6c: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00251d70: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00251d74: lw v1,0x3840(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003840)));
/* 00251d78: jr v1 */ {uint64_t target=cpu(3);/* delay 00251d7c */ switch((uint32_t)target){case 0x00251d80u:goto L_00251d80;case 0x00251dc0u:goto L_00251dc0;case 0x00251e00u:goto L_00251e00;default:abort();}}
L_00251d80:;
/* 00251d80: move a1,s5 */ set(5,cpu(21));
/* 00251d84: move s1,zero */ set(17,cpu(0));
/* 00251d88: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00251d8c: sllv v0,v1,s1 */ set(2,sx((uint32_t)((uint32_t)cpu(3)<<((uint32_t)cpu(17)&31u))));
L_00251d90:;
/* 00251d90: and v0,s2,v0 */ set(2,cpu(18)&cpu(2));
/* 00251d94: beql v0,zero,0x00251dac */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00251d98 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00251dac;}}
/* 00251d9c: sb s1,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
/* 00251da0: sb s6,0x1(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(22));
/* 00251da4: addiu a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 00251da8: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00251dac:;
/* 00251dac: slti v0,s1,0x20 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000020));
/* 00251db0: bne v0,zero,0x00251d90 */ {int taken=(cpu(2)!=cpu(0));/* delay 00251db4 */ set(2,sx((uint32_t)((uint32_t)cpu(3)<<((uint32_t)cpu(17)&31u))));if(taken){goto L_00251d90;}}
/* 00251db8: b 0x00251ec0 */ /* delay 00251dbc */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_00251ec0;
L_00251dc0:;
/* 00251dc0: move a1,s5 */ set(5,cpu(21));
/* 00251dc4: li s1,0x1f */ set(17,sx(UINT32_C(0x0000001f)));
/* 00251dc8: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00251dcc: sllv v0,v1,s1 */ set(2,sx((uint32_t)((uint32_t)cpu(3)<<((uint32_t)cpu(17)&31u))));
L_00251dd0:;
/* 00251dd0: and v0,s2,v0 */ set(2,cpu(18)&cpu(2));
/* 00251dd4: beql v0,zero,0x00251dec */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00251dd8 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));goto L_00251dec;}}
/* 00251ddc: sb s1,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
/* 00251de0: sb s6,0x1(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(22));
/* 00251de4: addiu a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 00251de8: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
L_00251dec:;
/* 00251dec: bgez s1,0x00251dd0 */ {int taken=((int64_t)cpu(17)>=0);/* delay 00251df0 */ set(2,sx((uint32_t)((uint32_t)cpu(3)<<((uint32_t)cpu(17)&31u))));if(taken){goto L_00251dd0;}}
/* 00251df4: b 0x00251ec0 */ /* delay 00251df8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_00251ec0;
L_00251e00:;
/* 00251e00: move s4,zero */ set(20,cpu(0));
/* 00251e04: move s1,zero */ set(17,cpu(0));
/* 00251e08: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00251e0c: move v1,s5 */ set(3,cpu(21));
/* 00251e10: sllv v0,a0,s1 */ set(2,sx((uint32_t)((uint32_t)cpu(4)<<((uint32_t)cpu(17)&31u))));
/* 00251e14: nop  */ 
L_00251e18:;
/* 00251e18: and v0,s2,v0 */ set(2,cpu(18)&cpu(2));
/* 00251e1c: beql v0,zero,0x00251e38 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00251e20 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_00251e38;}}
/* 00251e24: sb s1,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
/* 00251e28: addiu s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
/* 00251e2c: sb s6,0x1(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(22));
/* 00251e30: addiu v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000002)));
/* 00251e34: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00251e38:;
/* 00251e38: slti v0,s1,0x20 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000020));
/* 00251e3c: bne v0,zero,0x00251e18 */ {int taken=(cpu(2)!=cpu(0));/* delay 00251e40 */ set(2,sx((uint32_t)((uint32_t)cpu(4)<<((uint32_t)cpu(17)&31u))));if(taken){goto L_00251e18;}}
/* 00251e44: slti v0,s4,0x2 */ set(2,(int64_t)cpu(20)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00251e48: bne v0,zero,0x00251ec0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00251e4c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));if(taken){goto L_00251ec0;}}
/* 00251e50: move s1,zero */ set(17,cpu(0));
/* 00251e54: move a0,zero */ set(4,cpu(0));
L_00251e58:;
/* 00251e58: jal 0x002c0c60 */ set(31,0x00251e60u);/* delay 00251e5c */ set(5,cpu(20));nocturneBattleActionSkillCall(0x002c0c60u);
/* 00251e60: move a0,zero */ set(4,cpu(0));
/* 00251e64: move a1,s4 */ set(5,cpu(20));
/* 00251e68: jal 0x002c0c60 */ set(31,0x00251e70u);/* delay 00251e6c */ set(16,cpu(2));nocturneBattleActionSkillCall(0x002c0c60u);
/* 00251e70: sll v1,s0,0x1 */ set(3,sx((uint32_t)cpu(16)<<1));
/* 00251e74: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00251e78: move s2,zero */ set(18,cpu(0));
/* 00251e7c: addu a3,v1,s5 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(21)));
/* 00251e80: addu a2,v0,s5 */ set(6,sx((uint32_t)cpu(2)+(uint32_t)cpu(21)));
/* 00251e84: nop  */ 
L_00251e88:;
/* 00251e88: addu v1,a3,s2 */ set(3,sx((uint32_t)cpu(7)+(uint32_t)cpu(18)));
/* 00251e8c: addu a0,a2,s2 */ set(4,sx((uint32_t)cpu(6)+(uint32_t)cpu(18)));
/* 00251e90: lb s3,0x0(v1) */ set(19,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00251e94: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 00251e98: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00251e9c: slti a1,s2,0x2 */ set(5,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00251ea0: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 00251ea4: bne a1,zero,0x00251e88 */ {int taken=(cpu(5)!=cpu(0));/* delay 00251ea8 */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(19));if(taken){goto L_00251e88;}}
/* 00251eac: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 00251eb0: slti v0,s1,0x20 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000020));
/* 00251eb4: bnel v0,zero,0x00251e58 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251eb8 */ set(4,cpu(0));goto L_00251e58;}}
L_00251ebc:;
/* 00251ebc: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
L_00251ec0:;
/* 00251ec0: ld s1,0x58(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00251ec4: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00251ec8: ld s3,0x68(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00251ecc: ld s4,0x70(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 00251ed0: ld s5,0x78(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00251ed4: ld s6,0x80(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00251ed8: ld s7,0x88(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 00251edc: ld s8,0x90(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 00251ee0: ld ra,0x98(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00251ee4: jr ra */ {uint64_t target=cpu(31);/* delay 00251ee8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000a0)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_002518C8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_002518c8();
return;
}
static void body_00252060(void){
nocturneEffectAxisNoteEntry(0x00252060u);
uint64_t incoming=cpu(31);
/* 00252060: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00252064: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00252068: move s0,a0 */ set(16,cpu(4));
/* 0025206c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00252070: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00252074: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00252078: lw v1,0x30(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000030)));
/* 0025207c: slti v1,v1,0x4 */ set(3,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 00252080: beq v1,zero,0x002521ac */ {int taken=(cpu(3)==cpu(0));/* delay 00252084 */ set(2,cpu(0));if(taken){goto L_002521ac;}}
/* 00252088: jal 0x0028fa80 */ set(31,0x00252090u);/* delay 0025208c */ nocturneBattleActionSkillCall(0x0028fa80u);
/* 00252090: move a0,s0 */ set(4,cpu(16));
/* 00252094: move s2,v0 */ set(18,cpu(2));
/* 00252098: jal 0x002515e8 */ set(31,0x002520a0u);/* delay 0025209c */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(18,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002515e8u);
/* 002520a0: bne v0,zero,0x002521ac */ {int taken=(cpu(2)!=cpu(0));/* delay 002520a4 */ set(2,cpu(0));if(taken){goto L_002521ac;}}
/* 002520a8: jal 0x00246ab8 */ set(31,0x002520b0u);/* delay 002520ac */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(18,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x00246ab8u);
/* 002520b0: li a0,0x123 */ set(4,sx(UINT32_C(0x00000123)));
/* 002520b4: lhu v1,0x4(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 002520b8: bne v1,a0,0x002521ac */ {int taken=(cpu(3)!=cpu(4));/* delay 002520bc */ set(2,cpu(0));if(taken){goto L_002521ac;}}
/* 002520c0: li a0,0x851 */ set(4,sx(UINT32_C(0x00000851)));
/* 002520c4: jal 0x001e0f50 */ set(31,0x002520ccu);/* delay 002520c8 */ set(17,cpu(0));nocturneBattleActionSkillCall(0x001e0f50u);
/* 002520cc: beq v0,zero,0x002520e0 */ {int taken=(cpu(2)==cpu(0));/* delay 002520d0 */ set(3,sx(UINT32_C(0x00010000)));if(taken){goto L_002520e0;}}
/* 002520d4: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002520d8: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002520dc: sltu s1,zero,v0 */ set(17,cpu(0)<cpu(2));
L_002520e0:;
/* 002520e0: jal 0x001e0f50 */ set(31,0x002520e8u);/* delay 002520e4 */ set(4,sx(UINT32_C(0x00000852)));nocturneBattleActionSkillCall(0x001e0f50u);
/* 002520e8: beq v0,zero,0x00252100 */ {int taken=(cpu(2)==cpu(0));/* delay 002520ec */ set(3,sx(UINT32_C(0x00020000)));if(taken){goto L_00252100;}}
/* 002520f0: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002520f4: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002520f8: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002520fc: movn s1,a0,v0 */ if(cpu(2)!=0){set(17,cpu(4));}
L_00252100:;
/* 00252100: jal 0x001e0f50 */ set(31,0x00252108u);/* delay 00252104 */ set(4,sx(UINT32_C(0x00000853)));nocturneBattleActionSkillCall(0x001e0f50u);
/* 00252108: beq v0,zero,0x00252120 */ {int taken=(cpu(2)==cpu(0));/* delay 0025210c */ set(3,sx(UINT32_C(0x00040000)));if(taken){goto L_00252120;}}
/* 00252110: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00252114: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00252118: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 0025211c: movn s1,a0,v0 */ if(cpu(2)!=0){set(17,cpu(4));}
L_00252120:;
/* 00252120: jal 0x001e0f50 */ set(31,0x00252128u);/* delay 00252124 */ set(4,sx(UINT32_C(0x00000854)));nocturneBattleActionSkillCall(0x001e0f50u);
/* 00252128: beq v0,zero,0x00252140 */ {int taken=(cpu(2)==cpu(0));/* delay 0025212c */ set(3,sx(UINT32_C(0x00080000)));if(taken){goto L_00252140;}}
/* 00252130: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00252134: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00252138: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 0025213c: movn s1,a0,v0 */ if(cpu(2)!=0){set(17,cpu(4));}
L_00252140:;
/* 00252140: jal 0x001e0f50 */ set(31,0x00252148u);/* delay 00252144 */ set(4,sx(UINT32_C(0x00000855)));nocturneBattleActionSkillCall(0x001e0f50u);
/* 00252148: beq v0,zero,0x00252160 */ {int taken=(cpu(2)==cpu(0));/* delay 0025214c */ set(3,sx(UINT32_C(0x00100000)));if(taken){goto L_00252160;}}
/* 00252150: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00252154: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00252158: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 0025215c: movn s1,a0,v0 */ if(cpu(2)!=0){set(17,cpu(4));}
L_00252160:;
/* 00252160: jal 0x001e0f50 */ set(31,0x00252168u);/* delay 00252164 */ set(4,sx(UINT32_C(0x00000856)));nocturneBattleActionSkillCall(0x001e0f50u);
/* 00252168: beq v0,zero,0x00252180 */ {int taken=(cpu(2)==cpu(0));/* delay 0025216c */ set(3,sx(UINT32_C(0x00200000)));if(taken){goto L_00252180;}}
/* 00252170: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00252174: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00252178: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 0025217c: movn s1,a0,v0 */ if(cpu(2)!=0){set(17,cpu(4));}
L_00252180:;
/* 00252180: beq s1,zero,0x002521ac */ {int taken=(cpu(17)==cpu(0));/* delay 00252184 */ set(2,cpu(0));if(taken){goto L_002521ac;}}
/* 00252188: lh a1,0x90(s2) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(18,(int32_t)UINT32_C(0x00000090))));
/* 0025218c: li a0,0x4 */ set(4,sx(UINT32_C(0x00000004)));
/* 00252190: lw a2,0x30(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000030)));
/* 00252194: jal 0x00247ed8 */ set(31,0x0025219cu);/* delay 00252198 */ set(7,sx(UINT32_C(0x000000f3)));nocturneBattleActionSkillCall(0x00247ed8u);
/* 0025219c: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 002521a0: jal 0x002d4748 */ set(31,0x002521a8u);/* delay 002521a4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00003880)));nocturneBattleActionSkillCall(0x002d4748u);
/* 002521a8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002521ac:;
/* 002521ac: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002521b0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002521b4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002521b8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002521bc: jr ra */ {uint64_t target=cpu(31);/* delay 002521c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00252060(uint64_t a0){
set(4,a0);
body_00252060();
return cpu(2);
}
static void body_00252fb8(void){
nocturneEffectAxisNoteEntry(0x00252fb8u);
uint64_t incoming=cpu(31);
/* 00252fb8: move a3,a0 */ set(7,cpu(4));
/* 00252fbc: lw v0,0x30(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000030)));
/* 00252fc0: slti v0,v0,0x4 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 00252fc4: beq v0,zero,0x002532a0 */ {int taken=(cpu(2)==cpu(0));/* delay 00252fc8 */ if(taken){goto L_002532a0;}}
/* 00252fcc: beq a1,zero,0x00252fe8 */ {int taken=(cpu(5)==cpu(0));/* delay 00252fd0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00252fe8;}}
/* 00252fd4: beq a1,v0,0x00253008 */ {int taken=(cpu(5)==cpu(2));/* delay 00252fd8 */ set(11,sx(UINT32_C(0x003d0000)));if(taken){goto L_00253008;}}
/* 00252fdc: b 0x002530ac */ /* delay 00252fe0 */ set(8,sx((uint32_t)cpu(6)<<4));goto L_002530ac;
L_00252fe8:;
/* 00252fe8: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 00252fec: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 00252ff0: lui t3,0x3d */ set(11,sx(UINT32_C(0x003d0000)));
/* 00252ff4: sll t0,a2,0x4 */ set(8,sx((uint32_t)cpu(6)<<4));
/* 00252ff8: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00252ffc: b 0x002530a8 */ /* delay 00253000 */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002530a8;
L_00253008:;
/* 00253008: sll t0,a2,0x4 */ set(8,sx((uint32_t)cpu(6)<<4));
/* 0025300c: subu v0,t0,a2 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(6)));
/* 00253010: addiu v1,t3,0x7998 */ set(3,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 00253014: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00253018: move t2,t3 */ set(10,cpu(11));
/* 0025301c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00253020: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00253024: bne v1,zero,0x002530a8 */ {int taken=(cpu(3)!=cpu(0));/* delay 00253028 */ set(9,cpu(8));if(taken){goto L_002530a8;}}
/* 0025302c: move a0,zero */ set(4,cpu(0));
L_00253030:;
/* 00253030: bne a0,zero,0x00253050 */ {int taken=(cpu(4)!=cpu(0));/* delay 00253034 */ set(2,sx((uint32_t)cpu(9)-(uint32_t)cpu(6)));if(taken){goto L_00253050;}}
/* 00253038: addiu v1,t2,0x7998 */ set(3,sx((uint32_t)cpu(10)+UINT32_C(0x00007998)));
/* 0025303c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00253040: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00253044: b 0x00253060 */ /* delay 00253048 */ set(2,half(ea(2,(int32_t)UINT32_C(0x00000016))));goto L_00253060;
L_00253050:;
/* 00253050: addiu v1,t2,0x7998 */ set(3,sx((uint32_t)cpu(10)+UINT32_C(0x00007998)));
/* 00253054: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00253058: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0025305c: lhu v0,0x1a(v0) */ set(2,half(ea(2,(int32_t)UINT32_C(0x0000001a))));
L_00253060:;
/* 00253060: addiu v1,v0,-0x1 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00253064: sltiu v0,v1,0xe */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 00253068: beql v0,zero,0x0025309c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025306c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));goto L_0025309c;}}
/* 00253070: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 00253074: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00253078: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0025307c: lw v1,0x3920(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003920)));
/* 00253080: jr v1 */ {uint64_t target=cpu(3);/* delay 00253084 */ switch((uint32_t)target){case 0x00253088u:goto L_00253088;case 0x00253098u:goto L_00253098;default:abort();}}
L_00253088:;
/* 00253088: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 0025308c: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 00253090: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00253094: sw v0,0x4(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_00253098:;
/* 00253098: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
L_0025309c:;
/* 0025309c: slti v0,a0,0x2 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002530a0: bne v0,zero,0x00253030 */ {int taken=(cpu(2)!=cpu(0));/* delay 002530a4 */ if(taken){goto L_00253030;}}
L_002530a8:;
/* 002530a8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002530ac:;
/* 002530ac: bne a1,v0,0x00253180 */ {int taken=(cpu(5)!=cpu(2));/* delay 002530b0 */ set(4,cpu(0));if(taken){goto L_00253180;}}
/* 002530b4: subu v0,t0,a2 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(6)));
/* 002530b8: addiu a0,t3,0x7998 */ set(4,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 002530bc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002530c0: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002530c4: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 002530c8: bne v1,a1,0x00253180 */ {int taken=(cpu(3)!=cpu(5));/* delay 002530cc */ set(4,cpu(0));if(taken){goto L_00253180;}}
L_002530d0:;
/* 002530d0: bne a0,zero,0x002530f0 */ {int taken=(cpu(4)!=cpu(0));/* delay 002530d4 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(6)));if(taken){goto L_002530f0;}}
/* 002530d8: addiu v1,t3,0x7998 */ set(3,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 002530dc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002530e0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002530e4: b 0x00253100 */ /* delay 002530e8 */ set(2,half(ea(2,(int32_t)UINT32_C(0x00000016))));goto L_00253100;
L_002530f0:;
/* 002530f0: addiu v1,t3,0x7998 */ set(3,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 002530f4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002530f8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002530fc: lhu v0,0x1a(v0) */ set(2,half(ea(2,(int32_t)UINT32_C(0x0000001a))));
L_00253100:;
/* 00253100: addiu v1,v0,-0x1 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00253104: sltiu v0,v1,0xe */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 00253108: beql v0,zero,0x0025313c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025310c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));goto L_0025313c;}}
/* 00253110: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 00253114: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00253118: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0025311c: lw v1,0x3960(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003960)));
/* 00253120: jr v1 */ {uint64_t target=cpu(3);/* delay 00253124 */ switch((uint32_t)target){case 0x00253128u:goto L_00253128;case 0x00253138u:goto L_00253138;default:abort();}}
L_00253128:;
/* 00253128: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 0025312c: lui v1,0x2 */ set(3,sx(UINT32_C(0x00020000)));
/* 00253130: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00253134: sw v0,0x4(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_00253138:;
/* 00253138: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
L_0025313c:;
/* 0025313c: slti v0,a0,0x2 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00253140: bne v0,zero,0x002530d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00253144 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(6)));if(taken){goto L_002530d0;}}
/* 00253148: addiu v1,t3,0x7998 */ set(3,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 0025314c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00253150: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00253154: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00253158: lbu v1,0x24(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000024))));
/* 0025315c: beq v1,a0,0x0025316c */ {int taken=(cpu(3)==cpu(4));/* delay 00253160 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_0025316c;}}
/* 00253164: bne v1,v0,0x00253180 */ {int taken=(cpu(3)!=cpu(2));/* delay 00253168 */ set(4,cpu(0));if(taken){goto L_00253180;}}
L_0025316c:;
/* 0025316c: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 00253170: lui v1,0x2 */ set(3,sx(UINT32_C(0x00020000)));
/* 00253174: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00253178: sw v0,0x4(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 0025317c: move a0,zero */ set(4,cpu(0));
L_00253180:;
/* 00253180: bne a0,zero,0x002531a0 */ {int taken=(cpu(4)!=cpu(0));/* delay 00253184 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(6)));if(taken){goto L_002531a0;}}
/* 00253188: addiu v1,t3,0x7998 */ set(3,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 0025318c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00253190: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00253194: b 0x002531b0 */ /* delay 00253198 */ set(2,half(ea(2,(int32_t)UINT32_C(0x00000016))));goto L_002531b0;
L_002531a0:;
/* 002531a0: addiu v1,t3,0x7998 */ set(3,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 002531a4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002531a8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002531ac: lhu v0,0x1a(v0) */ set(2,half(ea(2,(int32_t)UINT32_C(0x0000001a))));
L_002531b0:;
/* 002531b0: addiu v1,v0,-0x2 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffe)));
/* 002531b4: sltiu v0,v1,0xe */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 002531b8: beql v0,zero,0x002531ec */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002531bc */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));goto L_002531ec;}}
/* 002531c0: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 002531c4: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002531c8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002531cc: lw v1,0x39a0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x000039a0)));
/* 002531d0: jr v1 */ {uint64_t target=cpu(3);/* delay 002531d4 */ switch((uint32_t)target){case 0x002531d8u:goto L_002531d8;case 0x002531e8u:goto L_002531e8;default:abort();}}
L_002531d8:;
/* 002531d8: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 002531dc: lui v1,0x4 */ set(3,sx(UINT32_C(0x00040000)));
/* 002531e0: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002531e4: sw v0,0x4(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002531e8:;
/* 002531e8: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
L_002531ec:;
/* 002531ec: slti v0,a0,0x2 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002531f0: bne v0,zero,0x00253180 */ {int taken=(cpu(2)!=cpu(0));/* delay 002531f4 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00253180;}}
/* 002531f8: bne a1,v0,0x00253230 */ {int taken=(cpu(5)!=cpu(2));/* delay 002531fc */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_00253230;}}
/* 00253200: subu v0,t0,a2 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(6)));
/* 00253204: addiu a0,t3,0x7998 */ set(4,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 00253208: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0025320c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00253210: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00253214: bne v1,a1,0x00253230 */ {int taken=(cpu(3)!=cpu(5));/* delay 00253218 */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_00253230;}}
/* 0025321c: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 00253220: lui v1,0x8 */ set(3,sx(UINT32_C(0x00080000)));
/* 00253224: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00253228: sw v0,0x4(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 0025322c: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
L_00253230:;
/* 00253230: bne a1,v0,0x0025324c */ {int taken=(cpu(5)!=cpu(2));/* delay 00253234 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0025324c;}}
/* 00253238: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 0025323c: lui v1,0x10 */ set(3,sx(UINT32_C(0x00100000)));
/* 00253240: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00253244: sw v0,0x4(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 00253248: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_0025324c:;
/* 0025324c: beq a1,v0,0x00253268 */ {int taken=(cpu(5)==cpu(2));/* delay 00253250 */ set(2,sx(UINT32_C(0x00000006)));if(taken){goto L_00253268;}}
/* 00253254: bne a1,v0,0x002532a0 */ {int taken=(cpu(5)!=cpu(2));/* delay 00253258 */ if(taken){goto L_002532a0;}}
/* 0025325c: b 0x00253294 */ /* delay 00253260 */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));goto L_00253294;
L_00253268:;
/* 00253268: subu v0,t0,a2 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(6)));
/* 0025326c: addiu v1,t3,0x7998 */ set(3,sx((uint32_t)cpu(11)+UINT32_C(0x00007998)));
/* 00253270: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00253274: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00253278: lw v0,0x30(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000030)));
/* 0025327c: sltiu v1,v0,0x4 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000004));
/* 00253280: beq v1,zero,0x002532a0 */ {int taken=(cpu(3)==cpu(0));/* delay 00253284 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_002532a0;}}
/* 00253288: bne v0,zero,0x002532a0 */ {int taken=(cpu(2)!=cpu(0));/* delay 0025328c */ if(taken){goto L_002532a0;}}
/* 00253290: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
L_00253294:;
/* 00253294: lui v1,0x20 */ set(3,sx(UINT32_C(0x00200000)));
/* 00253298: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 0025329c: sw v0,0x4(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002532a0:;
/* 002532a0: jr ra */ {uint64_t target=cpu(31);/* delay 002532a4 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00252FB8(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00252fb8();
return;
}
static void body_00255650(void){
nocturneEffectAxisNoteEntry(0x00255650u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00255650: addiu sp,sp,-0xf0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff10)));
/* 00255654: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00255658: sd s2,0xa0(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0025565c: move s2,a0 */ set(18,cpu(4));
/* 00255660: swc1 f21,0xe8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000e8)),f[21]);
/* 00255664: sd s0,0x90(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 00255668: sd s1,0x98(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0025566c: sd s3,0xa8(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 00255670: sd s4,0xb0(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 00255674: sd s5,0xb8(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 00255678: sd s6,0xc0(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 0025567c: sd s7,0xc8(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 00255680: sd s8,0xd0(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 00255684: sd ra,0xd8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000d8)));
/* 00255688: swc1 f20,0xe0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000e0)),f[20]);
/* 0025568c: sw zero,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));
/* 00255690: lui at,0x4040 */ set(1,sx(UINT32_C(0x40400000)));
/* 00255694: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 00255698: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0025569c: sw zero,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 002556a0: sw zero,0x18(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 002556a4: sw zero,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));
/* 002556a8: sw zero,0x14c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000014c)),(uint32_t)cpu(0));
/* 002556ac: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002556b0: sw zero,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(0));
/* 002556b4: sw zero,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(0));
/* 002556b8: sw v0,0x5c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(2));
/* 002556bc: lw v0,0x4(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 002556c0: sw zero,0x60(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(0));
/* 002556c4: andi v0,v0,0x100 */ set(2,cpu(2)&UINT32_C(0x00000100));
/* 002556c8: sw v1,0x64(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000064)),(uint32_t)cpu(3));
/* 002556cc: sw v1,0x68(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000068)),(uint32_t)cpu(3));
/* 002556d0: bne v0,zero,0x002556e0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002556d4 */ sw(ea(29,(int32_t)UINT32_C(0x0000006c)),(uint32_t)cpu(0));if(taken){goto L_002556e0;}}
/* 002556d8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002556dc: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
L_002556e0:;
/* 002556e0: lw a0,0x74(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000074)));
/* 002556e4: beq a0,zero,0x00255758 */ {int taken=(cpu(4)==cpu(0));/* delay 002556e8 */ if(taken){goto L_00255758;}}
/* 002556ec: lw v0,0x44(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000044)));
/* 002556f0: bne v0,zero,0x00255758 */ {int taken=(cpu(2)!=cpu(0));/* delay 002556f4 */ set(7,sx(UINT32_C(0x00000001)));if(taken){goto L_00255758;}}
/* 002556f8: lw a2,0x28(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002556fc: jal 0x0016ac70 */ set(31,0x00255704u);/* delay 00255700 */ set(5,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x0016ac70u);
/* 00255704: move a0,v0 */ set(4,cpu(2));
/* 00255708: jal 0x0016aec0 */ set(31,0x00255710u);/* delay 0025570c */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x0016aec0u);
/* 00255710: lw a0,0x40(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00255714: jal 0x0016aee8 */ set(31,0x0025571cu);/* delay 00255718 */ set(30,cpu(2));nocturneBattleActionSkillCall(0x0016aee8u);
/* 0025571c: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00255720: addiu a0,a0,0x3e10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00003e10)));
/* 00255724: move a1,s8 */ set(5,cpu(30));
/* 00255728: move a2,v0 */ set(6,cpu(2));
/* 0025572c: jal 0x002d4748 */ set(31,0x00255734u);/* delay 00255730 */ set(23,cpu(2));nocturneBattleActionSkillCall(0x002d4748u);
/* 00255734: lw v1,0x28(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00255738: move a0,s2 */ set(4,cpu(18));
/* 0025573c: move a2,zero */ set(6,cpu(0));
/* 00255740: lh a1,0x92(v1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));
/* 00255744: move a3,s7 */ set(7,cpu(23));
/* 00255748: jal 0x002517e0 */ set(31,0x00255750u);/* delay 0025574c */ set(8,cpu(23));nocturneBattleActionSkillCall(0x002517e0u);
/* 00255750: b 0x00255794 */ /* delay 00255754 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_00255794;
L_00255758:;
/* 00255758: lui at,0x4120 */ set(1,sx(UINT32_C(0x41200000)));
/* 0025575c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00255760: move a0,s2 */ set(4,cpu(18));
/* 00255764: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00255768: move a2,zero */ set(6,cpu(0));
/* 0025576c: nop  */ 
/* 00255770: nop  */ 
/* 00255774: div.S f0,f0,f21 */ f[0]=EE_FPU_DIV_S(f[0],f[21]);
/* 00255778: move s7,zero */ set(23,cpu(0));
/* 0025577c: lh a1,0x92(v0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));
/* 00255780: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00255784: mfc1 a3,f1 */ set(7,sx(f[1]));
/* 00255788: jal 0x002517e0 */ set(31,0x00255790u);/* delay 0025578c */ set(8,cpu(7));nocturneBattleActionSkillCall(0x002517e0u);
/* 00255790: lw a0,0x28(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000028)));
L_00255794:;
/* 00255794: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
/* 00255798: lh v0,0xa4(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x000000a4))));
/* 0025579c: bnel v0,v1,0x00255838 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 002557a0 */ lw(4,ea(18,(int32_t)UINT32_C(0x0000002c)));goto L_00255838;}}
/* 002557a4: lh a1,0xae(a0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x000000ae))));
/* 002557a8: bltzl a1,0x00255838 */ {int taken=((int64_t)cpu(5)<0);if(taken){/* delay 002557ac */ lw(4,ea(18,(int32_t)UINT32_C(0x0000002c)));goto L_00255838;}}
/* 002557b0: lh v0,0xa6(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x000000a6))));
/* 002557b4: bltzl v0,0x00255838 */ {int taken=((int64_t)cpu(2)<0);if(taken){/* delay 002557b8 */ lw(4,ea(18,(int32_t)UINT32_C(0x0000002c)));goto L_00255838;}}
/* 002557bc: jal 0x0024d428 */ set(31,0x002557c4u);/* delay 002557c0 */ f[12]=f[21];body_0024d428();
/* 002557c4: lw a0,0x28(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002557c8: mov.S f12,f21 */ f[12]=f[21];
/* 002557cc: mov.S f20,f0 */ f[20]=f[0];
/* 002557d0: jal 0x0024d3a0 */ set(31,0x002557d8u);/* delay 002557d4 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x000000ae))));body_0024d3a0();
/* 002557d8: lw v1,0x28(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002557dc: lui at,0x4120 */ set(1,sx(UINT32_C(0x41200000)));
/* 002557e0: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 002557e4: move a0,s2 */ set(4,cpu(18));
/* 002557e8: lh a3,0xa6(v1) */ set(7,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x000000a6))));
/* 002557ec: move a2,zero */ set(6,cpu(0));
/* 002557f0: nop  */ 
/* 002557f4: nop  */ 
/* 002557f8: div.S f1,f1,f21 */ f[1]=EE_FPU_DIV_S(f[1],f[21]);
/* 002557fc: lh a1,0x92(v1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));
/* 00255800: mtc1 a3,f0 */ f[0]=(uint32_t)cpu(7);
/* 00255804: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00255808: nop  */ 
/* 0025580c: nop  */ 
/* 00255810: div.S f0,f0,f20 */ f[0]=EE_FPU_DIV_S(f[0],f[20]);
/* 00255814: cvt.w.S f2,f1 */ f[2]=EE_FPU_CVT_W_S(f[1]);
/* 00255818: mfc1 a3,f2 */ set(7,sx(f[2]));
/* 0025581c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00255820: mfc1 s1,f1 */ set(17,sx(f[1]));
/* 00255824: subu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)-(uint32_t)cpu(2)));
/* 00255828: addu a3,s1,a3 */ set(7,sx((uint32_t)cpu(17)+(uint32_t)cpu(7)));
/* 0025582c: jal 0x00251770 */ set(31,0x00255834u);/* delay 00255830 */ set(8,cpu(7));body_00251770();
/* 00255834: lw a0,0x2c(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x0000002c)));
L_00255838:;
/* 00255838: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0025583c: lh v1,0x6a(a0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x0000006a))));
/* 00255840: beq v1,v0,0x00255888 */ {int taken=(cpu(3)==cpu(2));/* delay 00255844 */ set(22,cpu(0));if(taken){goto L_00255888;}}
/* 00255848: slti v0,v1,0x2 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0025584c: bnel v0,zero,0x00255890 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00255850 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x0000006a))));goto L_00255890;}}
/* 00255854: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 00255858: beq v1,v0,0x00255870 */ {int taken=(cpu(3)==cpu(2));/* delay 0025585c */ set(2,sx(UINT32_C(0x00000006)));if(taken){goto L_00255870;}}
/* 00255860: beql v1,v0,0x0025588c */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 00255864 */ set(22,sx(UINT32_C(0x000000ff)));goto L_0025588c;}}
/* 00255868: b 0x00255890 */ /* delay 0025586c */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x0000006a))));goto L_00255890;
L_00255870:;
/* 00255870: lhu a1,0x6c(a0) */ set(5,half(ea(4,(int32_t)UINT32_C(0x0000006c))));
/* 00255874: jal 0x00259c48 */ set(31,0x0025587cu);/* delay 00255878 */ set(4,cpu(18));nocturneBattleActionSkillCall(0x00259c48u);
/* 0025587c: lw a0,0x2c(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x0000002c)));
/* 00255880: b 0x0025588c */ /* delay 00255884 */ set(22,cpu(2));goto L_0025588c;
L_00255888:;
/* 00255888: lhu s6,0x6c(a0) */ set(22,half(ea(4,(int32_t)UINT32_C(0x0000006c))));
L_0025588c:;
/* 0025588c: lh a1,0x6a(a0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x0000006a))));
L_00255890:;
/* 00255890: move a0,s2 */ set(4,cpu(18));
/* 00255894: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00255898: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 0025589c: jal 0x00252fb8 */ set(31,0x002558a4u);/* delay 002558a0 */ set(6,cpu(22));body_00252fb8();
/* 002558a4: move a0,s2 */ set(4,cpu(18));
/* 002558a8: lw a2,0x3c(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000003c)));
/* 002558ac: move a1,sp */ set(5,cpu(29));
/* 002558b0: move a3,s6 */ set(7,cpu(22));
/* 002558b4: jal 0x002518c8 */ set(31,0x002558bcu);/* delay 002558b8 */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(23));body_002518c8();
/* 002558bc: lb v0,0x0(sp) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(29,(int32_t)UINT32_C(0x00000000))));
/* 002558c0: bltz v0,0x00255ff8 */ {int taken=((int64_t)cpu(2)<0);/* delay 002558c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(0));if(taken){goto L_00255ff8;}}
/* 002558c8: addiu v0,s2,0x8 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000008)));
/* 002558cc: sll v1,s6,0x4 */ set(3,sx((uint32_t)cpu(22)<<4));
/* 002558d0: sw v0,0x74(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000074)),(uint32_t)cpu(2));
/* 002558d4: sll v0,s6,0x2 */ set(2,sx((uint32_t)cpu(22)<<2));
/* 002558d8: addiu a0,s6,-0x103 */ set(4,sx((uint32_t)cpu(22)+UINT32_C(0xfffffefd)));
/* 002558dc: sw v1,0x7c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000007c)),(uint32_t)cpu(3));
/* 002558e0: sw a0,0x70(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000070)),(uint32_t)cpu(4));
/* 002558e4: move s5,zero */ set(21,cpu(0));
/* 002558e8: sw v0,0x78(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000078)),(uint32_t)cpu(2));
/* 002558ec: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
L_002558f0:;
/* 002558f0: lw v1,0x28(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002558f4: lb a2,0x0(v0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002558f8: move a0,s6 */ set(4,cpu(22));
/* 002558fc: lh a1,0x92(v1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));
/* 00255900: lw v1,0x74(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000074)));
/* 00255904: sll v0,a2,0x3 */ set(2,sx((uint32_t)cpu(6)<<3));
/* 00255908: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0025590c: lhu a3,0x80(v0) */ set(7,half(ea(2,(int32_t)UINT32_C(0x00000080))));
/* 00255910: slt v1,s7,a3 */ set(3,(int64_t)cpu(23)<(int64_t)cpu(7));
/* 00255914: movz a3,s7,v1 */ if(cpu(3)==0){set(7,cpu(23));}
/* 00255918: jal 0x00265948 */ set(31,0x00255920u);/* delay 0025591c */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(7));nocturneBattleActionSkillCall(0x00265948u);
/* 00255920: move s3,v0 */ set(19,cpu(2));
/* 00255924: lui v0,0x54 */ set(2,sx(UINT32_C(0x00540000)));
/* 00255928: addiu a0,v0,0x3e20 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00003e20)));
/* 0025592c: jal 0x002d4748 */ set(31,0x00255934u);/* delay 00255930 */ set(5,cpu(19));nocturneBattleActionSkillCall(0x002d4748u);
/* 00255934: lw v1,0x34(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000034)));
/* 00255938: slti a0,s3,0x3 */ set(4,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 0025593c: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 00255940: lw s4,0x50(sp) */ lw(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00255944: bne v1,v0,0x0025596c */ {int taken=(cpu(3)!=cpu(2));/* delay 00255948 */ sw(ea(29,(int32_t)UINT32_C(0x00000080)),(uint32_t)cpu(4));if(taken){goto L_0025596c;}}
/* 0025594c: move v0,a0 */ set(2,cpu(4));
/* 00255950: beql v0,zero,0x00255970 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00255954 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000074)));goto L_00255970;}}
/* 00255958: slti v1,s3,0x1 */ set(3,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000001));
/* 0025595c: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 00255960: movz s3,v0,v1 */ if(cpu(3)==0){set(19,cpu(2));}
/* 00255964: slti v1,s3,0x3 */ set(3,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00255968: sw v1,0x80(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000080)),(uint32_t)cpu(3));
L_0025596c:;
/* 0025596c: lw a0,0x74(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000074)));
L_00255970:;
/* 00255970: beq a0,zero,0x002559fc */ {int taken=(cpu(4)==cpu(0));/* delay 00255974 */ set(30,cpu(0));if(taken){goto L_002559fc;}}
/* 00255978: lw v1,0x44(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 0025597c: slti v0,v1,0x10 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00255980: beql v0,zero,0x00255a00 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00255984 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));goto L_00255a00;}}
/* 00255988: beq s3,zero,0x002559ac */ {int taken=(cpu(19)==cpu(0));/* delay 0025598c */ if(taken){goto L_002559ac;}}
/* 00255990: bltz s3,0x002559fc */ {int taken=((int64_t)cpu(19)<0);/* delay 00255994 */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x0000000f));if(taken){goto L_002559fc;}}
/* 00255998: beq v0,zero,0x00255a00 */ {int taken=(cpu(2)==cpu(0));/* delay 0025599c */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));if(taken){goto L_00255a00;}}
/* 002559a0: lw v0,0x80(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002559a4: bne v0,zero,0x00255a00 */ {int taken=(cpu(2)!=cpu(0));/* delay 002559a8 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));if(taken){goto L_00255a00;}}
L_002559ac:;
/* 002559ac: jal 0x0016ab70 */ set(31,0x002559b4u);/* delay 002559b0 */ set(5,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x0016ab70u);
/* 002559b4: lw a0,0x74(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000074)));
/* 002559b8: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 002559bc: jal 0x0016aba0 */ set(31,0x002559c4u);/* delay 002559c0 */ set(30,cpu(2));nocturneBattleActionSkillCall(0x0016aba0u);
/* 002559c4: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 002559c8: addiu a0,a0,0x3e38 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00003e38)));
/* 002559cc: move a1,s8 */ set(5,cpu(30));
/* 002559d0: move a2,v0 */ set(6,cpu(2));
/* 002559d4: jal 0x002d4748 */ set(31,0x002559dcu);/* delay 002559d8 */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x002d4748u);
/* 002559dc: move a0,s2 */ set(4,cpu(18));
/* 002559e0: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 002559e4: lw v1,0x48(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002559e8: lb a1,0x0(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002559ec: move a2,s4 */ set(6,cpu(20));
/* 002559f0: move a3,zero */ set(7,cpu(0));
/* 002559f4: jal 0x002517e0 */ set(31,0x002559fcu);/* delay 002559f8 */ set(8,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002517e0u);
L_002559fc:;
/* 002559fc: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
L_00255a00:;
/* 00255a00: lw v1,0x0(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00255a04: lb a3,0x0(v0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255a08: addu s4,s4,s8 */ set(20,sx((uint32_t)cpu(20)+(uint32_t)cpu(30)));
/* 00255a0c: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00255a10: move a0,s4 */ set(4,cpu(20));
/* 00255a14: sll a2,a3,0x4 */ set(6,sx((uint32_t)cpu(7)<<4));
/* 00255a18: move a1,s2 */ set(5,cpu(18));
/* 00255a1c: subu a2,a2,a3 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(7)));
/* 00255a20: move a3,zero */ set(7,cpu(0));
/* 00255a24: sll a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)<<4));
/* 00255a28: li t0,0x2000 */ set(8,sx(UINT32_C(0x00002000)));
/* 00255a2c: addu a2,v0,a2 */ set(6,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00255a30: lw v0,0x50(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00255a34: addu v0,v0,s8 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(30)));
/* 00255a38: jal 0x00263028 */ set(31,0x00255a40u);/* delay 00255a3c */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(2));body_00263028();
/* 00255a40: lw a0,0x64(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000064)));
/* 00255a44: addiu v1,s3,-0x1 */ set(3,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));
/* 00255a48: sltiu v1,v1,0x2 */ set(3,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00255a4c: xori v0,s3,0x2 */ set(2,cpu(19)^UINT32_C(0x00000002));
/* 00255a50: movz a0,zero,v1 */ if(cpu(3)==0){set(4,cpu(0));}
/* 00255a54: lw v1,0x68(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00255a58: sw a0,0x64(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000064)),(uint32_t)cpu(4));
/* 00255a5c: movn v1,zero,v0 */ if(cpu(2)!=0){set(3,cpu(0));}
/* 00255a60: beq s3,zero,0x00255a84 */ {int taken=(cpu(19)==cpu(0));/* delay 00255a64 */ sw(ea(29,(int32_t)UINT32_C(0x00000068)),(uint32_t)cpu(3));if(taken){goto L_00255a84;}}
/* 00255a68: bltz s3,0x00255a8c */ {int taken=((int64_t)cpu(19)<0);/* delay 00255a6c */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_00255a8c;}}
/* 00255a70: beq v0,zero,0x00255a90 */ {int taken=(cpu(2)==cpu(0));/* delay 00255a74 */ lw(4,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_00255a90;}}
/* 00255a78: slti v0,s3,0x2 */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00255a7c: bne v0,zero,0x00255a94 */ {int taken=(cpu(2)!=cpu(0));/* delay 00255a80 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00255a94;}}
L_00255a84:;
/* 00255a84: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00255a88: sw a0,0x60(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(4));
L_00255a8c:;
/* 00255a8c: lw a0,0x6c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000006c)));
L_00255a90:;
/* 00255a90: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_00255a94:;
/* 00255a94: sltiu v1,s3,0xf */ set(3,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000f));
/* 00255a98: movz a0,v0,s3 */ if(cpu(19)==0){set(4,cpu(2));}
/* 00255a9c: beq v1,zero,0x00255c7c */ {int taken=(cpu(3)==cpu(0));/* delay 00255aa0 */ sw(ea(29,(int32_t)UINT32_C(0x0000006c)),(uint32_t)cpu(4));if(taken){goto L_00255c7c;}}
/* 00255aa4: sll v0,s3,0x2 */ set(2,sx((uint32_t)cpu(19)<<2));
/* 00255aa8: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00255aac: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00255ab0: lw v1,0x3f00(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003f00)));
/* 00255ab4: jr v1 */ {uint64_t target=cpu(3);/* delay 00255ab8 */ switch((uint32_t)target){case 0x00255ac0u:goto L_00255ac0;case 0x00255af8u:goto L_00255af8;case 0x00255b28u:goto L_00255b28;case 0x00255b58u:goto L_00255b58;case 0x00255b88u:goto L_00255b88;case 0x00255ba8u:goto L_00255ba8;case 0x00255bc8u:goto L_00255bc8;case 0x00255be8u:goto L_00255be8;case 0x00255c08u:goto L_00255c08;case 0x00255c38u:goto L_00255c38;case 0x00255c58u:goto L_00255c58;case 0x00255c70u:goto L_00255c70;default:abort();}}
L_00255ac0:;
/* 00255ac0: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00255ac4: addu a1,s5,sp */ set(5,sx((uint32_t)cpu(21)+(uint32_t)cpu(29)));
/* 00255ac8: addu v1,sp,s5 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255acc: lb t1,0x1(a1) */ set(9,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000001))));
/* 00255ad0: lb t0,0x0(v1) */ set(8,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00255ad4: move a0,s2 */ set(4,cpu(18));
/* 00255ad8: lh a3,0x92(v0) */ set(7,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));
/* 00255adc: move a1,s3 */ set(5,cpu(19));
/* 00255ae0: move a2,s6 */ set(6,cpu(22));
/* 00255ae4: move t2,s4 */ set(10,cpu(20));
/* 00255ae8: jal 0x0024ff60 */ set(31,0x00255af0u);/* delay 00255aec */ f[12]=f[20];nocturneBattleActionSkillCall(0x0024ff60u);
/* 00255af0: b 0x00255c7c */ /* delay 00255af4 */ goto L_00255c7c;
L_00255af8:;
/* 00255af8: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00255afc: addu a1,s5,sp */ set(5,sx((uint32_t)cpu(21)+(uint32_t)cpu(29)));
/* 00255b00: addu v1,sp,s5 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255b04: lb t0,0x1(a1) */ set(8,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000001))));
/* 00255b08: lb a3,0x0(v1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00255b0c: move a0,s2 */ set(4,cpu(18));
/* 00255b10: lh a2,0x92(v0) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));
/* 00255b14: move a1,s6 */ set(5,cpu(22));
/* 00255b18: jal 0x0024fb38 */ set(31,0x00255b20u);/* delay 00255b1c */ set(9,cpu(20));body_0024fb38();
/* 00255b20: b 0x00255c7c */ /* delay 00255b24 */ goto L_00255c7c;
L_00255b28:;
/* 00255b28: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00255b2c: addu a1,s5,sp */ set(5,sx((uint32_t)cpu(21)+(uint32_t)cpu(29)));
/* 00255b30: addu v1,sp,s5 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255b34: lb t0,0x1(a1) */ set(8,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000001))));
/* 00255b38: lb a3,0x0(v1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00255b3c: move a0,s2 */ set(4,cpu(18));
/* 00255b40: lh a2,0x92(v0) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));
/* 00255b44: move a1,s6 */ set(5,cpu(22));
/* 00255b48: jal 0x0024fc28 */ set(31,0x00255b50u);/* delay 00255b4c */ set(9,cpu(20));body_0024fc28();
/* 00255b50: b 0x00255c7c */ /* delay 00255b54 */ goto L_00255c7c;
L_00255b58:;
/* 00255b58: lw v1,0x28(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00255b5c: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255b60: lb a3,0x0(v0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255b64: move a0,s2 */ set(4,cpu(18));
/* 00255b68: lh a2,0x92(v1) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));
/* 00255b6c: move a1,s6 */ set(5,cpu(22));
/* 00255b70: jal 0x0024f990 */ set(31,0x00255b78u);/* delay 00255b74 */ set(8,cpu(20));body_0024f990();
/* 00255b78: beql v0,zero,0x00255c7c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00255b7c */ sw(ea(29,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(0));goto L_00255c7c;}}
/* 00255b80: b 0x00255c7c */ /* delay 00255b84 */ goto L_00255c7c;
L_00255b88:;
/* 00255b88: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255b8c: move a0,s2 */ set(4,cpu(18));
/* 00255b90: lb a1,0x0(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255b94: jal 0x0024f938 */ set(31,0x00255b9cu);/* delay 00255b98 */ set(6,cpu(20));body_0024f938();
/* 00255b9c: b 0x00255c7c */ /* delay 00255ba0 */ goto L_00255c7c;
L_00255ba8:;
/* 00255ba8: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255bac: move a0,s2 */ set(4,cpu(18));
/* 00255bb0: lb a1,0x0(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255bb4: jal 0x0024f8a8 */ set(31,0x00255bbcu);/* delay 00255bb8 */ set(6,cpu(20));body_0024f8a8();
/* 00255bbc: b 0x00255c7c */ /* delay 00255bc0 */ goto L_00255c7c;
L_00255bc8:;
/* 00255bc8: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255bcc: move a0,s2 */ set(4,cpu(18));
/* 00255bd0: lb a1,0x0(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255bd4: jal 0x0024f7e0 */ set(31,0x00255bdcu);/* delay 00255bd8 */ set(6,cpu(20));body_0024f7e0();
/* 00255bdc: b 0x00255c7c */ /* delay 00255be0 */ goto L_00255c7c;
L_00255be8:;
/* 00255be8: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255bec: move a0,s2 */ set(4,cpu(18));
/* 00255bf0: lb a1,0x0(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255bf4: jal 0x0024f5f0 */ set(31,0x00255bfcu);/* delay 00255bf8 */ set(6,cpu(20));body_0024f5f0();
/* 00255bfc: b 0x00255c7c */ /* delay 00255c00 */ goto L_00255c7c;
L_00255c08:;
/* 00255c08: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00255c0c: addu a1,s5,sp */ set(5,sx((uint32_t)cpu(21)+(uint32_t)cpu(29)));
/* 00255c10: addu v1,sp,s5 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255c14: lb t0,0x1(a1) */ set(8,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000001))));
/* 00255c18: lb a3,0x0(v1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00255c1c: move a0,s2 */ set(4,cpu(18));
/* 00255c20: lh a2,0x92(v0) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));
/* 00255c24: move a1,s6 */ set(5,cpu(22));
/* 00255c28: jal 0x0024fcc0 */ set(31,0x00255c30u);/* delay 00255c2c */ set(9,cpu(20));body_0024fcc0();
/* 00255c30: b 0x00255c7c */ /* delay 00255c34 */ goto L_00255c7c;
L_00255c38:;
/* 00255c38: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255c3c: move a0,s2 */ set(4,cpu(18));
/* 00255c40: lb a1,0x0(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255c44: jal 0x0024f658 */ set(31,0x00255c4cu);/* delay 00255c48 */ set(6,cpu(20));body_0024f658();
/* 00255c4c: b 0x00255c7c */ /* delay 00255c50 */ goto L_00255c7c;
L_00255c58:;
/* 00255c58: move a0,s2 */ set(4,cpu(18));
/* 00255c5c: jal 0x0024f728 */ set(31,0x00255c64u);/* delay 00255c60 */ set(5,cpu(22));body_0024f728();
/* 00255c64: b 0x00255c7c */ /* delay 00255c68 */ goto L_00255c7c;
L_00255c70:;
/* 00255c70: move a0,s2 */ set(4,cpu(18));
/* 00255c74: jal 0x0024f7b8 */ set(31,0x00255c7cu);/* delay 00255c78 */ set(5,cpu(20));body_0024f7b8();
L_00255c7c:;
/* 00255c7c: bnel s3,zero,0x00255cd0 */ {int taken=(cpu(19)!=cpu(0));if(taken){/* delay 00255c80 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000074)));goto L_00255cd0;}}
/* 00255c84: lw v1,0x0(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00255c88: lw v0,0x60(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000060)));
/* 00255c8c: andi v0,v0,0x400 */ set(2,cpu(2)&UINT32_C(0x00000400));
/* 00255c90: beq v0,zero,0x00255ccc */ {int taken=(cpu(2)==cpu(0));/* delay 00255c94 */ set(16,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));if(taken){goto L_00255ccc;}}
/* 00255c98: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 00255c9c: addiu v0,v0,-0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffc)));
/* 00255ca0: sltiu v0,v0,0xa */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 00255ca4: beql v0,zero,0x00255cd0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00255ca8 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000074)));goto L_00255cd0;}}
/* 00255cac: jal 0x00267e38 */ set(31,0x00255cb4u);/* delay 00255cb0 */ set(4,cpu(22));nocturneBattleActionSkillCall(0x00267e38u);
/* 00255cb4: li v1,0xe */ set(3,sx(UINT32_C(0x0000000e)));
/* 00255cb8: beq v0,v1,0x00255ccc */ {int taken=(cpu(2)==cpu(3));/* delay 00255cbc */ set(4,cpu(18));if(taken){goto L_00255ccc;}}
/* 00255cc0: lb a1,0x0(s0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 00255cc4: jal 0x0024fe40 */ set(31,0x00255cccu);/* delay 00255cc8 */ set(6,sx((uint32_t)cpu(20)+UINT32_C(0x00000005)));body_0024fe40();
L_00255ccc:;
/* 00255ccc: lw v0,0x74(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000074)));
L_00255cd0:;
/* 00255cd0: beq v0,zero,0x00255db0 */ {int taken=(cpu(2)==cpu(0));/* delay 00255cd4 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000044)));if(taken){goto L_00255db0;}}
/* 00255cd8: slti v0,v1,0x10 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00255cdc: beql v0,zero,0x00255db4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00255ce0 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_00255db4;}}
/* 00255ce4: lw a0,0x5c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000005c)));
/* 00255ce8: beql a0,zero,0x00255db4 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00255cec */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_00255db4;}}
/* 00255cf0: beq s3,zero,0x00255d18 */ {int taken=(cpu(19)==cpu(0));/* delay 00255cf4 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00255d18;}}
/* 00255cf8: bltz s3,0x00255db0 */ {int taken=((int64_t)cpu(19)<0);/* delay 00255cfc */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x0000000f));if(taken){goto L_00255db0;}}
/* 00255d00: beql v0,zero,0x00255db4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00255d04 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_00255db4;}}
/* 00255d08: lw v0,0x80(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00255d0c: bnel v0,zero,0x00255db4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00255d10 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_00255db4;}}
/* 00255d14: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
L_00255d18:;
/* 00255d18: bne s3,v0,0x00255d2c */ {int taken=(cpu(19)!=cpu(2));/* delay 00255d1c */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));if(taken){goto L_00255d2c;}}
/* 00255d20: li v0,0x107 */ set(2,sx(UINT32_C(0x00000107)));
/* 00255d24: beq s6,v0,0x00255db0 */ {int taken=(cpu(22)==cpu(2));/* delay 00255d28 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));if(taken){goto L_00255db0;}}
L_00255d2c:;
/* 00255d2c: move a0,s2 */ set(4,cpu(18));
/* 00255d30: lb a1,0x0(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255d34: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
/* 00255d38: jal 0x002515e8 */ set(31,0x00255d40u);/* delay 00255d3c */ set(16,sx((uint32_t)cpu(20)-(uint32_t)cpu(30)));nocturneBattleActionSkillCall(0x002515e8u);
/* 00255d40: addiu a0,s3,-0x4 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xfffffffc)));
/* 00255d44: addu v1,sp,s5 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255d48: lw a2,0x0(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00255d4c: lb a1,0x0(v1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00255d50: li v1,0x20 */ set(3,sx(UINT32_C(0x00000020)));
/* 00255d54: sltiu a0,a0,0x2 */ set(4,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00255d58: xori v0,v0,0x0 */ set(2,cpu(2)^UINT32_C(0x00000000));
/* 00255d5c: sll t1,a1,0x4 */ set(9,sx((uint32_t)cpu(5)<<4));
/* 00255d60: movn s1,v1,a0 */ if(cpu(4)!=0){set(17,cpu(3));}
/* 00255d64: subu t1,t1,a1 */ set(9,sx((uint32_t)cpu(9)-(uint32_t)cpu(5)));
/* 00255d68: lw a1,0x48(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00255d6c: lw a0,0x0(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 00255d70: move a2,s2 */ set(6,cpu(18));
/* 00255d74: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 00255d78: sll t1,t1,0x4 */ set(9,sx((uint32_t)cpu(9)<<4));
/* 00255d7c: movn s1,v1,v0 */ if(cpu(2)!=0){set(17,cpu(3));}
/* 00255d80: lw a3,0x74(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000074)));
/* 00255d84: addu t1,a0,t1 */ set(9,sx((uint32_t)cpu(4)+(uint32_t)cpu(9)));
/* 00255d88: move a0,s0 */ set(4,cpu(16));
/* 00255d8c: move t2,s1 */ set(10,cpu(17));
/* 00255d90: jal 0x00261638 */ set(31,0x00255d98u);/* delay 00255d94 */ set(8,sx(UINT32_C(0x00000002)));body_00261638();
/* 00255d98: addiu a2,s6,0x200 */ set(6,sx((uint32_t)cpu(22)+UINT32_C(0x00000200)));
/* 00255d9c: sll a2,a2,0x10 */ set(6,sx((uint32_t)cpu(6)<<16));
/* 00255da0: move a0,s0 */ set(4,cpu(16));
/* 00255da4: ori a2,a2,0x1 */ set(6,cpu(6)|UINT32_C(0x00000001));
/* 00255da8: jal 0x00262cc0 */ set(31,0x00255db0u);/* delay 00255dac */ set(5,cpu(18));nocturneBattleActionSkillCall(0x00262cc0u);
L_00255db0:;
/* 00255db0: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
L_00255db4:;
/* 00255db4: addu s0,sp,s5 */ set(16,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255db8: lb a2,0x0(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 00255dbc: move a0,s6 */ set(4,cpu(22));
/* 00255dc0: jal 0x00266d20 */ set(31,0x00255dc8u);/* delay 00255dc4 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x00266d20u);
/* 00255dc8: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 00255dcc: addiu a0,v1,0x7998 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00007998)));
/* 00255dd0: lw v1,0x7c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000007c)));
/* 00255dd4: subu v0,v1,s6 */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(22)));
/* 00255dd8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00255ddc: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00255de0: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00255de4: bne v1,zero,0x00255e00 */ {int taken=(cpu(3)!=cpu(0));/* delay 00255de8 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);if(taken){goto L_00255e00;}}
/* 00255dec: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00255df0: li a1,0xf */ set(5,sx(UINT32_C(0x0000000f)));
/* 00255df4: move a2,zero */ set(6,cpu(0));
/* 00255df8: jal 0x00267e50 */ set(31,0x00255e00u);/* delay 00255dfc */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x00267e50u);
L_00255e00:;
/* 00255e00: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
/* 00255e04: beq s3,s1,0x00255ea0 */ {int taken=(cpu(19)==cpu(17));/* delay 00255e08 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00255ea0;}}
/* 00255e0c: bnel s3,v0,0x00255ea4 */ {int taken=(cpu(19)!=cpu(2));if(taken){/* delay 00255e10 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000070)));goto L_00255ea4;}}
/* 00255e14: jal 0x00267e38 */ set(31,0x00255e1cu);/* delay 00255e18 */ set(4,cpu(22));nocturneBattleActionSkillCall(0x00267e38u);
/* 00255e1c: move v1,v0 */ set(3,cpu(2));
/* 00255e20: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00255e24: beq v1,v0,0x00255e68 */ {int taken=(cpu(3)==cpu(2));/* delay 00255e28 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_00255e68;}}
/* 00255e2c: beq v0,zero,0x00255e48 */ {int taken=(cpu(2)==cpu(0));/* delay 00255e30 */ set(2,sx(UINT32_C(0x00000006)));if(taken){goto L_00255e48;}}
/* 00255e34: beql v1,s1,0x00255e60 */ {int taken=(cpu(3)==cpu(17));if(taken){/* delay 00255e38 */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x00000000))));goto L_00255e60;}}
/* 00255e3c: b 0x00255ea4 */ /* delay 00255e40 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000070)));goto L_00255ea4;
L_00255e48:;
/* 00255e48: beq v1,v0,0x00255e78 */ {int taken=(cpu(3)==cpu(2));/* delay 00255e4c */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_00255e78;}}
/* 00255e50: beq v1,v0,0x00255e90 */ {int taken=(cpu(3)==cpu(2));/* delay 00255e54 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000070)));if(taken){goto L_00255e90;}}
/* 00255e58: b 0x00255ea8 */ /* delay 00255e5c */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));goto L_00255ea8;
L_00255e60:;
/* 00255e60: b 0x00255e80 */ /* delay 00255e64 */ set(5,sx(UINT32_C(0x0000000a)));goto L_00255e80;
L_00255e68:;
/* 00255e68: lb a0,0x0(s0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 00255e6c: b 0x00255e80 */ /* delay 00255e70 */ set(5,sx(UINT32_C(0x00000009)));goto L_00255e80;
L_00255e78:;
/* 00255e78: lb a0,0x0(s0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 00255e7c: li a1,0xc */ set(5,sx(UINT32_C(0x0000000c)));
L_00255e80:;
/* 00255e80: jal 0x00267e50 */ set(31,0x00255e88u);/* delay 00255e84 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x00267e50u);
/* 00255e88: b 0x00255ea4 */ /* delay 00255e8c */ lw(4,ea(29,(int32_t)UINT32_C(0x00000070)));goto L_00255ea4;
L_00255e90:;
/* 00255e90: lb a0,0x0(s0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 00255e94: li a1,0xb */ set(5,sx(UINT32_C(0x0000000b)));
/* 00255e98: jal 0x00267e50 */ set(31,0x00255ea0u);/* delay 00255e9c */ set(6,cpu(0));nocturneBattleActionSkillCall(0x00267e50u);
L_00255ea0:;
/* 00255ea0: lw a0,0x70(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000070)));
L_00255ea4:;
/* 00255ea4: sltiu v0,a0,0x2 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
L_00255ea8:;
/* 00255ea8: beq v0,zero,0x00255ec8 */ {int taken=(cpu(2)==cpu(0));/* delay 00255eac */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00255ec8;}}
/* 00255eb0: addu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255eb4: li a1,0xb */ set(5,sx(UINT32_C(0x0000000b)));
/* 00255eb8: lb a0,0x0(v0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00255ebc: jal 0x00267e50 */ set(31,0x00255ec4u);/* delay 00255ec0 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x00267e50u);
/* 00255ec4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_00255ec8:;
/* 00255ec8: bne s3,v0,0x00255ee0 */ {int taken=(cpu(19)!=cpu(2));/* delay 00255ecc */ set(3,sx(UINT32_C(0x003e0000)));if(taken){goto L_00255ee0;}}
/* 00255ed0: move a0,s4 */ set(4,cpu(20));
/* 00255ed4: jal 0x00261758 */ set(31,0x00255edcu);/* delay 00255ed8 */ set(5,cpu(18));nocturneBattleActionSkillCall(0x00261758u);
/* 00255edc: lui v1,0x3e */ set(3,sx(UINT32_C(0x003e0000)));
L_00255ee0:;
/* 00255ee0: lw a0,0x78(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00255ee4: addiu v0,v1,-0x42e0 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xffffbd20)));
/* 00255ee8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00255eec: lbu v0,0x1(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0x00000001))));
/* 00255ef0: sltiu v1,v0,0x10 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00255ef4: beql v1,zero,0x00255f38 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00255ef8 */ set(2,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));goto L_00255f38;}}
/* 00255efc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00255f00: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00255f04: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00255f08: lw v1,0x3f40(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003f40)));
/* 00255f0c: jr v1 */ {uint64_t target=cpu(3);/* delay 00255f10 */ switch((uint32_t)target){case 0x00255f18u:goto L_00255f18;case 0x00255f20u:goto L_00255f20;case 0x00255f28u:goto L_00255f28;case 0x00255f30u:goto L_00255f30;case 0x00255f34u:goto L_00255f34;default:abort();}}
L_00255f18:;
/* 00255f18: b 0x00255f34 */ /* delay 00255f1c */ set(23,sx((uint32_t)cpu(23)+UINT32_C(0x00000005)));goto L_00255f34;
L_00255f20:;
/* 00255f20: b 0x00255f34 */ /* delay 00255f24 */ set(23,sx((uint32_t)cpu(23)+UINT32_C(0x00000008)));goto L_00255f34;
L_00255f28:;
/* 00255f28: b 0x00255f34 */ /* delay 00255f2c */ set(23,sx((uint32_t)cpu(23)+UINT32_C(0x0000000a)));goto L_00255f34;
L_00255f30:;
/* 00255f30: addiu s7,s7,0x1 */ set(23,sx((uint32_t)cpu(23)+UINT32_C(0x00000001)));
L_00255f34:;
/* 00255f34: sltiu v0,s3,0xa */ set(2,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
L_00255f38:;
/* 00255f38: beq v0,zero,0x00255fa8 */ {int taken=(cpu(2)==cpu(0));/* delay 00255f3c */ lw(4,ea(29,(int32_t)UINT32_C(0x00000080)));if(taken){goto L_00255fa8;}}
/* 00255f40: sll v0,s3,0x2 */ set(2,sx((uint32_t)cpu(19)<<2));
/* 00255f44: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00255f48: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00255f4c: lw v1,0x3f80(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003f80)));
/* 00255f50: jr v1 */ {uint64_t target=cpu(3);/* delay 00255f54 */ switch((uint32_t)target){case 0x00255f58u:goto L_00255f58;case 0x00255f68u:goto L_00255f68;case 0x00255f78u:goto L_00255f78;case 0x00255f88u:goto L_00255f88;case 0x00255f98u:goto L_00255f98;case 0x00255fa4u:goto L_00255fa4;default:abort();}}
L_00255f58:;
/* 00255f58: lw v0,0x54(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 00255f5c: ori v0,v0,0x4 */ set(2,cpu(2)|UINT32_C(0x00000004));
/* 00255f60: b 0x00255fa4 */ /* delay 00255f64 */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));goto L_00255fa4;
L_00255f68:;
/* 00255f68: lw v1,0x54(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 00255f6c: b 0x00255fa0 */ /* delay 00255f70 */ set(3,cpu(3)|UINT32_C(0x00000008));goto L_00255fa0;
L_00255f78:;
/* 00255f78: lw a0,0x54(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 00255f7c: ori a0,a0,0x20 */ set(4,cpu(4)|UINT32_C(0x00000020));
/* 00255f80: b 0x00255fa4 */ /* delay 00255f84 */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(4));goto L_00255fa4;
L_00255f88:;
/* 00255f88: lw v0,0x54(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 00255f8c: ori v0,v0,0x10 */ set(2,cpu(2)|UINT32_C(0x00000010));
/* 00255f90: b 0x00255fa4 */ /* delay 00255f94 */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));goto L_00255fa4;
L_00255f98:;
/* 00255f98: lw v1,0x54(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 00255f9c: ori v1,v1,0x40 */ set(3,cpu(3)|UINT32_C(0x00000040));
L_00255fa0:;
/* 00255fa0: sw v1,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(3));
L_00255fa4:;
/* 00255fa4: lw a0,0x80(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000080)));
L_00255fa8:;
/* 00255fa8: beq a0,zero,0x00255fbc */ {int taken=(cpu(4)==cpu(0));/* delay 00255fac */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00255fbc;}}
/* 00255fb0: bgtz s3,0x00255fc4 */ {int taken=((int64_t)cpu(19)>0);/* delay 00255fb4 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000044)));if(taken){goto L_00255fc4;}}
/* 00255fb8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_00255fbc:;
/* 00255fbc: sw v0,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(2));
/* 00255fc0: lw v1,0x44(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000044)));
L_00255fc4:;
/* 00255fc4: lw a0,0x4c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 00255fc8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 00255fcc: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00255fd0: slti v0,v1,0x20 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000020));
/* 00255fd4: sw v1,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(3));
/* 00255fd8: beq v0,zero,0x00255ff8 */ {int taken=(cpu(2)==cpu(0));/* delay 00255fdc */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(4));if(taken){goto L_00255ff8;}}
/* 00255fe0: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 00255fe4: move s5,v0 */ set(21,cpu(2));
/* 00255fe8: addu v1,sp,s5 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));
/* 00255fec: lb v0,0x0(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00255ff0: bgez v0,0x002558f0 */ {int taken=((int64_t)cpu(2)>=0);/* delay 00255ff4 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(21)));if(taken){goto L_002558f0;}}
L_00255ff8:;
/* 00255ff8: lw v0,0x64(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000064)));
/* 00255ffc: beq v0,zero,0x00256014 */ {int taken=(cpu(2)==cpu(0));/* delay 00256000 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000058)));if(taken){goto L_00256014;}}
/* 00256004: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00256008: xori v0,s6,0x108 */ set(2,cpu(22)^UINT32_C(0x00000108));
/* 0025600c: movz a0,v1,v0 */ if(cpu(2)==0){set(4,cpu(3));}
/* 00256010: sw a0,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(4));
L_00256014:;
/* 00256014: lw v0,0x68(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00256018: beq v0,zero,0x00256034 */ {int taken=(cpu(2)==cpu(0));/* delay 0025601c */ lw(4,ea(29,(int32_t)UINT32_C(0x00000058)));if(taken){goto L_00256034;}}
/* 00256020: addiu v0,s6,-0x106 */ set(2,sx((uint32_t)cpu(22)+UINT32_C(0xfffffefa)));
/* 00256024: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00256028: sltiu v0,v0,0x2 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0025602c: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
/* 00256030: sw a0,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(4));
L_00256034:;
/* 00256034: bne s6,zero,0x00256140 */ {int taken=(cpu(22)!=cpu(0));/* delay 00256038 */ set(2,sx(UINT32_C(0x0000011e)));if(taken){goto L_00256140;}}
/* 0025603c: lw v0,0x58(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000058)));
/* 00256040: bnel v0,zero,0x00256140 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00256044 */ set(2,sx(UINT32_C(0x0000011e)));goto L_00256140;}}
/* 00256048: lw a0,0x2c(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x0000002c)));
/* 0025604c: jal 0x0026a3d8 */ set(31,0x00256054u);/* delay 00256050 */ set(5,sx(UINT32_C(0x0000012e)));nocturneBattleActionSkillCall(0x0026a3d8u);
/* 00256054: beq v0,zero,0x0025613c */ {int taken=(cpu(2)==cpu(0));/* delay 00256058 */ set(4,cpu(18));if(taken){goto L_0025613c;}}
/* 0025605c: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00256060: jal 0x002515e8 */ set(31,0x00256068u);/* delay 00256064 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002515e8u);
/* 00256068: bne v0,zero,0x00256140 */ {int taken=(cpu(2)!=cpu(0));/* delay 0025606c */ set(2,sx(UINT32_C(0x0000011e)));if(taken){goto L_00256140;}}
/* 00256070: li v0,0x12e */ set(2,sx(UINT32_C(0x0000012e)));
/* 00256074: move a0,s2 */ set(4,cpu(18));
/* 00256078: jal 0x00251858 */ set(31,0x00256080u);/* delay 0025607c */ sw(ea(18,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x00251858u);
/* 00256080: lui a0,0x3e */ set(4,sx(UINT32_C(0x003e0000)));
/* 00256084: addiu a0,a0,-0x3e60 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffc1a0)));
/* 00256088: lw a2,0x5c(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000005c)));
/* 0025608c: lh a1,0x70(a0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000070))));
/* 00256090: move s1,v0 */ set(17,cpu(2));
/* 00256094: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 00256098: div a2,a1 */ nativeDivide((uint32_t)cpu(6),(uint32_t)cpu(5),1,0);
/* 0025609c: beql a1,zero,0x002560a4 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 002560a0 */ nocturneCompilerArithmeticTrap(7u);goto L_002560a4;}}
L_002560a4:;
/* 002560a4: move s0,v0 */ set(16,cpu(2));
/* 002560a8: move t1,v0 */ set(9,cpu(2));
/* 002560ac: lh v1,0x72(a0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000072))));
/* 002560b0: lw v0,0x60(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000060)));
/* 002560b4: mflo a2 */ set(6,nocturneEffectHostLo());
/* 002560b8: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 002560bc: movn s0,a2,a2 */ if(cpu(6)!=0){set(16,cpu(6));}
/* 002560c0: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002560c4: bgtz s0,0x002560d4 */ {int taken=((int64_t)cpu(16)>0);/* delay 002560c8 */ if(cpu(2)!=0){set(9,cpu(2));}if(taken){goto L_002560d4;}}
/* 002560cc: blezl t1,0x00256140 */ {int taken=((int64_t)cpu(9)<=0);if(taken){/* delay 002560d0 */ set(2,sx(UINT32_C(0x0000011e)));goto L_00256140;}}
L_002560d4:;
/* 002560d4: lw a2,0x28(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002560d8: move a0,s1 */ set(4,cpu(17));
/* 002560dc: move a1,s2 */ set(5,cpu(18));
/* 002560e0: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 002560e4: move t0,s0 */ set(8,cpu(16));
/* 002560e8: jal 0x00264010 */ set(31,0x002560f0u);/* delay 002560ec */ set(10,cpu(0));nocturneBattleActionSkillCall(0x00264010u);
/* 002560f0: blez s0,0x00256108 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002560f4 */ set(6,cpu(16));if(taken){goto L_00256108;}}
/* 002560f8: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002560fc: move a0,s2 */ set(4,cpu(18));
/* 00256100: jal 0x002516e8 */ set(31,0x00256108u);/* delay 00256104 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002516e8u);
L_00256108:;
/* 00256108: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 0025610c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00256110: move a2,s1 */ set(6,cpu(17));
/* 00256114: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00256118: move a0,s2 */ set(4,cpu(18));
/* 0025611c: nop  */ 
/* 00256120: nop  */ 
/* 00256124: div.S f0,f0,f21 */ f[0]=EE_FPU_DIV_S(f[0],f[21]);
/* 00256128: lh a1,0x92(v0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));
/* 0025612c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00256130: mfc1 a3,f1 */ set(7,sx(f[1]));
/* 00256134: jal 0x002517e0 */ set(31,0x0025613cu);/* delay 00256138 */ set(8,cpu(7));nocturneBattleActionSkillCall(0x002517e0u);
L_0025613c:;
/* 0025613c: li v0,0x11e */ set(2,sx(UINT32_C(0x0000011e)));
L_00256140:;
/* 00256140: bne s6,v0,0x00256234 */ {int taken=(cpu(22)!=cpu(2));/* delay 00256144 */ set(2,sx(UINT32_C(0x00000109)));if(taken){goto L_00256234;}}
/* 00256148: lw v0,0x58(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000058)));
/* 0025614c: bne v0,zero,0x00256234 */ {int taken=(cpu(2)!=cpu(0));/* delay 00256150 */ set(2,sx(UINT32_C(0x00000109)));if(taken){goto L_00256234;}}
/* 00256154: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00256158: move a0,s2 */ set(4,cpu(18));
/* 0025615c: jal 0x002515e8 */ set(31,0x00256164u);/* delay 00256160 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002515e8u);
/* 00256164: bne v0,zero,0x00256234 */ {int taken=(cpu(2)!=cpu(0));/* delay 00256168 */ set(2,sx(UINT32_C(0x00000109)));if(taken){goto L_00256234;}}
/* 0025616c: lw v0,0x44(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000044)));
/* 00256170: bne v0,zero,0x00256234 */ {int taken=(cpu(2)!=cpu(0));/* delay 00256174 */ set(2,sx(UINT32_C(0x00000109)));if(taken){goto L_00256234;}}
/* 00256178: li v0,0x12e */ set(2,sx(UINT32_C(0x0000012e)));
/* 0025617c: move a0,s2 */ set(4,cpu(18));
/* 00256180: sw v0,0x58(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(2));
/* 00256184: jal 0x00251858 */ set(31,0x0025618cu);/* delay 00256188 */ set(16,sx(UINT32_C(0xffffffff)));nocturneBattleActionSkillCall(0x00251858u);
/* 0025618c: sw zero,0x58(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(0));
/* 00256190: lw a0,0x2c(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x0000002c)));
/* 00256194: move s1,v0 */ set(17,cpu(2));
/* 00256198: lui v0,0x3e */ set(2,sx(UINT32_C(0x003e0000)));
/* 0025619c: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 002561a0: lb a1,-0x4334(v0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0xffffbccc))));
/* 002561a4: beql v1,zero,0x002561ac */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002561a8 */ nocturneCompilerArithmeticTrap(7u);goto L_002561ac;}}
L_002561ac:;
/* 002561ac: lhu v0,0x8(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000008))));
/* 002561b0: mult v0,v0,a1 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(5),1,0);
/* 002561b4: div1 v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,1);
/* 002561b8: mflo1 v0 */ set(2,nocturneBattleActionFormulaSecondaryLo());
/* 002561bc: movn s0,v0,v0 */ if(cpu(2)!=0){set(16,cpu(2));}
/* 002561c0: blezl s0,0x00256234 */ {int taken=((int64_t)cpu(16)<=0);if(taken){/* delay 002561c4 */ set(2,sx(UINT32_C(0x00000109)));goto L_00256234;}}
/* 002561c8: lw a2,0x28(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002561cc: move a3,zero */ set(7,cpu(0));
/* 002561d0: move t0,s0 */ set(8,cpu(16));
/* 002561d4: move a0,s1 */ set(4,cpu(17));
/* 002561d8: move a1,s2 */ set(5,cpu(18));
/* 002561dc: li t1,-0x1 */ set(9,sx(UINT32_C(0xffffffff)));
/* 002561e0: jal 0x00264010 */ set(31,0x002561e8u);/* delay 002561e4 */ set(10,cpu(0));nocturneBattleActionSkillCall(0x00264010u);
/* 002561e8: lw v1,0x28(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002561ec: move a2,s0 */ set(6,cpu(16));
/* 002561f0: move a0,s2 */ set(4,cpu(18));
/* 002561f4: jal 0x002516e8 */ set(31,0x002561fcu);/* delay 002561f8 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002516e8u);
/* 002561fc: lw v1,0x28(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00256200: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 00256204: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00256208: move a2,s1 */ set(6,cpu(17));
/* 0025620c: lh a1,0x92(v1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));
/* 00256210: move a0,s2 */ set(4,cpu(18));
/* 00256214: nop  */ 
/* 00256218: nop  */ 
/* 0025621c: div.S f0,f0,f21 */ f[0]=EE_FPU_DIV_S(f[0],f[21]);
/* 00256220: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00256224: mfc1 a3,f1 */ set(7,sx(f[1]));
/* 00256228: jal 0x002517e0 */ set(31,0x00256230u);/* delay 0025622c */ set(8,cpu(7));nocturneBattleActionSkillCall(0x002517e0u);
/* 00256230: li v0,0x109 */ set(2,sx(UINT32_C(0x00000109)));
L_00256234:;
/* 00256234: bne s6,v0,0x00256308 */ {int taken=(cpu(22)!=cpu(2));/* delay 00256238 */ if(taken){goto L_00256308;}}
/* 0025623c: lw v0,0x58(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000058)));
/* 00256240: bne v0,zero,0x00256308 */ {int taken=(cpu(2)!=cpu(0));/* delay 00256244 */ if(taken){goto L_00256308;}}
/* 00256248: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 0025624c: move a0,s2 */ set(4,cpu(18));
/* 00256250: jal 0x002515e8 */ set(31,0x00256258u);/* delay 00256254 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002515e8u);
/* 00256258: bne v0,zero,0x00256308 */ {int taken=(cpu(2)!=cpu(0));/* delay 0025625c */ if(taken){goto L_00256308;}}
/* 00256260: lw v0,0x44(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000044)));
/* 00256264: bne v0,zero,0x00256308 */ {int taken=(cpu(2)!=cpu(0));/* delay 00256268 */ set(2,sx(UINT32_C(0x0000012e)));if(taken){goto L_00256308;}}
/* 0025626c: move a0,s2 */ set(4,cpu(18));
/* 00256270: sw v0,0x58(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(2));
/* 00256274: jal 0x00251858 */ set(31,0x0025627cu);/* delay 00256278 */ set(16,sx(UINT32_C(0xffffffff)));nocturneBattleActionSkillCall(0x00251858u);
/* 0025627c: sw zero,0x58(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(0));
/* 00256280: lw a0,0x2c(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x0000002c)));
/* 00256284: move s1,v0 */ set(17,cpu(2));
/* 00256288: lui v0,0x3e */ set(2,sx(UINT32_C(0x003e0000)));
/* 0025628c: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00256290: lh a1,-0x4830(v0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0xffffb7d0))));
/* 00256294: beql v1,zero,0x0025629c */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00256298 */ nocturneCompilerArithmeticTrap(7u);goto L_0025629c;}}
L_0025629c:;
/* 0025629c: lhu v0,0xc(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000000c))));
/* 002562a0: mult v0,v0,a1 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(5),1,0);
/* 002562a4: div1 v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,1);
/* 002562a8: mflo1 v0 */ set(2,nocturneBattleActionFormulaSecondaryLo());
/* 002562ac: movn s0,v0,v0 */ if(cpu(2)!=0){set(16,cpu(2));}
/* 002562b0: blez s0,0x00256308 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002562b4 */ set(5,cpu(18));if(taken){goto L_00256308;}}
/* 002562b8: lw a2,0x28(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002562bc: move a0,s1 */ set(4,cpu(17));
/* 002562c0: move a3,zero */ set(7,cpu(0));
/* 002562c4: li t0,-0x1 */ set(8,sx(UINT32_C(0xffffffff)));
/* 002562c8: move t1,s0 */ set(9,cpu(16));
/* 002562cc: jal 0x00264010 */ set(31,0x002562d4u);/* delay 002562d0 */ set(10,cpu(0));nocturneBattleActionSkillCall(0x00264010u);
/* 002562d4: lw v1,0x28(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002562d8: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 002562dc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002562e0: move a2,s1 */ set(6,cpu(17));
/* 002562e4: lh a1,0x92(v1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));
/* 002562e8: move a0,s2 */ set(4,cpu(18));
/* 002562ec: nop  */ 
/* 002562f0: nop  */ 
/* 002562f4: div.S f0,f0,f21 */ f[0]=EE_FPU_DIV_S(f[0],f[21]);
/* 002562f8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 002562fc: mfc1 a3,f1 */ set(7,sx(f[1]));
/* 00256300: jal 0x002517e0 */ set(31,0x00256308u);/* delay 00256304 */ set(8,cpu(7));nocturneBattleActionSkillCall(0x002517e0u);
L_00256308:;
/* 00256308: jal 0x0016ba40 */ set(31,0x00256310u);/* delay 0025630c */ lw(4,ea(29,(int32_t)UINT32_C(0x00000054)));nocturneBattleActionSkillCall(0x0016ba40u);
/* 00256310: jal 0x00251858 */ set(31,0x00256318u);/* delay 00256314 */ set(4,cpu(18));nocturneBattleActionSkillCall(0x00251858u);
/* 00256318: lwc1 f1,-0x5c78(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa388)));
/* 0025631c: move s1,v0 */ set(17,cpu(2));
/* 00256320: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00256324: mtc1 s1,f0 */ f[0]=(uint32_t)cpu(17);
/* 00256328: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0025632c: move a0,s2 */ set(4,cpu(18));
/* 00256330: lh a1,0x92(v0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));
/* 00256334: move a2,zero */ set(6,cpu(0));
/* 00256338: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0025633c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00256340: mfc1 a3,f1 */ set(7,sx(f[1]));
/* 00256344: jal 0x00251770 */ set(31,0x0025634cu);/* delay 00256348 */ set(8,sx(UINT32_C(0xffffffff)));body_00251770();
/* 0025634c: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00256350: move a0,s2 */ set(4,cpu(18));
/* 00256354: jal 0x002515e8 */ set(31,0x0025635cu);/* delay 00256358 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002515e8u);
/* 0025635c: beql v0,zero,0x002563c0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00256360 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_002563c0;}}
/* 00256364: lw v1,0x24(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000024)));
/* 00256368: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 0025636c: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00256370: bnel v0,zero,0x002563c0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00256374 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_002563c0;}}
/* 00256378: lw a0,0x50(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0025637c: move a1,s2 */ set(5,cpu(18));
/* 00256380: lw a2,0x28(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00256384: move a3,zero */ set(7,cpu(0));
/* 00256388: jal 0x00263918 */ set(31,0x00256390u);/* delay 0025638c */ set(8,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x00263918u);
/* 00256390: lw v1,0x28(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 00256394: lw a2,0x50(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00256398: move a0,s2 */ set(4,cpu(18));
/* 0025639c: lh a1,0x92(v1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000092))));
/* 002563a0: li a3,0x1e */ set(7,sx(UINT32_C(0x0000001e)));
/* 002563a4: jal 0x002517e0 */ set(31,0x002563acu);/* delay 002563a8 */ set(8,sx(UINT32_C(0x0000001e)));nocturneBattleActionSkillCall(0x002517e0u);
/* 002563ac: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002563b0: move a0,s2 */ set(4,cpu(18));
/* 002563b4: jal 0x0024f478 */ set(31,0x002563bcu);/* delay 002563b8 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x0024f478u);
/* 002563bc: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
L_002563c0:;
/* 002563c0: move a0,s2 */ set(4,cpu(18));
/* 002563c4: jal 0x002515e8 */ set(31,0x002563ccu);/* delay 002563c8 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002515e8u);
/* 002563cc: bnel v0,zero,0x002563ec */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002563d0 */ lw(6,ea(18,(int32_t)UINT32_C(0x00000060)));goto L_002563ec;}}
/* 002563d4: lw v0,0x34(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000034)));
/* 002563d8: bnel v0,zero,0x002563ec */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002563dc */ lw(6,ea(18,(int32_t)UINT32_C(0x00000060)));goto L_002563ec;}}
/* 002563e0: jal 0x00252060 */ set(31,0x002563e8u);/* delay 002563e4 */ set(4,cpu(18));body_00252060();
/* 002563e8: lw a2,0x60(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000060)));
L_002563ec:;
/* 002563ec: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 002563f0: lw a1,0x5c(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x0000005c)));
/* 002563f4: jal 0x002d4748 */ set(31,0x002563fcu);/* delay 002563f8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00003e58)));nocturneBattleActionSkillCall(0x002d4748u);
/* 002563fc: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00256400: move a1,s1 */ set(5,cpu(17));
/* 00256404: jal 0x002d4748 */ set(31,0x0025640cu);/* delay 00256408 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00003e78)));nocturneBattleActionSkillCall(0x002d4748u);
/* 0025640c: jal 0x00251890 */ set(31,0x00256414u);/* delay 00256410 */ set(4,cpu(18));nocturneBattleActionSkillCall(0x00251890u);
/* 00256414: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00256418: addiu a0,a0,0x3e98 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00003e98)));
/* 0025641c: jal 0x002d4748 */ set(31,0x00256424u);/* delay 00256420 */ set(5,cpu(2));nocturneBattleActionSkillCall(0x002d4748u);
/* 00256424: lw a0,0x44(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000044)));
/* 00256428: bnel a0,zero,0x002567d0 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 0025642c */ lw(6,ea(18,(int32_t)UINT32_C(0x00000048)));goto L_002567d0;}}
/* 00256430: lw v1,0x58(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000058)));
/* 00256434: beq v1,zero,0x00256490 */ {int taken=(cpu(3)==cpu(0));/* delay 00256438 */ set(2,sx(UINT32_C(0x0000012c)));if(taken){goto L_00256490;}}
/* 0025643c: beq v1,v0,0x00256478 */ {int taken=(cpu(3)==cpu(2));/* delay 00256440 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000012d));if(taken){goto L_00256478;}}
/* 00256444: beq v0,zero,0x00256460 */ {int taken=(cpu(2)==cpu(0));/* delay 00256448 */ set(2,sx(UINT32_C(0x0000012d)));if(taken){goto L_00256460;}}
/* 0025644c: li v0,0x12b */ set(2,sx(UINT32_C(0x0000012b)));
/* 00256450: beql v1,v0,0x00256484 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 00256454 */ set(4,sx(UINT32_C(0x0000012b)));goto L_00256484;}}
/* 00256458: b 0x00256490 */ /* delay 0025645c */ goto L_00256490;
L_00256460:;
/* 00256460: beq v1,v0,0x00256480 */ {int taken=(cpu(3)==cpu(2));/* delay 00256464 */ set(2,sx(UINT32_C(0x0000012e)));if(taken){goto L_00256480;}}
/* 00256468: beql v1,v0,0x00256484 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 0025646c */ set(4,sx(UINT32_C(0x0000012e)));goto L_00256484;}}
/* 00256470: b 0x00256490 */ /* delay 00256474 */ goto L_00256490;
L_00256478:;
/* 00256478: b 0x00256484 */ /* delay 0025647c */ set(4,sx(UINT32_C(0x0000012c)));goto L_00256484;
L_00256480:;
/* 00256480: li a0,0x12d */ set(4,sx(UINT32_C(0x0000012d)));
L_00256484:;
/* 00256484: jal 0x00289008 */ set(31,0x0025648cu);/* delay 00256488 */ nocturneBattleActionSkillCall(0x00289008u);
/* 0025648c: lw a0,0x44(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000044)));
L_00256490:;
/* 00256490: bnel a0,zero,0x002567d0 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 00256494 */ lw(6,ea(18,(int32_t)UINT32_C(0x00000048)));goto L_002567d0;}}
/* 00256498: li v0,0x46 */ set(2,sx(UINT32_C(0x00000046)));
/* 0025649c: beq s6,v0,0x00256688 */ {int taken=(cpu(22)==cpu(2));/* delay 002564a0 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000047));if(taken){goto L_00256688;}}
/* 002564a4: beq v0,zero,0x00256548 */ {int taken=(cpu(2)==cpu(0));/* delay 002564a8 */ set(2,sx(UINT32_C(0x000000ce)));if(taken){goto L_00256548;}}
/* 002564ac: li v0,0x40 */ set(2,sx(UINT32_C(0x00000040)));
/* 002564b0: beq s6,v0,0x00256638 */ {int taken=(cpu(22)==cpu(2));/* delay 002564b4 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000041));if(taken){goto L_00256638;}}
/* 002564b8: beq v0,zero,0x00256500 */ {int taken=(cpu(2)==cpu(0));/* delay 002564bc */ set(2,sx(UINT32_C(0x00000043)));if(taken){goto L_00256500;}}
/* 002564c0: li v0,0x35 */ set(2,sx(UINT32_C(0x00000035)));
/* 002564c4: beq s6,v0,0x00256600 */ {int taken=(cpu(22)==cpu(2));/* delay 002564c8 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000036));if(taken){goto L_00256600;}}
/* 002564cc: beq v0,zero,0x002564e8 */ {int taken=(cpu(2)==cpu(0));/* delay 002564d0 */ set(2,sx(UINT32_C(0x00000036)));if(taken){goto L_002564e8;}}
/* 002564d4: li v0,0x34 */ set(2,sx(UINT32_C(0x00000034)));
/* 002564d8: beq s6,v0,0x002565e0 */ {int taken=(cpu(22)==cpu(2));/* delay 002564dc */ lw(3,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_002565e0;}}
/* 002564e0: b 0x00256748 */ /* delay 002564e4 */ goto L_00256748;
L_002564e8:;
/* 002564e8: beq s6,v0,0x002565f0 */ {int taken=(cpu(22)==cpu(2));/* delay 002564ec */ set(2,sx(UINT32_C(0x00000039)));if(taken){goto L_002565f0;}}
/* 002564f0: beq s6,v0,0x00256610 */ {int taken=(cpu(22)==cpu(2));/* delay 002564f4 */ lw(3,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_00256610;}}
/* 002564f8: b 0x00256748 */ /* delay 002564fc */ goto L_00256748;
L_00256500:;
/* 00256500: beq s6,v0,0x00256668 */ {int taken=(cpu(22)==cpu(2));/* delay 00256504 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000044));if(taken){goto L_00256668;}}
/* 00256508: beq v0,zero,0x00256530 */ {int taken=(cpu(2)==cpu(0));/* delay 0025650c */ set(2,sx(UINT32_C(0x00000044)));if(taken){goto L_00256530;}}
/* 00256510: li v0,0x41 */ set(2,sx(UINT32_C(0x00000041)));
/* 00256514: beq s6,v0,0x00256648 */ {int taken=(cpu(22)==cpu(2));/* delay 00256518 */ set(2,sx(UINT32_C(0x00000042)));if(taken){goto L_00256648;}}
/* 0025651c: beq s6,v0,0x00256658 */ {int taken=(cpu(22)==cpu(2));/* delay 00256520 */ lw(3,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_00256658;}}
/* 00256524: b 0x00256748 */ /* delay 00256528 */ goto L_00256748;
L_00256530:;
/* 00256530: beq s6,v0,0x00256678 */ {int taken=(cpu(22)==cpu(2));/* delay 00256534 */ set(2,sx(UINT32_C(0x00000045)));if(taken){goto L_00256678;}}
/* 00256538: beq s6,v0,0x00256698 */ {int taken=(cpu(22)==cpu(2));/* delay 0025653c */ lw(3,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_00256698;}}
/* 00256540: b 0x00256748 */ /* delay 00256544 */ goto L_00256748;
L_00256548:;
/* 00256548: beq s6,v0,0x002566f8 */ {int taken=(cpu(22)==cpu(2));/* delay 0025654c */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x000000cf));if(taken){goto L_002566f8;}}
/* 00256550: beq v0,zero,0x00256598 */ {int taken=(cpu(2)==cpu(0));/* delay 00256554 */ set(2,sx(UINT32_C(0x00000112)));if(taken){goto L_00256598;}}
/* 00256558: li v0,0xcb */ set(2,sx(UINT32_C(0x000000cb)));
/* 0025655c: beq s6,v0,0x002566a8 */ {int taken=(cpu(22)==cpu(2));/* delay 00256560 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x000000cc));if(taken){goto L_002566a8;}}
/* 00256564: beq v0,zero,0x00256580 */ {int taken=(cpu(2)==cpu(0));/* delay 00256568 */ set(2,sx(UINT32_C(0x000000cc)));if(taken){goto L_00256580;}}
/* 0025656c: li v0,0x4d */ set(2,sx(UINT32_C(0x0000004d)));
/* 00256570: beq s6,v0,0x00256708 */ {int taken=(cpu(22)==cpu(2));/* delay 00256574 */ lw(3,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_00256708;}}
/* 00256578: b 0x00256748 */ /* delay 0025657c */ goto L_00256748;
L_00256580:;
/* 00256580: beq s6,v0,0x002566b8 */ {int taken=(cpu(22)==cpu(2));/* delay 00256584 */ set(2,sx(UINT32_C(0x000000cd)));if(taken){goto L_002566b8;}}
/* 00256588: beq s6,v0,0x002566c8 */ {int taken=(cpu(22)==cpu(2));/* delay 0025658c */ lw(3,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_002566c8;}}
/* 00256590: b 0x00256748 */ /* delay 00256594 */ goto L_00256748;
L_00256598:;
/* 00256598: beq s6,v0,0x002566e8 */ {int taken=(cpu(22)==cpu(2));/* delay 0025659c */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000113));if(taken){goto L_002566e8;}}
/* 002565a0: beq v0,zero,0x002565c8 */ {int taken=(cpu(2)==cpu(0));/* delay 002565a4 */ set(2,sx(UINT32_C(0x00000114)));if(taken){goto L_002565c8;}}
/* 002565a8: li v0,0x109 */ set(2,sx(UINT32_C(0x00000109)));
/* 002565ac: beq s6,v0,0x002566d8 */ {int taken=(cpu(22)==cpu(2));/* delay 002565b0 */ set(2,sx(UINT32_C(0x00000110)));if(taken){goto L_002566d8;}}
/* 002565b4: beq s6,v0,0x00256728 */ {int taken=(cpu(22)==cpu(2));/* delay 002565b8 */ lw(3,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_00256728;}}
/* 002565bc: b 0x00256748 */ /* delay 002565c0 */ goto L_00256748;
L_002565c8:;
/* 002565c8: beq s6,v0,0x00256718 */ {int taken=(cpu(22)==cpu(2));/* delay 002565cc */ set(2,sx(UINT32_C(0x0000011a)));if(taken){goto L_00256718;}}
/* 002565d0: beq s6,v0,0x00256620 */ {int taken=(cpu(22)==cpu(2));/* delay 002565d4 */ lw(3,ea(29,(int32_t)UINT32_C(0x0000006c)));if(taken){goto L_00256620;}}
/* 002565d8: b 0x00256748 */ /* delay 002565dc */ goto L_00256748;
L_002565e0:;
/* 002565e0: move a0,s2 */ set(4,cpu(18));
/* 002565e4: b 0x00256730 */ /* delay 002565e8 */ set(5,sx(UINT32_C(0x00000010)));goto L_00256730;
L_002565f0:;
/* 002565f0: move a0,s2 */ set(4,cpu(18));
/* 002565f4: b 0x00256730 */ /* delay 002565f8 */ set(5,sx(UINT32_C(0x00000012)));goto L_00256730;
L_00256600:;
/* 00256600: move a0,s2 */ set(4,cpu(18));
/* 00256604: b 0x00256730 */ /* delay 00256608 */ set(5,sx(UINT32_C(0x00000014)));goto L_00256730;
L_00256610:;
/* 00256610: move a0,s2 */ set(4,cpu(18));
/* 00256614: b 0x00256730 */ /* delay 00256618 */ set(5,sx(UINT32_C(0x00000016)));goto L_00256730;
L_00256620:;
/* 00256620: lw v0,0x60(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00256624: beq v0,zero,0x00256770 */ {int taken=(cpu(2)==cpu(0));/* delay 00256628 */ set(5,sx(UINT32_C(0x00000016)));if(taken){goto L_00256770;}}
/* 0025662c: b 0x00256730 */ /* delay 00256630 */ set(4,cpu(18));goto L_00256730;
L_00256638:;
/* 00256638: move a0,s2 */ set(4,cpu(18));
/* 0025663c: b 0x00256730 */ /* delay 00256640 */ set(5,sx(UINT32_C(0x00000018)));goto L_00256730;
L_00256648:;
/* 00256648: move a0,s2 */ set(4,cpu(18));
/* 0025664c: b 0x00256730 */ /* delay 00256650 */ set(5,sx(UINT32_C(0x0000001a)));goto L_00256730;
L_00256658:;
/* 00256658: move a0,s2 */ set(4,cpu(18));
/* 0025665c: b 0x00256730 */ /* delay 00256660 */ set(5,sx(UINT32_C(0x0000001c)));goto L_00256730;
L_00256668:;
/* 00256668: move a0,s2 */ set(4,cpu(18));
/* 0025666c: b 0x00256730 */ /* delay 00256670 */ set(5,sx(UINT32_C(0x0000001e)));goto L_00256730;
L_00256678:;
/* 00256678: move a0,s2 */ set(4,cpu(18));
/* 0025667c: b 0x00256730 */ /* delay 00256680 */ set(5,sx(UINT32_C(0x00000020)));goto L_00256730;
L_00256688:;
/* 00256688: move a0,s2 */ set(4,cpu(18));
/* 0025668c: b 0x00256730 */ /* delay 00256690 */ set(5,sx(UINT32_C(0x00000022)));goto L_00256730;
L_00256698:;
/* 00256698: move a0,s2 */ set(4,cpu(18));
/* 0025669c: b 0x00256730 */ /* delay 002566a0 */ set(5,sx(UINT32_C(0x00000024)));goto L_00256730;
L_002566a8:;
/* 002566a8: move a0,s2 */ set(4,cpu(18));
/* 002566ac: b 0x00256730 */ /* delay 002566b0 */ set(5,sx(UINT32_C(0x00000050)));goto L_00256730;
L_002566b8:;
/* 002566b8: move a0,s2 */ set(4,cpu(18));
/* 002566bc: b 0x00256730 */ /* delay 002566c0 */ set(5,sx(UINT32_C(0x00000052)));goto L_00256730;
L_002566c8:;
/* 002566c8: move a0,s2 */ set(4,cpu(18));
/* 002566cc: b 0x00256730 */ /* delay 002566d0 */ set(5,sx(UINT32_C(0x00000054)));goto L_00256730;
L_002566d8:;
/* 002566d8: move a0,s2 */ set(4,cpu(18));
/* 002566dc: b 0x00256730 */ /* delay 002566e0 */ set(5,sx(UINT32_C(0x00000054)));goto L_00256730;
L_002566e8:;
/* 002566e8: move a0,s2 */ set(4,cpu(18));
/* 002566ec: b 0x00256730 */ /* delay 002566f0 */ set(5,sx(UINT32_C(0x0000005c)));goto L_00256730;
L_002566f8:;
/* 002566f8: move a0,s2 */ set(4,cpu(18));
/* 002566fc: b 0x00256730 */ /* delay 00256700 */ set(5,sx(UINT32_C(0x00000056)));goto L_00256730;
L_00256708:;
/* 00256708: move a0,s2 */ set(4,cpu(18));
/* 0025670c: b 0x00256730 */ /* delay 00256710 */ set(5,sx(UINT32_C(0x0000005c)));goto L_00256730;
L_00256718:;
/* 00256718: move a0,s2 */ set(4,cpu(18));
/* 0025671c: b 0x00256730 */ /* delay 00256720 */ set(5,sx(UINT32_C(0x00000062)));goto L_00256730;
L_00256728:;
/* 00256728: move a0,s2 */ set(4,cpu(18));
/* 0025672c: li a1,0x60 */ set(5,sx(UINT32_C(0x00000060)));
L_00256730:;
/* 00256730: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 00256734: jal 0x002592b0 */ set(31,0x0025673cu);/* delay 00256738 */ set(7,cpu(0));nocturneBattleActionSkillCall(0x002592b0u);
/* 0025673c: b 0x00256774 */ /* delay 00256740 */ lw(5,ea(18,(int32_t)UINT32_C(0x0000003c)));goto L_00256774;
L_00256748:;
/* 00256748: beql v1,zero,0x00256774 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0025674c */ lw(5,ea(18,(int32_t)UINT32_C(0x0000003c)));goto L_00256774;}}
/* 00256750: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00256754: lw v1,0x14c(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000014c)));
/* 00256758: beq v1,zero,0x00256770 */ {int taken=(cpu(3)==cpu(0));/* delay 0025675c */ set(5,sx(UINT32_C(0x00000064)));if(taken){goto L_00256770;}}
/* 00256760: move a0,s2 */ set(4,cpu(18));
/* 00256764: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 00256768: jal 0x002592b0 */ set(31,0x00256770u);/* delay 0025676c */ set(7,cpu(0));nocturneBattleActionSkillCall(0x002592b0u);
L_00256770:;
/* 00256770: lw a1,0x3c(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x0000003c)));
L_00256774:;
/* 00256774: jal 0x00290780 */ set(31,0x0025677cu);/* delay 00256778 */ set(4,cpu(22));nocturneBattleActionSkillCall(0x00290780u);
/* 0025677c: beq v0,zero,0x002567a0 */ {int taken=(cpu(2)==cpu(0));/* delay 00256780 */ set(4,sx(UINT32_C(0x00540000)));if(taken){goto L_002567a0;}}
/* 00256784: jal 0x002d4748 */ set(31,0x0025678cu);/* delay 00256788 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00003eb8)));nocturneBattleActionSkillCall(0x002d4748u);
/* 0025678c: move a0,s2 */ set(4,cpu(18));
/* 00256790: li a1,0x44 */ set(5,sx(UINT32_C(0x00000044)));
/* 00256794: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 00256798: jal 0x002592b0 */ set(31,0x002567a0u);/* delay 0025679c */ set(7,cpu(0));nocturneBattleActionSkillCall(0x002592b0u);
L_002567a0:;
/* 002567a0: lw a2,0x48(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000048)));
/* 002567a4: blez a2,0x00256838 */ {int taken=((int64_t)cpu(6)<=0);/* delay 002567a8 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000040)));if(taken){goto L_00256838;}}
/* 002567ac: lw v0,0x4(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 002567b0: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 002567b4: beq v0,zero,0x002567d0 */ {int taken=(cpu(2)==cpu(0));/* delay 002567b8 */ set(2,cpu(6)&UINT32_C(0x00000001));if(taken){goto L_002567d0;}}
/* 002567bc: bnel v0,zero,0x002567c8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002567c0 */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));goto L_002567c8;}}
/* 002567c4: addiu v0,a2,0x1 */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
L_002567c8:;
/* 002567c8: sw v0,0x48(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(2));
/* 002567cc: move a2,v0 */ set(6,cpu(2));
L_002567d0:;
/* 002567d0: blez a2,0x00256838 */ {int taken=((int64_t)cpu(6)<=0);/* delay 002567d4 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000040)));if(taken){goto L_00256838;}}
/* 002567d8: slti v0,s6,0x33 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000033));
/* 002567dc: beql v0,zero,0x00256820 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002567e0 */ lw(7,ea(18,(int32_t)UINT32_C(0x0000004c)));goto L_00256820;}}
/* 002567e4: slti v0,s6,0x31 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000031));
/* 002567e8: bnel v0,zero,0x00256820 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002567ec */ lw(7,ea(18,(int32_t)UINT32_C(0x0000004c)));goto L_00256820;}}
/* 002567f0: lw a0,0x50(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002567f4: li a3,0x28 */ set(7,sx(UINT32_C(0x00000028)));
/* 002567f8: lw v0,0x28(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002567fc: li t0,0x28 */ set(8,sx(UINT32_C(0x00000028)));
/* 00256800: addiu a0,a0,0x14 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000014)));
/* 00256804: sw a0,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(4));
/* 00256808: move a0,s2 */ set(4,cpu(18));
/* 0025680c: lw a2,0x50(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00256810: jal 0x002517e0 */ set(31,0x00256818u);/* delay 00256814 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000092))));nocturneBattleActionSkillCall(0x002517e0u);
/* 00256818: lw a2,0x48(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000048)));
/* 0025681c: lw a3,0x4c(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x0000004c)));
L_00256820:;
/* 00256820: move a1,s2 */ set(5,cpu(18));
/* 00256824: lw t0,0x50(s2) */ lw(8,ea(18,(int32_t)UINT32_C(0x00000050)));
/* 00256828: jal 0x00262ed8 */ set(31,0x00256830u);/* delay 0025682c */ lw(4,ea(29,(int32_t)UINT32_C(0x00000050)));body_00262ed8();
/* 00256830: sw zero,0x48(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 00256834: lw v0,0x40(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000040)));
L_00256838:;
/* 00256838: beq v0,zero,0x002568d0 */ {int taken=(cpu(2)==cpu(0));/* delay 0025683c */ set(4,cpu(2));if(taken){goto L_002568d0;}}
/* 00256840: jal 0x0016aef0 */ set(31,0x00256848u);/* delay 00256844 */ set(5,cpu(17));nocturneBattleActionSkillCall(0x0016aef0u);
/* 00256848: move a0,s1 */ set(4,cpu(17));
/* 0025684c: jal 0x00262430 */ set(31,0x00256854u);/* delay 00256850 */ set(5,cpu(18));body_00262430();
/* 00256854: lw v1,0x58(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00256858: beq v1,zero,0x002568c0 */ {int taken=(cpu(3)==cpu(0));/* delay 0025685c */ lw(7,ea(29,(int32_t)UINT32_C(0x00000040)));if(taken){goto L_002568c0;}}
/* 00256860: move a0,zero */ set(4,cpu(0));
/* 00256864: move a1,s1 */ set(5,cpu(17));
/* 00256868: jal 0x00261500 */ set(31,0x00256870u);/* delay 0025686c */ set(6,cpu(18));body_00261500();
/* 00256870: lw a0,0x68(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00256874: beq a0,zero,0x002568a0 */ {int taken=(cpu(4)==cpu(0));/* delay 00256878 */ set(2,sx(UINT32_C(0x00000106)));if(taken){goto L_002568a0;}}
/* 0025687c: bnel s6,v0,0x002568a4 */ {int taken=(cpu(22)!=cpu(2));if(taken){/* delay 00256880 */ set(6,sx((uint32_t)cpu(22)+UINT32_C(0x00000200)));goto L_002568a4;}}
/* 00256884: lui a2,0x306 */ set(6,sx(UINT32_C(0x03060000)));
/* 00256888: move a0,zero */ set(4,cpu(0));
/* 0025688c: move a1,s2 */ set(5,cpu(18));
/* 00256890: jal 0x00262cc0 */ set(31,0x00256898u);/* delay 00256894 */ set(6,cpu(6)|UINT32_C(0x00000001));nocturneBattleActionSkillCall(0x00262cc0u);
/* 00256898: b 0x002568e0 */ /* delay 0025689c */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_002568e0;
L_002568a0:;
/* 002568a0: addiu a2,s6,0x200 */ set(6,sx((uint32_t)cpu(22)+UINT32_C(0x00000200)));
L_002568a4:;
/* 002568a4: move a0,zero */ set(4,cpu(0));
/* 002568a8: sll a2,a2,0x10 */ set(6,sx((uint32_t)cpu(6)<<16));
/* 002568ac: jal 0x00262cc0 */ set(31,0x002568b4u);/* delay 002568b0 */ set(5,cpu(18));nocturneBattleActionSkillCall(0x00262cc0u);
/* 002568b4: b 0x002568e0 */ /* delay 002568b8 */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_002568e0;
L_002568c0:;
/* 002568c0: jal 0x0016b090 */ set(31,0x002568c8u);/* delay 002568c4 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));nocturneBattleActionSkillCall(0x0016b090u);
/* 002568c8: b 0x002568e0 */ /* delay 002568cc */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));goto L_002568e0;
L_002568d0:;
/* 002568d0: move a0,s1 */ set(4,cpu(17));
/* 002568d4: jal 0x00262430 */ set(31,0x002568dcu);/* delay 002568d8 */ set(5,cpu(18));body_00262430();
/* 002568dc: lw a2,0x28(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000028)));
L_002568e0:;
/* 002568e0: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002568e4: lh v0,0xa4(a2) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(6,(int32_t)UINT32_C(0x000000a4))));
/* 002568e8: bne v0,v1,0x00256920 */ {int taken=(cpu(2)!=cpu(3));/* delay 002568ec */ lw(2,ea(29,(int32_t)UINT32_C(0x0000004c)));if(taken){goto L_00256920;}}
/* 002568f0: sll a0,s1,0x4 */ set(4,sx((uint32_t)cpu(17)<<4));
/* 002568f4: li v0,0x64 */ set(2,sx(UINT32_C(0x00000064)));
/* 002568f8: subu a0,a0,s1 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(17)));
/* 002568fc: move a1,s2 */ set(5,cpu(18));
/* 00256900: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00256904: beql v0,zero,0x0025690c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00256908 */ nocturneCompilerArithmeticTrap(7u);goto L_0025690c;}}
L_0025690c:;
/* 0025690c: div a0,v0 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(2),1,0);
/* 00256910: mflo a0 */ set(4,nocturneEffectHostLo());
/* 00256914: jal 0x00261f90 */ set(31,0x0025691cu);/* delay 00256918 */ nocturneBattleActionSkillCall(0x00261f90u);
/* 0025691c: lw v0,0x4c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000004c)));
L_00256920:;
/* 00256920: blez v0,0x00256980 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00256924 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000050)));if(taken){goto L_00256980;}}
/* 00256928: lw v0,0x34(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000034)));
/* 0025692c: bnel v0,zero,0x002569a8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00256930 */ lw(6,ea(18,(int32_t)UINT32_C(0x00000020)));goto L_002569a8;}}
/* 00256934: lw a0,0x50(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00256938: move a1,s2 */ set(5,cpu(18));
/* 0025693c: lwc1 f12,0x14(s2) */ f[12]=word(ea(18,(int32_t)UINT32_C(0x00000014)));
/* 00256940: lui s0,0x54 */ set(16,sx(UINT32_C(0x00540000)));
/* 00256944: jal 0x002642e0 */ set(31,0x0025694cu);/* delay 00256948 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00003ee8)));body_002642e0();
/* 0025694c: move a1,s2 */ set(5,cpu(18));
/* 00256950: lw a0,0x50(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00256954: lw a2,0x18(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 00256958: jal 0x00264368 */ set(31,0x00256960u);/* delay 0025695c */ lw(7,ea(18,(int32_t)UINT32_C(0x00000028)));body_00264368();
/* 00256960: jal 0x002d1550 */ set(31,0x00256968u);/* delay 00256964 */ f[12]=word(ea(18,(int32_t)UINT32_C(0x00000014)));nocturneBattleActionSkillCall(0x002d1550u);
/* 00256968: move a1,v0 */ set(5,cpu(2));
/* 0025696c: jal 0x002d4748 */ set(31,0x00256974u);/* delay 00256970 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002d4748u);
/* 00256974: b 0x002569a8 */ /* delay 00256978 */ lw(6,ea(18,(int32_t)UINT32_C(0x00000020)));goto L_002569a8;
L_00256980:;
/* 00256980: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
/* 00256984: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 00256988: jal 0x002642e0 */ set(31,0x00256990u);/* delay 0025698c */ set(5,cpu(18));body_002642e0();
/* 00256990: move a1,s2 */ set(5,cpu(18));
/* 00256994: lw a0,0x50(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00256998: move a2,zero */ set(6,cpu(0));
/* 0025699c: jal 0x00264368 */ set(31,0x002569a4u);/* delay 002569a0 */ lw(7,ea(18,(int32_t)UINT32_C(0x00000028)));body_00264368();
/* 002569a4: lw a2,0x20(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000020)));
L_002569a8:;
/* 002569a8: blezl a2,0x002569c8 */ {int taken=((int64_t)cpu(6)<=0);if(taken){/* delay 002569ac */ lw(2,ea(18,(int32_t)UINT32_C(0x0000018c)));goto L_002569c8;}}
/* 002569b0: lw v1,0x50(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002569b4: move a1,s2 */ set(5,cpu(18));
/* 002569b8: lw a3,0x28(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002569bc: jal 0x00264368 */ set(31,0x002569c4u);/* delay 002569c0 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000014)));body_00264368();
/* 002569c4: lw v0,0x18c(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000018c)));
L_002569c8:;
/* 002569c8: blez v0,0x00256a44 */ {int taken=((int64_t)cpu(2)<=0);/* delay 002569cc */ restore(16,ea(29,(int32_t)UINT32_C(0x00000090)));if(taken){goto L_00256a44;}}
/* 002569d0: jal 0x001e0f50 */ set(31,0x002569d8u);/* delay 002569d4 */ set(4,sx(UINT32_C(0x00000c09)));nocturneBattleActionSkillCall(0x001e0f50u);
/* 002569d8: beq v0,zero,0x00256a44 */ {int taken=(cpu(2)==cpu(0));/* delay 002569dc */ restore(16,ea(29,(int32_t)UINT32_C(0x00000090)));if(taken){goto L_00256a44;}}
/* 002569e0: lw v1,0x0(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 002569e4: lw v0,0x60(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000060)));
/* 002569e8: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 002569ec: beql v0,zero,0x002569f8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002569f0 */ set(17,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000018))));goto L_002569f8;}}
/* 002569f4: lh s1,0x1a(v1) */ set(17,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x0000001a))));
L_002569f8:;
/* 002569f8: mtc1 s1,f3 */ f[3]=(uint32_t)cpu(17);
/* 002569fc: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 00256a00: lwc1 f1,0x14(s2) */ f[1]=word(ea(18,(int32_t)UINT32_C(0x00000014)));
/* 00256a04: lwc1 f0,0x74(v1) */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000074)));
/* 00256a08: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00256a0c: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00256a10: nop  */ 
/* 00256a14: nop  */ 
/* 00256a18: div.S f1,f1,f3 */ f[1]=EE_FPU_DIV_S(f[1],f[3]);
/* 00256a1c: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 00256a20: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 00256a24: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00256a28: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 00256a2c: bgtz v0,0x00256a44 */ {int taken=((int64_t)cpu(2)>0);/* delay 00256a30 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000090)));if(taken){goto L_00256a44;}}
/* 00256a34: lw a0,0x18c(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x0000018c)));
/* 00256a38: jal 0x00262e28 */ set(31,0x00256a40u);/* delay 00256a3c */ set(5,cpu(18));body_00262e28();
/* 00256a40: ld s0,0x90(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000090)));
L_00256a44:;
/* 00256a44: ld s1,0x98(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00256a48: ld s2,0xa0(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 00256a4c: ld s3,0xa8(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 00256a50: ld s4,0xb0(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 00256a54: ld s5,0xb8(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 00256a58: ld s6,0xc0(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 00256a5c: ld s7,0xc8(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 00256a60: ld s8,0xd0(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 00256a64: ld ra,0xd8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000d8)));
/* 00256a68: lwc1 f21,0xe8(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x000000e8)));
/* 00256a6c: lwc1 f20,0xe0(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x000000e0)));
/* 00256a70: jr ra */ {uint64_t target=cpu(31);/* delay 00256a74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000f0)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00255650(uint64_t a0){
set(4,a0);
body_00255650();
return;
}
static void body_002594b0(void){
nocturneEffectAxisNoteEntry(0x002594b0u);
uint64_t incoming=cpu(31);
/* 002594b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002594b4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002594b8: move s1,zero */ set(17,cpu(0));
/* 002594bc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002594c0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002594c4: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002594c8: lw a2,0x8(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002594cc: lw v0,0x0(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002594d0: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002594d4: beq v0,zero,0x0025950c */ {int taken=(cpu(2)==cpu(0));/* delay 002594d8 */ set(18,cpu(5));if(taken){goto L_0025950c;}}
/* 002594dc: move v1,a2 */ set(3,cpu(6));
/* 002594e0: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 002594e4: nop  */ 
L_002594e8:;
/* 002594e8: slti v0,s1,0xa */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 002594ec: beq v0,zero,0x0025950c */ {int taken=(cpu(2)==cpu(0));/* delay 002594f0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ec)));if(taken){goto L_0025950c;}}
/* 002594f4: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002594f8: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002594fc: nop  */ 
/* 00259500: nop  */ 
/* 00259504: bnel v0,zero,0x002594e8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00259508 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_002594e8;}}
L_0025950c:;
/* 0025950c: li v1,0xa */ set(3,sx(UINT32_C(0x0000000a)));
/* 00259510: beq s1,v1,0x00259584 */ {int taken=(cpu(17)==cpu(3));/* delay 00259514 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_00259584;}}
/* 00259518: sll s0,s1,0x4 */ set(16,sx((uint32_t)cpu(17)<<4));
/* 0025951c: move a0,s2 */ set(4,cpu(18));
/* 00259520: subu s0,s0,s1 */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(17)));
/* 00259524: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 00259528: subu s0,s0,s1 */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(17)));
/* 0025952c: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 00259530: addu s0,a2,s0 */ set(16,sx((uint32_t)cpu(6)+(uint32_t)cpu(16)));
/* 00259534: jal 0x00244ef8 */ set(31,0x0025953cu);/* delay 00259538 */ set(5,cpu(16));nocturneBattleActionSkillCall(0x00244ef8u);
/* 0025953c: sll v1,s2,0x4 */ set(3,sx((uint32_t)cpu(18)<<4));
/* 00259540: subu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(18)));
/* 00259544: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00259548: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0025954c: move v0,s1 */ set(2,cpu(17));
/* 00259550: lui at,0x35 */ set(1,sx(UINT32_C(0x00350000)));
/* 00259554: addiu at,at,-0x6840 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffff97c0)));
/* 00259558: addu v1,at,v1 */ set(3,sx((uint32_t)cpu(1)+(uint32_t)cpu(3)));
/* 0025955c: ori a0,a0,0x2 */ set(4,cpu(4)|UINT32_C(0x00000002));
/* 00259560: lhu a1,0x8(v1) */ set(5,half(ea(3,(int32_t)UINT32_C(0x00000008))));
/* 00259564: sw a0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 00259568: sh a1,0x8(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(5));
/* 0025956c: lhu a0,0x6(v1) */ set(4,half(ea(3,(int32_t)UINT32_C(0x00000006))));
/* 00259570: sh a0,0x6(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(4));
/* 00259574: lhu a1,0xc(v1) */ set(5,half(ea(3,(int32_t)UINT32_C(0x0000000c))));
/* 00259578: sh a1,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(5));
/* 0025957c: lhu a0,0xa(v1) */ set(4,half(ea(3,(int32_t)UINT32_C(0x0000000a))));
/* 00259580: sh a0,0xa(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(4));
L_00259584:;
/* 00259584: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259588: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025958c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00259590: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00259594: jr ra */ {uint64_t target=cpu(31);/* delay 00259598 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_002594B0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002594b0();
return cpu(2);
}
static void body_002595a0(void){
nocturneEffectAxisNoteEntry(0x002595a0u);
uint64_t incoming=cpu(31);
/* 002595a0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002595a4: lw t1,-0x5750(gp) */ lw(9,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 002595a8: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002595ac: move a1,zero */ set(5,cpu(0));
/* 002595b0: move a3,zero */ set(7,cpu(0));
/* 002595b4: li t3,0x800 */ set(11,sx(UINT32_C(0x00000800)));
/* 002595b8: addiu t2,t1,0x4 */ set(10,sx((uint32_t)cpu(9)+UINT32_C(0x00000004)));
/* 002595bc: li a2,0xa50 */ set(6,sx(UINT32_C(0x00000a50)));
/* 002595c0: move t0,sp */ set(8,cpu(29));
/* 002595c4: nop  */ 
L_002595c8:;
/* 002595c8: addu v0,t2,a2 */ set(2,sx((uint32_t)cpu(10)+(uint32_t)cpu(6)));
/* 002595cc: lw v0,0x0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002595d0: andi v1,v0,0x1 */ set(3,cpu(2)&UINT32_C(0x00000001));
/* 002595d4: beq v1,zero,0x0025961c */ {int taken=(cpu(3)==cpu(0));/* delay 002595d8 */ set(4,cpu(2)&UINT32_C(0x00000002));if(taken){goto L_0025961c;}}
/* 002595dc: bnel a0,zero,0x00259620 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 002595e0 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));goto L_00259620;}}
/* 002595e4: andi v0,v0,0x10 */ set(2,cpu(2)&UINT32_C(0x00000010));
/* 002595e8: bnel v0,zero,0x00259620 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002595ec */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));goto L_00259620;}}
/* 002595f0: addu v1,t1,a2 */ set(3,sx((uint32_t)cpu(9)+(uint32_t)cpu(6)));
/* 002595f4: lhu v0,0x12(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000012))));
/* 002595f8: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 002595fc: beql v0,t3,0x00259620 */ {int taken=(cpu(2)==cpu(11));if(taken){/* delay 00259600 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));goto L_00259620;}}
/* 00259604: lhu v0,0xa(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000a))));
/* 00259608: beql v0,zero,0x00259620 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025960c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));goto L_00259620;}}
/* 00259610: sw a3,0x0(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));
/* 00259614: addiu t0,t0,0x4 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));
/* 00259618: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
L_0025961c:;
/* 0025961c: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
L_00259620:;
/* 00259620: slti v0,a3,0x10 */ set(2,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00259624: bne v0,zero,0x002595c8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00259628 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x000000ec)));if(taken){goto L_002595c8;}}
/* 0025962c: beq a1,zero,0x00259648 */ {int taken=(cpu(5)==cpu(0));/* delay 00259630 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_00259648;}}
/* 00259634: jal 0x002c0c60 */ set(31,0x0025963cu);/* delay 00259638 */ set(4,cpu(0));nocturneBattleActionSkillCall(0x002c0c60u);
/* 0025963c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00259640: addu v1,sp,v0 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(2)));
/* 00259644: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
L_00259648:;
/* 00259648: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0025964c: jr ra */ {uint64_t target=cpu(31);/* delay 00259650 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_002595A0(void){

body_002595a0();
return cpu(2);
}
static void body_00261500(void){
nocturneEffectAxisNoteEntry(0x00261500u);
uint64_t incoming=cpu(31);
/* 00261500: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00261504: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261508: move s0,a0 */ set(16,cpu(4));
/* 0026150c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261510: move s1,a1 */ set(17,cpu(5));
/* 00261514: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261518: move s2,a2 */ set(18,cpu(6));
/* 0026151c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261520: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261524: jal 0x0025e8e0 */ set(31,0x0026152cu);/* delay 00261528 */ set(19,cpu(7));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 0026152c: move a0,v0 */ set(4,cpu(2));
/* 00261530: move a1,s0 */ set(5,cpu(16));
/* 00261534: move a2,s1 */ set(6,cpu(17));
/* 00261538: jal 0x0025ea48 */ set(31,0x00261540u);/* delay 0026153c */ set(7,cpu(18));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00261540: move v1,v0 */ set(3,cpu(2));
/* 00261544: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261548: sw s3,0x24(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(19));
/* 0026154c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261550: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261554: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261558: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0026155c: sb zero,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(0));
/* 00261560: jr ra */ {uint64_t target=cpu(31);/* delay 00261564 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00261500(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_00261500();
return cpu(2);
}
static void body_00261638(void){
nocturneEffectAxisNoteEntry(0x00261638u);
uint64_t incoming=cpu(31);
/* 00261638: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 0026163c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261640: move s0,a0 */ set(16,cpu(4));
/* 00261644: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261648: move s1,a1 */ set(17,cpu(5));
/* 0026164c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261650: move s2,a2 */ set(18,cpu(6));
/* 00261654: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261658: move s3,a3 */ set(19,cpu(7));
/* 0026165c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261660: move s4,t1 */ set(20,cpu(9));
/* 00261664: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00261668: move s5,t2 */ set(21,cpu(10));
/* 0026166c: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00261670: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00261674: jal 0x0025e8e0 */ set(31,0x0026167cu);/* delay 00261678 */ set(22,cpu(8));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 0026167c: move a0,v0 */ set(4,cpu(2));
/* 00261680: move a1,s0 */ set(5,cpu(16));
/* 00261684: move a2,s1 */ set(6,cpu(17));
/* 00261688: jal 0x0025ea48 */ set(31,0x00261690u);/* delay 0026168c */ set(7,cpu(18));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00261690: bne s1,zero,0x002616a4 */ {int taken=(cpu(17)!=cpu(0));/* delay 00261694 */ set(4,cpu(2));if(taken){goto L_002616a4;}}
/* 00261698: lbu v1,0x5(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000005))));
/* 0026169c: ori v1,v1,0x1 */ set(3,cpu(3)|UINT32_C(0x00000001));
/* 002616a0: sb v1,0x5(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(3));
L_002616a4:;
/* 002616a4: sw s4,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(20));
/* 002616a8: li v1,0x15 */ set(3,sx(UINT32_C(0x00000015)));
/* 002616ac: sw s3,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(19));
/* 002616b0: sh s6,0x2c(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(22));
/* 002616b4: sh s5,0x2e(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(21));
/* 002616b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002616bc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002616c0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002616c4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002616c8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002616cc: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002616d0: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002616d4: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002616d8: sb v1,0x4(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 002616dc: sw zero,0x24(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 002616e0: jr ra */ {uint64_t target=cpu(31);/* delay 002616e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00261638(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);set(9,t1);set(10,t2);
body_00261638();
return cpu(2);
}
static void body_00261e80(void){
nocturneEffectAxisNoteEntry(0x00261e80u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 00261e80: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00261e84: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261e88: move s0,a0 */ set(16,cpu(4));
/* 00261e8c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261e90: move s1,a1 */ set(17,cpu(5));
/* 00261e94: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261e98: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261e9c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261ea0: jal 0x0025e8e0 */ set(31,0x00261ea8u);/* delay 00261ea4 */ set(19,cpu(6));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00261ea8: move a0,v0 */ set(4,cpu(2));
/* 00261eac: move a1,s0 */ set(5,cpu(16));
/* 00261eb0: move a2,zero */ set(6,cpu(0));
/* 00261eb4: jal 0x0025ea48 */ set(31,0x00261ebcu);/* delay 00261eb8 */ set(7,cpu(17));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00261ebc: lwc1 f1,0x50(s3) */ f[1]=word(ea(19,(int32_t)UINT32_C(0x00000050)));
/* 00261ec0: lwc1 f0,-0x5c60(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa3a0)));
/* 00261ec4: lui a2,0x1 */ set(6,sx(UINT32_C(0x00010000)));
/* 00261ec8: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00261ecc: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00261ed0: move s2,v0 */ set(18,cpu(2));
/* 00261ed4: mul.S f1,f1,f0 */ f[1]=EE_FPU_MUL_S(f[1],f[0]);
/* 00261ed8: move a0,s0 */ set(4,cpu(16));
/* 00261edc: move a1,s1 */ set(5,cpu(17));
/* 00261ee0: c.lt.S f2,f1 */ condition=EE_FPU_COMPARE_S(f[2],f[1],1)!=0;
/* 00261ee4: bc1f 0x00261ef0 */ {int taken=(condition==0);/* delay 00261ee8 */ set(6,cpu(6)|UINT32_C(0x00000010));if(taken){goto L_00261ef0;}}
/* 00261eec: mov.S f1,f2 */ f[1]=f[2];
L_00261ef0:;
/* 00261ef0: lwc1 f0,-0x5c5c(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa3a4)));
/* 00261ef4: li v0,0xd */ set(2,sx(UINT32_C(0x0000000d)));
/* 00261ef8: sw s3,0x14(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 00261efc: swc1 f1,0x28(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000028)),f[1]);
/* 00261f00: swc1 f0,0x2c(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000002c)),f[0]);
/* 00261f04: jal 0x00262cc0 */ set(31,0x00261f0cu);/* delay 00261f08 */ sb(ea(18,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(2));nocturneBattleActionSkillCall(0x00262cc0u);
/* 00261f0c: move v0,s2 */ set(2,cpu(18));
/* 00261f10: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261f14: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261f18: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261f1c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261f20: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261f24: jr ra */ {uint64_t target=cpu(31);/* delay 00261f28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00261E80(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00261e80();
return cpu(2);
}
static void body_00262340(void){
nocturneEffectAxisNoteEntry(0x00262340u);
uint64_t incoming=cpu(31);
/* 00262340: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262344: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262348: move s0,a0 */ set(16,cpu(4));
/* 0026234c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262350: move s1,a1 */ set(17,cpu(5));
/* 00262354: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262358: move s2,t0 */ set(18,cpu(8));
/* 0026235c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262360: move s3,a2 */ set(19,cpu(6));
/* 00262364: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262368: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026236c: jal 0x0025e8e0 */ set(31,0x00262374u);/* delay 00262370 */ set(20,cpu(7));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00262374: move a0,v0 */ set(4,cpu(2));
/* 00262378: move a1,s0 */ set(5,cpu(16));
/* 0026237c: move a3,s1 */ set(7,cpu(17));
/* 00262380: jal 0x0025ea48 */ set(31,0x00262388u);/* delay 00262384 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00262388: li a0,0xc */ set(4,sx(UINT32_C(0x0000000c)));
/* 0026238c: move v1,v0 */ set(3,cpu(2));
/* 00262390: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262394: sh s2,0x2c(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(18));
/* 00262398: sh s3,0x28(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000028)),(uint16_t)cpu(19));
/* 0026239c: sh s4,0x2a(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000002a)),(uint16_t)cpu(20));
/* 002623a0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002623a4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002623a8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002623ac: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002623b0: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002623b4: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002623b8: jr ra */ {uint64_t target=cpu(31);/* delay 002623bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00262340(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);
body_00262340();
return cpu(2);
}
static void body_00262430(void){
nocturneEffectAxisNoteEntry(0x00262430u);
uint64_t incoming=cpu(31);
/* 00262430: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262434: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262438: move s0,a0 */ set(16,cpu(4));
/* 0026243c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262440: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262444: jal 0x0025e8e0 */ set(31,0x0026244cu);/* delay 00262448 */ set(17,cpu(5));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 0026244c: move a0,v0 */ set(4,cpu(2));
/* 00262450: move a1,s0 */ set(5,cpu(16));
/* 00262454: move a3,s1 */ set(7,cpu(17));
/* 00262458: jal 0x0025ea48 */ set(31,0x00262460u);/* delay 0026245c */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00262460: li v1,0xe */ set(3,sx(UINT32_C(0x0000000e)));
/* 00262464: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262468: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026246c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262470: sb v1,0x4(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 00262474: jr ra */ {uint64_t target=cpu(31);/* delay 00262478 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00262430(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00262430();
return cpu(2);
}
static void body_00262a68(void){
nocturneEffectAxisNoteEntry(0x00262a68u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00262a68: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262a6c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262a70: move s0,a0 */ set(16,cpu(4));
/* 00262a74: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262a78: move s1,a1 */ set(17,cpu(5));
/* 00262a7c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262a80: swc1 f20,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);
/* 00262a84: jal 0x0025e8e0 */ set(31,0x00262a8cu);/* delay 00262a88 */ f[20]=f[12];nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00262a8c: move a1,s0 */ set(5,cpu(16));
/* 00262a90: move a3,s1 */ set(7,cpu(17));
/* 00262a94: move a0,v0 */ set(4,cpu(2));
/* 00262a98: jal 0x0025ea48 */ set(31,0x00262aa0u);/* delay 00262a9c */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00262aa0: li a0,0x12 */ set(4,sx(UINT32_C(0x00000012)));
/* 00262aa4: move v1,v0 */ set(3,cpu(2));
/* 00262aa8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262aac: swc1 f20,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 00262ab0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262ab4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262ab8: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262abc: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262ac0: jr ra */ {uint64_t target=cpu(31);/* delay 00262ac4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00262A68(uint64_t a0, uint64_t a1, float f12){
set(4,a0);set(5,a1);
nocturneEffectHostFpr()[12]=bits(f12);
body_00262a68();
return cpu(2);
}
static void body_00262ac8(void){
nocturneEffectAxisNoteEntry(0x00262ac8u);
uint64_t incoming=cpu(31);
/* 00262ac8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262acc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262ad0: move s0,a0 */ set(16,cpu(4));
/* 00262ad4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262ad8: move s1,a1 */ set(17,cpu(5));
/* 00262adc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262ae0: move s2,a3 */ set(18,cpu(7));
/* 00262ae4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262ae8: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262aec: jal 0x0025e8e0 */ set(31,0x00262af4u);/* delay 00262af0 */ set(19,cpu(6));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00262af4: move a0,v0 */ set(4,cpu(2));
/* 00262af8: move a1,s0 */ set(5,cpu(16));
/* 00262afc: move a3,s1 */ set(7,cpu(17));
/* 00262b00: jal 0x0025ea48 */ set(31,0x00262b08u);/* delay 00262b04 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00262b08: li a0,0x1f */ set(4,sx(UINT32_C(0x0000001f)));
/* 00262b0c: move v1,v0 */ set(3,cpu(2));
/* 00262b10: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262b14: sh s2,0x2a(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000002a)),(uint16_t)cpu(18));
/* 00262b18: sh s3,0x28(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000028)),(uint16_t)cpu(19));
/* 00262b1c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262b20: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262b24: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262b28: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262b2c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262b30: jr ra */ {uint64_t target=cpu(31);/* delay 00262b34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00262AC8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_00262ac8();
return cpu(2);
}
static void body_00262e28(void){
nocturneEffectAxisNoteEntry(0x00262e28u);
uint64_t incoming=cpu(31);
/* 00262e28: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262e2c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262e30: move s0,a0 */ set(16,cpu(4));
/* 00262e34: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262e38: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262e3c: jal 0x0025e8e0 */ set(31,0x00262e44u);/* delay 00262e40 */ set(17,cpu(5));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00262e44: move a0,v0 */ set(4,cpu(2));
/* 00262e48: move a1,s0 */ set(5,cpu(16));
/* 00262e4c: move a3,s1 */ set(7,cpu(17));
/* 00262e50: jal 0x0025ea48 */ set(31,0x00262e58u);/* delay 00262e54 */ set(6,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00262e58: li v1,0x1e */ set(3,sx(UINT32_C(0x0000001e)));
/* 00262e5c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262e60: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262e64: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262e68: sb v1,0x4(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 00262e6c: jr ra */ {uint64_t target=cpu(31);/* delay 00262e70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00262E28(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_00262e28();
return cpu(2);
}
static void body_00262e78(void){
nocturneEffectAxisNoteEntry(0x00262e78u);
uint64_t incoming=cpu(31);
/* 00262e78: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262e7c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262e80: move s0,a0 */ set(16,cpu(4));
/* 00262e84: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262e88: move s1,a1 */ set(17,cpu(5));
/* 00262e8c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262e90: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262e94: jal 0x0025e8e0 */ set(31,0x00262e9cu);/* delay 00262e98 */ set(18,cpu(6));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00262e9c: move a0,v0 */ set(4,cpu(2));
/* 00262ea0: move a1,s0 */ set(5,cpu(16));
/* 00262ea4: move a3,s1 */ set(7,cpu(17));
/* 00262ea8: jal 0x0025ea48 */ set(31,0x00262eb0u);/* delay 00262eac */ set(6,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00262eb0: li a0,0x22 */ set(4,sx(UINT32_C(0x00000022)));
/* 00262eb4: move v1,v0 */ set(3,cpu(2));
/* 00262eb8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262ebc: sw s2,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 00262ec0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262ec4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262ec8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262ecc: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262ed0: jr ra */ {uint64_t target=cpu(31);/* delay 00262ed4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00262E78(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00262e78();
return cpu(2);
}
static void body_00262ed8(void){
nocturneEffectAxisNoteEntry(0x00262ed8u);
uint64_t incoming=cpu(31);
/* 00262ed8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262edc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262ee0: move s0,a0 */ set(16,cpu(4));
/* 00262ee4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262ee8: move s1,a1 */ set(17,cpu(5));
/* 00262eec: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262ef0: move s2,t0 */ set(18,cpu(8));
/* 00262ef4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262ef8: move s3,a2 */ set(19,cpu(6));
/* 00262efc: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262f00: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262f04: jal 0x0025e8e0 */ set(31,0x00262f0cu);/* delay 00262f08 */ set(20,cpu(7));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00262f0c: move a0,v0 */ set(4,cpu(2));
/* 00262f10: move a1,s0 */ set(5,cpu(16));
/* 00262f14: move a3,s1 */ set(7,cpu(17));
/* 00262f18: jal 0x0025ea48 */ set(31,0x00262f20u);/* delay 00262f1c */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00262f20: li a0,0x23 */ set(4,sx(UINT32_C(0x00000023)));
/* 00262f24: move v1,v0 */ set(3,cpu(2));
/* 00262f28: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262f2c: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00262f30: sh s3,0x28(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000028)),(uint16_t)cpu(19));
/* 00262f34: sh s4,0x2a(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000002a)),(uint16_t)cpu(20));
/* 00262f38: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262f3c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262f40: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262f44: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262f48: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262f4c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262f50: jr ra */ {uint64_t target=cpu(31);/* delay 00262f54 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00262ED8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);
body_00262ed8();
return cpu(2);
}
static void body_00263028(void){
nocturneEffectAxisNoteEntry(0x00263028u);
uint64_t incoming=cpu(31);
/* 00263028: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0026302c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263030: move s0,a0 */ set(16,cpu(4));
/* 00263034: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263038: move s1,a1 */ set(17,cpu(5));
/* 0026303c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263040: move s2,t0 */ set(18,cpu(8));
/* 00263044: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263048: move s3,a2 */ set(19,cpu(6));
/* 0026304c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263050: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00263054: jal 0x0025e8e0 */ set(31,0x0026305cu);/* delay 00263058 */ set(20,cpu(7));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 0026305c: move a0,v0 */ set(4,cpu(2));
/* 00263060: move a1,s0 */ set(5,cpu(16));
/* 00263064: move a3,s1 */ set(7,cpu(17));
/* 00263068: jal 0x0025ea48 */ set(31,0x00263070u);/* delay 0026306c */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00263070: li a0,0x2c */ set(4,sx(UINT32_C(0x0000002c)));
/* 00263074: move v1,v0 */ set(3,cpu(2));
/* 00263078: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026307c: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00263080: sw s3,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 00263084: sw s4,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(20));
/* 00263088: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026308c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263090: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263094: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263098: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026309c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002630a0: jr ra */ {uint64_t target=cpu(31);/* delay 002630a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00263028(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);
body_00263028();
return cpu(2);
}
static void body_00263250(void){
nocturneEffectAxisNoteEntry(0x00263250u);
uint64_t incoming=cpu(31);
/* 00263250: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00263254: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263258: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026325c: move s1,a0 */ set(17,cpu(4));
/* 00263260: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263264: move s2,a1 */ set(18,cpu(5));
/* 00263268: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026326c: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00263270: jal 0x0025e8e0 */ set(31,0x00263278u);/* delay 00263274 */ set(19,cpu(6));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00263278: jal 0x00198860 */ set(31,0x00263280u);/* delay 0026327c */ set(16,cpu(2));nocturneBattleActionSkillCall(0x00198860u);
/* 00263280: move a2,v0 */ set(6,cpu(2));
/* 00263284: move a1,s1 */ set(5,cpu(17));
/* 00263288: move a3,s2 */ set(7,cpu(18));
/* 0026328c: jal 0x0025ea48 */ set(31,0x00263294u);/* delay 00263290 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00263294: move a0,sp */ set(4,cpu(29));
/* 00263298: move s0,v0 */ set(16,cpu(2));
/* 0026329c: jal 0x00198200 */ set(31,0x002632a4u);/* delay 002632a0 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(19));nocturneBattleActionSkillCall(0x00198200u);
/* 002632a4: li v1,0x29 */ set(3,sx(UINT32_C(0x00000029)));
/* 002632a8: sw v0,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));
/* 002632ac: sb v1,0x4(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 002632b0: move v0,s0 */ set(2,cpu(16));
/* 002632b4: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002632b8: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002632bc: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002632c0: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002632c4: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002632c8: jr ra */ {uint64_t target=cpu(31);/* delay 002632cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00263250(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00263250();
return cpu(2);
}
static void body_002632d0(void){
nocturneEffectAxisNoteEntry(0x002632d0u);
uint64_t incoming=cpu(31);
/* 002632d0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002632d4: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002632d8: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002632dc: move s1,a0 */ set(17,cpu(4));
/* 002632e0: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002632e4: move s2,a1 */ set(18,cpu(5));
/* 002632e8: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002632ec: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002632f0: jal 0x0025e8e0 */ set(31,0x002632f8u);/* delay 002632f4 */ set(19,cpu(6));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 002632f8: jal 0x00198ff8 */ set(31,0x00263300u);/* delay 002632fc */ set(16,cpu(2));nocturneBattleActionSkillCall(0x00198ff8u);
/* 00263300: move a2,v0 */ set(6,cpu(2));
/* 00263304: move a1,s1 */ set(5,cpu(17));
/* 00263308: move a3,s2 */ set(7,cpu(18));
/* 0026330c: jal 0x0025ea48 */ set(31,0x00263314u);/* delay 00263310 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00263314: move a0,sp */ set(4,cpu(29));
/* 00263318: move s0,v0 */ set(16,cpu(2));
/* 0026331c: jal 0x00198868 */ set(31,0x00263324u);/* delay 00263320 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(19));nocturneBattleActionSkillCall(0x00198868u);
/* 00263324: li v1,0x2a */ set(3,sx(UINT32_C(0x0000002a)));
/* 00263328: sw v0,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));
/* 0026332c: sb v1,0x4(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 00263330: move v0,s0 */ set(2,cpu(16));
/* 00263334: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263338: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026333c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263340: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00263344: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00263348: jr ra */ {uint64_t target=cpu(31);/* delay 0026334c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_002632D0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_002632d0();
return cpu(2);
}
static void body_00263548(void){
nocturneEffectAxisNoteEntry(0x00263548u);
uint64_t incoming=cpu(31);
/* 00263548: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0026354c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263550: move s0,a0 */ set(16,cpu(4));
/* 00263554: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263558: move s1,a1 */ set(17,cpu(5));
/* 0026355c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263560: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263564: jal 0x0025e8e0 */ set(31,0x0026356cu);/* delay 00263568 */ set(18,cpu(6));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 0026356c: move a0,v0 */ set(4,cpu(2));
/* 00263570: move a1,s0 */ set(5,cpu(16));
/* 00263574: move a3,s1 */ set(7,cpu(17));
/* 00263578: jal 0x0025ea48 */ set(31,0x00263580u);/* delay 0026357c */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00263580: li a0,0x33 */ set(4,sx(UINT32_C(0x00000033)));
/* 00263584: move v1,v0 */ set(3,cpu(2));
/* 00263588: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026358c: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00263590: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263594: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263598: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026359c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002635a0: jr ra */ {uint64_t target=cpu(31);/* delay 002635a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00263548(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00263548();
return cpu(2);
}
static void body_002636c8(void){
nocturneEffectAxisNoteEntry(0x002636c8u);
uint64_t incoming=cpu(31);
/* 002636c8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002636cc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002636d0: move s1,t0 */ set(17,cpu(8));
/* 002636d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002636d8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002636dc: move s2,a2 */ set(18,cpu(6));
/* 002636e0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002636e4: move s3,a3 */ set(19,cpu(7));
/* 002636e8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002636ec: move s4,a0 */ set(20,cpu(4));
/* 002636f0: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002636f4: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002636f8: jal 0x002469a0 */ set(31,0x00263700u);/* delay 002636fc */ set(21,cpu(5));nocturneBattleActionSkillCall(0x002469a0u);
/* 00263700: sll v1,s1,0x4 */ set(3,sx((uint32_t)cpu(17)<<4));
/* 00263704: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00263708: subu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));
/* 0026370c: move a2,s2 */ set(6,cpu(18));
/* 00263710: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 00263714: move a3,s3 */ set(7,cpu(19));
/* 00263718: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 0026371c: move t0,s1 */ set(8,cpu(17));
/* 00263720: move a0,s4 */ set(4,cpu(20));
/* 00263724: jal 0x00262340 */ set(31,0x0026372cu);/* delay 00263728 */ set(5,cpu(21));body_00262340();
/* 0026372c: addiu a0,s4,0x1 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
/* 00263730: move a1,s5 */ set(5,cpu(21));
/* 00263734: move a2,s0 */ set(6,cpu(16));
/* 00263738: move a3,zero */ set(7,cpu(0));
/* 0026373c: li t0,0xf */ set(8,sx(UINT32_C(0x0000000f)));
/* 00263740: li t1,0xf */ set(9,sx(UINT32_C(0x0000000f)));
/* 00263744: jal 0x00263810 */ set(31,0x0026374cu);/* delay 00263748 */ set(10,sx(UINT32_C(0x00000014)));nocturneBattleActionSkillCall(0x00263810u);
/* 0026374c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00263750: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263754: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263758: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026375c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263760: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263764: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00263768: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0026376c: jr ra */ {uint64_t target=cpu(31);/* delay 00263770 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_002636C8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);
body_002636c8();
return cpu(2);
}
static void body_00263778(void){
nocturneEffectAxisNoteEntry(0x00263778u);
uint64_t incoming=cpu(31);
/* 00263778: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0026377c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263780: move s0,a2 */ set(16,cpu(6));
/* 00263784: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263788: move s1,a0 */ set(17,cpu(4));
/* 0026378c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263790: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263794: jal 0x002469a0 */ set(31,0x0026379cu);/* delay 00263798 */ set(18,cpu(5));nocturneBattleActionSkillCall(0x002469a0u);
/* 0026379c: lh a3,0x2(s0) */ set(7,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000002))));
/* 002637a0: move a0,s1 */ set(4,cpu(17));
/* 002637a4: lhu v1,0x0(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002637a8: move a1,s2 */ set(5,cpu(18));
/* 002637ac: sll a2,a3,0x4 */ set(6,sx((uint32_t)cpu(7)<<4));
/* 002637b0: lw t0,0x0(v0) */ lw(8,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002637b4: ori v1,v1,0x20 */ set(3,cpu(3)|UINT32_C(0x00000020));
/* 002637b8: subu a2,a2,a3 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(7)));
/* 002637bc: sh v1,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002637c0: sll a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)<<4));
/* 002637c4: addu a2,t0,a2 */ set(6,sx((uint32_t)cpu(8)+(uint32_t)cpu(6)));
/* 002637c8: li t0,0x6 */ set(8,sx(UINT32_C(0x00000006)));
/* 002637cc: li t1,0x6 */ set(9,sx(UINT32_C(0x00000006)));
/* 002637d0: li t2,0x6 */ set(10,sx(UINT32_C(0x00000006)));
/* 002637d4: jal 0x002638a0 */ set(31,0x002637dcu);/* delay 002637d8 */ set(7,cpu(0));nocturneBattleActionSkillCall(0x002638a0u);
/* 002637dc: addiu a0,s1,0xd */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x0000000d)));
/* 002637e0: move a1,s2 */ set(5,cpu(18));
/* 002637e4: move a2,s0 */ set(6,cpu(16));
/* 002637e8: jal 0x002622d0 */ set(31,0x002637f0u);/* delay 002637ec */ set(7,cpu(0));nocturneBattleActionSkillCall(0x002622d0u);
/* 002637f0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002637f4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002637f8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002637fc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263800: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263804: jr ra */ {uint64_t target=cpu(31);/* delay 00263808 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00263778(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00263778();
return cpu(2);
}
static void body_002642e0(void){
nocturneEffectAxisNoteEntry(0x002642e0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002642e0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002642e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002642e8: move s0,a0 */ set(16,cpu(4));
/* 002642ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002642f0: move s1,a1 */ set(17,cpu(5));
/* 002642f4: swc1 f20,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);
/* 002642f8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002642fc: jal 0x002469a0 */ set(31,0x00264304u);/* delay 00264300 */ f[20]=f[12];nocturneBattleActionSkillCall(0x002469a0u);
/* 00264304: move v1,v0 */ set(3,cpu(2));
/* 00264308: move a0,s0 */ set(4,cpu(16));
/* 0026430c: lw v0,0x60(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000060)));
/* 00264310: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 00264314: beq v0,zero,0x00264328 */ {int taken=(cpu(2)==cpu(0));/* delay 00264318 */ set(5,cpu(17));if(taken){goto L_00264328;}}
/* 0026431c: b 0x0026432c */ /* delay 00264320 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x0000001a))));goto L_0026432c;
L_00264328:;
/* 00264328: lh v0,0x18(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000018))));
L_0026432c:;
/* 0026432c: mtc1 v0,f12 */ f[12]=(uint32_t)cpu(2);
/* 00264330: cvt.s.W f12,f12 */ f[12]=EE_FPU_CVT_S_W(f[12]);
/* 00264334: nop  */ 
/* 00264338: nop  */ 
/* 0026433c: div.S f12,f20,f12 */ f[12]=EE_FPU_DIV_S(f[20],f[12]);
/* 00264340: jal 0x00262a68 */ set(31,0x00264348u);/* delay 00264344 */ body_00262a68();
/* 00264348: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0026434c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00264350: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00264354: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00264358: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026435c: jr ra */ {uint64_t target=cpu(31);/* delay 00264360 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_002642E0(uint64_t a0, uint64_t a1, float f12){
set(4,a0);set(5,a1);
nocturneEffectHostFpr()[12]=bits(f12);
body_002642e0();
return cpu(2);
}
static void body_00264368(void){
nocturneEffectAxisNoteEntry(0x00264368u);
uint64_t incoming=cpu(31);
/* 00264368: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0026436c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00264370: move s0,a2 */ set(16,cpu(6));
/* 00264374: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00264378: move s1,a0 */ set(17,cpu(4));
/* 0026437c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00264380: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00264384: jal 0x002469a0 */ set(31,0x0026438cu);/* delay 00264388 */ set(18,cpu(5));nocturneBattleActionSkillCall(0x002469a0u);
/* 0026438c: lh t1,0x7a(v0) */ set(9,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x0000007a))));
/* 00264390: move t4,zero */ set(12,cpu(0));
/* 00264394: lhu t8,0x78(v0) */ set(24,half(ea(2,(int32_t)UINT32_C(0x00000078))));
/* 00264398: move t3,zero */ set(11,cpu(0));
/* 0026439c: lh t0,0x78(v0) */ set(8,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000078))));
/* 002643a0: move a2,zero */ set(6,cpu(0));
/* 002643a4: lhu t7,0x7a(v0) */ set(15,half(ea(2,(int32_t)UINT32_C(0x0000007a))));
/* 002643a8: move a3,zero */ set(7,cpu(0));
/* 002643ac: move t5,zero */ set(13,cpu(0));
/* 002643b0: sltiu t6,s0,0x12 */ set(14,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000012));
/* 002643b4: sltiu a1,t0,0x1 */ set(5,cpu(8)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_002643b8:;
/* 002643b8: beq t6,zero,0x00264468 */ {int taken=(cpu(14)==cpu(0));/* delay 002643bc */ set(4,(int64_t)cpu(8)<(int64_t)cpu(9));if(taken){goto L_00264468;}}
/* 002643c0: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002643c4: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002643c8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002643cc: lw v1,0x4940(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004940)));
/* 002643d0: jr v1 */ {uint64_t target=cpu(3);/* delay 002643d4 */ switch((uint32_t)target){case 0x002643d8u:goto L_002643d8;case 0x002643e8u:goto L_002643e8;case 0x002643f8u:goto L_002643f8;case 0x00264408u:goto L_00264408;case 0x00264440u:goto L_00264440;case 0x00264450u:goto L_00264450;case 0x00264458u:goto L_00264458;case 0x00264460u:goto L_00264460;default:abort();}}
L_002643d8:;
/* 002643d8: bne a0,zero,0x00264468 */ {int taken=(cpu(4)!=cpu(0));/* delay 002643dc */ set(11,sx(UINT32_C(0xffffffff)));if(taken){goto L_00264468;}}
/* 002643e0: b 0x00264468 */ /* delay 002643e4 */ set(12,sx(UINT32_C(0xffffffff)));goto L_00264468;
L_002643e8:;
/* 002643e8: beql a0,zero,0x00264468 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 002643ec */ set(12,sx(UINT32_C(0xffffffff)));goto L_00264468;}}
/* 002643f0: b 0x00264468 */ /* delay 002643f4 */ set(11,sx(UINT32_C(0xffffffff)));goto L_00264468;
L_002643f8:;
/* 002643f8: beql a1,zero,0x00264468 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 002643fc */ set(12,sx(UINT32_C(0xffffffff)));goto L_00264468;}}
/* 00264400: b 0x00264468 */ /* delay 00264404 */ set(11,sx(UINT32_C(0xffffffff)));goto L_00264468;
L_00264408:;
/* 00264408: beq a0,zero,0x00264430 */ {int taken=(cpu(4)==cpu(0));/* delay 0026440c */ set(2,sx((uint32_t)cpu(9)+UINT32_C(0xfffffffe)));if(taken){goto L_00264430;}}
/* 00264410: slt v0,v0,t0 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(8));
/* 00264414: beq v0,zero,0x00264468 */ {int taken=(cpu(2)==cpu(0));/* delay 00264418 */ set(11,sx(UINT32_C(0xfffffffe)));if(taken){goto L_00264468;}}
/* 0026441c: subu v0,t0,t1 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(9)));
/* 00264420: addiu v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 00264424: b 0x00264468 */ /* delay 00264428 */ set(12,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));goto L_00264468;
L_00264430:;
/* 00264430: li t3,-0x2 */ set(11,sx(UINT32_C(0xfffffffe)));
/* 00264434: b 0x00264468 */ /* delay 00264438 */ set(12,sx(UINT32_C(0xfffffffe)));goto L_00264468;
L_00264440:;
/* 00264440: li t3,-0xa */ set(11,sx(UINT32_C(0xfffffff6)));
/* 00264444: b 0x00264468 */ /* delay 00264448 */ set(12,sx(UINT32_C(0xfffffff6)));goto L_00264468;
L_00264450:;
/* 00264450: b 0x00264464 */ /* delay 00264454 */ set(11,sx(UINT32_C(0x00000002)));goto L_00264464;
L_00264458:;
/* 00264458: b 0x00264464 */ /* delay 0026445c */ set(11,sx(UINT32_C(0x00000004)));goto L_00264464;
L_00264460:;
/* 00264460: li t3,0x3 */ set(11,sx(UINT32_C(0x00000003)));
L_00264464:;
/* 00264464: move t4,zero */ set(12,cpu(0));
L_00264468:;
/* 00264468: addu t0,t0,t4 */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(12)));
/* 0026446c: addu t1,t1,t3 */ set(9,sx((uint32_t)cpu(9)+(uint32_t)cpu(11)));
/* 00264470: sll v0,t8,0x10 */ set(2,sx((uint32_t)cpu(24)<<16));
/* 00264474: slti v1,t0,0x0 */ set(3,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00264478: sra t2,v0,0x10 */ set(10,sx((uint32_t)((int32_t)cpu(2)>>16)));
/* 0026447c: slti a0,t1,0x0 */ set(4,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00264480: addu a2,a2,t4 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(12)));
/* 00264484: movn t0,zero,v1 */ if(cpu(3)!=0){set(8,cpu(0));}
/* 00264488: movn t1,zero,a0 */ if(cpu(4)!=0){set(9,cpu(0));}
/* 0026448c: li a0,0x7 */ set(4,sx(UINT32_C(0x00000007)));
/* 00264490: addu v1,t2,a2 */ set(3,sx((uint32_t)cpu(10)+(uint32_t)cpu(6)));
/* 00264494: slti a1,t0,0x8 */ set(5,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 00264498: slti v0,t1,0x8 */ set(2,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0026449c: slti v1,v1,0x9 */ set(3,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 002644a0: movz t1,a0,v0 */ if(cpu(2)==0){set(9,cpu(4));}
/* 002644a4: movz t0,a0,a1 */ if(cpu(5)==0){set(8,cpu(4));}
/* 002644a8: bne v1,zero,0x002644b8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002644ac */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(11)));if(taken){goto L_002644b8;}}
/* 002644b0: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002644b4: subu a2,v0,t2 */ set(6,sx((uint32_t)cpu(2)-(uint32_t)cpu(10)));
L_002644b8:;
/* 002644b8: sll v1,t7,0x10 */ set(3,sx((uint32_t)cpu(15)<<16));
/* 002644bc: sra v1,v1,0x10 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 002644c0: addu v0,v1,a3 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 002644c4: slti v0,v0,0x9 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 002644c8: bne v0,zero,0x002644d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002644cc */ set(13,sx((uint32_t)cpu(13)+UINT32_C(0x00000001)));if(taken){goto L_002644d8;}}
/* 002644d0: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002644d4: subu a3,v0,v1 */ set(7,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
L_002644d8:;
/* 002644d8: blez t5,0x002643b8 */ {int taken=((int64_t)cpu(13)<=0);/* delay 002644dc */ set(5,cpu(8)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));if(taken){goto L_002643b8;}}
/* 002644e0: move a0,s1 */ set(4,cpu(17));
/* 002644e4: jal 0x00262ac8 */ set(31,0x002644ecu);/* delay 002644e8 */ set(5,cpu(18));body_00262ac8();
/* 002644ec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002644f0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002644f4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002644f8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002644fc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00264500: jr ra */ {uint64_t target=cpu(31);/* delay 00264504 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00264368(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_00264368();
return cpu(2);
}
