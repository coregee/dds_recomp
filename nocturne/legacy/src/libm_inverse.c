/* Complete8 original SLUS_209.11 binary32 libm bodies/790 instructions.
 * Fixed native-PC scalar statements and real typed dependencies; no host libm.
 * Newlib/Sun fdlibm is lineage context; native words decide all differences.
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 */
#include "libm_inverse.h"
#include "libm_trig.h"
#include "ps2_sdk_neighbors.h"
#include "ee_fpu.h"
#include "script_compare.h"

#include <string.h>
typedef struct LibmInverseValues {uint64_t r[32];uint32_t f[32],condition;} LibmInverseValues;
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static int neg(uint64_t v){return (int)(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint64_t sar(uint32_t v,unsigned n){return sx(n==0?v:(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32u-n)):0u));}
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveLibmInverseAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static float real(uint32_t u){float v;memcpy(&v,&u,4);return v;}

static void body_002cf6b8(LibmInverseValues *c);
static void body_002cf730(LibmInverseValues *c);
static void body_002cf748(LibmInverseValues *c);
static void body_002cf760(LibmInverseValues *c);
static void body_002cfb88(LibmInverseValues *c);
static void body_002d0118(LibmInverseValues *c);
static void body_002d0ca8(LibmInverseValues *c);
static void body_002d0f30(LibmInverseValues *c);

