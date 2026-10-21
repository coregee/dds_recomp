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
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_billboard_copy_frames.h"
#include "battle_action_creation_frames.h"
#include "battle_action_texture_creation_frames.h"
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}

static void body_0015c350(void);
static void body_0015cea0(void);
static void body_0015c350(void){
nocturneEffectAxisNoteEntry(0x0015c350u);
uint64_t incoming=cpu(31);
/* 0015c350: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015c354: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015c358: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015c35c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015c360: lw s1,0x30(a0) */ lw(17,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 0015c364: lw v1,0xc(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0015c368: lw v0,0x14(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 0015c36c: sll a0,v1,0x2 */ set(4,sx((uint32_t)cpu(3)<<2));
/* 0015c370: addu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 0015c374: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0015c378: sw v0,0x14(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 0015c37c: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 0015c380: jal 0x002a8af8 */ set(31,0x0015c388u);/* delay 0015c384 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000006c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015c388: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0015c38c: move s0,v0 */ set(16,cpu(2));
/* 0015c390: move a1,zero */ set(5,cpu(0));
/* 0015c394: addiu v0,s0,0x6c */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x0000006c)));
/* 0015c398: sw s1,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(17));
/* 0015c39c: sw v0,0x60(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(2));
/* 0015c3a0: move a0,s0 */ set(4,cpu(16));
/* 0015c3a4: sh v1,0x50(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000050)),(uint16_t)cpu(3));
/* 0015c3a8: sw zero,0x48(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 0015c3ac: jal 0x0015c940 */ set(31,0x0015c3b4u);/* delay 0015c3b0 */ sw(ea(16,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));ps2BattleActionTexture_0015C940(cpu(4),cpu(5));
/* 0015c3b4: move v0,s0 */ set(2,cpu(16));
/* 0015c3b8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015c3bc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015c3c0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015c3c4: jr ra */ {uint64_t target=cpu(31);/* delay 0015c3c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionBillboardCopy_0015C350(uint64_t a0){set(4,a0);body_0015c350();return cpu(2);}
static void body_0015cea0(void){
nocturneEffectAxisNoteEntry(0x0015cea0u);
uint64_t incoming=cpu(31);
/* 0015cea0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015cea4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0015cea8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015ceac: move s1,a0 */ set(17,cpu(4));
/* 0015ceb0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015ceb4: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015ceb8: lhu v0,0x2c(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000002c))));
/* 0015cebc: bne v0,v1,0x0015cef0 */ {int taken=(cpu(2)!=cpu(3));/* delay 0015cec0 */ if(taken){goto L_0015cef0;}}
/* 0015cec4: jal 0x0015c350 */ set(31,0x0015ceccu);/* delay 0015cec8 */ body_0015c350();
/* 0015cecc: move s0,v0 */ set(16,cpu(2));
/* 0015ced0: jal 0x0015c1e8 */ set(31,0x0015ced8u);/* delay 0015ced4 */ set(4,cpu(16));ps2BattleActionCreation_0015C1E8(cpu(4));
/* 0015ced8: lhu v0,0x2c(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000002c))));
/* 0015cedc: lw v1,0x28(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 0015cee0: sh v0,0x2c(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(2));
/* 0015cee4: b 0x0015cf28 */ /* delay 0015cee8 */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));goto L_0015cf28;
L_0015cef0:;
/* 0015cef0: jal 0x0015c230 */ set(31,0x0015cef8u);/* delay 0015cef4 */ set(4,cpu(0));set(2,ps2BattleActionCreation_0015C230(cpu(4)));
/* 0015cef8: move s0,v0 */ set(16,cpu(2));
/* 0015cefc: jal 0x0015c1e8 */ set(31,0x0015cf04u);/* delay 0015cf00 */ set(4,cpu(16));ps2BattleActionCreation_0015C1E8(cpu(4));
/* 0015cf04: lhu a0,0x2c(s1) */ set(4,half(ea(17,(int32_t)UINT32_C(0x0000002c))));
/* 0015cf08: lw v1,0x30(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000030)));
/* 0015cf0c: lw a1,0x28(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 0015cf10: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0015cf14: sh a0,0x2c(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(4));
/* 0015cf18: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0015cf1c: sw a1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(5));
/* 0015cf20: sw v0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0015cf24: sw v1,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(3));
L_0015cf28:;
/* 0015cf28: move v0,s0 */ set(2,cpu(16));
/* 0015cf2c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015cf30: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015cf34: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015cf38: jr ra */ {uint64_t target=cpu(31);/* delay 0015cf3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionBillboardCopy_0015CEA0(uint64_t a0){set(4,a0);body_0015cea0();return cpu(2);}
