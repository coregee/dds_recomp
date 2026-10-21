/* Complete formation8/1274 original instructions; fixed native PCs.
 * Real guest frames, scalar EE-FPU and shared VF10; typed real callees.
 * No managed geometry substitution, synthetic model or unit result. */
#include "battle_formation.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "ee_vu_rotation.h"
#include <stdlib.h>
#include "battle_action_printf_frames.h"
#include "battle_action_scale_lookup_frames.h"
#include "battle_action_status.h"
#include "battle_effect_copy.h"
#include "battle_panel_support.h"
#include "battle_presentation.h"
#include "battle_targeting.h"
#include "battle_work_access.h"
#include "combat_calculation.h"
#include "model_motion_sampling.h"
#include "rst_level_chain.h"
#include "unit_progression.h"
#include <string.h>
typedef struct BattleFormationValues {uint64_t r[32],upper[32];uint32_t f[32],condition;} BattleFormationValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleFormationAddress(a);}
static uint16_t hword(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}

/* All17 selected GPR128 stores have an immediately preceding same-register
 * LQ, so no uninitialized incoming upper lane is supplied by this structure.
 * LQ/SQ use the architectural align-down address. VF transfers use the
 * existing actual shared VU bank, including real quaternion callee effects. */
static void lq(BattleFormationValues *c,unsigned reg,uint32_t address){
 uint32_t a=address&~UINT32_C(15);c->r[reg]=quad(a);c->upper[reg]=quad(a+8u);
}
static void sq(BattleFormationValues *c,unsigned reg,uint32_t address){
 uint32_t a=address&~UINT32_C(15);sd(a,c->r[reg]);sd(a+8u,c->upper[reg]);
}
static void lqc2(unsigned reg,uint32_t address){uint32_t v[4];memcpy(v,at(address),16);EE_ROT_VU_WRITE(reg,v);}
static void sqc2(unsigned reg,uint32_t address){uint32_t v[4];EE_ROT_VU_READ(reg,v);memcpy(at(address),v,16);}

static void body_0024d490(BattleFormationValues *c);
static void body_0024d550(BattleFormationValues *c);
static void body_0024d8c0(BattleFormationValues *c);
static void body_0024e178(BattleFormationValues *c);
static void body_00259740(BattleFormationValues *c);
static void body_0028a2e0(BattleFormationValues *c);
static void body_0028a340(BattleFormationValues *c);
static void body_0028a758(BattleFormationValues *c);

