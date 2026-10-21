/* Whole66 BAD/BADWAIT/TARSEL/STKSEL direct family,2909 original operations.
 * Fixed native PCs/guest frames; no opcode interpreter or substitute UI.
 * Real registered calls; unresolved actual bank/frame bridges are declarations.
 * Source-only: no executable, callback, OS, resource or identity admission. */
#include "battle_status_pairs.h"
#include <stdlib.h>
#include "battle_action_consumer.h"
#include "battle_action_finish.h"
#include "battle_action_sequence.h"
#include "battle_ai_actions.h"
#include "battle_ai_startup.h"
#include "battle_check1_packets.h"
#include "battle_outcome.h"
#include "battle_panel_support.h"
#include "battle_presentation.h"
#include "battle_stock_renderer.h"
#include "battle_support_access.h"
#include "battle_targeting.h"
#include "battle_work_access.h"
#include "combat_calculation.h"
#include "event_camera.h"
#include "font_message.h"
#include "font_parser_support.h"
#include "font_text.h"
#include "libc_printf.h"
#include "message_commands.h"
#include "nocturne.h"
#include "process_lists.h"
#include "ps2_memory.h"
#include "script_lifetime.h"
#include "sound_bank_flow.h"
#include <string.h>
typedef struct BattleStatusPairsValues {uint64_t r[32],lo,hi;uint32_t f[32],condition;} BattleStatusPairsValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleStatusPairsAddress(a);}
static uint16_t hword(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
/* Each original partial64 instruction preserves its own live merge/store.
 * Access only the participating bytes in native little-endian order; source
 * values are latched before any aliased register or RAM destination changes. */
static uint64_t partial_load(uint64_t old,uint32_t a,unsigned left){
 unsigned offset=a&7u,count=left?offset+1u:8u-offset;
 uint32_t start=left?(a&~7u):a;unsigned target=left?7u-offset:0u;
 uint64_t value=old;
 for(unsigned i=0;i<count;i++){unsigned shift=8u*(target+i);value=(value&~(UINT64_C(255)<<shift))|((uint64_t)*at(start+i)<<shift);}
 return value;
}
static void partial_store(uint64_t value,uint32_t a,unsigned left){
 unsigned offset=a&7u,count=left?offset+1u:8u-offset;
 uint32_t start=left?(a&~7u):a;unsigned source=left?7u-offset:0u;
 for(unsigned i=0;i<count;i++)*at(start+i)=(uint8_t)(value>>(8u*(source+i)));
}

static uint64_t native_frame(BattleStatusPairsValues *c,uint32_t kind,uint32_t pc,uint32_t mask){
 BattleStatusPairsBoundary b;unsigned i;b.pc=pc;b.defined_mask=mask;
 for(i=0;i<32u;++i)b.gpr[i]=(mask&(UINT32_C(1)<<i))?c->r[i]:0;
 return nocturneBattleStatusPairsNativeCall(kind,&b);
}

static void body_001c8268(BattleStatusPairsValues *c);
static void body_001c9108(BattleStatusPairsValues *c);
static void body_001ca0d0(BattleStatusPairsValues *c);
static void body_001ca258(BattleStatusPairsValues *c);
static void body_001cea58(BattleStatusPairsValues *c);
static void body_001cf960(BattleStatusPairsValues *c);
static void body_00251428(BattleStatusPairsValues *c);
static void body_00253de0(BattleStatusPairsValues *c);
static void body_00253e00(BattleStatusPairsValues *c);
static void body_00254010(BattleStatusPairsValues *c);
static void body_00254058(BattleStatusPairsValues *c);
static void body_00254178(BattleStatusPairsValues *c);
static void body_00254190(BattleStatusPairsValues *c);
static void body_00254360(BattleStatusPairsValues *c);
static void body_002543a0(BattleStatusPairsValues *c);
static void body_00259c90(BattleStatusPairsValues *c);
static void body_00259cf8(BattleStatusPairsValues *c);
static void body_0025c8a8(BattleStatusPairsValues *c);
static void body_0025c8d0(BattleStatusPairsValues *c);
static void body_0025d1e8(BattleStatusPairsValues *c);
static void body_0025d2a0(BattleStatusPairsValues *c);
static void body_0025d4c0(BattleStatusPairsValues *c);
static void body_0025d6b8(BattleStatusPairsValues *c);
static void body_0025d6d8(BattleStatusPairsValues *c);
static void body_0025d700(BattleStatusPairsValues *c);
static void body_0025de40(BattleStatusPairsValues *c);
static void body_0025dfa0(BattleStatusPairsValues *c);
static void body_0025e070(BattleStatusPairsValues *c);
static void body_0025e0b8(BattleStatusPairsValues *c);
static void body_0025e100(BattleStatusPairsValues *c);
static void body_00279c30(BattleStatusPairsValues *c);
static void body_0027c2c0(BattleStatusPairsValues *c);
static void body_0027fa78(BattleStatusPairsValues *c);
static void body_0027fa98(BattleStatusPairsValues *c);
static void body_00281e10(BattleStatusPairsValues *c);
static void body_00282258(BattleStatusPairsValues *c);
static void body_00288e18(BattleStatusPairsValues *c);
static void body_002892a8(BattleStatusPairsValues *c);
static void body_00289310(BattleStatusPairsValues *c);
static void body_00289450(BattleStatusPairsValues *c);
static void body_0028d090(BattleStatusPairsValues *c);
static void body_0028e3c8(BattleStatusPairsValues *c);
static void body_0028e470(BattleStatusPairsValues *c);
static void body_0028e4b0(BattleStatusPairsValues *c);
static void body_0028e560(BattleStatusPairsValues *c);
static void body_0028e5c8(BattleStatusPairsValues *c);
static void body_0028e758(BattleStatusPairsValues *c);
static void body_0028e818(BattleStatusPairsValues *c);
static void body_0028e8d8(BattleStatusPairsValues *c);
static void body_0028e9b8(BattleStatusPairsValues *c);
static void body_0028eab8(BattleStatusPairsValues *c);
static void body_0028eb80(BattleStatusPairsValues *c);
static void body_0028ec18(BattleStatusPairsValues *c);
static void body_0028ec90(BattleStatusPairsValues *c);
static void body_0028ecc8(BattleStatusPairsValues *c);
static void body_0028ed98(BattleStatusPairsValues *c);
static void body_0028edc8(BattleStatusPairsValues *c);
static void body_0028f0a0(BattleStatusPairsValues *c);
static void body_002900e8(BattleStatusPairsValues *c);
static void body_00290138(BattleStatusPairsValues *c);
static void body_00290188(BattleStatusPairsValues *c);
static void body_002901d0(BattleStatusPairsValues *c);
static void body_00290490(BattleStatusPairsValues *c);
static void body_00290568(BattleStatusPairsValues *c);
static void body_0029ba80(BattleStatusPairsValues *c);
static void body_0029bae0(BattleStatusPairsValues *c);

static void body_001c8268(BattleStatusPairsValues *c){
/* 001c8268: lw a0,0x2c(a0) */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x0000002c)));
/* 001c826c: beq a0,zero,0x001c82b0 */ {int taken=(c->r[4]==c->r[0]);/* delay 001c8270 */ c->r[6]=c->r[0];if(taken){goto L_001c82b0;}}
/* 001c8274: lw v1,0x1c(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x0000001c)));
L_001c8278:;
/* 001c8278: beql v1,zero,0x001c82a8 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 001c827c */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000028)));goto L_001c82a8;}}
/* 001c8280: lb a1,0x1(a0) */ c->r[5]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[4]+UINT32_C(0x00000001)));
/* 001c8284: nop  */ (void)0;
L_001c8288:;
/* 001c8288: lw v0,0xc(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x0000000c)));
/* 001c828c: lw v1,0x28(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000028)));
/* 001c8290: addu a2,a2,v0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[2]);
/* 001c8294: nop  */ (void)0;
/* 001c8298: nop  */ (void)0;
/* 001c829c: bne v1,zero,0x001c8288 */ {int taken=(c->r[3]!=c->r[0]);/* delay 001c82a0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[5]);if(taken){goto L_001c8288;}}
/* 001c82a4: lw a0,0x28(a0) */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000028)));
L_001c82a8:;
/* 001c82a8: bnel a0,zero,0x001c8278 */ {int taken=(c->r[4]!=c->r[0]);if(taken){/* delay 001c82ac */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x0000001c)));goto L_001c8278;}}
L_001c82b0:;
/* 001c82b0: jr ra */ /* delay 001c82b4 */ c->r[2]=c->r[6];return;
}

static void body_001c9108(BattleStatusPairsValues *c){
/* 001c9108: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 001c910c: move t3,a2 */ c->r[11]=c->r[6];
/* 001c9110: sw a3,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[7]);
/* 001c9114: move a3,zero */ c->r[7]=c->r[0];
/* 001c9118: move a2,zero */ c->r[6]=c->r[0];
/* 001c911c: move t0,zero */ c->r[8]=c->r[0];
/* 001c9120: move t1,zero */ c->r[9]=c->r[0];
/* 001c9124: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 001c9128: jal 0x001c9188 */ c->r[31]=UINT64_C(0x001c9130);/* delay 001c912c */ c->r[10]=sx(UINT32_C(0x00000080));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FontMessageRequestEx(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8],c->r[9],c->r[10],c->r[11],sx(word((uint32_t)c->r[29])));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001c9130: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001c9134: jr ra */ /* delay 001c9138 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_001ca0d0(BattleStatusPairsValues *c){
/* 001ca0d0: addiu sp,sp,-0x70 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffff90));
/* 001ca0d4: sll t2,t2,0x18 */ c->r[10]=sx((uint32_t)c->r[10]<<24u);
/* 001ca0d8: sd s5,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[21]);
/* 001ca0dc: move s5,t0 */ c->r[21]=c->r[8];
/* 001ca0e0: sll t1,t1,0x18 */ c->r[9]=sx((uint32_t)c->r[9]<<24u);
/* 001ca0e4: sw a0,0x10(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000010),(uint32_t)c->r[4]);
/* 001ca0e8: sra t2,t2,0x18 */ c->r[10]=sar((uint32_t)c->r[10],24u);
/* 001ca0ec: move a0,s5 */ c->r[4]=c->r[21];
/* 001ca0f0: sd s0,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[16]);
/* 001ca0f4: move s0,a2 */ c->r[16]=c->r[6];
/* 001ca0f8: sd s1,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[17]);
/* 001ca0fc: move s1,zero */ c->r[17]=c->r[0];
/* 001ca100: sd s2,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[18]);
/* 001ca104: move s2,t3 */ c->r[18]=c->r[11];
/* 001ca108: sd s4,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[20]);
/* 001ca10c: sd s7,0x58(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000058),c->r[23]);
/* 001ca110: sra s7,t1,0x18 */ c->r[23]=sar((uint32_t)c->r[9],24u);
/* 001ca114: sd s8,0x60(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000060),c->r[30]);
/* 001ca118: move s8,a3 */ c->r[30]=c->r[7];
/* 001ca11c: sd s3,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[19]);
/* 001ca120: sd s6,0x50(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000050),c->r[22]);
/* 001ca124: sd ra,0x68(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000068),c->r[31]);
/* 001ca128: sw t2,0x18(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000018),(uint32_t)c->r[10]);
/* 001ca12c: jal 0x002d5d0c */ c->r[31]=UINT64_C(0x001ca134);/* delay 001ca130 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000014),(uint32_t)c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(ps2Strlen((const char *)at((uint32_t)c->r[4])));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca134: move s4,v0 */ c->r[20]=c->r[2];
/* 001ca138: lw v0,0x18(sp) */ c->r[2]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000018)));
/* 001ca13c: bne v0,zero,0x001ca14c */ {int taken=(c->r[2]!=c->r[0]);/* delay 001ca140 */ (void)0;if(taken){goto L_001ca14c;}}
/* 001ca144: jal 0x001c7c00 */ c->r[31]=UINT64_C(0x001ca14c);/* delay 001ca148 */ c->r[4]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frEnableMode(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
L_001ca14c:;
/* 001ca14c: jal 0x001c7c10 */ c->r[31]=UINT64_C(0x001ca154);/* delay 001ca150 */ c->r[4]=sx(UINT32_C(0x00000002));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frDisableMode(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca154: blez s4,0x001ca208 */ {int taken=((neg(c->r[20])||!c->r[20]));/* delay 001ca158 */ c->r[3]=sx((uint32_t)c->r[21]+(uint32_t)c->r[17]);if(taken){goto L_001ca208;}}
/* 001ca15c: sll s6,s0,0x4 */ c->r[22]=sx((uint32_t)c->r[16]<<4u);
L_001ca160:;
/* 001ca160: lb v0,0x0(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 001ca164: bltz v0,0x001ca180 */ {int taken=(neg(c->r[2]));/* delay 001ca168 */ c->r[4]=*at((uint32_t)c->r[3]+UINT32_C(0x00000000));if(taken){goto L_001ca180;}}
/* 001ca16c: sb a0,0x0(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000000))=(uint8_t)c->r[4];
/* 001ca170: li s3,0x1 */ c->r[19]=sx(UINT32_C(0x00000001));
/* 001ca174: b 0x001ca194 */ /* delay 001ca178 */ *at((uint32_t)c->r[29]+UINT32_C(0x00000001))=(uint8_t)c->r[0];goto L_001ca194;
L_001ca180:;
/* 001ca180: lbu v0,0x1(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 001ca184: li s3,0x2 */ c->r[19]=sx(UINT32_C(0x00000002));
/* 001ca188: sb a0,0x0(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000000))=(uint8_t)c->r[4];
/* 001ca18c: sb zero,0x2(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000002))=(uint8_t)c->r[0];
/* 001ca190: sb v0,0x1(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000001))=(uint8_t)c->r[2];
L_001ca194:;
/* 001ca194: move a0,sp */ c->r[4]=c->r[29];
/* 001ca198: move a2,zero */ c->r[6]=c->r[0];
/* 001ca19c: move a3,zero */ c->r[7]=c->r[0];
/* 001ca1a0: move t0,zero */ c->r[8]=c->r[0];
/* 001ca1a4: jal 0x001c7828 */ c->r[31]=UINT64_C(0x001ca1ac);/* delay 001ca1a8 */ c->r[5]=c->r[23];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FontAppendStringCombined(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca1ac: move a1,s6 */ c->r[5]=c->r[22];
/* 001ca1b0: move s0,v0 */ c->r[16]=c->r[2];
/* 001ca1b4: jal 0x001c7b40 */ c->r[31]=UINT64_C(0x001ca1bc);/* delay 001ca1b8 */ c->r[4]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2FontSetDepth(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca1bc: move a0,s0 */ c->r[4]=c->r[16];
/* 001ca1c0: jal 0x001c7ba8 */ c->r[31]=UINT64_C(0x001ca1c8);/* delay 001ca1c4 */ c->r[5]=c->r[30];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);frSetFontColor(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca1c8: move a0,s0 */ c->r[4]=c->r[16];
/* 001ca1cc: jal 0x001c7a88 */ c->r[31]=UINT64_C(0x001ca1d4);/* delay 001ca1d0 */ c->r[5]=sx(UINT32_C(0x00000003));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);frSetFontSpace(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca1d4: move a0,s2 */ c->r[4]=c->r[18];
/* 001ca1d8: jal 0x001c8108 */ c->r[31]=UINT64_C(0x001ca1e0);/* delay 001ca1dc */ c->r[5]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FontCombineRequest(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca1e0: bne s1,zero,0x001ca1f0 */ {int taken=(c->r[17]!=c->r[0]);/* delay 001ca1e4 */ c->r[18]=c->r[2];if(taken){goto L_001ca1f0;}}
/* 001ca1e8: lw v0,0x10(sp) */ c->r[2]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000010)));
/* 001ca1ec: sw v0,0x4(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[2]);
L_001ca1f0:;
/* 001ca1f0: lw v0,0x14(sp) */ c->r[2]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000014)));
/* 001ca1f4: addu s1,s1,s3 */ c->r[17]=sx((uint32_t)c->r[17]+(uint32_t)c->r[19]);
/* 001ca1f8: sw v0,0x8(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000008),(uint32_t)c->r[2]);
/* 001ca1fc: slt v0,s1,s4 */ c->r[2]=less(c->r[17],c->r[20]);
/* 001ca200: bne v0,zero,0x001ca160 */ {int taken=(c->r[2]!=c->r[0]);/* delay 001ca204 */ c->r[3]=sx((uint32_t)c->r[21]+(uint32_t)c->r[17]);if(taken){goto L_001ca160;}}
L_001ca208:;
/* 001ca208: jal 0x001c7c00 */ c->r[31]=UINT64_C(0x001ca210);/* delay 001ca20c */ c->r[4]=sx(UINT32_C(0x00000002));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frEnableMode(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca210: lw v0,0x18(sp) */ c->r[2]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000018)));
/* 001ca214: bnel v0,zero,0x001ca228 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 001ca218 */ c->r[2]=c->r[18];goto L_001ca228;}}
/* 001ca21c: jal 0x001c7c10 */ c->r[31]=UINT64_C(0x001ca224);/* delay 001ca220 */ c->r[4]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frDisableMode(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca224: move v0,s2 */ c->r[2]=c->r[18];
L_001ca228:;
/* 001ca228: ld s0,0x20(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 001ca22c: ld s1,0x28(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 001ca230: ld s2,0x30(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 001ca234: ld s3,0x38(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 001ca238: ld s4,0x40(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 001ca23c: ld s5,0x48(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 001ca240: ld s6,0x50(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000050));
/* 001ca244: ld s7,0x58(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000058));
/* 001ca248: ld s8,0x60(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000060));
/* 001ca24c: ld ra,0x68(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000068));
/* 001ca250: jr ra */ /* delay 001ca254 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000070));return;
}

static void body_001ca258(BattleStatusPairsValues *c){
/* 001ca258: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 001ca25c: move t3,t1 */ c->r[11]=c->r[9];
/* 001ca260: move t2,zero */ c->r[10]=c->r[0];
/* 001ca264: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001ca268: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 001ca26c: jal 0x001ca0d0 */ c->r[31]=UINT64_C(0x001ca274);/* delay 001ca270 */ c->r[9]=sx(UINT32_C(0x00000001));body_001ca0d0(c);
/* 001ca274: move s0,v0 */ c->r[16]=c->r[2];
/* 001ca278: li a1,0x3 */ c->r[5]=sx(UINT32_C(0x00000003));
/* 001ca27c: jal 0x001c7a88 */ c->r[31]=UINT64_C(0x001ca284);/* delay 001ca280 */ c->r[4]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);frSetFontSpace(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ca284: move v0,s0 */ c->r[2]=c->r[16];
/* 001ca288: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001ca28c: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001ca290: jr ra */ /* delay 001ca294 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_001cea58(BattleStatusPairsValues *c){
/* 001cea58: sll v0,a0,0x2 */ c->r[2]=sx((uint32_t)c->r[4]<<2u);
/* 001cea5c: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 001cea60: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 001cea64: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 001cea68: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 001cea6c: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 001cea70: lui s0,0x57 */ c->r[16]=sx(UINT32_C(0x00570000));
/* 001cea74: addu s0,s0,v0 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[2]);
/* 001cea78: lw s0,-0x4174(s0) */ c->r[16]=sx(word((uint32_t)c->r[16]+UINT32_C(0xffffbe8c)));
/* 001cea7c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 001cea80: move s2,a2 */ c->r[18]=c->r[6];
/* 001cea84: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 001cea88: jal 0x001cf178 */ c->r[31]=UINT64_C(0x001cea90);/* delay 001cea8c */ c->r[4]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2MessageGetResourceEntry(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001cea90: addiu a0,s0,0xc4 */ c->r[4]=sx((uint32_t)c->r[16]+UINT32_C(0x000000c4));
/* 001cea94: lw s1,0x4(v0) */ c->r[17]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000004)));
/* 001cea98: lh v1,0x18(s1) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000018)));
/* 001cea9c: beq v1,zero,0x001ceb00 */ {int taken=(c->r[3]==c->r[0]);/* delay 001ceaa0 */ c->r[2]=c->r[0];if(taken){goto L_001ceb00;}}
/* 001ceaa4: jal 0x001cf440 */ c->r[31]=UINT64_C(0x001ceaac);/* delay 001ceaa8 */ (void)0;nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);CommitVarTable(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ceaac: lw v0,0x8(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000008)));
/* 001ceab0: beq v0,zero,0x001ceac0 */ {int taken=(c->r[2]==c->r[0]);/* delay 001ceab4 */ c->r[4]=c->r[2];if(taken){goto L_001ceac0;}}
/* 001ceab8: jal 0x001c81b8 */ c->r[31]=UINT64_C(0x001ceac0);/* delay 001ceabc */ (void)0;nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2FontBindMessageStyle(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
L_001ceac0:;
/* 001ceac0: move a0,s1 */ c->r[4]=c->r[17];
/* 001ceac4: jal 0x001cf1a8 */ c->r[31]=UINT64_C(0x001ceacc);/* delay 001ceac8 */ c->r[5]=c->r[18];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=GetMessagePagePtr(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ceacc: move a0,zero */ c->r[4]=c->r[0];
/* 001cead0: move a2,v0 */ c->r[6]=c->r[2];
/* 001cead4: beq a2,zero,0x001ceb00 */ {int taken=(c->r[6]==c->r[0]);/* delay 001cead8 */ c->r[5]=c->r[0];if(taken){goto L_001ceb00;}}
/* 001ceadc: jal 0x001c9108 */ c->r[31]=UINT64_C(0x001ceae4);/* delay 001ceae0 */ c->r[7]=c->r[0];body_001c9108(c);
/* 001ceae4: move s0,v0 */ c->r[16]=c->r[2];
/* 001ceae8: jal 0x001cf960 */ c->r[31]=UINT64_C(0x001ceaf0);/* delay 001ceaec */ c->r[4]=c->r[16];body_001cf960(c);
/* 001ceaf0: move a0,s0 */ c->r[4]=c->r[16];
/* 001ceaf4: jal 0x001c6ff8 */ c->r[31]=UINT64_C(0x001ceafc);/* delay 001ceaf8 */ c->r[17]=c->r[2];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frDestroyFontRequestAfter(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 001ceafc: move v0,s1 */ c->r[2]=c->r[17];
L_001ceb00:;
/* 001ceb00: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001ceb04: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 001ceb08: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 001ceb0c: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 001ceb10: jr ra */ /* delay 001ceb14 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_001cf960(BattleStatusPairsValues *c){
/* 001cf960: beq a0,zero,0x001cf9a8 */ {int taken=(c->r[4]==c->r[0]);/* delay 001cf964 */ c->r[6]=c->r[0];if(taken){goto L_001cf9a8;}}
L_001cf968:;
/* 001cf968: lw a1,0x8(a0) */ c->r[5]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000008)));
/* 001cf96c: move v1,zero */ c->r[3]=c->r[0];
/* 001cf970: lw v0,0xc(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x0000000c)));
/* 001cf974: nop  */ (void)0;
L_001cf978:;
/* 001cf978: lw a0,0x24(a0) */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000024)));
/* 001cf97c: beq a0,zero,0x001cf99c */ {int taken=(c->r[4]==c->r[0]);/* delay 001cf980 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);if(taken){goto L_001cf99c;}}
/* 001cf984: lw v0,0x8(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000008)));
/* 001cf988: nop  */ (void)0;
/* 001cf98c: nop  */ (void)0;
/* 001cf990: nop  */ (void)0;
/* 001cf994: beql a1,v0,0x001cf978 */ {int taken=(c->r[5]==c->r[2]);if(taken){/* delay 001cf998 */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x0000000c)));goto L_001cf978;}}
L_001cf99c:;
/* 001cf99c: slt v0,a2,v1 */ c->r[2]=less(c->r[6],c->r[3]);
/* 001cf9a0: bne a0,zero,0x001cf968 */ {int taken=(c->r[4]!=c->r[0]);/* delay 001cf9a4 */ if(c->r[2]!=0){c->r[6]=c->r[3];}if(taken){goto L_001cf968;}}
L_001cf9a8:;
/* 001cf9a8: jr ra */ /* delay 001cf9ac */ c->r[2]=sx((uint32_t)c->r[6]<<4u);return;
}

