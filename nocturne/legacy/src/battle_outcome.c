/* Complete23 original outcome/motion/press bodies,1203 fixed instructions.
 * Real guest frames and registered algorithms; no service-answer replay.
 * Integer transport carriers retain native V0 versus F0 ownership. */
#include "battle_outcome.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include "battle_action_choice.h"
#include "battle_action_finish.h"
#include "battle_action_printf_frames.h"
#include "battle_action_process.h"
#include "battle_action_scale_lookup_frames.h"
#include "battle_action_sequence.h"
#include "battle_action_status.h"
#include "battle_check1_packets.h"
#include "battle_formation.h"
#include "battle_kouka_packets.h"
#include "battle_presentation.h"
#include "battle_roster.h"
#include "battle_work_access.h"
#include "combat_calculation.h"
#include "nocturne.h"
#include "screen_fade.h"
#include <string.h>
typedef struct BattleOutcomeValues {uint64_t r[32],lo,hi;uint32_t f[32],condition;} BattleOutcomeValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleOutcomeAddress(a);}
static uint16_t hword(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}

static void body_001b17e0(BattleOutcomeValues *c);
static void body_001e3b68(BattleOutcomeValues *c);
static void body_001e3b70(BattleOutcomeValues *c);
static void body_001e3b78(BattleOutcomeValues *c);
static void body_001e3cc0(BattleOutcomeValues *c);
static void body_0024ce78(BattleOutcomeValues *c);
static void body_0024cff8(BattleOutcomeValues *c);
static void body_0024d238(BattleOutcomeValues *c);
static void body_0024d428(BattleOutcomeValues *c);
static void body_00252cd8(BattleOutcomeValues *c);
static void body_00256c00(BattleOutcomeValues *c);
static void body_00257098(BattleOutcomeValues *c);
static void body_002570b8(BattleOutcomeValues *c);
static void body_00257210(BattleOutcomeValues *c);
static void body_00257230(BattleOutcomeValues *c);
static void body_002572c0(BattleOutcomeValues *c);
static void body_002573a8(BattleOutcomeValues *c);
static void body_00257440(BattleOutcomeValues *c);
static void body_00262a68(BattleOutcomeValues *c);
static void body_00262ac8(BattleOutcomeValues *c);
static void body_00263778(BattleOutcomeValues *c);
static void body_002642e0(BattleOutcomeValues *c);
static void body_00264368(BattleOutcomeValues *c);

static void body_001b17e0(BattleOutcomeValues *c){
/* 001b17e0: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 001b17e4: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 001b17e8: lh v0,0x92(a1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000092)));
/* 001b17ec: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
/* 001b17f0: lh a0,0x92(a0) */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000092)));
/* 001b17f4: jal 0x0016b8a8 */ c->r[31]=UINT64_C(0x001b17fc);/* delay 001b17f8 */ c->r[5]=sx((uint32_t)c->r[5]<<((unsigned)c->r[2]&31u));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);effBTLSkillSetFormationInfo(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 001b17fc: li a0,0xe */ c->r[4]=sx(UINT32_C(0x0000000e));
/* 001b1800: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 001b1804: j 0x001b1740 */ /* delay 001b1808 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbCameraSetState(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);return;
}

static void body_001e3b68(BattleOutcomeValues *c){
/* 001e3b68: jr ra */ /* delay 001e3b6c */ sh((uint32_t)c->r[4]+UINT32_C(0x000000b8),(uint16_t)c->r[5]);return;
}

static void body_001e3b70(BattleOutcomeValues *c){
/* 001e3b70: jr ra */ /* delay 001e3b74 */ sw((uint32_t)c->r[4]+UINT32_C(0x000000b4),c->f[12]);return;
}

static void body_001e3b78(BattleOutcomeValues *c){
/* 001e3b78: sh a2,0xbc(a0) */ sh((uint32_t)c->r[4]+UINT32_C(0x000000bc),(uint16_t)c->r[6]);
/* 001e3b7c: jr ra */ /* delay 001e3b80 */ sh((uint32_t)c->r[4]+UINT32_C(0x000000ba),(uint16_t)c->r[5]);return;
}

static void body_001e3cc0(BattleOutcomeValues *c){
/* 001e3cc0: move t3,a0 */ c->r[11]=c->r[4];
/* 001e3cc4: lui a0,0xffbf */ c->r[4]=sx(UINT32_C(0xffbf0000));
/* 001e3cc8: lw v0,0xa4(t3) */ c->r[2]=sx(word((uint32_t)c->r[11]+UINT32_C(0x000000a4)));
/* 001e3ccc: li v1,-0x2 */ c->r[3]=sx(UINT32_C(0xfffffffe));
/* 001e3cd0: li t1,-0x21 */ c->r[9]=sx(UINT32_C(0xffffffdf));
/* 001e3cd4: li t2,-0x41 */ c->r[10]=sx(UINT32_C(0xffffffbf));
/* 001e3cd8: and v0,v0,v1 */ c->r[2]=c->r[2]&c->r[3];
/* 001e3cdc: lui v1,0xff7f */ c->r[3]=sx(UINT32_C(0xff7f0000));
/* 001e3ce0: and v0,v0,t1 */ c->r[2]=c->r[2]&c->r[9];
/* 001e3ce4: ori a0,a0,0xffff */ c->r[4]=c->r[4]|UINT64_C(0xffff);
/* 001e3ce8: and v0,v0,t2 */ c->r[2]=c->r[2]&c->r[10];
/* 001e3cec: ori v1,v1,0xffff */ c->r[3]=c->r[3]|UINT64_C(0xffff);
/* 001e3cf0: and v0,v0,a0 */ c->r[2]=c->r[2]&c->r[4];
/* 001e3cf4: li a0,0x2 */ c->r[4]=sx(UINT32_C(0x00000002));
/* 001e3cf8: and t1,v0,v1 */ c->r[9]=c->r[2]&c->r[3];
/* 001e3cfc: li v1,0x1 */ c->r[3]=sx(UINT32_C(0x00000001));
/* 001e3d00: ori v0,t1,0x80 */ c->r[2]=c->r[9]|UINT64_C(0x80);
/* 001e3d04: sh a0,0xa8(t3) */ sh((uint32_t)c->r[11]+UINT32_C(0x000000a8),(uint16_t)c->r[4]);
/* 001e3d08: sh a1,0xbe(t3) */ sh((uint32_t)c->r[11]+UINT32_C(0x000000be),(uint16_t)c->r[5]);
/* 001e3d0c: sh a2,0xc0(t3) */ sh((uint32_t)c->r[11]+UINT32_C(0x000000c0),(uint16_t)c->r[6]);
/* 001e3d10: sh a3,0xc2(t3) */ sh((uint32_t)c->r[11]+UINT32_C(0x000000c2),(uint16_t)c->r[7]);
/* 001e3d14: sw v0,0xa4(t3) */ sw((uint32_t)c->r[11]+UINT32_C(0x000000a4),(uint32_t)c->r[2]);
/* 001e3d18: sh zero,0xae(t3) */ sh((uint32_t)c->r[11]+UINT32_C(0x000000ae),(uint16_t)c->r[0]);
/* 001e3d1c: beq t0,v1,0x001e3d60 */ {int taken=(c->r[8]==c->r[3]);/* delay 001e3d20 */ sw((uint32_t)c->r[11]+UINT32_C(0x00000094),(uint32_t)c->r[0]);if(taken){goto L_001e3d60;}}
/* 001e3d24: slti v0,t0,0x2 */ c->r[2]=less(c->r[8],sx(UINT32_C(0x00000002)));
/* 001e3d28: beql v0,zero,0x001e3d40 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 001e3d2c */ c->r[2]=sx(UINT32_C(0x00000002));goto L_001e3d40;}}
/* 001e3d30: beql t0,zero,0x001e3d58 */ {int taken=(c->r[8]==c->r[0]);if(taken){/* delay 001e3d34 */ c->r[2]=c->r[9]|UINT64_C(0xa0);goto L_001e3d58;}}
L_001e3d38:;
/* 001e3d38: jr ra */ /* delay 001e3d3c */ (void)0;return;
L_001e3d40:;
/* 001e3d40: beq t0,v0,0x001e3d38 */ {int taken=(c->r[8]==c->r[2]);/* delay 001e3d44 */ c->r[2]=sx(UINT32_C(0x00000003));if(taken){goto L_001e3d38;}}
/* 001e3d48: beql t0,v0,0x001e3d70 */ {int taken=(c->r[8]==c->r[2]);if(taken){/* delay 001e3d4c */ c->r[2]=c->r[9]|UINT64_C(0xc0);goto L_001e3d70;}}
/* 001e3d50: jr ra */ /* delay 001e3d54 */ (void)0;return;
L_001e3d58:;
/* 001e3d58: jr ra */ /* delay 001e3d5c */ sw((uint32_t)c->r[11]+UINT32_C(0x000000a4),(uint32_t)c->r[2]);return;
L_001e3d60:;
/* 001e3d60: ori v0,t1,0x81 */ c->r[2]=c->r[9]|UINT64_C(0x81);
/* 001e3d64: jr ra */ /* delay 001e3d68 */ sw((uint32_t)c->r[11]+UINT32_C(0x000000a4),(uint32_t)c->r[2]);return;
L_001e3d70:;
/* 001e3d70: sw v0,0xa4(t3) */ sw((uint32_t)c->r[11]+UINT32_C(0x000000a4),(uint32_t)c->r[2]);
/* 001e3d74: jr ra */ /* delay 001e3d78 */ (void)0;return;
}