static void body_0024d490(BattleFormationValues *c){
/* 0024d490: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 0024d494: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0024d498: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0024d49c: move s1,a0 */ c->r[17]=c->r[4];
/* 0024d4a0: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0024d4a4: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0024d4a8: move s3,a1 */ c->r[19]=c->r[5];
/* 0024d4ac: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 0024d4b0: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x0024d4b8);/* delay 0024d4b4 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000092)));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d4b8: move s0,v0 */ c->r[16]=c->r[2];
/* 0024d4bc: jal 0x00259a30 */ c->r[31]=UINT64_C(0x0024d4c4);/* delay 0024d4c0 */ c->r[4]=c->r[16];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitID(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d4c4: move a0,s0 */ c->r[4]=c->r[16];
/* 0024d4c8: jal 0x00259a60 */ c->r[31]=UINT64_C(0x0024d4d0);/* delay 0024d4cc */ c->r[18]=c->r[2];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatModelScaleDescriptor_00259A60(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d4d0: sll v1,s3,0x3 */ c->r[3]=sx((uint32_t)c->r[19]<<3u);
/* 0024d4d4: lwc1 f1,0x5c(s1) */ c->f[1]=word((uint32_t)c->r[17]+UINT32_C(0x0000005c));
/* 0024d4d8: subu v1,v1,s3 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[19]);
/* 0024d4dc: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 0024d4e0: addu a0,v1,v0 */ c->r[4]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0024d4e4: addiu v1,v1,0x30 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000030));
/* 0024d4e8: lwc1 f0,0x38(a0) */ c->f[0]=word((uint32_t)c->r[4]+UINT32_C(0x00000038));
/* 0024d4ec: addu a1,v0,v1 */ c->r[5]=sx((uint32_t)c->r[2]+(uint32_t)c->r[3]);
/* 0024d4f0: move v0,a1 */ c->r[2]=c->r[5];
/* 0024d4f4: mul.S f0,f0,f1 */ c->f[0]=EE_FPU_MUL_S(c->f[0],c->f[1]);
/* 0024d4f8: swc1 f0,0x58(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000058),c->f[0]);
/* 0024d4fc: lwc1 f1,0xc(a1) */ c->f[1]=word((uint32_t)c->r[5]+UINT32_C(0x0000000c));
/* 0024d500: swc1 f1,0x68(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000068),c->f[1]);
/* 0024d504: lwc1 f0,0x10(v0) */ c->f[0]=word((uint32_t)c->r[2]+UINT32_C(0x00000010));
/* 0024d508: bne s2,zero,0x0024d528 */ {int taken=(c->r[18]!=c->r[0]);/* delay 0024d50c */ sw((uint32_t)c->r[17]+UINT32_C(0x0000006c),c->f[0]);if(taken){goto L_0024d528;}}
/* 0024d510: lui v0,0x35 */ c->r[2]=sx(UINT32_C(0x00350000));
/* 0024d514: addu v0,v0,s3 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[19]);
/* 0024d518: lbu v0,-0x6c60(v0) */ c->r[2]=*at((uint32_t)c->r[2]+UINT32_C(0xffff93a0));
/* 0024d51c: b 0x0024d538 */ /* delay 0024d520 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0024d538;
L_0024d528:;
/* 0024d528: lui v0,0x35 */ c->r[2]=sx(UINT32_C(0x00350000));
/* 0024d52c: addu v0,v0,s3 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[19]);
/* 0024d530: lbu v0,-0xe40(v0) */ c->r[2]=*at((uint32_t)c->r[2]+UINT32_C(0xfffff1c0));
/* 0024d534: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
L_0024d538:;
/* 0024d538: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0024d53c: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0024d540: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0024d544: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0024d548: jr ra */ /* delay 0024d54c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_0024d550(BattleFormationValues *c){
/* 0024d550: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 0024d554: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0024d558: move s1,a2 */ c->r[17]=c->r[6];
/* 0024d55c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0024d560: move s2,a0 */ c->r[18]=c->r[4];
/* 0024d564: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 0024d568: move s4,zero */ c->r[20]=c->r[0];
/* 0024d56c: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 0024d570: move s5,a3 */ c->r[21]=c->r[7];
/* 0024d574: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 0024d578: move s6,zero */ c->r[22]=c->r[0];
/* 0024d57c: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 0024d580: li s7,-0x1 */ c->r[23]=sx(UINT32_C(0xffffffff));
/* 0024d584: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0024d588: move a2,zero */ c->r[6]=c->r[0];
/* 0024d58c: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0024d590: beq a1,zero,0x0024d650 */ {int taken=(c->r[5]==c->r[0]);/* delay 0024d594 */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);if(taken){goto L_0024d650;}}
/* 0024d598: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 0024d59c: bne a1,v0,0x0024d704 */ {int taken=(c->r[5]!=c->r[2]);/* delay 0024d5a0 */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000010)));if(taken){goto L_0024d704;}}
/* 0024d5a4: move a0,v1 */ c->r[4]=c->r[3];
/* 0024d5a8: lhu v0,0x200(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x00000200));
/* 0024d5ac: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0024d5b0: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 0024d5b4: bne v0,zero,0x0024d5c8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0024d5b8 */ c->r[16]=sx(UINT32_C(0x00000004));if(taken){goto L_0024d5c8;}}
/* 0024d5bc: b 0x0024d5f4 */ /* delay 0024d5c0 */ c->r[23]=sx(UINT32_C(0x00000004));goto L_0024d5f4;
L_0024d5c8:;
/* 0024d5c8: addiu s0,s0,0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));
L_0024d5cc:;
/* 0024d5cc: sll v0,s0,0x7 */ c->r[2]=sx((uint32_t)c->r[16]<<7u);
/* 0024d5d0: slti v1,s0,0xe */ c->r[3]=less(c->r[16],sx(UINT32_C(0x0000000e)));
/* 0024d5d4: beq v1,zero,0x0024d5f4 */ {int taken=(c->r[3]==c->r[0]);/* delay 0024d5d8 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);if(taken){goto L_0024d5f4;}}
/* 0024d5dc: lhu v0,0x0(v0) */ c->r[2]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 0024d5e0: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0024d5e4: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 0024d5e8: bnel v0,zero,0x0024d5cc */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0024d5ec */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));goto L_0024d5cc;}}
/* 0024d5f0: move s7,s0 */ c->r[23]=c->r[16];
L_0024d5f4:;
/* 0024d5f4: sll s0,s1,0x4 */ c->r[16]=sx((uint32_t)c->r[17]<<4u);
/* 0024d5f8: lw v0,0x8(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000008)));
/* 0024d5fc: subu s0,s0,s1 */ c->r[16]=sx((uint32_t)c->r[16]-(uint32_t)c->r[17]);
/* 0024d600: sll s0,s0,0x2 */ c->r[16]=sx((uint32_t)c->r[16]<<2u);
/* 0024d604: subu s0,s0,s1 */ c->r[16]=sx((uint32_t)c->r[16]-(uint32_t)c->r[17]);
/* 0024d608: sll s0,s0,0x2 */ c->r[16]=sx((uint32_t)c->r[16]<<2u);
/* 0024d60c: addu s4,v0,s0 */ c->r[20]=sx((uint32_t)c->r[2]+(uint32_t)c->r[16]);
/* 0024d610: jal 0x00259a30 */ c->r[31]=UINT64_C(0x0024d618);/* delay 0024d614 */ c->r[4]=c->r[20];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitID(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d618: jal 0x00259a60 */ c->r[31]=UINT64_C(0x0024d620);/* delay 0024d61c */ c->r[4]=c->r[20];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatModelScaleDescriptor_00259A60(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d620: li a2,0x3 */ c->r[6]=sx(UINT32_C(0x00000003));
/* 0024d624: lw a0,0x8(s2) */ c->r[4]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000008)));
/* 0024d628: move s6,v0 */ c->r[22]=c->r[2];
/* 0024d62c: lhu v0,0x1a(s2) */ c->r[2]=hword((uint32_t)c->r[18]+UINT32_C(0x0000001a));
/* 0024d630: addu s0,s0,a0 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[4]);
/* 0024d634: lw v1,0x0(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0024d638: addiu v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000001));
/* 0024d63c: sh v0,0x1a(s2) */ sh((uint32_t)c->r[18]+UINT32_C(0x0000001a),(uint16_t)c->r[2]);
/* 0024d640: ori v1,v1,0x22 */ c->r[3]=c->r[3]|UINT64_C(0x22);
/* 0024d644: b 0x0024d700 */ /* delay 0024d648 */ sw((uint32_t)c->r[16]+UINT32_C(0x00000000),(uint32_t)c->r[3]);goto L_0024d700;
L_0024d650:;
/* 0024d650: lw v1,0x10(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000010)));
/* 0024d654: move a0,v1 */ c->r[4]=c->r[3];
/* 0024d658: lhu v0,0x0(a0) */ c->r[2]=hword((uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 0024d65c: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0024d660: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 0024d664: bne v0,zero,0x0024d678 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0024d668 */ c->r[16]=c->r[0];if(taken){goto L_0024d678;}}
/* 0024d66c: b 0x0024d6a4 */ /* delay 0024d670 */ c->r[23]=c->r[0];goto L_0024d6a4;
L_0024d678:;
/* 0024d678: addiu s0,s0,0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));
L_0024d67c:;
/* 0024d67c: sll v0,s0,0x7 */ c->r[2]=sx((uint32_t)c->r[16]<<7u);
/* 0024d680: slti v1,s0,0x4 */ c->r[3]=less(c->r[16],sx(UINT32_C(0x00000004)));
/* 0024d684: beq v1,zero,0x0024d6a4 */ {int taken=(c->r[3]==c->r[0]);/* delay 0024d688 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);if(taken){goto L_0024d6a4;}}
/* 0024d68c: lhu v0,0x0(v0) */ c->r[2]=hword((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 0024d690: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0024d694: andi v0,v0,0xffff */ c->r[2]=c->r[2]&UINT64_C(0xffff);
/* 0024d698: bnel v0,zero,0x0024d67c */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 0024d69c */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));goto L_0024d67c;}}
/* 0024d6a0: move s7,s0 */ c->r[23]=c->r[16];
L_0024d6a4:;
/* 0024d6a4: sll s0,s1,0x4 */ c->r[16]=sx((uint32_t)c->r[17]<<4u);
/* 0024d6a8: lw v0,-0x5750(gp) */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 0024d6ac: subu s0,s0,s1 */ c->r[16]=sx((uint32_t)c->r[16]-(uint32_t)c->r[17]);
/* 0024d6b0: sll s0,s0,0x2 */ c->r[16]=sx((uint32_t)c->r[16]<<2u);
/* 0024d6b4: subu s0,s0,s1 */ c->r[16]=sx((uint32_t)c->r[16]-(uint32_t)c->r[17]);
/* 0024d6b8: sll s0,s0,0x2 */ c->r[16]=sx((uint32_t)c->r[16]<<2u);
/* 0024d6bc: addu v0,v0,s0 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[16]);
/* 0024d6c0: addiu s4,v0,0xa54 */ c->r[20]=sx((uint32_t)c->r[2]+UINT32_C(0x00000a54));
/* 0024d6c4: jal 0x00259a30 */ c->r[31]=UINT64_C(0x0024d6cc);/* delay 0024d6c8 */ c->r[4]=c->r[20];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetUnitID(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d6cc: jal 0x00259a60 */ c->r[31]=UINT64_C(0x0024d6d4);/* delay 0024d6d0 */ c->r[4]=c->r[20];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=ps2CombatModelScaleDescriptor_00259A60(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d6d4: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0024d6d8: move s6,v0 */ c->r[22]=c->r[2];
/* 0024d6dc: lw v0,-0x5750(gp) */ c->r[2]=sx(word((uint32_t)c->r[28]+UINT32_C(0xffffa8b0)));
/* 0024d6e0: lhu v1,0x18(s2) */ c->r[3]=hword((uint32_t)c->r[18]+UINT32_C(0x00000018));
/* 0024d6e4: addu s0,s0,v0 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[2]);
/* 0024d6e8: addiu s0,s0,0xa54 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000a54));
/* 0024d6ec: addiu v1,v1,0x1 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000001));
/* 0024d6f0: lw v0,0x0(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000000)));
/* 0024d6f4: sh v1,0x18(s2) */ sh((uint32_t)c->r[18]+UINT32_C(0x00000018),(uint16_t)c->r[3]);
/* 0024d6f8: ori v0,v0,0x2 */ c->r[2]=c->r[2]|UINT64_C(0x2);
/* 0024d6fc: sw v0,0x0(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000000),(uint32_t)c->r[2]);
L_0024d700:;
/* 0024d700: lw v1,0x10(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000010)));
L_0024d704:;
/* 0024d704: sll s3,s7,0x7 */ c->r[19]=sx((uint32_t)c->r[23]<<7u);
/* 0024d708: li s0,0x13 */ c->r[16]=sx(UINT32_C(0x00000013));
/* 0024d70c: addu v0,s3,v1 */ c->r[2]=sx((uint32_t)c->r[19]+(uint32_t)c->r[3]);
/* 0024d710: sh a2,0x0(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x00000000),(uint16_t)c->r[6]);
/* 0024d714: addiu v1,v0,0x2e */ c->r[3]=sx((uint32_t)c->r[2]+UINT32_C(0x0000002e));
/* 0024d718: sh s1,0x4(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x00000004),(uint16_t)c->r[17]);
/* 0024d71c: sh s5,0x2(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x00000002),(uint16_t)c->r[21]);
L_0024d720:;
/* 0024d720: addiu s0,s0,-0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffffff));
/* 0024d724: sh zero,0x0(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x00000000),(uint16_t)c->r[0]);
/* 0024d728: nop  */ (void)0;
/* 0024d72c: nop  */ (void)0;
/* 0024d730: nop  */ (void)0;
/* 0024d734: bgez s0,0x0024d720 */ {int taken=(!neg(c->r[16]));/* delay 0024d738 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0xfffffffe));if(taken){goto L_0024d720;}}
/* 0024d73c: lw v0,0x0(s4) */ c->r[2]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000000)));
/* 0024d740: andi v0,v0,0x4 */ c->r[2]=c->r[2]&UINT64_C(0x4);
/* 0024d744: beql v0,zero,0x0024d7a4 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0024d748 */ c->r[16]=c->r[0];goto L_0024d7a4;}}
/* 0024d74c: jal 0x00220000 */ c->r[31]=UINT64_C(0x0024d754);/* delay 0024d750 */ (void)0;nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)(int32_t)rstGetEquipHeartsAisyo());nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d754: beq v0,zero,0x0024d7a0 */ {int taken=(c->r[2]==c->r[0]);/* delay 0024d758 */ c->r[2]=sx((uint32_t)c->r[2]<<6u);if(taken){goto L_0024d7a0;}}
/* 0024d75c: lw v1,0x10(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000010)));
/* 0024d760: lui a1,0x3a */ c->r[5]=sx(UINT32_C(0x003a0000));
/* 0024d764: addiu a1,a1,0x7fe0 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00007fe0));
/* 0024d768: addu a1,a1,v0 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[2]);
/* 0024d76c: move s0,zero */ c->r[16]=c->r[0];
/* 0024d770: addu v0,s3,v1 */ c->r[2]=sx((uint32_t)c->r[19]+(uint32_t)c->r[3]);
/* 0024d774: addiu a0,v0,0x30 */ c->r[4]=sx((uint32_t)c->r[2]+UINT32_C(0x00000030));
L_0024d778:;
/* 0024d778: lw v1,0x0(a1) */ c->r[3]=sx(word((uint32_t)c->r[5]+UINT32_C(0x00000000)));
/* 0024d77c: addiu a1,a1,0x4 */ c->r[5]=sx((uint32_t)c->r[5]+UINT32_C(0x00000004));
/* 0024d780: addiu s0,s0,0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));
/* 0024d784: slti v0,s0,0x10 */ c->r[2]=less(c->r[16],sx(UINT32_C(0x00000010)));
/* 0024d788: sw v1,0x0(a0) */ sw((uint32_t)c->r[4]+UINT32_C(0x00000000),(uint32_t)c->r[3]);
/* 0024d78c: bne v0,zero,0x0024d778 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0024d790 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000004));if(taken){goto L_0024d778;}}
/* 0024d794: b 0x0024d7d8 */ /* delay 0024d798 */ c->r[6]=sx((uint32_t)c->r[21]<<4u);goto L_0024d7d8;
L_0024d7a0:;
/* 0024d7a0: move s0,zero */ c->r[16]=c->r[0];
L_0024d7a4:;
/* 0024d7a4: li s1,0x30 */ c->r[17]=sx(UINT32_C(0x00000030));
L_0024d7a8:;
/* 0024d7a8: move a1,s0 */ c->r[5]=c->r[16];
/* 0024d7ac: addiu s0,s0,0x1 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000001));
/* 0024d7b0: jal 0x00243fe8 */ c->r[31]=UINT64_C(0x0024d7b8);/* delay 0024d7b4 */ c->r[4]=c->r[20];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=datGetAisyo(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d7b8: lw v1,0x10(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000010)));
/* 0024d7bc: slti a0,s0,0x10 */ c->r[4]=less(c->r[16],sx(UINT32_C(0x00000010)));
/* 0024d7c0: addu v1,s3,v1 */ c->r[3]=sx((uint32_t)c->r[19]+(uint32_t)c->r[3]);
/* 0024d7c4: addu v1,v1,s1 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[17]);
/* 0024d7c8: addiu s1,s1,0x4 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000004));
/* 0024d7cc: bne a0,zero,0x0024d7a8 */ {int taken=(c->r[4]!=c->r[0]);/* delay 0024d7d0 */ sw((uint32_t)c->r[3]+UINT32_C(0x00000000),(uint32_t)c->r[2]);if(taken){goto L_0024d7a8;}}
/* 0024d7d4: sll a2,s5,0x4 */ c->r[6]=sx((uint32_t)c->r[21]<<4u);
L_0024d7d8:;
/* 0024d7d8: lw a3,0x0(s2) */ c->r[7]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0024d7dc: subu v0,a2,s5 */ c->r[2]=sx((uint32_t)c->r[6]-(uint32_t)c->r[21]);
/* 0024d7e0: li a0,0x41 */ c->r[4]=sx(UINT32_C(0x00000041));
/* 0024d7e4: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 0024d7e8: slti v1,s5,0x4 */ c->r[3]=less(c->r[21],sx(UINT32_C(0x00000004)));
/* 0024d7ec: addu a1,v0,a3 */ c->r[5]=sx((uint32_t)c->r[2]+(uint32_t)c->r[7]);
/* 0024d7f0: beq v1,zero,0x0024d800 */ {int taken=(c->r[3]==c->r[0]);/* delay 0024d7f4 */ sw((uint32_t)c->r[5]+UINT32_C(0x00000078),(uint32_t)c->r[4]);if(taken){goto L_0024d800;}}
/* 0024d7f8: b 0x0024d810 */ /* delay 0024d7fc */ c->r[2]=sx(UINT32_C(0x00000141));goto L_0024d810;
L_0024d800:;
/* 0024d800: slti v0,s5,0xe */ c->r[2]=less(c->r[21],sx(UINT32_C(0x0000000e)));
/* 0024d804: beql v0,zero,0x0024d810 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0024d808 */ c->r[2]=sx(UINT32_C(0x00000441));goto L_0024d810;}}
/* 0024d80c: li v0,0x241 */ c->r[2]=sx(UINT32_C(0x00000241));
L_0024d810:;
/* 0024d810: sw v0,0x78(a1) */ sw((uint32_t)c->r[5]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
/* 0024d814: lhu v1,0x2a(s6) */ c->r[3]=hword((uint32_t)c->r[22]+UINT32_C(0x0000002a));
/* 0024d818: beq v1,zero,0x0024d83c */ {int taken=(c->r[3]==c->r[0]);/* delay 0024d81c */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_0024d83c;}}
/* 0024d820: bne v1,v0,0x0024d840 */ {int taken=(c->r[3]!=c->r[2]);/* delay 0024d824 */ c->r[3]=sx((uint32_t)c->r[6]-(uint32_t)c->r[21]);if(taken){goto L_0024d840;}}
/* 0024d828: sll v1,v1,0x4 */ c->r[3]=sx((uint32_t)c->r[3]<<4u);
/* 0024d82c: addu v1,v1,a3 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[7]);
/* 0024d830: lw v0,0x78(v1) */ c->r[2]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00000078)));
/* 0024d834: ori v0,v0,0x80 */ c->r[2]=c->r[2]|UINT64_C(0x80);
/* 0024d838: sw v0,0x78(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
L_0024d83c:;
/* 0024d83c: subu v1,a2,s5 */ c->r[3]=sx((uint32_t)c->r[6]-(uint32_t)c->r[21]);
L_0024d840:;
/* 0024d840: lwc1 f0,0x10(s6) */ c->f[0]=word((uint32_t)c->r[22]+UINT32_C(0x00000010));
/* 0024d844: sll v1,v1,0x4 */ c->r[3]=sx((uint32_t)c->r[3]<<4u);
/* 0024d848: addu v1,v1,a3 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[7]);
/* 0024d84c: sh s7,0x90(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x00000090),(uint16_t)c->r[23]);
/* 0024d850: addiu a0,v1,0x40 */ c->r[4]=sx((uint32_t)c->r[3]+UINT32_C(0x00000040));
/* 0024d854: sh s5,0x92(v1) */ sh((uint32_t)c->r[3]+UINT32_C(0x00000092),(uint16_t)c->r[21]);
/* 0024d858: swc1 f0,0x50(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000050),c->f[0]);
/* 0024d85c: sw zero,0x58(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000058),(uint32_t)c->r[0]);
/* 0024d860: lq v0,0x0(s6) */ lq(c,2,(uint32_t)c->r[22]+UINT32_C(0x00000000));
/* 0024d864: sq v0,0x0(a0) */ sq(c,2,(uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 0024d868: lwc1 f1,0x18(s6) */ c->f[1]=word((uint32_t)c->r[22]+UINT32_C(0x00000018));
/* 0024d86c: move a0,v1 */ c->r[4]=c->r[3];
/* 0024d870: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0024d874: move a1,zero */ c->r[5]=c->r[0];
/* 0024d878: swc1 f1,0x5c(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x0000005c),c->f[1]);
/* 0024d87c: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0024d880: lwc1 f0,0x14(s6) */ c->f[0]=word((uint32_t)c->r[22]+UINT32_C(0x00000014));
/* 0024d884: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0024d888: swc1 f0,0x54(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000054),c->f[0]);
/* 0024d88c: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0024d890: lwc1 f1,0x1c(s6) */ c->f[1]=word((uint32_t)c->r[22]+UINT32_C(0x0000001c));
/* 0024d894: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0024d898: swc1 f1,0x60(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000060),c->f[1]);
/* 0024d89c: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 0024d8a0: lwc1 f0,0x20(s6) */ c->f[0]=word((uint32_t)c->r[22]+UINT32_C(0x00000020));
/* 0024d8a4: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 0024d8a8: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0024d8ac: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 0024d8b0: sw zero,0x98(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000098),(uint32_t)c->r[0]);
/* 0024d8b4: swc1 f0,0x64(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000064),c->f[0]);
/* 0024d8b8: j 0x0024d490 */ /* delay 0024d8bc */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));body_0024d490(c);return;
}