static void body_00251428(BattleStatusPairsValues *c){
/* 00251428: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0025142c: sd s0,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[16]);
/* 00251430: move s0,a0 */ c->r[16]=c->r[4];
/* 00251434: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 00251438: sw zero,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[0]);
/* 0025143c: lw a1,0x2c(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 00251440: sw zero,0x4(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint32_t)c->r[0]);
/* 00251444: lh v1,0x6a(a1) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x0000006a)));
/* 00251448: sltiu v0,v1,0x9 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000009)));
/* 0025144c: beq v0,zero,0x00251480 */ {int taken=(c->r[2]==c->r[0]);/* delay 00251450 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),(uint32_t)c->r[0]);if(taken){goto L_00251480;}}
/* 00251454: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 00251458: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 0025145c: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00251460: lw v1,0x37d0(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x000037d0)));
/* 00251464: jr v1 */ {uint64_t target=c->r[3];/* delay 00251468 */ (void)0;switch(target){case UINT64_C(0x00251470):goto L_00251470;case UINT64_C(0x00251480):goto L_00251480;default:abort();}}
L_00251470:;
/* 00251470: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00251474: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00251478: b 0x002514ac */ /* delay 0025147c */ sw((uint32_t)c->r[3]+UINT32_C(0x00000080),(uint32_t)c->r[2]);goto L_002514ac;
L_00251480:;
/* 00251480: lh a0,0x6a(a1) */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x0000006a)));
/* 00251484: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00251488: bnel a0,v0,0x002514a8 */ {int taken=(c->r[4]!=c->r[2]);if(taken){/* delay 0025148c */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));goto L_002514a8;}}
/* 00251490: lhu v1,0x6c(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x0000006c));
/* 00251494: li v0,0xdf */ c->r[2]=sx(UINT32_C(0x000000df));
/* 00251498: bne v1,v0,0x002514a8 */ {int taken=(c->r[3]!=c->r[2]);/* delay 0025149c */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));if(taken){goto L_002514a8;}}
/* 002514a0: b 0x002514ac */ /* delay 002514a4 */ sw((uint32_t)c->r[2]+UINT32_C(0x00000080),(uint32_t)c->r[4]);goto L_002514ac;
L_002514a8:;
/* 002514a8: sw zero,0x80(v0) */ sw((uint32_t)c->r[2]+UINT32_C(0x00000080),(uint32_t)c->r[0]);
L_002514ac:;
/* 002514ac: sw zero,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[0]);
/* 002514b0: move a2,sp */ c->r[6]=c->r[29];
/* 002514b4: addiu a3,sp,0x4 */ c->r[7]=sx((uint32_t)c->r[29]+UINT32_C(0x00000004));
/* 002514b8: addiu t0,sp,0x8 */ c->r[8]=sx((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002514bc: move a0,s0 */ c->r[4]=c->r[16];
/* 002514c0: jal 0x00258de8 */ c->r[31]=UINT64_C(0x002514c8);/* delay 002514c4 */ c->r[9]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbGetTargetTypeRuleArea(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8],c->r[9]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002514c8: move a0,s0 */ c->r[4]=c->r[16];
/* 002514cc: lw a1,0x30(a0) */ c->r[5]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000030)));
/* 002514d0: lw a2,0x0(sp) */ c->r[6]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000000)));
/* 002514d4: lw a3,0x4(sp) */ c->r[7]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000004)));
/* 002514d8: jal 0x0025dfa0 */ c->r[31]=UINT64_C(0x002514e0);/* delay 002514dc */ c->r[8]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000008)));body_0025dfa0(c);
/* 002514e0: ld s0,0x10(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002514e4: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002514e8: jr ra */ /* delay 002514ec */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00253de0(BattleStatusPairsValues *c){
/* 00253de0: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00253de4: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 00253de8: jal 0x00279c30 */ c->r[31]=UINT64_C(0x00253df0);/* delay 00253dec */ (void)0;body_00279c30(c);
/* 00253df0: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00253df4: j 0x0027c2c0 */ /* delay 00253df8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_0027c2c0(c);return;
}

static void body_00253e00(BattleStatusPairsValues *c){
/* 00253e00: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00253e04: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00253e08: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 00253e0c: jal 0x002514f0 */ c->r[31]=UINT64_C(0x00253e14);/* delay 00253e10 */ c->r[16]=c->r[4];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionClearTimeList(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253e14: jal 0x00251538 */ c->r[31]=UINT64_C(0x00253e1c);/* delay 00253e18 */ c->r[4]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionSetHpForTimeList(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253e1c: sw zero,0x48(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000048),(uint32_t)c->r[0]);
/* 00253e20: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00253e24: jal 0x00267788 */ c->r[31]=UINT64_C(0x00253e2c);/* delay 00253e28 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetBadStat(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253e2c: move v1,v0 */ c->r[3]=c->r[2];
/* 00253e30: li v0,0x8 */ c->r[2]=sx(UINT32_C(0x00000008));
/* 00253e34: beq v1,v0,0x00253ee8 */ {int taken=(c->r[3]==c->r[2]);/* delay 00253e38 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000009)));if(taken){goto L_00253ee8;}}
/* 00253e3c: beq v0,zero,0x00253e70 */ {int taken=(c->r[2]==c->r[0]);/* delay 00253e40 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_00253e70;}}
/* 00253e44: beql v1,zero,0x00253fd8 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00253e48 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));goto L_00253fd8;}}
/* 00253e4c: sltiu v0,v1,0x3 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000003)));
/* 00253e50: bnel v0,zero,0x00253ea8 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00253e54 */ c->r[4]=c->r[0];goto L_00253ea8;}}
/* 00253e58: li v0,0x4 */ c->r[2]=sx(UINT32_C(0x00000004));
/* 00253e5c: beql v1,v0,0x00253f08 */ {int taken=(c->r[3]==c->r[2]);if(taken){/* delay 00253e60 */ c->r[4]=c->r[0];goto L_00253f08;}}
/* 00253e64: b 0x00253fd8 */ /* delay 00253e68 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));goto L_00253fd8;
L_00253e70:;
/* 00253e70: beq v1,v0,0x00253ee8 */ {int taken=(c->r[3]==c->r[2]);/* delay 00253e74 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000081)));if(taken){goto L_00253ee8;}}
/* 00253e78: beq v0,zero,0x00253e98 */ {int taken=(c->r[2]==c->r[0]);/* delay 00253e7c */ c->r[2]=sx(UINT32_C(0x00000400));if(taken){goto L_00253e98;}}
/* 00253e80: li v0,0x10 */ c->r[2]=sx(UINT32_C(0x00000010));
/* 00253e84: beq v1,v0,0x00253f60 */ {int taken=(c->r[3]==c->r[2]);/* delay 00253e88 */ (void)0;if(taken){goto L_00253f60;}}
/* 00253e8c: b 0x00253fd8 */ /* delay 00253e90 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));goto L_00253fd8;
L_00253e98:;
/* 00253e98: beq v1,v0,0x00253f60 */ {int taken=(c->r[3]==c->r[2]);/* delay 00253e9c */ (void)0;if(taken){goto L_00253f60;}}
/* 00253ea0: b 0x00253fd8 */ /* delay 00253ea4 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));goto L_00253fd8;
L_00253ea8:;
/* 00253ea8: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 00253eac: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];nocturneBattleStatusPairsWriteFpr(12u,c->f[12]);
/* 00253eb0: jal 0x002642e0 */ c->r[31]=UINT64_C(0x00253eb8);/* delay 00253eb4 */ c->r[5]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleOutcome_002642E0(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253eb8: move a0,zero */ c->r[4]=c->r[0];
/* 00253ebc: lw a3,0x28(s0) */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00253ec0: move a1,s0 */ c->r[5]=c->r[16];
/* 00253ec4: jal 0x00264368 */ c->r[31]=UINT64_C(0x00253ecc);/* delay 00253ec8 */ c->r[6]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleOutcome_00264368(c->r[4],c->r[5],c->r[6]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253ecc: li a0,0x5 */ c->r[4]=sx(UINT32_C(0x00000005));
/* 00253ed0: lw a2,0x28(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00253ed4: jal 0x002645a8 */ c->r[31]=UINT64_C(0x00253edc);/* delay 00253ed8 */ c->r[5]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbMakeBadKaifukuPacket(c->r[4],c->r[5],c->r[6]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253edc: b 0x00253f8c */ /* delay 00253ee0 */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));goto L_00253f8c;
L_00253ee8:;
/* 00253ee8: jal 0x0028f0a0 */ c->r[31]=UINT64_C(0x00253ef0);/* delay 00253eec */ c->r[4]=c->r[16];body_0028f0a0(c);
/* 00253ef0: move a0,s0 */ c->r[4]=c->r[16];
/* 00253ef4: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x00253efc);/* delay 00253ef8 */ c->r[5]=sx(UINT32_C(0x0000000b));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253efc: b 0x00254000 */ /* delay 00253f00 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00254000;
L_00253f08:;
/* 00253f08: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 00253f0c: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];nocturneBattleStatusPairsWriteFpr(12u,c->f[12]);
/* 00253f10: jal 0x002642e0 */ c->r[31]=UINT64_C(0x00253f18);/* delay 00253f14 */ c->r[5]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleOutcome_002642E0(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253f18: move a0,zero */ c->r[4]=c->r[0];
/* 00253f1c: lw a3,0x28(s0) */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00253f20: move a1,s0 */ c->r[5]=c->r[16];
/* 00253f24: jal 0x00264368 */ c->r[31]=UINT64_C(0x00253f2c);/* delay 00253f28 */ c->r[6]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleOutcome_00264368(c->r[4],c->r[5],c->r[6]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253f2c: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 00253f30: lw a2,0x28(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00253f34: li a0,0xa */ c->r[4]=sx(UINT32_C(0x0000000a));
/* 00253f38: lhu t1,0xc(v1) */ c->r[9]=hword((uint32_t)c->r[3]+UINT32_C(0x0000000c));
/* 00253f3c: move a1,s0 */ c->r[5]=c->r[16];
/* 00253f40: lhu t0,0x8(v1) */ c->r[8]=hword((uint32_t)c->r[3]+UINT32_C(0x00000008));
/* 00253f44: move a3,zero */ c->r[7]=c->r[0];
/* 00253f48: srl t1,t1,0x3 */ c->r[9]=sx((uint32_t)c->r[9]>>3u);
/* 00253f4c: move t2,zero */ c->r[10]=c->r[0];
/* 00253f50: jal 0x00264010 */ c->r[31]=UINT64_C(0x00253f58);/* delay 00253f54 */ c->r[8]=sx((uint32_t)c->r[8]>>3u);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleAction_00264010(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8],c->r[9],c->r[10]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253f58: b 0x00253f8c */ /* delay 00253f5c */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));goto L_00253f8c;
L_00253f60:;
/* 00253f60: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 00253f64: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];nocturneBattleStatusPairsWriteFpr(12u,c->f[12]);
/* 00253f68: move a0,zero */ c->r[4]=c->r[0];
/* 00253f6c: jal 0x002642e0 */ c->r[31]=UINT64_C(0x00253f74);/* delay 00253f70 */ c->r[5]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleOutcome_002642E0(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253f74: move a0,zero */ c->r[4]=c->r[0];
/* 00253f78: lw a3,0x28(s0) */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00253f7c: move a1,s0 */ c->r[5]=c->r[16];
/* 00253f80: jal 0x00264368 */ c->r[31]=UINT64_C(0x00253f88);/* delay 00253f84 */ c->r[6]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleOutcome_00264368(c->r[4],c->r[5],c->r[6]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253f88: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
L_00253f8c:;
/* 00253f8c: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 00253f90: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 00253f94: beql v0,zero,0x00253fa8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00253f98 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));goto L_00253fa8;}}
/* 00253f9c: jal 0x001b1740 */ c->r[31]=UINT64_C(0x00253fa4);/* delay 00253fa0 */ c->r[4]=sx(UINT32_C(0x00000019));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbCameraSetState(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253fa4: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
L_00253fa8:;
/* 00253fa8: move a0,s0 */ c->r[4]=c->r[16];
/* 00253fac: move a2,zero */ c->r[6]=c->r[0];
/* 00253fb0: li a3,0x1e */ c->r[7]=sx(UINT32_C(0x0000001e));
/* 00253fb4: lh a1,0x92(v0) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));
/* 00253fb8: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00253fc0);/* delay 00253fbc */ c->r[8]=sx(UINT32_C(0x0000001e));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253fc0: move a0,s0 */ c->r[4]=c->r[16];
/* 00253fc4: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x00253fcc);/* delay 00253fc8 */ c->r[5]=sx(UINT32_C(0x00000012));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253fcc: b 0x00254000 */ /* delay 00253fd0 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00254000;
L_00253fd8:;
/* 00253fd8: jal 0x002677b8 */ c->r[31]=UINT64_C(0x00253fe0);/* delay 00253fdc */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatCheckCurse_002677B8(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253fe0: beql v0,zero,0x00254000 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00253fe4 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00254000;}}
/* 00253fe8: jal 0x0028f0a0 */ c->r[31]=UINT64_C(0x00253ff0);/* delay 00253fec */ c->r[4]=c->r[16];body_0028f0a0(c);
/* 00253ff0: move a0,s0 */ c->r[4]=c->r[16];
/* 00253ff4: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x00253ffc);/* delay 00253ff8 */ c->r[5]=sx(UINT32_C(0x0000000b));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00253ffc: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00254000:;
/* 00254000: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00254004: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00254008: jr ra */ /* delay 0025400c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00254010(BattleStatusPairsValues *c){
/* 00254010: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00254014: move a1,a0 */ c->r[5]=c->r[4];
/* 00254018: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0025401c: lw v1,0x4(a1) */ c->r[3]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000004)));
/* 00254020: lw a2,0x0(a1) */ c->r[6]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 00254024: ori v1,v1,0x20 */ c->r[3]=c->r[3]|UINT64_C(0x20);
/* 00254028: sw v1,0x4(a1) */ sw((uint32_t)c->r[5]+UINT32_C(0x00000004),(uint32_t)c->r[3]);
/* 0025402c: lw v0,0x60(a2) */ c->r[2]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000060)));
/* 00254030: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 00254034: beq v0,zero,0x00254048 */ {int taken=(c->r[2]==c->r[0]);/* delay 00254038 */ c->r[4]=sx(UINT32_C(0x00000019));if(taken){goto L_00254048;}}
/* 0025403c: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00254040: j 0x001b1740 */ /* delay 00254044 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbCameraSetState(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);return;
L_00254048:;
/* 00254048: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025404c: li a0,0x3 */ c->r[4]=sx(UINT32_C(0x00000003));
/* 00254050: j 0x001b1740 */ /* delay 00254054 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbCameraSetState(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);return;
}

static void body_00254058(BattleStatusPairsValues *c){
/* 00254058: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0025405c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00254060: move s0,a0 */ c->r[16]=c->r[4];
/* 00254064: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00254068: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 0025406c: lw a2,0x2c(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 00254070: lh v1,0x6a(a2) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[6]+UINT32_C(0x0000006a)));
/* 00254074: sltiu v0,v1,0xb */ c->r[2]=(c->r[3]<sx(UINT32_C(0x0000000b)));
/* 00254078: beq v0,zero,0x002540c0 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025407c */ c->r[17]=c->r[0];if(taken){goto L_002540c0;}}
/* 00254080: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 00254084: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 00254088: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0025408c: lw v1,0x3ad0(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00003ad0)));
/* 00254090: jr v1 */ {uint64_t target=c->r[3];/* delay 00254094 */ (void)0;switch(target){case UINT64_C(0x00254098):goto L_00254098;case UINT64_C(0x002540c0):goto L_002540c0;default:abort();}}
L_00254098:;
/* 00254098: lhu a0,0xa(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x0000000a));
/* 0025409c: li v0,0x5 */ c->r[2]=sx(UINT32_C(0x00000005));
/* 002540a0: bnel a0,v0,0x002540fc */ {int taken=(c->r[4]!=c->r[2]);if(taken){/* delay 002540a4 */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[6]+UINT32_C(0x0000006a)));goto L_002540fc;}}
/* 002540a8: lw a1,0x48(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000048)));
/* 002540ac: blezl a1,0x002540fc */ {int taken=((neg(c->r[5])||!c->r[5]));if(taken){/* delay 002540b0 */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[6]+UINT32_C(0x0000006a)));goto L_002540fc;}}
/* 002540b4: b 0x002540e0 */ /* delay 002540b8 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));goto L_002540e0;
L_002540c0:;
/* 002540c0: lhu a0,0xa(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x0000000a));
/* 002540c4: li v0,0x5 */ c->r[2]=sx(UINT32_C(0x00000005));
/* 002540c8: bnel a0,v0,0x002540fc */ {int taken=(c->r[4]!=c->r[2]);if(taken){/* delay 002540cc */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[6]+UINT32_C(0x0000006a)));goto L_002540fc;}}
/* 002540d0: lw a1,0x48(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000048)));
/* 002540d4: blezl a1,0x002540fc */ {int taken=((neg(c->r[5])||!c->r[5]));if(taken){/* delay 002540d8 */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[6]+UINT32_C(0x0000006a)));goto L_002540fc;}}
/* 002540dc: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
L_002540e0:;
/* 002540e0: lw a2,0x4c(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000004c)));
/* 002540e4: lw a0,0x130(v0) */ c->r[4]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000130)));
/* 002540e8: jal 0x002892a8 */ c->r[31]=UINT64_C(0x002540f0);/* delay 002540ec */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000050)));body_002892a8(c);
/* 002540f0: lw a2,0x2c(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 002540f4: lhu a0,0xa(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x0000000a));
/* 002540f8: lh v1,0x6a(a2) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[6]+UINT32_C(0x0000006a)));
L_002540fc:;
/* 002540fc: sltiu v0,v1,0xb */ c->r[2]=(c->r[3]<sx(UINT32_C(0x0000000b)));
/* 00254100: beq v0,zero,0x0025412c */ {int taken=(c->r[2]==c->r[0]);/* delay 00254104 */ c->r[2]=(c->r[4]<sx(UINT32_C(0x00000029)));if(taken){goto L_0025412c;}}
/* 00254108: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 0025410c: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 00254110: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00254114: lw v1,0x3b00(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00003b00)));
/* 00254118: jr v1 */ {uint64_t target=c->r[3];/* delay 0025411c */ (void)0;switch(target){case UINT64_C(0x00254120):goto L_00254120;case UINT64_C(0x00254128):goto L_00254128;default:abort();}}
L_00254120:;
/* 00254120: b 0x00254138 */ /* delay 00254124 */ c->r[2]=(c->r[4]<sx(UINT32_C(0x0000001f)));goto L_00254138;
L_00254128:;
/* 00254128: sltiu v0,a0,0x29 */ c->r[2]=(c->r[4]<sx(UINT32_C(0x00000029)));
L_0025412c:;
/* 0025412c: beql v0,zero,0x00254140 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00254130 */ c->r[17]=sx(UINT32_C(0x00000001));goto L_00254140;}}
/* 00254134: lw v0,0x48(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000048)));
L_00254138:;
/* 00254138: beql v0,zero,0x00254140 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0025413c */ c->r[17]=sx(UINT32_C(0x00000001));goto L_00254140;}}
L_00254140:;
/* 00254140: beq s1,zero,0x00254160 */ {int taken=(c->r[17]==c->r[0]);/* delay 00254144 */ c->r[4]=c->r[16];if(taken){goto L_00254160;}}
/* 00254148: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x00254150);/* delay 0025414c */ c->r[5]=sx(UINT32_C(0x00000007));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00254150: sw zero,0x48(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000048),(uint32_t)c->r[0]);
/* 00254154: b 0x00254164 */ /* delay 00254158 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_00254164;
L_00254160:;
/* 00254160: move v0,zero */ c->r[2]=c->r[0];
L_00254164:;
/* 00254164: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00254168: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025416c: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00254170: jr ra */ /* delay 00254174 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00254178(BattleStatusPairsValues *c){
/* 00254178: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025417c: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 00254180: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00254184: j 0x00251428 */ /* delay 00254188 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_00251428(c);return;
}

static void body_00254190(BattleStatusPairsValues *c){
/* 00254190: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 00254194: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00254198: move s1,a0 */ c->r[17]=c->r[4];
/* 0025419c: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 002541a0: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002541a4: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 002541a8: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 002541ac: lw v1,0x0(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 002541b0: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 002541b4: andi v0,v0,0x40 */ c->r[2]=c->r[2]&UINT64_C(0x40);
/* 002541b8: beq v0,zero,0x002541f8 */ {int taken=(c->r[2]==c->r[0]);/* delay 002541bc */ c->r[19]=c->r[0];if(taken){goto L_002541f8;}}
/* 002541c0: lw v1,0x4(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000004)));
/* 002541c4: andi v0,v1,0x80 */ c->r[2]=c->r[3]&UINT64_C(0x80);
/* 002541c8: bne v0,zero,0x002541f8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002541cc */ c->r[2]=c->r[3]|UINT64_C(0x80);if(taken){goto L_002541f8;}}
/* 002541d0: li a0,0x2 */ c->r[4]=sx(UINT32_C(0x00000002));
/* 002541d4: jal 0x0025c8a8 */ c->r[31]=UINT64_C(0x002541dc);/* delay 002541d8 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000004),(uint32_t)c->r[2]);body_0025c8a8(c);
/* 002541dc: jal 0x0025d4c0 */ c->r[31]=UINT64_C(0x002541e4);/* delay 002541e0 */ (void)0;body_0025d4c0(c);
/* 002541e4: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 002541e8: move v0,zero */ c->r[2]=c->r[0];
/* 002541ec: b 0x00254340 */ /* delay 002541f0 */ *at((uint32_t)c->r[17]+UINT32_C(0x00000008))=(uint8_t)c->r[3];goto L_00254340;
L_002541f8:;
/* 002541f8: jal 0x0025d6b8 */ c->r[31]=UINT64_C(0x00254200);/* delay 002541fc */ c->r[16]=sx(UINT32_C(0x00000001));body_0025d6b8(c);
/* 00254200: move v1,v0 */ c->r[3]=c->r[2];
/* 00254204: beq v1,s0,0x0025433c */ {int taken=(c->r[3]==c->r[16]);/* delay 00254208 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000002)));if(taken){goto L_0025433c;}}
/* 0025420c: beq v0,zero,0x00254228 */ {int taken=(c->r[2]==c->r[0]);/* delay 00254210 */ c->r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_00254228;}}
/* 00254214: beq v1,zero,0x00254238 */ {int taken=(c->r[3]==c->r[0]);/* delay 00254218 */ c->r[2]=c->r[19];if(taken){goto L_00254238;}}
/* 0025421c: b 0x00254344 */ /* delay 00254220 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00254344;
L_00254228:;
/* 00254228: beq v1,v0,0x00254300 */ {int taken=(c->r[3]==c->r[2]);/* delay 0025422c */ c->r[2]=c->r[19];if(taken){goto L_00254300;}}
/* 00254230: b 0x00254344 */ /* delay 00254234 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00254344;
L_00254238:;
/* 00254238: jal 0x00246b68 */ c->r[31]=UINT64_C(0x00254240);/* delay 0025423c */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetSelectBit(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00254240: move s2,v0 */ c->r[18]=c->r[2];
/* 00254244: lw v0,0x4(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000004)));
/* 00254248: andi v0,v0,0x80 */ c->r[2]=c->r[2]&UINT64_C(0x80);
/* 0025424c: bne v0,zero,0x002542e0 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00254250 */ (void)0;if(taken){goto L_002542e0;}}
/* 00254254: lw v1,0x2c(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000002c)));
/* 00254258: lh a1,0x6a(v1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x0000006a)));
/* 0025425c: beq a1,s0,0x00254288 */ {int taken=(c->r[5]==c->r[16]);/* delay 00254260 */ c->r[4]=sx(UINT32_C(0xffffffff));if(taken){goto L_00254288;}}
/* 00254264: li v0,0x5 */ c->r[2]=sx(UINT32_C(0x00000005));
/* 00254268: bne a1,v0,0x0025428c */ {int taken=(c->r[5]!=c->r[2]);/* delay 0025426c */ (void)0;if(taken){goto L_0025428c;}}
/* 00254270: lhu a1,0x6c(v1) */ c->r[5]=hword((uint32_t)c->r[3]+UINT32_C(0x0000006c));
/* 00254274: jal 0x00259c48 */ c->r[31]=UINT64_C(0x0025427c);/* delay 00254278 */ c->r[4]=c->r[17];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetItemSkillNo(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0025427c: b 0x0025428c */ /* delay 00254280 */ c->r[4]=c->r[2];goto L_0025428c;
L_00254288:;
/* 00254288: lhu a0,0x6c(v1) */ c->r[4]=hword((uint32_t)c->r[3]+UINT32_C(0x0000006c));
L_0025428c:;
/* 0025428c: bltz a0,0x002542d8 */ {int taken=(neg(c->r[4]));/* delay 00254290 */ (void)0;if(taken){goto L_002542d8;}}
/* 00254294: jal 0x00290568 */ c->r[31]=UINT64_C(0x0025429c);/* delay 00254298 */ c->r[5]=c->r[18];body_00290568(c);
/* 0025429c: move s0,v0 */ c->r[16]=c->r[2];
/* 002542a0: beq s0,zero,0x002542d8 */ {int taken=(c->r[16]==c->r[0]);/* delay 002542a4 */ (void)0;if(taken){goto L_002542d8;}}
/* 002542a8: jal 0x00290490 */ c->r[31]=UINT64_C(0x002542b0);/* delay 002542ac */ c->r[4]=c->r[16];body_00290490(c);
/* 002542b0: li v0,0x4 */ c->r[2]=sx(UINT32_C(0x00000004));
/* 002542b4: bne s0,v0,0x002542c4 */ {int taken=(c->r[16]!=c->r[2]);/* delay 002542b8 */ (void)0;if(taken){goto L_002542c4;}}
/* 002542bc: jal 0x0025d700 */ c->r[31]=UINT64_C(0x002542c4);/* delay 002542c0 */ c->r[4]=sx(UINT32_C(0x0000001d));body_0025d700(c);
L_002542c4:;
/* 002542c4: jal 0x0025d6d8 */ c->r[31]=UINT64_C(0x002542cc);/* delay 002542c8 */ c->r[4]=sx(UINT32_C(0x00000001));body_0025d6d8(c);
/* 002542cc: b 0x00254340 */ /* delay 002542d0 */ c->r[2]=c->r[19];goto L_00254340;
L_002542d8:;
/* 002542d8: jal 0x0028d090 */ c->r[31]=UINT64_C(0x002542e0);/* delay 002542dc */ c->r[4]=sx(UINT32_C(0x00000008));body_0028d090(c);
L_002542e0:;
/* 002542e0: jal 0x0025c8d0 */ c->r[31]=UINT64_C(0x002542e8);/* delay 002542e4 */ c->r[19]=sx(UINT32_C(0x00000001));body_0025c8d0(c);
/* 002542e8: sw s2,0x3c(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x0000003c),(uint32_t)c->r[18]);
/* 002542ec: move a0,s1 */ c->r[4]=c->r[17];
/* 002542f0: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x002542f8);/* delay 002542f4 */ c->r[5]=sx(UINT32_C(0x00000007));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002542f8: b 0x00254340 */ /* delay 002542fc */ c->r[2]=c->r[19];goto L_00254340;
L_00254300:;
/* 00254300: lw v0,0x0(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00254304: li a1,-0x9 */ c->r[5]=sx(UINT32_C(0xfffffff7));
/* 00254308: li a0,0xf */ c->r[4]=sx(UINT32_C(0x0000000f));
/* 0025430c: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
L_00254310:;
/* 00254310: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 00254314: addiu a0,a0,-0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0xffffffff));
/* 00254318: and v0,v0,a1 */ c->r[2]=c->r[2]&c->r[5];
/* 0025431c: sw v0,0x78(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
/* 00254320: nop  */ (void)0;
/* 00254324: bgez a0,0x00254310 */ {int taken=(!neg(c->r[4]));/* delay 00254328 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x000000f0));if(taken){goto L_00254310;}}
/* 0025432c: jal 0x0025c8a8 */ c->r[31]=UINT64_C(0x00254334);/* delay 00254330 */ c->r[4]=sx(UINT32_C(0x00000002));body_0025c8a8(c);
/* 00254334: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00254338: sb v0,0x8(s1) */ *at((uint32_t)c->r[17]+UINT32_C(0x00000008))=(uint8_t)c->r[2];
L_0025433c:;
/* 0025433c: move v0,s3 */ c->r[2]=c->r[19];
L_00254340:;
/* 00254340: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00254344:;
/* 00254344: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00254348: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0025434c: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00254350: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00254354: jr ra */ /* delay 00254358 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_00254360(BattleStatusPairsValues *c){
/* 00254360: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00254364: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00254368: move s0,a0 */ c->r[16]=c->r[4];
/* 0025436c: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 00254370: jal 0x0027fa98 */ c->r[31]=UINT64_C(0x00254378);/* delay 00254374 */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[0]);body_0027fa98(c);
/* 00254378: lw a0,0x0(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0025437c: jal 0x0027fd18 */ c->r[31]=UINT64_C(0x00254384);/* delay 00254380 */ c->r[5]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbPanelStockSelect(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00254384: li v1,-0x1 */ c->r[3]=sx(UINT32_C(0xffffffff));
/* 00254388: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025438c: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00254390: sw v1,-0x3050(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffcfb0),(uint32_t)c->r[3]);
/* 00254394: jr ra */ /* delay 00254398 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_002543a0(BattleStatusPairsValues *c){
/* 002543a0: lw v1,-0x3050(gp) */ c->r[3]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffcfb0)));
/* 002543a4: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 002543a8: li v0,-0x2 */ c->r[2]=sx(UINT32_C(0xfffffffe));
/* 002543ac: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002543b0: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 002543b4: beq v1,v0,0x00254428 */ {int taken=(c->r[3]==c->r[2]);/* delay 002543b8 */ c->r[16]=c->r[4];if(taken){goto L_00254428;}}
/* 002543bc: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
/* 002543c0: beq v1,v0,0x00254418 */ {int taken=(c->r[3]==c->r[2]);/* delay 002543c4 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));if(taken){goto L_00254418;}}
/* 002543c8: jal 0x0027fd18 */ c->r[31]=UINT64_C(0x002543d0);/* delay 002543cc */ c->r[5]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbPanelStockSelect(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002543d0: jal 0x0025c8d0 */ c->r[31]=UINT64_C(0x002543d8);/* delay 002543d4 */ (void)0;body_0025c8d0(c);
/* 002543d8: lw v0,-0x3050(gp) */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffcfb0)));
/* 002543dc: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 002543e0: move a0,s0 */ c->r[4]=c->r[16];
/* 002543e4: li a1,0x7 */ c->r[5]=sx(UINT32_C(0x00000007));
/* 002543e8: addiu v0,v0,0x10 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000010));
/* 002543ec: sllv v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]<<((unsigned)c->r[2]&31u));
/* 002543f0: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x002543f8);/* delay 002543f4 */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[3]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002543f8: lw v0,0x4(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 002543fc: li a0,0x8 */ c->r[4]=sx(UINT32_C(0x00000008));
/* 00254400: ori v0,v0,0x400 */ c->r[2]=c->r[2]|UINT64_C(0x400);
/* 00254404: jal 0x0028d090 */ c->r[31]=UINT64_C(0x0025440c);/* delay 00254408 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[2]);body_0028d090(c);
/* 0025440c: b 0x00254478 */ /* delay 00254410 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_00254478;
L_00254418:;
/* 00254418: jal 0x0027fd18 */ c->r[31]=UINT64_C(0x00254420);/* delay 0025441c */ c->r[5]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbPanelStockSelect(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00254420: b 0x00254474 */ /* delay 00254424 */ sw((uint32_t)c->r[28]+UINT32_C(0xffffcfb0),(uint32_t)c->r[2]);goto L_00254474;
L_00254428:;
/* 00254428: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0025442c: li a1,-0x9 */ c->r[5]=sx(UINT32_C(0xfffffff7));
/* 00254430: li a0,0xf */ c->r[4]=sx(UINT32_C(0x0000000f));
/* 00254434: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
L_00254438:;
/* 00254438: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 0025443c: addiu a0,a0,-0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0xffffffff));
/* 00254440: and v0,v0,a1 */ c->r[2]=c->r[2]&c->r[5];
/* 00254444: sw v0,0x78(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
/* 00254448: nop  */ (void)0;
/* 0025444c: bgez a0,0x00254438 */ {int taken=(!neg(c->r[4]));/* delay 00254450 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x000000f0));if(taken){goto L_00254438;}}
/* 00254454: jal 0x0025c8a8 */ c->r[31]=UINT64_C(0x0025445c);/* delay 00254458 */ c->r[4]=sx(UINT32_C(0x00000002));body_0025c8a8(c);
/* 0025445c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00254460: sb v0,0x8(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x00000008))=(uint8_t)c->r[2];
/* 00254464: jal 0x0028d090 */ c->r[31]=UINT64_C(0x0025446c);/* delay 00254468 */ c->r[4]=sx(UINT32_C(0x0000000a));body_0028d090(c);
/* 0025446c: jal 0x0027fa78 */ c->r[31]=UINT64_C(0x00254474);/* delay 00254470 */ (void)0;body_0027fa78(c);
L_00254474:;
/* 00254474: move v0,zero */ c->r[2]=c->r[0];
L_00254478:;
/* 00254478: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025447c: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00254480: jr ra */ /* delay 00254484 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00259c90(BattleStatusPairsValues *c){
/* 00259c90: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00259c94: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 00259c98: sll v0,a1,0x2 */ c->r[2]=sx((uint32_t)c->r[5]<<2u);
/* 00259c9c: li a2,0x3 */ c->r[6]=sx(UINT32_C(0x00000003));
/* 00259ca0: addiu t2,v1,0x4190 */ c->r[10]=sx((uint32_t)c->r[3]+UINT32_C(0x00004190));
/* 00259ca4: ldl a3,0x7(t2) */ c->r[7]=partial_load(c->r[7],(uint32_t)c->r[10]+UINT32_C(0x00000007),1);
/* 00259ca8: ldr a3,0x0(t2) */ c->r[7]=partial_load(c->r[7],(uint32_t)c->r[10]+UINT32_C(0x00000000),0);
/* 00259cac: ldl t0,0xf(t2) */ c->r[8]=partial_load(c->r[8],(uint32_t)c->r[10]+UINT32_C(0x0000000f),1);
/* 00259cb0: ldr t0,0x8(t2) */ c->r[8]=partial_load(c->r[8],(uint32_t)c->r[10]+UINT32_C(0x00000008),0);
/* 00259cb4: ldl t1,0x17(t2) */ c->r[9]=partial_load(c->r[9],(uint32_t)c->r[10]+UINT32_C(0x00000017),1);
/* 00259cb8: ldr t1,0x10(t2) */ c->r[9]=partial_load(c->r[9],(uint32_t)c->r[10]+UINT32_C(0x00000010),0);
/* 00259cbc: sdl a3,0x7(sp) */ partial_store(c->r[7],(uint32_t)c->r[29]+UINT32_C(0x00000007),1);
/* 00259cc0: sdr a3,0x0(sp) */ partial_store(c->r[7],(uint32_t)c->r[29]+UINT32_C(0x00000000),0);
/* 00259cc4: sdl t0,0xf(sp) */ partial_store(c->r[8],(uint32_t)c->r[29]+UINT32_C(0x0000000f),1);
/* 00259cc8: sdr t0,0x8(sp) */ partial_store(c->r[8],(uint32_t)c->r[29]+UINT32_C(0x00000008),0);
/* 00259ccc: sdl t1,0x17(sp) */ partial_store(c->r[9],(uint32_t)c->r[29]+UINT32_C(0x00000017),1);
/* 00259cd0: sdr t1,0x10(sp) */ partial_store(c->r[9],(uint32_t)c->r[29]+UINT32_C(0x00000010),0);
/* 00259cd4: bne a1,a2,0x00259ce8 */ {int taken=(c->r[5]!=c->r[6]);/* delay 00259cd8 */ c->r[2]=sx((uint32_t)c->r[29]+(uint32_t)c->r[2]);if(taken){goto L_00259ce8;}}
/* 00259cdc: b 0x00259cec */ /* delay 00259ce0 */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x000014ac)));goto L_00259cec;
L_00259ce8:;
/* 00259ce8: lw v0,0x0(v0) */ c->r[2]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
L_00259cec:;
/* 00259cec: jr ra */ /* delay 00259cf0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00259cf8(BattleStatusPairsValues *c){
/* 00259cf8: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 00259cfc: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00259d00: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 00259d04: jal 0x00101898 */ c->r[31]=UINT64_C(0x00259d0c);/* delay 00259d08 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000041a8));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3SearchProcessName(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00259d0c: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00259d10: move a0,v0 */ c->r[4]=c->r[2];
/* 00259d14: j 0x00101ab0 */ /* delay 00259d18 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3GetProcessData(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);return;
}

static void body_0025c8a8(BattleStatusPairsValues *c){
/* 0025c8a8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025c8ac: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025c8b0: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0025c8b4: jal 0x00259cf8 */ c->r[31]=UINT64_C(0x0025c8bc);/* delay 0025c8b8 */ c->r[16]=c->r[4];body_00259cf8(c);
/* 0025c8bc: sb s0,0xc(v0) */ *at((uint32_t)c->r[2]+UINT32_C(0x0000000c))=(uint8_t)c->r[16];
/* 0025c8c0: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025c8c4: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025c8c8: jr ra */ /* delay 0025c8cc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0025c8d0(BattleStatusPairsValues *c){
/* 0025c8d0: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025c8d4: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0025c8d8: jal 0x00259cf8 */ c->r[31]=UINT64_C(0x0025c8e0);/* delay 0025c8dc */ (void)0;body_00259cf8(c);
/* 0025c8e0: lw v1,0x14b4(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x000014b4)));
/* 0025c8e4: li a1,-0x2 */ c->r[5]=sx(UINT32_C(0xfffffffe));
/* 0025c8e8: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025c8ec: li a0,0x4 */ c->r[4]=sx(UINT32_C(0x00000004));
/* 0025c8f0: ori v1,v1,0x2 */ c->r[3]=c->r[3]|UINT64_C(0x2);
/* 0025c8f4: sb a0,0xc(v0) */ *at((uint32_t)c->r[2]+UINT32_C(0x0000000c))=(uint8_t)c->r[4];
/* 0025c8f8: and v1,v1,a1 */ c->r[3]=c->r[3]&c->r[5];
/* 0025c8fc: sw v1,0x14b4(v0) */ sw((uint32_t)c->r[2]+UINT32_C(0x000014b4),(uint32_t)c->r[3]);
/* 0025c900: jr ra */ /* delay 0025c904 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0025d1e8(BattleStatusPairsValues *c){
/* 0025d1e8: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0025d1ec: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025d1f0: move s0,a1 */ c->r[16]=c->r[5];
/* 0025d1f4: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0025d1f8: move s1,a2 */ c->r[17]=c->r[6];
/* 0025d1fc: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0025d200: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 0025d204: jal 0x00259c90 */ c->r[31]=UINT64_C(0x0025d20c);/* delay 0025d208 */ c->r[18]=c->r[4];body_00259c90(c);
/* 0025d20c: sll a1,s0,0x2 */ c->r[5]=sx((uint32_t)c->r[16]<<2u);
/* 0025d210: addiu t0,s2,0xc */ c->r[8]=sx((uint32_t)c->r[18]+UINT32_C(0x0000000c));
/* 0025d214: addiu a2,a1,0x10 */ c->r[6]=sx((uint32_t)c->r[5]+UINT32_C(0x00000010));
/* 0025d218: addiu a0,a1,0x30 */ c->r[4]=sx((uint32_t)c->r[5]+UINT32_C(0x00000030));
/* 0025d21c: addiu a3,s2,0x4 */ c->r[7]=sx((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 0025d220: addu t2,t0,a2 */ c->r[10]=sx((uint32_t)c->r[8]+(uint32_t)c->r[6]);
/* 0025d224: addu t1,a3,a0 */ c->r[9]=sx((uint32_t)c->r[7]+(uint32_t)c->r[4]);
/* 0025d228: sb s0,0xd(s2) */ *at((uint32_t)c->r[18]+UINT32_C(0x0000000d))=(uint8_t)c->r[16];
/* 0025d22c: sll v1,s0,0x3 */ c->r[3]=sx((uint32_t)c->r[16]<<3u);
/* 0025d230: sw s1,0x0(t2) */ sw((uint32_t)c->r[10]+UINT32_C(0x00000000),(uint32_t)c->r[17]);
/* 0025d234: sw s1,0x0(t1) */ sw((uint32_t)c->r[9]+UINT32_C(0x00000000),(uint32_t)c->r[17]);
/* 0025d238: addu v1,v1,s0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[16]);
/* 0025d23c: addu a1,a1,a3 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[7]);
/* 0025d240: sll v1,v1,0x5 */ c->r[3]=sx((uint32_t)c->r[3]<<5u);
/* 0025d244: lw a0,0xdd0(a1) */ c->r[4]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000dd0)));
/* 0025d248: addu v1,s1,v1 */ c->r[3]=sx((uint32_t)c->r[17]+(uint32_t)c->r[3]);
/* 0025d24c: addu v0,s1,v0 */ c->r[2]=sx((uint32_t)c->r[17]+(uint32_t)c->r[2]);
/* 0025d250: addu a2,v1,t0 */ c->r[6]=sx((uint32_t)c->r[3]+(uint32_t)c->r[8]);
/* 0025d254: subu v1,v0,a0 */ c->r[3]=sx((uint32_t)c->r[2]-(uint32_t)c->r[4]);
/* 0025d258: slt v0,v0,a0 */ c->r[2]=less(c->r[2],c->r[4]);
/* 0025d25c: bne v0,zero,0x0025d274 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025d260 */ c->r[17]=sx((uint32_t)c->r[17]-(uint32_t)c->r[3]);if(taken){goto L_0025d274;}}
/* 0025d264: slti v0,s1,0x0 */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000000)));
/* 0025d268: move v1,zero */ c->r[3]=c->r[0];
/* 0025d26c: movz v1,s1,v0 */ if(c->r[2]==0){c->r[3]=c->r[17];}
/* 0025d270: sw v1,0x0(t1) */ sw((uint32_t)c->r[9]+UINT32_C(0x00000000),(uint32_t)c->r[3]);
L_0025d274:;
/* 0025d274: lb v0,0xde0(a2) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[6]+UINT32_C(0x00000de0)));
/* 0025d278: beq v0,zero,0x0025d28c */ {int taken=(c->r[2]==c->r[0]);/* delay 0025d27c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_0025d28c;}}
/* 0025d280: sb zero,0xd(s2) */ *at((uint32_t)c->r[18]+UINT32_C(0x0000000d))=(uint8_t)c->r[0];
/* 0025d284: sw zero,0x0(t2) */ sw((uint32_t)c->r[10]+UINT32_C(0x00000000),(uint32_t)c->r[0]);
/* 0025d288: sw zero,0x0(t1) */ sw((uint32_t)c->r[9]+UINT32_C(0x00000000),(uint32_t)c->r[0]);
L_0025d28c:;
/* 0025d28c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025d290: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0025d294: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0025d298: jr ra */ /* delay 0025d29c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_0025d2a0(BattleStatusPairsValues *c){
/* 0025d2a0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0025d2a4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025d2a8: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0025d2ac: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0025d2b0: move s2,a0 */ c->r[18]=c->r[4];
/* 0025d2b4: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 0025d2b8: lw a0,0x4(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000004)));
/* 0025d2bc: jal 0x002469c0 */ c->r[31]=UINT64_C(0x0025d2c4);/* delay 0025d2c0 */ c->r[5]=sx(word((uint32_t)c->r[18]+UINT32_C(0x0000004c)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitWorkPointer(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0025d2c4: li a0,0x2 */ c->r[4]=sx(UINT32_C(0x00000002));
/* 0025d2c8: lhu s1,0x74(v0) */ c->r[17]=hword((uint32_t)c->r[2]+UINT32_C(0x00000074));
/* 0025d2cc: jal 0x0029bae0 */ c->r[31]=UINT64_C(0x0025d2d4);/* delay 0025d2d0 */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000072)));body_0029bae0(c);
/* 0025d2d4: bne v0,zero,0x0025d2f8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025d2d8 */ (void)0;if(taken){goto L_0025d2f8;}}
/* 0025d2dc: lw v1,0x8(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000008)));
/* 0025d2e0: lw v0,0x4(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000004)));
/* 0025d2e4: andi v0,v0,0x80 */ c->r[2]=c->r[2]&UINT64_C(0x80);
/* 0025d2e8: beq v0,zero,0x0025d2f8 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025d2ec */ (void)0;if(taken){goto L_0025d2f8;}}
/* 0025d2f0: move s0,zero */ c->r[16]=c->r[0];
/* 0025d2f4: move s1,zero */ c->r[17]=c->r[0];
L_0025d2f8:;
/* 0025d2f8: jal 0x0029bae0 */ c->r[31]=UINT64_C(0x0025d300);/* delay 0025d2fc */ c->r[4]=sx(UINT32_C(0x00000001));body_0029bae0(c);
/* 0025d300: bne v0,zero,0x0025d328 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025d304 */ c->r[5]=c->r[0];if(taken){goto L_0025d328;}}
/* 0025d308: lw v1,0x8(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000008)));
/* 0025d30c: lw v0,0x4(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000004)));
/* 0025d310: andi v0,v0,0x80 */ c->r[2]=c->r[2]&UINT64_C(0x80);
/* 0025d314: bne v0,zero,0x0025d330 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025d318 */ c->r[9]=sx((uint32_t)c->r[18]+UINT32_C(0x00000004));if(taken){goto L_0025d330;}}
/* 0025d31c: move s0,zero */ c->r[16]=c->r[0];
/* 0025d320: move s1,zero */ c->r[17]=c->r[0];
/* 0025d324: move a1,zero */ c->r[5]=c->r[0];
L_0025d328:;
/* 0025d328: addiu t1,s2,0x4 */ c->r[9]=sx((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 0025d32c: nop  */ (void)0;
L_0025d330:;
/* 0025d330: sll a3,a1,0x2 */ c->r[7]=sx((uint32_t)c->r[5]<<2u);
L_0025d334:;
/* 0025d334: move a0,t1 */ c->r[4]=c->r[9];
/* 0025d338: addu v1,a3,a0 */ c->r[3]=sx((uint32_t)c->r[7]+(uint32_t)c->r[4]);
/* 0025d33c: lw v0,0xdd0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000dd0)));
/* 0025d340: blez v0,0x0025d494 */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 0025d344 */ c->r[6]=c->r[0];if(taken){goto L_0025d494;}}
/* 0025d348: sll t0,a1,0x3 */ c->r[8]=sx((uint32_t)c->r[5]<<3u);
/* 0025d34c: addu v0,t0,a1 */ c->r[2]=sx((uint32_t)c->r[8]+(uint32_t)c->r[5]);
L_0025d350:;
/* 0025d350: sll v0,v0,0x5 */ c->r[2]=sx((uint32_t)c->r[2]<<5u);
/* 0025d354: addu v0,v0,a2 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[6]);
/* 0025d358: sll v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]<<1u);
/* 0025d35c: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 0025d360: lhu a0,0x50(v0) */ c->r[4]=hword((uint32_t)c->r[2]+UINT32_C(0x00000050));
/* 0025d364: addiu v1,a0,-0x8000 */ c->r[3]=sx((uint32_t)c->r[4]+UINT32_C(0xffff8000));
/* 0025d368: sltiu v0,v1,0x5 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000005)));
/* 0025d36c: beql v0,zero,0x0025d3d0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0025d370 */ c->r[3]=sx(UINT32_C(0x00000001));goto L_0025d3d0;}}
/* 0025d374: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 0025d378: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 0025d37c: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0025d380: lw v1,0x42a0(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x000042a0)));
/* 0025d384: jr v1 */ {uint64_t target=c->r[3];/* delay 0025d388 */ (void)0;switch(target){case UINT64_C(0x0025d390):goto L_0025d390;case UINT64_C(0x0025d3a0):goto L_0025d3a0;case UINT64_C(0x0025d3a8):goto L_0025d3a8;case UINT64_C(0x0025d3b0):goto L_0025d3b0;case UINT64_C(0x0025d478):goto L_0025d478;default:abort();}}
L_0025d390:;
/* 0025d390: bnel s0,zero,0x0025d47c */ {int taken=(c->r[16]!=c->r[0]);if(taken){/* delay 0025d394 */ c->r[4]=c->r[9];goto L_0025d47c;}}
/* 0025d398: b 0x0025d3bc */ /* delay 0025d39c */ (void)0;goto L_0025d3bc;
L_0025d3a0:;
/* 0025d3a0: b 0x0025d3b4 */ /* delay 0025d3a4 */ c->r[2]=sx(UINT32_C(0x00000002));goto L_0025d3b4;
L_0025d3a8:;
/* 0025d3a8: b 0x0025d3b4 */ /* delay 0025d3ac */ c->r[2]=sx(UINT32_C(0x00000003));goto L_0025d3b4;
L_0025d3b0:;
/* 0025d3b0: li v0,0x7 */ c->r[2]=sx(UINT32_C(0x00000007));
L_0025d3b4:;
/* 0025d3b4: bnel s0,v0,0x0025d47c */ {int taken=(c->r[16]!=c->r[2]);if(taken){/* delay 0025d3b8 */ c->r[4]=c->r[9];goto L_0025d47c;}}
L_0025d3bc:;
/* 0025d3bc: jal 0x0025d1e8 */ c->r[31]=UINT64_C(0x0025d3c4);/* delay 0025d3c0 */ c->r[4]=c->r[18];body_0025d1e8(c);
/* 0025d3c4: b 0x0025d4a8 */ /* delay 0025d3c8 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0025d4a8;
L_0025d3d0:;
/* 0025d3d0: beq a1,v1,0x0025d428 */ {int taken=(c->r[5]==c->r[3]);/* delay 0025d3d4 */ c->r[2]=less(c->r[5],sx(UINT32_C(0x00000002)));if(taken){goto L_0025d428;}}
/* 0025d3d8: beq v0,zero,0x0025d3f0 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025d3dc */ c->r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_0025d3f0;}}
/* 0025d3e0: beq a1,zero,0x0025d400 */ {int taken=(c->r[5]==c->r[0]);/* delay 0025d3e4 */ (void)0;if(taken){goto L_0025d400;}}
/* 0025d3e8: b 0x0025d47c */ /* delay 0025d3ec */ c->r[4]=c->r[9];goto L_0025d47c;
L_0025d3f0:;
/* 0025d3f0: beq a1,v0,0x0025d450 */ {int taken=(c->r[5]==c->r[2]);/* delay 0025d3f4 */ c->r[2]=sx(UINT32_C(0x00000005));if(taken){goto L_0025d450;}}
/* 0025d3f8: b 0x0025d47c */ /* delay 0025d3fc */ c->r[4]=c->r[9];goto L_0025d47c;
L_0025d400:;
/* 0025d400: bnel s0,v1,0x0025d47c */ {int taken=(c->r[16]!=c->r[3]);if(taken){/* delay 0025d404 */ c->r[4]=c->r[9];goto L_0025d47c;}}
/* 0025d408: bnel s1,a0,0x0025d47c */ {int taken=(c->r[17]!=c->r[4]);if(taken){/* delay 0025d40c */ c->r[4]=c->r[9];goto L_0025d47c;}}
/* 0025d410: move a0,s2 */ c->r[4]=c->r[18];
/* 0025d414: jal 0x0025d1e8 */ c->r[31]=UINT64_C(0x0025d41c);/* delay 0025d418 */ c->r[5]=c->r[0];body_0025d1e8(c);
/* 0025d41c: b 0x0025d4a8 */ /* delay 0025d420 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0025d4a8;
L_0025d428:;
/* 0025d428: li v0,0x4 */ c->r[2]=sx(UINT32_C(0x00000004));
/* 0025d42c: bnel s0,v0,0x0025d47c */ {int taken=(c->r[16]!=c->r[2]);if(taken){/* delay 0025d430 */ c->r[4]=c->r[9];goto L_0025d47c;}}
/* 0025d434: bnel s1,a0,0x0025d47c */ {int taken=(c->r[17]!=c->r[4]);if(taken){/* delay 0025d438 */ c->r[4]=c->r[9];goto L_0025d47c;}}
/* 0025d43c: move a0,s2 */ c->r[4]=c->r[18];
/* 0025d440: jal 0x0025d1e8 */ c->r[31]=UINT64_C(0x0025d448);/* delay 0025d444 */ c->r[5]=sx(UINT32_C(0x00000001));body_0025d1e8(c);
/* 0025d448: b 0x0025d4a8 */ /* delay 0025d44c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0025d4a8;
L_0025d450:;
/* 0025d450: bnel s0,v0,0x0025d47c */ {int taken=(c->r[16]!=c->r[2]);if(taken){/* delay 0025d454 */ c->r[4]=c->r[9];goto L_0025d47c;}}
/* 0025d458: bnel s1,a0,0x0025d47c */ {int taken=(c->r[17]!=c->r[4]);if(taken){/* delay 0025d45c */ c->r[4]=c->r[9];goto L_0025d47c;}}
/* 0025d460: move a0,s2 */ c->r[4]=c->r[18];
/* 0025d464: jal 0x0025d1e8 */ c->r[31]=UINT64_C(0x0025d46c);/* delay 0025d468 */ c->r[5]=sx(UINT32_C(0x00000002));body_0025d1e8(c);
/* 0025d46c: b 0x0025d4a8 */ /* delay 0025d470 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0025d4a8;
L_0025d478:;
/* 0025d478: move a0,t1 */ c->r[4]=c->r[9];
L_0025d47c:;
/* 0025d47c: addiu a2,a2,0x1 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 0025d480: addu v1,a3,a0 */ c->r[3]=sx((uint32_t)c->r[7]+(uint32_t)c->r[4]);
/* 0025d484: lw v0,0xdd0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000dd0)));
/* 0025d488: slt v0,a2,v0 */ c->r[2]=less(c->r[6],c->r[2]);
/* 0025d48c: bne v0,zero,0x0025d350 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025d490 */ c->r[2]=sx((uint32_t)c->r[8]+(uint32_t)c->r[5]);if(taken){goto L_0025d350;}}
L_0025d494:;
/* 0025d494: addiu a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));
/* 0025d498: slti v0,a1,0x6 */ c->r[2]=less(c->r[5],sx(UINT32_C(0x00000006)));
/* 0025d49c: bnel v0,zero,0x0025d334 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0025d4a0 */ c->r[7]=sx((uint32_t)c->r[5]<<2u);goto L_0025d334;}}
/* 0025d4a4: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0025d4a8:;
/* 0025d4a8: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025d4ac: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0025d4b0: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0025d4b4: jr ra */ /* delay 0025d4b8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_0025d4c0(BattleStatusPairsValues *c){
/* 0025d4c0: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025d4c4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025d4c8: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0025d4cc: jal 0x00259cf8 */ c->r[31]=UINT64_C(0x0025d4d4);/* delay 0025d4d0 */ (void)0;body_00259cf8(c);
/* 0025d4d4: move s0,v0 */ c->r[16]=c->r[2];
/* 0025d4d8: jal 0x0025d2a0 */ c->r[31]=UINT64_C(0x0025d4e0);/* delay 0025d4dc */ c->r[4]=c->r[16];body_0025d2a0(c);
/* 0025d4e0: lw v0,0x14b4(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x000014b4)));
/* 0025d4e4: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025d4e8: ori v0,v0,0x10 */ c->r[2]=c->r[2]|UINT64_C(0x10);
/* 0025d4ec: sw v0,0x14b4(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x000014b4),(uint32_t)c->r[2]);
/* 0025d4f0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025d4f4: jr ra */ /* delay 0025d4f8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0025d6b8(BattleStatusPairsValues *c){
/* 0025d6b8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025d6bc: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0025d6c0: jal 0x0025d690 */ c->r[31]=UINT64_C(0x0025d6c8);/* delay 0025d6c4 */ (void)0;nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=GetTarSelProcessData();nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0025d6c8: lbu v0,0x8(v0) */ c->r[2]=*at((uint32_t)c->r[2]+UINT32_C(0x00000008));
/* 0025d6cc: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025d6d0: jr ra */ /* delay 0025d6d4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0025d6d8(BattleStatusPairsValues *c){
/* 0025d6d8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025d6dc: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025d6e0: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0025d6e4: jal 0x0025d690 */ c->r[31]=UINT64_C(0x0025d6ec);/* delay 0025d6e8 */ c->r[16]=c->r[4];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=GetTarSelProcessData();nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0025d6ec: sb s0,0x8(v0) */ *at((uint32_t)c->r[2]+UINT32_C(0x00000008))=(uint8_t)c->r[16];
/* 0025d6f0: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025d6f4: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025d6f8: jr ra */ /* delay 0025d6fc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0025d700(BattleStatusPairsValues *c){
/* 0025d700: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025d704: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025d708: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0025d70c: jal 0x0025d690 */ c->r[31]=UINT64_C(0x0025d714);/* delay 0025d710 */ c->r[16]=c->r[4];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=GetTarSelProcessData();nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0025d714: sw s0,0x2c(v0) */ sw((uint32_t)c->r[2]+UINT32_C(0x0000002c),(uint32_t)c->r[16]);
/* 0025d718: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025d71c: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025d720: jr ra */ /* delay 0025d724 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0025de40(BattleStatusPairsValues *c){
/* 0025de40: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0025de44: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025de48: move s0,a0 */ c->r[16]=c->r[4];
/* 0025de4c: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0025de50: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0025de54: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 0025de58: lb v0,0x12(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000012)));
/* 0025de5c: blezl v0,0x0025de68 */ {int taken=((neg(c->r[2])||!c->r[2]));if(taken){/* delay 0025de60 */ c->r[2]=sx(UINT32_C(0x00000002));goto L_0025de68;}}
/* 0025de64: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_0025de68:;
/* 0025de68: sb v0,0xc(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000c))=(uint8_t)c->r[2];
/* 0025de6c: sb zero,0xd(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000d))=(uint8_t)c->r[0];
/* 0025de70: lw a0,0x0(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0025de74: lh a1,0x10(s0) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[16]+UINT32_C(0x00000010)));
/* 0025de78: lw v0,0x10(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000010)));
/* 0025de7c: sll a1,a1,0x7 */ c->r[5]=sx((uint32_t)c->r[5]<<7u);
/* 0025de80: jal 0x002469c0 */ c->r[31]=UINT64_C(0x0025de88);/* delay 0025de84 */ c->r[5]=sx((uint32_t)c->r[2]+(uint32_t)c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitWorkPointer(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0025de88: lw v1,0x4(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 0025de8c: lh s2,0x78(v0) */ c->r[18]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000078)));
/* 0025de90: beq v1,zero,0x0025dec4 */ {int taken=(c->r[3]==c->r[0]);/* delay 0025de94 */ c->r[17]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000076)));if(taken){goto L_0025dec4;}}
/* 0025de98: jal 0x0029bae0 */ c->r[31]=UINT64_C(0x0025dea0);/* delay 0025de9c */ c->r[4]=sx(UINT32_C(0x00000001));body_0029bae0(c);
/* 0025dea0: bne v0,zero,0x0025dec8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025dea4 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0025dec8;}}
/* 0025dea8: lw v1,0x4(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 0025deac: lw v0,0x4(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000004)));
/* 0025deb0: andi v0,v0,0x80 */ c->r[2]=c->r[2]&UINT64_C(0x80);
/* 0025deb4: bne v0,zero,0x0025dec8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025deb8 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0025dec8;}}
/* 0025debc: li s1,-0x1 */ c->r[17]=sx(UINT32_C(0xffffffff));
/* 0025dec0: li s2,-0x1 */ c->r[18]=sx(UINT32_C(0xffffffff));
L_0025dec4:;
/* 0025dec4: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_0025dec8:;
/* 0025dec8: beq s1,v0,0x0025dee0 */ {int taken=(c->r[17]==c->r[2]);/* delay 0025decc */ c->r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_0025dee0;}}
/* 0025ded0: beql s1,v0,0x0025df38 */ {int taken=(c->r[17]==c->r[2]);if(taken){/* delay 0025ded4 */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000013)));goto L_0025df38;}}
/* 0025ded8: b 0x0025df8c */ /* delay 0025dedc */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0025df8c;
L_0025dee0:;
/* 0025dee0: lb v0,0x12(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000012)));
/* 0025dee4: blez v0,0x0025df88 */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 0025dee8 */ c->r[5]=*at((uint32_t)c->r[16]+UINT32_C(0x00000012));if(taken){goto L_0025df88;}}
/* 0025deec: sb s1,0xc(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000c))=(uint8_t)c->r[17];
/* 0025def0: blez v0,0x0025df88 */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 0025def4 */ c->r[4]=c->r[0];if(taken){goto L_0025df88;}}
/* 0025def8: lb v0,0x14(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000014)));
/* 0025defc: beql v0,s2,0x0025df88 */ {int taken=(c->r[2]==c->r[18]);if(taken){/* delay 0025df00 */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000d))=(uint8_t)c->r[0];goto L_0025df88;}}
/* 0025df04: sll v0,a1,0x18 */ c->r[2]=sx((uint32_t)c->r[5]<<24u);
L_0025df08:;
/* 0025df08: addiu a0,a0,0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));
/* 0025df0c: sra v0,v0,0x18 */ c->r[2]=sar((uint32_t)c->r[2],24u);
/* 0025df10: slt v0,a0,v0 */ c->r[2]=less(c->r[4],c->r[2]);
/* 0025df14: beq v0,zero,0x0025df88 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025df18 */ c->r[3]=sx((uint32_t)c->r[4]+(uint32_t)c->r[16]);if(taken){goto L_0025df88;}}
/* 0025df1c: lb v0,0x14(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[3]+UINT32_C(0x00000014)));
/* 0025df20: nop  */ (void)0;
/* 0025df24: bne v0,s2,0x0025df08 */ {int taken=(c->r[2]!=c->r[18]);/* delay 0025df28 */ c->r[2]=sx((uint32_t)c->r[5]<<24u);if(taken){goto L_0025df08;}}
/* 0025df2c: b 0x0025df88 */ /* delay 0025df30 */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000d))=(uint8_t)c->r[4];goto L_0025df88;
L_0025df38:;
/* 0025df38: blez v0,0x0025df88 */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 0025df3c */ c->r[5]=*at((uint32_t)c->r[16]+UINT32_C(0x00000013));if(taken){goto L_0025df88;}}
/* 0025df40: sb s1,0xc(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000c))=(uint8_t)c->r[17];
/* 0025df44: blez v0,0x0025df88 */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 0025df48 */ c->r[4]=c->r[0];if(taken){goto L_0025df88;}}
/* 0025df4c: lb v0,0x20(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000020)));
/* 0025df50: bne v0,s2,0x0025df60 */ {int taken=(c->r[2]!=c->r[18]);/* delay 0025df54 */ c->r[2]=sx((uint32_t)c->r[5]<<24u);if(taken){goto L_0025df60;}}
/* 0025df58: b 0x0025df88 */ /* delay 0025df5c */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000d))=(uint8_t)c->r[0];goto L_0025df88;
L_0025df60:;
/* 0025df60: addiu a0,a0,0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));
/* 0025df64: sra v0,v0,0x18 */ c->r[2]=sar((uint32_t)c->r[2],24u);
/* 0025df68: slt v0,a0,v0 */ c->r[2]=less(c->r[4],c->r[2]);
/* 0025df6c: beq v0,zero,0x0025df88 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025df70 */ c->r[3]=sx((uint32_t)c->r[4]+(uint32_t)c->r[16]);if(taken){goto L_0025df88;}}
/* 0025df74: lb v0,0x20(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[3]+UINT32_C(0x00000020)));
/* 0025df78: nop  */ (void)0;
/* 0025df7c: bne v0,s2,0x0025df60 */ {int taken=(c->r[2]!=c->r[18]);/* delay 0025df80 */ c->r[2]=sx((uint32_t)c->r[5]<<24u);if(taken){goto L_0025df60;}}
/* 0025df84: sb a0,0xd(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000d))=(uint8_t)c->r[4];
L_0025df88:;
/* 0025df88: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0025df8c:;
/* 0025df8c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025df90: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0025df94: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0025df98: jr ra */ /* delay 0025df9c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_0025dfa0(BattleStatusPairsValues *c){
/* 0025dfa0: addiu sp,sp,-0x40 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffc0));
/* 0025dfa4: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0025dfa8: move s1,a1 */ c->r[17]=c->r[5];
/* 0025dfac: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0025dfb0: move s2,a2 */ c->r[18]=c->r[6];
/* 0025dfb4: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0025dfb8: move s3,a3 */ c->r[19]=c->r[7];
/* 0025dfbc: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 0025dfc0: move s4,t0 */ c->r[20]=c->r[8];
/* 0025dfc4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025dfc8: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 0025dfcc: sd ra,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[31]);
/* 0025dfd0: jal 0x0025d690 */ c->r[31]=UINT64_C(0x0025dfd8);/* delay 0025dfd4 */ c->r[21]=c->r[4];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=GetTarSelProcessData();nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0025dfd8: move a0,s1 */ c->r[4]=c->r[17];
/* 0025dfdc: move a1,s2 */ c->r[5]=c->r[18];
/* 0025dfe0: move a2,s3 */ c->r[6]=c->r[19];
/* 0025dfe4: move a3,s4 */ c->r[7]=c->r[20];
/* 0025dfe8: jal 0x0025dc00 */ c->r[31]=UINT64_C(0x0025dff0);/* delay 0025dfec */ c->r[16]=c->r[2];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbSetSelectOkMark(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0025dff0: li v1,0x80 */ c->r[3]=sx(UINT32_C(0x00000080));
/* 0025dff4: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 0025dff8: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];nocturneBattleStatusPairsWriteFpr(0u,c->f[0]);
/* 0025dffc: beq v0,zero,0x0025e048 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025e000 */ c->r[4]=c->r[16];if(taken){goto L_0025e048;}}
/* 0025e004: sw v1,0x38(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000038),(uint32_t)c->r[3]);
/* 0025e008: swc1 f0,0x40(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000040),c->f[0]);
/* 0025e00c: sw v1,0x34(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000034),(uint32_t)c->r[3]);
/* 0025e010: swc1 f0,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),c->f[0]);
/* 0025e014: sw s5,0x4(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[21]);
/* 0025e018: sh s1,0x10(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000010),(uint16_t)c->r[17]);
/* 0025e01c: sb s2,0x9(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x00000009))=(uint8_t)c->r[18];
/* 0025e020: sb s3,0xa(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000a))=(uint8_t)c->r[19];
/* 0025e024: sb s4,0xb(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000b))=(uint8_t)c->r[20];
/* 0025e028: sw zero,0x2c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000002c),(uint32_t)c->r[0]);
/* 0025e02c: jal 0x0025de40 */ c->r[31]=UINT64_C(0x0025e034);/* delay 0025e030 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000030),(uint32_t)c->r[0]);body_0025de40(c);
/* 0025e034: jal 0x0025e100 */ c->r[31]=UINT64_C(0x0025e03c);/* delay 0025e038 */ c->r[4]=c->r[16];body_0025e100(c);
/* 0025e03c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0025e040: sb v0,0x8(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x00000008))=(uint8_t)c->r[2];
/* 0025e044: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_0025e048:;
/* 0025e048: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025e04c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025e050: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0025e054: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0025e058: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0025e05c: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 0025e060: ld ra,0x30(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0025e064: jr ra */ /* delay 0025e068 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000040));return;
}

static void body_0025e070(BattleStatusPairsValues *c){
/* 0025e070: lw a2,0x0(a0) */ c->r[6]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 0025e074: addiu v1,a1,-0x4 */ c->r[3]=sx((uint32_t)c->r[5]+UINT32_C(0xfffffffc));
/* 0025e078: sltiu v1,v1,0xa */ c->r[3]=(c->r[3]<sx(UINT32_C(0x0000000a)));
/* 0025e07c: lw v0,0x60(a2) */ c->r[2]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000060)));
/* 0025e080: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 0025e084: beq v0,zero,0x0025e0a0 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025e088 */ c->r[5]=less(c->r[5],sx(UINT32_C(0x00000004)));if(taken){goto L_0025e0a0;}}
/* 0025e08c: beql v1,zero,0x0025e0ac */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 0025e090 */ c->r[2]=c->r[0];goto L_0025e0ac;}}
/* 0025e094: jr ra */ /* delay 0025e098 */ c->r[2]=sx(UINT32_C(0x00000001));return;
L_0025e0a0:;
/* 0025e0a0: bne a1,zero,0x0025e0ac */ {int taken=(c->r[5]!=c->r[0]);/* delay 0025e0a4 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0025e0ac;}}
/* 0025e0a8: move v0,zero */ c->r[2]=c->r[0];
L_0025e0ac:;
/* 0025e0ac: jr ra */ /* delay 0025e0b0 */ (void)0;return;
}