static void body_002cf6b8(LibmInverseValues *c){
/* 002cf6b8: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 002cf6bc: mov.S f0,f12 */ c->f[0]=c->f[12];
/* 002cf6c0: sd ra,0x20(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000020),c->r[31]);
/* 002cf6c4: swc1 f0,0x10(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000010),c->f[0]);
/* 002cf6c8: lui v1,0x7fff */ c->r[3]=sx(UINT32_C(0x7fff0000));
/* 002cf6cc: clear f13 */ c->f[13]=0;
/* 002cf6d0: lw a1,0x10(sp) */ c->r[5]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000010)));
/* 002cf6d4: ori v1,v1,0xffff */ c->r[3]=c->r[3]|UINT64_C(0xffff);
/* 002cf6d8: lui v0,0x3f49 */ c->r[2]=sx(UINT32_C(0x3f490000));
/* 002cf6dc: and v1,a1,v1 */ c->r[3]=c->r[5]&c->r[3];
/* 002cf6e0: ori v0,v0,0xfda */ c->r[2]=c->r[2]|UINT64_C(0xfda);
/* 002cf6e4: slt v0,v0,v1 */ c->r[2]=less(c->r[2],c->r[3]);
/* 002cf6e8: bne v0,zero,0x002cf700 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002cf6ec */ c->r[4]=c->r[29];if(taken){goto L_002cf700;}}
/* 002cf6f0: jal 0x002d0ca8 */ c->r[31]=UINT64_C(0x002cf6f8);/* delay 002cf6f4 */ c->r[4]=sx(UINT32_C(0x00000001));body_002d0ca8(c);
/* 002cf6f8: b 0x002cf728 */ /* delay 002cf6fc */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));goto L_002cf728;
L_002cf700:;
/* 002cf700: jal 0x002cfd68 */ c->r[31]=UINT64_C(0x002cf708);/* delay 002cf704 */ (void)0;nocturneLibmInverseSetStackPointer((uint32_t)c->r[29]);c->r[2]=sx((uint32_t)ps2LibmRemPio2Float(real(c->f[12]),(float *)at((uint32_t)c->r[4])));nocturneLibmInverseSetStackPointer((uint32_t)c->r[29]);
/* 002cf708: li a0,0x1 */ c->r[4]=sx(UINT32_C(0x00000001));
/* 002cf70c: andi v0,v0,0x1 */ c->r[2]=c->r[2]&UINT64_C(0x1);
/* 002cf710: lwc1 f12,0x0(sp) */ c->f[12]=word((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002cf714: sll v0,v0,0x1 */ c->r[2]=sx((uint32_t)c->r[2]<<1u);
/* 002cf718: lwc1 f13,0x4(sp) */ c->f[13]=word((uint32_t)c->r[29]+UINT32_C(0x00000004));
/* 002cf71c: jal 0x002d0ca8 */ c->r[31]=UINT64_C(0x002cf724);/* delay 002cf720 */ c->r[4]=sx((uint32_t)c->r[4]-(uint32_t)c->r[2]);body_002d0ca8(c);
/* 002cf724: ld ra,0x20(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000020));
L_002cf728:;
/* 002cf728: jr ra */ /* delay 002cf72c */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_002cf730(LibmInverseValues *c){
/* 002cf730: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 002cf734: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 002cf738: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002cf73c: j 0x002cf760 */ /* delay 002cf740 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_002cf760(c);return;
}

static void body_002cf748(LibmInverseValues *c){
/* 002cf748: addiu sp,sp,-0x10 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xfffffff0));
/* 002cf74c: sd ra,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[31]);
/* 002cf750: ld ra,0x0(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002cf754: j 0x002cfb88 */ /* delay 002cf758 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000010));body_002cfb88(c);return;
}

static void body_002cf760(LibmInverseValues *c){
/* 002cf760: addiu sp,sp,-0x30 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffd0));
/* 002cf764: mov.S f11,f12 */ c->f[11]=c->f[12];
/* 002cf768: sd ra,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);
/* 002cf76c: swc1 f22,0x28(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000028),c->f[22]);
/* 002cf770: swc1 f21,0x20(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000020),c->f[21]);
/* 002cf774: mfc1 a0,f11 */ c->r[4]=sx(c->f[11]);
/* 002cf778: lui v0,0x7fff */ c->r[2]=sx(UINT32_C(0x7fff0000));
/* 002cf77c: lui a1,0x3f80 */ c->r[5]=sx(UINT32_C(0x3f800000));
/* 002cf780: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002cf784: and v1,a0,v0 */ c->r[3]=c->r[4]&c->r[2];
/* 002cf788: bne v1,a1,0x002cf7b0 */ {int taken=(c->r[3]!=c->r[5]);/* delay 002cf78c */ sw((uint32_t)c->r[29]+UINT32_C(0x00000018),c->f[20]);if(taken){goto L_002cf7b0;}}
/* 002cf790: clear f0 */ c->f[0]=0;
/* 002cf794: bgtz a0,0x002cfb70 */ {int taken=((!neg(c->r[4])&&c->r[4]));/* delay 002cf798 */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));if(taken){goto L_002cfb70;}}
/* 002cf79c: lui at,0x4049 */ c->r[1]=sx(UINT32_C(0x40490000));
/* 002cf7a0: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cf7a4: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cf7a8: b 0x002cfb74 */ /* delay 002cf7ac */ c->f[22]=word((uint32_t)c->r[29]+UINT32_C(0x00000028));goto L_002cfb74;
L_002cf7b0:;
/* 002cf7b0: slt v0,a1,v1 */ c->r[2]=less(c->r[5],c->r[3]);
/* 002cf7b4: beq v0,zero,0x002cf7d8 */ {int taken=(c->r[2]==c->r[0]);/* delay 002cf7b8 */ c->r[2]=sx(UINT32_C(0x3eff0000));if(taken){goto L_002cf7d8;}}
/* 002cf7bc: sub.S f0,f11,f11 */ c->f[0]=EE_FPU_SUB_S(c->f[11],c->f[11]);
/* 002cf7c0: nop  */ (void)0;
/* 002cf7c4: nop  */ (void)0;
/* 002cf7c8: div.S f0,f0,f0 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[0]);
/* 002cf7cc: b 0x002cfb70 */ /* delay 002cf7d0 */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));goto L_002cfb70;
L_002cf7d8:;
/* 002cf7d8: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002cf7dc: slt v0,v0,v1 */ c->r[2]=less(c->r[2],c->r[3]);
/* 002cf7e0: bne v0,zero,0x002cf908 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002cf7e4 */ c->r[2]=sx(UINT32_C(0x23000000));if(taken){goto L_002cf908;}}
/* 002cf7e8: lui at,0x3fc9 */ c->r[1]=sx(UINT32_C(0x3fc90000));
/* 002cf7ec: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cf7f0: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cf7f4: slt v0,v0,v1 */ c->r[2]=less(c->r[2],c->r[3]);
/* 002cf7f8: beq v0,zero,0x002cfb70 */ {int taken=(c->r[2]==c->r[0]);/* delay 002cf7fc */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));if(taken){goto L_002cfb70;}}
/* 002cf800: mul.S f21,f11,f11 */ c->f[21]=EE_FPU_MUL_S(c->f[11],c->f[11]);
/* 002cf804: lui at,0x3811 */ c->r[1]=sx(UINT32_C(0x38110000));
/* 002cf808: ori at,at,0xef08 */ c->r[1]=c->r[1]|UINT64_C(0xef08);
/* 002cf80c: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002cf810: lui at,0x3a4f */ c->r[1]=sx(UINT32_C(0x3a4f0000));
/* 002cf814: ori at,at,0x7f04 */ c->r[1]=c->r[1]|UINT64_C(0x7f04);
/* 002cf818: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 002cf81c: lui at,0xbd24 */ c->r[1]=sx(UINT32_C(0xbd240000));
/* 002cf820: ori at,at,0x1146 */ c->r[1]=c->r[1]|UINT64_C(0x1146);
/* 002cf824: mtc1 at,f7 */ c->f[7]=(uint32_t)c->r[1];
/* 002cf828: lui at,0x3d9d */ c->r[1]=sx(UINT32_C(0x3d9d0000));
/* 002cf82c: ori at,at,0xc62d */ c->r[1]=c->r[1]|UINT64_C(0xc62d);
/* 002cf830: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 002cf834: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf838: lui at,0xbf30 */ c->r[1]=sx(UINT32_C(0xbf300000));
/* 002cf83c: ori at,at,0x3360 */ c->r[1]=c->r[1]|UINT64_C(0x3360);
/* 002cf840: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cf844: mul.S f2,f21,f2 */ c->f[2]=EE_FPU_MUL_S(c->f[21],c->f[2]);
/* 002cf848: lui at,0x3e4e */ c->r[1]=sx(UINT32_C(0x3e4e0000));
/* 002cf84c: ori at,at,0xaa8 */ c->r[1]=c->r[1]|UINT64_C(0xaa8);
/* 002cf850: mtc1 at,f6 */ c->f[6]=(uint32_t)c->r[1];
/* 002cf854: lui at,0x4001 */ c->r[1]=sx(UINT32_C(0x40010000));
/* 002cf858: ori at,at,0x572c */ c->r[1]=c->r[1]|UINT64_C(0x572c);
/* 002cf85c: mtc1 at,f4 */ c->f[4]=(uint32_t)c->r[1];
/* 002cf860: lui at,0xbea6 */ c->r[1]=sx(UINT32_C(0xbea60000));
/* 002cf864: ori at,at,0xb08f */ c->r[1]=c->r[1]|UINT64_C(0xb08f);
/* 002cf868: mtc1 at,f9 */ c->f[9]=(uint32_t)c->r[1];
/* 002cf86c: add.S f1,f1,f3 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[3]);
/* 002cf870: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002cf874: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 002cf878: add.S f2,f2,f0 */ c->f[2]=EE_FPU_ADD_S(c->f[2],c->f[0]);
/* 002cf87c: lui at,0x33a2 */ c->r[1]=sx(UINT32_C(0x33a20000));
/* 002cf880: ori at,at,0x2168 */ c->r[1]=c->r[1]|UINT64_C(0x2168);
/* 002cf884: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cf888: lui at,0xc019 */ c->r[1]=sx(UINT32_C(0xc0190000));
/* 002cf88c: ori at,at,0xd138 */ c->r[1]=c->r[1]|UINT64_C(0xd138);
/* 002cf890: mtc1 at,f5 */ c->f[5]=(uint32_t)c->r[1];
/* 002cf894: lui at,0x3e2a */ c->r[1]=sx(UINT32_C(0x3e2a0000));
/* 002cf898: ori at,at,0xaaaa */ c->r[1]=c->r[1]|UINT64_C(0xaaaa);
/* 002cf89c: mtc1 at,f8 */ c->f[8]=(uint32_t)c->r[1];
/* 002cf8a0: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf8a4: lui at,0x3fc9 */ c->r[1]=sx(UINT32_C(0x3fc90000));
/* 002cf8a8: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cf8ac: mtc1 at,f10 */ c->f[10]=(uint32_t)c->r[1];
/* 002cf8b0: mul.S f2,f21,f2 */ c->f[2]=EE_FPU_MUL_S(c->f[21],c->f[2]);
/* 002cf8b4: add.S f1,f1,f7 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[7]);
/* 002cf8b8: add.S f2,f2,f4 */ c->f[2]=EE_FPU_ADD_S(c->f[2],c->f[4]);
/* 002cf8bc: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf8c0: mul.S f2,f21,f2 */ c->f[2]=EE_FPU_MUL_S(c->f[21],c->f[2]);
/* 002cf8c4: add.S f1,f1,f6 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[6]);
/* 002cf8c8: add.S f2,f2,f5 */ c->f[2]=EE_FPU_ADD_S(c->f[2],c->f[5]);
/* 002cf8cc: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf8d0: mul.S f2,f21,f2 */ c->f[2]=EE_FPU_MUL_S(c->f[21],c->f[2]);
/* 002cf8d4: add.S f1,f1,f9 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[9]);
/* 002cf8d8: add.S f22,f2,f3 */ c->f[22]=EE_FPU_ADD_S(c->f[2],c->f[3]);
/* 002cf8dc: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf8e0: add.S f1,f1,f8 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[8]);
/* 002cf8e4: mul.S f20,f21,f1 */ c->f[20]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf8e8: nop  */ (void)0;
/* 002cf8ec: nop  */ (void)0;
/* 002cf8f0: div.S f12,f20,f22 */ c->f[12]=EE_FPU_DIV_S(c->f[20],c->f[22]);
/* 002cf8f4: mul.S f1,f11,f12 */ c->f[1]=EE_FPU_MUL_S(c->f[11],c->f[12]);
/* 002cf8f8: sub.S f0,f0,f1 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[1]);
/* 002cf8fc: sub.S f0,f11,f0 */ c->f[0]=EE_FPU_SUB_S(c->f[11],c->f[0]);
/* 002cf900: b 0x002cfb70 */ /* delay 002cf904 */ c->f[0]=EE_FPU_SUB_S(c->f[10],c->f[0]);goto L_002cfb70;
L_002cf908:;
/* 002cf908: bgez a0,0x002cfa38 */ {int taken=(!neg(c->r[4]));/* delay 002cf90c */ (void)0;if(taken){goto L_002cfa38;}}
/* 002cf910: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002cf914: mtc1 at,f10 */ c->f[10]=(uint32_t)c->r[1];
/* 002cf918: lui at,0x3f00 */ c->r[1]=sx(UINT32_C(0x3f000000));
/* 002cf91c: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 002cf920: add.S f2,f11,f10 */ c->f[2]=EE_FPU_ADD_S(c->f[11],c->f[10]);
/* 002cf924: lui at,0x3811 */ c->r[1]=sx(UINT32_C(0x38110000));
/* 002cf928: ori at,at,0xef08 */ c->r[1]=c->r[1]|UINT64_C(0xef08);
/* 002cf92c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cf930: lui at,0x3a4f */ c->r[1]=sx(UINT32_C(0x3a4f0000));
/* 002cf934: ori at,at,0x7f04 */ c->r[1]=c->r[1]|UINT64_C(0x7f04);
/* 002cf938: mtc1 at,f5 */ c->f[5]=(uint32_t)c->r[1];
/* 002cf93c: lui at,0xbd24 */ c->r[1]=sx(UINT32_C(0xbd240000));
/* 002cf940: ori at,at,0x1146 */ c->r[1]=c->r[1]|UINT64_C(0x1146);
/* 002cf944: mtc1 at,f6 */ c->f[6]=(uint32_t)c->r[1];
/* 002cf948: lui at,0x3d9d */ c->r[1]=sx(UINT32_C(0x3d9d0000));
/* 002cf94c: ori at,at,0xc62d */ c->r[1]=c->r[1]|UINT64_C(0xc62d);
/* 002cf950: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002cf954: mul.S f21,f2,f3 */ c->f[21]=EE_FPU_MUL_S(c->f[2],c->f[3]);
/* 002cf958: lui at,0x4001 */ c->r[1]=sx(UINT32_C(0x40010000));
/* 002cf95c: ori at,at,0x572c */ c->r[1]=c->r[1]|UINT64_C(0x572c);
/* 002cf960: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 002cf964: lui at,0xbf30 */ c->r[1]=sx(UINT32_C(0xbf300000));
/* 002cf968: ori at,at,0x3360 */ c->r[1]=c->r[1]|UINT64_C(0x3360);
/* 002cf96c: mtc1 at,f4 */ c->f[4]=(uint32_t)c->r[1];
/* 002cf970: lui at,0x3e4e */ c->r[1]=sx(UINT32_C(0x3e4e0000));
/* 002cf974: ori at,at,0xaa8 */ c->r[1]=c->r[1]|UINT64_C(0xaa8);
/* 002cf978: mtc1 at,f7 */ c->f[7]=(uint32_t)c->r[1];
/* 002cf97c: lui at,0xbea6 */ c->r[1]=sx(UINT32_C(0xbea60000));
/* 002cf980: ori at,at,0xb08f */ c->r[1]=c->r[1]|UINT64_C(0xb08f);
/* 002cf984: mtc1 at,f9 */ c->f[9]=(uint32_t)c->r[1];
/* 002cf988: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cf98c: lui at,0xc019 */ c->r[1]=sx(UINT32_C(0xc0190000));
/* 002cf990: ori at,at,0xd138 */ c->r[1]=c->r[1]|UINT64_C(0xd138);
/* 002cf994: mtc1 at,f3 */ c->f[3]=(uint32_t)c->r[1];
/* 002cf998: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf99c: lui at,0x3e2a */ c->r[1]=sx(UINT32_C(0x3e2a0000));
/* 002cf9a0: ori at,at,0xaaaa */ c->r[1]=c->r[1]|UINT64_C(0xaaaa);
/* 002cf9a4: mtc1 at,f8 */ c->f[8]=(uint32_t)c->r[1];
/* 002cf9a8: mov.S f12,f21 */ c->f[12]=c->f[21];
/* 002cf9ac: add.S f0,f0,f5 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[5]);
/* 002cf9b0: add.S f1,f1,f4 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[4]);
/* 002cf9b4: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cf9b8: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf9bc: add.S f0,f0,f6 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[6]);
/* 002cf9c0: add.S f1,f1,f2 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[2]);
/* 002cf9c4: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cf9c8: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf9cc: add.S f0,f0,f7 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[7]);
/* 002cf9d0: add.S f1,f1,f3 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[3]);
/* 002cf9d4: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cf9d8: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cf9dc: add.S f0,f0,f9 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[9]);
/* 002cf9e0: add.S f22,f1,f10 */ c->f[22]=EE_FPU_ADD_S(c->f[1],c->f[10]);
/* 002cf9e4: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cf9e8: add.S f0,f0,f8 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[8]);
/* 002cf9ec: jal 0x002d0118 */ c->r[31]=UINT64_C(0x002cf9f4);/* delay 002cf9f0 */ c->f[20]=EE_FPU_MUL_S(c->f[21],c->f[0]);body_002d0118(c);
/* 002cf9f4: mov.S f13,f0 */ c->f[13]=c->f[0];
/* 002cf9f8: lui at,0x33a2 */ c->r[1]=sx(UINT32_C(0x33a20000));
/* 002cf9fc: ori at,at,0x2168 */ c->r[1]=c->r[1]|UINT64_C(0x2168);
/* 002cfa00: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002cfa04: lui at,0x4049 */ c->r[1]=sx(UINT32_C(0x40490000));
/* 002cfa08: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cfa0c: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 002cfa10: nop  */ (void)0;
/* 002cfa14: nop  */ (void)0;
/* 002cfa18: div.S f12,f20,f22 */ c->f[12]=EE_FPU_DIV_S(c->f[20],c->f[22]);
/* 002cfa1c: mul.S f0,f12,f13 */ c->f[0]=EE_FPU_MUL_S(c->f[12],c->f[13]);
/* 002cfa20: sub.S f0,f0,f1 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[1]);
/* 002cfa24: add.S f0,f13,f0 */ c->f[0]=EE_FPU_ADD_S(c->f[13],c->f[0]);
/* 002cfa28: add.S f0,f0,f0 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[0]);
/* 002cfa2c: b 0x002cfb6c */ /* delay 002cfa30 */ c->f[0]=EE_FPU_SUB_S(c->f[2],c->f[0]);goto L_002cfb6c;
L_002cfa38:;
/* 002cfa38: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002cfa3c: mtc1 at,f20 */ c->f[20]=(uint32_t)c->r[1];
/* 002cfa40: lui at,0x3f00 */ c->r[1]=sx(UINT32_C(0x3f000000));
/* 002cfa44: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002cfa48: sub.S f0,f20,f11 */ c->f[0]=EE_FPU_SUB_S(c->f[20],c->f[11]);
/* 002cfa4c: mul.S f21,f0,f1 */ c->f[21]=EE_FPU_MUL_S(c->f[0],c->f[1]);
/* 002cfa50: jal 0x002d0118 */ c->r[31]=UINT64_C(0x002cfa58);/* delay 002cfa54 */ c->f[12]=c->f[21];body_002d0118(c);
/* 002cfa58: mov.S f11,f0 */ c->f[11]=c->f[0];
/* 002cfa5c: mov.S f13,f11 */ c->f[13]=c->f[11];
/* 002cfa60: swc1 f0,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),c->f[0]);
/* 002cfa64: li v0,-0x1000 */ c->r[2]=sx(UINT32_C(0xfffff000));
/* 002cfa68: lw v1,0x0(sp) */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000000)));
/* 002cfa6c: and v1,v1,v0 */ c->r[3]=c->r[3]&c->r[2];
/* 002cfa70: mtc1 v1,f11 */ c->f[11]=(uint32_t)c->r[3];
/* 002cfa74: mul.S f3,f11,f11 */ c->f[3]=EE_FPU_MUL_S(c->f[11],c->f[11]);
/* 002cfa78: lui at,0x3811 */ c->r[1]=sx(UINT32_C(0x38110000));
/* 002cfa7c: ori at,at,0xef08 */ c->r[1]=c->r[1]|UINT64_C(0xef08);
/* 002cfa80: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cfa84: lui at,0x3a4f */ c->r[1]=sx(UINT32_C(0x3a4f0000));
/* 002cfa88: ori at,at,0x7f04 */ c->r[1]=c->r[1]|UINT64_C(0x7f04);
/* 002cfa8c: mtc1 at,f5 */ c->f[5]=(uint32_t)c->r[1];
/* 002cfa90: lui at,0xbd24 */ c->r[1]=sx(UINT32_C(0xbd240000));
/* 002cfa94: ori at,at,0x1146 */ c->r[1]=c->r[1]|UINT64_C(0x1146);
/* 002cfa98: mtc1 at,f9 */ c->f[9]=(uint32_t)c->r[1];
/* 002cfa9c: lui at,0x3d9d */ c->r[1]=sx(UINT32_C(0x3d9d0000));
/* 002cfaa0: ori at,at,0xc62d */ c->r[1]=c->r[1]|UINT64_C(0xc62d);
/* 002cfaa4: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002cfaa8: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cfaac: lui at,0xbf30 */ c->r[1]=sx(UINT32_C(0xbf300000));
/* 002cfab0: ori at,at,0x3360 */ c->r[1]=c->r[1]|UINT64_C(0x3360);
/* 002cfab4: mtc1 at,f4 */ c->f[4]=(uint32_t)c->r[1];
/* 002cfab8: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cfabc: lui at,0x3e4e */ c->r[1]=sx(UINT32_C(0x3e4e0000));
/* 002cfac0: ori at,at,0xaa8 */ c->r[1]=c->r[1]|UINT64_C(0xaa8);
/* 002cfac4: mtc1 at,f8 */ c->f[8]=(uint32_t)c->r[1];
/* 002cfac8: lui at,0x4001 */ c->r[1]=sx(UINT32_C(0x40010000));
/* 002cfacc: ori at,at,0x572c */ c->r[1]=c->r[1]|UINT64_C(0x572c);
/* 002cfad0: mtc1 at,f7 */ c->f[7]=(uint32_t)c->r[1];
/* 002cfad4: sub.S f3,f21,f3 */ c->f[3]=EE_FPU_SUB_S(c->f[21],c->f[3]);
/* 002cfad8: lui at,0xbea6 */ c->r[1]=sx(UINT32_C(0xbea60000));
/* 002cfadc: ori at,at,0xb08f */ c->r[1]=c->r[1]|UINT64_C(0xb08f);
/* 002cfae0: mtc1 at,f10 */ c->f[10]=(uint32_t)c->r[1];
/* 002cfae4: add.S f2,f13,f11 */ c->f[2]=EE_FPU_ADD_S(c->f[13],c->f[11]);
/* 002cfae8: add.S f0,f0,f5 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[5]);
/* 002cfaec: lui at,0x3e2a */ c->r[1]=sx(UINT32_C(0x3e2a0000));
/* 002cfaf0: ori at,at,0xaaaa */ c->r[1]=c->r[1]|UINT64_C(0xaaaa);
/* 002cfaf4: mtc1 at,f5 */ c->f[5]=(uint32_t)c->r[1];
/* 002cfaf8: add.S f1,f1,f4 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[4]);
/* 002cfafc: lui at,0xc019 */ c->r[1]=sx(UINT32_C(0xc0190000));
/* 002cfb00: ori at,at,0xd138 */ c->r[1]=c->r[1]|UINT64_C(0xd138);
/* 002cfb04: mtc1 at,f6 */ c->f[6]=(uint32_t)c->r[1];
/* 002cfb08: nop  */ (void)0;
/* 002cfb0c: nop  */ (void)0;
/* 002cfb10: div.S f3,f3,f2 */ c->f[3]=EE_FPU_DIV_S(c->f[3],c->f[2]);
/* 002cfb14: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cfb18: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cfb1c: add.S f0,f0,f9 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[9]);
/* 002cfb20: add.S f1,f1,f7 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[7]);
/* 002cfb24: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cfb28: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cfb2c: add.S f0,f0,f8 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[8]);
/* 002cfb30: add.S f1,f1,f6 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[6]);
/* 002cfb34: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cfb38: mul.S f1,f21,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[21],c->f[1]);
/* 002cfb3c: add.S f0,f0,f10 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[10]);
/* 002cfb40: add.S f22,f1,f20 */ c->f[22]=EE_FPU_ADD_S(c->f[1],c->f[20]);
/* 002cfb44: mul.S f0,f21,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cfb48: add.S f0,f0,f5 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[5]);
/* 002cfb4c: mul.S f20,f21,f0 */ c->f[20]=EE_FPU_MUL_S(c->f[21],c->f[0]);
/* 002cfb50: nop  */ (void)0;
/* 002cfb54: nop  */ (void)0;
/* 002cfb58: div.S f12,f20,f22 */ c->f[12]=EE_FPU_DIV_S(c->f[20],c->f[22]);
/* 002cfb5c: mul.S f0,f12,f13 */ c->f[0]=EE_FPU_MUL_S(c->f[12],c->f[13]);
/* 002cfb60: add.S f0,f0,f3 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[3]);
/* 002cfb64: add.S f0,f11,f0 */ c->f[0]=EE_FPU_ADD_S(c->f[11],c->f[0]);
/* 002cfb68: add.S f0,f0,f0 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[0]);
L_002cfb6c:;
/* 002cfb6c: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
L_002cfb70:;
/* 002cfb70: lwc1 f22,0x28(sp) */ c->f[22]=word((uint32_t)c->r[29]+UINT32_C(0x00000028));
L_002cfb74:;
/* 002cfb74: lwc1 f21,0x20(sp) */ c->f[21]=word((uint32_t)c->r[29]+UINT32_C(0x00000020));
/* 002cfb78: lwc1 f20,0x18(sp) */ c->f[20]=word((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002cfb7c: jr ra */ /* delay 002cfb80 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000030));return;
}

static void body_002cfb88(LibmInverseValues *c){
/* 002cfb88: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002cfb8c: mov.S f1,f12 */ c->f[1]=c->f[12];
/* 002cfb90: sd s0,0x10(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[16]);
/* 002cfb94: sd ra,0x18(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000018),c->r[31]);
/* 002cfb98: mfc1 a2,f13 */ c->r[6]=sx(c->f[13]);
/* 002cfb9c: lui v0,0x7fff */ c->r[2]=sx(UINT32_C(0x7fff0000));
/* 002cfba0: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002cfba4: and t0,a2,v0 */ c->r[8]=c->r[6]&c->r[2];
/* 002cfba8: mfc1 a1,f1 */ c->r[5]=sx(c->f[1]);
/* 002cfbac: lui v1,0x3f80 */ c->r[3]=sx(UINT32_C(0x3f800000));
/* 002cfbb0: bne a2,v1,0x002cfbc8 */ {int taken=(c->r[6]!=c->r[3]);/* delay 002cfbb4 */ c->r[7]=c->r[5]&c->r[2];if(taken){goto L_002cfbc8;}}
/* 002cfbb8: ld s0,0x10(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002cfbbc: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
/* 002cfbc0: j 0x002d0f30 */ /* delay 002cfbc4 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));body_002d0f30(c);return;
L_002cfbc8:;
/* 002cfbc8: lui v0,0x7f */ c->r[2]=sx(UINT32_C(0x007f0000));
/* 002cfbcc: sra a0,a2,0x1e */ c->r[4]=sar((uint32_t)c->r[6],30u);
/* 002cfbd0: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002cfbd4: andi a0,a0,0x2 */ c->r[4]=c->r[4]&UINT64_C(0x2);
/* 002cfbd8: srl v1,a1,0x1f */ c->r[3]=sx((uint32_t)c->r[5]>>31u);
/* 002cfbdc: slt v0,v0,a3 */ c->r[2]=less(c->r[2],c->r[7]);
/* 002cfbe0: bne v0,zero,0x002cfc2c */ {int taken=(c->r[2]!=c->r[0]);/* delay 002cfbe4 */ c->r[16]=c->r[3]|c->r[4];if(taken){goto L_002cfc2c;}}
/* 002cfbe8: li v0,0x2 */ c->r[2]=sx(UINT32_C(0x00000002));
/* 002cfbec: lui at,0x4049 */ c->r[1]=sx(UINT32_C(0x40490000));
/* 002cfbf0: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cfbf4: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cfbf8: beq s0,v0,0x002cfd58 */ {int taken=(c->r[16]==c->r[2]);/* delay 002cfbfc */ c->r[2]=less(c->r[16],sx(UINT32_C(0x00000003)));if(taken){goto L_002cfd58;}}
/* 002cfc00: beql v0,zero,0x002cfc18 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002cfc04 */ c->r[2]=sx(UINT32_C(0x00000003));goto L_002cfc18;}}
/* 002cfc08: bltz s0,0x002cfc30 */ {int taken=(neg(c->r[16]));/* delay 002cfc0c */ c->r[2]=sx(UINT32_C(0x007f0000));if(taken){goto L_002cfc30;}}
/* 002cfc10: b 0x002cfd58 */ /* delay 002cfc14 */ c->f[0]=c->f[1];goto L_002cfd58;
L_002cfc18:;
/* 002cfc18: lui at,0xc049 */ c->r[1]=sx(UINT32_C(0xc0490000));
/* 002cfc1c: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cfc20: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cfc24: beql s0,v0,0x002cfd5c */ {int taken=(c->r[16]==c->r[2]);if(taken){/* delay 002cfc28 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));goto L_002cfd5c;}}
L_002cfc2c:;
/* 002cfc2c: lui v0,0x7f */ c->r[2]=sx(UINT32_C(0x007f0000));
L_002cfc30:;
/* 002cfc30: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002cfc34: slt v0,v0,t0 */ c->r[2]=less(c->r[2],c->r[8]);
/* 002cfc38: bne v0,zero,0x002cfc68 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002cfc3c */ c->r[3]=sx((uint32_t)c->r[7]-(uint32_t)c->r[8]);if(taken){goto L_002cfc68;}}
/* 002cfc40: lui at,0xbfc9 */ c->r[1]=sx(UINT32_C(0xbfc90000));
/* 002cfc44: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cfc48: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cfc4c: bltz a1,0x002cfd58 */ {int taken=(neg(c->r[5]));/* delay 002cfc50 */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));if(taken){goto L_002cfd58;}}
/* 002cfc54: lui at,0x3fc9 */ c->r[1]=sx(UINT32_C(0x3fc90000));
/* 002cfc58: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cfc5c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cfc60: b 0x002cfd60 */ /* delay 002cfc64 */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));goto L_002cfd60;
L_002cfc68:;
/* 002cfc68: lui at,0x3fc9 */ c->r[1]=sx(UINT32_C(0x3fc90000));
/* 002cfc6c: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cfc70: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 002cfc74: sra v1,v1,0x17 */ c->r[3]=sar((uint32_t)c->r[3],23u);
/* 002cfc78: slti v0,v1,0x3d */ c->r[2]=less(c->r[3],sx(UINT32_C(0x0000003d)));
/* 002cfc7c: beq v0,zero,0x002cfcbc */ {int taken=(c->r[2]==c->r[0]);/* delay 002cfc80 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_002cfcbc;}}
/* 002cfc84: bgez a2,0x002cfc98 */ {int taken=(!neg(c->r[6]));/* delay 002cfc88 */ c->r[2]=less(c->r[3],sx(UINT32_C(0xffffffc4)));if(taken){goto L_002cfc98;}}
/* 002cfc8c: clear f2 */ c->f[2]=0;
/* 002cfc90: bne v0,zero,0x002cfcbc */ {int taken=(c->r[2]!=c->r[0]);/* delay 002cfc94 */ c->r[2]=sx(UINT32_C(0x00000001));if(taken){goto L_002cfcbc;}}
L_002cfc98:;
/* 002cfc98: nop  */ (void)0;
/* 002cfc9c: nop  */ (void)0;
/* 002cfca0: div.S f12,f1,f13 */ c->f[12]=EE_FPU_DIV_S(c->f[1],c->f[13]);
/* 002cfca4: jal 0x002d11c0 */ c->r[31]=UINT64_C(0x002cfcac);/* delay 002cfca8 */ (void)0;nocturneLibmInverseSetStackPointer((uint32_t)c->r[29]);c->f[0]=bits(ps2AbsFloat(real(c->f[12])));nocturneLibmInverseSetStackPointer((uint32_t)c->r[29]);
/* 002cfcac: jal 0x002d0f30 */ c->r[31]=UINT64_C(0x002cfcb4);/* delay 002cfcb0 */ c->f[12]=c->f[0];body_002d0f30(c);
/* 002cfcb4: mov.S f2,f0 */ c->f[2]=c->f[0];
/* 002cfcb8: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
L_002cfcbc:;
/* 002cfcbc: beq s0,v0,0x002cfcf0 */ {int taken=(c->r[16]==c->r[2]);/* delay 002cfcc0 */ c->r[2]=less(c->r[16],sx(UINT32_C(0x00000002)));if(taken){goto L_002cfcf0;}}
/* 002cfcc4: beql v0,zero,0x002cfce0 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002cfcc8 */ c->r[2]=sx(UINT32_C(0x00000002));goto L_002cfce0;}}
/* 002cfccc: beq s0,zero,0x002cfd58 */ {int taken=(c->r[16]==c->r[0]);/* delay 002cfcd0 */ c->f[0]=c->f[2];if(taken){goto L_002cfd58;}}
/* 002cfcd4: b 0x002cfd38 */ /* delay 002cfcd8 */ (void)0;goto L_002cfd38;
L_002cfce0:;
/* 002cfce0: beq s0,v0,0x002cfd10 */ {int taken=(c->r[16]==c->r[2]);/* delay 002cfce4 */ (void)0;if(taken){goto L_002cfd10;}}
/* 002cfce8: b 0x002cfd38 */ /* delay 002cfcec */ (void)0;goto L_002cfd38;
L_002cfcf0:;
/* 002cfcf0: swc1 f2,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),c->f[2]);
/* 002cfcf4: lui v0,0x8000 */ c->r[2]=sx(UINT32_C(0x80000000));
/* 002cfcf8: lw v1,0x0(sp) */ c->r[3]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000000)));
/* 002cfcfc: xor v1,v1,v0 */ c->r[3]=c->r[3]^c->r[2];
/* 002cfd00: mtc1 v1,f2 */ c->f[2]=(uint32_t)c->r[3];
/* 002cfd04: b 0x002cfd58 */ /* delay 002cfd08 */ c->f[0]=c->f[2];goto L_002cfd58;
L_002cfd10:;
/* 002cfd10: lui at,0x3422 */ c->r[1]=sx(UINT32_C(0x34220000));
/* 002cfd14: ori at,at,0x2168 */ c->r[1]=c->r[1]|UINT64_C(0x2168);
/* 002cfd18: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cfd1c: lui at,0x4049 */ c->r[1]=sx(UINT32_C(0x40490000));
/* 002cfd20: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cfd24: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002cfd28: sub.S f0,f2,f0 */ c->f[0]=EE_FPU_SUB_S(c->f[2],c->f[0]);
/* 002cfd2c: b 0x002cfd58 */ /* delay 002cfd30 */ c->f[0]=EE_FPU_SUB_S(c->f[1],c->f[0]);goto L_002cfd58;
L_002cfd38:;
/* 002cfd38: lui at,0x3422 */ c->r[1]=sx(UINT32_C(0x34220000));
/* 002cfd3c: ori at,at,0x2168 */ c->r[1]=c->r[1]|UINT64_C(0x2168);
/* 002cfd40: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002cfd44: lui at,0x4049 */ c->r[1]=sx(UINT32_C(0x40490000));
/* 002cfd48: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002cfd4c: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002cfd50: sub.S f0,f2,f0 */ c->f[0]=EE_FPU_SUB_S(c->f[2],c->f[0]);
/* 002cfd54: sub.S f0,f0,f1 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[1]);
L_002cfd58:;
/* 002cfd58: ld s0,0x10(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
L_002cfd5c:;
/* 002cfd5c: ld ra,0x18(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000018));
L_002cfd60:;
/* 002cfd60: jr ra */ /* delay 002cfd64 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_002d0118(LibmInverseValues *c){
/* 002d0118: mfc1 v1,f12 */ c->r[3]=sx(c->f[12]);
/* 002d011c: move a1,v1 */ c->r[5]=c->r[3];
/* 002d0120: lui v0,0x7fff */ c->r[2]=sx(UINT32_C(0x7fff0000));
/* 002d0124: lui v1,0x7f */ c->r[3]=sx(UINT32_C(0x007f0000));
/* 002d0128: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002d012c: ori v1,v1,0xffff */ c->r[3]=c->r[3]|UINT64_C(0xffff);
/* 002d0130: and v0,a1,v0 */ c->r[2]=c->r[5]&c->r[2];
/* 002d0134: sltu v0,v1,v0 */ c->r[2]=(c->r[3]<c->r[2]);
/* 002d0138: beq v0,zero,0x002d0158 */ {int taken=(c->r[2]==c->r[0]);/* delay 002d013c */ c->f[0]=c->f[12];if(taken){goto L_002d0158;}}
/* 002d0140: bgez a1,0x002d0160 */ {int taken=(!neg(c->r[5]));/* delay 002d0144 */ c->r[7]=sar((uint32_t)c->r[5],23u);if(taken){goto L_002d0160;}}
/* 002d0148: sub.S f0,f12,f12 */ c->f[0]=EE_FPU_SUB_S(c->f[12],c->f[12]);
/* 002d014c: nop  */ (void)0;
/* 002d0150: nop  */ (void)0;
/* 002d0154: div.S f0,f0,f0 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[0]);
L_002d0158:;
/* 002d0158: jr ra */ /* delay 002d015c */ (void)0;return;
L_002d0160:;
/* 002d0160: addiu a3,a3,-0x7f */ c->r[7]=sx((uint32_t)c->r[7]+UINT32_C(0xffffff81));
/* 002d0164: lui v0,0x80 */ c->r[2]=sx(UINT32_C(0x00800000));
/* 002d0168: and v1,a1,v1 */ c->r[3]=c->r[5]&c->r[3];
/* 002d016c: andi a0,a3,0x1 */ c->r[4]=c->r[7]&UINT64_C(0x1);
/* 002d0170: or a1,v1,v0 */ c->r[5]=c->r[3]|c->r[2];
/* 002d0174: move t0,zero */ c->r[8]=c->r[0];
/* 002d0178: sllv a1,a1,a0 */ c->r[5]=sx((uint32_t)c->r[5]<<(c->r[4]&31u));
/* 002d017c: lui a0,0x100 */ c->r[4]=sx(UINT32_C(0x01000000));
/* 002d0180: sra a3,a3,0x1 */ c->r[7]=sar((uint32_t)c->r[7],1u);
/* 002d0184: sll a1,a1,0x1 */ c->r[5]=sx((uint32_t)c->r[5]<<1u);
/* 002d0188: move a2,zero */ c->r[6]=c->r[0];
/* 002d018c: nop  */ (void)0;
L_002d0190:;
/* 002d0190: addu v1,t0,a0 */ c->r[3]=sx((uint32_t)c->r[8]+(uint32_t)c->r[4]);
/* 002d0194: slt v0,a1,v1 */ c->r[2]=less(c->r[5],c->r[3]);
/* 002d0198: bnel v0,zero,0x002d01b0 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002d019c */ c->r[4]=sx((uint32_t)c->r[4]>>1u);goto L_002d01b0;}}
/* 002d01a0: subu a1,a1,v1 */ c->r[5]=sx((uint32_t)c->r[5]-(uint32_t)c->r[3]);
/* 002d01a4: addu t0,v1,a0 */ c->r[8]=sx((uint32_t)c->r[3]+(uint32_t)c->r[4]);
/* 002d01a8: addu a2,a2,a0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[4]);
/* 002d01ac: srl a0,a0,0x1 */ c->r[4]=sx((uint32_t)c->r[4]>>1u);
L_002d01b0:;
/* 002d01b0: bne a0,zero,0x002d0190 */ {int taken=(c->r[4]!=c->r[0]);/* delay 002d01b4 */ c->r[5]=sx((uint32_t)c->r[5]<<1u);if(taken){goto L_002d0190;}}
/* 002d01b8: beq a1,zero,0x002d01c4 */ {int taken=(c->r[5]==c->r[0]);/* delay 002d01bc */ c->r[2]=c->r[6]&UINT64_C(0x1);if(taken){goto L_002d01c4;}}
/* 002d01c0: addu a2,a2,v0 */ c->r[6]=sx((uint32_t)c->r[6]+(uint32_t)c->r[2]);
L_002d01c4:;
/* 002d01c4: sra v0,a2,0x1 */ c->r[2]=sar((uint32_t)c->r[6],1u);
/* 002d01c8: sll v1,a3,0x17 */ c->r[3]=sx((uint32_t)c->r[7]<<23u);
/* 002d01cc: lui a1,0x3f00 */ c->r[5]=sx(UINT32_C(0x3f000000));
/* 002d01d0: addu a1,a1,v0 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[2]);
/* 002d01d4: addu a1,a1,v1 */ c->r[5]=sx((uint32_t)c->r[5]+(uint32_t)c->r[3]);
/* 002d01d8: mtc1 a1,f0 */ c->f[0]=(uint32_t)c->r[5];
/* 002d01dc: jr ra */ /* delay 002d01e0 */ (void)0;return;
}