static void body_0024d8c0(BattleFormationValues *c){
/* 0024d8c0: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 0024d8c4: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 0024d8c8: move s0,a2 */ c->r[16]=c->r[6];
/* 0024d8cc: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 0024d8d0: move s1,a0 */ c->r[17]=c->r[4];
/* 0024d8d4: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 0024d8d8: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 0024d8dc: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 0024d8e0: jal 0x002469a0 */ c->r[31]=UINT64_C(0x0024d8e8);/* delay 0024d8e4 */ c->r[18]=c->r[5];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nbGetMainProcessData();nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0024d8e8: move s3,v0 */ c->r[19]=c->r[2];
/* 0024d8ec: move a1,s1 */ c->r[5]=c->r[17];
/* 0024d8f0: move a0,s3 */ c->r[4]=c->r[19];
/* 0024d8f4: move a2,s2 */ c->r[6]=c->r[18];
/* 0024d8f8: jal 0x0024d550 */ c->r[31]=UINT64_C(0x0024d900);/* delay 0024d8fc */ c->r[7]=c->r[16];body_0024d550(c);
/* 0024d900: sll a0,s0,0x4 */ c->r[4]=sx((uint32_t)c->r[16]<<4u);
/* 0024d904: lw v0,0x0(s3) */ c->r[2]=sx(word((uint32_t)c->r[19]+UINT32_C(0x00000000)));
/* 0024d908: subu a0,a0,s0 */ c->r[4]=sx((uint32_t)c->r[4]-(uint32_t)c->r[16]);
/* 0024d90c: sll a0,a0,0x4 */ c->r[4]=sx((uint32_t)c->r[4]<<4u);
/* 0024d910: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0024d914: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0024d918: move a1,zero */ c->r[5]=c->r[0];
/* 0024d91c: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0024d920: addu a0,v0,a0 */ c->r[4]=sx((uint32_t)c->r[2]+(uint32_t)c->r[4]);
/* 0024d924: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 0024d928: li a2,0x1 */ c->r[6]=sx(UINT32_C(0x00000001));
/* 0024d92c: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0024d930: j 0x0024e178 */ /* delay 0024d934 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));body_0024e178(c);return;
}

static void body_0024e178(BattleFormationValues *c){
/* 0024e178: move a3,a0 */ c->r[7]=c->r[4];
/* 0024e17c: lw v1,0x78(a3) */ c->r[3]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00000078)));
/* 0024e180: andi v0,v1,0x1 */ c->r[2]=c->r[3]&UINT64_C(0x1);
/* 0024e184: beq v0,zero,0x0024e1d8 */ {int taken=(c->r[2]==c->r[0]);/* delay 0024e188 */ c->r[4]=c->r[3]&UINT64_C(0x40);if(taken){goto L_0024e1d8;}}
/* 0024e18c: beq a0,zero,0x0024e1d8 */ {int taken=(c->r[4]==c->r[0]);/* delay 0024e190 */ c->r[2]=c->r[3]&UINT64_C(0x2);if(taken){goto L_0024e1d8;}}
/* 0024e194: bne v0,zero,0x0024e1d8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0024e198 */ c->r[3]=sx(UINT32_C(0xfffffff9));if(taken){goto L_0024e1d8;}}
/* 0024e19c: lw v0,0x7c(a3) */ c->r[2]=sx(word((uint32_t)c->r[7]+UINT32_C(0x0000007c)));
/* 0024e1a0: li a0,0x4 */ c->r[4]=sx(UINT32_C(0x00000004));
/* 0024e1a4: sw zero,0x74(a3) */ sw((uint32_t)c->r[7]+UINT32_C(0x00000074),(uint32_t)c->r[0]);
/* 0024e1a8: and v0,v0,v1 */ c->r[2]=c->r[2]&c->r[3];
/* 0024e1ac: sw a0,0x70(a3) */ sw((uint32_t)c->r[7]+UINT32_C(0x00000070),(uint32_t)c->r[4]);
/* 0024e1b0: ori v1,v0,0x9 */ c->r[3]=c->r[2]|UINT64_C(0x9);
/* 0024e1b4: ori v0,v0,0x1 */ c->r[2]=c->r[2]|UINT64_C(0x1);
/* 0024e1b8: beq a1,zero,0x0024e1c4 */ {int taken=(c->r[5]==c->r[0]);/* delay 0024e1bc */ sw((uint32_t)c->r[7]+UINT32_C(0x0000007c),(uint32_t)c->r[2]);if(taken){goto L_0024e1c4;}}
/* 0024e1c0: sw v1,0x7c(a3) */ sw((uint32_t)c->r[7]+UINT32_C(0x0000007c),(uint32_t)c->r[3]);
L_0024e1c4:;
/* 0024e1c4: bne a2,zero,0x0024e1d8 */ {int taken=(c->r[6]!=c->r[0]);/* delay 0024e1c8 */ (void)0;if(taken){goto L_0024e1d8;}}
/* 0024e1cc: lw v0,0x80(a3) */ c->r[2]=sx(word((uint32_t)c->r[7]+UINT32_C(0x00000080)));
/* 0024e1d0: ori v0,v0,0x200 */ c->r[2]=c->r[2]|UINT64_C(0x200);
/* 0024e1d4: sw v0,0x80(a3) */ sw((uint32_t)c->r[7]+UINT32_C(0x00000080),(uint32_t)c->r[2]);
L_0024e1d8:;
/* 0024e1d8: jr ra */ /* delay 0024e1dc */ (void)0;return;
}

static void body_00259740(BattleFormationValues *c){
/* 00259740: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 00259744: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 00259748: li s1,0x9 */ c->r[17]=sx(UINT32_C(0x00000009));
/* 0025974c: sd s2,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[18]);
/* 00259750: move s2,a0 */ c->r[18]=c->r[4];
/* 00259754: sd s5,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[21]);
/* 00259758: move s5,a1 */ c->r[21]=c->r[5];
/* 0025975c: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 00259760: li a0,0x200 */ c->r[4]=sx(UINT32_C(0x00000200));
/* 00259764: sd s3,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[19]);
/* 00259768: sd s4,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[20]);
/* 0025976c: sd s6,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[22]);
/* 00259770: sd s7,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[23]);
/* 00259774: sd ra,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);
/* 00259778: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0025977c: lw v0,0x10(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000010)));
/* 00259780: addiu v1,v1,0x438 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000438));
/* 00259784: addiu v0,v0,0x200 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000200));
L_00259788:;
/* 00259788: addiu s1,s1,-0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0xffffffff));
/* 0025978c: sw a0,0x0(v1) */ sw((uint32_t)c->r[3]+UINT32_C(0x00000000),(uint32_t)c->r[4]);
/* 00259790: sh zero,0x0(v0) */ sh((uint32_t)c->r[2]+UINT32_C(0x00000000),(uint16_t)c->r[0]);
/* 00259794: addiu v0,v0,0x80 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0x00000080));
/* 00259798: nop  */ (void)0;
/* 0025979c: bgez s1,0x00259788 */ {int taken=(!neg(c->r[17]));/* delay 002597a0 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x000000f0));if(taken){goto L_00259788;}}
/* 002597a4: sll s7,s5,0x2 */ c->r[23]=sx((uint32_t)c->r[21]<<2u);
/* 002597a8: lui v1,0x35 */ c->r[3]=sx(UINT32_C(0x00350000));
/* 002597ac: addu v0,s7,s5 */ c->r[2]=sx((uint32_t)c->r[23]+(uint32_t)c->r[21]);
/* 002597b0: addiu s4,v1,-0x6840 */ c->r[20]=sx((uint32_t)c->r[3]+UINT32_C(0xffff97c0));
/* 002597b4: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 002597b8: move s6,zero */ c->r[22]=c->r[0];
/* 002597bc: subu v0,v0,s5 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[21]);
/* 002597c0: move s1,zero */ c->r[17]=c->r[0];
/* 002597c4: sll v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]<<1u);
/* 002597c8: move s3,zero */ c->r[19]=c->r[0];
/* 002597cc: lui s0,0x3b */ c->r[16]=sx(UINT32_C(0x003b0000));
/* 002597d0: addiu s0,s0,-0x101a */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0xffffefe6));
/* 002597d4: addu s0,s0,v0 */ c->r[16]=sx((uint32_t)c->r[16]+(uint32_t)c->r[2]);
L_002597d8:;
/* 002597d8: lhu v0,0x0(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 002597dc: beq v0,zero,0x00259890 */ {int taken=(c->r[2]==c->r[0]);/* delay 002597e0 */ c->r[4]=c->r[2];if(taken){goto L_00259890;}}
/* 002597e4: lw a1,0x8(s2) */ c->r[5]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000008)));
/* 002597e8: jal 0x00244ef8 */ c->r[31]=UINT64_C(0x002597f0);/* delay 002597ec */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[19]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);ps2UnitInitializeCompanion_00244EF8(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 002597f0: lw t1,0x8(s2) */ c->r[9]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000008)));
/* 002597f4: lhu a0,0x0(s0) */ c->r[4]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 002597f8: move a2,s6 */ c->r[6]=c->r[22];
/* 002597fc: addu t1,s3,t1 */ c->r[9]=sx((uint32_t)c->r[19]+(uint32_t)c->r[9]);
/* 00259800: addiu s3,s3,0xec */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x000000ec));
/* 00259804: sll v0,a0,0x4 */ c->r[2]=sx((uint32_t)c->r[4]<<4u);
/* 00259808: lw v1,0x0(t1) */ c->r[3]=sx(word((uint32_t)c->r[9]+UINT32_C(0x00000000)));
/* 0025980c: subu v0,v0,a0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[4]);
/* 00259810: move a0,s2 */ c->r[4]=c->r[18];
/* 00259814: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00259818: ori v1,v1,0x2 */ c->r[3]=c->r[3]|UINT64_C(0x2);
/* 0025981c: addu v0,v0,s4 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[20]);
/* 00259820: sw v1,0x0(t1) */ sw((uint32_t)c->r[9]+UINT32_C(0x00000000),(uint32_t)c->r[3]);
/* 00259824: lhu t0,0x8(v0) */ c->r[8]=hword((uint32_t)c->r[2]+UINT32_C(0x00000008));
/* 00259828: addiu a3,s1,0x4 */ c->r[7]=sx((uint32_t)c->r[17]+UINT32_C(0x00000004));
/* 0025982c: li a1,0x1 */ c->r[5]=sx(UINT32_C(0x00000001));
/* 00259830: addiu s6,s6,0x1 */ c->r[22]=sx((uint32_t)c->r[22]+UINT32_C(0x00000001));
/* 00259834: sh t0,0x8(t1) */ sh((uint32_t)c->r[9]+UINT32_C(0x00000008),(uint16_t)c->r[8]);
/* 00259838: lhu v1,0x0(s0) */ c->r[3]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 0025983c: sll v0,v1,0x4 */ c->r[2]=sx((uint32_t)c->r[3]<<4u);
/* 00259840: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 00259844: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00259848: addu v0,v0,s4 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[20]);
/* 0025984c: lhu v1,0x6(v0) */ c->r[3]=hword((uint32_t)c->r[2]+UINT32_C(0x00000006));
/* 00259850: sh v1,0x6(t1) */ sh((uint32_t)c->r[9]+UINT32_C(0x00000006),(uint16_t)c->r[3]);
/* 00259854: lhu t0,0x0(s0) */ c->r[8]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 00259858: sll v0,t0,0x4 */ c->r[2]=sx((uint32_t)c->r[8]<<4u);
/* 0025985c: subu v0,v0,t0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[8]);
/* 00259860: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00259864: addu v0,v0,s4 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[20]);
/* 00259868: lhu v1,0xc(v0) */ c->r[3]=hword((uint32_t)c->r[2]+UINT32_C(0x0000000c));
/* 0025986c: sh v1,0xc(t1) */ sh((uint32_t)c->r[9]+UINT32_C(0x0000000c),(uint16_t)c->r[3]);
/* 00259870: lhu t0,0x0(s0) */ c->r[8]=hword((uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 00259874: sll v0,t0,0x4 */ c->r[2]=sx((uint32_t)c->r[8]<<4u);
/* 00259878: subu v0,v0,t0 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[8]);
/* 0025987c: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 00259880: addu v0,v0,s4 */ c->r[2]=sx((uint32_t)c->r[2]+(uint32_t)c->r[20]);
/* 00259884: lhu v1,0xa(v0) */ c->r[3]=hword((uint32_t)c->r[2]+UINT32_C(0x0000000a));
/* 00259888: jal 0x0024d550 */ c->r[31]=UINT64_C(0x00259890);/* delay 0025988c */ sh((uint32_t)c->r[9]+UINT32_C(0x0000000a),(uint16_t)c->r[3]);body_0024d550(c);
L_00259890:;
/* 00259890: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
/* 00259894: slti v0,s1,0xa */ c->r[2]=less(c->r[17],sx(UINT32_C(0x0000000a)));
/* 00259898: bne v0,zero,0x002597d8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0025989c */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x00000002));if(taken){goto L_002597d8;}}
/* 002598a0: jal 0x0028a758 */ c->r[31]=UINT64_C(0x002598a8);/* delay 002598a4 */ c->r[4]=c->r[18];body_0028a758(c);
/* 002598a8: lui v0,0x3b */ c->r[2]=sx(UINT32_C(0x003b0000));
/* 002598ac: addu v1,s7,s5 */ c->r[3]=sx((uint32_t)c->r[23]+(uint32_t)c->r[21]);
/* 002598b0: addiu v0,v0,-0x1020 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffefe0));
/* 002598b4: sll v1,v1,0x2 */ c->r[3]=sx((uint32_t)c->r[3]<<2u);
/* 002598b8: subu v1,v1,s5 */ c->r[3]=sx((uint32_t)c->r[3]-(uint32_t)c->r[21]);
/* 002598bc: sll v1,v1,0x1 */ c->r[3]=sx((uint32_t)c->r[3]<<1u);
/* 002598c0: addiu v1,v1,0x20 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00000020));
/* 002598c4: addu v0,v1,v0 */ c->r[2]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 002598c8: lbu a0,0x3(v0) */ c->r[4]=*at((uint32_t)c->r[2]+UINT32_C(0x00000003));
/* 002598cc: bne a0,zero,0x002598d8 */ {int taken=(c->r[4]!=c->r[0]);/* delay 002598d0 */ c->r[2]=c->r[4];if(taken){goto L_002598d8;}}
/* 002598d4: li v0,-0x1 */ c->r[2]=sx(UINT32_C(0xffffffff));
L_002598d8:;
/* 002598d8: sw v0,0x84(s2) */ sw((uint32_t)c->r[18]+UINT32_C(0x00000084),(uint32_t)c->r[2]);
/* 002598dc: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002598e0: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002598e4: ld s2,0x10(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002598e8: ld s3,0x18(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002598ec: ld s4,0x20(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 002598f0: ld s5,0x28(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
/* 002598f4: ld s6,0x30(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 002598f8: ld s7,0x38(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 002598fc: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 00259900: jr ra */ /* delay 00259904 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}

static void body_0028a2e0(BattleFormationValues *c){
/* 0028a2e0: addiu a0,a0,0x20 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00000020));
/* 0028a2e4: lqc2 vf10,0x0(a0) */ lqc2(10,(uint32_t)c->r[4]+UINT32_C(0x00000000));
/* 0028a2e8: jr ra */ /* delay 0028a2ec */ (void)0;return;
}