static void body_0025e0b8(BattleStatusPairsValues *c){
/* 0025e0b8: lw a2,0x0(a0) */ c->r[6]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 0025e0bc: addiu v1,a1,-0x4 */ c->r[3]=sx((uint32_t)c->r[5]+UINT32_C(0xfffffffc));
/* 0025e0c0: sltiu v1,v1,0xa */ c->r[3]=(c->r[3]<sx(UINT32_C(0x0000000a)));
/* 0025e0c4: lw v0,0x60(a2) */ c->r[2]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000060)));
/* 0025e0c8: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 0025e0cc: beq v0,zero,0x0025e0e8 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025e0d0 */ c->r[5]=less(c->r[5],sx(UINT32_C(0x00000004)));if(taken){goto L_0025e0e8;}}
/* 0025e0d4: beql a1,zero,0x0025e0f4 */ {int taken=(c->r[5]==c->r[0]);if(taken){/* delay 0025e0d8 */ c->r[2]=c->r[0];goto L_0025e0f4;}}
/* 0025e0dc: jr ra */ /* delay 0025e0e0 */ c->r[2]=sx(UINT32_C(0x00000001));return;
L_0025e0e8:;
/* 0025e0e8: bne v1,zero,0x0025e0f4 */ {int taken=(c->r[3]!=c->r[0]);/* delay 0025e0ec */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0025e0f4;}}
/* 0025e0f0: move v0,zero */ c->r[2]=c->r[0];
L_0025e0f4:;
/* 0025e0f4: jr ra */ /* delay 0025e0f8 */ (void)0;return;
}

