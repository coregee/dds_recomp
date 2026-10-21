/* Whole8 compendium roots +2 callbacks +existing66-op variant,578 instructions.
 * Fixed native-PC semantic values, real typed prerequisites and guest-backed
 * local objects; no shared volatile/private-frame or incidental VOID result claim. */
#include "compendium_records.h"
#include "libc_printf.h"
#include "nocturne.h"
#include "ps2_memory.h"
#include "ps2_qsort.h"
#include "script_construction.h"

#include <string.h>
typedef struct CompendiumValues {uint64_t r[32],lo,hi;} CompendiumValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}
static uint8_t *at(uint32_t address){return (uint8_t *)nocturneResolveCompendiumRecordsAddress(address);}
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
#define A0 c->r[4]
#define A1 c->r[5]
#define A2 c->r[6]
#define A3 c->r[7]

static void body_00216910(CompendiumValues *c);
static void body_00219fc0(CompendiumValues *c);
static void body_00216c08(CompendiumValues *c);
static void body_00219400(CompendiumValues *c);
static void body_002197b0(CompendiumValues *c);
static void body_00219ba0(CompendiumValues *c);
static void body_00219bf0(CompendiumValues *c);
static void body_00219dc0(CompendiumValues *c);
static void body_00219c40(CompendiumValues *c);
static void body_00219d00(CompendiumValues *c);
static void body_00216a18(CompendiumValues *c);

