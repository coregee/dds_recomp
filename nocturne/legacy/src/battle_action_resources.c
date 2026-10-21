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
static uint32_t add(uint32_t a,uint32_t b){return EE_FPU_ADD_S(a,b);}
static uint32_t mul(uint32_t a,uint32_t b){return EE_FPU_MUL_S(a,b);}
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
static void pextuw(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4];nocturneEffectHostCpuRead(s,x);nocturneEffectHostCpuRead(t,y);z[0]=y[2];z[1]=x[2];z[2]=y[3];z[3]=x[3];nocturneEffectHostCpuWrite(d,z);}
static void vuMul(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);for(unsigned k=0;k<4;k++)z[k]=(uint32_t)EE_ROT_VU_MUL(x[k],y[k]);EE_ROT_VU_WRITE(d,z);}
static void vuMula(unsigned s,unsigned t,unsigned c){uint32_t x[4],y[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++){uint64_t v=EE_ROT_VU_MUL(x[k],y[c]);a[k]=(uint32_t)v;o[k]=(uint32_t)(v>>32)&1u;}EE_ROT_ACC_WRITE(a,o);}
static void vuMadda(unsigned s,unsigned t,unsigned c){uint32_t x[4],y[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++){uint64_t v=EE_ROT_VU_MAC(a[k],x[k],y[c],o[k],0);a[k]=(uint32_t)v;o[k]=(uint32_t)(v>>32)&1u;}EE_ROT_ACC_WRITE(a,o);}
static void vuMadd(unsigned d,unsigned s,unsigned t,unsigned c){uint32_t x[4],y[4],z[4],a[4],o[4];EE_ROT_VU_READ(s,x);EE_ROT_VU_READ(t,y);EE_ROT_ACC_READ(a,o);for(unsigned k=0;k<4;k++)z[k]=(uint32_t)EE_ROT_VU_MAC(a[k],x[k],y[c],o[k],0);EE_ROT_VU_WRITE(d,z);}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


