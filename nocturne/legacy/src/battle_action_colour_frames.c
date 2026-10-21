/* Complete original SLUS_209.11 resource/instance algorithms.
 * Each fixed C statement is tied to an original instruction. There is no
 * runtime instruction decoder, game-result provider, or expected-state input.
 * Guest frames are real shared RAM; only original stores initialize slots.
 */
#include "battle_action_consumer.h"
#include "battle_action_rotation_frame.h"
#include "battle_action_status_resources.h"
#include "effect_host_bindings.h"
#include "effect_model_child_dependency_frames.h"
#include "effect_packet_native_frames.h"
#include "effect_movie_native.h"
#include "effect_billboard_dependency_frames.h"
#include "effect_particle_camera_frames.h"
#include "effect_special_polygon_dependency_frames.h"
#include "effect_table_trig_frames.h"
#include "special_polygon_steps.h"
#include "battle_effect_copy.h"
#include "pcp_construction.h"
#include "model_pac_loading.h"
#include "model_loading_completion.h"
#include "resource_request_lifecycle.h"
#include "material_motion_scalars.h"
#include "libm_trig.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include <stdlib.h>
#include <string.h>

static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t divs(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void loadVu(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a),16);EE_ROT_VU_WRITE(r,q);}
static void storeVu(unsigned r,uint32_t a){uint32_t q[4];EE_ROT_VU_READ(r,q);memcpy(at(a),q,16);}
static void moveVu(unsigned d,unsigned s){uint32_t q[4];EE_ROT_VU_READ(s,q);EE_ROT_VU_WRITE(d,q);}
/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */
static void vuMula(unsigned s,unsigned t,unsigned c){uint32_t x[4],y[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++){uint64_t v=EE_ROT_VU_MUL(x[k],y[c]);a[k]=(uint32_t)v;o[k]=(uint32_t)(v>>32)&1u;}EE_ROT_ACC_WRITE(a,o);}
static void vuMadd(unsigned d,unsigned s,unsigned t,unsigned c){uint32_t x[4],y[4],z[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++)z[k]=(uint32_t)EE_ROT_VU_MAC(a[k],x[k],y[c],o[k],0);EE_ROT_VU_WRITE(d,z);}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_colour_frames.h"
#include "effect_ftoi0.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include "polygon_prerequisites.h"
extern uint64_t nocturneEffectHostLo(void);
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void signedDivide(uint32_t a,uint32_t c){
 int64_t n=(int32_t)a,d=(int32_t)c;
 uint32_t q=d?(uint32_t)(n/d):(n<0?1u:UINT32_MAX),r=d?(uint32_t)(n%d):a;
 EE_ANCHOR_DIVU_STATE(q,r);
}
static void qmt(unsigned vf,unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);EE_ROT_VU_WRITE(vf,q);}
static void qmf(unsigned r,unsigned vf){uint32_t q[4];EE_ROT_VU_READ(vf,q);nocturneEffectHostCpuWrite(r,q);}
static void colourMulX(unsigned d,unsigned a,unsigned c){uint32_t x[4],y[4],q[4];EE_ROT_VU_READ(a,x);EE_ROT_VU_READ(c,y);for(unsigned k=0;k<4;k++)q[k]=(uint32_t)EE_ROT_VU_MUL(x[k],y[0]);EE_ROT_VU_WRITE(d,q);}
static void colourSubXW(unsigned d,unsigned a,unsigned c){uint32_t x[4],y[4],q[4];EE_ROT_VU_READ(a,x);EE_ROT_VU_READ(c,y);EE_ROT_VU_READ(d,q);q[3]=(uint32_t)EE_ROT_VU_SUB(x[3],y[0]);EE_ROT_VU_WRITE(d,q);}
static void colourSub(unsigned d,unsigned a,unsigned c){uint32_t x[4],y[4],q[4];EE_ROT_VU_READ(a,x);EE_ROT_VU_READ(c,y);for(unsigned k=0;k<4;k++)q[k]=(uint32_t)EE_ROT_VU_SUB(x[k],y[k]);EE_ROT_VU_WRITE(d,q);}