static void body_00216910(CompendiumValues *c){
/* 00216910: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 00216914: lw v0,-0x5750(gp) */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00216918: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0021691c: move s0,a0 */ c->r[16]=c->r[4];
/* 00216920: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00216924: lui s1,0x1 */ c->r[17]=sx(UINT32_C(0x00010000));
/* 00216928: ori s1,s1,0x1e80 */ c->r[17]=c->r[17]|UINT64_C(0x1e80);
/* 0021692c: addu s1,s1,v0 */ c->r[17]=sx((uint32_t)c->r[17]+(uint32_t)c->r[2]);
/* 00216930: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00216934: move s2,a1 */ c->r[18]=c->r[5];
/* 00216938: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0021693c: lui s3,0x1 */ c->r[19]=sx(UINT32_C(0x00010000));
/* 00216940: ori s3,s3,0x1e90 */ c->r[19]=c->r[19]|UINT64_C(0x1e90);
/* 00216944: addu s3,s3,v0 */ c->r[19]=sx((uint32_t)c->r[19]+(uint32_t)c->r[2]);
/* 00216948: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 0021694c: jal 0x00216b20 */ c->r[31]=UINT64_C(0x00216954);/* delay 00216950 */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)fclEncycSearch((int32_t)(uint32_t)A0));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216954: move a1,s0 */ c->r[5]=c->r[16];
/* 00216958: move v1,v0 */ c->r[3]=c->r[2];
/* 0021695c: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
/* 00216960: bgez v1,0x002169a8 */ {int taken=(!neg(c->r[3]));/* delay 00216964 */ c->r[16]=sx(UINT32_C(0x00000001));if(taken){goto L_002169a8;}}
/* 00216968: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 0021696c: slti v0,a0,0xb8 */ c->r[2]=less(c->r[4],sx(UINT32_C(0x000000b8)));
/* 00216970: bnel v0,zero,0x00216998 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00216974 */ c->r[3]=c->r[4];goto L_00216998;}}
/* 00216978: lui s0,0x54 */ c->r[16]=sx(UINT32_C(0x00540000));
/* 0021697c: addiu s0,s0,-0x2818 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffd7e8));
/* 00216980: jal 0x002d4748 */ c->r[31]=UINT64_C(0x00216988);/* delay 00216984 */ c->r[4]=c->r[16];nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2LibcPrintf(A0);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216988: jal 0x001097e8 */ c->r[31]=UINT64_C(0x00216990);/* delay 0021698c */ c->r[4]=c->r[16];nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);ps2ScriptDiagnosticDisabled(A0);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216990: b 0x002169fc */ /* delay 00216994 */ c->r[2]=sx(UINT32_C(0xffffffff));goto L_002169fc;
L_00216998:;
/* 00216998: move s0,zero */ c->r[16]=c->r[0];
/* 0021699c: addiu v0,v1,0x1 */ c->r[2]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 002169a0: b 0x002169b0 */ /* delay 002169a4 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000000),(uint32_t)c->r[2]);goto L_002169b0;
L_002169a8:;
/* 002169a8: beql s2,zero,0x00216a00 */ {int taken=(c->r[18]==c->r[0]);if(taken){/* delay 002169ac */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00216a00;}}
L_002169b0:;
/* 002169b0: sll a0,v1,0x1 */ c->r[4]=sx((uint32_t)c->r[3]<<1u);
/* 002169b4: addu a0,a0,v1 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[3]);
/* 002169b8: sll a0,a0,0x2 */ c->r[4]=sx((uint32_t)c->r[4]<<2u);
/* 002169bc: subu a0,a0,v1 */ c->r[4]=sx((uint32_t)c->r[4]-(uint32_t)c->r[3]);
/* 002169c0: sll a0,a0,0x4 */ c->r[4]=sx((uint32_t)c->r[4]<<4u);
/* 002169c4: jal 0x00219fc0 */ c->r[31]=UINT64_C(0x002169cc);/* delay 002169c8 */ c->r[4]=sx((uint32_t)c->r[19]+(uint32_t)c->r[4]);body_00219fc0(c);
/* 002169cc: jal 0x00216b90 */ c->r[31]=UINT64_C(0x002169d4);/* delay 002169d0 */ (void)0;nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)fclEncycGetRatio2());nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 002169d4: slti v0,v0,0x64 */ c->r[2]=less(c->r[2],sx(UINT32_C(0x00000064)));
/* 002169d8: bne v0,zero,0x002169f0 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002169dc */ c->r[4]=sx(UINT32_C(0x00000913));if(taken){goto L_002169f0;}}
/* 002169e0: jal 0x001e0ed0 */ c->r[31]=UINT64_C(0x002169e8);/* delay 002169e4 */ (void)0;nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);evtBitOn((int32_t)(uint32_t)A0);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 002169e8: b 0x002169fc */ /* delay 002169ec */ c->r[2]=c->r[16];goto L_002169fc;
L_002169f0:;
/* 002169f0: jal 0x001e0f10 */ c->r[31]=UINT64_C(0x002169f8);/* delay 002169f4 */ c->r[4]=sx(UINT32_C(0x00000913));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);evtBitOff((int32_t)(uint32_t)A0);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 002169f8: move v0,s0 */ c->r[2]=c->r[16];
L_002169fc:;
/* 002169fc: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00216a00:;
/* 00216a00: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00216a04: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00216a08: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00216a0c: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00216a10: jr ra */ /* delay 00216a14 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_00219fc0(CompendiumValues *c){
/* 00219fc0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00219fc4: li a2,0xb0 */ c->r[6]=sx(UINT32_C(0x000000b0));
/* 00219fc8: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00219fcc: move s0,a0 */ c->r[16]=c->r[4];
/* 00219fd0: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00219fd4: move s1,a1 */ c->r[17]=c->r[5];
/* 00219fd8: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 00219fdc: jal 0x002d4558 */ c->r[31]=UINT64_C(0x00219fe4);/* delay 00219fe0 */ c->r[5]=c->r[0];nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);(void)ps2Memset(at((uint32_t)A0),(int32_t)(uint32_t)A1,(uint32_t)A2);c->r[2]=A0;nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00219fe4: or v0,s1,s0 */ c->r[2]=c->r[17]|c->r[16];
/* 00219fe8: andi v0,v0,0x7 */ c->r[2]=c->r[2]&UINT64_C(0x7);
/* 00219fec: beq v0,zero,0x0021a050 */ {int taken=(c->r[2]==c->r[0]);/* delay 00219ff0 */ c->r[2]=sx((uint32_t)c->r[17]+UINT32_C(0x000000a0));if(taken){goto L_0021a050;}}
L_00219ff4:;
/* 00219ff4: ldl v1,0x7(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000007),1);
/* 00219ff8: ldr v1,0x0(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000000),0);
/* 00219ffc: ldl a0,0xf(s1) */ c->r[4]=partial_load(c->r[4],(uint32_t)c->r[17]+UINT32_C(0x0000000f),1);
/* 0021a000: ldr a0,0x8(s1) */ c->r[4]=partial_load(c->r[4],(uint32_t)c->r[17]+UINT32_C(0x00000008),0);
/* 0021a004: ldl a1,0x17(s1) */ c->r[5]=partial_load(c->r[5],(uint32_t)c->r[17]+UINT32_C(0x00000017),1);
/* 0021a008: ldr a1,0x10(s1) */ c->r[5]=partial_load(c->r[5],(uint32_t)c->r[17]+UINT32_C(0x00000010),0);
/* 0021a00c: ldl a2,0x1f(s1) */ c->r[6]=partial_load(c->r[6],(uint32_t)c->r[17]+UINT32_C(0x0000001f),1);
/* 0021a010: ldr a2,0x18(s1) */ c->r[6]=partial_load(c->r[6],(uint32_t)c->r[17]+UINT32_C(0x00000018),0);
/* 0021a014: sdl v1,0x7(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x00000007),1);
/* 0021a018: sdr v1,0x0(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x00000000),0);
/* 0021a01c: sdl a0,0xf(s0) */ partial_store(c->r[4],(uint32_t)c->r[16]+UINT32_C(0x0000000f),1);
/* 0021a020: sdr a0,0x8(s0) */ partial_store(c->r[4],(uint32_t)c->r[16]+UINT32_C(0x00000008),0);
/* 0021a024: sdl a1,0x17(s0) */ partial_store(c->r[5],(uint32_t)c->r[16]+UINT32_C(0x00000017),1);
/* 0021a028: sdr a1,0x10(s0) */ partial_store(c->r[5],(uint32_t)c->r[16]+UINT32_C(0x00000010),0);
/* 0021a02c: sdl a2,0x1f(s0) */ partial_store(c->r[6],(uint32_t)c->r[16]+UINT32_C(0x0000001f),1);
/* 0021a030: sdr a2,0x18(s0) */ partial_store(c->r[6],(uint32_t)c->r[16]+UINT32_C(0x00000018),0);
/* 0021a034: addiu s1,s1,0x20 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000020));
/* 0021a038: nop  */ (void)0;
/* 0021a03c: nop  */ (void)0;
/* 0021a040: bne s1,v0,0x00219ff4 */ {int taken=(c->r[17]!=c->r[2]);/* delay 0021a044 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000020));if(taken){goto L_00219ff4;}}
/* 0021a048: b 0x0021a084 */ /* delay 0021a04c */ (void)0;goto L_0021a084;
L_0021a050:;
/* 0021a050: ld v1,0x0(s1) */ c->r[3]=quad((uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0021a054: ld a0,0x8(s1) */ c->r[4]=quad((uint32_t)c->r[17]+UINT32_C(0x00000008));
/* 0021a058: ld a1,0x10(s1) */ c->r[5]=quad((uint32_t)c->r[17]+UINT32_C(0x00000010));
/* 0021a05c: ld a2,0x18(s1) */ c->r[6]=quad((uint32_t)c->r[17]+UINT32_C(0x00000018));
/* 0021a060: sd v1,0x0(s0) */ sd((uint32_t)c->r[16]+UINT32_C(0x00000000),c->r[3]);
/* 0021a064: sd a0,0x8(s0) */ sd((uint32_t)c->r[16]+UINT32_C(0x00000008),c->r[4]);
/* 0021a068: sd a1,0x10(s0) */ sd((uint32_t)c->r[16]+UINT32_C(0x00000010),c->r[5]);
/* 0021a06c: sd a2,0x18(s0) */ sd((uint32_t)c->r[16]+UINT32_C(0x00000018),c->r[6]);
/* 0021a070: addiu s1,s1,0x20 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000020));
/* 0021a074: nop  */ (void)0;
/* 0021a078: nop  */ (void)0;
/* 0021a07c: bne s1,v0,0x0021a050 */ {int taken=(c->r[17]!=c->r[2]);/* delay 0021a080 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000020));if(taken){goto L_0021a050;}}
L_0021a084:;
/* 0021a084: ldl v0,0x7(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000007),1);
/* 0021a088: ldr v0,0x0(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000000),0);
/* 0021a08c: ldl v1,0xf(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x0000000f),1);
/* 0021a090: ldr v1,0x8(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000008),0);
/* 0021a094: sdl v0,0x7(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000007),1);
/* 0021a098: sdr v0,0x0(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000000),0);
/* 0021a09c: sdl v1,0xf(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x0000000f),1);
/* 0021a0a0: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0021a0a4: sdr v1,0x8(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x00000008),0);
/* 0021a0a8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0021a0ac: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0021a0b0: jr ra */ /* delay 0021a0b4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00216c08(CompendiumValues *c){
/* 00216c08: addiu sp,sp,-0x110 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffef0));
/* 00216c0c: lw a1,-0x5750(gp) */ c->r[5]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00216c10: sd s0,0xf0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000f0),c->r[16]);
/* 00216c14: sd s1,0xf8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000f8),c->r[17]);
/* 00216c18: sd ra,0x100(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000100),c->r[31]);
/* 00216c1c: lw s1,0x1924(a1) */ c->r[17]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00001924)));
/* 00216c20: blez s1,0x00216d58 */ {int taken=((neg(c->r[17])||!c->r[17]));/* delay 00216c24 */ c->r[16]=c->r[0];if(taken){goto L_00216d58;}}
/* 00216c28: b 0x00216c38 */ /* delay 00216c2c */ c->r[3]=sx((uint32_t)c->r[16]+(uint32_t)c->r[5]);goto L_00216c38;
L_00216c30:;
/* 00216c30: addu v1,s0,a1 */ c->r[3]=sx((uint32_t)c->r[16]+(uint32_t)c->r[5]);
/* 00216c34: nop  */ (void)0;
L_00216c38:;
/* 00216c38: lbu a0,0x1914(v1) */ c->r[4]=*at((uint32_t)c->r[3]+UINT32_C(0x00001914));
/* 00216c3c: sll v0,a0,0x4 */ c->r[2]=sx((uint32_t)c->r[4]<<4u);
/* 00216c40: subu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[4]);
/* 00216c44: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00216c48: subu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[4]);
/* 00216c4c: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00216c50: addu a1,a1,v0 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[2]);
/* 00216c54: addiu v1,a1,0xa54 */ c->r[3]=sx((uint32_t)c->r[5]+UINT32_C(0x00000a54));
/* 00216c58: lw v0,0x0(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000000)));
/* 00216c5c: andi v0,v0,0x4 */ c->r[2]=c->r[2]&UINT64_C(0x4);
/* 00216c60: bnel v0,zero,0x00216d4c */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00216c64 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));goto L_00216d4c;}}
/* 00216c68: andi v0,v1,0x7 */ c->r[2]=c->r[3]&UINT64_C(0x7);
/* 00216c6c: beq v0,zero,0x00216cd8 */ {int taken=(c->r[2]==c->r[0]);/* delay 00216c70 */ c->r[4]=c->r[29];if(taken){goto L_00216cd8;}}
/* 00216c74: addiu v0,a1,0xb34 */ c->r[2]=sx((uint32_t)c->r[5]+UINT32_C(0x00000b34));
L_00216c78:;
/* 00216c78: ldl a1,0x7(v1) */ c->r[5]=partial_load(c->r[5],(uint32_t)c->r[3]+UINT32_C(0x00000007),1);
/* 00216c7c: ldr a1,0x0(v1) */ c->r[5]=partial_load(c->r[5],(uint32_t)c->r[3]+UINT32_C(0x00000000),0);
/* 00216c80: ldl a2,0xf(v1) */ c->r[6]=partial_load(c->r[6],(uint32_t)c->r[3]+UINT32_C(0x0000000f),1);
/* 00216c84: ldr a2,0x8(v1) */ c->r[6]=partial_load(c->r[6],(uint32_t)c->r[3]+UINT32_C(0x00000008),0);
/* 00216c88: ldl a3,0x17(v1) */ c->r[7]=partial_load(c->r[7],(uint32_t)c->r[3]+UINT32_C(0x00000017),1);
/* 00216c8c: ldr a3,0x10(v1) */ c->r[7]=partial_load(c->r[7],(uint32_t)c->r[3]+UINT32_C(0x00000010),0);
/* 00216c90: ldl t0,0x1f(v1) */ c->r[8]=partial_load(c->r[8],(uint32_t)c->r[3]+UINT32_C(0x0000001f),1);
/* 00216c94: ldr t0,0x18(v1) */ c->r[8]=partial_load(c->r[8],(uint32_t)c->r[3]+UINT32_C(0x00000018),0);
/* 00216c98: sdl a1,0x7(a0) */ partial_store(c->r[5],(uint32_t)c->r[4]+UINT32_C(0x00000007),1);
/* 00216c9c: sdr a1,0x0(a0) */ partial_store(c->r[5],(uint32_t)c->r[4]+UINT32_C(0x00000000),0);
/* 00216ca0: sdl a2,0xf(a0) */ partial_store(c->r[6],(uint32_t)c->r[4]+UINT32_C(0x0000000f),1);
/* 00216ca4: sdr a2,0x8(a0) */ partial_store(c->r[6],(uint32_t)c->r[4]+UINT32_C(0x00000008),0);
/* 00216ca8: sdl a3,0x17(a0) */ partial_store(c->r[7],(uint32_t)c->r[4]+UINT32_C(0x00000017),1);
/* 00216cac: sdr a3,0x10(a0) */ partial_store(c->r[7],(uint32_t)c->r[4]+UINT32_C(0x00000010),0);
/* 00216cb0: sdl t0,0x1f(a0) */ partial_store(c->r[8],(uint32_t)c->r[4]+UINT32_C(0x0000001f),1);
/* 00216cb4: sdr t0,0x18(a0) */ partial_store(c->r[8],(uint32_t)c->r[4]+UINT32_C(0x00000018),0);
/* 00216cb8: addiu v1,v1,0x20 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000020));
/* 00216cbc: nop  */ (void)0;
/* 00216cc0: nop  */ (void)0;
/* 00216cc4: bne v1,v0,0x00216c78 */ {int taken=(c->r[3]!=c->r[2]);/* delay 00216cc8 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000020));if(taken){goto L_00216c78;}}
/* 00216ccc: b 0x00216d10 */ /* delay 00216cd0 */ (void)0;goto L_00216d10;
L_00216cd8:;
/* 00216cd8: addiu v0,a1,0xb34 */ c->r[2]=sx((uint32_t)c->r[5]+UINT32_C(0x00000b34));
L_00216cdc:;
/* 00216cdc: ld a1,0x0(v1) */ c->r[5]=quad((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 00216ce0: ld a2,0x8(v1) */ c->r[6]=quad((uint32_t)c->r[3]+UINT32_C(0x00000008));
/* 00216ce4: ld a3,0x10(v1) */ c->r[7]=quad((uint32_t)c->r[3]+UINT32_C(0x00000010));
/* 00216ce8: ld t0,0x18(v1) */ c->r[8]=quad((uint32_t)c->r[3]+UINT32_C(0x00000018));
/* 00216cec: sd a1,0x0(a0) */ sd((uint32_t)c->r[4]+UINT32_C(0x00000000),c->r[5]);
/* 00216cf0: sd a2,0x8(a0) */ sd((uint32_t)c->r[4]+UINT32_C(0x00000008),c->r[6]);
/* 00216cf4: sd a3,0x10(a0) */ sd((uint32_t)c->r[4]+UINT32_C(0x00000010),c->r[7]);
/* 00216cf8: sd t0,0x18(a0) */ sd((uint32_t)c->r[4]+UINT32_C(0x00000018),c->r[8]);
/* 00216cfc: addiu v1,v1,0x20 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000020));
/* 00216d00: nop  */ (void)0;
/* 00216d04: nop  */ (void)0;
/* 00216d08: bne v1,v0,0x00216cdc */ {int taken=(c->r[3]!=c->r[2]);/* delay 00216d0c */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000020));if(taken){goto L_00216cdc;}}
L_00216d10:;
/* 00216d10: ldl v0,0x7(v1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[3]+UINT32_C(0x00000007),1);
/* 00216d14: ldr v0,0x0(v1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[3]+UINT32_C(0x00000000),0);
/* 00216d18: lw a1,0x8(v1) */ c->r[5]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000008)));
/* 00216d1c: sdl v0,0x7(a0) */ partial_store(c->r[2],(uint32_t)c->r[4]+UINT32_C(0x00000007),1);
/* 00216d20: sdr v0,0x0(a0) */ partial_store(c->r[2],(uint32_t)c->r[4]+UINT32_C(0x00000000),0);
/* 00216d24: sw a1,0x8(a0) */ sw((uint32_t)c->r[4]+UINT32_C(0x00000008),(uint32_t)c->r[5]);
/* 00216d28: lb v0,0x16(sp) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[29]+UINT32_C(0x00000016)));
/* 00216d2c: blez v0,0x00216d3c */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 00216d30 */ c->r[3]=*at((uint32_t)c->r[29]+UINT32_C(0x00000016));if(taken){goto L_00216d3c;}}
/* 00216d34: addiu v0,v1,-0x1 */ c->r[2]=sx((uint32_t)c->r[3]+UINT32_C(0xffffffff));
/* 00216d38: sb v0,0x16(sp) */ *at((uint32_t)c->r[29]+UINT32_C(0x00000016))=(uint8_t)c->r[2];
L_00216d3c:;
/* 00216d3c: move a0,sp */ c->r[4]=c->r[29];
/* 00216d40: jal 0x00216a18 */ c->r[31]=UINT64_C(0x00216d48);/* delay 00216d44 */ c->r[5]=c->r[0];body_00216a18(c);
/* 00216d48: addiu s0,s0,0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));
L_00216d4c:;
/* 00216d4c: slt v0,s0,s1 */ c->r[2]=less(c->r[16],c->r[17]);
/* 00216d50: bnel v0,zero,0x00216c30 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00216d54 */ c->r[5]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));goto L_00216c30;}}
L_00216d58:;
/* 00216d58: ld s0,0xf0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x000000f0));
/* 00216d5c: ld s1,0xf8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x000000f8));
/* 00216d60: ld ra,0x100(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000100));
/* 00216d64: jr ra */ /* delay 00216d68 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000110));return;
}

static void body_00219400(CompendiumValues *c){
/* 00219400: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00219404: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00219408: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0021940c: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00219410: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 00219414: lw v0,0x70(a0) */ c->r[2]=sx(word((uint32_t)c->r[4]+UINT32_C(0x00000070)));
/* 00219418: blez v0,0x0021946c */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 0021941c */ c->r[18]=c->r[0];if(taken){goto L_0021946c;}}
/* 00219420: addiu s1,a0,0x74 */ c->r[17]=sx((uint32_t)c->r[4]+UINT32_C(0x00000074));
/* 00219424: move s0,v0 */ c->r[16]=c->r[2];
L_00219428:;
/* 00219428: lbu v1,0x0(s1) */ c->r[3]=*at((uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0021942c: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
/* 00219430: lw a0,-0x5750(gp) */ c->r[4]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00219434: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
/* 00219438: sll v0,v1,0x4 */ c->r[2]=sx((uint32_t)c->r[3]<<4u);
/* 0021943c: addiu s0,s0,-0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffffff));
/* 00219440: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 00219444: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00219448: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 0021944c: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00219450: addu a0,a0,v0 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[2]);
/* 00219454: jal 0x00216a18 */ c->r[31]=UINT64_C(0x0021945c);/* delay 00219458 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000a54));body_00216a18(c);
/* 0021945c: addiu v1,s2,0x1 */ c->r[3]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));
/* 00219460: xori v0,v0,0x1 */ c->r[2]=c->r[2]^UINT64_C(0x1);
/* 00219464: bne s0,zero,0x00219428 */ {int taken=(c->r[16]!=c->r[0]);/* delay 00219468 */ if(c->r[2]==0){c->r[18]=c->r[3];}if(taken){goto L_00219428;}}
L_0021946c:;
/* 0021946c: move v0,s2 */ c->r[2]=c->r[18];
/* 00219470: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00219474: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00219478: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0021947c: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00219480: jr ra */ /* delay 00219484 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_002197b0(CompendiumValues *c){
/* 002197b0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002197b4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002197b8: move s0,a2 */ c->r[16]=c->r[6];
/* 002197bc: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002197c0: move s1,a1 */ c->r[17]=c->r[5];
/* 002197c4: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 002197c8: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 002197cc: jal 0x00216b78 */ c->r[31]=UINT64_C(0x002197d4);/* delay 002197d0 */ c->r[18]=c->r[4];nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)fclEncycGetNum());nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 002197d4: move a3,v0 */ c->r[7]=c->r[2];
/* 002197d8: move a2,zero */ c->r[6]=c->r[0];
/* 002197dc: slt v1,a2,a3 */ c->r[3]=less(c->r[6],c->r[7]);
/* 002197e0: addiu t2,s2,0x15c */ c->r[10]=sx((uint32_t)c->r[18]+UINT32_C(0x0000015c));
/* 002197e4: addiu a0,s2,0x17c */ c->r[4]=sx((uint32_t)c->r[18]+UINT32_C(0x0000017c));
/* 002197e8: beq v1,zero,0x002198c0 */ {int taken=(c->r[3]==c->r[0]);/* delay 002197ec */ c->r[9]=sx((uint32_t)c->r[18]+UINT32_C(0x00000164));if(taken){goto L_002198c0;}}
/* 002197f0: lh v0,0x0(s1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 002197f4: beq s0,v0,0x0021982c */ {int taken=(c->r[16]==c->r[2]);/* delay 002197f8 */ (void)0;if(taken){goto L_0021982c;}}
/* 002197fc: move a1,s1 */ c->r[5]=c->r[17];
/* 00219800: addiu a2,a2,0x1 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 00219804: nop  */ (void)0;
L_00219808:;
/* 00219808: slt v1,a2,a3 */ c->r[3]=less(c->r[6],c->r[7]);
/* 0021980c: beq v1,zero,0x002198c0 */ {int taken=(c->r[3]==c->r[0]);/* delay 00219810 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000002));if(taken){goto L_002198c0;}}
/* 00219814: lh v0,0x0(a1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 00219818: nop  */ (void)0;
/* 0021981c: nop  */ (void)0;
/* 00219820: nop  */ (void)0;
/* 00219824: bnel s0,v0,0x00219808 */ {int taken=(c->r[16]!=c->r[2]);if(taken){/* delay 00219828 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));goto L_00219808;}}
L_0021982c:;
/* 0021982c: beql v1,zero,0x002198c4 */ {int taken=(c->r[3]==c->r[0]);if(taken){/* delay 00219830 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_002198c4;}}
/* 00219834: lbu v0,0x4(a0) */ c->r[2]=*at((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 00219838: lbu a3,0x0(a0) */ c->r[7]=*at((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 0021983c: subu v1,a2,v0 */ c->r[3]=sx((uint32_t)c->r[6]-(uint32_t)c->r[2]);
/* 00219840: lbu a2,0x6(a0) */ c->r[6]=*at((uint32_t)c->r[4]+UINT32_C(0x00000006));
/* 00219844: bgez v1,0x00219858 */ {int taken=(!neg(c->r[3]));/* delay 00219848 */ c->r[8]=c->r[3];if(taken){goto L_00219858;}}
/* 0021984c: b 0x00219870 */ /* delay 00219850 */ c->r[3]=c->r[0];goto L_00219870;
L_00219858:;
/* 00219858: subu a1,a3,a2 */ c->r[5]=sx((uint32_t)c->r[7]-(uint32_t)c->r[6]);
/* 0021985c: slt v0,a1,v1 */ c->r[2]=less(c->r[5],c->r[3]);
/* 00219860: beq v0,zero,0x00219870 */ {int taken=(c->r[2]==c->r[0]);/* delay 00219864 */ c->r[2]=less(c->r[7],c->r[6]);if(taken){goto L_00219870;}}
/* 00219868: move v1,zero */ c->r[3]=c->r[0];
/* 0021986c: movz v1,a1,v0 */ if(c->r[2]==0){c->r[3]=c->r[5];}
L_00219870:;
/* 00219870: beq v1,t0,0x002198a4 */ {int taken=(c->r[3]==c->r[8]);/* delay 00219874 */ sh((uint32_t)c->r[4]+UINT32_C(0x00000002),(uint16_t)c->r[3]);if(taken){goto L_002198a4;}}
/* 00219878: lbu v0,0x4(a0) */ c->r[2]=*at((uint32_t)c->r[4]+UINT32_C(0x00000004));
/* 0021987c: subu v1,t0,v1 */ c->r[3]=sx((uint32_t)c->r[8]-(uint32_t)c->r[3]);
/* 00219880: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00219884: sb v0,0x5(a0) */ *at((uint32_t)c->r[4]+UINT32_C(0x00000005))=(uint8_t)c->r[2];
/* 00219888: andi v1,v0,0xff */ c->r[3]=c->r[2]&UINT64_C(0xff);
/* 0021988c: sb v0,0x4(a0) */ *at((uint32_t)c->r[4]+UINT32_C(0x00000004))=(uint8_t)c->r[2];
/* 00219890: lw v0,0x0(t2) */ c->r[2]=sx(word((uint32_t)c->r[10]+UINT32_C(0x00000000)));
/* 00219894: lw a0,0x14(t1) */ c->r[4]=sx(word((uint32_t)c->r[9]+UINT32_C(0x00000014)));
/* 00219898: mult v1,v1,v0 */ {int64_t p=(int64_t)(int32_t)(uint32_t)c->r[3]*(int64_t)(int32_t)(uint32_t)c->r[2];c->lo=sx((uint32_t)(uint64_t)p);c->hi=sx((uint32_t)((uint64_t)p>>32));c->r[3]=c->lo;}
/* 0021989c: addu v1,v1,a0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[4]);
/* 002198a0: sw v1,0x4(t1) */ sw((uint32_t)c->r[9]+UINT32_C(0x00000004),(uint32_t)c->r[3]);
L_002198a4:;
/* 002198a4: move a0,s2 */ c->r[4]=c->r[18];
/* 002198a8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002198ac: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002198b0: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002198b4: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002198b8: j 0x002198d8 */ /* delay 002198bc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_002198d8;
L_002198c0:;
/* 002198c0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_002198c4:;
/* 002198c4: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002198c8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002198cc: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002198d0: jr ra */ /* delay 002198d4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
L_002198d8:;
/* 002198d8: addiu a1,a0,0x17c */ c->r[5]=sx((uint32_t)c->r[4]+UINT32_C(0x0000017c));
/* 002198dc: addiu t0,a0,0x164 */ c->r[8]=sx((uint32_t)c->r[4]+UINT32_C(0x00000164));
/* 002198e0: lbu v1,0x4(a1) */ c->r[3]=*at((uint32_t)c->r[5]+UINT32_C(0x00000004));
/* 002198e4: addiu t1,a0,0x15c */ c->r[9]=sx((uint32_t)c->r[4]+UINT32_C(0x0000015c));
/* 002198e8: bne v1,zero,0x00219928 */ {int taken=(c->r[3]!=c->r[0]);/* delay 002198ec */ c->r[6]=*at((uint32_t)c->r[5]+UINT32_C(0x00000006));if(taken){goto L_00219928;}}
/* 002198f0: lh v0,0x2(a1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000002)));
/* 002198f4: blez v0,0x00219978 */ {int taken=((neg(c->r[2])||!c->r[2]));/* delay 002198f8 */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000002));if(taken){goto L_00219978;}}
/* 002198fc: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 00219900: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 00219904: sb v0,0x5(a1) */ *at((uint32_t)c->r[5]+UINT32_C(0x00000005))=(uint8_t)c->r[2];
/* 00219908: addiu v1,v1,-0x1 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xffffffff));
/* 0021990c: sb a0,0x4(a1) */ *at((uint32_t)c->r[5]+UINT32_C(0x00000004))=(uint8_t)c->r[4];
/* 00219910: sh v1,0x2(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x00000002),(uint16_t)c->r[3]);
/* 00219914: lw v0,0x0(t1) */ c->r[2]=sx(word((uint32_t)c->r[9]+UINT32_C(0x00000000)));
/* 00219918: lw v1,0x14(t0) */ c->r[3]=sx(word((uint32_t)c->r[8]+UINT32_C(0x00000014)));
/* 0021991c: addu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 00219920: jr ra */ /* delay 00219924 */ sw((uint32_t)c->r[8]+UINT32_C(0x00000004),(uint32_t)c->r[2]);return;
L_00219928:;
/* 00219928: addiu v0,a2,-0x1 */ c->r[2]=sx((uint32_t)c->r[6]+UINT32_C(0xffffffff));
/* 0021992c: bne v1,v0,0x00219978 */ {int taken=(c->r[3]!=c->r[2]);/* delay 00219930 */ (void)0;if(taken){goto L_00219978;}}
/* 00219934: lh v0,0x2(a1) */ c->r[2]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000002)));
/* 00219938: lbu a0,0x0(a1) */ c->r[4]=*at((uint32_t)c->r[5]+UINT32_C(0x00000000));
/* 0021993c: lhu v1,0x2(a1) */ c->r[3]=hword((uint32_t)c->r[5]+UINT32_C(0x00000002));
/* 00219940: addu v0,v0,a2 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[6]);
/* 00219944: slt v0,v0,a0 */ c->r[2]=less(c->r[2],c->r[4]);
/* 00219948: beq v0,zero,0x00219978 */ {int taken=(c->r[2]==c->r[0]);/* delay 0021994c */ c->r[7]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));if(taken){goto L_00219978;}}
/* 00219950: addiu v1,a2,0xfe */ c->r[3]=sx((uint32_t)c->r[6]+UINT32_C(0x000000fe));
/* 00219954: sh a3,0x2(a1) */ sh((uint32_t)c->r[5]+UINT32_C(0x00000002),(uint16_t)c->r[7]);
/* 00219958: sb v1,0x5(a1) */ *at((uint32_t)c->r[5]+UINT32_C(0x00000005))=(uint8_t)c->r[3];
/* 0021995c: andi v0,v1,0xff */ c->r[2]=c->r[3]&UINT64_C(0xff);
/* 00219960: sb v1,0x4(a1) */ *at((uint32_t)c->r[5]+UINT32_C(0x00000004))=(uint8_t)c->r[3];
/* 00219964: lw v1,0x0(t1) */ c->r[3]=sx(word((uint32_t)c->r[9]+UINT32_C(0x00000000)));
/* 00219968: lw a0,0x14(t0) */ c->r[4]=sx(word((uint32_t)c->r[8]+UINT32_C(0x00000014)));
/* 0021996c: mult v0,v0,v1 */ {int64_t p=(int64_t)(int32_t)(uint32_t)c->r[2]*(int64_t)(int32_t)(uint32_t)c->r[3];c->lo=sx((uint32_t)(uint64_t)p);c->hi=sx((uint32_t)((uint64_t)p>>32));c->r[2]=c->lo;}
/* 00219970: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 00219974: sw v0,0x4(t0) */ sw((uint32_t)c->r[8]+UINT32_C(0x00000004),(uint32_t)c->r[2]);
L_00219978:;
/* 00219978: jr ra */ /* delay 0021997c */ (void)0;return;
}

static void body_00219ba0(CompendiumValues *c){
/* 00219ba0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00219ba4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00219ba8: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00219bac: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 00219bb0: jal 0x00216b78 */ c->r[31]=UINT64_C(0x00219bb8);/* delay 00219bb4 */ c->r[17]=c->r[4];nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)fclEncycGetNum());nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00219bb8: move s0,v0 */ c->r[16]=c->r[2];
/* 00219bbc: move a0,s1 */ c->r[4]=c->r[17];
/* 00219bc0: jal 0x00219dc0 */ c->r[31]=UINT64_C(0x00219bc8);/* delay 00219bc4 */ c->r[5]=c->r[16];body_00219dc0(c);
/* 00219bc8: lui a3,0x22 */ c->r[7]=sx(UINT32_C(0x00220000));
/* 00219bcc: move a0,s1 */ c->r[4]=c->r[17];
/* 00219bd0: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00219bd4: move a1,s0 */ c->r[5]=c->r[16];
/* 00219bd8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00219bdc: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00219be0: addiu a3,a3,-0x63c0 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0xffff9c40));
/* 00219be4: li a2,0x2 */ c->r[6]=sx(UINT32_C(0x00000002));
/* 00219be8: j 0x002d4860 */ /* delay 00219bec */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);ps2Qsort_002D4860(A0,A1,A2,A3);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);return;
}

