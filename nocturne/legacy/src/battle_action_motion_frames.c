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
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void sq(unsigned r,uint32_t a){uint32_t q[4];nocturneEffectHostCpuRead(r,q);memcpy(at(a&~15u),q,16);}
/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */
static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_motion_frames.h"
#include "battle_action_model_frames.h"
#include "effect_model_map_frames.h"
#include "script_compare.h"
#include <stdio.h>
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void lq(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneEffectHostCpuWrite(r,q);}

static void body_002b3b20(void);
static void body_002b3b50(void);
static void body_002b3b78(void);
static void body_002b3b88(void);
static void body_002b3c60(void);
static void body_002b3d28(void);
static void body_002b4100(void);
static void body_002b4118(void);
static void body_002b43a8(void);
static void body_002b43d8(void);
static void body_002b4428(void);
static void body_002b45b8(void);
static void body_002b47b8(void);
static void body_002b4948(void);
static void body_002b4af8(void);
static void body_002b4c08(void);
static void body_002b4c28(void);
static void body_002b4c48(void);
static void body_002b4c68(void);
static void body_002b4c88(void);
static void body_002b4cb8(void);
static void body_002b4d10(void);
static void body_002b4e60(void);
static void body_002b4e70(void);
static void body_002b4fc0(void);
static void body_002b4fd0(void);
static void body_002b5120(void);
static void body_002b5130(void);
static void body_002b5280(void);
static void body_002b5290(void);
static void body_002b5388(void);
static void body_002b5398(void);
static void body_002b54c0(void);
static void body_002b5510(void);
static void body_002b5638(void);
static void body_002b5688(void);
static void body_002b57d8(void);
static void body_002b57e8(void);
static void body_002b58b8(void);
static void body_002b58c0(void);
static void body_002b5990(void);
static void body_002b5998(void);
static void body_002b59c8(void);
static void body_002b5a20(void);
static void body_002b5ca0(void);
static void factory_002b3b20(uint64_t target){switch((uint32_t)target){
case 0x002b43a8u:body_002b43a8();return;
case 0x002b4c88u:body_002b4c88();return;
case 0x002b5998u:body_002b5998();return;
default:fprintf(stderr,"Unsupported original motion callback %08x\n",(uint32_t)target);abort();}}
static void factory_002b43a8(uint64_t target){switch((uint32_t)target){
case 0x002b4428u:body_002b4428();return;
case 0x002b45b8u:body_002b45b8();return;
case 0x002b47b8u:body_002b47b8();return;
case 0x002b4948u:body_002b4948();return;
case 0x002b4af8u:body_002b4af8();return;
default:fprintf(stderr,"Unsupported original motion callback %08x\n",(uint32_t)target);abort();}}
static void factory_002b4c88(uint64_t target){switch((uint32_t)target){
case 0x002b4d10u:body_002b4d10();return;
case 0x002b4e70u:body_002b4e70();return;
case 0x002b4fd0u:body_002b4fd0();return;
case 0x002b5130u:body_002b5130();return;
case 0x002b5290u:body_002b5290();return;
case 0x002b5398u:body_002b5398();return;
case 0x002b5510u:body_002b5510();return;
case 0x002b5688u:body_002b5688();return;
case 0x002b57e8u:body_002b57e8();return;
case 0x002b58c0u:body_002b58c0();return;
default:fprintf(stderr,"Unsupported original motion callback %08x\n",(uint32_t)target);abort();}}
static void factory_002b5998(uint64_t target){switch((uint32_t)target){
case 0x002b5a20u:body_002b5a20();return;
default:fprintf(stderr,"Unsupported original motion callback %08x\n",(uint32_t)target);abort();}}
static void capture_callback(uint64_t target){switch((uint32_t)target){
case 0x002b4c08u:body_002b4c08();return;
case 0x002b4c28u:body_002b4c28();return;
case 0x002b4c48u:body_002b4c48();return;
case 0x002b4c68u:body_002b4c68();return;
case 0x002b4e60u:body_002b4e60();return;
case 0x002b4fc0u:body_002b4fc0();return;
case 0x002b5120u:body_002b5120();return;
case 0x002b5280u:body_002b5280();return;
case 0x002b5388u:body_002b5388();return;
case 0x002b54c0u:body_002b54c0();return;
case 0x002b5638u:body_002b5638();return;
case 0x002b57d8u:body_002b57d8();return;
case 0x002b58b8u:body_002b58b8();return;
case 0x002b5990u:body_002b5990();return;
case 0x002b5ca0u:body_002b5ca0();return;
default:fprintf(stderr,"Unsupported original motion callback %08x\n",(uint32_t)target);abort();}}
static void bind_callback(uint64_t target){switch((uint32_t)target){
case 0x002b4118u:body_002b4118();return;
default:fprintf(stderr,"Unsupported original motion callback %08x\n",(uint32_t)target);abort();}}
static void destructor_callback(uint64_t target){switch((uint32_t)target){
case 0x002b4100u:body_002b4100();return;
default:fprintf(stderr,"Unsupported original motion callback %08x\n",(uint32_t)target);abort();}}
static void body_002b3b20(void){
nocturneEffectAxisNoteEntry(0x002b3b20u);
uint64_t incoming=cpu(31);
/* 002b3b20: srl v1,a1,0x10 */ set(3,sx((uint32_t)cpu(5)>>16));
/* 002b3b24: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b3b28: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 002b3b2c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3b30: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002b3b34: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002b3b38: lw v0,-0x6bb8(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffff9448)));
/* 002b3b3c: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002b3b44u);/* delay 002b3b40 */ factory_002b3b20(target);}
/* 002b3b44: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3b48: jr ra */ {uint64_t target=cpu(31);/* delay 002b3b4c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B3B20(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b3b20();return cpu(2);}
static void body_002b3b50(void){
nocturneEffectAxisNoteEntry(0x002b3b50u);
uint64_t incoming=cpu(31);
/* 002b3b50: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b3b54: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002b3b58: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3b5c: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b3b60: jalr v1 */ {uint64_t target=cpu(3);set(31,0x002b3b68u);/* delay 002b3b64 */ destructor_callback(target);}
/* 002b3b68: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3b6c: jr ra */ {uint64_t target=cpu(31);/* delay 002b3b70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B3B50(uint64_t a0){set(4,a0);body_002b3b50();}
static void body_002b3b78(void){
nocturneEffectAxisNoteEntry(0x002b3b78u);
uint64_t incoming=cpu(31);
/* 002b3b78: sw a1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 002b3b7c: jr ra */ {uint64_t target=cpu(31);/* delay 002b3b80 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B3B78(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b3b78();}
static void body_002b3b88(void){
nocturneEffectAxisNoteEntry(0x002b3b88u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002b3b88: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002b3b8c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3b90: move s0,a0 */ set(16,cpu(4));
/* 002b3b94: li a0,0x34 */ set(4,sx(UINT32_C(0x00000034)));
/* 002b3b98: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b3b9c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b3ba0: move s1,a1 */ set(17,cpu(5));
/* 002b3ba4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b3ba8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b3bac: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002b3bb0: jal 0x002a8ba8 */ set(31,0x002b3bb8u);/* delay 002b3bb4 */ set(19,cpu(0));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 002b3bb8: move s2,v0 */ set(18,cpu(2));
/* 002b3bbc: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 002b3bc0: lhu s4,0x2(s1) */ set(20,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002b3bc4: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 002b3bc8: sw v0,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002b3bcc: li a2,0x8 */ set(6,sx(UINT32_C(0x00000008)));
/* 002b3bd0: sw s0,0x4(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002b3bd4: move a0,s4 */ set(4,cpu(20));
/* 002b3bd8: sw s2,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 002b3bdc: jal 0x002bfe58 */ set(31,0x002b3be4u);/* delay 002b3be0 */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));set(2,ps2EffectArrayCreate_002BFE58(cpu(4),cpu(5),cpu(6)));
/* 002b3be4: lw v1,0x8(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 002b3be8: sh s4,0x4(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(20));
/* 002b3bec: sw v0,0x10(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002b3bf0: beq s4,zero,0x002b3c2c */ {int taken=(cpu(20)==cpu(0));/* delay 002b3bf4 */ set(16,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));if(taken){goto L_002b3c2c;}}
L_002b3bf8:;
/* 002b3bf8: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002b3bfc: move a0,s2 */ set(4,cpu(18));
/* 002b3c00: lw a2,0x4(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002b3c04: jal 0x002b3b20 */ set(31,0x002b3c0cu);/* delay 002b3c08 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));body_002b3b20();
/* 002b3c0c: lw a1,0x10(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002b3c10: sll v1,s3,0x2 */ set(3,sx((uint32_t)cpu(19)<<2));
/* 002b3c14: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002b3c18: lw a0,0xc(a1) */ lw(4,ea(5,(int32_t)UINT32_C(0x0000000c)));
/* 002b3c1c: slt a2,s3,s4 */ set(6,(int64_t)cpu(19)<(int64_t)cpu(20));
/* 002b3c20: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002b3c24: bne a2,zero,0x002b3bf8 */ {int taken=(cpu(6)!=cpu(0));/* delay 002b3c28 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_002b3bf8;}}
L_002b3c2c:;
/* 002b3c2c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 002b3c30: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002b3c34: move v0,s2 */ set(2,cpu(18));
/* 002b3c38: sb zero,0x30(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000030)),(uint8_t)cpu(0));
/* 002b3c3c: swc1 f0,0x20(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000020)),f[0]);
/* 002b3c40: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3c44: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b3c48: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b3c4c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b3c50: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b3c54: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002b3c58: jr ra */ {uint64_t target=cpu(31);/* delay 002b3c5c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B3B88(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_002b3b88();return cpu(2);}
static void body_002b3c60(void){
nocturneEffectAxisNoteEntry(0x002b3c60u);
uint64_t incoming=cpu(31);
/* 002b3c60: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b3c64: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b3c68: move s2,a0 */ set(18,cpu(4));
/* 002b3c6c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3c70: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b3c74: beq s2,zero,0x002b3d10 */ {int taken=(cpu(18)==cpu(0));/* delay 002b3c78 */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002b3d10;}}
/* 002b3c7c: lw v0,0x4(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 002b3c80: beq v0,zero,0x002b3cb4 */ {int taken=(cpu(2)==cpu(0));/* delay 002b3c84 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000014)));if(taken){goto L_002b3cb4;}}
L_002b3c88:;
/* 002b3c88: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002b3c8c: beql v0,zero,0x002b3cb8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002b3c90 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000010)));goto L_002b3cb8;}}
/* 002b3c94: nop  */ 
/* 002b3c98: nop  */ 
/* 002b3c9c: nop  */ 
/* 002b3ca0: nop  */ 
/* 002b3ca4: bnel v0,s2,0x002b3c88 */ {int taken=(cpu(2)!=cpu(18));if(taken){/* delay 002b3ca8 */ set(3,cpu(2));goto L_002b3c88;}}
/* 002b3cac: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 002b3cb0: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002b3cb4:;
/* 002b3cb4: lw a0,0x10(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000010)));
L_002b3cb8:;
/* 002b3cb8: lh v1,0x4(a0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 002b3cbc: blez v1,0x002b3ce8 */ {int taken=((int64_t)cpu(3)<=0);/* delay 002b3cc0 */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));if(taken){goto L_002b3ce8;}}
/* 002b3cc4: move s1,v0 */ set(17,cpu(2));
/* 002b3cc8: move s0,v1 */ set(16,cpu(3));
/* 002b3ccc: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
L_002b3cd0:;
/* 002b3cd0: addiu s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
/* 002b3cd4: jal 0x002b3b50 */ set(31,0x002b3cdcu);/* delay 002b3cd8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));body_002b3b50();
/* 002b3cdc: bnel s0,zero,0x002b3cd0 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 002b3ce0 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));goto L_002b3cd0;}}
/* 002b3ce4: lw a0,0x10(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000010)));
L_002b3ce8:;
/* 002b3ce8: jal 0x002bfee8 */ set(31,0x002b3cf0u);/* delay 002b3cec */ ps2BattleActionModel_002BFEE8(cpu(4));
/* 002b3cf0: move a0,s2 */ set(4,cpu(18));
/* 002b3cf4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3cf8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b3cfc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b3d00: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b3d04: j 0x002a8bd8 */ /* delay 002b3d08 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);ps2BattleActionModel_002A8BD8(cpu(4));return;
L_002b3d10:;
/* 002b3d10: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3d14: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b3d18: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b3d1c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b3d20: jr ra */ {uint64_t target=cpu(31);/* delay 002b3d24 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B3C60(uint64_t a0){set(4,a0);body_002b3c60();}
static void body_002b3d28(void){
nocturneEffectAxisNoteEntry(0x002b3d28u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 002b3d28: clear f0 */ f[0]=0;
/* 002b3d2c: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002b3d30: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3d34: move s0,a0 */ set(16,cpu(4));
/* 002b3d38: c.lt.S f0,f13 */ condition=EE_FPU_COMPARE_S(f[0],f[13],1);
/* 002b3d3c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b3d40: move s1,a1 */ set(17,cpu(5));
/* 002b3d44: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b3d48: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b3d4c: move s3,a2 */ set(19,cpu(6));
/* 002b3d50: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b3d54: bc1f 0x002b3db8 */ {int taken=(!condition);/* delay 002b3d58 */ sh(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(17));if(taken){goto L_002b3db8;}}
/* 002b3d5c: neg.S f0,f12 */ f[0]=f[12]^UINT32_C(0x80000000);
/* 002b3d60: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002b3d64: swc1 f13,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),f[13]);
/* 002b3d68: move s2,zero */ set(18,cpu(0));
/* 002b3d6c: lh v0,0x4(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000004))));
/* 002b3d70: blez v0,0x002b3dc0 */ {int taken=((int64_t)cpu(2)<=0);/* delay 002b3d74 */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),f[0]);if(taken){goto L_002b3dc0;}}
/* 002b3d78: lw v1,0xc(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 002b3d7c: nop  */ 
L_002b3d80:;
/* 002b3d80: sll v0,s2,0x2 */ set(2,sx((uint32_t)cpu(18)<<2));
/* 002b3d84: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002b3d88: lw a0,0x0(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b3d8c: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002b3d90: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 002b3d94: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002b3d9cu);/* delay 002b3d98 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));capture_callback(target);}
/* 002b3d9c: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002b3da0: lh v0,0x4(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000004))));
/* 002b3da4: slt v0,s2,v0 */ set(2,(int64_t)cpu(18)<(int64_t)cpu(2));
/* 002b3da8: bnel v0,zero,0x002b3d80 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002b3dac */ lw(3,ea(3,(int32_t)UINT32_C(0x0000000c)));goto L_002b3d80;}}
/* 002b3db0: b 0x002b3dc4 */ /* delay 002b3db4 */ set(3,sx(UINT32_C(0x00000001)));goto L_002b3dc4;
L_002b3db8:;
/* 002b3db8: sw zero,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002b3dbc: sw zero,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
L_002b3dc0:;
/* 002b3dc0: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
L_002b3dc4:;
/* 002b3dc4: sb s3,0x32(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000032)),(uint8_t)cpu(19));
/* 002b3dc8: sb v1,0x30(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000030)),(uint8_t)cpu(3));
/* 002b3dcc: sll v0,s1,0x2 */ set(2,sx((uint32_t)cpu(17)<<2));
/* 002b3dd0: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002b3dd4: lwc1 f0,0x18(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000018)));
/* 002b3dd8: lw a0,0x4(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002b3ddc: swc1 f0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),f[0]);
/* 002b3de0: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002b3de4: lw v0,0x0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b3de8: bnel v0,zero,0x002b3e00 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002b3dec */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));goto L_002b3e00;}}
/* 002b3df0: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 002b3df4: sh zero,0x2e(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(0));
/* 002b3df8: b 0x002b3e54 */ /* delay 002b3dfc */ sb(ea(16,(int32_t)UINT32_C(0x00000030)),(uint8_t)cpu(2));goto L_002b3e54;
L_002b3e00:;
/* 002b3e00: addiu s1,v0,0x4 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 002b3e04: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002b3e08: sh v1,0x2e(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(3));
/* 002b3e0c: lh v0,0x4(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 002b3e10: blez v0,0x002b3e54 */ {int taken=((int64_t)cpu(2)<=0);/* delay 002b3e14 */ set(18,cpu(0));if(taken){goto L_002b3e54;}}
L_002b3e18:;
/* 002b3e18: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b3e1c: sll v0,s2,0x2 */ set(2,sx((uint32_t)cpu(18)<<2));
/* 002b3e20: move a1,s1 */ set(5,cpu(17));
/* 002b3e24: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002b3e28: lw a0,0x0(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002b3e2c: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002b3e30: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 002b3e34: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002b3e3cu);/* delay 002b3e38 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));bind_callback(target);}
/* 002b3e3c: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002b3e40: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002b3e44: lh v0,0x4(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 002b3e48: slt v0,s2,v0 */ set(2,(int64_t)cpu(18)<(int64_t)cpu(2));
/* 002b3e4c: bne v0,zero,0x002b3e18 */ {int taken=(cpu(2)!=cpu(0));/* delay 002b3e50 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(3)));if(taken){goto L_002b3e18;}}
L_002b3e54:;
/* 002b3e54: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b3e58: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b3e5c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b3e60: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b3e64: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002b3e68: jr ra */ {uint64_t target=cpu(31);/* delay 002b3e6c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B3D28(uint64_t a0, uint64_t a1, uint64_t a2, float f12, float f13){set(4,a0);set(5,a1);set(6,a2);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectHostFpr()[13]=bits(f13);body_002b3d28();}
static void body_002b4100(void){
nocturneEffectAxisNoteEntry(0x002b4100u);
uint64_t incoming=cpu(31);
/* 002b4100: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b4104: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4108: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b410c: j 0x002a8bd8 */ /* delay 002b4110 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionModel_002A8BD8(cpu(4));return;
}
void ps2BattleActionMotion_002B4100(uint64_t a0){set(4,a0);body_002b4100();}
static void body_002b4118(void){
nocturneEffectAxisNoteEntry(0x002b4118u);
uint64_t incoming=cpu(31);
/* 002b4118: jr ra */ {uint64_t target=cpu(31);/* delay 002b411c */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B4118(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_002b4118();}
static void body_002b43a8(void){
nocturneEffectAxisNoteEntry(0x002b43a8u);
uint64_t incoming=cpu(31);
/* 002b43a8: andi v1,a1,0xffff */ set(3,cpu(5)&UINT32_C(0x0000ffff));
/* 002b43ac: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b43b0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 002b43b4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b43b8: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002b43bc: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002b43c0: lw v0,-0x6ba8(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffff9458)));
/* 002b43c4: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002b43ccu);/* delay 002b43c8 */ factory_002b43a8(target);}
/* 002b43cc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b43d0: jr ra */ {uint64_t target=cpu(31);/* delay 002b43d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B43A8(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b43a8();return cpu(2);}
static void body_002b43d8(void){
nocturneEffectAxisNoteEntry(0x002b43d8u);
uint64_t incoming=cpu(31);
/* 002b43d8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b43dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b43e0: move s0,a1 */ set(16,cpu(5));
/* 002b43e4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b43e8: move s1,a3 */ set(17,cpu(7));
/* 002b43ec: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b43f0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b43f4: jal 0x002b3b78 */ set(31,0x002b43fcu);/* delay 002b43f8 */ set(18,cpu(4));body_002b3b78();
/* 002b43fc: lw a0,0x4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002b4400: jal 0x002b08e8 */ set(31,0x002b4408u);/* delay 002b4404 */ set(5,cpu(17));set(2,ps2EffectModelSearchNode_002B08E8(cpu(4),cpu(5)));
/* 002b4408: sw v0,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002b440c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4410: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4414: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4418: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b441c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4420 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B43D8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){set(4,a0);set(5,a1);set(6,a2);set(7,a3);body_002b43d8();}
static void body_002b4428(void){
nocturneEffectAxisNoteEntry(0x002b4428u);
uint64_t incoming=cpu(31);
/* 002b4428: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b442c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4430: move s1,a0 */ set(17,cpu(4));
/* 002b4434: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 002b4438: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b443c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4440: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4444: jal 0x002a8af8 */ set(31,0x002b444cu);/* delay 002b4448 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b444c: move s0,v0 */ set(16,cpu(2));
/* 002b4450: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b4454: move a1,s1 */ set(5,cpu(17));
/* 002b4458: move a3,s2 */ set(7,cpu(18));
/* 002b445c: move a0,s0 */ set(4,cpu(16));
/* 002b4460: jal 0x002b43d8 */ set(31,0x002b4468u);/* delay 002b4464 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9470)));body_002b43d8();
/* 002b4468: move v0,s0 */ set(2,cpu(16));
/* 002b446c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4470: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4474: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4478: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b447c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4480 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B4428(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b4428();return cpu(2);}
static void body_002b45b8(void){
nocturneEffectAxisNoteEntry(0x002b45b8u);
uint64_t incoming=cpu(31);
/* 002b45b8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b45bc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b45c0: move s1,a0 */ set(17,cpu(4));
/* 002b45c4: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 002b45c8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b45cc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b45d0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b45d4: jal 0x002a8af8 */ set(31,0x002b45dcu);/* delay 002b45d8 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b45dc: move s0,v0 */ set(16,cpu(2));
/* 002b45e0: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b45e4: move a1,s1 */ set(5,cpu(17));
/* 002b45e8: move a3,s2 */ set(7,cpu(18));
/* 002b45ec: move a0,s0 */ set(4,cpu(16));
/* 002b45f0: jal 0x002b43d8 */ set(31,0x002b45f8u);/* delay 002b45f4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9488)));body_002b43d8();
/* 002b45f8: move v0,s0 */ set(2,cpu(16));
/* 002b45fc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4600: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4604: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4608: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b460c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4610 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B45B8(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b45b8();return cpu(2);}
static void body_002b47b8(void){
nocturneEffectAxisNoteEntry(0x002b47b8u);
uint64_t incoming=cpu(31);
/* 002b47b8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b47bc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b47c0: move s1,a0 */ set(17,cpu(4));
/* 002b47c4: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 002b47c8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b47cc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b47d0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b47d4: jal 0x002a8af8 */ set(31,0x002b47dcu);/* delay 002b47d8 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b47dc: move s0,v0 */ set(16,cpu(2));
/* 002b47e0: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b47e4: move a1,s1 */ set(5,cpu(17));
/* 002b47e8: move a3,s2 */ set(7,cpu(18));
/* 002b47ec: move a0,s0 */ set(4,cpu(16));
/* 002b47f0: jal 0x002b43d8 */ set(31,0x002b47f8u);/* delay 002b47f4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff94a0)));body_002b43d8();
/* 002b47f8: move v0,s0 */ set(2,cpu(16));
/* 002b47fc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4800: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4804: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4808: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b480c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4810 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B47B8(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b47b8();return cpu(2);}
static void body_002b4948(void){
nocturneEffectAxisNoteEntry(0x002b4948u);
uint64_t incoming=cpu(31);
/* 002b4948: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b494c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4950: move s1,a0 */ set(17,cpu(4));
/* 002b4954: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 002b4958: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b495c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4960: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4964: jal 0x002a8af8 */ set(31,0x002b496cu);/* delay 002b4968 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b496c: move s0,v0 */ set(16,cpu(2));
/* 002b4970: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b4974: move a1,s1 */ set(5,cpu(17));
/* 002b4978: move a3,s2 */ set(7,cpu(18));
/* 002b497c: move a0,s0 */ set(4,cpu(16));
/* 002b4980: jal 0x002b43d8 */ set(31,0x002b4988u);/* delay 002b4984 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff94b8)));body_002b43d8();
/* 002b4988: move v0,s0 */ set(2,cpu(16));
/* 002b498c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4990: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4994: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4998: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b499c: jr ra */ {uint64_t target=cpu(31);/* delay 002b49a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B4948(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b4948();return cpu(2);}
static void body_002b4af8(void){
nocturneEffectAxisNoteEntry(0x002b4af8u);
uint64_t incoming=cpu(31);
/* 002b4af8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b4afc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4b00: move s1,a0 */ set(17,cpu(4));
/* 002b4b04: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 002b4b08: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4b0c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4b10: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4b14: jal 0x002a8af8 */ set(31,0x002b4b1cu);/* delay 002b4b18 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b4b1c: move s0,v0 */ set(16,cpu(2));
/* 002b4b20: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b4b24: move a1,s1 */ set(5,cpu(17));
/* 002b4b28: move a3,s2 */ set(7,cpu(18));
/* 002b4b2c: move a0,s0 */ set(4,cpu(16));
/* 002b4b30: jal 0x002b43d8 */ set(31,0x002b4b38u);/* delay 002b4b34 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff94d0)));body_002b43d8();
/* 002b4b38: move v0,s0 */ set(2,cpu(16));
/* 002b4b3c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4b40: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4b44: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4b48: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4b4c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4b50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B4AF8(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b4af8();return cpu(2);}
static void body_002b4c08(void){
nocturneEffectAxisNoteEntry(0x002b4c08u);
uint64_t incoming=cpu(31);
/* 002b4c08: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b4c0c: lhu v0,0x14(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000014))));
/* 002b4c10: srl v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)>>4));
/* 002b4c14: xori v0,v0,0x1 */ set(2,cpu(2)^UINT32_C(0x00000001));
/* 002b4c18: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002b4c1c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4c20 */ sb(ea(4,(int32_t)UINT32_C(0x00000010)),(uint8_t)cpu(2));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B4C08(uint64_t a0){set(4,a0);body_002b4c08();}
static void body_002b4c28(void){
nocturneEffectAxisNoteEntry(0x002b4c28u);
uint64_t incoming=cpu(31);
/* 002b4c28: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b4c2c: addiu a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
/* 002b4c30: addiu v1,v1,0x60 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000060)));
/* 002b4c34: lq v0,0x0(v1) */ lq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002b4c38: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002b4c3c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4c40 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B4C28(uint64_t a0){set(4,a0);body_002b4c28();}
static void body_002b4c48(void){
nocturneEffectAxisNoteEntry(0x002b4c48u);
uint64_t incoming=cpu(31);
/* 002b4c48: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b4c4c: addiu a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
/* 002b4c50: addiu v1,v1,0x50 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000050)));
/* 002b4c54: lq v0,0x0(v1) */ lq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002b4c58: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002b4c5c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4c60 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B4C48(uint64_t a0){set(4,a0);body_002b4c48();}
static void body_002b4c68(void){
nocturneEffectAxisNoteEntry(0x002b4c68u);
uint64_t incoming=cpu(31);
/* 002b4c68: lw v1,0xc(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b4c6c: addiu a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
/* 002b4c70: addiu v1,v1,0x70 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000070)));
/* 002b4c74: lq v0,0x0(v1) */ lq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002b4c78: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002b4c7c: jr ra */ {uint64_t target=cpu(31);/* delay 002b4c80 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B4C68(uint64_t a0){set(4,a0);body_002b4c68();}
static void body_002b4c88(void){
nocturneEffectAxisNoteEntry(0x002b4c88u);
uint64_t incoming=cpu(31);
/* 002b4c88: andi v1,a1,0xffff */ set(3,cpu(5)&UINT32_C(0x0000ffff));
/* 002b4c8c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b4c90: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 002b4c94: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4c98: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002b4c9c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002b4ca0: lw v0,-0x6b18(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffff94e8)));
/* 002b4ca4: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002b4cacu);/* delay 002b4ca8 */ factory_002b4c88(target);}
/* 002b4cac: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4cb0: jr ra */ {uint64_t target=cpu(31);/* delay 002b4cb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B4C88(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b4c88();return cpu(2);}
static void body_002b4cb8(void){
nocturneEffectAxisNoteEntry(0x002b4cb8u);
uint64_t incoming=cpu(31);
/* 002b4cb8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b4cbc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4cc0: move s1,a1 */ set(17,cpu(5));
/* 002b4cc4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4cc8: move s0,a3 */ set(16,cpu(7));
/* 002b4ccc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4cd0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4cd4: jal 0x002b3b78 */ set(31,0x002b4cdcu);/* delay 002b4cd8 */ set(18,cpu(4));body_002b3b78();
/* 002b4cdc: lw a0,0x4(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002b4ce0: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 002b4ce4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4ce8: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b4cec: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4cf0: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002b4cf4: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 002b4cf8: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002b4cfc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4d00: sw v0,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002b4d04: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4d08: jr ra */ {uint64_t target=cpu(31);/* delay 002b4d0c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B4CB8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){set(4,a0);set(5,a1);set(6,a2);set(7,a3);body_002b4cb8();}
static void body_002b4d10(void){
nocturneEffectAxisNoteEntry(0x002b4d10u);
uint64_t incoming=cpu(31);
/* 002b4d10: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b4d14: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4d18: move s1,a0 */ set(17,cpu(4));
/* 002b4d1c: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 002b4d20: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4d24: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4d28: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4d2c: jal 0x002a8af8 */ set(31,0x002b4d34u);/* delay 002b4d30 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b4d34: move s0,v0 */ set(16,cpu(2));
/* 002b4d38: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b4d3c: move a1,s1 */ set(5,cpu(17));
/* 002b4d40: move a3,s2 */ set(7,cpu(18));
/* 002b4d44: move a0,s0 */ set(4,cpu(16));
/* 002b4d48: jal 0x002b4cb8 */ set(31,0x002b4d50u);/* delay 002b4d4c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9510)));body_002b4cb8();
/* 002b4d50: move v0,s0 */ set(2,cpu(16));
/* 002b4d54: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4d58: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4d5c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4d60: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4d64: jr ra */ {uint64_t target=cpu(31);/* delay 002b4d68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B4D10(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b4d10();return cpu(2);}
static void body_002b4e60(void){
nocturneEffectAxisNoteEntry(0x002b4e60u);
uint64_t incoming=cpu(31);
/* 002b4e60: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b4e64: lw v1,0x14(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000014)));
/* 002b4e68: jr ra */ {uint64_t target=cpu(31);/* delay 002b4e6c */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B4E60(uint64_t a0){set(4,a0);body_002b4e60();}
static void body_002b4e70(void){
nocturneEffectAxisNoteEntry(0x002b4e70u);
uint64_t incoming=cpu(31);
/* 002b4e70: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b4e74: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4e78: move s1,a0 */ set(17,cpu(4));
/* 002b4e7c: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 002b4e80: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4e84: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4e88: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4e8c: jal 0x002a8af8 */ set(31,0x002b4e94u);/* delay 002b4e90 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b4e94: move s0,v0 */ set(16,cpu(2));
/* 002b4e98: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b4e9c: move a1,s1 */ set(5,cpu(17));
/* 002b4ea0: move a3,s2 */ set(7,cpu(18));
/* 002b4ea4: move a0,s0 */ set(4,cpu(16));
/* 002b4ea8: jal 0x002b4cb8 */ set(31,0x002b4eb0u);/* delay 002b4eac */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9528)));body_002b4cb8();
/* 002b4eb0: move v0,s0 */ set(2,cpu(16));
/* 002b4eb4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4eb8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4ebc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4ec0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4ec4: jr ra */ {uint64_t target=cpu(31);/* delay 002b4ec8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B4E70(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b4e70();return cpu(2);}
static void body_002b4fc0(void){
nocturneEffectAxisNoteEntry(0x002b4fc0u);
uint64_t incoming=cpu(31);
/* 002b4fc0: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b4fc4: lw v1,0x10(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 002b4fc8: jr ra */ {uint64_t target=cpu(31);/* delay 002b4fcc */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B4FC0(uint64_t a0){set(4,a0);body_002b4fc0();}
static void body_002b4fd0(void){
nocturneEffectAxisNoteEntry(0x002b4fd0u);
uint64_t incoming=cpu(31);
/* 002b4fd0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b4fd4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b4fd8: move s1,a0 */ set(17,cpu(4));
/* 002b4fdc: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 002b4fe0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b4fe4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b4fe8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b4fec: jal 0x002a8af8 */ set(31,0x002b4ff4u);/* delay 002b4ff0 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b4ff4: move s0,v0 */ set(16,cpu(2));
/* 002b4ff8: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b4ffc: move a1,s1 */ set(5,cpu(17));
/* 002b5000: move a3,s2 */ set(7,cpu(18));
/* 002b5004: move a0,s0 */ set(4,cpu(16));
/* 002b5008: jal 0x002b4cb8 */ set(31,0x002b5010u);/* delay 002b500c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9540)));body_002b4cb8();
/* 002b5010: move v0,s0 */ set(2,cpu(16));
/* 002b5014: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5018: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b501c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5020: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b5024: jr ra */ {uint64_t target=cpu(31);/* delay 002b5028 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B4FD0(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b4fd0();return cpu(2);}
static void body_002b5120(void){
nocturneEffectAxisNoteEntry(0x002b5120u);
uint64_t incoming=cpu(31);
/* 002b5120: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b5124: lw v1,0x20(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 002b5128: jr ra */ {uint64_t target=cpu(31);/* delay 002b512c */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B5120(uint64_t a0){set(4,a0);body_002b5120();}
static void body_002b5130(void){
nocturneEffectAxisNoteEntry(0x002b5130u);
uint64_t incoming=cpu(31);
/* 002b5130: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b5134: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5138: move s1,a0 */ set(17,cpu(4));
/* 002b513c: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 002b5140: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5144: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5148: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b514c: jal 0x002a8af8 */ set(31,0x002b5154u);/* delay 002b5150 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b5154: move s0,v0 */ set(16,cpu(2));
/* 002b5158: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b515c: move a1,s1 */ set(5,cpu(17));
/* 002b5160: move a3,s2 */ set(7,cpu(18));
/* 002b5164: move a0,s0 */ set(4,cpu(16));
/* 002b5168: jal 0x002b4cb8 */ set(31,0x002b5170u);/* delay 002b516c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9558)));body_002b4cb8();
/* 002b5170: move v0,s0 */ set(2,cpu(16));
/* 002b5174: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5178: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b517c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5180: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b5184: jr ra */ {uint64_t target=cpu(31);/* delay 002b5188 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B5130(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b5130();return cpu(2);}
static void body_002b5280(void){
nocturneEffectAxisNoteEntry(0x002b5280u);
uint64_t incoming=cpu(31);
/* 002b5280: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b5284: lw v1,0x28(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000028)));
/* 002b5288: jr ra */ {uint64_t target=cpu(31);/* delay 002b528c */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B5280(uint64_t a0){set(4,a0);body_002b5280();}
static void body_002b5290(void){
nocturneEffectAxisNoteEntry(0x002b5290u);
uint64_t incoming=cpu(31);
/* 002b5290: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b5294: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5298: move s1,a0 */ set(17,cpu(4));
/* 002b529c: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 002b52a0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b52a4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b52a8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b52ac: jal 0x002a8af8 */ set(31,0x002b52b4u);/* delay 002b52b0 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b52b4: move s0,v0 */ set(16,cpu(2));
/* 002b52b8: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b52bc: move a1,s1 */ set(5,cpu(17));
/* 002b52c0: move a3,s2 */ set(7,cpu(18));
/* 002b52c4: move a0,s0 */ set(4,cpu(16));
/* 002b52c8: jal 0x002b4cb8 */ set(31,0x002b52d0u);/* delay 002b52cc */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9570)));body_002b4cb8();
/* 002b52d0: move v0,s0 */ set(2,cpu(16));
/* 002b52d4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b52d8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b52dc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b52e0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b52e4: jr ra */ {uint64_t target=cpu(31);/* delay 002b52e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B5290(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b5290();return cpu(2);}
static void body_002b5388(void){
nocturneEffectAxisNoteEntry(0x002b5388u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002b5388: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b538c: lwc1 f0,0x1c(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x0000001c)));
/* 002b5390: jr ra */ {uint64_t target=cpu(31);/* delay 002b5394 */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),f[0]);checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B5388(uint64_t a0){set(4,a0);body_002b5388();}
static void body_002b5398(void){
nocturneEffectAxisNoteEntry(0x002b5398u);
uint64_t incoming=cpu(31);
/* 002b5398: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b539c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b53a0: move s1,a0 */ set(17,cpu(4));
/* 002b53a4: li a0,0x24 */ set(4,sx(UINT32_C(0x00000024)));
/* 002b53a8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b53ac: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b53b0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b53b4: jal 0x002a8af8 */ set(31,0x002b53bcu);/* delay 002b53b8 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b53bc: move s0,v0 */ set(16,cpu(2));
/* 002b53c0: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b53c4: move a1,s1 */ set(5,cpu(17));
/* 002b53c8: move a3,s2 */ set(7,cpu(18));
/* 002b53cc: move a0,s0 */ set(4,cpu(16));
/* 002b53d0: jal 0x002b4cb8 */ set(31,0x002b53d8u);/* delay 002b53d4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9588)));body_002b4cb8();
/* 002b53d8: move v0,s0 */ set(2,cpu(16));
/* 002b53dc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b53e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b53e4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b53e8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b53ec: jr ra */ {uint64_t target=cpu(31);/* delay 002b53f0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B5398(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b5398();return cpu(2);}
static void body_002b54c0(void){
nocturneEffectAxisNoteEntry(0x002b54c0u);
uint64_t incoming=cpu(31);
/* 002b54c0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b54c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b54c8: move s0,a0 */ set(16,cpu(4));
/* 002b54cc: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b54d0: jal 0x002b2f48 */ set(31,0x002b54d8u);/* delay 002b54d4 */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));set(2,ps2EffectMaterialGetFiveWords38_002B2F48(cpu(4)));
/* 002b54d8: ldl v1,0x7(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000007)),1);
/* 002b54dc: ldr v1,0x0(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000000)),0);
/* 002b54e0: ldl a0,0xf(v0) */ loadPartial(4,ea(2,(int32_t)UINT32_C(0x0000000f)),1);
/* 002b54e4: ldr a0,0x8(v0) */ loadPartial(4,ea(2,(int32_t)UINT32_C(0x00000008)),0);
/* 002b54e8: lw a1,0x10(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 002b54ec: sdl v1,0x17(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000017)),3,1);
/* 002b54f0: sdr v1,0x10(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000010)),3,0);
/* 002b54f4: sdl a0,0x1f(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000001f)),4,1);
/* 002b54f8: sdr a0,0x18(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000018)),4,0);
/* 002b54fc: sw a1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(5));
/* 002b5500: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5504: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5508: jr ra */ {uint64_t target=cpu(31);/* delay 002b550c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B54C0(uint64_t a0){set(4,a0);body_002b54c0();}
static void body_002b5510(void){
nocturneEffectAxisNoteEntry(0x002b5510u);
uint64_t incoming=cpu(31);
/* 002b5510: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b5514: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5518: move s1,a0 */ set(17,cpu(4));
/* 002b551c: li a0,0x24 */ set(4,sx(UINT32_C(0x00000024)));
/* 002b5520: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5524: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5528: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b552c: jal 0x002a8af8 */ set(31,0x002b5534u);/* delay 002b5530 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b5534: move s0,v0 */ set(16,cpu(2));
/* 002b5538: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b553c: move a1,s1 */ set(5,cpu(17));
/* 002b5540: move a3,s2 */ set(7,cpu(18));
/* 002b5544: move a0,s0 */ set(4,cpu(16));
/* 002b5548: jal 0x002b4cb8 */ set(31,0x002b5550u);/* delay 002b554c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff95a0)));body_002b4cb8();
/* 002b5550: move v0,s0 */ set(2,cpu(16));
/* 002b5554: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5558: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b555c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5560: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b5564: jr ra */ {uint64_t target=cpu(31);/* delay 002b5568 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B5510(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b5510();return cpu(2);}
static void body_002b5638(void){
nocturneEffectAxisNoteEntry(0x002b5638u);
uint64_t incoming=cpu(31);
/* 002b5638: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b563c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5640: move s0,a0 */ set(16,cpu(4));
/* 002b5644: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5648: jal 0x002b30b0 */ set(31,0x002b5650u);/* delay 002b564c */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));set(2,ps2EffectMaterialGetFiveWords3C_002B30B0(cpu(4)));
/* 002b5650: ldl v1,0x7(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000007)),1);
/* 002b5654: ldr v1,0x0(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000000)),0);
/* 002b5658: ldl a0,0xf(v0) */ loadPartial(4,ea(2,(int32_t)UINT32_C(0x0000000f)),1);
/* 002b565c: ldr a0,0x8(v0) */ loadPartial(4,ea(2,(int32_t)UINT32_C(0x00000008)),0);
/* 002b5660: lw a1,0x10(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 002b5664: sdl v1,0x17(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000017)),3,1);
/* 002b5668: sdr v1,0x10(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000010)),3,0);
/* 002b566c: sdl a0,0x1f(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000001f)),4,1);
/* 002b5670: sdr a0,0x18(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000018)),4,0);
/* 002b5674: sw a1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(5));
/* 002b5678: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b567c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5680: jr ra */ {uint64_t target=cpu(31);/* delay 002b5684 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B5638(uint64_t a0){set(4,a0);body_002b5638();}
static void body_002b5688(void){
nocturneEffectAxisNoteEntry(0x002b5688u);
uint64_t incoming=cpu(31);
/* 002b5688: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b568c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5690: move s1,a0 */ set(17,cpu(4));
/* 002b5694: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 002b5698: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b569c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b56a0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b56a4: jal 0x002a8af8 */ set(31,0x002b56acu);/* delay 002b56a8 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b56ac: move s0,v0 */ set(16,cpu(2));
/* 002b56b0: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b56b4: move a1,s1 */ set(5,cpu(17));
/* 002b56b8: move a3,s2 */ set(7,cpu(18));
/* 002b56bc: move a0,s0 */ set(4,cpu(16));
/* 002b56c0: jal 0x002b4cb8 */ set(31,0x002b56c8u);/* delay 002b56c4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff95b8)));body_002b4cb8();
/* 002b56c8: move v0,s0 */ set(2,cpu(16));
/* 002b56cc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b56d0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b56d4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b56d8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b56dc: jr ra */ {uint64_t target=cpu(31);/* delay 002b56e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B5688(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b5688();return cpu(2);}
static void body_002b57d8(void){
nocturneEffectAxisNoteEntry(0x002b57d8u);
uint64_t incoming=cpu(31);
/* 002b57d8: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b57dc: lw v1,0x18(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 002b57e0: jr ra */ {uint64_t target=cpu(31);/* delay 002b57e4 */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B57D8(uint64_t a0){set(4,a0);body_002b57d8();}
static void body_002b57e8(void){
nocturneEffectAxisNoteEntry(0x002b57e8u);
uint64_t incoming=cpu(31);
/* 002b57e8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b57ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b57f0: move s1,a0 */ set(17,cpu(4));
/* 002b57f4: li a0,0x24 */ set(4,sx(UINT32_C(0x00000024)));
/* 002b57f8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b57fc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5800: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b5804: jal 0x002a8af8 */ set(31,0x002b580cu);/* delay 002b5808 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b580c: move s0,v0 */ set(16,cpu(2));
/* 002b5810: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b5814: move a1,s1 */ set(5,cpu(17));
/* 002b5818: move a3,s2 */ set(7,cpu(18));
/* 002b581c: move a0,s0 */ set(4,cpu(16));
/* 002b5820: jal 0x002b4cb8 */ set(31,0x002b5828u);/* delay 002b5824 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff95d0)));body_002b4cb8();
/* 002b5828: move v0,s0 */ set(2,cpu(16));
/* 002b582c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5830: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5834: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5838: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b583c: jr ra */ {uint64_t target=cpu(31);/* delay 002b5840 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B57E8(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b57e8();return cpu(2);}
static void body_002b58b8(void){
nocturneEffectAxisNoteEntry(0x002b58b8u);
uint64_t incoming=cpu(31);
/* 002b58b8: jr ra */ {uint64_t target=cpu(31);/* delay 002b58bc */ checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B58B8(uint64_t a0){set(4,a0);body_002b58b8();}
static void body_002b58c0(void){
nocturneEffectAxisNoteEntry(0x002b58c0u);
uint64_t incoming=cpu(31);
/* 002b58c0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b58c4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b58c8: move s1,a0 */ set(17,cpu(4));
/* 002b58cc: li a0,0x24 */ set(4,sx(UINT32_C(0x00000024)));
/* 002b58d0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b58d4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b58d8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b58dc: jal 0x002a8af8 */ set(31,0x002b58e4u);/* delay 002b58e0 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b58e4: move s0,v0 */ set(16,cpu(2));
/* 002b58e8: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b58ec: move a1,s1 */ set(5,cpu(17));
/* 002b58f0: move a3,s2 */ set(7,cpu(18));
/* 002b58f4: move a0,s0 */ set(4,cpu(16));
/* 002b58f8: jal 0x002b4cb8 */ set(31,0x002b5900u);/* delay 002b58fc */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff95e8)));body_002b4cb8();
/* 002b5900: move v0,s0 */ set(2,cpu(16));
/* 002b5904: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5908: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b590c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5910: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b5914: jr ra */ {uint64_t target=cpu(31);/* delay 002b5918 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B58C0(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b58c0();return cpu(2);}
static void body_002b5990(void){
nocturneEffectAxisNoteEntry(0x002b5990u);
uint64_t incoming=cpu(31);
/* 002b5990: jr ra */ {uint64_t target=cpu(31);/* delay 002b5994 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B5990(uint64_t a0){set(4,a0);body_002b5990();}
static void body_002b5998(void){
nocturneEffectAxisNoteEntry(0x002b5998u);
uint64_t incoming=cpu(31);
/* 002b5998: andi v1,a1,0xffff */ set(3,cpu(5)&UINT32_C(0x0000ffff));
/* 002b599c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b59a0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 002b59a4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b59a8: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002b59ac: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002b59b0: lw v0,-0x6a00(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffff9600)));
/* 002b59b4: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002b59bcu);/* delay 002b59b8 */ factory_002b5998(target);}
/* 002b59bc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b59c0: jr ra */ {uint64_t target=cpu(31);/* delay 002b59c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B5998(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b5998();return cpu(2);}
static void body_002b59c8(void){
nocturneEffectAxisNoteEntry(0x002b59c8u);
uint64_t incoming=cpu(31);
/* 002b59c8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b59cc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b59d0: move s1,a1 */ set(17,cpu(5));
/* 002b59d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b59d8: move s0,a3 */ set(16,cpu(7));
/* 002b59dc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b59e0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b59e4: jal 0x002b3b78 */ set(31,0x002b59ecu);/* delay 002b59e8 */ set(18,cpu(4));body_002b3b78();
/* 002b59ec: lw a0,0x4(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002b59f0: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 002b59f4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b59f8: lw v1,0x10(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002b59fc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b5a00: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 002b5a04: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002b5a08: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5a0c: sw v0,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002b5a10: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5a14: jr ra */ {uint64_t target=cpu(31);/* delay 002b5a18 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B59C8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){set(4,a0);set(5,a1);set(6,a2);set(7,a3);body_002b59c8();}
static void body_002b5a20(void){
nocturneEffectAxisNoteEntry(0x002b5a20u);
uint64_t incoming=cpu(31);
/* 002b5a20: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b5a24: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5a28: move s1,a0 */ set(17,cpu(4));
/* 002b5a2c: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 002b5a30: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5a34: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5a38: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b5a3c: jal 0x002a8af8 */ set(31,0x002b5a44u);/* delay 002b5a40 */ set(18,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002b5a44: move s0,v0 */ set(16,cpu(2));
/* 002b5a48: lui a2,0x53 */ set(6,sx(UINT32_C(0x00530000)));
/* 002b5a4c: move a1,s1 */ set(5,cpu(17));
/* 002b5a50: move a3,s2 */ set(7,cpu(18));
/* 002b5a54: move a0,s0 */ set(4,cpu(16));
/* 002b5a58: jal 0x002b59c8 */ set(31,0x002b5a60u);/* delay 002b5a5c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffff9608)));body_002b59c8();
/* 002b5a60: move v0,s0 */ set(2,cpu(16));
/* 002b5a64: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b5a68: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b5a6c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b5a70: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b5a74: jr ra */ {uint64_t target=cpu(31);/* delay 002b5a78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionMotion_002B5A20(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002b5a20();return cpu(2);}
static void body_002b5ca0(void){
nocturneEffectAxisNoteEntry(0x002b5ca0u);
uint64_t incoming=cpu(31);
/* 002b5ca0: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 002b5ca4: ldl v1,0x7(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000007)),1);
/* 002b5ca8: ldr v1,0x0(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000000)),0);
/* 002b5cac: ldl a1,0xf(v0) */ loadPartial(5,ea(2,(int32_t)UINT32_C(0x0000000f)),1);
/* 002b5cb0: ldr a1,0x8(v0) */ loadPartial(5,ea(2,(int32_t)UINT32_C(0x00000008)),0);
/* 002b5cb4: sdl v1,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),3,1);
/* 002b5cb8: sdr v1,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),3,0);
/* 002b5cbc: sdl a1,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),5,1);
/* 002b5cc0: sdr a1,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),5,0);
/* 002b5cc4: jr ra */ {uint64_t target=cpu(31);/* delay 002b5cc8 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionMotion_002B5CA0(uint64_t a0){set(4,a0);body_002b5ca0();}
