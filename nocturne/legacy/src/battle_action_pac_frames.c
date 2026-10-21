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
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */
static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_pac_frames.h"
#include "battle_action_model_frames.h"
#include "battle_action_texture_creation_frames.h"
#include <stdio.h>
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}

static void pacCallback(uint64_t target){switch((uint32_t)target){
case 0x002c60e0u:ps2BattleActionPac_002C60E0(cpu(4));return;
case 0x002c61f0u:ps2BattleActionPac_002C61F0(cpu(4));return;
case 0x002c64b0u:set(2,ps2BattleActionPac_002C64B0(cpu(4),cpu(5),cpu(6)));return;
case 0x002c65b0u:ps2BattleActionPac_002C65B0(cpu(4));return;
case 0x002c6638u:ps2BattleActionPac_002C6638(cpu(4));return;
case 0x002c66b0u:ps2BattleActionPac_002C66B0(cpu(4));return;
case 0x002c6870u:ps2BattleActionPac_002C6870(cpu(4));return;
case 0x002c6900u:ps2BattleActionPac_002C6900(cpu(4));return;
case 0x002c6990u:ps2BattleActionPac_002C6990(cpu(4));return;
case 0x002c6a38u:ps2BattleActionPac_002C6A38(cpu(4));return;
case 0x002c6ad0u:ps2BattleActionPac_002C6AD0(cpu(4));return;
case 0x002c6c80u:ps2BattleActionPac_002C6C80(cpu(4));return;
case 0x002c6d18u:ps2BattleActionPac_002C6D18(cpu(4));return;
case 0x002c6d88u:ps2BattleActionPac_002C6D88(cpu(4));return;
case 0x002c6e00u:ps2BattleActionPac_002C6E00(cpu(4));return;
case 0x002c6e70u:ps2BattleActionPac_002C6E70(cpu(4));return;
default:fprintf(stderr,"Unrecovered actual PAC callback %08x\n",(uint32_t)target);abort();}}
void ps2BattleActionPac_002C6030(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c6030u);
uint64_t incoming=cpu(31);
/* 002c6030: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6034: li a2,0x38 */ set(6,sx(UINT32_C(0x00000038)));
/* 002c6038: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c603c: move s1,a1 */ set(17,cpu(5));
/* 002c6040: move a1,zero */ set(5,cpu(0));
/* 002c6044: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6048: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c604c: jal 0x002d4558 */ set(31,0x002c6054u);/* delay 002c6050 */ set(16,cpu(4));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 002c6054: lui v1,0x2c */ set(3,sx(UINT32_C(0x002c0000)));
/* 002c6058: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002c605c: addiu v1,v1,0x64b0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000064b0)));
/* 002c6060: beq s1,zero,0x002c6070 */ {int taken=(cpu(17)==cpu(0));/* delay 002c6064 */ sh(ea(16,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));if(taken){goto L_002c6070;}}
/* 002c6068: b 0x002c6074 */ /* delay 002c606c */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));goto L_002c6074;
L_002c6070:;
/* 002c6070: sw v1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
L_002c6074:;
/* 002c6074: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6078: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c607c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6080: jr ra */ {uint64_t target=cpu(31);/* delay 002c6084 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6088(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6088u);
uint64_t incoming=cpu(31);
/* 002c6088: lbu v0,0x1(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 002c608c: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 002c6090: jr ra */ {uint64_t target=cpu(31);/* delay 002c6094 */ sb(ea(4,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6098(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6098u);
uint64_t incoming=cpu(31);
/* 002c6098: lbu v0,0x1(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 002c609c: ori v0,v0,0x2 */ set(2,cpu(2)|UINT32_C(0x00000002));
/* 002c60a0: jr ra */ {uint64_t target=cpu(31);/* delay 002c60a4 */ sb(ea(4,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C60A8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c60a8u);
uint64_t incoming=cpu(31);
/* 002c60a8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c60ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c60b0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c60b4: lw s0,0x30(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002c60b8: beq s0,zero,0x002c60d0 */ {int taken=(cpu(16)==cpu(0));/* delay 002c60bc */ set(4,cpu(16));if(taken){goto L_002c60d0;}}
L_002c60c0:;
/* 002c60c0: jal 0x002a8bd8 */ set(31,0x002c60c8u);/* delay 002c60c4 */ lw(16,ea(16,(int32_t)UINT32_C(0x00000000)));ps2BattleActionModel_002A8BD8(cpu(4));
/* 002c60c8: bne s0,zero,0x002c60c0 */ {int taken=(cpu(16)!=cpu(0));/* delay 002c60cc */ set(4,cpu(16));if(taken){goto L_002c60c0;}}
L_002c60d0:;
/* 002c60d0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c60d4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c60d8: jr ra */ {uint64_t target=cpu(31);/* delay 002c60dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C60E0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c60e0u);
uint64_t incoming=cpu(31);
/* 002c60e0: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002c60e4: jr ra */ {uint64_t target=cpu(31);/* delay 002c60e8 */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C60F0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c60f0u);
uint64_t incoming=cpu(31);
/* 002c60f0: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002c60f4: lw v1,0x14(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000014)));
/* 002c60f8: lw a2,0x18(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002c60fc: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002c6100: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
/* 002c6104: sw v0,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002c6108: addu a2,a2,a1 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 002c610c: sw v1,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 002c6110: jr ra */ {uint64_t target=cpu(31);/* delay 002c6114 */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(6));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6118(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6118u);
uint64_t incoming=cpu(31);
/* 002c6118: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c611c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6120: move s1,a0 */ set(17,cpu(4));
/* 002c6124: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6128: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c612c: lw v0,0x18(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 002c6130: andi a1,v0,0x3f */ set(5,cpu(2)&UINT32_C(0x0000003f));
/* 002c6134: beq a1,zero,0x002c6150 */ {int taken=(cpu(5)==cpu(0));/* delay 002c6138 */ set(2,sx(UINT32_C(0x00000040)));if(taken){goto L_002c6150;}}
/* 002c613c: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002c6140: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 002c6144: sb v1,0x0(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
/* 002c6148: b 0x002c61d8 */ /* delay 002c614c */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));goto L_002c61d8;
L_002c6150:;
/* 002c6150: li a1,0x10 */ set(5,sx(UINT32_C(0x00000010)));
/* 002c6154: jal 0x002c60f0 */ set(31,0x002c615cu);/* delay 002c6158 */ lw(16,ea(17,(int32_t)UINT32_C(0x00000010)));ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c615c: lhu v1,0x2(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c6160: lw a3,0x4(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002c6164: move a0,s1 */ set(4,cpu(17));
/* 002c6168: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002c616c: lw v0,0x4(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002c6170: sh v1,0x2(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(3));
/* 002c6174: move a1,zero */ set(5,cpu(0));
/* 002c6178: move a2,s0 */ set(6,cpu(16));
/* 002c617c: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 002c6180: andi v1,v1,0xf0 */ set(3,cpu(3)&UINT32_C(0x000000f0));
/* 002c6184: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002c6188: subu a3,a3,v1 */ set(7,sx((uint32_t)cpu(7)-(uint32_t)cpu(3)));
/* 002c618c: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002c6194u);/* delay 002c6190 */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(7));pacCallback(target);}
/* 002c6194: move a0,s1 */ set(4,cpu(17));
/* 002c6198: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002c619c: bne v0,a1,0x002c61b8 */ {int taken=(cpu(2)!=cpu(5));/* delay 002c61a0 */ set(3,sx(UINT32_C(0x00000002)));if(taken){goto L_002c61b8;}}
/* 002c61a4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c61a8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c61ac: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c61b0: j 0x002c60e0 */ /* delay 002c61b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);ps2BattleActionPac_002C60E0(cpu(4));return;
L_002c61b8:;
/* 002c61b8: bnel v0,v1,0x002c61d8 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 002c61bc */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));goto L_002c61d8;}}
/* 002c61c0: lw v0,0x20(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 002c61c4: li v1,-0x40 */ set(3,sx(UINT32_C(0xffffffc0)));
/* 002c61c8: sb a1,0x0(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(5));
/* 002c61cc: addiu v0,v0,0x3f */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000003f)));
/* 002c61d0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002c61d4: sw v0,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
L_002c61d8:;
/* 002c61d8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c61dc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c61e0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c61e4: jr ra */ {uint64_t target=cpu(31);/* delay 002c61e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C61F0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c61f0u);
uint64_t incoming=cpu(31);
/* 002c61f0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c61f4: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002c61f8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c61fc: move s0,a0 */ set(16,cpu(4));
/* 002c6200: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6204: lw a2,0x34(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000034)));
/* 002c6208: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002c620c: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002c6214u);/* delay 002c6210 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000010)));pacCallback(target);}
/* 002c6214: move v1,v0 */ set(3,cpu(2));
/* 002c6218: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c621c: bne v1,v0,0x002c6238 */ {int taken=(cpu(3)!=cpu(2));/* delay 002c6220 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_002c6238;}}
/* 002c6224: move a0,s0 */ set(4,cpu(16));
/* 002c6228: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c622c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6230: j 0x002c60e0 */ /* delay 002c6234 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionPac_002C60E0(cpu(4));return;
L_002c6238:;
/* 002c6238: bnel v1,v0,0x002c628c */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 002c623c */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));goto L_002c628c;}}
/* 002c6240: lw a0,0x34(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000034)));
/* 002c6244: lw v1,0x30(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000030)));
/* 002c6248: bnel v1,a0,0x002c6264 */ {int taken=(cpu(3)!=cpu(4));if(taken){/* delay 002c624c */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_002c6264;}}
/* 002c6250: sw zero,0x34(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(0));
/* 002c6254: b 0x002c6280 */ /* delay 002c6258 */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));goto L_002c6280;
L_002c6260:;
/* 002c6260: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
L_002c6264:;
/* 002c6264: nop  */ 
/* 002c6268: nop  */ 
/* 002c626c: nop  */ 
/* 002c6270: nop  */ 
/* 002c6274: bnel v0,a0,0x002c6260 */ {int taken=(cpu(2)!=cpu(4));if(taken){/* delay 002c6278 */ set(3,cpu(2));goto L_002c6260;}}
/* 002c627c: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
L_002c6280:;
/* 002c6280: jal 0x002a8bd8 */ set(31,0x002c6288u);/* delay 002c6284 */ ps2BattleActionModel_002A8BD8(cpu(4));
/* 002c6288: sb zero,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
L_002c628c:;
/* 002c628c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6290: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6294: jr ra */ {uint64_t target=cpu(31);/* delay 002c6298 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionPac_002C62A0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x002c62a0u);
uint64_t incoming=cpu(31);
/* 002c62a0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002c62a4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c62a8: move s1,a0 */ set(17,cpu(4));
/* 002c62ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c62b0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c62b4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c62b8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c62bc: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c62c0: sw a1,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));
/* 002c62c4: blez a2,0x002c6388 */ {int taken=((int64_t)cpu(6)<=0);/* delay 002c62c8 */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(6));if(taken){goto L_002c6388;}}
/* 002c62cc: lbu a0,0x0(s1) */ set(4,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
/* 002c62d0: li s4,-0x1 */ set(20,sx(UINT32_C(0xffffffff)));
/* 002c62d4: li s3,0x1 */ set(19,sx(UINT32_C(0x00000001)));
/* 002c62d8: li s2,0x2 */ set(18,sx(UINT32_C(0x00000002)));
/* 002c62dc: sll v0,a0,0x18 */ set(2,sx((uint32_t)cpu(4)<<24));
L_002c62e0:;
/* 002c62e0: sra v1,v0,0x18 */ set(3,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 002c62e4: beq v1,zero,0x002c6320 */ {int taken=(cpu(3)==cpu(0));/* delay 002c62e8 */ if(taken){goto L_002c6320;}}
/* 002c62ec: bgtz v1,0x002c6308 */ {int taken=((int64_t)cpu(3)>0);/* delay 002c62f0 */ if(taken){goto L_002c6308;}}
/* 002c62f4: beq v1,s4,0x002c6394 */ {int taken=(cpu(3)==cpu(20));/* delay 002c62f8 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002c6394;}}
/* 002c62fc: b 0x002c6378 */ /* delay 002c6300 */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));goto L_002c6378;
L_002c6308:;
/* 002c6308: beql v1,s3,0x002c6330 */ {int taken=(cpu(3)==cpu(19));if(taken){/* delay 002c630c */ lw(16,ea(17,(int32_t)UINT32_C(0x00000020)));goto L_002c6330;}}
/* 002c6310: beql v1,s2,0x002c6368 */ {int taken=(cpu(3)==cpu(18));if(taken){/* delay 002c6314 */ lw(2,ea(17,(int32_t)UINT32_C(0x00000008)));goto L_002c6368;}}
/* 002c6318: b 0x002c6378 */ /* delay 002c631c */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));goto L_002c6378;
L_002c6320:;
/* 002c6320: jal 0x002c6118 */ set(31,0x002c6328u);/* delay 002c6324 */ set(4,cpu(17));ps2BattleActionPac_002C6118(cpu(4));
/* 002c6328: b 0x002c6374 */ /* delay 002c632c */ set(4,byte(ea(17,(int32_t)UINT32_C(0x00000000))));goto L_002c6374;
L_002c6330:;
/* 002c6330: move a0,s1 */ set(4,cpu(17));
/* 002c6334: lw v1,0x14(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 002c6338: slt v0,v1,s0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(16));
/* 002c633c: movn s0,v1,v0 */ if(cpu(2)!=0){set(16,cpu(3));}
/* 002c6340: jal 0x002c60f0 */ set(31,0x002c6348u);/* delay 002c6344 */ set(5,cpu(16));ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c6348: lw v0,0x20(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 002c634c: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 002c6350: bne v0,zero,0x002c6370 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c6354 */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));if(taken){goto L_002c6370;}}
/* 002c6358: sb zero,0x0(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 002c635c: b 0x002c6374 */ /* delay 002c6360 */ set(4,cpu(0));goto L_002c6374;
L_002c6368:;
/* 002c6368: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002c6370u);/* delay 002c636c */ set(4,cpu(17));pacCallback(target);}
L_002c6370:;
/* 002c6370: lbu a0,0x0(s1) */ set(4,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
L_002c6374:;
/* 002c6374: lw v0,0x14(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));
L_002c6378:;
/* 002c6378: bgtz v0,0x002c62e0 */ {int taken=((int64_t)cpu(2)>0);/* delay 002c637c */ set(2,sx((uint32_t)cpu(4)<<24));if(taken){goto L_002c62e0;}}
/* 002c6380: b 0x002c6394 */ /* delay 002c6384 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>24)));goto L_002c6394;
L_002c6388:;
/* 002c6388: lbu a0,0x0(s1) */ set(4,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
/* 002c638c: sll v0,a0,0x18 */ set(2,sx((uint32_t)cpu(4)<<24));
/* 002c6390: sra v0,v0,0x18 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>24)));
L_002c6394:;
/* 002c6394: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6398: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c639c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c63a0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c63a4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c63a8: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c63ac: jr ra */ {uint64_t target=cpu(31);/* delay 002c63b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPac_002C63B8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c63b8u);
uint64_t incoming=cpu(31);
/* 002c63b8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002c63bc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c63c0: move s1,a1 */ set(17,cpu(5));
/* 002c63c4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c63c8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c63cc: move s3,a0 */ set(19,cpu(4));
/* 002c63d0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c63d4: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c63d8: lbu s0,0x1(s1) */ set(16,byte(ea(17,(int32_t)UINT32_C(0x00000001))));
/* 002c63dc: andi s0,s0,0xf0 */ set(16,cpu(16)&UINT32_C(0x000000f0));
/* 002c63e0: jal 0x002a8ba8 */ set(31,0x002c63e8u);/* delay 002c63e4 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 002c63e8: move a1,s1 */ set(5,cpu(17));
/* 002c63ec: move s2,v0 */ set(18,cpu(2));
/* 002c63f0: addiu a2,s0,0x10 */ set(6,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002c63f4: sw s3,0x4(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(19));
/* 002c63f8: jal 0x002d43a4 */ set(31,0x002c6400u);/* delay 002c63fc */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0x00000010)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 002c6400: lw v1,0x34(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000034)));
/* 002c6404: bne v1,zero,0x002c6418 */ {int taken=(cpu(3)!=cpu(0));/* delay 002c6408 */ set(2,cpu(18));if(taken){goto L_002c6418;}}
/* 002c640c: b 0x002c641c */ /* delay 002c6410 */ sw(ea(19,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(18));goto L_002c641c;
L_002c6418:;
/* 002c6418: sw s2,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));
L_002c641c:;
/* 002c641c: sw s2,0x34(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(18));
/* 002c6420: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6424: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6428: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c642c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6430: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c6434: jr ra */ {uint64_t target=cpu(31);/* delay 002c6438 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPac_002C6440(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6440u);
uint64_t incoming=cpu(31);
/* 002c6440: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c6444: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6448: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c644c: lw a2,0x4(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 002c6450: addiu v1,a2,0x30 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0x00000030)));
/* 002c6454: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002c6458: beq v0,a0,0x002c647c */ {int taken=(cpu(2)==cpu(4));/* delay 002c645c */ set(5,cpu(0));if(taken){goto L_002c647c;}}
L_002c6460:;
/* 002c6460: move a1,v0 */ set(5,cpu(2));
/* 002c6464: lw v0,0x0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002c6468: nop  */ 
/* 002c646c: nop  */ 
/* 002c6470: nop  */ 
/* 002c6474: bne v0,a0,0x002c6460 */ {int taken=(cpu(2)!=cpu(4));/* delay 002c6478 */ set(3,cpu(5));if(taken){goto L_002c6460;}}
L_002c647c:;
/* 002c647c: lw s0,0x0(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002c6480: sw s0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002c6484: lw v0,0x34(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000034)));
/* 002c6488: beql v0,a0,0x002c6490 */ {int taken=(cpu(2)==cpu(4));if(taken){/* delay 002c648c */ sw(ea(6,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(5));goto L_002c6490;}}
L_002c6490:;
/* 002c6490: jal 0x002a8bd8 */ set(31,0x002c6498u);/* delay 002c6494 */ ps2BattleActionModel_002A8BD8(cpu(4));
/* 002c6498: move v0,s0 */ set(2,cpu(16));
/* 002c649c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c64a0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c64a4: jr ra */ {uint64_t target=cpu(31);/* delay 002c64a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPac_002C64B0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x002c64b0u);
uint64_t incoming=cpu(31);
/* 002c64b0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c64b4: bne a1,zero,0x002c6580 */ {int taken=(cpu(5)!=cpu(0));/* delay 002c64b8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002c6580;}}
/* 002c64bc: lbu a1,0x0(a2) */ set(5,byte(ea(6,(int32_t)UINT32_C(0x00000000))));
/* 002c64c0: li v0,0x6 */ set(2,sx(UINT32_C(0x00000006)));
/* 002c64c4: beq a1,v0,0x002c6548 */ {int taken=(cpu(5)==cpu(2));/* delay 002c64c8 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000007));if(taken){goto L_002c6548;}}
/* 002c64cc: beq v0,zero,0x002c64f0 */ {int taken=(cpu(2)==cpu(0));/* delay 002c64d0 */ set(2,sx(UINT32_C(0x00000009)));if(taken){goto L_002c64f0;}}
/* 002c64d4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c64d8: beq a1,v0,0x002c6528 */ {int taken=(cpu(5)==cpu(2));/* delay 002c64dc */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_002c6528;}}
/* 002c64e0: beq a1,v0,0x002c6538 */ {int taken=(cpu(5)==cpu(2));/* delay 002c64e4 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002c6538;}}
/* 002c64e8: b 0x002c6588 */ /* delay 002c64ec */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002c6588;
L_002c64f0:;
/* 002c64f0: beq a1,v0,0x002c6568 */ {int taken=(cpu(5)==cpu(2));/* delay 002c64f4 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000000a));if(taken){goto L_002c6568;}}
/* 002c64f8: beq v0,zero,0x002c6518 */ {int taken=(cpu(2)==cpu(0));/* delay 002c64fc */ set(3,sx(UINT32_C(0x000000ff)));if(taken){goto L_002c6518;}}
/* 002c6500: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002c6504: beq a1,v0,0x002c6558 */ {int taken=(cpu(5)==cpu(2));/* delay 002c6508 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002c6558;}}
/* 002c650c: b 0x002c6588 */ /* delay 002c6510 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002c6588;
L_002c6518:;
/* 002c6518: beq a1,v1,0x002c6584 */ {int taken=(cpu(5)==cpu(3));/* delay 002c651c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002c6584;}}
/* 002c6520: b 0x002c6578 */ /* delay 002c6524 */ set(2,sx(UINT32_C(0x00000003)));goto L_002c6578;
L_002c6528:;
/* 002c6528: jal 0x002c6840 */ set(31,0x002c6530u);/* delay 002c652c */ set(5,cpu(6));ps2BattleActionPac_002C6840(cpu(4),cpu(5));
/* 002c6530: b 0x002c6584 */ /* delay 002c6534 */ set(2,cpu(0));goto L_002c6584;
L_002c6538:;
/* 002c6538: jal 0x002c6cc0 */ set(31,0x002c6540u);/* delay 002c653c */ set(5,cpu(6));ps2BattleActionPac_002C6CC0(cpu(4),cpu(5));
/* 002c6540: b 0x002c6584 */ /* delay 002c6544 */ set(2,cpu(0));goto L_002c6584;
L_002c6548:;
/* 002c6548: jal 0x002c68d0 */ set(31,0x002c6550u);/* delay 002c654c */ set(5,cpu(6));ps2BattleActionPac_002C68D0(cpu(4),cpu(5));
/* 002c6550: b 0x002c6584 */ /* delay 002c6554 */ set(2,cpu(0));goto L_002c6584;
L_002c6558:;
/* 002c6558: jal 0x002c6960 */ set(31,0x002c6560u);/* delay 002c655c */ set(5,cpu(6));ps2BattleActionPac_002C6960(cpu(4),cpu(5));
/* 002c6560: b 0x002c6584 */ /* delay 002c6564 */ set(2,cpu(0));goto L_002c6584;
L_002c6568:;
/* 002c6568: jal 0x002c6ef8 */ set(31,0x002c6570u);/* delay 002c656c */ set(5,cpu(6));ps2BattleActionPac_002C6EF8(cpu(4),cpu(5));
/* 002c6570: b 0x002c6584 */ /* delay 002c6574 */ set(2,cpu(0));goto L_002c6584;
L_002c6578:;
/* 002c6578: b 0x002c6588 */ /* delay 002c657c */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002c6588;
L_002c6580:;
/* 002c6580: move v0,zero */ set(2,cpu(0));
L_002c6584:;
/* 002c6584: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002c6588:;
/* 002c6588: jr ra */ {uint64_t target=cpu(31);/* delay 002c658c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionPac_002C65B0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c65b0u);
uint64_t incoming=cpu(31);
/* 002c65b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c65b4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c65b8: move s0,a0 */ set(16,cpu(4));
/* 002c65bc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c65c0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c65c4: lw s1,0x20(s0) */ lw(17,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002c65c8: lw v1,0x14(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 002c65cc: slt v0,v1,s1 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(17));
/* 002c65d0: movn s1,v1,v0 */ if(cpu(2)!=0){set(17,cpu(3));}
/* 002c65d4: beq s1,zero,0x002c6620 */ {int taken=(cpu(17)==cpu(0));/* delay 002c65d8 */ set(6,cpu(17));if(taken){goto L_002c6620;}}
/* 002c65dc: lw a0,0x1c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 002c65e0: jal 0x002d43a4 */ set(31,0x002c65e8u);/* delay 002c65e4 */ lw(5,ea(16,(int32_t)UINT32_C(0x00000010)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 002c65e8: move a0,s0 */ set(4,cpu(16));
/* 002c65ec: jal 0x002c60f0 */ set(31,0x002c65f4u);/* delay 002c65f0 */ set(5,cpu(17));ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c65f4: move a0,s0 */ set(4,cpu(16));
/* 002c65f8: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 002c65fc: lw v1,0x20(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002c6600: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 002c6604: subu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));
/* 002c6608: sw v0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 002c660c: bne v1,zero,0x002c6620 */ {int taken=(cpu(3)!=cpu(0));/* delay 002c6610 */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));if(taken){goto L_002c6620;}}
/* 002c6614: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 002c6618: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002c6620u);/* delay 002c661c */ pacCallback(target);}
L_002c6620:;
/* 002c6620: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6624: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6628: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c662c: jr ra */ {uint64_t target=cpu(31);/* delay 002c6630 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6638(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6638u);
uint64_t incoming=cpu(31);
/* 002c6638: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c663c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6640: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6644: move s2,a0 */ set(18,cpu(4));
/* 002c6648: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c664c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6650: lw s0,0x14(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000014)));
/* 002c6654: lw a0,0x24(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000024)));
/* 002c6658: lw a1,0x10(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002c665c: jal 0x002c6f38 */ set(31,0x002c6664u);/* delay 002c6660 */ set(6,cpu(16));set(2,ps2BattleActionPac_002C6F38(cpu(4),cpu(5),cpu(6)));
/* 002c6664: move a0,s2 */ set(4,cpu(18));
/* 002c6668: move s1,v0 */ set(17,cpu(2));
/* 002c666c: lw v0,0x24(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000024)));
/* 002c6670: lw a1,0xc(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002c6674: jal 0x002c60f0 */ set(31,0x002c667cu);/* delay 002c6678 */ set(5,sx((uint32_t)cpu(16)-(uint32_t)cpu(5)));ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c667c: beql s1,zero,0x002c669c */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 002c6680 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002c669c;}}
/* 002c6684: jal 0x002a8bd8 */ set(31,0x002c668cu);/* delay 002c6688 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000024)));ps2BattleActionModel_002A8BD8(cpu(4));
/* 002c668c: lw v0,0xc(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 002c6690: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002c6698u);/* delay 002c6694 */ set(4,cpu(18));pacCallback(target);}
/* 002c6698: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002c669c:;
/* 002c669c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c66a0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c66a4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c66a8: jr ra */ {uint64_t target=cpu(31);/* delay 002c66ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C66B0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c66b0u);
uint64_t incoming=cpu(31);
/* 002c66b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c66b4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c66b8: move s1,a0 */ set(17,cpu(4));
/* 002c66bc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c66c0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c66c4: lw s0,0x20(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 002c66c8: lw v1,0x14(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 002c66cc: slt v0,v1,s0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(16));
/* 002c66d0: movn s0,v1,v0 */ if(cpu(2)!=0){set(16,cpu(3));}
/* 002c66d4: beq s0,zero,0x002c6704 */ {int taken=(cpu(16)==cpu(0));/* delay 002c66d8 */ set(5,cpu(16));if(taken){goto L_002c6704;}}
/* 002c66dc: jal 0x002c60f0 */ set(31,0x002c66e4u);/* delay 002c66e0 */ ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c66e4: lw v0,0x20(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 002c66e8: move a0,s1 */ set(4,cpu(17));
/* 002c66ec: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 002c66f0: bne v0,zero,0x002c6704 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c66f4 */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));if(taken){goto L_002c6704;}}
/* 002c66f8: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002c66fc: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002c6704u);/* delay 002c6700 */ pacCallback(target);}
L_002c6704:;
/* 002c6704: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6708: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c670c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6710: jr ra */ {uint64_t target=cpu(31);/* delay 002c6714 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6718(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c6718u);
uint64_t incoming=cpu(31);
/* 002c6718: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002c671c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6720: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6724: move s3,a1 */ set(19,cpu(5));
/* 002c6728: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c672c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6730: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c6734: lw s1,0xc(s3) */ lw(17,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 002c6738: bne s1,zero,0x002c6754 */ {int taken=(cpu(17)!=cpu(0));/* delay 002c673c */ set(18,cpu(4));if(taken){goto L_002c6754;}}
/* 002c6740: lbu v0,0x1(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000001))));
/* 002c6744: lw v1,0x4(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 002c6748: andi v0,v0,0xf0 */ set(2,cpu(2)&UINT32_C(0x000000f0));
/* 002c674c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002c6750: addiu s1,v1,-0x10 */ set(17,sx((uint32_t)cpu(3)+UINT32_C(0xfffffff0)));
L_002c6754:;
/* 002c6754: lbu v0,0x1(s2) */ set(2,byte(ea(18,(int32_t)UINT32_C(0x00000001))));
/* 002c6758: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002c675c: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 002c6760: beq v0,zero,0x002c6788 */ {int taken=(cpu(2)==cpu(0));/* delay 002c6764 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_002c6788;}}
/* 002c6768: jal 0x002c63b8 */ set(31,0x002c6770u);/* delay 002c676c */ set(2,ps2BattleActionPac_002C63B8(cpu(4),cpu(5)));
/* 002c6770: addiu a0,s3,0x10 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00000010)));
/* 002c6774: lui v1,0x2c */ set(3,sx(UINT32_C(0x002c0000)));
/* 002c6778: sw a0,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
/* 002c677c: addiu v1,v1,0x66b0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000066b0)));
/* 002c6780: b 0x002c6824 */ /* delay 002c6784 */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));goto L_002c6824;
L_002c6788:;
/* 002c6788: jal 0x002c63b8 */ set(31,0x002c6790u);/* delay 002c678c */ sb(ea(18,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));set(2,ps2BattleActionPac_002C63B8(cpu(4),cpu(5)));
/* 002c6790: move s0,v0 */ set(16,cpu(2));
/* 002c6794: lbu v0,0x1(s2) */ set(2,byte(ea(18,(int32_t)UINT32_C(0x00000001))));
/* 002c6798: andi v0,v0,0x2 */ set(2,cpu(2)&UINT32_C(0x00000002));
/* 002c679c: beq v0,zero,0x002c67b8 */ {int taken=(cpu(2)==cpu(0));/* delay 002c67a0 */ if(taken){goto L_002c67b8;}}
/* 002c67a4: jal 0x002a9158 */ set(31,0x002c67acu);/* delay 002c67a8 */ set(4,cpu(17));set(2,ps2BattleActionModel_002A9158(cpu(4)));
/* 002c67ac: b 0x002c67c4 */ /* delay 002c67b0 */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));goto L_002c67c4;
L_002c67b8:;
/* 002c67b8: jal 0x002a9038 */ set(31,0x002c67c0u);/* delay 002c67bc */ set(4,cpu(17));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 002c67c0: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_002c67c4:;
/* 002c67c4: jal 0x002a9688 */ set(31,0x002c67ccu);/* delay 002c67c8 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 002c67cc: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002c67d0: sw v0,0x1c(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 002c67d4: lbu v0,0x1(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000001))));
/* 002c67d8: andi a0,v0,0xf */ set(4,cpu(2)&UINT32_C(0x0000000f));
/* 002c67dc: beq a0,zero,0x002c67f8 */ {int taken=(cpu(4)==cpu(0));/* delay 002c67e0 */ set(2,sx(UINT32_C(0x002c0000)));if(taken){goto L_002c67f8;}}
/* 002c67e4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c67e8: beq a0,v0,0x002c6800 */ {int taken=(cpu(4)==cpu(2));/* delay 002c67ec */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002c6800;}}
/* 002c67f0: b 0x002c682c */ /* delay 002c67f4 */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));goto L_002c682c;
L_002c67f8:;
/* 002c67f8: b 0x002c6820 */ /* delay 002c67fc */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000065b0)));goto L_002c6820;
L_002c6800:;
/* 002c6800: jal 0x002a8af8 */ set(31,0x002c6808u);/* delay 002c6804 */ set(4,sx(UINT32_C(0x00000020)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002c6808: lw a1,0x1c(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x0000001c)));
/* 002c680c: sw v0,0x24(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
/* 002c6810: jal 0x002c72f0 */ set(31,0x002c6818u);/* delay 002c6814 */ set(4,cpu(2));ps2BattleActionPac_002C72F0(cpu(4),cpu(5));
/* 002c6818: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002c681c: addiu v0,v0,0x6638 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006638)));
L_002c6820:;
/* 002c6820: sw v0,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_002c6824:;
/* 002c6824: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6828: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
L_002c682c:;
/* 002c682c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6830: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6834: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c6838: jr ra */ {uint64_t target=cpu(31);/* delay 002c683c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6840(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c6840u);
uint64_t incoming=cpu(31);
/* 002c6840: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c6844: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6848: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c684c: jal 0x002c6718 */ set(31,0x002c6854u);/* delay 002c6850 */ set(16,cpu(4));ps2BattleActionPac_002C6718(cpu(4),cpu(5));
/* 002c6854: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002c6858: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c685c: addiu v0,v0,0x61f0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000061f0)));
/* 002c6860: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002c6864: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6868: jr ra */ {uint64_t target=cpu(31);/* delay 002c686c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6870(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6870u);
uint64_t incoming=cpu(31);
/* 002c6870: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6874: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6878: move s1,a0 */ set(17,cpu(4));
/* 002c687c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6880: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6884: lw v0,0x34(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000034)));
/* 002c6888: lw s0,0xc(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002c688c: addiu v1,s0,0x10 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002c6890: lw a2,0x4(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002c6894: move a0,v1 */ set(4,cpu(3));
/* 002c6898: sw v1,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 002c689c: move a3,a2 */ set(7,cpu(6));
/* 002c68a0: beq a2,zero,0x002c68b8 */ {int taken=(cpu(6)==cpu(0));/* delay 002c68a4 */ set(5,cpu(4));if(taken){goto L_002c68b8;}}
/* 002c68a8: lw a2,0x0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002c68ac: jal 0x002c39c8 */ set(31,0x002c68b4u);/* delay 002c68b0 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(6)));ps2BattleActionPac_002C39C8(cpu(4),cpu(5),cpu(6),cpu(7));
/* 002c68b4: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
L_002c68b8:;
/* 002c68b8: move a0,s1 */ set(4,cpu(17));
/* 002c68bc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c68c0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c68c4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c68c8: j 0x002c61f0 */ /* delay 002c68cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);ps2BattleActionPac_002C61F0(cpu(4));return;
}
void ps2BattleActionPac_002C68D0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c68d0u);
uint64_t incoming=cpu(31);
/* 002c68d0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c68d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c68d8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c68dc: jal 0x002c6718 */ set(31,0x002c68e4u);/* delay 002c68e0 */ set(16,cpu(4));ps2BattleActionPac_002C6718(cpu(4),cpu(5));
/* 002c68e4: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002c68e8: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c68ec: addiu v0,v0,0x6870 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006870)));
/* 002c68f0: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002c68f4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c68f8: jr ra */ {uint64_t target=cpu(31);/* delay 002c68fc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6900(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6900u);
uint64_t incoming=cpu(31);
/* 002c6900: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6904: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6908: move s1,a0 */ set(17,cpu(4));
/* 002c690c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6910: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6914: lw v0,0x34(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000034)));
/* 002c6918: lw s0,0xc(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002c691c: addiu v1,s0,0x10 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002c6920: lw a2,0x4(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002c6924: move a0,v1 */ set(4,cpu(3));
/* 002c6928: sw v1,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 002c692c: move a3,a2 */ set(7,cpu(6));
/* 002c6930: beq a2,zero,0x002c6948 */ {int taken=(cpu(6)==cpu(0));/* delay 002c6934 */ set(5,cpu(4));if(taken){goto L_002c6948;}}
/* 002c6938: lw a2,0x0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002c693c: jal 0x002c39c8 */ set(31,0x002c6944u);/* delay 002c6940 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(6)));ps2BattleActionPac_002C39C8(cpu(4),cpu(5),cpu(6),cpu(7));
/* 002c6944: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
L_002c6948:;
/* 002c6948: move a0,s1 */ set(4,cpu(17));
/* 002c694c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6950: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6954: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6958: j 0x002c61f0 */ /* delay 002c695c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);ps2BattleActionPac_002C61F0(cpu(4));return;
}
void ps2BattleActionPac_002C6960(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c6960u);
uint64_t incoming=cpu(31);
/* 002c6960: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c6964: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6968: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c696c: jal 0x002c6718 */ set(31,0x002c6974u);/* delay 002c6970 */ set(16,cpu(4));ps2BattleActionPac_002C6718(cpu(4),cpu(5));
/* 002c6974: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002c6978: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c697c: addiu v0,v0,0x6900 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006900)));
/* 002c6980: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002c6984: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6988: jr ra */ {uint64_t target=cpu(31);/* delay 002c698c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6990(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6990u);
uint64_t incoming=cpu(31);
/* 002c6990: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6994: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6998: move s2,a0 */ set(18,cpu(4));
/* 002c699c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c69a0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c69a4: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c69a8: lw s1,0x28(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002c69ac: lw v1,0x14(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000014)));
/* 002c69b0: lw s0,0xc(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002c69b4: slt v0,v1,s0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(16));
/* 002c69b8: movn s0,v1,v0 */ if(cpu(2)!=0){set(16,cpu(3));}
/* 002c69bc: beq s0,zero,0x002c6a20 */ {int taken=(cpu(16)==cpu(0));/* delay 002c69c0 */ set(6,cpu(16));if(taken){goto L_002c6a20;}}
/* 002c69c4: lw a0,0x8(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002c69c8: jal 0x002d43a4 */ set(31,0x002c69d0u);/* delay 002c69cc */ lw(5,ea(18,(int32_t)UINT32_C(0x00000010)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 002c69d0: move a0,s2 */ set(4,cpu(18));
/* 002c69d4: jal 0x002c60f0 */ set(31,0x002c69dcu);/* delay 002c69d8 */ set(5,cpu(16));ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c69dc: lw v0,0x8(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002c69e0: lw v1,0xc(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002c69e4: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002c69e8: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 002c69ec: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002c69f0: bne v1,zero,0x002c6a20 */ {int taken=(cpu(3)!=cpu(0));/* delay 002c69f4 */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));if(taken){goto L_002c6a20;}}
/* 002c69f8: jal 0x002a9688 */ set(31,0x002c6a00u);/* delay 002c69fc */ lw(4,ea(17,(int32_t)UINT32_C(0x00000004)));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 002c6a00: jal 0x002abe08 */ set(31,0x002c6a08u);/* delay 002c6a04 */ set(4,cpu(2));set(2,ps2BattleActionTexture_002ABE08(cpu(4)));
/* 002c6a08: addiu a0,s1,0x4 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
/* 002c6a0c: jal 0x002a9618 */ set(31,0x002c6a14u);/* delay 002c6a10 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));ps2BattleActionModel_002A9618(cpu(4));
/* 002c6a14: lw v0,0xc(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 002c6a18: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002c6a20u);/* delay 002c6a1c */ set(4,cpu(18));pacCallback(target);}
L_002c6a20:;
/* 002c6a20: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6a24: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6a28: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6a2c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6a30: jr ra */ {uint64_t target=cpu(31);/* delay 002c6a34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6A38(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6a38u);
uint64_t incoming=cpu(31);
/* 002c6a38: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6a3c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6a40: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6a44: move s2,a0 */ set(18,cpu(4));
/* 002c6a48: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6a4c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6a50: lw s0,0x20(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 002c6a54: lw a0,0x24(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000024)));
/* 002c6a58: lw a1,0x10(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002c6a5c: jal 0x002c6f38 */ set(31,0x002c6a64u);/* delay 002c6a60 */ set(6,cpu(16));set(2,ps2BattleActionPac_002C6F38(cpu(4),cpu(5),cpu(6)));
/* 002c6a64: move a0,s2 */ set(4,cpu(18));
/* 002c6a68: move s1,v0 */ set(17,cpu(2));
/* 002c6a6c: lw v0,0x24(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000024)));
/* 002c6a70: lw a1,0xc(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 002c6a74: jal 0x002c60f0 */ set(31,0x002c6a7cu);/* delay 002c6a78 */ set(5,sx((uint32_t)cpu(16)-(uint32_t)cpu(5)));ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c6a7c: beq s1,zero,0x002c6abc */ {int taken=(cpu(17)==cpu(0));/* delay 002c6a80 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002c6abc;}}
/* 002c6a84: lw s0,0x28(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002c6a88: jal 0x002a9688 */ set(31,0x002c6a90u);/* delay 002c6a8c */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 002c6a90: jal 0x002abe08 */ set(31,0x002c6a98u);/* delay 002c6a94 */ set(4,cpu(2));set(2,ps2BattleActionTexture_002ABE08(cpu(4)));
/* 002c6a98: addiu a0,s0,0x4 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000004)));
/* 002c6a9c: jal 0x002a9618 */ set(31,0x002c6aa4u);/* delay 002c6aa0 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));ps2BattleActionModel_002A9618(cpu(4));
/* 002c6aa4: jal 0x002a8bd8 */ set(31,0x002c6aacu);/* delay 002c6aa8 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000024)));ps2BattleActionModel_002A8BD8(cpu(4));
/* 002c6aac: lw v0,0xc(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 002c6ab0: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002c6ab8u);/* delay 002c6ab4 */ set(4,cpu(18));pacCallback(target);}
/* 002c6ab8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002c6abc:;
/* 002c6abc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6ac0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6ac4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6ac8: jr ra */ {uint64_t target=cpu(31);/* delay 002c6acc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6AD0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6ad0u);
uint64_t incoming=cpu(31);
/* 002c6ad0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6ad4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6ad8: move s2,a0 */ set(18,cpu(4));
/* 002c6adc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6ae0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6ae4: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6ae8: lw s1,0x28(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000028)));
/* 002c6aec: lw v1,0x14(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000014)));
/* 002c6af0: lw s0,0xc(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002c6af4: slt v0,v1,s0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(16));
/* 002c6af8: movn s0,v1,v0 */ if(cpu(2)!=0){set(16,cpu(3));}
/* 002c6afc: beq s0,zero,0x002c6b34 */ {int taken=(cpu(16)==cpu(0));/* delay 002c6b00 */ set(5,cpu(16));if(taken){goto L_002c6b34;}}
/* 002c6b04: jal 0x002c60f0 */ set(31,0x002c6b0cu);/* delay 002c6b08 */ ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c6b0c: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002c6b10: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 002c6b14: bne v0,zero,0x002c6b34 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c6b18 */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));if(taken){goto L_002c6b34;}}
/* 002c6b1c: jal 0x002abe20 */ set(31,0x002c6b24u);/* delay 002c6b20 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000008)));set(2,ps2BattleActionPac_002ABE20(cpu(4)));
/* 002c6b24: lw v1,0xc(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 002c6b28: sw v0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002c6b2c: jalr v1 */ {uint64_t target=cpu(3);set(31,0x002c6b34u);/* delay 002c6b30 */ set(4,cpu(18));pacCallback(target);}
L_002c6b34:;
/* 002c6b34: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6b38: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6b3c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6b40: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6b44: jr ra */ {uint64_t target=cpu(31);/* delay 002c6b48 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6B50(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x002c6b50u);
uint64_t incoming=cpu(31);
/* 002c6b50: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6b54: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6b58: move s0,a2 */ set(16,cpu(6));
/* 002c6b5c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6b60: move s1,a0 */ set(17,cpu(4));
/* 002c6b64: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6b68: move s2,a1 */ set(18,cpu(5));
/* 002c6b6c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6b70: sw s0,0x28(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(16));
/* 002c6b74: lw v0,0x4(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 002c6b78: addiu v0,v0,-0x10 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffff0)));
/* 002c6b7c: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002c6b80: lbu v1,0x1(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000001))));
/* 002c6b84: andi v0,v1,0x1 */ set(2,cpu(3)&UINT32_C(0x00000001));
/* 002c6b88: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 002c6b8c: beq v0,zero,0x002c6bb0 */ {int taken=(cpu(2)==cpu(0));/* delay 002c6b90 */ set(2,sx(UINT32_C(0x002c0000)));if(taken){goto L_002c6bb0;}}
/* 002c6b94: lw v1,0x10(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002c6b98: addiu v0,v0,0x6ad0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006ad0)));
/* 002c6b9c: addiu v1,v1,-0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xfffffff0)));
/* 002c6ba0: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002c6ba4: b 0x002c6c64 */ /* delay 002c6ba8 */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));goto L_002c6c64;
L_002c6bb0:;
/* 002c6bb0: andi v0,v1,0x2 */ set(2,cpu(3)&UINT32_C(0x00000002));
/* 002c6bb4: beq v0,zero,0x002c6bd0 */ {int taken=(cpu(2)==cpu(0));/* delay 002c6bb8 */ if(taken){goto L_002c6bd0;}}
/* 002c6bbc: jal 0x002a9158 */ set(31,0x002c6bc4u);/* delay 002c6bc0 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000004)));set(2,ps2BattleActionModel_002A9158(cpu(4)));
/* 002c6bc4: b 0x002c6bdc */ /* delay 002c6bc8 */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));goto L_002c6bdc;
L_002c6bd0:;
/* 002c6bd0: jal 0x002a9038 */ set(31,0x002c6bd8u);/* delay 002c6bd4 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000004)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 002c6bd8: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002c6bdc:;
/* 002c6bdc: jal 0x002a9688 */ set(31,0x002c6be4u);/* delay 002c6be0 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 002c6be4: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002c6be8: ldl v1,0x7(s2) */ loadPartial(3,ea(18,(int32_t)UINT32_C(0x00000007)),1);
/* 002c6bec: ldr v1,0x0(s2) */ loadPartial(3,ea(18,(int32_t)UINT32_C(0x00000000)),0);
/* 002c6bf0: ldl a0,0xf(s2) */ loadPartial(4,ea(18,(int32_t)UINT32_C(0x0000000f)),1);
/* 002c6bf4: ldr a0,0x8(s2) */ loadPartial(4,ea(18,(int32_t)UINT32_C(0x00000008)),0);
/* 002c6bf8: sdl v1,0x7(v0) */ storePartial(ea(2,(int32_t)UINT32_C(0x00000007)),3,1);
/* 002c6bfc: sdr v1,0x0(v0) */ storePartial(ea(2,(int32_t)UINT32_C(0x00000000)),3,0);
/* 002c6c00: sdl a0,0xf(v0) */ storePartial(ea(2,(int32_t)UINT32_C(0x0000000f)),4,1);
/* 002c6c04: sdr a0,0x8(v0) */ storePartial(ea(2,(int32_t)UINT32_C(0x00000008)),4,0);
/* 002c6c08: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002c6c0c: addiu v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 002c6c10: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002c6c14: lbu a1,0x1(s2) */ set(5,byte(ea(18,(int32_t)UINT32_C(0x00000001))));
/* 002c6c18: beq a1,zero,0x002c6c38 */ {int taken=(cpu(5)==cpu(0));/* delay 002c6c1c */ set(2,sx(UINT32_C(0x002c0000)));if(taken){goto L_002c6c38;}}
/* 002c6c20: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c6c24: beq a1,v0,0x002c6c40 */ {int taken=(cpu(5)==cpu(2));/* delay 002c6c28 */ if(taken){goto L_002c6c40;}}
/* 002c6c2c: b 0x002c6c68 */ /* delay 002c6c30 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002c6c68;
L_002c6c38:;
/* 002c6c38: b 0x002c6c60 */ /* delay 002c6c3c */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006990)));goto L_002c6c60;
L_002c6c40:;
/* 002c6c40: jal 0x002a8af8 */ set(31,0x002c6c48u);/* delay 002c6c44 */ set(4,sx(UINT32_C(0x00000020)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002c6c48: sw v0,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
/* 002c6c4c: move a0,v0 */ set(4,cpu(2));
/* 002c6c50: jal 0x002c72f0 */ set(31,0x002c6c58u);/* delay 002c6c54 */ lw(5,ea(16,(int32_t)UINT32_C(0x00000008)));ps2BattleActionPac_002C72F0(cpu(4),cpu(5));
/* 002c6c58: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002c6c5c: addiu v0,v0,0x6a38 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006a38)));
L_002c6c60:;
/* 002c6c60: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_002c6c64:;
/* 002c6c64: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002c6c68:;
/* 002c6c68: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6c6c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6c70: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6c74: jr ra */ {uint64_t target=cpu(31);/* delay 002c6c78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6C80(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6c80u);
uint64_t incoming=cpu(31);
/* 002c6c80: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c6c84: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6c88: move s0,a0 */ set(16,cpu(4));
/* 002c6c8c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6c90: lw v1,0x2c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000002c)));
/* 002c6c94: lw a0,0x34(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000034)));
/* 002c6c98: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002c6c9c: sw v0,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002c6ca0: jal 0x002a8bd8 */ set(31,0x002c6ca8u);/* delay 002c6ca4 */ lw(4,ea(16,(int32_t)UINT32_C(0x0000002c)));ps2BattleActionModel_002A8BD8(cpu(4));
/* 002c6ca8: move a0,s0 */ set(4,cpu(16));
/* 002c6cac: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6cb0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6cb4: j 0x002c61f0 */ /* delay 002c6cb8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionPac_002C61F0(cpu(4));return;
}
void ps2BattleActionPac_002C6CC0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c6cc0u);
uint64_t incoming=cpu(31);
/* 002c6cc0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6cc4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6cc8: move s0,a0 */ set(16,cpu(4));
/* 002c6ccc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6cd0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6cd4: jal 0x002c63b8 */ set(31,0x002c6cdcu);/* delay 002c6cd8 */ set(17,cpu(5));set(2,ps2BattleActionPac_002C63B8(cpu(4),cpu(5)));
/* 002c6cdc: jal 0x002a8af8 */ set(31,0x002c6ce4u);/* delay 002c6ce0 */ set(4,sx(UINT32_C(0x00000010)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002c6ce4: move a0,s0 */ set(4,cpu(16));
/* 002c6ce8: sw v0,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(2));
/* 002c6cec: move a1,s1 */ set(5,cpu(17));
/* 002c6cf0: jal 0x002c6b50 */ set(31,0x002c6cf8u);/* delay 002c6cf4 */ set(6,cpu(2));ps2BattleActionPac_002C6B50(cpu(4),cpu(5),cpu(6));
/* 002c6cf8: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002c6cfc: addiu v0,v0,0x6c80 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006c80)));
/* 002c6d00: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6d04: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002c6d08: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6d0c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6d10: jr ra */ {uint64_t target=cpu(31);/* delay 002c6d14 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6D18(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6d18u);
uint64_t incoming=cpu(31);
/* 002c6d18: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c6d1c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6d20: move s0,a0 */ set(16,cpu(4));
/* 002c6d24: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6d28: lw a1,0x2c(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x0000002c)));
/* 002c6d2c: addiu a2,a1,0x20 */ set(6,sx((uint32_t)cpu(5)+UINT32_C(0x00000020)));
/* 002c6d30: jal 0x002c6b50 */ set(31,0x002c6d38u);/* delay 002c6d34 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));ps2BattleActionPac_002C6B50(cpu(4),cpu(5),cpu(6));
/* 002c6d38: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002c6d3c: addiu v0,v0,0x6d88 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006d88)));
/* 002c6d40: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6d44: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002c6d48: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6d4c: jr ra */ {uint64_t target=cpu(31);/* delay 002c6d50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6D58(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6d58u);
uint64_t incoming=cpu(31);
/* 002c6d58: lw v1,0x2c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000002c)));
/* 002c6d5c: lui a1,0x2c */ set(5,sx(UINT32_C(0x002c0000)));
/* 002c6d60: lui v0,0x2c */ set(2,sx(UINT32_C(0x002c0000)));
/* 002c6d64: addiu a1,a1,0x65b0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000065b0)));
/* 002c6d68: addiu v0,v0,0x6d18 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00006d18)));
/* 002c6d6c: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002c6d70: li a2,0x10 */ set(6,sx(UINT32_C(0x00000010)));
/* 002c6d74: sw v0,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002c6d78: sw v1,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(3));
/* 002c6d7c: sw a2,0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(6));
/* 002c6d80: jr ra */ {uint64_t target=cpu(31);/* delay 002c6d84 */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6D88(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6d88u);
uint64_t incoming=cpu(31);
/* 002c6d88: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6d8c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6d90: move s1,a0 */ set(17,cpu(4));
/* 002c6d94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6d98: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6d9c: lw s0,0x2c(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000002c)));
/* 002c6da0: lw v0,0x34(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000034)));
/* 002c6da4: lw a1,0x20(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002c6da8: jal 0x002b2b10 */ set(31,0x002c6db0u);/* delay 002c6dac */ lw(4,ea(2,(int32_t)UINT32_C(0x00000008)));ps2BattleActionModel_002B2B10(cpu(4),cpu(5));
/* 002c6db0: move a0,s0 */ set(4,cpu(16));
/* 002c6db4: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002c6db8: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002c6dbc: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002c6dc0: bne v0,v1,0x002c6de8 */ {int taken=(cpu(2)!=cpu(3));/* delay 002c6dc4 */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_002c6de8;}}
/* 002c6dc8: jal 0x002a8bd8 */ set(31,0x002c6dd0u);/* delay 002c6dcc */ ps2BattleActionModel_002A8BD8(cpu(4));
/* 002c6dd0: move a0,s1 */ set(4,cpu(17));
/* 002c6dd4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6dd8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6ddc: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6de0: j 0x002c61f0 */ /* delay 002c6de4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);ps2BattleActionPac_002C61F0(cpu(4));return;
L_002c6de8:;
/* 002c6de8: move a0,s1 */ set(4,cpu(17));
/* 002c6dec: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6df0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6df4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6df8: j 0x002c6d58 */ /* delay 002c6dfc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);ps2BattleActionPac_002C6D58(cpu(4));return;
}
void ps2BattleActionPac_002C6E00(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6e00u);
uint64_t incoming=cpu(31);
/* 002c6e00: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6e04: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6e08: move s1,a0 */ set(17,cpu(4));
/* 002c6e0c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6e10: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6e14: lw s0,0x14(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 002c6e18: lw v1,0x20(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 002c6e1c: slt v0,v1,s0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(16));
/* 002c6e20: movn s0,v1,v0 */ if(cpu(2)!=0){set(16,cpu(3));}
/* 002c6e24: jal 0x002c60f0 */ set(31,0x002c6e2cu);/* delay 002c6e28 */ set(5,cpu(16));ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c6e2c: move a0,s1 */ set(4,cpu(17));
/* 002c6e30: lw v0,0x20(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 002c6e34: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 002c6e38: bne v0,zero,0x002c6e58 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c6e3c */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));if(taken){goto L_002c6e58;}}
/* 002c6e40: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6e44: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6e48: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6e4c: j 0x002c6d58 */ /* delay 002c6e50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);ps2BattleActionPac_002C6D58(cpu(4));return;
L_002c6e58:;
/* 002c6e58: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6e5c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6e60: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6e64: jr ra */ {uint64_t target=cpu(31);/* delay 002c6e68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6E70(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002c6e70u);
uint64_t incoming=cpu(31);
/* 002c6e70: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c6e74: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6e78: move s2,a0 */ set(18,cpu(4));
/* 002c6e7c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6e80: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6e84: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6e88: lw v0,0x14(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000014)));
/* 002c6e8c: beq v0,zero,0x002c6ee0 */ {int taken=(cpu(2)==cpu(0));/* delay 002c6e90 */ set(5,sx(UINT32_C(0x00000004)));if(taken){goto L_002c6ee0;}}
/* 002c6e94: lw v0,0x10(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 002c6e98: jal 0x002c60f0 */ set(31,0x002c6ea0u);/* delay 002c6e9c */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));ps2BattleActionPac_002C60F0(cpu(4),cpu(5));
/* 002c6ea0: lw v0,0x2c(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x0000002c)));
/* 002c6ea4: move a0,s0 */ set(4,cpu(16));
/* 002c6ea8: lw s1,0x34(s2) */ lw(17,ea(18,(int32_t)UINT32_C(0x00000034)));
/* 002c6eac: sw s0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002c6eb0: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 002c6eb4: sw zero,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002c6eb8: jal 0x002b2a60 */ set(31,0x002c6ec0u);/* delay 002c6ebc */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000053)));set(2,ps2BattleActionModel_002B2A60(cpu(4)));
/* 002c6ec0: li v1,-0x40 */ set(3,sx(UINT32_C(0xffffffc0)));
/* 002c6ec4: and s0,s0,v1 */ set(16,cpu(16)&cpu(3));
/* 002c6ec8: lui a0,0x2c */ set(4,sx(UINT32_C(0x002c0000)));
/* 002c6ecc: addiu s0,s0,-0x14 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffec)));
/* 002c6ed0: addiu a0,a0,0x6e00 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00006e00)));
/* 002c6ed4: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002c6ed8: sw a0,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 002c6edc: sw s0,0x20(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(16));
L_002c6ee0:;
/* 002c6ee0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6ee4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6ee8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6eec: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6ef0: jr ra */ {uint64_t target=cpu(31);/* delay 002c6ef4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C6EF8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c6ef8u);
uint64_t incoming=cpu(31);
/* 002c6ef8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c6efc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6f00: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6f04: jal 0x002c63b8 */ set(31,0x002c6f0cu);/* delay 002c6f08 */ set(16,cpu(4));set(2,ps2BattleActionPac_002C63B8(cpu(4),cpu(5)));
/* 002c6f0c: jal 0x002a8af8 */ set(31,0x002c6f14u);/* delay 002c6f10 */ set(4,sx(UINT32_C(0x00000030)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002c6f14: lui v1,0x2c */ set(3,sx(UINT32_C(0x002c0000)));
/* 002c6f18: addiu v1,v1,0x6e70 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00006e70)));
/* 002c6f1c: sw v0,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(2));
/* 002c6f20: sw v1,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002c6f24: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6f28: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6f2c: jr ra */ {uint64_t target=cpu(31);/* delay 002c6f30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionPac_00175D78(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00175d78u);
uint64_t incoming=cpu(31);
/* 00175d78: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00175d7c: move a3,a0 */ set(7,cpu(4));
/* 00175d80: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00175d84: li a2,0x101 */ set(6,sx(UINT32_C(0x00000101)));
/* 00175d88: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00175d8c: li a0,0x7 */ set(4,sx(UINT32_C(0x00000007)));
/* 00175d90: lw a1,-0x4f8c(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffb074)));
/* 00175d94: lw t0,0x0(a3) */ lw(8,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 00175d98: jal 0x001de2e0 */ set(31,0x00175da0u);/* delay 00175d9c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));ps2BattleActionPac_001DE2E0(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
/* 00175da0: li a0,0x7 */ set(4,sx(UINT32_C(0x00000007)));
/* 00175da4: jal 0x001dd0d0 */ set(31,0x00175dacu);/* delay 00175da8 */ lw(5,ea(28,(int32_t)UINT32_C(0xffffb074)));set(2,ps2BattleActionModel_001DD0D0(cpu(4),cpu(5)));
/* 00175dac: move s0,v0 */ set(16,cpu(2));
/* 00175db0: jal 0x00175cd0 */ set(31,0x00175db8u);/* delay 00175db4 */ set(4,cpu(16));ps2BattleActionModel_00175CD0(cpu(4));
/* 00175db8: lw v1,-0x4f8c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb074)));
/* 00175dbc: move v0,s0 */ set(2,cpu(16));
/* 00175dc0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00175dc4: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 00175dc8: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00175dcc: sw v1,-0x4f8c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffb074)),(uint32_t)cpu(3));
/* 00175dd0: jr ra */ {uint64_t target=cpu(31);/* delay 00175dd4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionPac_001DE2E0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);nocturneEffectAxisNoteEntry(0x001de2e0u);
uint64_t incoming=cpu(31);
/* 001de2e0: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 001de2e4: sd s2,0x50(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001de2e8: move s2,a2 */ set(18,cpu(6));
/* 001de2ec: sd s3,0x58(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001de2f0: move s3,a0 */ set(19,cpu(4));
/* 001de2f4: sd s4,0x60(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001de2f8: move s4,a1 */ set(20,cpu(5));
/* 001de2fc: move a0,sp */ set(4,cpu(29));
/* 001de300: move a1,zero */ set(5,cpu(0));
/* 001de304: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001de308: move s0,a3 */ set(16,cpu(7));
/* 001de30c: sd s1,0x48(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001de310: sd ra,0x68(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001de314: jal 0x002c6030 */ set(31,0x001de31cu);/* delay 001de318 */ set(17,cpu(8));ps2BattleActionPac_002C6030(cpu(4),cpu(5));
/* 001de31c: andi v0,s2,0x2 */ set(2,cpu(18)&UINT32_C(0x00000002));
/* 001de320: beq v0,zero,0x001de330 */ {int taken=(cpu(2)==cpu(0));/* delay 001de324 */ set(4,cpu(29));if(taken){goto L_001de330;}}
/* 001de328: jal 0x002c6088 */ set(31,0x001de330u);/* delay 001de32c */ ps2BattleActionPac_002C6088(cpu(4));
L_001de330:;
/* 001de330: move a0,sp */ set(4,cpu(29));
/* 001de334: move a1,s0 */ set(5,cpu(16));
/* 001de338: jal 0x002c62a0 */ set(31,0x001de340u);/* delay 001de33c */ set(6,cpu(17));set(2,ps2BattleActionPac_002C62A0(cpu(4),cpu(5),cpu(6)));
/* 001de340: move a1,s3 */ set(5,cpu(19));
/* 001de344: lw a0,0x30(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001de348: move a2,s4 */ set(6,cpu(20));
/* 001de34c: jal 0x001ddf00 */ set(31,0x001de354u);/* delay 001de350 */ set(7,cpu(18));set(2,ps2BattleActionModel_001DDF00(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 001de354: jal 0x002c60a8 */ set(31,0x001de35cu);/* delay 001de358 */ set(4,cpu(29));ps2BattleActionPac_002C60A8(cpu(4));
/* 001de35c: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001de360: ld s1,0x48(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001de364: ld s2,0x50(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001de368: ld s3,0x58(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001de36c: ld s4,0x60(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001de370: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001de374: jr ra */ {uint64_t target=cpu(31);/* delay 001de378 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPac_002C39C8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectAxisNoteEntry(0x002c39c8u);
uint64_t incoming=cpu(31);
/* 002c39c8: blez a3,0x002c3aa4 */ {int taken=((int64_t)cpu(7)<=0);/* delay 002c39cc */ set(9,cpu(6));if(taken){goto L_002c3aa4;}}
/* 002c39d0: lbu t0,0x0(t1) */ set(8,byte(ea(9,(int32_t)UINT32_C(0x00000000))));
/* 002c39d4: nop  */ 
L_002c39d8:;
/* 002c39d8: andi v0,t0,0x1 */ set(2,cpu(8)&UINT32_C(0x00000001));
/* 002c39dc: bne v0,zero,0x002c39f0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c39e0 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000001)));if(taken){goto L_002c39f0;}}
/* 002c39e4: b 0x002c3a80 */ /* delay 002c39e8 */ set(8,sx((uint32_t)((int32_t)cpu(8)>>1)));goto L_002c3a80;
L_002c39f0:;
/* 002c39f0: andi v0,t0,0x2 */ set(2,cpu(8)&UINT32_C(0x00000002));
/* 002c39f4: bne v0,zero,0x002c3a18 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c39f8 */ set(2,cpu(8)&UINT32_C(0x00000004));if(taken){goto L_002c3a18;}}
/* 002c39fc: lbu v0,0x0(t1) */ set(2,byte(ea(9,(int32_t)UINT32_C(0x00000000))));
/* 002c3a00: addiu t1,t1,0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000001)));
/* 002c3a04: sll v0,v0,0x8 */ set(2,sx((uint32_t)cpu(2)<<8));
/* 002c3a08: or v0,t0,v0 */ set(2,cpu(8)|cpu(2));
/* 002c3a0c: b 0x002c3a80 */ /* delay 002c3a10 */ set(8,sx((uint32_t)((int32_t)cpu(2)>>2)));goto L_002c3a80;
L_002c3a18:;
/* 002c3a18: bne v0,zero,0x002c3a48 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c3a1c */ set(2,sx((uint32_t)((int32_t)cpu(8)>>3)));if(taken){goto L_002c3a48;}}
/* 002c3a20: lbu v0,0x0(t1) */ set(2,byte(ea(9,(int32_t)UINT32_C(0x00000000))));
/* 002c3a24: lbu v1,0x1(t1) */ set(3,byte(ea(9,(int32_t)UINT32_C(0x00000001))));
/* 002c3a28: addiu t1,t1,0x2 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000002)));
/* 002c3a2c: sll v0,v0,0x8 */ set(2,sx((uint32_t)cpu(2)<<8));
/* 002c3a30: or v0,t0,v0 */ set(2,cpu(8)|cpu(2));
/* 002c3a34: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002c3a38: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002c3a3c: b 0x002c3a80 */ /* delay 002c3a40 */ set(8,sx((uint32_t)((int32_t)cpu(2)>>3)));goto L_002c3a80;
L_002c3a48:;
/* 002c3a48: addiu t0,v0,0x2 */ set(8,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 002c3a4c: blez t0,0x002c3a94 */ {int taken=((int64_t)cpu(8)<=0);/* delay 002c3a50 */ set(10,cpu(0));if(taken){goto L_002c3a94;}}
/* 002c3a54: nop  */ 
L_002c3a58:;
/* 002c3a58: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 002c3a5c: addiu t2,t2,0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000001)));
/* 002c3a60: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002c3a64: slt v1,t2,t0 */ set(3,(int64_t)cpu(10)<(int64_t)cpu(8));
/* 002c3a68: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002c3a6c: bne v1,zero,0x002c3a58 */ {int taken=(cpu(3)!=cpu(0));/* delay 002c3a70 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_002c3a58;}}
/* 002c3a74: b 0x002c3a98 */ /* delay 002c3a78 */ set(2,sx((uint32_t)cpu(9)-(uint32_t)cpu(6)));goto L_002c3a98;
L_002c3a80:;
/* 002c3a80: sll v1,t0,0x2 */ set(3,sx((uint32_t)cpu(8)<<2));
/* 002c3a84: addu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 002c3a88: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002c3a8c: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002c3a90: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002c3a94:;
/* 002c3a94: subu v0,t1,a2 */ set(2,sx((uint32_t)cpu(9)-(uint32_t)cpu(6)));
L_002c3a98:;
/* 002c3a98: slt v0,v0,a3 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(7));
/* 002c3a9c: bnel v0,zero,0x002c39d8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002c3aa0 */ set(8,byte(ea(9,(int32_t)UINT32_C(0x00000000))));goto L_002c39d8;}}
L_002c3aa4:;
/* 002c3aa4: jr ra */ {uint64_t target=cpu(31);/* delay 002c3aa8 */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionPac_002C6F38(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x002c6f38u);
uint64_t incoming=cpu(31);
/* 002c6f38: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002c6f3c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c6f40: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c6f44: move s1,a0 */ set(17,cpu(4));
/* 002c6f48: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c6f4c: move s3,a1 */ set(19,cpu(5));
/* 002c6f50: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c6f54: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c6f58: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c6f5c: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c6f60: lbu v1,0x0(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
/* 002c6f64: beq v1,zero,0x002c72d0 */ {int taken=(cpu(3)==cpu(0));/* delay 002c6f68 */ set(20,cpu(6));if(taken){goto L_002c72d0;}}
/* 002c6f6c: sw zero,-0x2000(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffe000)),(uint32_t)cpu(0));
/* 002c6f70: blez s4,0x002c72c0 */ {int taken=((int64_t)cpu(20)<=0);/* delay 002c6f74 */ lw(18,ea(17,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_002c72c0;}}
/* 002c6f78: lbu v0,0x0(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
/* 002c6f7c: nop  */ 
L_002c6f80:;
/* 002c6f80: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002c6f84: sltiu v1,v0,0xa */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 002c6f88: beq v1,zero,0x002c72b8 */ {int taken=(cpu(3)==cpu(0));/* delay 002c6f8c */ set(2,sx((uint32_t)cpu(2)<<2));if(taken){goto L_002c72b8;}}
/* 002c6f90: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002c6f94: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002c6f98: lw v1,-0x5cf0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffa310)));
/* 002c6f9c: jr v1 */ {uint64_t target=cpu(3);/* delay 002c6fa0 */ switch((uint32_t)target){case 0x002c6fa8u:goto L_002c6fa8;case 0x002c7030u:goto L_002c7030;case 0x002c7050u:goto L_002c7050;case 0x002c7078u:goto L_002c7078;case 0x002c7140u:goto L_002c7140;case 0x002c7188u:goto L_002c7188;case 0x002c71b8u:goto L_002c71b8;case 0x002c71f8u:goto L_002c71f8;case 0x002c7218u:goto L_002c7218;case 0x002c7260u:goto L_002c7260;default:fprintf(stderr,"Unexpected native PAC decoder jump %08x\n",(uint32_t)target);abort();}}
L_002c6fa8:;
/* 002c6fa8: lw v0,-0x2000(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffe000)));
/* 002c6fac: addiu s4,s4,-0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffffff)));
/* 002c6fb0: addiu v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002c6fb4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002c6fb8: andi v1,v1,0xf */ set(3,cpu(3)&UINT32_C(0x0000000f));
/* 002c6fbc: lui at,0x59 */ set(1,sx(UINT32_C(0x00590000)));
/* 002c6fc0: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 002c6fc4: sw s3,0x4780(at) */ sw(ea(1,(int32_t)UINT32_C(0x00004780)),(uint32_t)cpu(19));
/* 002c6fc8: sw v1,-0x2000(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffe000)),(uint32_t)cpu(3));
/* 002c6fcc: lbu v1,0x0(s3) */ set(3,byte(ea(19,(int32_t)UINT32_C(0x00000000))));
/* 002c6fd0: sltiu v0,v1,0xe0 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x000000e0));
/* 002c6fd4: bne v0,zero,0x002c7000 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c6fd8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));if(taken){goto L_002c7000;}}
/* 002c6fdc: li v0,0xff */ set(2,sx(UINT32_C(0x000000ff)));
/* 002c6fe0: bne v1,v0,0x002c72b8 */ {int taken=(cpu(3)!=cpu(2));/* delay 002c6fe4 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002c72b8;}}
/* 002c6fe8: sw s2,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(18));
/* 002c6fec: sw s3,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));
/* 002c6ff0: sw s4,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(20));
/* 002c6ff4: b 0x002c72d0 */ /* delay 002c6ff8 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));goto L_002c72d0;
L_002c7000:;
/* 002c7000: andi v0,v1,0xe0 */ set(2,cpu(3)&UINT32_C(0x000000e0));
/* 002c7004: andi a0,v1,0x1f */ set(4,cpu(3)&UINT32_C(0x0000001f));
/* 002c7008: bne a0,zero,0x002c7020 */ {int taken=(cpu(4)!=cpu(0));/* delay 002c700c */ sb(ea(17,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));if(taken){goto L_002c7020;}}
/* 002c7010: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002c7014: b 0x002c72b8 */ /* delay 002c7018 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7020:;
/* 002c7020: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 002c7024: sh a0,0x2(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(4));
/* 002c7028: b 0x002c72b8 */ /* delay 002c702c */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7030:;
/* 002c7030: lbu v1,0x0(s3) */ set(3,byte(ea(19,(int32_t)UINT32_C(0x00000000))));
/* 002c7034: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002c7038: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002c703c: addiu s4,s4,-0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffffff)));
/* 002c7040: sh v1,0x2(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(3));
/* 002c7044: b 0x002c72b8 */ /* delay 002c7048 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7050:;
/* 002c7050: lbu v0,0x0(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000000))));
/* 002c7054: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002c7058: lhu v1,0x2(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c705c: li a0,0x4 */ set(4,sx(UINT32_C(0x00000004)));
/* 002c7060: sll v0,v0,0x8 */ set(2,sx((uint32_t)cpu(2)<<8));
/* 002c7064: sb a0,0x0(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 002c7068: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002c706c: addiu s4,s4,-0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffffff)));
/* 002c7070: b 0x002c72b8 */ /* delay 002c7074 */ sh(ea(17,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(3));goto L_002c72b8;
L_002c7078:;
/* 002c7078: lbu v1,0x1(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000001))));
/* 002c707c: li v0,0x40 */ set(2,sx(UINT32_C(0x00000040)));
/* 002c7080: beq v1,v0,0x002c7110 */ {int taken=(cpu(3)==cpu(2));/* delay 002c7084 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000041));if(taken){goto L_002c7110;}}
/* 002c7088: beq v0,zero,0x002c70a8 */ {int taken=(cpu(2)==cpu(0));/* delay 002c708c */ set(2,sx(UINT32_C(0x00000080)));if(taken){goto L_002c70a8;}}
/* 002c7090: beq v1,zero,0x002c70e0 */ {int taken=(cpu(3)==cpu(0));/* delay 002c7094 */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_002c70e0;}}
/* 002c7098: beql v1,v0,0x002c70f0 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 002c709c */ set(16,half(ea(17,(int32_t)UINT32_C(0x00000002))));goto L_002c70f0;}}
/* 002c70a0: b 0x002c72b8 */ /* delay 002c70a4 */ goto L_002c72b8;
L_002c70a8:;
/* 002c70a8: beq v1,v0,0x002c7128 */ {int taken=(cpu(3)==cpu(2));/* delay 002c70ac */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000081));if(taken){goto L_002c7128;}}
/* 002c70b0: beq v0,zero,0x002c70d0 */ {int taken=(cpu(2)==cpu(0));/* delay 002c70b4 */ set(2,sx(UINT32_C(0x000000a0)));if(taken){goto L_002c70d0;}}
/* 002c70b8: li v0,0x60 */ set(2,sx(UINT32_C(0x00000060)));
/* 002c70bc: beq v1,v0,0x002c7120 */ {int taken=(cpu(3)==cpu(2));/* delay 002c70c0 */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_002c7120;}}
/* 002c70c4: b 0x002c72b8 */ /* delay 002c70c8 */ goto L_002c72b8;
L_002c70d0:;
/* 002c70d0: beq v1,v0,0x002c7138 */ {int taken=(cpu(3)==cpu(2));/* delay 002c70d4 */ set(2,sx(UINT32_C(0x0000000a)));if(taken){goto L_002c7138;}}
/* 002c70d8: b 0x002c72b8 */ /* delay 002c70dc */ goto L_002c72b8;
L_002c70e0:;
/* 002c70e0: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 002c70e4: b 0x002c72b8 */ /* delay 002c70e8 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c70f0:;
/* 002c70f0: move a0,s2 */ set(4,cpu(18));
/* 002c70f4: move a1,zero */ set(5,cpu(0));
/* 002c70f8: move a2,s0 */ set(6,cpu(16));
/* 002c70fc: jal 0x002d4558 */ set(31,0x002c7104u);/* delay 002c7100 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(16)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 002c7104: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002c7108: b 0x002c72b8 */ /* delay 002c710c */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));goto L_002c72b8;
L_002c7110:;
/* 002c7110: li v0,0x6 */ set(2,sx(UINT32_C(0x00000006)));
/* 002c7114: b 0x002c72b8 */ /* delay 002c7118 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7120:;
/* 002c7120: b 0x002c72b8 */ /* delay 002c7124 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7128:;
/* 002c7128: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002c712c: b 0x002c72b8 */ /* delay 002c7130 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7138:;
/* 002c7138: b 0x002c72b8 */ /* delay 002c713c */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7140:;
/* 002c7140: lhu s0,0x2(s1) */ set(16,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c7144: move a0,s2 */ set(4,cpu(18));
/* 002c7148: move a1,s3 */ set(5,cpu(19));
/* 002c714c: slt v0,s4,s0 */ set(2,(int64_t)cpu(20)<(int64_t)cpu(16));
/* 002c7150: movn s0,s4,v0 */ if(cpu(2)!=0){set(16,cpu(20));}
/* 002c7154: move a2,s0 */ set(6,cpu(16));
/* 002c7158: jal 0x002d43a4 */ set(31,0x002c7160u);/* delay 002c715c */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(16)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 002c7160: lhu v1,0x2(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c7164: addu s3,s3,s0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(16)));
/* 002c7168: subu s4,s4,s0 */ set(20,sx((uint32_t)cpu(20)-(uint32_t)cpu(16)));
/* 002c716c: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 002c7170: andi v0,v1,0xffff */ set(2,cpu(3)&UINT32_C(0x0000ffff));
/* 002c7174: bne v0,zero,0x002c72b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c7178 */ sh(ea(17,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(3));if(taken){goto L_002c72b8;}}
/* 002c717c: b 0x002c7258 */ /* delay 002c7180 */ set(2,sx(UINT32_C(0x00000001)));goto L_002c7258;
L_002c7188:;
/* 002c7188: lhu s0,0x2(s1) */ set(16,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c718c: move a0,s2 */ set(4,cpu(18));
/* 002c7190: lbu a1,0x0(s3) */ set(5,byte(ea(19,(int32_t)UINT32_C(0x00000000))));
/* 002c7194: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002c7198: move a2,s0 */ set(6,cpu(16));
/* 002c719c: jal 0x002d4558 */ set(31,0x002c71a4u);/* delay 002c71a0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(16)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 002c71a4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002c71a8: addiu s4,s4,-0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffffff)));
/* 002c71ac: b 0x002c72b8 */ /* delay 002c71b0 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));goto L_002c72b8;
L_002c71b8:;
/* 002c71b8: lbu v0,0x0(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000000))));
/* 002c71bc: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002c71c0: lhu s0,0x2(s1) */ set(16,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c71c4: addiu s4,s4,-0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffffff)));
/* 002c71c8: subu v1,s2,v0 */ set(3,sx((uint32_t)cpu(18)-(uint32_t)cpu(2)));
/* 002c71cc: nop  */ 
L_002c71d0:;
/* 002c71d0: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 002c71d4: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002c71d8: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 002c71dc: sb v0,0x0(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002c71e0: nop  */ 
/* 002c71e4: bne s0,zero,0x002c71d0 */ {int taken=(cpu(16)!=cpu(0));/* delay 002c71e8 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));if(taken){goto L_002c71d0;}}
/* 002c71ec: b 0x002c7258 */ /* delay 002c71f0 */ set(2,sx(UINT32_C(0x00000001)));goto L_002c7258;
L_002c71f8:;
/* 002c71f8: lbu v0,0x0(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000000))));
/* 002c71fc: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002c7200: addiu s4,s4,-0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffffff)));
/* 002c7204: bne s4,zero,0x002c7218 */ {int taken=(cpu(20)!=cpu(0));/* delay 002c7208 */ sb(ea(17,(int32_t)UINT32_C(0x00000010)),(uint8_t)cpu(2));if(taken){goto L_002c7218;}}
/* 002c720c: li v0,0x9 */ set(2,sx(UINT32_C(0x00000009)));
/* 002c7210: b 0x002c72b8 */ /* delay 002c7214 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7218:;
/* 002c7218: lbu v0,0x0(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000000))));
/* 002c721c: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002c7220: lbu v1,0x10(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000010))));
/* 002c7224: addiu s4,s4,-0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0xffffffff)));
/* 002c7228: sll v0,v0,0x8 */ set(2,sx((uint32_t)cpu(2)<<8));
/* 002c722c: lhu s0,0x2(s1) */ set(16,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c7230: or v0,v1,v0 */ set(2,cpu(3)|cpu(2));
/* 002c7234: subu v1,s2,v0 */ set(3,sx((uint32_t)cpu(18)-(uint32_t)cpu(2)));
L_002c7238:;
/* 002c7238: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 002c723c: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002c7240: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 002c7244: sb v0,0x0(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002c7248: nop  */ 
/* 002c724c: bne s0,zero,0x002c7238 */ {int taken=(cpu(16)!=cpu(0));/* delay 002c7250 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));if(taken){goto L_002c7238;}}
/* 002c7254: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002c7258:;
/* 002c7258: b 0x002c72b8 */ /* delay 002c725c */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002c72b8;
L_002c7260:;
/* 002c7260: lhu s0,0x2(s1) */ set(16,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c7264: slt v0,s4,s0 */ set(2,(int64_t)cpu(20)<(int64_t)cpu(16));
/* 002c7268: beq v0,zero,0x002c7288 */ {int taken=(cpu(2)==cpu(0));/* delay 002c726c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002c7288;}}
/* 002c7270: lhu v0,0x2(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x00000002))));
/* 002c7274: move s0,s4 */ set(16,cpu(20));
/* 002c7278: move s4,zero */ set(20,cpu(0));
/* 002c727c: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 002c7280: b 0x002c7298 */ /* delay 002c7284 */ sh(ea(17,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));goto L_002c7298;
L_002c7288:;
/* 002c7288: sh zero,0x2(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(0));
/* 002c728c: sb v0,0x0(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002c7290: subu s4,s4,s0 */ set(20,sx((uint32_t)cpu(20)-(uint32_t)cpu(16)));
/* 002c7294: nop  */ 
L_002c7298:;
/* 002c7298: lbu v0,0x0(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000000))));
/* 002c729c: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002c72a0: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 002c72a4: sb v0,0x0(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002c72a8: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 002c72ac: sb zero,0x0(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 002c72b0: bne s0,zero,0x002c7298 */ {int taken=(cpu(16)!=cpu(0));/* delay 002c72b4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));if(taken){goto L_002c7298;}}
L_002c72b8:;
/* 002c72b8: bgtzl s4,0x002c6f80 */ {int taken=((int64_t)cpu(20)>0);if(taken){/* delay 002c72bc */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000000))));goto L_002c6f80;}}
L_002c72c0:;
/* 002c72c0: sw s2,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(18));
/* 002c72c4: move v0,zero */ set(2,cpu(0));
/* 002c72c8: sw s3,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));
/* 002c72cc: sw s4,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(20));
L_002c72d0:;
/* 002c72d0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c72d4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c72d8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c72dc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c72e0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c72e4: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c72e8: jr ra */ {uint64_t target=cpu(31);/* delay 002c72ec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionPac_002C72F0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x002c72f0u);
uint64_t incoming=cpu(31);
/* 002c72f0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c72f4: sw a1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 002c72f8: jr ra */ {uint64_t target=cpu(31);/* delay 002c72fc */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionPac_002ABE20(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x002abe20u);
uint64_t incoming=cpu(31);
/* 002abe20: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002abe24: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002abe28: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002abe2c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002abe30: j 0x002abc90 */ /* delay 002abe34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);set(2,ps2BattleActionTexture_002ABC90(cpu(4),cpu(5)));return cpu(2);
}
