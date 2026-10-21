/* Isolated23-body native texture projection; exact MULT1 bank fix;zero new identity credit. */
#include "battle_action_formula_frames.h"
#define ps2BattleActionTexture_0015B1B0 ps2BattleRewardTexture_0015B1B0
#define ps2BattleActionTexture_0015C2C8 ps2BattleRewardTexture_0015C2C8
#define ps2BattleActionTexture_0015C908 ps2BattleRewardTexture_0015C908
#define ps2BattleActionTexture_0015C940 ps2BattleRewardTexture_0015C940
#define ps2BattleActionTexture_0015CAF0 ps2BattleRewardTexture_0015CAF0
#define ps2BattleActionTexture_002A8170 ps2BattleRewardTexture_002A8170
#define ps2BattleActionTexture_002AA558 ps2BattleRewardTexture_002AA558
#define ps2BattleActionTexture_002AA980 ps2BattleRewardTexture_002AA980
#define ps2BattleActionTexture_002AA9E0 ps2BattleRewardTexture_002AA9E0
#define ps2BattleActionTexture_002AAFF0 ps2BattleRewardTexture_002AAFF0
#define ps2BattleActionTexture_002AB070 ps2BattleRewardTexture_002AB070
#define ps2BattleActionTexture_002AB1A8 ps2BattleRewardTexture_002AB1A8
#define ps2BattleActionTexture_002AB2B0 ps2BattleRewardTexture_002AB2B0
#define ps2BattleActionTexture_002AB360 ps2BattleRewardTexture_002AB360
#define ps2BattleActionTexture_002AB388 ps2BattleRewardTexture_002AB388
#define ps2BattleActionTexture_002AB580 ps2BattleRewardTexture_002AB580
#define ps2BattleActionTexture_002AB658 ps2BattleRewardTexture_002AB658
#define ps2BattleActionTexture_002AB688 ps2BattleRewardTexture_002AB688
#define ps2BattleActionTexture_002AB6C8 ps2BattleRewardTexture_002AB6C8
#define ps2BattleActionTexture_002AB6E8 ps2BattleRewardTexture_002AB6E8
#define ps2BattleActionTexture_002ABB18 ps2BattleRewardTexture_002ABB18
#define ps2BattleActionTexture_002ABC90 ps2BattleRewardTexture_002ABC90
#define ps2BattleActionTexture_002ABE08 ps2BattleRewardTexture_002ABE08
#define nocturneLibcStreamKernel nocturneBattleRewardRawKernel
#define nocturneEffectHostCpuWrite nocturneBattleRewardTextureCpuWrite
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
static uint32_t mul(uint32_t a,uint32_t b){return EE_FPU_MUL_S(a,b);}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_texture_creation_frames.h"
#include "battle_action_printf_frames.h"
#include "magatuhi_helpers.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include "../tests/libc_stream_mode.h"
#include <stdio.h>
extern uint64_t nocturneEffectHostLo(void);
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void textureDivide(uint32_t n,uint32_t d){int64_t a=(int32_t)n,c=(int32_t)d;uint32_t q=c?(uint32_t)(a/c):(a<0?1u:UINT32_MAX),r=c?(uint32_t)(a%c):n;EE_ANCHOR_DIVU_STATE(q,r);}
/* A genuine unresolved game callback boundary, never a replacement result.
 * The actual VRAM-pressure target is latched before the caller's delay slot.
 */
static void texturePressure(uint64_t target){fprintf(stderr,"Unrecovered native VRAM pressure callback %08x\n",(uint32_t)target);abort();}
/* Original four-instruction registered leaves. The syscall supplies only its
 * explicitly authored external reply; no game function result is provided.
 */
static void waitSemaphore(void){nocturneEffectAxisNoteEntry(0x002dbee0);set(3,0x44);uint64_t a=cpu(4);set(2,nocturneLibcStreamKernel(0x44,1,&a));}
static void signalSemaphore(void){nocturneEffectAxisNoteEntry(0x002dbec0);set(3,0x42);uint64_t a=cpu(4);set(2,nocturneLibcStreamKernel(0x42,1,&a));}