static void pextlb(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint8_t x[16],y[16],z[16];
 nocturneEffectHostCpuRead(a,aq);nocturneEffectHostCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<8;k++){z[k*2]=y[k];z[k*2+1]=x[k];}memcpy(q,z,16);nocturneEffectHostCpuWrite(d,q);
}
static void pextlh(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint16_t x[8],y[8],z[8];
 nocturneEffectHostCpuRead(a,aq);nocturneEffectHostCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<4;k++){z[k*2]=y[k];z[k*2+1]=x[k];}memcpy(q,z,16);nocturneEffectHostCpuWrite(d,q);
}
static void ppach(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint16_t x[8],y[8],z[8];
 nocturneEffectHostCpuRead(a,aq);nocturneEffectHostCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<4;k++){z[k]=y[k*2];z[k+4]=x[k*2];}memcpy(q,z,16);nocturneEffectHostCpuWrite(d,q);
}
static void ppacb(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint8_t x[16],y[16],z[16];
 nocturneEffectHostCpuRead(a,aq);nocturneEffectHostCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<8;k++){z[k]=y[k*2];z[k+8]=x[k*2];}memcpy(q,z,16);nocturneEffectHostCpuWrite(d,q);
}
static void itof(unsigned d,unsigned s){
 uint32_t q[4];EE_ROT_VU_READ(s,q);
 /* PEXTLB/LH with ZERO makes each input an exact unsigned byte0..255. */
 for(unsigned k=0;k<4;k++)q[k]=EE_FPU_CVT_S_W(q[k]);EE_ROT_VU_WRITE(d,q);
}
static void ftoi(unsigned d,unsigned s){
 uint32_t q[4];EE_ROT_VU_READ(s,q);
 for(unsigned k=0;k<4;k++)q[k]=nocturneEffectFtoi0Bits(q[k]);EE_ROT_VU_WRITE(d,q);
}
void ps2BattleActionPolygonColourDispatch_00167898(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectAxisNoteEntry(0x00167898u);
uint64_t incoming=cpu(31);
/* 00167898: lhu v0,0x0(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 0016789c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001678a0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001678a4: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 001678a8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001678ac: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 001678b0: move a1,a2 */ set(5,cpu(6));
/* 001678b4: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001678b8: lui v0,0x31 */ set(2,sx(UINT32_C(0x00310000)));
/* 001678bc: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001678c0: lw v0,0x7600(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00007600)));
/* 001678c4: jalr v0 */ {uint64_t target=cpu(2);set(31,0x001678ccu);/* delay 001678c8 */ set(6,cpu(7));if((uint32_t)target==0x00166b78u){ps2BattleActionPolygonTripleFade_00166B78(cpu(4),cpu(5),cpu(6));}else{nocturneCallPolygonColor((uint32_t)target,cpu(4),cpu(5),cpu(6));}}
/* 001678cc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001678d0: jr ra */ {uint64_t target=cpu(31);/* delay 001678d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPolygonTripleFade_00166B78(uint64_t a0,uint64_t a1,uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x00166b78u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00166b78: addiu sp,sp,-0xc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff40)));
/* 00166b7c: move a3,a0 */ set(7,cpu(4));
/* 00166b80: sd s0,0xa0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 00166b84: move s0,a2 */ set(16,cpu(6));
/* 00166b88: sd s1,0xa8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 00166b8c: move s1,a1 */ set(17,cpu(5));
/* 00166b90: sd s2,0xb0(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 00166b94: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 00166b98: lui v0,0xff00 */ set(2,sx(UINT32_C(0xff000000)));
/* 00166b9c: beql v1,zero,0x00166ba4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00166ba0 */ nocturneCompilerArithmeticTrap(7u);goto L_00166ba4;}}
L_00166ba4:;
/* 00166ba4: lw a0,0x8(a3) */ lw(4,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 00166ba8: and v0,s1,v0 */ set(2,cpu(17)&cpu(2));
/* 00166bac: sw v0,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
/* 00166bb0: div a0,v1 */ signedDivide((uint32_t)cpu(4),(uint32_t)cpu(3));
/* 00166bb4: addiu v1,sp,0x40 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
/* 00166bb8: lui at,0x3c00 */ set(1,sx(UINT32_C(0x3c000000)));
/* 00166bbc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00166bc0: lw a2,0x4(a3) */ lw(6,ea(7,(int32_t)UINT32_C(0x00000004)));
/* 00166bc4: mfc1 a1,f0 */ set(5,sx(f[0]));
/* 00166bc8: mflo t5 */ set(13,nocturneEffectHostLo());
/* 00166bcc: move a0,t5 */ set(4,cpu(13));
/* 00166bd0: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00166bd4: pextlb v0,zero,v0 */ pextlb(2,0,2);
/* 00166bd8: pextlh v0,zero,v0 */ pextlh(2,0,2);
/* 00166bdc: qmtc2 v0,vf10 */ qmt(10,2);
/* 00166be0: vitof0.xyzw vf10,vf10 */ itof(10,10);
/* 00166be4: qmtc2 a1,vf2 */ qmt(2,5);
/* 00166be8: vmulx.xyzw vf10,vf10,vf2 */ colourMulX(10,10,2);
/* 00166bec: vmove.xyzw vf11,vf10 */ moveVu(11,10);
/* 00166bf0: lui a1,0x31 */ set(5,sx(UINT32_C(0x00310000)));
/* 00166bf4: addiu v0,a1,0x75f0 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x000075f0)));
/* 00166bf8: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00166bfc: bltz a0,0x00166c18 */ {int taken=((int64_t)cpu(4)<0);/* delay 00166c00 */ set(2,cpu(13)&UINT32_C(0x00000001));if(taken){goto L_00166c18;}}
/* 00166c04: mtc1 t5,f1 */ f[1]=(uint32_t)cpu(13);
/* 00166c08: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00166c0c: b 0x00166c2c */ /* delay 00166c10 */ goto L_00166c2c;
L_00166c18:;
/* 00166c18: srl v1,t5,0x1 */ set(3,sx((uint32_t)cpu(13)>>1));
/* 00166c1c: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00166c20: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00166c24: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00166c28: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
L_00166c2c:;
/* 00166c2c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00166c30: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00166c34: nop  */ 
/* 00166c38: nop  */ 
/* 00166c3c: div.S f0,f0,f1 */ f[0]=divs(f[0],f[1]);
/* 00166c40: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 00166c44: qmtc2 v0,vf2 */ qmt(2,2);
/* 00166c48: vsubx.w vf3,vf0,vf2 */ colourSubXW(3,0,2);
/* 00166c4c: vmulax.xyzw ACC,vf11,vf2 */ vuMula(11,2,0);
/* 00166c50: vmaddw.xyzw vf10,vf10,vf3 */ vuMadd(10,10,3,3);
/* 00166c54: addiu s2,sp,0x20 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 00166c58: sqc2 vf10,0x0(s2) */ storeVu(10,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00166c5c: lui at,0x3c00 */ set(1,sx(UINT32_C(0x3c000000)));
/* 00166c60: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00166c64: lui v1,0xff00 */ set(3,sx(UINT32_C(0xff000000)));
/* 00166c68: and v1,s0,v1 */ set(3,cpu(16)&cpu(3));
/* 00166c6c: addiu a0,sp,0x50 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));
/* 00166c70: sw v1,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
/* 00166c74: mfc1 v1,f0 */ set(3,sx(f[0]));
/* 00166c78: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00166c7c: pextlb v0,zero,v0 */ pextlb(2,0,2);
/* 00166c80: pextlh v0,zero,v0 */ pextlh(2,0,2);
/* 00166c84: qmtc2 v0,vf10 */ qmt(10,2);
/* 00166c88: vitof0.xyzw vf10,vf10 */ itof(10,10);
/* 00166c8c: qmtc2 v1,vf2 */ qmt(2,3);
/* 00166c90: vmulx.xyzw vf10,vf10,vf2 */ colourMulX(10,10,2);
/* 00166c94: vmove.xyzw vf11,vf10 */ moveVu(11,10);
/* 00166c98: addiu v0,a1,0x75f0 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x000075f0)));
/* 00166c9c: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00166ca0: bltz t5,0x00166cb8 */ {int taken=((int64_t)cpu(13)<0);/* delay 00166ca4 */ set(2,cpu(13)&UINT32_C(0x00000001));if(taken){goto L_00166cb8;}}
/* 00166ca8: mtc1 t5,f1 */ f[1]=(uint32_t)cpu(13);
/* 00166cac: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00166cb0: b 0x00166ccc */ /* delay 00166cb4 */ goto L_00166ccc;
L_00166cb8:;
/* 00166cb8: srl v1,t5,0x1 */ set(3,sx((uint32_t)cpu(13)>>1));
/* 00166cbc: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00166cc0: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00166cc4: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00166cc8: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
L_00166ccc:;
/* 00166ccc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00166cd0: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00166cd4: nop  */ 
/* 00166cd8: nop  */ 
/* 00166cdc: div.S f0,f0,f1 */ f[0]=divs(f[0],f[1]);
/* 00166ce0: mfc1 a1,f0 */ set(5,sx(f[0]));
/* 00166ce4: qmtc2 a1,vf2 */ qmt(2,5);
/* 00166ce8: vsubx.w vf3,vf0,vf2 */ colourSubXW(3,0,2);
/* 00166cec: vmulax.xyzw ACC,vf11,vf2 */ vuMula(11,2,0);
/* 00166cf0: vmaddw.xyzw vf10,vf10,vf3 */ vuMadd(10,10,3,3);
/* 00166cf4: addiu a1,sp,0x30 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 00166cf8: sqc2 vf10,0x0(a1) */ storeVu(10,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00166cfc: beq a2,zero,0x00166e18 */ {int taken=(cpu(6)==cpu(0));/* delay 00166d00 */ set(15,cpu(0));if(taken){goto L_00166e18;}}
/* 00166d04: lw v0,0x14(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000014)));
/* 00166d08: addiu t4,sp,0x10 */ set(12,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 00166d0c: lui t6,0x3c00 */ set(14,sx(UINT32_C(0x3c000000)));
/* 00166d10: addiu t9,sp,0x60 */ set(25,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 00166d14: addiu a0,v0,0x4 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 00166d18: addiu t8,sp,0x70 */ set(24,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));
/* 00166d1c: nop  */ 
L_00166d20:;
/* 00166d20: sw s1,0x60(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(17));
/* 00166d24: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00166d28: lw v0,0x0(t9) */ lw(2,ea(25,(int32_t)UINT32_C(0x00000000)));
/* 00166d2c: pextlb v0,zero,v0 */ pextlb(2,0,2);
/* 00166d30: pextlh v0,zero,v0 */ pextlh(2,0,2);
/* 00166d34: qmtc2 v0,vf10 */ qmt(10,2);
/* 00166d38: vitof0.xyzw vf10,vf10 */ itof(10,10);
/* 00166d3c: qmtc2 t6,vf2 */ qmt(2,14);
/* 00166d40: vmulx.xyzw vf10,vf10,vf2 */ colourMulX(10,10,2);
/* 00166d44: sqc2 vf10,0x0(sp) */ storeVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00166d48: sw s0,0x70(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000070)),(uint32_t)cpu(16));
/* 00166d4c: lw v0,0x0(t8) */ lw(2,ea(24,(int32_t)UINT32_C(0x00000000)));
/* 00166d50: pextlb v0,zero,v0 */ pextlb(2,0,2);
/* 00166d54: pextlh v0,zero,v0 */ pextlh(2,0,2);
/* 00166d58: qmtc2 v0,vf10 */ qmt(10,2);
/* 00166d5c: vitof0.xyzw vf10,vf10 */ itof(10,10);
/* 00166d60: qmtc2 t6,vf2 */ qmt(2,14);
/* 00166d64: vmulx.xyzw vf10,vf10,vf2 */ colourMulX(10,10,2);
/* 00166d68: sqc2 vf10,0x0(t4) */ storeVu(10,ea(12,(int32_t)UINT32_C(0x00000000)));
/* 00166d6c: beq t5,zero,0x00166e08 */ {int taken=(cpu(13)==cpu(0));/* delay 00166d70 */ set(11,cpu(0));if(taken){goto L_00166e08;}}
/* 00166d74: lui t1,0x4300 */ set(9,sx(UINT32_C(0x43000000)));
/* 00166d78: move t0,s2 */ set(8,cpu(18));
/* 00166d7c: move a3,a1 */ set(7,cpu(5));
/* 00166d80: addiu t2,sp,0x10 */ set(10,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 00166d84: nop  */ 
L_00166d88:;
/* 00166d88: lqc2 vf10,0x0(sp) */ loadVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00166d8c: vmove.xyzw vf11,vf10 */ moveVu(11,10);
/* 00166d90: qmtc2 t1,vf2 */ qmt(2,9);
/* 00166d94: vmulx.xyzw vf10,vf10,vf2 */ colourMulX(10,10,2);
/* 00166d98: vftoi0.xyzw vf10,vf10 */ ftoi(10,10);
/* 00166d9c: qmfc2 v0,vf10 */ qmf(2,10);
/* 00166da0: ppach v0,zero,v0 */ ppach(2,0,2);
/* 00166da4: ppacb v0,zero,v0 */ ppacb(2,0,2);
/* 00166da8: sw v0,0x80(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000080)),(uint32_t)cpu(2));
/* 00166dac: sw v0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 00166db0: lqc2 vf12,0x0(t0) */ loadVu(12,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 00166db4: vsub.xyzw vf11,vf11,vf12 */ colourSub(11,11,12);
/* 00166db8: sqc2 vf11,0x0(sp) */ storeVu(11,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00166dbc: lqc2 vf10,0x0(t4) */ loadVu(10,ea(12,(int32_t)UINT32_C(0x00000000)));
/* 00166dc0: vmove.xyzw vf11,vf10 */ moveVu(11,10);
/* 00166dc4: qmtc2 t1,vf2 */ qmt(2,9);
/* 00166dc8: vmulx.xyzw vf10,vf10,vf2 */ colourMulX(10,10,2);
/* 00166dcc: vftoi0.xyzw vf10,vf10 */ ftoi(10,10);
/* 00166dd0: qmfc2 v0,vf10 */ qmf(2,10);
/* 00166dd4: ppach v0,zero,v0 */ ppach(2,0,2);
/* 00166dd8: ppacb v0,zero,v0 */ ppacb(2,0,2);
/* 00166ddc: sw v0,0x90(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000090)),(uint32_t)cpu(2));
/* 00166de0: sw v0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 00166de4: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00166de8: lqc2 vf12,0x0(a3) */ loadVu(12,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 00166dec: vsub.xyzw vf11,vf11,vf12 */ colourSub(11,11,12);
/* 00166df0: move t4,t2 */ set(12,cpu(10));
/* 00166df4: sqc2 vf11,0x0(t2) */ storeVu(11,ea(10,(int32_t)UINT32_C(0x00000000)));
/* 00166df8: addiu t3,t3,0x1 */ set(11,sx((uint32_t)cpu(11)+UINT32_C(0x00000001)));
/* 00166dfc: sltu v0,t3,t5 */ set(2,cpu(11)<cpu(13));
/* 00166e00: bne v0,zero,0x00166d88 */ {int taken=(cpu(2)!=cpu(0));/* delay 00166e04 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x0000000c)));if(taken){goto L_00166d88;}}
L_00166e08:;
/* 00166e08: addiu t7,t7,0x1 */ set(15,sx((uint32_t)cpu(15)+UINT32_C(0x00000001)));
/* 00166e0c: sltu v0,t7,a2 */ set(2,cpu(15)<cpu(6));
/* 00166e10: bne v0,zero,0x00166d20 */ {int taken=(cpu(2)!=cpu(0));/* delay 00166e14 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000014)));if(taken){goto L_00166d20;}}
L_00166e18:;
/* 00166e18: ld s0,0xa0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 00166e1c: ld s1,0xa8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 00166e20: ld s2,0xb0(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 00166e24: jr ra */ {uint64_t target=cpu(31);/* delay 00166e28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000c0)));checkReturn(target,incoming);return;}
}