static void body_00219bf0(CompendiumValues *c){
/* 00219bf0: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 00219bf4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00219bf8: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00219bfc: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 00219c00: jal 0x00216b78 */ c->r[31]=UINT64_C(0x00219c08);/* delay 00219c04 */ c->r[17]=c->r[4];nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)fclEncycGetNum());nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00219c08: move s0,v0 */ c->r[16]=c->r[2];
/* 00219c0c: move a0,s1 */ c->r[4]=c->r[17];
/* 00219c10: jal 0x00219dc0 */ c->r[31]=UINT64_C(0x00219c18);/* delay 00219c14 */ c->r[5]=c->r[16];body_00219dc0(c);
/* 00219c18: lui a3,0x22 */ c->r[7]=sx(UINT32_C(0x00220000));
/* 00219c1c: move a0,s1 */ c->r[4]=c->r[17];
/* 00219c20: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00219c24: move a1,s0 */ c->r[5]=c->r[16];
/* 00219c28: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00219c2c: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00219c30: addiu a3,a3,-0x6300 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0xffff9d00));
/* 00219c34: li a2,0x2 */ c->r[6]=sx(UINT32_C(0x00000002));
/* 00219c38: j 0x002d4860 */ /* delay 00219c3c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);ps2Qsort_002D4860(A0,A1,A2,A3);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);return;
}

static void body_00219dc0(CompendiumValues *c){
/* 00219dc0: blez a1,0x00219de4 */ {int taken=((neg(c->r[5])||!c->r[5]));/* delay 00219dc4 */ c->r[6]=c->r[0];if(taken){goto L_00219de4;}}
L_00219dc8:;
/* 00219dc8: addiu v1,a2,0x1 */ c->r[3]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 00219dcc: sh a2,0x0(a0) */ sh((uint32_t)c->r[4]+UINT32_C(0x00000000),(uint16_t)c->r[6]);
/* 00219dd0: sll v1,v1,0x10 */ c->r[3]=sx((uint32_t)c->r[3]<<16u);
/* 00219dd4: sra a2,v1,0x10 */ c->r[6]=sar((uint32_t)c->r[3],16u);
/* 00219dd8: slt v0,a2,a1 */ c->r[2]=less(c->r[6],c->r[5]);
/* 00219ddc: bne v0,zero,0x00219dc8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00219de0 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000002));if(taken){goto L_00219dc8;}}
L_00219de4:;
/* 00219de4: jr ra */ /* delay 00219de8 */ (void)0;return;
}

