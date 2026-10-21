/* Complete fixed native control-flow translations of twenty SLUS_209.11
 * battle-action consumers. Each comment identifies its actual instruction.
 * Static labels are ordinary C flow, not an opcode interpreter. Guest stack
 * saves/loads and partial-word transfers execute at their original positions.
 * Legacy registered semantic callees retain their own volatile/frame limits;
 * this source does not fabricate those states or supply game return values.
 * Local LO preserves the actual word arithmetic consumed inside these bodies;
 * complete architectural HI/LO transport across semantic dependencies is outside
 * this layer. Dynamic callbacks are the real original hit table functions. */
#include "battle_action_consumer.h"
#include "battle_action_copy_frames.h"
#include "battle_action_hit_frames.h"
#include "battle_action_activation.h"
#include "../analysis/drafts/model-context-anchor/effect_model_child_dependency_frames.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "compiler_numeric.h"
#include "../analysis/drafts/model-context-anchor/effect_host_bindings.h"
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#pragma warning(disable:4102) /* Fixed original PC labels include fallthroughs. */
#endif
#include "battle_action_finish.h"
#include "battle_action_process.h"
#include "battle_action_status.h"
#include "battle_affinity.h"
#include "battle_check1_packets.h"
#include "battle_effect_copy.h"
#include "battle_effects.h"
#include "battle_kouka_packets.h"
#include "battle_support_access.h"
#include "battle_work_access.h"
#include "combat_calculation.h"
#include "libc_printf.h"
#include "material_fiveword_pool.h"
#include "model_pac_loading.h"
#include "nocturne.h"
#include "pcp_construction.h"

static uint64_t cpu(unsigned r) { uint32_t q[4]; if(!r)return 0; nocturneEffectHostCpuRead(r,q); return (uint64_t)q[0]|((uint64_t)q[1]<<32); }
static void set(unsigned r,uint64_t v) { uint32_t q[4]; if(!r)return; nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q); }
static uint32_t *fpr(void) { return nocturneEffectHostFpr(); }
static uint8_t *at(uint32_t a) { return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a); }
static uint32_t ea(uint64_t base,uint32_t delta) { return (uint32_t)base+delta; }
static uint8_t r8(uint32_t a) { return *at(a); }
static uint16_t r16(uint32_t a) { uint16_t v;memcpy(&v,at(a),2);return v; }
static uint32_t r32(uint32_t a) { uint32_t v;memcpy(&v,at(a),4);return v; }
static uint64_t r64(uint32_t a) { uint64_t v;memcpy(&v,at(a),8);return v; }
static void w8(uint32_t a,uint8_t v) { *at(a)=v; }
static void w16(uint32_t a,uint16_t v) { memcpy(at(a),&v,2); }
static void w32(uint32_t a,uint32_t v) { memcpy(at(a),&v,4); }
static void w64(uint32_t a,uint64_t v) { memcpy(at(a),&v,8); }
static int32_t i8(uint8_t v) { return v<128?(int32_t)v:(int32_t)v-256; }
static int32_t i16(uint16_t v) { return v<32768?(int32_t)v:(int32_t)v-65536; }
static int32_t i32(uint32_t v) { return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v); }
static uint64_t sx(uint32_t v) { return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v; }
static int lt(uint64_t a,uint64_t b) { return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000)); }
static uint32_t asr(uint32_t v,unsigned n) { return n?((v>>n)|((v&0x80000000u)?UINT32_MAX<<(32-n):0)):v; }
static uint32_t divs(uint32_t a,uint32_t b) { int64_t n=i32(a),d=i32(b);return d?(uint32_t)(n/d):(n<0?1u:UINT32_MAX); }
static uint32_t divu(uint32_t a,uint32_t b) { return b?a/b:UINT32_MAX; }
static uint32_t fbits(float v) { uint32_t b;memcpy(&b,&v,4);return b; }
static float fvalue(uint32_t b) { float v;memcpy(&v,&b,4);return v; }
static uint64_t ldl(uint64_t old,uint32_t a) { unsigned s=(7-(a&7))*8;uint64_t m=UINT64_MAX<<s;return (old&~m)|(r64(a&~7u)<<s); }
static uint64_t ldr(uint64_t old,uint32_t a) { unsigned s=(a&7)*8;uint64_t m=UINT64_MAX>>s;return (old&~m)|(r64(a&~7u)>>s); }
static void sdl(uint32_t a,uint64_t v) { unsigned s=(7-(a&7))*8;uint64_t m=UINT64_MAX>>s;uint32_t b=a&~7u;w64(b,(r64(b)&~m)|(v>>s)); }
static void sdr(uint32_t a,uint64_t v) { unsigned s=(a&7)*8;uint64_t m=UINT64_MAX<<s;uint32_t b=a&~7u;w64(b,(r64(b)&~m)|(v<<s)); }
static void ba_return_target(uint64_t incoming,uint64_t target) { if((uint32_t)incoming!=(uint32_t)target)abort(); }
static void ba_return(uint64_t incoming) { ba_return_target(incoming,cpu(31)); }
static void body_00175a88(void);
static void body_00176038(void);
static void part_copy_callback(uint64_t target);
static void body_00171a00(void);
static void body_00171cc8(void);
static void body_00172178(void);
static void body_00173cb0(void);
static void body_00173ef0(void);
static void body_0024f420(void);
static void body_0024f478(void);
static void body_0024f548(void);
static void body_0024f5b0(void);
static void body_0024f5c8(void);
static void body_0024ff60(void);
static void body_00251750(void);
static void body_002521c8(void);
static void body_002592b0(void);
static void body_00259300(void);
static void body_00262480(void);
static void body_002634c8(void);
static void body_00263918(void);
static void body_00263c00(void);
static void body_00264010(void);
static void callback(uint64_t target)
{
    switch((uint32_t)target) {
    case 0x00171a00u: body_00171a00(); return;
    case 0x00171cc8u: body_00171cc8(); return;
    case 0x00172178u: body_00172178(); return;
    case 0x00172618u: set(2,ps2BattleActionHitCreate20_00172618(cpu(4))); return;
    case 0x001727b0u: set(2,ps2BattleActionHitCreate24_001727B0(cpu(4))); return;
    case 0x00172da0u: set(2,ps2BattleActionHitCreate25_00172DA0(cpu(4))); return;
    case 0x00173668u: set(2,ps2BattleActionHitCreate26_00173668(cpu(4))); return;
    case 0x00173800u: set(2,ps2BattleActionHitCreate27_00173800(cpu(4))); return;
    case 0x00173990u: set(2,ps2BattleActionHitCreate28_00173990(cpu(4))); return;
    case 0x00173b20u: set(2,ps2BattleActionHitCreate29_00173B20(cpu(4))); return;
    case 0x00171c40u: set(2,ps2HitEffectLength14(cpu(4))); return;
    case 0x001720f0u: set(2,ps2HitEffectLength17(cpu(4))); return;
    case 0x00172590u: set(2,ps2HitEffectLength18(cpu(4))); return;
    case 0x00172718u: set(2,ps2HitEffectLength20(cpu(4))); return;
    case 0x00172d18u: set(2,ps2HitEffectLength24(cpu(4))); return;
    case 0x001735e0u: set(2,ps2HitEffectLength25(cpu(4))); return;
    case 0x00173768u: set(2,ps2HitEffectLength26(cpu(4))); return;
    case 0x001738f8u: set(2,ps2HitEffectLength27(cpu(4))); return;
    case 0x00173a88u: set(2,ps2HitEffectLength28(cpu(4))); return;
    case 0x00173c18u: set(2,ps2HitEffectLength29(cpu(4))); return;
    default: abort(); /* Foreign callback requires a real typed binding. */
    }
}

static void body_00171a00(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00171a00u);
L_00171a00: ;
    /* 00171A00: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
L_00171a04: ;
    /* 00171A04: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_00171a08: ;
    /* 00171A08: move s2,a0 */ set(18,cpu(4));
L_00171a0c: ;
    /* 00171A0C: li a0,0x14 */ set(4,UINT64_C(0x0000000000000014));
L_00171a10: ;
    /* 00171A10: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_00171a14: ;
    /* 00171A14: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00171a18: ;
    /* 00171A18: lui s1,0x32 */ set(17,sx(UINT32_C(0x00320000)));
L_00171a1c: ;
    /* 00171A1C: sd ra,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(31));
L_00171a20: ;
    /* 00171A20: addiu s1,s1,-0x43d8 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffbc28)));
L_00171a24: ;
    /* 00171A24: jal 0x002a8af8; native delay follows */
    set(31,UINT64_C(0x0000000000171a2c));
    /* 00171A28: swc1 f20,0x20(sp) */ w32(ea(cpu(29),UINT32_C(0x00000020)),fpr()[20]);
    set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
    goto L_00171a2c;
L_00171a2c: ;
    /* 00171A2C: move s0,v0 */ set(16,cpu(2));
L_00171a30: ;
    /* 00171A30: lw a0,0x10(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000010)))));
L_00171a34: ;
    /* 00171A34: sw s2,0x0(s0) */ w32(ea(cpu(16),UINT32_C(0x00000000)),(uint32_t)cpu(18));
L_00171a38: ;
    /* 00171A38: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x0000000000171a40));
    /* 00171A3C: sw zero,0x4(s0) */ w32(ea(cpu(16),UINT32_C(0x00000004)),(uint32_t)cpu(0));
    body_00175a88();
    goto L_00171a40;
L_00171a40: ;
    /* 00171A40: sw v0,0x8(s0) */ w32(ea(cpu(16),UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_00171a44: ;
    /* 00171A44: jal 0x00175988; native delay follows */
    set(31,UINT64_C(0x0000000000171a4c));
    /* 00171A48: move a0,v0 */ set(4,cpu(2));
    set(2,dds3EffectPartGetHandle(cpu(4)));
    goto L_00171a4c;
L_00171a4c: ;
    /* 00171A4C: move a1,zero */ set(5,cpu(0));
L_00171a50: ;
    /* 00171A50: move a2,zero */ set(6,cpu(0));
L_00171a54: ;
    /* 00171A54: jal 0x001dd558; native delay follows */
    set(31,UINT64_C(0x0000000000171a5c));
    /* 00171A58: move a0,v0 */ set(4,cpu(2));
    ps2ModelChangeMotionSingle(cpu(4),cpu(5),cpu(6));
    goto L_00171a5c;
L_00171a5c: ;
    /* 00171A5C: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x0000000000171a64));
    /* 00171A60: lw a0,0x2c(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x0000002c)))));
    body_00175a88();
    goto L_00171a64;
L_00171a64: ;
    /* 00171A64: sw v0,0xc(s0) */ w32(ea(cpu(16),UINT32_C(0x0000000c)),(uint32_t)cpu(2));
L_00171a68: ;
    /* 00171A68: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x0000000000171a70));
    /* 00171A6C: lw a0,0x48(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000048)))));
    body_00175a88();
    goto L_00171a70;
L_00171a70: ;
    /* 00171A70: lw a0,0x0(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000000)))));
L_00171a74: ;
    /* 00171A74: jal 0x0016fcf0; native delay follows */
    set(31,UINT64_C(0x0000000000171a7c));
    /* 00171A78: sw v0,0x10(s0) */ w32(ea(cpu(16),UINT32_C(0x00000010)),(uint32_t)cpu(2));
    fpr()[0]=fbits(effBTLSystem_GetScalePtr(cpu(4)));
    goto L_00171a7c;
L_00171a7c: ;
    /* 00171A7C: lw a0,0x8(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000008)))));
L_00171a80: ;
    /* 00171A80: mov.S f20,f0 */ fpr()[20]=fpr()[0];
L_00171a84: ;
    /* 00171A84: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x0000000000171a8c));
    /* 00171A88: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_00171a8c;
L_00171a8c: ;
    /* 00171A8C: lw a0,0xc(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x0000000c)))));
L_00171a90: ;
    /* 00171A90: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x0000000000171a98));
    /* 00171A94: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_00171a98;
L_00171a98: ;
    /* 00171A98: lw a0,0x10(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000010)))));
L_00171a9c: ;
    /* 00171A9C: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x0000000000171aa4));
    /* 00171AA0: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_00171aa4;
L_00171aa4: ;
    /* 00171AA4: move v0,s0 */ set(2,cpu(16));
L_00171aa8: ;
    /* 00171AA8: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_00171aac: ;
    /* 00171AAC: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_00171ab0: ;
    /* 00171AB0: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_00171ab4: ;
    /* 00171AB4: ld ra,0x18(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_00171ab8: ;
    /* 00171AB8: lwc1 f20,0x20(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x00000020)));
L_00171abc: ;
    /* 00171ABC: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00171AC0: addiu sp,sp,0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030))); ba_return_target(incoming_ra,target); return; }
}

static void body_00171cc8(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00171cc8u);
L_00171cc8: ;
    /* 00171CC8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
L_00171ccc: ;
    /* 00171CCC: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_00171cd0: ;
    /* 00171CD0: move s0,a0 */ set(16,cpu(4));
L_00171cd4: ;
    /* 00171CD4: li a0,0xf0 */ set(4,UINT64_C(0x00000000000000f0));
L_00171cd8: ;
    /* 00171CD8: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00171cdc: ;
    /* 00171CDC: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_00171ce0: ;
    /* 00171CE0: sd ra,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(31));
L_00171ce4: ;
    /* 00171CE4: jal 0x002a8af8; native delay follows */
    set(31,UINT64_C(0x0000000000171cec));
    /* 00171CE8: swc1 f20,0x20(sp) */ w32(ea(cpu(29),UINT32_C(0x00000020)),fpr()[20]);
    set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
    goto L_00171cec;
L_00171cec: ;
    /* 00171CEC: move s1,v0 */ set(17,cpu(2));
L_00171cf0: ;
    /* 00171CF0: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
L_00171cf4: ;
    /* 00171CF4: addiu s2,v0,-0x4380 */ set(18,sx((uint32_t)cpu(2)+UINT32_C(0xffffbc80)));
L_00171cf8: ;
    /* 00171CF8: sw s0,0xe0(s1) */ w32(ea(cpu(17),UINT32_C(0x000000e0)),(uint32_t)cpu(16));
L_00171cfc: ;
    /* 00171CFC: lw a0,0x10(s2) */ set(4,sx(r32(ea(cpu(18),UINT32_C(0x00000010)))));
L_00171d00: ;
    /* 00171D00: lui s0,0x3d */ set(16,sx(UINT32_C(0x003d0000)));
L_00171d04: ;
    /* 00171D04: sw zero,0xe4(s1) */ w32(ea(cpu(17),UINT32_C(0x000000e4)),(uint32_t)cpu(0));
L_00171d08: ;
    /* 00171D08: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x0000000000171d10));
    /* 00171D0C: addiu s0,s0,0x7998 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00007998)));
    body_00175a88();
    goto L_00171d10;
L_00171d10: ;
    /* 00171D10: sw v0,0xe8(s1) */ w32(ea(cpu(17),UINT32_C(0x000000e8)),(uint32_t)cpu(2));
L_00171d14: ;
    /* 00171D14: jal 0x00175988; native delay follows */
    set(31,UINT64_C(0x0000000000171d1c));
    /* 00171D18: move a0,v0 */ set(4,cpu(2));
    set(2,dds3EffectPartGetHandle(cpu(4)));
    goto L_00171d1c;
L_00171d1c: ;
    /* 00171D1C: move a1,zero */ set(5,cpu(0));
L_00171d20: ;
    /* 00171D20: move a0,v0 */ set(4,cpu(2));
L_00171d24: ;
    /* 00171D24: jal 0x001dd538; native delay follows */
    set(31,UINT64_C(0x0000000000171d2c));
    /* 00171D28: move a2,zero */ set(6,cpu(0));
    ps2ModelChangeMotionDefault(cpu(4),cpu(5),cpu(6));
    goto L_00171d2c;
L_00171d2c: ;
    /* 00171D2C: jal 0x0016ba70; native delay follows */
    set(31,UINT64_C(0x0000000000171d34));
    /* 00171D30: nop  */ ;
    set(2,effBTLSkillGetID());
    goto L_00171d34;
L_00171d34: ;
    /* 00171D34: sll v1,v0,0x4 */ set(3,sx(((uint32_t)cpu(2)<<4)));
L_00171d38: ;
    /* 00171D38: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
L_00171d3c: ;
    /* 00171D3C: sll v1,v1,0x2 */ set(3,sx(((uint32_t)cpu(3)<<2)));
L_00171d40: ;
    /* 00171D40: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
L_00171d44: ;
    /* 00171D44: lbu v0,0x2(v1) */ set(2,r8(ea(cpu(3),UINT32_C(0x00000002))));
L_00171d48: ;
    /* 00171D48: bnel v0,zero,0x00171d54; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      if(taken) { /* 00171D4C: lw a0,0x48(s2) */ set(4,sx(r32(ea(cpu(18),UINT32_C(0x00000048))))); goto L_00171d54; }
      goto L_00171d50; }
L_00171d50: ;
    /* 00171D50: lw a0,0x2c(s2) */ set(4,sx(r32(ea(cpu(18),UINT32_C(0x0000002c)))));
L_00171d54: ;
    /* 00171D54: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x0000000000171d5c));
    /* 00171D58: nop  */ ;
    body_00175a88();
    goto L_00171d5c;
L_00171d5c: ;
    /* 00171D5C: sw v0,0xec(s1) */ w32(ea(cpu(17),UINT32_C(0x000000ec)),(uint32_t)cpu(2));
L_00171d60: ;
    /* 00171D60: jal 0x0016fcf0; native delay follows */
    set(31,UINT64_C(0x0000000000171d68));
    /* 00171D64: lw a0,0xe0(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x000000e0)))));
    fpr()[0]=fbits(effBTLSystem_GetScalePtr(cpu(4)));
    goto L_00171d68;
L_00171d68: ;
    /* 00171D68: lw a0,0xe8(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x000000e8)))));
L_00171d6c: ;
    /* 00171D6C: mov.S f20,f0 */ fpr()[20]=fpr()[0];
L_00171d70: ;
    /* 00171D70: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x0000000000171d78));
    /* 00171D74: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_00171d78;
L_00171d78: ;
    /* 00171D78: lw a0,0xec(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x000000ec)))));
L_00171d7c: ;
    /* 00171D7C: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x0000000000171d84));
    /* 00171D80: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_00171d84;
L_00171d84: ;
    /* 00171D84: move v0,s1 */ set(2,cpu(17));
L_00171d88: ;
    /* 00171D88: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_00171d8c: ;
    /* 00171D8C: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_00171d90: ;
    /* 00171D90: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_00171d94: ;
    /* 00171D94: ld ra,0x18(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_00171d98: ;
    /* 00171D98: lwc1 f20,0x20(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x00000020)));
L_00171d9c: ;
    /* 00171D9C: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00171DA0: addiu sp,sp,0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030))); ba_return_target(incoming_ra,target); return; }
}

static void body_00172178(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00172178u);
L_00172178: ;
    /* 00172178: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
L_0017217c: ;
    /* 0017217C: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_00172180: ;
    /* 00172180: move s2,a0 */ set(18,cpu(4));
L_00172184: ;
    /* 00172184: li a0,0x18 */ set(4,UINT64_C(0x0000000000000018));
L_00172188: ;
    /* 00172188: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_0017218c: ;
    /* 0017218C: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00172190: ;
    /* 00172190: lui s1,0x32 */ set(17,sx(UINT32_C(0x00320000)));
L_00172194: ;
    /* 00172194: sd ra,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(31));
L_00172198: ;
    /* 00172198: addiu s1,s1,-0x4328 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffbcd8)));
L_0017219c: ;
    /* 0017219C: jal 0x002a8af8; native delay follows */
    set(31,UINT64_C(0x00000000001721a4));
    /* 001721A0: swc1 f20,0x20(sp) */ w32(ea(cpu(29),UINT32_C(0x00000020)),fpr()[20]);
    set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
    goto L_001721a4;
L_001721a4: ;
    /* 001721A4: move s0,v0 */ set(16,cpu(2));
L_001721a8: ;
    /* 001721A8: lw a0,0x10(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000010)))));
L_001721ac: ;
    /* 001721AC: sw s2,0x0(s0) */ w32(ea(cpu(16),UINT32_C(0x00000000)),(uint32_t)cpu(18));
L_001721b0: ;
    /* 001721B0: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x00000000001721b8));
    /* 001721B4: sw zero,0x4(s0) */ w32(ea(cpu(16),UINT32_C(0x00000004)),(uint32_t)cpu(0));
    body_00175a88();
    goto L_001721b8;
L_001721b8: ;
    /* 001721B8: sw v0,0x8(s0) */ w32(ea(cpu(16),UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_001721bc: ;
    /* 001721BC: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x00000000001721c4));
    /* 001721C0: lw a0,0x10(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000010)))));
    body_00175a88();
    goto L_001721c4;
L_001721c4: ;
    /* 001721C4: sw v0,0xc(s0) */ w32(ea(cpu(16),UINT32_C(0x0000000c)),(uint32_t)cpu(2));
L_001721c8: ;
    /* 001721C8: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x00000000001721d0));
    /* 001721CC: lw a0,0x10(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000010)))));
    body_00175a88();
    goto L_001721d0;
L_001721d0: ;
    /* 001721D0: sw v0,0x10(s0) */ w32(ea(cpu(16),UINT32_C(0x00000010)),(uint32_t)cpu(2));
L_001721d4: ;
    /* 001721D4: jal 0x00175a88; native delay follows */
    set(31,UINT64_C(0x00000000001721dc));
    /* 001721D8: lw a0,0x2c(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x0000002c)))));
    body_00175a88();
    goto L_001721dc;
L_001721dc: ;
    /* 001721DC: lw a0,0x0(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000000)))));
L_001721e0: ;
    /* 001721E0: jal 0x0016fcf0; native delay follows */
    set(31,UINT64_C(0x00000000001721e8));
    /* 001721E4: sw v0,0x14(s0) */ w32(ea(cpu(16),UINT32_C(0x00000014)),(uint32_t)cpu(2));
    fpr()[0]=fbits(effBTLSystem_GetScalePtr(cpu(4)));
    goto L_001721e8;
L_001721e8: ;
    /* 001721E8: lw a0,0x8(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000008)))));
L_001721ec: ;
    /* 001721EC: mov.S f20,f0 */ fpr()[20]=fpr()[0];
L_001721f0: ;
    /* 001721F0: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x00000000001721f8));
    /* 001721F4: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_001721f8;
L_001721f8: ;
    /* 001721F8: lw a0,0xc(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x0000000c)))));
L_001721fc: ;
    /* 001721FC: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x0000000000172204));
    /* 00172200: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_00172204;
L_00172204: ;
    /* 00172204: lw a0,0x10(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000010)))));
L_00172208: ;
    /* 00172208: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x0000000000172210));
    /* 0017220C: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_00172210;
L_00172210: ;
    /* 00172210: lw a0,0x14(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000014)))));
L_00172214: ;
    /* 00172214: jal 0x00175b38; native delay follows */
    set(31,UINT64_C(0x000000000017221c));
    /* 00172218: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    ps2BattleActionPartScale_00175B38(cpu(4),fvalue(fpr()[12]));
    goto L_0017221c;
L_0017221c: ;
    /* 0017221C: move v0,s0 */ set(2,cpu(16));
L_00172220: ;
    /* 00172220: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_00172224: ;
    /* 00172224: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_00172228: ;
    /* 00172228: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_0017222c: ;
    /* 0017222C: ld ra,0x18(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_00172230: ;
    /* 00172230: lwc1 f20,0x20(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x00000020)));
L_00172234: ;
    /* 00172234: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00172238: addiu sp,sp,0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030))); ba_return_target(incoming_ra,target); return; }
}

static void body_00173cb0(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00173cb0u);
L_00173cb0: ;
    /* 00173CB0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
L_00173cb4: ;
    /* 00173CB4: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00173cb8: ;
    /* 00173CB8: move s1,a0 */ set(17,cpu(4));
L_00173cbc: ;
    /* 00173CBC: li a0,0xc */ set(4,UINT64_C(0x000000000000000c));
L_00173cc0: ;
    /* 00173CC0: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_00173cc4: ;
    /* 00173CC4: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_00173cc8: ;
    /* 00173CC8: sd ra,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(31));
L_00173ccc: ;
    /* 00173CCC: jal 0x002a8af8; native delay follows */
    set(31,UINT64_C(0x0000000000173cd4));
    /* 00173CD0: move s0,a1 */ set(16,cpu(5));
    set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
    goto L_00173cd4;
L_00173cd4: ;
    /* 00173CD4: move s2,v0 */ set(18,cpu(2));
L_00173cd8: ;
    /* 00173CD8: sll v0,s0,0x3 */ set(2,sx(((uint32_t)cpu(16)<<3)));
L_00173cdc: ;
    /* 00173CDC: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
L_00173ce0: ;
    /* 00173CE0: move a0,s1 */ set(4,cpu(17));
L_00173ce4: ;
    /* 00173CE4: sll v0,v0,0x3 */ set(2,sx(((uint32_t)cpu(2)<<3)));
L_00173ce8: ;
    /* 00173CE8: sw s0,0x0(s2) */ w32(ea(cpu(18),UINT32_C(0x00000000)),(uint32_t)cpu(16));
L_00173cec: ;
    /* 00173CEC: lui at,0x32 */ set(1,sx(UINT32_C(0x00320000)));
L_00173cf0: ;
    /* 00173CF0: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
L_00173cf4: ;
    /* 00173CF4: lw v0,-0x4100(at) */ set(2,sx(r32(ea(cpu(1),UINT32_C(0xffffbf00)))));
L_00173cf8: ;
    /* 00173CF8: beq v0,zero,0x00173d0c; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00173CFC: sw s1,0x8(s2) */ w32(ea(cpu(18),UINT32_C(0x00000008)),(uint32_t)cpu(17));
      if(taken) goto L_00173d0c;
      goto L_00173d00; }
L_00173d00: ;
    /* 00173D00: jalr v0; native delay follows */
    { uint64_t target=cpu(2); set(31,UINT64_C(0x0000000000173d08));
      /* 00173D04: nop  */ ; callback(target); }
    goto L_00173d08;
L_00173d08: ;
    /* 00173D08: sw v0,0x4(s2) */ w32(ea(cpu(18),UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_00173d0c: ;
    /* 00173D0C: move v0,s2 */ set(2,cpu(18));
L_00173d10: ;
    /* 00173D10: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_00173d14: ;
    /* 00173D14: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_00173d18: ;
    /* 00173D18: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_00173d1c: ;
    /* 00173D1C: ld ra,0x18(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_00173d20: ;
    /* 00173D20: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00173D24: addiu sp,sp,0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020))); ba_return_target(incoming_ra,target); return; }
}

static void body_00173ef0(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00173ef0u);
L_00173ef0: ;
    /* 00173EF0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
L_00173ef4: ;
    /* 00173EF4: sd ra,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(31));
L_00173ef8: ;
    /* 00173EF8: lw v1,0x0(a0) */ set(3,sx(r32(ea(cpu(4),UINT32_C(0x00000000)))));
L_00173efc: ;
    /* 00173EFC: sll v0,v1,0x3 */ set(2,sx(((uint32_t)cpu(3)<<3)));
L_00173f00: ;
    /* 00173F00: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
L_00173f04: ;
    /* 00173F04: sll v0,v0,0x3 */ set(2,sx(((uint32_t)cpu(2)<<3)));
L_00173f08: ;
    /* 00173F08: lui at,0x32 */ set(1,sx(UINT32_C(0x00320000)));
L_00173f0c: ;
    /* 00173F0C: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
L_00173f10: ;
    /* 00173F10: lw v0,-0x40ec(at) */ set(2,sx(r32(ea(cpu(1),UINT32_C(0xffffbf14)))));
L_00173f14: ;
    /* 00173F14: beql v0,zero,0x00173f30; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      if(taken) { /* 00173F18: move v0,zero */ set(2,cpu(0)); goto L_00173f30; }
      goto L_00173f1c; }
L_00173f1c: ;
    /* 00173F1C: jalr v0; native delay follows */
    { uint64_t target=cpu(2); set(31,UINT64_C(0x0000000000173f24));
      /* 00173F20: lw a0,0x4(a0) */ set(4,sx(r32(ea(cpu(4),UINT32_C(0x00000004))))); callback(target); }
    goto L_00173f24;
L_00173f24: ;
    /* 00173F24: b 0x00173f34; native delay follows */
    { /* 00173F28: ld ra,0x0(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000000)))); goto L_00173f34; }
L_00173f30: ;
    /* 00173F30: ld ra,0x0(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_00173f34: ;
    /* 00173F34: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00173F38: addiu sp,sp,0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010))); ba_return_target(incoming_ra,target); return; }
}

static void body_0024f420(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x0024f420u);
L_0024f420: ;
    /* 0024F420: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
L_0024f424: ;
    /* 0024F424: li a3,0x2 */ set(7,UINT64_C(0x0000000000000002));
L_0024f428: ;
    /* 0024F428: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_0024f42c: ;
    /* 0024F42C: move s0,a0 */ set(16,cpu(4));
L_0024f430: ;
    /* 0024F430: sd ra,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(31));
L_0024f434: ;
    /* 0024F434: move a0,a1 */ set(4,cpu(5));
L_0024f438: ;
    /* 0024F438: move a1,s0 */ set(5,cpu(16));
L_0024f43c: ;
    /* 0024F43C: lw v1,0x28(s0) */ set(3,sx(r32(ea(cpu(16),UINT32_C(0x00000028)))));
L_0024f440: ;
    /* 0024F440: lh v0,0xa4(v1) */ set(2,sx((uint32_t)i16(r16(ea(cpu(3),UINT32_C(0x000000a4))))));
L_0024f444: ;
    /* 0024F444: bne v0,a3,0x0024f468; native delay follows */
    { int taken=(cpu(2)!=cpu(7));
      /* 0024F448: move a2,v1 */ set(6,cpu(3));
      if(taken) goto L_0024f468;
      goto L_0024f44c; }
L_0024f44c: ;
    /* 0024F44C: move a3,zero */ set(7,cpu(0));
L_0024f450: ;
    /* 0024F450: li t0,0x2 */ set(8,UINT64_C(0x0000000000000002));
L_0024f454: ;
    /* 0024F454: li t1,0x4 */ set(9,UINT64_C(0x0000000000000004));
L_0024f458: ;
    /* 0024F458: jal 0x00263810; native delay follows */
    set(31,UINT64_C(0x000000000024f460));
    /* 0024F45C: li t2,0x4 */ set(10,UINT64_C(0x0000000000000004));
    set(2,nbMakeUnitFadeInPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10)));
    goto L_0024f460;
L_0024f460: ;
    /* 0024F460: lw v1,0x28(s0) */ set(3,sx(r32(ea(cpu(16),UINT32_C(0x00000028)))));
L_0024f464: ;
    /* 0024F464: sh zero,0xa4(v1) */ w16(ea(cpu(3),UINT32_C(0x000000a4)),(uint16_t)cpu(0));
L_0024f468: ;
    /* 0024F468: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_0024f46c: ;
    /* 0024F46C: ld ra,0x8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_0024f470: ;
    /* 0024F470: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 0024F474: addiu sp,sp,0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010))); ba_return_target(incoming_ra,target); return; }
}

static void body_0024f478(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x0024f478u);
L_0024f478: ;
    /* 0024F478: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
L_0024f47c: ;
    /* 0024F47C: sll v0,a1,0x4 */ set(2,sx(((uint32_t)cpu(5)<<4)));
L_0024f480: ;
    /* 0024F480: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_0024f484: ;
    /* 0024F484: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
L_0024f488: ;
    /* 0024F488: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_0024f48c: ;
    /* 0024F48C: move s1,a0 */ set(17,cpu(4));
L_0024f490: ;
    /* 0024F490: sd s3,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(19));
L_0024f494: ;
    /* 0024F494: sll s3,v0,0x4 */ set(19,sx(((uint32_t)cpu(2)<<4)));
L_0024f498: ;
    /* 0024F498: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_0024f49c: ;
    /* 0024F49C: sd ra,0x20(sp) */ w64(ea(cpu(29),UINT32_C(0x00000020)),(uint64_t)cpu(31));
L_0024f4a0: ;
    /* 0024F4A0: lw a2,0x0(s1) */ set(6,sx(r32(ea(cpu(17),UINT32_C(0x00000000)))));
L_0024f4a4: ;
    /* 0024F4A4: lw v1,0x0(a2) */ set(3,sx(r32(ea(cpu(6),UINT32_C(0x00000000)))));
L_0024f4a8: ;
    /* 0024F4A8: lw a3,0x10(a2) */ set(7,sx(r32(ea(cpu(6),UINT32_C(0x00000010)))));
L_0024f4ac: ;
    /* 0024F4AC: addu v1,s3,v1 */ set(3,sx((uint32_t)cpu(19)+(uint32_t)cpu(3)));
L_0024f4b0: ;
    /* 0024F4B0: lh v0,0x90(v1) */ set(2,sx((uint32_t)i16(r16(ea(cpu(3),UINT32_C(0x00000090))))));
L_0024f4b4: ;
    /* 0024F4B4: sll v0,v0,0x7 */ set(2,sx(((uint32_t)cpu(2)<<7)));
L_0024f4b8: ;
    /* 0024F4B8: addu s0,a3,v0 */ set(16,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
L_0024f4bc: ;
    /* 0024F4BC: lhu v1,0x0(s0) */ set(3,r16(ea(cpu(16),UINT32_C(0x00000000))));
L_0024f4c0: ;
    /* 0024F4C0: andi v1,v1,0x20 */ set(3,cpu(3)&UINT64_C(0x0000000000000020));
L_0024f4c4: ;
    /* 0024F4C4: bnel v1,zero,0x0024f530; native delay follows */
    { int taken=(cpu(3)!=cpu(0));
      if(taken) { /* 0024F4C8: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000)))); goto L_0024f530; }
      goto L_0024f4cc; }
L_0024f4cc: ;
    /* 0024F4CC: jal 0x00251760; native delay follows */
    set(31,UINT64_C(0x000000000024f4d4));
    /* 0024F4D0: nop  */ ;
    set(2,nbActionGetEndTime(cpu(4),cpu(5)));
    goto L_0024f4d4;
L_0024f4d4: ;
    /* 0024F4D4: lw a0,0x0(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000000)))));
L_0024f4d8: ;
    /* 0024F4D8: move a1,s0 */ set(5,cpu(16));
L_0024f4dc: ;
    /* 0024F4DC: jal 0x002469c0; native delay follows */
    set(31,UINT64_C(0x000000000024f4e4));
    /* 0024F4E0: move s2,v0 */ set(18,cpu(2));
    set(2,nbGetUnitWorkPointer(cpu(4),cpu(5)));
    goto L_0024f4e4;
L_0024f4e4: ;
    /* 0024F4E4: lw v1,0x0(v0) */ set(3,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_0024f4e8: ;
    /* 0024F4E8: andi v1,v1,0x20 */ set(3,cpu(3)&UINT64_C(0x0000000000000020));
L_0024f4ec: ;
    /* 0024F4EC: beq v1,zero,0x0024f4fc; native delay follows */
    { int taken=(cpu(3)==cpu(0));
      /* 0024F4F0: move a0,v0 */ set(4,cpu(2));
      if(taken) goto L_0024f4fc;
      goto L_0024f4f4; }
L_0024f4f4: ;
    /* 0024F4F4: jal 0x00269448; native delay follows */
    set(31,UINT64_C(0x000000000024f4fc));
    /* 0024F4F8: nop  */ ;
    ps2CombatAddRewards_00269448(cpu(4));
    goto L_0024f4fc;
L_0024f4fc: ;
    /* 0024F4FC: lw v0,0x0(s1) */ set(2,sx(r32(ea(cpu(17),UINT32_C(0x00000000)))));
L_0024f500: ;
    /* 0024F500: move a0,s2 */ set(4,cpu(18));
L_0024f504: ;
    /* 0024F504: move a1,s1 */ set(5,cpu(17));
L_0024f508: ;
    /* 0024F508: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_0024f50c: ;
    /* 0024F50C: lw a2,0x0(v0) */ set(6,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_0024f510: ;
    /* 0024F510: move a3,zero */ set(7,cpu(0));
L_0024f514: ;
    /* 0024F514: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_0024f518: ;
    /* 0024F518: addu a2,a2,s3 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(19)));
L_0024f51c: ;
    /* 0024F51C: ld s3,0x18(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_0024f520: ;
    /* 0024F520: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_0024f524: ;
    /* 0024F524: ld ra,0x20(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000020))));
L_0024f528: ;
    /* 0024F528: j 0x002641f8; native delay follows */
    /* 0024F52C: addiu sp,sp,0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
    set(2,nbMakeDeadPacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    ba_return(incoming_ra); return;
L_0024f530: ;
    /* 0024F530: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_0024f534: ;
    /* 0024F534: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_0024f538: ;
    /* 0024F538: ld s3,0x18(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_0024f53c: ;
    /* 0024F53C: ld ra,0x20(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000020))));
L_0024f540: ;
    /* 0024F540: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 0024F544: addiu sp,sp,0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030))); ba_return_target(incoming_ra,target); return; }
}

static void body_0024f548(void)
{
    uint64_t incoming_ra=cpu(31);
    int condition=0;
    nocturneEffectAxisNoteEntry(0x0024f548u);
L_0024f548: ;
    /* 0024F548: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
L_0024f54c: ;
    /* 0024F54C: mtc1 at,f0 */ fpr()[0]=(uint32_t)cpu(1);
L_0024f550: ;
    /* 0024F550: c.lt.S f12,f0 */ condition=EE_FPU_COMPARE_S(fpr()[12],fpr()[0],1)!=0;
L_0024f554: ;
    /* 0024F554: bc1f 0x0024f570; native delay follows */
    { int taken=(!condition);
      /* 0024F558: nop  */ ;
      if(taken) goto L_0024f570;
      goto L_0024f55c; }
L_0024f55c: ;
    /* 0024F55C: lwc1 f0,0x14(a0) */ fpr()[0]=r32(ea(cpu(4),UINT32_C(0x00000014)));
L_0024f560: ;
    /* 0024F560: c.lt.S f12,f0 */ condition=EE_FPU_COMPARE_S(fpr()[12],fpr()[0],1)!=0;
L_0024f564: ;
    /* 0024F564: b 0x0024f59c; native delay follows */
    { /* 0024F568: nop  */ ; goto L_0024f59c; }
L_0024f570: ;
    /* 0024F570: c.lt.S f0,f12 */ condition=EE_FPU_COMPARE_S(fpr()[0],fpr()[12],1)!=0;
L_0024f574: ;
    /* 0024F574: bc1f 0x0024f594; native delay follows */
    { int taken=(!condition);
      /* 0024F578: lwc1 f1,0x14(a0) */ fpr()[1]=r32(ea(cpu(4),UINT32_C(0x00000014)));
      if(taken) goto L_0024f594;
      goto L_0024f57c; }
L_0024f57c: ;
    /* 0024F57C: c.le.S f0,f1 */ condition=EE_FPU_COMPARE_S(fpr()[0],fpr()[1],2)!=0;
L_0024f580: ;
    /* 0024F580: bc1f 0x0024f5a4; native delay follows */
    { int taken=(!condition);
      /* 0024F584: nop  */ ;
      if(taken) goto L_0024f5a4;
      goto L_0024f588; }
L_0024f588: ;
    /* 0024F588: c.lt.S f1,f12 */ condition=EE_FPU_COMPARE_S(fpr()[1],fpr()[12],1)!=0;
L_0024f58c: ;
    /* 0024F58C: bc1tl 0x0024f5a4; native delay follows */
    { int taken=(condition);
      if(taken) { /* 0024F590: swc1 f12,0x14(a0) */ w32(ea(cpu(4),UINT32_C(0x00000014)),fpr()[12]); goto L_0024f5a4; }
      goto L_0024f594; }
L_0024f594: ;
    /* 0024F594: clear f0 */ fpr()[0]=0;
L_0024f598: ;
    /* 0024F598: c.eq.S f1,f0 */ condition=EE_FPU_COMPARE_S(fpr()[1],fpr()[0],0)!=0;
L_0024f59c: ;
    /* 0024F59C: bc1tl 0x0024f5a4; native delay follows */
    { int taken=(condition);
      if(taken) { /* 0024F5A0: swc1 f12,0x14(a0) */ w32(ea(cpu(4),UINT32_C(0x00000014)),fpr()[12]); goto L_0024f5a4; }
      goto L_0024f5a4; }
L_0024f5a4: ;
    /* 0024F5A4: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 0024F5A8: nop  */ ; ba_return_target(incoming_ra,target); return; }
}

static void body_0024f5b0(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x0024f5b0u);
L_0024f5b0: ;
    /* 0024F5B0: lw v0,0x18(a0) */ set(2,sx(r32(ea(cpu(4),UINT32_C(0x00000018)))));
L_0024f5b4: ;
    /* 0024F5B4: slt v0,v0,a1 */ set(2,lt(cpu(2),cpu(5)));
L_0024f5b8: ;
    /* 0024F5B8: bnel v0,zero,0x0024f5c0; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      if(taken) { /* 0024F5BC: sw a1,0x18(a0) */ w32(ea(cpu(4),UINT32_C(0x00000018)),(uint32_t)cpu(5)); goto L_0024f5c0; }
      goto L_0024f5c0; }
L_0024f5c0: ;
    /* 0024F5C0: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 0024F5C4: nop  */ ; ba_return_target(incoming_ra,target); return; }
}

