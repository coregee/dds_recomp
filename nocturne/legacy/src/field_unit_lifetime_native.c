/* Complete13 unit-lifetime owners and4 existing native factory variants; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "field_unit_lifetime_native.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveFieldUnitLifetimeNativeAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}

static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneFieldUnitLifetimeNativeCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneFieldUnitLifetimeNativeCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneFieldUnitLifetimeNativeCpuWrite(r,q);if(r==29u)nocturneFieldUnitLifetimeNativeSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);

static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}









#include "ee_fpu_sqrt.h"
#include "ee_vu_rotation.h"





static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}
static void loadVu(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a),16);nocturneFieldUnitLifetimeNativeVuWrite(r,q);}
static void storeVu(unsigned r,uint32_t a){uint32_t q[4];nocturneFieldUnitLifetimeNativeVuRead(r,q);memcpy(at(a),q,16);}
static void body_0010dbe0(void);
static void body_0010dcb8(void);
static void body_0010f040(void);
static void body_0010f0e8(void);
static void body_0010f9d8(void);
static void body_0010fb98(void);
static void body_00110070(void);
static void body_00110370(void);
static void body_00111b80(void);
static void body_00112a40(void);
static void body_00112af0(void);
static void body_00112b38(void);
static void body_00112bb0(void);
static void body_001130d0(void);
static void body_00115bc8(void);
static void body_001e3548(void);
static void body_001e39e8(void);
static void body_0010dbe0(void){
uint64_t incoming=cpu(31);
/* 0010dbe0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010dbe4: move v0,zero */ set(2,cpu(0));
/* 0010dbe8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010dbec: move s1,a0 */ set(17,cpu(4));
/* 0010dbf0: sltiu v1,s1,0x12 */ set(3,cpu(17)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000012));
/* 0010dbf4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010dbf8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010dbfc: beq v1,zero,0x0010dca4 */ {int taken=(cpu(3)==cpu(0));/* delay 0010dc00 */ set(4,sx(UINT32_C(0x00000044)));if(taken){goto L_0010dca4;}}
/* 0010dc04: jal 0x002a8af8 */ set(31,UINT64_C(0x0010dc0c));/* delay 0010dc08 */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x0010dc04));
/* 0010dc0c: lui a1,0x8080 */ set(5,sx(UINT32_C(0x80800000)));
/* 0010dc10: move s0,v0 */ set(16,cpu(2));
/* 0010dc14: sll a0,s1,0x2 */ set(4,sx((uint32_t)cpu(17)<<2));
/* 0010dc18: sll v1,s1,0x18 */ set(3,sx((uint32_t)cpu(17)<<24));
/* 0010dc1c: beq s0,zero,0x0010dca4 */ {int taken=(cpu(16)==cpu(0));/* delay 0010dc20 */ set(5,cpu(5)|UINT32_C(0x00008080));if(taken){goto L_0010dca4;}}
/* 0010dc24: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0010dc28: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0010dc2c: lw v0,-0x5a38(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffffa5c8)));
/* 0010dc30: sw v1,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 0010dc34: sw a1,0x34(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(5));
/* 0010dc38: sw zero,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0010dc3c: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 0010dc40: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 0010dc44: sw v0,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 0010dc48: sw zero,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 0010dc4c: sw zero,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 0010dc50: sw zero,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 0010dc54: sw zero,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 0010dc58: sw zero,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 0010dc5c: sw zero,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 0010dc60: sw zero,0x2c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(0));
/* 0010dc64: beq v0,zero,0x0010dca0 */ {int taken=(cpu(2)==cpu(0));/* delay 0010dc68 */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));if(taken){goto L_0010dca0;}}
/* 0010dc6c: lw v0,0x0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0010dc70: beql v0,zero,0x0010dca4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0010dc74 */ set(2,cpu(16));goto L_0010dca4;}}
/* 0010dc78: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0010dc80));/* delay 0010dc7c */ set(4,cpu(16));nocturneFieldUnitLifetimeNativeIndirect(target,UINT32_C(0x0010dc78));}
/* 0010dc80: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0010dc84: beq v0,v1,0x0010dca0 */ {int taken=(cpu(2)==cpu(3));/* delay 0010dc88 */ set(4,cpu(16));if(taken){goto L_0010dca0;}}
/* 0010dc8c: jal 0x0010dcb8 */ set(31,UINT64_C(0x0010dc94));/* delay 0010dc90 */ body_0010dcb8();
/* 0010dc94: b 0x0010dca4 */ /* delay 0010dc98 */ set(2,cpu(0));goto L_0010dca4;
L_0010dca0:;
/* 0010dca0: move v0,s0 */ set(2,cpu(16));
L_0010dca4:;
/* 0010dca4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010dca8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010dcac: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010dcb0: jr ra */ {uint64_t target=cpu(31);/* delay 0010dcb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010dcb8(void){
uint64_t incoming=cpu(31);
/* 0010dcb8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0010dcbc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010dcc0: move s0,a0 */ set(16,cpu(4));
/* 0010dcc4: beq s0,zero,0x0010dd28 */ {int taken=(cpu(16)==cpu(0));/* delay 0010dcc8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_0010dd28;}}
/* 0010dccc: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0010dcd0: beql v0,zero,0x0010dcf0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0010dcd4 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000024)));goto L_0010dcf0;}}
/* 0010dcd8: lw v0,0x4(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 0010dcdc: beql v0,zero,0x0010dcf0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0010dce0 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000024)));goto L_0010dcf0;}}
/* 0010dce4: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0010dcec));/* delay 0010dce8 */ nocturneFieldUnitLifetimeNativeIndirect(target,UINT32_C(0x0010dce4));}
/* 0010dcec: lw v1,0x24(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000024)));
L_0010dcf0:;
/* 0010dcf0: beql v1,zero,0x0010dd04 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0010dcf4 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000020)));goto L_0010dd04;}}
/* 0010dcf8: lw v0,0x20(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 0010dcfc: sw v0,0x20(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 0010dd00: lw v1,0x20(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000020)));
L_0010dd04:;
/* 0010dd04: beq v1,zero,0x0010dd14 */ {int taken=(cpu(3)==cpu(0));/* delay 0010dd08 */ set(4,cpu(16));if(taken){goto L_0010dd14;}}
/* 0010dd0c: lw v0,0x24(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000024)));
/* 0010dd10: sw v0,0x24(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
L_0010dd14:;
/* 0010dd14: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010dd18: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010dd1c: j 0x002a8bd8 */ /* delay 0010dd20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x0010dd1c));return;
L_0010dd28:;
/* 0010dd28: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010dd2c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010dd30: jr ra */ {uint64_t target=cpu(31);/* delay 0010dd34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0010f040(void){
uint64_t incoming=cpu(31);
/* 0010f040: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010f044: move v0,zero */ set(2,cpu(0));
/* 0010f048: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f04c: move s0,a0 */ set(16,cpu(4));
/* 0010f050: addiu v1,s0,-0x2 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0xfffffffe)));
/* 0010f054: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f058: sltiu v1,v1,0x10 */ set(3,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0010f05c: beq v1,zero,0x0010f0d4 */ {int taken=(cpu(3)==cpu(0));/* delay 0010f060 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_0010f0d4;}}
/* 0010f064: jal 0x0010e588 */ set(31,UINT64_C(0x0010f06c));/* delay 0010f068 */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010e588),UINT32_C(0x0010f064));
/* 0010f06c: sll v1,s0,0x1 */ set(3,sx((uint32_t)cpu(16)<<1));
/* 0010f070: move s1,v0 */ set(17,cpu(2));
/* 0010f074: move a0,s0 */ set(4,cpu(16));
/* 0010f078: beq s1,zero,0x0010f0d4 */ {int taken=(cpu(17)==cpu(0));/* delay 0010f07c */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));if(taken){goto L_0010f0d4;}}
/* 0010f080: lw v0,0x18(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 0010f084: sll a1,v1,0x2 */ set(5,sx((uint32_t)cpu(3)<<2));
/* 0010f088: lw v1,0x8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 0010f08c: jal 0x0010dbe0 */ set(31,UINT64_C(0x0010f094));/* delay 0010f090 */ set(16,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));body_0010dbe0();
/* 0010f094: move a0,v0 */ set(4,cpu(2));
/* 0010f098: beql a0,zero,0x0010f0d8 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0010f09c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0010f0d8;}}
/* 0010f0a0: sw s1,0x30(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(17));
/* 0010f0a4: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0010f0a8: bnel v0,zero,0x0010f0b8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0010f0ac */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(4));goto L_0010f0b8;}}
/* 0010f0b0: b 0x0010f0c0 */ /* delay 0010f0b4 */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));goto L_0010f0c0;
L_0010f0b8:;
/* 0010f0b8: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0010f0bc: sw v0,0x24(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));
L_0010f0c0:;
/* 0010f0c0: sw a0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 0010f0c4: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0010f0c8: move v0,a0 */ set(2,cpu(4));
/* 0010f0cc: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0010f0d0: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
L_0010f0d4:;
/* 0010f0d4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0010f0d8:;
/* 0010f0d8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f0dc: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f0e0: jr ra */ {uint64_t target=cpu(31);/* delay 0010f0e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010f0e8(void){
uint64_t incoming=cpu(31);
/* 0010f0e8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0010f0ec: move a2,a0 */ set(6,cpu(4));
/* 0010f0f0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f0f4: beq a2,zero,0x0010f164 */ {int taken=(cpu(6)==cpu(0));/* delay 0010f0f8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_0010f164;}}
/* 0010f0fc: lbu v0,0xf(a2) */ set(2,byte(ea(6,(int32_t)UINT32_C(0x0000000f))));
/* 0010f100: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 0010f104: addiu a1,v0,-0x2 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffe)));
/* 0010f108: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0010f10c: sltiu a1,a1,0x10 */ set(5,cpu(5)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0010f110: beq a1,zero,0x0010f164 */ {int taken=(cpu(5)==cpu(0));/* delay 0010f114 */ set(7,sx((uint32_t)cpu(3)<<2));if(taken){goto L_0010f164;}}
/* 0010f118: lw v0,0x30(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000030)));
/* 0010f11c: lw v1,0x18(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 0010f120: lw a1,0x8(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0010f124: addu s0,a1,a3 */ set(16,sx((uint32_t)cpu(5)+(uint32_t)cpu(7)));
/* 0010f128: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0010f12c: bnel v0,a2,0x0010f140 */ {int taken=(cpu(2)!=cpu(6));if(taken){/* delay 0010f130 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));goto L_0010f140;}}
/* 0010f134: lw v0,0x20(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000020)));
/* 0010f138: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 0010f13c: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
L_0010f140:;
/* 0010f140: bne v0,a2,0x0010f150 */ {int taken=(cpu(2)!=cpu(6));/* delay 0010f144 */ if(taken){goto L_0010f150;}}
/* 0010f148: lw v0,0x24(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000024)));
/* 0010f14c: sw v0,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_0010f150:;
/* 0010f150: jal 0x0010dcb8 */ set(31,UINT64_C(0x0010f158));/* delay 0010f154 */ body_0010dcb8();
/* 0010f158: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0010f15c: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 0010f160: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_0010f164:;
/* 0010f164: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f168: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f16c: jr ra */ {uint64_t target=cpu(31);/* delay 0010f170 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0010f9d8(void){
uint64_t incoming=cpu(31);
/* 0010f9d8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010f9dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f9e0: move s0,a0 */ set(16,cpu(4));
/* 0010f9e4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f9e8: move s1,a1 */ set(17,cpu(5));
/* 0010f9ec: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f9f0: jal 0x0010f970 */ set(31,UINT64_C(0x0010f9f8));/* delay 0010f9f4 */ set(4,byte(ea(17,(int32_t)UINT32_C(0x0000000f))));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010f970),UINT32_C(0x0010f9f0));
/* 0010f9f8: move a0,s0 */ set(4,cpu(16));
/* 0010f9fc: jal 0x0010fab8 */ set(31,UINT64_C(0x0010fa04));/* delay 0010fa00 */ set(5,cpu(2));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010fab8),UINT32_C(0x0010f9fc));
/* 0010fa04: move s0,v0 */ set(16,cpu(2));
/* 0010fa08: jal 0x0010ec58 */ set(31,UINT64_C(0x0010fa10));/* delay 0010fa0c */ set(4,cpu(16));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ec58),UINT32_C(0x0010fa08));
/* 0010fa10: move a0,s0 */ set(4,cpu(16));
/* 0010fa14: jal 0x0010ea38 */ set(31,UINT64_C(0x0010fa1c));/* delay 0010fa18 */ set(5,cpu(17));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ea38),UINT32_C(0x0010fa14));
/* 0010fa1c: move a0,s0 */ set(4,cpu(16));
/* 0010fa20: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0010fa24: beq v0,v1,0x0010fa50 */ {int taken=(cpu(2)==cpu(3));/* delay 0010fa28 */ set(5,sx(UINT32_C(0x00000001)));if(taken){goto L_0010fa50;}}
/* 0010fa2c: jal 0x0010ea90 */ set(31,UINT64_C(0x0010fa34));/* delay 0010fa30 */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ea90),UINT32_C(0x0010fa2c));
/* 0010fa34: move a0,s0 */ set(4,cpu(16));
/* 0010fa38: move a1,s1 */ set(5,cpu(17));
/* 0010fa3c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010fa40: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010fa44: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010fa48: j 0x0010ebe0 */ /* delay 0010fa4c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ebe0),UINT32_C(0x0010fa48));return;
L_0010fa50:;
/* 0010fa50: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010fa54: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010fa58: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010fa5c: jr ra */ {uint64_t target=cpu(31);/* delay 0010fa60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010fb98(void){
uint64_t incoming=cpu(31);
/* 0010fb98: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010fb9c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010fba0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010fba4: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010fba8: jal 0x0010e588 */ set(31,UINT64_C(0x0010fbb0));/* delay 0010fbac */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010e588),UINT32_C(0x0010fba8));
/* 0010fbb0: move a0,v0 */ set(4,cpu(2));
/* 0010fbb4: jal 0x0010f270 */ set(31,UINT64_C(0x0010fbbc));/* delay 0010fbb8 */ set(5,sx(UINT32_C(0x00000002)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010f270),UINT32_C(0x0010fbb4));
/* 0010fbbc: move s1,v0 */ set(17,cpu(2));
/* 0010fbc0: bne s1,zero,0x0010fbd8 */ {int taken=(cpu(17)!=cpu(0));/* delay 0010fbc4 */ set(4,cpu(17));if(taken){goto L_0010fbd8;}}
/* 0010fbc8: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0010fbcc: b 0x0010fbf0 */ /* delay 0010fbd0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff7c0)));goto L_0010fbf0;
L_0010fbd8:;
/* 0010fbd8: jal 0x0010ebc8 */ set(31,UINT64_C(0x0010fbe0));/* delay 0010fbdc */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ebc8),UINT32_C(0x0010fbd8));
/* 0010fbe0: bne v0,zero,0x0010fc00 */ {int taken=(cpu(2)!=cpu(0));/* delay 0010fbe4 */ if(taken){goto L_0010fc00;}}
/* 0010fbe8: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0010fbec: addiu a0,a0,-0x818 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff7e8)));
L_0010fbf0:;
/* 0010fbf0: jal 0x002d4748 */ set(31,UINT64_C(0x0010fbf8));/* delay 0010fbf4 */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x0010fbf0));
/* 0010fbf8: b 0x0010fc20 */ /* delay 0010fbfc */ set(2,cpu(0));goto L_0010fc20;
L_0010fc00:;
/* 0010fc00: jal 0x0010ec58 */ set(31,UINT64_C(0x0010fc08));/* delay 0010fc04 */ set(4,cpu(17));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ec58),UINT32_C(0x0010fc00));
/* 0010fc08: jal 0x0010ec20 */ set(31,UINT64_C(0x0010fc10));/* delay 0010fc0c */ set(4,cpu(17));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ec20),UINT32_C(0x0010fc08));
/* 0010fc10: move a0,s1 */ set(4,cpu(17));
/* 0010fc14: jal 0x0010e748 */ set(31,UINT64_C(0x0010fc1c));/* delay 0010fc18 */ set(16,cpu(2));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010e748),UINT32_C(0x0010fc14));
/* 0010fc1c: move v0,s0 */ set(2,cpu(16));
L_0010fc20:;
/* 0010fc20: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010fc24: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010fc28: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010fc2c: jr ra */ {uint64_t target=cpu(31);/* delay 0010fc30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00110070(void){
uint64_t incoming=cpu(31);
/* 00110070: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00110074: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 00110078: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0011007c: move s3,a0 */ set(19,cpu(4));
/* 00110080: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110084: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00110088: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0011008c: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00110090: lw s2,0x10(s3) */ lw(18,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 00110094: jal 0x00110300 */ set(31,UINT64_C(0x0011009c));/* delay 00110098 */ set(4,cpu(18));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x00110300),UINT32_C(0x00110094));
/* 0011009c: beq v0,zero,0x001100ac */ {int taken=(cpu(2)==cpu(0));/* delay 001100a0 */ set(4,cpu(2));if(taken){goto L_001100ac;}}
/* 001100a4: jal 0x0010fa68 */ set(31,UINT64_C(0x001100ac));/* delay 001100a8 */ set(5,cpu(18));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010fa68),UINT32_C(0x001100a4));
L_001100ac:;
/* 001100ac: move s0,zero */ set(16,cpu(0));
/* 001100b0: addiu s1,s3,0x10 */ set(17,sx((uint32_t)cpu(19)+UINT32_C(0x00000010)));
/* 001100b4: nop  */ 
L_001100b8:;
/* 001100b8: slti v0,s0,0x3 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 001100bc: beql v0,zero,0x001100e4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001100c0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));goto L_001100e4;}}
/* 001100c4: blezl s0,0x001100e4 */ {int taken=((int64_t)cpu(16)<=0);if(taken){/* delay 001100c8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));goto L_001100e4;}}
/* 001100cc: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001100d0: beq v0,zero,0x001100e0 */ {int taken=(cpu(2)==cpu(0));/* delay 001100d4 */ set(4,cpu(2));if(taken){goto L_001100e0;}}
/* 001100d8: jal 0x0010f0e8 */ set(31,UINT64_C(0x001100e0));/* delay 001100dc */ body_0010f0e8();
L_001100e0:;
/* 001100e0: addiu s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
L_001100e4:;
/* 001100e4: slti v0,s0,0x8 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 001100e8: bne v0,zero,0x001100b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001100ec */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));if(taken){goto L_001100b8;}}
/* 001100f0: jal 0x00110370 */ set(31,UINT64_C(0x001100f8));/* delay 001100f4 */ set(4,cpu(18));body_00110370();
/* 001100f8: lw a0,0x34(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000034)));
/* 001100fc: beq a0,zero,0x0011010c */ {int taken=(cpu(4)==cpu(0));/* delay 00110100 */ set(5,sx(UINT32_C(0x00000001)));if(taken){goto L_0011010c;}}
/* 00110104: jal 0x002b0648 */ set(31,UINT64_C(0x0011010c));/* delay 00110108 */ set(6,sx(UINT32_C(0x00000001)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002b0648),UINT32_C(0x00110104));
L_0011010c:;
/* 0011010c: jal 0x0010e748 */ set(31,UINT64_C(0x00110114));/* delay 00110110 */ lw(4,ea(19,(int32_t)UINT32_C(0x00000004)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010e748),UINT32_C(0x0011010c));
/* 00110114: move a0,s3 */ set(4,cpu(19));
/* 00110118: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0011011c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00110120: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00110124: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00110128: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0011012c: j 0x002a8bd8 */ /* delay 00110130 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x0011012c));return;
}
static void body_00110370(void){
uint64_t incoming=cpu(31);
/* 00110370: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00110374: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110378: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0011037c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00110380: jal 0x001122a0 */ set(31,UINT64_C(0x00110388));/* delay 00110384 */ set(16,cpu(4));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x001122a0),UINT32_C(0x00110380));
/* 00110388: move s1,v0 */ set(17,cpu(2));
/* 0011038c: lw a0,0xc(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 00110390: beq a0,zero,0x001103f4 */ {int taken=(cpu(4)==cpu(0));/* delay 00110394 */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_001103f4;}}
/* 00110398: lw v0,0x8(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 0011039c: beq v0,v1,0x001103d8 */ {int taken=(cpu(2)==cpu(3));/* delay 001103a0 */ set(5,sx(UINT32_C(0x00000001)));if(taken){goto L_001103d8;}}
/* 001103a4: bnel v0,zero,0x001103ec */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001103a8 */ set(2,sx(UINT32_C(0x00000003)));goto L_001103ec;}}
/* 001103ac: jal 0x001dd220 */ set(31,UINT64_C(0x001103b4));/* delay 001103b0 */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x001dd220),UINT32_C(0x001103ac));
/* 001103b4: lw s0,0x18(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 001103b8: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001103bc: beq v0,zero,0x001103e8 */ {int taken=(cpu(2)==cpu(0));/* delay 001103c0 */ set(4,cpu(2));if(taken){goto L_001103e8;}}
/* 001103c4: jal 0x001e3af0 */ set(31,UINT64_C(0x001103cc));/* delay 001103c8 */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x001e3af0),UINT32_C(0x001103c4));
/* 001103cc: b 0x001103e8 */ /* delay 001103d0 */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));goto L_001103e8;
L_001103d8:;
/* 001103d8: jal 0x002b0648 */ set(31,UINT64_C(0x001103e0));/* delay 001103dc */ set(6,sx(UINT32_C(0x00000001)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002b0648),UINT32_C(0x001103d8));
/* 001103e0: jal 0x002b3c60 */ set(31,UINT64_C(0x001103e8));/* delay 001103e4 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000038)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002b3c60),UINT32_C(0x001103e0));
L_001103e8:;
/* 001103e8: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
L_001103ec:;
/* 001103ec: sw zero,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 001103f0: sw v0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_001103f4:;
/* 001103f4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001103f8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001103fc: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00110400: jr ra */ {uint64_t target=cpu(31);/* delay 00110404 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00111b80(void){
uint64_t incoming=cpu(31);
/* 00111b80: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00111b84: li a1,0x5 */ set(5,sx(UINT32_C(0x00000005)));
/* 00111b88: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00111b8c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00111b90: jal 0x00110300 */ set(31,UINT64_C(0x00111b98));/* delay 00111b94 */ set(16,cpu(4));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x00110300),UINT32_C(0x00111b90));
/* 00111b98: move a0,v0 */ set(4,cpu(2));
/* 00111b9c: beq a0,zero,0x00111bb0 */ {int taken=(cpu(4)==cpu(0));/* delay 00111ba0 */ set(5,cpu(16));if(taken){goto L_00111bb0;}}
/* 00111ba4: jal 0x0010f9d8 */ set(31,UINT64_C(0x00111bac));/* delay 00111ba8 */ body_0010f9d8();
/* 00111bac: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_00111bb0:;
/* 00111bb0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00111bb4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00111bb8: jr ra */ {uint64_t target=cpu(31);/* delay 00111bbc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00112a40(void){
uint64_t incoming=cpu(31);
/* 00112a40: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00112a44: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112a48: move s1,a0 */ set(17,cpu(4));
/* 00112a4c: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 00112a50: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112a54: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00112a58: move s2,a1 */ set(18,cpu(5));
/* 00112a5c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00112a60: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00112a64: jal 0x0010f040 */ set(31,UINT64_C(0x00112a6c));/* delay 00112a68 */ set(19,cpu(6));body_0010f040();
/* 00112a6c: move s0,v0 */ set(16,cpu(2));
/* 00112a70: beq s0,zero,0x00112ad0 */ {int taken=(cpu(16)==cpu(0));/* delay 00112a74 */ set(4,cpu(16));if(taken){goto L_00112ad0;}}
/* 00112a78: jal 0x00112168 */ set(31,UINT64_C(0x00112a80));/* delay 00112a7c */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x00112168),UINT32_C(0x00112a78));
/* 00112a80: move a0,s0 */ set(4,cpu(16));
/* 00112a84: jal 0x0010dea8 */ set(31,UINT64_C(0x00112a8c));/* delay 00112a88 */ set(5,cpu(18));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010dea8),UINT32_C(0x00112a84));
/* 00112a8c: move a0,s0 */ set(4,cpu(16));
/* 00112a90: jal 0x0010ded8 */ set(31,UINT64_C(0x00112a98));/* delay 00112a94 */ set(5,cpu(19));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ded8),UINT32_C(0x00112a90));
/* 00112a98: jal 0x0010de50 */ set(31,UINT64_C(0x00112aa0));/* delay 00112a9c */ lw(4,ea(16,(int32_t)UINT32_C(0x0000001c)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010de50),UINT32_C(0x00112a98));
/* 00112aa0: lw v1,0x18(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 00112aa4: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 00112aa8: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00112aac: jal 0x0010fb98 */ set(31,UINT64_C(0x00112ab4));/* delay 00112ab0 */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));body_0010fb98();
/* 00112ab4: move a0,s0 */ set(4,cpu(16));
/* 00112ab8: move a1,v0 */ set(5,cpu(2));
/* 00112abc: jal 0x00110298 */ set(31,UINT64_C(0x00112ac4));/* delay 00112ac0 */ set(6,sx(UINT32_C(0x00000005)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x00110298),UINT32_C(0x00112abc));
/* 00112ac4: jal 0x00111b80 */ set(31,UINT64_C(0x00112acc));/* delay 00112ac8 */ set(4,cpu(16));body_00111b80();
/* 00112acc: move v0,s0 */ set(2,cpu(16));
L_00112ad0:;
/* 00112ad0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112ad4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112ad8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00112adc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00112ae0: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00112ae4: jr ra */ {uint64_t target=cpu(31);/* delay 00112ae8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00112af0(void){
uint64_t incoming=cpu(31);
/* 00112af0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00112af4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112af8: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112afc: j 0x0010f0e8 */ /* delay 00112b00 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0010f0e8();return;
}
static void body_00112b38(void){
uint64_t incoming=cpu(31);
/* 00112b38: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00112b3c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112b40: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112b44: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00112b48: jal 0x0010dd38 */ set(31,UINT64_C(0x00112b50));/* delay 00112b4c */ set(17,cpu(4));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010dd38),UINT32_C(0x00112b48));
/* 00112b50: jal 0x002a8af8 */ set(31,UINT64_C(0x00112b58));/* delay 00112b54 */ set(4,sx(UINT32_C(0x00000020)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x00112b50));
/* 00112b58: move a1,zero */ set(5,cpu(0));
/* 00112b5c: sw v0,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 00112b60: li a2,0x20 */ set(6,sx(UINT32_C(0x00000020)));
/* 00112b64: jal 0x002d4558 */ set(31,UINT64_C(0x00112b6c));/* delay 00112b68 */ set(4,cpu(2));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002d4558),UINT32_C(0x00112b64));
/* 00112b6c: lw s0,0x18(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 00112b70: jal 0x0010ffe0 */ set(31,UINT64_C(0x00112b78));/* delay 00112b74 */ set(4,cpu(17));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ffe0),UINT32_C(0x00112b70));
/* 00112b78: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 00112b7c: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 00112b80: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 00112b84: sw v1,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 00112b88: move a0,s1 */ set(4,cpu(17));
/* 00112b8c: sw v1,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 00112b90: jal 0x00110138 */ set(31,UINT64_C(0x00112b98));/* delay 00112b94 */ set(5,sx(UINT32_C(0x00000042)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x00110138),UINT32_C(0x00112b90));
/* 00112b98: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00112b9c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112ba0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112ba4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00112ba8: jr ra */ {uint64_t target=cpu(31);/* delay 00112bac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00112bb0(void){
uint64_t incoming=cpu(31);
/* 00112bb0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00112bb4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112bb8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112bbc: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00112bc0: jal 0x001130d0 */ set(31,UINT64_C(0x00112bc8));/* delay 00112bc4 */ set(17,cpu(4));body_001130d0();
/* 00112bc8: jal 0x0010ddb0 */ set(31,UINT64_C(0x00112bd0));/* delay 00112bcc */ set(4,cpu(17));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x0010ddb0),UINT32_C(0x00112bc8));
/* 00112bd0: lw s0,0x18(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 00112bd4: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 00112bd8: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00112bdc: bnel v0,v1,0x00112be4 */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 00112be0 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));goto L_00112be4;}}
L_00112be4:;
/* 00112be4: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00112be8: beq v0,zero,0x00112bfc */ {int taken=(cpu(2)==cpu(0));/* delay 00112bec */ set(4,cpu(2));if(taken){goto L_00112bfc;}}
/* 00112bf0: jal 0x001e3af0 */ set(31,UINT64_C(0x00112bf8));/* delay 00112bf4 */ nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x001e3af0),UINT32_C(0x00112bf0));
/* 00112bf8: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
L_00112bfc:;
/* 00112bfc: jal 0x00110370 */ set(31,UINT64_C(0x00112c04));/* delay 00112c00 */ set(4,cpu(17));body_00110370();
/* 00112c04: jal 0x00110070 */ set(31,UINT64_C(0x00112c0c));/* delay 00112c08 */ lw(4,ea(16,(int32_t)UINT32_C(0x0000000c)));body_00110070();
/* 00112c0c: lw a0,0x18(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 00112c10: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112c14: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00112c18: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00112c1c: j 0x002a8bd8 */ /* delay 00112c20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002a8bd8),UINT32_C(0x00112c1c));return;
}
static void body_001130d0(void){
uint64_t incoming=cpu(31);
/* 001130d0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001130d4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001130d8: li s1,-0x1 */ set(17,sx(UINT32_C(0xffffffff)));
/* 001130dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001130e0: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001130e4: lw s0,0x18(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001130e8: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 001130ec: beql v0,s1,0x00113104 */ {int taken=(cpu(2)==cpu(17));if(taken){/* delay 001130f0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00113104;}}
/* 001130f4: jal 0x00115bc8 */ set(31,UINT64_C(0x001130fc));/* delay 001130f8 */ set(5,sx(UINT32_C(0x0000000a)));body_00115bc8();
/* 001130fc: sw s1,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(17));
/* 00113100: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00113104:;
/* 00113104: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00113108: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0011310c: jr ra */ {uint64_t target=cpu(31);/* delay 00113110 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00115bc8(void){
uint64_t incoming=cpu(31);
/* 00115bc8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00115bcc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00115bd0: lw v0,0x18(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 00115bd4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00115bd8: lw a0,0x8(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 00115bdc: j 0x001e3548 */ /* delay 00115be0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001e3548();return;
}
static void body_001e3548(void){
uint64_t incoming=cpu(31);
/* 001e3548: move a2,a0 */ set(6,cpu(4));
/* 001e354c: lw v0,0x84(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000084)));
/* 001e3550: beq v0,zero,0x001e35a8 */ {int taken=(cpu(2)==cpu(0));/* delay 001e3554 */ if(taken){goto L_001e35a8;}}
/* 001e3558: bne a1,zero,0x001e3588 */ {int taken=(cpu(5)!=cpu(0));/* delay 001e355c */ lw(2,ea(6,(int32_t)UINT32_C(0x000000a4)));if(taken){goto L_001e3588;}}
/* 001e3560: lui v1,0xfffb */ set(3,sx(UINT32_C(0xfffb0000)));
/* 001e3564: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 001e3568: lui a0,0xffe7 */ set(4,sx(UINT32_C(0xffe70000)));
/* 001e356c: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001e3570: ori a0,a0,0xffff */ set(4,cpu(4)|UINT32_C(0x0000ffff));
/* 001e3574: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 001e3578: sw zero,0x84(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000084)),(uint32_t)cpu(0));
/* 001e357c: jr ra */ {uint64_t target=cpu(31);/* delay 001e3580 */ sw(ea(6,(int32_t)UINT32_C(0x000000a4)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
L_001e3588:;
/* 001e3588: lui v1,0xfff7 */ set(3,sx(UINT32_C(0xfff70000)));
/* 001e358c: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 001e3590: lui a0,0x10 */ set(4,sx(UINT32_C(0x00100000)));
/* 001e3594: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001e3598: sh a1,0x146(a2) */ sh(ea(6,(int32_t)UINT32_C(0x00000146)),(uint16_t)cpu(5));
/* 001e359c: or v0,v0,a0 */ set(2,cpu(2)|cpu(4));
/* 001e35a0: sh zero,0x144(a2) */ sh(ea(6,(int32_t)UINT32_C(0x00000144)),(uint16_t)cpu(0));
/* 001e35a4: sw v0,0xa4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x000000a4)),(uint32_t)cpu(2));
L_001e35a8:;
/* 001e35a8: jr ra */ {uint64_t target=cpu(31);/* delay 001e35ac */ checkReturn(target,incoming);return;}
}
static void body_001e39e8(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 001e39e8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001e39ec: lui v0,0x54 */ set(2,sx(UINT32_C(0x00540000)));
/* 001e39f0: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001e39f4: move s2,a0 */ set(18,cpu(4));
/* 001e39f8: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e39fc: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e3a00: move s1,a1 */ set(17,cpu(5));
/* 001e3a04: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001e3a08: addiu a3,v0,-0x57b0 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0xffffa850)));
/* 001e3a0c: ldl v1,0x7(a3) */ loadPartial(3,ea(7,(int32_t)UINT32_C(0x00000007)),1);
/* 001e3a10: ldr v1,0x0(a3) */ loadPartial(3,ea(7,(int32_t)UINT32_C(0x00000000)),0);
/* 001e3a14: ldl a1,0xf(a3) */ loadPartial(5,ea(7,(int32_t)UINT32_C(0x0000000f)),1);
/* 001e3a18: ldr a1,0x8(a3) */ loadPartial(5,ea(7,(int32_t)UINT32_C(0x00000008)),0);
/* 001e3a1c: sdl v1,0x7(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000007)),3,1);
/* 001e3a20: sdr v1,0x0(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000000)),3,0);
/* 001e3a24: sdl a1,0xf(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000000f)),5,1);
/* 001e3a28: sdr a1,0x8(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000008)),5,0);
/* 001e3a2c: jal 0x002a8af8 */ set(31,UINT64_C(0x001e3a34));/* delay 001e3a30 */ set(4,sx(UINT32_C(0x00000148)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x001e3a2c));
/* 001e3a34: move s0,v0 */ set(16,cpu(2));
/* 001e3a38: move a1,zero */ set(5,cpu(0));
/* 001e3a3c: move a0,s0 */ set(4,cpu(16));
/* 001e3a40: jal 0x002d4558 */ set(31,UINT64_C(0x001e3a48));/* delay 001e3a44 */ set(6,sx(UINT32_C(0x00000148)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002d4558),UINT32_C(0x001e3a40));
/* 001e3a48: sh zero,0xa8(s0) */ sh(ea(16,(int32_t)UINT32_C(0x000000a8)),(uint16_t)cpu(0));
/* 001e3a4c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001e3a50: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 001e3a54: li v1,0xa */ set(3,sx(UINT32_C(0x0000000a)));
/* 001e3a58: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001e3a5c: sh v1,0xc2(s0) */ sh(ea(16,(int32_t)UINT32_C(0x000000c2)),(uint16_t)cpu(3));
/* 001e3a60: sh v0,0xaa(s0) */ sh(ea(16,(int32_t)UINT32_C(0x000000aa)),(uint16_t)cpu(2));
/* 001e3a64: swc1 f0,0xb4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000b4)),f[0]);
/* 001e3a68: sw s2,0x80(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000080)),(uint32_t)cpu(18));
/* 001e3a6c: sw s1,0x8c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000008c)),(uint32_t)cpu(17));
/* 001e3a70: sh v1,0xbc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x000000bc)),(uint16_t)cpu(3));
/* 001e3a74: sh zero,0xba(s0) */ sh(ea(16,(int32_t)UINT32_C(0x000000ba)),(uint16_t)cpu(0));
/* 001e3a78: sh zero,0xc0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x000000c0)),(uint16_t)cpu(0));
/* 001e3a7c: lqc2 vf10,0x0(sp) */ loadVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001e3a80: addiu v0,s0,0x10 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 001e3a84: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001e3a88: addiu v1,s0,0x40 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
/* 001e3a8c: sqc2 vf10,0x0(v1) */ storeVu(10,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001e3a90: lui v0,0xb2 */ set(2,sx(UINT32_C(0x00b20000)));
/* 001e3a94: lui v1,0x8030 */ set(3,sx(UINT32_C(0x80300000)));
/* 001e3a98: ori v1,v1,0x3030 */ set(3,cpu(3)|UINT32_C(0x00003030));
/* 001e3a9c: ori v0,v0,0xb2b2 */ set(2,cpu(2)|UINT32_C(0x0000b2b2));
/* 001e3aa0: sw v1,0x50(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
/* 001e3aa4: li a0,0xe0 */ set(4,sx(UINT32_C(0x000000e0)));
/* 001e3aa8: sw v1,0x5c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(3));
/* 001e3aac: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001e3ab0: jal 0x002a8af8 */ set(31,UINT64_C(0x001e3ab8));/* delay 001e3ab4 */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002a8af8),UINT32_C(0x001e3ab0));
/* 001e3ab8: move a1,zero */ set(5,cpu(0));
/* 001e3abc: sw v0,0x68(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000068)),(uint32_t)cpu(2));
/* 001e3ac0: move a0,v0 */ set(4,cpu(2));
/* 001e3ac4: jal 0x002d4558 */ set(31,UINT64_C(0x001e3acc));/* delay 001e3ac8 */ set(6,sx(UINT32_C(0x000000e0)));nocturneFieldUnitLifetimeNativeExternal(UINT32_C(0x002d4558),UINT32_C(0x001e3ac4));
/* 001e3acc: sw zero,0x6c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000006c)),(uint32_t)cpu(0));
/* 001e3ad0: move v0,s0 */ set(2,cpu(16));
/* 001e3ad4: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e3ad8: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e3adc: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001e3ae0: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001e3ae4: jr ra */ {uint64_t target=cpu(31);/* delay 001e3ae8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint32_t nocturneFieldUnitLifetimeNativeBody(uint32_t entry){switch(entry){
case UINT32_C(0x0010dbe0):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010dbe0();return 1u;case UINT32_C(0x0010dcb8):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010dcb8();return 1u;case UINT32_C(0x0010f040):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010f040();return 1u;case UINT32_C(0x0010f0e8):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010f0e8();return 1u;case UINT32_C(0x0010f9d8):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010f9d8();return 1u;case UINT32_C(0x0010fb98):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010fb98();return 1u;case UINT32_C(0x00110070):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00110070();return 1u;case UINT32_C(0x00110370):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00110370();return 1u;case UINT32_C(0x00111b80):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00111b80();return 1u;case UINT32_C(0x00112a40):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00112a40();return 1u;case UINT32_C(0x00112af0):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00112af0();return 1u;case UINT32_C(0x00112b38):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00112b38();return 1u;case UINT32_C(0x00112bb0):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00112bb0();return 1u;case UINT32_C(0x001130d0):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001130d0();return 1u;case UINT32_C(0x00115bc8):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00115bc8();return 1u;case UINT32_C(0x001e3548):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001e3548();return 1u;case UINT32_C(0x001e39e8):if(nocturneFieldUnitLifetimeNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001e39e8();return 1u;
default:return 0u;}}
uint64_t ps2FieldUnitLifetimeNative_0010DBE0(uint64_t a0){set(4,a0);body_0010dbe0();return cpu(2);}
void ps2FieldUnitLifetimeNative_0010DCB8(uint64_t a0){set(4,a0);body_0010dcb8();}
uint64_t ps2FieldUnitLifetimeNative_0010F040(uint64_t a0){set(4,a0);body_0010f040();return cpu(2);}
void ps2FieldUnitLifetimeNative_0010F0E8(uint64_t a0){set(4,a0);body_0010f0e8();}
uint64_t ps2FieldUnitLifetimeNative_0010F9D8(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_0010f9d8();return cpu(2);}
uint64_t ps2FieldUnitLifetimeNative_0010FB98(void){body_0010fb98();return cpu(2);}
void ps2FieldUnitLifetimeNative_00110070(uint64_t a0){set(4,a0);body_00110070();}
void ps2FieldUnitLifetimeNative_00110370(uint64_t a0){set(4,a0);body_00110370();}
uint64_t ps2FieldUnitLifetimeNative_00111B80(uint64_t a0){set(4,a0);body_00111b80();return cpu(2);}
uint64_t ps2FieldUnitLifetimeNative_00112A40(uint64_t a0,uint64_t a1,uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_00112a40();return cpu(2);}
void ps2FieldUnitLifetimeNative_00112AF0(uint64_t a0){set(4,a0);body_00112af0();}
uint64_t ps2FieldUnitLifetimeNative_00112B38(uint64_t a0){set(4,a0);body_00112b38();return cpu(2);}
void ps2FieldUnitLifetimeNative_00112BB0(uint64_t a0){set(4,a0);body_00112bb0();}
void ps2FieldUnitLifetimeNative_001130D0(uint64_t a0){set(4,a0);body_001130d0();}
void ps2FieldUnitLifetimeNative_00115BC8(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_00115bc8();}
void ps2FieldUnitLifetimeNative_001E3548(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_001e3548();}
uint64_t ps2FieldUnitLifetimeNative_001E39E8(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_001e39e8();return cpu(2);}
