/* Complete original SLUS_209.11 SKILL support43 bodies.
 * Fixed native instruction statements and real guest frames, not an emulator
 * or a captured-output transport. External dispatch receives code targets only;
 * it must execute complete native bodies in the same live machine banks.
 */
#include "battle_action_skill_support_frames.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "script_compare.h"
#include "magatuhi_helpers.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static float real(uint32_t u){float v;memcpy(&v,&u,4);return v;}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
/* CPU LQ/SQ align down; original LQC2/SQC2 use their raw effective address. */
static void pkLq(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneEffectHostCpuWrite(r,q);}
static void sq(unsigned r,uint32_t a){uint32_t q[4];nocturneEffectHostCpuRead(r,q);memcpy(at(a&~15u),q,16);}
static void loadVu(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a),16);EE_ROT_VU_WRITE(r,q);}
static void storeVu(unsigned r,uint32_t a){uint32_t q[4];EE_ROT_VU_READ(r,q);memcpy(at(a),q,16);}
static void moveVu(unsigned d,unsigned s){uint32_t q[4];EE_ROT_VU_READ(s,q);EE_ROT_VU_WRITE(d,q);}
static void qmf(unsigned d,unsigned s){uint32_t q[4];EE_ROT_VU_READ(s,q);nocturneEffectHostCpuWrite(d,q);}
static void qmt(unsigned d,unsigned s){uint32_t q[4];nocturneEffectHostCpuRead(s,q);EE_ROT_VU_WRITE(d,q);}
static void pextlw(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4];nocturneEffectHostCpuRead(s,x);nocturneEffectHostCpuRead(t,y);z[0]=y[0];z[1]=x[0];z[2]=y[1];z[3]=x[1];nocturneEffectHostCpuWrite(d,z);}
static void pextuw(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4];nocturneEffectHostCpuRead(s,x);nocturneEffectHostCpuRead(t,y);z[0]=y[2];z[1]=x[2];z[2]=y[3];z[3]=x[3];nocturneEffectHostCpuWrite(d,z);}
static void pcpyld(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4];nocturneEffectHostCpuRead(s,x);nocturneEffectHostCpuRead(t,y);z[0]=y[0];z[1]=y[1];z[2]=x[0];z[3]=x[1];nocturneEffectHostCpuWrite(d,z);}
static void pcpyud(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4];nocturneEffectHostCpuRead(s,x);nocturneEffectHostCpuRead(t,y);z[0]=x[2];z[1]=x[3];z[2]=y[2];z[3]=y[3];nocturneEffectHostCpuWrite(d,z);}
static uint32_t vuLane(unsigned r,unsigned k){uint32_t q[4];EE_ROT_VU_READ(r,q);return q[k];}
static void vuMulMasked(unsigned d,unsigned s,unsigned t,unsigned mask,int component){uint32_t x[4],y[4],z[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_VU_READ(d,z);for(unsigned k=0;k<4;k++)if(mask&(8u>>k))z[k]=(uint32_t)EE_ROT_VU_MUL(x[k],y[component<0?k:(unsigned)component]);EE_ROT_VU_WRITE(d,z);}
static void vuAddMasked(unsigned d,unsigned s,unsigned t,unsigned mask){uint32_t x[4],y[4],z[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_VU_READ(d,z);for(unsigned k=0;k<4;k++)if(mask&(8u>>k))z[k]=(uint32_t)EE_ROT_VU_ADD(x[k],y[k]);EE_ROT_VU_WRITE(d,z);}
static void vuSubMasked(unsigned d,unsigned s,unsigned t,unsigned mask){uint32_t x[4],y[4],z[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_VU_READ(d,z);for(unsigned k=0;k<4;k++)if(mask&(8u>>k))z[k]=(uint32_t)EE_ROT_VU_SUB(x[k],y[k]);EE_ROT_VU_WRITE(d,z);}
static void vuMulaMasked(unsigned s,unsigned t,unsigned component,unsigned mask){uint32_t x[4],y[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t v=EE_ROT_VU_MUL(x[k],y[component]);a[k]=(uint32_t)v;o[k]=(uint32_t)(v>>32)&1u;}EE_ROT_ACC_WRITE(a,o);}
static void vuMaddaMasked(unsigned s,unsigned t,unsigned component,unsigned mask){uint32_t x[4],y[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t v=EE_ROT_VU_MAC(a[k],x[k],y[component],o[k],0);a[k]=(uint32_t)v;o[k]=(uint32_t)(v>>32)&1u;}EE_ROT_ACC_WRITE(a,o);}
static void vuMaddMasked(unsigned d,unsigned s,unsigned t,unsigned component,unsigned mask){uint32_t x[4],y[4],z[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_VU_READ(d,z);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++)if(mask&(8u>>k))z[k]=(uint32_t)EE_ROT_VU_MAC(a[k],x[k],y[component],o[k],0);EE_ROT_VU_WRITE(d,z);}
static void vuMulQMasked(unsigned d,unsigned s,uint32_t q,unsigned mask){uint32_t x[4],z[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(d,z);for(unsigned k=0;k<4;k++)if(mask&(8u>>k))z[k]=(uint32_t)EE_ROT_VU_MUL(x[k],q);EE_ROT_VU_WRITE(d,z);}
static void vuOpmula(unsigned s,unsigned t){uint32_t x[4],y[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<3;k++){uint64_t v=EE_ROT_VU_MUL(x[(k+1)%3],y[(k+2)%3]);a[k]=(uint32_t)v;o[k]=(uint32_t)(v>>32)&1u;}EE_ROT_ACC_WRITE(a,o);}
static void vuOpmsub(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_VU_READ(d,z);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<3;k++)z[k]=(uint32_t)EE_ROT_VU_MAC(a[k],x[(k+1)%3],y[(k+2)%3],o[k],1);EE_ROT_VU_WRITE(d,z);}
static void nativeSignedMultiply(unsigned rd,uint32_t a,uint32_t c){uint64_t product=(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)c);EE_MAGATUHI_MULT_STATE(product);if(rd)set(rd,sx((uint32_t)product));}

static void body_00100410(void);
static void body_00104870(void);
static void body_001049d0(void);
static void body_00104ac0(void);
static void body_00104af8(void);
static void body_0016ab70(void);
static void body_0016aba0(void);
static void body_0016aec0(void);
static void body_0016aef0(void);
static void body_0016b090(void);
static void body_0016ba40(void);
static void body_00197dd0(void);
static void body_00198200(void);
static void body_00198860(void);
static void body_00198868(void);
static void body_00198ff8(void);
static void body_001c8268(void);
static void body_001c9108(void);
static void body_001ca0d0(void);
static void body_001ca258(void);
static void body_001cea58(void);
static void body_001cf960(void);
static void body_001dd578(void);
static void body_00280518(void);
static void body_00288e18(void);
static void body_00289008(void);
static void body_00289450(void);
static void body_0028fa80(void);
static void body_002901d0(void);
static void body_00290780(void);
static void body_002aa718(void);
static void body_002aa7f0(void);
static void body_002aa8d0(void);
static void body_002ab190(void);
static void body_002ab860(void);
static void body_002abb78(void);
static void body_002b5e30(void);
static void body_002b6690(void);
static void body_002b9e30(void);
static void body_002ba070(void);
static void body_002ba250(void);
static void body_002cf6b8(void);
static void body_002d0ca8(void);
static void body_00100410(void){
nocturneEffectAxisNoteEntry(0x00100410u);
uint64_t incoming=cpu(31);
/* 00100410: jr ra */ {uint64_t target=cpu(31);/* delay 00100414 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa690)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00100410(void){
body_00100410();
return cpu(2);
}
static void body_00104870(void){
nocturneEffectAxisNoteEntry(0x00104870u);
uint64_t incoming=cpu(31);
/* 00104870: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 00104874: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 00104878: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0010487c: lui s6,0x30 */ set(22,sx(UINT32_C(0x00300000)));
/* 00104880: lhu t0,-0x581a(gp) */ set(8,half(ea(28,(int32_t)UINT32_C(0xffffa7e6))));
/* 00104884: li a2,0x30 */ set(6,sx(UINT32_C(0x00000030)));
/* 00104888: lhu a1,-0x581c(gp) */ set(5,half(ea(28,(int32_t)UINT32_C(0xffffa7e4))));
/* 0010488c: lw a3,-0x5824(gp) */ lw(7,ea(28,(int32_t)UINT32_C(0xffffa7dc)));
/* 00104890: lw v1,-0x6c68(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0xffff9398)));
/* 00104894: addiu v0,s6,-0x5d80 */ set(2,sx((uint32_t)cpu(22)+UINT32_C(0xffffa280)));
/* 00104898: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010489c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001048a0: move s3,zero */ set(19,cpu(0));
/* 001048a4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001048a8: move s4,zero */ set(20,cpu(0));
/* 001048ac: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001048b0: lui s5,0x2f */ set(21,sx(UINT32_C(0x002f0000)));
/* 001048b4: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001048b8: addiu a0,s5,0x5b80 */ set(4,sx((uint32_t)cpu(21)+UINT32_C(0x00005b80)));
/* 001048bc: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001048c0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001048c4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001048c8: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001048cc: sw v1,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 001048d0: sh a1,0x0(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(5));
/* 001048d4: sh t0,0x4(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(8));
/* 001048d8: sb a2,0x7(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000007)),(uint8_t)cpu(6));
/* 001048dc: sw a3,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(7));
/* 001048e0: sh t0,0x2(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(8));
/* 001048e4: sb zero,0x6(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(0));
/* 001048e8: jal 0x002ba070 */ set(31,0x001048f0u);/* delay 001048ec */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));body_002ba070();
/* 001048f0: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 001048f4: addiu v0,v0,-0x7eb0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff8150)));
/* 001048f8: move s2,v0 */ set(18,cpu(2));
/* 001048fc: addiu s8,v0,0x190 */ set(30,sx((uint32_t)cpu(2)+UINT32_C(0x00000190)));
/* 00104900: addiu s7,v0,0x260 */ set(23,sx((uint32_t)cpu(2)+UINT32_C(0x00000260)));
/* 00104904: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
L_00104908:;
/* 00104908: move a0,s2 */ set(4,cpu(18));
/* 0010490c: addiu v0,v0,-0x7e90 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff8170)));
/* 00104910: addu s1,s3,s8 */ set(17,sx((uint32_t)cpu(19)+(uint32_t)cpu(30)));
/* 00104914: jal 0x002acb90 */ set(31,0x0010491cu);/* delay 00104918 */ set(16,sx((uint32_t)cpu(19)+(uint32_t)cpu(2)));nocturneBattleActionSkillCall(0x002acb90u);
/* 0010491c: move a0,s0 */ set(4,cpu(16));
/* 00104920: move a2,zero */ set(6,cpu(0));
/* 00104924: addiu a1,s6,-0x5d80 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0xffffa280)));
/* 00104928: jal 0x002ad428 */ set(31,0x00104930u);/* delay 0010492c */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x002ad428u);
/* 00104930: lw v0,-0x5818(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa7e8)));
/* 00104934: move a1,s0 */ set(5,cpu(16));
/* 00104938: addu s0,s3,s7 */ set(16,sx((uint32_t)cpu(19)+(uint32_t)cpu(23)));
/* 0010493c: sw v0,0x120(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000120)),(uint32_t)cpu(2));
/* 00104940: move a0,s2 */ set(4,cpu(18));
/* 00104944: jal 0x002acbb8 */ set(31,0x0010494cu);/* delay 00104948 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00001be0)));nocturneBattleActionSkillCall(0x002acbb8u);
/* 0010494c: move a0,s1 */ set(4,cpu(17));
/* 00104950: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 00104954: addiu a1,s5,0x5b80 */ set(5,sx((uint32_t)cpu(21)+UINT32_C(0x00005b80)));
/* 00104958: jal 0x002b9e30 */ set(31,0x00104960u);/* delay 0010495c */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0xffffa2a0)));body_002b9e30();
/* 00104960: move a0,s2 */ set(4,cpu(18));
/* 00104964: jal 0x002acbb8 */ set(31,0x0010496cu);/* delay 00104968 */ set(5,cpu(17));nocturneBattleActionSkillCall(0x002acbb8u);
/* 0010496c: move a0,s0 */ set(4,cpu(16));
/* 00104970: lui v0,0x2f */ set(2,sx(UINT32_C(0x002f0000)));
/* 00104974: addiu a2,v0,0x5d20 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00005d20)));
/* 00104978: lui v0,0x2f */ set(2,sx(UINT32_C(0x002f0000)));
/* 0010497c: jal 0x002ba250 */ set(31,0x00104984u);/* delay 00104980 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00005d10)));body_002ba250();
/* 00104984: move a0,s2 */ set(4,cpu(18));
/* 00104988: move a1,s0 */ set(5,cpu(16));
/* 0010498c: jal 0x002acbb8 */ set(31,0x00104994u);/* delay 00104990 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00001be0)));nocturneBattleActionSkillCall(0x002acbb8u);
/* 00104994: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00104998: bnel s4,v0,0x00104908 */ {int taken=(cpu(20)!=cpu(2));if(taken){/* delay 0010499c */ set(2,sx(UINT32_C(0x00300000)));goto L_00104908;}}
/* 001049a0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001049a4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001049a8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001049ac: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001049b0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001049b4: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001049b8: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001049bc: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001049c0: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001049c4: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001049c8: jr ra */ {uint64_t target=cpu(31);/* delay 001049cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00104870(void){
body_00104870();
return;
}
static void body_001049d0(void){
nocturneEffectAxisNoteEntry(0x001049d0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001049d0: lw v0,-0x5820(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa7e0)));
/* 001049d4: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001049d8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001049dc: andi s1,a0,0xffff */ set(17,cpu(4)&UINT32_C(0x0000ffff));
/* 001049e0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001049e4: andi s2,a1,0xffff */ set(18,cpu(5)&UINT32_C(0x0000ffff));
/* 001049e8: swc1 f20,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[20]);
/* 001049ec: mov.S f20,f12 */ f[20]=f[12];
/* 001049f0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001049f4: beq v0,zero,0x00104a04 */ {int taken=(cpu(2)==cpu(0));/* delay 001049f8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_00104a04;}}
/* 001049fc: jal 0x00104ac0 */ set(31,0x00104a04u);/* delay 00104a00 */ body_00104ac0();
L_00104a04:;
/* 00104a04: move a0,s1 */ set(4,cpu(17));
/* 00104a08: move a1,s2 */ set(5,cpu(18));
/* 00104a0c: move a2,zero */ set(6,cpu(0));
/* 00104a10: sw zero,-0x5828(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa7d8)),(uint32_t)cpu(0));
/* 00104a14: sh s1,-0x581c(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffa7e4)),(uint16_t)cpu(17));
/* 00104a18: jal 0x002aa8d0 */ set(31,0x00104a20u);/* delay 00104a1c */ sh(ea(28,(int32_t)UINT32_C(0xffffa7e6)),(uint16_t)cpu(18));body_002aa8d0();
/* 00104a20: move v1,v0 */ set(3,cpu(2));
/* 00104a24: move a0,s1 */ set(4,cpu(17));
/* 00104a28: move t0,v1 */ set(8,cpu(3));
/* 00104a2c: move a1,s2 */ set(5,cpu(18));
/* 00104a30: move a2,zero */ set(6,cpu(0));
/* 00104a34: move a3,zero */ set(7,cpu(0));
/* 00104a38: move t1,zero */ set(9,cpu(0));
/* 00104a3c: move t2,zero */ set(10,cpu(0));
/* 00104a40: move t3,zero */ set(11,cpu(0));
/* 00104a44: beq v1,zero,0x00104aa0 */ {int taken=(cpu(3)==cpu(0));/* delay 00104a48 */ sw(ea(28,(int32_t)UINT32_C(0xffffa7dc)),(uint32_t)cpu(3));if(taken){goto L_00104aa0;}}
/* 00104a4c: jal 0x002ab388 */ set(31,0x00104a54u);/* delay 00104a50 */ nocturneBattleActionSkillCall(0x002ab388u);
/* 00104a54: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 00104a58: move s0,v0 */ set(16,cpu(2));
/* 00104a5c: beq s0,zero,0x00104aa0 */ {int taken=(cpu(16)==cpu(0));/* delay 00104a60 */ set(4,cpu(16));if(taken){goto L_00104aa0;}}
/* 00104a64: jal 0x002ab190 */ set(31,0x00104a6cu);/* delay 00104a68 */ sw(ea(28,(int32_t)UINT32_C(0xffffa7e0)),(uint32_t)cpu(16));body_002ab190();
/* 00104a6c: jal 0x002abb18 */ set(31,0x00104a74u);/* delay 00104a70 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x002abb18u);
/* 00104a74: lui v0,0x2f */ set(2,sx(UINT32_C(0x002f0000)));
/* 00104a78: mtc1 s1,f1 */ f[1]=(uint32_t)cpu(17);
/* 00104a7c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00104a80: addiu v0,v0,0x5b80 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00005b80)));
/* 00104a84: mtc1 s2,f0 */ f[0]=(uint32_t)cpu(18);
/* 00104a88: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00104a8c: swc1 f20,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),f[20]);
/* 00104a90: swc1 f1,0x18(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000018)),f[1]);
/* 00104a94: jal 0x00104870 */ set(31,0x00104a9cu);/* delay 00104a98 */ sw(ea(2,(int32_t)UINT32_C(0x0000001c)),f[0]);body_00104870();
/* 00104a9c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_00104aa0:;
/* 00104aa0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00104aa4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00104aa8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00104aac: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00104ab0: lwc1 f20,0x20(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00104ab4: jr ra */ {uint64_t target=cpu(31);/* delay 00104ab8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_001049D0(uint64_t a0, uint64_t a1, float f12){
set(4,a0);
set(5,a1);
nocturneEffectHostFpr()[12]=bits(f12);
body_001049d0();
return cpu(2);
}
static void body_00104ac0(void){
nocturneEffectAxisNoteEntry(0x00104ac0u);
uint64_t incoming=cpu(31);
/* 00104ac0: lw v0,-0x5820(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa7e0)));
/* 00104ac4: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00104ac8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00104acc: beq v0,zero,0x00104adc */ {int taken=(cpu(2)==cpu(0));/* delay 00104ad0 */ set(4,cpu(2));if(taken){goto L_00104adc;}}
/* 00104ad4: jal 0x002ab860 */ set(31,0x00104adcu);/* delay 00104ad8 */ body_002ab860();
L_00104adc:;
/* 00104adc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00104ae0: sw zero,-0x5820(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa7e0)),(uint32_t)cpu(0));
/* 00104ae4: sw zero,-0x5824(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa7dc)),(uint32_t)cpu(0));
/* 00104ae8: sw zero,-0x5828(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa7d8)),(uint32_t)cpu(0));
/* 00104aec: jr ra */ {uint64_t target=cpu(31);/* delay 00104af0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00104AC0(void){
body_00104ac0();
return;
}
static void body_00104af8(void){
nocturneEffectAxisNoteEntry(0x00104af8u);
uint64_t incoming=cpu(31);
/* 00104af8: lw v1,-0x5820(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa7e0)));
/* 00104afc: beq v1,zero,0x00104b10 */ {int taken=(cpu(3)==cpu(0));/* delay 00104b00 */ set(2,cpu(0));if(taken){goto L_00104b10;}}
/* 00104b04: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00104b08: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00104b0c: sw v1,-0x5828(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa7d8)),(uint32_t)cpu(3));
L_00104b10:;
/* 00104b10: jr ra */ {uint64_t target=cpu(31);/* delay 00104b14 */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00104AF8(void){
body_00104af8();
return cpu(2);
}
static void body_0016ab70(void){
nocturneEffectAxisNoteEntry(0x0016ab70u);
uint64_t incoming=cpu(31);
/* 0016ab70: andi a1,a1,0xffff */ set(5,cpu(5)&UINT32_C(0x0000ffff));
/* 0016ab74: sltiu a1,a1,0x2 */ set(5,cpu(5)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0016ab78: xori a1,a1,0x1 */ set(5,cpu(5)^UINT32_C(0x00000001));
/* 0016ab7c: sll v1,a1,0x1 */ set(3,sx((uint32_t)cpu(5)<<1));
/* 0016ab80: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0016ab84: sll v0,v1,0x6 */ set(2,sx((uint32_t)cpu(3)<<6));
/* 0016ab88: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0016ab8c: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 0016ab90: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0016ab94: jr ra */ {uint64_t target=cpu(31);/* delay 0016ab98 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_0016AB70(uint64_t a0, uint64_t a1){
set(4,a0);
set(5,a1);
body_0016ab70();
return cpu(2);
}
static void body_0016aba0(void){
nocturneEffectAxisNoteEntry(0x0016aba0u);
uint64_t incoming=cpu(31);
/* 0016aba0: andi a1,a1,0xffff */ set(5,cpu(5)&UINT32_C(0x0000ffff));
/* 0016aba4: sltiu a1,a1,0x2 */ set(5,cpu(5)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0016aba8: xori a1,a1,0x1 */ set(5,cpu(5)^UINT32_C(0x00000001));
/* 0016abac: sll v0,a1,0x1 */ set(2,sx((uint32_t)cpu(5)<<1));
/* 0016abb0: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0016abb4: sll v1,v0,0x6 */ set(3,sx((uint32_t)cpu(2)<<6));
/* 0016abb8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0016abbc: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0016abc0: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0016abc4: jr ra */ {uint64_t target=cpu(31);/* delay 0016abc8 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_0016ABA0(uint64_t a0, uint64_t a1){
set(4,a0);
set(5,a1);
body_0016aba0();
return cpu(2);
}
static void body_0016aec0(void){
nocturneEffectAxisNoteEntry(0x0016aec0u);
uint64_t incoming=cpu(31);
/* 0016aec0: lw v1,0x1c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 0016aec4: jr ra */ {uint64_t target=cpu(31);/* delay 0016aec8 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000048)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_0016AEC0(uint64_t a0){
set(4,a0);
body_0016aec0();
return cpu(2);
}
static void body_0016aef0(void){
nocturneEffectAxisNoteEntry(0x0016aef0u);
uint64_t incoming=cpu(31);
/* 0016aef0: lhu v0,0x14(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000014))));
/* 0016aef4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0016aef8: bnel v0,v1,0x0016af18 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 0016aefc */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));goto L_0016af18;}}
/* 0016af00: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0016af04: sltu v0,a1,v0 */ set(2,cpu(5)<cpu(2));
/* 0016af08: beq v0,zero,0x0016af18 */ {int taken=(cpu(2)==cpu(0));/* delay 0016af0c */ if(taken){goto L_0016af18;}}
/* 0016af10: jr ra */ {uint64_t target=cpu(31);/* delay 0016af14 */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
L_0016af18:;
/* 0016af18: jr ra */ {uint64_t target=cpu(31);/* delay 0016af1c */ checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_0016AEF0(uint64_t a0, uint64_t a1){
set(4,a0);
set(5,a1);
body_0016aef0();
return;
}
static void body_0016b090(void){
nocturneEffectAxisNoteEntry(0x0016b090u);
uint64_t incoming=cpu(31);
/* 0016b090: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0016b094: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016b098: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0016b09c: jal 0x002469a0 */ set(31,0x0016b0a4u);/* delay 0016b0a0 */ set(16,cpu(4));nocturneBattleActionSkillCall(0x002469a0u);
/* 0016b0a4: lw v1,0x60(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000060)));
/* 0016b0a8: andi v1,v1,0x1000 */ set(3,cpu(3)&UINT32_C(0x00001000));
/* 0016b0ac: bnel v1,zero,0x0016b0e4 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0016b0b0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0016b0e4;}}
/* 0016b0b4: lhu v0,0x14(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 0016b0b8: sltiu v0,v0,0x3 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 0016b0bc: beql v0,zero,0x0016b0e4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0016b0c0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0016b0e4;}}
/* 0016b0c4: lhu v0,0x14(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 0016b0c8: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0016b0cc: lui a0,0x32 */ set(4,sx(UINT32_C(0x00320000)));
/* 0016b0d0: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0016b0d4: lhu a0,-0x4740(a0) */ set(4,half(ea(4,(int32_t)UINT32_C(0xffffb8c0))));
/* 0016b0d8: jal 0x001b1740 */ set(31,0x0016b0e0u);/* delay 0016b0dc */ nocturneBattleActionSkillCall(0x001b1740u);
/* 0016b0e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0016b0e4:;
/* 0016b0e4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0016b0e8: jr ra */ {uint64_t target=cpu(31);/* delay 0016b0ec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_0016B090(uint64_t a0){
set(4,a0);
body_0016b090();
return;
}
static void body_0016ba40(void){
nocturneEffectAxisNoteEntry(0x0016ba40u);
uint64_t incoming=cpu(31);
/* 0016ba40: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0016ba44: move v0,a0 */ set(2,cpu(4));
/* 0016ba48: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016ba4c: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0016ba50: addiu a0,a0,0x2f20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00002f20)));
/* 0016ba54: move a1,v0 */ set(5,cpu(2));
/* 0016ba58: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016ba5c: sw v0,-0x23f0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdc10)),(uint32_t)cpu(2));
/* 0016ba60: j 0x002d4748 */ /* delay 0016ba64 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002d4748u);return;
}
void ps2BattleActionSkill_0016BA40(uint64_t a0){
set(4,a0);
body_0016ba40();
return;
}
static void body_00197dd0(void){
nocturneEffectAxisNoteEntry(0x00197dd0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00197dd0: lw v0,-0x4f7c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb084)));
/* 00197dd4: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00197dd8: bne v0,zero,0x00197e48 */ {int taken=(cpu(2)!=cpu(0));/* delay 00197ddc */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00197e48;}}
/* 00197de0: lwc1 f12,-0x785c(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffff87a4)));
/* 00197de4: li a0,0x100 */ set(4,sx(UINT32_C(0x00000100)));
/* 00197de8: li a1,0x100 */ set(5,sx(UINT32_C(0x00000100)));
/* 00197dec: jal 0x001049d0 */ set(31,0x00197df4u);/* delay 00197df0 */ sw(ea(28,(int32_t)UINT32_C(0xffffa7e8)),(uint32_t)cpu(0));body_001049d0();
/* 00197df4: jal 0x00104af8 */ set(31,0x00197dfcu);/* delay 00197df8 */ body_00104af8();
/* 00197dfc: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00197e00: jal 0x001dd0d0 */ set(31,0x00197e08u);/* delay 00197e04 */ set(5,sx(UINT32_C(0x0000010d)));nocturneBattleActionSkillCall(0x001dd0d0u);
/* 00197e08: move a1,zero */ set(5,cpu(0));
/* 00197e0c: clear f12 */ f[12]=0;
/* 00197e10: move a0,v0 */ set(4,cpu(2));
/* 00197e14: lui at,0x4080 */ set(1,sx(UINT32_C(0x40800000)));
/* 00197e18: mtc1 at,f13 */ f[13]=(uint32_t)cpu(1);
/* 00197e1c: move a2,zero */ set(6,cpu(0));
/* 00197e20: jal 0x001dd578 */ set(31,0x00197e28u);/* delay 00197e24 */ sw(ea(28,(int32_t)UINT32_C(0xffffb080)),(uint32_t)cpu(2));body_001dd578();
/* 00197e28: jal 0x00100410 */ set(31,0x00197e30u);/* delay 00197e2c */ body_00100410();
/* 00197e30: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00197e34: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00197e38: addiu a0,a0,0x3d60 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00003d60)));
/* 00197e3c: jal 0x002d4748 */ set(31,0x00197e44u);/* delay 00197e40 */ sw(ea(28,(int32_t)UINT32_C(0xffffb088)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x002d4748u);
/* 00197e44: lw v0,-0x4f7c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb084)));
L_00197e48:;
/* 00197e48: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00197e4c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00197e50: sw v0,-0x4f7c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffb084)),(uint32_t)cpu(2));
/* 00197e54: jr ra */ {uint64_t target=cpu(31);/* delay 00197e58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00197DD0(void){
body_00197dd0();
return;
}
static void body_00198200(void){
nocturneEffectAxisNoteEntry(0x00198200u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00198200: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00198204: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00198208: move s0,a0 */ set(16,cpu(4));
/* 0019820c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00198210: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00198214: jal 0x002a8af8 */ set(31,0x0019821cu);/* delay 00198218 */ set(4,sx(UINT32_C(0x00000010)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 0019821c: move s1,v0 */ set(17,cpu(2));
/* 00198220: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00198224: sw zero,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 00198228: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 0019822c: sw v0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00198230: addiu s0,s0,-0x5130 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffaed0)));
/* 00198234: jal 0x002b31e8 */ set(31,0x0019823cu);/* delay 00198238 */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));nocturneBattleActionSkillCall(0x002b31e8u);
/* 0019823c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00198240: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 00198244: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 00198248: jal 0x002b2ed8 */ set(31,0x00198250u);/* delay 0019824c */ set(4,cpu(2));nocturneBattleActionSkillCall(0x002b2ed8u);
/* 00198250: jal 0x00197dd0 */ set(31,0x00198258u);/* delay 00198254 */ body_00197dd0();
/* 00198258: move a0,s0 */ set(4,cpu(16));
/* 0019825c: move a1,zero */ set(5,cpu(0));
/* 00198260: jal 0x002d4558 */ set(31,0x00198268u);/* delay 00198264 */ set(6,sx(UINT32_C(0x0000002c)));nocturneBattleActionSkillCall(0x002d4558u);
/* 00198268: li a0,0x4000 */ set(4,sx(UINT32_C(0x00004000)));
/* 0019826c: lui v1,0x32 */ set(3,sx(UINT32_C(0x00320000)));
/* 00198270: move v0,s1 */ set(2,cpu(17));
/* 00198274: addiu v1,v1,-0xe0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffff20)));
/* 00198278: sh a0,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(4));
/* 0019827c: sw v1,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 00198280: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00198284: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00198288: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0019828c: jr ra */ {uint64_t target=cpu(31);/* delay 00198290 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00198200(uint64_t a0){
set(4,a0);
body_00198200();
return cpu(2);
}
static void body_00198860(void){
nocturneEffectAxisNoteEntry(0x00198860u);
uint64_t incoming=cpu(31);
/* 00198860: jr ra */ {uint64_t target=cpu(31);/* delay 00198864 */ set(2,sx(UINT32_C(0x00000016)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00198860(void){
body_00198860();
return cpu(2);
}
static void body_00198868(void){
nocturneEffectAxisNoteEntry(0x00198868u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00198868: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0019886c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00198870: move s0,a0 */ set(16,cpu(4));
/* 00198874: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00198878: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0019887c: jal 0x002a8af8 */ set(31,0x00198884u);/* delay 00198880 */ set(4,sx(UINT32_C(0x00000010)));nocturneBattleActionSkillCall(0x002a8af8u);
/* 00198884: move s1,v0 */ set(17,cpu(2));
/* 00198888: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0019888c: sw zero,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 00198890: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 00198894: sw v0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00198898: addiu s0,s0,-0x5130 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffaed0)));
/* 0019889c: jal 0x002b31e8 */ set(31,0x001988a4u);/* delay 001988a0 */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));nocturneBattleActionSkillCall(0x002b31e8u);
/* 001988a4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001988a8: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 001988ac: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 001988b0: jal 0x002b2ed8 */ set(31,0x001988b8u);/* delay 001988b4 */ set(4,cpu(2));nocturneBattleActionSkillCall(0x002b2ed8u);
/* 001988b8: jal 0x00197dd0 */ set(31,0x001988c0u);/* delay 001988bc */ body_00197dd0();
/* 001988c0: move a0,s0 */ set(4,cpu(16));
/* 001988c4: move a1,zero */ set(5,cpu(0));
/* 001988c8: jal 0x002d4558 */ set(31,0x001988d0u);/* delay 001988cc */ set(6,sx(UINT32_C(0x0000002c)));nocturneBattleActionSkillCall(0x002d4558u);
/* 001988d0: li a0,0x4000 */ set(4,sx(UINT32_C(0x00004000)));
/* 001988d4: lui v1,0x32 */ set(3,sx(UINT32_C(0x00320000)));
/* 001988d8: move v0,s1 */ set(2,cpu(17));
/* 001988dc: addiu v1,v1,-0xe0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffff20)));
/* 001988e0: sh a0,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(4));
/* 001988e4: sw v1,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 001988e8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001988ec: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001988f0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001988f4: jr ra */ {uint64_t target=cpu(31);/* delay 001988f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00198868(uint64_t a0){
set(4,a0);
body_00198868();
return cpu(2);
}
static void body_00198ff8(void){
nocturneEffectAxisNoteEntry(0x00198ff8u);
uint64_t incoming=cpu(31);
/* 00198ff8: jr ra */ {uint64_t target=cpu(31);/* delay 00198ffc */ set(2,sx(UINT32_C(0x0000001b)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00198FF8(void){
body_00198ff8();
return cpu(2);
}
static void body_001c8268(void){
nocturneEffectAxisNoteEntry(0x001c8268u);
uint64_t incoming=cpu(31);
/* 001c8268: lw a0,0x2c(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x0000002c)));
/* 001c826c: beq a0,zero,0x001c82b0 */ {int taken=(cpu(4)==cpu(0));/* delay 001c8270 */ set(6,cpu(0));if(taken){goto L_001c82b0;}}
/* 001c8274: lw v1,0x1c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000001c)));
L_001c8278:;
/* 001c8278: beql v1,zero,0x001c82a8 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 001c827c */ lw(4,ea(4,(int32_t)UINT32_C(0x00000028)));goto L_001c82a8;}}
/* 001c8280: lb a1,0x1(a0) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 001c8284: nop  */ 
L_001c8288:;
/* 001c8288: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 001c828c: lw v1,0x28(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000028)));
/* 001c8290: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001c8294: nop  */ 
/* 001c8298: nop  */ 
/* 001c829c: bne v1,zero,0x001c8288 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c82a0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));if(taken){goto L_001c8288;}}
/* 001c82a4: lw a0,0x28(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000028)));
L_001c82a8:;
/* 001c82a8: bnel a0,zero,0x001c8278 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 001c82ac */ lw(3,ea(4,(int32_t)UINT32_C(0x0000001c)));goto L_001c8278;}}
L_001c82b0:;
/* 001c82b0: jr ra */ {uint64_t target=cpu(31);/* delay 001c82b4 */ set(2,cpu(6));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_001C8268(uint64_t a0){
set(4,a0);
body_001c8268();
return cpu(2);
}
static void body_001c9108(void){
nocturneEffectAxisNoteEntry(0x001c9108u);
uint64_t incoming=cpu(31);
/* 001c9108: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c910c: move t3,a2 */ set(11,cpu(6));
/* 001c9110: sw a3,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));
/* 001c9114: move a3,zero */ set(7,cpu(0));
/* 001c9118: move a2,zero */ set(6,cpu(0));
/* 001c911c: move t0,zero */ set(8,cpu(0));
/* 001c9120: move t1,zero */ set(9,cpu(0));
/* 001c9124: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9128: jal 0x001c9188 */ set(31,0x001c9130u);/* delay 001c912c */ set(10,sx(UINT32_C(0x00000080)));nocturneBattleActionSkillCall(0x001c9188u);
/* 001c9130: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9134: jr ra */ {uint64_t target=cpu(31);/* delay 001c9138 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_001C9108(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);
set(5,a1);
set(6,a2);
set(7,a3);
body_001c9108();
return cpu(2);
}
static void body_001ca0d0(void){
nocturneEffectAxisNoteEntry(0x001ca0d0u);
uint64_t incoming=cpu(31);
/* 001ca0d0: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 001ca0d4: sll t2,t2,0x18 */ set(10,sx((uint32_t)cpu(10)<<24));
/* 001ca0d8: sd s5,0x48(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001ca0dc: move s5,t0 */ set(21,cpu(8));
/* 001ca0e0: sll t1,t1,0x18 */ set(9,sx((uint32_t)cpu(9)<<24));
/* 001ca0e4: sw a0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(4));
/* 001ca0e8: sra t2,t2,0x18 */ set(10,sx((uint32_t)((int32_t)cpu(10)>>24)));
/* 001ca0ec: move a0,s5 */ set(4,cpu(21));
/* 001ca0f0: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001ca0f4: move s0,a2 */ set(16,cpu(6));
/* 001ca0f8: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001ca0fc: move s1,zero */ set(17,cpu(0));
/* 001ca100: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001ca104: move s2,t3 */ set(18,cpu(11));
/* 001ca108: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001ca10c: sd s7,0x58(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001ca110: sra s7,t1,0x18 */ set(23,sx((uint32_t)((int32_t)cpu(9)>>24)));
/* 001ca114: sd s8,0x60(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001ca118: move s8,a3 */ set(30,cpu(7));
/* 001ca11c: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001ca120: sd s6,0x50(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001ca124: sd ra,0x68(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001ca128: sw t2,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(10));
/* 001ca12c: jal 0x002d5d0c */ set(31,0x001ca134u);/* delay 001ca130 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(5));nocturneBattleActionSkillCall(0x002d5d0cu);
/* 001ca134: move s4,v0 */ set(20,cpu(2));
/* 001ca138: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001ca13c: bne v0,zero,0x001ca14c */ {int taken=(cpu(2)!=cpu(0));/* delay 001ca140 */ if(taken){goto L_001ca14c;}}
/* 001ca144: jal 0x001c7c00 */ set(31,0x001ca14cu);/* delay 001ca148 */ set(4,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x001c7c00u);
L_001ca14c:;
/* 001ca14c: jal 0x001c7c10 */ set(31,0x001ca154u);/* delay 001ca150 */ set(4,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x001c7c10u);
/* 001ca154: blez s4,0x001ca208 */ {int taken=((int64_t)cpu(20)<=0);/* delay 001ca158 */ set(3,sx((uint32_t)cpu(21)+(uint32_t)cpu(17)));if(taken){goto L_001ca208;}}
/* 001ca15c: sll s6,s0,0x4 */ set(22,sx((uint32_t)cpu(16)<<4));
L_001ca160:;
/* 001ca160: lb v0,0x0(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001ca164: bltz v0,0x001ca180 */ {int taken=((int64_t)cpu(2)<0);/* delay 001ca168 */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_001ca180;}}
/* 001ca16c: sb a0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 001ca170: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
/* 001ca174: b 0x001ca194 */ /* delay 001ca178 */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));goto L_001ca194;
L_001ca180:;
/* 001ca180: lbu v0,0x1(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000001))));
/* 001ca184: li s3,0x2 */ set(19,sx(UINT32_C(0x00000002)));
/* 001ca188: sb a0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 001ca18c: sb zero,0x2(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(0));
/* 001ca190: sb v0,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
L_001ca194:;
/* 001ca194: move a0,sp */ set(4,cpu(29));
/* 001ca198: move a2,zero */ set(6,cpu(0));
/* 001ca19c: move a3,zero */ set(7,cpu(0));
/* 001ca1a0: move t0,zero */ set(8,cpu(0));
/* 001ca1a4: jal 0x001c7828 */ set(31,0x001ca1acu);/* delay 001ca1a8 */ set(5,cpu(23));nocturneBattleActionSkillCall(0x001c7828u);
/* 001ca1ac: move a1,s6 */ set(5,cpu(22));
/* 001ca1b0: move s0,v0 */ set(16,cpu(2));
/* 001ca1b4: jal 0x001c7b40 */ set(31,0x001ca1bcu);/* delay 001ca1b8 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x001c7b40u);
/* 001ca1bc: move a0,s0 */ set(4,cpu(16));
/* 001ca1c0: jal 0x001c7ba8 */ set(31,0x001ca1c8u);/* delay 001ca1c4 */ set(5,cpu(30));nocturneBattleActionSkillCall(0x001c7ba8u);
/* 001ca1c8: move a0,s0 */ set(4,cpu(16));
/* 001ca1cc: jal 0x001c7a88 */ set(31,0x001ca1d4u);/* delay 001ca1d0 */ set(5,sx(UINT32_C(0x00000003)));nocturneBattleActionSkillCall(0x001c7a88u);
/* 001ca1d4: move a0,s2 */ set(4,cpu(18));
/* 001ca1d8: jal 0x001c8108 */ set(31,0x001ca1e0u);/* delay 001ca1dc */ set(5,cpu(16));nocturneBattleActionSkillCall(0x001c8108u);
/* 001ca1e0: bne s1,zero,0x001ca1f0 */ {int taken=(cpu(17)!=cpu(0));/* delay 001ca1e4 */ set(18,cpu(2));if(taken){goto L_001ca1f0;}}
/* 001ca1e8: lw v0,0x10(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001ca1ec: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_001ca1f0:;
/* 001ca1f0: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 001ca1f4: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 001ca1f8: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001ca1fc: slt v0,s1,s4 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(20));
/* 001ca200: bne v0,zero,0x001ca160 */ {int taken=(cpu(2)!=cpu(0));/* delay 001ca204 */ set(3,sx((uint32_t)cpu(21)+(uint32_t)cpu(17)));if(taken){goto L_001ca160;}}
L_001ca208:;
/* 001ca208: jal 0x001c7c00 */ set(31,0x001ca210u);/* delay 001ca20c */ set(4,sx(UINT32_C(0x00000002)));nocturneBattleActionSkillCall(0x001c7c00u);
/* 001ca210: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001ca214: bnel v0,zero,0x001ca228 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001ca218 */ set(2,cpu(18));goto L_001ca228;}}
/* 001ca21c: jal 0x001c7c10 */ set(31,0x001ca224u);/* delay 001ca220 */ set(4,sx(UINT32_C(0x00000001)));nocturneBattleActionSkillCall(0x001c7c10u);
/* 001ca224: move v0,s2 */ set(2,cpu(18));
L_001ca228:;
/* 001ca228: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001ca22c: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001ca230: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001ca234: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001ca238: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001ca23c: ld s5,0x48(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001ca240: ld s6,0x50(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001ca244: ld s7,0x58(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001ca248: ld s8,0x60(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001ca24c: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001ca250: jr ra */ {uint64_t target=cpu(31);/* delay 001ca254 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_001CA0D0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2, uint64_t t3){
set(4,a0);
set(5,a1);
set(6,a2);
set(7,a3);
set(8,t0);
set(9,t1);
set(10,t2);
set(11,t3);
body_001ca0d0();
return cpu(2);
}
static void body_001ca258(void){
nocturneEffectAxisNoteEntry(0x001ca258u);
uint64_t incoming=cpu(31);
/* 001ca258: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001ca25c: move t3,t1 */ set(11,cpu(9));
/* 001ca260: move t2,zero */ set(10,cpu(0));
/* 001ca264: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ca268: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001ca26c: jal 0x001ca0d0 */ set(31,0x001ca274u);/* delay 001ca270 */ set(9,sx(UINT32_C(0x00000001)));body_001ca0d0();
/* 001ca274: move s0,v0 */ set(16,cpu(2));
/* 001ca278: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 001ca27c: jal 0x001c7a88 */ set(31,0x001ca284u);/* delay 001ca280 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x001c7a88u);
/* 001ca284: move v0,s0 */ set(2,cpu(16));
/* 001ca288: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001ca28c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ca290: jr ra */ {uint64_t target=cpu(31);/* delay 001ca294 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_001CA258(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1){
set(4,a0);
set(5,a1);
set(6,a2);
set(7,a3);
set(8,t0);
set(9,t1);
body_001ca258();
return cpu(2);
}
static void body_001cea58(void){
nocturneEffectAxisNoteEntry(0x001cea58u);
uint64_t incoming=cpu(31);
/* 001cea58: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001cea5c: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001cea60: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001cea64: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cea68: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001cea6c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cea70: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 001cea74: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001cea78: lw s0,-0x4174(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0xffffbe8c)));
/* 001cea7c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cea80: move s2,a2 */ set(18,cpu(6));
/* 001cea84: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cea88: jal 0x001cf178 */ set(31,0x001cea90u);/* delay 001cea8c */ set(4,cpu(16));nocturneBattleActionSkillCall(0x001cf178u);
/* 001cea90: addiu a0,s0,0xc4 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x000000c4)));
/* 001cea94: lw s1,0x4(v0) */ lw(17,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 001cea98: lh v1,0x18(s1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000018))));
/* 001cea9c: beq v1,zero,0x001ceb00 */ {int taken=(cpu(3)==cpu(0));/* delay 001ceaa0 */ set(2,cpu(0));if(taken){goto L_001ceb00;}}
/* 001ceaa4: jal 0x001cf440 */ set(31,0x001ceaacu);/* delay 001ceaa8 */ nocturneBattleActionSkillCall(0x001cf440u);
/* 001ceaac: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001ceab0: beq v0,zero,0x001ceac0 */ {int taken=(cpu(2)==cpu(0));/* delay 001ceab4 */ set(4,cpu(2));if(taken){goto L_001ceac0;}}
/* 001ceab8: jal 0x001c81b8 */ set(31,0x001ceac0u);/* delay 001ceabc */ nocturneBattleActionSkillCall(0x001c81b8u);
L_001ceac0:;
/* 001ceac0: move a0,s1 */ set(4,cpu(17));
/* 001ceac4: jal 0x001cf1a8 */ set(31,0x001ceaccu);/* delay 001ceac8 */ set(5,cpu(18));nocturneBattleActionSkillCall(0x001cf1a8u);
/* 001ceacc: move a0,zero */ set(4,cpu(0));
/* 001cead0: move a2,v0 */ set(6,cpu(2));
/* 001cead4: beq a2,zero,0x001ceb00 */ {int taken=(cpu(6)==cpu(0));/* delay 001cead8 */ set(5,cpu(0));if(taken){goto L_001ceb00;}}
/* 001ceadc: jal 0x001c9108 */ set(31,0x001ceae4u);/* delay 001ceae0 */ set(7,cpu(0));body_001c9108();
/* 001ceae4: move s0,v0 */ set(16,cpu(2));
/* 001ceae8: jal 0x001cf960 */ set(31,0x001ceaf0u);/* delay 001ceaec */ set(4,cpu(16));body_001cf960();
/* 001ceaf0: move a0,s0 */ set(4,cpu(16));
/* 001ceaf4: jal 0x001c6ff8 */ set(31,0x001ceafcu);/* delay 001ceaf8 */ set(17,cpu(2));nocturneBattleActionSkillCall(0x001c6ff8u);
/* 001ceafc: move v0,s1 */ set(2,cpu(17));
L_001ceb00:;
/* 001ceb00: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ceb04: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001ceb08: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001ceb0c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001ceb10: jr ra */ {uint64_t target=cpu(31);/* delay 001ceb14 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_001CEA58(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);
set(5,a1);
set(6,a2);
body_001cea58();
return cpu(2);
}
static void body_001cf960(void){
nocturneEffectAxisNoteEntry(0x001cf960u);
uint64_t incoming=cpu(31);
/* 001cf960: beq a0,zero,0x001cf9a8 */ {int taken=(cpu(4)==cpu(0));/* delay 001cf964 */ set(6,cpu(0));if(taken){goto L_001cf9a8;}}
L_001cf968:;
/* 001cf968: lw a1,0x8(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 001cf96c: move v1,zero */ set(3,cpu(0));
/* 001cf970: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 001cf974: nop  */ 
L_001cf978:;
/* 001cf978: lw a0,0x24(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000024)));
/* 001cf97c: beq a0,zero,0x001cf99c */ {int taken=(cpu(4)==cpu(0));/* delay 001cf980 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));if(taken){goto L_001cf99c;}}
/* 001cf984: lw v0,0x8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 001cf988: nop  */ 
/* 001cf98c: nop  */ 
/* 001cf990: nop  */ 
/* 001cf994: beql a1,v0,0x001cf978 */ {int taken=(cpu(5)==cpu(2));if(taken){/* delay 001cf998 */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));goto L_001cf978;}}
L_001cf99c:;
/* 001cf99c: slt v0,a2,v1 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(3));
/* 001cf9a0: bne a0,zero,0x001cf968 */ {int taken=(cpu(4)!=cpu(0));/* delay 001cf9a4 */ if(cpu(2)!=0){set(6,cpu(3));}if(taken){goto L_001cf968;}}
L_001cf9a8:;
/* 001cf9a8: jr ra */ {uint64_t target=cpu(31);/* delay 001cf9ac */ set(2,sx((uint32_t)cpu(6)<<4));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_001CF960(uint64_t a0){
set(4,a0);
body_001cf960();
return cpu(2);
}
static void body_001dd578(void){
nocturneEffectAxisNoteEntry(0x001dd578u);
uint64_t incoming=cpu(31);
/* 001dd578: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dd57c: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 001dd580: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd584: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd588: j 0x001dd440 */ /* delay 001dd58c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x001dd440u);return;
}
void ps2BattleActionSkill_001DD578(uint64_t a0, uint64_t a1, uint64_t a2, float f12, float f13){
set(4,a0);
set(5,a1);
set(6,a2);
nocturneEffectHostFpr()[12]=bits(f12);
nocturneEffectHostFpr()[13]=bits(f13);
body_001dd578();
return;
}
static void body_00280518(void){
nocturneEffectAxisNoteEntry(0x00280518u);
uint64_t incoming=cpu(31);
/* 00280518: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0028051c: sw zero,-0x2f4c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0b4)),(uint32_t)cpu(0));
/* 00280520: jr ra */ {uint64_t target=cpu(31);/* delay 00280524 */ sw(ea(28,(int32_t)UINT32_C(0xffffd0b0)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00280518(void){
body_00280518();
return;
}
static void body_00288e18(void){
nocturneEffectAxisNoteEntry(0x00288e18u);
uint64_t incoming=cpu(31);
/* 00288e18: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00288e1c: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 00288e20: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00288e24: move s1,a0 */ set(17,cpu(4));
/* 00288e28: addiu a0,v0,0x14f0 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x000014f0)));
/* 00288e2c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00288e30: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00288e34: move s0,a1 */ set(16,cpu(5));
/* 00288e38: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00288e3c: move s3,t0 */ set(19,cpu(8));
/* 00288e40: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00288e44: move s4,a2 */ set(20,cpu(6));
/* 00288e48: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00288e4c: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00288e50: jal 0x00101898 */ set(31,0x00288e58u);/* delay 00288e54 */ set(21,cpu(7));nocturneBattleActionSkillCall(0x00101898u);
/* 00288e58: jal 0x00101ab0 */ set(31,0x00288e60u);/* delay 00288e5c */ set(4,cpu(2));nocturneBattleActionSkillCall(0x00101ab0u);
/* 00288e60: jal 0x00289450 */ set(31,0x00288e68u);/* delay 00288e64 */ set(18,cpu(2));body_00289450();
/* 00288e68: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00288e6c: sw s1,0x4(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 00288e70: bne s4,a0,0x00288e88 */ {int taken=(cpu(20)!=cpu(4));/* delay 00288e74 */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));if(taken){goto L_00288e88;}}
/* 00288e78: lw v0,0x2c(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000002c)));
/* 00288e7c: lw v1,0x30(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000030)));
/* 00288e80: sw v0,0x24(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
/* 00288e84: sw v1,0x28(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
L_00288e88:;
/* 00288e88: beq s4,a0,0x00288eb0 */ {int taken=(cpu(20)==cpu(4));/* delay 00288e8c */ sw(ea(18,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(19));if(taken){goto L_00288eb0;}}
/* 00288e90: slti v0,s4,0x2 */ set(2,(int64_t)cpu(20)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 00288e94: bne v0,zero,0x00288f50 */ {int taken=(cpu(2)!=cpu(0));/* delay 00288e98 */ lw(8,ea(18,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_00288f50;}}
/* 00288e9c: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00288ea0: beq s4,v0,0x00288ed0 */ {int taken=(cpu(20)==cpu(2));/* delay 00288ea4 */ if(taken){goto L_00288ed0;}}
/* 00288ea8: b 0x00288f54 */ /* delay 00288eac */ set(6,sx(UINT32_C(0x00ff0000)));goto L_00288f54;
L_00288eb0:;
/* 00288eb0: lw a0,0x24(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000024)));
/* 00288eb4: move a2,zero */ set(6,cpu(0));
/* 00288eb8: jal 0x001cea58 */ set(31,0x00288ec0u);/* delay 00288ebc */ lw(5,ea(18,(int32_t)UINT32_C(0x00000028)));body_001cea58();
/* 00288ec0: sra v0,v0,0x4 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>4)));
/* 00288ec4: b 0x00288fd8 */ /* delay 00288ec8 */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));goto L_00288fd8;
L_00288ed0:;
/* 00288ed0: lui a2,0xff */ set(6,sx(UINT32_C(0x00ff0000)));
/* 00288ed4: move t1,zero */ set(9,cpu(0));
/* 00288ed8: move a3,s3 */ set(7,cpu(19));
/* 00288edc: move a1,zero */ set(5,cpu(0));
/* 00288ee0: ori a2,a2,0x51 */ set(6,cpu(6)|UINT32_C(0x00000051));
/* 00288ee4: jal 0x001ca258 */ set(31,0x00288eecu);/* delay 00288ee8 */ set(4,cpu(0));body_001ca258();
/* 00288eec: move s0,v0 */ set(16,cpu(2));
/* 00288ef0: jal 0x001c8268 */ set(31,0x00288ef8u);/* delay 00288ef4 */ set(4,cpu(16));body_001c8268();
/* 00288ef8: move a0,s0 */ set(4,cpu(16));
/* 00288efc: jal 0x001c6ff8 */ set(31,0x00288f04u);/* delay 00288f00 */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x001c6ff8u);
/* 00288f04: move a0,zero */ set(4,cpu(0));
/* 00288f08: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00288f0c: move a2,zero */ set(6,cpu(0));
/* 00288f10: jal 0x001c9d60 */ set(31,0x00288f18u);/* delay 00288f14 */ set(7,cpu(0));nocturneBattleActionSkillCall(0x001c9d60u);
/* 00288f18: move s0,v0 */ set(16,cpu(2));
/* 00288f1c: lw v0,0x18(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 00288f20: move a0,s0 */ set(4,cpu(16));
/* 00288f24: addiu v0,v0,0xa */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000000a)));
/* 00288f28: jal 0x001c8268 */ set(31,0x00288f30u);/* delay 00288f2c */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));body_001c8268();
/* 00288f30: lw v1,0x18(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 00288f34: move a0,s0 */ set(4,cpu(16));
/* 00288f38: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00288f3c: addiu v1,v1,0xa */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x0000000a)));
/* 00288f40: jal 0x001c6ff8 */ set(31,0x00288f48u);/* delay 00288f44 */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));nocturneBattleActionSkillCall(0x001c6ff8u);
/* 00288f48: b 0x00288fdc */ /* delay 00288f4c */ sw(ea(18,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(21));goto L_00288fdc;
L_00288f50:;
/* 00288f50: lui a2,0xff */ set(6,sx(UINT32_C(0x00ff0000)));
L_00288f54:;
/* 00288f54: lw a3,0x20(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 00288f58: move a1,zero */ set(5,cpu(0));
/* 00288f5c: ori a2,a2,0x51 */ set(6,cpu(6)|UINT32_C(0x00000051));
/* 00288f60: move t1,zero */ set(9,cpu(0));
/* 00288f64: jal 0x001ca258 */ set(31,0x00288f6cu);/* delay 00288f68 */ set(4,cpu(0));body_001ca258();
/* 00288f6c: move s0,v0 */ set(16,cpu(2));
/* 00288f70: jal 0x001c8268 */ set(31,0x00288f78u);/* delay 00288f74 */ set(4,cpu(16));body_001c8268();
/* 00288f78: move a0,s0 */ set(4,cpu(16));
/* 00288f7c: jal 0x001c6ff8 */ set(31,0x00288f84u);/* delay 00288f80 */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));nocturneBattleActionSkillCall(0x001c6ff8u);
/* 00288f84: lw t0,0x8(s2) */ lw(8,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 00288f88: beq t0,zero,0x00288fd8 */ {int taken=(cpu(8)==cpu(0));/* delay 00288f8c */ set(6,sx(UINT32_C(0x00ff0000)));if(taken){goto L_00288fd8;}}
/* 00288f90: lw a3,0x20(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 00288f94: move a0,zero */ set(4,cpu(0));
/* 00288f98: move a1,zero */ set(5,cpu(0));
/* 00288f9c: ori a2,a2,0x51 */ set(6,cpu(6)|UINT32_C(0x00000051));
/* 00288fa0: jal 0x001ca258 */ set(31,0x00288fa8u);/* delay 00288fa4 */ set(9,cpu(0));body_001ca258();
/* 00288fa8: move s0,v0 */ set(16,cpu(2));
/* 00288fac: lw v0,0x18(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 00288fb0: move a0,s0 */ set(4,cpu(16));
/* 00288fb4: addiu v0,v0,0xa */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000000a)));
/* 00288fb8: jal 0x001c8268 */ set(31,0x00288fc0u);/* delay 00288fbc */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));body_001c8268();
/* 00288fc0: lw v1,0x18(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 00288fc4: move a0,s0 */ set(4,cpu(16));
/* 00288fc8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00288fcc: addiu v1,v1,0xa */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x0000000a)));
/* 00288fd0: jal 0x001c6ff8 */ set(31,0x00288fd8u);/* delay 00288fd4 */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));nocturneBattleActionSkillCall(0x001c6ff8u);
L_00288fd8:;
/* 00288fd8: sw s5,0x10(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(21));
L_00288fdc:;
/* 00288fdc: sw s4,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));
/* 00288fe0: sw zero,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 00288fe4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00288fe8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00288fec: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00288ff0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00288ff4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00288ff8: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00288ffc: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00289000: jr ra */ {uint64_t target=cpu(31);/* delay 00289004 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00288E18(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0){
set(4,a0);
set(5,a1);
set(6,a2);
set(7,a3);
set(8,t0);
body_00288e18();
return;
}
static void body_00289008(void){
nocturneEffectAxisNoteEntry(0x00289008u);
uint64_t incoming=cpu(31);
/* 00289008: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0028900c: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00289010: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00289014: lui t0,0x89fe */ set(8,sx(UINT32_C(0x89fe0000)));
/* 00289018: lui at,0x3f */ set(1,sx(UINT32_C(0x003f0000)));
/* 0028901c: addu at,at,a0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00289020: lw a0,-0x7c10(at) */ lw(4,ea(1,(int32_t)UINT32_C(0xffff83f0)));
/* 00289024: move a1,zero */ set(5,cpu(0));
/* 00289028: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028902c: move a2,zero */ set(6,cpu(0));
/* 00289030: li a3,0x1e */ set(7,sx(UINT32_C(0x0000001e)));
/* 00289034: ori t0,t0,0xff80 */ set(8,cpu(8)|UINT32_C(0x0000ff80));
/* 00289038: j 0x00288e18 */ /* delay 0028903c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00288e18();return;
}
void ps2BattleActionSkill_00289008(uint64_t a0){
set(4,a0);
body_00289008();
return;
}
static void body_00289450(void){
nocturneEffectAxisNoteEntry(0x00289450u);
uint64_t incoming=cpu(31);
/* 00289450: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 00289454: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00289458: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028945c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00289460: jal 0x00101898 */ set(31,0x00289468u);/* delay 00289464 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000014f0)));nocturneBattleActionSkillCall(0x00101898u);
/* 00289468: jal 0x00101ab0 */ set(31,0x00289470u);/* delay 0028946c */ set(4,cpu(2));nocturneBattleActionSkillCall(0x00101ab0u);
/* 00289470: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00289474: move s0,v0 */ set(16,cpu(2));
/* 00289478: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0028947c: bne v0,zero,0x002894a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00289480 */ set(4,sx(UINT32_C(0x00000001)));if(taken){goto L_002894a8;}}
/* 00289484: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00289488: bnel v1,a0,0x002894d0 */ {int taken=(cpu(3)!=cpu(4));if(taken){/* delay 0028948c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002894d0;}}
/* 00289490: lw v0,0x24(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000024)));
/* 00289494: bltzl v0,0x002894d0 */ {int taken=((int64_t)cpu(2)<0);if(taken){/* delay 00289498 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002894d0;}}
/* 0028949c: b 0x002894b0 */ /* delay 002894a0 */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));goto L_002894b0;
L_002894a8:;
/* 002894a8: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002894ac: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
L_002894b0:;
/* 002894b0: bne v1,a1,0x002894cc */ {int taken=(cpu(3)!=cpu(5));/* delay 002894b4 */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));if(taken){goto L_002894cc;}}
/* 002894b8: lw a0,0x24(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000024)));
/* 002894bc: jal 0x001cdd78 */ set(31,0x002894c4u);/* delay 002894c0 */ set(5,cpu(0));nocturneBattleActionSkillCall(0x001cdd78u);
/* 002894c4: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002894c8: sw v0,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
L_002894cc:;
/* 002894cc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002894d0:;
/* 002894d0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002894d4: jr ra */ {uint64_t target=cpu(31);/* delay 002894d8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_00289450(void){
body_00289450();
return;
}
static void body_0028fa80(void){
nocturneEffectAxisNoteEntry(0x0028fa80u);
uint64_t incoming=cpu(31);
/* 0028fa80: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0028fa84: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028fa88: jal 0x002469a0 */ set(31,0x0028fa90u);/* delay 0028fa8c */ nocturneBattleActionSkillCall(0x002469a0u);
/* 0028fa90: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0028fa94: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 0028fa98: addiu a0,v1,0x3c0 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x000003c0)));
/* 0028fa9c: lw v1,0x78(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000078)));
L_0028faa0:;
/* 0028faa0: move v0,a0 */ set(2,cpu(4));
/* 0028faa4: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 0028faa8: bne v1,zero,0x0028fac8 */ {int taken=(cpu(3)!=cpu(0));/* delay 0028faac */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000000f0)));if(taken){goto L_0028fac8;}}
/* 0028fab0: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0028fab4: slti v0,a1,0xe */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 0028fab8: nop  */ 
/* 0028fabc: bnel v0,zero,0x0028faa0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0028fac0 */ lw(3,ea(4,(int32_t)UINT32_C(0x00000078)));goto L_0028faa0;}}
/* 0028fac4: move v0,zero */ set(2,cpu(0));
L_0028fac8:;
/* 0028fac8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028facc: jr ra */ {uint64_t target=cpu(31);/* delay 0028fad0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_0028FA80(void){
body_0028fa80();
return cpu(2);
}
static void body_002901d0(void){
nocturneEffectAxisNoteEntry(0x002901d0u);
uint64_t incoming=cpu(31);
/* 002901d0: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002901d4: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002901d8: move s4,a1 */ set(20,cpu(5));
/* 002901dc: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002901e0: move s2,a2 */ set(18,cpu(6));
/* 002901e4: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002901e8: move s3,zero */ set(19,cpu(0));
/* 002901ec: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002901f0: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002901f4: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002901f8: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002901fc: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00290200: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00290204: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00290208: blez s4,0x0029045c */ {int taken=((int64_t)cpu(20)<=0);/* delay 0029020c */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));if(taken){goto L_0029045c;}}
/* 00290210: lui v0,0x1 */ set(2,sx(UINT32_C(0x00010000)));
/* 00290214: lui v1,0x2 */ set(3,sx(UINT32_C(0x00020000)));
/* 00290218: lui a0,0x100 */ set(4,sx(UINT32_C(0x01000000)));
/* 0029021c: and s8,s2,v0 */ set(30,cpu(18)&cpu(2));
/* 00290220: and s7,s2,v1 */ set(23,cpu(18)&cpu(3));
/* 00290224: and s6,s2,a0 */ set(22,cpu(18)&cpu(4));
/* 00290228: andi s5,s2,0x1 */ set(21,cpu(18)&UINT32_C(0x00000001));
/* 0029022c: lw v1,0x0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00290230:;
/* 00290230: sll v0,s3,0x2 */ set(2,sx((uint32_t)cpu(19)<<2));
/* 00290234: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00290238: beq s5,zero,0x00290254 */ {int taken=(cpu(21)==cpu(0));/* delay 0029023c */ lw(17,ea(2,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00290254;}}
/* 00290240: lh s0,0x10(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000010))));
/* 00290244: jal 0x00267ec8 */ set(31,0x0029024cu);/* delay 00290248 */ set(4,sx(UINT32_C(0x00000004)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 0029024c: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290250 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
L_00290254:;
/* 00290254: andi v0,s2,0x2 */ set(2,cpu(18)&UINT32_C(0x00000002));
/* 00290258: beql v0,zero,0x00290278 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0029025c */ set(2,cpu(18)&UINT32_C(0x00000004));goto L_00290278;}}
/* 00290260: lh s0,0x10(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000010))));
/* 00290264: jal 0x00267f18 */ set(31,0x0029026cu);/* delay 00290268 */ set(4,sx(UINT32_C(0x00000004)));nocturneBattleActionSkillCall(0x00267f18u);
/* 0029026c: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290270 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 00290274: andi v0,s2,0x4 */ set(2,cpu(18)&UINT32_C(0x00000004));
L_00290278:;
/* 00290278: beql v0,zero,0x00290298 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0029027c */ set(2,cpu(18)&UINT32_C(0x00000008));goto L_00290298;}}
/* 00290280: lh s0,0x12(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000012))));
/* 00290284: jal 0x00267ec8 */ set(31,0x0029028cu);/* delay 00290288 */ set(4,sx(UINT32_C(0x00000005)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 0029028c: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290290 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 00290294: andi v0,s2,0x8 */ set(2,cpu(18)&UINT32_C(0x00000008));
L_00290298:;
/* 00290298: beql v0,zero,0x002902b8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0029029c */ set(2,cpu(18)&UINT32_C(0x00000010));goto L_002902b8;}}
/* 002902a0: lh s0,0x12(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000012))));
/* 002902a4: jal 0x00267f18 */ set(31,0x002902acu);/* delay 002902a8 */ set(4,sx(UINT32_C(0x00000005)));nocturneBattleActionSkillCall(0x00267f18u);
/* 002902ac: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 002902b0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 002902b4: andi v0,s2,0x10 */ set(2,cpu(18)&UINT32_C(0x00000010));
L_002902b8:;
/* 002902b8: beql v0,zero,0x002902d8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002902bc */ set(2,cpu(18)&UINT32_C(0x00000020));goto L_002902d8;}}
/* 002902c0: lh s0,0x14(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 002902c4: jal 0x00267ec8 */ set(31,0x002902ccu);/* delay 002902c8 */ set(4,sx(UINT32_C(0x00000006)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 002902cc: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 002902d0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 002902d4: andi v0,s2,0x20 */ set(2,cpu(18)&UINT32_C(0x00000020));
L_002902d8:;
/* 002902d8: beql v0,zero,0x002902f8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002902dc */ set(2,cpu(18)&UINT32_C(0x00000040));goto L_002902f8;}}
/* 002902e0: lh s0,0x14(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 002902e4: jal 0x00267f18 */ set(31,0x002902ecu);/* delay 002902e8 */ set(4,sx(UINT32_C(0x00000006)));nocturneBattleActionSkillCall(0x00267f18u);
/* 002902ec: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 002902f0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 002902f4: andi v0,s2,0x40 */ set(2,cpu(18)&UINT32_C(0x00000040));
L_002902f8:;
/* 002902f8: beql v0,zero,0x00290318 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002902fc */ set(2,cpu(18)&UINT32_C(0x00000080));goto L_00290318;}}
/* 00290300: lh s0,0x16(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000016))));
/* 00290304: jal 0x00267ec8 */ set(31,0x0029030cu);/* delay 00290308 */ set(4,sx(UINT32_C(0x00000007)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 0029030c: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290310 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 00290314: andi v0,s2,0x80 */ set(2,cpu(18)&UINT32_C(0x00000080));
L_00290318:;
/* 00290318: beql v0,zero,0x00290338 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0029031c */ set(2,cpu(18)&UINT32_C(0x00000100));goto L_00290338;}}
/* 00290320: lh s0,0x16(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000016))));
/* 00290324: jal 0x00267f18 */ set(31,0x0029032cu);/* delay 00290328 */ set(4,sx(UINT32_C(0x00000007)));nocturneBattleActionSkillCall(0x00267f18u);
/* 0029032c: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290330 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 00290334: andi v0,s2,0x100 */ set(2,cpu(18)&UINT32_C(0x00000100));
L_00290338:;
/* 00290338: beql v0,zero,0x00290358 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0029033c */ set(2,cpu(18)&UINT32_C(0x00000200));goto L_00290358;}}
/* 00290340: lh s0,0x18(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000018))));
/* 00290344: jal 0x00267ec8 */ set(31,0x0029034cu);/* delay 00290348 */ set(4,sx(UINT32_C(0x00000008)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 0029034c: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290350 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 00290354: andi v0,s2,0x200 */ set(2,cpu(18)&UINT32_C(0x00000200));
L_00290358:;
/* 00290358: beql v0,zero,0x00290378 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0029035c */ set(2,cpu(18)&UINT32_C(0x00001000));goto L_00290378;}}
/* 00290360: lh s0,0x18(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000018))));
/* 00290364: jal 0x00267f18 */ set(31,0x0029036cu);/* delay 00290368 */ set(4,sx(UINT32_C(0x00000008)));nocturneBattleActionSkillCall(0x00267f18u);
/* 0029036c: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290370 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 00290374: andi v0,s2,0x1000 */ set(2,cpu(18)&UINT32_C(0x00001000));
L_00290378:;
/* 00290378: beql v0,zero,0x00290398 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0029037c */ set(2,cpu(18)&UINT32_C(0x00002000));goto L_00290398;}}
/* 00290380: lh s0,0x1a(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000001a))));
/* 00290384: jal 0x00267ec8 */ set(31,0x0029038cu);/* delay 00290388 */ set(4,sx(UINT32_C(0x00000009)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 0029038c: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290390 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 00290394: andi v0,s2,0x2000 */ set(2,cpu(18)&UINT32_C(0x00002000));
L_00290398:;
/* 00290398: beql v0,zero,0x002903b8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0029039c */ set(2,cpu(18)&UINT32_C(0x00004000));goto L_002903b8;}}
/* 002903a0: lh s0,0x1c(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000001c))));
/* 002903a4: jal 0x00267ec8 */ set(31,0x002903acu);/* delay 002903a8 */ set(4,sx(UINT32_C(0x0000000a)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 002903ac: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 002903b0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 002903b4: andi v0,s2,0x4000 */ set(2,cpu(18)&UINT32_C(0x00004000));
L_002903b8:;
/* 002903b8: beql v0,zero,0x002903d8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002903bc */ set(2,cpu(18)&UINT32_C(0x00008000));goto L_002903d8;}}
/* 002903c0: lh s0,0x1e(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000001e))));
/* 002903c4: jal 0x00267ec8 */ set(31,0x002903ccu);/* delay 002903c8 */ set(4,sx(UINT32_C(0x0000000b)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 002903cc: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 002903d0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
/* 002903d4: andi v0,s2,0x8000 */ set(2,cpu(18)&UINT32_C(0x00008000));
L_002903d8:;
/* 002903d8: beq v0,zero,0x002903f4 */ {int taken=(cpu(2)==cpu(0));/* delay 002903dc */ if(taken){goto L_002903f4;}}
/* 002903e0: lh s0,0x20(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000020))));
/* 002903e4: jal 0x00267ec8 */ set(31,0x002903ecu);/* delay 002903e8 */ set(4,sx(UINT32_C(0x0000000c)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 002903ec: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 002903f0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
L_002903f4:;
/* 002903f4: beq s8,zero,0x00290410 */ {int taken=(cpu(30)==cpu(0));/* delay 002903f8 */ if(taken){goto L_00290410;}}
/* 002903fc: lh s0,0x22(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000022))));
/* 00290400: jal 0x00267ec8 */ set(31,0x00290408u);/* delay 00290404 */ set(4,sx(UINT32_C(0x0000000d)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 00290408: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 0029040c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
L_00290410:;
/* 00290410: beq s7,zero,0x0029042c */ {int taken=(cpu(23)==cpu(0));/* delay 00290414 */ if(taken){goto L_0029042c;}}
/* 00290418: lh s0,0x24(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000024))));
/* 0029041c: jal 0x00267ec8 */ set(31,0x00290424u);/* delay 00290420 */ set(4,sx(UINT32_C(0x0000000e)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 00290424: bne s0,v0,0x00290460 */ {int taken=(cpu(16)!=cpu(2));/* delay 00290428 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00290460;}}
L_0029042c:;
/* 0029042c: beql s6,zero,0x00290450 */ {int taken=(cpu(22)==cpu(0));if(taken){/* delay 00290430 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));goto L_00290450;}}
/* 00290434: lh s0,0x26(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000026))));
/* 00290438: jal 0x00267ec8 */ set(31,0x00290440u);/* delay 0029043c */ set(4,sx(UINT32_C(0x0000000f)));nocturneBattleActionSkillCall(0x00267ec8u);
/* 00290440: beq s0,v0,0x00290450 */ {int taken=(cpu(16)==cpu(2));/* delay 00290444 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));if(taken){goto L_00290450;}}
/* 00290448: b 0x00290460 */ /* delay 0029044c */ set(2,sx(UINT32_C(0x00000001)));goto L_00290460;
L_00290450:;
/* 00290450: slt v0,s3,s4 */ set(2,(int64_t)cpu(19)<(int64_t)cpu(20));
/* 00290454: bne v0,zero,0x00290230 */ {int taken=(cpu(2)!=cpu(0));/* delay 00290458 */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00290230;}}
L_0029045c:;
/* 0029045c: move v0,zero */ set(2,cpu(0));
L_00290460:;
/* 00290460: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00290464: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00290468: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0029046c: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00290470: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00290474: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00290478: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0029047c: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00290480: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00290484: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00290488: jr ra */ {uint64_t target=cpu(31);/* delay 0029048c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_002901D0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);
set(5,a1);
set(6,a2);
body_002901d0();
return cpu(2);
}
static void body_00290780(void){
nocturneEffectAxisNoteEntry(0x00290780u);
uint64_t incoming=cpu(31);
/* 00290780: addiu sp,sp,-0x150 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffeb0)));
/* 00290784: sd s0,0x100(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000100)));
/* 00290788: move s0,zero */ set(16,cpu(0));
/* 0029078c: sd s1,0x108(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000108)));
/* 00290790: move s1,a0 */ set(17,cpu(4));
/* 00290794: sd s2,0x110(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000110)));
/* 00290798: sd s3,0x118(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000118)));
/* 0029079c: sd s4,0x120(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000120)));
/* 002907a0: move s4,zero */ set(20,cpu(0));
/* 002907a4: sd s5,0x128(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000128)));
/* 002907a8: move s5,zero */ set(21,cpu(0));
/* 002907ac: sd s6,0x130(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000130)));
/* 002907b0: move s6,a1 */ set(22,cpu(5));
/* 002907b4: sd s7,0x138(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000138)));
/* 002907b8: li s7,0x1 */ set(23,sx(UINT32_C(0x00000001)));
/* 002907bc: sd s8,0x140(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000140)));
/* 002907c0: sd ra,0x148(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000148)));
/* 002907c4: jal 0x002469a0 */ set(31,0x002907ccu);/* delay 002907c8 */ set(30,cpu(0));nocturneBattleActionSkillCall(0x002469a0u);
/* 002907cc: addiu s3,sp,0x80 */ set(19,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));
/* 002907d0: move s2,sp */ set(18,cpu(29));
/* 002907d4: sllv v0,s7,s0 */ set(2,sx((uint32_t)((uint32_t)cpu(23)<<((uint32_t)cpu(16)&31u))));
L_002907d8:;
/* 002907d8: and v0,s6,v0 */ set(2,cpu(22)&cpu(2));
/* 002907dc: beql v0,zero,0x0029081c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002907e0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));goto L_0029081c;}}
/* 002907e4: jal 0x00246ab8 */ set(31,0x002907ecu);/* delay 002907e8 */ set(4,cpu(16));nocturneBattleActionSkillCall(0x00246ab8u);
/* 002907ec: beq v0,zero,0x00290800 */ {int taken=(cpu(2)==cpu(0));/* delay 002907f0 */ set(4,cpu(16));if(taken){goto L_00290800;}}
/* 002907f4: sw v0,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002907f8: addiu s2,s2,0x4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000004)));
/* 002907fc: addiu s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
L_00290800:;
/* 00290800: jal 0x00246a40 */ set(31,0x00290808u);/* delay 00290804 */ nocturneBattleActionSkillCall(0x00246a40u);
/* 00290808: beq v0,zero,0x0029081c */ {int taken=(cpu(2)==cpu(0));/* delay 0029080c */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));if(taken){goto L_0029081c;}}
/* 00290810: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00290814: addiu s3,s3,0x4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000004)));
/* 00290818: addiu s5,s5,0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));
L_0029081c:;
/* 0029081c: slti v0,s0,0x10 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00290820: bne v0,zero,0x002907d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00290824 */ set(2,sx((uint32_t)((uint32_t)cpu(23)<<((uint32_t)cpu(16)&31u))));if(taken){goto L_002907d8;}}
/* 00290828: beq s4,zero,0x002908d4 */ {int taken=(cpu(20)==cpu(0));/* delay 0029082c */ set(2,cpu(0));if(taken){goto L_002908d4;}}
/* 00290830: slti v0,s1,0x44 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000044));
/* 00290834: beq v0,zero,0x00290868 */ {int taken=(cpu(2)==cpu(0));/* delay 00290838 */ set(2,sx(UINT32_C(0x00000109)));if(taken){goto L_00290868;}}
/* 0029083c: slti v0,s1,0x40 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000040));
/* 00290840: beq v0,zero,0x002908a4 */ {int taken=(cpu(2)==cpu(0));/* delay 00290844 */ set(2,sx((uint32_t)cpu(17)<<4));if(taken){goto L_002908a4;}}
/* 00290848: slti v0,s1,0x37 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000037));
/* 0029084c: beq v0,zero,0x002908d4 */ {int taken=(cpu(2)==cpu(0));/* delay 00290850 */ set(2,cpu(30));if(taken){goto L_002908d4;}}
/* 00290854: slti v0,s1,0x34 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000034));
/* 00290858: bnel v0,zero,0x002908d4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0029085c */ set(2,cpu(30));goto L_002908d4;}}
/* 00290860: b 0x002908a4 */ /* delay 00290864 */ set(2,sx((uint32_t)cpu(17)<<4));goto L_002908a4;
L_00290868:;
/* 00290868: beq s1,v0,0x002908a0 */ {int taken=(cpu(17)==cpu(2));/* delay 0029086c */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x0000010a));if(taken){goto L_002908a0;}}
/* 00290870: beq v0,zero,0x00290898 */ {int taken=(cpu(2)==cpu(0));/* delay 00290874 */ set(2,sx(UINT32_C(0x00000114)));if(taken){goto L_00290898;}}
/* 00290878: slti v0,s1,0xcf */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x000000cf));
/* 0029087c: beq v0,zero,0x002908d4 */ {int taken=(cpu(2)==cpu(0));/* delay 00290880 */ set(2,cpu(30));if(taken){goto L_002908d4;}}
/* 00290884: slti v0,s1,0xcb */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x000000cb));
/* 00290888: bnel v0,zero,0x002908d4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0029088c */ set(2,cpu(30));goto L_002908d4;}}
/* 00290890: b 0x002908a4 */ /* delay 00290894 */ set(2,sx((uint32_t)cpu(17)<<4));goto L_002908a4;
L_00290898:;
/* 00290898: bne s1,v0,0x002908d4 */ {int taken=(cpu(17)!=cpu(2));/* delay 0029089c */ set(2,cpu(30));if(taken){goto L_002908d4;}}
L_002908a0:;
/* 002908a0: sll v0,s1,0x4 */ set(2,sx((uint32_t)cpu(17)<<4));
L_002908a4:;
/* 002908a4: move a1,s5 */ set(5,cpu(21));
/* 002908a8: subu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(17)));
/* 002908ac: addiu a0,sp,0x80 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));
/* 002908b0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002908b4: lui a2,0x3d */ set(6,sx(UINT32_C(0x003d0000)));
/* 002908b8: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 002908bc: lw a2,0x79c0(a2) */ lw(6,ea(6,(int32_t)UINT32_C(0x000079c0)));
/* 002908c0: jal 0x002901d0 */ set(31,0x002908c8u);/* delay 002908c4 */ set(30,cpu(0));body_002901d0();
/* 002908c8: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 002908cc: movz s8,v1,v0 */ if(cpu(2)==0){set(30,cpu(3));}
/* 002908d0: move v0,s8 */ set(2,cpu(30));
L_002908d4:;
/* 002908d4: ld s0,0x100(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000100)));
/* 002908d8: ld s1,0x108(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000108)));
/* 002908dc: ld s2,0x110(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000110)));
/* 002908e0: ld s3,0x118(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000118)));
/* 002908e4: ld s4,0x120(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000120)));
/* 002908e8: ld s5,0x128(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000128)));
/* 002908ec: ld s6,0x130(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000130)));
/* 002908f0: ld s7,0x138(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000138)));
/* 002908f4: ld s8,0x140(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000140)));
/* 002908f8: ld ra,0x148(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000148)));
/* 002908fc: jr ra */ {uint64_t target=cpu(31);/* delay 00290900 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000150)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_00290780(uint64_t a0, uint64_t a1){
set(4,a0);
set(5,a1);
body_00290780();
return cpu(2);
}
static void body_002aa718(void){
nocturneEffectAxisNoteEntry(0x002aa718u);
uint64_t incoming=cpu(31);
/* 002aa718: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002aa71c: move a1,a0 */ set(5,cpu(4));
/* 002aa720: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa724: lw a2,0x4(a1) */ lw(6,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002aa728: beq a2,zero,0x002aa778 */ {int taken=(cpu(6)==cpu(0));/* delay 002aa72c */ set(2,cpu(0));if(taken){goto L_002aa778;}}
/* 002aa730: lw v0,0x8(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000008)));
/* 002aa734: bne v0,zero,0x002aa778 */ {int taken=(cpu(2)!=cpu(0));/* delay 002aa738 */ set(2,cpu(0));if(taken){goto L_002aa778;}}
/* 002aa73c: lw v0,0x10(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 002aa740: lw v1,0x10(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002aa744: lw a0,0x4(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 002aa748: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002aa74c: sw v0,0x10(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002aa750: beq a0,zero,0x002aa768 */ {int taken=(cpu(4)==cpu(0));/* delay 002aa754 */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));if(taken){goto L_002aa768;}}
/* 002aa758: lw v0,0x4(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 002aa75c: b 0x002aa76c */ /* delay 002aa760 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));goto L_002aa76c;
L_002aa768:;
/* 002aa768: sw a1,-0x20dc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdf24)),(uint32_t)cpu(5));
L_002aa76c:;
/* 002aa76c: jal 0x002a8bd8 */ set(31,0x002aa774u);/* delay 002aa770 */ set(4,cpu(6));nocturneBattleActionSkillCall(0x002a8bd8u);
/* 002aa774: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002aa778:;
/* 002aa778: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa77c: jr ra */ {uint64_t target=cpu(31);/* delay 002aa780 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_002AA718(uint64_t a0){
set(4,a0);
body_002aa718();
return cpu(2);
}
static void body_002aa7f0(void){
nocturneEffectAxisNoteEntry(0x002aa7f0u);
uint64_t incoming=cpu(31);
/* 002aa7f0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002aa7f4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa7f8: move s0,a0 */ set(16,cpu(4));
/* 002aa7fc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa800: beq s0,zero,0x002aa850 */ {int taken=(cpu(16)==cpu(0));/* delay 002aa804 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002aa850;}}
/* 002aa808: jal 0x002e4070 */ set(31,0x002aa810u);/* delay 002aa80c */ nocturneBattleActionSkillCall(0x002e4070u);
/* 002aa810: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002aa814: move a0,s0 */ set(4,cpu(16));
/* 002aa818: jal 0x002aa718 */ set(31,0x002aa820u);/* delay 002aa81c */ set(17,cpu(2));body_002aa718();
/* 002aa820: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002aa824: beq a0,zero,0x002aa840 */ {int taken=(cpu(4)==cpu(0));/* delay 002aa828 */ if(taken){goto L_002aa840;}}
/* 002aa82c: lw v0,0x8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002aa830: bne v0,zero,0x002aa840 */ {int taken=(cpu(2)!=cpu(0));/* delay 002aa834 */ if(taken){goto L_002aa840;}}
/* 002aa838: jal 0x002aa718 */ set(31,0x002aa840u);/* delay 002aa83c */ body_002aa718();
L_002aa840:;
/* 002aa840: beq s1,zero,0x002aa854 */ {int taken=(cpu(17)==cpu(0));/* delay 002aa844 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002aa854;}}
/* 002aa848: jal 0x002e40b8 */ set(31,0x002aa850u);/* delay 002aa84c */ nocturneBattleActionSkillCall(0x002e40b8u);
L_002aa850:;
/* 002aa850: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002aa854:;
/* 002aa854: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa858: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aa85c: jr ra */ {uint64_t target=cpu(31);/* delay 002aa860 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_002AA7F0(uint64_t a0){
set(4,a0);
body_002aa7f0();
return;
}
static void body_002aa8d0(void){
nocturneEffectAxisNoteEntry(0x002aa8d0u);
uint64_t incoming=cpu(31);
/* 002aa8d0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002aa8d4: li v0,-0x20 */ set(2,sx(UINT32_C(0xffffffe0)));
/* 002aa8d8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa8dc: move s0,a2 */ set(16,cpu(6));
/* 002aa8e0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa8e4: move s1,a0 */ set(17,cpu(4));
/* 002aa8e8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aa8ec: move s2,a1 */ set(18,cpu(5));
/* 002aa8f0: addiu a2,s1,0x3f */ set(6,sx((uint32_t)cpu(17)+UINT32_C(0x0000003f)));
/* 002aa8f4: li a0,-0x40 */ set(4,sx(UINT32_C(0xffffffc0)));
/* 002aa8f8: addiu a1,s2,0x1f */ set(5,sx((uint32_t)cpu(18)+UINT32_C(0x0000001f)));
/* 002aa8fc: sltiu v1,s0,0x3b */ set(3,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000003b));
/* 002aa900: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aa904: and a0,a2,a0 */ set(4,cpu(6)&cpu(4));
/* 002aa908: beq v1,zero,0x002aa92c */ {int taken=(cpu(3)==cpu(0));/* delay 002aa90c */ set(5,cpu(5)&cpu(2));if(taken){goto L_002aa92c;}}
/* 002aa910: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002aa914: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002aa918: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002aa91c: lw v1,-0x6dd0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffff9230)));
/* 002aa920: jr v1 */ {uint64_t target=cpu(3);/* delay 002aa924 */ switch((uint32_t)target){case 0x002aa928u:goto L_002aa928;case 0x002aa92cu:goto L_002aa92c;default:abort();}}
L_002aa928:;
/* 002aa928: sra a0,a0,0x1 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>1)));
L_002aa92c:;
/* 002aa92c: mult a0,a0,a1 */ nativeSignedMultiply(4,(uint32_t)cpu(4),(uint32_t)cpu(5));
/* 002aa930: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002aa934: li v0,-0x800 */ set(2,sx(UINT32_C(0xfffff800)));
/* 002aa938: addiu a0,a0,0x7ff */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000007ff)));
/* 002aa93c: jal 0x002aa438 */ set(31,0x002aa944u);/* delay 002aa940 */ set(4,cpu(4)&cpu(2));nocturneBattleActionSkillCall(0x002aa438u);
/* 002aa944: move v1,v0 */ set(3,cpu(2));
/* 002aa948: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aa94c: sw s0,0x18(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(16));
/* 002aa950: sh s1,0x14(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(17));
/* 002aa954: sh s2,0x16(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(18));
/* 002aa958: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa95c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa960: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aa964: jr ra */ {uint64_t target=cpu(31);/* delay 002aa968 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionSkill_002AA8D0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);
set(5,a1);
set(6,a2);
body_002aa8d0();
return cpu(2);
}
static void body_002ab190(void){
nocturneEffectAxisNoteEntry(0x002ab190u);
uint64_t incoming=cpu(31);
/* 002ab190: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ab194: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab198: sb a1,0x1f(a0) */ sb(ea(4,(int32_t)UINT32_C(0x0000001f)),(uint8_t)cpu(5));
/* 002ab19c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab1a0: j 0x002abb78 */ /* delay 002ab1a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002abb78();return;
}
void ps2BattleActionSkill_002AB190(uint64_t a0, uint64_t a1){
set(4,a0);
set(5,a1);
body_002ab190();
return;
}
static void body_002ab860(void){
nocturneEffectAxisNoteEntry(0x002ab860u);
uint64_t incoming=cpu(31);
/* 002ab860: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ab864: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab868: move s0,a0 */ set(16,cpu(4));
/* 002ab86c: beq s0,zero,0x002ab8e0 */ {int taken=(cpu(16)==cpu(0));/* delay 002ab870 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002ab8e0;}}
/* 002ab874: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002ab878: bne v0,zero,0x002ab888 */ {int taken=(cpu(2)!=cpu(0));/* delay 002ab87c */ if(taken){goto L_002ab888;}}
/* 002ab880: jal 0x002aa7f0 */ set(31,0x002ab888u);/* delay 002ab884 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));body_002aa7f0();
L_002ab888:;
/* 002ab888: jal 0x002aa7f0 */ set(31,0x002ab890u);/* delay 002ab88c */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));body_002aa7f0();
/* 002ab890: jal 0x002a8bd8 */ set(31,0x002ab898u);/* delay 002ab894 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));nocturneBattleActionSkillCall(0x002a8bd8u);
/* 002ab898: jal 0x002a8bd8 */ set(31,0x002ab8a0u);/* delay 002ab89c */ lw(4,ea(16,(int32_t)UINT32_C(0x0000002c)));nocturneBattleActionSkillCall(0x002a8bd8u);
/* 002ab8a0: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002ab8a4: beq v0,zero,0x002ab8b0 */ {int taken=(cpu(2)==cpu(0));/* delay 002ab8a8 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002ab8b0;}}
/* 002ab8ac: sw v1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
L_002ab8b0:;
/* 002ab8b0: beql v1,zero,0x002ab8bc */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002ab8b4 */ sw(ea(28,(int32_t)UINT32_C(0xffffd6f0)),(uint32_t)cpu(2));goto L_002ab8bc;}}
/* 002ab8b8: sw v0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002ab8bc:;
/* 002ab8bc: jal 0x002a81b0 */ set(31,0x002ab8c4u);/* delay 002ab8c0 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000030)));nocturneBattleActionSkillCall(0x002a81b0u);
/* 002ab8c4: jal 0x002a81b0 */ set(31,0x002ab8ccu);/* delay 002ab8c8 */ lw(4,ea(16,(int32_t)UINT32_C(0x0000003c)));nocturneBattleActionSkillCall(0x002a81b0u);
/* 002ab8cc: move a0,s0 */ set(4,cpu(16));
/* 002ab8d0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab8d4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab8d8: j 0x002a8bd8 */ /* delay 002ab8dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002a8bd8u);return;
L_002ab8e0:;
/* 002ab8e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab8e4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab8e8: jr ra */ {uint64_t target=cpu(31);/* delay 002ab8ec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_002AB860(uint64_t a0){
set(4,a0);
body_002ab860();
return;
}
static void body_002abb78(void){
nocturneEffectAxisNoteEntry(0x002abb78u);
uint64_t incoming=cpu(31);
/* 002abb78: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002abb7c: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002abb80: move s1,a0 */ set(17,cpu(4));
/* 002abb84: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002abb88: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002abb8c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002abb90: lw s2,0x28(s1) */ lw(18,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 002abb94: beql s2,zero,0x002abc04 */ {int taken=(cpu(18)==cpu(0));if(taken){/* delay 002abb98 */ lw(18,ea(17,(int32_t)UINT32_C(0x0000002c)));goto L_002abc04;}}
/* 002abb9c: jal 0x002ab010 */ set(31,0x002abba4u);/* delay 002abba0 */ nocturneBattleActionSkillCall(0x002ab010u);
/* 002abba4: move a0,s1 */ set(4,cpu(17));
/* 002abba8: jal 0x002aaff8 */ set(31,0x002abbb0u);/* delay 002abbac */ set(16,cpu(2));nocturneBattleActionSkillCall(0x002aaff8u);
/* 002abbb0: ld t3,0x20(s2) */ restore(11,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 002abbb4: move t1,v0 */ set(9,cpu(2));
/* 002abbb8: lh a1,0xc(s1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002abbbc: move a3,s0 */ set(7,cpu(16));
/* 002abbc0: dsrl32 t3,t3,0x2 */ set(11,cpu(11)>>34);
/* 002abbc4: lh a2,0xe(s1) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 002abbc8: lbu t0,0x1a(s1) */ set(8,byte(ea(17,(int32_t)UINT32_C(0x0000001a))));
/* 002abbcc: andi t3,t3,0x1 */ set(11,cpu(11)&UINT32_C(0x00000001));
/* 002abbd0: lbu t2,0x19(s1) */ set(10,byte(ea(17,(int32_t)UINT32_C(0x00000019))));
/* 002abbd4: move a0,s2 */ set(4,cpu(18));
/* 002abbd8: lbu t4,0x1b(s1) */ set(12,byte(ea(17,(int32_t)UINT32_C(0x0000001b))));
/* 002abbdc: dsll32 t3,t3,0x0 */ set(11,cpu(11)<<32);
/* 002abbe0: dsra32 t3,t3,0x0 */ set(11,(uint64_t)((int64_t)cpu(11)>>32));
/* 002abbe4: lhu t5,0x1c(s1) */ set(13,half(ea(17,(int32_t)UINT32_C(0x0000001c))));
/* 002abbe8: lbu v1,0x1f(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x0000001f))));
/* 002abbec: sw t4,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 002abbf0: sw t5,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(13));
/* 002abbf4: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 002abbf8: jal 0x002ab910 */ set(31,0x002abc00u);/* delay 002abbfc */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));nocturneBattleActionSkillCall(0x002ab910u);
/* 002abc00: lw s2,0x2c(s1) */ lw(18,ea(17,(int32_t)UINT32_C(0x0000002c)));
L_002abc04:;
/* 002abc04: beq s2,zero,0x002abc78 */ {int taken=(cpu(18)==cpu(0));/* delay 002abc08 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002abc78;}}
/* 002abc0c: jal 0x002ab010 */ set(31,0x002abc14u);/* delay 002abc10 */ set(4,cpu(17));nocturneBattleActionSkillCall(0x002ab010u);
/* 002abc14: move a0,s1 */ set(4,cpu(17));
/* 002abc18: jal 0x002aaff8 */ set(31,0x002abc20u);/* delay 002abc1c */ set(16,cpu(2));nocturneBattleActionSkillCall(0x002aaff8u);
/* 002abc20: ld t3,0x20(s2) */ restore(11,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 002abc24: move t1,v0 */ set(9,cpu(2));
/* 002abc28: lh a1,0xc(s1) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002abc2c: li t6,0x1 */ set(14,sx(UINT32_C(0x00000001)));
/* 002abc30: dsrl32 t3,t3,0x2 */ set(11,cpu(11)>>34);
/* 002abc34: lh a2,0xe(s1) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 002abc38: lbu t0,0x1a(s1) */ set(8,byte(ea(17,(int32_t)UINT32_C(0x0000001a))));
/* 002abc3c: andi t3,t3,0x1 */ set(11,cpu(11)&UINT32_C(0x00000001));
/* 002abc40: lbu t2,0x19(s1) */ set(10,byte(ea(17,(int32_t)UINT32_C(0x00000019))));
/* 002abc44: move a0,s2 */ set(4,cpu(18));
/* 002abc48: lbu t5,0x1f(s1) */ set(13,byte(ea(17,(int32_t)UINT32_C(0x0000001f))));
/* 002abc4c: move a3,s0 */ set(7,cpu(16));
/* 002abc50: lbu v1,0x1b(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x0000001b))));
/* 002abc54: dsll32 t3,t3,0x0 */ set(11,cpu(11)<<32);
/* 002abc58: dsra32 t3,t3,0x0 */ set(11,(uint64_t)((int64_t)cpu(11)>>32));
/* 002abc5c: lhu t4,0x1c(s1) */ set(12,half(ea(17,(int32_t)UINT32_C(0x0000001c))));
/* 002abc60: sw v1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002abc64: sw t4,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(12));
/* 002abc68: sw t5,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(13));
/* 002abc6c: jal 0x002ab910 */ set(31,0x002abc74u);/* delay 002abc70 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(14));nocturneBattleActionSkillCall(0x002ab910u);
/* 002abc74: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
L_002abc78:;
/* 002abc78: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002abc7c: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002abc80: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002abc84: jr ra */ {uint64_t target=cpu(31);/* delay 002abc88 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_002ABB78(uint64_t a0){
set(4,a0);
body_002abb78();
return;
}
static void body_002b5e30(void){
nocturneEffectAxisNoteEntry(0x002b5e30u);
uint64_t incoming=cpu(31);
/* 002b5e30: qmfc2 t0,vf28 */ qmf(8,28);
/* 002b5e34: qmfc2 t1,vf29 */ qmf(9,29);
/* 002b5e38: qmfc2 t2,vf30 */ qmf(10,30);
/* 002b5e3c: qmfc2 t3,vf31 */ qmf(11,31);
/* 002b5e40: pextlw t4,t1,t0 */ pextlw(12,9,8);
/* 002b5e44: pextuw t5,t1,t0 */ pextuw(13,9,8);
/* 002b5e48: pextlw t6,t3,t2 */ pextlw(14,11,10);
/* 002b5e4c: pextuw t7,t3,t2 */ pextuw(15,11,10);
/* 002b5e50: pcpyld t0,t6,t4 */ pcpyld(8,14,12);
/* 002b5e54: pcpyud t1,t4,t6 */ pcpyud(9,12,14);
/* 002b5e58: pcpyld t2,t7,t5 */ pcpyld(10,15,13);
/* 002b5e5c: pcpyud t3,t5,t7 */ pcpyud(11,13,15);
/* 002b5e60: qmtc2 t0,vf28 */ qmt(28,8);
/* 002b5e64: qmtc2 t1,vf29 */ qmt(29,9);
/* 002b5e68: qmtc2 t2,vf30 */ qmt(30,10);
/* 002b5e6c: qmtc2 t3,vf31 */ qmt(31,11);
/* 002b5e70: jr ra */ {uint64_t target=cpu(31);/* delay 002b5e74 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_002B5E30(void){
body_002b5e30();
return;
}
static void body_002b6690(void){
nocturneEffectAxisNoteEntry(0x002b6690u);
uint64_t incoming=cpu(31);
/* 002b6690: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b6694: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b6698: lqc2 vf24,0x0(a0) */ loadVu(24,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002b669c: lqc2 vf25,0x10(a0) */ loadVu(25,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002b66a0: lqc2 vf26,0x20(a0) */ loadVu(26,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002b66a4: lqc2 vf27,0x30(a0) */ loadVu(27,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002b66a8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b66ac: j 0x002b6550 */ /* delay 002b66b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattleActionSkillCall(0x002b6550u);return;
}
void ps2BattleActionSkill_002B6690(uint64_t a0){
set(4,a0);
body_002b6690();
return;
}
static void body_002b9e30(void){
nocturneEffectAxisNoteEntry(0x002b9e30u);
uint64_t incoming=cpu(31);
/* 002b9e30: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b9e34: lui v1,0x6c0b */ set(3,sx(UINT32_C(0x6c0b0000)));
/* 002b9e38: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9e3c: move s0,a0 */ set(16,cpu(4));
/* 002b9e40: ori v1,v1,0xc000 */ set(3,cpu(3)|UINT32_C(0x0000c000));
/* 002b9e44: li v0,0xc */ set(2,sx(UINT32_C(0x0000000c)));
/* 002b9e48: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9e4c: move s1,a1 */ set(17,cpu(5));
/* 002b9e50: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b9e54: move s2,a2 */ set(18,cpu(6));
/* 002b9e58: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b9e5c: sh v0,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));
/* 002b9e60: sw v1,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 002b9e64: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002b9e68: lqc2 vf28,0x0(s2) */ loadVu(28,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 002b9e6c: lqc2 vf29,0x10(s2) */ loadVu(29,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002b9e70: lqc2 vf30,0x20(s2) */ loadVu(30,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 002b9e74: lqc2 vf31,0x30(s2) */ loadVu(31,ea(18,(int32_t)UINT32_C(0x00000030)));
/* 002b9e78: addiu v0,s0,0x10 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002b9e7c: sqc2 vf28,0x0(v0) */ storeVu(28,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b9e80: sqc2 vf29,0x10(v0) */ storeVu(29,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 002b9e84: sqc2 vf30,0x20(v0) */ storeVu(30,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 002b9e88: sqc2 vf31,0x30(v0) */ storeVu(31,ea(2,(int32_t)UINT32_C(0x00000030)));
/* 002b9e8c: jal 0x002b66b8 */ set(31,0x002b9e94u);/* delay 002b9e90 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000030)));nocturneBattleActionSkillCall(0x002b66b8u);
/* 002b9e94: addiu v0,s0,0x50 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000050)));
/* 002b9e98: sqc2 vf28,0x0(v0) */ storeVu(28,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b9e9c: sqc2 vf29,0x10(v0) */ storeVu(29,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 002b9ea0: sqc2 vf30,0x20(v0) */ storeVu(30,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 002b9ea4: sqc2 vf31,0x30(v0) */ storeVu(31,ea(2,(int32_t)UINT32_C(0x00000030)));
/* 002b9ea8: addiu v1,s1,0x70 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000070)));
/* 002b9eac: lqc2 vf10,0x0(v1) */ loadVu(10,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002b9eb0: addiu v0,s0,0x90 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000090)));
/* 002b9eb4: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b9eb8: addiu v1,s1,0x80 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000080)));
/* 002b9ebc: lqc2 vf10,0x0(v1) */ loadVu(10,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002b9ec0: addiu v0,s0,0xa0 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x000000a0)));
/* 002b9ec4: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b9ec8: lqc2 vf28,0x0(s2) */ loadVu(28,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 002b9ecc: lqc2 vf29,0x10(s2) */ loadVu(29,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002b9ed0: lqc2 vf30,0x20(s2) */ loadVu(30,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 002b9ed4: lqc2 vf31,0x30(s2) */ loadVu(31,ea(18,(int32_t)UINT32_C(0x00000030)));
/* 002b9ed8: jal 0x002b5e78 */ set(31,0x002b9ee0u);/* delay 002b9edc */ nocturneBattleActionSkillCall(0x002b5e78u);
/* 002b9ee0: vmove.xyzw vf10,vf31 */ moveVu(10,31);
/* 002b9ee4: addiu v0,s0,0xb0 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x000000b0)));
/* 002b9ee8: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b9eec: addiu s1,s1,0x90 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000090)));
/* 002b9ef0: sqc2 vf10,0x0(s1) */ storeVu(10,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002b9ef4: lui v0,0x400 */ set(2,sx(UINT32_C(0x04000000)));
/* 002b9ef8: lui v1,0x1400 */ set(3,sx(UINT32_C(0x14000000)));
/* 002b9efc: ori v0,v0,0x2 */ set(2,cpu(2)|UINT32_C(0x00000002));
/* 002b9f00: sw v1,0xc4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000c4)),(uint32_t)cpu(3));
/* 002b9f04: sw v0,0xc0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000c0)),(uint32_t)cpu(2));
/* 002b9f08: sw zero,0xcc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000cc)),(uint32_t)cpu(0));
/* 002b9f0c: sw zero,0xc8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000c8)),(uint32_t)cpu(0));
/* 002b9f10: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9f14: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9f18: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b9f1c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b9f20: jr ra */ {uint64_t target=cpu(31);/* delay 002b9f24 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_002B9E30(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);
set(5,a1);
set(6,a2);
body_002b9e30();
return;
}
static void body_002ba070(void){
nocturneEffectAxisNoteEntry(0x002ba070u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002ba070: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002ba074: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 002ba078: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 002ba07c: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ba080: move s0,a0 */ set(16,cpu(4));
/* 002ba084: swc1 f21,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),f[21]);
/* 002ba088: swc1 f20,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),f[20]);
/* 002ba08c: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002ba090: lwc1 f0,0x2c(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x0000002c)));
/* 002ba094: lwc1 f3,0x28(s0) */ f[3]=word(ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002ba098: lwc1 f1,0x18(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000018)));
/* 002ba09c: lwc1 f2,0x1c(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 002ba0a0: sub.S f5,f0,f3 */ f[5]=EE_FPU_SUB_S(f[0],f[3]);
/* 002ba0a4: mul.S f21,f1,f4 */ f[21]=EE_FPU_MUL_S(f[1],f[4]);
/* 002ba0a8: mul.S f20,f2,f4 */ f[20]=EE_FPU_MUL_S(f[2],f[4]);
/* 002ba0ac: qmfc2 a1,vf0 */ qmf(5,0);
/* 002ba0b0: pextuw a0,zero,a1 */ pextuw(4,0,5);
/* 002ba0b4: pextuw v0,zero,a0 */ pextuw(2,0,4);
/* 002ba0b8: pextuw v1,a0,zero */ pextuw(3,4,0);
/* 002ba0bc: sq v0,0x0(sp) */ sq(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ba0c0: sq v1,0x10(sp) */ sq(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ba0c4: sq a0,0x20(sp) */ sq(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ba0c8: sq a1,0x30(sp) */ sq(5,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ba0cc: add.S f1,f3,f0 */ f[1]=EE_FPU_ADD_S(f[3],f[0]);
/* 002ba0d0: lwc1 f4,0x4(s0) */ f[4]=word(ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002ba0d4: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 002ba0d8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002ba0dc: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 002ba0e0: mul.S f4,f21,f4 */ f[4]=EE_FPU_MUL_S(f[21],f[4]);
/* 002ba0e4: nop  */ 
/* 002ba0e8: nop  */ 
/* 002ba0ec: div.S f3,f2,f20 */ f[3]=EE_FPU_DIV_S(f[2],f[20]);
/* 002ba0f0: neg.S f1,f1 */ f[1]=f[1]^UINT32_C(0x80000000);
/* 002ba0f4: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 002ba0f8: nop  */ 
/* 002ba0fc: nop  */ 
/* 002ba100: div.S f1,f1,f5 */ f[1]=EE_FPU_DIV_S(f[1],f[5]);
/* 002ba104: swc1 f3,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[3]);
/* 002ba108: nop  */ 
/* 002ba10c: nop  */ 
/* 002ba110: div.S f2,f2,f4 */ f[2]=EE_FPU_DIV_S(f[2],f[4]);
/* 002ba114: swc1 f1,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[1]);
/* 002ba118: nop  */ 
/* 002ba11c: nop  */ 
/* 002ba120: div.S f0,f0,f5 */ f[0]=EE_FPU_DIV_S(f[0],f[5]);
/* 002ba124: swc1 f2,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[2]);
/* 002ba128: swc1 f0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[0]);
/* 002ba12c: lqc2 vf28,0x0(sp) */ loadVu(28,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ba130: lqc2 vf29,0x10(sp) */ loadVu(29,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ba134: lqc2 vf30,0x20(sp) */ loadVu(30,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ba138: lqc2 vf31,0x30(sp) */ loadVu(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ba13c: qmfc2 a1,vf0 */ qmf(5,0);
/* 002ba140: pextuw a0,zero,a1 */ pextuw(4,0,5);
/* 002ba144: pextuw v0,zero,a0 */ pextuw(2,0,4);
/* 002ba148: pextuw v1,a0,zero */ pextuw(3,4,0);
/* 002ba14c: sq v0,0x0(sp) */ sq(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ba150: sq v1,0x10(sp) */ sq(3,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ba154: sq a0,0x20(sp) */ sq(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ba158: sq a1,0x30(sp) */ sq(5,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ba15c: lw a2,0x0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002ba160: andi a2,a2,0x2 */ set(6,cpu(6)&UINT32_C(0x00000002));
/* 002ba164: beql a2,zero,0x002ba194 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002ba168 */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000008)));goto L_002ba194;}}
/* 002ba16c: lwc1 f0,0xc(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002ba170: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 002ba174: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 002ba178: jal 0x002cf6b8 */ set(31,0x002ba180u);/* delay 002ba17c */ f[12]=EE_FPU_MUL_S(f[0],f[12]);body_002cf6b8();
/* 002ba180: lwc1 f1,0x1c(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 002ba184: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 002ba188: nop  */ 
/* 002ba18c: nop  */ 
/* 002ba190: div.S f1,f1,f0 */ f[1]=EE_FPU_DIV_S(f[1],f[0]);
L_002ba194:;
/* 002ba194: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002ba198: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002ba19c: move a0,sp */ set(4,cpu(29));
/* 002ba1a0: swc1 f1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[1]);
/* 002ba1a4: swc1 f1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[1]);
/* 002ba1a8: sw zero,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 002ba1ac: sw zero,0x3c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));
/* 002ba1b0: swc1 f0,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[0]);
/* 002ba1b4: jal 0x002b6690 */ set(31,0x002ba1bcu);/* delay 002ba1b8 */ sw(ea(29,(int32_t)UINT32_C(0x0000002c)),f[0]);body_002b6690();
/* 002ba1bc: addiu v0,s0,0x30 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));
/* 002ba1c0: sqc2 vf28,0x0(v0) */ storeVu(28,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002ba1c4: sqc2 vf29,0x10(v0) */ storeVu(29,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 002ba1c8: sqc2 vf30,0x20(v0) */ storeVu(30,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 002ba1cc: sqc2 vf31,0x30(v0) */ storeVu(31,ea(2,(int32_t)UINT32_C(0x00000030)));
/* 002ba1d0: lwc1 f1,0x20(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002ba1d4: lwc1 f0,0x24(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000024)));
/* 002ba1d8: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002ba1dc: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 002ba1e0: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 002ba1e4: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 002ba1e8: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002ba1ec: swc1 f21,0x70(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000070)),f[21]);
/* 002ba1f0: beq v0,zero,0x002ba208 */ {int taken=(cpu(2)==cpu(0));/* delay 002ba1f4 */ f[4]=EE_FPU_MUL_S(f[0],f[2]);if(taken){goto L_002ba208;}}
/* 002ba1f8: mul.S f0,f20,f2 */ f[0]=EE_FPU_MUL_S(f[20],f[2]);
/* 002ba1fc: b 0x002ba20c */ /* delay 002ba200 */ sw(ea(16,(int32_t)UINT32_C(0x00000074)),f[0]);goto L_002ba20c;
L_002ba208:;
/* 002ba208: swc1 f20,0x74(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000074)),f[20]);
L_002ba20c:;
/* 002ba20c: add.S f3,f4,f1 */ f[3]=EE_FPU_ADD_S(f[4],f[1]);
/* 002ba210: lwc1 f1,0x10(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002ba214: lwc1 f2,0x14(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x00000014)));
/* 002ba218: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002ba21c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002ba220: sw zero,0x8c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000008c)),(uint32_t)cpu(0));
/* 002ba224: swc1 f0,0x7c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000007c)),f[0]);
/* 002ba228: swc1 f4,0x78(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000078)),f[4]);
/* 002ba22c: swc1 f1,0x80(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000080)),f[1]);
/* 002ba230: swc1 f2,0x84(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000084)),f[2]);
/* 002ba234: swc1 f3,0x88(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000088)),f[3]);
/* 002ba238: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002ba23c: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ba240: lwc1 f21,0x58(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002ba244: lwc1 f20,0x50(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002ba248: jr ra */ {uint64_t target=cpu(31);/* delay 002ba24c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_002BA070(uint64_t a0){
set(4,a0);
body_002ba070();
return;
}
static void body_002ba250(void){
nocturneEffectAxisNoteEntry(0x002ba250u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition;
uint32_t qvalue;
/* 002ba250: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002ba254: lui v0,0x6c0d */ set(2,sx(UINT32_C(0x6c0d0000)));
/* 002ba258: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ba25c: move s0,a0 */ set(16,cpu(4));
/* 002ba260: li v1,0xd */ set(3,sx(UINT32_C(0x0000000d)));
/* 002ba264: ori v0,v0,0x4398 */ set(2,cpu(2)|UINT32_C(0x00004398));
/* 002ba268: lui a0,0x1000 */ set(4,sx(UINT32_C(0x10000000)));
/* 002ba26c: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ba270: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ba274: sh v1,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002ba278: sw a0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 002ba27c: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002ba280: lqc2 vf11,0x0(a2) */ loadVu(11,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002ba284: addiu v0,s0,0x80 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000080)));
/* 002ba288: sqc2 vf11,0x0(v0) */ storeVu(11,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002ba28c: lui t2,0xbf80 */ set(10,sx(UINT32_C(0xbf800000)));
/* 002ba290: addiu a3,s0,0x50 */ set(7,sx((uint32_t)cpu(16)+UINT32_C(0x00000050)));
/* 002ba294: move t0,zero */ set(8,cpu(0));
/* 002ba298: move t1,zero */ set(9,cpu(0));
/* 002ba29c: addiu a0,s0,0x30 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));
/* 002ba2a0: addiu a2,s0,0x5c */ set(6,sx((uint32_t)cpu(16)+UINT32_C(0x0000005c)));
/* 002ba2a4: nop  */ 
L_002ba2a8:;
/* 002ba2a8: lw v1,0x0(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002ba2ac: bne v1,zero,0x002ba2d8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002ba2b0 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));if(taken){goto L_002ba2d8;}}
/* 002ba2b4: sw zero,-0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0xffffffe0)),(uint32_t)cpu(0));
/* 002ba2b8: sw zero,-0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0xfffffff0)),(uint32_t)cpu(0));
/* 002ba2bc: sw zero,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002ba2c0: sw zero,-0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0xfffffff4)),(uint32_t)cpu(0));
/* 002ba2c4: sw zero,-0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0xfffffff8)),(uint32_t)cpu(0));
/* 002ba2c8: sw zero,-0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0xfffffffc)),(uint32_t)cpu(0));
/* 002ba2cc: b 0x002ba32c */ /* delay 002ba2d0 */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));goto L_002ba32c;
L_002ba2d8:;
/* 002ba2d8: movz t0,v1,t0 */ if(cpu(8)==0){set(8,cpu(3));}
/* 002ba2dc: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002ba2e0: vmul.xyz vf2,vf10,vf10 */ vuMulMasked(2,10,10,14,-1);
/* 002ba2e4: vmulax.w ACC,vf0,vf2 */ vuMulaMasked(0,2,0,1);
/* 002ba2e8: vmadday.w ACC,vf0,vf2 */ vuMaddaMasked(0,2,1,1);
/* 002ba2ec: vmaddz.w vf2,vf0,vf2 */ vuMaddMasked(2,0,2,2,1);
/* 002ba2f0: vrsqrt Q,vf0,vf2 */ qvalue=EE_ROT_VU_RSQRT(vuLane(0,3),vuLane(2,3));EE_ROT_Q_WRITE(qvalue);
/* 002ba2f4: vwaitq  */ 
/* 002ba2f8: vmulq.xyz vf10,vf10,Q */ vuMulQMasked(10,10,qvalue,14);
/* 002ba2fc: qmtc2 t2,vf2 */ qmt(2,10);
/* 002ba300: vmulx.xyzw vf10,vf10,vf2 */ vuMulMasked(10,10,2,15,0);
/* 002ba304: sqc2 vf10,0x0(sp) */ storeVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ba308: lwc1 f0,0x0(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ba30c: lwc1 f1,0x4(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002ba310: lwc1 f2,0x8(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ba314: swc1 f0,-0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0xffffffe0)),f[0]);
/* 002ba318: swc1 f1,-0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0xfffffff0)),f[1]);
/* 002ba31c: swc1 f2,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),f[2]);
/* 002ba320: lqc2 vf10,0x0(v1) */ loadVu(10,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002ba324: vadd.xyzw vf11,vf11,vf10 */ vuAddMasked(11,11,10,15);
/* 002ba328: sqc2 vf10,0x0(a3) */ storeVu(10,ea(7,(int32_t)UINT32_C(0x00000000)));
L_002ba32c:;
/* 002ba32c: addiu t1,t1,0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000001)));
/* 002ba330: addiu a3,a3,0x10 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));
/* 002ba334: slti v0,t1,0x3 */ set(2,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 002ba338: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 002ba33c: addiu a2,a2,0x10 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000010)));
/* 002ba340: bne v0,zero,0x002ba2a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002ba344 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000004)));if(taken){goto L_002ba2a8;}}
/* 002ba348: addiu v1,s0,0x40 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
/* 002ba34c: addiu a0,s0,0x50 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000050)));
/* 002ba350: lq v0,0x0(a0) */ pkLq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002ba354: sq v0,0x0(v1) */ sq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002ba358: addiu a1,s0,0x90 */ set(5,sx((uint32_t)cpu(16)+UINT32_C(0x00000090)));
/* 002ba35c: sqc2 vf11,0x0(a1) */ storeVu(11,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002ba360: bne t0,zero,0x002ba398 */ {int taken=(cpu(8)!=cpu(0));/* delay 002ba364 */ set(17,sx((uint32_t)cpu(8)+UINT32_C(0x00000010)));if(taken){goto L_002ba398;}}
/* 002ba368: addiu a2,s0,0xa0 */ set(6,sx((uint32_t)cpu(16)+UINT32_C(0x000000a0)));
/* 002ba36c: qmfc2 a1,vf0 */ qmf(5,0);
/* 002ba370: pextuw a0,zero,a1 */ pextuw(4,0,5);
/* 002ba374: pextuw v0,zero,a0 */ pextuw(2,0,4);
/* 002ba378: pextuw v1,a0,zero */ pextuw(3,4,0);
/* 002ba37c: sq v0,0x0(a2) */ sq(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002ba380: sq v1,0x10(a2) */ sq(3,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002ba384: sq a0,0x20(a2) */ sq(4,ea(6,(int32_t)UINT32_C(0x00000020)));
/* 002ba388: sq a1,0x30(a2) */ sq(5,ea(6,(int32_t)UINT32_C(0x00000030)));
/* 002ba38c: b 0x002ba4f8 */ /* delay 002ba390 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));goto L_002ba4f8;
L_002ba398:;
/* 002ba398: lqc2 vf10,0x0(s1) */ loadVu(10,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002ba39c: vmul.xyz vf2,vf10,vf10 */ vuMulMasked(2,10,10,14,-1);
/* 002ba3a0: vmulax.w ACC,vf0,vf2 */ vuMulaMasked(0,2,0,1);
/* 002ba3a4: vmadday.w ACC,vf0,vf2 */ vuMaddaMasked(0,2,1,1);
/* 002ba3a8: vmaddz.w vf2,vf0,vf2 */ vuMaddMasked(2,0,2,2,1);
/* 002ba3ac: vrsqrt Q,vf0,vf2 */ qvalue=EE_ROT_VU_RSQRT(vuLane(0,3),vuLane(2,3));EE_ROT_Q_WRITE(qvalue);
/* 002ba3b0: vwaitq  */ 
/* 002ba3b4: vmulq.xyz vf10,vf10,Q */ vuMulQMasked(10,10,qvalue,14);
/* 002ba3b8: vmulx.w vf10,vf10,vf0 */ vuMulMasked(10,10,0,1,0);
/* 002ba3bc: vmove.xyzw vf30,vf10 */ moveVu(30,10);
/* 002ba3c0: addiu v0,sp,0x10 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002ba3c4: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002ba3c8: lwc1 f1,-0x5a20(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa5e0)));
/* 002ba3cc: lwc1 f0,0x10(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ba3d0: abs.S f0,f0 */ f[0]=f[0]&UINT32_C(0x7fffffff);
/* 002ba3d4: c.lt.S f0,f1 */ condition=EE_FPU_COMPARE_S(f[0],f[1],1)!=0;
/* 002ba3d8: bc1fl 0x002ba418 */ {int taken=(condition==0);if(taken){/* delay 002ba3dc */ set(2,sx(UINT32_C(0x00530000)));goto L_002ba418;}}
/* 002ba3e0: lwc1 f0,0x18(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ba3e4: abs.S f0,f0 */ f[0]=f[0]&UINT32_C(0x7fffffff);
/* 002ba3e8: c.lt.S f0,f1 */ condition=EE_FPU_COMPARE_S(f[0],f[1],1)!=0;
/* 002ba3ec: bc1fl 0x002ba418 */ {int taken=(condition==0);if(taken){/* delay 002ba3f0 */ set(2,sx(UINT32_C(0x00530000)));goto L_002ba418;}}
/* 002ba3f4: lwc1 f0,0x14(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002ba3f8: neg.S f0,f0 */ f[0]=f[0]^UINT32_C(0x80000000);
/* 002ba3fc: swc1 f0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[0]);
/* 002ba400: sw zero,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002ba404: sw zero,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 002ba408: sw zero,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 002ba40c: lqc2 vf11,0x0(v0) */ loadVu(11,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002ba410: b 0x002ba420 */ /* delay 002ba414 */ goto L_002ba420;
L_002ba418:;
/* 002ba418: addiu v0,v0,-0x69d0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff9630)));
/* 002ba41c: lqc2 vf11,0x0(v0) */ loadVu(11,ea(2,(int32_t)UINT32_C(0x00000000)));
L_002ba420:;
/* 002ba420: vopmula.xyz ACC,vf10,vf11 */ vuOpmula(10,11);
/* 002ba424: vopmsub.xyz vf10,vf11,vf10 */ vuOpmsub(10,11,10);
/* 002ba428: vmul.xyz vf2,vf10,vf10 */ vuMulMasked(2,10,10,14,-1);
/* 002ba42c: vmulax.w ACC,vf0,vf2 */ vuMulaMasked(0,2,0,1);
/* 002ba430: vmadday.w ACC,vf0,vf2 */ vuMaddaMasked(0,2,1,1);
/* 002ba434: vmaddz.w vf2,vf0,vf2 */ vuMaddMasked(2,0,2,2,1);
/* 002ba438: vrsqrt Q,vf0,vf2 */ qvalue=EE_ROT_VU_RSQRT(vuLane(0,3),vuLane(2,3));EE_ROT_Q_WRITE(qvalue);
/* 002ba43c: vwaitq  */ 
/* 002ba440: vmulq.xyz vf10,vf10,Q */ vuMulQMasked(10,10,qvalue,14);
/* 002ba444: vmulx.w vf10,vf10,vf0 */ vuMulMasked(10,10,0,1,0);
/* 002ba448: vmove.xyzw vf28,vf10 */ moveVu(28,10);
/* 002ba44c: vmove.xyzw vf11,vf10 */ moveVu(11,10);
/* 002ba450: vmove.xyzw vf10,vf30 */ moveVu(10,30);
/* 002ba454: vopmula.xyz ACC,vf10,vf11 */ vuOpmula(10,11);
/* 002ba458: vopmsub.xyz vf10,vf11,vf10 */ vuOpmsub(10,11,10);
/* 002ba45c: vmulx.w vf10,vf10,vf0 */ vuMulMasked(10,10,0,1,0);
/* 002ba460: vmove.xyzw vf29,vf10 */ moveVu(29,10);
/* 002ba464: vmove.xyzw vf31,vf0 */ moveVu(31,0);
/* 002ba468: jal 0x002b5e30 */ set(31,0x002ba470u);/* delay 002ba46c */ body_002b5e30();
/* 002ba470: lqc2 vf10,0x0(s1) */ loadVu(10,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002ba474: vmul.xyz vf2,vf10,vf10 */ vuMulMasked(2,10,10,14,-1);
/* 002ba478: vmulax.w ACC,vf0,vf2 */ vuMulaMasked(0,2,0,1);
/* 002ba47c: vmadday.w ACC,vf0,vf2 */ vuMaddaMasked(0,2,1,1);
/* 002ba480: vmaddz.w vf2,vf0,vf2 */ vuMaddMasked(2,0,2,2,1);
/* 002ba484: vrsqrt Q,vf0,vf2 */ qvalue=EE_ROT_VU_RSQRT(vuLane(0,3),vuLane(2,3));EE_ROT_Q_WRITE(qvalue);
/* 002ba488: vwaitq  */ 
/* 002ba48c: vmulq.xyz vf10,vf10,Q */ vuMulQMasked(10,10,qvalue,14);
/* 002ba490: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002ba494: addiu a2,a2,-0x68a8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9758)));
/* 002ba498: lw v0,0x0(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002ba49c: lw v1,0x10(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002ba4a0: lw a0,0x20(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x00000020)));
/* 002ba4a4: lw a1,0x30(a2) */ lw(5,ea(6,(int32_t)UINT32_C(0x00000030)));
/* 002ba4a8: pextlw v0,v1,v0 */ pextlw(2,3,2);
/* 002ba4ac: pextlw a0,a1,a0 */ pextlw(4,5,4);
/* 002ba4b0: pcpyld v0,a0,v0 */ pcpyld(2,4,2);
/* 002ba4b4: qmtc2 v0,vf11 */ qmt(11,2);
/* 002ba4b8: vadd.xyzw vf10,vf10,vf11 */ vuAddMasked(10,10,11,15);
/* 002ba4bc: vsub.xyz vf10,vf0,vf10 */ vuSubMasked(10,0,10,14);
/* 002ba4c0: vmul.xyz vf2,vf10,vf10 */ vuMulMasked(2,10,10,14,-1);
/* 002ba4c4: vmulax.w ACC,vf0,vf2 */ vuMulaMasked(0,2,0,1);
/* 002ba4c8: vmadday.w ACC,vf0,vf2 */ vuMaddaMasked(0,2,1,1);
/* 002ba4cc: vmaddz.w vf2,vf0,vf2 */ vuMaddMasked(2,0,2,2,1);
/* 002ba4d0: vrsqrt Q,vf0,vf2 */ qvalue=EE_ROT_VU_RSQRT(vuLane(0,3),vuLane(2,3));EE_ROT_Q_WRITE(qvalue);
/* 002ba4d4: vwaitq  */ 
/* 002ba4d8: vmulq.xyz vf10,vf10,Q */ vuMulQMasked(10,10,qvalue,14);
/* 002ba4dc: vmove.xyzw vf31,vf10 */ moveVu(31,10);
/* 002ba4e0: addiu v0,s0,0xa0 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x000000a0)));
/* 002ba4e4: sqc2 vf28,0x0(v0) */ storeVu(28,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002ba4e8: sqc2 vf29,0x10(v0) */ storeVu(29,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 002ba4ec: sqc2 vf30,0x20(v0) */ storeVu(30,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 002ba4f0: sqc2 vf31,0x30(v0) */ storeVu(31,ea(2,(int32_t)UINT32_C(0x00000030)));
/* 002ba4f4: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
L_002ba4f8:;
/* 002ba4f8: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ba4fc: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ba500: jr ra */ {uint64_t target=cpu(31);/* delay 002ba504 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionSkill_002BA250(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);
set(5,a1);
set(6,a2);
body_002ba250();
return;
}
static void body_002cf6b8(void){
nocturneEffectAxisNoteEntry(0x002cf6b8u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002cf6b8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002cf6bc: mov.S f0,f12 */ f[0]=f[12];
/* 002cf6c0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002cf6c4: swc1 f0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[0]);
/* 002cf6c8: lui v1,0x7fff */ set(3,sx(UINT32_C(0x7fff0000)));
/* 002cf6cc: clear f13 */ f[13]=0;
/* 002cf6d0: lw a1,0x10(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002cf6d4: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002cf6d8: lui v0,0x3f49 */ set(2,sx(UINT32_C(0x3f490000)));
/* 002cf6dc: and v1,a1,v1 */ set(3,cpu(5)&cpu(3));
/* 002cf6e0: ori v0,v0,0xfda */ set(2,cpu(2)|UINT32_C(0x00000fda));
/* 002cf6e4: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 002cf6e8: bne v0,zero,0x002cf700 */ {int taken=(cpu(2)!=cpu(0));/* delay 002cf6ec */ set(4,cpu(29));if(taken){goto L_002cf700;}}
/* 002cf6f0: jal 0x002d0ca8 */ set(31,0x002cf6f8u);/* delay 002cf6f4 */ set(4,sx(UINT32_C(0x00000001)));body_002d0ca8();
/* 002cf6f8: b 0x002cf728 */ /* delay 002cf6fc */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));goto L_002cf728;
L_002cf700:;
/* 002cf700: jal 0x002cfd68 */ set(31,0x002cf708u);/* delay 002cf704 */ nocturneBattleActionSkillCall(0x002cfd68u);
/* 002cf708: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002cf70c: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002cf710: lwc1 f12,0x0(sp) */ f[12]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002cf714: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 002cf718: lwc1 f13,0x4(sp) */ f[13]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002cf71c: jal 0x002d0ca8 */ set(31,0x002cf724u);/* delay 002cf720 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(2)));body_002d0ca8();
/* 002cf724: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
L_002cf728:;
/* 002cf728: jr ra */ {uint64_t target=cpu(31);/* delay 002cf72c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
float ps2BattleActionSkill_002CF6B8(float f12){
nocturneEffectHostFpr()[12]=bits(f12);
body_002cf6b8();
return real(nocturneEffectHostFpr()[0]);
}
static void body_002d0ca8(void){
nocturneEffectAxisNoteEntry(0x002d0ca8u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002d0ca8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002d0cac: mov.S f16,f12 */ f[16]=f[12];
/* 002d0cb0: mfc1 a2,f16 */ set(6,sx(f[16]));
/* 002d0cb4: lui v1,0x7fff */ set(3,sx(UINT32_C(0x7fff0000)));
/* 002d0cb8: lui v0,0x317f */ set(2,sx(UINT32_C(0x317f0000)));
/* 002d0cbc: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002d0cc0: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d0cc4: and a1,a2,v1 */ set(5,cpu(6)&cpu(3));
/* 002d0cc8: slt v0,v0,a1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(5));
/* 002d0ccc: bne v0,zero,0x002d0d48 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d0cd0 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002d0d48;}}
/* 002d0cd4: cvt.w.S f0,f16 */ f[0]=EE_FPU_CVT_W_S(f[16]);
/* 002d0cd8: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 002d0cdc: bne v0,zero,0x002d0d4c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d0ce0 */ set(2,sx(UINT32_C(0x3f2c0000)));if(taken){goto L_002d0d4c;}}
/* 002d0ce4: addiu v0,a0,0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002d0ce8: or v0,a1,v0 */ set(2,cpu(5)|cpu(2));
/* 002d0cec: bnel v0,zero,0x002d0d18 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d0cf0 */ set(2,sx(UINT32_C(0x00000001)));goto L_002d0d18;}}
/* 002d0cf4: jal 0x002d11c0 */ set(31,0x002d0cfcu);/* delay 002d0cf8 */ nocturneBattleActionSkillCall(0x002d11c0u);
/* 002d0cfc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002d0d00: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 002d0d04: nop  */ 
/* 002d0d08: nop  */ 
/* 002d0d0c: div.S f0,f1,f0 */ f[0]=EE_FPU_DIV_S(f[1],f[0]);
/* 002d0d10: b 0x002d0f24 */ /* delay 002d0d14 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_002d0f24;
L_002d0d18:;
/* 002d0d18: beq a0,v0,0x002d0d40 */ {int taken=(cpu(4)==cpu(2));/* delay 002d0d1c */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002d0d40;}}
/* 002d0d20: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
/* 002d0d24: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002d0d28: nop  */ 
/* 002d0d2c: nop  */ 
/* 002d0d30: div.S f0,f0,f16 */ f[0]=EE_FPU_DIV_S(f[0],f[16]);
/* 002d0d34: b 0x002d0f24 */ /* delay 002d0d38 */ goto L_002d0f24;
L_002d0d40:;
/* 002d0d40: b 0x002d0f20 */ /* delay 002d0d44 */ f[0]=f[16];goto L_002d0f20;
L_002d0d48:;
/* 002d0d48: lui v0,0x3f2c */ set(2,sx(UINT32_C(0x3f2c0000)));
L_002d0d4c:;
/* 002d0d4c: ori v0,v0,0xa13f */ set(2,cpu(2)|UINT32_C(0x0000a13f));
/* 002d0d50: slt v0,v0,a1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(5));
/* 002d0d54: beql v0,zero,0x002d0d98 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d0d58 */ f[15]=EE_FPU_MUL_S(f[16],f[16]);goto L_002d0d98;}}
/* 002d0d5c: bgez a2,0x002d0d6c */ {int taken=((int64_t)cpu(6)>=0);/* delay 002d0d60 */ if(taken){goto L_002d0d6c;}}
/* 002d0d64: neg.S f16,f16 */ f[16]=f[16]^UINT32_C(0x80000000);
/* 002d0d68: neg.S f13,f13 */ f[13]=f[13]^UINT32_C(0x80000000);
L_002d0d6c:;
/* 002d0d6c: lui at,0x3f49 */ set(1,sx(UINT32_C(0x3f490000)));
/* 002d0d70: ori at,at,0xfda */ set(1,cpu(1)|UINT32_C(0x00000fda));
/* 002d0d74: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002d0d78: lui at,0x3322 */ set(1,sx(UINT32_C(0x33220000)));
/* 002d0d7c: ori at,at,0x2167 */ set(1,cpu(1)|UINT32_C(0x00002167));
/* 002d0d80: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 002d0d84: sub.S f15,f0,f16 */ f[15]=EE_FPU_SUB_S(f[0],f[16]);
/* 002d0d88: sub.S f14,f1,f13 */ f[14]=EE_FPU_SUB_S(f[1],f[13]);
/* 002d0d8c: clear f13 */ f[13]=0;
/* 002d0d90: add.S f16,f15,f14 */ f[16]=EE_FPU_ADD_S(f[15],f[14]);
/* 002d0d94: mul.S f15,f16,f16 */ f[15]=EE_FPU_MUL_S(f[16],f[16]);
L_002d0d98:;
/* 002d0d98: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d0d9c: addiu v0,v0,-0x4c40 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb3c0)));
/* 002d0da0: lui v1,0x3f2c */ set(3,sx(UINT32_C(0x3f2c0000)));
/* 002d0da4: lwc1 f8,0x30(v0) */ f[8]=word(ea(2,(int32_t)UINT32_C(0x00000030)));
/* 002d0da8: ori v1,v1,0xa13f */ set(3,cpu(3)|UINT32_C(0x0000a13f));
/* 002d0dac: lwc1 f9,0x2c(v0) */ f[9]=word(ea(2,(int32_t)UINT32_C(0x0000002c)));
/* 002d0db0: slt v1,v1,a1 */ set(3,(int64_t)cpu(3)<(int64_t)cpu(5));
/* 002d0db4: mul.S f14,f15,f15 */ f[14]=EE_FPU_MUL_S(f[15],f[15]);
/* 002d0db8: lwc1 f0,0x28(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000028)));
/* 002d0dbc: lwc1 f1,0x24(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000024)));
/* 002d0dc0: mul.S f12,f15,f16 */ f[12]=EE_FPU_MUL_S(f[15],f[16]);
/* 002d0dc4: lwc1 f2,0x20(v0) */ f[2]=word(ea(2,(int32_t)UINT32_C(0x00000020)));
/* 002d0dc8: lwc1 f3,0x1c(v0) */ f[3]=word(ea(2,(int32_t)UINT32_C(0x0000001c)));
/* 002d0dcc: mul.S f8,f14,f8 */ f[8]=EE_FPU_MUL_S(f[14],f[8]);
/* 002d0dd0: lwc1 f5,0x18(v0) */ f[5]=word(ea(2,(int32_t)UINT32_C(0x00000018)));
/* 002d0dd4: mul.S f9,f14,f9 */ f[9]=EE_FPU_MUL_S(f[14],f[9]);
/* 002d0dd8: lwc1 f4,0x14(v0) */ f[4]=word(ea(2,(int32_t)UINT32_C(0x00000014)));
/* 002d0ddc: lwc1 f6,0x10(v0) */ f[6]=word(ea(2,(int32_t)UINT32_C(0x00000010)));
/* 002d0de0: lwc1 f7,0xc(v0) */ f[7]=word(ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002d0de4: add.S f0,f0,f8 */ f[0]=EE_FPU_ADD_S(f[0],f[8]);
/* 002d0de8: lwc1 f8,0x0(v0) */ f[8]=word(ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002d0dec: add.S f1,f1,f9 */ f[1]=EE_FPU_ADD_S(f[1],f[9]);
/* 002d0df0: lwc1 f10,0x8(v0) */ f[10]=word(ea(2,(int32_t)UINT32_C(0x00000008)));
/* 002d0df4: lwc1 f11,0x4(v0) */ f[11]=word(ea(2,(int32_t)UINT32_C(0x00000004)));
/* 002d0df8: mul.S f8,f8,f12 */ f[8]=EE_FPU_MUL_S(f[8],f[12]);
/* 002d0dfc: mul.S f0,f14,f0 */ f[0]=EE_FPU_MUL_S(f[14],f[0]);
/* 002d0e00: mul.S f1,f14,f1 */ f[1]=EE_FPU_MUL_S(f[14],f[1]);
/* 002d0e04: add.S f2,f2,f0 */ f[2]=EE_FPU_ADD_S(f[2],f[0]);
/* 002d0e08: add.S f3,f3,f1 */ f[3]=EE_FPU_ADD_S(f[3],f[1]);
/* 002d0e0c: mul.S f2,f14,f2 */ f[2]=EE_FPU_MUL_S(f[14],f[2]);
/* 002d0e10: mul.S f3,f14,f3 */ f[3]=EE_FPU_MUL_S(f[14],f[3]);
/* 002d0e14: add.S f5,f5,f2 */ f[5]=EE_FPU_ADD_S(f[5],f[2]);
/* 002d0e18: add.S f4,f4,f3 */ f[4]=EE_FPU_ADD_S(f[4],f[3]);
/* 002d0e1c: mul.S f5,f14,f5 */ f[5]=EE_FPU_MUL_S(f[14],f[5]);
/* 002d0e20: mul.S f4,f14,f4 */ f[4]=EE_FPU_MUL_S(f[14],f[4]);
/* 002d0e24: add.S f6,f6,f5 */ f[6]=EE_FPU_ADD_S(f[6],f[5]);
/* 002d0e28: add.S f7,f7,f4 */ f[7]=EE_FPU_ADD_S(f[7],f[4]);
/* 002d0e2c: mul.S f6,f14,f6 */ f[6]=EE_FPU_MUL_S(f[14],f[6]);
/* 002d0e30: mul.S f7,f14,f7 */ f[7]=EE_FPU_MUL_S(f[14],f[7]);
/* 002d0e34: add.S f10,f10,f6 */ f[10]=EE_FPU_ADD_S(f[10],f[6]);
/* 002d0e38: add.S f3,f11,f7 */ f[3]=EE_FPU_ADD_S(f[11],f[7]);
/* 002d0e3c: mul.S f5,f15,f10 */ f[5]=EE_FPU_MUL_S(f[15],f[10]);
/* 002d0e40: add.S f0,f3,f5 */ f[0]=EE_FPU_ADD_S(f[3],f[5]);
/* 002d0e44: mul.S f0,f12,f0 */ f[0]=EE_FPU_MUL_S(f[12],f[0]);
/* 002d0e48: add.S f0,f0,f13 */ f[0]=EE_FPU_ADD_S(f[0],f[13]);
/* 002d0e4c: mul.S f0,f15,f0 */ f[0]=EE_FPU_MUL_S(f[15],f[0]);
/* 002d0e50: add.S f3,f13,f0 */ f[3]=EE_FPU_ADD_S(f[13],f[0]);
/* 002d0e54: add.S f3,f3,f8 */ f[3]=EE_FPU_ADD_S(f[3],f[8]);
/* 002d0e58: beq v1,zero,0x002d0eb0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d0e5c */ f[14]=EE_FPU_ADD_S(f[16],f[3]);if(taken){goto L_002d0eb0;}}
/* 002d0e60: mtc1 a0,f5 */ f[5]=(uint32_t)cpu(4);
/* 002d0e64: cvt.s.W f5,f5 */ f[5]=EE_FPU_CVT_S_W(f[5]);
/* 002d0e68: sra v1,a2,0x1e */ set(3,sx((uint32_t)((int32_t)cpu(6)>>30)));
/* 002d0e6c: mul.S f0,f14,f14 */ f[0]=EE_FPU_MUL_S(f[14],f[14]);
/* 002d0e70: andi v1,v1,0x2 */ set(3,cpu(3)&UINT32_C(0x00000002));
/* 002d0e74: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d0e78: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002d0e7c: add.S f1,f14,f5 */ f[1]=EE_FPU_ADD_S(f[14],f[5]);
/* 002d0e80: mtc1 v0,f2 */ f[2]=(uint32_t)cpu(2);
/* 002d0e84: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 002d0e88: nop  */ 
/* 002d0e8c: nop  */ 
/* 002d0e90: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 002d0e94: sub.S f0,f0,f3 */ f[0]=EE_FPU_SUB_S(f[0],f[3]);
/* 002d0e98: sub.S f0,f16,f0 */ f[0]=EE_FPU_SUB_S(f[16],f[0]);
/* 002d0e9c: add.S f0,f0,f0 */ f[0]=EE_FPU_ADD_S(f[0],f[0]);
/* 002d0ea0: sub.S f0,f5,f0 */ f[0]=EE_FPU_SUB_S(f[5],f[0]);
/* 002d0ea4: b 0x002d0f20 */ /* delay 002d0ea8 */ f[0]=EE_FPU_MUL_S(f[2],f[0]);goto L_002d0f20;
L_002d0eb0:;
/* 002d0eb0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d0eb4: beq a0,v0,0x002d0f20 */ {int taken=(cpu(4)==cpu(2));/* delay 002d0eb8 */ f[0]=f[14];if(taken){goto L_002d0f20;}}
/* 002d0ebc: mfc1 v1,f14 */ set(3,sx(f[14]));
/* 002d0ec0: move v0,v1 */ set(2,cpu(3));
/* 002d0ec4: li v1,-0x1000 */ set(3,sx(UINT32_C(0xfffff000)));
/* 002d0ec8: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d0ecc: mtc1 v0,f15 */ f[15]=(uint32_t)cpu(2);
/* 002d0ed0: sub.S f1,f15,f16 */ f[1]=EE_FPU_SUB_S(f[15],f[16]);
/* 002d0ed4: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
/* 002d0ed8: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002d0edc: nop  */ 
/* 002d0ee0: nop  */ 
/* 002d0ee4: div.S f0,f0,f14 */ f[0]=EE_FPU_DIV_S(f[0],f[14]);
/* 002d0ee8: sub.S f5,f3,f1 */ f[5]=EE_FPU_SUB_S(f[3],f[1]);
/* 002d0eec: mov.S f1,f0 */ f[1]=f[0];
/* 002d0ef0: swc1 f1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[1]);
/* 002d0ef4: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d0ef8: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d0efc: mtc1 v0,f3 */ f[3]=(uint32_t)cpu(2);
/* 002d0f00: mul.S f4,f3,f15 */ f[4]=EE_FPU_MUL_S(f[3],f[15]);
/* 002d0f04: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002d0f08: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 002d0f0c: mul.S f1,f3,f5 */ f[1]=EE_FPU_MUL_S(f[3],f[5]);
/* 002d0f10: add.S f12,f4,f2 */ f[12]=EE_FPU_ADD_S(f[4],f[2]);
/* 002d0f14: add.S f1,f12,f1 */ f[1]=EE_FPU_ADD_S(f[12],f[1]);
/* 002d0f18: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 002d0f1c: add.S f0,f3,f0 */ f[0]=EE_FPU_ADD_S(f[3],f[0]);
L_002d0f20:;
/* 002d0f20: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
L_002d0f24:;
/* 002d0f24: jr ra */ {uint64_t target=cpu(31);/* delay 002d0f28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
float ps2BattleActionSkill_002D0CA8(uint64_t a0, float f12, float f13){
set(4,a0);
nocturneEffectHostFpr()[12]=bits(f12);
nocturneEffectHostFpr()[13]=bits(f13);
body_002d0ca8();
return real(nocturneEffectHostFpr()[0]);
}
