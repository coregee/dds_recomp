/* Whole original registered file-packet/thread14 native bodies.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_file_thread_frames.h"
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



#include "ee_vu_rotation.h"
/* Each partial-word instruction performs its own original merge/store.
 * Preserve upper128 CPU lanes. LWL always sign-extends; EE LWR preserves
 * bits63:32 except at aligned offset0, where it sign-extends the full word.
 */
static void loadPartial32(unsigned r,uint32_t a,int left){uint8_t d[4],s[4];uint64_t old=cpu(r);uint32_t value=(uint32_t)old;memcpy(d,&value,4);memcpy(s,at(a&~3u),4);unsigned o=a&3u;if(left){for(unsigned i=0;i<=o;i++)d[3u-o+i]=s[i];}else{for(unsigned i=o;i<4;i++)d[i-o]=s[i];}memcpy(&value,d,4);set(r,left||!o?sx(value):(old&UINT64_C(0xffffffff00000000))|value);}
static void storePartial32(uint32_t a,unsigned r,int left){uint8_t s[4];uint32_t value=(uint32_t)cpu(r);memcpy(s,&value,4);uint8_t *d=at(a&~3u);unsigned o=a&3u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[3u-o+i];}else{for(unsigned i=o;i<4;i++)d[i]=s[i-o];}}

/* Raw128 operands are fully latched before destination writes, including
 * aliases. PCPYUD uses source upper64 then target upper64 in native order. */
static void packetPacked(unsigned kind,unsigned d,unsigned s,unsigned t){
 uint32_t x[4],y[4],z[4];nocturneEffectHostCpuRead(s,x);nocturneEffectHostCpuRead(t,y);
 if(kind==0){z[0]=y[0];z[1]=y[1];z[2]=x[0];z[3]=x[1];}
 else if(kind==1){z[0]=x[2];z[1]=x[3];z[2]=y[2];z[3]=y[3];}
 else if(kind==2){for(unsigned i=0;i<4;i++)z[i]=x[i]&y[i];}
 else if(kind==3){for(unsigned i=0;i<4;i++)z[i]=~(x[i]|y[i]);}
 else if(kind==4){uint8_t a[16],b[16],c[16];memcpy(a,x,16);memcpy(b,y,16);for(unsigned i=0;i<16;i++)c[i]=(uint8_t)(a[i]-b[i]);memcpy(z,c,16);}
 else{for(unsigned i=0;i<4;i++)z[i]=x[i]^y[i];}
 nocturneEffectHostCpuWrite(d,z);
}
static void pkLq(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneEffectHostCpuWrite(r,q);}
static void sq(unsigned r,uint32_t a){uint32_t q[4];nocturneEffectHostCpuRead(r,q);memcpy(at(a&~15u),q,16);}

