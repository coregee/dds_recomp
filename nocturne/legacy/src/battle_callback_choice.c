/* Four genuine bank-entry variants, ten complete bodies/1320 instructions.
 * Fixed native-PC statements and guest frames; real registered calls.
 * Raw64 scalar ABI, not a shared fullvolatile/private-save-frame model.
 * No synthetic process, packet, RNG, actor or constructor results. */
#include "battle_callback_choice.h"
#include "nocturne.h"
#include <stdlib.h>
#include "battle_action_consumer.h"
#include "battle_action_finish.h"
#include "battle_action_sequence.h"
#include "battle_action_status.h"
#include "battle_affinity.h"
#include "battle_ai_actions.h"
#include "battle_ai_startup.h"
#include "battle_check1_packets.h"
#include "battle_kouka_packets.h"
#include "battle_support_access.h"
#include "battle_targeting.h"
#include "battle_work_access.h"
#include "libc_printf.h"
#include "material_construction_release.h"
#include "material_fiveword_pool.h"
#include "process_creation.h"
#include "process_lists.h"
#include "ps2_memory.h"
#include <string.h>
typedef struct BattleCallbackChoiceValues {uint64_t r[32],lo,hi;uint32_t f[32],condition;} BattleCallbackChoiceValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleCallbackChoiceAddress(a);}
static uint16_t hword(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}