uint64_t ps2BattleActionTexture_0015C2C8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015c2c8u);
uint64_t incoming=cpu(31);
/* 0015c2c8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015c2cc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015c2d0: move s1,zero */ set(17,cpu(0));
/* 0015c2d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015c2d8: beq a0,zero,0x0015c2ec */ {int taken=(cpu(4)==cpu(0));/* delay 0015c2dc */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_0015c2ec;}}
/* 0015c2e0: jal 0x0015caf0 */ set(31,0x0015c2e8u);/* delay 0015c2e4 */ set(2,ps2BattleActionTexture_0015CAF0(cpu(4)));
/* 0015c2e8: move s1,v0 */ set(17,cpu(2));
L_0015c2ec:;
/* 0015c2ec: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0015c2f0: sll a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)<<2));
/* 0015c2f4: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0015c2f8: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 0015c2fc: jal 0x002a8af8 */ set(31,0x0015c304u);/* delay 0015c300 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000006c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015c304: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0015c308: move s0,v0 */ set(16,cpu(2));
/* 0015c30c: move a1,zero */ set(5,cpu(0));
/* 0015c310: addiu v0,s0,0x6c */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x0000006c)));
/* 0015c314: sw s1,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(17));
/* 0015c318: sw v0,0x60(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(2));
/* 0015c31c: move a0,s0 */ set(4,cpu(16));
/* 0015c320: sh v1,0x50(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000050)),(uint16_t)cpu(3));
/* 0015c324: sw zero,0x48(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 0015c328: sw zero,0x4c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));
/* 0015c32c: jal 0x0015c940 */ set(31,0x0015c334u);/* delay 0015c330 */ sh(ea(16,(int32_t)UINT32_C(0x0000003c)),(uint16_t)cpu(0));ps2BattleActionTexture_0015C940(cpu(4),cpu(5));
/* 0015c334: move v0,s0 */ set(2,cpu(16));
/* 0015c338: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015c33c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015c340: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015c344: jr ra */ {uint64_t target=cpu(31);/* delay 0015c348 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_0015CAF0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015caf0u);
uint64_t incoming=cpu(31);
/* 0015caf0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 0015caf4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015caf8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015cafc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015cb00: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015cb04: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0015cb08: move s5,zero */ set(21,cpu(0));
/* 0015cb0c: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0015cb10: move s6,a0 */ set(22,cpu(4));
/* 0015cb14: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0015cb18: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0015cb1c: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0015cb20: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0015cb24: lw a0,0x0(s6) */ lw(4,ea(22,(int32_t)UINT32_C(0x00000000)));
/* 0015cb28: addu s3,s6,a0 */ set(19,sx((uint32_t)cpu(22)+(uint32_t)cpu(4)));
/* 0015cb2c: lw s4,0x0(s3) */ lw(20,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0015cb30: addiu s3,s3,0x4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000004)));
/* 0015cb34: sll v0,s4,0x2 */ set(2,sx((uint32_t)cpu(20)<<2));
/* 0015cb38: addu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(20)));
/* 0015cb3c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0015cb40: subu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(20)));
/* 0015cb44: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0015cb48: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0015cb4c: jal 0x002a9038 */ set(31,0x0015cb54u);/* delay 0015cb50 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000001c)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 0015cb54: move s1,v0 */ set(17,cpu(2));
/* 0015cb58: jal 0x002a9688 */ set(31,0x0015cb60u);/* delay 0015cb5c */ set(4,cpu(17));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 0015cb60: move a1,s6 */ set(5,cpu(22));
/* 0015cb64: move s2,v0 */ set(18,cpu(2));
/* 0015cb68: lw a2,0x0(s6) */ lw(6,ea(22,(int32_t)UINT32_C(0x00000000)));
/* 0015cb6c: addiu s0,s2,0x1c */ set(16,sx((uint32_t)cpu(18)+UINT32_C(0x0000001c)));
/* 0015cb70: sw s1,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 0015cb74: jal 0x002d43a4 */ set(31,0x0015cb7cu);/* delay 0015cb78 */ set(4,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015cb7c: sw s0,0x4(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 0015cb80: sw s4,0x10(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(20));
/* 0015cb84: addiu v0,s2,0x24 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000024)));
/* 0015cb88: sw v0,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0015cb8c: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0015cb90: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 0015cb94: addiu s0,s0,0x8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));
/* 0015cb98: blez s4,0x0015cbcc */ {int taken=((int64_t)cpu(20)<=0);/* delay 0015cb9c */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(16));if(taken){goto L_0015cbcc;}}
L_0015cba0:;
/* 0015cba0: lw a0,0x0(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0015cba4: addiu s3,s3,0x4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000004)));
/* 0015cba8: jal 0x0015b1b0 */ set(31,0x0015cbb0u);/* delay 0015cbac */ set(4,sx((uint32_t)cpu(22)+(uint32_t)cpu(4)));set(2,ps2BattleActionTexture_0015B1B0(cpu(4)));
/* 0015cbb0: lw a1,0x18(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 0015cbb4: sll v1,s5,0x2 */ set(3,sx((uint32_t)cpu(21)<<2));
/* 0015cbb8: addiu s5,s5,0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));
/* 0015cbbc: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0015cbc0: slt a0,s5,s4 */ set(4,(int64_t)cpu(21)<(int64_t)cpu(20));
/* 0015cbc4: bne a0,zero,0x0015cba0 */ {int taken=(cpu(4)!=cpu(0));/* delay 0015cbc8 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_0015cba0;}}
L_0015cbcc:;
/* 0015cbcc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0015cbd0: lw v1,0x4(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0015cbd4: sw v0,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 0015cbd8: sw v0,0x14(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 0015cbdc: lw s1,0x4(v1) */ lw(17,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0015cbe0: blez s1,0x0015cc94 */ {int taken=((int64_t)cpu(17)<=0);/* delay 0015cbe4 */ set(21,cpu(0));if(taken){goto L_0015cc94;}}
/* 0015cbe8: lui s8,0x1000 */ set(30,sx(UINT32_C(0x10000000)));
/* 0015cbec: lui s7,0x53 */ set(23,sx(UINT32_C(0x00530000)));
/* 0015cbf0: li s3,0x2 */ set(19,sx(UINT32_C(0x00000002)));
/* 0015cbf4: lui s6,0x53 */ set(22,sx(UINT32_C(0x00530000)));
/* 0015cbf8: lui s4,0x53 */ set(20,sx(UINT32_C(0x00530000)));
/* 0015cbfc: move s0,zero */ set(16,cpu(0));
/* 0015cc00: lw v0,0x8(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 0015cc04: nop  */ 
L_0015cc08:;
/* 0015cc08: addu v1,v0,s0 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 0015cc0c: lw v0,0x10(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0015cc10: and v0,v0,s8 */ set(2,cpu(2)&cpu(30));
/* 0015cc14: beq v0,zero,0x0015cc40 */ {int taken=(cpu(2)==cpu(0));/* delay 0015cc18 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000014)));if(taken){goto L_0015cc40;}}
/* 0015cc1c: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 0015cc20: move a1,s5 */ set(5,cpu(21));
/* 0015cc24: addiu a0,s7,0x2cb8 */ set(4,sx((uint32_t)cpu(23)+UINT32_C(0x00002cb8)));
/* 0015cc28: sw v0,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 0015cc2c: jal 0x002d4748 */ set(31,0x0015cc34u);/* delay 0015cc30 */ set(6,cpu(2));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));
/* 0015cc34: b 0x0015cc88 */ /* delay 0015cc38 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));goto L_0015cc88;
L_0015cc40:;
/* 0015cc40: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0015cc44: andi v1,v0,0x80 */ set(3,cpu(2)&UINT32_C(0x00000080));
/* 0015cc48: andi v0,v0,0x40 */ set(2,cpu(2)&UINT32_C(0x00000040));
/* 0015cc4c: beq v0,zero,0x0015cc70 */ {int taken=(cpu(2)==cpu(0));/* delay 0015cc50 */ set(5,cpu(21));if(taken){goto L_0015cc70;}}
/* 0015cc54: sw s3,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(19));
/* 0015cc58: addiu a0,s6,0x2cd8 */ set(4,sx((uint32_t)cpu(22)+UINT32_C(0x00002cd8)));
/* 0015cc5c: jal 0x002d4748 */ set(31,0x0015cc64u);/* delay 0015cc60 */ set(6,sx(UINT32_C(0x00000002)));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));
/* 0015cc64: b 0x0015cc88 */ /* delay 0015cc68 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));goto L_0015cc88;
L_0015cc70:;
/* 0015cc70: beq v1,zero,0x0015cc84 */ {int taken=(cpu(3)==cpu(0));/* delay 0015cc74 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0x00002cf8)));if(taken){goto L_0015cc84;}}
/* 0015cc78: sw s3,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(19));
/* 0015cc7c: jal 0x002d4748 */ set(31,0x0015cc84u);/* delay 0015cc80 */ set(6,sx(UINT32_C(0x00000002)));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));
L_0015cc84:;
/* 0015cc84: addiu s5,s5,0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));
L_0015cc88:;
/* 0015cc88: slt v0,s5,s1 */ set(2,(int64_t)cpu(21)<(int64_t)cpu(17));
/* 0015cc8c: bnel v0,zero,0x0015cc08 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0015cc90 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000008)));goto L_0015cc08;}}
L_0015cc94:;
/* 0015cc94: move v0,s2 */ set(2,cpu(18));
/* 0015cc98: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015cc9c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015cca0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015cca4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015cca8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0015ccac: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0015ccb0: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0015ccb4: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0015ccb8: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0015ccbc: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0015ccc0: jr ra */ {uint64_t target=cpu(31);/* delay 0015ccc4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_0015B1B0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015b1b0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0015b1b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015b1b4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015b1b8: move s2,a0 */ set(18,cpu(4));
/* 0015b1bc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015b1c0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015b1c4: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015b1c8: jal 0x002a9038 */ set(31,0x0015b1d0u);/* delay 0015b1cc */ set(4,sx(UINT32_C(0x0000044c)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 0015b1d0: move s0,v0 */ set(16,cpu(2));
/* 0015b1d4: jal 0x002a9688 */ set(31,0x0015b1dcu);/* delay 0015b1d8 */ set(4,cpu(16));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 0015b1dc: li a0,0x3 */ set(4,sx(UINT32_C(0x00000003)));
/* 0015b1e0: addiu s1,v0,0x400 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00000400)));
/* 0015b1e4: addiu v1,v0,0x438 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000438)));
/* 0015b1e8: sw zero,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 0015b1ec: sw s0,0x40(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(16));
/* 0015b1f0: sw v0,0x44(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 0015b1f4: sw zero,0x3fc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x000003fc)),(uint32_t)cpu(0));
/* 0015b1f8: sw s1,0x48(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(17));
/* 0015b1fc: sh zero,0x4(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(0));
L_0015b200:;
/* 0015b200: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 0015b204: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0015b208: nop  */ 
/* 0015b20c: nop  */ 
/* 0015b210: nop  */ 
/* 0015b214: bgez a0,0x0015b200 */ {int taken=((int64_t)cpu(4)>=0);/* delay 0015b218 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xfffffffc)));if(taken){goto L_0015b200;}}
/* 0015b21c: sh zero,0x3c(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000003c)),(uint16_t)cpu(0));
/* 0015b220: jal 0x002abe08 */ set(31,0x0015b228u);/* delay 0015b224 */ set(4,cpu(18));set(2,ps2BattleActionTexture_002ABE08(cpu(4)));
/* 0015b228: lw a3,0x8(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 0015b22c: move t0,v0 */ set(8,cpu(2));
/* 0015b230: move v0,s1 */ set(2,cpu(17));
/* 0015b234: lhu a2,0xe(t0) */ set(6,half(ea(8,(int32_t)UINT32_C(0x0000000e))));
/* 0015b238: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 0015b23c: lhu v1,0xc(t0) */ set(3,half(ea(8,(int32_t)UINT32_C(0x0000000c))));
/* 0015b240: sll a2,a2,0x14 */ set(6,sx((uint32_t)cpu(6)<<20));
/* 0015b244: lui at,0x3d80 */ set(1,sx(UINT32_C(0x3d800000)));
/* 0015b248: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0015b24c: sll v1,v1,0x14 */ set(3,sx((uint32_t)cpu(3)<<20));
/* 0015b250: sra a0,a2,0x15 */ set(4,sx((uint32_t)((int32_t)cpu(6)>>21)));
/* 0015b254: sra a1,v1,0x15 */ set(5,sx((uint32_t)((int32_t)cpu(3)>>21)));
/* 0015b258: sra v1,v1,0x10 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 0015b25c: mtc1 a0,f0 */ f[0]=(uint32_t)cpu(4);
/* 0015b260: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0015b264: sra a2,a2,0x10 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>16)));
/* 0015b268: mtc1 a1,f1 */ f[1]=(uint32_t)cpu(5);
/* 0015b26c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0015b270: sw a3,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(7));
/* 0015b274: sh v1,0x14(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(3));
/* 0015b278: sh a2,0x1a(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000001a)),(uint16_t)cpu(6));
/* 0015b27c: mul.S f0,f0,f2 */ f[0]=mul(f[0],f[2]);
/* 0015b280: sw t0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(8));
/* 0015b284: mul.S f1,f1,f2 */ f[1]=mul(f[1],f[2]);
/* 0015b288: sh zero,0xc(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(0));
/* 0015b28c: sh zero,0xe(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(0));
/* 0015b290: sh v1,0x10(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000010)),(uint16_t)cpu(3));
/* 0015b294: swc1 f0,0x28(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000028)),f[0]);
/* 0015b298: swc1 f1,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),f[1]);
/* 0015b29c: sh zero,0x12(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000012)),(uint16_t)cpu(0));
/* 0015b2a0: sh a2,0x16(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(6));
/* 0015b2a4: sh zero,0x18(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000018)),(uint16_t)cpu(0));
/* 0015b2a8: sw zero,0x1c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 0015b2ac: sw zero,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 0015b2b0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015b2b4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015b2b8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015b2bc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015b2c0: jr ra */ {uint64_t target=cpu(31);/* delay 0015b2c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionTexture_0015C940(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x0015c940u);
uint64_t incoming=cpu(31);
/* 0015c940: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 0015c944: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015c948: move s0,a1 */ set(16,cpu(5));
/* 0015c94c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015c950: move s1,a0 */ set(17,cpu(4));
/* 0015c954: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015c958: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 0015c95c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015c960: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 0015c964: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0015c968: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0015c96c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0015c970: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0015c974: lw s4,0x30(s1) */ lw(20,ea(17,(int32_t)UINT32_C(0x00000030)));
/* 0015c978: lw a0,0x8(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000008)));
/* 0015c97c: addu s3,a0,v0 */ set(19,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0015c980: lw v1,0xc(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 0015c984: bnel v1,zero,0x0015c998 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0015c988 */ lw(2,ea(19,(int32_t)UINT32_C(0x00000010)));goto L_0015c998;}}
/* 0015c98c: b 0x0015cacc */ /* delay 0015c990 */ sh(ea(17,(int32_t)UINT32_C(0x00000050)),(uint16_t)cpu(0));goto L_0015cacc;
L_0015c998:;
/* 0015c998: lui s2,0x1000 */ set(18,sx(UINT32_C(0x10000000)));
/* 0015c99c: and v0,v0,s2 */ set(2,cpu(2)&cpu(18));
/* 0015c9a0: beq v0,zero,0x0015ca30 */ {int taken=(cpu(2)==cpu(0));/* delay 0015c9a4 */ set(4,sx(UINT32_C(0x00530000)));if(taken){goto L_0015ca30;}}
/* 0015c9a8: move s5,zero */ set(21,cpu(0));
/* 0015c9ac: jal 0x002d4748 */ set(31,0x0015c9b4u);/* delay 0015c9b0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00002c70)));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));
/* 0015c9b4: sw s2,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(18));
/* 0015c9b8: sw s0,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(16));
/* 0015c9bc: lw a0,0x4(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000004)));
/* 0015c9c0: lw v0,0xc(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 0015c9c4: sw v0,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(2));
/* 0015c9c8: lw v1,0x0(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0015c9cc: lw v0,0xc(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 0015c9d0: beq v0,zero,0x0015caa8 */ {int taken=(cpu(2)==cpu(0));/* delay 0015c9d4 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));if(taken){goto L_0015caa8;}}
/* 0015c9d8: lw a2,0x60(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000060)));
/* 0015c9dc: move s0,a0 */ set(16,cpu(4));
/* 0015c9e0: move s2,zero */ set(18,cpu(0));
/* 0015c9e4: nop  */ 
L_0015c9e8:;
/* 0015c9e8: lh a1,0x0(s0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 0015c9ec: addu a2,a2,s2 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(18)));
/* 0015c9f0: move a0,s4 */ set(4,cpu(20));
/* 0015c9f4: jal 0x0015c908 */ set(31,0x0015c9fcu);/* delay 0015c9f8 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));ps2BattleActionTexture_0015C908(cpu(4),cpu(5),cpu(6));
/* 0015c9fc: lw v0,0x60(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000060)));
/* 0015ca00: lh v1,0x2(s0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000002))));
/* 0015ca04: addiu s0,s0,0x18 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000018)));
/* 0015ca08: move a2,v0 */ set(6,cpu(2));
/* 0015ca0c: addu v0,s2,a2 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(6)));
/* 0015ca10: subu v1,zero,v1 */ set(3,sx((uint32_t)cpu(0)-(uint32_t)cpu(3)));
/* 0015ca14: sw v1,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 0015ca18: lw v0,0xc(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 0015ca1c: sltu v0,s5,v0 */ set(2,cpu(21)<cpu(2));
/* 0015ca20: bne v0,zero,0x0015c9e8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0015ca24 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));if(taken){goto L_0015c9e8;}}
/* 0015ca28: b 0x0015caac */ /* delay 0015ca2c */ lw(2,ea(19,(int32_t)UINT32_C(0x00000008)));goto L_0015caac;
L_0015ca30:;
/* 0015ca30: lw v0,0x8(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 0015ca34: andi v0,v0,0xc0 */ set(2,cpu(2)&UINT32_C(0x000000c0));
/* 0015ca38: beq v0,zero,0x0015ca88 */ {int taken=(cpu(2)==cpu(0));/* delay 0015ca3c */ set(4,sx(UINT32_C(0x00530000)));if(taken){goto L_0015ca88;}}
/* 0015ca40: jal 0x002d4748 */ set(31,0x0015ca48u);/* delay 0015ca44 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00002c88)));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));
/* 0015ca48: lw v1,0x8(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 0015ca4c: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0015ca50: lw a2,0x60(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000060)));
/* 0015ca54: sw s0,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(16));
/* 0015ca58: move a0,s4 */ set(4,cpu(20));
/* 0015ca5c: sw v1,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(3));
/* 0015ca60: move a1,s0 */ set(5,cpu(16));
/* 0015ca64: jal 0x0015c908 */ set(31,0x0015ca6cu);/* delay 0015ca68 */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(2));ps2BattleActionTexture_0015C908(cpu(4),cpu(5),cpu(6));
/* 0015ca6c: lw a2,0x60(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000060)));
/* 0015ca70: move a0,s4 */ set(4,cpu(20));
/* 0015ca74: addiu a1,s0,0x1 */ set(5,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
/* 0015ca78: jal 0x0015c908 */ set(31,0x0015ca80u);/* delay 0015ca7c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000014)));ps2BattleActionTexture_0015C908(cpu(4),cpu(5),cpu(6));
/* 0015ca80: b 0x0015caac */ /* delay 0015ca84 */ lw(2,ea(19,(int32_t)UINT32_C(0x00000008)));goto L_0015caac;
L_0015ca88:;
/* 0015ca88: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0015ca8c: sw zero,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(0));
/* 0015ca90: sw v0,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(2));
/* 0015ca94: move a0,s4 */ set(4,cpu(20));
/* 0015ca98: sw s0,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(16));
/* 0015ca9c: move a1,s0 */ set(5,cpu(16));
/* 0015caa0: jal 0x0015c908 */ set(31,0x0015caa8u);/* delay 0015caa4 */ lw(6,ea(17,(int32_t)UINT32_C(0x00000060)));ps2BattleActionTexture_0015C908(cpu(4),cpu(5),cpu(6));
L_0015caa8:;
/* 0015caa8: lw v0,0x8(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000008)));
L_0015caac:;
/* 0015caac: andi v0,v0,0x100 */ set(2,cpu(2)&UINT32_C(0x00000100));
/* 0015cab0: beql v0,zero,0x0015cac8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0015cab4 */ set(2,sx(UINT32_C(0x00000001)));goto L_0015cac8;}}
/* 0015cab8: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0015cabc: jal 0x002d4748 */ set(31,0x0015cac4u);/* delay 0015cac0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00002ca0)));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));
/* 0015cac4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_0015cac8:;
/* 0015cac8: sh v0,0x50(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000050)),(uint16_t)cpu(2));
L_0015cacc:;
/* 0015cacc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015cad0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015cad4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015cad8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015cadc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0015cae0: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0015cae4: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0015cae8: jr ra */ {uint64_t target=cpu(31);/* delay 0015caec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionTexture_0015C908(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x0015c908u);
uint64_t incoming=cpu(31);
/* 0015c908: sll v0,a1,0x2 */ set(2,sx((uint32_t)cpu(5)<<2));
/* 0015c90c: lw v1,0x8(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 0015c910: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0015c914: lw a1,0x4(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 0015c918: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0015c91c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0015c920: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0015c924: sw v1,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 0015c928: addu a1,a1,v0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 0015c92c: sw zero,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 0015c930: lh v0,0x12(a1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000012))));
/* 0015c934: sw a1,0x10(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));
/* 0015c938: jr ra */ {uint64_t target=cpu(31);/* delay 0015c93c */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionTexture_002ABE08(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002abe08u);
uint64_t incoming=cpu(31);
/* 002abe08: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002abe0c: move a1,zero */ set(5,cpu(0));
/* 002abe10: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002abe14: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002abe18: j 0x002abc90 */ /* delay 002abe1c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);set(2,ps2BattleActionTexture_002ABC90(cpu(4),cpu(5)));return cpu(2);
}
uint64_t ps2BattleActionTexture_002ABC90(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002abc90u);
uint64_t incoming=cpu(31);
/* 002abc90: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002abc94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002abc98: move s0,a0 */ set(16,cpu(4));
/* 002abc9c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002abca0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002abca4: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002abca8: move s8,a1 */ set(30,cpu(5));
/* 002abcac: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002abcb0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002abcb4: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002abcb8: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002abcbc: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002abcc0: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002abcc4: lh a0,0x12(s0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000012))));
/* 002abcc8: lh a1,0x14(s0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 002abccc: lbu a2,0x16(s0) */ set(6,byte(ea(16,(int32_t)UINT32_C(0x00000016))));
/* 002abcd0: lbu a3,0x17(s0) */ set(7,byte(ea(16,(int32_t)UINT32_C(0x00000017))));
/* 002abcd4: lbu t0,0x11(s0) */ set(8,byte(ea(16,(int32_t)UINT32_C(0x00000011))));
/* 002abcd8: jal 0x002ab6e8 */ set(31,0x002abce0u);/* delay 002abcdc */ set(9,byte(ea(16,(int32_t)UINT32_C(0x00000010))));set(2,ps2BattleActionTexture_002AB6E8(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9)));
/* 002abce0: lhu v1,0x18(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000018))));
/* 002abce4: move s1,v0 */ set(17,cpu(2));
/* 002abce8: sh v1,0x1c(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint16_t)cpu(3));
/* 002abcec: move a0,s1 */ set(4,cpu(17));
/* 002abcf0: lbu v0,0x1a(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x0000001a))));
/* 002abcf4: sb v0,0x1e(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000001e)),(uint8_t)cpu(2));
/* 002abcf8: lbu v1,0x1b(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x0000001b))));
/* 002abcfc: sb v1,0x1f(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000001f)),(uint8_t)cpu(3));
/* 002abd00: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 002abd04: sw v0,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 002abd08: lw v1,0x20(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002abd0c: sw v1,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(3));
/* 002abd10: lbu v0,0x1(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 002abd14: andi v0,v0,0xf0 */ set(2,cpu(2)&UINT32_C(0x000000f0));
/* 002abd18: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002abd1c: jal 0x002aaff0 */ set(31,0x002abd24u);/* delay 002abd20 */ set(20,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));set(2,ps2BattleActionTexture_002AAFF0(cpu(4)));
/* 002abd24: beql v0,zero,0x002abd64 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002abd28 */ set(22,byte(ea(17,(int32_t)UINT32_C(0x0000001a))));goto L_002abd64;}}
/* 002abd2c: jal 0x002ab688 */ set(31,0x002abd34u);/* delay 002abd30 */ set(4,cpu(17));ps2BattleActionTexture_002AB688(cpu(4));
/* 002abd34: move a0,s1 */ set(4,cpu(17));
/* 002abd38: jal 0x002ab6c8 */ set(31,0x002abd40u);/* delay 002abd3c */ set(5,cpu(20));set(2,ps2BattleActionTexture_002AB6C8(cpu(4),cpu(5)));
/* 002abd40: jal 0x002aaff8 */ set(31,0x002abd48u);/* delay 002abd44 */ set(4,cpu(17));set(2,ps2EffectTexturePaletteAddress_002AAFF8(cpu(4)));
/* 002abd48: move a0,s1 */ set(4,cpu(17));
/* 002abd4c: move a2,s4 */ set(6,cpu(20));
/* 002abd50: move a1,v0 */ set(5,cpu(2));
/* 002abd54: jal 0x002ab2b0 */ set(31,0x002abd5cu);/* delay 002abd58 */ set(7,cpu(30));set(2,ps2BattleActionTexture_002AB2B0(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 002abd5c: move s4,v0 */ set(20,cpu(2));
/* 002abd60: lbu s6,0x1a(s1) */ set(22,byte(ea(17,(int32_t)UINT32_C(0x0000001a))));
L_002abd64:;
/* 002abd64: move a0,s1 */ set(4,cpu(17));
/* 002abd68: lh s2,0xc(s1) */ set(18,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002abd6c: lh s0,0xe(s1) */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 002abd70: jal 0x002ab010 */ set(31,0x002abd78u);/* delay 002abd74 */ set(21,byte(ea(17,(int32_t)UINT32_C(0x0000001b))));set(2,ps2EffectTextureBaseAddress_002AB010(cpu(4)));
/* 002abd78: move a0,s6 */ set(4,cpu(22));
/* 002abd7c: jal 0x002ab070 */ set(31,0x002abd84u);/* delay 002abd80 */ set(19,cpu(2));set(2,ps2BattleActionTexture_002AB070(cpu(4)));
/* 002abd84: move s7,v0 */ set(23,cpu(2));
L_002abd88:;
/* 002abd88: move t0,s4 */ set(8,cpu(20));
/* 002abd8c: move a0,s3 */ set(4,cpu(19));
/* 002abd90: move a1,s2 */ set(5,cpu(18));
/* 002abd94: move a2,s0 */ set(6,cpu(16));
/* 002abd98: move a3,s6 */ set(7,cpu(22));
/* 002abd9c: jal 0x002ab1a8 */ set(31,0x002abda4u);/* delay 002abda0 */ set(9,cpu(30));set(2,ps2BattleActionTexture_002AB1A8(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9)));
/* 002abda4: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
/* 002abda8: move s4,v0 */ set(20,cpu(2));
/* 002abdac: mult v0,s7,s2 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(23)*(int64_t)(int32_t)(uint32_t)cpu(18));EE_MAGATUHI_MULT_STATE(product);set(2,sx((uint32_t)product));}
/* 002abdb0: sra s2,s2,0x1 */ set(18,sx((uint32_t)((int32_t)cpu(18)>>1)));
/* 002abdb4: mult v0,v0,s0 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(2)*(int64_t)(int32_t)(uint32_t)cpu(16));EE_MAGATUHI_MULT_STATE(product);set(2,sx((uint32_t)product));}
/* 002abdb8: sra v0,v0,0x5 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>5)));
/* 002abdbc: addu s3,s3,v0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(2)));
/* 002abdc0: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002abdc4: bne s5,v0,0x002abd88 */ {int taken=(cpu(21)!=cpu(2));/* delay 002abdc8 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>1)));if(taken){goto L_002abd88;}}
/* 002abdcc: jal 0x002abb18 */ set(31,0x002abdd4u);/* delay 002abdd0 */ set(4,cpu(17));ps2BattleActionTexture_002ABB18(cpu(4));
/* 002abdd4: move v0,s1 */ set(2,cpu(17));
/* 002abdd8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002abddc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002abde0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002abde4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002abde8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002abdec: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002abdf0: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002abdf4: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002abdf8: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002abdfc: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002abe00: jr ra */ {uint64_t target=cpu(31);/* delay 002abe04 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_002AB6E8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);nocturneEffectAxisNoteEntry(0x002ab6e8u);
uint64_t incoming=cpu(31);
/* 002ab6e8: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002ab6ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab6f0: move s1,a2 */ set(17,cpu(6));
/* 002ab6f4: sltiu v0,s1,0x15 */ set(2,cpu(17)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000015));
/* 002ab6f8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ab6fc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ab700: move s3,a1 */ set(19,cpu(5));
/* 002ab704: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ab708: move s4,a3 */ set(20,cpu(7));
/* 002ab70c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ab710: move s5,t0 */ set(21,cpu(8));
/* 002ab714: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ab718: move s6,t1 */ set(22,cpu(9));
/* 002ab71c: move s2,a0 */ set(18,cpu(4));
/* 002ab720: move a0,zero */ set(4,cpu(0));
/* 002ab724: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab728: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ab72c: beq v0,zero,0x002ab830 */ {int taken=(cpu(2)==cpu(0));/* delay 002ab730 */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));if(taken){goto L_002ab830;}}
/* 002ab734: sll v0,s1,0x2 */ set(2,sx((uint32_t)cpu(17)<<2));
/* 002ab738: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002ab73c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002ab740: lw v1,-0x6b10(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffff94f0)));
/* 002ab744: jr v1 */ {uint64_t target=cpu(3);/* delay 002ab748 */ switch((uint32_t)target){case 0x002ab750u:goto L_002ab750;case 0x002ab758u:goto L_002ab758;case 0x002ab760u:goto L_002ab760;case 0x002ab770u:goto L_002ab770;case 0x002ab830u:goto L_002ab830;default:fprintf(stderr,"Unexpected native texture jump target %08x\n",(uint32_t)target);abort();}}
L_002ab750:;
/* 002ab750: b 0x002ab778 */ /* delay 002ab754 */ set(16,sx(UINT32_C(0x00000020)));goto L_002ab778;
L_002ab758:;
/* 002ab758: b 0x002ab778 */ /* delay 002ab75c */ set(16,sx(UINT32_C(0x00000010)));goto L_002ab778;
L_002ab760:;
/* 002ab760: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002ab764: b 0x002ab778 */ /* delay 002ab768 */ set(16,sx(UINT32_C(0x00000008)));goto L_002ab778;
L_002ab770:;
/* 002ab770: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002ab774: li s0,0x4 */ set(16,sx(UINT32_C(0x00000004)));
L_002ab778:;
/* 002ab778: beq a0,zero,0x002ab794 */ {int taken=(cpu(4)==cpu(0));/* delay 002ab77c */ set(23,cpu(0));if(taken){goto L_002ab794;}}
/* 002ab780: move a0,s1 */ set(4,cpu(17));
/* 002ab784: move a1,s5 */ set(5,cpu(21));
/* 002ab788: jal 0x002ab580 */ set(31,0x002ab790u);/* delay 002ab78c */ set(6,cpu(22));set(2,ps2BattleActionTexture_002AB580(cpu(4),cpu(5),cpu(6)));
/* 002ab790: move s7,v0 */ set(23,cpu(2));
L_002ab794:;
/* 002ab794: move a2,s2 */ set(6,cpu(18));
/* 002ab798: move a1,s3 */ set(5,cpu(19));
/* 002ab79c: move a0,zero */ set(4,cpu(0));
/* 002ab7a0: move a3,zero */ set(7,cpu(0));
/* 002ab7a4: nop  */ 
L_002ab7a8:;
/* 002ab7a8: mult v0,a2,a1 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(6)*(int64_t)(int32_t)(uint32_t)cpu(5));EE_MAGATUHI_MULT_STATE(product);set(2,sx((uint32_t)product));}
/* 002ab7ac: sra a2,a2,0x1 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>1)));
/* 002ab7b0: move v1,a3 */ set(3,cpu(7));
/* 002ab7b4: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 002ab7b8: sra a1,a1,0x1 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>1)));
/* 002ab7bc: mult v0,v0,s0 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(2)*(int64_t)(int32_t)(uint32_t)cpu(16));EE_MAGATUHI_MULT_STATE(product);set(2,sx((uint32_t)product));}
/* 002ab7c0: sra v0,v0,0x5 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>5)));
/* 002ab7c4: bne v1,s4,0x002ab7a8 */ {int taken=(cpu(3)!=cpu(20));/* delay 002ab7c8 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));if(taken){goto L_002ab7a8;}}
/* 002ab7cc: jal 0x002aa558 */ set(31,0x002ab7d4u);/* delay 002ab7d0 */ set(5,sx(UINT32_C(0x00000002)));set(2,ps2BattleActionTexture_002AA558(cpu(4),cpu(5)));
/* 002ab7d4: move a0,s2 */ set(4,cpu(18));
/* 002ab7d8: sh s2,0x14(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(18));
/* 002ab7dc: move a1,s3 */ set(5,cpu(19));
/* 002ab7e0: sh s3,0x16(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(19));
/* 002ab7e4: move a2,s1 */ set(6,cpu(17));
/* 002ab7e8: sw s1,0x18(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(17));
/* 002ab7ec: move a3,s4 */ set(7,cpu(20));
/* 002ab7f0: move t1,s5 */ set(9,cpu(21));
/* 002ab7f4: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ab7f8: move t2,s6 */ set(10,cpu(22));
/* 002ab7fc: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ab800: move t3,s7 */ set(11,cpu(23));
/* 002ab804: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ab808: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab80c: move t0,v0 */ set(8,cpu(2));
/* 002ab810: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab814: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ab818: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ab81c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ab820: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ab824: j 0x002ab388 */ /* delay 002ab828 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(cpu(31),incoming);set(2,ps2BattleActionTexture_002AB388(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10),cpu(11)));return cpu(2);
L_002ab830:;
/* 002ab830: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab834: move v0,zero */ set(2,cpu(0));
/* 002ab838: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab83c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ab840: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ab844: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ab848: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ab84c: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ab850: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ab854: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ab858: jr ra */ {uint64_t target=cpu(31);/* delay 002ab85c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_002AB580(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x002ab580u);
uint64_t incoming=cpu(31);
/* 002ab580: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002ab584: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002ab588: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab58c: move s0,a1 */ set(16,cpu(5));
/* 002ab590: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab594: beq s0,v0,0x002ab5d0 */ {int taken=(cpu(16)==cpu(2));/* delay 002ab598 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002ab5d0;}}
/* 002ab59c: slti v0,s0,0x3 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 002ab5a0: beq v0,zero,0x002ab5b8 */ {int taken=(cpu(2)==cpu(0));/* delay 002ab5a4 */ set(2,sx(UINT32_C(0x0000000a)));if(taken){goto L_002ab5b8;}}
/* 002ab5a8: beq s0,zero,0x002ab5c8 */ {int taken=(cpu(16)==cpu(0));/* delay 002ab5ac */ set(2,cpu(0));if(taken){goto L_002ab5c8;}}
/* 002ab5b0: b 0x002ab648 */ /* delay 002ab5b4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002ab648;
L_002ab5b8:;
/* 002ab5b8: beq s0,v0,0x002ab5d0 */ {int taken=(cpu(16)==cpu(2));/* delay 002ab5bc */ set(2,cpu(0));if(taken){goto L_002ab5d0;}}
/* 002ab5c0: b 0x002ab648 */ /* delay 002ab5c4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002ab648;
L_002ab5c8:;
/* 002ab5c8: b 0x002ab5d4 */ /* delay 002ab5cc */ set(5,sx(UINT32_C(0x00000020)));goto L_002ab5d4;
L_002ab5d0:;
/* 002ab5d0: li a1,0x10 */ set(5,sx(UINT32_C(0x00000010)));
L_002ab5d4:;
/* 002ab5d4: addiu a0,a0,-0x13 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffed)));
/* 002ab5d8: sltiu v0,a0,0x1a */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000001a));
/* 002ab5dc: beq v0,zero,0x002ab644 */ {int taken=(cpu(2)==cpu(0));/* delay 002ab5e0 */ set(2,cpu(0));if(taken){goto L_002ab644;}}
/* 002ab5e4: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 002ab5e8: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002ab5ec: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002ab5f0: lw v1,-0x6b80(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffff9480)));
/* 002ab5f4: jr v1 */ {uint64_t target=cpu(3);/* delay 002ab5f8 */ switch((uint32_t)target){case 0x002ab600u:goto L_002ab600;case 0x002ab610u:goto L_002ab610;case 0x002ab620u:goto L_002ab620;default:fprintf(stderr,"Unexpected native texture jump target %08x\n",(uint32_t)target);abort();}}
L_002ab600:;
/* 002ab600: sll a0,a1,0x3 */ set(4,sx((uint32_t)cpu(5)<<3));
/* 002ab604: b 0x002ab628 */ /* delay 002ab608 */ set(17,sx(UINT32_C(0x00000020)));goto L_002ab628;
L_002ab610:;
/* 002ab610: li a0,0x40 */ set(4,sx(UINT32_C(0x00000040)));
/* 002ab614: b 0x002ab628 */ /* delay 002ab618 */ set(17,sx(UINT32_C(0x00000008)));goto L_002ab628;
L_002ab620:;
/* 002ab620: b 0x002ab644 */ /* delay 002ab624 */ set(2,cpu(0));goto L_002ab644;
L_002ab628:;
/* 002ab628: jal 0x002aa558 */ set(31,0x002ab630u);/* delay 002ab62c */ set(5,sx(UINT32_C(0x00000003)));set(2,ps2BattleActionTexture_002AA558(cpu(4),cpu(5)));
/* 002ab630: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 002ab634: move v1,v0 */ set(3,cpu(2));
/* 002ab638: sw s0,0x18(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(16));
/* 002ab63c: sh a0,0x14(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(4));
/* 002ab640: sh s1,0x16(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(17));
L_002ab644:;
/* 002ab644: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002ab648:;
/* 002ab648: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab64c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ab650: jr ra */ {uint64_t target=cpu(31);/* delay 002ab654 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_002AA558(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002aa558u);
uint64_t incoming=cpu(31);
/* 002aa558: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002aa55c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa560: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aa564: move s2,a0 */ set(18,cpu(4));
/* 002aa568: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aa56c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002aa570: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa574: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002aa578: jal 0x002e4070 */ set(31,0x002aa580u);/* delay 002aa57c */ set(19,cpu(5));set(2,ps2EffectKernelDisableInterrupts_002E4070());
/* 002aa580: lw s0,-0x20dc(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffdf24)));
/* 002aa584: move s4,v0 */ set(20,cpu(2));
L_002aa588:;
/* 002aa588: bnel s0,zero,0x002aa5b8 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 002aa58c */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_002aa5b8;}}
/* 002aa590: beq s4,zero,0x002aa5a4 */ {int taken=(cpu(20)==cpu(0));/* delay 002aa594 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6ec)));if(taken){goto L_002aa5a4;}}
/* 002aa598: jal 0x002e40b8 */ set(31,0x002aa5a0u);/* delay 002aa59c */ set(2,ps2EffectKernelEnableInterrupts_002E40B8());
/* 002aa5a0: lw v0,-0x2914(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6ec)));
L_002aa5a4:;
/* 002aa5a4: beq v0,zero,0x002aa5b4 */ {int taken=(cpu(2)==cpu(0));/* delay 002aa5a8 */ set(4,cpu(18));if(taken){goto L_002aa5b4;}}
/* 002aa5ac: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002aa5b4u);/* delay 002aa5b0 */ set(5,cpu(19));texturePressure(target);}
L_002aa5b4:;
/* 002aa5b4: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
L_002aa5b8:;
/* 002aa5b8: bnel v0,zero,0x002aa588 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002aa5bc */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002aa588;}}
/* 002aa5c0: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002aa5c4: slt v0,v1,s2 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(18));
/* 002aa5c8: bnel v0,zero,0x002aa588 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002aa5cc */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002aa588;}}
/* 002aa5d0: bne v1,s2,0x002aa5f0 */ {int taken=(cpu(3)!=cpu(18));/* delay 002aa5d4 */ if(taken){goto L_002aa5f0;}}
/* 002aa5d8: beq s4,zero,0x002aa5e8 */ {int taken=(cpu(20)==cpu(0));/* delay 002aa5dc */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));if(taken){goto L_002aa5e8;}}
/* 002aa5e0: jal 0x002e40b8 */ set(31,0x002aa5e8u);/* delay 002aa5e4 */ set(2,ps2EffectKernelEnableInterrupts_002E40B8());
L_002aa5e8:;
/* 002aa5e8: b 0x002aa658 */ /* delay 002aa5ec */ set(2,cpu(16));goto L_002aa658;
L_002aa5f0:;
/* 002aa5f0: jal 0x002a8af8 */ set(31,0x002aa5f8u);/* delay 002aa5f4 */ set(4,sx(UINT32_C(0x0000001c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002aa5f8: move s1,v0 */ set(17,cpu(2));
/* 002aa5fc: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002aa600: bne v0,zero,0x002aa610 */ {int taken=(cpu(2)!=cpu(0));/* delay 002aa604 */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_002aa610;}}
/* 002aa608: b 0x002aa618 */ /* delay 002aa60c */ sw(ea(28,(int32_t)UINT32_C(0xffffdf24)),(uint32_t)cpu(17));goto L_002aa618;
L_002aa610:;
/* 002aa610: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002aa614: sw s1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
L_002aa618:;
/* 002aa618: sw s3,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));
/* 002aa61c: sw s1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 002aa620: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002aa624: lw v1,0xc(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002aa628: subu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 002aa62c: sw s2,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 002aa630: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002aa634: sw s0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002aa638: sw v1,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 002aa63c: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002aa640: subu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 002aa644: beq s4,zero,0x002aa654 */ {int taken=(cpu(20)==cpu(0));/* delay 002aa648 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));if(taken){goto L_002aa654;}}
/* 002aa64c: jal 0x002e40b8 */ set(31,0x002aa654u);/* delay 002aa650 */ set(2,ps2EffectKernelEnableInterrupts_002E40B8());
L_002aa654:;
/* 002aa654: move v0,s1 */ set(2,cpu(17));
L_002aa658:;
/* 002aa658: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aa65c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa660: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aa664: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aa668: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002aa66c: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002aa670: jr ra */ {uint64_t target=cpu(31);/* delay 002aa674 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_002AB388(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);set(10,a6);set(11,a7);nocturneEffectAxisNoteEntry(0x002ab388u);
uint64_t incoming=cpu(31);
/* 002ab388: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002ab38c: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ab390: move s7,a0 */ set(23,cpu(4));
/* 002ab394: li a0,0x40 */ set(4,sx(UINT32_C(0x00000040)));
/* 002ab398: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab39c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab3a0: move s1,t2 */ set(17,cpu(10));
/* 002ab3a4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ab3a8: move s2,t1 */ set(18,cpu(9));
/* 002ab3ac: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ab3b0: move s3,t3 */ set(19,cpu(11));
/* 002ab3b4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ab3b8: move s4,a1 */ set(20,cpu(5));
/* 002ab3bc: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ab3c0: move s5,a2 */ set(21,cpu(6));
/* 002ab3c4: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ab3c8: move s6,a3 */ set(22,cpu(7));
/* 002ab3cc: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ab3d0: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002ab3d4: jal 0x002a8ba8 */ set(31,0x002ab3dcu);/* delay 002ab3d8 */ set(30,cpu(8));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 002ab3dc: move s0,v0 */ set(16,cpu(2));
/* 002ab3e0: sb s1,0x18(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(17));
/* 002ab3e4: move a0,s0 */ set(4,cpu(16));
/* 002ab3e8: sb s2,0x19(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000019)),(uint8_t)cpu(18));
/* 002ab3ec: sh s7,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(23));
/* 002ab3f0: sh s4,0xe(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(20));
/* 002ab3f4: sb s5,0x1a(s0) */ sb(ea(16,(int32_t)UINT32_C(0x0000001a)),(uint8_t)cpu(21));
/* 002ab3f8: sb s6,0x1b(s0) */ sb(ea(16,(int32_t)UINT32_C(0x0000001b)),(uint8_t)cpu(22));
/* 002ab3fc: sw s3,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 002ab400: jal 0x002ab360 */ set(31,0x002ab408u);/* delay 002ab404 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(30));ps2BattleActionTexture_002AB360(cpu(4));
/* 002ab408: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
/* 002ab40c: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 002ab410: move v0,s0 */ set(2,cpu(16));
/* 002ab414: sw v1,0x38(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(3));
/* 002ab418: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab41c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab420: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002ab424: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002ab428: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ab42c: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ab430: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ab434: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ab438: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ab43c: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002ab440: jr ra */ {uint64_t target=cpu(31);/* delay 002ab444 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionTexture_002AB360(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002ab360u);
uint64_t incoming=cpu(31);
/* 002ab360: lw v0,-0x2910(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6f0)));
/* 002ab364: beq v0,zero,0x002ab378 */ {int taken=(cpu(2)==cpu(0));/* delay 002ab368 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));if(taken){goto L_002ab378;}}
/* 002ab36c: sw v0,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002ab370: b 0x002ab37c */ /* delay 002ab374 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_002ab37c;
L_002ab378:;
/* 002ab378: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
L_002ab37c:;
/* 002ab37c: jr ra */ {uint64_t target=cpu(31);/* delay 002ab380 */ sw(ea(28,(int32_t)UINT32_C(0xffffd6f0)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionTexture_002AAFF0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002aaff0u);
uint64_t incoming=cpu(31);
/* 002aaff0: jr ra */ {uint64_t target=cpu(31);/* delay 002aaff4 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000018))));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionTexture_002AB688(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002ab688u);
uint64_t incoming=cpu(31);
/* 002ab688: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ab68c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab690: move s0,a0 */ set(16,cpu(4));
/* 002ab694: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab698: lbu a0,0x1a(s0) */ set(4,byte(ea(16,(int32_t)UINT32_C(0x0000001a))));
/* 002ab69c: lbu a1,0x19(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x00000019))));
/* 002ab6a0: jal 0x002ab658 */ set(31,0x002ab6a8u);/* delay 002ab6a4 */ set(6,byte(ea(16,(int32_t)UINT32_C(0x00000018))));set(2,ps2BattleActionTexture_002AB658(cpu(4),cpu(5),cpu(6)));
/* 002ab6a8: sw v0,0x34(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(2));
/* 002ab6ac: jal 0x002a8170 */ set(31,0x002ab6b4u);/* delay 002ab6b0 */ set(4,cpu(2));set(2,ps2BattleActionTexture_002A8170(cpu(4)));
/* 002ab6b4: sw v0,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));
/* 002ab6b8: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ab6bc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab6c0: jr ra */ {uint64_t target=cpu(31);/* delay 002ab6c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionTexture_002AB658(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x002ab658u);
uint64_t incoming=cpu(31);
/* 002ab658: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002ab65c: li a3,0x4 */ set(7,sx(UINT32_C(0x00000004)));
/* 002ab660: li v1,0x13 */ set(3,sx(UINT32_C(0x00000013)));
/* 002ab664: beq a0,v1,0x002ab678 */ {int taken=(cpu(4)==cpu(3));/* delay 002ab668 */ if(cpu(5)!=0){set(7,cpu(2));}if(taken){goto L_002ab678;}}
/* 002ab66c: li v0,0x1b */ set(2,sx(UINT32_C(0x0000001b)));
/* 002ab670: bne a0,v0,0x002ab67c */ {int taken=(cpu(4)!=cpu(2));/* delay 002ab674 */ set(3,sx(UINT32_C(0x00000010)));if(taken){goto L_002ab67c;}}
L_002ab678:;
/* 002ab678: li v1,0x100 */ set(3,sx(UINT32_C(0x00000100)));
L_002ab67c:;
/* 002ab67c: mult v0,v1,a3 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(3)*(int64_t)(int32_t)(uint32_t)cpu(7));EE_MAGATUHI_MULT_STATE(product);set(2,sx((uint32_t)product));}
/* 002ab680: jr ra */ {uint64_t target=cpu(31);/* delay 002ab684 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(2)*(int64_t)(int32_t)(uint32_t)cpu(6));/* MULT1 uses the secondary bank; direct lowword result is consumed here. */set(2,sx((uint32_t)product));}checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_002A8170(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002a8170u);
uint64_t incoming=cpu(31);
/* 002a8170: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a8174: slti v0,a0,0x401 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000401));
/* 002a8178: bne v0,zero,0x002a8198 */ {int taken=(cpu(2)!=cpu(0));/* delay 002a817c */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002a8198;}}
/* 002a8180: jal 0x002a9038 */ set(31,0x002a8188u);/* delay 002a8184 */ set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 002a8188: jal 0x002a9688 */ set(31,0x002a8190u);/* delay 002a818c */ set(4,cpu(2));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 002a8190: b 0x002a81a4 */ /* delay 002a8194 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002a81a4;
L_002a8198:;
/* 002a8198: jal 0x002a8af8 */ set(31,0x002a81a0u);/* delay 002a819c */ set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002a81a0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002a81a4:;
/* 002a81a4: jr ra */ {uint64_t target=cpu(31);/* delay 002a81a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_002AB6C8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002ab6c8u);
uint64_t incoming=cpu(31);
/* 002ab6c8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ab6cc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab6d0: lw a2,0x34(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000034)));
/* 002ab6d4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab6d8: lw a0,0x30(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002ab6dc: j 0x002d43a4 */ /* delay 002ab6e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));return cpu(2);
}
uint64_t ps2BattleActionTexture_002AB2B0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectAxisNoteEntry(0x002ab2b0u);
uint64_t incoming=cpu(31);
/* 002ab2b0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ab2b4: move t2,a0 */ set(10,cpu(4));
/* 002ab2b8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab2bc: li v0,0x13 */ set(2,sx(UINT32_C(0x00000013)));
/* 002ab2c0: move a0,a1 */ set(4,cpu(5));
/* 002ab2c4: move t0,a2 */ set(8,cpu(6));
/* 002ab2c8: lbu v1,0x1a(t2) */ set(3,byte(ea(10,(int32_t)UINT32_C(0x0000001a))));
/* 002ab2cc: beq v1,v0,0x002ab2e0 */ {int taken=(cpu(3)==cpu(2));/* delay 002ab2d0 */ set(9,cpu(7));if(taken){goto L_002ab2e0;}}
/* 002ab2d4: li v0,0x1b */ set(2,sx(UINT32_C(0x0000001b)));
/* 002ab2d8: bnel v1,v0,0x002ab2f0 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 002ab2dc */ set(5,sx(UINT32_C(0x00000008)));goto L_002ab2f0;}}
L_002ab2e0:;
/* 002ab2e0: li a1,0x10 */ set(5,sx(UINT32_C(0x00000010)));
/* 002ab2e4: b 0x002ab2f4 */ /* delay 002ab2e8 */ set(6,sx(UINT32_C(0x00000010)));goto L_002ab2f4;
L_002ab2f0:;
/* 002ab2f0: li a2,0x2 */ set(6,sx(UINT32_C(0x00000002)));
L_002ab2f4:;
/* 002ab2f4: lbu a3,0x19(t2) */ set(7,byte(ea(10,(int32_t)UINT32_C(0x00000019))));
/* 002ab2f8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab2fc: j 0x002ab1a8 */ /* delay 002ab300 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);set(2,ps2BattleActionTexture_002AB1A8(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9)));return cpu(2);
}
uint64_t ps2BattleActionTexture_002AB1A8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);nocturneEffectAxisNoteEntry(0x002ab1a8u);
uint64_t incoming=cpu(31);
/* 002ab1a8: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002ab1ac: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ab1b0: move s4,a3 */ set(20,cpu(7));
/* 002ab1b4: sd s6,0x50(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002ab1b8: move s6,a0 */ set(22,cpu(4));
/* 002ab1bc: move a0,s4 */ set(4,cpu(20));
/* 002ab1c0: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ab1c4: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ab1c8: move s0,t1 */ set(16,cpu(9));
/* 002ab1cc: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ab1d0: move s2,t0 */ set(18,cpu(8));
/* 002ab1d4: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ab1d8: move s3,a1 */ set(19,cpu(5));
/* 002ab1dc: sd s5,0x48(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002ab1e0: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002ab1e4: jal 0x002aa980 */ set(31,0x002ab1ecu);/* delay 002ab1e8 */ set(21,cpu(6));set(2,ps2BattleActionTexture_002AA980(cpu(4),cpu(5),cpu(6)));
/* 002ab1ec: bne s0,zero,0x002ab258 */ {int taken=(cpu(16)!=cpu(0));/* delay 002ab1f0 */ set(17,sx((uint32_t)cpu(2)<<4));if(taken){goto L_002ab258;}}
/* 002ab1f4: slti v0,s1,0x401 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000401));
/* 002ab1f8: bne v0,zero,0x002ab228 */ {int taken=(cpu(2)!=cpu(0));/* delay 002ab1fc */ if(taken){goto L_002ab228;}}
/* 002ab200: jal 0x002a9038 */ set(31,0x002ab208u);/* delay 002ab204 */ set(4,cpu(17));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 002ab208: move a0,v0 */ set(4,cpu(2));
/* 002ab20c: jal 0x002a9688 */ set(31,0x002ab214u);/* delay 002ab210 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 002ab214: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002ab218: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002ab21c: b 0x002ab23c */ /* delay 002ab220 */ sb(ea(29,(int32_t)UINT32_C(0x00000008)),(uint8_t)cpu(3));goto L_002ab23c;
L_002ab228:;
/* 002ab228: jal 0x002a8af8 */ set(31,0x002ab230u);/* delay 002ab22c */ set(4,cpu(17));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002ab230: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
/* 002ab234: sb v1,0x8(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000008)),(uint8_t)cpu(3));
/* 002ab238: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002ab23c:;
/* 002ab23c: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ab240: move a1,s2 */ set(5,cpu(18));
/* 002ab244: jal 0x002d43a4 */ set(31,0x002ab24cu);/* delay 002ab248 */ set(6,cpu(17));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 002ab24c: b 0x002ab264 */ /* delay 002ab250 */ set(4,cpu(29));goto L_002ab264;
L_002ab258:;
/* 002ab258: sw s2,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));
/* 002ab25c: sb zero,0x8(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000008)),(uint8_t)cpu(0));
/* 002ab260: move a0,sp */ set(4,cpu(29));
L_002ab264:;
/* 002ab264: sb s4,0x9(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000009)),(uint8_t)cpu(20));
/* 002ab268: sw s6,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(22));
/* 002ab26c: sh s3,0x14(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(19));
/* 002ab270: sh s5,0x16(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(21));
/* 002ab274: sh s3,0xa(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(19));
/* 002ab278: sh zero,0x10(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000010)),(uint16_t)cpu(0));
/* 002ab27c: jal 0x002aa9e0 */ set(31,0x002ab284u);/* delay 002ab280 */ sh(ea(29,(int32_t)UINT32_C(0x00000012)),(uint16_t)cpu(0));set(2,ps2BattleActionTexture_002AA9E0(cpu(4)));
/* 002ab284: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002ab288: addu v0,s2,s1 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(17)));
/* 002ab28c: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002ab290: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002ab294: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002ab298: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002ab29c: ld s5,0x48(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002ab2a0: ld s6,0x50(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002ab2a4: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002ab2a8: jr ra */ {uint64_t target=cpu(31);/* delay 002ab2ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_002AA980(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x002aa980u);
uint64_t incoming=cpu(31);
/* 002aa980: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 002aa984: sltiu v0,a0,0x3a */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000003a));
/* 002aa988: beq v0,zero,0x002aa9cc */ {int taken=(cpu(2)==cpu(0));/* delay 002aa98c */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_002aa9cc;}}
/* 002aa990: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 002aa994: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002aa998: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002aa99c: lw v1,-0x6ce0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffff9320)));
/* 002aa9a0: jr v1 */ {uint64_t target=cpu(3);/* delay 002aa9a4 */ switch((uint32_t)target){case 0x002aa9a8u:goto L_002aa9a8;case 0x002aa9b0u:goto L_002aa9b0;case 0x002aa9b8u:goto L_002aa9b8;case 0x002aa9c0u:goto L_002aa9c0;case 0x002aa9c8u:goto L_002aa9c8;default:fprintf(stderr,"Unexpected native texture jump target %08x\n",(uint32_t)target);abort();}}
L_002aa9a8:;
/* 002aa9a8: b 0x002aa9cc */ /* delay 002aa9ac */ set(2,sx(UINT32_C(0x00000018)));goto L_002aa9cc;
L_002aa9b0:;
/* 002aa9b0: b 0x002aa9cc */ /* delay 002aa9b4 */ set(2,sx(UINT32_C(0x00000010)));goto L_002aa9cc;
L_002aa9b8:;
/* 002aa9b8: b 0x002aa9cc */ /* delay 002aa9bc */ set(2,sx(UINT32_C(0x00000008)));goto L_002aa9cc;
L_002aa9c0:;
/* 002aa9c0: b 0x002aa9cc */ /* delay 002aa9c4 */ set(2,sx(UINT32_C(0x00000004)));goto L_002aa9cc;
L_002aa9c8:;
/* 002aa9c8: li v0,0x20 */ set(2,sx(UINT32_C(0x00000020)));
L_002aa9cc:;
/* 002aa9cc: mult v0,v0,a1 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(2)*(int64_t)(int32_t)(uint32_t)cpu(5));EE_MAGATUHI_MULT_STATE(product);set(2,sx((uint32_t)product));}
/* 002aa9d0: mult1 v0,v0,a2 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(2)*(int64_t)(int32_t)(uint32_t)cpu(6));nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)product),sx((uint32_t)(product>>32)));set(2,sx((uint32_t)product));}
/* 002aa9d4: jr ra */ {uint64_t target=cpu(31);/* delay 002aa9d8 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>7)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionTexture_002AA9E0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002aa9e0u);
uint64_t incoming=cpu(31);
/* 002aa9e0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002aa9e4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002aa9e8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa9ec: move s1,a0 */ set(17,cpu(4));
/* 002aa9f0: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002aa9f4: lui v0,0x58 */ set(2,sx(UINT32_C(0x00580000)));
/* 002aa9f8: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002aa9fc: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002aaa00: addiu s7,v0,0x1018 */ set(23,sx((uint32_t)cpu(2)+UINT32_C(0x00001018)));
/* 002aaa04: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aaa08: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aaa0c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aaa10: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002aaa14: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002aaa18: lbu s2,0x9(s1) */ set(18,byte(ea(17,(int32_t)UINT32_C(0x00000009))));
/* 002aaa1c: lhu s4,0x14(s1) */ set(20,half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 002aaa20: lhu s3,0x16(s1) */ set(19,half(ea(17,(int32_t)UINT32_C(0x00000016))));
/* 002aaa24: move a0,s2 */ set(4,cpu(18));
/* 002aaa28: lhu s0,0xa(s1) */ set(16,half(ea(17,(int32_t)UINT32_C(0x0000000a))));
/* 002aaa2c: move a1,s4 */ set(5,cpu(20));
/* 002aaa30: move a2,s3 */ set(6,cpu(19));
/* 002aaa34: dsll32 s3,s3,0x0 */ set(19,cpu(19)<<32);
/* 002aaa38: srl s0,s0,0x6 */ set(16,sx((uint32_t)cpu(16)>>6));
/* 002aaa3c: dsll32 s2,s2,0x18 */ set(18,cpu(18)<<56);
/* 002aaa40: jal 0x002aa980 */ set(31,0x002aaa48u);/* delay 002aaa44 */ if(cpu(16)==0){set(16,cpu(3));}set(2,ps2BattleActionTexture_002AA980(cpu(4),cpu(5),cpu(6)));
/* 002aaa48: move s5,v0 */ set(21,cpu(2));
/* 002aaa4c: li v0,0x7ff0 */ set(2,sx(UINT32_C(0x00007ff0)));
/* 002aaa50: addiu v1,s5,0x7fef */ set(3,sx((uint32_t)cpu(21)+UINT32_C(0x00007fef)));
/* 002aaa54: beql v0,zero,0x002aaa5c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002aaa58 */ nocturneCompilerArithmeticTrap(7u);goto L_002aaa5c;}}
L_002aaa5c:;
/* 002aaa5c: div v1,v0 */ textureDivide((uint32_t)cpu(3),(uint32_t)cpu(2));
/* 002aaa60: dsll32 s0,s0,0x10 */ set(16,cpu(16)<<48);
/* 002aaa64: or s2,s2,s0 */ set(18,cpu(18)|cpu(16));
/* 002aaa68: or s4,s4,s3 */ set(20,cpu(20)|cpu(19));
/* 002aaa6c: mflo v1 */ set(3,nocturneEffectHostLo());
/* 002aaa70: sll a0,v1,0x1 */ set(4,sx((uint32_t)cpu(3)<<1));
/* 002aaa74: addu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 002aaa78: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 002aaa7c: jal 0x002a8af8 */ set(31,0x002aaa84u);/* delay 002aaa80 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000080)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002aaa84: lw v1,0x4(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002aaa88: move s6,v0 */ set(22,cpu(2));
/* 002aaa8c: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002aaa90: sw v1,0x8(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002aaa94: addiu s3,s6,0x10 */ set(19,sx((uint32_t)cpu(22)+UINT32_C(0x00000010)));
/* 002aaa98: sw v0,0x4(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002aaa9c: lui a2,0x1000 */ set(6,sx(UINT32_C(0x10000000)));
/* 002aaaa0: ori a2,a2,0x5 */ set(6,cpu(6)|UINT32_C(0x00000005));
/* 002aaaa4: sw zero,0x0(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002aaaa8: li t4,0x52 */ set(12,sx(UINT32_C(0x00000052)));
/* 002aaaac: li t5,0x53 */ set(13,sx(UINT32_C(0x00000053)));
/* 002aaab0: lui a3,0x5000 */ set(7,sx(UINT32_C(0x50000000)));
/* 002aaab4: ori a3,a3,0x5 */ set(7,cpu(7)|UINT32_C(0x00000005));
/* 002aaab8: dsll32 a3,a3,0x0 */ set(7,cpu(7)<<32);
/* 002aaabc: lbu v0,0x8(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000008))));
/* 002aaac0: lui t0,0x1000 */ set(8,sx(UINT32_C(0x10000000)));
/* 002aaac4: dsll32 t0,t0,0x0 */ set(8,cpu(8)<<32);
/* 002aaac8: ori t0,t0,0x4 */ set(8,cpu(8)|UINT32_C(0x00000004));
/* 002aaacc: li t1,0xe */ set(9,sx(UINT32_C(0x0000000e)));
/* 002aaad0: li t2,0x50 */ set(10,sx(UINT32_C(0x00000050)));
/* 002aaad4: sb v0,0xc(s6) */ sb(ea(22,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(2));
/* 002aaad8: li t3,0x51 */ set(11,sx(UINT32_C(0x00000051)));
/* 002aaadc: sd a2,0x0(s3) */ save(6,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 002aaae0: addiu s0,s6,0x70 */ set(16,sx((uint32_t)cpu(22)+UINT32_C(0x00000070)));
/* 002aaae4: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002aaae8: lui t7,0x1000 */ set(15,sx(UINT32_C(0x10000000)));
/* 002aaaec: ori t7,t7,0x1 */ set(15,cpu(15)|UINT32_C(0x00000001));
/* 002aaaf0: lhu a0,0x12(s1) */ set(4,half(ea(17,(int32_t)UINT32_C(0x00000012))));
/* 002aaaf4: lui t6,0x5000 */ set(14,sx(UINT32_C(0x50000000)));
/* 002aaaf8: ori t6,t6,0x1 */ set(14,cpu(14)|UINT32_C(0x00000001));
/* 002aaafc: dsll32 t6,t6,0x0 */ set(14,cpu(14)<<32);
/* 002aab00: lhu v1,0x10(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000010))));
/* 002aab04: srl v0,v0,0x6 */ set(2,sx((uint32_t)cpu(2)>>6));
/* 002aab08: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002aab0c: dsll32 a0,a0,0x10 */ set(4,cpu(4)<<48);
/* 002aab10: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002aab14: or s2,s2,v0 */ set(18,cpu(18)|cpu(2));
/* 002aab18: or a0,a0,v1 */ set(4,cpu(4)|cpu(3));
/* 002aab1c: lw a1,0x0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002aab20: lui v0,0xfff */ set(2,sx(UINT32_C(0x0fff0000)));
/* 002aab24: sd s2,0x20(s3) */ save(18,ea(19,(int32_t)UINT32_C(0x00000020)));
/* 002aab28: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002aab2c: sd a0,0x30(s3) */ save(4,ea(19,(int32_t)UINT32_C(0x00000030)));
/* 002aab30: sd s4,0x40(s3) */ save(20,ea(19,(int32_t)UINT32_C(0x00000040)));
/* 002aab34: sd t4,0x48(s3) */ save(12,ea(19,(int32_t)UINT32_C(0x00000048)));
/* 002aab38: sd t5,0x58(s3) */ save(13,ea(19,(int32_t)UINT32_C(0x00000058)));
/* 002aab3c: sd zero,0x50(s3) */ save(0,ea(19,(int32_t)UINT32_C(0x00000050)));
/* 002aab40: sd a3,0x8(s3) */ save(7,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 002aab44: and a3,a1,v0 */ set(7,cpu(5)&cpu(2));
/* 002aab48: sd t0,0x10(s3) */ save(8,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 002aab4c: move t0,zero */ set(8,cpu(0));
/* 002aab50: sd t1,0x18(s3) */ save(9,ea(19,(int32_t)UINT32_C(0x00000018)));
/* 002aab54: lui t1,0x5100 */ set(9,sx(UINT32_C(0x51000000)));
/* 002aab58: sd t2,0x28(s3) */ save(10,ea(19,(int32_t)UINT32_C(0x00000028)));
/* 002aab5c: lui t2,0x3000 */ set(10,sx(UINT32_C(0x30000000)));
/* 002aab60: sd t3,0x38(s3) */ save(11,ea(19,(int32_t)UINT32_C(0x00000038)));
/* 002aab64: ori t3,zero,0x8000 */ set(11,cpu(0)|UINT32_C(0x00008000));
/* 002aab68: dsll32 t3,t3,0xc */ set(11,cpu(11)<<44);
/* 002aab6c: nop  */ 
L_002aab70:;
/* 002aab70: slti v0,s5,0x7ff1 */ set(2,(int64_t)cpu(21)<(int64_t)(int32_t)UINT32_C(0x00007ff1));
/* 002aab74: beq v0,zero,0x002aab84 */ {int taken=(cpu(2)==cpu(0));/* delay 002aab78 */ set(6,sx(UINT32_C(0x00007ff0)));if(taken){goto L_002aab84;}}
/* 002aab7c: move a2,s5 */ set(6,cpu(21));
/* 002aab80: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
L_002aab84:;
/* 002aab84: dsll v1,t0,0xf */ set(3,cpu(8)<<15);
/* 002aab88: andi a0,a2,0xffff */ set(4,cpu(6)&UINT32_C(0x0000ffff));
/* 002aab8c: dsll32 v0,a3,0x0 */ set(2,cpu(7)<<32);
/* 002aab90: or v1,a2,v1 */ set(3,cpu(6)|cpu(3));
/* 002aab94: or a0,a0,t2 */ set(4,cpu(4)|cpu(10));
/* 002aab98: or a1,a2,t1 */ set(5,cpu(6)|cpu(9));
/* 002aab9c: or a0,a0,v0 */ set(4,cpu(4)|cpu(2));
/* 002aaba0: sll v0,a2,0x4 */ set(2,sx((uint32_t)cpu(6)<<4));
/* 002aaba4: or v1,v1,t3 */ set(3,cpu(3)|cpu(11));
/* 002aaba8: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002aabac: sd v1,0x10(s0) */ save(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002aabb0: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 002aabb4: sd a0,0x20(s0) */ save(4,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002aabb8: subu s5,s5,a2 */ set(21,sx((uint32_t)cpu(21)-(uint32_t)cpu(6)));
/* 002aabbc: sd a1,0x28(s0) */ save(5,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002aabc0: sd t7,0x0(s0) */ save(15,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002aabc4: sd t6,0x8(s0) */ save(14,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002aabc8: beq t0,zero,0x002aab70 */ {int taken=(cpu(8)==cpu(0));/* delay 002aabcc */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));if(taken){goto L_002aab70;}}
/* 002aabd0: jal 0x002dbee0 */ set(31,0x002aabd8u);/* delay 002aabd4 */ lw(4,ea(23,(int32_t)UINT32_C(0x00000000)));waitSemaphore();
/* 002aabd8: lw v0,0x8(s7) */ lw(2,ea(23,(int32_t)UINT32_C(0x00000008)));
/* 002aabdc: beql v0,zero,0x002aabe8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002aabe0 */ sw(ea(23,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(22));goto L_002aabe8;}}
/* 002aabe4: sw s6,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(22));
L_002aabe8:;
/* 002aabe8: lui v0,0xfff */ set(2,sx(UINT32_C(0x0fff0000)));
/* 002aabec: lw a0,0x10(s7) */ lw(4,ea(23,(int32_t)UINT32_C(0x00000010)));
/* 002aabf0: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002aabf4: sw s6,0x8(s7) */ sw(ea(23,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(22));
/* 002aabf8: beq a0,zero,0x002aac18 */ {int taken=(cpu(4)==cpu(0));/* delay 002aabfc */ set(19,cpu(19)&cpu(2));if(taken){goto L_002aac18;}}
/* 002aac00: dsll32 v0,s3,0x0 */ set(2,cpu(19)<<32);
/* 002aac04: lui v1,0x2000 */ set(3,sx(UINT32_C(0x20000000)));
/* 002aac08: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002aac0c: sd zero,0x8(a0) */ save(0,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002aac10: b 0x002aac1c */ /* delay 002aac14 */ save(2,ea(4,(int32_t)UINT32_C(0x00000000)));goto L_002aac1c;
L_002aac18:;
/* 002aac18: sw s3,0xc(s7) */ sw(ea(23,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(19));
L_002aac1c:;
/* 002aac1c: sw s0,0x10(s7) */ sw(ea(23,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(16));
/* 002aac20: lw a0,0x0(s7) */ lw(4,ea(23,(int32_t)UINT32_C(0x00000000)));
/* 002aac24: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aac28: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aac2c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aac30: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aac34: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002aac38: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002aac3c: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002aac40: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002aac44: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002aac48: j 0x002dbec0 */ /* delay 002aac4c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(cpu(31),incoming);signalSemaphore();return cpu(2);
}
uint64_t ps2BattleActionTexture_002AB070(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002ab070u);
uint64_t incoming=cpu(31);
/* 002ab070: li v0,0xa */ set(2,sx(UINT32_C(0x0000000a)));
/* 002ab074: beq a0,v0,0x002ab0b8 */ {int taken=(cpu(4)==cpu(2));/* delay 002ab078 */ set(3,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x0000000b));if(taken){goto L_002ab0b8;}}
/* 002ab07c: beq v1,zero,0x002ab098 */ {int taken=(cpu(3)==cpu(0));/* delay 002ab080 */ set(2,sx(UINT32_C(0x00000013)));if(taken){goto L_002ab098;}}
/* 002ab084: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002ab088: beql a0,v0,0x002ab0bc */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 002ab08c */ set(3,sx(UINT32_C(0x00000010)));goto L_002ab0bc;}}
/* 002ab090: b 0x002ab0bc */ /* delay 002ab094 */ set(3,sx(UINT32_C(0x00000020)));goto L_002ab0bc;
L_002ab098:;
/* 002ab098: beq a0,v0,0x002ab0bc */ {int taken=(cpu(4)==cpu(2));/* delay 002ab09c */ set(3,sx(UINT32_C(0x00000008)));if(taken){goto L_002ab0bc;}}
/* 002ab0a0: li v0,0x14 */ set(2,sx(UINT32_C(0x00000014)));
/* 002ab0a4: bnel a0,v0,0x002ab0bc */ {int taken=(cpu(4)!=cpu(2));if(taken){/* delay 002ab0a8 */ set(3,sx(UINT32_C(0x00000020)));goto L_002ab0bc;}}
/* 002ab0ac: b 0x002ab0bc */ /* delay 002ab0b0 */ set(3,sx(UINT32_C(0x00000004)));goto L_002ab0bc;
L_002ab0b8:;
/* 002ab0b8: li v1,0x10 */ set(3,sx(UINT32_C(0x00000010)));
L_002ab0bc:;
/* 002ab0bc: jr ra */ {uint64_t target=cpu(31);/* delay 002ab0c0 */ set(2,cpu(3));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionTexture_002ABB18(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002abb18u);
uint64_t incoming=cpu(31);
/* 002abb18: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002abb1c: move a1,zero */ set(5,cpu(0));
/* 002abb20: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002abb24: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002abb28: jal 0x002aba78 */ set(31,0x002abb30u);/* delay 002abb2c */ set(16,cpu(4));set(2,ps2EffectTextureRegisterCacheCreate_002ABA78(cpu(4),cpu(5)));
/* 002abb30: sw v0,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));
/* 002abb34: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002abb38: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002abb3c: jr ra */ {uint64_t target=cpu(31);/* delay 002abb40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
