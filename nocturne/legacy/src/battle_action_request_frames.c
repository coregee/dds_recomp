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
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_request_frames.h"
#include "battle_action_pac_frames.h"
#include "battle_action_model_frames.h"
#include "battle_action_texture_creation_frames.h"
#include "battle_action_printf_frames.h"
#include "file_device.h"
#include "file_worker_control.h"
#include "file_loader_support.h"
#include "model_pac_loading.h"
#include "diagnostic_transport.h"
#include "diagnostic_rpc.h"
#include "sdk_debug.h"
#include "../tests/libc_stream_mode.h"
#include <stdio.h>
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void requestLq(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneEffectHostCpuWrite(d,q);}
static void requestPacked(unsigned kind,unsigned d,unsigned s,unsigned t){
 uint32_t a[4],c[4],q[4];nocturneEffectHostCpuRead(s,a);nocturneEffectHostCpuRead(t,c);
 if(kind==0){q[0]=c[0];q[1]=c[1];q[2]=a[0];q[3]=a[1];}
 else if(kind==1){q[0]=a[2];q[1]=a[3];q[2]=c[2];q[3]=c[3];}
 else if(kind==2){for(unsigned i=0;i<4;i++)q[i]=a[i]&c[i];}
 else if(kind==3){for(unsigned i=0;i<4;i++)q[i]=~(a[i]|c[i]);}
 else{uint8_t x[16],y[16],z[16];memcpy(x,a,16);memcpy(y,c,16);for(unsigned i=0;i<16;i++)z[i]=(uint8_t)(x[i]-y[i]);memcpy(q,z,16);}
 nocturneEffectHostCpuWrite(d,q);
}