static void body_0024f5c8(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x0024f5c8u);
L_0024f5c8: ;
    /* 0024F5C8: lw v0,0x18c(a0) */ set(2,sx(r32(ea(cpu(4),UINT32_C(0x0000018c)))));
L_0024f5cc: ;
    /* 0024F5CC: addiu a1,a1,0x7 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000007)));
L_0024f5d0: ;
    /* 0024F5D0: beq v0,zero,0x0024f5e0; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 0024F5D4: slt v1,a1,v0 */ set(3,lt(cpu(5),cpu(2)));
      if(taken) goto L_0024f5e0;
      goto L_0024f5d8; }
L_0024f5d8: ;
    /* 0024F5D8: beq v1,zero,0x0024f5e4; native delay follows */
    { int taken=(cpu(3)==cpu(0));
      /* 0024F5DC: nop  */ ;
      if(taken) goto L_0024f5e4;
      goto L_0024f5e0; }
L_0024f5e0: ;
    /* 0024F5E0: sw a1,0x18c(a0) */ w32(ea(cpu(4),UINT32_C(0x0000018c)),(uint32_t)cpu(5));
L_0024f5e4: ;
    /* 0024F5E4: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 0024F5E8: nop  */ ; ba_return_target(incoming_ra,target); return; }
}

static void body_0024ff60(void)
{
    uint64_t incoming_ra=cpu(31);
    int condition=0;
    uint32_t lo=0;
    nocturneEffectAxisNoteEntry(0x0024ff60u);
L_0024ff60: ;
    /* 0024FF60: addiu sp,sp,-0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff00)));
L_0024ff64: ;
    /* 0024FF64: sd s1,0xa8(sp) */ w64(ea(cpu(29),UINT32_C(0x000000a8)),(uint64_t)cpu(17));
L_0024ff68: ;
    /* 0024FF68: move s1,t0 */ set(17,cpu(8));
L_0024ff6c: ;
    /* 0024FF6C: sd s7,0xd8(sp) */ w64(ea(cpu(29),UINT32_C(0x000000d8)),(uint64_t)cpu(23));
L_0024ff70: ;
    /* 0024FF70: move s7,a2 */ set(23,cpu(6));
L_0024ff74: ;
    /* 0024FF74: sd s8,0xe0(sp) */ w64(ea(cpu(29),UINT32_C(0x000000e0)),(uint64_t)cpu(30));
L_0024ff78: ;
    /* 0024FF78: move s8,a3 */ set(30,cpu(7));
L_0024ff7c: ;
    /* 0024FF7C: sd s2,0xb0(sp) */ w64(ea(cpu(29),UINT32_C(0x000000b0)),(uint64_t)cpu(18));
L_0024ff80: ;
    /* 0024FF80: move s2,a0 */ set(18,cpu(4));
L_0024ff84: ;
    /* 0024FF84: sw a1,0x20(sp) */ w32(ea(cpu(29),UINT32_C(0x00000020)),(uint32_t)cpu(5));
L_0024ff88: ;
    /* 0024FF88: move a1,s8 */ set(5,cpu(30));
L_0024ff8c: ;
    /* 0024FF8C: move a0,s7 */ set(4,cpu(23));
L_0024ff90: ;
    /* 0024FF90: move a2,s1 */ set(6,cpu(17));
L_0024ff94: ;
    /* 0024FF94: sd s3,0xb8(sp) */ w64(ea(cpu(29),UINT32_C(0x000000b8)),(uint64_t)cpu(19));
L_0024ff98: ;
    /* 0024FF98: move s3,t2 */ set(19,cpu(10));
L_0024ff9c: ;
    /* 0024FF9C: sd s6,0xd0(sp) */ w64(ea(cpu(29),UINT32_C(0x000000d0)),(uint64_t)cpu(22));
L_0024ffa0: ;
    /* 0024FFA0: swc1 f20,0xf0(sp) */ w32(ea(cpu(29),UINT32_C(0x000000f0)),fpr()[20]);
L_0024ffa4: ;
    /* 0024FFA4: mov.S f20,f12 */ fpr()[20]=fpr()[12];
L_0024ffa8: ;
    /* 0024FFA8: sd s0,0xa0(sp) */ w64(ea(cpu(29),UINT32_C(0x000000a0)),(uint64_t)cpu(16));
L_0024ffac: ;
    /* 0024FFAC: sd s4,0xc0(sp) */ w64(ea(cpu(29),UINT32_C(0x000000c0)),(uint64_t)cpu(20));
L_0024ffb0: ;
    /* 0024FFB0: sd s5,0xc8(sp) */ w64(ea(cpu(29),UINT32_C(0x000000c8)),(uint64_t)cpu(21));
L_0024ffb4: ;
    /* 0024FFB4: sd ra,0xe8(sp) */ w64(ea(cpu(29),UINT32_C(0x000000e8)),(uint64_t)cpu(31));
L_0024ffb8: ;
    /* 0024FFB8: swc1 f21,0xf8(sp) */ w32(ea(cpu(29),UINT32_C(0x000000f8)),fpr()[21]);
L_0024ffbc: ;
    /* 0024FFBC: sw s1,0x7c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000007c)),(uint32_t)cpu(17));
L_0024ffc0: ;
    /* 0024FFC0: jal 0x00266130; native delay follows */
    set(31,UINT64_C(0x000000000024ffc8));
    /* 0024FFC4: sw t1,0x24(sp) */ w32(ea(cpu(29),UINT32_C(0x00000024)),(uint32_t)cpu(9));
    fpr()[0]=fbits(nbGetAisyoRitu(cpu(4),cpu(5),cpu(6)));
    goto L_0024ffc8;
L_0024ffc8: ;
    /* 0024FFC8: mul.S f20,f0,f20 */ fpr()[20]=EE_FPU_MUL_S(fpr()[0],fpr()[20]);
L_0024ffcc: ;
    /* 0024FFCC: lw a2,0x7c(sp) */ set(6,sx(r32(ea(cpu(29),UINT32_C(0x0000007c)))));
L_0024ffd0: ;
    /* 0024FFD0: move a0,s7 */ set(4,cpu(23));
L_0024ffd4: ;
    /* 0024FFD4: move a3,zero */ set(7,cpu(0));
L_0024ffd8: ;
    /* 0024FFD8: move a1,s8 */ set(5,cpu(30));
L_0024ffdc: ;
    /* 0024FFDC: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_0024ffe0: ;
    /* 0024FFE0: sw v0,0x44(sp) */ w32(ea(cpu(29),UINT32_C(0x00000044)),(uint32_t)cpu(2));
L_0024ffe4: ;
    /* 0024FFE4: mov.S f12,f20 */ fpr()[12]=fpr()[20];
L_0024ffe8: ;
    /* 0024FFE8: sw zero,0x30(sp) */ w32(ea(cpu(29),UINT32_C(0x00000030)),(uint32_t)cpu(0));
L_0024ffec: ;
    /* 0024FFEC: sw zero,0x48(sp) */ w32(ea(cpu(29),UINT32_C(0x00000048)),(uint32_t)cpu(0));
L_0024fff0: ;
    /* 0024FFF0: sw zero,0x70(sp) */ w32(ea(cpu(29),UINT32_C(0x00000070)),(uint32_t)cpu(0));
L_0024fff4: ;
    /* 0024FFF4: jal 0x00266d60; native delay follows */
    set(31,UINT64_C(0x000000000024fffc));
    /* 0024FFF8: sw zero,0x78(sp) */ w32(ea(cpu(29),UINT32_C(0x00000078)),(uint32_t)cpu(0));
    set(2,nbGetKoukaBadDamage(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_0024fffc;
L_0024fffc: ;
    /* 0024FFFC: lw a2,0x7c(sp) */ set(6,sx(r32(ea(cpu(29),UINT32_C(0x0000007c)))));
L_00250000: ;
    /* 00250000: move a0,s7 */ set(4,cpu(23));
L_00250004: ;
    /* 00250004: move a1,s8 */ set(5,cpu(30));
L_00250008: ;
    /* 00250008: mov.S f12,f20 */ fpr()[12]=fpr()[20];
L_0025000c: ;
    /* 0025000C: move a3,zero */ set(7,cpu(0));
L_00250010: ;
    /* 00250010: jal 0x00267180; native delay follows */
    set(31,UINT64_C(0x0000000000250018));
    /* 00250014: move s6,v0 */ set(22,cpu(2));
    set(2,nbGetKoukaBadKaifuku(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00250018;
L_00250018: ;
    /* 00250018: move a0,s2 */ set(4,cpu(18));
L_0025001c: ;
    /* 0025001C: sw v0,0x3c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000003c)),(uint32_t)cpu(2));
L_00250020: ;
    /* 00250020: move a1,s7 */ set(5,cpu(23));
L_00250024: ;
    /* 00250024: lw a3,0x7c(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x0000007c)))));
L_00250028: ;
    /* 00250028: move a2,s8 */ set(6,cpu(30));
L_0025002c: ;
    /* 0025002C: lw v1,0x58(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000058)))));
L_00250030: ;
    /* 00250030: jal 0x002654b8; native delay follows */
    set(31,UINT64_C(0x0000000000250038));
    /* 00250034: sw v1,0x28(sp) */ w32(ea(cpu(29),UINT32_C(0x00000028)),(uint32_t)cpu(3));
    set(2,ps2CombatHitType_002654B8(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00250038;
L_00250038: ;
    /* 00250038: lw a0,0x20(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
L_0025003c: ;
    /* 0025003C: lw a1,0x44(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000044)))));
L_00250040: ;
    /* 00250040: sw v0,0x2c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000002c)),(uint32_t)cpu(2));
L_00250044: ;
    /* 00250044: sw zero,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(0));
L_00250048: ;
    /* 00250048: sw zero,0x6c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000006c)),(uint32_t)cpu(0));
L_0025004c: ;
    /* 0025004C: sw zero,0x54(sp) */ w32(ea(cpu(29),UINT32_C(0x00000054)),(uint32_t)cpu(0));
L_00250050: ;
    /* 00250050: sw zero,0x58(sp) */ w32(ea(cpu(29),UINT32_C(0x00000058)),(uint32_t)cpu(0));
L_00250054: ;
    /* 00250054: sw zero,0x5c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000005c)),(uint32_t)cpu(0));
L_00250058: ;
    /* 00250058: sw zero,0x60(sp) */ w32(ea(cpu(29),UINT32_C(0x00000060)),(uint32_t)cpu(0));
L_0025005c: ;
    /* 0025005C: sw zero,0x4c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000004c)),(uint32_t)cpu(0));
L_00250060: ;
    /* 00250060: bne a0,a1,0x00250070; native delay follows */
    { int taken=(cpu(4)!=cpu(5));
      /* 00250064: sw zero,0x50(sp) */ w32(ea(cpu(29),UINT32_C(0x00000050)),(uint32_t)cpu(0));
      if(taken) goto L_00250070;
      goto L_00250068; }
L_00250068: ;
    /* 00250068: lw a3,0x28(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000028)))));
L_0025006c: ;
    /* 0025006C: sw a3,0x58(s2) */ w32(ea(cpu(18),UINT32_C(0x00000058)),(uint32_t)cpu(7));
L_00250070: ;
    /* 00250070: lw v0,0x2c(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x0000002c)))));
L_00250074: ;
    /* 00250074: lw v1,0x44(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000044)))));
L_00250078: ;
    /* 00250078: bnel v0,v1,0x00250094; native delay follows */
    { int taken=(cpu(2)!=cpu(3));
      if(taken) { /* 0025007C: lw v0,0x4(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000004))))); goto L_00250094; }
      goto L_00250080; }
L_00250080: ;
    /* 00250080: mov.S f12,f20 */ fpr()[12]=fpr()[20];
L_00250084: ;
    /* 00250084: jal 0x0026a828; native delay follows */
    set(31,UINT64_C(0x000000000025008c));
    /* 00250088: move a0,s8 */ set(4,cpu(30));
    fpr()[0]=fbits(ps2CombatCriticalPower_0026A828(cpu(4),fvalue(fpr()[12])));
    goto L_0025008c;
L_0025008c: ;
    /* 0025008C: mov.S f20,f0 */ fpr()[20]=fpr()[0];
L_00250090: ;
    /* 00250090: lw v0,0x4(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000004)))));
L_00250094: ;
    /* 00250094: lui at,0x4040 */ set(1,sx(UINT32_C(0x40400000)));
L_00250098: ;
    /* 00250098: mtc1 at,f21 */ fpr()[21]=(uint32_t)cpu(1);
L_0025009c: ;
    /* 0025009C: andi v0,v0,0x100 */ set(2,cpu(2)&UINT64_C(0x0000000000000100));
L_002500a0: ;
    /* 002500A0: bne v0,zero,0x002500b0; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 002500A4: lw a0,0x20(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
      if(taken) goto L_002500b0;
      goto L_002500a8; }
L_002500a8: ;
    /* 002500A8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
L_002500ac: ;
    /* 002500AC: mtc1 at,f21 */ fpr()[21]=(uint32_t)cpu(1);
L_002500b0: ;
    /* 002500B0: li v0,0x2 */ set(2,UINT64_C(0x0000000000000002));
L_002500b4: ;
    /* 002500B4: beq a0,v0,0x00250348; native delay follows */
    { int taken=(cpu(4)==cpu(2));
      /* 002500B8: slti v0,a0,0x3 */ set(2,lt(cpu(4),UINT64_C(0x0000000000000003)));
      if(taken) goto L_00250348;
      goto L_002500bc; }
L_002500bc: ;
    /* 002500BC: beq v0,zero,0x002500d8; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002500C0: lw a3,0x20(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
      if(taken) goto L_002500d8;
      goto L_002500c4; }
L_002500c4: ;
    /* 002500C4: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_002500c8: ;
    /* 002500C8: beq a0,v0,0x002500f0; native delay follows */
    { int taken=(cpu(4)==cpu(2));
      /* 002500CC: slti a1,s1,0x10 */ set(5,lt(cpu(17),UINT64_C(0x0000000000000010)));
      if(taken) goto L_002500f0;
      goto L_002500d0; }
L_002500d0: ;
    /* 002500D0: b 0x0025045c; native delay follows */
    { /* 002500D4: sw a1,0x90(sp) */ w32(ea(cpu(29),UINT32_C(0x00000090)),(uint32_t)cpu(5)); goto L_0025045c; }
L_002500d8: ;
    /* 002500D8: li v0,0x3 */ set(2,UINT64_C(0x0000000000000003));
L_002500dc: ;
    /* 002500DC: beq a3,v0,0x00250430; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 002500E0: slti v0,s1,0x10 */ set(2,lt(cpu(17),UINT64_C(0x0000000000000010)));
      if(taken) goto L_00250430;
      goto L_002500e4; }
L_002500e4: ;
    /* 002500E4: b 0x0025045c; native delay follows */
    { /* 002500E8: sw v0,0x90(sp) */ w32(ea(cpu(29),UINT32_C(0x00000090)),(uint32_t)cpu(2)); goto L_0025045c; }
L_002500f0: ;
    /* 002500F0: li v0,0x107 */ set(2,UINT64_C(0x0000000000000107));
L_002500f4: ;
    /* 002500F4: bnel s7,v0,0x00250110; native delay follows */
    { int taken=(cpu(23)!=cpu(2));
      if(taken) { /* 002500F8: addiu v0,s3,0x5a */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0x0000005a))); goto L_00250110; }
      goto L_002500fc; }
L_002500fc: ;
    /* 002500FC: jal 0x002469a0; native delay follows */
    set(31,UINT64_C(0x0000000000250104));
    /* 00250100: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
    set(2,nbGetMainProcessData());
    goto L_00250104;
L_00250104: ;
    /* 00250104: lw v1,0x20(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
L_00250108: ;
    /* 00250108: sw v1,0x144(v0) */ w32(ea(cpu(2),UINT32_C(0x00000144)),(uint32_t)cpu(3));
L_0025010c: ;
    /* 0025010C: addiu v0,s3,0x5a */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0x0000005a)));
L_00250110: ;
    /* 00250110: xori v1,s7,0x108 */ set(3,cpu(23)^UINT64_C(0x0000000000000108));
L_00250114: ;
    /* 00250114: li a0,0x113 */ set(4,UINT64_C(0x0000000000000113));
L_00250118: ;
    /* 00250118: bne s7,a0,0x00250130; native delay follows */
    { int taken=(cpu(23)!=cpu(4));
      /* 0025011C: movz s3,v0,v1 */ if(cpu(3)==0) set(19,cpu(2));
      if(taken) goto L_00250130;
      goto L_00250120; }
L_00250120: ;
    /* 00250120: jal 0x002469a0; native delay follows */
    set(31,UINT64_C(0x0000000000250128));
    /* 00250124: nop  */ ;
    set(2,nbGetMainProcessData());
    goto L_00250128;
L_00250128: ;
    /* 00250128: lw a0,0x20(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
L_0025012c: ;
    /* 0025012C: sw a0,0x148(v0) */ w32(ea(cpu(2),UINT32_C(0x00000148)),(uint32_t)cpu(4));
L_00250130: ;
    /* 00250130: slti v0,s1,0x10 */ set(2,lt(cpu(17),UINT64_C(0x0000000000000010)));
L_00250134: ;
    /* 00250134: beq v0,zero,0x00250168; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250138: move a1,s3 */ set(5,cpu(19));
      if(taken) goto L_00250168;
      goto L_0025013c; }
L_0025013c: ;
    /* 0025013C: lw v0,0x0(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_00250140: ;
    /* 00250140: sll a2,s1,0x4 */ set(6,sx(((uint32_t)cpu(17)<<4)));
L_00250144: ;
    /* 00250144: subu a2,a2,s1 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(17)));
L_00250148: ;
    /* 00250148: move a0,s3 */ set(4,cpu(19));
L_0025014c: ;
    /* 0025014C: lw v1,0x0(v0) */ set(3,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_00250150: ;
    /* 00250150: sll a2,a2,0x4 */ set(6,sx(((uint32_t)cpu(6)<<4)));
L_00250154: ;
    /* 00250154: move a1,s2 */ set(5,cpu(18));
L_00250158: ;
    /* 00250158: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
L_0025015c: ;
    /* 0025015C: jal 0x00262480; native delay follows */
    set(31,UINT64_C(0x0000000000250164));
    /* 00250160: addu a2,v1,a2 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
    body_00262480();
    goto L_00250164;
L_00250164: ;
    /* 00250164: move a1,s3 */ set(5,cpu(19));
L_00250168: ;
    /* 00250168: jal 0x0024f5c8; native delay follows */
    set(31,UINT64_C(0x0000000000250170));
    /* 0025016C: move a0,s2 */ set(4,cpu(18));
    body_0024f5c8();
    goto L_00250170;
L_00250170: ;
    /* 00250170: move a0,s2 */ set(4,cpu(18));
L_00250174: ;
    /* 00250174: move a1,s1 */ set(5,cpu(17));
L_00250178: ;
    /* 00250178: move s1,s8 */ set(17,cpu(30));
L_0025017c: ;
    /* 0025017C: move a2,s3 */ set(6,cpu(19));
L_00250180: ;
    /* 00250180: addiu s3,s3,0xd */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x0000000d)));
L_00250184: ;
    /* 00250184: li a3,0xf */ set(7,UINT64_C(0x000000000000000f));
L_00250188: ;
    /* 00250188: jal 0x002517e0; native delay follows */
    set(31,UINT64_C(0x0000000000250190));
    /* 0025018C: li t0,0x1e */ set(8,UINT64_C(0x000000000000001e));
    nbActionSetTimeList(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00250190;
L_00250190: ;
    /* 00250190: jal 0x00267e38; native delay follows */
    set(31,UINT64_C(0x0000000000250198));
    /* 00250194: move a0,s7 */ set(4,cpu(23));
    set(2,nbGetNormalSkillAttr(cpu(4)));
    goto L_00250198;
L_00250198: ;
    /* 00250198: li a0,-0x1 */ set(4,UINT64_C(0xffffffffffffffff));
L_0025019c: ;
    /* 0025019C: move a1,s8 */ set(5,cpu(30));
L_002501a0: ;
    /* 002501A0: jal 0x00267890; native delay follows */
    set(31,UINT64_C(0x00000000002501a8));
    /* 002501A4: move a2,v0 */ set(6,cpu(2));
    set(2,nbGetAisyo(cpu(4),cpu(5),cpu(6)));
    goto L_002501a8;
L_002501a8: ;
    /* 002501A8: lui v1,0x7 */ set(3,sx(UINT32_C(0x00070000)));
L_002501ac: ;
    /* 002501AC: li a1,0x1 */ set(5,UINT64_C(0x0000000000000001));
L_002501b0: ;
    /* 002501B0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
L_002501b4: ;
    /* 002501B4: sw a1,0x24(sp) */ w32(ea(cpu(29),UINT32_C(0x00000024)),(uint32_t)cpu(5));
L_002501b8: ;
    /* 002501B8: beq v0,zero,0x002501d0; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002501BC: sw zero,0x44(sp) */ w32(ea(cpu(29),UINT32_C(0x00000044)),(uint32_t)cpu(0));
      if(taken) goto L_002501d0;
      goto L_002501c0; }
L_002501c0: ;
    /* 002501C0: lui a3,0x1 */ set(7,sx(UINT32_C(0x00010000)));
L_002501c4: ;
    /* 002501C4: move s6,zero */ set(22,cpu(0));
L_002501c8: ;
    /* 002501C8: b 0x002501d4; native delay follows */
    { /* 002501CC: sw a3,0x30(sp) */ w32(ea(cpu(29),UINT32_C(0x00000030)),(uint32_t)cpu(7)); goto L_002501d4; }
L_002501d0: ;
    /* 002501D0: sw zero,0x30(sp) */ w32(ea(cpu(29),UINT32_C(0x00000030)),(uint32_t)cpu(0));
L_002501d4: ;
    /* 002501D4: li v0,0x80 */ set(2,UINT64_C(0x0000000000000080));
L_002501d8: ;
    /* 002501D8: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 002501DC: sltiu v0,s6,0x81 */ set(2,(cpu(22)<UINT64_C(0x0000000000000081)));
      if(taken) goto L_002502d0;
      goto L_002501e0; }
L_002501e0: ;
    /* 002501E0: beq v0,zero,0x00250258; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002501E4: li v0,0x800 */ set(2,UINT64_C(0x0000000000000800));
      if(taken) goto L_00250258;
      goto L_002501e8; }
L_002501e8: ;
    /* 002501E8: li v0,0x8 */ set(2,UINT64_C(0x0000000000000008));
L_002501ec: ;
    /* 002501EC: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 002501F0: sltiu v0,s6,0x9 */ set(2,(cpu(22)<UINT64_C(0x0000000000000009)));
      if(taken) goto L_002502d0;
      goto L_002501f4; }
L_002501f4: ;
    /* 002501F4: beq v0,zero,0x00250220; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002501F8: li v0,0x20 */ set(2,UINT64_C(0x0000000000000020));
      if(taken) goto L_00250220;
      goto L_002501fc; }
L_002501fc: ;
    /* 002501FC: beql s6,zero,0x002502f8; native delay follows */
    { int taken=(cpu(22)==cpu(0));
      if(taken) { /* 00250200: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000))))); goto L_002502f8; }
      goto L_00250204; }
L_00250204: ;
    /* 00250204: sltiu v0,s6,0x3 */ set(2,(cpu(22)<UINT64_C(0x0000000000000003)));
L_00250208: ;
    /* 00250208: bne v0,zero,0x002502d0; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 0025020C: li v0,0x4 */ set(2,UINT64_C(0x0000000000000004));
      if(taken) goto L_002502d0;
      goto L_00250210; }
L_00250210: ;
    /* 00250210: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 00250214: nop  */ ;
      if(taken) goto L_002502d0;
      goto L_00250218; }
L_00250218: ;
    /* 00250218: b 0x002502f8; native delay follows */
    { /* 0025021C: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000))))); goto L_002502f8; }
L_00250220: ;
    /* 00250220: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 00250224: sltiu v0,s6,0x21 */ set(2,(cpu(22)<UINT64_C(0x0000000000000021)));
      if(taken) goto L_002502d0;
      goto L_00250228; }
L_00250228: ;
    /* 00250228: beq v0,zero,0x00250248; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 0025022C: li v0,0x40 */ set(2,UINT64_C(0x0000000000000040));
      if(taken) goto L_00250248;
      goto L_00250230; }
L_00250230: ;
    /* 00250230: li v0,0x10 */ set(2,UINT64_C(0x0000000000000010));
L_00250234: ;
    /* 00250234: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 00250238: nop  */ ;
      if(taken) goto L_002502d0;
      goto L_0025023c; }
L_0025023c: ;
    /* 0025023C: b 0x002502f8; native delay follows */
    { /* 00250240: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000))))); goto L_002502f8; }
L_00250248: ;
    /* 00250248: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 0025024C: nop  */ ;
      if(taken) goto L_002502d0;
      goto L_00250250; }
L_00250250: ;
    /* 00250250: b 0x002502f8; native delay follows */
    { /* 00250254: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000))))); goto L_002502f8; }
L_00250258: ;
    /* 00250258: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 0025025C: sltiu v0,s6,0x801 */ set(2,(cpu(22)<UINT64_C(0x0000000000000801)));
      if(taken) goto L_002502d0;
      goto L_00250260; }
L_00250260: ;
    /* 00250260: beq v0,zero,0x002502a0; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250264: li v0,0x2000 */ set(2,UINT64_C(0x0000000000002000));
      if(taken) goto L_002502a0;
      goto L_00250268; }
L_00250268: ;
    /* 00250268: li v0,0x200 */ set(2,UINT64_C(0x0000000000000200));
L_0025026c: ;
    /* 0025026C: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 00250270: sltiu v0,s6,0x201 */ set(2,(cpu(22)<UINT64_C(0x0000000000000201)));
      if(taken) goto L_002502d0;
      goto L_00250274; }
L_00250274: ;
    /* 00250274: beq v0,zero,0x00250290; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250278: li v0,0x400 */ set(2,UINT64_C(0x0000000000000400));
      if(taken) goto L_00250290;
      goto L_0025027c; }
L_0025027c: ;
    /* 0025027C: li v0,0x100 */ set(2,UINT64_C(0x0000000000000100));
L_00250280: ;
    /* 00250280: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 00250284: nop  */ ;
      if(taken) goto L_002502d0;
      goto L_00250288; }
L_00250288: ;
    /* 00250288: b 0x002502f8; native delay follows */
    { /* 0025028C: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000))))); goto L_002502f8; }
L_00250290: ;
    /* 00250290: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 00250294: nop  */ ;
      if(taken) goto L_002502d0;
      goto L_00250298; }
L_00250298: ;
    /* 00250298: b 0x002502f8; native delay follows */
    { /* 0025029C: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000))))); goto L_002502f8; }
L_002502a0: ;
    /* 002502A0: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 002502A4: sltiu v0,s6,0x2001 */ set(2,(cpu(22)<UINT64_C(0x0000000000002001)));
      if(taken) goto L_002502d0;
      goto L_002502a8; }
L_002502a8: ;
    /* 002502A8: beq v0,zero,0x002502c8; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002502AC: li v0,0x4000 */ set(2,UINT64_C(0x0000000000004000));
      if(taken) goto L_002502c8;
      goto L_002502b0; }
L_002502b0: ;
    /* 002502B0: li v0,0x1000 */ set(2,UINT64_C(0x0000000000001000));
L_002502b4: ;
    /* 002502B4: beq s6,v0,0x002502d0; native delay follows */
    { int taken=(cpu(22)==cpu(2));
      /* 002502B8: nop  */ ;
      if(taken) goto L_002502d0;
      goto L_002502bc; }
L_002502bc: ;
    /* 002502BC: b 0x002502f8; native delay follows */
    { /* 002502C0: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000))))); goto L_002502f8; }
L_002502c8: ;
    /* 002502C8: bnel s6,v0,0x002502f8; native delay follows */
    { int taken=(cpu(22)!=cpu(2));
      if(taken) { /* 002502CC: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000))))); goto L_002502f8; }
      goto L_002502d0; }
L_002502d0: ;
    /* 002502D0: jal 0x002440c0; native delay follows */
    set(31,UINT64_C(0x00000000002502d8));
    /* 002502D4: move a0,s6 */ set(4,cpu(22));
    set(2,sx((uint32_t)datGetBadStatusAttr(i32((uint32_t)cpu(4)))));
    goto L_002502d8;
L_002502d8: ;
    /* 002502D8: move a0,s7 */ set(4,cpu(23));
L_002502dc: ;
    /* 002502DC: move a1,s8 */ set(5,cpu(30));
L_002502e0: ;
    /* 002502E0: jal 0x00267890; native delay follows */
    set(31,UINT64_C(0x00000000002502e8));
    /* 002502E4: move a2,v0 */ set(6,cpu(2));
    set(2,nbGetAisyo(cpu(4),cpu(5),cpu(6)));
    goto L_002502e8;
L_002502e8: ;
    /* 002502E8: lui v1,0x17 */ set(3,sx(UINT32_C(0x00170000)));
L_002502ec: ;
    /* 002502EC: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
L_002502f0: ;
    /* 002502F0: movn s6,zero,v0 */ if(cpu(2)!=0) set(22,cpu(0));
L_002502f4: ;
    /* 002502F4: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_002502f8: ;
    /* 002502F8: lw v0,0x60(v1) */ set(2,sx(r32(ea(cpu(3),UINT32_C(0x00000060)))));
L_002502fc: ;
    /* 002502FC: andi v0,v0,0x400 */ set(2,cpu(2)&UINT64_C(0x0000000000000400));
L_00250300: ;
    /* 00250300: beql v0,zero,0x00250328; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      if(taken) { /* 00250304: li v0,0xd4 */ set(2,UINT64_C(0x00000000000000d4)); goto L_00250328; }
      goto L_00250308; }
L_00250308: ;
    /* 00250308: jal 0x0026a468; native delay follows */
    set(31,UINT64_C(0x0000000000250310));
    /* 0025030C: move a0,s8 */ set(4,cpu(30));
    set(2,nbCheckFormationPlayerSide(cpu(4)));
    goto L_00250310;
L_00250310: ;
    /* 00250310: bne v0,zero,0x00250328; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250314: li v0,0xd4 */ set(2,UINT64_C(0x00000000000000d4));
      if(taken) goto L_00250328;
      goto L_00250318; }
L_00250318: ;
    /* 00250318: lui v0,0x1 */ set(2,sx(UINT32_C(0x00010000)));
L_0025031c: ;
    /* 0025031C: move s6,zero */ set(22,cpu(0));
L_00250320: ;
    /* 00250320: sw v0,0x30(sp) */ w32(ea(cpu(29),UINT32_C(0x00000030)),(uint32_t)cpu(2));
L_00250324: ;
    /* 00250324: li v0,0xd4 */ set(2,UINT64_C(0x00000000000000d4));
L_00250328: ;
    /* 00250328: bne s7,v0,0x0025033c; native delay follows */
    { int taken=(cpu(23)!=cpu(2));
      /* 0025032C: slti a0,s8,0x10 */ set(4,lt(cpu(30),UINT64_C(0x0000000000000010)));
      if(taken) goto L_0025033c;
      goto L_00250330; }
L_00250330: ;
    /* 00250330: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
L_00250334: ;
    /* 00250334: move s6,zero */ set(22,cpu(0));
L_00250338: ;
    /* 00250338: sw v1,0x30(sp) */ w32(ea(cpu(29),UINT32_C(0x00000030)),(uint32_t)cpu(3));
L_0025033c: ;
    /* 0025033C: b 0x00250458; native delay follows */
    { /* 00250340: sw zero,0x2c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000002c)),(uint32_t)cpu(0)); goto L_00250458; }
L_00250348: ;
    /* 00250348: addiu v1,s3,0x8 */ set(3,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
L_0025034c: ;
    /* 0025034C: xori v0,s7,0x106 */ set(2,cpu(23)^UINT64_C(0x0000000000000106));
L_00250350: ;
    /* 00250350: movz s3,v1,v0 */ if(cpu(2)==0) set(19,cpu(3));
L_00250354: ;
    /* 00250354: xori v1,s7,0x108 */ set(3,cpu(23)^UINT64_C(0x0000000000000108));
L_00250358: ;
    /* 00250358: addiu v0,s3,0x3c */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0x0000003c)));
L_0025035c: ;
    /* 0025035C: xori a0,s7,0x107 */ set(4,cpu(23)^UINT64_C(0x0000000000000107));
L_00250360: ;
    /* 00250360: movz s3,v0,a0 */ if(cpu(4)==0) set(19,cpu(2));
L_00250364: ;
    /* 00250364: slti a1,s1,0x10 */ set(5,lt(cpu(17),UINT64_C(0x0000000000000010)));
L_00250368: ;
    /* 00250368: addiu v0,s3,0x5a */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0x0000005a)));
L_0025036c: ;
    /* 0025036C: sw a1,0x90(sp) */ w32(ea(cpu(29),UINT32_C(0x00000090)),(uint32_t)cpu(5));
L_00250370: ;
    /* 00250370: beq a1,zero,0x002503a0; native delay follows */
    { int taken=(cpu(5)==cpu(0));
      /* 00250374: movz s3,v0,v1 */ if(cpu(3)==0) set(19,cpu(2));
      if(taken) goto L_002503a0;
      goto L_00250378; }
L_00250378: ;
    /* 00250378: lw v0,0x0(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_0025037c: ;
    /* 0025037C: sll a2,s1,0x4 */ set(6,sx(((uint32_t)cpu(17)<<4)));
L_00250380: ;
    /* 00250380: subu a2,a2,s1 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(17)));
L_00250384: ;
    /* 00250384: move a0,s3 */ set(4,cpu(19));
L_00250388: ;
    /* 00250388: lw v1,0x0(v0) */ set(3,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_0025038c: ;
    /* 0025038C: sll a2,a2,0x4 */ set(6,sx(((uint32_t)cpu(6)<<4)));
L_00250390: ;
    /* 00250390: move a1,s2 */ set(5,cpu(18));
L_00250394: ;
    /* 00250394: li a3,0x2 */ set(7,UINT64_C(0x0000000000000002));
L_00250398: ;
    /* 00250398: jal 0x00262480; native delay follows */
    set(31,UINT64_C(0x00000000002503a0));
    /* 0025039C: addu a2,v1,a2 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
    body_00262480();
    goto L_002503a0;
L_002503a0: ;
    /* 002503A0: move a1,s3 */ set(5,cpu(19));
L_002503a4: ;
    /* 002503A4: jal 0x0024f5c8; native delay follows */
    set(31,UINT64_C(0x00000000002503ac));
    /* 002503A8: move a0,s2 */ set(4,cpu(18));
    body_0024f5c8();
    goto L_002503ac;
L_002503ac: ;
    /* 002503AC: move a0,s2 */ set(4,cpu(18));
L_002503b0: ;
    /* 002503B0: move a2,s3 */ set(6,cpu(19));
L_002503b4: ;
    /* 002503B4: addiu s3,s3,0xd */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x0000000d)));
L_002503b8: ;
    /* 002503B8: li a3,0xf */ set(7,UINT64_C(0x000000000000000f));