static void body_002d0ca8(LibmInverseValues *c){
/* 002d0ca8: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002d0cac: mov.S f16,f12 */ c->f[16]=c->f[12];
/* 002d0cb0: mfc1 a2,f16 */ c->r[6]=sx(c->f[16]);
/* 002d0cb4: lui v1,0x7fff */ c->r[3]=sx(UINT32_C(0x7fff0000));
/* 002d0cb8: lui v0,0x317f */ c->r[2]=sx(UINT32_C(0x317f0000));
/* 002d0cbc: ori v1,v1,0xffff */ c->r[3]=c->r[3]|UINT64_C(0xffff);
/* 002d0cc0: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002d0cc4: and a1,a2,v1 */ c->r[5]=c->r[6]&c->r[3];
/* 002d0cc8: slt v0,v0,a1 */ c->r[2]=less(c->r[2],c->r[5]);
/* 002d0ccc: bne v0,zero,0x002d0d48 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002d0cd0 */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);if(taken){goto L_002d0d48;}}
/* 002d0cd4: cvt.w.S f0,f16 */ c->f[0]=EE_FPU_CVT_W_S(c->f[16]);
/* 002d0cd8: mfc1 v0,f0 */ c->r[2]=sx(c->f[0]);
/* 002d0cdc: bne v0,zero,0x002d0d4c */ {int taken=(c->r[2]!=c->r[0]);/* delay 002d0ce0 */ c->r[2]=sx(UINT32_C(0x3f2c0000));if(taken){goto L_002d0d4c;}}
/* 002d0ce4: addiu v0,a0,0x1 */ c->r[2]=sx((uint32_t)c->r[4]+UINT32_C(0x00000001));
/* 002d0ce8: or v0,a1,v0 */ c->r[2]=c->r[5]|c->r[2];
/* 002d0cec: bnel v0,zero,0x002d0d18 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002d0cf0 */ c->r[2]=sx(UINT32_C(0x00000001));goto L_002d0d18;}}
/* 002d0cf4: jal 0x002d11c0 */ c->r[31]=UINT64_C(0x002d0cfc);/* delay 002d0cf8 */ (void)0;nocturneLibmInverseSetStackPointer((uint32_t)c->r[29]);c->f[0]=bits(ps2AbsFloat(real(c->f[12])));nocturneLibmInverseSetStackPointer((uint32_t)c->r[29]);
/* 002d0cfc: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002d0d00: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002d0d04: nop  */ (void)0;
/* 002d0d08: nop  */ (void)0;
/* 002d0d0c: div.S f0,f1,f0 */ c->f[0]=EE_FPU_DIV_S(c->f[1],c->f[0]);
/* 002d0d10: b 0x002d0f24 */ /* delay 002d0d14 */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));goto L_002d0f24;
L_002d0d18:;
/* 002d0d18: beq a0,v0,0x002d0d40 */ {int taken=(c->r[4]==c->r[2]);/* delay 002d0d1c */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));if(taken){goto L_002d0d40;}}
/* 002d0d20: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 002d0d24: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002d0d28: nop  */ (void)0;
/* 002d0d2c: nop  */ (void)0;
/* 002d0d30: div.S f0,f0,f16 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[16]);
/* 002d0d34: b 0x002d0f24 */ /* delay 002d0d38 */ (void)0;goto L_002d0f24;
L_002d0d40:;
/* 002d0d40: b 0x002d0f20 */ /* delay 002d0d44 */ c->f[0]=c->f[16];goto L_002d0f20;
L_002d0d48:;
/* 002d0d48: lui v0,0x3f2c */ c->r[2]=sx(UINT32_C(0x3f2c0000));
L_002d0d4c:;
/* 002d0d4c: ori v0,v0,0xa13f */ c->r[2]=c->r[2]|UINT64_C(0xa13f);
/* 002d0d50: slt v0,v0,a1 */ c->r[2]=less(c->r[2],c->r[5]);
/* 002d0d54: beql v0,zero,0x002d0d98 */ {int taken=(c->r[2]==c->r[0]);if(taken){/* delay 002d0d58 */ c->f[15]=EE_FPU_MUL_S(c->f[16],c->f[16]);goto L_002d0d98;}}
/* 002d0d5c: bgez a2,0x002d0d6c */ {int taken=(!neg(c->r[6]));/* delay 002d0d60 */ (void)0;if(taken){goto L_002d0d6c;}}
/* 002d0d64: neg.S f16,f16 */ c->f[16]=c->f[16]^UINT32_C(0x80000000);
/* 002d0d68: neg.S f13,f13 */ c->f[13]=c->f[13]^UINT32_C(0x80000000);
L_002d0d6c:;
/* 002d0d6c: lui at,0x3f49 */ c->r[1]=sx(UINT32_C(0x3f490000));
/* 002d0d70: ori at,at,0xfda */ c->r[1]=c->r[1]|UINT64_C(0xfda);
/* 002d0d74: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002d0d78: lui at,0x3322 */ c->r[1]=sx(UINT32_C(0x33220000));
/* 002d0d7c: ori at,at,0x2167 */ c->r[1]=c->r[1]|UINT64_C(0x2167);
/* 002d0d80: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002d0d84: sub.S f15,f0,f16 */ c->f[15]=EE_FPU_SUB_S(c->f[0],c->f[16]);
/* 002d0d88: sub.S f14,f1,f13 */ c->f[14]=EE_FPU_SUB_S(c->f[1],c->f[13]);
/* 002d0d8c: clear f13 */ c->f[13]=0;
/* 002d0d90: add.S f16,f15,f14 */ c->f[16]=EE_FPU_ADD_S(c->f[15],c->f[14]);
/* 002d0d94: mul.S f15,f16,f16 */ c->f[15]=EE_FPU_MUL_S(c->f[16],c->f[16]);
L_002d0d98:;
/* 002d0d98: lui v0,0x55 */ c->r[2]=sx(UINT32_C(0x00550000));
/* 002d0d9c: addiu v0,v0,-0x4c40 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffb3c0));
/* 002d0da0: lui v1,0x3f2c */ c->r[3]=sx(UINT32_C(0x3f2c0000));
/* 002d0da4: lwc1 f8,0x30(v0) */ c->f[8]=word((uint32_t)c->r[2]+UINT32_C(0x00000030));
/* 002d0da8: ori v1,v1,0xa13f */ c->r[3]=c->r[3]|UINT64_C(0xa13f);
/* 002d0dac: lwc1 f9,0x2c(v0) */ c->f[9]=word((uint32_t)c->r[2]+UINT32_C(0x0000002c));
/* 002d0db0: slt v1,v1,a1 */ c->r[3]=less(c->r[3],c->r[5]);
/* 002d0db4: mul.S f14,f15,f15 */ c->f[14]=EE_FPU_MUL_S(c->f[15],c->f[15]);
/* 002d0db8: lwc1 f0,0x28(v0) */ c->f[0]=word((uint32_t)c->r[2]+UINT32_C(0x00000028));
/* 002d0dbc: lwc1 f1,0x24(v0) */ c->f[1]=word((uint32_t)c->r[2]+UINT32_C(0x00000024));
/* 002d0dc0: mul.S f12,f15,f16 */ c->f[12]=EE_FPU_MUL_S(c->f[15],c->f[16]);
/* 002d0dc4: lwc1 f2,0x20(v0) */ c->f[2]=word((uint32_t)c->r[2]+UINT32_C(0x00000020));
/* 002d0dc8: lwc1 f3,0x1c(v0) */ c->f[3]=word((uint32_t)c->r[2]+UINT32_C(0x0000001c));
/* 002d0dcc: mul.S f8,f14,f8 */ c->f[8]=EE_FPU_MUL_S(c->f[14],c->f[8]);
/* 002d0dd0: lwc1 f5,0x18(v0) */ c->f[5]=word((uint32_t)c->r[2]+UINT32_C(0x00000018));
/* 002d0dd4: mul.S f9,f14,f9 */ c->f[9]=EE_FPU_MUL_S(c->f[14],c->f[9]);
/* 002d0dd8: lwc1 f4,0x14(v0) */ c->f[4]=word((uint32_t)c->r[2]+UINT32_C(0x00000014));
/* 002d0ddc: lwc1 f6,0x10(v0) */ c->f[6]=word((uint32_t)c->r[2]+UINT32_C(0x00000010));
/* 002d0de0: lwc1 f7,0xc(v0) */ c->f[7]=word((uint32_t)c->r[2]+UINT32_C(0x0000000c));
/* 002d0de4: add.S f0,f0,f8 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[8]);
/* 002d0de8: lwc1 f8,0x0(v0) */ c->f[8]=word((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 002d0dec: add.S f1,f1,f9 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[9]);
/* 002d0df0: lwc1 f10,0x8(v0) */ c->f[10]=word((uint32_t)c->r[2]+UINT32_C(0x00000008));
/* 002d0df4: lwc1 f11,0x4(v0) */ c->f[11]=word((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 002d0df8: mul.S f8,f8,f12 */ c->f[8]=EE_FPU_MUL_S(c->f[8],c->f[12]);
/* 002d0dfc: mul.S f0,f14,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[14],c->f[0]);
/* 002d0e00: mul.S f1,f14,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[14],c->f[1]);
/* 002d0e04: add.S f2,f2,f0 */ c->f[2]=EE_FPU_ADD_S(c->f[2],c->f[0]);
/* 002d0e08: add.S f3,f3,f1 */ c->f[3]=EE_FPU_ADD_S(c->f[3],c->f[1]);
/* 002d0e0c: mul.S f2,f14,f2 */ c->f[2]=EE_FPU_MUL_S(c->f[14],c->f[2]);
/* 002d0e10: mul.S f3,f14,f3 */ c->f[3]=EE_FPU_MUL_S(c->f[14],c->f[3]);
/* 002d0e14: add.S f5,f5,f2 */ c->f[5]=EE_FPU_ADD_S(c->f[5],c->f[2]);
/* 002d0e18: add.S f4,f4,f3 */ c->f[4]=EE_FPU_ADD_S(c->f[4],c->f[3]);
/* 002d0e1c: mul.S f5,f14,f5 */ c->f[5]=EE_FPU_MUL_S(c->f[14],c->f[5]);
/* 002d0e20: mul.S f4,f14,f4 */ c->f[4]=EE_FPU_MUL_S(c->f[14],c->f[4]);
/* 002d0e24: add.S f6,f6,f5 */ c->f[6]=EE_FPU_ADD_S(c->f[6],c->f[5]);
/* 002d0e28: add.S f7,f7,f4 */ c->f[7]=EE_FPU_ADD_S(c->f[7],c->f[4]);
/* 002d0e2c: mul.S f6,f14,f6 */ c->f[6]=EE_FPU_MUL_S(c->f[14],c->f[6]);
/* 002d0e30: mul.S f7,f14,f7 */ c->f[7]=EE_FPU_MUL_S(c->f[14],c->f[7]);
/* 002d0e34: add.S f10,f10,f6 */ c->f[10]=EE_FPU_ADD_S(c->f[10],c->f[6]);
/* 002d0e38: add.S f3,f11,f7 */ c->f[3]=EE_FPU_ADD_S(c->f[11],c->f[7]);
/* 002d0e3c: mul.S f5,f15,f10 */ c->f[5]=EE_FPU_MUL_S(c->f[15],c->f[10]);
/* 002d0e40: add.S f0,f3,f5 */ c->f[0]=EE_FPU_ADD_S(c->f[3],c->f[5]);
/* 002d0e44: mul.S f0,f12,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[12],c->f[0]);
/* 002d0e48: add.S f0,f0,f13 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[13]);
/* 002d0e4c: mul.S f0,f15,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[15],c->f[0]);
/* 002d0e50: add.S f3,f13,f0 */ c->f[3]=EE_FPU_ADD_S(c->f[13],c->f[0]);
/* 002d0e54: add.S f3,f3,f8 */ c->f[3]=EE_FPU_ADD_S(c->f[3],c->f[8]);
/* 002d0e58: beq v1,zero,0x002d0eb0 */ {int taken=(c->r[3]==c->r[0]);/* delay 002d0e5c */ c->f[14]=EE_FPU_ADD_S(c->f[16],c->f[3]);if(taken){goto L_002d0eb0;}}
/* 002d0e60: mtc1 a0,f5 */ c->f[5]=(uint32_t)c->r[4];
/* 002d0e64: cvt.s.W f5,f5 */ c->f[5]=EE_FPU_CVT_S_W(c->f[5]);
/* 002d0e68: sra v1,a2,0x1e */ c->r[3]=sar((uint32_t)c->r[6],30u);
/* 002d0e6c: mul.S f0,f14,f14 */ c->f[0]=EE_FPU_MUL_S(c->f[14],c->f[14]);
/* 002d0e70: andi v1,v1,0x2 */ c->r[3]=c->r[3]&UINT64_C(0x2);
/* 002d0e74: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 002d0e78: subu v0,v0,v1 */ c->r[2]=sx((uint32_t)c->r[2]-(uint32_t)c->r[3]);
/* 002d0e7c: add.S f1,f14,f5 */ c->f[1]=EE_FPU_ADD_S(c->f[14],c->f[5]);
/* 002d0e80: mtc1 v0,f2 */ c->f[2]=(uint32_t)c->r[2];
/* 002d0e84: cvt.s.W f2,f2 */ c->f[2]=EE_FPU_CVT_S_W(c->f[2]);
/* 002d0e88: nop  */ (void)0;
/* 002d0e8c: nop  */ (void)0;
/* 002d0e90: div.S f0,f0,f1 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[1]);
/* 002d0e94: sub.S f0,f0,f3 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[3]);
/* 002d0e98: sub.S f0,f16,f0 */ c->f[0]=EE_FPU_SUB_S(c->f[16],c->f[0]);
/* 002d0e9c: add.S f0,f0,f0 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[0]);
/* 002d0ea0: sub.S f0,f5,f0 */ c->f[0]=EE_FPU_SUB_S(c->f[5],c->f[0]);
/* 002d0ea4: b 0x002d0f20 */ /* delay 002d0ea8 */ c->f[0]=EE_FPU_MUL_S(c->f[2],c->f[0]);goto L_002d0f20;
L_002d0eb0:;
/* 002d0eb0: li v0,0x1 */ c->r[2]=sx(UINT32_C(0x00000001));
/* 002d0eb4: beq a0,v0,0x002d0f20 */ {int taken=(c->r[4]==c->r[2]);/* delay 002d0eb8 */ c->f[0]=c->f[14];if(taken){goto L_002d0f20;}}
/* 002d0ebc: mfc1 v1,f14 */ c->r[3]=sx(c->f[14]);
/* 002d0ec0: move v0,v1 */ c->r[2]=c->r[3];
/* 002d0ec4: li v1,-0x1000 */ c->r[3]=sx(UINT32_C(0xfffff000));
/* 002d0ec8: and v0,v0,v1 */ c->r[2]=c->r[2]&c->r[3];
/* 002d0ecc: mtc1 v0,f15 */ c->f[15]=(uint32_t)c->r[2];
/* 002d0ed0: sub.S f1,f15,f16 */ c->f[1]=EE_FPU_SUB_S(c->f[15],c->f[16]);
/* 002d0ed4: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 002d0ed8: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002d0edc: nop  */ (void)0;
/* 002d0ee0: nop  */ (void)0;
/* 002d0ee4: div.S f0,f0,f14 */ c->f[0]=EE_FPU_DIV_S(c->f[0],c->f[14]);
/* 002d0ee8: sub.S f5,f3,f1 */ c->f[5]=EE_FPU_SUB_S(c->f[3],c->f[1]);
/* 002d0eec: mov.S f1,f0 */ c->f[1]=c->f[0];
/* 002d0ef0: swc1 f1,0x0(sp) */ sw((uint32_t)c->r[29]+UINT32_C(0x00000000),c->f[1]);
/* 002d0ef4: lw v0,0x0(sp) */ c->r[2]=sx(word((uint32_t)c->r[29]+UINT32_C(0x00000000)));
/* 002d0ef8: and v0,v0,v1 */ c->r[2]=c->r[2]&c->r[3];
/* 002d0efc: mtc1 v0,f3 */ c->f[3]=(uint32_t)c->r[2];
/* 002d0f00: mul.S f4,f3,f15 */ c->f[4]=EE_FPU_MUL_S(c->f[3],c->f[15]);
/* 002d0f04: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002d0f08: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 002d0f0c: mul.S f1,f3,f5 */ c->f[1]=EE_FPU_MUL_S(c->f[3],c->f[5]);
/* 002d0f10: add.S f12,f4,f2 */ c->f[12]=EE_FPU_ADD_S(c->f[4],c->f[2]);
/* 002d0f14: add.S f1,f12,f1 */ c->f[1]=EE_FPU_ADD_S(c->f[12],c->f[1]);
/* 002d0f18: mul.S f0,f0,f1 */ c->f[0]=EE_FPU_MUL_S(c->f[0],c->f[1]);
/* 002d0f1c: add.S f0,f3,f0 */ c->f[0]=EE_FPU_ADD_S(c->f[3],c->f[0]);
L_002d0f20:;
/* 002d0f20: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
L_002d0f24:;
/* 002d0f24: jr ra */ /* delay 002d0f28 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}

static void body_002d0f30(LibmInverseValues *c){
/* 002d0f30: addiu sp,sp,-0x20 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0xffffffe0));
/* 002d0f34: mov.S f13,f12 */ c->f[13]=c->f[12];
/* 002d0f38: sd s0,0x0(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000000),c->r[16]);
/* 002d0f3c: sd s1,0x8(sp) */ sd((uint32_t)c->r[29]+UINT32_C(0x00000008),c->r[17]);
/* 002d0f40: mfc1 s1,f13 */ c->r[17]=sx(c->f[13]);
/* 002d0f44: lui v1,0x7fff */ c->r[3]=sx(UINT32_C(0x7fff0000));
/* 002d0f48: lui v0,0x507f */ c->r[2]=sx(UINT32_C(0x507f0000));
/* 002d0f4c: ori v1,v1,0xffff */ c->r[3]=c->r[3]|UINT64_C(0xffff);
/* 002d0f50: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002d0f54: and s0,s1,v1 */ c->r[16]=c->r[17]&c->r[3];
/* 002d0f58: slt v0,v0,s0 */ c->r[2]=less(c->r[2],c->r[16]);
/* 002d0f5c: beq v0,zero,0x002d0f98 */ {int taken=(c->r[2]==c->r[0]);/* delay 002d0f60 */ sd((uint32_t)c->r[29]+UINT32_C(0x00000010),c->r[31]);if(taken){goto L_002d0f98;}}
/* 002d0f64: blez s1,0x002d0f80 */ {int taken=((neg(c->r[17])||!c->r[17]));/* delay 002d0f68 */ c->r[2]=sx(UINT32_C(0x00550000));if(taken){goto L_002d0f80;}}
/* 002d0f6c: lui v1,0x55 */ c->r[3]=sx(UINT32_C(0x00550000));
/* 002d0f70: lwc1 f1,-0x4bfc(v0) */ c->f[1]=word((uint32_t)c->r[2]+UINT32_C(0xffffb404));
/* 002d0f74: lwc1 f0,-0x4bec(v1) */ c->f[0]=word((uint32_t)c->r[3]+UINT32_C(0xffffb414));
/* 002d0f78: b 0x002d11a8 */ /* delay 002d0f7c */ c->f[0]=EE_FPU_ADD_S(c->f[1],c->f[0]);goto L_002d11a8;
L_002d0f80:;
/* 002d0f80: lui v1,0x55 */ c->r[3]=sx(UINT32_C(0x00550000));
/* 002d0f84: lwc1 f0,-0x4bfc(v0) */ c->f[0]=word((uint32_t)c->r[2]+UINT32_C(0xffffb404));
/* 002d0f88: lwc1 f1,-0x4bec(v1) */ c->f[1]=word((uint32_t)c->r[3]+UINT32_C(0xffffb414));
/* 002d0f8c: neg.S f0,f0 */ c->f[0]=c->f[0]^UINT32_C(0x80000000);
/* 002d0f90: b 0x002d11a8 */ /* delay 002d0f94 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[1]);goto L_002d11a8;
L_002d0f98:;
/* 002d0f98: lui v0,0x3edf */ c->r[2]=sx(UINT32_C(0x3edf0000));
/* 002d0f9c: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002d0fa0: slt v0,v0,s0 */ c->r[2]=less(c->r[2],c->r[16]);
/* 002d0fa4: bne v0,zero,0x002d0fe8 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002d0fa8 */ c->r[2]=sx(UINT32_C(0x30ff0000));if(taken){goto L_002d0fe8;}}
/* 002d0fac: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002d0fb0: slt v0,v0,s0 */ c->r[2]=less(c->r[2],c->r[16]);
/* 002d0fb4: bne v0,zero,0x002d10cc */ {int taken=(c->r[2]!=c->r[0]);/* delay 002d0fb8 */ c->r[3]=sx(UINT32_C(0xffffffff));if(taken){goto L_002d10cc;}}
/* 002d0fbc: lui at,0x7149 */ c->r[1]=sx(UINT32_C(0x71490000));
/* 002d0fc0: ori at,at,0xf2c9 */ c->r[1]=c->r[1]|UINT64_C(0xf2c9);
/* 002d0fc4: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002d0fc8: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002d0fcc: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 002d0fd0: add.S f1,f13,f1 */ c->f[1]=EE_FPU_ADD_S(c->f[13],c->f[1]);
/* 002d0fd4: c.lt.S f2,f1 */ c->condition=EE_FPU_COMPARE_S(c->f[2],c->f[1],1);
/* 002d0fd8: bc1t 0x002d11a8 */ {int taken=(c->condition!=0);/* delay 002d0fdc */ c->f[0]=c->f[13];if(taken){goto L_002d11a8;}}
/* 002d0fe0: b 0x002d10d0 */ /* delay 002d0fe4 */ c->f[12]=EE_FPU_MUL_S(c->f[13],c->f[13]);goto L_002d10d0;
L_002d0fe8:;
/* 002d0fe8: jal 0x002d11c0 */ c->r[31]=UINT64_C(0x002d0ff0);/* delay 002d0fec */ (void)0;nocturneLibmInverseSetStackPointer((uint32_t)c->r[29]);c->f[0]=bits(ps2AbsFloat(real(c->f[12])));nocturneLibmInverseSetStackPointer((uint32_t)c->r[29]);
/* 002d0ff0: lui v0,0x3f97 */ c->r[2]=sx(UINT32_C(0x3f970000));
/* 002d0ff4: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002d0ff8: slt v0,v0,s0 */ c->r[2]=less(c->r[2],c->r[16]);
/* 002d0ffc: bne v0,zero,0x002d1070 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002d1000 */ c->f[13]=c->f[0];if(taken){goto L_002d1070;}}
/* 002d1004: lui v0,0x3f2f */ c->r[2]=sx(UINT32_C(0x3f2f0000));
/* 002d1008: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002d100c: slt v0,v0,s0 */ c->r[2]=less(c->r[2],c->r[16]);
/* 002d1010: bne v0,zero,0x002d1048 */ {int taken=(c->r[2]!=c->r[0]);/* delay 002d1014 */ (void)0;if(taken){goto L_002d1048;}}
/* 002d1018: add.S f0,f13,f13 */ c->f[0]=EE_FPU_ADD_S(c->f[13],c->f[13]);
/* 002d101c: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002d1020: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 002d1024: lui at,0x4000 */ c->r[1]=sx(UINT32_C(0x40000000));
/* 002d1028: mtc1 at,f1 */ c->f[1]=(uint32_t)c->r[1];
/* 002d102c: add.S f1,f13,f1 */ c->f[1]=EE_FPU_ADD_S(c->f[13],c->f[1]);
/* 002d1030: sub.S f0,f0,f2 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[2]);
/* 002d1034: nop  */ (void)0;
/* 002d1038: nop  */ (void)0;
/* 002d103c: div.S f13,f0,f1 */ c->f[13]=EE_FPU_DIV_S(c->f[0],c->f[1]);
/* 002d1040: b 0x002d10cc */ /* delay 002d1044 */ c->r[3]=c->r[0];goto L_002d10cc;
L_002d1048:;
/* 002d1048: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002d104c: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002d1050: add.S f1,f13,f0 */ c->f[1]=EE_FPU_ADD_S(c->f[13],c->f[0]);
/* 002d1054: sub.S f0,f13,f0 */ c->f[0]=EE_FPU_SUB_S(c->f[13],c->f[0]);
/* 002d1058: nop  */ (void)0;
/* 002d105c: nop  */ (void)0;
/* 002d1060: div.S f13,f0,f1 */ c->f[13]=EE_FPU_DIV_S(c->f[0],c->f[1]);
/* 002d1064: b 0x002d10cc */ /* delay 002d1068 */ c->r[3]=sx(UINT32_C(0x00000001));goto L_002d10cc;
L_002d1070:;
/* 002d1070: lui v0,0x401b */ c->r[2]=sx(UINT32_C(0x401b0000));
/* 002d1074: ori v0,v0,0xffff */ c->r[2]=c->r[2]|UINT64_C(0xffff);
/* 002d1078: slt v0,v0,s0 */ c->r[2]=less(c->r[2],c->r[16]);
/* 002d107c: bnel v0,zero,0x002d10b8 */ {int taken=(c->r[2]!=c->r[0]);if(taken){/* delay 002d1080 */ c->r[3]=sx(UINT32_C(0x00000003));goto L_002d10b8;}}
/* 002d1084: lui at,0x3fc0 */ c->r[1]=sx(UINT32_C(0x3fc00000));
/* 002d1088: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002d108c: lui at,0x3f80 */ c->r[1]=sx(UINT32_C(0x3f800000));
/* 002d1090: mtc1 at,f2 */ c->f[2]=(uint32_t)c->r[1];
/* 002d1094: mul.S f1,f13,f0 */ c->f[1]=EE_FPU_MUL_S(c->f[13],c->f[0]);
/* 002d1098: sub.S f0,f13,f0 */ c->f[0]=EE_FPU_SUB_S(c->f[13],c->f[0]);
/* 002d109c: add.S f1,f1,f2 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[2]);
/* 002d10a0: nop  */ (void)0;
/* 002d10a4: nop  */ (void)0;
/* 002d10a8: div.S f13,f0,f1 */ c->f[13]=EE_FPU_DIV_S(c->f[0],c->f[1]);
/* 002d10ac: b 0x002d10cc */ /* delay 002d10b0 */ c->r[3]=sx(UINT32_C(0x00000002));goto L_002d10cc;
L_002d10b8:;
/* 002d10b8: lui at,0xbf80 */ c->r[1]=sx(UINT32_C(0xbf800000));
/* 002d10bc: mtc1 at,f0 */ c->f[0]=(uint32_t)c->r[1];
/* 002d10c0: nop  */ (void)0;
/* 002d10c4: nop  */ (void)0;
/* 002d10c8: div.S f13,f0,f13 */ c->f[13]=EE_FPU_DIV_S(c->f[0],c->f[13]);
L_002d10cc:;
/* 002d10cc: mul.S f12,f13,f13 */ c->f[12]=EE_FPU_MUL_S(c->f[13],c->f[13]);
L_002d10d0:;
/* 002d10d0: lui v0,0x55 */ c->r[2]=sx(UINT32_C(0x00550000));
/* 002d10d4: addiu v0,v0,-0x4be8 */ c->r[2]=sx((uint32_t)c->r[2]+UINT32_C(0xffffb418));
/* 002d10d8: lwc1 f7,0x28(v0) */ c->f[7]=word((uint32_t)c->r[2]+UINT32_C(0x00000028));
/* 002d10dc: lwc1 f4,0x20(v0) */ c->f[4]=word((uint32_t)c->r[2]+UINT32_C(0x00000020));
/* 002d10e0: mul.S f0,f12,f12 */ c->f[0]=EE_FPU_MUL_S(c->f[12],c->f[12]);
/* 002d10e4: lwc1 f5,0x24(v0) */ c->f[5]=word((uint32_t)c->r[2]+UINT32_C(0x00000024));
/* 002d10e8: lwc1 f6,0x18(v0) */ c->f[6]=word((uint32_t)c->r[2]+UINT32_C(0x00000018));
/* 002d10ec: lwc1 f1,0x1c(v0) */ c->f[1]=word((uint32_t)c->r[2]+UINT32_C(0x0000001c));
/* 002d10f0: lwc1 f8,0x10(v0) */ c->f[8]=word((uint32_t)c->r[2]+UINT32_C(0x00000010));
/* 002d10f4: mul.S f7,f0,f7 */ c->f[7]=EE_FPU_MUL_S(c->f[0],c->f[7]);
/* 002d10f8: lwc1 f2,0x14(v0) */ c->f[2]=word((uint32_t)c->r[2]+UINT32_C(0x00000014));
/* 002d10fc: mul.S f5,f0,f5 */ c->f[5]=EE_FPU_MUL_S(c->f[0],c->f[5]);
/* 002d1100: lwc1 f9,0x8(v0) */ c->f[9]=word((uint32_t)c->r[2]+UINT32_C(0x00000008));
/* 002d1104: lwc1 f3,0xc(v0) */ c->f[3]=word((uint32_t)c->r[2]+UINT32_C(0x0000000c));
/* 002d1108: lwc1 f10,0x4(v0) */ c->f[10]=word((uint32_t)c->r[2]+UINT32_C(0x00000004));
/* 002d110c: add.S f4,f4,f7 */ c->f[4]=EE_FPU_ADD_S(c->f[4],c->f[7]);
/* 002d1110: lwc1 f11,0x0(v0) */ c->f[11]=word((uint32_t)c->r[2]+UINT32_C(0x00000000));
/* 002d1114: add.S f1,f1,f5 */ c->f[1]=EE_FPU_ADD_S(c->f[1],c->f[5]);
/* 002d1118: mul.S f4,f0,f4 */ c->f[4]=EE_FPU_MUL_S(c->f[0],c->f[4]);
/* 002d111c: mul.S f1,f0,f1 */ c->f[1]=EE_FPU_MUL_S(c->f[0],c->f[1]);
/* 002d1120: add.S f6,f6,f4 */ c->f[6]=EE_FPU_ADD_S(c->f[6],c->f[4]);
/* 002d1124: add.S f2,f2,f1 */ c->f[2]=EE_FPU_ADD_S(c->f[2],c->f[1]);
/* 002d1128: mul.S f6,f0,f6 */ c->f[6]=EE_FPU_MUL_S(c->f[0],c->f[6]);
/* 002d112c: mul.S f2,f0,f2 */ c->f[2]=EE_FPU_MUL_S(c->f[0],c->f[2]);
/* 002d1130: add.S f8,f8,f6 */ c->f[8]=EE_FPU_ADD_S(c->f[8],c->f[6]);
/* 002d1134: add.S f3,f3,f2 */ c->f[3]=EE_FPU_ADD_S(c->f[3],c->f[2]);
/* 002d1138: mul.S f8,f0,f8 */ c->f[8]=EE_FPU_MUL_S(c->f[0],c->f[8]);
/* 002d113c: mul.S f3,f0,f3 */ c->f[3]=EE_FPU_MUL_S(c->f[0],c->f[3]);
/* 002d1140: add.S f9,f9,f8 */ c->f[9]=EE_FPU_ADD_S(c->f[9],c->f[8]);
/* 002d1144: add.S f10,f10,f3 */ c->f[10]=EE_FPU_ADD_S(c->f[10],c->f[3]);
/* 002d1148: mul.S f9,f0,f9 */ c->f[9]=EE_FPU_MUL_S(c->f[0],c->f[9]);
/* 002d114c: mul.S f1,f0,f10 */ c->f[1]=EE_FPU_MUL_S(c->f[0],c->f[10]);
/* 002d1150: add.S f11,f11,f9 */ c->f[11]=EE_FPU_ADD_S(c->f[11],c->f[9]);
/* 002d1154: bgez v1,0x002d1170 */ {int taken=(!neg(c->r[3]));/* delay 002d1158 */ c->f[0]=EE_FPU_MUL_S(c->f[12],c->f[11]);if(taken){goto L_002d1170;}}
/* 002d115c: add.S f0,f0,f1 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[1]);
/* 002d1160: mul.S f0,f13,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[13],c->f[0]);
/* 002d1164: b 0x002d11a8 */ /* delay 002d1168 */ c->f[0]=EE_FPU_SUB_S(c->f[13],c->f[0]);goto L_002d11a8;
L_002d1170:;
/* 002d1170: add.S f0,f0,f1 */ c->f[0]=EE_FPU_ADD_S(c->f[0],c->f[1]);
/* 002d1174: sll v0,v1,0x2 */ c->r[2]=sx((uint32_t)c->r[3]<<2u);
/* 002d1178: lui at,0x55 */ c->r[1]=sx(UINT32_C(0x00550000));
/* 002d117c: addu at,at,v0 */ c->r[1]=sx((uint32_t)c->r[1]+(uint32_t)c->r[2]);
/* 002d1180: lwc1 f1,-0x4bf8(at) */ c->f[1]=word((uint32_t)c->r[1]+UINT32_C(0xffffb408));
/* 002d1184: lui at,0x55 */ c->r[1]=sx(UINT32_C(0x00550000));
/* 002d1188: addu at,at,v0 */ c->r[1]=sx((uint32_t)c->r[1]+(uint32_t)c->r[2]);
/* 002d118c: lwc1 f2,-0x4c08(at) */ c->f[2]=word((uint32_t)c->r[1]+UINT32_C(0xffffb3f8));
/* 002d1190: mul.S f0,f13,f0 */ c->f[0]=EE_FPU_MUL_S(c->f[13],c->f[0]);
/* 002d1194: sub.S f0,f0,f1 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[1]);
/* 002d1198: sub.S f0,f0,f13 */ c->f[0]=EE_FPU_SUB_S(c->f[0],c->f[13]);
/* 002d119c: bgez s1,0x002d11a8 */ {int taken=(!neg(c->r[17]));/* delay 002d11a0 */ c->f[0]=EE_FPU_SUB_S(c->f[2],c->f[0]);if(taken){goto L_002d11a8;}}
/* 002d11a4: neg.S f0,f0 */ c->f[0]=c->f[0]^UINT32_C(0x80000000);
L_002d11a8:;
/* 002d11a8: ld s0,0x0(sp) */ c->r[16]=quad((uint32_t)c->r[29]+UINT32_C(0x00000000));
/* 002d11ac: ld s1,0x8(sp) */ c->r[17]=quad((uint32_t)c->r[29]+UINT32_C(0x00000008));
/* 002d11b0: ld ra,0x10(sp) */ c->r[31]=quad((uint32_t)c->r[29]+UINT32_C(0x00000010));
/* 002d11b4: jr ra */ /* delay 002d11b8 */ c->r[29]=sx((uint32_t)c->r[29]+UINT32_C(0x00000020));return;
}
static LibmInverseValues begin(void){LibmInverseValues c={0};c.r[28]=UINT64_C(0x00554170);c.r[29]=nocturneLibmInverseStackPointer();return c;}
float ps2LibmInverse_002CF6B8(float p0){LibmInverseValues c=begin();c.f[12]=bits(p0);body_002cf6b8(&c);nocturneLibmInverseSetStackPointer((uint32_t)c.r[29]);return real(c.f[0]);}
float ps2LibmInverse_002CF730(float p0){LibmInverseValues c=begin();c.f[12]=bits(p0);body_002cf730(&c);nocturneLibmInverseSetStackPointer((uint32_t)c.r[29]);return real(c.f[0]);}
float ps2LibmInverse_002CF748(float p0,float p1){LibmInverseValues c=begin();c.f[12]=bits(p0);c.f[13]=bits(p1);body_002cf748(&c);nocturneLibmInverseSetStackPointer((uint32_t)c.r[29]);return real(c.f[0]);}
float ps2LibmInverse_002CF760(float p0){LibmInverseValues c=begin();c.f[12]=bits(p0);body_002cf760(&c);nocturneLibmInverseSetStackPointer((uint32_t)c.r[29]);return real(c.f[0]);}
float ps2LibmInverse_002CFB88(float p0,float p1){LibmInverseValues c=begin();c.f[12]=bits(p0);c.f[13]=bits(p1);body_002cfb88(&c);nocturneLibmInverseSetStackPointer((uint32_t)c.r[29]);return real(c.f[0]);}
float ps2LibmInverse_002D0118(float p0){LibmInverseValues c=begin();c.f[12]=bits(p0);body_002d0118(&c);nocturneLibmInverseSetStackPointer((uint32_t)c.r[29]);return real(c.f[0]);}
float ps2LibmInverse_002D0CA8(float p0,float p1,uint64_t p2){LibmInverseValues c=begin();c.f[12]=bits(p0);c.f[13]=bits(p1);c.r[4]=p2;body_002d0ca8(&c);nocturneLibmInverseSetStackPointer((uint32_t)c.r[29]);return real(c.f[0]);}
float ps2LibmInverse_002D0F30(float p0){LibmInverseValues c=begin();c.f[12]=bits(p0);body_002d0f30(&c);nocturneLibmInverseSetStackPointer((uint32_t)c.r[29]);return real(c.f[0]);}