static void body_001dc230(void);
static void body_001dc910(void);
static void body_001dc968(void);
static void body_001dc9b8(void);
static void body_001dca30(void);
static void body_001de1a0(void);
static void body_00296648(void);
static void body_002966a8(void);
static void body_002966c0(void);
static void body_00296738(void);
static void body_002967e8(void);
static void body_002968a8(void);
static void body_002968b8(void);
static void body_002968f8(void);
static void body_002969a0(void);
static void body_002969c8(void);
static void body_002969f0(void);
static void body_00296a68(void);
static void body_00296a88(void);
static void body_00296aa8(void);
static void body_00296ab0(void);
static void body_00296ab8(void);
static void body_00296ac8(void);
static void body_00296b08(void);
static void body_00296b28(void);
static void body_00296b70(void);
static void body_00296b88(void);
static void body_00296bd8(void);
static void body_00296c68(void);
static void body_00296c88(void);
static void body_00296d90(void);
static void body_00296f50(void);
static void body_00296fd8(void);
static void body_00297218(void);
static void body_002972a0(void);
static void body_00297460(void);
static void body_00297658(void);
static void body_002976c0(void);
static void body_002a8078(void);
static void body_002bd4a8(void);
static void body_002bd550(void);
static void body_002be6a8(void);
static void body_002bf688(void);
static void body_002bf800(void);
static void body_002bf898(void);
static void body_002bfd60(void);
static void body_002c3798(void);
static void body_002c3888(void);
static void body_002c3928(void);
static void body_002d5d0c(void);
static void body_002d7f88(void);
static void body_002dbd30(void);
static void body_002dbec0(void);
static void body_002dbee0(void);
static void completion(uint64_t target){switch((uint32_t)target){
case 0x001dc968u:body_001dc968();return;
case 0x001dc9b8u:body_001dc9b8();return;
case 0x001dca30u:body_001dca30();return;
case 0x001de1a0u:body_001de1a0();return;
case 0x00296aa8u:body_00296aa8();return;
case 0x00296ab0u:body_00296ab0();return;
case 0x00296ab8u:body_00296ab8();return;
case 0x002967e8u:body_002967e8();return;
default:fprintf(stderr,"Unrecovered native resource completion %08x\n",(uint32_t)target);abort();}}
static void notification(uint64_t target){switch((uint32_t)target){
case 0x001ddb68u:(void)ps2BattleActionModel_001DDB68(cpu(4));return;
case 0x002a8078u:body_002a8078();return;
default:fprintf(stderr,"Unrecovered native model notification %08x\n",(uint32_t)target);abort();}}
static void body_001dc230(void){
nocturneEffectAxisNoteEntry(0x001dc230u);
uint64_t incoming=cpu(31);
/* 001dc230: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dc234: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 001dc238: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc23c: lui v1,0x33 */ set(3,sx(UINT32_C(0x00330000)));
/* 001dc240: addiu v1,v1,-0x3b88 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffc478)));
/* 001dc244: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001dc248: lw a0,0x0(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001dc24c: beq a0,zero,0x001dc288 */ {int taken=(cpu(4)==cpu(0));/* delay 001dc250 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001dc288;}}
/* 001dc254: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
L_001dc258:;
/* 001dc258: bnel v0,a1,0x001dc278 */ {int taken=(cpu(2)!=cpu(5));if(taken){/* delay 001dc25c */ set(3,cpu(4));goto L_001dc278;}}
/* 001dc260: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001dc264: jal 0x002a8bd8 */ set(31,0x001dc26cu);/* delay 001dc268 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));ps2BattleActionModel_002A8BD8(cpu(4));
/* 001dc26c: b 0x001dc288 */ /* delay 001dc270 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001dc288;
L_001dc278:;
/* 001dc278: lw a0,0x0(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001dc27c: bnel a0,zero,0x001dc258 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 001dc280 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));goto L_001dc258;}}
/* 001dc284: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001dc288:;
/* 001dc288: jr ra */ {uint64_t target=cpu(31);/* delay 001dc28c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_001DC230(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_001dc230();}
static void body_001dc910(void){
nocturneEffectAxisNoteEntry(0x001dc910u);
uint64_t incoming=cpu(31);
/* 001dc910: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dc914: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc918: move s0,a0 */ set(16,cpu(4));
/* 001dc91c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc920: addiu a3,s0,0xc */ set(7,sx((uint32_t)cpu(16)+UINT32_C(0x0000000c)));
/* 001dc924: lw a2,0x8(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001dc928: lhu a1,0x2(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000002))));
/* 001dc92c: jal 0x001dc808 */ set(31,0x001dc934u);/* delay 001dc930 */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000000))));ps2BattleActionModel_001DC808(cpu(4),cpu(5),cpu(6),cpu(7));
/* 001dc934: jal 0x002dbee0 */ set(31,0x001dc93cu);/* delay 001dc938 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdd8c)));body_002dbee0();
/* 001dc93c: lhu a0,0x0(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 001dc940: jal 0x001dc230 */ set(31,0x001dc948u);/* delay 001dc944 */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000002))));body_001dc230();
/* 001dc948: jal 0x002dbec0 */ set(31,0x001dc950u);/* delay 001dc94c */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdd8c)));body_002dbec0();
/* 001dc950: move a0,s0 */ set(4,cpu(16));
/* 001dc954: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc958: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc95c: j 0x002a8bd8 */ /* delay 001dc960 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionModel_002A8BD8(cpu(4));return;
}
void ps2BattleActionRequest_001DC910(uint64_t a0){set(4,a0);body_001dc910();}
static void body_001dc968(void){
nocturneEffectAxisNoteEntry(0x001dc968u);
uint64_t incoming=cpu(31);
/* 001dc968: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dc96c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc970: move s0,a1 */ set(16,cpu(5));
/* 001dc974: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc978: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc97c: jal 0x00296ab0 */ set(31,0x001dc984u);/* delay 001dc980 */ set(17,cpu(4));body_00296ab0();
/* 001dc984: jal 0x002c3798 */ set(31,0x001dc98cu);/* delay 001dc988 */ set(4,cpu(2));body_002c3798();
/* 001dc98c: move a0,s1 */ set(4,cpu(17));
/* 001dc990: jal 0x00296aa8 */ set(31,0x001dc998u);/* delay 001dc994 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));body_00296aa8();
/* 001dc998: jal 0x002a9558 */ set(31,0x001dc9a0u);/* delay 001dc99c */ set(4,cpu(2));ps2BattleActionModel_002A9558(cpu(4));
/* 001dc9a0: move a0,s1 */ set(4,cpu(17));
/* 001dc9a4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc9a8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc9ac: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc9b0: j 0x002966c0 */ /* delay 001dc9b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002966c0();return;
}
void ps2BattleActionRequest_001DC968(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_001dc968();}
static void body_001dc9b8(void){
nocturneEffectAxisNoteEntry(0x001dc9b8u);
uint64_t incoming=cpu(31);
/* 001dc9b8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dc9bc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dc9c0: move s0,a1 */ set(16,cpu(5));
/* 001dc9c4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dc9c8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dc9cc: jal 0x00296aa8 */ set(31,0x001dc9d4u);/* delay 001dc9d0 */ set(17,cpu(4));body_00296aa8();
/* 001dc9d4: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001dc9d8: jal 0x00296ab0 */ set(31,0x001dc9e0u);/* delay 001dc9dc */ set(4,cpu(17));body_00296ab0();
/* 001dc9e0: jal 0x002c3888 */ set(31,0x001dc9e8u);/* delay 001dc9e4 */ set(4,cpu(2));body_002c3888();
/* 001dc9e8: move a0,s1 */ set(4,cpu(17));
/* 001dc9ec: jal 0x002966c0 */ set(31,0x001dc9f4u);/* delay 001dc9f0 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));body_002966c0();
/* 001dc9f4: lbu v0,0x6(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 001dc9f8: bne v0,zero,0x001dca18 */ {int taken=(cpu(2)!=cpu(0));/* delay 001dc9fc */ set(4,cpu(16));if(taken){goto L_001dca18;}}
/* 001dca00: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dca04: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dca08: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dca0c: j 0x001dc910 */ /* delay 001dca10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_001dc910();return;
L_001dca18:;
/* 001dca18: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dca1c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dca20: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dca24: jr ra */ {uint64_t target=cpu(31);/* delay 001dca28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_001DC9B8(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_001dc9b8();}
static void body_001dca30(void){
nocturneEffectAxisNoteEntry(0x001dca30u);
uint64_t incoming=cpu(31);
/* 001dca30: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001dca34: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dca38: move s0,a1 */ set(16,cpu(5));
/* 001dca3c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dca40: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dca44: jal 0x00296aa8 */ set(31,0x001dca4cu);/* delay 001dca48 */ set(17,cpu(4));body_00296aa8();
/* 001dca4c: sw v0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 001dca50: jal 0x00296ab0 */ set(31,0x001dca58u);/* delay 001dca54 */ set(4,cpu(17));body_00296ab0();
/* 001dca58: jal 0x002c3928 */ set(31,0x001dca60u);/* delay 001dca5c */ set(4,cpu(2));body_002c3928();
/* 001dca60: move a0,s1 */ set(4,cpu(17));
/* 001dca64: jal 0x002966c0 */ set(31,0x001dca6cu);/* delay 001dca68 */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));body_002966c0();
/* 001dca6c: move a0,s0 */ set(4,cpu(16));
/* 001dca70: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001dca74: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dca78: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001dca7c: j 0x001dc910 */ /* delay 001dca80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_001dc910();return;
}
void ps2BattleActionRequest_001DCA30(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_001dca30();}
static void body_001de1a0(void){
nocturneEffectAxisNoteEntry(0x001de1a0u);
uint64_t incoming=cpu(31);
/* 001de1a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001de1a4: move v0,a0 */ set(2,cpu(4));
/* 001de1a8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001de1ac: move s0,a1 */ set(16,cpu(5));
/* 001de1b0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001de1b4: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001de1b8: lhu a2,0x2(s0) */ set(6,half(ea(16,(int32_t)UINT32_C(0x00000002))));
/* 001de1bc: lw a3,0x4(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 001de1c0: lhu a1,0x0(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 001de1c4: jal 0x001ddf00 */ set(31,0x001de1ccu);/* delay 001de1c8 */ lw(4,ea(2,(int32_t)UINT32_C(0x00000060)));set(2,ps2BattleActionModel_001DDF00(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 001de1cc: jal 0x002dbee0 */ set(31,0x001de1d4u);/* delay 001de1d0 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdd8c)));body_002dbee0();
/* 001de1d4: lhu a0,0x0(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 001de1d8: jal 0x001dc230 */ set(31,0x001de1e0u);/* delay 001de1dc */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000002))));body_001dc230();
/* 001de1e0: jal 0x002dbec0 */ set(31,0x001de1e8u);/* delay 001de1e4 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdd8c)));body_002dbec0();
/* 001de1e8: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001de1ec: beql v0,zero,0x001de210 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001de1f0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001de210;}}
/* 001de1f4: jalr v0 */ {uint64_t target=cpu(2);set(31,0x001de1fcu);/* delay 001de1f8 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));notification(target);}
/* 001de1fc: move a0,s0 */ set(4,cpu(16));
/* 001de200: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001de204: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001de208: j 0x001de170 */ /* delay 001de20c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionModel_001DE170(cpu(4));return;
L_001de210:;
/* 001de210: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001de214: jr ra */ {uint64_t target=cpu(31);/* delay 001de218 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_001DE1A0(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_001de1a0();}
static void body_00296648(void){
nocturneEffectAxisNoteEntry(0x00296648u);
uint64_t incoming=cpu(31);
/* 00296648: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0029664c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296650: move s0,a0 */ set(16,cpu(4));
/* 00296654: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296658: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
/* 0029665c: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00296660: bne v1,a0,0x00296698 */ {int taken=(cpu(3)!=cpu(4));/* delay 00296664 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00296698;}}
/* 00296668: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0029666c: beq v0,zero,0x0029667c */ {int taken=(cpu(2)==cpu(0));/* delay 00296670 */ set(4,cpu(2));if(taken){goto L_0029667c;}}
/* 00296674: jal 0x002bf688 */ set(31,0x0029667cu);/* delay 00296678 */ body_002bf688();
L_0029667c:;
/* 0029667c: jal 0x002c60a8 */ set(31,0x00296684u);/* delay 00296680 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));ps2BattleActionPac_002C60A8(cpu(4));
/* 00296684: jal 0x002a8bd8 */ set(31,0x0029668cu);/* delay 00296688 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));ps2BattleActionModel_002A8BD8(cpu(4));
/* 0029668c: jal 0x002a8bd8 */ set(31,0x00296694u);/* delay 00296690 */ set(4,cpu(16));ps2BattleActionModel_002A8BD8(cpu(4));
/* 00296694: move v0,zero */ set(2,cpu(0));
L_00296698:;
/* 00296698: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029669c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002966a0: jr ra */ {uint64_t target=cpu(31);/* delay 002966a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296648(uint64_t a0){set(4,a0);body_00296648();return cpu(2);}
static void body_002966a8(void){
nocturneEffectAxisNoteEntry(0x002966a8u);
uint64_t incoming=cpu(31);
/* 002966a8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002966ac: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002966b0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002966b4: j 0x00296648 */ /* delay 002966b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00296648();return;
}
uint64_t ps2BattleActionRequest_002966A8(uint64_t a0){set(4,a0);body_002966a8();return cpu(2);}
static void body_002966c0(void){
nocturneEffectAxisNoteEntry(0x002966c0u);
uint64_t incoming=cpu(31);
/* 002966c0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002966c4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002966c8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002966cc: move s0,a0 */ set(16,cpu(4));
/* 002966d0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002966d4: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002966d8: bnel v0,v1,0x002966f0 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 002966dc */ set(4,byte(ea(16,(int32_t)UINT32_C(0x00000001))));goto L_002966f0;}}
/* 002966e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002966e4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002966e8: j 0x00296648 */ /* delay 002966ec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00296648();return;
L_002966f0:;
/* 002966f0: li v1,0x6 */ set(3,sx(UINT32_C(0x00000006)));
/* 002966f4: bne a0,v1,0x00296724 */ {int taken=(cpu(4)!=cpu(3));/* delay 002966f8 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00296724;}}
/* 002966fc: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 00296700: beq v0,zero,0x00296710 */ {int taken=(cpu(2)==cpu(0));/* delay 00296704 */ set(4,cpu(2));if(taken){goto L_00296710;}}
/* 00296708: jal 0x002bf688 */ set(31,0x00296710u);/* delay 0029670c */ body_002bf688();
L_00296710:;
/* 00296710: jal 0x002a8bd8 */ set(31,0x00296718u);/* delay 00296714 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));ps2BattleActionModel_002A8BD8(cpu(4));
/* 00296718: jal 0x002a8bd8 */ set(31,0x00296720u);/* delay 0029671c */ set(4,cpu(16));ps2BattleActionModel_002A8BD8(cpu(4));
/* 00296720: move v0,zero */ set(2,cpu(0));
L_00296724:;
/* 00296724: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296728: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0029672c: jr ra */ {uint64_t target=cpu(31);/* delay 00296730 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002966C0(uint64_t a0){set(4,a0);body_002966c0();return cpu(2);}
static void body_00296738(void){
nocturneEffectAxisNoteEntry(0x00296738u);
uint64_t incoming=cpu(31);
/* 00296738: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0029673c: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00296740: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296744: move s2,a0 */ set(18,cpu(4));
/* 00296748: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029674c: move s0,a3 */ set(16,cpu(7));
/* 00296750: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296754: move s1,t0 */ set(17,cpu(8));
/* 00296758: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0029675c: addiu s3,v0,0x5618 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00296760: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296764: move a0,a2 */ set(4,cpu(6));
/* 00296768: jal 0x002bfd60 */ set(31,0x00296770u);/* delay 0029676c */ sb(ea(18,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(5));body_002bfd60();
/* 00296770: sw s0,0x18(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(16));
/* 00296774: sw v0,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 00296778: sw s1,0x1c(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(17));
/* 0029677c: jal 0x002dbee0 */ set(31,0x00296784u);/* delay 00296780 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 00296784: lw v0,0xc(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 00296788: bnel v0,zero,0x002967a0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0029678c */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(18));goto L_002967a0;}}
/* 00296790: sw s2,0x8(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));
/* 00296794: b 0x002967a4 */ /* delay 00296798 */ set(16,sx(UINT32_C(0x00000001)));goto L_002967a4;
L_002967a0:;
/* 002967a0: move s0,zero */ set(16,cpu(0));
L_002967a4:;
/* 002967a4: lw a0,0x0(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 002967a8: jal 0x002dbec0 */ set(31,0x002967b0u);/* delay 002967ac */ sw(ea(19,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(18));body_002dbec0();
/* 002967b0: beq s0,zero,0x002967d0 */ {int taken=(cpu(16)==cpu(0));/* delay 002967b4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002967d0;}}
/* 002967b8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002967bc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002967c0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002967c4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002967c8: j 0x00297460 */ /* delay 002967cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_00297460();return;
L_002967d0:;
/* 002967d0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002967d4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002967d8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002967dc: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002967e0: jr ra */ {uint64_t target=cpu(31);/* delay 002967e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_00296738(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);body_00296738();}
static void body_002967e8(void){
nocturneEffectAxisNoteEntry(0x002967e8u);
uint64_t incoming=cpu(31);
/* 002967e8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002967ec: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 002967f0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002967f4: move s0,a0 */ set(16,cpu(4));
/* 002967f8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002967fc: addiu s1,v0,0x5618 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00296800: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296804: jal 0x002dbee0 */ set(31,0x0029680cu);/* delay 00296808 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 0029680c: move a0,zero */ set(4,cpu(0));
/* 00296810: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 00296814: addiu v1,s1,0x24 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000024)));
L_00296818:;
/* 00296818: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0029681c: beql v0,s0,0x00296824 */ {int taken=(cpu(2)==cpu(16));if(taken){/* delay 00296820 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));goto L_00296824;}}
L_00296824:;
/* 00296824: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00296828: nop  */ 
/* 0029682c: nop  */ 
/* 00296830: nop  */ 
/* 00296834: bne a0,a1,0x00296818 */ {int taken=(cpu(4)!=cpu(5));/* delay 00296838 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));if(taken){goto L_00296818;}}
/* 0029683c: lw v0,0x8(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 00296840: b 0x0029684c */ /* delay 00296844 */ set(4,cpu(0));goto L_0029684c;
L_00296848:;
/* 00296848: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
L_0029684c:;
/* 0029684c: beql v0,zero,0x00296890 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00296850 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));goto L_00296890;}}
/* 00296854: nop  */ 
/* 00296858: nop  */ 
/* 0029685c: nop  */ 
/* 00296860: nop  */ 
/* 00296864: bnel v0,s0,0x00296848 */ {int taken=(cpu(2)!=cpu(16));if(taken){/* delay 00296868 */ set(4,cpu(2));goto L_00296848;}}
/* 0029686c: lw v1,0x4(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 00296870: bne v1,zero,0x00296880 */ {int taken=(cpu(3)!=cpu(0));/* delay 00296874 */ if(taken){goto L_00296880;}}
/* 00296878: sw a0,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
/* 0029687c: lw v1,0x4(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000004)));
L_00296880:;
/* 00296880: beql a0,zero,0x0029688c */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00296884 */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));goto L_0029688c;}}
/* 00296888: sw v1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
L_0029688c:;
/* 0029688c: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
L_00296890:;
/* 00296890: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296894: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296898: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0029689c: j 0x002dbec0 */ /* delay 002968a0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002dbec0();return;
}
uint64_t ps2BattleActionRequest_002967E8(uint64_t a0){set(4,a0);body_002967e8();return cpu(2);}
static void body_002968a8(void){
nocturneEffectAxisNoteEntry(0x002968a8u);
uint64_t incoming=cpu(31);
/* 002968a8: lw v0,0x18(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002968ac: sw v0,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002968b0: jr ra */ {uint64_t target=cpu(31);/* delay 002968b4 */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_002968A8(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_002968a8();}
static void body_002968b8(void){
nocturneEffectAxisNoteEntry(0x002968b8u);
uint64_t incoming=cpu(31);
/* 002968b8: addiu a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000018)));
/* 002968bc: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002968c0: beql v0,a1,0x002968f0 */ {int taken=(cpu(2)==cpu(5));if(taken){/* delay 002968c4 */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));goto L_002968f0;}}
/* 002968c8: addiu a0,v0,0x4 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 002968cc: nop  */ 
L_002968d0:;
/* 002968d0: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002968d4: nop  */ 
/* 002968d8: nop  */ 
/* 002968dc: nop  */ 
/* 002968e0: nop  */ 
/* 002968e4: bnel v0,a1,0x002968d0 */ {int taken=(cpu(2)!=cpu(5));if(taken){/* delay 002968e8 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));goto L_002968d0;}}
/* 002968ec: lw v0,0x4(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));
L_002968f0:;
/* 002968f0: jr ra */ {uint64_t target=cpu(31);/* delay 002968f4 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_002968B8(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_002968b8();}
static void body_002968f8(void){
nocturneEffectAxisNoteEntry(0x002968f8u);
uint64_t incoming=cpu(31);
/* 002968f8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002968fc: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00296900: move s6,a0 */ set(22,cpu(4));
/* 00296904: li a0,0x70 */ set(4,sx(UINT32_C(0x00000070)));
/* 00296908: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029690c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296910: move s1,a2 */ set(17,cpu(6));
/* 00296914: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296918: move s2,a1 */ set(18,cpu(5));
/* 0029691c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296920: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296924: move s4,a3 */ set(20,cpu(7));
/* 00296928: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0029692c: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00296930: jal 0x002a8ba8 */ set(31,0x00296938u);/* delay 00296934 */ set(21,cpu(8));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 00296938: move s3,v0 */ set(19,cpu(2));
/* 0029693c: move a1,s1 */ set(5,cpu(17));
/* 00296940: addiu s0,s3,0x30 */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0x00000030)));
/* 00296944: jal 0x002c6030 */ set(31,0x0029694cu);/* delay 00296948 */ set(4,cpu(16));ps2BattleActionPac_002C6030(cpu(4),cpu(5));
/* 0029694c: beq s2,zero,0x0029695c */ {int taken=(cpu(18)==cpu(0));/* delay 00296950 */ set(4,cpu(16));if(taken){goto L_0029695c;}}
/* 00296954: jal 0x002c6098 */ set(31,0x0029695cu);/* delay 00296958 */ ps2BattleActionPac_002C6098(cpu(4));
L_0029695c:;
/* 0029695c: move a2,s6 */ set(6,cpu(22));
/* 00296960: move a3,s4 */ set(7,cpu(20));
/* 00296964: move t0,s5 */ set(8,cpu(21));
/* 00296968: move a0,s3 */ set(4,cpu(19));
/* 0029696c: jal 0x00296738 */ set(31,0x00296974u);/* delay 00296970 */ set(5,sx(UINT32_C(0x00000001)));body_00296738();
/* 00296974: move v0,s3 */ set(2,cpu(19));
/* 00296978: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029697c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296980: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296984: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296988: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0029698c: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00296990: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00296994: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00296998: jr ra */ {uint64_t target=cpu(31);/* delay 0029699c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002968F8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);body_002968f8();return cpu(2);}
static void body_002969a0(void){
nocturneEffectAxisNoteEntry(0x002969a0u);
uint64_t incoming=cpu(31);
/* 002969a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002969a4: move a1,zero */ set(5,cpu(0));
/* 002969a8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002969ac: move a2,zero */ set(6,cpu(0));
/* 002969b0: move a3,zero */ set(7,cpu(0));
/* 002969b4: move t0,zero */ set(8,cpu(0));
/* 002969b8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002969bc: j 0x002968f8 */ /* delay 002969c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002968f8();return;
}
uint64_t ps2BattleActionRequest_002969A0(uint64_t a0){set(4,a0);body_002969a0();return cpu(2);}
static void body_002969c8(void){
nocturneEffectAxisNoteEntry(0x002969c8u);
uint64_t incoming=cpu(31);
/* 002969c8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002969cc: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002969d0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002969d4: move a2,zero */ set(6,cpu(0));
/* 002969d8: move a3,zero */ set(7,cpu(0));
/* 002969dc: move t0,zero */ set(8,cpu(0));
/* 002969e0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002969e4: j 0x002968f8 */ /* delay 002969e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002968f8();return;
}
uint64_t ps2BattleActionRequest_002969C8(uint64_t a0){set(4,a0);body_002969c8();return cpu(2);}
static void body_002969f0(void){
nocturneEffectAxisNoteEntry(0x002969f0u);
uint64_t incoming=cpu(31);
/* 002969f0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002969f4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002969f8: move s4,a0 */ set(20,cpu(4));
/* 002969fc: li a0,0x30 */ set(4,sx(UINT32_C(0x00000030)));
/* 00296a00: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296a04: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296a08: move s1,a1 */ set(17,cpu(5));
/* 00296a0c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296a10: move s2,a2 */ set(18,cpu(6));
/* 00296a14: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296a18: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00296a1c: jal 0x002a8ba8 */ set(31,0x00296a24u);/* delay 00296a20 */ set(19,cpu(7));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 00296a24: move s0,v0 */ set(16,cpu(2));
/* 00296a28: move a2,s4 */ set(6,cpu(20));
/* 00296a2c: sb s1,0x3(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(17));
/* 00296a30: move a3,s2 */ set(7,cpu(18));
/* 00296a34: move t0,s3 */ set(8,cpu(19));
/* 00296a38: move a0,s0 */ set(4,cpu(16));
/* 00296a3c: jal 0x00296738 */ set(31,0x00296a44u);/* delay 00296a40 */ set(5,cpu(0));body_00296738();
/* 00296a44: move v0,s0 */ set(2,cpu(16));
/* 00296a48: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296a4c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296a50: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296a54: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296a58: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296a5c: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00296a60: jr ra */ {uint64_t target=cpu(31);/* delay 00296a64 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002969F0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){set(4,a0);set(5,a1);set(6,a2);set(7,a3);body_002969f0();return cpu(2);}
static void body_00296a68(void){
nocturneEffectAxisNoteEntry(0x00296a68u);
uint64_t incoming=cpu(31);
/* 00296a68: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00296a6c: move a1,zero */ set(5,cpu(0));
/* 00296a70: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296a74: move a2,zero */ set(6,cpu(0));
/* 00296a78: move a3,zero */ set(7,cpu(0));
/* 00296a7c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296a80: j 0x002969f0 */ /* delay 00296a84 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002969f0();return;
}
uint64_t ps2BattleActionRequest_00296A68(uint64_t a0){set(4,a0);body_00296a68();return cpu(2);}
static void body_00296a88(void){
nocturneEffectAxisNoteEntry(0x00296a88u);
uint64_t incoming=cpu(31);
/* 00296a88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00296a8c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00296a90: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296a94: move a2,zero */ set(6,cpu(0));
/* 00296a98: move a3,zero */ set(7,cpu(0));
/* 00296a9c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296aa0: j 0x002969f0 */ /* delay 00296aa4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002969f0();return;
}
uint64_t ps2BattleActionRequest_00296A88(uint64_t a0){set(4,a0);body_00296a88();return cpu(2);}
static void body_00296aa8(void){
nocturneEffectAxisNoteEntry(0x00296aa8u);
uint64_t incoming=cpu(31);
/* 00296aa8: jr ra */ {uint64_t target=cpu(31);/* delay 00296aac */ lw(2,ea(4,(int32_t)UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296AA8(uint64_t a0){set(4,a0);body_00296aa8();return cpu(2);}
static void body_00296ab0(void){
nocturneEffectAxisNoteEntry(0x00296ab0u);
uint64_t incoming=cpu(31);
/* 00296ab0: jr ra */ {uint64_t target=cpu(31);/* delay 00296ab4 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000024)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296AB0(uint64_t a0){set(4,a0);body_00296ab0();return cpu(2);}
static void body_00296ab8(void){
nocturneEffectAxisNoteEntry(0x00296ab8u);
uint64_t incoming=cpu(31);
/* 00296ab8: jr ra */ {uint64_t target=cpu(31);/* delay 00296abc */ lw(2,ea(4,(int32_t)UINT32_C(0x00000014)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296AB8(uint64_t a0){set(4,a0);body_00296ab8();return cpu(2);}
static void body_00296ac8(void){
nocturneEffectAxisNoteEntry(0x00296ac8u);
uint64_t incoming=cpu(31);
/* 00296ac8: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00296acc: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00296ad0: bnel v0,v1,0x00296af8 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 00296ad4 */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000001))));goto L_00296af8;}}
/* 00296ad8: lhu v0,0x68(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000068))));
/* 00296adc: beq v0,zero,0x00296af0 */ {int taken=(cpu(2)==cpu(0));/* delay 00296ae0 */ set(3,cpu(0));if(taken){goto L_00296af0;}}
/* 00296ae4: lbu v0,0x1(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 00296ae8: xori v0,v0,0x6 */ set(2,cpu(2)^UINT32_C(0x00000006));
/* 00296aec: sltiu v1,v0,0x1 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_00296af0:;
/* 00296af0: jr ra */ {uint64_t target=cpu(31);/* delay 00296af4 */ set(2,cpu(3));checkReturn(target,incoming);return;}
L_00296af8:;
/* 00296af8: xori v0,v0,0x6 */ set(2,cpu(2)^UINT32_C(0x00000006));
/* 00296afc: jr ra */ {uint64_t target=cpu(31);/* delay 00296b00 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296AC8(uint64_t a0){set(4,a0);body_00296ac8();return cpu(2);}
static void body_00296b08(void){
nocturneEffectAxisNoteEntry(0x00296b08u);
uint64_t incoming=cpu(31);
/* 00296b08: lhu v0,0x68(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000068))));
/* 00296b0c: beq v0,zero,0x00296b20 */ {int taken=(cpu(2)==cpu(0));/* delay 00296b10 */ set(3,cpu(0));if(taken){goto L_00296b20;}}
/* 00296b14: lbu v0,0x1(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 00296b18: xori v0,v0,0x6 */ set(2,cpu(2)^UINT32_C(0x00000006));
/* 00296b1c: sltiu v1,v0,0x1 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_00296b20:;
/* 00296b20: jr ra */ {uint64_t target=cpu(31);/* delay 00296b24 */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296B08(uint64_t a0){set(4,a0);body_00296b08();return cpu(2);}
static void body_00296b28(void){
nocturneEffectAxisNoteEntry(0x00296b28u);
uint64_t incoming=cpu(31);
/* 00296b28: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00296b2c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296b30: move s0,a0 */ set(16,cpu(4));
/* 00296b34: b 0x00296b50 */ /* delay 00296b38 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));goto L_00296b50;
L_00296b40:;
/* 00296b40: jal 0x002bf898 */ set(31,0x00296b48u);/* delay 00296b44 */ body_002bf898();
/* 00296b48: jal 0x002976c0 */ set(31,0x00296b50u);/* delay 00296b4c */ body_002976c0();
L_00296b50:;
/* 00296b50: jal 0x00296ac8 */ set(31,0x00296b58u);/* delay 00296b54 */ set(4,cpu(16));body_00296ac8();
/* 00296b58: beq v0,zero,0x00296b40 */ {int taken=(cpu(2)==cpu(0));/* delay 00296b5c */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_00296b40;}}
/* 00296b60: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296b64: jr ra */ {uint64_t target=cpu(31);/* delay 00296b68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296B28(uint64_t a0){set(4,a0);body_00296b28();return cpu(2);}
static void body_00296b70(void){
nocturneEffectAxisNoteEntry(0x00296b70u);
uint64_t incoming=cpu(31);
/* 00296b70: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00296b74: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296b78: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296b7c: j 0x00296b28 */ /* delay 00296b80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00296b28();return;
}
uint64_t ps2BattleActionRequest_00296B70(uint64_t a0){set(4,a0);body_00296b70();return cpu(2);}
static void body_00296b88(void){
nocturneEffectAxisNoteEntry(0x00296b88u);
uint64_t incoming=cpu(31);
/* 00296b88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00296b8c: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00296b90: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296b94: addiu s0,v0,0x5618 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00296b98: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00296b9c: b 0x00296bb4 */ /* delay 00296ba0 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));goto L_00296bb4;
L_00296ba8:;
/* 00296ba8: jal 0x002976c0 */ set(31,0x00296bb0u);/* delay 00296bac */ body_002976c0();
/* 00296bb0: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
L_00296bb4:;
/* 00296bb4: bne v1,zero,0x00296ba8 */ {int taken=(cpu(3)!=cpu(0));/* delay 00296bb8 */ if(taken){goto L_00296ba8;}}
/* 00296bbc: lw v0,0x18(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 00296bc0: bne v0,zero,0x00296ba8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00296bc4 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_00296ba8;}}
/* 00296bc8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296bcc: jr ra */ {uint64_t target=cpu(31);/* delay 00296bd0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_00296B88(void){body_00296b88();}
static void body_00296bd8(void){
nocturneEffectAxisNoteEntry(0x00296bd8u);
uint64_t incoming=cpu(31);
/* 00296bd8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00296bdc: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00296be0: move s5,a0 */ set(21,cpu(4));
/* 00296be4: li a0,0x30 */ set(4,sx(UINT32_C(0x00000030)));
/* 00296be8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296bec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296bf0: move s1,a1 */ set(17,cpu(5));
/* 00296bf4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296bf8: move s2,a2 */ set(18,cpu(6));
/* 00296bfc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296c00: move s3,a3 */ set(19,cpu(7));
/* 00296c04: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296c08: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00296c0c: jal 0x002a8ba8 */ set(31,0x00296c14u);/* delay 00296c10 */ set(20,cpu(8));set(2,ps2EffectPoolAllocateZeroed_002A8BA8(cpu(4)));
/* 00296c14: move s0,v0 */ set(16,cpu(2));
/* 00296c18: move a2,s5 */ set(6,cpu(21));
/* 00296c1c: sw s1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(17));
/* 00296c20: move a3,s3 */ set(7,cpu(19));
/* 00296c24: sw s2,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 00296c28: move t0,s4 */ set(8,cpu(20));
/* 00296c2c: sw s1,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(17));
/* 00296c30: move a0,s0 */ set(4,cpu(16));
/* 00296c34: sw s2,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 00296c38: jal 0x00296738 */ set(31,0x00296c40u);/* delay 00296c3c */ set(5,sx(UINT32_C(0x00000002)));body_00296738();
/* 00296c40: move v0,s0 */ set(2,cpu(16));
/* 00296c44: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296c48: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296c4c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296c50: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296c54: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296c58: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00296c5c: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00296c60: jr ra */ {uint64_t target=cpu(31);/* delay 00296c64 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296BD8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);body_00296bd8();return cpu(2);}
static void body_00296c68(void){
nocturneEffectAxisNoteEntry(0x00296c68u);
uint64_t incoming=cpu(31);
/* 00296c68: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00296c6c: move a3,zero */ set(7,cpu(0));
/* 00296c70: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296c74: move t0,zero */ set(8,cpu(0));
/* 00296c78: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296c7c: j 0x00296bd8 */ /* delay 00296c80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00296bd8();return;
}
uint64_t ps2BattleActionRequest_00296C68(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_00296c68();return cpu(2);}
static void body_00296c88(void){
nocturneEffectAxisNoteEntry(0x00296c88u);
uint64_t incoming=cpu(31);
/* 00296c88: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00296c8c: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00296c90: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296c94: addiu s1,v0,0x5618 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00296c98: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296c9c: move s3,a0 */ set(19,cpu(4));
/* 00296ca0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296ca4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296ca8: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296cac: jal 0x002dbee0 */ set(31,0x00296cb4u);/* delay 00296cb0 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 00296cb4: lbu v0,0x7(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000007))));
/* 00296cb8: bne v0,zero,0x00296ce0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00296cbc */ set(3,sx(UINT32_C(0x00000003)));if(taken){goto L_00296ce0;}}
/* 00296cc0: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00296cc4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296cc8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296ccc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296cd0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296cd4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296cd8: j 0x002dbec0 */ /* delay 00296cdc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_002dbec0();return;
L_00296ce0:;
/* 00296ce0: lbu a0,0x1(s3) */ set(4,byte(ea(19,(int32_t)UINT32_C(0x00000001))));
/* 00296ce4: beq a0,v1,0x00296d08 */ {int taken=(cpu(4)==cpu(3));/* delay 00296ce8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00296d08;}}
/* 00296cec: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00296cf0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296cf4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296cf8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296cfc: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296d00: j 0x002dbec0 */ /* delay 00296d04 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_002dbec0();return;
L_00296d08:;
/* 00296d08: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 00296d0c: sb v0,0x1(s3) */ sb(ea(19,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
/* 00296d10: lbu s2,0x5(s1) */ set(18,byte(ea(17,(int32_t)UINT32_C(0x00000005))));
/* 00296d14: sll v0,s2,0x3 */ set(2,sx((uint32_t)cpu(18)<<3));
/* 00296d18: addiu v1,s2,0x1 */ set(3,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 00296d1c: bne s2,a0,0x00296d30 */ {int taken=(cpu(18)!=cpu(4));/* delay 00296d20 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));if(taken){goto L_00296d30;}}
/* 00296d24: b 0x00296d34 */ /* delay 00296d28 */ sb(ea(17,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(0));goto L_00296d34;
L_00296d30:;
/* 00296d30: sb v1,0x5(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(3));
L_00296d34:;
/* 00296d34: sh s2,0x6a(s3) */ sh(ea(19,(int32_t)UINT32_C(0x0000006a)),(uint16_t)cpu(18));
/* 00296d38: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 00296d3c: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00296d40: lbu v0,0x7(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000007))));
/* 00296d44: addiu v0,v0,0xff */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000ff)));
/* 00296d48: sb v0,0x7(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000007)),(uint8_t)cpu(2));
/* 00296d4c: sw s3,0x24(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(19));
/* 00296d50: lw s0,0x10(s3) */ lw(16,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 00296d54: slt v0,v1,s0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(16));
/* 00296d58: jal 0x002dbec0 */ set(31,0x00296d60u);/* delay 00296d5c */ if(cpu(2)!=0){set(16,cpu(3));}body_002dbec0();
/* 00296d60: lw v1,0x1c(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 00296d64: sll a1,s2,0x10 */ set(5,sx((uint32_t)cpu(18)<<16));
/* 00296d68: lw a0,0xc(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 00296d6c: move a2,s0 */ set(6,cpu(16));
/* 00296d70: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296d74: addu a1,v1,a1 */ set(5,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00296d78: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296d7c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296d80: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296d84: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296d88: j 0x002bf548 */ /* delay 00296d8c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);set(2,ps2FileCommandRead(cpu(4),cpu(5),cpu(6)));return;
}
uint64_t ps2BattleActionRequest_00296C88(uint64_t a0){set(4,a0);body_00296c88();return cpu(2);}
static void body_00296d90(void){
nocturneEffectAxisNoteEntry(0x00296d90u);
uint64_t incoming=cpu(31);
/* 00296d90: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00296d94: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00296d98: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296d9c: move s1,a1 */ set(17,cpu(5));
/* 00296da0: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 00296da4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296da8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296dac: move s2,a3 */ set(18,cpu(7));
/* 00296db0: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296db4: addiu s3,v0,0x5618 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00296db8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296dbc: move s4,a0 */ set(20,cpu(4));
/* 00296dc0: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00296dc4: beq s1,v1,0x00296e18 */ {int taken=(cpu(17)==cpu(3));/* delay 00296dc8 */ set(16,cpu(8));if(taken){goto L_00296e18;}}
/* 00296dcc: slti v0,s1,0x5 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000005));
/* 00296dd0: beq v0,zero,0x00296df0 */ {int taken=(cpu(2)==cpu(0));/* delay 00296dd4 */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_00296df0;}}
/* 00296dd8: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00296ddc: beql s1,v0,0x00296e08 */ {int taken=(cpu(17)==cpu(2));if(taken){/* delay 00296de0 */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));goto L_00296e08;}}
/* 00296de4: b 0x00296f2c */ /* delay 00296de8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00296f2c;
L_00296df0:;
/* 00296df0: beq s1,v0,0x00296e38 */ {int taken=(cpu(17)==cpu(2));/* delay 00296df4 */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_00296e38;}}
/* 00296df8: beq s1,v0,0x00296ef8 */ {int taken=(cpu(17)==cpu(2));/* delay 00296dfc */ if(taken){goto L_00296ef8;}}
/* 00296e00: b 0x00296f2c */ /* delay 00296e04 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00296f2c;
L_00296e08:;
/* 00296e08: jal 0x002bf4f0 */ set(31,0x00296e10u);/* delay 00296e0c */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(20));set(2,ps2FileCommandSize(cpu(4)));
/* 00296e10: b 0x00296f2c */ /* delay 00296e14 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00296f2c;
L_00296e18:;
/* 00296e18: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 00296e1c: sw s2,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 00296e20: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
/* 00296e24: move a0,s0 */ set(4,cpu(16));
/* 00296e28: jal 0x00296c88 */ set(31,0x00296e30u);/* delay 00296e2c */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));body_00296c88();
/* 00296e30: b 0x00296f2c */ /* delay 00296e34 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00296f2c;
L_00296e38:;
/* 00296e38: jal 0x002dbee0 */ set(31,0x00296e40u);/* delay 00296e3c */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 00296e40: lhu v1,0x68(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000068))));
/* 00296e44: beql v1,zero,0x00296e58 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00296e48 */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000006a))));goto L_00296e58;}}
/* 00296e4c: b 0x00296e98 */ /* delay 00296e50 */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));goto L_00296e98;
L_00296e58:;
/* 00296e58: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00296e5c: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 00296e60: sw s2,0x20(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(18));
/* 00296e64: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 00296e68: subu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(18)));
/* 00296e6c: bne v1,zero,0x00296e90 */ {int taken=(cpu(3)!=cpu(0));/* delay 00296e70 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));if(taken){goto L_00296e90;}}
/* 00296e74: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00296e78: sb s1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));
/* 00296e7c: bne v0,zero,0x00296e98 */ {int taken=(cpu(2)!=cpu(0));/* delay 00296e80 */ sw(ea(19,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_00296e98;}}
/* 00296e84: b 0x00296e98 */ /* delay 00296e88 */ sw(ea(19,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));goto L_00296e98;
L_00296e90:;
/* 00296e90: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 00296e94: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
L_00296e98:;
/* 00296e98: lbu v0,0x6(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000006))));
/* 00296e9c: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 00296ea0: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00296ea4: sb v0,0x6(s3) */ sb(ea(19,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(2));
/* 00296ea8: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00296eac: bne v1,a0,0x00296ed8 */ {int taken=(cpu(3)!=cpu(4));/* delay 00296eb0 */ set(5,cpu(16));if(taken){goto L_00296ed8;}}
/* 00296eb4: jal 0x002968a8 */ set(31,0x00296ebcu);/* delay 00296eb8 */ set(4,cpu(19));body_002968a8();
/* 00296ebc: jal 0x002dbec0 */ set(31,0x00296ec4u);/* delay 00296ec0 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00296ec4: jal 0x002bf638 */ set(31,0x00296eccu);/* delay 00296ec8 */ set(4,cpu(20));set(2,ps2FileCommandClose(cpu(4)));
/* 00296ecc: b 0x00296ee4 */ /* delay 00296ed0 */ lw(16,ea(28,(int32_t)UINT32_C(0xffffd4d8)));goto L_00296ee4;
L_00296ed8:;
/* 00296ed8: jal 0x002dbec0 */ set(31,0x00296ee0u);/* delay 00296edc */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00296ee0: lw s0,-0x2b28(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffd4d8)));
L_00296ee4:;
/* 00296ee4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00296ee8: jal 0x00297460 */ set(31,0x00296ef0u);/* delay 00296eec */ sw(ea(28,(int32_t)UINT32_C(0xffffd4d8)),(uint32_t)cpu(2));body_00297460();
/* 00296ef0: b 0x00296f28 */ /* delay 00296ef4 */ sw(ea(28,(int32_t)UINT32_C(0xffffd4d8)),(uint32_t)cpu(16));goto L_00296f28;
L_00296ef8:;
/* 00296ef8: jal 0x002dbee0 */ set(31,0x00296f00u);/* delay 00296efc */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 00296f00: move a0,s3 */ set(4,cpu(19));
/* 00296f04: jal 0x002968b8 */ set(31,0x00296f0cu);/* delay 00296f08 */ set(5,cpu(16));body_002968b8();
/* 00296f0c: jal 0x002dbec0 */ set(31,0x00296f14u);/* delay 00296f10 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00296f14: jal 0x002bf688 */ set(31,0x00296f1cu);/* delay 00296f18 */ set(4,cpu(20));body_002bf688();
/* 00296f1c: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 00296f20: li v0,0x6 */ set(2,sx(UINT32_C(0x00000006)));
/* 00296f24: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
L_00296f28:;
/* 00296f28: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00296f2c:;
/* 00296f2c: move v0,zero */ set(2,cpu(0));
/* 00296f30: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296f34: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296f38: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296f3c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00296f40: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00296f44: jr ra */ {uint64_t target=cpu(31);/* delay 00296f48 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296D90(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);body_00296d90();return cpu(2);}
static void body_00296f50(void){
nocturneEffectAxisNoteEntry(0x00296f50u);
uint64_t incoming=cpu(31);
/* 00296f50: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00296f54: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00296f58: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296f5c: move s0,a0 */ set(16,cpu(4));
/* 00296f60: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296f64: addiu s1,v0,0x5618 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00296f68: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296f6c: jal 0x002dbee0 */ set(31,0x00296f74u);/* delay 00296f70 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 00296f74: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00296f78: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 00296f7c: beq v1,v0,0x00296f98 */ {int taken=(cpu(3)==cpu(2));/* delay 00296f80 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_00296f98;}}
/* 00296f84: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00296f88: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296f8c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296f90: j 0x002dbec0 */ /* delay 00296f94 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002dbec0();return;
L_00296f98:;
/* 00296f98: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 00296f9c: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
/* 00296fa0: jal 0x002dbec0 */ set(31,0x00296fa8u);/* delay 00296fa4 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00296fa8: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 00296fac: ori a2,zero,0x8000 */ set(6,cpu(0)|UINT32_C(0x00008000));
/* 00296fb0: lw a1,0x28(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 00296fb4: slt v0,a2,v1 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(3));
/* 00296fb8: lw a0,0xc(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 00296fbc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296fc0: movz a2,v1,v0 */ if(cpu(2)==0){set(6,cpu(3));}
/* 00296fc4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296fc8: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296fcc: j 0x002bf548 */ /* delay 00296fd0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);set(2,ps2FileCommandRead(cpu(4),cpu(5),cpu(6)));return;
}
uint64_t ps2BattleActionRequest_00296F50(uint64_t a0){set(4,a0);body_00296f50();return cpu(2);}
static void body_00296fd8(void){
nocturneEffectAxisNoteEntry(0x00296fd8u);
uint64_t incoming=cpu(31);
/* 00296fd8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00296fdc: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00296fe0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00296fe4: move s1,a1 */ set(17,cpu(5));
/* 00296fe8: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 00296fec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00296ff0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00296ff4: move s2,a3 */ set(18,cpu(7));
/* 00296ff8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00296ffc: addiu s3,v0,0x5618 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00297000: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00297004: move s4,a0 */ set(20,cpu(4));
/* 00297008: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0029700c: beq s1,v1,0x00297060 */ {int taken=(cpu(17)==cpu(3));/* delay 00297010 */ set(16,cpu(8));if(taken){goto L_00297060;}}
/* 00297014: slti v0,s1,0x5 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000005));
/* 00297018: beq v0,zero,0x00297038 */ {int taken=(cpu(2)==cpu(0));/* delay 0029701c */ set(2,sx(UINT32_C(0x00000005)));if(taken){goto L_00297038;}}
/* 00297020: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00297024: beql s1,v0,0x00297050 */ {int taken=(cpu(17)==cpu(2));if(taken){/* delay 00297028 */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));goto L_00297050;}}
/* 0029702c: b 0x002971f4 */ /* delay 00297030 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002971f4;
L_00297038:;
/* 00297038: beq s1,v0,0x002970d0 */ {int taken=(cpu(17)==cpu(2));/* delay 0029703c */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_002970d0;}}
/* 00297040: beq s1,v0,0x00297180 */ {int taken=(cpu(17)==cpu(2));/* delay 00297044 */ if(taken){goto L_00297180;}}
/* 00297048: b 0x002971f4 */ /* delay 0029704c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002971f4;
L_00297050:;
/* 00297050: jal 0x002bf4f0 */ set(31,0x00297058u);/* delay 00297054 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(20));set(2,ps2FileCommandSize(cpu(4)));
/* 00297058: b 0x002971f4 */ /* delay 0029705c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002971f4;
L_00297060:;
/* 00297060: lbu v0,0x3(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000003))));
/* 00297064: sw s2,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 00297068: bne v0,zero,0x00297098 */ {int taken=(cpu(2)!=cpu(0));/* delay 0029706c */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));if(taken){goto L_00297098;}}
/* 00297070: jal 0x002a9288 */ set(31,0x00297078u);/* delay 00297074 */ set(4,cpu(18));set(2,ps2MemoryHandleTryAllocate(cpu(4)));
/* 00297078: bne v0,zero,0x002970a4 */ {int taken=(cpu(2)!=cpu(0));/* delay 0029707c */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));if(taken){goto L_002970a4;}}
/* 00297080: li v1,0xa */ set(3,sx(UINT32_C(0x0000000a)));
/* 00297084: li v0,0x7 */ set(2,sx(UINT32_C(0x00000007)));
/* 00297088: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
/* 0029708c: b 0x002971f0 */ /* delay 00297090 */ sb(ea(16,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(3));goto L_002971f0;
L_00297098:;
/* 00297098: jal 0x002a9158 */ set(31,0x002970a0u);/* delay 0029709c */ set(4,cpu(18));set(2,ps2BattleActionModel_002A9158(cpu(4)));
/* 002970a0: sw v0,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
L_002970a4:;
/* 002970a4: jal 0x002a9688 */ set(31,0x002970acu);/* delay 002970a8 */ set(4,cpu(2));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 002970ac: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 002970b0: sw v0,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
/* 002970b4: move a0,s0 */ set(4,cpu(16));
/* 002970b8: sb v1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(3));
/* 002970bc: jal 0x00296f50 */ set(31,0x002970c4u);/* delay 002970c0 */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));body_00296f50();
/* 002970c4: b 0x002971f4 */ /* delay 002970c8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002971f4;
L_002970d0:;
/* 002970d0: jal 0x002dbee0 */ set(31,0x002970d8u);/* delay 002970d4 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 002970d8: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002970dc: subu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(18)));
/* 002970e0: bne v1,zero,0x00297110 */ {int taken=(cpu(3)!=cpu(0));/* delay 002970e4 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));if(taken){goto L_00297110;}}
/* 002970e8: sb s1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));
/* 002970ec: lw v0,0x8(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 002970f0: bnel v0,s0,0x00297128 */ {int taken=(cpu(2)!=cpu(16));if(taken){/* delay 002970f4 */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));goto L_00297128;}}
/* 002970f8: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002970fc: bne v0,zero,0x00297124 */ {int taken=(cpu(2)!=cpu(0));/* delay 00297100 */ sw(ea(19,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_00297124;}}
/* 00297104: b 0x00297124 */ /* delay 00297108 */ sw(ea(19,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));goto L_00297124;
L_00297110:;
/* 00297110: lw v0,0x28(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 00297114: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 00297118: sb v1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(3));
/* 0029711c: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00297120: sw v0,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));
L_00297124:;
/* 00297124: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
L_00297128:;
/* 00297128: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 0029712c: bne v1,v0,0x00297168 */ {int taken=(cpu(3)!=cpu(2));/* delay 00297130 */ set(5,cpu(16));if(taken){goto L_00297168;}}
/* 00297134: jal 0x002968a8 */ set(31,0x0029713cu);/* delay 00297138 */ set(4,cpu(19));body_002968a8();
/* 0029713c: jal 0x002dbec0 */ set(31,0x00297144u);/* delay 00297140 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00297144: jal 0x002bf638 */ set(31,0x0029714cu);/* delay 00297148 */ set(4,cpu(20));set(2,ps2FileCommandClose(cpu(4)));
/* 0029714c: lw s0,-0x2b28(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffd4d8)));
/* 00297150: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00297154: jal 0x00297460 */ set(31,0x0029715cu);/* delay 00297158 */ sw(ea(28,(int32_t)UINT32_C(0xffffd4d8)),(uint32_t)cpu(2));body_00297460();
/* 0029715c: b 0x002971f0 */ /* delay 00297160 */ sw(ea(28,(int32_t)UINT32_C(0xffffd4d8)),(uint32_t)cpu(16));goto L_002971f0;
L_00297168:;
/* 00297168: jal 0x002dbec0 */ set(31,0x00297170u);/* delay 0029716c */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00297170: jal 0x00296f50 */ set(31,0x00297178u);/* delay 00297174 */ set(4,cpu(16));body_00296f50();
/* 00297178: b 0x002971f4 */ /* delay 0029717c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002971f4;
L_00297180:;
/* 00297180: jal 0x002bf688 */ set(31,0x00297188u);/* delay 00297184 */ body_002bf688();
/* 00297188: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 0029718c: li v0,0x6 */ set(2,sx(UINT32_C(0x00000006)));
/* 00297190: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
/* 00297194: jal 0x002dbee0 */ set(31,0x0029719cu);/* delay 00297198 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 0029719c: move a0,s3 */ set(4,cpu(19));
/* 002971a0: jal 0x002968b8 */ set(31,0x002971a8u);/* delay 002971a4 */ set(5,cpu(16));body_002968b8();
/* 002971a8: lw v0,0x18(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 002971ac: beq v0,zero,0x002971e8 */ {int taken=(cpu(2)==cpu(0));/* delay 002971b0 */ set(3,sx((uint32_t)cpu(19)+UINT32_C(0x00000010)));if(taken){goto L_002971e8;}}
/* 002971b4: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002971b8: beql v0,zero,0x002971e8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002971bc */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));goto L_002971e8;}}
/* 002971c0: addiu v1,v0,0x2c */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x0000002c)));
/* 002971c4: nop  */ 
L_002971c8:;
/* 002971c8: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002971cc: nop  */ 
/* 002971d0: nop  */ 
/* 002971d4: nop  */ 
/* 002971d8: nop  */ 
/* 002971dc: bnel v0,zero,0x002971c8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002971e0 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x0000002c)));goto L_002971c8;}}
/* 002971e4: sw s0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
L_002971e8:;
/* 002971e8: jal 0x002dbec0 */ set(31,0x002971f0u);/* delay 002971ec */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
L_002971f0:;
/* 002971f0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002971f4:;
/* 002971f4: move v0,zero */ set(2,cpu(0));
/* 002971f8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002971fc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297200: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00297204: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00297208: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0029720c: jr ra */ {uint64_t target=cpu(31);/* delay 00297210 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_00296FD8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);body_00296fd8();return cpu(2);}
static void body_00297218(void){
nocturneEffectAxisNoteEntry(0x00297218u);
uint64_t incoming=cpu(31);
/* 00297218: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0029721c: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00297220: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297224: move s0,a0 */ set(16,cpu(4));
/* 00297228: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0029722c: addiu s1,v0,0x5618 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00297230: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297234: jal 0x002dbee0 */ set(31,0x0029723cu);/* delay 00297238 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 0029723c: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00297240: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 00297244: beq v1,v0,0x00297260 */ {int taken=(cpu(3)==cpu(2));/* delay 00297248 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_00297260;}}
/* 0029724c: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00297250: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297254: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297258: j 0x002dbec0 */ /* delay 0029725c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002dbec0();return;
L_00297260:;
/* 00297260: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 00297264: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
/* 00297268: jal 0x002dbec0 */ set(31,0x00297270u);/* delay 0029726c */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00297270: lw v1,0x10(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 00297274: ori a2,zero,0x8000 */ set(6,cpu(0)|UINT32_C(0x00008000));
/* 00297278: lw a1,0x28(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 0029727c: slt v0,a2,v1 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(3));
/* 00297280: lw a0,0xc(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 00297284: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297288: movz a2,v1,v0 */ if(cpu(2)==0){set(6,cpu(3));}
/* 0029728c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297290: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297294: j 0x002bf5a8 */ /* delay 00297298 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);set(2,ps2FileCommandWrite(cpu(4),cpu(5),cpu(6)));return;
}
uint64_t ps2BattleActionRequest_00297218(uint64_t a0){set(4,a0);body_00297218();return cpu(2);}
static void body_002972a0(void){
nocturneEffectAxisNoteEntry(0x002972a0u);
uint64_t incoming=cpu(31);
/* 002972a0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002972a4: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 002972a8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002972ac: li s3,0x6 */ set(19,sx(UINT32_C(0x00000006)));
/* 002972b0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002972b4: move s0,t0 */ set(16,cpu(8));
/* 002972b8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002972bc: addiu s1,v0,0x5618 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 002972c0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002972c4: move s2,a3 */ set(18,cpu(7));
/* 002972c8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002972cc: move s4,a0 */ set(20,cpu(4));
/* 002972d0: beq a1,s3,0x00297320 */ {int taken=(cpu(5)==cpu(19));/* delay 002972d4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_00297320;}}
/* 002972d8: slti v0,a1,0x7 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000007));
/* 002972dc: beq v0,zero,0x002972f8 */ {int taken=(cpu(2)==cpu(0));/* delay 002972e0 */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_002972f8;}}
/* 002972e4: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002972e8: beq a1,v0,0x00297308 */ {int taken=(cpu(5)==cpu(2));/* delay 002972ec */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00297308;}}
/* 002972f0: b 0x0029743c */ /* delay 002972f4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0029743c;
L_002972f8:;
/* 002972f8: beq a1,v0,0x002973d0 */ {int taken=(cpu(5)==cpu(2));/* delay 002972fc */ if(taken){goto L_002973d0;}}
/* 00297300: b 0x0029743c */ /* delay 00297304 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0029743c;
L_00297308:;
/* 00297308: move a0,s0 */ set(4,cpu(16));
/* 0029730c: jal 0x00297218 */ set(31,0x00297314u);/* delay 00297310 */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));body_00297218();
/* 00297314: b 0x0029743c */ /* delay 00297318 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0029743c;
L_00297320:;
/* 00297320: jal 0x002dbee0 */ set(31,0x00297328u);/* delay 00297324 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 00297328: lw v1,0x28(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 0029732c: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 00297330: addu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(18)));
/* 00297334: subu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));
/* 00297338: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 0029733c: bne v0,zero,0x00297370 */ {int taken=(cpu(2)!=cpu(0));/* delay 00297340 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));if(taken){goto L_00297370;}}
/* 00297344: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 00297348: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
/* 0029734c: lw v1,0x8(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 00297350: bnel v1,s0,0x0029737c */ {int taken=(cpu(3)!=cpu(16));if(taken){/* delay 00297354 */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));goto L_0029737c;}}
/* 00297358: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0029735c: bne v0,zero,0x00297378 */ {int taken=(cpu(2)!=cpu(0));/* delay 00297360 */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_00297378;}}
/* 00297364: b 0x00297378 */ /* delay 00297368 */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));goto L_00297378;
L_00297370:;
/* 00297370: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 00297374: sb v0,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(2));
L_00297378:;
/* 00297378: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
L_0029737c:;
/* 0029737c: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 00297380: bne v1,v0,0x002973b8 */ {int taken=(cpu(3)!=cpu(2));/* delay 00297384 */ set(5,cpu(16));if(taken){goto L_002973b8;}}
/* 00297388: jal 0x002968a8 */ set(31,0x00297390u);/* delay 0029738c */ set(4,cpu(17));body_002968a8();
/* 00297390: jal 0x002dbec0 */ set(31,0x00297398u);/* delay 00297394 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00297398: jal 0x002bf638 */ set(31,0x002973a0u);/* delay 0029739c */ set(4,cpu(20));set(2,ps2FileCommandClose(cpu(4)));
/* 002973a0: lw s0,-0x2b28(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffd4d8)));
/* 002973a4: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002973a8: jal 0x00297460 */ set(31,0x002973b0u);/* delay 002973ac */ sw(ea(28,(int32_t)UINT32_C(0xffffd4d8)),(uint32_t)cpu(2));body_00297460();
/* 002973b0: b 0x00297438 */ /* delay 002973b4 */ sw(ea(28,(int32_t)UINT32_C(0xffffd4d8)),(uint32_t)cpu(16));goto L_00297438;
L_002973b8:;
/* 002973b8: jal 0x002dbec0 */ set(31,0x002973c0u);/* delay 002973bc */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 002973c0: jal 0x00297218 */ set(31,0x002973c8u);/* delay 002973c4 */ set(4,cpu(16));body_00297218();
/* 002973c8: b 0x0029743c */ /* delay 002973cc */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0029743c;
L_002973d0:;
/* 002973d0: jal 0x002bf688 */ set(31,0x002973d8u);/* delay 002973d4 */ body_002bf688();
/* 002973d8: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002973dc: sb s3,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(19));
/* 002973e0: jal 0x002dbee0 */ set(31,0x002973e8u);/* delay 002973e4 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 002973e8: move a0,s1 */ set(4,cpu(17));
/* 002973ec: jal 0x002968b8 */ set(31,0x002973f4u);/* delay 002973f0 */ set(5,cpu(16));body_002968b8();
/* 002973f4: lw v0,0x18(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 002973f8: beq v0,zero,0x00297430 */ {int taken=(cpu(2)==cpu(0));/* delay 002973fc */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));if(taken){goto L_00297430;}}
/* 00297400: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00297404: beql v0,zero,0x00297430 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00297408 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));goto L_00297430;}}
/* 0029740c: addiu v1,v0,0x2c */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x0000002c)));
L_00297410:;
/* 00297410: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00297414: nop  */ 
/* 00297418: nop  */ 
/* 0029741c: nop  */ 
/* 00297420: nop  */ 
/* 00297424: bnel v0,zero,0x00297410 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00297428 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x0000002c)));goto L_00297410;}}
/* 0029742c: sw s0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
L_00297430:;
/* 00297430: jal 0x002dbec0 */ set(31,0x00297438u);/* delay 00297434 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
L_00297438:;
/* 00297438: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0029743c:;
/* 0029743c: move v0,zero */ set(2,cpu(0));
/* 00297440: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297444: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297448: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0029744c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00297450: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00297454: jr ra */ {uint64_t target=cpu(31);/* delay 00297458 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002972A0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);body_002972a0();return cpu(2);}
static void body_00297460(void){
nocturneEffectAxisNoteEntry(0x00297460u);
uint64_t incoming=cpu(31);
/* 00297460: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00297464: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00297468: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0029746c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297470: addiu s2,v0,0x5618 */ set(18,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 00297474: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297478: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0029747c: jal 0x002dbee0 */ set(31,0x00297484u);/* delay 00297480 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 00297484: lw s0,0x8(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 00297488: bnel s0,zero,0x002974b0 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 0029748c */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000000))));goto L_002974b0;}}
/* 00297490: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00297494: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297498: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0029749c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002974a0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002974a4: j 0x002dbec0 */ /* delay 002974a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002dbec0();return;
L_002974b0:;
/* 002974b0: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
/* 002974b4: beq v1,s1,0x00297590 */ {int taken=(cpu(3)==cpu(17));/* delay 002974b8 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_00297590;}}
/* 002974bc: beql v0,zero,0x002974d8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002974c0 */ set(2,sx(UINT32_C(0x00000002)));goto L_002974d8;}}
/* 002974c4: beql v1,zero,0x002974e8 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002974c8 */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));goto L_002974e8;}}
/* 002974cc: b 0x0029762c */ /* delay 002974d0 */ goto L_0029762c;
L_002974d8:;
/* 002974d8: beql v1,v0,0x002975f8 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 002974dc */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000001))));goto L_002975f8;}}
/* 002974e0: b 0x0029762c */ /* delay 002974e4 */ goto L_0029762c;
L_002974e8:;
/* 002974e8: beq v1,zero,0x00297500 */ {int taken=(cpu(3)==cpu(0));/* delay 002974ec */ set(2,sx(UINT32_C(0x00000007)));if(taken){goto L_00297500;}}
/* 002974f0: beq v1,v0,0x00297530 */ {int taken=(cpu(3)==cpu(2));/* delay 002974f4 */ if(taken){goto L_00297530;}}
/* 002974f8: b 0x0029762c */ /* delay 002974fc */ goto L_0029762c;
L_00297500:;
/* 00297500: sb s1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));
/* 00297504: move s1,zero */ set(17,cpu(0));
/* 00297508: jal 0x002dbec0 */ set(31,0x00297510u);/* delay 0029750c */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00297510: lui a1,0x29 */ set(5,sx(UINT32_C(0x00290000)));
/* 00297514: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00297518: addiu a1,a1,0x6fd8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00006fd8)));
/* 0029751c: jal 0x002bf3a8 */ set(31,0x00297524u);/* delay 00297520 */ set(6,cpu(16));set(2,ps2FileRequestRead(cpu(4),cpu(5),cpu(6)));
/* 00297524: b 0x0029762c */ /* delay 00297528 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));goto L_0029762c;
L_00297530:;
/* 00297530: jal 0x002a9288 */ set(31,0x00297538u);/* delay 00297534 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));set(2,ps2MemoryHandleTryAllocate(cpu(4)));
/* 00297538: bne v0,zero,0x00297568 */ {int taken=(cpu(2)!=cpu(0));/* delay 0029753c */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));if(taken){goto L_00297568;}}
/* 00297540: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 00297544: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 00297548: addiu a0,a0,0x68e8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000068e8)));
/* 0029754c: jal 0x002bd550 */ set(31,0x00297554u);/* delay 00297550 */ lw(5,ea(2,(int32_t)UINT32_C(0x00000010)));body_002bd550();
/* 00297554: lbu v1,0x2(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000002))));
/* 00297558: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 0029755c: b 0x0029762c */ /* delay 00297560 */ sb(ea(16,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(3));goto L_0029762c;
L_00297568:;
/* 00297568: jal 0x002a9688 */ set(31,0x00297570u);/* delay 0029756c */ set(4,cpu(2));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 00297570: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 00297574: sw v0,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
/* 00297578: move a0,s0 */ set(4,cpu(16));
/* 0029757c: sb v1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(3));
/* 00297580: jal 0x00296f50 */ set(31,0x00297588u);/* delay 00297584 */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));body_00296f50();
/* 00297588: b 0x0029762c */ /* delay 0029758c */ goto L_0029762c;
L_00297590:;
/* 00297590: lbu v1,0x1(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000001))));
/* 00297594: beq v1,zero,0x002975b0 */ {int taken=(cpu(3)==cpu(0));/* delay 00297598 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002975b0;}}
/* 0029759c: beql v1,v0,0x002975e0 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 002975a0 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));goto L_002975e0;}}
/* 002975a4: b 0x0029762c */ /* delay 002975a8 */ goto L_0029762c;
L_002975b0:;
/* 002975b0: sb s1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));
/* 002975b4: move s1,zero */ set(17,cpu(0));
/* 002975b8: jal 0x002dbec0 */ set(31,0x002975c0u);/* delay 002975bc */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 002975c0: lui a1,0x29 */ set(5,sx(UINT32_C(0x00290000)));
/* 002975c4: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002975c8: addiu a1,a1,0x6d90 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00006d90)));
/* 002975cc: jal 0x002bf3a8 */ set(31,0x002975d4u);/* delay 002975d0 */ set(6,cpu(16));set(2,ps2FileRequestRead(cpu(4),cpu(5),cpu(6)));
/* 002975d4: b 0x0029762c */ /* delay 002975d8 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));goto L_0029762c;
L_002975e0:;
/* 002975e0: jal 0x002dbec0 */ set(31,0x002975e8u);/* delay 002975e4 */ set(17,cpu(0));body_002dbec0();
/* 002975e8: jal 0x00296c88 */ set(31,0x002975f0u);/* delay 002975ec */ set(4,cpu(16));body_00296c88();
/* 002975f0: b 0x0029762c */ /* delay 002975f4 */ goto L_0029762c;
L_002975f8:;
/* 002975f8: bne v0,zero,0x0029762c */ {int taken=(cpu(2)!=cpu(0));/* delay 002975fc */ if(taken){goto L_0029762c;}}
/* 00297600: sb s1,0x1(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(17));
/* 00297604: move s1,zero */ set(17,cpu(0));
/* 00297608: jal 0x002dbec0 */ set(31,0x00297610u);/* delay 0029760c */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 00297610: lui a1,0x29 */ set(5,sx(UINT32_C(0x00290000)));
/* 00297614: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00297618: addiu a1,a1,0x72a0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000072a0)));
/* 0029761c: move a2,s0 */ set(6,cpu(16));
/* 00297620: jal 0x002bf410 */ set(31,0x00297628u);/* delay 00297624 */ set(7,sx(UINT32_C(0x00000180)));set(2,ps2FileRequestStream(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 00297628: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
L_0029762c:;
/* 0029762c: beq s1,zero,0x00297640 */ {int taken=(cpu(17)==cpu(0));/* delay 00297630 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00297640;}}
/* 00297634: jal 0x002dbec0 */ set(31,0x0029763cu);/* delay 00297638 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));body_002dbec0();
/* 0029763c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00297640:;
/* 00297640: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297644: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297648: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0029764c: jr ra */ {uint64_t target=cpu(31);/* delay 00297650 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_00297460(void){body_00297460();}
static void body_00297658(void){
nocturneEffectAxisNoteEntry(0x00297658u);
uint64_t incoming=cpu(31);
/* 00297658: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0029765c: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 00297660: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297664: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297668: addiu s1,v0,0x5618 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));
/* 0029766c: b 0x00297694 */ /* delay 00297670 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_00297694;
L_00297678:;
/* 00297678: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0029767c: jal 0x002dbec0 */ set(31,0x00297684u);/* delay 00297680 */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));body_002dbec0();
/* 00297684: lw v1,0x18(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 00297688: move a0,s0 */ set(4,cpu(16));
/* 0029768c: jalr v1 */ {uint64_t target=cpu(3);set(31,0x00297694u);/* delay 00297690 */ lw(5,ea(4,(int32_t)UINT32_C(0x0000001c)));completion(target);}
L_00297694:;
/* 00297694: jal 0x002dbee0 */ set(31,0x0029769cu);/* delay 00297698 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_002dbee0();
/* 0029769c: lw s0,0x10(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002976a0: bnel s0,zero,0x00297678 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 002976a4 */ lw(2,ea(16,(int32_t)UINT32_C(0x0000002c)));goto L_00297678;}}
/* 002976a8: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002976ac: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002976b0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002976b4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002976b8: j 0x002dbec0 */ /* delay 002976bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002dbec0();return;
}
uint64_t ps2BattleActionRequest_00297658(void){body_00297658();return cpu(2);}
static void body_002976c0(void){
nocturneEffectAxisNoteEntry(0x002976c0u);
uint64_t incoming=cpu(31);
/* 002976c0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002976c4: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 002976c8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002976cc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002976d0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002976d4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002976d8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002976dc: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002976e0: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002976e4: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002976e8: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002976ec: jal 0x00297658 */ set(31,0x002976f4u);/* delay 002976f0 */ set(19,sx((uint32_t)cpu(2)+UINT32_C(0x00005618)));body_00297658();
/* 002976f4: lbu a3,0x6(s3) */ set(7,byte(ea(19,(int32_t)UINT32_C(0x00000006))));
/* 002976f8: beq a3,zero,0x002977e8 */ {int taken=(cpu(7)==cpu(0));/* delay 002976fc */ set(23,sx((uint32_t)cpu(19)+UINT32_C(0x00000004)));if(taken){goto L_002977e8;}}
/* 00297700: addiu s4,s3,0x14 */ set(20,sx((uint32_t)cpu(19)+UINT32_C(0x00000014)));
/* 00297704: li s6,0x1 */ set(22,sx(UINT32_C(0x00000001)));
/* 00297708: li s5,-0x1 */ set(21,sx(UINT32_C(0xffffffff)));
/* 0029770c: lbu s1,0x4(s3) */ set(17,byte(ea(19,(int32_t)UINT32_C(0x00000004))));
L_00297710:;
/* 00297710: lw a0,0x1c(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x0000001c)));
/* 00297714: sll v0,s1,0x3 */ set(2,sx((uint32_t)cpu(17)<<3));
/* 00297718: sll v1,s1,0x10 */ set(3,sx((uint32_t)cpu(17)<<16));
/* 0029771c: addiu a2,v0,0x20 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 00297720: addu v0,s7,a2 */ set(2,sx((uint32_t)cpu(23)+(uint32_t)cpu(6)));
/* 00297724: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00297728: lbu s2,0x0(s0) */ set(18,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 0029772c: bne s2,s6,0x002977d4 */ {int taken=(cpu(18)!=cpu(22));/* delay 00297730 */ set(5,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));if(taken){goto L_002977d4;}}
/* 00297734: beq s0,zero,0x00297798 */ {int taken=(cpu(16)==cpu(0));/* delay 00297738 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));if(taken){goto L_00297798;}}
/* 0029773c: addu v0,s3,a2 */ set(2,sx((uint32_t)cpu(19)+(uint32_t)cpu(6)));
/* 00297740: jal 0x002c62a0 */ set(31,0x00297748u);/* delay 00297744 */ lw(6,ea(2,(int32_t)UINT32_C(0x00000000)));set(2,ps2BattleActionPac_002C62A0(cpu(4),cpu(5),cpu(6)));
/* 00297748: bnel v0,s5,0x0029779c */ {int taken=(cpu(2)!=cpu(21));if(taken){/* delay 0029774c */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));goto L_0029779c;}}
/* 00297750: jal 0x002967e8 */ set(31,0x00297758u);/* delay 00297754 */ set(4,cpu(16));body_002967e8();
/* 00297758: sh s2,0x68(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000068)),(uint16_t)cpu(18));
/* 0029775c: lw v0,0x18(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 00297760: beql v0,zero,0x0029779c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00297764 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));goto L_0029779c;}}
/* 00297768: lw v0,0x0(s4) */ lw(2,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 0029776c: beq v0,zero,0x00297794 */ {int taken=(cpu(2)==cpu(0));/* delay 00297770 */ set(3,cpu(20));if(taken){goto L_00297794;}}
/* 00297774: addiu v1,v0,0x6c */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x0000006c)));
L_00297778:;
/* 00297778: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0029777c: nop  */ 
/* 00297780: nop  */ 
/* 00297784: nop  */ 
/* 00297788: nop  */ 
/* 0029778c: bnel v0,zero,0x00297778 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00297790 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x0000006c)));goto L_00297778;}}
L_00297794:;
/* 00297794: sw s0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
L_00297798:;
/* 00297798: lw a0,0x0(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));
L_0029779c:;
/* 0029779c: jal 0x002dbee0 */ set(31,0x002977a4u);/* delay 002977a0 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));body_002dbee0();
/* 002977a4: xori v1,s1,0x4 */ set(3,cpu(17)^UINT32_C(0x00000004));
/* 002977a8: lbu a1,0x7(s3) */ set(5,byte(ea(19,(int32_t)UINT32_C(0x00000007))));
/* 002977ac: movz s1,zero,v1 */ if(cpu(3)==0){set(17,cpu(0));}
/* 002977b0: lbu v0,0x6(s3) */ set(2,byte(ea(19,(int32_t)UINT32_C(0x00000006))));
/* 002977b4: lw a0,0x0(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 002977b8: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002977bc: addiu v0,v0,0xff */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000ff)));
/* 002977c0: sb s1,0x4(s3) */ sb(ea(19,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(17));
/* 002977c4: sb a1,0x7(s3) */ sb(ea(19,(int32_t)UINT32_C(0x00000007)),(uint8_t)cpu(5));
/* 002977c8: jal 0x002dbec0 */ set(31,0x002977d0u);/* delay 002977cc */ sb(ea(19,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(2));body_002dbec0();
/* 002977d0: lbu a3,0x6(s3) */ set(7,byte(ea(19,(int32_t)UINT32_C(0x00000006))));
L_002977d4:;
/* 002977d4: bnel a3,zero,0x00297710 */ {int taken=(cpu(7)!=cpu(0));if(taken){/* delay 002977d8 */ set(17,byte(ea(19,(int32_t)UINT32_C(0x00000004))));goto L_00297710;}}
/* 002977dc: b 0x002977ec */ /* delay 002977e0 */ goto L_002977ec;
L_002977e8:;
/* 002977e8: addiu s4,s3,0x14 */ set(20,sx((uint32_t)cpu(19)+UINT32_C(0x00000014)));
L_002977ec:;
/* 002977ec: jal 0x00297460 */ set(31,0x002977f4u);/* delay 002977f0 */ set(16,cpu(20));body_00297460();
/* 002977f4: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002977f8: beq v1,zero,0x0029783c */ {int taken=(cpu(3)==cpu(0));/* delay 002977fc */ set(17,sx(UINT32_C(0x00000006)));if(taken){goto L_0029783c;}}
/* 00297800: lbu v0,0x1(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000001))));
/* 00297804: nop  */ 
L_00297808:;
/* 00297808: bnel v0,s1,0x00297830 */ {int taken=(cpu(2)!=cpu(17));if(taken){/* delay 0029780c */ set(16,sx((uint32_t)cpu(3)+UINT32_C(0x0000006c)));goto L_00297830;}}
/* 00297810: lw v0,0x6c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000006c)));
/* 00297814: move a0,v1 */ set(4,cpu(3));
/* 00297818: lw a1,0x1c(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 0029781c: lw v1,0x18(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 00297820: jalr v1 */ {uint64_t target=cpu(3);set(31,0x00297828u);/* delay 00297824 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));completion(target);}
/* 00297828: b 0x00297834 */ /* delay 0029782c */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_00297834;
L_00297830:;
/* 00297830: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
L_00297834:;
/* 00297834: bnel v1,zero,0x00297808 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 00297838 */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000001))));goto L_00297808;}}
L_0029783c:;
/* 0029783c: lw v0,0x8(s3) */ lw(2,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 00297840: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00297844: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00297848: sltu v0,zero,v0 */ set(2,cpu(0)<cpu(2));
/* 0029784c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00297850: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00297854: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00297858: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0029785c: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00297860: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00297864: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00297868: jr ra */ {uint64_t target=cpu(31);/* delay 0029786c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002976C0(void){body_002976c0();return cpu(2);}
static void body_002a8078(void){
nocturneEffectAxisNoteEntry(0x002a8078u);
uint64_t incoming=cpu(31);
/* 002a8078: jr ra */ {uint64_t target=cpu(31);/* delay 002a807c */ checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_002A8078(void){body_002a8078();}
static void body_002bd4a8(void){
nocturneEffectAxisNoteEntry(0x002bd4a8u);
uint64_t incoming=cpu(31);
/* 002bd4a8: addiu sp,sp,-0x170 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffe90)));
/* 002bd4ac: lb v0,-0x2870(gp) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffd790))));
/* 002bd4b0: sd s1,0x158(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000158)));
/* 002bd4b4: move s1,a0 */ set(17,cpu(4));
/* 002bd4b8: sd s0,0x150(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000150)));
/* 002bd4bc: move a1,s1 */ set(5,cpu(17));
/* 002bd4c0: beq v0,zero,0x002bd530 */ {int taken=(cpu(2)==cpu(0));/* delay 002bd4c4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000160)));if(taken){goto L_002bd530;}}
/* 002bd4c8: jal 0x002d5d0c */ set(31,0x002bd4d0u);/* delay 002bd4cc */ body_002d5d0c();
/* 002bd4d0: li v1,-0x40 */ set(3,sx(UINT32_C(0xffffffc0)));
/* 002bd4d4: move s0,v0 */ set(16,cpu(2));
/* 002bd4d8: addiu v0,sp,0x4f */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x0000004f)));
/* 002bd4dc: move a1,s1 */ set(5,cpu(17));
/* 002bd4e0: and s1,v0,v1 */ set(17,cpu(2)&cpu(3));
/* 002bd4e4: move a2,s0 */ set(6,cpu(16));
/* 002bd4e8: beq s0,zero,0x002bd53c */ {int taken=(cpu(16)==cpu(0));/* delay 002bd4ec */ set(4,cpu(17));if(taken){goto L_002bd53c;}}
/* 002bd4f0: jal 0x002d43a4 */ set(31,0x002bd4f8u);/* delay 002bd4f4 */ set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 002bd4f8: lui a0,0x59 */ set(4,sx(UINT32_C(0x00590000)));
/* 002bd4fc: move t0,s0 */ set(8,cpu(16));
/* 002bd500: li a1,0x7d1 */ set(5,sx(UINT32_C(0x000007d1)));
/* 002bd504: move a2,zero */ set(6,cpu(0));
/* 002bd508: move t1,zero */ set(9,cpu(0));
/* 002bd50c: addiu a0,a0,-0xcf0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff310)));
/* 002bd510: move a3,s1 */ set(7,cpu(17));
/* 002bd514: move t2,zero */ set(10,cpu(0));
/* 002bd518: move t3,zero */ set(11,cpu(0));
/* 002bd51c: jal 0x002cd418 */ set(31,0x002bd524u);/* delay 002bd520 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));set(2,ps2DiagnosticRpcCall(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10),cpu(11),word(ea(29,0))));
/* 002bd524: b 0x002bd540 */ /* delay 002bd528 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000150)));goto L_002bd540;
L_002bd530:;
/* 002bd530: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 002bd534: jal 0x002ddd60 */ set(31,0x002bd53cu);/* delay 002bd538 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00001908)));ps2SdkPrintf(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10),cpu(11));
L_002bd53c:;
/* 002bd53c: ld s0,0x150(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000150)));
L_002bd540:;
/* 002bd540: ld s1,0x158(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000158)));
/* 002bd544: ld ra,0x160(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000160)));
/* 002bd548: jr ra */ {uint64_t target=cpu(31);/* delay 002bd54c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000170)));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_002BD4A8(uint64_t a0){set(4,a0);body_002bd4a8();}
static void body_002bd550(void){
nocturneEffectAxisNoteEntry(0x002bd550u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002bd550: addiu sp,sp,-0x170 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffe90)));
/* 002bd554: move v0,a0 */ set(2,cpu(4));
/* 002bd558: sd a1,0x138(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000138)));
/* 002bd55c: move a1,v0 */ set(5,cpu(2));
/* 002bd560: move a0,sp */ set(4,cpu(29));
/* 002bd564: sd a2,0x140(sp) */ save(6,ea(29,(int32_t)UINT32_C(0x00000140)));
/* 002bd568: addiu a2,sp,0x138 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000138)));
/* 002bd56c: sd s0,0x100(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000100)));
/* 002bd570: sd ra,0x108(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000108)));
/* 002bd574: sd a3,0x148(sp) */ save(7,ea(29,(int32_t)UINT32_C(0x00000148)));
/* 002bd578: sd t0,0x150(sp) */ save(8,ea(29,(int32_t)UINT32_C(0x00000150)));
/* 002bd57c: sd t1,0x158(sp) */ save(9,ea(29,(int32_t)UINT32_C(0x00000158)));
/* 002bd580: sd t2,0x160(sp) */ save(10,ea(29,(int32_t)UINT32_C(0x00000160)));
/* 002bd584: sd t3,0x168(sp) */ save(11,ea(29,(int32_t)UINT32_C(0x00000168)));
/* 002bd588: swc1 f12,0x118(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000118)),f[12]);
/* 002bd58c: swc1 f13,0x11c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000011c)),f[13]);
/* 002bd590: swc1 f14,0x120(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000120)),f[14]);
/* 002bd594: swc1 f15,0x124(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000124)),f[15]);
/* 002bd598: swc1 f16,0x128(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000128)),f[16]);
/* 002bd59c: swc1 f17,0x12c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000012c)),f[17]);
/* 002bd5a0: swc1 f18,0x130(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000130)),f[18]);
/* 002bd5a4: jal 0x002d7f88 */ set(31,0x002bd5acu);/* delay 002bd5a8 */ sw(ea(29,(int32_t)UINT32_C(0x00000134)),f[19]);body_002d7f88();
/* 002bd5ac: move a0,sp */ set(4,cpu(29));
/* 002bd5b0: jal 0x002bd4a8 */ set(31,0x002bd5b8u);/* delay 002bd5b4 */ set(16,cpu(2));body_002bd4a8();
/* 002bd5b8: move v0,s0 */ set(2,cpu(16));
/* 002bd5bc: ld ra,0x108(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000108)));
/* 002bd5c0: ld s0,0x100(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000100)));
/* 002bd5c4: jr ra */ {uint64_t target=cpu(31);/* delay 002bd5c8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000170)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002BD550(uint64_t a0){set(4,a0);body_002bd550();return cpu(2);}
static void body_002be6a8(void){
nocturneEffectAxisNoteEntry(0x002be6a8u);
uint64_t incoming=cpu(31);
/* 002be6a8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002be6ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002be6b0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be6b4: jal 0x002e4070 */ set(31,0x002be6bcu);/* delay 002be6b8 */ set(16,cpu(4));set(2,ps2EffectKernelDisableInterrupts_002E4070());
/* 002be6bc: lw v1,0x4(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002be6c0: move a0,v0 */ set(4,cpu(2));
/* 002be6c4: bne v1,zero,0x002be6d8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002be6c8 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002be6d8;}}
/* 002be6cc: b 0x002be6dc */ /* delay 002be6d0 */ sw(ea(28,(int32_t)UINT32_C(0xffffd7e4)),(uint32_t)cpu(2));goto L_002be6dc;
L_002be6d8:;
/* 002be6d8: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002be6dc:;
/* 002be6dc: bnel v0,zero,0x002be6e8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002be6e0 */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));goto L_002be6e8;}}
/* 002be6e4: sw v1,-0x2818(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd7e8)),(uint32_t)cpu(3));
L_002be6e8:;
/* 002be6e8: lhu v0,-0x2820(gp) */ set(2,half(ea(28,(int32_t)UINT32_C(0xffffd7e0))));
/* 002be6ec: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002be6f0: beq a0,zero,0x002be700 */ {int taken=(cpu(4)==cpu(0));/* delay 002be6f4 */ sh(ea(28,(int32_t)UINT32_C(0xffffd7e0)),(uint16_t)cpu(2));if(taken){goto L_002be700;}}
/* 002be6f8: jal 0x002e40b8 */ set(31,0x002be700u);/* delay 002be6fc */ set(2,ps2EffectKernelEnableInterrupts_002E40B8());
L_002be700:;
/* 002be700: jal 0x002a8bd8 */ set(31,0x002be708u);/* delay 002be704 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));ps2BattleActionModel_002A8BD8(cpu(4));
/* 002be708: move a0,s0 */ set(4,cpu(16));
/* 002be70c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002be710: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002be714: j 0x002a8bd8 */ /* delay 002be718 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionModel_002A8BD8(cpu(4));return;
}
void ps2BattleActionRequest_002BE6A8(uint64_t a0){set(4,a0);body_002be6a8();}
static void body_002bf688(void){
nocturneEffectAxisNoteEntry(0x002bf688u);
uint64_t incoming=cpu(31);
/* 002bf688: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002bf68c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf690: lb v0,0x16(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000016))));
/* 002bf694: slti v1,v0,0x7 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000007));
/* 002bf698: slti v0,v0,0x9 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 002bf69c: beq v0,zero,0x002bf6b8 */ {int taken=(cpu(2)==cpu(0));/* delay 002bf6a0 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002bf6b8;}}
/* 002bf6a4: bne v1,zero,0x002bf6bc */ {int taken=(cpu(3)!=cpu(0));/* delay 002bf6a8 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002bf6bc;}}
/* 002bf6ac: jal 0x002be6a8 */ set(31,0x002bf6b4u);/* delay 002bf6b0 */ body_002be6a8();
/* 002bf6b4: move v0,zero */ set(2,cpu(0));
L_002bf6b8:;
/* 002bf6b8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002bf6bc:;
/* 002bf6bc: jr ra */ {uint64_t target=cpu(31);/* delay 002bf6c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002BF688(uint64_t a0){set(4,a0);body_002bf688();return cpu(2);}
static void body_002bf800(void){
nocturneEffectAxisNoteEntry(0x002bf800u);
uint64_t incoming=cpu(31);
/* 002bf800: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002bf804: lw v0,-0x2810(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd7f0)));
/* 002bf808: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf80c: move s0,a0 */ set(16,cpu(4));
/* 002bf810: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf814: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf818: beq v0,s0,0x002bf85c */ {int taken=(cpu(2)==cpu(16));/* delay 002bf81c */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002bf85c;}}
/* 002bf820: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002bf824: sw s0,-0x2810(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd7f0)),(uint32_t)cpu(16));
/* 002bf828: addiu s2,v0,-0x6500 */ set(18,sx((uint32_t)cpu(2)+UINT32_C(0xffff9b00)));
/* 002bf82c: move s1,zero */ set(17,cpu(0));
/* 002bf830: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 002bf834: nop  */ 
L_002bf838:;
/* 002bf838: addiu s2,s2,0x18 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000018)));
/* 002bf83c: bltz v0,0x002bf84c */ {int taken=((int64_t)cpu(2)<0);/* delay 002bf840 */ set(4,cpu(2));if(taken){goto L_002bf84c;}}
/* 002bf844: jal 0x002dbd30 */ set(31,0x002bf84cu);/* delay 002bf848 */ set(5,cpu(16));body_002dbd30();
L_002bf84c:;
/* 002bf84c: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 002bf850: sltiu v0,s1,0x4 */ set(2,cpu(17)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000004));
/* 002bf854: bnel v0,zero,0x002bf838 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002bf858 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));goto L_002bf838;}}
L_002bf85c:;
/* 002bf85c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf860: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bf864: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bf868: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bf86c: jr ra */ {uint64_t target=cpu(31);/* delay 002bf870 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
void ps2BattleActionRequest_002BF800(uint64_t a0){set(4,a0);body_002bf800();}
static void body_002bf898(void){
nocturneEffectAxisNoteEntry(0x002bf898u);
uint64_t incoming=cpu(31);
/* 002bf898: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002bf89c: li a0,0x48 */ set(4,sx(UINT32_C(0x00000048)));
/* 002bf8a0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf8a4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bf8a8: j 0x002bf800 */ /* delay 002bf8ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002bf800();return;
}
void ps2BattleActionRequest_002BF898(void){body_002bf898();}
static void body_002bfd60(void){
nocturneEffectAxisNoteEntry(0x002bfd60u);
uint64_t incoming=cpu(31);
/* 002bfd60: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002bfd64: move v0,zero */ set(2,cpu(0));
/* 002bfd68: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bfd6c: move s2,a0 */ set(18,cpu(4));
/* 002bfd70: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bfd74: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bfd78: beq s2,zero,0x002bfdb4 */ {int taken=(cpu(18)==cpu(0));/* delay 002bfd7c */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002bfdb4;}}
/* 002bfd80: jal 0x002d5d0c */ set(31,0x002bfd88u);/* delay 002bfd84 */ body_002d5d0c();
/* 002bfd88: move s0,v0 */ set(16,cpu(2));
/* 002bfd8c: jal 0x002a8af8 */ set(31,0x002bfd94u);/* delay 002bfd90 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 002bfd94: move a1,s2 */ set(5,cpu(18));
/* 002bfd98: move s1,v0 */ set(17,cpu(2));
/* 002bfd9c: move a2,s0 */ set(6,cpu(16));
/* 002bfda0: move a0,s1 */ set(4,cpu(17));
/* 002bfda4: jal 0x002d43a4 */ set(31,0x002bfdacu);/* delay 002bfda8 */ set(16,sx((uint32_t)cpu(17)+(uint32_t)cpu(16)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 002bfdac: sb zero,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 002bfdb0: move v0,s1 */ set(2,cpu(17));
L_002bfdb4:;
/* 002bfdb4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002bfdb8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002bfdbc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002bfdc0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002bfdc4: jr ra */ {uint64_t target=cpu(31);/* delay 002bfdc8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002BFD60(uint64_t a0){set(4,a0);body_002bfd60();return cpu(2);}
static void body_002c3798(void){
nocturneEffectAxisNoteEntry(0x002c3798u);
uint64_t incoming=cpu(31);
/* 002c3798: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002c379c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c37a0: move s1,zero */ set(17,cpu(0));
/* 002c37a4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c37a8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c37ac: move s4,a0 */ set(20,cpu(4));
/* 002c37b0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c37b4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c37b8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c37bc: lw s2,0x10(s4) */ lw(18,ea(20,(int32_t)UINT32_C(0x00000010)));
/* 002c37c0: jal 0x002b2a60 */ set(31,0x002c37c8u);/* delay 002c37c4 */ set(4,cpu(18));set(2,ps2BattleActionModel_002B2A60(cpu(4)));
/* 002c37c8: beq s2,s1,0x002c37fc */ {int taken=(cpu(18)==cpu(17));/* delay 002c37cc */ set(19,cpu(2));if(taken){goto L_002c37fc;}}
/* 002c37d0: addiu s0,s4,0x14 */ set(16,sx((uint32_t)cpu(20)+UINT32_C(0x00000014)));
/* 002c37d4: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
L_002c37d8:;
/* 002c37d8: addiu s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000004)));
/* 002c37dc: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 002c37e0: jal 0x002abe08 */ set(31,0x002c37e8u);/* delay 002c37e4 */ set(4,sx((uint32_t)cpu(20)+(uint32_t)cpu(4)));set(2,ps2BattleActionTexture_002ABE08(cpu(4)));
/* 002c37e8: move a0,s3 */ set(4,cpu(19));
/* 002c37ec: jal 0x002b2b10 */ set(31,0x002c37f4u);/* delay 002c37f0 */ set(5,cpu(2));ps2BattleActionModel_002B2B10(cpu(4),cpu(5));
/* 002c37f4: bnel s1,s2,0x002c37d8 */ {int taken=(cpu(17)!=cpu(18));if(taken){/* delay 002c37f8 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002c37d8;}}
L_002c37fc:;
/* 002c37fc: move v0,s3 */ set(2,cpu(19));
/* 002c3800: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c3804: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c3808: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c380c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c3810: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c3814: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c3818: jr ra */ {uint64_t target=cpu(31);/* delay 002c381c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002C3798(uint64_t a0){set(4,a0);body_002c3798();return cpu(2);}
static void body_002c3888(void){
nocturneEffectAxisNoteEntry(0x002c3888u);
uint64_t incoming=cpu(31);
/* 002c3888: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c388c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c3890: addiu s0,a0,0x20 */ set(16,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 002c3894: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c3898: move a1,s0 */ set(5,cpu(16));
/* 002c389c: lw a2,0x10(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002c38a0: lw a3,0x14(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000014)));
/* 002c38a4: move a0,s0 */ set(4,cpu(16));
/* 002c38a8: jal 0x002c39c8 */ set(31,0x002c38b0u);/* delay 002c38ac */ set(6,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));ps2BattleActionPac_002C39C8(cpu(4),cpu(5),cpu(6),cpu(7));
/* 002c38b0: move v0,s0 */ set(2,cpu(16));
/* 002c38b4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c38b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c38bc: jr ra */ {uint64_t target=cpu(31);/* delay 002c38c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002C3888(uint64_t a0){set(4,a0);body_002c3888();return cpu(2);}
static void body_002c3928(void){
nocturneEffectAxisNoteEntry(0x002c3928u);
uint64_t incoming=cpu(31);
/* 002c3928: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c392c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c3930: addiu s0,a0,0x20 */ set(16,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 002c3934: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c3938: move a1,s0 */ set(5,cpu(16));
/* 002c393c: lw a2,0x10(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002c3940: lw a3,0x14(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000014)));
/* 002c3944: move a0,s0 */ set(4,cpu(16));
/* 002c3948: jal 0x002c39c8 */ set(31,0x002c3950u);/* delay 002c394c */ set(6,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));ps2BattleActionPac_002C39C8(cpu(4),cpu(5),cpu(6),cpu(7));
/* 002c3950: move v0,s0 */ set(2,cpu(16));
/* 002c3954: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c3958: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c395c: jr ra */ {uint64_t target=cpu(31);/* delay 002c3960 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002C3928(uint64_t a0){set(4,a0);body_002c3928();return cpu(2);}
static void body_002d5d0c(void){
nocturneEffectAxisNoteEntry(0x002d5d0cu);
uint64_t incoming=cpu(31);
/* 002d5d0c: andi v0,a0,0x7 */ set(2,cpu(4)&UINT32_C(0x00000007));
/* 002d5d10: bne v0,zero,0x002d5e20 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5d14 */ set(7,cpu(4));if(taken){goto L_002d5e20;}}
/* 002d5d18: andi v1,a0,0xf */ set(3,cpu(4)&UINT32_C(0x0000000f));
/* 002d5d1c: lui v0,0x101 */ set(2,sx(UINT32_C(0x01010000)));
/* 002d5d20: ori v0,v0,0x101 */ set(2,cpu(2)|UINT32_C(0x00000101));
/* 002d5d24: dsll v0,v0,0x10 */ set(2,cpu(2)<<16);
/* 002d5d28: ori v0,v0,0x101 */ set(2,cpu(2)|UINT32_C(0x00000101));
/* 002d5d2c: dsll v0,v0,0x10 */ set(2,cpu(2)<<16);
/* 002d5d30: ori v0,v0,0x101 */ set(2,cpu(2)|UINT32_C(0x00000101));
/* 002d5d34: bne v1,zero,0x002d5db0 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d5d38 */ set(5,cpu(4));if(taken){goto L_002d5db0;}}
/* 002d5d3c: lq v1,0x0(a1) */ requestLq(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5d40: pcpyld t0,v0,v0 */ requestPacked(0,8,2,2);
/* 002d5d44: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 002d5d48: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5d4c: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5d50: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5d54: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5d58: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5d5c: psubb v0,v1,t0 */ requestPacked(4,2,3,8);
/* 002d5d60: pnor v1,zero,v1 */ requestPacked(3,3,0,3);
/* 002d5d64: pcpyld t1,a0,a0 */ requestPacked(0,9,4,4);
/* 002d5d68: pand v0,v0,v1 */ requestPacked(2,2,2,3);
/* 002d5d6c: pand v0,v0,t1 */ requestPacked(2,2,2,9);
/* 002d5d70: pcpyud v1,v0,t0 */ requestPacked(1,3,2,8);
/* 002d5d74: or a2,v1,v0 */ set(6,cpu(3)|cpu(2));
/* 002d5d78: bnel a2,zero,0x002d5e20 */ {int taken=(cpu(6)!=cpu(0));if(taken){/* delay 002d5d7c */ set(4,cpu(5));goto L_002d5e20;}}
/* 002d5d80: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
L_002d5d84:;
/* 002d5d84: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5d88: pnor v1,zero,v0 */ requestPacked(3,3,0,2);
/* 002d5d8c: psubb v0,v0,t0 */ requestPacked(4,2,2,8);
/* 002d5d90: pand v0,v0,v1 */ requestPacked(2,2,2,3);
/* 002d5d94: pand a0,v0,t1 */ requestPacked(2,4,2,9);
/* 002d5d98: pcpyud v1,a0,a2 */ requestPacked(1,3,4,6);
/* 002d5d9c: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002d5da0: beql v1,zero,0x002d5d84 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002d5da4 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));goto L_002d5d84;}}
/* 002d5da8: b 0x002d5e20 */ /* delay 002d5dac */ set(4,cpu(5));goto L_002d5e20;
L_002d5db0:;
/* 002d5db0: ld v1,0x0(a1) */ restore(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5db4: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 002d5db8: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5dbc: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5dc0: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5dc4: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5dc8: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5dcc: dsubu v0,v1,v0 */ set(2,cpu(3)-cpu(2));
/* 002d5dd0: nor v1,zero,v1 */ set(3,~(cpu(0)|cpu(3)));
/* 002d5dd4: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5dd8: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 002d5ddc: bnel v0,zero,0x002d5e20 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d5de0 */ set(4,cpu(5));goto L_002d5e20;}}
/* 002d5de4: lui a2,0x101 */ set(6,sx(UINT32_C(0x01010000)));
/* 002d5de8: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d5dec: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d5df0: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d5df4: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d5df8: ori a2,a2,0x101 */ set(6,cpu(6)|UINT32_C(0x00000101));
/* 002d5dfc: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
L_002d5e00:;
/* 002d5e00: ld v0,0x0(a1) */ restore(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5e04: nor v1,zero,v0 */ set(3,~(cpu(0)|cpu(2)));
/* 002d5e08: dsubu v0,v0,a2 */ set(2,cpu(2)-cpu(6));
/* 002d5e0c: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5e10: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 002d5e14: beql v0,zero,0x002d5e00 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d5e18 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));goto L_002d5e00;}}
/* 002d5e1c: move a0,a1 */ set(4,cpu(5));
L_002d5e20:;
/* 002d5e20: lb v0,0x0(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002d5e24: nop  */ 
/* 002d5e28: nop  */ 
/* 002d5e2c: nop  */ 
/* 002d5e30: nop  */ 
/* 002d5e34: bnel v0,zero,0x002d5e20 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d5e38 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));goto L_002d5e20;}}
/* 002d5e3c: jr ra */ {uint64_t target=cpu(31);/* delay 002d5e40 */ set(2,sx((uint32_t)cpu(4)-(uint32_t)cpu(7)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002D5D0C(uint64_t a0){set(4,a0);body_002d5d0c();return cpu(2);}
static void body_002d7f88(void){
nocturneEffectAxisNoteEntry(0x002d7f88u);
uint64_t incoming=cpu(31);
/* 002d7f88: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d7f8c: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 002d7f90: lw t0,-0x41d8(v0) */ lw(8,ea(2,(int32_t)UINT32_C(0xffffbe28)));
/* 002d7f94: li v0,0x208 */ set(2,sx(UINT32_C(0x00000208)));
/* 002d7f98: lui v1,0x7fff */ set(3,sx(UINT32_C(0x7fff0000)));
/* 002d7f9c: move a3,a0 */ set(7,cpu(4));
/* 002d7fa0: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002d7fa4: move a0,sp */ set(4,cpu(29));
/* 002d7fa8: sd ra,0x60(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d7fac: sw v1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 002d7fb0: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002d7fb4: sh v0,0xc(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 002d7fb8: sw a3,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(7));
/* 002d7fbc: sw t0,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(8));
/* 002d7fc0: jal 0x002d6600 */ set(31,0x002d7fc8u);/* delay 002d7fc4 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));set(2,ps2BattleActionVfprintfStream_002D6600(cpu(4),cpu(5),cpu(6)));
/* 002d7fc8: lw v1,0x0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d7fcc: ld ra,0x60(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d7fd0: sb zero,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 002d7fd4: jr ra */ {uint64_t target=cpu(31);/* delay 002d7fd8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002D7F88(uint64_t a0, uint64_t a1, uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002d7f88();return cpu(2);}
static void body_002dbd30(void){
nocturneEffectAxisNoteEntry(0x002dbd30u);
uint64_t incoming=cpu(31);
/* 002dbd30: li v1,0x29 */ set(3,sx(UINT32_C(0x00000029)));
/* 002dbd34: syscall 0x0 */ {uint64_t arguments[2]={cpu(4),cpu(5)};set(2,nocturneLibcStreamKernel(0x29u,2,arguments));}
/* 002dbd38: jr ra */ {uint64_t target=cpu(31);/* delay 002dbd3c */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002DBD30(uint64_t a0, uint64_t a1){set(4,a0);set(5,a1);body_002dbd30();return cpu(2);}
static void body_002dbec0(void){
nocturneEffectAxisNoteEntry(0x002dbec0u);
uint64_t incoming=cpu(31);
/* 002dbec0: li v1,0x42 */ set(3,sx(UINT32_C(0x00000042)));
/* 002dbec4: syscall 0x0 */ {uint64_t arguments[1]={cpu(4)};set(2,nocturneLibcStreamKernel(0x42u,1,arguments));}
/* 002dbec8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbecc */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002DBEC0(uint64_t a0){set(4,a0);body_002dbec0();return cpu(2);}
static void body_002dbee0(void){
nocturneEffectAxisNoteEntry(0x002dbee0u);
uint64_t incoming=cpu(31);
/* 002dbee0: li v1,0x44 */ set(3,sx(UINT32_C(0x00000044)));
/* 002dbee4: syscall 0x0 */ {uint64_t arguments[1]={cpu(4)};set(2,nocturneLibcStreamKernel(0x44u,1,arguments));}
/* 002dbee8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbeec */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionRequest_002DBEE0(uint64_t a0){set(4,a0);body_002dbee0();return cpu(2);}
