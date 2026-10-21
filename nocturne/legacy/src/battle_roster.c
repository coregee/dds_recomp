/* Three complete battle roster/order callers,216 original instructions.
 * Fixed native-PC semantic control and actual registered typed callees.
 * Raw64 slots, effective32 guest addresses; not a shared volatile CPU bank. */
#include "battle_roster.h"
#include "battle_roster_transport.h"
#include "battle_action_status.h"
#include "battle_work_access.h"
#include "compendium_records.h"
#include "nocturne.h"
#include "unit_progression.h"
#include <string.h>
typedef struct BattleRosterValues {uint64_t r[32];} BattleRosterValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleRosterAddress(a);}
static uint16_t hword(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
#define A0 c->r[4]
#define A1 c->r[5]

static void body_002580e8(BattleRosterValues *c);
static void body_00259180(BattleRosterValues *c);
static void body_002594b0(BattleRosterValues *c);

static void body_002580e8(BattleRosterValues *c){
/* 002580e8: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 002580ec: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002580f0: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 002580f4: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002580f8: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 002580fc: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 00258100: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 00258104: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 00258108: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 0025810c: sd s8,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[30]);
/* 00258110: sd ra,0x48(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000048),c->r[31]);
/* 00258114: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0025811c);/* delay 00258118 */ c->r[16]=c->r[4];nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 0025811c: move s4,v0 */ c->r[20]=c->r[2];
/* 00258120: slti v0,s0,0xb */ c->r[2]=less(c->r[16],sx(UINT32_C(0x0000000b)));
/* 00258124: beql v0,zero,0x00258254 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00258128 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00258254;}}
/* 0025812c: addiu s7,s4,0x8 */ c->r[23]=sx((uint32_t)c->r[20]+UINT32_C(0x00000008));
/* 00258130: addiu s8,s0,0x40 */ c->r[30]=sx((uint32_t)c->r[16]+UINT32_C(0x00000040));
/* 00258134: nop  */ (void)0;
L_00258138:;
/* 00258138: addu v0,s7,s8 */ c->r[2]=sx((uint32_t)c->r[23]+(uint32_t)c->r[30]);
/* 0025813c: lb v1,0x0(v0) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 00258140: bltz v1,0x00258240 */ {int taken=(neg(c->r[3]));/* delay 00258144 */ c->r[21]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));if(taken){goto L_00258240;}}
/* 00258148: slti v0,s5,0xc */ c->r[2]=less(c->r[21],sx(UINT32_C(0x0000000c)));
/* 0025814c: beq v0,zero,0x00258240 */ {int taken=(c->r[2]==c->r[0]);/* delay 00258150 */ c->r[22]=c->r[21];if(taken){goto L_00258240;}}
/* 00258154: addu v0,s5,s7 */ c->r[2]=sx((uint32_t)c->r[21]+(uint32_t)c->r[23]);
/* 00258158: addiu s2,v0,0x40 */ c->r[18]=sx((uint32_t)c->r[2]+UINT32_C(0x00000040));
/* 0025815c: nop  */ (void)0;
L_00258160:;
/* 00258160: lb v0,0x0(s2) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00258164: bltz v0,0x00258228 */ {int taken=(neg(c->r[2]));/* delay 00258168 */ c->r[19]=sx((uint32_t)c->r[23]+(uint32_t)c->r[30]);if(taken){goto L_00258228;}}
/* 0025816c: lw v0,0x10(s4) */ c->r[2]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000010)));
/* 00258170: lb a1,0x0(s3) */ c->r[5]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[19]+UINT32_C(0x00000000)));
/* 00258174: move a0,s4 */ c->r[4]=c->r[20];
/* 00258178: sll a1,a1,0x7 */ c->r[5]=sx((uint32_t)c->r[5]<<7u);
/* 0025817c: jal 0x002469c0 */ c->r[31]=UINT64_C(0x00258184);/* delay 00258180 */ c->r[5]=sx((uint32_t)c->r[2]+(uint32_t)c->r[5]);nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitWorkPointer(A0,A1);nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 00258184: lb a1,0x0(s2) */ c->r[5]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 00258188: move s1,v0 */ c->r[17]=c->r[2];
/* 0025818c: lw v0,0x10(s4) */ c->r[2]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000010)));
/* 00258190: sll a1,a1,0x7 */ c->r[5]=sx((uint32_t)c->r[5]<<7u);
/* 00258194: move a0,s4 */ c->r[4]=c->r[20];
/* 00258198: jal 0x002469c0 */ c->r[31]=UINT64_C(0x002581a0);/* delay 0025819c */ c->r[5]=sx((uint32_t)c->r[2]+(uint32_t)c->r[5]);nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitWorkPointer(A0,A1);nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 002581a0: move a0,s1 */ c->r[4]=c->r[17];
/* 002581a4: move s0,v0 */ c->r[16]=c->r[2];
/* 002581a8: jal 0x00243ee0 */ c->r[31]=UINT64_C(0x002581b0);/* delay 002581ac */ c->r[5]=sx(UINT32_C(0x00000004));nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)datGetParam((datUnitWork_PS2 *)at((uint32_t)A0),(int32_t)(uint32_t)A1));nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 002581b0: move a0,s0 */ c->r[4]=c->r[16];
/* 002581b4: li a1,0x4 */ c->r[5]=sx(UINT32_C(0x00000004));
/* 002581b8: jal 0x00243ee0 */ c->r[31]=UINT64_C(0x002581c0);/* delay 002581bc */ c->r[17]=c->r[2];nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)datGetParam((datUnitWork_PS2 *)at((uint32_t)A0),(int32_t)(uint32_t)A1));nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 002581c0: move v1,v0 */ c->r[3]=c->r[2];
/* 002581c4: slt v0,s1,v1 */ c->r[2]=less(c->r[17],c->r[3]);
/* 002581c8: beq v0,zero,0x002581e8 */ {int taken=(c->r[2]==c->r[0]);/* delay 002581cc */ (void)0;if(taken){goto L_002581e8;}}
/* 002581d0: lbu v0,0x0(s2) */ c->r[2]=*at((uint32_t)c->r[18]+UINT32_C(0x00000000));
/* 002581d4: lb v1,0x0(s3) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[19]+UINT32_C(0x00000000)));
/* 002581d8: sb v0,0x0(s3) */ *at((uint32_t)c->r[19]+UINT32_C(0x00000000))=(uint8_t)c->r[2];
/* 002581dc: b 0x00258228 */ /* delay 002581e0 */ *at((uint32_t)c->r[18]+UINT32_C(0x00000000))=(uint8_t)c->r[3];goto L_00258228;
L_002581e8:;
/* 002581e8: bnel s1,v1,0x0025822c */ {int taken=(c->r[17]!=c->r[3]);if(taken){/* delay 002581ec */ c->r[22]=sx((uint32_t)c->r[22]+UINT32_C(0x00000001));goto L_0025822c;}}
/* 002581f0: lb a0,0x0(s2) */ c->r[4]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 002581f4: lb a2,0x0(s3) */ c->r[6]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[19]+UINT32_C(0x00000000)));
/* 002581f8: lw v0,0x10(s4) */ c->r[2]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000010)));
/* 002581fc: sll a0,a0,0x7 */ c->r[4]=sx((uint32_t)c->r[4]<<7u);
/* 00258200: sll v1,a2,0x7 */ c->r[3]=sx((uint32_t)c->r[6]<<7u);
/* 00258204: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00258208: addu a0,a0,v0 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[2]);
/* 0025820c: lh a1,0x2(v1) */ c->r[5]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[3]+UINT32_C(0x00000002)));
/* 00258210: lh v0,0x2(a0) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000002)));
/* 00258214: slt v0,v0,a1 */ c->r[2]=less(c->r[2],c->r[5]);
/* 00258218: beq v0,zero,0x00258228 */ {int taken=(c->r[2]==c->r[0]);/* delay 0025821c */ c->r[7]=*at((uint32_t)c->r[18]+UINT32_C(0x00000000));if(taken){goto L_00258228;}}
/* 00258220: sb a3,0x0(s3) */ *at((uint32_t)c->r[19]+UINT32_C(0x00000000))=(uint8_t)c->r[7];
/* 00258224: sb a2,0x0(s2) */ *at((uint32_t)c->r[18]+UINT32_C(0x00000000))=(uint8_t)c->r[6];
L_00258228:;
/* 00258228: addiu s6,s6,0x1 */ c->r[22]=sx((uint32_t)c->r[22]+UINT32_C(0x00000001));
L_0025822c:;
/* 0025822c: slti v0,s6,0xc */ c->r[2]=less(c->r[22],sx(UINT32_C(0x0000000c)));
/* 00258230: bne v0,zero,0x00258160 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00258234 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));if(taken){goto L_00258160;}}
/* 00258238: b 0x00258244 */ /* delay 0025823c */ c->r[16]=c->r[21];goto L_00258244;
L_00258240:;
/* 00258240: move s0,s5 */ c->r[16]=c->r[21];
L_00258244:;
/* 00258244: slti v0,s0,0xb */ c->r[2]=less(c->r[16],sx(UINT32_C(0x0000000b)));
/* 00258248: bne v0,zero,0x00258138 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025824c */ c->r[30]=sx((uint32_t)c->r[16]+UINT32_C(0x00000040));if(taken){goto L_00258138;}}
/* 00258250: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00258254:;
/* 00258254: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00258258: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0025825c: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00258260: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00258264: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 00258268: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0025826c: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 00258270: ld s8,0x40(sp) */ c->r[30]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 00258274: ld ra,0x48(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 00258278: jr ra */ /* delay 0025827c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}

static void body_00259180(BattleRosterValues *c){
/* 00259180: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00259184: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00259188: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0025918c: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00259190: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 00259194: jal 0x00244eb8 */ c->r[31]=UINT64_C(0x0025919c);/* delay 00259198 */ c->r[18]=c->r[4];nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)datCheckStockFull());nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 0025919c: bne v0,zero,0x0025924c */ {int taken=(c->r[2]!=c->r[0]);/* delay 002591a0 */ c->r[2]=c->r[0];if(taken){goto L_0025924c;}}
/* 002591a4: lhu a0,0x4(s2) */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 002591a8: move s1,zero */ c->r[17]=c->r[0];
/* 002591ac: jal 0x00244530 */ c->r[31]=UINT64_C(0x002591b4);/* delay 002591b0 */ c->r[16]=sx(UINT32_C(0x00000004));nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);c->r[2]=datSearchDevilStock(A0);nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 002591b4: lw a1,-0x5750(gp) */ c->r[5]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 002591b8: addiu v1,a1,0xe04 */ c->r[3]=sx((uint32_t)c->r[5]+UINT32_C(0x00000e04));
/* 002591bc: lw v0,0x0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 002591c0: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 002591c4: bnel v0,zero,0x002591d8 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002591c8 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));goto L_002591d8;}}
/* 002591cc: b 0x00259210 */ /* delay 002591d0 */ c->r[17]=c->r[3];goto L_00259210;
L_002591d8:;
/* 002591d8: sll v0,s0,0x4 */ c->r[2]=sx((uint32_t)c->r[16]<<4u);
/* 002591dc: slti v1,s0,0x10 */ c->r[3]=less(c->r[16],sx(UINT32_C(0x00000010)));
/* 002591e0: beq v1,zero,0x00259210 */ {int taken=(c->r[3]==c->r[0]);/* delay 002591e4 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[16]);if(taken){goto L_00259210;}}
/* 002591e8: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 002591ec: subu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[16]);
/* 002591f0: sll a0,v0,0x2 */ c->r[4]=sx((uint32_t)c->r[2]<<2u);
/* 002591f4: addu v1,a0,a1 */ c->r[3]=sx((uint32_t)c->r[4]+(uint32_t)c->r[5]);
/* 002591f8: lw v0,0xa54(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000a54)));
/* 002591fc: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 00259200: bnel v0,zero,0x002591d8 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00259204 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));goto L_002591d8;}}
/* 00259208: addu v0,a1,a0 */ c->r[2]=sx((uint32_t)c->r[5]+(uint32_t)c->r[4]);
/* 0025920c: addiu s1,v0,0xa54 */ c->r[17]=sx((uint32_t)c->r[2]+UINT32_C(0x00000a54));
L_00259210:;
/* 00259210: lhu a0,0x4(s2) */ c->r[4]=hword((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 00259214: jal 0x00244ef8 */ c->r[31]=UINT64_C(0x0025921c);/* delay 00259218 */ c->r[5]=c->r[17];nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);ps2UnitInitializeCompanion_00244EF8(A0,A1);nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 0025921c: move a0,s1 */ c->r[4]=c->r[17];
/* 00259220: jal 0x00216a18 */ c->r[31]=UINT64_C(0x00259228);/* delay 00259224 */ c->r[5]=c->r[0];nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CompendiumRecords_00216A18(A0,A1);nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 00259228: lw a0,-0x5750(gp) */ c->r[4]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 0025922c: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00259230: lw v1,0x1924(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00001924)));
/* 00259234: addu v1,v1,a0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[4]);
/* 00259238: sb s0,0x1914(v1) */ *at((uint32_t)c->r[3]+UINT32_C(0x00001914))=(uint8_t)c->r[16];
/* 0025923c: lw a0,-0x5750(gp) */ c->r[4]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00259240: lw v1,0x1924(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00001924)));
/* 00259244: addiu v1,v1,0x1 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 00259248: sw v1,0x1924(a0) */ sw((uint32_t)c->r[4]+UINT32_C(0x00001924),(uint32_t)c->r[3]);
L_0025924c:;
/* 0025924c: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00259250: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00259254: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00259258: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0025925c: jr ra */ /* delay 00259260 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_002594b0(BattleRosterValues *c){
/* 002594b0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002594b4: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002594b8: move s1,zero */ c->r[17]=c->r[0];
/* 002594bc: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 002594c0: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002594c4: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 002594c8: lw a2,0x8(a0) */ c->r[6]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000008)));
/* 002594cc: lw v0,0x0(a2) */ c->r[2]=sx(word((uint32_t)c->r[6]+UINT32_C(0x00000000)));
/* 002594d0: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 002594d4: beq v0,zero,0x0025950c */ {int taken=(c->r[2]==c->r[0]);/* delay 002594d8 */ c->r[18]=c->r[5];if(taken){goto L_0025950c;}}
/* 002594dc: move v1,a2 */ c->r[3]=c->r[6];
/* 002594e0: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
/* 002594e4: nop  */ (void)0;
L_002594e8:;
/* 002594e8: slti v0,s1,0xa */ c->r[2]=less(c->r[17],sx(UINT32_C(0x0000000a)));
/* 002594ec: beq v0,zero,0x0025950c */ {int taken=(c->r[2]==c->r[0]);/* delay 002594f0 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x000000ec));if(taken){goto L_0025950c;}}
/* 002594f4: lw v0,0x0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 002594f8: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 002594fc: nop  */ (void)0;
/* 00259500: nop  */ (void)0;
/* 00259504: bnel v0,zero,0x002594e8 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00259508 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_002594e8;}}
L_0025950c:;
/* 0025950c: li v1,0xa */ c->r[3]=sx(UINT32_C(0x0000000a));
/* 00259510: beq s1,v1,0x00259584 */ {int taken=(c->r[17]==c->r[3]);/* delay 00259514 */ c->r[2]=sx(UINT32_C(0xffffffff));if(taken){goto L_00259584;}}
/* 00259518: sll s0,s1,0x4 */ c->r[16]=sx((uint32_t)c->r[17]<<4u);
/* 0025951c: move a0,s2 */ c->r[4]=c->r[18];
/* 00259520: subu s0,s0,s1 */ c->r[16]=sx((uint32_t)c->r[16]-(uint32_t)c->r[17]);
/* 00259524: sll s0,s0,0x2 */ c->r[16]=sx((uint32_t)c->r[16]<<2u);
/* 00259528: subu s0,s0,s1 */ c->r[16]=sx((uint32_t)c->r[16]-(uint32_t)c->r[17]);
/* 0025952c: sll s0,s0,0x2 */ c->r[16]=sx((uint32_t)c->r[16]<<2u);
/* 00259530: addu s0,a2,s0 */ c->r[16]=sx((uint32_t)c->r[6]+(uint32_t)c->r[16]);
/* 00259534: jal 0x00244ef8 */ c->r[31]=UINT64_C(0x0025953c);/* delay 00259538 */ c->r[5]=c->r[16];nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);ps2UnitInitializeCompanion_00244EF8(A0,A1);nocturneBattleRosterSetStackPointer((uint32_t)c->r[29]);
/* 0025953c: sll v1,s2,0x4 */ c->r[3]=sx((uint32_t)c->r[18]<<4u);
/* 00259540: subu v1,v1,s2 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[18]);
/* 00259544: lw a0,0x0(s0) */ c->r[4]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00259548: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 0025954c: move v0,s1 */ c->r[2]=c->r[17];
/* 00259550: lui at,0x35 */ c->r[1]=sx(UINT32_C(0x00350000));
/* 00259554: addiu at,at,-0x6840 */ c->r[1]=sx((uint32_t)c->r[1]+UINT32_C(0xffff97c0));
/* 00259558: addu v1,at,v1 */ c->r[3]=sx((uint32_t)c->r[1]+(uint32_t)c->r[3]);
/* 0025955c: ori a0,a0,0x2 */ c->r[4]=c->r[4]|UINT64_C(0x2);
/* 00259560: lhu a1,0x8(v1) */ c->r[5]=hword((uint32_t)c->r[3]+UINT32_C(0x00000008));
/* 00259564: sw a0,0x0(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000000),(uint32_t)c->r[4]);
/* 00259568: sh a1,0x8(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000008),(uint16_t)c->r[5]);
/* 0025956c: lhu a0,0x6(v1) */ c->r[4]=hword((uint32_t)c->r[3]+UINT32_C(0x00000006));
/* 00259570: sh a0,0x6(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000006),(uint16_t)c->r[4]);
/* 00259574: lhu a1,0xc(v1) */ c->r[5]=hword((uint32_t)c->r[3]+UINT32_C(0x0000000c));
/* 00259578: sh a1,0xc(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000000c),(uint16_t)c->r[5]);
/* 0025957c: lhu a0,0xa(v1) */ c->r[4]=hword((uint32_t)c->r[3]+UINT32_C(0x0000000a));
/* 00259580: sh a0,0xa(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000000a),(uint16_t)c->r[4]);
L_00259584:;
/* 00259584: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00259588: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025958c: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00259590: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00259594: jr ra */ /* delay 00259598 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}
static BattleRosterValues begin(void){BattleRosterValues c={0};c.r[28]=UINT64_C(0x00554170);c.r[29]=nocturneBattleRosterStackPointer();return c;}
void ps2BattleRoster_002580E8(uint64_t p0){BattleRosterValues c=begin();c.r[4]=p0;body_002580e8(&c);nocturneBattleRosterSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2BattleRoster_00259180(uint64_t p0){BattleRosterValues c=begin();c.r[4]=p0;body_00259180(&c);nocturneBattleRosterSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2BattleRoster_002594B0(uint64_t p0,uint64_t p1){BattleRosterValues c=begin();c.r[4]=p0;c.r[5]=p1;body_002594b0(&c);nocturneBattleRosterSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
