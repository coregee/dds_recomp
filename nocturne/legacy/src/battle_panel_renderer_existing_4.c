#include "battle_panel_renderer_bundle.h"
#include "battle_panel_color_native.h"
#include "battle_panel_color_privileged.h"
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

static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattlePanelColorAddress(a);}

static uint8_t byte(uint32_t a){return *at(a);}



static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelColorSetStackPointer(q[0]);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}

static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}

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
static void body_002dbec0(void){
nocturneEffectAxisNoteEntry(0x002dbec0u);
uint64_t incoming=cpu(31);
/* 002dbec0: li v1,0x42 */ set(3,sx(UINT32_C(0x00000042)));
/* 002dbec4: syscall 0x0 */ {uint64_t arguments[1]={cpu(4)};nocturneBattlePanelRendererSyscall(UINT32_C(0x002dbec4),0x42u,1,arguments);}
/* 002dbec8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbecc */ checkReturn(target,incoming);return;}
}
static void body_002dbee0(void){
nocturneEffectAxisNoteEntry(0x002dbee0u);
uint64_t incoming=cpu(31);
/* 002dbee0: li v1,0x44 */ set(3,sx(UINT32_C(0x00000044)));
/* 002dbee4: syscall 0x0 */ {uint64_t arguments[1]={cpu(4)};nocturneBattlePanelRendererSyscall(UINT32_C(0x002dbee4),0x44u,1,arguments);}
/* 002dbee8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbeec */ checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelRendererExisting4(uint32_t entry){switch(entry){case UINT32_C(0x002d5d0c):(void)body_002d5d0c();return 1u;case UINT32_C(0x002dbec0):(void)body_002dbec0();return 1u;case UINT32_C(0x002dbee0):(void)body_002dbee0();return 1u;default:return 0u;}}