static void body_0025e100(BattleStatusPairsValues *c){
/* 0025e100: addiu sp,sp,-0x40 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffc0));
/* 0025e104: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0025e108: sd ra,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[31]);
/* 0025e10c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025e110: move s0,a0 */ c->r[16]=c->r[4];
/* 0025e114: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0025e118: move s1,zero */ c->r[17]=c->r[0];
/* 0025e11c: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0025e120: move s3,zero */ c->r[19]=c->r[0];
/* 0025e124: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 0025e128: li s4,0x2 */ c->r[20]=sx(UINT32_C(0x00000002));
/* 0025e12c: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 0025e130: move s5,zero */ c->r[21]=c->r[0];
/* 0025e134: nop  */ (void)0;
L_0025e138:;
/* 0025e138: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0025e13c: li a0,-0x9 */ c->r[4]=sx(UINT32_C(0xfffffff7));
/* 0025e140: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 0025e144: addu v1,s3,v1 */ c->r[3]=sx((uint32_t)c->r[19]+(uint32_t)c->r[3]);
/* 0025e148: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 0025e14c: and a0,v0,a0 */ c->r[4]=c->r[2]&c->r[4];
/* 0025e150: andi v0,v0,0x4 */ c->r[2]=c->r[2]&UINT64_C(0x4);
/* 0025e154: beq v0,zero,0x0025e23c */ {int taken=(c->r[2]==c->r[0]);/* delay 0025e158 */ sw((uint32_t)c->r[3]+UINT32_C(0x00000078),(uint32_t)c->r[4]);if(taken){goto L_0025e23c;}}
/* 0025e15c: lb v1,0x9(s0) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000009)));
/* 0025e160: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 0025e164: beq v1,a0,0x0025e1d8 */ {int taken=(c->r[3]==c->r[4]);/* delay 0025e168 */ c->r[18]=c->r[0];if(taken){goto L_0025e1d8;}}
/* 0025e16c: slti v0,v1,0x2 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000002)));
/* 0025e170: beq v0,zero,0x0025e188 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025e174 */ (void)0;if(taken){goto L_0025e188;}}
/* 0025e178: beql v1,zero,0x0025e198 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 0025e17c */ c->r[2]=*at((uint32_t)c->r[16]+UINT32_C(0x0000000c));goto L_0025e198;}}
/* 0025e180: b 0x0025e21c */ /* delay 0025e184 */ (void)0;goto L_0025e21c;
L_0025e188:;
/* 0025e188: beql v1,s4,0x0025e21c */ {int taken=(c->r[3]==c->r[20]);if(taken){/* delay 0025e18c */ c->r[18]=sx(UINT32_C(0x00000001));goto L_0025e21c;}}
/* 0025e190: b 0x0025e21c */ /* delay 0025e194 */ (void)0;goto L_0025e21c;
L_0025e198:;
/* 0025e198: beql v0,a0,0x0025e1b0 */ {int taken=(c->r[2]==c->r[4]);if(taken){/* delay 0025e19c */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x0000000d)));goto L_0025e1b0;}}
/* 0025e1a0: beql v0,s4,0x0025e1c8 */ {int taken=(c->r[2]==c->r[20]);if(taken){/* delay 0025e1a4 */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x0000000d)));goto L_0025e1c8;}}
/* 0025e1a8: b 0x0025e21c */ /* delay 0025e1ac */ (void)0;goto L_0025e21c;
L_0025e1b0:;
/* 0025e1b0: addu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[16]);
/* 0025e1b4: lb v1,0x14(v0) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000014)));
L_0025e1b8:;
/* 0025e1b8: bne v1,s1,0x0025e21c */ {int taken=(c->r[3]!=c->r[17]);/* delay 0025e1bc */ (void)0;if(taken){goto L_0025e21c;}}
/* 0025e1c0: b 0x0025e218 */ /* delay 0025e1c4 */ *at((uint32_t)c->r[16]+UINT32_C(0x0000000e))=(uint8_t)c->r[17];goto L_0025e218;
L_0025e1c8:;
/* 0025e1c8: addu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[16]);
/* 0025e1cc: b 0x0025e1b8 */ /* delay 0025e1d0 */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000020)));goto L_0025e1b8;
L_0025e1d8:;
/* 0025e1d8: lbu v0,0xc(s0) */ c->r[2]=*at((uint32_t)c->r[16]+UINT32_C(0x0000000c));
/* 0025e1dc: beq v0,v1,0x0025e1f8 */ {int taken=(c->r[2]==c->r[3]);/* delay 0025e1e0 */ c->r[4]=c->r[16];if(taken){goto L_0025e1f8;}}
/* 0025e1e4: beq v0,s4,0x0025e208 */ {int taken=(c->r[2]==c->r[20]);/* delay 0025e1e8 */ (void)0;if(taken){goto L_0025e208;}}
/* 0025e1ec: b 0x0025e21c */ /* delay 0025e1f0 */ (void)0;goto L_0025e21c;
L_0025e1f8:;
/* 0025e1f8: jal 0x0025e070 */ c->r[31]=UINT64_C(0x0025e200);/* delay 0025e1fc */ c->r[5]=c->r[17];body_0025e070(c);
/* 0025e200: b 0x0025e210 */ /* delay 0025e204 */ (void)0;goto L_0025e210;
L_0025e208:;
/* 0025e208: jal 0x0025e0b8 */ c->r[31]=UINT64_C(0x0025e210);/* delay 0025e20c */ c->r[5]=c->r[17];body_0025e0b8(c);
L_0025e210:;
/* 0025e210: beq v0,zero,0x0025e21c */ {int taken=(c->r[2]==c->r[0]);/* delay 0025e214 */ (void)0;if(taken){goto L_0025e21c;}}
L_0025e218:;
/* 0025e218: li s2,0x1 */ c->r[18]=sx(UINT32_C(0x00000001));
L_0025e21c:;
/* 0025e21c: beql s2,zero,0x0025e240 */ {int taken=(c->r[18]==c->r[0]);if(taken){/* delay 0025e220 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0025e240;}}
/* 0025e224: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0025e228: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 0025e22c: addu v1,s5,v1 */ c->r[3]=sx((uint32_t)c->r[21]+(uint32_t)c->r[3]);
/* 0025e230: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 0025e234: ori v0,v0,0x8 */ c->r[2]=c->r[2]|UINT64_C(0x8);
/* 0025e238: sw v0,0x78(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
L_0025e23c:;
/* 0025e23c: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
L_0025e240:;
/* 0025e240: addiu s5,s5,0xf0 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0x000000f0));
/* 0025e244: slti v0,s1,0x10 */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000010)));
/* 0025e248: bne v0,zero,0x0025e138 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025e24c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x000000f0));if(taken){goto L_0025e138;}}
/* 0025e250: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025e254: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025e258: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0025e25c: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0025e260: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0025e264: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 0025e268: ld ra,0x30(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0025e26c: jr ra */ /* delay 0025e270 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000040));return;
}

static void body_00279c30(BattleStatusPairsValues *c){
/* 00279c30: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00279c34: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 00279c38: jal 0x0027c2c0 */ c->r[31]=UINT64_C(0x00279c40);/* delay 00279c3c */ (void)0;body_0027c2c0(c);
/* 00279c40: jal 0x00282258 */ c->r[31]=UINT64_C(0x00279c48);/* delay 00279c44 */ (void)0;body_00282258(c);
/* 00279c48: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00279c4c: j 0x00281e10 */ /* delay 00279c50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_00281e10(c);return;
}

static void body_0027c2c0(BattleStatusPairsValues *c){
/* 0027c2c0: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0027c2c4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0027c2c8: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0027c2cc: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0027c2d4);/* delay 0027c2d0 */ (void)0;nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0027c2d4: move s0,v0 */ c->r[16]=c->r[2];
/* 0027c2d8: lb v0,-0x2fcb(gp) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[28]+UINT32_C(0xffffd035)));
/* 0027c2dc: bne v0,zero,0x0027c310 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0027c2e0 */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[28]+UINT32_C(0xffffd036)));if(taken){goto L_0027c310;}}
/* 0027c2e4: bne v0,zero,0x0027c310 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0027c2e8 */ (void)0;if(taken){goto L_0027c310;}}
/* 0027c2ec: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0027c2f0: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0027c2f8);/* delay 0027c2f4 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005398));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,1u,UINT32_C(0x0027c2f0),UINT32_C(0xf0ff0010));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0027c2f8: lw v1,0x60(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000060)));
/* 0027c2fc: lh v0,0x7a(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[16]+UINT32_C(0x0000007a)));
/* 0027c300: andi v1,v1,0x8 */ c->r[3]=c->r[3]&UINT64_C(0x8);
/* 0027c304: sw zero,-0x2fd4(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd02c),(uint32_t)c->r[0]);
/* 0027c308: sw v1,-0x2fe4(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd01c),(uint32_t)c->r[3]);
/* 0027c30c: sw v0,-0x2fe0(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd020),(uint32_t)c->r[2]);
L_0027c310:;
/* 0027c310: lui v0,0x8080 */ c->r[2]=sx(UINT32_C(0x80800000));
/* 0027c314: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0027c318: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0027c31c: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 0027c320: ori v0,v0,0x8080 */ c->r[2]=c->r[2]|UINT64_C(0x8080);
/* 0027c324: sb zero,-0x2fca(gp) */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd036))=(uint8_t)c->r[0];
/* 0027c328: sb v1,-0x2fcb(gp) */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd035))=(uint8_t)c->r[3];
/* 0027c32c: sw v0,-0x2fc8(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd038),(uint32_t)c->r[2]);
/* 0027c330: jr ra */ /* delay 0027c334 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0027fa78(BattleStatusPairsValues *c){
/* 0027fa78: sb zero,-0x2f70(gp) */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd090))=(uint8_t)c->r[0];
/* 0027fa7c: jr ra */ /* delay 0027fa80 */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd091))=(uint8_t)c->r[0];return;
}

static void body_0027fa98(BattleStatusPairsValues *c){
/* 0027fa98: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0027fa9c: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0027faa0: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0027faa8);/* delay 0027faa4 */ (void)0;nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0027faa8: lw a3,-0x5750(gp) */ c->r[7]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 0027faac: li v0,0x12c */ c->r[2]=sx(UINT32_C(0x0000012c));
/* 0027fab0: sw v0,-0x2f60(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd0a0),(uint32_t)c->r[2]);
/* 0027fab4: move t1,zero */ c->r[9]=c->r[0];
/* 0027fab8: lw v0,0x1924(a3) */ c->r[2]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00001924)));
/* 0027fabc: move t2,a3 */ c->r[10]=c->r[7];
/* 0027fac0: sw zero,-0x2f58(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd0a8),(uint32_t)c->r[0]);
/* 0027fac4: sw zero,-0x2f54(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd0ac),(uint32_t)c->r[0]);
/* 0027fac8: sw zero,-0x2f64(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd09c),(uint32_t)c->r[0]);
/* 0027facc: beq v0,zero,0x0027fb78 */ {int taken=(c->r[2]==c->r[0]);/* delay 0027fad0 */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd0a4),(uint32_t)c->r[0]);if(taken){goto L_0027fb78;}}
/* 0027fad4: lui v0,0x57 */ c->r[2]=sx(UINT32_C(0x00570000));
/* 0027fad8: li t4,0x800 */ c->r[12]=sx(UINT32_C(0x00000800));
/* 0027fadc: addiu t3,v0,0x5400 */ c->r[11]=sx((uint32_t)c->r[2]+UINT32_C(0x00005400));
/* 0027fae0: move t0,zero */ c->r[8]=c->r[0];
/* 0027fae4: addiu a0,a3,0x4 */ c->r[4]=sx((uint32_t)c->r[7]+UINT32_C(0x00000004));
L_0027fae8:;
/* 0027fae8: addu v1,t1,a0 */ c->r[3]=sx((uint32_t)c->r[9]+(uint32_t)c->r[4]);
/* 0027faec: addiu t1,t1,0x1 */ c->r[9]=sx((uint32_t)c->r[9]+UINT32_C(0x00000001));
/* 0027faf0: lbu a1,0x1910(v1) */ c->r[5]=*at((uint32_t)c->r[3]+UINT32_C(0x00001910));
/* 0027faf4: sll v0,a1,0x4 */ c->r[2]=sx((uint32_t)c->r[5]<<4u);
/* 0027faf8: subu v0,v0,a1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[5]);
/* 0027fafc: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 0027fb00: subu v0,v0,a1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[5]);
/* 0027fb04: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 0027fb08: addiu a2,v0,0xa50 */ c->r[6]=sx((uint32_t)c->r[2]+UINT32_C(0x00000a50));
/* 0027fb0c: addu a0,a0,a2 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[6]);
/* 0027fb10: lw a0,0x0(a0) */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 0027fb14: andi v0,a0,0x1 */ c->r[2]=c->r[4]&UINT64_C(0x1);
/* 0027fb18: beq v0,zero,0x0027fb60 */ {int taken=(c->r[2]==c->r[0]);/* delay 0027fb1c */ c->r[3]=c->r[4]&UINT64_C(0x4);if(taken){goto L_0027fb60;}}
/* 0027fb20: bnel v1,zero,0x0027fb64 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 0027fb24 */ c->r[7]=c->r[10];goto L_0027fb64;}}
/* 0027fb28: andi v0,a0,0x2 */ c->r[2]=c->r[4]&UINT64_C(0x2);
/* 0027fb2c: bnel v0,zero,0x0027fb64 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0027fb30 */ c->r[7]=c->r[10];goto L_0027fb64;}}
/* 0027fb34: addu a0,a3,a2 */ c->r[4]=sx((uint32_t)c->r[7]+(uint32_t)c->r[6]);
/* 0027fb38: lhu v0,0xa(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x0000000a));
/* 0027fb3c: beq v0,zero,0x0027fb54 */ {int taken=(c->r[2]==c->r[0]);/* delay 0027fb40 */ c->r[2]=sx((uint32_t)c->r[8]<<2u);if(taken){goto L_0027fb54;}}
/* 0027fb44: lhu v0,0x12(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x00000012));
/* 0027fb48: bne v0,t4,0x0027fb64 */ {int taken=(c->r[2]!=c->r[12]);/* delay 0027fb4c */ c->r[7]=c->r[10];if(taken){goto L_0027fb64;}}
/* 0027fb50: sll v0,t0,0x2 */ c->r[2]=sx((uint32_t)c->r[8]<<2u);
L_0027fb54:;
/* 0027fb54: addiu t0,t0,0x1 */ c->r[8]=sx((uint32_t)c->r[8]+UINT32_C(0x00000001));
/* 0027fb58: addu v0,v0,t3 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[11]);
/* 0027fb5c: sw a1,0x0(v0) */ sw((uint32_t)c->r[2]+UINT32_C(0x00000000),(uint32_t)c->r[5]);
L_0027fb60:;
/* 0027fb60: move a3,t2 */ c->r[7]=c->r[10];
L_0027fb64:;
/* 0027fb64: lw v0,0x1924(a3) */ c->r[2]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00001924)));
/* 0027fb68: sltu v0,t1,v0 */ c->r[2]=(c->r[9]<c->r[2]);
/* 0027fb6c: bne v0,zero,0x0027fae8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0027fb70 */ c->r[4]=sx((uint32_t)c->r[7]+UINT32_C(0x00000004));if(taken){goto L_0027fae8;}}
/* 0027fb74: sw t0,-0x2f5c(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd0a4),(uint32_t)c->r[8]);
L_0027fb78:;
/* 0027fb78: lui v0,0x8080 */ c->r[2]=sx(UINT32_C(0x80800000));
/* 0027fb7c: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0027fb80: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 0027fb84: ori v0,v0,0x8080 */ c->r[2]=c->r[2]|UINT64_C(0x8080);
/* 0027fb88: sb v1,-0x2f6f(gp) */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd091))=(uint8_t)c->r[3];
/* 0027fb8c: sw v0,-0x2f6c(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd094),(uint32_t)c->r[2]);
/* 0027fb90: sb zero,-0x2f68(gp) */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd098))=(uint8_t)c->r[0];
/* 0027fb94: sb v1,-0x2f70(gp) */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd090))=(uint8_t)c->r[3];
/* 0027fb98: jr ra */ /* delay 0027fb9c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00281e10(BattleStatusPairsValues *c){
/* 00281e10: lui v0,0x8080 */ c->r[2]=sx(UINT32_C(0x80800000));
/* 00281e14: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 00281e18: ori v0,v0,0x8080 */ c->r[2]=c->r[2]|UINT64_C(0x8080);
/* 00281e1c: sb v1,-0x2f34(gp) */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd0cc))=(uint8_t)c->r[3];
/* 00281e20: jr ra */ /* delay 00281e24 */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd0c8),(uint32_t)c->r[2]);return;
}

static void body_00282258(BattleStatusPairsValues *c){
/* 00282258: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0028225c: jr ra */ /* delay 00282260 */ *at((uint32_t)c->r[28]+UINT32_C(0xffffd0cd))=(uint8_t)c->r[2];return;
}