static void body_00251ef0(BattleCallbackChoiceValues *c);
static void body_00251fd8(BattleCallbackChoiceValues *c);
static void body_00252400(BattleCallbackChoiceValues *c);
static void body_002525f0(BattleCallbackChoiceValues *c);
static void body_00252720(BattleCallbackChoiceValues *c);
static void body_002529d0(BattleCallbackChoiceValues *c);
static void body_002532a8(BattleCallbackChoiceValues *c);
static void body_00253490(BattleCallbackChoiceValues *c);
static void body_00257488(BattleCallbackChoiceValues *c);
static void body_002577d8(BattleCallbackChoiceValues *c);
static uint64_t native_frame(BattleCallbackChoiceValues *c,uint32_t kind,uint32_t pc,uint32_t mask){
 BattleCallbackChoiceBoundary b;unsigned i;b.pc=pc;b.defined_mask=mask;
 for(i=0;i<32u;++i)b.gpr[i]=(mask&(UINT32_C(1)<<i))?c->r[i]:0;
 return nocturneBattleCallbackChoiceNativeCall(kind,&b);
}
static void body_00251ef0(BattleCallbackChoiceValues *c){
/* 00251ef0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00251ef4: li a2,-0x5 */ c->r[6]=sx(UINT32_C(0xfffffffb));
/* 00251ef8: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00251efc: li s0,0xf */ c->r[16]=sx(UINT32_C(0x0000000f));
/* 00251f00: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00251f04: move s2,a0 */ c->r[18]=c->r[4];
/* 00251f08: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00251f0c: li a1,-0x9 */ c->r[5]=sx(UINT32_C(0xfffffff7));
/* 00251f10: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 00251f14: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00251f18: lw a0,0x0(v1) */ c->r[4]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 00251f1c: nop  */ (void)0;
L_00251f20:;
/* 00251f20: lw v0,0x78(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000078)));
/* 00251f24: addiu s0,s0,-0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffffff));
/* 00251f28: and v0,v0,a2 */ c->r[2]=c->r[2]&c->r[6];
/* 00251f2c: and v0,v0,a1 */ c->r[2]=c->r[2]&c->r[5];
/* 00251f30: sw v0,0x78(a0) */ sw((uint32_t)c->r[4]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
/* 00251f34: bgez s0,0x00251f20 */ {int taken=(!neg(c->r[16]));/* delay 00251f38 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000000f0));if(taken){goto L_00251f20;}}
/* 00251f3c: b 0x00251f60 */ /* delay 00251f40 */ c->r[16]=c->r[0];goto L_00251f60;
L_00251f48:;
/* 00251f48: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 00251f4c: addu v1,s1,v1 */ c->r[3]=sx((uint32_t)c->r[17]+(uint32_t)c->r[3]);
/* 00251f50: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 00251f54: ori v0,v0,0x8 */ c->r[2]=c->r[2]|UINT64_C(0x8);
/* 00251f58: b 0x00251fbc */ /* delay 00251f5c */ sw((uint32_t)c->r[3]+UINT32_C(0x00000078),(uint32_t)c->r[2]);goto L_00251fbc;
L_00251f60:;
/* 00251f60: sll v0,s0,0x4 */ c->r[2]=sx((uint32_t)c->r[16]<<4u);
/* 00251f64: lw v1,0x0(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 00251f68: subu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[16]);
/* 00251f6c: sll s1,v0,0x4 */ c->r[17]=sx((uint32_t)c->r[2]<<4u);
/* 00251f70: addu v1,s1,v1 */ c->r[3]=sx((uint32_t)c->r[17]+(uint32_t)c->r[3]);
/* 00251f74: lw v1,0x78(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 00251f78: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 00251f7c: beq v0,zero,0x00251fac */ {int taken=(c->r[2]==c->r[0]);/* delay 00251f80 */ c->r[4]=c->r[3]&UINT64_C(0x40);if(taken){goto L_00251fac;}}
/* 00251f84: beq a0,zero,0x00251fac */ {int taken=(c->r[4]==c->r[0]);/* delay 00251f88 */ c->r[2]=c->r[3]&UINT64_C(0x100);if(taken){goto L_00251fac;}}
/* 00251f8c: beql v0,zero,0x00251fb0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00251f90 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));goto L_00251fb0;}}
/* 00251f94: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x00251f9c);/* delay 00251f98 */ c->r[4]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,2u,UINT32_C(0x00251f94),UINT32_C(0xf0ff0010));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00251f9c: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 00251fa0: andi v1,v1,0x4 */ c->r[3]=c->r[3]&UINT64_C(0x4);
/* 00251fa4: bnel v1,zero,0x00251f48 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00251fa8 */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));goto L_00251f48;}}
L_00251fac:;
/* 00251fac: addiu s0,s0,0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));
L_00251fb0:;
/* 00251fb0: slti v0,s0,0x10 */ c->r[2]=less(c->r[16],sx(UINT32_C(0x00000010)));
/* 00251fb4: bnel v0,zero,0x00251f60 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00251fb8 */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));goto L_00251f60;}}
L_00251fbc:;
/* 00251fbc: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00251fc0: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00251fc4: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00251fc8: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00251fcc: jr ra */ /* delay 00251fd0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}
static void body_00251fd8(BattleCallbackChoiceValues *c){
/* 00251fd8: lw a0,0x0(a0) */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 00251fdc: li t0,-0x5 */ c->r[8]=sx(UINT32_C(0xfffffffb));
/* 00251fe0: li a2,-0x9 */ c->r[6]=sx(UINT32_C(0xfffffff7));
/* 00251fe4: li a3,0xf */ c->r[7]=sx(UINT32_C(0x0000000f));
/* 00251fe8: lw v1,0x0(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 00251fec: nop  */ (void)0;
L_00251ff0:;
/* 00251ff0: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 00251ff4: addiu a3,a3,-0x1 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0xffffffff));
/* 00251ff8: and v0,v0,t0 */ c->r[2]=c->r[2]&c->r[8];
/* 00251ffc: and v0,v0,a2 */ c->r[2]=c->r[2]&c->r[6];
/* 00252000: sw v0,0x78(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
/* 00252004: bgez a3,0x00251ff0 */ {int taken=(!neg(c->r[7]));/* delay 00252008 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x000000f0));if(taken){goto L_00251ff0;}}
/* 0025200c: lw a0,0x0(a0) */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 00252010: move a3,zero */ c->r[7]=c->r[0];
/* 00252014: nop  */ (void)0;
L_00252018:;
/* 00252018: lw a2,0x78(a0) */ c->r[6]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000078)));
/* 0025201c: andi v0,a2,0x1 */ c->r[2]=c->r[6]&UINT64_C(0x1);
/* 00252020: beq v0,zero,0x00252048 */ {int taken=(c->r[2]==c->r[0]);/* delay 00252024 */ c->r[3]=c->r[6]&UINT64_C(0x40);if(taken){goto L_00252048;}}
/* 00252028: beql v1,zero,0x0025204c */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 0025202c */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0x00000001));goto L_0025204c;}}
/* 00252030: lh v0,0x90(a0) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000090)));
/* 00252034: bnel v0,a1,0x0025204c */ {int taken=(c->r[2]!=c->r[5]);if(taken){/* delay 00252038 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0x00000001));goto L_0025204c;}}
/* 0025203c: ori v0,a2,0x8 */ c->r[2]=c->r[6]|UINT64_C(0x8);
/* 00252040: jr ra */ /* delay 00252044 */ sw((uint32_t)c->r[4]+UINT32_C(0x00000078),(uint32_t)c->r[2]);return;
L_00252048:;
/* 00252048: addiu a3,a3,0x1 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0x00000001));
L_0025204c:;
/* 0025204c: slti v0,a3,0x10 */ c->r[2]=less(c->r[7],sx(UINT32_C(0x00000010)));
/* 00252050: bne v0,zero,0x00252018 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00252054 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000000f0));if(taken){goto L_00252018;}}
/* 00252058: jr ra */ /* delay 0025205c */ (void)0;return;
}
static void body_00252400(BattleCallbackChoiceValues *c){
/* 00252400: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00252404: move v0,zero */ c->r[2]=c->r[0];
/* 00252408: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0025240c: move s1,a0 */ c->r[17]=c->r[4];
/* 00252410: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00252414: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00252418: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 0025241c: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00252420: lhu v1,0x7c(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x0000007c));
/* 00252424: addiu v1,v1,-0xf0 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffffff10));
/* 00252428: sltiu v1,v1,0x7 */ c->r[3]=(c->r[3]<sx(UINT32_C(0x00000007)));
/* 0025242c: bne v1,zero,0x002525d4 */ {int taken=(c->r[3]!=c->r[0]);/* delay 00252430 */ c->r[18]=c->r[0];if(taken){goto L_002525d4;}}
/* 00252434: lw v1,0x60(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000060)));
/* 00252438: andi v1,v1,0x1 */ c->r[3]=c->r[3]&UINT64_C(0x1);
/* 0025243c: bnel v1,zero,0x002525d8 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252440 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002525d8;}}
/* 00252444: lw a0,0x24(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000024)));
/* 00252448: lhu v1,0x0(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 0025244c: andi v1,v1,0x2 */ c->r[3]=c->r[3]&UINT64_C(0x2);
/* 00252450: beql v1,zero,0x002525d8 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00252454 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002525d8;}}
/* 00252458: lw v1,0x2c(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));
/* 0025245c: lhu a1,0x4(v1) */ c->r[5]=hword((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 00252460: sll a0,a1,0x1 */ c->r[4]=sx((uint32_t)c->r[5]<<1u);
/* 00252464: addu a0,a0,a1 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[5]);
/* 00252468: sll a0,a0,0x4 */ c->r[4]=sx((uint32_t)c->r[4]<<4u);
/* 0025246c: lui v1,0x3e */ c->r[3]=sx(UINT32_C(0x003e0000));
/* 00252470: addu v1,v1,a0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[4]);
/* 00252474: lhu v1,-0x34b6(v1) */ c->r[3]=hword((uint32_t)c->r[3]+UINT32_C(0xffffcb4a));
/* 00252478: beql v1,zero,0x002525d8 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 0025247c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002525d8;}}
/* 00252480: jal 0x00244530 */ c->r[31]=UINT64_C(0x00252488);/* delay 00252484 */ c->r[4]=c->r[5];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datSearchDevilStock(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252488: bgezl v0,0x002525d4 */ {int taken=(!neg(c->r[2]));if(taken){/* delay 0025248c */ c->r[2]=c->r[0];goto L_002525d4;}}
/* 00252490: jal 0x001e9998 */ c->r[31]=UINT64_C(0x00252498);/* delay 00252494 */ (void)0;nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(evtGetAgeOfMoon());nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252498: li v1,0x8 */ c->r[3]=sx(UINT32_C(0x00000008));
/* 0025249c: beql v0,v1,0x002525d4 */ {int taken=(c->r[2]==c->r[3]);if(taken){/* delay 002524a0 */ c->r[2]=c->r[0];goto L_002525d4;}}
/* 002524a4: jal 0x002444a8 */ c->r[31]=UINT64_C(0x002524ac);/* delay 002524a8 */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datCheckTalk(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002524ac: beql v0,zero,0x002525d8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002524b0 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002525d8;}}
/* 002524b4: lw a0,-0x5750(gp) */ c->r[4]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 002524b8: jal 0x002444a8 */ c->r[31]=UINT64_C(0x002524c0);/* delay 002524bc */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000a54));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datCheckTalk(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002524c0: beql v0,zero,0x002525d8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002524c4 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002525d8;}}
/* 002524c8: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 002524cc: lh v1,0x1a(a0) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x0000001a)));
/* 002524d0: slti v1,v1,0x2 */ c->r[3]=less(c->r[3],sx(UINT32_C(0x00000002)));
/* 002524d4: bne v1,zero,0x002525d4 */ {int taken=(c->r[3]!=c->r[0]);/* delay 002524d8 */ c->r[2]=c->r[0];if(taken){goto L_002525d4;}}
/* 002524dc: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 002524e0: li a1,0x10 */ c->r[5]=sx(UINT32_C(0x00000010));
/* 002524e4: jal 0x00267e90 */ c->r[31]=UINT64_C(0x002524ec);/* delay 002524e8 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounter(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002524ec: beql v0,zero,0x00252500 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002524f0 */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));goto L_00252500;}}
/* 002524f4: b 0x002525d4 */ /* delay 002524f8 */ c->r[2]=c->r[0];goto L_002525d4;
L_00252500:;
/* 00252500: lui a0,0x200 */ c->r[4]=sx(UINT32_C(0x02000000));
/* 00252504: lw v1,0x60(a1) */ c->r[3]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000060)));
/* 00252508: and v1,v1,a0 */ c->r[3]=c->r[3]&c->r[4];
/* 0025250c: bne v1,zero,0x00252528 */ {int taken=(c->r[3]!=c->r[0]);/* delay 00252510 */ c->r[16]=sx(UINT32_C(0x00000004));if(taken){goto L_00252528;}}
/* 00252514: lbu v1,0x68(a1) */ c->r[3]=*at((uint32_t)c->r[5]+UINT32_C(0x00000068));
/* 00252518: sltiu v1,v1,0x3 */ c->r[3]=(c->r[3]<sx(UINT32_C(0x00000003)));
/* 0025251c: bnel v1,zero,0x002525d8 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252520 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002525d8;}}
L_00252524:;
/* 00252524: nop  */ (void)0;
L_00252528:;
/* 00252528: sll v0,s0,0x4 */ c->r[2]=sx((uint32_t)c->r[16]<<4u);
/* 0025252c: lw a0,0x0(a1) */ c->r[4]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 00252530: subu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[16]);
/* 00252534: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 00252538: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 0025253c: lw v1,0x78(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000078)));
/* 00252540: andi v0,v1,0x40 */ c->r[2]=c->r[3]&UINT64_C(0x40);
/* 00252544: andi v1,v1,0x1 */ c->r[3]=c->r[3]&UINT64_C(0x1);
/* 00252548: beql v1,zero,0x0025256c */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 0025254c */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));goto L_0025256c;}}
/* 00252550: beq v0,zero,0x00252568 */ {int taken=(c->r[2]==c->r[0]);/* delay 00252554 */ c->r[4]=c->r[16];if(taken){goto L_00252568;}}
/* 00252558: jal 0x00267e90 */ c->r[31]=UINT64_C(0x00252560);/* delay 0025255c */ c->r[5]=sx(UINT32_C(0x00000010));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounter(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252560: addiu v1,s2,0x1 */ c->r[3]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));
/* 00252564: movz s2,v1,v0 */ if(c->r[2]==0){c->r[18]=c->r[3];}
L_00252568:;
/* 00252568: addiu s0,s0,0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));
L_0025256c:;
/* 0025256c: slti v0,s0,0xe */ c->r[2]=less(c->r[16],sx(UINT32_C(0x0000000e)));
/* 00252570: bnel v0,zero,0x00252524 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252574 */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));goto L_00252524;}}
/* 00252578: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 0025257c: bne s2,v1,0x002525d4 */ {int taken=(c->r[18]!=c->r[3]);/* delay 00252580 */ c->r[2]=c->r[0];if(taken){goto L_002525d4;}}
/* 00252584: lw v1,0x0(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00252588: lui a2,0x200 */ c->r[6]=sx(UINT32_C(0x02000000));
/* 0025258c: li a3,0x64 */ c->r[7]=sx(UINT32_C(0x00000064));
/* 00252590: li s0,0x5 */ c->r[16]=sx(UINT32_C(0x00000005));
/* 00252594: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 00252598: move a0,zero */ c->r[4]=c->r[0];
/* 0025259c: li a1,0x64 */ c->r[5]=sx(UINT32_C(0x00000064));
/* 002525a0: and v0,v0,a2 */ c->r[2]=c->r[2]&c->r[6];
/* 002525a4: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x002525ac);/* delay 002525a8 */ if(c->r[2]!=0){c->r[16]=c->r[7];}nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]==0?NULL:(uint32_t *)at((uint32_t)c->r[4]),(uint32_t)c->r[5]));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002525ac: slt v1,v0,s0 */ c->r[3]=less(c->r[2],c->r[16]);
/* 002525b0: beq v1,zero,0x002525d4 */ {int taken=(c->r[3]==c->r[0]);/* delay 002525b4 */ c->r[2]=c->r[0];if(taken){goto L_002525d4;}}
/* 002525b8: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 002525bc: li a1,0x10 */ c->r[5]=sx(UINT32_C(0x00000010));
/* 002525c0: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 002525c4: move a3,zero */ c->r[7]=c->r[0];
/* 002525c8: jal 0x00267f58 */ c->r[31]=UINT64_C(0x002525d0);/* delay 002525cc */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbSetHojoAddCounter(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002525d0: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_002525d4:;
/* 002525d4: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_002525d8:;
/* 002525d8: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002525dc: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002525e0: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002525e4: jr ra */ /* delay 002525e8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}
static void body_002525f0(BattleCallbackChoiceValues *c){
/* 002525f0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002525f4: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002525f8: move s1,a0 */ c->r[17]=c->r[4];
/* 002525fc: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00252600: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 00252604: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00252608: lhu v1,0x7c(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x0000007c));
/* 0025260c: addiu v1,v1,-0xf0 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffffff10));
/* 00252610: sltiu v1,v1,0x7 */ c->r[3]=(c->r[3]<sx(UINT32_C(0x00000007)));
/* 00252614: bne v1,zero,0x00252708 */ {int taken=(c->r[3]!=c->r[0]);/* delay 00252618 */ c->r[2]=c->r[0];if(taken){goto L_00252708;}}
/* 0025261c: lw a0,0x60(a0) */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000060)));
/* 00252620: andi v1,a0,0x1 */ c->r[3]=c->r[4]&UINT64_C(0x1);
/* 00252624: bnel v1,zero,0x0025270c */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252628 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0025270c;}}
/* 0025262c: andi v1,a0,0x80 */ c->r[3]=c->r[4]&UINT64_C(0x80);
/* 00252630: beq v1,zero,0x00252708 */ {int taken=(c->r[3]==c->r[0]);/* delay 00252634 */ c->r[3]=c->r[4]&UINT64_C(0x10);if(taken){goto L_00252708;}}
/* 00252638: bnel v1,zero,0x0025270c */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 0025263c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0025270c;}}
/* 00252640: andi v1,a0,0x100 */ c->r[3]=c->r[4]&UINT64_C(0x100);
/* 00252644: bnel v1,zero,0x0025270c */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252648 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0025270c;}}
/* 0025264c: jal 0x001e9998 */ c->r[31]=UINT64_C(0x00252654);/* delay 00252650 */ (void)0;nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(evtGetAgeOfMoon());nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252654: li v1,0x8 */ c->r[3]=sx(UINT32_C(0x00000008));
/* 00252658: bnel v0,v1,0x00252668 */ {int taken=(c->r[2]!=c->r[3]);if(taken){/* delay 0025265c */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));goto L_00252668;}}
/* 00252660: b 0x00252708 */ /* delay 00252664 */ c->r[2]=c->r[0];goto L_00252708;
L_00252668:;
/* 00252668: lhu v1,0x4(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000004));
/* 0025266c: sll a0,v1,0x1 */ c->r[4]=sx((uint32_t)c->r[3]<<1u);
/* 00252670: addu a0,a0,v1 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[3]);
/* 00252674: sll a0,a0,0x4 */ c->r[4]=sx((uint32_t)c->r[4]<<4u);
/* 00252678: lui v1,0x3e */ c->r[3]=sx(UINT32_C(0x003e0000));
/* 0025267c: addu v1,v1,a0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[4]);
/* 00252680: lbu v1,-0x34b9(v1) */ c->r[3]=*at((uint32_t)c->r[3]+UINT32_C(0xffffcb47));
/* 00252684: beq v1,zero,0x00252708 */ {int taken=(c->r[3]==c->r[0]);/* delay 00252688 */ c->r[2]=c->r[0];if(taken){goto L_00252708;}}
/* 0025268c: jal 0x002444a8 */ c->r[31]=UINT64_C(0x00252694);/* delay 00252690 */ c->r[4]=c->r[5];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datCheckTalk(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252694: beq v0,zero,0x00252708 */ {int taken=(c->r[2]==c->r[0]);/* delay 00252698 */ c->r[4]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));if(taken){goto L_00252708;}}
/* 0025269c: jal 0x002444a8 */ c->r[31]=UINT64_C(0x002526a4);/* delay 002526a0 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000a54));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datCheckTalk(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002526a4: beq v0,zero,0x00252708 */ {int taken=(c->r[2]==c->r[0]);/* delay 002526a8 */ c->r[3]=sx(UINT32_C(0x02000000));if(taken){goto L_00252708;}}
/* 002526ac: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 002526b0: lw v0,0x60(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000060)));
/* 002526b4: and v0,v0,v1 */ c->r[2]=c->r[2]&c->r[3];
/* 002526b8: bnel v0,zero,0x002526dc */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002526bc */ c->r[16]=sx(UINT32_C(0x00000064));goto L_002526dc;}}
/* 002526c0: lh v0,0x1a(a0) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x0000001a)));
/* 002526c4: li v1,0x15 */ c->r[3]=sx(UINT32_C(0x00000015));
/* 002526c8: div v1,v0 */ {int32_t n=(int32_t)(uint32_t)c->r[3],d=(int32_t)(uint32_t)c->r[2];if(d==0){c->lo=n<0?UINT64_C(1):UINT64_MAX;c->hi=sx((uint32_t)n);}else if(n==INT32_MIN&&d==-1){c->lo=sx(UINT32_C(0x80000000));c->hi=0;}else{c->lo=sx((uint32_t)(n/d));c->hi=sx((uint32_t)(n%d));}}
/* 002526cc: beql v0,zero,0x002526d4 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002526d0 */ nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nocturne_break(7);goto L_002526d4;}}
L_002526d4:;
/* 002526d4: mflo v1 */ c->r[3]=c->lo;
/* 002526d8: move s0,v1 */ c->r[16]=c->r[3];
L_002526dc:;
/* 002526dc: move a0,zero */ c->r[4]=c->r[0];
/* 002526e0: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x002526e8);/* delay 002526e4 */ c->r[5]=sx(UINT32_C(0x00000064));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]==0?NULL:(uint32_t *)at((uint32_t)c->r[4]),(uint32_t)c->r[5]));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002526e8: slt v1,v0,s0 */ c->r[3]=less(c->r[2],c->r[16]);
/* 002526ec: beq v1,zero,0x00252708 */ {int taken=(c->r[3]==c->r[0]);/* delay 002526f0 */ c->r[2]=c->r[0];if(taken){goto L_00252708;}}
/* 002526f4: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 002526f8: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 002526fc: lw v1,0x60(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000060)));
/* 00252700: ori v1,v1,0x100 */ c->r[3]=c->r[3]|UINT64_C(0x100);
/* 00252704: sw v1,0x60(a0) */ sw((uint32_t)c->r[4]+UINT32_C(0x00000060),(uint32_t)c->r[3]);
L_00252708:;
/* 00252708: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0025270c:;
/* 0025270c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00252710: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00252714: jr ra */ /* delay 00252718 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}
static void body_00252720(BattleCallbackChoiceValues *c){
/* 00252720: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 00252724: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00252728: move s1,a0 */ c->r[17]=c->r[4];
/* 0025272c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00252730: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00252734: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 00252738: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 0025273c: sd ra,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[31]);
/* 00252740: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00252744: lhu v1,0x7c(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x0000007c));
/* 00252748: addiu v1,v1,-0xf0 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffffff10));
/* 0025274c: sltiu v1,v1,0x7 */ c->r[3]=(c->r[3]<sx(UINT32_C(0x00000007)));
/* 00252750: bne v1,zero,0x002529b0 */ {int taken=(c->r[3]!=c->r[0]);/* delay 00252754 */ c->r[2]=c->r[0];if(taken){goto L_002529b0;}}
/* 00252758: lw v1,0x60(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000060)));
/* 0025275c: andi v1,v1,0x1 */ c->r[3]=c->r[3]&UINT64_C(0x1);
/* 00252760: bnel v1,zero,0x002529b4 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252764 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002529b4;}}
/* 00252768: lw a0,0x24(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000024)));
/* 0025276c: lhu v1,0x0(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 00252770: andi v1,v1,0x6 */ c->r[3]=c->r[3]&UINT64_C(0x6);
/* 00252774: bnel v1,zero,0x002529b4 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252778 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002529b4;}}
/* 0025277c: lw v1,0x30(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000030)));
/* 00252780: slti v1,v1,0x4 */ c->r[3]=less(c->r[3],sx(UINT32_C(0x00000004)));
/* 00252784: beql v1,zero,0x002529b4 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00252788 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002529b4;}}
/* 0025278c: jal 0x001e9998 */ c->r[31]=UINT64_C(0x00252794);/* delay 00252790 */ (void)0;nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(evtGetAgeOfMoon());nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252794: li v1,0x8 */ c->r[3]=sx(UINT32_C(0x00000008));
/* 00252798: beql v0,v1,0x002529b0 */ {int taken=(c->r[2]==c->r[3]);if(taken){/* delay 0025279c */ c->r[2]=c->r[0];goto L_002529b0;}}
/* 002527a0: jal 0x002444a8 */ c->r[31]=UINT64_C(0x002527a8);/* delay 002527a4 */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datCheckTalk(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002527a8: beql v0,zero,0x002529b4 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002527ac */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002529b4;}}
/* 002527b0: lw v0,0x2c(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));
/* 002527b4: lh v1,0x6a(v0) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x0000006a)));
/* 002527b8: bltz v1,0x002529ac */ {int taken=(neg(c->r[3]));/* delay 002527bc */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000002)));if(taken){goto L_002529ac;}}
/* 002527c0: bnel v0,zero,0x002527d8 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002527c4 */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));goto L_002527d8;}}
/* 002527c8: li v0,0x5 */ c->r[2]=sx(UINT32_C(0x00000005));
/* 002527cc: bne v1,v0,0x002529b0 */ {int taken=(c->r[3]!=c->r[2]);/* delay 002527d0 */ c->r[2]=c->r[0];if(taken){goto L_002529b0;}}
/* 002527d4: lw a1,0x0(s1) */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
L_002527d8:;
/* 002527d8: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 002527dc: lh v1,0x1a(a1) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x0000001a)));
/* 002527e0: bne v1,a0,0x002529b0 */ {int taken=(c->r[3]!=c->r[4]);/* delay 002527e4 */ c->r[2]=c->r[0];if(taken){goto L_002529b0;}}
/* 002527e8: b 0x00252820 */ /* delay 002527ec */ c->r[19]=sx(UINT32_C(0x00000004));goto L_00252820;
L_002527f0:;
/* 002527f0: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 002527f4: lh a1,0x90(s4) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[20]+UINT32_C(0x00000090)));
/* 002527f8: jal 0x00247ed8 */ c->r[31]=UINT64_C(0x00252800);/* delay 002527fc */ c->r[7]=c->r[0];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbPushAction(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252800: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 00252804: lh a1,0x90(s4) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[20]+UINT32_C(0x00000090)));
/* 00252808: addiu a0,a0,0x38d8 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000038d8));
/* 0025280c: jal 0x002d4748 */ c->r[31]=UINT64_C(0x00252814);/* delay 00252810 */ c->r[6]=hword((uint32_t)c->r[18]+UINT32_C(0x00000004));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,1u,UINT32_C(0x0025280c),UINT32_C(0xf0ff0070));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252814: b 0x002529b0 */ /* delay 00252818 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_002529b0;
L_00252820:;
/* 00252820: sll v0,s3,0x4 */ c->r[2]=sx((uint32_t)c->r[19]<<4u);
/* 00252824: lw v1,0x0(a1) */ c->r[3]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 00252828: subu v0,v0,s3 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[19]);
/* 0025282c: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 00252830: addu s4,v1,v0 */ c->r[20]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00252834: lw v1,0x78(s4) */ c->r[3]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000078)));
/* 00252838: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 0025283c: beq v0,zero,0x0025299c */ {int taken=(c->r[2]==c->r[0]);/* delay 00252840 */ c->r[2]=c->r[3]&UINT64_C(0x8);if(taken){goto L_0025299c;}}
/* 00252844: beq v0,zero,0x0025299c */ {int taken=(c->r[2]==c->r[0]);/* delay 00252848 */ c->r[2]=c->r[3]&UINT64_C(0x40);if(taken){goto L_0025299c;}}
/* 0025284c: beql v0,zero,0x002529a0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00252850 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_002529a0;}}
/* 00252854: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x0025285c);/* delay 00252858 */ c->r[4]=c->r[19];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,2u,UINT32_C(0x00252854),UINT32_C(0xf0ff0010));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 0025285c: lw a1,0x0(s1) */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00252860: move s2,v0 */ c->r[18]=c->r[2];
/* 00252864: lh v0,0x90(s4) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[20]+UINT32_C(0x00000090)));
/* 00252868: lw v1,0x10(a1) */ c->r[3]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000010)));
/* 0025286c: sll v0,v0,0x7 */ c->r[2]=sx((uint32_t)c->r[2]<<7u);
/* 00252870: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00252874: lhu v0,0x0(v0) */ c->r[2]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 00252878: andi v1,v0,0x1 */ c->r[3]=c->r[2]&UINT64_C(0x1);
/* 0025287c: andi v1,v1,0xffff */ c->r[3]=c->r[3]&UINT64_C(0xffff);
/* 00252880: beq v1,zero,0x0025299c */ {int taken=(c->r[3]==c->r[0]);/* delay 00252884 */ c->r[2]=c->r[2]&UINT64_C(0x20);if(taken){goto L_0025299c;}}
/* 00252888: bnel v0,zero,0x002529a0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0025288c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_002529a0;}}
/* 00252890: move a0,s1 */ c->r[4]=c->r[17];
/* 00252894: jal 0x002515e8 */ c->r[31]=UINT64_C(0x0025289c);/* delay 00252898 */ c->r[5]=c->r[19];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 0025289c: bnel v0,zero,0x002529a0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002528a0 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_002529a0;}}
/* 002528a4: lhu a2,0x4(s2) */ c->r[6]=hword((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 002528a8: sll v0,a2,0x1 */ c->r[2]=sx((uint32_t)c->r[6]<<1u);
/* 002528ac: addu v0,v0,a2 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[6]);
/* 002528b0: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 002528b4: lui v1,0x3e */ c->r[3]=sx(UINT32_C(0x003e0000));
/* 002528b8: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 002528bc: lbu v1,-0x34b8(v1) */ c->r[3]=*at((uint32_t)c->r[3]+UINT32_C(0xffffcb48));
/* 002528c0: beq v1,zero,0x0025299c */ {int taken=(c->r[3]==c->r[0]);/* delay 002528c4 */ c->r[16]=sx(UINT32_C(0x02000000));if(taken){goto L_0025299c;}}
/* 002528c8: lw a1,0x0(s1) */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 002528cc: lw v0,0x60(a1) */ c->r[2]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000060)));
/* 002528d0: and v0,v0,s0 */ c->r[2]=c->r[2]&c->r[16];
/* 002528d4: bnel v0,zero,0x00252920 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002528d8 */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));goto L_00252920;}}
/* 002528dc: sll v0,s3,0x3 */ c->r[2]=sx((uint32_t)c->r[19]<<3u);
/* 002528e0: lhu a0,0x8(s2) */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000008));
/* 002528e4: addu v0,v0,s1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[17]);
/* 002528e8: lhu v1,0x8c(v0) */ c->r[3]=hword((uint32_t)c->r[2]+UINT32_C(0x0000008c));
/* 002528ec: beql a0,zero,0x002528f4 */ {int taken=(c->r[4]==c->r[0]);if(taken){/* delay 002528f0 */ nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nocturne_break(7);goto L_002528f4;}}
L_002528f4:;
/* 002528f4: sll v0,v1,0x1 */ c->r[2]=sx((uint32_t)c->r[3]<<1u);
/* 002528f8: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 002528fc: sll v0,v0,0x3 */ c->r[2]=sx((uint32_t)c->r[2]<<3u);
/* 00252900: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00252904: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00252908: div v0,a0 */ {int32_t n=(int32_t)(uint32_t)c->r[2],d=(int32_t)(uint32_t)c->r[4];if(d==0){c->lo=n<0?UINT64_C(1):UINT64_MAX;c->hi=sx((uint32_t)n);}else if(n==INT32_MIN&&d==-1){c->lo=sx(UINT32_C(0x80000000));c->hi=0;}else{c->lo=sx((uint32_t)(n/d));c->hi=sx((uint32_t)(n%d));}}
/* 0025290c: mflo v0 */ c->r[2]=c->lo;
/* 00252910: slti v0,v0,0x19 */ c->r[2]=less(c->r[2],sx(UINT32_C(0x00000019)));
/* 00252914: beql v0,zero,0x002529a0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00252918 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_002529a0;}}
/* 0025291c: lw v1,0x2c(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));
L_00252920:;
/* 00252920: lw v0,0x0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 00252924: andi v0,v0,0x4 */ c->r[2]=c->r[2]&UINT64_C(0x4);
/* 00252928: bne v0,zero,0x0025293c */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025292c */ (void)0;if(taken){goto L_0025293c;}}
/* 00252930: lhu v0,0x4(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 00252934: beql v0,a2,0x002529a0 */ {int taken=(c->r[2]==c->r[6]);if(taken){/* delay 00252938 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_002529a0;}}
L_0025293c:;
/* 0025293c: jal 0x002444a8 */ c->r[31]=UINT64_C(0x00252944);/* delay 00252940 */ c->r[4]=c->r[18];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datCheckTalk(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252944: beql v0,zero,0x002529a0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00252948 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_002529a0;}}
/* 0025294c: lw v0,0x0(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00252950: lw v1,0x60(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000060)));
/* 00252954: and a2,v1,s0 */ c->r[6]=c->r[3]&c->r[16];
/* 00252958: bne a2,zero,0x0025297c */ {int taken=(c->r[6]!=c->r[0]);/* delay 0025295c */ c->r[2]=sx(UINT32_C(0x00000064));if(taken){goto L_0025297c;}}
/* 00252960: lw v0,-0x5750(gp) */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00252964: lhu a0,0x14(s2) */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000014));
/* 00252968: lhu v1,0xa68(v0) */ c->r[3]=hword((uint32_t)c->r[2]+UINT32_C(0x00000a68));
/* 0025296c: sltu v1,v1,a0 */ c->r[3]=(c->r[3]<c->r[4]);
/* 00252970: bnel v1,zero,0x002529a0 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252974 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_002529a0;}}
/* 00252978: li v0,0x64 */ c->r[2]=sx(UINT32_C(0x00000064));
L_0025297c:;
/* 0025297c: li s0,0x6 */ c->r[16]=sx(UINT32_C(0x00000006));
/* 00252980: move a0,zero */ c->r[4]=c->r[0];
/* 00252984: li a1,0x64 */ c->r[5]=sx(UINT32_C(0x00000064));
/* 00252988: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x00252990);/* delay 0025298c */ if(c->r[6]!=0){c->r[16]=c->r[2];}nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]==0?NULL:(uint32_t *)at((uint32_t)c->r[4]),(uint32_t)c->r[5]));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252990: slt v0,v0,s0 */ c->r[2]=less(c->r[2],c->r[16]);
/* 00252994: bnel v0,zero,0x002527f0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252998 */ c->r[6]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000030)));goto L_002527f0;}}
L_0025299c:;
/* 0025299c: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_002529a0:;
/* 002529a0: slti v0,s3,0xe */ c->r[2]=less(c->r[19],sx(UINT32_C(0x0000000e)));
/* 002529a4: bnel v0,zero,0x00252820 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002529a8 */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));goto L_00252820;}}
L_002529ac:;
/* 002529ac: move v0,zero */ c->r[2]=c->r[0];
L_002529b0:;
/* 002529b0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_002529b4:;
/* 002529b4: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002529b8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002529bc: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002529c0: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 002529c4: ld ra,0x28(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 002529c8: jr ra */ /* delay 002529cc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}
static void body_002529d0(BattleCallbackChoiceValues *c){
/* 002529d0: addiu sp,sp,-0x40 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffc0));
/* 002529d4: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002529d8: move s1,a0 */ c->r[17]=c->r[4];
/* 002529dc: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002529e0: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 002529e4: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 002529e8: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 002529ec: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 002529f0: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 002529f4: sd ra,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[31]);
/* 002529f8: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 002529fc: lhu v1,0x7c(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x0000007c));
/* 00252a00: addiu v1,v1,-0xf0 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffffff10));
/* 00252a04: sltiu v1,v1,0x7 */ c->r[3]=(c->r[3]<sx(UINT32_C(0x00000007)));
/* 00252a08: bne v1,zero,0x00252c00 */ {int taken=(c->r[3]!=c->r[0]);/* delay 00252a0c */ c->r[2]=c->r[0];if(taken){goto L_00252c00;}}
/* 00252a10: lw v1,0x60(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000060)));
/* 00252a14: andi v1,v1,0x1 */ c->r[3]=c->r[3]&UINT64_C(0x1);
/* 00252a18: bnel v1,zero,0x00252c04 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252a1c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00252c04;}}
/* 00252a20: lw a0,0x24(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000024)));
/* 00252a24: lhu v1,0x0(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 00252a28: andi v1,v1,0x6 */ c->r[3]=c->r[3]&UINT64_C(0x6);
/* 00252a2c: bnel v1,zero,0x00252c04 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00252a30 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00252c04;}}
/* 00252a34: lw v1,0x30(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000030)));
/* 00252a38: slti v1,v1,0x4 */ c->r[3]=less(c->r[3],sx(UINT32_C(0x00000004)));
/* 00252a3c: beql v1,zero,0x00252c04 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00252a40 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00252c04;}}
/* 00252a44: lw v1,0x4(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000004)));
/* 00252a48: andi v1,v1,0x8 */ c->r[3]=c->r[3]&UINT64_C(0x8);
/* 00252a4c: beql v1,zero,0x00252c04 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00252a50 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00252c04;}}
/* 00252a54: jal 0x001e9998 */ c->r[31]=UINT64_C(0x00252a5c);/* delay 00252a58 */ (void)0;nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(evtGetAgeOfMoon());nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252a5c: li v1,0x8 */ c->r[3]=sx(UINT32_C(0x00000008));
/* 00252a60: beq v0,v1,0x00252bfc */ {int taken=(c->r[2]==c->r[3]);/* delay 00252a64 */ c->r[19]=sx(UINT32_C(0x00000004));if(taken){goto L_00252bfc;}}
/* 00252a68: lw a0,0x2c(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));
/* 00252a6c: li s6,0x64 */ c->r[22]=sx(UINT32_C(0x00000064));
/* 00252a70: jal 0x002444a8 */ c->r[31]=UINT64_C(0x00252a78);/* delay 00252a74 */ c->r[20]=sx(UINT32_C(0x000003c0));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datCheckTalk(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252a78: lui v1,0x3e */ c->r[3]=sx(UINT32_C(0x003e0000));
/* 00252a7c: bne v0,zero,0x00252ad8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00252a80 */ c->r[21]=sx((uint32_t)c->r[3]+UINT32_C(0xffffcb38));if(taken){goto L_00252ad8;}}
/* 00252a84: b 0x00252c04 */ /* delay 00252a88 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00252c04;
L_00252a90:;
/* 00252a90: li a0,0x2 */ c->r[4]=sx(UINT32_C(0x00000002));
/* 00252a94: lh v1,0x90(s2) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[18]+UINT32_C(0x00000090)));
/* 00252a98: move a3,zero */ c->r[7]=c->r[0];
/* 00252a9c: lw a1,0x10(v0) */ c->r[5]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000010)));
/* 00252aa0: sll v1,v1,0x7 */ c->r[3]=sx((uint32_t)c->r[3]<<7u);
/* 00252aa4: lw a2,0x30(s1) */ c->r[6]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000030)));
/* 00252aa8: addu v1,v1,a1 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[5]);
/* 00252aac: lhu v0,0x0(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 00252ab0: ori v0,v0,0x40 */ c->r[2]=c->r[2]|UINT64_C(0x40);
/* 00252ab4: sh v0,0x0(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x00000000),(uint16_t)c->r[2]);
/* 00252ab8: jal 0x00247ed8 */ c->r[31]=UINT64_C(0x00252ac0);/* delay 00252abc */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[18]+UINT32_C(0x00000090)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbPushAction(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252ac0: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 00252ac4: lh a1,0x90(s2) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[18]+UINT32_C(0x00000090)));
/* 00252ac8: jal 0x002d4748 */ c->r[31]=UINT64_C(0x00252ad0);/* delay 00252acc */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000038f0));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,1u,UINT32_C(0x00252ac8),UINT32_C(0xf0ff0030));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252ad0: b 0x00252c00 */ /* delay 00252ad4 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_00252c00;
L_00252ad8:;
/* 00252ad8: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00252adc: lw v0,0x0(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 00252ae0: addu s2,v0,s4 */ c->r[18]=sx((uint32_t)c->r[2]+(uint32_t)c->r[20]);
/* 00252ae4: lw v1,0x78(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000078)));
/* 00252ae8: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 00252aec: beq v0,zero,0x00252bec */ {int taken=(c->r[2]==c->r[0]);/* delay 00252af0 */ c->r[2]=c->r[3]&UINT64_C(0x8);if(taken){goto L_00252bec;}}
/* 00252af4: bnel v0,zero,0x00252bf0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252af8 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252bf0;}}
/* 00252afc: andi v0,v1,0x40 */ c->r[2]=c->r[3]&UINT64_C(0x40);
/* 00252b00: beql v0,zero,0x00252bf0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00252b04 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252bf0;}}
/* 00252b08: lh v0,0x90(s2) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[18]+UINT32_C(0x00000090)));
/* 00252b0c: lw v1,0x10(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000010)));
/* 00252b10: sll v0,v0,0x7 */ c->r[2]=sx((uint32_t)c->r[2]<<7u);
/* 00252b14: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00252b18: lhu a0,0x0(v0) */ c->r[4]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 00252b1c: andi v1,a0,0x1 */ c->r[3]=c->r[4]&UINT64_C(0x1);
/* 00252b20: andi v1,v1,0xffff */ c->r[3]=c->r[3]&UINT64_C(0xffff);
/* 00252b24: beq v1,zero,0x00252bec */ {int taken=(c->r[3]==c->r[0]);/* delay 00252b28 */ c->r[2]=c->r[4]&UINT64_C(0x20);if(taken){goto L_00252bec;}}
/* 00252b2c: bnel v0,zero,0x00252bf0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252b30 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252bf0;}}
/* 00252b34: andi v0,a0,0x40 */ c->r[2]=c->r[4]&UINT64_C(0x40);
/* 00252b38: bnel v0,zero,0x00252bf0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252b3c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252bf0;}}
/* 00252b40: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x00252b48);/* delay 00252b44 */ c->r[4]=c->r[19];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,2u,UINT32_C(0x00252b40),UINT32_C(0xf0ff0010));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252b48: move a0,s1 */ c->r[4]=c->r[17];
/* 00252b4c: move a1,s3 */ c->r[5]=c->r[19];
/* 00252b50: jal 0x002515e8 */ c->r[31]=UINT64_C(0x00252b58);/* delay 00252b54 */ c->r[16]=c->r[2];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252b58: bnel v0,zero,0x00252bf0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252b5c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252bf0;}}
/* 00252b60: lhu a0,0x4(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000004));
/* 00252b64: sll v0,a0,0x1 */ c->r[2]=sx((uint32_t)c->r[4]<<1u);
/* 00252b68: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 00252b6c: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 00252b70: addu v0,v0,s5 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[21]);
/* 00252b74: lbu v1,0x11(v0) */ c->r[3]=*at((uint32_t)c->r[2]+UINT32_C(0x00000011));
/* 00252b78: beql v1,zero,0x00252bf0 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00252b7c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252bf0;}}
/* 00252b80: lw v1,0x2c(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));
/* 00252b84: lw v0,0x0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 00252b88: andi v0,v0,0x4 */ c->r[2]=c->r[2]&UINT64_C(0x4);
/* 00252b8c: bne v0,zero,0x00252ba0 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00252b90 */ (void)0;if(taken){goto L_00252ba0;}}
/* 00252b94: lhu v0,0x4(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 00252b98: beql v0,a0,0x00252bf0 */ {int taken=(c->r[2]==c->r[4]);if(taken){/* delay 00252b9c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252bf0;}}
L_00252ba0:;
/* 00252ba0: jal 0x00244530 */ c->r[31]=UINT64_C(0x00252ba8);/* delay 00252ba4 */ (void)0;nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datSearchDevilStock(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252ba8: bgezl v0,0x00252bf0 */ {int taken=(!neg(c->r[2]));if(taken){/* delay 00252bac */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252bf0;}}
/* 00252bb0: jal 0x002444a8 */ c->r[31]=UINT64_C(0x00252bb8);/* delay 00252bb4 */ c->r[4]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datCheckTalk(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252bb8: beq v0,zero,0x00252bec */ {int taken=(c->r[2]==c->r[0]);/* delay 00252bbc */ c->r[6]=sx(UINT32_C(0x02000000));if(taken){goto L_00252bec;}}
/* 00252bc0: lw v1,0x0(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00252bc4: li s0,0x2 */ c->r[16]=sx(UINT32_C(0x00000002));
/* 00252bc8: move a0,zero */ c->r[4]=c->r[0];
/* 00252bcc: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 00252bd0: li a1,0x64 */ c->r[5]=sx(UINT32_C(0x00000064));
/* 00252bd4: and v0,v0,a2 */ c->r[2]=c->r[2]&c->r[6];
/* 00252bd8: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x00252be0);/* delay 00252bdc */ if(c->r[2]!=0){c->r[16]=c->r[22];}nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]==0?NULL:(uint32_t *)at((uint32_t)c->r[4]),(uint32_t)c->r[5]));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00252be0: slt v0,v0,s0 */ c->r[2]=less(c->r[2],c->r[16]);
/* 00252be4: bnel v0,zero,0x00252a90 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252be8 */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));goto L_00252a90;}}
L_00252bec:;
/* 00252bec: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_00252bf0:;
/* 00252bf0: slti v0,s3,0xe */ c->r[2]=less(c->r[19],sx(UINT32_C(0x0000000e)));
/* 00252bf4: bne v0,zero,0x00252ad8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00252bf8 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x000000f0));if(taken){goto L_00252ad8;}}
L_00252bfc:;
/* 00252bfc: move v0,zero */ c->r[2]=c->r[0];
L_00252c00:;
/* 00252c00: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00252c04:;
/* 00252c04: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00252c08: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00252c0c: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00252c10: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00252c14: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 00252c18: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 00252c1c: ld ra,0x38(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 00252c20: jr ra */ /* delay 00252c24 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000040));return;
}
static void body_002532a8(BattleCallbackChoiceValues *c){
/* 002532a8: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 002532ac: sd s1,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[17]);
/* 002532b0: move s1,a0 */ c->r[17]=c->r[4];
/* 002532b4: sd s2,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[18]);
/* 002532b8: sd s3,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[19]);
/* 002532bc: sd s0,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[16]);
/* 002532c0: sd ra,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);
/* 002532c4: jal 0x00251890 */ c->r[31]=UINT64_C(0x002532cc);/* delay 002532c8 */ c->r[18]=c->r[5];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetAllUnlockTime(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002532cc: move s3,v0 */ c->r[19]=c->r[2];
/* 002532d0: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 002532d4: jal 0x0026a2d8 */ c->r[31]=UINT64_C(0x002532dc);/* delay 002532d8 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbCheckKuisibariSkill(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002532dc: beq v0,zero,0x00253338 */ {int taken=(c->r[2]==c->r[0]);/* delay 002532e0 */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));if(taken){goto L_00253338;}}
/* 002532e4: blez s2,0x00253398 */ {int taken=((neg(c->r[18])||!c->r[18]));/* delay 002532e8 */ (void)0;if(taken){goto L_00253398;}}
/* 002532ec: move a0,s1 */ c->r[4]=c->r[17];
/* 002532f0: jal 0x002515d8 */ c->r[31]=UINT64_C(0x002532f8);/* delay 002532f4 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetTimeListHp(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002532f8: slt v0,s2,v0 */ c->r[2]=less(c->r[18],c->r[2]);
/* 002532fc: bne v0,zero,0x00253398 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00253300 */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));if(taken){goto L_00253398;}}
/* 00253304: move a0,s1 */ c->r[4]=c->r[17];
/* 00253308: jal 0x002515d8 */ c->r[31]=UINT64_C(0x00253310);/* delay 0025330c */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetTimeListHp(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253310: move a0,s3 */ c->r[4]=c->r[19];
/* 00253314: move a1,s1 */ c->r[5]=c->r[17];
/* 00253318: li a2,0x159 */ c->r[6]=sx(UINT32_C(0x00000159));
/* 0025331c: jal 0x00262f58 */ c->r[31]=UINT64_C(0x00253324);/* delay 00253320 */ c->r[18]=sx((uint32_t)c->r[2]+UINT32_C(0xffffffff));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddSkillNamePacket(c->r[4],c->r[5],c->r[6]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253324: lw v1,0x28(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 00253328: jal 0x0026a398 */ c->r[31]=UINT64_C(0x00253330);/* delay 0025332c */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbSetKuisibariStop(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253330: b 0x00253398 */ /* delay 00253334 */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));goto L_00253398;
L_00253338:;
/* 00253338: jal 0x0026a338 */ c->r[31]=UINT64_C(0x00253340);/* delay 0025333c */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbCheckKuisibari2Skill(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253340: beq v0,zero,0x00253398 */ {int taken=(c->r[2]==c->r[0]);/* delay 00253344 */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));if(taken){goto L_00253398;}}
/* 00253348: blez s2,0x00253398 */ {int taken=((neg(c->r[18])||!c->r[18]));/* delay 0025334c */ (void)0;if(taken){goto L_00253398;}}
/* 00253350: move a0,s1 */ c->r[4]=c->r[17];
/* 00253354: jal 0x002515d8 */ c->r[31]=UINT64_C(0x0025335c);/* delay 00253358 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetTimeListHp(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 0025335c: slt v0,s2,v0 */ c->r[2]=less(c->r[18],c->r[2]);
/* 00253360: bne v0,zero,0x00253398 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00253364 */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));if(taken){goto L_00253398;}}
/* 00253368: move a0,s1 */ c->r[4]=c->r[17];
/* 0025336c: jal 0x002515d8 */ c->r[31]=UINT64_C(0x00253374);/* delay 00253370 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetTimeListHp(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253374: move a0,s3 */ c->r[4]=c->r[19];
/* 00253378: move a1,s1 */ c->r[5]=c->r[17];
/* 0025337c: li a2,0x168 */ c->r[6]=sx(UINT32_C(0x00000168));
/* 00253380: jal 0x00262f58 */ c->r[31]=UINT64_C(0x00253388);/* delay 00253384 */ c->r[18]=sx((uint32_t)c->r[2]+UINT32_C(0xffffffff));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddSkillNamePacket(c->r[4],c->r[5],c->r[6]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253388: lw v1,0x28(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 0025338c: jal 0x0026a398 */ c->r[31]=UINT64_C(0x00253394);/* delay 00253390 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbSetKuisibariStop(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253394: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
L_00253398:;
/* 00253398: subu a2,zero,s2 */ c->r[6]=sx((uint32_t)c->r[0]-(uint32_t)c->r[18]);
/* 0025339c: move a0,s1 */ c->r[4]=c->r[17];
/* 002533a0: jal 0x002516e8 */ c->r[31]=UINT64_C(0x002533a8);/* delay 002533a4 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionAddTimeListHp(c->r[4],c->r[5],c->r[6]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002533a8: lw v1,0x28(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 002533ac: move a0,s1 */ c->r[4]=c->r[17];
/* 002533b0: jal 0x002515e8 */ c->r[31]=UINT64_C(0x002533b8);/* delay 002533b4 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002533b8: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 002533bc: lw a2,0x28(s1) */ c->r[6]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 002533c0: sltu s0,zero,v0 */ c->r[16]=(c->r[0]<c->r[2]);
/* 002533c4: move t0,s2 */ c->r[8]=c->r[18];
/* 002533c8: move a0,s3 */ c->r[4]=c->r[19];
/* 002533cc: move a1,s1 */ c->r[5]=c->r[17];
/* 002533d0: li a3,0x3 */ c->r[7]=sx(UINT32_C(0x00000003));
/* 002533d4: li t1,-0x1 */ c->r[9]=sx(UINT32_C(0xffffffff));
/* 002533d8: move t2,zero */ c->r[10]=c->r[0];
/* 002533dc: move t3,zero */ c->r[11]=c->r[0];
/* 002533e0: sw v1,0x10(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000010),(uint32_t)c->r[3]);
/* 002533e4: sw s0,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[16]);
/* 002533e8: sw zero,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),(uint32_t)c->r[0]);
/* 002533ec: jal 0x00263c00 */ c->r[31]=UINT64_C(0x002533f4);/* delay 002533f0 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000018),(uint32_t)c->r[0]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleAction_00263C00(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8],c->r[9],c->r[10],c->r[11],word((uint32_t)c->r[29]),word((uint32_t)c->r[29]+8u),word((uint32_t)c->r[29]+16u),word((uint32_t)c->r[29]+24u));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002533f4: beq s0,zero,0x00253458 */ {int taken=(c->r[16]==c->r[0]);/* delay 002533f8 */ c->r[6]=c->r[19];if(taken){goto L_00253458;}}
/* 002533fc: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 00253400: li a3,0x1e */ c->r[7]=sx(UINT32_C(0x0000001e));
/* 00253404: li t0,0x1e */ c->r[8]=sx(UINT32_C(0x0000001e));
/* 00253408: lh a1,0x92(v0) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));
/* 0025340c: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00253414);/* delay 00253410 */ c->r[4]=c->r[17];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253414: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 00253418: move a0,s1 */ c->r[4]=c->r[17];
/* 0025341c: jal 0x0024f478 */ c->r[31]=UINT64_C(0x00253424);/* delay 00253420 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_0024F478(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253424: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 00253428: move a0,s1 */ c->r[4]=c->r[17];
/* 0025342c: ld s1,0x28(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 00253430: move a2,s3 */ c->r[6]=c->r[19];
/* 00253434: ld s3,0x38(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 00253438: lh a1,0x92(v0) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));
/* 0025343c: li a3,0x14 */ c->r[7]=sx(UINT32_C(0x00000014));
/* 00253440: ld s0,0x20(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00253444: li t0,0x14 */ c->r[8]=sx(UINT32_C(0x00000014));
/* 00253448: ld s2,0x30(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0025344c: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 00253450: j 0x002517e0 */ /* delay 00253454 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);return;
L_00253458:;
/* 00253458: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 0025345c: move a0,s1 */ c->r[4]=c->r[17];
/* 00253460: ld s3,0x38(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 00253464: lh a1,0x92(v0) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));
/* 00253468: li a3,0x1e */ c->r[7]=sx(UINT32_C(0x0000001e));
/* 0025346c: ld s0,0x20(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00253470: li t0,0x1e */ c->r[8]=sx(UINT32_C(0x0000001e));
/* 00253474: ld s1,0x28(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 00253478: ld s2,0x30(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0025347c: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 00253480: j 0x002517e0 */ /* delay 00253484 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);return;
}
static void body_00253490(BattleCallbackChoiceValues *c){
/* 00253490: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00253494: li a1,-0x4001 */ c->r[5]=sx(UINT32_C(0xffffbfff));
/* 00253498: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025349c: move s0,a0 */ c->r[16]=c->r[4];
/* 002534a0: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 002534a4: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 002534a8: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 002534ac: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 002534b0: sw zero,0x94(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000094),(uint32_t)c->r[0]);
/* 002534b4: and v0,v0,a1 */ c->r[2]=c->r[2]&c->r[5];
/* 002534b8: sh zero,0x90(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x00000090),(uint16_t)c->r[0]);
/* 002534bc: sw v0,0x60(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000060),(uint32_t)c->r[2]);
/* 002534c0: jal 0x00245c90 */ c->r[31]=UINT64_C(0x002534c8);/* delay 002534c4 */ sh((uint32_t)c->r[3]+UINT32_C(0x00000092),(uint16_t)c->r[0]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=datGetItemSkillNo(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002534c8: lw a1,0x28(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 002534cc: lw a0,0x24(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));
/* 002534d0: sh zero,0xa4(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x000000a4),(uint16_t)c->r[0]);
/* 002534d4: sw v0,0x64(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000064),(uint32_t)c->r[2]);
/* 002534d8: lhu v0,0x0(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 002534dc: andi v0,v0,0xfeff */ c->r[2]=c->r[2]&UINT64_C(0xfeff);
/* 002534e0: andi v1,v0,0x8 */ c->r[3]=c->r[2]&UINT64_C(0x8);
/* 002534e4: beq v1,zero,0x002534f8 */ {int taken=(c->r[3]==c->r[0]);/* delay 002534e8 */ sh((uint32_t)c->r[4]+UINT32_C(0x00000000),(uint16_t)c->r[2]);if(taken){goto L_002534f8;}}
/* 002534ec: move a0,s0 */ c->r[4]=c->r[16];
/* 002534f0: b 0x00253814 */ /* delay 002534f4 */ c->r[5]=sx(UINT32_C(0x0000000f));goto L_00253814;
L_002534f8:;
/* 002534f8: lw v0,0x34(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000034)));
/* 002534fc: addiu v0,v0,-0x1 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffffff));
/* 00253500: sltiu v1,v0,0x5 */ c->r[3]=(c->r[2]<sx(UINT32_C(0x00000005)));
/* 00253504: beql v1,zero,0x00253648 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00253508 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000092)));goto L_00253648;}}
/* 0025350c: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00253510: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 00253514: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00253518: lw v1,0x39e0(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x000039e0)));
/* 0025351c: jr v1 */ {uint64_t target=c->r[3];/* delay 00253520 */ (void)0;switch(target){case UINT64_C(0x00253528):goto L_00253528;case UINT64_C(0x00253568):goto L_00253568;case UINT64_C(0x002535b0):goto L_002535b0;case UINT64_C(0x002535f0):goto L_002535f0;case UINT64_C(0x00253638):goto L_00253638;default:abort();}}
L_00253528:;
/* 00253528: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0025352c: li a2,0x4 */ c->r[6]=sx(UINT32_C(0x00000004));
/* 00253530: li v0,0x182 */ c->r[2]=sx(UINT32_C(0x00000182));
/* 00253534: li a1,0x4 */ c->r[5]=sx(UINT32_C(0x00000004));
/* 00253538: sh v0,0x6c(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006c),(uint16_t)c->r[2]);
/* 0025353c: move a0,s0 */ c->r[4]=c->r[16];
/* 00253540: sh a2,0x6a(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006a),(uint16_t)c->r[6]);
/* 00253544: sw a1,0x68(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000068),(uint32_t)c->r[5]);
/* 00253548: jal 0x00251fd8 */ c->r[31]=UINT64_C(0x00253550);/* delay 0025354c */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000038)));body_00251fd8(c);
/* 00253550: jal 0x00246b68 */ c->r[31]=UINT64_C(0x00253558);/* delay 00253554 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetSelectBit(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253558: move a0,s0 */ c->r[4]=c->r[16];
/* 0025355c: sw v0,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[2]);
/* 00253560: b 0x00253814 */ /* delay 00253564 */ c->r[5]=sx(UINT32_C(0x00000007));goto L_00253814;
L_00253568:;
/* 00253568: lw a2,0x2c(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0025356c: li v0,0x4 */ c->r[2]=sx(UINT32_C(0x00000004));
/* 00253570: lw a1,0x0(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00253574: li v1,0x3 */ c->r[3]=sx(UINT32_C(0x00000003));
/* 00253578: sh v0,0x6a(a2) */ sh((uint32_t)c->r[6]+UINT32_C(0x0000006a),(uint16_t)c->r[2]);
/* 0025357c: move a0,s0 */ c->r[4]=c->r[16];
/* 00253580: sw v1,0x68(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000068),(uint32_t)c->r[3]);
/* 00253584: lhu v0,0x5a(a1) */ c->r[2]=hword((uint32_t)c->r[5]+UINT32_C(0x0000005a));
/* 00253588: lw a1,0x38(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000038)));
/* 0025358c: jal 0x00251fd8 */ c->r[31]=UINT64_C(0x00253594);/* delay 00253590 */ sh((uint32_t)c->r[6]+UINT32_C(0x0000006c),(uint16_t)c->r[2]);body_00251fd8(c);
/* 00253594: jal 0x00246b68 */ c->r[31]=UINT64_C(0x0025359c);/* delay 00253598 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetSelectBit(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 0025359c: move a0,s0 */ c->r[4]=c->r[16];
/* 002535a0: sw v0,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[2]);
/* 002535a4: b 0x00253814 */ /* delay 002535a8 */ c->r[5]=sx(UINT32_C(0x00000007));goto L_00253814;
L_002535b0:;
/* 002535b0: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 002535b4: li a2,0x4 */ c->r[6]=sx(UINT32_C(0x00000004));
/* 002535b8: li v0,0x182 */ c->r[2]=sx(UINT32_C(0x00000182));
/* 002535bc: li a1,0x5 */ c->r[5]=sx(UINT32_C(0x00000005));
/* 002535c0: sh v0,0x6c(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006c),(uint16_t)c->r[2]);
/* 002535c4: move a0,s0 */ c->r[4]=c->r[16];
/* 002535c8: sh a2,0x6a(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006a),(uint16_t)c->r[6]);
/* 002535cc: sw a1,0x68(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000068),(uint32_t)c->r[5]);
/* 002535d0: jal 0x00251fd8 */ c->r[31]=UINT64_C(0x002535d8);/* delay 002535d4 */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000038)));body_00251fd8(c);
/* 002535d8: jal 0x00246b68 */ c->r[31]=UINT64_C(0x002535e0);/* delay 002535dc */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetSelectBit(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002535e0: move a0,s0 */ c->r[4]=c->r[16];
/* 002535e4: sw v0,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[2]);
/* 002535e8: b 0x00253814 */ /* delay 002535ec */ c->r[5]=sx(UINT32_C(0x00000007));goto L_00253814;
L_002535f0:;
/* 002535f0: lw a1,0x2c(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 002535f4: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 002535f8: lhu v1,0x54(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x00000054));
/* 002535fc: move a0,s0 */ c->r[4]=c->r[16];
/* 00253600: sh v0,0x6a(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x0000006a),(uint16_t)c->r[2]);
/* 00253604: sh v1,0x6c(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x0000006c),(uint16_t)c->r[3]);
/* 00253608: jal 0x00251fd8 */ c->r[31]=UINT64_C(0x00253610);/* delay 0025360c */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000038)));body_00251fd8(c);
/* 00253610: jal 0x00246b68 */ c->r[31]=UINT64_C(0x00253618);/* delay 00253614 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetSelectBit(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253618: lw v1,0x4(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 0025361c: sw v0,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[2]);
/* 00253620: move a0,s0 */ c->r[4]=c->r[16];
/* 00253624: ori v1,v1,0x4 */ c->r[3]=c->r[3]|UINT64_C(0x4);
/* 00253628: li a1,0x7 */ c->r[5]=sx(UINT32_C(0x00000007));
/* 0025362c: b 0x00253814 */ /* delay 00253630 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[3]);goto L_00253814;
L_00253638:;
/* 00253638: move a0,s0 */ c->r[4]=c->r[16];
/* 0025363c: b 0x00253814 */ /* delay 00253640 */ c->r[5]=sx(UINT32_C(0x00000013));goto L_00253814;
L_00253648:;
/* 00253648: li a1,0x11 */ c->r[5]=sx(UINT32_C(0x00000011));
/* 0025364c: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 00253650: jal 0x00267f58 */ c->r[31]=UINT64_C(0x00253658);/* delay 00253654 */ c->r[7]=c->r[0];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbSetHojoAddCounter(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253658: lw v1,0x28(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0025365c: li a1,0x12 */ c->r[5]=sx(UINT32_C(0x00000012));
/* 00253660: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 00253664: lh a0,0x92(v1) */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));
/* 00253668: jal 0x00267f58 */ c->r[31]=UINT64_C(0x00253670);/* delay 0025366c */ c->r[7]=c->r[0];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbSetHojoAddCounter(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253670: lw v1,0x28(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00253674: jal 0x00267788 */ c->r[31]=UINT64_C(0x0025367c);/* delay 00253678 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetBadStat(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 0025367c: move v1,v0 */ c->r[3]=c->r[2];
/* 00253680: li v0,0x4 */ c->r[2]=sx(UINT32_C(0x00000004));
/* 00253684: beq v1,v0,0x002536e0 */ {int taken=(c->r[3]==c->r[2]);/* delay 00253688 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000005)));if(taken){goto L_002536e0;}}
/* 0025368c: beq v0,zero,0x002536b0 */ {int taken=(c->r[2]==c->r[0]);/* delay 00253690 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_002536b0;}}
/* 00253694: sltiu v0,v1,0x3 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000003)));
/* 00253698: beql v0,zero,0x002536f0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0025369c */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));goto L_002536f0;}}
/* 002536a0: beql v1,zero,0x002536f0 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 002536a4 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));goto L_002536f0;}}
/* 002536a8: b 0x002536e4 */ /* delay 002536ac */ c->r[4]=c->r[16];goto L_002536e4;
L_002536b0:;
/* 002536b0: beq v1,v0,0x002536e0 */ {int taken=(c->r[3]==c->r[2]);/* delay 002536b4 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000081)));if(taken){goto L_002536e0;}}
/* 002536b8: beq v0,zero,0x002536d8 */ {int taken=(c->r[2]==c->r[0]);/* delay 002536bc */ c->r[2]=sx(UINT32_C(0x00000400));if(taken){goto L_002536d8;}}
/* 002536c0: li v0,0x10 */ c->r[2]=sx(UINT32_C(0x00000010));
/* 002536c4: beq v1,v0,0x002536e4 */ {int taken=(c->r[3]==c->r[2]);/* delay 002536c8 */ c->r[4]=c->r[16];if(taken){goto L_002536e4;}}
/* 002536cc: b 0x002536f0 */ /* delay 002536d0 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));goto L_002536f0;
L_002536d8:;
/* 002536d8: bnel v1,v0,0x002536f0 */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 002536dc */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));goto L_002536f0;}}
L_002536e0:;
/* 002536e0: move a0,s0 */ c->r[4]=c->r[16];
L_002536e4:;
/* 002536e4: b 0x00253814 */ /* delay 002536e8 */ c->r[5]=sx(UINT32_C(0x00000004));goto L_00253814;
L_002536f0:;
/* 002536f0: lhu v0,0x0(v0) */ c->r[2]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 002536f4: andi v1,v0,0x2 */ c->r[3]=c->r[2]&UINT64_C(0x2);
/* 002536f8: beq v1,zero,0x00253800 */ {int taken=(c->r[3]==c->r[0]);/* delay 002536fc */ c->r[2]=c->r[2]&UINT64_C(0x4);if(taken){goto L_00253800;}}
/* 00253700: jal 0x00252400 */ c->r[31]=UINT64_C(0x00253708);/* delay 00253704 */ c->r[4]=c->r[16];body_00252400(c);
/* 00253708: beq v0,zero,0x00253748 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025370c */ c->r[6]=sx(UINT32_C(0x00000004));if(taken){goto L_00253748;}}
/* 00253710: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 00253714: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
/* 00253718: li v0,0x182 */ c->r[2]=sx(UINT32_C(0x00000182));
/* 0025371c: sh v0,0x6c(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006c),(uint16_t)c->r[2]);
/* 00253720: move a0,s0 */ c->r[4]=c->r[16];
/* 00253724: sh a2,0x6a(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006a),(uint16_t)c->r[6]);
/* 00253728: jal 0x00251ef0 */ c->r[31]=UINT64_C(0x00253730);/* delay 0025372c */ sw((uint32_t)c->r[16]+UINT32_C(0x00000068),(uint32_t)c->r[5]);body_00251ef0(c);
/* 00253730: jal 0x00246b68 */ c->r[31]=UINT64_C(0x00253738);/* delay 00253734 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetSelectBit(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253738: move a0,s0 */ c->r[4]=c->r[16];
/* 0025373c: sw v0,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[2]);
/* 00253740: b 0x00253814 */ /* delay 00253744 */ c->r[5]=sx(UINT32_C(0x00000007));goto L_00253814;
L_00253748:;
/* 00253748: jal 0x002525f0 */ c->r[31]=UINT64_C(0x00253750);/* delay 0025374c */ c->r[4]=c->r[16];body_002525f0(c);
/* 00253750: beq v0,zero,0x00253790 */ {int taken=(c->r[2]==c->r[0]);/* delay 00253754 */ c->r[6]=sx(UINT32_C(0x00000004));if(taken){goto L_00253790;}}
/* 00253758: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0025375c: li a1,0x2 */ c->r[5]=sx(UINT32_C(0x00000002));
/* 00253760: li v0,0x182 */ c->r[2]=sx(UINT32_C(0x00000182));
/* 00253764: sh v0,0x6c(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006c),(uint16_t)c->r[2]);
/* 00253768: move a0,s0 */ c->r[4]=c->r[16];
/* 0025376c: sh a2,0x6a(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006a),(uint16_t)c->r[6]);
/* 00253770: jal 0x00251ef0 */ c->r[31]=UINT64_C(0x00253778);/* delay 00253774 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000068),(uint32_t)c->r[5]);body_00251ef0(c);
/* 00253778: jal 0x00246b68 */ c->r[31]=UINT64_C(0x00253780);/* delay 0025377c */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetSelectBit(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00253780: move a0,s0 */ c->r[4]=c->r[16];
/* 00253784: sw v0,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[2]);
/* 00253788: b 0x00253814 */ /* delay 0025378c */ c->r[5]=sx(UINT32_C(0x00000007));goto L_00253814;
L_00253790:;
/* 00253790: lw v1,-0x594c(gp) */ c->r[3]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa6b4)));
/* 00253794: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00253798: bnel v1,v0,0x002537bc */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 0025379c */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));goto L_002537bc;}}
/* 002537a0: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 002537a4: lui a0,0x1000 */ c->r[4]=sx(UINT32_C(0x10000000));
/* 002537a8: lw v1,0x60(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000060)));
/* 002537ac: and v1,v1,a0 */ c->r[3]=c->r[3]&c->r[4];
/* 002537b0: bne v1,zero,0x00253810 */ {int taken=(c->r[3]!=c->r[0]);/* delay 002537b4 */ c->r[4]=c->r[16];if(taken){goto L_00253810;}}
/* 002537b8: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
L_002537bc:;
/* 002537bc: lhu a0,0x4(v1) */ c->r[4]=hword((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 002537c0: sll v0,a0,0x2 */ c->r[2]=sx((uint32_t)c->r[4]<<2u);
/* 002537c4: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 002537c8: sll v0,v0,0x3 */ c->r[2]=sx((uint32_t)c->r[2]<<3u);
/* 002537cc: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 002537d0: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 002537d4: lui v1,0x3a */ c->r[3]=sx(UINT32_C(0x003a0000));
/* 002537d8: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 002537dc: lhu v1,-0x7620(v1) */ c->r[3]=hword((uint32_t)c->r[3]+UINT32_C(0xffff89e0));
/* 002537e0: beq v1,zero,0x002537f0 */ {int taken=(c->r[3]==c->r[0]);/* delay 002537e4 */ c->r[4]=c->r[16];if(taken){goto L_002537f0;}}
/* 002537e8: b 0x00253814 */ /* delay 002537ec */ c->r[5]=sx(UINT32_C(0x00000003));goto L_00253814;
L_002537f0:;
/* 002537f0: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x002537f8);/* delay 002537f4 */ c->r[5]=sx(UINT32_C(0x00000002));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002537f8: b 0x00253820 */ /* delay 002537fc */ c->r[2]=sx(UINT32_C(0x00000001));goto L_00253820;
L_00253800:;
/* 00253800: beq v0,zero,0x00253810 */ {int taken=(c->r[2]==c->r[0]);/* delay 00253804 */ c->r[4]=c->r[16];if(taken){goto L_00253810;}}
/* 00253808: b 0x00253814 */ /* delay 0025380c */ c->r[5]=sx(UINT32_C(0x00000015));goto L_00253814;
L_00253810:;
/* 00253810: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
L_00253814:;
/* 00253814: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x0025381c);/* delay 00253818 */ (void)0;nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 0025381c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_00253820:;
/* 00253820: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00253824: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00253828: jr ra */ /* delay 0025382c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}
static void body_00257488(BattleCallbackChoiceValues *c){
/* 00257488: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 0025748c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00257490: move s0,a0 */ c->r[16]=c->r[4];
/* 00257494: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00257498: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0025749c: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 002574a0: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 002574a4: sd ra,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[31]);
/* 002574a8: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 002574ac: jal 0x002515e8 */ c->r[31]=UINT64_C(0x002574b4);/* delay 002574b0 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002574b4: bnel v0,zero,0x00257540 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002574b8 */ c->r[4]=c->r[16];goto L_00257540;}}
/* 002574bc: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 002574c0: jal 0x00267788 */ c->r[31]=UINT64_C(0x002574c8);/* delay 002574c4 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetBadStat(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002574c8: li v1,0x40 */ c->r[3]=sx(UINT32_C(0x00000040));
/* 002574cc: bne v0,v1,0x00257540 */ {int taken=(c->r[2]!=c->r[3]);/* delay 002574d0 */ c->r[4]=c->r[16];if(taken){goto L_00257540;}}
/* 002574d4: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 002574d8: jal 0x00251628 */ c->r[31]=UINT64_C(0x002574e0);/* delay 002574dc */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDeadEnemyParty(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002574e0: bne v0,zero,0x00257540 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002574e4 */ c->r[4]=c->r[16];if(taken){goto L_00257540;}}
/* 002574e8: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 002574ec: lw v1,0x44(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000044)));
/* 002574f0: bne v1,zero,0x00257540 */ {int taken=(c->r[3]!=c->r[0]);/* delay 002574f4 */ c->r[3]=sx(UINT32_C(0x00000005));if(taken){goto L_00257540;}}
/* 002574f8: lw a0,0x2c(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 002574fc: lh v0,0x6a(a0) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x0000006a)));
/* 00257500: bnel v0,v1,0x0025751c */ {int taken=(c->r[2]!=c->r[3]);if(taken){/* delay 00257504 */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));goto L_0025751c;}}
/* 00257508: lhu v1,0x6c(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x0000006c));
/* 0025750c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00257510: beql v1,v0,0x00257540 */ {int taken=(c->r[3]==c->r[2]);if(taken){/* delay 00257514 */ c->r[4]=c->r[16];goto L_00257540;}}
/* 00257518: lw v1,0x24(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));
L_0025751c:;
/* 0025751c: lhu v0,0x0(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 00257520: andi v0,v0,0x20 */ c->r[2]=c->r[2]&UINT64_C(0x20);
/* 00257524: bnel v0,zero,0x00257540 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00257528 */ c->r[4]=c->r[16];goto L_00257540;}}
/* 0025752c: lhu a1,0x8(a0) */ c->r[5]=hword((uint32_t)c->r[4]+UINT32_C(0x00000008));
/* 00257530: move a0,s0 */ c->r[4]=c->r[16];
/* 00257534: jal 0x002532a8 */ c->r[31]=UINT64_C(0x0025753c);/* delay 00257538 */ c->r[5]=sx((uint32_t)c->r[5]>>3u);body_002532a8(c);
/* 0025753c: move a0,s0 */ c->r[4]=c->r[16];
L_00257540:;
/* 00257540: jal 0x00251890 */ c->r[31]=UINT64_C(0x00257548);/* delay 00257544 */ c->r[17]=c->r[0];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetAllUnlockTime(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257548: lui s4,0x54 */ c->r[20]=sx(UINT32_C(0x00540000));
/* 0025754c: move s3,v0 */ c->r[19]=c->r[2];
/* 00257550: move s2,zero */ c->r[18]=c->r[0];
/* 00257554: nop  */ (void)0;
L_00257558:;
/* 00257558: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0025755c: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 00257560: addu v1,s2,v1 */ c->r[3]=sx((uint32_t)c->r[18]+(uint32_t)c->r[3]);
/* 00257564: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 00257568: andi v1,v0,0x40 */ c->r[3]=c->r[2]&UINT64_C(0x40);
/* 0025756c: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 00257570: beql v0,zero,0x00257628 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00257574 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_00257628;}}
/* 00257578: beq v1,zero,0x00257624 */ {int taken=(c->r[3]==c->r[0]);/* delay 0025757c */ c->r[5]=c->r[17];if(taken){goto L_00257624;}}
/* 00257580: jal 0x002515e8 */ c->r[31]=UINT64_C(0x00257588);/* delay 00257584 */ c->r[4]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257588: beql v0,zero,0x00257628 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0025758c */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_00257628;}}
/* 00257590: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00257594: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 00257598: lw a0,0x10(v0) */ c->r[4]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000010)));
/* 0025759c: addu v1,s2,v1 */ c->r[3]=sx((uint32_t)c->r[18]+(uint32_t)c->r[3]);
/* 002575a0: lh v0,0x90(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000090)));
/* 002575a4: sll v0,v0,0x7 */ c->r[2]=sx((uint32_t)c->r[2]<<7u);
/* 002575a8: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 002575ac: lhu v1,0x0(v0) */ c->r[3]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 002575b0: andi v1,v1,0x20 */ c->r[3]=c->r[3]&UINT64_C(0x20);
/* 002575b4: bnel v1,zero,0x00257628 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 002575b8 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_00257628;}}
/* 002575bc: move a1,s1 */ c->r[5]=c->r[17];
/* 002575c0: jal 0x002d4748 */ c->r[31]=UINT64_C(0x002575c8);/* delay 002575c4 */ c->r[4]=sx((uint32_t)c->r[20]+UINT32_C(0x00004030));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,1u,UINT32_C(0x002575c0),UINT32_C(0xf0ff0030));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002575c8: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 002575cc: move a3,zero */ c->r[7]=c->r[0];
/* 002575d0: li t0,0x1 */ c->r[8]=sx(UINT32_C(0x00000001));
/* 002575d4: lw a2,0x0(v1) */ c->r[6]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 002575d8: move a0,s3 */ c->r[4]=c->r[19];
/* 002575dc: move a1,s0 */ c->r[5]=c->r[16];
/* 002575e0: jal 0x00263918 */ c->r[31]=UINT64_C(0x002575e8);/* delay 002575e4 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[18]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleAction_00263918(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002575e8: move a0,s0 */ c->r[4]=c->r[16];
/* 002575ec: move a2,s3 */ c->r[6]=c->r[19];
/* 002575f0: li a3,0x1e */ c->r[7]=sx(UINT32_C(0x0000001e));
/* 002575f4: li t0,0x1e */ c->r[8]=sx(UINT32_C(0x0000001e));
/* 002575f8: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00257600);/* delay 002575fc */ c->r[5]=c->r[17];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257600: move a0,s0 */ c->r[4]=c->r[16];
/* 00257604: jal 0x0024f478 */ c->r[31]=UINT64_C(0x0025760c);/* delay 00257608 */ c->r[5]=c->r[17];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_0024F478(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 0025760c: move a0,s0 */ c->r[4]=c->r[16];
/* 00257610: move a1,s1 */ c->r[5]=c->r[17];
/* 00257614: move a2,s3 */ c->r[6]=c->r[19];
/* 00257618: li a3,0x14 */ c->r[7]=sx(UINT32_C(0x00000014));
/* 0025761c: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00257624);/* delay 00257620 */ c->r[8]=sx(UINT32_C(0x00000014));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
L_00257624:;
/* 00257624: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
L_00257628:;
/* 00257628: slti v0,s1,0x10 */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000010)));
/* 0025762c: bne v0,zero,0x00257558 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00257630 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x000000f0));if(taken){goto L_00257558;}}
/* 00257634: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00257638: move a0,s0 */ c->r[4]=c->r[16];
/* 0025763c: jal 0x002515e8 */ c->r[31]=UINT64_C(0x00257644);/* delay 00257640 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257644: bne v0,zero,0x00257730 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00257648 */ c->r[4]=c->r[16];if(taken){goto L_00257730;}}
/* 0025764c: jal 0x00251858 */ c->r[31]=UINT64_C(0x00257654);/* delay 00257650 */ c->r[18]=c->r[0];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetAllEndTime(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257654: move a0,s0 */ c->r[4]=c->r[16];
/* 00257658: jal 0x00251890 */ c->r[31]=UINT64_C(0x00257660);/* delay 0025765c */ c->r[17]=c->r[2];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetAllUnlockTime(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257660: lw a0,0x28(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00257664: li v1,0x2 */ c->r[3]=sx(UINT32_C(0x00000002));
/* 00257668: lh v0,0xa4(a0) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x000000a4)));
/* 0025766c: beq v0,v1,0x00257680 */ {int taken=(c->r[2]==c->r[3]);/* delay 00257670 */ c->r[3]=sx(UINT32_C(0x00000003));if(taken){goto L_00257680;}}
/* 00257674: lw v0,0x4(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 00257678: andi v0,v0,0x100 */ c->r[2]=c->r[2]&UINT64_C(0x100);
/* 0025767c: movz s2,v1,v0 */ if(c->r[2]==0){c->r[18]=c->r[3];}
L_00257680:;
/* 00257680: lw v0,0x78(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000078)));
/* 00257684: andi v0,v0,0x10 */ c->r[2]=c->r[2]&UINT64_C(0x10);
/* 00257688: beq v0,zero,0x00257730 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025768c */ c->r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_00257730;}}
/* 00257690: lh v1,0xa4(a0) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x000000a4)));
/* 00257694: bne v1,v0,0x002576c0 */ {int taken=(c->r[3]!=c->r[2]);/* delay 00257698 */ c->r[7]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));if(taken){goto L_002576c0;}}
/* 0025769c: lh a1,0x92(a0) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000092)));
/* 002576a0: move a0,s0 */ c->r[4]=c->r[16];
/* 002576a4: move a2,s1 */ c->r[6]=c->r[17];
/* 002576a8: li a3,0x6 */ c->r[7]=sx(UINT32_C(0x00000006));
/* 002576ac: jal 0x002517e0 */ c->r[31]=UINT64_C(0x002576b4);/* delay 002576b0 */ c->r[8]=sx(UINT32_C(0x00000006));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002576b4: b 0x002576d8 */ /* delay 002576b8 */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));goto L_002576d8;
L_002576c0:;
/* 002576c0: lh a1,0x92(a0) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000092)));
/* 002576c4: move a2,s1 */ c->r[6]=c->r[17];
/* 002576c8: move t0,a3 */ c->r[8]=c->r[7];
/* 002576cc: jal 0x002517e0 */ c->r[31]=UINT64_C(0x002576d4);/* delay 002576d0 */ c->r[4]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002576d4: lw a2,0x28(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
L_002576d8:;
/* 002576d8: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
/* 002576dc: lh s3,0xa4(a2) */ c->r[19]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[6]+UINT32_C(0x000000a4)));
/* 002576e0: bne s3,v0,0x00257730 */ {int taken=(c->r[19]!=c->r[2]);/* delay 002576e4 */ c->r[17]=sx((uint32_t)c->r[17]+(uint32_t)c->r[18]);if(taken){goto L_00257730;}}
/* 002576e8: move a3,zero */ c->r[7]=c->r[0];
/* 002576ec: li t0,0x2 */ c->r[8]=sx(UINT32_C(0x00000002));
/* 002576f0: li t1,0x4 */ c->r[9]=sx(UINT32_C(0x00000004));
/* 002576f4: li t2,0x4 */ c->r[10]=sx(UINT32_C(0x00000004));
/* 002576f8: move a0,s1 */ c->r[4]=c->r[17];
/* 002576fc: jal 0x00263810 */ c->r[31]=UINT64_C(0x00257704);/* delay 00257700 */ c->r[5]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbMakeUnitFadeInPacket(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8],c->r[9],c->r[10]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257704: move a0,s1 */ c->r[4]=c->r[17];
/* 00257708: lw a2,0x28(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0025770c: move a1,s0 */ c->r[5]=c->r[16];
/* 00257710: jal 0x00262fb8 */ c->r[31]=UINT64_C(0x00257718);/* delay 00257714 */ c->r[7]=c->r[0];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddFormOnOffPacket(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257718: lw a2,0x28(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0025771c: lh v0,0xa4(a2) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[6]+UINT32_C(0x000000a4)));
/* 00257720: bne v0,s3,0x00257730 */ {int taken=(c->r[2]!=c->r[19]);/* delay 00257724 */ c->r[4]=c->r[17];if(taken){goto L_00257730;}}
/* 00257728: jal 0x00261f90 */ c->r[31]=UINT64_C(0x00257730);/* delay 0025772c */ c->r[5]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddMotionStopClearPacket(c->r[4],c->r[5],c->r[6]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
L_00257730:;
/* 00257730: jal 0x00251858 */ c->r[31]=UINT64_C(0x00257738);/* delay 00257734 */ c->r[4]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionGetAllEndTime(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257738: li v1,0x64 */ c->r[3]=sx(UINT32_C(0x00000064));
/* 0025773c: sll a0,v0,0x3 */ c->r[4]=sx((uint32_t)c->r[2]<<3u);
/* 00257740: move a1,s0 */ c->r[5]=c->r[16];
/* 00257744: addu a0,a0,v0 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[2]);
/* 00257748: sw v0,0x188(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000188),(uint32_t)c->r[2]);
/* 0025774c: sll a0,a0,0x2 */ c->r[4]=sx((uint32_t)c->r[4]<<2u);
/* 00257750: beql v1,zero,0x00257758 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00257754 */ nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nocturne_break(7);goto L_00257758;}}
L_00257758:;
/* 00257758: subu a0,a0,v0 */ c->r[4]=sx((uint32_t)c->r[4]-(uint32_t)c->r[2]);
/* 0025775c: sll a0,a0,0x1 */ c->r[4]=sx((uint32_t)c->r[4]<<1u);
/* 00257760: divu a0,v1 */ {uint32_t n=(uint32_t)c->r[4],d=(uint32_t)c->r[3];c->lo=d?sx(n/d):UINT64_MAX;c->hi=sx(d?n%d:n);}
/* 00257764: mflo a0 */ c->r[4]=c->lo;
/* 00257768: jal 0x00261758 */ c->r[31]=UINT64_C(0x00257770);/* delay 0025776c */ (void)0;nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddHatudoEffectEndPacket(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257770: lw v0,0x4(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 00257774: andi v0,v0,0x400 */ c->r[2]=c->r[2]&UINT64_C(0x400);
/* 00257778: beq v0,zero,0x002577a8 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025777c */ c->r[4]=c->r[0];if(taken){goto L_002577a8;}}
/* 00257780: lw v0,0x188(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000188)));
/* 00257784: move a1,s0 */ c->r[5]=c->r[16];
/* 00257788: addiu s2,v0,-0xa */ c->r[18]=sx((uint32_t)c->r[2]+UINT32_C(0xfffffff6));
/* 0025778c: slti v1,s2,0x0 */ c->r[3]=less(c->r[18],sx(UINT32_C(0x00000000)));
/* 00257790: jal 0x00263628 */ c->r[31]=UINT64_C(0x00257798);/* delay 00257794 */ if(c->r[3]==0){c->r[4]=c->r[18];}nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddPanelStockFadeOutPacket(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257798: lw a0,0x188(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000188)));
/* 0025779c: move a1,s0 */ c->r[5]=c->r[16];
/* 002577a0: jal 0x00263678 */ c->r[31]=UINT64_C(0x002577a8);/* delay 002577a4 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0xffffffff));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddPanelStockEndPacket(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
L_002577a8:;
/* 002577a8: lw a1,0x188(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000188)));
/* 002577ac: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 002577b0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002577b4: addiu a0,a0,0x4048 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00004048));
/* 002577b8: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002577bc: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002577c0: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002577c4: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 002577c8: ld ra,0x28(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 002577cc: j 0x002d4748 */ /* delay 002577d0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,1u,UINT32_C(0x002577cc),UINT32_C(0xf0ff0030));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);return;
}
static void body_002577d8(BattleCallbackChoiceValues *c){
/* 002577d8: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002577dc: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002577e0: move s1,a0 */ c->r[17]=c->r[4];
/* 002577e4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002577e8: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 002577ec: lw a0,0x4(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000004)));
/* 002577f0: andi v0,a0,0x10 */ c->r[2]=c->r[4]&UINT64_C(0x10);
/* 002577f4: beq v0,zero,0x00257860 */ {int taken=(c->r[2]==c->r[0]);/* delay 002577f8 */ c->r[2]=sx(UINT32_C(0x002f0000));if(taken){goto L_00257860;}}
/* 002577fc: addiu v0,v0,0x5810 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00005810));
/* 00257800: lb v1,0x21(v0) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000021)));
/* 00257804: bltzl v1,0x0025781c */ {int taken=(neg(c->r[3]));if(taken){/* delay 00257808 */ c->r[2]=sx(UINT32_C(0xffffffef));goto L_0025781c;}}
/* 0025780c: lb v0,0x23(v0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000023)));
/* 00257810: bgezl v0,0x00257848 */ {int taken=(!neg(c->r[2]));if(taken){/* delay 00257814 */ c->r[4]=sx(UINT32_C(0x0000000e));goto L_00257848;}}
/* 00257818: li v0,-0x11 */ c->r[2]=sx(UINT32_C(0xffffffef));
L_0025781c:;
/* 0025781c: and v0,a0,v0 */ c->r[2]=c->r[4]&c->r[2];
/* 00257820: jal 0x00280528 */ c->r[31]=UINT64_C(0x00257828);/* delay 00257824 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000004),(uint32_t)c->r[2]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbPanelAnalyzeEnd();nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257828: li v0,0x15 */ c->r[2]=sx(UINT32_C(0x00000015));
/* 0025782c: sw v0,0x188(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000188),(uint32_t)c->r[2]);
/* 00257830: li a0,0xe */ c->r[4]=sx(UINT32_C(0x0000000e));
/* 00257834: li a1,0x2 */ c->r[5]=sx(UINT32_C(0x00000002));
/* 00257838: jal 0x0025ee78 */ c->r[31]=UINT64_C(0x00257840);/* delay 0025783c */ c->r[6]=c->r[0];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbOnOffKoukaPacketFlag(c->r[4],c->r[5],c->r[6]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257840: b 0x00257a50 */ /* delay 00257844 */ c->r[2]=c->r[0];goto L_00257a50;
L_00257848:;
/* 00257848: li a1,0x2 */ c->r[5]=sx(UINT32_C(0x00000002));
/* 0025784c: jal 0x0025ee78 */ c->r[31]=UINT64_C(0x00257854);/* delay 00257850 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbOnOffKoukaPacketFlag(c->r[4],c->r[5],c->r[6]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257854: b 0x00257a50 */ /* delay 00257858 */ c->r[2]=c->r[0];goto L_00257a50;
L_00257860:;
/* 00257860: lw v1,0x188(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000188)));
/* 00257864: sltiu v0,v1,0x10 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000010)));
/* 00257868: bne v0,zero,0x00257880 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025786c */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffffffff));if(taken){goto L_00257880;}}
/* 00257870: move v0,zero */ c->r[2]=c->r[0];
/* 00257874: b 0x00257a50 */ /* delay 00257878 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000188),(uint32_t)c->r[3]);goto L_00257a50;
L_00257880:;
/* 00257880: jal 0x002584c8 */ c->r[31]=UINT64_C(0x00257888);/* delay 00257884 */ (void)0;nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbUpdateOrder();nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257888: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 0025788c: move a0,s1 */ c->r[4]=c->r[17];
/* 00257890: jal 0x002515e8 */ c->r[31]=UINT64_C(0x00257898);/* delay 00257894 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257898: bnel v0,zero,0x002578ac */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0025789c */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));goto L_002578ac;}}
/* 002578a0: jal 0x00252720 */ c->r[31]=UINT64_C(0x002578a8);/* delay 002578a4 */ c->r[4]=c->r[17];body_00252720(c);
/* 002578a8: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
L_002578ac:;
/* 002578ac: move a0,s1 */ c->r[4]=c->r[17];
/* 002578b0: jal 0x002515e8 */ c->r[31]=UINT64_C(0x002578b8);/* delay 002578b4 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002578b8: bnel v0,zero,0x002578cc */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002578bc */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));goto L_002578cc;}}
/* 002578c0: jal 0x002529d0 */ c->r[31]=UINT64_C(0x002578c8);/* delay 002578c4 */ c->r[4]=c->r[17];body_002529d0(c);
/* 002578c8: lw v0,0x28(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
L_002578cc:;
/* 002578cc: move a0,s1 */ c->r[4]=c->r[17];
/* 002578d0: jal 0x002515e8 */ c->r[31]=UINT64_C(0x002578d8);/* delay 002578d4 */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002578d8: bne v0,zero,0x002578fc */ {int taken=(c->r[2]!=c->r[0]);/* delay 002578dc */ c->r[3]=sx(UINT32_C(0x00000003));if(taken){goto L_002578fc;}}
/* 002578e0: lw a0,0x28(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000028)));
/* 002578e4: lh v0,0xa4(a0) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x000000a4)));
/* 002578e8: bne v0,v1,0x002578fc */ {int taken=(c->r[2]!=c->r[3]);/* delay 002578ec */ (void)0;if(taken){goto L_002578fc;}}
/* 002578f0: lw v0,0x78(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000078)));
/* 002578f4: ori v0,v0,0x4000 */ c->r[2]=c->r[2]|UINT64_C(0x4000);
/* 002578f8: sw v0,0x78(a0) */ sw((uint32_t)c->r[4]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
L_002578fc:;
/* 002578fc: jal 0x00252c28 */ c->r[31]=UINT64_C(0x00257904);/* delay 00257900 */ c->r[4]=c->r[17];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionQueueDeadScripts(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257904: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00257908: jal 0x002469c0 */ c->r[31]=UINT64_C(0x00257910);/* delay 0025790c */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000024)));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitWorkPointer(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257910: move s0,v0 */ c->r[16]=c->r[2];
/* 00257914: bnel s0,zero,0x00257938 */ {int taken=(c->r[16]!=c->r[0]);if(taken){/* delay 00257918 */ c->r[5]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));goto L_00257938;}}
/* 0025791c: lw v0,0x0(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00257920: sh zero,0x5c(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x0000005c),(uint16_t)c->r[0]);
/* 00257924: sh zero,0x56(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x00000056),(uint16_t)c->r[0]);
/* 00257928: sh zero,0x58(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x00000058),(uint16_t)c->r[0]);
/* 0025792c: b 0x00257a40 */ /* delay 00257930 */ sh((uint32_t)c->r[2]+UINT32_C(0x0000005a),(uint16_t)c->r[0]);goto L_00257a40;
L_00257938:;
/* 00257938: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0025793c: lhu v1,0x30(s1) */ c->r[3]=hword((uint32_t)c->r[17]+UINT32_C(0x00000030));
/* 00257940: addiu a0,a0,0x4058 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00004058));
/* 00257944: sh v1,0x56(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x00000056),(uint16_t)c->r[3]);
/* 00257948: lhu v0,0x6a(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006a));
/* 0025794c: sh v0,0x58(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x00000058),(uint16_t)c->r[2]);
/* 00257950: lhu v1,0x6c(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006c));
/* 00257954: sh v1,0x5a(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x0000005a),(uint16_t)c->r[3]);
/* 00257958: jal 0x002d4748 */ c->r[31]=UINT64_C(0x00257960);/* delay 0025795c */ c->r[5]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006c));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,1u,UINT32_C(0x00257958),UINT32_C(0xf0ff0030));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257960: lw v1,0x0(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00257964: lw v0,0x4(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000004)));
/* 00257968: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 0025796c: beq v0,zero,0x0025797c */ {int taken=(c->r[2]==c->r[0]);/* delay 00257970 */ sh((uint32_t)c->r[3]+UINT32_C(0x0000005c),(uint16_t)c->r[0]);if(taken){goto L_0025797c;}}
/* 00257974: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00257978: sh v0,0x5c(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000005c),(uint16_t)c->r[2]);
L_0025797c:;
/* 0025797c: lh v1,0x6a(s0) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[16]+UINT32_C(0x0000006a)));
/* 00257980: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00257984: beq v1,v0,0x002579b8 */ {int taken=(c->r[3]==c->r[2]);/* delay 00257988 */ c->r[5]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006a));if(taken){goto L_002579b8;}}
/* 0025798c: slti v0,v1,0x2 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000002)));
/* 00257990: beql v0,zero,0x002579a8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00257994 */ c->r[2]=sx(UINT32_C(0x00000003));goto L_002579a8;}}
/* 00257998: beql v1,zero,0x00257a18 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 0025799c */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006c));goto L_00257a18;}}
/* 002579a0: b 0x00257a38 */ /* delay 002579a4 */ (void)0;goto L_00257a38;
L_002579a8:;
/* 002579a8: beql v1,v0,0x00257a18 */ {int taken=(c->r[3]==c->r[2]);if(taken){/* delay 002579ac */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006c));goto L_00257a18;}}
/* 002579b0: b 0x00257a38 */ /* delay 002579b4 */ (void)0;goto L_00257a38;
L_002579b8:;
/* 002579b8: lhu a0,0x6c(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006c));
/* 002579bc: ori v0,zero,0xffcf */ c->r[2]=c->r[0]|UINT64_C(0xffcf);
/* 002579c0: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 002579c4: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 002579c8: sltiu v0,v0,0x2 */ c->r[2]=(c->r[2]<sx(UINT32_C(0x00000002)));
/* 002579cc: beq v0,zero,0x002579e8 */ {int taken=(c->r[2]==c->r[0]);/* delay 002579d0 */ (void)0;if(taken){goto L_002579e8;}}
/* 002579d4: jal 0x002457f0 */ c->r[31]=UINT64_C(0x002579dc);/* delay 002579d8 */ c->r[4]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);datClearCommMemory(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 002579dc: b 0x00257a44 */ /* delay 002579e0 */ c->r[4]=c->r[17];goto L_00257a44;
L_002579e8:;
/* 002579e8: ori v0,zero,0xff5c */ c->r[2]=c->r[0]|UINT64_C(0xff5c);
/* 002579ec: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 002579f0: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 002579f4: sltiu v0,v0,0x3 */ c->r[2]=(c->r[2]<sx(UINT32_C(0x00000003)));
/* 002579f8: bnel v0,zero,0x00257a44 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002579fc */ c->r[4]=c->r[17];goto L_00257a44;}}
/* 00257a00: li v0,0xf7 */ c->r[2]=sx(UINT32_C(0x000000f7));
/* 00257a04: beql a0,v0,0x00257a44 */ {int taken=(c->r[4]==c->r[2]);if(taken){/* delay 00257a08 */ c->r[4]=c->r[17];goto L_00257a44;}}
/* 00257a0c: b 0x00257a1c */ /* delay 00257a10 */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006e));goto L_00257a1c;
L_00257a18:;
/* 00257a18: lhu v1,0x6e(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x0000006e));
L_00257a1c:;
/* 00257a1c: lhu v0,0x70(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000070));
/* 00257a20: sh a1,0x72(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000072),(uint16_t)c->r[5]);
/* 00257a24: sh v0,0x78(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000078),(uint16_t)c->r[2]);
/* 00257a28: sh a0,0x74(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000074),(uint16_t)c->r[4]);
/* 00257a2c: b 0x00257a40 */ /* delay 00257a30 */ sh((uint32_t)c->r[16]+UINT32_C(0x00000076),(uint16_t)c->r[3]);goto L_00257a40;
L_00257a38:;
/* 00257a38: jal 0x002457f0 */ c->r[31]=UINT64_C(0x00257a40);/* delay 00257a3c */ c->r[4]=c->r[16];nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);datClearCommMemory(c->r[4]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
L_00257a40:;
/* 00257a40: move a0,s1 */ c->r[4]=c->r[17];
L_00257a44:;
/* 00257a44: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x00257a4c);/* delay 00257a48 */ c->r[5]=sx(UINT32_C(0x00000014));nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c->r[29]);
/* 00257a4c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_00257a50:;
/* 00257a50: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00257a54: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00257a58: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00257a5c: jr ra */ /* delay 00257a60 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}
static BattleCallbackChoiceValues begin(void){
 BattleCallbackChoiceValues c={0};unsigned i;
 for(i=16u;i<=23u;++i)c.r[i]=nocturneBattleCallbackChoiceReadGpr(i);
 c.r[28]=nocturneBattleCallbackChoiceReadGpr(28);
 c.r[30]=nocturneBattleCallbackChoiceReadGpr(30);
 c.r[31]=nocturneBattleCallbackChoiceReadGpr(31);
 c.r[29]=nocturneBattleCallbackChoiceStackPointer();return c;
}
uint64_t ps2BattleCallbackChoice_00253490(uint64_t context){BattleCallbackChoiceValues c=begin();c.r[4]=context;body_00253490(&c);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleCallbackChoice_00257488(uint64_t context){BattleCallbackChoiceValues c=begin();c.r[4]=context;body_00257488(&c);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleCallbackChoice_002577D8(uint64_t context){BattleCallbackChoiceValues c=begin();c.r[4]=context;body_002577d8(&c);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleCallbackChoice_002532A8(uint64_t context,uint64_t value){BattleCallbackChoiceValues c=begin();c.r[4]=context;c.r[5]=value;body_002532a8(&c);nocturneBattleCallbackChoiceSetStackPointer((uint32_t)c.r[29]);}
