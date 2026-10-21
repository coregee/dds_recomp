/* Complete original battle-order4/183 instructions. NativePC-qualified
 * scalar C preserves all branches/delays, original guest frames and real
 * process/sort calls. No synthesized Main pointer, sort result or guard. */
#include "battle_order.h"
#include "battle_work_access.h"
#include "battle_roster.h"
#include <string.h>
typedef struct BattleOrderValues {uint64_t r[32];} BattleOrderValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleOrderAddress(a);}
static uint16_t hword(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
#define A0 c->r[4]
#define A1 c->r[5]

static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}

static void body_00258048(BattleOrderValues *c);
static void body_00258280(BattleOrderValues *c);
static void body_002583d8(BattleOrderValues *c);
static void body_00258418(BattleOrderValues *c);

static void body_00258048(BattleOrderValues *c){
/* 00258048: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 0025804c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00258050: sd ra,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[31]);
/* 00258054: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0025805c);/* delay 00258058 */ c->r[16]=c->r[4];nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);
/* 0025805c: move a1,v0 */ c->r[5]=c->r[2];
/* 00258060: sll v0,s0,0x4 */ c->r[2]=sx((uint32_t)c->r[16]<<4u);
/* 00258064: lw v1,0x0(a1) */ c->r[3]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 00258068: subu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[16]);
/* 0025806c: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 00258070: addu a0,v0,v1 */ c->r[4]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00258074: lw v1,0x78(a0) */ c->r[3]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000078)));
/* 00258078: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 0025807c: beq v0,zero,0x002580d4 */ {int taken=(c->r[2]==c->r[0]);/* delay 00258080 */ c->r[2]=c->r[3]&UINT64_C(0x40);if(taken){goto L_002580d4;}}
/* 00258084: beq v0,zero,0x002580d8 */ {int taken=(c->r[2]==c->r[0]);/* delay 00258088 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_002580d8;}}
/* 0025808c: lb v0,0x54(a1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[5]+UINT32_C(0x00000054)));
/* 00258090: lh a2,0x90(a0) */ c->r[6]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000090)));
/* 00258094: addiu a0,v0,0x1 */ c->r[4]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));
/* 00258098: addu v1,a0,a1 */ c->r[3]=sx((uint32_t)c->r[4]+(uint32_t)c->r[5]);
/* 0025809c: move a1,a0 */ c->r[5]=c->r[4];
/* 002580a0: addiu v1,v1,0x48 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000048));
/* 002580a4: nop  */ (void)0;
L_002580a8:;
/* 002580a8: slti v0,a1,0xc */ c->r[2]=less(c->r[5],sx(UINT32_C(0x0000000c)));
/* 002580ac: beq v0,zero,0x002580d4 */ {int taken=(c->r[2]==c->r[0]);/* delay 002580b0 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));if(taken){goto L_002580d4;}}
/* 002580b4: lb v0,0x0(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 002580b8: nop  */ (void)0;
/* 002580bc: nop  */ (void)0;
/* 002580c0: nop  */ (void)0;
/* 002580c4: bgezl v0,0x002580a8 */ {int taken=(!neg(c->r[2]));if(taken){/* delay 002580c8 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));goto L_002580a8;}}
/* 002580cc: jal 0x002580e8 */ c->r[31]=UINT64_C(0x002580d4);/* delay 002580d0 */ *at((uint32_t)c->r[3]+UINT32_C(0x00000000))=(uint8_t)c->r[6];nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);ps2BattleRoster_002580E8(A0);nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);
L_002580d4:;
/* 002580d4: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_002580d8:;
/* 002580d8: ld ra,0x8(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002580dc: jr ra */ /* delay 002580e0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));return;
}

static void body_00258280(BattleOrderValues *c){
/* 00258280: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00258284: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00258288: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0025828c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00258290: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 00258294: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0025829c);/* delay 00258298 */ c->r[18]=c->r[4];nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);
/* 0025829c: move s0,v0 */ c->r[16]=c->r[2];
/* 002582a0: li v1,-0x1 */ c->r[3]=sx(UINT32_C(0xffffffff));
/* 002582a4: addiu s1,s0,0x8 */ c->r[17]=sx((uint32_t)c->r[16]+UINT32_C(0x00000008));
/* 002582a8: addiu v0,s0,0x53 */ c->r[2]=sx((uint32_t)c->r[16]+UINT32_C(0x00000053));
/* 002582ac: li a1,0xb */ c->r[5]=sx(UINT32_C(0x0000000b));
L_002582b0:;
/* 002582b0: addiu a1,a1,-0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0xffffffff));
/* 002582b4: sb v1,0x0(v0) */ *at((uint32_t)c->r[2]+UINT32_C(0x00000000))=(uint8_t)c->r[3];
/* 002582b8: nop  */ (void)0;
/* 002582bc: nop  */ (void)0;
/* 002582c0: nop  */ (void)0;
/* 002582c4: bgez a1,0x002582b0 */ {int taken=(!neg(c->r[5]));/* delay 002582c8 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffffff));if(taken){goto L_002582b0;}}
/* 002582cc: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
/* 002582d0: move a3,zero */ c->r[7]=c->r[0];
/* 002582d4: bne s2,zero,0x00258330 */ {int taken=(c->r[18]!=c->r[0]);/* delay 002582d8 */ *at((uint32_t)c->r[16]+UINT32_C(0x00000054))=(uint8_t)c->r[2];if(taken){goto L_00258330;}}
/* 002582dc: move a1,zero */ c->r[5]=c->r[0];
/* 002582e0: addiu a2,s1,0x40 */ c->r[6]=sx((uint32_t)c->r[17]+UINT32_C(0x00000040));
/* 002582e4: lw v1,0x10(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000010)));
L_002582e8:;
/* 002582e8: sll v0,a1,0x7 */ c->r[2]=sx((uint32_t)c->r[5]<<7u);
/* 002582ec: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 002582f0: lhu a0,0x0(v0) */ c->r[4]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 002582f4: andi v1,a0,0x1 */ c->r[3]=c->r[4]&UINT64_C(0x1);
/* 002582f8: andi v1,v1,0xffff */ c->r[3]=c->r[3]&UINT64_C(0xffff);
/* 002582fc: beq v1,zero,0x00258318 */ {int taken=(c->r[3]==c->r[0]);/* delay 00258300 */ c->r[4]=c->r[4]&UINT64_C(0x20);if(taken){goto L_00258318;}}
/* 00258304: bnel a0,zero,0x0025831c */ {int taken=(c->r[4]!=c->r[0]);if(taken){/* delay 00258308 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));goto L_0025831c;}}
/* 0025830c: sb a1,0x0(a2) */ *at((uint32_t)c->r[6]+UINT32_C(0x00000000))=(uint8_t)c->r[5];
/* 00258310: addiu a2,a2,0x1 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 00258314: addiu a3,a3,0x1 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0x00000001));
L_00258318:;
/* 00258318: addiu a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));
L_0025831c:;
/* 0025831c: slti v0,a1,0x4 */ c->r[2]=less(c->r[5],sx(UINT32_C(0x00000004)));
/* 00258320: bnel v0,zero,0x002582e8 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00258324 */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000010)));goto L_002582e8;}}
/* 00258328: b 0x00258380 */ /* delay 0025832c */ (void)0;goto L_00258380;
L_00258330:;
/* 00258330: addu v0,a3,s1 */ c->r[2]=sx((uint32_t)c->r[7]+(uint32_t)c->r[17]);
/* 00258334: li a1,0x4 */ c->r[5]=sx(UINT32_C(0x00000004));
/* 00258338: addiu a2,v0,0x40 */ c->r[6]=sx((uint32_t)c->r[2]+UINT32_C(0x00000040));
/* 0025833c: lw v1,0x10(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000010)));
L_00258340:;
/* 00258340: sll v0,a1,0x7 */ c->r[2]=sx((uint32_t)c->r[5]<<7u);
/* 00258344: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00258348: lhu a0,0x0(v0) */ c->r[4]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 0025834c: andi v1,a0,0x1 */ c->r[3]=c->r[4]&UINT64_C(0x1);
/* 00258350: andi v1,v1,0xffff */ c->r[3]=c->r[3]&UINT64_C(0xffff);
/* 00258354: beq v1,zero,0x00258370 */ {int taken=(c->r[3]==c->r[0]);/* delay 00258358 */ c->r[4]=c->r[4]&UINT64_C(0x20);if(taken){goto L_00258370;}}
/* 0025835c: bnel a0,zero,0x00258374 */ {int taken=(c->r[4]!=c->r[0]);if(taken){/* delay 00258360 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));goto L_00258374;}}
/* 00258364: sb a1,0x0(a2) */ *at((uint32_t)c->r[6]+UINT32_C(0x00000000))=(uint8_t)c->r[5];
/* 00258368: addiu a2,a2,0x1 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 0025836c: addiu a3,a3,0x1 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0x00000001));
L_00258370:;
/* 00258370: addiu a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000001));
L_00258374:;
/* 00258374: slti v0,a1,0xe */ c->r[2]=less(c->r[5],sx(UINT32_C(0x0000000e)));
/* 00258378: bnel v0,zero,0x00258340 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0025837c */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000010)));goto L_00258340;}}
L_00258380:;
/* 00258380: blez a3,0x00258390 */ {int taken=((neg(c->r[7])||!c->r[7]));/* delay 00258384 */ c->r[3]=sx(UINT32_C(0xffffffff));if(taken){goto L_00258390;}}
/* 00258388: b 0x002583a0 */ /* delay 0025838c */ *at((uint32_t)c->r[16]+UINT32_C(0x00000054))=(uint8_t)c->r[0];goto L_002583a0;
L_00258390:;
/* 00258390: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
/* 00258394: sh v0,0x1c(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000001c),(uint16_t)c->r[2]);
/* 00258398: b 0x002583c0 */ /* delay 0025839c */ *at((uint32_t)c->r[16]+UINT32_C(0x00000054))=(uint8_t)c->r[3];goto L_002583c0;
L_002583a0:;
/* 002583a0: jal 0x002580e8 */ c->r[31]=UINT64_C(0x002583a8);/* delay 002583a4 */ c->r[4]=c->r[0];nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);ps2BattleRoster_002580E8(A0);nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);
/* 002583a8: lb v0,0x54(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000054)));
/* 002583ac: addu v0,v0,s1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[17]);
/* 002583b0: lbu v1,0x40(v0) */ c->r[3]=*at((uint32_t)c->r[2]+UINT32_C(0x00000040));
/* 002583b4: sll v1,v1,0x18 */ c->r[3]=sx((uint32_t)c->r[3]<<24u);
/* 002583b8: sra v1,v1,0x18 */ c->r[3]=sar((uint32_t)c->r[3],24u);
/* 002583bc: sh v1,0x1c(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000001c),(uint16_t)c->r[3]);
L_002583c0:;
/* 002583c0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002583c4: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002583c8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002583cc: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002583d0: jr ra */ /* delay 002583d4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_002583d8(BattleOrderValues *c){
/* 002583d8: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 002583dc: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 002583e0: jal 0x002469a0 */ c->r[31]=UINT64_C(0x002583e8);/* delay 002583e4 */ (void)0;nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);
/* 002583e8: lw v1,0x60(v0) */ c->r[3]=sx(word((uint32_t)c->r[2]+UINT32_C(0x00000060)));
/* 002583ec: andi v1,v1,0x8 */ c->r[3]=c->r[3]&UINT64_C(0x8);
/* 002583f0: bne v1,zero,0x00258408 */ {int taken=(c->r[3]!=c->r[0]);/* delay 002583f4 */ c->r[4]=c->r[0];if(taken){goto L_00258408;}}
/* 002583f8: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002583fc: j 0x00258280 */ /* delay 00258400 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_00258280(c);return;
L_00258408:;
/* 00258408: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0025840c: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 00258410: j 0x00258280 */ /* delay 00258414 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_00258280(c);return;
}

static void body_00258418(BattleOrderValues *c){
/* 00258418: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0025841c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00258420: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00258424: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 00258428: jal 0x002469a0 */ c->r[31]=UINT64_C(0x00258430);/* delay 0025842c */ (void)0;nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleOrderSetStackPointer((uint32_t)c->r[29]);
/* 00258430: move s0,v0 */ c->r[16]=c->r[2];
/* 00258434: lb v0,0x54(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000054)));
/* 00258438: addiu s1,s0,0x8 */ c->r[17]=sx((uint32_t)c->r[16]+UINT32_C(0x00000008));
/* 0025843c: bgez v0,0x00258468 */ {int taken=(!neg(c->r[2]));/* delay 00258440 */ c->r[4]=c->r[2];if(taken){goto L_00258468;}}
/* 00258444: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00258448: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0025844c: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00258450: j 0x002583d8 */ /* delay 00258454 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));body_002583d8(c);return;
L_00258458:;
/* 00258458: jal 0x002583d8 */ c->r[31]=UINT64_C(0x00258460);/* delay 0025845c */ (void)0;body_002583d8(c);
/* 00258460: b 0x0025849c */ /* delay 00258464 */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000054)));goto L_0025849c;
L_00258468:;
/* 00258468: addiu v1,a0,0x1 */ c->r[3]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));
L_0025846c:;
/* 0025846c: sll v0,v1,0x18 */ c->r[2]=sx((uint32_t)c->r[3]<<24u);
/* 00258470: move a0,v1 */ c->r[4]=c->r[3];
/* 00258474: sra v0,v0,0x18 */ c->r[2]=sar((uint32_t)c->r[2],24u);
/* 00258478: sb v1,0x54(s0) */ *at((uint32_t)c->r[16]+UINT32_C(0x00000054))=(uint8_t)c->r[3];
/* 0025847c: addu v1,v0,s1 */ c->r[3]=sx((uint32_t)c->r[2]+(uint32_t)c->r[17]);
/* 00258480: slti v0,v0,0xc */ c->r[2]=less(c->r[2],sx(UINT32_C(0x0000000c)));
/* 00258484: beq v0,zero,0x00258458 */ {int taken=(c->r[2]==c->r[0]);/* delay 00258488 */ (void)0;if(taken){goto L_00258458;}}
/* 0025848c: lb v0,0x40(v1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[3]+UINT32_C(0x00000040)));
/* 00258490: bltz v0,0x0025846c */ {int taken=(neg(c->r[2]));/* delay 00258494 */ c->r[3]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));if(taken){goto L_0025846c;}}
/* 00258498: lb v0,0x54(s0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[16]+UINT32_C(0x00000054)));
L_0025849c:;
/* 0025849c: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002584a0: addu v0,v0,s1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[17]);
/* 002584a4: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002584a8: lbu v1,0x40(v0) */ c->r[3]=*at((uint32_t)c->r[2]+UINT32_C(0x00000040));
/* 002584ac: sll v1,v1,0x18 */ c->r[3]=sx((uint32_t)c->r[3]<<24u);
/* 002584b0: sra v1,v1,0x18 */ c->r[3]=sar((uint32_t)c->r[3],24u);
/* 002584b4: sh v1,0x1c(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000001c),(uint16_t)c->r[3]);
/* 002584b8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002584bc: jr ra */ /* delay 002584c0 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}
static BattleOrderValues begin(void){BattleOrderValues c={0};c.r[28]=UINT64_C(0x00554170);c.r[29]=nocturneBattleOrderStackPointer();return c;}
void ps2BattleOrder_00258048(uint64_t p0){BattleOrderValues c=begin();c.r[4]=p0;body_00258048(&c);nocturneBattleOrderSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleOrder_00258280(uint64_t p0){BattleOrderValues c=begin();c.r[4]=p0;body_00258280(&c);nocturneBattleOrderSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleOrder_002583D8(void){BattleOrderValues c=begin();body_002583d8(&c);nocturneBattleOrderSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleOrder_00258418(void){BattleOrderValues c=begin();body_00258418(&c);nocturneBattleOrderSetStackPointer((uint32_t)c.r[29]);}