static void body_0024ce78(BattleOutcomeValues *c){
/* 0024ce78: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0024ce7c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0024ce80: move s0,a1 */ c->r[16]=c->r[5];
/* 0024ce84: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0024ce88: move s1,a0 */ c->r[17]=c->r[4];
/* 0024ce8c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0024ce90: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 0024ce94: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0024ce9c);/* delay 0024ce98 */ c->r[18]=c->r[6];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024ce9c: lw v1,0x60(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000060)));
/* 0024cea0: andi v1,v1,0x1000 */ c->r[3]=c->r[3]&UINT64_C(0x1000);
/* 0024cea4: bne v1,zero,0x0024cf58 */ {int taken=(c->r[3]!=c->r[0]);/* delay 0024cea8 */ c->r[2]=c->r[16];if(taken){goto L_0024cf58;}}
/* 0024ceac: jal 0x00244200 */ c->r[31]=UINT64_C(0x0024ceb4);/* delay 0024ceb0 */ c->r[4]=c->r[18];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)datCheckDying((datUnitWork_PS2 *)at((uint32_t)c->r[4])));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024ceb4: beq v0,zero,0x0024cee0 */ {int taken=(c->r[2]==c->r[0]);/* delay 0024ceb8 */ (void)0;if(taken){goto L_0024cee0;}}
/* 0024cebc: bne s0,zero,0x0024cf58 */ {int taken=(c->r[16]!=c->r[0]);/* delay 0024cec0 */ c->r[2]=c->r[16];if(taken){goto L_0024cf58;}}
/* 0024cec4: lw v0,0x8c(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000008c)));
/* 0024cec8: move a1,zero */ c->r[5]=c->r[0];
/* 0024cecc: jal 0x001ddba8 */ c->r[31]=UINT64_C(0x0024ced4);/* delay 0024ced0 */ c->r[4]=sx(word((uint32_t)c->r[2]+UINT32_C(0x0000008c)));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2ModelMotionLength(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024ced4: li v1,0x16 */ c->r[3]=sx(UINT32_C(0x00000016));
/* 0024ced8: slti v0,v0,0x17 */ c->r[2]=less(c->r[2],sx(UINT32_C(0x00000017)));
/* 0024cedc: movz s0,v1,v0 */ if(c->r[2]==0){c->r[16]=c->r[3];}
L_0024cee0:;
/* 0024cee0: bne s0,zero,0x0024cf58 */ {int taken=(c->r[16]!=c->r[0]);/* delay 0024cee4 */ c->r[2]=c->r[16];if(taken){goto L_0024cf58;}}
/* 0024cee8: lhu v0,0xe(s2) */ c->r[2]=hword((uint32_t)c->r[18]+UINT32_C(0x0000000e));
/* 0024ceec: li v1,0x20 */ c->r[3]=sx(UINT32_C(0x00000020));
/* 0024cef0: andi a0,v0,0xfff */ c->r[4]=c->r[2]&UINT64_C(0xfff);
/* 0024cef4: beq a0,v1,0x0024cf50 */ {int taken=(c->r[4]==c->r[3]);/* delay 0024cef8 */ c->r[2]=less(c->r[4],sx(UINT32_C(0x00000021)));if(taken){goto L_0024cf50;}}
/* 0024cefc: beq v0,zero,0x0024cf20 */ {int taken=(c->r[2]==c->r[0]);/* delay 0024cf00 */ c->r[2]=sx(UINT32_C(0x00000080));if(taken){goto L_0024cf20;}}
/* 0024cf04: li v0,0x4 */ c->r[2]=sx(UINT32_C(0x00000004));
/* 0024cf08: beq a0,v0,0x0024cf50 */ {int taken=(c->r[4]==c->r[2]);/* delay 0024cf0c */ c->r[2]=sx(UINT32_C(0x00000008));if(taken){goto L_0024cf50;}}
/* 0024cf10: beq a0,v0,0x0024cf50 */ {int taken=(c->r[4]==c->r[2]);/* delay 0024cf14 */ c->r[2]=c->r[16];if(taken){goto L_0024cf50;}}
/* 0024cf18: b 0x0024cf5c */ /* delay 0024cf1c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0024cf5c;
L_0024cf20:;
/* 0024cf20: beq a0,v0,0x0024cf50 */ {int taken=(c->r[4]==c->r[2]);/* delay 0024cf24 */ c->r[2]=less(c->r[4],sx(UINT32_C(0x00000081)));if(taken){goto L_0024cf50;}}
/* 0024cf28: beq v0,zero,0x0024cf48 */ {int taken=(c->r[2]==c->r[0]);/* delay 0024cf2c */ c->r[2]=sx(UINT32_C(0x00000100));if(taken){goto L_0024cf48;}}
/* 0024cf30: li v0,0x40 */ c->r[2]=sx(UINT32_C(0x00000040));
/* 0024cf34: beq a0,v0,0x0024cf50 */ {int taken=(c->r[4]==c->r[2]);/* delay 0024cf38 */ c->r[2]=c->r[16];if(taken){goto L_0024cf50;}}
/* 0024cf3c: b 0x0024cf5c */ /* delay 0024cf40 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0024cf5c;
L_0024cf48:;
/* 0024cf48: bne a0,v0,0x0024cf58 */ {int taken=(c->r[4]!=c->r[2]);/* delay 0024cf4c */ c->r[2]=c->r[16];if(taken){goto L_0024cf58;}}
L_0024cf50:;
/* 0024cf50: li s0,0x2 */ c->r[16]=sx(UINT32_C(0x00000002));
/* 0024cf54: move v0,s0 */ c->r[2]=c->r[16];
L_0024cf58:;
/* 0024cf58: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0024cf5c:;
/* 0024cf5c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0024cf60: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0024cf64: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0024cf68: jr ra */ /* delay 0024cf6c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_0024cff8(BattleOutcomeValues *c){
/* 0024cff8: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 0024cffc: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0024d000: move s1,a0 */ c->r[17]=c->r[4];
/* 0024d004: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0024d008: move s0,a1 */ c->r[16]=c->r[5];
/* 0024d00c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0024d010: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0024d014: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 0024d018: move s4,zero */ c->r[20]=c->r[0];
/* 0024d01c: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 0024d020: move s5,zero */ c->r[21]=c->r[0];
/* 0024d024: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 0024d028: move s6,a2 */ c->r[22]=c->r[6];
/* 0024d02c: swc1 f20,0x48(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000048),c->f[20]);
/* 0024d030: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 0024d034: sd ra,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);
/* 0024d038: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0024d040);/* delay 0024d03c */ c->f[20]=c->f[12];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d040: lh a1,0x90(s1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000090)));
/* 0024d044: move a0,v0 */ c->r[4]=c->r[2];
/* 0024d048: lw v1,0x10(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000010)));
/* 0024d04c: sll a1,a1,0x7 */ c->r[5]=sx((uint32_t)c->r[5]<<7u);
/* 0024d050: lw s3,0x8c(s1) */ c->r[19]=sx(word((uint32_t)c->r[17]+UINT32_C(0x0000008c)));
/* 0024d054: jal 0x002469c0 */ c->r[31]=UINT64_C(0x0024d05c);/* delay 0024d058 */ c->r[5]=sx((uint32_t)c->r[3]+(uint32_t)c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitWorkPointer(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d05c: move s2,v0 */ c->r[18]=c->r[2];
/* 0024d060: lw v0,0x80(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000080)));
/* 0024d064: andi v0,v0,0x80 */ c->r[2]=c->r[2]&UINT64_C(0x80);
/* 0024d068: bnel v0,zero,0x0024d208 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0024d06c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0024d208;}}
/* 0024d070: jal 0x00259a60 */ c->r[31]=UINT64_C(0x0024d078);/* delay 0024d074 */ c->r[4]=c->r[18];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatModelScaleDescriptor_00259A60(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d078: move a0,s1 */ c->r[4]=c->r[17];
/* 0024d07c: move a1,s0 */ c->r[5]=c->r[16];
/* 0024d080: move a2,s2 */ c->r[6]=c->r[18];
/* 0024d084: jal 0x0024ce78 */ c->r[31]=UINT64_C(0x0024d08c);/* delay 0024d088 */ c->r[23]=c->r[2];body_0024ce78(c);
/* 0024d08c: move s0,v0 */ c->r[16]=c->r[2];
/* 0024d090: mov.S f12,f20 */ c->f[12]=c->f[20];
/* 0024d094: move a0,s1 */ c->r[4]=c->r[17];
/* 0024d098: jal 0x0024d428 */ c->r[31]=UINT64_C(0x0024d0a0);/* delay 0024d09c */ c->r[5]=c->r[16];body_0024d428(c);
/* 0024d0a0: move a0,s1 */ c->r[4]=c->r[17];
/* 0024d0a4: move a1,s0 */ c->r[5]=c->r[16];
/* 0024d0a8: jal 0x0024d490 */ c->r[31]=UINT64_C(0x0024d0b0);/* delay 0024d0ac */ c->f[20]=c->f[0];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleFormation_0024D490(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d0b0: move a1,v0 */ c->r[5]=c->r[2];
/* 0024d0b4: sltiu v0,s0,0x1a */ c->r[2]=(c->r[16]<sx(UINT32_C(0x0000001a)));
/* 0024d0b8: beq v0,zero,0x0024d114 */ {int taken=(c->r[2]==c->r[0]);/* delay 0024d0bc */ c->r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_0024d114;}}
/* 0024d0c0: sll v0,s0,0x2 */ c->r[2]=sx((uint32_t)c->r[16]<<2u);
/* 0024d0c4: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 0024d0c8: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0024d0cc: lw v1,0x36b0(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x000036b0)));
/* 0024d0d0: jr v1 */ {uint64_t target=c->r[3];/* delay 0024d0d4 */ (void)0;switch(target){case UINT64_C(0x0024d0d8):goto L_0024d0d8;case UINT64_C(0x0024d0e8):goto L_0024d0e8;case UINT64_C(0x0024d0f8):goto L_0024d0f8;case UINT64_C(0x0024d108):goto L_0024d108;default:abort();}}
L_0024d0d8:;
/* 0024d0d8: lh s5,0xaa(s1) */ c->r[21]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x000000aa)));
/* 0024d0dc: b 0x0024d110 */ /* delay 0024d0e0 */ c->r[20]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x000000a8)));goto L_0024d110;
L_0024d0e8:;
/* 0024d0e8: move s5,zero */ c->r[21]=c->r[0];
/* 0024d0ec: b 0x0024d110 */ /* delay 0024d0f0 */ c->r[20]=sx(UINT32_C(0x00000001));goto L_0024d110;
L_0024d0f8:;
/* 0024d0f8: move s5,zero */ c->r[21]=c->r[0];
/* 0024d0fc: b 0x0024d110 */ /* delay 0024d100 */ c->r[20]=c->r[0];goto L_0024d110;
L_0024d108:;
/* 0024d108: move s5,zero */ c->r[21]=c->r[0];
/* 0024d10c: li s4,0xf */ c->r[20]=sx(UINT32_C(0x0000000f));
L_0024d110:;
/* 0024d110: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
L_0024d114:;
/* 0024d114: beq s0,v0,0x0024d148 */ {int taken=(c->r[16]==c->r[2]);/* delay 0024d118 */ c->r[2]=less(c->r[16],sx(UINT32_C(0x00000003)));if(taken){goto L_0024d148;}}
/* 0024d11c: beql v0,zero,0x0024d138 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0024d120 */ c->r[2]=sx(UINT32_C(0x0000000d));goto L_0024d138;}}
/* 0024d124: beq s0,zero,0x0024d148 */ {int taken=(c->r[16]==c->r[0]);/* delay 0024d128 */ c->r[6]=c->r[21];if(taken){goto L_0024d148;}}
/* 0024d12c: b 0x0024d174 */ /* delay 0024d130 */ c->r[7]=c->r[20];goto L_0024d174;
L_0024d138:;
/* 0024d138: beq s0,v0,0x0024d148 */ {int taken=(c->r[16]==c->r[2]);/* delay 0024d13c */ c->r[2]=sx(UINT32_C(0x00000016));if(taken){goto L_0024d148;}}
/* 0024d140: bne s0,v0,0x0024d170 */ {int taken=(c->r[16]!=c->r[2]);/* delay 0024d144 */ c->r[6]=c->r[21];if(taken){goto L_0024d170;}}
L_0024d148:;
/* 0024d148: lw v1,0x8c(s3) */ c->r[3]=sx(word((uint32_t)c->r[19]+UINT32_C(0x0000008c)));
/* 0024d14c: lh v0,0x12(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000012)));
/* 0024d150: beq v0,a1,0x0024d184 */ {int taken=(c->r[2]==c->r[5]);/* delay 0024d154 */ c->r[6]=c->r[21];if(taken){goto L_0024d184;}}
/* 0024d158: move a3,s4 */ c->r[7]=c->r[20];
/* 0024d15c: move a0,s3 */ c->r[4]=c->r[19];
/* 0024d160: jal 0x001e3cc0 */ c->r[31]=UINT64_C(0x0024d168);/* delay 0024d164 */ c->r[8]=c->r[22];body_001e3cc0(c);
/* 0024d168: b 0x0024d184 */ /* delay 0024d16c */ c->r[3]=sx(word((uint32_t)c->r[19]+UINT32_C(0x0000008c)));goto L_0024d184;
L_0024d170:;
/* 0024d170: move a3,s4 */ c->r[7]=c->r[20];
L_0024d174:;
/* 0024d174: move a0,s3 */ c->r[4]=c->r[19];
/* 0024d178: jal 0x001e3cc0 */ c->r[31]=UINT64_C(0x0024d180);/* delay 0024d17c */ c->r[8]=c->r[22];body_001e3cc0(c);
/* 0024d180: lw v1,0x8c(s3) */ c->r[3]=sx(word((uint32_t)c->r[19]+UINT32_C(0x0000008c)));
L_0024d184:;
/* 0024d184: sll v0,s0,0x3 */ c->r[2]=sx((uint32_t)c->r[16]<<3u);
/* 0024d188: lw v1,0x1c(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x0000001c)));
/* 0024d18c: subu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[16]);
/* 0024d190: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 0024d194: swc1 f20,0x20(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000020),c->f[20]);
/* 0024d198: addiu v0,v0,0x30 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000030));
/* 0024d19c: swc1 f20,0xa0(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x000000a0),c->f[20]);
/* 0024d1a0: addu v0,s7,v0 */ c->r[2]=sx((uint32_t)c->r[23]+(uint32_t)c->r[2]);
/* 0024d1a4: lhu a2,0x16(v0) */ c->r[6]=hword((uint32_t)c->r[2]+UINT32_C(0x00000016));
/* 0024d1a8: sh a2,0xa8(s1) */ sh((uint32_t)c->r[17]+UINT32_C(0x000000a8),(uint16_t)c->r[6]);
/* 0024d1ac: lhu a1,0x14(v0) */ c->r[5]=hword((uint32_t)c->r[2]+UINT32_C(0x00000014));
/* 0024d1b0: beq s6,zero,0x0024d1c4 */ {int taken=(c->r[22]==c->r[0]);/* delay 0024d1b4 */ sh((uint32_t)c->r[17]+UINT32_C(0x000000aa),(uint16_t)c->r[5]);if(taken){goto L_0024d1c4;}}
/* 0024d1b8: li v0,0x3 */ c->r[2]=sx(UINT32_C(0x00000003));
/* 0024d1bc: bne s6,v0,0x0024d208 */ {int taken=(c->r[22]!=c->r[2]);/* delay 0024d1c0 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_0024d208;}}
L_0024d1c4:;
/* 0024d1c4: sll a1,a1,0x10 */ c->r[5]=sx((uint32_t)c->r[5]<<16u);
/* 0024d1c8: sll a2,a2,0x10 */ c->r[6]=sx((uint32_t)c->r[6]<<16u);
/* 0024d1cc: move a0,s3 */ c->r[4]=c->r[19];
/* 0024d1d0: sra a1,a1,0x10 */ c->r[5]=sar((uint32_t)c->r[5],16u);
/* 0024d1d4: jal 0x001e3b78 */ c->r[31]=UINT64_C(0x0024d1dc);/* delay 0024d1d8 */ c->r[6]=sar((uint32_t)c->r[6],16u);body_001e3b78(c);
/* 0024d1dc: lh v1,0xac(s1) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x000000ac)));
/* 0024d1e0: sll v0,v1,0x3 */ c->r[2]=sx((uint32_t)c->r[3]<<3u);
/* 0024d1e4: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 0024d1e8: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 0024d1ec: addiu v0,v0,0x30 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000030));
/* 0024d1f0: addu v0,s7,v0 */ c->r[2]=sx((uint32_t)c->r[23]+(uint32_t)c->r[2]);
/* 0024d1f4: lhu v1,0x16(v0) */ c->r[3]=hword((uint32_t)c->r[2]+UINT32_C(0x00000016));
/* 0024d1f8: sh v1,0xa8(s1) */ sh((uint32_t)c->r[17]+UINT32_C(0x000000a8),(uint16_t)c->r[3]);
/* 0024d1fc: lhu a0,0x14(v0) */ c->r[4]=hword((uint32_t)c->r[2]+UINT32_C(0x00000014));
/* 0024d200: sh a0,0xaa(s1) */ sh((uint32_t)c->r[17]+UINT32_C(0x000000aa),(uint16_t)c->r[4]);
/* 0024d204: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0024d208:;
/* 0024d208: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0024d20c: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0024d210: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0024d214: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0024d218: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 0024d21c: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0024d220: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 0024d224: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 0024d228: lwc1 f20,0x48(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 0024d22c: jr ra */ /* delay 0024d230 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}

static void body_0024d238(BattleOutcomeValues *c){
/* 0024d238: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 0024d23c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0024d240: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0024d244: move s1,a1 */ c->r[17]=c->r[5];
/* 0024d248: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0024d24c: move s2,a0 */ c->r[18]=c->r[4];
/* 0024d250: swc1 f21,0x28(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000028),c->f[21]);
/* 0024d254: mov.S f21,f12 */ c->f[21]=c->f[12];
/* 0024d258: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 0024d25c: swc1 f20,0x20(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000020),c->f[20]);
/* 0024d260: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x0024d268);/* delay 0024d264 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[18]+UINT32_C(0x00000092)));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d268: move a0,s2 */ c->r[4]=c->r[18];
/* 0024d26c: move s0,v0 */ c->r[16]=c->r[2];
/* 0024d270: move a1,s1 */ c->r[5]=c->r[17];
/* 0024d274: jal 0x0024ce78 */ c->r[31]=UINT64_C(0x0024d27c);/* delay 0024d278 */ c->r[6]=c->r[16];body_0024ce78(c);
/* 0024d27c: move a0,s0 */ c->r[4]=c->r[16];
/* 0024d280: jal 0x00259a30 */ c->r[31]=UINT64_C(0x0024d288);/* delay 0024d284 */ c->r[17]=c->r[2];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitID(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d288: bne v0,zero,0x0024d2a8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0024d28c */ c->r[4]=c->r[16];if(taken){goto L_0024d2a8;}}
/* 0024d290: lui s0,0x35 */ c->r[16]=sx(UINT32_C(0x00350000));
/* 0024d294: addu s0,s0,s1 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[17]);
/* 0024d298: lbu s0,-0x6c60(s0) */ c->r[16]=*at((uint32_t)c->r[16]+UINT32_C(0xffff93a0));
/* 0024d29c: b 0x0024d2b4 */ /* delay 0024d2a0 */ (void)0;goto L_0024d2b4;
L_0024d2a8:;
/* 0024d2a8: lui s0,0x35 */ c->r[16]=sx(UINT32_C(0x00350000));
/* 0024d2ac: addu s0,s0,s1 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[17]);
/* 0024d2b0: lbu s0,-0xe40(s0) */ c->r[16]=*at((uint32_t)c->r[16]+UINT32_C(0xfffff1c0));
L_0024d2b4:;
/* 0024d2b4: jal 0x00259a60 */ c->r[31]=UINT64_C(0x0024d2bc);/* delay 0024d2b8 */ (void)0;nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatModelScaleDescriptor_00259A60(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d2bc: sll v1,s1,0x3 */ c->r[3]=sx((uint32_t)c->r[17]<<3u);
/* 0024d2c0: subu v1,v1,s1 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[17]);
/* 0024d2c4: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 0024d2c8: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0024d2cc: lwc1 f20,0x34(v1) */ c->f[20]=word((uint32_t)c->r[3]+UINT32_C(0x00000034));
/* 0024d2d0: mul.S f20,f20,f21 */ c->f[20]=EE_FPU_MUL_S(c->f[20],c->f[21]);
/* 0024d2d4: lw a0,0x8c(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x0000008c)));
/* 0024d2d8: jal 0x001e3b68 */ c->r[31]=UINT64_C(0x0024d2e0);/* delay 0024d2dc */ c->r[5]=c->r[16];body_001e3b68(c);
/* 0024d2e0: lw a0,0x8c(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x0000008c)));
/* 0024d2e4: jal 0x001e3b70 */ c->r[31]=UINT64_C(0x0024d2ec);/* delay 0024d2e8 */ c->f[12]=c->f[20];body_001e3b70(c);
/* 0024d2ec: sh s1,0xac(s2) */ sh((uint32_t)c->r[18]+UINT32_C(0x000000ac),(uint16_t)c->r[17]);
/* 0024d2f0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0024d2f4: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0024d2f8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0024d2fc: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0024d300: lwc1 f21,0x28(sp) */ c->f[21]=word((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 0024d304: lwc1 f20,0x20(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0024d308: jr ra */ /* delay 0024d30c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_0024d428(BattleOutcomeValues *c){
/* 0024d428: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0024d42c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0024d430: move s0,a1 */ c->r[16]=c->r[5];
/* 0024d434: swc1 f20,0x10(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000010),c->f[20]);
/* 0024d438: mov.S f20,f12 */ c->f[20]=c->f[12];
/* 0024d43c: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 0024d440: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x0024d448);/* delay 0024d444 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000092)));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d448: jal 0x00259a60 */ c->r[31]=UINT64_C(0x0024d450);/* delay 0024d44c */ c->r[4]=c->r[2];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatModelScaleDescriptor_00259A60(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0024d450: sll v1,s0,0x3 */ c->r[3]=sx((uint32_t)c->r[16]<<3u);
/* 0024d454: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 0024d458: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0024d45c: subu v1,v1,s0 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[16]);
/* 0024d460: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 0024d464: c.eq.S f20,f0 */ c->condition=EE_FPU_COMPARE_S(c->f[20],c->f[0],0);
/* 0024d468: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0024d46c: bc1t 0x0024d478 */ {int taken=(c->condition!=0);/* delay 0024d470 */ c->f[0]=word((uint32_t)c->r[3]+UINT32_C(0x00000034));if(taken){goto L_0024d478;}}
/* 0024d474: mul.S f0,f0,f20 */ c->f[0]=EE_FPU_MUL_S(c->f[0],c->f[20]);
L_0024d478:;
/* 0024d478: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0024d47c: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0024d480: lwc1 f20,0x10(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0024d484: jr ra */ /* delay 0024d488 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00252cd8(BattleOutcomeValues *c){
/* 00252cd8: addiu sp,sp,-0x70 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffff90));
/* 00252cdc: sd s2,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[18]);
/* 00252ce0: move s2,a0 */ c->r[18]=c->r[4];
/* 00252ce4: sd s0,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[16]);
/* 00252ce8: sd s1,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[17]);
/* 00252cec: sd s3,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[19]);
/* 00252cf0: sd s4,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[20]);
/* 00252cf4: sd s5,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[21]);
/* 00252cf8: sd s6,0x50(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000050),c->r[22]);
/* 00252cfc: sd s7,0x58(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000058),c->r[23]);
/* 00252d00: sd s8,0x60(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000060),c->r[30]);
/* 00252d04: sd ra,0x68(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000068),c->r[31]);
/* 00252d08: lw a0,0x24(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000024)));
/* 00252d0c: lhu v1,0x0(a0) */ c->r[3]=hword((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 00252d10: andi v1,v1,0x6 */ c->r[3]=c->r[3]&UINT64_C(0x6);
/* 00252d14: bne v1,zero,0x00252e74 */ {int taken=(c->r[3]!=c->r[0]);/* delay 00252d18 */ c->r[2]=c->r[0];if(taken){goto L_00252e74;}}
/* 00252d1c: lw v1,0x30(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000030)));
/* 00252d20: slti v1,v1,0x4 */ c->r[3]=less(c->r[3],sx(UINT32_C(0x00000004)));
/* 00252d24: beq v1,zero,0x00252e78 */ {int taken=(c->r[3]==c->r[0]);/* delay 00252d28 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));if(taken){goto L_00252e78;}}
/* 00252d2c: move s4,zero */ c->r[20]=c->r[0];
/* 00252d30: li s3,0x4 */ c->r[19]=sx(UINT32_C(0x00000004));
/* 00252d34: li s8,0x100 */ c->r[30]=sx(UINT32_C(0x00000100));
/* 00252d38: li s5,0x3c0 */ c->r[21]=sx(UINT32_C(0x000003c0));
/* 00252d3c: li s7,0x10 */ c->r[23]=sx(UINT32_C(0x00000010));
/* 00252d40: li s6,0x400 */ c->r[22]=sx(UINT32_C(0x00000400));
/* 00252d44: nop  */ (void)0;
L_00252d48:;
/* 00252d48: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00252d4c: lw v0,0x0(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 00252d50: addu s1,v0,s5 */ c->r[17]=sx((uint32_t)c->r[2]+(uint32_t)c->r[21]);
/* 00252d54: lw v1,0x78(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 00252d58: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 00252d5c: beq v0,zero,0x00252e28 */ {int taken=(c->r[2]==c->r[0]);/* delay 00252d60 */ c->r[2]=c->r[3]&UINT64_C(0x40);if(taken){goto L_00252e28;}}
/* 00252d64: beql v0,zero,0x00252e2c */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00252d68 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252e2c;}}
/* 00252d6c: lh v0,0x90(s1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000090)));
/* 00252d70: lw v1,0x10(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000010)));
/* 00252d74: sll v0,v0,0x7 */ c->r[2]=sx((uint32_t)c->r[2]<<7u);
/* 00252d78: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00252d7c: lhu v0,0x0(v0) */ c->r[2]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 00252d80: andi v1,v0,0x1 */ c->r[3]=c->r[2]&UINT64_C(0x1);
/* 00252d84: andi v1,v1,0xffff */ c->r[3]=c->r[3]&UINT64_C(0xffff);
/* 00252d88: beq v1,zero,0x00252e28 */ {int taken=(c->r[3]==c->r[0]);/* delay 00252d8c */ c->r[2]=c->r[2]&UINT64_C(0x20);if(taken){goto L_00252e28;}}
/* 00252d90: bnel v0,zero,0x00252e2c */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252d94 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252e2c;}}
/* 00252d98: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x00252da0);/* delay 00252d9c */ c->r[4]=c->r[19];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00252da0: move a0,s2 */ c->r[4]=c->r[18];
/* 00252da4: move a1,s3 */ c->r[5]=c->r[19];
/* 00252da8: jal 0x002515e8 */ c->r[31]=UINT64_C(0x00252db0);/* delay 00252dac */ c->r[16]=c->r[2];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbActionCheckTimeListDead(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00252db0: bnel v0,zero,0x00252e2c */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00252db4 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252e2c;}}
/* 00252db8: lhu v0,0xe(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x0000000e));
/* 00252dbc: andi v1,v0,0xfff */ c->r[3]=c->r[2]&UINT64_C(0xfff);
/* 00252dc0: li v0,0x4 */ c->r[2]=sx(UINT32_C(0x00000004));
/* 00252dc4: beq v1,v0,0x00252e28 */ {int taken=(c->r[3]==c->r[2]);/* delay 00252dc8 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000005)));if(taken){goto L_00252e28;}}
/* 00252dcc: beq v0,zero,0x00252df0 */ {int taken=(c->r[2]==c->r[0]);/* delay 00252dd0 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000003)));if(taken){goto L_00252df0;}}
/* 00252dd4: beql v0,zero,0x00252e1c */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00252dd8 */ c->r[3]=*at((uint32_t)c->r[17]+UINT32_C(0x00000090));goto L_00252e1c;}}
/* 00252ddc: beql v1,zero,0x00252e1c */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00252de0 */ c->r[3]=*at((uint32_t)c->r[17]+UINT32_C(0x00000090));goto L_00252e1c;}}
/* 00252de4: b 0x00252e2c */ /* delay 00252de8 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252e2c;
L_00252df0:;
/* 00252df0: beq v1,s8,0x00252e28 */ {int taken=(c->r[3]==c->r[30]);/* delay 00252df4 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000101)));if(taken){goto L_00252e28;}}
/* 00252df8: beq v0,zero,0x00252e10 */ {int taken=(c->r[2]==c->r[0]);/* delay 00252dfc */ (void)0;if(taken){goto L_00252e10;}}
/* 00252e00: beql v1,s7,0x00252e2c */ {int taken=(c->r[3]==c->r[23]);if(taken){/* delay 00252e04 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252e2c;}}
/* 00252e08: b 0x00252e1c */ /* delay 00252e0c */ c->r[3]=*at((uint32_t)c->r[17]+UINT32_C(0x00000090));goto L_00252e1c;
L_00252e10:;
/* 00252e10: beql v1,s6,0x00252e2c */ {int taken=(c->r[3]==c->r[22]);if(taken){/* delay 00252e14 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00252e2c;}}
/* 00252e18: lbu v1,0x90(s1) */ c->r[3]=*at((uint32_t)c->r[17]+UINT32_C(0x00000090));
L_00252e1c:;
/* 00252e1c: addu v0,sp,s4 */ c->r[2]=sx((uint32_t)c->r[29]+(uint32_t)c->r[20]);
/* 00252e20: addiu s4,s4,0x1 */ c->r[20]=sx((uint32_t)c->r[20]+UINT32_C(0x00000001));
/* 00252e24: sb v1,0x0(v0) */ *at((uint32_t)c->r[2]+UINT32_C(0x00000000))=(uint8_t)c->r[3];
L_00252e28:;
/* 00252e28: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_00252e2c:;
/* 00252e2c: slti v0,s3,0xe */ c->r[2]=less(c->r[19],sx(UINT32_C(0x0000000e)));
/* 00252e30: bne v0,zero,0x00252d48 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00252e34 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0x000000f0));if(taken){goto L_00252d48;}}
/* 00252e38: beq s4,zero,0x00252e74 */ {int taken=(c->r[20]==c->r[0]);/* delay 00252e3c */ c->r[2]=c->r[0];if(taken){goto L_00252e74;}}
/* 00252e40: move a1,s4 */ c->r[5]=c->r[20];
/* 00252e44: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x00252e4c);/* delay 00252e48 */ c->r[4]=c->r[0];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]==0?NULL:(uint32_t *)at((uint32_t)c->r[4]),(uint32_t)c->r[5]));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00252e4c: li a0,0x3 */ c->r[4]=sx(UINT32_C(0x00000003));
/* 00252e50: addu v0,sp,v0 */ c->r[2]=sx((uint32_t)c->r[29]+(uint32_t)c->r[2]);
/* 00252e54: lw a2,0x30(s2) */ c->r[6]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000030)));
/* 00252e58: lb a1,0x0(v0) */ c->r[5]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 00252e5c: jal 0x00247ed8 */ c->r[31]=UINT64_C(0x00252e64);/* delay 00252e60 */ c->r[7]=c->r[0];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbPushAction(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00252e64: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 00252e68: jal 0x002d4748 */ c->r[31]=UINT64_C(0x00252e70);/* delay 00252e6c */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00003908));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00252e70: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_00252e74:;
/* 00252e74: ld s0,0x20(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
L_00252e78:;
/* 00252e78: ld s1,0x28(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 00252e7c: ld s2,0x30(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 00252e80: ld s3,0x38(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 00252e84: ld s4,0x40(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 00252e88: ld s5,0x48(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 00252e8c: ld s6,0x50(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000050));
/* 00252e90: ld s7,0x58(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000058));
/* 00252e94: ld s8,0x60(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000060));
/* 00252e98: ld ra,0x68(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000068));
/* 00252e9c: jr ra */ /* delay 00252ea0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000070));return;
}

static void body_00256c00(BattleOutcomeValues *c){
/* 00256c00: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 00256c04: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00256c08: move s2,a0 */ c->r[18]=c->r[4];
/* 00256c0c: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 00256c10: move s4,zero */ c->r[20]=c->r[0];
/* 00256c14: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 00256c18: move s5,zero */ c->r[21]=c->r[0];
/* 00256c1c: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 00256c20: move s6,zero */ c->r[22]=c->r[0];
/* 00256c24: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 00256c28: li s7,0x1 */ c->r[23]=sx(UINT32_C(0x00000001));
/* 00256c2c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00256c30: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00256c34: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 00256c38: sd ra,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);
/* 00256c3c: swc1 f20,0x48(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000048),c->f[20]);
/* 00256c40: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256c44: lw v1,0x94(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000094)));
/* 00256c48: addiu v1,v1,-0x1 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffffffff));
/* 00256c4c: sltiu v0,v1,0x9 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000009)));
/* 00256c50: beq v0,zero,0x00256ef4 */ {int taken=(c->r[2]==c->r[0]);/* delay 00256c54 */ c->r[5]=c->r[4];if(taken){goto L_00256ef4;}}
/* 00256c58: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 00256c5c: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 00256c60: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00256c64: lw v1,0x3fd0(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00003fd0)));
/* 00256c68: jr v1 */ {uint64_t target=c->r[3];/* delay 00256c6c */ (void)0;switch(target){case UINT64_C(0x00256c70):goto L_00256c70;case UINT64_C(0x00256c78):goto L_00256c78;case UINT64_C(0x00256c90):goto L_00256c90;case UINT64_C(0x00256cb0):goto L_00256cb0;case UINT64_C(0x00256d18):goto L_00256d18;case UINT64_C(0x00256d38):goto L_00256d38;case UINT64_C(0x00256e18):goto L_00256e18;case UINT64_C(0x00256ee8):goto L_00256ee8;default:abort();}}
L_00256c70:;
/* 00256c70: b 0x00256ef4 */ /* delay 00256c74 */ c->r[22]=sx(UINT32_C(0x00000001));goto L_00256ef4;
L_00256c78:;
/* 00256c78: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 00256c7c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 00256c80: li s4,0x1 */ c->r[20]=sx(UINT32_C(0x00000001));
/* 00256c84: b 0x00256d28 */ /* delay 00256c88 */ c->r[21]=sx(UINT32_C(0x0000000c));goto L_00256d28;
L_00256c90:;
/* 00256c90: lh a0,0x92(a1) */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000092)));
/* 00256c94: li s4,0x1 */ c->r[20]=sx(UINT32_C(0x00000001));
/* 00256c98: jal 0x00246a40 */ c->r[31]=UINT64_C(0x00256ca0);/* delay 00256c9c */ c->r[21]=sx(UINT32_C(0x0000000c));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetPartyFromFormindex(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256ca0: move a0,zero */ c->r[4]=c->r[0];
/* 00256ca4: b 0x00256ce0 */ /* delay 00256ca8 */ c->r[6]=c->r[2];goto L_00256ce0;
L_00256cb0:;
/* 00256cb0: lh a0,0x92(a1) */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000092)));
/* 00256cb4: li s4,0x1 */ c->r[20]=sx(UINT32_C(0x00000001));
/* 00256cb8: jal 0x00246a40 */ c->r[31]=UINT64_C(0x00256cc0);/* delay 00256cbc */ c->r[21]=sx(UINT32_C(0x0000000b));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetPartyFromFormindex(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256cc0: move s0,v0 */ c->r[16]=c->r[2];
/* 00256cc4: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256cc8: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x00256cd0);/* delay 00256ccc */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256cd0: jal 0x00259180 */ c->r[31]=UINT64_C(0x00256cd8);/* delay 00256cd4 */ c->r[4]=c->r[2];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleRoster_00259180(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256cd8: move a0,zero */ c->r[4]=c->r[0];
/* 00256cdc: move a2,s0 */ c->r[6]=c->r[16];
L_00256ce0:;
/* 00256ce0: jal 0x00263778 */ c->r[31]=UINT64_C(0x00256ce8);/* delay 00256ce4 */ c->r[5]=c->r[18];body_00263778(c);
/* 00256ce8: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256cec: move a0,s2 */ c->r[4]=c->r[18];
/* 00256cf0: move a2,zero */ c->r[6]=c->r[0];
/* 00256cf4: lh a1,0x92(v1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));
/* 00256cf8: li a3,0x28 */ c->r[7]=sx(UINT32_C(0x00000028));
/* 00256cfc: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00256d04);/* delay 00256d00 */ c->r[8]=sx(UINT32_C(0x00000028));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256d04: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 00256d08: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 00256d0c: b 0x00256ef4 */ /* delay 00256d10 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000014),c->f[0]);goto L_00256ef4;
L_00256d18:;
/* 00256d18: lui at,0xc120 */ c->r[1]=sx(UINT32_C(0xc1200000));
/* 00256d1c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 00256d20: li s4,0x1 */ c->r[20]=sx(UINT32_C(0x00000001));
/* 00256d24: li s5,0xd */ c->r[21]=sx(UINT32_C(0x0000000d));
L_00256d28:;
/* 00256d28: li s6,0x1 */ c->r[22]=sx(UINT32_C(0x00000001));
/* 00256d2c: b 0x00256ef4 */ /* delay 00256d30 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000014),c->f[0]);goto L_00256ef4;
L_00256d38:;
/* 00256d38: lh a0,0x92(a1) */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000092)));
/* 00256d3c: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x00256d44);/* delay 00256d40 */ c->r[19]=sx(UINT32_C(0x00000004));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256d44: lhu s4,0x4(v0) */ c->r[20]=hword((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 00256d48: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256d4c: nop  */ (void)0;
L_00256d50:;
/* 00256d50: sll s1,s3,0x7 */ c->r[17]=sx((uint32_t)c->r[19]<<7u);
/* 00256d54: lw v0,0x10(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000010)));
/* 00256d58: addu a1,s1,v0 */ c->r[5]=sx((uint32_t)c->r[17]+(uint32_t)c->r[2]);
/* 00256d5c: lhu v1,0x0(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000000));
/* 00256d60: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 00256d64: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 00256d68: beq v0,zero,0x00256df0 */ {int taken=(c->r[2]==c->r[0]);/* delay 00256d6c */ c->r[2]=c->r[3]&UINT64_C(0x2);if(taken){goto L_00256df0;}}
/* 00256d70: beq v0,zero,0x00256df0 */ {int taken=(c->r[2]==c->r[0]);/* delay 00256d74 */ c->r[2]=c->r[3]&UINT64_C(0x20);if(taken){goto L_00256df0;}}
/* 00256d78: bnel v0,zero,0x00256df4 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00256d7c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00256df4;}}
/* 00256d80: jal 0x002469c0 */ c->r[31]=UINT64_C(0x00256d88);/* delay 00256d84 */ (void)0;nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitWorkPointer(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256d88: lhu v1,0x4(v0) */ c->r[3]=hword((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 00256d8c: bnel v1,s4,0x00256df4 */ {int taken=(c->r[3]!=c->r[20]);if(taken){/* delay 00256d90 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00256df4;}}
/* 00256d94: move a0,zero */ c->r[4]=c->r[0];
/* 00256d98: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x00256da0);/* delay 00256d9c */ c->r[5]=sx(UINT32_C(0x00000014));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]==0?NULL:(uint32_t *)at((uint32_t)c->r[4]),(uint32_t)c->r[5]));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256da0: move a1,s2 */ c->r[5]=c->r[18];
/* 00256da4: move s0,v0 */ c->r[16]=c->r[2];
/* 00256da8: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256dac: move a0,s0 */ c->r[4]=c->r[16];
/* 00256db0: lw a2,0x10(v0) */ c->r[6]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000010)));
/* 00256db4: jal 0x00263778 */ c->r[31]=UINT64_C(0x00256dbc);/* delay 00256db8 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[17]);body_00263778(c);
/* 00256dbc: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256dc0: lw v1,0x10(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000010)));
/* 00256dc4: addu a0,s1,v1 */ c->r[4]=sx((uint32_t)c->r[17]+(uint32_t)c->r[3]);
/* 00256dc8: lhu v0,0x0(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 00256dcc: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 00256dd0: bnel v0,zero,0x00256df4 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00256dd4 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00256df4;}}
/* 00256dd8: lh a1,0x2(a0) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000002)));
/* 00256ddc: move a0,s2 */ c->r[4]=c->r[18];
/* 00256de0: move a2,s0 */ c->r[6]=c->r[16];
/* 00256de4: li a3,0x28 */ c->r[7]=sx(UINT32_C(0x00000028));
/* 00256de8: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00256df0);/* delay 00256dec */ c->r[8]=sx(UINT32_C(0x00000028));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
L_00256df0:;
/* 00256df0: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_00256df4:;
/* 00256df4: slti v0,s3,0xe */ c->r[2]=less(c->r[19],sx(UINT32_C(0x0000000e)));
/* 00256df8: bnel v0,zero,0x00256d50 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00256dfc */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));goto L_00256d50;}}
/* 00256e00: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 00256e04: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 00256e08: li s4,0x1 */ c->r[20]=sx(UINT32_C(0x00000001));
/* 00256e0c: li s5,0xc */ c->r[21]=sx(UINT32_C(0x0000000c));
/* 00256e10: b 0x00256ef4 */ /* delay 00256e14 */ sw((uint32_t)c->r[18]+UINT32_C(0x00000014),c->f[0]);goto L_00256ef4;
L_00256e18:;
/* 00256e18: lw v1,0x94(a1) */ c->r[3]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000094)));
/* 00256e1c: li v0,0x9 */ c->r[2]=sx(UINT32_C(0x00000009));
/* 00256e20: bne v1,v0,0x00256e40 */ {int taken=(c->r[3]!=c->r[2]);/* delay 00256e24 */ c->r[19]=sx(UINT32_C(0x00000004));if(taken){goto L_00256e40;}}
/* 00256e28: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x00256e30);/* delay 00256e2c */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000092)));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256e30: jal 0x00259180 */ c->r[31]=UINT64_C(0x00256e38);/* delay 00256e34 */ c->r[4]=c->r[2];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2BattleRoster_00259180(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256e38: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256e3c: li s3,0x4 */ c->r[19]=sx(UINT32_C(0x00000004));
L_00256e40:;
/* 00256e40: lw v1,0x10(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000010)));
/* 00256e44: sll s1,s3,0x7 */ c->r[17]=sx((uint32_t)c->r[19]<<7u);
/* 00256e48: addu v1,s1,v1 */ c->r[3]=sx((uint32_t)c->r[17]+(uint32_t)c->r[3]);
/* 00256e4c: lhu v1,0x0(v1) */ c->r[3]=hword((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 00256e50: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 00256e54: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 00256e58: beq v0,zero,0x00256ecc */ {int taken=(c->r[2]==c->r[0]);/* delay 00256e5c */ c->r[2]=c->r[3]&UINT64_C(0x2);if(taken){goto L_00256ecc;}}
/* 00256e60: beq v0,zero,0x00256ecc */ {int taken=(c->r[2]==c->r[0]);/* delay 00256e64 */ c->r[2]=c->r[3]&UINT64_C(0x20);if(taken){goto L_00256ecc;}}
/* 00256e68: bnel v0,zero,0x00256ed0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00256e6c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00256ed0;}}
/* 00256e70: move a0,zero */ c->r[4]=c->r[0];
/* 00256e74: jal 0x002c0c60 */ c->r[31]=UINT64_C(0x00256e7c);/* delay 00256e78 */ c->r[5]=sx(UINT32_C(0x00000014));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx(sdfGetRandInt(c->r[4]==0?NULL:(uint32_t *)at((uint32_t)c->r[4]),(uint32_t)c->r[5]));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256e7c: move a1,s2 */ c->r[5]=c->r[18];
/* 00256e80: move s0,v0 */ c->r[16]=c->r[2];
/* 00256e84: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256e88: move a0,s0 */ c->r[4]=c->r[16];
/* 00256e8c: lw a2,0x10(v0) */ c->r[6]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000010)));
/* 00256e90: jal 0x00263778 */ c->r[31]=UINT64_C(0x00256e98);/* delay 00256e94 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[17]);body_00263778(c);
/* 00256e98: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256e9c: lw v1,0x10(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000010)));
/* 00256ea0: addu v1,s1,v1 */ c->r[3]=sx((uint32_t)c->r[17]+(uint32_t)c->r[3]);
/* 00256ea4: lhu v0,0x0(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 00256ea8: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 00256eac: bnel v0,zero,0x00256ed0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00256eb0 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_00256ed0;}}
/* 00256eb4: lh a1,0x2(v1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000002)));
/* 00256eb8: move a2,s0 */ c->r[6]=c->r[16];
/* 00256ebc: move a0,s2 */ c->r[4]=c->r[18];
/* 00256ec0: li a3,0x28 */ c->r[7]=sx(UINT32_C(0x00000028));
/* 00256ec4: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00256ecc);/* delay 00256ec8 */ c->r[8]=sx(UINT32_C(0x00000028));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
L_00256ecc:;
/* 00256ecc: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_00256ed0:;
/* 00256ed0: slti v0,s3,0xe */ c->r[2]=less(c->r[19],sx(UINT32_C(0x0000000e)));
/* 00256ed4: bnel v0,zero,0x00256e40 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00256ed8 */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));goto L_00256e40;}}
/* 00256edc: b 0x00256ef8 */ /* delay 00256ee0 */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000068)));goto L_00256ef8;
L_00256ee8:;
/* 00256ee8: move s6,zero */ c->r[22]=c->r[0];
/* 00256eec: move s7,zero */ c->r[23]=c->r[0];
/* 00256ef0: move s4,zero */ c->r[20]=c->r[0];
L_00256ef4:;
/* 00256ef4: lw v1,0x68(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000068)));
L_00256ef8:;
/* 00256ef8: sltiu v0,v1,0x7 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000007)));
/* 00256efc: beq v0,zero,0x00256f50 */ {int taken=(c->r[2]==c->r[0]);/* delay 00256f00 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);if(taken){goto L_00256f50;}}
/* 00256f04: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 00256f08: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00256f0c: lw v1,0x4000(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00004000)));
/* 00256f10: jr v1 */ {uint64_t target=c->r[3];/* delay 00256f14 */ (void)0;switch(target){case UINT64_C(0x00256f18):goto L_00256f18;case UINT64_C(0x00256f40):goto L_00256f40;case UINT64_C(0x00256f50):goto L_00256f50;default:abort();}}
L_00256f18:;
/* 00256f18: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256f1c: lw a0,0x94(a0) */ c->r[4]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000094)));
/* 00256f20: slti v0,a0,0x5 */ c->r[2]=less(c->r[4],sx(UINT32_C(0x00000005)));
/* 00256f24: beql v0,zero,0x00256f50 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00256f28 */ c->r[20]=c->r[0];goto L_00256f50;}}
/* 00256f2c: slti v0,a0,0x2 */ c->r[2]=less(c->r[4],sx(UINT32_C(0x00000002)));
/* 00256f30: beq v0,zero,0x00256f50 */ {int taken=(c->r[2]==c->r[0]);/* delay 00256f34 */ (void)0;if(taken){goto L_00256f50;}}
/* 00256f38: b 0x00256f50 */ /* delay 00256f3c */ c->r[20]=c->r[0];goto L_00256f50;
L_00256f40:;
/* 00256f40: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256f44: lw v0,0x94(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000094)));
/* 00256f48: xori v0,v0,0x4 */ c->r[2]=c->r[2]^UINT64_C(0x4);
/* 00256f4c: movn s4,zero,v0 */ if(c->r[2]!=0){c->r[20]=c->r[0];}
L_00256f50:;
/* 00256f50: beq s4,zero,0x00256f78 */ {int taken=(c->r[20]==c->r[0]);/* delay 00256f54 */ c->r[4]=c->r[0];if(taken){goto L_00256f78;}}
/* 00256f58: lwc1 f12,0x14(s2) */ c->f[12]=word((uint32_t)c->r[18]+UINT32_C(0x00000014));
/* 00256f5c: jal 0x002642e0 */ c->r[31]=UINT64_C(0x00256f64);/* delay 00256f60 */ c->r[5]=c->r[18];body_002642e0(c);
/* 00256f64: move a0,zero */ c->r[4]=c->r[0];
/* 00256f68: lw a3,0x28(s2) */ c->r[7]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000028)));
/* 00256f6c: move a2,s5 */ c->r[6]=c->r[21];
/* 00256f70: jal 0x00264368 */ c->r[31]=UINT64_C(0x00256f78);/* delay 00256f74 */ c->r[5]=c->r[18];body_00264368(c);
L_00256f78:;
/* 00256f78: beq s6,zero,0x00256fd4 */ {int taken=(c->r[22]==c->r[0]);/* delay 00256f7c */ (void)0;if(taken){goto L_00256fd4;}}
/* 00256f80: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256f84: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 00256f88: mtc1 at,f20 */ c->f[20]=(uint32_t)c->r[1];
/* 00256f8c: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x00256f94);/* delay 00256f90 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00256f94: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00256f98: move a1,zero */ c->r[5]=c->r[0];
/* 00256f9c: mov.S f12,f20 */ c->f[12]=c->f[20];
/* 00256fa0: lh v1,0x92(a0) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000092)));
/* 00256fa4: lw s0,0x0(a0) */ c->r[16]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 00256fa8: sll v0,v1,0x4 */ c->r[2]=sx((uint32_t)c->r[3]<<4u);
/* 00256fac: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 00256fb0: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 00256fb4: addu s0,s0,v0 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[2]);
/* 00256fb8: jal 0x0024d238 */ c->r[31]=UINT64_C(0x00256fc0);/* delay 00256fbc */ c->r[4]=c->r[16];body_0024d238(c);
/* 00256fc0: move a0,s0 */ c->r[4]=c->r[16];
/* 00256fc4: move a1,zero */ c->r[5]=c->r[0];
/* 00256fc8: mov.S f12,f20 */ c->f[12]=c->f[20];
/* 00256fcc: jal 0x0024cff8 */ c->r[31]=UINT64_C(0x00256fd4);/* delay 00256fd0 */ c->r[6]=sx(UINT32_C(0x00000001));body_0024cff8(c);
L_00256fd4:;
/* 00256fd4: beql s7,zero,0x00257020 */ {int taken=(c->r[23]==c->r[0]);if(taken){/* delay 00256fd8 */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));goto L_00257020;}}
/* 00256fdc: lw v0,0x68(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000068)));
/* 00256fe0: bnel v0,zero,0x00257020 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00256fe4 */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));goto L_00257020;}}
/* 00256fe8: lw a0,0x28(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000028)));
/* 00256fec: lw v0,0x78(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000078)));
/* 00256ff0: andi v0,v0,0x10 */ c->r[2]=c->r[2]&UINT64_C(0x10);
/* 00256ff4: beql v0,zero,0x00257020 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00256ff8 */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));goto L_00257020;}}
/* 00256ffc: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00257000: lh v1,0x92(v0) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000092)));
/* 00257004: lw a2,0x0(v0) */ c->r[6]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 00257008: sll a1,v1,0x4 */ c->r[5]=sx((uint32_t)c->r[3]<<4u);
/* 0025700c: subu a1,a1,v1 */ c->r[5]=sx((uint32_t)c->r[5]-(uint32_t)c->r[3]);
/* 00257010: sll a1,a1,0x4 */ c->r[5]=sx((uint32_t)c->r[5]<<4u);
/* 00257014: jal 0x001b17e0 */ c->r[31]=UINT64_C(0x0025701c);/* delay 00257018 */ c->r[5]=sx((uint32_t)c->r[6]+(uint32_t)c->r[5]);body_001b17e0(c);
/* 0025701c: lw a0,0x0(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
L_00257020:;
/* 00257020: move a2,zero */ c->r[6]=c->r[0];
/* 00257024: li s3,0x9 */ c->r[19]=sx(UINT32_C(0x00000009));
/* 00257028: lw v0,0x10(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000010)));
/* 0025702c: addiu a1,v0,0x200 */ c->r[5]=sx((uint32_t)c->r[2]+UINT32_C(0x00000200));
L_00257030:;
/* 00257030: lhu v1,0x0(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000000));
/* 00257034: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 00257038: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 0025703c: beq v0,zero,0x0025704c */ {int taken=(c->r[2]==c->r[0]);/* delay 00257040 */ c->r[3]=c->r[3]&UINT64_C(0x20);if(taken){goto L_0025704c;}}
/* 00257044: addiu v0,a2,0x1 */ c->r[2]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 00257048: movz a2,v0,v1 */ if(c->r[3]==0){c->r[6]=c->r[2];}
L_0025704c:;
/* 0025704c: addiu s3,s3,-0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0xffffffff));
/* 00257050: bgez s3,0x00257030 */ {int taken=(!neg(c->r[19]));/* delay 00257054 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000080));if(taken){goto L_00257030;}}
/* 00257058: bne a2,zero,0x00257068 */ {int taken=(c->r[6]!=c->r[0]);/* delay 0025705c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_00257068;}}
/* 00257060: li v0,0x9 */ c->r[2]=sx(UINT32_C(0x00000009));
/* 00257064: sw v0,0x44(a0) */ sw((uint32_t)c->r[4]+UINT32_C(0x00000044),(uint32_t)c->r[2]);
L_00257068:;
/* 00257068: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025706c: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00257070: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00257074: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00257078: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 0025707c: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 00257080: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 00257084: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 00257088: lwc1 f20,0x48(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 0025708c: jr ra */ /* delay 00257090 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}

static void body_00257098(BattleOutcomeValues *c){
/* 00257098: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025709c: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 002570a0: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x002570a8);/* delay 002570a4 */ c->r[5]=sx(UINT32_C(0x00000012));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 002570a8: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002570ac: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 002570b0: jr ra */ /* delay 002570b4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_002570b8(BattleOutcomeValues *c){
/* 002570b8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 002570bc: li v0,0x8 */ c->r[2]=sx(UINT32_C(0x00000008));
/* 002570c0: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002570c4: move s0,a0 */ c->r[16]=c->r[4];
/* 002570c8: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 002570cc: move a1,s0 */ c->r[5]=c->r[16];
/* 002570d0: lw a3,0x2c(s0) */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x0000002c)));
/* 002570d4: lh v1,0x6a(a3) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[7]+UINT32_C(0x0000006a)));
/* 002570d8: beq v1,v0,0x00257170 */ {int taken=(c->r[3]==c->r[2]);/* delay 002570dc */ c->r[6]=less(c->r[3],sx(UINT32_C(0x00000009)));if(taken){goto L_00257170;}}
/* 002570e0: beq a2,zero,0x00257100 */ {int taken=(c->r[6]==c->r[0]);/* delay 002570e4 */ c->r[2]=sx(UINT32_C(0x00000009));if(taken){goto L_00257100;}}
/* 002570e8: li v0,0x3 */ c->r[2]=sx(UINT32_C(0x00000003));
/* 002570ec: beql v1,v0,0x002571c0 */ {int taken=(c->r[3]==c->r[2]);if(taken){/* delay 002570f0 */ c->r[4]=c->r[0];goto L_002571c0;}}
/* 002570f4: b 0x00257204 */ /* delay 002570f8 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00257204;
L_00257100:;
/* 00257100: beq v1,v0,0x00257200 */ {int taken=(c->r[3]==c->r[2]);/* delay 00257104 */ c->r[2]=sx(UINT32_C(0x0000000a));if(taken){goto L_00257200;}}
/* 00257108: bnel v1,v0,0x00257204 */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 0025710c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00257204;}}
/* 00257110: lhu v1,0x8(a3) */ c->r[3]=hword((uint32_t)c->r[7]+UINT32_C(0x00000008));
/* 00257114: li v0,0x64 */ c->r[2]=sx(UINT32_C(0x00000064));
/* 00257118: beql v0,zero,0x00257120 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0025711c */ nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nocturne_break(7);goto L_00257120;}}
L_00257120:;
/* 00257120: sll a1,v1,0x4 */ c->r[5]=sx((uint32_t)c->r[3]<<4u);
/* 00257124: subu a1,a1,v1 */ c->r[5]=sx((uint32_t)c->r[5]-(uint32_t)c->r[3]);
/* 00257128: div a1,v0 */ {int32_t n=(int32_t)(uint32_t)c->r[5],d=(int32_t)(uint32_t)c->r[2];if(d==0){c->lo=n<0?UINT64_C(1):UINT64_MAX;c->hi=sx((uint32_t)n);}else if(n==INT32_MIN&&d==-1){c->lo=sx(UINT32_C(0x80000000));c->hi=0;}else{c->lo=sx((uint32_t)(n/d));c->hi=sx((uint32_t)(n%d));}}
/* 0025712c: mflo a1 */ c->r[5]=c->lo;
/* 00257130: jal 0x002532a8 */ c->r[31]=UINT64_C(0x00257138);/* delay 00257134 */ (void)0;nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nocturneBattleOutcomeNativeChoice((uint32_t)c->r[31]-8u,c->r[4],c->r[5],c->r[29],c->r[31],c->r[16]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00257138: move a0,zero */ c->r[4]=c->r[0];
/* 0025713c: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 00257140: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];
/* 00257144: jal 0x002642e0 */ c->r[31]=UINT64_C(0x0025714c);/* delay 00257148 */ c->r[5]=c->r[16];body_002642e0(c);
/* 0025714c: move a0,zero */ c->r[4]=c->r[0];
/* 00257150: move a1,s0 */ c->r[5]=c->r[16];
/* 00257154: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00257158: lw a3,0x28(a1) */ c->r[7]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000028)));
/* 0025715c: move a2,zero */ c->r[6]=c->r[0];
/* 00257160: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00257164: j 0x00264368 */ /* delay 00257168 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_00264368(c);return;
L_00257170:;
/* 00257170: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 00257174: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];
/* 00257178: jal 0x002642e0 */ c->r[31]=UINT64_C(0x00257180);/* delay 0025717c */ c->r[4]=c->r[0];body_002642e0(c);
/* 00257180: move a0,zero */ c->r[4]=c->r[0];
/* 00257184: lw a3,0x28(s0) */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00257188: move a1,s0 */ c->r[5]=c->r[16];
/* 0025718c: jal 0x00264368 */ c->r[31]=UINT64_C(0x00257194);/* delay 00257190 */ c->r[6]=c->r[0];body_00264368(c);
/* 00257194: lw v1,0x28(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00257198: move a0,s0 */ c->r[4]=c->r[16];
/* 0025719c: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002571a0: lh a1,0x92(v1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));
/* 002571a4: move a2,zero */ c->r[6]=c->r[0];
/* 002571a8: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002571ac: li a3,0x5 */ c->r[7]=sx(UINT32_C(0x00000005));
/* 002571b0: li t0,0x5 */ c->r[8]=sx(UINT32_C(0x00000005));
/* 002571b4: j 0x002517e0 */ /* delay 002571b8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);return;
L_002571c0:;
/* 002571c0: lui at,0xbf00 */ c->r[1]=sx(UINT32_C(0xbf000000));
/* 002571c4: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];
/* 002571c8: jal 0x002642e0 */ c->r[31]=UINT64_C(0x002571d0);/* delay 002571cc */ c->r[5]=c->r[16];body_002642e0(c);
/* 002571d0: move a0,zero */ c->r[4]=c->r[0];
/* 002571d4: lw a3,0x28(s0) */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 002571d8: move a1,s0 */ c->r[5]=c->r[16];
/* 002571dc: jal 0x00264368 */ c->r[31]=UINT64_C(0x002571e4);/* delay 002571e0 */ c->r[6]=sx(UINT32_C(0x00000001));body_00264368(c);
/* 002571e4: lw v1,0x28(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 002571e8: move a0,s0 */ c->r[4]=c->r[16];
/* 002571ec: move a2,zero */ c->r[6]=c->r[0];
/* 002571f0: lh a1,0x92(v1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));
/* 002571f4: li a3,0x5 */ c->r[7]=sx(UINT32_C(0x00000005));
/* 002571f8: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00257200);/* delay 002571fc */ c->r[8]=sx(UINT32_C(0x00000005));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
L_00257200:;
/* 00257200: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00257204:;
/* 00257204: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00257208: jr ra */ /* delay 0025720c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00257210(BattleOutcomeValues *c){
/* 00257210: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00257214: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 00257218: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x00257220);/* delay 0025721c */ c->r[5]=sx(UINT32_C(0x00000012));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00257220: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00257224: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00257228: jr ra */ /* delay 0025722c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00257230(BattleOutcomeValues *c){
/* 00257230: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00257234: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00257238: move s0,a0 */ c->r[16]=c->r[4];
/* 0025723c: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 00257240: move a1,s0 */ c->r[5]=c->r[16];
/* 00257244: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00257248: lbu v0,0x6b(v1) */ c->r[2]=*at((uint32_t)c->r[3]+UINT32_C(0x0000006b));
/* 0025724c: addiu a2,v0,0x1 */ c->r[6]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));
/* 00257250: sltiu v0,v0,0xff */ c->r[2]=(c->r[2]<sx(UINT32_C(0x000000ff)));
/* 00257254: beq v0,zero,0x00257260 */ {int taken=(c->r[2]==c->r[0]);/* delay 00257258 */ c->r[4]=c->r[0];if(taken){goto L_00257260;}}
/* 0025725c: sb a2,0x6b(v1) */ *at((uint32_t)c->r[3]+UINT32_C(0x0000006b))=(uint8_t)c->r[6];
L_00257260:;
/* 00257260: lui at,0xc120 */ c->r[1]=sx(UINT32_C(0xc1200000));
/* 00257264: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];
/* 00257268: jal 0x002642e0 */ c->r[31]=UINT64_C(0x00257270);/* delay 0025726c */ (void)0;body_002642e0(c);
/* 00257270: move a0,zero */ c->r[4]=c->r[0];
/* 00257274: lw a3,0x28(s0) */ c->r[7]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 00257278: move a1,s0 */ c->r[5]=c->r[16];
/* 0025727c: jal 0x00264368 */ c->r[31]=UINT64_C(0x00257284);/* delay 00257280 */ c->r[6]=sx(UINT32_C(0x00000008));body_00264368(c);
/* 00257284: jal 0x00269e98 */ c->r[31]=UINT64_C(0x0025728c);/* delay 00257288 */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatCheckEscape_00269E98(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0025728c: beq v0,zero,0x002572b0 */ {int taken=(c->r[2]==c->r[0]);/* delay 00257290 */ c->r[4]=c->r[16];if(taken){goto L_002572b0;}}
/* 00257294: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00257298: li v0,0x3 */ c->r[2]=sx(UINT32_C(0x00000003));
/* 0025729c: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002572a0: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002572a4: sw v0,0x44(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000044),(uint32_t)c->r[2]);
/* 002572a8: jr ra */ /* delay 002572ac */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
L_002572b0:;
/* 002572b0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002572b4: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002572b8: j 0x00252cd8 */ /* delay 002572bc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_00252cd8(c);return;
}

static void body_002572c0(BattleOutcomeValues *c){
/* 002572c0: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 002572c4: li v1,0xf */ c->r[3]=sx(UINT32_C(0x0000000f));
/* 002572c8: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002572cc: move s0,a0 */ c->r[16]=c->r[4];
/* 002572d0: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 002572d4: beql v1,zero,0x002572dc */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 002572d8 */ nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nocturne_break(7);goto L_002572dc;}}
L_002572dc:;
/* 002572dc: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
/* 002572e0: lhu v0,0xa(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x0000000a));
/* 002572e4: divu v0,v1 */ {uint32_t n=(uint32_t)c->r[2],d=(uint32_t)c->r[3];c->lo=d?sx(n/d):UINT64_MAX;c->hi=sx(d?n%d:n);}
/* 002572e8: mflo v0 */ c->r[2]=c->lo;
/* 002572ec: andi v1,v0,0xffff */ c->r[3]=c->r[2]&UINT64_C(0xffff);
/* 002572f0: beq v1,a1,0x00257308 */ {int taken=(c->r[3]==c->r[5]);/* delay 002572f4 */ c->r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_00257308;}}
/* 002572f8: beq v1,v0,0x00257328 */ {int taken=(c->r[3]==c->r[2]);/* delay 002572fc */ c->r[2]=c->r[0];if(taken){goto L_00257328;}}
/* 00257300: b 0x00257398 */ /* delay 00257304 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00257398;
L_00257308:;
/* 00257308: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0025730c: li a1,0x3 */ c->r[5]=sx(UINT32_C(0x00000003));
/* 00257310: lw v1,0x44(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000044)));
/* 00257314: beq v1,a1,0x00257394 */ {int taken=(c->r[3]==c->r[5]);/* delay 00257318 */ c->r[2]=c->r[0];if(taken){goto L_00257394;}}
/* 0025731c: b 0x00257388 */ /* delay 00257320 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000188),(uint32_t)c->r[0]);goto L_00257388;
L_00257328:;
/* 00257328: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0025732c: li a0,0x3 */ c->r[4]=sx(UINT32_C(0x00000003));
/* 00257330: lw v1,0x44(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000044)));
/* 00257334: bne v1,a0,0x00257394 */ {int taken=(c->r[3]!=c->r[4]);/* delay 00257338 */ c->r[2]=c->r[0];if(taken){goto L_00257394;}}
/* 0025733c: li v0,0x1e */ c->r[2]=sx(UINT32_C(0x0000001e));
/* 00257340: li a3,0x14 */ c->r[7]=sx(UINT32_C(0x00000014));
/* 00257344: sw v0,0x188(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000188),(uint32_t)c->r[2]);
/* 00257348: li a0,0xff */ c->r[4]=sx(UINT32_C(0x000000ff));
/* 0025734c: li a1,0xff */ c->r[5]=sx(UINT32_C(0x000000ff));
/* 00257350: jal 0x00105098 */ c->r[31]=UINT64_C(0x00257358);/* delay 00257354 */ c->r[6]=sx(UINT32_C(0x000000ff));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);dds3FadeOut(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00257358: move a0,zero */ c->r[4]=c->r[0];
/* 0025735c: move a1,s0 */ c->r[5]=c->r[16];
/* 00257360: jal 0x00262cc0 */ c->r[31]=UINT64_C(0x00257368);/* delay 00257364 */ c->r[6]=sx(UINT32_C(0x00010000));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddSePacket(c->r[4],c->r[5],c->r[6]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00257368: lw v1,0x28(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 0025736c: move a2,zero */ c->r[6]=c->r[0];
/* 00257370: li a3,0x11 */ c->r[7]=sx(UINT32_C(0x00000011));
/* 00257374: lh a1,0x92(v1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));
/* 00257378: li t0,0x11 */ c->r[8]=sx(UINT32_C(0x00000011));
/* 0025737c: jal 0x002517e0 */ c->r[31]=UINT64_C(0x00257384);/* delay 00257380 */ c->r[4]=c->r[16];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00257384: move a0,s0 */ c->r[4]=c->r[16];
L_00257388:;
/* 00257388: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x00257390);/* delay 0025738c */ c->r[5]=sx(UINT32_C(0x00000012));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00257390: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_00257394:;
/* 00257394: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00257398:;
/* 00257398: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025739c: jr ra */ /* delay 002573a0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_002573a8(BattleOutcomeValues *c){
/* 002573a8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 002573ac: lui v0,0x54 */ c->r[2]=sx(UINT32_C(0x00540000));
/* 002573b0: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002573b4: move s0,a0 */ c->r[16]=c->r[4];
/* 002573b8: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 002573bc: jal 0x002d4748 */ c->r[31]=UINT64_C(0x002573c4);/* delay 002573c0 */ c->r[4]=sx((uint32_t)c->r[2]+UINT32_C(0x00004020));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleOutcomeNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 002573c4: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 002573c8: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 002573cc: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 002573d0: beq v0,zero,0x002573e0 */ {int taken=(c->r[2]==c->r[0]);/* delay 002573d4 */ c->r[4]=sx(UINT32_C(0x00000015));if(taken){goto L_002573e0;}}
/* 002573d8: jal 0x001b1740 */ c->r[31]=UINT64_C(0x002573e0);/* delay 002573dc */ (void)0;nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbCameraSetState(c->r[4]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
L_002573e0:;
/* 002573e0: lw a2,0x24(s0) */ c->r[6]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000024)));
/* 002573e4: move a1,s0 */ c->r[5]=c->r[16];
/* 002573e8: jal 0x00263778 */ c->r[31]=UINT64_C(0x002573f0);/* delay 002573ec */ c->r[4]=c->r[0];body_00263778(c);
/* 002573f0: lw v1,0x28(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000028)));
/* 002573f4: move a2,zero */ c->r[6]=c->r[0];
/* 002573f8: li a3,0x28 */ c->r[7]=sx(UINT32_C(0x00000028));
/* 002573fc: lh a1,0x92(v1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000092)));
/* 00257400: move a0,s0 */ c->r[4]=c->r[16];
/* 00257404: jal 0x002517e0 */ c->r[31]=UINT64_C(0x0025740c);/* delay 00257408 */ c->r[8]=sx(UINT32_C(0x00000028));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetTimeList(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0025740c: li a0,0xa */ c->r[4]=sx(UINT32_C(0x0000000a));
/* 00257410: lui at,0xbf00 */ c->r[1]=sx(UINT32_C(0xbf000000));
/* 00257414: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];
/* 00257418: jal 0x002642e0 */ c->r[31]=UINT64_C(0x00257420);/* delay 0025741c */ c->r[5]=c->r[16];body_002642e0(c);
/* 00257420: li a0,0xa */ c->r[4]=sx(UINT32_C(0x0000000a));
/* 00257424: move a1,s0 */ c->r[5]=c->r[16];
/* 00257428: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025742c: lw a3,0x28(a1) */ c->r[7]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000028)));
/* 00257430: li a2,0x9 */ c->r[6]=sx(UINT32_C(0x00000009));
/* 00257434: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00257438: j 0x00264368 */ /* delay 0025743c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_00264368(c);return;
}

static void body_00257440(BattleOutcomeValues *c){
/* 00257440: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00257444: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 00257448: jal 0x00257cc8 */ c->r[31]=UINT64_C(0x00257450);/* delay 0025744c */ c->r[5]=sx(UINT32_C(0x00000012));nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);nbActionSetNextSeq(c->r[4],c->r[5]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00257450: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00257454: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00257458: jr ra */ /* delay 0025745c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00262a68(BattleOutcomeValues *c){
/* 00262a68: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00262a6c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00262a70: move s0,a0 */ c->r[16]=c->r[4];
/* 00262a74: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00262a78: move s1,a1 */ c->r[17]=c->r[5];
/* 00262a7c: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 00262a80: swc1 f20,0x18(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000018),c->f[20]);
/* 00262a84: jal 0x0025e8e0 */ c->r[31]=UINT64_C(0x00262a8c);/* delay 00262a88 */ c->f[20]=c->f[12];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetKoukaProcessData();nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00262a8c: move a1,s0 */ c->r[5]=c->r[16];
/* 00262a90: move a3,s1 */ c->r[7]=c->r[17];
/* 00262a94: move a0,v0 */ c->r[4]=c->r[2];
/* 00262a98: jal 0x0025ea48 */ c->r[31]=UINT64_C(0x00262aa0);/* delay 00262a9c */ c->r[6]=c->r[0];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddKoukaPacket(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00262aa0: li a0,0x12 */ c->r[4]=sx(UINT32_C(0x00000012));
/* 00262aa4: move v1,v0 */ c->r[3]=c->r[2];
/* 00262aa8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00262aac: swc1 f20,0x28(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000028),c->f[20]);
/* 00262ab0: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00262ab4: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00262ab8: lwc1 f20,0x18(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00262abc: sb a0,0x4(v1) */ *at((uint32_t)c->r[3]+UINT32_C(0x00000004))=(uint8_t)c->r[4];
/* 00262ac0: jr ra */ /* delay 00262ac4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00262ac8(BattleOutcomeValues *c){
/* 00262ac8: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 00262acc: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00262ad0: move s0,a0 */ c->r[16]=c->r[4];
/* 00262ad4: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00262ad8: move s1,a1 */ c->r[17]=c->r[5];
/* 00262adc: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00262ae0: move s2,a3 */ c->r[18]=c->r[7];
/* 00262ae4: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 00262ae8: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 00262aec: jal 0x0025e8e0 */ c->r[31]=UINT64_C(0x00262af4);/* delay 00262af0 */ c->r[19]=c->r[6];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetKoukaProcessData();nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00262af4: move a0,v0 */ c->r[4]=c->r[2];
/* 00262af8: move a1,s0 */ c->r[5]=c->r[16];
/* 00262afc: move a3,s1 */ c->r[7]=c->r[17];
/* 00262b00: jal 0x0025ea48 */ c->r[31]=UINT64_C(0x00262b08);/* delay 00262b04 */ c->r[6]=c->r[0];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddKoukaPacket(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00262b08: li a0,0x1f */ c->r[4]=sx(UINT32_C(0x0000001f));
/* 00262b0c: move v1,v0 */ c->r[3]=c->r[2];
/* 00262b10: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00262b14: sh s2,0x2a(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x0000002a),(uint16_t)c->r[18]);
/* 00262b18: sh s3,0x28(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x00000028),(uint16_t)c->r[19]);
/* 00262b1c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00262b20: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00262b24: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00262b28: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00262b2c: sb a0,0x4(v1) */ *at((uint32_t)c->r[3]+UINT32_C(0x00000004))=(uint8_t)c->r[4];
/* 00262b30: jr ra */ /* delay 00262b34 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_00263778(BattleOutcomeValues *c){
/* 00263778: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0026377c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00263780: move s0,a2 */ c->r[16]=c->r[6];
/* 00263784: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00263788: move s1,a0 */ c->r[17]=c->r[4];
/* 0026378c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00263790: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 00263794: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0026379c);/* delay 00263798 */ c->r[18]=c->r[5];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0026379c: lh a3,0x2(s0) */ c->r[7]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[16]+UINT32_C(0x00000002)));
/* 002637a0: move a0,s1 */ c->r[4]=c->r[17];
/* 002637a4: lhu v1,0x0(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 002637a8: move a1,s2 */ c->r[5]=c->r[18];
/* 002637ac: sll a2,a3,0x4 */ c->r[6]=sx((uint32_t)c->r[7]<<4u);
/* 002637b0: lw t0,0x0(v0) */ c->r[8]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 002637b4: ori v1,v1,0x20 */ c->r[3]=c->r[3]|UINT64_C(0x20);
/* 002637b8: subu a2,a2,a3 */ c->r[6]=sx((uint32_t)c->r[6]-(uint32_t)c->r[7]);
/* 002637bc: sh v1,0x0(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000000),(uint16_t)c->r[3]);
/* 002637c0: sll a2,a2,0x4 */ c->r[6]=sx((uint32_t)c->r[6]<<4u);
/* 002637c4: addu a2,t0,a2 */ c->r[6]=sx((uint32_t)c->r[8]+(uint32_t)c->r[6]);
/* 002637c8: li t0,0x6 */ c->r[8]=sx(UINT32_C(0x00000006));
/* 002637cc: li t1,0x6 */ c->r[9]=sx(UINT32_C(0x00000006));
/* 002637d0: li t2,0x6 */ c->r[10]=sx(UINT32_C(0x00000006));
/* 002637d4: jal 0x002638a0 */ c->r[31]=UINT64_C(0x002637dc);/* delay 002637d8 */ c->r[7]=c->r[0];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbMakeUnitFadeOutPacket(c->r[4],c->r[5],c->r[6],c->r[7],c->r[8],c->r[9],c->r[10]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 002637dc: addiu a0,s1,0xd */ c->r[4]=sx((uint32_t)c->r[17]+UINT32_C(0x0000000d));
/* 002637e0: move a1,s2 */ c->r[5]=c->r[18];
/* 002637e4: move a2,s0 */ c->r[6]=c->r[16];
/* 002637e8: jal 0x002622d0 */ c->r[31]=UINT64_C(0x002637f0);/* delay 002637ec */ c->r[7]=c->r[0];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbAddReturnKoukaPacket(c->r[4],c->r[5],c->r[6],c->r[7]);nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 002637f0: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 002637f4: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002637f8: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002637fc: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00263800: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00263804: jr ra */ /* delay 00263808 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_002642e0(BattleOutcomeValues *c){
/* 002642e0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002642e4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002642e8: move s0,a0 */ c->r[16]=c->r[4];
/* 002642ec: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002642f0: move s1,a1 */ c->r[17]=c->r[5];
/* 002642f4: swc1 f20,0x18(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000018),c->f[20]);
/* 002642f8: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 002642fc: jal 0x002469a0 */ c->r[31]=UINT64_C(0x00264304);/* delay 00264300 */ c->f[20]=c->f[12];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 00264304: move v1,v0 */ c->r[3]=c->r[2];
/* 00264308: move a0,s0 */ c->r[4]=c->r[16];
/* 0026430c: lw v0,0x60(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000060)));
/* 00264310: andi v0,v0,0x8 */ c->r[2]=c->r[2]&UINT64_C(0x8);
/* 00264314: beq v0,zero,0x00264328 */ {int taken=(c->r[2]==c->r[0]);/* delay 00264318 */ c->r[5]=c->r[17];if(taken){goto L_00264328;}}
/* 0026431c: b 0x0026432c */ /* delay 00264320 */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x0000001a)));goto L_0026432c;
L_00264328:;
/* 00264328: lh v0,0x18(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000018)));
L_0026432c:;
/* 0026432c: mtc1 v0,f12 */ c->f[12]=(uint32_t)c->r[2];
/* 00264330: cvt.s.W f12,f12 */ c->f[12]=EE_FPU_CVT_S_W(c->f[12]);
/* 00264334: nop  */ (void)0;
/* 00264338: nop  */ (void)0;
/* 0026433c: div.S f12,f20,f12 */ c->f[12]=EE_FPU_DIV_S(c->f[20],c->f[12]);
/* 00264340: jal 0x00262a68 */ c->r[31]=UINT64_C(0x00264348);/* delay 00264344 */ (void)0;body_00262a68(c);
/* 00264348: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0026434c: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00264350: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00264354: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00264358: lwc1 f20,0x18(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0026435c: jr ra */ /* delay 00264360 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00264368(BattleOutcomeValues *c){
/* 00264368: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0026436c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00264370: move s0,a2 */ c->r[16]=c->r[6];
/* 00264374: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00264378: move s1,a0 */ c->r[17]=c->r[4];
/* 0026437c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00264380: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 00264384: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0026438c);/* delay 00264388 */ c->r[18]=c->r[5];nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOutcomeSetStackPointer((uint32_t)c->r[29]);
/* 0026438c: lh t1,0x7a(v0) */ c->r[9]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x0000007a)));
/* 00264390: move t4,zero */ c->r[12]=c->r[0];
/* 00264394: lhu t8,0x78(v0) */ c->r[24]=hword((uint32_t)c->r[2]+UINT32_C(0x00000078));
/* 00264398: move t3,zero */ c->r[11]=c->r[0];
/* 0026439c: lh t0,0x78(v0) */ c->r[8]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[2]+UINT32_C(0x00000078)));
/* 002643a0: move a2,zero */ c->r[6]=c->r[0];
/* 002643a4: lhu t7,0x7a(v0) */ c->r[15]=hword((uint32_t)c->r[2]+UINT32_C(0x0000007a));
/* 002643a8: move a3,zero */ c->r[7]=c->r[0];
/* 002643ac: move t5,zero */ c->r[13]=c->r[0];
/* 002643b0: sltiu t6,s0,0x12 */ c->r[14]=(c->r[16]<sx(UINT32_C(0x00000012)));
/* 002643b4: sltiu a1,t0,0x1 */ c->r[5]=(c->r[8]<sx(UINT32_C(0x00000001)));
L_002643b8:;
/* 002643b8: beq t6,zero,0x00264468 */ {int taken=(c->r[14]==c->r[0]);/* delay 002643bc */ c->r[4]=less(c->r[8],c->r[9]);if(taken){goto L_00264468;}}
/* 002643c0: sll v0,s0,0x2 */ c->r[2]=sx((uint32_t)c->r[16]<<2u);
/* 002643c4: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 002643c8: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 002643cc: lw v1,0x4940(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00004940)));
/* 002643d0: jr v1 */ {uint64_t target=c->r[3];/* delay 002643d4 */ (void)0;switch(target){case UINT64_C(0x002643d8):goto L_002643d8;case UINT64_C(0x002643e8):goto L_002643e8;case UINT64_C(0x002643f8):goto L_002643f8;case UINT64_C(0x00264408):goto L_00264408;case UINT64_C(0x00264440):goto L_00264440;case UINT64_C(0x00264450):goto L_00264450;case UINT64_C(0x00264458):goto L_00264458;case UINT64_C(0x00264460):goto L_00264460;default:abort();}}
L_002643d8:;
/* 002643d8: bne a0,zero,0x00264468 */ {int taken=(c->r[4]!=c->r[0]);/* delay 002643dc */ c->r[11]=sx(UINT32_C(0xffffffff));if(taken){goto L_00264468;}}
/* 002643e0: b 0x00264468 */ /* delay 002643e4 */ c->r[12]=sx(UINT32_C(0xffffffff));goto L_00264468;
L_002643e8:;
/* 002643e8: beql a0,zero,0x00264468 */ {int taken=(c->r[4]==c->r[0]);if(taken){/* delay 002643ec */ c->r[12]=sx(UINT32_C(0xffffffff));goto L_00264468;}}
/* 002643f0: b 0x00264468 */ /* delay 002643f4 */ c->r[11]=sx(UINT32_C(0xffffffff));goto L_00264468;
L_002643f8:;
/* 002643f8: beql a1,zero,0x00264468 */ {int taken=(c->r[5]==c->r[0]);if(taken){/* delay 002643fc */ c->r[12]=sx(UINT32_C(0xffffffff));goto L_00264468;}}
/* 00264400: b 0x00264468 */ /* delay 00264404 */ c->r[11]=sx(UINT32_C(0xffffffff));goto L_00264468;
L_00264408:;
/* 00264408: beq a0,zero,0x00264430 */ {int taken=(c->r[4]==c->r[0]);/* delay 0026440c */ c->r[2]=sx((uint32_t)c->r[9]+UINT32_C(0xfffffffe));if(taken){goto L_00264430;}}
/* 00264410: slt v0,v0,t0 */ c->r[2]=less(c->r[2],c->r[8]);
/* 00264414: beq v0,zero,0x00264468 */ {int taken=(c->r[2]==c->r[0]);/* delay 00264418 */ c->r[11]=sx(UINT32_C(0xfffffffe));if(taken){goto L_00264468;}}
/* 0026441c: subu v0,t0,t1 */ c->r[2]=sx((uint32_t)c->r[8]-(uint32_t)c->r[9]);
/* 00264420: addiu v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000002));
/* 00264424: b 0x00264468 */ /* delay 00264428 */ c->r[12]=sx((uint32_t)c->r[0]-(uint32_t)c->r[2]);goto L_00264468;
L_00264430:;
/* 00264430: li t3,-0x2 */ c->r[11]=sx(UINT32_C(0xfffffffe));
/* 00264434: b 0x00264468 */ /* delay 00264438 */ c->r[12]=sx(UINT32_C(0xfffffffe));goto L_00264468;
L_00264440:;
/* 00264440: li t3,-0xa */ c->r[11]=sx(UINT32_C(0xfffffff6));
/* 00264444: b 0x00264468 */ /* delay 00264448 */ c->r[12]=sx(UINT32_C(0xfffffff6));goto L_00264468;
L_00264450:;
/* 00264450: b 0x00264464 */ /* delay 00264454 */ c->r[11]=sx(UINT32_C(0x00000002));goto L_00264464;
L_00264458:;
/* 00264458: b 0x00264464 */ /* delay 0026445c */ c->r[11]=sx(UINT32_C(0x00000004));goto L_00264464;
L_00264460:;
/* 00264460: li t3,0x3 */ c->r[11]=sx(UINT32_C(0x00000003));
L_00264464:;
/* 00264464: move t4,zero */ c->r[12]=c->r[0];
L_00264468:;
/* 00264468: addu t0,t0,t4 */ c->r[8]=sx((uint32_t)c->r[8]+(uint32_t)c->r[12]);
/* 0026446c: addu t1,t1,t3 */ c->r[9]=sx((uint32_t)c->r[9]+(uint32_t)c->r[11]);
/* 00264470: sll v0,t8,0x10 */ c->r[2]=sx((uint32_t)c->r[24]<<16u);
/* 00264474: slti v1,t0,0x0 */ c->r[3]=less(c->r[8],sx(UINT32_C(0x00000000)));
/* 00264478: sra t2,v0,0x10 */ c->r[10]=sar((uint32_t)c->r[2],16u);
/* 0026447c: slti a0,t1,0x0 */ c->r[4]=less(c->r[9],sx(UINT32_C(0x00000000)));
/* 00264480: addu a2,a2,t4 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[12]);
/* 00264484: movn t0,zero,v1 */ if(c->r[3]!=0){c->r[8]=c->r[0];}
/* 00264488: movn t1,zero,a0 */ if(c->r[4]!=0){c->r[9]=c->r[0];}
/* 0026448c: li a0,0x7 */ c->r[4]=sx(UINT32_C(0x00000007));
/* 00264490: addu v1,t2,a2 */ c->r[3]=sx((uint32_t)c->r[10]+(uint32_t)c->r[6]);
/* 00264494: slti a1,t0,0x8 */ c->r[5]=less(c->r[8],sx(UINT32_C(0x00000008)));
/* 00264498: slti v0,t1,0x8 */ c->r[2]=less(c->r[9],sx(UINT32_C(0x00000008)));
/* 0026449c: slti v1,v1,0x9 */ c->r[3]=less(c->r[3],sx(UINT32_C(0x00000009)));
/* 002644a0: movz t1,a0,v0 */ if(c->r[2]==0){c->r[9]=c->r[4];}
/* 002644a4: movz t0,a0,a1 */ if(c->r[5]==0){c->r[8]=c->r[4];}
/* 002644a8: bne v1,zero,0x002644b8 */ {int taken=(c->r[3]!=c->r[0]);/* delay 002644ac */ c->r[7]=sx((uint32_t)c->r[7]+(uint32_t)c->r[11]);if(taken){goto L_002644b8;}}
/* 002644b0: li v0,0x8 */ c->r[2]=sx(UINT32_C(0x00000008));
/* 002644b4: subu a2,v0,t2 */ c->r[6]=sx((uint32_t)c->r[2]-(uint32_t)c->r[10]);
L_002644b8:;
/* 002644b8: sll v1,t7,0x10 */ c->r[3]=sx((uint32_t)c->r[15]<<16u);
/* 002644bc: sra v1,v1,0x10 */ c->r[3]=sar((uint32_t)c->r[3],16u);
/* 002644c0: addu v0,v1,a3 */ c->r[2]=sx((uint32_t)c->r[3]+(uint32_t)c->r[7]);
/* 002644c4: slti v0,v0,0x9 */ c->r[2]=less(c->r[2],sx(UINT32_C(0x00000009)));
/* 002644c8: bne v0,zero,0x002644d8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002644cc */ c->r[13]=sx((uint32_t)c->r[13]+UINT32_C(0x00000001));if(taken){goto L_002644d8;}}
/* 002644d0: li v0,0x8 */ c->r[2]=sx(UINT32_C(0x00000008));
/* 002644d4: subu a3,v0,v1 */ c->r[7]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
L_002644d8:;
/* 002644d8: blez t5,0x002643b8 */ {int taken=((neg(c->r[13])||!c->r[13]));/* delay 002644dc */ c->r[5]=(c->r[8]<sx(UINT32_C(0x00000001)));if(taken){goto L_002643b8;}}
/* 002644e0: move a0,s1 */ c->r[4]=c->r[17];
/* 002644e4: jal 0x00262ac8 */ c->r[31]=UINT64_C(0x002644ec);/* delay 002644e8 */ c->r[5]=c->r[18];body_00262ac8(c);
/* 002644ec: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 002644f0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002644f4: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002644f8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002644fc: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00264500: jr ra */ /* delay 00264504 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}
static BattleOutcomeValues begin(int resident_f12){BattleOutcomeValues c={0};c.r[28]=UINT64_C(0x00554170);c.r[29]=nocturneBattleOutcomeStackPointer();for(unsigned r=16;r<=23;++r)c.r[r]=nocturneBattleOutcomeReadGpr(r);c.r[30]=nocturneBattleOutcomeReadGpr(30);c.r[31]=nocturneBattleOutcomeReadGpr(31);c.f[20]=nocturneBattleOutcomeReadFpr(20);c.f[21]=nocturneBattleOutcomeReadFpr(21);if(resident_f12)c.f[12]=nocturneBattleOutcomeReadFpr(12);return c;}
void ps2BattleOutcome_001B17E0(uint64_t p0,uint64_t p1){BattleOutcomeValues c=begin(0);c.r[4]=p0;c.r[5]=p1;body_001b17e0(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleOutcome_001E3B68(uint64_t p0,uint64_t p1){BattleOutcomeValues c=begin(0);c.r[4]=p0;c.r[5]=p1;body_001e3b68(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleOutcome_001E3B70(uint64_t p0){BattleOutcomeValues c=begin(1);c.r[4]=p0;body_001e3b70(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleOutcome_001E3B78(uint64_t p0,uint64_t p1,uint64_t p2){BattleOutcomeValues c=begin(0);c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_001e3b78(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleOutcome_001E3CC0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4){BattleOutcomeValues c=begin(0);c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;c.r[8]=p4;body_001e3cc0(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleOutcome_0024CE78(uint64_t p0,uint64_t p1,uint64_t p2){BattleOutcomeValues c=begin(0);c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_0024ce78(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleOutcome_0024CFF8(uint64_t p0,uint64_t p1,uint64_t p2){BattleOutcomeValues c=begin(1);c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_0024cff8(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleOutcome_0024D238(uint64_t p0,uint64_t p1){BattleOutcomeValues c=begin(1);c.r[4]=p0;c.r[5]=p1;body_0024d238(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleOutcome_0024D428(uint64_t p0,uint64_t p1){BattleOutcomeValues c=begin(1);c.r[4]=p0;c.r[5]=p1;body_0024d428(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return (uint64_t)c.f[0];}
uint64_t ps2BattleOutcome_00252CD8(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_00252cd8(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleOutcome_00256C00(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_00256c00(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleOutcome_00257098(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_00257098(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleOutcome_002570B8(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_002570b8(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleOutcome_00257210(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_00257210(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleOutcome_00257230(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_00257230(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleOutcome_002572C0(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_002572c0(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleOutcome_002573A8(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_002573a8(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleOutcome_00257440(uint64_t p0){BattleOutcomeValues c=begin(0);c.r[4]=p0;body_00257440(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2BattleOutcome_00262A68(uint64_t p0,uint64_t p1){BattleOutcomeValues c=begin(1);c.r[4]=p0;c.r[5]=p1;body_00262a68(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2BattleOutcome_00262AC8(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3){BattleOutcomeValues c=begin(0);c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;body_00262ac8(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2BattleOutcome_00263778(uint64_t p0,uint64_t p1,uint64_t p2){BattleOutcomeValues c=begin(0);c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_00263778(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2BattleOutcome_002642E0(uint64_t p0,uint64_t p1){BattleOutcomeValues c=begin(1);c.r[4]=p0;c.r[5]=p1;body_002642e0(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2BattleOutcome_00264368(uint64_t p0,uint64_t p1,uint64_t p2){BattleOutcomeValues c=begin(0);c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_00264368(&c);nocturneBattleOutcomeSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