L_002503bc: ;
    /* 002503BC: move a1,s1 */ set(5,cpu(17));
L_002503c0: ;
    /* 002503C0: li t0,0x1e */ set(8,UINT64_C(0x000000000000001e));
L_002503c4: ;
    /* 002503C4: jal 0x002517e0; native delay follows */
    set(31,UINT64_C(0x00000000002503cc));
    /* 002503C8: move s6,zero */ set(22,cpu(0));
    nbActionSetTimeList(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_002503cc;
L_002503cc: ;
    /* 002503CC: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
L_002503d0: ;
    /* 002503D0: sw a3,0x24(sp) */ w32(ea(cpu(29),UINT32_C(0x00000024)),(uint32_t)cpu(7));
L_002503d4: ;
    /* 002503D4: sw zero,0x44(sp) */ w32(ea(cpu(29),UINT32_C(0x00000044)),(uint32_t)cpu(0));
L_002503d8: ;
    /* 002503D8: b 0x0025045c; native delay follows */
    { /* 002503DC: sw a3,0x48(sp) */ w32(ea(cpu(29),UINT32_C(0x00000048)),(uint32_t)cpu(7)); goto L_0025045c; }
L_002503e0: ;
    /* 002503E0: sw zero,0x2c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000002c)),(uint32_t)cpu(0));
L_002503e4: ;
    /* 002503E4: jal 0x002d4748; native delay follows */
    set(31,UINT64_C(0x00000000002503ec));
    /* 002503E8: addiu a0,a0,0x37c0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000037c0)));
    set(2,ps2LibcPrintf(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10),cpu(11)));
    goto L_002503ec;
L_002503ec: ;
    /* 002503EC: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_002503f0: ;
    /* 002503F0: sll a3,s1,0x4 */ set(7,sx(((uint32_t)cpu(17)<<4)));
L_002503f4: ;
    /* 002503F4: move a0,s3 */ set(4,cpu(19));
L_002503f8: ;
    /* 002503F8: lw v0,0x0(v1) */ set(2,sx(r32(ea(cpu(3),UINT32_C(0x00000000)))));
L_002503fc: ;
    /* 002503FC: subu a3,a3,s1 */ set(7,sx((uint32_t)cpu(7)-(uint32_t)cpu(17)));
L_00250400: ;
    /* 00250400: sll a3,a3,0x4 */ set(7,sx(((uint32_t)cpu(7)<<4)));
L_00250404: ;
    /* 00250404: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_00250408: ;
    /* 00250408: addu a3,v0,a3 */ set(7,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
L_0025040c: ;
    /* 0025040C: move a2,s2 */ set(6,cpu(18));
L_00250410: ;
    /* 00250410: jal 0x002628d0; native delay follows */
    set(31,UINT64_C(0x0000000000250418));
    /* 00250414: li t0,0x3 */ set(8,UINT64_C(0x0000000000000003));
    nbAddMojiEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00250418;
L_00250418: ;
    /* 00250418: move a0,s2 */ set(4,cpu(18));
L_0025041c: ;
    /* 0025041C: jal 0x0024f5c8; native delay follows */
    set(31,UINT64_C(0x0000000000250424));
    /* 00250420: move a1,s3 */ set(5,cpu(19));
    body_0024f5c8();
    goto L_00250424;
L_00250424: ;
    /* 00250424: b 0x00250dbc; native delay follows */
    { /* 00250428: lw a0,0x54(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000054))))); goto L_00250dbc; }
L_00250430: ;
    /* 00250430: move a0,s2 */ set(4,cpu(18));
L_00250434: ;
    /* 00250434: jal 0x0024f5c8; native delay follows */
    set(31,UINT64_C(0x000000000025043c));
    /* 00250438: move a1,s3 */ set(5,cpu(19));
    body_0024f5c8();
    goto L_0025043c;
L_0025043c: ;
    /* 0025043C: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_00250440: ;
    /* 00250440: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
L_00250444: ;
    /* 00250444: slti a0,s1,0x10 */ set(4,lt(cpu(17),UINT64_C(0x0000000000000010)));
L_00250448: ;
    /* 00250448: sw v0,0x24(sp) */ w32(ea(cpu(29),UINT32_C(0x00000024)),(uint32_t)cpu(2));
L_0025044c: ;
    /* 0025044C: move s6,zero */ set(22,cpu(0));
L_00250450: ;
    /* 00250450: sw zero,0x44(sp) */ w32(ea(cpu(29),UINT32_C(0x00000044)),(uint32_t)cpu(0));
L_00250454: ;
    /* 00250454: sw v1,0x30(sp) */ w32(ea(cpu(29),UINT32_C(0x00000030)),(uint32_t)cpu(3));
L_00250458: ;
    /* 00250458: sw a0,0x90(sp) */ w32(ea(cpu(29),UINT32_C(0x00000090)),(uint32_t)cpu(4));
L_0025045c: ;
    /* 0025045C: lw a1,0x90(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000090)))));
L_00250460: ;
    /* 00250460: beq a1,zero,0x002504a0; native delay follows */
    { int taken=(cpu(5)==cpu(0));
      /* 00250464: sll v0,s1,0x4 */ set(2,sx(((uint32_t)cpu(17)<<4)));
      if(taken) goto L_002504a0;
      goto L_00250468; }
L_00250468: ;
    /* 00250468: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_0025046c: ;
    /* 0025046C: subu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(17)));
L_00250470: ;
    /* 00250470: lw a3,0x24(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
L_00250474: ;
    /* 00250474: lw a0,0x0(v1) */ set(4,sx(r32(ea(cpu(3),UINT32_C(0x00000000)))));
L_00250478: ;
    /* 00250478: sll v0,v0,0x4 */ set(2,sx(((uint32_t)cpu(2)<<4)));
L_0025047c: ;
    /* 0025047C: lw a1,0x10(v1) */ set(5,sx(r32(ea(cpu(3),UINT32_C(0x00000010)))));
L_00250480: ;
    /* 00250480: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
L_00250484: ;
    /* 00250484: lh v1,0x90(v0) */ set(3,sx((uint32_t)i16(r16(ea(cpu(2),UINT32_C(0x00000090))))));
L_00250488: ;
    /* 00250488: sll v1,v1,0x7 */ set(3,sx(((uint32_t)cpu(3)<<7)));
L_0025048c: ;
    /* 0025048C: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
L_00250490: ;
    /* 00250490: lhu v0,0x0(v1) */ set(2,r16(ea(cpu(3),UINT32_C(0x00000000))));
L_00250494: ;
    /* 00250494: andi v0,v0,0x20 */ set(2,cpu(2)&UINT64_C(0x0000000000000020));
L_00250498: ;
    /* 00250498: movn a3,zero,v0 */ if(cpu(2)!=0) set(7,cpu(0));
L_0025049c: ;
    /* 0025049C: sw a3,0x24(sp) */ w32(ea(cpu(29),UINT32_C(0x00000024)),(uint32_t)cpu(7));
L_002504a0: ;
    /* 002504A0: move a0,s2 */ set(4,cpu(18));
L_002504a4: ;
    /* 002504A4: jal 0x00251750; native delay follows */
    set(31,UINT64_C(0x00000000002504ac));
    /* 002504A8: move a1,s1 */ set(5,cpu(17));
    body_00251750();
    goto L_002504ac;
L_002504ac: ;
    /* 002504AC: slt v0,s3,v0 */ set(2,lt(cpu(19),cpu(2)));
L_002504b0: ;
    /* 002504B0: beq v0,zero,0x002504cc; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002504B4: lw v1,0x20(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
      if(taken) goto L_002504cc;
      goto L_002504b8; }
L_002504b8: ;
    /* 002504B8: move a0,s2 */ set(4,cpu(18));
L_002504bc: ;
    /* 002504BC: jal 0x00251750; native delay follows */
    set(31,UINT64_C(0x00000000002504c4));
    /* 002504C0: move a1,s1 */ set(5,cpu(17));
    body_00251750();
    goto L_002504c4;
L_002504c4: ;
    /* 002504C4: move s3,v0 */ set(19,cpu(2));
L_002504c8: ;
    /* 002504C8: lw v1,0x20(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
L_002504cc: ;
    /* 002504CC: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_002504d0: ;
    /* 002504D0: bne v1,v0,0x002504f8; native delay follows */
    { int taken=(cpu(3)!=cpu(2));
      /* 002504D4: lw a1,0x24(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
      if(taken) goto L_002504f8;
      goto L_002504d8; }
L_002504d8: ;
    /* 002504D8: lw a0,0x30(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000030)))));
L_002504dc: ;
    /* 002504DC: lui v0,0x7 */ set(2,sx(UINT32_C(0x00070000)));
L_002504e0: ;
    /* 002504E0: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
L_002504e4: ;
    /* 002504E4: bne v0,zero,0x002504f8; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 002504E8: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_002504f8;
      goto L_002504ec; }
L_002504ec: ;
    /* 002504EC: jal 0x0024f420; native delay follows */
    set(31,UINT64_C(0x00000000002504f4));
    /* 002504F0: move a1,s3 */ set(5,cpu(19));
    body_0024f420();
    goto L_002504f4;
L_002504f4: ;
    /* 002504F4: lw a1,0x24(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
L_002504f8: ;
    /* 002504F8: blez a1,0x00250db8; native delay follows */
    { int taken=(!lt(0,cpu(5)));
      /* 002504FC: sw zero,0x28(sp) */ w32(ea(cpu(29),UINT32_C(0x00000028)),(uint32_t)cpu(0));
      if(taken) goto L_00250db8;
      goto L_00250500; }
L_00250500: ;
    /* 00250500: sll v0,s7,0x4 */ set(2,sx(((uint32_t)cpu(23)<<4)));
L_00250504: ;
    /* 00250504: lui a1,0x3d */ set(5,sx(UINT32_C(0x003d0000)));
L_00250508: ;
    /* 00250508: subu v0,v0,s7 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(23)));
L_0025050c: ;
    /* 0025050C: addiu a1,a1,0x7998 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00007998)));
L_00250510: ;
    /* 00250510: sll v0,v0,0x2 */ set(2,sx(((uint32_t)cpu(2)<<2)));
L_00250514: ;
    /* 00250514: lw a3,0x24(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
L_00250518: ;
    /* 00250518: addu a0,v0,a1 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
L_0025051c: ;
    /* 0025051C: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
L_00250520: ;
    /* 00250520: addiu a0,a0,0x28 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000028)));
L_00250524: ;
    /* 00250524: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
L_00250528: ;
    /* 00250528: sw a0,0x88(sp) */ w32(ea(cpu(29),UINT32_C(0x00000088)),(uint32_t)cpu(4));
L_0025052c: ;
    /* 0025052C: sw a3,0x8c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000008c)),(uint32_t)cpu(7));
L_00250530: ;
    /* 00250530: sw v0,0x80(sp) */ w32(ea(cpu(29),UINT32_C(0x00000080)),(uint32_t)cpu(2));
L_00250534: ;
    /* 00250534: nop  */ ;
L_00250538: ;
    /* 00250538: li v0,0x800 */ set(2,UINT64_C(0x0000000000000800));
L_0025053c: ;
    /* 0025053C: bne s6,v0,0x00250560; native delay follows */
    { int taken=(cpu(22)!=cpu(2));
      /* 00250540: sw zero,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(0));
      if(taken) goto L_00250560;
      goto L_00250544; }
L_00250544: ;
    /* 00250544: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_00250548: ;
    /* 00250548: move a0,s7 */ set(4,cpu(23));
L_0025054c: ;
    /* 0025054C: move a1,s8 */ set(5,cpu(30));
L_00250550: ;
    /* 00250550: move a2,s1 */ set(6,cpu(17));
L_00250554: ;
    /* 00250554: jal 0x00267388; native delay follows */
    set(31,UINT64_C(0x000000000025055c));
    /* 00250558: sw v0,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(2));
    set(2,ps2CombatDeadType_00267388());
    goto L_0025055c;
L_0025055c: ;
    /* 0025055C: sw v0,0x6c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000006c)),(uint32_t)cpu(2));
L_00250560: ;
    /* 00250560: lw t0,0x24(sp) */ set(8,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
L_00250564: ;
    /* 00250564: li a0,0x1 */ set(4,UINT64_C(0x0000000000000001));
L_00250568: ;
    /* 00250568: move a1,s7 */ set(5,cpu(23));
L_0025056c: ;
    /* 0025056C: move a2,s8 */ set(6,cpu(30));
L_00250570: ;
    /* 00250570: move a3,s1 */ set(7,cpu(17));
L_00250574: ;
    /* 00250574: jal 0x00266350; native delay follows */
    set(31,UINT64_C(0x000000000025057c));
    /* 00250578: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    set(2,nbGetKoukaHp(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_0025057c;
L_0025057c: ;
    /* 0025057C: move a0,zero */ set(4,cpu(0));
L_00250580: ;
    /* 00250580: lw t0,0x24(sp) */ set(8,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
L_00250584: ;
    /* 00250584: move a1,s7 */ set(5,cpu(23));
L_00250588: ;
    /* 00250588: move a2,s8 */ set(6,cpu(30));
L_0025058c: ;
    /* 0025058C: move a3,s1 */ set(7,cpu(17));
L_00250590: ;
    /* 00250590: mov.S f12,f20 */ fpr()[12]=fpr()[20];
L_00250594: ;
    /* 00250594: jal 0x00266350; native delay follows */
    set(31,UINT64_C(0x000000000025059c));
    /* 00250598: move s0,v0 */ set(16,cpu(2));
    set(2,nbGetKoukaHp(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_0025059c;
L_0025059c: ;
    /* 0025059C: sw v0,0x34(sp) */ w32(ea(cpu(29),UINT32_C(0x00000034)),(uint32_t)cpu(2));
L_002505a0: ;
    /* 002505A0: li v0,0x4000 */ set(2,UINT64_C(0x0000000000004000));
L_002505a4: ;
    /* 002505A4: bnel s6,v0,0x002505e8; native delay follows */
    { int taken=(cpu(22)!=cpu(2));
      if(taken) { /* 002505A8: li v0,0x2000 */ set(2,UINT64_C(0x0000000000002000)); goto L_002505e8; }
      goto L_002505ac; }
L_002505ac: ;
    /* 002505AC: move a0,s1 */ set(4,cpu(17));
L_002505b0: ;
    /* 002505B0: jal 0x00246ab8; native delay follows */
    set(31,UINT64_C(0x00000000002505b8));
    /* 002505B4: move s6,zero */ set(22,cpu(0));
    set(2,nbGetUnitWorkFromFormindex(cpu(4)));
    goto L_002505b8;
L_002505b8: ;
    /* 002505B8: li a0,0xa */ set(4,UINT64_C(0x000000000000000a));
L_002505bc: ;
    /* 002505BC: lhu v1,0x6(v0) */ set(3,r16(ea(cpu(2),UINT32_C(0x00000006))));
L_002505c0: ;
    /* 002505C0: beql a0,zero,0x002505c8; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      if(taken) { /* 002505C4: break 0x7 */ nocturneCompilerArithmeticTrap(7); goto L_002505c8; }
      goto L_002505c8; }
L_002505c8: ;
    /* 002505C8: divu v1,a0 */ lo=divu((uint32_t)cpu(3),(uint32_t)cpu(4));
L_002505cc: ;
    /* 002505CC: addiu a1,v1,-0x1 */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
L_002505d0: ;
    /* 002505D0: mflo a0 */ set(4,sx(lo));
L_002505d4: ;
    /* 002505D4: subu s0,v1,a0 */ set(16,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
L_002505d8: ;
    /* 002505D8: slt v1,s0,v1 */ set(3,lt(cpu(16),cpu(3)));
L_002505dc: ;
    /* 002505DC: b 0x00250614; native delay follows */
    { /* 002505E0: movz s0,a1,v1 */ if(cpu(3)==0) set(16,cpu(5)); goto L_00250614; }
L_002505e8: ;
    /* 002505E8: bnel s6,v0,0x00250620; native delay follows */
    { int taken=(cpu(22)!=cpu(2));
      if(taken) { /* 002505EC: li v0,0x1000 */ set(2,UINT64_C(0x0000000000001000)); goto L_00250620; }
      goto L_002505f0; }
L_002505f0: ;
    /* 002505F0: move a0,s1 */ set(4,cpu(17));
L_002505f4: ;
    /* 002505F4: jal 0x00246ab8; native delay follows */
    set(31,UINT64_C(0x00000000002505fc));
    /* 002505F8: move s6,zero */ set(22,cpu(0));
    set(2,nbGetUnitWorkFromFormindex(cpu(4)));
    goto L_002505fc;
L_002505fc: ;
    /* 002505FC: lhu v1,0x6(v0) */ set(3,r16(ea(cpu(2),UINT32_C(0x00000006))));
L_00250600: ;
    /* 00250600: srl v0,v1,0x2 */ set(2,sx(((uint32_t)cpu(3)>>2)));
L_00250604: ;
    /* 00250604: addiu a0,v1,-0x1 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
L_00250608: ;
    /* 00250608: subu s0,v1,v0 */ set(16,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
L_0025060c: ;
    /* 0025060C: slt v1,s0,v1 */ set(3,lt(cpu(16),cpu(3)));
L_00250610: ;
    /* 00250610: movz s0,a0,v1 */ if(cpu(3)==0) set(16,cpu(4));
L_00250614: ;
    /* 00250614: slti v0,s0,0x0 */ set(2,lt(cpu(16),UINT64_C(0x0000000000000000)));
L_00250618: ;
    /* 00250618: b 0x0025063c; native delay follows */
    { /* 0025061C: movn s0,zero,v0 */ if(cpu(2)!=0) set(16,cpu(0)); goto L_0025063c; }
L_00250620: ;
    /* 00250620: bne s6,v0,0x00250640; native delay follows */
    { int taken=(cpu(22)!=cpu(2));
      /* 00250624: lw a2,0x34(sp) */ set(6,sx(r32(ea(cpu(29),UINT32_C(0x00000034)))));
      if(taken) goto L_00250640;
      goto L_00250628; }
L_00250628: ;
    /* 00250628: move a0,s1 */ set(4,cpu(17));
L_0025062c: ;
    /* 0025062C: jal 0x00246ab8; native delay follows */
    set(31,UINT64_C(0x0000000000250634));
    /* 00250630: move s6,zero */ set(22,cpu(0));
    set(2,nbGetUnitWorkFromFormindex(cpu(4)));
    goto L_00250634;
L_00250634: ;
    /* 00250634: lhu v1,0x6(v0) */ set(3,r16(ea(cpu(2),UINT32_C(0x00000006))));
L_00250638: ;
    /* 00250638: srl s0,v1,0x1 */ set(16,sx(((uint32_t)cpu(3)>>1)));
L_0025063c: ;
    /* 0025063C: lw a2,0x34(sp) */ set(6,sx(r32(ea(cpu(29),UINT32_C(0x00000034)))));
L_00250640: ;
    /* 00250640: lui v0,0x54 */ set(2,sx(UINT32_C(0x00540000)));
L_00250644: ;
    /* 00250644: addiu a0,v0,0x3780 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00003780)));
L_00250648: ;
    /* 00250648: jal 0x002d4748; native delay follows */
    set(31,UINT64_C(0x0000000000250650));
    /* 0025064C: move a1,s0 */ set(5,cpu(16));
    set(2,ps2LibcPrintf(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10),cpu(11)));
    goto L_00250650;
L_00250650: ;
    /* 00250650: li a0,0x1 */ set(4,UINT64_C(0x0000000000000001));
L_00250654: ;
    /* 00250654: lw t0,0x24(sp) */ set(8,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
L_00250658: ;
    /* 00250658: move a1,s7 */ set(5,cpu(23));
L_0025065c: ;
    /* 0025065C: move a2,s8 */ set(6,cpu(30));
L_00250660: ;
    /* 00250660: move a3,s1 */ set(7,cpu(17));
L_00250664: ;
    /* 00250664: jal 0x00266878; native delay follows */
    set(31,UINT64_C(0x000000000025066c));
    /* 00250668: mov.S f12,f20 */ fpr()[12]=fpr()[20];
    set(2,nbGetKoukaMp(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_0025066c;
L_0025066c: ;
    /* 0025066C: move a0,zero */ set(4,cpu(0));
L_00250670: ;
    /* 00250670: lw t0,0x24(sp) */ set(8,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
L_00250674: ;
    /* 00250674: move a1,s7 */ set(5,cpu(23));
L_00250678: ;
    /* 00250678: move a2,s8 */ set(6,cpu(30));
L_0025067c: ;
    /* 0025067C: move a3,s1 */ set(7,cpu(17));
L_00250680: ;
    /* 00250680: mov.S f12,f20 */ fpr()[12]=fpr()[20];
L_00250684: ;
    /* 00250684: jal 0x00266878; native delay follows */
    set(31,UINT64_C(0x000000000025068c));
    /* 00250688: move s4,v0 */ set(20,cpu(2));
    set(2,nbGetKoukaMp(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_0025068c;
L_0025068c: ;
    /* 0025068C: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
L_00250690: ;
    /* 00250690: addiu a0,v1,0x37a0 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x000037a0)));
L_00250694: ;
    /* 00250694: move a1,s4 */ set(5,cpu(20));
L_00250698: ;
    /* 00250698: move a2,v0 */ set(6,cpu(2));
L_0025069c: ;
    /* 0025069C: jal 0x002d4748; native delay follows */
    set(31,UINT64_C(0x00000000002506a4));
    /* 002506A0: sw v0,0x38(sp) */ w32(ea(cpu(29),UINT32_C(0x00000038)),(uint32_t)cpu(2));
    set(2,ps2LibcPrintf(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10),cpu(11)));
    goto L_002506a4;
L_002506a4: ;
    /* 002506A4: lw a0,0x48(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000048)))));
L_002506a8: ;
    /* 002506A8: beql a0,zero,0x002506fc; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      if(taken) { /* 002506AC: lw a0,0x30(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000030))))); goto L_002506fc; }
      goto L_002506b0; }
L_002506b0: ;
    /* 002506B0: bltz s0,0x002506c8; native delay follows */
    { int taken=(lt(cpu(16),0));
      /* 002506B4: lw a1,0x34(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000034)))));
      if(taken) goto L_002506c8;
      goto L_002506b8; }
L_002506b8: ;
    /* 002506B8: slti v1,a1,0x0 */ set(3,lt(cpu(5),UINT64_C(0x0000000000000000)));
L_002506bc: ;
    /* 002506BC: addu v0,a1,s0 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(16)));
L_002506c0: ;
    /* 002506C0: movz s0,v0,v1 */ if(cpu(3)==0) set(16,cpu(2));
L_002506c4: ;
    /* 002506C4: sw s0,0x34(sp) */ w32(ea(cpu(29),UINT32_C(0x00000034)),(uint32_t)cpu(16));
L_002506c8: ;
    /* 002506C8: bltz s4,0x002506e4; native delay follows */
    { int taken=(lt(cpu(20),0));
      /* 002506CC: li s0,-0x1 */ set(16,UINT64_C(0xffffffffffffffff));
      if(taken) goto L_002506e4;
      goto L_002506d0; }
L_002506d0: ;
    /* 002506D0: lw a3,0x38(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000038)))));
L_002506d4: ;
    /* 002506D4: slti v1,a3,0x0 */ set(3,lt(cpu(7),UINT64_C(0x0000000000000000)));
L_002506d8: ;
    /* 002506D8: addu v0,a3,s4 */ set(2,sx((uint32_t)cpu(7)+(uint32_t)cpu(20)));
L_002506dc: ;
    /* 002506DC: movz s4,v0,v1 */ if(cpu(3)==0) set(20,cpu(2));
L_002506e0: ;
    /* 002506E0: sw s4,0x38(sp) */ w32(ea(cpu(29),UINT32_C(0x00000038)),(uint32_t)cpu(20));
L_002506e4: ;
    /* 002506E4: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_002506e8: ;
    /* 002506E8: li s4,-0x1 */ set(20,UINT64_C(0xffffffffffffffff));
L_002506ec: ;
    /* 002506EC: move v1,v0 */ set(3,cpu(2));
L_002506f0: ;
    /* 002506F0: movn v0,zero,v1 */ if(cpu(3)!=0) set(2,cpu(0));
L_002506f4: ;
    /* 002506F4: sw v0,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(2));
L_002506f8: ;
    /* 002506F8: lw a0,0x30(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000030)))));
L_002506fc: ;
    /* 002506FC: lui v0,0x1 */ set(2,sx(UINT32_C(0x00010000)));
L_00250700: ;
    /* 00250700: bne a0,v0,0x0025075c; native delay follows */
    { int taken=(cpu(4)!=cpu(2));
      /* 00250704: sw zero,0x74(sp) */ w32(ea(cpu(29),UINT32_C(0x00000074)),(uint32_t)cpu(0));
      if(taken) goto L_0025075c;
      goto L_00250708; }
L_00250708: ;
    /* 00250708: lw a1,0x90(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000090)))));
L_0025070c: ;
    /* 0025070C: beq a1,zero,0x00250744; native delay follows */
    { int taken=(cpu(5)==cpu(0));
      /* 00250710: sll a3,s1,0x4 */ set(7,sx(((uint32_t)cpu(17)<<4)));
      if(taken) goto L_00250744;
      goto L_00250714; }
L_00250714: ;
    /* 00250714: lw v0,0x0(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_00250718: ;
    /* 00250718: subu a3,a3,s1 */ set(7,sx((uint32_t)cpu(7)-(uint32_t)cpu(17)));
L_0025071c: ;
    /* 0025071C: move a0,s3 */ set(4,cpu(19));
L_00250720: ;
    /* 00250720: lw v1,0x0(v0) */ set(3,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_00250724: ;
    /* 00250724: sll a3,a3,0x4 */ set(7,sx(((uint32_t)cpu(7)<<4)));
L_00250728: ;
    /* 00250728: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_0025072c: ;
    /* 0025072C: move a2,s2 */ set(6,cpu(18));
L_00250730: ;
    /* 00250730: addu a3,v1,a3 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
L_00250734: ;
    /* 00250734: jal 0x002628d0; native delay follows */
    set(31,UINT64_C(0x000000000025073c));
    /* 00250738: li t0,0x4 */ set(8,UINT64_C(0x0000000000000004));
    nbAddMojiEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_0025073c;
L_0025073c: ;
    /* 0025073C: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
L_00250740: ;
    /* 00250740: sw a3,0x74(sp) */ w32(ea(cpu(29),UINT32_C(0x00000074)),(uint32_t)cpu(7));
L_00250744: ;
    /* 00250744: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250748: ;
    /* 00250748: li s0,-0x1 */ set(16,UINT64_C(0xffffffffffffffff));
L_0025074c: ;
    /* 0025074C: li s4,-0x1 */ set(20,UINT64_C(0xffffffffffffffff));
L_00250750: ;
    /* 00250750: move v1,v0 */ set(3,cpu(2));
L_00250754: ;
    /* 00250754: movn v0,zero,v1 */ if(cpu(3)!=0) set(2,cpu(0));
L_00250758: ;
    /* 00250758: sw v0,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(2));
L_0025075c: ;
    /* 0025075C: move a0,s7 */ set(4,cpu(23));
L_00250760: ;
    /* 00250760: move a1,s8 */ set(5,cpu(30));
L_00250764: ;
    /* 00250764: move a2,s1 */ set(6,cpu(17));
L_00250768: ;
    /* 00250768: jal 0x00267370; native delay follows */
    set(31,UINT64_C(0x0000000000250770));
    /* 0025076C: sw zero,0x40(sp) */ w32(ea(cpu(29),UINT32_C(0x00000040)),(uint32_t)cpu(0));
    set(2,ps2CombatCheckHitEffect_00267370(cpu(4)));
    goto L_00250770;
L_00250770: ;
    /* 00250770: lw a0,0x28(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000028)))));
L_00250774: ;
    /* 00250774: lw a1,0x8c(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x0000008c)))));
L_00250778: ;
    /* 00250778: bne a0,a1,0x00250798; native delay follows */
    { int taken=(cpu(4)!=cpu(5));
      /* 0025077C: sw v0,0x64(sp) */ w32(ea(cpu(29),UINT32_C(0x00000064)),(uint32_t)cpu(2));
      if(taken) goto L_00250798;
      goto L_00250780; }
L_00250780: ;
    /* 00250780: beq s6,zero,0x00250798; native delay follows */
    { int taken=(cpu(22)==cpu(0));
      /* 00250784: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
      if(taken) goto L_00250798;
      goto L_00250788; }
L_00250788: ;
    /* 00250788: sw s6,0x70(sp) */ w32(ea(cpu(29),UINT32_C(0x00000070)),(uint32_t)cpu(22));
L_0025078c: ;
    /* 0025078C: b 0x002507b0; native delay follows */
    { /* 00250790: sw a3,0x40(sp) */ w32(ea(cpu(29),UINT32_C(0x00000040)),(uint32_t)cpu(7)); goto L_002507b0; }
L_00250798: ;
    /* 00250798: bgez s0,0x002507a8; native delay follows */
    { int taken=(!lt(cpu(16),0));
      /* 0025079C: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
      if(taken) goto L_002507a8;
      goto L_002507a0; }
L_002507a0: ;
    /* 002507A0: bltz s4,0x002507b4; native delay follows */
    { int taken=(lt(cpu(20),0));
      /* 002507A4: lw v1,0x68(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
      if(taken) goto L_002507b4;
      goto L_002507a8; }
L_002507a8: ;
    /* 002507A8: sw zero,0x70(sp) */ w32(ea(cpu(29),UINT32_C(0x00000070)),(uint32_t)cpu(0));
L_002507ac: ;
    /* 002507AC: sw v0,0x40(sp) */ w32(ea(cpu(29),UINT32_C(0x00000040)),(uint32_t)cpu(2));
L_002507b0: ;
    /* 002507B0: lw v1,0x68(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_002507b4: ;
    /* 002507B4: beq v1,zero,0x002507c4; native delay follows */
    { int taken=(cpu(3)==cpu(0));
      /* 002507B8: li a0,0x1 */ set(4,UINT64_C(0x0000000000000001));
      if(taken) goto L_002507c4;
      goto L_002507bc; }
L_002507bc: ;
    /* 002507BC: sw zero,0x70(sp) */ w32(ea(cpu(29),UINT32_C(0x00000070)),(uint32_t)cpu(0));
L_002507c0: ;
    /* 002507C0: sw a0,0x40(sp) */ w32(ea(cpu(29),UINT32_C(0x00000040)),(uint32_t)cpu(4));
L_002507c4: ;
    /* 002507C4: lw a1,0x40(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000040)))));
L_002507c8: ;
    /* 002507C8: beq a1,zero,0x00250cf8; native delay follows */
    { int taken=(cpu(5)==cpu(0));
      /* 002507CC: lw a3,0x20(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
      if(taken) goto L_00250cf8;
      goto L_002507d0; }
L_002507d0: ;
    /* 002507D0: bne a3,zero,0x002507f4; native delay follows */
    { int taken=(cpu(7)!=cpu(0));
      /* 002507D4: lw a1,0x68(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
      if(taken) goto L_002507f4;
      goto L_002507d8; }
L_002507d8: ;
    /* 002507D8: lw v0,0x80(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000080)))));
L_002507dc: ;
    /* 002507DC: lw a0,0x78(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000078)))));
L_002507e0: ;
    /* 002507E0: lbu v1,0x2(v0) */ set(3,r8(ea(cpu(2),UINT32_C(0x00000002))));
L_002507e4: ;
    /* 002507E4: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_002507e8: ;
    /* 002507E8: movz a0,v0,v1 */ if(cpu(3)==0) set(4,cpu(2));
L_002507ec: ;
    /* 002507EC: sw a0,0x78(sp) */ w32(ea(cpu(29),UINT32_C(0x00000078)),(uint32_t)cpu(4));
L_002507f0: ;
    /* 002507F0: lw a1,0x68(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_002507f4: ;
    /* 002507F4: beq a1,zero,0x00250868; native delay follows */
    { int taken=(cpu(5)==cpu(0));
      /* 002507F8: nop  */ ;
      if(taken) goto L_00250868;
      goto L_002507fc; }
L_002507fc: ;
    /* 002507FC: jal 0x0026a338; native delay follows */
    set(31,UINT64_C(0x0000000000250804));
    /* 00250800: move a0,s1 */ set(4,cpu(17));
    set(2,nbCheckKuisibari2Skill(cpu(4)));
    goto L_00250804;
L_00250804: ;
    /* 00250804: beq v0,zero,0x00250838; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250808: lw a3,0x70(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000070)))));
      if(taken) goto L_00250838;
      goto L_0025080c; }
L_0025080c: ;
    /* 0025080C: move a0,s2 */ set(4,cpu(18));
L_00250810: ;
    /* 00250810: move a1,s1 */ set(5,cpu(17));
L_00250814: ;
    /* 00250814: sw zero,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(0));
L_00250818: ;
    /* 00250818: xori v0,a3,0x800 */ set(2,cpu(7)^UINT64_C(0x0000000000000800));
L_0025081c: ;
    /* 0025081C: movz a3,zero,v0 */ if(cpu(2)==0) set(7,cpu(0));
L_00250820: ;
    /* 00250820: jal 0x002515d8; native delay follows */
    set(31,UINT64_C(0x0000000000250828));
    /* 00250824: sw a3,0x70(sp) */ w32(ea(cpu(29),UINT32_C(0x00000070)),(uint32_t)cpu(7));
    set(2,nbActionGetTimeListHp(cpu(4),cpu(5)));
    goto L_00250828;
L_00250828: ;
    /* 00250828: move a0,s3 */ set(4,cpu(19));
L_0025082c: ;
    /* 0025082C: move a1,s2 */ set(5,cpu(18));
L_00250830: ;
    /* 00250830: b 0x002508ac; native delay follows */
    { /* 00250834: li a2,0x168 */ set(6,UINT64_C(0x0000000000000168)); goto L_002508ac; }
L_00250838: ;
    /* 00250838: jal 0x0026a2d8; native delay follows */
    set(31,UINT64_C(0x0000000000250840));
    /* 0025083C: move a0,s1 */ set(4,cpu(17));
    set(2,nbCheckKuisibariSkill(cpu(4)));
    goto L_00250840;
L_00250840: ;
    /* 00250840: beq v0,zero,0x002508ec; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250844: lw v1,0x70(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000070)))));
      if(taken) goto L_002508ec;
      goto L_00250848; }
L_00250848: ;
    /* 00250848: move a0,s2 */ set(4,cpu(18));
L_0025084c: ;
    /* 0025084C: move a1,s1 */ set(5,cpu(17));
L_00250850: ;
    /* 00250850: sw zero,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(0));
L_00250854: ;
    /* 00250854: xori v0,v1,0x800 */ set(2,cpu(3)^UINT64_C(0x0000000000000800));
L_00250858: ;
    /* 00250858: movz v1,zero,v0 */ if(cpu(2)==0) set(3,cpu(0));
L_0025085c: ;
    /* 0025085C: b 0x00250898; native delay follows */
    { /* 00250860: sw v1,0x70(sp) */ w32(ea(cpu(29),UINT32_C(0x00000070)),(uint32_t)cpu(3)); goto L_00250898; }
L_00250868: ;
    /* 00250868: blez s0,0x002509e4; native delay follows */
    { int taken=(!lt(0,cpu(16)));
      /* 0025086C: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_002509e4;
      goto L_00250870; }
L_00250870: ;
    /* 00250870: jal 0x002515d8; native delay follows */
    set(31,UINT64_C(0x0000000000250878));
    /* 00250874: move a1,s1 */ set(5,cpu(17));
    set(2,nbActionGetTimeListHp(cpu(4),cpu(5)));
    goto L_00250878;
L_00250878: ;
    /* 00250878: slt v0,s0,v0 */ set(2,lt(cpu(16),cpu(2)));
L_0025087c: ;
    /* 0025087C: bne v0,zero,0x002508ec; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250880: nop  */ ;
      if(taken) goto L_002508ec;
      goto L_00250884; }
L_00250884: ;
    /* 00250884: jal 0x0026a2d8; native delay follows */
    set(31,UINT64_C(0x000000000025088c));
    /* 00250888: move a0,s1 */ set(4,cpu(17));
    set(2,nbCheckKuisibariSkill(cpu(4)));
    goto L_0025088c;
L_0025088c: ;
    /* 0025088C: beq v0,zero,0x002508c0; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250890: move a1,s1 */ set(5,cpu(17));
      if(taken) goto L_002508c0;
      goto L_00250894; }
L_00250894: ;
    /* 00250894: move a0,s2 */ set(4,cpu(18));
L_00250898: ;
    /* 00250898: jal 0x002515d8; native delay follows */
    set(31,UINT64_C(0x00000000002508a0));
    /* 0025089C: nop  */ ;
    set(2,nbActionGetTimeListHp(cpu(4),cpu(5)));
    goto L_002508a0;
L_002508a0: ;
    /* 002508A0: move a0,s3 */ set(4,cpu(19));
L_002508a4: ;
    /* 002508A4: move a1,s2 */ set(5,cpu(18));
L_002508a8: ;
    /* 002508A8: li a2,0x159 */ set(6,UINT64_C(0x0000000000000159));
L_002508ac: ;
    /* 002508AC: jal 0x00262f58; native delay follows */
    set(31,UINT64_C(0x00000000002508b4));
    /* 002508B0: addiu s0,v0,-0x1 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
    set(2,nbAddSkillNamePacket(cpu(4),cpu(5),cpu(6)));
    goto L_002508b4;
L_002508b4: ;
    /* 002508B4: b 0x002508ec; native delay follows */
    { /* 002508B8: nop  */ ; goto L_002508ec; }
L_002508c0: ;
    /* 002508C0: jal 0x0026a338; native delay follows */
    set(31,UINT64_C(0x00000000002508c8));
    /* 002508C4: move a0,s1 */ set(4,cpu(17));
    set(2,nbCheckKuisibari2Skill(cpu(4)));
    goto L_002508c8;
L_002508c8: ;
    /* 002508C8: beq v0,zero,0x002508ec; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002508CC: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_002508ec;
      goto L_002508d0; }
L_002508d0: ;
    /* 002508D0: jal 0x002515d8; native delay follows */
    set(31,UINT64_C(0x00000000002508d8));
    /* 002508D4: move a1,s1 */ set(5,cpu(17));
    set(2,nbActionGetTimeListHp(cpu(4),cpu(5)));
    goto L_002508d8;
L_002508d8: ;
    /* 002508D8: move a0,s3 */ set(4,cpu(19));
L_002508dc: ;
    /* 002508DC: move a1,s2 */ set(5,cpu(18));
L_002508e0: ;
    /* 002508E0: li a2,0x168 */ set(6,UINT64_C(0x0000000000000168));
L_002508e4: ;
    /* 002508E4: jal 0x00262f58; native delay follows */
    set(31,UINT64_C(0x00000000002508ec));
    /* 002508E8: addiu s0,v0,-0x1 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
    set(2,nbAddSkillNamePacket(cpu(4),cpu(5),cpu(6)));
    goto L_002508ec;
L_002508ec: ;
    /* 002508EC: blez s0,0x002509e4; native delay follows */
    { int taken=(!lt(0,cpu(16)));
      /* 002508F0: lw a0,0x44(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000044)))));
      if(taken) goto L_002509e4;
      goto L_002508f4; }
L_002508f4: ;
    /* 002508F4: beq a0,zero,0x0025092c; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      /* 002508F8: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_0025092c;
      goto L_002508fc; }
L_002508fc: ;
    /* 002508FC: jal 0x002515d8; native delay follows */
    set(31,UINT64_C(0x0000000000250904));
    /* 00250900: move a1,s1 */ set(5,cpu(17));
    set(2,nbActionGetTimeListHp(cpu(4),cpu(5)));
    goto L_00250904;
L_00250904: ;
    /* 00250904: slt v0,v0,s0 */ set(2,lt(cpu(2),cpu(16)));
L_00250908: ;
    /* 00250908: beq v0,zero,0x00250920; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 0025090C: move v1,s0 */ set(3,cpu(16));
      if(taken) goto L_00250920;
      goto L_00250910; }
L_00250910: ;
    /* 00250910: move a0,s2 */ set(4,cpu(18));
L_00250914: ;
    /* 00250914: jal 0x002515d8; native delay follows */
    set(31,UINT64_C(0x000000000025091c));
    /* 00250918: move a1,s1 */ set(5,cpu(17));
    set(2,nbActionGetTimeListHp(cpu(4),cpu(5)));
    goto L_0025091c;
L_0025091c: ;
    /* 0025091C: move v1,v0 */ set(3,cpu(2));
L_00250920: ;
    /* 00250920: lw a1,0x54(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000054)))));
L_00250924: ;
    /* 00250924: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
L_00250928: ;
    /* 00250928: sw a1,0x54(sp) */ w32(ea(cpu(29),UINT32_C(0x00000054)),(uint32_t)cpu(5));
L_0025092c: ;
    /* 0025092C: move a0,s7 */ set(4,cpu(23));
L_00250930: ;
    /* 00250930: move a1,s8 */ set(5,cpu(30));
L_00250934: ;
    /* 00250934: jal 0x00266c90; native delay follows */
    set(31,UINT64_C(0x000000000025093c));
    /* 00250938: move a2,s1 */ set(6,cpu(17));
    fpr()[0]=fbits(ps2CombatHpDrainRate_00266C90(cpu(4)));
    goto L_0025093c;
L_0025093c: ;
    /* 0025093C: mov.S f1,f0 */ fpr()[1]=fpr()[0];
L_00250940: ;
    /* 00250940: clear f0 */ fpr()[0]=0;
L_00250944: ;
    /* 00250944: c.lt.S f0,f1 */ condition=EE_FPU_COMPARE_S(fpr()[0],fpr()[1],1)!=0;
L_00250948: ;
    /* 00250948: bc1f 0x00250970; native delay follows */
    { int taken=(!condition);
      /* 0025094C: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_00250970;
      goto L_00250950; }
L_00250950: ;
    /* 00250950: mtc1 s0,f0 */ fpr()[0]=(uint32_t)cpu(16);
L_00250954: ;
    /* 00250954: cvt.s.W f0,f0 */ fpr()[0]=EE_FPU_CVT_S_W(fpr()[0]);
L_00250958: ;
    /* 00250958: lw v1,0x4c(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x0000004c)))));
L_0025095c: ;
    /* 0025095C: mul.S f0,f0,f1 */ fpr()[0]=EE_FPU_MUL_S(fpr()[0],fpr()[1]);
L_00250960: ;
    /* 00250960: cvt.w.S f1,f0 */ fpr()[1]=EE_FPU_CVT_W_S(fpr()[0]);
L_00250964: ;
    /* 00250964: mfc1 v0,f1 */ set(2,sx(fpr()[1]));
L_00250968: ;
    /* 00250968: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
L_0025096c: ;
    /* 0025096C: sw v1,0x4c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000004c)),(uint32_t)cpu(3));
L_00250970: ;
    /* 00250970: move a1,s1 */ set(5,cpu(17));
L_00250974: ;
    /* 00250974: jal 0x002516e8; native delay follows */
    set(31,UINT64_C(0x000000000025097c));
    /* 00250978: subu a2,zero,s0 */ set(6,sx((uint32_t)cpu(0)-(uint32_t)cpu(16)));
    set(2,nbActionAddTimeListHp(cpu(4),cpu(5),cpu(6)));
    goto L_0025097c;
L_0025097c: ;
    /* 0025097C: move a0,s2 */ set(4,cpu(18));
L_00250980: ;
    /* 00250980: jal 0x002515e8; native delay follows */
    set(31,UINT64_C(0x0000000000250988));
    /* 00250984: move a1,s1 */ set(5,cpu(17));
    set(2,nbActionCheckTimeListDead(cpu(4),cpu(5)));
    goto L_00250988;
L_00250988: ;
    /* 00250988: beq v0,zero,0x002509c8; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 0025098C: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
      if(taken) goto L_002509c8;
      goto L_00250990; }
L_00250990: ;
    /* 00250990: move a1,s8 */ set(5,cpu(30));
L_00250994: ;
    /* 00250994: move a2,s1 */ set(6,cpu(17));
L_00250998: ;
    /* 00250998: move a0,s7 */ set(4,cpu(23));
L_0025099c: ;
    /* 0025099C: jal 0x00267388; native delay follows */
    set(31,UINT64_C(0x00000000002509a4));
    /* 002509A0: sw a3,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(7));
    set(2,ps2CombatDeadType_00267388());
    goto L_002509a4;
L_002509a4: ;
    /* 002509A4: move a0,s1 */ set(4,cpu(17));
L_002509a8: ;
    /* 002509A8: jal 0x00267788; native delay follows */
    set(31,UINT64_C(0x00000000002509b0));
    /* 002509AC: sw v0,0x6c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000006c)),(uint32_t)cpu(2));
    set(2,nbGetBadStat(cpu(4)));
    goto L_002509b0;
L_002509b0: ;
    /* 002509B0: li v1,0x400 */ set(3,UINT64_C(0x0000000000000400));
L_002509b4: ;
    /* 002509B4: bne v0,v1,0x002509e4; native delay follows */
    { int taken=(cpu(2)!=cpu(3));
      /* 002509B8: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
      if(taken) goto L_002509e4;
      goto L_002509bc; }
L_002509bc: ;
    /* 002509BC: b 0x002509e4; native delay follows */
    { /* 002509C0: sw v0,0x6c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000006c)),(uint32_t)cpu(2)); goto L_002509e4; }
L_002509c8: ;
    /* 002509C8: move a0,s7 */ set(4,cpu(23));
L_002509cc: ;
    /* 002509CC: jal 0x00267390; native delay follows */
    set(31,UINT64_C(0x00000000002509d4));
    /* 002509D0: move a1,s1 */ set(5,cpu(17));
    set(2,ps2CombatCheckStoneDeath_00267390(cpu(4),cpu(5)));
    goto L_002509d4;
L_002509d4: ;
    /* 002509D4: beq v0,zero,0x002509e4; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002509D8: li v1,0x1 */ set(3,UINT64_C(0x0000000000000001));
      if(taken) goto L_002509e4;
      goto L_002509dc; }
L_002509dc: ;
    /* 002509DC: sw v1,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(3));
L_002509e0: ;
    /* 002509E0: sw v1,0x6c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000006c)),(uint32_t)cpu(3));
L_002509e4: ;
    /* 002509E4: blez s4,0x00250a4c; native delay follows */
    { int taken=(!lt(0,cpu(20)));
      /* 002509E8: sll a3,s1,0x4 */ set(7,sx(((uint32_t)cpu(17)<<4)));
      if(taken) goto L_00250a4c;
      goto L_002509ec; }
L_002509ec: ;
    /* 002509EC: lw a0,0x58(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000058)))));
L_002509f0: ;
    /* 002509F0: move a2,s1 */ set(6,cpu(17));
L_002509f4: ;
    /* 002509F4: lw a1,0x44(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000044)))));
L_002509f8: ;
    /* 002509F8: lw a3,0x58(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000058)))));
L_002509fc: ;
    /* 002509FC: addu v1,a0,s4 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(20)));
L_00250a00: ;
    /* 00250A00: xori v0,a1,0x0 */ set(2,cpu(5)^UINT64_C(0x0000000000000000));
L_00250a04: ;
    /* 00250A04: move a1,s8 */ set(5,cpu(30));
L_00250a08: ;
    /* 00250A08: movn a3,v1,v0 */ if(cpu(2)!=0) set(7,cpu(3));
L_00250a0c: ;
    /* 00250A0C: move a0,s7 */ set(4,cpu(23));
L_00250a10: ;
    /* 00250A10: jal 0x00266cd8; native delay follows */
    set(31,UINT64_C(0x0000000000250a18));
    /* 00250A14: sw a3,0x58(sp) */ w32(ea(cpu(29),UINT32_C(0x00000058)),(uint32_t)cpu(7));
    fpr()[0]=fbits(ps2CombatMpDrainRate_00266CD8(cpu(4)));
    goto L_00250a18;
L_00250a18: ;
    /* 00250A18: mov.S f1,f0 */ fpr()[1]=fpr()[0];
L_00250a1c: ;
    /* 00250A1C: clear f0 */ fpr()[0]=0;
L_00250a20: ;
    /* 00250A20: c.lt.S f0,f1 */ condition=EE_FPU_COMPARE_S(fpr()[0],fpr()[1],1)!=0;
L_00250a24: ;
    /* 00250A24: bc1f 0x00250a4c; native delay follows */
    { int taken=(!condition);
      /* 00250A28: sll a3,s1,0x4 */ set(7,sx(((uint32_t)cpu(17)<<4)));
      if(taken) goto L_00250a4c;
      goto L_00250a2c; }
L_00250a2c: ;
    /* 00250A2C: mtc1 s4,f0 */ fpr()[0]=(uint32_t)cpu(20);
L_00250a30: ;
    /* 00250A30: cvt.s.W f0,f0 */ fpr()[0]=EE_FPU_CVT_S_W(fpr()[0]);
L_00250a34: ;
    /* 00250A34: mul.S f0,f0,f1 */ fpr()[0]=EE_FPU_MUL_S(fpr()[0],fpr()[1]);
L_00250a38: ;
    /* 00250A38: cvt.w.S f1,f0 */ fpr()[1]=EE_FPU_CVT_W_S(fpr()[0]);
L_00250a3c: ;
    /* 00250A3C: mfc1 v0,f1 */ set(2,sx(fpr()[1]));
L_00250a40: ;
    /* 00250A40: lw v1,0x50(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000050)))));
L_00250a44: ;
    /* 00250A44: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
L_00250a48: ;
    /* 00250A48: sw v1,0x50(sp) */ w32(ea(cpu(29),UINT32_C(0x00000050)),(uint32_t)cpu(3));
L_00250a4c: ;
    /* 00250A4C: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_00250a50: ;
    /* 00250A50: sw a3,0x84(sp) */ w32(ea(cpu(29),UINT32_C(0x00000084)),(uint32_t)cpu(7));
L_00250a54: ;
    /* 00250A54: lui a1,0x2 */ set(5,sx(UINT32_C(0x00020000)));
L_00250a58: ;
    /* 00250A58: move a0,s1 */ set(4,cpu(17));
L_00250a5c: ;
    /* 00250A5C: li s5,0x1 */ set(21,UINT64_C(0x0000000000000001));
L_00250a60: ;
    /* 00250A60: lw v0,0x60(v1) */ set(2,sx(r32(ea(cpu(3),UINT32_C(0x00000060)))));
L_00250a64: ;
    /* 00250A64: lw v1,0x68(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250a68: ;
    /* 00250A68: and v0,v0,a1 */ set(2,cpu(2)&cpu(5));
L_00250a6c: ;
    /* 00250A6C: movn v1,zero,v0 */ if(cpu(2)!=0) set(3,cpu(0));
L_00250a70: ;
    /* 00250A70: jal 0x0026a7d0; native delay follows */
    set(31,UINT64_C(0x0000000000250a78));
    /* 00250A74: sw v1,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(3));
    set(2,nbGetDevilFormatFlag(cpu(4)));
    goto L_00250a78;
L_00250a78: ;
    /* 00250A78: lw a3,0x68(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250a7c: ;
    /* 00250A7C: andi v0,v0,0x100 */ set(2,cpu(2)&UINT64_C(0x0000000000000100));
L_00250a80: ;
    /* 00250A80: lw v1,0x0(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_00250a84: ;
    /* 00250A84: li t4,0x2 */ set(12,UINT64_C(0x0000000000000002));
L_00250a88: ;
    /* 00250A88: lw a0,0x84(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000084)))));
L_00250a8c: ;
    /* 00250A8C: movn a3,zero,v0 */ if(cpu(2)!=0) set(7,cpu(0));
L_00250a90: ;
    /* 00250A90: lw a1,0x20(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
L_00250a94: ;
    /* 00250A94: move t0,s0 */ set(8,cpu(16));
L_00250a98: ;
    /* 00250A98: subu a2,a0,s1 */ set(6,sx((uint32_t)cpu(4)-(uint32_t)cpu(17)));
L_00250a9c: ;
    /* 00250A9C: lw a0,0x0(v1) */ set(4,sx(r32(ea(cpu(3),UINT32_C(0x00000000)))));
L_00250aa0: ;
    /* 00250AA0: sw a3,0x68(sp) */ w32(ea(cpu(29),UINT32_C(0x00000068)),(uint32_t)cpu(7));
L_00250aa4: ;
    /* 00250AA4: xor v1,a1,s5 */ set(3,cpu(5)^cpu(21));
L_00250aa8: ;
    /* 00250AA8: movn t4,zero,v1 */ if(cpu(3)!=0) set(12,cpu(0));
L_00250aac: ;
    /* 00250AAC: lw v1,0x6c(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x0000006c)))));
L_00250ab0: ;
    /* 00250AB0: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250ab4: ;
    /* 00250AB4: sll a2,a2,0x4 */ set(6,sx(((uint32_t)cpu(6)<<4)));
L_00250ab8: ;
    /* 00250AB8: lw t3,0x64(sp) */ set(11,sx(r32(ea(cpu(29),UINT32_C(0x00000064)))));
L_00250abc: ;
    /* 00250ABC: addu a2,a0,a2 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(6)));
L_00250ac0: ;
    /* 00250AC0: lw a3,0x2c(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x0000002c)))));
L_00250ac4: ;
    /* 00250AC4: move t1,s4 */ set(9,cpu(20));
L_00250ac8: ;
    /* 00250AC8: lw t2,0x70(sp) */ set(10,sx(r32(ea(cpu(29),UINT32_C(0x00000070)))));
L_00250acc: ;
    /* 00250ACC: move a0,s3 */ set(4,cpu(19));
L_00250ad0: ;
    /* 00250AD0: move a1,s2 */ set(5,cpu(18));
L_00250ad4: ;
    /* 00250AD4: sw t4,0x18(sp) */ w32(ea(cpu(29),UINT32_C(0x00000018)),(uint32_t)cpu(12));
L_00250ad8: ;
    /* 00250AD8: sw v0,0x0(sp) */ w32(ea(cpu(29),UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_00250adc: ;
    /* 00250ADC: sw v1,0x8(sp) */ w32(ea(cpu(29),UINT32_C(0x00000008)),(uint32_t)cpu(3));
L_00250ae0: ;
    /* 00250AE0: jal 0x00263c00; native delay follows */
    set(31,UINT64_C(0x0000000000250ae8));
    /* 00250AE4: sw s5,0x10(sp) */ w32(ea(cpu(29),UINT32_C(0x00000010)),(uint32_t)cpu(21));
    body_00263c00();
    goto L_00250ae8;
L_00250ae8: ;
    /* 00250AE8: lw a0,0x20(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
L_00250aec: ;
    /* 00250AEC: bne a0,s5,0x00250b10; native delay follows */
    { int taken=(cpu(4)!=cpu(21));
      /* 00250AF0: lw a1,0x20(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
      if(taken) goto L_00250b10;
      goto L_00250af4; }
L_00250af4: ;
    /* 00250AF4: lui a2,0x1 */ set(6,sx(UINT32_C(0x00010000)));
L_00250af8: ;
    /* 00250AF8: move a0,s3 */ set(4,cpu(19));
L_00250afc: ;
    /* 00250AFC: move a1,s2 */ set(5,cpu(18));
L_00250b00: ;
    /* 00250B00: jal 0x00262cc0; native delay follows */
    set(31,UINT64_C(0x0000000000250b08));
    /* 00250B04: ori a2,a2,0x2 */ set(6,cpu(6)|UINT64_C(0x0000000000000002));
    set(2,nbAddSePacket(cpu(4),cpu(5),cpu(6)));
    goto L_00250b08;
L_00250b08: ;
    /* 00250B08: b 0x00250b84; native delay follows */
    { /* 00250B0C: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068))))); goto L_00250b84; }
L_00250b10: ;
    /* 00250B10: slti v0,a1,0x3 */ set(2,lt(cpu(5),UINT64_C(0x0000000000000003)));
L_00250b14: ;
    /* 00250B14: beq v0,zero,0x00250b24; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250B18: nop  */ ;
      if(taken) goto L_00250b24;
      goto L_00250b1c; }
L_00250b1c: ;
    /* 00250B1C: bgtz a1,0x00250b84; native delay follows */
    { int taken=(lt(0,cpu(5)));
      /* 00250B20: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
      if(taken) goto L_00250b84;
      goto L_00250b24; }
L_00250b24: ;
    /* 00250B24: beq s7,zero,0x00250b4c; native delay follows */
    { int taken=(cpu(23)==cpu(0));
      /* 00250B28: lw a3,0x2c(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x0000002c)))));
      if(taken) goto L_00250b4c;
      goto L_00250b2c; }
L_00250b2c: ;
    /* 00250B2C: bltz s7,0x00250b80; native delay follows */
    { int taken=(lt(cpu(23),0));
      /* 00250B30: slti v0,s7,0xa7 */ set(2,lt(cpu(23),UINT64_C(0x00000000000000a7)));
      if(taken) goto L_00250b80;
      goto L_00250b34; }
L_00250b34: ;
    /* 00250B34: beq v0,zero,0x00250b84; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250B38: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
      if(taken) goto L_00250b84;
      goto L_00250b3c; }
L_00250b3c: ;
    /* 00250B3C: slti v0,s7,0xa4 */ set(2,lt(cpu(23),UINT64_C(0x00000000000000a4)));
L_00250b40: ;
    /* 00250B40: bne v0,zero,0x00250b84; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250B44: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
      if(taken) goto L_00250b84;
      goto L_00250b48; }
L_00250b48: ;
    /* 00250B48: lw a3,0x2c(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x0000002c)))));
L_00250b4c: ;
    /* 00250B4C: bne a3,s5,0x00250b70; native delay follows */
    { int taken=(cpu(7)!=cpu(21));
      /* 00250B50: lui a2,0x1 */ set(6,sx(UINT32_C(0x00010000)));
      if(taken) goto L_00250b70;
      goto L_00250b54; }
L_00250b54: ;
    /* 00250B54: move a0,s3 */ set(4,cpu(19));
L_00250b58: ;
    /* 00250B58: move a1,s2 */ set(5,cpu(18));
L_00250b5c: ;
    /* 00250B5C: jal 0x00262cc0; native delay follows */
    set(31,UINT64_C(0x0000000000250b64));
    /* 00250B60: ori a2,a2,0x3 */ set(6,cpu(6)|UINT64_C(0x0000000000000003));
    set(2,nbAddSePacket(cpu(4),cpu(5),cpu(6)));
    goto L_00250b64;
L_00250b64: ;
    /* 00250B64: b 0x00250b84; native delay follows */
    { /* 00250B68: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068))))); goto L_00250b84; }
L_00250b70: ;
    /* 00250B70: move a0,s3 */ set(4,cpu(19));
L_00250b74: ;
    /* 00250B74: move a1,s2 */ set(5,cpu(18));
L_00250b78: ;
    /* 00250B78: jal 0x00262cc0; native delay follows */
    set(31,UINT64_C(0x0000000000250b80));
    /* 00250B7C: ori a2,a2,0x2 */ set(6,cpu(6)|UINT64_C(0x0000000000000002));
    set(2,nbAddSePacket(cpu(4),cpu(5),cpu(6)));
    goto L_00250b80;
L_00250b80: ;
    /* 00250B80: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250b84: ;
    /* 00250B84: beq v0,zero,0x00250bc8; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250B88: move a2,s3 */ set(6,cpu(19));
      if(taken) goto L_00250bc8;
      goto L_00250b8c; }
L_00250b8c: ;
    /* 00250B8C: addiu s3,s3,0x1e */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x0000001e)));
L_00250b90: ;
    /* 00250B90: li a3,0x1e */ set(7,UINT64_C(0x000000000000001e));
L_00250b94: ;
    /* 00250B94: li t0,0x1e */ set(8,UINT64_C(0x000000000000001e));
L_00250b98: ;
    /* 00250B98: move a0,s2 */ set(4,cpu(18));
L_00250b9c: ;
    /* 00250B9C: jal 0x002517e0; native delay follows */
    set(31,UINT64_C(0x0000000000250ba4));
    /* 00250BA0: move a1,s1 */ set(5,cpu(17));
    nbActionSetTimeList(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00250ba4;
L_00250ba4: ;
    /* 00250BA4: move a0,s2 */ set(4,cpu(18));
L_00250ba8: ;
    /* 00250BA8: jal 0x002515d8; native delay follows */
    set(31,UINT64_C(0x0000000000250bb0));
    /* 00250BAC: move a1,s1 */ set(5,cpu(17));
    set(2,nbActionGetTimeListHp(cpu(4),cpu(5)));
    goto L_00250bb0;
L_00250bb0: ;
    /* 00250BB0: move a0,s2 */ set(4,cpu(18));
L_00250bb4: ;
    /* 00250BB4: move a1,s1 */ set(5,cpu(17));
L_00250bb8: ;
    /* 00250BB8: jal 0x002516e8; native delay follows */
    set(31,UINT64_C(0x0000000000250bc0));
    /* 00250BBC: subu a2,zero,v0 */ set(6,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));
    set(2,nbActionAddTimeListHp(cpu(4),cpu(5),cpu(6)));
    goto L_00250bc0;
L_00250bc0: ;
    /* 00250BC0: b 0x00250c9c; native delay follows */
    { /* 00250BC4: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068))))); goto L_00250c9c; }
L_00250bc8: ;
    /* 00250BC8: lw a0,0x2c(s2) */ set(4,sx(r32(ea(cpu(18),UINT32_C(0x0000002c)))));
L_00250bcc: ;
    /* 00250BCC: lw v0,0x0(a0) */ set(2,sx(r32(ea(cpu(4),UINT32_C(0x00000000)))));
L_00250bd0: ;
    /* 00250BD0: andi v0,v0,0x4 */ set(2,cpu(2)&UINT64_C(0x0000000000000004));
L_00250bd4: ;
    /* 00250BD4: bne v0,zero,0x00250c54; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250BD8: li s0,0xa */ set(16,UINT64_C(0x000000000000000a));
      if(taken) goto L_00250c54;
      goto L_00250bdc; }
L_00250bdc: ;
    /* 00250BDC: lh v1,0x6a(a0) */ set(3,sx((uint32_t)i16(r16(ea(cpu(4),UINT32_C(0x0000006a))))));
L_00250be0: ;
    /* 00250BE0: beql v1,zero,0x00250c00; native delay follows */
    { int taken=(cpu(3)==cpu(0));
      if(taken) { /* 00250BE4: lhu v1,0x4(a0) */ set(3,r16(ea(cpu(4),UINT32_C(0x00000004)))); goto L_00250c00; }
      goto L_00250be8; }
L_00250be8: ;
    /* 00250BE8: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_00250bec: ;
    /* 00250BEC: beql v1,v0,0x00250c20; native delay follows */
    { int taken=(cpu(3)==cpu(2));
      if(taken) { /* 00250BF0: lhu v1,0x6c(a0) */ set(3,r16(ea(cpu(4),UINT32_C(0x0000006c)))); goto L_00250c20; }
      goto L_00250bf4; }
L_00250bf4: ;
    /* 00250BF4: b 0x00250c54; native delay follows */
    { /* 00250BF8: nop  */ ; goto L_00250c54; }
L_00250c00: ;
    /* 00250C00: sll v0,v1,0x4 */ set(2,sx(((uint32_t)cpu(3)<<4)));
L_00250c04: ;
    /* 00250C04: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
L_00250c08: ;
    /* 00250C08: lui v1,0x35 */ set(3,sx(UINT32_C(0x00350000)));
L_00250c0c: ;
    /* 00250C0C: sll v0,v0,0x2 */ set(2,sx(((uint32_t)cpu(2)<<2)));
L_00250c10: ;
    /* 00250C10: addiu v1,v1,-0x6840 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffff97c0)));
L_00250c14: ;
    /* 00250C14: b 0x00250c50; native delay follows */
    { /* 00250C18: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3))); goto L_00250c50; }
L_00250c20: ;
    /* 00250C20: slti v0,v1,0xa8 */ set(2,lt(cpu(3),UINT64_C(0x00000000000000a8)));
L_00250c24: ;
    /* 00250C24: beq v0,zero,0x00250c54; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250C28: slti v0,v1,0xa4 */ set(2,lt(cpu(3),UINT64_C(0x00000000000000a4)));
      if(taken) goto L_00250c54;
      goto L_00250c2c; }
L_00250c2c: ;
    /* 00250C2C: bne v0,zero,0x00250c54; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250C30: nop  */ ;
      if(taken) goto L_00250c54;
      goto L_00250c34; }
L_00250c34: ;
    /* 00250C34: lhu v1,0x4(a0) */ set(3,r16(ea(cpu(4),UINT32_C(0x00000004))));
L_00250c38: ;
    /* 00250C38: lui a0,0x35 */ set(4,sx(UINT32_C(0x00350000)));
L_00250c3c: ;
    /* 00250C3C: addiu a0,a0,-0x6840 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffff97c0)));
L_00250c40: ;
    /* 00250C40: sll v0,v1,0x4 */ set(2,sx(((uint32_t)cpu(3)<<4)));
L_00250c44: ;
    /* 00250C44: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
L_00250c48: ;
    /* 00250C48: sll v0,v0,0x2 */ set(2,sx(((uint32_t)cpu(2)<<2)));
L_00250c4c: ;
    /* 00250C4C: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
L_00250c50: ;
    /* 00250C50: lbu s0,0x3a(v0) */ set(16,r8(ea(cpu(2),UINT32_C(0x0000003a))));
L_00250c54: ;
    /* 00250C54: mtc1 s0,f0 */ fpr()[0]=(uint32_t)cpu(16);
L_00250c58: ;
    /* 00250C58: cvt.s.W f0,f0 */ fpr()[0]=EE_FPU_CVT_S_W(fpr()[0]);
L_00250c5c: ;
    /* 00250C5C: li v1,0x5 */ set(3,UINT64_C(0x0000000000000005));
L_00250c60: ;
    /* 00250C60: move a2,s3 */ set(6,cpu(19));
L_00250c64: ;
    /* 00250C64: move a0,s2 */ set(4,cpu(18));
L_00250c68: ;
    /* 00250C68: move a1,s1 */ set(5,cpu(17));
L_00250c6c: ;
    /* 00250C6C: nop  */ ;
L_00250c70: ;
    /* 00250C70: nop  */ ;
L_00250c74: ;
    /* 00250C74: div.S f0,f0,f21 */ fpr()[0]=EE_FPU_DIV_S(fpr()[0],fpr()[21]);
L_00250c78: ;
    /* 00250C78: cvt.w.S f1,f0 */ fpr()[1]=EE_FPU_CVT_W_S(fpr()[0]);
L_00250c7c: ;
    /* 00250C7C: mfc1 s0,f1 */ set(16,sx(fpr()[1]));
L_00250c80: ;
    /* 00250C80: slti v0,s0,0x5 */ set(2,lt(cpu(16),UINT64_C(0x0000000000000005)));
L_00250c84: ;
    /* 00250C84: movn s0,v1,v0 */ if(cpu(2)!=0) set(16,cpu(3));
L_00250c88: ;
    /* 00250C88: move a3,s0 */ set(7,cpu(16));
L_00250c8c: ;
    /* 00250C8C: jal 0x002517e0; native delay follows */
    set(31,UINT64_C(0x0000000000250c94));
    /* 00250C90: move t0,s0 */ set(8,cpu(16));
    nbActionSetTimeList(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00250c94;
L_00250c94: ;
    /* 00250C94: addu s3,s3,s0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(16)));
L_00250c98: ;
    /* 00250C98: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250c9c: ;
    /* 00250C9C: bne v0,zero,0x00250cfc; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250CA0: lw a3,0x38(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000038)))));
      if(taken) goto L_00250cfc;
      goto L_00250ca4; }
L_00250ca4: ;
    /* 00250CA4: lw v1,0x70(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000070)))));
L_00250ca8: ;
    /* 00250CA8: bnel v1,zero,0x00250d00; native delay follows */
    { int taken=(cpu(3)!=cpu(0));
      if(taken) { /* 00250CAC: move v0,zero */ set(2,cpu(0)); goto L_00250d00; }
      goto L_00250cb0; }
L_00250cb0: ;
    /* 00250CB0: lw a0,0x90(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000090)))));
L_00250cb4: ;
    /* 00250CB4: beql a0,zero,0x00250d00; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      if(taken) { /* 00250CB8: move v0,zero */ set(2,cpu(0)); goto L_00250d00; }
      goto L_00250cbc; }
L_00250cbc: ;
    /* 00250CBC: jal 0x00246ab8; native delay follows */
    set(31,UINT64_C(0x0000000000250cc4));
    /* 00250CC0: move a0,s1 */ set(4,cpu(17));
    set(2,nbGetUnitWorkFromFormindex(cpu(4)));
    goto L_00250cc4;
L_00250cc4: ;
    /* 00250CC4: li a1,0x2 */ set(5,UINT64_C(0x0000000000000002));
L_00250cc8: ;
    /* 00250CC8: jal 0x00267530; native delay follows */
    set(31,UINT64_C(0x0000000000250cd0));
    /* 00250CCC: move a0,v0 */ set(4,cpu(2));
    set(2,ps2CombatCheckStatusRecovery_00267530(cpu(4),cpu(5)));
    goto L_00250cd0;
L_00250cd0: ;
    /* 00250CD0: beq v0,zero,0x00250cf8; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00250CD4: lw a1,0x84(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000084)))));
      if(taken) goto L_00250cf8;
      goto L_00250cd8; }
L_00250cd8: ;
    /* 00250CD8: move a0,s3 */ set(4,cpu(19));
L_00250cdc: ;
    /* 00250CDC: lw v0,0x0(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_00250ce0: ;
    /* 00250CE0: subu a2,a1,s1 */ set(6,sx((uint32_t)cpu(5)-(uint32_t)cpu(17)));
L_00250ce4: ;
    /* 00250CE4: move a1,s2 */ set(5,cpu(18));
L_00250ce8: ;
    /* 00250CE8: lw v1,0x0(v0) */ set(3,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_00250cec: ;
    /* 00250CEC: sll a2,a2,0x4 */ set(6,sx(((uint32_t)cpu(6)<<4)));
L_00250cf0: ;
    /* 00250CF0: jal 0x002645a8; native delay follows */
    set(31,UINT64_C(0x0000000000250cf8));
    /* 00250CF4: addu a2,v1,a2 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
    set(2,nbMakeBadKaifukuPacket(cpu(4),cpu(5),cpu(6)));
    goto L_00250cf8;
L_00250cf8: ;
    /* 00250CF8: lw a3,0x38(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000038)))));
L_00250cfc: ;
    /* 00250CFC: move v0,zero */ set(2,cpu(0));
L_00250d00: ;
    /* 00250D00: lw a1,0x34(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000034)))));
L_00250d04: ;
    /* 00250D04: move a0,s7 */ set(4,cpu(23));
L_00250d08: ;
    /* 00250D08: slt v1,v0,a3 */ set(3,lt(cpu(2),cpu(7)));
L_00250d0c: ;
    /* 00250D0C: lw a3,0x5c(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x0000005c)))));
L_00250d10: ;
    /* 00250D10: slt v0,v0,a1 */ set(2,lt(cpu(2),cpu(5)));
L_00250d14: ;
    /* 00250D14: move a1,s8 */ set(5,cpu(30));
L_00250d18: ;
    /* 00250D18: mtlo a3 */ lo=(uint32_t)cpu(7);
L_00250d1c: ;
    /* 00250D1C: lw a3,0x34(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000034)))));
L_00250d20: ;
    /* 00250D20: move a2,s1 */ set(6,cpu(17));
L_00250d24: ;
    /* 00250D24: madd v0,a3 */ lo+=(uint32_t)((int64_t)i32((uint32_t)cpu(2))*(int64_t)i32((uint32_t)cpu(7)));
L_00250d28: ;
    /* 00250D28: lw v0,0x60(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000060)))));
L_00250d2c: ;
    /* 00250D2C: mflo a3 */ set(7,sx(lo));
L_00250d30: ;
    /* 00250D30: mtlo v0 */ lo=(uint32_t)cpu(2);
L_00250d34: ;
    /* 00250D34: lw v0,0x38(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000038)))));
L_00250d38: ;
    /* 00250D38: sw a3,0x5c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000005c)),(uint32_t)cpu(7));
L_00250d3c: ;
    /* 00250D3C: madd v1,v0 */ lo+=(uint32_t)((int64_t)i32((uint32_t)cpu(3))*(int64_t)i32((uint32_t)cpu(2)));
L_00250d40: ;
    /* 00250D40: mflo v0 */ set(2,sx(lo));
L_00250d44: ;
    /* 00250D44: jal 0x00266d20; native delay follows */
    set(31,UINT64_C(0x0000000000250d4c));
    /* 00250D48: sw v0,0x60(sp) */ w32(ea(cpu(29),UINT32_C(0x00000060)),(uint32_t)cpu(2));
    fpr()[0]=fbits(ps2CombatReductionRate_00266D20(cpu(4)));
    goto L_00250d4c;
L_00250d4c: ;
    /* 00250D4C: lw v1,0x68(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250d50: ;
    /* 00250D50: bne v1,zero,0x00250db8; native delay follows */
    { int taken=(cpu(3)!=cpu(0));
      /* 00250D54: mul.S f20,f20,f0 */ fpr()[20]=EE_FPU_MUL_S(fpr()[20],fpr()[0]);
      if(taken) goto L_00250db8;
      goto L_00250d58; }
L_00250d58: ;
    /* 00250D58: lw a0,0x40(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000040)))));
L_00250d5c: ;
    /* 00250D5C: bne a0,zero,0x00250da4; native delay follows */
    { int taken=(cpu(4)!=cpu(0));
      /* 00250D60: lw a3,0x28(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000028)))));
      if(taken) goto L_00250da4;
      goto L_00250d64; }
L_00250d64: ;
    /* 00250D64: lw a1,0x34(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000034)))));
L_00250d68: ;
    /* 00250D68: bgtz a1,0x00250da8; native delay follows */
    { int taken=(lt(0,cpu(5)));
      /* 00250D6C: lw v1,0x24(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
      if(taken) goto L_00250da8;
      goto L_00250d70; }
L_00250d70: ;
    /* 00250D70: lw a3,0x38(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000038)))));
L_00250d74: ;
    /* 00250D74: bgtz a3,0x00250da8; native delay follows */
    { int taken=(lt(0,cpu(7)));
      /* 00250D78: lw a3,0x28(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000028)))));
      if(taken) goto L_00250da8;
      goto L_00250d7c; }
L_00250d7c: ;
    /* 00250D7C: lw v1,0x88(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000088)))));
L_00250d80: ;
    /* 00250D80: lw v0,0x0(v1) */ set(2,sx(r32(ea(cpu(3),UINT32_C(0x00000000)))));
L_00250d84: ;
    /* 00250D84: bne v0,zero,0x00250da4; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250D88: nop  */ ;
      if(taken) goto L_00250da4;
      goto L_00250d8c; }
L_00250d8c: ;
    /* 00250D8C: lw a0,0x74(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000074)))));
L_00250d90: ;
    /* 00250D90: bne a0,zero,0x00250da8; native delay follows */
    { int taken=(cpu(4)!=cpu(0));
      /* 00250D94: lw v1,0x24(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
      if(taken) goto L_00250da8;
      goto L_00250d98; }
L_00250d98: ;
    /* 00250D98: lw a1,0x3c(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x0000003c)))));
L_00250d9c: ;
    /* 00250D9C: beq a1,zero,0x002503e0; native delay follows */
    { int taken=(cpu(5)==cpu(0));
      /* 00250DA0: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
      if(taken) goto L_002503e0;
      goto L_00250da4; }
L_00250da4: ;
    /* 00250DA4: lw v1,0x24(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000024)))));
L_00250da8: ;
    /* 00250DA8: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
L_00250dac: ;
    /* 00250DAC: slt v0,a3,v1 */ set(2,lt(cpu(7),cpu(3)));
L_00250db0: ;
    /* 00250DB0: bne v0,zero,0x00250538; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250DB4: sw a3,0x28(sp) */ w32(ea(cpu(29),UINT32_C(0x00000028)),(uint32_t)cpu(7));
      if(taken) goto L_00250538;
      goto L_00250db8; }
L_00250db8: ;
    /* 00250DB8: lw a0,0x54(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000054)))));
L_00250dbc: ;
    /* 00250DBC: lw a1,0x58(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000058)))));
L_00250dc0: ;
    /* 00250DC0: lw v1,0x5c(s2) */ set(3,sx(r32(ea(cpu(18),UINT32_C(0x0000005c)))));
L_00250dc4: ;
    /* 00250DC4: lw v0,0x60(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000060)))));
L_00250dc8: ;
    /* 00250DC8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
L_00250dcc: ;
    /* 00250DCC: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
L_00250dd0: ;
    /* 00250DD0: sw v1,0x5c(s2) */ w32(ea(cpu(18),UINT32_C(0x0000005c)),(uint32_t)cpu(3));
L_00250dd4: ;
    /* 00250DD4: sw v0,0x60(s2) */ w32(ea(cpu(18),UINT32_C(0x00000060)),(uint32_t)cpu(2));
L_00250dd8: ;
    /* 00250DD8: lw a3,0x68(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250ddc: ;
    /* 00250DDC: bne a3,zero,0x00250f24; native delay follows */
    { int taken=(cpu(7)!=cpu(0));
      /* 00250DE0: move s0,s3 */ set(16,cpu(19));
      if(taken) goto L_00250f24;
      goto L_00250de4; }
L_00250de4: ;
    /* 00250DE4: lw v0,0x5c(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x0000005c)))));
L_00250de8: ;
    /* 00250DE8: bgtz v0,0x00250e08; native delay follows */
    { int taken=(lt(0,cpu(2)));
      /* 00250DEC: lw a3,0x5c(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x0000005c)))));
      if(taken) goto L_00250e08;
      goto L_00250df0; }
L_00250df0: ;
    /* 00250DF0: lw v1,0x60(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000060)))));
L_00250df4: ;
    /* 00250DF4: bgtz v1,0x00250e0c; native delay follows */
    { int taken=(lt(0,cpu(3)));
      /* 00250DF8: move v0,zero */ set(2,cpu(0));
      if(taken) goto L_00250e0c;
      goto L_00250dfc; }
L_00250dfc: ;
    /* 00250DFC: lw a0,0x3c(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x0000003c)))));
L_00250e00: ;
    /* 00250E00: beq a0,zero,0x00250eac; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      /* 00250E04: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
      if(taken) goto L_00250eac;
      goto L_00250e08; }
L_00250e08: ;
    /* 00250E08: move v0,zero */ set(2,cpu(0));
L_00250e0c: ;
    /* 00250E0C: lw a0,0x0(s2) */ set(4,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_00250e10: ;
    /* 00250E10: li t1,-0x1 */ set(9,UINT64_C(0xffffffffffffffff));
L_00250e14: ;
    /* 00250E14: slt v1,v0,a3 */ set(3,lt(cpu(2),cpu(7)));
L_00250e18: ;
    /* 00250E18: sll a2,s1,0x4 */ set(6,sx(((uint32_t)cpu(17)<<4)));
L_00250e1c: ;
    /* 00250E1C: movz a3,t1,v1 */ if(cpu(3)==0) set(7,cpu(9));
L_00250e20: ;
    /* 00250E20: lw a1,0x0(a0) */ set(5,sx(r32(ea(cpu(4),UINT32_C(0x00000000)))));
L_00250e24: ;
    /* 00250E24: lw a0,0x60(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000060)))));
L_00250e28: ;
    /* 00250E28: subu a2,a2,s1 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(17)));
L_00250e2c: ;
    /* 00250E2C: sw a3,0x5c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000005c)),(uint32_t)cpu(7));
L_00250e30: ;
    /* 00250E30: move a3,zero */ set(7,cpu(0));
L_00250e34: ;
    /* 00250E34: slt v0,v0,a0 */ set(2,lt(cpu(2),cpu(4)));
L_00250e38: ;
    /* 00250E38: sll a2,a2,0x4 */ set(6,sx(((uint32_t)cpu(6)<<4)));
L_00250e3c: ;
    /* 00250E3C: lw t0,0x5c(sp) */ set(8,sx(r32(ea(cpu(29),UINT32_C(0x0000005c)))));
L_00250e40: ;
    /* 00250E40: movn t1,a0,v0 */ if(cpu(2)!=0) set(9,cpu(4));
L_00250e44: ;
    /* 00250E44: lw t2,0x3c(sp) */ set(10,sx(r32(ea(cpu(29),UINT32_C(0x0000003c)))));
L_00250e48: ;
    /* 00250E48: addu a2,a1,a2 */ set(6,sx((uint32_t)cpu(5)+(uint32_t)cpu(6)));
L_00250e4c: ;
    /* 00250E4C: move a0,s3 */ set(4,cpu(19));
L_00250e50: ;
    /* 00250E50: jal 0x00264010; native delay follows */
    set(31,UINT64_C(0x0000000000250e58));
    /* 00250E54: move a1,s2 */ set(5,cpu(18));
    body_00264010();
    goto L_00250e58;
L_00250e58: ;
    /* 00250E58: lw a1,0x3c(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x0000003c)))));
L_00250e5c: ;
    /* 00250E5C: beq a1,zero,0x00250e70; native delay follows */
    { int taken=(cpu(5)==cpu(0));
      /* 00250E60: move a2,a1 */ set(6,cpu(5));
      if(taken) goto L_00250e70;
      goto L_00250e64; }
L_00250e64: ;
    /* 00250E64: move a1,zero */ set(5,cpu(0));
L_00250e68: ;
    /* 00250E68: jal 0x002674d0; native delay follows */
    set(31,UINT64_C(0x0000000000250e70));
    /* 00250E6C: move a0,s1 */ set(4,cpu(17));
    ps2CombatSetStatus_002674D0(cpu(4),cpu(5),cpu(6));
    goto L_00250e70;
L_00250e70: ;
    /* 00250E70: lw a3,0x5c(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x0000005c)))));
L_00250e74: ;
    /* 00250E74: blez a3,0x00250e90; native delay follows */
    { int taken=(!lt(0,cpu(7)));
      /* 00250E78: move a2,s3 */ set(6,cpu(19));
      if(taken) goto L_00250e90;
      goto L_00250e7c; }
L_00250e7c: ;
    /* 00250E7C: move a2,a3 */ set(6,cpu(7));
L_00250e80: ;
    /* 00250E80: move a0,s2 */ set(4,cpu(18));
L_00250e84: ;
    /* 00250E84: jal 0x002516e8; native delay follows */
    set(31,UINT64_C(0x0000000000250e8c));
    /* 00250E88: move a1,s1 */ set(5,cpu(17));
    set(2,nbActionAddTimeListHp(cpu(4),cpu(5),cpu(6)));
    goto L_00250e8c;
L_00250e8c: ;
    /* 00250E8C: move a2,s3 */ set(6,cpu(19));
L_00250e90: ;
    /* 00250E90: addiu s3,s3,0xf */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x0000000f)));
L_00250e94: ;
    /* 00250E94: move a0,s2 */ set(4,cpu(18));
L_00250e98: ;
    /* 00250E98: move a1,s1 */ set(5,cpu(17));
L_00250e9c: ;
    /* 00250E9C: li a3,0xf */ set(7,UINT64_C(0x000000000000000f));
L_00250ea0: ;
    /* 00250EA0: jal 0x002517e0; native delay follows */
    set(31,UINT64_C(0x0000000000250ea8));
    /* 00250EA4: li t0,0x14 */ set(8,UINT64_C(0x0000000000000014));
    nbActionSetTimeList(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00250ea8;
L_00250ea8: ;
    /* 00250EA8: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250eac: ;
    /* 00250EAC: bne v0,zero,0x00250f28; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250EB0: lw a0,0x4c(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x0000004c)))));
      if(taken) goto L_00250f28;
      goto L_00250eb4; }
L_00250eb4: ;
    /* 00250EB4: lw v1,0x90(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000090)))));
L_00250eb8: ;
    /* 00250EB8: beq v1,zero,0x00250f28; native delay follows */
    { int taken=(cpu(3)==cpu(0));
      /* 00250EBC: sll v0,s7,0x4 */ set(2,sx(((uint32_t)cpu(23)<<4)));
      if(taken) goto L_00250f28;
      goto L_00250ec0; }
L_00250ec0: ;
    /* 00250EC0: lui v1,0x3d */ set(3,sx(UINT32_C(0x003d0000)));
L_00250ec4: ;
    /* 00250EC4: subu v0,v0,s7 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(23)));
L_00250ec8: ;
    /* 00250EC8: addiu a1,v1,0x7998 */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0x00007998)));
L_00250ecc: ;
    /* 00250ECC: sll v0,v0,0x2 */ set(2,sx(((uint32_t)cpu(2)<<2)));
L_00250ed0: ;
    /* 00250ED0: addiu a0,v0,0x20 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
L_00250ed4: ;
    /* 00250ED4: addu v1,a1,a0 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
L_00250ed8: ;
    /* 00250ED8: lw a3,0x8(v1) */ set(7,sx(r32(ea(cpu(3),UINT32_C(0x00000008)))));
L_00250edc: ;
    /* 00250EDC: beq a3,zero,0x00250f24; native delay follows */
    { int taken=(cpu(7)==cpu(0));
      /* 00250EE0: sll a2,s1,0x4 */ set(6,sx(((uint32_t)cpu(17)<<4)));
      if(taken) goto L_00250f24;
      goto L_00250ee4; }
L_00250ee4: ;
    /* 00250EE4: lw v0,0x0(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_00250ee8: ;
    /* 00250EE8: addu v1,a0,a1 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
L_00250eec: ;
    /* 00250EEC: move a1,s2 */ set(5,cpu(18));
L_00250ef0: ;
    /* 00250EF0: lw a0,0x0(v0) */ set(4,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_00250ef4: ;
    /* 00250EF4: subu a2,a2,s1 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(17)));
L_00250ef8: ;
    /* 00250EF8: lb t0,0xc(v1) */ set(8,sx((uint32_t)i8(r8(ea(cpu(3),UINT32_C(0x0000000c))))));
L_00250efc: ;
    /* 00250EFC: sll a2,a2,0x4 */ set(6,sx(((uint32_t)cpu(6)<<4)));
L_00250f00: ;
    /* 00250F00: addu a2,a0,a2 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(6)));
L_00250f04: ;
    /* 00250F04: jal 0x002634c8; native delay follows */
    set(31,UINT64_C(0x0000000000250f0c));
    /* 00250F08: move a0,s3 */ set(4,cpu(19));
    body_002634c8();
    goto L_00250f0c;
L_00250f0c: ;
    /* 00250F0C: move a0,s2 */ set(4,cpu(18));
L_00250f10: ;
    /* 00250F10: move a1,s1 */ set(5,cpu(17));
L_00250f14: ;
    /* 00250F14: move a2,s3 */ set(6,cpu(19));
L_00250f18: ;
    /* 00250F18: li a3,0xa */ set(7,UINT64_C(0x000000000000000a));
L_00250f1c: ;
    /* 00250F1C: jal 0x002517e0; native delay follows */
    set(31,UINT64_C(0x0000000000250f24));
    /* 00250F20: li t0,0xf */ set(8,UINT64_C(0x000000000000000f));
    nbActionSetTimeList(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00250f24;
L_00250f24: ;
    /* 00250F24: lw a0,0x4c(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x0000004c)))));
L_00250f28: ;
    /* 00250F28: bgtz a0,0x00250f40; native delay follows */
    { int taken=(lt(0,cpu(4)));
      /* 00250F2C: lw a3,0x44(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000044)))));
      if(taken) goto L_00250f40;
      goto L_00250f30; }
L_00250f30: ;
    /* 00250F30: lw a1,0x50(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000050)))));
L_00250f34: ;
    /* 00250F34: blez a1,0x00250fd4; native delay follows */
    { int taken=(!lt(0,cpu(5)));
      /* 00250F38: lw v1,0x68(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
      if(taken) goto L_00250fd4;
      goto L_00250f3c; }
L_00250f3c: ;
    /* 00250F3C: lw a3,0x44(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000044)))));
L_00250f40: ;
    /* 00250F40: beq a3,zero,0x00250fd0; native delay follows */
    { int taken=(cpu(7)==cpu(0));
      /* 00250F44: move v0,zero */ set(2,cpu(0));
      if(taken) goto L_00250fd0;
      goto L_00250f48; }
L_00250f48: ;
    /* 00250F48: lw a0,0x0(s2) */ set(4,sx(r32(ea(cpu(18),UINT32_C(0x00000000)))));
L_00250f4c: ;
    /* 00250F4C: li t1,-0x1 */ set(9,UINT64_C(0xffffffffffffffff));
L_00250f50: ;
    /* 00250F50: lw a3,0x50(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000050)))));
L_00250f54: ;
    /* 00250F54: lw a1,0x0(a0) */ set(5,sx(r32(ea(cpu(4),UINT32_C(0x00000000)))));
L_00250f58: ;
    /* 00250F58: sll a2,s8,0x4 */ set(6,sx(((uint32_t)cpu(30)<<4)));
L_00250f5c: ;
    /* 00250F5C: lw a0,0x4c(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x0000004c)))));
L_00250f60: ;
    /* 00250F60: subu a2,a2,s8 */ set(6,sx((uint32_t)cpu(6)-(uint32_t)cpu(30)));
L_00250f64: ;
    /* 00250F64: sll a2,a2,0x4 */ set(6,sx(((uint32_t)cpu(6)<<4)));
L_00250f68: ;
    /* 00250F68: addiu s0,s0,0x5 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000005)));
L_00250f6c: ;
    /* 00250F6C: slt v1,v0,a0 */ set(3,lt(cpu(2),cpu(4)));
L_00250f70: ;
    /* 00250F70: slt v0,v0,a3 */ set(2,lt(cpu(2),cpu(7)));
L_00250f74: ;
    /* 00250F74: movz a0,t1,v1 */ if(cpu(3)==0) set(4,cpu(9));
L_00250f78: ;
    /* 00250F78: movn t1,a3,v0 */ if(cpu(2)!=0) set(9,cpu(7));
L_00250f7c: ;
    /* 00250F7C: sw a0,0x4c(sp) */ w32(ea(cpu(29),UINT32_C(0x0000004c)),(uint32_t)cpu(4));
L_00250f80: ;
    /* 00250F80: addiu a0,s0,0xa */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x0000000a)));
L_00250f84: ;
    /* 00250F84: addu a2,a1,a2 */ set(6,sx((uint32_t)cpu(5)+(uint32_t)cpu(6)));
L_00250f88: ;
    /* 00250F88: move a1,s2 */ set(5,cpu(18));
L_00250f8c: ;
    /* 00250F8C: lw t0,0x4c(sp) */ set(8,sx(r32(ea(cpu(29),UINT32_C(0x0000004c)))));
L_00250f90: ;
    /* 00250F90: li a3,0x2 */ set(7,UINT64_C(0x0000000000000002));
L_00250f94: ;
    /* 00250F94: jal 0x00264010; native delay follows */
    set(31,UINT64_C(0x0000000000250f9c));
    /* 00250F98: move t2,zero */ set(10,cpu(0));
    body_00264010();
    goto L_00250f9c;
L_00250f9c: ;
    /* 00250F9C: lw v0,0x4c(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x0000004c)))));
L_00250fa0: ;
    /* 00250FA0: blez v0,0x00250fbc; native delay follows */
    { int taken=(!lt(0,cpu(2)));
      /* 00250FA4: move a2,s0 */ set(6,cpu(16));
      if(taken) goto L_00250fbc;
      goto L_00250fa8; }
L_00250fa8: ;
    /* 00250FA8: move a2,v0 */ set(6,cpu(2));
L_00250fac: ;
    /* 00250FAC: move a0,s2 */ set(4,cpu(18));
L_00250fb0: ;
    /* 00250FB0: jal 0x002516e8; native delay follows */
    set(31,UINT64_C(0x0000000000250fb8));
    /* 00250FB4: move a1,s8 */ set(5,cpu(30));
    set(2,nbActionAddTimeListHp(cpu(4),cpu(5),cpu(6)));
    goto L_00250fb8;
L_00250fb8: ;
    /* 00250FB8: move a2,s0 */ set(6,cpu(16));
L_00250fbc: ;
    /* 00250FBC: move a0,s2 */ set(4,cpu(18));
L_00250fc0: ;
    /* 00250FC0: move a1,s8 */ set(5,cpu(30));
L_00250fc4: ;
    /* 00250FC4: li a3,0xf */ set(7,UINT64_C(0x000000000000000f));
L_00250fc8: ;
    /* 00250FC8: jal 0x002517e0; native delay follows */
    set(31,UINT64_C(0x0000000000250fd0));
    /* 00250FCC: li t0,0x14 */ set(8,UINT64_C(0x0000000000000014));
    nbActionSetTimeList(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00250fd0;
L_00250fd0: ;
    /* 00250FD0: lw v1,0x68(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00250fd4: ;
    /* 00250FD4: bne v1,zero,0x00251000; native delay follows */
    { int taken=(cpu(3)!=cpu(0));
      /* 00250FD8: nop  */ ;
      if(taken) goto L_00251000;
      goto L_00250fdc; }
L_00250fdc: ;
    /* 00250FDC: lw a0,0x78(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x00000078)))));
L_00250fe0: ;
    /* 00250FE0: beq a0,zero,0x00251000; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      /* 00250FE4: nop  */ ;
      if(taken) goto L_00251000;
      goto L_00250fe8; }
L_00250fe8: ;
    /* 00250FE8: lw v0,0x34(s2) */ set(2,sx(r32(ea(cpu(18),UINT32_C(0x00000034)))));
L_00250fec: ;
    /* 00250FEC: bne v0,zero,0x00251000; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00250FF0: move a1,s1 */ set(5,cpu(17));
      if(taken) goto L_00251000;
      goto L_00250ff4; }
L_00250ff4: ;
    /* 00250FF4: move a0,s2 */ set(4,cpu(18));
L_00250ff8: ;
    /* 00250FF8: jal 0x002521c8; native delay follows */
    set(31,UINT64_C(0x0000000000251000));
    /* 00250FFC: move a2,s8 */ set(6,cpu(30));
    body_002521c8();
    goto L_00251000;
L_00251000: ;
    /* 00251000: jal 0x0026a398; native delay follows */
    set(31,UINT64_C(0x0000000000251008));
    /* 00251004: move a0,s1 */ set(4,cpu(17));
    nbSetKuisibariStop(cpu(4));
    goto L_00251008;
L_00251008: ;
    /* 00251008: lw a1,0x68(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_0025100c: ;
    /* 0025100C: beq a1,zero,0x00251020; native delay follows */
    { int taken=(cpu(5)==cpu(0));
      /* 00251010: nop  */ ;
      if(taken) goto L_00251020;
      goto L_00251014; }
L_00251014: ;
    /* 00251014: move a0,s2 */ set(4,cpu(18));
L_00251018: ;
    /* 00251018: jal 0x0024f478; native delay follows */
    set(31,UINT64_C(0x0000000000251020));
    /* 0025101C: move a1,s1 */ set(5,cpu(17));
    body_0024f478();
    goto L_00251020;
L_00251020: ;
    /* 00251020: jal 0x00246ab8; native delay follows */
    set(31,UINT64_C(0x0000000000251028));
    /* 00251024: move a0,s1 */ set(4,cpu(17));
    set(2,nbGetUnitWorkFromFormindex(cpu(4)));
    goto L_00251028;
L_00251028: ;
    /* 00251028: move v1,v0 */ set(3,cpu(2));
L_0025102c: ;
    /* 0025102C: slti v0,s7,0x31 */ set(2,lt(cpu(23),UINT64_C(0x0000000000000031)));
L_00251030: ;
    /* 00251030: bne v0,zero,0x00251084; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00251034: lw a3,0x20(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
      if(taken) goto L_00251084;
      goto L_00251038; }
L_00251038: ;
    /* 00251038: slti v0,s7,0x33 */ set(2,lt(cpu(23),UINT64_C(0x0000000000000033)));
L_0025103c: ;
    /* 0025103C: bnel v0,zero,0x00251058; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      if(taken) { /* 00251040: lhu a3,0x4(v1) */ set(7,r16(ea(cpu(3),UINT32_C(0x00000004)))); goto L_00251058; }
      goto L_00251044; }
L_00251044: ;
    /* 00251044: li v0,0xe0 */ set(2,UINT64_C(0x00000000000000e0));
L_00251048: ;
    /* 00251048: beql s7,v0,0x00251070; native delay follows */
    { int taken=(cpu(23)==cpu(2));
      if(taken) { /* 0025104C: lhu a3,0x4(v1) */ set(7,r16(ea(cpu(3),UINT32_C(0x00000004)))); goto L_00251070; }
      goto L_00251050; }
L_00251050: ;
    /* 00251050: b 0x00251088; native delay follows */
    { /* 00251054: li v1,0x1 */ set(3,UINT64_C(0x0000000000000001)); goto L_00251088; }
L_00251058: ;
    /* 00251058: move a0,s2 */ set(4,cpu(18));
L_0025105c: ;
    /* 0025105C: li a1,0x4e */ set(5,UINT64_C(0x000000000000004e));
L_00251060: ;
    /* 00251060: jal 0x002592b0; native delay follows */
    set(31,UINT64_C(0x0000000000251068));
    /* 00251064: li a2,0x1 */ set(6,UINT64_C(0x0000000000000001));
    body_002592b0();
    goto L_00251068;
L_00251068: ;
    /* 00251068: b 0x00251084; native delay follows */
    { /* 0025106C: lw a3,0x20(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000020))))); goto L_00251084; }
L_00251070: ;
    /* 00251070: move a0,s2 */ set(4,cpu(18));
L_00251074: ;
    /* 00251074: li a1,0x58 */ set(5,UINT64_C(0x0000000000000058));
L_00251078: ;
    /* 00251078: jal 0x002592b0; native delay follows */
    set(31,UINT64_C(0x0000000000251080));
    /* 0025107C: li a2,0x1 */ set(6,UINT64_C(0x0000000000000001));
    body_002592b0();
    goto L_00251080;
L_00251080: ;
    /* 00251080: lw a3,0x20(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
L_00251084: ;
    /* 00251084: li v1,0x1 */ set(3,UINT64_C(0x0000000000000001));
L_00251088: ;
    /* 00251088: beq a3,v1,0x002511f8; native delay follows */
    { int taken=(cpu(7)==cpu(3));
      /* 0025108C: slti v0,a3,0x2 */ set(2,lt(cpu(7),UINT64_C(0x0000000000000002)));
      if(taken) goto L_002511f8;
      goto L_00251090; }
L_00251090: ;
    /* 00251090: beql v0,zero,0x002510a8; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      if(taken) { /* 00251094: lw v1,0x20(sp) */ set(3,sx(r32(ea(cpu(29),UINT32_C(0x00000020))))); goto L_002510a8; }
      goto L_00251098; }
L_00251098: ;
    /* 00251098: beq a3,zero,0x002510c8; native delay follows */
    { int taken=(cpu(7)==cpu(0));
      /* 0025109C: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
      if(taken) goto L_002510c8;
      goto L_002510a0; }
L_002510a0: ;
    /* 002510A0: b 0x002513f4; native delay follows */
    { /* 002510A4: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8)))); goto L_002513f4; }
L_002510a8: ;
    /* 002510A8: li v0,0x2 */ set(2,UINT64_C(0x0000000000000002));
L_002510ac: ;
    /* 002510AC: beq v1,v0,0x002512b0; native delay follows */
    { int taken=(cpu(3)==cpu(2));
      /* 002510B0: li v0,0x3 */ set(2,UINT64_C(0x0000000000000003));
      if(taken) goto L_002512b0;
      goto L_002510b4; }
L_002510b4: ;
    /* 002510B4: beq v1,v0,0x00251368; native delay follows */
    { int taken=(cpu(3)==cpu(2));
      /* 002510B8: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
      if(taken) goto L_00251368;
      goto L_002510bc; }
L_002510bc: ;
    /* 002510BC: b 0x002513f4; native delay follows */
    { /* 002510C0: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8)))); goto L_002513f4; }
L_002510c8: ;
    /* 002510C8: lw a0,0x2c(sp) */ set(4,sx(r32(ea(cpu(29),UINT32_C(0x0000002c)))));
L_002510cc: ;
    /* 002510CC: beq a0,v1,0x00251158; native delay follows */
    { int taken=(cpu(4)==cpu(3));
      /* 002510D0: slti v0,a0,0x2 */ set(2,lt(cpu(4),UINT64_C(0x0000000000000002)));
      if(taken) goto L_00251158;
      goto L_002510d4; }
L_002510d4: ;
    /* 002510D4: beq v0,zero,0x002510f0; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002510D8: lw a1,0x2c(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x0000002c)))));
      if(taken) goto L_002510f0;
      goto L_002510dc; }
L_002510dc: ;
    /* 002510DC: beq a0,zero,0x00251108; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      /* 002510E0: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
      if(taken) goto L_00251108;
      goto L_002510e4; }
L_002510e4: ;
    /* 002510E4: b 0x002513f4; native delay follows */
    { /* 002510E8: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8)))); goto L_002513f4; }
L_002510f0: ;
    /* 002510F0: li v0,0x2 */ set(2,UINT64_C(0x0000000000000002));
L_002510f4: ;
    /* 002510F4: beq a1,v0,0x002511a8; native delay follows */
    { int taken=(cpu(5)==cpu(2));
      /* 002510F8: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
      if(taken) goto L_002511a8;
      goto L_002510fc; }
L_002510fc: ;
    /* 002510FC: b 0x002513f4; native delay follows */
    { /* 00251100: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8)))); goto L_002513f4; }
L_00251108: ;
    /* 00251108: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
L_0025110c: ;
    /* 0025110C: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00251110: ;
    /* 00251110: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x0000000000251118));
    /* 00251114: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_00251118;
L_00251118: ;
    /* 00251118: move a0,s2 */ set(4,cpu(18));
L_0025111c: ;
    /* 0025111C: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_00251120: ;
    /* 00251120: move a1,zero */ set(5,cpu(0));
L_00251124: ;
    /* 00251124: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_00251128: ;
    /* 00251128: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_0025112c: ;
    /* 0025112C: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_00251130: ;
    /* 00251130: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_00251134: ;
    /* 00251134: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_00251138: ;
    /* 00251138: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_0025113c: ;
    /* 0025113C: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_00251140: ;
    /* 00251140: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_00251144: ;
    /* 00251144: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_00251148: ;
    /* 00251148: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_0025114c: ;
    /* 0025114C: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_00251150: ;
    /* 00251150: j 0x0024f5b0; native delay follows */
    /* 00251154: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));
    body_0024f5b0();
    ba_return(incoming_ra); return;
L_00251158: ;
    /* 00251158: lui at,0xbf00 */ set(1,sx(UINT32_C(0xbf000000)));
L_0025115c: ;
    /* 0025115C: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00251160: ;
    /* 00251160: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x0000000000251168));
    /* 00251164: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_00251168;
L_00251168: ;
    /* 00251168: move a0,s2 */ set(4,cpu(18));
L_0025116c: ;
    /* 0025116C: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_00251170: ;
    /* 00251170: li a1,0x3 */ set(5,UINT64_C(0x0000000000000003));
L_00251174: ;
    /* 00251174: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_00251178: ;
    /* 00251178: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_0025117c: ;
    /* 0025117C: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_00251180: ;
    /* 00251180: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_00251184: ;
    /* 00251184: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_00251188: ;
    /* 00251188: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_0025118c: ;
    /* 0025118C: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_00251190: ;
    /* 00251190: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_00251194: ;
    /* 00251194: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_00251198: ;
    /* 00251198: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_0025119c: ;
    /* 0025119C: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_002511a0: ;
    /* 002511A0: j 0x0024f5b0; native delay follows */
    /* 002511A4: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));
    body_0024f5b0();
    ba_return(incoming_ra); return;
L_002511a8: ;
    /* 002511A8: lui at,0xbf00 */ set(1,sx(UINT32_C(0xbf000000)));
L_002511ac: ;
    /* 002511AC: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_002511b0: ;
    /* 002511B0: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x00000000002511b8));
    /* 002511B4: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_002511b8;
L_002511b8: ;
    /* 002511B8: move a0,s2 */ set(4,cpu(18));
L_002511bc: ;
    /* 002511BC: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_002511c0: ;
    /* 002511C0: li a1,0x2 */ set(5,UINT64_C(0x0000000000000002));
L_002511c4: ;
    /* 002511C4: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_002511c8: ;
    /* 002511C8: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_002511cc: ;
    /* 002511CC: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_002511d0: ;
    /* 002511D0: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_002511d4: ;
    /* 002511D4: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_002511d8: ;
    /* 002511D8: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_002511dc: ;
    /* 002511DC: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_002511e0: ;
    /* 002511E0: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_002511e4: ;
    /* 002511E4: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_002511e8: ;
    /* 002511E8: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_002511ec: ;
    /* 002511EC: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_002511f0: ;
    /* 002511F0: j 0x0024f5b0; native delay follows */
    /* 002511F4: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));
    body_0024f5b0();
    ba_return(incoming_ra); return;
L_002511f8: ;
    /* 002511F8: lw a1,0x7c(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x0000007c)))));
L_002511fc: ;
    /* 002511FC: jal 0x0026a470; native delay follows */
    set(31,UINT64_C(0x0000000000251204));
    /* 00251200: move a0,s8 */ set(4,cpu(30));
    set(2,ps2CombatSameFormation_0026A470(cpu(4),cpu(5)));
    goto L_00251204;
L_00251204: ;
    /* 00251204: bne v0,zero,0x00251260; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00251208: nop  */ ;
      if(taken) goto L_00251260;
      goto L_0025120c; }
L_0025120c: ;
    /* 0025120C: lui at,0xc080 */ set(1,sx(UINT32_C(0xc0800000)));
L_00251210: ;
    /* 00251210: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00251214: ;
    /* 00251214: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x000000000025121c));
    /* 00251218: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_0025121c;
L_0025121c: ;
    /* 0025121C: move a0,s2 */ set(4,cpu(18));
L_00251220: ;
    /* 00251220: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_00251224: ;
    /* 00251224: li a1,0x6 */ set(5,UINT64_C(0x0000000000000006));
L_00251228: ;
    /* 00251228: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_0025122c: ;
    /* 0025122C: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_00251230: ;
    /* 00251230: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_00251234: ;
    /* 00251234: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_00251238: ;
    /* 00251238: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_0025123c: ;
    /* 0025123C: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_00251240: ;
    /* 00251240: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_00251244: ;
    /* 00251244: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_00251248: ;
    /* 00251248: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_0025124c: ;
    /* 0025124C: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_00251250: ;
    /* 00251250: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_00251254: ;
    /* 00251254: j 0x0024f5b0; native delay follows */
    /* 00251258: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));
    body_0024f5b0();
    ba_return(incoming_ra); return;
L_00251260: ;
    /* 00251260: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
L_00251264: ;
    /* 00251264: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00251268: ;
    /* 00251268: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x0000000000251270));
    /* 0025126C: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_00251270;
L_00251270: ;
    /* 00251270: move a0,s2 */ set(4,cpu(18));
L_00251274: ;
    /* 00251274: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_00251278: ;
    /* 00251278: move a1,zero */ set(5,cpu(0));
L_0025127c: ;
    /* 0025127C: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_00251280: ;
    /* 00251280: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_00251284: ;
    /* 00251284: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_00251288: ;
    /* 00251288: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_0025128c: ;
    /* 0025128C: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_00251290: ;
    /* 00251290: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_00251294: ;
    /* 00251294: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_00251298: ;
    /* 00251298: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_0025129c: ;
    /* 0025129C: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_002512a0: ;
    /* 002512A0: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_002512a4: ;
    /* 002512A4: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_002512a8: ;
    /* 002512A8: j 0x0024f5b0; native delay follows */
    /* 002512AC: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));
    body_0024f5b0();
    ba_return(incoming_ra); return;
L_002512b0: ;
    /* 002512B0: lw a1,0x7c(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x0000007c)))));
L_002512b4: ;
    /* 002512B4: jal 0x0026a470; native delay follows */
    set(31,UINT64_C(0x00000000002512bc));
    /* 002512B8: move a0,s8 */ set(4,cpu(30));
    set(2,ps2CombatSameFormation_0026A470(cpu(4),cpu(5)));
    goto L_002512bc;
L_002512bc: ;
    /* 002512BC: bne v0,zero,0x00251318; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 002512C0: nop  */ ;
      if(taken) goto L_00251318;
      goto L_002512c4; }
L_002512c4: ;
    /* 002512C4: lui at,0xc080 */ set(1,sx(UINT32_C(0xc0800000)));
L_002512c8: ;
    /* 002512C8: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_002512cc: ;
    /* 002512CC: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x00000000002512d4));
    /* 002512D0: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_002512d4;
L_002512d4: ;
    /* 002512D4: move a0,s2 */ set(4,cpu(18));
L_002512d8: ;
    /* 002512D8: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_002512dc: ;
    /* 002512DC: li a1,0x7 */ set(5,UINT64_C(0x0000000000000007));
L_002512e0: ;
    /* 002512E0: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_002512e4: ;
    /* 002512E4: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_002512e8: ;
    /* 002512E8: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_002512ec: ;
    /* 002512EC: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_002512f0: ;
    /* 002512F0: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_002512f4: ;
    /* 002512F4: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_002512f8: ;
    /* 002512F8: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_002512fc: ;
    /* 002512FC: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_00251300: ;
    /* 00251300: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_00251304: ;
    /* 00251304: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_00251308: ;
    /* 00251308: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_0025130c: ;
    /* 0025130C: j 0x0024f5b0; native delay follows */
    /* 00251310: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));
    body_0024f5b0();
    ba_return(incoming_ra); return;
L_00251318: ;
    /* 00251318: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
L_0025131c: ;
    /* 0025131C: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00251320: ;
    /* 00251320: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x0000000000251328));
    /* 00251324: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_00251328;
L_00251328: ;
    /* 00251328: move a0,s2 */ set(4,cpu(18));
L_0025132c: ;
    /* 0025132C: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_00251330: ;
    /* 00251330: move a1,zero */ set(5,cpu(0));
L_00251334: ;
    /* 00251334: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_00251338: ;
    /* 00251338: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_0025133c: ;
    /* 0025133C: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_00251340: ;
    /* 00251340: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_00251344: ;
    /* 00251344: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_00251348: ;
    /* 00251348: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_0025134c: ;
    /* 0025134C: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_00251350: ;
    /* 00251350: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_00251354: ;
    /* 00251354: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_00251358: ;
    /* 00251358: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_0025135c: ;
    /* 0025135C: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_00251360: ;
    /* 00251360: j 0x0024f5b0; native delay follows */
    /* 00251364: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));
    body_0024f5b0();
    ba_return(incoming_ra); return;
L_00251368: ;
    /* 00251368: lw a1,0x7c(sp) */ set(5,sx(r32(ea(cpu(29),UINT32_C(0x0000007c)))));
L_0025136c: ;
    /* 0025136C: jal 0x0026a470; native delay follows */
    set(31,UINT64_C(0x0000000000251374));
    /* 00251370: move a0,s8 */ set(4,cpu(30));
    set(2,ps2CombatSameFormation_0026A470(cpu(4),cpu(5)));
    goto L_00251374;
L_00251374: ;
    /* 00251374: bne v0,zero,0x002513d0; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00251378: nop  */ ;
      if(taken) goto L_002513d0;
      goto L_0025137c; }
L_0025137c: ;
    /* 0025137C: lui at,0xc000 */ set(1,sx(UINT32_C(0xc0000000)));
L_00251380: ;
    /* 00251380: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00251384: ;
    /* 00251384: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x000000000025138c));
    /* 00251388: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_0025138c;
L_0025138c: ;
    /* 0025138C: move a0,s2 */ set(4,cpu(18));
L_00251390: ;
    /* 00251390: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_00251394: ;
    /* 00251394: li a1,0x5 */ set(5,UINT64_C(0x0000000000000005));
L_00251398: ;
    /* 00251398: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_0025139c: ;
    /* 0025139C: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_002513a0: ;
    /* 002513A0: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_002513a4: ;
    /* 002513A4: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_002513a8: ;
    /* 002513A8: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_002513ac: ;
    /* 002513AC: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_002513b0: ;
    /* 002513B0: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_002513b4: ;
    /* 002513B4: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_002513b8: ;
    /* 002513B8: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_002513bc: ;
    /* 002513BC: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_002513c0: ;
    /* 002513C0: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_002513c4: ;
    /* 002513C4: j 0x0024f5b0; native delay follows */
    /* 002513C8: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100)));
    body_0024f5b0();
    ba_return(incoming_ra); return;
L_002513d0: ;
    /* 002513D0: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
L_002513d4: ;
    /* 002513D4: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_002513d8: ;
    /* 002513D8: jal 0x0024f548; native delay follows */
    set(31,UINT64_C(0x00000000002513e0));
    /* 002513DC: move a0,s2 */ set(4,cpu(18));
    body_0024f548();
    goto L_002513e0;
L_002513e0: ;
    /* 002513E0: move a0,s2 */ set(4,cpu(18));
L_002513e4: ;
    /* 002513E4: jal 0x0024f5b0; native delay follows */
    set(31,UINT64_C(0x00000000002513ec));
    /* 002513E8: move a1,zero */ set(5,cpu(0));
    body_0024f5b0();
    goto L_002513ec;
L_002513ec: ;
    /* 002513EC: ld s0,0xa0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x000000a0))));
L_002513f0: ;
    /* 002513F0: ld s1,0xa8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x000000a8))));
L_002513f4: ;
    /* 002513F4: ld s2,0xb0(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x000000b0))));
L_002513f8: ;
    /* 002513F8: ld s3,0xb8(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x000000b8))));
L_002513fc: ;
    /* 002513FC: ld s4,0xc0(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x000000c0))));
L_00251400: ;
    /* 00251400: ld s5,0xc8(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x000000c8))));
L_00251404: ;
    /* 00251404: ld s6,0xd0(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x000000d0))));
L_00251408: ;
    /* 00251408: ld s7,0xd8(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x000000d8))));
L_0025140c: ;
    /* 0025140C: ld s8,0xe0(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x000000e0))));
L_00251410: ;
    /* 00251410: ld ra,0xe8(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x000000e8))));
L_00251414: ;
    /* 00251414: lwc1 f21,0xf8(sp) */ fpr()[21]=r32(ea(cpu(29),UINT32_C(0x000000f8)));
L_00251418: ;
    /* 00251418: lwc1 f20,0xf0(sp) */ fpr()[20]=r32(ea(cpu(29),UINT32_C(0x000000f0)));
L_0025141c: ;
    /* 0025141C: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00251420: addiu sp,sp,0x100 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000100))); ba_return_target(incoming_ra,target); return; }
}

static void body_00251750(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00251750u);
L_00251750: ;
    /* 00251750: sll a1,a1,0x3 */ set(5,sx(((uint32_t)cpu(5)<<3)));
L_00251754: ;
    /* 00251754: addu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
L_00251758: ;
    /* 00251758: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 0025175C: lhu v0,0x88(a1) */ set(2,r16(ea(cpu(5),UINT32_C(0x00000088)))); ba_return_target(incoming_ra,target); return; }
}

static void body_002521c8(void)
{
    uint64_t incoming_ra=cpu(31);
    uint32_t lo=0;
    nocturneEffectAxisNoteEntry(0x002521c8u);
L_002521c8: ;
    /* 002521C8: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
L_002521cc: ;
    /* 002521CC: lui v0,0x54 */ set(2,sx(UINT32_C(0x00540000)));
L_002521d0: ;
    /* 002521D0: sd s8,0x70(sp) */ w64(ea(cpu(29),UINT32_C(0x00000070)),(uint64_t)cpu(30));
L_002521d4: ;
    /* 002521D4: move s8,a2 */ set(30,cpu(6));
L_002521d8: ;
    /* 002521D8: sd s7,0x68(sp) */ w64(ea(cpu(29),UINT32_C(0x00000068)),(uint64_t)cpu(23));
L_002521dc: ;
    /* 002521DC: move s7,a1 */ set(23,cpu(5));
L_002521e0: ;
    /* 002521E0: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
L_002521e4: ;
    /* 002521E4: sd s0,0x30(sp) */ w64(ea(cpu(29),UINT32_C(0x00000030)),(uint64_t)cpu(16));
L_002521e8: ;
    /* 002521E8: sd s1,0x38(sp) */ w64(ea(cpu(29),UINT32_C(0x00000038)),(uint64_t)cpu(17));
L_002521ec: ;
    /* 002521EC: sd s2,0x40(sp) */ w64(ea(cpu(29),UINT32_C(0x00000040)),(uint64_t)cpu(18));
L_002521f0: ;
    /* 002521F0: sd s3,0x48(sp) */ w64(ea(cpu(29),UINT32_C(0x00000048)),(uint64_t)cpu(19));
L_002521f4: ;
    /* 002521F4: sd s4,0x50(sp) */ w64(ea(cpu(29),UINT32_C(0x00000050)),(uint64_t)cpu(20));
L_002521f8: ;
    /* 002521F8: sd s5,0x58(sp) */ w64(ea(cpu(29),UINT32_C(0x00000058)),(uint64_t)cpu(21));
L_002521fc: ;
    /* 002521FC: sd s6,0x60(sp) */ w64(ea(cpu(29),UINT32_C(0x00000060)),(uint64_t)cpu(22));
L_00252200: ;
    /* 00252200: sd ra,0x78(sp) */ w64(ea(cpu(29),UINT32_C(0x00000078)),(uint64_t)cpu(31));
L_00252204: ;
    /* 00252204: addiu t1,v0,0x38a0 */ set(9,sx((uint32_t)cpu(2)+UINT32_C(0x000038a0)));
L_00252208: ;
    /* 00252208: ldl a2,0x7(t1) */ set(6,ldl(cpu(6),ea(cpu(9),UINT32_C(0x00000007))));
L_0025220c: ;
    /* 0025220C: ldr a2,0x0(t1) */ set(6,ldr(cpu(6),ea(cpu(9),UINT32_C(0x00000000))));
L_00252210: ;
    /* 00252210: ldl a3,0xf(t1) */ set(7,ldl(cpu(7),ea(cpu(9),UINT32_C(0x0000000f))));
L_00252214: ;
    /* 00252214: ldr a3,0x8(t1) */ set(7,ldr(cpu(7),ea(cpu(9),UINT32_C(0x00000008))));
L_00252218: ;
    /* 00252218: sdl a2,0x7(sp) */ sdl(ea(cpu(29),UINT32_C(0x00000007)),cpu(6));
L_0025221c: ;
    /* 0025221C: sdr a2,0x0(sp) */ sdr(ea(cpu(29),UINT32_C(0x00000000)),cpu(6));
L_00252220: ;
    /* 00252220: sdl a3,0xf(sp) */ sdl(ea(cpu(29),UINT32_C(0x0000000f)),cpu(7));
L_00252224: ;
    /* 00252224: sdr a3,0x8(sp) */ sdr(ea(cpu(29),UINT32_C(0x00000008)),cpu(7));
L_00252228: ;
    /* 00252228: sw a0,0x20(sp) */ w32(ea(cpu(29),UINT32_C(0x00000020)),(uint32_t)cpu(4));
L_0025222c: ;
    /* 0025222C: addiu t0,v1,0x38b0 */ set(8,sx((uint32_t)cpu(3)+UINT32_C(0x000038b0)));
L_00252230: ;
    /* 00252230: ldl v0,0x7(t0) */ set(2,ldl(cpu(2),ea(cpu(8),UINT32_C(0x00000007))));
L_00252234: ;
    /* 00252234: ldr v0,0x0(t0) */ set(2,ldr(cpu(2),ea(cpu(8),UINT32_C(0x00000000))));
L_00252238: ;
    /* 00252238: lw a2,0x8(t0) */ set(6,sx(r32(ea(cpu(8),UINT32_C(0x00000008)))));
L_0025223c: ;
    /* 0025223C: sdl v0,0x17(sp) */ sdl(ea(cpu(29),UINT32_C(0x00000017)),cpu(2));
L_00252240: ;
    /* 00252240: sdr v0,0x10(sp) */ sdr(ea(cpu(29),UINT32_C(0x00000010)),cpu(2));
L_00252244: ;
    /* 00252244: sw a2,0x18(sp) */ w32(ea(cpu(29),UINT32_C(0x00000018)),(uint32_t)cpu(6));
L_00252248: ;
    /* 00252248: jal 0x002515e8; native delay follows */
    set(31,UINT64_C(0x0000000000252250));
    /* 0025224C: move a1,s8 */ set(5,cpu(30));
    set(2,nbActionCheckTimeListDead(cpu(4),cpu(5)));
    goto L_00252250;
L_00252250: ;
    /* 00252250: bnel v0,zero,0x002523d0; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      if(taken) { /* 00252254: move v0,zero */ set(2,cpu(0)); goto L_002523d0; }
      goto L_00252258; }
L_00252258: ;
    /* 00252258: jal 0x00246ab8; native delay follows */
    set(31,UINT64_C(0x0000000000252260));
    /* 0025225C: move a0,s7 */ set(4,cpu(23));
    set(2,nbGetUnitWorkFromFormindex(cpu(4)));
    goto L_00252260;
L_00252260: ;
    /* 00252260: li v1,0x10 */ set(3,UINT64_C(0x0000000000000010));
L_00252264: ;
    /* 00252264: move s6,v0 */ set(22,cpu(2));
L_00252268: ;
    /* 00252268: lhu v0,0xe(s6) */ set(2,r16(ea(cpu(22),UINT32_C(0x0000000e))));
L_0025226c: ;
    /* 0025226C: andi a0,v0,0xfff */ set(4,cpu(2)&UINT64_C(0x0000000000000fff));
L_00252270: ;
    /* 00252270: beq a0,v1,0x002523d0; native delay follows */
    { int taken=(cpu(4)==cpu(3));
      /* 00252274: move v0,zero */ set(2,cpu(0));
      if(taken) goto L_002523d0;
      goto L_00252278; }
L_00252278: ;
    /* 00252278: slti v0,a0,0x11 */ set(2,lt(cpu(4),UINT64_C(0x0000000000000011)));
L_0025227c: ;
    /* 0025227C: beq v0,zero,0x002522b0; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00252280: li v0,0x100 */ set(2,UINT64_C(0x0000000000000100));
      if(taken) goto L_002522b0;
      goto L_00252284; }
L_00252284: ;
    /* 00252284: beq a0,zero,0x002522f8; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      /* 00252288: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000)))));
      if(taken) goto L_002522f8;
      goto L_0025228c; }
L_0025228c: ;
    /* 0025228C: slti v0,a0,0x3 */ set(2,lt(cpu(4),UINT64_C(0x0000000000000003)));
L_00252290: ;
    /* 00252290: bne v0,zero,0x002523d0; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00252294: move v0,zero */ set(2,cpu(0));
      if(taken) goto L_002523d0;
      goto L_00252298; }
L_00252298: ;
    /* 00252298: li v0,0x4 */ set(2,UINT64_C(0x0000000000000004));
L_0025229c: ;
    /* 0025229C: beql a0,v0,0x002523d0; native delay follows */
    { int taken=(cpu(4)==cpu(2));
      if(taken) { /* 002522A0: move v0,zero */ set(2,cpu(0)); goto L_002523d0; }
      goto L_002522a4; }
L_002522a4: ;
    /* 002522A4: b 0x002522f8; native delay follows */
    { /* 002522A8: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000))))); goto L_002522f8; }
L_002522b0: ;
    /* 002522B0: beq a0,v0,0x002523d0; native delay follows */
    { int taken=(cpu(4)==cpu(2));
      /* 002522B4: move v0,zero */ set(2,cpu(0));
      if(taken) goto L_002523d0;
      goto L_002522b8; }
L_002522b8: ;
    /* 002522B8: slti v0,a0,0x101 */ set(2,lt(cpu(4),UINT64_C(0x0000000000000101)));
L_002522bc: ;
    /* 002522BC: beq v0,zero,0x002522d8; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 002522C0: li v0,0x400 */ set(2,UINT64_C(0x0000000000000400));
      if(taken) goto L_002522d8;
      goto L_002522c4; }
L_002522c4: ;
    /* 002522C4: li v0,0x80 */ set(2,UINT64_C(0x0000000000000080));
L_002522c8: ;
    /* 002522C8: beql a0,v0,0x002523d0; native delay follows */
    { int taken=(cpu(4)==cpu(2));
      if(taken) { /* 002522CC: move v0,zero */ set(2,cpu(0)); goto L_002523d0; }
      goto L_002522d0; }
L_002522d0: ;
    /* 002522D0: b 0x002522f8; native delay follows */
    { /* 002522D4: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000))))); goto L_002522f8; }
L_002522d8: ;
    /* 002522D8: bnel a0,v0,0x002522f8; native delay follows */
    { int taken=(cpu(4)!=cpu(2));
      if(taken) { /* 002522DC: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000))))); goto L_002522f8; }
      goto L_002522e0; }
L_002522e0: ;
    /* 002522E0: b 0x002523d0; native delay follows */
    { /* 002522E4: move v0,zero */ set(2,cpu(0)); goto L_002523d0; }
L_002522e8: ;
    /* 002522E8: addu v0,t1,s5 */ set(2,sx((uint32_t)cpu(9)+(uint32_t)cpu(21)));
L_002522ec: ;
    /* 002522EC: b 0x00252378; native delay follows */
    { /* 002522F0: lw s4,0x0(v0) */ set(20,sx(r32(ea(cpu(2),UINT32_C(0x00000000))))); goto L_00252378; }
L_002522f8: ;
    /* 002522F8: bltz v0,0x00252378; native delay follows */
    { int taken=(lt(cpu(2),0));
      /* 002522FC: move s4,zero */ set(20,cpu(0));
      if(taken) goto L_00252378;
      goto L_00252300; }
L_00252300: ;
    /* 00252300: move s5,zero */ set(21,cpu(0));
L_00252304: ;
    /* 00252304: li s3,0x64 */ set(19,UINT64_C(0x0000000000000064));
L_00252308: ;
    /* 00252308: move s2,zero */ set(18,cpu(0));
L_0025230c: ;
    /* 0025230C: move s1,sp */ set(17,cpu(29));
L_00252310: ;
    /* 00252310: lw a1,0x0(s1) */ set(5,sx(r32(ea(cpu(17),UINT32_C(0x00000000)))));
L_00252314: ;
    /* 00252314: jal 0x00243f40; native delay follows */
    set(31,UINT64_C(0x000000000025231c));
    /* 00252318: move a0,s6 */ set(4,cpu(22));
    set(2,sx((uint32_t)datCheckSyojiSkill((datUnitWork_PS2 *)at((uint32_t)cpu(4)),i32((uint32_t)cpu(5)))));
    goto L_0025231c;
L_0025231c: ;
    /* 0025231C: move a0,zero */ set(4,cpu(0));
L_00252320: ;
    /* 00252320: beq v0,zero,0x00252364; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00252324: li a1,0x64 */ set(5,UINT64_C(0x0000000000000064));
      if(taken) goto L_00252364;
      goto L_00252328; }
L_00252328: ;
    /* 00252328: lw v0,0x0(s1) */ set(2,sx(r32(ea(cpu(17),UINT32_C(0x00000000)))));
L_0025232c: ;
    /* 0025232C: lui v1,0x3e */ set(3,sx(UINT32_C(0x003e0000)));
L_00252330: ;
    /* 00252330: addiu v1,v1,-0x3e60 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffc1a0)));
L_00252334: ;
    /* 00252334: sll v0,v0,0x3 */ set(2,sx(((uint32_t)cpu(2)<<3)));
L_00252338: ;
    /* 00252338: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
L_0025233c: ;
    /* 0025233C: lh v1,-0x900(v0) */ set(3,sx((uint32_t)i16(r16(ea(cpu(2),UINT32_C(0xfffff700))))));
L_00252340: ;
    /* 00252340: div s3,v1 */ lo=divs((uint32_t)cpu(19),(uint32_t)cpu(3));
L_00252344: ;
    /* 00252344: beql v1,zero,0x0025234c; native delay follows */
    { int taken=(cpu(3)==cpu(0));
      if(taken) { /* 00252348: break 0x7 */ nocturneCompilerArithmeticTrap(7); goto L_0025234c; }
      goto L_0025234c; }
L_0025234c: ;
    /* 0025234C: mflo s0 */ set(16,sx(lo));
L_00252350: ;
    /* 00252350: jal 0x002c0c60; native delay follows */
    set(31,UINT64_C(0x0000000000252358));
    /* 00252354: nop  */ ;
    set(2,sx((uint32_t)sdfGetRandInt((cpu(4)?(uint32_t *)at((uint32_t)cpu(4)):NULL),i32((uint32_t)cpu(5)))));
    goto L_00252358;
L_00252358: ;
    /* 00252358: slt v0,v0,s0 */ set(2,lt(cpu(2),cpu(16)));
L_0025235c: ;
    /* 0025235C: bne v0,zero,0x002522e8; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 00252360: addiu t1,sp,0x10 */ set(9,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
      if(taken) goto L_002522e8;
      goto L_00252364; }
L_00252364: ;
    /* 00252364: addiu s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
L_00252368: ;
    /* 00252368: addiu s2,s2,0x4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000004)));
L_0025236c: ;
    /* 0025236C: lw v0,0x0(s1) */ set(2,sx(r32(ea(cpu(17),UINT32_C(0x00000000)))));
L_00252370: ;
    /* 00252370: bgez v0,0x00252310; native delay follows */
    { int taken=(!lt(cpu(2),0));
      /* 00252374: move s5,s2 */ set(21,cpu(18));
      if(taken) goto L_00252310;
      goto L_00252378; }
L_00252378: ;
    /* 00252378: beq s4,zero,0x002523d0; native delay follows */
    { int taken=(cpu(20)==cpu(0));
      /* 0025237C: move v0,zero */ set(2,cpu(0));
      if(taken) goto L_002523d0;
      goto L_00252380; }
L_00252380: ;
    /* 00252380: lw v0,0x20(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000020)))));
L_00252384: ;
    /* 00252384: sll v1,s8,0x4 */ set(3,sx(((uint32_t)cpu(30)<<4)));
L_00252388: ;
    /* 00252388: subu v1,v1,s8 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(30)));
L_0025238c: ;
    /* 0025238C: move a3,s4 */ set(7,cpu(20));
L_00252390: ;
    /* 00252390: lw a1,0x0(v0) */ set(5,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_00252394: ;
    /* 00252394: sll v0,s7,0x4 */ set(2,sx(((uint32_t)cpu(23)<<4)));
L_00252398: ;
    /* 00252398: subu v0,v0,s7 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(23)));
L_0025239c: ;
    /* 0025239C: sll v1,v1,0x4 */ set(3,sx(((uint32_t)cpu(3)<<4)));
L_002523a0: ;
    /* 002523A0: lw a0,0x0(a1) */ set(4,sx(r32(ea(cpu(5),UINT32_C(0x00000000)))));
L_002523a4: ;
    /* 002523A4: sll v0,v0,0x4 */ set(2,sx(((uint32_t)cpu(2)<<4)));
L_002523a8: ;
    /* 002523A8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
L_002523ac: ;
    /* 002523AC: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
L_002523b0: ;
    /* 002523B0: lh a1,0x90(v0) */ set(5,sx((uint32_t)i16(r16(ea(cpu(2),UINT32_C(0x00000090))))));
L_002523b4: ;
    /* 002523B4: li a0,0x4 */ set(4,UINT64_C(0x0000000000000004));
L_002523b8: ;
    /* 002523B8: jal 0x00247ed8; native delay follows */
    set(31,UINT64_C(0x00000000002523c0));
    /* 002523BC: lh a2,0x90(v1) */ set(6,sx((uint32_t)i16(r16(ea(cpu(3),UINT32_C(0x00000090))))));
    nbPushAction(cpu(4),cpu(5),cpu(6),cpu(7));
    goto L_002523c0;
L_002523c0: ;
    /* 002523C0: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
L_002523c4: ;
    /* 002523C4: jal 0x002d4748; native delay follows */
    set(31,UINT64_C(0x00000000002523cc));
    /* 002523C8: addiu a0,a0,0x38c0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000038c0)));
    set(2,ps2LibcPrintf(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10),cpu(11)));
    goto L_002523cc;
L_002523cc: ;
    /* 002523CC: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_002523d0: ;
    /* 002523D0: ld s0,0x30(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000030))));
L_002523d4: ;
    /* 002523D4: ld s1,0x38(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000038))));
L_002523d8: ;
    /* 002523D8: ld s2,0x40(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000040))));
L_002523dc: ;
    /* 002523DC: ld s3,0x48(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000048))));
L_002523e0: ;
    /* 002523E0: ld s4,0x50(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x00000050))));
L_002523e4: ;
    /* 002523E4: ld s5,0x58(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x00000058))));
L_002523e8: ;
    /* 002523E8: ld s6,0x60(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x00000060))));
L_002523ec: ;
    /* 002523EC: ld s7,0x68(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x00000068))));
L_002523f0: ;
    /* 002523F0: ld s8,0x70(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x00000070))));
L_002523f4: ;
    /* 002523F4: ld ra,0x78(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000078))));
L_002523f8: ;
    /* 002523F8: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 002523FC: addiu sp,sp,0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080))); ba_return_target(incoming_ra,target); return; }
}

static void body_002592b0(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x002592b0u);
L_002592b0: ;
    /* 002592B0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
L_002592b4: ;
    /* 002592B4: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_002592b8: ;
    /* 002592B8: move s0,a0 */ set(16,cpu(4));
L_002592bc: ;
    /* 002592BC: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_002592c0: ;
    /* 002592C0: move s1,a3 */ set(17,cpu(7));
L_002592c4: ;
    /* 002592C4: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_002592c8: ;
    /* 002592C8: move s2,a2 */ set(18,cpu(6));
L_002592cc: ;
    /* 002592CC: sd ra,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(31));
L_002592d0: ;
    /* 002592D0: jal 0x00259300; native delay follows */
    set(31,UINT64_C(0x00000000002592d8));
    /* 002592D4: lw a0,0x0(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000000)))));
    body_00259300();
    goto L_002592d8;
L_002592d8: ;
    /* 002592D8: sw s2,0x4c(s0) */ w32(ea(cpu(16),UINT32_C(0x0000004c)),(uint32_t)cpu(18));
L_002592dc: ;
    /* 002592DC: sw s1,0x50(s0) */ w32(ea(cpu(16),UINT32_C(0x00000050)),(uint32_t)cpu(17));
L_002592e0: ;
    /* 002592E0: sw v0,0x48(s0) */ w32(ea(cpu(16),UINT32_C(0x00000048)),(uint32_t)cpu(2));
L_002592e4: ;
    /* 002592E4: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_002592e8: ;
    /* 002592E8: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_002592ec: ;
    /* 002592EC: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_002592f0: ;
    /* 002592F0: ld ra,0x18(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_002592f4: ;
    /* 002592F4: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 002592F8: addiu sp,sp,0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020))); ba_return_target(incoming_ra,target); return; }
}

static void body_00259300(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00259300u);
L_00259300: ;
    /* 00259300: lw v1,0x60(a0) */ set(3,sx(r32(ea(cpu(4),UINT32_C(0x00000060)))));
L_00259304: ;
    /* 00259304: addiu v0,a1,0x1 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
L_00259308: ;
    /* 00259308: andi v1,v1,0x8 */ set(3,cpu(3)&UINT64_C(0x0000000000000008));
L_0025930c: ;
    /* 0025930C: xori v1,v1,0x0 */ set(3,cpu(3)^UINT64_C(0x0000000000000000));
L_00259310: ;
    /* 00259310: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00259314: movz v0,a1,v1 */ if(cpu(3)==0) set(2,cpu(5)); ba_return_target(incoming_ra,target); return; }
}

static void body_00262480(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00262480u);
L_00262480: ;
    /* 00262480: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
L_00262484: ;
    /* 00262484: move v0,zero */ set(2,cpu(0));
L_00262488: ;
    /* 00262488: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_0026248c: ;
    /* 0026248C: move s0,zero */ set(16,cpu(0));
L_00262490: ;
    /* 00262490: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00262494: ;
    /* 00262494: move s1,a3 */ set(17,cpu(7));
L_00262498: ;
    /* 00262498: sd s3,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(19));
L_0026249c: ;
    /* 0026249C: move s3,a2 */ set(19,cpu(6));
L_002624a0: ;
    /* 002624A0: sd s4,0x20(sp) */ w64(ea(cpu(29),UINT32_C(0x00000020)),(uint64_t)cpu(20));
L_002624a4: ;
    /* 002624A4: move s4,a1 */ set(20,cpu(5));
L_002624a8: ;
    /* 002624A8: sd s5,0x28(sp) */ w64(ea(cpu(29),UINT32_C(0x00000028)),(uint64_t)cpu(21));
L_002624ac: ;
    /* 002624AC: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_002624b0: ;
    /* 002624B0: sd ra,0x30(sp) */ w64(ea(cpu(29),UINT32_C(0x00000030)),(uint64_t)cpu(31));
L_002624b4: ;
    /* 002624B4: lw v1,0x78(s3) */ set(3,sx(r32(ea(cpu(19),UINT32_C(0x00000078)))));
L_002624b8: ;
    /* 002624B8: andi v1,v1,0x1 */ set(3,cpu(3)&UINT64_C(0x0000000000000001));
L_002624bc: ;
    /* 002624BC: beq v1,zero,0x002625e8; native delay follows */
    { int taken=(cpu(3)==cpu(0));
      /* 002624C0: move s5,a0 */ set(21,cpu(4));
      if(taken) goto L_002625e8;
      goto L_002624c4; }
L_002624c4: ;
    /* 002624C4: jal 0x0025e8e0; native delay follows */
    set(31,UINT64_C(0x00000000002624cc));
    /* 002624C8: nop  */ ;
    set(2,nbGetKoukaProcessData());
    goto L_002624cc;
L_002624cc: ;
    /* 002624CC: move a1,s5 */ set(5,cpu(21));
L_002624d0: ;
    /* 002624D0: move a0,v0 */ set(4,cpu(2));
L_002624d4: ;
    /* 002624D4: move a2,zero */ set(6,cpu(0));
L_002624d8: ;
    /* 002624D8: jal 0x0025ea48; native delay follows */
    set(31,UINT64_C(0x00000000002624e0));
    /* 002624DC: move a3,s4 */ set(7,cpu(20));
    set(2,nbAddKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_002624e0;
L_002624e0: ;
    /* 002624E0: li v1,0xf */ set(3,UINT64_C(0x000000000000000f));
L_002624e4: ;
    /* 002624E4: move s2,v0 */ set(18,cpu(2));
L_002624e8: ;
    /* 002624E8: sltiu a0,s1,0xb */ set(4,(cpu(17)<UINT64_C(0x000000000000000b)));
L_002624ec: ;
    /* 002624EC: sb v1,0x4(s2) */ w8(ea(cpu(18),UINT32_C(0x00000004)),(uint8_t)cpu(3));
L_002624f0: ;
    /* 002624F0: sw s3,0x14(s2) */ w32(ea(cpu(18),UINT32_C(0x00000014)),(uint32_t)cpu(19));
L_002624f4: ;
    /* 002624F4: beq a0,zero,0x002625e8; native delay follows */
    { int taken=(cpu(4)==cpu(0));
      /* 002624F8: sw s1,0x28(s2) */ w32(ea(cpu(18),UINT32_C(0x00000028)),(uint32_t)cpu(17));
      if(taken) goto L_002625e8;
      goto L_002624fc; }
L_002624fc: ;
    /* 002624FC: sll v0,s1,0x2 */ set(2,sx(((uint32_t)cpu(17)<<2)));
L_00262500: ;
    /* 00262500: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
L_00262504: ;
    /* 00262504: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
L_00262508: ;
    /* 00262508: lw v1,0x4910(v1) */ set(3,sx(r32(ea(cpu(3),UINT32_C(0x00004910)))));
L_0026250c: ;
    /* 0026250C: jr v1; native delay follows */
    { uint64_t target=cpu(3); /* 00262510: nop  */ ; switch((uint32_t)target) {
      case 0x00262518u: goto L_00262518;
      case 0x00262520u: goto L_00262520;
      case 0x00262528u: goto L_00262528;
      case 0x00262538u: goto L_00262538;
      case 0x00262548u: goto L_00262548;
      case 0x00262558u: goto L_00262558;
      case 0x00262568u: goto L_00262568;
      case 0x00262570u: goto L_00262570;
      case 0x00262578u: goto L_00262578;
      case 0x00262588u: goto L_00262588;
      case 0x00262598u: goto L_00262598;
      default: abort(); } }
L_00262518: ;
    /* 00262518: b 0x002625a4; native delay follows */
    { /* 0026251C: li a1,0x18 */ set(5,UINT64_C(0x0000000000000018)); goto L_002625a4; }
L_00262520: ;
    /* 00262520: b 0x002625a4; native delay follows */
    { /* 00262524: li a1,0x19 */ set(5,UINT64_C(0x0000000000000019)); goto L_002625a4; }
L_00262528: ;
    /* 00262528: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
L_0026252c: ;
    /* 0026252C: li a1,0x11 */ set(5,UINT64_C(0x0000000000000011));
L_00262530: ;
    /* 00262530: b 0x002625a4; native delay follows */
    { /* 00262534: ori s0,s0,0x8 */ set(16,cpu(16)|UINT64_C(0x0000000000000008)); goto L_002625a4; }
L_00262538: ;
    /* 00262538: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
L_0026253c: ;
    /* 0026253C: li a1,0x12 */ set(5,UINT64_C(0x0000000000000012));
L_00262540: ;
    /* 00262540: b 0x002625a4; native delay follows */
    { /* 00262544: ori s0,s0,0x9 */ set(16,cpu(16)|UINT64_C(0x0000000000000009)); goto L_002625a4; }
L_00262548: ;
    /* 00262548: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
L_0026254c: ;
    /* 0026254C: li a1,0x1a */ set(5,UINT64_C(0x000000000000001a));
L_00262550: ;
    /* 00262550: b 0x002625a4; native delay follows */
    { /* 00262554: ori s0,s0,0x1 */ set(16,cpu(16)|UINT64_C(0x0000000000000001)); goto L_002625a4; }
L_00262558: ;
    /* 00262558: li a1,0x14 */ set(5,UINT64_C(0x0000000000000014));
L_0026255c: ;
    /* 0026255C: b 0x002625a4; native delay follows */
    { /* 00262560: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000))); goto L_002625a4; }
L_00262568: ;
    /* 00262568: b 0x002625a4; native delay follows */
    { /* 0026256C: li a1,0xe */ set(5,UINT64_C(0x000000000000000e)); goto L_002625a4; }
L_00262570: ;
    /* 00262570: b 0x002625e4; native delay follows */
    { /* 00262574: sh zero,0x2(s2) */ w16(ea(cpu(18),UINT32_C(0x00000002)),(uint16_t)cpu(0)); goto L_002625e4; }
L_00262578: ;
    /* 00262578: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
L_0026257c: ;
    /* 0026257C: li a1,0x1b */ set(5,UINT64_C(0x000000000000001b));
L_00262580: ;
    /* 00262580: b 0x002625a4; native delay follows */
    { /* 00262584: ori s0,s0,0x5 */ set(16,cpu(16)|UINT64_C(0x0000000000000005)); goto L_002625a4; }
L_00262588: ;
    /* 00262588: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
L_0026258c: ;
    /* 0026258C: li a1,0x1c */ set(5,UINT64_C(0x000000000000001c));
L_00262590: ;
    /* 00262590: b 0x002625a4; native delay follows */
    { /* 00262594: ori s0,s0,0x7 */ set(16,cpu(16)|UINT64_C(0x0000000000000007)); goto L_002625a4; }
L_00262598: ;
    /* 00262598: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
L_0026259c: ;
    /* 0026259C: li a1,0x1d */ set(5,UINT64_C(0x000000000000001d));
L_002625a0: ;
    /* 002625A0: ori s0,s0,0x6 */ set(16,cpu(16)|UINT64_C(0x0000000000000006));
L_002625a4: ;
    /* 002625A4: jal 0x00173cb0; native delay follows */
    set(31,UINT64_C(0x00000000002625ac));
    /* 002625A8: move a0,s3 */ set(4,cpu(19));
    body_00173cb0();
    goto L_002625ac;
L_002625ac: ;
    /* 002625AC: sw v0,0x2c(s2) */ w32(ea(cpu(18),UINT32_C(0x0000002c)),(uint32_t)cpu(2));
L_002625b0: ;
    /* 002625B0: jal 0x00173ef0; native delay follows */
    set(31,UINT64_C(0x00000000002625b8));
    /* 002625B4: move a0,v0 */ set(4,cpu(2));
    body_00173ef0();
    goto L_002625b8;
L_002625b8: ;
    /* 002625B8: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
L_002625bc: ;
    /* 002625BC: sll a1,v0,0x10 */ set(5,sx(((uint32_t)cpu(2)<<16)));
L_002625c0: ;
    /* 002625C0: sh v0,0x2(s2) */ w16(ea(cpu(18),UINT32_C(0x00000002)),(uint16_t)cpu(2));
L_002625c4: ;
    /* 002625C4: addiu a0,a0,0x4900 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004900)));
L_002625c8: ;
    /* 002625C8: jal 0x002d4748; native delay follows */
    set(31,UINT64_C(0x00000000002625d0));
    /* 002625CC: sra a1,a1,0x10 */ set(5,sx(asr((uint32_t)cpu(5),16)));
    set(2,ps2LibcPrintf(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10),cpu(11)));
    goto L_002625d0;
L_002625d0: ;
    /* 002625D0: beq s0,zero,0x002625e4; native delay follows */
    { int taken=(cpu(16)==cpu(0));
      /* 002625D4: move a0,s5 */ set(4,cpu(21));
      if(taken) goto L_002625e4;
      goto L_002625d8; }
L_002625d8: ;
    /* 002625D8: move a1,s4 */ set(5,cpu(20));
L_002625dc: ;
    /* 002625DC: jal 0x00262cc0; native delay follows */
    set(31,UINT64_C(0x00000000002625e4));
    /* 002625E0: move a2,s0 */ set(6,cpu(16));
    set(2,nbAddSePacket(cpu(4),cpu(5),cpu(6)));
    goto L_002625e4;
L_002625e4: ;
    /* 002625E4: move v0,s2 */ set(2,cpu(18));
L_002625e8: ;
    /* 002625E8: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_002625ec: ;
    /* 002625EC: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_002625f0: ;
    /* 002625F0: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_002625f4: ;
    /* 002625F4: ld s3,0x18(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_002625f8: ;
    /* 002625F8: ld s4,0x20(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x00000020))));
L_002625fc: ;
    /* 002625FC: ld s5,0x28(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x00000028))));
L_00262600: ;
    /* 00262600: ld ra,0x30(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000030))));
L_00262604: ;
    /* 00262604: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00262608: addiu sp,sp,0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040))); ba_return_target(incoming_ra,target); return; }
}

static void body_002634c8(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x002634c8u);
L_002634c8: ;
    /* 002634C8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
L_002634cc: ;
    /* 002634CC: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_002634d0: ;
    /* 002634D0: move s0,a0 */ set(16,cpu(4));
L_002634d4: ;
    /* 002634D4: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_002634d8: ;
    /* 002634D8: move s1,a1 */ set(17,cpu(5));
L_002634dc: ;
    /* 002634DC: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_002634e0: ;
    /* 002634E0: move s2,t0 */ set(18,cpu(8));
L_002634e4: ;
    /* 002634E4: sd s3,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(19));
L_002634e8: ;
    /* 002634E8: move s3,a2 */ set(19,cpu(6));
L_002634ec: ;
    /* 002634EC: sd s4,0x20(sp) */ w64(ea(cpu(29),UINT32_C(0x00000020)),(uint64_t)cpu(20));
L_002634f0: ;
    /* 002634F0: sd ra,0x28(sp) */ w64(ea(cpu(29),UINT32_C(0x00000028)),(uint64_t)cpu(31));
L_002634f4: ;
    /* 002634F4: jal 0x0025e8e0; native delay follows */
    set(31,UINT64_C(0x00000000002634fc));
    /* 002634F8: move s4,a3 */ set(20,cpu(7));
    set(2,nbGetKoukaProcessData());
    goto L_002634fc;
L_002634fc: ;
    /* 002634FC: move a0,v0 */ set(4,cpu(2));
L_00263500: ;
    /* 00263500: move a1,s0 */ set(5,cpu(16));
L_00263504: ;
    /* 00263504: move a3,s1 */ set(7,cpu(17));
L_00263508: ;
    /* 00263508: jal 0x0025ea48; native delay follows */
    set(31,UINT64_C(0x0000000000263510));
    /* 0026350C: move a2,zero */ set(6,cpu(0));
    set(2,nbAddKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263510;
L_00263510: ;
    /* 00263510: li a0,0x32 */ set(4,UINT64_C(0x0000000000000032));
L_00263514: ;
    /* 00263514: move v1,v0 */ set(3,cpu(2));
L_00263518: ;
    /* 00263518: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_0026351c: ;
    /* 0026351C: sw s2,0x2c(v1) */ w32(ea(cpu(3),UINT32_C(0x0000002c)),(uint32_t)cpu(18));
L_00263520: ;
    /* 00263520: sw s3,0x14(v1) */ w32(ea(cpu(3),UINT32_C(0x00000014)),(uint32_t)cpu(19));
L_00263524: ;
    /* 00263524: sw s4,0x28(v1) */ w32(ea(cpu(3),UINT32_C(0x00000028)),(uint32_t)cpu(20));
L_00263528: ;
    /* 00263528: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_0026352c: ;
    /* 0026352C: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_00263530: ;
    /* 00263530: ld s3,0x18(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_00263534: ;
    /* 00263534: ld s4,0x20(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x00000020))));
L_00263538: ;
    /* 00263538: ld ra,0x28(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000028))));
L_0026353c: ;
    /* 0026353C: sb a0,0x4(v1) */ w8(ea(cpu(3),UINT32_C(0x00000004)),(uint8_t)cpu(4));
L_00263540: ;
    /* 00263540: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00263544: addiu sp,sp,0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030))); ba_return_target(incoming_ra,target); return; }
}

static void body_00263918(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00263918u);
L_00263918: ;
    /* 00263918: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
L_0026391c: ;
    /* 0026391C: sd s1,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(17));
L_00263920: ;
    /* 00263920: move s1,a2 */ set(17,cpu(6));
L_00263924: ;
    /* 00263924: sd s0,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(16));
L_00263928: ;
    /* 00263928: move s0,a3 */ set(16,cpu(7));
L_0026392c: ;
    /* 0026392C: sd s2,0x20(sp) */ w64(ea(cpu(29),UINT32_C(0x00000020)),(uint64_t)cpu(18));
L_00263930: ;
    /* 00263930: move s2,a1 */ set(18,cpu(5));
L_00263934: ;
    /* 00263934: sd s3,0x28(sp) */ w64(ea(cpu(29),UINT32_C(0x00000028)),(uint64_t)cpu(19));
L_00263938: ;
    /* 00263938: move s3,zero */ set(19,cpu(0));
L_0026393c: ;
    /* 0026393C: sd s4,0x30(sp) */ w64(ea(cpu(29),UINT32_C(0x00000030)),(uint64_t)cpu(20));
L_00263940: ;
    /* 00263940: move s4,a0 */ set(20,cpu(4));
L_00263944: ;
    /* 00263944: sd s5,0x38(sp) */ w64(ea(cpu(29),UINT32_C(0x00000038)),(uint64_t)cpu(21));
L_00263948: ;
    /* 00263948: sd s6,0x40(sp) */ w64(ea(cpu(29),UINT32_C(0x00000040)),(uint64_t)cpu(22));
L_0026394c: ;
    /* 0026394C: sd s7,0x48(sp) */ w64(ea(cpu(29),UINT32_C(0x00000048)),(uint64_t)cpu(23));
L_00263950: ;
    /* 00263950: sd s8,0x50(sp) */ w64(ea(cpu(29),UINT32_C(0x00000050)),(uint64_t)cpu(30));
L_00263954: ;
    /* 00263954: sd ra,0x58(sp) */ w64(ea(cpu(29),UINT32_C(0x00000058)),(uint64_t)cpu(31));
L_00263958: ;
    /* 00263958: jal 0x002469a0; native delay follows */
    set(31,UINT64_C(0x0000000000263960));
    /* 0026395C: sw t0,0x0(sp) */ w32(ea(cpu(29),UINT32_C(0x00000000)),(uint32_t)cpu(8));
    set(2,nbGetMainProcessData());
    goto L_00263960;
L_00263960: ;
    /* 00263960: jal 0x00259ab0; native delay follows */
    set(31,UINT64_C(0x0000000000263968));
    /* 00263964: move a0,s1 */ set(4,cpu(17));
    set(2,nbCheckEventDead(cpu(4)));
    goto L_00263968;
L_00263968: ;
    /* 00263968: li v1,0x2 */ set(3,UINT64_C(0x0000000000000002));
L_0026396c: ;
    /* 0026396C: movn s0,v1,v0 */ if(cpu(2)!=0) set(16,cpu(3));
L_00263970: ;
    /* 00263970: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_00263974: ;
    /* 00263974: beql s0,v0,0x002639a8; native delay follows */
    { int taken=(cpu(16)==cpu(2));
      if(taken) { /* 00263978: move a0,s4 */ set(4,cpu(20)); goto L_002639a8; }
      goto L_0026397c; }
L_0026397c: ;
    /* 0026397C: slti v0,s0,0x2 */ set(2,lt(cpu(16),UINT64_C(0x0000000000000002)));
L_00263980: ;
    /* 00263980: beq v0,zero,0x00263998; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263984: nop  */ ;
      if(taken) goto L_00263998;
      goto L_00263988; }
L_00263988: ;
    /* 00263988: beql s0,zero,0x002639e8; native delay follows */
    { int taken=(cpu(16)==cpu(0));
      if(taken) { /* 0026398C: move a0,s4 */ set(4,cpu(20)); goto L_002639e8; }
      goto L_00263990; }
L_00263990: ;
    /* 00263990: b 0x00263b48; native delay follows */
    { /* 00263994: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000))))); goto L_00263b48; }
L_00263998: ;
    /* 00263998: beq s0,v1,0x00263a30; native delay follows */
    { int taken=(cpu(16)==cpu(3));
      /* 0026399C: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000)))));
      if(taken) goto L_00263a30;
      goto L_002639a0; }
L_002639a0: ;
    /* 002639A0: b 0x00263b48; native delay follows */
    { /* 002639A4: nop  */ ; goto L_00263b48; }
L_002639a8: ;
    /* 002639A8: move a1,s2 */ set(5,cpu(18));
L_002639ac: ;
    /* 002639AC: move a2,s1 */ set(6,cpu(17));
L_002639b0: ;
    /* 002639B0: move a3,zero */ set(7,cpu(0));
L_002639b4: ;
    /* 002639B4: li t0,0x2 */ set(8,UINT64_C(0x0000000000000002));
L_002639b8: ;
    /* 002639B8: li t1,0x2 */ set(9,UINT64_C(0x0000000000000002));
L_002639bc: ;
    /* 002639BC: li t2,0x2 */ set(10,UINT64_C(0x0000000000000002));
L_002639c0: ;
    /* 002639C0: jal 0x002638a0; native delay follows */
    set(31,UINT64_C(0x00000000002639c8));
    /* 002639C4: lui s3,0x1 */ set(19,sx(UINT32_C(0x00010000)));
    set(2,nbMakeUnitFadeOutPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10)));
    goto L_002639c8;
L_002639c8: ;
    /* 002639C8: addiu a0,s4,0x1 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
L_002639cc: ;
    /* 002639CC: move a1,s2 */ set(5,cpu(18));
L_002639d0: ;
    /* 002639D0: move a2,s1 */ set(6,cpu(17));
L_002639d4: ;
    /* 002639D4: li a3,0x6 */ set(7,UINT64_C(0x0000000000000006));
L_002639d8: ;
    /* 002639D8: jal 0x00262480; native delay follows */
    set(31,UINT64_C(0x00000000002639e0));
    /* 002639DC: ori s3,s3,0x4 */ set(19,cpu(19)|UINT64_C(0x0000000000000004));
    body_00262480();
    goto L_002639e0;
L_002639e0: ;
    /* 002639E0: b 0x00263b48; native delay follows */
    { /* 002639E4: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000))))); goto L_00263b48; }
L_002639e8: ;
    /* 002639E8: lui at,0x4188 */ set(1,sx(UINT32_C(0x41880000)));
L_002639ec: ;
    /* 002639EC: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_002639f0: ;
    /* 002639F0: move a1,s2 */ set(5,cpu(18));
L_002639f4: ;
    /* 002639F4: move a2,s1 */ set(6,cpu(17));
L_002639f8: ;
    /* 002639F8: move a3,zero */ set(7,cpu(0));
L_002639fc: ;
    /* 002639FC: jal 0x002621e0; native delay follows */
    set(31,UINT64_C(0x0000000000263a04));
    /* 00263A00: lui s3,0x1 */ set(19,sx(UINT32_C(0x00010000)));
    set(2,nbAddBadDmgMotKoukaPacket(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263a04;
L_00263a04: ;
    /* 00263A04: addiu a0,s4,0x7 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0x00000007)));
L_00263a08: ;
    /* 00263A08: move a1,s2 */ set(5,cpu(18));
L_00263a0c: ;
    /* 00263A0C: move a2,s1 */ set(6,cpu(17));
L_00263a10: ;
    /* 00263A10: move a3,zero */ set(7,cpu(0));
L_00263a14: ;
    /* 00263A14: li t0,0xa */ set(8,UINT64_C(0x000000000000000a));
L_00263a18: ;
    /* 00263A18: li t1,0xa */ set(9,UINT64_C(0x000000000000000a));
L_00263a1c: ;
    /* 00263A1C: jal 0x002638a0; native delay follows */
    set(31,UINT64_C(0x0000000000263a24));
    /* 00263A20: li t2,0xa */ set(10,UINT64_C(0x000000000000000a));
    set(2,nbMakeUnitFadeOutPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10)));
    goto L_00263a24;
L_00263a24: ;
    /* 00263A24: b 0x00263b48; native delay follows */
    { /* 00263A28: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000))))); goto L_00263b48; }
L_00263a30: ;
    /* 00263A30: lw v0,0x8c(s1) */ set(2,sx(r32(ea(cpu(17),UINT32_C(0x0000008c)))));
L_00263a34: ;
    /* 00263A34: move a1,zero */ set(5,cpu(0));
L_00263a38: ;
    /* 00263A38: jal 0x001ddba8; native delay follows */
    set(31,UINT64_C(0x0000000000263a40));
    /* 00263A3C: lw a0,0x8c(v0) */ set(4,sx(r32(ea(cpu(2),UINT32_C(0x0000008c)))));
    set(2,ps2ModelMotionLength(cpu(4),cpu(5)));
    goto L_00263a40;
L_00263a40: ;
    /* 00263A40: slti v0,v0,0x18 */ set(2,lt(cpu(2),UINT64_C(0x0000000000000018)));
L_00263a44: ;
    /* 00263A44: beq v0,zero,0x00263a80; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263A48: move a0,s4 */ set(4,cpu(20));
      if(taken) goto L_00263a80;
      goto L_00263a4c; }
L_00263a4c: ;
    /* 00263A4C: move a1,s2 */ set(5,cpu(18));
L_00263a50: ;
    /* 00263A50: jal 0x002645a8; native delay follows */
    set(31,UINT64_C(0x0000000000263a58));
    /* 00263A54: move a2,s1 */ set(6,cpu(17));
    set(2,nbMakeBadKaifukuPacket(cpu(4),cpu(5),cpu(6)));
    goto L_00263a58;
L_00263a58: ;
    /* 00263A58: move a0,s4 */ set(4,cpu(20));
L_00263a5c: ;
    /* 00263A5C: lui at,0x41f0 */ set(1,sx(UINT32_C(0x41f00000)));
L_00263a60: ;
    /* 00263A60: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00263a64: ;
    /* 00263A64: move a1,s2 */ set(5,cpu(18));
L_00263a68: ;
    /* 00263A68: move a2,s1 */ set(6,cpu(17));
L_00263a6c: ;
    /* 00263A6C: jal 0x002621e0; native delay follows */
    set(31,UINT64_C(0x0000000000263a74));
    /* 00263A70: li a3,-0x1 */ set(7,UINT64_C(0xffffffffffffffff));
    set(2,nbAddBadDmgMotKoukaPacket(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263a74;
L_00263a74: ;
    /* 00263A74: b 0x00263aa0; native delay follows */
    { /* 00263A78: nop  */ ; goto L_00263aa0; }
L_00263a80: ;
    /* 00263A80: move a1,s2 */ set(5,cpu(18));
L_00263a84: ;
    /* 00263A84: jal 0x002645a8; native delay follows */
    set(31,UINT64_C(0x0000000000263a8c));
    /* 00263A88: move a2,s1 */ set(6,cpu(17));
    set(2,nbMakeBadKaifukuPacket(cpu(4),cpu(5),cpu(6)));
    goto L_00263a8c;
L_00263a8c: ;
    /* 00263A8C: move a0,s4 */ set(4,cpu(20));
L_00263a90: ;
    /* 00263A90: move a1,s2 */ set(5,cpu(18));
L_00263a94: ;
    /* 00263A94: move a2,s1 */ set(6,cpu(17));
L_00263a98: ;
    /* 00263A98: jal 0x00261ff0; native delay follows */
    set(31,UINT64_C(0x0000000000263aa0));
    /* 00263A9C: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
    set(2,nbAddMotionKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263aa0;
L_00263aa0: ;
    /* 00263AA0: jal 0x00259b70; native delay follows */
    set(31,UINT64_C(0x0000000000263aa8));
    /* 00263AA4: move a0,s1 */ set(4,cpu(17));
    set(2,nbCheckDeadEvent(cpu(4)));
    goto L_00263aa8;
L_00263aa8: ;
    /* 00263AA8: move s0,v0 */ set(16,cpu(2));
L_00263aac: ;
    /* 00263AAC: beq s0,zero,0x00263b44; native delay follows */
    { int taken=(cpu(16)==cpu(0));
      /* 00263AB0: lui s3,0x1 */ set(19,sx(UINT32_C(0x00010000)));
      if(taken) goto L_00263b44;
      goto L_00263ab4; }
L_00263ab4: ;
    /* 00263AB4: jal 0x0028fc38; native delay follows */
    set(31,UINT64_C(0x0000000000263abc));
    /* 00263AB8: move a0,s0 */ set(4,cpu(16));
    set(2,nbGetDeadEventFadeTime(cpu(4)));
    goto L_00263abc;
L_00263abc: ;
    /* 00263ABC: move a0,s0 */ set(4,cpu(16));
L_00263ac0: ;
    /* 00263AC0: jal 0x0028fc70; native delay follows */
    set(31,UINT64_C(0x0000000000263ac8));
    /* 00263AC4: move s6,v0 */ set(22,cpu(2));
    set(2,nbGetDeadEventFadeOutFrame(cpu(4)));
    goto L_00263ac8;
L_00263ac8: ;
    /* 00263AC8: move a0,s0 */ set(4,cpu(16));
L_00263acc: ;
    /* 00263ACC: jal 0x0028fce0; native delay follows */
    set(31,UINT64_C(0x0000000000263ad4));
    /* 00263AD0: move s3,v0 */ set(19,cpu(2));
    set(2,nbGetDeadEventFadeStopFrame(cpu(4)));
    goto L_00263ad4;
L_00263ad4: ;
    /* 00263AD4: move a0,s0 */ set(4,cpu(16));
L_00263ad8: ;
    /* 00263AD8: addu s8,s4,s6 */ set(30,sx((uint32_t)cpu(20)+(uint32_t)cpu(22)));
L_00263adc: ;
    /* 00263ADC: jal 0x0028fca8; native delay follows */
    set(31,UINT64_C(0x0000000000263ae4));
    /* 00263AE0: move s7,v0 */ set(23,cpu(2));
    set(2,nbGetDeadEventFadeInFrame(cpu(4)));
    goto L_00263ae4;
L_00263ae4: ;
    /* 00263AE4: move a0,s8 */ set(4,cpu(30));
L_00263ae8: ;
    /* 00263AE8: move s5,v0 */ set(21,cpu(2));
L_00263aec: ;
    /* 00263AEC: move a1,s2 */ set(5,cpu(18));
L_00263af0: ;
    /* 00263AF0: move a2,s3 */ set(6,cpu(19));
L_00263af4: ;
    /* 00263AF4: jal 0x002633e8; native delay follows */
    set(31,UINT64_C(0x0000000000263afc));
    /* 00263AF8: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
    set(2,nbAddFadeOutKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263afc;
L_00263afc: ;
    /* 00263AFC: blez s5,0x00263b28; native delay follows */
    { int taken=(!lt(0,cpu(21)));
      /* 00263B00: addu a0,s8,s3 */ set(4,sx((uint32_t)cpu(30)+(uint32_t)cpu(19)));
      if(taken) goto L_00263b28;
      goto L_00263b04; }
L_00263b04: ;
    /* 00263B04: addu a0,s4,s7 */ set(4,sx((uint32_t)cpu(20)+(uint32_t)cpu(23)));
L_00263b08: ;
    /* 00263B08: addiu v0,s3,0x2 */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0x00000002)));
L_00263b0c: ;
    /* 00263B0C: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
L_00263b10: ;
    /* 00263B10: move a2,s5 */ set(6,cpu(21));
L_00263b14: ;
    /* 00263B14: addu a0,a0,s6 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(22)));
L_00263b18: ;
    /* 00263B18: move a1,s2 */ set(5,cpu(18));
L_00263b1c: ;
    /* 00263B1C: jal 0x00263458; native delay follows */
    set(31,UINT64_C(0x0000000000263b24));
    /* 00263B20: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
    set(2,nbAddFadeInKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263b24;
L_00263b24: ;
    /* 00263B24: addu a0,s8,s3 */ set(4,sx((uint32_t)cpu(30)+(uint32_t)cpu(19)));
L_00263b28: ;
    /* 00263B28: move a3,s0 */ set(7,cpu(16));
L_00263b2c: ;
    /* 00263B2C: addu a0,a0,s7 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(23)));
L_00263b30: ;
    /* 00263B30: move a1,s2 */ set(5,cpu(18));
L_00263b34: ;
    /* 00263B34: addiu a0,a0,-0x3 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffd)));
L_00263b38: ;
    /* 00263B38: jal 0x00263350; native delay follows */
    set(31,UINT64_C(0x0000000000263b40));
    /* 00263B3C: move a2,s1 */ set(6,cpu(17));
    set(2,nbAddDeadEventKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263b40;
L_00263b40: ;
    /* 00263B40: lui s3,0x1 */ set(19,sx(UINT32_C(0x00010000)));
L_00263b44: ;
    /* 00263B44: lw v0,0x0(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000000)))));
L_00263b48: ;
    /* 00263B48: beq v0,zero,0x00263b74; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263B4C: addiu s0,s4,0x7 */ set(16,sx((uint32_t)cpu(20)+UINT32_C(0x00000007)));
      if(taken) goto L_00263b74;
      goto L_00263b50; }
L_00263b50: ;
    /* 00263B50: move a1,s2 */ set(5,cpu(18));
L_00263b54: ;
    /* 00263B54: move a0,s0 */ set(4,cpu(16));
L_00263b58: ;
    /* 00263B58: jal 0x00262c18; native delay follows */
    set(31,UINT64_C(0x0000000000263b60));
    /* 00263B5C: move a2,s1 */ set(6,cpu(17));
    set(2,nbAddDeadPcmPacket(cpu(4),cpu(5),cpu(6)));
    goto L_00263b60;
L_00263b60: ;
    /* 00263B60: beq s3,zero,0x00263b74; native delay follows */
    { int taken=(cpu(19)==cpu(0));
      /* 00263B64: move a0,s0 */ set(4,cpu(16));
      if(taken) goto L_00263b74;
      goto L_00263b68; }
L_00263b68: ;
    /* 00263B68: move a2,s3 */ set(6,cpu(19));
L_00263b6c: ;
    /* 00263B6C: jal 0x00262cc0; native delay follows */
    set(31,UINT64_C(0x0000000000263b74));
    /* 00263B70: move a1,s2 */ set(5,cpu(18));
    set(2,nbAddSePacket(cpu(4),cpu(5),cpu(6)));
    goto L_00263b74;
L_00263b74: ;
    /* 00263B74: lw v0,0x78(s1) */ set(2,sx(r32(ea(cpu(17),UINT32_C(0x00000078)))));
L_00263b78: ;
    /* 00263B78: andi v0,v0,0x100 */ set(2,cpu(2)&UINT64_C(0x0000000000000100));
L_00263b7c: ;
    /* 00263B7C: beql v0,zero,0x00263bd0; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      if(taken) { /* 00263B80: ld s0,0x10(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000010)))); goto L_00263bd0; }
      goto L_00263b84; }
L_00263b84: ;
    /* 00263B84: jal 0x00246ab8; native delay follows */
    set(31,UINT64_C(0x0000000000263b8c));
    /* 00263B88: lh a0,0x92(s1) */ set(4,sx((uint32_t)i16(r16(ea(cpu(17),UINT32_C(0x00000092))))));
    set(2,nbGetUnitWorkFromFormindex(cpu(4)));
    goto L_00263b8c;
L_00263b8c: ;
    /* 00263B8C: lw v1,0x0(v0) */ set(3,sx(r32(ea(cpu(2),UINT32_C(0x00000000)))));
L_00263b90: ;
    /* 00263B90: andi v1,v1,0x4 */ set(3,cpu(3)&UINT64_C(0x0000000000000004));
L_00263b94: ;
    /* 00263B94: beq v1,zero,0x00263bb8; native delay follows */
    { int taken=(cpu(3)==cpu(0));
      /* 00263B98: move a0,s4 */ set(4,cpu(20));
      if(taken) goto L_00263bb8;
      goto L_00263b9c; }
L_00263b9c: ;
    /* 00263B9C: move a1,s2 */ set(5,cpu(18));
L_00263ba0: ;
    /* 00263BA0: li a2,0x1 */ set(6,UINT64_C(0x0000000000000001));
L_00263ba4: ;
    /* 00263BA4: li a3,0xfa */ set(7,UINT64_C(0x00000000000000fa));
L_00263ba8: ;
    /* 00263BA8: jal 0x002635a8; native delay follows */
    set(31,UINT64_C(0x0000000000263bb0));
    /* 00263BAC: li t0,0x1e */ set(8,UINT64_C(0x000000000000001e));
    set(2,nbAddPadShockPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_00263bb0;
L_00263bb0: ;
    /* 00263BB0: b 0x00263bd0; native delay follows */
    { /* 00263BB4: ld s0,0x10(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000010)))); goto L_00263bd0; }
L_00263bb8: ;
    /* 00263BB8: move a1,s2 */ set(5,cpu(18));
L_00263bbc: ;
    /* 00263BBC: li a2,0x1 */ set(6,UINT64_C(0x0000000000000001));
L_00263bc0: ;
    /* 00263BC0: li a3,0x96 */ set(7,UINT64_C(0x0000000000000096));
L_00263bc4: ;
    /* 00263BC4: jal 0x002635a8; native delay follows */
    set(31,UINT64_C(0x0000000000263bcc));
    /* 00263BC8: li t0,0x14 */ set(8,UINT64_C(0x0000000000000014));
    set(2,nbAddPadShockPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_00263bcc;
L_00263bcc: ;
    /* 00263BCC: ld s0,0x10(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_00263bd0: ;
    /* 00263BD0: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_00263bd4: ;
    /* 00263BD4: ld s1,0x18(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_00263bd8: ;
    /* 00263BD8: ld s2,0x20(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000020))));
L_00263bdc: ;
    /* 00263BDC: ld s3,0x28(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000028))));
L_00263be0: ;
    /* 00263BE0: ld s4,0x30(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x00000030))));
L_00263be4: ;
    /* 00263BE4: ld s5,0x38(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x00000038))));
L_00263be8: ;
    /* 00263BE8: ld s6,0x40(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x00000040))));
L_00263bec: ;
    /* 00263BEC: ld s7,0x48(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x00000048))));
L_00263bf0: ;
    /* 00263BF0: ld s8,0x50(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x00000050))));
L_00263bf4: ;
    /* 00263BF4: ld ra,0x58(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000058))));
L_00263bf8: ;
    /* 00263BF8: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00263BFC: addiu sp,sp,0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060))); ba_return_target(incoming_ra,target); return; }
}

static void body_00263c00(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00263c00u);
L_00263c00: ;
    /* 00263C00: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
L_00263c04: ;
    /* 00263C04: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_00263c08: ;
    /* 00263C08: move s0,a1 */ set(16,cpu(5));
L_00263c0c: ;
    /* 00263C0C: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00263c10: ;
    /* 00263C10: move s1,a2 */ set(17,cpu(6));
L_00263c14: ;
    /* 00263C14: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_00263c18: ;
    /* 00263C18: move s2,a0 */ set(18,cpu(4));
L_00263c1c: ;
    /* 00263C1C: sd s3,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(19));
L_00263c20: ;
    /* 00263C20: move s3,a3 */ set(19,cpu(7));
L_00263c24: ;
    /* 00263C24: sd s4,0x20(sp) */ w64(ea(cpu(29),UINT32_C(0x00000020)),(uint64_t)cpu(20));
L_00263c28: ;
    /* 00263C28: move s4,t3 */ set(20,cpu(11));
L_00263c2c: ;
    /* 00263C2C: sd s5,0x28(sp) */ w64(ea(cpu(29),UINT32_C(0x00000028)),(uint64_t)cpu(21));
L_00263c30: ;
    /* 00263C30: move a3,t2 */ set(7,cpu(10));
L_00263c34: ;
    /* 00263C34: sd s6,0x30(sp) */ w64(ea(cpu(29),UINT32_C(0x00000030)),(uint64_t)cpu(22));
L_00263c38: ;
    /* 00263C38: move s6,t0 */ set(22,cpu(8));
L_00263c3c: ;
    /* 00263C3C: sd s7,0x38(sp) */ w64(ea(cpu(29),UINT32_C(0x00000038)),(uint64_t)cpu(23));
L_00263c40: ;
    /* 00263C40: move s7,t1 */ set(23,cpu(9));
L_00263c44: ;
    /* 00263C44: sd s8,0x40(sp) */ w64(ea(cpu(29),UINT32_C(0x00000040)),(uint64_t)cpu(30));
L_00263c48: ;
    /* 00263C48: sd ra,0x48(sp) */ w64(ea(cpu(29),UINT32_C(0x00000048)),(uint64_t)cpu(31));
L_00263c4c: ;
    /* 00263C4C: lw s8,0x60(sp) */ set(30,sx(r32(ea(cpu(29),UINT32_C(0x00000060)))));
L_00263c50: ;
    /* 00263C50: lh v0,0x92(s1) */ set(2,sx((uint32_t)i16(r16(ea(cpu(17),UINT32_C(0x00000092))))));
L_00263c54: ;
    /* 00263C54: slti v0,v0,0x10 */ set(2,lt(cpu(2),UINT64_C(0x0000000000000010)));
L_00263c58: ;
    /* 00263C58: sltiu s5,v0,0x1 */ set(21,(cpu(2)<UINT64_C(0x0000000000000001)));
L_00263c5c: ;
    /* 00263C5C: bne s5,zero,0x00263df0; native delay follows */
    { int taken=(cpu(21)!=cpu(0));
      /* 00263C60: lw v0,0x50(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000050)))));
      if(taken) goto L_00263df0;
      goto L_00263c64; }
L_00263c64: ;
    /* 00263C64: beq v0,zero,0x00263c80; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263C68: li v0,0x20 */ set(2,UINT64_C(0x0000000000000020));
      if(taken) goto L_00263c80;
      goto L_00263c6c; }
L_00263c6c: ;
    /* 00263C6C: lw a3,0x58(sp) */ set(7,sx(r32(ea(cpu(29),UINT32_C(0x00000058)))));
L_00263c70: ;
    /* 00263C70: jal 0x00263918; native delay follows */
    set(31,UINT64_C(0x0000000000263c78));
    /* 00263C74: li t0,0x1 */ set(8,UINT64_C(0x0000000000000001));
    body_00263918();
    goto L_00263c78;
L_00263c78: ;
    /* 00263C78: b 0x00263df0; native delay follows */
    { /* 00263C7C: nop  */ ; goto L_00263df0; }
L_00263c80: ;
    /* 00263C80: beq a3,v0,0x00263d38; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263C84: slti v0,a3,0x21 */ set(2,lt(cpu(7),UINT64_C(0x0000000000000021)));
      if(taken) goto L_00263d38;
      goto L_00263c88; }
L_00263c88: ;
    /* 00263C88: beq v0,zero,0x00263cd8; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263C8C: li v0,0x100 */ set(2,UINT64_C(0x0000000000000100));
      if(taken) goto L_00263cd8;
      goto L_00263c90; }
L_00263c90: ;
    /* 00263C90: li v0,0x4 */ set(2,UINT64_C(0x0000000000000004));
L_00263c94: ;
    /* 00263C94: beq a3,v0,0x00263d38; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263C98: slti v0,a3,0x5 */ set(2,lt(cpu(7),UINT64_C(0x0000000000000005)));
      if(taken) goto L_00263d38;
      goto L_00263c9c; }
L_00263c9c: ;
    /* 00263C9C: beq v0,zero,0x00263cc0; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263CA0: li v0,0x8 */ set(2,UINT64_C(0x0000000000000008));
      if(taken) goto L_00263cc0;
      goto L_00263ca4; }
L_00263ca4: ;
    /* 00263CA4: slti v0,a3,0x3 */ set(2,lt(cpu(7),UINT64_C(0x0000000000000003)));
L_00263ca8: ;
    /* 00263CA8: beq v0,zero,0x00263d60; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263CAC: slti v0,s3,0x3 */ set(2,lt(cpu(19),UINT64_C(0x0000000000000003)));
      if(taken) goto L_00263d60;
      goto L_00263cb0; }
L_00263cb0: ;
    /* 00263CB0: blez a3,0x00263d60; native delay follows */
    { int taken=(!lt(0,cpu(7)));
      /* 00263CB4: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_00263d60;
      goto L_00263cb8; }
L_00263cb8: ;
    /* 00263CB8: b 0x00263d3c; native delay follows */
    { /* 00263CBC: nop  */ ; goto L_00263d3c; }
L_00263cc0: ;
    /* 00263CC0: beq a3,v0,0x00263d38; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263CC4: li v0,0x10 */ set(2,UINT64_C(0x0000000000000010));
      if(taken) goto L_00263d38;
      goto L_00263cc8; }
L_00263cc8: ;
    /* 00263CC8: beq a3,v0,0x00263d38; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263CCC: slti v0,s3,0x3 */ set(2,lt(cpu(19),UINT64_C(0x0000000000000003)));
      if(taken) goto L_00263d38;
      goto L_00263cd0; }
L_00263cd0: ;
    /* 00263CD0: b 0x00263d60; native delay follows */
    { /* 00263CD4: nop  */ ; goto L_00263d60; }
L_00263cd8: ;
    /* 00263CD8: beq a3,v0,0x00263d38; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263CDC: slti v0,a3,0x101 */ set(2,lt(cpu(7),UINT64_C(0x0000000000000101)));
      if(taken) goto L_00263d38;
      goto L_00263ce0; }
L_00263ce0: ;
    /* 00263CE0: beq v0,zero,0x00263d08; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263CE4: li v0,0x400 */ set(2,UINT64_C(0x0000000000000400));
      if(taken) goto L_00263d08;
      goto L_00263ce8; }
L_00263ce8: ;
    /* 00263CE8: li v0,0x40 */ set(2,UINT64_C(0x0000000000000040));
L_00263cec: ;
    /* 00263CEC: beq a3,v0,0x00263d38; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263CF0: li v0,0x80 */ set(2,UINT64_C(0x0000000000000080));
      if(taken) goto L_00263d38;
      goto L_00263cf4; }
L_00263cf4: ;
    /* 00263CF4: beq a3,v0,0x00263d38; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263CF8: slti v0,s3,0x3 */ set(2,lt(cpu(19),UINT64_C(0x0000000000000003)));
      if(taken) goto L_00263d38;
      goto L_00263cfc; }
L_00263cfc: ;
    /* 00263CFC: b 0x00263d60; native delay follows */
    { /* 00263D00: nop  */ ; goto L_00263d60; }
L_00263d08: ;
    /* 00263D08: beq a3,v0,0x00263d38; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263D0C: slti v0,a3,0x401 */ set(2,lt(cpu(7),UINT64_C(0x0000000000000401)));
      if(taken) goto L_00263d38;
      goto L_00263d10; }
L_00263d10: ;
    /* 00263D10: beq v0,zero,0x00263d30; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263D14: li v0,0x800 */ set(2,UINT64_C(0x0000000000000800));
      if(taken) goto L_00263d30;
      goto L_00263d18; }
L_00263d18: ;
    /* 00263D18: li v0,0x200 */ set(2,UINT64_C(0x0000000000000200));
L_00263d1c: ;
    /* 00263D1C: beq a3,v0,0x00263d50; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00263D20: slti v0,s3,0x3 */ set(2,lt(cpu(19),UINT64_C(0x0000000000000003)));
      if(taken) goto L_00263d50;
      goto L_00263d24; }
L_00263d24: ;
    /* 00263D24: b 0x00263d60; native delay follows */
    { /* 00263D28: nop  */ ; goto L_00263d60; }
L_00263d30: ;
    /* 00263D30: bne a3,v0,0x00263d60; native delay follows */
    { int taken=(cpu(7)!=cpu(2));
      /* 00263D34: slti v0,s3,0x3 */ set(2,lt(cpu(19),UINT64_C(0x0000000000000003)));
      if(taken) goto L_00263d60;
      goto L_00263d38; }
L_00263d38: ;
    /* 00263D38: move a0,s2 */ set(4,cpu(18));
L_00263d3c: ;
    /* 00263D3C: move a1,s0 */ set(5,cpu(16));
L_00263d40: ;
    /* 00263D40: jal 0x00264528; native delay follows */
    set(31,UINT64_C(0x0000000000263d48));
    /* 00263D44: move a2,s1 */ set(6,cpu(17));
    set(2,nbMakeBadDamagePacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263d48;
L_00263d48: ;
    /* 00263D48: b 0x00263df0; native delay follows */
    { /* 00263D4C: nop  */ ; goto L_00263df0; }
L_00263d50: ;
    /* 00263D50: jal 0x00264508; native delay follows */
    set(31,UINT64_C(0x0000000000263d58));
    /* 00263D54: nop  */ ;
    set(2,nbMakeFlyBadPacket(cpu(4),cpu(5),cpu(6)));
    goto L_00263d58;
L_00263d58: ;
    /* 00263D58: b 0x00263df0; native delay follows */
    { /* 00263D5C: nop  */ ; goto L_00263df0; }
L_00263d60: ;
    /* 00263D60: beql v0,zero,0x00263d80; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      if(taken) { /* 00263D64: li v0,0x3 */ set(2,UINT64_C(0x0000000000000003)); goto L_00263d80; }
      goto L_00263d68; }
L_00263d68: ;
    /* 00263D68: bgtz s3,0x00263dd8; native delay follows */
    { int taken=(lt(0,cpu(19)));
      /* 00263D6C: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_00263dd8;
      goto L_00263d70; }
L_00263d70: ;
    /* 00263D70: beq s3,zero,0x00263db8; native delay follows */
    { int taken=(cpu(19)==cpu(0));
      /* 00263D74: move a1,s0 */ set(5,cpu(16));
      if(taken) goto L_00263db8;
      goto L_00263d78; }
L_00263d78: ;
    /* 00263D78: b 0x00263df0; native delay follows */
    { /* 00263D7C: nop  */ ; goto L_00263df0; }
L_00263d80: ;
    /* 00263D80: bne s3,v0,0x00263df0; native delay follows */
    { int taken=(cpu(19)!=cpu(2));
      /* 00263D84: move a2,s1 */ set(6,cpu(17));
      if(taken) goto L_00263df0;
      goto L_00263d88; }
L_00263d88: ;
    /* 00263D88: lui at,0x4120 */ set(1,sx(UINT32_C(0x41200000)));
L_00263d8c: ;
    /* 00263D8C: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00263d90: ;
    /* 00263D90: move a0,s2 */ set(4,cpu(18));
L_00263d94: ;
    /* 00263D94: jal 0x00262170; native delay follows */
    set(31,UINT64_C(0x0000000000263d9c));
    /* 00263D98: move a1,s0 */ set(5,cpu(16));
    set(2,nbAddEasyDmgMotKoukaPacket(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6)));
    goto L_00263d9c;
L_00263d9c: ;
    /* 00263D9C: move a0,s2 */ set(4,cpu(18));
L_00263da0: ;
    /* 00263DA0: lui a2,0x1 */ set(6,sx(UINT32_C(0x00010000)));
L_00263da4: ;
    /* 00263DA4: move a1,s0 */ set(5,cpu(16));
L_00263da8: ;
    /* 00263DA8: jal 0x00262cc0; native delay follows */
    set(31,UINT64_C(0x0000000000263db0));
    /* 00263DAC: ori a2,a2,0x2 */ set(6,cpu(6)|UINT64_C(0x0000000000000002));
    set(2,nbAddSePacket(cpu(4),cpu(5),cpu(6)));
    goto L_00263db0;
L_00263db0: ;
    /* 00263DB0: b 0x00263df0; native delay follows */
    { /* 00263DB4: nop  */ ; goto L_00263df0; }
L_00263db8: ;
    /* 00263DB8: lui at,0x4188 */ set(1,sx(UINT32_C(0x41880000)));
L_00263dbc: ;
    /* 00263DBC: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00263dc0: ;
    /* 00263DC0: move a2,s1 */ set(6,cpu(17));
L_00263dc4: ;
    /* 00263DC4: jal 0x002620f0; native delay follows */
    set(31,UINT64_C(0x0000000000263dcc));
    /* 00263DC8: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
    set(2,nbAddDmgMotKoukaPacket(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263dcc;
L_00263dcc: ;
    /* 00263DCC: b 0x00263df0; native delay follows */
    { /* 00263DD0: nop  */ ; goto L_00263df0; }
L_00263dd8: ;
    /* 00263DD8: lui at,0x4188 */ set(1,sx(UINT32_C(0x41880000)));
L_00263ddc: ;
    /* 00263DDC: mtc1 at,f12 */ fpr()[12]=(uint32_t)cpu(1);
L_00263de0: ;
    /* 00263DE0: move a1,s0 */ set(5,cpu(16));
L_00263de4: ;
    /* 00263DE4: move a2,s1 */ set(6,cpu(17));
L_00263de8: ;
    /* 00263DE8: jal 0x002620f0; native delay follows */
    set(31,UINT64_C(0x0000000000263df0));
    /* 00263DEC: li a3,0x1 */ set(7,UINT64_C(0x0000000000000001));
    set(2,nbAddDmgMotKoukaPacket(fvalue(fpr()[12]),cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_00263df0;
L_00263df0: ;
    /* 00263DF0: beq s4,zero,0x00263e68; native delay follows */
    { int taken=(cpu(20)==cpu(0));
      /* 00263DF4: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
      if(taken) goto L_00263e68;
      goto L_00263df8; }
L_00263df8: ;
    /* 00263DF8: bne s5,zero,0x00263e6c; native delay follows */
    { int taken=(cpu(21)!=cpu(0));
      /* 00263DFC: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
      if(taken) goto L_00263e6c;
      goto L_00263e00; }
L_00263e00: ;
    /* 00263E00: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_00263e04: ;
    /* 00263E04: beq s3,v0,0x00263e50; native delay follows */
    { int taken=(cpu(19)==cpu(2));
      /* 00263E08: slti v0,s3,0x2 */ set(2,lt(cpu(19),UINT64_C(0x0000000000000002)));
      if(taken) goto L_00263e50;
      goto L_00263e0c; }
L_00263e0c: ;
    /* 00263E0C: beq v0,zero,0x00263e28; native delay follows */
    { int taken=(cpu(2)==cpu(0));
      /* 00263E10: li v0,0x2 */ set(2,UINT64_C(0x0000000000000002));
      if(taken) goto L_00263e28;
      goto L_00263e14; }
L_00263e14: ;
    /* 00263E14: beq s3,zero,0x00263e34; native delay follows */
    { int taken=(cpu(19)==cpu(0));
      /* 00263E18: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_00263e34;
      goto L_00263e1c; }
L_00263e1c: ;
    /* 00263E1C: b 0x00263e68; native delay follows */
    { /* 00263E20: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068))))); goto L_00263e68; }
L_00263e28: ;
    /* 00263E28: bnel s3,v0,0x00263e68; native delay follows */
    { int taken=(cpu(19)!=cpu(2));
      if(taken) { /* 00263E2C: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068))))); goto L_00263e68; }
      goto L_00263e30; }
L_00263e30: ;
    /* 00263E30: move a0,s2 */ set(4,cpu(18));
L_00263e34: ;
    /* 00263E34: move a1,s0 */ set(5,cpu(16));
L_00263e38: ;
    /* 00263E38: move a2,s1 */ set(6,cpu(17));
L_00263e3c: ;
    /* 00263E3C: jal 0x00262480; native delay follows */
    set(31,UINT64_C(0x0000000000263e44));
    /* 00263E40: move a3,zero */ set(7,cpu(0));
    body_00262480();
    goto L_00263e44;
L_00263e44: ;
    /* 00263E44: b 0x00263e68; native delay follows */
    { /* 00263E48: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068))))); goto L_00263e68; }
L_00263e50: ;
    /* 00263E50: move a0,s2 */ set(4,cpu(18));
L_00263e54: ;
    /* 00263E54: move a1,s0 */ set(5,cpu(16));
L_00263e58: ;
    /* 00263E58: move a2,s1 */ set(6,cpu(17));
L_00263e5c: ;
    /* 00263E5C: jal 0x00262480; native delay follows */
    set(31,UINT64_C(0x0000000000263e64));
    /* 00263E60: li a3,0x7 */ set(7,UINT64_C(0x0000000000000007));
    body_00262480();
    goto L_00263e64;
L_00263e64: ;
    /* 00263E64: lw v0,0x68(sp) */ set(2,sx(r32(ea(cpu(29),UINT32_C(0x00000068)))));
L_00263e68: ;
    /* 00263E68: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
L_00263e6c: ;
    /* 00263E6C: bltz s6,0x00263ed8; native delay follows */
    { int taken=(lt(cpu(22),0));
      /* 00263E70: addiu s4,v0,0x1 */ set(20,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
      if(taken) goto L_00263ed8;
      goto L_00263e74; }
L_00263e74: ;
    /* 00263E74: bltz s7,0x00263f30; native delay follows */
    { int taken=(lt(cpu(23),0));
      /* 00263E78: nop  */ ;
      if(taken) goto L_00263f30;
      goto L_00263e7c; }
L_00263e7c: ;
    /* 00263E7C: bnel s5,zero,0x00263eac; native delay follows */
    { int taken=(cpu(21)!=cpu(0));
      if(taken) { /* 00263E80: subu a3,zero,s6 */ set(7,sx((uint32_t)cpu(0)-(uint32_t)cpu(22))); goto L_00263eac; }
      goto L_00263e84; }
L_00263e84: ;
    /* 00263E84: beq s8,zero,0x00263ea8; native delay follows */
    { int taken=(cpu(30)==cpu(0));
      /* 00263E88: move t1,s7 */ set(9,cpu(23));
      if(taken) goto L_00263ea8;
      goto L_00263e8c; }
L_00263e8c: ;
    /* 00263E8C: move a0,s4 */ set(4,cpu(20));
L_00263e90: ;
    /* 00263E90: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_00263e94: ;
    /* 00263E94: move a2,s0 */ set(6,cpu(16));
L_00263e98: ;
    /* 00263E98: move a3,s1 */ set(7,cpu(17));
L_00263e9c: ;
    /* 00263E9C: move t0,s6 */ set(8,cpu(22));
L_00263ea0: ;
    /* 00263EA0: jal 0x002627c0; native delay follows */
    set(31,UINT64_C(0x0000000000263ea8));
    /* 00263EA4: li t2,0x4 */ set(10,UINT64_C(0x0000000000000004));
    nbAddNumEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10));
    goto L_00263ea8;
L_00263ea8: ;
    /* 00263EA8: subu a3,zero,s6 */ set(7,sx((uint32_t)cpu(0)-(uint32_t)cpu(22)));
L_00263eac: ;
    /* 00263EAC: move t0,zero */ set(8,cpu(0));
L_00263eb0: ;
    /* 00263EB0: move a0,s2 */ set(4,cpu(18));
L_00263eb4: ;
    /* 00263EB4: move a1,s0 */ set(5,cpu(16));
L_00263eb8: ;
    /* 00263EB8: jal 0x002629e8; native delay follows */
    set(31,UINT64_C(0x0000000000263ec0));
    /* 00263EBC: move a2,s1 */ set(6,cpu(17));
    set(2,nbAddHpMpKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_00263ec0;
L_00263ec0: ;
    /* 00263EC0: move a0,s2 */ set(4,cpu(18));
L_00263ec4: ;
    /* 00263EC4: move a1,s0 */ set(5,cpu(16));
L_00263ec8: ;
    /* 00263EC8: move a2,s1 */ set(6,cpu(17));
L_00263ecc: ;
    /* 00263ECC: b 0x00263f1c; native delay follows */
    { /* 00263ED0: subu a3,zero,s7 */ set(7,sx((uint32_t)cpu(0)-(uint32_t)cpu(23))); goto L_00263f1c; }
L_00263ed8: ;
    /* 00263ED8: bltz s7,0x00263f30; native delay follows */
    { int taken=(lt(cpu(23),0));
      /* 00263EDC: nop  */ ;
      if(taken) goto L_00263f30;
      goto L_00263ee0; }
L_00263ee0: ;
    /* 00263EE0: bne s5,zero,0x00263f10; native delay follows */
    { int taken=(cpu(21)!=cpu(0));
      /* 00263EE4: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_00263f10;
      goto L_00263ee8; }
L_00263ee8: ;
    /* 00263EE8: beq s8,zero,0x00263f0c; native delay follows */
    { int taken=(cpu(30)==cpu(0));
      /* 00263EEC: move a0,s4 */ set(4,cpu(20));
      if(taken) goto L_00263f0c;
      goto L_00263ef0; }
L_00263ef0: ;
    /* 00263EF0: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_00263ef4: ;
    /* 00263EF4: move a2,s0 */ set(6,cpu(16));
L_00263ef8: ;
    /* 00263EF8: move a3,s1 */ set(7,cpu(17));
L_00263efc: ;
    /* 00263EFC: move t0,s7 */ set(8,cpu(23));
L_00263f00: ;
    /* 00263F00: move t1,zero */ set(9,cpu(0));
L_00263f04: ;
    /* 00263F04: jal 0x002627c0; native delay follows */
    set(31,UINT64_C(0x0000000000263f0c));
    /* 00263F08: li t2,0x1 */ set(10,UINT64_C(0x0000000000000001));
    nbAddNumEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10));
    goto L_00263f0c;
L_00263f0c: ;
    /* 00263F0C: move a0,s2 */ set(4,cpu(18));
L_00263f10: ;
    /* 00263F10: subu a3,zero,s7 */ set(7,sx((uint32_t)cpu(0)-(uint32_t)cpu(23)));
L_00263f14: ;
    /* 00263F14: move a1,s0 */ set(5,cpu(16));
L_00263f18: ;
    /* 00263F18: move a2,s1 */ set(6,cpu(17));
L_00263f1c: ;
    /* 00263F1C: jal 0x002629e8; native delay follows */
    set(31,UINT64_C(0x0000000000263f24));
    /* 00263F20: li t0,0x1 */ set(8,UINT64_C(0x0000000000000001));
    set(2,nbAddHpMpKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_00263f24;
L_00263f24: ;
    /* 00263F24: b 0x00263f7c; native delay follows */
    { /* 00263F28: nop  */ ; goto L_00263f7c; }
L_00263f30: ;
    /* 00263F30: bltz s6,0x00263f7c; native delay follows */
    { int taken=(lt(cpu(22),0));
      /* 00263F34: nop  */ ;
      if(taken) goto L_00263f7c;
      goto L_00263f38; }
L_00263f38: ;
    /* 00263F38: bne s5,zero,0x00263f68; native delay follows */
    { int taken=(cpu(21)!=cpu(0));
      /* 00263F3C: move a0,s2 */ set(4,cpu(18));
      if(taken) goto L_00263f68;
      goto L_00263f40; }
L_00263f40: ;
    /* 00263F40: beq s8,zero,0x00263f64; native delay follows */
    { int taken=(cpu(30)==cpu(0));
      /* 00263F44: move a0,s4 */ set(4,cpu(20));
      if(taken) goto L_00263f64;
      goto L_00263f48; }
L_00263f48: ;
    /* 00263F48: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_00263f4c: ;
    /* 00263F4C: move a2,s0 */ set(6,cpu(16));
L_00263f50: ;
    /* 00263F50: move a3,s1 */ set(7,cpu(17));
L_00263f54: ;
    /* 00263F54: move t0,s6 */ set(8,cpu(22));
L_00263f58: ;
    /* 00263F58: move t1,zero */ set(9,cpu(0));
L_00263f5c: ;
    /* 00263F5C: jal 0x002627c0; native delay follows */
    set(31,UINT64_C(0x0000000000263f64));
    /* 00263F60: move t2,zero */ set(10,cpu(0));
    nbAddNumEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10));
    goto L_00263f64;
L_00263f64: ;
    /* 00263F64: move a0,s2 */ set(4,cpu(18));
L_00263f68: ;
    /* 00263F68: subu a3,zero,s6 */ set(7,sx((uint32_t)cpu(0)-(uint32_t)cpu(22)));
L_00263f6c: ;
    /* 00263F6C: move a1,s0 */ set(5,cpu(16));
L_00263f70: ;
    /* 00263F70: move a2,s1 */ set(6,cpu(17));
L_00263f74: ;
    /* 00263F74: jal 0x002629e8; native delay follows */
    set(31,UINT64_C(0x0000000000263f7c));
    /* 00263F78: move t0,zero */ set(8,cpu(0));
    set(2,nbAddHpMpKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_00263f7c;
L_00263f7c: ;
    /* 00263F7C: beq s8,zero,0x00263fdc; native delay follows */
    { int taken=(cpu(30)==cpu(0));
      /* 00263F80: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
      if(taken) goto L_00263fdc;
      goto L_00263f84; }
L_00263f84: ;
    /* 00263F84: beq s3,v0,0x00263fa8; native delay follows */
    { int taken=(cpu(19)==cpu(2));
      /* 00263F88: slti v0,s3,0x2 */ set(2,lt(cpu(19),UINT64_C(0x0000000000000002)));
      if(taken) goto L_00263fa8;
      goto L_00263f8c; }
L_00263f8c: ;
    /* 00263F8C: bnel v0,zero,0x00263fe0; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      if(taken) { /* 00263F90: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000)))); goto L_00263fe0; }
      goto L_00263f94; }
L_00263f94: ;
    /* 00263F94: li v0,0x2 */ set(2,UINT64_C(0x0000000000000002));
L_00263f98: ;
    /* 00263F98: beq s3,v0,0x00263fc8; native delay follows */
    { int taken=(cpu(19)==cpu(2));
      /* 00263F9C: move a0,s4 */ set(4,cpu(20));
      if(taken) goto L_00263fc8;
      goto L_00263fa0; }
L_00263fa0: ;
    /* 00263FA0: b 0x00263fe0; native delay follows */
    { /* 00263FA4: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000)))); goto L_00263fe0; }
L_00263fa8: ;
    /* 00263FA8: move a0,s4 */ set(4,cpu(20));
L_00263fac: ;
    /* 00263FAC: move a2,s0 */ set(6,cpu(16));
L_00263fb0: ;
    /* 00263FB0: move a3,s1 */ set(7,cpu(17));
L_00263fb4: ;
    /* 00263FB4: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_00263fb8: ;
    /* 00263FB8: jal 0x002628d0; native delay follows */
    set(31,UINT64_C(0x0000000000263fc0));
    /* 00263FBC: li t0,0x2 */ set(8,UINT64_C(0x0000000000000002));
    nbAddMojiEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00263fc0;
L_00263fc0: ;
    /* 00263FC0: b 0x00263fe0; native delay follows */
    { /* 00263FC4: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000)))); goto L_00263fe0; }
L_00263fc8: ;
    /* 00263FC8: move a2,s0 */ set(6,cpu(16));
L_00263fcc: ;
    /* 00263FCC: move a3,s1 */ set(7,cpu(17));
L_00263fd0: ;
    /* 00263FD0: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_00263fd4: ;
    /* 00263FD4: jal 0x002628d0; native delay follows */
    set(31,UINT64_C(0x0000000000263fdc));
    /* 00263FD8: li t0,0x1 */ set(8,UINT64_C(0x0000000000000001));
    nbAddMojiEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8));
    goto L_00263fdc;
L_00263fdc: ;
    /* 00263FDC: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_00263fe0: ;
    /* 00263FE0: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_00263fe4: ;
    /* 00263FE4: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_00263fe8: ;
    /* 00263FE8: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_00263fec: ;
    /* 00263FEC: ld s3,0x18(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_00263ff0: ;
    /* 00263FF0: ld s4,0x20(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x00000020))));
L_00263ff4: ;
    /* 00263FF4: ld s5,0x28(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x00000028))));
L_00263ff8: ;
    /* 00263FF8: ld s6,0x30(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x00000030))));
L_00263ffc: ;
    /* 00263FFC: ld s7,0x38(sp) */ set(23,r64(ea(cpu(29),UINT32_C(0x00000038))));
L_00264000: ;
    /* 00264000: ld s8,0x40(sp) */ set(30,r64(ea(cpu(29),UINT32_C(0x00000040))));
L_00264004: ;
    /* 00264004: ld ra,0x48(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000048))));
L_00264008: ;
    /* 00264008: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 0026400C: addiu sp,sp,0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050))); ba_return_target(incoming_ra,target); return; }
}

static void body_00264010(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00264010u);
L_00264010: ;
    /* 00264010: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
L_00264014: ;
    /* 00264014: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_00264018: ;
    /* 00264018: move s0,a1 */ set(16,cpu(5));
L_0026401c: ;
    /* 0026401C: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00264020: ;
    /* 00264020: move s1,a0 */ set(17,cpu(4));
L_00264024: ;
    /* 00264024: sd s2,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(18));
L_00264028: ;
    /* 00264028: move s2,a2 */ set(18,cpu(6));
L_0026402c: ;
    /* 0026402C: sd s3,0x18(sp) */ w64(ea(cpu(29),UINT32_C(0x00000018)),(uint64_t)cpu(19));
L_00264030: ;
    /* 00264030: sd s4,0x20(sp) */ w64(ea(cpu(29),UINT32_C(0x00000020)),(uint64_t)cpu(20));
L_00264034: ;
    /* 00264034: move s4,t0 */ set(20,cpu(8));
L_00264038: ;
    /* 00264038: sd s5,0x28(sp) */ w64(ea(cpu(29),UINT32_C(0x00000028)),(uint64_t)cpu(21));
L_0026403c: ;
    /* 0026403C: move s5,t1 */ set(21,cpu(9));
L_00264040: ;
    /* 00264040: sd s6,0x30(sp) */ w64(ea(cpu(29),UINT32_C(0x00000030)),(uint64_t)cpu(22));
L_00264044: ;
    /* 00264044: move s6,t2 */ set(22,cpu(10));
L_00264048: ;
    /* 00264048: sd ra,0x38(sp) */ w64(ea(cpu(29),UINT32_C(0x00000038)),(uint64_t)cpu(31));
L_0026404c: ;
    /* 0026404C: lh v0,0x92(s2) */ set(2,sx((uint32_t)i16(r16(ea(cpu(18),UINT32_C(0x00000092))))));
L_00264050: ;
    /* 00264050: slti v0,v0,0x10 */ set(2,lt(cpu(2),UINT64_C(0x0000000000000010)));
L_00264054: ;
    /* 00264054: sltiu s3,v0,0x1 */ set(19,(cpu(2)<UINT64_C(0x0000000000000001)));
L_00264058: ;
    /* 00264058: bne s3,zero,0x002640b8; native delay follows */
    { int taken=(cpu(19)!=cpu(0));
      /* 0026405C: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
      if(taken) goto L_002640b8;
      goto L_00264060; }
L_00264060: ;
    /* 00264060: beq a3,v0,0x00264088; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00264064: slti v0,a3,0x2 */ set(2,lt(cpu(7),UINT64_C(0x0000000000000002)));
      if(taken) goto L_00264088;
      goto L_00264068; }
L_00264068: ;
    /* 00264068: bne v0,zero,0x002640b8; native delay follows */
    { int taken=(cpu(2)!=cpu(0));
      /* 0026406C: li v0,0x2 */ set(2,UINT64_C(0x0000000000000002));
      if(taken) goto L_002640b8;
      goto L_00264070; }
L_00264070: ;
    /* 00264070: beq a3,v0,0x002640b8; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 00264074: li v0,0x3 */ set(2,UINT64_C(0x0000000000000003));
      if(taken) goto L_002640b8;
      goto L_00264078; }
L_00264078: ;
    /* 00264078: beq a3,v0,0x00264098; native delay follows */
    { int taken=(cpu(7)==cpu(2));
      /* 0026407C: li t0,0xa */ set(8,UINT64_C(0x000000000000000a));
      if(taken) goto L_00264098;
      goto L_00264080; }
L_00264080: ;
    /* 00264080: b 0x002640b8; native delay follows */
    { /* 00264084: nop  */ ; goto L_002640b8; }
L_00264088: ;
    /* 00264088: jal 0x00262480; native delay follows */
    set(31,UINT64_C(0x0000000000264090));
    /* 0026408C: li a3,0x2 */ set(7,UINT64_C(0x0000000000000002));
    body_00262480();
    goto L_00264090;
L_00264090: ;
    /* 00264090: b 0x002640b8; native delay follows */
    { /* 00264094: nop  */ ; goto L_002640b8; }
L_00264098: ;
    /* 00264098: lui a3,0x8086 */ set(7,sx(UINT32_C(0x80860000)));
L_0026409c: ;
    /* 0026409C: jal 0x00261ca0; native delay follows */
    set(31,UINT64_C(0x00000000002640a4));
    /* 002640A0: ori a3,a3,0xeb9b */ set(7,cpu(7)|UINT64_C(0x000000000000eb9b));
    set(2,nbAddUnitColKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_002640a4;
L_002640a4: ;
    /* 002640A4: addiu a0,s1,0xa */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x0000000a)));
L_002640a8: ;
    /* 002640A8: move a1,s0 */ set(5,cpu(16));
L_002640ac: ;
    /* 002640AC: move a2,s2 */ set(6,cpu(18));
L_002640b0: ;
    /* 002640B0: jal 0x00261d20; native delay follows */
    set(31,UINT64_C(0x00000000002640b8));
    /* 002640B4: li a3,0xa */ set(7,UINT64_C(0x000000000000000a));
    set(2,nbAddUnitHomeColKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7)));
    goto L_002640b8;
L_002640b8: ;
    /* 002640B8: bltz s4,0x00264120; native delay follows */
    { int taken=(lt(cpu(20),0));
      /* 002640BC: nop  */ ;
      if(taken) goto L_00264120;
      goto L_002640c0; }
L_002640c0: ;
    /* 002640C0: bltz s5,0x00264170; native delay follows */
    { int taken=(lt(cpu(21),0));
      /* 002640C4: nop  */ ;
      if(taken) goto L_00264170;
      goto L_002640c8; }
L_002640c8: ;
    /* 002640C8: bnel s3,zero,0x002640f4; native delay follows */
    { int taken=(cpu(19)!=cpu(0));
      if(taken) { /* 002640CC: move a3,s4 */ set(7,cpu(20)); goto L_002640f4; }
      goto L_002640d0; }
L_002640d0: ;
    /* 002640D0: addiu a0,s1,0x1 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_002640d4: ;
    /* 002640D4: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_002640d8: ;
    /* 002640D8: move a2,s0 */ set(6,cpu(16));
L_002640dc: ;
    /* 002640DC: move a3,s2 */ set(7,cpu(18));
L_002640e0: ;
    /* 002640E0: move t0,s4 */ set(8,cpu(20));
L_002640e4: ;
    /* 002640E4: move t1,s5 */ set(9,cpu(21));
L_002640e8: ;
    /* 002640E8: jal 0x002627c0; native delay follows */
    set(31,UINT64_C(0x00000000002640f0));
    /* 002640EC: li t2,0x5 */ set(10,UINT64_C(0x0000000000000005));
    nbAddNumEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10));
    goto L_002640f0;
L_002640f0: ;
    /* 002640F0: move a3,s4 */ set(7,cpu(20));
L_002640f4: ;
    /* 002640F4: move t0,zero */ set(8,cpu(0));
L_002640f8: ;
    /* 002640F8: move a0,s1 */ set(4,cpu(17));
L_002640fc: ;
    /* 002640FC: move a1,s0 */ set(5,cpu(16));
L_00264100: ;
    /* 00264100: jal 0x002629e8; native delay follows */
    set(31,UINT64_C(0x0000000000264108));
    /* 00264104: move a2,s2 */ set(6,cpu(18));
    set(2,nbAddHpMpKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_00264108;
L_00264108: ;
    /* 00264108: move a0,s1 */ set(4,cpu(17));
L_0026410c: ;
    /* 0026410C: move a1,s0 */ set(5,cpu(16));
L_00264110: ;
    /* 00264110: move a2,s2 */ set(6,cpu(18));
L_00264114: ;
    /* 00264114: b 0x00264160; native delay follows */
    { /* 00264118: move a3,s5 */ set(7,cpu(21)); goto L_00264160; }
L_00264120: ;
    /* 00264120: bltz s5,0x00264170; native delay follows */
    { int taken=(lt(cpu(21),0));
      /* 00264124: nop  */ ;
      if(taken) goto L_00264170;
      goto L_00264128; }
L_00264128: ;
    /* 00264128: bne s3,zero,0x00264154; native delay follows */
    { int taken=(cpu(19)!=cpu(0));
      /* 0026412C: move a3,s5 */ set(7,cpu(21));
      if(taken) goto L_00264154;
      goto L_00264130; }
L_00264130: ;
    /* 00264130: addiu a0,s1,0x1 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00264134: ;
    /* 00264134: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_00264138: ;
    /* 00264138: move a2,s0 */ set(6,cpu(16));
L_0026413c: ;
    /* 0026413C: move a3,s2 */ set(7,cpu(18));
L_00264140: ;
    /* 00264140: move t0,s5 */ set(8,cpu(21));
L_00264144: ;
    /* 00264144: move t1,zero */ set(9,cpu(0));
L_00264148: ;
    /* 00264148: jal 0x002627c0; native delay follows */
    set(31,UINT64_C(0x0000000000264150));
    /* 0026414C: li t2,0x3 */ set(10,UINT64_C(0x0000000000000003));
    nbAddNumEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10));
    goto L_00264150;
L_00264150: ;
    /* 00264150: move a3,s5 */ set(7,cpu(21));
L_00264154: ;
    /* 00264154: move a0,s1 */ set(4,cpu(17));
L_00264158: ;
    /* 00264158: move a1,s0 */ set(5,cpu(16));
L_0026415c: ;
    /* 0026415C: move a2,s2 */ set(6,cpu(18));
L_00264160: ;
    /* 00264160: jal 0x002629e8; native delay follows */
    set(31,UINT64_C(0x0000000000264168));
    /* 00264164: li t0,0x1 */ set(8,UINT64_C(0x0000000000000001));
    set(2,nbAddHpMpKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_00264168;
L_00264168: ;
    /* 00264168: b 0x002641b8; native delay follows */
    { /* 0026416C: nop  */ ; goto L_002641b8; }
L_00264170: ;
    /* 00264170: bltz s4,0x002641b8; native delay follows */
    { int taken=(lt(cpu(20),0));
      /* 00264174: nop  */ ;
      if(taken) goto L_002641b8;
      goto L_00264178; }
L_00264178: ;
    /* 00264178: bne s3,zero,0x002641a4; native delay follows */
    { int taken=(cpu(19)!=cpu(0));
      /* 0026417C: move a3,s4 */ set(7,cpu(20));
      if(taken) goto L_002641a4;
      goto L_00264180; }
L_00264180: ;
    /* 00264180: addiu a0,s1,0x1 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
L_00264184: ;
    /* 00264184: li a1,0x2d */ set(5,UINT64_C(0x000000000000002d));
L_00264188: ;
    /* 00264188: move a2,s0 */ set(6,cpu(16));
L_0026418c: ;
    /* 0026418C: move a3,s2 */ set(7,cpu(18));
L_00264190: ;
    /* 00264190: move t0,s4 */ set(8,cpu(20));
L_00264194: ;
    /* 00264194: move t1,zero */ set(9,cpu(0));
L_00264198: ;
    /* 00264198: jal 0x002627c0; native delay follows */
    set(31,UINT64_C(0x00000000002641a0));
    /* 0026419C: li t2,0x2 */ set(10,UINT64_C(0x0000000000000002));
    nbAddNumEffKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8),cpu(9),cpu(10));
    goto L_002641a0;
L_002641a0: ;
    /* 002641A0: move a3,s4 */ set(7,cpu(20));
L_002641a4: ;
    /* 002641A4: move a0,s1 */ set(4,cpu(17));
L_002641a8: ;
    /* 002641A8: move a1,s0 */ set(5,cpu(16));
L_002641ac: ;
    /* 002641AC: move a2,s2 */ set(6,cpu(18));
L_002641b0: ;
    /* 002641B0: jal 0x002629e8; native delay follows */
    set(31,UINT64_C(0x00000000002641b8));
    /* 002641B4: move t0,zero */ set(8,cpu(0));
    set(2,nbAddHpMpKoukaPacket(cpu(4),cpu(5),cpu(6),cpu(7),cpu(8)));
    goto L_002641b8;
L_002641b8: ;
    /* 002641B8: beq s6,zero,0x002641cc; native delay follows */
    { int taken=(cpu(22)==cpu(0));
      /* 002641BC: addiu a0,s1,0x1 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
      if(taken) goto L_002641cc;
      goto L_002641c0; }
L_002641c0: ;
    /* 002641C0: move a1,s0 */ set(5,cpu(16));
L_002641c4: ;
    /* 002641C4: jal 0x002645a8; native delay follows */
    set(31,UINT64_C(0x00000000002641cc));
    /* 002641C8: move a2,s2 */ set(6,cpu(18));
    set(2,nbMakeBadKaifukuPacket(cpu(4),cpu(5),cpu(6)));
    goto L_002641cc;
L_002641cc: ;
    /* 002641CC: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_002641d0: ;
    /* 002641D0: li v0,0x1 */ set(2,UINT64_C(0x0000000000000001));
L_002641d4: ;
    /* 002641D4: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_002641d8: ;
    /* 002641D8: ld s2,0x10(sp) */ set(18,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_002641dc: ;
    /* 002641DC: ld s3,0x18(sp) */ set(19,r64(ea(cpu(29),UINT32_C(0x00000018))));
L_002641e0: ;
    /* 002641E0: ld s4,0x20(sp) */ set(20,r64(ea(cpu(29),UINT32_C(0x00000020))));
L_002641e4: ;
    /* 002641E4: ld s5,0x28(sp) */ set(21,r64(ea(cpu(29),UINT32_C(0x00000028))));
L_002641e8: ;
    /* 002641E8: ld s6,0x30(sp) */ set(22,r64(ea(cpu(29),UINT32_C(0x00000030))));
L_002641ec: ;
    /* 002641EC: ld ra,0x38(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000038))));
L_002641f0: ;
    /* 002641F0: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 002641F4: addiu sp,sp,0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040))); ba_return_target(incoming_ra,target); return; }
}

uint64_t ps2BattleAction_00171A00(uint64_t a0)
{
    set(4,a0);
    body_00171a00();
    return cpu(2);
}

uint64_t ps2BattleAction_00171CC8(uint64_t a0)
{
    set(4,a0);
    body_00171cc8();
    return cpu(2);
}

uint64_t ps2BattleAction_00172178(uint64_t a0)
{
    set(4,a0);
    body_00172178();
    return cpu(2);
}

uint64_t ps2BattleAction_00173CB0(uint64_t a0, uint64_t a1)
{
    set(4,a0);
    set(5,a1);
    body_00173cb0();
    return cpu(2);
}

uint64_t ps2BattleAction_00173EF0(uint64_t a0)
{
    set(4,a0);
    body_00173ef0();
    return cpu(2);
}

void ps2BattleAction_0024F420(uint64_t a0, uint64_t a1)
{
    set(4,a0);
    set(5,a1);
    body_0024f420();
}

void ps2BattleAction_0024F478(uint64_t a0, uint64_t a1)
{
    set(4,a0);
    set(5,a1);
    body_0024f478();
}

void ps2BattleAction_0024F548(uint64_t a0, float f12)
{
    set(4,a0);
    fpr()[12]=fbits(f12);
    body_0024f548();
}

void ps2BattleAction_0024F5B0(uint64_t a0, uint64_t a1)
{
    set(4,a0);
    set(5,a1);
    body_0024f5b0();
}

void ps2BattleAction_0024F5C8(uint64_t a0, uint64_t a1)
{
    set(4,a0);
    set(5,a1);
    body_0024f5c8();
}

void ps2BattleAction_0024FF60(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2, float f12)
{
    set(4,a0);
    set(5,a1);
    set(6,a2);
    set(7,a3);
    set(8,t0);
    set(9,t1);
    set(10,t2);
    fpr()[12]=fbits(f12);
    body_0024ff60();
}

uint64_t ps2BattleAction_00251750(uint64_t a0, uint64_t a1)
{
    set(4,a0);
    set(5,a1);
    body_00251750();
    return cpu(2);
}

uint64_t ps2BattleAction_002521C8(uint64_t a0, uint64_t a1, uint64_t a2)
{
    set(4,a0);
    set(5,a1);
    set(6,a2);
    body_002521c8();
    return cpu(2);
}

void ps2BattleAction_002592B0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3)
{
    set(4,a0);
    set(5,a1);
    set(6,a2);
    set(7,a3);
    body_002592b0();
}

uint64_t ps2BattleAction_00259300(uint64_t a0, uint64_t a1)
{
    set(4,a0);
    set(5,a1);
    body_00259300();
    return cpu(2);
}

uint64_t ps2BattleAction_00262480(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3)
{
    set(4,a0);
    set(5,a1);
    set(6,a2);
    set(7,a3);
    body_00262480();
    return cpu(2);
}

uint64_t ps2BattleAction_002634C8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0)
{
    set(4,a0);
    set(5,a1);
    set(6,a2);
    set(7,a3);
    set(8,t0);
    body_002634c8();
    return cpu(2);
}

uint64_t ps2BattleAction_00263918(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0)
{
    set(4,a0);
    set(5,a1);
    set(6,a2);
    set(7,a3);
    set(8,t0);
    body_00263918();
    return cpu(2);
}

uint64_t ps2BattleAction_00263C00(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2, uint64_t t3, uint32_t stack_0, uint32_t stack_8, uint32_t stack_16, uint32_t stack_24)
{
    set(4,a0);
    set(5,a1);
    set(6,a2);
    set(7,a3);
    set(8,t0);
    set(9,t1);
    set(10,t2);
    set(11,t3);
    w32(ea(cpu(29),0),stack_0);
    w32(ea(cpu(29),8),stack_8);
    w32(ea(cpu(29),16),stack_16);
    w32(ea(cpu(29),24),stack_24);
    body_00263c00();
    return cpu(2);
}

uint64_t ps2BattleAction_00264010(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2)
{
    set(4,a0);
    set(5,a1);
    set(6,a2);
    set(7,a3);
    set(8,t0);
    set(9,t1);
    set(10,t2);
    body_00264010();
    return cpu(2);
}

/* Registered dependency extensions: exact native frames, zero identity credit. */
static void body_00175a88(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00175a88u);
L_00175a88: ;
    /* 00175A88: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
L_00175a8c: ;
    /* 00175A8C: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_00175a90: ;
    /* 00175A90: move s0,a0 */ set(16,cpu(4));
L_00175a94: ;
    /* 00175A94: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00175a98: ;
    /* 00175A98: sd ra,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(31));
L_00175a9c: ;
    /* 00175A9C: jal 0x002a8af8; native delay follows */
    set(31,0x00175aa4u);
    /* 00175AA0: li a0,0x8 */ set(4,8);
    set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
    goto L_00175aa4;
L_00175aa4: ;
    /* 00175AA4: lhu v1,0x0(s0) */ set(3,r16(ea(cpu(16),UINT32_C(0x00000000))));
L_00175aa8: ;
    /* 00175AA8: move s1,v0 */ set(17,cpu(2));
L_00175aac: ;
    /* 00175AAC: lw a0,0x4(s0) */ set(4,sx(r32(ea(cpu(16),UINT32_C(0x00000004)))));
L_00175ab0: ;
    /* 00175AB0: sh v1,0x0(s1) */ w16(ea(cpu(17),UINT32_C(0x00000000)),(uint16_t)cpu(3));
L_00175ab4: ;
    /* 00175AB4: lhu v0,0x0(s0) */ set(2,r16(ea(cpu(16),UINT32_C(0x00000000))));
L_00175ab8: ;
    /* 00175AB8: sll v1,v0,0x2 */ set(3,sx((uint32_t)cpu(2)<<2));
L_00175abc: ;
    /* 00175ABC: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
L_00175ac0: ;
    /* 00175AC0: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
L_00175ac4: ;
    /* 00175AC4: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
L_00175ac8: ;
    /* 00175AC8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
L_00175acc: ;
    /* 00175ACC: lw v0,-0x21b4(v0) */ set(2,sx(r32(ea(cpu(2),UINT32_C(0xffffde4c)))));
L_00175ad0: ;
    /* 00175AD0: jalr v0; native delay follows */
    { uint64_t target=cpu(2); set(31,0x00175ad8u);
      /* 00175AD4: nop  */ ; part_copy_callback(target); }
    goto L_00175ad8;
L_00175ad8: ;
    /* 00175AD8: sw v0,0x4(s1) */ w32(ea(cpu(17),UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_00175adc: ;
    /* 00175ADC: move v0,s1 */ set(2,cpu(17));
L_00175ae0: ;
    /* 00175AE0: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_00175ae4: ;
    /* 00175AE4: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_00175ae8: ;
    /* 00175AE8: ld ra,0x10(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_00175aec: ;
    /* 00175AEC: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 00175AF0: addiu sp,sp,0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020))); ba_return_target(incoming_ra,target); return; }
}

static void body_00176038(void)
{
    uint64_t incoming_ra=cpu(31);
    nocturneEffectAxisNoteEntry(0x00176038u);
L_00176038: ;
    /* 00176038: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
L_0017603c: ;
    /* 0017603C: sd s1,0x8(sp) */ w64(ea(cpu(29),UINT32_C(0x00000008)),(uint64_t)cpu(17));
L_00176040: ;
    /* 00176040: move s1,a0 */ set(17,cpu(4));
L_00176044: ;
    /* 00176044: sd s0,0x0(sp) */ w64(ea(cpu(29),UINT32_C(0x00000000)),(uint64_t)cpu(16));
L_00176048: ;
    /* 00176048: sd ra,0x10(sp) */ w64(ea(cpu(29),UINT32_C(0x00000010)),(uint64_t)cpu(31));
L_0017604c: ;
    /* 0017604C: jal 0x002a8af8; native delay follows */
    set(31,0x00176054u);
    /* 00176050: li a0,0xc */ set(4,12);
    set(2,ps2EffectPoolAllocate_002A8AF8(cpu(4)));
    goto L_00176054;
L_00176054: ;
    /* 00176054: lw a0,0x0(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000000)))));
L_00176058: ;
    /* 00176058: move s0,v0 */ set(16,cpu(2));
L_0017605c: ;
    /* 0017605C: lui v1,0x32 */ set(3,sx(UINT32_C(0x00320000)));
L_00176060: ;
    /* 00176060: sll a1,a0,0x2 */ set(5,sx((uint32_t)cpu(4)<<2));
L_00176064: ;
    /* 00176064: addiu v1,v1,-0x2070 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffdf90)));
L_00176068: ;
    /* 00176068: addu v0,a1,a0 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
L_0017606c: ;
    /* 0017606C: sw a0,0x0(s0) */ w32(ea(cpu(16),UINT32_C(0x00000000)),(uint32_t)cpu(4));
L_00176070: ;
    /* 00176070: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
L_00176074: ;
    /* 00176074: addu a2,v0,v1 */ set(6,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
L_00176078: ;
    /* 00176078: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
L_0017607c: ;
    /* 0017607C: lw v1,0xc(v1) */ set(3,sx(r32(ea(cpu(3),UINT32_C(0x0000000c)))));
L_00176080: ;
    /* 00176080: lw v0,0x4(s1) */ set(2,sx(r32(ea(cpu(17),UINT32_C(0x00000004)))));
L_00176084: ;
    /* 00176084: sll a0,v0,0x2 */ set(4,sx((uint32_t)cpu(2)<<2));
L_00176088: ;
    /* 00176088: bne v1,zero,0x001760b8; native delay follows */
    { int taken=(cpu(3)!=cpu(0)); /* 0017608C: sw v0,0x4(s0) */ w32(ea(cpu(16),UINT32_C(0x00000004)),(uint32_t)cpu(2));
      if(taken) goto L_001760b8; goto L_00176090; }
L_00176090: ;
    /* 00176090: lui v1,0x32 */ set(3,sx(UINT32_C(0x00320000)));
L_00176094: ;
    /* 00176094: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
L_00176098: ;
    /* 00176098: lw v1,-0x2230(v1) */ set(3,sx(r32(ea(cpu(3),UINT32_C(0xffffddd0)))));
L_0017609c: ;
    /* 0017609C: lw v0,0x0(a2) */ set(2,sx(r32(ea(cpu(6),UINT32_C(0x00000000)))));
L_001760a0: ;
    /* 001760A0: addu v1,a0,v1 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
L_001760a4: ;
    /* 001760A4: jalr v0; native delay follows */
    { uint64_t target=cpu(2); set(31,0x001760acu);
      /* 001760A8: lw a0,0x0(v1) */ set(4,sx(r32(ea(cpu(3),UINT32_C(0x00000000))))); part_copy_callback(target); }
    goto L_001760ac;
L_001760ac: ;
    /* 001760AC: b 0x001760c4; native delay follows */
    /* 001760B0: sw v0,0x8(s0) */ w32(ea(cpu(16),UINT32_C(0x00000008)),(uint32_t)cpu(2)); goto L_001760c4;
L_001760b8: ;
    /* 001760B8: jalr v1; native delay follows */
    { uint64_t target=cpu(3); set(31,0x001760c0u);
      /* 001760BC: lw a0,0x8(s1) */ set(4,sx(r32(ea(cpu(17),UINT32_C(0x00000008))))); part_copy_callback(target); }
    goto L_001760c0;
L_001760c0: ;
    /* 001760C0: sw v0,0x8(s0) */ w32(ea(cpu(16),UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_001760c4: ;
    /* 001760C4: move v0,s0 */ set(2,cpu(16));
L_001760c8: ;
    /* 001760C8: ld s0,0x0(sp) */ set(16,r64(ea(cpu(29),UINT32_C(0x00000000))));
L_001760cc: ;
    /* 001760CC: ld s1,0x8(sp) */ set(17,r64(ea(cpu(29),UINT32_C(0x00000008))));
L_001760d0: ;
    /* 001760D0: ld ra,0x10(sp) */ set(31,r64(ea(cpu(29),UINT32_C(0x00000010))));
L_001760d4: ;
    /* 001760D4: jr ra; native delay follows */
    { uint64_t target=cpu(31); /* 001760D8: addiu sp,sp,0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020))); ba_return_target(incoming_ra,target); return; }
}

static void part_copy_callback(uint64_t target)
{
    if((uint32_t)target==0x00176038u) { body_00176038(); return; }
    /* Existing host callback transport invokes the actual selected game body;
     * its finite target binding belongs to the declared resource contract. */
    set(2,nocturneCallEffectCopy((uint32_t)target,cpu(4)));
}
uint64_t ps2BattleActionPartCopy_00175A88(uint64_t part)
{
    set(4,part); body_00175a88(); return cpu(2);
}
uint64_t ps2BattleActionPcpCopy_00176038(uint64_t pcp)
{
    set(4,pcp); body_00176038(); return cpu(2);
}
