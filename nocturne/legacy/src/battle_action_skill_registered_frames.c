/* Whole93 registered SKILL dependency native variants; zero new identities.
 * Fixed statements/labels retain original operation and delay positions.
 * No opcode loop, game-result callback, captured output, stack patch or
 * caller-filled local target list. Native frames occupy actual shared RAM.
 */
#include "battle_action_skill_registered_frames.h"
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
static void nativeDivide(uint32_t n,uint32_t d,int isSigned,int secondary){
 uint32_t q,r;
 if(!d){q=isSigned&&((int32_t)n<0)?1u:UINT32_MAX;r=n;}
 else if(isSigned&&n==UINT32_C(0x80000000)&&d==UINT32_MAX){q=n;r=0;}
 else if(isSigned){q=(uint32_t)((int32_t)n/(int32_t)d);r=(uint32_t)((int32_t)n%(int32_t)d);}
 else{q=n/d;r=n%d;}
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx(q),sx(r));
 else EE_PCP_EFFECT_DIV_STATE(q,r);
}


#include "ee_vu_rotation.h"
/* Each partial-word instruction performs its own original merge/store.
 * Preserve upper128 CPU lanes. LWL always sign-extends; EE LWR preserves
 * bits63:32 except at aligned offset0, where it sign-extends the full word.
 */
static void loadPartial32(unsigned r,uint32_t a,int left){uint8_t d[4],s[4];uint64_t old=cpu(r);uint32_t value=(uint32_t)old;memcpy(d,&value,4);memcpy(s,at(a&~3u),4);unsigned o=a&3u;if(left){for(unsigned i=0;i<=o;i++)d[3u-o+i]=s[i];}else{for(unsigned i=o;i<4;i++)d[i-o]=s[i];}memcpy(&value,d,4);set(r,left||!o?sx(value):(old&UINT64_C(0xffffffff00000000))|value);}
static void storePartial32(uint32_t a,unsigned r,int left){uint8_t s[4];uint32_t value=(uint32_t)cpu(r);memcpy(s,&value,4);uint8_t *d=at(a&~3u);unsigned o=a&3u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[3u-o+i];}else{for(unsigned i=o;i<4;i++)d[i]=s[i-o];}}

static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}

static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}

static void loadVu(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a),16);EE_ROT_VU_WRITE(r,q);}

static void moveVu(unsigned d,unsigned s){uint32_t q[4];EE_ROT_VU_READ(s,q);EE_ROT_VU_WRITE(d,q);}

static void vuMula(unsigned s,unsigned t,unsigned c){uint32_t x[4],y[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++){uint64_t v=EE_ROT_VU_MUL(x[k],y[c]);a[k]=(uint32_t)v;o[k]=(uint32_t)(v>>32)&1u;}EE_ROT_ACC_WRITE(a,o);}

static void vuMadda(unsigned s,unsigned t,unsigned c){uint32_t x[4],y[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++){uint64_t v=EE_ROT_VU_MAC(a[k],x[k],y[c],o[k],0);a[k]=(uint32_t)v;o[k]=(uint32_t)(v>>32)&1u;}EE_ROT_ACC_WRITE(a,o);}

static void vuMadd(unsigned d,unsigned s,unsigned t,unsigned c){uint32_t x[4],y[4],z[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++)z[k]=(uint32_t)EE_ROT_VU_MAC(a[k],x[k],y[c],o[k],0);EE_ROT_VU_WRITE(d,z);}