static void body_00288e18(BattleStatusPairsValues *c){
/* 00288e18: addiu sp,sp,-0x40 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffc0));
/* 00288e1c: lui v0,0x55 */ c->r[2]=sx(UINT32_C(0x00550000));
/* 00288e20: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00288e24: move s1,a0 */ c->r[17]=c->r[4];
/* 00288e28: addiu a0,v0,0x14f0 */ c->r[4]=sx((uint32_t)c->r[2]+UINT32_C(0x000014f0));
/* 00288e2c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00288e30: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00288e34: move s0,a1 */ c->r[16]=c->r[5];
/* 00288e38: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 00288e3c: move s3,t0 */ c->r[19]=c->r[8];
/* 00288e40: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 00288e44: move s4,a2 */ c->r[20]=c->r[6];
/* 00288e48: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 00288e4c: sd ra,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[31]);
/* 00288e50: jal 0x00101898 */ c->r[31]=UINT64_C(0x00288e58);/* delay 00288e54 */ c->r[21]=c->r[7];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3SearchProcessName(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00288e58: jal 0x00101ab0 */ c->r[31]=UINT64_C(0x00288e60);/* delay 00288e5c */ c->r[4]=c->r[2];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3GetProcessData(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00288e60: jal 0x00289450 */ c->r[31]=UINT64_C(0x00288e68);/* delay 00288e64 */ c->r[18]=c->r[2];body_00289450(c);
/* 00288e68: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 00288e6c: sw s1,0x4(s2) */ sw((uint32_t)c->r[18]+UINT32_C(0x00000004),(uint32_t)c->r[17]);
/* 00288e70: bne s4,a0,0x00288e88 */ {int taken=(c->r[20]!=c->r[4]);/* delay 00288e74 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000008),(uint32_t)c->r[16]);if(taken){goto L_00288e88;}}
/* 00288e78: lw v0,0x2c(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x0000002c)));
/* 00288e7c: lw v1,0x30(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000030)));
/* 00288e80: sw v0,0x24(s2) */ sw((uint32_t)c->r[18]+UINT32_C(0x00000024),(uint32_t)c->r[2]);
/* 00288e84: sw v1,0x28(s2) */ sw((uint32_t)c->r[18]+UINT32_C(0x00000028),(uint32_t)c->r[3]);
L_00288e88:;
/* 00288e88: beq s4,a0,0x00288eb0 */ {int taken=(c->r[20]==c->r[4]);/* delay 00288e8c */ sw((uint32_t)c->r[18]+UINT32_C(0x00000020),(uint32_t)c->r[19]);if(taken){goto L_00288eb0;}}
/* 00288e90: slti v0,s4,0x2 */ c->r[2]=less(c->r[20],sx(UINT32_C(0x00000002)));
/* 00288e94: bne v0,zero,0x00288f50 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00288e98 */ c->r[8]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000004)));if(taken){goto L_00288f50;}}
/* 00288e9c: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
/* 00288ea0: beq s4,v0,0x00288ed0 */ {int taken=(c->r[20]==c->r[2]);/* delay 00288ea4 */ (void)0;if(taken){goto L_00288ed0;}}
/* 00288ea8: b 0x00288f54 */ /* delay 00288eac */ c->r[6]=sx(UINT32_C(0x00ff0000));goto L_00288f54;
L_00288eb0:;
/* 00288eb0: lw a0,0x24(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000024)));
/* 00288eb4: move a2,zero */ c->r[6]=c->r[0];
/* 00288eb8: jal 0x001cea58 */ c->r[31]=UINT64_C(0x00288ec0);/* delay 00288ebc */ c->r[5]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000028)));body_001cea58(c);
/* 00288ec0: sra v0,v0,0x4 */ c->r[2]=sar((uint32_t)c->r[2],4u);
/* 00288ec4: b 0x00288fd8 */ /* delay 00288ec8 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000018),(uint32_t)c->r[2]);goto L_00288fd8;
L_00288ed0:;
/* 00288ed0: lui a2,0xff */ c->r[6]=sx(UINT32_C(0x00ff0000));
/* 00288ed4: move t1,zero */ c->r[9]=c->r[0];
/* 00288ed8: move a3,s3 */ c->r[7]=c->r[19];
/* 00288edc: move a1,zero */ c->r[5]=c->r[0];
/* 00288ee0: ori a2,a2,0x51 */ c->r[6]=c->r[6]|UINT64_C(0x51);
/* 00288ee4: jal 0x001ca258 */ c->r[31]=UINT64_C(0x00288eec);/* delay 00288ee8 */ c->r[4]=c->r[0];body_001ca258(c);
/* 00288eec: move s0,v0 */ c->r[16]=c->r[2];
/* 00288ef0: jal 0x001c8268 */ c->r[31]=UINT64_C(0x00288ef8);/* delay 00288ef4 */ c->r[4]=c->r[16];body_001c8268(c);
/* 00288ef8: move a0,s0 */ c->r[4]=c->r[16];
/* 00288efc: jal 0x001c6ff8 */ c->r[31]=UINT64_C(0x00288f04);/* delay 00288f00 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000018),(uint32_t)c->r[2]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frDestroyFontRequestAfter(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00288f04: move a0,zero */ c->r[4]=c->r[0];
/* 00288f08: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
/* 00288f0c: move a2,zero */ c->r[6]=c->r[0];
/* 00288f10: jal 0x001c9d60 */ c->r[31]=UINT64_C(0x00288f18);/* delay 00288f14 */ c->r[7]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2FontAppendResourceName(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00288f18: move s0,v0 */ c->r[16]=c->r[2];
/* 00288f1c: lw v0,0x18(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000018)));
/* 00288f20: move a0,s0 */ c->r[4]=c->r[16];
/* 00288f24: addiu v0,v0,0xa */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x0000000a));
/* 00288f28: jal 0x001c8268 */ c->r[31]=UINT64_C(0x00288f30);/* delay 00288f2c */ sw((uint32_t)c->r[18]+UINT32_C(0x0000001c),(uint32_t)c->r[2]);body_001c8268(c);
/* 00288f30: lw v1,0x18(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000018)));
/* 00288f34: move a0,s0 */ c->r[4]=c->r[16];
/* 00288f38: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00288f3c: addiu v1,v1,0xa */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x0000000a));
/* 00288f40: jal 0x001c6ff8 */ c->r[31]=UINT64_C(0x00288f48);/* delay 00288f44 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000018),(uint32_t)c->r[3]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frDestroyFontRequestAfter(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00288f48: b 0x00288fdc */ /* delay 00288f4c */ sw((uint32_t)c->r[18]+UINT32_C(0x00000010),(uint32_t)c->r[21]);goto L_00288fdc;
L_00288f50:;
/* 00288f50: lui a2,0xff */ c->r[6]=sx(UINT32_C(0x00ff0000));
L_00288f54:;
/* 00288f54: lw a3,0x20(s2) */ c->r[7]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000020)));
/* 00288f58: move a1,zero */ c->r[5]=c->r[0];
/* 00288f5c: ori a2,a2,0x51 */ c->r[6]=c->r[6]|UINT64_C(0x51);
/* 00288f60: move t1,zero */ c->r[9]=c->r[0];
/* 00288f64: jal 0x001ca258 */ c->r[31]=UINT64_C(0x00288f6c);/* delay 00288f68 */ c->r[4]=c->r[0];body_001ca258(c);
/* 00288f6c: move s0,v0 */ c->r[16]=c->r[2];
/* 00288f70: jal 0x001c8268 */ c->r[31]=UINT64_C(0x00288f78);/* delay 00288f74 */ c->r[4]=c->r[16];body_001c8268(c);
/* 00288f78: move a0,s0 */ c->r[4]=c->r[16];
/* 00288f7c: jal 0x001c6ff8 */ c->r[31]=UINT64_C(0x00288f84);/* delay 00288f80 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000018),(uint32_t)c->r[2]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frDestroyFontRequestAfter(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00288f84: lw t0,0x8(s2) */ c->r[8]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000008)));
/* 00288f88: beq t0,zero,0x00288fd8 */ {int taken=(c->r[8]==c->r[0]);/* delay 00288f8c */ c->r[6]=sx(UINT32_C(0x00ff0000));if(taken){goto L_00288fd8;}}
/* 00288f90: lw a3,0x20(s2) */ c->r[7]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000020)));
/* 00288f94: move a0,zero */ c->r[4]=c->r[0];
/* 00288f98: move a1,zero */ c->r[5]=c->r[0];
/* 00288f9c: ori a2,a2,0x51 */ c->r[6]=c->r[6]|UINT64_C(0x51);
/* 00288fa0: jal 0x001ca258 */ c->r[31]=UINT64_C(0x00288fa8);/* delay 00288fa4 */ c->r[9]=c->r[0];body_001ca258(c);
/* 00288fa8: move s0,v0 */ c->r[16]=c->r[2];
/* 00288fac: lw v0,0x18(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000018)));
/* 00288fb0: move a0,s0 */ c->r[4]=c->r[16];
/* 00288fb4: addiu v0,v0,0xa */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x0000000a));
/* 00288fb8: jal 0x001c8268 */ c->r[31]=UINT64_C(0x00288fc0);/* delay 00288fbc */ sw((uint32_t)c->r[18]+UINT32_C(0x0000001c),(uint32_t)c->r[2]);body_001c8268(c);
/* 00288fc0: lw v1,0x18(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000018)));
/* 00288fc4: move a0,s0 */ c->r[4]=c->r[16];
/* 00288fc8: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00288fcc: addiu v1,v1,0xa */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x0000000a));
/* 00288fd0: jal 0x001c6ff8 */ c->r[31]=UINT64_C(0x00288fd8);/* delay 00288fd4 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000018),(uint32_t)c->r[3]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=frDestroyFontRequestAfter(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
L_00288fd8:;
/* 00288fd8: sw s5,0x10(s2) */ sw((uint32_t)c->r[18]+UINT32_C(0x00000010),(uint32_t)c->r[21]);
L_00288fdc:;
/* 00288fdc: sw s4,0x0(s2) */ sw((uint32_t)c->r[18]+UINT32_C(0x00000000),(uint32_t)c->r[20]);
/* 00288fe0: sw zero,0xc(s2) */ sw((uint32_t)c->r[18]+UINT32_C(0x0000000c),(uint32_t)c->r[0]);
/* 00288fe4: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00288fe8: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00288fec: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00288ff0: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00288ff4: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00288ff8: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 00288ffc: ld ra,0x30(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 00289000: jr ra */ /* delay 00289004 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000040));return;
}

static void body_002892a8(BattleStatusPairsValues *c){
/* 002892a8: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002892ac: move v1,a2 */ c->r[3]=c->r[6];
/* 002892b0: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 002892b4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002892b8: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002892bc: move s1,a1 */ c->r[17]=c->r[5];
/* 002892c0: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 002892c4: move a2,a3 */ c->r[6]=c->r[7];
/* 002892c8: move a1,zero */ c->r[5]=c->r[0];
/* 002892cc: bne v1,v0,0x002892dc */ {int taken=(c->r[3]!=c->r[2]);/* delay 002892d0 */ c->r[16]=c->r[4];if(taken){goto L_002892dc;}}
/* 002892d4: li v0,0xa */ c->r[2]=sx(UINT32_C(0x0000000a));
/* 002892d8: movz v1,v0,a3 */ if(c->r[7]==0){c->r[3]=c->r[2];}
L_002892dc:;
/* 002892dc: bltzl v1,0x002892f0 */ {int taken=(neg(c->r[3]));if(taken){/* delay 002892e0 */ c->r[4]=c->r[16];goto L_002892f0;}}
/* 002892e4: jal 0x001ce5e8 */ c->r[31]=UINT64_C(0x002892ec);/* delay 002892e8 */ c->r[7]=c->r[3];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);itfMesMngSetVar(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002892ec: move a0,s0 */ c->r[4]=c->r[16];
L_002892f0:;
/* 002892f0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002892f4: move a1,s1 */ c->r[5]=c->r[17];
/* 002892f8: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002892fc: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00289300: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 00289304: j 0x00289310 */ /* delay 00289308 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));body_00289310(c);return;
}

static void body_00289310(BattleStatusPairsValues *c){
/* 00289310: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00289314: lui v0,0x55 */ c->r[2]=sx(UINT32_C(0x00550000));
/* 00289318: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0028931c: move s1,a0 */ c->r[17]=c->r[4];
/* 00289320: addiu a0,v0,0x14f0 */ c->r[4]=sx((uint32_t)c->r[2]+UINT32_C(0x000014f0));
/* 00289324: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00289328: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0028932c: move s2,a2 */ c->r[18]=c->r[6];
/* 00289330: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 00289334: jal 0x00101898 */ c->r[31]=UINT64_C(0x0028933c);/* delay 00289338 */ c->r[16]=c->r[5];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3SearchProcessName(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028933c: jal 0x00101ab0 */ c->r[31]=UINT64_C(0x00289344);/* delay 00289340 */ c->r[4]=c->r[2];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3GetProcessData(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00289344: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 00289348: sw s0,0x30(v0) */ sw((uint32_t)c->r[2]+UINT32_C(0x00000030),(uint32_t)c->r[16]);
/* 0028934c: beq s2,v1,0x002893b8 */ {int taken=(c->r[18]==c->r[3]);/* delay 00289350 */ sw((uint32_t)c->r[2]+UINT32_C(0x0000002c),(uint32_t)c->r[17]);if(taken){goto L_002893b8;}}
/* 00289354: slti v0,s2,0x2 */ c->r[2]=less(c->r[18],sx(UINT32_C(0x00000002)));
/* 00289358: beql v0,zero,0x00289370 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028935c */ c->r[2]=sx(UINT32_C(0x00000002));goto L_00289370;}}
/* 00289360: beq s2,zero,0x00289388 */ {int taken=(c->r[18]==c->r[0]);/* delay 00289364 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_00289388;}}
/* 00289368: b 0x0028943c */ /* delay 0028936c */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));goto L_0028943c;
L_00289370:;
/* 00289370: beq s2,v0,0x002893e8 */ {int taken=(c->r[18]==c->r[2]);/* delay 00289374 */ c->r[2]=sx(UINT32_C(0x00000003));if(taken){goto L_002893e8;}}
/* 00289378: beq s2,v0,0x00289418 */ {int taken=(c->r[18]==c->r[2]);/* delay 0028937c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_00289418;}}
/* 00289380: b 0x0028943c */ /* delay 00289384 */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));goto L_0028943c;
L_00289388:;
/* 00289388: lui t0,0x89fe */ c->r[8]=sx(UINT32_C(0x89fe0000));
/* 0028938c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00289390: move a0,zero */ c->r[4]=c->r[0];
/* 00289394: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00289398: move a1,zero */ c->r[5]=c->r[0];
/* 0028939c: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002893a0: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 002893a4: li a3,0x2d */ c->r[7]=sx(UINT32_C(0x0000002d));
/* 002893a8: ori t0,t0,0xff80 */ c->r[8]=c->r[8]|UINT64_C(0xff80);
/* 002893ac: j 0x00288e18 */ /* delay 002893b0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));body_00288e18(c);return;
L_002893b8:;
/* 002893b8: lui t0,0x89fe */ c->r[8]=sx(UINT32_C(0x89fe0000));
/* 002893bc: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002893c0: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002893c4: move a0,zero */ c->r[4]=c->r[0];
/* 002893c8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002893cc: move a1,zero */ c->r[5]=c->r[0];
/* 002893d0: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002893d4: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 002893d8: li a3,0x2d */ c->r[7]=sx(UINT32_C(0x0000002d));
/* 002893dc: ori t0,t0,0xff80 */ c->r[8]=c->r[8]|UINT64_C(0xff80);
/* 002893e0: j 0x00288e18 */ /* delay 002893e4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));body_00288e18(c);return;
L_002893e8:;
/* 002893e8: lui t0,0xa09d */ c->r[8]=sx(UINT32_C(0xa09d0000));
/* 002893ec: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002893f0: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002893f4: move a0,zero */ c->r[4]=c->r[0];
/* 002893f8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002893fc: move a1,zero */ c->r[5]=c->r[0];
/* 00289400: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00289404: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 00289408: li a3,0x14 */ c->r[7]=sx(UINT32_C(0x00000014));
/* 0028940c: ori t0,t0,0xc380 */ c->r[8]=c->r[8]|UINT64_C(0xc380);
/* 00289410: j 0x00288e18 */ /* delay 00289414 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));body_00288e18(c);return;
L_00289418:;
/* 00289418: lui t0,0x89fe */ c->r[8]=sx(UINT32_C(0x89fe0000));
/* 0028941c: move a0,zero */ c->r[4]=c->r[0];
/* 00289420: move a1,zero */ c->r[5]=c->r[0];
/* 00289424: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 00289428: li a3,0x1e */ c->r[7]=sx(UINT32_C(0x0000001e));
/* 0028942c: jal 0x00288e18 */ c->r[31]=UINT64_C(0x00289434);/* delay 00289430 */ c->r[8]=c->r[8]|UINT64_C(0xff80);body_00288e18(c);
/* 00289434: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00289438: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
L_0028943c:;
/* 0028943c: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00289440: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00289444: jr ra */ /* delay 00289448 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00289450(BattleStatusPairsValues *c){
/* 00289450: lui a0,0x55 */ c->r[4]=sx(UINT32_C(0x00550000));
/* 00289454: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00289458: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0028945c: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 00289460: jal 0x00101898 */ c->r[31]=UINT64_C(0x00289468);/* delay 00289464 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000014f0));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3SearchProcessName(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00289468: jal 0x00101ab0 */ c->r[31]=UINT64_C(0x00289470);/* delay 0028946c */ c->r[4]=c->r[2];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=dds3GetProcessData(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00289470: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
/* 00289474: move s0,v0 */ c->r[16]=c->r[2];
/* 00289478: lw v0,0x4(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 0028947c: bne v0,zero,0x002894a8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00289480 */ c->r[4]=sx(UINT32_C(0x00000001));if(taken){goto L_002894a8;}}
/* 00289484: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00289488: bnel v1,a0,0x002894d0 */ {int taken=(c->r[3]!=c->r[4]);if(taken){/* delay 0028948c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002894d0;}}
/* 00289490: lw v0,0x24(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));
/* 00289494: bltzl v0,0x002894d0 */ {int taken=(neg(c->r[2]));if(taken){/* delay 00289498 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002894d0;}}
/* 0028949c: b 0x002894b0 */ /* delay 002894a0 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[0]);goto L_002894b0;
L_002894a8:;
/* 002894a8: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 002894ac: sw zero,0x4(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[0]);
L_002894b0:;
/* 002894b0: bne v1,a1,0x002894cc */ {int taken=(c->r[3]!=c->r[5]);/* delay 002894b4 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000008),(uint32_t)c->r[0]);if(taken){goto L_002894cc;}}
/* 002894b8: lw a0,0x24(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));
/* 002894bc: jal 0x001cdd78 */ c->r[31]=UINT64_C(0x002894c4);/* delay 002894c0 */ c->r[5]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);itfMesMngRequestMessageRelease(c->r[4],c->r[5]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002894c4: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
/* 002894c8: sw v0,0x24(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000024),(uint32_t)c->r[2]);
L_002894cc:;
/* 002894cc: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_002894d0:;
/* 002894d0: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002894d4: jr ra */ /* delay 002894d8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028d090(BattleStatusPairsValues *c){
/* 0028d090: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028d094: li a1,0x7f */ c->r[5]=sx(UINT32_C(0x0000007f));
/* 0028d098: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0028d09c: li a2,0x3f */ c->r[6]=sx(UINT32_C(0x0000003f));
/* 0028d0a0: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028d0a4: j 0x002c18d8 */ /* delay 0028d0a8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2SoundPlay(c->r[4],c->r[5],c->r[6]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);return;
}

static void body_0028e3c8(BattleStatusPairsValues *c){
/* 0028e3c8: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 0028e3cc: move a1,zero */ c->r[5]=c->r[0];
/* 0028e3d0: sd s0,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[16]);
/* 0028e3d4: move s0,a0 */ c->r[16]=c->r[4];
/* 0028e3d8: sd ra,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[31]);
/* 0028e3dc: move a2,zero */ c->r[6]=c->r[0];
/* 0028e3e0: move a0,zero */ c->r[4]=c->r[0];
/* 0028e3e4: lw a3,0x0(s0) */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0028e3e8: lw v1,0x0(a3) */ c->r[3]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00000000)));
/* 0028e3ec: nop  */ (void)0;
L_0028e3f0:;
/* 0028e3f0: addu v1,a0,v1 */ c->r[3]=sx((uint32_t)c->r[4]+(uint32_t)c->r[3]);
/* 0028e3f4: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 0028e3f8: andi v0,v0,0x4 */ c->r[2]=c->r[2]&UINT64_C(0x4);
/* 0028e3fc: beq v0,zero,0x0028e410 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e400 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000000f0));if(taken){goto L_0028e410;}}
/* 0028e404: addu v0,sp,a1 */ c->r[2]=sx((uint32_t)c->r[29]+(uint32_t)c->r[5]);
/* 0028e408: addiu a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));
/* 0028e40c: sb a2,0x0(v0) */ *at((uint32_t)c->r[2]+UINT32_C(0x00000000))=(uint8_t)c->r[6];
L_0028e410:;
/* 0028e410: addiu a2,a2,0x1 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 0028e414: slti v0,a2,0x10 */ c->r[2]=less(c->r[6],sx(UINT32_C(0x00000010)));
/* 0028e418: bnel v0,zero,0x0028e3f0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028e41c */ c->r[3]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00000000)));goto L_0028e3f0;}}
/* 0028e420: blezl a1,0x0028e460 */ {int taken=((neg(c->r[5])||!c->r[5]));if(taken){/* delay 0028e424 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028e460;}}
/* 0028e428: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x0028e430);/* delay 0028e42c */ c->r[4]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]?(uint32_t *)at((uint32_t)c->r[4]):NULL,(uint32_t)c->r[5]));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e430: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0028e434: addu v0,sp,v0 */ c->r[2]=sx((uint32_t)c->r[29]+(uint32_t)c->r[2]);
/* 0028e438: lb a2,0x0(v0) */ c->r[6]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 0028e43c: lw a0,0x0(v1) */ c->r[4]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 0028e440: sll v0,a2,0x4 */ c->r[2]=sx((uint32_t)c->r[6]<<4u);
/* 0028e444: subu v0,v0,a2 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[6]);
/* 0028e448: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 0028e44c: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 0028e450: lw v1,0x78(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000078)));
/* 0028e454: ori v1,v1,0x8 */ c->r[3]=c->r[3]|UINT64_C(0x8);
/* 0028e458: sw v1,0x78(v0) */ sw((uint32_t)c->r[2]+UINT32_C(0x00000078),(uint32_t)c->r[3]);
/* 0028e45c: ld s0,0x20(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
L_0028e460:;
/* 0028e460: ld ra,0x28(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 0028e464: jr ra */ /* delay 0028e468 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_0028e470(BattleStatusPairsValues *c){
/* 0028e470: lw v0,0x0(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 0028e474: li a1,0xf */ c->r[5]=sx(UINT32_C(0x0000000f));
/* 0028e478: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 0028e47c: nop  */ (void)0;
L_0028e480:;
/* 0028e480: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 0028e484: ori a0,v0,0x8 */ c->r[4]=c->r[2]|UINT64_C(0x8);
/* 0028e488: andi v0,v0,0x4 */ c->r[2]=c->r[2]&UINT64_C(0x4);
/* 0028e48c: bnel v0,zero,0x0028e494 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028e490 */ sw((uint32_t)c->r[3]+UINT32_C(0x00000078),(uint32_t)c->r[4]);goto L_0028e494;}}
L_0028e494:;
/* 0028e494: addiu a1,a1,-0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0xffffffff));
/* 0028e498: nop  */ (void)0;
/* 0028e49c: bgez a1,0x0028e480 */ {int taken=(!neg(c->r[5]));/* delay 0028e4a0 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x000000f0));if(taken){goto L_0028e480;}}
/* 0028e4a4: jr ra */ /* delay 0028e4a8 */ (void)0;return;
}

static void body_0028e4b0(BattleStatusPairsValues *c){
/* 0028e4b0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0028e4b4: move t1,a1 */ c->r[9]=c->r[5];
/* 0028e4b8: sd s0,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[16]);
/* 0028e4bc: move s0,a0 */ c->r[16]=c->r[4];
/* 0028e4c0: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 0028e4c4: move a2,sp */ c->r[6]=c->r[29];
/* 0028e4c8: addiu a3,sp,0x4 */ c->r[7]=sx((uint32_t)c->r[29]+UINT32_C(0x00000004));
/* 0028e4cc: addiu t0,sp,0x8 */ c->r[8]=sx((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028e4d0: lw a1,0x2c(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e4d4: sw zero,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[0]);
/* 0028e4d8: sw zero,0x4(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint32_t)c->r[0]);
/* 0028e4dc: jal 0x00258de8 */ c->r[31]=UINT64_C(0x0028e4e4);/* delay 0028e4e0 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),(uint32_t)c->r[0]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);nbGetTargetTypeRuleArea(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8],c->r[9]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e4e4: lw a1,0x0(sp) */ c->r[5]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000000)));
/* 0028e4e8: lw a0,0x30(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000030)));
/* 0028e4ec: lw a2,0x4(sp) */ c->r[6]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000004)));
/* 0028e4f0: jal 0x0025dc00 */ c->r[31]=UINT64_C(0x0028e4f8);/* delay 0028e4f4 */ c->r[7]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000008)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbSetSelectOkMark(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e4f8: beql v0,zero,0x0028e554 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028e4fc */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));goto L_0028e554;}}
/* 0028e500: lw v0,0x0(sp) */ c->r[2]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000000)));
/* 0028e504: beq v0,zero,0x0028e528 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e508 */ (void)0;if(taken){goto L_0028e528;}}
/* 0028e50c: bltz v0,0x0028e540 */ {int taken=(neg(c->r[2]));/* delay 0028e510 */ c->r[2]=less(c->r[2],sx(UINT32_C(0x00000003)));if(taken){goto L_0028e540;}}
/* 0028e514: beq v0,zero,0x0028e540 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e518 */ (void)0;if(taken){goto L_0028e540;}}
/* 0028e51c: b 0x0028e538 */ /* delay 0028e520 */ (void)0;goto L_0028e538;
L_0028e528:;
/* 0028e528: jal 0x0028e3c8 */ c->r[31]=UINT64_C(0x0028e530);/* delay 0028e52c */ c->r[4]=c->r[16];body_0028e3c8(c);
/* 0028e530: b 0x0028e540 */ /* delay 0028e534 */ (void)0;goto L_0028e540;
L_0028e538:;
/* 0028e538: jal 0x0028e470 */ c->r[31]=UINT64_C(0x0028e540);/* delay 0028e53c */ c->r[4]=c->r[16];body_0028e470(c);
L_0028e540:;
/* 0028e540: jal 0x00246b68 */ c->r[31]=UINT64_C(0x0028e548);/* delay 0028e544 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetSelectBit(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e548: sw v0,0x3c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000003c),(uint32_t)c->r[2]);
/* 0028e54c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0028e550: ld s0,0x10(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
L_0028e554:;
/* 0028e554: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0028e558: jr ra */ /* delay 0028e55c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_0028e560(BattleStatusPairsValues *c){
/* 0028e560: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
/* 0028e564: beq a1,v0,0x0028e580 */ {int taken=(c->r[5]==c->r[2]);/* delay 0028e568 */ c->r[2]=sx(UINT32_C(0x00000003));if(taken){goto L_0028e580;}}
/* 0028e56c: beq a1,v0,0x0028e5a0 */ {int taken=(c->r[5]==c->r[2]);/* delay 0028e570 */ c->r[2]=c->r[0];if(taken){goto L_0028e5a0;}}
/* 0028e574: b 0x0028e5bc */ /* delay 0028e578 */ (void)0;goto L_0028e5bc;
L_0028e580:;
/* 0028e580: slti v0,a0,0x2a */ c->r[2]=less(c->r[4],sx(UINT32_C(0x0000002a)));
/* 0028e584: beq v0,zero,0x0028e5bc */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e588 */ c->r[2]=c->r[0];if(taken){goto L_0028e5bc;}}
/* 0028e58c: slti v0,a0,0x24 */ c->r[2]=less(c->r[4],sx(UINT32_C(0x00000024)));
/* 0028e590: bnel v0,zero,0x0028e5bc */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028e594 */ c->r[2]=c->r[0];goto L_0028e5bc;}}
/* 0028e598: jr ra */ /* delay 0028e59c */ c->r[2]=sx(UINT32_C(0x00000001));return;
L_0028e5a0:;
/* 0028e5a0: slti v0,a0,0x45 */ c->r[2]=less(c->r[4],sx(UINT32_C(0x00000045)));
/* 0028e5a4: beq v0,zero,0x0028e5bc */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e5a8 */ c->r[2]=c->r[0];if(taken){goto L_0028e5bc;}}
/* 0028e5ac: slti v1,a0,0x40 */ c->r[3]=less(c->r[4],sx(UINT32_C(0x00000040)));
/* 0028e5b0: beq v1,zero,0x0028e5bc */ {int taken=(c->r[3]==c->r[0]);/* delay 0028e5b4 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0028e5bc;}}
/* 0028e5b8: move v0,zero */ c->r[2]=c->r[0];
L_0028e5bc:;
/* 0028e5bc: jr ra */ /* delay 0028e5c0 */ (void)0;return;
}

