#include "battle_panel_renderer_bundle.h"
#include "battle_panel_color_native.h"
#include "battle_panel_color_privileged.h"
/* Whole fixed original instruction algorithms for registered printf9.
 * Each statement is tied to a native PC. No runtime opcode interpreter,
 * host va_list, captured output provider, stack spill injection or frame shim.
 */
#include "battle_action_printf_frames.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include "libc_formatter.h"
#include "libc_stream.h"
#include "libc_vector.h"
#include "libc_cvt.h"
#include "libc_console.h"
#include "ps2_memory.h"
#include "ps2_sdk_frontier.h"
#include "compiler_numeric.h"
#include "nocturne.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Native fallthrough PCs are retained even when the compiler combines CFGs. */
#ifdef _MSC_VER
#pragma warning(disable:4102)
#endif
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattlePanelColorAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelColorSetStackPointer(q[0]);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void pkLq(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneEffectHostCpuWrite(r,q);}
static void sq(unsigned r,uint32_t a){uint32_t q[4];nocturneEffectHostCpuRead(r,q);memcpy(at(a&~15u),q,16);}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming){fprintf(stderr,"Native printf return address changed: %llx/%llx\n",(unsigned long long)target,(unsigned long long)incoming);abort();}}


/* Three actual WriteVectors JALR sites latch the target before delay. This
 * known target comes from the original StreamRecordInitialize +24 store.
 * Its real registered writer preserves the actual external kernel boundary.
 * Foreign executable targets require their genuine typed route, never a value.
 */