static void body_00100418(void);
static void body_001b1740(void);
static void body_001c6018(void);
static void body_001c6098(void);
static void body_001c60e0(void);
static void body_001c6128(void);
static void body_001c6b68(void);
static void body_001c6ff8(void);
static void body_001c7080(void);
static void body_001c7088(void);
static void body_001c7288(void);
static void body_001c7408(void);
static void body_001c74e8(void);
static void body_001c7568(void);
static void body_001c7660(void);
static void body_001c76a8(void);
static void body_001c76e0(void);
static void body_001c7828(void);
static void body_001c7890(void);
static void body_001c7a60(void);
static void body_001c7a88(void);
static void body_001c7b30(void);
static void body_001c7b40(void);
static void body_001c7ba8(void);
static void body_001c7c00(void);
static void body_001c7c10(void);
static void body_001c8108(void);
static void body_001c8120(void);
static void body_001c81b8(void);
static void body_001c8230(void);
static void body_001c83b0(void);
static void body_001c83f0(void);
static void body_001c8418(void);
static void body_001c8458(void);
static void body_001c8508(void);
static void body_001c86a0(void);
static void body_001c8730(void);
static void body_001c8758(void);
static void body_001c87c8(void);
static void body_001c8f08(void);
static void body_001c9188(void);
static void body_001c9230(void);
static void body_001c96d8(void);
static void body_001c98c0(void);
static void body_001c9a98(void);
static void body_001c9b58(void);
static void body_001c9c28(void);
static void body_001c9d00(void);
static void body_001c9d60(void);
static void body_001ca9c0(void);
static void body_001ca9c8(void);
static void body_001caa18(void);
static void body_001cabd8(void);
static void body_001cdd78(void);
static void body_001cf178(void);
static void body_001cf1a8(void);
static void body_001cf440(void);
static void body_001cfc58(void);
static void body_001cfc80(void);
static void body_00242ae8(void);
static void body_00242cb0(void);
static void body_00242d50(void);
static void body_00243c28(void);
static void body_00243d28(void);
static void body_00244238(void);
static void body_00244e68(void);
static void body_00244ef8(void);
static void body_00245c90(void);
static void body_00251858(void);
static void body_00251890(void);
static void body_00259a60(void);
static void body_00259c48(void);
static void body_00261758(void);
static void body_00261f90(void);
static void body_00262fb8(void);
static void body_00265868(void);
static void body_002658b8(void);
static void body_00265948(void);
static void body_00267e50(void);
static void body_00267ec8(void);
static void body_00267f18(void);
static void body_0026a448(void);
static void body_0026a4b0(void);
static void body_002aa438(void);
static void body_002acb90(void);
static void body_002acbb8(void);
static void body_002ad130(void);
static void body_002ad1f8(void);
static void body_002ad2b0(void);
static void body_002ad338(void);
static void body_002ad428(void);
static void body_002b6550(void);
static void body_002b66b8(void);
static void body_00100418(void){
nocturneEffectAxisNoteEntry(0x00100418u);
uint64_t incoming=cpu(31);
/* 00100418: jr ra */ {uint64_t target=cpu(31);/* delay 0010041c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffda10)));checkReturn(target,incoming);return;}
}
static void body_001b1740(void){
nocturneEffectAxisNoteEntry(0x001b1740u);
uint64_t incoming=cpu(31);
/* 001b1740: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 001b1744: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001b1748: sll v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)<<4));
/* 001b174c: addiu v0,v0,0xe40 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000e40)));
/* 001b1750: lui a1,0x32 */ set(5,sx(UINT32_C(0x00320000)));
/* 001b1754: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 001b1758: lb a1,0xc5c(a1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000c5c))));
/* 001b175c: beq a1,zero,0x001b1768 */ {int taken=(cpu(5)==cpu(0));/* delay 001b1760 */ sw(ea(2,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(4));if(taken){goto L_001b1768;}}
/* 001b1764: sw zero,0x2c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(0));
L_001b1768:;
/* 001b1768: jr ra */ {uint64_t target=cpu(31);/* delay 001b176c */ checkReturn(target,incoming);return;}
}
static void body_001c6018(void){
nocturneEffectAxisNoteEntry(0x001c6018u);
uint64_t incoming=cpu(31);
/* 001c6018: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c601c: addiu a3,v1,-0x4998 */ set(7,sx((uint32_t)cpu(3)+UINT32_C(0xffffb668)));
/* 001c6020: lw a0,0x1c(a3) */ lw(4,ea(7,(int32_t)UINT32_C(0x0000001c)));
/* 001c6024: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001c6028: lw v1,0x0(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 001c602c: beq v1,zero,0x001c605c */ {int taken=(cpu(3)==cpu(0));/* delay 001c6030 */ set(2,cpu(0));if(taken){goto L_001c605c;}}
/* 001c6034: lw a0,0x1c(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 001c6038: move v0,a2 */ set(2,cpu(6));
/* 001c603c: lw a1,0x18(a2) */ lw(5,ea(6,(int32_t)UINT32_C(0x00000018)));
/* 001c6040: lw v1,0x18(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000018)));
/* 001c6044: sw a0,0x1c(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(4));
/* 001c6048: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 001c604c: sw v1,0x18(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 001c6050: lw a0,0x1c(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 001c6054: lw v1,0x18(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000018)));
/* 001c6058: sw v1,0x18(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
L_001c605c:;
/* 001c605c: jr ra */ {uint64_t target=cpu(31);/* delay 001c6060 */ checkReturn(target,incoming);return;}
}
static void body_001c6098(void){
nocturneEffectAxisNoteEntry(0x001c6098u);
uint64_t incoming=cpu(31);
/* 001c6098: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001c609c: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 001c60a0: addiu a3,v0,0x5b10 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0x00005b10)));
/* 001c60a4: move a2,zero */ set(6,cpu(0));
/* 001c60a8: lhu v1,0x0(a3) */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000000))));
/* 001c60ac: nop  */ 
L_001c60b0:;
/* 001c60b0: addiu a3,a3,0x2 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000002)));
/* 001c60b4: move v0,a2 */ set(2,cpu(6));
/* 001c60b8: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001c60bc: beq v1,a0,0x001c60d8 */ {int taken=(cpu(3)==cpu(4));/* delay 001c60c0 */ set(5,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x000001a0));if(taken){goto L_001c60d8;}}
/* 001c60c4: nop  */ 
/* 001c60c8: nop  */ 
/* 001c60cc: bnel a1,zero,0x001c60b0 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 001c60d0 */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000000))));goto L_001c60b0;}}
/* 001c60d4: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
L_001c60d8:;
/* 001c60d8: jr ra */ {uint64_t target=cpu(31);/* delay 001c60dc */ checkReturn(target,incoming);return;}
}
static void body_001c60e0(void){
nocturneEffectAxisNoteEntry(0x001c60e0u);
uint64_t incoming=cpu(31);
/* 001c60e0: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001c60e4: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 001c60e8: addiu a3,v0,0x5e50 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0x00005e50)));
/* 001c60ec: move a2,zero */ set(6,cpu(0));
/* 001c60f0: lhu v1,0x0(a3) */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000000))));
/* 001c60f4: nop  */ 
L_001c60f8:;
/* 001c60f8: addiu a3,a3,0x2 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000002)));
/* 001c60fc: move v0,a2 */ set(2,cpu(6));
/* 001c6100: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001c6104: beq v1,a0,0x001c6120 */ {int taken=(cpu(3)==cpu(4));/* delay 001c6108 */ set(5,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000108));if(taken){goto L_001c6120;}}
/* 001c610c: nop  */ 
/* 001c6110: nop  */ 
/* 001c6114: bnel a1,zero,0x001c60f8 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 001c6118 */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000000))));goto L_001c60f8;}}
/* 001c611c: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
L_001c6120:;
/* 001c6120: jr ra */ {uint64_t target=cpu(31);/* delay 001c6124 */ checkReturn(target,incoming);return;}
}
static void body_001c6128(void){
nocturneEffectAxisNoteEntry(0x001c6128u);
uint64_t incoming=cpu(31);
/* 001c6128: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 001c612c: ori v0,zero,0x85ec */ set(2,cpu(0)|UINT32_C(0x000085ec));
/* 001c6130: beq a0,v0,0x001c6158 */ {int taken=(cpu(4)==cpu(2));/* delay 001c6134 */ set(3,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000002f));if(taken){goto L_001c6158;}}
/* 001c6138: bne v1,zero,0x001c6158 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c613c */ if(taken){goto L_001c6158;}}
/* 001c6140: ori v0,zero,0xffc6 */ set(2,cpu(0)|UINT32_C(0x0000ffc6));
/* 001c6144: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c6148: andi v0,v0,0xffff */ set(2,cpu(2)&UINT32_C(0x0000ffff));
/* 001c614c: sltiu v0,v0,0x7 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000007));
/* 001c6150: beql v0,zero,0x001c6158 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c6154 */ sh(ea(28,(int32_t)UINT32_C(0xffffa890)),(uint16_t)cpu(4));goto L_001c6158;}}
L_001c6158:;
/* 001c6158: jr ra */ {uint64_t target=cpu(31);/* delay 001c615c */ checkReturn(target,incoming);return;}
}
static void body_001c6b68(void){
nocturneEffectAxisNoteEntry(0x001c6b68u);
uint64_t incoming=cpu(31);
/* 001c6b68: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c6b6c: move t0,a1 */ set(8,cpu(5));
/* 001c6b70: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c6b74: move s0,a2 */ set(16,cpu(6));
/* 001c6b78: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c6b7c: andi s1,a0,0xff */ set(17,cpu(4)&UINT32_C(0x000000ff));
/* 001c6b80: bne t0,zero,0x001c6b9c */ {int taken=(cpu(8)!=cpu(0));/* delay 001c6b84 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_001c6b9c;}}
/* 001c6b88: beq s0,zero,0x001c6ba0 */ {int taken=(cpu(16)==cpu(0));/* delay 001c6b8c */ set(2,sx((uint32_t)cpu(17)<<3));if(taken){goto L_001c6ba0;}}
/* 001c6b90: jal 0x002a9688 */ set(31,0x001c6b98u);/* delay 001c6b94 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002a9688u);
/* 001c6b98: move t0,v0 */ set(8,cpu(2));
L_001c6b9c:;
/* 001c6b9c: sll v0,s1,0x3 */ set(2,sx((uint32_t)cpu(17)<<3));
L_001c6ba0:;
/* 001c6ba0: lw a0,0x0(t0) */ lw(4,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 001c6ba4: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 001c6ba8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c6bac: lui a2,0x57 */ set(6,sx(UINT32_C(0x00570000)));
/* 001c6bb0: addiu a2,a2,-0x45d0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffba30)));
/* 001c6bb4: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001c6bb8: sw s0,0x0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 001c6bbc: sw t0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(8));
/* 001c6bc0: lbu v0,0xa(t0) */ set(2,byte(ea(8,(int32_t)UINT32_C(0x0000000a))));
/* 001c6bc4: lbu v1,0x16(t0) */ set(3,byte(ea(8,(int32_t)UINT32_C(0x00000016))));
/* 001c6bc8: sll v0,v0,0x6 */ set(2,sx((uint32_t)cpu(2)<<6));
/* 001c6bcc: beq v1,zero,0x001c6c10 */ {int taken=(cpu(3)==cpu(0));/* delay 001c6bd0 */ set(7,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));if(taken){goto L_001c6c10;}}
/* 001c6bd4: addu v0,t0,a3 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(7)));
/* 001c6bd8: lw a0,0x0(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001c6bdc: addiu v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c6be0: sw v1,0x10(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 001c6be4: addiu a1,a0,0x4 */ set(5,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 001c6be8: sw a0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 001c6bec: addu a3,a3,a1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(5)));
/* 001c6bf0: addu v0,t0,a3 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(7)));
/* 001c6bf4: lw a0,0x0(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001c6bf8: addiu v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c6bfc: sw v0,0x14(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c6c00: addiu v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 001c6c04: sw a0,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
/* 001c6c08: b 0x001c6c20 */ /* delay 001c6c0c */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(3)));goto L_001c6c20;
L_001c6c10:;
/* 001c6c10: sw zero,0x10(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 001c6c14: sw zero,0x14(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 001c6c18: sw zero,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001c6c1c: sw zero,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
L_001c6c20:;
/* 001c6c20: lw v0,0x4(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 001c6c24: addu a0,t0,a3 */ set(4,sx((uint32_t)cpu(8)+(uint32_t)cpu(7)));
/* 001c6c28: sw a0,0x18(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(4));
/* 001c6c2c: lhu v1,0xe(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x0000000e))));
/* 001c6c30: lw a1,0x18(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 001c6c34: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001c6c38: addu a3,a3,v1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(3)));
/* 001c6c3c: addu a0,t0,a1 */ set(4,sx((uint32_t)cpu(8)+(uint32_t)cpu(5)));
/* 001c6c40: addu v0,t0,a3 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(7)));
/* 001c6c44: beq a1,zero,0x001c6c58 */ {int taken=(cpu(5)==cpu(0));/* delay 001c6c48 */ sw(ea(6,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));if(taken){goto L_001c6c58;}}
/* 001c6c4c: b 0x001c6c5c */ /* delay 001c6c50 */ sw(ea(6,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(4));goto L_001c6c5c;
L_001c6c58:;
/* 001c6c58: sw zero,0x20(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
L_001c6c5c:;
/* 001c6c5c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c6c60: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c6c64: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c6c68: jr ra */ {uint64_t target=cpu(31);/* delay 001c6c6c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c6ff8(void){
nocturneEffectAxisNoteEntry(0x001c6ff8u);
uint64_t incoming=cpu(31);
/* 001c6ff8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c6ffc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7000: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7004: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7008: jal 0x00100418 */ set(31,0x001c7010u);/* delay 001c700c */ set(17,cpu(4));body_00100418();
/* 001c7010: andi s0,v0,0xff */ set(16,cpu(2)&UINT32_C(0x000000ff));
/* 001c7014: move a1,s1 */ set(5,cpu(17));
/* 001c7018: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001c701c: move a2,zero */ set(6,cpu(0));
/* 001c7020: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c7024: addiu at,at,-0x443c */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffbbc4)));
/* 001c7028: addu s0,at,s0 */ set(16,sx((uint32_t)cpu(1)+(uint32_t)cpu(16)));
/* 001c702c: jal 0x001c8120 */ set(31,0x001c7034u);/* delay 001c7030 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));body_001c8120();
/* 001c7034: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001c7038: move v0,zero */ set(2,cpu(0));
/* 001c703c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7040: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7044: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7048: jr ra */ {uint64_t target=cpu(31);/* delay 001c704c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c7080(void){
nocturneEffectAxisNoteEntry(0x001c7080u);
uint64_t incoming=cpu(31);
/* 001c7080: jr ra */ {uint64_t target=cpu(31);/* delay 001c7084 */ set(2,sx(UINT32_C(0x00000018)));checkReturn(target,incoming);return;}
}
static void body_001c7088(void){
nocturneEffectAxisNoteEntry(0x001c7088u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001c7088: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c708c: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 001c7090: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7094: move s0,a0 */ set(16,cpu(4));
/* 001c7098: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c709c: move s1,a1 */ set(17,cpu(5));
/* 001c70a0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c70a4: move s2,zero */ set(18,cpu(0));
/* 001c70a8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c70ac: swc1 f20,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 001c70b0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c70b4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001c70b8: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 001c70bc: lbu a0,0x15(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000015))));
/* 001c70c0: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c70c4: slti v1,a0,0x2 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c70c8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c70cc: xori v1,v1,0x0 */ set(3,cpu(3)^UINT32_C(0x00000000));
/* 001c70d0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c70d4: lui s3,0x57 */ set(19,sx(UINT32_C(0x00570000)));
/* 001c70d8: addiu s3,s3,-0x45d0 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffba30)));
/* 001c70dc: addu s3,s3,v0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(2)));
/* 001c70e0: jal 0x001c83b0 */ set(31,0x001c70e8u);/* delay 001c70e4 */ if(cpu(3)!=0){set(18,cpu(6));}body_001c83b0();
/* 001c70e8: sb v0,0x18(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(2));
/* 001c70ec: jal 0x001c8418 */ set(31,0x001c70f4u);/* delay 001c70f0 */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000015))));body_001c8418();
/* 001c70f4: lbu v1,0x15(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000015))));
/* 001c70f8: sb v0,0x19(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000019)),(uint8_t)cpu(2));
/* 001c70fc: sltiu a0,v1,0x2 */ set(4,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c7100: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001c7104: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c7108: lbu v0,0x6060(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0x00006060))));
/* 001c710c: sll a1,v0,0x18 */ set(5,sx((uint32_t)cpu(2)<<24));
/* 001c7110: sra v1,a1,0x18 */ set(3,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c7114: beq a0,zero,0x001c7140 */ {int taken=(cpu(4)==cpu(0));/* delay 001c7118 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));if(taken){goto L_001c7140;}}
/* 001c711c: lbu v0,0x18(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000018))));
/* 001c7120: li s2,0x1 */ set(18,sx(UINT32_C(0x00000001)));
/* 001c7124: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 001c7128: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 001c712c: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 001c7130: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 001c7134: nop  */ 
/* 001c7138: nop  */ 
/* 001c713c: div.S f20,f0,f1 */ f[20]=EE_FPU_DIV_S(f[0],f[1]);
L_001c7140:;
/* 001c7140: lbu a0,0x17(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000017))));
/* 001c7144: beq s2,zero,0x001c7168 */ {int taken=(cpu(18)==cpu(0));/* delay 001c7148 */ set(2,cpu(4)&UINT32_C(0x00000002));if(taken){goto L_001c7168;}}
/* 001c714c: lhu v1,0x0(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 001c7150: sltiu v0,v1,0x80 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001c7154: beq v0,zero,0x001c7170 */ {int taken=(cpu(2)==cpu(0));/* delay 001c7158 */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_001c7170;}}
/* 001c715c: sra v0,a1,0x19 */ set(2,sx((uint32_t)((int32_t)cpu(5)>>25)));
/* 001c7160: b 0x001c716c */ /* delay 001c7164 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));goto L_001c716c;
L_001c7168:;
/* 001c7168: lhu v1,0x0(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000000))));
L_001c716c:;
/* 001c716c: li v0,0x20 */ set(2,sx(UINT32_C(0x00000020)));
L_001c7170:;
/* 001c7170: bne v1,v0,0x001c71a8 */ {int taken=(cpu(3)!=cpu(2));/* delay 001c7174 */ set(2,sx(UINT32_C(0x000002c1)));if(taken){goto L_001c71a8;}}
/* 001c7178: lbu v1,0x15(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000015))));
/* 001c717c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c7180: beql v1,v0,0x001c7194 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 001c7184 */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));goto L_001c7194;}}
/* 001c7188: bne v1,zero,0x001c71a8 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c718c */ set(2,sx(UINT32_C(0x000002c1)));if(taken){goto L_001c71a8;}}
/* 001c7190: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
L_001c7194:;
/* 001c7194: lw v1,-0x4d5c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb2a4)));
/* 001c7198: sra v0,v0,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 001c719c: addu v1,v0,v1 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c71a0: b 0x001c7268 */ /* delay 001c71a4 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));goto L_001c7268;
L_001c71a8:;
/* 001c71a8: bne s1,v0,0x001c71c0 */ {int taken=(cpu(17)!=cpu(2));/* delay 001c71ac */ set(2,cpu(4)&UINT32_C(0x00000001));if(taken){goto L_001c71c0;}}
/* 001c71b0: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001c71b4: addiu v0,v0,-0x7 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffff9)));
/* 001c71b8: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001c71bc: andi v0,a0,0x1 */ set(2,cpu(4)&UINT32_C(0x00000001));
L_001c71c0:;
/* 001c71c0: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 001c71c4: beql v0,zero,0x001c726c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c71c8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001c726c;}}
/* 001c71cc: lw v0,0x4(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 001c71d0: lbu v1,0x16(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000016))));
/* 001c71d4: beq v1,zero,0x001c7268 */ {int taken=(cpu(3)==cpu(0));/* delay 001c71d8 */ set(17,sx((uint32_t)cpu(17)<<1));if(taken){goto L_001c7268;}}
/* 001c71dc: lw v0,0x8(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 001c71e0: slt v0,s1,v0 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(2));
/* 001c71e4: beql v0,zero,0x001c726c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c71e8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001c726c;}}
/* 001c71ec: lw v0,0x10(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 001c71f0: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 001c71f4: lb a0,0x1(v0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000001))));
/* 001c71f8: beq a0,zero,0x001c7268 */ {int taken=(cpu(4)==cpu(0));/* delay 001c71fc */ set(3,sx((uint32_t)((int32_t)cpu(17)>>1)));if(taken){goto L_001c7268;}}
/* 001c7200: lb v0,0x0(v0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c7204: lui at,0x4180 */ set(1,sx(UINT32_C(0x41800000)));
/* 001c7208: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 001c720c: addiu a1,v1,0x20 */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001c7210: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 001c7214: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 001c7218: subu v0,a0,v0 */ set(2,sx((uint32_t)cpu(4)-(uint32_t)cpu(2)));
/* 001c721c: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 001c7220: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 001c7224: li v1,0x21 */ set(3,sx(UINT32_C(0x00000021)));
/* 001c7228: mul.S f1,f1,f2 */ f[1]=EE_FPU_MUL_S(f[1],f[2]);
/* 001c722c: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 001c7230: mul.S f1,f1,f20 */ f[1]=EE_FPU_MUL_S(f[1],f[20]);
/* 001c7234: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 001c7238: mfc1 a2,f2 */ set(6,sx(f[2]));
/* 001c723c: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 001c7240: mfc1 a0,f0 */ set(4,sx(f[0]));
/* 001c7244: beq a1,v1,0x001c7254 */ {int taken=(cpu(5)==cpu(3));/* delay 001c7248 */ set(2,sx(UINT32_C(0x00000031)));if(taken){goto L_001c7254;}}
/* 001c724c: bne a1,v0,0x001c7260 */ {int taken=(cpu(5)!=cpu(2));/* delay 001c7250 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));if(taken){goto L_001c7260;}}
L_001c7254:;
/* 001c7254: addiu a0,a0,-0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffe0)));
/* 001c7258: addiu a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000004)));
/* 001c725c: subu v0,zero,a0 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
L_001c7260:;
/* 001c7260: sw a2,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(6));
/* 001c7264: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_001c7268:;
/* 001c7268: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001c726c:;
/* 001c726c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7270: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7274: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7278: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c727c: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7280: jr ra */ {uint64_t target=cpu(31);/* delay 001c7284 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c7288(void){
nocturneEffectAxisNoteEntry(0x001c7288u);
uint64_t incoming=cpu(31);
/* 001c7288: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c728c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7290: move s2,a1 */ set(18,cpu(5));
/* 001c7294: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7298: move s4,a0 */ set(20,cpu(4));
/* 001c729c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c72a0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c72a4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c72a8: bne s2,zero,0x001c72e0 */ {int taken=(cpu(18)!=cpu(0));/* delay 001c72ac */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_001c72e0;}}
/* 001c72b0: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
/* 001c72b4: addiu s0,s1,-0x45d0 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0xffffba30)));
/* 001c72b8: jal 0x001cabd8 */ set(31,0x001c72c0u);/* delay 001c72bc */ lw(4,ea(16,(int32_t)UINT32_C(0x00000154)));body_001cabd8();
/* 001c72c0: move s2,v0 */ set(18,cpu(2));
/* 001c72c4: lw v0,0x14c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000014c)));
/* 001c72c8: move a0,s2 */ set(4,cpu(18));
/* 001c72cc: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c72d0: jal 0x001c76a8 */ set(31,0x001c72d8u);/* delay 001c72d4 */ sw(ea(16,(int32_t)UINT32_C(0x0000014c)),(uint32_t)cpu(2));body_001c76a8();
/* 001c72d8: b 0x001c72e8 */ /* delay 001c72dc */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0xffffba30)));goto L_001c72e8;
L_001c72e0:;
/* 001c72e0: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
/* 001c72e4: addiu s0,s1,-0x45d0 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0xffffba30)));
L_001c72e8:;
/* 001c72e8: jal 0x001cabd8 */ set(31,0x001c72f0u);/* delay 001c72ec */ lw(4,ea(16,(int32_t)UINT32_C(0x00000150)));body_001cabd8();
/* 001c72f0: lw s3,0x20(s2) */ lw(19,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 001c72f4: move s1,v0 */ set(17,cpu(2));
/* 001c72f8: lw v0,0x148(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000148)));
/* 001c72fc: lui t0,0xa09d */ set(8,sx(UINT32_C(0xa09d0000)));
/* 001c7300: move a0,s1 */ set(4,cpu(17));
/* 001c7304: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c7308: move a1,zero */ set(5,cpu(0));
/* 001c730c: sw v0,0x148(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000148)),(uint32_t)cpu(2));
/* 001c7310: move a2,zero */ set(6,cpu(0));
/* 001c7314: move a3,zero */ set(7,cpu(0));
/* 001c7318: ori t0,t0,0xc300 */ set(8,cpu(8)|UINT32_C(0x0000c300));
/* 001c731c: jal 0x001c7660 */ set(31,0x001c7324u);/* delay 001c7320 */ set(9,cpu(0));body_001c7660();
/* 001c7324: bne s3,zero,0x001c7338 */ {int taken=(cpu(19)!=cpu(0));/* delay 001c7328 */ set(4,cpu(0));if(taken){goto L_001c7338;}}
/* 001c732c: b 0x001c733c */ /* delay 001c7330 */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(17));goto L_001c733c;
L_001c7338:;
/* 001c7338: sw s1,0x28(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(17));
L_001c733c:;
/* 001c733c: sw s4,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(20));
/* 001c7340: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001c7344: lb v1,0x6060(v0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00006060))));
/* 001c7348: jal 0x001c83b0 */ set(31,0x001c7350u);/* delay 001c734c */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));body_001c83b0();
/* 001c7350: move a0,zero */ set(4,cpu(0));
/* 001c7354: jal 0x001c8418 */ set(31,0x001c735cu);/* delay 001c7358 */ sb(ea(17,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(2));body_001c8418();
/* 001c735c: sw s3,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(19));
/* 001c7360: sb v0,0x19(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000019)),(uint8_t)cpu(2));
/* 001c7364: move v0,s2 */ set(2,cpu(18));
/* 001c7368: sw s1,0x20(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(17));
/* 001c736c: lw v1,0x18(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 001c7370: lw a1,0xc(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 001c7374: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001c7378: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c737c: sw v1,0x18(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 001c7380: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7384: lw a0,0xc(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 001c7388: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c738c: addu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 001c7390: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7394: sw a1,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(5));
/* 001c7398: lbu v1,0x18(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000018))));
/* 001c739c: sh v1,0x10(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000010)),(uint16_t)cpu(3));
/* 001c73a0: lbu a0,0x19(s1) */ set(4,byte(ea(17,(int32_t)UINT32_C(0x00000019))));
/* 001c73a4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c73a8: sh a0,0x12(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000012)),(uint16_t)cpu(4));
/* 001c73ac: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c73b0: jr ra */ {uint64_t target=cpu(31);/* delay 001c73b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c7408(void){
nocturneEffectAxisNoteEntry(0x001c7408u);
uint64_t incoming=cpu(31);
/* 001c7408: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001c740c: sd s0,0x30(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7410: sll s0,a3,0x18 */ set(16,sx((uint32_t)cpu(7)<<24));
/* 001c7414: sd s1,0x38(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7418: sra s0,s0,0x18 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>24)));
/* 001c741c: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c7420: move s2,a2 */ set(18,cpu(6));
/* 001c7424: sd s3,0x48(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c7428: move s3,a0 */ set(19,cpu(4));
/* 001c742c: sd s4,0x50(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c7430: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c7434: jal 0x001c6018 */ set(31,0x001c743cu);/* delay 001c7438 */ set(20,cpu(5));body_001c6018();
/* 001c743c: lw a0,0x4(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 001c7440: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c7444: addiu a2,v1,-0x45d0 */ set(6,sx((uint32_t)cpu(3)+UINT32_C(0xffffba30)));
/* 001c7448: lw s1,0x14(v0) */ lw(17,ea(2,(int32_t)UINT32_C(0x00000014)));
/* 001c744c: sra a0,a0,0x4 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>4)));
/* 001c7450: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001c7454: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001c7458: addiu a0,sp,0x10 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 001c745c: sh a1,0x4(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(5));
/* 001c7460: lw v1,0x8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 001c7464: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001c7468: sra v1,v1,0x4 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>4)));
/* 001c746c: bne s0,zero,0x001c7480 */ {int taken=(cpu(16)!=cpu(0));/* delay 001c7470 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));if(taken){goto L_001c7480;}}
/* 001c7474: b 0x001c7488 */ /* delay 001c7478 */ sb(ea(29,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(0));goto L_001c7488;
L_001c7480:;
/* 001c7480: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 001c7484: sb v0,0x18(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(2));
L_001c7488:;
/* 001c7488: lw v1,0x170(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000170)));
/* 001c748c: li v0,0x14 */ set(2,sx(UINT32_C(0x00000014)));
/* 001c7490: lhu a1,0x160(a2) */ set(5,half(ea(6,(int32_t)UINT32_C(0x00000160))));
/* 001c7494: lhu a3,0x0(sp) */ set(7,half(ea(29,(int32_t)UINT32_C(0x00000000))));
/* 001c7498: sll v1,v1,0x6 */ set(3,sx((uint32_t)cpu(3)<<6));
/* 001c749c: lhu a2,0x4(sp) */ set(6,half(ea(29,(int32_t)UINT32_C(0x00000004))));
/* 001c74a0: sw s2,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 001c74a4: sb v0,0x19(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000019)),(uint8_t)cpu(2));
/* 001c74a8: sh s3,0x24(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000024)),(uint16_t)cpu(19));
/* 001c74ac: sh s4,0x26(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000026)),(uint16_t)cpu(20));
/* 001c74b0: sh a1,0x1a(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000001a)),(uint16_t)cpu(5));
/* 001c74b4: sw v1,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(3));
/* 001c74b8: sh a3,0x20(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000020)),(uint16_t)cpu(7));
/* 001c74bc: jal 0x002aa9e0 */ set(31,0x001c74c4u);/* delay 001c74c0 */ sh(ea(29,(int32_t)UINT32_C(0x00000022)),(uint16_t)cpu(6));nocturneBattleActionSkillCall(0x002aa9e0u);
/* 001c74c4: ld s0,0x30(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c74c8: move v0,s1 */ set(2,cpu(17));
/* 001c74cc: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c74d0: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c74d4: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c74d8: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c74dc: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c74e0: jr ra */ {uint64_t target=cpu(31);/* delay 001c74e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_001c74e8(void){
nocturneEffectAxisNoteEntry(0x001c74e8u);
uint64_t incoming=cpu(31);
/* 001c74e8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c74ec: andi v0,a0,0xff */ set(2,cpu(4)&UINT32_C(0x000000ff));
/* 001c74f0: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c74f4: sll s0,v0,0x3 */ set(16,sx((uint32_t)cpu(2)<<3));
/* 001c74f8: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001c74fc: li a0,0x120 */ set(4,sx(UINT32_C(0x00000120)));
/* 001c7500: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001c7504: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7508: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c750c: addiu at,at,-0x45d0 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffba30)));
/* 001c7510: addu s0,at,s0 */ set(16,sx((uint32_t)cpu(1)+(uint32_t)cpu(16)));
/* 001c7514: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7518: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c751c: jal 0x002a8af8 */ set(31,0x001c7524u);/* delay 001c7520 */ set(18,cpu(5));nocturneBattleActionSkillCall(0x002a8af8u);
/* 001c7524: lw a0,0x1c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001c7528: move a1,sp */ set(5,cpu(29));
/* 001c752c: jal 0x001ca9c8 */ set(31,0x001c7534u);/* delay 001c7530 */ set(17,cpu(2));body_001ca9c8();
/* 001c7534: move a0,s1 */ set(4,cpu(17));
/* 001c7538: lw a2,0x1c(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001c753c: move a1,s2 */ set(5,cpu(18));
/* 001c7540: jal 0x001caa18 */ set(31,0x001c7548u);/* delay 001c7544 */ set(7,cpu(29));body_001caa18();
/* 001c7548: move v0,s1 */ set(2,cpu(17));
/* 001c754c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7550: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7554: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7558: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c755c: jr ra */ {uint64_t target=cpu(31);/* delay 001c7560 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c7568(void){
nocturneEffectAxisNoteEntry(0x001c7568u);
uint64_t incoming=cpu(31);
/* 001c7568: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c756c: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c7570: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7574: move s2,a0 */ set(18,cpu(4));
/* 001c7578: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c757c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7580: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7584: addiu s5,v1,-0x45d0 */ set(21,sx((uint32_t)cpu(3)+UINT32_C(0xffffba30)));
/* 001c7588: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c758c: move s6,a1 */ set(22,cpu(5));
/* 001c7590: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7594: sll s4,s6,0x2 */ set(20,sx((uint32_t)cpu(22)<<2));
/* 001c7598: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c759c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c75a0: lbu v0,0x15(s2) */ set(2,byte(ea(18,(int32_t)UINT32_C(0x00000015))));
/* 001c75a4: sll v1,v0,0x3 */ set(3,sx((uint32_t)cpu(2)<<3));
/* 001c75a8: move a0,v0 */ set(4,cpu(2));
/* 001c75ac: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c75b0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001c75b4: addu s3,v1,s5 */ set(19,sx((uint32_t)cpu(3)+(uint32_t)cpu(21)));
/* 001c75b8: lw v0,0x18(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000018)));
/* 001c75bc: addu v0,s4,v0 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 001c75c0: lw a2,0x0(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001c75c4: beq a2,zero,0x001c75e0 */ {int taken=(cpu(6)==cpu(0));/* delay 001c75c8 */ set(2,cpu(6));if(taken){goto L_001c75e0;}}
/* 001c75cc: lhu v1,0x4(a2) */ set(3,half(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 001c75d0: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001c75d4: b 0x001c7634 */ /* delay 001c75d8 */ sh(ea(6,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));goto L_001c7634;
L_001c75e0:;
/* 001c75e0: jal 0x001c74e8 */ set(31,0x001c75e8u);/* delay 001c75e4 */ body_001c74e8();
/* 001c75e8: lbu a0,0x15(s2) */ set(4,byte(ea(18,(int32_t)UINT32_C(0x00000015))));
/* 001c75ec: jal 0x001c83f0 */ set(31,0x001c75f4u);/* delay 001c75f0 */ set(17,cpu(2));body_001c83f0();
/* 001c75f4: lbu a0,0x15(s2) */ set(4,byte(ea(18,(int32_t)UINT32_C(0x00000015))));
/* 001c75f8: jal 0x001c8458 */ set(31,0x001c7600u);/* delay 001c75fc */ set(16,cpu(2));body_001c8458();
/* 001c7600: move a0,s0 */ set(4,cpu(16));
/* 001c7604: move a2,s1 */ set(6,cpu(17));
/* 001c7608: move a1,v0 */ set(5,cpu(2));
/* 001c760c: jal 0x001c7408 */ set(31,0x001c7614u);/* delay 001c7610 */ set(7,sx(UINT32_C(0x00000001)));body_001c7408();
/* 001c7614: lw v1,0x18(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000018)));
/* 001c7618: lw a0,0x144(s5) */ lw(4,ea(21,(int32_t)UINT32_C(0x00000144)));
/* 001c761c: move a2,v0 */ set(6,cpu(2));
/* 001c7620: addu v1,s4,v1 */ set(3,sx((uint32_t)cpu(20)+(uint32_t)cpu(3)));
/* 001c7624: sh s6,0x0(a2) */ sh(ea(6,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(22));
/* 001c7628: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 001c762c: sw a2,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
/* 001c7630: sw a0,0x144(s5) */ sw(ea(21,(int32_t)UINT32_C(0x00000144)),(uint32_t)cpu(4));
L_001c7634:;
/* 001c7634: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7638: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c763c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7640: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7644: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7648: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c764c: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7650: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7654: jr ra */ {uint64_t target=cpu(31);/* delay 001c7658 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c7660(void){
nocturneEffectAxisNoteEntry(0x001c7660u);
uint64_t incoming=cpu(31);
/* 001c7660: sb a2,0x15(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000015)),(uint8_t)cpu(6));
/* 001c7664: li v0,-0x100 */ set(2,sx(UINT32_C(0xffffff00)));
/* 001c7668: sb a3,0x14(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(7));
/* 001c766c: and t0,t0,v0 */ set(8,cpu(8)&cpu(2));
/* 001c7670: sb t1,0x16(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000016)),(uint8_t)cpu(9));
/* 001c7674: sh a1,0x0(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(5));
/* 001c7678: lbu v0,-0x4d54(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));
/* 001c767c: sw t0,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(8));
/* 001c7680: sb v0,0x17(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000017)),(uint8_t)cpu(2));
/* 001c7684: sw zero,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 001c7688: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001c768c: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001c7690: sw zero,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 001c7694: sh zero,0x2(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(0));
/* 001c7698: sw zero,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 001c769c: sw zero,0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 001c76a0: jr ra */ {uint64_t target=cpu(31);/* delay 001c76a4 */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_001c76a8(void){
nocturneEffectAxisNoteEntry(0x001c76a8u);
uint64_t incoming=cpu(31);
/* 001c76a8: li v0,-0x80 */ set(2,sx(UINT32_C(0xffffff80)));
/* 001c76ac: sw zero,0x18(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 001c76b0: sb v0,0x0(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001c76b4: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001c76b8: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001c76bc: sb zero,0x1(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));
/* 001c76c0: sw zero,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 001c76c4: sw zero,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 001c76c8: sw zero,0x24(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 001c76cc: sw zero,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 001c76d0: sw a0,0x2c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(4));
/* 001c76d4: sw zero,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 001c76d8: jr ra */ {uint64_t target=cpu(31);/* delay 001c76dc */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_001c76e0(void){
nocturneEffectAxisNoteEntry(0x001c76e0u);
uint64_t incoming=cpu(31);
/* 001c76e0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c76e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c76e8: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 001c76ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c76f0: andi s1,a2,0xff */ set(17,cpu(6)&UINT32_C(0x000000ff));
/* 001c76f4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c76f8: andi s2,a3,0xff */ set(18,cpu(7)&UINT32_C(0x000000ff));
/* 001c76fc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7700: andi s3,a0,0xffff */ set(19,cpu(4)&UINT32_C(0x0000ffff));
/* 001c7704: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7708: addiu s0,s0,-0x45d0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffba30)));
/* 001c770c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7710: andi s5,a1,0xff */ set(21,cpu(5)&UINT32_C(0x000000ff));
/* 001c7714: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7718: move s6,t0 */ set(22,cpu(8));
/* 001c771c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7720: jal 0x001cabd8 */ set(31,0x001c7728u);/* delay 001c7724 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000150)));body_001cabd8();
/* 001c7728: lui t0,0xa09d */ set(8,sx(UINT32_C(0xa09d0000)));
/* 001c772c: move s4,v0 */ set(20,cpu(2));
/* 001c7730: lw v0,0x148(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000148)));
/* 001c7734: move a1,s3 */ set(5,cpu(19));
/* 001c7738: move a0,s4 */ set(4,cpu(20));
/* 001c773c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c7740: move a3,s1 */ set(7,cpu(17));
/* 001c7744: sw v0,0x148(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000148)),(uint32_t)cpu(2));
/* 001c7748: move s0,zero */ set(16,cpu(0));
/* 001c774c: move t1,s2 */ set(9,cpu(18));
/* 001c7750: move a2,s5 */ set(6,cpu(21));
/* 001c7754: jal 0x001c7660 */ set(31,0x001c775cu);/* delay 001c7758 */ set(8,cpu(8)|UINT32_C(0x0000c300));body_001c7660();
/* 001c775c: move a0,s4 */ set(4,cpu(20));
/* 001c7760: lhu v1,0x0(s4) */ set(3,half(ea(20,(int32_t)UINT32_C(0x00000000))));
/* 001c7764: sltiu v0,v1,0x20 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 001c7768: bne v0,zero,0x001c77b4 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c776c */ set(5,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));if(taken){goto L_001c77b4;}}
/* 001c7770: beql a1,zero,0x001c7798 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 001c7774 */ set(2,half(ea(20,(int32_t)UINT32_C(0x00000000))));goto L_001c7798;}}
/* 001c7778: li v0,0x5e */ set(2,sx(UINT32_C(0x0000005e)));
/* 001c777c: bnel v1,v0,0x001c7790 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 001c7780 */ set(2,half(ea(20,(int32_t)UINT32_C(0x00000000))));goto L_001c7790;}}
/* 001c7784: li v0,0x26 */ set(2,sx(UINT32_C(0x00000026)));
/* 001c7788: sh v0,0x0(s4) */ sh(ea(20,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));
/* 001c778c: lhu v0,0x0(s4) */ set(2,half(ea(20,(int32_t)UINT32_C(0x00000000))));
L_001c7790:;
/* 001c7790: b 0x001c77b4 */ /* delay 001c7794 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffe0)));goto L_001c77b4;
L_001c7798:;
/* 001c7798: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 001c779c: ori v1,v1,0x7f80 */ set(3,cpu(3)|UINT32_C(0x00007f80));
/* 001c77a0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c77a4: andi a1,v0,0xff00 */ set(5,cpu(2)&UINT32_C(0x0000ff00));
/* 001c77a8: andi v0,v0,0x7f */ set(2,cpu(2)&UINT32_C(0x0000007f));
/* 001c77ac: sra a1,a1,0x1 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>1)));
/* 001c77b0: addu s0,a1,v0 */ set(16,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
L_001c77b4:;
/* 001c77b4: jal 0x001c7568 */ set(31,0x001c77bcu);/* delay 001c77b8 */ set(5,cpu(16));body_001c7568();
/* 001c77bc: move a0,s4 */ set(4,cpu(20));
/* 001c77c0: sw v0,0x1c(s4) */ sw(ea(20,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 001c77c4: move a1,s0 */ set(5,cpu(16));
/* 001c77c8: jal 0x001c7088 */ set(31,0x001c77d0u);/* delay 001c77cc */ set(6,cpu(22));body_001c7088();
/* 001c77d0: sll a0,s5,0x18 */ set(4,sx((uint32_t)cpu(21)<<24));
/* 001c77d4: lbu v0,0x17(s4) */ set(2,byte(ea(20,(int32_t)UINT32_C(0x00000017))));
/* 001c77d8: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c77dc: andi v0,v0,0x10 */ set(2,cpu(2)&UINT32_C(0x00000010));
/* 001c77e0: beq v0,zero,0x001c77f8 */ {int taken=(cpu(2)==cpu(0));/* delay 001c77e4 */ set(5,cpu(16));if(taken){goto L_001c77f8;}}
/* 001c77e8: jal 0x001c7080 */ set(31,0x001c77f0u);/* delay 001c77ec */ body_001c7080();
/* 001c77f0: b 0x001c77fc */ /* delay 001c77f4 */ sw(ea(20,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));goto L_001c77fc;
L_001c77f8:;
/* 001c77f8: sw zero,0x8(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
L_001c77fc:;
/* 001c77fc: move v0,s4 */ set(2,cpu(20));
/* 001c7800: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7804: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7808: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c780c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7810: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7814: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7818: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c781c: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7820: jr ra */ {uint64_t target=cpu(31);/* delay 001c7824 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c7828(void){
nocturneEffectAxisNoteEntry(0x001c7828u);
uint64_t incoming=cpu(31);
/* 001c7828: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c782c: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c7830: sll a2,a2,0x18 */ set(6,sx((uint32_t)cpu(6)<<24));
/* 001c7834: sll a3,a3,0x18 */ set(7,sx((uint32_t)cpu(7)<<24));
/* 001c7838: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c783c: move s0,t0 */ set(16,cpu(8));
/* 001c7840: sra a1,a1,0x18 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c7844: sra a2,a2,0x18 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c7848: sra a3,a3,0x18 */ set(7,sx((uint32_t)((int32_t)cpu(7)>>24)));
/* 001c784c: move t0,zero */ set(8,cpu(0));
/* 001c7850: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7854: jal 0x001c7890 */ set(31,0x001c785cu);/* delay 001c7858 */ set(9,cpu(0));body_001c7890();
/* 001c785c: move a0,s0 */ set(4,cpu(16));
/* 001c7860: move v1,v0 */ set(3,cpu(2));
/* 001c7864: move v0,s0 */ set(2,cpu(16));
/* 001c7868: beq v1,zero,0x001c7880 */ {int taken=(cpu(3)==cpu(0));/* delay 001c786c */ set(5,cpu(3));if(taken){goto L_001c7880;}}
/* 001c7870: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7874: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7878: j 0x001c8108 */ /* delay 001c787c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001c8108();return;
L_001c7880:;
/* 001c7880: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7884: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7888: jr ra */ {uint64_t target=cpu(31);/* delay 001c788c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c7890(void){
nocturneEffectAxisNoteEntry(0x001c7890u);
uint64_t incoming=cpu(31);
/* 001c7890: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c7894: sll a3,a3,0x18 */ set(7,sx((uint32_t)cpu(7)<<24));
/* 001c7898: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001c789c: sll a2,a2,0x18 */ set(6,sx((uint32_t)cpu(6)<<24));
/* 001c78a0: sra a3,a3,0x18 */ set(7,sx((uint32_t)((int32_t)cpu(7)>>24)));
/* 001c78a4: sra a1,a1,0x18 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c78a8: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c78ac: move s2,t0 */ set(18,cpu(8));
/* 001c78b0: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c78b4: move s5,a0 */ set(21,cpu(4));
/* 001c78b8: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c78bc: sra s6,a2,0x18 */ set(22,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c78c0: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c78c4: move s8,zero */ set(30,cpu(0));
/* 001c78c8: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c78cc: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c78d0: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c78d4: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c78d8: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c78dc: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c78e0: sw t1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(9));
/* 001c78e4: bltz a1,0x001c78f0 */ {int taken=((int64_t)cpu(5)<0);/* delay 001c78e8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));if(taken){goto L_001c78f0;}}
/* 001c78ec: sb a1,-0x4d4c(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffb2b4)),(uint8_t)cpu(5));
L_001c78f0:;
/* 001c78f0: lbu a1,-0x4d4c(gp) */ set(5,byte(ea(28,(int32_t)UINT32_C(0xffffb2b4))));
/* 001c78f4: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 001c78f8: addiu s0,v0,-0x45d0 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffba30)));
/* 001c78fc: sll v1,a1,0x3 */ set(3,sx((uint32_t)cpu(5)<<3));
/* 001c7900: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 001c7904: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001c7908: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 001c790c: lw a1,0x1c(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x0000001c)));
/* 001c7910: beq a1,zero,0x001c7a2c */ {int taken=(cpu(5)==cpu(0));/* delay 001c7914 */ set(2,cpu(0));if(taken){goto L_001c7a2c;}}
/* 001c7918: beq s5,zero,0x001c792c */ {int taken=(cpu(21)==cpu(0));/* delay 001c791c */ if(taken){goto L_001c792c;}}
/* 001c7920: jal 0x002d5d0c */ set(31,0x001c7928u);/* delay 001c7924 */ nocturneBattleActionSkillCall(0x002d5d0cu);
/* 001c7928: move s8,v0 */ set(30,cpu(2));
L_001c792c:;
/* 001c792c: bnel s2,zero,0x001c7958 */ {int taken=(cpu(18)!=cpu(0));if(taken){/* delay 001c7930 */ lw(20,ea(18,(int32_t)UINT32_C(0x00000020)));goto L_001c7958;}}
/* 001c7934: jal 0x001cabd8 */ set(31,0x001c793cu);/* delay 001c7938 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000154)));body_001cabd8();
/* 001c793c: move s2,v0 */ set(18,cpu(2));
/* 001c7940: lw v0,0x14c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000014c)));
/* 001c7944: move a0,s2 */ set(4,cpu(18));
/* 001c7948: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c794c: jal 0x001c76a8 */ set(31,0x001c7954u);/* delay 001c7950 */ sw(ea(16,(int32_t)UINT32_C(0x0000014c)),(uint32_t)cpu(2));body_001c76a8();
/* 001c7954: lw s4,0x20(s2) */ lw(20,ea(18,(int32_t)UINT32_C(0x00000020)));
L_001c7958:;
/* 001c7958: move s3,zero */ set(19,cpu(0));
/* 001c795c: beq s8,zero,0x001c7a0c */ {int taken=(cpu(30)==cpu(0));/* delay 001c7960 */ set(17,cpu(0));if(taken){goto L_001c7a0c;}}
/* 001c7964: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7968: andi s7,s6,0xff */ set(23,cpu(22)&UINT32_C(0x000000ff));
/* 001c796c: andi s6,v0,0xff */ set(22,cpu(2)&UINT32_C(0x000000ff));
/* 001c7970: addu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));
/* 001c7974: nop  */ 
L_001c7978:;
/* 001c7978: lbu s0,0x0(v0) */ set(16,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c797c: sltiu v0,s0,0x80 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001c7980: bne v0,zero,0x001c7998 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c7984 */ set(4,sx((uint32_t)cpu(16)<<8));if(taken){goto L_001c7998;}}
/* 001c7988: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 001c798c: addu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));
/* 001c7990: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c7994: or s0,v1,a0 */ set(16,cpu(3)|cpu(4));
L_001c7998:;
/* 001c7998: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 001c799c: move a0,s0 */ set(4,cpu(16));
/* 001c79a0: lbu a1,-0x4d4c(gp) */ set(5,byte(ea(28,(int32_t)UINT32_C(0xffffb2b4))));
/* 001c79a4: move a2,s7 */ set(6,cpu(23));
/* 001c79a8: sltu t0,zero,v0 */ set(8,cpu(0)<cpu(2));
/* 001c79ac: move a3,s6 */ set(7,cpu(22));
/* 001c79b0: movn t0,zero,s3 */ if(cpu(19)!=0){set(8,cpu(0));}
/* 001c79b4: jal 0x001c76e0 */ set(31,0x001c79bcu);/* delay 001c79b8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));body_001c76e0();
/* 001c79bc: bne s4,zero,0x001c79d0 */ {int taken=(cpu(20)!=cpu(0));/* delay 001c79c0 */ set(17,cpu(2));if(taken){goto L_001c79d0;}}
/* 001c79c4: b 0x001c79d4 */ /* delay 001c79c8 */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(17));goto L_001c79d4;
L_001c79d0:;
/* 001c79d0: sw s1,0x28(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(17));
L_001c79d4:;
/* 001c79d4: lw a1,0xc(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 001c79d8: move a0,s0 */ set(4,cpu(16));
/* 001c79dc: lw v0,0xc(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 001c79e0: lw v1,0x18(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 001c79e4: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 001c79e8: sw s4,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(20));
/* 001c79ec: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001c79f0: sw v0,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001c79f4: sw v1,0x18(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 001c79f8: jal 0x001c6128 */ set(31,0x001c7a00u);/* delay 001c79fc */ set(20,cpu(17));body_001c6128();
/* 001c7a00: sltu v0,s3,s8 */ set(2,cpu(19)<cpu(30));
/* 001c7a04: bne v0,zero,0x001c7978 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c7a08 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));if(taken){goto L_001c7978;}}
L_001c7a0c:;
/* 001c7a0c: beq s1,zero,0x001c7a2c */ {int taken=(cpu(17)==cpu(0));/* delay 001c7a10 */ set(2,cpu(18));if(taken){goto L_001c7a2c;}}
/* 001c7a14: sw s1,0x20(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(17));
/* 001c7a18: lbu v0,0x18(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000018))));
/* 001c7a1c: sh v0,0x10(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000010)),(uint16_t)cpu(2));
/* 001c7a20: lbu v1,0x19(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000019))));
/* 001c7a24: sh v1,0x12(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000012)),(uint16_t)cpu(3));
/* 001c7a28: move v0,s2 */ set(2,cpu(18));
L_001c7a2c:;
/* 001c7a2c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7a30: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7a34: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7a38: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7a3c: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7a40: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7a44: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c7a48: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c7a4c: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c7a50: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c7a54: jr ra */ {uint64_t target=cpu(31);/* delay 001c7a58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_001c7a60(void){
nocturneEffectAxisNoteEntry(0x001c7a60u);
uint64_t incoming=cpu(31);
/* 001c7a60: andi a1,a1,0xff */ set(5,cpu(5)&UINT32_C(0x000000ff));
/* 001c7a64: sll a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)<<1));
/* 001c7a68: slti v0,a1,0x81 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000081));
/* 001c7a6c: bne v0,zero,0x001c7a80 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c7a70 */ set(2,sx(UINT32_C(0xffffff80)));if(taken){goto L_001c7a80;}}
/* 001c7a74: jr ra */ {uint64_t target=cpu(31);/* delay 001c7a78 */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));checkReturn(target,incoming);return;}
L_001c7a80:;
/* 001c7a80: jr ra */ {uint64_t target=cpu(31);/* delay 001c7a84 */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_001c7a88(void){
nocturneEffectAxisNoteEntry(0x001c7a88u);
uint64_t incoming=cpu(31);
/* 001c7a88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c7a8c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7a90: move s0,a0 */ set(16,cpu(4));
/* 001c7a94: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7a98: jal 0x001c8230 */ set(31,0x001c7aa0u);/* delay 001c7a9c */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(5));body_001c8230();
/* 001c7aa0: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001c7aa4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c7aa8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c7aac: jr ra */ {uint64_t target=cpu(31);/* delay 001c7ab0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c7b30(void){
nocturneEffectAxisNoteEntry(0x001c7b30u);
uint64_t incoming=cpu(31);
/* 001c7b30: sw a2,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 001c7b34: jr ra */ {uint64_t target=cpu(31);/* delay 001c7b38 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_001c7b40(void){
nocturneEffectAxisNoteEntry(0x001c7b40u);
uint64_t incoming=cpu(31);
/* 001c7b40: srl a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)>>4));
/* 001c7b44: jr ra */ {uint64_t target=cpu(31);/* delay 001c7b48 */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_001c7ba8(void){
nocturneEffectAxisNoteEntry(0x001c7ba8u);
uint64_t incoming=cpu(31);
/* 001c7ba8: beq a0,zero,0x001c7bf8 */ {int taken=(cpu(4)==cpu(0));/* delay 001c7bac */ if(taken){goto L_001c7bf8;}}
/* 001c7bb0: lw v0,0x1c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001c7bb4: nop  */ 
L_001c7bb8:;
/* 001c7bb8: beql v0,zero,0x001c7be8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c7bbc */ lw(4,ea(4,(int32_t)UINT32_C(0x00000024)));goto L_001c7be8;}}
/* 001c7bc0: sw a1,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));
/* 001c7bc4: nop  */ 
L_001c7bc8:;
/* 001c7bc8: lw v0,0x28(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000028)));
/* 001c7bcc: nop  */ 
/* 001c7bd0: nop  */ 
/* 001c7bd4: nop  */ 
/* 001c7bd8: nop  */ 
/* 001c7bdc: bnel v0,zero,0x001c7bc8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c7be0 */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));goto L_001c7bc8;}}
/* 001c7be4: lw a0,0x24(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000024)));
L_001c7be8:;
/* 001c7be8: nop  */ 
/* 001c7bec: nop  */ 
/* 001c7bf0: bnel a0,zero,0x001c7bb8 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 001c7bf4 */ lw(2,ea(4,(int32_t)UINT32_C(0x0000001c)));goto L_001c7bb8;}}
L_001c7bf8:;
/* 001c7bf8: jr ra */ {uint64_t target=cpu(31);/* delay 001c7bfc */ checkReturn(target,incoming);return;}
}
static void body_001c7c00(void){
nocturneEffectAxisNoteEntry(0x001c7c00u);
uint64_t incoming=cpu(31);
/* 001c7c00: lbu v0,-0x4d54(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));
/* 001c7c04: or a0,a0,v0 */ set(4,cpu(4)|cpu(2));
/* 001c7c08: jr ra */ {uint64_t target=cpu(31);/* delay 001c7c0c */ sb(ea(28,(int32_t)UINT32_C(0xffffb2ac)),(uint8_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_001c7c10(void){
nocturneEffectAxisNoteEntry(0x001c7c10u);
uint64_t incoming=cpu(31);
/* 001c7c10: lbu v0,-0x4d54(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));
/* 001c7c14: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c7c18: nor a0,zero,a0 */ set(4,~(cpu(0)|cpu(4)));
/* 001c7c1c: and a0,v0,a0 */ set(4,cpu(2)&cpu(4));
/* 001c7c20: jr ra */ {uint64_t target=cpu(31);/* delay 001c7c24 */ sb(ea(28,(int32_t)UINT32_C(0xffffb2ac)),(uint8_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_001c8108(void){
nocturneEffectAxisNoteEntry(0x001c8108u);
uint64_t incoming=cpu(31);
/* 001c8108: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c810c: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 001c8110: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c8114: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c8118: j 0x001c8120 */ /* delay 001c811c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001c8120();return;
}
static void body_001c8120(void){
nocturneEffectAxisNoteEntry(0x001c8120u);
uint64_t incoming=cpu(31);
/* 001c8120: move a3,a0 */ set(7,cpu(4));
/* 001c8124: beq a3,zero,0x001c81ac */ {int taken=(cpu(7)==cpu(0));/* delay 001c8128 */ set(2,cpu(5));if(taken){goto L_001c81ac;}}
/* 001c812c: beq a1,zero,0x001c81ac */ {int taken=(cpu(5)==cpu(0));/* delay 001c8130 */ set(2,cpu(7));if(taken){goto L_001c81ac;}}
/* 001c8134: lw v1,0x2c(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x0000002c)));
/* 001c8138: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c813c: sw v1,0x28(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 001c8140: lw v0,0x2c(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x0000002c)));
/* 001c8144: sw a3,0x24(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(7));
/* 001c8148: lw v1,0x2c(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x0000002c)));
/* 001c814c: bne a2,a0,0x001c81a8 */ {int taken=(cpu(6)!=cpu(4));/* delay 001c8150 */ sw(ea(5,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(3));if(taken){goto L_001c81a8;}}
/* 001c8154: lw v0,0x1c(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x0000001c)));
/* 001c8158: beql v0,zero,0x001c8190 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c815c */ lw(2,ea(7,(int32_t)UINT32_C(0x0000000c)));goto L_001c8190;}}
/* 001c8160: lhu v1,0x0(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8164: li v0,0xd */ set(2,sx(UINT32_C(0x0000000d)));
/* 001c8168: bnel v1,v0,0x001c8190 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 001c816c */ lw(2,ea(7,(int32_t)UINT32_C(0x0000000c)));goto L_001c8190;}}
/* 001c8170: lw v0,0x4(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 001c8174: lh a0,0x12(a3) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x00000012))));
/* 001c8178: sw v0,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 001c817c: lw v1,0x8(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 001c8180: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001c8184: b 0x001c81a8 */ /* delay 001c8188 */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));goto L_001c81a8;
L_001c8190:;
/* 001c8190: lw v1,0x4(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 001c8194: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 001c8198: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c819c: sw v1,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001c81a0: lw v0,0x8(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 001c81a4: sw v0,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_001c81a8:;
/* 001c81a8: move v0,a1 */ set(2,cpu(5));
L_001c81ac:;
/* 001c81ac: jr ra */ {uint64_t target=cpu(31);/* delay 001c81b0 */ checkReturn(target,incoming);return;}
}
static void body_001c81b8(void){
nocturneEffectAxisNoteEntry(0x001c81b8u);
uint64_t incoming=cpu(31);
/* 001c81b8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c81bc: move a1,a0 */ set(5,cpu(4));
/* 001c81c0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c81c4: move a2,zero */ set(6,cpu(0));
/* 001c81c8: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 001c81cc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c81d0: j 0x001c6b68 */ /* delay 001c81d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001c6b68();return;
}
static void body_001c8230(void){
nocturneEffectAxisNoteEntry(0x001c8230u);
uint64_t incoming=cpu(31);
/* 001c8230: lw v1,0x1c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001c8234: beq v1,zero,0x001c825c */ {int taken=(cpu(3)==cpu(0));/* delay 001c8238 */ set(5,cpu(0));if(taken){goto L_001c825c;}}
/* 001c823c: lb a0,0x1(a0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000001))));
L_001c8240:;
/* 001c8240: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 001c8244: lw v1,0x28(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000028)));
/* 001c8248: addu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 001c824c: nop  */ 
/* 001c8250: nop  */ 
/* 001c8254: bne v1,zero,0x001c8240 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c8258 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));if(taken){goto L_001c8240;}}
L_001c825c:;
/* 001c825c: jr ra */ {uint64_t target=cpu(31);/* delay 001c8260 */ set(2,cpu(5));checkReturn(target,incoming);return;}
}
static void body_001c83b0(void){
nocturneEffectAxisNoteEntry(0x001c83b0u);
uint64_t incoming=cpu(31);
/* 001c83b0: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c83b4: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c83b8: slti v1,a0,0x2 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c83bc: beq v1,zero,0x001c83d8 */ {int taken=(cpu(3)==cpu(0));/* delay 001c83c0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));if(taken){goto L_001c83d8;}}
/* 001c83c4: bltzl a0,0x001c83dc */ {int taken=((int64_t)cpu(4)<0);if(taken){/* delay 001c83c8 */ set(2,sx((uint32_t)cpu(2)<<2));goto L_001c83dc;}}
/* 001c83cc: jr ra */ {uint64_t target=cpu(31);/* delay 001c83d0 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb2a0)));checkReturn(target,incoming);return;}
L_001c83d8:;
/* 001c83d8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
L_001c83dc:;
/* 001c83dc: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c83e0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c83e4: lw v1,-0x45cc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffba34)));
/* 001c83e8: jr ra */ {uint64_t target=cpu(31);/* delay 001c83ec */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000010))));checkReturn(target,incoming);return;}
}
static void body_001c83f0(void){
nocturneEffectAxisNoteEntry(0x001c83f0u);
uint64_t incoming=cpu(31);
/* 001c83f0: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c83f4: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c83f8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c83fc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c8400: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c8404: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8408: lw v1,-0x45cc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffba34)));
/* 001c840c: jr ra */ {uint64_t target=cpu(31);/* delay 001c8410 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000010))));checkReturn(target,incoming);return;}
}
static void body_001c8418(void){
nocturneEffectAxisNoteEntry(0x001c8418u);
uint64_t incoming=cpu(31);
/* 001c8418: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c841c: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c8420: slti v1,a0,0x2 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c8424: beq v1,zero,0x001c8440 */ {int taken=(cpu(3)==cpu(0));/* delay 001c8428 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));if(taken){goto L_001c8440;}}
/* 001c842c: bltzl a0,0x001c8444 */ {int taken=((int64_t)cpu(4)<0);if(taken){/* delay 001c8430 */ set(2,sx((uint32_t)cpu(2)<<2));goto L_001c8444;}}
/* 001c8434: jr ra */ {uint64_t target=cpu(31);/* delay 001c8438 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb2a0)));checkReturn(target,incoming);return;}
L_001c8440:;
/* 001c8440: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
L_001c8444:;
/* 001c8444: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c8448: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c844c: lw v1,-0x45cc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffba34)));
/* 001c8450: jr ra */ {uint64_t target=cpu(31);/* delay 001c8454 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000012))));checkReturn(target,incoming);return;}
}
static void body_001c8458(void){
nocturneEffectAxisNoteEntry(0x001c8458u);
uint64_t incoming=cpu(31);
/* 001c8458: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 001c845c: sll v0,a0,0x3 */ set(2,sx((uint32_t)cpu(4)<<3));
/* 001c8460: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c8464: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c8468: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 001c846c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8470: lw v1,-0x45cc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffba34)));
/* 001c8474: jr ra */ {uint64_t target=cpu(31);/* delay 001c8478 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000012))));checkReturn(target,incoming);return;}
}
static void body_001c8508(void){
nocturneEffectAxisNoteEntry(0x001c8508u);
uint64_t incoming=cpu(31);
/* 001c8508: andi v0,a0,0xff */ set(2,cpu(4)&UINT32_C(0x000000ff));
/* 001c850c: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 001c8510: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c8514: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c8518: lui s5,0x57 */ set(21,sx(UINT32_C(0x00570000)));
/* 001c851c: addu s5,s5,v0 */ set(21,sx((uint32_t)cpu(21)+(uint32_t)cpu(2)));
/* 001c8520: lw s5,-0x4430(s5) */ lw(21,ea(21,(int32_t)UINT32_C(0xffffbbd0)));
/* 001c8524: move a0,sp */ set(4,cpu(29));
/* 001c8528: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c852c: move s0,a1 */ set(16,cpu(5));
/* 001c8530: li a2,0x3 */ set(6,sx(UINT32_C(0x00000003)));
/* 001c8534: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c8538: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c853c: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c8540: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c8544: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c8548: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c854c: jal 0x002d4558 */ set(31,0x001c8554u);/* delay 001c8550 */ set(5,cpu(0));nocturneBattleActionSkillCall(0x002d4558u);
/* 001c8554: beql s5,zero,0x001c8678 */ {int taken=(cpu(21)==cpu(0));if(taken){/* delay 001c8558 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_001c8678;}}
/* 001c855c: move a0,s5 */ set(4,cpu(21));
/* 001c8560: jal 0x002d5d0c */ set(31,0x001c8568u);/* delay 001c8564 */ set(19,cpu(0));nocturneBattleActionSkillCall(0x002d5d0cu);
/* 001c8568: lbu a1,0xc(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 001c856c: move s6,v0 */ set(22,cpu(2));
/* 001c8570: blez s6,0x001c8674 */ {int taken=((int64_t)cpu(22)<=0);/* delay 001c8574 */ set(20,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000c))));if(taken){goto L_001c8674;}}
/* 001c8578: b 0x001c8588 */ /* delay 001c857c */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));goto L_001c8588;
L_001c8580:;
/* 001c8580: addu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));
/* 001c8584: nop  */ 
L_001c8588:;
/* 001c8588: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c858c: andi a0,v1,0x80 */ set(4,cpu(3)&UINT32_C(0x00000080));
/* 001c8590: beq a0,zero,0x001c85c0 */ {int taken=(cpu(4)==cpu(0));/* delay 001c8594 */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));if(taken){goto L_001c85c0;}}
/* 001c8598: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 001c859c: andi s2,v1,0xff */ set(18,cpu(3)&UINT32_C(0x000000ff));
/* 001c85a0: addu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));
/* 001c85a4: sll a0,s2,0x8 */ set(4,sx((uint32_t)cpu(18)<<8));
/* 001c85a8: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c85ac: andi v0,v1,0xff */ set(2,cpu(3)&UINT32_C(0x000000ff));
/* 001c85b0: sb v1,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(3));
/* 001c85b4: b 0x001c85c8 */ /* delay 001c85b8 */ set(18,cpu(4)|cpu(2));goto L_001c85c8;
L_001c85c0:;
/* 001c85c0: sb zero,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));
/* 001c85c4: lbu s2,0x0(sp) */ set(18,byte(ea(29,(int32_t)UINT32_C(0x00000000))));
L_001c85c8:;
/* 001c85c8: sll v0,a1,0x18 */ set(2,sx((uint32_t)cpu(5)<<24));
/* 001c85cc: sra s1,v0,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 001c85d0: beql s1,s4,0x001c8634 */ {int taken=(cpu(17)==cpu(20));if(taken){/* delay 001c85d4 */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));goto L_001c8634;}}
/* 001c85d8: lw t0,0x14(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c85dc: beq t0,zero,0x001c8600 */ {int taken=(cpu(8)==cpu(0));/* delay 001c85e0 */ set(4,sx(UINT32_C(0x00550000)));if(taken){goto L_001c8600;}}
/* 001c85e4: lw v0,0x1c(t0) */ lw(2,ea(8,(int32_t)UINT32_C(0x0000001c)));
/* 001c85e8: beql v0,zero,0x001c8624 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c85ec */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000f))));goto L_001c8624;}}
/* 001c85f0: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
/* 001c85f4: b 0x001c860c */ /* delay 001c85f8 */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));goto L_001c860c;
L_001c8600:;
/* 001c8600: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
/* 001c8604: lb a3,0xe(s0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 001c8608: move t0,zero */ set(8,cpu(0));
L_001c860c:;
/* 001c860c: addiu a0,a0,-0xbd0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff430)));
/* 001c8610: jal 0x001c7828 */ set(31,0x001c8618u);/* delay 001c8614 */ set(5,cpu(0));body_001c7828();
/* 001c8618: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c861c: move t0,v0 */ set(8,cpu(2));
/* 001c8620: lbu a1,0xf(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000f))));
L_001c8624:;
/* 001c8624: move a0,t0 */ set(4,cpu(8));
/* 001c8628: jal 0x001c7a60 */ set(31,0x001c8630u);/* delay 001c862c */ set(20,cpu(17));body_001c7a60();
/* 001c8630: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
L_001c8634:;
/* 001c8634: move a0,sp */ set(4,cpu(29));
/* 001c8638: lb a3,0xe(s0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 001c863c: sltiu t1,s3,0x1 */ set(9,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
/* 001c8640: lw t0,0x14(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c8644: move a1,s1 */ set(5,cpu(17));
/* 001c8648: jal 0x001c7890 */ set(31,0x001c8650u);/* delay 001c864c */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));body_001c7890();
/* 001c8650: lb a1,-0x4d68(gp) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));
/* 001c8654: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c8658: jal 0x001c7a88 */ set(31,0x001c8660u);/* delay 001c865c */ set(4,cpu(2));body_001c7a88();
/* 001c8660: jal 0x001c6128 */ set(31,0x001c8668u);/* delay 001c8664 */ set(4,cpu(18));body_001c6128();
/* 001c8668: slt v0,s3,s6 */ set(2,(int64_t)cpu(19)<(int64_t)cpu(22));
/* 001c866c: bnel v0,zero,0x001c8580 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c8670 */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000c))));goto L_001c8580;}}
L_001c8674:;
/* 001c8674: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
L_001c8678:;
/* 001c8678: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c867c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c8680: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c8684: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c8688: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c868c: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c8690: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c8694: jr ra */ {uint64_t target=cpu(31);/* delay 001c8698 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_001c86a0(void){
nocturneEffectAxisNoteEntry(0x001c86a0u);
uint64_t incoming=cpu(31);
/* 001c86a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c86a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c86a8: move s0,a0 */ set(16,cpu(4));
/* 001c86ac: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c86b0: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c86b4: beq v0,zero,0x001c86c8 */ {int taken=(cpu(2)==cpu(0));/* delay 001c86b8 */ set(8,cpu(2));if(taken){goto L_001c86c8;}}
/* 001c86bc: lw v0,0x1c(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x0000001c)));
/* 001c86c0: beql v0,zero,0x001c86c8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c86c4 */ sb(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(0));goto L_001c86c8;}}
L_001c86c8:;
/* 001c86c8: lb v0,0x1c(s0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000001c))));
/* 001c86cc: beql v0,zero,0x001c8704 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c86d0 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000001d))));goto L_001c8704;}}
/* 001c86d4: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
/* 001c86d8: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 001c86dc: lb a3,0xe(s0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 001c86e0: addiu a0,a0,-0xbd0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff430)));
/* 001c86e4: jal 0x001c7828 */ set(31,0x001c86ecu);/* delay 001c86e8 */ set(5,cpu(0));body_001c7828();
/* 001c86ec: lbu a1,0xf(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000f))));
/* 001c86f0: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c86f4: jal 0x001c7a60 */ set(31,0x001c86fcu);/* delay 001c86f8 */ set(4,cpu(2));body_001c7a60();
/* 001c86fc: sb zero,0x1c(s0) */ sb(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(0));
/* 001c8700: lb v0,0x1d(s0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000001d))));
L_001c8704:;
/* 001c8704: beql v0,zero,0x001c8724 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c8708 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001c8724;}}
/* 001c870c: lw a0,0x14(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c8710: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001c8714: jal 0x001c7b30 */ set(31,0x001c871cu);/* delay 001c8718 */ lw(6,ea(16,(int32_t)UINT32_C(0x00000004)));body_001c7b30();
/* 001c871c: sb zero,0x1d(s0) */ sb(ea(16,(int32_t)UINT32_C(0x0000001d)),(uint8_t)cpu(0));
/* 001c8720: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001c8724:;
/* 001c8724: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c8728: jr ra */ {uint64_t target=cpu(31);/* delay 001c872c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c8730(void){
nocturneEffectAxisNoteEntry(0x001c8730u);
uint64_t incoming=cpu(31);
/* 001c8730: lw v0,-0x4d64(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb29c)));
/* 001c8734: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001c8738: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001c873c: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 001c8740: sb a1,0x1d(a0) */ sb(ea(4,(int32_t)UINT32_C(0x0000001d)),(uint8_t)cpu(5));
/* 001c8744: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8748: sb a1,0x1c(a0) */ sb(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(5));
/* 001c874c: jr ra */ {uint64_t target=cpu(31);/* delay 001c8750 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
static void body_001c8758(void){
nocturneEffectAxisNoteEntry(0x001c8758u);
uint64_t incoming=cpu(31);
/* 001c8758: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c875c: andi a1,a1,0xffff */ set(5,cpu(5)&UINT32_C(0x0000ffff));
/* 001c8760: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c8764: move s0,a0 */ set(16,cpu(4));
/* 001c8768: srl v0,a1,0x8 */ set(2,sx((uint32_t)cpu(5)>>8));
/* 001c876c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c8770: sb a1,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(5));
/* 001c8774: sb v0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001c8778: jal 0x001c86a0 */ set(31,0x001c8780u);/* delay 001c877c */ sb(ea(29,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(0));body_001c86a0();
/* 001c8780: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
/* 001c8784: move a0,sp */ set(4,cpu(29));
/* 001c8788: lb a3,0xe(s0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 001c878c: move t1,zero */ set(9,cpu(0));
/* 001c8790: lw t0,0x14(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c8794: jal 0x001c7890 */ set(31,0x001c879cu);/* delay 001c8798 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000c))));body_001c7890();
/* 001c879c: lb a1,-0x4d68(gp) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));
/* 001c87a0: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c87a4: jal 0x001c7a88 */ set(31,0x001c87acu);/* delay 001c87a8 */ set(4,cpu(2));body_001c7a88();
/* 001c87ac: lw a0,0x14(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c87b0: jal 0x001c7b40 */ set(31,0x001c87b8u);/* delay 001c87b4 */ lw(5,ea(16,(int32_t)UINT32_C(0x00000008)));body_001c7b40();
/* 001c87b8: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c87bc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c87c0: jr ra */ {uint64_t target=cpu(31);/* delay 001c87c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c87c8(void){
nocturneEffectAxisNoteEntry(0x001c87c8u);
uint64_t incoming=cpu(31);
/* 001c87c8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c87cc: sll v0,a0,0x8 */ set(2,sx((uint32_t)cpu(4)<<8));
/* 001c87d0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c87d4: andi t0,a0,0xf */ set(8,cpu(4)&UINT32_C(0x0000000f));
/* 001c87d8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c87dc: move s1,a1 */ set(17,cpu(5));
/* 001c87e0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c87e4: addiu s0,s1,0x18 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));
/* 001c87e8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c87ec: ori a3,zero,0xf118 */ set(7,cpu(0)|UINT32_C(0x0000f118));
/* 001c87f0: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001c87f4: lw a2,0x10(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c87f8: lb s2,0xd(s1) */ set(18,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000d))));
/* 001c87fc: addu v1,a2,a1 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c8800: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 001c8804: lbu a0,0x0(v1) */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001c8808: or a0,v0,a0 */ set(4,cpu(2)|cpu(4));
/* 001c880c: beq a0,a3,0x001c8c60 */ {int taken=(cpu(4)==cpu(7));/* delay 001c8810 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));if(taken){goto L_001c8c60;}}
/* 001c8814: slt v0,a3,a0 */ set(2,(int64_t)cpu(7)<(int64_t)cpu(4));
/* 001c8818: bne v0,zero,0x001c88d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c881c */ set(2,cpu(0)|UINT32_C(0x0000f209));if(taken){goto L_001c88d0;}}
/* 001c8820: ori v0,zero,0xf112 */ set(2,cpu(0)|UINT32_C(0x0000f112));
/* 001c8824: beq a0,v0,0x001c8ba0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8828 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c8ba0;}}
/* 001c882c: bne v0,zero,0x001c8880 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c8830 */ set(2,cpu(0)|UINT32_C(0x0000f115));if(taken){goto L_001c8880;}}
/* 001c8834: ori v0,zero,0xf10f */ set(2,cpu(0)|UINT32_C(0x0000f10f));
/* 001c8838: beq a0,v0,0x001c8b50 */ {int taken=(cpu(4)==cpu(2));/* delay 001c883c */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c8b50;}}
/* 001c8840: bne v0,zero,0x001c8860 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c8844 */ set(2,cpu(0)|UINT32_C(0x0000f110));if(taken){goto L_001c8860;}}
/* 001c8848: ori v0,zero,0xf104 */ set(2,cpu(0)|UINT32_C(0x0000f104));
/* 001c884c: beql a0,v0,0x001c8b8c */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 001c8850 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb294)));goto L_001c8b8c;}}
/* 001c8854: b 0x001c8ca0 */ /* delay 001c8858 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8860:;
/* 001c8860: beq a0,v0,0x001c8b70 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8864 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb294)));if(taken){goto L_001c8b70;}}
/* 001c8868: ori v0,zero,0xf111 */ set(2,cpu(0)|UINT32_C(0x0000f111));
/* 001c886c: beq a0,v0,0x001c8b80 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8870 */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));if(taken){goto L_001c8b80;}}
/* 001c8874: b 0x001c8ca0 */ /* delay 001c8878 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8880:;
/* 001c8880: beq a0,v0,0x001c8be0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8884 */ if(taken){goto L_001c8be0;}}
/* 001c8888: slt v0,v0,a0 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));
/* 001c888c: bne v0,zero,0x001c88b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c8890 */ set(2,cpu(0)|UINT32_C(0x0000f116));if(taken){goto L_001c88b8;}}
/* 001c8894: ori v0,zero,0xf113 */ set(2,cpu(0)|UINT32_C(0x0000f113));
/* 001c8898: beq a0,v0,0x001c8bb0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c889c */ if(taken){goto L_001c8bb0;}}
/* 001c88a0: ori v0,zero,0xf114 */ set(2,cpu(0)|UINT32_C(0x0000f114));
/* 001c88a4: beq a0,v0,0x001c8bc8 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88a8 */ if(taken){goto L_001c8bc8;}}
/* 001c88ac: b 0x001c8ca0 */ /* delay 001c88b0 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c88b8:;
/* 001c88b8: beq a0,v0,0x001c8c08 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88bc */ set(2,cpu(0)|UINT32_C(0x0000f117));if(taken){goto L_001c8c08;}}
/* 001c88c0: beq a0,v0,0x001c8c30 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88c4 */ if(taken){goto L_001c8c30;}}
/* 001c88c8: b 0x001c8ca0 */ /* delay 001c88cc */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c88d0:;
/* 001c88d0: beq a0,v0,0x001c89a0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88d4 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c89a0;}}
/* 001c88d8: bne v0,zero,0x001c8920 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c88dc */ set(2,cpu(0)|UINT32_C(0x0000f20c));if(taken){goto L_001c8920;}}
/* 001c88e0: ori v0,zero,0xf203 */ set(2,cpu(0)|UINT32_C(0x0000f203));
/* 001c88e4: beq a0,v0,0x001c89d8 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88e8 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c89d8;}}
/* 001c88ec: bne v0,zero,0x001c8908 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c88f0 */ set(2,cpu(0)|UINT32_C(0x0000f206));if(taken){goto L_001c8908;}}
/* 001c88f4: ori v0,zero,0xf202 */ set(2,cpu(0)|UINT32_C(0x0000f202));
/* 001c88f8: beq a0,v0,0x001c8988 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88fc */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));if(taken){goto L_001c8988;}}
/* 001c8900: b 0x001c8ca0 */ /* delay 001c8904 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8908:;
/* 001c8908: beq a0,v0,0x001c8968 */ {int taken=(cpu(4)==cpu(2));/* delay 001c890c */ set(2,cpu(0)|UINT32_C(0x0000f207));if(taken){goto L_001c8968;}}
/* 001c8910: beq a0,v0,0x001c89c0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8914 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));if(taken){goto L_001c89c0;}}
/* 001c8918: b 0x001c8ca0 */ /* delay 001c891c */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8920:;
/* 001c8920: beq a0,v0,0x001c8aa0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8924 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c8aa0;}}
/* 001c8928: bne v0,zero,0x001c8950 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c892c */ set(2,cpu(0)|UINT32_C(0x0000f20d));if(taken){goto L_001c8950;}}
/* 001c8930: ori v0,zero,0xf20a */ set(2,cpu(0)|UINT32_C(0x0000f20a));
/* 001c8934: beq a0,v0,0x001c8a30 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8938 */ set(2,cpu(0)|UINT32_C(0x0000f20b));if(taken){goto L_001c8a30;}}
/* 001c893c: beq a0,v0,0x001c8a68 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8940 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));if(taken){goto L_001c8a68;}}
/* 001c8944: b 0x001c8ca0 */ /* delay 001c8948 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8950:;
/* 001c8950: beq a0,v0,0x001c8ae8 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8954 */ set(2,cpu(0)|UINT32_C(0x0000f20e));if(taken){goto L_001c8ae8;}}
/* 001c8958: beq a0,v0,0x001c8b48 */ {int taken=(cpu(4)==cpu(2));/* delay 001c895c */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_001c8b48;}}
/* 001c8960: b 0x001c8ca0 */ /* delay 001c8964 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8968:;
/* 001c8968: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c896c: addiu a0,a1,0x2 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8970: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8974: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 001c8978: sb v1,0xc(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(3));
/* 001c897c: b 0x001c8cb0 */ /* delay 001c8980 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_001c8cb0;
L_001c8988:;
/* 001c8988: addiu a0,a1,0x2 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c898c: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8990: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 001c8994: sb v1,0xd(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000000d)),(uint8_t)cpu(3));
/* 001c8998: b 0x001c8cb0 */ /* delay 001c899c */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_001c8cb0;
L_001c89a0:;
/* 001c89a0: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c89a4: addiu a0,a1,0x2 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c89a8: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c89ac: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 001c89b0: sb v1,0xe(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000000e)),(uint8_t)cpu(3));
/* 001c89b4: b 0x001c8cb0 */ /* delay 001c89b8 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_001c8cb0;
L_001c89c0:;
/* 001c89c0: addiu a0,a1,0x2 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c89c4: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c89c8: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 001c89cc: sb v1,0xf(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000000f)),(uint8_t)cpu(3));
/* 001c89d0: b 0x001c8cb0 */ /* delay 001c89d4 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_001c8cb0;
L_001c89d8:;
/* 001c89d8: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c89dc: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c89e0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001c89e4: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 001c89e8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c89ec: lw v0,-0x4434(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffffbbcc)));
/* 001c89f0: beql v0,zero,0x001c8a24 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c89f4 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_001c8a24;}}
/* 001c89f8: jal 0x001c86a0 */ set(31,0x001c8a00u);/* delay 001c89fc */ set(4,cpu(17));body_001c86a0();
/* 001c8a00: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c8a04: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001c8a08: move a1,s1 */ set(5,cpu(17));
/* 001c8a0c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c8a10: lbu a0,0x0(v0) */ set(4,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8a14: addiu a0,a0,0xff */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000000ff)));
/* 001c8a18: jal 0x001c8508 */ set(31,0x001c8a20u);/* delay 001c8a1c */ set(4,cpu(4)&UINT32_C(0x000000ff));body_001c8508();
/* 001c8a20: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
L_001c8a24:;
/* 001c8a24: addiu v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 001c8a28: b 0x001c8cb0 */ /* delay 001c8a2c */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_001c8cb0;
L_001c8a30:;
/* 001c8a30: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c8a34: addiu v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8a38: lbu a1,0x0(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8a3c: move a0,s1 */ set(4,cpu(17));
/* 001c8a40: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c8a44: jal 0x001c86a0 */ set(31,0x001c8a4cu);/* delay 001c8a48 */ set(16,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));body_001c86a0();
/* 001c8a4c: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 001c8a50: lw a1,0x14(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8a54: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c8a58: jal 0x001c9d00 */ set(31,0x001c8a60u);/* delay 001c8a5c */ set(6,cpu(18));body_001c9d00();
/* 001c8a60: b 0x001c8ad4 */ /* delay 001c8a64 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));goto L_001c8ad4;
L_001c8a68:;
/* 001c8a68: addiu v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8a6c: lbu a1,0x0(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8a70: move a0,s1 */ set(4,cpu(17));
/* 001c8a74: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c8a78: jal 0x001c86a0 */ set(31,0x001c8a80u);/* delay 001c8a7c */ set(16,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));body_001c86a0();
/* 001c8a80: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 001c8a84: lw a1,0x14(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8a88: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c8a8c: jal 0x001c9b58 */ set(31,0x001c8a94u);/* delay 001c8a90 */ set(6,cpu(18));body_001c9b58();
/* 001c8a94: b 0x001c8ad4 */ /* delay 001c8a98 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));goto L_001c8ad4;
L_001c8aa0:;
/* 001c8aa0: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c8aa4: addiu v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8aa8: lbu a1,0x0(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8aac: move a0,s1 */ set(4,cpu(17));
/* 001c8ab0: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c8ab4: jal 0x001c86a0 */ set(31,0x001c8abcu);/* delay 001c8ab8 */ set(16,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));body_001c86a0();
/* 001c8abc: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 001c8ac0: lw a1,0x14(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8ac4: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c8ac8: jal 0x001c9c28 */ set(31,0x001c8ad0u);/* delay 001c8acc */ set(6,cpu(18));body_001c9c28();
/* 001c8ad0: lb a1,-0x4d68(gp) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));
L_001c8ad4:;
/* 001c8ad4: sw v0,0x14(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c8ad8: jal 0x001c7a88 */ set(31,0x001c8ae0u);/* delay 001c8adc */ set(4,cpu(2));body_001c7a88();
/* 001c8ae0: b 0x001c8cb4 */ /* delay 001c8ae4 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8ae8:;
/* 001c8ae8: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c8aec: addiu v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8af0: lbu a1,0x0(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8af4: move a0,s1 */ set(4,cpu(17));
/* 001c8af8: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c8afc: jal 0x001c86a0 */ set(31,0x001c8b04u);/* delay 001c8b00 */ set(16,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));body_001c86a0();
/* 001c8b04: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 001c8b08: lb a1,0xc(s1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 001c8b0c: move a3,s2 */ set(7,cpu(18));
/* 001c8b10: lw a2,0x14(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8b14: jal 0x001c9d60 */ set(31,0x001c8b1cu);/* delay 001c8b18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));body_001c9d60();
/* 001c8b1c: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c8b20: jal 0x001c7c00 */ set(31,0x001c8b28u);/* delay 001c8b24 */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));body_001c7c00();
/* 001c8b28: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8b2c: jal 0x001c7a88 */ set(31,0x001c8b34u);/* delay 001c8b30 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));body_001c7a88();
/* 001c8b34: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8b38: jal 0x001c7a60 */ set(31,0x001c8b40u);/* delay 001c8b3c */ set(5,byte(ea(17,(int32_t)UINT32_C(0x0000000f))));body_001c7a60();
/* 001c8b40: b 0x001c8cb4 */ /* delay 001c8b44 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8b48:;
/* 001c8b48: b 0x001c8cb0 */ /* delay 001c8b4c */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_001c8cb0;
L_001c8b50:;
/* 001c8b50: lbu v0,-0x4d54(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));
/* 001c8b54: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 001c8b58: bnel v0,zero,0x001c8cb4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c8b5c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;}}
/* 001c8b60: jal 0x001c8730 */ set(31,0x001c8b68u);/* delay 001c8b64 */ set(4,cpu(17));body_001c8730();
/* 001c8b68: b 0x001c8cb4 */ /* delay 001c8b6c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8b70:;
/* 001c8b70: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c8b74: ori v1,v1,0x2 */ set(3,cpu(3)|UINT32_C(0x00000002));
/* 001c8b78: b 0x001c8cc8 */ /* delay 001c8b7c */ sw(ea(28,(int32_t)UINT32_C(0xffffb294)),(uint32_t)cpu(3));goto L_001c8cc8;
L_001c8b80:;
/* 001c8b80: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 001c8b84: beq v0,zero,0x001c8cb0 */ {int taken=(cpu(2)==cpu(0));/* delay 001c8b88 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb294)));if(taken){goto L_001c8cb0;}}
L_001c8b8c:;
/* 001c8b8c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c8b90: ori v1,v1,0x1 */ set(3,cpu(3)|UINT32_C(0x00000001));
/* 001c8b94: b 0x001c8cc8 */ /* delay 001c8b98 */ sw(ea(28,(int32_t)UINT32_C(0xffffb294)),(uint32_t)cpu(3));goto L_001c8cc8;
L_001c8ba0:;
/* 001c8ba0: lw v0,-0x4d6c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb294)));
/* 001c8ba4: ori v0,v0,0x4 */ set(2,cpu(2)|UINT32_C(0x00000004));
/* 001c8ba8: b 0x001c8cb0 */ /* delay 001c8bac */ sw(ea(28,(int32_t)UINT32_C(0xffffb294)),(uint32_t)cpu(2));goto L_001c8cb0;
L_001c8bb0:;
/* 001c8bb0: jal 0x001c6098 */ set(31,0x001c8bb8u);/* delay 001c8bb4 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8bb8: ori v1,zero,0x80e2 */ set(3,cpu(0)|UINT32_C(0x000080e2));
/* 001c8bbc: slti v0,v0,0x0 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001c8bc0: b 0x001c8bf4 */ /* delay 001c8bc4 */ set(5,cpu(0)|UINT32_C(0x000080e3));goto L_001c8bf4;
L_001c8bc8:;
/* 001c8bc8: jal 0x001c6098 */ set(31,0x001c8bd0u);/* delay 001c8bcc */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8bd0: ori v1,zero,0x80e4 */ set(3,cpu(0)|UINT32_C(0x000080e4));
/* 001c8bd4: slti v0,v0,0x0 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001c8bd8: b 0x001c8bf4 */ /* delay 001c8bdc */ set(5,cpu(0)|UINT32_C(0x000080e5));goto L_001c8bf4;
L_001c8be0:;
/* 001c8be0: jal 0x001c6098 */ set(31,0x001c8be8u);/* delay 001c8be4 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8be8: ori v1,zero,0x80e0 */ set(3,cpu(0)|UINT32_C(0x000080e0));
/* 001c8bec: slti v0,v0,0x0 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001c8bf0: ori a1,zero,0x80e1 */ set(5,cpu(0)|UINT32_C(0x000080e1));
L_001c8bf4:;
/* 001c8bf4: movn a1,v1,v0 */ if(cpu(2)!=0){set(5,cpu(3));}
/* 001c8bf8: jal 0x001c8758 */ set(31,0x001c8c00u);/* delay 001c8bfc */ set(4,cpu(17));body_001c8758();
/* 001c8c00: b 0x001c8cb4 */ /* delay 001c8c04 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8c08:;
/* 001c8c08: jal 0x001c6098 */ set(31,0x001c8c10u);/* delay 001c8c0c */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8c10: bgezl v0,0x001c8cb4 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 001c8c14 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;}}
/* 001c8c18: move a0,s1 */ set(4,cpu(17));
/* 001c8c1c: jal 0x001c8758 */ set(31,0x001c8c24u);/* delay 001c8c20 */ set(5,cpu(0)|UINT32_C(0x000080e2));body_001c8758();
/* 001c8c24: b 0x001c8cb4 */ /* delay 001c8c28 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8c30:;
/* 001c8c30: jal 0x001c6098 */ set(31,0x001c8c38u);/* delay 001c8c34 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8c38: bgez v0,0x001c8c50 */ {int taken=((int64_t)cpu(2)>=0);/* delay 001c8c3c */ set(4,cpu(17));if(taken){goto L_001c8c50;}}
/* 001c8c40: jal 0x001c8758 */ set(31,0x001c8c48u);/* delay 001c8c44 */ set(5,cpu(0)|UINT32_C(0x000080e7));body_001c8758();
/* 001c8c48: b 0x001c8cb4 */ /* delay 001c8c4c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8c50:;
/* 001c8c50: jal 0x001c8758 */ set(31,0x001c8c58u);/* delay 001c8c54 */ set(5,cpu(0)|UINT32_C(0x000080e6));body_001c8758();
/* 001c8c58: b 0x001c8cb4 */ /* delay 001c8c5c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8c60:;
/* 001c8c60: jal 0x001c6098 */ set(31,0x001c8c68u);/* delay 001c8c64 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8c68: bgez v0,0x001c8c8c */ {int taken=((int64_t)cpu(2)>=0);/* delay 001c8c6c */ set(4,cpu(17));if(taken){goto L_001c8c8c;}}
/* 001c8c70: jal 0x001c60e0 */ set(31,0x001c8c78u);/* delay 001c8c74 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c60e0();
/* 001c8c78: bgez v0,0x001c8c8c */ {int taken=((int64_t)cpu(2)>=0);/* delay 001c8c7c */ set(4,cpu(17));if(taken){goto L_001c8c8c;}}
/* 001c8c80: jal 0x001c8758 */ set(31,0x001c8c88u);/* delay 001c8c84 */ set(5,cpu(0)|UINT32_C(0x000080e9));body_001c8758();
/* 001c8c88: move a0,s1 */ set(4,cpu(17));
L_001c8c8c:;
/* 001c8c8c: jal 0x001c8758 */ set(31,0x001c8c94u);/* delay 001c8c90 */ set(5,cpu(0)|UINT32_C(0x000080e8));body_001c8758();
/* 001c8c94: b 0x001c8cb4 */ /* delay 001c8c98 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8ca0:;
/* 001c8ca0: addiu v0,t0,-0x1 */ set(2,sx((uint32_t)cpu(8)+UINT32_C(0xffffffff)));
/* 001c8ca4: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 001c8ca8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8cac: sw v1,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
L_001c8cb0:;
/* 001c8cb0: lb v0,0x1c(s1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));
L_001c8cb4:;
/* 001c8cb4: bne v0,zero,0x001c8cc8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c8cb8 */ set(2,cpu(0));if(taken){goto L_001c8cc8;}}
/* 001c8cbc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c8cc0: sb v0,0x1c(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(2));
/* 001c8cc4: move v0,zero */ set(2,cpu(0));
L_001c8cc8:;
/* 001c8cc8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c8ccc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c8cd0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c8cd4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c8cd8: jr ra */ {uint64_t target=cpu(31);/* delay 001c8cdc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c8f08(void){
nocturneEffectAxisNoteEntry(0x001c8f08u);
uint64_t incoming=cpu(31);
/* 001c8f08: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c8f0c: li v1,0xf0 */ set(3,sx(UINT32_C(0x000000f0)));
/* 001c8f10: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c8f14: move s1,a0 */ set(17,cpu(4));
/* 001c8f18: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c8f1c: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c8f20: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c8f24: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c8f28: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c8f2c: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 001c8f30: andi v0,v0,0xf0 */ set(2,cpu(2)&UINT32_C(0x000000f0));
/* 001c8f34: beq v0,v1,0x001c8f58 */ {int taken=(cpu(2)==cpu(3));/* delay 001c8f38 */ set(19,sx(UINT32_C(0x00000001)));if(taken){goto L_001c8f58;}}
/* 001c8f3c: lbu v1,0x1(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 001c8f40: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 001c8f44: bne v1,v0,0x001c8f5c */ {int taken=(cpu(3)!=cpu(2));/* delay 001c8f48 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb294)));if(taken){goto L_001c8f5c;}}
/* 001c8f4c: lw v0,0x18(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 001c8f50: addiu v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c8f54: sw v0,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
L_001c8f58:;
/* 001c8f58: lw v0,-0x4d6c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb294)));
L_001c8f5c:;
/* 001c8f5c: li v1,-0x2 */ set(3,sx(UINT32_C(0xfffffffe)));
/* 001c8f60: li a1,-0x3 */ set(5,sx(UINT32_C(0xfffffffd)));
/* 001c8f64: li a2,-0x5 */ set(6,sx(UINT32_C(0xfffffffb)));
/* 001c8f68: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001c8f6c: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c8f70: and v0,v0,a1 */ set(2,cpu(2)&cpu(5));
/* 001c8f74: and v0,v0,a2 */ set(2,cpu(2)&cpu(6));
/* 001c8f78: jal 0x001c7c00 */ set(31,0x001c8f80u);/* delay 001c8f7c */ sw(ea(28,(int32_t)UINT32_C(0xffffb294)),(uint32_t)cpu(2));body_001c7c00();
/* 001c8f80: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c8f84: b 0x001c909c */ /* delay 001c8f88 */ set(18,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));goto L_001c909c;
L_001c8f90:;
/* 001c8f90: bne s0,v0,0x001c8fb8 */ {int taken=(cpu(16)!=cpu(2));/* delay 001c8f94 */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));if(taken){goto L_001c8fb8;}}
/* 001c8f98: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 001c8f9c: beql v0,zero,0x001c909c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c8fa0 */ set(19,sx(UINT32_C(0x00000001)));goto L_001c909c;}}
/* 001c8fa4: jal 0x001c8730 */ set(31,0x001c8facu);/* delay 001c8fa8 */ set(4,cpu(17));body_001c8730();
/* 001c8fac: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c8fb0: b 0x001c909c */ /* delay 001c8fb4 */ set(19,sx(UINT32_C(0x00000001)));goto L_001c909c;
L_001c8fb8:;
/* 001c8fb8: jal 0x001c86a0 */ set(31,0x001c8fc0u);/* delay 001c8fbc */ set(4,cpu(17));body_001c86a0();
/* 001c8fc0: slti v0,s0,0x80 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001c8fc4: beql v0,zero,0x001c8ff8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c8fc8 */ lw(3,ea(18,(int32_t)UINT32_C(0x00000000)));goto L_001c8ff8;}}
/* 001c8fcc: lb a1,0xc(s1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 001c8fd0: move t1,s3 */ set(9,cpu(19));
/* 001c8fd4: lb a2,0xd(s1) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000d))));
/* 001c8fd8: move a0,sp */ set(4,cpu(29));
/* 001c8fdc: lb a3,0xe(s1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 001c8fe0: lw t0,0x14(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8fe4: sb s0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(16));
/* 001c8fe8: jal 0x001c7890 */ set(31,0x001c8ff0u);/* delay 001c8fec */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));body_001c7890();
/* 001c8ff0: b 0x001c907c */ /* delay 001c8ff4 */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));goto L_001c907c;
L_001c8ff8:;
/* 001c8ff8: sll a2,s0,0x8 */ set(6,sx((uint32_t)cpu(16)<<8));
/* 001c8ffc: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c9000: ori a1,zero,0xc07f */ set(5,cpu(0)|UINT32_C(0x0000c07f));
/* 001c9004: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c9008: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001c900c: lbu a0,0x0(v0) */ set(4,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c9010: or s0,a2,a0 */ set(16,cpu(6)|cpu(4));
/* 001c9014: slt a1,a1,s0 */ set(5,(int64_t)cpu(5)<(int64_t)cpu(16));
/* 001c9018: bne a1,zero,0x001c9040 */ {int taken=(cpu(5)!=cpu(0));/* delay 001c901c */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_001c9040;}}
/* 001c9020: lb a1,0xc(s1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 001c9024: srl v0,s0,0x8 */ set(2,sx((uint32_t)cpu(16)>>8));
/* 001c9028: lb a2,0xd(s1) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000d))));
/* 001c902c: move t1,s3 */ set(9,cpu(19));
/* 001c9030: lb a3,0xe(s1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 001c9034: move a0,sp */ set(4,cpu(29));
/* 001c9038: b 0x001c9060 */ /* delay 001c903c */ lw(8,ea(17,(int32_t)UINT32_C(0x00000014)));goto L_001c9060;
L_001c9040:;
/* 001c9040: lb a2,0xd(s1) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000d))));
/* 001c9044: addiu s0,s0,-0x4000 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffc000)));
/* 001c9048: lb a3,0xe(s1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 001c904c: srl v0,s0,0x8 */ set(2,sx((uint32_t)cpu(16)>>8));
/* 001c9050: lw t0,0x14(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c9054: move t1,s3 */ set(9,cpu(19));
/* 001c9058: move a0,sp */ set(4,cpu(29));
/* 001c905c: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
L_001c9060:;
/* 001c9060: sb v0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001c9064: sb s0,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(16));
/* 001c9068: jal 0x001c7890 */ set(31,0x001c9070u);/* delay 001c906c */ sb(ea(29,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(0));body_001c7890();
/* 001c9070: sw v0,0x14(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c9074: jal 0x001c6128 */ set(31,0x001c907cu);/* delay 001c9078 */ set(4,cpu(16)&UINT32_C(0x0000ffff));body_001c6128();
L_001c907c:;
/* 001c907c: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c9080: move s3,zero */ set(19,cpu(0));
/* 001c9084: jal 0x001c7a88 */ set(31,0x001c908cu);/* delay 001c9088 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));body_001c7a88();
/* 001c908c: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c9090: jal 0x001c7b40 */ set(31,0x001c9098u);/* delay 001c9094 */ lw(5,ea(17,(int32_t)UINT32_C(0x00000008)));body_001c7b40();
/* 001c9098: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
L_001c909c:;
/* 001c909c: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 001c90a0: addu v1,a0,v0 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001c90a4: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c90a8: lbu s0,0x0(v1) */ set(16,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001c90ac: beq s0,zero,0x001c90d8 */ {int taken=(cpu(16)==cpu(0));/* delay 001c90b0 */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_001c90d8;}}
/* 001c90b4: andi v1,s0,0xf0 */ set(3,cpu(16)&UINT32_C(0x000000f0));
/* 001c90b8: li v0,0xf0 */ set(2,sx(UINT32_C(0x000000f0)));
/* 001c90bc: bne v1,v0,0x001c8f90 */ {int taken=(cpu(3)!=cpu(2));/* delay 001c90c0 */ set(2,sx(UINT32_C(0x0000000a)));if(taken){goto L_001c8f90;}}
/* 001c90c4: move a0,s0 */ set(4,cpu(16));
/* 001c90c8: jal 0x001c87c8 */ set(31,0x001c90d0u);/* delay 001c90cc */ set(5,cpu(17));body_001c87c8();
/* 001c90d0: beql v0,zero,0x001c909c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c90d4 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));goto L_001c909c;}}
L_001c90d8:;
/* 001c90d8: jal 0x001c7c10 */ set(31,0x001c90e0u);/* delay 001c90dc */ set(4,sx(UINT32_C(0x00000001)));body_001c7c10();
/* 001c90e0: jal 0x001c7c00 */ set(31,0x001c90e8u);/* delay 001c90e4 */ set(4,sx(UINT32_C(0x00000002)));body_001c7c00();
/* 001c90e8: lw v0,0x14(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c90ec: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c90f0: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c90f4: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c90f8: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c90fc: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9100: jr ra */ {uint64_t target=cpu(31);/* delay 001c9104 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c9188(void){
nocturneEffectAxisNoteEntry(0x001c9188u);
uint64_t incoming=cpu(31);
/* 001c9188: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c918c: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 001c9190: lw v0,0x30(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9194: sll a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)<<4));
/* 001c9198: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001c919c: move a0,sp */ set(4,cpu(29));
/* 001c91a0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c91a4: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 001c91a8: sw a2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 001c91ac: sb a3,0xc(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(7));
/* 001c91b0: sb t0,0xd(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000000d)),(uint8_t)cpu(8));
/* 001c91b4: sb t1,0xe(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000000e)),(uint8_t)cpu(9));
/* 001c91b8: sb t2,0xf(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000000f)),(uint8_t)cpu(10));
/* 001c91bc: sw t3,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(11));
/* 001c91c0: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c91c4: sb v1,0x1d(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000001d)),(uint8_t)cpu(3));
/* 001c91c8: sw zero,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 001c91cc: jal 0x001c8f08 */ set(31,0x001c91d4u);/* delay 001c91d0 */ sb(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(3));body_001c8f08();
/* 001c91d4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c91d8: jr ra */ {uint64_t target=cpu(31);/* delay 001c91dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c9230(void){
nocturneEffectAxisNoteEntry(0x001c9230u);
uint64_t incoming=cpu(31);
/* 001c9230: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 001c9234: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c9238: addu at,at,a0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 001c923c: sw a1,-0x4430(at) */ sw(ea(1,(int32_t)UINT32_C(0xffffbbd0)),(uint32_t)cpu(5));
/* 001c9240: jr ra */ {uint64_t target=cpu(31);/* delay 001c9244 */ checkReturn(target,incoming);return;}
}
static void body_001c96d8(void){
nocturneEffectAxisNoteEntry(0x001c96d8u);
uint64_t incoming=cpu(31);
/* 001c96d8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c96dc: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c96e0: sll a2,a2,0x18 */ set(6,sx((uint32_t)cpu(6)<<24));
/* 001c96e4: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c96e8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c96ec: sra s3,a0,0x18 */ set(19,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c96f0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c96f4: sra a2,a2,0x18 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c96f8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c96fc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9700: bne a1,zero,0x001c9720 */ {int taken=(cpu(5)!=cpu(0));/* delay 001c9704 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_001c9720;}}
/* 001c9708: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c970c: sll v0,s3,0x1 */ set(2,sx((uint32_t)cpu(19)<<1));
/* 001c9710: move a1,zero */ set(5,cpu(0));
/* 001c9714: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c9718: b 0x001c973c */ /* delay 001c971c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x0000657c))));goto L_001c973c;
L_001c9720:;
/* 001c9720: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9724: sll v1,s3,0x1 */ set(3,sx((uint32_t)cpu(19)<<1));
/* 001c9728: addiu v0,v0,0xc */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000000c)));
/* 001c972c: addu a0,v1,v0 */ set(4,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c9730: move v1,a0 */ set(3,cpu(4));
/* 001c9734: lb v0,0x6571(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00006571))));
/* 001c9738: lb a1,0x6570(v1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00006570))));
L_001c973c:;
/* 001c973c: move s0,a1 */ set(16,cpu(5));
/* 001c9740: addu v1,s0,v0 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001c9744: slt v0,s0,v1 */ set(2,(int64_t)cpu(16)<(int64_t)cpu(3));
/* 001c9748: beq v0,zero,0x001c978c */ {int taken=(cpu(2)==cpu(0));/* delay 001c974c */ if(taken){goto L_001c978c;}}
/* 001c9750: sll v0,s3,0x4 */ set(2,sx((uint32_t)cpu(19)<<4));
/* 001c9754: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c9758: subu s0,v1,s0 */ set(16,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 001c975c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c9760: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c9764: addiu at,at,-0x43b0 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffbc50)));
/* 001c9768: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 001c976c: nop  */ 
L_001c9770:;
/* 001c9770: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 001c9774: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001c9778: nop  */ 
/* 001c977c: nop  */ 
/* 001c9780: nop  */ 
/* 001c9784: bne s0,zero,0x001c9770 */ {int taken=(cpu(16)!=cpu(0));/* delay 001c9788 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));if(taken){goto L_001c9770;}}
L_001c978c:;
/* 001c978c: blezl a2,0x001c989c */ {int taken=((int64_t)cpu(6)<=0);if(taken){/* delay 001c9790 */ set(5,cpu(19));goto L_001c989c;}}
/* 001c9794: sll v0,s3,0x4 */ set(2,sx((uint32_t)cpu(19)<<4));
/* 001c9798: move s1,a3 */ set(17,cpu(7));
/* 001c979c: addu v0,a1,v0 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 001c97a0: move s0,a2 */ set(16,cpu(6));
/* 001c97a4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c97a8: lui s2,0x57 */ set(18,sx(UINT32_C(0x00570000)));
/* 001c97ac: addiu s2,s2,-0x43b0 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffbc50)));
/* 001c97b0: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001c97b4: nop  */ 
L_001c97b8:;
/* 001c97b8: jal 0x002a8af8 */ set(31,0x001c97c0u);/* delay 001c97bc */ set(4,sx(UINT32_C(0x00000120)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 001c97c0: move v1,s1 */ set(3,cpu(17));
/* 001c97c4: move a2,v0 */ set(6,cpu(2));
/* 001c97c8: or v0,s1,a2 */ set(2,cpu(17)|cpu(6));
/* 001c97cc: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
/* 001c97d0: beq v0,zero,0x001c9838 */ {int taken=(cpu(2)==cpu(0));/* delay 001c97d4 */ set(4,cpu(6));if(taken){goto L_001c9838;}}
/* 001c97d8: addiu v0,s1,0x120 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000120)));
L_001c97dc:;
/* 001c97dc: ldl a1,0x7(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000007)),1);
/* 001c97e0: ldr a1,0x0(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000000)),0);
/* 001c97e4: ldl a3,0xf(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
/* 001c97e8: ldr a3,0x8(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000008)),0);
/* 001c97ec: ldl t0,0x17(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x00000017)),1);
/* 001c97f0: ldr t0,0x10(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x00000010)),0);
/* 001c97f4: ldl t1,0x1f(v1) */ loadPartial(9,ea(3,(int32_t)UINT32_C(0x0000001f)),1);
/* 001c97f8: ldr t1,0x18(v1) */ loadPartial(9,ea(3,(int32_t)UINT32_C(0x00000018)),0);
/* 001c97fc: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
/* 001c9800: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
/* 001c9804: sdl a3,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),7,1);
/* 001c9808: sdr a3,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),7,0);
/* 001c980c: sdl t0,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),8,1);
/* 001c9810: sdr t0,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),8,0);
/* 001c9814: sdl t1,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),9,1);
/* 001c9818: sdr t1,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),9,0);
/* 001c981c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001c9820: nop  */ 
/* 001c9824: nop  */ 
/* 001c9828: bne v1,v0,0x001c97dc */ {int taken=(cpu(3)!=cpu(2));/* delay 001c982c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_001c97dc;}}
/* 001c9830: b 0x001c9874 */ /* delay 001c9834 */ set(4,sx(UINT32_C(0x00000018)));goto L_001c9874;
L_001c9838:;
/* 001c9838: addiu v0,s1,0x120 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000120)));
L_001c983c:;
/* 001c983c: ld a1,0x0(v1) */ restore(5,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001c9840: ld a3,0x8(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001c9844: ld t0,0x10(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 001c9848: ld t1,0x18(v1) */ restore(9,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 001c984c: sd a1,0x0(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001c9850: sd a3,0x8(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 001c9854: sd t0,0x10(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 001c9858: sd t1,0x18(a0) */ save(9,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001c985c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001c9860: nop  */ 
/* 001c9864: nop  */ 
/* 001c9868: bne v1,v0,0x001c983c */ {int taken=(cpu(3)!=cpu(2));/* delay 001c986c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_001c983c;}}
/* 001c9870: li a0,0x18 */ set(4,sx(UINT32_C(0x00000018)));
L_001c9874:;
/* 001c9874: li a1,0x18 */ set(5,sx(UINT32_C(0x00000018)));
/* 001c9878: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 001c987c: jal 0x001c7408 */ set(31,0x001c9884u);/* delay 001c9880 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));body_001c7408();
/* 001c9884: addiu s1,s1,0x120 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000120)));
/* 001c9888: sw v0,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001c988c: addiu s2,s2,0x4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000004)));
/* 001c9890: bne s0,zero,0x001c97b8 */ {int taken=(cpu(16)!=cpu(0));/* delay 001c9894 */ sh(ea(2,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(19));if(taken){goto L_001c97b8;}}
/* 001c9898: move a1,s3 */ set(5,cpu(19));
L_001c989c:;
/* 001c989c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c98a0: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 001c98a4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c98a8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c98ac: addiu a0,a0,0x5998 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00005998)));
/* 001c98b0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c98b4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c98b8: j 0x002d4748 */ /* delay 001c98bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002d4748u);return;
}
static void body_001c98c0(void){
nocturneEffectAxisNoteEntry(0x001c98c0u);
uint64_t incoming=cpu(31);
/* 001c98c0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c98c4: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c98c8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c98cc: sra s1,a0,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c98d0: sll v1,s1,0x2 */ set(3,sx((uint32_t)cpu(17)<<2));
/* 001c98d4: sll a2,a1,0x18 */ set(6,sx((uint32_t)cpu(5)<<24));
/* 001c98d8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c98dc: lui s3,0x57 */ set(19,sx(UINT32_C(0x00570000)));
/* 001c98e0: addiu s3,s3,-0x42b0 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffbd50)));
/* 001c98e4: addu s3,s3,v1 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(3)));
/* 001c98e8: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c98ec: sra s5,a2,0x18 */ set(21,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c98f0: sll v0,s1,0x3 */ set(2,sx((uint32_t)cpu(17)<<3));
/* 001c98f4: lw a2,0x0(s3) */ lw(6,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 001c98f8: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 001c98fc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9900: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9904: sll s4,v0,0x9 */ set(20,sx((uint32_t)cpu(2)<<9));
/* 001c9908: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c990c: move a1,zero */ set(5,cpu(0));
/* 001c9910: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9914: sll s2,s1,0x1 */ set(18,sx((uint32_t)cpu(17)<<1));
/* 001c9918: bne a2,zero,0x001c9970 */ {int taken=(cpu(6)!=cpu(0));/* delay 001c991c */ set(4,cpu(17));if(taken){goto L_001c9970;}}
/* 001c9920: lw a3,-0x5750(gp) */ lw(7,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9924: addu v0,s2,a3 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(7)));
/* 001c9928: addu a3,a3,s4 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(20)));
/* 001c992c: lb s0,0x657c(v0) */ set(16,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x0000657c))));
/* 001c9930: addiu a3,a3,0x1d7c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00001d7c)));
/* 001c9934: jal 0x001c96d8 */ set(31,0x001c993cu);/* delay 001c9938 */ set(6,cpu(16));body_001c96d8();
/* 001c993c: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9940: sll v0,s0,0x3 */ set(2,sx((uint32_t)cpu(16)<<3));
/* 001c9944: move a0,s1 */ set(4,cpu(17));
/* 001c9948: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c994c: addu a3,v1,s4 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(20)));
/* 001c9950: sll v0,v0,0x5 */ set(2,sx((uint32_t)cpu(2)<<5));
/* 001c9954: addu v1,s2,v1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(3)));
/* 001c9958: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 001c995c: lb a2,0x657d(v1) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x0000657d))));
/* 001c9960: addiu a3,a3,0x1d7c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00001d7c)));
/* 001c9964: jal 0x001c96d8 */ set(31,0x001c996cu);/* delay 001c9968 */ set(5,sx(UINT32_C(0x00000001)));body_001c96d8();
/* 001c996c: lw a2,0x0(s3) */ lw(6,ea(19,(int32_t)UINT32_C(0x00000000)));
L_001c9970:;
/* 001c9970: bne s5,zero,0x001c9988 */ {int taken=(cpu(21)!=cpu(0));/* delay 001c9974 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_001c9988;}}
/* 001c9978: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001c997c: b 0x001c9990 */ /* delay 001c9980 */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000657c))));goto L_001c9990;
L_001c9988:;
/* 001c9988: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001c998c: lbu v1,0x657d(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000657d))));
L_001c9990:;
/* 001c9990: addu v1,a2,v1 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(3)));
/* 001c9994: sw v1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c9998: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c999c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c99a0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c99a4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c99a8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c99ac: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c99b0: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c99b4: jr ra */ {uint64_t target=cpu(31);/* delay 001c99b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c9a98(void){
nocturneEffectAxisNoteEntry(0x001c9a98u);
uint64_t incoming=cpu(31);
/* 001c9a98: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c9a9c: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c9aa0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9aa4: sll s0,a0,0x18 */ set(16,sx((uint32_t)cpu(4)<<24));
/* 001c9aa8: sra a1,a1,0x18 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c9aac: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9ab0: sra s0,s0,0x14 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>20)));
/* 001c9ab4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9ab8: addu s0,s0,a1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 001c9abc: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9ac0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9ac4: sll v1,s0,0x1 */ set(3,sx((uint32_t)cpu(16)<<1));
/* 001c9ac8: addiu v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c9acc: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001c9ad0: addu a0,v1,v0 */ set(4,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c9ad4: move s2,a2 */ set(18,cpu(6));
/* 001c9ad8: move v1,a0 */ set(3,cpu(4));
/* 001c9adc: lbu s1,0x6580(a0) */ set(17,byte(ea(4,(int32_t)UINT32_C(0x00006580))));
/* 001c9ae0: lbu a1,0x6581(v1) */ set(5,byte(ea(3,(int32_t)UINT32_C(0x00006581))));
/* 001c9ae4: sll v0,s1,0x8 */ set(2,sx((uint32_t)cpu(17)<<8));
/* 001c9ae8: or s1,v0,a1 */ set(17,cpu(2)|cpu(5));
/* 001c9aec: move a0,s1 */ set(4,cpu(17));
/* 001c9af0: jal 0x001c6128 */ set(31,0x001c9af8u);/* delay 001c9af4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffe0)));body_001c6128();
/* 001c9af8: lui a0,0x57 */ set(4,sx(UINT32_C(0x00570000)));
/* 001c9afc: addu a0,a0,s0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(16)));
/* 001c9b00: lw a0,-0x43b0(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0xffffbc50)));
/* 001c9b04: jal 0x001c7288 */ set(31,0x001c9b0cu);/* delay 001c9b08 */ set(5,cpu(18));body_001c7288();
/* 001c9b0c: move a1,s1 */ set(5,cpu(17));
/* 001c9b10: move s2,v0 */ set(18,cpu(2));
/* 001c9b14: addiu v0,s1,0x20 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000020)));
/* 001c9b18: lw a0,0x20(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 001c9b1c: move a2,zero */ set(6,cpu(0));
/* 001c9b20: jal 0x001c7088 */ set(31,0x001c9b28u);/* delay 001c9b24 */ sh(ea(4,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));body_001c7088();
/* 001c9b28: move a0,zero */ set(4,cpu(0));
/* 001c9b2c: jal 0x001c7080 */ set(31,0x001c9b34u);/* delay 001c9b30 */ set(5,cpu(17));body_001c7080();
/* 001c9b34: lw v1,0x20(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 001c9b38: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9b3c: sw v0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001c9b40: move v0,s2 */ set(2,cpu(18));
/* 001c9b44: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9b48: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9b4c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9b50: jr ra */ {uint64_t target=cpu(31);/* delay 001c9b54 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c9b58(void){
nocturneEffectAxisNoteEntry(0x001c9b58u);
uint64_t incoming=cpu(31);
/* 001c9b58: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c9b5c: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c9b60: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9b64: sra s1,a0,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c9b68: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9b6c: move s0,a1 */ set(16,cpu(5));
/* 001c9b70: move a0,s1 */ set(4,cpu(17));
/* 001c9b74: move a1,zero */ set(5,cpu(0));
/* 001c9b78: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9b7c: move s2,zero */ set(18,cpu(0));
/* 001c9b80: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9b84: move s3,zero */ set(19,cpu(0));
/* 001c9b88: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9b8c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9b90: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9b94: jal 0x001c98c0 */ set(31,0x001c9b9cu);/* delay 001c9b98 */ set(21,cpu(6));body_001c98c0();
/* 001c9b9c: sll v0,s1,0x1 */ set(2,sx((uint32_t)cpu(17)<<1));
/* 001c9ba0: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9ba4: addiu a0,v0,0x6570 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00006570)));
/* 001c9ba8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001c9bac: lbu v0,0xc(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x0000000c))));
/* 001c9bb0: beq v0,zero,0x001c9c04 */ {int taken=(cpu(2)==cpu(0));/* delay 001c9bb4 */ set(2,cpu(16));if(taken){goto L_001c9c04;}}
/* 001c9bb8: move s4,a0 */ set(20,cpu(4));
/* 001c9bbc: move a2,s0 */ set(6,cpu(16));
L_001c9bc0:;
/* 001c9bc0: move a1,s2 */ set(5,cpu(18));
/* 001c9bc4: move a0,s1 */ set(4,cpu(17));
/* 001c9bc8: jal 0x001c9a98 */ set(31,0x001c9bd0u);/* delay 001c9bcc */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));body_001c9a98();
/* 001c9bd0: move s0,v0 */ set(16,cpu(2));
/* 001c9bd4: addiu v0,s2,0x1 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 001c9bd8: lw v1,0x20(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 001c9bdc: sll v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)<<24));
/* 001c9be0: sra s2,v0,0x18 */ set(18,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 001c9be4: sb s5,0x14(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(21));
/* 001c9be8: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9bec: addu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(20)));
/* 001c9bf0: lbu v1,0xc(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 001c9bf4: slt v1,s3,v1 */ set(3,(int64_t)cpu(19)<(int64_t)cpu(3));
/* 001c9bf8: bne v1,zero,0x001c9bc0 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c9bfc */ set(6,cpu(16));if(taken){goto L_001c9bc0;}}
/* 001c9c00: move v0,s0 */ set(2,cpu(16));
L_001c9c04:;
/* 001c9c04: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9c08: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9c0c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9c10: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9c14: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9c18: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9c1c: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9c20: jr ra */ {uint64_t target=cpu(31);/* delay 001c9c24 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c9c28(void){
nocturneEffectAxisNoteEntry(0x001c9c28u);
uint64_t incoming=cpu(31);
/* 001c9c28: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c9c2c: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c9c30: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9c34: sra s4,a0,0x18 */ set(20,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c9c38: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9c3c: move a0,s4 */ set(4,cpu(20));
/* 001c9c40: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9c44: sll s0,s4,0x1 */ set(16,sx((uint32_t)cpu(20)<<1));
/* 001c9c48: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9c4c: move s1,a1 */ set(17,cpu(5));
/* 001c9c50: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9c54: move s3,zero */ set(19,cpu(0));
/* 001c9c58: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9c5c: move s5,a2 */ set(21,cpu(6));
/* 001c9c60: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9c64: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001c9c68: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9c6c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001c9c70: addiu s0,s0,0x6571 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00006571)));
/* 001c9c74: jal 0x001c98c0 */ set(31,0x001c9c7cu);/* delay 001c9c78 */ set(18,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x0000657c))));body_001c98c0();
/* 001c9c7c: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9c80: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c9c84: lbu v1,0xc(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 001c9c88: beq v1,zero,0x001c9cdc */ {int taken=(cpu(3)==cpu(0));/* delay 001c9c8c */ set(2,cpu(17));if(taken){goto L_001c9cdc;}}
/* 001c9c90: move a2,s1 */ set(6,cpu(17));
/* 001c9c94: nop  */ 
L_001c9c98:;
/* 001c9c98: move a1,s2 */ set(5,cpu(18));
/* 001c9c9c: move a0,s4 */ set(4,cpu(20));
/* 001c9ca0: jal 0x001c9a98 */ set(31,0x001c9ca8u);/* delay 001c9ca4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));body_001c9a98();
/* 001c9ca8: move s1,v0 */ set(17,cpu(2));
/* 001c9cac: addiu v0,s2,0x1 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 001c9cb0: lw v1,0x20(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 001c9cb4: sll v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)<<24));
/* 001c9cb8: sra s2,v0,0x18 */ set(18,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 001c9cbc: sb s5,0x14(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(21));
/* 001c9cc0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9cc4: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c9cc8: lbu v1,0xc(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 001c9ccc: slt v1,s3,v1 */ set(3,(int64_t)cpu(19)<(int64_t)cpu(3));
/* 001c9cd0: bne v1,zero,0x001c9c98 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c9cd4 */ set(6,cpu(17));if(taken){goto L_001c9c98;}}
/* 001c9cd8: move v0,s1 */ set(2,cpu(17));
L_001c9cdc:;
/* 001c9cdc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9ce0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9ce4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9ce8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9cec: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9cf0: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9cf4: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9cf8: jr ra */ {uint64_t target=cpu(31);/* delay 001c9cfc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c9d00(void){
nocturneEffectAxisNoteEntry(0x001c9d00u);
uint64_t incoming=cpu(31);
/* 001c9d00: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c9d04: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9d08: sll s0,a0,0x18 */ set(16,sx((uint32_t)cpu(4)<<24));
/* 001c9d0c: sra s0,s0,0x18 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>24)));
/* 001c9d10: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9d14: move a0,s0 */ set(4,cpu(16));
/* 001c9d18: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9d1c: jal 0x001c9c28 */ set(31,0x001c9d24u);/* delay 001c9d20 */ set(17,cpu(6));body_001c9c28();
/* 001c9d24: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 001c9d28: move a1,v0 */ set(5,cpu(2));
/* 001c9d2c: lw a3,0x20(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 001c9d30: move a0,s0 */ set(4,cpu(16));
/* 001c9d34: addiu v1,v1,0x8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 001c9d38: move a2,s1 */ set(6,cpu(17));
/* 001c9d3c: sw v1,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 001c9d40: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9d44: lw v0,0xc(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x0000000c)));
/* 001c9d48: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9d4c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9d50: addiu v0,v0,0x8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000008)));
/* 001c9d54: sw v0,0xc(a3) */ sw(ea(7,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001c9d58: j 0x001c9b58 */ /* delay 001c9d5c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_001c9b58();return;
}
static void body_001c9d60(void){
nocturneEffectAxisNoteEntry(0x001c9d60u);
uint64_t incoming=cpu(31);
/* 001c9d60: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001c9d64: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c9d68: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9d6c: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c9d70: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9d74: addiu t1,a0,0x6650 */ set(9,sx((uint32_t)cpu(4)+UINT32_C(0x00006650)));
/* 001c9d78: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9d7c: move s2,a3 */ set(18,cpu(7));
/* 001c9d80: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c9d84: move s3,a2 */ set(19,cpu(6));
/* 001c9d88: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c9d8c: move s4,sp */ set(20,cpu(29));
/* 001c9d90: sd s8,0x48(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c9d94: move s8,sp */ set(30,cpu(29));
/* 001c9d98: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c9d9c: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c9da0: sra s1,a1,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c9da4: move a3,zero */ set(7,cpu(0));
/* 001c9da8: lw t0,-0x5750(gp) */ lw(8,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9dac: move a2,zero */ set(6,cpu(0));
/* 001c9db0: addu v0,t0,t1 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(9)));
/* 001c9db4: lbu v1,0x4(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 001c9db8: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 001c9dbc: addiu v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 001c9dc0: andi v0,v0,0x3f0 */ set(2,cpu(2)&UINT32_C(0x000003f0));
/* 001c9dc4: subu sp,sp,v0 */ set(29,sx((uint32_t)cpu(29)-(uint32_t)cpu(2)));
/* 001c9dc8: beq v1,zero,0x001c9e44 */ {int taken=(cpu(3)==cpu(0));/* delay 001c9dcc */ set(16,cpu(29));if(taken){goto L_001c9e44;}}
/* 001c9dd0: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001c9dd4: move a1,sp */ set(5,cpu(29));
/* 001c9dd8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c9ddc: sll a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)<<2));
L_001c9de0:;
/* 001c9de0: addiu v0,t0,0x4 */ set(2,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));
/* 001c9de4: addu v1,a0,v0 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001c9de8: move v0,v1 */ set(2,cpu(3));
/* 001c9dec: lbu v0,0x6600(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0x00006600))));
/* 001c9df0: bnel v0,zero,0x001c9e08 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c9df4 */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_001c9e08;}}
/* 001c9df8: lbu v0,0x6601(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00006601))));
/* 001c9dfc: b 0x001c9e20 */ /* delay 001c9e00 */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_001c9e20;
L_001c9e08:;
/* 001c9e08: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 001c9e0c: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001c9e10: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9e14: addu v0,a0,v0 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001c9e18: lbu v1,0x6605(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00006605))));
/* 001c9e1c: sb v1,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
L_001c9e20:;
/* 001c9e20: lw t0,-0x5750(gp) */ lw(8,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9e24: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 001c9e28: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 001c9e2c: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001c9e30: addu v1,t0,t1 */ set(3,sx((uint32_t)cpu(8)+(uint32_t)cpu(9)));
/* 001c9e34: lbu v0,0x4(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000004))));
/* 001c9e38: slt v0,a3,v0 */ set(2,(int64_t)cpu(7)<(int64_t)cpu(2));
/* 001c9e3c: bne v0,zero,0x001c9de0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c9e40 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));if(taken){goto L_001c9de0;}}
L_001c9e44:;
/* 001c9e44: addu v0,s0,a2 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));
/* 001c9e48: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c9e4c: jal 0x001c7c00 */ set(31,0x001c9e54u);/* delay 001c9e50 */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));body_001c7c00();
/* 001c9e54: sll a2,s2,0x18 */ set(6,sx((uint32_t)cpu(18)<<24));
/* 001c9e58: move a1,s1 */ set(5,cpu(17));
/* 001c9e5c: sra a2,a2,0x18 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c9e60: move t0,s3 */ set(8,cpu(19));
/* 001c9e64: move a3,zero */ set(7,cpu(0));
/* 001c9e68: jal 0x001c7828 */ set(31,0x001c9e70u);/* delay 001c9e6c */ set(4,cpu(16));body_001c7828();
/* 001c9e70: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c9e74: jal 0x001c7c10 */ set(31,0x001c9e7cu);/* delay 001c9e78 */ set(16,cpu(2));body_001c7c10();
/* 001c9e7c: move a0,s0 */ set(4,cpu(16));
/* 001c9e80: jal 0x001c7a88 */ set(31,0x001c9e88u);/* delay 001c9e84 */ set(5,sx(UINT32_C(0x00000004)));body_001c7a88();
/* 001c9e88: move sp,s4 */ set(29,cpu(20));
/* 001c9e8c: move v0,s0 */ set(2,cpu(16));
/* 001c9e90: move sp,s8 */ set(29,cpu(30));
/* 001c9e94: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9e98: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9e9c: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9ea0: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c9ea4: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c9ea8: ld s8,0x48(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c9eac: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c9eb0: jr ra */ {uint64_t target=cpu(31);/* delay 001c9eb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_001ca9c0(void){
nocturneEffectAxisNoteEntry(0x001ca9c0u);
uint64_t incoming=cpu(31);
/* 001ca9c0: jr ra */ {uint64_t target=cpu(31);/* delay 001ca9c4 */ set(2,cpu(4));checkReturn(target,incoming);return;}
}
static void body_001ca9c8(void){
nocturneEffectAxisNoteEntry(0x001ca9c8u);
uint64_t incoming=cpu(31);
/* 001ca9c8: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001ca9cc: lw a3,0x4(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001ca9d0: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001ca9d4: addu a2,a0,v0 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001ca9d8: addu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 001ca9dc: sw a2,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
/* 001ca9e0: addu v1,v0,v1 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001ca9e4: addu v0,a0,v0 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001ca9e8: addu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 001ca9ec: sw v0,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 001ca9f0: jr ra */ {uint64_t target=cpu(31);/* delay 001ca9f4 */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_001caa18(void){
nocturneEffectAxisNoteEntry(0x001caa18u);
uint64_t incoming=cpu(31);
/* 001caa18: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001caa1c: sll a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)<<2));
/* 001caa20: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001caa24: move s0,a3 */ set(16,cpu(7));
/* 001caa28: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001caa2c: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001caa30: move s3,a0 */ set(19,cpu(4));
/* 001caa34: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001caa38: move a0,a2 */ set(4,cpu(6));
/* 001caa3c: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001caa40: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001caa44: lw s2,0x0(s0) */ lw(18,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001caa48: addu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 001caa4c: lwl v0,0x3(a1) */ loadPartial32(2,ea(5,(int32_t)UINT32_C(0x00000003)),1);
/* 001caa50: lwr v0,0x0(a1) */ loadPartial32(2,ea(5,(int32_t)UINT32_C(0x00000000)),0);
/* 001caa54: swl v0,0x3(sp) */ storePartial32(ea(29,(int32_t)UINT32_C(0x00000003)),2,1);
/* 001caa58: swr v0,0x0(sp) */ storePartial32(ea(29,(int32_t)UINT32_C(0x00000000)),2,0);
/* 001caa5c: lwl v0,0x7(a1) */ loadPartial32(2,ea(5,(int32_t)UINT32_C(0x00000007)),1);
/* 001caa60: lwr v0,0x4(a1) */ loadPartial32(2,ea(5,(int32_t)UINT32_C(0x00000004)),0);
/* 001caa64: swl v0,0x7(sp) */ storePartial32(ea(29,(int32_t)UINT32_C(0x00000007)),2,1);
/* 001caa68: swr v0,0x4(sp) */ storePartial32(ea(29,(int32_t)UINT32_C(0x00000004)),2,0);
/* 001caa6c: jal 0x001ca9c0 */ set(31,0x001caa74u);/* delay 001caa70 */ set(17,cpu(0));body_001ca9c0();
/* 001caa74: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001caa78: lui a3,0x1 */ set(7,sx(UINT32_C(0x00010000)));
/* 001caa7c: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001caa80: addiu t1,s2,0x2 */ set(9,sx((uint32_t)cpu(18)+UINT32_C(0x00000002)));
/* 001caa84: srl v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)>>4));
/* 001caa88: lw a1,0x4(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 001caa8c: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 001caa90: andi a2,a0,0xf */ set(6,cpu(4)&UINT32_C(0x0000000f));
/* 001caa94: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001caa98: subu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));
/* 001caa9c: lhu v1,0x0(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001caaa0: move t0,v0 */ set(8,cpu(2));
/* 001caaa4: move a0,t1 */ set(4,cpu(9));
/* 001caaa8: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 001caaac: or v1,v1,a3 */ set(3,cpu(3)|cpu(7));
/* 001caab0: srav a2,v1,a2 */ set(6,sx((uint32_t)((int32_t)(uint32_t)cpu(3)>>((uint32_t)cpu(6)&31u))));
/* 001caab4: andi v1,a2,0x1 */ set(3,cpu(6)&UINT32_C(0x00000001));
L_001caab8:;
/* 001caab8: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 001caabc: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001caac0: lhu a0,0x0(v1) */ set(4,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001caac4: sll v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)<<1));
/* 001caac8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001caacc: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 001caad0: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001caad4: addiu a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 001caad8: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 001caadc: bne v1,zero,0x001caaf8 */ {int taken=(cpu(3)!=cpu(0));/* delay 001caae0 */ set(6,sx((uint32_t)cpu(6)>>1));if(taken){goto L_001caaf8;}}
/* 001caae4: lbu v1,0x2(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000002))));
/* 001caae8: move a0,t1 */ set(4,cpu(9));
/* 001caaec: addu v0,s3,s1 */ set(2,sx((uint32_t)cpu(19)+(uint32_t)cpu(17)));
/* 001caaf0: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 001caaf4: sb v1,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
L_001caaf8:;
/* 001caaf8: bne a2,t2,0x001cab0c */ {int taken=(cpu(6)!=cpu(10));/* delay 001caafc */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));if(taken){goto L_001cab0c;}}
/* 001cab00: addiu t0,t0,0x2 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000002)));
/* 001cab04: lhu v0,0x0(t0) */ set(2,half(ea(8,(int32_t)UINT32_C(0x00000000))));
/* 001cab08: or a2,v0,a3 */ set(6,cpu(2)|cpu(7));
L_001cab0c:;
/* 001cab0c: bne a1,zero,0x001caab8 */ {int taken=(cpu(5)!=cpu(0));/* delay 001cab10 */ set(3,cpu(6)&UINT32_C(0x00000001));if(taken){goto L_001caab8;}}
/* 001cab14: move v0,s1 */ set(2,cpu(17));
/* 001cab18: sw s1,-0x22d0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdd30)),(uint32_t)cpu(17));
/* 001cab1c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cab20: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cab24: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cab28: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001cab2c: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001cab30: jr ra */ {uint64_t target=cpu(31);/* delay 001cab34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001cabd8(void){
nocturneEffectAxisNoteEntry(0x001cabd8u);
uint64_t incoming=cpu(31);
/* 001cabd8: lw a1,0x4(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001cabdc: lw v1,0x0(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 001cabe0: beq v1,zero,0x001cabf8 */ {int taken=(cpu(3)==cpu(0));/* delay 001cabe4 */ set(2,cpu(0));if(taken){goto L_001cabf8;}}
/* 001cabe8: lw v1,0x4(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 001cabec: addiu v0,a1,0x8 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 001cabf0: sw v1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001cabf4: sw zero,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
L_001cabf8:;
/* 001cabf8: jr ra */ {uint64_t target=cpu(31);/* delay 001cabfc */ checkReturn(target,incoming);return;}
}
static void body_001cdd78(void){
nocturneEffectAxisNoteEntry(0x001cdd78u);
uint64_t incoming=cpu(31);
/* 001cdd78: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001cdd7c: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001cdd80: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cdd84: move s3,a1 */ set(19,cpu(5));
/* 001cdd88: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cdd8c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cdd90: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cdd94: bltz a0,0x001cde38 */ {int taken=((int64_t)cpu(4)<0);/* delay 001cdd98 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_001cde38;}}
/* 001cdd9c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001cdda0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001cdda4: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
/* 001cdda8: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 001cddac: lw s1,-0x4174(s1) */ lw(17,ea(17,(int32_t)UINT32_C(0xffffbe8c)));
/* 001cddb0: addiu s0,s1,0x24 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0x00000024)));
/* 001cddb4: addiu s2,s1,0x14 */ set(18,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));
/* 001cddb8: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001cddbc: beq v0,zero,0x001cddd0 */ {int taken=(cpu(2)==cpu(0));/* delay 001cddc0 */ set(4,cpu(2));if(taken){goto L_001cddd0;}}
/* 001cddc4: jal 0x001c6ff8 */ set(31,0x001cddccu);/* delay 001cddc8 */ body_001c6ff8();
/* 001cddcc: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
L_001cddd0:;
/* 001cddd0: move a0,s0 */ set(4,cpu(16));
/* 001cddd4: jal 0x001cfc80 */ set(31,0x001cdddcu);/* delay 001cddd8 */ set(5,cpu(0));body_001cfc80();
/* 001cdddc: li a0,-0x8 */ set(4,sx(UINT32_C(0xfffffff8)));
/* 001cdde0: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001cdde4: lui v1,0xfffd */ set(3,sx(UINT32_C(0xfffd0000)));
/* 001cdde8: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 001cddec: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 001cddf0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001cddf4: beq s3,zero,0x001cde38 */ {int taken=(cpu(19)==cpu(0));/* delay 001cddf8 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_001cde38;}}
/* 001cddfc: lw v0,0x8(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 001cde00: beq v0,zero,0x001cde14 */ {int taken=(cpu(2)==cpu(0));/* delay 001cde04 */ set(4,cpu(2));if(taken){goto L_001cde14;}}
/* 001cde08: jal 0x001c6ff8 */ set(31,0x001cde10u);/* delay 001cde0c */ body_001c6ff8();
/* 001cde10: sw zero,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
L_001cde14:;
/* 001cde14: move a0,s2 */ set(4,cpu(18));
/* 001cde18: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cde1c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cde20: move a1,zero */ set(5,cpu(0));
/* 001cde24: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cde28: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cde2c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cde30: j 0x001cfc58 */ /* delay 001cde34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_001cfc58();return;
L_001cde38:;
/* 001cde38: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cde3c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cde40: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cde44: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cde48: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cde4c: jr ra */ {uint64_t target=cpu(31);/* delay 001cde50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001cf178(void){
nocturneEffectAxisNoteEntry(0x001cf178u);
uint64_t incoming=cpu(31);
/* 001cf178: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001cf17c: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 001cf180: addiu v0,v0,0x20 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 001cf184: jr ra */ {uint64_t target=cpu(31);/* delay 001cf188 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));checkReturn(target,incoming);return;}
}
static void body_001cf1a8(void){
nocturneEffectAxisNoteEntry(0x001cf1a8u);
uint64_t incoming=cpu(31);
/* 001cf1a8: bltz a1,0x001cf1bc */ {int taken=((int64_t)cpu(5)<0);/* delay 001cf1ac */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000018))));if(taken){goto L_001cf1bc;}}
/* 001cf1b0: slt v0,a1,v0 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(2));
/* 001cf1b4: bne v0,zero,0x001cf1c8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001cf1b8 */ set(3,sx((uint32_t)cpu(5)<<2));if(taken){goto L_001cf1c8;}}
L_001cf1bc:;
/* 001cf1bc: jr ra */ {uint64_t target=cpu(31);/* delay 001cf1c0 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_001cf1c8:;
/* 001cf1c8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001cf1cc: jr ra */ {uint64_t target=cpu(31);/* delay 001cf1d0 */ lw(2,ea(3,(int32_t)UINT32_C(0x0000001c)));checkReturn(target,incoming);return;}
}
static void body_001cf440(void){
nocturneEffectAxisNoteEntry(0x001cf440u);
uint64_t incoming=cpu(31);
/* 001cf440: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001cf444: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cf448: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf44c: move s0,zero */ set(16,cpu(0));
/* 001cf450: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf454: move s1,a0 */ set(17,cpu(4));
/* 001cf458: lw a1,0x0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001cf45c: nop  */ 
L_001cf460:;
/* 001cf460: addiu s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
/* 001cf464: move a0,s0 */ set(4,cpu(16));
/* 001cf468: jal 0x001c9230 */ set(31,0x001cf470u);/* delay 001cf46c */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));body_001c9230();
/* 001cf470: slti v0,s0,0x20 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000020));
/* 001cf474: bnel v0,zero,0x001cf460 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001cf478 */ lw(5,ea(17,(int32_t)UINT32_C(0x00000000)));goto L_001cf460;}}
/* 001cf47c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf480: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf484: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cf488: jr ra */ {uint64_t target=cpu(31);/* delay 001cf48c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001cfc58(void){
nocturneEffectAxisNoteEntry(0x001cfc58u);
uint64_t incoming=cpu(31);
/* 001cfc58: beq a1,zero,0x001cfc6c */ {int taken=(cpu(5)==cpu(0));/* delay 001cfc5c */ set(3,sx(UINT32_C(0x000009b0)));if(taken){goto L_001cfc6c;}}
/* 001cfc60: li v0,0x430 */ set(2,sx(UINT32_C(0x00000430)));
/* 001cfc64: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001cfc68: sw v1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
L_001cfc6c:;
/* 001cfc6c: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 001cfc70: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001cfc74: jr ra */ {uint64_t target=cpu(31);/* delay 001cfc78 */ sh(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_001cfc80(void){
nocturneEffectAxisNoteEntry(0x001cfc80u);
uint64_t incoming=cpu(31);
/* 001cfc80: beq a1,zero,0x001cfc94 */ {int taken=(cpu(5)==cpu(0));/* delay 001cfc84 */ set(3,sx(UINT32_C(0x00000a88)));if(taken){goto L_001cfc94;}}
/* 001cfc88: li v0,0x4b0 */ set(2,sx(UINT32_C(0x000004b0)));
/* 001cfc8c: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001cfc90: sw v1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
L_001cfc94:;
/* 001cfc94: li v0,-0x80 */ set(2,sx(UINT32_C(0xffffff80)));
/* 001cfc98: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001cfc9c: sb v0,0x15(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000015)),(uint8_t)cpu(2));
/* 001cfca0: sw zero,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 001cfca4: sb zero,0x10(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000010)),(uint8_t)cpu(0));
/* 001cfca8: sb zero,0x11(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000011)),(uint8_t)cpu(0));
/* 001cfcac: sh zero,0x16(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(0));
/* 001cfcb0: sh zero,0x18(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000018)),(uint16_t)cpu(0));
/* 001cfcb4: sh zero,0x1a(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000001a)),(uint16_t)cpu(0));
/* 001cfcb8: sb zero,0x12(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000012)),(uint8_t)cpu(0));
/* 001cfcbc: sb zero,0x13(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000013)),(uint8_t)cpu(0));
/* 001cfcc0: jr ra */ {uint64_t target=cpu(31);/* delay 001cfcc4 */ sb(ea(4,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_00242ae8(void){
nocturneEffectAxisNoteEntry(0x00242ae8u);
uint64_t incoming=cpu(31);
/* 00242ae8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00242aec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242af0: move s0,a0 */ set(16,cpu(4));
/* 00242af4: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242af8: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00242afc: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00242b00: jal 0x00243ee0 */ set(31,0x00242b08u);/* delay 00242b04 */ set(5,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x00243ee0u);
/* 00242b08: lhu a0,0x14(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 00242b0c: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00242b10: jal 0x002d1b88 */ set(31,0x00242b18u);/* delay 00242b14 */ set(4,sx((uint32_t)cpu(4)<<1));nocturneBattleActionSkillCall(0x002d1b88u);
/* 00242b18: ori a1,zero,0xffe0 */ set(5,cpu(0)|UINT32_C(0x0000ffe0));
/* 00242b1c: dsll32 a1,a1,0xe */ set(5,cpu(5)<<46);
/* 00242b20: move a0,v0 */ set(4,cpu(2));
/* 00242b24: jal 0x002d18b0 */ set(31,0x00242b2cu);/* delay 00242b28 */ nocturneBattleActionSkillCall(0x002d18b0u);
/* 00242b2c: move a0,v0 */ set(4,cpu(2));
/* 00242b30: jal 0x002d1c40 */ set(31,0x00242b38u);/* delay 00242b34 */ nocturneBattleActionSkillCall(0x002d1c40u);
/* 00242b38: move a1,v0 */ set(5,cpu(2));
/* 00242b3c: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00242b40: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00242b44: bne v0,zero,0x00242b58 */ {int taken=(cpu(2)!=cpu(0));/* delay 00242b48 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00242b58;}}
/* 00242b4c: slti v1,a1,0x3e8 */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x000003e8));
/* 00242b50: li v0,0x3e7 */ set(2,sx(UINT32_C(0x000003e7)));
/* 00242b54: movz a1,v0,v1 */ if(cpu(3)==0){set(5,cpu(2));}
L_00242b58:;
/* 00242b58: move v0,a1 */ set(2,cpu(5));
/* 00242b5c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242b60: jr ra */ {uint64_t target=cpu(31);/* delay 00242b64 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00242cb0(void){
nocturneEffectAxisNoteEntry(0x00242cb0u);
uint64_t incoming=cpu(31);
/* 00242cb0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00242cb4: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 00242cb8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242cbc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242cc0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00242cc4: jal 0x00243ee0 */ set(31,0x00242cccu);/* delay 00242cc8 */ set(17,cpu(4));nocturneBattleActionSkillCall(0x00243ee0u);
/* 00242ccc: move a0,s1 */ set(4,cpu(17));
/* 00242cd0: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 00242cd4: jal 0x00243ee0 */ set(31,0x00242cdcu);/* delay 00242cd8 */ set(16,cpu(2));nocturneBattleActionSkillCall(0x00243ee0u);
/* 00242cdc: addiu v0,v0,0x5 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000005)));
/* 00242ce0: lhu a0,0x14(s1) */ set(4,half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 00242ce4: srl v1,v0,0x1f */ set(3,sx((uint32_t)cpu(2)>>31));
/* 00242ce8: sll s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)<<1));
/* 00242cec: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00242cf0: addu s0,s0,a0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(4)));
/* 00242cf4: sra v0,v0,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 00242cf8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242cfc: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00242d00: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00242d04: addiu v0,s0,0xf */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x0000000f)));
/* 00242d08: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242d0c: jr ra */ {uint64_t target=cpu(31);/* delay 00242d10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00242d50(void){
nocturneEffectAxisNoteEntry(0x00242d50u);
uint64_t incoming=cpu(31);
/* 00242d50: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00242d54: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 00242d58: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242d5c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242d60: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00242d64: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00242d68: jal 0x00243ee0 */ set(31,0x00242d70u);/* delay 00242d6c */ set(18,cpu(4));nocturneBattleActionSkillCall(0x00243ee0u);
/* 00242d70: move s0,v0 */ set(16,cpu(2));
/* 00242d74: move a0,s2 */ set(4,cpu(18));
/* 00242d78: jal 0x00243ee0 */ set(31,0x00242d80u);/* delay 00242d7c */ set(5,sx(UINT32_C(0x00000005)));nocturneBattleActionSkillCall(0x00243ee0u);
/* 00242d80: addiu a0,s0,0x5 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000005)));
/* 00242d84: jal 0x002d1b88 */ set(31,0x00242d8cu);/* delay 00242d88 */ set(17,cpu(2));nocturneBattleActionSkillCall(0x002d1b88u);
/* 00242d8c: ori a1,zero,0xffe0 */ set(5,cpu(0)|UINT32_C(0x0000ffe0));
/* 00242d90: dsll32 a1,a1,0xe */ set(5,cpu(5)<<46);
/* 00242d94: move a0,v0 */ set(4,cpu(2));
/* 00242d98: jal 0x002d18b0 */ set(31,0x00242da0u);/* delay 00242d9c */ nocturneBattleActionSkillCall(0x002d18b0u);
/* 00242da0: move s0,v0 */ set(16,cpu(2));
/* 00242da4: jal 0x002d1b88 */ set(31,0x00242dacu);/* delay 00242da8 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000005)));nocturneBattleActionSkillCall(0x002d1b88u);
/* 00242dac: move a1,v0 */ set(5,cpu(2));
/* 00242db0: move a0,s0 */ set(4,cpu(16));
/* 00242db4: jal 0x002d17f0 */ set(31,0x00242dbcu);/* delay 00242db8 */ nocturneBattleActionSkillCall(0x002d17f0u);
/* 00242dbc: lhu a0,0x14(s2) */ set(4,half(ea(18,(int32_t)UINT32_C(0x00000014))));
/* 00242dc0: move s0,v0 */ set(16,cpu(2));
/* 00242dc4: jal 0x002d1b88 */ set(31,0x00242dccu);/* delay 00242dc8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000005)));nocturneBattleActionSkillCall(0x002d1b88u);
/* 00242dcc: move a0,s0 */ set(4,cpu(16));
/* 00242dd0: move a1,v0 */ set(5,cpu(2));
/* 00242dd4: jal 0x002d17f0 */ set(31,0x00242ddcu);/* delay 00242dd8 */ nocturneBattleActionSkillCall(0x002d17f0u);
/* 00242ddc: move a0,v0 */ set(4,cpu(2));
/* 00242de0: jal 0x002d1c40 */ set(31,0x00242de8u);/* delay 00242de4 */ nocturneBattleActionSkillCall(0x002d1c40u);
/* 00242de8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00242dec: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00242df0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00242df4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00242df8: jr ra */ {uint64_t target=cpu(31);/* delay 00242dfc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00243c28(void){
nocturneEffectAxisNoteEntry(0x00243c28u);
uint64_t incoming=cpu(31);
/* 00243c28: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00243c2c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243c30: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243c34: move s1,a0 */ set(17,cpu(4));
/* 00243c38: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243c3c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00243c40: jal 0x00242a88 */ set(31,0x00243c48u);/* delay 00243c44 */ set(18,cpu(0));nocturneBattleActionSkillCall(0x00242a88u);
/* 00243c48: move s0,v0 */ set(16,cpu(2));
/* 00243c4c: move a0,s1 */ set(4,cpu(17));
/* 00243c50: jal 0x00243f40 */ set(31,0x00243c58u);/* delay 00243c54 */ set(5,sx(UINT32_C(0x00000122)));nocturneBattleActionSkillCall(0x00243f40u);
/* 00243c58: move a0,s1 */ set(4,cpu(17));
/* 00243c5c: sll v1,s0,0x2 */ set(3,sx((uint32_t)cpu(16)<<2));
/* 00243c60: li a2,0x64 */ set(6,sx(UINT32_C(0x00000064)));
/* 00243c64: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00243c68: li a1,0x123 */ set(5,sx(UINT32_C(0x00000123)));
/* 00243c6c: beq v0,zero,0x00243c88 */ {int taken=(cpu(2)==cpu(0));/* delay 00243c70 */ set(3,sx((uint32_t)cpu(3)<<1));if(taken){goto L_00243c88;}}
/* 00243c74: divu v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),0,0);
/* 00243c78: beql a2,zero,0x00243c80 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 00243c7c */ nocturneCompilerArithmeticTrap(7u);goto L_00243c80;}}
L_00243c80:;
/* 00243c80: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243c84: move s2,v0 */ set(18,cpu(2));
L_00243c88:;
/* 00243c88: jal 0x00243f40 */ set(31,0x00243c90u);/* delay 00243c8c */ nocturneBattleActionSkillCall(0x00243f40u);
/* 00243c90: beq v0,zero,0x00243cb8 */ {int taken=(cpu(2)==cpu(0));/* delay 00243c94 */ set(3,sx(UINT32_C(0x00000064)));if(taken){goto L_00243cb8;}}
/* 00243c98: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 00243c9c: beql v1,zero,0x00243ca4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00243ca0 */ nocturneCompilerArithmeticTrap(7u);goto L_00243ca4;}}
L_00243ca4:;
/* 00243ca4: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 00243ca8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00243cac: divu v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),0,0);
/* 00243cb0: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243cb4: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00243cb8:;
/* 00243cb8: move a0,s1 */ set(4,cpu(17));
/* 00243cbc: jal 0x00243f40 */ set(31,0x00243cc4u);/* delay 00243cc0 */ set(5,sx(UINT32_C(0x00000124)));nocturneBattleActionSkillCall(0x00243f40u);
/* 00243cc4: sll v1,s0,0x4 */ set(3,sx((uint32_t)cpu(16)<<4));
/* 00243cc8: li a0,0x64 */ set(4,sx(UINT32_C(0x00000064)));
/* 00243ccc: beq v0,zero,0x00243cec */ {int taken=(cpu(2)==cpu(0));/* delay 00243cd0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));if(taken){goto L_00243cec;}}
/* 00243cd4: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 00243cd8: beql a0,zero,0x00243ce0 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00243cdc */ nocturneCompilerArithmeticTrap(7u);goto L_00243ce0;}}
L_00243ce0:;
/* 00243ce0: divu v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),0,0);
/* 00243ce4: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243ce8: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00243cec:;
/* 00243cec: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00243cf0: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 00243cf4: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00243cf8: bne v0,zero,0x00243d08 */ {int taken=(cpu(2)!=cpu(0));/* delay 00243cfc */ set(3,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x000003e8));if(taken){goto L_00243d08;}}
/* 00243d00: li v0,0x3e7 */ set(2,sx(UINT32_C(0x000003e7)));
/* 00243d04: movz s0,v0,v1 */ if(cpu(3)==0){set(16,cpu(2));}
L_00243d08:;
/* 00243d08: move v0,s0 */ set(2,cpu(16));
/* 00243d0c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243d10: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243d14: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243d18: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00243d1c: jr ra */ {uint64_t target=cpu(31);/* delay 00243d20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00243d28(void){
nocturneEffectAxisNoteEntry(0x00243d28u);
uint64_t incoming=cpu(31);
/* 00243d28: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00243d2c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243d30: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243d34: move s1,a0 */ set(17,cpu(4));
/* 00243d38: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243d3c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00243d40: jal 0x00242ae8 */ set(31,0x00243d48u);/* delay 00243d44 */ set(18,cpu(0));body_00242ae8();
/* 00243d48: move s0,v0 */ set(16,cpu(2));
/* 00243d4c: move a0,s1 */ set(4,cpu(17));
/* 00243d50: jal 0x00243f40 */ set(31,0x00243d58u);/* delay 00243d54 */ set(5,sx(UINT32_C(0x00000125)));nocturneBattleActionSkillCall(0x00243f40u);
/* 00243d58: move a0,s1 */ set(4,cpu(17));
/* 00243d5c: sll v1,s0,0x2 */ set(3,sx((uint32_t)cpu(16)<<2));
/* 00243d60: li a2,0x64 */ set(6,sx(UINT32_C(0x00000064)));
/* 00243d64: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00243d68: li a1,0x126 */ set(5,sx(UINT32_C(0x00000126)));
/* 00243d6c: beq v0,zero,0x00243d88 */ {int taken=(cpu(2)==cpu(0));/* delay 00243d70 */ set(3,sx((uint32_t)cpu(3)<<1));if(taken){goto L_00243d88;}}
/* 00243d74: divu v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),0,0);
/* 00243d78: beql a2,zero,0x00243d80 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 00243d7c */ nocturneCompilerArithmeticTrap(7u);goto L_00243d80;}}
L_00243d80:;
/* 00243d80: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243d84: move s2,v0 */ set(18,cpu(2));
L_00243d88:;
/* 00243d88: jal 0x00243f40 */ set(31,0x00243d90u);/* delay 00243d8c */ nocturneBattleActionSkillCall(0x00243f40u);
/* 00243d90: beq v0,zero,0x00243db8 */ {int taken=(cpu(2)==cpu(0));/* delay 00243d94 */ set(3,sx(UINT32_C(0x00000064)));if(taken){goto L_00243db8;}}
/* 00243d98: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 00243d9c: beql v1,zero,0x00243da4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00243da0 */ nocturneCompilerArithmeticTrap(7u);goto L_00243da4;}}
L_00243da4:;
/* 00243da4: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 00243da8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00243dac: divu v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),0,0);
/* 00243db0: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243db4: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00243db8:;
/* 00243db8: move a0,s1 */ set(4,cpu(17));
/* 00243dbc: jal 0x00243f40 */ set(31,0x00243dc4u);/* delay 00243dc0 */ set(5,sx(UINT32_C(0x00000127)));nocturneBattleActionSkillCall(0x00243f40u);
/* 00243dc4: sll v1,s0,0x4 */ set(3,sx((uint32_t)cpu(16)<<4));
/* 00243dc8: li a0,0x64 */ set(4,sx(UINT32_C(0x00000064)));
/* 00243dcc: beq v0,zero,0x00243dec */ {int taken=(cpu(2)==cpu(0));/* delay 00243dd0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));if(taken){goto L_00243dec;}}
/* 00243dd4: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 00243dd8: beql a0,zero,0x00243de0 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00243ddc */ nocturneCompilerArithmeticTrap(7u);goto L_00243de0;}}
L_00243de0:;
/* 00243de0: divu v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),0,0);
/* 00243de4: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00243de8: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00243dec:;
/* 00243dec: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00243df0: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 00243df4: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00243df8: bne v0,zero,0x00243e08 */ {int taken=(cpu(2)!=cpu(0));/* delay 00243dfc */ set(3,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x000003e8));if(taken){goto L_00243e08;}}
/* 00243e00: li v0,0x3e7 */ set(2,sx(UINT32_C(0x000003e7)));
/* 00243e04: movz s0,v0,v1 */ if(cpu(3)==0){set(16,cpu(2));}
L_00243e08:;
/* 00243e08: move v0,s0 */ set(2,cpu(16));
/* 00243e0c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00243e10: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00243e14: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00243e18: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00243e1c: jr ra */ {uint64_t target=cpu(31);/* delay 00243e20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00244238(void){
nocturneEffectAxisNoteEntry(0x00244238u);
uint64_t incoming=cpu(31);
/* 00244238: lw a2,-0x5750(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024423c: lui a1,0x98 */ set(5,sx(UINT32_C(0x00980000)));
/* 00244240: ori a1,a1,0x967f */ set(5,cpu(5)|UINT32_C(0x0000967f));
/* 00244244: lw v0,0xa48(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000a48)));
/* 00244248: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0024424c: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00244250: movn v0,zero,v1 */ if(cpu(3)!=0){set(2,cpu(0));}
/* 00244254: slt a0,a1,v0 */ set(4,(int64_t)cpu(5)<(int64_t)cpu(2));
/* 00244258: movn v0,a1,a0 */ if(cpu(4)!=0){set(2,cpu(5));}
/* 0024425c: jr ra */ {uint64_t target=cpu(31);/* delay 00244260 */ sw(ea(6,(int32_t)UINT32_C(0x00000a48)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_00244e68(void){
nocturneEffectAxisNoteEntry(0x00244e68u);
uint64_t incoming=cpu(31);
/* 00244e68: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00244e6c: andi v1,v1,0x4 */ set(3,cpu(3)&UINT32_C(0x00000004));
/* 00244e70: bne v1,zero,0x00244eac */ {int taken=(cpu(3)!=cpu(0));/* delay 00244e74 */ set(2,cpu(0));if(taken){goto L_00244eac;}}
/* 00244e78: lhu a0,0x4(a0) */ set(4,half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 00244e7c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00244e80: sll v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)<<4));
/* 00244e84: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 00244e88: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00244e8c: lui a0,0x35 */ set(4,sx(UINT32_C(0x00350000)));
/* 00244e90: addu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 00244e94: lw a0,-0x6840(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0xffff97c0)));
/* 00244e98: andi a1,a0,0x40 */ set(5,cpu(4)&UINT32_C(0x00000040));
/* 00244e9c: bne a1,zero,0x00244eac */ {int taken=(cpu(5)!=cpu(0));/* delay 00244ea0 */ set(3,cpu(4)&UINT32_C(0x00000080));if(taken){goto L_00244eac;}}
/* 00244ea4: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 00244ea8: movz v0,zero,v1 */ if(cpu(3)==0){set(2,cpu(0));}
L_00244eac:;
/* 00244eac: jr ra */ {uint64_t target=cpu(31);/* delay 00244eb0 */ checkReturn(target,incoming);return;}
}
static void body_00244ef8(void){
nocturneEffectAxisNoteEntry(0x00244ef8u);
uint64_t incoming=cpu(31);
/* 00244ef8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00244efc: li a2,0xec */ set(6,sx(UINT32_C(0x000000ec)));
/* 00244f00: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00244f04: move s0,a1 */ set(16,cpu(5));
/* 00244f08: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00244f0c: move s1,a0 */ set(17,cpu(4));
/* 00244f10: move a1,zero */ set(5,cpu(0));
/* 00244f14: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00244f18: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00244f1c: jal 0x002d4558 */ set(31,0x00244f24u);/* delay 00244f20 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002d4558u);
/* 00244f24: sll v0,s1,0x4 */ set(2,sx((uint32_t)cpu(17)<<4));
/* 00244f28: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00244f2c: subu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(17)));
/* 00244f30: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 00244f34: sh s1,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(17));
/* 00244f38: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00244f3c: lui at,0x35 */ set(1,sx(UINT32_C(0x00350000)));
/* 00244f40: addiu at,at,-0x6840 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffff97c0)));
/* 00244f44: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 00244f48: addiu a1,s0,0x16 */ set(5,sx((uint32_t)cpu(16)+UINT32_C(0x00000016)));
/* 00244f4c: lbu v1,0x5(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000005))));
/* 00244f50: li a2,0x5 */ set(6,sx(UINT32_C(0x00000005)));
/* 00244f54: sw zero,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 00244f58: addiu a0,v0,0x10 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 00244f5c: sh v1,0x14(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(3));
L_00244f60:;
/* 00244f60: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00244f64: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00244f68: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 00244f6c: sb v0,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 00244f70: nop  */ 
/* 00244f74: bgez a2,0x00244f60 */ {int taken=((int64_t)cpu(6)>=0);/* delay 00244f78 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_00244f60;}}
/* 00244f7c: sll v1,s1,0x1 */ set(3,sx((uint32_t)cpu(17)<<1));
/* 00244f80: move s2,zero */ set(18,cpu(0));
/* 00244f84: addu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(17)));
/* 00244f88: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00244f8c: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 00244f90: addiu a1,s0,0x3a */ set(5,sx((uint32_t)cpu(16)+UINT32_C(0x0000003a)));
/* 00244f94: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00244f98: li a2,0x17 */ set(6,sx(UINT32_C(0x00000017)));
/* 00244f9c: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00244fa0: lui v1,0x33 */ set(3,sx(UINT32_C(0x00330000)));
/* 00244fa4: addiu v1,v1,0x3cf8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00003cf8)));
/* 00244fa8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00244fac: nop  */ 
L_00244fb0:;
/* 00244fb0: lbu v0,0x6(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000006))));
/* 00244fb4: bne v0,zero,0x00244fd8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00244fb8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));if(taken){goto L_00244fd8;}}
/* 00244fbc: lbu v0,0x7(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000007))));
/* 00244fc0: bne v0,a0,0x00244fd8 */ {int taken=(cpu(2)!=cpu(4));/* delay 00244fc4 */ if(taken){goto L_00244fd8;}}
/* 00244fc8: lhu v0,0x8(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000008))));
/* 00244fcc: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 00244fd0: sh v0,0x0(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));
/* 00244fd4: addiu a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
L_00244fd8:;
/* 00244fd8: bgez a2,0x00244fb0 */ {int taken=((int64_t)cpu(6)>=0);/* delay 00244fdc */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000004)));if(taken){goto L_00244fb0;}}
/* 00244fe0: jal 0x00243c28 */ set(31,0x00244fe8u);/* delay 00244fe4 */ set(4,cpu(16));body_00243c28();
/* 00244fe8: move a0,s0 */ set(4,cpu(16));
/* 00244fec: sh v0,0x6(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(2));
/* 00244ff0: jal 0x00243d28 */ set(31,0x00244ff8u);/* delay 00244ff4 */ sh(ea(16,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(2));body_00243d28();
/* 00244ff8: sh s2,0x38(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000038)),(uint16_t)cpu(18));
/* 00244ffc: sh v0,0xa(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(2));
/* 00245000: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 00245004: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00245008: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0024500c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00245010: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00245014: jr ra */ {uint64_t target=cpu(31);/* delay 00245018 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00245c90(void){
nocturneEffectAxisNoteEntry(0x00245c90u);
uint64_t incoming=cpu(31);
/* 00245c90: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00245c94: move v0,a0 */ set(2,cpu(4));
/* 00245c98: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00245c9c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00245ca0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00245ca4: move a0,zero */ set(4,cpu(0));
/* 00245ca8: addiu t2,v1,0x3170 */ set(10,sx((uint32_t)cpu(3)+UINT32_C(0x00003170)));
/* 00245cac: ldl a3,0x7(t2) */ loadPartial(7,ea(10,(int32_t)UINT32_C(0x00000007)),1);
/* 00245cb0: ldr a3,0x0(t2) */ loadPartial(7,ea(10,(int32_t)UINT32_C(0x00000000)),0);
/* 00245cb4: ldl t0,0xf(t2) */ loadPartial(8,ea(10,(int32_t)UINT32_C(0x0000000f)),1);
/* 00245cb8: ldr t0,0x8(t2) */ loadPartial(8,ea(10,(int32_t)UINT32_C(0x00000008)),0);
/* 00245cbc: ldl t1,0x17(t2) */ loadPartial(9,ea(10,(int32_t)UINT32_C(0x00000017)),1);
/* 00245cc0: ldr t1,0x10(t2) */ loadPartial(9,ea(10,(int32_t)UINT32_C(0x00000010)),0);
/* 00245cc4: sdl a3,0x7(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000007)),7,1);
/* 00245cc8: sdr a3,0x0(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000000)),7,0);
/* 00245ccc: sdl t0,0xf(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000000f)),8,1);
/* 00245cd0: sdr t0,0x8(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000008)),8,0);
/* 00245cd4: sdl t1,0x17(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000017)),9,1);
/* 00245cd8: sdr t1,0x10(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000010)),9,0);
/* 00245cdc: bne v0,a1,0x00245d00 */ {int taken=(cpu(2)!=cpu(5));/* delay 00245ce0 */ set(6,sx((uint32_t)cpu(2)<<3));if(taken){goto L_00245d00;}}
/* 00245ce4: jal 0x002c0c60 */ set(31,0x00245cecu);/* delay 00245ce8 */ set(5,sx(UINT32_C(0x00000006)));nocturneBattleActionSkillCall(0x002c0c60u);
/* 00245cec: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00245cf0: addu v1,sp,v0 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(2)));
/* 00245cf4: b 0x00245d0c */ /* delay 00245cf8 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_00245d0c;
L_00245d00:;
/* 00245d00: lui v0,0x3e */ set(2,sx(UINT32_C(0x003e0000)));
/* 00245d04: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00245d08: lhu v0,-0x3b5e(v0) */ set(2,half(ea(2,(int32_t)UINT32_C(0xffffc4a2))));
L_00245d0c:;
/* 00245d0c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00245d10: jr ra */ {uint64_t target=cpu(31);/* delay 00245d14 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00251858(void){
nocturneEffectAxisNoteEntry(0x00251858u);
uint64_t incoming=cpu(31);
/* 00251858: addiu a0,a0,0x8a */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000008a)));
/* 0025185c: move a1,zero */ set(5,cpu(0));
/* 00251860: li a2,0x1f */ set(6,sx(UINT32_C(0x0000001f)));
/* 00251864: nop  */ 
L_00251868:;
/* 00251868: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 0025186c: addiu a0,a0,0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
/* 00251870: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 00251874: slt v0,a1,v1 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(3));
/* 00251878: nop  */ 
/* 0025187c: bgez a2,0x00251868 */ {int taken=((int64_t)cpu(6)>=0);/* delay 00251880 */ if(cpu(2)!=0){set(5,cpu(3));}if(taken){goto L_00251868;}}
/* 00251884: jr ra */ {uint64_t target=cpu(31);/* delay 00251888 */ set(2,cpu(5));checkReturn(target,incoming);return;}
}
static void body_00251890(void){
nocturneEffectAxisNoteEntry(0x00251890u);
uint64_t incoming=cpu(31);
/* 00251890: addiu a0,a0,0x88 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000088)));
/* 00251894: move a1,zero */ set(5,cpu(0));
/* 00251898: li a2,0x1f */ set(6,sx(UINT32_C(0x0000001f)));
/* 0025189c: nop  */ 
L_002518a0:;
/* 002518a0: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002518a4: addiu a0,a0,0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
/* 002518a8: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002518ac: slt v0,a1,v1 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(3));
/* 002518b0: nop  */ 
/* 002518b4: bgez a2,0x002518a0 */ {int taken=((int64_t)cpu(6)>=0);/* delay 002518b8 */ if(cpu(2)!=0){set(5,cpu(3));}if(taken){goto L_002518a0;}}
/* 002518bc: jr ra */ {uint64_t target=cpu(31);/* delay 002518c0 */ set(2,cpu(5));checkReturn(target,incoming);return;}
}
static void body_00259a60(void){
nocturneEffectAxisNoteEntry(0x00259a60u);
uint64_t incoming=cpu(31);
/* 00259a60: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00259a64: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259a68: jal 0x00259a30 */ set(31,0x00259a70u);/* delay 00259a6c */ nocturneBattleActionSkillCall(0x00259a30u);
/* 00259a70: move v1,v0 */ set(3,cpu(2));
/* 00259a74: bne v1,zero,0x00259a88 */ {int taken=(cpu(3)!=cpu(0));/* delay 00259a78 */ set(2,sx((uint32_t)cpu(3)<<1));if(taken){goto L_00259a88;}}
/* 00259a7c: lui v0,0x35 */ set(2,sx(UINT32_C(0x00350000)));
/* 00259a80: b 0x00259aa4 */ /* delay 00259a84 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff94b0)));goto L_00259aa4;
L_00259a88:;
/* 00259a88: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00259a8c: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 00259a90: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00259a94: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 00259a98: lui at,0x35 */ set(1,sx(UINT32_C(0x00350000)));
/* 00259a9c: addiu at,at,-0xe20 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xfffff1e0)));
/* 00259aa0: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
L_00259aa4:;
/* 00259aa4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259aa8: jr ra */ {uint64_t target=cpu(31);/* delay 00259aac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00259c48(void){
nocturneEffectAxisNoteEntry(0x00259c48u);
uint64_t incoming=cpu(31);
/* 00259c48: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00259c4c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259c50: move s0,a1 */ set(16,cpu(5));
/* 00259c54: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00259c58: move s1,a0 */ set(17,cpu(4));
/* 00259c5c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00259c60: jal 0x00245c90 */ set(31,0x00259c68u);/* delay 00259c64 */ set(4,cpu(16));body_00245c90();
/* 00259c68: move v1,v0 */ set(3,cpu(2));
/* 00259c6c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00259c70: beql s0,v0,0x00259c78 */ {int taken=(cpu(16)==cpu(2));if(taken){/* delay 00259c74 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000064)));goto L_00259c78;}}
L_00259c78:;
/* 00259c78: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259c7c: move v0,v1 */ set(2,cpu(3));
/* 00259c80: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00259c84: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00259c88: jr ra */ {uint64_t target=cpu(31);/* delay 00259c8c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00261758(void){
nocturneEffectAxisNoteEntry(0x00261758u);
uint64_t incoming=cpu(31);
/* 00261758: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0026175c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261760: move s0,a0 */ set(16,cpu(4));
/* 00261764: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261768: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026176c: jal 0x0025e8e0 */ set(31,0x00261774u);/* delay 00261770 */ set(17,cpu(5));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00261774: move a0,v0 */ set(4,cpu(2));
/* 00261778: move a1,s0 */ set(5,cpu(16));
/* 0026177c: move a3,s1 */ set(7,cpu(17));
/* 00261780: jal 0x0025ea48 */ set(31,0x00261788u);/* delay 00261784 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00261788: li v1,0x3a */ set(3,sx(UINT32_C(0x0000003a)));
/* 0026178c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261790: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261794: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261798: sb v1,0x4(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 0026179c: jr ra */ {uint64_t target=cpu(31);/* delay 002617a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00261f90(void){
nocturneEffectAxisNoteEntry(0x00261f90u);
uint64_t incoming=cpu(31);
/* 00261f90: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00261f94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261f98: move s0,a0 */ set(16,cpu(4));
/* 00261f9c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261fa0: move s1,a1 */ set(17,cpu(5));
/* 00261fa4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261fa8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261fac: jal 0x0025e8e0 */ set(31,0x00261fb4u);/* delay 00261fb0 */ set(18,cpu(6));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00261fb4: move a0,v0 */ set(4,cpu(2));
/* 00261fb8: move a1,s0 */ set(5,cpu(16));
/* 00261fbc: move a3,s1 */ set(7,cpu(17));
/* 00261fc0: jal 0x0025ea48 */ set(31,0x00261fc8u);/* delay 00261fc4 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00261fc8: li a0,0x21 */ set(4,sx(UINT32_C(0x00000021)));
/* 00261fcc: move v1,v0 */ set(3,cpu(2));
/* 00261fd0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261fd4: sw s2,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 00261fd8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261fdc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261fe0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261fe4: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00261fe8: jr ra */ {uint64_t target=cpu(31);/* delay 00261fec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00262fb8(void){
nocturneEffectAxisNoteEntry(0x00262fb8u);
uint64_t incoming=cpu(31);
/* 00262fb8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262fbc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262fc0: move s0,a0 */ set(16,cpu(4));
/* 00262fc4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262fc8: move s1,a1 */ set(17,cpu(5));
/* 00262fcc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262fd0: move s2,a3 */ set(18,cpu(7));
/* 00262fd4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262fd8: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262fdc: jal 0x0025e8e0 */ set(31,0x00262fe4u);/* delay 00262fe0 */ set(19,cpu(6));nocturneBattleActionSkillCall(0x0025e8e0u);
/* 00262fe4: move a0,v0 */ set(4,cpu(2));
/* 00262fe8: move a1,s0 */ set(5,cpu(16));
/* 00262fec: move a3,s1 */ set(7,cpu(17));
/* 00262ff0: jal 0x0025ea48 */ set(31,0x00262ff8u);/* delay 00262ff4 */ set(6,cpu(0));nocturneBattleActionSkillCall(0x0025ea48u);
/* 00262ff8: li a0,0x26 */ set(4,sx(UINT32_C(0x00000026)));
/* 00262ffc: move v1,v0 */ set(3,cpu(2));
/* 00263000: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263004: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00263008: sw s3,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 0026300c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263010: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263014: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263018: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0026301c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00263020: jr ra */ {uint64_t target=cpu(31);/* delay 00263024 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00265868(void){
nocturneEffectAxisNoteEntry(0x00265868u);
uint64_t incoming=cpu(31);
/* 00265868: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026586c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00265870: jal 0x00246ab8 */ set(31,0x00265878u);/* delay 00265874 */ nocturneBattleActionSkillCall(0x00246ab8u);
/* 00265878: jal 0x00244e68 */ set(31,0x00265880u);/* delay 0026587c */ set(4,cpu(2));body_00244e68();
/* 00265880: move a0,v0 */ set(4,cpu(2));
/* 00265884: beq a0,zero,0x002658ac */ {int taken=(cpu(4)==cpu(0));/* delay 00265888 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002658ac;}}
/* 0026588c: bgtzl a0,0x002658a0 */ {int taken=((int64_t)cpu(4)>0);if(taken){/* delay 00265890 */ set(3,sx(UINT32_C(0x00000001)));goto L_002658a0;}}
/* 00265894: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 00265898: b 0x002658a4 */ /* delay 0026589c */ set(2,cpu(0));goto L_002658a4;
L_002658a0:;
/* 002658a0: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
L_002658a4:;
/* 002658a4: bnel a0,v1,0x002658ac */ {int taken=(cpu(4)!=cpu(3));if(taken){/* delay 002658a8 */ set(2,sx(UINT32_C(0x00000001)));goto L_002658ac;}}
L_002658ac:;
/* 002658ac: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002658b0: jr ra */ {uint64_t target=cpu(31);/* delay 002658b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002658b8(void){
nocturneEffectAxisNoteEntry(0x002658b8u);
uint64_t incoming=cpu(31);
/* 002658b8: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 002658bc: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002658c0: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 002658c4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002658c8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002658cc: lui s0,0x3d */ set(16,sx(UINT32_C(0x003d0000)));
/* 002658d0: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002658d4: lbu s0,0x79a8(s0) */ set(16,byte(ea(16,(int32_t)UINT32_C(0x000079a8))));
/* 002658d8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002658dc: jal 0x00265868 */ set(31,0x002658e4u);/* delay 002658e0 */ set(4,cpu(6));body_00265868();
/* 002658e4: andi v1,s0,0x1 */ set(3,cpu(16)&UINT32_C(0x00000001));
/* 002658e8: move a1,v0 */ set(5,cpu(2));
/* 002658ec: andi a0,s0,0x2 */ set(4,cpu(16)&UINT32_C(0x00000002));
/* 002658f0: bne v1,zero,0x00265934 */ {int taken=(cpu(3)!=cpu(0));/* delay 002658f4 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00265934;}}
/* 002658f8: beql a0,zero,0x0026590c */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 002658fc */ set(2,cpu(16)&UINT32_C(0x00000004));goto L_0026590c;}}
/* 00265900: beql a1,zero,0x00265938 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 00265904 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00265938;}}
/* 00265908: andi v0,s0,0x4 */ set(2,cpu(16)&UINT32_C(0x00000004));
L_0026590c:;
/* 0026590c: beq v0,zero,0x0026591c */ {int taken=(cpu(2)==cpu(0));/* delay 00265910 */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_0026591c;}}
/* 00265914: beq a1,v1,0x00265934 */ {int taken=(cpu(5)==cpu(3));/* delay 00265918 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00265934;}}
L_0026591c:;
/* 0026591c: andi v0,s0,0x8 */ set(2,cpu(16)&UINT32_C(0x00000008));
/* 00265920: beq v0,zero,0x00265930 */ {int taken=(cpu(2)==cpu(0));/* delay 00265924 */ set(3,sx(UINT32_C(0x00000002)));if(taken){goto L_00265930;}}
/* 00265928: beq a1,v1,0x00265934 */ {int taken=(cpu(5)==cpu(3));/* delay 0026592c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00265934;}}
L_00265930:;
/* 00265930: move v0,zero */ set(2,cpu(0));
L_00265934:;
/* 00265934: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00265938:;
/* 00265938: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026593c: jr ra */ {uint64_t target=cpu(31);/* delay 00265940 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00265948(void){
nocturneEffectAxisNoteEntry(0x00265948u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 00265948: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
/* 0026594c: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00265950: move s1,a0 */ set(17,cpu(4));
/* 00265954: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00265958: move s5,a2 */ set(21,cpu(6));
/* 0026595c: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00265960: sll s6,s1,0x4 */ set(22,sx((uint32_t)cpu(17)<<4));
/* 00265964: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00265968: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0026596c: lui s8,0x3d */ set(30,sx(UINT32_C(0x003d0000)));
/* 00265970: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00265974: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00265978: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026597c: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00265980: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00265984: swc1 f23,0x78(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000078)),f[23]);
/* 00265988: swc1 f22,0x70(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000070)),f[22]);
/* 0026598c: swc1 f21,0x68(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000068)),f[21]);
/* 00265990: swc1 f20,0x60(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),f[20]);
/* 00265994: jal 0x002469a0 */ set(31,0x0026599cu);/* delay 00265998 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));nocturneBattleActionSkillCall(0x002469a0u);
/* 0026599c: move s7,v0 */ set(23,cpu(2));
/* 002659a0: subu v0,s6,s1 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(17)));
/* 002659a4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002659a8: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
/* 002659ac: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002659b0: lw v1,0x79c8(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x000079c8)));
/* 002659b4: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 002659b8: sltiu v0,v1,0xe */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 002659bc: beq v0,zero,0x00265a18 */ {int taken=(cpu(2)==cpu(0));/* delay 002659c0 */ set(2,sx((uint32_t)cpu(3)<<2));if(taken){goto L_00265a18;}}
/* 002659c4: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002659c8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002659cc: lw v1,0x4a10(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004a10)));
/* 002659d0: jr v1 */ {uint64_t target=cpu(3);/* delay 002659d4 */ switch((uint32_t)target){case 0x002659d8u:goto L_002659d8;case 0x002659e0u:goto L_002659e0;case 0x002659e8u:goto L_002659e8;case 0x002659f0u:goto L_002659f0;case 0x002659f8u:goto L_002659f8;case 0x00265a00u:goto L_00265a00;case 0x00265a08u:goto L_00265a08;case 0x00265a10u:goto L_00265a10;case 0x00265a18u:goto L_00265a18;default:abort();}}
L_002659d8:;
/* 002659d8: b 0x0026607c */ /* delay 002659dc */ set(2,sx(UINT32_C(0x00000007)));goto L_0026607c;
L_002659e0:;
/* 002659e0: b 0x0026607c */ /* delay 002659e4 */ set(2,sx(UINT32_C(0x00000006)));goto L_0026607c;
L_002659e8:;
/* 002659e8: b 0x0026607c */ /* delay 002659ec */ set(2,sx(UINT32_C(0x00000008)));goto L_0026607c;
L_002659f0:;
/* 002659f0: b 0x0026607c */ /* delay 002659f4 */ set(2,sx(UINT32_C(0x0000000a)));goto L_0026607c;
L_002659f8:;
/* 002659f8: b 0x0026607c */ /* delay 002659fc */ set(2,sx(UINT32_C(0x00000009)));goto L_0026607c;
L_00265a00:;
/* 00265a00: b 0x0026607c */ /* delay 00265a04 */ set(2,sx(UINT32_C(0x0000000c)));goto L_0026607c;
L_00265a08:;
/* 00265a08: b 0x0026607c */ /* delay 00265a0c */ set(2,sx(UINT32_C(0x0000000d)));goto L_0026607c;
L_00265a10:;
/* 00265a10: b 0x0026607c */ /* delay 00265a14 */ set(2,sx(UINT32_C(0x0000000e)));goto L_0026607c;
L_00265a18:;
/* 00265a18: jal 0x00246ab8 */ set(31,0x00265a20u);/* delay 00265a1c */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));nocturneBattleActionSkillCall(0x00246ab8u);
/* 00265a20: move a0,s5 */ set(4,cpu(21));
/* 00265a24: jal 0x00246ab8 */ set(31,0x00265a2cu);/* delay 00265a28 */ set(20,cpu(2));nocturneBattleActionSkillCall(0x00246ab8u);
/* 00265a2c: move a0,s5 */ set(4,cpu(21));
/* 00265a30: jal 0x0026a7d0 */ set(31,0x00265a38u);/* delay 00265a34 */ set(19,cpu(2));nocturneBattleActionSkillCall(0x0026a7d0u);
/* 00265a38: lui v1,0x4000 */ set(3,sx(UINT32_C(0x40000000)));
/* 00265a3c: sw v0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 00265a40: lw a0,0x60(s7) */ lw(4,ea(23,(int32_t)UINT32_C(0x00000060)));
/* 00265a44: and v1,a0,v1 */ set(3,cpu(4)&cpu(3));
/* 00265a48: bne v1,zero,0x0026607c */ {int taken=(cpu(3)!=cpu(0));/* delay 00265a4c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0026607c;}}
/* 00265a50: lui v1,0x800 */ set(3,sx(UINT32_C(0x08000000)));
/* 00265a54: and v1,a0,v1 */ set(3,cpu(4)&cpu(3));
/* 00265a58: bne v1,zero,0x0026607c */ {int taken=(cpu(3)!=cpu(0));/* delay 00265a5c */ set(2,cpu(0));if(taken){goto L_0026607c;}}
/* 00265a60: li v0,0x9e */ set(2,sx(UINT32_C(0x0000009e)));
/* 00265a64: bne s1,v0,0x00265a98 */ {int taken=(cpu(17)!=cpu(2));/* delay 00265a68 */ set(2,sx(UINT32_C(0x0000009f)));if(taken){goto L_00265a98;}}
/* 00265a6c: andi v0,a0,0x1 */ set(2,cpu(4)&UINT32_C(0x00000001));
/* 00265a70: beq v0,zero,0x00265a94 */ {int taken=(cpu(2)==cpu(0));/* delay 00265a74 */ set(2,sx(UINT32_C(0x00000408)));if(taken){goto L_00265a94;}}
/* 00265a78: lw v1,0x34(s7) */ lw(3,ea(23,(int32_t)UINT32_C(0x00000034)));
/* 00265a7c: beq v1,v0,0x00265a98 */ {int taken=(cpu(3)==cpu(2));/* delay 00265a80 */ set(2,sx(UINT32_C(0x0000009f)));if(taken){goto L_00265a98;}}
/* 00265a84: lw v1,0x0(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 00265a88: andi v1,v1,0x20 */ set(3,cpu(3)&UINT32_C(0x00000020));
/* 00265a8c: bne v1,zero,0x0026607c */ {int taken=(cpu(3)!=cpu(0));/* delay 00265a90 */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_0026607c;}}
L_00265a94:;
/* 00265a94: li v0,0x9f */ set(2,sx(UINT32_C(0x0000009f)));
L_00265a98:;
/* 00265a98: bne s1,v0,0x00265abc */ {int taken=(cpu(17)!=cpu(2));/* delay 00265a9c */ if(taken){goto L_00265abc;}}
/* 00265aa0: andi v0,a0,0x1 */ set(2,cpu(4)&UINT32_C(0x00000001));
/* 00265aa4: beq v0,zero,0x00265abc */ {int taken=(cpu(2)==cpu(0));/* delay 00265aa8 */ if(taken){goto L_00265abc;}}
/* 00265aac: lw v1,0x0(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 00265ab0: andi v1,v1,0x20 */ set(3,cpu(3)&UINT32_C(0x00000020));
/* 00265ab4: bne v1,zero,0x0026607c */ {int taken=(cpu(3)!=cpu(0));/* delay 00265ab8 */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_0026607c;}}
L_00265abc:;
/* 00265abc: jal 0x00267e38 */ set(31,0x00265ac4u);/* delay 00265ac0 */ set(4,cpu(17));nocturneBattleActionSkillCall(0x00267e38u);
/* 00265ac4: move s2,v0 */ set(18,cpu(2));
/* 00265ac8: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 00265acc: beq s2,v0,0x00265bd0 */ {int taken=(cpu(18)==cpu(2));/* delay 00265ad0 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0xffffffff));if(taken){goto L_00265bd0;}}
/* 00265ad4: bnel v0,zero,0x00265af8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00265ad8 */ set(4,cpu(17));goto L_00265af8;}}
/* 00265adc: slti v0,s2,0xf */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x0000000f));
/* 00265ae0: beql v0,zero,0x00265af8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00265ae4 */ set(4,cpu(17));goto L_00265af8;}}
/* 00265ae8: slti v0,s2,0xc */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 00265aec: beql v0,zero,0x00265bd4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00265af0 */ lw(2,ea(23,(int32_t)UINT32_C(0x00000060)));goto L_00265bd4;}}
/* 00265af4: move a0,s1 */ set(4,cpu(17));
L_00265af8:;
/* 00265af8: move a1,s5 */ set(5,cpu(21));
/* 00265afc: jal 0x00267890 */ set(31,0x00265b04u);/* delay 00265b00 */ set(6,cpu(18));nocturneBattleActionSkillCall(0x00267890u);
/* 00265b04: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
/* 00265b08: move s0,v0 */ set(16,cpu(2));
/* 00265b0c: lhu v0,0xe(s3) */ set(2,half(ea(19,(int32_t)UINT32_C(0x0000000e))));
/* 00265b10: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
/* 00265b14: bne v0,v1,0x00265b60 */ {int taken=(cpu(2)!=cpu(3));/* delay 00265b18 */ set(3,sx(UINT32_C(0x00020000)));if(taken){goto L_00265b60;}}
/* 00265b1c: subu v0,s6,s1 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(17)));
/* 00265b20: addiu a0,s8,0x7998 */ set(4,sx((uint32_t)cpu(30)+UINT32_C(0x00007998)));
/* 00265b24: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00265b28: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00265b2c: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00265b30: bne v1,zero,0x00265b60 */ {int taken=(cpu(3)!=cpu(0));/* delay 00265b34 */ set(3,sx(UINT32_C(0x00020000)));if(taken){goto L_00265b60;}}
/* 00265b38: lui v0,0xfffe */ set(2,sx(UINT32_C(0xfffe0000)));
/* 00265b3c: lui a0,0xfffd */ set(4,sx(UINT32_C(0xfffd0000)));
/* 00265b40: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 00265b44: ori a0,a0,0xffff */ set(4,cpu(4)|UINT32_C(0x0000ffff));
/* 00265b48: and s0,s0,v0 */ set(16,cpu(16)&cpu(2));
/* 00265b4c: lui v1,0xfffb */ set(3,sx(UINT32_C(0xfffb0000)));
/* 00265b50: and s0,s0,a0 */ set(16,cpu(16)&cpu(4));
/* 00265b54: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 00265b58: and s0,s0,v1 */ set(16,cpu(16)&cpu(3));
/* 00265b5c: lui v1,0x2 */ set(3,sx(UINT32_C(0x00020000)));
L_00265b60:;
/* 00265b60: and v1,s0,v1 */ set(3,cpu(16)&cpu(3));
/* 00265b64: bne v1,zero,0x0026607c */ {int taken=(cpu(3)!=cpu(0));/* delay 00265b68 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0026607c;}}
/* 00265b6c: move a0,s4 */ set(4,cpu(20));
/* 00265b70: jal 0x00243f40 */ set(31,0x00265b78u);/* delay 00265b74 */ set(5,sx(UINT32_C(0x00000165)));nocturneBattleActionSkillCall(0x00243f40u);
/* 00265b78: beq v0,zero,0x00265bb0 */ {int taken=(cpu(2)==cpu(0));/* delay 00265b7c */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(17)));if(taken){goto L_00265bb0;}}
/* 00265b80: addiu a0,s8,0x7998 */ set(4,sx((uint32_t)cpu(30)+UINT32_C(0x00007998)));
/* 00265b84: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00265b88: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00265b8c: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00265b90: bnel v1,zero,0x00265bb4 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00265b94 */ set(3,sx(UINT32_C(0x00040000)));goto L_00265bb4;}}
/* 00265b98: lui v0,0x5 */ set(2,sx(UINT32_C(0x00050000)));
/* 00265b9c: and v0,s0,v0 */ set(2,cpu(16)&cpu(2));
/* 00265ba0: beq v0,zero,0x00265bd0 */ {int taken=(cpu(2)==cpu(0));/* delay 00265ba4 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00265bd0;}}
/* 00265ba8: b 0x00265bd0 */ /* delay 00265bac */ sw(ea(23,(int32_t)UINT32_C(0x0000014c)),(uint32_t)cpu(2));goto L_00265bd0;
L_00265bb0:;
/* 00265bb0: lui v1,0x4 */ set(3,sx(UINT32_C(0x00040000)));
L_00265bb4:;
/* 00265bb4: and v1,s0,v1 */ set(3,cpu(16)&cpu(3));
/* 00265bb8: bne v1,zero,0x0026607c */ {int taken=(cpu(3)!=cpu(0));/* delay 00265bbc */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_0026607c;}}
/* 00265bc0: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 00265bc4: and v1,s0,v1 */ set(3,cpu(16)&cpu(3));
/* 00265bc8: bne v1,zero,0x0026607c */ {int taken=(cpu(3)!=cpu(0));/* delay 00265bcc */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_0026607c;}}
L_00265bd0:;
/* 00265bd0: lw v0,0x60(s7) */ lw(2,ea(23,(int32_t)UINT32_C(0x00000060)));
L_00265bd4:;
/* 00265bd4: andi v0,v0,0x400 */ set(2,cpu(2)&UINT32_C(0x00000400));
/* 00265bd8: beq v0,zero,0x00265c50 */ {int taken=(cpu(2)==cpu(0));/* delay 00265bdc */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(17)));if(taken){goto L_00265c50;}}
/* 00265be0: lw v0,0x0(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 00265be4: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00265be8: beq v0,zero,0x00265c4c */ {int taken=(cpu(2)==cpu(0));/* delay 00265bec */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(17)));if(taken){goto L_00265c4c;}}
/* 00265bf0: addiu a0,s8,0x7998 */ set(4,sx((uint32_t)cpu(30)+UINT32_C(0x00007998)));
/* 00265bf4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00265bf8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00265bfc: lbu v1,0x8(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000008))));
/* 00265c00: beq v1,zero,0x00265c28 */ {int taken=(cpu(3)==cpu(0));/* delay 00265c04 */ set(2,sx(UINT32_C(0x0000000e)));if(taken){goto L_00265c28;}}
/* 00265c08: beq s2,v0,0x00265c4c */ {int taken=(cpu(18)==cpu(2));/* delay 00265c0c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00265c4c;}}
/* 00265c10: lh v1,0x1a(s7) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(23,(int32_t)UINT32_C(0x0000001a))));
/* 00265c14: beq v1,v0,0x00265c4c */ {int taken=(cpu(3)==cpu(2));/* delay 00265c18 */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_00265c4c;}}
/* 00265c1c: b 0x00266080 */ /* delay 00265c20 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_00266080;
L_00265c28:;
/* 00265c28: sll v1,s5,0x4 */ set(3,sx((uint32_t)cpu(21)<<4));
/* 00265c2c: lw a1,0x0(s7) */ lw(5,ea(23,(int32_t)UINT32_C(0x00000000)));
/* 00265c30: subu v1,v1,s5 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(21)));
/* 00265c34: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 00265c38: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00265c3c: lw a0,0x78(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000078)));
/* 00265c40: andi a0,a0,0x1000 */ set(4,cpu(4)&UINT32_C(0x00001000));
/* 00265c44: bne a0,zero,0x0026607c */ {int taken=(cpu(4)!=cpu(0));/* delay 00265c48 */ set(2,sx(UINT32_C(0x0000000b)));if(taken){goto L_0026607c;}}
L_00265c4c:;
/* 00265c4c: subu v0,s6,s1 */ set(2,sx((uint32_t)cpu(22)-(uint32_t)cpu(17)));
L_00265c50:;
/* 00265c50: addiu v1,s8,0x7998 */ set(3,sx((uint32_t)cpu(30)+UINT32_C(0x00007998)));
/* 00265c54: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00265c58: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
/* 00265c5c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00265c60: lw v1,0x30(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000030)));
/* 00265c64: beq v1,a0,0x00265c80 */ {int taken=(cpu(3)==cpu(4));/* delay 00265c68 */ set(2,sx(UINT32_C(0x0000000f)));if(taken){goto L_00265c80;}}
/* 00265c6c: beq v1,v0,0x00265ca0 */ {int taken=(cpu(3)==cpu(2));/* delay 00265c70 */ set(5,half(ea(19,(int32_t)UINT32_C(0x0000000e))));if(taken){goto L_00265ca0;}}
/* 00265c74: b 0x00265cb4 */ /* delay 00265c78 */ set(3,cpu(5)&UINT32_C(0x00000fff));goto L_00265cb4;
L_00265c80:;
/* 00265c80: lhu a1,0xe(s3) */ set(5,half(ea(19,(int32_t)UINT32_C(0x0000000e))));
/* 00265c84: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 00265c88: andi v0,a1,0xfff */ set(2,cpu(5)&UINT32_C(0x00000fff));
/* 00265c8c: beq v0,v1,0x00265cb0 */ {int taken=(cpu(2)==cpu(3));/* delay 00265c90 */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_00265cb0;}}
/* 00265c94: b 0x00266080 */ /* delay 00265c98 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_00266080;
L_00265ca0:;
/* 00265ca0: li a0,0x40 */ set(4,sx(UINT32_C(0x00000040)));
/* 00265ca4: andi v1,a1,0xfff */ set(3,cpu(5)&UINT32_C(0x00000fff));
/* 00265ca8: bne v1,a0,0x0026607c */ {int taken=(cpu(3)!=cpu(4));/* delay 00265cac */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_0026607c;}}
L_00265cb0:;
/* 00265cb0: andi v1,a1,0xfff */ set(3,cpu(5)&UINT32_C(0x00000fff));
L_00265cb4:;
/* 00265cb4: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 00265cb8: beq v1,v0,0x00266078 */ {int taken=(cpu(3)==cpu(2));/* delay 00265cbc */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000005));if(taken){goto L_00266078;}}
/* 00265cc0: beq v0,zero,0x00265ce8 */ {int taken=(cpu(2)==cpu(0));/* delay 00265cc4 */ set(2,sx(UINT32_C(0x00000100)));if(taken){goto L_00265ce8;}}
/* 00265cc8: slti v0,v1,0x3 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00265ccc: beq v0,zero,0x00265d04 */ {int taken=(cpu(2)==cpu(0));/* delay 00265cd0 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00265d04;}}
/* 00265cd4: beq v1,zero,0x00265d08 */ {int taken=(cpu(3)==cpu(0));/* delay 00265cd8 */ set(4,cpu(17));if(taken){goto L_00265d08;}}
/* 00265cdc: b 0x0026607c */ /* delay 00265ce0 */ set(2,cpu(0));goto L_0026607c;
L_00265ce8:;
/* 00265ce8: beq v1,v0,0x00266078 */ {int taken=(cpu(3)==cpu(2));/* delay 00265cec */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000101));if(taken){goto L_00266078;}}
/* 00265cf0: beql v0,zero,0x00265cfc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00265cf4 */ set(2,sx(UINT32_C(0x00000400)));goto L_00265cfc;}}
/* 00265cf8: li v0,0x10 */ set(2,sx(UINT32_C(0x00000010)));
L_00265cfc:;
/* 00265cfc: beq v1,v0,0x00266078 */ {int taken=(cpu(3)==cpu(2));/* delay 00265d00 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00266078;}}
L_00265d04:;
/* 00265d04: move a0,s1 */ set(4,cpu(17));
L_00265d08:;
/* 00265d08: jal 0x002658b8 */ set(31,0x00265d10u);/* delay 00265d0c */ set(6,cpu(21));body_002658b8();
/* 00265d10: bne v0,zero,0x00265d30 */ {int taken=(cpu(2)!=cpu(0));/* delay 00265d14 */ set(3,sx((uint32_t)cpu(22)-(uint32_t)cpu(17)));if(taken){goto L_00265d30;}}
/* 00265d18: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 00265d1c: jal 0x002d4748 */ set(31,0x00265d24u);/* delay 00265d20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00001140)));nocturneBattleActionSkillCall(0x002d4748u);
/* 00265d24: b 0x0026607c */ /* delay 00265d28 */ set(2,sx(UINT32_C(0x00000005)));goto L_0026607c;
L_00265d30:;
/* 00265d30: addiu a1,s8,0x7998 */ set(5,sx((uint32_t)cpu(30)+UINT32_C(0x00007998)));
/* 00265d34: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00265d38: li a2,0xff */ set(6,sx(UINT32_C(0x000000ff)));
/* 00265d3c: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 00265d40: addu s0,v1,a1 */ set(16,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00265d44: lbu a0,0x1(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00265d48: beq a0,a2,0x0026607c */ {int taken=(cpu(4)==cpu(6));/* delay 00265d4c */ set(2,cpu(0));if(taken){goto L_0026607c;}}
/* 00265d50: lbu v0,0x1(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00265d54: li a0,0xaf2 */ set(4,sx(UINT32_C(0x00000af2)));
/* 00265d58: lwc1 f1,-0x5c48(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa3b8)));
/* 00265d5c: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00265d60: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00265d64: jal 0x001e0f50 */ set(31,0x00265d6cu);/* delay 00265d68 */ f[21]=EE_FPU_MUL_S(f[0],f[1]);nocturneBattleActionSkillCall(0x001e0f50u);
/* 00265d6c: beq v0,zero,0x00265da8 */ {int taken=(cpu(2)==cpu(0));/* delay 00265d70 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00265da8;}}
/* 00265d74: lhu v1,0x6(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 00265d78: bne v1,v0,0x00265dac */ {int taken=(cpu(3)!=cpu(2));/* delay 00265d7c */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00265dac;}}
/* 00265d80: lh v1,0x8(s0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000008))));
/* 00265d84: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00265d88: bne v1,v0,0x00265db0 */ {int taken=(cpu(3)!=cpu(2));/* delay 00265d8c */ set(5,sx(UINT32_C(0x00000008)));if(taken){goto L_00265db0;}}
/* 00265d90: lw v0,0x0(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 00265d94: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00265d98: bne v0,zero,0x00265db0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00265d9c */ if(taken){goto L_00265db0;}}
/* 00265da0: lwc1 f0,-0x5c44(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa3bc)));
/* 00265da4: mul.S f21,f21,f0 */ f[21]=EE_FPU_MUL_S(f[21],f[0]);
L_00265da8:;
/* 00265da8: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00265dac:;
/* 00265dac: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
L_00265db0:;
/* 00265db0: jal 0x002684b0 */ set(31,0x00265db8u);/* delay 00265db4 */ set(18,sx((uint32_t)cpu(30)+UINT32_C(0x00007998)));nocturneBattleActionSkillCall(0x002684b0u);
/* 00265db8: move a0,s5 */ set(4,cpu(21));
/* 00265dbc: li a1,0x6 */ set(5,sx(UINT32_C(0x00000006)));
/* 00265dc0: jal 0x002684b0 */ set(31,0x00265dc8u);/* delay 00265dc4 */ f[22]=f[0];nocturneBattleActionSkillCall(0x002684b0u);
/* 00265dc8: subu v1,s6,s1 */ set(3,sx((uint32_t)cpu(22)-(uint32_t)cpu(17)));
/* 00265dcc: sll s1,v1,0x2 */ set(17,sx((uint32_t)cpu(3)<<2));
/* 00265dd0: addu v0,s1,s2 */ set(2,sx((uint32_t)cpu(17)+(uint32_t)cpu(18)));
/* 00265dd4: lbu v1,0x2(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 00265dd8: beq v1,zero,0x00265df8 */ {int taken=(cpu(3)==cpu(0));/* delay 00265ddc */ f[23]=f[0];if(taken){goto L_00265df8;}}
/* 00265de0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00265de4: beq v1,v0,0x00265f30 */ {int taken=(cpu(3)==cpu(2));/* delay 00265de8 */ set(2,cpu(0));if(taken){goto L_00265f30;}}
/* 00265dec: b 0x00266080 */ /* delay 00265df0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_00266080;
L_00265df8:;
/* 00265df8: lw v0,0x0(s4) */ lw(2,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 00265dfc: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00265e00: move a0,s4 */ set(4,cpu(20));
/* 00265e04: jal 0x00243ee0 */ set(31,0x00265e0cu);/* delay 00265e08 */ set(5,sx(UINT32_C(0x00000004)));nocturneBattleActionSkillCall(0x00243ee0u);
/* 00265e0c: lhu a2,0x14(s4) */ set(6,half(ea(20,(int32_t)UINT32_C(0x00000014))));
/* 00265e10: li s0,0x5 */ set(16,sx(UINT32_C(0x00000005)));
/* 00265e14: move a0,s3 */ set(4,cpu(19));
/* 00265e18: divu a2,s0 */ nativeDivide((uint32_t)cpu(6),(uint32_t)cpu(16),0,0);
/* 00265e1c: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 00265e20: beql s0,zero,0x00265e28 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 00265e24 */ nocturneCompilerArithmeticTrap(7u);goto L_00265e28;}}
L_00265e28:;
/* 00265e28: mflo a2 */ set(6,nocturneEffectHostLo());
/* 00265e2c: addiu a2,a2,0x3 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000003)));
/* 00265e30: div v0,a2 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(6),1,0);
/* 00265e34: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00265e38: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 00265e3c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00265e40: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00265e44: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00265e48: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00265e4c: mtc1 v1,f20 */ f[20]=(uint32_t)cpu(3);
/* 00265e50: cvt.s.W f20,f20 */ f[20]=EE_FPU_CVT_S_W(f[20]);
/* 00265e54: jal 0x00243ee0 */ set(31,0x00265e5cu);/* delay 00265e58 */ nocturneBattleActionSkillCall(0x00243ee0u);
/* 00265e5c: lhu v1,0x14(s3) */ set(3,half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 00265e60: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 00265e64: beql a0,zero,0x00265e6c */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00265e68 */ nocturneCompilerArithmeticTrap(7u);goto L_00265e6c;}}
L_00265e6c:;
/* 00265e6c: addu a2,s1,s2 */ set(6,sx((uint32_t)cpu(17)+(uint32_t)cpu(18)));
/* 00265e70: divu v1,s0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(16),0,0);
/* 00265e74: li a1,0x64 */ set(5,sx(UINT32_C(0x00000064)));
/* 00265e78: lui at,0x3d80 */ set(1,sx(UINT32_C(0x3d800000)));
/* 00265e7c: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00265e80: mflo v1 */ set(3,nocturneEffectHostLo());
/* 00265e84: addiu v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000003)));
/* 00265e88: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 00265e8c: lh a0,0x36(a2) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(6,(int32_t)UINT32_C(0x00000036))));
/* 00265e90: subu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));
/* 00265e94: mtc1 a1,f1 */ f[1]=(uint32_t)cpu(5);
/* 00265e98: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00265e9c: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00265ea0: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 00265ea4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00265ea8: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00265eac: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00265eb0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00265eb4: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00265eb8: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00265ebc: sub.S f0,f20,f0 */ f[0]=EE_FPU_SUB_S(f[20],f[0]);
/* 00265ec0: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 00265ec4: add.S f20,f1,f0 */ f[20]=EE_FPU_ADD_S(f[1],f[0]);
/* 00265ec8: mul.S f0,f20,f22 */ f[0]=EE_FPU_MUL_S(f[20],f[22]);
/* 00265ecc: lui at,0x4248 */ set(1,sx(UINT32_C(0x42480000)));
/* 00265ed0: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00265ed4: mul.S f0,f0,f23 */ f[0]=EE_FPU_MUL_S(f[0],f[23]);
/* 00265ed8: mul.S f20,f0,f21 */ f[20]=EE_FPU_MUL_S(f[0],f[21]);
/* 00265edc: c.lt.S f20,f1 */ condition=EE_FPU_COMPARE_S(f[20],f[1],1)!=0;
/* 00265ee0: bc1tl 0x00265ee8 */ {int taken=(condition!=0);if(taken){/* delay 00265ee4 */ f[20]=f[1];goto L_00265ee8;}}
L_00265ee8:;
/* 00265ee8: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00265eec: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00265ef0: c.lt.S f0,f20 */ condition=EE_FPU_COMPARE_S(f[0],f[20],1)!=0;
/* 00265ef4: bc1tl 0x00265efc */ {int taken=(condition!=0);if(taken){/* delay 00265ef8 */ f[20]=f[0];goto L_00265efc;}}
L_00265efc:;
/* 00265efc: jal 0x00267788 */ set(31,0x00265f04u);/* delay 00265f00 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));nocturneBattleActionSkillCall(0x00267788u);
/* 00265f04: li v1,0x100 */ set(3,sx(UINT32_C(0x00000100)));
/* 00265f08: bne v0,v1,0x00265f1c */ {int taken=(cpu(2)!=cpu(3));/* delay 00265f0c */ if(taken){goto L_00265f1c;}}
/* 00265f10: lui at,0x3e80 */ set(1,sx(UINT32_C(0x3e800000)));
/* 00265f14: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00265f18: mul.S f20,f20,f0 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);
L_00265f1c:;
/* 00265f1c: cvt.w.S f0,f20 */ f[0]=EE_FPU_CVT_W_S(f[20]);
/* 00265f20: mfc1 s0,f0 */ set(16,sx(f[0]));
/* 00265f24: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00265f28: b 0x0026603c */ /* delay 00265f2c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000049e0)));goto L_0026603c;
L_00265f30:;
/* 00265f30: lw v0,0x0(s4) */ lw(2,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 00265f34: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00265f38: beq v0,zero,0x00265f78 */ {int taken=(cpu(2)==cpu(0));/* delay 00265f3c */ if(taken){goto L_00265f78;}}
/* 00265f40: jal 0x00242d50 */ set(31,0x00265f48u);/* delay 00265f44 */ set(4,cpu(19));body_00242d50();
/* 00265f48: move a0,s4 */ set(4,cpu(20));
/* 00265f4c: jal 0x00242cb0 */ set(31,0x00265f54u);/* delay 00265f50 */ set(16,cpu(2));body_00242cb0();
/* 00265f54: sll v1,s0,0x1 */ set(3,sx((uint32_t)cpu(16)<<1));
/* 00265f58: li a0,0x64 */ set(4,sx(UINT32_C(0x00000064)));
/* 00265f5c: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00265f60: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 00265f64: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00265f68: lui at,0x42be */ set(1,sx(UINT32_C(0x42be0000)));
/* 00265f6c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00265f70: b 0x00265fac */ /* delay 00265f74 */ set(3,sx((uint32_t)cpu(3)<<3));goto L_00265fac;
L_00265f78:;
/* 00265f78: jal 0x00242d50 */ set(31,0x00265f80u);/* delay 00265f7c */ set(4,cpu(19));body_00242d50();
/* 00265f80: move a0,s4 */ set(4,cpu(20));
/* 00265f84: jal 0x00242cb0 */ set(31,0x00265f8cu);/* delay 00265f88 */ set(16,cpu(2));body_00242cb0();
/* 00265f8c: sll v1,s0,0x1 */ set(3,sx((uint32_t)cpu(16)<<1));
/* 00265f90: li a0,0x64 */ set(4,sx(UINT32_C(0x00000064)));
/* 00265f94: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00265f98: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 00265f9c: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 00265fa0: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00265fa4: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00265fa8: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
L_00265fac:;
/* 00265fac: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00265fb0: beql v0,zero,0x00265fb8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00265fb4 */ nocturneCompilerArithmeticTrap(7u);goto L_00265fb8;}}
L_00265fb8:;
/* 00265fb8: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00265fbc: div v1,v0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(2),1,0);
/* 00265fc0: mflo v1 */ set(3,nocturneEffectHostLo());
/* 00265fc4: subu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(3)));
/* 00265fc8: mtc1 a0,f0 */ f[0]=(uint32_t)cpu(4);
/* 00265fcc: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00265fd0: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 00265fd4: add.S f20,f0,f1 */ f[20]=EE_FPU_ADD_S(f[0],f[1]);
/* 00265fd8: mul.S f0,f20,f22 */ f[0]=EE_FPU_MUL_S(f[20],f[22]);
/* 00265fdc: lui at,0x4248 */ set(1,sx(UINT32_C(0x42480000)));
/* 00265fe0: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00265fe4: mul.S f0,f0,f23 */ f[0]=EE_FPU_MUL_S(f[0],f[23]);
/* 00265fe8: mul.S f20,f0,f21 */ f[20]=EE_FPU_MUL_S(f[0],f[21]);
/* 00265fec: c.lt.S f20,f1 */ condition=EE_FPU_COMPARE_S(f[20],f[1],1)!=0;
/* 00265ff0: bc1tl 0x00265ff8 */ {int taken=(condition!=0);if(taken){/* delay 00265ff4 */ f[20]=f[1];goto L_00265ff8;}}
L_00265ff8:;
/* 00265ff8: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 00265ffc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00266000: c.lt.S f0,f20 */ condition=EE_FPU_COMPARE_S(f[0],f[20],1)!=0;
/* 00266004: bc1tl 0x0026600c */ {int taken=(condition!=0);if(taken){/* delay 00266008 */ f[20]=f[0];goto L_0026600c;}}
L_0026600c:;
/* 0026600c: jal 0x00267788 */ set(31,0x00266014u);/* delay 00266010 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));nocturneBattleActionSkillCall(0x00267788u);
/* 00266014: li v1,0x100 */ set(3,sx(UINT32_C(0x00000100)));
/* 00266018: bne v0,v1,0x0026602c */ {int taken=(cpu(2)!=cpu(3));/* delay 0026601c */ if(taken){goto L_0026602c;}}
/* 00266020: lui at,0x3e80 */ set(1,sx(UINT32_C(0x3e800000)));
/* 00266024: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00266028: mul.S f20,f20,f0 */ f[20]=EE_FPU_MUL_S(f[20],f[0]);
L_0026602c:;
/* 0026602c: cvt.w.S f0,f20 */ f[0]=EE_FPU_CVT_W_S(f[20]);
/* 00266030: mfc1 s0,f0 */ set(16,sx(f[0]));
/* 00266034: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00266038: addiu a0,a0,0x49f8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000049f8)));
L_0026603c:;
/* 0026603c: jal 0x002d4748 */ set(31,0x00266044u);/* delay 00266040 */ set(5,cpu(16));nocturneBattleActionSkillCall(0x002d4748u);
/* 00266044: move a0,zero */ set(4,cpu(0));
/* 00266048: jal 0x002c0c60 */ set(31,0x00266050u);/* delay 0026604c */ set(5,sx(UINT32_C(0x00000064)));nocturneBattleActionSkillCall(0x002c0c60u);
/* 00266050: slt v0,v0,s0 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(16));
/* 00266054: bnel v0,zero,0x0026607c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00266058 */ set(2,cpu(0));goto L_0026607c;}}
/* 0026605c: lw v0,0x4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 00266060: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 00266064: andi a0,v0,0x800 */ set(4,cpu(2)&UINT32_C(0x00000800));
/* 00266068: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 0026606c: b 0x0026607c */ /* delay 00266070 */ if(cpu(4)==0){set(2,cpu(3));}goto L_0026607c;
L_00266078:;
/* 00266078: move v0,zero */ set(2,cpu(0));
L_0026607c:;
/* 0026607c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
L_00266080:;
/* 00266080: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00266084: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00266088: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026608c: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00266090: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00266094: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00266098: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0026609c: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002660a0: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002660a4: lwc1 f23,0x78(sp) */ f[23]=word(ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002660a8: lwc1 f22,0x70(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002660ac: lwc1 f21,0x68(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002660b0: lwc1 f20,0x60(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002660b4: jr ra */ {uint64_t target=cpu(31);/* delay 002660b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));checkReturn(target,incoming);return;}
}
static void body_00267e50(void){
nocturneEffectAxisNoteEntry(0x00267e50u);
uint64_t incoming=cpu(31);
/* 00267e50: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00267e54: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267e58: move s0,a1 */ set(16,cpu(5));
/* 00267e5c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00267e60: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00267e64: jal 0x00246a40 */ set(31,0x00267e6cu);/* delay 00267e68 */ set(17,cpu(6));nocturneBattleActionSkillCall(0x00246a40u);
/* 00267e6c: sll s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)<<1));
/* 00267e70: beq v0,zero,0x00267e7c */ {int taken=(cpu(2)==cpu(0));/* delay 00267e74 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));if(taken){goto L_00267e7c;}}
/* 00267e78: sh s1,0x8(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(17));
L_00267e7c:;
/* 00267e7c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267e80: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00267e84: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00267e88: jr ra */ {uint64_t target=cpu(31);/* delay 00267e8c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00267ec8(void){
nocturneEffectAxisNoteEntry(0x00267ec8u);
uint64_t incoming=cpu(31);
/* 00267ec8: sltiu v0,a0,0x14 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000014));
/* 00267ecc: beq v0,zero,0x00267f0c */ {int taken=(cpu(2)==cpu(0));/* delay 00267ed0 */ set(3,cpu(0));if(taken){goto L_00267f0c;}}
/* 00267ed4: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00267ed8: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00267edc: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00267ee0: lw v1,0x4c60(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004c60)));
/* 00267ee4: jr v1 */ {uint64_t target=cpu(3);/* delay 00267ee8 */ switch((uint32_t)target){case 0x00267ef0u:goto L_00267ef0;case 0x00267ef8u:goto L_00267ef8;case 0x00267f00u:goto L_00267f00;case 0x00267f08u:goto L_00267f08;default:abort();}}
L_00267ef0:;
/* 00267ef0: b 0x00267f0c */ /* delay 00267ef4 */ set(3,sx(UINT32_C(0x0000007f)));goto L_00267f0c;
L_00267ef8:;
/* 00267ef8: b 0x00267f0c */ /* delay 00267efc */ set(3,sx(UINT32_C(0x00000004)));goto L_00267f0c;
L_00267f00:;
/* 00267f00: b 0x00267f0c */ /* delay 00267f04 */ set(3,sx(UINT32_C(0x00000001)));goto L_00267f0c;
L_00267f08:;
/* 00267f08: li v1,0x7fff */ set(3,sx(UINT32_C(0x00007fff)));
L_00267f0c:;
/* 00267f0c: jr ra */ {uint64_t target=cpu(31);/* delay 00267f10 */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
static void body_00267f18(void){
nocturneEffectAxisNoteEntry(0x00267f18u);
uint64_t incoming=cpu(31);
/* 00267f18: sltiu v0,a0,0x14 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000014));
/* 00267f1c: beq v0,zero,0x00267f4c */ {int taken=(cpu(2)==cpu(0));/* delay 00267f20 */ set(3,cpu(0));if(taken){goto L_00267f4c;}}
/* 00267f24: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00267f28: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00267f2c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00267f30: lw v1,0x4cb0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004cb0)));
/* 00267f34: jr v1 */ {uint64_t target=cpu(3);/* delay 00267f38 */ switch((uint32_t)target){case 0x00267f40u:goto L_00267f40;case 0x00267f48u:goto L_00267f48;default:abort();}}
L_00267f40:;
/* 00267f40: b 0x00267f4c */ /* delay 00267f44 */ set(3,sx(UINT32_C(0xfffffffc)));goto L_00267f4c;
L_00267f48:;
/* 00267f48: move v1,zero */ set(3,cpu(0));
L_00267f4c:;
/* 00267f4c: jr ra */ {uint64_t target=cpu(31);/* delay 00267f50 */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
static void body_0026a448(void){
nocturneEffectAxisNoteEntry(0x0026a448u);
uint64_t incoming=cpu(31);
/* 0026a448: sll v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)<<4));
/* 0026a44c: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 0026a450: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0026a454: lui v0,0x3d */ set(2,sx(UINT32_C(0x003d0000)));
/* 0026a458: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0026a45c: lbu v0,0x79a0(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0x000079a0))));
/* 0026a460: jr ra */ {uint64_t target=cpu(31);/* delay 0026a464 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));checkReturn(target,incoming);return;}
}
static void body_0026a4b0(void){
nocturneEffectAxisNoteEntry(0x0026a4b0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 0026a4b0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0026a4b4: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0026a4b8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a4bc: move s1,a0 */ set(17,cpu(4));
/* 0026a4c0: swc1 f21,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[21]);
/* 0026a4c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a4c8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026a4cc: swc1 f20,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);
/* 0026a4d0: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 0026a4d4: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0026a4d8: lwc1 f1,0xa48(v1) */ f[1]=word(ea(3,(int32_t)UINT32_C(0x00000a48)));
/* 0026a4dc: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0026a4e0: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0026a4e4: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 0026a4e8: nop  */ 
/* 0026a4ec: nop  */ 
/* 0026a4f0: div.S f21,f1,f0 */ f[21]=EE_FPU_DIV_S(f[1],f[0]);
/* 0026a4f4: beq v0,zero,0x0026a580 */ {int taken=(cpu(2)==cpu(0));/* delay 0026a4f8 */ set(5,sx(UINT32_C(0x00000005)));if(taken){goto L_0026a580;}}
/* 0026a4fc: lhu v0,0xa68(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000a68))));
/* 0026a500: addiu a0,v1,0xa54 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000a54)));
/* 0026a504: lui at,0x40a0 */ set(1,sx(UINT32_C(0x40a00000)));
/* 0026a508: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0026a50c: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0026a510: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0026a514: lui at,0x4080 */ set(1,sx(UINT32_C(0x40800000)));
/* 0026a518: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0026a51c: nop  */ 
/* 0026a520: nop  */ 
/* 0026a524: div.S f0,f0,f2 */ f[0]=EE_FPU_DIV_S(f[0],f[2]);
/* 0026a528: jal 0x00243ee0 */ set(31,0x0026a530u);/* delay 0026a52c */ f[20]=EE_FPU_ADD_S(f[0],f[1]);nocturneBattleActionSkillCall(0x00243ee0u);
/* 0026a530: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0026a534: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0026a538: lhu v1,0x4(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 0026a53c: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 0026a540: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 0026a544: nop  */ 
/* 0026a548: nop  */ 
/* 0026a54c: div.S f1,f0,f20 */ f[1]=EE_FPU_DIV_S(f[0],f[20]);
/* 0026a550: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0026a554: lui v1,0x35 */ set(3,sx(UINT32_C(0x00350000)));
/* 0026a558: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0026a55c: lhu v1,-0x6816(v1) */ set(3,half(ea(3,(int32_t)UINT32_C(0xffff97ea))));
/* 0026a560: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 0026a564: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0026a568: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0026a56c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0026a570: mfc1 s0,f1 */ set(16,sx(f[1]));
/* 0026a574: b 0x0026a5ec */ /* delay 0026a578 */ goto L_0026a5ec;
L_0026a580:;
/* 0026a580: lhu v0,0x14(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 0026a584: lui at,0x40a0 */ set(1,sx(UINT32_C(0x40a00000)));
/* 0026a588: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0026a58c: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0026a590: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0026a594: lui at,0x4080 */ set(1,sx(UINT32_C(0x40800000)));
/* 0026a598: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0026a59c: nop  */ 
/* 0026a5a0: nop  */ 
/* 0026a5a4: div.S f0,f0,f2 */ f[0]=EE_FPU_DIV_S(f[0],f[2]);
/* 0026a5a8: jal 0x00243ee0 */ set(31,0x0026a5b0u);/* delay 0026a5ac */ f[20]=EE_FPU_ADD_S(f[0],f[1]);nocturneBattleActionSkillCall(0x00243ee0u);
/* 0026a5b0: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 0026a5b4: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0026a5b8: lwc1 f2,-0x5bd8(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffa428)));
/* 0026a5bc: nop  */ 
/* 0026a5c0: nop  */ 
/* 0026a5c4: div.S f1,f1,f20 */ f[1]=EE_FPU_DIV_S(f[1],f[20]);
/* 0026a5c8: abs.S f0,f1 */ f[0]=f[1]&UINT32_C(0x7fffffff);
/* 0026a5cc: c.le.S f2,f0 */ condition=EE_FPU_COMPARE_S(f[2],f[0],2)!=0;
/* 0026a5d0: bc1fl 0x0026a5ec */ {int taken=(condition==0);if(taken){/* delay 0026a5d4 */ set(16,cpu(0));goto L_0026a5ec;}}
/* 0026a5d8: nop  */ 
/* 0026a5dc: nop  */ 
/* 0026a5e0: div.S f0,f21,f1 */ f[0]=EE_FPU_DIV_S(f[21],f[1]);
/* 0026a5e4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0026a5e8: mfc1 s0,f1 */ set(16,sx(f[1]));
L_0026a5ec:;
/* 0026a5ec: jal 0x002c0c00 */ set(31,0x0026a5f4u);/* delay 0026a5f0 */ set(4,cpu(0));nocturneBattleActionSkillCall(0x002c0c00u);
/* 0026a5f4: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0026a5f8: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0026a5fc: lwc1 f2,-0x5bd4(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffa42c)));
/* 0026a600: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 0026a604: mtc1 s0,f1 */ f[1]=(uint32_t)cpu(16);
/* 0026a608: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0026a60c: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 0026a610: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0026a614: mul.S f0,f1,f0 */ f[0]=EE_FPU_MUL_S(f[1],f[0]);
/* 0026a618: add.S f1,f1,f0 */ f[1]=EE_FPU_ADD_S(f[1],f[0]);
/* 0026a61c: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0026a620: mfc1 s0,f0 */ set(16,sx(f[0]));
/* 0026a624: jal 0x001e0f50 */ set(31,0x0026a62cu);/* delay 0026a628 */ set(4,sx(UINT32_C(0x00000af2)));nocturneBattleActionSkillCall(0x001e0f50u);
/* 0026a62c: beq v0,zero,0x0026a660 */ {int taken=(cpu(2)==cpu(0));/* delay 0026a630 */ set(3,(int64_t)cpu(0)<(int64_t)cpu(16));if(taken){goto L_0026a660;}}
/* 0026a634: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0026a638: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 0026a63c: bne v0,zero,0x0026a664 */ {int taken=(cpu(2)!=cpu(0));/* delay 0026a640 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0026a664;}}
/* 0026a644: li v0,0xa */ set(2,sx(UINT32_C(0x0000000a)));
/* 0026a648: div s0,v0 */ nativeDivide((uint32_t)cpu(16),(uint32_t)cpu(2),1,0);
/* 0026a64c: beql v0,zero,0x0026a654 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0026a650 */ nocturneCompilerArithmeticTrap(7u);goto L_0026a654;}}
L_0026a654:;
/* 0026a654: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0026a658: move s0,v0 */ set(16,cpu(2));
/* 0026a65c: slt v1,zero,s0 */ set(3,(int64_t)cpu(0)<(int64_t)cpu(16));
L_0026a660:;
/* 0026a660: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_0026a664:;
/* 0026a664: movn v0,s0,v1 */ if(cpu(3)!=0){set(2,cpu(16));}
/* 0026a668: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a66c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a670: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026a674: lwc1 f21,0x20(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0026a678: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026a67c: jr ra */ {uint64_t target=cpu(31);/* delay 0026a680 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002aa438(void){
nocturneEffectAxisNoteEntry(0x002aa438u);
uint64_t incoming=cpu(31);
/* 002aa438: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002aa43c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa440: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aa444: move s2,a0 */ set(18,cpu(4));
/* 002aa448: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aa44c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002aa450: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa454: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002aa458: jal 0x002e4070 */ set(31,0x002aa460u);/* delay 002aa45c */ set(19,cpu(5));nocturneBattleActionSkillCall(0x002e4070u);
/* 002aa460: lw s0,-0x20e0(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffdf20)));
/* 002aa464: move s4,v0 */ set(20,cpu(2));
L_002aa468:;
/* 002aa468: bnel s0,zero,0x002aa498 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 002aa46c */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_002aa498;}}
/* 002aa470: beq s4,zero,0x002aa484 */ {int taken=(cpu(20)==cpu(0));/* delay 002aa474 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6ec)));if(taken){goto L_002aa484;}}
/* 002aa478: jal 0x002e40b8 */ set(31,0x002aa480u);/* delay 002aa47c */ nocturneBattleActionSkillCall(0x002e40b8u);
/* 002aa480: lw v0,-0x2914(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6ec)));
L_002aa484:;
/* 002aa484: beq v0,zero,0x002aa494 */ {int taken=(cpu(2)==cpu(0));/* delay 002aa488 */ set(4,cpu(18));if(taken){goto L_002aa494;}}
/* 002aa48c: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002aa494u);/* delay 002aa490 */ set(5,cpu(19));nocturneBattleActionSkillCall((uint32_t)target);}
L_002aa494:;
/* 002aa494: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
L_002aa498:;
/* 002aa498: bnel v0,zero,0x002aa468 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002aa49c */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002aa468;}}
/* 002aa4a0: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002aa4a4: slt v0,v1,s2 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(18));
/* 002aa4a8: bnel v0,zero,0x002aa468 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002aa4ac */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002aa468;}}
/* 002aa4b0: bne v1,s2,0x002aa4d0 */ {int taken=(cpu(3)!=cpu(18));/* delay 002aa4b4 */ if(taken){goto L_002aa4d0;}}
/* 002aa4b8: beq s4,zero,0x002aa4c8 */ {int taken=(cpu(20)==cpu(0));/* delay 002aa4bc */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));if(taken){goto L_002aa4c8;}}
/* 002aa4c0: jal 0x002e40b8 */ set(31,0x002aa4c8u);/* delay 002aa4c4 */ nocturneBattleActionSkillCall(0x002e40b8u);
L_002aa4c8:;
/* 002aa4c8: b 0x002aa538 */ /* delay 002aa4cc */ set(2,cpu(16));goto L_002aa538;
L_002aa4d0:;
/* 002aa4d0: jal 0x002a8af8 */ set(31,0x002aa4d8u);/* delay 002aa4d4 */ set(4,sx(UINT32_C(0x0000001c)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 002aa4d8: move s1,v0 */ set(17,cpu(2));
/* 002aa4dc: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002aa4e0: bne v0,zero,0x002aa4f0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002aa4e4 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_002aa4f0;}}
/* 002aa4e8: b 0x002aa4f8 */ /* delay 002aa4ec */ sw(ea(28,(int32_t)UINT32_C(0xffffdf20)),(uint32_t)cpu(17));goto L_002aa4f8;
L_002aa4f0:;
/* 002aa4f0: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002aa4f4: sw s1,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
L_002aa4f8:;
/* 002aa4f8: sw s3,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));
/* 002aa4fc: sw s1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002aa500: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002aa504: sw s2,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 002aa508: sw v0,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002aa50c: sw s0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002aa510: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002aa514: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002aa518: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 002aa51c: subu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(18)));
/* 002aa520: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002aa524: beq s4,zero,0x002aa534 */ {int taken=(cpu(20)==cpu(0));/* delay 002aa528 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));if(taken){goto L_002aa534;}}
/* 002aa52c: jal 0x002e40b8 */ set(31,0x002aa534u);/* delay 002aa530 */ nocturneBattleActionSkillCall(0x002e40b8u);
L_002aa534:;
/* 002aa534: move v0,s1 */ set(2,cpu(17));
L_002aa538:;
/* 002aa538: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa53c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa540: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aa544: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aa548: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002aa54c: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002aa550: jr ra */ {uint64_t target=cpu(31);/* delay 002aa554 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002acb90(void){
nocturneEffectAxisNoteEntry(0x002acb90u);
uint64_t incoming=cpu(31);
/* 002acb90: ori v0,zero,0xffff */ set(2,cpu(0)|UINT32_C(0x0000ffff));
/* 002acb94: sw zero,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 002acb98: sw v0,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002acb9c: sw zero,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002acba0: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002acba4: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002acba8: sw zero,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002acbac: sw zero,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002acbb0: jr ra */ {uint64_t target=cpu(31);/* delay 002acbb4 */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_002acbb8(void){
nocturneEffectAxisNoteEntry(0x002acbb8u);
uint64_t incoming=cpu(31);
/* 002acbb8: lw a2,0x8(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002acbbc: bne a2,zero,0x002acbd0 */ {int taken=(cpu(6)!=cpu(0));/* delay 002acbc0 */ set(2,sx(UINT32_C(0x0fff0000)));if(taken){goto L_002acbd0;}}
/* 002acbc4: b 0x002acbe4 */ /* delay 002acbc8 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));goto L_002acbe4;
L_002acbd0:;
/* 002acbd0: li v1,0x20 */ set(3,sx(UINT32_C(0x00000020)));
/* 002acbd4: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002acbd8: sb v1,0x3(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(3));
/* 002acbdc: and v0,a1,v0 */ set(2,cpu(5)&cpu(2));
/* 002acbe0: sw v0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002acbe4:;
/* 002acbe4: jr ra */ {uint64_t target=cpu(31);/* delay 002acbe8 */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_002ad130(void){
nocturneEffectAxisNoteEntry(0x002ad130u);
uint64_t incoming=cpu(31);
/* 002ad130: addiu a3,a1,0x1 */ set(7,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002ad134: lui v0,0x5000 */ set(2,sx(UINT32_C(0x50000000)));
/* 002ad138: or v0,a3,v0 */ set(2,cpu(7)|cpu(2));
/* 002ad13c: lui a2,0x1000 */ set(6,sx(UINT32_C(0x10000000)));
/* 002ad140: lui v1,0x1000 */ set(3,sx(UINT32_C(0x10000000)));
/* 002ad144: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002ad148: ori v1,v1,0x8000 */ set(3,cpu(3)|UINT32_C(0x00008000));
/* 002ad14c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002ad150: or v1,a1,v1 */ set(3,cpu(5)|cpu(3));
/* 002ad154: li a1,0xe */ set(5,sx(UINT32_C(0x0000000e)));
/* 002ad158: or v0,v0,a2 */ set(2,cpu(2)|cpu(6));
/* 002ad15c: sd a1,0x18(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002ad160: sd v0,0x8(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002ad164: sd v1,0x10(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002ad168: jr ra */ {uint64_t target=cpu(31);/* delay 002ad16c */ save(7,ea(4,(int32_t)UINT32_C(0x00000000)));checkReturn(target,incoming);return;}
}
static void body_002ad1f8(void){
nocturneEffectAxisNoteEntry(0x002ad1f8u);
uint64_t incoming=cpu(31);
/* 002ad1f8: move t5,a0 */ set(13,cpu(4));
/* 002ad1fc: addiu a0,a2,0x3f */ set(4,sx((uint32_t)cpu(6)+UINT32_C(0x0000003f)));
/* 002ad200: sra a0,a0,0x6 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>6)));
/* 002ad204: addiu v1,a3,-0x1 */ set(3,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002ad208: addiu v0,a2,-0x1 */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002ad20c: sll a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)<<16));
/* 002ad210: sll t0,t0,0x18 */ set(8,sx((uint32_t)cpu(8)<<24));
/* 002ad214: lw t4,0x0(sp) */ lw(12,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ad218: dsll32 v1,v1,0x10 */ set(3,cpu(3)<<48);
/* 002ad21c: dsll v0,v0,0x10 */ set(2,cpu(2)<<16);
/* 002ad220: sra a1,a1,0xb */ set(5,sx((uint32_t)((int32_t)cpu(5)>>11)));
/* 002ad224: sra t1,t1,0xb */ set(9,sx((uint32_t)((int32_t)cpu(9)>>11)));
/* 002ad228: or t0,t0,a0 */ set(8,cpu(8)|cpu(4));
/* 002ad22c: sll t2,t2,0x18 */ set(10,sx((uint32_t)cpu(10)<<24));
/* 002ad230: or t6,v1,v0 */ set(14,cpu(3)|cpu(2));
/* 002ad234: or t0,t0,a1 */ set(8,cpu(8)|cpu(5));
/* 002ad238: bne t4,zero,0x002ad258 */ {int taken=(cpu(12)!=cpu(0));/* delay 002ad23c */ set(10,cpu(10)|cpu(9));if(taken){goto L_002ad258;}}
/* 002ad240: li t1,0x4c */ set(9,sx(UINT32_C(0x0000004c)));
/* 002ad244: li t4,0x4e */ set(12,sx(UINT32_C(0x0000004e)));
/* 002ad248: li a1,0x18 */ set(5,sx(UINT32_C(0x00000018)));
/* 002ad24c: b 0x002ad268 */ /* delay 002ad250 */ set(3,sx(UINT32_C(0x00000040)));goto L_002ad268;
L_002ad258:;
/* 002ad258: li t1,0x4d */ set(9,sx(UINT32_C(0x0000004d)));
/* 002ad25c: li t4,0x4f */ set(12,sx(UINT32_C(0x0000004f)));
/* 002ad260: li a1,0x19 */ set(5,sx(UINT32_C(0x00000019)));
/* 002ad264: li v1,0x41 */ set(3,sx(UINT32_C(0x00000041)));
L_002ad268:;
/* 002ad268: li v0,0x1000 */ set(2,sx(UINT32_C(0x00001000)));
/* 002ad26c: sd v1,0x38(t5) */ save(3,ea(13,(int32_t)UINT32_C(0x00000038)));
/* 002ad270: subu v1,v0,a3 */ set(3,sx((uint32_t)cpu(2)-(uint32_t)cpu(7)));
/* 002ad274: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 002ad278: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 002ad27c: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 002ad280: addiu a0,v1,0x8 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 002ad284: sd t0,0x0(t5) */ save(8,ea(13,(int32_t)UINT32_C(0x00000000)));
/* 002ad288: movn v1,a0,t3 */ if(cpu(11)!=0){set(3,cpu(4));}
/* 002ad28c: sd t1,0x8(t5) */ save(9,ea(13,(int32_t)UINT32_C(0x00000008)));
/* 002ad290: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002ad294: sd t2,0x10(t5) */ save(10,ea(13,(int32_t)UINT32_C(0x00000010)));
/* 002ad298: or v1,v0,v1 */ set(3,cpu(2)|cpu(3));
/* 002ad29c: sd t4,0x18(t5) */ save(12,ea(13,(int32_t)UINT32_C(0x00000018)));
/* 002ad2a0: sd a1,0x28(t5) */ save(5,ea(13,(int32_t)UINT32_C(0x00000028)));
/* 002ad2a4: sd t6,0x30(t5) */ save(14,ea(13,(int32_t)UINT32_C(0x00000030)));
/* 002ad2a8: jr ra */ {uint64_t target=cpu(31);/* delay 002ad2ac */ save(3,ea(13,(int32_t)UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002ad2b0(void){
nocturneEffectAxisNoteEntry(0x002ad2b0u);
uint64_t incoming=cpu(31);
/* 002ad2b0: li v0,0x1000 */ set(2,sx(UINT32_C(0x00001000)));
/* 002ad2b4: addiu a3,a2,0x1000 */ set(7,sx((uint32_t)cpu(6)+UINT32_C(0x00001000)));
/* 002ad2b8: subu v1,v0,a1 */ set(3,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 002ad2bc: addiu a1,a1,0x1000 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001000)));
/* 002ad2c0: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 002ad2c4: li a2,0x6 */ set(6,sx(UINT32_C(0x00000006)));
/* 002ad2c8: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 002ad2cc: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 002ad2d0: sll v0,v0,0x13 */ set(2,sx((uint32_t)cpu(2)<<19));
/* 002ad2d4: sll a3,a3,0x13 */ set(7,sx((uint32_t)cpu(7)<<19));
/* 002ad2d8: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002ad2dc: lui v1,0x3 */ set(3,sx(UINT32_C(0x00030000)));
/* 002ad2e0: ori v1,v1,0x3 */ set(3,cpu(3)|UINT32_C(0x00000003));
/* 002ad2e4: or a3,a3,a1 */ set(7,cpu(7)|cpu(5));
/* 002ad2e8: li a1,0x47 */ set(5,sx(UINT32_C(0x00000047)));
/* 002ad2ec: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002ad2f0: dsll32 a3,a3,0x0 */ set(7,cpu(7)<<32);
/* 002ad2f4: li t2,0x5 */ set(10,sx(UINT32_C(0x00000005)));
/* 002ad2f8: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002ad2fc: dsrl32 a3,a3,0x0 */ set(7,cpu(7)>>32);
/* 002ad300: ori t0,zero,0xfe00 */ set(8,cpu(0)|UINT32_C(0x0000fe00));
/* 002ad304: dsll32 t0,t0,0xe */ set(8,cpu(8)<<46);
/* 002ad308: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 002ad30c: sd t2,0x48(a0) */ save(10,ea(4,(int32_t)UINT32_C(0x00000048)));
/* 002ad310: sd v1,0x0(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002ad314: sd a1,0x8(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002ad318: sd a2,0x10(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002ad31c: sd t0,0x20(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002ad320: sd t1,0x28(a0) */ save(9,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002ad324: sd v0,0x30(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002ad328: sd a3,0x40(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 002ad32c: sd zero,0x18(a0) */ save(0,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002ad330: jr ra */ {uint64_t target=cpu(31);/* delay 002ad334 */ save(10,ea(4,(int32_t)UINT32_C(0x00000038)));checkReturn(target,incoming);return;}
}
static void body_002ad338(void){
nocturneEffectAxisNoteEntry(0x002ad338u);
uint64_t incoming=cpu(31);
/* 002ad338: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 002ad33c: li v1,0x1a */ set(3,sx(UINT32_C(0x0000001a)));
/* 002ad340: li a1,0x46 */ set(5,sx(UINT32_C(0x00000046)));
/* 002ad344: li a2,0x45 */ set(6,sx(UINT32_C(0x00000045)));
/* 002ad348: li a3,0x40 */ set(7,sx(UINT32_C(0x00000040)));
/* 002ad34c: dsll32 a3,a3,0x0 */ set(7,cpu(7)<<32);
/* 002ad350: ori a3,a3,0x80 */ set(7,cpu(7)|UINT32_C(0x00000080));
/* 002ad354: li v0,0x3b */ set(2,sx(UINT32_C(0x0000003b)));
/* 002ad358: sd v1,0x8(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002ad35c: sd v0,0x38(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000038)));
/* 002ad360: sd t0,0x10(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002ad364: sd a1,0x18(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002ad368: sd a2,0x28(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002ad36c: sd a3,0x30(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002ad370: sd t0,0x0(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002ad374: jr ra */ {uint64_t target=cpu(31);/* delay 002ad378 */ save(0,ea(4,(int32_t)UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002ad428(void){
nocturneEffectAxisNoteEntry(0x002ad428u);
uint64_t incoming=cpu(31);
/* 002ad428: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002ad42c: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ad430: move s0,a2 */ set(16,cpu(6));
/* 002ad434: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ad438: move s1,a1 */ set(17,cpu(5));
/* 002ad43c: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 002ad440: li a1,0x15 */ set(5,sx(UINT32_C(0x00000015)));
/* 002ad444: addu s0,s1,s0 */ set(16,sx((uint32_t)cpu(17)+(uint32_t)cpu(16)));
/* 002ad448: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ad44c: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ad450: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ad454: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ad458: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ad45c: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002ad460: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002ad464: jal 0x002ad130 */ set(31,0x002ad46cu);/* delay 002ad468 */ set(18,cpu(4));body_002ad130();
/* 002ad46c: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002ad470: addiu a0,s2,0x60 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000060)));
/* 002ad474: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002ad478: lw s4,0xc(v1) */ lw(20,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 002ad47c: lw s7,0xc(v0) */ lw(23,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002ad480: lh s5,0x0(s1) */ set(21,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000000))));
/* 002ad484: move a1,s4 */ set(5,cpu(20));
/* 002ad488: lbu s6,0x6(s1) */ set(22,byte(ea(17,(int32_t)UINT32_C(0x00000006))));
/* 002ad48c: move t1,s7 */ set(9,cpu(23));
/* 002ad490: lh s0,0x4(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 002ad494: move a2,s5 */ set(6,cpu(21));
/* 002ad498: lbu s3,0x7(s1) */ set(19,byte(ea(17,(int32_t)UINT32_C(0x00000007))));
/* 002ad49c: move t0,s6 */ set(8,cpu(22));
/* 002ad4a0: lbu t3,-0x28e6(gp) */ set(11,byte(ea(28,(int32_t)UINT32_C(0xffffd71a))));
/* 002ad4a4: move a3,s0 */ set(7,cpu(16));
/* 002ad4a8: move t2,s3 */ set(10,cpu(19));
/* 002ad4ac: jal 0x002ad1f8 */ set(31,0x002ad4b4u);/* delay 002ad4b0 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));body_002ad1f8();
/* 002ad4b4: lbu t3,-0x28e6(gp) */ set(11,byte(ea(28,(int32_t)UINT32_C(0xffffd71a))));
/* 002ad4b8: move t1,s7 */ set(9,cpu(23));
/* 002ad4bc: move t2,s3 */ set(10,cpu(19));
/* 002ad4c0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002ad4c4: move a1,s4 */ set(5,cpu(20));
/* 002ad4c8: move a2,s5 */ set(6,cpu(21));
/* 002ad4cc: move a3,s0 */ set(7,cpu(16));
/* 002ad4d0: move t0,s6 */ set(8,cpu(22));
/* 002ad4d4: addiu a0,s2,0xa0 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x000000a0)));
/* 002ad4d8: jal 0x002ad1f8 */ set(31,0x002ad4e0u);/* delay 002ad4dc */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));body_002ad1f8();
/* 002ad4e0: lbu t0,0x7(s1) */ set(8,byte(ea(17,(int32_t)UINT32_C(0x00000007))));
/* 002ad4e4: addiu a0,s2,0xe0 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x000000e0)));
/* 002ad4e8: lh a1,0x0(s1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000000))));
/* 002ad4ec: lh a2,0x4(s1) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 002ad4f0: jal 0x002ad2b0 */ set(31,0x002ad4f8u);/* delay 002ad4f4 */ set(7,byte(ea(17,(int32_t)UINT32_C(0x00000006))));body_002ad2b0();
/* 002ad4f8: lui a3,0x5 */ set(7,sx(UINT32_C(0x00050000)));
/* 002ad4fc: ori a3,a3,0x17fb */ set(7,cpu(7)|UINT32_C(0x000017fb));
/* 002ad500: li t0,0x44 */ set(8,sx(UINT32_C(0x00000044)));
/* 002ad504: li v0,0x47 */ set(2,sx(UINT32_C(0x00000047)));
/* 002ad508: li v1,0x42 */ set(3,sx(UINT32_C(0x00000042)));
/* 002ad50c: li a1,0x48 */ set(5,sx(UINT32_C(0x00000048)));
/* 002ad510: li a2,0x43 */ set(6,sx(UINT32_C(0x00000043)));
/* 002ad514: sd v0,0x138(s2) */ save(2,ea(18,(int32_t)UINT32_C(0x00000138)));
/* 002ad518: sd v1,0x148(s2) */ save(3,ea(18,(int32_t)UINT32_C(0x00000148)));
/* 002ad51c: addiu a0,s2,0x20 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000020)));
/* 002ad520: sd a3,0x150(s2) */ save(7,ea(18,(int32_t)UINT32_C(0x00000150)));
/* 002ad524: sd a1,0x158(s2) */ save(5,ea(18,(int32_t)UINT32_C(0x00000158)));
/* 002ad528: sd t0,0x160(s2) */ save(8,ea(18,(int32_t)UINT32_C(0x00000160)));
/* 002ad52c: sd a2,0x168(s2) */ save(6,ea(18,(int32_t)UINT32_C(0x00000168)));
/* 002ad530: sd a3,0x130(s2) */ save(7,ea(18,(int32_t)UINT32_C(0x00000130)));
/* 002ad534: sd t0,0x140(s2) */ save(8,ea(18,(int32_t)UINT32_C(0x00000140)));
/* 002ad538: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ad53c: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ad540: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ad544: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ad548: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ad54c: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ad550: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ad554: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002ad558: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002ad55c: j 0x002ad338 */ /* delay 002ad560 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(cpu(31),incoming);body_002ad338();return;
}
static void body_002b6550(void){
nocturneEffectAxisNoteEntry(0x002b6550u);
uint64_t incoming=cpu(31);
/* 002b6550: vmulax.xyzw ACC,vf28,vf24 */ vuMula(28,24,0);
/* 002b6554: vmadday.xyzw ACC,vf29,vf24 */ vuMadda(29,24,1);
/* 002b6558: vmaddaz.xyzw ACC,vf30,vf24 */ vuMadda(30,24,2);
/* 002b655c: vmaddw.xyzw vf2,vf31,vf24 */ vuMadd(2,31,24,3);
/* 002b6560: vmulax.xyzw ACC,vf28,vf25 */ vuMula(28,25,0);
/* 002b6564: vmadday.xyzw ACC,vf29,vf25 */ vuMadda(29,25,1);
/* 002b6568: vmaddaz.xyzw ACC,vf30,vf25 */ vuMadda(30,25,2);
/* 002b656c: vmaddw.xyzw vf3,vf31,vf25 */ vuMadd(3,31,25,3);
/* 002b6570: vmulax.xyzw ACC,vf28,vf26 */ vuMula(28,26,0);
/* 002b6574: vmadday.xyzw ACC,vf29,vf26 */ vuMadda(29,26,1);
/* 002b6578: vmaddaz.xyzw ACC,vf30,vf26 */ vuMadda(30,26,2);
/* 002b657c: vmaddw.xyzw vf4,vf31,vf26 */ vuMadd(4,31,26,3);
/* 002b6580: vmulax.xyzw ACC,vf28,vf27 */ vuMula(28,27,0);
/* 002b6584: vmadday.xyzw ACC,vf29,vf27 */ vuMadda(29,27,1);
/* 002b6588: vmaddaz.xyzw ACC,vf30,vf27 */ vuMadda(30,27,2);
/* 002b658c: vmaddw.xyzw vf31,vf31,vf27 */ vuMadd(31,31,27,3);
/* 002b6590: vmove.xyzw vf28,vf2 */ moveVu(28,2);
/* 002b6594: vmove.xyzw vf29,vf3 */ moveVu(29,3);
/* 002b6598: vmove.xyzw vf30,vf4 */ moveVu(30,4);
/* 002b659c: jr ra */ {uint64_t target=cpu(31);/* delay 002b65a0 */ checkReturn(target,incoming);return;}
}
static void body_002b66b8(void){
nocturneEffectAxisNoteEntry(0x002b66b8u);
uint64_t incoming=cpu(31);
/* 002b66b8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b66bc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b66c0: lqc2 vf24,0x0(a0) */ loadVu(24,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002b66c4: lqc2 vf25,0x10(a0) */ loadVu(25,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002b66c8: lqc2 vf26,0x20(a0) */ loadVu(26,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002b66cc: lqc2 vf27,0x30(a0) */ loadVu(27,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002b66d0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b66d4: j 0x002b65a8 */ /* delay 002b66d8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002b65a8u);return;
}
uint32_t nocturneBattleActionSkillRegisteredBody(uint32_t entry){switch(entry){
case 0x00100418u:body_00100418();return 1u;
case 0x001b1740u:body_001b1740();return 1u;
case 0x001c6018u:body_001c6018();return 1u;
case 0x001c6098u:body_001c6098();return 1u;
case 0x001c60e0u:body_001c60e0();return 1u;
case 0x001c6128u:body_001c6128();return 1u;
case 0x001c6b68u:body_001c6b68();return 1u;
case 0x001c6ff8u:body_001c6ff8();return 1u;
case 0x001c7080u:body_001c7080();return 1u;
case 0x001c7088u:body_001c7088();return 1u;
case 0x001c7288u:body_001c7288();return 1u;
case 0x001c7408u:body_001c7408();return 1u;
case 0x001c74e8u:body_001c74e8();return 1u;
case 0x001c7568u:body_001c7568();return 1u;
case 0x001c7660u:body_001c7660();return 1u;
case 0x001c76a8u:body_001c76a8();return 1u;
case 0x001c76e0u:body_001c76e0();return 1u;
case 0x001c7828u:body_001c7828();return 1u;
case 0x001c7890u:body_001c7890();return 1u;
case 0x001c7a60u:body_001c7a60();return 1u;
case 0x001c7a88u:body_001c7a88();return 1u;
case 0x001c7b30u:body_001c7b30();return 1u;
case 0x001c7b40u:body_001c7b40();return 1u;
case 0x001c7ba8u:body_001c7ba8();return 1u;
case 0x001c7c00u:body_001c7c00();return 1u;
case 0x001c7c10u:body_001c7c10();return 1u;
case 0x001c8108u:body_001c8108();return 1u;
case 0x001c8120u:body_001c8120();return 1u;
case 0x001c81b8u:body_001c81b8();return 1u;
case 0x001c8230u:body_001c8230();return 1u;
case 0x001c83b0u:body_001c83b0();return 1u;
case 0x001c83f0u:body_001c83f0();return 1u;
case 0x001c8418u:body_001c8418();return 1u;
case 0x001c8458u:body_001c8458();return 1u;
case 0x001c8508u:body_001c8508();return 1u;
case 0x001c86a0u:body_001c86a0();return 1u;
case 0x001c8730u:body_001c8730();return 1u;
case 0x001c8758u:body_001c8758();return 1u;
case 0x001c87c8u:body_001c87c8();return 1u;
case 0x001c8f08u:body_001c8f08();return 1u;
case 0x001c9188u:body_001c9188();return 1u;
case 0x001c9230u:body_001c9230();return 1u;
case 0x001c96d8u:body_001c96d8();return 1u;
case 0x001c98c0u:body_001c98c0();return 1u;
case 0x001c9a98u:body_001c9a98();return 1u;
case 0x001c9b58u:body_001c9b58();return 1u;
case 0x001c9c28u:body_001c9c28();return 1u;
case 0x001c9d00u:body_001c9d00();return 1u;
case 0x001c9d60u:body_001c9d60();return 1u;
case 0x001ca9c0u:body_001ca9c0();return 1u;
case 0x001ca9c8u:body_001ca9c8();return 1u;
case 0x001caa18u:body_001caa18();return 1u;
case 0x001cabd8u:body_001cabd8();return 1u;
case 0x001cdd78u:body_001cdd78();return 1u;
case 0x001cf178u:body_001cf178();return 1u;
case 0x001cf1a8u:body_001cf1a8();return 1u;
case 0x001cf440u:body_001cf440();return 1u;
case 0x001cfc58u:body_001cfc58();return 1u;
case 0x001cfc80u:body_001cfc80();return 1u;
case 0x00242ae8u:body_00242ae8();return 1u;
case 0x00242cb0u:body_00242cb0();return 1u;
case 0x00242d50u:body_00242d50();return 1u;
case 0x00243c28u:body_00243c28();return 1u;
case 0x00243d28u:body_00243d28();return 1u;
case 0x00244238u:body_00244238();return 1u;
case 0x00244e68u:body_00244e68();return 1u;
case 0x00244ef8u:body_00244ef8();return 1u;
case 0x00245c90u:body_00245c90();return 1u;
case 0x00251858u:body_00251858();return 1u;
case 0x00251890u:body_00251890();return 1u;
case 0x00259a60u:body_00259a60();return 1u;
case 0x00259c48u:body_00259c48();return 1u;
case 0x00261758u:body_00261758();return 1u;
case 0x00261f90u:body_00261f90();return 1u;
case 0x00262fb8u:body_00262fb8();return 1u;
case 0x00265868u:body_00265868();return 1u;
case 0x002658b8u:body_002658b8();return 1u;
case 0x00265948u:body_00265948();return 1u;
case 0x00267e50u:body_00267e50();return 1u;
case 0x00267ec8u:body_00267ec8();return 1u;
case 0x00267f18u:body_00267f18();return 1u;
case 0x0026a448u:body_0026a448();return 1u;
case 0x0026a4b0u:body_0026a4b0();return 1u;
case 0x002aa438u:body_002aa438();return 1u;
case 0x002acb90u:body_002acb90();return 1u;
case 0x002acbb8u:body_002acbb8();return 1u;
case 0x002ad130u:body_002ad130();return 1u;
case 0x002ad1f8u:body_002ad1f8();return 1u;
case 0x002ad2b0u:body_002ad2b0();return 1u;
case 0x002ad338u:body_002ad338();return 1u;
case 0x002ad428u:body_002ad428();return 1u;
case 0x002b6550u:body_002b6550();return 1u;
case 0x002b66b8u:body_002b66b8();return 1u;
default:return 0u;}}