static void body_0028a340(BattleFormationValues *c){
/* 0028a340: addiu sp,sp,-0x120 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffee0));
/* 0028a344: li a3,0x808 */ c->r[7]=sx(UINT32_C(0x00000808));
/* 0028a348: sd s1,0xa8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000a8),c->r[17]);
/* 0028a34c: move s1,zero */ c->r[17]=c->r[0];
/* 0028a350: sd s4,0xc0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000c0),c->r[20]);
/* 0028a354: move s4,a0 */ c->r[20]=c->r[4];
/* 0028a358: sd s5,0xc8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000c8),c->r[21]);
/* 0028a35c: move s5,zero */ c->r[21]=c->r[0];
/* 0028a360: swc1 f22,0xf8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x000000f8),c->f[22]);
/* 0028a364: addiu a2,sp,0x20 */ c->r[6]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0028a368: sd s0,0xa0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000a0),c->r[16]);
/* 0028a36c: sd s2,0xb0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000b0),c->r[18]);
/* 0028a370: sd s3,0xb8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000b8),c->r[19]);
/* 0028a374: sd s6,0xd0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000d0),c->r[22]);
/* 0028a378: sd s7,0xd8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000d8),c->r[23]);
/* 0028a37c: sd ra,0xe0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x000000e0),c->r[31]);
/* 0028a380: swc1 f25,0x110(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000110),c->f[25]);
/* 0028a384: swc1 f24,0x108(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000108),c->f[24]);
/* 0028a388: swc1 f23,0x100(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000100),c->f[23]);
/* 0028a38c: swc1 f21,0xf0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x000000f0),c->f[21]);
/* 0028a390: swc1 f20,0xe8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x000000e8),c->f[20]);
/* 0028a394: clear f22 */ c->f[22]=0;
/* 0028a398: lw s0,0x0(s4) */ c->r[16]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000000)));
/* 0028a39c: mov.S f12,f22 */ c->f[12]=c->f[22];
L_0028a3a0:;
/* 0028a3a0: lw v1,0x78(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000078)));
/* 0028a3a4: and v0,v1,a1 */ c->r[2]=c->r[3]&c->r[5];
/* 0028a3a8: beq v0,zero,0x0028a3e4 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028a3ac */ c->r[4]=c->r[3]&UINT64_C(0x1);if(taken){goto L_0028a3e4;}}
/* 0028a3b0: bnel a0,zero,0x0028a3c8 */ {int taken=(c->r[4]!=c->r[0]);if(taken){/* delay 0028a3b4 */ c->f[0]=word((uint32_t)c->r[16]+UINT32_C(0x00000050));goto L_0028a3c8;}}
/* 0028a3b8: andi v0,v1,0x808 */ c->r[2]=c->r[3]&UINT64_C(0x808);
/* 0028a3bc: bnel v0,a3,0x0028a3e8 */ {int taken=(c->r[2]!=c->r[7]);if(taken){/* delay 0028a3c0 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));goto L_0028a3e8;}}
/* 0028a3c4: lwc1 f0,0x50(s0) */ c->f[0]=word((uint32_t)c->r[16]+UINT32_C(0x00000050));
L_0028a3c8:;
/* 0028a3c8: addiu s5,s5,0x1 */ c->r[21]=sx((uint32_t)c->r[21]+UINT32_C(0x00000001));
/* 0028a3cc: lwc1 f1,0x5c(s0) */ c->f[1]=word((uint32_t)c->r[16]+UINT32_C(0x0000005c));
/* 0028a3d0: sw s1,0x0(a2) */ sw((uint32_t)c->r[6]+UINT32_C(0x00000000),(uint32_t)c->r[17]);
/* 0028a3d4: addiu a2,a2,0x4 */ c->r[6]=sx((uint32_t)c->r[6]+UINT32_C(0x00000004));
/* 0028a3d8: mul.S f0,f0,f1 */ c->f[0]=EE_FPU_MUL_S(c->f[0],c->f[1]);
/* 0028a3dc: add.S f0,f0,f0 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[0]);
/* 0028a3e0: add.S f22,f22,f0 */ c->f[22]=EE_FPU_ADD_S(c->f[22],c->f[0]);
L_0028a3e4:;
/* 0028a3e4: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
L_0028a3e8:;
/* 0028a3e8: slti v0,s1,0x20 */ c->r[2]=less(c->r[17],sx(UINT32_C(0x00000020)));
/* 0028a3ec: bne v0,zero,0x0028a3a0 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028a3f0 */ c->r[16]=sx((uint32_t)c->r[16]+UINT32_C(0x000000f0));if(taken){goto L_0028a3a0;}}
/* 0028a3f4: beq s5,zero,0x0028a714 */ {int taken=(c->r[21]==c->r[0]);/* delay 0028a3f8 */ c->r[2]=(c->r[21]<sx(UINT32_C(0x00000002)));if(taken){goto L_0028a714;}}
/* 0028a3fc: bne v0,zero,0x0028a48c */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028a400 */ c->r[19]=c->r[5]&UINT64_C(0x100);if(taken){goto L_0028a48c;}}
/* 0028a404: lui at,0x4496 */ c->r[1]=sx(UINT32_C(0x44960000));
/* 0028a408: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028a40c: lui at,0x4248 */ c->r[1]=sx(UINT32_C(0x42480000));
/* 0028a410: mtc1 at,f12 */ c->f[12]=(uint32_t)c->r[1];
/* 0028a414: c.lt.S f0,f22 */ c->condition=EE_FPU_COMPARE_S(c->f[0],c->f[22],1);
/* 0028a418: bc1t 0x0028a48c */ {int taken=(c->condition!=0);/* delay 0028a41c */ c->r[2]=sx((uint32_t)c->r[21]+UINT32_C(0xffffffff));if(taken){goto L_0028a48c;}}
/* 0028a420: bltz v0,0x0028a438 */ {int taken=(neg(c->r[2]));/* delay 0028a424 */ c->f[12]=EE_FPU_SUB_S(c->f[0],c->f[22]);if(taken){goto L_0028a438;}}
/* 0028a428: mtc1 v0,f0 */ c->f[0]=(uint32_t)c->r[2];
/* 0028a42c: cvt.s.W f0,f0 */ c->f[0]=EE_FPU_CVT_S_W(c->f[0]);
/* 0028a430: b 0x0028a450 */ /* delay 0028a434 */ (void)0;goto L_0028a450;
L_0028a438:;
/* 0028a438: srl v1,v0,0x1 */ c->r[3]=sx((uint32_t)c->r[2]>>1u);
/* 0028a43c: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028a440: or v0,v0,v1 */ c->r[2]=c->r[2]|c->r[3];
/* 0028a444: mtc1 v0,f0 */ c->f[0]=(uint32_t)c->r[2];
/* 0028a448: cvt.s.W f0,f0 */ c->f[0]=EE_FPU_CVT_S_W(c->f[0]);
/* 0028a44c: add.S f0,f0,f0 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[0]);
L_0028a450:;
/* 0028a450: nop  */ (void)0;
/* 0028a454: nop  */ (void)0;
/* 0028a458: div.S f12,f12,f0 */ c->f[12]=EE_FPU_DIV_S(c->f[12],c->f[0]);
/* 0028a45c: lui at,0x4248 */ c->r[1]=sx(UINT32_C(0x42480000));
/* 0028a460: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028a464: c.lt.S f12,f0 */ c->condition=EE_FPU_COMPARE_S(c->f[12],c->f[0],1);
/* 0028a468: bc1tl 0x0028a488 */ {int taken=(c->condition!=0);if(taken){/* delay 0028a46c */ c->f[12]=c->f[0];goto L_0028a488;}}
/* 0028a470: lui at,0x42c8 */ c->r[1]=sx(UINT32_C(0x42c80000));
/* 0028a474: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028a478: c.lt.S f0,f12 */ c->condition=EE_FPU_COMPARE_S(c->f[0],c->f[12],1);
/* 0028a47c: bc1f 0x0028a48c */ {int taken=(c->condition==0);/* delay 0028a480 */ c->r[19]=c->r[5]&UINT64_C(0x100);if(taken){goto L_0028a48c;}}
/* 0028a484: mov.S f12,f0 */ c->f[12]=c->f[0];
L_0028a488:;
/* 0028a488: andi s3,a1,0x100 */ c->r[19]=c->r[5]&UINT64_C(0x100);
L_0028a48c:;
/* 0028a48c: beql s3,zero,0x0028a498 */ {int taken=(c->r[19]==c->r[0]);if(taken){/* delay 0028a490 */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd38c),c->f[12]);goto L_0028a498;}}
/* 0028a494: swc1 f12,-0x2c78(gp) */ sw((uint32_t)c->r[28]+UINT32_C(0xffffd388),c->f[12]);
L_0028a498:;
/* 0028a498: lui at,0x4496 */ c->r[1]=sx(UINT32_C(0x44960000));
/* 0028a49c: mtc1 at,f21 */ c->f[21]=(uint32_t)c->r[1];
/* 0028a4a0: nop  */ (void)0;
/* 0028a4a4: nop  */ (void)0;
/* 0028a4a8: div.S f12,f12,f21 */ c->f[12]=EE_FPU_DIV_S(c->f[12],c->f[21]);
/* 0028a4ac: jal 0x002c0228 */ c->r[31]=UINT64_C(0x0028a4b4);/* delay 0028a4b0 */ c->r[17]=c->r[0];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->f[0]=sdfAtanBits(c->f[12]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a4b4: mov.S f24,f0 */ c->f[24]=c->f[0];
/* 0028a4b8: beq s5,zero,0x0028a518 */ {int taken=(c->r[21]==c->r[0]);/* delay 0028a4bc */ c->f[20]=c->f[24]^UINT32_C(0x80000000);if(taken){goto L_0028a518;}}
/* 0028a4c0: mov.S f23,f21 */ c->f[23]=c->f[21];
/* 0028a4c4: addiu s2,sp,0x20 */ c->r[18]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));
L_0028a4c8:;
/* 0028a4c8: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028a4cc: addiu s2,s2,0x4 */ c->r[18]=sx((uint32_t)c->r[18]+UINT32_C(0x00000004));
/* 0028a4d0: lw a0,0x0(s4) */ c->r[4]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000000)));
/* 0028a4d4: sll v0,v1,0x4 */ c->r[2]=sx((uint32_t)c->r[3]<<4u);
/* 0028a4d8: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 0028a4dc: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 0028a4e0: addu s0,a0,v0 */ c->r[16]=sx((uint32_t)c->r[4]+(uint32_t)c->r[2]);
/* 0028a4e4: lwc1 f1,0x5c(s0) */ c->f[1]=word((uint32_t)c->r[16]+UINT32_C(0x0000005c));
/* 0028a4e8: lwc1 f0,0x50(s0) */ c->f[0]=word((uint32_t)c->r[16]+UINT32_C(0x00000050));
/* 0028a4ec: mul.S f21,f0,f1 */ c->f[21]=EE_FPU_MUL_S(c->f[0],c->f[1]);
/* 0028a4f0: add.S f12,f21,f21 */ c->f[12]=EE_FPU_ADD_S(c->f[21],c->f[21]);
/* 0028a4f4: nop  */ (void)0;
/* 0028a4f8: nop  */ (void)0;
/* 0028a4fc: div.S f12,f12,f23 */ c->f[12]=EE_FPU_DIV_S(c->f[12],c->f[23]);
/* 0028a500: jal 0x002c0228 */ c->r[31]=UINT64_C(0x0028a508);/* delay 0028a504 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->f[0]=sdfAtanBits(c->f[12]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a508: sltu v0,s1,s5 */ c->r[2]=(c->r[17]<c->r[21]);
/* 0028a50c: add.S f20,f20,f0 */ c->f[20]=EE_FPU_ADD_S(c->f[20],c->f[0]);
/* 0028a510: bne v0,zero,0x0028a4c8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028a514 */ c->f[20]=EE_FPU_ADD_S(c->f[20],c->f[24]);if(taken){goto L_0028a4c8;}}
L_0028a518:;
/* 0028a518: lui at,0x4448 */ c->r[1]=sx(UINT32_C(0x44480000));
/* 0028a51c: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028a520: mov.S f0,f22 */ c->f[0]=c->f[22];
/* 0028a524: c.lt.S f0,f1 */ c->condition=EE_FPU_COMPARE_S(c->f[0],c->f[1],1);
/* 0028a528: bc1tl 0x0028a53c */ {int taken=(c->condition!=0);if(taken){/* delay 0028a52c */ c->f[0]=c->f[1];goto L_0028a53c;}}
/* 0028a530: c.lt.S f1,f0 */ c->condition=EE_FPU_COMPARE_S(c->f[1],c->f[0],1);
/* 0028a534: bc1tl 0x0028a53c */ {int taken=(c->condition!=0);if(taken){/* delay 0028a538 */ c->f[0]=c->f[1];goto L_0028a53c;}}
L_0028a53c:;
/* 0028a53c: lui at,0x3f00 */ c->r[1]=sx(UINT32_C(0x3f000000));
/* 0028a540: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028a544: neg.S f2,f20 */ c->f[2]=c->f[20]^UINT32_C(0x80000000);
/* 0028a548: lui at,0x4496 */ c->r[1]=sx(UINT32_C(0x44960000));
/* 0028a54c: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028a550: mul.S f0,f0,f1 */ c->f[0]=EE_FPU_MUL_S(c->f[0],c->f[1]);
/* 0028a554: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 0028a558: mtc1 at,f25 */ c->f[25]=(uint32_t)c->r[1];
/* 0028a55c: mul.S f20,f2,f1 */ c->f[20]=EE_FPU_MUL_S(c->f[2],c->f[1]);
/* 0028a560: bne s3,zero,0x0028a570 */ {int taken=(c->r[19]!=c->r[0]);/* delay 0028a564 */ c->f[21]=EE_FPU_SUB_S(c->f[3],c->f[0]);if(taken){goto L_0028a570;}}
/* 0028a568: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 0028a56c: mtc1 at,f25 */ c->f[25]=(uint32_t)c->r[1];
L_0028a570:;
/* 0028a570: beq s3,zero,0x0028a590 */ {int taken=(c->r[19]==c->r[0]);/* delay 0028a574 */ c->r[3]=sx(UINT32_C(0x00520000));if(taken){goto L_0028a590;}}
/* 0028a578: addiu a1,sp,0x10 */ c->r[5]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0028a57c: addiu v1,v1,0x6400 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00006400));
/* 0028a580: lq v0,0x0(v1) */ lq(c,2,(uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 0028a584: sq v0,0x0(a1) */ sq(c,2,(uint32_t)c->r[5]+UINT32_C(0x00000000));
/* 0028a588: b 0x0028a5a8 */ /* delay 0028a58c */ c->r[3]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000038)));goto L_0028a5a8;
L_0028a590:;
/* 0028a590: lui v1,0x52 */ c->r[3]=sx(UINT32_C(0x00520000));
/* 0028a594: addiu a1,sp,0x10 */ c->r[5]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0028a598: addiu v1,v1,0x6410 */ c->r[3]=sx((uint32_t)c->r[3]+UINT32_C(0x00006410));
/* 0028a59c: lq v0,0x0(v1) */ lq(c,2,(uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 0028a5a0: sq v0,0x0(a1) */ sq(c,2,(uint32_t)c->r[5]+UINT32_C(0x00000000));
/* 0028a5a4: lw v1,0x38(s4) */ c->r[3]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000038)));
L_0028a5a8:;
/* 0028a5a8: slti v0,v1,0xb */ c->r[2]=less(c->r[3],sx(UINT32_C(0x0000000b)));
/* 0028a5ac: beq v0,zero,0x0028a5c4 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028a5b0 */ c->r[22]=c->r[0];if(taken){goto L_0028a5c4;}}
/* 0028a5b4: slti v0,v1,0x8 */ c->r[2]=less(c->r[3],sx(UINT32_C(0x00000008)));
/* 0028a5b8: beq v0,zero,0x0028a5c4 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028a5bc */ c->r[22]=sx(UINT32_C(0x00000001));if(taken){goto L_0028a5c4;}}
/* 0028a5c0: move s6,zero */ c->r[22]=c->r[0];
L_0028a5c4:;
/* 0028a5c4: beq s5,zero,0x0028a714 */ {int taken=(c->r[21]==c->r[0]);/* delay 0028a5c8 */ c->r[17]=c->r[0];if(taken){goto L_0028a714;}}
/* 0028a5cc: lui at,0x4496 */ c->r[1]=sx(UINT32_C(0x44960000));
/* 0028a5d0: mtc1 at,f23 */ c->f[23]=(uint32_t)c->r[1];
/* 0028a5d4: move s2,a1 */ c->r[18]=c->r[5];
/* 0028a5d8: addiu s3,sp,0x20 */ c->r[19]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 0028a5dc: lui s7,0x54 */ c->r[23]=sx(UINT32_C(0x00540000));
/* 0028a5e0: lw v1,0x0(s3) */ c->r[3]=sx(word((uint32_t)c->r[19]+UINT32_C(0x00000000)));
/* 0028a5e4: nop  */ (void)0;
L_0028a5e8:;
/* 0028a5e8: lw a0,0x0(s4) */ c->r[4]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000000)));
/* 0028a5ec: sll v0,v1,0x4 */ c->r[2]=sx((uint32_t)c->r[3]<<4u);
/* 0028a5f0: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 0028a5f4: sll v0,v0,0x4 */ c->r[2]=sx((uint32_t)c->r[2]<<4u);
/* 0028a5f8: addu s0,a0,v0 */ c->r[16]=sx((uint32_t)c->r[4]+(uint32_t)c->r[2]);
/* 0028a5fc: lwc1 f12,0x50(s0) */ c->f[12]=word((uint32_t)c->r[16]+UINT32_C(0x00000050));
/* 0028a600: lwc1 f0,0x5c(s0) */ c->f[0]=word((uint32_t)c->r[16]+UINT32_C(0x0000005c));
/* 0028a604: mul.S f12,f12,f0 */ c->f[12]=EE_FPU_MUL_S(c->f[12],c->f[0]);
/* 0028a608: nop  */ (void)0;
/* 0028a60c: nop  */ (void)0;
/* 0028a610: div.S f12,f12,f23 */ c->f[12]=EE_FPU_DIV_S(c->f[12],c->f[23]);
/* 0028a614: jal 0x002c0228 */ c->r[31]=UINT64_C(0x0028a61c);/* delay 0028a618 */ (void)0;nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->f[0]=sdfAtanBits(c->f[12]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a61c: mov.S f22,f0 */ c->f[22]=c->f[0];
/* 0028a620: add.S f20,f20,f22 */ c->f[20]=EE_FPU_ADD_S(c->f[20],c->f[22]);
/* 0028a624: jal 0x002c0060 */ c->r[31]=UINT64_C(0x0028a62c);/* delay 0028a628 */ c->f[12]=c->f[20];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->f[0]=sdfSinBits(c->f[12]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a62c: mov.S f12,f20 */ c->f[12]=c->f[20];
/* 0028a630: mul.S f0,f0,f23 */ c->f[0]=EE_FPU_MUL_S(c->f[0],c->f[23]);
/* 0028a634: sw zero,0x4(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint32_t)c->r[0]);
/* 0028a638: jal 0x002c0160 */ c->r[31]=UINT64_C(0x0028a640);/* delay 0028a63c */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),c->f[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->f[0]=sdfCosBits(c->f[12]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a640: mul.S f0,f0,f23 */ c->f[0]=EE_FPU_MUL_S(c->f[0],c->f[23]);
/* 0028a644: move a0,s0 */ c->r[4]=c->r[16];
/* 0028a648: sub.S f0,f21,f0 */ c->f[0]=EE_FPU_SUB_S(c->f[21],c->f[0]);
/* 0028a64c: mul.S f0,f0,f25 */ c->f[0]=EE_FPU_MUL_S(c->f[0],c->f[25]);
/* 0028a650: jal 0x0016e560 */ c->r[31]=UINT64_C(0x0028a658);/* delay 0028a654 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=effBTLModelGetID(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a658: move v1,v0 */ c->r[3]=c->r[2];
/* 0028a65c: lw v0,0x78(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000078)));
/* 0028a660: andi v0,v0,0x100 */ c->r[2]=c->r[2]&UINT64_C(0x100);
/* 0028a664: beq v0,zero,0x0028a6a8 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028a668 */ c->r[4]=sx(UINT32_C(0x0000009b));if(taken){goto L_0028a6a8;}}
/* 0028a66c: bnel v1,a0,0x0028a6ac */ {int taken=(c->r[3]!=c->r[4]);if(taken){/* delay 0028a670 */ c->r[4]=c->r[16];goto L_0028a6ac;}}
/* 0028a674: bnel s6,zero,0x0028a6ac */ {int taken=(c->r[22]!=c->r[0]);if(taken){/* delay 0028a678 */ c->r[4]=c->r[16];goto L_0028a6ac;}}
/* 0028a67c: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028a684);/* delay 0028a680 */ c->r[4]=sx((uint32_t)c->r[23]+UINT32_C(0x000058c0));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a684: lwc1 f2,-0x5b28(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4d8));
/* 0028a688: lwc1 f0,0x5c(s0) */ c->f[0]=word((uint32_t)c->r[16]+UINT32_C(0x0000005c));
/* 0028a68c: lwc1 f1,0x50(s0) */ c->f[1]=word((uint32_t)c->r[16]+UINT32_C(0x00000050));
/* 0028a690: mul.S f1,f1,f0 */ c->f[1]=EE_FPU_MUL_S(c->f[1],c->f[0]);
/* 0028a694: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028a698: mul.S f1,f1,f2 */ c->f[1]=EE_FPU_MUL_S(c->f[1],c->f[2]);
/* 0028a69c: mul.S f1,f1,f25 */ c->f[1]=EE_FPU_MUL_S(c->f[1],c->f[25]);
/* 0028a6a0: sub.S f0,f0,f1 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[1]);
/* 0028a6a4: swc1 f0,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);
L_0028a6a8:;
/* 0028a6a8: move a0,s0 */ c->r[4]=c->r[16];
L_0028a6ac:;
/* 0028a6ac: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028a6b4);/* delay 0028a6b0 */ c->r[5]=c->r[29];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a6b4: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028a6b8: sq v0,0x0(s0) */ sq(c,2,(uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 0028a6bc: move a0,s0 */ c->r[4]=c->r[16];
/* 0028a6c0: jal 0x0028a158 */ c->r[31]=UINT64_C(0x0028a6c8);/* delay 0028a6c4 */ c->r[5]=c->r[18];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormRot(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a6c8: addiu v1,s0,0x10 */ c->r[3]=sx((uint32_t)c->r[16]+UINT32_C(0x00000010));
/* 0028a6cc: lq v0,0x0(s2) */ lq(c,2,(uint32_t)c->r[18]+UINT32_C(0x00000000));
/* 0028a6d0: sq v0,0x0(v1) */ sq(c,2,(uint32_t)c->r[3]+UINT32_C(0x00000000));
/* 0028a6d4: add.S f20,f20,f22 */ c->f[20]=EE_FPU_ADD_S(c->f[20],c->f[22]);
/* 0028a6d8: lw v0,0x60(s4) */ c->r[2]=sx(word((uint32_t)c->r[20]+UINT32_C(0x00000060)));
/* 0028a6dc: addiu s1,s1,0x1 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x00000001));
/* 0028a6e0: addiu s3,s3,0x4 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000004));
/* 0028a6e4: andi v0,v0,0x10 */ c->r[2]=c->r[2]&UINT64_C(0x10);
/* 0028a6e8: sltu a0,s1,s5 */ c->r[4]=(c->r[17]<c->r[21]);
/* 0028a6ec: bne v0,zero,0x0028a70c */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028a6f0 */ c->f[20]=EE_FPU_ADD_S(c->f[20],c->f[24]);if(taken){goto L_0028a70c;}}
/* 0028a6f4: lw v1,0x78(s0) */ c->r[3]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000078)));
/* 0028a6f8: andi v0,v1,0x2000 */ c->r[2]=c->r[3]&UINT64_C(0x2000);
/* 0028a6fc: beq v0,zero,0x0028a70c */ {int taken=(c->r[2]==c->r[0]);/* delay 0028a700 */ c->r[2]=sx(UINT32_C(0xffffdfff));if(taken){goto L_0028a70c;}}
/* 0028a704: and v0,v1,v0 */ c->r[2]=c->r[3]&c->r[2];
/* 0028a708: sw v0,0x78(s0) */ sw((uint32_t)c->r[16]+UINT32_C(0x00000078),(uint32_t)c->r[2]);
L_0028a70c:;
/* 0028a70c: bnel a0,zero,0x0028a5e8 */ {int taken=(c->r[4]!=c->r[0]);if(taken){/* delay 0028a710 */ c->r[3]=sx(word((uint32_t)c->r[19]+UINT32_C(0x00000000)));goto L_0028a5e8;}}
L_0028a714:;
/* 0028a714: ld s0,0xa0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x000000a0));
/* 0028a718: ld s1,0xa8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x000000a8));
/* 0028a71c: ld s2,0xb0(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x000000b0));
/* 0028a720: ld s3,0xb8(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x000000b8));
/* 0028a724: ld s4,0xc0(sp) */ c->r[20]=quad((uint32_t)c->r[29]+UINT32_C(0x000000c0));
/* 0028a728: ld s5,0xc8(sp) */ c->r[21]=quad((uint32_t)c->r[29]+UINT32_C(0x000000c8));
/* 0028a72c: ld s6,0xd0(sp) */ c->r[22]=quad((uint32_t)c->r[29]+UINT32_C(0x000000d0));
/* 0028a730: ld s7,0xd8(sp) */ c->r[23]=quad((uint32_t)c->r[29]+UINT32_C(0x000000d8));
/* 0028a734: ld ra,0xe0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x000000e0));
/* 0028a738: lwc1 f25,0x110(sp) */ c->f[25]=word((uint32_t)c->r[29]+UINT32_C(0x00000110));
/* 0028a73c: lwc1 f24,0x108(sp) */ c->f[24]=word((uint32_t)c->r[29]+UINT32_C(0x00000108));
/* 0028a740: lwc1 f23,0x100(sp) */ c->f[23]=word((uint32_t)c->r[29]+UINT32_C(0x00000100));
/* 0028a744: lwc1 f22,0xf8(sp) */ c->f[22]=word((uint32_t)c->r[29]+UINT32_C(0x000000f8));
/* 0028a748: lwc1 f21,0xf0(sp) */ c->f[21]=word((uint32_t)c->r[29]+UINT32_C(0x000000f0));
/* 0028a74c: lwc1 f20,0xe8(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x000000e8));
/* 0028a750: jr ra */ /* delay 0028a754 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000120));return;
}

static void body_0028a758(BattleFormationValues *c){
/* 0028a758: addiu sp,sp,-0x50 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffb0));
/* 0028a75c: sd s2,0x30(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000030),c->r[18]);
/* 0028a760: move s2,a0 */ c->r[18]=c->r[4];
/* 0028a764: sd s0,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[16]);
/* 0028a768: sd s1,0x28(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000028),c->r[17]);
/* 0028a76c: sd s3,0x38(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000038),c->r[19]);
/* 0028a770: sd ra,0x40(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000040),c->r[31]);
/* 0028a774: swc1 f20,0x48(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000048),c->f[20]);
/* 0028a778: lw v1,0x38(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000038)));
/* 0028a77c: sltiu v0,v1,0xe */ c->r[2]=(c->r[3]<sx(UINT32_C(0x0000000e)));
/* 0028a780: beql v0,zero,0x0028b080 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028a784 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;}}
/* 0028a788: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 0028a78c: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 0028a790: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0028a794: lw v1,0x5b20(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00005b20)));
/* 0028a798: jr v1 */ {uint64_t target=c->r[3];/* delay 0028a79c */ (void)0;switch(target){case UINT64_C(0x0028a7a0):goto L_0028a7a0;case UINT64_C(0x0028a7b0):goto L_0028a7b0;case UINT64_C(0x0028a838):goto L_0028a838;case UINT64_C(0x0028a848):goto L_0028a848;case UINT64_C(0x0028a8d8):goto L_0028a8d8;case UINT64_C(0x0028aa38):goto L_0028aa38;case UINT64_C(0x0028ab98):goto L_0028ab98;case UINT64_C(0x0028aba8):goto L_0028aba8;case UINT64_C(0x0028ac18):goto L_0028ac18;case UINT64_C(0x0028acf8):goto L_0028acf8;case UINT64_C(0x0028ae70):goto L_0028ae70;case UINT64_C(0x0028af80):goto L_0028af80;case UINT64_C(0x0028afa8):goto L_0028afa8;default:abort();}}
L_0028a7a0:;
/* 0028a7a0: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028a7a4: b 0x0028af88 */ /* delay 0028a7a8 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000058e8));goto L_0028af88;
L_0028a7b0:;
/* 0028a7b0: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028a7b4: lui at,0x4396 */ c->r[1]=sx(UINT32_C(0x43960000));
/* 0028a7b8: mtc1 at,f20 */ c->f[20]=(uint32_t)c->r[1];
/* 0028a7bc: addiu a0,a0,0x5918 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005918));
/* 0028a7c0: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028a7c8);/* delay 0028a7c4 */ c->r[19]=c->r[0];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a7c8: move a0,s2 */ c->r[4]=c->r[18];
/* 0028a7cc: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028a7d4);/* delay 0028a7d0 */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028a7d4: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028a7d8: addiu s1,v0,0x3c0 */ c->r[17]=sx((uint32_t)c->r[2]+UINT32_C(0x000003c0));
/* 0028a7dc: nop  */ (void)0;
L_0028a7e0:;
/* 0028a7e0: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028a7e4: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028a7e8: beql v0,zero,0x0028a820 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028a7ec */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_0028a820;}}
/* 0028a7f0: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028a7f8);/* delay 0028a7f4 */ c->r[4]=c->r[17];body_0028a2e0(c);
/* 0028a7f8: sqc2 vf10,0x0(sp) */ sqc2(10,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028a7fc: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028a800: move a0,s1 */ c->r[4]=c->r[17];
/* 0028a804: move a1,sp */ c->r[5]=c->r[29];
/* 0028a808: add.S f0,f0,f20 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[20]);
/* 0028a80c: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028a814);/* delay 0028a810 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a814: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028a818: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028a81c: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_0028a820:;
/* 0028a820: sltiu v0,s3,0xa */ c->r[2]=(c->r[19]<sx(UINT32_C(0x0000000a)));
/* 0028a824: bne v0,zero,0x0028a7e0 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028a828 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x000000f0));if(taken){goto L_0028a7e0;}}
/* 0028a82c: b 0x0028b080 */ /* delay 0028a830 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;
L_0028a838:;
/* 0028a838: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028a83c: b 0x0028af88 */ /* delay 0028a840 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005948));goto L_0028af88;
L_0028a848:;
/* 0028a848: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028a84c: lui at,0x43d2 */ c->r[1]=sx(UINT32_C(0x43d20000));
/* 0028a850: mtc1 at,f20 */ c->f[20]=(uint32_t)c->r[1];
/* 0028a854: addiu a0,a0,0x5978 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005978));
/* 0028a858: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028a860);/* delay 0028a85c */ c->r[19]=c->r[0];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a860: move a0,s2 */ c->r[4]=c->r[18];
/* 0028a864: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028a86c);/* delay 0028a868 */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028a86c: move a0,s2 */ c->r[4]=c->r[18];
/* 0028a870: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028a878);/* delay 0028a874 */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028a878: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028a87c: addiu s1,v0,0x3c0 */ c->r[17]=sx((uint32_t)c->r[2]+UINT32_C(0x000003c0));
L_0028a880:;
/* 0028a880: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028a884: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028a888: beql v0,zero,0x0028a8c0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028a88c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_0028a8c0;}}
/* 0028a890: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028a898);/* delay 0028a894 */ c->r[4]=c->r[17];body_0028a2e0(c);
/* 0028a898: sqc2 vf10,0x0(sp) */ sqc2(10,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028a89c: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028a8a0: move a0,s1 */ c->r[4]=c->r[17];
/* 0028a8a4: move a1,sp */ c->r[5]=c->r[29];
/* 0028a8a8: add.S f0,f0,f20 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[20]);
/* 0028a8ac: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028a8b4);/* delay 0028a8b0 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a8b4: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028a8b8: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028a8bc: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_0028a8c0:;
/* 0028a8c0: sltiu v0,s3,0xa */ c->r[2]=(c->r[19]<sx(UINT32_C(0x0000000a)));
/* 0028a8c4: bne v0,zero,0x0028a880 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028a8c8 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x000000f0));if(taken){goto L_0028a880;}}
/* 0028a8cc: b 0x0028b080 */ /* delay 0028a8d0 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;
L_0028a8d8:;
/* 0028a8d8: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028a8dc: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028a8e4);/* delay 0028a8e0 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000059a0));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a8e4: move a0,s2 */ c->r[4]=c->r[18];
/* 0028a8e8: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028a8f0);/* delay 0028a8ec */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028a8f0: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028a8f4: addiu s1,v1,0x4b0 */ c->r[17]=sx((uint32_t)c->r[3]+UINT32_C(0x000004b0));
/* 0028a8f8: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028a8fc: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028a900: beql v0,zero,0x0028a9c0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028a904 */ c->r[17]=sx((uint32_t)c->r[3]+UINT32_C(0x000003c0));goto L_0028a9c0;}}
/* 0028a908: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028a910);/* delay 0028a90c */ c->r[4]=c->r[17];body_0028a2e0(c);
/* 0028a910: sqc2 vf10,0x0(sp) */ sqc2(10,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028a914: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028a918: addiu s0,v0,0x3c0 */ c->r[16]=sx((uint32_t)c->r[2]+UINT32_C(0x000003c0));
/* 0028a91c: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028a924);/* delay 0028a920 */ c->r[4]=c->r[16];body_0028a2e0(c);
/* 0028a924: addiu s1,sp,0x10 */ c->r[17]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0028a928: sqc2 vf10,0x0(s1) */ sqc2(10,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028a92c: lw v0,0x78(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000078)));
/* 0028a930: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028a934: beq v0,zero,0x0028a968 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028a938 */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_0028a968;}}
/* 0028a93c: move a0,s0 */ c->r[4]=c->r[16];
/* 0028a940: lui at,0x4367 */ c->r[1]=sx(UINT32_C(0x43670000));
/* 0028a944: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028a948: move a1,s1 */ c->r[5]=c->r[17];
/* 0028a94c: lwc1 f1,0x8(sp) */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028a950: sub.S f0,f0,f2 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[2]);
/* 0028a954: swc1 f1,0x18(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000018),c->f[1]);
/* 0028a958: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028a960);/* delay 0028a95c */ sw((uint32_t)c->r[29]+UINT32_C(0x00000010),c->f[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a960: lq v0,0x0(s1) */ lq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028a964: sq v0,0x0(s0) */ sq(c,2,(uint32_t)c->r[16]+UINT32_C(0x00000000));
L_0028a968:;
/* 0028a968: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028a96c: addiu s0,v0,0x5a0 */ c->r[16]=sx((uint32_t)c->r[2]+UINT32_C(0x000005a0));
/* 0028a970: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028a978);/* delay 0028a974 */ c->r[4]=c->r[16];body_0028a2e0(c);
/* 0028a978: sqc2 vf10,0x0(s1) */ sqc2(10,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028a97c: lw v0,0x78(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000078)));
/* 0028a980: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028a984: beq v0,zero,0x0028b07c */ {int taken=(c->r[2]==c->r[0]);/* delay 0028a988 */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_0028b07c;}}
/* 0028a98c: move a0,s0 */ c->r[4]=c->r[16];
/* 0028a990: lwc1 f2,-0x5b24(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4dc));
/* 0028a994: move a1,s1 */ c->r[5]=c->r[17];
/* 0028a998: lwc1 f1,0x8(sp) */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028a99c: add.S f0,f0,f2 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[2]);
/* 0028a9a0: swc1 f1,0x18(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000018),c->f[1]);
/* 0028a9a4: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028a9ac);/* delay 0028a9a8 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000010),c->f[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028a9ac: lq v0,0x0(s1) */ lq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028a9b0: sq v0,0x0(s0) */ sq(c,2,(uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 0028a9b4: b 0x0028b080 */ /* delay 0028a9b8 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;
L_0028a9c0:;
/* 0028a9c0: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028a9c8);/* delay 0028a9c4 */ c->r[4]=c->r[17];body_0028a2e0(c);
/* 0028a9c8: sqc2 vf10,0x0(sp) */ sqc2(10,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028a9cc: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028a9d0: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028a9d4: beq v0,zero,0x0028b080 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028a9d8 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));if(taken){goto L_0028b080;}}
/* 0028a9dc: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028a9e0: addiu s0,v0,0x5a0 */ c->r[16]=sx((uint32_t)c->r[2]+UINT32_C(0x000005a0));
/* 0028a9e4: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028a9ec);/* delay 0028a9e8 */ c->r[4]=c->r[16];body_0028a2e0(c);
/* 0028a9ec: addiu s1,sp,0x10 */ c->r[17]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 0028a9f0: sqc2 vf10,0x0(s1) */ sqc2(10,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028a9f4: lw v0,0x78(s0) */ c->r[2]=sx(word((uint32_t)c->r[16]+UINT32_C(0x00000078)));
/* 0028a9f8: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028a9fc: beq v0,zero,0x0028b07c */ {int taken=(c->r[2]==c->r[0]);/* delay 0028aa00 */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));if(taken){goto L_0028b07c;}}
/* 0028aa04: move a0,s0 */ c->r[4]=c->r[16];
/* 0028aa08: lwc1 f2,-0x5b20(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4e0));
/* 0028aa0c: move a1,s1 */ c->r[5]=c->r[17];
/* 0028aa10: lwc1 f1,0x8(sp) */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028aa14: add.S f0,f0,f2 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[2]);
/* 0028aa18: swc1 f1,0x18(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000018),c->f[1]);
/* 0028aa1c: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028aa24);/* delay 0028aa20 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000010),c->f[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028aa24: lq v0,0x0(s1) */ lq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028aa28: sq v0,0x0(s0) */ sq(c,2,(uint32_t)c->r[16]+UINT32_C(0x00000000));
/* 0028aa2c: b 0x0028b080 */ /* delay 0028aa30 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;
L_0028aa38:;
/* 0028aa38: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028aa3c: move s3,zero */ c->r[19]=c->r[0];
/* 0028aa40: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028aa48);/* delay 0028aa44 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x000059d0));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028aa48: move a0,s2 */ c->r[4]=c->r[18];
/* 0028aa4c: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028aa54);/* delay 0028aa50 */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028aa54: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028aa58: addiu s1,v0,0x3c0 */ c->r[17]=sx((uint32_t)c->r[2]+UINT32_C(0x000003c0));
/* 0028aa5c: nop  */ (void)0;
L_0028aa60:;
/* 0028aa60: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028aa64: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028aa68: beql v0,zero,0x0028ab80 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028aa6c */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));goto L_0028ab80;}}
/* 0028aa70: jal 0x00246ab8 */ c->r[31]=UINT64_C(0x0028aa78);/* delay 0028aa74 */ c->r[4]=sx((uint32_t)(int32_t)(int16_t)hword((uint32_t)c->r[17]+UINT32_C(0x00000092)));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativeScaleLookup((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31],c->r[16],c->r[17]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028aa78: move a0,s1 */ c->r[4]=c->r[17];
/* 0028aa7c: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028aa84);/* delay 0028aa80 */ c->r[16]=c->r[2];body_0028a2e0(c);
/* 0028aa84: sqc2 vf10,0x0(sp) */ sqc2(10,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028aa88: lhu v0,0x4(s0) */ c->r[2]=hword((uint32_t)c->r[16]+UINT32_C(0x00000004));
/* 0028aa8c: addiu v0,v0,-0x116 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xfffffeea));
/* 0028aa90: sltiu v1,v0,0x5 */ c->r[3]=(c->r[2]<sx(UINT32_C(0x00000005)));
/* 0028aa94: beq v1,zero,0x0028ab6c */ {int taken=(c->r[3]==c->r[0]);/* delay 0028aa98 */ c->r[4]=c->r[17];if(taken){goto L_0028ab6c;}}
/* 0028aa9c: sll v0,v0,0x2 */ c->r[2]=sx((uint32_t)c->r[2]<<2u);
/* 0028aaa0: lui v1,0x54 */ c->r[3]=sx(UINT32_C(0x00540000));
/* 0028aaa4: addu v1,v1,v0 */ c->r[3]=sx((uint32_t)c->r[3]+(uint32_t)c->r[2]);
/* 0028aaa8: lw v1,0x5b60(v1) */ c->r[3]=sx(word((uint32_t)c->r[3]+UINT32_C(0x00005b60)));
/* 0028aaac: jr v1 */ {uint64_t target=c->r[3];/* delay 0028aab0 */ (void)0;switch(target){case UINT64_C(0x0028aab8):goto L_0028aab8;case UINT64_C(0x0028aad0):goto L_0028aad0;case UINT64_C(0x0028aaf8):goto L_0028aaf8;case UINT64_C(0x0028ab20):goto L_0028ab20;case UINT64_C(0x0028ab40):goto L_0028ab40;default:abort();}}
L_0028aab8:;
/* 0028aab8: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028aabc: lui at,0x4461 */ c->r[1]=sx(UINT32_C(0x44610000));
/* 0028aac0: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028aac4: add.S f0,f0,f1 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[1]);
/* 0028aac8: b 0x0028ab68 */ /* delay 0028aacc */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);goto L_0028ab68;
L_0028aad0:;
/* 0028aad0: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028aad4: lwc1 f1,0x0(sp) */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028aad8: lui at,0x4416 */ c->r[1]=sx(UINT32_C(0x44160000));
/* 0028aadc: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028aae0: lui at,0x42c8 */ c->r[1]=sx(UINT32_C(0x42c80000));
/* 0028aae4: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028aae8: add.S f0,f0,f2 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[2]);
/* 0028aaec: b 0x0028ab60 */ /* delay 0028aaf0 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[3]);goto L_0028ab60;
L_0028aaf8:;
/* 0028aaf8: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028aafc: lwc1 f1,0x0(sp) */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028ab00: lui at,0x4416 */ c->r[1]=sx(UINT32_C(0x44160000));
/* 0028ab04: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028ab08: lui at,0x4348 */ c->r[1]=sx(UINT32_C(0x43480000));
/* 0028ab0c: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028ab10: add.S f0,f0,f2 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[2]);
/* 0028ab14: b 0x0028ab60 */ /* delay 0028ab18 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[3]);goto L_0028ab60;
L_0028ab20:;
/* 0028ab20: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028ab24: lui at,0x4416 */ c->r[1]=sx(UINT32_C(0x44160000));
/* 0028ab28: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028ab2c: lui at,0x4348 */ c->r[1]=sx(UINT32_C(0x43480000));
/* 0028ab30: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028ab34: b 0x0028ab58 */ /* delay 0028ab38 */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));goto L_0028ab58;
L_0028ab40:;
/* 0028ab40: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028ab44: lwc1 f1,0x0(sp) */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028ab48: lui at,0x4416 */ c->r[1]=sx(UINT32_C(0x44160000));
/* 0028ab4c: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028ab50: lui at,0x42c8 */ c->r[1]=sx(UINT32_C(0x42c80000));
/* 0028ab54: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
L_0028ab58:;
/* 0028ab58: add.S f0,f0,f2 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[2]);
/* 0028ab5c: sub.S f1,f1,f3 */ c->f[1]=EE_FPU_SUB_S(c->f[1],c->f[3]);
L_0028ab60:;
/* 0028ab60: swc1 f0,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);
/* 0028ab64: swc1 f1,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),c->f[1]);
L_0028ab68:;
/* 0028ab68: move a0,s1 */ c->r[4]=c->r[17];
L_0028ab6c:;
/* 0028ab6c: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028ab74);/* delay 0028ab70 */ c->r[5]=c->r[29];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ab74: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028ab78: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028ab7c: addiu s3,s3,0x1 */ c->r[19]=sx((uint32_t)c->r[19]+UINT32_C(0x00000001));
L_0028ab80:;
/* 0028ab80: sltiu v0,s3,0xa */ c->r[2]=(c->r[19]<sx(UINT32_C(0x0000000a)));
/* 0028ab84: bne v0,zero,0x0028aa60 */ {int taken=(c->r[2]!=c->r[0]);/* delay 0028ab88 */ c->r[17]=sx((uint32_t)c->r[17]+UINT32_C(0x000000f0));if(taken){goto L_0028aa60;}}
/* 0028ab8c: b 0x0028b080 */ /* delay 0028ab90 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;
L_0028ab98:;
/* 0028ab98: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028ab9c: b 0x0028af88 */ /* delay 0028aba0 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005a00));goto L_0028af88;
L_0028aba8:;
/* 0028aba8: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028abac: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028abb4);/* delay 0028abb0 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005a30));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028abb4: move a0,s2 */ c->r[4]=c->r[18];
/* 0028abb8: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028abc0);/* delay 0028abbc */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028abc0: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028abc4: addiu s1,v1,0x3c0 */ c->r[17]=sx((uint32_t)c->r[3]+UINT32_C(0x000003c0));
/* 0028abc8: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028abcc: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028abd0: beql v0,zero,0x0028b080 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 0028abd4 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;}}
/* 0028abd8: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028abe0);/* delay 0028abdc */ c->r[4]=c->r[17];body_0028a2e0(c);
/* 0028abe0: sqc2 vf10,0x0(sp) */ sqc2(10,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028abe4: lwc1 f0,0x0(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028abe8: move a0,s1 */ c->r[4]=c->r[17];
/* 0028abec: lui at,0x42f0 */ c->r[1]=sx(UINT32_C(0x42f00000));
/* 0028abf0: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028abf4: move a1,sp */ c->r[5]=c->r[29];
/* 0028abf8: sub.S f0,f0,f1 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[1]);
/* 0028abfc: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028ac04);/* delay 0028ac00 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),c->f[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ac04: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028ac08: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028ac0c: b 0x0028b080 */ /* delay 0028ac10 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;
L_0028ac18:;
/* 0028ac18: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028ac1c: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028ac24);/* delay 0028ac20 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005a58));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ac24: move a0,s2 */ c->r[4]=c->r[18];
/* 0028ac28: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028ac30);/* delay 0028ac2c */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028ac30: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028ac34: addiu s1,v1,0x3c0 */ c->r[17]=sx((uint32_t)c->r[3]+UINT32_C(0x000003c0));
/* 0028ac38: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028ac3c: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028ac40: beq v0,zero,0x0028b07c */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ac44 */ c->r[4]=c->r[17];if(taken){goto L_0028b07c;}}
/* 0028ac48: lui at,0x4416 */ c->r[1]=sx(UINT32_C(0x44160000));
/* 0028ac4c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028ac50: lui at,0x43cd */ c->r[1]=sx(UINT32_C(0x43cd0000));
/* 0028ac54: mtc1 at,f20 */ c->f[20]=(uint32_t)c->r[1];
/* 0028ac58: move a1,sp */ c->r[5]=c->r[29];
/* 0028ac5c: swc1 f0,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);
/* 0028ac60: swc1 f20,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),c->f[20]);
/* 0028ac64: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028ac6c);/* delay 0028ac68 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint32_t)c->r[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ac6c: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028ac70: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028ac74: jal 0x0016e560 */ c->r[31]=UINT64_C(0x0028ac7c);/* delay 0028ac78 */ c->r[4]=c->r[17];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=effBTLModelGetID(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ac7c: move v1,v0 */ c->r[3]=c->r[2];
/* 0028ac80: li v0,0x103 */ c->r[2]=sx(UINT32_C(0x00000103));
/* 0028ac84: beq v1,v0,0x0028acc0 */ {int taken=(c->r[3]==c->r[2]);/* delay 0028ac88 */ c->r[2]=sx(UINT32_C(0x00000124));if(taken){goto L_0028acc0;}}
/* 0028ac8c: bne v1,v0,0x0028b080 */ {int taken=(c->r[3]!=c->r[2]);/* delay 0028ac90 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));if(taken){goto L_0028b080;}}
/* 0028ac94: lui at,0x43c8 */ c->r[1]=sx(UINT32_C(0x43c80000));
/* 0028ac98: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028ac9c: lui at,0x4443 */ c->r[1]=sx(UINT32_C(0x44430000));
/* 0028aca0: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028aca4: lui at,0xc3e1 */ c->r[1]=sx(UINT32_C(0xc3e10000));
/* 0028aca8: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028acac: lui at,0xc35c */ c->r[1]=sx(UINT32_C(0xc35c0000));
/* 0028acb0: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028acb4: b 0x0028ace4 */ /* delay 0028acb8 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000050),c->f[1]);goto L_0028ace4;
L_0028acc0:;
/* 0028acc0: lui at,0x43c8 */ c->r[1]=sx(UINT32_C(0x43c80000));
/* 0028acc4: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028acc8: lui at,0x4443 */ c->r[1]=sx(UINT32_C(0x44430000));
/* 0028accc: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028acd0: lui at,0xc3e1 */ c->r[1]=sx(UINT32_C(0xc3e10000));
/* 0028acd4: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028acd8: lui at,0xc316 */ c->r[1]=sx(UINT32_C(0xc3160000));
/* 0028acdc: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028ace0: swc1 f1,0x50(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000050),c->f[1]);
L_0028ace4:;
/* 0028ace4: swc1 f0,0x48(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000048),c->f[0]);
/* 0028ace8: swc1 f2,0x54(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000054),c->f[2]);
/* 0028acec: swc1 f20,0x40(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000040),c->f[20]);
/* 0028acf0: b 0x0028b07c */ /* delay 0028acf4 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000044),c->f[3]);goto L_0028b07c;
L_0028acf8:;
/* 0028acf8: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028acfc: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028ad04);/* delay 0028ad00 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005a80));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ad04: move a0,s2 */ c->r[4]=c->r[18];
/* 0028ad08: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028ad10);/* delay 0028ad0c */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028ad10: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028ad14: addiu s1,v1,0x3c0 */ c->r[17]=sx((uint32_t)c->r[3]+UINT32_C(0x000003c0));
/* 0028ad18: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028ad1c: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028ad20: beq v0,zero,0x0028b07c */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ad24 */ c->r[4]=c->r[17];if(taken){goto L_0028b07c;}}
/* 0028ad28: lui at,0x4416 */ c->r[1]=sx(UINT32_C(0x44160000));
/* 0028ad2c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028ad30: move a1,sp */ c->r[5]=c->r[29];
/* 0028ad34: sw zero,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[0]);
/* 0028ad38: swc1 f0,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);
/* 0028ad3c: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028ad44);/* delay 0028ad40 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint32_t)c->r[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ad44: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028ad48: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028ad4c: jal 0x0016e560 */ c->r[31]=UINT64_C(0x0028ad54);/* delay 0028ad50 */ c->r[4]=c->r[17];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=effBTLModelGetID(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ad54: move v1,v0 */ c->r[3]=c->r[2];
/* 0028ad58: li v0,0x123 */ c->r[2]=sx(UINT32_C(0x00000123));
/* 0028ad5c: beq v1,v0,0x0028ae18 */ {int taken=(c->r[3]==c->r[2]);/* delay 0028ad60 */ c->r[2]=(c->r[3]<sx(UINT32_C(0x00000124)));if(taken){goto L_0028ae18;}}
/* 0028ad64: beq v0,zero,0x0028ad80 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ad68 */ c->r[2]=sx(UINT32_C(0x00000156));if(taken){goto L_0028ad80;}}
/* 0028ad6c: li v0,0x102 */ c->r[2]=sx(UINT32_C(0x00000102));
/* 0028ad70: beq v1,v0,0x0028ae38 */ {int taken=(c->r[3]==c->r[2]);/* delay 0028ad74 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));if(taken){goto L_0028ae38;}}
/* 0028ad78: b 0x0028b084 */ /* delay 0028ad7c */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));goto L_0028b084;
L_0028ad80:;
/* 0028ad80: bne v1,v0,0x0028b080 */ {int taken=(c->r[3]!=c->r[2]);/* delay 0028ad84 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));if(taken){goto L_0028b080;}}
/* 0028ad88: lui at,0x447a */ c->r[1]=sx(UINT32_C(0x447a0000));
/* 0028ad8c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028ad90: move a0,s1 */ c->r[4]=c->r[17];
/* 0028ad94: move a1,sp */ c->r[5]=c->r[29];
/* 0028ad98: sw zero,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[0]);
/* 0028ad9c: swc1 f0,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);
/* 0028ada0: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028ada8);/* delay 0028ada4 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint32_t)c->r[0]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ada8: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028adac: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028adb0: lui at,0x4348 */ c->r[1]=sx(UINT32_C(0x43480000));
/* 0028adb4: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028adb8: lwc1 f2,0x5c(s1) */ c->f[2]=word((uint32_t)c->r[17]+UINT32_C(0x0000005c));
/* 0028adbc: lui at,0x442f */ c->r[1]=sx(UINT32_C(0x442f0000));
/* 0028adc0: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028adc4: lwc1 f4,-0x5b1c(gp) */ c->f[4]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4e4));
/* 0028adc8: nop  */ (void)0;
/* 0028adcc: nop  */ (void)0;
/* 0028add0: div.S f1,f1,f2 */ c->f[1]=EE_FPU_DIV_S(c->f[1],c->f[2]);
/* 0028add4: lui at,0x437a */ c->r[1]=sx(UINT32_C(0x437a0000));
/* 0028add8: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028addc: sw zero,0x40(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000040),(uint32_t)c->r[0]);
/* 0028ade0: nop  */ (void)0;
/* 0028ade4: nop  */ (void)0;
/* 0028ade8: div.S f0,f0,f2 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[2]);
/* 0028adec: swc1 f1,0x50(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000050),c->f[1]);
/* 0028adf0: nop  */ (void)0;
/* 0028adf4: nop  */ (void)0;
/* 0028adf8: div.S f3,f3,f2 */ c->f[3]=EE_FPU_DIV_S(c->f[3],c->f[2]);
/* 0028adfc: swc1 f0,0x48(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000048),c->f[0]);
/* 0028ae00: nop  */ (void)0;
/* 0028ae04: nop  */ (void)0;
/* 0028ae08: div.S f4,f4,f2 */ c->f[4]=EE_FPU_DIV_S(c->f[4],c->f[2]);
/* 0028ae0c: b 0x0028b078 */ /* delay 0028ae10 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000054),c->f[3]);goto L_0028b078;
L_0028ae18:;
/* 0028ae18: lui at,0x43af */ c->r[1]=sx(UINT32_C(0x43af0000));
/* 0028ae1c: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028ae20: lwc1 f2,-0x5b18(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4e8));
/* 0028ae24: lwc1 f3,-0x5b14(gp) */ c->f[3]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4ec));
/* 0028ae28: lui at,0xc366 */ c->r[1]=sx(UINT32_C(0xc3660000));
/* 0028ae2c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028ae30: b 0x0028ae58 */ /* delay 0028ae34 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000050),c->f[1]);goto L_0028ae58;
L_0028ae38:;
/* 0028ae38: lui at,0x43af */ c->r[1]=sx(UINT32_C(0x43af0000));
/* 0028ae3c: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028ae40: lwc1 f2,-0x5b10(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4f0));
/* 0028ae44: lui at,0xc3c3 */ c->r[1]=sx(UINT32_C(0xc3c30000));
/* 0028ae48: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028ae4c: lui at,0xc316 */ c->r[1]=sx(UINT32_C(0xc3160000));
/* 0028ae50: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028ae54: swc1 f1,0x50(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000050),c->f[1]);
L_0028ae58:;
/* 0028ae58: swc1 f0,0x48(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000048),c->f[0]);
/* 0028ae5c: swc1 f2,0x54(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000054),c->f[2]);
/* 0028ae60: swc1 f3,0x44(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000044),c->f[3]);
/* 0028ae64: b 0x0028b07c */ /* delay 0028ae68 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000040),(uint32_t)c->r[0]);goto L_0028b07c;
L_0028ae70:;
/* 0028ae70: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028ae74: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028ae7c);/* delay 0028ae78 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005aa8));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028ae7c: move a0,s2 */ c->r[4]=c->r[18];
/* 0028ae80: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028ae88);/* delay 0028ae84 */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028ae88: lw v1,0x0(s2) */ c->r[3]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028ae8c: addiu s1,v1,0x3c0 */ c->r[17]=sx((uint32_t)c->r[3]+UINT32_C(0x000003c0));
/* 0028ae90: lw v0,0x78(s1) */ c->r[2]=sx(word((uint32_t)c->r[17]+UINT32_C(0x00000078)));
/* 0028ae94: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 0028ae98: beq v0,zero,0x0028b080 */ {int taken=(c->r[2]==c->r[0]);/* delay 0028ae9c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));if(taken){goto L_0028b080;}}
/* 0028aea0: jal 0x0016e560 */ c->r[31]=UINT64_C(0x0028aea8);/* delay 0028aea4 */ c->r[4]=c->r[17];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=effBTLModelGetID(c->r[4]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028aea8: move v1,v0 */ c->r[3]=c->r[2];
/* 0028aeac: li v0,0x108 */ c->r[2]=sx(UINT32_C(0x00000108));
/* 0028aeb0: beq v1,v0,0x0028af18 */ {int taken=(c->r[3]==c->r[2]);/* delay 0028aeb4 */ c->r[2]=sx(UINT32_C(0x00000125));if(taken){goto L_0028af18;}}
/* 0028aeb8: bne v1,v0,0x0028af68 */ {int taken=(c->r[3]!=c->r[2]);/* delay 0028aebc */ c->r[4]=c->r[17];if(taken){goto L_0028af68;}}
/* 0028aec0: lwc1 f1,0x8(sp) */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028aec4: lui at,0x4470 */ c->r[1]=sx(UINT32_C(0x44700000));
/* 0028aec8: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028aecc: lwc1 f2,-0x5b0c(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4f4));
/* 0028aed0: add.S f1,f1,f0 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[0]);
/* 0028aed4: lui at,0x4461 */ c->r[1]=sx(UINT32_C(0x44610000));
/* 0028aed8: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028aedc: lui at,0x4416 */ c->r[1]=sx(UINT32_C(0x44160000));
/* 0028aee0: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028aee4: lui at,0x4396 */ c->r[1]=sx(UINT32_C(0x43960000));
/* 0028aee8: mtc1 at,f4 */ c->f[4]=(uint32_t)c->r[1];
/* 0028aeec: lui at,0x42c8 */ c->r[1]=sx(UINT32_C(0x42c80000));
/* 0028aef0: mtc1 at,f5 */ c->f[5]=(uint32_t)c->r[1];
/* 0028aef4: swc1 f2,0x4(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),c->f[2]);
/* 0028aef8: swc1 f1,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[1]);
/* 0028aefc: sw zero,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[0]);
/* 0028af00: swc1 f3,0x50(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000050),c->f[3]);
/* 0028af04: swc1 f0,0x54(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000054),c->f[0]);
/* 0028af08: swc1 f4,0x44(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000044),c->f[4]);
/* 0028af0c: b 0x0028af60 */ /* delay 0028af10 */ sw((uint32_t)c->r[17]+UINT32_C(0x00000048),c->f[5]);goto L_0028af60;
L_0028af18:;
/* 0028af18: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028af1c: lwc1 f1,-0x5b08(gp) */ c->f[1]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4f8));
/* 0028af20: lui at,0x43fa */ c->r[1]=sx(UINT32_C(0x43fa0000));
/* 0028af24: mtc1 at,f4 */ c->f[4]=(uint32_t)c->r[1];
/* 0028af28: add.S f0,f0,f1 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[1]);
/* 0028af2c: lui at,0xc448 */ c->r[1]=sx(UINT32_C(0xc4480000));
/* 0028af30: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 0028af34: lui at,0x447a */ c->r[1]=sx(UINT32_C(0x447a0000));
/* 0028af38: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028af3c: lui at,0x4316 */ c->r[1]=sx(UINT32_C(0x43160000));
/* 0028af40: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 0028af44: sw zero,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),(uint32_t)c->r[0]);
/* 0028af48: swc1 f0,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);
/* 0028af4c: sw zero,0x4(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),(uint32_t)c->r[0]);
/* 0028af50: swc1 f4,0x50(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000050),c->f[4]);
/* 0028af54: swc1 f2,0x54(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000054),c->f[2]);
/* 0028af58: swc1 f1,0x44(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000044),c->f[1]);
/* 0028af5c: swc1 f3,0x48(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000048),c->f[3]);
L_0028af60:;
/* 0028af60: sw zero,0x40(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000040),(uint32_t)c->r[0]);
/* 0028af64: move a0,s1 */ c->r[4]=c->r[17];
L_0028af68:;
/* 0028af68: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028af70);/* delay 0028af6c */ c->r[5]=c->r[29];nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028af70: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028af74: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028af78: b 0x0028b080 */ /* delay 0028af7c */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;
L_0028af80:;
/* 0028af80: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028af84: addiu a0,a0,0x5ad0 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005ad0));
L_0028af88:;
/* 0028af88: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028af90);/* delay 0028af8c */ (void)0;nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028af90: move a0,s2 */ c->r[4]=c->r[18];
/* 0028af94: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028af9c);/* delay 0028af98 */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028af9c: b 0x0028b080 */ /* delay 0028afa0 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_0028b080;
L_0028afa8:;
/* 0028afa8: lui a0,0x54 */ c->r[4]=sx(UINT32_C(0x00540000));
/* 0028afac: jal 0x002d4748 */ c->r[31]=UINT64_C(0x0028afb4);/* delay 0028afb0 */ c->r[4]=sx((uint32_t)c->r[4]+UINT32_C(0x00005af8));nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);c->r[2]=nocturneBattleFormationNativePrintf((uint32_t)c->r[31]-8u,c->r[4],c->r[29],c->r[31]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028afb4: move a0,s2 */ c->r[4]=c->r[18];
/* 0028afb8: jal 0x0028a340 */ c->r[31]=UINT64_C(0x0028afc0);/* delay 0028afbc */ c->r[5]=sx(UINT32_C(0x00000200));body_0028a340(c);
/* 0028afc0: lw v0,0x0(s2) */ c->r[2]=sx(word((uint32_t)c->r[18]+UINT32_C(0x00000000)));
/* 0028afc4: addiu s1,v0,0x3c0 */ c->r[17]=sx((uint32_t)c->r[2]+UINT32_C(0x000003c0));
/* 0028afc8: jal 0x0028a2e0 */ c->r[31]=UINT64_C(0x0028afd0);/* delay 0028afcc */ c->r[4]=c->r[17];body_0028a2e0(c);
/* 0028afd0: sqc2 vf10,0x0(sp) */ sqc2(10,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028afd4: lwc1 f1,0x4(sp) */ c->f[1]=word((uint32_t)c->r[29]+UINT32_C(0x00000004));
/* 0028afd8: move a0,s1 */ c->r[4]=c->r[17];
/* 0028afdc: lwc1 f0,0x8(sp) */ c->f[0]=word((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 0028afe0: move a1,sp */ c->r[5]=c->r[29];
/* 0028afe4: lui at,0x442f */ c->r[1]=sx(UINT32_C(0x442f0000));
/* 0028afe8: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 0028afec: lui at,0x4348 */ c->r[1]=sx(UINT32_C(0x43480000));
/* 0028aff0: mtc1 at,f20 */ c->f[20]=(uint32_t)c->r[1];
/* 0028aff4: add.S f0,f0,f2 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[2]);
/* 0028aff8: sub.S f1,f1,f20 */ c->f[1]=EE_FPU_SUB_S(c->f[1],c->f[20]);
/* 0028affc: swc1 f0,0x8(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000008),c->f[0]);
/* 0028b000: jal 0x0028a0e8 */ c->r[31]=UINT64_C(0x0028b008);/* delay 0028b004 */ sw((uint32_t)c->r[29]+UINT32_C(0x00000004),c->f[1]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);nbSetFormPos(c->r[4],c->r[5]);nocturneBattleFormationSetStackPointer((uint32_t)c->r[29]);
/* 0028b008: lq v0,0x0(sp) */ lq(c,2,(uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 0028b00c: sq v0,0x0(s1) */ sq(c,2,(uint32_t)c->r[17]+UINT32_C(0x00000000));
/* 0028b010: lwc1 f2,-0x5b04(gp) */ c->f[2]=word((uint32_t)c->r[28]+UINT32_C(0xffffa4fc));
/* 0028b014: lwc1 f1,0x5c(s1) */ c->f[1]=word((uint32_t)c->r[17]+UINT32_C(0x0000005c));
/* 0028b018: clear f3 */ c->f[3]=0;
/* 0028b01c: lui at,0xc448 */ c->r[1]=sx(UINT32_C(0xc4480000));
/* 0028b020: mtc1 at,f4 */ c->f[4]=(uint32_t)c->r[1];
/* 0028b024: nop  */ (void)0;
/* 0028b028: nop  */ (void)0;
/* 0028b02c: div.S f20,f20,f1 */ c->f[20]=EE_FPU_DIV_S(c->f[20],c->f[1]);
/* 0028b030: lui at,0x4396 */ c->r[1]=sx(UINT32_C(0x43960000));
/* 0028b034: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 0028b038: nop  */ (void)0;
/* 0028b03c: nop  */ (void)0;
/* 0028b040: div.S f2,f2,f1 */ c->f[2]=EE_FPU_DIV_S(c->f[2],c->f[1]);
/* 0028b044: swc1 f20,0x50(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000050),c->f[20]);
/* 0028b048: nop  */ (void)0;
/* 0028b04c: nop  */ (void)0;
/* 0028b050: div.S f0,f0,f1 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[1]);
/* 0028b054: swc1 f2,0x54(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000054),c->f[2]);
/* 0028b058: nop  */ (void)0;
/* 0028b05c: nop  */ (void)0;
/* 0028b060: div.S f3,f3,f1 */ c->f[3]=EE_FPU_DIV_S(c->f[3],c->f[1]);
/* 0028b064: swc1 f0,0x48(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000048),c->f[0]);
/* 0028b068: nop  */ (void)0;
/* 0028b06c: nop  */ (void)0;
/* 0028b070: div.S f4,f4,f1 */ c->f[4]=EE_FPU_DIV_S(c->f[4],c->f[1]);
/* 0028b074: swc1 f3,0x40(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000040),c->f[3]);
L_0028b078:;
/* 0028b078: swc1 f4,0x44(s1) */ sw((uint32_t)c->r[17]+UINT32_C(0x00000044),c->f[4]);
L_0028b07c:;
/* 0028b07c: ld s0,0x20(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
L_0028b080:;
/* 0028b080: ld s1,0x28(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000028));
L_0028b084:;
/* 0028b084: ld s2,0x30(sp) */ c->r[18]=quad((uint32_t)c->r[29]+UINT32_C(0x00000030));
/* 0028b088: ld s3,0x38(sp) */ c->r[19]=quad((uint32_t)c->r[29]+UINT32_C(0x00000038));
/* 0028b08c: ld ra,0x40(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000040));
/* 0028b090: lwc1 f20,0x48(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x00000048));
/* 0028b094: jr ra */ /* delay 0028b098 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000050));return;
}
static BattleFormationValues begin(void){BattleFormationValues c={0};c.r[28]=UINT64_C(0x00554170);c.r[29]=nocturneBattleFormationStackPointer();for(unsigned r=16;r<=23;++r)c.r[r]=nocturneBattleFormationReadGpr(r);c.r[31]=nocturneBattleFormationReadGpr(31);for(unsigned f=20;f<=25;++f)c.f[f]=nocturneBattleFormationReadFpr(f);return c;}
uint64_t ps2BattleFormation_0024D490(uint64_t p0,uint64_t p1){BattleFormationValues c=begin();c.r[4]=p0;c.r[5]=p1;body_0024d490(&c);nocturneBattleFormationSetStackPointer((uint32_t)c.r[29]);return c.r[2];}
void ps2BattleFormation_0024D550(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3){BattleFormationValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;c.r[7]=p3;body_0024d550(&c);nocturneBattleFormationSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleFormation_0024D8C0(uint64_t p0,uint64_t p1,uint64_t p2){BattleFormationValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_0024d8c0(&c);nocturneBattleFormationSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleFormation_0024E178(uint64_t p0,uint64_t p1,uint64_t p2){BattleFormationValues c=begin();c.r[4]=p0;c.r[5]=p1;c.r[6]=p2;body_0024e178(&c);nocturneBattleFormationSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleFormation_00259740(uint64_t p0,uint64_t p1){BattleFormationValues c=begin();c.r[4]=p0;c.r[5]=p1;body_00259740(&c);nocturneBattleFormationSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleFormation_0028A2E0(uint64_t p0){BattleFormationValues c=begin();c.r[4]=p0;body_0028a2e0(&c);nocturneBattleFormationSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleFormation_0028A340(uint64_t p0,uint64_t p1){BattleFormationValues c=begin();c.r[4]=p0;c.r[5]=p1;body_0028a340(&c);nocturneBattleFormationSetStackPointer((uint32_t)c.r[29]);}
void ps2BattleFormation_0028A758(uint64_t p0){BattleFormationValues c=begin();c.r[4]=p0;body_0028a758(&c);nocturneBattleFormationSetStackPointer((uint32_t)c.r[29]);}
