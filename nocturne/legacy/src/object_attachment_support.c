/* Complete6 registered object/zero/chunk/name helper variants; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "object_attachment.h"
#include "ee_vu_rotation.h"
#include "effect_ftoi0.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveObjectAttachmentAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}

static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneObjectAttachmentCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneObjectAttachmentCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneObjectAttachmentCpuWrite(r,q);if(r==29u)nocturneObjectAttachmentSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);


static void sq(unsigned reg,uint32_t a){uint32_t q[4];nocturneObjectAttachmentCpuRead(reg,q);memcpy(at(a&~15u),q,16);}





static void requestLq(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneObjectAttachmentCpuWrite(d,q);}
static void requestPacked(unsigned kind,unsigned d,unsigned s,unsigned t){
 uint32_t a[4],c[4],q[4];nocturneObjectAttachmentCpuRead(s,a);nocturneObjectAttachmentCpuRead(t,c);
 if(kind==0){q[0]=c[0];q[1]=c[1];q[2]=a[0];q[3]=a[1];}
 else if(kind==1){q[0]=a[2];q[1]=a[3];q[2]=c[2];q[3]=c[3];}
 else if(kind==2){for(unsigned i=0;i<4;i++)q[i]=a[i]&c[i];}
 else if(kind==3){for(unsigned i=0;i<4;i++)q[i]=~(a[i]|c[i]);}
 else if(kind==5){for(unsigned i=0;i<4;i++)q[i]=a[i]^c[i];}
 else{uint8_t x[16],y[16],z[16];memcpy(x,a,16);memcpy(y,c,16);for(unsigned i=0;i<16;i++)z[i]=(uint8_t)(x[i]-y[i]);memcpy(q,z,16);}
 nocturneObjectAttachmentCpuWrite(d,q);
}













static void body_0010df08(void);
static void body_002a8ba8(void);
static void body_002bfce8(void);
static void body_002b2670(void);
static void body_002b2628(void);
static void body_002d4310(void);
static void body_0010df08(void){
uint64_t incoming=cpu(31);
/* 0010df08: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 0010df0c: li v0,-0x3 */ set(2,sx(UINT32_C(0xfffffffd)));
/* 0010df10: lw v1,0xc0(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x000000c0)));
/* 0010df14: addiu a0,a2,0x60 */ set(4,sx((uint32_t)cpu(6)+UINT32_C(0x00000060)));
/* 0010df18: ori v1,v1,0x1 */ set(3,cpu(3)|UINT32_C(0x00000001));
/* 0010df1c: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 0010df20: sw v1,0xc0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x000000c0)),(uint32_t)cpu(3));
/* 0010df24: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0010df28: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0010df2c: jr ra */ {uint64_t target=cpu(31);/* delay 0010df30 */ checkReturn(target,incoming);return;}
}
static void body_002a8ba8(void){
uint64_t incoming=cpu(31);
/* 002a8ba8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a8bac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8bb0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8bb4: jal 0x002a8af8 */ set(31,UINT64_C(0x002a8bbc));/* delay 002a8bb8 */ set(16,cpu(4));nocturneObjectAttachmentCall(UINT32_C(0x002a8af8),UINT32_C(0x002a8bb4));
/* 002a8bbc: addiu s0,s0,0xf */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x0000000f)));
/* 002a8bc0: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8bc4: sra a1,s0,0x4 */ set(5,sx((uint32_t)((int32_t)cpu(16)>>4)));
/* 002a8bc8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8bcc: move a0,v0 */ set(4,cpu(2));
/* 002a8bd0: j 0x002bfce8 */ /* delay 002a8bd4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002bfce8();return;
}
static void body_002bfce8(void){
uint64_t incoming=cpu(31);
/* 002bfce8: slti v0,a1,0x4 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 002bfcec: bne v0,zero,0x002bfd14 */ {int taken=(cpu(2)!=cpu(0));/* delay 002bfcf0 */ set(3,cpu(4));if(taken){goto L_002bfd14;}}
L_002bfcf4:;
/* 002bfcf4: addiu a1,a1,-0x4 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xfffffffc)));
/* 002bfcf8: slti v0,a1,0x4 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 002bfcfc: sq zero,0x0(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002bfd00: sq zero,0x10(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 002bfd04: sq zero,0x20(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000020)));
/* 002bfd08: sq zero,0x30(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000030)));
/* 002bfd0c: beq v0,zero,0x002bfcf4 */ {int taken=(cpu(2)==cpu(0));/* delay 002bfd10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000040)));if(taken){goto L_002bfcf4;}}
L_002bfd14:;
/* 002bfd14: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002bfd18: beq a1,v0,0x002bfd4c */ {int taken=(cpu(5)==cpu(2));/* delay 002bfd1c */ if(taken){goto L_002bfd4c;}}
/* 002bfd20: slti v0,a1,0x3 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 002bfd24: beq v0,zero,0x002bfd40 */ {int taken=(cpu(2)==cpu(0));/* delay 002bfd28 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002bfd40;}}
/* 002bfd2c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002bfd30: beq a1,v0,0x002bfd50 */ {int taken=(cpu(5)==cpu(2));/* delay 002bfd34 */ if(taken){goto L_002bfd50;}}
/* 002bfd38: jr ra */ {uint64_t target=cpu(31);/* delay 002bfd3c */ set(2,cpu(4));checkReturn(target,incoming);return;}
L_002bfd40:;
/* 002bfd40: bnel a1,v0,0x002bfd58 */ {int taken=(cpu(5)!=cpu(2));if(taken){/* delay 002bfd44 */ set(2,cpu(4));goto L_002bfd58;}}
/* 002bfd48: sq zero,0x20(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000020)));
L_002bfd4c:;
/* 002bfd4c: sq zero,0x10(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000010)));
L_002bfd50:;
/* 002bfd50: sq zero,0x0(v1) */ sq(0,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002bfd54: move v0,a0 */ set(2,cpu(4));
L_002bfd58:;
/* 002bfd58: jr ra */ {uint64_t target=cpu(31);/* delay 002bfd5c */ checkReturn(target,incoming);return;}
}
static void body_002b2670(void){
uint64_t incoming=cpu(31);
/* 002b2670: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b2674: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2678: lw a0,0x90(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000090)));
/* 002b267c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b2680: j 0x002b2628 */ /* delay 002b2684 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002b2628();return;
}
static void body_002b2628(void){
uint64_t incoming=cpu(31);
/* 002b2628: bnel a0,zero,0x002b2660 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 002b262c */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));goto L_002b2660;}}
/* 002b2630: jr ra */ {uint64_t target=cpu(31);/* delay 002b2634 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_002b2638:;
/* 002b2638: jr ra */ {uint64_t target=cpu(31);/* delay 002b263c */ set(2,cpu(4));checkReturn(target,incoming);return;}
L_002b2640:;
/* 002b2640: nop  */ 
/* 002b2644: nop  */ 
/* 002b2648: nop  */ 
/* 002b264c: beq v0,a1,0x002b2638 */ {int taken=(cpu(2)==cpu(5));/* delay 002b2650 */ if(taken){goto L_002b2638;}}
/* 002b2654: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 002b2658: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002b265c: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
L_002b2660:;
/* 002b2660: bne v0,zero,0x002b2640 */ {int taken=(cpu(2)!=cpu(0));/* delay 002b2664 */ if(taken){goto L_002b2640;}}
/* 002b2668: jr ra */ {uint64_t target=cpu(31);/* delay 002b266c */ set(2,cpu(0));checkReturn(target,incoming);return;}
}
static void body_002d4310(void){
uint64_t incoming=cpu(31);
/* 002d4310: sltiu v0,a2,0x10 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002d4314: bne v0,zero,0x002d435c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4318 */ set(2,cpu(4)|cpu(5));if(taken){goto L_002d435c;}}
/* 002d431c: andi v0,v0,0xf */ set(2,cpu(2)&UINT32_C(0x0000000f));
/* 002d4320: bne v0,zero,0x002d435c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4324 */ if(taken){goto L_002d435c;}}
L_002d4328:;
/* 002d4328: lq v1,0x0(a0) */ requestLq(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d432c: sltiu a3,a2,0x20 */ set(7,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d4330: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d4334: addiu a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
/* 002d4338: pxor t0,v0,v1 */ requestPacked(5,8,2,3);
/* 002d433c: addiu v0,a1,0x10 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d4340: pcpyud t2,t0,a3 */ requestPacked(1,10,8,7);
/* 002d4344: or t1,t2,t0 */ set(9,cpu(10)|cpu(8));
/* 002d4348: movz a1,v0,t1 */ if(cpu(9)==0){set(5,cpu(2));}
/* 002d434c: bnel t1,zero,0x002d435c */ {int taken=(cpu(9)!=cpu(0));if(taken){/* delay 002d4350 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffff0)));goto L_002d435c;}}
/* 002d4354: beq a3,zero,0x002d4328 */ {int taken=(cpu(7)==cpu(0));/* delay 002d4358 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xfffffff0)));if(taken){goto L_002d4328;}}
L_002d435c:;
/* 002d435c: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 002d4360: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d4364: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d4368: beq a2,v0,0x002d439c */ {int taken=(cpu(6)==cpu(2));/* delay 002d436c */ if(taken){goto L_002d439c;}}
/* 002d4370: lui a3,0xffff */ set(7,sx(UINT32_C(0xffff0000)));
/* 002d4374: ori a3,a3,0xffff */ set(7,cpu(7)|UINT32_C(0x0000ffff));
L_002d4378:;
/* 002d4378: lbu v1,0x0(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002d437c: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d4380: beq v1,v0,0x002d4390 */ {int taken=(cpu(3)==cpu(2));/* delay 002d4384 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));if(taken){goto L_002d4390;}}
/* 002d4388: jr ra */ {uint64_t target=cpu(31);/* delay 002d438c */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));checkReturn(target,incoming);return;}
L_002d4390:;
/* 002d4390: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d4394: bne a2,a3,0x002d4378 */ {int taken=(cpu(6)!=cpu(7));/* delay 002d4398 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_002d4378;}}
L_002d439c:;
/* 002d439c: jr ra */ {uint64_t target=cpu(31);/* delay 002d43a0 */ set(2,cpu(0));checkReturn(target,incoming);return;}
}
uint32_t nocturneObjectAttachmentSupportBody(uint32_t entry){switch(entry){
case UINT32_C(0x0010df08):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_0010df08();return 1u;case UINT32_C(0x002a8ba8):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_002a8ba8();return 1u;case UINT32_C(0x002bfce8):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_002bfce8();return 1u;case UINT32_C(0x002b2670):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_002b2670();return 1u;case UINT32_C(0x002b2628):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_002b2628();return 1u;case UINT32_C(0x002d4310):if(nocturneObjectAttachmentStackPointer()!=(uint32_t)cpu(29))abort();body_002d4310();return 1u;
default:return 0u;}}
