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
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
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


#include "battle_action_command_frames.h"
#include "effect_model_map_frames.h"
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}

uint64_t ps2BattleActionCommand_002B0AC0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectAxisNoteEntry(0x002b0ac0u);
uint64_t incoming=cpu(31);
/* 002b0ac0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b0ac4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b0ac8: move s1,a1 */ set(17,cpu(5));
/* 002b0acc: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b0ad0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b0ad4: lw s0,0x4(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002b0ad8: lw a0,0x10(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002b0adc: srl a1,s0,0x10 */ set(5,sx((uint32_t)cpu(16)>>16));
/* 002b0ae0: jal 0x002b09d0 */ set(31,0x002b0ae8u);/* delay 002b0ae4 */ set(16,cpu(16)&UINT32_C(0x0000ffff));set(2,ps2EffectModelWriteIndexedAssetPacket_002B09D0(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 002b0ae8: lui a0,0xfff */ set(4,sx(UINT32_C(0x0fff0000)));
/* 002b0aec: move a1,v0 */ set(5,cpu(2));
/* 002b0af0: li v0,0x30 */ set(2,sx(UINT32_C(0x00000030)));
/* 002b0af4: sb v0,0x3(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(2));
/* 002b0af8: addiu v0,a1,0x10 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002b0afc: ori a0,a0,0xffff */ set(4,cpu(4)|UINT32_C(0x0000ffff));
/* 002b0b00: sh s0,0x0(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(16));
/* 002b0b04: lw v1,0x8(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002b0b08: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b0b0c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b0b10: and v1,v1,a0 */ set(3,cpu(3)&cpu(4));
/* 002b0b14: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b0b18: sw zero,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002b0b1c: sw zero,0xc(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002b0b20: sw v1,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002b0b24: jr ra */ {uint64_t target=cpu(31);/* delay 002b0b28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCommand_002B0B30(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectAxisNoteEntry(0x002b0b30u);
uint64_t incoming=cpu(31);
/* 002b0b30: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002b0b34: lui v0,0xfff */ set(2,sx(UINT32_C(0x0fff0000)));
/* 002b0b38: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b0b3c: move s0,a3 */ set(16,cpu(7));
/* 002b0b40: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b0b44: sll s0,s0,0x7 */ set(16,sx((uint32_t)cpu(16)<<7));
/* 002b0b48: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b0b4c: move s2,zero */ set(18,cpu(0));
/* 002b0b50: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002b0b54: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
/* 002b0b58: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002b0b5c: move s4,a0 */ set(20,cpu(4));
/* 002b0b60: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002b0b64: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002b0b68: lui s7,0x6c07 */ set(23,sx(UINT32_C(0x6c070000)));
/* 002b0b6c: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002b0b70: move s8,a1 */ set(30,cpu(5));
/* 002b0b74: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002b0b78: ori s7,s7,0xc000 */ set(23,cpu(23)|UINT32_C(0x0000c000));
/* 002b0b7c: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002b0b80: lw s6,0x4(s8) */ lw(22,ea(30,(int32_t)UINT32_C(0x00000004)));
/* 002b0b84: lw a0,0x10(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000010)));
/* 002b0b88: srl a1,s6,0x10 */ set(5,sx((uint32_t)cpu(22)>>16));
/* 002b0b8c: andi s6,s6,0xffff */ set(22,cpu(22)&UINT32_C(0x0000ffff));
/* 002b0b90: jal 0x002b09d0 */ set(31,0x002b0b98u);/* delay 002b0b94 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));set(2,ps2EffectModelWriteIndexedAssetPacket_002B09D0(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 002b0b98: lw v1,0x0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b0b9c: move s1,v0 */ set(17,cpu(2));
/* 002b0ba0: lw s5,0xc(s8) */ lw(21,ea(30,(int32_t)UINT32_C(0x0000000c)));
/* 002b0ba4: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002b0ba8: sw s0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002b0bac: sw v1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002b0bb0: addiu s0,s8,0x10 */ set(16,sx((uint32_t)cpu(30)+UINT32_C(0x00000010)));
/* 002b0bb4: nop  */ 
L_002b0bb8:;
/* 002b0bb8: lhu a1,0x0(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002b0bbc: addiu s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000002)));
/* 002b0bc0: lw a0,0x10(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000010)));
/* 002b0bc4: jal 0x002b08e8 */ set(31,0x002b0bccu);/* delay 002b0bc8 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));set(2,ps2EffectModelSearchNode_002B08E8(cpu(4),cpu(5)));
/* 002b0bcc: li a0,0x7 */ set(4,sx(UINT32_C(0x00000007)));
/* 002b0bd0: li v1,0x30 */ set(3,sx(UINT32_C(0x00000030)));
/* 002b0bd4: sh a0,0x0(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));
/* 002b0bd8: sb v1,0x3(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(3));
/* 002b0bdc: jal 0x002b0438 */ set(31,0x002b0be4u);/* delay 002b0be0 */ set(4,cpu(2));set(2,ps2EffectModelEnsureWorkspace_002B0438(cpu(4)));
/* 002b0be4: sw zero,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002b0be8: or v1,s3,s7 */ set(3,cpu(19)|cpu(23));
/* 002b0bec: addiu s3,s3,0x7 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000007)));
/* 002b0bf0: lw a0,0x4(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002b0bf4: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002b0bf8: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b0bfc: sw v1,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 002b0c00: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 002b0c04: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002b0c08: bne s2,s5,0x002b0bb8 */ {int taken=(cpu(18)!=cpu(21));/* delay 002b0c0c */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));if(taken)goto L_002b0bb8;}
/* 002b0c10: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002b0c14: li v0,0x10 */ set(2,sx(UINT32_C(0x00000010)));
/* 002b0c18: lui a1,0x6001 */ set(5,sx(UINT32_C(0x60010000)));
/* 002b0c1c: lui a2,0x400 */ set(6,sx(UINT32_C(0x04000000)));
/* 002b0c20: sb v0,0x3(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(2));
/* 002b0c24: lui v0,0x1400 */ set(2,sx(UINT32_C(0x14000000)));
/* 002b0c28: sw zero,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002b0c2c: addiu v1,s1,0x10 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));
/* 002b0c30: sw zero,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002b0c34: ori a1,a1,0xc000 */ set(5,cpu(5)|UINT32_C(0x0000c000));
/* 002b0c38: sh a0,0x0(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));
/* 002b0c3c: addiu s1,s1,0x20 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000020)));
/* 002b0c40: ori a2,a2,0xe */ set(6,cpu(6)|UINT32_C(0x0000000e));
/* 002b0c44: li a3,0x30 */ set(7,sx(UINT32_C(0x00000030)));
/* 002b0c48: sw v0,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002b0c4c: addiu v0,s1,0x10 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));
/* 002b0c50: sw s5,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(21));
/* 002b0c54: lui a0,0xfff */ set(4,sx(UINT32_C(0x0fff0000)));
/* 002b0c58: sw a1,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
/* 002b0c5c: ori a0,a0,0xffff */ set(4,cpu(4)|UINT32_C(0x0000ffff));
/* 002b0c60: sw a2,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 002b0c64: sb a3,0x3(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(7));
/* 002b0c68: sh s6,0x0(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(22));
/* 002b0c6c: lw v1,0x8(s8) */ lw(3,ea(30,(int32_t)UINT32_C(0x00000008)));
/* 002b0c70: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b0c74: and v1,v1,a0 */ set(3,cpu(3)&cpu(4));
/* 002b0c78: sw zero,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002b0c7c: sw zero,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002b0c80: sw v1,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002b0c84: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b0c88: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b0c8c: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002b0c90: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002b0c94: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002b0c98: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002b0c9c: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002b0ca0: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002b0ca4: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002b0ca8: jr ra */ {uint64_t target=cpu(31);/* delay 002b0cac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return cpu(2);}
}
