/* Complete registered pose/mover/array and movement-state carrier variants; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "field_movement_encounter.h"
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
static uint8_t *at(uint32_t a){return nocturneResolveFieldMovementAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneFieldMovementCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneFieldMovementCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneFieldMovementCpuWrite(r,q);if(r==29u)nocturneFieldMovementSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}
static void nativeDivide(uint32_t n,uint32_t d,int isSigned,int secondary){
 uint32_t q,r;if(secondary)abort();
 if(!d){q=isSigned&&(int32_t)n<0?1u:UINT32_MAX;r=n;}
 else if(isSigned&&n==UINT32_C(0x80000000)&&d==UINT32_MAX){q=n;r=0;}
 else if(isSigned){q=(uint32_t)((int32_t)n/(int32_t)d);r=(uint32_t)((int32_t)n%(int32_t)d);}
 else{q=n/d;r=n%d;}
 nocturneEffectHostSetHilo(sx(q),sx(r));
}



void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sq(unsigned reg,uint32_t a){uint32_t q[4];nocturneFieldMovementCpuRead(reg,q);memcpy(at(a&~15u),q,16);}
static void nativeMultiply(unsigned rd,uint32_t a,uint32_t b,int isSigned,int secondary){
 uint64_t p=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)b):(uint64_t)a*b;
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 else nocturneEffectHostSetHilo(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 if(rd)set(rd,sx((uint32_t)p));
}




static void requestLq(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneFieldMovementCpuWrite(d,q);}


static void qmf(unsigned reg,unsigned vf){
 uint32_t q[4];nocturneFieldMovementVuRead(vf,q);nocturneFieldMovementCpuWrite(reg,q);
}












static void loadVu(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneFieldMovementVuWrite(d,q);}
static void storeVu(unsigned s,uint32_t a){uint32_t q[4];nocturneFieldMovementVuRead(s,q);memcpy(at(a&~15u),q,16);}
static void constructorVu(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned broadcast,unsigned multiply){uint32_t a[4],b[4],q[4];nocturneFieldMovementVuRead(s,a);nocturneFieldMovementVuRead(t,b);nocturneFieldMovementVuRead(d,q);for(unsigned k=0;k<4;k++)if(mask&(8u>>k))q[k]=(uint32_t)(multiply?EE_ROT_VU_MUL(a[k],b[broadcast]):EE_ROT_VU_ADD(a[k],b[broadcast]));nocturneFieldMovementVuWrite(d,q);}
static void constructorMoveW(unsigned d,unsigned s){uint32_t a[4],q[4];nocturneFieldMovementVuRead(s,a);nocturneFieldMovementVuRead(d,q);q[3]=a[3];nocturneFieldMovementVuWrite(d,q);}
void nocturneFieldMovementAccRead(uint32_t[4],uint32_t[4]);
void nocturneFieldMovementAccWrite(const uint32_t[4],const uint32_t[4]);
static void constructorMac(unsigned d,unsigned s,unsigned t,unsigned broadcast,unsigned add){uint32_t a[4],b[4],q[4],ac[4],of[4];nocturneFieldMovementVuRead(s,a);nocturneFieldMovementVuRead(t,b);nocturneFieldMovementAccRead(ac,of);for(unsigned k=0;k<4;k++){uint64_t v=add?EE_ROT_VU_MAC(ac[k],a[k],b[broadcast],of[k],0):EE_ROT_VU_MUL(a[k],b[broadcast]);q[k]=(uint32_t)v;if(d==32)of[k]=(uint32_t)(v>>32)&1u;}if(d==32)nocturneFieldMovementAccWrite(q,of);else nocturneFieldMovementVuWrite(d,q);}
static void constructorPexew(unsigned d,unsigned s){uint32_t a[4],q[4];nocturneFieldMovementCpuRead(s,a);q[0]=a[2];q[1]=a[1];q[2]=a[0];q[3]=a[3];nocturneFieldMovementCpuWrite(d,q);}

static void body_0010dd38(void);
static void body_0010de28(void);
static void body_0010de50(void);
static void body_0010dea8(void);
static void body_0010ded8(void);
static void body_0010ffe0(void);
static void body_0010fc38(void);
static void body_0010fe48(void);
static void body_00112168(void);
static void body_00110238(void);
static void body_00110298(void);
static void body_00110300(void);
static void body_001122a0(void);
static void body_00112a30(void);
static void body_0010ff90(void);
static void body_0010e248(void);
static void body_0010e690(void);
static void body_0010e748(void);
static void body_0010e8e8(void);
static void body_0010f270(void);
static void body_0010ea38(void);
static void body_0010ea90(void);
static void body_0010ebe0(void);
static void body_0010ec20(void);
static void body_0010ec58(void);
static void body_0010ec78(void);
static void body_0010ebc8(void);
static void body_0010f970(void);
static void body_0010fab8(void);
static void body_0010e548(void);
static void body_0010e588(void);
static void body_0028cca8(void);
static void body_0028cb68(void);
static void body_0028c9f0(void);
static void body_0028cfb0(void);
static void body_0028cee0(void);
static void body_00244598(void);
static void body_00244a38(void);
static void body_002456d0(void);
static void body_002455b8(void);
static void body_00245478(void);
static void body_00243f40(void);
static void body_00243e28(void);
static void body_00243e50(void);
static void body_002c0258(void);
static void body_002c0228(void);
static void body_002c0b60(void);
static void body_001e9998(void);
static void body_001e99c0(void);
static void body_001e99d0(void);
static void body_001e0f50(void);
static void body_00125990(void);
static void body_001259c0(void);
static void body_001259e0(void);
static void body_001259f8(void);
static void body_001225e8(void);
static void body_00122718(void);
static void body_0010ddf0(void);
static void body_0010df38(void);
static void body_0010df50(void);
static void body_00110350(void);
static void body_00110138(void);
static void body_00109f08(void);
static void body_0010a078(void);
static void body_00104fe0(void);
static void body_00104f78(void);
static void body_0010f208(void);
static void body_001121d8(void);
static void body_0010fed0(void);
static void body_0010dd38(void){
uint64_t incoming=cpu(31);
/* 0010dd38: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010dd3c: move v0,zero */ set(2,cpu(0));
/* 0010dd40: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010dd44: move s1,a0 */ set(17,cpu(4));
/* 0010dd48: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010dd4c: beq s1,zero,0x0010dd98 */ {int taken=(cpu(17)==cpu(0));/* delay 0010dd50 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_0010dd98;}}
/* 0010dd54: lw v1,0x1c(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 0010dd58: bnel v1,zero,0x0010dd9c */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0010dd5c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0010dd9c;}}
/* 0010dd60: jal 0x002a8af8 */ set(31,UINT64_C(0x0010dd68));/* delay 0010dd64 */ set(4,sx(UINT32_C(0x000000d0)));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x0010dd60));
/* 0010dd68: move s0,v0 */ set(16,cpu(2));
/* 0010dd6c: beq s0,zero,0x0010dd98 */ {int taken=(cpu(16)==cpu(0));/* delay 0010dd70 */ set(4,cpu(16));if(taken){goto L_0010dd98;}}
/* 0010dd74: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0010dd78: jal 0x0010de28 */ set(31,UINT64_C(0x0010dd80));/* delay 0010dd7c */ sw(ea(16,(int32_t)UINT32_C(0x000000c0)),(uint32_t)cpu(2));body_0010de28();
/* 0010dd80: addiu v0,s0,0xb0 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x000000b0)));
/* 0010dd84: sqc2 vf0,0x0(v0) */ storeVu(0,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0010dd88: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0010dd8c: sw s0,0x1c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(16));
/* 0010dd90: sw zero,0xc4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000c4)),(uint32_t)cpu(0));
/* 0010dd94: sw zero,0xc8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000c8)),(uint32_t)cpu(0));
L_0010dd98:;
/* 0010dd98: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0010dd9c:;
/* 0010dd9c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010dda0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010dda4: jr ra */ {uint64_t target=cpu(31);/* delay 0010dda8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010de28(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0010de28: addiu v0,a0,0x40 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000040)));
/* 0010de2c: sqc2 vf0,0x0(v0) */ storeVu(0,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0010de30: addiu v1,a0,0x50 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00000050)));
/* 0010de34: sqc2 vf0,0x0(v1) */ storeVu(0,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0010de38: vaddw.xyz vf10,vf0,vf0 */ constructorVu(10u,0u,0u,14u,3u,0u);
/* 0010de3c: vmulx.w vf10,vf0,vf0 */ constructorVu(10u,0u,0u,1u,0u,1u);
/* 0010de40: addiu a0,a0,0x60 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000060)));
/* 0010de44: sqc2 vf10,0x0(a0) */ storeVu(10,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0010de48: jr ra */ {uint64_t target=cpu(31);/* delay 0010de4c */ checkReturn(target,incoming);return;}
}
static void body_0010de50(void){
uint64_t incoming=cpu(31);
/* 0010de50: addiu a1,a0,0xa0 */ set(5,sx((uint32_t)cpu(4)+UINT32_C(0x000000a0)));
/* 0010de54: addiu v1,a0,0x60 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00000060)));
/* 0010de58: lq v0,0x0(v1) */ requestLq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0010de5c: sq v0,0x0(a1) */ sq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0010de60: addiu a2,a0,0x90 */ set(6,sx((uint32_t)cpu(4)+UINT32_C(0x00000090)));
/* 0010de64: addiu v1,a0,0x50 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00000050)));
/* 0010de68: lq v0,0x0(v1) */ requestLq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0010de6c: sq v0,0x0(a2) */ sq(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 0010de70: addiu a1,a0,0x40 */ set(5,sx((uint32_t)cpu(4)+UINT32_C(0x00000040)));
/* 0010de74: addiu a0,a0,0x80 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000080)));
/* 0010de78: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0010de7c: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0010de80: jr ra */ {uint64_t target=cpu(31);/* delay 0010de84 */ checkReturn(target,incoming);return;}
}
static void body_0010dea8(void){
uint64_t incoming=cpu(31);
/* 0010dea8: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 0010deac: li v0,-0x3 */ set(2,sx(UINT32_C(0xfffffffd)));
/* 0010deb0: lw v1,0xc0(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x000000c0)));
/* 0010deb4: addiu a0,a2,0x40 */ set(4,sx((uint32_t)cpu(6)+UINT32_C(0x00000040)));
/* 0010deb8: ori v1,v1,0x1 */ set(3,cpu(3)|UINT32_C(0x00000001));
/* 0010debc: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 0010dec0: sw v1,0xc0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x000000c0)),(uint32_t)cpu(3));
/* 0010dec4: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0010dec8: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0010decc: jr ra */ {uint64_t target=cpu(31);/* delay 0010ded0 */ checkReturn(target,incoming);return;}
}
static void body_0010ded8(void){
uint64_t incoming=cpu(31);
/* 0010ded8: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 0010dedc: li v0,-0x3 */ set(2,sx(UINT32_C(0xfffffffd)));
/* 0010dee0: lw v1,0xc0(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x000000c0)));
/* 0010dee4: addiu a0,a2,0x50 */ set(4,sx((uint32_t)cpu(6)+UINT32_C(0x00000050)));
/* 0010dee8: ori v1,v1,0x1 */ set(3,cpu(3)|UINT32_C(0x00000001));
/* 0010deec: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 0010def0: sw v1,0xc0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x000000c0)),(uint32_t)cpu(3));
/* 0010def4: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0010def8: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0010defc: jr ra */ {uint64_t target=cpu(31);/* delay 0010df00 */ checkReturn(target,incoming);return;}
}
static void body_0010ffe0(void){
uint64_t incoming=cpu(31);
/* 0010ffe0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010ffe4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010ffe8: move s0,a0 */ set(16,cpu(4));
/* 0010ffec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010fff0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010fff4: jal 0x002a8af8 */ set(31,UINT64_C(0x0010fffc));/* delay 0010fff8 */ set(4,sx(UINT32_C(0x000000ac)));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x0010fff4));
/* 0010fffc: move s1,v0 */ set(17,cpu(2));
/* 00110000: move a1,zero */ set(5,cpu(0));
/* 00110004: move a0,s1 */ set(4,cpu(17));
/* 00110008: jal 0x002d4558 */ set(31,UINT64_C(0x00110010));/* delay 0011000c */ set(6,sx(UINT32_C(0x000000ac)));nocturneFieldMovementCall(UINT32_C(0x002d4558),UINT32_C(0x00110008));
/* 00110010: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 00110014: sw v1,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 00110018: jal 0x0010e690 */ set(31,UINT64_C(0x00110020));/* delay 0011001c */ set(4,cpu(0));body_0010e690();
/* 00110020: sw s0,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(16));
/* 00110024: sw v0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 00110028: addiu v0,s1,0xa8 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x000000a8)));
/* 0011002c: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 00110030: li v1,0x17 */ set(3,sx(UINT32_C(0x00000017)));
/* 00110034: nop  */ 
L_00110038:;
/* 00110038: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 0011003c: sw a0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 00110040: nop  */ 
/* 00110044: nop  */ 
/* 00110048: nop  */ 
/* 0011004c: bgez v1,0x00110038 */ {int taken=((int64_t)cpu(3)>=0);/* delay 00110050 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffc)));if(taken){goto L_00110038;}}
/* 00110054: move v0,s1 */ set(2,cpu(17));
/* 00110058: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0011005c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00110060: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00110064: jr ra */ {uint64_t target=cpu(31);/* delay 00110068 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010fc38(void){
uint64_t incoming=cpu(31);
/* 0010fc38: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0010fc3c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010fc40: move s0,a0 */ set(16,cpu(4));
/* 0010fc44: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010fc48: jal 0x002a8af8 */ set(31,UINT64_C(0x0010fc50));/* delay 0010fc4c */ set(4,sx(UINT32_C(0x00000010)));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x0010fc48));
/* 0010fc50: move a1,zero */ set(5,cpu(0));
/* 0010fc54: sw v0,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 0010fc58: move a0,v0 */ set(4,cpu(2));
/* 0010fc5c: jal 0x002d4558 */ set(31,UINT64_C(0x0010fc64));/* delay 0010fc60 */ set(6,sx(UINT32_C(0x00000010)));nocturneFieldMovementCall(UINT32_C(0x002d4558),UINT32_C(0x0010fc5c));
/* 0010fc64: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0010fc68: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010fc6c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010fc70: jr ra */ {uint64_t target=cpu(31);/* delay 0010fc74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0010fe48(void){
uint64_t incoming=cpu(31);
/* 0010fe48: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010fe4c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010fe50: move s2,a0 */ set(18,cpu(4));
/* 0010fe54: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010fe58: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010fe5c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010fe60: jal 0x0010f040 */ set(31,UINT64_C(0x0010fe68));/* delay 0010fe64 */ set(4,sx(UINT32_C(0x00000003)));nocturneFieldMovementCall(UINT32_C(0x0010f040),UINT32_C(0x0010fe60));
/* 0010fe68: move s0,v0 */ set(16,cpu(2));
/* 0010fe6c: jal 0x0010e248 */ set(31,UINT64_C(0x0010fe74));/* delay 0010fe70 */ lw(17,ea(16,(int32_t)UINT32_C(0x00000018)));body_0010e248();
/* 0010fe74: lw v1,-0x57a8(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa858)));
/* 0010fe78: li a1,0xa */ set(5,sx(UINT32_C(0x0000000a)));
/* 0010fe7c: sw s2,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));
/* 0010fe80: addiu a0,v1,0x1 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0010fe84: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 0010fe88: div a0,a1 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(5),1,0);
/* 0010fe8c: lui at,0x30 */ set(1,sx(UINT32_C(0x00300000)));
/* 0010fe90: addiu at,at,-0x5990 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffa670)));
/* 0010fe94: addu v1,at,v1 */ set(3,sx((uint32_t)cpu(1)+(uint32_t)cpu(3)));
/* 0010fe98: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 0010fe9c: move v0,s0 */ set(2,cpu(16));
/* 0010fea0: sw v1,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 0010fea4: sw a0,-0x57a8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa858)),(uint32_t)cpu(4));
/* 0010fea8: beql a1,zero,0x0010feb0 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 0010feac */ nocturneFieldMovementTrap(7u,UINT32_C(0x0010feac));goto L_0010feb0;}}
L_0010feb0:;
/* 0010feb0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010feb4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010feb8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010febc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010fec0: mfhi a2 */ set(6,nocturneEffectHostHi());
/* 0010fec4: sw a2,-0x57a8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa858)),(uint32_t)cpu(6));
/* 0010fec8: jr ra */ {uint64_t target=cpu(31);/* delay 0010fecc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00112168(void){
uint64_t incoming=cpu(31);
/* 00112168: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0011216c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00112170: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112174: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112178: jal 0x00110300 */ set(31,UINT64_C(0x00112180));/* delay 0011217c */ set(16,cpu(4));body_00110300();
/* 00112180: bne v0,zero,0x001121a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00112184 */ set(4,cpu(16));if(taken){goto L_001121a8;}}
/* 00112188: jal 0x0010fe48 */ set(31,UINT64_C(0x00112190));/* delay 0011218c */ body_0010fe48();
/* 00112190: move a0,s0 */ set(4,cpu(16));
/* 00112194: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112198: move a1,v0 */ set(5,cpu(2));
/* 0011219c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001121a0: j 0x00110238 */ /* delay 001121a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00110238();return;
L_001121a8:;
/* 001121a8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001121ac: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001121b0: jr ra */ {uint64_t target=cpu(31);/* delay 001121b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00110238(void){
uint64_t incoming=cpu(31);
/* 00110238: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0011023c: move v0,zero */ set(2,cpu(0));
/* 00110240: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110244: move s0,a1 */ set(16,cpu(5));
/* 00110248: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0011024c: move s1,a0 */ set(17,cpu(4));
/* 00110250: beq s0,zero,0x00110280 */ {int taken=(cpu(16)==cpu(0));/* delay 00110254 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_00110280;}}
/* 00110258: jal 0x0010ff90 */ set(31,UINT64_C(0x00110260));/* delay 0011025c */ set(4,byte(ea(16,(int32_t)UINT32_C(0x0000000f))));body_0010ff90();
/* 00110260: move a0,s1 */ set(4,cpu(17));
/* 00110264: move a1,s0 */ set(5,cpu(16));
/* 00110268: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0011026c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00110270: move a2,v0 */ set(6,cpu(2));
/* 00110274: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00110278: j 0x00110298 */ /* delay 0011027c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_00110298();return;
L_00110280:;
/* 00110280: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110284: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00110288: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0011028c: jr ra */ {uint64_t target=cpu(31);/* delay 00110290 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00110298(void){
uint64_t incoming=cpu(31);
/* 00110298: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0011029c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001102a0: move s0,a2 */ set(16,cpu(6));
/* 001102a4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001102a8: move s1,a0 */ set(17,cpu(4));
/* 001102ac: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001102b0: move s3,a1 */ set(19,cpu(5));
/* 001102b4: move a1,s0 */ set(5,cpu(16));
/* 001102b8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001102bc: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001102c0: jal 0x00110300 */ set(31,UINT64_C(0x001102c8));/* delay 001102c4 */ set(16,sx((uint32_t)cpu(16)<<2));body_00110300();
/* 001102c8: move a0,s1 */ set(4,cpu(17));
/* 001102cc: jal 0x001122a0 */ set(31,UINT64_C(0x001102d4));/* delay 001102d0 */ set(18,cpu(2));body_001122a0();
/* 001102d4: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001102d8: move v0,s2 */ set(2,cpu(18));
/* 001102dc: sw s3,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(19));
/* 001102e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001102e4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001102e8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001102ec: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001102f0: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001102f4: jr ra */ {uint64_t target=cpu(31);/* delay 001102f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00110300(void){
uint64_t incoming=cpu(31);
/* 00110300: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00110304: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110308: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0011030c: jal 0x001122a0 */ set(31,UINT64_C(0x00110314));/* delay 00110310 */ set(16,cpu(5));body_001122a0();
/* 00110314: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 00110318: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0011031c: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00110320: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 00110324: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110328: jr ra */ {uint64_t target=cpu(31);/* delay 0011032c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001122a0(void){
uint64_t incoming=cpu(31);
/* 001122a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001122a4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001122a8: lbu v0,0xf(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x0000000f))));
/* 001122ac: addiu v0,v0,-0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffc)));
/* 001122b0: sltiu v1,v0,0x6 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000006));
/* 001122b4: beq v1,zero,0x00112334 */ {int taken=(cpu(3)==cpu(0));/* delay 001122b8 */ set(5,cpu(0));if(taken){goto L_00112334;}}
/* 001122bc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001122c0: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 001122c4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001122c8: lw v1,0xd20(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000d20)));
/* 001122cc: jr v1 */ {uint64_t target=cpu(3);/* delay 001122d0 */ switch((uint32_t)target){case UINT32_C(0x001122d8):goto L_001122d8;case UINT32_C(0x001122e8):goto L_001122e8;case UINT32_C(0x001122f8):goto L_001122f8;case UINT32_C(0x00112308):goto L_00112308;case UINT32_C(0x00112318):goto L_00112318;case UINT32_C(0x00112328):goto L_00112328;default:abort();}}
L_001122d8:;
/* 001122d8: jal 0x001125c8 */ set(31,UINT64_C(0x001122e0));/* delay 001122dc */ nocturneFieldMovementCall(UINT32_C(0x001125c8),UINT32_C(0x001122d8));
/* 001122e0: b 0x00112334 */ /* delay 001122e4 */ set(5,cpu(2));goto L_00112334;
L_001122e8:;
/* 001122e8: jal 0x00112a30 */ set(31,UINT64_C(0x001122f0));/* delay 001122ec */ body_00112a30();
/* 001122f0: b 0x00112334 */ /* delay 001122f4 */ set(5,cpu(2));goto L_00112334;
L_001122f8:;
/* 001122f8: jal 0x00113300 */ set(31,UINT64_C(0x00112300));/* delay 001122fc */ nocturneFieldMovementCall(UINT32_C(0x00113300),UINT32_C(0x001122f8));
/* 00112300: b 0x00112334 */ /* delay 00112304 */ set(5,cpu(2));goto L_00112334;
L_00112308:;
/* 00112308: jal 0x00114038 */ set(31,UINT64_C(0x00112310));/* delay 0011230c */ nocturneFieldMovementCall(UINT32_C(0x00114038),UINT32_C(0x00112308));
/* 00112310: b 0x00112334 */ /* delay 00112314 */ set(5,cpu(2));goto L_00112334;
L_00112318:;
/* 00112318: jal 0x00115728 */ set(31,UINT64_C(0x00112320));/* delay 0011231c */ nocturneFieldMovementCall(UINT32_C(0x00115728),UINT32_C(0x00112318));
/* 00112320: b 0x00112334 */ /* delay 00112324 */ set(5,cpu(2));goto L_00112334;
L_00112328:;
/* 00112328: jal 0x00115a70 */ set(31,UINT64_C(0x00112330));/* delay 0011232c */ nocturneFieldMovementCall(UINT32_C(0x00115a70),UINT32_C(0x00112328));
/* 00112330: move a1,v0 */ set(5,cpu(2));
L_00112334:;
/* 00112334: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112338: move v0,a1 */ set(2,cpu(5));
/* 0011233c: jr ra */ {uint64_t target=cpu(31);/* delay 00112340 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00112a30(void){
uint64_t incoming=cpu(31);
/* 00112a30: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 00112a34: jr ra */ {uint64_t target=cpu(31);/* delay 00112a38 */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));checkReturn(target,incoming);return;}
}
static void body_0010ff90(void){
uint64_t incoming=cpu(31);
/* 0010ff90: addiu a0,a0,-0x2 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffe)));
/* 0010ff94: sltiu v0,a0,0xc */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 0010ff98: beq v0,zero,0x0010ffd4 */ {int taken=(cpu(2)==cpu(0));/* delay 0010ff9c */ set(5,cpu(0));if(taken){goto L_0010ffd4;}}
/* 0010ffa0: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 0010ffa4: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 0010ffa8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0010ffac: lw v1,-0x7e0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xfffff820)));
/* 0010ffb0: jr v1 */ {uint64_t target=cpu(3);/* delay 0010ffb4 */ switch((uint32_t)target){case UINT32_C(0x0010ffb8):goto L_0010ffb8;case UINT32_C(0x0010ffc0):goto L_0010ffc0;case UINT32_C(0x0010ffc8):goto L_0010ffc8;case UINT32_C(0x0010ffd0):goto L_0010ffd0;case UINT32_C(0x0010ffd4):goto L_0010ffd4;default:abort();}}
L_0010ffb8:;
/* 0010ffb8: b 0x0010ffd4 */ /* delay 0010ffbc */ set(5,sx(UINT32_C(0x00000001)));goto L_0010ffd4;
L_0010ffc0:;
/* 0010ffc0: b 0x0010ffd4 */ /* delay 0010ffc4 */ set(5,sx(UINT32_C(0x00000003)));goto L_0010ffd4;
L_0010ffc8:;
/* 0010ffc8: b 0x0010ffd4 */ /* delay 0010ffcc */ set(5,sx(UINT32_C(0x00000004)));goto L_0010ffd4;
L_0010ffd0:;
/* 0010ffd0: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
L_0010ffd4:;
/* 0010ffd4: jr ra */ {uint64_t target=cpu(31);/* delay 0010ffd8 */ set(2,cpu(5));checkReturn(target,incoming);return;}
}
static void body_0010e248(void){
uint64_t incoming=cpu(31);
/* 0010e248: lw v0,-0x57b0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa850)));
/* 0010e24c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0010e250: andi v0,v0,0xffff */ set(2,cpu(2)&UINT32_C(0x0000ffff));
/* 0010e254: jr ra */ {uint64_t target=cpu(31);/* delay 0010e258 */ sw(ea(28,(int32_t)UINT32_C(0xffffa850)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_0010e690(void){
uint64_t incoming=cpu(31);
/* 0010e690: lw v1,-0x57ac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010e694: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010e698: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010e69c: move s2,a0 */ set(18,cpu(4));
/* 0010e6a0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010e6a4: move v0,zero */ set(2,cpu(0));
/* 0010e6a8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010e6ac: beq v1,zero,0x0010e72c */ {int taken=(cpu(3)==cpu(0));/* delay 0010e6b0 */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_0010e72c;}}
/* 0010e6b4: lw s1,0x18(v1) */ lw(17,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0010e6b8: lhu v1,0x1e(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000001e))));
/* 0010e6bc: slt v1,v1,s2 */ set(3,(int64_t)cpu(3)<(int64_t)cpu(18));
/* 0010e6c0: bnel v1,zero,0x0010e730 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0010e6c4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0010e730;}}
/* 0010e6c8: jal 0x002a8af8 */ set(31,UINT64_C(0x0010e6d0));/* delay 0010e6cc */ set(4,sx(UINT32_C(0x00000010)));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x0010e6c8));
/* 0010e6d0: move a1,s2 */ set(5,cpu(18));
/* 0010e6d4: move s0,v0 */ set(16,cpu(2));
/* 0010e6d8: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 0010e6dc: beq s0,zero,0x0010e72c */ {int taken=(cpu(16)==cpu(0));/* delay 0010e6e0 */ set(4,cpu(16));if(taken){goto L_0010e72c;}}
/* 0010e6e4: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 0010e6e8: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 0010e6ec: sh v1,0x4(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
/* 0010e6f0: lw v0,0x24(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 0010e6f4: sh v1,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 0010e6f8: sh v1,0x2(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(3));
/* 0010e6fc: bne v0,zero,0x0010e710 */ {int taken=(cpu(2)!=cpu(0));/* delay 0010e700 */ sh(ea(16,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(0));if(taken){goto L_0010e710;}}
/* 0010e704: sw s0,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(16));
/* 0010e708: b 0x0010e720 */ /* delay 0010e70c */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(16));goto L_0010e720;
L_0010e710:;
/* 0010e710: sw s0,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));
/* 0010e714: lw v0,0x24(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 0010e718: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 0010e71c: sw s0,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(16));
L_0010e720:;
/* 0010e720: jal 0x0010ea90 */ set(31,UINT64_C(0x0010e728));/* delay 0010e724 */ body_0010ea90();
/* 0010e728: move v0,s0 */ set(2,cpu(16));
L_0010e72c:;
/* 0010e72c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0010e730:;
/* 0010e730: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010e734: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010e738: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010e73c: jr ra */ {uint64_t target=cpu(31);/* delay 0010e740 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010e748(void){
uint64_t incoming=cpu(31);
/* 0010e748: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010e74c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010e750: move s0,a0 */ set(16,cpu(4));
/* 0010e754: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010e758: beq s0,zero,0x0010e7c8 */ {int taken=(cpu(16)==cpu(0));/* delay 0010e75c */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_0010e7c8;}}
/* 0010e760: lw v0,-0x57ac(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010e764: beql v0,zero,0x0010e7cc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0010e768 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0010e7cc;}}
/* 0010e76c: jal 0x0010e8e8 */ set(31,UINT64_C(0x0010e774));/* delay 0010e770 */ lw(17,ea(2,(int32_t)UINT32_C(0x00000018)));body_0010e8e8();
/* 0010e774: lw v1,0xc(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0010e778: bne v1,zero,0x0010e790 */ {int taken=(cpu(3)!=cpu(0));/* delay 0010e77c */ set(4,cpu(16));if(taken){goto L_0010e790;}}
/* 0010e780: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0010e784: b 0x0010e798 */ /* delay 0010e788 */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));goto L_0010e798;
L_0010e790:;
/* 0010e790: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0010e794: sw v0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_0010e798:;
/* 0010e798: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0010e79c: bne v1,zero,0x0010e7b0 */ {int taken=(cpu(3)!=cpu(0));/* delay 0010e7a0 */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));if(taken){goto L_0010e7b0;}}
/* 0010e7a4: b 0x0010e7b4 */ /* delay 0010e7a8 */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));goto L_0010e7b4;
L_0010e7b0:;
/* 0010e7b0: sw v0,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
L_0010e7b4:;
/* 0010e7b4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010e7b8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010e7bc: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010e7c0: j 0x002a8bd8 */ /* delay 0010e7c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneFieldMovementCall(UINT32_C(0x002a8bd8),UINT32_C(0x0010e7c0));return;
L_0010e7c8:;
/* 0010e7c8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0010e7cc:;
/* 0010e7cc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010e7d0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010e7d4: jr ra */ {uint64_t target=cpu(31);/* delay 0010e7d8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010e8e8(void){
uint64_t incoming=cpu(31);
/* 0010e8e8: move a3,a0 */ set(7,cpu(4));
/* 0010e8ec: beq a3,zero,0x0010e99c */ {int taken=(cpu(7)==cpu(0));/* delay 0010e8f0 */ if(taken){goto L_0010e99c;}}
/* 0010e8f4: lhu v0,0x6(a3) */ set(2,half(ea(7,(int32_t)UINT32_C(0x00000006))));
/* 0010e8f8: beq v0,zero,0x0010e99c */ {int taken=(cpu(2)==cpu(0));/* delay 0010e8fc */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa854)));if(taken){goto L_0010e99c;}}
/* 0010e900: beq v0,zero,0x0010e99c */ {int taken=(cpu(2)==cpu(0));/* delay 0010e904 */ if(taken){goto L_0010e99c;}}
/* 0010e908: lh v1,0x0(a3) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x00000000))));
/* 0010e90c: lw a2,0x18(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 0010e910: bltz v1,0x0010e93c */ {int taken=((int64_t)cpu(3)<0);/* delay 0010e914 */ set(8,half(ea(7,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_0010e93c;}}
/* 0010e918: lw a0,0x14(a2) */ lw(4,ea(6,(int32_t)UINT32_C(0x00000014)));
/* 0010e91c: nop  */ 
L_0010e920:;
/* 0010e920: sll v0,v1,0x3 */ set(2,sx((uint32_t)cpu(3)<<3));
/* 0010e924: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0010e928: lh v1,0x4(v0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 0010e92c: nop  */ 
/* 0010e930: nop  */ 
/* 0010e934: bgez v1,0x0010e920 */ {int taken=((int64_t)cpu(3)>=0);/* delay 0010e938 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));if(taken){goto L_0010e920;}}
L_0010e93c:;
/* 0010e93c: lh v0,0x1c(a2) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(6,(int32_t)UINT32_C(0x0000001c))));
/* 0010e940: bgezl v0,0x0010e950 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 0010e944 */ lw(5,ea(6,(int32_t)UINT32_C(0x00000014)));goto L_0010e950;}}
/* 0010e948: b 0x0010e970 */ /* delay 0010e94c */ sh(ea(6,(int32_t)UINT32_C(0x0000001a)),(uint16_t)cpu(8));goto L_0010e970;
L_0010e950:;
/* 0010e950: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0010e954: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0010e958: sh t0,0x4(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(8));
/* 0010e95c: lh v1,0x0(a3) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x00000000))));
/* 0010e960: lhu a0,0x1c(a2) */ set(4,half(ea(6,(int32_t)UINT32_C(0x0000001c))));
/* 0010e964: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 0010e968: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0010e96c: sh a0,0x6(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(4));
L_0010e970:;
/* 0010e970: lhu v0,0x2(a3) */ set(2,half(ea(7,(int32_t)UINT32_C(0x00000002))));
/* 0010e974: sh v0,0x1c(a2) */ sh(ea(6,(int32_t)UINT32_C(0x0000001c)),(uint16_t)cpu(2));
/* 0010e978: lhu v0,0x1e(a2) */ set(2,half(ea(6,(int32_t)UINT32_C(0x0000001e))));
/* 0010e97c: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 0010e980: lhu v1,0x6(a3) */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000006))));
/* 0010e984: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0010e988: sh v0,0x1e(a2) */ sh(ea(6,(int32_t)UINT32_C(0x0000001e)),(uint16_t)cpu(2));
/* 0010e98c: sh a0,0x4(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(4));
/* 0010e990: sh zero,0x6(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(0));
/* 0010e994: sh a0,0x0(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));
/* 0010e998: sh a0,0x2(a3) */ sh(ea(7,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(4));
L_0010e99c:;
/* 0010e99c: jr ra */ {uint64_t target=cpu(31);/* delay 0010e9a0 */ checkReturn(target,incoming);return;}
}
static void body_0010f270(void){
uint64_t incoming=cpu(31);
/* 0010f270: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010f274: sll v1,a1,0x1 */ set(3,sx((uint32_t)cpu(5)<<1));
/* 0010f278: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f27c: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0010f280: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f284: sll s0,v1,0x2 */ set(16,sx((uint32_t)cpu(3)<<2));
/* 0010f288: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f28c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010f290: lw s2,0x18(a0) */ lw(18,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0010f294: lw a0,0x8(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 0010f298: addu a0,s0,a0 */ set(4,sx((uint32_t)cpu(16)+(uint32_t)cpu(4)));
/* 0010f29c: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0010f2a0: beq v1,zero,0x0010f2ec */ {int taken=(cpu(3)==cpu(0));/* delay 0010f2a4 */ set(2,cpu(0));if(taken){goto L_0010f2ec;}}
/* 0010f2a8: jal 0x0010e690 */ set(31,UINT64_C(0x0010f2b0));/* delay 0010f2ac */ set(4,cpu(0));body_0010e690();
/* 0010f2b0: move s1,v0 */ set(17,cpu(2));
/* 0010f2b4: lw v0,0x8(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 0010f2b8: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0010f2bc: lw s0,0x4(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 0010f2c0: move a0,s1 */ set(4,cpu(17));
/* 0010f2c4: nop  */ 
L_0010f2c8:;
/* 0010f2c8: jal 0x0010ea90 */ set(31,UINT64_C(0x0010f2d0));/* delay 0010f2cc */ set(5,sx(UINT32_C(0x00000001)));body_0010ea90();
/* 0010f2d0: move a0,s1 */ set(4,cpu(17));
/* 0010f2d4: jal 0x0010ebe0 */ set(31,UINT64_C(0x0010f2dc));/* delay 0010f2d8 */ set(5,cpu(16));body_0010ebe0();
/* 0010f2dc: lw s0,0x20(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 0010f2e0: bne s0,zero,0x0010f2c8 */ {int taken=(cpu(16)!=cpu(0));/* delay 0010f2e4 */ set(4,cpu(17));if(taken){goto L_0010f2c8;}}
/* 0010f2e8: move v0,s1 */ set(2,cpu(17));
L_0010f2ec:;
/* 0010f2ec: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f2f0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f2f4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f2f8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010f2fc: jr ra */ {uint64_t target=cpu(31);/* delay 0010f300 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010ea38(void){
uint64_t incoming=cpu(31);
/* 0010ea38: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010ea3c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010ea40: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010ea44: move s0,a0 */ set(16,cpu(4));
/* 0010ea48: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010ea4c: move s1,a1 */ set(17,cpu(5));
L_0010ea50:;
/* 0010ea50: jal 0x0010ec20 */ set(31,UINT64_C(0x0010ea58));/* delay 0010ea54 */ set(4,cpu(16));body_0010ec20();
/* 0010ea58: move v1,v0 */ set(3,cpu(2));
/* 0010ea5c: beq v1,zero,0x0010ea7c */ {int taken=(cpu(3)==cpu(0));/* delay 0010ea60 */ set(4,cpu(16));if(taken){goto L_0010ea7c;}}
/* 0010ea64: beq s1,v1,0x0010ea7c */ {int taken=(cpu(17)==cpu(3));/* delay 0010ea68 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0010ea7c;}}
/* 0010ea6c: jal 0x0010ec78 */ set(31,UINT64_C(0x0010ea74));/* delay 0010ea70 */ body_0010ec78();
/* 0010ea74: bne v0,zero,0x0010ea50 */ {int taken=(cpu(2)!=cpu(0));/* delay 0010ea78 */ if(taken){goto L_0010ea50;}}
L_0010ea7c:;
/* 0010ea7c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010ea80: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010ea84: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010ea88: jr ra */ {uint64_t target=cpu(31);/* delay 0010ea8c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010ea90(void){
uint64_t incoming=cpu(31);
/* 0010ea90: move t2,a0 */ set(10,cpu(4));
/* 0010ea94: beq a1,zero,0x0010ebc0 */ {int taken=(cpu(5)==cpu(0));/* delay 0010ea98 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0010ebc0;}}
/* 0010ea9c: lw v1,-0x57ac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010eaa0: beq v1,zero,0x0010ebc0 */ {int taken=(cpu(3)==cpu(0));/* delay 0010eaa4 */ set(2,cpu(0));if(taken){goto L_0010ebc0;}}
/* 0010eaa8: lw a2,0x18(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0010eaac: lhu v0,0x1e(a2) */ set(2,half(ea(6,(int32_t)UINT32_C(0x0000001e))));
/* 0010eab0: slt v0,v0,a1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(5));
/* 0010eab4: bne v0,zero,0x0010eac4 */ {int taken=(cpu(2)!=cpu(0));/* delay 0010eab8 */ if(taken){goto L_0010eac4;}}
/* 0010eabc: bgez a1,0x0010ead0 */ {int taken=((int64_t)cpu(5)>=0);/* delay 0010eac0 */ if(taken){goto L_0010ead0;}}
L_0010eac4:;
/* 0010eac4: jr ra */ {uint64_t target=cpu(31);/* delay 0010eac8 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_0010ead0:;
/* 0010ead0: beq t2,zero,0x0010ebc0 */ {int taken=(cpu(10)==cpu(0));/* delay 0010ead4 */ set(2,cpu(0));if(taken){goto L_0010ebc0;}}
/* 0010ead8: lh t3,0x1a(a2) */ set(11,(uint64_t)(int64_t)(int16_t)half(ea(6,(int32_t)UINT32_C(0x0000001a))));
/* 0010eadc: addiu t0,a1,-0x1 */ set(8,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 0010eae0: move t1,zero */ set(9,cpu(0));
/* 0010eae4: blez t0,0x0010eb20 */ {int taken=((int64_t)cpu(8)<=0);/* delay 0010eae8 */ set(4,cpu(11));if(taken){goto L_0010eb20;}}
/* 0010eaec: lw a3,0x14(a2) */ lw(7,ea(6,(int32_t)UINT32_C(0x00000014)));
L_0010eaf0:;
/* 0010eaf0: sll v0,a0,0x10 */ set(2,sx((uint32_t)cpu(4)<<16));
/* 0010eaf4: addiu t1,t1,0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000001)));
/* 0010eaf8: sra v0,v0,0xd */ set(2,sx((uint32_t)((int32_t)cpu(2)>>13)));
/* 0010eafc: slt v1,t1,t0 */ set(3,(int64_t)cpu(9)<(int64_t)cpu(8));
/* 0010eb00: addu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 0010eb04: lhu v0,0x4(v0) */ set(2,half(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 0010eb08: sh v0,0x1a(a2) */ sh(ea(6,(int32_t)UINT32_C(0x0000001a)),(uint16_t)cpu(2));
/* 0010eb0c: bne v1,zero,0x0010eaf0 */ {int taken=(cpu(3)!=cpu(0));/* delay 0010eb10 */ set(4,cpu(2));if(taken){goto L_0010eaf0;}}
/* 0010eb14: b 0x0010eb28 */ /* delay 0010eb18 */ set(3,sx((uint32_t)cpu(4)<<16));goto L_0010eb28;
L_0010eb20:;
/* 0010eb20: lw a3,0x14(a2) */ lw(7,ea(6,(int32_t)UINT32_C(0x00000014)));
/* 0010eb24: sll v1,a0,0x10 */ set(3,sx((uint32_t)cpu(4)<<16));
L_0010eb28:;
/* 0010eb28: li t0,-0x1 */ set(8,sx(UINT32_C(0xffffffff)));
/* 0010eb2c: sra t1,v1,0x10 */ set(9,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 0010eb30: sll v0,t1,0x3 */ set(2,sx((uint32_t)cpu(9)<<3));
/* 0010eb34: addu a0,v0,a3 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 0010eb38: lhu v1,0x4(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 0010eb3c: sll v0,v1,0x10 */ set(2,sx((uint32_t)cpu(3)<<16));
/* 0010eb40: sra v0,v0,0x10 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>16)));
/* 0010eb44: bne v0,t0,0x0010eb58 */ {int taken=(cpu(2)!=cpu(8));/* delay 0010eb48 */ sh(ea(6,(int32_t)UINT32_C(0x0000001a)),(uint16_t)cpu(3));if(taken){goto L_0010eb58;}}
/* 0010eb4c: b 0x0010eb6c */ /* delay 0010eb50 */ sh(ea(6,(int32_t)UINT32_C(0x0000001c)),(uint16_t)cpu(8));goto L_0010eb6c;
L_0010eb58:;
/* 0010eb58: sh t0,0x4(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(8));
/* 0010eb5c: lh v0,0x1a(a2) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(6,(int32_t)UINT32_C(0x0000001a))));
/* 0010eb60: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0010eb64: addu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 0010eb68: sh t0,0x6(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(8));
L_0010eb6c:;
/* 0010eb6c: lhu v0,0x1e(a2) */ set(2,half(ea(6,(int32_t)UINT32_C(0x0000001e))));
/* 0010eb70: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 0010eb74: sh v0,0x1e(a2) */ sh(ea(6,(int32_t)UINT32_C(0x0000001e)),(uint16_t)cpu(2));
/* 0010eb78: lh v0,0x2(t2) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(10,(int32_t)UINT32_C(0x00000002))));
/* 0010eb7c: bgezl v0,0x0010eb90 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 0010eb80 */ set(2,sx((uint32_t)cpu(2)<<3));goto L_0010eb90;}}
/* 0010eb84: sh t1,0x2(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(9));
/* 0010eb88: b 0x0010ebac */ /* delay 0010eb8c */ sh(ea(10,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(11));goto L_0010ebac;
L_0010eb90:;
/* 0010eb90: sll a0,t3,0x3 */ set(4,sx((uint32_t)cpu(11)<<3));
/* 0010eb94: addu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 0010eb98: addu a0,a0,a3 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 0010eb9c: sh t3,0x4(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(11));
/* 0010eba0: lhu v1,0x2(t2) */ set(3,half(ea(10,(int32_t)UINT32_C(0x00000002))));
/* 0010eba4: sh v1,0x6(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(3));
/* 0010eba8: sh t1,0x2(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(9));
L_0010ebac:;
/* 0010ebac: lhu v1,0x6(t2) */ set(3,half(ea(10,(int32_t)UINT32_C(0x00000006))));
/* 0010ebb0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0010ebb4: sh t3,0x4(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(11));
/* 0010ebb8: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0010ebbc: sh v1,0x6(t2) */ sh(ea(10,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(3));
L_0010ebc0:;
/* 0010ebc0: jr ra */ {uint64_t target=cpu(31);/* delay 0010ebc4 */ checkReturn(target,incoming);return;}
}
static void body_0010ebe0(void){
uint64_t incoming=cpu(31);
/* 0010ebe0: lhu v1,0x6(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000006))));
/* 0010ebe4: move a3,a1 */ set(7,cpu(5));
/* 0010ebe8: beq v1,zero,0x0010ec14 */ {int taken=(cpu(3)==cpu(0));/* delay 0010ebec */ set(2,cpu(0));if(taken){goto L_0010ec14;}}
/* 0010ebf0: lh v1,0x4(a0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 0010ebf4: bltz v1,0x0010ec14 */ {int taken=((int64_t)cpu(3)<0);/* delay 0010ebf8 */ set(6,sx((uint32_t)cpu(3)<<3));if(taken){goto L_0010ec14;}}
/* 0010ebfc: lw a1,-0x57ac(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010ec00: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0010ec04: lw a0,0x18(a1) */ lw(4,ea(5,(int32_t)UINT32_C(0x00000018)));
/* 0010ec08: lw v1,0x14(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000014)));
/* 0010ec0c: addu v1,a2,v1 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(3)));
/* 0010ec10: sw a3,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));
L_0010ec14:;
/* 0010ec14: jr ra */ {uint64_t target=cpu(31);/* delay 0010ec18 */ checkReturn(target,incoming);return;}
}
static void body_0010ec20(void){
uint64_t incoming=cpu(31);
/* 0010ec20: lhu v1,0x6(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000006))));
/* 0010ec24: beq v1,zero,0x0010ec4c */ {int taken=(cpu(3)==cpu(0));/* delay 0010ec28 */ set(2,cpu(0));if(taken){goto L_0010ec4c;}}
/* 0010ec2c: lh v1,0x4(a0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 0010ec30: bltz v1,0x0010ec4c */ {int taken=((int64_t)cpu(3)<0);/* delay 0010ec34 */ set(5,sx((uint32_t)cpu(3)<<3));if(taken){goto L_0010ec4c;}}
/* 0010ec38: lw v0,-0x57ac(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010ec3c: lw a0,0x18(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 0010ec40: lw v1,0x14(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000014)));
/* 0010ec44: addu v1,a1,v1 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 0010ec48: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
L_0010ec4c:;
/* 0010ec4c: jr ra */ {uint64_t target=cpu(31);/* delay 0010ec50 */ checkReturn(target,incoming);return;}
}
static void body_0010ec58(void){
uint64_t incoming=cpu(31);
/* 0010ec58: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 0010ec5c: sll v0,v1,0x10 */ set(2,sx((uint32_t)cpu(3)<<16));
/* 0010ec60: sh v1,0x4(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
/* 0010ec64: sra v0,v0,0x10 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>16)));
/* 0010ec68: nor v0,zero,v0 */ set(2,~(cpu(0)|cpu(2)));
/* 0010ec6c: jr ra */ {uint64_t target=cpu(31);/* delay 0010ec70 */ set(2,sx((uint32_t)cpu(2)>>31));checkReturn(target,incoming);return;}
}
static void body_0010ec78(void){
uint64_t incoming=cpu(31);
/* 0010ec78: move a2,a0 */ set(6,cpu(4));
/* 0010ec7c: move v0,zero */ set(2,cpu(0));
/* 0010ec80: lh v1,0x4(a2) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(6,(int32_t)UINT32_C(0x00000004))));
/* 0010ec84: bltz v1,0x0010ecb4 */ {int taken=((int64_t)cpu(3)<0);/* delay 0010ec88 */ set(5,sx((uint32_t)cpu(3)<<3));if(taken){goto L_0010ecb4;}}
/* 0010ec8c: lw v1,-0x57ac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010ec90: lw a0,0x18(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0010ec94: lw v0,0x14(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000014)));
/* 0010ec98: addu v0,a1,v0 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 0010ec9c: lhu v1,0x4(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 0010eca0: sll v0,v1,0x10 */ set(2,sx((uint32_t)cpu(3)<<16));
/* 0010eca4: sh v1,0x4(a2) */ sh(ea(6,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(3));
/* 0010eca8: sra v0,v0,0x10 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>16)));
/* 0010ecac: nor v0,zero,v0 */ set(2,~(cpu(0)|cpu(2)));
/* 0010ecb0: srl v0,v0,0x1f */ set(2,sx((uint32_t)cpu(2)>>31));
L_0010ecb4:;
/* 0010ecb4: jr ra */ {uint64_t target=cpu(31);/* delay 0010ecb8 */ checkReturn(target,incoming);return;}
}
static void body_0010ebc8(void){
uint64_t incoming=cpu(31);
/* 0010ebc8: beq a0,zero,0x0010ebd4 */ {int taken=(cpu(4)==cpu(0));/* delay 0010ebcc */ set(2,cpu(0));if(taken){goto L_0010ebd4;}}
/* 0010ebd0: lhu v0,0x6(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000006))));
L_0010ebd4:;
/* 0010ebd4: jr ra */ {uint64_t target=cpu(31);/* delay 0010ebd8 */ checkReturn(target,incoming);return;}
}
static void body_0010f970(void){
uint64_t incoming=cpu(31);
/* 0010f970: sltiu v0,a0,0x4 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0010f974: move a1,zero */ set(5,cpu(0));
/* 0010f978: bne v0,zero,0x0010f990 */ {int taken=(cpu(2)!=cpu(0));/* delay 0010f97c */ set(3,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));if(taken){goto L_0010f990;}}
/* 0010f980: bne v1,zero,0x0010f990 */ {int taken=(cpu(3)!=cpu(0));/* delay 0010f984 */ if(taken){goto L_0010f990;}}
/* 0010f988: xori v0,a0,0x8 */ set(2,cpu(4)^UINT32_C(0x00000008));
/* 0010f98c: sltiu a1,v0,0x1 */ set(5,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_0010f990:;
/* 0010f990: jr ra */ {uint64_t target=cpu(31);/* delay 0010f994 */ set(2,cpu(5));checkReturn(target,incoming);return;}
}
static void body_0010fab8(void){
uint64_t incoming=cpu(31);
/* 0010fab8: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0010fabc: sll a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)<<2));
/* 0010fac0: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0010fac4: jr ra */ {uint64_t target=cpu(31);/* delay 0010fac8 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));checkReturn(target,incoming);return;}
}
static void body_0010e548(void){
uint64_t incoming=cpu(31);
/* 0010e548: lw v1,-0x57ac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010e54c: beq v1,zero,0x0010e55c */ {int taken=(cpu(3)==cpu(0));/* delay 0010e550 */ set(2,cpu(0));if(taken){goto L_0010e55c;}}
/* 0010e554: lw v1,0x18(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0010e558: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
L_0010e55c:;
/* 0010e55c: jr ra */ {uint64_t target=cpu(31);/* delay 0010e560 */ checkReturn(target,incoming);return;}
}
static void body_0010e588(void){
uint64_t incoming=cpu(31);
/* 0010e588: lw v1,-0x57ac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa854)));
/* 0010e58c: beq v1,zero,0x0010e59c */ {int taken=(cpu(3)==cpu(0));/* delay 0010e590 */ set(2,cpu(0));if(taken){goto L_0010e59c;}}
/* 0010e594: lw v1,0x18(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 0010e598: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
L_0010e59c:;
/* 0010e59c: jr ra */ {uint64_t target=cpu(31);/* delay 0010e5a0 */ checkReturn(target,incoming);return;}
}
static void body_0028cca8(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 0028cca8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 0028ccac: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0028ccb0: move s2,a0 */ set(18,cpu(4));
/* 0028ccb4: swc1 f20,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);
/* 0028ccb8: mov.S f20,f12 */ f[20]=f[12];
/* 0028ccbc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028ccc0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0028ccc4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0028ccc8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0028cccc: beq s2,zero,0x0028ceb8 */ {int taken=(cpu(18)==cpu(0));/* delay 0028ccd0 */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_0028ceb8;}}
/* 0028ccd4: clear f0 */ f[0]=0;
/* 0028ccd8: c.eq.S f20,f0 */ (void)(EE_FPU_COMPARE_S(f[20],f[0],0)!=0);
/* 0028ccdc: bc1t 0x0028cebc */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)!=0);/* delay 0028cce0 */ set(2,cpu(0));if(taken){goto L_0028cebc;}}
/* 0028cce4: jal 0x0028c9f0 */ set(31,UINT64_C(0x0028ccec));/* delay 0028cce8 */ body_0028c9f0();
/* 0028ccec: move a0,s2 */ set(4,cpu(18));
/* 0028ccf0: jal 0x0028cb68 */ set(31,UINT64_C(0x0028ccf8));/* delay 0028ccf4 */ set(19,cpu(2));body_0028cb68();
/* 0028ccf8: move s4,v0 */ set(20,cpu(2));
/* 0028ccfc: beq s4,zero,0x0028cec0 */ {int taken=(cpu(20)==cpu(0));/* delay 0028cd00 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0028cec0;}}
/* 0028cd04: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028cd08: lui at,0x42c8 */ set(1,sx(UINT32_C(0x42c80000)));
/* 0028cd0c: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0028cd10: lwc1 f0,0x1cf4(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00001cf4)));
/* 0028cd14: add.S f12,f0,f20 */ f[12]=EE_FPU_ADD_S(f[0],f[20]);
/* 0028cd18: c.lt.S f12,f2 */ (void)(EE_FPU_COMPARE_S(f[12],f[2],1)!=0);
/* 0028cd1c: bc1t 0x0028ceb8 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)!=0);/* delay 0028cd20 */ sw(ea(2,(int32_t)UINT32_C(0x00001cf4)),f[12]);if(taken){goto L_0028ceb8;}}
/* 0028cd24: nop  */ 
/* 0028cd28: nop  */ 
/* 0028cd2c: div.S f1,f12,f2 */ f[1]=EE_FPU_DIV_S(f[12],f[2]);
/* 0028cd30: move s1,zero */ set(17,cpu(0));
/* 0028cd34: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0028cd38: mfc1 s0,f0 */ set(16,sx(f[0]));
/* 0028cd3c: mtc1 s0,f0 */ f[0]=(uint32_t)cpu(16);
/* 0028cd40: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0028cd44: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0028cd48: sub.S f0,f12,f0 */ f[0]=EE_FPU_SUB_S(f[12],f[0]);
/* 0028cd4c: b 0x0028cda4 */ /* delay 0028cd50 */ sw(ea(2,(int32_t)UINT32_C(0x00001cf4)),f[0]);goto L_0028cda4;
L_0028cd58:;
/* 0028cd58: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028cd5c: lw v0,0xa4c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000a4c)));
/* 0028cd60: andi v0,v0,0x2 */ set(2,cpu(2)&UINT32_C(0x00000002));
/* 0028cd64: beq v0,zero,0x0028cd88 */ {int taken=(cpu(2)==cpu(0));/* delay 0028cd68 */ set(4,cpu(0));if(taken){goto L_0028cd88;}}
/* 0028cd6c: jal 0x002c0c60 */ set(31,UINT64_C(0x0028cd74));/* delay 0028cd70 */ set(5,sx(UINT32_C(0x00000007)));nocturneFieldMovementCall(UINT32_C(0x002c0c60),UINT32_C(0x0028cd6c));
/* 0028cd74: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028cd78: lhu v1,0x1cf8(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00001cf8))));
/* 0028cd7c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0028cd80: b 0x0028cda0 */ /* delay 0028cd84 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000006)));goto L_0028cda0;
L_0028cd88:;
/* 0028cd88: jal 0x002c0c60 */ set(31,UINT64_C(0x0028cd90));/* delay 0028cd8c */ set(5,sx(UINT32_C(0x00000003)));nocturneFieldMovementCall(UINT32_C(0x002c0c60),UINT32_C(0x0028cd88));
/* 0028cd90: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028cd94: lhu v1,0x1cf8(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00001cf8))));
/* 0028cd98: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0028cd9c: addiu v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000002)));
L_0028cda0:;
/* 0028cda0: sh v1,0x1cf8(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00001cf8)),(uint16_t)cpu(3));
L_0028cda4:;
/* 0028cda4: slt v0,s1,s0 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(16));
/* 0028cda8: bne v0,zero,0x0028cd58 */ {int taken=(cpu(2)!=cpu(0));/* delay 0028cdac */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));if(taken){goto L_0028cd58;}}
/* 0028cdb0: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028cdb4: ori v0,zero,0xfde8 */ set(2,cpu(0)|UINT32_C(0x0000fde8));
/* 0028cdb8: lhu v1,0x1cf8(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00001cf8))));
/* 0028cdbc: sltu v0,v0,v1 */ set(2,cpu(2)<cpu(3));
/* 0028cdc0: beql v0,zero,0x0028cdd4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0028cdc4 */ set(2,half(ea(4,(int32_t)UINT32_C(0x00001cf8))));goto L_0028cdd4;}}
/* 0028cdc8: li v0,-0x218 */ set(2,sx(UINT32_C(0xfffffde8)));
/* 0028cdcc: sh v0,0x1cf8(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00001cf8)),(uint16_t)cpu(2));
/* 0028cdd0: lhu v0,0x1cf8(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00001cf8))));
L_0028cdd4:;
/* 0028cdd4: slt v0,v0,s4 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(20));
/* 0028cdd8: beql v0,zero,0x0028cdf8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0028cddc */ set(4,cpu(0));goto L_0028cdf8;}}
/* 0028cde0: b 0x0028cebc */ /* delay 0028cde4 */ set(2,cpu(0));goto L_0028cebc;
L_0028cde8:;
/* 0028cde8: jal 0x0028cfb0 */ set(31,UINT64_C(0x0028cdf0));/* delay 0028cdec */ body_0028cfb0();
/* 0028cdf0: b 0x0028cebc */ /* delay 0028cdf4 */ set(2,cpu(0));goto L_0028cebc;
L_0028cdf8:;
/* 0028cdf8: jal 0x002c0c60 */ set(31,UINT64_C(0x0028ce00));/* delay 0028cdfc */ set(5,sx(UINT32_C(0x000003e8)));nocturneFieldMovementCall(UINT32_C(0x002c0c60),UINT32_C(0x0028cdf8));
/* 0028ce00: sll a0,s2,0x3 */ set(4,sx((uint32_t)cpu(18)<<3));
/* 0028ce04: subu a0,a0,s2 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(18)));
/* 0028ce08: sll s2,s3,0x18 */ set(18,sx((uint32_t)cpu(19)<<24));
/* 0028ce0c: move t0,v0 */ set(8,cpu(2));
/* 0028ce10: sll v0,s3,0x3 */ set(2,sx((uint32_t)cpu(19)<<3));
/* 0028ce14: sll a1,s3,0x4 */ set(5,sx((uint32_t)cpu(19)<<4));
/* 0028ce18: sll v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)<<4));
/* 0028ce1c: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 0028ce20: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 0028ce24: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0028ce28: lui a1,0x3c */ set(5,sx(UINT32_C(0x003c0000)));
/* 0028ce2c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0028ce30: addiu a1,a1,-0x5216 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffadea)));
/* 0028ce34: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0028ce38: move s0,zero */ set(16,cpu(0));
/* 0028ce3c: addiu a0,v0,0x10 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 0028ce40: move s1,zero */ set(17,cpu(0));
/* 0028ce44: addiu a3,a1,-0x2 */ set(7,sx((uint32_t)cpu(5)+UINT32_C(0xfffffffe)));
L_0028ce48:;
/* 0028ce48: addu a2,a0,a3 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 0028ce4c: lhu v0,0x0(a2) */ set(2,half(ea(6,(int32_t)UINT32_C(0x00000000))));
/* 0028ce50: beq v0,zero,0x0028cea8 */ {int taken=(cpu(2)==cpu(0));/* delay 0028ce54 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));if(taken){goto L_0028cea8;}}
/* 0028ce58: lhu v1,0x0(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 0028ce5c: addu v1,s0,v1 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 0028ce60: slt v0,t0,v1 */ set(2,(int64_t)cpu(8)<(int64_t)cpu(3));
/* 0028ce64: beq v0,zero,0x0028cea8 */ {int taken=(cpu(2)==cpu(0));/* delay 0028ce68 */ set(16,cpu(3));if(taken){goto L_0028cea8;}}
/* 0028ce6c: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028ce70: lw v0,0xa4c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000a4c)));
/* 0028ce74: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0028ce78: beq v0,zero,0x0028ce90 */ {int taken=(cpu(2)==cpu(0));/* delay 0028ce7c */ set(16,half(ea(6,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_0028ce90;}}
/* 0028ce80: jal 0x0028cee0 */ set(31,UINT64_C(0x0028ce88));/* delay 0028ce84 */ set(4,cpu(16));body_0028cee0();
/* 0028ce88: beq v0,zero,0x0028cde8 */ {int taken=(cpu(2)==cpu(0));/* delay 0028ce8c */ if(taken){goto L_0028cde8;}}
L_0028ce90:;
/* 0028ce90: sll v0,s1,0x10 */ set(2,sx((uint32_t)cpu(17)<<16));
/* 0028ce94: sw zero,-0x2c50(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd3b0)),(uint32_t)cpu(0));
/* 0028ce98: or v0,s2,v0 */ set(2,cpu(18)|cpu(2));
/* 0028ce9c: b 0x0028cebc */ /* delay 0028cea0 */ set(2,cpu(2)|cpu(16));goto L_0028cebc;
L_0028cea8:;
/* 0028cea8: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 0028ceac: slti v0,s1,0xc */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 0028ceb0: bne v0,zero,0x0028ce48 */ {int taken=(cpu(2)!=cpu(0));/* delay 0028ceb4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));if(taken){goto L_0028ce48;}}
L_0028ceb8:;
/* 0028ceb8: move v0,zero */ set(2,cpu(0));
L_0028cebc:;
/* 0028cebc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0028cec0:;
/* 0028cec0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0028cec4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0028cec8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0028cecc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0028ced0: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0028ced4: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0028ced8: jr ra */ {uint64_t target=cpu(31);/* delay 0028cedc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_0028cb68(void){
uint64_t incoming=cpu(31);
/* 0028cb68: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0028cb6c: move v0,zero */ set(2,cpu(0));
/* 0028cb70: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028cb74: move s0,a0 */ set(16,cpu(4));
/* 0028cb78: beq s0,zero,0x0028cc88 */ {int taken=(cpu(16)==cpu(0));/* delay 0028cb7c */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_0028cc88;}}
/* 0028cb80: jal 0x0028c9f0 */ set(31,UINT64_C(0x0028cb88));/* delay 0028cb84 */ body_0028c9f0();
/* 0028cb88: move a3,zero */ set(7,cpu(0));
/* 0028cb8c: move a2,v0 */ set(6,cpu(2));
/* 0028cb90: sll t0,s0,0x3 */ set(8,sx((uint32_t)cpu(16)<<3));
/* 0028cb94: subu a1,t0,s0 */ set(5,sx((uint32_t)cpu(8)-(uint32_t)cpu(16)));
/* 0028cb98: sll v0,a2,0x3 */ set(2,sx((uint32_t)cpu(6)<<3));
/* 0028cb9c: sll v1,a1,0x4 */ set(3,sx((uint32_t)cpu(5)<<4));
/* 0028cba0: sll a0,a2,0x4 */ set(4,sx((uint32_t)cpu(6)<<4));
/* 0028cba4: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 0028cba8: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
/* 0028cbac: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0028cbb0: li a0,0xb */ set(4,sx(UINT32_C(0x0000000b)));
/* 0028cbb4: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0028cbb8: sll a1,a2,0x1 */ set(5,sx((uint32_t)cpu(6)<<1));
/* 0028cbbc: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0028cbc0: lui v1,0x3c */ set(3,sx(UINT32_C(0x003c0000)));
/* 0028cbc4: addiu v1,v1,-0x5206 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffadfa)));
/* 0028cbc8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0028cbcc: nop  */ 
L_0028cbd0:;
/* 0028cbd0: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 0028cbd4: addiu v1,v1,0x8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 0028cbd8: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 0028cbdc: nop  */ 
/* 0028cbe0: nop  */ 
/* 0028cbe4: bgez a0,0x0028cbd0 */ {int taken=((int64_t)cpu(4)>=0);/* delay 0028cbe8 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));if(taken){goto L_0028cbd0;}}
/* 0028cbec: beq a3,zero,0x0028cc88 */ {int taken=(cpu(7)==cpu(0));/* delay 0028cbf0 */ set(2,cpu(0));if(taken){goto L_0028cc88;}}
/* 0028cbf4: lw v1,-0x2c50(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd3b0)));
/* 0028cbf8: bgtz v1,0x0028cc88 */ {int taken=((int64_t)cpu(3)>0);/* delay 0028cbfc */ set(2,cpu(3));if(taken){goto L_0028cc88;}}
/* 0028cc00: subu a0,t0,s0 */ set(4,sx((uint32_t)cpu(8)-(uint32_t)cpu(16)));
/* 0028cc04: addu v1,a1,a2 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(6)));
/* 0028cc08: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 0028cc0c: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 0028cc10: addu v1,v1,a2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
/* 0028cc14: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0028cc18: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0028cc1c: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 0028cc20: lui a0,0x3c */ set(4,sx(UINT32_C(0x003c0000)));
/* 0028cc24: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0028cc28: addiu a0,a0,-0x5220 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffade0)));
/* 0028cc2c: beql v1,zero,0x0028cc34 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0028cc30 */ nocturneFieldMovementTrap(7u,UINT32_C(0x0028cc30));goto L_0028cc34;}}
L_0028cc34:;
/* 0028cc34: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0028cc38: move a0,zero */ set(4,cpu(0));
/* 0028cc3c: lw a1,0x14(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000014)));
/* 0028cc40: lw s0,-0x4254(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffbdac)));
/* 0028cc44: sll v0,a1,0x1 */ set(2,sx((uint32_t)cpu(5)<<1));
/* 0028cc48: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0028cc4c: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 0028cc50: div v0,v1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(3),1,0);
/* 0028cc54: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0028cc58: subu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(2)));
/* 0028cc5c: sll a1,s0,0x1 */ set(5,sx((uint32_t)cpu(16)<<1));
/* 0028cc60: jal 0x002c0c60 */ set(31,UINT64_C(0x0028cc68));/* delay 0028cc64 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffe0)));nocturneFieldMovementCall(UINT32_C(0x002c0c60),UINT32_C(0x0028cc60));
/* 0028cc68: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 0028cc6c: addiu v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));
/* 0028cc70: addiu a0,a0,0x5ba0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00005ba0)));
/* 0028cc74: move a1,v0 */ set(5,cpu(2));
/* 0028cc78: move a2,s0 */ set(6,cpu(16));
/* 0028cc7c: jal 0x002d4748 */ set(31,UINT64_C(0x0028cc84));/* delay 0028cc80 */ sw(ea(28,(int32_t)UINT32_C(0xffffd3b0)),(uint32_t)cpu(2));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x0028cc7c));
/* 0028cc84: lw v0,-0x2c50(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd3b0)));
L_0028cc88:;
/* 0028cc88: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028cc8c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0028cc90: jr ra */ {uint64_t target=cpu(31);/* delay 0028cc94 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0028c9f0(void){
uint64_t incoming=cpu(31);
/* 0028c9f0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0028c9f4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0028c9f8: move s1,a0 */ set(17,cpu(4));
/* 0028c9fc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0028ca00: sll s2,s1,0x3 */ set(18,sx((uint32_t)cpu(17)<<3));
/* 0028ca04: subu v0,s2,s1 */ set(2,sx((uint32_t)cpu(18)-(uint32_t)cpu(17)));
/* 0028ca08: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028ca0c: sll v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)<<4));
/* 0028ca10: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0028ca14: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 0028ca18: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0028ca1c: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0028ca20: lui s0,0x3c */ set(16,sx(UINT32_C(0x003c0000)));
/* 0028ca24: addiu s0,s0,-0x5220 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffade0)));
/* 0028ca28: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 0028ca2c: lhu v0,0x6(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 0028ca30: beq v0,zero,0x0028ca60 */ {int taken=(cpu(2)==cpu(0));/* delay 0028ca34 */ set(19,sx(UINT32_C(0x003c0000)));if(taken){goto L_0028ca60;}}
/* 0028ca38: jal 0x001e9998 */ set(31,UINT64_C(0x0028ca40));/* delay 0028ca3c */ body_001e9998();
/* 0028ca40: lhu v1,0x6(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 0028ca44: srav v1,v1,v0 */ set(3,sx((uint32_t)((int32_t)(uint32_t)cpu(3)>>((uint32_t)cpu(2)&31u))));
/* 0028ca48: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 0028ca4c: beq v1,zero,0x0028ca64 */ {int taken=(cpu(3)==cpu(0));/* delay 0028ca50 */ set(3,sx((uint32_t)cpu(18)-(uint32_t)cpu(17)));if(taken){goto L_0028ca64;}}
/* 0028ca54: b 0x0028cb48 */ /* delay 0028ca58 */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000008))));goto L_0028cb48;
L_0028ca60:;
/* 0028ca60: subu v1,s2,s1 */ set(3,sx((uint32_t)cpu(18)-(uint32_t)cpu(17)));
L_0028ca64:;
/* 0028ca64: addiu a0,s3,-0x5220 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffade0)));
/* 0028ca68: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 0028ca6c: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 0028ca70: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0028ca74: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0028ca78: lhu v1,0xa(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x0000000a))));
/* 0028ca7c: beq v1,zero,0x0028ca90 */ {int taken=(cpu(3)==cpu(0));/* delay 0028ca80 */ set(16,cpu(0));if(taken){goto L_0028ca90;}}
/* 0028ca84: jal 0x001e0f50 */ set(31,UINT64_C(0x0028ca8c));/* delay 0028ca88 */ set(4,cpu(3));body_001e0f50();
/* 0028ca8c: move s0,v0 */ set(16,cpu(2));
L_0028ca90:;
/* 0028ca90: subu v1,s2,s1 */ set(3,sx((uint32_t)cpu(18)-(uint32_t)cpu(17)));
/* 0028ca94: addiu a0,s3,-0x5220 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffade0)));
/* 0028ca98: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 0028ca9c: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 0028caa0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0028caa4: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0028caa8: lhu v1,0xc(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 0028caac: beql v1,zero,0x0028cabc */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0028cab0 */ set(2,cpu(0));goto L_0028cabc;}}
/* 0028cab4: jal 0x001e0f50 */ set(31,UINT64_C(0x0028cabc));/* delay 0028cab8 */ set(4,cpu(3));body_001e0f50();
L_0028cabc:;
/* 0028cabc: bne s0,zero,0x0028cae8 */ {int taken=(cpu(16)!=cpu(0));/* delay 0028cac0 */ if(taken){goto L_0028cae8;}}
/* 0028cac4: bne v0,zero,0x0028cb10 */ {int taken=(cpu(2)!=cpu(0));/* delay 0028cac8 */ set(2,sx((uint32_t)cpu(18)-(uint32_t)cpu(17)));if(taken){goto L_0028cb10;}}
/* 0028cacc: addiu a0,s3,-0x5220 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffade0)));
/* 0028cad0: sll v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)<<4));
/* 0028cad4: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 0028cad8: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0028cadc: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0028cae0: b 0x0028cb48 */ /* delay 0028cae4 */ set(2,byte(ea(3,(int32_t)UINT32_C(0x0000000e))));goto L_0028cb48;
L_0028cae8:;
/* 0028cae8: bne v0,zero,0x0028cb30 */ {int taken=(cpu(2)!=cpu(0));/* delay 0028caec */ set(2,sx((uint32_t)cpu(18)-(uint32_t)cpu(17)));if(taken){goto L_0028cb30;}}
/* 0028caf0: addiu a0,s3,-0x5220 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffade0)));
/* 0028caf4: sll v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)<<4));
/* 0028caf8: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 0028cafc: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0028cb00: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0028cb04: b 0x0028cb48 */ /* delay 0028cb08 */ set(2,byte(ea(3,(int32_t)UINT32_C(0x0000000f))));goto L_0028cb48;
L_0028cb10:;
/* 0028cb10: addiu a0,s3,-0x5220 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffade0)));
/* 0028cb14: sll v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)<<4));
/* 0028cb18: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 0028cb1c: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0028cb20: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0028cb24: b 0x0028cb48 */ /* delay 0028cb28 */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000010))));goto L_0028cb48;
L_0028cb30:;
/* 0028cb30: addiu a0,s3,-0x5220 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffade0)));
/* 0028cb34: sll v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)<<4));
/* 0028cb38: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 0028cb3c: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0028cb40: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0028cb44: lbu v0,0x11(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000011))));
L_0028cb48:;
/* 0028cb48: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028cb4c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0028cb50: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0028cb54: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0028cb58: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0028cb5c: jr ra */ {uint64_t target=cpu(31);/* delay 0028cb60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_0028cfb0(void){
uint64_t incoming=cpu(31);
/* 0028cfb0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028cfb4: sh zero,0x1cf8(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00001cf8)),(uint16_t)cpu(0));
/* 0028cfb8: sw zero,0x1cf4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00001cf4)),(uint32_t)cpu(0));
/* 0028cfbc: jr ra */ {uint64_t target=cpu(31);/* delay 0028cfc0 */ sw(ea(28,(int32_t)UINT32_C(0xffffd3b0)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_0028cee0(void){
uint64_t incoming=cpu(31);
/* 0028cee0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0028cee4: move v0,zero */ set(2,cpu(0));
/* 0028cee8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028ceec: beq a0,zero,0x0028cfa0 */ {int taken=(cpu(4)==cpu(0));/* delay 0028cef0 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_0028cfa0;}}
/* 0028cef4: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 0028cef8: lui v1,0x35 */ set(3,sx(UINT32_C(0x00350000)));
/* 0028cefc: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0028cf00: addiu a3,v1,-0x6840 */ set(7,sx((uint32_t)cpu(3)+UINT32_C(0xffff97c0)));
/* 0028cf04: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0028cf08: move s0,zero */ set(16,cpu(0));
/* 0028cf0c: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 0028cf10: move a1,zero */ set(5,cpu(0));
/* 0028cf14: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0028cf18: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 0028cf1c: lui a0,0x3b */ set(4,sx(UINT32_C(0x003b0000)));
/* 0028cf20: addiu a0,a0,-0x101a */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffefe6)));
/* 0028cf24: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0028cf28: lhu v0,0x0(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 0028cf2c: nop  */ 
L_0028cf30:;
/* 0028cf30: addiu a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));
/* 0028cf34: beq v0,zero,0x0028cf54 */ {int taken=(cpu(2)==cpu(0));/* delay 0028cf38 */ set(3,sx((uint32_t)cpu(2)<<4));if(taken){goto L_0028cf54;}}
/* 0028cf3c: subu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 0028cf40: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0028cf44: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0028cf48: addu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 0028cf4c: lbu v1,0x5(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000005))));
/* 0028cf50: addu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
L_0028cf54:;
/* 0028cf54: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 0028cf58: bgezl a2,0x0028cf30 */ {int taken=((int64_t)cpu(6)>=0);if(taken){/* delay 0028cf5c */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_0028cf30;}}
/* 0028cf60: beq a1,zero,0x0028cfa0 */ {int taken=(cpu(5)==cpu(0));/* delay 0028cf64 */ set(2,cpu(0));if(taken){goto L_0028cfa0;}}
/* 0028cf68: div s0,a1 */ nativeDivide((uint32_t)cpu(16),(uint32_t)cpu(5),1,0);
/* 0028cf6c: beql a1,zero,0x0028cf74 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 0028cf70 */ nocturneFieldMovementTrap(7u,UINT32_C(0x0028cf70));goto L_0028cf74;}}
L_0028cf74:;
/* 0028cf74: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0028cf78: jal 0x00244598 */ set(31,UINT64_C(0x0028cf80));/* delay 0028cf7c */ set(16,cpu(2));body_00244598();
/* 0028cf80: move v1,v0 */ set(3,cpu(2));
/* 0028cf84: addiu a1,v1,0x3 */ set(5,sx((uint32_t)cpu(3)+UINT32_C(0x00000003)));
/* 0028cf88: slti a0,v1,0x0 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 0028cf8c: movn v0,a1,a0 */ if(cpu(4)!=0){set(2,cpu(5));}
/* 0028cf90: sra v0,v0,0x2 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>2)));
/* 0028cf94: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0028cf98: slt v0,v0,v1 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(3));
/* 0028cf9c: sltiu v0,v0,0x1 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_0028cfa0:;
/* 0028cfa0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0028cfa4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0028cfa8: jr ra */ {uint64_t target=cpu(31);/* delay 0028cfac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00244598(void){
uint64_t incoming=cpu(31);
/* 00244598: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024459c: jr ra */ {uint64_t target=cpu(31);/* delay 002445a0 */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000a68))));checkReturn(target,incoming);return;}
}
static void body_00244a38(void){
uint64_t incoming=cpu(31);
/* 00244a38: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00244a3c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00244a40: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00244a44: move s6,a0 */ set(22,cpu(4));
/* 00244a48: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00244a4c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00244a50: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00244a54: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00244a58: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00244a5c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00244a60: bne s6,v0,0x00244b08 */ {int taken=(cpu(22)!=cpu(2));/* delay 00244a64 */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));if(taken){goto L_00244b08;}}
/* 00244a68: li s4,0x64 */ set(20,sx(UINT32_C(0x00000064)));
/* 00244a6c: li s5,0x1 */ set(21,sx(UINT32_C(0x00000001)));
/* 00244a70: li s2,0xa50 */ set(18,sx(UINT32_C(0x00000a50)));
/* 00244a74: li s3,0xf */ set(19,sx(UINT32_C(0x0000000f)));
L_00244a78:;
/* 00244a78: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244a7c: addu a0,v1,s2 */ set(4,sx((uint32_t)cpu(3)+(uint32_t)cpu(18)));
/* 00244a80: move v1,a0 */ set(3,cpu(4));
/* 00244a84: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 00244a88: andi v0,v0,0x2 */ set(2,cpu(2)&UINT32_C(0x00000002));
/* 00244a8c: beql v0,zero,0x00244b00 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00244a90 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));goto L_00244b00;}}
/* 00244a94: lhu v0,0x12(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000012))));
/* 00244a98: andi v0,v0,0x40 */ set(2,cpu(2)&UINT32_C(0x00000040));
/* 00244a9c: beql v0,zero,0x00244b00 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00244aa0 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));goto L_00244b00;}}
/* 00244aa4: lhu v0,0xa(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000000a))));
/* 00244aa8: beq v0,zero,0x00244afc */ {int taken=(cpu(2)==cpu(0));/* delay 00244aac */ set(17,cpu(2));if(taken){goto L_00244afc;}}
/* 00244ab0: li a0,0xaf2 */ set(4,sx(UINT32_C(0x00000af2)));
/* 00244ab4: sll v0,s1,0x1 */ set(2,sx((uint32_t)cpu(17)<<1));
/* 00244ab8: beql s4,zero,0x00244ac0 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00244abc */ nocturneFieldMovementTrap(7u,UINT32_C(0x00244abc));goto L_00244ac0;}}
L_00244ac0:;
/* 00244ac0: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 00244ac4: div v0,s4 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(20),1,0);
/* 00244ac8: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00244acc: jal 0x001e0f50 */ set(31,UINT64_C(0x00244ad4));/* delay 00244ad0 */ set(16,cpu(2));body_001e0f50();
/* 00244ad4: bne v0,zero,0x00244ae0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00244ad8 */ set(3,sx((uint32_t)cpu(16)<<1));if(taken){goto L_00244ae0;}}
/* 00244adc: addu s0,v1,s0 */ set(16,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
L_00244ae0:;
/* 00244ae0: movz s0,s5,s0 */ if(cpu(16)==0){set(16,cpu(21));}
/* 00244ae4: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244ae8: subu s1,s1,s0 */ set(17,sx((uint32_t)cpu(17)-(uint32_t)cpu(16)));
/* 00244aec: slt v1,zero,s1 */ set(3,(int64_t)cpu(0)<(int64_t)cpu(17));
/* 00244af0: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00244af4: movz s1,s5,v1 */ if(cpu(3)==0){set(17,cpu(21));}
/* 00244af8: sh s1,0xa(v0) */ sh(ea(2,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(17));
L_00244afc:;
/* 00244afc: addiu s3,s3,-0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));
L_00244b00:;
/* 00244b00: bgez s3,0x00244a78 */ {int taken=((int64_t)cpu(19)>=0);/* delay 00244b04 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x000000ec)));if(taken){goto L_00244a78;}}
L_00244b08:;
/* 00244b08: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00244b0c: bne s6,v0,0x00244ba8 */ {int taken=(cpu(22)!=cpu(2));/* delay 00244b10 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00244ba8;}}
/* 00244b14: li s4,0x64 */ set(20,sx(UINT32_C(0x00000064)));
/* 00244b18: li s5,0x1 */ set(21,sx(UINT32_C(0x00000001)));
/* 00244b1c: li s2,0xa50 */ set(18,sx(UINT32_C(0x00000a50)));
/* 00244b20: li s3,0xf */ set(19,sx(UINT32_C(0x0000000f)));
/* 00244b24: nop  */ 
L_00244b28:;
/* 00244b28: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244b2c: addu a0,v0,s2 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00244b30: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 00244b34: andi v1,v1,0x2 */ set(3,cpu(3)&UINT32_C(0x00000002));
/* 00244b38: beq v1,zero,0x00244b98 */ {int taken=(cpu(3)==cpu(0));/* delay 00244b3c */ set(5,cpu(4));if(taken){goto L_00244b98;}}
/* 00244b40: lhu v0,0xa(a1) */ set(2,half(ea(5,(int32_t)UINT32_C(0x0000000a))));
/* 00244b44: beq v0,zero,0x00244b98 */ {int taken=(cpu(2)==cpu(0));/* delay 00244b48 */ set(17,cpu(2));if(taken){goto L_00244b98;}}
/* 00244b4c: li a0,0xaf2 */ set(4,sx(UINT32_C(0x00000af2)));
/* 00244b50: sll v0,s1,0x1 */ set(2,sx((uint32_t)cpu(17)<<1));
/* 00244b54: beql s4,zero,0x00244b5c */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00244b58 */ nocturneFieldMovementTrap(7u,UINT32_C(0x00244b58));goto L_00244b5c;}}
L_00244b5c:;
/* 00244b5c: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 00244b60: div v0,s4 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(20),1,0);
/* 00244b64: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00244b68: jal 0x001e0f50 */ set(31,UINT64_C(0x00244b70));/* delay 00244b6c */ set(16,cpu(2));body_001e0f50();
/* 00244b70: bne v0,zero,0x00244b7c */ {int taken=(cpu(2)!=cpu(0));/* delay 00244b74 */ set(3,sx((uint32_t)cpu(16)<<1));if(taken){goto L_00244b7c;}}
/* 00244b78: addu s0,v1,s0 */ set(16,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
L_00244b7c:;
/* 00244b7c: movz s0,s5,s0 */ if(cpu(16)==0){set(16,cpu(21));}
/* 00244b80: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244b84: subu s1,s1,s0 */ set(17,sx((uint32_t)cpu(17)-(uint32_t)cpu(16)));
/* 00244b88: slt v1,zero,s1 */ set(3,(int64_t)cpu(0)<(int64_t)cpu(17));
/* 00244b8c: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00244b90: movz s1,s5,v1 */ if(cpu(3)==0){set(17,cpu(21));}
/* 00244b94: sh s1,0xa(v0) */ sh(ea(2,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(17));
L_00244b98:;
/* 00244b98: addiu s3,s3,-0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));
/* 00244b9c: bgez s3,0x00244b28 */ {int taken=((int64_t)cpu(19)>=0);/* delay 00244ba0 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x000000ec)));if(taken){goto L_00244b28;}}
/* 00244ba4: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
L_00244ba8:;
/* 00244ba8: bne s6,v0,0x00244c38 */ {int taken=(cpu(22)!=cpu(2));/* delay 00244bac */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_00244c38;}}
/* 00244bb0: li s4,0x64 */ set(20,sx(UINT32_C(0x00000064)));
/* 00244bb4: li s5,0x1 */ set(21,sx(UINT32_C(0x00000001)));
/* 00244bb8: li s2,0xa50 */ set(18,sx(UINT32_C(0x00000a50)));
/* 00244bbc: li s3,0xf */ set(19,sx(UINT32_C(0x0000000f)));
L_00244bc0:;
/* 00244bc0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244bc4: addu a0,v0,s2 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00244bc8: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 00244bcc: andi v1,v1,0x2 */ set(3,cpu(3)&UINT32_C(0x00000002));
/* 00244bd0: beq v1,zero,0x00244c28 */ {int taken=(cpu(3)==cpu(0));/* delay 00244bd4 */ set(6,cpu(4));if(taken){goto L_00244c28;}}
/* 00244bd8: lhu v0,0xa(a2) */ set(2,half(ea(6,(int32_t)UINT32_C(0x0000000a))));
/* 00244bdc: beq v0,zero,0x00244c28 */ {int taken=(cpu(2)==cpu(0));/* delay 00244be0 */ set(4,cpu(0));if(taken){goto L_00244c28;}}
/* 00244be4: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 00244be8: jal 0x002c0c60 */ set(31,UINT64_C(0x00244bf0));/* delay 00244bec */ set(17,cpu(2));nocturneFieldMovementCall(UINT32_C(0x002c0c60),UINT32_C(0x00244be8));
/* 00244bf0: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00244bf4: move s0,s5 */ set(16,cpu(21));
/* 00244bf8: mult v0,s1,v0 */ nativeMultiply(2,(uint32_t)cpu(17),(uint32_t)cpu(2),1,0);
/* 00244bfc: beql s4,zero,0x00244c04 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00244c00 */ nocturneFieldMovementTrap(7u,UINT32_C(0x00244c00));goto L_00244c04;}}
L_00244c04:;
/* 00244c04: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244c08: addu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(18)));
/* 00244c0c: divu v0,s4 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(20),0,0);
/* 00244c10: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00244c14: movn s0,v0,v0 */ if(cpu(2)!=0){set(16,cpu(2));}
/* 00244c18: subu s1,s1,s0 */ set(17,sx((uint32_t)cpu(17)-(uint32_t)cpu(16)));
/* 00244c1c: slt v0,zero,s1 */ set(2,(int64_t)cpu(0)<(int64_t)cpu(17));
/* 00244c20: movz s1,s5,v0 */ if(cpu(2)==0){set(17,cpu(21));}
/* 00244c24: sh s1,0xa(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(17));
L_00244c28:;
/* 00244c28: addiu s3,s3,-0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));
/* 00244c2c: bgez s3,0x00244bc0 */ {int taken=((int64_t)cpu(19)>=0);/* delay 00244c30 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x000000ec)));if(taken){goto L_00244bc0;}}
/* 00244c34: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
L_00244c38:;
/* 00244c38: bne s6,v0,0x00244c9c */ {int taken=(cpu(22)!=cpu(2));/* delay 00244c3c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00244c9c;}}
/* 00244c40: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00244c44: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00244c48: move a1,zero */ set(5,cpu(0));
/* 00244c4c: li s3,0xf */ set(19,sx(UINT32_C(0x0000000f)));
/* 00244c50: addiu v1,v0,0xa50 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000a50)));
/* 00244c54: nop  */ 
L_00244c58:;
/* 00244c58: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 00244c5c: andi v0,v0,0x2 */ set(2,cpu(2)&UINT32_C(0x00000002));
/* 00244c60: beql v0,zero,0x00244c90 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00244c64 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));goto L_00244c90;}}
/* 00244c68: lhu v0,0xa(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000a))));
/* 00244c6c: beq v0,zero,0x00244c8c */ {int taken=(cpu(2)==cpu(0));/* delay 00244c70 */ set(17,cpu(2));if(taken){goto L_00244c8c;}}
/* 00244c74: srl s0,s1,0x1 */ set(16,sx((uint32_t)cpu(17)>>1));
/* 00244c78: movz s0,a0,s0 */ if(cpu(16)==0){set(16,cpu(4));}
/* 00244c7c: subu s1,s1,s0 */ set(17,sx((uint32_t)cpu(17)-(uint32_t)cpu(16)));
/* 00244c80: slt v0,a1,s1 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(17));
/* 00244c84: movz s1,a0,v0 */ if(cpu(2)==0){set(17,cpu(4));}
/* 00244c88: sh s1,0xa(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(17));
L_00244c8c:;
/* 00244c8c: addiu s3,s3,-0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));
L_00244c90:;
/* 00244c90: bgez s3,0x00244c58 */ {int taken=((int64_t)cpu(19)>=0);/* delay 00244c94 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ec)));if(taken){goto L_00244c58;}}
/* 00244c98: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00244c9c:;
/* 00244c9c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00244ca0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00244ca4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00244ca8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00244cac: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00244cb0: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00244cb4: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00244cb8: jr ra */ {uint64_t target=cpu(31);/* delay 00244cbc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002456d0(void){
uint64_t incoming=cpu(31);
/* 002456d0: lui v0,0x3e */ set(2,sx(UINT32_C(0x003e0000)));
/* 002456d4: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002456d8: lw a0,-0x36e0(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0xffffc920)));
/* 002456dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002456e0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002456e4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002456e8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002456ec: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002456f0: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002456f4: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002456f8: beq a0,zero,0x00245718 */ {int taken=(cpu(4)==cpu(0));/* delay 002456fc */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));if(taken){goto L_00245718;}}
/* 00245700: jal 0x001e0f50 */ set(31,UINT64_C(0x00245708));/* delay 00245704 */ body_001e0f50();
/* 00245708: bne v0,zero,0x0024571c */ {int taken=(cpu(2)!=cpu(0));/* delay 0024570c */ set(21,cpu(0));if(taken){goto L_0024571c;}}
/* 00245710: b 0x002457c8 */ /* delay 00245714 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002457c8;
L_00245718:;
/* 00245718: move s5,zero */ set(21,cpu(0));
L_0024571c:;
/* 0024571c: li s4,0x64 */ set(20,sx(UINT32_C(0x00000064)));
/* 00245720: lui s6,0x54 */ set(22,sx(UINT32_C(0x00540000)));
/* 00245724: move s3,zero */ set(19,cpu(0));
/* 00245728: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0024572c: nop  */ 
L_00245730:;
/* 00245730: addu v1,v1,s3 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(19)));
/* 00245734: addiu s1,v1,0xa54 */ set(17,sx((uint32_t)cpu(3)+UINT32_C(0x00000a54)));
/* 00245738: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0024573c: andi v1,v0,0x2 */ set(3,cpu(2)&UINT32_C(0x00000002));
/* 00245740: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 00245744: beq v0,zero,0x002457b0 */ {int taken=(cpu(2)==cpu(0));/* delay 00245748 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x000000ec)));if(taken){goto L_002457b0;}}
/* 0024574c: beq v1,zero,0x002457b0 */ {int taken=(cpu(3)==cpu(0));/* delay 00245750 */ set(4,cpu(17));if(taken){goto L_002457b0;}}
/* 00245754: lb v0,0x1b(s1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001b))));
/* 00245758: li a1,0x161 */ set(5,sx(UINT32_C(0x00000161)));
/* 0024575c: beql s4,zero,0x00245764 */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 00245760 */ nocturneFieldMovementTrap(7u,UINT32_C(0x00245760));goto L_00245764;}}
L_00245764:;
/* 00245764: sll v0,v0,0x7 */ set(2,sx((uint32_t)cpu(2)<<7));
/* 00245768: div v0,s4 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(20),1,0);
/* 0024576c: mflo s2 */ set(18,nocturneEffectHostLo());
/* 00245770: jal 0x00243f40 */ set(31,UINT64_C(0x00245778));/* delay 00245774 */ body_00243f40();
/* 00245778: move a0,zero */ set(4,cpu(0));
/* 0024577c: beq v0,zero,0x002457b0 */ {int taken=(cpu(2)==cpu(0));/* delay 00245780 */ set(5,sx(UINT32_C(0x00000020)));if(taken){goto L_002457b0;}}
/* 00245784: jal 0x002c0c60 */ set(31,UINT64_C(0x0024578c));/* delay 00245788 */ nocturneFieldMovementCall(UINT32_C(0x002c0c60),UINT32_C(0x00245784));
/* 0024578c: lhu a1,0x4(s1) */ set(5,half(ea(17,(int32_t)UINT32_C(0x00000004))));
/* 00245790: move s0,v0 */ set(16,cpu(2));
/* 00245794: addiu a0,s6,0x3158 */ set(4,sx((uint32_t)cpu(22)+UINT32_C(0x00003158)));
/* 00245798: move a3,s0 */ set(7,cpu(16));
/* 0024579c: slt s0,s2,s0 */ set(16,(int64_t)cpu(18)<(int64_t)cpu(16));
/* 002457a0: jal 0x001097e8 */ set(31,UINT64_C(0x002457a8));/* delay 002457a4 */ set(6,cpu(18));nocturneFieldMovementCall(UINT32_C(0x001097e8),UINT32_C(0x002457a0));
/* 002457a8: beql s0,zero,0x002457c4 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 002457ac */ set(2,half(ea(17,(int32_t)UINT32_C(0x00000004))));goto L_002457c4;}}
L_002457b0:;
/* 002457b0: addiu s5,s5,0x1 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000001)));
/* 002457b4: slti v0,s5,0x10 */ set(2,(int64_t)cpu(21)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002457b8: bne v0,zero,0x00245730 */ {int taken=(cpu(2)!=cpu(0));/* delay 002457bc */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_00245730;}}
/* 002457c0: move v0,zero */ set(2,cpu(0));
L_002457c4:;
/* 002457c4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002457c8:;
/* 002457c8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002457cc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002457d0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002457d4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002457d8: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002457dc: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002457e0: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002457e4: jr ra */ {uint64_t target=cpu(31);/* delay 002457e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002455b8(void){
uint64_t incoming=cpu(31);
/* 002455b8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002455bc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002455c0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002455c4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002455c8: li s1,0xf */ set(17,sx(UINT32_C(0x0000000f)));
/* 002455cc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002455d0: move s2,zero */ set(18,cpu(0));
/* 002455d4: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
L_002455d8:;
/* 002455d8: addu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(18)));
/* 002455dc: addiu s0,v1,0xa54 */ set(16,sx((uint32_t)cpu(3)+UINT32_C(0x00000a54)));
/* 002455e0: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002455e4: andi v1,v0,0x2 */ set(3,cpu(2)&UINT32_C(0x00000002));
/* 002455e8: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 002455ec: beq v0,zero,0x00245614 */ {int taken=(cpu(2)==cpu(0));/* delay 002455f0 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x000000ec)));if(taken){goto L_00245614;}}
/* 002455f4: beql v1,zero,0x00245618 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002455f8 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));goto L_00245618;}}
/* 002455fc: li a1,0x15d */ set(5,sx(UINT32_C(0x0000015d)));
/* 00245600: jal 0x00245478 */ set(31,UINT64_C(0x00245608));/* delay 00245604 */ set(4,cpu(16));body_00245478();
/* 00245608: move a0,s0 */ set(4,cpu(16));
/* 0024560c: jal 0x00245478 */ set(31,UINT64_C(0x00245614));/* delay 00245610 */ set(5,sx(UINT32_C(0x0000015e)));body_00245478();
L_00245614:;
/* 00245614: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
L_00245618:;
/* 00245618: bgez s1,0x002455d8 */ {int taken=((int64_t)cpu(17)>=0);/* delay 0024561c */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_002455d8;}}
/* 00245620: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00245624: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00245628: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0024562c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00245630: jr ra */ {uint64_t target=cpu(31);/* delay 00245634 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00245478(void){
uint64_t incoming=cpu(31);
/* 00245478: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0024547c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00245480: move s0,a0 */ set(16,cpu(4));
/* 00245484: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00245488: move s1,a1 */ set(17,cpu(5));
/* 0024548c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00245490: move s2,zero */ set(18,cpu(0));
/* 00245494: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00245498: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0024549c: jal 0x00243f40 */ set(31,UINT64_C(0x002454a4));/* delay 002454a0 */ set(19,cpu(0));body_00243f40();
/* 002454a4: beq v0,zero,0x0024559c */ {int taken=(cpu(2)==cpu(0));/* delay 002454a8 */ set(3,sx(UINT32_C(0x003e0000)));if(taken){goto L_0024559c;}}
/* 002454ac: sll v0,s1,0x3 */ set(2,sx((uint32_t)cpu(17)<<3));
/* 002454b0: addiu v1,v1,-0x3e60 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffc1a0)));
/* 002454b4: addiu v0,v0,-0x900 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffff700)));
/* 002454b8: addiu a3,s1,-0x15a */ set(7,sx((uint32_t)cpu(17)+UINT32_C(0xfffffea6)));
/* 002454bc: addu a1,v1,v0 */ set(5,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002454c0: sltiu a0,a3,0x5 */ set(4,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 002454c4: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 002454c8: lh a2,0x0(v0) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 002454cc: beq a0,zero,0x00245578 */ {int taken=(cpu(4)==cpu(0));/* delay 002454d0 */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000002))));if(taken){goto L_00245578;}}
/* 002454d4: sll v0,a3,0x2 */ set(2,sx((uint32_t)cpu(7)<<2));
/* 002454d8: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002454dc: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002454e0: lw v1,0x3140(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00003140)));
/* 002454e4: jr v1 */ {uint64_t target=cpu(3);/* delay 002454e8 */ switch((uint32_t)target){case UINT32_C(0x002454f0):goto L_002454f0;case UINT32_C(0x00245530):goto L_00245530;case UINT32_C(0x00245558):goto L_00245558;default:abort();}}
L_002454f0:;
/* 002454f0: blez a2,0x00245510 */ {int taken=((int64_t)cpu(6)<=0);/* delay 002454f4 */ if(taken){goto L_00245510;}}
/* 002454f8: lhu v0,0x8(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000008))));
/* 002454fc: beql a2,zero,0x00245504 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 00245500 */ nocturneFieldMovementTrap(7u,UINT32_C(0x00245500));goto L_00245504;}}
L_00245504:;
/* 00245504: div v0,a2 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(6),1,0);
/* 00245508: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024550c: mflo s2 */ set(18,nocturneEffectHostLo());
L_00245510:;
/* 00245510: blez a1,0x00245578 */ {int taken=((int64_t)cpu(5)<=0);/* delay 00245514 */ if(taken){goto L_00245578;}}
/* 00245518: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 0024551c: beql a1,zero,0x00245524 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 00245520 */ nocturneFieldMovementTrap(7u,UINT32_C(0x00245520));goto L_00245524;}}
L_00245524:;
/* 00245524: b 0x00245570 */ /* delay 00245528 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(5),1,0);goto L_00245570;
L_00245530:;
/* 00245530: blez a2,0x00245578 */ {int taken=((int64_t)cpu(6)<=0);/* delay 00245534 */ if(taken){goto L_00245578;}}
/* 00245538: lhu v0,0x8(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000008))));
/* 0024553c: beql a2,zero,0x00245544 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 00245540 */ nocturneFieldMovementTrap(7u,UINT32_C(0x00245540));goto L_00245544;}}
L_00245544:;
/* 00245544: div v0,a2 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(6),1,0);
/* 00245548: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024554c: b 0x00245578 */ /* delay 00245550 */ set(18,cpu(2));goto L_00245578;
L_00245558:;
/* 00245558: blez a2,0x00245578 */ {int taken=((int64_t)cpu(6)<=0);/* delay 0024555c */ if(taken){goto L_00245578;}}
/* 00245560: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 00245564: beql a2,zero,0x0024556c */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 00245568 */ nocturneFieldMovementTrap(7u,UINT32_C(0x00245568));goto L_0024556c;}}
L_0024556c:;
/* 0024556c: div v0,a2 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(6),1,0);
L_00245570:;
/* 00245570: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00245574: move s3,v0 */ set(19,cpu(2));
L_00245578:;
/* 00245578: blez s2,0x00245588 */ {int taken=((int64_t)cpu(18)<=0);/* delay 0024557c */ set(5,cpu(18));if(taken){goto L_00245588;}}
/* 00245580: jal 0x00243e28 */ set(31,UINT64_C(0x00245588));/* delay 00245584 */ set(4,cpu(16));body_00243e28();
L_00245588:;
/* 00245588: blezl s3,0x002455a0 */ {int taken=((int64_t)cpu(19)<=0);if(taken){/* delay 0024558c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002455a0;}}
/* 00245590: move a0,s0 */ set(4,cpu(16));
/* 00245594: jal 0x00243e50 */ set(31,UINT64_C(0x0024559c));/* delay 00245598 */ set(5,cpu(19));body_00243e50();
L_0024559c:;
/* 0024559c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002455a0:;
/* 002455a0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002455a4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002455a8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002455ac: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002455b0: jr ra */ {uint64_t target=cpu(31);/* delay 002455b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00243f40(void){
uint64_t incoming=cpu(31);
/* 00243f40: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00243f44: andi v0,v0,0x20 */ set(2,cpu(2)&UINT32_C(0x00000020));
/* 00243f48: bnel v0,zero,0x00243f98 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00243f4c */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000004))));goto L_00243f98;}}
/* 00243f50: lhu v0,0x38(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000038))));
/* 00243f54: beq v0,zero,0x00243fdc */ {int taken=(cpu(2)==cpu(0));/* delay 00243f58 */ set(6,cpu(0));if(taken){goto L_00243fdc;}}
/* 00243f5c: move a3,v0 */ set(7,cpu(2));
/* 00243f60: addiu a0,a0,0x3a */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000003a)));
/* 00243f64: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
L_00243f68:;
/* 00243f68: addiu a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));
/* 00243f6c: beq v1,a1,0x00243fe0 */ {int taken=(cpu(3)==cpu(5));/* delay 00243f70 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00243fe0;}}
/* 00243f74: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 00243f78: slt v0,a2,a3 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(7));
/* 00243f7c: nop  */ 
/* 00243f80: nop  */ 
/* 00243f84: bnel v0,zero,0x00243f68 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00243f88 */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_00243f68;}}
/* 00243f8c: jr ra */ {uint64_t target=cpu(31);/* delay 00243f90 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_00243f98:;
/* 00243f98: move a2,zero */ set(6,cpu(0));
/* 00243f9c: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 00243fa0: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 00243fa4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00243fa8: lui a0,0x35 */ set(4,sx(UINT32_C(0x00350000)));
/* 00243fac: addiu a0,a0,-0x682a */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffff97d6)));
/* 00243fb0: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 00243fb4: lhu v1,0x0(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));
L_00243fb8:;
/* 00243fb8: addiu a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));
/* 00243fbc: beq v1,a1,0x00243fe0 */ {int taken=(cpu(3)==cpu(5));/* delay 00243fc0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00243fe0;}}
/* 00243fc4: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 00243fc8: slti v0,a2,0x8 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 00243fcc: nop  */ 
/* 00243fd0: nop  */ 
/* 00243fd4: bnel v0,zero,0x00243fb8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00243fd8 */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_00243fb8;}}
L_00243fdc:;
/* 00243fdc: move v0,zero */ set(2,cpu(0));
L_00243fe0:;
/* 00243fe0: jr ra */ {uint64_t target=cpu(31);/* delay 00243fe4 */ checkReturn(target,incoming);return;}
}
static void body_00243e28(void){
uint64_t incoming=cpu(31);
/* 00243e28: lhu v0,0x6(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000006))));
/* 00243e2c: lhu a2,0x8(a0) */ set(6,half(ea(4,(int32_t)UINT32_C(0x00000008))));
/* 00243e30: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 00243e34: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00243e38: movn v0,zero,v1 */ if(cpu(3)!=0){set(2,cpu(0));}
/* 00243e3c: slt a1,a2,v0 */ set(5,(int64_t)cpu(6)<(int64_t)cpu(2));
/* 00243e40: movn v0,a2,a1 */ if(cpu(5)!=0){set(2,cpu(6));}
/* 00243e44: jr ra */ {uint64_t target=cpu(31);/* delay 00243e48 */ sh(ea(4,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_00243e50(void){
uint64_t incoming=cpu(31);
/* 00243e50: lhu v0,0xa(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x0000000a))));
/* 00243e54: lhu a2,0xc(a0) */ set(6,half(ea(4,(int32_t)UINT32_C(0x0000000c))));
/* 00243e58: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 00243e5c: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00243e60: movn v0,zero,v1 */ if(cpu(3)!=0){set(2,cpu(0));}
/* 00243e64: slt a1,a2,v0 */ set(5,(int64_t)cpu(6)<(int64_t)cpu(2));
/* 00243e68: movn v0,a2,a1 */ if(cpu(5)!=0){set(2,cpu(6));}
/* 00243e6c: jr ra */ {uint64_t target=cpu(31);/* delay 00243e70 */ sh(ea(4,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_002c0258(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 002c0258: clear f0 */ f[0]=0;
/* 002c025c: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c0260: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0264: move s1,zero */ set(17,cpu(0));
/* 002c0268: c.lt.S f13,f0 */ (void)(EE_FPU_COMPARE_S(f[13],f[0],1)!=0);
/* 002c026c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0270: bc1f 0x002c0280 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 002c0274 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002c0280;}}
/* 002c0278: neg.S f13,f13 */ f[13u]=f[13u]^UINT32_C(0x80000000);
/* 002c027c: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
L_002c0280:;
/* 002c0280: c.lt.S f12,f0 */ (void)(EE_FPU_COMPARE_S(f[12],f[0],1)!=0);
/* 002c0284: bc1f 0x002c0294 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 002c0288 */ set(16,cpu(0));if(taken){goto L_002c0294;}}
/* 002c028c: neg.S f12,f12 */ f[12u]=f[12u]^UINT32_C(0x80000000);
/* 002c0290: li s0,0x1 */ set(16,sx(UINT32_C(0x00000001)));
L_002c0294:;
/* 002c0294: c.lt.S f12,f13 */ (void)(EE_FPU_COMPARE_S(f[12],f[13],1)!=0);
/* 002c0298: bc1f 0x002c02c0 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 002c029c */ if(taken){goto L_002c02c0;}}
/* 002c02a0: nop  */ 
/* 002c02a4: nop  */ 
/* 002c02a8: div.S f12,f12,f13 */ f[12]=EE_FPU_DIV_S(f[12],f[13]);
/* 002c02ac: jal 0x002c0228 */ set(31,UINT64_C(0x002c02b4));/* delay 002c02b0 */ body_002c0228();
/* 002c02b4: b 0x002c02dc */ /* delay 002c02b8 */ f[1]=f[0];goto L_002c02dc;
L_002c02c0:;
/* 002c02c0: nop  */ 
/* 002c02c4: nop  */ 
/* 002c02c8: div.S f12,f13,f12 */ f[12]=EE_FPU_DIV_S(f[13],f[12]);
/* 002c02cc: jal 0x002c0228 */ set(31,UINT64_C(0x002c02d4));/* delay 002c02d0 */ body_002c0228();
/* 002c02d4: lwc1 f1,-0x59ec(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa614)));
/* 002c02d8: sub.S f1,f1,f0 */ f[1]=EE_FPU_SUB_S(f[1],f[0]);
L_002c02dc:;
/* 002c02dc: beq s1,zero,0x002c02ec */ {int taken=(cpu(17)==cpu(0));/* delay 002c02e0 */ if(taken){goto L_002c02ec;}}
/* 002c02e4: lwc1 f0,-0x59e8(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa618)));
/* 002c02e8: sub.S f1,f0,f1 */ f[1]=EE_FPU_SUB_S(f[0],f[1]);
L_002c02ec:;
/* 002c02ec: bnel s0,zero,0x002c02f4 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 002c02f0 */ f[1u]=f[1u]^UINT32_C(0x80000000);goto L_002c02f4;}}
L_002c02f4:;
/* 002c02f4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c02f8: mov.S f0,f1 */ f[0]=f[1];
/* 002c02fc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0300: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c0304: jr ra */ {uint64_t target=cpu(31);/* delay 002c0308 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002c0228(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 002c0228: mul.S f0,f12,f12 */ f[0]=EE_FPU_MUL_S(f[12],f[12]);
/* 002c022c: lwc1 f2,-0x59f8(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffa608)));
/* 002c0230: lwc1 f1,-0x59f4(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa60c)));
/* 002c0234: mul.S f2,f12,f2 */ f[2]=EE_FPU_MUL_S(f[12],f[2]);
/* 002c0238: lwc1 f3,-0x59f0(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffa610)));
/* 002c023c: mul.S f12,f0,f12 */ f[12]=EE_FPU_MUL_S(f[0],f[12]);
/* 002c0240: mul.S f1,f12,f1 */ f[1]=EE_FPU_MUL_S(f[12],f[1]);
/* 002c0244: mul.S f0,f0,f12 */ f[0]=EE_FPU_MUL_S(f[0],f[12]);
/* 002c0248: add.S f2,f2,f1 */ f[2]=EE_FPU_ADD_S(f[2],f[1]);
/* 002c024c: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 002c0250: jr ra */ {uint64_t target=cpu(31);/* delay 002c0254 */ f[0]=EE_FPU_ADD_S(f[2],f[0]);checkReturn(target,incoming);return;}
}
static void body_002c0b60(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 002c0b60: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c0b64: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0b68: jal 0x002c0600 */ set(31,UINT64_C(0x002c0b70));/* delay 002c0b6c */ nocturneFieldMovementCall(UINT32_C(0x002c0600),UINT32_C(0x002c0b68));
/* 002c0b70: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002c0b74: addiu v0,v0,-0x69e0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff9620)));
/* 002c0b78: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002c0b7c: vmulax.xyzw ACC,vf28,vf10 */ constructorMac(32u,28u,10u,0u,0u);
/* 002c0b80: vmadday.xyzw ACC,vf29,vf10 */ constructorMac(32u,29u,10u,1u,1u);
/* 002c0b84: vmaddz.xyzw vf10,vf30,vf10 */ constructorMac(10u,30u,10u,2u,1u);
/* 002c0b88: qmfc2 v0,vf10 */ qmf(2u,10u);
/* 002c0b8c: pexew v0,v0 */ constructorPexew(2u,2u);
/* 002c0b90: mtc1 v0,f12 */ f[12]=(uint32_t)cpu(2);
/* 002c0b94: qmfc2 v0,vf10 */ qmf(2u,10u);
/* 002c0b98: mtc1 v0,f13 */ f[13]=(uint32_t)cpu(2);
/* 002c0b9c: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0ba0: j 0x002c0258 */ /* delay 002c0ba4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002c0258();return;
}
static void body_001e9998(void){
uint64_t incoming=cpu(31);
/* 001e9998: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e999c: lbu v0,0xa41(v0) */ set(2,byte(ea(2,(int32_t)UINT32_C(0x00000a41))));
/* 001e99a0: slti v1,v0,0x9 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 001e99a4: bne v1,zero,0x001e99b4 */ {int taken=(cpu(3)!=cpu(0));/* delay 001e99a8 */ set(4,cpu(2)&UINT32_C(0x00000007));if(taken){goto L_001e99b4;}}
/* 001e99ac: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 001e99b0: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
L_001e99b4:;
/* 001e99b4: jr ra */ {uint64_t target=cpu(31);/* delay 001e99b8 */ checkReturn(target,incoming);return;}
}
static void body_001e99c0(void){
uint64_t incoming=cpu(31);
/* 001e99c0: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e99c4: jr ra */ {uint64_t target=cpu(31);/* delay 001e99c8 */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000a41))));checkReturn(target,incoming);return;}
}
static void body_001e99d0(void){
uint64_t incoming=cpu(31);
/* 001e99d0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e99d4: andi a0,a0,0xf */ set(4,cpu(4)&UINT32_C(0x0000000f));
/* 001e99d8: sb a0,0xa41(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000a41)),(uint8_t)cpu(4));
/* 001e99dc: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e99e0: jr ra */ {uint64_t target=cpu(31);/* delay 001e99e4 */ sw(ea(3,(int32_t)UINT32_C(0x00000a44)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_001e0f50(void){
uint64_t incoming=cpu(31);
/* 001e0f50: slti v0,a0,0x0 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001e0f54: addiu a1,a0,0x1f */ set(5,sx((uint32_t)cpu(4)+UINT32_C(0x0000001f)));
/* 001e0f58: move v1,a0 */ set(3,cpu(4));
/* 001e0f5c: lw a2,-0x5750(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001e0f60: movn v1,a1,v0 */ if(cpu(2)!=0){set(3,cpu(5));}
/* 001e0f64: sra v1,v1,0x5 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>5)));
/* 001e0f68: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001e0f6c: addu v1,v1,a2 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
/* 001e0f70: lw v0,0x840(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000840)));
/* 001e0f74: srav v0,v0,a0 */ set(2,sx((uint32_t)((int32_t)(uint32_t)cpu(2)>>((uint32_t)cpu(4)&31u))));
/* 001e0f78: jr ra */ {uint64_t target=cpu(31);/* delay 001e0f7c */ set(2,cpu(2)&UINT32_C(0x00000001));checkReturn(target,incoming);return;}
}
static void body_00125990(void){
uint64_t incoming=cpu(31);
/* 00125990: addiu v1,gp,-0x55f0 */ set(3,sx((uint32_t)cpu(28)+UINT32_C(0xffffaa10)));
/* 00125994: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00125998: or v0,v0,a0 */ set(2,cpu(2)|cpu(4));
/* 0012599c: jr ra */ {uint64_t target=cpu(31);/* delay 001259a0 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_001259c0(void){
uint64_t incoming=cpu(31);
/* 001259c0: lw v0,-0x55f0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffaa10)));
/* 001259c4: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 001259c8: jr ra */ {uint64_t target=cpu(31);/* delay 001259cc */ set(2,cpu(0)<cpu(2));checkReturn(target,incoming);return;}
}
static void body_001259e0(void){
uint64_t incoming=cpu(31);
/* 001259e0: lw v0,-0x55e8(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffaa18)));
/* 001259e4: nor a0,zero,a0 */ set(4,~(cpu(0)|cpu(4)));
/* 001259e8: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 001259ec: jr ra */ {uint64_t target=cpu(31);/* delay 001259f0 */ sw(ea(28,(int32_t)UINT32_C(0xffffaa18)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_001259f8(void){
uint64_t incoming=cpu(31);
/* 001259f8: lw v0,-0x55e8(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffaa18)));
/* 001259fc: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 00125a00: jr ra */ {uint64_t target=cpu(31);/* delay 00125a04 */ set(2,cpu(0)<cpu(2));checkReturn(target,incoming);return;}
}
static void body_001225e8(void){
uint64_t incoming=cpu(31);
/* 001225e8: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 001225ec: jr ra */ {uint64_t target=cpu(31);/* delay 001225f0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffc350)));checkReturn(target,incoming);return;}
}
static void body_00122718(void){
uint64_t incoming=cpu(31);
/* 00122718: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0012271c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00122720: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00122724: jal 0x001225e8 */ set(31,UINT64_C(0x0012272c));/* delay 00122728 */ body_001225e8();
/* 0012272c: move s0,v0 */ set(16,cpu(2));
/* 00122730: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00122734: beq v0,zero,0x00122750 */ {int taken=(cpu(2)==cpu(0));/* delay 00122738 */ set(4,sx(UINT32_C(0x00000040)));if(taken){goto L_00122750;}}
/* 0012273c: jal 0x001259e0 */ set(31,UINT64_C(0x00122744));/* delay 00122740 */ body_001259e0();
/* 00122744: move a1,zero */ set(5,cpu(0));
/* 00122748: jal 0x001121d8 */ set(31,UINT64_C(0x00122750));/* delay 0012274c */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));body_001121d8();
L_00122750:;
/* 00122750: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00122754: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 00122758: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0012275c: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 00122760: sw v0,-0x4024(v1) */ sw(ea(3,(int32_t)UINT32_C(0xffffbfdc)),(uint32_t)cpu(2));
/* 00122764: jr ra */ {uint64_t target=cpu(31);/* delay 00122768 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0010ddf0(void){
uint64_t incoming=cpu(31);
/* 0010ddf0: lw v0,0xc0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x000000c0)));
/* 0010ddf4: or v0,v0,a1 */ set(2,cpu(2)|cpu(5));
/* 0010ddf8: jr ra */ {uint64_t target=cpu(31);/* delay 0010ddfc */ sw(ea(4,(int32_t)UINT32_C(0x000000c0)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_0010df38(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0010df38: lw v0,0x1c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 0010df3c: addiu v0,v0,0x40 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000040)));
/* 0010df40: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0010df44: vmove.w vf10,vf0 */ constructorMoveW(10u,0u);
/* 0010df48: jr ra */ {uint64_t target=cpu(31);/* delay 0010df4c */ checkReturn(target,incoming);return;}
}
static void body_0010df50(void){
uint64_t incoming=cpu(31);
/* 0010df50: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0010df54: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010df58: lw v0,0x1c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 0010df5c: addiu v0,v0,0x50 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000050)));
/* 0010df60: lqc2 vf10,0x0(v0) */ loadVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0010df64: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010df68: j 0x002c04e8 */ /* delay 0010df6c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneFieldMovementCall(UINT32_C(0x002c04e8),UINT32_C(0x0010df68));return;
}
static void body_00110350(void){
uint64_t incoming=cpu(31);
/* 00110350: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00110354: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110358: jal 0x001122a0 */ set(31,UINT64_C(0x00110360));/* delay 0011035c */ body_001122a0();
/* 00110360: lw v0,0xc(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 00110364: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110368: jr ra */ {uint64_t target=cpu(31);/* delay 0011036c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00110138(void){
uint64_t incoming=cpu(31);
/* 00110138: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0011013c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110140: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00110144: jal 0x001122a0 */ set(31,UINT64_C(0x0011014c));/* delay 00110148 */ set(16,cpu(5));body_001122a0();
/* 0011014c: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00110150: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00110154: or v1,v1,s0 */ set(3,cpu(3)|cpu(16));
/* 00110158: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0011015c: sw v1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 00110160: jr ra */ {uint64_t target=cpu(31);/* delay 00110164 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00109f08(void){
uint64_t incoming=cpu(31);
/* 00109f08: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00109f0c: lw a1,-0x57dc(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa824)));
/* 00109f10: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00109f14: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109f18: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00109f1c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00109f20: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00109f24: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00109f28: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00109f2c: jal 0x002d4748 */ set(31,UINT64_C(0x00109f34));/* delay 00109f30 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffe2e0)));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x00109f2c));
/* 00109f34: lw s0,-0x57d8(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa828)));
/* 00109f38: beq s0,zero,0x00109fa4 */ {int taken=(cpu(16)==cpu(0));/* delay 00109f3c */ set(20,sx(UINT32_C(0x00530000)));if(taken){goto L_00109fa4;}}
/* 00109f40: lui s3,0x53 */ set(19,sx(UINT32_C(0x00530000)));
/* 00109f44: lui s2,0x53 */ set(18,sx(UINT32_C(0x00530000)));
/* 00109f48: addiu a0,s4,-0x1d10 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0xffffe2f0)));
/* 00109f4c: nop  */ 
L_00109f50:;
/* 00109f50: jal 0x002d4748 */ set(31,UINT64_C(0x00109f58));/* delay 00109f54 */ set(5,cpu(16));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x00109f50));
/* 00109f58: addiu a0,s2,-0x1cd8 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0xffffe328)));
/* 00109f5c: lw v0,0xe4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x000000e4)));
/* 00109f60: beq v0,zero,0x00109f88 */ {int taken=(cpu(2)==cpu(0));/* delay 00109f64 */ lw(17,ea(16,(int32_t)UINT32_C(0x000000ec)));if(taken){goto L_00109f88;}}
/* 00109f68: jal 0x002d4748 */ set(31,UINT64_C(0x00109f70));/* delay 00109f6c */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffe310)));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x00109f68));
/* 00109f70: lw a0,0xe4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000e4)));
/* 00109f74: jal 0x00101738 */ set(31,UINT64_C(0x00109f7c));/* delay 00109f78 */ set(5,cpu(0));nocturneFieldMovementCall(UINT32_C(0x00101738),UINT32_C(0x00109f74));
/* 00109f7c: b 0x00109f9c */ /* delay 00109f80 */ set(16,cpu(17));goto L_00109f9c;
L_00109f88:;
/* 00109f88: jal 0x002d4748 */ set(31,UINT64_C(0x00109f90));/* delay 00109f8c */ nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x00109f88));
/* 00109f90: jal 0x00109e50 */ set(31,UINT64_C(0x00109f98));/* delay 00109f94 */ set(4,cpu(16));nocturneFieldMovementCall(UINT32_C(0x00109e50),UINT32_C(0x00109f90));
/* 00109f98: move s0,s1 */ set(16,cpu(17));
L_00109f9c:;
/* 00109f9c: bne s0,zero,0x00109f50 */ {int taken=(cpu(16)!=cpu(0));/* delay 00109fa0 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0xffffe2f0)));if(taken){goto L_00109f50;}}
L_00109fa4:;
/* 00109fa4: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00109fa8: lw a1,-0x57dc(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa824)));
/* 00109fac: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109fb0: addiu a0,a0,-0x1cc0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffe340)));
/* 00109fb4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00109fb8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00109fbc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00109fc0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00109fc4: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00109fc8: j 0x002d4748 */ /* delay 00109fcc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x00109fc8));return;
}
static void body_0010a078(void){
uint64_t incoming=cpu(31);
/* 0010a078: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010a07c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010a080: lw s0,-0x57d8(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa828)));
/* 0010a084: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010a088: move s1,a0 */ set(17,cpu(4));
/* 0010a08c: beq s0,zero,0x0010a0b8 */ {int taken=(cpu(16)==cpu(0));/* delay 0010a090 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_0010a0b8;}}
/* 0010a094: move a1,s0 */ set(5,cpu(16));
L_0010a098:;
/* 0010a098: jal 0x002d5ab4 */ set(31,UINT64_C(0x0010a0a0));/* delay 0010a09c */ set(4,cpu(17));nocturneFieldMovementCall(UINT32_C(0x002d5ab4),UINT32_C(0x0010a098));
/* 0010a0a0: bnel v0,zero,0x0010a0b0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0010a0a4 */ lw(16,ea(16,(int32_t)UINT32_C(0x000000ec)));goto L_0010a0b0;}}
/* 0010a0a8: b 0x0010a0bc */ /* delay 0010a0ac */ set(2,cpu(16));goto L_0010a0bc;
L_0010a0b0:;
/* 0010a0b0: bne s0,zero,0x0010a098 */ {int taken=(cpu(16)!=cpu(0));/* delay 0010a0b4 */ set(5,cpu(16));if(taken){goto L_0010a098;}}
L_0010a0b8:;
/* 0010a0b8: move v0,zero */ set(2,cpu(0));
L_0010a0bc:;
/* 0010a0bc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010a0c0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010a0c4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010a0c8: jr ra */ {uint64_t target=cpu(31);/* delay 0010a0cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00104fe0(void){
uint64_t incoming=cpu(31);
/* 00104fe0: addiu v1,gp,-0x57f8 */ set(3,sx((uint32_t)cpu(28)+UINT32_C(0xffffa808)));
/* 00104fe4: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00104fe8: addiu t0,v1,0x3 */ set(8,sx((uint32_t)cpu(3)+UINT32_C(0x00000003)));
/* 00104fec: li v0,-0x80 */ set(2,sx(UINT32_C(0xffffff80)));
/* 00104ff0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00104ff4: sb v0,0x0(t0) */ sb(ea(8,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 00104ff8: sb a0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));
/* 00104ffc: sb a1,0x1(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(5));
/* 00105000: bne a3,zero,0x00105020 */ {int taken=(cpu(7)!=cpu(0));/* delay 00105004 */ sb(ea(3,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(6));if(taken){goto L_00105020;}}
/* 00105008: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010500c: sb zero,0x0(t0) */ sb(ea(8,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 00105010: sh zero,-0x25b8(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffda48)),(uint16_t)cpu(0));
/* 00105014: sh zero,-0x25b6(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffda4a)),(uint16_t)cpu(0));
/* 00105018: j 0x00104f78 */ /* delay 0010501c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00104f78();return;
L_00105020:;
/* 00105020: lw v0,-0x5814(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa7ec)));
/* 00105024: li v1,-0x3 */ set(3,sx(UINT32_C(0xfffffffd)));
/* 00105028: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010502c: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 00105030: sh a3,-0x25b8(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffda48)),(uint16_t)cpu(7));
/* 00105034: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 00105038: sh a3,-0x25b6(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffda4a)),(uint16_t)cpu(7));
/* 0010503c: sw v0,-0x5814(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa7ec)),(uint32_t)cpu(2));
/* 00105040: jr ra */ {uint64_t target=cpu(31);/* delay 00105044 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00104f78(void){
uint64_t incoming=cpu(31);
/* 00104f78: lw v0,-0x5814(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa7ec)));
/* 00104f7c: li a0,-0x4 */ set(4,sx(UINT32_C(0xfffffffc)));
/* 00104f80: addiu v1,gp,-0x57f8 */ set(3,sx((uint32_t)cpu(28)+UINT32_C(0xffffa808)));
/* 00104f84: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 00104f88: sb zero,0x3(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(0));
/* 00104f8c: sw v0,-0x5814(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa7ec)),(uint32_t)cpu(2));
/* 00104f90: sb zero,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 00104f94: sb zero,0x1(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));
/* 00104f98: jr ra */ {uint64_t target=cpu(31);/* delay 00104f9c */ sb(ea(3,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_0010f208(void){
uint64_t incoming=cpu(31);
/* 0010f208: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0010f20c: sll v0,a2,0x1 */ set(2,sx((uint32_t)cpu(6)<<1));
/* 0010f210: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 0010f214: lw a0,0x8(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0010f218: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0010f21c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0010f220: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0010f224: bnel v1,zero,0x0010f238 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0010f228 */ lw(4,ea(2,(int32_t)UINT32_C(0x00000004)));goto L_0010f238;}}
/* 0010f22c: jr ra */ {uint64_t target=cpu(31);/* delay 0010f230 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_0010f238:;
/* 0010f238: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 0010f23c: nop  */ 
L_0010f240:;
/* 0010f240: beq a1,v1,0x0010f268 */ {int taken=(cpu(5)==cpu(3));/* delay 0010f244 */ set(2,cpu(4));if(taken){goto L_0010f268;}}
/* 0010f248: lw a0,0x20(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 0010f24c: nop  */ 
/* 0010f250: nop  */ 
/* 0010f254: nop  */ 
/* 0010f258: nop  */ 
/* 0010f25c: bnel a0,zero,0x0010f240 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 0010f260 */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));goto L_0010f240;}}
/* 0010f264: move v0,zero */ set(2,cpu(0));
L_0010f268:;
/* 0010f268: jr ra */ {uint64_t target=cpu(31);/* delay 0010f26c */ checkReturn(target,incoming);return;}
}
static void body_001121d8(void){
uint64_t incoming=cpu(31);
/* 001121d8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001121dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001121e0: move s0,a1 */ set(16,cpu(5));
/* 001121e4: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001121e8: jal 0x00110300 */ set(31,UINT64_C(0x001121f0));/* delay 001121ec */ set(5,sx(UINT32_C(0x00000001)));body_00110300();
/* 001121f0: move a0,v0 */ set(4,cpu(2));
/* 001121f4: beq a0,zero,0x00112208 */ {int taken=(cpu(4)==cpu(0));/* delay 001121f8 */ set(5,cpu(16));if(taken){goto L_00112208;}}
/* 001121fc: jal 0x0010fed0 */ set(31,UINT64_C(0x00112204));/* delay 00112200 */ body_0010fed0();
/* 00112204: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_00112208:;
/* 00112208: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0011220c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112210: jr ra */ {uint64_t target=cpu(31);/* delay 00112214 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0010fed0(void){
uint64_t incoming=cpu(31);
/* 0010fed0: lw v0,0x18(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0010fed4: jr ra */ {uint64_t target=cpu(31);/* delay 0010fed8 */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
uint32_t nocturneFieldMovementConstructorBody(uint32_t entry){switch(entry){
case UINT32_C(0x0010dd38):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010dd38();return 1u;case UINT32_C(0x0010de28):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010de28();return 1u;case UINT32_C(0x0010de50):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010de50();return 1u;case UINT32_C(0x0010dea8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010dea8();return 1u;case UINT32_C(0x0010ded8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ded8();return 1u;case UINT32_C(0x0010ffe0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ffe0();return 1u;case UINT32_C(0x0010fc38):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010fc38();return 1u;case UINT32_C(0x0010fe48):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010fe48();return 1u;case UINT32_C(0x00112168):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00112168();return 1u;case UINT32_C(0x00110238):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00110238();return 1u;case UINT32_C(0x00110298):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00110298();return 1u;case UINT32_C(0x00110300):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00110300();return 1u;case UINT32_C(0x001122a0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001122a0();return 1u;case UINT32_C(0x00112a30):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00112a30();return 1u;case UINT32_C(0x0010ff90):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ff90();return 1u;case UINT32_C(0x0010e248):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010e248();return 1u;case UINT32_C(0x0010e690):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010e690();return 1u;case UINT32_C(0x0010e748):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010e748();return 1u;case UINT32_C(0x0010e8e8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010e8e8();return 1u;case UINT32_C(0x0010f270):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010f270();return 1u;case UINT32_C(0x0010ea38):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ea38();return 1u;case UINT32_C(0x0010ea90):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ea90();return 1u;case UINT32_C(0x0010ebe0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ebe0();return 1u;case UINT32_C(0x0010ec20):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ec20();return 1u;case UINT32_C(0x0010ec58):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ec58();return 1u;case UINT32_C(0x0010ec78):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ec78();return 1u;case UINT32_C(0x0010ebc8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ebc8();return 1u;case UINT32_C(0x0010f970):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010f970();return 1u;case UINT32_C(0x0010fab8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010fab8();return 1u;case UINT32_C(0x0010e548):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010e548();return 1u;case UINT32_C(0x0010e588):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010e588();return 1u;case UINT32_C(0x0028cca8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0028cca8();return 1u;case UINT32_C(0x0028cb68):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0028cb68();return 1u;case UINT32_C(0x0028c9f0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0028c9f0();return 1u;case UINT32_C(0x0028cfb0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0028cfb0();return 1u;case UINT32_C(0x0028cee0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0028cee0();return 1u;case UINT32_C(0x00244598):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00244598();return 1u;case UINT32_C(0x00244a38):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00244a38();return 1u;case UINT32_C(0x002456d0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002456d0();return 1u;case UINT32_C(0x002455b8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002455b8();return 1u;case UINT32_C(0x00245478):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00245478();return 1u;case UINT32_C(0x00243f40):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00243f40();return 1u;case UINT32_C(0x00243e28):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00243e28();return 1u;case UINT32_C(0x00243e50):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00243e50();return 1u;case UINT32_C(0x002c0258):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002c0258();return 1u;case UINT32_C(0x002c0228):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002c0228();return 1u;case UINT32_C(0x002c0b60):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002c0b60();return 1u;case UINT32_C(0x001e9998):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001e9998();return 1u;case UINT32_C(0x001e99c0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001e99c0();return 1u;case UINT32_C(0x001e99d0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001e99d0();return 1u;case UINT32_C(0x001e0f50):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001e0f50();return 1u;case UINT32_C(0x00125990):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00125990();return 1u;case UINT32_C(0x001259c0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001259c0();return 1u;case UINT32_C(0x001259e0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001259e0();return 1u;case UINT32_C(0x001259f8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001259f8();return 1u;case UINT32_C(0x001225e8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001225e8();return 1u;case UINT32_C(0x00122718):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00122718();return 1u;case UINT32_C(0x0010ddf0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010ddf0();return 1u;case UINT32_C(0x0010df38):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010df38();return 1u;case UINT32_C(0x0010df50):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010df50();return 1u;case UINT32_C(0x00110350):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00110350();return 1u;case UINT32_C(0x00110138):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00110138();return 1u;case UINT32_C(0x00109f08):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00109f08();return 1u;case UINT32_C(0x0010a078):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010a078();return 1u;case UINT32_C(0x00104fe0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00104fe0();return 1u;case UINT32_C(0x00104f78):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00104f78();return 1u;case UINT32_C(0x0010f208):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010f208();return 1u;case UINT32_C(0x001121d8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001121d8();return 1u;case UINT32_C(0x0010fed0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010fed0();return 1u;
default:return 0u;}}
