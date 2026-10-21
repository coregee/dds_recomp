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
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static float real(uint32_t u){float v;memcpy(&v,&u,4);return v;}
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static uint32_t divs(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void sq(unsigned r,uint32_t a){uint32_t q[4];nocturneEffectHostCpuRead(r,q);memcpy(at(a&~15u),q,16);}
static void loadVu(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a),16);EE_ROT_VU_WRITE(r,q);}
static void storeVu(unsigned r,uint32_t a){uint32_t q[4];EE_ROT_VU_READ(r,q);memcpy(at(a),q,16);}
static void moveVu(unsigned d,unsigned s){uint32_t q[4];EE_ROT_VU_READ(s,q);EE_ROT_VU_WRITE(d,q);}
/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */
static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_model_frames.h"
#include "battle_action_pac_frames.h"
#include "battle_action_texture_creation_frames.h"
#include "battle_action_creation_frames.h"
#include "battle_action_copy_frames.h"
#include "battle_action_printf_frames.h"
#include "pcp_remaining_native_dependency_frames.h"
#include "part_control_native_frames.h"
#include "model_effect_creation.h"
#include "model_motion_creation.h"
#include "model_cleanup.h"
#include "model_track_creation.h"
#include "resource_loader_flow.h"
#include "movie_decoder.h"
#include "billboard_copy.h"
#include "particle_release.h"
#include "effect_recursive_release.h"
#include "effect_release.h"
#include "basic_pose.h"
#include "ps2_sdk_helpers.h"
#include "ps2_sdk_neighbors.h"
#include "effect_ftoi0.h"
#include "magatuhi_helpers.h"
#include "../tests/libc_stream_mode.h"
#include <stdio.h>
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void lq(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneEffectHostCpuWrite(r,q);}
static void modelMul(unsigned d,unsigned a,unsigned c){uint32_t x[4],y[4],q[4];EE_ROT_VU_READ(a,x);EE_ROT_VU_READ(c,y);for(unsigned k=0;k<4;k++)q[k]=(uint32_t)EE_ROT_VU_MUL(x[k],y[0]);EE_ROT_VU_WRITE(d,q);}
static void modelSub(unsigned d,unsigned a,unsigned c){uint32_t x[4],y[4],q[4];EE_ROT_VU_READ(a,x);EE_ROT_VU_READ(c,y);for(unsigned k=0;k<4;k++)q[k]=(uint32_t)EE_ROT_VU_SUB(x[k],y[k]);EE_ROT_VU_WRITE(d,q);}
static void modelQmt(unsigned vf,unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);EE_ROT_VU_WRITE(vf,q);}
static void waitSemaphore(void){nocturneEffectAxisNoteEntry(0x002dbee0);set(3,0x44);uint64_t a=cpu(4);set(2,nocturneLibcStreamKernel(0x44,1,&a));}
static void signalSemaphore(void){nocturneEffectAxisNoteEntry(0x002dbec0);set(3,0x42);uint64_t a=cpu(4);set(2,nocturneLibcStreamKernel(0x42,1,&a));}

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
static void itof(unsigned d,unsigned s){
 uint32_t q[4];EE_ROT_VU_READ(s,q);
 /* PEXTLB/LH with ZERO makes each input an exact unsigned byte0..255. */
 for(unsigned k=0;k<4;k++)q[k]=EE_FPU_CVT_S_W(q[k]);EE_ROT_VU_WRITE(d,q);
}
static void quatSplit(uint64_t result,uint32_t *v,uint32_t *of){*v=(uint32_t)result;*of=(uint32_t)(result>>32)&1;}
static void quatValue(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned bc,unsigned op)
{
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_VU_READ(d,v);
 for(unsigned i=0;i<4;i++)if(mask&(8u>>i))v[i]=(uint32_t)(op==0?EE_ROT_VU_ADD(a[i],b[bc==4?i:bc]):op==1?EE_ROT_VU_SUB(a[i],b[bc==4?i:bc]):EE_ROT_VU_MUL(a[i],b[bc==4?i:bc]));
 EE_ROT_VU_WRITE(d,v);
}
static void quatAccum(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned bc,unsigned op)
{
 uint32_t a[4],b[4],v[4],ac[4],of[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_ACC_READ(ac,of);
 if(d==32)memcpy(v,ac,16);else EE_ROT_VU_READ(d,v);
 for(unsigned i=0;i<4;i++)if(mask&(8u>>i)){
  uint32_t next;uint64_t r=op==0?EE_ROT_VU_ADD(a[i],b[bc]):op==1?EE_ROT_VU_MUL(a[i],b[bc]):EE_ROT_VU_MAC(ac[i],a[i],b[bc],of[i],op==3);
  quatSplit(r,&v[i],&next);if(d==32)of[i]=next;
 }
 if(d==32)EE_ROT_ACC_WRITE(v,of);else EE_ROT_VU_WRITE(d,v);
}
static void body_00175cd0(void);
static uint64_t body_00175e10(void);
static uint64_t body_001dc158(void);
static uint64_t body_001dc188(void);
static void body_001dc1d8(void);
static void body_001dc290(void);
static void body_001dc3a8(void);
static void body_001dc4c0(void);
static uint64_t body_001dc550(void);
static void body_001dc5c8(void);
static void body_001dc600(void);
static void body_001dc650(void);
static void body_001dc748(void);
static void body_001dc808(void);
static uint64_t body_001dc8b8(void);
static uint64_t body_001dca88(void);
static uint64_t body_001dcab8(void);
static uint64_t body_001dcce8(void);
static void body_001dcd00(void);
static void body_001dcd60(void);
static void body_001dce88(void);
static uint64_t body_001dd0d0(void);
static void body_001dd220(void);
static void body_001dd440(void);
static void body_001dd538(void);
static void body_001dd558(void);
static void body_001dd750(void);
static uint64_t body_001ddb68(void);
static uint64_t body_001ddb78(void);
static uint64_t body_001ddd18(void);
static uint64_t body_001ddd48(void);
static uint64_t body_001ddf00(void);
static void body_001de170(void);
static uint64_t body_001dea58(void);
static uint64_t body_001dea60(void);
static uint64_t body_001dea68(void);
static uint64_t body_001deae8(void);
static uint64_t body_001deb00(void);
static uint64_t body_001deb80(void);
static uint64_t body_001deb88(void);
static void body_001df290(void);
static void body_001df2e8(void);
static void body_001df348(void);
static void body_001df3d0(void);
static uint64_t body_001df460(void);
static void body_001df480(void);
static uint64_t body_001df570(void);
static uint64_t body_001df5c8(void);
static uint64_t body_001df600(void);
static uint64_t body_001df638(void);
static void body_001df670(void);
static void body_001df770(void);
static void body_001df820(void);
static void body_001df848(void);
static void body_001df968(void);
static void body_001dfa00(void);
static void body_001dfa78(void);
static void body_001dfb00(void);
static void body_002a8bd8(void);
static uint64_t body_002a9158(void);
static uint64_t body_002a9540(void);
static void body_002a9558(void);
static void body_002a9618(void);
static void body_002a9650(void);
static void body_002ab308(void);
static uint64_t body_002ab448(void);
static void body_002ab8f0(void);
static void body_002ac7b0(void);
static void body_002b0648(void);
static uint64_t body_002b2a60(void);
static void body_002b2a80(void);
static void body_002b2b10(void);
static uint64_t body_002b2bd0(void);
static void body_002b2db0(void);
static void body_002bfee8(void);
static void body_002c0600(void);
static void body_00175cd0(void){
nocturneEffectAxisNoteEntry(0x00175cd0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00175cd0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00175cd4: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 00175cd8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00175cdc: move s0,a0 */ set(16,cpu(4));
/* 00175ce0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00175ce4: addiu v0,v0,-0x20a0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffdf60)));
/* 00175ce8: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00175cec: jal 0x001dd720 */ set(31,0x00175cf4u);/* delay 00175cf0 */ set(4,cpu(16));ps2EffectPcpModelSetPositionVu_001DD720(cpu(4));
/* 00175cf4: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 00175cf8: addiu v0,v0,-0x2090 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffdf70)));
/* 00175cfc: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00175d00: jal 0x001dd750 */ set(31,0x00175d08u);/* delay 00175d04 */ set(4,cpu(16));body_001dd750();
/* 00175d08: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 00175d0c: addiu v0,v0,-0x2080 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffdf80)));
/* 00175d10: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00175d14: jal 0x001dd7c0 */ set(31,0x00175d1cu);/* delay 00175d18 */ set(4,cpu(16));ps2EffectPcpModelSetScaleVu_001DD7C0(cpu(4));
/* 00175d1c: move a0,s0 */ set(4,cpu(16));
/* 00175d20: lui a1,0x8080 */ set(5,sx(UINT32_C(0x80800000)));
/* 00175d24: jal 0x001dd840 */ set(31,0x00175d2cu);/* delay 00175d28 */ set(5,cpu(5)|UINT32_C(0x00008080));ps2EffectPcpModelSetColor_001DD840(cpu(4),cpu(5));
/* 00175d2c: move a0,s0 */ set(4,cpu(16));
/* 00175d30: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 00175d34: move a1,zero */ set(5,cpu(0));
/* 00175d38: beq v0,zero,0x00175d58 */ {int taken=(cpu(2)==cpu(0));/* delay 00175d3c */ set(6,cpu(0));if(taken){goto L_00175d58;}}
/* 00175d40: jal 0x001dd538 */ set(31,0x00175d48u);/* delay 00175d44 */ body_001dd538();
/* 00175d48: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00175d4c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00175d50: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 00175d54: swc1 f0,0x20(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),f[0]);
L_00175d58:;
/* 00175d58: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00175d5c: li v1,-0x2 */ set(3,sx(UINT32_C(0xfffffffe)));
/* 00175d60: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00175d64: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 00175d68: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00175d6c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00175d70: jr ra */ {uint64_t target=cpu(31);/* delay 00175d74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_00175CD0(uint64_t a0){
set(4,a0);
body_00175cd0();
}
static uint64_t body_00175e10(void){
nocturneEffectAxisNoteEntry(0x00175e10u);
uint64_t incoming=cpu(31);
/* 00175e10: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00175e14: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00175e18: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00175e1c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00175e20: jal 0x001ddb68 */ set(31,0x00175e28u);/* delay 00175e24 */ set(16,cpu(4));body_001ddb68();
/* 00175e28: move a0,s0 */ set(4,cpu(16));
/* 00175e2c: jal 0x001ddb78 */ set(31,0x00175e34u);/* delay 00175e30 */ set(17,cpu(2));body_001ddb78();
/* 00175e34: move a0,s1 */ set(4,cpu(17));
/* 00175e38: jal 0x001dd0d0 */ set(31,0x00175e40u);/* delay 00175e3c */ set(5,cpu(2));body_001dd0d0();
/* 00175e40: move s0,v0 */ set(16,cpu(2));
/* 00175e44: jal 0x00175cd0 */ set(31,0x00175e4cu);/* delay 00175e48 */ set(4,cpu(16));body_00175cd0();
/* 00175e4c: move v0,s0 */ set(2,cpu(16));
/* 00175e50: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00175e54: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00175e58: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00175e5c: jr ra */ {uint64_t target=cpu(31);/* delay 00175e60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_00175E10(uint64_t a0){
set(4,a0);
return body_00175e10();
}
static uint64_t body_001dc158(void){
nocturneEffectAxisNoteEntry(0x001dc158u);
uint64_t incoming=cpu(31);
/* 001dc158: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 001dc15c: lui v1,0x33 */ set(3,sx(UINT32_C(0x00330000)));
/* 001dc160: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001dc164: lw v1,-0x3ba8(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffc458)));
L_001dc168:;
/* 001dc168: beq v1,zero,0x001dc17c */ {int taken=(cpu(3)==cpu(0));/* delay 001dc16c */ if(taken){goto L_001dc17c;}}
/* 001dc170: lhu v0,0xa(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000a))));
/* 001dc174: bnel v0,a1,0x001dc168 */ {int taken=(cpu(2)!=cpu(5));if(taken){/* delay 001dc178 */ lw(3,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_001dc168;}}
L_001dc17c:;
/* 001dc17c: jr ra */ {uint64_t target=cpu(31);/* delay 001dc180 */ set(2,cpu(3));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DC158(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001dc158();
}
static uint64_t body_001dc188(void){
nocturneEffectAxisNoteEntry(0x001dc188u);
uint64_t incoming=cpu(31);
/* 001dc188: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 001dc18c: lui at,0x33 */ set(1,sx(UINT32_C(0x00330000)));
/* 001dc190: addu at,at,a0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 001dc194: lw a0,-0x3b88(at) */ lw(4,ea(1,(int32_t)UINT32_C(0xffffc478)));
/* 001dc198: beq a0,zero,0x001dc1d0 */ {int taken=(cpu(4)==cpu(0));/* delay 001dc19c */ set(2,cpu(0));if(taken){goto L_001dc1d0;}}
/* 001dc1a0: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001dc1a4: nop  */ 
L_001dc1a8:;
/* 001dc1a8: beq v1,a1,0x001dc1d0 */ {int taken=(cpu(3)==cpu(5));/* delay 001dc1ac */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_001dc1d0;}}
/* 001dc1b0: lw a0,0x0(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001dc1b4: nop  */ 
/* 001dc1b8: nop  */ 
/* 001dc1bc: nop  */ 
/* 001dc1c0: nop  */ 
/* 001dc1c4: bnel a0,zero,0x001dc1a8 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 001dc1c8 */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));goto L_001dc1a8;}}
/* 001dc1cc: move v0,zero */ set(2,cpu(0));
L_001dc1d0:;
/* 001dc1d0: jr ra */ {uint64_t target=cpu(31);/* delay 001dc1d4 */ checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DC188(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001dc188();
}
static void body_001dc1d8(void){
nocturneEffectAxisNoteEntry(0x001dc1d8u);
uint64_t incoming=cpu(31);
/* 001dc1d8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dc1dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc1e0: move s0,a0 */ set(16,cpu(4));
/* 001dc1e4: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001dc1e8: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 001dc1ec: lui at,0x33 */ set(1,sx(UINT32_C(0x00330000)));
/* 001dc1f0: addiu at,at,-0x3b88 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffc478)));
/* 001dc1f4: addu s0,at,s0 */ set(16,sx((uint32_t)cpu(1)+(uint32_t)cpu(16)));
/* 001dc1f8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc1fc: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc200: jal 0x002a8af8 */ set(31,0x001dc208u);/* delay 001dc204 */ set(17,cpu(5));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 001dc208: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001dc20c: sw s1,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 001dc210: sw v1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001dc214: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc218: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001dc21c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc220: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc224: jr ra */ {uint64_t target=cpu(31);/* delay 001dc228 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DC1D8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_001dc1d8();
}
static void body_001dc290(void){
nocturneEffectAxisNoteEntry(0x001dc290u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001dc290: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001dc294: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc298: move s0,a0 */ set(16,cpu(4));
/* 001dc29c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc2a0: move s1,a1 */ set(17,cpu(5));
/* 001dc2a4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc2a8: move s2,a3 */ set(18,cpu(7));
/* 001dc2ac: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc2b0: move s3,t0 */ set(19,cpu(8));
/* 001dc2b4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc2b8: move s4,t1 */ set(20,cpu(9));
/* 001dc2bc: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dc2c0: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dc2c4: jal 0x001dc4c0 */ set(31,0x001dc2ccu);/* delay 001dc2c8 */ set(21,cpu(6));body_001dc4c0();
/* 001dc2cc: jal 0x002a8af8 */ set(31,0x001dc2d4u);/* delay 001dc2d0 */ set(4,sx(UINT32_C(0x000000b4)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 001dc2d4: move a1,v0 */ set(5,cpu(2));
/* 001dc2d8: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 001dc2dc: lui at,0x33 */ set(1,sx(UINT32_C(0x00330000)));
/* 001dc2e0: addiu at,at,-0x3ba8 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffc458)));
/* 001dc2e4: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 001dc2e8: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001dc2ec: bnel v1,zero,0x001dc2f4 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001dc2f0 */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));goto L_001dc2f4;}}
L_001dc2f4:;
/* 001dc2f4: sw a1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
/* 001dc2f8: move a3,zero */ set(7,cpu(0));
/* 001dc2fc: sw v1,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001dc300: addiu t1,a1,0x8 */ set(9,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 001dc304: sh s0,0x8(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(16));
/* 001dc308: addiu t0,a1,0xc */ set(8,sx((uint32_t)cpu(5)+UINT32_C(0x0000000c)));
/* 001dc30c: sh s1,0xa(a1) */ sh(ea(5,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(17));
/* 001dc310: li t2,0x8 */ set(10,sx(UINT32_C(0x00000008)));
/* 001dc314: sw s2,0x14(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 001dc318: li a2,0x20 */ set(6,sx(UINT32_C(0x00000020)));
/* 001dc31c: sw s3,0x18(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(19));
/* 001dc320: sw s4,0x1c(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(20));
/* 001dc324: sw zero,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001dc328: sw zero,0x10(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 001dc32c: nop  */ 
L_001dc330:;
/* 001dc330: addu v0,a1,a2 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(6)));
/* 001dc334: addu v1,t1,a2 */ set(3,sx((uint32_t)cpu(9)+(uint32_t)cpu(6)));
/* 001dc338: addu a0,t0,a2 */ set(4,sx((uint32_t)cpu(8)+(uint32_t)cpu(6)));
/* 001dc33c: addiu a2,a2,0x10 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000010)));
/* 001dc340: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 001dc344: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001dc348: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001dc34c: bne a3,t2,0x001dc330 */ {int taken=(cpu(7)!=cpu(10));/* delay 001dc350 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));if(taken){goto L_001dc330;}}
/* 001dc354: andi v0,s5,0x1 */ set(2,cpu(21)&UINT32_C(0x00000001));
/* 001dc358: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dc35c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001dc360: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 001dc364: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 001dc368: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 001dc36c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc370: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc374: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc378: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc37c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc380: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dc384: sb v0,0xc(a1) */ sb(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(2));
/* 001dc388: swc1 f1,0xb0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x000000b0)),f[1]);
/* 001dc38c: swc1 f0,0xac(a1) */ sw(ea(5,(int32_t)UINT32_C(0x000000ac)),f[0]);
/* 001dc390: sw zero,0xa0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x000000a0)),(uint32_t)cpu(0));
/* 001dc394: sw zero,0xa4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x000000a4)),(uint32_t)cpu(0));
/* 001dc398: sw zero,0xa8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x000000a8)),(uint32_t)cpu(0));
/* 001dc39c: jr ra */ {uint64_t target=cpu(31);/* delay 001dc3a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DC290(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);
body_001dc290();
}
static void body_001dc3a8(void){
nocturneEffectAxisNoteEntry(0x001dc3a8u);
uint64_t incoming=cpu(31);
/* 001dc3a8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001dc3ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc3b0: move s0,a0 */ set(16,cpu(4));
/* 001dc3b4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc3b8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc3bc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc3c0: beq s0,zero,0x001dc4a0 */ {int taken=(cpu(16)==cpu(0));/* delay 001dc3c4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_001dc4a0;}}
/* 001dc3c8: lw a0,0x4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001dc3cc: bne a0,zero,0x001dc3f0 */ {int taken=(cpu(4)!=cpu(0));/* delay 001dc3d0 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001dc3f0;}}
/* 001dc3d4: lhu v0,0x8(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000008))));
/* 001dc3d8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001dc3dc: lui at,0x33 */ set(1,sx(UINT32_C(0x00330000)));
/* 001dc3e0: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 001dc3e4: sw v1,-0x3ba8(at) */ sw(ea(1,(int32_t)UINT32_C(0xffffc458)),(uint32_t)cpu(3));
/* 001dc3e8: b 0x001dc3f4 */ /* delay 001dc3ec */ goto L_001dc3f4;
L_001dc3f0:;
/* 001dc3f0: sw v1,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
L_001dc3f4:;
/* 001dc3f4: bnel v1,zero,0x001dc3fc */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001dc3f8 */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));goto L_001dc3fc;}}
L_001dc3fc:;
/* 001dc3fc: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 001dc400: lbu s1,0xc(s0) */ set(17,byte(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 001dc404: beq a0,zero,0x001dc424 */ {int taken=(cpu(4)==cpu(0));/* delay 001dc408 */ sb(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(0));if(taken){goto L_001dc424;}}
/* 001dc40c: nop  */ 
L_001dc410:;
/* 001dc410: jal 0x001dd220 */ set(31,0x001dc418u);/* delay 001dc414 */ body_001dd220();
/* 001dc418: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 001dc41c: bne v0,zero,0x001dc410 */ {int taken=(cpu(2)!=cpu(0));/* delay 001dc420 */ set(4,cpu(2));if(taken){goto L_001dc410;}}
L_001dc424:;
/* 001dc424: beq s1,zero,0x001dc470 */ {int taken=(cpu(17)==cpu(0));/* delay 001dc428 */ set(5,sx(UINT32_C(0x00000001)));if(taken){goto L_001dc470;}}
/* 001dc42c: lw a0,0x14(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001dc430: move s2,zero */ set(18,cpu(0));
/* 001dc434: jal 0x002b2a80 */ set(31,0x001dc43cu);/* delay 001dc438 */ set(19,sx(UINT32_C(0x00000008)));body_002b2a80();
/* 001dc43c: lw a0,0x1c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001dc440: jal 0x002a9650 */ set(31,0x001dc448u);/* delay 001dc444 */ set(17,sx((uint32_t)cpu(16)+UINT32_C(0x0000002c)));body_002a9650();
/* 001dc448: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001dc44c: nop  */ 
L_001dc450:;
/* 001dc450: addiu s1,s1,0x10 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));
/* 001dc454: beq v0,zero,0x001dc464 */ {int taken=(cpu(2)==cpu(0));/* delay 001dc458 */ set(4,cpu(2));if(taken){goto L_001dc464;}}
/* 001dc45c: jal 0x002a9558 */ set(31,0x001dc464u);/* delay 001dc460 */ body_002a9558();
L_001dc464:;
/* 001dc464: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 001dc468: bnel s2,s3,0x001dc450 */ {int taken=(cpu(18)!=cpu(19));if(taken){/* delay 001dc46c */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));goto L_001dc450;}}
L_001dc470:;
/* 001dc470: jal 0x001df480 */ set(31,0x001dc478u);/* delay 001dc474 */ lw(4,ea(16,(int32_t)UINT32_C(0x000000a8)));body_001df480();
/* 001dc478: jal 0x002a9558 */ set(31,0x001dc480u);/* delay 001dc47c */ lw(4,ea(16,(int32_t)UINT32_C(0x000000a0)));body_002a9558();
/* 001dc480: move a0,s0 */ set(4,cpu(16));
/* 001dc484: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc488: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc48c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc490: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc494: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc498: j 0x002a8bd8 */ /* delay 001dc49c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_002a8bd8();return;
L_001dc4a0:;
/* 001dc4a0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc4a4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc4a8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc4ac: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc4b0: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc4b4: jr ra */ {uint64_t target=cpu(31);/* delay 001dc4b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DC3A8(uint64_t a0){
set(4,a0);
body_001dc3a8();
}
static void body_001dc4c0(void){
nocturneEffectAxisNoteEntry(0x001dc4c0u);
uint64_t incoming=cpu(31);
/* 001dc4c0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dc4c4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc4c8: jal 0x001dc158 */ set(31,0x001dc4d0u);/* delay 001dc4cc */ body_001dc158();
/* 001dc4d0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc4d4: move a0,v0 */ set(4,cpu(2));
/* 001dc4d8: j 0x001dc3a8 */ /* delay 001dc4dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001dc3a8();return;
}
void ps2BattleActionModel_001DC4C0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_001dc4c0();
}
static uint64_t body_001dc550(void){
nocturneEffectAxisNoteEntry(0x001dc550u);
uint64_t incoming=cpu(31);
/* 001dc550: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dc554: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc558: move s1,a1 */ set(17,cpu(5));
/* 001dc55c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc560: move s2,a0 */ set(18,cpu(4));
/* 001dc564: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc568: sll v0,s1,0x4 */ set(2,sx((uint32_t)cpu(17)<<4));
/* 001dc56c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc570: addiu v0,v0,0x20 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 001dc574: lw v1,0xc(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 001dc578: lw a0,0x18(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 001dc57c: addu a1,v1,v0 */ set(5,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001dc580: move v1,a1 */ set(3,cpu(5));
/* 001dc584: lh s0,0x4(a1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000004))));
/* 001dc588: jal 0x002b3b88 */ set(31,0x001dc590u);/* delay 001dc58c */ lw(5,ea(3,(int32_t)UINT32_C(0x00000008)));set(2,sdfMotionCtrlrNew(cpu(4),cpu(5)));
/* 001dc590: sll v1,s0,0x2 */ set(3,sx((uint32_t)cpu(16)<<2));
/* 001dc594: move a0,v0 */ set(4,cpu(2));
/* 001dc598: addu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(18)));
/* 001dc59c: sh s1,0x28(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000028)),(uint16_t)cpu(17));
/* 001dc5a0: sw a0,0x20(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(4));
/* 001dc5a4: bne s0,zero,0x001dc5b0 */ {int taken=(cpu(16)!=cpu(0));/* delay 001dc5a8 */ sh(ea(4,(int32_t)UINT32_C(0x0000002a)),(uint16_t)cpu(16));if(taken){goto L_001dc5b0;}}
/* 001dc5ac: sw a0,0x1c(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(4));
L_001dc5b0:;
/* 001dc5b0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc5b4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc5b8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc5bc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc5c0: jr ra */ {uint64_t target=cpu(31);/* delay 001dc5c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DC550(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001dc550();
}
static void body_001dc5c8(void){
nocturneEffectAxisNoteEntry(0x001dc5c8u);
uint64_t incoming=cpu(31);
/* 001dc5c8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dc5cc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc5d0: lh v0,0x2a(a1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x0000002a))));
/* 001dc5d4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001dc5d8: addiu v0,v0,0x20 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 001dc5dc: addu v1,a0,v0 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001dc5e0: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001dc5e4: bne v0,a1,0x001dc5f0 */ {int taken=(cpu(2)!=cpu(5));/* delay 001dc5e8 */ set(4,cpu(5));if(taken){goto L_001dc5f0;}}
/* 001dc5ec: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
L_001dc5f0:;
/* 001dc5f0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc5f4: j 0x002b3c60 */ /* delay 001dc5f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);sdfMotionCtrlrFree(cpu(4));return;
}
void ps2BattleActionModel_001DC5C8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_001dc5c8();
}
static void body_001dc600(void){
nocturneEffectAxisNoteEntry(0x001dc600u);
uint64_t incoming=cpu(31);
/* 001dc600: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dc604: move v1,a1 */ set(3,cpu(5));
/* 001dc608: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc60c: lw v0,0x18(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001dc610: lw a1,0x14(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000014)));
/* 001dc614: nop  */ 
L_001dc618:;
/* 001dc618: beq a1,zero,0x001dc648 */ {int taken=(cpu(5)==cpu(0));/* delay 001dc61c */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001dc648;}}
/* 001dc620: lh v0,0x28(a1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000028))));
/* 001dc624: nop  */ 
/* 001dc628: nop  */ 
/* 001dc62c: nop  */ 
/* 001dc630: nop  */ 
/* 001dc634: bnel v0,v1,0x001dc618 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 001dc638 */ lw(5,ea(5,(int32_t)UINT32_C(0x00000000)));goto L_001dc618;}}
/* 001dc63c: jal 0x001dc5c8 */ set(31,0x001dc644u);/* delay 001dc640 */ body_001dc5c8();
/* 001dc644: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001dc648:;
/* 001dc648: jr ra */ {uint64_t target=cpu(31);/* delay 001dc64c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DC600(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_001dc600();
}
static void body_001dc650(void){
nocturneEffectAxisNoteEntry(0x001dc650u);
uint64_t incoming=cpu(31);
/* 001dc650: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001dc654: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc658: move s1,a0 */ set(17,cpu(4));
/* 001dc65c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc660: move s2,a1 */ set(18,cpu(5));
/* 001dc664: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc668: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc66c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc670: beq s1,zero,0x001dc6f4 */ {int taken=(cpu(17)==cpu(0));/* delay 001dc674 */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_001dc6f4;}}
/* 001dc678: sll s3,s2,0x4 */ set(19,sx((uint32_t)cpu(18)<<4));
/* 001dc67c: addiu s4,s1,0x8 */ set(20,sx((uint32_t)cpu(17)+UINT32_C(0x00000008)));
/* 001dc680: addu v0,s3,s4 */ set(2,sx((uint32_t)cpu(19)+(uint32_t)cpu(20)));
/* 001dc684: lw v1,0x20(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 001dc688: beq v1,zero,0x001dc6f8 */ {int taken=(cpu(3)==cpu(0));/* delay 001dc68c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001dc6f8;}}
/* 001dc690: lw s0,0x10(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001dc694: beql s0,zero,0x001dc6b8 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 001dc698 */ set(2,byte(ea(17,(int32_t)UINT32_C(0x0000000c))));goto L_001dc6b8;}}
/* 001dc69c: move a0,s0 */ set(4,cpu(16));
L_001dc6a0:;
/* 001dc6a0: jal 0x001dc600 */ set(31,0x001dc6a8u);/* delay 001dc6a4 */ set(5,cpu(18));body_001dc600();
/* 001dc6a8: lw s0,0x4(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001dc6ac: bne s0,zero,0x001dc6a0 */ {int taken=(cpu(16)!=cpu(0));/* delay 001dc6b0 */ set(4,cpu(16));if(taken){goto L_001dc6a0;}}
/* 001dc6b4: lbu v0,0xc(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x0000000c))));
L_001dc6b8:;
/* 001dc6b8: beq v0,zero,0x001dc6e0 */ {int taken=(cpu(2)==cpu(0));/* delay 001dc6bc */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0x0000000c)));if(taken){goto L_001dc6e0;}}
/* 001dc6c0: addu v0,s3,s0 */ set(2,sx((uint32_t)cpu(19)+(uint32_t)cpu(16)));
/* 001dc6c4: lw a0,0x20(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 001dc6c8: beql a0,zero,0x001dc6e4 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 001dc6cc */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0x00000020)));goto L_001dc6e4;}}
/* 001dc6d0: jal 0x002a9558 */ set(31,0x001dc6d8u);/* delay 001dc6d4 */ body_002a9558();
/* 001dc6d8: b 0x001dc6e4 */ /* delay 001dc6dc */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0x00000020)));goto L_001dc6e4;
L_001dc6e0:;
/* 001dc6e0: addiu v0,s3,0x20 */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0x00000020)));
L_001dc6e4:;
/* 001dc6e4: addu v1,s0,v0 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001dc6e8: addu v0,s4,v0 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 001dc6ec: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001dc6f0: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
L_001dc6f4:;
/* 001dc6f4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001dc6f8:;
/* 001dc6f8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc6fc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc700: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc704: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc708: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dc70c: jr ra */ {uint64_t target=cpu(31);/* delay 001dc710 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DC650(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_001dc650();
}
static void body_001dc748(void){
nocturneEffectAxisNoteEntry(0x001dc748u);
uint64_t incoming=cpu(31);
/* 001dc748: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001dc74c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc750: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc754: move s1,t0 */ set(17,cpu(8));
/* 001dc758: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc75c: move s2,a2 */ set(18,cpu(6));
/* 001dc760: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc764: move s3,t1 */ set(19,cpu(9));
/* 001dc768: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc76c: move s4,t2 */ set(20,cpu(10));
/* 001dc770: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dc774: move s5,t3 */ set(21,cpu(11));
/* 001dc778: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dc77c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001dc780: jal 0x001dc158 */ set(31,0x001dc788u);/* delay 001dc784 */ set(22,cpu(7));body_001dc158();
/* 001dc788: move s0,v0 */ set(16,cpu(2));
/* 001dc78c: move a1,s1 */ set(5,cpu(17));
/* 001dc790: sll s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)<<4));
/* 001dc794: move a0,s0 */ set(4,cpu(16));
/* 001dc798: jal 0x001dc650 */ set(31,0x001dc7a0u);/* delay 001dc79c */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(17)));body_001dc650();
/* 001dc7a0: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
/* 001dc7a4: andi v1,s2,0x200 */ set(3,cpu(18)&UINT32_C(0x00000200));
/* 001dc7a8: andi s2,s2,0x100 */ set(18,cpu(18)&UINT32_C(0x00000100));
/* 001dc7ac: sh s3,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(19));
/* 001dc7b0: sh s6,0x6(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(22));
/* 001dc7b4: sw s4,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));
/* 001dc7b8: sw s5,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(21));
/* 001dc7bc: beq s2,zero,0x001dc7cc */ {int taken=(cpu(18)==cpu(0));/* delay 001dc7c0 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));if(taken){goto L_001dc7cc;}}
/* 001dc7c4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001dc7c8: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_001dc7cc:;
/* 001dc7cc: beql v1,zero,0x001dc7e4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 001dc7d0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001dc7e4;}}
/* 001dc7d4: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001dc7d8: ori v0,v0,0x2 */ set(2,cpu(2)|UINT32_C(0x00000002));
/* 001dc7dc: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001dc7e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001dc7e4:;
/* 001dc7e4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc7e8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc7ec: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc7f0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc7f4: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dc7f8: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dc7fc: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001dc800: jr ra */ {uint64_t target=cpu(31);/* delay 001dc804 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DC748(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);set(10,a6);set(11,a7);
body_001dc748();
}
static void body_001dc808(void){
nocturneEffectAxisNoteEntry(0x001dc808u);
uint64_t incoming=cpu(31);
/* 001dc808: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001dc80c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc810: move s0,a2 */ set(16,cpu(6));
/* 001dc814: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc818: move s1,a3 */ set(17,cpu(7));
/* 001dc81c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc820: move s2,a1 */ set(18,cpu(5));
/* 001dc824: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc828: move s3,a0 */ set(19,cpu(4));
/* 001dc82c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc830: lw a3,0x0(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001dc834: lw t0,0x4(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 001dc838: jal 0x001dc290 */ set(31,0x001dc840u);/* delay 001dc83c */ lw(9,ea(17,(int32_t)UINT32_C(0x00000008)));body_001dc290();
/* 001dc840: move a0,s3 */ set(4,cpu(19));
/* 001dc844: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 001dc848: move a2,s0 */ set(6,cpu(16));
/* 001dc84c: move a1,s2 */ set(5,cpu(18));
/* 001dc850: move a3,zero */ set(7,cpu(0));
/* 001dc854: move t2,v0 */ set(10,cpu(2));
/* 001dc858: move t0,zero */ set(8,cpu(0));
/* 001dc85c: beq v0,zero,0x001dc86c */ {int taken=(cpu(2)==cpu(0));/* delay 001dc860 */ set(9,cpu(0));if(taken){goto L_001dc86c;}}
/* 001dc864: jal 0x001dc748 */ set(31,0x001dc86cu);/* delay 001dc868 */ lw(11,ea(17,(int32_t)UINT32_C(0x00000010)));body_001dc748();
L_001dc86c:;
/* 001dc86c: lw v0,0x14(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001dc870: beq v0,zero,0x001dc898 */ {int taken=(cpu(2)==cpu(0));/* delay 001dc874 */ set(4,cpu(19));if(taken){goto L_001dc898;}}
/* 001dc878: jal 0x001dc158 */ set(31,0x001dc880u);/* delay 001dc87c */ set(5,cpu(18));body_001dc158();
/* 001dc880: lw a1,0x14(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001dc884: lw v1,0x1c(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 001dc888: lw a0,0x18(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 001dc88c: sw v1,0xa8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x000000a8)),(uint32_t)cpu(3));
/* 001dc890: sw a1,0xa4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x000000a4)),(uint32_t)cpu(5));
/* 001dc894: sw a0,0xa0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x000000a0)),(uint32_t)cpu(4));
L_001dc898:;
/* 001dc898: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc89c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc8a0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc8a4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dc8a8: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dc8ac: jr ra */ {uint64_t target=cpu(31);/* delay 001dc8b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DC808(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_001dc808();
}
static uint64_t body_001dc8b8(void){
nocturneEffectAxisNoteEntry(0x001dc8b8u);
uint64_t incoming=cpu(31);
/* 001dc8b8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dc8bc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc8c0: move s0,a0 */ set(16,cpu(4));
/* 001dc8c4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc8c8: move s1,a1 */ set(17,cpu(5));
/* 001dc8cc: b 0x001dc8e0 */ /* delay 001dc8d0 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_001dc8e0;
L_001dc8d8:;
/* 001dc8d8: jal 0x002976c0 */ set(31,0x001dc8e0u);/* delay 001dc8dc */ set(2,ps2ResourcePump());
L_001dc8e0:;
/* 001dc8e0: move a0,s0 */ set(4,cpu(16));
/* 001dc8e4: jal 0x001dc188 */ set(31,0x001dc8ecu);/* delay 001dc8e8 */ set(5,cpu(17));body_001dc188();
/* 001dc8ec: bne v0,zero,0x001dc8d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001dc8f0 */ set(4,cpu(16));if(taken){goto L_001dc8d8;}}
/* 001dc8f4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc8f8: move a1,s1 */ set(5,cpu(17));
/* 001dc8fc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc900: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc904: j 0x001dc158 */ /* delay 001dc908 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_001dc158();return cpu(2);
}
uint64_t ps2BattleActionModel_001DC8B8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001dc8b8();
}
static uint64_t body_001dca88(void){
nocturneEffectAxisNoteEntry(0x001dca88u);
uint64_t incoming=cpu(31);
/* 001dca88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dca8c: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 001dca90: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dca94: addiu t0,v0,-0x9d8 */ set(8,sx((uint32_t)cpu(2)+UINT32_C(0xfffff628)));
/* 001dca98: ldl v1,0x7(t0) */ loadPartial(3,ea(8,(int32_t)UINT32_C(0x00000007)),1);
/* 001dca9c: ldr v1,0x0(t0) */ loadPartial(3,ea(8,(int32_t)UINT32_C(0x00000000)),0);
/* 001dcaa0: sdl v1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),3,1);
/* 001dcaa4: sdr v1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),3,0);
/* 001dcaa8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dcaac: j 0x002d57f8 */ /* delay 001dcab0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);{uint64_t base=cpu(4);char *start=(char *)at((uint32_t)base);char *p=ps2Strcat(start,(const char *)at((uint32_t)cpu(5)));set(2,p?sx((uint32_t)base+(uint32_t)(p-start)):0);}return cpu(2);
}
uint64_t ps2BattleActionModel_001DCA88(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001dca88();
}
static uint64_t body_001dcab8(void){
nocturneEffectAxisNoteEntry(0x001dcab8u);
uint64_t incoming=cpu(31);
/* 001dcab8: addiu sp,sp,-0xb0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff50)));
/* 001dcabc: sd s2,0x90(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 001dcac0: move s2,a0 */ set(18,cpu(4));
/* 001dcac4: lw a0,-0x2274(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdd8c)));
/* 001dcac8: sd s3,0x98(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 001dcacc: move s3,a1 */ set(19,cpu(5));
/* 001dcad0: sd s0,0x80(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 001dcad4: sd s4,0xa0(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 001dcad8: sd s1,0x88(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 001dcadc: sd ra,0xa8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 001dcae0: jal 0x002dbee0 */ set(31,0x001dcae8u);/* delay 001dcae4 */ set(20,cpu(6));waitSemaphore();
/* 001dcae8: move a0,s2 */ set(4,cpu(18));
/* 001dcaec: jal 0x001dc158 */ set(31,0x001dcaf4u);/* delay 001dcaf0 */ set(5,cpu(19));body_001dc158();
/* 001dcaf4: move s0,v0 */ set(16,cpu(2));
/* 001dcaf8: beql s0,zero,0x001dcb10 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 001dcafc */ set(4,cpu(18));goto L_001dcb10;}}
/* 001dcb00: jal 0x002dbec0 */ set(31,0x001dcb08u);/* delay 001dcb04 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdd8c)));signalSemaphore();
/* 001dcb08: b 0x001dccc4 */ /* delay 001dcb0c */ set(2,cpu(16));goto L_001dccc4;
L_001dcb10:;
/* 001dcb10: jal 0x001dc188 */ set(31,0x001dcb18u);/* delay 001dcb14 */ set(5,cpu(19));body_001dc188();
/* 001dcb18: beql v0,zero,0x001dcb38 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001dcb1c */ set(2,sx((uint32_t)cpu(18)<<3));goto L_001dcb38;}}
/* 001dcb20: jal 0x002dbec0 */ set(31,0x001dcb28u);/* delay 001dcb24 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdd8c)));signalSemaphore();
/* 001dcb28: bnel s4,zero,0x001dccac */ {int taken=(cpu(20)!=cpu(0));if(taken){/* delay 001dcb2c */ set(4,cpu(18));goto L_001dccac;}}
/* 001dcb30: b 0x001dccc4 */ /* delay 001dcb34 */ set(2,sx(UINT32_C(0xffffffff)));goto L_001dccc4;
L_001dcb38:;
/* 001dcb38: sll a0,s3,0x3 */ set(4,sx((uint32_t)cpu(19)<<3));
/* 001dcb3c: lui v1,0x33 */ set(3,sx(UINT32_C(0x00330000)));
/* 001dcb40: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001dcb44: lw v1,-0x3be0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffc420)));
/* 001dcb48: li a1,0x2e */ set(5,sx(UINT32_C(0x0000002e)));
/* 001dcb4c: move s0,zero */ set(16,cpu(0));
/* 001dcb50: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001dcb54: lhu a2,0x2(v1) */ set(6,half(ea(3,(int32_t)UINT32_C(0x00000002))));
/* 001dcb58: lhu a0,0x0(v1) */ set(4,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001dcb5c: sll v0,a2,0x1 */ set(2,sx((uint32_t)cpu(6)<<1));
/* 001dcb60: sll a0,a0,0x3 */ set(4,sx((uint32_t)cpu(4)<<3));
/* 001dcb64: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 001dcb68: lui v1,0x33 */ set(3,sx(UINT32_C(0x00330000)));
/* 001dcb6c: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001dcb70: lw v1,-0x57e0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffa820)));
/* 001dcb74: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001dcb78: addu s1,v1,v0 */ set(17,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001dcb7c: jal 0x002d61c0 */ set(31,0x001dcb84u);/* delay 001dcb80 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000004)));{uint64_t base=cpu(4);const char *start=(const char *)at((uint32_t)base);char *p=ps2Strrchr(start,(int32_t)(uint32_t)cpu(5));set(2,p?sx((uint32_t)base+(uint32_t)(p-start)):0);}
/* 001dcb84: beq v0,zero,0x001dcb9c */ {int taken=(cpu(2)==cpu(0));/* delay 001dcb88 */ set(5,sx(UINT32_C(0x00550000)));if(taken){goto L_001dcb9c;}}
/* 001dcb8c: move a0,v0 */ set(4,cpu(2));
/* 001dcb90: jal 0x002d5720 */ set(31,0x001dcb98u);/* delay 001dcb94 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xfffff630)));set(2,sx((uint32_t)ps2Strcasecmp((const char *)at((uint32_t)cpu(4)),(const char *)at((uint32_t)cpu(5)))));
/* 001dcb98: sltiu s0,v0,0x1 */ set(16,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_001dcb9c:;
/* 001dcb9c: move a0,s2 */ set(4,cpu(18));
/* 001dcba0: jal 0x001dc1d8 */ set(31,0x001dcba8u);/* delay 001dcba4 */ set(5,cpu(19));body_001dc1d8();
/* 001dcba8: jal 0x002dbec0 */ set(31,0x001dcbb0u);/* delay 001dcbac */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdd8c)));signalSemaphore();
/* 001dcbb0: beq s0,zero,0x001dcbf0 */ {int taken=(cpu(16)==cpu(0));/* delay 001dcbb4 */ if(taken){goto L_001dcbf0;}}
/* 001dcbb8: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 001dcbbc: jal 0x001dca88 */ set(31,0x001dcbc4u);/* delay 001dcbc0 */ set(4,cpu(29));body_001dca88();
/* 001dcbc4: lui t0,0x2b */ set(8,sx(UINT32_C(0x002b0000)));
/* 001dcbc8: addiu t0,t0,-0x7f88 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0xffff8078)));
/* 001dcbcc: move a0,s2 */ set(4,cpu(18));
/* 001dcbd0: move a1,s3 */ set(5,cpu(19));
/* 001dcbd4: li a2,0x101 */ set(6,sx(UINT32_C(0x00000101)));
/* 001dcbd8: move a3,sp */ set(7,cpu(29));
/* 001dcbdc: jal 0x001de220 */ set(31,0x001dcbe4u);/* delay 001dcbe0 */ set(9,cpu(0));set(2,ps2BattleAction_001DE220(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9)));
/* 001dcbe4: b 0x001dcca4 */ /* delay 001dcbe8 */ goto L_001dcca4;
L_001dcbf0:;
/* 001dcbf0: jal 0x002a8ba8 */ set(31,0x001dcbf8u);/* delay 001dcbf4 */ set(4,sx(UINT32_C(0x0000002c)));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 001dcbf8: lw v1,0x8(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 001dcbfc: move s0,v0 */ set(16,cpu(2));
/* 001dcc00: li v0,0x101 */ set(2,sx(UINT32_C(0x00000101)));
/* 001dcc04: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001dcc08: sh s2,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(18));
/* 001dcc0c: beq v1,zero,0x001dcc18 */ {int taken=(cpu(3)==cpu(0));/* delay 001dcc10 */ sh(ea(16,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(19));if(taken){goto L_001dcc18;}}
/* 001dcc14: sb v0,0x6(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(2));
L_001dcc18:;
/* 001dcc18: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001dcc1c: beq v0,zero,0x001dcc4c */ {int taken=(cpu(2)==cpu(0));/* delay 001dcc20 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_001dcc4c;}}
/* 001dcc24: move a0,sp */ set(4,cpu(29));
/* 001dcc28: sb v0,0x4(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(2));
/* 001dcc2c: jal 0x001dca88 */ set(31,0x001dcc34u);/* delay 001dcc30 */ lw(5,ea(17,(int32_t)UINT32_C(0x00000000)));body_001dca88();
/* 001dcc34: lui a2,0x1e */ set(6,sx(UINT32_C(0x001e0000)));
/* 001dcc38: addiu a2,a2,-0x3698 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffc968)));
/* 001dcc3c: move a0,sp */ set(4,cpu(29));
/* 001dcc40: move a1,zero */ set(5,cpu(0));
/* 001dcc44: jal 0x002969f0 */ set(31,0x001dcc4cu);/* delay 001dcc48 */ set(7,cpu(16));set(2,ps2ResourceReadRequestCreate(cpu(4),cpu(5),cpu(6),cpu(7)));
L_001dcc4c:;
/* 001dcc4c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001dcc50: move a0,sp */ set(4,cpu(29));
/* 001dcc54: sb v0,0x5(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(2));
/* 001dcc58: jal 0x001dca88 */ set(31,0x001dcc60u);/* delay 001dcc5c */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));body_001dca88();
/* 001dcc60: lui a2,0x1e */ set(6,sx(UINT32_C(0x001e0000)));
/* 001dcc64: move a1,zero */ set(5,cpu(0));
/* 001dcc68: addiu a2,a2,-0x3648 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffc9b8)));
/* 001dcc6c: move a0,sp */ set(4,cpu(29));
/* 001dcc70: jal 0x002969f0 */ set(31,0x001dcc78u);/* delay 001dcc74 */ set(7,cpu(16));set(2,ps2ResourceReadRequestCreate(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 001dcc78: lw a1,0x8(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 001dcc7c: beq a1,zero,0x001dcca4 */ {int taken=(cpu(5)==cpu(0));/* delay 001dcc80 */ if(taken){goto L_001dcca4;}}
/* 001dcc84: jal 0x001dca88 */ set(31,0x001dcc8cu);/* delay 001dcc88 */ set(4,cpu(29));body_001dca88();
/* 001dcc8c: lui a2,0x1e */ set(6,sx(UINT32_C(0x001e0000)));
/* 001dcc90: addiu a2,a2,-0x35d0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffca30)));
/* 001dcc94: move a3,s0 */ set(7,cpu(16));
/* 001dcc98: move a0,sp */ set(4,cpu(29));
/* 001dcc9c: jal 0x002969f0 */ set(31,0x001dcca4u);/* delay 001dcca0 */ set(5,cpu(0));set(2,ps2ResourceReadRequestCreate(cpu(4),cpu(5),cpu(6),cpu(7)));
L_001dcca4:;
/* 001dcca4: beq s4,zero,0x001dccc0 */ {int taken=(cpu(20)==cpu(0));/* delay 001dcca8 */ set(4,cpu(18));if(taken){goto L_001dccc0;}}
L_001dccac:;
/* 001dccac: jal 0x001dc8b8 */ set(31,0x001dccb4u);/* delay 001dccb0 */ set(5,cpu(19));body_001dc8b8();
/* 001dccb4: b 0x001dccc8 */ /* delay 001dccb8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000080)));goto L_001dccc8;
L_001dccc0:;
/* 001dccc0: move v0,zero */ set(2,cpu(0));
L_001dccc4:;
/* 001dccc4: ld s0,0x80(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000080)));
L_001dccc8:;
/* 001dccc8: ld s1,0x88(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 001dcccc: ld s2,0x90(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 001dccd0: ld s3,0x98(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 001dccd4: ld s4,0xa0(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 001dccd8: ld ra,0xa8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 001dccdc: jr ra */ {uint64_t target=cpu(31);/* delay 001dcce0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000b0)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DCAB8(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_001dcab8();
}
static uint64_t body_001dcce8(void){
nocturneEffectAxisNoteEntry(0x001dcce8u);
uint64_t incoming=cpu(31);
/* 001dcce8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dccec: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 001dccf0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dccf4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dccf8: j 0x001dcab8 */ /* delay 001dccfc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001dcab8();return cpu(2);
}
uint64_t ps2BattleActionModel_001DCCE8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001dcce8();
}
static void body_001dcd00(void){
nocturneEffectAxisNoteEntry(0x001dcd00u);
uint64_t incoming=cpu(31);
/* 001dcd00: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dcd04: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dcd08: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001dcd0c: beq v1,zero,0x001dcd18 */ {int taken=(cpu(3)==cpu(0));/* delay 001dcd10 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_001dcd18;}}
/* 001dcd14: sw v0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_001dcd18:;
/* 001dcd18: beq v0,zero,0x001dcd28 */ {int taken=(cpu(2)==cpu(0));/* delay 001dcd1c */ if(taken){goto L_001dcd28;}}
/* 001dcd20: b 0x001dcd50 */ /* delay 001dcd24 */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));goto L_001dcd50;
L_001dcd28:;
/* 001dcd28: beq v1,zero,0x001dcd38 */ {int taken=(cpu(3)==cpu(0));/* delay 001dcd2c */ lw(4,ea(4,(int32_t)UINT32_C(0x0000000c)));if(taken){goto L_001dcd38;}}
/* 001dcd30: b 0x001dcd50 */ /* delay 001dcd34 */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));goto L_001dcd50;
L_001dcd38:;
/* 001dcd38: lbu v0,0xc(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x0000000c))));
/* 001dcd3c: beq v0,zero,0x001dcd50 */ {int taken=(cpu(2)==cpu(0));/* delay 001dcd40 */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));if(taken){goto L_001dcd50;}}
/* 001dcd44: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dcd48: j 0x001dc3a8 */ /* delay 001dcd4c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001dc3a8();return;
L_001dcd50:;
/* 001dcd50: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dcd54: jr ra */ {uint64_t target=cpu(31);/* delay 001dcd58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DCD00(uint64_t a0){
set(4,a0);
body_001dcd00();
}
static void body_001dcd60(void){
nocturneEffectAxisNoteEntry(0x001dcd60u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001dcd60: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 001dcd64: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dcd68: move s0,a2 */ set(16,cpu(6));
/* 001dcd6c: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dcd70: move s1,a0 */ set(17,cpu(4));
/* 001dcd74: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dcd78: move s2,a1 */ set(18,cpu(5));
/* 001dcd7c: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001dcd80: move s3,t0 */ set(19,cpu(8));
/* 001dcd84: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001dcd88: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001dcd8c: jal 0x001dce88 */ set(31,0x001dcd94u);/* delay 001dcd90 */ set(20,cpu(7));body_001dce88();
/* 001dcd94: blez s0,0x001dce64 */ {int taken=((int64_t)cpu(16)<=0);/* delay 001dcd98 */ set(4,sx(UINT32_C(0x00000030)));if(taken){goto L_001dce64;}}
/* 001dcd9c: jal 0x002a8ba8 */ set(31,0x001dcda4u);/* delay 001dcda0 */ set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 001dcda4: mult v1,s0,s2 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(16)*(int64_t)(int32_t)(uint32_t)cpu(18));EE_MAGATUHI_MULT_STATE(product);set(3,sx((uint32_t)product));}
/* 001dcda8: lui at,0x3c00 */ set(1,sx(UINT32_C(0x3c000000)));
/* 001dcdac: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 001dcdb0: move a0,v0 */ set(4,cpu(2));
/* 001dcdb4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001dcdb8: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 001dcdbc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001dcdc0: sh v0,0xa(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(2));
/* 001dcdc4: mtc1 v1,f2 */ f[2]=(uint32_t)cpu(3);
/* 001dcdc8: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 001dcdcc: sw v1,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 001dcdd0: sw a0,0x30(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(4));
/* 001dcdd4: sh s0,0x4(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(16));
/* 001dcdd8: sw s3,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(19));
/* 001dcddc: sh s0,0x6(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(16));
/* 001dcde0: nop  */ 
/* 001dcde4: nop  */ 
/* 001dcde8: div.S f1,f1,f2 */ f[1]=divs(f[1],f[2]);
/* 001dcdec: sh s2,0x8(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(18));
/* 001dcdf0: mfc1 v1,f0 */ set(3,sx(f[0]));
/* 001dcdf4: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dcdf8: pextlb v0,zero,v0 */ pextlb(2,0,2);
/* 001dcdfc: pextlh v0,zero,v0 */ pextlh(2,0,2);
/* 001dce00: qmtc2 v0,vf10 */ modelQmt(10,2);
/* 001dce04: vitof0.xyzw vf10,vf10 */ itof(10,10);
/* 001dce08: qmtc2 v1,vf2 */ modelQmt(2,3);
/* 001dce0c: vmulx.xyzw vf10,vf10,vf2 */ modelMul(10,10,2);
/* 001dce10: addiu v1,a0,0x10 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
/* 001dce14: sqc2 vf10,0x0(v1) */ storeVu(10,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001dce18: vmove.xyzw vf11,vf10 */ moveVu(11,10);
/* 001dce1c: lui at,0x3c00 */ set(1,sx(UINT32_C(0x3c000000)));
/* 001dce20: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 001dce24: sw s4,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(20));
/* 001dce28: addiu v1,sp,0x10 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 001dce2c: mfc1 a1,f0 */ set(5,sx(f[0]));
/* 001dce30: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001dce34: pextlb v0,zero,v0 */ pextlb(2,0,2);
/* 001dce38: pextlh v0,zero,v0 */ pextlh(2,0,2);
/* 001dce3c: qmtc2 v0,vf10 */ modelQmt(10,2);
/* 001dce40: vitof0.xyzw vf10,vf10 */ itof(10,10);
/* 001dce44: qmtc2 a1,vf2 */ modelQmt(2,5);
/* 001dce48: vmulx.xyzw vf10,vf10,vf2 */ modelMul(10,10,2);
/* 001dce4c: vsub.xyzw vf10,vf10,vf11 */ modelSub(10,10,11);
/* 001dce50: mfc1 v0,f1 */ set(2,sx(f[1]));
/* 001dce54: qmtc2 v0,vf2 */ modelQmt(2,2);
/* 001dce58: vmulx.xyzw vf10,vf10,vf2 */ modelMul(10,10,2);
/* 001dce5c: addiu a0,a0,0x20 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 001dce60: sqc2 vf10,0x0(a0) */ storeVu(10,ea(4,(int32_t)UINT32_C(0x00000000)));
L_001dce64:;
/* 001dce64: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dce68: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dce6c: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dce70: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001dce74: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001dce78: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001dce7c: jr ra */ {uint64_t target=cpu(31);/* delay 001dce80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DCD60(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
body_001dcd60();
}
static void body_001dce88(void){
nocturneEffectAxisNoteEntry(0x001dce88u);
uint64_t incoming=cpu(31);
/* 001dce88: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001dce8c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dce90: move s3,a0 */ set(19,cpu(4));
/* 001dce94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dce98: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dce9c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dcea0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dcea4: lw s2,0x30(s3) */ lw(18,ea(19,(int32_t)UINT32_C(0x00000030)));
/* 001dcea8: beq s2,zero,0x001dcef4 */ {int taken=(cpu(18)==cpu(0));/* delay 001dceac */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001dcef4;}}
/* 001dceb0: lw s1,0x0(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 001dceb4: beq s1,zero,0x001dcee4 */ {int taken=(cpu(17)==cpu(0));/* delay 001dceb8 */ if(taken){goto L_001dcee4;}}
/* 001dcebc: move s0,s1 */ set(16,cpu(17));
L_001dcec0:;
/* 001dcec0: lw s1,0x0(s1) */ lw(17,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001dcec4: lw a0,0x4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001dcec8: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001dcecc: jal 0x002b0648 */ set(31,0x001dced4u);/* delay 001dced0 */ set(6,sx(UINT32_C(0x00000001)));body_002b0648();
/* 001dced4: jal 0x002a8bd8 */ set(31,0x001dcedcu);/* delay 001dced8 */ set(4,cpu(16));body_002a8bd8();
/* 001dcedc: bnel s1,zero,0x001dcec0 */ {int taken=(cpu(17)!=cpu(0));if(taken){/* delay 001dcee0 */ set(16,cpu(17));goto L_001dcec0;}}
L_001dcee4:;
/* 001dcee4: jal 0x002a8bd8 */ set(31,0x001dceecu);/* delay 001dcee8 */ set(4,cpu(18));body_002a8bd8();
/* 001dceec: sw zero,0x30(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));
/* 001dcef0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001dcef4:;
/* 001dcef4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dcef8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dcefc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dcf00: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dcf04: jr ra */ {uint64_t target=cpu(31);/* delay 001dcf08 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DCE88(uint64_t a0){
set(4,a0);
body_001dce88();
}
static uint64_t body_001dd0d0(void){
nocturneEffectAxisNoteEntry(0x001dd0d0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001dd0d0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 001dd0d4: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dd0d8: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dd0dc: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dd0e0: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dd0e4: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dd0e8: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001dd0ec: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001dd0f0: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001dd0f4: jal 0x001dcce8 */ set(31,0x001dd0fcu);/* delay 001dd0f8 */ body_001dcce8();
/* 001dd0fc: li a0,0x38 */ set(4,sx(UINT32_C(0x00000038)));
/* 001dd100: jal 0x002a8ba8 */ set(31,0x001dd108u);/* delay 001dd104 */ set(19,cpu(2));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 001dd108: move s1,v0 */ set(17,cpu(2));
/* 001dd10c: lw v0,0x10(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 001dd110: sw s3,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(19));
/* 001dd114: beq v0,zero,0x001dd120 */ {int taken=(cpu(2)==cpu(0));/* delay 001dd118 */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_001dd120;}}
/* 001dd11c: sw s1,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));
L_001dd120:;
/* 001dd120: lw a0,0x14(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000014)));
/* 001dd124: jal 0x002b2bd0 */ set(31,0x001dd12cu);/* delay 001dd128 */ sw(ea(19,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(17));body_002b2bd0();
/* 001dd12c: lw a1,0x18(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000018)));
/* 001dd130: jal 0x002b1588 */ set(31,0x001dd138u);/* delay 001dd134 */ set(4,cpu(2));set(2,ps2EffectModelMake_002B1588(cpu(4),cpu(5)));
/* 001dd138: lwc1 f0,0xac(s3) */ f[0]=word(ea(19,(int32_t)UINT32_C(0x000000ac)));
/* 001dd13c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001dd140: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 001dd144: addiu v1,v0,0x70 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000070)));
/* 001dd148: swc1 f0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[0]);
/* 001dd14c: swc1 f1,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),f[1]);
/* 001dd150: sw v0,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 001dd154: swc1 f0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[0]);
/* 001dd158: swc1 f0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[0]);
/* 001dd15c: lq v0,0x0(sp) */ lq(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd160: sq v0,0x0(v1) */ sq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001dd164: lwc1 f0,0xb0(s3) */ f[0]=word(ea(19,(int32_t)UINT32_C(0x000000b0)));
/* 001dd168: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 001dd16c: sh v0,0x12(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000012)),(uint16_t)cpu(2));
/* 001dd170: move s2,zero */ set(18,cpu(0));
/* 001dd174: swc1 f0,0x34(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000034)),f[0]);
/* 001dd178: addiu s5,s3,0x8 */ set(21,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 001dd17c: sh v0,0x10(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000010)),(uint16_t)cpu(2));
/* 001dd180: li s6,0x8 */ set(22,sx(UINT32_C(0x00000008)));
/* 001dd184: li s4,0x20 */ set(20,sx(UINT32_C(0x00000020)));
L_001dd188:;
/* 001dd188: addu v0,s5,s4 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(20)));
/* 001dd18c: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001dd190: beq v1,zero,0x001dd1d0 */ {int taken=(cpu(3)==cpu(0));/* delay 001dd194 */ set(16,sx((uint32_t)cpu(19)+(uint32_t)cpu(20)));if(taken){goto L_001dd1d0;}}
/* 001dd198: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001dd19c: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 001dd1a0: beq v0,zero,0x001dd1d0 */ {int taken=(cpu(2)==cpu(0));/* delay 001dd1a4 */ set(5,cpu(18));if(taken){goto L_001dd1d0;}}
/* 001dd1a8: jal 0x001dc550 */ set(31,0x001dd1b0u);/* delay 001dd1ac */ set(4,cpu(17));body_001dc550();
/* 001dd1b0: blezl s2,0x001dd1d4 */ {int taken=((int64_t)cpu(18)<=0);if(taken){/* delay 001dd1b4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));goto L_001dd1d4;}}
/* 001dd1b8: lh v0,0x6(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 001dd1bc: bltz v0,0x001dd1d0 */ {int taken=((int64_t)cpu(2)<0);/* delay 001dd1c0 */ set(6,cpu(2));if(taken){goto L_001dd1d0;}}
/* 001dd1c4: move a1,s2 */ set(5,cpu(18));
/* 001dd1c8: jal 0x001dd538 */ set(31,0x001dd1d0u);/* delay 001dd1cc */ set(4,cpu(17));body_001dd538();
L_001dd1d0:;
/* 001dd1d0: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
L_001dd1d4:;
/* 001dd1d4: bne s2,s6,0x001dd188 */ {int taken=(cpu(18)!=cpu(22));/* delay 001dd1d8 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000010)));if(taken){goto L_001dd188;}}
/* 001dd1dc: sw zero,0x14(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 001dd1e0: move a0,s1 */ set(4,cpu(17));
/* 001dd1e4: li a1,-0x1 */ set(5,sx(UINT32_C(0xffffffff)));
/* 001dd1e8: jal 0x001dfa00 */ set(31,0x001dd1f0u);/* delay 001dd1ec */ set(6,sx(UINT32_C(0xffffffff)));body_001dfa00();
/* 001dd1f0: move v0,s1 */ set(2,cpu(17));
/* 001dd1f4: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dd1f8: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dd1fc: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dd200: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dd204: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dd208: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001dd20c: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001dd210: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001dd214: jr ra */ {uint64_t target=cpu(31);/* delay 001dd218 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DD0D0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001dd0d0();
}
static void body_001dd220(void){
nocturneEffectAxisNoteEntry(0x001dd220u);
uint64_t incoming=cpu(31);
/* 001dd220: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dd224: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dd228: move s2,a0 */ set(18,cpu(4));
/* 001dd22c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd230: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dd234: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dd238: lw s1,0x18(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 001dd23c: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001dd240: beql a0,zero,0x001dd260 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 001dd244 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000008)));goto L_001dd260;}}
L_001dd248:;
/* 001dd248: jal 0x002b3c60 */ set(31,0x001dd250u);/* delay 001dd24c */ sdfMotionCtrlrFree(cpu(4));
/* 001dd250: lw v0,0x14(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001dd254: bne v0,zero,0x001dd248 */ {int taken=(cpu(2)!=cpu(0));/* delay 001dd258 */ set(4,cpu(2));if(taken){goto L_001dd248;}}
/* 001dd25c: lw a0,0x8(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000008)));
L_001dd260:;
/* 001dd260: jal 0x002b2a80 */ set(31,0x001dd268u);/* delay 001dd264 */ set(5,sx(UINT32_C(0x00000001)));body_002b2a80();
/* 001dd268: lw a0,0x14(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000014)));
/* 001dd26c: beq a0,zero,0x001dd28c */ {int taken=(cpu(4)==cpu(0));/* delay 001dd270 */ if(taken){goto L_001dd28c;}}
/* 001dd274: nop  */ 
L_001dd278:;
/* 001dd278: jal 0x001dfa78 */ set(31,0x001dd280u);/* delay 001dd27c */ lw(16,ea(4,(int32_t)UINT32_C(0x00000000)));body_001dfa78();
/* 001dd280: move a0,s0 */ set(4,cpu(16));
/* 001dd284: bne a0,zero,0x001dd278 */ {int taken=(cpu(4)!=cpu(0));/* delay 001dd288 */ if(taken){goto L_001dd278;}}
L_001dd28c:;
/* 001dd28c: jal 0x001dce88 */ set(31,0x001dd294u);/* delay 001dd290 */ set(4,cpu(18));body_001dce88();
/* 001dd294: move a0,s1 */ set(4,cpu(17));
/* 001dd298: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001dd29c: jal 0x002b0648 */ set(31,0x001dd2a4u);/* delay 001dd2a0 */ set(6,sx(UINT32_C(0x00000001)));body_002b0648();
/* 001dd2a4: jal 0x001dcd00 */ set(31,0x001dd2acu);/* delay 001dd2a8 */ set(4,cpu(18));body_001dcd00();
/* 001dd2ac: move a0,s2 */ set(4,cpu(18));
/* 001dd2b0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd2b4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dd2b8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dd2bc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dd2c0: j 0x002a8bd8 */ /* delay 001dd2c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002a8bd8();return;
}
void ps2BattleActionModel_001DD220(uint64_t a0){
set(4,a0);
body_001dd220();
}
static void body_001dd440(void){
nocturneEffectAxisNoteEntry(0x001dd440u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001dd440: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001dd444: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd448: move s0,a0 */ set(16,cpu(4));
/* 001dd44c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dd450: move s2,a1 */ set(18,cpu(5));
/* 001dd454: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dd458: move s3,a2 */ set(19,cpu(6));
/* 001dd45c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dd460: move s4,a3 */ set(20,cpu(7));
/* 001dd464: swc1 f21,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[21]);
/* 001dd468: mov.S f21,f12 */ f[21]=f[12];
/* 001dd46c: swc1 f20,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);
/* 001dd470: mov.S f20,f13 */ f[20]=f[13];
/* 001dd474: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dd478: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dd47c: lw v0,0x18(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001dd480: lw a0,0x14(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000014)));
/* 001dd484: nop  */ 
L_001dd488:;
/* 001dd488: beql a0,zero,0x001dd4b8 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 001dd48c */ set(4,cpu(16));goto L_001dd4b8;}}
/* 001dd490: lh v0,0x28(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000028))));
/* 001dd494: nop  */ 
/* 001dd498: nop  */ 
/* 001dd49c: nop  */ 
/* 001dd4a0: nop  */ 
/* 001dd4a4: bnel v0,s2,0x001dd488 */ {int taken=(cpu(2)!=cpu(18));if(taken){/* delay 001dd4a8 */ lw(4,ea(4,(int32_t)UINT32_C(0x00000000)));goto L_001dd488;}}
/* 001dd4ac: bnel a0,zero,0x001dd4c8 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 001dd4b0 */ set(17,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x0000002a))));goto L_001dd4c8;}}
/* 001dd4b4: move a0,s0 */ set(4,cpu(16));
L_001dd4b8:;
/* 001dd4b8: jal 0x001dc550 */ set(31,0x001dd4c0u);/* delay 001dd4bc */ set(5,cpu(18));body_001dc550();
/* 001dd4c0: move a0,v0 */ set(4,cpu(2));
/* 001dd4c4: lh s1,0x2a(a0) */ set(17,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x0000002a))));
L_001dd4c8:;
/* 001dd4c8: sll v0,s1,0x2 */ set(2,sx((uint32_t)cpu(17)<<2));
/* 001dd4cc: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001dd4d0: bne s1,zero,0x001dd4dc */ {int taken=(cpu(17)!=cpu(0));/* delay 001dd4d4 */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(4));if(taken){goto L_001dd4dc;}}
/* 001dd4d8: sw a0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(4));
L_001dd4dc:;
/* 001dd4dc: move a2,s4 */ set(6,cpu(20));
/* 001dd4e0: mov.S f12,f21 */ f[12]=f[21];
/* 001dd4e4: mov.S f13,f20 */ f[13]=f[20];
/* 001dd4e8: jal 0x002b3d28 */ set(31,0x001dd4f0u);/* delay 001dd4ec */ set(5,cpu(19));sdfMotionChangeBlend(cpu(4),cpu(5),cpu(6),real(nocturneEffectHostFpr()[12]),real(nocturneEffectHostFpr()[13]));
/* 001dd4f0: sh s2,0x10(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000010)),(uint16_t)cpu(18));
/* 001dd4f4: sh s3,0x12(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000012)),(uint16_t)cpu(19));
/* 001dd4f8: move a0,s0 */ set(4,cpu(16));
/* 001dd4fc: jal 0x001dfb00 */ set(31,0x001dd504u);/* delay 001dd500 */ set(5,cpu(17));body_001dfb00();
/* 001dd504: move a0,s0 */ set(4,cpu(16));
/* 001dd508: move a1,s3 */ set(5,cpu(19));
/* 001dd50c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dd510: move a2,s1 */ set(6,cpu(17));
/* 001dd514: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dd518: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd51c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dd520: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001dd524: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001dd528: lwc1 f21,0x38(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001dd52c: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001dd530: j 0x001dfa00 */ /* delay 001dd534 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);body_001dfa00();return;
}
void ps2BattleActionModel_001DD440(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, float f12, float f13){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectHostFpr()[13]=bits(f13);
body_001dd440();
}
static void body_001dd538(void){
nocturneEffectAxisNoteEntry(0x001dd538u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001dd538: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dd53c: clear f12 */ f[12]=0;
/* 001dd540: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd544: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 001dd548: mov.S f13,f12 */ f[13]=f[12];
/* 001dd54c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd550: j 0x001dd440 */ /* delay 001dd554 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001dd440();return;
}
void ps2BattleActionModel_001DD538(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_001dd538();
}
static void body_001dd558(void){
nocturneEffectAxisNoteEntry(0x001dd558u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001dd558: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dd55c: clear f12 */ f[12]=0;
/* 001dd560: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd564: move a3,zero */ set(7,cpu(0));
/* 001dd568: mov.S f13,f12 */ f[13]=f[12];
/* 001dd56c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd570: j 0x001dd440 */ /* delay 001dd574 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001dd440();return;
}
void ps2BattleActionModel_001DD558(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_001dd558();
}
static void body_001dd750(void){
nocturneEffectAxisNoteEntry(0x001dd750u);
uint64_t incoming=cpu(31);
/* 001dd750: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dd754: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd758: move s0,a0 */ set(16,cpu(4));
/* 001dd75c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dd760: lw v0,0x18(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001dd764: addiu v0,v0,0x60 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000060)));
/* 001dd768: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001dd76c: jal 0x002c0600 */ set(31,0x001dd774u);/* delay 001dd770 */ body_002c0600();
/* 001dd774: lw v0,0x18(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001dd778: addiu v0,v0,0x20 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 001dd77c: sqc2 vf28,0x0(v0) */ storeVu(28,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001dd780: lw v1,0x18(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001dd784: addiu v1,v1,0x30 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000030)));
/* 001dd788: sqc2 vf29,0x0(v1) */ storeVu(29,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001dd78c: lw v0,0x18(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001dd790: addiu v0,v0,0x40 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000040)));
/* 001dd794: sqc2 vf30,0x0(v0) */ storeVu(30,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001dd798: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd79c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dd7a0: jr ra */ {uint64_t target=cpu(31);/* delay 001dd7a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DD750(uint64_t a0){
set(4,a0);
body_001dd750();
}
static uint64_t body_001ddb68(void){
nocturneEffectAxisNoteEntry(0x001ddb68u);
uint64_t incoming=cpu(31);
/* 001ddb68: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 001ddb6c: jr ra */ {uint64_t target=cpu(31);/* delay 001ddb70 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000008))));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DDB68(uint64_t a0){
set(4,a0);
return body_001ddb68();
}
static uint64_t body_001ddb78(void){
nocturneEffectAxisNoteEntry(0x001ddb78u);
uint64_t incoming=cpu(31);
/* 001ddb78: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 001ddb7c: jr ra */ {uint64_t target=cpu(31);/* delay 001ddb80 */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000a))));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DDB78(uint64_t a0){
set(4,a0);
return body_001ddb78();
}
static uint64_t body_001ddd18(void){
nocturneEffectAxisNoteEntry(0x001ddd18u);
uint64_t incoming=cpu(31);
/* 001ddd18: lbu v0,0x10(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000010))));
/* 001ddd1c: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 001ddd20: bne v0,v1,0x001ddd3c */ {int taken=(cpu(2)!=cpu(3));/* delay 001ddd24 */ set(5,cpu(0));if(taken){goto L_001ddd3c;}}
/* 001ddd28: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001ddd2c: lui v0,0x3042 */ set(2,sx(UINT32_C(0x30420000)));
/* 001ddd30: ori v0,v0,0x4950 */ set(2,cpu(2)|UINT32_C(0x00004950));
/* 001ddd34: xor v1,v1,v0 */ set(3,cpu(3)^cpu(2));
/* 001ddd38: sltiu a1,v1,0x1 */ set(5,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_001ddd3c:;
/* 001ddd3c: jr ra */ {uint64_t target=cpu(31);/* delay 001ddd40 */ set(2,cpu(5));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DDD18(uint64_t a0){
set(4,a0);
return body_001ddd18();
}
static uint64_t body_001ddd48(void){
nocturneEffectAxisNoteEntry(0x001ddd48u);
uint64_t incoming=cpu(31);
/* 001ddd48: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 001ddd4c: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001ddd50: move s0,a0 */ set(16,cpu(4));
/* 001ddd54: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001ddd58: move s3,a2 */ set(19,cpu(6));
/* 001ddd5c: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001ddd60: move s4,a1 */ set(20,cpu(5));
/* 001ddd64: move a0,sp */ set(4,cpu(29));
/* 001ddd68: li a2,0x20 */ set(6,sx(UINT32_C(0x00000020)));
/* 001ddd6c: move a1,zero */ set(5,cpu(0));
/* 001ddd70: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001ddd74: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001ddd78: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001ddd7c: jal 0x002d4558 */ set(31,0x001ddd84u);/* delay 001ddd80 */ set(18,cpu(7));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 001ddd84: beq s0,zero,0x001ddec8 */ {int taken=(cpu(16)==cpu(0));/* delay 001ddd88 */ set(17,cpu(0));if(taken){goto L_001ddec8;}}
/* 001ddd8c: lbu v1,0x10(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000010))));
L_001ddd90:;
/* 001ddd90: li v0,0x6 */ set(2,sx(UINT32_C(0x00000006)));
/* 001ddd94: beq v1,v0,0x001dde78 */ {int taken=(cpu(3)==cpu(2));/* delay 001ddd98 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000007));if(taken){goto L_001dde78;}}
/* 001ddd9c: beq v0,zero,0x001dddb8 */ {int taken=(cpu(2)==cpu(0));/* delay 001ddda0 */ set(2,sx(UINT32_C(0x00000008)));if(taken){goto L_001dddb8;}}
/* 001ddda4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001ddda8: beq v1,v0,0x001dddd0 */ {int taken=(cpu(3)==cpu(2));/* delay 001dddac */ set(2,sx(UINT32_C(0x00500000)));if(taken){goto L_001dddd0;}}
/* 001dddb0: b 0x001ddeb4 */ /* delay 001dddb4 */ goto L_001ddeb4;
L_001dddb8:;
/* 001dddb8: beq v1,v0,0x001dde98 */ {int taken=(cpu(3)==cpu(2));/* delay 001dddbc */ set(2,sx(UINT32_C(0x00000009)));if(taken){goto L_001dde98;}}
/* 001dddc0: beql v1,v0,0x001dde70 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 001dddc4 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_001dde70;}}
/* 001dddc8: b 0x001ddeb4 */ /* delay 001dddcc */ goto L_001ddeb4;
L_001dddd0:;
/* 001dddd0: lw v1,0x18(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001dddd4: ori v0,v0,0x3344 */ set(2,cpu(2)|UINT32_C(0x00003344));
/* 001dddd8: beq v1,v0,0x001dde50 */ {int taken=(cpu(3)==cpu(2));/* delay 001ddddc */ set(2,cpu(2)<cpu(3));if(taken){goto L_001dde50;}}
/* 001ddde0: bne v0,zero,0x001dde00 */ {int taken=(cpu(2)!=cpu(0));/* delay 001ddde4 */ set(2,sx(UINT32_C(0x30420000)));if(taken){goto L_001dde00;}}
/* 001ddde8: lui v0,0x41 */ set(2,sx(UINT32_C(0x00410000)));
/* 001dddec: ori v0,v0,0x3250 */ set(2,cpu(2)|UINT32_C(0x00003250));
/* 001dddf0: beql v1,v0,0x001dde40 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 001dddf4 */ lw(5,ea(16,(int32_t)UINT32_C(0x0000000c)));goto L_001dde40;}}
/* 001dddf8: b 0x001ddeb4 */ /* delay 001dddfc */ goto L_001ddeb4;
L_001dde00:;
/* 001dde00: ori v0,v0,0x4950 */ set(2,cpu(2)|UINT32_C(0x00004950));
/* 001dde04: bne v1,v0,0x001ddeb4 */ {int taken=(cpu(3)!=cpu(2));/* delay 001dde08 */ if(taken){goto L_001ddeb4;}}
/* 001dde0c: lw a0,0xc(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001dde10: sw a0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(4));
/* 001dde14: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001dde18: jal 0x001deb80 */ set(31,0x001dde20u);/* delay 001dde1c */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));body_001deb80();
/* 001dde20: blez v0,0x001ddeb4 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001dde24 */ if(taken){goto L_001ddeb4;}}
/* 001dde28: jal 0x001df460 */ set(31,0x001dde30u);/* delay 001dde2c */ set(4,cpu(2));body_001df460();
/* 001dde30: move s1,v0 */ set(17,cpu(2));
/* 001dde34: b 0x001ddeb4 */ /* delay 001dde38 */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(17));goto L_001ddeb4;
L_001dde40:;
/* 001dde40: jal 0x001df290 */ set(31,0x001dde48u);/* delay 001dde44 */ set(4,cpu(17));body_001df290();
/* 001dde48: b 0x001dde5c */ /* delay 001dde4c */ goto L_001dde5c;
L_001dde50:;
/* 001dde50: lw a1,0xc(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001dde54: jal 0x001df2e8 */ set(31,0x001dde5cu);/* delay 001dde58 */ set(4,cpu(17));body_001df2e8();
L_001dde5c:;
/* 001dde5c: jal 0x002a9558 */ set(31,0x001dde64u);/* delay 001dde60 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));body_002a9558();
/* 001dde64: b 0x001ddeb4 */ /* delay 001dde68 */ goto L_001ddeb4;
L_001dde70:;
/* 001dde70: b 0x001ddeb4 */ /* delay 001dde74 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_001ddeb4;
L_001dde78:;
/* 001dde78: lw v0,0x8(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dde7c: bne v0,zero,0x001ddeb4 */ {int taken=(cpu(2)!=cpu(0));/* delay 001dde80 */ if(taken){goto L_001ddeb4;}}
/* 001dde84: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001dde88: lw v1,0xc(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001dde8c: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001dde90: b 0x001ddeb4 */ /* delay 001dde94 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));goto L_001ddeb4;
L_001dde98:;
/* 001dde98: lw v0,0x10(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dde9c: bne v0,zero,0x001ddeb4 */ {int taken=(cpu(2)!=cpu(0));/* delay 001ddea0 */ if(taken){goto L_001ddeb4;}}
/* 001ddea4: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001ddea8: lw v1,0xc(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001ddeac: sw v0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 001ddeb0: sw v1,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
L_001ddeb4:;
/* 001ddeb4: jal 0x002c6440 */ set(31,0x001ddebcu);/* delay 001ddeb8 */ set(4,cpu(16));set(2,ps2BattleActionPac_002C6440(cpu(4)));
/* 001ddebc: move s0,v0 */ set(16,cpu(2));
/* 001ddec0: bnel s0,zero,0x001ddd90 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 001ddec4 */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000010))));goto L_001ddd90;}}
L_001ddec8:;
/* 001ddec8: move a0,s4 */ set(4,cpu(20));
/* 001ddecc: move a1,s3 */ set(5,cpu(19));
/* 001dded0: move a2,s2 */ set(6,cpu(18));
/* 001dded4: jal 0x001dc808 */ set(31,0x001ddedcu);/* delay 001dded8 */ set(7,cpu(29));body_001dc808();
/* 001ddedc: move v0,s0 */ set(2,cpu(16));
/* 001ddee0: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001ddee4: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001ddee8: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001ddeec: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001ddef0: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001ddef4: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001ddef8: jr ra */ {uint64_t target=cpu(31);/* delay 001ddefc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DDD48(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_001ddd48();
}
static uint64_t body_001ddf00(void){
nocturneEffectAxisNoteEntry(0x001ddf00u);
uint64_t incoming=cpu(31);
/* 001ddf00: addiu sp,sp,-0x90 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff70)));
/* 001ddf04: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001ddf08: move s0,a0 */ set(16,cpu(4));
/* 001ddf0c: sd s7,0x78(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 001ddf10: move s7,a1 */ set(23,cpu(5));
/* 001ddf14: sd s8,0x80(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 001ddf18: move s8,a2 */ set(30,cpu(6));
/* 001ddf1c: sd s1,0x48(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001ddf20: sd s2,0x50(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001ddf24: sd s3,0x58(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001ddf28: sd s4,0x60(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001ddf2c: sd s5,0x68(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001ddf30: sd s6,0x70(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 001ddf34: sd ra,0x88(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 001ddf38: jal 0x001ddd18 */ set(31,0x001ddf40u);/* delay 001ddf3c */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(7));body_001ddd18();
/* 001ddf40: beq v0,zero,0x001ddf60 */ {int taken=(cpu(2)==cpu(0));/* delay 001ddf44 */ lw(7,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_001ddf60;}}
/* 001ddf48: lw s4,0xc(s0) */ lw(20,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001ddf4c: jal 0x001dea58 */ set(31,0x001ddf54u);/* delay 001ddf50 */ set(4,cpu(20));body_001dea58();
/* 001ddf54: bgtzl v0,0x001ddf78 */ {int taken=((int64_t)cpu(2)>0);if(taken){/* delay 001ddf58 */ set(4,cpu(29));goto L_001ddf78;}}
/* 001ddf5c: lw a3,0x30(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000030)));
L_001ddf60:;
/* 001ddf60: move a0,s0 */ set(4,cpu(16));
/* 001ddf64: move a1,s7 */ set(5,cpu(23));
/* 001ddf68: jal 0x001ddd48 */ set(31,0x001ddf70u);/* delay 001ddf6c */ set(6,cpu(30));body_001ddd48();
/* 001ddf70: b 0x001de144 */ /* delay 001ddf74 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));goto L_001de144;
L_001ddf78:;
/* 001ddf78: move a1,zero */ set(5,cpu(0));
/* 001ddf7c: jal 0x002d4558 */ set(31,0x001ddf84u);/* delay 001ddf80 */ set(6,sx(UINT32_C(0x00000020)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 001ddf84: move a0,s0 */ set(4,cpu(16));
/* 001ddf88: sw s4,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(20));
/* 001ddf8c: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001ddf90: jal 0x002c6440 */ set(31,0x001ddf98u);/* delay 001ddf94 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));set(2,ps2BattleActionPac_002C6440(cpu(4)));
/* 001ddf98: move a0,s4 */ set(4,cpu(20));
/* 001ddf9c: jal 0x001deb80 */ set(31,0x001ddfa4u);/* delay 001ddfa0 */ set(16,cpu(2));body_001deb80();
/* 001ddfa4: move s1,v0 */ set(17,cpu(2));
/* 001ddfa8: blezl s1,0x001de098 */ {int taken=((int64_t)cpu(17)<=0);if(taken){/* delay 001ddfac */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000010))));goto L_001de098;}}
/* 001ddfb0: jal 0x001df460 */ set(31,0x001ddfb8u);/* delay 001ddfb4 */ set(4,cpu(17));body_001df460();
/* 001ddfb8: move s2,v0 */ set(18,cpu(2));
/* 001ddfbc: blez s1,0x001de094 */ {int taken=((int64_t)cpu(17)<=0);/* delay 001ddfc0 */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(18));if(taken){goto L_001de094;}}
/* 001ddfc4: lui s3,0x50 */ set(19,sx(UINT32_C(0x00500000)));
/* 001ddfc8: lui s6,0x41 */ set(22,sx(UINT32_C(0x00410000)));
/* 001ddfcc: lui s5,0x55 */ set(21,sx(UINT32_C(0x00550000)));
/* 001ddfd0: ori s3,s3,0x3344 */ set(19,cpu(19)|UINT32_C(0x00003344));
/* 001ddfd4: ori s6,s6,0x3250 */ set(22,cpu(22)|UINT32_C(0x00003250));
/* 001ddfd8: ori s5,s5,0x5049 */ set(21,cpu(21)|UINT32_C(0x00005049));
/* 001ddfdc: nop  */ 
L_001ddfe0:;
/* 001ddfe0: lw v1,0x18(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001ddfe4: beq v1,s3,0x001de028 */ {int taken=(cpu(3)==cpu(19));/* delay 001ddfe8 */ set(2,cpu(19)<cpu(3));if(taken){goto L_001de028;}}
/* 001ddfec: bne v0,zero,0x001de008 */ {int taken=(cpu(2)!=cpu(0));/* delay 001ddff0 */ if(taken){goto L_001de008;}}
/* 001ddff4: beql v1,s6,0x001de018 */ {int taken=(cpu(3)==cpu(22));if(taken){/* delay 001ddff8 */ lw(5,ea(16,(int32_t)UINT32_C(0x0000000c)));goto L_001de018;}}
/* 001ddffc: b 0x001de078 */ /* delay 001de000 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));goto L_001de078;
L_001de008:;
/* 001de008: beql v1,s5,0x001de048 */ {int taken=(cpu(3)==cpu(21));if(taken){/* delay 001de00c */ lw(7,ea(16,(int32_t)UINT32_C(0x0000001c)));goto L_001de048;}}
/* 001de010: b 0x001de078 */ /* delay 001de014 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));goto L_001de078;
L_001de018:;
/* 001de018: jal 0x001df290 */ set(31,0x001de020u);/* delay 001de01c */ set(4,cpu(18));body_001df290();
/* 001de020: b 0x001de034 */ /* delay 001de024 */ goto L_001de034;
L_001de028:;
/* 001de028: lw a1,0xc(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001de02c: jal 0x001df2e8 */ set(31,0x001de034u);/* delay 001de030 */ set(4,cpu(18));body_001df2e8();
L_001de034:;
/* 001de034: jal 0x002a9558 */ set(31,0x001de03cu);/* delay 001de038 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));body_002a9558();
/* 001de03c: b 0x001de084 */ /* delay 001de040 */ set(4,cpu(16));goto L_001de084;
L_001de048:;
/* 001de048: bne a3,zero,0x001de064 */ {int taken=(cpu(7)!=cpu(0));/* delay 001de04c */ lw(5,ea(16,(int32_t)UINT32_C(0x0000000c)));if(taken){goto L_001de064;}}
/* 001de050: lbu v0,0x11(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000011))));
/* 001de054: lw v1,0x14(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001de058: andi v0,v0,0xf0 */ set(2,cpu(2)&UINT32_C(0x000000f0));
/* 001de05c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001de060: addiu a3,v1,-0x10 */ set(7,sx((uint32_t)cpu(3)+UINT32_C(0xfffffff0)));
L_001de064:;
/* 001de064: move a0,s2 */ set(4,cpu(18));
/* 001de068: jal 0x001df348 */ set(31,0x001de070u);/* delay 001de06c */ lw(6,ea(16,(int32_t)UINT32_C(0x00000008)));body_001df348();
/* 001de070: b 0x001de084 */ /* delay 001de074 */ set(4,cpu(16));goto L_001de084;
L_001de078:;
/* 001de078: sb zero,0x24(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000024)),(uint8_t)cpu(0));
/* 001de07c: sw v0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 001de080: move a0,s0 */ set(4,cpu(16));
L_001de084:;
/* 001de084: jal 0x002c6440 */ set(31,0x001de08cu);/* delay 001de088 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));set(2,ps2BattleActionPac_002C6440(cpu(4)));
/* 001de08c: bne s1,zero,0x001ddfe0 */ {int taken=(cpu(17)!=cpu(0));/* delay 001de090 */ set(16,cpu(2));if(taken){goto L_001ddfe0;}}
L_001de094:;
/* 001de094: lbu v1,0x10(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000010))));
L_001de098:;
/* 001de098: li v0,0x9 */ set(2,sx(UINT32_C(0x00000009)));
/* 001de09c: bnel v1,v0,0x001de0bc */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 001de0a0 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_001de0bc;}}
/* 001de0a4: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001de0a8: move a0,s0 */ set(4,cpu(16));
/* 001de0ac: jal 0x002c6440 */ set(31,0x001de0b4u);/* delay 001de0b0 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));set(2,ps2BattleActionPac_002C6440(cpu(4)));
/* 001de0b4: move s0,v0 */ set(16,cpu(2));
/* 001de0b8: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
L_001de0bc:;
/* 001de0bc: move a0,s0 */ set(4,cpu(16));
/* 001de0c0: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001de0c4: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 001de0c8: jal 0x002c6440 */ set(31,0x001de0d0u);/* delay 001de0cc */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));set(2,ps2BattleActionPac_002C6440(cpu(4)));
/* 001de0d0: lw a2,0x30(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001de0d4: move a3,sp */ set(7,cpu(29));
/* 001de0d8: move a0,s7 */ set(4,cpu(23));
/* 001de0dc: move a1,s8 */ set(5,cpu(30));
/* 001de0e0: jal 0x001dc808 */ set(31,0x001de0e8u);/* delay 001de0e4 */ set(16,cpu(2));body_001dc808();
/* 001de0e8: jal 0x001deb88 */ set(31,0x001de0f0u);/* delay 001de0ec */ set(4,cpu(20));body_001deb88();
/* 001de0f0: move s1,v0 */ set(17,cpu(2));
/* 001de0f4: blez s1,0x001de140 */ {int taken=((int64_t)cpu(17)<=0);/* delay 001de0f8 */ set(2,cpu(16));if(taken){goto L_001de140;}}
/* 001de0fc: nop  */ 
L_001de100:;
/* 001de100: lw t2,0xc(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001de104: move a1,s8 */ set(5,cpu(30));
/* 001de108: lw t3,0x8(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001de10c: move a0,s7 */ set(4,cpu(23));
/* 001de110: addiu v0,t2,-0x10 */ set(2,sx((uint32_t)cpu(10)+UINT32_C(0xfffffff0)));
/* 001de114: lw a2,0x30(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001de118: lhu t1,0xa(v0) */ set(9,half(ea(2,(int32_t)UINT32_C(0x0000000a))));
/* 001de11c: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
/* 001de120: lh a3,0xc(v0) */ set(7,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 001de124: jal 0x001dc748 */ set(31,0x001de12cu);/* delay 001de128 */ set(8,half(ea(2,(int32_t)UINT32_C(0x00000008))));body_001dc748();
/* 001de12c: jal 0x002c6440 */ set(31,0x001de134u);/* delay 001de130 */ set(4,cpu(16));set(2,ps2BattleActionPac_002C6440(cpu(4)));
/* 001de134: bgtz s1,0x001de100 */ {int taken=((int64_t)cpu(17)>0);/* delay 001de138 */ set(16,cpu(2));if(taken){goto L_001de100;}}
/* 001de13c: move v0,s0 */ set(2,cpu(16));
L_001de140:;
/* 001de140: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
L_001de144:;
/* 001de144: ld s1,0x48(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001de148: ld s2,0x50(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001de14c: ld s3,0x58(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001de150: ld s4,0x60(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001de154: ld s5,0x68(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001de158: ld s6,0x70(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 001de15c: ld s7,0x78(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 001de160: ld s8,0x80(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 001de164: ld ra,0x88(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 001de168: jr ra */ {uint64_t target=cpu(31);/* delay 001de16c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000090)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DDF00(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_001ddf00();
}
static void body_001de170(void){
nocturneEffectAxisNoteEntry(0x001de170u);
uint64_t incoming=cpu(31);
/* 001de170: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001de174: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001de178: move s0,a0 */ set(16,cpu(4));
/* 001de17c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001de180: jal 0x002966a8 */ set(31,0x001de188u);/* delay 001de184 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));set(2,ps2ResourcePacRequestFree(cpu(4)));
/* 001de188: move a0,s0 */ set(4,cpu(16));
/* 001de18c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001de190: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001de194: j 0x002a8bd8 */ /* delay 001de198 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002a8bd8();return;
}
void ps2BattleActionModel_001DE170(uint64_t a0){
set(4,a0);
body_001de170();
}
static uint64_t body_001dea58(void){
nocturneEffectAxisNoteEntry(0x001dea58u);
uint64_t incoming=cpu(31);
/* 001dea58: jr ra */ {uint64_t target=cpu(31);/* delay 001dea5c */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DEA58(uint64_t a0){
set(4,a0);
return body_001dea58();
}
static uint64_t body_001dea60(void){
nocturneEffectAxisNoteEntry(0x001dea60u);
uint64_t incoming=cpu(31);
/* 001dea60: jr ra */ {uint64_t target=cpu(31);/* delay 001dea64 */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000000c))));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DEA60(uint64_t a0){
set(4,a0);
return body_001dea60();
}
static uint64_t body_001dea68(void){
nocturneEffectAxisNoteEntry(0x001dea68u);
uint64_t incoming=cpu(31);
/* 001dea68: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dea6c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dea70: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dea74: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dea78: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 001dea7c: lw v0,0xa4(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x000000a4)));
/* 001dea80: bne v0,zero,0x001dea90 */ {int taken=(cpu(2)!=cpu(0));/* delay 001dea84 */ set(17,cpu(5));if(taken){goto L_001dea90;}}
/* 001dea88: b 0x001dead0 */ /* delay 001dea8c */ set(2,cpu(0));goto L_001dead0;
L_001dea90:;
/* 001dea90: move s0,v0 */ set(16,cpu(2));
/* 001dea94: jal 0x001dea60 */ set(31,0x001dea9cu);/* delay 001dea98 */ set(4,cpu(16));body_001dea60();
/* 001dea9c: li a1,-0x1 */ set(5,sx(UINT32_C(0xffffffff)));
/* 001deaa0: move a0,v0 */ set(4,cpu(2));
/* 001deaa4: lw v1,0x4(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));
L_001deaa8:;
/* 001deaa8: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 001deaac: move v0,zero */ set(2,cpu(0));
/* 001deab0: beq a0,a1,0x001dead0 */ {int taken=(cpu(4)==cpu(5));/* delay 001deab4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));if(taken){goto L_001dead0;}}
/* 001deab8: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001deabc: nop  */ 
/* 001deac0: nop  */ 
/* 001deac4: bnel v0,s1,0x001deaa8 */ {int taken=(cpu(2)!=cpu(17));if(taken){/* delay 001deac8 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_001deaa8;}}
/* 001deacc: move v0,s0 */ set(2,cpu(16));
L_001dead0:;
/* 001dead0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dead4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dead8: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001deadc: jr ra */ {uint64_t target=cpu(31);/* delay 001deae0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DEA68(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001dea68();
}
static uint64_t body_001deae8(void){
nocturneEffectAxisNoteEntry(0x001deae8u);
uint64_t incoming=cpu(31);
/* 001deae8: addiu v0,a0,0x8 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
/* 001deaec: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001deaf0: xori v1,v1,0xffff */ set(3,cpu(3)^UINT32_C(0x0000ffff));
/* 001deaf4: jr ra */ {uint64_t target=cpu(31);/* delay 001deaf8 */ if(cpu(3)==0){set(2,cpu(0));}checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DEAE8(uint64_t a0){
set(4,a0);
return body_001deae8();
}
static uint64_t body_001deb00(void){
nocturneEffectAxisNoteEntry(0x001deb00u);
uint64_t incoming=cpu(31);
/* 001deb00: move v0,a0 */ set(2,cpu(4));
/* 001deb04: lw a0,0x4(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 001deb08: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001deb0c: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001deb10: xori v1,v1,0xffff */ set(3,cpu(3)^UINT32_C(0x0000ffff));
/* 001deb14: jr ra */ {uint64_t target=cpu(31);/* delay 001deb18 */ if(cpu(3)==0){set(2,cpu(0));}checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DEB00(uint64_t a0){
set(4,a0);
return body_001deb00();
}
static uint64_t body_001deb80(void){
nocturneEffectAxisNoteEntry(0x001deb80u);
uint64_t incoming=cpu(31);
/* 001deb80: jr ra */ {uint64_t target=cpu(31);/* delay 001deb84 */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000000e))));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DEB80(uint64_t a0){
set(4,a0);
return body_001deb80();
}
static uint64_t body_001deb88(void){
nocturneEffectAxisNoteEntry(0x001deb88u);
uint64_t incoming=cpu(31);
/* 001deb88: jr ra */ {uint64_t target=cpu(31);/* delay 001deb8c */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000010))));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DEB88(uint64_t a0){
set(4,a0);
return body_001deb88();
}
static void body_001df290(void){
nocturneEffectAxisNoteEntry(0x001df290u);
uint64_t incoming=cpu(31);
/* 001df290: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001df294: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df298: move s1,a0 */ set(17,cpu(4));
/* 001df29c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df2a0: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001df2a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df2a8: lh v0,0x4(s1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 001df2ac: lw s0,0xc(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 001df2b0: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 001df2b4: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001df2b8: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001df2bc: jal 0x0015cdb0 */ set(31,0x001df2c4u);/* delay 001df2c0 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));set(2,ps2BattleActionCreation_0015CDB0(cpu(4),cpu(5)));
/* 001df2c4: lhu v1,0x4(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 001df2c8: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001df2cc: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001df2d0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df2d4: sh v1,0x4(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
/* 001df2d8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df2dc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df2e0: jr ra */ {uint64_t target=cpu(31);/* delay 001df2e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DF290(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_001df290();
}
static void body_001df2e8(void){
nocturneEffectAxisNoteEntry(0x001df2e8u);
uint64_t incoming=cpu(31);
/* 001df2e8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001df2ec: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 001df2f0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df2f4: move s1,a0 */ set(17,cpu(4));
/* 001df2f8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df2fc: move a0,a1 */ set(4,cpu(5));
/* 001df300: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df304: lh v0,0x4(s1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 001df308: lw s0,0xc(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 001df30c: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 001df310: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001df314: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001df318: jal 0x0015ada0 */ set(31,0x001df320u);/* delay 001df31c */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));set(2,ps2BattleActionCreation_0015ADA0(cpu(4)));
/* 001df320: lhu v1,0x4(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 001df324: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001df328: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001df32c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df330: sh v1,0x4(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
/* 001df334: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df338: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df33c: jr ra */ {uint64_t target=cpu(31);/* delay 001df340 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DF2E8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_001df2e8();
}
static void body_001df348(void){
nocturneEffectAxisNoteEntry(0x001df348u);
uint64_t incoming=cpu(31);
/* 001df348: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001df34c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df350: move s0,a0 */ set(16,cpu(4));
/* 001df354: li a0,0xac */ set(4,sx(UINT32_C(0x000000ac)));
/* 001df358: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df35c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df360: move s2,a1 */ set(18,cpu(5));
/* 001df364: move s1,a3 */ set(17,cpu(7));
/* 001df368: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df36c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001df370: jal 0x002a8ba8 */ set(31,0x001df378u);/* delay 001df374 */ set(19,cpu(6));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 001df378: lh a1,0x4(s0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000004))));
/* 001df37c: lhu v1,0x4(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000004))));
/* 001df380: li a2,0x3 */ set(6,sx(UINT32_C(0x00000003)));
/* 001df384: lw a0,0xc(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001df388: sll a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)<<4));
/* 001df38c: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001df390: sw s1,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(17));
/* 001df394: sw s2,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));
/* 001df398: addu a0,a0,a1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 001df39c: sh v1,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
/* 001df3a0: sw s3,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(19));
/* 001df3a4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df3a8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df3ac: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df3b0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df3b4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001df3b8: sw v0,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001df3bc: sw a2,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
/* 001df3c0: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001df3c4: jr ra */ {uint64_t target=cpu(31);/* delay 001df3c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DF348(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_001df348();
}
static void body_001df3d0(void){
nocturneEffectAxisNoteEntry(0x001df3d0u);
uint64_t incoming=cpu(31);
/* 001df3d0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001df3d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df3d8: move s0,a0 */ set(16,cpu(4));
/* 001df3dc: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df3e0: lbu v0,0x9(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000009))));
/* 001df3e4: beq v0,zero,0x001df3f4 */ {int taken=(cpu(2)==cpu(0));/* delay 001df3e8 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));if(taken){goto L_001df3f4;}}
/* 001df3ec: jal 0x002c42b0 */ set(31,0x001df3f4u);/* delay 001df3f0 */ ps2MovieDecoderDestroy(cpu(4));
L_001df3f4:;
/* 001df3f4: jal 0x002a9558 */ set(31,0x001df3fcu);/* delay 001df3f8 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));body_002a9558();
/* 001df3fc: move a0,s0 */ set(4,cpu(16));
/* 001df400: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df404: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df408: j 0x002a8bd8 */ /* delay 001df40c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002a8bd8();return;
}
void ps2BattleActionModel_001DF3D0(uint64_t a0){
set(4,a0);
body_001df3d0();
}
static uint64_t body_001df460(void){
nocturneEffectAxisNoteEntry(0x001df460u);
uint64_t incoming=cpu(31);
/* 001df460: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001df464: li a1,0x10 */ set(5,sx(UINT32_C(0x00000010)));
/* 001df468: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df46c: li a2,0x4 */ set(6,sx(UINT32_C(0x00000004)));
/* 001df470: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df474: j 0x002bfe58 */ /* delay 001df478 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);set(2,ps2EffectArrayCreate_002BFE58(cpu(4),cpu(5),cpu(6)));return cpu(2);
}
uint64_t ps2BattleActionModel_001DF460(uint64_t a0){
set(4,a0);
return body_001df460();
}
static void body_001df480(void){
nocturneEffectAxisNoteEntry(0x001df480u);
uint64_t incoming=cpu(31);
/* 001df480: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001df484: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df488: move s0,a0 */ set(16,cpu(4));
/* 001df48c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df490: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df494: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df498: beq s0,zero,0x001df550 */ {int taken=(cpu(16)==cpu(0));/* delay 001df49c */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_001df550;}}
/* 001df4a0: lh v0,0x4(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000004))));
/* 001df4a4: move s1,zero */ set(17,cpu(0));
/* 001df4a8: blez v0,0x001df530 */ {int taken=((int64_t)cpu(2)<=0);/* delay 001df4ac */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000004))));if(taken){goto L_001df530;}}
/* 001df4b0: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
/* 001df4b4: li s2,0x3 */ set(18,sx(UINT32_C(0x00000003)));
/* 001df4b8: lw v1,0xc(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001df4bc: nop  */ 
L_001df4c0:;
/* 001df4c0: sll v0,s1,0x4 */ set(2,sx((uint32_t)cpu(17)<<4));
/* 001df4c4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001df4c8: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001df4cc: beq v0,s3,0x001df500 */ {int taken=(cpu(2)==cpu(19));/* delay 001df4d0 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));if(taken){goto L_001df500;}}
/* 001df4d4: beq v0,zero,0x001df4f0 */ {int taken=(cpu(2)==cpu(0));/* delay 001df4d8 */ if(taken){goto L_001df4f0;}}
/* 001df4dc: beq v0,s2,0x001df510 */ {int taken=(cpu(2)==cpu(18));/* delay 001df4e0 */ set(2,sx((uint32_t)cpu(4)<<16));if(taken){goto L_001df510;}}
/* 001df4e4: b 0x001df524 */ /* delay 001df4e8 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>16)));goto L_001df524;
L_001df4f0:;
/* 001df4f0: jal 0x0015cf40 */ set(31,0x001df4f8u);/* delay 001df4f4 */ lw(4,ea(3,(int32_t)UINT32_C(0x00000008)));dds3BillboardDelete(cpu(4));
/* 001df4f8: b 0x001df51c */ /* delay 001df4fc */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000004))));goto L_001df51c;
L_001df500:;
/* 001df500: jal 0x0015ab58 */ set(31,0x001df508u);/* delay 001df504 */ lw(4,ea(3,(int32_t)UINT32_C(0x00000008)));dds3EffectDelete(cpu(4));
/* 001df508: b 0x001df51c */ /* delay 001df50c */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000004))));goto L_001df51c;
L_001df510:;
/* 001df510: jal 0x001df3d0 */ set(31,0x001df518u);/* delay 001df514 */ lw(4,ea(3,(int32_t)UINT32_C(0x00000008)));body_001df3d0();
/* 001df518: lhu a0,0x4(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000004))));
L_001df51c:;
/* 001df51c: sll v0,a0,0x10 */ set(2,sx((uint32_t)cpu(4)<<16));
/* 001df520: sra v0,v0,0x10 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>16)));
L_001df524:;
/* 001df524: slt v0,s1,v0 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(2));
/* 001df528: bnel v0,zero,0x001df4c0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001df52c */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));goto L_001df4c0;}}
L_001df530:;
/* 001df530: move a0,s0 */ set(4,cpu(16));
/* 001df534: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df538: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df53c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df540: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df544: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001df548: j 0x002bfee8 */ /* delay 001df54c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_002bfee8();return;
L_001df550:;
/* 001df550: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df554: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df558: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df55c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df560: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001df564: jr ra */ {uint64_t target=cpu(31);/* delay 001df568 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DF480(uint64_t a0){
set(4,a0);
body_001df480();
}
static uint64_t body_001df570(void){
nocturneEffectAxisNoteEntry(0x001df570u);
uint64_t incoming=cpu(31);
/* 001df570: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001df574: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df578: move s1,a0 */ set(17,cpu(4));
/* 001df57c: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 001df580: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df584: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df588: move s2,a2 */ set(18,cpu(6));
/* 001df58c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df590: jal 0x002a8ba8 */ set(31,0x001df598u);/* delay 001df594 */ set(16,cpu(5));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 001df598: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001df59c: move v1,v0 */ set(3,cpu(2));
/* 001df5a0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df5a4: sh s0,0x4(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(16));
/* 001df5a8: sw a0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001df5ac: sh s2,0x6(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(18));
/* 001df5b0: sw v1,0x14(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 001df5b4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df5b8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df5bc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df5c0: jr ra */ {uint64_t target=cpu(31);/* delay 001df5c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DF570(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_001df570();
}
static uint64_t body_001df5c8(void){
nocturneEffectAxisNoteEntry(0x001df5c8u);
uint64_t incoming=cpu(31);
/* 001df5c8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001df5cc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df5d0: move s0,a0 */ set(16,cpu(4));
/* 001df5d4: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df5d8: jal 0x0015cea0 */ set(31,0x001df5e0u);/* delay 001df5dc */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));set(2,dds3BillboardCopy(cpu(4)));
/* 001df5e0: lw v1,0x4(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001df5e4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df5e8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001df5ec: sw v1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001df5f0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df5f4: jr ra */ {uint64_t target=cpu(31);/* delay 001df5f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DF5C8(uint64_t a0){
set(4,a0);
return body_001df5c8();
}
static uint64_t body_001df600(void){
nocturneEffectAxisNoteEntry(0x001df600u);
uint64_t incoming=cpu(31);
/* 001df600: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001df604: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df608: move s0,a0 */ set(16,cpu(4));
/* 001df60c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df610: jal 0x0015af10 */ set(31,0x001df618u);/* delay 001df614 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));set(2,ps2BattleActionCreation_0015AF10(cpu(4)));
/* 001df618: lw v1,0x4(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001df61c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df620: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001df624: sw v1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001df628: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df62c: jr ra */ {uint64_t target=cpu(31);/* delay 001df630 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DF600(uint64_t a0){
set(4,a0);
return body_001df600();
}
static uint64_t body_001df638(void){
nocturneEffectAxisNoteEntry(0x001df638u);
uint64_t incoming=cpu(31);
/* 001df638: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 001df63c: lw a0,0xa8(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x000000a8)));
/* 001df640: beq a0,zero,0x001df664 */ {int taken=(cpu(4)==cpu(0));/* delay 001df644 */ set(2,cpu(0));if(taken){goto L_001df664;}}
/* 001df648: lh v1,0x4(a0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 001df64c: slt v1,a1,v1 */ set(3,(int64_t)cpu(5)<(int64_t)cpu(3));
/* 001df650: beq v1,zero,0x001df664 */ {int taken=(cpu(3)==cpu(0));/* delay 001df654 */ if(taken){goto L_001df664;}}
/* 001df658: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 001df65c: sll v0,a1,0x4 */ set(2,sx((uint32_t)cpu(5)<<4));
/* 001df660: addu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
L_001df664:;
/* 001df664: jr ra */ {uint64_t target=cpu(31);/* delay 001df668 */ checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_001DF638(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_001df638();
}
static void body_001df670(void){
nocturneEffectAxisNoteEntry(0x001df670u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001df670: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 001df674: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df678: move s0,a1 */ set(16,cpu(5));
/* 001df67c: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001df680: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001df684: move s5,a0 */ set(21,cpu(4));
/* 001df688: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001df68c: move s7,t0 */ set(23,cpu(8));
/* 001df690: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001df694: move s8,a3 */ set(30,cpu(7));
/* 001df698: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df69c: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001df6a0: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001df6a4: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001df6a8: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001df6ac: swc1 f20,0x60(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),f[20]);
/* 001df6b0: sw a2,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
/* 001df6b4: jal 0x001df638 */ set(31,0x001df6bcu);/* delay 001df6b8 */ set(5,half(ea(16,(int32_t)UINT32_C(0x0000000e))));body_001df638();
/* 001df6bc: move s4,v0 */ set(20,cpu(2));
/* 001df6c0: beql s4,zero,0x001df740 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 001df6c4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_001df740;}}
/* 001df6c8: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001df6cc: lw s6,0x18(s5) */ lw(22,ea(21,(int32_t)UINT32_C(0x00000018)));
/* 001df6d0: sltiu v0,v0,0x11 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000011));
/* 001df6d4: lw s3,0x8(s0) */ lw(19,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001df6d8: clear f20 */ f[20]=0;
/* 001df6dc: bne v0,zero,0x001df6e8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001df6e0 */ set(18,half(ea(16,(int32_t)UINT32_C(0x0000000c))));if(taken){goto L_001df6e8;}}
/* 001df6e4: lwc1 f20,0x10(s0) */ f[20]=word(ea(16,(int32_t)UINT32_C(0x00000010)));
L_001df6e8:;
/* 001df6e8: move a1,s3 */ set(5,cpu(19));
L_001df6ec:;
/* 001df6ec: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 001df6f0: jal 0x002b28f8 */ set(31,0x001df6f8u);/* delay 001df6f4 */ set(4,cpu(22));set(2,ps2ModelPositionFind(cpu(4),cpu(5)));
/* 001df6f8: move a0,s5 */ set(4,cpu(21));
/* 001df6fc: move s1,v0 */ set(17,cpu(2));
/* 001df700: move a1,s8 */ set(5,cpu(30));
/* 001df704: beq s1,zero,0x001df730 */ {int taken=(cpu(17)==cpu(0));/* delay 001df708 */ lw(6,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001df730;}}
/* 001df70c: jal 0x001df570 */ set(31,0x001df714u);/* delay 001df710 */ body_001df570();
/* 001df714: move a0,s4 */ set(4,cpu(20));
/* 001df718: jalr s7 */ {uint64_t target=cpu(23);set(31,0x001df720u);/* delay 001df71c */ set(16,cpu(2));switch((uint32_t)target){case 0x001df5c8u:body_001df5c8();break;case 0x001df600u:body_001df600();break;default:fprintf(stderr,"Unrecovered native model copy callback %08x\n",(uint32_t)target);abort();}}
/* 001df720: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001df724: sw s4,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(20));
/* 001df728: sw s1,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(17));
/* 001df72c: swc1 f20,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),f[20]);
L_001df730:;
/* 001df730: addiu s2,s2,-0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));
/* 001df734: bne s2,zero,0x001df6ec */ {int taken=(cpu(18)!=cpu(0));/* delay 001df738 */ set(5,cpu(19));if(taken){goto L_001df6ec;}}
/* 001df73c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
L_001df740:;
/* 001df740: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df744: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001df748: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001df74c: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001df750: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001df754: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001df758: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001df75c: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001df760: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001df764: lwc1 f20,0x60(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001df768: jr ra */ {uint64_t target=cpu(31);/* delay 001df76c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DF670(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
body_001df670();
}
static void body_001df770(void){
nocturneEffectAxisNoteEntry(0x001df770u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001df770: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 001df774: move v0,a1 */ set(2,cpu(5));
/* 001df778: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001df77c: li t6,0x3 */ set(14,sx(UINT32_C(0x00000003)));
/* 001df780: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001df784: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 001df788: lhu v1,0x10(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000010))));
/* 001df78c: lhu a3,0x12(v0) */ set(7,half(ea(2,(int32_t)UINT32_C(0x00000012))));
/* 001df790: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 001df794: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 001df798: lw v1,0x8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 001df79c: mtc1 a3,f0 */ f[0]=(uint32_t)cpu(7);
/* 001df7a0: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 001df7a4: lw a3,0xc(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 001df7a8: lbu t1,0x16(v0) */ set(9,byte(ea(2,(int32_t)UINT32_C(0x00000016))));
/* 001df7ac: lbu t2,0x17(v0) */ set(10,byte(ea(2,(int32_t)UINT32_C(0x00000017))));
/* 001df7b0: lw t7,0x24(v0) */ lw(15,ea(2,(int32_t)UINT32_C(0x00000024)));
/* 001df7b4: lw t3,0x18(v0) */ lw(11,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 001df7b8: lw t4,0x1c(v0) */ lw(12,ea(2,(int32_t)UINT32_C(0x0000001c)));
/* 001df7bc: lw t5,0x20(v0) */ lw(13,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 001df7c0: lhu t0,0x14(v0) */ set(8,half(ea(2,(int32_t)UINT32_C(0x00000014))));
/* 001df7c4: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001df7c8: sw v1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 001df7cc: sw a3,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(7));
/* 001df7d0: swc1 f1,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),f[1]);
/* 001df7d4: swc1 f0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[0]);
/* 001df7d8: sw t0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(8));
/* 001df7dc: sw t1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(9));
/* 001df7e0: sw t6,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(14));
/* 001df7e4: sw t2,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(10));
/* 001df7e8: sw t3,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(11));
/* 001df7ec: sw t4,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(12));
/* 001df7f0: sw t5,0x2c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(13));
/* 001df7f4: jal 0x001df570 */ set(31,0x001df7fcu);/* delay 001df7f8 */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(15));body_001df570();
/* 001df7fc: move a0,sp */ set(4,cpu(29));
/* 001df800: jal 0x001a2f38 */ set(31,0x001df808u);/* delay 001df804 */ set(16,cpu(2));set(2,ps2ModelTrackPolyCreate(cpu(4)));
/* 001df808: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001df80c: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001df810: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001df814: jr ra */ {uint64_t target=cpu(31);/* delay 001df818 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DF770(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_001df770();
}
static void body_001df820(void){
nocturneEffectAxisNoteEntry(0x001df820u);
uint64_t incoming=cpu(31);
/* 001df820: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001df824: move v0,a1 */ set(2,cpu(5));
/* 001df828: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df82c: lw t0,0x10(v0) */ lw(8,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 001df830: lhu a1,0x8(v0) */ set(5,half(ea(2,(int32_t)UINT32_C(0x00000008))));
/* 001df834: lhu a2,0xa(v0) */ set(6,half(ea(2,(int32_t)UINT32_C(0x0000000a))));
/* 001df838: lw a3,0xc(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 001df83c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df840: j 0x001dcd60 */ /* delay 001df844 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001dcd60();return;
}
void ps2BattleActionModel_001DF820(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_001df820();
}
static void body_001df848(void){
nocturneEffectAxisNoteEntry(0x001df848u);
uint64_t incoming=cpu(31);
/* 001df848: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001df84c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df850: move s0,a2 */ set(16,cpu(6));
/* 001df854: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df858: move s2,a1 */ set(18,cpu(5));
/* 001df85c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001df860: move s4,a0 */ set(20,cpu(4));
/* 001df864: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df868: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df86c: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001df870: jal 0x001df638 */ set(31,0x001df878u);/* delay 001df874 */ set(5,half(ea(18,(int32_t)UINT32_C(0x00000012))));body_001df638();
/* 001df878: beql v0,zero,0x001df8e8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001df87c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001df8e8;}}
/* 001df880: lw s1,0x8(v0) */ lw(17,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 001df884: lbu v0,0x8(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000008))));
/* 001df888: bnel v0,zero,0x001df8e8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001df88c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001df8e8;}}
/* 001df890: jal 0x002ac0d8 */ set(31,0x001df898u);/* delay 001df894 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000008)));set(2,ps2ModelResourceFind(cpu(4)));
/* 001df898: move a0,s4 */ set(4,cpu(20));
/* 001df89c: move s3,v0 */ set(19,cpu(2));
/* 001df8a0: move a2,s0 */ set(6,cpu(16));
/* 001df8a4: beq s3,zero,0x001df8e4 */ {int taken=(cpu(19)==cpu(0));/* delay 001df8a8 */ set(5,sx(UINT32_C(0x00000003)));if(taken){goto L_001df8e4;}}
/* 001df8ac: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
/* 001df8b0: jal 0x001df570 */ set(31,0x001df8b8u);/* delay 001df8b4 */ sb(ea(17,(int32_t)UINT32_C(0x00000008)),(uint8_t)cpu(16));body_001df570();
/* 001df8b8: sw s1,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(17));
/* 001df8bc: addiu a0,v0,0x18 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000018)));
/* 001df8c0: sw s3,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(19));
/* 001df8c4: sw s4,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));
/* 001df8c8: lw v1,0xc(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 001df8cc: sw v1,0x14(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 001df8d0: sb s0,0x1(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(16));
/* 001df8d4: lbu v0,0x11(s2) */ set(2,byte(ea(18,(int32_t)UINT32_C(0x00000011))));
/* 001df8d8: sb v0,0x2(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(2));
/* 001df8dc: lbu v1,0x10(s2) */ set(3,byte(ea(18,(int32_t)UINT32_C(0x00000010))));
/* 001df8e0: sb v1,0x3(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(3));
L_001df8e4:;
/* 001df8e4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001df8e8:;
/* 001df8e8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001df8ec: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001df8f0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001df8f4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001df8f8: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001df8fc: jr ra */ {uint64_t target=cpu(31);/* delay 001df900 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DF848(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_001df848();
}
static void body_001df968(void){
nocturneEffectAxisNoteEntry(0x001df968u);
uint64_t incoming=cpu(31);
/* 001df968: lw v1,0x0(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 001df96c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001df970: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 001df974: sltiu v0,v1,0x5 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 001df978: beq v0,zero,0x001df9f0 */ {int taken=(cpu(2)==cpu(0));/* delay 001df97c */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001df9f0;}}
/* 001df980: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 001df984: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 001df988: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001df98c: lw v1,-0x5890(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffa770)));
/* 001df990: jr v1 */ {uint64_t target=cpu(3);/* delay 001df994 */ switch((uint32_t)target){case 0x001df998u:goto L_001df998;case 0x001df9b0u:goto L_001df9b0;case 0x001df9c8u:goto L_001df9c8;case 0x001df9d8u:goto L_001df9d8;case 0x001df9e8u:goto L_001df9e8;default:fprintf(stderr,"Unexpected native model effect target %08x\n",(uint32_t)target);abort();}}
L_001df998:;
/* 001df998: lui t0,0x1e */ set(8,sx(UINT32_C(0x001e0000)));
/* 001df99c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df9a0: addiu t0,t0,-0xa38 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0xfffff5c8)));
/* 001df9a4: move a3,zero */ set(7,cpu(0));
/* 001df9a8: j 0x001df670 */ /* delay 001df9ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001df670();return;
L_001df9b0:;
/* 001df9b0: lui t0,0x1e */ set(8,sx(UINT32_C(0x001e0000)));
/* 001df9b4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df9b8: addiu t0,t0,-0xa00 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0xfffff600)));
/* 001df9bc: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 001df9c0: j 0x001df670 */ /* delay 001df9c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001df670();return;
L_001df9c8:;
/* 001df9c8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df9cc: j 0x001df770 */ /* delay 001df9d0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001df770();return;
L_001df9d8:;
/* 001df9d8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df9dc: j 0x001df820 */ /* delay 001df9e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001df820();return;
L_001df9e8:;
/* 001df9e8: jal 0x001df848 */ set(31,0x001df9f0u);/* delay 001df9ec */ body_001df848();
L_001df9f0:;
/* 001df9f0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001df9f4: jr ra */ {uint64_t target=cpu(31);/* delay 001df9f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DF968(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_001df968();
}
static void body_001dfa00(void){
nocturneEffectAxisNoteEntry(0x001dfa00u);
uint64_t incoming=cpu(31);
/* 001dfa00: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dfa04: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dfa08: move s1,a0 */ set(17,cpu(4));
/* 001dfa0c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dfa10: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dfa14: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dfa18: jal 0x001dea68 */ set(31,0x001dfa20u);/* delay 001dfa1c */ set(18,cpu(6));body_001dea68();
/* 001dfa20: beq v0,zero,0x001dfa64 */ {int taken=(cpu(2)==cpu(0));/* delay 001dfa24 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001dfa64;}}
/* 001dfa28: jal 0x001deae8 */ set(31,0x001dfa30u);/* delay 001dfa2c */ set(4,cpu(2));body_001deae8();
/* 001dfa30: move s0,v0 */ set(16,cpu(2));
/* 001dfa34: beql s0,zero,0x001dfa64 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 001dfa38 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001dfa64;}}
/* 001dfa3c: move a1,s0 */ set(5,cpu(16));
L_001dfa40:;
/* 001dfa40: move a2,s2 */ set(6,cpu(18));
/* 001dfa44: jal 0x001df968 */ set(31,0x001dfa4cu);/* delay 001dfa48 */ set(4,cpu(17));body_001df968();
/* 001dfa4c: jal 0x001deb00 */ set(31,0x001dfa54u);/* delay 001dfa50 */ set(4,cpu(16));body_001deb00();
/* 001dfa54: move s0,v0 */ set(16,cpu(2));
/* 001dfa58: bne s0,zero,0x001dfa40 */ {int taken=(cpu(16)!=cpu(0));/* delay 001dfa5c */ set(5,cpu(16));if(taken){goto L_001dfa40;}}
/* 001dfa60: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001dfa64:;
/* 001dfa64: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dfa68: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dfa6c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dfa70: jr ra */ {uint64_t target=cpu(31);/* delay 001dfa74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DFA00(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_001dfa00();
}
static void body_001dfa78(void){
nocturneEffectAxisNoteEntry(0x001dfa78u);
uint64_t incoming=cpu(31);
/* 001dfa78: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dfa7c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001dfa80: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dfa84: move s0,a0 */ set(16,cpu(4));
/* 001dfa88: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dfa8c: lhu v1,0x4(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000004))));
/* 001dfa90: beq v1,v0,0x001dfad0 */ {int taken=(cpu(3)==cpu(2));/* delay 001dfa94 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_001dfad0;}}
/* 001dfa98: beql a0,zero,0x001dfab0 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 001dfa9c */ set(2,sx(UINT32_C(0x00000002)));goto L_001dfab0;}}
/* 001dfaa0: beq v1,zero,0x001dfac0 */ {int taken=(cpu(3)==cpu(0));/* delay 001dfaa4 */ if(taken){goto L_001dfac0;}}
/* 001dfaa8: b 0x001dfaec */ /* delay 001dfaac */ set(4,cpu(16));goto L_001dfaec;
L_001dfab0:;
/* 001dfab0: beq v1,v0,0x001dfae0 */ {int taken=(cpu(3)==cpu(2));/* delay 001dfab4 */ if(taken){goto L_001dfae0;}}
/* 001dfab8: b 0x001dfaec */ /* delay 001dfabc */ set(4,cpu(16));goto L_001dfaec;
L_001dfac0:;
/* 001dfac0: jal 0x0015cf40 */ set(31,0x001dfac8u);/* delay 001dfac4 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));dds3BillboardDelete(cpu(4));
/* 001dfac8: b 0x001dfaec */ /* delay 001dfacc */ set(4,cpu(16));goto L_001dfaec;
L_001dfad0:;
/* 001dfad0: jal 0x0015ab58 */ set(31,0x001dfad8u);/* delay 001dfad4 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));dds3EffectDelete(cpu(4));
/* 001dfad8: b 0x001dfaec */ /* delay 001dfadc */ set(4,cpu(16));goto L_001dfaec;
L_001dfae0:;
/* 001dfae0: jal 0x001a3118 */ set(31,0x001dfae8u);/* delay 001dfae4 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));Eff_ModelTrackPolyDelete(cpu(4));
/* 001dfae8: move a0,s0 */ set(4,cpu(16));
L_001dfaec:;
/* 001dfaec: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dfaf0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dfaf4: j 0x002a8bd8 */ /* delay 001dfaf8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002a8bd8();return;
}
void ps2BattleActionModel_001DFA78(uint64_t a0){
set(4,a0);
body_001dfa78();
}
static void body_001dfb00(void){
nocturneEffectAxisNoteEntry(0x001dfb00u);
uint64_t incoming=cpu(31);
/* 001dfb00: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dfb04: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dfb08: addiu s1,a0,0x14 */ set(17,sx((uint32_t)cpu(4)+UINT32_C(0x00000014)));
/* 001dfb0c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dfb10: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dfb14: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dfb18: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001dfb1c: beq a0,zero,0x001dfb54 */ {int taken=(cpu(4)==cpu(0));/* delay 001dfb20 */ set(18,cpu(5));if(taken){goto L_001dfb54;}}
/* 001dfb24: lh v0,0x6(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000006))));
L_001dfb28:;
/* 001dfb28: bnel v0,s2,0x001dfb48 */ {int taken=(cpu(2)!=cpu(18));if(taken){/* delay 001dfb2c */ set(17,cpu(4));goto L_001dfb48;}}
/* 001dfb30: jal 0x001dfa78 */ set(31,0x001dfb38u);/* delay 001dfb34 */ lw(16,ea(4,(int32_t)UINT32_C(0x00000000)));body_001dfa78();
/* 001dfb38: move a0,s0 */ set(4,cpu(16));
/* 001dfb3c: b 0x001dfb4c */ /* delay 001dfb40 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));goto L_001dfb4c;
L_001dfb48:;
/* 001dfb48: lw a0,0x0(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000000)));
L_001dfb4c:;
/* 001dfb4c: bnel a0,zero,0x001dfb28 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 001dfb50 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000006))));goto L_001dfb28;}}
L_001dfb54:;
/* 001dfb54: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dfb58: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dfb5c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dfb60: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001dfb64: jr ra */ {uint64_t target=cpu(31);/* delay 001dfb68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_001DFB00(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_001dfb00();
}
static void body_002a8bd8(void){
nocturneEffectAxisNoteEntry(0x002a8bd8u);
uint64_t incoming=cpu(31);
/* 002a8bd8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002a8bdc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a8be0: move s2,a0 */ set(18,cpu(4));
/* 002a8be4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8be8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8bec: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8bf0: beq s2,zero,0x002a8cdc */ {int taken=(cpu(18)==cpu(0));/* delay 002a8bf4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002a8cdc;}}
/* 002a8bf8: lw v0,-0x2110(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdef0)));
/* 002a8bfc: lw a1,-0x2118(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffdee8)));
/* 002a8c00: subu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)-(uint32_t)cpu(2)));
/* 002a8c04: addiu a0,v0,0xfff */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000fff)));
/* 002a8c08: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 002a8c0c: movn v0,a0,v1 */ if(cpu(3)!=0){set(2,cpu(4));}
/* 002a8c10: sra v0,v0,0xc */ set(2,sx((uint32_t)((int32_t)cpu(2)>>12)));
/* 002a8c14: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 002a8c18: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002a8c1c: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 002a8c20: addu s0,a1,v1 */ set(16,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 002a8c24: jal 0x002e4070 */ set(31,0x002a8c2cu);/* delay 002a8c28 */ lw(17,ea(16,(int32_t)UINT32_C(0x0000000c)));set(2,ps2EffectKernelDisableInterrupts_002E4070());
/* 002a8c2c: lh a0,0x14(s0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 002a8c30: move s3,v0 */ set(19,cpu(2));
/* 002a8c34: addiu v0,a0,-0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 002a8c38: sll v1,v0,0x10 */ set(3,sx((uint32_t)cpu(2)<<16));
/* 002a8c3c: bne v1,zero,0x002a8ca8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002a8c40 */ sh(ea(16,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(2));if(taken){goto L_002a8ca8;}}
/* 002a8c44: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002a8c48: bne v0,s0,0x002a8c60 */ {int taken=(cpu(2)!=cpu(16));/* delay 002a8c4c */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));if(taken){goto L_002a8c60;}}
/* 002a8c50: jal 0x002a89c0 */ set(31,0x002a8c58u);/* delay 002a8c54 */ set(4,cpu(17));ps2EffectPoolAdvancePageList_002A89C0(cpu(4));
/* 002a8c58: b 0x002a8c98 */ /* delay 002a8c5c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdeec)));goto L_002a8c98;
L_002a8c60:;
/* 002a8c60: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002a8c64: beql v1,s0,0x002a8c90 */ {int taken=(cpu(3)==cpu(16));if(taken){/* delay 002a8c68 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002a8c90;}}
/* 002a8c6c: nop  */ 
L_002a8c70:;
/* 002a8c70: move a0,v1 */ set(4,cpu(3));
/* 002a8c74: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002a8c78: nop  */ 
/* 002a8c7c: nop  */ 
/* 002a8c80: nop  */ 
/* 002a8c84: bne v0,s0,0x002a8c70 */ {int taken=(cpu(2)!=cpu(16));/* delay 002a8c88 */ set(3,cpu(2));if(taken){goto L_002a8c70;}}
/* 002a8c8c: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
L_002a8c90:;
/* 002a8c90: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a8c94: lw v0,-0x2114(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdeec)));
L_002a8c98:;
/* 002a8c98: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002a8c9c: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a8ca0: b 0x002a8ccc */ /* delay 002a8ca4 */ sw(ea(28,(int32_t)UINT32_C(0xffffdeec)),(uint32_t)cpu(16));goto L_002a8ccc;
L_002a8ca8:;
/* 002a8ca8: lh v0,0xa(s1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000a))));
/* 002a8cac: bnel a0,v0,0x002a8cc4 */ {int taken=(cpu(4)!=cpu(2));if(taken){/* delay 002a8cb0 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));goto L_002a8cc4;}}
/* 002a8cb4: lw v0,0x4(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002a8cb8: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a8cbc: sw s0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002a8cc0: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
L_002a8cc4:;
/* 002a8cc4: sw v0,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002a8cc8: sw s2,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
L_002a8ccc:;
/* 002a8ccc: beq s3,zero,0x002a8ce0 */ {int taken=(cpu(19)==cpu(0));/* delay 002a8cd0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002a8ce0;}}
/* 002a8cd4: jal 0x002e40b8 */ set(31,0x002a8cdcu);/* delay 002a8cd8 */ set(2,ps2EffectKernelEnableInterrupts_002E40B8());
L_002a8cdc:;
/* 002a8cdc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002a8ce0:;
/* 002a8ce0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8ce4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a8ce8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8cec: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a8cf0: jr ra */ {uint64_t target=cpu(31);/* delay 002a8cf4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002A8BD8(uint64_t a0){
set(4,a0);
body_002a8bd8();
}
static uint64_t body_002a9158(void){
nocturneEffectAxisNoteEntry(0x002a9158u);
uint64_t incoming=cpu(31);
/* 002a9158: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002a915c: addiu a0,a0,0x7f */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000007f)));
/* 002a9160: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9164: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 002a9168: li v0,-0x80 */ set(2,sx(UINT32_C(0xffffff80)));
/* 002a916c: addiu s0,s0,0x7f18 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00007f18)));
/* 002a9170: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a9174: and s2,a0,v0 */ set(18,cpu(4)&cpu(2));
/* 002a9178: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a917c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a9180: li s4,0x2 */ set(20,sx(UINT32_C(0x00000002)));
/* 002a9184: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002a9188: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a918c: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002a9190: jal 0x002e4070 */ set(31,0x002a9198u);/* delay 002a9194 */ set(21,sx(UINT32_C(0x00000001)));set(2,ps2EffectKernelDisableInterrupts_002E4070());
/* 002a9198: lw s0,0x10(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002a919c: move s3,v0 */ set(19,cpu(2));
L_002a91a0:;
/* 002a91a0: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002a91a4: beql v0,zero,0x002a91f0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002a91a8 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a91f0;}}
/* 002a91ac: nop  */ 
/* 002a91b0: nop  */ 
/* 002a91b4: nop  */ 
/* 002a91b8: nop  */ 
/* 002a91bc: bnel v0,s4,0x002a91a0 */ {int taken=(cpu(2)!=cpu(20));if(taken){/* delay 002a91c0 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002a91a0;}}
/* 002a91c4: nop  */ 
/* 002a91c8: nop  */ 
/* 002a91cc: nop  */ 
/* 002a91d0: nop  */ 
/* 002a91d4: beql s3,zero,0x002a91a0 */ {int taken=(cpu(19)==cpu(0));if(taken){/* delay 002a91d8 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002a91a0;}}
/* 002a91dc: jal 0x002e40b8 */ set(31,0x002a91e4u);/* delay 002a91e0 */ set(2,ps2EffectKernelEnableInterrupts_002E40B8());
/* 002a91e4: b 0x002a91a0 */ /* delay 002a91e8 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002a91a0;
L_002a91f0:;
/* 002a91f0: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002a91f4: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 002a91f8: subu s1,v0,a0 */ set(17,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 002a91fc: slt v1,s1,s2 */ set(3,(int64_t)cpu(17)<(int64_t)cpu(18));
/* 002a9200: bnel v1,zero,0x002a91a0 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002a9204 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002a91a0;}}
/* 002a9208: slt v0,s2,s1 */ set(2,(int64_t)cpu(18)<(int64_t)cpu(17));
/* 002a920c: beq v0,zero,0x002a9250 */ {int taken=(cpu(2)==cpu(0));/* delay 002a9210 */ if(taken){goto L_002a9250;}}
/* 002a9214: jal 0x002a8af8 */ set(31,0x002a921cu);/* delay 002a9218 */ set(4,sx(UINT32_C(0x00000010)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002a921c: subu a1,s1,s2 */ set(5,sx((uint32_t)cpu(17)-(uint32_t)cpu(18)));
/* 002a9220: sw s0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002a9224: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002a9228: lw a0,0x4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002a922c: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 002a9230: sh zero,0xc(v0) */ sh(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(0));
/* 002a9234: sw a0,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002a9238: sw v1,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002a923c: lw a0,0x4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002a9240: sh zero,0xe(v0) */ sh(ea(2,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(0));
/* 002a9244: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a9248: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002a924c: move s0,v0 */ set(16,cpu(2));
L_002a9250:;
/* 002a9250: beq s3,zero,0x002a9260 */ {int taken=(cpu(19)==cpu(0));/* delay 002a9254 */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(21));if(taken){goto L_002a9260;}}
/* 002a9258: jal 0x002e40b8 */ set(31,0x002a9260u);/* delay 002a925c */ set(2,ps2EffectKernelEnableInterrupts_002E40B8());
L_002a9260:;
/* 002a9260: move v0,s0 */ set(2,cpu(16));
/* 002a9264: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9268: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a926c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a9270: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a9274: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a9278: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002a927c: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002a9280: jr ra */ {uint64_t target=cpu(31);/* delay 002a9284 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_002A9158(uint64_t a0){
set(4,a0);
return body_002a9158();
}
static uint64_t body_002a9540(void){
nocturneEffectAxisNoteEntry(0x002a9540u);
uint64_t incoming=cpu(31);
/* 002a9540: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 002a9544: lw v1,0x4(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 002a9548: sw a0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002a954c: jr ra */ {uint64_t target=cpu(31);/* delay 002a9550 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_002A9540(uint64_t a0){
set(4,a0);
return body_002a9540();
}
static void body_002a9558(void){
nocturneEffectAxisNoteEntry(0x002a9558u);
uint64_t incoming=cpu(31);
/* 002a9558: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002a955c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9560: move s0,a0 */ set(16,cpu(4));
/* 002a9564: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9568: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a956c: beq s0,zero,0x002a95e0 */ {int taken=(cpu(16)==cpu(0));/* delay 002a9570 */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002a95e0;}}
/* 002a9574: jal 0x002e4070 */ set(31,0x002a957cu);/* delay 002a9578 */ set(2,ps2EffectKernelDisableInterrupts_002E4070());
/* 002a957c: lw s1,0x4(s0) */ lw(17,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002a9580: move s2,v0 */ set(18,cpu(2));
/* 002a9584: lhu v0,0xc(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002a9588: bne v0,zero,0x002a95a0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002a958c */ set(4,cpu(16));if(taken){goto L_002a95a0;}}
/* 002a9590: jal 0x002a9540 */ set(31,0x002a9598u);/* delay 002a9594 */ body_002a9540();
/* 002a9598: jal 0x002a8bd8 */ set(31,0x002a95a0u);/* delay 002a959c */ set(4,cpu(17));body_002a8bd8();
L_002a95a0:;
/* 002a95a0: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002a95a4: lhu v0,0xc(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000c))));
/* 002a95a8: bne v0,zero,0x002a95c8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002a95ac */ set(4,cpu(3));if(taken){goto L_002a95c8;}}
/* 002a95b0: jal 0x002a9540 */ set(31,0x002a95b8u);/* delay 002a95b4 */ body_002a9540();
/* 002a95b8: jal 0x002a8bd8 */ set(31,0x002a95c0u);/* delay 002a95bc */ set(4,cpu(16));body_002a8bd8();
/* 002a95c0: b 0x002a95d0 */ /* delay 002a95c4 */ goto L_002a95d0;
L_002a95c8:;
/* 002a95c8: sh zero,0xe(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(0));
/* 002a95cc: sh zero,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(0));
L_002a95d0:;
/* 002a95d0: beq s2,zero,0x002a95e4 */ {int taken=(cpu(18)==cpu(0));/* delay 002a95d4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002a95e4;}}
/* 002a95d8: jal 0x002e40b8 */ set(31,0x002a95e0u);/* delay 002a95dc */ set(2,ps2EffectKernelEnableInterrupts_002E40B8());
L_002a95e0:;
/* 002a95e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002a95e4:;
/* 002a95e4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a95e8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a95ec: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a95f0: jr ra */ {uint64_t target=cpu(31);/* delay 002a95f4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002A9558(uint64_t a0){
set(4,a0);
body_002a9558();
}
static void body_002a9618(void){
nocturneEffectAxisNoteEntry(0x002a9618u);
uint64_t incoming=cpu(31);
/* 002a9618: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a961c: move v1,a0 */ set(3,cpu(4));
/* 002a9620: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9624: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002a9628: beq v0,zero,0x002a9640 */ {int taken=(cpu(2)==cpu(0));/* delay 002a962c */ set(4,cpu(2));if(taken){goto L_002a9640;}}
/* 002a9630: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9634: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002a9638: j 0x002a9558 */ /* delay 002a963c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002a9558();return;
L_002a9640:;
/* 002a9640: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9644: jr ra */ {uint64_t target=cpu(31);/* delay 002a9648 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002A9618(uint64_t a0){
set(4,a0);
body_002a9618();
}
static void body_002a9650(void){
nocturneEffectAxisNoteEntry(0x002a9650u);
uint64_t incoming=cpu(31);
/* 002a9650: move v0,a0 */ set(2,cpu(4));
/* 002a9654: addiu a0,gp,-0x20f8 */ set(4,sx((uint32_t)cpu(28)+UINT32_C(0xffffdf08)));
/* 002a9658: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a965c: move a1,v0 */ set(5,cpu(2));
/* 002a9660: beq v0,zero,0x002a9678 */ {int taken=(cpu(2)==cpu(0));/* delay 002a9664 */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002a9678;}}
/* 002a9668: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a966c: j 0x002ac7b0 */ /* delay 002a9670 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002ac7b0();return;
L_002a9678:;
/* 002a9678: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a967c: jr ra */ {uint64_t target=cpu(31);/* delay 002a9680 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002A9650(uint64_t a0){
set(4,a0);
body_002a9650();
}
static void body_002ab308(void){
nocturneEffectAxisNoteEntry(0x002ab308u);
uint64_t incoming=cpu(31);
/* 002ab308: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ab30c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab310: move s0,a0 */ set(16,cpu(4));
/* 002ab314: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab318: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 002ab31c: beql v0,zero,0x002ab350 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002ab320 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002ab350;}}
/* 002ab324: jal 0x002aaff8 */ set(31,0x002ab32cu);/* delay 002ab328 */ set(2,ps2EffectTexturePaletteAddress_002AAFF8(cpu(4)));
/* 002ab32c: move a0,s0 */ set(4,cpu(16));
/* 002ab330: lw a2,0x30(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000030)));
/* 002ab334: move a1,v0 */ set(5,cpu(2));
/* 002ab338: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab33c: move a3,zero */ set(7,cpu(0));
/* 002ab340: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab344: j 0x002ab2b0 */ /* delay 002ab348 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);set(2,ps2BattleActionTexture_002AB2B0(cpu(4),cpu(5),cpu(6),cpu(7)));return;
L_002ab350:;
/* 002ab350: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab354: jr ra */ {uint64_t target=cpu(31);/* delay 002ab358 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002AB308(uint64_t a0){
set(4,a0);
body_002ab308();
}
static uint64_t body_002ab448(void){
nocturneEffectAxisNoteEntry(0x002ab448u);
uint64_t incoming=cpu(31);
/* 002ab448: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002ab44c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ab450: move s2,a0 */ set(18,cpu(4));
/* 002ab454: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab458: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab45c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ab460: jal 0x002a8af8 */ set(31,0x002ab468u);/* delay 002ab464 */ set(4,sx(UINT32_C(0x00000040)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002ab468: move s0,v0 */ set(16,cpu(2));
/* 002ab46c: ldl v0,0x7(s2) */ loadPartial(2,ea(18,(int32_t)UINT32_C(0x00000007)),1);
/* 002ab470: ldr v0,0x0(s2) */ loadPartial(2,ea(18,(int32_t)UINT32_C(0x00000000)),0);
/* 002ab474: ldl v1,0xf(s2) */ loadPartial(3,ea(18,(int32_t)UINT32_C(0x0000000f)),1);
/* 002ab478: ldr v1,0x8(s2) */ loadPartial(3,ea(18,(int32_t)UINT32_C(0x00000008)),0);
/* 002ab47c: ldl a0,0x17(s2) */ loadPartial(4,ea(18,(int32_t)UINT32_C(0x00000017)),1);
/* 002ab480: ldr a0,0x10(s2) */ loadPartial(4,ea(18,(int32_t)UINT32_C(0x00000010)),0);
/* 002ab484: ldl a1,0x1f(s2) */ loadPartial(5,ea(18,(int32_t)UINT32_C(0x0000001f)),1);
/* 002ab488: ldr a1,0x18(s2) */ loadPartial(5,ea(18,(int32_t)UINT32_C(0x00000018)),0);
/* 002ab48c: sdl v0,0x7(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000007)),2,1);
/* 002ab490: sdr v0,0x0(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000000)),2,0);
/* 002ab494: sdl v1,0xf(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000000f)),3,1);
/* 002ab498: sdr v1,0x8(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000008)),3,0);
/* 002ab49c: sdl a0,0x17(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000017)),4,1);
/* 002ab4a0: sdr a0,0x10(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000010)),4,0);
/* 002ab4a4: sdl a1,0x1f(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000001f)),5,1);
/* 002ab4a8: sdr a1,0x18(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000018)),5,0);
/* 002ab4ac: ldl v0,0x27(s2) */ loadPartial(2,ea(18,(int32_t)UINT32_C(0x00000027)),1);
/* 002ab4b0: ldr v0,0x20(s2) */ loadPartial(2,ea(18,(int32_t)UINT32_C(0x00000020)),0);
/* 002ab4b4: ldl v1,0x2f(s2) */ loadPartial(3,ea(18,(int32_t)UINT32_C(0x0000002f)),1);
/* 002ab4b8: ldr v1,0x28(s2) */ loadPartial(3,ea(18,(int32_t)UINT32_C(0x00000028)),0);
/* 002ab4bc: ldl a0,0x37(s2) */ loadPartial(4,ea(18,(int32_t)UINT32_C(0x00000037)),1);
/* 002ab4c0: ldr a0,0x30(s2) */ loadPartial(4,ea(18,(int32_t)UINT32_C(0x00000030)),0);
/* 002ab4c4: ldl a1,0x3f(s2) */ loadPartial(5,ea(18,(int32_t)UINT32_C(0x0000003f)),1);
/* 002ab4c8: ldr a1,0x38(s2) */ loadPartial(5,ea(18,(int32_t)UINT32_C(0x00000038)),0);
/* 002ab4cc: sdl v0,0x27(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000027)),2,1);
/* 002ab4d0: sdr v0,0x20(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000020)),2,0);
/* 002ab4d4: sdl v1,0x2f(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000002f)),3,1);
/* 002ab4d8: sdr v1,0x28(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000028)),3,0);
/* 002ab4dc: sdl a0,0x37(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000037)),4,1);
/* 002ab4e0: sdr a0,0x30(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000030)),4,0);
/* 002ab4e4: sdl a1,0x3f(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000003f)),5,1);
/* 002ab4e8: sdr a1,0x38(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000038)),5,0);
/* 002ab4ec: lw s1,0x8(s0) */ lw(17,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002ab4f0: bne s1,zero,0x002ab500 */ {int taken=(cpu(17)!=cpu(0));/* delay 002ab4f4 */ set(4,cpu(16));if(taken){goto L_002ab500;}}
/* 002ab4f8: move s1,s2 */ set(17,cpu(18));
/* 002ab4fc: sw s1,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));
L_002ab500:;
/* 002ab500: sw zero,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 002ab504: sw zero,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(0));
/* 002ab508: sw zero,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));
/* 002ab50c: jal 0x002ab360 */ set(31,0x002ab514u);/* delay 002ab510 */ sw(ea(16,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));ps2BattleActionTexture_002AB360(cpu(4));
/* 002ab514: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 002ab518: beq v0,zero,0x002ab554 */ {int taken=(cpu(2)==cpu(0));/* delay 002ab51c */ if(taken){goto L_002ab554;}}
/* 002ab520: lbu a1,0x19(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x00000019))));
/* 002ab524: lbu a2,0x18(s0) */ set(6,byte(ea(16,(int32_t)UINT32_C(0x00000018))));
/* 002ab528: jal 0x002ab580 */ set(31,0x002ab530u);/* delay 002ab52c */ set(4,byte(ea(16,(int32_t)UINT32_C(0x0000001a))));set(2,ps2BattleActionTexture_002AB580(cpu(4),cpu(5),cpu(6)));
/* 002ab530: move a0,s0 */ set(4,cpu(16));
/* 002ab534: jal 0x002ab688 */ set(31,0x002ab53cu);/* delay 002ab538 */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));ps2BattleActionTexture_002AB688(cpu(4));
/* 002ab53c: move a0,s0 */ set(4,cpu(16));
/* 002ab540: jal 0x002ab6c8 */ set(31,0x002ab548u);/* delay 002ab544 */ lw(5,ea(17,(int32_t)UINT32_C(0x00000030)));set(2,ps2BattleActionTexture_002AB6C8(cpu(4),cpu(5)));
/* 002ab548: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
/* 002ab54c: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 002ab550: sw v0,0x38(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(2));
L_002ab554:;
/* 002ab554: jal 0x002abb18 */ set(31,0x002ab55cu);/* delay 002ab558 */ set(4,cpu(16));ps2BattleActionTexture_002ABB18(cpu(4));
/* 002ab55c: jal 0x002ab308 */ set(31,0x002ab564u);/* delay 002ab560 */ set(4,cpu(16));body_002ab308();
/* 002ab564: move v0,s0 */ set(2,cpu(16));
/* 002ab568: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab56c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab570: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ab574: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ab578: jr ra */ {uint64_t target=cpu(31);/* delay 002ab57c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_002AB448(uint64_t a0){
set(4,a0);
return body_002ab448();
}
static void body_002ab8f0(void){
nocturneEffectAxisNoteEntry(0x002ab8f0u);
uint64_t incoming=cpu(31);
/* 002ab8f0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ab8f4: move a1,a0 */ set(5,cpu(4));
/* 002ab8f8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab8fc: addiu a0,gp,-0x20d0 */ set(4,sx((uint32_t)cpu(28)+UINT32_C(0xffffdf30)));
/* 002ab900: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab904: j 0x002ac7b0 */ /* delay 002ab908 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002ac7b0();return;
}
void ps2BattleActionModel_002AB8F0(uint64_t a0){
set(4,a0);
body_002ab8f0();
}
static void body_002ac7b0(void){
nocturneEffectAxisNoteEntry(0x002ac7b0u);
uint64_t incoming=cpu(31);
/* 002ac7b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002ac7b4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac7b8: move s2,a1 */ set(18,cpu(5));
/* 002ac7bc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac7c0: move s1,a0 */ set(17,cpu(4));
/* 002ac7c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac7c8: beq s2,zero,0x002ac868 */ {int taken=(cpu(18)==cpu(0));/* delay 002ac7cc */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002ac868;}}
/* 002ac7d0: jal 0x002dbee0 */ set(31,0x002ac7d8u);/* delay 002ac7d4 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd6f4)));waitSemaphore();
/* 002ac7d8: lw s0,0x4(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002ac7dc: bne s0,zero,0x002ac80c */ {int taken=(cpu(16)!=cpu(0));/* delay 002ac7e0 */ set(4,sx(UINT32_C(0x00000010)));if(taken){goto L_002ac80c;}}
/* 002ac7e4: jal 0x002a8af8 */ set(31,0x002ac7ecu);/* delay 002ac7e8 */ set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002ac7ec: move s0,v0 */ set(16,cpu(2));
/* 002ac7f0: lw v0,-0x20c0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdf40)));
/* 002ac7f4: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002ac7f8: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002ac7fc: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002ac800: sw s0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002ac804: sw s1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 002ac808: sw s0,-0x20c0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdf40)),(uint32_t)cpu(16));
L_002ac80c:;
/* 002ac80c: lw a1,0xc(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002ac810: bne a1,zero,0x002ac830 */ {int taken=(cpu(5)!=cpu(0));/* delay 002ac814 */ lw(17,ea(16,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002ac830;}}
/* 002ac818: jal 0x002a8af8 */ set(31,0x002ac820u);/* delay 002ac81c */ set(4,sx(UINT32_C(0x00000100)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002ac820: li a1,0x3f */ set(5,sx(UINT32_C(0x0000003f)));
/* 002ac824: sw s1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002ac828: move s1,v0 */ set(17,cpu(2));
/* 002ac82c: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_002ac830:;
/* 002ac830: li v0,0x3f */ set(2,sx(UINT32_C(0x0000003f)));
/* 002ac834: addiu v1,a1,-0x1 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 002ac838: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 002ac83c: lw a0,-0x290c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd6f4)));
/* 002ac840: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002ac844: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ac848: addu v0,s1,v0 */ set(2,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 002ac84c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac850: sw s2,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(18));
/* 002ac854: sw v1,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 002ac858: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac85c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac860: j 0x002dbec0 */ /* delay 002ac864 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);signalSemaphore();return;
L_002ac868:;
/* 002ac868: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ac86c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ac870: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ac874: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ac878: jr ra */ {uint64_t target=cpu(31);/* delay 002ac87c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002AC7B0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002ac7b0();
}
static void body_002b0648(void){
nocturneEffectAxisNoteEntry(0x002b0648u);
uint64_t incoming=cpu(31);
/* 002b0648: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b064c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b0650: move s0,a0 */ set(16,cpu(4));
/* 002b0654: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b0658: move s1,a1 */ set(17,cpu(5));
/* 002b065c: beq s0,zero,0x002b06b8 */ {int taken=(cpu(16)==cpu(0));/* delay 002b0660 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002b06b8;}}
/* 002b0664: beql a2,zero,0x002b067c */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 002b0668 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));goto L_002b067c;}}
/* 002b066c: lw a0,0xc(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002b0670: jal 0x002b2db0 */ set(31,0x002b0678u);/* delay 002b0674 */ set(5,sx(UINT32_C(0x00000001)));body_002b2db0();
/* 002b0678: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
L_002b067c:;
/* 002b067c: beq v0,zero,0x002b068c */ {int taken=(cpu(2)==cpu(0));/* delay 002b0680 */ set(4,cpu(2));if(taken){goto L_002b068c;}}
/* 002b0684: jal 0x002bfee8 */ set(31,0x002b068cu);/* delay 002b0688 */ body_002bfee8();
L_002b068c:;
/* 002b068c: beq s1,zero,0x002b06a8 */ {int taken=(cpu(17)==cpu(0));/* delay 002b0690 */ if(taken){goto L_002b06a8;}}
/* 002b0694: addiu a0,gp,-0x20b8 */ set(4,sx((uint32_t)cpu(28)+UINT32_C(0xffffdf48)));
/* 002b0698: jal 0x002ac7b0 */ set(31,0x002b06a0u);/* delay 002b069c */ set(5,cpu(16));body_002ac7b0();
/* 002b06a0: b 0x002b06bc */ /* delay 002b06a4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002b06bc;
L_002b06a8:;
/* 002b06a8: jal 0x002bfee8 */ set(31,0x002b06b0u);/* delay 002b06ac */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));body_002bfee8();
/* 002b06b0: jal 0x002a8bd8 */ set(31,0x002b06b8u);/* delay 002b06b4 */ set(4,cpu(16));body_002a8bd8();
L_002b06b8:;
/* 002b06b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002b06bc:;
/* 002b06bc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b06c0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b06c4: jr ra */ {uint64_t target=cpu(31);/* delay 002b06c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002B0648(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
body_002b0648();
}
static uint64_t body_002b2a60(void){
nocturneEffectAxisNoteEntry(0x002b2a60u);
uint64_t incoming=cpu(31);
/* 002b2a60: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b2a64: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 002b2a68: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2a6c: li a2,0x4 */ set(6,sx(UINT32_C(0x00000004)));
/* 002b2a70: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2a74: j 0x002bfe58 */ /* delay 002b2a78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);set(2,ps2EffectArrayCreate_002BFE58(cpu(4),cpu(5),cpu(6)));return cpu(2);
}
uint64_t ps2BattleActionModel_002B2A60(uint64_t a0){
set(4,a0);
return body_002b2a60();
}
static void body_002b2a80(void){
nocturneEffectAxisNoteEntry(0x002b2a80u);
uint64_t incoming=cpu(31);
/* 002b2a80: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b2a84: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b2a88: move s1,a0 */ set(17,cpu(4));
/* 002b2a8c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2a90: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2a94: beq s1,zero,0x002b2af8 */ {int taken=(cpu(17)==cpu(0));/* delay 002b2a98 */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002b2af8;}}
/* 002b2a9c: beql a1,zero,0x002b2adc */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 002b2aa0 */ set(4,cpu(17));goto L_002b2adc;}}
/* 002b2aa4: lh s2,0x4(s1) */ set(18,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 002b2aa8: blez s2,0x002b2ad8 */ {int taken=((int64_t)cpu(18)<=0);/* delay 002b2aac */ set(16,cpu(0));if(taken){goto L_002b2ad8;}}
/* 002b2ab0: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002b2ab4: nop  */ 
L_002b2ab8:;
/* 002b2ab8: sll v1,s0,0x2 */ set(3,sx((uint32_t)cpu(16)<<2));
/* 002b2abc: addiu s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
/* 002b2ac0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002b2ac4: jal 0x002ab8f0 */ set(31,0x002b2accu);/* delay 002b2ac8 */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));body_002ab8f0();
/* 002b2acc: slt v0,s0,s2 */ set(2,(int64_t)cpu(16)<(int64_t)cpu(18));
/* 002b2ad0: bnel v0,zero,0x002b2ab8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002b2ad4 */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));goto L_002b2ab8;}}
L_002b2ad8:;
/* 002b2ad8: move a0,s1 */ set(4,cpu(17));
L_002b2adc:;
/* 002b2adc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b2ae0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2ae4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2ae8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b2aec: j 0x002bfee8 */ /* delay 002b2af0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002bfee8();return;
L_002b2af8:;
/* 002b2af8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2afc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b2b00: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2b04: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b2b08: jr ra */ {uint64_t target=cpu(31);/* delay 002b2b0c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002B2A80(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002b2a80();
}
static void body_002b2b10(void){
nocturneEffectAxisNoteEntry(0x002b2b10u);
uint64_t incoming=cpu(31);
/* 002b2b10: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b2b14: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2b18: move s0,a0 */ set(16,cpu(4));
/* 002b2b1c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b2b20: move s1,a1 */ set(17,cpu(5));
/* 002b2b24: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2b28: lh v0,0x4(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000004))));
/* 002b2b2c: lh v1,0x6(s0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 002b2b30: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 002b2b34: bne v0,zero,0x002b2b48 */ {int taken=(cpu(2)!=cpu(0));/* delay 002b2b38 */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000004))));if(taken){goto L_002b2b48;}}
/* 002b2b3c: jal 0x002bff18 */ set(31,0x002b2b44u);/* delay 002b2b40 */ ps2EffectArrayGrow_002BFF18(cpu(4));
/* 002b2b44: lhu a1,0x4(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000004))));
L_002b2b48:;
/* 002b2b48: lw v1,0xc(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002b2b4c: sll v0,a1,0x10 */ set(2,sx((uint32_t)cpu(5)<<16));
/* 002b2b50: sra v0,v0,0xe */ set(2,sx((uint32_t)((int32_t)cpu(2)>>14)));
/* 002b2b54: addiu a0,a1,0x1 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002b2b58: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002b2b5c: sh a0,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(4));
/* 002b2b60: sw s1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002b2b64: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2b68: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b2b6c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2b70: jr ra */ {uint64_t target=cpu(31);/* delay 002b2b74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002B2B10(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002b2b10();
}
static uint64_t body_002b2bd0(void){
nocturneEffectAxisNoteEntry(0x002b2bd0u);
uint64_t incoming=cpu(31);
/* 002b2bd0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002b2bd4: move v0,zero */ set(2,cpu(0));
/* 002b2bd8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b2bdc: move s4,a0 */ set(20,cpu(4));
/* 002b2be0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2be4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b2be8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2bec: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b2bf0: beq s4,zero,0x002b2c44 */ {int taken=(cpu(20)==cpu(0));/* delay 002b2bf4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_002b2c44;}}
/* 002b2bf8: lh s2,0x4(s4) */ set(18,(uint64_t)(int64_t)(int16_t)half(ea(20,(int32_t)UINT32_C(0x00000004))));
/* 002b2bfc: move s1,zero */ set(17,cpu(0));
/* 002b2c00: jal 0x002b2a60 */ set(31,0x002b2c08u);/* delay 002b2c04 */ set(4,cpu(18));body_002b2a60();
/* 002b2c08: blez s2,0x002b2c3c */ {int taken=((int64_t)cpu(18)<=0);/* delay 002b2c0c */ set(19,cpu(2));if(taken){goto L_002b2c3c;}}
L_002b2c10:;
/* 002b2c10: lw v0,0xc(s4) */ lw(2,ea(20,(int32_t)UINT32_C(0x0000000c)));
/* 002b2c14: sll s0,s1,0x2 */ set(16,sx((uint32_t)cpu(17)<<2));
/* 002b2c18: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 002b2c1c: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002b2c20: jal 0x002ab448 */ set(31,0x002b2c28u);/* delay 002b2c24 */ lw(4,ea(2,(int32_t)UINT32_C(0x00000000)));body_002ab448();
/* 002b2c28: lw v1,0xc(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 002b2c2c: slt a0,s1,s2 */ set(4,(int64_t)cpu(17)<(int64_t)cpu(18));
/* 002b2c30: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 002b2c34: bne a0,zero,0x002b2c10 */ {int taken=(cpu(4)!=cpu(0));/* delay 002b2c38 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_002b2c10;}}
L_002b2c3c:;
/* 002b2c3c: sh s2,0x4(s3) */ sh(ea(19,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(18));
/* 002b2c40: move v0,s3 */ set(2,cpu(19));
L_002b2c44:;
/* 002b2c44: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2c48: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b2c4c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b2c50: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b2c54: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b2c58: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002b2c5c: jr ra */ {uint64_t target=cpu(31);/* delay 002b2c60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionModel_002B2BD0(uint64_t a0){
set(4,a0);
return body_002b2bd0();
}
static void body_002b2db0(void){
nocturneEffectAxisNoteEntry(0x002b2db0u);
uint64_t incoming=cpu(31);
/* 002b2db0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b2db4: move v0,a0 */ set(2,cpu(4));
/* 002b2db8: beq v0,zero,0x002b2de8 */ {int taken=(cpu(2)==cpu(0));/* delay 002b2dbc */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002b2de8;}}
/* 002b2dc0: beq a1,zero,0x002b2de0 */ {int taken=(cpu(5)==cpu(0));/* delay 002b2dc4 */ if(taken){goto L_002b2de0;}}
/* 002b2dc8: addiu a0,gp,-0x20b0 */ set(4,sx((uint32_t)cpu(28)+UINT32_C(0xffffdf50)));
/* 002b2dcc: jal 0x002ac7b0 */ set(31,0x002b2dd4u);/* delay 002b2dd0 */ set(5,cpu(2));body_002ac7b0();
/* 002b2dd4: b 0x002b2dec */ /* delay 002b2dd8 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002b2dec;
L_002b2de0:;
/* 002b2de0: jal 0x002bfee8 */ set(31,0x002b2de8u);/* delay 002b2de4 */ body_002bfee8();
L_002b2de8:;
/* 002b2de8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002b2dec:;
/* 002b2dec: jr ra */ {uint64_t target=cpu(31);/* delay 002b2df0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002B2DB0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_002b2db0();
}
static void body_002bfee8(void){
nocturneEffectAxisNoteEntry(0x002bfee8u);
uint64_t incoming=cpu(31);
/* 002bfee8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002bfeec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bfef0: move s0,a0 */ set(16,cpu(4));
/* 002bfef4: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bfef8: jal 0x002a9558 */ set(31,0x002bff00u);/* delay 002bfefc */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));body_002a9558();
/* 002bff00: move a0,s0 */ set(4,cpu(16));
/* 002bff04: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bff08: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bff0c: j 0x002a8bd8 */ /* delay 002bff10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002a8bd8();return;
}
void ps2BattleActionModel_002BFEE8(uint64_t a0){
set(4,a0);
body_002bfee8();
}
static void body_002c0600(void){
nocturneEffectAxisNoteEntry(0x002c0600u);
uint64_t incoming=cpu(31);
/* 002c0600: vaddw.xyz vf1,vf0,vf0 */ quatValue(1,0,0,14,3,0);
/* 002c0604: vadd.xyzw vf2,vf10,vf10 */ quatValue(2,10,10,15,4,0);
/* 002c0608: vmulx.w vf28,vf0,vf0 */ quatValue(28,0,0,1,0,2);
/* 002c060c: vmulx.w vf29,vf0,vf0 */ quatValue(29,0,0,1,0,2);
/* 002c0610: vmulx.w vf30,vf0,vf0 */ quatValue(30,0,0,1,0,2);
/* 002c0614: vmul.xyzw vf3,vf10,vf2 */ quatValue(3,10,2,15,4,2);
/* 002c0618: vmuly.xyzw vf4,vf10,vf2 */ quatValue(4,10,2,15,1,2);
/* 002c061c: vmulz.xyzw vf5,vf10,vf2 */ quatValue(5,10,2,15,2,2);
/* 002c0620: vmulx.xyzw vf6,vf10,vf2 */ modelMul(6,10,2);
/* 002c0624: vaddaw.xyz ACC,vf0,vf0 */ quatAccum(32,0,0,14,3,0);
/* 002c0628: vmsubay.x ACC,vf1,vf3 */ quatAccum(32,1,3,8,1,3);
/* 002c062c: vmsubz.x vf28,vf1,vf3 */ quatAccum(28,1,3,8,2,3);
/* 002c0630: vmsubax.y ACC,vf1,vf3 */ quatAccum(32,1,3,4,0,3);
/* 002c0634: vmsubz.y vf29,vf1,vf3 */ quatAccum(29,1,3,4,2,3);
/* 002c0638: vmsubax.z ACC,vf1,vf3 */ quatAccum(32,1,3,2,0,3);
/* 002c063c: vmsuby.z vf30,vf1,vf3 */ quatAccum(30,1,3,2,1,3);
/* 002c0640: vmulax.y ACC,vf1,vf4 */ quatAccum(32,1,4,4,0,1);
/* 002c0644: vmsubw.y vf28,vf1,vf5 */ quatAccum(28,1,5,4,3,3);
/* 002c0648: vaddw.x vf29,vf4,vf5 */ quatValue(29,4,5,8,3,0);
/* 002c064c: vsubw.x vf30,vf5,vf4 */ quatValue(30,5,4,8,3,1);
/* 002c0650: vmulax.z ACC,vf1,vf5 */ quatAccum(32,1,5,2,0,1);
/* 002c0654: vmaddw.z vf28,vf1,vf4 */ quatAccum(28,1,4,2,3,2);
/* 002c0658: vmulay.z ACC,vf1,vf5 */ quatAccum(32,1,5,2,1,1);
/* 002c065c: vmsubw.z vf29,vf1,vf6 */ quatAccum(29,1,6,2,3,3);
/* 002c0660: vaddw.y vf30,vf5,vf6 */ quatValue(30,5,6,4,3,0);
/* 002c0664: vmove.xyzw vf31,vf0 */ moveVu(31,0);
/* 002c0668: jr ra */ {uint64_t target=cpu(31);/* delay 002c066c */ checkReturn(target,incoming);return;}
}
void ps2BattleActionModel_002C0600(void){

body_002c0600();
}
