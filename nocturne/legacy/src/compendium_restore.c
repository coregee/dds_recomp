/* Whole5 compendium restore/check routines335 instructions plus existing
 * complete22-op raw64Search variant. Fixed native-PC statements, real
 * constructor calls, guest frames and individual partial memory operations.
 * No HD missing-ID registration, null guard or serialized output answer. */
#include "compendium_restore.h"
#include "unit_neighbors.h"
#include "ps2_memory.h"

#include <string.h>
typedef struct CompendiumRestoreValues {uint64_t r[32],lo,hi;} CompendiumRestoreValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}
static uint8_t *at(uint32_t address){return (uint8_t *)nocturneResolveCompendiumRestoreAddress(address);}
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


/* EE LWL sign-extends the merged word. LWR preserves bits63:32 except
 * offset0, where its complete word sign-extends. Each partial instruction
 * latches its incoming value and changes only its own participating bytes. */
static uint64_t partial_word_load(uint64_t old,uint32_t a,unsigned left){
 unsigned offset=a&3u,count=left?offset+1u:4u-offset;
 uint32_t start=left?(a&~3u):a;unsigned target=left?3u-offset:0u;
 uint32_t value=(uint32_t)old;
 for(unsigned i=0;i<count;i++){unsigned shift=8u*(target+i);value=(value&~(UINT32_C(255)<<shift))|((uint32_t)*at(start+i)<<shift);}
 return left||!offset?sx(value):(old&UINT64_C(0xffffffff00000000))|value;
}
static void partial_word_store(uint64_t value,uint32_t a,unsigned left){
 unsigned offset=a&3u,count=left?offset+1u:4u-offset;
 uint32_t start=left?(a&~3u):a;unsigned source=left?3u-offset:0u;
 for(unsigned i=0;i<count;i++)*at(start+i)=(uint8_t)(value>>(8u*(source+i)));
}

static void body_00216bf0(CompendiumRestoreValues *c);
static void body_00219318(CompendiumRestoreValues *c);
static void body_0021a0b8(CompendiumRestoreValues *c);
static void body_0021a118(CompendiumRestoreValues *c);
static void body_0021a308(CompendiumRestoreValues *c);
static void body_00216b20(CompendiumRestoreValues *c);

