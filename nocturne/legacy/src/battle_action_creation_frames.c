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
static float real(uint32_t u){float v;memcpy(&v,&u,4);return v;}
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
/* Little-endian LDL/LDR and SDL/SDR each touch their actual aligned64 unit.
 * Do not replace adjacent operations with memcpy: aliases can observe order. */
static void pextuw(unsigned d,unsigned s,unsigned t){uint32_t x[4],y[4],z[4];nocturneEffectHostCpuRead(s,x);nocturneEffectHostCpuRead(t,y);z[0]=y[2];z[1]=x[2];z[2]=y[3];z[3]=x[3];nocturneEffectHostCpuWrite(d,z);}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}


#include "battle_action_creation_frames.h"
#include "battle_action_polygon_frames.h"
#include "battle_action_copy_frames.h"
#include "special_polygon_copy.h"
#include "magatuhi_creation.h"
#include "battle_action_printf_frames.h"
#include "effect_soft_double_frames.h"
#include "part_control_native_frames.h"
#include "emitter_initialization.h"
#include "billboard_copy.h"
#include "polygon_prerequisites.h"
#include "compiler_numeric.h"
#include "anchor_callbacks.h"
#include "script_compare.h"
#include "magatuhi_helpers.h"
#include <stdio.h>
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneBattleActionEffectCreation(uint32_t target,uint64_t type,uint64_t source);
extern uint64_t nocturneBattleActionEmitterCopy(uint32_t target,uint64_t source);
static uint32_t sub(uint32_t a,uint32_t c){return EE_FPU_SUB_S(a,c);}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void creationDivide(uint32_t n,uint32_t d){EE_ANCHOR_DIVU_STATE(d?n/d:UINT32_MAX,d?n%d:n);}