static void body_0028e5c8(BattleStatusPairsValues *c){
/* 0028e5c8: addiu sp,sp,-0xd0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffff30));
/* 0028e5cc: sd s0,0x80(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000080),c->r[16]);
/* 0028e5d0: move s0,a0 */ c->r[16]=c->r[4];
/* 0028e5d4: sd s7,0xb8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000b8),c->r[23]);
/* 0028e5d8: move s7,zero */ c->r[23]=c->r[0];
/* 0028e5dc: sd s8,0xc0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000c0),c->r[30]);
/* 0028e5e0: move s8,a1 */ c->r[30]=c->r[5];
/* 0028e5e4: sd s1,0x88(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000088),c->r[17]);
/* 0028e5e8: sd s2,0x90(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000090),c->r[18]);
/* 0028e5ec: sd s3,0x98(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000098),c->r[19]);
/* 0028e5f0: sd s4,0xa0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000a0),c->r[20]);
/* 0028e5f4: sd s5,0xa8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000a8),c->r[21]);
/* 0028e5f8: sd s6,0xb0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000b0),c->r[22]);
/* 0028e5fc: sd ra,0xc8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000c8),c->r[31]);
/* 0028e600: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0028e604: jal 0x0026a468 */ c->r[31]=UINT64_C(0x0028e60c);/* delay 0028e608 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbCheckFormationPlayerSide(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e60c: beql v0,zero,0x0028e670 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028e610 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));goto L_0028e670;}}
/* 0028e614: lw s2,0x2c(s0) */ c->r[18]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e618: lhu v0,0x38(s2) */ c->r[2]=hword((uint32_t)c->r[18]+UINT32_C(0x00000038));
/* 0028e61c: beq v0,zero,0x0028e704 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e620 */ c->r[22]=c->r[0];if(taken){goto L_0028e704;}}
/* 0028e624: addiu s1,s2,0x3a */ c->r[17]=sx((uint32_t)c->r[18]+UINT32_C(0x0000003a));
/* 0028e628: move s3,sp */ c->r[19]=c->r[29];
/* 0028e62c: lhu s0,0x0(s1) */ c->r[16]=hword((uint32_t)c->r[17]+UINT32_C(0x00000000));
L_0028e630:;
/* 0028e630: addiu s1,s1,0x2 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000002));
/* 0028e634: move a1,s8 */ c->r[5]=c->r[30];
/* 0028e638: jal 0x0028e560 */ c->r[31]=UINT64_C(0x0028e640);/* delay 0028e63c */ c->r[4]=c->r[16];body_0028e560(c);
/* 0028e640: beql v0,zero,0x0028e658 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028e644 */ c->r[2]=hword((uint32_t)c->r[18]+UINT32_C(0x00000038));goto L_0028e658;}}
/* 0028e648: sh s0,0x0(s3) */ sh((uint32_t)c->r[19]+UINT32_C(0x00000000),(uint16_t)c->r[16]);
/* 0028e64c: addiu s3,s3,0x2 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000002));
/* 0028e650: addiu s7,s7,0x1 */ c->r[23]=sx((uint32_t)c->r[23]+UINT32_C(0x00000001));
/* 0028e654: lhu v0,0x38(s2) */ c->r[2]=hword((uint32_t)c->r[18]+UINT32_C(0x00000038));
L_0028e658:;
/* 0028e658: addiu s6,s6,0x1 */ c->r[22]=sx((uint32_t)c->r[22]+UINT32_C(0x00000001));
/* 0028e65c: slt v0,s6,v0 */ c->r[2]=less(c->r[22],c->r[2]);
/* 0028e660: bnel v0,zero,0x0028e630 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028e664 */ c->r[16]=hword((uint32_t)c->r[17]+UINT32_C(0x00000000));goto L_0028e630;}}
/* 0028e668: b 0x0028e708 */ /* delay 0028e66c */ c->r[2]=sx(UINT32_C(0xffffffff));goto L_0028e708;
L_0028e670:;
/* 0028e670: move s6,zero */ c->r[22]=c->r[0];
/* 0028e674: lhu v0,0x4(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 0028e678: sll v1,v0,0x3 */ c->r[3]=sx((uint32_t)c->r[2]<<3u);
/* 0028e67c: sll a0,v0,0x7 */ c->r[4]=sx((uint32_t)c->r[2]<<7u);
/* 0028e680: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0028e684: lui s5,0x3a */ c->r[21]=sx(UINT32_C(0x003a0000));
/* 0028e688: addiu s5,s5,-0x75f6 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0xffff8a0a));
/* 0028e68c: addu s5,s5,a0 */ c->r[21]=sx((uint32_t)c->r[21]+(uint32_t)c->r[4]);
/* 0028e690: sll s4,v1,0x2 */ c->r[20]=sx((uint32_t)c->r[3]<<2u);
/* 0028e694: nop  */ (void)0;
L_0028e698:;
/* 0028e698: sll v0,s7,0x1 */ c->r[2]=sx((uint32_t)c->r[23]<<1u);
/* 0028e69c: addu s2,s5,s4 */ c->r[18]=sx((uint32_t)c->r[21]+(uint32_t)c->r[20]);
/* 0028e6a0: addu s1,v0,sp */ c->r[17]=sx((uint32_t)c->r[2]+(uint32_t)c->r[29]);
/* 0028e6a4: li s3,0x4 */ c->r[19]=sx(UINT32_C(0x00000004));
/* 0028e6a8: lhu s0,0x0(s2) */ c->r[16]=hword((uint32_t)c->r[18]+UINT32_C(0x00000000));
/* 0028e6ac: nop  */ (void)0;
L_0028e6b0:;
/* 0028e6b0: addiu s2,s2,0x8 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000008));
/* 0028e6b4: beq s0,zero,0x0028e6e4 */ {int taken=(c->r[16]==c->r[0]);/* delay 0028e6b8 */ c->r[2]=c->r[16]&UINT64_C(0x8000);if(taken){goto L_0028e6e4;}}
/* 0028e6bc: bnel v0,zero,0x0028e6e8 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028e6c0 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0xffffffff));goto L_0028e6e8;}}
/* 0028e6c4: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e6c8: jal 0x0028e560 */ c->r[31]=UINT64_C(0x0028e6d0);/* delay 0028e6cc */ c->r[5]=c->r[30];body_0028e560(c);
/* 0028e6d0: beql v0,zero,0x0028e6e8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028e6d4 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0xffffffff));goto L_0028e6e8;}}
/* 0028e6d8: sh s0,0x0(s1) */ sh((uint32_t)c->r[17]+UINT32_C(0x00000000),(uint16_t)c->r[16]);
/* 0028e6dc: addiu s1,s1,0x2 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000002));
/* 0028e6e0: addiu s7,s7,0x1 */ c->r[23]=sx((uint32_t)c->r[23]+UINT32_C(0x00000001));
L_0028e6e4:;
/* 0028e6e4: addiu s3,s3,-0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0xffffffff));
L_0028e6e8:;
/* 0028e6e8: bgezl s3,0x0028e6b0 */ {int taken=(!neg(c->r[19]));if(taken){/* delay 0028e6ec */ c->r[16]=hword((uint32_t)c->r[18]+UINT32_C(0x00000000));goto L_0028e6b0;}}
/* 0028e6f0: addiu s6,s6,0x1 */ c->r[22]=sx((uint32_t)c->r[22]+UINT32_C(0x00000001));
/* 0028e6f4: addiu s4,s4,0x8 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000008));
/* 0028e6f8: slti v0,s6,0x3 */ c->r[2]=less(c->r[22],sx(UINT32_C(0x00000003)));
/* 0028e6fc: bne v0,zero,0x0028e698 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028e700 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0x00000020));if(taken){goto L_0028e698;}}
L_0028e704:;
/* 0028e704: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
L_0028e708:;
/* 0028e708: beq s7,zero,0x0028e724 */ {int taken=(c->r[23]==c->r[0]);/* delay 0028e70c */ c->r[5]=c->r[23];if(taken){goto L_0028e724;}}
/* 0028e710: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x0028e718);/* delay 0028e714 */ c->r[4]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]?(uint32_t *)at((uint32_t)c->r[4]):NULL,(uint32_t)c->r[5]));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e718: sll v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]<<1u);
/* 0028e71c: addu v1,sp,v0 */ c->r[3]=sx((uint32_t)c->r[29]+(uint32_t)c->r[2]);
/* 0028e720: lh v0,0x0(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000000)));
L_0028e724:;
/* 0028e724: ld s0,0x80(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000080));
/* 0028e728: ld s1,0x88(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000088));
/* 0028e72c: ld s2,0x90(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000090));
/* 0028e730: ld s3,0x98(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000098));
/* 0028e734: ld s4,0xa0(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x000000a0));
/* 0028e738: ld s5,0xa8(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x000000a8));
/* 0028e73c: ld s6,0xb0(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x000000b0));
/* 0028e740: ld s7,0xb8(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x000000b8));
/* 0028e744: ld s8,0xc0(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x000000c0));
/* 0028e748: ld ra,0xc8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x000000c8));
/* 0028e74c: jr ra */ /* delay 0028e750 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x000000d0));return;
}

static void body_0028e758(BattleStatusPairsValues *c){
/* 0028e758: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028e75c: li a1,0x3 */ c->r[5]=sx(UINT32_C(0x00000003));
/* 0028e760: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0028e764: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0028e768: jal 0x0028e5c8 */ c->r[31]=UINT64_C(0x0028e770);/* delay 0028e76c */ c->r[16]=c->r[4];body_0028e5c8(c);
/* 0028e770: move a2,v0 */ c->r[6]=c->r[2];
/* 0028e774: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0028e778: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e77c: bltz a2,0x0028e808 */ {int taken=(neg(c->r[6]));/* delay 0028e780 */ c->r[5]=sx(UINT32_C(0x00000001));if(taken){goto L_0028e808;}}
/* 0028e784: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e788: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0028e78c: sh a2,0x6c(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006c),(uint16_t)c->r[6]);
/* 0028e790: jal 0x0028e4b0 */ c->r[31]=UINT64_C(0x0028e798);/* delay 0028e794 */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006a),(uint16_t)c->r[2]);body_0028e4b0(c);
/* 0028e798: bne v0,zero,0x0028e7a8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028e79c */ c->r[5]=sx(UINT32_C(0x00000008));if(taken){goto L_0028e7a8;}}
/* 0028e7a0: b 0x0028e808 */ /* delay 0028e7a4 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_0028e808;
L_0028e7a8:;
/* 0028e7a8: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e7ac: lhu v0,0xe(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x0000000e));
/* 0028e7b0: andi a0,v0,0xfff */ c->r[4]=c->r[2]&UINT64_C(0xfff);
/* 0028e7b4: beq a0,a1,0x0028e7d0 */ {int taken=(c->r[4]==c->r[5]);/* delay 0028e7b8 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_0028e7d0;}}
/* 0028e7bc: beq a0,v0,0x0028e7f0 */ {int taken=(c->r[4]==c->r[2]);/* delay 0028e7c0 */ c->r[2]=c->r[0];if(taken){goto L_0028e7f0;}}
/* 0028e7c4: b 0x0028e80c */ /* delay 0028e7c8 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028e80c;
L_0028e7d0:;
/* 0028e7d0: lhu a3,0x4(v1) */ c->r[7]=hword((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 0028e7d4: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e7d8: li a1,0x2e */ c->r[5]=sx(UINT32_C(0x0000002e));
/* 0028e7dc: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028e7e4);/* delay 0028e7e0 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e7e4: b 0x0028e808 */ /* delay 0028e7e8 */ c->r[2]=c->r[0];goto L_0028e808;
L_0028e7f0:;
/* 0028e7f0: lhu a3,0x4(v1) */ c->r[7]=hword((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 0028e7f4: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e7f8: li a1,0x36 */ c->r[5]=sx(UINT32_C(0x00000036));
/* 0028e7fc: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028e804);/* delay 0028e800 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e804: move v0,zero */ c->r[2]=c->r[0];
L_0028e808:;
/* 0028e808: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0028e80c:;
/* 0028e80c: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028e810: jr ra */ /* delay 0028e814 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028e818(BattleStatusPairsValues *c){
/* 0028e818: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028e81c: li a1,0x2 */ c->r[5]=sx(UINT32_C(0x00000002));
/* 0028e820: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0028e824: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0028e828: jal 0x0028e5c8 */ c->r[31]=UINT64_C(0x0028e830);/* delay 0028e82c */ c->r[16]=c->r[4];body_0028e5c8(c);
/* 0028e830: move a2,v0 */ c->r[6]=c->r[2];
/* 0028e834: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0028e838: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e83c: bltz a2,0x0028e8c8 */ {int taken=(neg(c->r[6]));/* delay 0028e840 */ c->r[5]=sx(UINT32_C(0x00000001));if(taken){goto L_0028e8c8;}}
/* 0028e844: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e848: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0028e84c: sh a2,0x6c(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006c),(uint16_t)c->r[6]);
/* 0028e850: jal 0x0028e4b0 */ c->r[31]=UINT64_C(0x0028e858);/* delay 0028e854 */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006a),(uint16_t)c->r[2]);body_0028e4b0(c);
/* 0028e858: bne v0,zero,0x0028e868 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028e85c */ c->r[5]=sx(UINT32_C(0x00000008));if(taken){goto L_0028e868;}}
/* 0028e860: b 0x0028e8c8 */ /* delay 0028e864 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_0028e8c8;
L_0028e868:;
/* 0028e868: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e86c: lhu v0,0xe(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x0000000e));
/* 0028e870: andi a0,v0,0xfff */ c->r[4]=c->r[2]&UINT64_C(0xfff);
/* 0028e874: beq a0,a1,0x0028e890 */ {int taken=(c->r[4]==c->r[5]);/* delay 0028e878 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_0028e890;}}
/* 0028e87c: beq a0,v0,0x0028e8b0 */ {int taken=(c->r[4]==c->r[2]);/* delay 0028e880 */ c->r[2]=c->r[0];if(taken){goto L_0028e8b0;}}
/* 0028e884: b 0x0028e8cc */ /* delay 0028e888 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028e8cc;
L_0028e890:;
/* 0028e890: lhu a3,0x4(v1) */ c->r[7]=hword((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 0028e894: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e898: li a1,0x2e */ c->r[5]=sx(UINT32_C(0x0000002e));
/* 0028e89c: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028e8a4);/* delay 0028e8a0 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e8a4: b 0x0028e8c8 */ /* delay 0028e8a8 */ c->r[2]=c->r[0];goto L_0028e8c8;
L_0028e8b0:;
/* 0028e8b0: lhu a3,0x4(v1) */ c->r[7]=hword((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 0028e8b4: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e8b8: li a1,0x36 */ c->r[5]=sx(UINT32_C(0x00000036));
/* 0028e8bc: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028e8c4);/* delay 0028e8c0 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e8c4: move v0,zero */ c->r[2]=c->r[0];
L_0028e8c8:;
/* 0028e8c8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0028e8cc:;
/* 0028e8cc: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028e8d0: jr ra */ /* delay 0028e8d4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028e8d8(BattleStatusPairsValues *c){
/* 0028e8d8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028e8dc: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
/* 0028e8e0: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0028e8e4: move s0,a0 */ c->r[16]=c->r[4];
/* 0028e8e8: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0028e8ec: lw v0,0x2c(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e8f0: sh zero,0x6c(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x0000006c),(uint16_t)c->r[0]);
/* 0028e8f4: jal 0x0028e4b0 */ c->r[31]=UINT64_C(0x0028e8fc);/* delay 0028e8f8 */ sh((uint32_t)c->r[2]+UINT32_C(0x0000006a),(uint16_t)c->r[0]);body_0028e4b0(c);
/* 0028e8fc: bnel v0,zero,0x0028e910 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028e900 */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));goto L_0028e910;}}
/* 0028e904: b 0x0028e9a8 */ /* delay 0028e908 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_0028e9a8;
L_0028e910:;
/* 0028e910: jal 0x002677b8 */ c->r[31]=UINT64_C(0x0028e918);/* delay 0028e914 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatCheckCurse_002677B8(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e918: beq v0,zero,0x0028e940 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e91c */ c->r[4]=c->r[16];if(taken){goto L_0028e940;}}
/* 0028e920: lw v0,0x2c(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e924: li a1,0x4a */ c->r[5]=sx(UINT32_C(0x0000004a));
/* 0028e928: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0028e92c: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028e934);/* delay 0028e930 */ c->r[7]=hword((uint32_t)c->r[2]+UINT32_C(0x00000004));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e934: b 0x0028e99c */ /* delay 0028e938 */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));goto L_0028e99c;
L_0028e940:;
/* 0028e940: lw a0,0x2c(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e944: li v1,0x8 */ c->r[3]=sx(UINT32_C(0x00000008));
/* 0028e948: lhu v0,0xe(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x0000000e));
/* 0028e94c: andi a1,v0,0xfff */ c->r[5]=c->r[2]&UINT64_C(0xfff);
/* 0028e950: beq a1,v1,0x0028e968 */ {int taken=(c->r[5]==c->r[3]);/* delay 0028e954 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_0028e968;}}
/* 0028e958: beql a1,v0,0x0028e988 */ {int taken=(c->r[5]==c->r[2]);if(taken){/* delay 0028e95c */ c->r[7]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));goto L_0028e988;}}
/* 0028e960: b 0x0028e99c */ /* delay 0028e964 */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));goto L_0028e99c;
L_0028e968:;
/* 0028e968: lhu a3,0x4(a0) */ c->r[7]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 0028e96c: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e970: li a1,0x2e */ c->r[5]=sx(UINT32_C(0x0000002e));
/* 0028e974: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028e97c);/* delay 0028e978 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e97c: b 0x0028e99c */ /* delay 0028e980 */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));goto L_0028e99c;
L_0028e988:;
/* 0028e988: move a0,s0 */ c->r[4]=c->r[16];
/* 0028e98c: li a1,0x36 */ c->r[5]=sx(UINT32_C(0x00000036));
/* 0028e990: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028e998);/* delay 0028e994 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e998: lw v1,0x4(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
L_0028e99c:;
/* 0028e99c: move v0,zero */ c->r[2]=c->r[0];
/* 0028e9a0: ori v1,v1,0x200 */ c->r[3]=c->r[3]|UINT64_C(0x200);
/* 0028e9a4: sw v1,0x4(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000004),(uint32_t)c->r[3]);
L_0028e9a8:;
/* 0028e9a8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028e9ac: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028e9b0: jr ra */ /* delay 0028e9b4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028e9b8(BattleStatusPairsValues *c){
/* 0028e9b8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028e9bc: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0028e9c0: move s0,a0 */ c->r[16]=c->r[4];
/* 0028e9c4: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0028e9c8: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0028e9cc: jal 0x0026a468 */ c->r[31]=UINT64_C(0x0028e9d4);/* delay 0028e9d0 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbCheckFormationPlayerSide(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028e9d4: beq v0,zero,0x0028e9e8 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e9d8 */ c->r[4]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));if(taken){goto L_0028e9e8;}}
/* 0028e9dc: lw v1,0xa48(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000a48)));
/* 0028e9e0: beq v1,zero,0x0028eaa8 */ {int taken=(c->r[3]==c->r[0]);/* delay 0028e9e4 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0028eaa8;}}
L_0028e9e8:;
/* 0028e9e8: lw t0,0x2c(s0) */ c->r[8]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028e9ec: lw v0,0x0(t0) */ c->r[2]=sx(word((uint32_t)c->r[8]+UINT32_C(0x00000000)));
/* 0028e9f0: andi v0,v0,0x20 */ c->r[2]=c->r[2]&UINT64_C(0x20);
/* 0028e9f4: beq v0,zero,0x0028ea18 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028e9f8 */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));if(taken){goto L_0028ea18;}}
/* 0028e9fc: lhu v0,0x0(a3) */ c->r[2]=hword((uint32_t)c->r[7]+UINT32_C(0x00000000));
/* 0028ea00: andi v0,v0,0x800 */ c->r[2]=c->r[2]&UINT64_C(0x800);
/* 0028ea04: beql v0,zero,0x0028ea1c */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028ea08 */ c->r[2]=hword((uint32_t)c->r[7]+UINT32_C(0x00000000));goto L_0028ea1c;}}
L_0028ea0c:;
/* 0028ea0c: b 0x0028eaa8 */ /* delay 0028ea10 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_0028eaa8;
L_0028ea18:;
/* 0028ea18: lhu v0,0x0(a3) */ c->r[2]=hword((uint32_t)c->r[7]+UINT32_C(0x00000000));
L_0028ea1c:;
/* 0028ea1c: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0028ea20: li v1,0xf7 */ c->r[3]=sx(UINT32_C(0x000000f7));
/* 0028ea24: move a0,s0 */ c->r[4]=c->r[16];
/* 0028ea28: ori v0,v0,0x800 */ c->r[2]=c->r[2]|UINT64_C(0x800);
/* 0028ea2c: move a1,zero */ c->r[5]=c->r[0];
/* 0028ea30: sh v0,0x0(a3) */ sh((uint32_t)c->r[7]+UINT32_C(0x00000000),(uint16_t)c->r[2]);
/* 0028ea34: sh v1,0x6c(t0) */ sh((uint32_t)c->r[8]+UINT32_C(0x0000006c),(uint16_t)c->r[3]);
/* 0028ea38: jal 0x0028e4b0 */ c->r[31]=UINT64_C(0x0028ea40);/* delay 0028ea3c */ sh((uint32_t)c->r[8]+UINT32_C(0x0000006a),(uint16_t)c->r[6]);body_0028e4b0(c);
/* 0028ea40: beq v0,zero,0x0028ea0c */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ea44 */ c->r[3]=sx(UINT32_C(0x00000008));if(taken){goto L_0028ea0c;}}
/* 0028ea48: lw a0,0x2c(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028ea4c: lhu v0,0xe(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x0000000e));
/* 0028ea50: andi a1,v0,0xfff */ c->r[5]=c->r[2]&UINT64_C(0xfff);
/* 0028ea54: beq a1,v1,0x0028ea70 */ {int taken=(c->r[5]==c->r[3]);/* delay 0028ea58 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_0028ea70;}}
/* 0028ea5c: beq a1,v0,0x0028ea90 */ {int taken=(c->r[5]==c->r[2]);/* delay 0028ea60 */ c->r[2]=c->r[0];if(taken){goto L_0028ea90;}}
/* 0028ea64: b 0x0028eaac */ /* delay 0028ea68 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028eaac;
L_0028ea70:;
/* 0028ea70: lhu a3,0x4(a0) */ c->r[7]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 0028ea74: move a0,s0 */ c->r[4]=c->r[16];
/* 0028ea78: li a1,0x2e */ c->r[5]=sx(UINT32_C(0x0000002e));
/* 0028ea7c: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028ea84);/* delay 0028ea80 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ea84: b 0x0028eaa8 */ /* delay 0028ea88 */ c->r[2]=c->r[0];goto L_0028eaa8;
L_0028ea90:;
/* 0028ea90: lhu a3,0x4(a0) */ c->r[7]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 0028ea94: move a0,s0 */ c->r[4]=c->r[16];
/* 0028ea98: li a1,0x36 */ c->r[5]=sx(UINT32_C(0x00000036));
/* 0028ea9c: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028eaa4);/* delay 0028eaa0 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028eaa4: move v0,zero */ c->r[2]=c->r[0];
L_0028eaa8:;
/* 0028eaa8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0028eaac:;
/* 0028eaac: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028eab0: jr ra */ /* delay 0028eab4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028eab8(BattleStatusPairsValues *c){
/* 0028eab8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028eabc: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0028eac0: move s0,a0 */ c->r[16]=c->r[4];
/* 0028eac4: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0028eac8: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0028eacc: jal 0x0026a468 */ c->r[31]=UINT64_C(0x0028ead4);/* delay 0028ead0 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbCheckFormationPlayerSide(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ead4: beq v0,zero,0x0028eb08 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ead8 */ c->r[5]=sx(UINT32_C(0x00000004));if(taken){goto L_0028eb08;}}
/* 0028eadc: lw v1,0x2c(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 0028eae0: li v0,0x180 */ c->r[2]=sx(UINT32_C(0x00000180));
/* 0028eae4: li a2,0x6 */ c->r[6]=sx(UINT32_C(0x00000006));
/* 0028eae8: sh a1,0x6a(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006a),(uint16_t)c->r[5]);
/* 0028eaec: move a1,zero */ c->r[5]=c->r[0];
/* 0028eaf0: sh v0,0x6c(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000006c),(uint16_t)c->r[2]);
/* 0028eaf4: move a0,s0 */ c->r[4]=c->r[16];
/* 0028eaf8: jal 0x0028e4b0 */ c->r[31]=UINT64_C(0x0028eb00);/* delay 0028eafc */ sw((uint32_t)c->r[16]+UINT32_C(0x00000068),(uint32_t)c->r[6]);body_0028e4b0(c);
/* 0028eb00: bnel v0,zero,0x0028eb10 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028eb04 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));goto L_0028eb10;}}
L_0028eb08:;
/* 0028eb08: b 0x0028eb70 */ /* delay 0028eb0c */ c->r[2]=sx(UINT32_C(0x00000001));goto L_0028eb70;
L_0028eb10:;
/* 0028eb10: li v1,0x8 */ c->r[3]=sx(UINT32_C(0x00000008));
/* 0028eb14: lhu v0,0xe(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x0000000e));
/* 0028eb18: andi a1,v0,0xfff */ c->r[5]=c->r[2]&UINT64_C(0xfff);
/* 0028eb1c: beq a1,v1,0x0028eb38 */ {int taken=(c->r[5]==c->r[3]);/* delay 0028eb20 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_0028eb38;}}
/* 0028eb24: beq a1,v0,0x0028eb58 */ {int taken=(c->r[5]==c->r[2]);/* delay 0028eb28 */ c->r[2]=c->r[0];if(taken){goto L_0028eb58;}}
/* 0028eb2c: b 0x0028eb74 */ /* delay 0028eb30 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028eb74;
L_0028eb38:;
/* 0028eb38: lhu a3,0x4(a0) */ c->r[7]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 0028eb3c: move a0,s0 */ c->r[4]=c->r[16];
/* 0028eb40: li a1,0x2e */ c->r[5]=sx(UINT32_C(0x0000002e));
/* 0028eb44: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028eb4c);/* delay 0028eb48 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028eb4c: b 0x0028eb70 */ /* delay 0028eb50 */ c->r[2]=c->r[0];goto L_0028eb70;
L_0028eb58:;
/* 0028eb58: lhu a3,0x4(a0) */ c->r[7]=hword((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 0028eb5c: move a0,s0 */ c->r[4]=c->r[16];
/* 0028eb60: li a1,0x36 */ c->r[5]=sx(UINT32_C(0x00000036));
/* 0028eb64: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028eb6c);/* delay 0028eb68 */ c->r[6]=sx(UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028eb6c: move v0,zero */ c->r[2]=c->r[0];
L_0028eb70:;
/* 0028eb70: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0028eb74:;
/* 0028eb74: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028eb78: jr ra */ /* delay 0028eb7c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028eb80(BattleStatusPairsValues *c){
/* 0028eb80: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028eb84: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0028eb88: lw a2,0x2c(a0) */ c->r[6]=sx(word((uint32_t)c->r[4]+UINT32_C(0x0000002c)));
/* 0028eb8c: lw v1,0x0(a2) */ c->r[3]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000000)));
/* 0028eb90: andi v1,v1,0x4 */ c->r[3]=c->r[3]&UINT64_C(0x4);
/* 0028eb94: bne v1,zero,0x0028ec0c */ {int taken=(c->r[3]!=c->r[0]);/* delay 0028eb98 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0028ec0c;}}
/* 0028eb9c: lhu v1,0x4(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 0028eba0: sltiu v1,v1,0x100 */ c->r[3]=(c->r[3]<sx(UINT32_C(0x00000100)));
/* 0028eba4: beql v1,zero,0x0028ec10 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 0028eba8 */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028ec10;}}
/* 0028ebac: lhu v0,0xe(a2) */ c->r[2]=hword((uint32_t)c->r[6]+UINT32_C(0x0000000e));
/* 0028ebb0: li v1,0x7 */ c->r[3]=sx(UINT32_C(0x00000007));
/* 0028ebb4: li a1,0x8 */ c->r[5]=sx(UINT32_C(0x00000008));
/* 0028ebb8: sh zero,0x6c(a2) */ sh((uint32_t)c->r[6]+UINT32_C(0x0000006c),(uint16_t)c->r[0]);
/* 0028ebbc: andi a3,v0,0xfff */ c->r[7]=c->r[2]&UINT64_C(0xfff);
/* 0028ebc0: beq a3,a1,0x0028ebe0 */ {int taken=(c->r[7]==c->r[5]);/* delay 0028ebc4 */ sh((uint32_t)c->r[6]+UINT32_C(0x0000006a),(uint16_t)c->r[3]);if(taken){goto L_0028ebe0;}}
/* 0028ebc8: li v0,0x80 */ c->r[2]=sx(UINT32_C(0x00000080));
/* 0028ebcc: beq a3,v0,0x0028ebf8 */ {int taken=(c->r[7]==c->r[2]);/* delay 0028ebd0 */ c->r[2]=c->r[0];if(taken){goto L_0028ebf8;}}
/* 0028ebd4: b 0x0028ec10 */ /* delay 0028ebd8 */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028ec10;
L_0028ebe0:;
/* 0028ebe0: lhu a3,0x4(a2) */ c->r[7]=hword((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 0028ebe4: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0028ebe8: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028ebf0);/* delay 0028ebec */ c->r[5]=sx(UINT32_C(0x0000002e));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ebf0: b 0x0028ec0c */ /* delay 0028ebf4 */ c->r[2]=c->r[0];goto L_0028ec0c;
L_0028ebf8:;
/* 0028ebf8: lhu a3,0x4(a2) */ c->r[7]=hword((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 0028ebfc: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0028ec00: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028ec08);/* delay 0028ec04 */ c->r[5]=sx(UINT32_C(0x00000036));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ec08: move v0,zero */ c->r[2]=c->r[0];
L_0028ec0c:;
/* 0028ec0c: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0028ec10:;
/* 0028ec10: jr ra */ /* delay 0028ec14 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028ec18(BattleStatusPairsValues *c){
/* 0028ec18: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028ec1c: li v0,0x8 */ c->r[2]=sx(UINT32_C(0x00000008));
/* 0028ec20: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0028ec24: li a1,0x8 */ c->r[5]=sx(UINT32_C(0x00000008));
/* 0028ec28: lw a2,0x2c(a0) */ c->r[6]=sx(word((uint32_t)c->r[4]+UINT32_C(0x0000002c)));
/* 0028ec2c: lhu v1,0xe(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x0000000e));
/* 0028ec30: sh v0,0x6a(a2) */ sh((uint32_t)c->r[6]+UINT32_C(0x0000006a),(uint16_t)c->r[2]);
/* 0028ec34: andi v1,v1,0xfff */ c->r[3]=c->r[3]&UINT64_C(0xfff);
/* 0028ec38: beq v1,a1,0x0028ec58 */ {int taken=(c->r[3]==c->r[5]);/* delay 0028ec3c */ sh((uint32_t)c->r[6]+UINT32_C(0x0000006c),(uint16_t)c->r[0]);if(taken){goto L_0028ec58;}}
/* 0028ec40: li v0,0x80 */ c->r[2]=sx(UINT32_C(0x00000080));
/* 0028ec44: beq v1,v0,0x0028ec70 */ {int taken=(c->r[3]==c->r[2]);/* delay 0028ec48 */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_0028ec70;}}
/* 0028ec4c: b 0x0028ec88 */ /* delay 0028ec50 */ c->r[2]=c->r[0];goto L_0028ec88;
L_0028ec58:;
/* 0028ec58: lhu a3,0x4(a2) */ c->r[7]=hword((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 0028ec5c: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0028ec60: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028ec68);/* delay 0028ec64 */ c->r[5]=sx(UINT32_C(0x00000030));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ec68: b 0x0028ec84 */ /* delay 0028ec6c */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028ec84;
L_0028ec70:;
/* 0028ec70: lhu a3,0x4(a2) */ c->r[7]=hword((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 0028ec74: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0028ec78: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028ec80);/* delay 0028ec7c */ c->r[5]=sx(UINT32_C(0x00000038));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ec80: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0028ec84:;
/* 0028ec84: move v0,zero */ c->r[2]=c->r[0];
L_0028ec88:;
/* 0028ec88: jr ra */ /* delay 0028ec8c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028ec90(BattleStatusPairsValues *c){
/* 0028ec90: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028ec94: li v1,0xa */ c->r[3]=sx(UINT32_C(0x0000000a));
/* 0028ec98: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0028ec9c: li a1,0x4c */ c->r[5]=sx(UINT32_C(0x0000004c));
/* 0028eca0: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0028eca4: lw v0,0x2c(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x0000002c)));
/* 0028eca8: sh v1,0x6a(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x0000006a),(uint16_t)c->r[3]);
/* 0028ecac: lhu a3,0x4(v0) */ c->r[7]=hword((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 0028ecb0: jal 0x002592b0 */ c->r[31]=UINT64_C(0x0028ecb8);/* delay 0028ecb4 */ sh((uint32_t)c->r[2]+UINT32_C(0x0000006c),(uint16_t)c->r[0]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);ps2BattleAction_002592B0(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ecb8: move v0,zero */ c->r[2]=c->r[0];
/* 0028ecbc: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028ecc0: jr ra */ /* delay 0028ecc4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028ecc8(BattleStatusPairsValues *c){
/* 0028ecc8: lw v1,-0x2c18(gp) */ c->r[3]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffd3e8)));
/* 0028eccc: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0028ecd0: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0028ecd4: blez v1,0x0028ed0c */ {int taken=((neg(c->r[3])||!c->r[3]));/* delay 0028ecd8 */ c->r[5]=c->r[0];if(taken){goto L_0028ed0c;}}
/* 0028ecdc: lui v0,0x57 */ c->r[2]=sx(UINT32_C(0x00570000));
/* 0028ece0: move a0,v1 */ c->r[4]=c->r[3];
/* 0028ece4: addiu v0,v0,0x5490 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00005490));
/* 0028ece8: addiu v1,v0,0x4 */ c->r[3]=sx((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 0028ecec: nop  */ (void)0;
L_0028ecf0:;
/* 0028ecf0: lw v0,0x0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 0028ecf4: addiu v1,v1,0x8 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000008));
/* 0028ecf8: addiu a0,a0,-0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0xffffffff));
/* 0028ecfc: nop  */ (void)0;
/* 0028ed00: nop  */ (void)0;
/* 0028ed04: bne a0,zero,0x0028ecf0 */ {int taken=(c->r[4]!=c->r[0]);/* delay 0028ed08 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[2]);if(taken){goto L_0028ecf0;}}
L_0028ed0c:;
/* 0028ed0c: bne a1,zero,0x0028ed28 */ {int taken=(c->r[5]!=c->r[0]);/* delay 0028ed10 */ c->r[2]=sx(UINT32_C(0xffffffff));if(taken){goto L_0028ed28;}}
/* 0028ed14: b 0x0028ed8c */ /* delay 0028ed18 */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028ed8c;
L_0028ed20:;
/* 0028ed20: b 0x0028ed88 */ /* delay 0028ed24 */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));goto L_0028ed88;
L_0028ed28:;
/* 0028ed28: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x0028ed30);/* delay 0028ed2c */ c->r[4]=c->r[0];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]?(uint32_t *)at((uint32_t)c->r[4]):NULL,(uint32_t)c->r[5]));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ed30: move a3,zero */ c->r[7]=c->r[0];
/* 0028ed34: lw a1,-0x2c18(gp) */ c->r[5]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffd3e8)));
/* 0028ed38: move t1,v0 */ c->r[9]=c->r[2];
/* 0028ed3c: blez a1,0x0028ed84 */ {int taken=((neg(c->r[5])||!c->r[5]));/* delay 0028ed40 */ c->r[4]=c->r[0];if(taken){goto L_0028ed84;}}
/* 0028ed44: lui v0,0x57 */ c->r[2]=sx(UINT32_C(0x00570000));
/* 0028ed48: move t0,a1 */ c->r[8]=c->r[5];
/* 0028ed4c: addiu t2,v0,0x5490 */ c->r[10]=sx((uint32_t)c->r[2]+UINT32_C(0x00005490));
/* 0028ed50: addiu a2,t2,0x4 */ c->r[6]=sx((uint32_t)c->r[10]+UINT32_C(0x00000004));
/* 0028ed54: lw v0,0x0(a2) */ c->r[2]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000000)));
L_0028ed58:;
/* 0028ed58: addiu a2,a2,0x8 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000008));
/* 0028ed5c: sll v1,a0,0x3 */ c->r[3]=sx((uint32_t)c->r[4]<<3u);
/* 0028ed60: addiu a0,a0,0x1 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));
/* 0028ed64: beq v0,zero,0x0028ed7c */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ed68 */ c->r[5]=less(c->r[4],c->r[8]);if(taken){goto L_0028ed7c;}}
/* 0028ed6c: addu a3,a3,v0 */ c->r[7]=sx((uint32_t)c->r[7]+(uint32_t)c->r[2]);
/* 0028ed70: slt v0,t1,a3 */ c->r[2]=less(c->r[9],c->r[7]);
/* 0028ed74: bnel v0,zero,0x0028ed20 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028ed78 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[10]);goto L_0028ed20;}}
L_0028ed7c:;
/* 0028ed7c: bnel a1,zero,0x0028ed58 */ {int taken=(c->r[5]!=c->r[0]);if(taken){/* delay 0028ed80 */ c->r[2]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000000)));goto L_0028ed58;}}
L_0028ed84:;
/* 0028ed84: li v0,0x9 */ c->r[2]=sx(UINT32_C(0x00000009));
L_0028ed88:;
/* 0028ed88: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0028ed8c:;
/* 0028ed8c: jr ra */ /* delay 0028ed90 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_0028ed98(BattleStatusPairsValues *c){
/* 0028ed98: lw a2,-0x2c18(gp) */ c->r[6]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffd3e8)));
/* 0028ed9c: lui v1,0x57 */ c->r[3]=sx(UINT32_C(0x00570000));
/* 0028eda0: addiu v1,v1,0x5490 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00005490));
/* 0028eda4: sll v0,a2,0x3 */ c->r[2]=sx((uint32_t)c->r[6]<<3u);
/* 0028eda8: addiu a2,a2,0x1 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 0028edac: addu a3,v0,v1 */ c->r[7]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 0028edb0: move v0,a3 */ c->r[2]=c->r[7];
/* 0028edb4: sw a0,0x0(v0) */ sw((uint32_t)c->r[2]+UINT32_C(0x00000000),(uint32_t)c->r[4]);
/* 0028edb8: sw a1,0x4(a3) */ sw((uint32_t)c->r[7]+UINT32_C(0x00000004),(uint32_t)c->r[5]);
/* 0028edbc: jr ra */ /* delay 0028edc0 */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd3e8),(uint32_t)c->r[6]);return;
}