void ps2BattleAction_00175DF8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00175df8);
 /* 00175df8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 00175dfc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00175e00: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00175e04: j 0x001dd220 */ /* delay 00175e08 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));ps2ModelContextRelease(cpu(4));return;
}

uint64_t ps2BattleAction_0018F1B8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018f1b8);
 uint64_t incomingRa=cpu(31);
 /* 0018f1b8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 0018f1bc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018f1c0: move s1,a0 */ set(17,cpu(4));
 /* 0018f1c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018f1c8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0018f1cc: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x0018f1d4)));/* delay 0018f1d0 */ set(4,sx(UINT32_C(0x00000038)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 0018f1d4: addiu a0,s1,0x18 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));
 /* 0018f1d8: jal 0x001a27a8 */ set(31,sx(UINT32_C(0x0018f1e0)));/* delay 0018f1dc */ set(16,cpu(2));set(2,ps2BattleAction_001A27A8(cpu(4)));
 /* 0018f1e0: lui a1,0x8080 */ set(5,sx(UINT32_C(0x80800000)));
 /* 0018f1e4: sw v0,0x34(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(2));
 /* 0018f1e8: move v0,s0 */ set(2,cpu(16));
 /* 0018f1ec: ori a1,a1,0x8080 */ set(5,cpu(5)|UINT32_C(0x00008080));
 /* 0018f1f0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0018f1f4: lbu v1,0x0(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
 /* 0018f1f8: sb v1,0x10(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000010)),(uint8_t)cpu(3));
 /* 0018f1fc: lw a0,0x4(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000004)));
 /* 0018f200: sw a0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(4));
 /* 0018f204: lw v1,0x8(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000008)));
 /* 0018f208: sw v1,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
 /* 0018f20c: lw a0,0xc(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000000c)));
 /* 0018f210: sw a0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(4));
 /* 0018f214: lw v1,0x10(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0018f218: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
 /* 0018f21c: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
 /* 0018f220: sw a1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(5));
 /* 0018f224: sw a0,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(4));
 /* 0018f228: sw zero,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));
 /* 0018f22c: lw v1,0x24(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000024)));
 /* 0018f230: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018f234: sw v1,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(3));
 /* 0018f238: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018f23c: jr ra */ {uint64_t target=cpu(31);/* delay 0018f240 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0018F248(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018f248);
 /* 0018f248: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018f24c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018f250: jal 0x00176270 */ set(31,sx(UINT32_C(0x0018f258)));/* delay 0018f254 */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0018f258: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018f25c: move a0,v0 */ set(4,cpu(2));
 /* 0018f260: j 0x0018f1b8 */ /* delay 0018f264 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0018F1B8(cpu(4)));return cpu(2);
}

uint64_t ps2BattleAction_0018F268(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018f268);
 uint64_t incomingRa=cpu(31);
 /* 0018f268: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
 /* 0018f26c: move v1,a0 */ set(3,cpu(4));
 /* 0018f270: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
 /* 0018f274: lbu v0,0x10(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000010))));
 /* 0018f278: lw a1,0x14(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000014)));
 /* 0018f27c: lw a2,0x18(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 0018f280: lw a3,0x1c(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x0000001c)));
 /* 0018f284: lw t0,0x28(v1) */ lw(8,ea(3,(int32_t)UINT32_C(0x00000028)));
 /* 0018f288: lw t1,0x2c(v1) */ lw(9,ea(3,(int32_t)UINT32_C(0x0000002c)));
 /* 0018f28c: sb v0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
 /* 0018f290: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
 /* 0018f294: sw a2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
 /* 0018f298: sw a3,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
 /* 0018f29c: sw t0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(8));
 /* 0018f2a0: sw t1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(9));
 /* 0018f2a4: lw v0,0x34(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000034)));
 /* 0018f2a8: ldl v1,0x7(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000007)),1);
 /* 0018f2ac: ldr v1,0x0(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000000)),0);
 /* 0018f2b0: ldl a1,0xf(v0) */ loadPartial(5,ea(2,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0018f2b4: ldr a1,0x8(v0) */ loadPartial(5,ea(2,(int32_t)UINT32_C(0x00000008)),0);
 /* 0018f2b8: ldl a2,0x17(v0) */ loadPartial(6,ea(2,(int32_t)UINT32_C(0x00000017)),1);
 /* 0018f2bc: ldr a2,0x10(v0) */ loadPartial(6,ea(2,(int32_t)UINT32_C(0x00000010)),0);
 /* 0018f2c0: ldl a3,0x1f(v0) */ loadPartial(7,ea(2,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0018f2c4: ldr a3,0x18(v0) */ loadPartial(7,ea(2,(int32_t)UINT32_C(0x00000018)),0);
 /* 0018f2c8: sdl v1,0x1f(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000001f)),3,1);
 /* 0018f2cc: sdr v1,0x18(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000018)),3,0);
 /* 0018f2d0: sdl a1,0x27(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000027)),5,1);
 /* 0018f2d4: sdr a1,0x20(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000020)),5,0);
 /* 0018f2d8: sdl a2,0x2f(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000002f)),6,1);
 /* 0018f2dc: sdr a2,0x28(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000028)),6,0);
 /* 0018f2e0: sdl a3,0x37(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000037)),7,1);
 /* 0018f2e4: sdr a3,0x30(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000030)),7,0);
 /* 0018f2e8: ldl v1,0x27(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000027)),1);
 /* 0018f2ec: ldr v1,0x20(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000020)),0);
 /* 0018f2f0: lw a1,0x28(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000028)));
 /* 0018f2f4: sdl v1,0x3f(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000003f)),3,1);
 /* 0018f2f8: sdr v1,0x38(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000038)),3,0);
 /* 0018f2fc: sw a1,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(5));
 /* 0018f300: jal 0x0018f1b8 */ set(31,sx(UINT32_C(0x0018f308)));/* delay 0018f304 */ set(4,cpu(29));set(2,ps2BattleAction_0018F1B8(cpu(4)));
 /* 0018f308: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
 /* 0018f30c: jr ra */ {uint64_t target=cpu(31);/* delay 0018f310 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_00193488(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00193488);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00193488: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 0019348c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 00193490: sll s3,a0,0x2 */ set(19,sx((uint32_t)cpu(4)<<2));
 /* 00193494: addiu s3,s3,0x4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000004)));
 /* 00193498: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0019349c: sll s0,s3,0x2 */ set(16,sx((uint32_t)cpu(19)<<2));
 /* 001934a0: li a0,0xb0 */ set(4,sx(UINT32_C(0x000000b0)));
 /* 001934a4: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
 /* 001934a8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001934ac: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001934b0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 001934b4: swc1 f20,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);
 /* 001934b8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 001934bc: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x001934c4)));/* delay 001934c0 */ set(16,sx((uint32_t)cpu(16)<<2));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 001934c4: move a0,s0 */ set(4,cpu(16));
 /* 001934c8: jal 0x002a9038 */ set(31,sx(UINT32_C(0x001934d0)));/* delay 001934cc */ set(18,cpu(2));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 001934d0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 001934d4: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
 /* 001934d8: move s4,v0 */ set(20,cpu(2));
 /* 001934dc: jal 0x002a9688 */ set(31,sx(UINT32_C(0x001934e4)));/* delay 001934e0 */ set(4,cpu(20));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 001934e4: move a1,zero */ set(5,cpu(0));
 /* 001934e8: move s1,v0 */ set(17,cpu(2));
 /* 001934ec: move a2,s0 */ set(6,cpu(16));
 /* 001934f0: jal 0x002d4558 */ set(31,sx(UINT32_C(0x001934f8)));/* delay 001934f4 */ set(4,cpu(17));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
 /* 001934f8: sw s1,0xa0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x000000a0)),(uint32_t)cpu(17));
 /* 001934fc: sll v1,s3,0x4 */ set(3,sx((uint32_t)cpu(19)<<4));
 /* 00193500: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 00193504: addu s1,s1,v1 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(3)));
 /* 00193508: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
 /* 0019350c: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 00193510: sw v1,0x94(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000094)),(uint32_t)cpu(3));
 /* 00193514: sw s1,0xa4(s2) */ sw(ea(18,(int32_t)UINT32_C(0x000000a4)),(uint32_t)cpu(17));
 /* 00193518: sw s3,0x9c(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000009c)),(uint32_t)cpu(19));
 /* 0019351c: sw v0,0x98(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000098)),(uint32_t)cpu(2));
 /* 00193520: sw s4,0xac(s2) */ sw(ea(18,(int32_t)UINT32_C(0x000000ac)),(uint32_t)cpu(20));
 /* 00193524: jal 0x002b31e8 */ set(31,sx(UINT32_C(0x0019352c)));/* delay 00193528 */ sw(ea(18,(int32_t)UINT32_C(0x00000090)),f[20]);set(2,ps2EffectMatCreate_002B31E8());
 /* 0019352c: mov.S f12,f20 */ f[12]=f[20];
 /* 00193530: sw v0,0xa8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x000000a8)),(uint32_t)cpu(2));
 /* 00193534: jal 0x002b2ed8 */ set(31,sx(UINT32_C(0x0019353c)));/* delay 00193538 */ set(4,cpu(2));ps2BattleActionMaterialSetConstant_002B2ED8(cpu(4),real(f[12]));
 /* 0019353c: addiu a2,s2,0x40 */ set(6,sx((uint32_t)cpu(18)+UINT32_C(0x00000040)));
 /* 00193540: qmfc2 a1,vf0 */ {uint32_t quad[4];EE_ROT_VU_READ(0,quad);nocturneEffectHostCpuWrite(5,quad);}
 /* 00193544: pextuw a0,zero,a1 */ pextuw(4,0,5);
 /* 00193548: pextuw v0,zero,a0 */ pextuw(2,0,4);
 /* 0019354c: pextuw v1,a0,zero */ pextuw(3,4,0);
 /* 00193550: sq v0,0x0(a2) */ sq(2,ea(6,(int32_t)UINT32_C(0x00000000)));
 /* 00193554: sq v1,0x10(a2) */ sq(3,ea(6,(int32_t)UINT32_C(0x00000010)));
 /* 00193558: sq a0,0x20(a2) */ sq(4,ea(6,(int32_t)UINT32_C(0x00000020)));
 /* 0019355c: sq a1,0x30(a2) */ sq(5,ea(6,(int32_t)UINT32_C(0x00000030)));
 /* 00193560: qmfc2 a1,vf0 */ {uint32_t quad[4];EE_ROT_VU_READ(0,quad);nocturneEffectHostCpuWrite(5,quad);}
 /* 00193564: pextuw a0,zero,a1 */ pextuw(4,0,5);
 /* 00193568: pextuw v0,zero,a0 */ pextuw(2,0,4);
 /* 0019356c: pextuw v1,a0,zero */ pextuw(3,4,0);
 /* 00193570: sq v0,0x0(s2) */ sq(2,ea(18,(int32_t)UINT32_C(0x00000000)));
 /* 00193574: sq v1,0x10(s2) */ sq(3,ea(18,(int32_t)UINT32_C(0x00000010)));
 /* 00193578: sq a0,0x20(s2) */ sq(4,ea(18,(int32_t)UINT32_C(0x00000020)));
 /* 0019357c: sq a1,0x30(s2) */ sq(5,ea(18,(int32_t)UINT32_C(0x00000030)));
 /* 00193580: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
 /* 00193584: move a1,zero */ set(5,cpu(0));
 /* 00193588: addiu s0,s0,-0x5248 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffadb8)));
 /* 0019358c: li a2,0x2c */ set(6,sx(UINT32_C(0x0000002c)));
 /* 00193590: jal 0x002d4558 */ set(31,sx(UINT32_C(0x00193598)));/* delay 00193594 */ set(4,cpu(16));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
 /* 00193598: li v1,0x4000 */ set(3,sx(UINT32_C(0x00004000)));
 /* 0019359c: move v0,s2 */ set(2,cpu(18));
 /* 001935a0: sh v1,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
 /* 001935a4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001935a8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001935ac: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001935b0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001935b4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 001935b8: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 001935bc: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 001935c0: jr ra */ {uint64_t target=cpu(31);/* delay 001935c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}

void ps2BattleAction_001937D0(uint64_t a0, float f12){
set(4,a0);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectAxisNoteEntry(0x001937d0);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 001937d0: addiu sp,sp,-0xa0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff60)));
 /* 001937d4: sd s6,0x80(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000080)));
 /* 001937d8: swc1 f20,0x90(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000090)),f[20]);
 /* 001937dc: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
 /* 001937e0: sd s1,0x58(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000058)));
 /* 001937e4: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
 /* 001937e8: sd s3,0x68(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000068)));
 /* 001937ec: sd s4,0x70(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000070)));
 /* 001937f0: sd s5,0x78(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000078)));
 /* 001937f4: sd ra,0x88(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000088)));
 /* 001937f8: swc1 f21,0x98(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000098)),f[21]);
 /* 001937fc: clear f20 */ f[20]=0;
 /* 00193800: lwc1 f0,0x38(a0) */ f[0]=word(ea(4,(int32_t)UINT32_C(0x00000038)));
 /* 00193804: lwc1 f1,0x40(a0) */ f[1]=word(ea(4,(int32_t)UINT32_C(0x00000040)));
 /* 00193808: add.S f0,f12,f0 */ f[0]=add(f[12],f[0]);
 /* 0019380c: lwc1 f2,0x48(a0) */ f[2]=word(ea(4,(int32_t)UINT32_C(0x00000048)));
 /* 00193810: lw v1,0x5c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000005c)));
 /* 00193814: lw a0,0x30(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000030)));
 /* 00193818: lw v0,0x9c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000009c)));
 /* 0019381c: add.S f1,f0,f1 */ f[1]=add(f[0],f[1]);
 /* 00193820: swc1 f12,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[12]);
 /* 00193824: swc1 f12,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[12]);
 /* 00193828: sra s6,v0,0x2 */ set(22,sx((uint32_t)((int32_t)cpu(2)>>2)));
 /* 0019382c: swc1 f12,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[12]);
 /* 00193830: swc1 f0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[0]);
 /* 00193834: add.S f2,f1,f2 */ f[2]=add(f[1],f[2]);
 /* 00193838: swc1 f0,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[0]);
 /* 0019383c: swc1 f0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[0]);
 /* 00193840: swc1 f1,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[1]);
 /* 00193844: swc1 f1,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),f[1]);
 /* 00193848: swc1 f2,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),f[2]);
 /* 0019384c: swc1 f1,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[1]);
 /* 00193850: swc1 f2,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),f[2]);
 /* 00193854: swc1 f2,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),f[2]);
 /* 00193858: bltz a0,0x00193870 */ {int take=((int64_t)cpu(4)<0);/* delay 0019385c */ lw(16,ea(3,(int32_t)UINT32_C(0x000000a0)));if(take){goto L_00193870;}}
 /* 00193860: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
 /* 00193864: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 00193868: b 0x00193888 */ /* delay 0019386c */ goto L_00193888;
L_00193870:;
 /* 00193870: srl v1,a0,0x1 */ set(3,sx((uint32_t)cpu(4)>>1));
 /* 00193874: andi v0,a0,0x1 */ set(2,cpu(4)&UINT32_C(0x00000001));
 /* 00193878: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
 /* 0019387c: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
 /* 00193880: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 00193884: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
L_00193888:;
 /* 00193888: lwc1 f0,-0x788c(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8774)));
 /* 0019388c: move s1,zero */ set(17,cpu(0));
 /* 00193890: nop  */ 
 /* 00193894: nop  */ 
 /* 00193898: div.S f21,f0,f1 */ f[21]=divs(f[0],f[1]);
 /* 0019389c: beq s6,zero,0x00193924 */ {int take=(cpu(22)==cpu(0));/* delay 001938a0 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));if(take){goto L_00193924;}}
 /* 001938a4: addiu s5,sp,0x10 */ set(21,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
 /* 001938a8: addiu s4,sp,0x20 */ set(20,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
 /* 001938ac: addiu s3,sp,0x30 */ set(19,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
 /* 001938b0: addiu s2,sp,0x40 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
 /* 001938b4: nop  */ 
L_001938b8:;
 /* 001938b8: jal 0x002c0160 */ set(31,sx(UINT32_C(0x001938c0)));/* delay 001938bc */ f[12]=f[20];f[0]=bits(ps2EffectTableCosFloat_002C0160(real(f[12])));
 /* 001938c0: mov.S f12,f20 */ f[12]=f[20];
 /* 001938c4: jal 0x002c0060 */ set(31,sx(UINT32_C(0x001938cc)));/* delay 001938c8 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[0]);f[0]=bits(ps2EffectTableSinFloat_002C0060(real(f[12])));
 /* 001938cc: swc1 f0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[0]);
 /* 001938d0: lqc2 vf11,0x0(sp) */ loadVu(11,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001938d4: lqc2 vf10,0x0(s5) */ loadVu(10,ea(21,(int32_t)UINT32_C(0x00000000)));
 /* 001938d8: vmul.xyzw vf10,vf10,vf11 */ vuMul(10,10,11);
 /* 001938dc: sqc2 vf10,0x0(s0) */ storeVu(10,ea(16,(int32_t)UINT32_C(0x00000000)));
 /* 001938e0: lqc2 vf10,0x0(s4) */ loadVu(10,ea(20,(int32_t)UINT32_C(0x00000000)));
 /* 001938e4: vmul.xyzw vf10,vf10,vf11 */ vuMul(10,10,11);
 /* 001938e8: addiu v0,s0,0x10 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
 /* 001938ec: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
 /* 001938f0: lqc2 vf10,0x0(s3) */ loadVu(10,ea(19,(int32_t)UINT32_C(0x00000000)));
 /* 001938f4: vmul.xyzw vf10,vf10,vf11 */ vuMul(10,10,11);
 /* 001938f8: addiu v0,s0,0x20 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 001938fc: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
 /* 00193900: lqc2 vf10,0x0(s2) */ loadVu(10,ea(18,(int32_t)UINT32_C(0x00000000)));
 /* 00193904: vmul.xyzw vf10,vf10,vf11 */ vuMul(10,10,11);
 /* 00193908: addiu v0,s0,0x30 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));
 /* 0019390c: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
 /* 00193910: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
 /* 00193914: add.S f20,f20,f21 */ f[20]=add(f[20],f[21]);
 /* 00193918: sltu v0,s1,s6 */ set(2,cpu(17)<cpu(22));
 /* 0019391c: bne v0,zero,0x001938b8 */ {int take=(cpu(2)!=cpu(0));/* delay 00193920 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));if(take){goto L_001938b8;}}
L_00193924:;
 /* 00193924: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
 /* 00193928: ld s1,0x58(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000058)));
 /* 0019392c: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
 /* 00193930: ld s3,0x68(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000068)));
 /* 00193934: ld s4,0x70(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000070)));
 /* 00193938: ld s5,0x78(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000078)));
 /* 0019393c: ld s6,0x80(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000080)));
 /* 00193940: ld ra,0x88(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000088)));
 /* 00193944: lwc1 f21,0x98(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
 /* 00193948: lwc1 f20,0x90(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000090)));
 /* 0019394c: jr ra */ {uint64_t target=cpu(31);/* delay 00193950 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000a0)));checkReturn(target,incomingRa);return;}
}

void ps2BattleAction_00193958(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00193958);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00193958: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0019395c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00193960: move s0,a0 */ set(16,cpu(4));
 /* 00193964: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00193968: jal 0x001937d0 */ set(31,sx(UINT32_C(0x00193970)));/* delay 0019396c */ f[12]=word(ea(16,(int32_t)UINT32_C(0x00000028)));ps2BattleAction_001937D0(cpu(4),real(f[12]));
 /* 00193970: sw zero,0x50(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(0));
 /* 00193974: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00193978: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0019397c: jr ra */ {uint64_t target=cpu(31);/* delay 00193980 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incomingRa);return;}
}

uint64_t ps2BattleAction_00193988(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00193988);
 uint64_t incomingRa=cpu(31);
 /* 00193988: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 0019398c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00193990: move s0,a0 */ set(16,cpu(4));
 /* 00193994: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00193998: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0019399c: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x001939a4)));/* delay 001939a0 */ set(4,sx(UINT32_C(0x00000060)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 001939a4: move s1,v0 */ set(17,cpu(2));
 /* 001939a8: move v1,s0 */ set(3,cpu(16));
 /* 001939ac: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
 /* 001939b0: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 001939b4: beq v0,zero,0x00193a20 */ {int take=(cpu(2)==cpu(0));/* delay 001939b8 */ set(4,cpu(17));if(take){goto L_00193a20;}}
 /* 001939bc: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_001939c0:;
 /* 001939c0: ldl a1,0x7(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000007)),1);
 /* 001939c4: ldr a1,0x0(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000000)),0);
 /* 001939c8: ldl a2,0xf(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
 /* 001939cc: ldr a2,0x8(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x00000008)),0);
 /* 001939d0: ldl a3,0x17(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000017)),1);
 /* 001939d4: ldr a3,0x10(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000010)),0);
 /* 001939d8: ldl t0,0x1f(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x0000001f)),1);
 /* 001939dc: ldr t0,0x18(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x00000018)),0);
 /* 001939e0: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
 /* 001939e4: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
 /* 001939e8: sdl a2,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),6,1);
 /* 001939ec: sdr a2,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),6,0);
 /* 001939f0: sdl a3,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),7,1);
 /* 001939f4: sdr a3,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),7,0);
 /* 001939f8: sdl t0,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),8,1);
 /* 001939fc: sdr t0,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),8,0);
 /* 00193a00: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
 /* 00193a04: nop  */ 
 /* 00193a08: nop  */ 
 /* 00193a0c: bne v1,v0,0x001939c0 */ {int take=(cpu(3)!=cpu(2));/* delay 00193a10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(take){goto L_001939c0;}}
 /* 00193a14: b 0x00193a58 */ /* delay 00193a18 */ goto L_00193a58;
L_00193a20:;
 /* 00193a20: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_00193a24:;
 /* 00193a24: ld a1,0x0(v1) */ restore(5,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 00193a28: ld a2,0x8(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 00193a2c: ld a3,0x10(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 00193a30: ld t0,0x18(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 00193a34: sd a1,0x0(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000000)));
 /* 00193a38: sd a2,0x8(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000008)));
 /* 00193a3c: sd a3,0x10(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000010)));
 /* 00193a40: sd t0,0x18(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000018)));
 /* 00193a44: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
 /* 00193a48: nop  */ 
 /* 00193a4c: nop  */ 
 /* 00193a50: bne v1,v0,0x00193a24 */ {int take=(cpu(3)!=cpu(2));/* delay 00193a54 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(take){goto L_00193a24;}}
L_00193a58:;
 /* 00193a58: ldl a1,0x7(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000007)),1);
 /* 00193a5c: ldr a1,0x0(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000000)),0);
 /* 00193a60: ldl a2,0xf(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
 /* 00193a64: ldr a2,0x8(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x00000008)),0);
 /* 00193a68: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
 /* 00193a6c: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
 /* 00193a70: sdl a2,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),6,1);
 /* 00193a74: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 00193a78: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 00193a7c: sdr a2,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),6,0);
 /* 00193a80: sw v0,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));
 /* 00193a84: sw zero,0x50(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(0));
 /* 00193a88: lw a0,0x30(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000030)));
 /* 00193a8c: sltiu v0,a0,0x3 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
 /* 00193a90: beq v0,zero,0x00193aa0 */ {int take=(cpu(2)==cpu(0));/* delay 00193a94 */ set(2,sx(UINT32_C(0x00000003)));if(take){goto L_00193aa0;}}
 /* 00193a98: li a0,0x3 */ set(4,sx(UINT32_C(0x00000003)));
 /* 00193a9c: sw v0,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));
L_00193aa0:;
 /* 00193aa0: jal 0x00193488 */ set(31,sx(UINT32_C(0x00193aa8)));/* delay 00193aa4 */ set(2,ps2BattleAction_00193488(cpu(4)));
 /* 00193aa8: move a3,zero */ set(7,cpu(0));
 /* 00193aac: lw v1,0x9c(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000009c)));
 /* 00193ab0: sw v0,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(2));
 /* 00193ab4: sw v1,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(3));
 /* 00193ab8: lw v1,0x9c(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000009c)));
 /* 00193abc: sra a2,v1,0x2 */ set(6,sx((uint32_t)((int32_t)cpu(3)>>2)));
 /* 00193ac0: beq a2,zero,0x00193af4 */ {int take=(cpu(6)==cpu(0));/* delay 00193ac4 */ lw(5,ea(2,(int32_t)UINT32_C(0x000000a4)));if(take){goto L_00193af4;}}
L_00193ac8:;
 /* 00193ac8: lw v0,0x3c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000003c)));
 /* 00193acc: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
 /* 00193ad0: sltu a0,a3,a2 */ set(4,cpu(7)<cpu(6));
 /* 00193ad4: sw v0,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
 /* 00193ad8: lw v1,0x44(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000044)));
 /* 00193adc: sw v1,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
 /* 00193ae0: sw v1,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
 /* 00193ae4: lw v0,0x4c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000004c)));
 /* 00193ae8: sw v0,0xc(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
 /* 00193aec: bne a0,zero,0x00193ac8 */ {int take=(cpu(4)!=cpu(0));/* delay 00193af0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));if(take){goto L_00193ac8;}}
L_00193af4:;
 /* 00193af4: jal 0x00193958 */ set(31,sx(UINT32_C(0x00193afc)));/* delay 00193af8 */ set(4,cpu(17));ps2BattleAction_00193958(cpu(4));
 /* 00193afc: lw a0,0x5c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000005c)));
 /* 00193b00: lw v1,0x34(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000034)));
 /* 00193b04: move v0,s1 */ set(2,cpu(17));
 /* 00193b08: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00193b0c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00193b10: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00193b14: sw v1,0x94(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000094)),(uint32_t)cpu(3));
 /* 00193b18: jr ra */ {uint64_t target=cpu(31);/* delay 00193b1c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_00193B20(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00193b20);
 /* 00193b20: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 00193b24: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00193b28: jal 0x00176270 */ set(31,sx(UINT32_C(0x00193b30)));/* delay 00193b2c */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 00193b30: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00193b34: move a0,v0 */ set(4,cpu(2));
 /* 00193b38: j 0x00193988 */ /* delay 00193b3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_00193988(cpu(4)));return cpu(2);
}

uint64_t ps2BattleAction_00193B40(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00193b40);
 /* 00193b40: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 00193b44: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00193b48: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00193b4c: j 0x00193988 */ /* delay 00193b50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_00193988(cpu(4)));return cpu(2);
}

void ps2BattleAction_00193DC0(uint64_t a0, float f12){
set(4,a0);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectAxisNoteEntry(0x00193dc0);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00193dc0: lw v0,0x5c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000005c)));
 /* 00193dc4: jr ra */ {uint64_t target=cpu(31);/* delay 00193dc8 */ sw(ea(2,(int32_t)UINT32_C(0x00000090)),f[12]);checkReturn(target,incomingRa);return;}
}

void ps2BattleAction_00193E60(uint64_t a0, float f12){
set(4,a0);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectAxisNoteEntry(0x00193e60);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00193e60: addiu sp,sp,-0xb0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff50)));
 /* 00193e64: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
 /* 00193e68: move s0,a0 */ set(16,cpu(4));
 /* 00193e6c: sd s7,0x88(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000088)));
 /* 00193e70: swc1 f20,0x98(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000098)),f[20]);
 /* 00193e74: sd s1,0x58(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000058)));
 /* 00193e78: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
 /* 00193e7c: sd s3,0x68(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000068)));
 /* 00193e80: sd s4,0x70(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000070)));
 /* 00193e84: sd s5,0x78(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000078)));
 /* 00193e88: sd s6,0x80(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000080)));
 /* 00193e8c: sd ra,0x90(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000090)));
 /* 00193e90: swc1 f21,0xa0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000a0)),f[21]);
 /* 00193e94: clear f20 */ f[20]=0;
 /* 00193e98: lwc1 f0,0x44(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000044)));
 /* 00193e9c: lwc1 f1,0x4c(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x0000004c)));
 /* 00193ea0: add.S f0,f12,f0 */ f[0]=add(f[12],f[0]);
 /* 00193ea4: lwc1 f2,0x54(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x00000054)));
 /* 00193ea8: lw v1,0x7c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000007c)));
 /* 00193eac: lw a0,0x3c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000003c)));
 /* 00193eb0: lw v0,0x9c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000009c)));
 /* 00193eb4: add.S f1,f0,f1 */ f[1]=add(f[0],f[1]);
 /* 00193eb8: swc1 f12,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[12]);
 /* 00193ebc: swc1 f12,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[12]);
 /* 00193ec0: sra s7,v0,0x2 */ set(23,sx((uint32_t)((int32_t)cpu(2)>>2)));
 /* 00193ec4: swc1 f12,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[12]);
 /* 00193ec8: swc1 f0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[0]);
 /* 00193ecc: add.S f2,f1,f2 */ f[2]=add(f[1],f[2]);
 /* 00193ed0: swc1 f0,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[0]);
 /* 00193ed4: swc1 f0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[0]);
 /* 00193ed8: swc1 f1,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[1]);
 /* 00193edc: swc1 f1,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),f[1]);
 /* 00193ee0: swc1 f2,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),f[2]);
 /* 00193ee4: swc1 f1,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[1]);
 /* 00193ee8: swc1 f2,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),f[2]);
 /* 00193eec: swc1 f2,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),f[2]);
 /* 00193ef0: bltz a0,0x00193f08 */ {int take=((int64_t)cpu(4)<0);/* delay 00193ef4 */ lw(17,ea(3,(int32_t)UINT32_C(0x000000a0)));if(take){goto L_00193f08;}}
 /* 00193ef8: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
 /* 00193efc: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 00193f00: b 0x00193f20 */ /* delay 00193f04 */ goto L_00193f20;
L_00193f08:;
 /* 00193f08: srl v1,a0,0x1 */ set(3,sx((uint32_t)cpu(4)>>1));
 /* 00193f0c: andi v0,a0,0x1 */ set(2,cpu(4)&UINT32_C(0x00000001));
 /* 00193f10: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
 /* 00193f14: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
 /* 00193f18: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 00193f1c: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
L_00193f20:;
 /* 00193f20: lwc1 f0,-0x7884(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff877c)));
 /* 00193f24: lbu v0,0x20(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000020))));
 /* 00193f28: nop  */ 
 /* 00193f2c: nop  */ 
 /* 00193f30: div.S f21,f0,f1 */ f[21]=divs(f[0],f[1]);
 /* 00193f34: bne v0,zero,0x00193f68 */ {int take=(cpu(2)!=cpu(0));/* delay 00193f38 */ set(4,sx(UINT32_C(0x002f0000)));if(take){goto L_00193f68;}}
 /* 00193f3c: lui a1,0x2f */ set(5,sx(UINT32_C(0x002f0000)));
 /* 00193f40: lui a2,0x2f */ set(6,sx(UINT32_C(0x002f0000)));
 /* 00193f44: addiu a0,a0,0x5a50 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00005a50)));
 /* 00193f48: addiu a1,a1,0x5a60 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00005a60)));
 /* 00193f4c: jal 0x002b6748 */ set(31,sx(UINT32_C(0x00193f54)));/* delay 00193f50 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00005a70)));ps2EffectParticleLookAtMatrix_002B6748(cpu(4),cpu(5),cpu(6));
 /* 00193f54: jal 0x002b5e78 */ set(31,sx(UINT32_C(0x00193f5c)));/* delay 00193f58 */ set(18,cpu(0));ps2EffectParticleRigidInverse_002B5E78();
 /* 00193f5c: b 0x00193f9c */ /* delay 00193f60 */ goto L_00193f9c;
L_00193f68:;
 /* 00193f68: jal 0x002b6060 */ set(31,sx(UINT32_C(0x00193f70)));/* delay 00193f6c */ f[12]=word(ea(16,(int32_t)UINT32_C(0x00000064)));ps2BattleActionRotationZNative_002B6060(real(f[12]));
 /* 00193f70: jal 0x002b62c0 */ set(31,sx(UINT32_C(0x00193f78)));/* delay 00193f74 */ f[12]=word(ea(16,(int32_t)UINT32_C(0x00000068)));ps2SpecialPolygonRotationY(real(f[12]));
 /* 00193f78: jal 0x002b65a8 */ set(31,sx(UINT32_C(0x00193f80)));/* delay 00193f7c */ set(18,cpu(0));ps2EffectModelComposeVuMatrices_002B65A8();
 /* 00193f80: lwc1 f0,0x6c(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x0000006c)));
 /* 00193f84: lwc1 f1,0x68(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000068)));
 /* 00193f88: lwc1 f2,0x1c(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x0000001c)));
 /* 00193f8c: add.S f1,f1,f0 */ f[1]=add(f[1],f[0]);
 /* 00193f90: mul.S f0,f0,f2 */ f[0]=mul(f[0],f[2]);
 /* 00193f94: swc1 f1,0x68(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000068)),f[1]);
 /* 00193f98: swc1 f0,0x6c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000006c)),f[0]);
L_00193f9c:;
 /* 00193f9c: beql s7,zero,0x00194074 */ {int take=(cpu(23)==cpu(0));if(take){/* delay 00193fa0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_00194074;}}
 /* 00193fa4: addiu s6,sp,0x10 */ set(22,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
 /* 00193fa8: addiu s5,sp,0x20 */ set(21,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
 /* 00193fac: addiu s4,sp,0x30 */ set(20,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
 /* 00193fb0: addiu s3,sp,0x40 */ set(19,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
 /* 00193fb4: nop  */ 
L_00193fb8:;
 /* 00193fb8: lbu v0,0x20(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000020))));
 /* 00193fbc: bne v0,zero,0x00193fe8 */ {int take=(cpu(2)!=cpu(0));/* delay 00193fc0 */ if(take){goto L_00193fe8;}}
 /* 00193fc4: jal 0x002c0160 */ set(31,sx(UINT32_C(0x00193fcc)));/* delay 00193fc8 */ f[12]=f[20];f[0]=bits(ps2EffectTableCosFloat_002C0160(real(f[12])));
 /* 00193fcc: mov.S f12,f20 */ f[12]=f[20];
 /* 00193fd0: jal 0x002c0060 */ set(31,sx(UINT32_C(0x00193fd8)));/* delay 00193fd4 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[0]);f[0]=bits(ps2EffectTableSinFloat_002C0060(real(f[12])));
 /* 00193fd8: swc1 f0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[0]);
 /* 00193fdc: b 0x00194004 */ /* delay 00193fe0 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));goto L_00194004;
L_00193fe8:;
 /* 00193fe8: jal 0x002c0160 */ set(31,sx(UINT32_C(0x00193ff0)));/* delay 00193fec */ f[12]=f[20];f[0]=bits(ps2EffectTableCosFloat_002C0160(real(f[12])));
 /* 00193ff0: mov.S f12,f20 */ f[12]=f[20];
 /* 00193ff4: swc1 f0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[0]);
 /* 00193ff8: jal 0x002c0060 */ set(31,sx(UINT32_C(0x00194000)));/* delay 00193ffc */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));f[0]=bits(ps2EffectTableSinFloat_002C0060(real(f[12])));
 /* 00194000: swc1 f0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[0]);
L_00194004:;
 /* 00194004: sw zero,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
 /* 00194008: lqc2 vf10,0x0(sp) */ loadVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0019400c: vmulax.xyzw ACC,vf28,vf10 */ vuMula(28,10,0);
 /* 00194010: vmadday.xyzw ACC,vf29,vf10 */ vuMadda(29,10,1);
 /* 00194014: vmaddaz.xyzw ACC,vf30,vf10 */ vuMadda(30,10,2);
 /* 00194018: vmaddw.xyzw vf10,vf31,vf10 */ vuMadd(10,31,10,3);
 /* 0019401c: vmove.xyzw vf11,vf10 */ moveVu(11,10);
 /* 00194020: lqc2 vf10,0x0(s6) */ loadVu(10,ea(22,(int32_t)UINT32_C(0x00000000)));
 /* 00194024: vmul.xyzw vf10,vf10,vf11 */ vuMul(10,10,11);
 /* 00194028: sqc2 vf10,0x0(s1) */ storeVu(10,ea(17,(int32_t)UINT32_C(0x00000000)));
 /* 0019402c: lqc2 vf10,0x0(s5) */ loadVu(10,ea(21,(int32_t)UINT32_C(0x00000000)));
 /* 00194030: vmul.xyzw vf10,vf10,vf11 */ vuMul(10,10,11);
 /* 00194034: addiu v0,s1,0x10 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));
 /* 00194038: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
 /* 0019403c: lqc2 vf10,0x0(s4) */ loadVu(10,ea(20,(int32_t)UINT32_C(0x00000000)));
 /* 00194040: vmul.xyzw vf10,vf10,vf11 */ vuMul(10,10,11);
 /* 00194044: addiu v0,s1,0x20 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000020)));
 /* 00194048: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
 /* 0019404c: lqc2 vf10,0x0(s3) */ loadVu(10,ea(19,(int32_t)UINT32_C(0x00000000)));
 /* 00194050: vmul.xyzw vf10,vf10,vf11 */ vuMul(10,10,11);
 /* 00194054: addiu v0,s1,0x30 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000030)));
 /* 00194058: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
 /* 0019405c: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
 /* 00194060: add.S f20,f20,f21 */ f[20]=add(f[20],f[21]);
 /* 00194064: sltu v0,s2,s7 */ set(2,cpu(18)<cpu(23));
 /* 00194068: bne v0,zero,0x00193fb8 */ {int take=(cpu(2)!=cpu(0));/* delay 0019406c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000040)));if(take){goto L_00193fb8;}}
 /* 00194070: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
L_00194074:;
 /* 00194074: ld s1,0x58(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000058)));
 /* 00194078: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
 /* 0019407c: ld s3,0x68(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000068)));
 /* 00194080: ld s4,0x70(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000070)));
 /* 00194084: ld s5,0x78(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000078)));
 /* 00194088: ld s6,0x80(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000080)));
 /* 0019408c: ld s7,0x88(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000088)));
 /* 00194090: ld ra,0x90(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000090)));
 /* 00194094: lwc1 f21,0xa0(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x000000a0)));
 /* 00194098: lwc1 f20,0x98(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
 /* 0019409c: jr ra */ {uint64_t target=cpu(31);/* delay 001940a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000b0)));checkReturn(target,incomingRa);return;}
}

void ps2BattleAction_001940A8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001940a8);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 001940a8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 001940ac: lwc1 f0,-0x7880(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8780)));
 /* 001940b0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001940b4: move s0,a0 */ set(16,cpu(4));
 /* 001940b8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001940bc: lwc1 f1,0x10(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 001940c0: lwc1 f2,0x14(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x00000014)));
 /* 001940c4: lwc1 f3,0x18(s0) */ f[3]=word(ea(16,(int32_t)UINT32_C(0x00000018)));
 /* 001940c8: mul.S f1,f1,f0 */ f[1]=mul(f[1],f[0]);
 /* 001940cc: mul.S f2,f2,f0 */ f[2]=mul(f[2],f[0]);
 /* 001940d0: lwc1 f12,0x30(s0) */ f[12]=word(ea(16,(int32_t)UINT32_C(0x00000030)));
 /* 001940d4: mul.S f3,f3,f0 */ f[3]=mul(f[3],f[0]);
 /* 001940d8: lwc1 f4,0x34(s0) */ f[4]=word(ea(16,(int32_t)UINT32_C(0x00000034)));
 /* 001940dc: swc1 f12,0x74(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000074)),f[12]);
 /* 001940e0: swc1 f1,0x64(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000064)),f[1]);
 /* 001940e4: swc1 f2,0x68(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000068)),f[2]);
 /* 001940e8: swc1 f3,0x6c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000006c)),f[3]);
 /* 001940ec: jal 0x00193e60 */ set(31,sx(UINT32_C(0x001940f4)));/* delay 001940f0 */ sw(ea(16,(int32_t)UINT32_C(0x00000078)),f[4]);ps2BattleAction_00193E60(cpu(4),real(f[12]));
 /* 001940f4: sw zero,0x5c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(0));
 /* 001940f8: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001940fc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00194100: jr ra */ {uint64_t target=cpu(31);/* delay 00194104 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incomingRa);return;}
}

uint64_t ps2BattleAction_00194108(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00194108);
 uint64_t incomingRa=cpu(31);
 /* 00194108: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 0019410c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00194110: move s0,a0 */ set(16,cpu(4));
 /* 00194114: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00194118: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0019411c: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x00194124)));/* delay 00194120 */ set(4,sx(UINT32_C(0x00000080)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 00194124: move s1,v0 */ set(17,cpu(2));
 /* 00194128: move v1,s0 */ set(3,cpu(16));
 /* 0019412c: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
 /* 00194130: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 00194134: beq v0,zero,0x001941a0 */ {int take=(cpu(2)==cpu(0));/* delay 00194138 */ set(4,cpu(17));if(take){goto L_001941a0;}}
 /* 0019413c: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_00194140:;
 /* 00194140: ldl a1,0x7(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000007)),1);
 /* 00194144: ldr a1,0x0(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000000)),0);
 /* 00194148: ldl a2,0xf(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0019414c: ldr a2,0x8(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x00000008)),0);
 /* 00194150: ldl a3,0x17(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000017)),1);
 /* 00194154: ldr a3,0x10(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000010)),0);
 /* 00194158: ldl t0,0x1f(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0019415c: ldr t0,0x18(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x00000018)),0);
 /* 00194160: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
 /* 00194164: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
 /* 00194168: sdl a2,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),6,1);
 /* 0019416c: sdr a2,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),6,0);
 /* 00194170: sdl a3,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),7,1);
 /* 00194174: sdr a3,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),7,0);
 /* 00194178: sdl t0,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),8,1);
 /* 0019417c: sdr t0,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),8,0);
 /* 00194180: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
 /* 00194184: nop  */ 
 /* 00194188: nop  */ 
 /* 0019418c: bne v1,v0,0x00194140 */ {int take=(cpu(3)!=cpu(2));/* delay 00194190 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(take){goto L_00194140;}}
 /* 00194194: b 0x001941d8 */ /* delay 00194198 */ goto L_001941d8;
L_001941a0:;
 /* 001941a0: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_001941a4:;
 /* 001941a4: ld a1,0x0(v1) */ restore(5,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 001941a8: ld a2,0x8(v1) */ restore(6,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 001941ac: ld a3,0x10(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 001941b0: ld t0,0x18(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 001941b4: sd a1,0x0(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000000)));
 /* 001941b8: sd a2,0x8(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000008)));
 /* 001941bc: sd a3,0x10(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000010)));
 /* 001941c0: sd t0,0x18(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000018)));
 /* 001941c4: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
 /* 001941c8: nop  */ 
 /* 001941cc: nop  */ 
 /* 001941d0: bne v1,v0,0x001941a4 */ {int take=(cpu(3)!=cpu(2));/* delay 001941d4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(take){goto L_001941a4;}}
L_001941d8:;
 /* 001941d8: ldl a1,0x7(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000007)),1);
 /* 001941dc: ldr a1,0x0(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000000)),0);
 /* 001941e0: ldl a2,0xf(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
 /* 001941e4: ldr a2,0x8(v1) */ loadPartial(6,ea(3,(int32_t)UINT32_C(0x00000008)),0);
 /* 001941e8: ldl a3,0x17(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000017)),1);
 /* 001941ec: ldr a3,0x10(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000010)),0);
 /* 001941f0: lw t0,0x18(v1) */ lw(8,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 001941f4: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
 /* 001941f8: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
 /* 001941fc: sdl a2,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),6,1);
 /* 00194200: sdr a2,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),6,0);
 /* 00194204: sdl a3,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),7,1);
 /* 00194208: sdr a3,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),7,0);
 /* 0019420c: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 00194210: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 00194214: sw t0,0x18(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(8));
 /* 00194218: sw v0,0x60(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(2));
 /* 0019421c: sw zero,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(0));
 /* 00194220: lw a0,0x3c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000003c)));
 /* 00194224: sltiu v0,a0,0x3 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
 /* 00194228: beq v0,zero,0x00194238 */ {int take=(cpu(2)==cpu(0));/* delay 0019422c */ set(2,sx(UINT32_C(0x00000003)));if(take){goto L_00194238;}}
 /* 00194230: li a0,0x3 */ set(4,sx(UINT32_C(0x00000003)));
 /* 00194234: sw v0,0x3c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(2));
L_00194238:;
 /* 00194238: jal 0x00193488 */ set(31,sx(UINT32_C(0x00194240)));/* delay 0019423c */ set(2,ps2BattleAction_00193488(cpu(4)));
 /* 00194240: move a3,zero */ set(7,cpu(0));
 /* 00194244: lw v1,0x9c(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000009c)));
 /* 00194248: sw v0,0x7c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000007c)),(uint32_t)cpu(2));
 /* 0019424c: sra a2,v1,0x2 */ set(6,sx((uint32_t)((int32_t)cpu(3)>>2)));
 /* 00194250: beq a2,zero,0x00194284 */ {int take=(cpu(6)==cpu(0));/* delay 00194254 */ lw(5,ea(2,(int32_t)UINT32_C(0x000000a4)));if(take){goto L_00194284;}}
L_00194258:;
 /* 00194258: lw v0,0x48(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000048)));
 /* 0019425c: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
 /* 00194260: sltu a0,a3,a2 */ set(4,cpu(7)<cpu(6));
 /* 00194264: sw v0,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
 /* 00194268: lw v1,0x50(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000050)));
 /* 0019426c: sw v1,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
 /* 00194270: sw v1,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
 /* 00194274: lw v0,0x58(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000058)));
 /* 00194278: sw v0,0xc(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
 /* 0019427c: bne a0,zero,0x00194258 */ {int take=(cpu(4)!=cpu(0));/* delay 00194280 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));if(take){goto L_00194258;}}
L_00194284:;
 /* 00194284: jal 0x001940a8 */ set(31,sx(UINT32_C(0x0019428c)));/* delay 00194288 */ set(4,cpu(17));ps2BattleAction_001940A8(cpu(4));
 /* 0019428c: lw a0,0x7c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000007c)));
 /* 00194290: lw v1,0x40(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000040)));
 /* 00194294: move v0,s1 */ set(2,cpu(17));
 /* 00194298: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0019429c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001942a0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001942a4: sw v1,0x94(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000094)),(uint32_t)cpu(3));
 /* 001942a8: jr ra */ {uint64_t target=cpu(31);/* delay 001942ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_001942B0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001942b0);
 /* 001942b0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 001942b4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001942b8: jal 0x00176270 */ set(31,sx(UINT32_C(0x001942c0)));/* delay 001942bc */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 001942c0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001942c4: move a0,v0 */ set(4,cpu(2));
 /* 001942c8: j 0x00194108 */ /* delay 001942cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_00194108(cpu(4)));return cpu(2);
}

uint64_t ps2BattleAction_001942D0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001942d0);
 /* 001942d0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 001942d4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001942d8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001942dc: j 0x00194108 */ /* delay 001942e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_00194108(cpu(4)));return cpu(2);
}

void ps2BattleAction_00194450(uint64_t a0, float f12){
set(4,a0);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectAxisNoteEntry(0x00194450);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00194450: lw v0,0x7c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000007c)));
 /* 00194454: jr ra */ {uint64_t target=cpu(31);/* delay 00194458 */ sw(ea(2,(int32_t)UINT32_C(0x00000090)),f[12]);checkReturn(target,incomingRa);return;}
}

void ps2BattleAction_001A26F0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x001a26f0);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 001a26f0: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
 /* 001a26f4: addiu a2,a1,0x8 */ set(6,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
 /* 001a26f8: sw zero,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
 /* 001a26fc: sw v0,0x0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
 /* 001a2700: sw zero,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
 /* 001a2704: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
 /* 001a2708: lwc1 f0,0x14(a0) */ f[0]=word(ea(4,(int32_t)UINT32_C(0x00000014)));
 /* 001a270c: sw v0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
 /* 001a2710: swc1 f0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),f[0]);
 /* 001a2714: lw v0,0x20(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000020)));
 /* 001a2718: sw v0,0x10(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
 /* 001a271c: lw v1,0x24(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000024)));
 /* 001a2720: jr ra */ {uint64_t target=cpu(31);/* delay 001a2724 */ sw(ea(6,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));checkReturn(target,incomingRa);return;}
}

uint64_t ps2BattleAction_001A27A8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001a27a8);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 001a27a8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
 /* 001a27ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001a27b0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001a27b4: move s1,a0 */ set(17,cpu(4));
 /* 001a27b8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001a27bc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001a27c0: move s3,zero */ set(19,cpu(0));
 /* 001a27c4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 001a27c8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 001a27cc: lw s4,0x0(s1) */ lw(20,ea(17,(int32_t)UINT32_C(0x00000000)));
 /* 001a27d0: sll a0,s4,0x1 */ set(4,sx((uint32_t)cpu(20)<<1));
 /* 001a27d4: addu a0,a0,s4 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(20)));
 /* 001a27d8: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
 /* 001a27dc: jal 0x002a9038 */ set(31,sx(UINT32_C(0x001a27e4)));/* delay 001a27e0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000038)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 001a27e4: move s0,v0 */ set(16,cpu(2));
 /* 001a27e8: jal 0x002a9688 */ set(31,sx(UINT32_C(0x001a27f0)));/* delay 001a27ec */ set(4,cpu(16));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 001a27f0: li a0,0x3 */ set(4,sx(UINT32_C(0x00000003)));
 /* 001a27f4: move s2,v0 */ set(18,cpu(2));
 /* 001a27f8: ldl v1,0x7(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000007)),1);
 /* 001a27fc: ldr v1,0x0(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000000)),0);
 /* 001a2800: ldl a1,0xf(s1) */ loadPartial(5,ea(17,(int32_t)UINT32_C(0x0000000f)),1);
 /* 001a2804: ldr a1,0x8(s1) */ loadPartial(5,ea(17,(int32_t)UINT32_C(0x00000008)),0);
 /* 001a2808: ldl a2,0x17(s1) */ loadPartial(6,ea(17,(int32_t)UINT32_C(0x00000017)),1);
 /* 001a280c: ldr a2,0x10(s1) */ loadPartial(6,ea(17,(int32_t)UINT32_C(0x00000010)),0);
 /* 001a2810: ldl a3,0x1f(s1) */ loadPartial(7,ea(17,(int32_t)UINT32_C(0x0000001f)),1);
 /* 001a2814: ldr a3,0x18(s1) */ loadPartial(7,ea(17,(int32_t)UINT32_C(0x00000018)),0);
 /* 001a2818: sdl v1,0x7(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000007)),3,1);
 /* 001a281c: sdr v1,0x0(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000000)),3,0);
 /* 001a2820: sdl a1,0xf(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x0000000f)),5,1);
 /* 001a2824: sdr a1,0x8(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000008)),5,0);
 /* 001a2828: sdl a2,0x17(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000017)),6,1);
 /* 001a282c: sdr a2,0x10(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000010)),6,0);
 /* 001a2830: sdl a3,0x1f(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x0000001f)),7,1);
 /* 001a2834: sdr a3,0x18(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000018)),7,0);
 /* 001a2838: ldl v1,0x27(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000027)),1);
 /* 001a283c: ldr v1,0x20(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000020)),0);
 /* 001a2840: lw a1,0x28(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000028)));
 /* 001a2844: sdl v1,0x27(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000027)),3,1);
 /* 001a2848: sdr v1,0x20(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000020)),3,0);
 /* 001a284c: addiu v0,s2,0x38 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000038)));
 /* 001a2850: sw a1,0x28(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(5));
 /* 001a2854: sw s0,0x30(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(16));
 /* 001a2858: jal 0x0015d000 */ set(31,sx(UINT32_C(0x001a2860)));/* delay 001a285c */ sw(ea(18,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(2));set(2,ps2BillboardTextureBase(cpu(4)));
 /* 001a2860: lw s0,0x34(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000034)));
 /* 001a2864: blez s4,0x001a28a4 */ {int take=((int64_t)cpu(20)<=0);/* delay 001a2868 */ sw(ea(18,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(2));if(take){goto L_001a28a4;}}
 /* 001a286c: nop  */ 
L_001a2870:;
 /* 001a2870: move a1,s0 */ set(5,cpu(16));
 /* 001a2874: jal 0x001a26f0 */ set(31,sx(UINT32_C(0x001a287c)));/* delay 001a2878 */ set(4,cpu(18));ps2BattleAction_001A26F0(cpu(4),cpu(5));
 /* 001a287c: mtc1 s3,f0 */ f[0]=(uint32_t)cpu(19);
 /* 001a2880: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
 /* 001a2884: lwc1 f1,0x8(s2) */ f[1]=word(ea(18,(int32_t)UINT32_C(0x00000008)));
 /* 001a2888: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
 /* 001a288c: slt v0,s3,s4 */ set(2,(int64_t)cpu(19)<(int64_t)cpu(20));
 /* 001a2890: mul.S f1,f1,f0 */ f[1]=mul(f[1],f[0]);
 /* 001a2894: neg.S f1,f1 */ f[1]=f[1]^UINT32_C(0x80000000);
 /* 001a2898: swc1 f1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),f[1]);
 /* 001a289c: bne v0,zero,0x001a2870 */ {int take=(cpu(2)!=cpu(0));/* delay 001a28a0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));if(take){goto L_001a2870;}}
L_001a28a4:;
 /* 001a28a4: move v0,s2 */ set(2,cpu(18));
 /* 001a28a8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001a28ac: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001a28b0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001a28b4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001a28b8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 001a28bc: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 001a28c0: jr ra */ {uint64_t target=cpu(31);/* delay 001a28c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_001DE220(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,t0);set(9,t1);nocturneEffectAxisNoteEntry(0x001de220);
 uint64_t incomingRa=cpu(31);
 /* 001de220: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 001de224: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001de228: move s1,a0 */ set(17,cpu(4));
 /* 001de22c: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
 /* 001de230: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001de234: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001de238: move s2,a1 */ set(18,cpu(5));
 /* 001de23c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001de240: move s3,t1 */ set(19,cpu(9));
 /* 001de244: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 001de248: move s4,a2 */ set(20,cpu(6));
 /* 001de24c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 001de250: move s5,t0 */ set(21,cpu(8));
 /* 001de254: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 001de258: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
 /* 001de25c: jal 0x002a8ba8 */ set(31,sx(UINT32_C(0x001de264)));/* delay 001de260 */ set(16,cpu(7));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
 /* 001de264: move s6,v0 */ set(22,cpu(2));
 /* 001de268: lui a3,0x1e */ set(7,sx(UINT32_C(0x001e0000)));
 /* 001de26c: sh s1,0x0(s6) */ sh(ea(22,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(17));
 /* 001de270: move a0,s0 */ set(4,cpu(16));
 /* 001de274: sh s2,0x2(s6) */ sh(ea(22,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(18));
 /* 001de278: addiu a3,a3,-0x1e60 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffe1a0)));
 /* 001de27c: sw s4,0x4(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));
 /* 001de280: move a1,zero */ set(5,cpu(0));
 /* 001de284: sw s3,0x10(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(19));
 /* 001de288: move a2,zero */ set(6,cpu(0));
 /* 001de28c: sw s5,0xc(s6) */ sw(ea(22,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(21));
 /* 001de290: jal 0x002968f8 */ set(31,sx(UINT32_C(0x001de298)));/* delay 001de294 */ set(8,cpu(22));set(2,ps2ResourcePacRequestCreate(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
 /* 001de298: move a0,v0 */ set(4,cpu(2));
 /* 001de29c: bne s5,zero,0x001de2b4 */ {int take=(cpu(21)!=cpu(0));/* delay 001de2a0 */ sw(ea(22,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(take){goto L_001de2b4;}}
 /* 001de2a4: jal 0x00296b70 */ set(31,sx(UINT32_C(0x001de2ac)));/* delay 001de2a8 */ set(2,ps2ResourcePacWait(cpu(4)));
 /* 001de2ac: jal 0x001de170 */ set(31,sx(UINT32_C(0x001de2b4)));/* delay 001de2b0 */ set(4,cpu(22));ps2ModelPacJobRelease(cpu(4));
L_001de2b4:;
 /* 001de2b4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001de2b8: move v0,zero */ set(2,cpu(0));
 /* 001de2bc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001de2c0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001de2c4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001de2c8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 001de2cc: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 001de2d0: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 001de2d4: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
 /* 001de2d8: jr ra */ {uint64_t target=cpu(31);/* delay 001de2dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}
