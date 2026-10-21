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


static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}

static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}





static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}





/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */







static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}

#include "battle_action_polygon_history_frames.h"
#include "magatuhi_helpers.h"
static void multiply(unsigned rd,unsigned rs,unsigned rt){
 uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(rs)*(int64_t)(int32_t)(uint32_t)cpu(rt));
 EE_MAGATUHI_MULT_STATE(product);set(rd,sx((uint32_t)product));
}

uint64_t ps2BattleActionPolygonHistory_00164420(uint64_t a0,uint64_t a1,uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
nocturneEffectAxisNoteEntry(0x00164420u);
uint64_t incoming=cpu(31);
/* 00164420: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00164424: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00164428: andi s1,a1,0xffff */ set(17,cpu(5)&UINT32_C(0x0000ffff));
/* 0016442c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00164430: sll s5,s1,0x4 */ set(21,sx((uint32_t)cpu(17)<<4));
/* 00164434: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00164438: addiu s0,s5,0x10 */ set(16,sx((uint32_t)cpu(21)+UINT32_C(0x00000010)));
/* 0016443c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00164440: move s4,a0 */ set(20,cpu(4));
/* 00164444: mult s0,s0,s4 */ multiply(16,16,20);
/* 00164448: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0016444c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00164450: move s3,a2 */ set(19,cpu(6));
/* 00164454: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00164458: jal 0x002a9038 */ set(31,0x00164460u);/* delay 0016445c */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 00164460: move s2,v0 */ set(18,cpu(2));
/* 00164464: jal 0x002a9688 */ set(31,0x0016446cu);/* delay 00164468 */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 0016446c: mult v1,s1,s4 */ multiply(3,17,20);
/* 00164470: move a0,v0 */ set(4,cpu(2));
/* 00164474: addu a1,v0,s0 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 00164478: sh s1,0x2(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(17));
/* 0016447c: move a2,zero */ set(6,cpu(0));
/* 00164480: sw s3,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));
/* 00164484: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 00164488: sw s2,0xc(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(18));
/* 0016448c: addu v0,a0,v1 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 00164490: sh s4,0x0(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(20));
/* 00164494: beq s4,zero,0x001644c8 */ {int taken=(cpu(20)==cpu(0));/* delay 00164498 */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_001644c8;}}
/* 0016449c: move s0,s5 */ set(16,cpu(21));
/* 001644a0: move v1,v0 */ set(3,cpu(2));
/* 001644a4: nop  */ 
L_001644a8:;
/* 001644a8: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001644ac: sw a0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001644b0: sltu v0,a2,s4 */ set(2,cpu(6)<cpu(20));
/* 001644b4: sh zero,0x4(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(0));
/* 001644b8: sw zero,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001644bc: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 001644c0: bne v0,zero,0x001644a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001644c4 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(16)));if(taken){goto L_001644a8;}}
L_001644c8:;
/* 001644c8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001644cc: move v0,a1 */ set(2,cpu(5));
/* 001644d0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001644d4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001644d8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001644dc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001644e0: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001644e4: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001644e8: jr ra */ {uint64_t target=cpu(31);/* delay 001644ec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return cpu(2);}
}