static void body_0028edc8(BattleStatusPairsValues *c){
/* 0028edc8: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 0028edcc: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0028edd0: move s0,a0 */ c->r[16]=c->r[4];
/* 0028edd4: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0028edd8: move s2,zero */ c->r[18]=c->r[0];
/* 0028eddc: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0028ede0: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0028ede4: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 0028ede8: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 0028edec: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 0028edf0: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 0028edf4: sd s8,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[30]);
/* 0028edf8: sd ra,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[31]);
/* 0028edfc: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0028ee00: jal 0x00267788 */ c->r[31]=UINT64_C(0x0028ee08);/* delay 0028ee04 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetBadStat(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ee08: move v1,v0 */ c->r[3]=c->r[2];
/* 0028ee0c: li v0,0x8 */ c->r[2]=sx(UINT32_C(0x00000008));
/* 0028ee10: beq v1,v0,0x0028ee38 */ {int taken=(c->r[3]==c->r[2]);/* delay 0028ee14 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_0028ee38;}}
/* 0028ee18: beq v1,v0,0x0028ee38 */ {int taken=(c->r[3]==c->r[2]);/* delay 0028ee1c */ c->r[18]=sx(UINT32_C(0x00000001));if(taken){goto L_0028ee38;}}
/* 0028ee20: lw v0,0x28(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0028ee24: move s2,zero */ c->r[18]=c->r[0];
/* 0028ee28: jal 0x002677b8 */ c->r[31]=UINT64_C(0x0028ee30);/* delay 0028ee2c */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatCheckCurse_002677B8(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028ee30: li v1,0x2 */ c->r[3]=sx(UINT32_C(0x00000002));
/* 0028ee34: movn s2,v1,v0 */ if(c->r[2]!=0){c->r[18]=c->r[3];}
L_0028ee38:;
/* 0028ee38: sw zero,-0x2c18(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd3e8),(uint32_t)c->r[0]);
/* 0028ee3c: move s1,zero */ c->r[17]=c->r[0];
/* 0028ee40: li s5,0x1 */ c->r[21]=sx(UINT32_C(0x00000001));
/* 0028ee44: li s8,0x2 */ c->r[30]=sx(UINT32_C(0x00000002));
/* 0028ee48: li s7,0x5 */ c->r[23]=sx(UINT32_C(0x00000005));
/* 0028ee4c: li s4,0x4 */ c->r[20]=sx(UINT32_C(0x00000004));
/* 0028ee50: li s3,0x9 */ c->r[19]=sx(UINT32_C(0x00000009));
/* 0028ee54: li s6,0x6 */ c->r[22]=sx(UINT32_C(0x00000006));
L_0028ee58:;
/* 0028ee58: beq s2,s5,0x0028ef90 */ {int taken=(c->r[18]==c->r[21]);/* delay 0028ee5c */ c->r[2]=less(c->r[18],sx(UINT32_C(0x00000002)));if(taken){goto L_0028ef90;}}
/* 0028ee60: beq v0,zero,0x0028ee78 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ee64 */ (void)0;if(taken){goto L_0028ee78;}}
/* 0028ee68: beql s2,zero,0x0028ee88 */ {int taken=(c->r[18]==c->r[0]);if(taken){/* delay 0028ee6c */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));goto L_0028ee88;}}
/* 0028ee70: b 0x0028f024 */ /* delay 0028ee74 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028ee78:;
/* 0028ee78: beq s2,s8,0x0028efe8 */ {int taken=(c->r[18]==c->r[30]);/* delay 0028ee7c */ (void)0;if(taken){goto L_0028efe8;}}
/* 0028ee80: b 0x0028f024 */ /* delay 0028ee84 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028ee88:;
/* 0028ee88: lw v0,0x0(v0) */ c->r[2]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 0028ee8c: andi v1,v0,0x4 */ c->r[3]=c->r[2]&UINT64_C(0x4);
/* 0028ee90: beq v1,zero,0x0028eed8 */ {int taken=(c->r[3]==c->r[0]);/* delay 0028ee94 */ c->r[2]=c->r[2]&UINT64_C(0x20);if(taken){goto L_0028eed8;}}
/* 0028ee98: beq s1,s7,0x0028eeb8 */ {int taken=(c->r[17]==c->r[23]);/* delay 0028ee9c */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000006)));if(taken){goto L_0028eeb8;}}
/* 0028eea0: beq v0,zero,0x0028ef50 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028eea4 */ (void)0;if(taken){goto L_0028ef50;}}
/* 0028eea8: bnel s1,s4,0x0028f024 */ {int taken=(c->r[17]!=c->r[20]);if(taken){/* delay 0028eeac */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;}}
/* 0028eeb0: b 0x0028efd4 */ /* delay 0028eeb4 */ c->r[4]=sx(UINT32_C(0x00000004));goto L_0028efd4;
L_0028eeb8:;
/* 0028eeb8: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0028eebc: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 0028eec0: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028eec4: bnel v0,zero,0x0028f024 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028eec8 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;}}
/* 0028eecc: b 0x0028ef10 */ /* delay 0028eed0 */ c->r[4]=sx(UINT32_C(0x00000005));goto L_0028ef10;
L_0028eed8:;
/* 0028eed8: beq v0,zero,0x0028ef28 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028eedc */ (void)0;if(taken){goto L_0028ef28;}}
/* 0028eee0: beq s1,s6,0x0028ef20 */ {int taken=(c->r[17]==c->r[22]);/* delay 0028eee4 */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000007)));if(taken){goto L_0028ef20;}}
/* 0028eee8: beq v0,zero,0x0028ef00 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028eeec */ (void)0;if(taken){goto L_0028ef00;}}
/* 0028eef0: beq s1,s4,0x0028ef10 */ {int taken=(c->r[17]==c->r[20]);/* delay 0028eef4 */ c->r[4]=sx(UINT32_C(0x00000004));if(taken){goto L_0028ef10;}}
/* 0028eef8: b 0x0028f024 */ /* delay 0028eefc */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028ef00:;
/* 0028ef00: beq s1,s3,0x0028efc0 */ {int taken=(c->r[17]==c->r[19]);/* delay 0028ef04 */ c->r[4]=sx(UINT32_C(0x00000009));if(taken){goto L_0028efc0;}}
/* 0028ef08: b 0x0028f024 */ /* delay 0028ef0c */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028ef10:;
/* 0028ef10: jal 0x0028ed98 */ c->r[31]=UINT64_C(0x0028ef18);/* delay 0028ef14 */ c->r[5]=sx(UINT32_C(0x0000001e));body_0028ed98(c);
/* 0028ef18: b 0x0028f024 */ /* delay 0028ef1c */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028ef20:;
/* 0028ef20: b 0x0028efd4 */ /* delay 0028ef24 */ c->r[4]=sx(UINT32_C(0x00000006));goto L_0028efd4;
L_0028ef28:;
/* 0028ef28: beq s1,s7,0x0028ef60 */ {int taken=(c->r[17]==c->r[23]);/* delay 0028ef2c */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000006)));if(taken){goto L_0028ef60;}}
/* 0028ef30: beq v0,zero,0x0028ef48 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ef34 */ (void)0;if(taken){goto L_0028ef48;}}
/* 0028ef38: beq s1,s4,0x0028efd4 */ {int taken=(c->r[17]==c->r[20]);/* delay 0028ef3c */ c->r[4]=sx(UINT32_C(0x00000004));if(taken){goto L_0028efd4;}}
/* 0028ef40: b 0x0028f024 */ /* delay 0028ef44 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028ef48:;
/* 0028ef48: beq s1,s6,0x0028ef80 */ {int taken=(c->r[17]==c->r[22]);/* delay 0028ef4c */ c->r[4]=sx(UINT32_C(0x00000006));if(taken){goto L_0028ef80;}}
L_0028ef50:;
/* 0028ef50: beq s1,s3,0x0028efd4 */ {int taken=(c->r[17]==c->r[19]);/* delay 0028ef54 */ c->r[4]=sx(UINT32_C(0x00000009));if(taken){goto L_0028efd4;}}
/* 0028ef58: b 0x0028f024 */ /* delay 0028ef5c */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028ef60:;
/* 0028ef60: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0028ef64: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 0028ef68: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028ef6c: bnel v0,zero,0x0028f024 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0028ef70 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;}}
/* 0028ef74: b 0x0028efd4 */ /* delay 0028ef78 */ c->r[4]=sx(UINT32_C(0x00000005));goto L_0028efd4;
L_0028ef80:;
/* 0028ef80: jal 0x0028ed98 */ c->r[31]=UINT64_C(0x0028ef88);/* delay 0028ef84 */ c->r[5]=sx(UINT32_C(0x0000000a));body_0028ed98(c);
/* 0028ef88: b 0x0028f024 */ /* delay 0028ef8c */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028ef90:;
/* 0028ef90: beq s1,s8,0x0028efd0 */ {int taken=(c->r[17]==c->r[30]);/* delay 0028ef94 */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000003)));if(taken){goto L_0028efd0;}}
/* 0028ef98: beq v0,zero,0x0028efb0 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ef9c */ c->r[2]=sx(UINT32_C(0x00000003));if(taken){goto L_0028efb0;}}
/* 0028efa0: beq s1,s5,0x0028efc0 */ {int taken=(c->r[17]==c->r[21]);/* delay 0028efa4 */ c->r[4]=sx(UINT32_C(0x00000001));if(taken){goto L_0028efc0;}}
/* 0028efa8: b 0x0028f024 */ /* delay 0028efac */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028efb0:;
/* 0028efb0: beq s1,v0,0x0028efd4 */ {int taken=(c->r[17]==c->r[2]);/* delay 0028efb4 */ c->r[4]=sx(UINT32_C(0x00000003));if(taken){goto L_0028efd4;}}
/* 0028efb8: b 0x0028ef50 */ /* delay 0028efbc */ (void)0;goto L_0028ef50;
L_0028efc0:;
/* 0028efc0: jal 0x0028ed98 */ c->r[31]=UINT64_C(0x0028efc8);/* delay 0028efc4 */ c->r[5]=sx(UINT32_C(0x00000028));body_0028ed98(c);
/* 0028efc8: b 0x0028f024 */ /* delay 0028efcc */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028efd0:;
/* 0028efd0: li a0,0x2 */ c->r[4]=sx(UINT32_C(0x00000002));
L_0028efd4:;
/* 0028efd4: jal 0x0028ed98 */ c->r[31]=UINT64_C(0x0028efdc);/* delay 0028efd8 */ c->r[5]=sx(UINT32_C(0x00000014));body_0028ed98(c);
/* 0028efdc: b 0x0028f024 */ /* delay 0028efe0 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028efe8:;
/* 0028efe8: beq s1,s5,0x0028f000 */ {int taken=(c->r[17]==c->r[21]);/* delay 0028efec */ c->r[2]=sx(UINT32_C(0x00000007));if(taken){goto L_0028f000;}}
/* 0028eff0: beq s1,v0,0x0028f018 */ {int taken=(c->r[17]==c->r[2]);/* delay 0028eff4 */ c->r[4]=sx(UINT32_C(0x00000007));if(taken){goto L_0028f018;}}
/* 0028eff8: b 0x0028f024 */ /* delay 0028effc */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028f000:;
/* 0028f000: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 0028f004: jal 0x0028ed98 */ c->r[31]=UINT64_C(0x0028f00c);/* delay 0028f008 */ c->r[5]=sx(UINT32_C(0x00000032));body_0028ed98(c);
/* 0028f00c: b 0x0028f024 */ /* delay 0028f010 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028f024;
L_0028f018:;
/* 0028f018: jal 0x0028ed98 */ c->r[31]=UINT64_C(0x0028f020);/* delay 0028f01c */ c->r[5]=sx(UINT32_C(0x00000032));body_0028ed98(c);
/* 0028f020: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
L_0028f024:;
/* 0028f024: slti v0,s1,0xa */ c->r[2]=less(c->r[17],sx(UINT32_C(0x0000000a)));
/* 0028f028: bne v0,zero,0x0028ee58 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028f02c */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffd3e8)));if(taken){goto L_0028ee58;}}
/* 0028f030: blez v0,0x0028f06c */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 0028f034 */ c->r[17]=c->r[0];if(taken){goto L_0028f06c;}}
/* 0028f038: lui v0,0x57 */ c->r[2]=sx(UINT32_C(0x00570000));
/* 0028f03c: lui s2,0x54 */ c->r[18]=sx(UINT32_C(0x00540000));
/* 0028f040: addiu s0,v0,0x5490 */ c->r[16]=sx((uint32_t)c->r[2]+UINT32_C(0x00005490));
/* 0028f044: lw a1,0x0(s0) */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
L_0028f048:;
/* 0028f048: addiu a0,s2,0x5d40 */ c->r[4]=sx((uint32_t)c->r[18]+UINT32_C(0x00005d40));
/* 0028f04c: lw a2,0x4(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000004)));
/* 0028f050: addiu s0,s0,0x8 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000008));
/* 0028f054: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028f05c);/* delay 0028f058 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,1u,UINT32_C(0x0028f054),UINT32_C(0xf0ff0070));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0028f05c: lw v1,-0x2c18(gp) */ c->r[3]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffd3e8)));
/* 0028f060: slt v1,s1,v1 */ c->r[3]=less(c->r[17],c->r[3]);
/* 0028f064: bnel v1,zero,0x0028f048 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 0028f068 */ c->r[5]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));goto L_0028f048;}}
L_0028f06c:;
/* 0028f06c: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028f070: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028f074: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0028f078: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0028f07c: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0028f080: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 0028f084: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0028f088: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 0028f08c: ld s8,0x40(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 0028f090: ld ra,0x48(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 0028f094: jr ra */ /* delay 0028f098 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}

static void body_0028f0a0(BattleStatusPairsValues *c){
/* 0028f0a0: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 0028f0a4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0028f0a8: move s0,a0 */ c->r[16]=c->r[4];
/* 0028f0ac: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0028f0b0: li s1,0x1 */ c->r[17]=sx(UINT32_C(0x00000001));
/* 0028f0b4: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0028f0b8: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0028f0bc: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 0028f0c0: jal 0x0028edc8 */ c->r[31]=UINT64_C(0x0028f0c8);/* delay 0028f0c4 */ c->r[19]=c->r[0];body_0028edc8(c);
L_0028f0c8:;
/* 0028f0c8: jal 0x0028ecc8 */ c->r[31]=UINT64_C(0x0028f0d0);/* delay 0028f0cc */ c->r[4]=c->r[16];body_0028ecc8(c);
/* 0028f0d0: move s2,v0 */ c->r[18]=c->r[2];
/* 0028f0d4: sltiu v0,s2,0xa */ c->r[2]=(c->r[18]<sx(UINT32_C(0x0000000a)));
/* 0028f0d8: beql v0,zero,0x0028f174 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028f0dc */ c->r[17]=sx(UINT32_C(0x00000001));goto L_0028f174;}}
/* 0028f0e0: sll v0,s2,0x2 */ c->r[2]=sx((uint32_t)c->r[18]<<2u);
/* 0028f0e4: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 0028f0e8: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0028f0ec: lw v1,0x5d60(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00005d60)));
/* 0028f0f0: jr v1 */ {uint64_t target=c->r[3];/* delay 0028f0f4 */ (void)0;switch(target){case UINT64_C(0x0028f0f8):goto L_0028f0f8;case UINT64_C(0x0028f108):goto L_0028f108;case UINT64_C(0x0028f118):goto L_0028f118;case UINT64_C(0x0028f128):goto L_0028f128;case UINT64_C(0x0028f138):goto L_0028f138;case UINT64_C(0x0028f148):goto L_0028f148;case UINT64_C(0x0028f158):goto L_0028f158;case UINT64_C(0x0028f168):goto L_0028f168;case UINT64_C(0x0028f174):goto L_0028f174;default:abort();}}
L_0028f0f8:;
/* 0028f0f8: jal 0x0028e8d8 */ c->r[31]=UINT64_C(0x0028f100);/* delay 0028f0fc */ c->r[4]=c->r[16];body_0028e8d8(c);
/* 0028f100: b 0x0028f174 */ /* delay 0028f104 */ c->r[17]=c->r[2];goto L_0028f174;
L_0028f108:;
/* 0028f108: jal 0x0028e818 */ c->r[31]=UINT64_C(0x0028f110);/* delay 0028f10c */ c->r[4]=c->r[16];body_0028e818(c);
/* 0028f110: b 0x0028f174 */ /* delay 0028f114 */ c->r[17]=c->r[2];goto L_0028f174;
L_0028f118:;
/* 0028f118: jal 0x0028e758 */ c->r[31]=UINT64_C(0x0028f120);/* delay 0028f11c */ c->r[4]=c->r[16];body_0028e758(c);
/* 0028f120: b 0x0028f174 */ /* delay 0028f124 */ c->r[17]=c->r[2];goto L_0028f174;
L_0028f128:;
/* 0028f128: jal 0x0028e9b8 */ c->r[31]=UINT64_C(0x0028f130);/* delay 0028f12c */ c->r[4]=c->r[16];body_0028e9b8(c);
/* 0028f130: b 0x0028f174 */ /* delay 0028f134 */ c->r[17]=c->r[2];goto L_0028f174;
L_0028f138:;
/* 0028f138: jal 0x0028eab8 */ c->r[31]=UINT64_C(0x0028f140);/* delay 0028f13c */ c->r[4]=c->r[16];body_0028eab8(c);
/* 0028f140: b 0x0028f174 */ /* delay 0028f144 */ c->r[17]=c->r[2];goto L_0028f174;
L_0028f148:;
/* 0028f148: jal 0x0028eb80 */ c->r[31]=UINT64_C(0x0028f150);/* delay 0028f14c */ c->r[4]=c->r[16];body_0028eb80(c);
/* 0028f150: b 0x0028f174 */ /* delay 0028f154 */ c->r[17]=c->r[2];goto L_0028f174;
L_0028f158:;
/* 0028f158: jal 0x0028ec18 */ c->r[31]=UINT64_C(0x0028f160);/* delay 0028f15c */ c->r[4]=c->r[16];body_0028ec18(c);
/* 0028f160: b 0x0028f174 */ /* delay 0028f164 */ c->r[17]=c->r[2];goto L_0028f174;
L_0028f168:;
/* 0028f168: jal 0x0028ec90 */ c->r[31]=UINT64_C(0x0028f170);/* delay 0028f16c */ c->r[4]=c->r[16];body_0028ec90(c);
/* 0028f170: move s1,v0 */ c->r[17]=c->r[2];
L_0028f174:;
/* 0028f174: bltzl s2,0x0028f1dc */ {int taken=(neg(c->r[18]));if(taken){/* delay 0028f178 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_0028f1dc;}}
/* 0028f17c: beql s1,zero,0x0028f1dc */ {int taken=(c->r[17]==c->r[0]);if(taken){/* delay 0028f180 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_0028f1dc;}}
/* 0028f184: lw a3,-0x2c18(gp) */ c->r[7]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffd3e8)));
/* 0028f188: blez a3,0x0028f1d8 */ {int taken=((neg(c->r[7])||!c->r[7]));/* delay 0028f18c */ c->r[6]=c->r[0];if(taken){goto L_0028f1d8;}}
/* 0028f190: lui t0,0x57 */ c->r[8]=sx(UINT32_C(0x00570000));
/* 0028f194: addiu v1,t0,0x5490 */ c->r[3]=sx((uint32_t)c->r[8]+UINT32_C(0x00005490));
/* 0028f198: lw v0,0x0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 0028f19c: bnel v0,s2,0x0028f1b0 */ {int taken=(c->r[2]!=c->r[18]);if(taken){/* delay 0028f1a0 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));goto L_0028f1b0;}}
/* 0028f1a4: b 0x0028f1d8 */ /* delay 0028f1a8 */ sw((uint32_t)c->r[3]+UINT32_C(0x00000004),(uint32_t)c->r[0]);goto L_0028f1d8;
L_0028f1b0:;
/* 0028f1b0: slt v0,a2,a3 */ c->r[2]=less(c->r[6],c->r[7]);
/* 0028f1b4: beql v0,zero,0x0028f1dc */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028f1b8 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_0028f1dc;}}
/* 0028f1bc: addiu a1,t0,0x5490 */ c->r[5]=sx((uint32_t)c->r[8]+UINT32_C(0x00005490));
/* 0028f1c0: sll a0,a2,0x3 */ c->r[4]=sx((uint32_t)c->r[6]<<3u);
/* 0028f1c4: addu v0,a0,a1 */ c->r[2]=sx((uint32_t)c->r[4]+(uint32_t)c->r[5]);
/* 0028f1c8: lw v1,0x0(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 0028f1cc: bnel v1,s2,0x0028f1b0 */ {int taken=(c->r[3]!=c->r[18]);if(taken){/* delay 0028f1d0 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));goto L_0028f1b0;}}
/* 0028f1d4: sw zero,0x4(v0) */ sw((uint32_t)c->r[2]+UINT32_C(0x00000004),(uint32_t)c->r[0]);
L_0028f1d8:;
/* 0028f1d8: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_0028f1dc:;
/* 0028f1dc: slti v0,s3,0xb */ c->r[2]=less(c->r[19],sx(UINT32_C(0x0000000b)));
/* 0028f1e0: bne v0,zero,0x0028f1f0 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028f1e4 */ c->r[4]=c->r[16];if(taken){goto L_0028f1f0;}}
/* 0028f1e8: jal 0x0028ec18 */ c->r[31]=UINT64_C(0x0028f1f0);/* delay 0028f1ec */ c->r[17]=c->r[0];body_0028ec18(c);
L_0028f1f0:;
/* 0028f1f0: bne s1,zero,0x0028f0c8 */ {int taken=(c->r[17]!=c->r[0]);/* delay 0028f1f4 */ c->r[2]=c->r[0];if(taken){goto L_0028f0c8;}}
/* 0028f1f8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028f1fc: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028f200: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0028f204: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0028f208: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0028f20c: jr ra */ /* delay 0028f210 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_002900e8(BattleStatusPairsValues *c){
/* 002900e8: move a3,a1 */ c->r[7]=c->r[5];
/* 002900ec: blez a3,0x00290128 */ {int taken=((neg(c->r[7])||!c->r[7]));/* delay 002900f0 */ c->r[8]=c->r[0];if(taken){goto L_00290128;}}
/* 002900f4: move a2,a0 */ c->r[6]=c->r[4];
/* 002900f8: lw a1,0x0(a2) */ c->r[5]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000000)));
/* 002900fc: nop  */ (void)0;
L_00290100:;
/* 00290100: addiu a2,a2,0x4 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 00290104: lhu a0,0x8(a1) */ c->r[4]=hword((uint32_t)c->r[5]+UINT32_C(0x00000008));
/* 00290108: lhu v1,0x6(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000006));
/* 0029010c: sltu v1,v1,a0 */ c->r[3]=(c->r[3]<c->r[4]);
/* 00290110: bne v1,zero,0x0029012c */ {int taken=(c->r[3]!=c->r[0]);/* delay 00290114 */ c->r[2]=c->r[0];if(taken){goto L_0029012c;}}
/* 00290118: addiu t0,t0,0x1 */ c->r[8]=sx((uint32_t)c->r[8]+UINT32_C(0x00000001));
/* 0029011c: slt v0,t0,a3 */ c->r[2]=less(c->r[8],c->r[7]);
/* 00290120: bnel v0,zero,0x00290100 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00290124 */ c->r[5]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000000)));goto L_00290100;}}
L_00290128:;
/* 00290128: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_0029012c:;
/* 0029012c: jr ra */ /* delay 00290130 */ (void)0;return;
}

static void body_00290138(BattleStatusPairsValues *c){
/* 00290138: move a3,a1 */ c->r[7]=c->r[5];
/* 0029013c: blez a3,0x00290178 */ {int taken=((neg(c->r[7])||!c->r[7]));/* delay 00290140 */ c->r[8]=c->r[0];if(taken){goto L_00290178;}}
/* 00290144: move a2,a0 */ c->r[6]=c->r[4];
/* 00290148: lw a1,0x0(a2) */ c->r[5]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000000)));
/* 0029014c: nop  */ (void)0;
L_00290150:;
/* 00290150: addiu a2,a2,0x4 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 00290154: lhu a0,0xc(a1) */ c->r[4]=hword((uint32_t)c->r[5]+UINT32_C(0x0000000c));
/* 00290158: lhu v1,0xa(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x0000000a));
/* 0029015c: sltu v1,v1,a0 */ c->r[3]=(c->r[3]<c->r[4]);
/* 00290160: bne v1,zero,0x0029017c */ {int taken=(c->r[3]!=c->r[0]);/* delay 00290164 */ c->r[2]=c->r[0];if(taken){goto L_0029017c;}}
/* 00290168: addiu t0,t0,0x1 */ c->r[8]=sx((uint32_t)c->r[8]+UINT32_C(0x00000001));
/* 0029016c: slt v0,t0,a3 */ c->r[2]=less(c->r[8],c->r[7]);
/* 00290170: bnel v0,zero,0x00290150 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00290174 */ c->r[5]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000000)));goto L_00290150;}}
L_00290178:;
/* 00290178: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_0029017c:;
/* 0029017c: jr ra */ /* delay 00290180 */ (void)0;return;
}

static void body_00290188(BattleStatusPairsValues *c){
/* 00290188: blez a1,0x002901c0 */ {int taken=((neg(c->r[5])||!c->r[5]));/* delay 0029018c */ c->r[8]=c->r[0];if(taken){goto L_002901c0;}}
/* 00290190: move a3,a0 */ c->r[7]=c->r[4];
/* 00290194: lw a0,0x0(a3) */ c->r[4]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00000000)));
L_00290198:;
/* 00290198: addiu a3,a3,0x4 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0x00000004));
/* 0029019c: lhu v1,0xe(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x0000000e));
/* 002901a0: andi v1,v1,0xfff */ c->r[3]=c->r[3]&UINT64_C(0xfff);
/* 002901a4: and v1,v1,a2 */ c->r[3]=c->r[3]&c->r[6];
/* 002901a8: bne v1,zero,0x002901c4 */ {int taken=(c->r[3]!=c->r[0]);/* delay 002901ac */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_002901c4;}}
/* 002901b0: addiu t0,t0,0x1 */ c->r[8]=sx((uint32_t)c->r[8]+UINT32_C(0x00000001));
/* 002901b4: slt v0,t0,a1 */ c->r[2]=less(c->r[8],c->r[5]);
/* 002901b8: bnel v0,zero,0x00290198 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002901bc */ c->r[4]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00000000)));goto L_00290198;}}
L_002901c0:;
/* 002901c0: move v0,zero */ c->r[2]=c->r[0];
L_002901c4:;
/* 002901c4: jr ra */ /* delay 002901c8 */ (void)0;return;
}