uint64_t ps2BattleActionCreation_0015ADA0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015ada0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 0015ada0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015ada4: lwc1 f0,-0x7bcc(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8434)));
/* 0015ada8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015adac: move s1,a0 */ set(17,cpu(4));
/* 0015adb0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015adb4: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015adb8: lwc1 f12,0xc(s1) */ f[12]=word(ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0015adbc: c.lt.S f12,f0 */ condition=EE_FPU_COMPARE_S(f[12],f[0],1);
/* 0015adc0: bc1fl 0x0015adec */ {int taken=(!condition);if(taken){/* delay 0015adc4 */ set(4,half(ea(17,(int32_t)UINT32_C(0x00000000))));goto L_0015adec;}}
/* 0015adc8: jal 0x002d1550 */ set(31,0x0015add0u);/* delay 0015adcc */ set(16,sx(UINT32_C(0x00530000)));set(2,ps2EffectSoftDoubleFromFloat_002D1550(real(f[12])));
/* 0015add0: addiu s0,s0,0x2af0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00002af0)));
/* 0015add4: move a1,v0 */ set(5,cpu(2));
/* 0015add8: jal 0x002d4748 */ set(31,0x0015ade0u);/* delay 0015addc */ set(4,cpu(16));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));
/* 0015ade0: jal 0x0015af88 */ set(31,0x0015ade8u);/* delay 0015ade4 */ set(4,cpu(17));ps2BattleActionCreation_0015AF88(cpu(4));
/* 0015ade8: lhu a0,0x0(s1) */ set(4,half(ea(17,(int32_t)UINT32_C(0x00000000))));
L_0015adec:;
/* 0015adec: addiu a2,s1,0x10 */ set(6,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));
/* 0015adf0: jal 0x0015aad0 */ set(31,0x0015adf8u);/* delay 0015adf4 */ set(5,half(ea(17,(int32_t)UINT32_C(0x00000004))));set(2,ps2BattleActionCreation_0015AAD0(cpu(4),cpu(5),cpu(6)));
/* 0015adf8: lwc1 f1,0xc(s1) */ f[1]=word(ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0015adfc: lwc1 f0,-0x7bc8(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8438)));
/* 0015ae00: c.le.S f1,f0 */ condition=EE_FPU_COMPARE_S(f[1],f[0],2);
/* 0015ae04: bc1f 0x0015ae90 */ {int taken=(!condition);/* delay 0015ae08 */ set(16,cpu(2));if(taken){goto L_0015ae90;}}
/* 0015ae0c: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0015ae10: sltiu v0,v1,0x2 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0015ae14: bnel v0,zero,0x0015ae30 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0015ae18 */ lw(6,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_0015ae30;}}
/* 0015ae1c: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0015ae20: beql v1,v0,0x0015ae60 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 0015ae24 */ lw(6,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_0015ae60;}}
/* 0015ae28: b 0x0015ae88 */ /* delay 0015ae2c */ set(4,sx(UINT32_C(0x00530000)));goto L_0015ae88;
L_0015ae30:;
/* 0015ae30: addiu a2,a2,0xb0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x000000b0)));
/* 0015ae34: qmfc2 a1,vf0 */ {uint32_t quad[4];EE_ROT_VU_READ(0,quad);nocturneEffectHostCpuWrite(5,quad);}
/* 0015ae38: pextuw a0,zero,a1 */ pextuw(4,0,5);
/* 0015ae3c: pextuw v0,zero,a0 */ pextuw(2,0,4);
/* 0015ae40: pextuw v1,a0,zero */ pextuw(3,4,0);
/* 0015ae44: sq v0,0x0(a2) */ sq(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 0015ae48: sq v1,0x10(a2) */ sq(3,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 0015ae4c: sq a0,0x20(a2) */ sq(4,ea(6,(int32_t)UINT32_C(0x00000020)));
/* 0015ae50: sq a1,0x30(a2) */ sq(5,ea(6,(int32_t)UINT32_C(0x00000030)));
/* 0015ae54: b 0x0015ae88 */ /* delay 0015ae58 */ set(4,sx(UINT32_C(0x00530000)));goto L_0015ae88;
L_0015ae60:;
/* 0015ae60: addiu a2,a2,0x20 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000020)));
/* 0015ae64: qmfc2 a1,vf0 */ {uint32_t quad[4];EE_ROT_VU_READ(0,quad);nocturneEffectHostCpuWrite(5,quad);}
/* 0015ae68: pextuw a0,zero,a1 */ pextuw(4,0,5);
/* 0015ae6c: pextuw v0,zero,a0 */ pextuw(2,0,4);
/* 0015ae70: pextuw v1,a0,zero */ pextuw(3,4,0);
/* 0015ae74: sq v0,0x0(a2) */ sq(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 0015ae78: sq v1,0x10(a2) */ sq(3,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 0015ae7c: sq a0,0x20(a2) */ sq(4,ea(6,(int32_t)UINT32_C(0x00000020)));
/* 0015ae80: sq a1,0x30(a2) */ sq(5,ea(6,(int32_t)UINT32_C(0x00000030)));
/* 0015ae84: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
L_0015ae88:;
/* 0015ae88: jal 0x002d4748 */ set(31,0x0015ae90u);/* delay 0015ae8c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00002b08)));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));
L_0015ae90:;
/* 0015ae90: move v0,s0 */ set(2,cpu(16));
/* 0015ae94: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015ae98: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015ae9c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015aea0: jr ra */ {uint64_t target=cpu(31);/* delay 0015aea4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015AAD0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);nocturneEffectAxisNoteEntry(0x0015aad0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0015aad0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0015aad4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015aad8: andi s1,a0,0xffff */ set(17,cpu(4)&UINT32_C(0x0000ffff));
/* 0015aadc: li a0,0x10 */ set(4,sx(UINT32_C(0x00000010)));
/* 0015aae0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015aae4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015aae8: andi s2,a1,0xffff */ set(18,cpu(5)&UINT32_C(0x0000ffff));
/* 0015aaec: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015aaf0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0015aaf4: jal 0x002a8af8 */ set(31,0x0015aafcu);/* delay 0015aaf8 */ set(19,cpu(6));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015aafc: sll v1,s1,0x1 */ set(3,sx((uint32_t)cpu(17)<<1));
/* 0015ab00: lwc1 f0,-0x7bd0(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8430)));
/* 0015ab04: addu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(17)));
/* 0015ab08: move s0,v0 */ set(16,cpu(2));
/* 0015ab0c: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 0015ab10: sw s1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 0015ab14: swc1 f0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),f[0]);
/* 0015ab18: move a0,s2 */ set(4,cpu(18));
/* 0015ab1c: sw s2,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(18));
/* 0015ab20: lui v0,0x31 */ set(2,sx(UINT32_C(0x00310000)));
/* 0015ab24: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0015ab28: lw v0,0x6ef0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00006ef0)));
/* 0015ab2c: jalr v0 */ {uint64_t target=cpu(2);set(31,0x0015ab34u);/* delay 0015ab30 */ set(5,cpu(19));set(2,nocturneBattleActionEffectCreation((uint32_t)target,cpu(4),cpu(5)));}
/* 0015ab34: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0015ab38: move v0,s0 */ set(2,cpu(16));
/* 0015ab3c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015ab40: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015ab44: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015ab48: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015ab4c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0015ab50: jr ra */ {uint64_t target=cpu(31);/* delay 0015ab54 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00164FF8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x00164ff8u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00164ff8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00164ffc: li a2,0x3 */ set(6,sx(UINT32_C(0x00000003)));
/* 00165000: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00165004: move s0,a1 */ set(16,cpu(5));
/* 00165008: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0016500c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00165010: move s2,a0 */ set(18,cpu(4));
/* 00165014: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00165018: sll v0,s2,0x1 */ set(2,sx((uint32_t)cpu(18)<<1));
/* 0016501c: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00165020: lw a3,0x4(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00165024: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00165028: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0016502c: addu v1,s0,a3 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(7)));
/* 00165030: addiu s1,v1,0x10 */ set(17,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 00165034: bne a1,a2,0x00165044 */ {int taken=(cpu(5)!=cpu(6));/* delay 00165038 */ set(4,cpu(17));if(taken){goto L_00165044;}}
/* 0016503c: beq a3,zero,0x001650a0 */ {int taken=(cpu(7)==cpu(0));/* delay 00165040 */ set(3,sx((uint32_t)cpu(18)<<1));if(taken){goto L_001650a0;}}
L_00165044:;
/* 00165044: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 00165048: lui at,0x31 */ set(1,sx(UINT32_C(0x00310000)));
/* 0016504c: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 00165050: lw v0,0x7270(at) */ lw(2,ea(1,(int32_t)UINT32_C(0x00007270)));
/* 00165054: jalr v0 */ {uint64_t target=cpu(2);set(31,0x0016505cu);/* delay 00165058 */ sw(ea(17,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));switch((uint32_t)target){case 0x0015e2a8u:set(2,ps2BattleActionCreation_0015E2A8(cpu(4)));break;case 0x0015e8f8u:set(2,ps2BattleActionCreation_0015E8F8(cpu(4)));break;case 0x0015ef48u:set(2,ps2BattleActionCreation_0015EF48(cpu(4)));break;case 0x0015faf0u:set(2,ps2BattleActionCreation_0015FAF0(cpu(4)));break;case 0x001600d0u:set(2,ps2BattleActionCreation_001600D0(cpu(4)));break;case 0x001607e0u:set(2,ps2BattleActionCreation_001607E0(cpu(4)));break;case 0x00160ea0u:set(2,ps2BattleActionCreation_00160EA0(cpu(4)));break;case 0x00161448u:set(2,ps2BattleActionCreation_00161448(cpu(4)));break;case 0x001619f0u:set(2,ps2BattleActionCreation_001619F0(cpu(4)));break;case 0x001621c8u:set(2,ps2BattleActionCreation_001621C8(cpu(4)));break;case 0x00162498u:set(2,ps2BattleActionCreation_00162498(cpu(4)));break;case 0x00162fc8u:set(2,ps2BattleActionCreation_00162FC8(cpu(4)));break;case 0x00163628u:set(2,ps2BattleActionCreation_00163628(cpu(4)));break;default:fprintf(stderr,"Unsupported actual emitter copy %08x\n",(uint32_t)target);abort();}}
/* 0016505c: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00165060: addiu a1,s0,0x10 */ set(5,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 00165064: jal 0x0015cdb0 */ set(31,0x0016506cu);/* delay 00165068 */ set(17,cpu(2));set(2,ps2BattleActionCreation_0015CDB0(cpu(4),cpu(5)));
/* 0016506c: lwc1 f12,0x10(s1) */ f[12]=word(ea(17,(int32_t)UINT32_C(0x00000010)));
/* 00165070: move s0,v0 */ set(16,cpu(2));
/* 00165074: lwc1 f13,0x14(s1) */ f[13]=word(ea(17,(int32_t)UINT32_C(0x00000014)));
/* 00165078: jal 0x0015d038 */ set(31,0x00165080u);/* delay 0016507c */ set(4,cpu(16));ps2EffectBillboardSetScale_0015D038(cpu(4),real(f[12]),real(f[13]));
/* 00165080: move a0,s0 */ set(4,cpu(16));
/* 00165084: jal 0x0015d088 */ set(31,0x0016508cu);/* delay 00165088 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000002c))));ps2BattleActionCreation_0015D088(cpu(4),cpu(5));
/* 0016508c: jal 0x0015d3e8 */ set(31,0x00165094u);/* delay 00165090 */ set(4,cpu(16));ps2BattleActionCreation_0015D3E8(cpu(4));
/* 00165094: b 0x001650c0 */ /* delay 00165098 */ sw(ea(17,(int32_t)UINT32_C(0x000000f4)),(uint32_t)cpu(16));goto L_001650c0;
L_001650a0:;
/* 001650a0: addu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(18)));
/* 001650a4: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001650a8: lui v0,0x31 */ set(2,sx(UINT32_C(0x00310000)));
/* 001650ac: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001650b0: lw v0,0x7270(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00007270)));
/* 001650b4: jalr v0 */ {uint64_t target=cpu(2);set(31,0x001650bcu);/* delay 001650b8 */ set(4,cpu(17));switch((uint32_t)target){case 0x0015e2a8u:set(2,ps2BattleActionCreation_0015E2A8(cpu(4)));break;case 0x0015e8f8u:set(2,ps2BattleActionCreation_0015E8F8(cpu(4)));break;case 0x0015ef48u:set(2,ps2BattleActionCreation_0015EF48(cpu(4)));break;case 0x0015faf0u:set(2,ps2BattleActionCreation_0015FAF0(cpu(4)));break;case 0x001600d0u:set(2,ps2BattleActionCreation_001600D0(cpu(4)));break;case 0x001607e0u:set(2,ps2BattleActionCreation_001607E0(cpu(4)));break;case 0x00160ea0u:set(2,ps2BattleActionCreation_00160EA0(cpu(4)));break;case 0x00161448u:set(2,ps2BattleActionCreation_00161448(cpu(4)));break;case 0x001619f0u:set(2,ps2BattleActionCreation_001619F0(cpu(4)));break;case 0x001621c8u:set(2,ps2BattleActionCreation_001621C8(cpu(4)));break;case 0x00162498u:set(2,ps2BattleActionCreation_00162498(cpu(4)));break;case 0x00162fc8u:set(2,ps2BattleActionCreation_00162FC8(cpu(4)));break;case 0x00163628u:set(2,ps2BattleActionCreation_00163628(cpu(4)));break;default:fprintf(stderr,"Unsupported actual emitter copy %08x\n",(uint32_t)target);abort();}}
/* 001650bc: move s1,v0 */ set(17,cpu(2));
L_001650c0:;
/* 001650c0: sh s2,0x140(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000140)),(uint16_t)cpu(18));
/* 001650c4: move v0,s1 */ set(2,cpu(17));
/* 001650c8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001650cc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001650d0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001650d4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001650d8: jr ra */ {uint64_t target=cpu(31);/* delay 001650dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015EF48(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015ef48u);
uint64_t incoming=cpu(31);
/* 0015ef48: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015ef4c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015ef50: move s0,a0 */ set(16,cpu(4));
/* 0015ef54: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015ef58: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015ef5c: jal 0x002a8af8 */ set(31,0x0015ef64u);/* delay 0015ef60 */ set(4,sx(UINT32_C(0x00000180)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015ef64: move s1,v0 */ set(17,cpu(2));
/* 0015ef68: move a1,zero */ set(5,cpu(0));
/* 0015ef6c: move a0,s1 */ set(4,cpu(17));
/* 0015ef70: jal 0x002d4558 */ set(31,0x0015ef78u);/* delay 0015ef74 */ set(6,sx(UINT32_C(0x00000180)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 0015ef78: move a0,s1 */ set(4,cpu(17));
/* 0015ef7c: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0015ef80: jal 0x002d43a4 */ set(31,0x0015ef88u);/* delay 0015ef84 */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015ef88: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0015ef8c: li a2,0x30 */ set(6,sx(UINT32_C(0x00000030)));
/* 0015ef90: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 0015ef94: jal 0x002d43a4 */ set(31,0x0015ef9cu);/* delay 0015ef98 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015ef9c: jal 0x0015df58 */ set(31,0x0015efa4u);/* delay 0015efa0 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 0015efa4: jal 0x0015eeb0 */ set(31,0x0015efacu);/* delay 0015efa8 */ set(4,cpu(17));ps2EffectPartControlNative_0015EEB0(cpu(4));
/* 0015efac: move v0,s1 */ set(2,cpu(17));
/* 0015efb0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015efb4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015efb8: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015efbc: jr ra */ {uint64_t target=cpu(31);/* delay 0015efc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionCreation_0015DF58(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015df58u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0015df58: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 0015df5c: li v0,0x150 */ set(2,sx(UINT32_C(0x00000150)));
/* 0015df60: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0015df64: move s0,a0 */ set(16,cpu(4));
/* 0015df68: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0015df6c: sw v0,0xa0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000a0)),(uint32_t)cpu(2));
/* 0015df70: jal 0x0015dec0 */ set(31,0x0015df78u);/* delay 0015df74 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000020)));set(2,ps2BattleActionCreation_0015DEC0(cpu(4)));
/* 0015df78: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 0015df7c: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 0015df80: beq a0,v1,0x0015dfb0 */ {int taken=(cpu(4)==cpu(3));/* delay 0015df84 */ sw(ea(16,(int32_t)UINT32_C(0x000000f8)),(uint32_t)cpu(2));if(taken){goto L_0015dfb0;}}
/* 0015df88: jal 0x0015cf98 */ set(31,0x0015df90u);/* delay 0015df8c */ set(2,ps2BattleActionCreation_0015CF98(cpu(4)));
/* 0015df90: lwc1 f12,0x10(s0) */ f[12]=word(ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0015df94: sw v0,0xf4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000f4)),(uint32_t)cpu(2));
/* 0015df98: move a0,v0 */ set(4,cpu(2));
/* 0015df9c: jal 0x0015d038 */ set(31,0x0015dfa4u);/* delay 0015dfa0 */ f[13]=word(ea(16,(int32_t)UINT32_C(0x00000014)));ps2EffectBillboardSetScale_0015D038(cpu(4),real(f[12]),real(f[13]));
/* 0015dfa4: lw a0,0xf4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000f4)));
/* 0015dfa8: jal 0x0015d088 */ set(31,0x0015dfb0u);/* delay 0015dfac */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002c))));ps2BattleActionCreation_0015D088(cpu(4),cpu(5));
L_0015dfb0:;
/* 0015dfb0: lw a1,0x24(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000024)));
/* 0015dfb4: jal 0x00163f00 */ set(31,0x0015dfbcu);/* delay 0015dfb8 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000048)));ps2BattleActionCreation_00163F00(cpu(4),cpu(5));
/* 0015dfbc: lhu v1,0x30(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000030))));
/* 0015dfc0: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0015dfc4: beq v1,v0,0x0015e018 */ {int taken=(cpu(3)==cpu(2));/* delay 0015dfc8 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_0015e018;}}
/* 0015dfcc: beq v0,zero,0x0015dfe8 */ {int taken=(cpu(2)==cpu(0));/* delay 0015dfd0 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_0015dfe8;}}
/* 0015dfd4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0015dfd8: beql v1,v0,0x0015e000 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 0015dfdc */ lw(4,ea(16,(int32_t)UINT32_C(0x00000020)));goto L_0015e000;}}
/* 0015dfe0: b 0x0015e0e8 */ /* delay 0015dfe4 */ lw(2,ea(16,(int32_t)UINT32_C(0x000000a4)));goto L_0015e0e8;
L_0015dfe8:;
/* 0015dfe8: beq v1,v0,0x0015e058 */ {int taken=(cpu(3)==cpu(2));/* delay 0015dfec */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_0015e058;}}
/* 0015dff0: beql v1,v0,0x0015e0a0 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 0015dff4 */ lw(9,ea(16,(int32_t)UINT32_C(0x0000003c)));goto L_0015e0a0;}}
/* 0015dff8: b 0x0015e0e8 */ /* delay 0015dffc */ lw(2,ea(16,(int32_t)UINT32_C(0x000000a4)));goto L_0015e0e8;
L_0015e000:;
/* 0015e000: addiu a2,s0,0xf4 */ set(6,sx((uint32_t)cpu(16)+UINT32_C(0x000000f4)));
/* 0015e004: jal 0x00164420 */ set(31,0x0015e00cu);/* delay 0015e008 */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000034))));set(2,ps2PolygonHistoryCreate(cpu(4),cpu(5),cpu(6)));
/* 0015e00c: b 0x0015e0e4 */ /* delay 0015e010 */ sw(ea(16,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(2));goto L_0015e0e4;
L_0015e018:;
/* 0015e018: jal 0x00165a38 */ set(31,0x0015e020u);/* delay 0015e01c */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000034))));set(2,ps2PolygonSampleLookup(cpu(4)));
/* 0015e020: lw a0,0x20(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 0015e024: lhu a1,0x34(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000034))));
/* 0015e028: move a2,v0 */ set(6,cpu(2));
/* 0015e02c: jal 0x00165eb8 */ set(31,0x0015e034u);/* delay 0015e030 */ set(7,cpu(0));set(2,ps2BattleActionPolygonCreate_00165EB8(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 0015e034: lw a2,0x3c(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000003c)));
/* 0015e038: sw v0,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
/* 0015e03c: move a0,v0 */ set(4,cpu(2));
/* 0015e040: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0015e044: jal 0x00167898 */ set(31,0x0015e04cu);/* delay 0015e048 */ set(7,cpu(6));ps2PolygonVertexColors(cpu(4),cpu(5),cpu(6),cpu(7));
/* 0015e04c: b 0x0015e090 */ /* delay 0015e050 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000040)));goto L_0015e090;
L_0015e058:;
/* 0015e058: jal 0x00165a38 */ set(31,0x0015e060u);/* delay 0015e05c */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000034))));set(2,ps2PolygonSampleLookup(cpu(4)));
/* 0015e060: lw a0,0x20(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 0015e064: lhu a1,0x34(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000034))));
/* 0015e068: move a2,v0 */ set(6,cpu(2));
/* 0015e06c: jal 0x00165eb8 */ set(31,0x0015e074u);/* delay 0015e070 */ set(7,sx(UINT32_C(0x00000001)));set(2,ps2BattleActionPolygonCreate_00165EB8(cpu(4),cpu(5),cpu(6),cpu(7)));
/* 0015e074: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0015e078: sw v0,0x44(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
/* 0015e07c: move a0,v0 */ set(4,cpu(2));
/* 0015e080: lw a2,0x3c(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000003c)));
/* 0015e084: jal 0x00167898 */ set(31,0x0015e08cu);/* delay 0015e088 */ lw(7,ea(16,(int32_t)UINT32_C(0x00000040)));ps2PolygonVertexColors(cpu(4),cpu(5),cpu(6),cpu(7));
/* 0015e08c: lw a0,0x44(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000044)));
L_0015e090:;
/* 0015e090: jal 0x00167890 */ set(31,0x0015e098u);/* delay 0015e094 */ set(5,half(ea(16,(int32_t)UINT32_C(0x0000002c))));ps2BattleActionPolygonSetMode_00167890(cpu(4),cpu(5));
/* 0015e098: b 0x0015e0e8 */ /* delay 0015e09c */ lw(2,ea(16,(int32_t)UINT32_C(0x000000a4)));goto L_0015e0e8;
L_0015e0a0:;
/* 0015e0a0: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 0015e0a4: lw t0,0x40(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000040)));
/* 0015e0a8: li a3,0xa */ set(7,sx(UINT32_C(0x0000000a)));
/* 0015e0ac: lhu v0,0x34(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000034))));
/* 0015e0b0: move a0,sp */ set(4,cpu(29));
/* 0015e0b4: lw a1,0x20(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 0015e0b8: lhu v1,0x2c(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000002c))));
/* 0015e0bc: sw a2,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(6));
/* 0015e0c0: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 0015e0c4: sw a3,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(7));
/* 0015e0c8: sw v1,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
/* 0015e0cc: sw t1,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(9));
/* 0015e0d0: sw t0,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(8));
/* 0015e0d4: sw t1,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(9));
/* 0015e0d8: jal 0x001a3510 */ set(31,0x0015e0e0u);/* delay 0015e0dc */ sw(ea(29,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(8));set(2,Eff_ModelTrackPolyListCreate(cpu(4),cpu(5)));
/* 0015e0e0: sw v0,0x44(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
L_0015e0e4:;
/* 0015e0e4: lw v0,0xa4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x000000a4)));
L_0015e0e8:;
/* 0015e0e8: addiu v1,s0,0xb0 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x000000b0)));
/* 0015e0ec: sw v0,0xfc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000fc)),(uint32_t)cpu(2));
/* 0015e0f0: lqc2 vf28,0x0(v1) */ loadVu(28,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0015e0f4: lqc2 vf29,0x10(v1) */ loadVu(29,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0015e0f8: lqc2 vf30,0x20(v1) */ loadVu(30,ea(3,(int32_t)UINT32_C(0x00000020)));
/* 0015e0fc: lqc2 vf31,0x30(v1) */ loadVu(31,ea(3,(int32_t)UINT32_C(0x00000030)));
/* 0015e100: addiu v0,s0,0x100 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000100)));
/* 0015e104: sqc2 vf28,0x0(v0) */ storeVu(28,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0015e108: sqc2 vf29,0x10(v0) */ storeVu(29,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 0015e10c: sqc2 vf30,0x20(v0) */ storeVu(30,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 0015e110: sqc2 vf31,0x30(v0) */ storeVu(31,ea(2,(int32_t)UINT32_C(0x00000030)));
/* 0015e114: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
/* 0015e118: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0015e11c: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 0015e120: sh v0,0x142(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000142)),(uint16_t)cpu(2));
/* 0015e124: sw v1,0xf0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000f0)),(uint32_t)cpu(3));
/* 0015e128: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0015e12c: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0015e130: jr ra */ {uint64_t target=cpu(31);/* delay 0015e134 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionCreation_0015DEC0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015dec0u);
uint64_t incoming=cpu(31);
/* 0015dec0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015dec4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015dec8: move s2,a0 */ set(18,cpu(4));
/* 0015decc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015ded0: sll s1,s2,0x6 */ set(17,sx((uint32_t)cpu(18)<<6));
/* 0015ded4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015ded8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015dedc: jal 0x002a9038 */ set(31,0x0015dee4u);/* delay 0015dee0 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000008)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 0015dee4: move s0,v0 */ set(16,cpu(2));
/* 0015dee8: jal 0x002a9688 */ set(31,0x0015def0u);/* delay 0015deec */ set(4,cpu(16));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 0015def0: addu v1,v0,s1 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 0015def4: sw s0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 0015def8: blez s2,0x0015df24 */ {int taken=((int64_t)cpu(18)<=0);/* delay 0015defc */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_0015df24;}}
/* 0015df00: move a0,s2 */ set(4,cpu(18));
/* 0015df04: nop  */ 
L_0015df08:;
/* 0015df08: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 0015df0c: sw zero,0x20(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 0015df10: sw zero,0x24(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 0015df14: nop  */ 
/* 0015df18: nop  */ 
/* 0015df1c: bne a0,zero,0x0015df08 */ {int taken=(cpu(4)!=cpu(0));/* delay 0015df20 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000040)));if(taken){goto L_0015df08;}}
L_0015df24:;
/* 0015df24: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015df28: move v0,v1 */ set(2,cpu(3));
/* 0015df2c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015df30: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015df34: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015df38: jr ra */ {uint64_t target=cpu(31);/* delay 0015df3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015CF98(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015cf98u);
uint64_t incoming=cpu(31);
/* 0015cf98: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0015cf9c: move a1,zero */ set(5,cpu(0));
/* 0015cfa0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015cfa4: move s0,a0 */ set(16,cpu(4));
/* 0015cfa8: sll v0,s0,0x3 */ set(2,sx((uint32_t)cpu(16)<<3));
/* 0015cfac: lui a0,0x31 */ set(4,sx(UINT32_C(0x00310000)));
/* 0015cfb0: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0015cfb4: lh a0,0x6ff4(a0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00006ff4))));
/* 0015cfb8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015cfbc: jal 0x0015cdb0 */ set(31,0x0015cfc4u);/* delay 0015cfc0 */ set(16,sx((uint32_t)cpu(16)<<2));set(2,ps2BattleActionCreation_0015CDB0(cpu(4),cpu(5)));
/* 0015cfc4: lui a0,0x57 */ set(4,sx(UINT32_C(0x00570000)));
/* 0015cfc8: addu a0,a0,s0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(16)));
/* 0015cfcc: lw a0,-0x67b8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0xffff9848)));
/* 0015cfd0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015cfd4: lw a1,0x30(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 0015cfd8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015cfdc: lw v1,0x8(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 0015cfe0: sw a1,0x30(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(5));
/* 0015cfe4: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0015cfe8: sw v1,0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 0015cfec: jr ra */ {uint64_t target=cpu(31);/* delay 0015cff0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015CDB0(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x0015cdb0u);
uint64_t incoming=cpu(31);
/* 0015cdb0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0015cdb4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015cdb8: move s3,a0 */ set(19,cpu(4));
/* 0015cdbc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015cdc0: sll s1,s3,0x1 */ set(17,sx((uint32_t)cpu(19)<<1));
/* 0015cdc4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015cdc8: lui s2,0x31 */ set(18,sx(UINT32_C(0x00310000)));
/* 0015cdcc: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 0015cdd0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015cdd4: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0015cdd8: sll s1,s1,0x2 */ set(17,sx((uint32_t)cpu(17)<<2));
/* 0015cddc: addiu s2,s2,0x7080 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00007080)));
/* 0015cde0: move a0,a1 */ set(4,cpu(5));
/* 0015cde4: addu v1,s1,s2 */ set(3,sx((uint32_t)cpu(17)+(uint32_t)cpu(18)));
/* 0015cde8: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0015cdec: jalr v0 */ {uint64_t target=cpu(2);set(31,0x0015cdf4u);/* delay 0015cdf0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(17)));switch((uint32_t)target){case 0x0015c230u:set(2,ps2BattleActionCreation_0015C230(cpu(4)));break;case 0x0015c2c8u:set(2,ps2BillAnimationAllocate(cpu(4)));break;default:fprintf(stderr,"Unsupported actual billboard factory %08x\n",(uint32_t)target);abort();}}
/* 0015cdf4: move s0,v0 */ set(16,cpu(2));
/* 0015cdf8: jal 0x0015c1e8 */ set(31,0x0015ce00u);/* delay 0015cdfc */ set(4,cpu(16));ps2BattleActionCreation_0015C1E8(cpu(4));
/* 0015ce00: sh s3,0x2c(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(19));
/* 0015ce04: lw v1,0x4(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0015ce08: move v0,s0 */ set(2,cpu(16));
/* 0015ce0c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015ce10: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 0015ce14: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015ce18: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015ce1c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0015ce20: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0015ce24: jr ra */ {uint64_t target=cpu(31);/* delay 0015ce28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015C230(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015c230u);
uint64_t incoming=cpu(31);
/* 0015c230: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015c234: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015c238: move s0,a0 */ set(16,cpu(4));
/* 0015c23c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015c240: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015c244: jal 0x002a8af8 */ set(31,0x0015c24cu);/* delay 0015c248 */ set(4,sx(UINT32_C(0x00000034)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015c24c: move s1,v0 */ set(17,cpu(2));
/* 0015c250: beq s0,zero,0x0015c264 */ {int taken=(cpu(16)==cpu(0));/* delay 0015c254 */ set(4,cpu(16));if(taken){goto L_0015c264;}}
/* 0015c258: jal 0x0015b1b0 */ set(31,0x0015c260u);/* delay 0015c25c */ set(2,ps2BillboardTextureResourceCreate(cpu(4)));
/* 0015c260: sw v0,0x30(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));
L_0015c264:;
/* 0015c264: move v0,s1 */ set(2,cpu(17));
/* 0015c268: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015c26c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015c270: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015c274: jr ra */ {uint64_t target=cpu(31);/* delay 0015c278 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
void ps2BattleActionCreation_0015AF88(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015af88u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 0015af88: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0015af8c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0015af90: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0015af94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015af98: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015af9c: lwc1 f1,0xc(a0) */ f[1]=word(ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 0015afa0: c.eq.S f1,f0 */ condition=EE_FPU_COMPARE_S(f[1],f[0],0);
/* 0015afa4: bc1f 0x0015affc */ {int taken=(!condition);/* delay 0015afa8 */ set(5,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));if(taken){goto L_0015affc;}}
/* 0015afac: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0015afb0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0015afb4: beql v1,v0,0x0015afe0 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 0015afb8 */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));goto L_0015afe0;}}
/* 0015afbc: beq v1,zero,0x0015afd8 */ {int taken=(cpu(3)==cpu(0));/* delay 0015afc0 */ set(2,sx(UINT32_C(0x000000ac)));if(taken){goto L_0015afd8;}}
/* 0015afc4: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0015afc8: beq v1,v0,0x0015aff8 */ {int taken=(cpu(3)==cpu(2));/* delay 0015afcc */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_0015aff8;}}
/* 0015afd0: b 0x0015affc */ /* delay 0015afd4 */ goto L_0015affc;
L_0015afd8:;
/* 0015afd8: b 0x0015affc */ /* delay 0015afdc */ sw(ea(5,(int32_t)UINT32_C(0x000000a0)),(uint32_t)cpu(2));goto L_0015affc;
L_0015afe0:;
/* 0015afe0: li v1,0xac */ set(3,sx(UINT32_C(0x000000ac)));
/* 0015afe4: addu v0,a1,v0 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 0015afe8: addiu a1,v0,0x10 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 0015afec: b 0x0015affc */ /* delay 0015aff0 */ sw(ea(5,(int32_t)UINT32_C(0x000000a0)),(uint32_t)cpu(3));goto L_0015affc;
L_0015aff8:;
/* 0015aff8: sw v0,0x18(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
L_0015affc:;
/* 0015affc: lwc1 f0,-0x7bc4(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff843c)));
/* 0015b000: c.le.S f1,f0 */ condition=EE_FPU_COMPARE_S(f[1],f[0],2);
/* 0015b004: bc1f 0x0015b090 */ {int taken=(!condition);/* delay 0015b008 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0015b090;}}
/* 0015b00c: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0015b010: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0015b014: bne v1,v0,0x0015b050 */ {int taken=(cpu(3)!=cpu(2));/* delay 0015b018 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_0015b050;}}
/* 0015b01c: lw v0,0x4(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 0015b020: lwc1 f3,-0x7bc0(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffff8440)));
/* 0015b024: addu v0,a1,v0 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 0015b028: addiu a1,v0,0x10 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 0015b02c: lwc1 f0,0x8c(a1) */ f[0]=word(ea(5,(int32_t)UINT32_C(0x0000008c)));
/* 0015b030: lwc1 f1,0x24(a1) */ f[1]=word(ea(5,(int32_t)UINT32_C(0x00000024)));
/* 0015b034: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0015b038: lwc1 f2,0x10(a1) */ f[2]=word(ea(5,(int32_t)UINT32_C(0x00000010)));
/* 0015b03c: mul.S f0,f0,f3 */ f[0]=mul(f[0],f[3]);
/* 0015b040: mul.S f0,f0,f1 */ f[0]=mul(f[0],f[1]);
/* 0015b044: add.S f0,f0,f2 */ f[0]=add(f[0],f[2]);
/* 0015b048: swc1 f0,0x8c(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000008c)),f[0]);
/* 0015b04c: sltiu v0,v1,0x2 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
L_0015b050:;
/* 0015b050: beq v0,zero,0x0015b090 */ {int taken=(cpu(2)==cpu(0));/* delay 0015b054 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0015b090;}}
/* 0015b058: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 0015b05c: bne v0,zero,0x0015b094 */ {int taken=(cpu(2)!=cpu(0));/* delay 0015b060 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_0015b094;}}
/* 0015b064: lwc1 f12,0xc(a0) */ f[12]=word(ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 0015b068: lui s0,0x53 */ set(16,sx(UINT32_C(0x00530000)));
/* 0015b06c: jal 0x002d1550 */ set(31,0x0015b074u);/* delay 0015b070 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00002b40)));set(2,ps2EffectSoftDoubleFromFloat_002D1550(real(f[12])));
/* 0015b074: move a0,s0 */ set(4,cpu(16));
/* 0015b078: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015b07c: move a1,v0 */ set(5,cpu(2));
/* 0015b080: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015b084: j 0x002d4748 */ /* delay 0015b088 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleActionPrintf_002D4748(cpu(4)));return;
L_0015b090:;
/* 0015b090: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
L_0015b094:;
/* 0015b094: jr ra */ {uint64_t target=cpu(31);/* delay 0015b098 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
void ps2BattleActionCreation_00163F00(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x00163f00u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
uint32_t condition=0;
/* 00163f00: move t0,a0 */ set(8,cpu(4));
/* 00163f04: lui v0,0xff */ set(2,sx(UINT32_C(0x00ff0000)));
/* 00163f08: lw a2,0x4(t0) */ lw(6,ea(8,(int32_t)UINT32_C(0x00000004)));
/* 00163f0c: move t1,a1 */ set(9,cpu(5));
/* 00163f10: lw a0,0x8(t0) */ lw(4,ea(8,(int32_t)UINT32_C(0x00000008)));
/* 00163f14: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 00163f18: lw v1,0xc(t0) */ lw(3,ea(8,(int32_t)UINT32_C(0x0000000c)));
/* 00163f1c: and a2,a2,v0 */ set(6,cpu(6)&cpu(2));
/* 00163f20: lw a1,0x10(t0) */ lw(5,ea(8,(int32_t)UINT32_C(0x00000010)));
/* 00163f24: and a0,a0,v0 */ set(4,cpu(4)&cpu(2));
/* 00163f28: lw a3,0x14(t0) */ lw(7,ea(8,(int32_t)UINT32_C(0x00000014)));
/* 00163f2c: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 00163f30: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 00163f34: sw a2,0x4(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));
/* 00163f38: sw a0,0x8(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 00163f3c: sw v1,0xc(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 00163f40: blez a3,0x00163f5c */ {int taken=((int64_t)cpu(7)<=0);/* delay 00163f44 */ sw(ea(8,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(5));if(taken){goto L_00163f5c;}}
/* 00163f48: divu a1,a3 */ creationDivide((uint32_t)cpu(5),(uint32_t)cpu(7));
/* 00163f4c: beql a3,zero,0x00163f54 */ {int taken=(cpu(7)==cpu(0));if(taken){/* delay 00163f50 */ nocturneCompilerArithmeticTrap(7u);goto L_00163f54;}}
L_00163f54:;
/* 00163f54: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00163f58: sw v0,0x3c(t0) */ sw(ea(8,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(2));
L_00163f5c:;
/* 00163f5c: lw v1,0x18(t0) */ lw(3,ea(8,(int32_t)UINT32_C(0x00000018)));
/* 00163f60: blez v1,0x00163f7c */ {int taken=((int64_t)cpu(3)<=0);/* delay 00163f64 */ sw(ea(8,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(5));if(taken){goto L_00163f7c;}}
/* 00163f68: divu a1,v1 */ creationDivide((uint32_t)cpu(5),(uint32_t)cpu(3));
/* 00163f6c: beql v1,zero,0x00163f74 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00163f70 */ nocturneCompilerArithmeticTrap(7u);goto L_00163f74;}}
L_00163f74:;
/* 00163f74: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00163f78: sw v0,0x40(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_00163f7c:;
/* 00163f7c: lw a3,0x0(t0) */ lw(7,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 00163f80: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00163f84: beq a3,v0,0x001642c8 */ {int taken=(cpu(7)==cpu(2));/* delay 00163f88 */ sw(ea(8,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(9));if(taken){goto L_001642c8;}}
/* 00163f8c: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00163f90: bne a3,v0,0x00163fa0 */ {int taken=(cpu(7)!=cpu(2));/* delay 00163f94 */ set(2,sx((uint32_t)((int32_t)cpu(9)>>1)));if(taken){goto L_00163fa0;}}
/* 00163f98: b 0x00163fa4 */ /* delay 00163f9c */ sw(ea(8,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(9));goto L_00163fa4;
L_00163fa0:;
/* 00163fa0: sw v0,0x20(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
L_00163fa4:;
/* 00163fa4: lwc1 f2,0x20(t0) */ f[2]=word(ea(8,(int32_t)UINT32_C(0x00000020)));
/* 00163fa8: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 00163fac: clear f0 */ f[0]=0;
/* 00163fb0: c.eq.S f2,f0 */ condition=EE_FPU_COMPARE_S(f[2],f[0],0);
/* 00163fb4: bc1f 0x00163fc4 */ {int taken=(!condition);/* delay 00163fb8 */ lw(5,ea(8,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_00163fc4;}}
/* 00163fbc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00163fc0: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
L_00163fc4:;
/* 00163fc4: lw a2,0x4(t0) */ lw(6,ea(8,(int32_t)UINT32_C(0x00000004)));
/* 00163fc8: andi v0,a1,0xff */ set(2,cpu(5)&UINT32_C(0x000000ff));
/* 00163fcc: bltz v0,0x00163fe8 */ {int taken=((int64_t)cpu(2)<0);/* delay 00163fd0 */ set(4,cpu(5));if(taken){goto L_00163fe8;}}
/* 00163fd4: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00163fd8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00163fdc: b 0x00164004 */ /* delay 00163fe0 */ set(2,cpu(6)&UINT32_C(0x000000ff));goto L_00164004;
L_00163fe8:;
/* 00163fe8: srl v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)>>1));
/* 00163fec: andi v0,a1,0x1 */ set(2,cpu(5)&UINT32_C(0x00000001));
/* 00163ff0: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00163ff4: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00163ff8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00163ffc: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
/* 00164000: andi v0,a2,0xff */ set(2,cpu(6)&UINT32_C(0x000000ff));
L_00164004:;
/* 00164004: bltz v0,0x00164020 */ {int taken=((int64_t)cpu(2)<0);/* delay 00164008 */ set(3,sx((uint32_t)cpu(2)>>1));if(taken){goto L_00164020;}}
/* 0016400c: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00164010: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164014: b 0x00164038 */ /* delay 00164018 */ f[0]=sub(f[1],f[0]);goto L_00164038;
L_00164020:;
/* 00164020: andi v0,a2,0x1 */ set(2,cpu(6)&UINT32_C(0x00000001));
/* 00164024: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00164028: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0016402c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164030: add.S f0,f0,f0 */ f[0]=add(f[0],f[0]);
/* 00164034: sub.S f0,f1,f0 */ f[0]=sub(f[1],f[0]);
L_00164038:;
/* 00164038: srl v0,a0,0x8 */ set(2,sx((uint32_t)cpu(4)>>8));
/* 0016403c: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 00164040: nop  */ 
/* 00164044: nop  */ 
/* 00164048: div.S f0,f0,f2 */ f[0]=divs(f[0],f[2]);
/* 0016404c: bltz v1,0x00164068 */ {int taken=((int64_t)cpu(3)<0);/* delay 00164050 */ sw(ea(8,(int32_t)UINT32_C(0x00000024)),f[0]);if(taken){goto L_00164068;}}
/* 00164054: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 00164058: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0016405c: b 0x00164084 */ /* delay 00164060 */ set(2,sx((uint32_t)cpu(6)>>8));goto L_00164084;
L_00164068:;
/* 00164068: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0016406c: srl v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)>>1));
/* 00164070: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00164074: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00164078: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0016407c: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
/* 00164080: srl v0,a2,0x8 */ set(2,sx((uint32_t)cpu(6)>>8));
L_00164084:;
/* 00164084: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 00164088: bltz v1,0x001640a0 */ {int taken=((int64_t)cpu(3)<0);/* delay 0016408c */ set(2,cpu(2)&UINT32_C(0x00000001));if(taken){goto L_001640a0;}}
/* 00164090: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00164094: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164098: b 0x001640b8 */ /* delay 0016409c */ f[0]=sub(f[1],f[0]);goto L_001640b8;
L_001640a0:;
/* 001640a0: srl v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)>>1));
/* 001640a4: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 001640a8: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 001640ac: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 001640b0: add.S f0,f0,f0 */ f[0]=add(f[0],f[0]);
/* 001640b4: sub.S f0,f1,f0 */ f[0]=sub(f[1],f[0]);
L_001640b8:;
/* 001640b8: srl v0,a0,0x10 */ set(2,sx((uint32_t)cpu(4)>>16));
/* 001640bc: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 001640c0: nop  */ 
/* 001640c4: nop  */ 
/* 001640c8: div.S f0,f0,f2 */ f[0]=divs(f[0],f[2]);
/* 001640cc: bltz v1,0x001640e8 */ {int taken=((int64_t)cpu(3)<0);/* delay 001640d0 */ sw(ea(8,(int32_t)UINT32_C(0x0000002c)),f[0]);if(taken){goto L_001640e8;}}
/* 001640d4: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 001640d8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 001640dc: b 0x00164104 */ /* delay 001640e0 */ set(2,sx((uint32_t)cpu(6)>>16));goto L_00164104;
L_001640e8:;
/* 001640e8: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 001640ec: srl v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)>>1));
/* 001640f0: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 001640f4: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 001640f8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 001640fc: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
/* 00164100: srl v0,a2,0x10 */ set(2,sx((uint32_t)cpu(6)>>16));
L_00164104:;
/* 00164104: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 00164108: bltz v1,0x00164120 */ {int taken=((int64_t)cpu(3)<0);/* delay 0016410c */ set(2,cpu(2)&UINT32_C(0x00000001));if(taken){goto L_00164120;}}
/* 00164110: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00164114: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164118: b 0x00164138 */ /* delay 0016411c */ f[0]=sub(f[1],f[0]);goto L_00164138;
L_00164120:;
/* 00164120: srl v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)>>1));
/* 00164124: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00164128: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0016412c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164130: add.S f0,f0,f0 */ f[0]=add(f[0],f[0]);
/* 00164134: sub.S f0,f1,f0 */ f[0]=sub(f[1],f[0]);
L_00164138:;
/* 00164138: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0016413c: nop  */ 
/* 00164140: nop  */ 
/* 00164144: div.S f0,f0,f2 */ f[0]=divs(f[0],f[2]);
/* 00164148: beq a3,v0,0x001642c8 */ {int taken=(cpu(7)==cpu(2));/* delay 0016414c */ sw(ea(8,(int32_t)UINT32_C(0x00000034)),f[0]);if(taken){goto L_001642c8;}}
/* 00164150: lw a0,0xc(t0) */ lw(4,ea(8,(int32_t)UINT32_C(0x0000000c)));
/* 00164154: andi v0,a0,0xff */ set(2,cpu(4)&UINT32_C(0x000000ff));
/* 00164158: bltz v0,0x00164170 */ {int taken=((int64_t)cpu(2)<0);/* delay 0016415c */ set(3,sx((uint32_t)cpu(2)>>1));if(taken){goto L_00164170;}}
/* 00164160: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00164164: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00164168: b 0x00164188 */ /* delay 0016416c */ set(2,cpu(5)&UINT32_C(0x000000ff));goto L_00164188;
L_00164170:;
/* 00164170: andi v0,a0,0x1 */ set(2,cpu(4)&UINT32_C(0x00000001));
/* 00164174: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00164178: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 0016417c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00164180: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
/* 00164184: andi v0,a1,0xff */ set(2,cpu(5)&UINT32_C(0x000000ff));
L_00164188:;
/* 00164188: bltz v0,0x001641a0 */ {int taken=((int64_t)cpu(2)<0);/* delay 0016418c */ set(3,sx((uint32_t)cpu(2)>>1));if(taken){goto L_001641a0;}}
/* 00164190: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00164194: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164198: b 0x001641b8 */ /* delay 0016419c */ f[0]=sub(f[1],f[0]);goto L_001641b8;
L_001641a0:;
/* 001641a0: andi v0,a1,0x1 */ set(2,cpu(5)&UINT32_C(0x00000001));
/* 001641a4: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 001641a8: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 001641ac: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 001641b0: add.S f0,f0,f0 */ f[0]=add(f[0],f[0]);
/* 001641b4: sub.S f0,f1,f0 */ f[0]=sub(f[1],f[0]);
L_001641b8:;
/* 001641b8: srl v0,a0,0x8 */ set(2,sx((uint32_t)cpu(4)>>8));
/* 001641bc: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 001641c0: nop  */ 
/* 001641c4: nop  */ 
/* 001641c8: div.S f0,f0,f2 */ f[0]=divs(f[0],f[2]);
/* 001641cc: bltz v1,0x001641e8 */ {int taken=((int64_t)cpu(3)<0);/* delay 001641d0 */ sw(ea(8,(int32_t)UINT32_C(0x00000028)),f[0]);if(taken){goto L_001641e8;}}
/* 001641d4: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 001641d8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 001641dc: b 0x00164204 */ /* delay 001641e0 */ set(2,sx((uint32_t)cpu(5)>>8));goto L_00164204;
L_001641e8:;
/* 001641e8: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 001641ec: srl v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)>>1));
/* 001641f0: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 001641f4: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 001641f8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 001641fc: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
/* 00164200: srl v0,a1,0x8 */ set(2,sx((uint32_t)cpu(5)>>8));
L_00164204:;
/* 00164204: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 00164208: bltz v1,0x00164220 */ {int taken=((int64_t)cpu(3)<0);/* delay 0016420c */ set(2,cpu(2)&UINT32_C(0x00000001));if(taken){goto L_00164220;}}
/* 00164210: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00164214: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164218: b 0x00164238 */ /* delay 0016421c */ f[0]=sub(f[1],f[0]);goto L_00164238;
L_00164220:;
/* 00164220: srl v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)>>1));
/* 00164224: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00164228: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0016422c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164230: add.S f0,f0,f0 */ f[0]=add(f[0],f[0]);
/* 00164234: sub.S f0,f1,f0 */ f[0]=sub(f[1],f[0]);
L_00164238:;
/* 00164238: srl v0,a0,0x10 */ set(2,sx((uint32_t)cpu(4)>>16));
/* 0016423c: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 00164240: nop  */ 
/* 00164244: nop  */ 
/* 00164248: div.S f0,f0,f2 */ f[0]=divs(f[0],f[2]);
/* 0016424c: bltz v1,0x00164268 */ {int taken=((int64_t)cpu(3)<0);/* delay 00164250 */ sw(ea(8,(int32_t)UINT32_C(0x00000030)),f[0]);if(taken){goto L_00164268;}}
/* 00164254: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 00164258: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0016425c: b 0x00164284 */ /* delay 00164260 */ set(2,sx((uint32_t)cpu(5)>>16));goto L_00164284;
L_00164268:;
/* 00164268: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0016426c: srl v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)>>1));
/* 00164270: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00164274: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
/* 00164278: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0016427c: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
/* 00164280: srl v0,a1,0x10 */ set(2,sx((uint32_t)cpu(5)>>16));
L_00164284:;
/* 00164284: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 00164288: bltzl v1,0x001642a0 */ {int taken=((int64_t)cpu(3)<0);if(taken){/* delay 0016428c */ set(2,cpu(2)&UINT32_C(0x00000001));goto L_001642a0;}}
/* 00164290: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 00164294: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00164298: b 0x001642b8 */ /* delay 0016429c */ f[0]=sub(f[1],f[0]);goto L_001642b8;
L_001642a0:;
/* 001642a0: srl v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)>>1));
/* 001642a4: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 001642a8: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 001642ac: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 001642b0: add.S f0,f0,f0 */ f[0]=add(f[0],f[0]);
/* 001642b4: sub.S f0,f1,f0 */ f[0]=sub(f[1],f[0]);
L_001642b8:;
/* 001642b8: nop  */ 
/* 001642bc: nop  */ 
/* 001642c0: div.S f0,f0,f2 */ f[0]=divs(f[0],f[2]);
/* 001642c4: swc1 f0,0x38(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000038)),f[0]);
L_001642c8:;
/* 001642c8: jr ra */ {uint64_t target=cpu(31);/* delay 001642cc */ checkReturn(target,incoming);return;}
}
void ps2BattleActionCreation_0015C1E8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015c1e8u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 0015c1e8: clear f0 */ f[0]=0;
/* 0015c1ec: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
/* 0015c1f0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0015c1f4: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0015c1f8: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0015c1fc: swc1 f0,0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),f[0]);
/* 0015c200: swc1 f1,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),f[1]);
/* 0015c204: sw v0,0x24(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
/* 0015c208: sh zero,0x2e(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(0));
/* 0015c20c: swc1 f0,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),f[0]);
/* 0015c210: swc1 f0,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),f[0]);
/* 0015c214: swc1 f0,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),f[0]);
/* 0015c218: swc1 f0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),f[0]);
/* 0015c21c: swc1 f1,0x18(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),f[1]);
/* 0015c220: swc1 f1,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),f[1]);
/* 0015c224: jr ra */ {uint64_t target=cpu(31);/* delay 0015c228 */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),f[0]);checkReturn(target,incoming);return;}
}
void ps2BattleActionCreation_0015D088(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x0015d088u);
uint64_t incoming=cpu(31);
/* 0015d088: lhu v1,0x2c(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x0000002c))));
/* 0015d08c: sll a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)<<16));
/* 0015d090: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0015d094: beq v1,v0,0x0015d0c8 */ {int taken=(cpu(3)==cpu(2));/* delay 0015d098 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>16)));if(taken){goto L_0015d0c8;}}
/* 0015d09c: slti v0,v1,0x2 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 0015d0a0: beql v0,zero,0x0015d0b8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0015d0a4 */ set(2,sx(UINT32_C(0x00000003)));goto L_0015d0b8;}}
/* 0015d0a8: beq v1,zero,0x0015d0c0 */ {int taken=(cpu(3)==cpu(0));/* delay 0015d0ac */ if(taken){goto L_0015d0c0;}}
/* 0015d0b0: jr ra */ {uint64_t target=cpu(31);/* delay 0015d0b4 */ checkReturn(target,incoming);return;}
L_0015d0b8:;
/* 0015d0b8: bne v1,v0,0x0015d12c */ {int taken=(cpu(3)!=cpu(2));/* delay 0015d0bc */ if(taken){goto L_0015d12c;}}
L_0015d0c0:;
/* 0015d0c0: jr ra */ {uint64_t target=cpu(31);/* delay 0015d0c4 */ sh(ea(4,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(5));checkReturn(target,incoming);return;}
L_0015d0c8:;
/* 0015d0c8: lw v1,0x5c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000005c)));
/* 0015d0cc: blez v1,0x0015d12c */ {int taken=((int64_t)cpu(3)<=0);/* delay 0015d0d0 */ if(taken){goto L_0015d12c;}}
/* 0015d0d4: lw v0,0x60(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000060)));
/* 0015d0d8: move a3,v1 */ set(7,cpu(3));
/* 0015d0dc: li t2,-0x7 */ set(10,sx(UINT32_C(0xfffffff9)));
/* 0015d0e0: li t1,0x2 */ set(9,sx(UINT32_C(0x00000002)));
/* 0015d0e4: addiu a0,v0,0xc */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x0000000c)));
/* 0015d0e8: li t0,0x3 */ set(8,sx(UINT32_C(0x00000003)));
/* 0015d0ec: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
L_0015d0f0:;
/* 0015d0f0: addiu a0,a0,0x14 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000014)));
/* 0015d0f4: lw v0,0x10(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 0015d0f8: and v0,v0,t2 */ set(2,cpu(2)&cpu(10));
/* 0015d0fc: ori a2,v0,0x2 */ set(6,cpu(2)|UINT32_C(0x00000002));
/* 0015d100: bne a1,t1,0x0015d110 */ {int taken=(cpu(5)!=cpu(9));/* delay 0015d104 */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));if(taken){goto L_0015d110;}}
/* 0015d108: b 0x0015d120 */ /* delay 0015d10c */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(6));goto L_0015d120;
L_0015d110:;
/* 0015d110: bnel a1,t0,0x0015d124 */ {int taken=(cpu(5)!=cpu(8));if(taken){/* delay 0015d114 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));goto L_0015d124;}}
/* 0015d118: ori v0,v0,0x4 */ set(2,cpu(2)|UINT32_C(0x00000004));
/* 0015d11c: sw v0,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
L_0015d120:;
/* 0015d120: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
L_0015d124:;
/* 0015d124: bnel a3,zero,0x0015d0f0 */ {int taken=(cpu(7)!=cpu(0));if(taken){/* delay 0015d128 */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));goto L_0015d0f0;}}
L_0015d12c:;
/* 0015d12c: jr ra */ {uint64_t target=cpu(31);/* delay 0015d130 */ checkReturn(target,incoming);return;}
}
void ps2BattleActionCreation_0015D3E8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015d3e8u);
uint64_t incoming=cpu(31);
/* 0015d3e8: lhu v0,0x2c(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000002c))));
/* 0015d3ec: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0015d3f0: bne v0,v1,0x0015d404 */ {int taken=(cpu(2)!=cpu(3));/* delay 0015d3f4 */ set(3,sx(UINT32_C(0x01000000)));if(taken){goto L_0015d404;}}
/* 0015d3f8: lw v0,0x54(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000054)));
/* 0015d3fc: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 0015d400: sw v0,0x54(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));
L_0015d404:;
/* 0015d404: jr ra */ {uint64_t target=cpu(31);/* delay 0015d408 */ checkReturn(target,incoming);return;}
}
uint64_t ps2BattleActionCreation_0015D000(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015d000u);
uint64_t incoming=cpu(31);
/* 0015d000: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 0015d004: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 0015d008: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0015d00c: lw v0,-0x67b8(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffff9848)));
/* 0015d010: lw v1,0x30(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000030)));
/* 0015d014: jr ra */ {uint64_t target=cpu(31);/* delay 0015d018 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00176260(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00176260u);
uint64_t incoming=cpu(31);
/* 00176260: jr ra */ {uint64_t target=cpu(31);/* delay 00176264 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00176268(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00176268u);
uint64_t incoming=cpu(31);
/* 00176268: jr ra */ {uint64_t target=cpu(31);/* delay 0017626c */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00176270(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);nocturneEffectAxisNoteEntry(0x00176270u);
uint64_t incoming=cpu(31);
/* 00176270: move v0,a0 */ set(2,cpu(4));
/* 00176274: sll a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)<<4));
/* 00176278: addu a1,v0,a1 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0017627c: lw v1,0x14(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000014)));
/* 00176280: jr ra */ {uint64_t target=cpu(31);/* delay 00176284 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015AF10(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015af10u);
uint64_t incoming=cpu(31);
/* 0015af10: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015af14: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015af18: move s0,a0 */ set(16,cpu(4));
/* 0015af1c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015af20: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015af24: jal 0x002a8af8 */ set(31,0x0015af2cu);/* delay 0015af28 */ set(4,sx(UINT32_C(0x00000010)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015af2c: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0015af30: move s1,v0 */ set(17,cpu(2));
/* 0015af34: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0015af38: sw v1,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 0015af3c: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0015af40: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 0015af44: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0015af48: sll v1,a1,0x1 */ set(3,sx((uint32_t)cpu(5)<<1));
/* 0015af4c: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0015af50: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 0015af54: lui v0,0x31 */ set(2,sx(UINT32_C(0x00310000)));
/* 0015af58: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0015af5c: lw v0,0x6f18(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00006f18)));
/* 0015af60: jalr v0 */ {uint64_t target=cpu(2);set(31,0x0015af68u);/* delay 0015af64 */ switch((uint32_t)target){case 0x00164dd0u:set(2,ps2BattleActionCreation_00164DD0(cpu(4)));break;case 0x001650e0u:set(2,ps2BattleActionCreation_001650E0(cpu(4)));break;case 0x00169d28u:set(2,dds3SpPolyCopy(cpu(4)));break;case 0x001a8e58u:set(2,dds3MagatuhiParCopy(cpu(4)));break;case 0x00175a88u:set(2,ps2BattleActionPartCopy_00175A88(cpu(4)));break;default:fprintf(stderr,"Unsupported actual generic effect copy %08x\n",(uint32_t)target);abort();}}
/* 0015af68: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0015af6c: move v0,s1 */ set(2,cpu(17));
/* 0015af70: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015af74: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015af78: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015af7c: jr ra */ {uint64_t target=cpu(31);/* delay 0015af80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_001650E0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001650e0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 001650e0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001650e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001650e8: move s0,a0 */ set(16,cpu(4));
/* 001650ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001650f0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001650f4: lhu v0,0x140(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000140))));
/* 001650f8: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 001650fc: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00165100: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00165104: lui v0,0x31 */ set(2,sx(UINT32_C(0x00310000)));
/* 00165108: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0016510c: lw v0,0x7270(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00007270)));
/* 00165110: jalr v0 */ {uint64_t target=cpu(2);set(31,0x00165118u);/* delay 00165114 */ switch((uint32_t)target){case 0x0015e2a8u:set(2,ps2BattleActionCreation_0015E2A8(cpu(4)));break;case 0x0015e8f8u:set(2,ps2BattleActionCreation_0015E8F8(cpu(4)));break;case 0x0015ef48u:set(2,ps2BattleActionCreation_0015EF48(cpu(4)));break;case 0x0015faf0u:set(2,ps2BattleActionCreation_0015FAF0(cpu(4)));break;case 0x001600d0u:set(2,ps2BattleActionCreation_001600D0(cpu(4)));break;case 0x001607e0u:set(2,ps2BattleActionCreation_001607E0(cpu(4)));break;case 0x00160ea0u:set(2,ps2BattleActionCreation_00160EA0(cpu(4)));break;case 0x00161448u:set(2,ps2BattleActionCreation_00161448(cpu(4)));break;case 0x001619f0u:set(2,ps2BattleActionCreation_001619F0(cpu(4)));break;case 0x001621c8u:set(2,ps2BattleActionCreation_001621C8(cpu(4)));break;case 0x00162498u:set(2,ps2BattleActionCreation_00162498(cpu(4)));break;case 0x00162fc8u:set(2,ps2BattleActionCreation_00162FC8(cpu(4)));break;case 0x00163628u:set(2,ps2BattleActionCreation_00163628(cpu(4)));break;default:fprintf(stderr,"Unsupported actual emitter copy %08x\n",(uint32_t)target);abort();}}
/* 00165118: lhu v1,0x140(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000140))));
/* 0016511c: lw a0,0x28(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 00165120: move s1,v0 */ set(17,cpu(2));
/* 00165124: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 00165128: bne a0,v0,0x00165164 */ {int taken=(cpu(4)!=cpu(2));/* delay 0016512c */ sh(ea(17,(int32_t)UINT32_C(0x00000140)),(uint16_t)cpu(3));if(taken){goto L_00165164;}}
/* 00165130: jal 0x0015cea0 */ set(31,0x00165138u);/* delay 00165134 */ lw(4,ea(16,(int32_t)UINT32_C(0x000000f4)));set(2,dds3BillboardCopy(cpu(4)));
/* 00165138: lwc1 f12,0x10(s1) */ f[12]=word(ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0016513c: move s0,v0 */ set(16,cpu(2));
/* 00165140: lwc1 f13,0x14(s1) */ f[13]=word(ea(17,(int32_t)UINT32_C(0x00000014)));
/* 00165144: jal 0x0015d038 */ set(31,0x0016514cu);/* delay 00165148 */ set(4,cpu(16));ps2EffectBillboardSetScale_0015D038(cpu(4),real(f[12]),real(f[13]));
/* 0016514c: move a0,s0 */ set(4,cpu(16));
/* 00165150: jal 0x0015d088 */ set(31,0x00165158u);/* delay 00165154 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000002c))));ps2BattleActionCreation_0015D088(cpu(4),cpu(5));
/* 00165158: jal 0x0015d3e8 */ set(31,0x00165160u);/* delay 0016515c */ set(4,cpu(16));ps2BattleActionCreation_0015D3E8(cpu(4));
/* 00165160: sw s0,0xf4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000f4)),(uint32_t)cpu(16));
L_00165164:;
/* 00165164: move v0,s1 */ set(2,cpu(17));
/* 00165168: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016516c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00165170: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00165174: jr ra */ {uint64_t target=cpu(31);/* delay 00165178 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00164DD0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00164dd0u);
uint64_t incoming=cpu(31);
/* 00164dd0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00164dd4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00164dd8: move s0,a0 */ set(16,cpu(4));
/* 00164ddc: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00164de0: lhu v0,0x140(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000140))));
/* 00164de4: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 00164de8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00164dec: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00164df0: lui v0,0x31 */ set(2,sx(UINT32_C(0x00310000)));
/* 00164df4: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00164df8: lw v0,0x7270(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00007270)));
/* 00164dfc: jalr v0 */ {uint64_t target=cpu(2);set(31,0x00164e04u);/* delay 00164e00 */ switch((uint32_t)target){case 0x0015e2a8u:set(2,ps2BattleActionCreation_0015E2A8(cpu(4)));break;case 0x0015e8f8u:set(2,ps2BattleActionCreation_0015E8F8(cpu(4)));break;case 0x0015ef48u:set(2,ps2BattleActionCreation_0015EF48(cpu(4)));break;case 0x0015faf0u:set(2,ps2BattleActionCreation_0015FAF0(cpu(4)));break;case 0x001600d0u:set(2,ps2BattleActionCreation_001600D0(cpu(4)));break;case 0x001607e0u:set(2,ps2BattleActionCreation_001607E0(cpu(4)));break;case 0x00160ea0u:set(2,ps2BattleActionCreation_00160EA0(cpu(4)));break;case 0x00161448u:set(2,ps2BattleActionCreation_00161448(cpu(4)));break;case 0x001619f0u:set(2,ps2BattleActionCreation_001619F0(cpu(4)));break;case 0x001621c8u:set(2,ps2BattleActionCreation_001621C8(cpu(4)));break;case 0x00162498u:set(2,ps2BattleActionCreation_00162498(cpu(4)));break;case 0x00162fc8u:set(2,ps2BattleActionCreation_00162FC8(cpu(4)));break;case 0x00163628u:set(2,ps2BattleActionCreation_00163628(cpu(4)));break;default:fprintf(stderr,"Unsupported actual emitter copy %08x\n",(uint32_t)target);abort();}}
/* 00164e04: lhu v1,0x140(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000140))));
/* 00164e08: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00164e0c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00164e10: sh v1,0x140(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000140)),(uint16_t)cpu(3));
/* 00164e14: jr ra */ {uint64_t target=cpu(31);/* delay 00164e18 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015E2A8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015e2a8u);
uint64_t incoming=cpu(31);
/* 0015e2a8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015e2ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015e2b0: move s0,a0 */ set(16,cpu(4));
/* 0015e2b4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015e2b8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015e2bc: jal 0x002a8af8 */ set(31,0x0015e2c4u);/* delay 0015e2c0 */ set(4,sx(UINT32_C(0x00000180)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015e2c4: move s1,v0 */ set(17,cpu(2));
/* 0015e2c8: move a1,zero */ set(5,cpu(0));
/* 0015e2cc: move a0,s1 */ set(4,cpu(17));
/* 0015e2d0: jal 0x002d4558 */ set(31,0x0015e2d8u);/* delay 0015e2d4 */ set(6,sx(UINT32_C(0x00000180)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 0015e2d8: move a0,s1 */ set(4,cpu(17));
/* 0015e2dc: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0015e2e0: jal 0x002d43a4 */ set(31,0x0015e2e8u);/* delay 0015e2e4 */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015e2e8: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0015e2ec: li a2,0x30 */ set(6,sx(UINT32_C(0x00000030)));
/* 0015e2f0: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 0015e2f4: jal 0x002d43a4 */ set(31,0x0015e2fcu);/* delay 0015e2f8 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015e2fc: jal 0x0015df58 */ set(31,0x0015e304u);/* delay 0015e300 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 0015e304: jal 0x0015e1e8 */ set(31,0x0015e30cu);/* delay 0015e308 */ set(4,cpu(17));ps2EffectPartControlNative_0015E1E8(cpu(4));
/* 0015e30c: move v0,s1 */ set(2,cpu(17));
/* 0015e310: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015e314: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015e318: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015e31c: jr ra */ {uint64_t target=cpu(31);/* delay 0015e320 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015E8F8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015e8f8u);
uint64_t incoming=cpu(31);
/* 0015e8f8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015e8fc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015e900: move s0,a0 */ set(16,cpu(4));
/* 0015e904: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015e908: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015e90c: jal 0x002a8af8 */ set(31,0x0015e914u);/* delay 0015e910 */ set(4,sx(UINT32_C(0x00000180)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015e914: move s1,v0 */ set(17,cpu(2));
/* 0015e918: move a1,zero */ set(5,cpu(0));
/* 0015e91c: move a0,s1 */ set(4,cpu(17));
/* 0015e920: jal 0x002d4558 */ set(31,0x0015e928u);/* delay 0015e924 */ set(6,sx(UINT32_C(0x00000180)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 0015e928: move a0,s1 */ set(4,cpu(17));
/* 0015e92c: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0015e930: jal 0x002d43a4 */ set(31,0x0015e938u);/* delay 0015e934 */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015e938: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0015e93c: li a2,0x30 */ set(6,sx(UINT32_C(0x00000030)));
/* 0015e940: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 0015e944: jal 0x002d43a4 */ set(31,0x0015e94cu);/* delay 0015e948 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015e94c: jal 0x0015df58 */ set(31,0x0015e954u);/* delay 0015e950 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 0015e954: jal 0x0015e860 */ set(31,0x0015e95cu);/* delay 0015e958 */ set(4,cpu(17));ps2EffectPartControlNative_0015E860(cpu(4));
/* 0015e95c: move v0,s1 */ set(2,cpu(17));
/* 0015e960: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015e964: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015e968: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015e96c: jr ra */ {uint64_t target=cpu(31);/* delay 0015e970 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_0015FAF0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0015faf0u);
uint64_t incoming=cpu(31);
/* 0015faf0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0015faf4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015faf8: move s0,a0 */ set(16,cpu(4));
/* 0015fafc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015fb00: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015fb04: jal 0x002a8af8 */ set(31,0x0015fb0cu);/* delay 0015fb08 */ set(4,sx(UINT32_C(0x00000170)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 0015fb0c: move s1,v0 */ set(17,cpu(2));
/* 0015fb10: move a1,zero */ set(5,cpu(0));
/* 0015fb14: move a0,s1 */ set(4,cpu(17));
/* 0015fb18: jal 0x002d4558 */ set(31,0x0015fb20u);/* delay 0015fb1c */ set(6,sx(UINT32_C(0x00000170)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 0015fb20: move a0,s1 */ set(4,cpu(17));
/* 0015fb24: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0015fb28: jal 0x002d43a4 */ set(31,0x0015fb30u);/* delay 0015fb2c */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015fb30: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0015fb34: li a2,0x20 */ set(6,sx(UINT32_C(0x00000020)));
/* 0015fb38: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 0015fb3c: jal 0x002d43a4 */ set(31,0x0015fb44u);/* delay 0015fb40 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0015fb44: jal 0x0015df58 */ set(31,0x0015fb4cu);/* delay 0015fb48 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 0015fb4c: jal 0x0015fa18 */ set(31,0x0015fb54u);/* delay 0015fb50 */ set(4,cpu(17));ps2EffectPartControlNative_0015FA18(cpu(4));
/* 0015fb54: move v0,s1 */ set(2,cpu(17));
/* 0015fb58: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0015fb5c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0015fb60: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0015fb64: jr ra */ {uint64_t target=cpu(31);/* delay 0015fb68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_001600D0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001600d0u);
uint64_t incoming=cpu(31);
/* 001600d0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001600d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001600d8: move s0,a0 */ set(16,cpu(4));
/* 001600dc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001600e0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001600e4: jal 0x002a8af8 */ set(31,0x001600ecu);/* delay 001600e8 */ set(4,sx(UINT32_C(0x00000170)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 001600ec: move s1,v0 */ set(17,cpu(2));
/* 001600f0: move a1,zero */ set(5,cpu(0));
/* 001600f4: move a0,s1 */ set(4,cpu(17));
/* 001600f8: jal 0x002d4558 */ set(31,0x00160100u);/* delay 001600fc */ set(6,sx(UINT32_C(0x00000170)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 00160100: move a0,s1 */ set(4,cpu(17));
/* 00160104: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00160108: jal 0x002d43a4 */ set(31,0x00160110u);/* delay 0016010c */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00160110: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00160114: li a2,0x20 */ set(6,sx(UINT32_C(0x00000020)));
/* 00160118: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 0016011c: jal 0x002d43a4 */ set(31,0x00160124u);/* delay 00160120 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00160124: jal 0x0015df58 */ set(31,0x0016012cu);/* delay 00160128 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 0016012c: jal 0x00160048 */ set(31,0x00160134u);/* delay 00160130 */ set(4,cpu(17));ps2EffectPartControlNative_00160048(cpu(4));
/* 00160134: move v0,s1 */ set(2,cpu(17));
/* 00160138: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016013c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00160140: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00160144: jr ra */ {uint64_t target=cpu(31);/* delay 00160148 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_001607E0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001607e0u);
uint64_t incoming=cpu(31);
/* 001607e0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001607e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001607e8: move s0,a0 */ set(16,cpu(4));
/* 001607ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001607f0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001607f4: jal 0x002a8af8 */ set(31,0x001607fcu);/* delay 001607f8 */ set(4,sx(UINT32_C(0x00000180)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 001607fc: move s1,v0 */ set(17,cpu(2));
/* 00160800: move a1,zero */ set(5,cpu(0));
/* 00160804: move a0,s1 */ set(4,cpu(17));
/* 00160808: jal 0x002d4558 */ set(31,0x00160810u);/* delay 0016080c */ set(6,sx(UINT32_C(0x00000180)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 00160810: move a0,s1 */ set(4,cpu(17));
/* 00160814: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00160818: jal 0x002d43a4 */ set(31,0x00160820u);/* delay 0016081c */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00160820: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00160824: li a2,0x30 */ set(6,sx(UINT32_C(0x00000030)));
/* 00160828: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 0016082c: jal 0x002d43a4 */ set(31,0x00160834u);/* delay 00160830 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00160834: jal 0x0015df58 */ set(31,0x0016083cu);/* delay 00160838 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 0016083c: jal 0x00160748 */ set(31,0x00160844u);/* delay 00160840 */ set(4,cpu(17));ps2EffectPartControlNative_00160748(cpu(4));
/* 00160844: move v0,s1 */ set(2,cpu(17));
/* 00160848: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016084c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00160850: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00160854: jr ra */ {uint64_t target=cpu(31);/* delay 00160858 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00160EA0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00160ea0u);
uint64_t incoming=cpu(31);
/* 00160ea0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00160ea4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00160ea8: move s0,a0 */ set(16,cpu(4));
/* 00160eac: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00160eb0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00160eb4: jal 0x002a8af8 */ set(31,0x00160ebcu);/* delay 00160eb8 */ set(4,sx(UINT32_C(0x00000170)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00160ebc: move s1,v0 */ set(17,cpu(2));
/* 00160ec0: move a1,zero */ set(5,cpu(0));
/* 00160ec4: move a0,s1 */ set(4,cpu(17));
/* 00160ec8: jal 0x002d4558 */ set(31,0x00160ed0u);/* delay 00160ecc */ set(6,sx(UINT32_C(0x00000170)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 00160ed0: move a0,s1 */ set(4,cpu(17));
/* 00160ed4: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00160ed8: jal 0x002d43a4 */ set(31,0x00160ee0u);/* delay 00160edc */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00160ee0: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00160ee4: li a2,0x20 */ set(6,sx(UINT32_C(0x00000020)));
/* 00160ee8: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 00160eec: jal 0x002d43a4 */ set(31,0x00160ef4u);/* delay 00160ef0 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00160ef4: jal 0x0015df58 */ set(31,0x00160efcu);/* delay 00160ef8 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 00160efc: jal 0x00160df8 */ set(31,0x00160f04u);/* delay 00160f00 */ set(4,cpu(17));ps2EffectPartControlNative_00160DF8(cpu(4));
/* 00160f04: move v0,s1 */ set(2,cpu(17));
/* 00160f08: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00160f0c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00160f10: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00160f14: jr ra */ {uint64_t target=cpu(31);/* delay 00160f18 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00161448(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00161448u);
uint64_t incoming=cpu(31);
/* 00161448: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0016144c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00161450: move s0,a0 */ set(16,cpu(4));
/* 00161454: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00161458: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0016145c: jal 0x002a8af8 */ set(31,0x00161464u);/* delay 00161460 */ set(4,sx(UINT32_C(0x00000180)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00161464: move s1,v0 */ set(17,cpu(2));
/* 00161468: move a1,zero */ set(5,cpu(0));
/* 0016146c: move a0,s1 */ set(4,cpu(17));
/* 00161470: jal 0x002d4558 */ set(31,0x00161478u);/* delay 00161474 */ set(6,sx(UINT32_C(0x00000180)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 00161478: move a0,s1 */ set(4,cpu(17));
/* 0016147c: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00161480: jal 0x002d43a4 */ set(31,0x00161488u);/* delay 00161484 */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00161488: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0016148c: li a2,0x30 */ set(6,sx(UINT32_C(0x00000030)));
/* 00161490: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 00161494: jal 0x002d43a4 */ set(31,0x0016149cu);/* delay 00161498 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0016149c: jal 0x0015df58 */ set(31,0x001614a4u);/* delay 001614a0 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 001614a4: jal 0x001613b0 */ set(31,0x001614acu);/* delay 001614a8 */ set(4,cpu(17));ps2EffectPartControlNative_001613B0(cpu(4));
/* 001614ac: move v0,s1 */ set(2,cpu(17));
/* 001614b0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001614b4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001614b8: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001614bc: jr ra */ {uint64_t target=cpu(31);/* delay 001614c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_001619F0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001619f0u);
uint64_t incoming=cpu(31);
/* 001619f0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001619f4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001619f8: move s0,a0 */ set(16,cpu(4));
/* 001619fc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00161a00: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00161a04: jal 0x002a8af8 */ set(31,0x00161a0cu);/* delay 00161a08 */ set(4,sx(UINT32_C(0x00000170)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00161a0c: move s1,v0 */ set(17,cpu(2));
/* 00161a10: move a1,zero */ set(5,cpu(0));
/* 00161a14: move a0,s1 */ set(4,cpu(17));
/* 00161a18: jal 0x002d4558 */ set(31,0x00161a20u);/* delay 00161a1c */ set(6,sx(UINT32_C(0x00000170)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 00161a20: move a0,s1 */ set(4,cpu(17));
/* 00161a24: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00161a28: jal 0x002d43a4 */ set(31,0x00161a30u);/* delay 00161a2c */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00161a30: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00161a34: li a2,0x20 */ set(6,sx(UINT32_C(0x00000020)));
/* 00161a38: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 00161a3c: jal 0x002d43a4 */ set(31,0x00161a44u);/* delay 00161a40 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00161a44: jal 0x0015df58 */ set(31,0x00161a4cu);/* delay 00161a48 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 00161a4c: jal 0x00161958 */ set(31,0x00161a54u);/* delay 00161a50 */ set(4,cpu(17));ps2EffectPartControlNative_00161958(cpu(4));
/* 00161a54: move v0,s1 */ set(2,cpu(17));
/* 00161a58: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00161a5c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00161a60: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00161a64: jr ra */ {uint64_t target=cpu(31);/* delay 00161a68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_001621C8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001621c8u);
uint64_t incoming=cpu(31);
/* 001621c8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001621cc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001621d0: move s1,a0 */ set(17,cpu(4));
/* 001621d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001621d8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001621dc: jal 0x002a8af8 */ set(31,0x001621e4u);/* delay 001621e0 */ set(4,sx(UINT32_C(0x00000150)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 001621e4: move s0,v0 */ set(16,cpu(2));
/* 001621e8: move a1,zero */ set(5,cpu(0));
/* 001621ec: move a0,s0 */ set(4,cpu(16));
/* 001621f0: jal 0x002d4558 */ set(31,0x001621f8u);/* delay 001621f4 */ set(6,sx(UINT32_C(0x00000150)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 001621f8: move a0,s0 */ set(4,cpu(16));
/* 001621fc: lw a2,0xa0(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x000000a0)));
/* 00162200: jal 0x002d43a4 */ set(31,0x00162208u);/* delay 00162204 */ set(5,cpu(17));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00162208: lw a1,0xa0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x000000a0)));
/* 0016220c: addiu a0,s0,0x150 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000150)));
/* 00162210: move a2,zero */ set(6,cpu(0));
/* 00162214: jal 0x002d43a4 */ set(31,0x0016221cu);/* delay 00162218 */ set(5,sx((uint32_t)cpu(17)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0016221c: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00162220: sw v1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
/* 00162224: move a0,s0 */ set(4,cpu(16));
/* 00162228: jal 0x0015df58 */ set(31,0x00162230u);/* delay 0016222c */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));ps2BattleActionCreation_0015DF58(cpu(4));
/* 00162230: move v0,s0 */ set(2,cpu(16));
/* 00162234: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00162238: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0016223c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00162240: jr ra */ {uint64_t target=cpu(31);/* delay 00162244 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00162498(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00162498u);
uint64_t incoming=cpu(31);
/* 00162498: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0016249c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001624a0: move s0,a0 */ set(16,cpu(4));
/* 001624a4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001624a8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001624ac: jal 0x002a8af8 */ set(31,0x001624b4u);/* delay 001624b0 */ set(4,sx(UINT32_C(0x00000190)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 001624b4: move s1,v0 */ set(17,cpu(2));
/* 001624b8: move a1,zero */ set(5,cpu(0));
/* 001624bc: move a0,s1 */ set(4,cpu(17));
/* 001624c0: jal 0x002d4558 */ set(31,0x001624c8u);/* delay 001624c4 */ set(6,sx(UINT32_C(0x00000190)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 001624c8: move a0,s1 */ set(4,cpu(17));
/* 001624cc: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 001624d0: jal 0x002d43a4 */ set(31,0x001624d8u);/* delay 001624d4 */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 001624d8: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 001624dc: li a2,0x40 */ set(6,sx(UINT32_C(0x00000040)));
/* 001624e0: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 001624e4: jal 0x002d43a4 */ set(31,0x001624ecu);/* delay 001624e8 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 001624ec: jal 0x0015df58 */ set(31,0x001624f4u);/* delay 001624f0 */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 001624f4: jal 0x00162400 */ set(31,0x001624fcu);/* delay 001624f8 */ set(4,cpu(17));ps2EffectPartControlNative_00162400(cpu(4));
/* 001624fc: move v0,s1 */ set(2,cpu(17));
/* 00162500: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00162504: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00162508: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0016250c: jr ra */ {uint64_t target=cpu(31);/* delay 00162510 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00162FC8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00162fc8u);
uint64_t incoming=cpu(31);
/* 00162fc8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00162fcc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00162fd0: move s1,a0 */ set(17,cpu(4));
/* 00162fd4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00162fd8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00162fdc: jal 0x002a8af8 */ set(31,0x00162fe4u);/* delay 00162fe0 */ set(4,sx(UINT32_C(0x00000200)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00162fe4: move s0,v0 */ set(16,cpu(2));
/* 00162fe8: move a1,zero */ set(5,cpu(0));
/* 00162fec: move a0,s0 */ set(4,cpu(16));
/* 00162ff0: jal 0x002d4558 */ set(31,0x00162ff8u);/* delay 00162ff4 */ set(6,sx(UINT32_C(0x00000200)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 00162ff8: move a0,s0 */ set(4,cpu(16));
/* 00162ffc: lw a2,0xa0(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x000000a0)));
/* 00163000: jal 0x002d43a4 */ set(31,0x00163008u);/* delay 00163004 */ set(5,cpu(17));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00163008: lw a1,0xa0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x000000a0)));
/* 0016300c: li a2,0xb0 */ set(6,sx(UINT32_C(0x000000b0)));
/* 00163010: addiu a0,s0,0x150 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000150)));
/* 00163014: jal 0x002d43a4 */ set(31,0x0016301cu);/* delay 00163018 */ set(5,sx((uint32_t)cpu(17)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 0016301c: lw a0,0x20(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 00163020: jal 0x002a9038 */ set(31,0x00163028u);/* delay 00163024 */ set(4,sx((uint32_t)cpu(4)<<4));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 00163028: sw v0,0x17c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000017c)),(uint32_t)cpu(2));
/* 0016302c: jal 0x002a9688 */ set(31,0x00163034u);/* delay 00163030 */ set(4,cpu(2));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 00163034: move a0,s0 */ set(4,cpu(16));
/* 00163038: jal 0x0015df58 */ set(31,0x00163040u);/* delay 0016303c */ sw(ea(16,(int32_t)UINT32_C(0x00000178)),(uint32_t)cpu(2));ps2BattleActionCreation_0015DF58(cpu(4));
/* 00163040: jal 0x00162f30 */ set(31,0x00163048u);/* delay 00163044 */ set(4,cpu(16));ps2EffectPartControlNative_00162F30(cpu(4));
/* 00163048: move v0,s0 */ set(2,cpu(16));
/* 0016304c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00163050: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00163054: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00163058: jr ra */ {uint64_t target=cpu(31);/* delay 0016305c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionCreation_00163628(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00163628u);
uint64_t incoming=cpu(31);
/* 00163628: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0016362c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00163630: move s0,a0 */ set(16,cpu(4));
/* 00163634: li a0,0x190 */ set(4,sx(UINT32_C(0x00000190)));
/* 00163638: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0016363c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00163640: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00163644: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00163648: jal 0x002a8af8 */ set(31,0x00163650u);/* delay 0016364c */ set(19,cpu(0));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
/* 00163650: move s1,v0 */ set(17,cpu(2));
/* 00163654: move a1,zero */ set(5,cpu(0));
/* 00163658: move a0,s1 */ set(4,cpu(17));
/* 0016365c: jal 0x002d4558 */ set(31,0x00163664u);/* delay 00163660 */ set(6,sx(UINT32_C(0x00000190)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
/* 00163664: move a0,s1 */ set(4,cpu(17));
/* 00163668: lw a2,0xa0(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 0016366c: jal 0x002d43a4 */ set(31,0x00163674u);/* delay 00163670 */ set(5,cpu(16));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00163674: lw a1,0xa0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000a0)));
/* 00163678: li a2,0x40 */ set(6,sx(UINT32_C(0x00000040)));
/* 0016367c: addiu a0,s1,0x150 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000150)));
/* 00163680: jal 0x002d43a4 */ set(31,0x00163688u);/* delay 00163684 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));set(2,ps2EffectGuestMemcpy_002D43A4(cpu(4),cpu(5),cpu(6)));
/* 00163688: jal 0x0015df58 */ set(31,0x00163690u);/* delay 0016368c */ set(4,cpu(17));ps2BattleActionCreation_0015DF58(cpu(4));
/* 00163690: lhu v0,0x30(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x00000030))));
/* 00163694: beq v0,zero,0x00163750 */ {int taken=(cpu(2)==cpu(0));/* delay 00163698 */ set(3,cpu(2));if(taken){goto L_00163750;}}
/* 0016369c: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 001636a0: beq v1,v0,0x001636d8 */ {int taken=(cpu(3)==cpu(2));/* delay 001636a4 */ lw(18,ea(17,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_001636d8;}}
/* 001636a8: slti v0,v1,0x3 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 001636ac: beq v0,zero,0x001636c8 */ {int taken=(cpu(2)==cpu(0));/* delay 001636b0 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_001636c8;}}
/* 001636b4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001636b8: beql v1,v0,0x001636dc */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 001636bc */ set(19,half(ea(17,(int32_t)UINT32_C(0x00000034))));goto L_001636dc;}}
/* 001636c0: b 0x001636e0 */ /* delay 001636c4 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(19)*(int64_t)(int32_t)(uint32_t)cpu(18));EE_MAGATUHI_MULT_STATE(product);set(4,sx((uint32_t)product));}goto L_001636e0;
L_001636c8:;
/* 001636c8: beq v1,v0,0x001636d8 */ {int taken=(cpu(3)==cpu(2));/* delay 001636cc */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_001636d8;}}
/* 001636d0: bnel v1,v0,0x001636e0 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 001636d4 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(19)*(int64_t)(int32_t)(uint32_t)cpu(18));EE_MAGATUHI_MULT_STATE(product);set(4,sx((uint32_t)product));}goto L_001636e0;}}
L_001636d8:;
/* 001636d8: lhu s3,0x34(s1) */ set(19,half(ea(17,(int32_t)UINT32_C(0x00000034))));
L_001636dc:;
/* 001636dc: mult a0,s3,s2 */ {uint64_t product=(uint64_t)((int64_t)(int32_t)(uint32_t)cpu(19)*(int64_t)(int32_t)(uint32_t)cpu(18));EE_MAGATUHI_MULT_STATE(product);set(4,sx((uint32_t)product));}
L_001636e0:;
/* 001636e0: sll s0,s2,0x1 */ set(16,sx((uint32_t)cpu(18)<<1));
/* 001636e4: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 001636e8: sw s3,0x170(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000170)),(uint32_t)cpu(19));
/* 001636ec: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001636f0: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 001636f4: jal 0x002a9038 */ set(31,0x001636fcu);/* delay 001636f8 */ set(4,sx((uint32_t)cpu(16)+(uint32_t)cpu(4)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
/* 001636fc: sw v0,0x174(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000174)),(uint32_t)cpu(2));
/* 00163700: jal 0x002a9688 */ set(31,0x00163708u);/* delay 00163704 */ set(4,cpu(2));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
/* 00163708: move a2,zero */ set(6,cpu(0));
/* 0016370c: move a1,v0 */ set(5,cpu(2));
/* 00163710: sw a1,0x16c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000016c)),(uint32_t)cpu(5));
/* 00163714: blez s2,0x00163754 */ {int taken=((int64_t)cpu(18)<=0);/* delay 00163718 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(16)));if(taken){goto L_00163754;}}
/* 0016371c: sll a0,s3,0x4 */ set(4,sx((uint32_t)cpu(19)<<4));
/* 00163720: move v1,v0 */ set(3,cpu(2));
/* 00163724: nop  */ 
L_00163728:;
/* 00163728: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 0016372c: sw a1,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 00163730: slt v0,a2,s2 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(18));
/* 00163734: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 00163738: sw zero,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 0016373c: addiu v1,v1,0xc */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x0000000c)));
/* 00163740: bne v0,zero,0x00163728 */ {int taken=(cpu(2)!=cpu(0));/* delay 00163744 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));if(taken){goto L_00163728;}}
/* 00163748: b 0x00163754 */ /* delay 0016374c */ goto L_00163754;
L_00163750:;
/* 00163750: sw zero,0x174(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000174)),(uint32_t)cpu(0));
L_00163754:;
/* 00163754: jal 0x001635a0 */ set(31,0x0016375cu);/* delay 00163758 */ set(4,cpu(17));ps2EffectPartControlNative_001635A0(cpu(4));
/* 0016375c: move v0,s1 */ set(2,cpu(17));
/* 00163760: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00163764: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00163768: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0016376c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00163770: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00163774: jr ra */ {uint64_t target=cpu(31);/* delay 00163778 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