static uint64_t body_002d4454(void){
nocturneEffectAxisNoteEntry(0x002d4454u);
uint64_t incoming=cpu(31);
/* 002d4454: move t0,a0 */ set(8,cpu(4));
/* 002d4458: sltu v0,a1,t0 */ set(2,cpu(5)<cpu(8));
/* 002d445c: beq v0,zero,0x002d44ac */ {int taken=(cpu(2)==cpu(0));/* delay 002d4460 */ set(3,cpu(8));if(taken){goto L_002d44ac;}}
/* 002d4464: addu a3,a1,a2 */ set(7,sx((uint32_t)cpu(5)+(uint32_t)cpu(6)));
/* 002d4468: sltu v0,t0,a3 */ set(2,cpu(8)<cpu(7));
/* 002d446c: beq v0,zero,0x002d44ac */ {int taken=(cpu(2)==cpu(0));/* delay 002d4470 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002d44ac;}}
/* 002d4474: addu v1,t0,a2 */ set(3,sx((uint32_t)cpu(8)+(uint32_t)cpu(6)));
/* 002d4478: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d447c: beq a2,v0,0x002d4550 */ {int taken=(cpu(6)==cpu(2));/* delay 002d4480 */ set(5,cpu(7));if(taken){goto L_002d4550;}}
/* 002d4484: move a0,v0 */ set(4,cpu(2));
L_002d4488:;
/* 002d4488: addiu a1,a1,-0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 002d448c: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 002d4490: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d4494: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d4498: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d449c: bne a2,a0,0x002d4488 */ {int taken=(cpu(6)!=cpu(4));/* delay 002d44a0 */ if(taken){goto L_002d4488;}}
/* 002d44a4: jr ra */ {uint64_t target=cpu(31);/* delay 002d44a8 */ set(2,cpu(8));checkReturn(target,incoming);return cpu(2);}
L_002d44ac:;
/* 002d44ac: sltiu v0,a2,0x20 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d44b0: bnel v0,zero,0x002d4528 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d44b4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));goto L_002d4528;}}
/* 002d44b8: or v0,a1,v1 */ set(2,cpu(5)|cpu(3));
/* 002d44bc: andi v0,v0,0xf */ set(2,cpu(2)&UINT32_C(0x0000000f));
/* 002d44c0: bnel v0,zero,0x002d4528 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d44c4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));goto L_002d4528;}}
/* 002d44c8: move a3,v1 */ set(7,cpu(3));
L_002d44cc:;
/* 002d44cc: lq v1,0x0(a1) */ pkLq(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d44d0: addiu a2,a2,-0x20 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffe0)));
/* 002d44d4: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d44d8: sltiu a0,a2,0x20 */ set(4,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d44dc: sq v1,0x0(a3) */ sq(3,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d44e0: addiu a3,a3,0x10 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));
/* 002d44e4: lq v0,0x0(a1) */ pkLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d44e8: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d44ec: sq v0,0x0(a3) */ sq(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d44f0: beq a0,zero,0x002d44cc */ {int taken=(cpu(4)==cpu(0));/* delay 002d44f4 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));if(taken){goto L_002d44cc;}}
/* 002d44f8: sltiu v0,a2,0x8 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d44fc: bne v0,zero,0x002d4524 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4500 */ set(3,cpu(7));if(taken){goto L_002d4524;}}
L_002d4504:;
/* 002d4504: ld v1,0x0(a1) */ restore(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d4508: addiu a2,a2,-0x8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xfffffff8)));
/* 002d450c: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 002d4510: sltiu v0,a2,0x8 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d4514: sd v1,0x0(a3) */ save(3,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d4518: beq v0,zero,0x002d4504 */ {int taken=(cpu(2)==cpu(0));/* delay 002d451c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000008)));if(taken){goto L_002d4504;}}
/* 002d4520: move v1,a3 */ set(3,cpu(7));
L_002d4524:;
/* 002d4524: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
L_002d4528:;
/* 002d4528: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d452c: beq a2,v0,0x002d4550 */ {int taken=(cpu(6)==cpu(2));/* delay 002d4530 */ set(4,cpu(2));if(taken){goto L_002d4550;}}
L_002d4534:;
/* 002d4534: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d4538: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d453c: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002d4540: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d4544: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d4548: bne a2,a0,0x002d4534 */ {int taken=(cpu(6)!=cpu(4));/* delay 002d454c */ if(taken){goto L_002d4534;}}
L_002d4550:;
/* 002d4550: jr ra */ {uint64_t target=cpu(31);/* delay 002d4554 */ set(2,cpu(8));checkReturn(target,incoming);return cpu(2);}
}
static uint64_t body_002d4748(void){
nocturneEffectAxisNoteEntry(0x002d4748u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002d4748: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 002d474c: lui t4,0x53 */ set(12,sx(UINT32_C(0x00530000)));
/* 002d4750: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d4754: sd a1,0x38(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d4758: move a1,a0 */ set(5,cpu(4));
/* 002d475c: sd a2,0x40(sp) */ save(6,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d4760: addiu a2,sp,0x38 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000038)));
/* 002d4764: sd a3,0x48(sp) */ save(7,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d4768: sd t0,0x50(sp) */ save(8,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d476c: sd t1,0x58(sp) */ save(9,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002d4770: sd t2,0x60(sp) */ save(10,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d4774: sd t3,0x68(sp) */ save(11,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002d4778: swc1 f12,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[12]);
/* 002d477c: swc1 f13,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),f[13]);
/* 002d4780: swc1 f14,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[14]);
/* 002d4784: swc1 f15,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[15]);
/* 002d4788: swc1 f16,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[16]);
/* 002d478c: swc1 f17,0x2c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000002c)),f[17]);
/* 002d4790: swc1 f18,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[18]);
/* 002d4794: swc1 f19,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),f[19]);
/* 002d4798: lw v0,-0x41d8(t4) */ lw(2,ea(12,(int32_t)UINT32_C(0xffffbe28)));
/* 002d479c: lw v1,0x8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 002d47a0: sw v0,0x54(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));
/* 002d47a4: jal 0x002d6600 */ set(31,0x002d47acu);/* delay 002d47a8 */ lw(4,ea(2,(int32_t)UINT32_C(0x00000008)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6600),UINT32_C(0x002d47a4));
/* 002d47ac: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d47b0: jr ra */ {uint64_t target=cpu(31);/* delay 002d47b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return cpu(2);}
}
static uint64_t body_002d6500(void){
nocturneEffectAxisNoteEntry(0x002d6500u);
uint64_t incoming=cpu(31);
/* 002d6500: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002d6504: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d6508: move s0,a1 */ set(16,cpu(5));
/* 002d650c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d6510: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002d6514: bne v0,zero,0x002d6528 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d6518 */ set(2,cpu(0));if(taken){goto L_002d6528;}}
/* 002d651c: b 0x002d6538 */ /* delay 002d6520 */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));goto L_002d6538;
L_002d6528:;
/* 002d6528: jal 0x002d9e00 */ set(31,0x002d6530u);/* delay 002d652c */ nocturneBattlePanelRendererCall(UINT32_C(0x002d9e00),UINT32_C(0x002d6528));
/* 002d6530: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002d6534: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
L_002d6538:;
/* 002d6538: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d653c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d6540: jr ra */ {uint64_t target=cpu(31);/* delay 002d6544 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
static uint64_t body_002d6600(void){
nocturneEffectAxisNoteEntry(0x002d6600u);
/* 002d6600: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002d6604: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d6608: move s0,a0 */ set(16,cpu(4));
/* 002d660c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d6610: move s1,a1 */ set(17,cpu(5));
/* 002d6614: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d6618: move s2,a2 */ set(18,cpu(6));
/* 002d661c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d6620: lw a0,0x54(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000054)));
/* 002d6624: bne a0,zero,0x002d6638 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d6628 */ set(2,sx(UINT32_C(0x00530000)));if(taken){goto L_002d6638;}}
/* 002d662c: lw v0,-0x41d8(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffffbe28)));
/* 002d6630: sw v0,0x54(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));
/* 002d6634: move a0,v0 */ set(4,cpu(2));
L_002d6638:;
/* 002d6638: lw v0,0x38(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000038)));
/* 002d663c: bne v0,zero,0x002d6654 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d6640 */ set(5,cpu(16));if(taken){goto L_002d6654;}}
/* 002d6644: jal 0x002d9908 */ set(31,0x002d664cu);/* delay 002d6648 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d9908),UINT32_C(0x002d6644));
/* 002d664c: lw a0,0x54(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000054)));
/* 002d6650: move a1,s0 */ set(5,cpu(16));
L_002d6654:;
/* 002d6654: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d6658: move a2,s1 */ set(6,cpu(17));
/* 002d665c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d6660: move a3,s2 */ set(7,cpu(18));
/* 002d6664: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d6668: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d666c: j 0x002d6678 */ /* delay 002d6670 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6678),UINT32_C(0x002d666c));return cpu(2);
}
static uint64_t body_002d6678(void){
nocturneEffectAxisNoteEntry(0x002d6678u);
uint64_t incoming=cpu(31);
/* 002d6678: addiu sp,sp,-0x290 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffd70)));
/* 002d667c: sd s0,0x240(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000240)));
/* 002d6680: move s0,a2 */ set(16,cpu(6));
/* 002d6684: sd s6,0x270(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000270)));
/* 002d6688: move s6,a3 */ set(22,cpu(7));
/* 002d668c: sw a0,0x1e4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000001e4)),(uint32_t)cpu(4));
/* 002d6690: sd s1,0x248(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000248)));
/* 002d6694: sd s2,0x250(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000250)));
/* 002d6698: sd s3,0x258(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000258)));
/* 002d669c: sd s4,0x260(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000260)));
/* 002d66a0: sd s5,0x268(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000268)));
/* 002d66a4: sd s7,0x278(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000278)));
/* 002d66a8: sd s8,0x280(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000280)));
/* 002d66ac: sd ra,0x288(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000288)));
/* 002d66b0: jal 0x002da340 */ set(31,0x002d66b8u);/* delay 002d66b4 */ sw(ea(29,(int32_t)UINT32_C(0x000001e8)),(uint32_t)cpu(5));nocturneBattlePanelRendererCall(UINT32_C(0x002da340),UINT32_C(0x002d66b0));
/* 002d66b8: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d66bc: lw v0,0x0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002d66c0: lhu v1,0xc(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x0000000c))));
/* 002d66c4: sw v0,0x1f4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000001f4)),(uint32_t)cpu(2));
/* 002d66c8: andi v0,v1,0x8 */ set(2,cpu(3)&UINT32_C(0x00000008));
/* 002d66cc: beq v0,zero,0x002d66e0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d66d0 */ sw(ea(29,(int32_t)UINT32_C(0x000001d8)),(uint32_t)cpu(0));if(taken){goto L_002d66e0;}}
/* 002d66d4: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002d66d8: bnel v0,zero,0x002d66fc */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d66dc */ set(3,cpu(3)&UINT32_C(0x0000001a));goto L_002d66fc;}}
L_002d66e0:;
/* 002d66e0: jal 0x002d8038 */ set(31,0x002d66e8u);/* delay 002d66e4 */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));nocturneBattlePanelRendererCall(UINT32_C(0x002d8038),UINT32_C(0x002d66e0));
/* 002d66e8: bne v0,zero,0x002d7cb8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d66ec */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002d7cb8;}}
/* 002d66f0: lw a1,0x1e8(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d66f4: lhu v1,0xc(a1) */ set(3,half(ea(5,(int32_t)UINT32_C(0x0000000c))));
/* 002d66f8: andi v1,v1,0x1a */ set(3,cpu(3)&UINT32_C(0x0000001a));
L_002d66fc:;
/* 002d66fc: li v0,0xa */ set(2,sx(UINT32_C(0x0000000a)));
/* 002d6700: bne v1,v0,0x002d6730 */ {int taken=(cpu(3)!=cpu(2));/* delay 002d6704 */ set(19,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));if(taken){goto L_002d6730;}}
/* 002d6708: lw a2,0x1e8(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d670c: lh v0,0xe(a2) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(6,(int32_t)UINT32_C(0x0000000e))));
/* 002d6710: bltz v0,0x002d6730 */ {int taken=((int64_t)cpu(2)<0);/* delay 002d6714 */ set(4,cpu(6));if(taken){goto L_002d6730;}}
/* 002d6718: move a2,s6 */ set(6,cpu(22));
/* 002d671c: jal 0x002d6548 */ set(31,0x002d6724u);/* delay 002d6720 */ set(5,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d6548),UINT32_C(0x002d671c));
/* 002d6724: b 0x002d7cbc */ /* delay 002d6728 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000240)));goto L_002d7cbc;
L_002d6730:;
/* 002d6730: sw zero,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 002d6734: sw s3,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(19));
/* 002d6738: move s2,s0 */ set(18,cpu(16));
/* 002d673c: sw zero,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002d6740: sw zero,0x1ec(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000001ec)),(uint32_t)cpu(0));
/* 002d6744: nop  */ 
L_002d6748:;
/* 002d6748: move s5,s2 */ set(21,cpu(18));
/* 002d674c: li s1,0x25 */ set(17,sx(UINT32_C(0x00000025)));
L_002d6750:;
/* 002d6750: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d6754: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002d6758: lw a0,-0x41d8(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0xffffbe28)));
/* 002d675c: addiu a1,sp,0x1d4 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x000001d4)));
/* 002d6760: lw a3,-0x3d70(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0xffffc290)));
/* 002d6764: move a2,s2 */ set(6,cpu(18));
/* 002d6768: jal 0x002da4b8 */ set(31,0x002d6770u);/* delay 002d676c */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x000001d8)));nocturneBattlePanelRendererCall(UINT32_C(0x002da4b8),UINT32_C(0x002d6768));
/* 002d6770: move s0,v0 */ set(16,cpu(2));
/* 002d6774: blezl s0,0x002d6790 */ {int taken=((int64_t)cpu(16)<=0);if(taken){/* delay 002d6778 */ set(17,sx((uint32_t)cpu(18)-(uint32_t)cpu(21)));goto L_002d6790;}}
/* 002d677c: lw v0,0x1d4(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001d4)));
/* 002d6780: bne v0,s1,0x002d6750 */ {int taken=(cpu(2)!=cpu(17));/* delay 002d6784 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(16)));if(taken){goto L_002d6750;}}
/* 002d6788: addiu s2,s2,-0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));
/* 002d678c: subu s1,s2,s5 */ set(17,sx((uint32_t)cpu(18)-(uint32_t)cpu(21)));
L_002d6790:;
/* 002d6790: beq s1,zero,0x002d67ec */ {int taken=(cpu(17)==cpu(0));/* delay 002d6794 */ if(taken){goto L_002d67ec;}}
/* 002d6798: sw s1,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 002d679c: sw s5,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));
/* 002d67a0: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d67a4: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d67a8: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d67ac: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d67b0: addu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(17)));
/* 002d67b4: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d67b8: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d67bc: bne a0,zero,0x002d67e0 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d67c0 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d67e0;}}
/* 002d67c4: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d67c8: jal 0x002d6500 */ set(31,0x002d67d0u);/* delay 002d67cc */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d67c8));
/* 002d67d0: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d67d4 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d67d8: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d67dc: move s3,a0 */ set(19,cpu(4));
L_002d67e0:;
/* 002d67e0: lw a1,0x1ec(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x000001ec)));
/* 002d67e4: addu a1,a1,s1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(17)));
/* 002d67e8: sw a1,0x1ec(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000001ec)),(uint32_t)cpu(5));
L_002d67ec:;
/* 002d67ec: blez s0,0x002d7c84 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d67f0 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002d7c84;}}
/* 002d67f4: sb zero,0x1d1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x000001d1)),(uint8_t)cpu(0));
/* 002d67f8: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 002d67fc: sw zero,0x204(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000204)),(uint32_t)cpu(0));
/* 002d6800: move s7,zero */ set(23,cpu(0));
/* 002d6804: sw zero,0x1f0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000001f0)),(uint32_t)cpu(0));
/* 002d6808: li s4,-0x1 */ set(20,sx(UINT32_C(0xffffffff)));
L_002d680c:;
/* 002d680c: lbu a0,0x0(s2) */ set(4,byte(ea(18,(int32_t)UINT32_C(0x00000000))));
L_002d6810:;
/* 002d6810: sll v0,a0,0x18 */ set(2,sx((uint32_t)cpu(4)<<24));
/* 002d6814: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 002d6818: sra s1,v0,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(2)>>24)));
L_002d681c:;
/* 002d681c: addiu v1,s1,-0x20 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0xffffffe0)));
L_002d6820:;
/* 002d6820: sltiu v0,v1,0x59 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000059));
/* 002d6824: beq v0,zero,0x002d6ef0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6828 */ set(2,sx((uint32_t)cpu(3)<<2));if(taken){goto L_002d6ef0;}}
/* 002d682c: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002d6830: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002d6834: lw v1,-0x48f0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffb710)));
/* 002d6838: jr v1 */ {uint64_t target=cpu(3);/* delay 002d683c */ switch((uint32_t)target){case 0x002d6840u:goto L_002d6840;case 0x002d6858u:goto L_002d6858;case 0x002d6860u:goto L_002d6860;case 0x002d687cu:goto L_002d687c;case 0x002d6888u:goto L_002d6888;case 0x002d6898u:goto L_002d6898;case 0x002d6918u:goto L_002d6918;case 0x002d6920u:goto L_002d6920;case 0x002d6958u:goto L_002d6958;case 0x002d6960u:goto L_002d6960;case 0x002d6968u:goto L_002d6968;case 0x002d697cu:goto L_002d697c;case 0x002d6990u:goto L_002d6990;case 0x002d69b0u:goto L_002d69b0;case 0x002d69b4u:goto L_002d69b4;case 0x002d6a08u:goto L_002d6a08;case 0x002d6be8u:goto L_002d6be8;case 0x002d6c48u:goto L_002d6c48;case 0x002d6c4cu:goto L_002d6c4c;case 0x002d6c90u:goto L_002d6c90;case 0x002d6cb8u:goto L_002d6cb8;case 0x002d6d18u:goto L_002d6d18;case 0x002d6d1cu:goto L_002d6d1c;case 0x002d6d60u:goto L_002d6d60;case 0x002d6d70u:goto L_002d6d70;case 0x002d6ef0u:goto L_002d6ef0;default:fprintf(stderr,"Unsupported original printf format PC %08x\n",(uint32_t)target);abort();}}
L_002d6840:;
/* 002d6840: lb v0,0x1d1(sp) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(29,(int32_t)UINT32_C(0x000001d1))));
/* 002d6844: bnel v0,zero,0x002d6810 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d6848 */ set(4,byte(ea(18,(int32_t)UINT32_C(0x00000000))));goto L_002d6810;}}
/* 002d684c: b 0x002d688c */ /* delay 002d6850 */ set(2,sx(UINT32_C(0x00000020)));goto L_002d688c;
L_002d6858:;
/* 002d6858: b 0x002d680c */ /* delay 002d685c */ set(23,cpu(23)|UINT32_C(0x00000001));goto L_002d680c;
L_002d6860:;
/* 002d6860: move v0,s6 */ set(2,cpu(22));
/* 002d6864: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6868: lw v0,0x0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002d686c: bgez v0,0x002d680c */ {int taken=((int64_t)cpu(2)>=0);/* delay 002d6870 */ sw(ea(29,(int32_t)UINT32_C(0x000001f0)),(uint32_t)cpu(2));if(taken){goto L_002d680c;}}
/* 002d6874: subu v0,zero,v0 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));
/* 002d6878: sw v0,0x1f0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000001f0)),(uint32_t)cpu(2));
L_002d687c:;
/* 002d687c: b 0x002d680c */ /* delay 002d6880 */ set(23,cpu(23)|UINT32_C(0x00000004));goto L_002d680c;
L_002d6888:;
/* 002d6888: li v0,0x2b */ set(2,sx(UINT32_C(0x0000002b)));
L_002d688c:;
/* 002d688c: lbu a0,0x0(s2) */ set(4,byte(ea(18,(int32_t)UINT32_C(0x00000000))));
/* 002d6890: b 0x002d6810 */ /* delay 002d6894 */ sb(ea(29,(int32_t)UINT32_C(0x000001d1)),(uint8_t)cpu(2));goto L_002d6810;
L_002d6898:;
/* 002d6898: lb s1,0x0(s2) */ set(17,(uint64_t)(int64_t)(int8_t)byte(ea(18,(int32_t)UINT32_C(0x00000000))));
/* 002d689c: li v0,0x2a */ set(2,sx(UINT32_C(0x0000002a)));
/* 002d68a0: bne s1,v0,0x002d68c8 */ {int taken=(cpu(17)!=cpu(2));/* delay 002d68a4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));if(taken){goto L_002d68c8;}}
/* 002d68a8: move v0,s6 */ set(2,cpu(22));
/* 002d68ac: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002d68b0: move s4,s0 */ set(20,cpu(16));
/* 002d68b4: slti v0,s4,-0x1 */ set(2,(int64_t)cpu(20)<(int64_t)(int32_t)UINT32_C(0xffffffff));
/* 002d68b8: beq v0,zero,0x002d680c */ {int taken=(cpu(2)==cpu(0));/* delay 002d68bc */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));if(taken){goto L_002d680c;}}
/* 002d68c0: b 0x002d680c */ /* delay 002d68c4 */ set(20,sx(UINT32_C(0xffffffff)));goto L_002d680c;
L_002d68c8:;
/* 002d68c8: addiu v0,s1,-0x30 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0xffffffd0)));
/* 002d68cc: sltiu v0,v0,0xa */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 002d68d0: beq v0,zero,0x002d6900 */ {int taken=(cpu(2)==cpu(0));/* delay 002d68d4 */ set(16,cpu(0));if(taken){goto L_002d6900;}}
L_002d68d8:;
/* 002d68d8: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002d68dc: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d68e0: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 002d68e4: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 002d68e8: lb s1,0x0(s2) */ set(17,(uint64_t)(int64_t)(int8_t)byte(ea(18,(int32_t)UINT32_C(0x00000000))));
/* 002d68ec: addiu s0,v0,-0x30 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffd0)));
/* 002d68f0: addiu v0,s1,-0x30 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0xffffffd0)));
/* 002d68f4: sltiu v0,v0,0xa */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 002d68f8: bne v0,zero,0x002d68d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d68fc */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));if(taken){goto L_002d68d8;}}
L_002d6900:;
/* 002d6900: move s4,s0 */ set(20,cpu(16));
/* 002d6904: slti v0,s4,-0x1 */ set(2,(int64_t)cpu(20)<(int64_t)(int32_t)UINT32_C(0xffffffff));
/* 002d6908: bnel v0,zero,0x002d681c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d690c */ set(20,sx(UINT32_C(0xffffffff)));goto L_002d681c;}}
/* 002d6910: b 0x002d6820 */ /* delay 002d6914 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0xffffffe0)));goto L_002d6820;
L_002d6918:;
/* 002d6918: b 0x002d680c */ /* delay 002d691c */ set(23,cpu(23)|UINT32_C(0x00000080));goto L_002d680c;
L_002d6920:;
/* 002d6920: move s0,zero */ set(16,cpu(0));
/* 002d6924: nop  */ 
L_002d6928:;
/* 002d6928: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002d692c: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d6930: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 002d6934: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 002d6938: lb s1,0x0(s2) */ set(17,(uint64_t)(int64_t)(int8_t)byte(ea(18,(int32_t)UINT32_C(0x00000000))));
/* 002d693c: addiu s0,v0,-0x30 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffd0)));
/* 002d6940: addiu v0,s1,-0x30 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0xffffffd0)));
/* 002d6944: sltiu v0,v0,0xa */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 002d6948: bne v0,zero,0x002d6928 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d694c */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));if(taken){goto L_002d6928;}}
/* 002d6950: b 0x002d681c */ /* delay 002d6954 */ sw(ea(29,(int32_t)UINT32_C(0x000001f0)),(uint32_t)cpu(16));goto L_002d681c;
L_002d6958:;
/* 002d6958: b 0x002d680c */ /* delay 002d695c */ set(23,cpu(23)|UINT32_C(0x00000008));goto L_002d680c;
L_002d6960:;
/* 002d6960: b 0x002d680c */ /* delay 002d6964 */ set(23,cpu(23)|UINT32_C(0x00000040));goto L_002d680c;
L_002d6968:;
/* 002d6968: lb v1,0x0(s2) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(18,(int32_t)UINT32_C(0x00000000))));
/* 002d696c: li v0,0x6c */ set(2,sx(UINT32_C(0x0000006c)));
/* 002d6970: bne v1,v0,0x002d6988 */ {int taken=(cpu(3)!=cpu(2));/* delay 002d6974 */ set(4,byte(ea(18,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_002d6988;}}
/* 002d6978: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
L_002d697c:;
/* 002d697c: b 0x002d680c */ /* delay 002d6980 */ set(23,cpu(23)|UINT32_C(0x00000020));goto L_002d680c;
L_002d6988:;
/* 002d6988: b 0x002d6810 */ /* delay 002d698c */ set(23,cpu(23)|UINT32_C(0x00000010));goto L_002d6810;
L_002d6990:;
/* 002d6990: move v0,s6 */ set(2,cpu(22));
/* 002d6994: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6998: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002d699c: addiu s5,sp,0x60 */ set(21,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 002d69a0: li s8,0x1 */ set(30,sx(UINT32_C(0x00000001)));
/* 002d69a4: b 0x002d6f00 */ /* delay 002d69a8 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));goto L_002d6f00;
L_002d69b0:;
/* 002d69b0: ori s7,s7,0x10 */ set(23,cpu(23)|UINT32_C(0x00000010));
L_002d69b4:;
/* 002d69b4: andi v0,s7,0x10 */ set(2,cpu(23)&UINT32_C(0x00000010));
/* 002d69b8: beq v0,zero,0x002d69d0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d69bc */ set(2,cpu(22));if(taken){goto L_002d69d0;}}
/* 002d69c0: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d69c4: b 0x002d69f0 */ /* delay 002d69c8 */ restore(16,ea(2,(int32_t)UINT32_C(0x00000000)));goto L_002d69f0;
L_002d69d0:;
/* 002d69d0: andi v0,s7,0x40 */ set(2,cpu(23)&UINT32_C(0x00000040));
/* 002d69d4: beq v0,zero,0x002d69e8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d69d8 */ set(2,cpu(22));if(taken){goto L_002d69e8;}}
/* 002d69dc: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d69e0: b 0x002d69f0 */ /* delay 002d69e4 */ set(16,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000000))));goto L_002d69f0;
L_002d69e8:;
/* 002d69e8: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d69ec: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
L_002d69f0:;
/* 002d69f0: bgez s0,0x002d6dd0 */ {int taken=((int64_t)cpu(16)>=0);/* delay 002d69f4 */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_002d6dd0;}}
/* 002d69f8: li v0,0x2d */ set(2,sx(UINT32_C(0x0000002d)));
/* 002d69fc: dsubu s0,zero,s0 */ set(16,cpu(0)-cpu(16));
/* 002d6a00: b 0x002d6dd0 */ /* delay 002d6a04 */ sb(ea(29,(int32_t)UINT32_C(0x000001d1)),(uint8_t)cpu(2));goto L_002d6dd0;
L_002d6a08:;
/* 002d6a08: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d6a0c: bne s4,v0,0x002d6a20 */ {int taken=(cpu(20)!=cpu(2));/* delay 002d6a10 */ set(2,sx(UINT32_C(0x00000067)));if(taken){goto L_002d6a20;}}
/* 002d6a14: b 0x002d6a38 */ /* delay 002d6a18 */ set(20,sx(UINT32_C(0x00000006)));goto L_002d6a38;
L_002d6a20:;
/* 002d6a20: beq s1,v0,0x002d6a30 */ {int taken=(cpu(17)==cpu(2));/* delay 002d6a24 */ set(2,sx(UINT32_C(0x00000047)));if(taken){goto L_002d6a30;}}
/* 002d6a28: bne s1,v0,0x002d6a3c */ {int taken=(cpu(17)!=cpu(2));/* delay 002d6a2c */ set(2,cpu(23)&UINT32_C(0x00000008));if(taken){goto L_002d6a3c;}}
L_002d6a30:;
/* 002d6a30: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d6a34: movz s4,v0,s4 */ if(cpu(20)==0){set(20,cpu(2));}
L_002d6a38:;
/* 002d6a38: andi v0,s7,0x8 */ set(2,cpu(23)&UINT32_C(0x00000008));
L_002d6a3c:;
/* 002d6a3c: move v0,s6 */ set(2,cpu(22));
/* 002d6a40: ld v0,0x0(v0) */ restore(2,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002d6a44: sd v0,0x1f8(sp) */ save(2,ea(29,(int32_t)UINT32_C(0x000001f8)));
/* 002d6a48: ld a0,0x1f8(sp) */ restore(4,ea(29,(int32_t)UINT32_C(0x000001f8)));
/* 002d6a4c: jal 0x002db5e8 */ set(31,0x002d6a54u);/* delay 002d6a50 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));nocturneBattlePanelRendererCall(UINT32_C(0x002db5e8),UINT32_C(0x002d6a4c));
/* 002d6a54: beq v0,zero,0x002d6a90 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6a58 */ if(taken){goto L_002d6a90;}}
/* 002d6a5c: ld a0,0x1f8(sp) */ restore(4,ea(29,(int32_t)UINT32_C(0x000001f8)));
/* 002d6a60: move a1,zero */ set(5,cpu(0));
/* 002d6a64: jal 0x002d1b38 */ set(31,0x002d6a6cu);/* delay 002d6a68 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d6a64));
/* 002d6a6c: bgez v0,0x002d6a80 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002d6a70 */ set(2,sx(UINT32_C(0x00550000)));if(taken){goto L_002d6a80;}}
/* 002d6a74: li v0,0x2d */ set(2,sx(UINT32_C(0x0000002d)));
/* 002d6a78: sb v0,0x1d1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x000001d1)),(uint8_t)cpu(2));
/* 002d6a7c: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
L_002d6a80:;
/* 002d6a80: li s8,0x3 */ set(30,sx(UINT32_C(0x00000003)));
/* 002d6a84: b 0x002d6f04 */ /* delay 002d6a88 */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0xffffb690)));goto L_002d6f04;
L_002d6a90:;
/* 002d6a90: ld a0,0x1f8(sp) */ restore(4,ea(29,(int32_t)UINT32_C(0x000001f8)));
/* 002d6a94: jal 0x002db630 */ set(31,0x002d6a9cu);/* delay 002d6a98 */ nocturneBattlePanelRendererCall(UINT32_C(0x002db630),UINT32_C(0x002d6a94));
/* 002d6a9c: beq v0,zero,0x002d6ab0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6aa0 */ set(2,sx(UINT32_C(0x00550000)));if(taken){goto L_002d6ab0;}}
/* 002d6aa4: li s8,0x3 */ set(30,sx(UINT32_C(0x00000003)));
/* 002d6aa8: b 0x002d6f04 */ /* delay 002d6aac */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0xffffb698)));goto L_002d6f04;
L_002d6ab0:;
/* 002d6ab0: ori s7,s7,0x100 */ set(23,cpu(23)|UINT32_C(0x00000100));
/* 002d6ab4: lw a0,0x1e4(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e4)));
/* 002d6ab8: ld a1,0x1f8(sp) */ restore(5,ea(29,(int32_t)UINT32_C(0x000001f8)));
/* 002d6abc: move a2,s4 */ set(6,cpu(20));
/* 002d6ac0: move a3,s7 */ set(7,cpu(23));
/* 002d6ac4: addiu t0,sp,0x1d0 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x000001d0)));
/* 002d6ac8: addiu t1,sp,0x1dc */ set(9,sx((uint32_t)cpu(29)+UINT32_C(0x000001dc)));
/* 002d6acc: move t2,s1 */ set(10,cpu(17));
/* 002d6ad0: jal 0x002d7ce8 */ set(31,0x002d6ad8u);/* delay 002d6ad4 */ set(11,sx((uint32_t)cpu(29)+UINT32_C(0x000001e0)));nocturneBattlePanelRendererCall(UINT32_C(0x002d7ce8),UINT32_C(0x002d6ad0));
/* 002d6ad8: move s5,v0 */ set(21,cpu(2));
/* 002d6adc: li v0,0x67 */ set(2,sx(UINT32_C(0x00000067)));
/* 002d6ae0: beq s1,v0,0x002d6af0 */ {int taken=(cpu(17)==cpu(2));/* delay 002d6ae4 */ set(2,sx(UINT32_C(0x00000047)));if(taken){goto L_002d6af0;}}
/* 002d6ae8: bne s1,v0,0x002d6b20 */ {int taken=(cpu(17)!=cpu(2));/* delay 002d6aec */ lw(7,ea(29,(int32_t)UINT32_C(0x000001dc)));if(taken){goto L_002d6b20;}}
L_002d6af0:;
/* 002d6af0: lw a3,0x1dc(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d6af4: slti v0,a3,-0x3 */ set(2,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0xfffffffd));
/* 002d6af8: bne v0,zero,0x002d6b10 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d6afc */ set(2,sx(UINT32_C(0x00000065)));if(taken){goto L_002d6b10;}}
/* 002d6b00: slt v0,s4,a3 */ set(2,(int64_t)cpu(20)<(int64_t)cpu(7));
/* 002d6b04: beql v0,zero,0x002d6b20 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d6b08 */ set(17,sx(UINT32_C(0x00000067)));goto L_002d6b20;}}
/* 002d6b0c: li v0,0x65 */ set(2,sx(UINT32_C(0x00000065)));
L_002d6b10:;
/* 002d6b10: xori a0,s1,0x67 */ set(4,cpu(17)^UINT32_C(0x00000067));
/* 002d6b14: li v1,0x45 */ set(3,sx(UINT32_C(0x00000045)));
/* 002d6b18: move s1,v0 */ set(17,cpu(2));
/* 002d6b1c: movn s1,v1,a0 */ if(cpu(4)!=0){set(17,cpu(3));}
L_002d6b20:;
/* 002d6b20: slti v0,s1,0x66 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000066));
/* 002d6b24: beql v0,zero,0x002d6b70 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d6b28 */ set(2,sx(UINT32_C(0x00000066)));goto L_002d6b70;}}
/* 002d6b2c: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002d6b30: move a2,s1 */ set(6,cpu(17));
/* 002d6b34: move a0,sp */ set(4,cpu(29));
/* 002d6b38: move a1,a3 */ set(5,cpu(7));
/* 002d6b3c: jal 0x002d7ea8 */ set(31,0x002d6b44u);/* delay 002d6b40 */ sw(ea(29,(int32_t)UINT32_C(0x000001dc)),(uint32_t)cpu(7));nocturneBattlePanelRendererCall(UINT32_C(0x002d7ea8),UINT32_C(0x002d6b3c));
/* 002d6b44: sw v0,0x200(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000200)),(uint32_t)cpu(2));
/* 002d6b48: lw v0,0x1e0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d6b4c: lw a2,0x200(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000200)));
/* 002d6b50: slti v1,v0,0x2 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d6b54: beq v1,zero,0x002d6b68 */ {int taken=(cpu(3)==cpu(0));/* delay 002d6b58 */ set(30,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));if(taken){goto L_002d6b68;}}
/* 002d6b5c: andi v0,s7,0x1 */ set(2,cpu(23)&UINT32_C(0x00000001));
/* 002d6b60: beq v0,zero,0x002d6bd4 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6b64 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(29,(int32_t)UINT32_C(0x000001d0))));if(taken){goto L_002d6bd4;}}
L_002d6b68:;
/* 002d6b68: b 0x002d6bd0 */ /* delay 002d6b6c */ set(30,sx((uint32_t)cpu(30)+UINT32_C(0x00000001)));goto L_002d6bd0;
L_002d6b70:;
/* 002d6b70: bne s1,v0,0x002d6ba0 */ {int taken=(cpu(17)!=cpu(2));/* delay 002d6b74 */ lw(5,ea(29,(int32_t)UINT32_C(0x000001e0)));if(taken){goto L_002d6ba0;}}
/* 002d6b78: blez a3,0x002d6bd0 */ {int taken=((int64_t)cpu(7)<=0);/* delay 002d6b7c */ set(30,sx((uint32_t)cpu(20)+UINT32_C(0x00000002)));if(taken){goto L_002d6bd0;}}
/* 002d6b80: bne s4,zero,0x002d6b94 */ {int taken=(cpu(20)!=cpu(0));/* delay 002d6b84 */ set(30,cpu(7));if(taken){goto L_002d6b94;}}
/* 002d6b88: andi v0,s7,0x1 */ set(2,cpu(23)&UINT32_C(0x00000001));
/* 002d6b8c: beq v0,zero,0x002d6bd4 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6b90 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(29,(int32_t)UINT32_C(0x000001d0))));if(taken){goto L_002d6bd4;}}
L_002d6b94:;
/* 002d6b94: addu v0,a3,s4 */ set(2,sx((uint32_t)cpu(7)+(uint32_t)cpu(20)));
/* 002d6b98: b 0x002d6bd0 */ /* delay 002d6b9c */ set(30,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));goto L_002d6bd0;
L_002d6ba0:;
/* 002d6ba0: slt v0,a3,a1 */ set(2,(int64_t)cpu(7)<(int64_t)cpu(5));
/* 002d6ba4: bne v0,zero,0x002d6bc0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d6ba8 */ set(2,cpu(23)&UINT32_C(0x00000001));if(taken){goto L_002d6bc0;}}
/* 002d6bac: beq v0,zero,0x002d6bd0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6bb0 */ set(30,cpu(7));if(taken){goto L_002d6bd0;}}
/* 002d6bb4: b 0x002d6bd0 */ /* delay 002d6bb8 */ set(30,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));goto L_002d6bd0;
L_002d6bc0:;
/* 002d6bc0: bgtzl a3,0x002d6bd0 */ {int taken=((int64_t)cpu(7)>0);if(taken){/* delay 002d6bc4 */ set(30,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));goto L_002d6bd0;}}
/* 002d6bc8: subu v0,a1,a3 */ set(2,sx((uint32_t)cpu(5)-(uint32_t)cpu(7)));
/* 002d6bcc: addiu s8,v0,0x2 */ set(30,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
L_002d6bd0:;
/* 002d6bd0: lb v0,0x1d0(sp) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(29,(int32_t)UINT32_C(0x000001d0))));
L_002d6bd4:;
/* 002d6bd4: beq v0,zero,0x002d6f04 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6bd8 */ set(2,sx(UINT32_C(0x0000002d)));if(taken){goto L_002d6f04;}}
/* 002d6bdc: b 0x002d6f04 */ /* delay 002d6be0 */ sb(ea(29,(int32_t)UINT32_C(0x000001d1)),(uint8_t)cpu(2));goto L_002d6f04;
L_002d6be8:;
/* 002d6be8: andi v0,s7,0x10 */ set(2,cpu(23)&UINT32_C(0x00000010));
/* 002d6bec: beq v0,zero,0x002d6c10 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6bf0 */ set(2,cpu(23)&UINT32_C(0x00000040));if(taken){goto L_002d6c10;}}
/* 002d6bf4: move v1,s6 */ set(3,cpu(22));
/* 002d6bf8: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6bfc: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002d6c00: lw v1,0x1ec(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000001ec)));
/* 002d6c04: b 0x002d6748 */ /* delay 002d6c08 */ save(3,ea(2,(int32_t)UINT32_C(0x00000000)));goto L_002d6748;
L_002d6c10:;
/* 002d6c10: beq v0,zero,0x002d6c30 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6c14 */ set(3,cpu(22));if(taken){goto L_002d6c30;}}
/* 002d6c18: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6c1c: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002d6c20: lw a0,0x1ec(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001ec)));
/* 002d6c24: b 0x002d6748 */ /* delay 002d6c28 */ sh(ea(2,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));goto L_002d6748;
L_002d6c30:;
/* 002d6c30: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6c34: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002d6c38: lw a1,0x1ec(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x000001ec)));
/* 002d6c3c: b 0x002d6748 */ /* delay 002d6c40 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));goto L_002d6748;
L_002d6c48:;
/* 002d6c48: ori s7,s7,0x10 */ set(23,cpu(23)|UINT32_C(0x00000010));
L_002d6c4c:;
/* 002d6c4c: andi v0,s7,0x10 */ set(2,cpu(23)&UINT32_C(0x00000010));
/* 002d6c50: beq v0,zero,0x002d6c68 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6c54 */ set(2,cpu(22));if(taken){goto L_002d6c68;}}
/* 002d6c58: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6c5c: b 0x002d6c88 */ /* delay 002d6c60 */ restore(16,ea(2,(int32_t)UINT32_C(0x00000000)));goto L_002d6c88;
L_002d6c68:;
/* 002d6c68: andi v0,s7,0x40 */ set(2,cpu(23)&UINT32_C(0x00000040));
/* 002d6c6c: beq v0,zero,0x002d6c80 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6c70 */ set(2,cpu(22));if(taken){goto L_002d6c80;}}
/* 002d6c74: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6c78: b 0x002d6c88 */ /* delay 002d6c7c */ set(16,half(ea(2,(int32_t)UINT32_C(0x00000000))));goto L_002d6c88;
L_002d6c80:;
/* 002d6c80: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6c84: lwu s0,0x0(v0) */ set(16,word(ea(2,(int32_t)UINT32_C(0x00000000))));
L_002d6c88:;
/* 002d6c88: b 0x002d6dcc */ /* delay 002d6c8c */ set(3,cpu(0));goto L_002d6dcc;
L_002d6c90:;
/* 002d6c90: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d6c94: move v1,s6 */ set(3,cpu(22));
/* 002d6c98: addiu v0,v0,-0x4960 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb6a0)));
/* 002d6c9c: lw s0,0x0(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002d6ca0: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6ca4: ori s7,s7,0x2 */ set(23,cpu(23)|UINT32_C(0x00000002));
/* 002d6ca8: sw v0,0x20c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000020c)),(uint32_t)cpu(2));
/* 002d6cac: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
/* 002d6cb0: b 0x002d6dcc */ /* delay 002d6cb4 */ set(17,sx(UINT32_C(0x00000078)));goto L_002d6dcc;
L_002d6cb8:;
/* 002d6cb8: move v0,s6 */ set(2,cpu(22));
/* 002d6cbc: lw s5,0x0(v0) */ lw(21,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002d6cc0: bne s5,zero,0x002d6cd0 */ {int taken=(cpu(21)!=cpu(0));/* delay 002d6cc4 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));if(taken){goto L_002d6cd0;}}
/* 002d6cc8: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d6ccc: addiu s5,v0,-0x4948 */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0xffffb6b8)));
L_002d6cd0:;
/* 002d6cd0: bltz s4,0x002d6d08 */ {int taken=((int64_t)cpu(20)<0);/* delay 002d6cd4 */ set(5,cpu(0));if(taken){goto L_002d6d08;}}
/* 002d6cd8: move a0,s5 */ set(4,cpu(21));
/* 002d6cdc: jal 0x002da4ec */ set(31,0x002d6ce4u);/* delay 002d6ce0 */ set(6,cpu(20));nocturneBattlePanelRendererCall(UINT32_C(0x002da4ec),UINT32_C(0x002d6cdc));
/* 002d6ce4: beq v0,zero,0x002d6f00 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6ce8 */ set(30,cpu(20));if(taken){goto L_002d6f00;}}
/* 002d6cec: subu s8,v0,s5 */ set(30,sx((uint32_t)cpu(2)-(uint32_t)cpu(21)));
/* 002d6cf0: slt v0,s4,s8 */ set(2,(int64_t)cpu(20)<(int64_t)cpu(30));
/* 002d6cf4: beql v0,zero,0x002d6f04 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d6cf8 */ sb(ea(29,(int32_t)UINT32_C(0x000001d1)),(uint8_t)cpu(0));goto L_002d6f04;}}
/* 002d6cfc: b 0x002d6f00 */ /* delay 002d6d00 */ set(30,cpu(20));goto L_002d6f00;
L_002d6d08:;
/* 002d6d08: jal 0x002d5d0c */ set(31,0x002d6d10u);/* delay 002d6d0c */ set(4,cpu(21));nocturneBattlePanelRendererCall(UINT32_C(0x002d5d0c),UINT32_C(0x002d6d08));
/* 002d6d10: b 0x002d6f00 */ /* delay 002d6d14 */ set(30,cpu(2));goto L_002d6f00;
L_002d6d18:;
/* 002d6d18: ori s7,s7,0x10 */ set(23,cpu(23)|UINT32_C(0x00000010));
L_002d6d1c:;
/* 002d6d1c: andi v0,s7,0x10 */ set(2,cpu(23)&UINT32_C(0x00000010));
/* 002d6d20: beq v0,zero,0x002d6d38 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6d24 */ set(2,cpu(22));if(taken){goto L_002d6d38;}}
/* 002d6d28: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6d2c: b 0x002d6d58 */ /* delay 002d6d30 */ restore(16,ea(2,(int32_t)UINT32_C(0x00000000)));goto L_002d6d58;
L_002d6d38:;
/* 002d6d38: andi v0,s7,0x40 */ set(2,cpu(23)&UINT32_C(0x00000040));
/* 002d6d3c: beq v0,zero,0x002d6d50 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6d40 */ set(2,cpu(22));if(taken){goto L_002d6d50;}}
/* 002d6d44: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6d48: b 0x002d6d58 */ /* delay 002d6d4c */ set(16,half(ea(2,(int32_t)UINT32_C(0x00000000))));goto L_002d6d58;
L_002d6d50:;
/* 002d6d50: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6d54: lwu s0,0x0(v0) */ set(16,word(ea(2,(int32_t)UINT32_C(0x00000000))));
L_002d6d58:;
/* 002d6d58: b 0x002d6dcc */ /* delay 002d6d5c */ set(3,sx(UINT32_C(0x00000001)));goto L_002d6dcc;
L_002d6d60:;
/* 002d6d60: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d6d64: b 0x002d6d78 */ /* delay 002d6d68 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb6c0)));goto L_002d6d78;
L_002d6d70:;
/* 002d6d70: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d6d74: addiu v0,v0,-0x4960 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb6a0)));
L_002d6d78:;
/* 002d6d78: sw v0,0x20c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000020c)),(uint32_t)cpu(2));
/* 002d6d7c: andi v0,s7,0x10 */ set(2,cpu(23)&UINT32_C(0x00000010));
/* 002d6d80: beq v0,zero,0x002d6d98 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6d84 */ set(2,cpu(22));if(taken){goto L_002d6d98;}}
/* 002d6d88: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6d8c: b 0x002d6db8 */ /* delay 002d6d90 */ restore(16,ea(2,(int32_t)UINT32_C(0x00000000)));goto L_002d6db8;
L_002d6d98:;
/* 002d6d98: andi v0,s7,0x40 */ set(2,cpu(23)&UINT32_C(0x00000040));
/* 002d6d9c: beq v0,zero,0x002d6db0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6da0 */ set(2,cpu(22));if(taken){goto L_002d6db0;}}
/* 002d6da4: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6da8: b 0x002d6db8 */ /* delay 002d6dac */ set(16,half(ea(2,(int32_t)UINT32_C(0x00000000))));goto L_002d6db8;
L_002d6db0:;
/* 002d6db0: addiu s6,s6,0x8 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000008)));
/* 002d6db4: lwu s0,0x0(v0) */ set(16,word(ea(2,(int32_t)UINT32_C(0x00000000))));
L_002d6db8:;
/* 002d6db8: andi v0,s7,0x1 */ set(2,cpu(23)&UINT32_C(0x00000001));
/* 002d6dbc: beq v0,zero,0x002d6dcc */ {int taken=(cpu(2)==cpu(0));/* delay 002d6dc0 */ set(3,sx(UINT32_C(0x00000002)));if(taken){goto L_002d6dcc;}}
/* 002d6dc4: ori v0,s7,0x2 */ set(2,cpu(23)|UINT32_C(0x00000002));
/* 002d6dc8: movn s7,v0,s0 */ if(cpu(16)!=0){set(23,cpu(2));}
L_002d6dcc:;
/* 002d6dcc: sb zero,0x1d1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x000001d1)),(uint8_t)cpu(0));
L_002d6dd0:;
/* 002d6dd0: bltz s4,0x002d6de0 */ {int taken=((int64_t)cpu(20)<0);/* delay 002d6dd4 */ sw(ea(29,(int32_t)UINT32_C(0x00000204)),(uint32_t)cpu(20));if(taken){goto L_002d6de0;}}
/* 002d6dd8: li v0,-0x81 */ set(2,sx(UINT32_C(0xffffff7f)));
/* 002d6ddc: and s7,s7,v0 */ set(23,cpu(23)&cpu(2));
L_002d6de0:;
/* 002d6de0: bne s0,zero,0x002d6df4 */ {int taken=(cpu(16)!=cpu(0));/* delay 002d6de4 */ set(21,sx((uint32_t)cpu(29)+UINT32_C(0x000001bc)));if(taken){goto L_002d6df4;}}
/* 002d6de8: lw a2,0x204(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000204)));
/* 002d6dec: beq a2,zero,0x002d6ee4 */ {int taken=(cpu(6)==cpu(0));/* delay 002d6df0 */ set(2,sx((uint32_t)cpu(29)-(uint32_t)cpu(21)));if(taken){goto L_002d6ee4;}}
L_002d6df4:;
/* 002d6df4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d6df8: beq v1,v0,0x002d6e94 */ {int taken=(cpu(3)==cpu(2));/* delay 002d6dfc */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));if(taken){goto L_002d6e94;}}
/* 002d6e00: beq v1,zero,0x002d6e28 */ {int taken=(cpu(3)==cpu(0));/* delay 002d6e04 */ set(4,sx(UINT32_C(0x00000007)));if(taken){goto L_002d6e28;}}
/* 002d6e08: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002d6e0c: beq v1,v0,0x002d6eb0 */ {int taken=(cpu(3)==cpu(2));/* delay 002d6e10 */ set(2,sx(UINT32_C(0x00550000)));if(taken){goto L_002d6eb0;}}
/* 002d6e14: addiu s5,v0,-0x4928 */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0xffffb6d8)));
/* 002d6e18: jal 0x002d5d0c */ set(31,0x002d6e20u);/* delay 002d6e1c */ set(4,cpu(21));nocturneBattlePanelRendererCall(UINT32_C(0x002d5d0c),UINT32_C(0x002d6e18));
/* 002d6e20: b 0x002d6f04 */ /* delay 002d6e24 */ set(30,cpu(2));goto L_002d6f04;
L_002d6e28:;
/* 002d6e28: and v0,s0,a0 */ set(2,cpu(16)&cpu(4));
/* 002d6e2c: dsrl s0,s0,0x3 */ set(16,cpu(16)>>3);
/* 002d6e30: daddiu v0,v0,0x30 */ set(2,cpu(2)+(uint64_t)(int64_t)(int16_t)UINT32_C(0x00000030));
/* 002d6e34: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
/* 002d6e38: andi v1,v0,0xff */ set(3,cpu(2)&UINT32_C(0x000000ff));
/* 002d6e3c: bne s0,zero,0x002d6e28 */ {int taken=(cpu(16)!=cpu(0));/* delay 002d6e40 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));if(taken){goto L_002d6e28;}}
/* 002d6e44: andi v0,s7,0x1 */ set(2,cpu(23)&UINT32_C(0x00000001));
/* 002d6e48: beq v0,zero,0x002d6ee0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6e4c */ set(2,sx(UINT32_C(0x00000030)));if(taken){goto L_002d6ee0;}}
/* 002d6e50: beql v1,v0,0x002d6ee4 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 002d6e54 */ set(2,sx((uint32_t)cpu(29)-(uint32_t)cpu(21)));goto L_002d6ee4;}}
/* 002d6e58: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
/* 002d6e5c: b 0x002d6ee0 */ /* delay 002d6e60 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002d6ee0;
L_002d6e68:;
/* 002d6e68: jal 0x002e65c8 */ set(31,0x002d6e70u);/* delay 002d6e6c */ set(5,sx(UINT32_C(0x0000000a)));nocturneBattlePanelRendererCall(UINT32_C(0x002e65c8),UINT32_C(0x002d6e68));
/* 002d6e70: move a0,s0 */ set(4,cpu(16));
/* 002d6e74: daddiu v0,v0,0x30 */ set(2,cpu(2)+(uint64_t)(int64_t)(int16_t)UINT32_C(0x00000030));
/* 002d6e78: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
/* 002d6e7c: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 002d6e80: li a1,0xa */ set(5,sx(UINT32_C(0x0000000a)));
/* 002d6e84: jal 0x002e6048 */ set(31,0x002d6e8cu);/* delay 002d6e88 */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));nocturneBattlePanelRendererCall(UINT32_C(0x002e6048),UINT32_C(0x002d6e84));
/* 002d6e8c: move s0,v0 */ set(16,cpu(2));
/* 002d6e90: sltiu v0,s0,0xa */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
L_002d6e94:;
/* 002d6e94: beq v0,zero,0x002d6e68 */ {int taken=(cpu(2)==cpu(0));/* delay 002d6e98 */ set(4,cpu(16));if(taken){goto L_002d6e68;}}
/* 002d6e9c: daddiu v0,s0,0x30 */ set(2,cpu(16)+(uint64_t)(int64_t)(int16_t)UINT32_C(0x00000030));
/* 002d6ea0: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
/* 002d6ea4: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 002d6ea8: b 0x002d6ee0 */ /* delay 002d6eac */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));goto L_002d6ee0;
L_002d6eb0:;
/* 002d6eb0: li a0,0xf */ set(4,sx(UINT32_C(0x0000000f)));
/* 002d6eb4: nop  */ 
L_002d6eb8:;
/* 002d6eb8: lw v1,0x20c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000020c)));
/* 002d6ebc: and v0,s0,a0 */ set(2,cpu(16)&cpu(4));
/* 002d6ec0: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d6ec4: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d6ec8: addiu s5,s5,-0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0xffffffff)));
/* 002d6ecc: addu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002d6ed0: dsrl s0,s0,0x4 */ set(16,cpu(16)>>4);
/* 002d6ed4: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002d6ed8: bne s0,zero,0x002d6eb8 */ {int taken=(cpu(16)!=cpu(0));/* delay 002d6edc */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));if(taken){goto L_002d6eb8;}}
L_002d6ee0:;
/* 002d6ee0: subu v0,sp,s5 */ set(2,sx((uint32_t)cpu(29)-(uint32_t)cpu(21)));
L_002d6ee4:;
/* 002d6ee4: b 0x002d6f04 */ /* delay 002d6ee8 */ set(30,sx((uint32_t)cpu(2)+UINT32_C(0x000001bc)));goto L_002d6f04;
L_002d6ef0:;
/* 002d6ef0: beq s1,zero,0x002d7c80 */ {int taken=(cpu(17)==cpu(0));/* delay 002d6ef4 */ set(21,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));if(taken){goto L_002d7c80;}}
/* 002d6ef8: li s8,0x1 */ set(30,sx(UINT32_C(0x00000001)));
/* 002d6efc: sb s1,0x0(s5) */ sb(ea(21,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
L_002d6f00:;
/* 002d6f00: sb zero,0x1d1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x000001d1)),(uint8_t)cpu(0));
L_002d6f04:;
/* 002d6f04: lw a1,0x204(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000204)));
/* 002d6f08: move a0,s8 */ set(4,cpu(30));
/* 002d6f0c: move a2,s8 */ set(6,cpu(30));
/* 002d6f10: lb v1,0x1d1(sp) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(29,(int32_t)UINT32_C(0x000001d1))));
/* 002d6f14: slt v0,a0,a1 */ set(2,(int64_t)cpu(4)<(int64_t)cpu(5));
/* 002d6f18: lbu a0,0x1d1(sp) */ set(4,byte(ea(29,(int32_t)UINT32_C(0x000001d1))));
/* 002d6f1c: movz a1,a2,v0 */ if(cpu(2)==0){set(5,cpu(6));}
/* 002d6f20: sw s8,0x208(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000208)),(uint32_t)cpu(30));
/* 002d6f24: beq v1,zero,0x002d6f38 */ {int taken=(cpu(3)==cpu(0));/* delay 002d6f28 */ sw(ea(29,(int32_t)UINT32_C(0x00000208)),(uint32_t)cpu(5));if(taken){goto L_002d6f38;}}
/* 002d6f2c: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002d6f30: b 0x002d6f48 */ /* delay 002d6f34 */ sw(ea(29,(int32_t)UINT32_C(0x00000208)),(uint32_t)cpu(5));goto L_002d6f48;
L_002d6f38:;
/* 002d6f38: lw v1,0x208(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000208)));
/* 002d6f3c: andi v0,s7,0x2 */ set(2,cpu(23)&UINT32_C(0x00000002));
/* 002d6f40: addu v1,v0,v1 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002d6f44: sw v1,0x208(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000208)),(uint32_t)cpu(3));
L_002d6f48:;
/* 002d6f48: andi a1,s7,0x84 */ set(5,cpu(23)&UINT32_C(0x00000084));
/* 002d6f4c: bne a1,zero,0x002d7038 */ {int taken=(cpu(5)!=cpu(0));/* delay 002d6f50 */ sw(ea(29,(int32_t)UINT32_C(0x00000210)),(uint32_t)cpu(5));if(taken){goto L_002d7038;}}
/* 002d6f54: lw a2,0x1f0(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x000001f0)));
/* 002d6f58: lw v0,0x208(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000208)));
/* 002d6f5c: subu s0,a2,v0 */ set(16,sx((uint32_t)cpu(6)-(uint32_t)cpu(2)));
/* 002d6f60: blez s0,0x002d7038 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d6f64 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));if(taken){goto L_002d7038;}}
/* 002d6f68: bne v0,zero,0x002d6fe8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d6f6c */ set(7,sx(UINT32_C(0x00550000)));if(taken){goto L_002d6fe8;}}
/* 002d6f70: li a2,0x10 */ set(6,sx(UINT32_C(0x00000010)));
/* 002d6f74: addiu s4,a3,-0x4990 */ set(20,sx((uint32_t)cpu(7)+UINT32_C(0xffffb670)));
/* 002d6f78: sw a2,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));
/* 002d6f7c: nop  */ 
L_002d6f80:;
/* 002d6f80: sw s4,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));
/* 002d6f84: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d6f88: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d6f8c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d6f90: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d6f94: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002d6f98: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d6f9c: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d6fa0: bne a0,zero,0x002d6fd0 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d6fa4 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d6fd0;}}
/* 002d6fa8: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d6fac: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002d6fb0: sq a2,0x220(sp) */ sq(6,ea(29,(int32_t)UINT32_C(0x00000220)));
/* 002d6fb4: jal 0x002d6500 */ set(31,0x002d6fbcu);/* delay 002d6fb8 */ sq(7,ea(29,(int32_t)UINT32_C(0x00000230)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d6fb4));
/* 002d6fbc: lq a2,0x220(sp) */ pkLq(6,ea(29,(int32_t)UINT32_C(0x00000220)));
/* 002d6fc0: bne v0,zero,0x002d7ca0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d6fc4 */ pkLq(7,ea(29,(int32_t)UINT32_C(0x00000230)));if(taken){goto L_002d7ca0;}}
/* 002d6fc8: addiu v1,sp,0x20 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d6fcc: move s3,v1 */ set(19,cpu(3));
L_002d6fd0:;
/* 002d6fd0: addiu s0,s0,-0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 002d6fd4: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d6fd8: beql v0,zero,0x002d6f80 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d6fdc */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));goto L_002d6f80;}}
/* 002d6fe0: b 0x002d6fec */ /* delay 002d6fe4 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d6fec;
L_002d6fe8:;
/* 002d6fe8: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d6fec:;
/* 002d6fec: addiu v0,a3,-0x4990 */ set(2,sx((uint32_t)cpu(7)+UINT32_C(0xffffb670)));
/* 002d6ff0: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d6ff4: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d6ff8: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d6ffc: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7000: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7004: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d7008: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d700c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7010: bne a0,zero,0x002d7034 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7014 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d7034;}}
/* 002d7018: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d701c: jal 0x002d6500 */ set(31,0x002d7024u);/* delay 002d7020 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d701c));
/* 002d7024: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7028 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d702c: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7030: move s3,a0 */ set(19,cpu(4));
L_002d7034:;
/* 002d7034: lbu a0,0x1d1(sp) */ set(4,byte(ea(29,(int32_t)UINT32_C(0x000001d1))));
L_002d7038:;
/* 002d7038: beq a0,zero,0x002d7090 */ {int taken=(cpu(4)==cpu(0));/* delay 002d703c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002d7090;}}
/* 002d7040: addiu v1,sp,0x1d1 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x000001d1)));
/* 002d7044: sw v0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d7048: sw v1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002d704c: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7050: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7054: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7058: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d705c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7060: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7064: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7068: bne a0,zero,0x002d70f4 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d706c */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d70f4;}}
/* 002d7070: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7074: jal 0x002d6500 */ set(31,0x002d707cu);/* delay 002d7078 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7074));
/* 002d707c: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7080 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d7084: addiu a1,sp,0x20 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7088: b 0x002d70f4 */ /* delay 002d708c */ set(19,cpu(5));goto L_002d70f4;
L_002d7090:;
/* 002d7090: andi v0,s7,0x2 */ set(2,cpu(23)&UINT32_C(0x00000002));
/* 002d7094: beq v0,zero,0x002d70f4 */ {int taken=(cpu(2)==cpu(0));/* delay 002d7098 */ set(2,sx(UINT32_C(0x00000030)));if(taken){goto L_002d70f4;}}
/* 002d709c: li a0,0x2 */ set(4,sx(UINT32_C(0x00000002)));
/* 002d70a0: sb v0,0x1c0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x000001c0)),(uint8_t)cpu(2));
/* 002d70a4: addiu v1,sp,0x1c0 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x000001c0)));
/* 002d70a8: sb s1,0x1c1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x000001c1)),(uint8_t)cpu(17));
/* 002d70ac: sw a0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002d70b0: sw v1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002d70b4: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d70b8: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d70bc: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d70c0: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d70c4: addiu v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 002d70c8: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d70cc: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d70d0: bne a0,zero,0x002d70f4 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d70d4 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d70f4;}}
/* 002d70d8: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d70dc: jal 0x002d6500 */ set(31,0x002d70e4u);/* delay 002d70e0 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d70dc));
/* 002d70e4: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d70e8 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d70ec: addiu a2,sp,0x20 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d70f0: move s3,a2 */ set(19,cpu(6));
L_002d70f4:;
/* 002d70f4: lw v1,0x210(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000210)));
/* 002d70f8: li v0,0x80 */ set(2,sx(UINT32_C(0x00000080)));
/* 002d70fc: bne v1,v0,0x002d71e8 */ {int taken=(cpu(3)!=cpu(2));/* delay 002d7100 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000204)));if(taken){goto L_002d71e8;}}
/* 002d7104: lw a0,0x1f0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001f0)));
/* 002d7108: lw a1,0x208(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000208)));
/* 002d710c: subu s0,a0,a1 */ set(16,sx((uint32_t)cpu(4)-(uint32_t)cpu(5)));
/* 002d7110: blez s0,0x002d71e8 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d7114 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000204)));if(taken){goto L_002d71e8;}}
/* 002d7118: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d711c: bne v0,zero,0x002d7198 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7120 */ set(7,sx(UINT32_C(0x00550000)));if(taken){goto L_002d7198;}}
/* 002d7124: li a2,0x10 */ set(6,sx(UINT32_C(0x00000010)));
/* 002d7128: addiu s4,a3,-0x4980 */ set(20,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d712c: sw a2,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));
L_002d7130:;
/* 002d7130: sw s4,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));
/* 002d7134: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7138: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d713c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7140: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7144: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002d7148: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d714c: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7150: bne a0,zero,0x002d7180 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7154 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d7180;}}
/* 002d7158: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d715c: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002d7160: sq a2,0x220(sp) */ sq(6,ea(29,(int32_t)UINT32_C(0x00000220)));
/* 002d7164: jal 0x002d6500 */ set(31,0x002d716cu);/* delay 002d7168 */ sq(7,ea(29,(int32_t)UINT32_C(0x00000230)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7164));
/* 002d716c: lq a2,0x220(sp) */ pkLq(6,ea(29,(int32_t)UINT32_C(0x00000220)));
/* 002d7170: bne v0,zero,0x002d7ca0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7174 */ pkLq(7,ea(29,(int32_t)UINT32_C(0x00000230)));if(taken){goto L_002d7ca0;}}
/* 002d7178: addiu v0,sp,0x20 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d717c: move s3,v0 */ set(19,cpu(2));
L_002d7180:;
/* 002d7180: addiu s0,s0,-0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 002d7184: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d7188: beql v0,zero,0x002d7130 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d718c */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));goto L_002d7130;}}
/* 002d7190: b 0x002d719c */ /* delay 002d7194 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d719c;
L_002d7198:;
/* 002d7198: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d719c:;
/* 002d719c: addiu v0,a3,-0x4980 */ set(2,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d71a0: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d71a4: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d71a8: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d71ac: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d71b0: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d71b4: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d71b8: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d71bc: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d71c0: bne a0,zero,0x002d71e4 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d71c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d71e4;}}
/* 002d71c8: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d71cc: jal 0x002d6500 */ set(31,0x002d71d4u);/* delay 002d71d0 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d71cc));
/* 002d71d4: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d71d8 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d71dc: addiu v1,sp,0x20 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d71e0: move s3,v1 */ set(19,cpu(3));
L_002d71e4:;
/* 002d71e4: lw a0,0x204(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000204)));
L_002d71e8:;
/* 002d71e8: subu s0,a0,s8 */ set(16,sx((uint32_t)cpu(4)-(uint32_t)cpu(30)));
/* 002d71ec: blez s0,0x002d72c8 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d71f0 */ set(2,cpu(23)&UINT32_C(0x00000100));if(taken){goto L_002d72c8;}}
/* 002d71f4: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d71f8: bne v0,zero,0x002d7278 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d71fc */ set(7,sx(UINT32_C(0x00550000)));if(taken){goto L_002d7278;}}
/* 002d7200: li a2,0x10 */ set(6,sx(UINT32_C(0x00000010)));
/* 002d7204: addiu s4,a3,-0x4980 */ set(20,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d7208: sw a2,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));
/* 002d720c: nop  */ 
L_002d7210:;
/* 002d7210: sw s4,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(20));
/* 002d7214: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7218: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d721c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7220: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7224: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002d7228: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d722c: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7230: bne a0,zero,0x002d7260 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7234 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d7260;}}
/* 002d7238: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d723c: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002d7240: sq a2,0x220(sp) */ sq(6,ea(29,(int32_t)UINT32_C(0x00000220)));
/* 002d7244: jal 0x002d6500 */ set(31,0x002d724cu);/* delay 002d7248 */ sq(7,ea(29,(int32_t)UINT32_C(0x00000230)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7244));
/* 002d724c: lq a2,0x220(sp) */ pkLq(6,ea(29,(int32_t)UINT32_C(0x00000220)));
/* 002d7250: bne v0,zero,0x002d7ca0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7254 */ pkLq(7,ea(29,(int32_t)UINT32_C(0x00000230)));if(taken){goto L_002d7ca0;}}
/* 002d7258: addiu a1,sp,0x20 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d725c: move s3,a1 */ set(19,cpu(5));
L_002d7260:;
/* 002d7260: addiu s0,s0,-0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 002d7264: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d7268: beql v0,zero,0x002d7210 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d726c */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));goto L_002d7210;}}
/* 002d7270: b 0x002d727c */ /* delay 002d7274 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d727c;
L_002d7278:;
/* 002d7278: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d727c:;
/* 002d727c: addiu v0,a3,-0x4980 */ set(2,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d7280: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d7284: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7288: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d728c: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7290: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7294: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d7298: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d729c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d72a0: bne a0,zero,0x002d72c4 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d72a4 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d72c4;}}
/* 002d72a8: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d72ac: jal 0x002d6500 */ set(31,0x002d72b4u);/* delay 002d72b0 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d72ac));
/* 002d72b4: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d72b8 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d72bc: addiu a2,sp,0x20 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d72c0: move s3,a2 */ set(19,cpu(6));
L_002d72c4:;
/* 002d72c4: andi v0,s7,0x100 */ set(2,cpu(23)&UINT32_C(0x00000100));
L_002d72c8:;
/* 002d72c8: bnel v0,zero,0x002d72f0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d72cc */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000066));goto L_002d72f0;}}
/* 002d72d0: sw s8,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(30));
/* 002d72d4: sw s5,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));
/* 002d72d8: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d72dc: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d72e0: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d72e4: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d72e8: b 0x002d7b28 */ /* delay 002d72ec */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(30)));goto L_002d7b28;
L_002d72f0:;
/* 002d72f0: bne v0,zero,0x002d78f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d72f4 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));if(taken){goto L_002d78f8;}}
/* 002d72f8: ld a0,0x1f8(sp) */ restore(4,ea(29,(int32_t)UINT32_C(0x000001f8)));
/* 002d72fc: move a1,zero */ set(5,cpu(0));
/* 002d7300: jal 0x002d1b38 */ set(31,0x002d7308u);/* delay 002d7304 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d7300));
/* 002d7308: bne v0,zero,0x002d7488 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d730c */ lw(3,ea(29,(int32_t)UINT32_C(0x000001dc)));if(taken){goto L_002d7488;}}
/* 002d7310: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
/* 002d7314: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d7318: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002d731c: addiu v0,v0,-0x4908 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb6f8)));
/* 002d7320: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d7324: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7328: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d732c: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7330: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7334: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7338: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d733c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7340: bne a0,zero,0x002d7364 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7344 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d7364;}}
/* 002d7348: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d734c: jal 0x002d6500 */ set(31,0x002d7354u);/* delay 002d7350 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d734c));
/* 002d7354: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7358 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d735c: addiu v1,sp,0x20 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7360: move s3,v1 */ set(19,cpu(3));
L_002d7364:;
/* 002d7364: lw v0,0x1dc(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d7368: lw v1,0x1e0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d736c: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 002d7370: bnel v0,zero,0x002d7388 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d7374 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d7388;}}
/* 002d7378: andi v0,s7,0x1 */ set(2,cpu(23)&UINT32_C(0x00000001));
/* 002d737c: beq v0,zero,0x002d7b5c */ {int taken=(cpu(2)==cpu(0));/* delay 002d7380 */ set(2,cpu(23)&UINT32_C(0x00000004));if(taken){goto L_002d7b5c;}}
/* 002d7384: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d7388:;
/* 002d7388: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d738c: lw a0,0x1f4(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001f4)));
/* 002d7390: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7394: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7398: sw a0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002d739c: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d73a0: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d73a4: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d73a8: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d73ac: bne a0,zero,0x002d73d0 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d73b0 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d73d0;}}
/* 002d73b4: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d73b8: jal 0x002d6500 */ set(31,0x002d73c0u);/* delay 002d73bc */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d73b8));
/* 002d73c0: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d73c4 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d73c8: addiu a1,sp,0x20 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d73cc: move s3,a1 */ set(19,cpu(5));
L_002d73d0:;
/* 002d73d0: lw v0,0x1e0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d73d4: addiu s0,v0,-0x1 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002d73d8: blez s0,0x002d7b5c */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d73dc */ set(2,cpu(23)&UINT32_C(0x00000004));if(taken){goto L_002d7b5c;}}
/* 002d73e0: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d73e4: bne v0,zero,0x002d7458 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d73e8 */ set(7,sx(UINT32_C(0x00550000)));if(taken){goto L_002d7458;}}
/* 002d73ec: li s4,0x10 */ set(20,sx(UINT32_C(0x00000010)));
/* 002d73f0: addiu s1,a3,-0x4980 */ set(17,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d73f4: sw s4,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));
L_002d73f8:;
/* 002d73f8: sw s1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002d73fc: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7400: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7404: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7408: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d740c: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002d7410: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7414: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7418: bne a0,zero,0x002d7440 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d741c */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d7440;}}
/* 002d7420: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7424: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002d7428: jal 0x002d6500 */ set(31,0x002d7430u);/* delay 002d742c */ sq(7,ea(29,(int32_t)UINT32_C(0x00000230)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7428));
/* 002d7430: bne v0,zero,0x002d7ca0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7434 */ pkLq(7,ea(29,(int32_t)UINT32_C(0x00000230)));if(taken){goto L_002d7ca0;}}
/* 002d7438: addiu a2,sp,0x20 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d743c: move s3,a2 */ set(19,cpu(6));
L_002d7440:;
/* 002d7440: addiu s0,s0,-0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 002d7444: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d7448: beql v0,zero,0x002d73f8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d744c */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));goto L_002d73f8;}}
/* 002d7450: b 0x002d745c */ /* delay 002d7454 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d745c;
L_002d7458:;
/* 002d7458: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d745c:;
/* 002d745c: addiu v0,a3,-0x4980 */ set(2,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d7460: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d7464: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7468: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d746c: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7470: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7474: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d7478: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d747c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7480: b 0x002d7b34 */ /* delay 002d7484 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));goto L_002d7b34;
L_002d7488:;
/* 002d7488: bgtz v1,0x002d7670 */ {int taken=((int64_t)cpu(3)>0);/* delay 002d748c */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));if(taken){goto L_002d7670;}}
/* 002d7490: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
/* 002d7494: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d7498: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002d749c: addiu v0,v0,-0x4908 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb6f8)));
/* 002d74a0: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d74a4: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d74a8: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d74ac: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d74b0: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d74b4: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d74b8: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d74bc: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d74c0: bne a0,zero,0x002d74e4 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d74c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d74e4;}}
/* 002d74c8: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d74cc: jal 0x002d6500 */ set(31,0x002d74d4u);/* delay 002d74d0 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d74cc));
/* 002d74d4: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d74d8 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d74dc: addiu v1,sp,0x20 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d74e0: move s3,v1 */ set(19,cpu(3));
L_002d74e4:;
/* 002d74e4: lw v0,0x1dc(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d74e8: bnel v0,zero,0x002d7500 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d74ec */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d7500;}}
/* 002d74f0: lw v0,0x1e0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d74f4: beq v0,zero,0x002d7b5c */ {int taken=(cpu(2)==cpu(0));/* delay 002d74f8 */ set(2,cpu(23)&UINT32_C(0x00000004));if(taken){goto L_002d7b5c;}}
/* 002d74fc: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d7500:;
/* 002d7500: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7504: lw a0,0x1f4(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001f4)));
/* 002d7508: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d750c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7510: sw a0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002d7514: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7518: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d751c: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7520: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7524: bne a0,zero,0x002d7548 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7528 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d7548;}}
/* 002d752c: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7530: jal 0x002d6500 */ set(31,0x002d7538u);/* delay 002d7534 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7530));
/* 002d7538: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d753c */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d7540: addiu a1,sp,0x20 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7544: move s3,a1 */ set(19,cpu(5));
L_002d7548:;
/* 002d7548: lw v0,0x1dc(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d754c: subu s0,zero,v0 */ set(16,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));
/* 002d7550: blezl s0,0x002d7620 */ {int taken=((int64_t)cpu(16)<=0);if(taken){/* delay 002d7554 */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));goto L_002d7620;}}
/* 002d7558: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d755c: bne v0,zero,0x002d75d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7560 */ set(7,sx(UINT32_C(0x00550000)));if(taken){goto L_002d75d0;}}
/* 002d7564: li s4,0x10 */ set(20,sx(UINT32_C(0x00000010)));
/* 002d7568: addiu s1,a3,-0x4980 */ set(17,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d756c: sw s4,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));
L_002d7570:;
/* 002d7570: sw s1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002d7574: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7578: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d757c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7580: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7584: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002d7588: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d758c: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7590: bne a0,zero,0x002d75b8 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7594 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d75b8;}}
/* 002d7598: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d759c: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002d75a0: jal 0x002d6500 */ set(31,0x002d75a8u);/* delay 002d75a4 */ sq(7,ea(29,(int32_t)UINT32_C(0x00000230)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d75a0));
/* 002d75a8: bne v0,zero,0x002d7ca0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d75ac */ pkLq(7,ea(29,(int32_t)UINT32_C(0x00000230)));if(taken){goto L_002d7ca0;}}
/* 002d75b0: addiu a2,sp,0x20 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d75b4: move s3,a2 */ set(19,cpu(6));
L_002d75b8:;
/* 002d75b8: addiu s0,s0,-0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 002d75bc: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d75c0: beql v0,zero,0x002d7570 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d75c4 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));goto L_002d7570;}}
/* 002d75c8: b 0x002d75d4 */ /* delay 002d75cc */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d75d4;
L_002d75d0:;
/* 002d75d0: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d75d4:;
/* 002d75d4: addiu v0,a3,-0x4980 */ set(2,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d75d8: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d75dc: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d75e0: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d75e4: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d75e8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d75ec: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d75f0: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d75f4: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d75f8: bne a0,zero,0x002d761c */ {int taken=(cpu(4)!=cpu(0));/* delay 002d75fc */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d761c;}}
/* 002d7600: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7604: jal 0x002d6500 */ set(31,0x002d760cu);/* delay 002d7608 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7604));
/* 002d760c: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7610 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d7614: addiu v0,sp,0x20 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7618: move s3,v0 */ set(19,cpu(2));
L_002d761c:;
/* 002d761c: sw s5,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));
L_002d7620:;
/* 002d7620: lw v0,0x1e0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d7624: sw v0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d7628: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d762c: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7630: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7634: lw a0,0x1e0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d7638: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d763c: slti a1,v0,0x8 */ set(5,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7640: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 002d7644: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002d7648: bne a1,zero,0x002d7b58 */ {int taken=(cpu(5)!=cpu(0));/* delay 002d764c */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));if(taken){goto L_002d7b58;}}
/* 002d7650: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7654: jal 0x002d6500 */ set(31,0x002d765cu);/* delay 002d7658 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7654));
/* 002d765c: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7660 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d7664: addiu v1,sp,0x20 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7668: b 0x002d7b58 */ /* delay 002d766c */ set(19,cpu(3));goto L_002d7b58;
L_002d7670:;
/* 002d7670: slt v0,v1,v0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(2));
/* 002d7674: bne v0,zero,0x002d77e8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7678 */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));if(taken){goto L_002d77e8;}}
/* 002d767c: lw v0,0x1e0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d7680: sw v0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d7684: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7688: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d768c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7690: lw a1,0x1e0(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d7694: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7698: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d769c: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 002d76a0: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 002d76a4: bne a0,zero,0x002d76cc */ {int taken=(cpu(4)!=cpu(0));/* delay 002d76a8 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));if(taken){goto L_002d76cc;}}
/* 002d76ac: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d76b0: jal 0x002d6500 */ set(31,0x002d76b8u);/* delay 002d76b4 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d76b0));
/* 002d76b8: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d76bc */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d76c0: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d76c4: lw a1,0x1e0(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d76c8: move s3,a0 */ set(19,cpu(4));
L_002d76cc:;
/* 002d76cc: lw v0,0x1dc(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d76d0: subu s0,v0,a1 */ set(16,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 002d76d4: blez s0,0x002d77a8 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d76d8 */ set(2,cpu(23)&UINT32_C(0x00000001));if(taken){goto L_002d77a8;}}
/* 002d76dc: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d76e0: bne v0,zero,0x002d7758 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d76e4 */ set(7,sx(UINT32_C(0x00550000)));if(taken){goto L_002d7758;}}
/* 002d76e8: li s4,0x10 */ set(20,sx(UINT32_C(0x00000010)));
/* 002d76ec: addiu s1,a3,-0x4980 */ set(17,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d76f0: sw s4,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));
/* 002d76f4: nop  */ 
L_002d76f8:;
/* 002d76f8: sw s1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002d76fc: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7700: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7704: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7708: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d770c: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002d7710: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7714: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7718: bne a0,zero,0x002d7740 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d771c */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d7740;}}
/* 002d7720: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7724: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002d7728: jal 0x002d6500 */ set(31,0x002d7730u);/* delay 002d772c */ sq(7,ea(29,(int32_t)UINT32_C(0x00000230)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7728));
/* 002d7730: bne v0,zero,0x002d7ca0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7734 */ pkLq(7,ea(29,(int32_t)UINT32_C(0x00000230)));if(taken){goto L_002d7ca0;}}
/* 002d7738: addiu a1,sp,0x20 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d773c: move s3,a1 */ set(19,cpu(5));
L_002d7740:;
/* 002d7740: addiu s0,s0,-0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 002d7744: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d7748: beql v0,zero,0x002d76f8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d774c */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));goto L_002d76f8;}}
/* 002d7750: b 0x002d775c */ /* delay 002d7754 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d775c;
L_002d7758:;
/* 002d7758: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d775c:;
/* 002d775c: addiu v0,a3,-0x4980 */ set(2,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d7760: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d7764: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7768: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d776c: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7770: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7774: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d7778: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d777c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7780: bne a0,zero,0x002d77a4 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7784 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d77a4;}}
/* 002d7788: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d778c: jal 0x002d6500 */ set(31,0x002d7794u);/* delay 002d7790 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d778c));
/* 002d7794: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7798 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d779c: addiu a2,sp,0x20 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d77a0: move s3,a2 */ set(19,cpu(6));
L_002d77a4:;
/* 002d77a4: andi v0,s7,0x1 */ set(2,cpu(23)&UINT32_C(0x00000001));
L_002d77a8:;
/* 002d77a8: beq v0,zero,0x002d7b58 */ {int taken=(cpu(2)==cpu(0));/* delay 002d77ac */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_002d7b58;}}
/* 002d77b0: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d77b4: sw v1,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d77b8: addiu v0,v0,-0x4900 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb700)));
/* 002d77bc: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d77c0: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d77c4: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d77c8: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d77cc: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d77d0: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d77d4: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d77d8: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d77dc: b 0x002d7b34 */ /* delay 002d77e0 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));goto L_002d7b34;
L_002d77e8:;
/* 002d77e8: lw v0,0x1dc(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d77ec: sw v0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d77f0: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d77f4: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d77f8: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d77fc: lw a3,0x1dc(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d7800: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7804: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7808: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 002d780c: addu v1,v1,a3 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 002d7810: bne a0,zero,0x002d7838 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7814 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));if(taken){goto L_002d7838;}}
/* 002d7818: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d781c: jal 0x002d6500 */ set(31,0x002d7824u);/* delay 002d7820 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d781c));
/* 002d7824: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7828 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d782c: addiu v1,sp,0x20 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7830: lw a3,0x1dc(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d7834: move s3,v1 */ set(19,cpu(3));
L_002d7838:;
/* 002d7838: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002d783c: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d7840: sw v1,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 002d7844: addiu v0,v0,-0x4900 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb700)));
/* 002d7848: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d784c: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7850: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7854: addu s5,s5,a3 */ set(21,sx((uint32_t)cpu(21)+(uint32_t)cpu(7)));
/* 002d7858: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d785c: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7860: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7864: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7868: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d786c: bne a0,zero,0x002d7890 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7870 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d7890;}}
/* 002d7874: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7878: jal 0x002d6500 */ set(31,0x002d7880u);/* delay 002d787c */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7878));
/* 002d7880: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7884 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d7888: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d788c: move s3,a0 */ set(19,cpu(4));
L_002d7890:;
/* 002d7890: sw s5,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));
/* 002d7894: lw v1,0x1dc(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d7898: lw v0,0x1e0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d789c: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002d78a0: sw v0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d78a4: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d78a8: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d78ac: lw a0,0x1e0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d78b0: lw a1,0x1dc(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x000001dc)));
/* 002d78b4: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d78b8: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d78bc: slti a2,v1,0x8 */ set(6,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d78c0: subu a0,a0,a1 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(5)));
/* 002d78c4: sw v1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 002d78c8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002d78cc: bne a2,zero,0x002d7b58 */ {int taken=(cpu(6)!=cpu(0));/* delay 002d78d0 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));if(taken){goto L_002d7b58;}}
/* 002d78d4: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d78d8: jal 0x002d6500 */ set(31,0x002d78e0u);/* delay 002d78dc */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d78d8));
/* 002d78e0: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d78e4 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d78e8: addiu a1,sp,0x20 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d78ec: b 0x002d7b58 */ /* delay 002d78f0 */ set(19,cpu(5));goto L_002d7b58;
L_002d78f8:;
/* 002d78f8: slti v0,v0,0x2 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d78fc: beql v0,zero,0x002d7914 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d7900 */ set(3,byte(ea(21,(int32_t)UINT32_C(0x00000000))));goto L_002d7914;}}
/* 002d7904: andi v0,s7,0x1 */ set(2,cpu(23)&UINT32_C(0x00000001));
/* 002d7908: beq v0,zero,0x002d7ac0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d790c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002d7ac0;}}
/* 002d7910: lbu v1,0x0(s5) */ set(3,byte(ea(21,(int32_t)UINT32_C(0x00000000))));
L_002d7914:;
/* 002d7914: addiu s5,s5,0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));
/* 002d7918: li a0,0x2e */ set(4,sx(UINT32_C(0x0000002e)));
/* 002d791c: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 002d7920: sb v1,0x1c0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x000001c0)),(uint8_t)cpu(3));
/* 002d7924: addiu v0,sp,0x1c0 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x000001c0)));
/* 002d7928: sb a0,0x1c1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x000001c1)),(uint8_t)cpu(4));
/* 002d792c: sw a1,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 002d7930: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d7934: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7938: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d793c: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7940: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7944: addiu v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 002d7948: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d794c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7950: bne a0,zero,0x002d7974 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7954 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d7974;}}
/* 002d7958: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d795c: jal 0x002d6500 */ set(31,0x002d7964u);/* delay 002d7960 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d795c));
/* 002d7964: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7968 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d796c: addiu a2,sp,0x20 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7970: move s3,a2 */ set(19,cpu(6));
L_002d7974:;
/* 002d7974: ld a0,0x1f8(sp) */ restore(4,ea(29,(int32_t)UINT32_C(0x000001f8)));
/* 002d7978: move a1,zero */ set(5,cpu(0));
/* 002d797c: jal 0x002d1b38 */ set(31,0x002d7984u);/* delay 002d7980 */ nocturneBattlePanelRendererCall(UINT32_C(0x002d1b38),UINT32_C(0x002d797c));
/* 002d7984: beq v0,zero,0x002d79e8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d7988 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));if(taken){goto L_002d79e8;}}
/* 002d798c: sw s5,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));
/* 002d7990: lw v0,0x1e0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d7994: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002d7998: sw v0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d799c: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d79a0: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d79a4: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d79a8: lw a0,0x1e0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e0)));
/* 002d79ac: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d79b0: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002d79b4: slti a1,v0,0x8 */ set(5,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d79b8: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 002d79bc: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 002d79c0: bne a1,zero,0x002d7b08 */ {int taken=(cpu(5)!=cpu(0));/* delay 002d79c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));if(taken){goto L_002d7b08;}}
/* 002d79c8: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d79cc: jal 0x002d6500 */ set(31,0x002d79d4u);/* delay 002d79d0 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d79cc));
/* 002d79d4: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d79d8 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d79dc: addiu v0,sp,0x20 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d79e0: b 0x002d7b08 */ /* delay 002d79e4 */ set(19,cpu(2));goto L_002d7b08;
L_002d79e8:;
/* 002d79e8: addiu s0,v0,-0x1 */ set(16,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002d79ec: blez s0,0x002d7b0c */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d79f0 */ lw(6,ea(29,(int32_t)UINT32_C(0x00000200)));if(taken){goto L_002d7b0c;}}
/* 002d79f4: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d79f8: bne v0,zero,0x002d7a70 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d79fc */ set(7,sx(UINT32_C(0x00550000)));if(taken){goto L_002d7a70;}}
/* 002d7a00: li s4,0x10 */ set(20,sx(UINT32_C(0x00000010)));
/* 002d7a04: addiu s1,a3,-0x4980 */ set(17,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d7a08: sw s4,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));
/* 002d7a0c: nop  */ 
L_002d7a10:;
/* 002d7a10: sw s1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002d7a14: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7a18: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7a1c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7a20: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7a24: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002d7a28: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7a2c: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7a30: bne a0,zero,0x002d7a58 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7a34 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d7a58;}}
/* 002d7a38: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7a3c: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002d7a40: jal 0x002d6500 */ set(31,0x002d7a48u);/* delay 002d7a44 */ sq(7,ea(29,(int32_t)UINT32_C(0x00000230)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7a40));
/* 002d7a48: bne v0,zero,0x002d7ca0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7a4c */ pkLq(7,ea(29,(int32_t)UINT32_C(0x00000230)));if(taken){goto L_002d7ca0;}}
/* 002d7a50: addiu v1,sp,0x20 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7a54: move s3,v1 */ set(19,cpu(3));
L_002d7a58:;
/* 002d7a58: addiu s0,s0,-0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 002d7a5c: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d7a60: beql v0,zero,0x002d7a10 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d7a64 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));goto L_002d7a10;}}
/* 002d7a68: b 0x002d7a74 */ /* delay 002d7a6c */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d7a74;
L_002d7a70:;
/* 002d7a70: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d7a74:;
/* 002d7a74: addiu v0,a3,-0x4980 */ set(2,sx((uint32_t)cpu(7)+UINT32_C(0xffffb680)));
/* 002d7a78: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d7a7c: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7a80: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7a84: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7a88: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7a8c: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d7a90: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7a94: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7a98: bne a0,zero,0x002d7b08 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7a9c */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d7b08;}}
/* 002d7aa0: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7aa4: jal 0x002d6500 */ set(31,0x002d7aacu);/* delay 002d7aa8 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7aa4));
/* 002d7aac: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7ab0 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d7ab4: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7ab8: b 0x002d7b08 */ /* delay 002d7abc */ set(19,cpu(4));goto L_002d7b08;
L_002d7ac0:;
/* 002d7ac0: sw s5,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(21));
/* 002d7ac4: sw v0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d7ac8: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7acc: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7ad0: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7ad4: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7ad8: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7adc: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7ae0: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7ae4: bne a0,zero,0x002d7b08 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7ae8 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d7b08;}}
/* 002d7aec: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7af0: jal 0x002d6500 */ set(31,0x002d7af8u);/* delay 002d7af4 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7af0));
/* 002d7af8: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7afc */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d7b00: addiu a1,sp,0x20 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7b04: move s3,a1 */ set(19,cpu(5));
L_002d7b08:;
/* 002d7b08: lw a2,0x200(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000200)));
L_002d7b0c:;
/* 002d7b0c: sw sp,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(29));
/* 002d7b10: sw a2,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(6));
/* 002d7b14: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7b18: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7b1c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7b20: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7b24: addu v1,v1,a2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
L_002d7b28:;
/* 002d7b28: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7b2c: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7b30: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
L_002d7b34:;
/* 002d7b34: bne a0,zero,0x002d7b5c */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7b38 */ set(2,cpu(23)&UINT32_C(0x00000004));if(taken){goto L_002d7b5c;}}
/* 002d7b3c: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7b40: jal 0x002d6500 */ set(31,0x002d7b48u);/* delay 002d7b44 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7b40));
/* 002d7b48: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7b4c */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
/* 002d7b50: addiu v0,sp,0x20 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7b54: move s3,v0 */ set(19,cpu(2));
L_002d7b58:;
/* 002d7b58: andi v0,s7,0x4 */ set(2,cpu(23)&UINT32_C(0x00000004));
L_002d7b5c:;
/* 002d7b5c: beq v0,zero,0x002d7c30 */ {int taken=(cpu(2)==cpu(0));/* delay 002d7b60 */ lw(3,ea(29,(int32_t)UINT32_C(0x000001f0)));if(taken){goto L_002d7c30;}}
/* 002d7b64: lw a0,0x208(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000208)));
/* 002d7b68: subu s0,v1,a0 */ set(16,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 002d7b6c: blez s0,0x002d7c38 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d7b70 */ lw(6,ea(29,(int32_t)UINT32_C(0x00000208)));if(taken){goto L_002d7c38;}}
/* 002d7b74: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d7b78: bne v0,zero,0x002d7bf0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7b7c */ set(7,sx(UINT32_C(0x00550000)));if(taken){goto L_002d7bf0;}}
/* 002d7b80: li s4,0x10 */ set(20,sx(UINT32_C(0x00000010)));
/* 002d7b84: addiu s1,a3,-0x4990 */ set(17,sx((uint32_t)cpu(7)+UINT32_C(0xffffb670)));
/* 002d7b88: sw s4,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));
/* 002d7b8c: nop  */ 
L_002d7b90:;
/* 002d7b90: sw s1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002d7b94: addiu s3,s3,0x8 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000008)));
/* 002d7b98: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7b9c: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7ba0: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d7ba4: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 002d7ba8: slti a0,v0,0x8 */ set(4,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7bac: sw v1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 002d7bb0: bne a0,zero,0x002d7bd8 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7bb4 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));if(taken){goto L_002d7bd8;}}
/* 002d7bb8: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7bbc: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002d7bc0: jal 0x002d6500 */ set(31,0x002d7bc8u);/* delay 002d7bc4 */ sq(7,ea(29,(int32_t)UINT32_C(0x00000230)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7bc0));
/* 002d7bc8: bne v0,zero,0x002d7ca0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7bcc */ pkLq(7,ea(29,(int32_t)UINT32_C(0x00000230)));if(taken){goto L_002d7ca0;}}
/* 002d7bd0: addiu a1,sp,0x20 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7bd4: move s3,a1 */ set(19,cpu(5));
L_002d7bd8:;
/* 002d7bd8: addiu s0,s0,-0x10 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 002d7bdc: slti v0,s0,0x11 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002d7be0: beql v0,zero,0x002d7b90 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d7be4 */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(20));goto L_002d7b90;}}
/* 002d7be8: b 0x002d7bf4 */ /* delay 002d7bec */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002d7bf4;
L_002d7bf0:;
/* 002d7bf0: sw s0,0x4(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
L_002d7bf4:;
/* 002d7bf4: addiu v0,a3,-0x4990 */ set(2,sx((uint32_t)cpu(7)+UINT32_C(0xffffb670)));
/* 002d7bf8: sw v0,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d7bfc: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 002d7c00: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7c04: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d7c08: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d7c0c: slti a0,v1,0x8 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d7c10: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002d7c14: bne a0,zero,0x002d7c30 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d7c18 */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));if(taken){goto L_002d7c30;}}
/* 002d7c1c: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7c20: jal 0x002d6500 */ set(31,0x002d7c28u);/* delay 002d7c24 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7c20));
/* 002d7c28: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7c2c */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
L_002d7c30:;
/* 002d7c30: lw a2,0x208(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000208)));
/* 002d7c34: lw v1,0x1f0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000001f0)));
L_002d7c38:;
/* 002d7c38: lw a0,0x1f0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001f0)));
/* 002d7c3c: slt v0,a2,v1 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(3));
/* 002d7c40: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d7c44: lw a1,0x1ec(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x000001ec)));
/* 002d7c48: movz a0,a2,v0 */ if(cpu(2)==0){set(4,cpu(6));}
/* 002d7c4c: addu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 002d7c50: beq v1,zero,0x002d7c6c */ {int taken=(cpu(3)==cpu(0));/* delay 002d7c54 */ sw(ea(29,(int32_t)UINT32_C(0x000001ec)),(uint32_t)cpu(5));if(taken){goto L_002d7c6c;}}
/* 002d7c58: lw a0,0x1e8(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));
/* 002d7c5c: jal 0x002d6500 */ set(31,0x002d7c64u);/* delay 002d7c60 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7c5c));
/* 002d7c64: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7c68 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
L_002d7c6c:;
/* 002d7c6c: addiu a2,sp,0x20 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d7c70: sw zero,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002d7c74: b 0x002d6748 */ /* delay 002d7c78 */ set(19,cpu(6));goto L_002d6748;
L_002d7c80:;
/* 002d7c80: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
L_002d7c84:;
/* 002d7c84: beq v0,zero,0x002d7c9c */ {int taken=(cpu(2)==cpu(0));/* delay 002d7c88 */ lw(4,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7c9c;}}
/* 002d7c8c: jal 0x002d6500 */ set(31,0x002d7c94u);/* delay 002d7c90 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002d6500),UINT32_C(0x002d7c8c));
/* 002d7c94: bne v0,zero,0x002d7ca4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7c98 */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));if(taken){goto L_002d7ca4;}}
L_002d7c9c:;
/* 002d7c9c: sw zero,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
L_002d7ca0:;
/* 002d7ca0: lw v0,0x1e8(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000001e8)));
L_002d7ca4:;
/* 002d7ca4: lw a0,0x1ec(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x000001ec)));
/* 002d7ca8: lhu v1,0xc(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 002d7cac: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d7cb0: andi v1,v1,0x40 */ set(3,cpu(3)&UINT32_C(0x00000040));
/* 002d7cb4: movz v0,a0,v1 */ if(cpu(3)==0){set(2,cpu(4));}
L_002d7cb8:;
/* 002d7cb8: ld s0,0x240(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000240)));
L_002d7cbc:;
/* 002d7cbc: ld s1,0x248(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000248)));
/* 002d7cc0: ld s2,0x250(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000250)));
/* 002d7cc4: ld s3,0x258(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000258)));
/* 002d7cc8: ld s4,0x260(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000260)));
/* 002d7ccc: ld s5,0x268(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000268)));
/* 002d7cd0: ld s6,0x270(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000270)));
/* 002d7cd4: ld s7,0x278(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000278)));
/* 002d7cd8: ld s8,0x280(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000280)));
/* 002d7cdc: ld ra,0x288(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000288)));
/* 002d7ce0: jr ra */ {uint64_t target=cpu(31);/* delay 002d7ce4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000290)));checkReturn(target,incoming);return cpu(2);}
}
static uint64_t body_002d9e00(void){
nocturneEffectAxisNoteEntry(0x002d9e00u);
uint64_t incoming=cpu(31);
/* 002d9e00: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002d9e04: move v0,zero */ set(2,cpu(0));
/* 002d9e08: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9e0c: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d9e10: move s6,a1 */ set(22,cpu(5));
/* 002d9e14: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9e18: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d9e1c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d9e20: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d9e24: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002d9e28: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d9e2c: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d9e30: lw s2,0x8(s6) */ lw(18,ea(22,(int32_t)UINT32_C(0x00000008)));
/* 002d9e34: beq s2,zero,0x002da1b4 */ {int taken=(cpu(18)==cpu(0));/* delay 002d9e38 */ set(17,cpu(4));if(taken){goto L_002da1b4;}}
/* 002d9e3c: lhu v1,0xc(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002d9e40: andi v0,v1,0x8 */ set(2,cpu(3)&UINT32_C(0x00000008));
/* 002d9e44: beq v0,zero,0x002d9e58 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9e48 */ if(taken){goto L_002d9e58;}}
/* 002d9e4c: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002d9e50: bne v0,zero,0x002d9e70 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9e54 */ set(2,cpu(3)&UINT32_C(0x00000002));if(taken){goto L_002d9e70;}}
L_002d9e58:;
/* 002d9e58: jal 0x002d8038 */ set(31,0x002d9e60u);/* delay 002d9e5c */ nocturneBattlePanelRendererCall(UINT32_C(0x002d8038),UINT32_C(0x002d9e58));
/* 002d9e60: bne v0,zero,0x002da1b4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9e64 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002da1b4;}}
/* 002d9e68: lhu v1,0xc(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002d9e6c: andi v0,v1,0x2 */ set(2,cpu(3)&UINT32_C(0x00000002));
L_002d9e70:;
/* 002d9e70: lw s4,0x0(s6) */ lw(20,ea(22,(int32_t)UINT32_C(0x00000000)));
/* 002d9e74: beq v0,zero,0x002d9ef0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9e78 */ set(18,cpu(0));if(taken){goto L_002d9ef0;}}
/* 002d9e7c: li s5,0x400 */ set(21,sx(UINT32_C(0x00000400)));
L_002d9e80:;
/* 002d9e80: bnel s2,zero,0x002d9ea8 */ {int taken=(cpu(18)!=cpu(0));if(taken){/* delay 002d9e84 */ set(3,cpu(18)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000401));goto L_002d9ea8;}}
L_002d9e88:;
/* 002d9e88: lw s2,0x4(s4) */ lw(18,ea(20,(int32_t)UINT32_C(0x00000004)));
/* 002d9e8c: lw s3,0x0(s4) */ lw(19,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 002d9e90: nop  */ 
/* 002d9e94: nop  */ 
/* 002d9e98: nop  */ 
/* 002d9e9c: beq s2,zero,0x002d9e88 */ {int taken=(cpu(18)==cpu(0));/* delay 002d9ea0 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000008)));if(taken){goto L_002d9e88;}}
/* 002d9ea4: sltiu v1,s2,0x401 */ set(3,cpu(18)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000401));
L_002d9ea8:;
/* 002d9ea8: lw v0,0x24(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 002d9eac: lw a0,0x1c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 002d9eb0: move a2,s5 */ set(6,cpu(21));
/* 002d9eb4: movn a2,s2,v1 */ if(cpu(3)!=0){set(6,cpu(18));}
/* 002d9eb8: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002d9ec0u);/* delay 002d9ebc */ set(5,cpu(19));nocturneBattlePanelRendererIndirect(target,UINT32_C(0x002d9eb8));}
/* 002d9ec0: move s0,v0 */ set(16,cpu(2));
/* 002d9ec4: blezl s0,0x002da1a8 */ {int taken=((int64_t)cpu(16)<=0);if(taken){/* delay 002d9ec8 */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));goto L_002da1a8;}}
/* 002d9ecc: lw v0,0x8(s6) */ lw(2,ea(22,(int32_t)UINT32_C(0x00000008)));
/* 002d9ed0: addu s3,s3,s0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(16)));
/* 002d9ed4: subu s2,s2,s0 */ set(18,sx((uint32_t)cpu(18)-(uint32_t)cpu(16)));
/* 002d9ed8: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 002d9edc: bne v0,zero,0x002d9e80 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9ee0 */ sw(ea(22,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002d9e80;}}
/* 002d9ee4: b 0x002da1b4 */ /* delay 002d9ee8 */ set(2,cpu(0));goto L_002da1b4;
L_002d9ef0:;
/* 002d9ef0: andi v0,v1,0x1 */ set(2,cpu(3)&UINT32_C(0x00000001));
/* 002d9ef4: bne v0,zero,0x002da040 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d9ef8 */ set(23,cpu(0));if(taken){goto L_002da040;}}
/* 002d9efc: b 0x002d9f10 */ /* delay 002d9f00 */ goto L_002d9f10;
L_002d9f08:;
/* 002d9f08: lhu v1,0xc(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002d9f0c: nop  */ 
L_002d9f10:;
/* 002d9f10: bne s2,zero,0x002d9f38 */ {int taken=(cpu(18)!=cpu(0));/* delay 002d9f14 */ set(2,cpu(3)&UINT32_C(0x00000200));if(taken){goto L_002d9f38;}}
L_002d9f18:;
/* 002d9f18: lw s2,0x4(s4) */ lw(18,ea(20,(int32_t)UINT32_C(0x00000004)));
/* 002d9f1c: lw s3,0x0(s4) */ lw(19,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 002d9f20: nop  */ 
/* 002d9f24: nop  */ 
/* 002d9f28: nop  */ 
/* 002d9f2c: beq s2,zero,0x002d9f18 */ {int taken=(cpu(18)==cpu(0));/* delay 002d9f30 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000008)));if(taken){goto L_002d9f18;}}
/* 002d9f34: andi v0,v1,0x200 */ set(2,cpu(3)&UINT32_C(0x00000200));
L_002d9f38:;
/* 002d9f38: beq v0,zero,0x002d9f70 */ {int taken=(cpu(2)==cpu(0));/* delay 002d9f3c */ lw(16,ea(17,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002d9f70;}}
/* 002d9f40: sltu v0,s2,s0 */ set(2,cpu(18)<cpu(16));
/* 002d9f44: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002d9f48: movn s0,s2,v0 */ if(cpu(2)!=0){set(16,cpu(18));}
/* 002d9f4c: move a1,s3 */ set(5,cpu(19));
/* 002d9f50: jal 0x002d4454 */ set(31,0x002d9f58u);/* delay 002d9f54 */ set(6,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d4454),UINT32_C(0x002d9f50));
/* 002d9f58: lw v1,0x8(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002d9f5c: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002d9f60: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 002d9f64: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002d9f68: b 0x002da014 */ /* delay 002d9f6c */ set(16,cpu(18));goto L_002da014;
L_002d9f70:;
/* 002d9f70: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002d9f74: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002d9f78: sltu v0,v0,a0 */ set(2,cpu(2)<cpu(4));
/* 002d9f7c: beql v0,zero,0x002d9fc0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d9f80 */ lw(16,ea(17,(int32_t)UINT32_C(0x00000014)));goto L_002d9fc0;}}
/* 002d9f84: sltu v0,s0,s2 */ set(2,cpu(16)<cpu(18));
/* 002d9f88: beql v0,zero,0x002d9fc0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d9f8c */ lw(16,ea(17,(int32_t)UINT32_C(0x00000014)));goto L_002d9fc0;}}
/* 002d9f90: move a1,s3 */ set(5,cpu(19));
/* 002d9f94: jal 0x002d4454 */ set(31,0x002d9f9cu);/* delay 002d9f98 */ set(6,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d4454),UINT32_C(0x002d9f94));
/* 002d9f9c: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002d9fa0: move a0,s1 */ set(4,cpu(17));
/* 002d9fa4: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 002d9fa8: jal 0x002d95e0 */ set(31,0x002d9fb0u);/* delay 002d9fac */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));nocturneBattlePanelRendererCall(UINT32_C(0x002d95e0),UINT32_C(0x002d9fa8));
/* 002d9fb0: beql v0,zero,0x002da020 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d9fb4 */ lw(2,ea(22,(int32_t)UINT32_C(0x00000008)));goto L_002da020;}}
/* 002d9fb8: b 0x002da1a8 */ /* delay 002d9fbc */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));goto L_002da1a8;
L_002d9fc0:;
/* 002d9fc0: sltu v0,s2,s0 */ set(2,cpu(18)<cpu(16));
/* 002d9fc4: bnel v0,zero,0x002d9ff8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d9fc8 */ set(16,cpu(18));goto L_002d9ff8;}}
/* 002d9fcc: lw v0,0x24(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 002d9fd0: move a2,s0 */ set(6,cpu(16));
/* 002d9fd4: lw a0,0x1c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 002d9fd8: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002d9fe0u);/* delay 002d9fdc */ set(5,cpu(19));nocturneBattlePanelRendererIndirect(target,UINT32_C(0x002d9fd8));}
/* 002d9fe0: move s0,v0 */ set(16,cpu(2));
/* 002d9fe4: bgtzl s0,0x002da020 */ {int taken=((int64_t)cpu(16)>0);if(taken){/* delay 002d9fe8 */ lw(2,ea(22,(int32_t)UINT32_C(0x00000008)));goto L_002da020;}}
/* 002d9fec: b 0x002da1a8 */ /* delay 002d9ff0 */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));goto L_002da1a8;
L_002d9ff8:;
/* 002d9ff8: move a1,s3 */ set(5,cpu(19));
/* 002d9ffc: jal 0x002d4454 */ set(31,0x002da004u);/* delay 002da000 */ set(6,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d4454),UINT32_C(0x002d9ffc));
/* 002da004: lw v1,0x8(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002da008: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002da00c: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 002da010: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
L_002da014:;
/* 002da014: sw v1,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002da018: sw v0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002da01c: lw v0,0x8(s6) */ lw(2,ea(22,(int32_t)UINT32_C(0x00000008)));
L_002da020:;
/* 002da020: addu s3,s3,s0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(16)));
/* 002da024: subu s2,s2,s0 */ set(18,sx((uint32_t)cpu(18)-(uint32_t)cpu(16)));
/* 002da028: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 002da02c: bne v0,zero,0x002d9f08 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da030 */ sw(ea(22,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002d9f08;}}
/* 002da034: b 0x002da1b4 */ /* delay 002da038 */ set(2,cpu(0));goto L_002da1b4;
L_002da040:;
/* 002da040: bne s2,zero,0x002da06c */ {int taken=(cpu(18)!=cpu(0));/* delay 002da044 */ if(taken){goto L_002da06c;}}
/* 002da048: move s7,zero */ set(23,cpu(0));
/* 002da04c: nop  */ 
L_002da050:;
/* 002da050: lw s2,0x4(s4) */ lw(18,ea(20,(int32_t)UINT32_C(0x00000004)));
/* 002da054: lw s3,0x0(s4) */ lw(19,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 002da058: nop  */ 
/* 002da05c: nop  */ 
/* 002da060: nop  */ 
/* 002da064: beq s2,zero,0x002da050 */ {int taken=(cpu(18)==cpu(0));/* delay 002da068 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000008)));if(taken){goto L_002da050;}}
L_002da06c:;
/* 002da06c: bnel s7,zero,0x002da0a4 */ {int taken=(cpu(23)!=cpu(0));if(taken){/* delay 002da070 */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));goto L_002da0a4;}}
/* 002da074: move a0,s3 */ set(4,cpu(19));
/* 002da078: li a1,0xa */ set(5,sx(UINT32_C(0x0000000a)));
/* 002da07c: jal 0x002da4ec */ set(31,0x002da084u);/* delay 002da080 */ set(6,cpu(18));nocturneBattlePanelRendererCall(UINT32_C(0x002da4ec),UINT32_C(0x002da07c));
/* 002da084: beq v0,zero,0x002da098 */ {int taken=(cpu(2)==cpu(0));/* delay 002da088 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(19)));if(taken){goto L_002da098;}}
/* 002da08c: b 0x002da09c */ /* delay 002da090 */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));goto L_002da09c;
L_002da098:;
/* 002da098: addiu s5,s2,0x1 */ set(21,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
L_002da09c:;
/* 002da09c: li s7,0x1 */ set(23,sx(UINT32_C(0x00000001)));
/* 002da0a0: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
L_002da0a4:;
/* 002da0a4: sltu v0,s2,s5 */ set(2,cpu(18)<cpu(21));
/* 002da0a8: lw v1,0x10(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002da0ac: move a1,s2 */ set(5,cpu(18));
/* 002da0b0: lw a0,0x8(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002da0b4: movz a1,s5,v0 */ if(cpu(2)==0){set(5,cpu(21));}
/* 002da0b8: lw a3,0x14(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 002da0bc: sltu v1,v1,t0 */ set(3,cpu(3)<cpu(8));
/* 002da0c0: beq v1,zero,0x002da108 */ {int taken=(cpu(3)==cpu(0));/* delay 002da0c4 */ set(16,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));if(taken){goto L_002da108;}}
/* 002da0c8: slt v0,s0,a1 */ set(2,(int64_t)cpu(16)<(int64_t)cpu(5));
/* 002da0cc: beql v0,zero,0x002da10c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002da0d0 */ set(16,cpu(7));goto L_002da10c;}}
/* 002da0d4: move a0,t0 */ set(4,cpu(8));
/* 002da0d8: move a1,s3 */ set(5,cpu(19));
/* 002da0dc: jal 0x002d4454 */ set(31,0x002da0e4u);/* delay 002da0e0 */ set(6,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d4454),UINT32_C(0x002da0dc));
/* 002da0e4: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002da0e8: move a0,s1 */ set(4,cpu(17));
/* 002da0ec: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 002da0f0: jal 0x002d95e0 */ set(31,0x002da0f8u);/* delay 002da0f4 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));nocturneBattlePanelRendererCall(UINT32_C(0x002d95e0),UINT32_C(0x002da0f0));
/* 002da0f8: beq v0,zero,0x002da16c */ {int taken=(cpu(2)==cpu(0));/* delay 002da0fc */ set(21,sx((uint32_t)cpu(21)-(uint32_t)cpu(16)));if(taken){goto L_002da16c;}}
/* 002da100: b 0x002da1a8 */ /* delay 002da104 */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));goto L_002da1a8;
L_002da108:;
/* 002da108: move s0,a3 */ set(16,cpu(7));
L_002da10c:;
/* 002da10c: slt v0,a1,s0 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(16));
/* 002da110: bnel v0,zero,0x002da140 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002da114 */ set(16,cpu(5));goto L_002da140;}}
/* 002da118: lw v0,0x24(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 002da11c: move a2,s0 */ set(6,cpu(16));
/* 002da120: lw a0,0x1c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 002da124: jalr v0 */ {uint64_t target=cpu(2);set(31,0x002da12cu);/* delay 002da128 */ set(5,cpu(19));nocturneBattlePanelRendererIndirect(target,UINT32_C(0x002da124));}
/* 002da12c: move s0,v0 */ set(16,cpu(2));
/* 002da130: bgtz s0,0x002da16c */ {int taken=((int64_t)cpu(16)>0);/* delay 002da134 */ set(21,sx((uint32_t)cpu(21)-(uint32_t)cpu(16)));if(taken){goto L_002da16c;}}
/* 002da138: b 0x002da1a8 */ /* delay 002da13c */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));goto L_002da1a8;
L_002da140:;
/* 002da140: move a1,s3 */ set(5,cpu(19));
/* 002da144: move a0,t0 */ set(4,cpu(8));
/* 002da148: jal 0x002d4454 */ set(31,0x002da150u);/* delay 002da14c */ set(6,cpu(16));nocturneBattlePanelRendererCall(UINT32_C(0x002d4454),UINT32_C(0x002da148));
/* 002da150: lw v1,0x8(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002da154: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002da158: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 002da15c: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 002da160: sw v1,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002da164: sw v0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002da168: subu s5,s5,s0 */ set(21,sx((uint32_t)cpu(21)-(uint32_t)cpu(16)));
L_002da16c:;
/* 002da16c: bnel s5,zero,0x002da18c */ {int taken=(cpu(21)!=cpu(0));if(taken){/* delay 002da170 */ lw(2,ea(22,(int32_t)UINT32_C(0x00000008)));goto L_002da18c;}}
/* 002da174: jal 0x002d95e0 */ set(31,0x002da17cu);/* delay 002da178 */ set(4,cpu(17));nocturneBattlePanelRendererCall(UINT32_C(0x002d95e0),UINT32_C(0x002da174));
/* 002da17c: bnel v0,zero,0x002da1a8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002da180 */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));goto L_002da1a8;}}
/* 002da184: move s7,zero */ set(23,cpu(0));
/* 002da188: lw v0,0x8(s6) */ lw(2,ea(22,(int32_t)UINT32_C(0x00000008)));
L_002da18c:;
/* 002da18c: addu s3,s3,s0 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(16)));
/* 002da190: subu s2,s2,s0 */ set(18,sx((uint32_t)cpu(18)-(uint32_t)cpu(16)));
/* 002da194: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 002da198: bne v0,zero,0x002da040 */ {int taken=(cpu(2)!=cpu(0));/* delay 002da19c */ sw(ea(22,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002da040;}}
/* 002da1a0: b 0x002da1b4 */ /* delay 002da1a4 */ set(2,cpu(0));goto L_002da1b4;
L_002da1a8:;
/* 002da1a8: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002da1ac: ori v1,v1,0x40 */ set(3,cpu(3)|UINT32_C(0x00000040));
/* 002da1b0: sh v1,0xc(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(3));
L_002da1b4:;
/* 002da1b4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002da1b8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002da1bc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002da1c0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002da1c4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002da1c8: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002da1cc: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002da1d0: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002da1d4: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002da1d8: jr ra */ {uint64_t target=cpu(31);/* delay 002da1dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return cpu(2);}
}
static uint64_t body_002da308(void){
nocturneEffectAxisNoteEntry(0x002da308u);
uint64_t incoming=cpu(31);
/* 002da308: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002da30c: jr ra */ {uint64_t target=cpu(31);/* delay 002da310 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb8d8)));checkReturn(target,incoming);return cpu(2);}
}
static uint64_t body_002da340(void){
nocturneEffectAxisNoteEntry(0x002da340u);
/* 002da340: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002da344: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002da348: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002da34c: lw a0,-0x41d8(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0xffffbe28)));
/* 002da350: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002da354: j 0x002da308 */ /* delay 002da358 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneBattlePanelRendererCall(UINT32_C(0x002da308),UINT32_C(0x002da354));return cpu(2);
}
static uint64_t body_002da4b8(void){
nocturneEffectAxisNoteEntry(0x002da4b8u);
uint64_t incoming=cpu(31);
/* 002da4b8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002da4bc: move v0,zero */ set(2,cpu(0));
/* 002da4c0: move v1,sp */ set(3,cpu(29));
/* 002da4c4: beq a2,zero,0x002da4e4 */ {int taken=(cpu(6)==cpu(0));/* delay 002da4c8 */ if(cpu(5)!=0){set(3,cpu(5));}if(taken){goto L_002da4e4;}}
/* 002da4cc: beq a3,zero,0x002da4e4 */ {int taken=(cpu(7)==cpu(0));/* delay 002da4d0 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002da4e4;}}
/* 002da4d4: lbu v0,0x0(a2) */ set(2,byte(ea(6,(int32_t)UINT32_C(0x00000000))));
/* 002da4d8: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002da4dc: lbu v0,0x0(a2) */ set(2,byte(ea(6,(int32_t)UINT32_C(0x00000000))));
/* 002da4e0: sltu v0,zero,v0 */ set(2,cpu(0)<cpu(2));
L_002da4e4:;
/* 002da4e4: jr ra */ {uint64_t target=cpu(31);/* delay 002da4e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint32_t nocturneBattlePanelRendererExisting3(uint32_t entry){switch(entry){case UINT32_C(0x002d4454):(void)body_002d4454();return 1u;case UINT32_C(0x002d4748):(void)body_002d4748();return 1u;case UINT32_C(0x002d6500):(void)body_002d6500();return 1u;case UINT32_C(0x002d6600):(void)body_002d6600();return 1u;case UINT32_C(0x002d6678):(void)body_002d6678();return 1u;case UINT32_C(0x002d9e00):(void)body_002d9e00();return 1u;case UINT32_C(0x002da308):(void)body_002da308();return 1u;case UINT32_C(0x002da340):(void)body_002da340();return 1u;case UINT32_C(0x002da4b8):(void)body_002da4b8();return 1u;default:return 0u;}}