static void body_002901d0(BattleStatusPairsValues *c){
/* 002901d0: addiu sp,sp,-0x60 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffa0));
/* 002901d4: sd s4,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[20]);
/* 002901d8: move s4,a1 */ c->r[20]=c->r[5];
/* 002901dc: sd s2,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[18]);
/* 002901e0: move s2,a2 */ c->r[18]=c->r[6];
/* 002901e4: sd s3,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[19]);
/* 002901e8: move s3,zero */ c->r[19]=c->r[0];
/* 002901ec: sd s0,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[16]);
/* 002901f0: sd s1,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[17]);
/* 002901f4: sd s5,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[21]);
/* 002901f8: sd s6,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[22]);
/* 002901fc: sd s7,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[23]);
/* 00290200: sd s8,0x50(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000050),c->r[30]);
/* 00290204: sd ra,0x58(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000058),c->r[31]);
/* 00290208: blez s4,0x0029045c */ {int taken=((neg(c->r[20])||!c->r[20]));/* delay 0029020c */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[4]);if(taken){goto L_0029045c;}}
/* 00290210: lui v0,0x1 */ c->r[2]=sx(UINT32_C(0x00010000));
/* 00290214: lui v1,0x2 */ c->r[3]=sx(UINT32_C(0x00020000));
/* 00290218: lui a0,0x100 */ c->r[4]=sx(UINT32_C(0x01000000));
/* 0029021c: and s8,s2,v0 */ c->r[30]=c->r[18]&c->r[2];
/* 00290220: and s7,s2,v1 */ c->r[23]=c->r[18]&c->r[3];
/* 00290224: and s6,s2,a0 */ c->r[22]=c->r[18]&c->r[4];
/* 00290228: andi s5,s2,0x1 */ c->r[21]=c->r[18]&UINT64_C(0x1);
/* 0029022c: lw v1,0x0(sp) */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000000)));
L_00290230:;
/* 00290230: sll v0,s3,0x2 */ c->r[2]=sx((uint32_t)c->r[19]<<2u);
/* 00290234: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00290238: beq s5,zero,0x00290254 */ {int taken=(c->r[21]==c->r[0]);/* delay 0029023c */ c->r[17]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));if(taken){goto L_00290254;}}
/* 00290240: lh s0,0x10(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000010)));
/* 00290244: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x0029024c);/* delay 00290248 */ c->r[4]=sx(UINT32_C(0x00000004));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0029024c: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290250 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
L_00290254:;
/* 00290254: andi v0,s2,0x2 */ c->r[2]=c->r[18]&UINT64_C(0x2);
/* 00290258: beql v0,zero,0x00290278 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0029025c */ c->r[2]=c->r[18]&UINT64_C(0x4);goto L_00290278;}}
/* 00290260: lh s0,0x10(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000010)));
/* 00290264: jal 0x00267f18 */ c->r[31]=UINT64_C(0x0029026c);/* delay 00290268 */ c->r[4]=sx(UINT32_C(0x00000004));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMin(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0029026c: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290270 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 00290274: andi v0,s2,0x4 */ c->r[2]=c->r[18]&UINT64_C(0x4);
L_00290278:;
/* 00290278: beql v0,zero,0x00290298 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0029027c */ c->r[2]=c->r[18]&UINT64_C(0x8);goto L_00290298;}}
/* 00290280: lh s0,0x12(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000012)));
/* 00290284: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x0029028c);/* delay 00290288 */ c->r[4]=sx(UINT32_C(0x00000005));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0029028c: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290290 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 00290294: andi v0,s2,0x8 */ c->r[2]=c->r[18]&UINT64_C(0x8);
L_00290298:;
/* 00290298: beql v0,zero,0x002902b8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0029029c */ c->r[2]=c->r[18]&UINT64_C(0x10);goto L_002902b8;}}
/* 002902a0: lh s0,0x12(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000012)));
/* 002902a4: jal 0x00267f18 */ c->r[31]=UINT64_C(0x002902ac);/* delay 002902a8 */ c->r[4]=sx(UINT32_C(0x00000005));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMin(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002902ac: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 002902b0 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 002902b4: andi v0,s2,0x10 */ c->r[2]=c->r[18]&UINT64_C(0x10);
L_002902b8:;
/* 002902b8: beql v0,zero,0x002902d8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002902bc */ c->r[2]=c->r[18]&UINT64_C(0x20);goto L_002902d8;}}
/* 002902c0: lh s0,0x14(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000014)));
/* 002902c4: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x002902cc);/* delay 002902c8 */ c->r[4]=sx(UINT32_C(0x00000006));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002902cc: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 002902d0 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 002902d4: andi v0,s2,0x20 */ c->r[2]=c->r[18]&UINT64_C(0x20);
L_002902d8:;
/* 002902d8: beql v0,zero,0x002902f8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002902dc */ c->r[2]=c->r[18]&UINT64_C(0x40);goto L_002902f8;}}
/* 002902e0: lh s0,0x14(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000014)));
/* 002902e4: jal 0x00267f18 */ c->r[31]=UINT64_C(0x002902ec);/* delay 002902e8 */ c->r[4]=sx(UINT32_C(0x00000006));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMin(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002902ec: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 002902f0 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 002902f4: andi v0,s2,0x40 */ c->r[2]=c->r[18]&UINT64_C(0x40);
L_002902f8:;
/* 002902f8: beql v0,zero,0x00290318 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002902fc */ c->r[2]=c->r[18]&UINT64_C(0x80);goto L_00290318;}}
/* 00290300: lh s0,0x16(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000016)));
/* 00290304: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x0029030c);/* delay 00290308 */ c->r[4]=sx(UINT32_C(0x00000007));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0029030c: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290310 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 00290314: andi v0,s2,0x80 */ c->r[2]=c->r[18]&UINT64_C(0x80);
L_00290318:;
/* 00290318: beql v0,zero,0x00290338 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0029031c */ c->r[2]=c->r[18]&UINT64_C(0x100);goto L_00290338;}}
/* 00290320: lh s0,0x16(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000016)));
/* 00290324: jal 0x00267f18 */ c->r[31]=UINT64_C(0x0029032c);/* delay 00290328 */ c->r[4]=sx(UINT32_C(0x00000007));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMin(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0029032c: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290330 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 00290334: andi v0,s2,0x100 */ c->r[2]=c->r[18]&UINT64_C(0x100);
L_00290338:;
/* 00290338: beql v0,zero,0x00290358 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0029033c */ c->r[2]=c->r[18]&UINT64_C(0x200);goto L_00290358;}}
/* 00290340: lh s0,0x18(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000018)));
/* 00290344: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x0029034c);/* delay 00290348 */ c->r[4]=sx(UINT32_C(0x00000008));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0029034c: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290350 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 00290354: andi v0,s2,0x200 */ c->r[2]=c->r[18]&UINT64_C(0x200);
L_00290358:;
/* 00290358: beql v0,zero,0x00290378 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0029035c */ c->r[2]=c->r[18]&UINT64_C(0x1000);goto L_00290378;}}
/* 00290360: lh s0,0x18(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000018)));
/* 00290364: jal 0x00267f18 */ c->r[31]=UINT64_C(0x0029036c);/* delay 00290368 */ c->r[4]=sx(UINT32_C(0x00000008));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMin(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0029036c: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290370 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 00290374: andi v0,s2,0x1000 */ c->r[2]=c->r[18]&UINT64_C(0x1000);
L_00290378:;
/* 00290378: beql v0,zero,0x00290398 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0029037c */ c->r[2]=c->r[18]&UINT64_C(0x2000);goto L_00290398;}}
/* 00290380: lh s0,0x1a(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x0000001a)));
/* 00290384: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x0029038c);/* delay 00290388 */ c->r[4]=sx(UINT32_C(0x00000009));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 0029038c: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290390 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 00290394: andi v0,s2,0x2000 */ c->r[2]=c->r[18]&UINT64_C(0x2000);
L_00290398:;
/* 00290398: beql v0,zero,0x002903b8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0029039c */ c->r[2]=c->r[18]&UINT64_C(0x4000);goto L_002903b8;}}
/* 002903a0: lh s0,0x1c(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x0000001c)));
/* 002903a4: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x002903ac);/* delay 002903a8 */ c->r[4]=sx(UINT32_C(0x0000000a));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002903ac: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 002903b0 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 002903b4: andi v0,s2,0x4000 */ c->r[2]=c->r[18]&UINT64_C(0x4000);
L_002903b8:;
/* 002903b8: beql v0,zero,0x002903d8 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002903bc */ c->r[2]=c->r[18]&UINT64_C(0x8000);goto L_002903d8;}}
/* 002903c0: lh s0,0x1e(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x0000001e)));
/* 002903c4: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x002903cc);/* delay 002903c8 */ c->r[4]=sx(UINT32_C(0x0000000b));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002903cc: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 002903d0 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
/* 002903d4: andi v0,s2,0x8000 */ c->r[2]=c->r[18]&UINT64_C(0x8000);
L_002903d8:;
/* 002903d8: beq v0,zero,0x002903f4 */ {int taken=(c->r[2]==c->r[0]);/* delay 002903dc */ (void)0;if(taken){goto L_002903f4;}}
/* 002903e0: lh s0,0x20(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000020)));
/* 002903e4: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x002903ec);/* delay 002903e8 */ c->r[4]=sx(UINT32_C(0x0000000c));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002903ec: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 002903f0 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
L_002903f4:;
/* 002903f4: beq s8,zero,0x00290410 */ {int taken=(c->r[30]==c->r[0]);/* delay 002903f8 */ (void)0;if(taken){goto L_00290410;}}
/* 002903fc: lh s0,0x22(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000022)));
/* 00290400: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x00290408);/* delay 00290404 */ c->r[4]=sx(UINT32_C(0x0000000d));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00290408: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 0029040c */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
L_00290410:;
/* 00290410: beq s7,zero,0x0029042c */ {int taken=(c->r[23]==c->r[0]);/* delay 00290414 */ (void)0;if(taken){goto L_0029042c;}}
/* 00290418: lh s0,0x24(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000024)));
/* 0029041c: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x00290424);/* delay 00290420 */ c->r[4]=sx(UINT32_C(0x0000000e));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00290424: bne s0,v0,0x00290460 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290428 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_00290460;}}
L_0029042c:;
/* 0029042c: beql s6,zero,0x00290450 */ {int taken=(c->r[22]==c->r[0]);if(taken){/* delay 00290430 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00290450;}}
/* 00290434: lh s0,0x26(s1) */ c->r[16]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000026)));
/* 00290438: jal 0x00267ec8 */ c->r[31]=UINT64_C(0x00290440);/* delay 0029043c */ c->r[4]=sx(UINT32_C(0x0000000f));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetHojoCounterMax(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00290440: beq s0,v0,0x00290450 */ {int taken=(c->r[16]==c->r[2]);/* delay 00290444 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));if(taken){goto L_00290450;}}
/* 00290448: b 0x00290460 */ /* delay 0029044c */ c->r[2]=sx(UINT32_C(0x00000001));goto L_00290460;
L_00290450:;
/* 00290450: slt v0,s3,s4 */ c->r[2]=less(c->r[19],c->r[20]);
/* 00290454: bne v0,zero,0x00290230 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00290458 */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000000)));if(taken){goto L_00290230;}}
L_0029045c:;
/* 0029045c: move v0,zero */ c->r[2]=c->r[0];
L_00290460:;
/* 00290460: ld s0,0x10(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00290464: ld s1,0x18(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00290468: ld s2,0x20(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0029046c: ld s3,0x28(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 00290470: ld s4,0x30(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 00290474: ld s5,0x38(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 00290478: ld s6,0x40(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 0029047c: ld s7,0x48(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 00290480: ld s8,0x50(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000050));
/* 00290484: ld ra,0x58(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000058));
/* 00290488: jr ra */ /* delay 0029048c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000060));return;
}

static void body_00290490(BattleStatusPairsValues *c){
/* 00290490: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00290494: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00290498: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0029049c: jal 0x002469a0 */ c->r[31]=UINT64_C(0x002904a4);/* delay 002904a0 */ c->r[16]=c->r[4];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002904a4: move v1,v0 */ c->r[3]=c->r[2];
/* 002904a8: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
/* 002904ac: li a1,0x42 */ c->r[5]=sx(UINT32_C(0x00000042));
/* 002904b0: li a2,0x3 */ c->r[6]=sx(UINT32_C(0x00000003));
/* 002904b4: beq s0,v0,0x002904d0 */ {int taken=(c->r[16]==c->r[2]);/* delay 002904b8 */ c->r[4]=sx(UINT32_C(0x00000004));if(taken){goto L_002904d0;}}
/* 002904bc: beql s0,a0,0x002904e0 */ {int taken=(c->r[16]==c->r[4]);if(taken){/* delay 002904c0 */ c->r[4]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000130)));goto L_002904e0;}}
/* 002904c4: b 0x002904ec */ /* delay 002904c8 */ (void)0;goto L_002904ec;
L_002904d0:;
/* 002904d0: jal 0x00289310 */ c->r[31]=UINT64_C(0x002904d8);/* delay 002904d4 */ c->r[4]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000130)));body_00289310(c);
/* 002904d8: b 0x002904ec */ /* delay 002904dc */ (void)0;goto L_002904ec;
L_002904e0:;
/* 002904e0: li a1,0x46 */ c->r[5]=sx(UINT32_C(0x00000046));
/* 002904e4: jal 0x00289310 */ c->r[31]=UINT64_C(0x002904ec);/* delay 002904e8 */ c->r[6]=sx(UINT32_C(0x00000003));body_00289310(c);
L_002904ec:;
/* 002904ec: blezl s0,0x00290514 */ {int taken=((neg(c->r[16])||!c->r[16]));if(taken){/* delay 002904f0 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00290514;}}
/* 002904f4: slti v0,s0,0x3 */ c->r[2]=less(c->r[16],sx(UINT32_C(0x00000003)));
/* 002904f8: bne v0,zero,0x00290508 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002904fc */ c->r[2]=sx(UINT32_C(0x00000004));if(taken){goto L_00290508;}}
/* 00290500: bne s0,v0,0x00290514 */ {int taken=(c->r[16]!=c->r[2]);/* delay 00290504 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_00290514;}}
L_00290508:;
/* 00290508: jal 0x0028d090 */ c->r[31]=UINT64_C(0x00290510);/* delay 0029050c */ c->r[4]=sx(UINT32_C(0x0000000d));body_0028d090(c);
/* 00290510: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00290514:;
/* 00290514: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00290518: jr ra */ /* delay 0029051c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00290568(BattleStatusPairsValues *c){
/* 00290568: addiu sp,sp,-0x150 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffeb0));
/* 0029056c: sd s1,0x108(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000108),c->r[17]);
/* 00290570: move s1,a0 */ c->r[17]=c->r[4];
/* 00290574: sd s6,0x130(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000130),c->r[22]);
/* 00290578: move s6,zero */ c->r[22]=c->r[0];
/* 0029057c: sd s7,0x138(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000138),c->r[23]);
/* 00290580: sd s0,0x100(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000100),c->r[16]);
/* 00290584: sd s2,0x110(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000110),c->r[18]);
/* 00290588: sd s3,0x118(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000118),c->r[19]);
/* 0029058c: sd s4,0x120(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000120),c->r[20]);
/* 00290590: sd s5,0x128(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000128),c->r[21]);
/* 00290594: sd s8,0x140(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000140),c->r[30]);
/* 00290598: sd ra,0x148(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000148),c->r[31]);
/* 0029059c: jal 0x002469a0 */ c->r[31]=UINT64_C(0x002905a4);/* delay 002905a0 */ c->r[23]=c->r[5];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002905a4: lw v1,0x60(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000060)));
/* 002905a8: lui a0,0x800 */ c->r[4]=sx(UINT32_C(0x08000000));
/* 002905ac: and v1,v1,a0 */ c->r[3]=c->r[3]&c->r[4];
/* 002905b0: bne v1,zero,0x0029074c */ {int taken=(c->r[3]!=c->r[0]);/* delay 002905b4 */ c->r[2]=c->r[0];if(taken){goto L_0029074c;}}
/* 002905b8: move s2,zero */ c->r[18]=c->r[0];
/* 002905bc: move s5,zero */ c->r[21]=c->r[0];
/* 002905c0: move s0,zero */ c->r[16]=c->r[0];
/* 002905c4: li s8,0x1 */ c->r[30]=sx(UINT32_C(0x00000001));
/* 002905c8: addiu s4,sp,0x80 */ c->r[20]=sx((uint32_t)c->r[29]+UINT32_C(0x00000080));
/* 002905cc: move s3,sp */ c->r[19]=c->r[29];
/* 002905d0: sllv v0,s8,s0 */ c->r[2]=sx((uint32_t)c->r[30]<<((unsigned)c->r[16]&31u));
/* 002905d4: nop  */ (void)0;
L_002905d8:;
/* 002905d8: and v0,s7,v0 */ c->r[2]=c->r[23]&c->r[2];
/* 002905dc: beql v0,zero,0x0029061c */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002905e0 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));goto L_0029061c;}}
/* 002905e4: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x002905ec);/* delay 002905e8 */ c->r[4]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=native_frame(c,2u,UINT32_C(0x002905e4),UINT32_C(0xf0ff0010));nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 002905ec: beq v0,zero,0x00290600 */ {int taken=(c->r[2]==c->r[0]);/* delay 002905f0 */ (void)0;if(taken){goto L_00290600;}}
/* 002905f4: sw v0,0x0(s3) */ sw((uint32_t)c->r[19]+UINT32_C(0x00000000),(uint32_t)c->r[2]);
/* 002905f8: addiu s3,s3,0x4 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000004));
/* 002905fc: addiu s2,s2,0x1 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));
L_00290600:;
/* 00290600: jal 0x00246a40 */ c->r[31]=UINT64_C(0x00290608);/* delay 00290604 */ c->r[4]=c->r[16];nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetPartyFromFormindex(c->r[4]);nocturneBattleStatusPairsSetStackPointer((uint32_t)c->r[29]);
/* 00290608: beq v0,zero,0x0029061c */ {int taken=(c->r[2]==c->r[0]);/* delay 0029060c */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));if(taken){goto L_0029061c;}}
/* 00290610: sw v0,0x0(s4) */ sw((uint32_t)c->r[20]+UINT32_C(0x00000000),(uint32_t)c->r[2]);
/* 00290614: addiu s4,s4,0x4 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000004));
/* 00290618: addiu s5,s5,0x1 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0x00000001));
L_0029061c:;
/* 0029061c: slti v0,s0,0x10 */ c->r[2]=less(c->r[16],sx(UINT32_C(0x00000010)));
/* 00290620: bne v0,zero,0x002905d8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00290624 */ c->r[2]=sx((uint32_t)c->r[30]<<((unsigned)c->r[16]&31u));if(taken){goto L_002905d8;}}
/* 00290628: beq s2,zero,0x0029074c */ {int taken=(c->r[18]==c->r[0]);/* delay 0029062c */ c->r[2]=c->r[0];if(taken){goto L_0029074c;}}
/* 00290630: addiu v1,s1,-0x24 */ c->r[3]=sx((uint32_t)c->r[17]+UINT32_C(0xffffffdc));
/* 00290634: sltiu v0,v1,0xd5 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x000000d5)));
/* 00290638: beq v0,zero,0x0029074c */ {int taken=(c->r[2]==c->r[0]);/* delay 0029063c */ c->r[2]=c->r[22];if(taken){goto L_0029074c;}}
/* 00290640: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 00290644: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 00290648: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0029064c: lw v1,0x5de0(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00005de0)));
/* 00290650: jr v1 */ {uint64_t target=c->r[3];/* delay 00290654 */ (void)0;switch(target){case UINT64_C(0x00290658):goto L_00290658;case UINT64_C(0x00290670):goto L_00290670;case UINT64_C(0x002906a8):goto L_002906a8;case UINT64_C(0x002906bc):goto L_002906bc;case UINT64_C(0x002906d8):goto L_002906d8;case UINT64_C(0x00290710):goto L_00290710;case UINT64_C(0x00290748):goto L_00290748;default:abort();}}
L_00290658:;
/* 00290658: move a1,s2 */ c->r[5]=c->r[18];
/* 0029065c: jal 0x002900e8 */ c->r[31]=UINT64_C(0x00290664);/* delay 00290660 */ c->r[4]=c->r[29];body_002900e8(c);
/* 00290664: b 0x002906c8 */ /* delay 00290668 */ (void)0;goto L_002906c8;
L_00290670:;
/* 00290670: sll v0,s1,0x4 */ c->r[2]=sx((uint32_t)c->r[17]<<4u);
/* 00290674: move a1,s2 */ c->r[5]=c->r[18];
/* 00290678: subu v0,v0,s1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[17]);
/* 0029067c: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00290680: lui a2,0x3d */ c->r[6]=sx(UINT32_C(0x003d0000));
/* 00290684: addu a2,a2,v0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[2]);
/* 00290688: lhu a2,0x79be(a2) */ c->r[6]=hword((uint32_t)c->r[6]+UINT32_C(0x000079be));
/* 0029068c: jal 0x00290188 */ c->r[31]=UINT64_C(0x00290694);/* delay 00290690 */ c->r[4]=c->r[29];body_00290188(c);
/* 00290694: beql v0,zero,0x00290748 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00290698 */ c->r[22]=sx(UINT32_C(0x00000001));goto L_00290748;}}
/* 0029069c: b 0x0029074c */ /* delay 002906a0 */ c->r[2]=c->r[22];goto L_0029074c;
L_002906a8:;
/* 002906a8: move a0,sp */ c->r[4]=c->r[29];
/* 002906ac: jal 0x002900e8 */ c->r[31]=UINT64_C(0x002906b4);/* delay 002906b0 */ c->r[5]=c->r[18];body_002900e8(c);
/* 002906b4: beq v0,zero,0x0029074c */ {int taken=(c->r[2]==c->r[0]);/* delay 002906b8 */ c->r[2]=c->r[22];if(taken){goto L_0029074c;}}
L_002906bc:;
/* 002906bc: move a1,s2 */ c->r[5]=c->r[18];
/* 002906c0: jal 0x00290138 */ c->r[31]=UINT64_C(0x002906c8);/* delay 002906c4 */ c->r[4]=c->r[29];body_00290138(c);
L_002906c8:;
/* 002906c8: bnel v0,zero,0x00290748 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002906cc */ c->r[22]=sx(UINT32_C(0x00000001));goto L_00290748;}}
/* 002906d0: b 0x0029074c */ /* delay 002906d4 */ c->r[2]=c->r[22];goto L_0029074c;
L_002906d8:;
/* 002906d8: sll v0,s1,0x4 */ c->r[2]=sx((uint32_t)c->r[17]<<4u);
/* 002906dc: move a1,s5 */ c->r[5]=c->r[21];
/* 002906e0: subu v0,v0,s1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[17]);
/* 002906e4: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 002906e8: lui a2,0x3d */ c->r[6]=sx(UINT32_C(0x003d0000));
/* 002906ec: addu a2,a2,v0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[2]);
/* 002906f0: lw a2,0x79c0(a2) */ c->r[6]=sx(word((uint32_t)c->r[6]+UINT32_C(0x000079c0)));
/* 002906f4: jal 0x002901d0 */ c->r[31]=UINT64_C(0x002906fc);/* delay 002906f8 */ c->r[4]=sx((uint32_t)c->r[29]+UINT32_C(0x00000080));body_002901d0(c);
/* 002906fc: beql v0,zero,0x00290748 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00290700 */ c->r[22]=sx(UINT32_C(0x00000004));goto L_00290748;}}
/* 00290704: b 0x0029074c */ /* delay 00290708 */ c->r[2]=c->r[22];goto L_0029074c;
L_00290710:;
/* 00290710: move a0,sp */ c->r[4]=c->r[29];
/* 00290714: jal 0x002900e8 */ c->r[31]=UINT64_C(0x0029071c);/* delay 00290718 */ c->r[5]=c->r[18];body_002900e8(c);
/* 0029071c: beq v0,zero,0x00290748 */ {int taken=(c->r[2]==c->r[0]);/* delay 00290720 */ c->r[2]=sx((uint32_t)c->r[17]<<4u);if(taken){goto L_00290748;}}
/* 00290724: move a1,s2 */ c->r[5]=c->r[18];
/* 00290728: subu v0,v0,s1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[17]);
/* 0029072c: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00290730: lui a2,0x3d */ c->r[6]=sx(UINT32_C(0x003d0000));
/* 00290734: addu a2,a2,v0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[2]);
/* 00290738: lhu a2,0x79be(a2) */ c->r[6]=hword((uint32_t)c->r[6]+UINT32_C(0x000079be));
/* 0029073c: jal 0x00290188 */ c->r[31]=UINT64_C(0x00290744);/* delay 00290740 */ c->r[4]=c->r[29];body_00290188(c);
/* 00290744: sltiu s6,v0,0x1 */ c->r[22]=(c->r[2]<sx(UINT32_C(0x00000001)));
L_00290748:;
/* 00290748: move v0,s6 */ c->r[2]=c->r[22];
L_0029074c:;
/* 0029074c: ld s0,0x100(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000100));
/* 00290750: ld s1,0x108(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000108));
/* 00290754: ld s2,0x110(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000110));
/* 00290758: ld s3,0x118(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000118));
/* 0029075c: ld s4,0x120(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000120));
/* 00290760: ld s5,0x128(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000128));
/* 00290764: ld s6,0x130(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000130));
/* 00290768: ld s7,0x138(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000138));
/* 0029076c: ld s8,0x140(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000140));
/* 00290770: ld ra,0x148(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000148));
/* 00290774: jr ra */ /* delay 00290778 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000150));return;
}

static void body_0029ba80(BattleStatusPairsValues *c){
/* 0029ba80: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0029ba84: beql a0,v0,0x0029bac0 */ {int taken=(c->r[4]==c->r[2]);if(taken){/* delay 0029ba88 */ c->r[2]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000000)));goto L_0029bac0;}}
/* 0029ba8c: beql a0,zero,0x0029bab0 */ {int taken=(c->r[4]==c->r[0]);if(taken){/* delay 0029ba90 */ c->r[2]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000000)));goto L_0029bab0;}}
/* 0029ba94: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
/* 0029ba98: beq a0,v0,0x0029bac8 */ {int taken=(c->r[4]==c->r[2]);/* delay 0029ba9c */ c->r[3]=sx(UINT32_C(0x00000005));if(taken){goto L_0029bac8;}}
/* 0029baa0: beq a0,v1,0x0029bad8 */ {int taken=(c->r[4]==c->r[3]);/* delay 0029baa4 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0029bad8;}}
/* 0029baa8: jr ra */ /* delay 0029baac */ c->r[2]=sx(UINT32_C(0xffffffff));return;
L_0029bab0:;
/* 0029bab0: sra v0,v0,0x1 */ c->r[2]=sar((uint32_t)c->r[2],1u);
/* 0029bab4: xori v0,v0,0x1 */ c->r[2]=c->r[2]^UINT64_C(0x1);
/* 0029bab8: jr ra */ /* delay 0029babc */ c->r[2]=c->r[2]&UINT64_C(0x1);return;
L_0029bac0:;
/* 0029bac0: jr ra */ /* delay 0029bac4 */ c->r[2]=c->r[2]&UINT64_C(0x4);return;
L_0029bac8:;
/* 0029bac8: lw v0,0x0(a1) */ c->r[2]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 0029bacc: jr ra */ /* delay 0029bad0 */ c->r[2]=c->r[2]&UINT64_C(0x8);return;
L_0029bad8:;
/* 0029bad8: jr ra */ /* delay 0029badc */ (void)0;return;
}

static void body_0029bae0(BattleStatusPairsValues *c){
/* 0029bae0: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0029bae4: lw a1,-0x5750(gp) */ c->r[5]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 0029bae8: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 0029baec: lui at,0x1 */ c->r[1]=sx(UINT32_C(0x00010000));
/* 0029baf0: ori at,at,0x1ab8 */ c->r[1]=c->r[1]|UINT64_C(0x1ab8);
/* 0029baf4: addu a1,at,a1 */ c->r[5]=sx((uint32_t)c->r[1]+(uint32_t)c->r[5]);
/* 0029baf8: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0029bafc: j 0x0029ba80 */ /* delay 0029bb00 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_0029ba80(c);return;
}
static BattleStatusPairsValues begin(void){
 BattleStatusPairsValues c={0};unsigned i;
 for(i=16u;i<=23u;++i)c.r[i]=nocturneBattleStatusPairsReadGpr(i);
 c.r[28]=nocturneBattleStatusPairsReadGpr(28);c.r[30]=nocturneBattleStatusPairsReadGpr(30);
 c.r[31]=nocturneBattleStatusPairsReadGpr(31);c.r[29]=nocturneBattleStatusPairsStackPointer();
 for(i=20u;i<=25u;++i)c.f[i]=nocturneBattleStatusPairsReadFpr(i);
 return c;
}
void ps2BattleStatusPairs_00253DE0(void){BattleStatusPairsValues c=begin();body_00253de0(&c);nocturneBattleStatusPairsSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleStatusPairs_00253E00(uint64_t context){BattleStatusPairsValues c=begin();c.r[4]=context;body_00253e00(&c);nocturneBattleStatusPairsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleStatusPairs_00254010(uint64_t context){BattleStatusPairsValues c=begin();c.r[4]=context;body_00254010(&c);nocturneBattleStatusPairsSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleStatusPairs_00254058(uint64_t context){BattleStatusPairsValues c=begin();c.r[4]=context;body_00254058(&c);nocturneBattleStatusPairsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleStatusPairs_00254178(uint64_t context){BattleStatusPairsValues c=begin();c.r[4]=context;body_00254178(&c);nocturneBattleStatusPairsSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleStatusPairs_00254190(uint64_t context){BattleStatusPairsValues c=begin();c.r[4]=context;body_00254190(&c);nocturneBattleStatusPairsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleStatusPairs_00254360(uint64_t context){BattleStatusPairsValues c=begin();c.r[4]=context;body_00254360(&c);nocturneBattleStatusPairsSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleStatusPairs_002543A0(uint64_t context){BattleStatusPairsValues c=begin();c.r[4]=context;body_002543a0(&c);nocturneBattleStatusPairsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