static void body_00216bf0(CompendiumRestoreValues *c){
/* 00216bf0: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 00216bf4: move a0,zero */ c->r[4]=c->r[0];
/* 00216bf8: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 00216bfc: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 00216c00: j 0x00219318 */ /* delay 00216c04 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_00219318(c);return;
}

static void body_00219318(CompendiumRestoreValues *c){
/* 00219318: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 0021931c: lw v0,-0x5750(gp) */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00219320: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00219324: move s1,a0 */ c->r[17]=c->r[4];
/* 00219328: sd ra,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[31]);
/* 0021932c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00219330: addiu s0,v0,0xe04 */ c->r[16]=sx((uint32_t)c->r[2]+UINT32_C(0x00000e04));
/* 00219334: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00219338: li s2,0x4 */ c->r[18]=sx(UINT32_C(0x00000004));
/* 0021933c: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 00219340: move s3,zero */ c->r[19]=c->r[0];
/* 00219344: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 00219348: sltu s4,zero,s1 */ c->r[20]=(c->r[0]<c->r[17]);
/* 0021934c: nop  */ (void)0;
L_00219350:;
/* 00219350: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 00219354: andi v1,v0,0x10 */ c->r[3]=c->r[2]&UINT64_C(0x10);
/* 00219358: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0021935c: beql v0,zero,0x002193d0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 00219360 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_002193d0;}}
/* 00219364: bnel v1,zero,0x002193d0 */ {int taken=(c->r[3]!=c->r[0]);if(taken){/* delay 00219368 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_002193d0;}}
/* 0021936c: lhu v0,0xe(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x0000000e));
/* 00219370: andi v0,v0,0x800 */ c->r[2]=c->r[2]&UINT64_C(0x800);
/* 00219374: bnel v0,zero,0x002193d0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 00219378 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_002193d0;}}
/* 0021937c: jal 0x00216b20 */ c->r[31]=UINT64_C(0x00219384);/* delay 00219380 */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000004));body_00216b20(c);
/* 00219384: lw a1,-0x5750(gp) */ c->r[5]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00219388: sll v1,v0,0x1 */ c->r[3]=sx((uint32_t)c->r[2]<<1u);
/* 0021938c: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 00219390: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 00219394: subu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[2]);
/* 00219398: sll v1,v1,0x4 */ c->r[3]=sx((uint32_t)c->r[3]<<4u);
/* 0021939c: addu a1,a1,v1 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[3]);
/* 002193a0: lui at,0x1 */ c->r[1]=sx(UINT32_C(0x00010000));
/* 002193a4: ori at,at,0x1e90 */ c->r[1]=c->r[1]|UINT64_C(0x1e90);
/* 002193a8: addu a1,at,a1 */ c->r[5]=sx((uint32_t)c->r[1]+(uint32_t)c->r[5]);
/* 002193ac: jal 0x0021a308 */ c->r[31]=UINT64_C(0x002193b4);/* delay 002193b0 */ c->r[4]=c->r[16];body_0021a308(c);
/* 002193b4: beql v0,zero,0x002193d0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002193b8 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));goto L_002193d0;}}
/* 002193bc: beq s4,zero,0x002193dc */ {int taken=(c->r[20]==c->r[0]);/* delay 002193c0 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));if(taken){goto L_002193dc;}}
/* 002193c4: sb s2,0x0(s1) */ *at((uint32_t)c->r[17]+UINT32_C(0x00000000))=(uint8_t)c->r[18];
/* 002193c8: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
/* 002193cc: addiu s2,s2,0x1 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000001));
L_002193d0:;
/* 002193d0: slti v0,s2,0x10 */ c->r[2]=less(c->r[18],sx(UINT32_C(0x00000010)));
/* 002193d4: bne v0,zero,0x00219350 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002193d8 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x000000ec));if(taken){goto L_00219350;}}
L_002193dc:;
/* 002193dc: move v0,s3 */ c->r[2]=c->r[19];
/* 002193e0: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002193e4: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002193e8: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002193ec: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002193f0: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 002193f4: ld ra,0x28(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 002193f8: jr ra */ /* delay 002193fc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_0021a0b8(CompendiumRestoreValues *c){
/* 0021a0b8: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0021a0bc: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0021a0c0: move s1,a0 */ c->r[17]=c->r[4];
/* 0021a0c4: move a0,a1 */ c->r[4]=c->r[5];
/* 0021a0c8: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0021a0cc: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 0021a0d0: jal 0x00216b20 */ c->r[31]=UINT64_C(0x0021a0d8);/* delay 0021a0d4 */ c->r[16]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));body_00216b20(c);
/* 0021a0d8: sll v1,v0,0x1 */ c->r[3]=sx((uint32_t)c->r[2]<<1u);
/* 0021a0dc: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0021a0e0: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0021a0e4: lui at,0x1 */ c->r[1]=sx(UINT32_C(0x00010000));
/* 0021a0e8: ori at,at,0x1e80 */ c->r[1]=c->r[1]|UINT64_C(0x1e80);
/* 0021a0ec: addu s0,at,s0 */ c->r[16]=sx((uint32_t)c->r[1]+(uint32_t)c->r[16]);
/* 0021a0f0: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 0021a0f4: move a0,s1 */ c->r[4]=c->r[17];
/* 0021a0f8: subu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[2]);
/* 0021a0fc: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0021a100: sll v1,v1,0x4 */ c->r[3]=sx((uint32_t)c->r[3]<<4u);
/* 0021a104: addu s0,s0,v1 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[3]);
/* 0021a108: addiu a1,s0,0x10 */ c->r[5]=sx((uint32_t)c->r[16]+UINT32_C(0x00000010));
/* 0021a10c: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0021a110: j 0x0021a118 */ /* delay 0021a114 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));body_0021a118(c);return;
}

static void body_0021a118(CompendiumRestoreValues *c){
/* 0021a118: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0021a11c: li a2,0xec */ c->r[6]=sx(UINT32_C(0x000000ec));
/* 0021a120: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0021a124: move s1,a1 */ c->r[17]=c->r[5];
/* 0021a128: move a1,zero */ c->r[5]=c->r[0];
/* 0021a12c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0021a130: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 0021a134: jal 0x002d4558 */ c->r[31]=UINT64_C(0x0021a13c);/* delay 0021a138 */ c->r[16]=c->r[4];nocturneCompendiumRestoreSetStackPointer((uint32_t)c->r[29]);(void)ps2Memset(at((uint32_t)A0),(int32_t)(uint32_t)A1,(uint32_t)A2);c->r[2]=A0;nocturneCompendiumRestoreSetStackPointer((uint32_t)c->r[29]);
/* 0021a13c: lhu a0,0x0(s1) */ c->r[4]=hword((uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0021a140: jal 0x001fee68 */ c->r[31]=UINT64_C(0x0021a148);/* delay 0021a144 */ c->r[5]=c->r[16];nocturneCompendiumRestoreSetStackPointer((uint32_t)c->r[29]);cmbCopyDefaultDevilToStock((uint16_t)A0,(datUnitWork_PS2 *)at((uint32_t)A1));nocturneCompendiumRestoreSetStackPointer((uint32_t)c->r[29]);
/* 0021a148: lhu v0,0x4(s1) */ c->r[2]=hword((uint32_t)c->r[17]+UINT32_C(0x00000004));
/* 0021a14c: lw v1,0x8(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000008)));
/* 0021a150: li a1,-0x241 */ c->r[5]=sx(UINT32_C(0xfffffdbf));
/* 0021a154: sh v0,0x6(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000006),(uint16_t)c->r[2]);
/* 0021a158: sw v1,0x10(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000010),(uint32_t)c->r[3]);
/* 0021a15c: lhu v0,0x4(s1) */ c->r[2]=hword((uint32_t)c->r[17]+UINT32_C(0x00000004));
/* 0021a160: sh v0,0x8(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000008),(uint16_t)c->r[2]);
/* 0021a164: lhu v1,0x6(s1) */ c->r[3]=hword((uint32_t)c->r[17]+UINT32_C(0x00000006));
/* 0021a168: sh v1,0xa(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000000a),(uint16_t)c->r[3]);
/* 0021a16c: lhu v0,0x6(s1) */ c->r[2]=hword((uint32_t)c->r[17]+UINT32_C(0x00000006));
/* 0021a170: sh v0,0xc(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000000c),(uint16_t)c->r[2]);
/* 0021a174: lhu v1,0xc(s1) */ c->r[3]=hword((uint32_t)c->r[17]+UINT32_C(0x0000000c));
/* 0021a178: sh v1,0x14(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000014),(uint16_t)c->r[3]);
/* 0021a17c: lwl v0,0x11(s1) */ c->r[2]=partial_word_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000011),1);
/* 0021a180: lwr v0,0xe(s1) */ c->r[2]=partial_word_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x0000000e),0);
/* 0021a184: lh v1,0x12(s1) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000012)));
/* 0021a188: swl v0,0x19(s0) */ partial_word_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000019),1);
/* 0021a18c: swr v0,0x16(s0) */ partial_word_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000016),0);
/* 0021a190: sh v1,0x1a(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000001a),(uint16_t)c->r[3]);
/* 0021a194: ldl v0,0x23(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000023),1);
/* 0021a198: ldr v0,0x1c(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x0000001c),0);
/* 0021a19c: ldl v1,0x2b(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x0000002b),1);
/* 0021a1a0: ldr v1,0x24(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000024),0);
/* 0021a1a4: ldl a0,0x33(s1) */ c->r[4]=partial_load(c->r[4],(uint32_t)c->r[17]+UINT32_C(0x00000033),1);
/* 0021a1a8: ldr a0,0x2c(s1) */ c->r[4]=partial_load(c->r[4],(uint32_t)c->r[17]+UINT32_C(0x0000002c),0);
/* 0021a1ac: ldl a2,0x3b(s1) */ c->r[6]=partial_load(c->r[6],(uint32_t)c->r[17]+UINT32_C(0x0000003b),1);
/* 0021a1b0: ldr a2,0x34(s1) */ c->r[6]=partial_load(c->r[6],(uint32_t)c->r[17]+UINT32_C(0x00000034),0);
/* 0021a1b4: sdl v0,0x41(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000041),1);
/* 0021a1b8: sdr v0,0x3a(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x0000003a),0);
/* 0021a1bc: sdl v1,0x49(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x00000049),1);
/* 0021a1c0: sdr v1,0x42(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x00000042),0);
/* 0021a1c4: sdl a0,0x51(s0) */ partial_store(c->r[4],(uint32_t)c->r[16]+UINT32_C(0x00000051),1);
/* 0021a1c8: sdr a0,0x4a(s0) */ partial_store(c->r[4],(uint32_t)c->r[16]+UINT32_C(0x0000004a),0);
/* 0021a1cc: sdl a2,0x59(s0) */ partial_store(c->r[6],(uint32_t)c->r[16]+UINT32_C(0x00000059),1);
/* 0021a1d0: sdr a2,0x52(s0) */ partial_store(c->r[6],(uint32_t)c->r[16]+UINT32_C(0x00000052),0);
/* 0021a1d4: ldl v0,0x43(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000043),1);
/* 0021a1d8: ldr v0,0x3c(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x0000003c),0);
/* 0021a1dc: ldl v1,0x4b(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x0000004b),1);
/* 0021a1e0: ldr v1,0x44(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000044),0);
/* 0021a1e4: sdl v0,0x61(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000061),1);
/* 0021a1e8: sdr v0,0x5a(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x0000005a),0);
/* 0021a1ec: sdl v1,0x69(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x00000069),1);
/* 0021a1f0: sdr v1,0x62(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x00000062),0);
/* 0021a1f4: lw v0,0x14(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000014)));
/* 0021a1f8: lh v1,0x18(s1) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000018)));
/* 0021a1fc: sw v0,0x1c(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x0000001c),(uint32_t)c->r[2]);
/* 0021a200: sh v1,0x20(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000020),(uint16_t)c->r[3]);
/* 0021a204: lhu v0,0x1a(s1) */ c->r[2]=hword((uint32_t)c->r[17]+UINT32_C(0x0000001a));
/* 0021a208: sh v0,0x38(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000038),(uint16_t)c->r[2]);
/* 0021a20c: lwl v0,0x4f(s1) */ c->r[2]=partial_word_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x0000004f),1);
/* 0021a210: lwr v0,0x4c(s1) */ c->r[2]=partial_word_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x0000004c),0);
/* 0021a214: lh v1,0x50(s1) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000050)));
/* 0021a218: swl v0,0x7d(s0) */ partial_word_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x0000007d),1);
/* 0021a21c: swr v0,0x7a(s0) */ partial_word_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x0000007a),0);
/* 0021a220: sh v1,0x7e(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x0000007e),(uint16_t)c->r[3]);
/* 0021a224: lwl v0,0x55(s1) */ c->r[2]=partial_word_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000055),1);
/* 0021a228: lwr v0,0x52(s1) */ c->r[2]=partial_word_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000052),0);
/* 0021a22c: lh v1,0x56(s1) */ c->r[3]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000056)));
/* 0021a230: swl v0,0x83(s0) */ partial_word_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000083),1);
/* 0021a234: swr v0,0x80(s0) */ partial_word_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000080),0);
/* 0021a238: sh v1,0x84(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x00000084),(uint16_t)c->r[3]);
/* 0021a23c: ldl v0,0x5f(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x0000005f),1);
/* 0021a240: ldr v0,0x58(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000058),0);
/* 0021a244: ldl v1,0x67(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000067),1);
/* 0021a248: ldr v1,0x60(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000060),0);
/* 0021a24c: ldl a0,0x6f(s1) */ c->r[4]=partial_load(c->r[4],(uint32_t)c->r[17]+UINT32_C(0x0000006f),1);
/* 0021a250: ldr a0,0x68(s1) */ c->r[4]=partial_load(c->r[4],(uint32_t)c->r[17]+UINT32_C(0x00000068),0);
/* 0021a254: ldl a2,0x77(s1) */ c->r[6]=partial_load(c->r[6],(uint32_t)c->r[17]+UINT32_C(0x00000077),1);
/* 0021a258: ldr a2,0x70(s1) */ c->r[6]=partial_load(c->r[6],(uint32_t)c->r[17]+UINT32_C(0x00000070),0);
/* 0021a25c: sdl v0,0x8d(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x0000008d),1);
/* 0021a260: sdr v0,0x86(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x00000086),0);
/* 0021a264: sdl v1,0x95(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x00000095),1);
/* 0021a268: sdr v1,0x8e(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x0000008e),0);
/* 0021a26c: sdl a0,0x9d(s0) */ partial_store(c->r[4],(uint32_t)c->r[16]+UINT32_C(0x0000009d),1);
/* 0021a270: sdr a0,0x96(s0) */ partial_store(c->r[4],(uint32_t)c->r[16]+UINT32_C(0x00000096),0);
/* 0021a274: sdl a2,0xa5(s0) */ partial_store(c->r[6],(uint32_t)c->r[16]+UINT32_C(0x000000a5),1);
/* 0021a278: sdr a2,0x9e(s0) */ partial_store(c->r[6],(uint32_t)c->r[16]+UINT32_C(0x0000009e),0);
/* 0021a27c: ldl v0,0x7f(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x0000007f),1);
/* 0021a280: ldr v0,0x78(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000078),0);
/* 0021a284: ldl v1,0x87(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000087),1);
/* 0021a288: ldr v1,0x80(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000080),0);
/* 0021a28c: sdl v0,0xad(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x000000ad),1);
/* 0021a290: sdr v0,0xa6(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x000000a6),0);
/* 0021a294: sdl v1,0xb5(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x000000b5),1);
/* 0021a298: sdr v1,0xae(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x000000ae),0);
/* 0021a29c: ldl v0,0x8f(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x0000008f),1);
/* 0021a2a0: ldr v0,0x88(s1) */ c->r[2]=partial_load(c->r[2],(uint32_t)c->r[17]+UINT32_C(0x00000088),0);
/* 0021a2a4: ldl v1,0x97(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000097),1);
/* 0021a2a8: ldr v1,0x90(s1) */ c->r[3]=partial_load(c->r[3],(uint32_t)c->r[17]+UINT32_C(0x00000090),0);
/* 0021a2ac: ldl a0,0x9f(s1) */ c->r[4]=partial_load(c->r[4],(uint32_t)c->r[17]+UINT32_C(0x0000009f),1);
/* 0021a2b0: ldr a0,0x98(s1) */ c->r[4]=partial_load(c->r[4],(uint32_t)c->r[17]+UINT32_C(0x00000098),0);
/* 0021a2b4: sdl v0,0xbd(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x000000bd),1);
/* 0021a2b8: sdr v0,0xb6(s0) */ partial_store(c->r[2],(uint32_t)c->r[16]+UINT32_C(0x000000b6),0);
/* 0021a2bc: sdl v1,0xc5(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x000000c5),1);
/* 0021a2c0: sdr v1,0xbe(s0) */ partial_store(c->r[3],(uint32_t)c->r[16]+UINT32_C(0x000000be),0);
/* 0021a2c4: sdl a0,0xcd(s0) */ partial_store(c->r[4],(uint32_t)c->r[16]+UINT32_C(0x000000cd),1);
/* 0021a2c8: sdr a0,0xc6(s0) */ partial_store(c->r[4],(uint32_t)c->r[16]+UINT32_C(0x000000c6),0);
/* 0021a2cc: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0021a2d0: lhu a0,0xa0(s1) */ c->r[4]=hword((uint32_t)c->r[17]+UINT32_C(0x000000a0));
/* 0021a2d4: and v0,v0,a1 */ c->r[2]=c->r[2]&c->r[5];
/* 0021a2d8: sw v0,0x0(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000000),(uint32_t)c->r[2]);
/* 0021a2dc: sh a0,0xce(s0) */ sh((uint32_t)c->r[16]+UINT32_C(0x000000ce),(uint16_t)c->r[4]);
/* 0021a2e0: lw v1,0xa4(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x000000a4)));
/* 0021a2e4: or v0,v0,v1 */ c->r[2]=c->r[2]|c->r[3];
/* 0021a2e8: sw v0,0x0(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000000),(uint32_t)c->r[2]);
/* 0021a2ec: lw v1,0xac(s1) */ c->r[3]=sx(word((uint32_t)c->r[17]+UINT32_C(0x000000ac)));
/* 0021a2f0: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0021a2f4: sw v1,0xd8(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x000000d8),(uint32_t)c->r[3]);
/* 0021a2f8: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0021a2fc: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0021a300: jr ra */ /* delay 0021a304 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_0021a308(CompendiumRestoreValues *c){
/* 0021a308: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 0021a30c: move t3,a0 */ c->r[11]=c->r[4];
/* 0021a310: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0021a314: move t2,a1 */ c->r[10]=c->r[5];
/* 0021a318: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0021a31c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0021a320: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0021a324: lw v1,0x0(t3) */ c->r[3]=sx(word((uint32_t)c->r[11]+UINT32_C(0x00000000)));
/* 0021a328: lw a0,0xa4(t2) */ c->r[4]=sx(word((uint32_t)c->r[10]+UINT32_C(0x000000a4)));
/* 0021a32c: andi v1,v1,0x240 */ c->r[3]=c->r[3]&UINT64_C(0x240);
/* 0021a330: bne a0,v1,0x0021a4e4 */ {int taken=(c->r[4]!=c->r[3]);/* delay 0021a334 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0021a4e4;}}
/* 0021a338: lhu a0,0x4(t2) */ c->r[4]=hword((uint32_t)c->r[10]+UINT32_C(0x00000004));
/* 0021a33c: lhu v1,0x8(t3) */ c->r[3]=hword((uint32_t)c->r[11]+UINT32_C(0x00000008));
/* 0021a340: bne a0,v1,0x0021a4e4 */ {int taken=(c->r[4]!=c->r[3]);/* delay 0021a344 */ c->r[2]=sx(UINT32_C(0x00000002));if(taken){goto L_0021a4e4;}}
/* 0021a348: lhu a0,0x6(t2) */ c->r[4]=hword((uint32_t)c->r[10]+UINT32_C(0x00000006));
/* 0021a34c: lhu v1,0xc(t3) */ c->r[3]=hword((uint32_t)c->r[11]+UINT32_C(0x0000000c));
/* 0021a350: bne a0,v1,0x0021a4e4 */ {int taken=(c->r[4]!=c->r[3]);/* delay 0021a354 */ c->r[2]=sx(UINT32_C(0x00000003));if(taken){goto L_0021a4e4;}}
/* 0021a358: lw a0,0x8(t2) */ c->r[4]=sx(word((uint32_t)c->r[10]+UINT32_C(0x00000008)));
/* 0021a35c: lw v1,0x10(t3) */ c->r[3]=sx(word((uint32_t)c->r[11]+UINT32_C(0x00000010)));
/* 0021a360: bne a0,v1,0x0021a4e4 */ {int taken=(c->r[4]!=c->r[3]);/* delay 0021a364 */ c->r[2]=sx(UINT32_C(0x00000004));if(taken){goto L_0021a4e4;}}
/* 0021a368: lhu a0,0xc(t2) */ c->r[4]=hword((uint32_t)c->r[10]+UINT32_C(0x0000000c));
/* 0021a36c: lhu v1,0x14(t3) */ c->r[3]=hword((uint32_t)c->r[11]+UINT32_C(0x00000014));
/* 0021a370: bne a0,v1,0x0021a4e4 */ {int taken=(c->r[4]!=c->r[3]);/* delay 0021a374 */ c->r[2]=sx(UINT32_C(0x00000005));if(taken){goto L_0021a4e4;}}
/* 0021a378: lui v0,0x33 */ c->r[2]=sx(UINT32_C(0x00330000));
/* 0021a37c: move t4,zero */ c->r[12]=c->r[0];
/* 0021a380: addiu s3,v0,0x22c0 */ c->r[19]=sx((uint32_t)c->r[2]+UINT32_C(0x000022c0));
/* 0021a384: addiu s2,t2,0xe */ c->r[18]=sx((uint32_t)c->r[10]+UINT32_C(0x0000000e));
/* 0021a388: addiu s1,t3,0x6 */ c->r[17]=sx((uint32_t)c->r[11]+UINT32_C(0x00000006));
/* 0021a38c: addiu s0,t2,0x4 */ c->r[16]=sx((uint32_t)c->r[10]+UINT32_C(0x00000004));
/* 0021a390: addiu t9,t3,0xc */ c->r[25]=sx((uint32_t)c->r[11]+UINT32_C(0x0000000c));
/* 0021a394: addiu t8,t2,0x2 */ c->r[24]=sx((uint32_t)c->r[10]+UINT32_C(0x00000002));
/* 0021a398: addu v0,t4,s3 */ c->r[2]=sx((uint32_t)c->r[12]+(uint32_t)c->r[19]);
/* 0021a39c: nop  */ (void)0;
L_0021a3a0:;
/* 0021a3a0: addiu t4,t4,0x1 */ c->r[12]=sx((uint32_t)c->r[12]+UINT32_C(0x00000001));
/* 0021a3a4: lb a2,0x0(v0) */ c->r[6]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[2]+UINT32_C(0x00000000)));
/* 0021a3a8: slti t7,t4,0x5 */ c->r[15]=less(c->r[12],sx(UINT32_C(0x00000005)));
/* 0021a3ac: addiu v0,a2,0x10 */ c->r[2]=sx((uint32_t)c->r[6]+UINT32_C(0x00000010));
/* 0021a3b0: addu a0,s2,a2 */ c->r[4]=sx((uint32_t)c->r[18]+(uint32_t)c->r[6]);
/* 0021a3b4: addu a1,s1,v0 */ c->r[5]=sx((uint32_t)c->r[17]+(uint32_t)c->r[2]);
/* 0021a3b8: addu t1,t9,v0 */ c->r[9]=sx((uint32_t)c->r[25]+(uint32_t)c->r[2]);
/* 0021a3bc: addu a3,s0,v0 */ c->r[7]=sx((uint32_t)c->r[16]+(uint32_t)c->r[2]);
/* 0021a3c0: lb v0,0x0(a1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 0021a3c4: lb v1,0x0(a0) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[4]+UINT32_C(0x00000000)));
/* 0021a3c8: addu t6,a2,t3 */ c->r[14]=sx((uint32_t)c->r[6]+(uint32_t)c->r[11]);
/* 0021a3cc: addu t5,a2,t8 */ c->r[13]=sx((uint32_t)c->r[6]+(uint32_t)c->r[24]);
/* 0021a3d0: bne v1,v0,0x0021a4c8 */ {int taken=(c->r[3]!=c->r[2]);/* delay 0021a3d4 */ c->r[8]=sx((uint32_t)c->r[6]+(uint32_t)c->r[10]);if(taken){goto L_0021a4c8;}}
/* 0021a3d8: lb v1,0x0(a3) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[7]+UINT32_C(0x00000000)));
/* 0021a3dc: lb v0,0x0(t1) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[9]+UINT32_C(0x00000000)));
/* 0021a3e0: bne v1,v0,0x0021a4e4 */ {int taken=(c->r[3]!=c->r[2]);/* delay 0021a3e4 */ c->r[2]=sx(UINT32_C(0x00000007));if(taken){goto L_0021a4e4;}}
/* 0021a3e8: addiu a1,t3,0xa */ c->r[5]=sx((uint32_t)c->r[11]+UINT32_C(0x0000000a));
/* 0021a3ec: lb v0,0x4c(t0) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[8]+UINT32_C(0x0000004c)));
/* 0021a3f0: addu v1,a2,a1 */ c->r[3]=sx((uint32_t)c->r[6]+(uint32_t)c->r[5]);
/* 0021a3f4: lb a0,0x70(v1) */ c->r[4]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[3]+UINT32_C(0x00000070)));
/* 0021a3f8: bne v0,a0,0x0021a4e4 */ {int taken=(c->r[2]!=c->r[4]);/* delay 0021a3fc */ c->r[2]=sx(UINT32_C(0x00000008));if(taken){goto L_0021a4e4;}}
/* 0021a400: lb v1,0x50(t5) */ c->r[3]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[13]+UINT32_C(0x00000050)));
/* 0021a404: lb v0,0x80(t6) */ c->r[2]=sx((uint32_t)(int32_t)(int8_t)*at((uint32_t)c->r[14]+UINT32_C(0x00000080)));
/* 0021a408: bnel v1,v0,0x0021a4e4 */ {int taken=(c->r[3]!=c->r[2]);if(taken){/* delay 0021a40c */ c->r[2]=sx(UINT32_C(0x00000009));goto L_0021a4e4;}}
/* 0021a410: bne t7,zero,0x0021a3a0 */ {int taken=(c->r[15]!=c->r[0]);/* delay 0021a414 */ c->r[2]=sx((uint32_t)c->r[12]+(uint32_t)c->r[19]);if(taken){goto L_0021a3a0;}}
/* 0021a418: lhu a0,0x1a(t2) */ c->r[4]=hword((uint32_t)c->r[10]+UINT32_C(0x0000001a));
/* 0021a41c: lhu v1,0x38(t3) */ c->r[3]=hword((uint32_t)c->r[11]+UINT32_C(0x00000038));
/* 0021a420: bne a0,v1,0x0021a4e4 */ {int taken=(c->r[4]!=c->r[3]);/* delay 0021a424 */ c->r[2]=sx(UINT32_C(0x0000000a));if(taken){goto L_0021a4e4;}}
/* 0021a428: lhu a3,0x1a(t2) */ c->r[7]=hword((uint32_t)c->r[10]+UINT32_C(0x0000001a));
/* 0021a42c: beq a3,zero,0x0021a4ac */ {int taken=(c->r[7]==c->r[0]);/* delay 0021a430 */ c->r[12]=c->r[0];if(taken){goto L_0021a4ac;}}
/* 0021a434: move t5,a1 */ c->r[13]=c->r[5];
/* 0021a438: addiu t1,t3,0x3a */ c->r[9]=sx((uint32_t)c->r[11]+UINT32_C(0x0000003a));
/* 0021a43c: addiu t0,t2,0x1c */ c->r[8]=sx((uint32_t)c->r[10]+UINT32_C(0x0000001c));
L_0021a440:;
/* 0021a440: move a2,zero */ c->r[6]=c->r[0];
/* 0021a444: slt a0,a2,a3 */ c->r[4]=less(c->r[6],c->r[7]);
/* 0021a448: beq a0,zero,0x0021a494 */ {int taken=(c->r[4]==c->r[0]);/* delay 0021a44c */ c->r[5]=hword((uint32_t)c->r[8]+UINT32_C(0x00000000));if(taken){goto L_0021a494;}}
/* 0021a450: lhu v0,0x0(t1) */ c->r[2]=hword((uint32_t)c->r[9]+UINT32_C(0x00000000));
/* 0021a454: beq a1,v0,0x0021a48c */ {int taken=(c->r[5]==c->r[2]);/* delay 0021a458 */ (void)0;if(taken){goto L_0021a48c;}}
/* 0021a45c: addiu v1,t5,0x30 */ c->r[3]=sx((uint32_t)c->r[13]+UINT32_C(0x00000030));
/* 0021a460: addiu a2,a2,0x1 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));
/* 0021a464: nop  */ (void)0;
L_0021a468:;
/* 0021a468: slt a0,a2,a3 */ c->r[4]=less(c->r[6],c->r[7]);
/* 0021a46c: beq a0,zero,0x0021a494 */ {int taken=(c->r[4]==c->r[0]);/* delay 0021a470 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000002));if(taken){goto L_0021a494;}}
/* 0021a474: lhu v0,0x0(v1) */ c->r[2]=hword((uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 0021a478: nop  */ (void)0;
/* 0021a47c: nop  */ (void)0;
/* 0021a480: nop  */ (void)0;
/* 0021a484: bnel a1,v0,0x0021a468 */ {int taken=(c->r[5]!=c->r[2]);if(taken){/* delay 0021a488 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000001));goto L_0021a468;}}
L_0021a48c:;
/* 0021a48c: bnel a0,zero,0x0021a4a0 */ {int taken=(c->r[4]!=c->r[0]);if(taken){/* delay 0021a490 */ c->r[12]=sx((uint32_t)c->r[12]+UINT32_C(0x00000001));goto L_0021a4a0;}}
L_0021a494:;
/* 0021a494: b 0x0021a4e4 */ /* delay 0021a498 */ c->r[2]=sx(UINT32_C(0x0000000b));goto L_0021a4e4;
L_0021a4a0:;
/* 0021a4a0: slt v0,t4,a3 */ c->r[2]=less(c->r[12],c->r[7]);
/* 0021a4a4: bne v0,zero,0x0021a440 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0021a4a8 */ c->r[8]=sx((uint32_t)c->r[8]+UINT32_C(0x00000002));if(taken){goto L_0021a440;}}
L_0021a4ac:;
/* 0021a4ac: lhu v1,0xa0(t2) */ c->r[3]=hword((uint32_t)c->r[10]+UINT32_C(0x000000a0));
/* 0021a4b0: lhu v0,0xce(t3) */ c->r[2]=hword((uint32_t)c->r[11]+UINT32_C(0x000000ce));
/* 0021a4b4: beq v1,v0,0x0021a4d0 */ {int taken=(c->r[3]==c->r[2]);/* delay 0021a4b8 */ c->r[2]=sx(UINT32_C(0x0000000c));if(taken){goto L_0021a4d0;}}
/* 0021a4bc: b 0x0021a4e8 */ /* delay 0021a4c0 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0021a4e8;
L_0021a4c8:;
/* 0021a4c8: b 0x0021a4e4 */ /* delay 0021a4cc */ c->r[2]=sx(UINT32_C(0x00000006));goto L_0021a4e4;
L_0021a4d0:;
/* 0021a4d0: lw v1,0xac(t2) */ c->r[3]=sx(word((uint32_t)c->r[10]+UINT32_C(0x000000ac)));
/* 0021a4d4: li v0,0xd */ c->r[2]=sx(UINT32_C(0x0000000d));
/* 0021a4d8: lw a0,0xd8(t3) */ c->r[4]=sx(word((uint32_t)c->r[11]+UINT32_C(0x000000d8)));
/* 0021a4dc: xor v1,v1,a0 */ c->r[3]=c->r[3]^c->r[4];
/* 0021a4e0: movz v0,zero,v1 */ if(c->r[3]==0){c->r[2]=c->r[0];}
L_0021a4e4:;
/* 0021a4e4: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0021a4e8:;
/* 0021a4e8: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0021a4ec: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0021a4f0: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0021a4f4: jr ra */ /* delay 0021a4f8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_00216b20(CompendiumRestoreValues *c){
/* 00216b20: lw v0,-0x5750(gp) */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 00216b24: lui t0,0x1 */ c->r[8]=sx(UINT32_C(0x00010000));
/* 00216b28: addu t0,t0,v0 */ c->r[8]=sx((uint32_t)c->r[8]+(uint32_t)c->r[2]);
/* 00216b2c: lw t0,0x1e80(t0) */ c->r[8]=sx(word((uint32_t)c->r[8]+UINT32_C(0x00001e80)));
/* 00216b30: lui a2,0x1 */ c->r[6]=sx(UINT32_C(0x00010000));
/* 00216b34: ori a2,a2,0x1e90 */ c->r[6]=c->r[6]|UINT64_C(0x1e90);
/* 00216b38: addu a2,a2,v0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[2]);
/* 00216b3c: blez t0,0x00216b6c */ {int taken=((neg(c->r[8])||!c->r[8]));/* delay 00216b40 */ c->r[7]=c->r[0];if(taken){goto L_00216b6c;}}
/* 00216b44: lhu v1,0x0(a2) */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));
L_00216b48:;
/* 00216b48: addiu a2,a2,0xb0 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x000000b0));
/* 00216b4c: move v0,a3 */ c->r[2]=c->r[7];
/* 00216b50: addiu a3,a3,0x1 */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0x00000001));
/* 00216b54: beq a0,v1,0x00216b70 */ {int taken=(c->r[4]==c->r[3]);/* delay 00216b58 */ c->r[5]=less(c->r[7],c->r[8]);if(taken){goto L_00216b70;}}
/* 00216b5c: nop  */ (void)0;
/* 00216b60: nop  */ (void)0;
/* 00216b64: bnel a1,zero,0x00216b48 */ {int taken=(c->r[5]!=c->r[0]);if(taken){/* delay 00216b68 */ c->r[3]=hword((uint32_t)c->r[6]+UINT32_C(0x00000000));goto L_00216b48;}}
L_00216b6c:;
/* 00216b6c: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
L_00216b70:;
/* 00216b70: jr ra */ /* delay 00216b74 */ (void)0;return;
}
static CompendiumRestoreValues begin(void){CompendiumRestoreValues c={0};c.r[28]=UINT64_C(0x00554170);c.r[29]=nocturneCompendiumRestoreStackPointer();return c;}
uint64_t ps2CompendiumRestore_00216BF0(void){CompendiumRestoreValues c=begin();body_00216bf0(&c);nocturneCompendiumRestoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2CompendiumRestore_00219318(uint64_t p0){CompendiumRestoreValues c=begin();c.r[4]=p0;body_00219318(&c);nocturneCompendiumRestoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2CompendiumRestore_0021A0B8(uint64_t p0,uint64_t p1){CompendiumRestoreValues c=begin();c.r[4]=p0;c.r[5]=p1;body_0021a0b8(&c);nocturneCompendiumRestoreSetStackPointer((uint32_t)c.r[29]);}
void ps2CompendiumRestore_0021A118(uint64_t p0,uint64_t p1){CompendiumRestoreValues c=begin();c.r[4]=p0;c.r[5]=p1;body_0021a118(&c);nocturneCompendiumRestoreSetStackPointer((uint32_t)c.r[29]);}
uint64_t ps2CompendiumRestore_0021A308(uint64_t p0,uint64_t p1){CompendiumRestoreValues c=begin();c.r[4]=p0;c.r[5]=p1;body_0021a308(&c);nocturneCompendiumRestoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
uint64_t ps2CompendiumRestore_00216B20(uint64_t p0){CompendiumRestoreValues c=begin();c.r[4]=p0;body_00216b20(&c);nocturneCompendiumRestoreSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