static void body_002a80a8(void);
static void body_002a8120(void);
static void body_002be588(void);
static void body_002be5b8(void);
static void body_002befc0(void);
static void body_002bf208(void);
static void body_002bf328(void);
static void body_002bf3a8(void);
static void body_002bf8f0(void);
static void body_002d4310(void);
static void body_002d5924(void);
static void body_002d5bf8(void);
static void body_002dbca0(void);
static void body_002dbcc0(void);
static void body_002a80a8(void){
nocturneEffectAxisNoteEntry(0x002a80a8u);
uint64_t incoming=cpu(31);
/* 002a80a8: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002a80ac: sd s1,0x38(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002a80b0: move s1,a2 */ set(17,cpu(6));
/* 002a80b4: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002a80b8: move s2,a1 */ set(18,cpu(5));
/* 002a80bc: sd s3,0x48(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002a80c0: move s3,a0 */ set(19,cpu(4));
/* 002a80c4: move a1,zero */ set(5,cpu(0));
/* 002a80c8: li a2,0x30 */ set(6,sx(UINT32_C(0x00000030)));
/* 002a80cc: move a0,sp */ set(4,cpu(29));
/* 002a80d0: sd s0,0x30(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002a80d4: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002a80d8: jal 0x002d4558 */ set(31,0x002a80e0u);/* delay 002a80dc */ set(16,cpu(7));nocturneBattleActionSkillCall(0x002d4558u);
/* 002a80e0: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002a80e4: addiu v0,v0,0x4170 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00004170)));
/* 002a80e8: move a0,sp */ set(4,cpu(29));
/* 002a80ec: sw s3,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(19));
/* 002a80f0: sw s2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));
/* 002a80f4: sw s1,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(17));
/* 002a80f8: sw s0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(16));
/* 002a80fc: jal 0x002dbca0 */ set(31,0x002a8104u);/* delay 002a8100 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));body_002dbca0();
/* 002a8104: ld s0,0x30(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002a8108: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002a810c: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002a8110: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002a8114: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002a8118: jr ra */ {uint64_t target=cpu(31);/* delay 002a811c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_002a8120(void){
nocturneEffectAxisNoteEntry(0x002a8120u);
uint64_t incoming=cpu(31);
/* 002a8120: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002a8124: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8128: move s0,a1 */ set(16,cpu(5));
/* 002a812c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8130: move s1,a0 */ set(17,cpu(4));
/* 002a8134: move a0,s0 */ set(4,cpu(16));
/* 002a8138: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a813c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8140: jal 0x002a8170 */ set(31,0x002a8148u);/* delay 002a8144 */ set(18,cpu(6));nocturneBattleActionSkillCall(0x002a8170u);
/* 002a8148: move a0,s1 */ set(4,cpu(17));
/* 002a814c: move a2,s0 */ set(6,cpu(16));
/* 002a8150: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8154: move a3,s2 */ set(7,cpu(18));
/* 002a8158: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a815c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8160: move a1,v0 */ set(5,cpu(2));
/* 002a8164: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8168: j 0x002a80a8 */ /* delay 002a816c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002a80a8();return;
}
static void body_002be588(void){
nocturneEffectAxisNoteEntry(0x002be588u);
uint64_t incoming=cpu(31);
/* 002be588: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002be58c: jr ra */ {uint64_t target=cpu(31);/* delay 002be590 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff9ac0)));checkReturn(target,incoming);return;}
}
static void body_002be5b8(void){
nocturneEffectAxisNoteEntry(0x002be5b8u);
uint64_t incoming=cpu(31);
/* 002be5b8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002be5bc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002be5c0: move s0,a0 */ set(16,cpu(4));
/* 002be5c4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be5c8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002be5cc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002be5d0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002be5d4: jal 0x002e4070 */ set(31,0x002be5dcu);/* delay 002be5d8 */ set(19,cpu(0));nocturneBattleActionSkillCall(0x002e4070u);
/* 002be5dc: lbu a0,0x14(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 002be5e0: move s2,v0 */ set(18,cpu(2));
/* 002be5e4: sll v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)<<1));
/* 002be5e8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002be5ec: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 002be5f0: lui s1,0x53 */ set(17,sx(UINT32_C(0x00530000)));
/* 002be5f4: addiu s1,s1,-0x6500 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffff9b00)));
/* 002be5f8: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002be5fc: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002be600: bgezl v1,0x002be614 */ {int taken=((int64_t)cpu(3)>=0);if(taken){/* delay 002be604 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd7dc)));goto L_002be614;}}
/* 002be608: jal 0x002bf8f0 */ set(31,0x002be610u);/* delay 002be60c */ body_002bf8f0();
/* 002be610: lw v0,-0x2824(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd7dc)));
L_002be614:;
/* 002be614: beq v0,zero,0x002be628 */ {int taken=(cpu(2)==cpu(0));/* delay 002be618 */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_002be628;}}
/* 002be61c: b 0x002be62c */ /* delay 002be620 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));goto L_002be62c;
L_002be628:;
/* 002be628: sw s0,-0x2828(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd7d8)),(uint32_t)cpu(16));
L_002be62c:;
/* 002be62c: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002be630: sw s0,-0x2824(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd7dc)),(uint32_t)cpu(16));
/* 002be634: beq v0,zero,0x002be648 */ {int taken=(cpu(2)==cpu(0));/* delay 002be638 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));if(taken){goto L_002be648;}}
/* 002be63c: b 0x002be650 */ /* delay 002be640 */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));goto L_002be650;
L_002be648:;
/* 002be648: sw s0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));
/* 002be64c: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
L_002be650:;
/* 002be650: lhu v0,-0x2814(gp) */ set(2,half(ea(28,(int32_t)UINT32_C(0xffffd7ec))));
/* 002be654: sw s0,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(16));
/* 002be658: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002be65c: beq s2,zero,0x002be66c */ {int taken=(cpu(18)==cpu(0));/* delay 002be660 */ sh(ea(28,(int32_t)UINT32_C(0xffffd7ec)),(uint16_t)cpu(2));if(taken){goto L_002be66c;}}
/* 002be664: jal 0x002e40b8 */ set(31,0x002be66cu);/* delay 002be668 */ nocturneBattleActionSkillCall(0x002e40b8u);
L_002be66c:;
/* 002be66c: beq s3,zero,0x002be690 */ {int taken=(cpu(19)==cpu(0));/* delay 002be670 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002be690;}}
/* 002be674: lw a0,0x4(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002be678: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be67c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002be680: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002be684: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002be688: j 0x002dbec0 */ /* delay 002be68c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002dbec0u);return;
L_002be690:;
/* 002be690: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be694: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002be698: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002be69c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002be6a0: jr ra */ {uint64_t target=cpu(31);/* delay 002be6a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002befc0(void){
nocturneEffectAxisNoteEntry(0x002befc0u);
uint64_t incoming=cpu(31);
/* 002befc0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002befc4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002befc8: move s0,a1 */ set(16,cpu(5));
/* 002befcc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002befd0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002befd4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002befd8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002befdc: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002befe0: jal 0x002d5d0c */ set(31,0x002befe8u);/* delay 002befe4 */ set(20,cpu(4));nocturneBattleActionSkillCall(0x002d5d0cu);
/* 002befe8: move s3,v0 */ set(19,cpu(2));
/* 002befec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002beff0: beq s0,v0,0x002bf0c8 */ {int taken=(cpu(16)==cpu(2));/* delay 002beff4 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_002bf0c8;}}
/* 002beff8: beq v0,zero,0x002bf010 */ {int taken=(cpu(2)==cpu(0));/* delay 002beffc */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_002bf010;}}
/* 002bf000: beq s0,zero,0x002bf028 */ {int taken=(cpu(16)==cpu(0));/* delay 002bf004 */ set(2,cpu(0));if(taken){goto L_002bf028;}}
/* 002bf008: b 0x002bf1e8 */ /* delay 002bf00c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002bf1e8;
L_002bf010:;
/* 002bf010: beq s0,v0,0x002bf178 */ {int taken=(cpu(16)==cpu(2));/* delay 002bf014 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002bf178;}}
/* 002bf018: beq s0,v0,0x002bf1c0 */ {int taken=(cpu(16)==cpu(2));/* delay 002bf01c */ set(2,cpu(0));if(taken){goto L_002bf1c0;}}
/* 002bf020: b 0x002bf1e8 */ /* delay 002bf024 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002bf1e8;
L_002bf028:;
/* 002bf028: jal 0x002a8af8 */ set(31,0x002bf030u);/* delay 002bf02c */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x0000000a)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 002bf030: move s2,v0 */ set(18,cpu(2));
/* 002bf034: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002bf038: addiu a2,v0,0x1968 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00001968)));
/* 002bf03c: lwl v1,0x3(a2) */ loadPartial32(3,ea(6,(int32_t)UINT32_C(0x00000003)),1);
/* 002bf040: lwr v1,0x0(a2) */ loadPartial32(3,ea(6,(int32_t)UINT32_C(0x00000000)),0);
/* 002bf044: lb a0,0x4(a2) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 002bf048: lb a1,0x5(a2) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000005))));
/* 002bf04c: swl v1,0x3(s2) */ storePartial32(ea(18,(int32_t)UINT32_C(0x00000003)),3,1);
/* 002bf050: swr v1,0x0(s2) */ storePartial32(ea(18,(int32_t)UINT32_C(0x00000000)),3,0);
/* 002bf054: sb a0,0x4(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002bf058: sb a1,0x5(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(5));
/* 002bf05c: lb v1,0x6(a2) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000006))));
/* 002bf060: sb v1,0x6(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(3));
/* 002bf064: lb a0,0x0(s4) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(20,(int32_t)UINT32_C(0x00000000))));
/* 002bf068: beq a0,zero,0x002bf0ac */ {int taken=(cpu(4)==cpu(0));/* delay 002bf06c */ set(6,cpu(0));if(taken){goto L_002bf0ac;}}
/* 002bf070: li a3,0x2f */ set(7,sx(UINT32_C(0x0000002f)));
/* 002bf074: addiu a1,s2,0x7 */ set(5,sx((uint32_t)cpu(18)+UINT32_C(0x00000007)));
L_002bf078:;
/* 002bf078: bne a0,a3,0x002bf088 */ {int taken=(cpu(4)!=cpu(7));/* delay 002bf07c */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xffffff9f)));if(taken){goto L_002bf088;}}
/* 002bf080: b 0x002bf094 */ /* delay 002bf084 */ set(4,sx(UINT32_C(0x0000005c)));goto L_002bf094;
L_002bf088:;
/* 002bf088: addiu v1,a0,-0x20 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0xffffffe0)));
/* 002bf08c: sltiu v0,v0,0x1a */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000001a));
/* 002bf090: movn a0,v1,v0 */ if(cpu(2)!=0){set(4,cpu(3));}
L_002bf094:;
/* 002bf094: sb a0,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 002bf098: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 002bf09c: addu v0,s4,a2 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(6)));
/* 002bf0a0: lb a0,0x0(v0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002bf0a4: bne a0,zero,0x002bf078 */ {int taken=(cpu(4)!=cpu(0));/* delay 002bf0a8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_002bf078;}}
L_002bf0ac:;
/* 002bf0ac: addu v0,s2,a2 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(6)));
/* 002bf0b0: li v1,0x3b */ set(3,sx(UINT32_C(0x0000003b)));
/* 002bf0b4: li a0,0x31 */ set(4,sx(UINT32_C(0x00000031)));
/* 002bf0b8: sb v1,0x7(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000007)),(uint8_t)cpu(3));
/* 002bf0bc: sb a0,0x8(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000008)),(uint8_t)cpu(4));
/* 002bf0c0: b 0x002bf1e0 */ /* delay 002bf0c4 */ sb(ea(2,(int32_t)UINT32_C(0x00000009)),(uint8_t)cpu(0));goto L_002bf1e0;
L_002bf0c8:;
/* 002bf0c8: lb v1,0x0(s4) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(20,(int32_t)UINT32_C(0x00000000))));
/* 002bf0cc: li v0,0x2f */ set(2,sx(UINT32_C(0x0000002f)));
/* 002bf0d0: beq v1,v0,0x002bf128 */ {int taken=(cpu(3)==cpu(2));/* delay 002bf0d4 */ if(taken){goto L_002bf128;}}
/* 002bf0d8: jal 0x002a8af8 */ set(31,0x002bf0e0u);/* delay 002bf0dc */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00000007)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 002bf0e0: move s2,v0 */ set(18,cpu(2));
/* 002bf0e4: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002bf0e8: addiu a2,v0,0x1970 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00001970)));
/* 002bf0ec: lwl v1,0x3(a2) */ loadPartial32(3,ea(6,(int32_t)UINT32_C(0x00000003)),1);
/* 002bf0f0: lwr v1,0x0(a2) */ loadPartial32(3,ea(6,(int32_t)UINT32_C(0x00000000)),0);
/* 002bf0f4: lb a0,0x4(a2) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 002bf0f8: lb a1,0x5(a2) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000005))));
/* 002bf0fc: swl v1,0x3(s2) */ storePartial32(ea(18,(int32_t)UINT32_C(0x00000003)),3,1);
/* 002bf100: swr v1,0x0(s2) */ storePartial32(ea(18,(int32_t)UINT32_C(0x00000000)),3,0);
/* 002bf104: sb a0,0x4(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002bf108: sb a1,0x5(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(5));
/* 002bf10c: move a1,s4 */ set(5,cpu(20));
/* 002bf110: addiu a0,s2,0x6 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000006)));
/* 002bf114: jal 0x002d43a4 */ set(31,0x002bf11cu);/* delay 002bf118 */ set(6,cpu(19));nocturneBattleActionSkillCall(0x002d43a4u);
/* 002bf11c: addu v1,s2,s3 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(19)));
/* 002bf120: b 0x002bf1e0 */ /* delay 002bf124 */ sb(ea(3,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(0));goto L_002bf1e0;
L_002bf128:;
/* 002bf128: jal 0x002be588 */ set(31,0x002bf130u);/* delay 002bf12c */ body_002be588();
/* 002bf130: move s1,v0 */ set(17,cpu(2));
/* 002bf134: jal 0x002d5d0c */ set(31,0x002bf13cu);/* delay 002bf138 */ set(4,cpu(17));nocturneBattleActionSkillCall(0x002d5d0cu);
/* 002bf13c: move s0,v0 */ set(16,cpu(2));
/* 002bf140: jal 0x002a8af8 */ set(31,0x002bf148u);/* delay 002bf144 */ set(4,sx((uint32_t)cpu(19)+(uint32_t)cpu(16)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 002bf148: move a1,s1 */ set(5,cpu(17));
/* 002bf14c: move s2,v0 */ set(18,cpu(2));
/* 002bf150: move a2,s0 */ set(6,cpu(16));
/* 002bf154: jal 0x002d43a4 */ set(31,0x002bf15cu);/* delay 002bf158 */ set(4,cpu(18));nocturneBattleActionSkillCall(0x002d43a4u);
/* 002bf15c: addu a0,s2,s0 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(16)));
/* 002bf160: addiu a1,s4,0x1 */ set(5,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
/* 002bf164: jal 0x002d43a4 */ set(31,0x002bf16cu);/* delay 002bf168 */ set(6,cpu(19));nocturneBattleActionSkillCall(0x002d43a4u);
/* 002bf16c: b 0x002bf1e4 */ /* delay 002bf170 */ set(2,cpu(18));goto L_002bf1e4;
L_002bf178:;
/* 002bf178: jal 0x002a8af8 */ set(31,0x002bf180u);/* delay 002bf17c */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00000006)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 002bf180: move s2,v0 */ set(18,cpu(2));
/* 002bf184: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002bf188: addiu a2,v0,0x1978 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00001978)));
/* 002bf18c: lwl v1,0x3(a2) */ loadPartial32(3,ea(6,(int32_t)UINT32_C(0x00000003)),1);
/* 002bf190: lwr v1,0x0(a2) */ loadPartial32(3,ea(6,(int32_t)UINT32_C(0x00000000)),0);
/* 002bf194: lb a0,0x4(a2) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 002bf198: swl v1,0x3(s2) */ storePartial32(ea(18,(int32_t)UINT32_C(0x00000003)),3,1);
/* 002bf19c: swr v1,0x0(s2) */ storePartial32(ea(18,(int32_t)UINT32_C(0x00000000)),3,0);
/* 002bf1a0: sb a0,0x4(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002bf1a4: move a1,s4 */ set(5,cpu(20));
/* 002bf1a8: addiu a0,s2,0x5 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000005)));
/* 002bf1ac: jal 0x002d43a4 */ set(31,0x002bf1b4u);/* delay 002bf1b0 */ set(6,cpu(19));nocturneBattleActionSkillCall(0x002d43a4u);
/* 002bf1b4: addu v1,s2,s3 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(19)));
/* 002bf1b8: b 0x002bf1e0 */ /* delay 002bf1bc */ sb(ea(3,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(0));goto L_002bf1e0;
L_002bf1c0:;
/* 002bf1c0: jal 0x002a8af8 */ set(31,0x002bf1c8u);/* delay 002bf1c4 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 002bf1c8: move a1,s4 */ set(5,cpu(20));
/* 002bf1cc: move s2,v0 */ set(18,cpu(2));
/* 002bf1d0: jal 0x002d5bf8 */ set(31,0x002bf1d8u);/* delay 002bf1d4 */ set(4,cpu(18));body_002d5bf8();
/* 002bf1d8: b 0x002bf1e4 */ /* delay 002bf1dc */ set(2,cpu(18));goto L_002bf1e4;
L_002bf1e0:;
/* 002bf1e0: move v0,s2 */ set(2,cpu(18));
L_002bf1e4:;
/* 002bf1e4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002bf1e8:;
/* 002bf1e8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf1ec: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf1f0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf1f4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf1f8: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002bf1fc: jr ra */ {uint64_t target=cpu(31);/* delay 002bf200 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002bf208(void){
nocturneEffectAxisNoteEntry(0x002bf208u);
uint64_t incoming=cpu(31);
/* 002bf208: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002bf20c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf210: move s2,a1 */ set(18,cpu(5));
/* 002bf214: li a1,0x3a */ set(5,sx(UINT32_C(0x0000003a)));
/* 002bf218: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf21c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf220: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf224: jal 0x002d5924 */ set(31,0x002bf22cu);/* delay 002bf228 */ set(17,cpu(4));body_002d5924();
/* 002bf22c: beq v0,zero,0x002bf2f8 */ {int taken=(cpu(2)==cpu(0));/* delay 002bf230 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_002bf2f8;}}
/* 002bf234: move a0,s1 */ set(4,cpu(17));
/* 002bf238: addiu a1,a1,0x1968 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001968)));
/* 002bf23c: jal 0x002d4310 */ set(31,0x002bf244u);/* delay 002bf240 */ set(6,sx(UINT32_C(0x00000007)));body_002d4310();
/* 002bf244: bne v0,zero,0x002bf280 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bf248 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_002bf280;}}
/* 002bf24c: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 002bf250: addiu a0,s1,0x7 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000007)));
/* 002bf254: addiu a1,a1,0x1980 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001980)));
/* 002bf258: jal 0x002d4310 */ set(31,0x002bf260u);/* delay 002bf25c */ set(6,sx(UINT32_C(0x00000007)));body_002d4310();
/* 002bf260: bnel v0,zero,0x002bf278 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002bf264 */ set(16,cpu(0));goto L_002bf278;}}
/* 002bf268: li s0,0x3 */ set(16,sx(UINT32_C(0x00000003)));
/* 002bf26c: b 0x002bf2f0 */ /* delay 002bf270 */ set(4,cpu(0));goto L_002bf2f0;
L_002bf278:;
/* 002bf278: b 0x002bf2f0 */ /* delay 002bf27c */ set(4,sx(UINT32_C(0x00000007)));goto L_002bf2f0;
L_002bf280:;
/* 002bf280: move a0,s1 */ set(4,cpu(17));
/* 002bf284: addiu a1,a1,0x1970 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001970)));
/* 002bf288: jal 0x002d4310 */ set(31,0x002bf290u);/* delay 002bf28c */ set(6,sx(UINT32_C(0x00000006)));body_002d4310();
/* 002bf290: bne v0,zero,0x002bf2a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bf294 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_002bf2a8;}}
/* 002bf298: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
/* 002bf29c: b 0x002bf2f0 */ /* delay 002bf2a0 */ set(4,sx(UINT32_C(0x00000006)));goto L_002bf2f0;
L_002bf2a8:;
/* 002bf2a8: move a0,s1 */ set(4,cpu(17));
/* 002bf2ac: addiu a1,a1,0x1978 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001978)));
/* 002bf2b0: jal 0x002d4310 */ set(31,0x002bf2b8u);/* delay 002bf2b4 */ set(6,sx(UINT32_C(0x00000005)));body_002d4310();
/* 002bf2b8: bne v0,zero,0x002bf2d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bf2bc */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_002bf2d0;}}
/* 002bf2c0: li s0,0x2 */ set(16,sx(UINT32_C(0x00000002)));
/* 002bf2c4: b 0x002bf2f0 */ /* delay 002bf2c8 */ set(4,sx(UINT32_C(0x00000005)));goto L_002bf2f0;
L_002bf2d0:;
/* 002bf2d0: move a0,s1 */ set(4,cpu(17));
/* 002bf2d4: addiu a1,a1,0x1988 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001988)));
/* 002bf2d8: jal 0x002d4310 */ set(31,0x002bf2e0u);/* delay 002bf2dc */ set(6,sx(UINT32_C(0x00000006)));body_002d4310();
/* 002bf2e0: bne v0,zero,0x002bf310 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bf2e4 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002bf310;}}
/* 002bf2e8: li s0,0x3 */ set(16,sx(UINT32_C(0x00000003)));
/* 002bf2ec: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
L_002bf2f0:;
/* 002bf2f0: b 0x002bf300 */ /* delay 002bf2f4 */ set(4,sx((uint32_t)cpu(17)+(uint32_t)cpu(4)));goto L_002bf300;
L_002bf2f8:;
/* 002bf2f8: lbu s0,-0x2812(gp) */ set(16,byte(ea(28,(int32_t)UINT32_C(0xffffd7ee))));
/* 002bf2fc: move a0,s1 */ set(4,cpu(17));
L_002bf300:;
/* 002bf300: jal 0x002befc0 */ set(31,0x002bf308u);/* delay 002bf304 */ set(5,cpu(16));body_002befc0();
/* 002bf308: sw v0,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002bf30c: move v0,s0 */ set(2,cpu(16));
L_002bf310:;
/* 002bf310: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf314: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf318: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf31c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf320: jr ra */ {uint64_t target=cpu(31);/* delay 002bf324 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002bf328(void){
nocturneEffectAxisNoteEntry(0x002bf328u);
uint64_t incoming=cpu(31);
/* 002bf328: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002bf32c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf330: move s3,a0 */ set(19,cpu(4));
/* 002bf334: li a0,0x40 */ set(4,sx(UINT32_C(0x00000040)));
/* 002bf338: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf33c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf340: move s1,a1 */ set(17,cpu(5));
/* 002bf344: move s0,t0 */ set(16,cpu(8));
/* 002bf348: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf34c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf350: move s4,a3 */ set(20,cpu(7));
/* 002bf354: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002bf358: jal 0x002a8ba8 */ set(31,0x002bf360u);/* delay 002bf35c */ set(18,cpu(6));nocturneBattleActionSkillCall(0x002a8ba8u);
/* 002bf360: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 002bf364: move v1,v0 */ set(3,cpu(2));
/* 002bf368: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002bf36c: sw s0,0x3c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(16));
/* 002bf370: sw s3,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(19));
/* 002bf374: sb s1,0x14(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(17));
/* 002bf378: sb s2,0x15(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000015)),(uint8_t)cpu(18));
/* 002bf37c: sw s4,0x38(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(20));
/* 002bf380: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf384: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf388: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf38c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf390: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf394: sw a0,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(4));
/* 002bf398: sb zero,0x16(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(0));
/* 002bf39c: jr ra */ {uint64_t target=cpu(31);/* delay 002bf3a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002bf3a8(void){
nocturneEffectAxisNoteEntry(0x002bf3a8u);
uint64_t incoming=cpu(31);
/* 002bf3a8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002bf3ac: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf3b0: move s1,a1 */ set(17,cpu(5));
/* 002bf3b4: move a1,sp */ set(5,cpu(29));
/* 002bf3b8: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf3bc: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf3c0: jal 0x002bf208 */ set(31,0x002bf3c8u);/* delay 002bf3c4 */ set(16,cpu(6));body_002bf208();
/* 002bf3c8: move a3,s1 */ set(7,cpu(17));
/* 002bf3cc: move v1,v0 */ set(3,cpu(2));
/* 002bf3d0: move v0,zero */ set(2,cpu(0));
/* 002bf3d4: move a1,v1 */ set(5,cpu(3));
/* 002bf3d8: move t0,s0 */ set(8,cpu(16));
/* 002bf3dc: bltz v1,0x002bf3fc */ {int taken=((int64_t)cpu(3)<0);/* delay 002bf3e0 */ set(6,sx(UINT32_C(0x00000001)));if(taken){goto L_002bf3fc;}}
/* 002bf3e4: jal 0x002bf328 */ set(31,0x002bf3ecu);/* delay 002bf3e8 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));body_002bf328();
/* 002bf3ec: move s0,v0 */ set(16,cpu(2));
/* 002bf3f0: jal 0x002be5b8 */ set(31,0x002bf3f8u);/* delay 002bf3f4 */ set(4,cpu(16));body_002be5b8();
/* 002bf3f8: move v0,s0 */ set(2,cpu(16));
L_002bf3fc:;
/* 002bf3fc: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf400: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf404: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002bf408: jr ra */ {uint64_t target=cpu(31);/* delay 002bf40c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002bf8f0(void){
nocturneEffectAxisNoteEntry(0x002bf8f0u);
uint64_t incoming=cpu(31);
/* 002bf8f0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002bf8f4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf8f8: move s1,a0 */ set(17,cpu(4));
/* 002bf8fc: sll v0,s1,0x1 */ set(2,sx((uint32_t)cpu(17)<<1));
/* 002bf900: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf904: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 002bf908: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf90c: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 002bf910: lui s0,0x53 */ set(16,sx(UINT32_C(0x00530000)));
/* 002bf914: addiu s0,s0,-0x6500 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffff9b00)));
/* 002bf918: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002bf91c: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002bf920: bgez v0,0x002bf988 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002bf924 */ set(4,cpu(0));if(taken){goto L_002bf988;}}
/* 002bf928: li a1,0xff */ set(5,sx(UINT32_C(0x000000ff)));
/* 002bf92c: jal 0x002a8080 */ set(31,0x002bf934u);/* delay 002bf930 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x002a8080u);
/* 002bf934: li a1,0x4000 */ set(5,sx(UINT32_C(0x00004000)));
/* 002bf938: lui v1,0x2c */ set(3,sx(UINT32_C(0x002c0000)));
/* 002bf93c: li a0,0x3 */ set(4,sx(UINT32_C(0x00000003)));
/* 002bf940: li a2,0x48 */ set(6,sx(UINT32_C(0x00000048)));
/* 002bf944: addiu v1,v1,-0x12b0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffed50)));
/* 002bf948: beq s1,a0,0x002bf958 */ {int taken=(cpu(17)==cpu(4));/* delay 002bf94c */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_002bf958;}}
/* 002bf950: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002bf954: addiu v1,v0,-0x1738 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0xffffe8c8)));
L_002bf958:;
/* 002bf958: move a0,v1 */ set(4,cpu(3));
/* 002bf95c: li v0,0x48 */ set(2,sx(UINT32_C(0x00000048)));
/* 002bf960: jal 0x002a8120 */ set(31,0x002bf968u);/* delay 002bf964 */ sw(ea(28,(int32_t)UINT32_C(0xffffd7f0)),(uint32_t)cpu(2));body_002a8120();
/* 002bf968: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002bf96c: move a1,s0 */ set(5,cpu(16));
/* 002bf970: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf974: move a0,v0 */ set(4,cpu(2));
/* 002bf978: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf97c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf980: j 0x002dbcc0 */ /* delay 002bf984 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002dbcc0();return;
L_002bf988:;
/* 002bf988: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf98c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf990: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf994: jr ra */ {uint64_t target=cpu(31);/* delay 002bf998 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002d4310(void){
nocturneEffectAxisNoteEntry(0x002d4310u);
uint64_t incoming=cpu(31);
/* 002d4310: sltiu v0,a2,0x10 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d4314: bne v0,zero,0x002d435c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4318 */ set(2,cpu(4)|cpu(5));if(taken){goto L_002d435c;}}
/* 002d431c: andi v0,v0,0xf */ set(2,cpu(2)&UINT32_C(0x0000000f));
/* 002d4320: bne v0,zero,0x002d435c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4324 */ if(taken){goto L_002d435c;}}
L_002d4328:;
/* 002d4328: lq v1,0x0(a0) */ pkLq(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d432c: sltiu a3,a2,0x20 */ set(7,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d4330: lq v0,0x0(a1) */ pkLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d4334: addiu a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
/* 002d4338: pxor t0,v0,v1 */ packetPacked(5,8,2,3);
/* 002d433c: addiu v0,a1,0x10 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d4340: pcpyud t2,t0,a3 */ packetPacked(1,10,8,7);
/* 002d4344: or t1,t2,t0 */ set(9,cpu(10)|cpu(8));
/* 002d4348: movz a1,v0,t1 */ if(cpu(9)==0){set(5,cpu(2));}
/* 002d434c: bnel t1,zero,0x002d435c */ {int taken=(cpu(9)!=cpu(0));if(taken){/* delay 002d4350 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffff0)));goto L_002d435c;}}
/* 002d4354: beq a3,zero,0x002d4328 */ {int taken=(cpu(7)==cpu(0));/* delay 002d4358 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xfffffff0)));if(taken){goto L_002d4328;}}
L_002d435c:;
/* 002d435c: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 002d4360: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d4364: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d4368: beq a2,v0,0x002d439c */ {int taken=(cpu(6)==cpu(2));/* delay 002d436c */ if(taken){goto L_002d439c;}}
/* 002d4370: lui a3,0xffff */ set(7,sx(UINT32_C(0xffff0000)));
/* 002d4374: ori a3,a3,0xffff */ set(7,cpu(7)|UINT32_C(0x0000ffff));
L_002d4378:;
/* 002d4378: lbu v1,0x0(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002d437c: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d4380: beq v1,v0,0x002d4390 */ {int taken=(cpu(3)==cpu(2));/* delay 002d4384 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));if(taken){goto L_002d4390;}}
/* 002d4388: jr ra */ {uint64_t target=cpu(31);/* delay 002d438c */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));checkReturn(target,incoming);return;}
L_002d4390:;
/* 002d4390: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d4394: bne a2,a3,0x002d4378 */ {int taken=(cpu(6)!=cpu(7));/* delay 002d4398 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_002d4378;}}
L_002d439c:;
/* 002d439c: jr ra */ {uint64_t target=cpu(31);/* delay 002d43a0 */ set(2,cpu(0));checkReturn(target,incoming);return;}
}
static void body_002d5924(void){
nocturneEffectAxisNoteEntry(0x002d5924u);
uint64_t incoming=cpu(31);
/* 002d5924: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 002d5928: bne v0,zero,0x002d5a94 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d592c */ set(5,cpu(5)&UINT32_C(0x000000ff));if(taken){goto L_002d5a94;}}
/* 002d5930: dsll v1,a1,0x8 */ set(3,cpu(5)<<8);
/* 002d5934: lui a2,0x101 */ set(6,sx(UINT32_C(0x01010000)));
/* 002d5938: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d593c: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d5940: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d5944: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d5948: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d594c: daddu t2,v1,a1 */ set(10,cpu(3)+cpu(5));
/* 002d5950: andi v1,a0,0xf */ set(3,cpu(4)&UINT32_C(0x0000000f));
/* 002d5954: dsll v0,t2,0x10 */ set(2,cpu(10)<<16);
/* 002d5958: lui t0,0x8080 */ set(8,sx(UINT32_C(0x80800000)));
/* 002d595c: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d5960: dsll t0,t0,0x10 */ set(8,cpu(8)<<16);
/* 002d5964: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d5968: dsll t0,t0,0x10 */ set(8,cpu(8)<<16);
/* 002d596c: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d5970: daddu v0,v0,t2 */ set(2,cpu(2)+cpu(10));
/* 002d5974: dsll32 t2,v0,0x0 */ set(10,cpu(2)<<32);
/* 002d5978: bne v1,zero,0x002d5a0c */ {int taken=(cpu(3)!=cpu(0));/* delay 002d597c */ set(7,cpu(2)+cpu(10));if(taken){goto L_002d5a0c;}}
L_002d5980:;
/* 002d5980: lq t1,0x0(a0) */ pkLq(9,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5984: pcpyld t2,a2,a2 */ packetPacked(0,10,6,6);
/* 002d5988: pnor v1,zero,t1 */ packetPacked(3,3,0,9);
/* 002d598c: psubb v0,t1,t2 */ packetPacked(4,2,9,10);
/* 002d5990: pcpyld a2,t0,t0 */ packetPacked(0,6,8,8);
/* 002d5994: pand v0,v0,v1 */ packetPacked(2,2,2,3);
/* 002d5998: pcpyld t0,a3,a3 */ packetPacked(0,8,7,7);
/* 002d599c: pand v0,v0,a2 */ packetPacked(2,2,2,6);
/* 002d59a0: pcpyud v1,v0,a3 */ packetPacked(1,3,2,7);
/* 002d59a4: or v1,v0,v1 */ set(3,cpu(2)|cpu(3));
/* 002d59a8: bnel v1,zero,0x002d5a98 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d59ac */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;}}
/* 002d59b0: pxor v0,t1,t0 */ packetPacked(5,2,9,8);
/* 002d59b4: psubb v1,v0,t2 */ packetPacked(4,3,2,10);
/* 002d59b8: pnor v0,zero,v0 */ packetPacked(3,2,0,2);
/* 002d59bc: lui t0,0x8080 */ set(8,sx(UINT32_C(0x80800000)));
/* 002d59c0: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d59c4: dsll t0,t0,0x10 */ set(8,cpu(8)<<16);
/* 002d59c8: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d59cc: dsll t0,t0,0x10 */ set(8,cpu(8)<<16);
/* 002d59d0: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 002d59d4: pand v1,v1,v0 */ packetPacked(2,3,3,2);
/* 002d59d8: pand v1,v1,a2 */ packetPacked(2,3,3,6);
/* 002d59dc: lui a2,0x101 */ set(6,sx(UINT32_C(0x01010000)));
/* 002d59e0: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d59e4: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d59e8: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d59ec: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d59f0: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d59f4: pcpyud v0,v1,a1 */ packetPacked(1,2,3,5);
/* 002d59f8: or v1,v0,v1 */ set(3,cpu(2)|cpu(3));
/* 002d59fc: beql v1,zero,0x002d5980 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002d5a00 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));goto L_002d5980;}}
/* 002d5a04: b 0x002d5a98 */ /* delay 002d5a08 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;
L_002d5a0c:;
/* 002d5a0c: ld t1,0x0(a0) */ restore(9,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5a10: nor v1,zero,t1 */ set(3,~(cpu(0)|cpu(9)));
/* 002d5a14: dsubu v0,t1,a2 */ set(2,cpu(9)-cpu(6));
/* 002d5a18: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5a1c: and v0,v0,t0 */ set(2,cpu(2)&cpu(8));
/* 002d5a20: bnel v0,zero,0x002d5a98 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d5a24 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;}}
/* 002d5a28: xor v0,t1,a3 */ set(2,cpu(9)^cpu(7));
/* 002d5a2c: dsubu v1,v0,a2 */ set(3,cpu(2)-cpu(6));
/* 002d5a30: nor v0,zero,v0 */ set(2,~(cpu(0)|cpu(2)));
/* 002d5a34: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 002d5a38: and v1,v1,t0 */ set(3,cpu(3)&cpu(8));
/* 002d5a3c: bnel v1,zero,0x002d5a98 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d5a40 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;}}
/* 002d5a44: move t1,a2 */ set(9,cpu(6));
/* 002d5a48: addiu a0,a0,0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
L_002d5a4c:;
/* 002d5a4c: ld a2,0x0(a0) */ restore(6,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5a50: dsubu v0,a2,t1 */ set(2,cpu(6)-cpu(9));
/* 002d5a54: nor v1,zero,a2 */ set(3,~(cpu(0)|cpu(6)));
/* 002d5a58: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5a5c: and v0,v0,t0 */ set(2,cpu(2)&cpu(8));
/* 002d5a60: bne v0,zero,0x002d5a94 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5a64 */ set(2,cpu(6)^cpu(7));if(taken){goto L_002d5a94;}}
/* 002d5a68: nor v1,zero,v0 */ set(3,~(cpu(0)|cpu(2)));
/* 002d5a6c: dsubu v0,v0,t1 */ set(2,cpu(2)-cpu(9));
/* 002d5a70: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5a74: and v0,v0,t0 */ set(2,cpu(2)&cpu(8));
/* 002d5a78: beql v0,zero,0x002d5a4c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d5a7c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));goto L_002d5a4c;}}
/* 002d5a80: b 0x002d5a98 */ /* delay 002d5a84 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5a98;
L_002d5a88:;
/* 002d5a88: beql v0,a1,0x002d5aa4 */ {int taken=(cpu(2)==cpu(5));if(taken){/* delay 002d5a8c */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5aa4;}}
/* 002d5a90: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
L_002d5a94:;
/* 002d5a94: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
L_002d5a98:;
/* 002d5a98: bne v0,zero,0x002d5a88 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5a9c */ if(taken){goto L_002d5a88;}}
/* 002d5aa0: lbu v1,0x0(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
L_002d5aa4:;
/* 002d5aa4: move v0,zero */ set(2,cpu(0));
/* 002d5aa8: xor v1,v1,a1 */ set(3,cpu(3)^cpu(5));
/* 002d5aac: jr ra */ {uint64_t target=cpu(31);/* delay 002d5ab0 */ if(cpu(3)==0){set(2,cpu(4));}checkReturn(target,incoming);return;}
}
static void body_002d5bf8(void){
nocturneEffectAxisNoteEntry(0x002d5bf8u);
uint64_t incoming=cpu(31);
/* 002d5bf8: move a3,a0 */ set(7,cpu(4));
/* 002d5bfc: or t0,a1,a3 */ set(8,cpu(5)|cpu(7));
/* 002d5c00: andi v0,t0,0x7 */ set(2,cpu(8)&UINT32_C(0x00000007));
/* 002d5c04: bne v0,zero,0x002d5ce8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5c08 */ set(3,cpu(7));if(taken){goto L_002d5ce8;}}
/* 002d5c0c: andi v0,t0,0xf */ set(2,cpu(8)&UINT32_C(0x0000000f));
/* 002d5c10: lui t1,0x101 */ set(9,sx(UINT32_C(0x01010000)));
/* 002d5c14: ori t1,t1,0x101 */ set(9,cpu(9)|UINT32_C(0x00000101));
/* 002d5c18: dsll t1,t1,0x10 */ set(9,cpu(9)<<16);
/* 002d5c1c: ori t1,t1,0x101 */ set(9,cpu(9)|UINT32_C(0x00000101));
/* 002d5c20: dsll t1,t1,0x10 */ set(9,cpu(9)<<16);
/* 002d5c24: ori t1,t1,0x101 */ set(9,cpu(9)|UINT32_C(0x00000101));
/* 002d5c28: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 002d5c2c: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5c30: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5c34: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5c38: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5c3c: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5c40: bnel v0,zero,0x002d5ca8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d5c44 */ restore(10,ea(5,(int32_t)UINT32_C(0x00000000)));goto L_002d5ca8;}}
/* 002d5c48: pcpyld t2,t1,t1 */ packetPacked(0,10,9,9);
/* 002d5c4c: lq t1,0x0(a1) */ pkLq(9,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5c50: pcpyld t0,a0,a0 */ packetPacked(0,8,4,4);
/* 002d5c54: psubb v0,t1,t2 */ packetPacked(4,2,9,10);
/* 002d5c58: pnor v1,zero,t1 */ packetPacked(3,3,0,9);
/* 002d5c5c: pand v0,v0,v1 */ packetPacked(2,2,2,3);
/* 002d5c60: pand v0,v0,t0 */ packetPacked(2,2,2,8);
/* 002d5c64: pcpyud a0,v0,t1 */ packetPacked(1,4,2,9);
/* 002d5c68: or v1,v0,a0 */ set(3,cpu(2)|cpu(4));
/* 002d5c6c: bne v1,zero,0x002d5ce4 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d5c70 */ set(6,cpu(7));if(taken){goto L_002d5ce4;}}
L_002d5c74:;
/* 002d5c74: sq t1,0x0(a2) */ sq(9,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002d5c78: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d5c7c: lq t1,0x0(a1) */ pkLq(9,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5c80: psubb v0,t1,t2 */ packetPacked(4,2,9,10);
/* 002d5c84: pnor v1,zero,t1 */ packetPacked(3,3,0,9);
/* 002d5c88: pand v0,v0,v1 */ packetPacked(2,2,2,3);
/* 002d5c8c: pand v0,v0,t0 */ packetPacked(2,2,2,8);
/* 002d5c90: pcpyud a0,v0,t1 */ packetPacked(1,4,2,9);
/* 002d5c94: or v1,v0,a0 */ set(3,cpu(2)|cpu(4));
/* 002d5c98: beq v1,zero,0x002d5c74 */ {int taken=(cpu(3)==cpu(0));/* delay 002d5c9c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000010)));if(taken){goto L_002d5c74;}}
/* 002d5ca0: b 0x002d5ce8 */ /* delay 002d5ca4 */ set(3,cpu(6));goto L_002d5ce8;
L_002d5ca8:;
/* 002d5ca8: dsubu v0,t2,t1 */ set(2,cpu(10)-cpu(9));
/* 002d5cac: nor v1,zero,t2 */ set(3,~(cpu(0)|cpu(10)));
/* 002d5cb0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5cb4: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 002d5cb8: bne v0,zero,0x002d5ce4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5cbc */ set(6,cpu(7));if(taken){goto L_002d5ce4;}}
L_002d5cc0:;
/* 002d5cc0: sd t2,0x0(a2) */ save(10,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002d5cc4: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 002d5cc8: ld t2,0x0(a1) */ restore(10,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5ccc: nor v0,zero,t2 */ set(2,~(cpu(0)|cpu(10)));
/* 002d5cd0: dsubu v1,t2,t1 */ set(3,cpu(10)-cpu(9));
/* 002d5cd4: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 002d5cd8: and v1,v1,a0 */ set(3,cpu(3)&cpu(4));
/* 002d5cdc: beq v1,zero,0x002d5cc0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d5ce0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000008)));if(taken){goto L_002d5cc0;}}
L_002d5ce4:;
/* 002d5ce4: move v1,a2 */ set(3,cpu(6));
L_002d5ce8:;
/* 002d5ce8: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d5cec: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002d5cf0: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d5cf4: sll v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)<<24));
/* 002d5cf8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d5cfc: bne v0,zero,0x002d5ce8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5d00 */ if(taken){goto L_002d5ce8;}}
/* 002d5d04: jr ra */ {uint64_t target=cpu(31);/* delay 002d5d08 */ set(2,cpu(7));checkReturn(target,incoming);return;}
}
static void body_002dbca0(void){
nocturneEffectAxisNoteEntry(0x002dbca0u);
uint64_t incoming=cpu(31);
/* 002dbca0: li v1,0x20 */ set(3,sx(UINT32_C(0x00000020)));
/* 002dbca4: syscall 0x0 */ {const uint64_t arguments[1]={cpu(4)};set(2,nocturneBattleActionSkillKernelValue(cpu(3),0x002dbca4u,1u,arguments));}
/* 002dbca8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbcac */ checkReturn(target,incoming);return;}
}
static void body_002dbcc0(void){
nocturneEffectAxisNoteEntry(0x002dbcc0u);
uint64_t incoming=cpu(31);
/* 002dbcc0: li v1,0x22 */ set(3,sx(UINT32_C(0x00000022)));
/* 002dbcc4: syscall 0x0 */ {const uint64_t arguments[2]={cpu(4),cpu(5)};set(2,nocturneBattleActionSkillKernelValue(cpu(3),0x002dbcc4u,2u,arguments));}
/* 002dbcc8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbccc */ checkReturn(target,incoming);return;}
}
uint32_t nocturneBattleActionSkillFileThreadBody(uint32_t entry){switch(entry){
case 0x002a80a8u:body_002a80a8();return 1u;
case 0x002a8120u:body_002a8120();return 1u;
case 0x002be588u:body_002be588();return 1u;
case 0x002be5b8u:body_002be5b8();return 1u;
case 0x002befc0u:body_002befc0();return 1u;
case 0x002bf208u:body_002bf208();return 1u;
case 0x002bf328u:body_002bf328();return 1u;
case 0x002bf3a8u:body_002bf3a8();return 1u;
case 0x002bf8f0u:body_002bf8f0();return 1u;
case 0x002d4310u:body_002d4310();return 1u;
case 0x002d5924u:body_002d5924();return 1u;
case 0x002d5bf8u:body_002d5bf8();return 1u;
case 0x002dbca0u:body_002dbca0();return 1u;
case 0x002dbcc0u:body_002dbcc0();return 1u;
default:return 0u;}}
uint64_t ps2BattleActionSkillFileRequestRead_002BF3A8(uint64_t path,uint64_t callback,uint64_t payload){set(4,path);set(5,callback);set(6,payload);body_002bf3a8();return cpu(2);}