static void body_00219c40(CompendiumValues *c){
/* 00219c40: lh a2,0x0(a0) */ c->r[6]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 00219c44: lui a3,0x1 */ c->r[7]=sx(UINT32_C(0x00010000));
/* 00219c48: lh a0,0x0(a1) */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 00219c4c: ori a3,a3,0x1e90 */ c->r[7]=c->r[7]|UINT64_C(0x1e90);
/* 00219c50: sll v1,a2,0x1 */ c->r[3]=sx((uint32_t)c->r[6]<<1u);
/* 00219c54: lw a1,-0x5750(gp) */ c->r[5]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00219c58: sll v0,a0,0x1 */ c->r[2]=sx((uint32_t)c->r[4]<<1u);
/* 00219c5c: addu v1,v1,a2 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[6]);
/* 00219c60: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 00219c64: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 00219c68: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00219c6c: subu v1,v1,a2 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[6]);
/* 00219c70: subu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[4]);
/* 00219c74: sll v1,v1,0x4 */ c->r[3]=sx((uint32_t)c->r[3]<<4u);
/* 00219c78: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 00219c7c: addu v1,a1,v1 */ c->r[3]=sx((uint32_t)c->r[5]+(uint32_t)c->r[3]);
/* 00219c80: addu a1,a1,v0 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[2]);
/* 00219c84: addu t0,v1,a3 */ c->r[8]=sx((uint32_t)c->r[3]+(uint32_t)c->r[7]);
/* 00219c88: addu a3,a1,a3 */ c->r[7]=sx((uint32_t)c->r[5]+(uint32_t)c->r[7]);
/* 00219c8c: lui a1,0x35 */ c->r[5]=sx(UINT32_C(0x00350000));
/* 00219c90: lhu a0,0x0(t0) */ c->r[4]=hword((uint32_t)c->r[8]+UINT32_C(0x00000000));
/* 00219c94: addiu a1,a1,-0x6840 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0xffff97c0));
/* 00219c98: lhu a2,0x0(a3) */ c->r[6]=hword((uint32_t)c->r[7]+UINT32_C(0x00000000));
/* 00219c9c: sll v1,a0,0x4 */ c->r[3]=sx((uint32_t)c->r[4]<<4u);
/* 00219ca0: sll v0,a2,0x4 */ c->r[2]=sx((uint32_t)c->r[6]<<4u);
/* 00219ca4: subu v1,v1,a0 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[4]);
/* 00219ca8: subu v0,v0,a2 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[6]);
/* 00219cac: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 00219cb0: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00219cb4: addu v1,v1,a1 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[5]);
/* 00219cb8: addu v0,v0,a1 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[5]);
/* 00219cbc: lbu a0,0x4(v1) */ c->r[4]=*at((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 00219cc0: lbu a1,0x4(v0) */ c->r[5]=*at((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 00219cc4: slt v0,a1,a0 */ c->r[2]=less(c->r[5],c->r[4]);
/* 00219cc8: slt a0,a0,a1 */ c->r[4]=less(c->r[4],c->r[5]);
/* 00219ccc: bne a0,zero,0x219cf8 */ {int taken=(c->r[4]!=c->r[0]);/* delay 00219cd0 */ c->r[6]=sx((uint32_t)c->r[0]+UINT32_C(0xffffffff));if(taken){goto L_00219cf8;}}
/* 00219cd4: bne v0,zero,0x219cf8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00219cd8 */ c->r[6]=sx((uint32_t)c->r[0]+UINT32_C(0x00000001));if(taken){goto L_00219cf8;}}
/* 00219cdc: lhu v0,0xc(t0) */ c->r[2]=hword((uint32_t)c->r[8]+UINT32_C(0x0000000c));
/* 00219ce0: addiu a2,zero,-0x1 */ c->r[6]=sx((uint32_t)c->r[0]+UINT32_C(0xffffffff));
/* 00219ce4: lhu a0,0xc(a3) */ c->r[4]=hword((uint32_t)c->r[7]+UINT32_C(0x0000000c));
/* 00219ce8: slt v1,a0,v0 */ c->r[3]=less(c->r[4],c->r[2]);
/* 00219cec: slt v0,v0,a0 */ c->r[2]=less(c->r[2],c->r[4]);
/* 00219cf0: xori v1,v1,0x0 */ c->r[3]=c->r[3]^UINT64_C(0x0);
/* 00219cf4: movz a2,v0,v1 */ if(c->r[3]==0){c->r[6]=c->r[2];}
L_00219cf8:;
/* 00219cf8: jr ra */ /* delay 00219cfc */ c->r[2]=c->r[6]+c->r[0];return;
}

static void body_00219d00(CompendiumValues *c){
/* 00219d00: lh a2,0x0(a0) */ c->r[6]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 00219d04: lui a3,0x1 */ c->r[7]=sx(UINT32_C(0x00010000));
/* 00219d08: lh a0,0x0(a1) */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 00219d0c: ori a3,a3,0x1e90 */ c->r[7]=c->r[7]|UINT64_C(0x1e90);
/* 00219d10: sll v1,a2,0x1 */ c->r[3]=sx((uint32_t)c->r[6]<<1u);
/* 00219d14: lw a1,-0x5750(gp) */ c->r[5]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00219d18: sll v0,a0,0x1 */ c->r[2]=sx((uint32_t)c->r[4]<<1u);
/* 00219d1c: addu v1,v1,a2 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[6]);
/* 00219d20: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 00219d24: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 00219d28: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00219d2c: subu v1,v1,a2 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[6]);
/* 00219d30: subu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[4]);
/* 00219d34: sll v1,v1,0x4 */ c->r[3]=sx((uint32_t)c->r[3]<<4u);
/* 00219d38: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 00219d3c: addu v1,a1,v1 */ c->r[3]=sx((uint32_t)c->r[5]+(uint32_t)c->r[3]);
/* 00219d40: addu a1,a1,v0 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[2]);
/* 00219d44: addu a2,v1,a3 */ c->r[6]=sx((uint32_t)c->r[3]+(uint32_t)c->r[7]);
/* 00219d48: addu a1,a1,a3 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[7]);
/* 00219d4c: lhu v1,0xc(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x0000000c));
/* 00219d50: lhu v0,0xc(a1) */ c->r[2]=hword((uint32_t)c->r[5]+UINT32_C(0x0000000c));
/* 00219d54: slt a0,v1,v0 */ c->r[4]=less(c->r[3],c->r[2]);
/* 00219d58: slt v0,v0,v1 */ c->r[2]=less(c->r[2],c->r[3]);
/* 00219d5c: bne v0,zero,0x219db8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00219d60 */ c->r[7]=sx((uint32_t)c->r[0]+UINT32_C(0xffffffff));if(taken){goto L_00219db8;}}
/* 00219d64: bne a0,zero,0x219db8 */ {int taken=(c->r[4]!=c->r[0]);/* delay 00219d68 */ c->r[7]=sx((uint32_t)c->r[0]+UINT32_C(0x00000001));if(taken){goto L_00219db8;}}
/* 00219d6c: lhu a1,0x0(a1) */ c->r[5]=hword((uint32_t)c->r[5]+UINT32_C(0x00000000));
/* 00219d70: lui a0,0x35 */ c->r[4]=sx(UINT32_C(0x00350000));
/* 00219d74: lhu a2,0x0(a2) */ c->r[6]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));
/* 00219d78: addiu a0,a0,-0x6840 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0xffff97c0));
/* 00219d7c: sll v0,a1,0x4 */ c->r[2]=sx((uint32_t)c->r[5]<<4u);
/* 00219d80: addiu a3,zero,-0x1 */ c->r[7]=sx((uint32_t)c->r[0]+UINT32_C(0xffffffff));
/* 00219d84: sll v1,a2,0x4 */ c->r[3]=sx((uint32_t)c->r[6]<<4u);
/* 00219d88: subu v0,v0,a1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[5]);
/* 00219d8c: subu v1,v1,a2 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[6]);
/* 00219d90: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00219d94: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 00219d98: addu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 00219d9c: addu v1,v1,a0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[4]);
/* 00219da0: lbu a0,0x4(v0) */ c->r[4]=*at((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 00219da4: lbu a1,0x4(v1) */ c->r[5]=*at((uint32_t)c->r[3]+UINT32_C(0x00000004));
/* 00219da8: slt v1,a1,a0 */ c->r[3]=less(c->r[5],c->r[4]);
/* 00219dac: slt a0,a0,a1 */ c->r[4]=less(c->r[4],c->r[5]);
/* 00219db0: xori v1,v1,0x0 */ c->r[3]=c->r[3]^UINT64_C(0x0);
/* 00219db4: movz a3,a0,v1 */ if(c->r[3]==0){c->r[7]=c->r[4];}
L_00219db8:;
/* 00219db8: jr ra */ /* delay 00219dbc */ c->r[2]=c->r[7]+c->r[0];return;
}

static void body_00216a18(CompendiumValues *c){
/* 00216a18: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 00216a1c: lw v0,-0x5750(gp) */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00216a20: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00216a24: move s0,a0 */ c->r[16]=c->r[4];
/* 00216a28: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00216a2c: lui s1,0x1 */ c->r[17]=sx(UINT32_C(0x00010000));
/* 00216a30: ori s1,s1,0x1e80 */ c->r[17]=c->r[17]|UINT64_C(0x1e80);
/* 00216a34: addu s1,s1,v0 */ c->r[17]=sx((uint32_t)c->r[17]+(uint32_t)c->r[2]);
/* 00216a38: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00216a3c: move s2,a1 */ c->r[18]=c->r[5];
/* 00216a40: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 00216a44: lui s3,0x1 */ c->r[19]=sx(UINT32_C(0x00010000));
/* 00216a48: ori s3,s3,0x1e90 */ c->r[19]=c->r[19]|UINT64_C(0x1e90);
/* 00216a4c: addu s3,s3,v0 */ c->r[19]=sx((uint32_t)c->r[19]+(uint32_t)c->r[2]);
/* 00216a50: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 00216a54: jal 0x00216b20 */ c->r[31]=UINT64_C(0x00216a5c);/* delay 00216a58 */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000004));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)fclEncycSearch((int32_t)(uint32_t)A0));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216a5c: move a1,s0 */ c->r[5]=c->r[16];
/* 00216a60: move v1,v0 */ c->r[3]=c->r[2];
/* 00216a64: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
/* 00216a68: bgez v1,0x00216ab0 */ {int taken=(!neg(c->r[3]));/* delay 00216a6c */ c->r[16]=sx(UINT32_C(0x00000001));if(taken){goto L_00216ab0;}}
/* 00216a70: lw a0,0x0(s1) */ c->r[4]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000000)));
/* 00216a74: slti v0,a0,0xb8 */ c->r[2]=less(c->r[4],sx(UINT32_C(0x000000b8)));
/* 00216a78: bnel v0,zero,0x00216aa0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00216a7c */ c->r[3]=c->r[4];goto L_00216aa0;}}
/* 00216a80: lui s0,0x54 */ c->r[16]=sx(UINT32_C(0x00540000));
/* 00216a84: addiu s0,s0,-0x2818 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffd7e8));
/* 00216a88: jal 0x002d4748 */ c->r[31]=UINT64_C(0x00216a90);/* delay 00216a8c */ c->r[4]=c->r[16];nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2LibcPrintf(A0);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216a90: jal 0x001097e8 */ c->r[31]=UINT64_C(0x00216a98);/* delay 00216a94 */ c->r[4]=c->r[16];nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);ps2ScriptDiagnosticDisabled(A0);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216a98: b 0x00216b04 */ /* delay 00216a9c */ c->r[2]=sx(UINT32_C(0xffffffff));goto L_00216b04;
L_00216aa0:;
/* 00216aa0: move s0,zero */ c->r[16]=c->r[0];
/* 00216aa4: addiu v0,v1,0x1 */ c->r[2]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 00216aa8: b 0x00216ab8 */ /* delay 00216aac */ sw((uint32_t)c->r[17]+UINT32_C(0x00000000),(uint32_t)c->r[2]);goto L_00216ab8;
L_00216ab0:;
/* 00216ab0: beql s2,zero,0x00216b08 */ {int taken=(c->r[18]==c->r[0]);if(taken){/* delay 00216ab4 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_00216b08;}}
L_00216ab8:;
/* 00216ab8: sll a0,v1,0x1 */ c->r[4]=sx((uint32_t)c->r[3]<<1u);
/* 00216abc: addu a0,a0,v1 */ c->r[4]=sx((uint32_t)c->r[4]+(uint32_t)c->r[3]);
/* 00216ac0: sll a0,a0,0x2 */ c->r[4]=sx((uint32_t)c->r[4]<<2u);
/* 00216ac4: subu a0,a0,v1 */ c->r[4]=sx((uint32_t)c->r[4]-(uint32_t)c->r[3]);
/* 00216ac8: sll a0,a0,0x4 */ c->r[4]=sx((uint32_t)c->r[4]<<4u);
/* 00216acc: jal 0x00219df0 */ c->r[31]=UINT64_C(0x00216ad4);/* delay 00216ad0 */ c->r[4]=sx((uint32_t)c->r[19]+(uint32_t)c->r[4]);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);fclEncyc_SetElem((fclEncycElem_PS2 *)at((uint32_t)A0),(datUnitWork_PS2 *)at((uint32_t)A1));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216ad4: jal 0x00216b90 */ c->r[31]=UINT64_C(0x00216adc);/* delay 00216ad8 */ (void)0;nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)fclEncycGetRatio2());nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216adc: slti v0,v0,0x64 */ c->r[2]=less(c->r[2],sx(UINT32_C(0x00000064)));
/* 00216ae0: bne v0,zero,0x00216af8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 00216ae4 */ c->r[4]=sx(UINT32_C(0x00000913));if(taken){goto L_00216af8;}}
/* 00216ae8: jal 0x001e0ed0 */ c->r[31]=UINT64_C(0x00216af0);/* delay 00216aec */ (void)0;nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);evtBitOn((int32_t)(uint32_t)A0);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216af0: b 0x00216b04 */ /* delay 00216af4 */ c->r[2]=c->r[16];goto L_00216b04;
L_00216af8:;
/* 00216af8: jal 0x001e0f10 */ c->r[31]=UINT64_C(0x00216b00);/* delay 00216afc */ c->r[4]=sx(UINT32_C(0x00000913));nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);evtBitOff((int32_t)(uint32_t)A0);nocturneCompendiumRecordsSetStackPointer((uint32_t)c->r[29]);
/* 00216b00: move v0,s0 */ c->r[2]=c->r[16];
L_00216b04:;
/* 00216b04: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_00216b08:;
/* 00216b08: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 00216b0c: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 00216b10: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 00216b14: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 00216b18: jr ra */ /* delay 00216b1c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}
static CompendiumValues begin(void){CompendiumValues c={0};c.r[28]=UINT64_C(0x00554170);c.r[29]=nocturneCompendiumRecordsStackPointer();return c;}
uint64_t ps2CompendiumRecords_00216910(uint64_t p0,uint64_t p1){CompendiumValues c=begin();c.r[4]=p0;c.r[5]=p1;body_00216910(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2CompendiumRecords_00219FC0(uint64_t p0,uint64_t p1){CompendiumValues c=begin();c.r[4]=p0;c.r[5]=p1;body_00219fc0(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);}
void ps2CompendiumRecords_00216C08(void){CompendiumValues c=begin();body_00216c08(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2CompendiumRecords_00219400(uint64_t p0){CompendiumValues c=begin();c.r[4]=p0;body_00219400(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2CompendiumRecords_002197B0(uint64_t p0,uint64_t p1,uint64_t p2){CompendiumValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_002197b0(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);}
void ps2CompendiumRecords_00219BA0(uint64_t p0){CompendiumValues c=begin();c.r[4]=p0;body_00219ba0(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);}
void ps2CompendiumRecords_00219BF0(uint64_t p0){CompendiumValues c=begin();c.r[4]=p0;body_00219bf0(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);}
void ps2CompendiumRecords_00219DC0(uint64_t p0,uint64_t p1){CompendiumValues c=begin();c.r[4]=p0;c.r[5]=p1;body_00219dc0(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2CompendiumRecords_00219C40(uint64_t p0,uint64_t p1){CompendiumValues c=begin();c.r[4]=p0;c.r[5]=p1;body_00219c40(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2CompendiumRecords_00219D00(uint64_t p0,uint64_t p1){CompendiumValues c=begin();c.r[4]=p0;c.r[5]=p1;body_00219d00(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2CompendiumRecords_00216A18(uint64_t p0,uint64_t p1){CompendiumValues c=begin();c.r[4]=p0;c.r[5]=p1;body_00216a18(&c);nocturneCompendiumRecordsSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
