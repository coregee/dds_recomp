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
static uint32_t divs(uint32_t a,uint32_t b){return EE_FPU_DIV_S(a,b);}
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


#include "battle_action_status_resources.h"
#include "battle_action_polygon_frames.h"
#include "effect_random_frames.h"
#include "compiler_numeric.h"
#include "anchor_callbacks.h"
extern uint64_t nocturneEffectHostLo(void);
extern uint64_t nocturneEffectHostHi(void);
static void statusDivu(uint32_t a,uint32_t b){uint32_t q=b?a/b:UINT32_MAX,r=b?a%b:a;EE_ANCHOR_DIVU_STATE(q,r);}


uint64_t ps2BattleAction_00176558(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00176558);
 uint64_t incomingRa=cpu(31);
 /* 00176558: jr ra */ {uint64_t target=cpu(31);/* delay 0017655c */ set(2,cpu(4));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0017D0A0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017d0a0);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 0017d0a0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 0017d0a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017d0a8: move s0,a0 */ set(16,cpu(4));
 /* 0017d0ac: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017d0b0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017d0b4: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017d0b8: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017d0bc: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
 /* 0017d0c0: jal 0x002a9038 */ set(31,sx(UINT32_C(0x0017d0c8)));/* delay 0017d0c4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000048)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 0017d0c8: move s1,v0 */ set(17,cpu(2));
 /* 0017d0cc: jal 0x002a9688 */ set(31,sx(UINT32_C(0x0017d0d4)));/* delay 0017d0d0 */ set(4,cpu(17));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 0017d0d4: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
 /* 0017d0d8: move s2,v0 */ set(18,cpu(2));
 /* 0017d0dc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 0017d0e0: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
 /* 0017d0e4: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017d0e8: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017d0ec: ldl a0,0xf(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0017d0f0: ldr a0,0x8(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0017d0f4: ldl a1,0x17(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 0017d0f8: ldr a1,0x10(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 0017d0fc: ldl a2,0x1f(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0017d100: ldr a2,0x18(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 0017d104: sdl v0,0x7(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 0017d108: sdr v0,0x0(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 0017d10c: sdl a0,0xf(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x0000000f)),4,1);
 /* 0017d110: sdr a0,0x8(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000008)),4,0);
 /* 0017d114: sdl a1,0x17(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000017)),5,1);
 /* 0017d118: sdr a1,0x10(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000010)),5,0);
 /* 0017d11c: sdl a2,0x1f(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x0000001f)),6,1);
 /* 0017d120: sdr a2,0x18(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000018)),6,0);
 /* 0017d124: ldl v0,0x27(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000027)),1);
 /* 0017d128: ldr v0,0x20(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000020)),0);
 /* 0017d12c: ldl a0,0x2f(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x0000002f)),1);
 /* 0017d130: ldr a0,0x28(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000028)),0);
 /* 0017d134: sdl v0,0x27(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000027)),2,1);
 /* 0017d138: sdr v0,0x20(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000020)),2,0);
 /* 0017d13c: sdl a0,0x2f(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x0000002f)),4,1);
 /* 0017d140: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
 /* 0017d144: sdr a0,0x28(s2) */ storePartial(ea(18,(int32_t)UINT32_C(0x00000028)),4,0);
 /* 0017d148: addiu v0,s2,0x48 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000048)));
 /* 0017d14c: sw v1,0x38(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(3));
 /* 0017d150: lw a0,0x10(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000010)));
 /* 0017d154: sw v0,0x30(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));
 /* 0017d158: sw s1,0x40(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(17));
 /* 0017d15c: swc1 f0,0x3c(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000003c)),f[0]);
 /* 0017d160: jal 0x00182f68 */ set(31,sx(UINT32_C(0x0017d168)));/* delay 0017d164 */ sw(ea(18,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(0));set(2,ps2BattleAction_00182F68(cpu(4)));
 /* 0017d168: lw v1,0x2c(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x0000002c)));
 /* 0017d16c: sw v0,0x44(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(2));
 /* 0017d170: sw v1,0x50(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 0017d174: lw v0,0x10(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000010)));
 /* 0017d178: beq v0,zero,0x0017d1a4 */ {int take=(cpu(2)==cpu(0));/* delay 0017d17c */ set(4,cpu(0));if(take){goto L_0017d1a4;}}
 /* 0017d180: lw v0,0x30(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000030)));
 /* 0017d184: addiu v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
L_0017d188:;
 /* 0017d188: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
 /* 0017d18c: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
 /* 0017d190: lw v0,0x10(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000010)));
 /* 0017d194: sltu v0,a0,v0 */ set(2,cpu(4)<cpu(2));
 /* 0017d198: nop  */ 
 /* 0017d19c: bne v0,zero,0x0017d188 */ {int take=(cpu(2)!=cpu(0));/* delay 0017d1a0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));if(take){goto L_0017d188;}}
L_0017d1a4:;
 /* 0017d1a4: move v0,s2 */ set(2,cpu(18));
 /* 0017d1a8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017d1ac: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017d1b0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017d1b4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017d1b8: jr ra */ {uint64_t target=cpu(31);/* delay 0017d1bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0017D1C0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017d1c0);
 uint64_t incomingRa=cpu(31);
 /* 0017d1c0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017d1c4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017d1c8: jal 0x00176270 */ set(31,sx(UINT32_C(0x0017d1d0)));/* delay 0017d1cc */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0017d1d0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017d1d4: move a0,v0 */ set(4,cpu(2));
 /* 0017d1d8: j 0x0017d0a0 */ /* delay 0017d1dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017D0A0(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017D1E0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017d1e0);
 uint64_t incomingRa=cpu(31);
 /* 0017d1e0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017d1e4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017d1e8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017d1ec: j 0x0017d0a0 */ /* delay 0017d1f0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017D0A0(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017E008(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017e008);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 0017e008: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 0017e00c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017e010: move s0,a0 */ set(16,cpu(4));
 /* 0017e014: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017e018: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017e01c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017e020: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0017e024: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 0017e028: swc1 f21,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[21]);
 /* 0017e02c: swc1 f20,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);
 /* 0017e030: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017e034: sll a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)<<2));
 /* 0017e038: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
 /* 0017e03c: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
 /* 0017e040: jal 0x002a9038 */ set(31,sx(UINT32_C(0x0017e048)));/* delay 0017e044 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000060)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 0017e048: move s2,v0 */ set(18,cpu(2));
 /* 0017e04c: jal 0x002a9688 */ set(31,sx(UINT32_C(0x0017e054)));/* delay 0017e050 */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 0017e054: move s1,v0 */ set(17,cpu(2));
 /* 0017e058: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
 /* 0017e05c: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 0017e060: beq v0,zero,0x0017e0c8 */ {int take=(cpu(2)==cpu(0));/* delay 0017e064 */ set(3,cpu(17));if(take){goto L_0017e0c8;}}
 /* 0017e068: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0017e06c:;
 /* 0017e06c: ldl a0,0x7(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017e070: ldr a0,0x0(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017e074: ldl a1,0xf(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0017e078: ldr a1,0x8(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0017e07c: ldl a2,0x17(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 0017e080: ldr a2,0x10(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 0017e084: ldl a3,0x1f(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0017e088: ldr a3,0x18(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 0017e08c: sdl a0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),4,1);
 /* 0017e090: sdr a0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),4,0);
 /* 0017e094: sdl a1,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),5,1);
 /* 0017e098: sdr a1,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),5,0);
 /* 0017e09c: sdl a2,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),6,1);
 /* 0017e0a0: sdr a2,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),6,0);
 /* 0017e0a4: sdl a3,0x1f(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000001f)),7,1);
 /* 0017e0a8: sdr a3,0x18(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000018)),7,0);
 /* 0017e0ac: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 0017e0b0: nop  */ 
 /* 0017e0b4: nop  */ 
 /* 0017e0b8: bne s0,v0,0x0017e06c */ {int take=(cpu(16)!=cpu(2));/* delay 0017e0bc */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0017e06c;}}
 /* 0017e0c0: b 0x0017e100 */ /* delay 0017e0c4 */ goto L_0017e100;
L_0017e0c8:;
 /* 0017e0c8: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0017e0cc:;
 /* 0017e0cc: ld a0,0x0(s0) */ restore(4,ea(16,(int32_t)UINT32_C(0x00000000)));
 /* 0017e0d0: ld a1,0x8(s0) */ restore(5,ea(16,(int32_t)UINT32_C(0x00000008)));
 /* 0017e0d4: ld a2,0x10(s0) */ restore(6,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017e0d8: ld a3,0x18(s0) */ restore(7,ea(16,(int32_t)UINT32_C(0x00000018)));
 /* 0017e0dc: sd a0,0x0(v1) */ save(4,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 0017e0e0: sd a1,0x8(v1) */ save(5,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 0017e0e4: sd a2,0x10(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 0017e0e8: sd a3,0x18(v1) */ save(7,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 0017e0ec: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 0017e0f0: nop  */ 
 /* 0017e0f4: nop  */ 
 /* 0017e0f8: bne s0,v0,0x0017e0cc */ {int take=(cpu(16)!=cpu(2));/* delay 0017e0fc */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0017e0cc;}}
L_0017e100:;
 /* 0017e100: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017e104: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017e108: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 0017e10c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 0017e110: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
 /* 0017e114: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 0017e118: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 0017e11c: addiu v1,s1,0x60 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000060)));
 /* 0017e120: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 0017e124: lw a0,0x20(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000020)));
 /* 0017e128: sw v1,0x48(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(3));
 /* 0017e12c: sw s2,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(18));
 /* 0017e130: sw v0,0x50(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(2));
 /* 0017e134: sw zero,0x4c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));
 /* 0017e138: bne a0,zero,0x0017e148 */ {int take=(cpu(4)!=cpu(0));/* delay 0017e13c */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),f[21]);if(take){goto L_0017e148;}}
 /* 0017e140: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
 /* 0017e144: sw v0,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
L_0017e148:;
 /* 0017e148: lwc1 f20,-0x79f0(gp) */ f[20]=word(ea(28,(int32_t)UINT32_C(0xffff8610)));
 /* 0017e14c: jal 0x00182b20 */ set(31,sx(UINT32_C(0x0017e154)));/* delay 0017e150 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));set(2,ps2BattleAction_00182B20(cpu(4)));
 /* 0017e154: lw v1,0x44(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000044)));
 /* 0017e158: swc1 f21,0x5c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000005c)),f[21]);
 /* 0017e15c: sw v1,0x50(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 0017e160: sw v0,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(2));
 /* 0017e164: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017e168: bltz a0,0x0017e180 */ {int take=((int64_t)cpu(4)<0);/* delay 0017e16c */ set(2,cpu(4)&UINT32_C(0x00000001));if(take){goto L_0017e180;}}
 /* 0017e170: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
 /* 0017e174: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 0017e178: b 0x0017e194 */ /* delay 0017e17c */ goto L_0017e194;
L_0017e180:;
 /* 0017e180: srl v1,a0,0x1 */ set(3,sx((uint32_t)cpu(4)>>1));
 /* 0017e184: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
 /* 0017e188: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
 /* 0017e18c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 0017e190: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
L_0017e194:;
 /* 0017e194: lwc1 f0,-0x79ec(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8614)));
 /* 0017e198: move s3,zero */ set(19,cpu(0));
 /* 0017e19c: nop  */ 
 /* 0017e1a0: nop  */ 
 /* 0017e1a4: div.S f21,f0,f1 */ f[21]=divs(f[0],f[1]);
 /* 0017e1a8: beq a0,zero,0x0017e1fc */ {int take=(cpu(4)==cpu(0));/* delay 0017e1ac */ lw(16,ea(17,(int32_t)UINT32_C(0x00000020)));if(take){goto L_0017e1fc;}}
 /* 0017e1b0: lui s4,0x31 */ set(20,sx(UINT32_C(0x00310000)));
 /* 0017e1b4: move s2,zero */ set(18,cpu(0));
L_0017e1b8:;
 /* 0017e1b8: addiu a0,s4,0x6fe0 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0x00006fe0)));
 /* 0017e1bc: jal 0x002c0ba8 */ set(31,sx(UINT32_C(0x0017e1c4)));/* delay 0017e1c0 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));set(2,ps2EffectRandomWord_002C0BA8(cpu(4)));
 /* 0017e1c4: lw v1,0x48(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000048)));
 /* 0017e1c8: divu v0,s0 */ statusDivu((uint32_t)cpu(2),(uint32_t)cpu(16));
 /* 0017e1cc: beql s0,zero,0x0017e1d4 */ {int take=(cpu(16)==cpu(0));if(take){/* delay 0017e1d0 */ nocturneCompilerArithmeticTrap(7u);goto L_0017e1d4;}}
L_0017e1d4:;
 /* 0017e1d4: addu v1,s2,v1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(3)));
 /* 0017e1d8: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
 /* 0017e1dc: swc1 f20,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),f[20]);
 /* 0017e1e0: mfhi a0 */ set(4,nocturneEffectHostHi());
 /* 0017e1e4: subu a0,zero,a0 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
 /* 0017e1e8: sw a0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
 /* 0017e1ec: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017e1f0: sltu v0,s3,v0 */ set(2,cpu(19)<cpu(2));
 /* 0017e1f4: bne v0,zero,0x0017e1b8 */ {int take=(cpu(2)!=cpu(0));/* delay 0017e1f8 */ f[20]=add(f[20],f[21]);if(take){goto L_0017e1b8;}}
L_0017e1fc:;
 /* 0017e1fc: move v0,s1 */ set(2,cpu(17));
 /* 0017e200: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017e204: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017e208: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017e20c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017e210: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0017e214: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 0017e218: lwc1 f21,0x38(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
 /* 0017e21c: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 0017e220: jr ra */ {uint64_t target=cpu(31);/* delay 0017e224 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0017E228(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017e228);
 uint64_t incomingRa=cpu(31);
 /* 0017e228: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017e22c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017e230: jal 0x00176270 */ set(31,sx(UINT32_C(0x0017e238)));/* delay 0017e234 */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0017e238: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017e23c: move a0,v0 */ set(4,cpu(2));
 /* 0017e240: j 0x0017e008 */ /* delay 0017e244 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017E008(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017E248(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017e248);
 uint64_t incomingRa=cpu(31);
 /* 0017e248: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017e24c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017e250: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017e254: j 0x0017e008 */ /* delay 0017e258 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017E008(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017E818(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017e818);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 0017e818: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 0017e81c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017e820: move s0,a0 */ set(16,cpu(4));
 /* 0017e824: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017e828: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017e82c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017e830: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0017e834: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 0017e838: swc1 f21,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[21]);
 /* 0017e83c: swc1 f20,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);
 /* 0017e840: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017e844: sll a0,v0,0x3 */ set(4,sx((uint32_t)cpu(2)<<3));
 /* 0017e848: subu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(2)));
 /* 0017e84c: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
 /* 0017e850: jal 0x002a9038 */ set(31,sx(UINT32_C(0x0017e858)));/* delay 0017e854 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000068)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 0017e858: move s2,v0 */ set(18,cpu(2));
 /* 0017e85c: jal 0x002a9688 */ set(31,sx(UINT32_C(0x0017e864)));/* delay 0017e860 */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 0017e864: move s1,v0 */ set(17,cpu(2));
 /* 0017e868: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
 /* 0017e86c: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 0017e870: beq v0,zero,0x0017e8d8 */ {int take=(cpu(2)==cpu(0));/* delay 0017e874 */ set(3,cpu(17));if(take){goto L_0017e8d8;}}
 /* 0017e878: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0017e87c:;
 /* 0017e87c: ldl a0,0x7(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017e880: ldr a0,0x0(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017e884: ldl a1,0xf(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0017e888: ldr a1,0x8(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0017e88c: ldl a2,0x17(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 0017e890: ldr a2,0x10(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 0017e894: ldl a3,0x1f(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0017e898: ldr a3,0x18(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 0017e89c: sdl a0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),4,1);
 /* 0017e8a0: sdr a0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),4,0);
 /* 0017e8a4: sdl a1,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),5,1);
 /* 0017e8a8: sdr a1,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),5,0);
 /* 0017e8ac: sdl a2,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),6,1);
 /* 0017e8b0: sdr a2,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),6,0);
 /* 0017e8b4: sdl a3,0x1f(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000001f)),7,1);
 /* 0017e8b8: sdr a3,0x18(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000018)),7,0);
 /* 0017e8bc: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 0017e8c0: nop  */ 
 /* 0017e8c4: nop  */ 
 /* 0017e8c8: bne s0,v0,0x0017e87c */ {int take=(cpu(16)!=cpu(2));/* delay 0017e8cc */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0017e87c;}}
 /* 0017e8d0: b 0x0017e910 */ /* delay 0017e8d4 */ goto L_0017e910;
L_0017e8d8:;
 /* 0017e8d8: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0017e8dc:;
 /* 0017e8dc: ld a0,0x0(s0) */ restore(4,ea(16,(int32_t)UINT32_C(0x00000000)));
 /* 0017e8e0: ld a1,0x8(s0) */ restore(5,ea(16,(int32_t)UINT32_C(0x00000008)));
 /* 0017e8e4: ld a2,0x10(s0) */ restore(6,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017e8e8: ld a3,0x18(s0) */ restore(7,ea(16,(int32_t)UINT32_C(0x00000018)));
 /* 0017e8ec: sd a0,0x0(v1) */ save(4,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 0017e8f0: sd a1,0x8(v1) */ save(5,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 0017e8f4: sd a2,0x10(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 0017e8f8: sd a3,0x18(v1) */ save(7,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 0017e8fc: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 0017e900: nop  */ 
 /* 0017e904: nop  */ 
 /* 0017e908: bne s0,v0,0x0017e8dc */ {int take=(cpu(16)!=cpu(2));/* delay 0017e90c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0017e8dc;}}
L_0017e910:;
 /* 0017e910: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017e914: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017e918: ldl a0,0xf(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0017e91c: ldr a0,0x8(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0017e920: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 0017e924: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 0017e928: sdl a0,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),4,1);
 /* 0017e92c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 0017e930: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
 /* 0017e934: sdr a0,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),4,0);
 /* 0017e938: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 0017e93c: addiu v1,s1,0x68 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000068)));
 /* 0017e940: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 0017e944: lw a0,0x1c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000001c)));
 /* 0017e948: sw v1,0x50(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 0017e94c: sw s2,0x60(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(18));
 /* 0017e950: sw v0,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(2));
 /* 0017e954: sw zero,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(0));
 /* 0017e958: bne a0,zero,0x0017e968 */ {int take=(cpu(4)!=cpu(0));/* delay 0017e95c */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),f[21]);if(take){goto L_0017e968;}}
 /* 0017e960: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
 /* 0017e964: sw v0,0x1c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
L_0017e968:;
 /* 0017e968: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017e96c: lwc1 f20,-0x79e8(gp) */ f[20]=word(ea(28,(int32_t)UINT32_C(0xffff8618)));
 /* 0017e970: jal 0x00183268 */ set(31,sx(UINT32_C(0x0017e978)));/* delay 0017e974 */ set(4,sx((uint32_t)cpu(4)<<1));set(2,ps2BattleAction_00183268(cpu(4)));
 /* 0017e978: lw v1,0x4c(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000004c)));
 /* 0017e97c: swc1 f21,0x5c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000005c)),f[21]);
 /* 0017e980: sw v1,0x50(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 0017e984: sw v0,0x64(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000064)),(uint32_t)cpu(2));
 /* 0017e988: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017e98c: bltz a0,0x0017e9a8 */ {int take=((int64_t)cpu(4)<0);/* delay 0017e990 */ set(2,cpu(4)&UINT32_C(0x00000001));if(take){goto L_0017e9a8;}}
 /* 0017e994: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
 /* 0017e998: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 0017e99c: b 0x0017e9bc */ /* delay 0017e9a0 */ goto L_0017e9bc;
L_0017e9a8:;
 /* 0017e9a8: srl v1,a0,0x1 */ set(3,sx((uint32_t)cpu(4)>>1));
 /* 0017e9ac: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
 /* 0017e9b0: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
 /* 0017e9b4: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 0017e9b8: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
L_0017e9bc:;
 /* 0017e9bc: lwc1 f0,-0x79e4(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff861c)));
 /* 0017e9c0: move s3,zero */ set(19,cpu(0));
 /* 0017e9c4: nop  */ 
 /* 0017e9c8: nop  */ 
 /* 0017e9cc: div.S f21,f0,f1 */ f[21]=divs(f[0],f[1]);
 /* 0017e9d0: beq a0,zero,0x0017ea24 */ {int take=(cpu(4)==cpu(0));/* delay 0017e9d4 */ lw(16,ea(17,(int32_t)UINT32_C(0x0000001c)));if(take){goto L_0017ea24;}}
 /* 0017e9d8: lui s4,0x31 */ set(20,sx(UINT32_C(0x00310000)));
 /* 0017e9dc: move s2,zero */ set(18,cpu(0));
L_0017e9e0:;
 /* 0017e9e0: addiu a0,s4,0x6fe0 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0x00006fe0)));
 /* 0017e9e4: jal 0x002c0ba8 */ set(31,sx(UINT32_C(0x0017e9ec)));/* delay 0017e9e8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));set(2,ps2EffectRandomWord_002C0BA8(cpu(4)));
 /* 0017e9ec: lw v1,0x50(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000050)));
 /* 0017e9f0: divu v0,s0 */ statusDivu((uint32_t)cpu(2),(uint32_t)cpu(16));
 /* 0017e9f4: beql s0,zero,0x0017e9fc */ {int take=(cpu(16)==cpu(0));if(take){/* delay 0017e9f8 */ nocturneCompilerArithmeticTrap(7u);goto L_0017e9fc;}}
L_0017e9fc:;
 /* 0017e9fc: addu v1,s2,v1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(3)));
 /* 0017ea00: addiu s2,s2,0x1c */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x0000001c)));
 /* 0017ea04: swc1 f20,0x18(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000018)),f[20]);
 /* 0017ea08: mfhi a0 */ set(4,nocturneEffectHostHi());
 /* 0017ea0c: subu a0,zero,a0 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
 /* 0017ea10: sw a0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
 /* 0017ea14: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017ea18: sltu v0,s3,v0 */ set(2,cpu(19)<cpu(2));
 /* 0017ea1c: bne v0,zero,0x0017e9e0 */ {int take=(cpu(2)!=cpu(0));/* delay 0017ea20 */ f[20]=add(f[20],f[21]);if(take){goto L_0017e9e0;}}
L_0017ea24:;
 /* 0017ea24: move v0,s1 */ set(2,cpu(17));
 /* 0017ea28: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017ea2c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017ea30: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017ea34: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017ea38: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0017ea3c: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 0017ea40: lwc1 f21,0x38(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
 /* 0017ea44: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 0017ea48: jr ra */ {uint64_t target=cpu(31);/* delay 0017ea4c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0017EA50(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017ea50);
 uint64_t incomingRa=cpu(31);
 /* 0017ea50: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017ea54: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017ea58: jal 0x00176270 */ set(31,sx(UINT32_C(0x0017ea60)));/* delay 0017ea5c */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0017ea60: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017ea64: move a0,v0 */ set(4,cpu(2));
 /* 0017ea68: j 0x0017e818 */ /* delay 0017ea6c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017E818(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017EA70(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017ea70);
 uint64_t incomingRa=cpu(31);
 /* 0017ea70: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017ea74: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017ea78: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017ea7c: j 0x0017e818 */ /* delay 0017ea80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017E818(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017F100(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017f100);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 0017f100: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 0017f104: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017f108: move s0,a0 */ set(16,cpu(4));
 /* 0017f10c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017f110: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017f114: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017f118: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0017f11c: swc1 f21,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[21]);
 /* 0017f120: swc1 f20,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);
 /* 0017f124: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017f128: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
 /* 0017f12c: jal 0x002a9038 */ set(31,sx(UINT32_C(0x0017f134)));/* delay 0017f130 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000080)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 0017f134: move s2,v0 */ set(18,cpu(2));
 /* 0017f138: jal 0x002a9688 */ set(31,sx(UINT32_C(0x0017f140)));/* delay 0017f13c */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 0017f140: move s1,v0 */ set(17,cpu(2));
 /* 0017f144: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
 /* 0017f148: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 0017f14c: beq v0,zero,0x0017f1b8 */ {int take=(cpu(2)==cpu(0));/* delay 0017f150 */ set(3,cpu(17));if(take){goto L_0017f1b8;}}
 /* 0017f154: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0017f158:;
 /* 0017f158: ldl a0,0x7(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017f15c: ldr a0,0x0(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017f160: ldl a1,0xf(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0017f164: ldr a1,0x8(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0017f168: ldl a2,0x17(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 0017f16c: ldr a2,0x10(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 0017f170: ldl a3,0x1f(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0017f174: ldr a3,0x18(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 0017f178: sdl a0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),4,1);
 /* 0017f17c: sdr a0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),4,0);
 /* 0017f180: sdl a1,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),5,1);
 /* 0017f184: sdr a1,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),5,0);
 /* 0017f188: sdl a2,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),6,1);
 /* 0017f18c: sdr a2,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),6,0);
 /* 0017f190: sdl a3,0x1f(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000001f)),7,1);
 /* 0017f194: sdr a3,0x18(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000018)),7,0);
 /* 0017f198: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 0017f19c: nop  */ 
 /* 0017f1a0: nop  */ 
 /* 0017f1a4: bne s0,v0,0x0017f158 */ {int take=(cpu(16)!=cpu(2));/* delay 0017f1a8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0017f158;}}
 /* 0017f1ac: b 0x0017f1f0 */ /* delay 0017f1b0 */ goto L_0017f1f0;
L_0017f1b8:;
 /* 0017f1b8: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0017f1bc:;
 /* 0017f1bc: ld a0,0x0(s0) */ restore(4,ea(16,(int32_t)UINT32_C(0x00000000)));
 /* 0017f1c0: ld a1,0x8(s0) */ restore(5,ea(16,(int32_t)UINT32_C(0x00000008)));
 /* 0017f1c4: ld a2,0x10(s0) */ restore(6,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017f1c8: ld a3,0x18(s0) */ restore(7,ea(16,(int32_t)UINT32_C(0x00000018)));
 /* 0017f1cc: sd a0,0x0(v1) */ save(4,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 0017f1d0: sd a1,0x8(v1) */ save(5,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 0017f1d4: sd a2,0x10(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 0017f1d8: sd a3,0x18(v1) */ save(7,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 0017f1dc: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 0017f1e0: nop  */ 
 /* 0017f1e4: nop  */ 
 /* 0017f1e8: bne s0,v0,0x0017f1bc */ {int take=(cpu(16)!=cpu(2));/* delay 0017f1ec */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0017f1bc;}}
L_0017f1f0:;
 /* 0017f1f0: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017f1f4: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017f1f8: ldl a0,0xf(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0017f1fc: ldr a0,0x8(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0017f200: ldl a1,0x17(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 0017f204: ldr a1,0x10(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 0017f208: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 0017f20c: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 0017f210: sdl a0,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),4,1);
 /* 0017f214: sdr a0,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),4,0);
 /* 0017f218: sdl a1,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),5,1);
 /* 0017f21c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 0017f220: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
 /* 0017f224: sdr a1,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),5,0);
 /* 0017f228: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 0017f22c: addiu v1,s1,0x80 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000080)));
 /* 0017f230: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 0017f234: lwc1 f2,0x38(s1) */ f[2]=word(ea(17,(int32_t)UINT32_C(0x00000038)));
 /* 0017f238: lwc1 f0,0x30(s1) */ f[0]=word(ea(17,(int32_t)UINT32_C(0x00000030)));
 /* 0017f23c: lwc1 f1,0x34(s1) */ f[1]=word(ea(17,(int32_t)UINT32_C(0x00000034)));
 /* 0017f240: lw a0,0x1c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000001c)));
 /* 0017f244: sw v1,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(3));
 /* 0017f248: sw s2,0x78(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000078)),(uint32_t)cpu(18));
 /* 0017f24c: sw v0,0x60(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(2));
 /* 0017f250: swc1 f2,0x68(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000068)),f[2]);
 /* 0017f254: swc1 f0,0x70(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000070)),f[0]);
 /* 0017f258: swc1 f1,0x74(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000074)),f[1]);
 /* 0017f25c: sw zero,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(0));
 /* 0017f260: bne a0,zero,0x0017f270 */ {int take=(cpu(4)!=cpu(0));/* delay 0017f264 */ sw(ea(17,(int32_t)UINT32_C(0x00000064)),f[21]);if(take){goto L_0017f270;}}
 /* 0017f268: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
 /* 0017f26c: sw v0,0x1c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
L_0017f270:;
 /* 0017f270: lwc1 f20,-0x79d8(gp) */ f[20]=word(ea(28,(int32_t)UINT32_C(0xffff8628)));
 /* 0017f274: jal 0x00182b20 */ set(31,sx(UINT32_C(0x0017f27c)));/* delay 0017f278 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));set(2,ps2BattleAction_00182B20(cpu(4)));
 /* 0017f27c: lw v1,0x54(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000054)));
 /* 0017f280: swc1 f21,0x5c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000005c)),f[21]);
 /* 0017f284: sw v1,0x50(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 0017f288: sw v0,0x7c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000007c)),(uint32_t)cpu(2));
 /* 0017f28c: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017f290: bltz a0,0x0017f2a8 */ {int take=((int64_t)cpu(4)<0);/* delay 0017f294 */ set(2,cpu(4)&UINT32_C(0x00000001));if(take){goto L_0017f2a8;}}
 /* 0017f298: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
 /* 0017f29c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 0017f2a0: b 0x0017f2bc */ /* delay 0017f2a4 */ goto L_0017f2bc;
L_0017f2a8:;
 /* 0017f2a8: srl v1,a0,0x1 */ set(3,sx((uint32_t)cpu(4)>>1));
 /* 0017f2ac: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
 /* 0017f2b0: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
 /* 0017f2b4: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 0017f2b8: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
L_0017f2bc:;
 /* 0017f2bc: lwc1 f0,-0x79d4(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff862c)));
 /* 0017f2c0: move s2,zero */ set(18,cpu(0));
 /* 0017f2c4: nop  */ 
 /* 0017f2c8: nop  */ 
 /* 0017f2cc: div.S f21,f0,f1 */ f[21]=divs(f[0],f[1]);
 /* 0017f2d0: beq a0,zero,0x0017f324 */ {int take=(cpu(4)==cpu(0));/* delay 0017f2d4 */ lw(16,ea(17,(int32_t)UINT32_C(0x0000001c)));if(take){goto L_0017f324;}}
 /* 0017f2d8: lui s3,0x31 */ set(19,sx(UINT32_C(0x00310000)));
 /* 0017f2dc: nop  */ 
L_0017f2e0:;
 /* 0017f2e0: jal 0x002c0ba8 */ set(31,sx(UINT32_C(0x0017f2e8)));/* delay 0017f2e4 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00006fe0)));set(2,ps2EffectRandomWord_002C0BA8(cpu(4)));
 /* 0017f2e8: lw a1,0x58(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000058)));
 /* 0017f2ec: divu v0,s0 */ statusDivu((uint32_t)cpu(2),(uint32_t)cpu(16));
 /* 0017f2f0: sll v1,s2,0x4 */ set(3,sx((uint32_t)cpu(18)<<4));
 /* 0017f2f4: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
 /* 0017f2f8: beql s0,zero,0x0017f300 */ {int take=(cpu(16)==cpu(0));if(take){/* delay 0017f2fc */ nocturneCompilerArithmeticTrap(7u);goto L_0017f300;}}
L_0017f300:;
 /* 0017f300: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
 /* 0017f304: swc1 f20,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),f[20]);
 /* 0017f308: mfhi a0 */ set(4,nocturneEffectHostHi());
 /* 0017f30c: subu a0,zero,a0 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
 /* 0017f310: sw a0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
 /* 0017f314: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017f318: sltu v0,s2,v0 */ set(2,cpu(18)<cpu(2));
 /* 0017f31c: bne v0,zero,0x0017f2e0 */ {int take=(cpu(2)!=cpu(0));/* delay 0017f320 */ f[20]=add(f[20],f[21]);if(take){goto L_0017f2e0;}}
L_0017f324:;
 /* 0017f324: move v0,s1 */ set(2,cpu(17));
 /* 0017f328: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017f32c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017f330: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017f334: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017f338: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0017f33c: lwc1 f21,0x30(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 0017f340: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 0017f344: jr ra */ {uint64_t target=cpu(31);/* delay 0017f348 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0017F350(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017f350);
 uint64_t incomingRa=cpu(31);
 /* 0017f350: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017f354: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017f358: jal 0x00176270 */ set(31,sx(UINT32_C(0x0017f360)));/* delay 0017f35c */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0017f360: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017f364: move a0,v0 */ set(4,cpu(2));
 /* 0017f368: j 0x0017f100 */ /* delay 0017f36c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017F100(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017F370(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017f370);
 uint64_t incomingRa=cpu(31);
 /* 0017f370: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017f374: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017f378: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017f37c: j 0x0017f100 */ /* delay 0017f380 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017F100(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017FA08(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017fa08);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 0017fa08: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
 /* 0017fa0c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017fa10: move s0,a0 */ set(16,cpu(4));
 /* 0017fa14: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017fa18: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017fa1c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017fa20: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0017fa24: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017fa28: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
 /* 0017fa2c: jal 0x002a9038 */ set(31,sx(UINT32_C(0x0017fa34)));/* delay 0017fa30 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000064)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 0017fa34: move s2,v0 */ set(18,cpu(2));
 /* 0017fa38: jal 0x002a9688 */ set(31,sx(UINT32_C(0x0017fa40)));/* delay 0017fa3c */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 0017fa40: move s1,v0 */ set(17,cpu(2));
 /* 0017fa44: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
 /* 0017fa48: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 0017fa4c: beq v0,zero,0x0017fab8 */ {int take=(cpu(2)==cpu(0));/* delay 0017fa50 */ set(3,cpu(17));if(take){goto L_0017fab8;}}
 /* 0017fa54: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0017fa58:;
 /* 0017fa58: ldl a0,0x7(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017fa5c: ldr a0,0x0(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017fa60: ldl a1,0xf(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0017fa64: ldr a1,0x8(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0017fa68: ldl a2,0x17(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 0017fa6c: ldr a2,0x10(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 0017fa70: ldl a3,0x1f(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0017fa74: ldr a3,0x18(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 0017fa78: sdl a0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),4,1);
 /* 0017fa7c: sdr a0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),4,0);
 /* 0017fa80: sdl a1,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),5,1);
 /* 0017fa84: sdr a1,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),5,0);
 /* 0017fa88: sdl a2,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),6,1);
 /* 0017fa8c: sdr a2,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),6,0);
 /* 0017fa90: sdl a3,0x1f(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000001f)),7,1);
 /* 0017fa94: sdr a3,0x18(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000018)),7,0);
 /* 0017fa98: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 0017fa9c: nop  */ 
 /* 0017faa0: nop  */ 
 /* 0017faa4: bne s0,v0,0x0017fa58 */ {int take=(cpu(16)!=cpu(2));/* delay 0017faa8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0017fa58;}}
 /* 0017faac: b 0x0017faf0 */ /* delay 0017fab0 */ goto L_0017faf0;
L_0017fab8:;
 /* 0017fab8: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0017fabc:;
 /* 0017fabc: ld a0,0x0(s0) */ restore(4,ea(16,(int32_t)UINT32_C(0x00000000)));
 /* 0017fac0: ld a1,0x8(s0) */ restore(5,ea(16,(int32_t)UINT32_C(0x00000008)));
 /* 0017fac4: ld a2,0x10(s0) */ restore(6,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0017fac8: ld a3,0x18(s0) */ restore(7,ea(16,(int32_t)UINT32_C(0x00000018)));
 /* 0017facc: sd a0,0x0(v1) */ save(4,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 0017fad0: sd a1,0x8(v1) */ save(5,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 0017fad4: sd a2,0x10(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 0017fad8: sd a3,0x18(v1) */ save(7,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 0017fadc: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 0017fae0: nop  */ 
 /* 0017fae4: nop  */ 
 /* 0017fae8: bne s0,v0,0x0017fabc */ {int take=(cpu(16)!=cpu(2));/* delay 0017faec */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0017fabc;}}
L_0017faf0:;
 /* 0017faf0: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0017faf4: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0017faf8: lw a0,0x8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000008)));
 /* 0017fafc: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 0017fb00: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 0017fb04: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 0017fb08: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
 /* 0017fb0c: sw a0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
 /* 0017fb10: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 0017fb14: addiu v1,s1,0x64 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000064)));
 /* 0017fb18: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 0017fb1c: lw a0,0x20(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000020)));
 /* 0017fb20: sw v1,0x4c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(3));
 /* 0017fb24: sw s2,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(18));
 /* 0017fb28: sw v0,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));
 /* 0017fb2c: swc1 f0,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),f[0]);
 /* 0017fb30: bne a0,zero,0x0017fb40 */ {int take=(cpu(4)!=cpu(0));/* delay 0017fb34 */ sw(ea(17,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(0));if(take){goto L_0017fb40;}}
 /* 0017fb38: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
 /* 0017fb3c: sw v0,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
L_0017fb40:;
 /* 0017fb40: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017fb44: jal 0x00182b20 */ set(31,sx(UINT32_C(0x0017fb4c)));/* delay 0017fb48 */ set(18,cpu(0));set(2,ps2BattleAction_00182B20(cpu(4)));
 /* 0017fb4c: lw v1,0x48(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000048)));
 /* 0017fb50: sw v0,0x60(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(2));
 /* 0017fb54: sw v1,0x50(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 0017fb58: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017fb5c: beq v0,zero,0x0017fba8 */ {int take=(cpu(2)==cpu(0));/* delay 0017fb60 */ lw(16,ea(17,(int32_t)UINT32_C(0x00000020)));if(take){goto L_0017fba8;}}
 /* 0017fb64: lui s3,0x31 */ set(19,sx(UINT32_C(0x00310000)));
L_0017fb68:;
 /* 0017fb68: jal 0x002c0ba8 */ set(31,sx(UINT32_C(0x0017fb70)));/* delay 0017fb6c */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00006fe0)));set(2,ps2EffectRandomWord_002C0BA8(cpu(4)));
 /* 0017fb70: lw a1,0x4c(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x0000004c)));
 /* 0017fb74: divu v0,s0 */ statusDivu((uint32_t)cpu(2),(uint32_t)cpu(16));
 /* 0017fb78: sll v1,s2,0x5 */ set(3,sx((uint32_t)cpu(18)<<5));
 /* 0017fb7c: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
 /* 0017fb80: beql s0,zero,0x0017fb88 */ {int take=(cpu(16)==cpu(0));if(take){/* delay 0017fb84 */ nocturneCompilerArithmeticTrap(7u);goto L_0017fb88;}}
L_0017fb88:;
 /* 0017fb88: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
 /* 0017fb8c: mfhi a0 */ set(4,nocturneEffectHostHi());
 /* 0017fb90: subu a0,zero,a0 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
 /* 0017fb94: sw a0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
 /* 0017fb98: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0017fb9c: sltu v0,s2,v0 */ set(2,cpu(18)<cpu(2));
 /* 0017fba0: bne v0,zero,0x0017fb68 */ {int take=(cpu(2)!=cpu(0));/* delay 0017fba4 */ if(take){goto L_0017fb68;}}
L_0017fba8:;
 /* 0017fba8: move v0,s1 */ set(2,cpu(17));
 /* 0017fbac: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017fbb0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0017fbb4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0017fbb8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0017fbbc: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0017fbc0: jr ra */ {uint64_t target=cpu(31);/* delay 0017fbc4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0017FBC8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017fbc8);
 uint64_t incomingRa=cpu(31);
 /* 0017fbc8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017fbcc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017fbd0: jal 0x00176270 */ set(31,sx(UINT32_C(0x0017fbd8)));/* delay 0017fbd4 */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0017fbd8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017fbdc: move a0,v0 */ set(4,cpu(2));
 /* 0017fbe0: j 0x0017fa08 */ /* delay 0017fbe4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017FA08(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0017FBE8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0017fbe8);
 uint64_t incomingRa=cpu(31);
 /* 0017fbe8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0017fbec: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017fbf0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0017fbf4: j 0x0017fa08 */ /* delay 0017fbf8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0017FA08(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_00180958(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00180958);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00180958: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
 /* 0018095c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00180960: move s0,a0 */ set(16,cpu(4));
 /* 00180964: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00180968: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0018096c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 00180970: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 00180974: swc1 f20,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);
 /* 00180978: lw a0,0x10(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 0018097c: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
 /* 00180980: jal 0x002a9038 */ set(31,sx(UINT32_C(0x00180988)));/* delay 00180984 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000000e8)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 00180988: move s2,v0 */ set(18,cpu(2));
 /* 0018098c: jal 0x002a9688 */ set(31,sx(UINT32_C(0x00180994)));/* delay 00180990 */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 00180994: move s1,v0 */ set(17,cpu(2));
 /* 00180998: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
 /* 0018099c: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 001809a0: beq v0,zero,0x00180a08 */ {int take=(cpu(2)==cpu(0));/* delay 001809a4 */ set(3,cpu(17));if(take){goto L_00180a08;}}
 /* 001809a8: addiu v0,s0,0xc0 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x000000c0)));
L_001809ac:;
 /* 001809ac: ldl a0,0x7(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 001809b0: ldr a0,0x0(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 001809b4: ldl a1,0xf(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 001809b8: ldr a1,0x8(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 001809bc: ldl a2,0x17(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 001809c0: ldr a2,0x10(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 001809c4: ldl a3,0x1f(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 001809c8: ldr a3,0x18(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 001809cc: sdl a0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),4,1);
 /* 001809d0: sdr a0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),4,0);
 /* 001809d4: sdl a1,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),5,1);
 /* 001809d8: sdr a1,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),5,0);
 /* 001809dc: sdl a2,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),6,1);
 /* 001809e0: sdr a2,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),6,0);
 /* 001809e4: sdl a3,0x1f(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000001f)),7,1);
 /* 001809e8: sdr a3,0x18(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000018)),7,0);
 /* 001809ec: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 001809f0: nop  */ 
 /* 001809f4: nop  */ 
 /* 001809f8: bne s0,v0,0x001809ac */ {int take=(cpu(16)!=cpu(2));/* delay 001809fc */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_001809ac;}}
 /* 00180a00: b 0x00180a40 */ /* delay 00180a04 */ goto L_00180a40;
L_00180a08:;
 /* 00180a08: addiu v0,s0,0xc0 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x000000c0)));
L_00180a0c:;
 /* 00180a0c: ld a0,0x0(s0) */ restore(4,ea(16,(int32_t)UINT32_C(0x00000000)));
 /* 00180a10: ld a1,0x8(s0) */ restore(5,ea(16,(int32_t)UINT32_C(0x00000008)));
 /* 00180a14: ld a2,0x10(s0) */ restore(6,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 00180a18: ld a3,0x18(s0) */ restore(7,ea(16,(int32_t)UINT32_C(0x00000018)));
 /* 00180a1c: sd a0,0x0(v1) */ save(4,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 00180a20: sd a1,0x8(v1) */ save(5,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 00180a24: sd a2,0x10(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 00180a28: sd a3,0x18(v1) */ save(7,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 00180a2c: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 00180a30: nop  */ 
 /* 00180a34: nop  */ 
 /* 00180a38: bne s0,v0,0x00180a0c */ {int take=(cpu(16)!=cpu(2));/* delay 00180a3c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_00180a0c;}}
L_00180a40:;
 /* 00180a40: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 00180a44: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 00180a48: ldl a0,0xf(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 00180a4c: ldr a0,0x8(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 00180a50: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 00180a54: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 00180a58: sdl a0,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),4,1);
 /* 00180a5c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 00180a60: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
 /* 00180a64: sdr a0,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),4,0);
 /* 00180a68: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 00180a6c: addiu v1,s1,0xe8 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x000000e8)));
 /* 00180a70: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 00180a74: lw a0,0x1c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000001c)));
 /* 00180a78: sw v1,0xd0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000d0)),(uint32_t)cpu(3));
 /* 00180a7c: sw s2,0xe0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000e0)),(uint32_t)cpu(18));
 /* 00180a80: sw v0,0xd8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000d8)),(uint32_t)cpu(2));
 /* 00180a84: sw zero,0xd4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000d4)),(uint32_t)cpu(0));
 /* 00180a88: bne a0,zero,0x00180a98 */ {int take=(cpu(4)!=cpu(0));/* delay 00180a8c */ sw(ea(17,(int32_t)UINT32_C(0x000000dc)),f[20]);if(take){goto L_00180a98;}}
 /* 00180a90: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
 /* 00180a94: sw v0,0x1c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
L_00180a98:;
 /* 00180a98: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 00180a9c: move s2,zero */ set(18,cpu(0));
 /* 00180aa0: jal 0x00183268 */ set(31,sx(UINT32_C(0x00180aa8)));/* delay 00180aa4 */ set(4,sx((uint32_t)cpu(4)<<1));set(2,ps2BattleAction_00183268(cpu(4)));
 /* 00180aa8: lw v1,0x4c(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000004c)));
 /* 00180aac: swc1 f20,0x5c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000005c)),f[20]);
 /* 00180ab0: sw v1,0x50(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 00180ab4: sw v0,0xe4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000e4)),(uint32_t)cpu(2));
 /* 00180ab8: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 00180abc: beq v0,zero,0x00180b08 */ {int take=(cpu(2)==cpu(0));/* delay 00180ac0 */ lw(16,ea(17,(int32_t)UINT32_C(0x0000001c)));if(take){goto L_00180b08;}}
 /* 00180ac4: lui s3,0x31 */ set(19,sx(UINT32_C(0x00310000)));
L_00180ac8:;
 /* 00180ac8: jal 0x002c0ba8 */ set(31,sx(UINT32_C(0x00180ad0)));/* delay 00180acc */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0x00006fe0)));set(2,ps2EffectRandomWord_002C0BA8(cpu(4)));
 /* 00180ad0: lw a1,0xd0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x000000d0)));
 /* 00180ad4: divu v0,s0 */ statusDivu((uint32_t)cpu(2),(uint32_t)cpu(16));
 /* 00180ad8: sll v1,s2,0x5 */ set(3,sx((uint32_t)cpu(18)<<5));
 /* 00180adc: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
 /* 00180ae0: beql s0,zero,0x00180ae8 */ {int take=(cpu(16)==cpu(0));if(take){/* delay 00180ae4 */ nocturneCompilerArithmeticTrap(7u);goto L_00180ae8;}}
L_00180ae8:;
 /* 00180ae8: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
 /* 00180aec: mfhi a0 */ set(4,nocturneEffectHostHi());
 /* 00180af0: subu a0,zero,a0 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
 /* 00180af4: sw a0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
 /* 00180af8: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 00180afc: sltu v0,s2,v0 */ set(2,cpu(18)<cpu(2));
 /* 00180b00: bne v0,zero,0x00180ac8 */ {int take=(cpu(2)!=cpu(0));/* delay 00180b04 */ if(take){goto L_00180ac8;}}
L_00180b08:;
 /* 00180b08: move v0,s1 */ set(2,cpu(17));
 /* 00180b0c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00180b10: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00180b14: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00180b18: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 00180b1c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 00180b20: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 00180b24: jr ra */ {uint64_t target=cpu(31);/* delay 00180b28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_00180B30(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00180b30);
 uint64_t incomingRa=cpu(31);
 /* 00180b30: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 00180b34: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00180b38: jal 0x00176270 */ set(31,sx(UINT32_C(0x00180b40)));/* delay 00180b3c */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 00180b40: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00180b44: move a0,v0 */ set(4,cpu(2));
 /* 00180b48: j 0x00180958 */ /* delay 00180b4c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_00180958(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_00180B50(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00180b50);
 uint64_t incomingRa=cpu(31);
 /* 00180b50: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 00180b54: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00180b58: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00180b5c: j 0x00180958 */ /* delay 00180b60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_00180958(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_001812A8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001812a8);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 001812a8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 001812ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001812b0: move s0,a0 */ set(16,cpu(4));
 /* 001812b4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001812b8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001812bc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001812c0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 001812c4: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 001812c8: swc1 f21,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[21]);
 /* 001812cc: swc1 f20,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);
 /* 001812d0: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 001812d4: sll a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)<<2));
 /* 001812d8: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
 /* 001812dc: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
 /* 001812e0: jal 0x002a9038 */ set(31,sx(UINT32_C(0x001812e8)));/* delay 001812e4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000068)));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 001812e8: move s2,v0 */ set(18,cpu(2));
 /* 001812ec: jal 0x002a9688 */ set(31,sx(UINT32_C(0x001812f4)));/* delay 001812f0 */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 001812f4: move s1,v0 */ set(17,cpu(2));
 /* 001812f8: or v0,s0,s1 */ set(2,cpu(16)|cpu(17));
 /* 001812fc: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 00181300: beq v0,zero,0x00181368 */ {int take=(cpu(2)==cpu(0));/* delay 00181304 */ set(3,cpu(17));if(take){goto L_00181368;}}
 /* 00181308: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0018130c:;
 /* 0018130c: ldl a0,0x7(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 00181310: ldr a0,0x0(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 00181314: ldl a1,0xf(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 00181318: ldr a1,0x8(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0018131c: ldl a2,0x17(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 00181320: ldr a2,0x10(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 00181324: ldl a3,0x1f(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 00181328: ldr a3,0x18(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 0018132c: sdl a0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),4,1);
 /* 00181330: sdr a0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),4,0);
 /* 00181334: sdl a1,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),5,1);
 /* 00181338: sdr a1,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),5,0);
 /* 0018133c: sdl a2,0x17(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000017)),6,1);
 /* 00181340: sdr a2,0x10(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000010)),6,0);
 /* 00181344: sdl a3,0x1f(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000001f)),7,1);
 /* 00181348: sdr a3,0x18(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000018)),7,0);
 /* 0018134c: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 00181350: nop  */ 
 /* 00181354: nop  */ 
 /* 00181358: bne s0,v0,0x0018130c */ {int take=(cpu(16)!=cpu(2));/* delay 0018135c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0018130c;}}
 /* 00181360: b 0x001813a0 */ /* delay 00181364 */ goto L_001813a0;
L_00181368:;
 /* 00181368: addiu v0,s0,0x40 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
L_0018136c:;
 /* 0018136c: ld a0,0x0(s0) */ restore(4,ea(16,(int32_t)UINT32_C(0x00000000)));
 /* 00181370: ld a1,0x8(s0) */ restore(5,ea(16,(int32_t)UINT32_C(0x00000008)));
 /* 00181374: ld a2,0x10(s0) */ restore(6,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 00181378: ld a3,0x18(s0) */ restore(7,ea(16,(int32_t)UINT32_C(0x00000018)));
 /* 0018137c: sd a0,0x0(v1) */ save(4,ea(3,(int32_t)UINT32_C(0x00000000)));
 /* 00181380: sd a1,0x8(v1) */ save(5,ea(3,(int32_t)UINT32_C(0x00000008)));
 /* 00181384: sd a2,0x10(v1) */ save(6,ea(3,(int32_t)UINT32_C(0x00000010)));
 /* 00181388: sd a3,0x18(v1) */ save(7,ea(3,(int32_t)UINT32_C(0x00000018)));
 /* 0018138c: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
 /* 00181390: nop  */ 
 /* 00181394: nop  */ 
 /* 00181398: bne s0,v0,0x0018136c */ {int take=(cpu(16)!=cpu(2));/* delay 0018139c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));if(take){goto L_0018136c;}}
L_001813a0:;
 /* 001813a0: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 001813a4: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 001813a8: ldl a0,0xf(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 001813ac: ldr a0,0x8(s0) */ loadPartial(4,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 001813b0: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 001813b4: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 001813b8: sdl a0,0xf(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x0000000f)),4,1);
 /* 001813bc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 001813c0: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
 /* 001813c4: sdr a0,0x8(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000008)),4,0);
 /* 001813c8: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 001813cc: addiu v1,s1,0x68 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000068)));
 /* 001813d0: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 001813d4: lw a0,0x20(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000020)));
 /* 001813d8: sw v1,0x50(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 001813dc: sw s2,0x60(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(18));
 /* 001813e0: sw v0,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(2));
 /* 001813e4: sw zero,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(0));
 /* 001813e8: bne a0,zero,0x001813f8 */ {int take=(cpu(4)!=cpu(0));/* delay 001813ec */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),f[21]);if(take){goto L_001813f8;}}
 /* 001813f0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
 /* 001813f4: sw v0,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
L_001813f8:;
 /* 001813f8: lwc1 f20,-0x79b4(gp) */ f[20]=word(ea(28,(int32_t)UINT32_C(0xffff864c)));
 /* 001813fc: jal 0x00182b20 */ set(31,sx(UINT32_C(0x00181404)));/* delay 00181400 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));set(2,ps2BattleAction_00182B20(cpu(4)));
 /* 00181404: lw v1,0x4c(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000004c)));
 /* 00181408: swc1 f21,0x5c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000005c)),f[21]);
 /* 0018140c: sw v1,0x50(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 00181410: sw v0,0x64(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000064)),(uint32_t)cpu(2));
 /* 00181414: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 00181418: bltz a0,0x00181430 */ {int take=((int64_t)cpu(4)<0);/* delay 0018141c */ set(2,cpu(4)&UINT32_C(0x00000001));if(take){goto L_00181430;}}
 /* 00181420: mtc1 a0,f1 */ f[1]=(uint32_t)cpu(4);
 /* 00181424: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 00181428: b 0x00181444 */ /* delay 0018142c */ goto L_00181444;
L_00181430:;
 /* 00181430: srl v1,a0,0x1 */ set(3,sx((uint32_t)cpu(4)>>1));
 /* 00181434: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
 /* 00181438: mtc1 v0,f1 */ f[1]=(uint32_t)cpu(2);
 /* 0018143c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
 /* 00181440: add.S f1,f1,f1 */ f[1]=add(f[1],f[1]);
L_00181444:;
 /* 00181444: lwc1 f0,-0x79b0(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8650)));
 /* 00181448: move s3,zero */ set(19,cpu(0));
 /* 0018144c: nop  */ 
 /* 00181450: nop  */ 
 /* 00181454: div.S f21,f0,f1 */ f[21]=divs(f[0],f[1]);
 /* 00181458: beq a0,zero,0x001814ac */ {int take=(cpu(4)==cpu(0));/* delay 0018145c */ lw(16,ea(17,(int32_t)UINT32_C(0x00000020)));if(take){goto L_001814ac;}}
 /* 00181460: lui s4,0x31 */ set(20,sx(UINT32_C(0x00310000)));
 /* 00181464: move s2,zero */ set(18,cpu(0));
L_00181468:;
 /* 00181468: addiu a0,s4,0x6fe0 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0x00006fe0)));
 /* 0018146c: jal 0x002c0ba8 */ set(31,sx(UINT32_C(0x00181474)));/* delay 00181470 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));set(2,ps2EffectRandomWord_002C0BA8(cpu(4)));
 /* 00181474: lw v1,0x50(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000050)));
 /* 00181478: divu v0,s0 */ statusDivu((uint32_t)cpu(2),(uint32_t)cpu(16));
 /* 0018147c: beql s0,zero,0x00181484 */ {int take=(cpu(16)==cpu(0));if(take){/* delay 00181480 */ nocturneCompilerArithmeticTrap(7u);goto L_00181484;}}
L_00181484:;
 /* 00181484: addu v1,s2,v1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(3)));
 /* 00181488: addiu s2,s2,0x14 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
 /* 0018148c: swc1 f20,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),f[20]);
 /* 00181490: mfhi a0 */ set(4,nocturneEffectHostHi());
 /* 00181494: subu a0,zero,a0 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
 /* 00181498: sw a0,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
 /* 0018149c: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 001814a0: sltu v0,s3,v0 */ set(2,cpu(19)<cpu(2));
 /* 001814a4: bne v0,zero,0x00181468 */ {int take=(cpu(2)!=cpu(0));/* delay 001814a8 */ f[20]=add(f[20],f[21]);if(take){goto L_00181468;}}
L_001814ac:;
 /* 001814ac: move v0,s1 */ set(2,cpu(17));
 /* 001814b0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001814b4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001814b8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001814bc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001814c0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 001814c4: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 001814c8: lwc1 f21,0x38(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
 /* 001814cc: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 001814d0: jr ra */ {uint64_t target=cpu(31);/* delay 001814d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_001814D8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001814d8);
 uint64_t incomingRa=cpu(31);
 /* 001814d8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 001814dc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001814e0: jal 0x00176270 */ set(31,sx(UINT32_C(0x001814e8)));/* delay 001814e4 */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 001814e8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001814ec: move a0,v0 */ set(4,cpu(2));
 /* 001814f0: j 0x001812a8 */ /* delay 001814f4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_001812A8(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_001814F8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001814f8);
 uint64_t incomingRa=cpu(31);
 /* 001814f8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 001814fc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00181500: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00181504: j 0x001812a8 */ /* delay 00181508 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_001812A8(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_00182B20(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00182b20);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00182b20: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 00182b24: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
 /* 00182b28: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 00182b2c: addu s4,v0,a0 */ set(20,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
 /* 00182b30: sll v1,s4,0x2 */ set(3,sx((uint32_t)cpu(20)<<2));
 /* 00182b34: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00182b38: addu v1,v1,s4 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(20)));
 /* 00182b3c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00182b40: sll s1,v1,0x2 */ set(17,sx((uint32_t)cpu(3)<<2));
 /* 00182b44: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00182b48: sra v1,s1,0x4 */ set(3,sx((uint32_t)((int32_t)cpu(17)>>4)));
 /* 00182b4c: andi v0,s1,0xf */ set(2,cpu(17)&UINT32_C(0x0000000f));
 /* 00182b50: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 00182b54: addiu a0,v1,0x1 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
 /* 00182b58: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 00182b5c: beq v0,zero,0x00182b70 */ {int take=(cpu(2)==cpu(0));/* delay 00182b60 */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);if(take){goto L_00182b70;}}
 /* 00182b64: b 0x00182b74 */ /* delay 00182b68 */ set(2,sx((uint32_t)cpu(4)<<4));goto L_00182b74;
L_00182b70:;
 /* 00182b70: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
L_00182b74:;
 /* 00182b74: move s1,v0 */ set(17,cpu(2));
 /* 00182b78: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 00182b7c: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
 /* 00182b80: addiu s2,s1,0x70 */ set(18,sx((uint32_t)cpu(17)+UINT32_C(0x00000070)));
 /* 00182b84: jal 0x002a9038 */ set(31,sx(UINT32_C(0x00182b8c)));/* delay 00182b88 */ set(4,cpu(18));set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 00182b8c: move s3,v0 */ set(19,cpu(2));
 /* 00182b90: jal 0x002a9688 */ set(31,sx(UINT32_C(0x00182b98)));/* delay 00182b94 */ set(4,cpu(19));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 00182b98: move a1,zero */ set(5,cpu(0));
 /* 00182b9c: move s0,v0 */ set(16,cpu(2));
 /* 00182ba0: move a2,s2 */ set(6,cpu(18));
 /* 00182ba4: move a0,s0 */ set(4,cpu(16));
 /* 00182ba8: jal 0x002d4558 */ set(31,sx(UINT32_C(0x00182bb0)));/* delay 00182bac */ set(17,sx((uint32_t)cpu(16)+(uint32_t)cpu(17)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
 /* 00182bb0: sw s0,0x60(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(16));
 /* 00182bb4: sll v1,s4,0x4 */ set(3,sx((uint32_t)cpu(20)<<4));
 /* 00182bb8: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 00182bbc: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
 /* 00182bc0: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
 /* 00182bc4: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 00182bc8: sw v1,0x50(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 00182bcc: sw s0,0x64(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000064)),(uint32_t)cpu(16));
 /* 00182bd0: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
 /* 00182bd4: sw s4,0x58(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(20));
 /* 00182bd8: addiu s0,s0,-0x5308 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffacf8)));
 /* 00182bdc: sw s3,0x6c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000006c)),(uint32_t)cpu(19));
 /* 00182be0: swc1 f20,0x5c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000005c)),f[20]);
 /* 00182be4: jal 0x002b31e8 */ set(31,sx(UINT32_C(0x00182bec)));/* delay 00182be8 */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));set(2,ps2EffectMatCreate_002B31E8());
 /* 00182bec: mov.S f12,f20 */ f[12]=f[20];
 /* 00182bf0: sw v0,0x68(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000068)),(uint32_t)cpu(2));
 /* 00182bf4: jal 0x002b2ed8 */ set(31,sx(UINT32_C(0x00182bfc)));/* delay 00182bf8 */ set(4,cpu(2));ps2BattleActionMaterialSetConstant_002B2ED8(cpu(4),real(f[12]));
 /* 00182bfc: move a1,zero */ set(5,cpu(0));
 /* 00182c00: move a0,s0 */ set(4,cpu(16));
 /* 00182c04: jal 0x002d4558 */ set(31,sx(UINT32_C(0x00182c0c)));/* delay 00182c08 */ set(6,sx(UINT32_C(0x0000002c)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
 /* 00182c0c: li v1,0x4000 */ set(3,sx(UINT32_C(0x00004000)));
 /* 00182c10: move v0,s1 */ set(2,cpu(17));
 /* 00182c14: sh v1,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
 /* 00182c18: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00182c1c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00182c20: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00182c24: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 00182c28: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 00182c2c: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 00182c30: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 00182c34: jr ra */ {uint64_t target=cpu(31);/* delay 00182c38 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_00182F68(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00182f68);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00182f68: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 00182f6c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00182f70: sll s2,a0,0x1 */ set(18,sx((uint32_t)cpu(4)<<1));
 /* 00182f74: addu s2,s2,a0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(4)));
 /* 00182f78: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00182f7c: sll s0,s2,0x2 */ set(16,sx((uint32_t)cpu(18)<<2));
 /* 00182f80: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 00182f84: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
 /* 00182f88: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00182f8c: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
 /* 00182f90: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 00182f94: addiu s3,s0,0x70 */ set(19,sx((uint32_t)cpu(16)+UINT32_C(0x00000070)));
 /* 00182f98: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 00182f9c: move a0,s3 */ set(4,cpu(19));
 /* 00182fa0: jal 0x002a9038 */ set(31,sx(UINT32_C(0x00182fa8)));/* delay 00182fa4 */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 00182fa8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 00182fac: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
 /* 00182fb0: move s4,v0 */ set(20,cpu(2));
 /* 00182fb4: jal 0x002a9688 */ set(31,sx(UINT32_C(0x00182fbc)));/* delay 00182fb8 */ set(4,cpu(20));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 00182fbc: move a1,zero */ set(5,cpu(0));
 /* 00182fc0: move s1,v0 */ set(17,cpu(2));
 /* 00182fc4: move a2,s3 */ set(6,cpu(19));
 /* 00182fc8: move a0,s1 */ set(4,cpu(17));
 /* 00182fcc: jal 0x002d4558 */ set(31,sx(UINT32_C(0x00182fd4)));/* delay 00182fd0 */ set(16,sx((uint32_t)cpu(17)+(uint32_t)cpu(16)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
 /* 00182fd4: sw s1,0x60(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(17));
 /* 00182fd8: sll v1,s2,0x4 */ set(3,sx((uint32_t)cpu(18)<<4));
 /* 00182fdc: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 00182fe0: addu s1,s1,v1 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(3)));
 /* 00182fe4: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
 /* 00182fe8: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 00182fec: sw v1,0x50(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 00182ff0: sw s1,0x64(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000064)),(uint32_t)cpu(17));
 /* 00182ff4: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
 /* 00182ff8: sw s2,0x58(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(18));
 /* 00182ffc: addiu s1,s1,-0x5308 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffacf8)));
 /* 00183000: sw s4,0x6c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000006c)),(uint32_t)cpu(20));
 /* 00183004: swc1 f20,0x5c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000005c)),f[20]);
 /* 00183008: jal 0x002b31e8 */ set(31,sx(UINT32_C(0x00183010)));/* delay 0018300c */ sw(ea(16,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));set(2,ps2EffectMatCreate_002B31E8());
 /* 00183010: mov.S f12,f20 */ f[12]=f[20];
 /* 00183014: sw v0,0x68(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000068)),(uint32_t)cpu(2));
 /* 00183018: jal 0x002b2ed8 */ set(31,sx(UINT32_C(0x00183020)));/* delay 0018301c */ set(4,cpu(2));ps2BattleActionMaterialSetConstant_002B2ED8(cpu(4),real(f[12]));
 /* 00183020: move a1,zero */ set(5,cpu(0));
 /* 00183024: move a0,s1 */ set(4,cpu(17));
 /* 00183028: jal 0x002d4558 */ set(31,sx(UINT32_C(0x00183030)));/* delay 0018302c */ set(6,sx(UINT32_C(0x0000002c)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
 /* 00183030: li v1,0x4000 */ set(3,sx(UINT32_C(0x00004000)));
 /* 00183034: move v0,s0 */ set(2,cpu(16));
 /* 00183038: sh v1,0x4(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
 /* 0018303c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00183040: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00183044: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00183048: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0018304c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 00183050: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 00183054: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 00183058: jr ra */ {uint64_t target=cpu(31);/* delay 0018305c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_00183268(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x00183268);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 00183268: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
 /* 0018326c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00183270: move s2,a0 */ set(18,cpu(4));
 /* 00183274: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00183278: sll s0,s2,0x4 */ set(16,sx((uint32_t)cpu(18)<<4));
 /* 0018327c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 00183280: sll s5,s2,0x2 */ set(21,sx((uint32_t)cpu(18)<<2));
 /* 00183284: addu s0,s0,s5 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));
 /* 00183288: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 0018328c: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
 /* 00183290: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00183294: addiu s3,s0,0x70 */ set(19,sx((uint32_t)cpu(16)+UINT32_C(0x00000070)));
 /* 00183298: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 0018329c: move a0,s3 */ set(4,cpu(19));
 /* 001832a0: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 001832a4: jal 0x002a9038 */ set(31,sx(UINT32_C(0x001832ac)));/* delay 001832a8 */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[20]);set(2,ps2EffectMemoryHandleAllocate_002A9038(cpu(4)));
 /* 001832ac: move s4,v0 */ set(20,cpu(2));
 /* 001832b0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 001832b4: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
 /* 001832b8: move a0,s4 */ set(4,cpu(20));
 /* 001832bc: jal 0x002a9688 */ set(31,sx(UINT32_C(0x001832c4)));/* delay 001832c0 */ set(18,sx((uint32_t)cpu(18)<<6));set(2,ps2EffectMemoryHandleAcquirePointer_002A9688(cpu(4)));
 /* 001832c4: move a1,zero */ set(5,cpu(0));
 /* 001832c8: move s1,v0 */ set(17,cpu(2));
 /* 001832cc: move a2,s3 */ set(6,cpu(19));
 /* 001832d0: move a0,s1 */ set(4,cpu(17));
 /* 001832d4: jal 0x002d4558 */ set(31,sx(UINT32_C(0x001832dc)));/* delay 001832d8 */ set(16,sx((uint32_t)cpu(17)+(uint32_t)cpu(16)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
 /* 001832dc: sw s1,0x60(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000060)),(uint32_t)cpu(17));
 /* 001832e0: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
 /* 001832e4: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
 /* 001832e8: addu s1,s1,s2 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(18)));
 /* 001832ec: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
 /* 001832f0: sw v1,0x50(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
 /* 001832f4: sw s1,0x64(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000064)),(uint32_t)cpu(17));
 /* 001832f8: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
 /* 001832fc: sw s5,0x58(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(21));
 /* 00183300: addiu s1,s1,-0x5308 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffacf8)));
 /* 00183304: sw s4,0x6c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000006c)),(uint32_t)cpu(20));
 /* 00183308: swc1 f20,0x5c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000005c)),f[20]);
 /* 0018330c: jal 0x002b31e8 */ set(31,sx(UINT32_C(0x00183314)));/* delay 00183310 */ sw(ea(16,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));set(2,ps2EffectMatCreate_002B31E8());
 /* 00183314: mov.S f12,f20 */ f[12]=f[20];
 /* 00183318: sw v0,0x68(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000068)),(uint32_t)cpu(2));
 /* 0018331c: jal 0x002b2ed8 */ set(31,sx(UINT32_C(0x00183324)));/* delay 00183320 */ set(4,cpu(2));ps2BattleActionMaterialSetConstant_002B2ED8(cpu(4),real(f[12]));
 /* 00183324: move a1,zero */ set(5,cpu(0));
 /* 00183328: move a0,s1 */ set(4,cpu(17));
 /* 0018332c: jal 0x002d4558 */ set(31,sx(UINT32_C(0x00183334)));/* delay 00183330 */ set(6,sx(UINT32_C(0x0000002c)));set(2,ps2EffectGuestMemset_002D4558(cpu(4),cpu(5),cpu(6)));
 /* 00183334: li v1,0x4000 */ set(3,sx(UINT32_C(0x00004000)));
 /* 00183338: move v0,s0 */ set(2,cpu(16));
 /* 0018333c: sh v1,0x4(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
 /* 00183340: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 00183344: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00183348: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0018334c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 00183350: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
 /* 00183354: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
 /* 00183358: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
 /* 0018335c: lwc1 f20,0x38(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
 /* 00183360: jr ra */ {uint64_t target=cpu(31);/* delay 00183364 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0018E390(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018e390);
 uint64_t incomingRa=cpu(31);
 /* 0018e390: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 0018e394: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018e398: move s1,a0 */ set(17,cpu(4));
 /* 0018e39c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018e3a0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0018e3a4: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x0018e3ac)));/* delay 0018e3a8 */ set(4,sx(UINT32_C(0x0000003c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 0018e3ac: addiu a0,s1,0x18 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));
 /* 0018e3b0: jal 0x001a2e28 */ set(31,sx(UINT32_C(0x0018e3b8)));/* delay 0018e3b4 */ set(16,cpu(2));set(2,ps2BattleAction_001A2E28(cpu(4)));
 /* 0018e3b8: sw zero,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
 /* 0018e3bc: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
 /* 0018e3c0: sw v0,0x38(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(2));
 /* 0018e3c4: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
 /* 0018e3c8: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0018e3cc: sw v1,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
 /* 0018e3d0: move v0,s0 */ set(2,cpu(16));
 /* 0018e3d4: lbu a0,0x0(s1) */ set(4,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
 /* 0018e3d8: sb a0,0x10(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000010)),(uint8_t)cpu(4));
 /* 0018e3dc: lw v1,0x4(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000004)));
 /* 0018e3e0: sw v1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
 /* 0018e3e4: lw a0,0x8(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000008)));
 /* 0018e3e8: sw a0,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(4));
 /* 0018e3ec: lw v1,0xc(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000000c)));
 /* 0018e3f0: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
 /* 0018e3f4: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0018e3f8: sw a0,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(4));
 /* 0018e3fc: lw v1,0x14(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000014)));
 /* 0018e400: sw v1,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(3));
 /* 0018e404: lw a0,0x24(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000024)));
 /* 0018e408: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018e40c: sw a0,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(4));
 /* 0018e410: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018e414: jr ra */ {uint64_t target=cpu(31);/* delay 0018e418 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0018E420(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018e420);
 uint64_t incomingRa=cpu(31);
 /* 0018e420: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018e424: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018e428: jal 0x00176270 */ set(31,sx(UINT32_C(0x0018e430)));/* delay 0018e42c */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0018e430: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018e434: move a0,v0 */ set(4,cpu(2));
 /* 0018e438: j 0x0018e390 */ /* delay 0018e43c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0018E390(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0018E440(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018e440);
 uint64_t incomingRa=cpu(31);
 /* 0018e440: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
 /* 0018e444: move v1,a0 */ set(3,cpu(4));
 /* 0018e448: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
 /* 0018e44c: lbu v0,0x10(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000010))));
 /* 0018e450: lw a1,0x20(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000020)));
 /* 0018e454: lw a2,0x24(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000024)));
 /* 0018e458: lw a3,0x28(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000028)));
 /* 0018e45c: lw t0,0x2c(v1) */ lw(8,ea(3,(int32_t)UINT32_C(0x0000002c)));
 /* 0018e460: lw t1,0x30(v1) */ lw(9,ea(3,(int32_t)UINT32_C(0x00000030)));
 /* 0018e464: sb v0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
 /* 0018e468: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
 /* 0018e46c: sw a2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
 /* 0018e470: sw a3,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
 /* 0018e474: sw t0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(8));
 /* 0018e478: sw t1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(9));
 /* 0018e47c: lw v0,0x38(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000038)));
 /* 0018e480: ldl v1,0x7(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000007)),1);
 /* 0018e484: ldr v1,0x0(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000000)),0);
 /* 0018e488: ldl a1,0xf(v0) */ loadPartial(5,ea(2,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0018e48c: ldr a1,0x8(v0) */ loadPartial(5,ea(2,(int32_t)UINT32_C(0x00000008)),0);
 /* 0018e490: ldl a2,0x17(v0) */ loadPartial(6,ea(2,(int32_t)UINT32_C(0x00000017)),1);
 /* 0018e494: ldr a2,0x10(v0) */ loadPartial(6,ea(2,(int32_t)UINT32_C(0x00000010)),0);
 /* 0018e498: ldl a3,0x1f(v0) */ loadPartial(7,ea(2,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0018e49c: ldr a3,0x18(v0) */ loadPartial(7,ea(2,(int32_t)UINT32_C(0x00000018)),0);
 /* 0018e4a0: sdl v1,0x1f(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000001f)),3,1);
 /* 0018e4a4: sdr v1,0x18(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000018)),3,0);
 /* 0018e4a8: sdl a1,0x27(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000027)),5,1);
 /* 0018e4ac: sdr a1,0x20(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000020)),5,0);
 /* 0018e4b0: sdl a2,0x2f(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000002f)),6,1);
 /* 0018e4b4: sdr a2,0x28(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000028)),6,0);
 /* 0018e4b8: sdl a3,0x37(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000037)),7,1);
 /* 0018e4bc: sdr a3,0x30(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000030)),7,0);
 /* 0018e4c0: lw v1,0x20(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000020)));
 /* 0018e4c4: sw v1,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(3));
 /* 0018e4c8: jal 0x0018e390 */ set(31,sx(UINT32_C(0x0018e4d0)));/* delay 0018e4cc */ set(4,cpu(29));set(2,ps2BattleAction_0018E390(cpu(4)));
 /* 0018e4d0: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
 /* 0018e4d4: jr ra */ {uint64_t target=cpu(31);/* delay 0018e4d8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0018E6D8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018e6d8);
 uint64_t incomingRa=cpu(31);
 /* 0018e6d8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 0018e6dc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018e6e0: move s1,a0 */ set(17,cpu(4));
 /* 0018e6e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018e6e8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0018e6ec: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x0018e6f4)));/* delay 0018e6f0 */ set(4,sx(UINT32_C(0x0000003c)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 0018e6f4: addiu a0,s1,0x18 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));
 /* 0018e6f8: jal 0x001a1ff8 */ set(31,sx(UINT32_C(0x0018e700)));/* delay 0018e6fc */ set(16,cpu(2));set(2,ps2BattleActionCopyRecord_001A1FF8(cpu(4)));
 /* 0018e700: sw zero,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
 /* 0018e704: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
 /* 0018e708: sw v0,0x38(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(2));
 /* 0018e70c: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
 /* 0018e710: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 0018e714: sw v1,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
 /* 0018e718: move v0,s0 */ set(2,cpu(16));
 /* 0018e71c: lbu a0,0x0(s1) */ set(4,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
 /* 0018e720: sb a0,0x10(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000010)),(uint8_t)cpu(4));
 /* 0018e724: lw v1,0x4(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000004)));
 /* 0018e728: sw v1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
 /* 0018e72c: lw a0,0x8(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000008)));
 /* 0018e730: sw a0,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(4));
 /* 0018e734: lw v1,0xc(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000000c)));
 /* 0018e738: sw v1,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
 /* 0018e73c: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 0018e740: sw a0,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(4));
 /* 0018e744: lw v1,0x14(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000014)));
 /* 0018e748: sw v1,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(3));
 /* 0018e74c: lw a0,0x1c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000001c)));
 /* 0018e750: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018e754: sw a0,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(4));
 /* 0018e758: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018e75c: jr ra */ {uint64_t target=cpu(31);/* delay 0018e760 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0018E768(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018e768);
 uint64_t incomingRa=cpu(31);
 /* 0018e768: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018e76c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018e770: jal 0x00176270 */ set(31,sx(UINT32_C(0x0018e778)));/* delay 0018e774 */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0018e778: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018e77c: move a0,v0 */ set(4,cpu(2));
 /* 0018e780: j 0x0018e6d8 */ /* delay 0018e784 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0018E6D8(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0018E788(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018e788);
 uint64_t incomingRa=cpu(31);
 /* 0018e788: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
 /* 0018e78c: move v1,a0 */ set(3,cpu(4));
 /* 0018e790: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
 /* 0018e794: lbu v0,0x10(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000010))));
 /* 0018e798: lw a1,0x20(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000020)));
 /* 0018e79c: lw a2,0x24(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000024)));
 /* 0018e7a0: lw a3,0x28(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000028)));
 /* 0018e7a4: lw t0,0x2c(v1) */ lw(8,ea(3,(int32_t)UINT32_C(0x0000002c)));
 /* 0018e7a8: lw t1,0x30(v1) */ lw(9,ea(3,(int32_t)UINT32_C(0x00000030)));
 /* 0018e7ac: sb v0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
 /* 0018e7b0: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
 /* 0018e7b4: sw a2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
 /* 0018e7b8: sw a3,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
 /* 0018e7bc: sw t0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(8));
 /* 0018e7c0: sw t1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(9));
 /* 0018e7c4: lw v0,0x38(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000038)));
 /* 0018e7c8: ldl v1,0x7(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000007)),1);
 /* 0018e7cc: ldr v1,0x0(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000000)),0);
 /* 0018e7d0: ldl a1,0xf(v0) */ loadPartial(5,ea(2,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0018e7d4: ldr a1,0x8(v0) */ loadPartial(5,ea(2,(int32_t)UINT32_C(0x00000008)),0);
 /* 0018e7d8: ldl a2,0x17(v0) */ loadPartial(6,ea(2,(int32_t)UINT32_C(0x00000017)),1);
 /* 0018e7dc: ldr a2,0x10(v0) */ loadPartial(6,ea(2,(int32_t)UINT32_C(0x00000010)),0);
 /* 0018e7e0: ldl a3,0x1f(v0) */ loadPartial(7,ea(2,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0018e7e4: ldr a3,0x18(v0) */ loadPartial(7,ea(2,(int32_t)UINT32_C(0x00000018)),0);
 /* 0018e7e8: sdl v1,0x1f(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000001f)),3,1);
 /* 0018e7ec: sdr v1,0x18(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000018)),3,0);
 /* 0018e7f0: sdl a1,0x27(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000027)),5,1);
 /* 0018e7f4: sdr a1,0x20(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000020)),5,0);
 /* 0018e7f8: sdl a2,0x2f(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000002f)),6,1);
 /* 0018e7fc: sdr a2,0x28(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000028)),6,0);
 /* 0018e800: sdl a3,0x37(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000037)),7,1);
 /* 0018e804: sdr a3,0x30(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000030)),7,0);
 /* 0018e808: ldl v1,0x27(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000027)),1);
 /* 0018e80c: ldr v1,0x20(v0) */ loadPartial(3,ea(2,(int32_t)UINT32_C(0x00000020)),0);
 /* 0018e810: lw a1,0x28(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000028)));
 /* 0018e814: sdl v1,0x3f(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000003f)),3,1);
 /* 0018e818: sdr v1,0x38(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000038)),3,0);
 /* 0018e81c: sw a1,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(5));
 /* 0018e820: jal 0x0018e6d8 */ set(31,sx(UINT32_C(0x0018e828)));/* delay 0018e824 */ set(4,cpu(29));set(2,ps2BattleAction_0018E6D8(cpu(4)));
 /* 0018e828: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
 /* 0018e82c: jr ra */ {uint64_t target=cpu(31);/* delay 0018e830 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0018EA30(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018ea30);
 uint64_t incomingRa=cpu(31);
 /* 0018ea30: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018ea34: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018ea38: move s0,a0 */ set(16,cpu(4));
 /* 0018ea3c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018ea40: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x0018ea48)));/* delay 0018ea44 */ set(4,sx(UINT32_C(0x00000030)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 0018ea48: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
 /* 0018ea4c: move a0,v0 */ set(4,cpu(2));
 /* 0018ea50: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
 /* 0018ea54: ldl a1,0x7(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0018ea58: ldr a1,0x0(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0018ea5c: ldl a2,0xf(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0018ea60: ldr a2,0x8(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0018ea64: ldl a3,0x17(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 0018ea68: ldr a3,0x10(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 0018ea6c: ldl t0,0x1f(s0) */ loadPartial(8,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0018ea70: ldr t0,0x18(s0) */ loadPartial(8,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 0018ea74: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
 /* 0018ea78: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
 /* 0018ea7c: sdl a2,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),6,1);
 /* 0018ea80: sdr a2,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),6,0);
 /* 0018ea84: sdl a3,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),7,1);
 /* 0018ea88: sdr a3,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),7,0);
 /* 0018ea8c: sdl t0,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),8,1);
 /* 0018ea90: sdr t0,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),8,0);
 /* 0018ea94: lw a1,0x20(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000020)));
 /* 0018ea98: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018ea9c: sw a1,0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(5));
 /* 0018eaa0: sw v1,0x24(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(3));
 /* 0018eaa4: sw zero,0x2c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(0));
 /* 0018eaa8: lw v1,0xc(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));
 /* 0018eaac: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018eab0: sw v1,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
 /* 0018eab4: jr ra */ {uint64_t target=cpu(31);/* delay 0018eab8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0018EAC0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018eac0);
 uint64_t incomingRa=cpu(31);
 /* 0018eac0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018eac4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018eac8: jal 0x00176270 */ set(31,sx(UINT32_C(0x0018ead0)));/* delay 0018eacc */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0018ead0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018ead4: move a0,v0 */ set(4,cpu(2));
 /* 0018ead8: j 0x0018ea30 */ /* delay 0018eadc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0018EA30(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0018EAE0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018eae0);
 uint64_t incomingRa=cpu(31);
 /* 0018eae0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018eae4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018eae8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018eaec: j 0x0018ea30 */ /* delay 0018eaf0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0018EA30(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0018EC28(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018ec28);
 uint64_t incomingRa=cpu(31);
 /* 0018ec28: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018ec2c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018ec30: move s0,a0 */ set(16,cpu(4));
 /* 0018ec34: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018ec38: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x0018ec40)));/* delay 0018ec3c */ set(4,sx(UINT32_C(0x00000040)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 0018ec40: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
 /* 0018ec44: move a0,v0 */ set(4,cpu(2));
 /* 0018ec48: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
 /* 0018ec4c: ldl a1,0x7(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000007)),1);
 /* 0018ec50: ldr a1,0x0(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000000)),0);
 /* 0018ec54: ldl a2,0xf(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x0000000f)),1);
 /* 0018ec58: ldr a2,0x8(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000008)),0);
 /* 0018ec5c: ldl a3,0x17(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000017)),1);
 /* 0018ec60: ldr a3,0x10(s0) */ loadPartial(7,ea(16,(int32_t)UINT32_C(0x00000010)),0);
 /* 0018ec64: ldl t0,0x1f(s0) */ loadPartial(8,ea(16,(int32_t)UINT32_C(0x0000001f)),1);
 /* 0018ec68: ldr t0,0x18(s0) */ loadPartial(8,ea(16,(int32_t)UINT32_C(0x00000018)),0);
 /* 0018ec6c: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
 /* 0018ec70: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
 /* 0018ec74: sdl a2,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),6,1);
 /* 0018ec78: sdr a2,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),6,0);
 /* 0018ec7c: sdl a3,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),7,1);
 /* 0018ec80: sdr a3,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),7,0);
 /* 0018ec84: sdl t0,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),8,1);
 /* 0018ec88: sdr t0,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),8,0);
 /* 0018ec8c: ldl a1,0x27(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000027)),1);
 /* 0018ec90: ldr a1,0x20(s0) */ loadPartial(5,ea(16,(int32_t)UINT32_C(0x00000020)),0);
 /* 0018ec94: ldl a2,0x2f(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x0000002f)),1);
 /* 0018ec98: ldr a2,0x28(s0) */ loadPartial(6,ea(16,(int32_t)UINT32_C(0x00000028)),0);
 /* 0018ec9c: lw a3,0x30(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000030)));
 /* 0018eca0: sdl a1,0x27(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000027)),5,1);
 /* 0018eca4: sdr a1,0x20(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000020)),5,0);
 /* 0018eca8: sdl a2,0x2f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000002f)),6,1);
 /* 0018ecac: sdr a2,0x28(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000028)),6,0);
 /* 0018ecb0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 0018ecb4: sw a3,0x30(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(7));
 /* 0018ecb8: sw v1,0x34(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(3));
 /* 0018ecbc: sw zero,0x3c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));
 /* 0018ecc0: lw v1,0xc(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));
 /* 0018ecc4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018ecc8: sw v1,0x38(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(3));
 /* 0018eccc: jr ra */ {uint64_t target=cpu(31);/* delay 0018ecd0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_0018ECD8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018ecd8);
 uint64_t incomingRa=cpu(31);
 /* 0018ecd8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018ecdc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018ece0: jal 0x00176270 */ set(31,sx(UINT32_C(0x0018ece8)));/* delay 0018ece4 */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 0018ece8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018ecec: move a0,v0 */ set(4,cpu(2));
 /* 0018ecf0: j 0x0018ec28 */ /* delay 0018ecf4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0018EC28(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_0018ECF8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x0018ecf8);
 uint64_t incomingRa=cpu(31);
 /* 0018ecf8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 0018ecfc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018ed00: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0018ed04: j 0x0018ec28 */ /* delay 0018ed08 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_0018EC28(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_001930E0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001930e0);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 001930e0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 001930e4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001930e8: move s1,a0 */ set(17,cpu(4));
 /* 001930ec: li a0,0x34 */ set(4,sx(UINT32_C(0x00000034)));
 /* 001930f0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001930f4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001930f8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 001930fc: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x00193104)));/* delay 00193100 */ set(18,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 00193104: lwc1 f0,0xc(s1) */ f[0]=word(ea(17,(int32_t)UINT32_C(0x0000000c)));
 /* 00193108: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
 /* 0019310c: move a0,s2 */ set(4,cpu(18));
 /* 00193110: move s0,v0 */ set(16,cpu(2));
 /* 00193114: swc1 f0,0x34(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000034)),f[0]);
 /* 00193118: jal 0x001762f8 */ set(31,sx(UINT32_C(0x00193120)));/* delay 0019311c */ sw(ea(17,(int32_t)UINT32_C(0x00000030)),f[0]);set(2,ps2BattleActionPcpType0Create_001762F8(cpu(4)));
 /* 00193120: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
 /* 00193124: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
 /* 00193128: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
 /* 0019312c: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
 /* 00193130: sw v1,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
 /* 00193134: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
 /* 00193138: swc1 f0,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),f[0]);
 /* 0019313c: lw v1,0x4(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000004)));
 /* 00193140: lwc1 f0,0x0(s2) */ f[0]=word(ea(18,(int32_t)UINT32_C(0x00000000)));
 /* 00193144: sw v1,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
 /* 00193148: swc1 f0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),f[0]);
 /* 0019314c: lw v1,0x8(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000008)));
 /* 00193150: lwc1 f0,0x18(s1) */ f[0]=word(ea(17,(int32_t)UINT32_C(0x00000018)));
 /* 00193154: sw v1,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
 /* 00193158: swc1 f0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),f[0]);
 /* 0019315c: lw v1,0xc(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000000c)));
 /* 00193160: lwc1 f0,0x1c(s1) */ f[0]=word(ea(17,(int32_t)UINT32_C(0x0000001c)));
 /* 00193164: sw v1,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(3));
 /* 00193168: sw v0,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(2));
 /* 0019316c: move v0,s0 */ set(2,cpu(16));
 /* 00193170: lw v1,0x10(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000010)));
 /* 00193174: swc1 f0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),f[0]);
 /* 00193178: sw v1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
 /* 0019317c: sw a0,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(4));
 /* 00193180: sw zero,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
 /* 00193184: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 00193188: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 0019318c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 00193190: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
 /* 00193194: jr ra */ {uint64_t target=cpu(31);/* delay 00193198 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_001931A0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001931a0);
 uint64_t incomingRa=cpu(31);
 /* 001931a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
 /* 001931a4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001931a8: jal 0x00176270 */ set(31,sx(UINT32_C(0x001931b0)));/* delay 001931ac */ set(5,cpu(0));set(2,ps2PcpDescriptorPartData(cpu(4),cpu(5)));
 /* 001931b0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001931b4: move a0,v0 */ set(4,cpu(2));
 /* 001931b8: j 0x001930e0 */ /* delay 001931bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));set(2,ps2BattleAction_001930E0(cpu(4)));checkReturn(cpu(31),incomingRa);return cpu(2);
}

uint64_t ps2BattleAction_001931C0(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001931c0);
 uint64_t incomingRa=cpu(31);
 /* 001931c0: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
 /* 001931c4: sd s0,0x60(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000060)));
 /* 001931c8: move s0,a0 */ set(16,cpu(4));
 /* 001931cc: sd ra,0x68(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000068)));
 /* 001931d0: jal 0x00176558 */ set(31,sx(UINT32_C(0x001931d8)));/* delay 001931d4 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000030)));set(2,ps2BattleAction_00176558(cpu(4)));
 /* 001931d8: lw a2,0x10(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x00000010)));
 /* 001931dc: move t0,v0 */ set(8,cpu(2));
 /* 001931e0: addiu t1,sp,0x14 */ set(9,sx((uint32_t)cpu(29)+UINT32_C(0x00000014)));
 /* 001931e4: lw a3,0x20(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000020)));
 /* 001931e8: or v0,t0,t1 */ set(2,cpu(8)|cpu(9));
 /* 001931ec: lw a1,0x14(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000014)));
 /* 001931f0: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
 /* 001931f4: lw v1,0x18(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000018)));
 /* 001931f8: lw a0,0x1c(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x0000001c)));
 /* 001931fc: sw a2,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
 /* 00193200: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
 /* 00193204: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
 /* 00193208: sw a0,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
 /* 0019320c: beq v0,zero,0x00193278 */ {int take=(cpu(2)==cpu(0));/* delay 00193210 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(7));if(take){goto L_00193278;}}
 /* 00193214: addiu v0,t0,0x40 */ set(2,sx((uint32_t)cpu(8)+UINT32_C(0x00000040)));
L_00193218:;
 /* 00193218: ldl v1,0x7(t0) */ loadPartial(3,ea(8,(int32_t)UINT32_C(0x00000007)),1);
 /* 0019321c: ldr v1,0x0(t0) */ loadPartial(3,ea(8,(int32_t)UINT32_C(0x00000000)),0);
 /* 00193220: ldl a0,0xf(t0) */ loadPartial(4,ea(8,(int32_t)UINT32_C(0x0000000f)),1);
 /* 00193224: ldr a0,0x8(t0) */ loadPartial(4,ea(8,(int32_t)UINT32_C(0x00000008)),0);
 /* 00193228: ldl a1,0x17(t0) */ loadPartial(5,ea(8,(int32_t)UINT32_C(0x00000017)),1);
 /* 0019322c: ldr a1,0x10(t0) */ loadPartial(5,ea(8,(int32_t)UINT32_C(0x00000010)),0);
 /* 00193230: ldl a2,0x1f(t0) */ loadPartial(6,ea(8,(int32_t)UINT32_C(0x0000001f)),1);
 /* 00193234: ldr a2,0x18(t0) */ loadPartial(6,ea(8,(int32_t)UINT32_C(0x00000018)),0);
 /* 00193238: sdl v1,0x7(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x00000007)),3,1);
 /* 0019323c: sdr v1,0x0(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x00000000)),3,0);
 /* 00193240: sdl a0,0xf(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x0000000f)),4,1);
 /* 00193244: sdr a0,0x8(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x00000008)),4,0);
 /* 00193248: sdl a1,0x17(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x00000017)),5,1);
 /* 0019324c: sdr a1,0x10(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x00000010)),5,0);
 /* 00193250: sdl a2,0x1f(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x0000001f)),6,1);
 /* 00193254: sdr a2,0x18(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x00000018)),6,0);
 /* 00193258: addiu t0,t0,0x20 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000020)));
 /* 0019325c: nop  */ 
 /* 00193260: nop  */ 
 /* 00193264: bne t0,v0,0x00193218 */ {int take=(cpu(8)!=cpu(2));/* delay 00193268 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000020)));if(take){goto L_00193218;}}
 /* 0019326c: b 0x001932b0 */ /* delay 00193270 */ goto L_001932b0;
L_00193278:;
 /* 00193278: addiu v0,t0,0x40 */ set(2,sx((uint32_t)cpu(8)+UINT32_C(0x00000040)));
L_0019327c:;
 /* 0019327c: ld v1,0x0(t0) */ restore(3,ea(8,(int32_t)UINT32_C(0x00000000)));
 /* 00193280: ld a0,0x8(t0) */ restore(4,ea(8,(int32_t)UINT32_C(0x00000008)));
 /* 00193284: ld a1,0x10(t0) */ restore(5,ea(8,(int32_t)UINT32_C(0x00000010)));
 /* 00193288: ld a2,0x18(t0) */ restore(6,ea(8,(int32_t)UINT32_C(0x00000018)));
 /* 0019328c: sd v1,0x0(t1) */ save(3,ea(9,(int32_t)UINT32_C(0x00000000)));
 /* 00193290: sd a0,0x8(t1) */ save(4,ea(9,(int32_t)UINT32_C(0x00000008)));
 /* 00193294: sd a1,0x10(t1) */ save(5,ea(9,(int32_t)UINT32_C(0x00000010)));
 /* 00193298: sd a2,0x18(t1) */ save(6,ea(9,(int32_t)UINT32_C(0x00000018)));
 /* 0019329c: addiu t0,t0,0x20 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000020)));
 /* 001932a0: nop  */ 
 /* 001932a4: nop  */ 
 /* 001932a8: bne t0,v0,0x0019327c */ {int take=(cpu(8)!=cpu(2));/* delay 001932ac */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000020)));if(take){goto L_0019327c;}}
L_001932b0:;
 /* 001932b0: ldl v0,0x7(t0) */ loadPartial(2,ea(8,(int32_t)UINT32_C(0x00000007)),1);
 /* 001932b4: ldr v0,0x0(t0) */ loadPartial(2,ea(8,(int32_t)UINT32_C(0x00000000)),0);
 /* 001932b8: lw v1,0x8(t0) */ lw(3,ea(8,(int32_t)UINT32_C(0x00000008)));
 /* 001932bc: sdl v0,0x7(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x00000007)),2,1);
 /* 001932c0: sdr v0,0x0(t1) */ storePartial(ea(9,(int32_t)UINT32_C(0x00000000)),2,0);
 /* 001932c4: move a0,sp */ set(4,cpu(29));
 /* 001932c8: jal 0x001930e0 */ set(31,sx(UINT32_C(0x001932d0)));/* delay 001932cc */ sw(ea(9,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));set(2,ps2BattleAction_001930E0(cpu(4)));
 /* 001932d0: ld s0,0x60(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000060)));
 /* 001932d4: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
 /* 001932d8: jr ra */ {uint64_t target=cpu(31);/* delay 001932dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleAction_001A2E28(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001a2e28);
 uint64_t incomingRa=cpu(31);
 /* 001a2e28: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 001a2e2c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001a2e30: move s1,a0 */ set(17,cpu(4));
 /* 001a2e34: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001a2e38: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001a2e3c: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x001a2e44)));/* delay 001a2e40 */ set(4,sx(UINT32_C(0x00000028)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 001a2e44: move a0,zero */ set(4,cpu(0));
 /* 001a2e48: jal 0x0015d000 */ set(31,sx(UINT32_C(0x001a2e50)));/* delay 001a2e4c */ set(16,cpu(2));set(2,ps2BillboardTextureBase(cpu(4)));
 /* 001a2e50: sw v0,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
 /* 001a2e54: move v0,s0 */ set(2,cpu(16));
 /* 001a2e58: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001a2e5c: ldl v1,0x7(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000007)),1);
 /* 001a2e60: ldr v1,0x0(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000000)),0);
 /* 001a2e64: ldl a0,0xf(s1) */ loadPartial(4,ea(17,(int32_t)UINT32_C(0x0000000f)),1);
 /* 001a2e68: ldr a0,0x8(s1) */ loadPartial(4,ea(17,(int32_t)UINT32_C(0x00000008)),0);
 /* 001a2e6c: ldl a1,0x17(s1) */ loadPartial(5,ea(17,(int32_t)UINT32_C(0x00000017)),1);
 /* 001a2e70: ldr a1,0x10(s1) */ loadPartial(5,ea(17,(int32_t)UINT32_C(0x00000010)),0);
 /* 001a2e74: ldl a2,0x1f(s1) */ loadPartial(6,ea(17,(int32_t)UINT32_C(0x0000001f)),1);
 /* 001a2e78: ldr a2,0x18(s1) */ loadPartial(6,ea(17,(int32_t)UINT32_C(0x00000018)),0);
 /* 001a2e7c: sdl v1,0x7(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000007)),3,1);
 /* 001a2e80: sdr v1,0x0(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000000)),3,0);
 /* 001a2e84: sdl a0,0xf(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000000f)),4,1);
 /* 001a2e88: sdr a0,0x8(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000008)),4,0);
 /* 001a2e8c: sdl a1,0x17(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000017)),5,1);
 /* 001a2e90: sdr a1,0x10(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000010)),5,0);
 /* 001a2e94: sdl a2,0x1f(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000001f)),6,1);
 /* 001a2e98: sdr a2,0x18(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000018)),6,0);
 /* 001a2e9c: lw v1,0x20(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000020)));
 /* 001a2ea0: sw v1,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
 /* 001a2ea4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001a2ea8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001a2eac: jr ra */ {uint64_t target=cpu(31);/* delay 001a2eb0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

uint64_t ps2BattleActionCopyRecord_001A1FF8(uint64_t a0){
set(4,a0);nocturneEffectAxisNoteEntry(0x001a1ff8);
 uint64_t incomingRa=cpu(31);
 /* 001a1ff8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
 /* 001a1ffc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001a2000: move s1,a0 */ set(17,cpu(4));
 /* 001a2004: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001a2008: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001a200c: jal 0x002a8af8 */ set(31,sx(UINT32_C(0x001a2014)));/* delay 001a2010 */ set(4,sx(UINT32_C(0x00000030)));set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
 /* 001a2014: li a0,0x2 */ set(4,sx(UINT32_C(0x00000002)));
 /* 001a2018: jal 0x0015d000 */ set(31,sx(UINT32_C(0x001a2020)));/* delay 001a201c */ set(16,cpu(2));set(2,ps2BillboardTextureBase(cpu(4)));
 /* 001a2020: sw v0,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(2));
 /* 001a2024: move v0,s0 */ set(2,cpu(16));
 /* 001a2028: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
 /* 001a202c: ldl v1,0x7(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000007)),1);
 /* 001a2030: ldr v1,0x0(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000000)),0);
 /* 001a2034: ldl a0,0xf(s1) */ loadPartial(4,ea(17,(int32_t)UINT32_C(0x0000000f)),1);
 /* 001a2038: ldr a0,0x8(s1) */ loadPartial(4,ea(17,(int32_t)UINT32_C(0x00000008)),0);
 /* 001a203c: ldl a1,0x17(s1) */ loadPartial(5,ea(17,(int32_t)UINT32_C(0x00000017)),1);
 /* 001a2040: ldr a1,0x10(s1) */ loadPartial(5,ea(17,(int32_t)UINT32_C(0x00000010)),0);
 /* 001a2044: ldl a2,0x1f(s1) */ loadPartial(6,ea(17,(int32_t)UINT32_C(0x0000001f)),1);
 /* 001a2048: ldr a2,0x18(s1) */ loadPartial(6,ea(17,(int32_t)UINT32_C(0x00000018)),0);
 /* 001a204c: sdl v1,0x7(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000007)),3,1);
 /* 001a2050: sdr v1,0x0(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000000)),3,0);
 /* 001a2054: sdl a0,0xf(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000000f)),4,1);
 /* 001a2058: sdr a0,0x8(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000008)),4,0);
 /* 001a205c: sdl a1,0x17(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000017)),5,1);
 /* 001a2060: sdr a1,0x10(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000010)),5,0);
 /* 001a2064: sdl a2,0x1f(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x0000001f)),6,1);
 /* 001a2068: sdr a2,0x18(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000018)),6,0);
 /* 001a206c: ldl v1,0x27(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000027)),1);
 /* 001a2070: ldr v1,0x20(s1) */ loadPartial(3,ea(17,(int32_t)UINT32_C(0x00000020)),0);
 /* 001a2074: lw a0,0x28(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000028)));
 /* 001a2078: sdl v1,0x27(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000027)),3,1);
 /* 001a207c: sdr v1,0x20(s0) */ storePartial(ea(16,(int32_t)UINT32_C(0x00000020)),3,0);
 /* 001a2080: sw a0,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(4));
 /* 001a2084: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
 /* 001a2088: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
 /* 001a208c: jr ra */ {uint64_t target=cpu(31);/* delay 001a2090 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incomingRa);return cpu(2);}
}

void ps2BattleActionMaterialSetConstant_002B2ED8(uint64_t a0, float f12){
set(4,a0);nocturneEffectHostFpr()[12]=bits(f12);nocturneEffectAxisNoteEntry(0x002b2ed8);
 uint64_t incomingRa=cpu(31);
 uint32_t *f=nocturneEffectHostFpr();
 /* 002b2ed8: lbu v0,0x6(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000006))));
 /* 002b2edc: swc1 f12,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),f[12]);
 /* 002b2ee0: ori v0,v0,0x3 */ set(2,cpu(2)|UINT32_C(0x00000003));
 /* 002b2ee4: jr ra */ {uint64_t target=cpu(31);/* delay 002b2ee8 */ sb(ea(4,(int32_t)UINT32_C(0x00000006)),(uint8_t)cpu(2));checkReturn(target,incomingRa);return;}
}
