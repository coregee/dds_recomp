/* Complete39 original field-controller/camera/collision owners; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "field_inf_controller_native.h"

#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveFieldInfControllerNativeAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneFieldInfControllerNativeCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneFieldInfControllerNativeCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneFieldInfControllerNativeCpuWrite(r,q);if(r==29u)nocturneFieldInfControllerNativeSetStackPointer(q[0]);
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

static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sq(unsigned reg,uint32_t a){uint32_t q[4];nocturneFieldInfControllerNativeCpuRead(reg,q);memcpy(at(a&~15u),q,16);}





static void requestLq(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneFieldInfControllerNativeCpuWrite(d,q);}


#include "ee_fpu_sqrt.h"
#include "ee_vu_rotation.h"
static float fieldReal(uint32_t bits){float value;memcpy(&value,&bits,4);return value;}
static uint32_t fieldBits(float value){uint32_t bits;memcpy(&bits,&value,4);return bits;}
static void fieldQmt(unsigned vf,unsigned reg){uint32_t words[4];nocturneFieldInfControllerNativeCpuRead(reg,words);nocturneFieldInfControllerNativeVuWrite(vf,words);}
static void fieldMulX(unsigned d,unsigned s,unsigned t,unsigned mask){
 uint32_t a[4],b[4],out[4];nocturneFieldInfControllerNativeVuRead(s,a);nocturneFieldInfControllerNativeVuRead(t,b);nocturneFieldInfControllerNativeVuRead(d,out);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[0]);
 nocturneFieldInfControllerNativeVuWrite(d,out);
}

static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}
static void loadVu(unsigned r,uint32_t a){uint32_t q[4];memcpy(q,at(a),16);nocturneFieldInfControllerNativeVuWrite(r,q);}
static void storeVu(unsigned r,uint32_t a){uint32_t q[4];nocturneFieldInfControllerNativeVuRead(r,q);memcpy(at(a),q,16);}
static void body_00109f08(void);
static void body_0010f020(void);
static void body_0010f1f8(void);
static void body_0010f270(void);
static void body_0010f4d8(void);
static void body_00110350(void);
static void body_00112410(void);
static void body_001128a8(void);
static void body_00113448(void);
static void body_00113458(void);
static void body_00120120(void);
static void body_001201a8(void);
static void body_001207c0(void);
static void body_00123370(void);
static void body_00125cb8(void);
static void body_0012c148(void);
static void body_0012c360(void);
static void body_0012c458(void);
static void body_0012c528(void);
static void body_0012c730(void);
static void body_0012ca30(void);
static void body_0012ddf8(void);
static void body_0012efd8(void);
static void body_001303a0(void);
static void body_00134df8(void);
static void body_00134e48(void);
static void body_00135318(void);
static void body_00137b40(void);
static void body_0013b928(void);
static void body_0013bad8(void);
static void body_0013c6f0(void);
static void body_0013c860(void);
static void body_001405b0(void);
static void body_00140cf0(void);
static void body_001452c8(void);
static void body_001dd578(void);
static void body_001e1688(void);
static void body_001e7228(void);
static void body_002c0560(void);
static void body_002c16b8(void);
static void body_002c18d8(void);
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
/* 00109f2c: jal 0x002d4748 */ set(31,UINT64_C(0x00109f34));/* delay 00109f30 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffe2e0)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x00109f2c));
/* 00109f34: lw s0,-0x57d8(gp) */ lw(16,ea(28,(int32_t)UINT32_C(0xffffa828)));
/* 00109f38: beq s0,zero,0x00109fa4 */ {int taken=(cpu(16)==cpu(0));/* delay 00109f3c */ set(20,sx(UINT32_C(0x00530000)));if(taken){goto L_00109fa4;}}
/* 00109f40: lui s3,0x53 */ set(19,sx(UINT32_C(0x00530000)));
/* 00109f44: lui s2,0x53 */ set(18,sx(UINT32_C(0x00530000)));
/* 00109f48: addiu a0,s4,-0x1d10 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0xffffe2f0)));
/* 00109f4c: nop  */ 
L_00109f50:;
/* 00109f50: jal 0x002d4748 */ set(31,UINT64_C(0x00109f58));/* delay 00109f54 */ set(5,cpu(16));nocturneFieldInfControllerNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x00109f50));
/* 00109f58: addiu a0,s2,-0x1cd8 */ set(4,sx((uint32_t)cpu(18)+UINT32_C(0xffffe328)));
/* 00109f5c: lw v0,0xe4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x000000e4)));
/* 00109f60: beq v0,zero,0x00109f88 */ {int taken=(cpu(2)==cpu(0));/* delay 00109f64 */ lw(17,ea(16,(int32_t)UINT32_C(0x000000ec)));if(taken){goto L_00109f88;}}
/* 00109f68: jal 0x002d4748 */ set(31,UINT64_C(0x00109f70));/* delay 00109f6c */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffe310)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x00109f68));
/* 00109f70: lw a0,0xe4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000e4)));
/* 00109f74: jal 0x00101738 */ set(31,UINT64_C(0x00109f7c));/* delay 00109f78 */ set(5,cpu(0));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00101738),UINT32_C(0x00109f74));
/* 00109f7c: b 0x00109f9c */ /* delay 00109f80 */ set(16,cpu(17));goto L_00109f9c;
L_00109f88:;
/* 00109f88: jal 0x002d4748 */ set(31,UINT64_C(0x00109f90));/* delay 00109f8c */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x00109f88));
/* 00109f90: jal 0x00109e50 */ set(31,UINT64_C(0x00109f98));/* delay 00109f94 */ set(4,cpu(16));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00109e50),UINT32_C(0x00109f90));
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
/* 00109fc8: j 0x002d4748 */ /* delay 00109fcc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);nocturneFieldInfControllerNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x00109fc8));return;
}
static void body_0010f020(void){
uint64_t incoming=cpu(31);
/* 0010f020: lw v0,0x18(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0010f024: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 0010f028: beq v0,zero,0x0010f034 */ {int taken=(cpu(2)==cpu(0));/* delay 0010f02c */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));if(taken){goto L_0010f034;}}
/* 0010f030: sw a1,0x20(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(5));
L_0010f034:;
/* 0010f034: jr ra */ {uint64_t target=cpu(31);/* delay 0010f038 */ checkReturn(target,incoming);return;}
}
static void body_0010f1f8(void){
uint64_t incoming=cpu(31);
/* 0010f1f8: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0010f1fc: jr ra */ {uint64_t target=cpu(31);/* delay 0010f200 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
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
/* 0010f2a8: jal 0x0010e690 */ set(31,UINT64_C(0x0010f2b0));/* delay 0010f2ac */ set(4,cpu(0));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e690),UINT32_C(0x0010f2a8));
/* 0010f2b0: move s1,v0 */ set(17,cpu(2));
/* 0010f2b4: lw v0,0x8(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 0010f2b8: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0010f2bc: lw s0,0x4(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 0010f2c0: move a0,s1 */ set(4,cpu(17));
/* 0010f2c4: nop  */ 
L_0010f2c8:;
/* 0010f2c8: jal 0x0010ea90 */ set(31,UINT64_C(0x0010f2d0));/* delay 0010f2cc */ set(5,sx(UINT32_C(0x00000001)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010ea90),UINT32_C(0x0010f2c8));
/* 0010f2d0: move a0,s1 */ set(4,cpu(17));
/* 0010f2d4: jal 0x0010ebe0 */ set(31,UINT64_C(0x0010f2dc));/* delay 0010f2d8 */ set(5,cpu(16));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010ebe0),UINT32_C(0x0010f2d4));
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
static void body_0010f4d8(void){
uint64_t incoming=cpu(31);
/* 0010f4d8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010f4dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f4e0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f4e4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f4e8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010f4ec: lw v0,0x18(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0010f4f0: lw s1,0x1c(v0) */ lw(17,ea(2,(int32_t)UINT32_C(0x0000001c)));
/* 0010f4f4: bne s1,zero,0x0010f510 */ {int taken=(cpu(17)!=cpu(0));/* delay 0010f4f8 */ set(16,cpu(5));if(taken){goto L_0010f510;}}
/* 0010f4fc: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0010f500: jal 0x002d4748 */ set(31,UINT64_C(0x0010f508));/* delay 0010f504 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff770)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x0010f500));
/* 0010f508: b 0x0010f580 */ /* delay 0010f50c */ set(2,cpu(0));goto L_0010f580;
L_0010f510:;
/* 0010f510: bne s0,zero,0x0010f528 */ {int taken=(cpu(16)!=cpu(0));/* delay 0010f514 */ if(taken){goto L_0010f528;}}
/* 0010f518: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0010f51c: b 0x0010f544 */ /* delay 0010f520 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff788)));goto L_0010f544;
L_0010f528:;
/* 0010f528: jal 0x0010a0d0 */ set(31,UINT64_C(0x0010f530));/* delay 0010f52c */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010a0d0),UINT32_C(0x0010f528));
/* 0010f530: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0010f534: move s2,v0 */ set(18,cpu(2));
/* 0010f538: addiu a0,a0,-0x860 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff7a0)));
/* 0010f53c: bgez s2,0x0010f558 */ {int taken=((int64_t)cpu(18)>=0);/* delay 0010f540 */ set(5,cpu(16));if(taken){goto L_0010f558;}}
L_0010f544:;
/* 0010f544: jal 0x002d4748 */ set(31,UINT64_C(0x0010f54c));/* delay 0010f548 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x002d4748),UINT32_C(0x0010f544));
/* 0010f54c: b 0x0010f580 */ /* delay 0010f550 */ set(2,cpu(0));goto L_0010f580;
L_0010f558:;
/* 0010f558: jal 0x00101898 */ set(31,UINT64_C(0x0010f560));/* delay 0010f55c */ set(4,cpu(16));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00101898),UINT32_C(0x0010f558));
/* 0010f560: li a0,0x3ea */ set(4,sx(UINT32_C(0x000003ea)));
/* 0010f564: beq v0,zero,0x0010f578 */ {int taken=(cpu(2)==cpu(0));/* delay 0010f568 */ set(6,cpu(18));if(taken){goto L_0010f578;}}
/* 0010f56c: b 0x0010f580 */ /* delay 0010f570 */ set(2,cpu(0));goto L_0010f580;
L_0010f578:;
/* 0010f578: jal 0x00109d98 */ set(31,UINT64_C(0x0010f580));/* delay 0010f57c */ set(5,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00109d98),UINT32_C(0x0010f578));
L_0010f580:;
/* 0010f580: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f584: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f588: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f58c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010f590: jr ra */ {uint64_t target=cpu(31);/* delay 0010f594 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00110350(void){
uint64_t incoming=cpu(31);
/* 00110350: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00110354: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110358: jal 0x001122a0 */ set(31,UINT64_C(0x00110360));/* delay 0011035c */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x001122a0),UINT32_C(0x00110358));
/* 00110360: lw v0,0xc(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 00110364: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00110368: jr ra */ {uint64_t target=cpu(31);/* delay 0011036c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00112410(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00112410: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00112414: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00112418: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0011241c: move s1,a0 */ set(17,cpu(4));
/* 00112420: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00112424: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00112428: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0011242c: lw s0,0x1c(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 00112430: lw s2,0x18(s1) */ lw(18,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 00112434: jal 0x0010de18 */ set(31,UINT64_C(0x0011243c));/* delay 00112438 */ set(4,cpu(16));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010de18),UINT32_C(0x00112434));
/* 0011243c: move a0,s0 */ set(4,cpu(16));
/* 00112440: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00112444: bne v0,v1,0x00112464 */ {int taken=(cpu(2)!=cpu(3));/* delay 00112448 */ set(5,sx(UINT32_C(0x00000001)));if(taken){goto L_00112464;}}
/* 0011244c: jal 0x0010de00 */ set(31,UINT64_C(0x00112454));/* delay 00112450 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010de00),UINT32_C(0x0011244c));
/* 00112454: jal 0x00112500 */ set(31,UINT64_C(0x0011245c));/* delay 00112458 */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00112500),UINT32_C(0x00112454));
/* 0011245c: jal 0x0010de50 */ set(31,UINT64_C(0x00112464));/* delay 00112460 */ set(4,cpu(16));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010de50),UINT32_C(0x0011245c));
L_00112464:;
/* 00112464: jal 0x0010e588 */ set(31,UINT64_C(0x0011246c));/* delay 00112468 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e588),UINT32_C(0x00112464));
/* 0011246c: jal 0x0010f1b0 */ set(31,UINT64_C(0x00112474));/* delay 00112470 */ set(4,cpu(2));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f1b0),UINT32_C(0x0011246c));
/* 00112474: lui v1,0x2f */ set(3,sx(UINT32_C(0x002f0000)));
/* 00112478: bne v0,s1,0x001124dc */ {int taken=(cpu(2)!=cpu(17));/* delay 0011247c */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00005a60)));if(taken){goto L_001124dc;}}
/* 00112480: addiu a0,s0,0x40 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));
/* 00112484: lq v0,0x0(a0) */ requestLq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00112488: sq v0,0x0(v1) */ sq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0011248c: lui v1,0x2f */ set(3,sx(UINT32_C(0x002f0000)));
/* 00112490: addiu a1,s2,0x60 */ set(5,sx((uint32_t)cpu(18)+UINT32_C(0x00000060)));
/* 00112494: addiu v1,v1,0x5a50 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00005a50)));
/* 00112498: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0011249c: sq v0,0x0(v1) */ sq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001124a0: lui a0,0x2f */ set(4,sx(UINT32_C(0x002f0000)));
/* 001124a4: addiu a1,s2,0x70 */ set(5,sx((uint32_t)cpu(18)+UINT32_C(0x00000070)));
/* 001124a8: addiu a0,a0,0x5a70 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00005a70)));
/* 001124ac: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 001124b0: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001124b4: lw v1,0x88(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000088)));
/* 001124b8: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 001124bc: beql v1,zero,0x001124e0 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 001124c0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001124e0;}}
/* 001124c4: jal 0x00105580 */ set(31,UINT64_C(0x001124cc));/* delay 001124c8 */ f[12]=word(ea(18,(int32_t)UINT32_C(0x0000008c)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00105580),UINT32_C(0x001124c4));
/* 001124cc: li v1,-0x2 */ set(3,sx(UINT32_C(0xfffffffe)));
/* 001124d0: lw v0,0x88(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000088)));
/* 001124d4: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001124d8: sw v0,0x88(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000088)),(uint32_t)cpu(2));
L_001124dc:;
/* 001124dc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001124e0:;
/* 001124e0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001124e4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001124e8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001124ec: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001124f0: jr ra */ {uint64_t target=cpu(31);/* delay 001124f4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001128a8(void){
uint64_t incoming=cpu(31);
/* 001128a8: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001128ac: addiu v1,v1,0x60 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000060)));
/* 001128b0: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 001128b4: sq v0,0x0(v1) */ sq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001128b8: jr ra */ {uint64_t target=cpu(31);/* delay 001128bc */ checkReturn(target,incoming);return;}
}
static void body_00113448(void){
uint64_t incoming=cpu(31);
/* 00113448: lw v0,0x18(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0011344c: jr ra */ {uint64_t target=cpu(31);/* delay 00113450 */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_00113458(void){
uint64_t incoming=cpu(31);
/* 00113458: lw v1,0x18(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 0011345c: jr ra */ {uint64_t target=cpu(31);/* delay 00113460 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));checkReturn(target,incoming);return;}
}
static void body_00120120(void){
uint64_t incoming=cpu(31);
/* 00120120: slti v0,a0,0x28 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000028));
/* 00120124: beql v0,zero,0x00120148 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00120128 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffd8)));goto L_00120148;}}
/* 0012012c: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 00120130: div a0,v1 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(3),1,0);
/* 00120134: beql v1,zero,0x0012013c */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00120138 */ nocturneFieldInfControllerNativeTrap(7u,UINT32_C(0x00120138));goto L_0012013c;}}
L_0012013c:;
/* 0012013c: mfhi v0 */ set(2,nocturneEffectHostHi());
/* 00120140: jr ra */ {uint64_t target=cpu(31);/* delay 00120144 */ checkReturn(target,incoming);return;}
L_00120148:;
/* 00120148: sltiu v0,a0,0x6 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0012014c: beq v0,zero,0x001201a0 */ {int taken=(cpu(2)==cpu(0));/* delay 00120150 */ if(taken){goto L_001201a0;}}
/* 00120154: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00120158: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 0012015c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00120160: lw v1,0x15f0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x000015f0)));
/* 00120164: jr v1 */ {uint64_t target=cpu(3);/* delay 00120168 */ switch((uint32_t)target){case UINT32_C(0x00120170):goto L_00120170;case UINT32_C(0x00120178):goto L_00120178;case UINT32_C(0x00120180):goto L_00120180;case UINT32_C(0x00120188):goto L_00120188;case UINT32_C(0x00120190):goto L_00120190;case UINT32_C(0x00120198):goto L_00120198;default:abort();}}
L_00120170:;
/* 00120170: jr ra */ {uint64_t target=cpu(31);/* delay 00120174 */ set(2,sx(UINT32_C(0x00000002)));checkReturn(target,incoming);return;}
L_00120178:;
/* 00120178: jr ra */ {uint64_t target=cpu(31);/* delay 0012017c */ set(2,sx(UINT32_C(0x00000005)));checkReturn(target,incoming);return;}
L_00120180:;
/* 00120180: jr ra */ {uint64_t target=cpu(31);/* delay 00120184 */ set(2,sx(UINT32_C(0x00000007)));checkReturn(target,incoming);return;}
L_00120188:;
/* 00120188: jr ra */ {uint64_t target=cpu(31);/* delay 0012018c */ set(2,sx(UINT32_C(0x00000009)));checkReturn(target,incoming);return;}
L_00120190:;
/* 00120190: jr ra */ {uint64_t target=cpu(31);/* delay 00120194 */ set(2,sx(UINT32_C(0x0000000a)));checkReturn(target,incoming);return;}
L_00120198:;
/* 00120198: jr ra */ {uint64_t target=cpu(31);/* delay 0012019c */ set(2,sx(UINT32_C(0x0000001e)));checkReturn(target,incoming);return;}
L_001201a0:;
/* 001201a0: jr ra */ {uint64_t target=cpu(31);/* delay 001201a4 */ set(2,cpu(0));checkReturn(target,incoming);return;}
}
static void body_001201a8(void){
uint64_t incoming=cpu(31);
/* 001201a8: addiu a0,a0,-0x2 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffe)));
/* 001201ac: sltiu v0,a0,0x1d */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000001d));
/* 001201b0: beq v0,zero,0x001201d8 */ {int taken=(cpu(2)==cpu(0));/* delay 001201b4 */ if(taken){goto L_001201d8;}}
/* 001201b8: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001201bc: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 001201c0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001201c4: lw v1,0x1610(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00001610)));
/* 001201c8: jr v1 */ {uint64_t target=cpu(3);/* delay 001201cc */ switch((uint32_t)target){case UINT32_C(0x001201d0):goto L_001201d0;case UINT32_C(0x001201d8):goto L_001201d8;default:abort();}}
L_001201d0:;
/* 001201d0: jr ra */ {uint64_t target=cpu(31);/* delay 001201d4 */ set(2,sx(UINT32_C(0x00000001)));checkReturn(target,incoming);return;}
L_001201d8:;
/* 001201d8: jr ra */ {uint64_t target=cpu(31);/* delay 001201dc */ set(2,cpu(0));checkReturn(target,incoming);return;}
}
static void body_001207c0(void){
uint64_t incoming=cpu(31);
/* 001207c0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001207c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001207c8: move s0,a0 */ set(16,cpu(4));
/* 001207cc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001207d0: move s1,a1 */ set(17,cpu(5));
/* 001207d4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001207d8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001207dc: jal 0x001201a8 */ set(31,UINT64_C(0x001207e4));/* delay 001207e0 */ set(18,cpu(6));body_001201a8();
/* 001207e4: bne v0,zero,0x00120870 */ {int taken=(cpu(2)!=cpu(0));/* delay 001207e8 */ set(2,cpu(0));if(taken){goto L_00120870;}}
/* 001207ec: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 001207f0: lw v0,-0x407c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0xffffbf84)));
/* 001207f4: slti v0,v0,0x28 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000028));
/* 001207f8: beq v0,zero,0x00120838 */ {int taken=(cpu(2)==cpu(0));/* delay 001207fc */ set(2,sx(UINT32_C(0x00000064)));if(taken){goto L_00120838;}}
/* 00120800: sll v1,s1,0x4 */ set(3,sx((uint32_t)cpu(17)<<4));
/* 00120804: div s0,v0 */ nativeDivide((uint32_t)cpu(16),(uint32_t)cpu(2),1,0);
/* 00120808: beql v0,zero,0x00120810 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0012080c */ nocturneFieldInfControllerNativeTrap(7u,UINT32_C(0x0012080c));goto L_00120810;}}
L_00120810:;
/* 00120810: subu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));
/* 00120814: lw a1,-0x5750(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00120818: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 0012081c: mfhi a0 */ set(4,nocturneEffectHostHi());
/* 00120820: sll v0,a0,0x4 */ set(2,sx((uint32_t)cpu(4)<<4));
/* 00120824: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 00120828: sll v0,v0,0x6 */ set(2,sx((uint32_t)cpu(2)<<6));
/* 0012082c: b 0x00120860 */ /* delay 00120830 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));goto L_00120860;
L_00120838:;
/* 00120838: jal 0x00120120 */ set(31,UINT64_C(0x00120840));/* delay 0012083c */ set(4,cpu(16));body_00120120();
/* 00120840: lw a1,-0x5750(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00120844: sll a0,v0,0x4 */ set(4,sx((uint32_t)cpu(2)<<4));
/* 00120848: sll v1,s1,0x4 */ set(3,sx((uint32_t)cpu(17)<<4));
/* 0012084c: subu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(2)));
/* 00120850: subu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));
/* 00120854: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 00120858: sll a0,a0,0x6 */ set(4,sx((uint32_t)cpu(4)<<6));
/* 0012085c: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
L_00120860:;
/* 00120860: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00120864: lhu v0,0x665c(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000665c))));
/* 00120868: srlv v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)>>((unsigned)cpu(18)&31u)));
/* 0012086c: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
L_00120870:;
/* 00120870: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00120874: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00120878: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0012087c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00120880: jr ra */ {uint64_t target=cpu(31);/* delay 00120884 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00123370(void){
uint64_t incoming=cpu(31);
/* 00123370: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00123374: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 00123378: addiu t0,v0,0x1850 */ set(8,sx((uint32_t)cpu(2)+UINT32_C(0x00001850)));
/* 0012337c: ldl a0,0x7(t0) */ loadPartial(4,ea(8,(int32_t)UINT32_C(0x00000007)),1);
/* 00123380: ldr a0,0x0(t0) */ loadPartial(4,ea(8,(int32_t)UINT32_C(0x00000000)),0);
/* 00123384: lw a1,0x8(t0) */ lw(5,ea(8,(int32_t)UINT32_C(0x00000008)));
/* 00123388: sdl a0,0x7(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000007)),4,1);
/* 0012338c: sdr a0,0x0(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000000)),4,0);
/* 00123390: sw a1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 00123394: move a1,zero */ set(5,cpu(0));
/* 00123398: lui a3,0x30 */ set(7,sx(UINT32_C(0x00300000)));
/* 0012339c: move a0,sp */ set(4,cpu(29));
/* 001233a0: addiu v1,a3,-0x4080 */ set(3,sx((uint32_t)cpu(7)+UINT32_C(0xffffbf80)));
/* 001233a4: lw a2,0x4(v1) */ lw(6,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 001233a8: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001233ac: nop  */ 
L_001233b0:;
/* 001233b0: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 001233b4: beq a2,v1,0x001233e8 */ {int taken=(cpu(6)==cpu(3));/* delay 001233b8 */ set(2,cpu(0));if(taken){goto L_001233e8;}}
/* 001233bc: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 001233c0: sltiu v0,a1,0x3 */ set(2,cpu(5)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 001233c4: nop  */ 
/* 001233c8: nop  */ 
/* 001233cc: bnel v0,zero,0x001233b0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001233d0 */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));goto L_001233b0;}}
/* 001233d4: addiu v1,a3,-0x4080 */ set(3,sx((uint32_t)cpu(7)+UINT32_C(0xffffbf80)));
/* 001233d8: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 001233dc: addiu v0,v0,-0x259 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffda7)));
/* 001233e0: sltiu v0,v0,0x10 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 001233e4: sltiu v0,v0,0x1 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_001233e8:;
/* 001233e8: jr ra */ {uint64_t target=cpu(31);/* delay 001233ec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00125cb8(void){
uint64_t incoming=cpu(31);
/* 00125cb8: li v0,0xe */ set(2,sx(UINT32_C(0x0000000e)));
/* 00125cbc: sw a0,-0x55f8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffaa08)),(uint32_t)cpu(4));
/* 00125cc0: bne a0,v0,0x00125cd8 */ {int taken=(cpu(4)!=cpu(2));/* delay 00125cc4 */ sw(ea(28,(int32_t)UINT32_C(0xffffaa0c)),(uint32_t)cpu(5));if(taken){goto L_00125cd8;}}
/* 00125cc8: li v0,0x25b */ set(2,sx(UINT32_C(0x0000025b)));
/* 00125ccc: bne a1,v0,0x00125cd8 */ {int taken=(cpu(5)!=cpu(2));/* delay 00125cd0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00125cd8;}}
/* 00125cd4: sw v0,-0x5620(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa9e0)),(uint32_t)cpu(2));
L_00125cd8:;
/* 00125cd8: jr ra */ {uint64_t target=cpu(31);/* delay 00125cdc */ checkReturn(target,incoming);return;}
}
static void body_0012c148(void){
uint64_t incoming=cpu(31);
/* 0012c148: jr ra */ {uint64_t target=cpu(31);/* delay 0012c14c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffab08)));checkReturn(target,incoming);return;}
}
static void body_0012c360(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0012c360: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0012c364: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012c368: jal 0x0012c148 */ set(31,UINT64_C(0x0012c370));/* delay 0012c36c */ body_0012c148();
/* 0012c370: lui v1,0x56 */ set(3,sx(UINT32_C(0x00560000)));
/* 0012c374: lui a1,0x980 */ set(5,sx(UINT32_C(0x09800000)));
/* 0012c378: addiu v1,v1,-0x2528 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffdad8)));
/* 0012c37c: ori a1,a1,0x8080 */ set(5,cpu(5)|UINT32_C(0x00008080));
/* 0012c380: bne v0,zero,0x0012c410 */ {int taken=(cpu(2)!=cpu(0));/* delay 0012c384 */ set(4,cpu(3));if(taken){goto L_0012c410;}}
/* 0012c388: li v0,0x80 */ set(2,sx(UINT32_C(0x00000080)));
/* 0012c38c: lwc1 f0,-0x7ec8(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8138)));
/* 0012c390: sw v0,-0x5500(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffab00)),(uint32_t)cpu(2));
/* 0012c394: li v0,0x44 */ set(2,sx(UINT32_C(0x00000044)));
/* 0012c398: lwc1 f1,-0x7ec4(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffff813c)));
/* 0012c39c: sw v0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0012c3a0: li v0,0x12c */ set(2,sx(UINT32_C(0x0000012c)));
/* 0012c3a4: sw a1,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 0012c3a8: swc1 f0,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),f[0]);
/* 0012c3ac: swc1 f1,0x10(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000010)),f[1]);
/* 0012c3b0: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0012c3b4: sw zero,-0x5504(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffaafc)),(uint32_t)cpu(0));
/* 0012c3b8: sw zero,-0x54fc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffab04)),(uint32_t)cpu(0));
/* 0012c3bc: sw zero,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 0012c3c0: sw zero,0x18(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 0012c3c4: sw zero,0x1c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 0012c3c8: sw zero,0x20(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 0012c3cc: sw zero,0x24(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 0012c3d0: jal 0x001a1ff8 */ set(31,UINT64_C(0x0012c3d8));/* delay 0012c3d4 */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));nocturneFieldInfControllerNativeExternal(UINT32_C(0x001a1ff8),UINT32_C(0x0012c3d0));
/* 0012c3d8: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0012c3dc: sw v0,-0x5508(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffaaf8)),(uint32_t)cpu(2));
/* 0012c3e0: jal 0x0010e548 */ set(31,UINT64_C(0x0012c3e8));/* delay 0012c3e4 */ sw(ea(28,(int32_t)UINT32_C(0xffffab08)),(uint32_t)cpu(3));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e548),UINT32_C(0x0012c3e0));
/* 0012c3e8: beq v0,zero,0x0012c414 */ {int taken=(cpu(2)==cpu(0));/* delay 0012c3ec */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0012c414;}}
/* 0012c3f0: jal 0x0010e548 */ set(31,UINT64_C(0x0012c3f8));/* delay 0012c3f4 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e548),UINT32_C(0x0012c3f0));
/* 0012c3f8: move a1,zero */ set(5,cpu(0));
/* 0012c3fc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012c400: move a0,v0 */ set(4,cpu(2));
/* 0012c404: j 0x0010f020 */ /* delay 0012c408 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_0010f020();return;
L_0012c410:;
/* 0012c410: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0012c414:;
/* 0012c414: jr ra */ {uint64_t target=cpu(31);/* delay 0012c418 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0012c458(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 0012c458: c.eq.S f12,f14 */ (void)(EE_FPU_COMPARE_S(f[12],f[14],0)!=0);
/* 0012c45c: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0012c460: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012c464: mov.S f1,f13 */ f[1]=f[13];
/* 0012c468: swc1 f22,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[22]);
/* 0012c46c: swc1 f21,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[21]);
/* 0012c470: bc1f 0x0012c488 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0012c474 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[20]);if(taken){goto L_0012c488;}}
/* 0012c478: c.eq.S f1,f15 */ (void)(EE_FPU_COMPARE_S(f[1],f[15],0)!=0);
/* 0012c47c: clear f0 */ f[0]=0;
/* 0012c480: bc1t 0x0012c514 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)!=0);/* delay 0012c484 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0012c514;}}
L_0012c488:;
/* 0012c488: sub.S f13,f12,f14 */ f[13]=EE_FPU_SUB_S(f[12],f[14]);
/* 0012c48c: clear f21 */ f[21]=0;
/* 0012c490: sub.S f20,f1,f15 */ f[20]=EE_FPU_SUB_S(f[1],f[15]);
/* 0012c494: c.lt.S f13,f21 */ (void)(EE_FPU_COMPARE_S(f[13],f[21],1)!=0);
/* 0012c498: mov.S f22,f13 */ f[22]=f[13];
/* 0012c49c: bc1f 0x0012c4a8 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0012c4a0 */ f[12]=f[20];if(taken){goto L_0012c4a8;}}
/* 0012c4a4: neg.S f13,f13 */ f[13]=f[13]^UINT32_C(0x80000000);
L_0012c4a8:;
/* 0012c4a8: c.lt.S f20,f21 */ (void)(EE_FPU_COMPARE_S(f[20],f[21],1)!=0);
/* 0012c4ac: bc1tl 0x0012c4b4 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)!=0);if(taken){/* delay 0012c4b0 */ f[12]=f[20]^UINT32_C(0x80000000);goto L_0012c4b4;}}
L_0012c4b4:;
/* 0012c4b4: jal 0x002c0258 */ set(31,UINT64_C(0x0012c4bc));/* delay 0012c4b8 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0258),UINT32_C(0x0012c4b4));
/* 0012c4bc: lwc1 f1,-0x7ec0(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffff8140)));
/* 0012c4c0: c.lt.S f22,f21 */ (void)(EE_FPU_COMPARE_S(f[22],f[21],1)!=0);
/* 0012c4c4: bc1f 0x0012c4e0 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0012c4c8 */ f[1]=EE_FPU_MUL_S(f[0],f[1]);if(taken){goto L_0012c4e0;}}
/* 0012c4cc: c.lt.S f20,f21 */ (void)(EE_FPU_COMPARE_S(f[20],f[21],1)!=0);
/* 0012c4d0: bc1fl 0x0012c50c */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);if(taken){/* delay 0012c4d4 */ f[1]=f[1]^UINT32_C(0x80000000);goto L_0012c50c;}}
/* 0012c4d8: b 0x0012c510 */ /* delay 0012c4dc */ f[0]=f[1];goto L_0012c510;
L_0012c4e0:;
/* 0012c4e0: c.lt.S f20,f21 */ (void)(EE_FPU_COMPARE_S(f[20],f[21],1)!=0);
/* 0012c4e4: bc1f 0x0012c500 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0012c4e8 */ if(taken){goto L_0012c500;}}
/* 0012c4ec: lui at,0x4334 */ set(1,sx(UINT32_C(0x43340000)));
/* 0012c4f0: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0012c4f4: b 0x0012c50c */ /* delay 0012c4f8 */ f[1]=EE_FPU_SUB_S(f[0],f[1]);goto L_0012c50c;
L_0012c500:;
/* 0012c500: lui at,0x4334 */ set(1,sx(UINT32_C(0x43340000)));
/* 0012c504: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0012c508: add.S f1,f1,f0 */ f[1]=EE_FPU_ADD_S(f[1],f[0]);
L_0012c50c:;
/* 0012c50c: mov.S f0,f1 */ f[0]=f[1];
L_0012c510:;
/* 0012c510: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0012c514:;
/* 0012c514: lwc1 f22,0x18(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0012c518: lwc1 f21,0x10(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0012c51c: lwc1 f20,0x8(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0012c520: jr ra */ {uint64_t target=cpu(31);/* delay 0012c524 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0012c528(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0012c528: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0012c52c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012c530: jal 0x0012c458 */ set(31,UINT64_C(0x0012c538));/* delay 0012c534 */ body_0012c458();
/* 0012c538: lui at,0x43b4 */ set(1,sx(UINT32_C(0x43b40000)));
/* 0012c53c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0012c540: li a0,0x168 */ set(4,sx(UINT32_C(0x00000168)));
/* 0012c544: lui at,0x42b4 */ set(1,sx(UINT32_C(0x42b40000)));
/* 0012c548: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0012c54c: beql a0,zero,0x0012c554 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 0012c550 */ nocturneFieldInfControllerNativeTrap(7u,UINT32_C(0x0012c550));goto L_0012c554;}}
L_0012c554:;
/* 0012c554: sub.S f1,f1,f0 */ f[1]=EE_FPU_SUB_S(f[1],f[0]);
/* 0012c558: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012c55c: add.S f1,f1,f2 */ f[1]=EE_FPU_ADD_S(f[1],f[2]);
/* 0012c560: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0012c564: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 0012c568: div v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),1,0);
/* 0012c56c: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 0012c570: mtc1 v1,f0 */ f[0]=(uint32_t)cpu(3);
/* 0012c574: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0012c578: jr ra */ {uint64_t target=cpu(31);/* delay 0012c57c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0012c730(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0012c730: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0012c734: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 0012c738: addiu v0,v0,-0x3640 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffc9c0)));
/* 0012c73c: addiu v1,v1,-0x3630 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffc9d0)));
/* 0012c740: lwc1 f3,0x0(v1) */ f[3]=word(ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0012c744: lwc1 f4,0x4(v1) */ f[4]=word(ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0012c748: lwc1 f0,0x0(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0012c74c: lwc1 f2,0x4(v0) */ f[2]=word(ea(2,(int32_t)UINT32_C(0x00000004)));
/* 0012c750: sub.S f0,f0,f3 */ f[0]=EE_FPU_SUB_S(f[0],f[3]);
/* 0012c754: lwc1 f3,0x8(v1) */ f[3]=word(ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0012c758: sub.S f2,f2,f4 */ f[2]=EE_FPU_SUB_S(f[2],f[4]);
/* 0012c75c: lui at,0x4248 */ set(1,sx(UINT32_C(0x42480000)));
/* 0012c760: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0012c764: lwc1 f1,0x8(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000008)));
/* 0012c768: mul.S f0,f0,f0 */ f[0]=EE_FPU_MUL_S(f[0],f[0]);
/* 0012c76c: sub.S f1,f1,f3 */ f[1]=EE_FPU_SUB_S(f[1],f[3]);
/* 0012c770: mul.S f2,f2,f2 */ f[2]=EE_FPU_MUL_S(f[2],f[2]);
/* 0012c774: mul.S f1,f1,f1 */ f[1]=EE_FPU_MUL_S(f[1],f[1]);
/* 0012c778: add.S f0,f0,f2 */ f[0]=EE_FPU_ADD_S(f[0],f[2]);
/* 0012c77c: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 0012c780: sqrt.S f0,f0 */ f[0]=EE_FPU_SQRT_S(f[0]);
/* 0012c784: sub.S f0,f0,f4 */ f[0]=EE_FPU_SUB_S(f[0],f[4]);
/* 0012c788: jr ra */ {uint64_t target=cpu(31);/* delay 0012c78c */ sw(ea(28,(int32_t)UINT32_C(0xffffa8f8)),f[0]);checkReturn(target,incoming);return;}
}
static void body_0012ca30(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0012ca30: addiu sp,sp,-0xc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff40)));
/* 0012ca34: sd s0,0x70(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0012ca38: sd s5,0x98(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0012ca3c: sd s1,0x78(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0012ca40: sd s2,0x80(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0012ca44: sd s3,0x88(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0012ca48: sd s4,0x90(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0012ca4c: sd ra,0xa0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0012ca50: swc1 f22,0xb8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b8)),f[22]);
/* 0012ca54: swc1 f21,0xb0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b0)),f[21]);
/* 0012ca58: jal 0x001225f8 */ set(31,UINT64_C(0x0012ca60));/* delay 0012ca5c */ sw(ea(29,(int32_t)UINT32_C(0x000000a8)),f[20]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x001225f8),UINT32_C(0x0012ca58));
/* 0012ca60: jal 0x001225e8 */ set(31,UINT64_C(0x0012ca68));/* delay 0012ca64 */ set(21,cpu(2));nocturneFieldInfControllerNativeExternal(UINT32_C(0x001225e8),UINT32_C(0x0012ca60));
/* 0012ca68: move s0,v0 */ set(16,cpu(2));
/* 0012ca6c: jal 0x0010df50 */ set(31,UINT64_C(0x0012ca74));/* delay 0012ca70 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010df50),UINT32_C(0x0012ca6c));
/* 0012ca74: jal 0x002c0b60 */ set(31,UINT64_C(0x0012ca7c));/* delay 0012ca78 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0b60),UINT32_C(0x0012ca74));
/* 0012ca7c: lui at,0x4334 */ set(1,sx(UINT32_C(0x43340000)));
/* 0012ca80: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0012ca84: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0012ca88: lwc1 f2,-0x7eb0(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffff8150)));
/* 0012ca8c: addiu v0,v0,-0x4080 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffbf80)));
/* 0012ca90: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0012ca94: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0012ca98: nop  */ 
/* 0012ca9c: nop  */ 
/* 0012caa0: div.S f0,f0,f2 */ f[0]=EE_FPU_DIV_S(f[0],f[2]);
/* 0012caa4: swc1 f0,0x128(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000128)),f[0]);
/* 0012caa8: jal 0x0010df38 */ set(31,UINT64_C(0x0012cab0));/* delay 0012caac */ sw(ea(2,(int32_t)UINT32_C(0x00000124)),f[0]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010df38),UINT32_C(0x0012caa8));
/* 0012cab0: addiu v0,sp,0x60 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 0012cab4: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0012cab8: lui s0,0x30 */ set(16,sx(UINT32_C(0x00300000)));
/* 0012cabc: lwc1 f20,-0x7eac(gp) */ f[20]=word(ea(28,(int32_t)UINT32_C(0xffff8154)));
/* 0012cac0: addiu s0,s0,-0x4080 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffbf80)));
/* 0012cac4: lui at,0x4334 */ set(1,sx(UINT32_C(0x43340000)));
/* 0012cac8: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 0012cacc: lwc1 f0,0x124(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000124)));
/* 0012cad0: lui s1,0x30 */ set(17,sx(UINT32_C(0x00300000)));
/* 0012cad4: lwc1 f3,0x60(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0012cad8: addiu s1,s1,-0x3840 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffc7c0)));
/* 0012cadc: neg.S f0,f0 */ f[0]=f[0]^UINT32_C(0x80000000);
/* 0012cae0: lwc1 f1,0x64(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000064)));
/* 0012cae4: lwc1 f2,0x68(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0012cae8: addiu s4,s1,0x4 */ set(20,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
/* 0012caec: swc1 f3,0x10c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000010c)),f[3]);
/* 0012caf0: lui s3,0x30 */ set(19,sx(UINT32_C(0x00300000)));
/* 0012caf4: swc1 f1,0x110(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000110)),f[1]);
/* 0012caf8: addiu s3,s3,-0x3640 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffc9c0)));
/* 0012cafc: mul.S f12,f0,f20 */ f[12]=EE_FPU_MUL_S(f[0],f[20]);
/* 0012cb00: swc1 f2,0x114(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000114)),f[2]);
/* 0012cb04: swc1 f3,0x100(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000100)),f[3]);
/* 0012cb08: swc1 f1,0x104(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000104)),f[1]);
/* 0012cb0c: swc1 f2,0x108(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000108)),f[2]);
/* 0012cb10: nop  */ 
/* 0012cb14: nop  */ 
/* 0012cb18: div.S f12,f12,f21 */ f[12]=EE_FPU_DIV_S(f[12],f[21]);
/* 0012cb1c: swc1 f0,-0x570c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa8f4)),f[0]);
/* 0012cb20: lui at,0x42a0 */ set(1,sx(UINT32_C(0x42a00000)));
/* 0012cb24: mtc1 at,f22 */ f[22]=(uint32_t)cpu(1);
/* 0012cb28: jal 0x002c0060 */ set(31,UINT64_C(0x0012cb30));/* delay 0012cb2c */ sw(ea(28,(int32_t)UINT32_C(0xffffab6c)),f[0]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0060),UINT32_C(0x0012cb28));
/* 0012cb30: lwc1 f3,0x100(s0) */ f[3]=word(ea(16,(int32_t)UINT32_C(0x00000100)));
/* 0012cb34: lwc1 f12,-0x570c(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffa8f4)));
/* 0012cb38: mul.S f0,f0,f22 */ f[0]=EE_FPU_MUL_S(f[0],f[22]);
/* 0012cb3c: lw v0,0x9c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000009c)));
/* 0012cb40: mul.S f12,f12,f20 */ f[12]=EE_FPU_MUL_S(f[12],f[20]);
/* 0012cb44: lwc1 f1,0x104(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000104)));
/* 0012cb48: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 0012cb4c: addu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(20)));
/* 0012cb50: sub.S f3,f3,f0 */ f[3]=EE_FPU_SUB_S(f[3],f[0]);
/* 0012cb54: lwc1 f2,0x0(v0) */ f[2]=word(ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0012cb58: nop  */ 
/* 0012cb5c: nop  */ 
/* 0012cb60: div.S f12,f12,f21 */ f[12]=EE_FPU_DIV_S(f[12],f[21]);
/* 0012cb64: add.S f1,f1,f2 */ f[1]=EE_FPU_ADD_S(f[1],f[2]);
/* 0012cb68: swc1 f3,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[3]);
/* 0012cb6c: jal 0x002c0160 */ set(31,UINT64_C(0x0012cb74));/* delay 0012cb70 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[1]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0160),UINT32_C(0x0012cb6c));
/* 0012cb74: lwc1 f1,0x108(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000108)));
/* 0012cb78: lwc1 f12,-0x570c(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffa8f4)));
/* 0012cb7c: mul.S f0,f0,f22 */ f[0]=EE_FPU_MUL_S(f[0],f[22]);
/* 0012cb80: mul.S f12,f12,f20 */ f[12]=EE_FPU_MUL_S(f[12],f[20]);
/* 0012cb84: sub.S f1,f1,f0 */ f[1]=EE_FPU_SUB_S(f[1],f[0]);
/* 0012cb88: nop  */ 
/* 0012cb8c: nop  */ 
/* 0012cb90: div.S f12,f12,f21 */ f[12]=EE_FPU_DIV_S(f[12],f[21]);
/* 0012cb94: jal 0x002c0060 */ set(31,UINT64_C(0x0012cb9c));/* delay 0012cb98 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[1]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0060),UINT32_C(0x0012cb94));
/* 0012cb9c: lw v1,0x9c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000009c)));
/* 0012cba0: lwc1 f12,-0x570c(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffa8f4)));
/* 0012cba4: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 0012cba8: lwc1 f2,0x100(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x00000100)));
/* 0012cbac: mul.S f12,f12,f20 */ f[12]=EE_FPU_MUL_S(f[12],f[20]);
/* 0012cbb0: addu v0,v1,s1 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(17)));
/* 0012cbb4: lwc1 f3,0x0(v0) */ f[3]=word(ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0012cbb8: addu v1,s1,v1 */ set(3,sx((uint32_t)cpu(17)+(uint32_t)cpu(3)));
/* 0012cbbc: lwc1 f4,0x8(v1) */ f[4]=word(ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0012cbc0: mul.S f0,f0,f3 */ f[0]=EE_FPU_MUL_S(f[0],f[3]);
/* 0012cbc4: lwc1 f1,0x104(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000104)));
/* 0012cbc8: nop  */ 
/* 0012cbcc: nop  */ 
/* 0012cbd0: div.S f12,f12,f21 */ f[12]=EE_FPU_DIV_S(f[12],f[21]);
/* 0012cbd4: add.S f1,f1,f4 */ f[1]=EE_FPU_ADD_S(f[1],f[4]);
/* 0012cbd8: add.S f2,f2,f0 */ f[2]=EE_FPU_ADD_S(f[2],f[0]);
/* 0012cbdc: swc1 f1,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[1]);
/* 0012cbe0: jal 0x002c0160 */ set(31,UINT64_C(0x0012cbe8));/* delay 0012cbe4 */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[2]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0160),UINT32_C(0x0012cbe0));
/* 0012cbe8: lw v1,0x9c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000009c)));
/* 0012cbec: lwc1 f4,0x108(s0) */ f[4]=word(ea(16,(int32_t)UINT32_C(0x00000108)));
/* 0012cbf0: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 0012cbf4: addu s1,v1,s1 */ set(17,sx((uint32_t)cpu(3)+(uint32_t)cpu(17)));
/* 0012cbf8: lwc1 f1,0x0(s1) */ f[1]=word(ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0012cbfc: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0012cc00: add.S f0,f4,f0 */ f[0]=EE_FPU_ADD_S(f[4],f[0]);
/* 0012cc04: swc1 f0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[0]);
/* 0012cc08: lq v0,0x0(sp) */ requestLq(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012cc0c: sq v0,0x0(s3) */ sq(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0012cc10: lui s2,0x30 */ set(18,sx(UINT32_C(0x00300000)));
/* 0012cc14: addiu s1,sp,0x20 */ set(17,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 0012cc18: addiu s2,s2,-0x3630 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffc9d0)));
/* 0012cc1c: lq v0,0x0(s1) */ requestLq(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0012cc20: sq v0,0x0(s2) */ sq(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0012cc24: sw zero,-0x5710(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa8f0)),(uint32_t)cpu(0));
/* 0012cc28: addu v1,v1,s4 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(20)));
/* 0012cc2c: lwc1 f3,0x0(v1) */ f[3]=word(ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0012cc30: addiu v1,sp,0x10 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0012cc34: lwc1 f1,0x104(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000104)));
/* 0012cc38: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 0012cc3c: lwc1 f20,-0x5710(gp) */ f[20]=word(ea(28,(int32_t)UINT32_C(0xffffa8f0)));
/* 0012cc40: addiu a1,sp,0x30 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 0012cc44: lwc1 f0,0x24(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000024)));
/* 0012cc48: add.S f1,f1,f3 */ f[1]=EE_FPU_ADD_S(f[1],f[3]);
/* 0012cc4c: lwc1 f2,0x100(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x00000100)));
/* 0012cc50: add.S f0,f0,f20 */ f[0]=EE_FPU_ADD_S(f[0],f[20]);
/* 0012cc54: sw v0,-0x54a8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffab58)),(uint32_t)cpu(2));
/* 0012cc58: swc1 f2,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[2]);
/* 0012cc5c: swc1 f1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[1]);
/* 0012cc60: swc1 f4,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[4]);
/* 0012cc64: swc1 f0,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[0]);
/* 0012cc68: sw v0,-0x54a4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffab5c)),(uint32_t)cpu(2));
/* 0012cc6c: swc1 f20,-0x54e4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffab1c)),f[20]);
/* 0012cc70: lq v0,0x0(v1) */ requestLq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0012cc74: sq v0,0x0(a1) */ sq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0012cc78: addiu a0,sp,0x40 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
/* 0012cc7c: lq v0,0x0(s1) */ requestLq(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0012cc80: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0012cc84: jal 0x0013bad8 */ set(31,UINT64_C(0x0012cc8c));/* delay 0012cc88 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));body_0013bad8();
/* 0012cc8c: lwc1 f6,-0x54d0(gp) */ f[6]=word(ea(28,(int32_t)UINT32_C(0xffffab30)));
/* 0012cc90: lwc1 f9,0x10(sp) */ f[9]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0012cc94: move a1,s1 */ set(5,cpu(17));
/* 0012cc98: lwc1 f7,0x14(sp) */ f[7]=word(ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0012cc9c: lwc1 f4,0x50(sp) */ f[4]=word(ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0012cca0: lwc1 f1,0x54(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000054)));
/* 0012cca4: sub.S f0,f4,f9 */ f[0]=EE_FPU_SUB_S(f[4],f[9]);
/* 0012cca8: lwc1 f8,0x18(sp) */ f[8]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0012ccac: sub.S f5,f1,f7 */ f[5]=EE_FPU_SUB_S(f[1],f[7]);
/* 0012ccb0: lwc1 f3,0x58(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0012ccb4: lwc1 f10,-0x54c8(gp) */ f[10]=word(ea(28,(int32_t)UINT32_C(0xffffab38)));
/* 0012ccb8: sub.S f1,f7,f1 */ f[1]=EE_FPU_SUB_S(f[7],f[1]);
/* 0012ccbc: sub.S f2,f3,f8 */ f[2]=EE_FPU_SUB_S(f[3],f[8]);
/* 0012ccc0: lw a0,0x78(s5) */ lw(4,ea(21,(int32_t)UINT32_C(0x00000078)));
/* 0012ccc4: mul.S f0,f0,f0 */ f[0]=EE_FPU_MUL_S(f[0],f[0]);
/* 0012ccc8: mul.S f5,f5,f5 */ f[5]=EE_FPU_MUL_S(f[5],f[5]);
/* 0012cccc: nop  */ 
/* 0012ccd0: nop  */ 
/* 0012ccd4: div.S f6,f6,f10 */ f[6]=EE_FPU_DIV_S(f[6],f[10]);
/* 0012ccd8: mul.S f2,f2,f2 */ f[2]=EE_FPU_MUL_S(f[2],f[2]);
/* 0012ccdc: sub.S f4,f9,f4 */ f[4]=EE_FPU_SUB_S(f[9],f[4]);
/* 0012cce0: add.S f0,f0,f5 */ f[0]=EE_FPU_ADD_S(f[0],f[5]);
/* 0012cce4: sub.S f3,f8,f3 */ f[3]=EE_FPU_SUB_S(f[8],f[3]);
/* 0012cce8: add.S f0,f0,f2 */ f[0]=EE_FPU_ADD_S(f[0],f[2]);
/* 0012ccec: sqrt.S f0,f0 */ f[0]=EE_FPU_SQRT_S(f[0]);
/* 0012ccf0: nop  */ 
/* 0012ccf4: nop  */ 
/* 0012ccf8: div.S f1,f1,f0 */ f[1]=EE_FPU_DIV_S(f[1],f[0]);
/* 0012ccfc: mul.S f6,f0,f6 */ f[6]=EE_FPU_MUL_S(f[0],f[6]);
/* 0012cd00: swc1 f6,-0x54cc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffab34)),f[6]);
/* 0012cd04: nop  */ 
/* 0012cd08: nop  */ 
/* 0012cd0c: div.S f4,f4,f0 */ f[4]=EE_FPU_DIV_S(f[4],f[0]);
/* 0012cd10: mul.S f1,f1,f6 */ f[1]=EE_FPU_MUL_S(f[1],f[6]);
/* 0012cd14: nop  */ 
/* 0012cd18: nop  */ 
/* 0012cd1c: div.S f3,f3,f0 */ f[3]=EE_FPU_DIV_S(f[3],f[0]);
/* 0012cd20: sub.S f7,f7,f1 */ f[7]=EE_FPU_SUB_S(f[7],f[1]);
/* 0012cd24: mul.S f4,f4,f6 */ f[4]=EE_FPU_MUL_S(f[4],f[6]);
/* 0012cd28: sub.S f7,f7,f20 */ f[7]=EE_FPU_SUB_S(f[7],f[20]);
/* 0012cd2c: sub.S f9,f9,f4 */ f[9]=EE_FPU_SUB_S(f[9],f[4]);
/* 0012cd30: mul.S f3,f3,f6 */ f[3]=EE_FPU_MUL_S(f[3],f[6]);
/* 0012cd34: swc1 f7,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[7]);
/* 0012cd38: swc1 f9,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[9]);
/* 0012cd3c: sub.S f8,f8,f3 */ f[8]=EE_FPU_SUB_S(f[8],f[3]);
/* 0012cd40: jal 0x0010dea8 */ set(31,UINT64_C(0x0012cd48));/* delay 0012cd44 */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[8]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010dea8),UINT32_C(0x0012cd40));
/* 0012cd48: lq v0,0x0(sp) */ requestLq(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012cd4c: sq v0,0x0(s3) */ sq(2,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0012cd50: lq v0,0x0(s1) */ requestLq(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0012cd54: sq v0,0x0(s2) */ sq(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0012cd58: lw a0,0x78(s5) */ lw(4,ea(21,(int32_t)UINT32_C(0x00000078)));
/* 0012cd5c: lw v1,0x10(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0012cd60: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0012cd64: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0012cd6c));/* delay 0012cd68 */ nocturneFieldInfControllerNativeIndirect(target,UINT32_C(0x0012cd64));}
/* 0012cd6c: jal 0x0012c730 */ set(31,UINT64_C(0x0012cd74));/* delay 0012cd70 */ body_0012c730();
/* 0012cd74: ld s0,0x70(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0012cd78: ld s1,0x78(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0012cd7c: ld s2,0x80(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0012cd80: ld s3,0x88(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0012cd84: ld s4,0x90(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0012cd88: ld s5,0x98(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0012cd8c: ld ra,0xa0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0012cd90: lwc1 f22,0xb8(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0012cd94: lwc1 f21,0xb0(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0012cd98: lwc1 f20,0xa8(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0012cd9c: jr ra */ {uint64_t target=cpu(31);/* delay 0012cda0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000c0)));checkReturn(target,incoming);return;}
}
static void body_0012ddf8(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0012ddf8: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 0012ddfc: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0012de00: lui s0,0x30 */ set(16,sx(UINT32_C(0x00300000)));
/* 0012de04: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0012de08: lui s1,0x30 */ set(17,sx(UINT32_C(0x00300000)));
/* 0012de0c: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0012de10: addiu s0,s0,-0x4080 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffbf80)));
/* 0012de14: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0012de18: swc1 f20,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),f[20]);
/* 0012de1c: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0012de20: jal 0x001225f8 */ set(31,UINT64_C(0x0012de28));/* delay 0012de24 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffc9c0)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x001225f8),UINT32_C(0x0012de20));
/* 0012de28: jal 0x001225e8 */ set(31,UINT64_C(0x0012de30));/* delay 0012de2c */ set(19,cpu(2));nocturneFieldInfControllerNativeExternal(UINT32_C(0x001225e8),UINT32_C(0x0012de28));
/* 0012de30: move s2,v0 */ set(18,cpu(2));
/* 0012de34: lui at,0x4334 */ set(1,sx(UINT32_C(0x43340000)));
/* 0012de38: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
/* 0012de3c: jal 0x0010df50 */ set(31,UINT64_C(0x0012de44));/* delay 0012de40 */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010df50),UINT32_C(0x0012de3c));
/* 0012de44: jal 0x002c0b60 */ set(31,UINT64_C(0x0012de4c));/* delay 0012de48 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0b60),UINT32_C(0x0012de44));
/* 0012de4c: lw v0,0x9c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000009c)));
/* 0012de50: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 0012de54: lwc1 f3,0x104(s0) */ f[3]=word(ea(16,(int32_t)UINT32_C(0x00000104)));
/* 0012de58: move a1,sp */ set(5,cpu(29));
/* 0012de5c: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 0012de60: lwc1 f6,0x0(s1) */ f[6]=word(ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0012de64: lui at,0x30 */ set(1,sx(UINT32_C(0x00300000)));
/* 0012de68: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 0012de6c: lwc1 f1,-0x383c(at) */ f[1]=word(ea(1,(int32_t)UINT32_C(0xffffc7c4)));
/* 0012de70: lwc1 f4,0x4(s1) */ f[4]=word(ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0012de74: add.S f3,f3,f1 */ f[3]=EE_FPU_ADD_S(f[3],f[1]);
/* 0012de78: lwc1 f1,0x100(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000100)));
/* 0012de7c: lwc1 f5,0x8(s1) */ f[5]=word(ea(17,(int32_t)UINT32_C(0x00000008)));
/* 0012de80: lwc1 f2,0x108(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x00000108)));
/* 0012de84: sub.S f1,f1,f6 */ f[1]=EE_FPU_SUB_S(f[1],f[6]);
/* 0012de88: lwc1 f7,-0x7e88(gp) */ f[7]=word(ea(28,(int32_t)UINT32_C(0xffff8178)));
/* 0012de8c: sub.S f3,f3,f4 */ f[3]=EE_FPU_SUB_S(f[3],f[4]);
/* 0012de90: lw a0,0x78(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000078)));
/* 0012de94: nop  */ 
/* 0012de98: nop  */ 
/* 0012de9c: div.S f0,f0,f7 */ f[0]=EE_FPU_DIV_S(f[0],f[7]);
/* 0012dea0: sub.S f2,f2,f5 */ f[2]=EE_FPU_SUB_S(f[2],f[5]);
/* 0012dea4: add.S f6,f6,f1 */ f[6]=EE_FPU_ADD_S(f[6],f[1]);
/* 0012dea8: add.S f4,f4,f3 */ f[4]=EE_FPU_ADD_S(f[4],f[3]);
/* 0012deac: add.S f5,f5,f2 */ f[5]=EE_FPU_ADD_S(f[5],f[2]);
/* 0012deb0: swc1 f6,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[6]);
/* 0012deb4: swc1 f4,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[4]);
/* 0012deb8: swc1 f0,0x128(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000128)),f[0]);
/* 0012debc: swc1 f5,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[5]);
/* 0012dec0: jal 0x001128a8 */ set(31,UINT64_C(0x0012dec8));/* delay 0012dec4 */ sw(ea(16,(int32_t)UINT32_C(0x00000124)),f[0]);body_001128a8();
/* 0012dec8: jal 0x0010e0a0 */ set(31,UINT64_C(0x0012ded0));/* delay 0012decc */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e0a0),UINT32_C(0x0012dec8));
/* 0012ded0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0012ded4: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0012ded8: lwc1 f3,0x38(s0) */ f[3]=word(ea(16,(int32_t)UINT32_C(0x00000038)));
/* 0012dedc: addiu s2,sp,0x10 */ set(18,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0012dee0: lwc1 f1,0x30(s0) */ f[1]=word(ea(16,(int32_t)UINT32_C(0x00000030)));
/* 0012dee4: move a1,s2 */ set(5,cpu(18));
/* 0012dee8: lwc1 f0,0x34(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000034)));
/* 0012deec: lui s0,0x30 */ set(16,sx(UINT32_C(0x00300000)));
/* 0012def0: lw a0,0x78(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000078)));
/* 0012def4: addiu s0,s0,-0x3630 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffc9d0)));
/* 0012def8: swc1 f2,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),f[2]);
/* 0012defc: swc1 f1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[1]);
/* 0012df00: swc1 f0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[0]);
/* 0012df04: jal 0x0010dea8 */ set(31,UINT64_C(0x0012df0c));/* delay 0012df08 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[3]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010dea8),UINT32_C(0x0012df04));
/* 0012df0c: lwc1 f5,0x10(sp) */ f[5]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0012df10: move a1,s2 */ set(5,cpu(18));
/* 0012df14: lwc1 f3,0x0(s0) */ f[3]=word(ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0012df18: lwc1 f2,0x4(s0) */ f[2]=word(ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0012df1c: lwc1 f0,0x8(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0012df20: sub.S f5,f5,f3 */ f[5]=EE_FPU_SUB_S(f[5],f[3]);
/* 0012df24: lwc1 f4,0x14(sp) */ f[4]=word(ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0012df28: lwc1 f1,0x18(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0012df2c: sub.S f4,f4,f2 */ f[4]=EE_FPU_SUB_S(f[4],f[2]);
/* 0012df30: lw a0,0x78(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000078)));
/* 0012df34: sub.S f1,f1,f0 */ f[1]=EE_FPU_SUB_S(f[1],f[0]);
/* 0012df38: add.S f3,f3,f5 */ f[3]=EE_FPU_ADD_S(f[3],f[5]);
/* 0012df3c: add.S f2,f2,f4 */ f[2]=EE_FPU_ADD_S(f[2],f[4]);
/* 0012df40: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 0012df44: swc1 f3,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[3]);
/* 0012df48: swc1 f2,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[2]);
/* 0012df4c: jal 0x0010dea8 */ set(31,UINT64_C(0x0012df54));/* delay 0012df50 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[0]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010dea8),UINT32_C(0x0012df4c));
/* 0012df54: lq v0,0x0(sp) */ requestLq(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012df58: sq v0,0x0(s1) */ sq(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0012df5c: lq v0,0x0(s2) */ requestLq(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0012df60: sq v0,0x0(s0) */ sq(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0012df64: lw a0,0x78(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000078)));
/* 0012df68: lw v1,0x10(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0012df6c: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0012df70: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0012df78));/* delay 0012df74 */ nocturneFieldInfControllerNativeIndirect(target,UINT32_C(0x0012df70));}
/* 0012df78: lwc1 f0,0x0(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012df7c: lwc1 f12,0x10(sp) */ f[12]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0012df80: lwc1 f2,0x4(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0012df84: mov.S f14,f0 */ f[14]=f[0];
/* 0012df88: lwc1 f4,0x14(sp) */ f[4]=word(ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0012df8c: sub.S f0,f0,f12 */ f[0]=EE_FPU_SUB_S(f[0],f[12]);
/* 0012df90: lwc1 f1,0x8(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0012df94: sub.S f2,f2,f4 */ f[2]=EE_FPU_SUB_S(f[2],f[4]);
/* 0012df98: lwc1 f3,0x18(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0012df9c: mov.S f15,f1 */ f[15]=f[1];
/* 0012dfa0: mul.S f0,f0,f0 */ f[0]=EE_FPU_MUL_S(f[0],f[0]);
/* 0012dfa4: mov.S f13,f3 */ f[13]=f[3];
/* 0012dfa8: sub.S f1,f1,f3 */ f[1]=EE_FPU_SUB_S(f[1],f[3]);
/* 0012dfac: mul.S f2,f2,f2 */ f[2]=EE_FPU_MUL_S(f[2],f[2]);
/* 0012dfb0: mul.S f1,f1,f1 */ f[1]=EE_FPU_MUL_S(f[1],f[1]);
/* 0012dfb4: add.S f0,f0,f2 */ f[0]=EE_FPU_ADD_S(f[0],f[2]);
/* 0012dfb8: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 0012dfbc: sqrt.S f0,f0 */ f[0]=EE_FPU_SQRT_S(f[0]);
/* 0012dfc0: jal 0x0012c528 */ set(31,UINT64_C(0x0012dfc8));/* delay 0012dfc4 */ sw(ea(28,(int32_t)UINT32_C(0xffffa8f8)),f[0]);body_0012c528();
/* 0012dfc8: add.S f0,f0,f20 */ f[0]=EE_FPU_ADD_S(f[0],f[20]);
/* 0012dfcc: lwc1 f20,0x48(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0012dfd0: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0012dfd4: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0012dfd8: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0012dfdc: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0012dfe0: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0012dfe4: swc1 f0,-0x570c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa8f4)),f[0]);
/* 0012dfe8: jr ra */ {uint64_t target=cpu(31);/* delay 0012dfec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_0012efd8(void){
uint64_t incoming=cpu(31);
/* 0012efd8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0012efdc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012efe0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0012efe4: jal 0x0010e548 */ set(31,UINT64_C(0x0012efec));/* delay 0012efe8 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e548),UINT32_C(0x0012efe4));
/* 0012efec: jal 0x0010f1b0 */ set(31,UINT64_C(0x0012eff4));/* delay 0012eff0 */ set(4,cpu(2));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f1b0),UINT32_C(0x0012efec));
/* 0012eff4: jal 0x00122608 */ set(31,UINT64_C(0x0012effc));/* delay 0012eff8 */ set(16,cpu(2));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00122608),UINT32_C(0x0012eff4));
/* 0012effc: xor v0,v0,s0 */ set(2,cpu(2)^cpu(16));
/* 0012f000: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0012f004: movz s0,zero,v0 */ if(cpu(2)==0){set(16,cpu(0));}
/* 0012f008: move v0,s0 */ set(2,cpu(16));
/* 0012f00c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0012f010: jr ra */ {uint64_t target=cpu(31);/* delay 0012f014 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001303a0(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 001303a0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001303a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001303a8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001303ac: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001303b0: move s2,a1 */ set(18,cpu(5));
/* 001303b4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001303b8: move s3,a0 */ set(19,cpu(4));
/* 001303bc: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001303c0: move s4,zero */ set(20,cpu(0));
/* 001303c4: swc1 f20,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);
/* 001303c8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001303cc: jal 0x001225e8 */ set(31,UINT64_C(0x001303d4));/* delay 001303d0 */ f[20]=f[12];nocturneFieldInfControllerNativeExternal(UINT32_C(0x001225e8),UINT32_C(0x001303cc));
/* 001303d4: move s1,v0 */ set(17,cpu(2));
/* 001303d8: jal 0x00110350 */ set(31,UINT64_C(0x001303e0));/* delay 001303dc */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));body_00110350();
/* 001303e0: move s0,v0 */ set(16,cpu(2));
/* 001303e4: lw v0,0x4(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 001303e8: beq v0,zero,0x001303fc */ {int taken=(cpu(2)==cpu(0));/* delay 001303ec */ set(4,cpu(2));if(taken){goto L_001303fc;}}
/* 001303f0: jal 0x00110350 */ set(31,UINT64_C(0x001303f8));/* delay 001303f4 */ body_00110350();
/* 001303f8: move s4,v0 */ set(20,cpu(2));
L_001303fc:;
/* 001303fc: beql s3,s2,0x001304c4 */ {int taken=(cpu(19)==cpu(18));if(taken){/* delay 00130400 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001304c4;}}
/* 00130404: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 00130408: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0013040c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00130410: jal 0x00123370 */ set(31,UINT64_C(0x00130418));/* delay 00130414 */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),f[0]);body_00123370();
/* 00130418: beq v0,zero,0x00130454 */ {int taken=(cpu(2)==cpu(0));/* delay 0013041c */ set(3,sx(UINT32_C(0x00300000)));if(taken){goto L_00130454;}}
/* 00130420: lw v0,-0x3ef0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0xffffc110)));
/* 00130424: andi v0,v0,0x2 */ set(2,cpu(2)&UINT32_C(0x00000002));
/* 00130428: beq v0,zero,0x00130448 */ {int taken=(cpu(2)==cpu(0));/* delay 0013042c */ set(4,cpu(16));if(taken){goto L_00130448;}}
/* 00130430: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 00130434: jal 0x001dd538 */ set(31,UINT64_C(0x0013043c));/* delay 00130438 */ set(6,sx(UINT32_C(0x00000001)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x001dd538),UINT32_C(0x00130434));
/* 0013043c: b 0x00130458 */ /* delay 00130440 */ set(4,cpu(16));goto L_00130458;
L_00130448:;
/* 00130448: li a1,0x3 */ set(5,sx(UINT32_C(0x00000003)));
/* 0013044c: jal 0x001dd538 */ set(31,UINT64_C(0x00130454));/* delay 00130450 */ set(6,cpu(0));nocturneFieldInfControllerNativeExternal(UINT32_C(0x001dd538),UINT32_C(0x0013044c));
L_00130454:;
/* 00130454: move a0,s0 */ set(4,cpu(16));
L_00130458:;
/* 00130458: move a1,zero */ set(5,cpu(0));
/* 0013045c: move a2,s2 */ set(6,cpu(18));
/* 00130460: mov.S f12,f20 */ f[12]=f[20];
/* 00130464: jal 0x001dd578 */ set(31,UINT64_C(0x0013046c));/* delay 00130468 */ f[13]=f[20];body_001dd578();
/* 0013046c: mov.S f12,f20 */ f[12]=f[20];
/* 00130470: lw v0,0x4(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 00130474: move a0,s4 */ set(4,cpu(20));
/* 00130478: move a2,s2 */ set(6,cpu(18));
/* 0013047c: move a1,zero */ set(5,cpu(0));
/* 00130480: beq v0,zero,0x001304c0 */ {int taken=(cpu(2)==cpu(0));/* delay 00130484 */ f[13]=f[12];if(taken){goto L_001304c0;}}
/* 00130488: lw v0,0x1c(s4) */ lw(2,ea(20,(int32_t)UINT32_C(0x0000001c)));
/* 0013048c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00130490: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00130494: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00130498: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013049c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001304a0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001304a4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001304a8: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001304ac: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001304b0: swc1 f0,0x20(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),f[0]);
/* 001304b4: j 0x001dd578 */ /* delay 001304b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);body_001dd578();return;
L_001304c0:;
/* 001304c0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001304c4:;
/* 001304c4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001304c8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001304cc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001304d0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001304d4: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001304d8: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001304dc: jr ra */ {uint64_t target=cpu(31);/* delay 001304e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_00134df8(void){
uint64_t incoming=cpu(31);
/* 00134df8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00134dfc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00134e00: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00134e04: jal 0x001225e8 */ set(31,UINT64_C(0x00134e0c));/* delay 00134e08 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x001225e8),UINT32_C(0x00134e04));
/* 00134e0c: move s0,v0 */ set(16,cpu(2));
/* 00134e10: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00134e14: jal 0x00110138 */ set(31,UINT64_C(0x00134e1c));/* delay 00134e18 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00110138),UINT32_C(0x00134e14));
/* 00134e1c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00134e20: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00134e24: beq v0,zero,0x00134e34 */ {int taken=(cpu(2)==cpu(0));/* delay 00134e28 */ set(4,cpu(2));if(taken){goto L_00134e34;}}
/* 00134e2c: jal 0x00110138 */ set(31,UINT64_C(0x00134e34));/* delay 00134e30 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x00110138),UINT32_C(0x00134e2c));
L_00134e34:;
/* 00134e34: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00134e38: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00134e3c: j 0x00135318 */ /* delay 00134e40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00135318();return;
}
static void body_00134e48(void){
uint64_t incoming=cpu(31);
/* 00134e48: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00134e4c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00134e50: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00134e54: jal 0x001225e8 */ set(31,UINT64_C(0x00134e5c));/* delay 00134e58 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x001225e8),UINT32_C(0x00134e54));
/* 00134e5c: move s0,v0 */ set(16,cpu(2));
/* 00134e60: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00134e64: jal 0x00110168 */ set(31,UINT64_C(0x00134e6c));/* delay 00134e68 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00110168),UINT32_C(0x00134e64));
/* 00134e6c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00134e70: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00134e74: beq v0,zero,0x00134e90 */ {int taken=(cpu(2)==cpu(0));/* delay 00134e78 */ set(4,cpu(2));if(taken){goto L_00134e90;}}
/* 00134e7c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00134e80: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00134e84: j 0x00110168 */ /* delay 00134e88 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneFieldInfControllerNativeExternal(UINT32_C(0x00110168),UINT32_C(0x00134e84));return;
L_00134e90:;
/* 00134e90: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00134e94: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00134e98: jr ra */ {uint64_t target=cpu(31);/* delay 00134e9c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00135318(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00135318: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 0013531c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00135320: lw v0,-0x407c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0xffffbf84)));
/* 00135324: slti v0,v0,0xa */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 00135328: bne v0,zero,0x00135370 */ {int taken=(cpu(2)!=cpu(0));/* delay 0013532c */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00135370;}}
/* 00135330: jal 0x0010e548 */ set(31,UINT64_C(0x00135338));/* delay 00135334 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e548),UINT32_C(0x00135330));
/* 00135338: jal 0x0010f1f8 */ set(31,UINT64_C(0x00135340));/* delay 0013533c */ set(4,cpu(2));body_0010f1f8();
/* 00135340: beq v0,zero,0x00135370 */ {int taken=(cpu(2)==cpu(0));/* delay 00135344 */ set(4,cpu(2));if(taken){goto L_00135370;}}
/* 00135348: jal 0x00112a30 */ set(31,UINT64_C(0x00135350));/* delay 0013534c */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x00112a30),UINT32_C(0x00135348));
/* 00135350: li a1,0x9 */ set(5,sx(UINT32_C(0x00000009)));
/* 00135354: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 00135358: clear f12 */ f[12]=0;
/* 0013535c: lh a0,0x12(v1) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000012))));
/* 00135360: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00135364: j 0x001303a0 */ /* delay 00135368 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001303a0();return;
L_00135370:;
/* 00135370: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00135374: jr ra */ {uint64_t target=cpu(31);/* delay 00135378 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00137b40(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00137b40: lwc1 f0,0x0(a1) */ f[0]=word(ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00137b44: lwc1 f2,0x0(a0) */ f[2]=word(ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00137b48: lwc1 f3,0x4(a0) */ f[3]=word(ea(4,(int32_t)UINT32_C(0x00000004)));
/* 00137b4c: lwc1 f4,0x4(a1) */ f[4]=word(ea(5,(int32_t)UINT32_C(0x00000004)));
/* 00137b50: mul.S f2,f2,f0 */ f[2]=EE_FPU_MUL_S(f[2],f[0]);
/* 00137b54: lwc1 f1,0x8(a1) */ f[1]=word(ea(5,(int32_t)UINT32_C(0x00000008)));
/* 00137b58: mul.S f3,f3,f4 */ f[3]=EE_FPU_MUL_S(f[3],f[4]);
/* 00137b5c: lwc1 f0,0x8(a0) */ f[0]=word(ea(4,(int32_t)UINT32_C(0x00000008)));
/* 00137b60: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 00137b64: add.S f2,f2,f3 */ f[2]=EE_FPU_ADD_S(f[2],f[3]);
/* 00137b68: jr ra */ {uint64_t target=cpu(31);/* delay 00137b6c */ f[0]=EE_FPU_ADD_S(f[2],f[0]);checkReturn(target,incoming);return;}
}
static void body_0013b928(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 0013b928: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 0013b92c: swc1 f20,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),f[20]);
/* 0013b930: mov.S f20,f12 */ f[20]=f[12];
/* 0013b934: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0013b938: move s0,a3 */ set(16,cpu(7));
/* 0013b93c: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0013b940: move s4,a1 */ set(20,cpu(5));
/* 0013b944: swc1 f21,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),f[21]);
/* 0013b948: mov.S f21,f20 */ f[21]=f[20];
/* 0013b94c: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0013b950: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0013b954: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0013b958: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0013b95c: bne a0,zero,0x0013b988 */ {int taken=(cpu(4)!=cpu(0));/* delay 0013b960 */ sw(ea(29,(int32_t)UINT32_C(0x00000060)),f[22]);if(taken){goto L_0013b988;}}
/* 0013b964: lwc1 f1,0x8(a2) */ f[1]=word(ea(6,(int32_t)UINT32_C(0x00000008)));
/* 0013b968: lwc1 f0,0x4(a2) */ f[0]=word(ea(6,(int32_t)UINT32_C(0x00000004)));
/* 0013b96c: swc1 f1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[1]);
/* 0013b970: swc1 f0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[0]);
/* 0013b974: sw zero,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0013b978: swc1 f0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[0]);
/* 0013b97c: b 0x0013b9d0 */ /* delay 0013b980 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[1]);goto L_0013b9d0;
L_0013b988:;
/* 0013b988: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0013b98c: bnel a0,v0,0x0013b9b8 */ {int taken=(cpu(4)!=cpu(2));if(taken){/* delay 0013b990 */ f[1]=word(ea(6,(int32_t)UINT32_C(0x00000004)));goto L_0013b9b8;}}
/* 0013b994: lwc1 f1,0x8(a2) */ f[1]=word(ea(6,(int32_t)UINT32_C(0x00000008)));
/* 0013b998: lwc1 f0,0x0(a2) */ f[0]=word(ea(6,(int32_t)UINT32_C(0x00000000)));
/* 0013b99c: swc1 f1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[1]);
/* 0013b9a0: swc1 f0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[0]);
/* 0013b9a4: swc1 f0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[0]);
/* 0013b9a8: sw zero,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 0013b9ac: b 0x0013b9d0 */ /* delay 0013b9b0 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[1]);goto L_0013b9d0;
L_0013b9b8:;
/* 0013b9b8: lwc1 f0,0x0(a2) */ f[0]=word(ea(6,(int32_t)UINT32_C(0x00000000)));
/* 0013b9bc: swc1 f1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[1]);
/* 0013b9c0: swc1 f0,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[0]);
/* 0013b9c4: swc1 f0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[0]);
/* 0013b9c8: swc1 f1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[1]);
/* 0013b9cc: sw zero,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
L_0013b9d0:;
/* 0013b9d0: blez s4,0x0013ba8c */ {int taken=((int64_t)cpu(20)<=0);/* delay 0013b9d4 */ set(19,cpu(0));if(taken){goto L_0013ba8c;}}
/* 0013b9d8: clear f22 */ f[22]=0;
/* 0013b9dc: addiu s2,s0,0x58 */ set(18,sx((uint32_t)cpu(16)+UINT32_C(0x00000058)));
/* 0013b9e0: addiu s1,s0,0x18 */ set(17,sx((uint32_t)cpu(16)+UINT32_C(0x00000018)));
/* 0013b9e4: move a1,s1 */ set(5,cpu(17));
L_0013b9e8:;
/* 0013b9e8: addiu s1,s1,0x10 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000010)));
/* 0013b9ec: jal 0x00137b40 */ set(31,UINT64_C(0x0013b9f4));/* delay 0013b9f0 */ set(4,cpu(29));body_00137b40();
/* 0013b9f4: lwc1 f1,0x0(s2) */ f[1]=word(ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0013b9f8: sub.S f3,f0,f1 */ f[3]=EE_FPU_SUB_S(f[0],f[1]);
/* 0013b9fc: add.S f4,f3,f20 */ f[4]=EE_FPU_ADD_S(f[3],f[20]);
/* 0013ba00: c.lt.S f4,f22 */ (void)(EE_FPU_COMPARE_S(f[4],f[22],1)!=0);
/* 0013ba04: bc1t 0x0013ba60 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)!=0);/* delay 0013ba08 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000004)));if(taken){goto L_0013ba60;}}
/* 0013ba0c: lwc1 f0,0x68(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000068)));
/* 0013ba10: lwc1 f2,0x10(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0013ba14: sub.S f0,f0,f20 */ f[0]=EE_FPU_SUB_S(f[0],f[20]);
/* 0013ba18: c.lt.S f2,f0 */ (void)(EE_FPU_COMPARE_S(f[2],f[0],1)!=0);
/* 0013ba1c: bc1t 0x0013ba60 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)!=0);/* delay 0013ba20 */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000014)));if(taken){goto L_0013ba60;}}
/* 0013ba24: lwc1 f0,0x6c(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x0000006c)));
/* 0013ba28: sub.S f0,f0,f20 */ f[0]=EE_FPU_SUB_S(f[0],f[20]);
/* 0013ba2c: c.lt.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],1)!=0);
/* 0013ba30: bc1t 0x0013ba60 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)!=0);/* delay 0013ba34 */ if(taken){goto L_0013ba60;}}
/* 0013ba38: lwc1 f0,0x70(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000070)));
/* 0013ba3c: add.S f0,f0,f20 */ f[0]=EE_FPU_ADD_S(f[0],f[20]);
/* 0013ba40: c.lt.S f0,f2 */ (void)(EE_FPU_COMPARE_S(f[0],f[2],1)!=0);
/* 0013ba44: bc1t 0x0013ba60 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)!=0);/* delay 0013ba48 */ if(taken){goto L_0013ba60;}}
/* 0013ba4c: lwc1 f0,0x74(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x00000074)));
/* 0013ba50: add.S f0,f0,f20 */ f[0]=EE_FPU_ADD_S(f[0],f[20]);
/* 0013ba54: c.lt.S f0,f1 */ (void)(EE_FPU_COMPARE_S(f[0],f[1],1)!=0);
/* 0013ba58: bc1f 0x0013ba70 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0013ba5c */ if(taken){goto L_0013ba70;}}
L_0013ba60:;
/* 0013ba60: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
/* 0013ba64: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0013ba68: b 0x0013baac */ /* delay 0013ba6c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));goto L_0013baac;
L_0013ba70:;
/* 0013ba70: c.lt.S f3,f22 */ (void)(EE_FPU_COMPARE_S(f[3],f[22],1)!=0);
/* 0013ba74: bc1tl 0x0013ba7c */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)!=0);if(taken){/* delay 0013ba78 */ f[21]=f[4];goto L_0013ba7c;}}
L_0013ba7c:;
/* 0013ba7c: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 0013ba80: slt v0,s3,s4 */ set(2,(int64_t)cpu(19)<(int64_t)cpu(20));
/* 0013ba84: bne v0,zero,0x0013b9e8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0013ba88 */ set(5,cpu(17));if(taken){goto L_0013b9e8;}}
L_0013ba8c:;
/* 0013ba8c: lwc1 f0,-0x7d00(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8300)));
/* 0013ba90: c.lt.S f21,f0 */ (void)(EE_FPU_COMPARE_S(f[21],f[0],1)!=0);
/* 0013ba94: bc1f 0x0013baa8 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0013ba98 */ f[0]=f[21];if(taken){goto L_0013baa8;}}
/* 0013ba9c: lui at,0xbf80 */ set(1,sx(UINT32_C(0xbf800000)));
/* 0013baa0: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 0013baa4: mov.S f0,f21 */ f[0]=f[21];
L_0013baa8:;
/* 0013baa8: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
L_0013baac:;
/* 0013baac: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0013bab0: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0013bab4: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0013bab8: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0013babc: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0013bac0: lwc1 f22,0x60(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0013bac4: lwc1 f21,0x58(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0013bac8: lwc1 f20,0x50(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0013bacc: jr ra */ {uint64_t target=cpu(31);/* delay 0013bad0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
static void body_0013bad8(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 0013bad8: addiu sp,sp,-0xc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff40)));
/* 0013badc: sd s8,0xa0(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0013bae0: lui s8,0x30 */ set(30,sx(UINT32_C(0x00300000)));
/* 0013bae4: sd s2,0x70(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0013bae8: move s2,a0 */ set(18,cpu(4));
/* 0013baec: sd s3,0x78(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0013baf0: move s3,a1 */ set(19,cpu(5));
/* 0013baf4: sd s5,0x88(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0013baf8: sd s6,0x90(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0013bafc: move s6,a2 */ set(22,cpu(6));
/* 0013bb00: sd s7,0x98(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0013bb04: li s7,-0x1 */ set(23,sx(UINT32_C(0xffffffff)));
/* 0013bb08: sd s0,0x60(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0013bb0c: sd s1,0x68(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0013bb10: sd s4,0x80(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0013bb14: sd ra,0xa8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0013bb18: swc1 f21,0xb8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b8)),f[21]);
/* 0013bb1c: jal 0x0010e588 */ set(31,UINT64_C(0x0013bb24));/* delay 0013bb20 */ sw(ea(29,(int32_t)UINT32_C(0x000000b0)),f[20]);nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e588),UINT32_C(0x0013bb1c));
/* 0013bb24: addiu v1,s8,-0x4080 */ set(3,sx((uint32_t)cpu(30)+UINT32_C(0xffffbf80)));
/* 0013bb28: move s5,v0 */ set(21,cpu(2));
/* 0013bb2c: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0013bb30: addiu v0,v0,-0xc8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffff38)));
/* 0013bb34: sltiu v0,v0,0x12c */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000012c));
/* 0013bb38: bnel v0,zero,0x0013bbb4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0013bb3c */ f[4]=word(ea(18,(int32_t)UINT32_C(0x00000008)));goto L_0013bbb4;}}
/* 0013bb40: move a0,s5 */ set(4,cpu(21));
/* 0013bb44: jal 0x0010f270 */ set(31,UINT64_C(0x0013bb4c));/* delay 0013bb48 */ set(5,sx(UINT32_C(0x00000006)));body_0010f270();
/* 0013bb4c: move s1,v0 */ set(17,cpu(2));
/* 0013bb50: jal 0x0010ebc8 */ set(31,UINT64_C(0x0013bb58));/* delay 0013bb54 */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010ebc8),UINT32_C(0x0013bb50));
/* 0013bb58: beql v0,zero,0x0013bbb4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0013bb5c */ f[4]=word(ea(18,(int32_t)UINT32_C(0x00000008)));goto L_0013bbb4;}}
/* 0013bb60: jal 0x0010ec58 */ set(31,UINT64_C(0x0013bb68));/* delay 0013bb64 */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010ec58),UINT32_C(0x0013bb60));
/* 0013bb68: li s4,0x4 */ set(20,sx(UINT32_C(0x00000004)));
/* 0013bb6c: nop  */ 
L_0013bb70:;
/* 0013bb70: jal 0x0010ec20 */ set(31,UINT64_C(0x0013bb78));/* delay 0013bb74 */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010ec20),UINT32_C(0x0013bb70));
/* 0013bb78: move s0,v0 */ set(16,cpu(2));
/* 0013bb7c: jal 0x00113458 */ set(31,UINT64_C(0x0013bb84));/* delay 0013bb80 */ set(4,cpu(16));body_00113458();
/* 0013bb84: move a0,s0 */ set(4,cpu(16));
/* 0013bb88: bne v0,s4,0x0013bb98 */ {int taken=(cpu(2)!=cpu(20));/* delay 0013bb8c */ set(5,sx(UINT32_C(0x00000003)));if(taken){goto L_0013bb98;}}
/* 0013bb90: jal 0x00113448 */ set(31,UINT64_C(0x0013bb98));/* delay 0013bb94 */ body_00113448();
L_0013bb98:;
/* 0013bb98: jal 0x0010ec78 */ set(31,UINT64_C(0x0013bba0));/* delay 0013bb9c */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010ec78),UINT32_C(0x0013bb98));
/* 0013bba0: bne v0,zero,0x0013bb70 */ {int taken=(cpu(2)!=cpu(0));/* delay 0013bba4 */ if(taken){goto L_0013bb70;}}
/* 0013bba8: jal 0x0010e748 */ set(31,UINT64_C(0x0013bbb0));/* delay 0013bbac */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e748),UINT32_C(0x0013bba8));
/* 0013bbb0: lwc1 f4,0x8(s2) */ f[4]=word(ea(18,(int32_t)UINT32_C(0x00000008)));
L_0013bbb4:;
/* 0013bbb4: move s4,zero */ set(20,cpu(0));
/* 0013bbb8: lwc1 f5,0x8(s3) */ f[5]=word(ea(19,(int32_t)UINT32_C(0x00000008)));
/* 0013bbbc: lwc1 f0,0x0(s2) */ f[0]=word(ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0013bbc0: lwc1 f1,0x4(s2) */ f[1]=word(ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0013bbc4: lwc1 f2,0x0(s3) */ f[2]=word(ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0013bbc8: lwc1 f3,0x4(s3) */ f[3]=word(ea(19,(int32_t)UINT32_C(0x00000004)));
/* 0013bbcc: lw a2,-0x53d0(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffac30)));
/* 0013bbd0: swc1 f0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[0]);
/* 0013bbd4: swc1 f1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[1]);
/* 0013bbd8: swc1 f4,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[4]);
/* 0013bbdc: swc1 f2,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[2]);
/* 0013bbe0: swc1 f3,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[3]);
/* 0013bbe4: blez a2,0x0013bf7c */ {int taken=((int64_t)cpu(6)<=0);/* delay 0013bbe8 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[5]);if(taken){goto L_0013bf7c;}}
/* 0013bbec: move s0,zero */ set(16,cpu(0));
L_0013bbf0:;
/* 0013bbf0: lw v0,-0x53d4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffac2c)));
/* 0013bbf4: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0013bbf8: addu a1,s0,v0 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0013bbfc: lh v1,0x0(a1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 0013bc00: bne v1,a0,0x0013bc20 */ {int taken=(cpu(3)!=cpu(4));/* delay 0013bc04 */ lw(3,ea(5,(int32_t)UINT32_C(0x000000d4)));if(taken){goto L_0013bc20;}}
/* 0013bc08: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0013bc0c: andi v0,v0,0x100 */ set(2,cpu(2)&UINT32_C(0x00000100));
/* 0013bc10: beql v0,zero,0x0013bf70 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0013bc14 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));goto L_0013bf70;}}
/* 0013bc18: b 0x0013bc24 */ /* delay 0013bc1c */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_0013bc24;
L_0013bc20:;
/* 0013bc20: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
L_0013bc24:;
/* 0013bc24: andi v0,v0,0xa01 */ set(2,cpu(2)&UINT32_C(0x00000a01));
/* 0013bc28: bnel v0,zero,0x0013bf70 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0013bc2c */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));goto L_0013bf70;}}
/* 0013bc30: addiu v0,s8,-0x4080 */ set(2,sx((uint32_t)cpu(30)+UINT32_C(0xffffbf80)));
/* 0013bc34: lw a2,0xdc(a1) */ lw(6,ea(5,(int32_t)UINT32_C(0x000000dc)));
/* 0013bc38: lw a1,0x8(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 0013bc3c: lw a0,0x4(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 0013bc40: jal 0x001207c0 */ set(31,UINT64_C(0x0013bc48));/* delay 0013bc44 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));body_001207c0();
/* 0013bc48: bne v0,zero,0x0013bf6c */ {int taken=(cpu(2)!=cpu(0));/* delay 0013bc4c */ lw(6,ea(28,(int32_t)UINT32_C(0xffffac30)));if(taken){goto L_0013bf6c;}}
/* 0013bc50: lw a1,-0x53d4(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffac2c)));
/* 0013bc54: addu v0,s0,a1 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 0013bc58: lw v0,0xd0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x000000d0)));
/* 0013bc5c: beq v0,zero,0x0013bcd0 */ {int taken=(cpu(2)==cpu(0));/* delay 0013bc60 */ set(18,sx(UINT32_C(0x00000001)));if(taken){goto L_0013bcd0;}}
/* 0013bc64: lw v0,0x1c(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x0000001c)));
/* 0013bc68: lwc1 f1,0x0(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013bc6c: lwc1 f0,0x40(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000040)));
/* 0013bc70: lwc1 f2,0x4(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0013bc74: sub.S f1,f1,f0 */ f[1]=EE_FPU_SUB_S(f[1],f[0]);
/* 0013bc78: lwc1 f3,0x8(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013bc7c: lwc1 f4,0x10(sp) */ f[4]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0013bc80: lwc1 f5,0x14(sp) */ f[5]=word(ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0013bc84: lwc1 f6,0x18(sp) */ f[6]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0013bc88: swc1 f1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[1]);
/* 0013bc8c: lwc1 f0,0x44(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000044)));
/* 0013bc90: sub.S f2,f2,f0 */ f[2]=EE_FPU_SUB_S(f[2],f[0]);
/* 0013bc94: swc1 f2,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[2]);
/* 0013bc98: lwc1 f0,0x48(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000048)));
/* 0013bc9c: sub.S f3,f3,f0 */ f[3]=EE_FPU_SUB_S(f[3],f[0]);
/* 0013bca0: swc1 f3,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[3]);
/* 0013bca4: lwc1 f0,0x40(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000040)));
/* 0013bca8: sub.S f4,f4,f0 */ f[4]=EE_FPU_SUB_S(f[4],f[0]);
/* 0013bcac: swc1 f4,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[4]);
/* 0013bcb0: lwc1 f0,0x44(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000044)));
/* 0013bcb4: sub.S f5,f5,f0 */ f[5]=EE_FPU_SUB_S(f[5],f[0]);
/* 0013bcb8: swc1 f5,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[5]);
/* 0013bcbc: lwc1 f0,0x48(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000048)));
/* 0013bcc0: sub.S f6,f6,f0 */ f[6]=EE_FPU_SUB_S(f[6],f[0]);
/* 0013bcc4: b 0x0013bcd4 */ /* delay 0013bcc8 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[6]);goto L_0013bcd4;
L_0013bcd0:;
/* 0013bcd0: move s2,zero */ set(18,cpu(0));
L_0013bcd4:;
/* 0013bcd4: lwc1 f2,0x10(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0013bcd8: addiu s1,sp,0x30 */ set(17,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 0013bcdc: lwc1 f1,0x18(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0013bce0: addu a1,a1,s0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(16)));
/* 0013bce4: lwc1 f4,0x0(sp) */ f[4]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013bce8: addiu a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000004)));
/* 0013bcec: lwc1 f5,0x4(sp) */ f[5]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0013bcf0: move a0,s1 */ set(4,cpu(17));
/* 0013bcf4: lwc1 f3,0x8(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013bcf8: lwc1 f0,0x14(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0013bcfc: swc1 f2,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),f[2]);
/* 0013bd00: swc1 f1,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),f[1]);
/* 0013bd04: swc1 f4,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[4]);
/* 0013bd08: swc1 f5,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),f[5]);
/* 0013bd0c: swc1 f3,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[3]);
/* 0013bd10: jal 0x00137b40 */ set(31,UINT64_C(0x0013bd18));/* delay 0013bd14 */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),f[0]);body_00137b40();
/* 0013bd18: lw a1,-0x53d4(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffac2c)));
/* 0013bd1c: addiu a0,sp,0x40 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
/* 0013bd20: addu a1,s0,a1 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 0013bd24: lwc1 f1,0x14(a1) */ f[1]=word(ea(5,(int32_t)UINT32_C(0x00000014)));
/* 0013bd28: addiu a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000004)));
/* 0013bd2c: jal 0x00137b40 */ set(31,UINT64_C(0x0013bd34));/* delay 0013bd30 */ f[20]=EE_FPU_SUB_S(f[0],f[1]);body_00137b40();
/* 0013bd34: clear f2 */ f[2]=0;
/* 0013bd38: lw v1,-0x53d4(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffac2c)));
/* 0013bd3c: c.lt.S f20,f2 */ (void)(EE_FPU_COMPARE_S(f[20],f[2],1)!=0);
/* 0013bd40: addu v0,s0,v1 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 0013bd44: lwc1 f1,0x14(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000014)));
/* 0013bd48: bc1f 0x0013bd5c */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0013bd4c */ f[0]=EE_FPU_SUB_S(f[0],f[1]);if(taken){goto L_0013bd5c;}}
/* 0013bd50: c.le.S f2,f0 */ (void)(EE_FPU_COMPARE_S(f[2],f[0],2)!=0);
/* 0013bd54: bc1t 0x0013bd74 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)!=0);/* delay 0013bd58 */ if(taken){goto L_0013bd74;}}
L_0013bd5c:;
/* 0013bd5c: c.lt.S f0,f2 */ (void)(EE_FPU_COMPARE_S(f[0],f[2],1)!=0);
/* 0013bd60: bc1f 0x0013bee8 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0013bd64 */ if(taken){goto L_0013bee8;}}
/* 0013bd68: c.le.S f2,f20 */ (void)(EE_FPU_COMPARE_S(f[2],f[20],2)!=0);
/* 0013bd6c: bc1f 0x0013bee8 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0013bd70 */ if(taken){goto L_0013bee8;}}
L_0013bd74:;
/* 0013bd74: abs.S f20,f20 */ f[20]=f[20]&UINT32_C(0x7fffffff);
/* 0013bd78: abs.S f0,f0 */ f[0]=f[0]&UINT32_C(0x7fffffff);
/* 0013bd7c: add.S f21,f20,f0 */ f[21]=EE_FPU_ADD_S(f[20],f[0]);
/* 0013bd80: lwc1 f0,0x44(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000044)));
/* 0013bd84: lwc1 f5,0x30(sp) */ f[5]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0013bd88: addu v0,s0,v1 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 0013bd8c: lwc1 f6,0x34(sp) */ f[6]=word(ea(29,(int32_t)UINT32_C(0x00000034)));
/* 0013bd90: move a2,s1 */ set(6,cpu(17));
/* 0013bd94: lwc1 f3,0x38(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0013bd98: move a3,v0 */ set(7,cpu(2));
/* 0013bd9c: nop  */ 
/* 0013bda0: nop  */ 
/* 0013bda4: div.S f7,f20,f21 */ f[7]=EE_FPU_DIV_S(f[20],f[21]);
/* 0013bda8: lwc1 f1,0x40(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0013bdac: lwc1 f2,0x48(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0013bdb0: sub.S f0,f0,f6 */ f[0]=EE_FPU_SUB_S(f[0],f[6]);
/* 0013bdb4: sub.S f1,f1,f5 */ f[1]=EE_FPU_SUB_S(f[1],f[5]);
/* 0013bdb8: swc1 f5,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),f[5]);
/* 0013bdbc: sub.S f2,f2,f3 */ f[2]=EE_FPU_SUB_S(f[2],f[3]);
/* 0013bdc0: swc1 f6,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),f[6]);
/* 0013bdc4: swc1 f3,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),f[3]);
/* 0013bdc8: swc1 f0,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[0]);
/* 0013bdcc: swc1 f1,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[1]);
/* 0013bdd0: lh a0,0x0(v0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 0013bdd4: mul.S f1,f1,f7 */ f[1]=EE_FPU_MUL_S(f[1],f[7]);
/* 0013bdd8: lh a1,0x2(v0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000002))));
/* 0013bddc: mul.S f4,f2,f7 */ f[4]=EE_FPU_MUL_S(f[2],f[7]);
/* 0013bde0: lui at,0x4000 */ set(1,sx(UINT32_C(0x40000000)));
/* 0013bde4: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0013bde8: mul.S f0,f0,f7 */ f[0]=EE_FPU_MUL_S(f[0],f[7]);
/* 0013bdec: swc1 f2,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[2]);
/* 0013bdf0: add.S f5,f5,f1 */ f[5]=EE_FPU_ADD_S(f[5],f[1]);
/* 0013bdf4: add.S f3,f3,f4 */ f[3]=EE_FPU_ADD_S(f[3],f[4]);
/* 0013bdf8: add.S f6,f6,f0 */ f[6]=EE_FPU_ADD_S(f[6],f[0]);
/* 0013bdfc: swc1 f5,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[5]);
/* 0013be00: swc1 f3,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[3]);
/* 0013be04: jal 0x0013b928 */ set(31,UINT64_C(0x0013be0c));/* delay 0013be08 */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),f[6]);body_0013b928();
/* 0013be0c: mov.S f1,f0 */ f[1]=f[0];
/* 0013be10: clear f0 */ f[0]=0;
/* 0013be14: c.le.S f0,f1 */ (void)(EE_FPU_COMPARE_S(f[0],f[1],2)!=0);
/* 0013be18: bc1f 0x0013bee8 */ {int taken=(((nocturneFieldInfControllerNativeFcsr()>>23)&1u)==0);/* delay 0013be1c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffac2c)));if(taken){goto L_0013bee8;}}
/* 0013be20: addu a0,s0,v0 */ set(4,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0013be24: lw v1,0xd4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x000000d4)));
/* 0013be28: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0013be2c: andi v0,v0,0x400 */ set(2,cpu(2)&UINT32_C(0x00000400));
/* 0013be30: beq v0,zero,0x0013be68 */ {int taken=(cpu(2)==cpu(0));/* delay 0013be34 */ set(5,sx(UINT32_C(0x00000006)));if(taken){goto L_0013be68;}}
/* 0013be38: lhu v1,0x6(v1) */ set(3,half(ea(3,(int32_t)UINT32_C(0x00000006))));
/* 0013be3c: lw v0,0xd8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x000000d8)));
/* 0013be40: move a0,s5 */ set(4,cpu(21));
/* 0013be44: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 0013be48: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0013be4c: jal 0x0010f6e0 */ set(31,UINT64_C(0x0013be54));/* delay 0013be50 */ lw(6,ea(2,(int32_t)UINT32_C(0x00000004)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f6e0),UINT32_C(0x0013be4c));
/* 0013be54: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 0013be58: jal 0x00113448 */ set(31,UINT64_C(0x0013be60));/* delay 0013be5c */ set(4,cpu(2));body_00113448();
/* 0013be60: b 0x0013bee8 */ /* delay 0013be64 */ goto L_0013bee8;
L_0013be68:;
/* 0013be68: add.S f0,f20,f1 */ f[0]=EE_FPU_ADD_S(f[20],f[1]);
/* 0013be6c: lwc1 f1,0x44(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000044)));
/* 0013be70: lwc1 f4,0x50(sp) */ f[4]=word(ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0013be74: move s7,s4 */ set(23,cpu(20));
/* 0013be78: lwc1 f5,0x54(sp) */ f[5]=word(ea(29,(int32_t)UINT32_C(0x00000054)));
/* 0013be7c: lwc1 f3,0x58(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0013be80: nop  */ 
/* 0013be84: nop  */ 
/* 0013be88: div.S f7,f0,f21 */ f[7]=EE_FPU_DIV_S(f[0],f[21]);
/* 0013be8c: lwc1 f0,0x48(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0013be90: lwc1 f2,0x40(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0013be94: sub.S f1,f1,f5 */ f[1]=EE_FPU_SUB_S(f[1],f[5]);
/* 0013be98: sub.S f0,f0,f3 */ f[0]=EE_FPU_SUB_S(f[0],f[3]);
/* 0013be9c: sub.S f2,f2,f4 */ f[2]=EE_FPU_SUB_S(f[2],f[4]);
/* 0013bea0: swc1 f1,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[1]);
/* 0013bea4: swc1 f0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[0]);
/* 0013bea8: swc1 f2,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[2]);
/* 0013beac: mul.S f0,f0,f7 */ f[0]=EE_FPU_MUL_S(f[0],f[7]);
/* 0013beb0: mul.S f2,f2,f7 */ f[2]=EE_FPU_MUL_S(f[2],f[7]);
/* 0013beb4: mul.S f1,f1,f7 */ f[1]=EE_FPU_MUL_S(f[1],f[7]);
/* 0013beb8: add.S f3,f3,f0 */ f[3]=EE_FPU_ADD_S(f[3],f[0]);
/* 0013bebc: add.S f4,f4,f2 */ f[4]=EE_FPU_ADD_S(f[4],f[2]);
/* 0013bec0: add.S f5,f5,f1 */ f[5]=EE_FPU_ADD_S(f[5],f[1]);
/* 0013bec4: swc1 f3,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[3]);
/* 0013bec8: swc1 f4,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[4]);
/* 0013becc: swc1 f5,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[5]);
/* 0013bed0: swc1 f4,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),f[4]);
/* 0013bed4: swc1 f5,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),f[5]);
/* 0013bed8: swc1 f3,0x58(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),f[3]);
/* 0013bedc: swc1 f4,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[4]);
/* 0013bee0: swc1 f5,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),f[5]);
/* 0013bee4: swc1 f3,0x38(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),f[3]);
L_0013bee8:;
/* 0013bee8: beq s2,zero,0x0013bf68 */ {int taken=(cpu(18)==cpu(0));/* delay 0013beec */ lw(2,ea(28,(int32_t)UINT32_C(0xffffac2c)));if(taken){goto L_0013bf68;}}
/* 0013bef0: lwc1 f1,0x0(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013bef4: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0013bef8: lwc1 f2,0x4(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0013befc: lw v1,0xd0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x000000d0)));
/* 0013bf00: lwc1 f3,0x8(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013bf04: lw v0,0x1c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000001c)));
/* 0013bf08: lwc1 f4,0x10(sp) */ f[4]=word(ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0013bf0c: lwc1 f0,0x40(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000040)));
/* 0013bf10: lwc1 f5,0x14(sp) */ f[5]=word(ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0013bf14: add.S f1,f1,f0 */ f[1]=EE_FPU_ADD_S(f[1],f[0]);
/* 0013bf18: lwc1 f6,0x18(sp) */ f[6]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0013bf1c: lw a2,-0x53d0(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffac30)));
/* 0013bf20: swc1 f1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),f[1]);
/* 0013bf24: lwc1 f0,0x44(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000044)));
/* 0013bf28: add.S f2,f2,f0 */ f[2]=EE_FPU_ADD_S(f[2],f[0]);
/* 0013bf2c: swc1 f2,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),f[2]);
/* 0013bf30: lwc1 f0,0x48(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000048)));
/* 0013bf34: add.S f3,f3,f0 */ f[3]=EE_FPU_ADD_S(f[3],f[0]);
/* 0013bf38: swc1 f3,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[3]);
/* 0013bf3c: lwc1 f0,0x40(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000040)));
/* 0013bf40: add.S f4,f4,f0 */ f[4]=EE_FPU_ADD_S(f[4],f[0]);
/* 0013bf44: swc1 f4,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[4]);
/* 0013bf48: lwc1 f0,0x44(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000044)));
/* 0013bf4c: add.S f5,f5,f0 */ f[5]=EE_FPU_ADD_S(f[5],f[0]);
/* 0013bf50: swc1 f5,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[5]);
/* 0013bf54: lwc1 f0,0x48(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000048)));
/* 0013bf58: add.S f6,f6,f0 */ f[6]=EE_FPU_ADD_S(f[6],f[0]);
/* 0013bf5c: b 0x0013bf6c */ /* delay 0013bf60 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[6]);goto L_0013bf6c;
L_0013bf68:;
/* 0013bf68: lw a2,-0x53d0(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffac30)));
L_0013bf6c:;
/* 0013bf6c: addiu s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000001)));
L_0013bf70:;
/* 0013bf70: slt v0,s4,a2 */ set(2,(int64_t)cpu(20)<(int64_t)cpu(6));
/* 0013bf74: bne v0,zero,0x0013bbf0 */ {int taken=(cpu(2)!=cpu(0));/* delay 0013bf78 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000000e4)));if(taken){goto L_0013bbf0;}}
L_0013bf7c:;
/* 0013bf7c: lwc1 f0,0x0(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013bf80: move v0,s7 */ set(2,cpu(23));
/* 0013bf84: lwc1 f2,0x4(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0013bf88: lwc1 f1,0x8(sp) */ f[1]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013bf8c: ld s0,0x60(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0013bf90: swc1 f0,0x0(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000000)),f[0]);
/* 0013bf94: swc1 f1,0x8(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000008)),f[1]);
/* 0013bf98: swc1 f2,0x4(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000004)),f[2]);
/* 0013bf9c: ld s1,0x68(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0013bfa0: ld s2,0x70(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0013bfa4: ld s3,0x78(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0013bfa8: ld s4,0x80(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0013bfac: ld s5,0x88(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0013bfb0: ld s6,0x90(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0013bfb4: ld s7,0x98(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0013bfb8: ld s8,0xa0(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0013bfbc: ld ra,0xa8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0013bfc0: lwc1 f21,0xb8(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0013bfc4: lwc1 f20,0xb0(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0013bfc8: jr ra */ {uint64_t target=cpu(31);/* delay 0013bfcc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000c0)));checkReturn(target,incoming);return;}
}
static void body_0013c6f0(void){
uint64_t incoming=cpu(31);
/* 0013c6f0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0013c6f4: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0013c6f8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013c6fc: move s0,zero */ set(16,cpu(0));
/* 0013c700: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013c704: li s1,0xf */ set(17,sx(UINT32_C(0x0000000f)));
L_0013c708:;
/* 0013c708: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0013c70c: li a1,0x270f */ set(5,sx(UINT32_C(0x0000270f)));
/* 0013c710: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
/* 0013c714: addu a0,a0,s0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(16)));
/* 0013c718: jal 0x00243e28 */ set(31,UINT64_C(0x0013c720));/* delay 0013c71c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000a54)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00243e28),UINT32_C(0x0013c718));
/* 0013c720: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0013c724: li a1,0x270f */ set(5,sx(UINT32_C(0x0000270f)));
/* 0013c728: addu a0,a0,s0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(16)));
/* 0013c72c: jal 0x00243e50 */ set(31,UINT64_C(0x0013c734));/* delay 0013c730 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000a54)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00243e50),UINT32_C(0x0013c72c));
/* 0013c734: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0013c738: addu v1,s0,v1 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(3)));
/* 0013c73c: addiu s0,s0,0xec */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000000ec)));
/* 0013c740: bgez s1,0x0013c708 */ {int taken=((int64_t)cpu(17)>=0);/* delay 0013c744 */ sh(ea(3,(int32_t)UINT32_C(0x00000a62)),(uint16_t)cpu(0));if(taken){goto L_0013c708;}}
/* 0013c748: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013c74c: li a0,0x10 */ set(4,sx(UINT32_C(0x00000010)));
/* 0013c750: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013c754: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 0013c758: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0013c75c: li a2,0x3f */ set(6,sx(UINT32_C(0x0000003f)));
/* 0013c760: j 0x002c18d8 */ /* delay 0013c764 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002c18d8();return;
}
static void body_0013c860(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0013c860: lui v0,0x56 */ set(2,sx(UINT32_C(0x00560000)));
/* 0013c864: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0013c868: addiu t3,v0,-0x23d0 */ set(11,sx((uint32_t)cpu(2)+UINT32_C(0xffffdc30)));
/* 0013c86c: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0013c870: move t4,t3 */ set(12,cpu(11));
/* 0013c874: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013c878: sw zero,-0x53b8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac48)),(uint32_t)cpu(0));
/* 0013c87c: addiu t5,v0,-0x3160 */ set(13,sx((uint32_t)cpu(2)+UINT32_C(0xffffcea0)));
/* 0013c880: sw zero,-0x53a8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac58)),(uint32_t)cpu(0));
/* 0013c884: move t0,zero */ set(8,cpu(0));
/* 0013c888: sw zero,-0x53a4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac5c)),(uint32_t)cpu(0));
/* 0013c88c: li t2,-0x1 */ set(10,sx(UINT32_C(0xffffffff)));
/* 0013c890: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0013c894: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0013c898: addiu a1,t3,0x120 */ set(5,sx((uint32_t)cpu(11)+UINT32_C(0x00000120)));
/* 0013c89c: move a3,zero */ set(7,cpu(0));
/* 0013c8a0: addiu t1,t4,0x114 */ set(9,sx((uint32_t)cpu(12)+UINT32_C(0x00000114)));
/* 0013c8a4: nop  */ 
L_0013c8a8:;
/* 0013c8a8: sll v0,a3,0x4 */ set(2,sx((uint32_t)cpu(7)<<4));
/* 0013c8ac: sll a2,t0,0x2 */ set(6,sx((uint32_t)cpu(8)<<2));
/* 0013c8b0: addu v0,v0,t3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(11)));
/* 0013c8b4: li a0,0x7 */ set(4,sx(UINT32_C(0x00000007)));
L_0013c8b8:;
/* 0013c8b8: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 0013c8bc: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0013c8c0: sw zero,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 0013c8c4: sw zero,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 0013c8c8: swc1 f1,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),f[1]);
/* 0013c8cc: bgez a0,0x0013c8b8 */ {int taken=((int64_t)cpu(4)>=0);/* delay 0013c8d0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000010)));if(taken){goto L_0013c8b8;}}
/* 0013c8d4: sll v0,a3,0x4 */ set(2,sx((uint32_t)cpu(7)<<4));
/* 0013c8d8: sw zero,-0xa0(a1) */ sw(ea(5,(int32_t)UINT32_C(0xffffff60)),(uint32_t)cpu(0));
/* 0013c8dc: addu v0,v0,t4 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(12)));
/* 0013c8e0: sw zero,-0x9c(a1) */ sw(ea(5,(int32_t)UINT32_C(0xffffff64)),(uint32_t)cpu(0));
/* 0013c8e4: sw zero,-0x98(a1) */ sw(ea(5,(int32_t)UINT32_C(0xffffff68)),(uint32_t)cpu(0));
/* 0013c8e8: addiu v1,v0,0x9c */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x0000009c)));
/* 0013c8ec: swc1 f1,-0x94(a1) */ sw(ea(5,(int32_t)UINT32_C(0xffffff6c)),f[1]);
/* 0013c8f0: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 0013c8f4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0013c8f8: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0013c8fc: addiu v0,v0,0xf0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000f0)));
L_0013c900:;
/* 0013c900: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 0013c904: sw zero,-0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0xfffffff4)),(uint32_t)cpu(0));
/* 0013c908: sw zero,-0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0xfffffff8)),(uint32_t)cpu(0));
/* 0013c90c: sw zero,-0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0xfffffffc)),(uint32_t)cpu(0));
/* 0013c910: swc1 f0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),f[0]);
/* 0013c914: addiu v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000010)));
/* 0013c918: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0013c91c: bgez a0,0x0013c900 */ {int taken=((int64_t)cpu(4)>=0);/* delay 0013c920 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));if(taken){goto L_0013c900;}}
/* 0013c924: addiu t0,t0,0x1 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000001)));
/* 0013c928: addu v0,a2,t5 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(13)));
/* 0013c92c: slti v1,t0,0x40 */ set(3,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000040));
/* 0013c930: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0013c934: sw zero,-0x14(a1) */ sw(ea(5,(int32_t)UINT32_C(0xffffffec)),(uint32_t)cpu(0));
/* 0013c938: addiu a3,a3,0x13 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000013)));
/* 0013c93c: sw zero,-0x10(a1) */ sw(ea(5,(int32_t)UINT32_C(0xfffffff0)),(uint32_t)cpu(0));
/* 0013c940: sw zero,-0x18(a1) */ sw(ea(5,(int32_t)UINT32_C(0xffffffe8)),(uint32_t)cpu(0));
/* 0013c944: sw zero,0x0(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0013c948: addiu t1,t1,0x130 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000130)));
/* 0013c94c: sw zero,-0x8(a1) */ sw(ea(5,(int32_t)UINT32_C(0xfffffff8)),(uint32_t)cpu(0));
/* 0013c950: sw zero,-0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0xfffffffc)),(uint32_t)cpu(0));
/* 0013c954: sh zero,0x0(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(0));
/* 0013c958: sh t2,0x2(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(10));
/* 0013c95c: sh t2,0x4(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000004)),(uint16_t)cpu(10));
/* 0013c960: sh zero,0x6(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(0));
/* 0013c964: sh t2,0x8(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(10));
/* 0013c968: sh zero,0xa(a1) */ sh(ea(5,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(0));
/* 0013c96c: sw zero,0xc(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 0013c970: bne v1,zero,0x0013c8a8 */ {int taken=(cpu(3)!=cpu(0));/* delay 0013c974 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000130)));if(taken){goto L_0013c8a8;}}
/* 0013c978: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013c97c: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 0013c980: sw zero,-0x539c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac64)),(uint32_t)cpu(0));
/* 0013c984: sw v0,-0x53ac(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac54)),(uint32_t)cpu(2));
/* 0013c988: sw v0,-0x53c0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac40)),(uint32_t)cpu(2));
/* 0013c98c: sw v0,-0x53bc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac44)),(uint32_t)cpu(2));
/* 0013c990: sw v0,-0x53b4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac4c)),(uint32_t)cpu(2));
/* 0013c994: sw v0,-0x53b0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac50)),(uint32_t)cpu(2));
/* 0013c998: j 0x00142fb0 */ /* delay 0013c99c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneFieldInfControllerNativeExternal(UINT32_C(0x00142fb0),UINT32_C(0x0013c998));return;
}
static void body_001405b0(void){
uint64_t incoming=cpu(31);
/* 001405b0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 001405b4: slti v0,a0,0xa */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 001405b8: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001405bc: move s5,zero */ set(21,cpu(0));
/* 001405c0: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001405c4: move s7,zero */ set(23,cpu(0));
/* 001405c8: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001405cc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001405d0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001405d4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001405d8: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001405dc: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001405e0: beq v0,zero,0x00140690 */ {int taken=(cpu(2)==cpu(0));/* delay 001405e4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));if(taken){goto L_00140690;}}
/* 001405e8: lw a2,-0x5398(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffac68)));
/* 001405ec: addiu s2,a0,-0x1 */ set(18,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 001405f0: lui s6,0x30 */ set(22,sx(UINT32_C(0x00300000)));
/* 001405f4: sll v0,a2,0x2 */ set(2,sx((uint32_t)cpu(6)<<2));
/* 001405f8: addiu s0,s6,-0xbe0 */ set(16,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
/* 001405fc: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00140600: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00140604: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00140608: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0014060c: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00140610: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00140614: addiu v0,v0,0xad0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000ad0)));
/* 00140618: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 0014061c: lh a0,0x0(v0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 00140620: bne a0,zero,0x00140630 */ {int taken=(cpu(4)!=cpu(0));/* delay 00140624 */ if(taken){goto L_00140630;}}
/* 00140628: b 0x001406d0 */ /* delay 0014062c */ set(17,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000002))));goto L_001406d0;
L_00140630:;
/* 00140630: jal 0x001e0f50 */ set(31,UINT64_C(0x00140638));/* delay 00140634 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x001e0f50),UINT32_C(0x00140630));
/* 00140638: beq v0,zero,0x00140668 */ {int taken=(cpu(2)==cpu(0));/* delay 0014063c */ lw(6,ea(28,(int32_t)UINT32_C(0xffffac68)));if(taken){goto L_00140668;}}
/* 00140640: sll v0,a2,0x2 */ set(2,sx((uint32_t)cpu(6)<<2));
/* 00140644: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00140648: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0014064c: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00140650: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00140654: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00140658: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0014065c: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 00140660: b 0x001406d0 */ /* delay 00140664 */ set(17,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000ad3))));goto L_001406d0;
L_00140668:;
/* 00140668: sll v0,a2,0x2 */ set(2,sx((uint32_t)cpu(6)<<2));
/* 0014066c: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00140670: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00140674: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00140678: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 0014067c: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00140680: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00140684: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 00140688: b 0x001406d0 */ /* delay 0014068c */ set(17,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000ad2))));goto L_001406d0;
L_00140690:;
/* 00140690: lw a2,-0x5398(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffac68)));
/* 00140694: addiu s2,a0,-0xa */ set(18,sx((uint32_t)cpu(4)+UINT32_C(0xfffffff6)));
/* 00140698: sll v1,s2,0x3 */ set(3,sx((uint32_t)cpu(18)<<3));
/* 0014069c: lui s6,0x30 */ set(22,sx(UINT32_C(0x00300000)));
/* 001406a0: sll v0,a2,0x2 */ set(2,sx((uint32_t)cpu(6)<<2));
/* 001406a4: subu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(18)));
/* 001406a8: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 001406ac: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 001406b0: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 001406b4: addu v1,a1,v1 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 001406b8: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 001406bc: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 001406c0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001406c4: lui s1,0x30 */ set(17,sx(UINT32_C(0x00300000)));
/* 001406c8: addu s1,s1,v1 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(3)));
/* 001406cc: lb s1,-0xfc(s1) */ set(17,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0xffffff04))));
L_001406d0:;
/* 001406d0: slti s4,s1,0xa */ set(20,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 001406d4: bne s4,zero,0x00140754 */ {int taken=(cpu(20)!=cpu(0));/* delay 001406d8 */ set(2,sx((uint32_t)cpu(6)<<2));if(taken){goto L_00140754;}}
/* 001406dc: sll v1,s1,0x3 */ set(3,sx((uint32_t)cpu(17)<<3));
/* 001406e0: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 001406e4: subu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));
/* 001406e8: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 001406ec: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 001406f0: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 001406f4: addiu s0,v1,0xac0 */ set(16,sx((uint32_t)cpu(3)+UINT32_C(0x00000ac0)));
/* 001406f8: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 001406fc: addiu v1,s6,-0xbe0 */ set(3,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
/* 00140700: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00140704: addiu s3,v1,0x8 */ set(19,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 00140708: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 0014070c: lh a0,-0x6c(v0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0xffffff94))));
/* 00140710: beql a0,zero,0x00140728 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00140714 */ set(2,sx((uint32_t)cpu(6)<<2));goto L_00140728;}}
/* 00140718: jal 0x001e0f10 */ set(31,UINT64_C(0x00140720));/* delay 0014071c */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x001e0f10),UINT32_C(0x00140718));
/* 00140720: lw a2,-0x5398(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffac68)));
/* 00140724: sll v0,a2,0x2 */ set(2,sx((uint32_t)cpu(6)<<2));
L_00140728:;
/* 00140728: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 0014072c: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00140730: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00140734: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00140738: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0014073c: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 00140740: lh a0,-0x6a(v0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0xffffff96))));
/* 00140744: beq a0,zero,0x00140754 */ {int taken=(cpu(4)==cpu(0));/* delay 00140748 */ if(taken){goto L_00140754;}}
/* 0014074c: jal 0x001e0ed0 */ set(31,UINT64_C(0x00140754));/* delay 00140750 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x001e0ed0),UINT32_C(0x0014074c));
L_00140754:;
/* 00140754: jal 0x0010e548 */ set(31,UINT64_C(0x0014075c));/* delay 00140758 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e548),UINT32_C(0x00140754));
/* 0014075c: bne s4,zero,0x00140798 */ {int taken=(cpu(20)!=cpu(0));/* delay 00140760 */ set(19,cpu(2));if(taken){goto L_00140798;}}
/* 00140764: lw a0,-0x5398(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffac68)));
/* 00140768: sll v1,s1,0x3 */ set(3,sx((uint32_t)cpu(17)<<3));
/* 0014076c: subu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));
/* 00140770: addiu a1,s6,-0xbe0 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
/* 00140774: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00140778: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 0014077c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00140780: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00140784: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 00140788: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0014078c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00140790: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00140794: lb s5,0xa61(v1) */ set(21,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000a61))));
L_00140798:;
/* 00140798: beq s5,zero,0x00140810 */ {int taken=(cpu(21)==cpu(0));/* delay 0014079c */ set(2,sx((uint32_t)cpu(21)<<2));if(taken){goto L_00140810;}}
/* 001407a0: addiu a2,s6,-0xbe0 */ set(6,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
/* 001407a4: addu v0,v0,s5 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(21)));
/* 001407a8: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001407ac: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001407b0: addiu a1,v0,0x7a0 */ set(5,sx((uint32_t)cpu(2)+UINT32_C(0x000007a0)));
/* 001407b4: addu v1,a1,a2 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(6)));
/* 001407b8: lh v1,0x0(v1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001407bc: bnel v1,a0,0x001407d8 */ {int taken=(cpu(3)!=cpu(4));if(taken){/* delay 001407c0 */ set(2,sx(UINT32_C(0x00000002)));goto L_001407d8;}}
/* 001407c4: jal 0x0013c6f0 */ set(31,UINT64_C(0x001407cc));/* delay 001407c8 */ body_0013c6f0();
/* 001407cc: b 0x00140810 */ /* delay 001407d0 */ goto L_00140810;
L_001407d8:;
/* 001407d8: bne v1,v0,0x00140800 */ {int taken=(cpu(3)!=cpu(2));/* delay 001407dc */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00140800;}}
/* 001407e0: addu v1,a2,a1 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001407e4: move v0,v1 */ set(2,cpu(3));
/* 001407e8: lw a1,0x8(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001407ec: jal 0x002442e0 */ set(31,UINT64_C(0x001407f4));/* delay 001407f0 */ lw(4,ea(2,(int32_t)UINT32_C(0x00000004)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x002442e0),UINT32_C(0x001407ec));
/* 001407f4: b 0x00140810 */ /* delay 001407f8 */ goto L_00140810;
L_00140800:;
/* 00140800: bne v1,v0,0x00140810 */ {int taken=(cpu(3)!=cpu(2));/* delay 00140804 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));if(taken){goto L_00140810;}}
/* 00140808: jal 0x00244238 */ set(31,UINT64_C(0x00140810));/* delay 0014080c */ lw(4,ea(2,(int32_t)UINT32_C(0x00000004)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00244238),UINT32_C(0x00140808));
L_00140810:;
/* 00140810: bne s4,zero,0x00140848 */ {int taken=(cpu(20)!=cpu(0));/* delay 00140814 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffac68)));if(taken){goto L_00140848;}}
/* 00140818: sll v1,s1,0x3 */ set(3,sx((uint32_t)cpu(17)<<3));
/* 0014081c: subu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(17)));
/* 00140820: addiu a1,s6,-0xbe0 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
/* 00140824: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00140828: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 0014082c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00140830: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00140834: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 00140838: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0014083c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00140840: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00140844: lb s7,0xa60(v1) */ set(23,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000a60))));
L_00140848:;
/* 00140848: beq s7,zero,0x00140988 */ {int taken=(cpu(23)==cpu(0));/* delay 0014084c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa978)));if(taken){goto L_00140988;}}
/* 00140850: lw v1,0x18(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 00140854: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00140858: beq v0,zero,0x00140898 */ {int taken=(cpu(2)==cpu(0));/* delay 0014085c */ set(16,sx((uint32_t)cpu(23)<<5));if(taken){goto L_00140898;}}
/* 00140860: addiu v0,s6,-0xbe0 */ set(2,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
/* 00140864: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00140868: lw v1,0x2a0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x000002a0)));
/* 0014086c: beq v1,zero,0x00140888 */ {int taken=(cpu(3)==cpu(0));/* delay 00140870 */ if(taken){goto L_00140888;}}
/* 00140874: jal 0x00134e48 */ set(31,UINT64_C(0x0014087c));/* delay 00140878 */ body_00134e48();
/* 0014087c: b 0x0014089c */ /* delay 00140880 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));goto L_0014089c;
L_00140888:;
/* 00140888: jal 0x00134df8 */ set(31,UINT64_C(0x00140890));/* delay 0014088c */ body_00134df8();
/* 00140890: b 0x0014089c */ /* delay 00140894 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));goto L_0014089c;
L_00140898:;
/* 00140898: addiu a1,s6,-0xbe0 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
L_0014089c:;
/* 0014089c: addu v0,s0,a1 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 001408a0: lb v1,0x2a8(v0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x000002a8))));
/* 001408a4: beq v1,zero,0x001408d0 */ {int taken=(cpu(3)==cpu(0));/* delay 001408a8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000002a8)));if(taken){goto L_001408d0;}}
/* 001408ac: move a0,s3 */ set(4,cpu(19));
/* 001408b0: jal 0x0010f790 */ set(31,UINT64_C(0x001408b8));/* delay 001408b4 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f790),UINT32_C(0x001408b0));
/* 001408b8: move v1,v0 */ set(3,cpu(2));
/* 001408bc: beq v1,zero,0x001408d0 */ {int taken=(cpu(3)==cpu(0));/* delay 001408c0 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa978)));if(taken){goto L_001408d0;}}
/* 001408c4: lw a1,0x4(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 001408c8: jal 0x001e1688 */ set(31,UINT64_C(0x001408d0));/* delay 001408cc */ lw(4,ea(2,(int32_t)UINT32_C(0x00000004)));body_001e1688();
L_001408d0:;
/* 001408d0: addiu a1,s6,-0xbe0 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
/* 001408d4: addu v0,s0,a1 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 001408d8: lb v1,0x2b4(v0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x000002b4))));
/* 001408dc: beq v1,zero,0x00140920 */ {int taken=(cpu(3)==cpu(0));/* delay 001408e0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x000002b4)));if(taken){goto L_00140920;}}
/* 001408e4: move a0,s3 */ set(4,cpu(19));
/* 001408e8: jal 0x0010f790 */ set(31,UINT64_C(0x001408f0));/* delay 001408ec */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f790),UINT32_C(0x001408e8));
/* 001408f0: move v1,v0 */ set(3,cpu(2));
/* 001408f4: beq v1,zero,0x00140988 */ {int taken=(cpu(3)==cpu(0));/* delay 001408f8 */ set(4,cpu(19));if(taken){goto L_00140988;}}
/* 001408fc: lw a1,0x4(v1) */ lw(5,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 00140900: jal 0x0010f208 */ set(31,UINT64_C(0x00140908));/* delay 00140904 */ set(6,sx(UINT32_C(0x00000004)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f208),UINT32_C(0x00140900));
/* 00140908: beq v0,zero,0x00140988 */ {int taken=(cpu(2)==cpu(0));/* delay 0014090c */ set(4,cpu(19));if(taken){goto L_00140988;}}
/* 00140910: jal 0x0010f178 */ set(31,UINT64_C(0x00140918));/* delay 00140914 */ set(5,cpu(2));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f178),UINT32_C(0x00140910));
/* 00140918: b 0x00140988 */ /* delay 0014091c */ goto L_00140988;
L_00140920:;
/* 00140920: jal 0x0012efd8 */ set(31,UINT64_C(0x00140928));/* delay 00140924 */ body_0012efd8();
/* 00140928: beq v0,zero,0x00140988 */ {int taken=(cpu(2)==cpu(0));/* delay 0014092c */ if(taken){goto L_00140988;}}
/* 00140930: jal 0x00122608 */ set(31,UINT64_C(0x00140938));/* delay 00140934 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x00122608),UINT32_C(0x00140930));
/* 00140938: move a0,s3 */ set(4,cpu(19));
/* 0014093c: jal 0x0010f178 */ set(31,UINT64_C(0x00140944));/* delay 00140940 */ set(5,cpu(2));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f178),UINT32_C(0x0014093c));
/* 00140944: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 00140948: lw v1,-0x4068(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffbf98)));
/* 0014094c: sltiu v0,v1,0x5 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 00140950: beq v0,zero,0x00140988 */ {int taken=(cpu(2)==cpu(0));/* delay 00140954 */ set(2,sx((uint32_t)cpu(3)<<2));if(taken){goto L_00140988;}}
/* 00140958: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 0014095c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00140960: lw v1,0x1e60(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00001e60)));
/* 00140964: jr v1 */ {uint64_t target=cpu(3);/* delay 00140968 */ switch((uint32_t)target){case UINT32_C(0x00140970):goto L_00140970;case UINT32_C(0x00140980):goto L_00140980;case UINT32_C(0x00140988):goto L_00140988;default:abort();}}
L_00140970:;
/* 00140970: jal 0x0012ca30 */ set(31,UINT64_C(0x00140978));/* delay 00140974 */ body_0012ca30();
/* 00140978: b 0x00140988 */ /* delay 0014097c */ goto L_00140988;
L_00140980:;
/* 00140980: jal 0x0012ddf8 */ set(31,UINT64_C(0x00140988));/* delay 00140984 */ body_0012ddf8();
L_00140988:;
/* 00140988: bne s1,zero,0x00140ae4 */ {int taken=(cpu(17)!=cpu(0));/* delay 0014098c */ set(2,cpu(17));if(taken){goto L_00140ae4;}}
/* 00140990: lw a0,-0x5398(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffac68)));
/* 00140994: sll v1,s2,0x3 */ set(3,sx((uint32_t)cpu(18)<<3));
/* 00140998: subu v1,v1,s2 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(18)));
/* 0014099c: addiu s0,s6,-0xbe0 */ set(16,sx((uint32_t)cpu(22)+UINT32_C(0xfffff420)));
/* 001409a0: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001409a4: sll s2,v1,0x1 */ set(18,sx((uint32_t)cpu(3)<<1));
/* 001409a8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001409ac: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 001409b0: subu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));
/* 001409b4: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 001409b8: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001409bc: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001409c0: lb v1,0xaed(v0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000aed))));
/* 001409c4: beq v1,zero,0x00140a68 */ {int taken=(cpu(3)==cpu(0));/* delay 001409c8 */ set(2,sx((uint32_t)cpu(3)<<2));if(taken){goto L_00140a68;}}
/* 001409cc: li a0,0x4 */ set(4,sx(UINT32_C(0x00000004)));
/* 001409d0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001409d4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001409d8: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001409dc: lh v1,0x7a0(v0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x000007a0))));
/* 001409e0: bnel v1,a0,0x00140a6c */ {int taken=(cpu(3)!=cpu(4));if(taken){/* delay 001409e4 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa978)));goto L_00140a6c;}}
/* 001409e8: jal 0x00109f08 */ set(31,UINT64_C(0x001409f0));/* delay 001409ec */ body_00109f08();
/* 001409f0: lw v0,-0x5398(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffac68)));
/* 001409f4: lui a0,0x30 */ set(4,sx(UINT32_C(0x00300000)));
/* 001409f8: sll v1,v0,0x2 */ set(3,sx((uint32_t)cpu(2)<<2));
/* 001409fc: addiu s3,a0,-0x4080 */ set(19,sx((uint32_t)cpu(4)+UINT32_C(0xffffbf80)));
/* 00140a00: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00140a04: lw a0,0x4(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 00140a08: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00140a0c: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 00140a10: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00140a14: addu v1,s2,v1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(3)));
/* 00140a18: addu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(16)));
/* 00140a1c: lb a1,0xaed(v1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000aed))));
/* 00140a20: sll v0,a1,0x2 */ set(2,sx((uint32_t)cpu(5)<<2));
/* 00140a24: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 00140a28: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00140a2c: addiu v0,v0,0x7a0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000007a0)));
/* 00140a30: addu v1,s0,v0 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 00140a34: lw s0,0x4(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 00140a38: move v0,v1 */ set(2,cpu(3));
/* 00140a3c: lw s1,0x8(v0) */ lw(17,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 00140a40: jal 0x00125cb8 */ set(31,UINT64_C(0x00140a48));/* delay 00140a44 */ set(5,cpu(16));body_00125cb8();
/* 00140a48: jal 0x001e7228 */ set(31,UINT64_C(0x00140a50));/* delay 00140a4c */ set(4,cpu(16));body_001e7228();
/* 00140a50: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00140a54: beql s1,v0,0x00140a5c */ {int taken=(cpu(17)==cpu(2));if(taken){/* delay 00140a58 */ sw(ea(19,(int32_t)UINT32_C(0x000000cc)),(uint32_t)cpu(17));goto L_00140a5c;}}
L_00140a5c:;
/* 00140a5c: b 0x00140ae4 */ /* delay 00140a60 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x000000c8)));goto L_00140ae4;
L_00140a68:;
/* 00140a68: lw v0,-0x5688(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa978)));
L_00140a6c:;
/* 00140a6c: lw v1,0x18(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 00140a70: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00140a74: beq v0,zero,0x00140a8c */ {int taken=(cpu(2)==cpu(0));/* delay 00140a78 */ set(3,sx(UINT32_C(0xfffffffe)));if(taken){goto L_00140a8c;}}
/* 00140a7c: lw a0,0x8c(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x0000008c)));
/* 00140a80: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00140a84: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 00140a88: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_00140a8c:;
/* 00140a8c: jal 0x0012efd8 */ set(31,UINT64_C(0x00140a94));/* delay 00140a90 */ body_0012efd8();
/* 00140a94: beq v0,zero,0x00140ae0 */ {int taken=(cpu(2)==cpu(0));/* delay 00140a98 */ set(2,sx(UINT32_C(0x00300000)));if(taken){goto L_00140ae0;}}
/* 00140a9c: lw v0,-0x4068(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffffbf98)));
/* 00140aa0: sltiu v1,v0,0x5 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 00140aa4: beql v1,zero,0x00140ae4 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00140aa8 */ set(2,cpu(17));goto L_00140ae4;}}
/* 00140aac: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00140ab0: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 00140ab4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00140ab8: lw v1,0x1e80(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00001e80)));
/* 00140abc: jr v1 */ {uint64_t target=cpu(3);/* delay 00140ac0 */ switch((uint32_t)target){case UINT32_C(0x00140ac8):goto L_00140ac8;case UINT32_C(0x00140ad8):goto L_00140ad8;case UINT32_C(0x00140ae0):goto L_00140ae0;default:abort();}}
L_00140ac8:;
/* 00140ac8: jal 0x0012ca30 */ set(31,UINT64_C(0x00140ad0));/* delay 00140acc */ body_0012ca30();
/* 00140ad0: b 0x00140ae4 */ /* delay 00140ad4 */ set(2,cpu(17));goto L_00140ae4;
L_00140ad8:;
/* 00140ad8: jal 0x0012ddf8 */ set(31,UINT64_C(0x00140ae0));/* delay 00140adc */ body_0012ddf8();
L_00140ae0:;
/* 00140ae0: move v0,s1 */ set(2,cpu(17));
L_00140ae4:;
/* 00140ae4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00140ae8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00140aec: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00140af0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00140af4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00140af8: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00140afc: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00140b00: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00140b04: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00140b08: jr ra */ {uint64_t target=cpu(31);/* delay 00140b0c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_00140cf0(void){
uint64_t incoming=cpu(31);
/* 00140cf0: lw v0,-0x5394(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffac6c)));
/* 00140cf4: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00140cf8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00140cfc: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00140d00: sll s1,v0,0x2 */ set(17,sx((uint32_t)cpu(2)<<2));
/* 00140d04: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00140d08: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00140d0c: sw v1,-0x5390(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac70)),(uint32_t)cpu(3));
/* 00140d10: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 00140d14: addu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(17)));
/* 00140d18: lw v1,-0x3260(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffcda0)));
/* 00140d1c: jal 0x00140f48 */ set(31,UINT64_C(0x00140d24));/* delay 00140d20 */ lw(4,ea(3,(int32_t)UINT32_C(0x00000008)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00140f48),UINT32_C(0x00140d1c));
/* 00140d24: move s0,v0 */ set(16,cpu(2));
/* 00140d28: jal 0x0010a078 */ set(31,UINT64_C(0x00140d30));/* delay 00140d2c */ set(4,cpu(16));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010a078),UINT32_C(0x00140d28));
/* 00140d30: bnel v0,zero,0x00140d5c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00140d34 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00140d5c;}}
/* 00140d38: jal 0x0010e548 */ set(31,UINT64_C(0x00140d40));/* delay 00140d3c */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e548),UINT32_C(0x00140d38));
/* 00140d40: move a1,s0 */ set(5,cpu(16));
/* 00140d44: jal 0x0010f4d8 */ set(31,UINT64_C(0x00140d4c));/* delay 00140d48 */ set(4,cpu(2));body_0010f4d8();
/* 00140d4c: lui at,0x30 */ set(1,sx(UINT32_C(0x00300000)));
/* 00140d50: addu at,at,s1 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(17)));
/* 00140d54: sw v0,-0x3160(at) */ sw(ea(1,(int32_t)UINT32_C(0xffffcea0)),(uint32_t)cpu(2));
/* 00140d58: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00140d5c:;
/* 00140d5c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00140d60: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00140d64: jr ra */ {uint64_t target=cpu(31);/* delay 00140d68 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001452c8(void){
uint64_t incoming=cpu(31);
/* 001452c8: lw a0,-0x534c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffacb4)));
/* 001452cc: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001452d0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001452d4: jal 0x002c16b8 */ set(31,UINT64_C(0x001452dc));/* delay 001452d8 */ body_002c16b8();
/* 001452dc: sw zero,-0x534c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffacb4)),(uint32_t)cpu(0));
/* 001452e0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001452e4: jr ra */ {uint64_t target=cpu(31);/* delay 001452e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001dd578(void){
uint64_t incoming=cpu(31);
/* 001dd578: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001dd57c: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 001dd580: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd584: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001dd588: j 0x001dd440 */ /* delay 001dd58c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneFieldInfControllerNativeExternal(UINT32_C(0x001dd440),UINT32_C(0x001dd588));return;
}
static void body_001e1688(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 001e1688: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001e168c: lui v0,0x54 */ set(2,sx(UINT32_C(0x00540000)));
/* 001e1690: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e1694: move s0,a0 */ set(16,cpu(4));
/* 001e1698: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e169c: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001e16a0: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001e16a4: addiu a3,v0,-0x5818 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0xffffa7e8)));
/* 001e16a8: ldl v1,0x7(a3) */ loadPartial(3,ea(7,(int32_t)UINT32_C(0x00000007)),1);
/* 001e16ac: ldr v1,0x0(a3) */ loadPartial(3,ea(7,(int32_t)UINT32_C(0x00000000)),0);
/* 001e16b0: ldl a0,0xf(a3) */ loadPartial(4,ea(7,(int32_t)UINT32_C(0x0000000f)),1);
/* 001e16b4: ldr a0,0x8(a3) */ loadPartial(4,ea(7,(int32_t)UINT32_C(0x00000008)),0);
/* 001e16b8: sdl v1,0x7(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000007)),3,1);
/* 001e16bc: sdr v1,0x0(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000000)),3,0);
/* 001e16c0: sdl a0,0xf(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000000f)),4,1);
/* 001e16c4: sdr a0,0x8(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000008)),4,0);
/* 001e16c8: jal 0x0010e588 */ set(31,UINT64_C(0x001e16d0));/* delay 001e16cc */ set(18,cpu(5));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e588),UINT32_C(0x001e16c8));
/* 001e16d0: move a0,v0 */ set(4,cpu(2));
/* 001e16d4: move a1,s0 */ set(5,cpu(16));
/* 001e16d8: jal 0x0010f208 */ set(31,UINT64_C(0x001e16e0));/* delay 001e16dc */ set(6,sx(UINT32_C(0x00000005)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f208),UINT32_C(0x001e16d8));
/* 001e16e0: move s1,v0 */ set(17,cpu(2));
/* 001e16e4: beql s1,zero,0x001e175c */ {int taken=(cpu(17)==cpu(0));if(taken){/* delay 001e16e8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_001e175c;}}
/* 001e16ec: jal 0x0010e588 */ set(31,UINT64_C(0x001e16f4));/* delay 001e16f0 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010e588),UINT32_C(0x001e16ec));
/* 001e16f4: move a1,s2 */ set(5,cpu(18));
/* 001e16f8: move a0,v0 */ set(4,cpu(2));
/* 001e16fc: jal 0x0010f208 */ set(31,UINT64_C(0x001e1704));/* delay 001e1700 */ set(6,sx(UINT32_C(0x00000011)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010f208),UINT32_C(0x001e16fc));
/* 001e1704: beq v0,zero,0x001e1758 */ {int taken=(cpu(2)==cpu(0));/* delay 001e1708 */ set(4,cpu(17));if(taken){goto L_001e1758;}}
/* 001e170c: lw s0,0x18(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 001e1710: jal 0x0010dea8 */ set(31,UINT64_C(0x001e1718));/* delay 001e1714 */ set(5,cpu(16));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010dea8),UINT32_C(0x001e1710));
/* 001e1718: lqc2 vf10,0x0(sp) */ loadVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001e171c: lwc1 f12,-0x5e08(gp) */ f[12]=word(ea(28,(int32_t)UINT32_C(0xffffa1f8)));
/* 001e1720: jal 0x002c0560 */ set(31,UINT64_C(0x001e1728));/* delay 001e1724 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));body_002c0560();
/* 001e1728: lqc2 vf11,0x0(s0) */ loadVu(11,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001e172c: jal 0x002c0488 */ set(31,UINT64_C(0x001e1734));/* delay 001e1730 */ nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0488),UINT32_C(0x001e172c));
/* 001e1734: sqc2 vf10,0x0(sp) */ storeVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001e1738: move a1,sp */ set(5,cpu(29));
/* 001e173c: jal 0x0010ded8 */ set(31,UINT64_C(0x001e1744));/* delay 001e1740 */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010ded8),UINT32_C(0x001e173c));
/* 001e1744: jal 0x0010df38 */ set(31,UINT64_C(0x001e174c));/* delay 001e1748 */ set(4,cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x0010df38),UINT32_C(0x001e1744));
/* 001e174c: lw v0,0x1c(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 001e1750: addiu v0,v0,0x70 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000070)));
/* 001e1754: sqc2 vf10,0x0(v0) */ storeVu(10,ea(2,(int32_t)UINT32_C(0x00000000)));
L_001e1758:;
/* 001e1758: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
L_001e175c:;
/* 001e175c: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e1760: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001e1764: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001e1768: jr ra */ {uint64_t target=cpu(31);/* delay 001e176c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001e7228(void){
uint64_t incoming=cpu(31);
/* 001e7228: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001e722c: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e7230: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e7234: jal 0x001452c8 */ set(31,UINT64_C(0x001e723c));/* delay 001e7238 */ set(16,cpu(4));body_001452c8();
/* 001e723c: li a0,0xf */ set(4,sx(UINT32_C(0x0000000f)));
/* 001e7240: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 001e7244: jal 0x002c18d8 */ set(31,UINT64_C(0x001e724c));/* delay 001e7248 */ set(6,sx(UINT32_C(0x0000003f)));body_002c18d8();
/* 001e724c: jal 0x0012c360 */ set(31,UINT64_C(0x001e7254));/* delay 001e7250 */ body_0012c360();
/* 001e7254: move a1,sp */ set(5,cpu(29));
/* 001e7258: li a0,0x13 */ set(4,sx(UINT32_C(0x00000013)));
/* 001e725c: li a2,0x8 */ set(6,sx(UINT32_C(0x00000008)));
/* 001e7260: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 001e7264: sw s0,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 001e7268: sw zero,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001e726c: jal 0x00102848 */ set(31,UINT64_C(0x001e7274));/* delay 001e7270 */ sw(ea(28,(int32_t)UINT32_C(0xffffb5e0)),(uint32_t)cpu(0));nocturneFieldInfControllerNativeExternal(UINT32_C(0x00102848),UINT32_C(0x001e726c));
/* 001e7274: jal 0x00109f08 */ set(31,UINT64_C(0x001e727c));/* delay 001e7278 */ body_00109f08();
/* 001e727c: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e7280: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e7284: jr ra */ {uint64_t target=cpu(31);/* delay 001e7288 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002c0560(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 002c0560: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 002c0564: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 002c0568: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c056c: swc1 f20,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[20]);
/* 002c0570: mul.S f20,f12,f0 */ f[20]=EE_FPU_MUL_S(f[12],f[0]);
/* 002c0574: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0578: jal 0x002c0060 */ set(31,UINT64_C(0x002c0580));/* delay 002c057c */ f[12]=f[20];nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0060),UINT32_C(0x002c0578));
/* 002c0580: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 002c0584: qmtc2 v0,vf2 */ fieldQmt(2u,2u);
/* 002c0588: vmulx.xyzw vf10,vf10,vf2 */ fieldMulX(10u,10u,2u,15u);
/* 002c058c: jal 0x002c0160 */ set(31,UINT64_C(0x002c0594));/* delay 002c0590 */ f[12]=f[20];nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c0160),UINT32_C(0x002c058c));
/* 002c0594: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 002c0598: qmtc2 v0,vf2 */ fieldQmt(2u,2u);
/* 002c059c: vmulx.w vf10,vf0,vf2 */ fieldMulX(10u,0u,2u,1u);
/* 002c05a0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c05a4: lwc1 f20,0x8(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c05a8: jr ra */ {uint64_t target=cpu(31);/* delay 002c05ac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002c16b8(void){
uint64_t incoming=cpu(31);
/* 002c16b8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c16bc: move a1,zero */ set(5,cpu(0));
/* 002c16c0: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002c16c4: li a0,0x30 */ set(4,sx(UINT32_C(0x00000030)));
/* 002c16c8: move a2,sp */ set(6,cpu(29));
/* 002c16cc: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c16d0: jal 0x002c10e8 */ set(31,UINT64_C(0x002c16d8));/* delay 002c16d4 */ set(7,sx(UINT32_C(0x00000010)));nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c10e8),UINT32_C(0x002c16d0));
/* 002c16d8: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c16dc: jr ra */ {uint64_t target=cpu(31);/* delay 002c16e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002c18d8(void){
uint64_t incoming=cpu(31);
/* 002c18d8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002c18dc: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c18e0: move s0,a1 */ set(16,cpu(5));
/* 002c18e4: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c18e8: move s1,a2 */ set(17,cpu(6));
/* 002c18ec: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c18f0: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c18f4: jal 0x002c1ca0 */ set(31,UINT64_C(0x002c18fc));/* delay 002c18f8 */ set(18,cpu(4));nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c1ca0),UINT32_C(0x002c18f4));
/* 002c18fc: andi s1,s1,0xff */ set(17,cpu(17)&UINT32_C(0x000000ff));
/* 002c1900: move a2,sp */ set(6,cpu(29));
/* 002c1904: li a0,0x90 */ set(4,sx(UINT32_C(0x00000090)));
/* 002c1908: move a1,zero */ set(5,cpu(0));
/* 002c190c: li a3,0xc */ set(7,sx(UINT32_C(0x0000000c)));
/* 002c1910: sw s2,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));
/* 002c1914: sh s0,0x8(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(16));
/* 002c1918: jal 0x002c10e8 */ set(31,UINT64_C(0x002c1920));/* delay 002c191c */ sh(ea(29,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(17));nocturneFieldInfControllerNativeExternal(UINT32_C(0x002c10e8),UINT32_C(0x002c1918));
/* 002c1920: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c1924: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c1928: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c192c: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c1930: jr ra */ {uint64_t target=cpu(31);/* delay 002c1934 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint32_t nocturneFieldInfControllerNativeBody(uint32_t entry){switch(entry){
case UINT32_C(0x00109f08):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00109f08();return 1u;case UINT32_C(0x0010f020):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010f020();return 1u;case UINT32_C(0x0010f1f8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010f1f8();return 1u;case UINT32_C(0x0010f270):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010f270();return 1u;case UINT32_C(0x0010f4d8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0010f4d8();return 1u;case UINT32_C(0x00110350):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00110350();return 1u;case UINT32_C(0x00112410):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00112410();return 1u;case UINT32_C(0x001128a8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001128a8();return 1u;case UINT32_C(0x00113448):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00113448();return 1u;case UINT32_C(0x00113458):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00113458();return 1u;case UINT32_C(0x00120120):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00120120();return 1u;case UINT32_C(0x001201a8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001201a8();return 1u;case UINT32_C(0x001207c0):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001207c0();return 1u;case UINT32_C(0x00123370):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00123370();return 1u;case UINT32_C(0x00125cb8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00125cb8();return 1u;case UINT32_C(0x0012c148):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0012c148();return 1u;case UINT32_C(0x0012c360):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0012c360();return 1u;case UINT32_C(0x0012c458):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0012c458();return 1u;case UINT32_C(0x0012c528):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0012c528();return 1u;case UINT32_C(0x0012c730):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0012c730();return 1u;case UINT32_C(0x0012ca30):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0012ca30();return 1u;case UINT32_C(0x0012ddf8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0012ddf8();return 1u;case UINT32_C(0x0012efd8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0012efd8();return 1u;case UINT32_C(0x001303a0):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001303a0();return 1u;case UINT32_C(0x00134df8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00134df8();return 1u;case UINT32_C(0x00134e48):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00134e48();return 1u;case UINT32_C(0x00135318):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00135318();return 1u;case UINT32_C(0x00137b40):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00137b40();return 1u;case UINT32_C(0x0013b928):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0013b928();return 1u;case UINT32_C(0x0013bad8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0013bad8();return 1u;case UINT32_C(0x0013c6f0):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0013c6f0();return 1u;case UINT32_C(0x0013c860):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_0013c860();return 1u;case UINT32_C(0x001405b0):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001405b0();return 1u;case UINT32_C(0x00140cf0):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_00140cf0();return 1u;case UINT32_C(0x001452c8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001452c8();return 1u;case UINT32_C(0x001dd578):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001dd578();return 1u;case UINT32_C(0x001e1688):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001e1688();return 1u;case UINT32_C(0x001e7228):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_001e7228();return 1u;case UINT32_C(0x002c0560):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002c0560();return 1u;case UINT32_C(0x002c16b8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002c16b8();return 1u;case UINT32_C(0x002c18d8):if(nocturneFieldInfControllerNativeStackPointer()!=(uint32_t)cpu(29))abort();body_002c18d8();return 1u;
default:return 0u;}}
uint64_t ps2FieldInfControllerNative_00109F08(void){body_00109f08();return cpu(2);}
void ps2FieldInfControllerNative_0010F020(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_0010f020();}
uint64_t ps2FieldInfControllerNative_0010F1F8(uint64_t a0){set(4,a0);body_0010f1f8();return cpu(2);}
uint64_t ps2FieldInfControllerNative_0010F270(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_0010f270();return cpu(2);}
uint64_t ps2FieldInfControllerNative_0010F4D8(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_0010f4d8();return cpu(2);}
uint64_t ps2FieldInfControllerNative_00110350(uint64_t a0){set(4,a0);body_00110350();return cpu(2);}
uint64_t ps2FieldInfControllerNative_00112410(uint64_t a0){set(4,a0);body_00112410();return cpu(2);}
void ps2FieldInfControllerNative_001128A8(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_001128a8();}
void ps2FieldInfControllerNative_00113448(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_00113448();}
uint64_t ps2FieldInfControllerNative_00113458(uint64_t a0){set(4,a0);body_00113458();return cpu(2);}
uint64_t ps2FieldInfControllerNative_00120120(uint64_t a0){set(4,a0);body_00120120();return cpu(2);}
uint64_t ps2FieldInfControllerNative_001201A8(uint64_t a0){set(4,a0);body_001201a8();return cpu(2);}
uint64_t ps2FieldInfControllerNative_001207C0(uint64_t a0,uint64_t a1,uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_001207c0();return cpu(2);}
uint64_t ps2FieldInfControllerNative_00123370(void){body_00123370();return cpu(2);}
void ps2FieldInfControllerNative_00125CB8(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_00125cb8();}
uint64_t ps2FieldInfControllerNative_0012C148(void){body_0012c148();return cpu(2);}
void ps2FieldInfControllerNative_0012C360(void){body_0012c360();}
float ps2FieldInfControllerNative_0012C458(float f12,float f13,float f14,float f15){nocturneEffectHostFpr()[12]=fieldBits(f12);nocturneEffectHostFpr()[13]=fieldBits(f13);nocturneEffectHostFpr()[14]=fieldBits(f14);nocturneEffectHostFpr()[15]=fieldBits(f15);body_0012c458();return fieldReal(nocturneEffectHostFpr()[0]);}
float ps2FieldInfControllerNative_0012C528(float f12,float f13,float f14,float f15){nocturneEffectHostFpr()[12]=fieldBits(f12);nocturneEffectHostFpr()[13]=fieldBits(f13);nocturneEffectHostFpr()[14]=fieldBits(f14);nocturneEffectHostFpr()[15]=fieldBits(f15);body_0012c528();return fieldReal(nocturneEffectHostFpr()[0]);}
void ps2FieldInfControllerNative_0012C730(void){body_0012c730();}
void ps2FieldInfControllerNative_0012CA30(void){body_0012ca30();}
void ps2FieldInfControllerNative_0012DDF8(void){body_0012ddf8();}
uint64_t ps2FieldInfControllerNative_0012EFD8(void){body_0012efd8();return cpu(2);}
void ps2FieldInfControllerNative_001303A0(uint64_t a0,uint64_t a1,float f12){set(4,a0);set(5,a1);nocturneEffectHostFpr()[12]=fieldBits(f12);body_001303a0();}
void ps2FieldInfControllerNative_00134DF8(void){body_00134df8();}
void ps2FieldInfControllerNative_00134E48(void){body_00134e48();}
void ps2FieldInfControllerNative_00135318(void){body_00135318();}
float ps2FieldInfControllerNative_00137B40(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_00137b40();return fieldReal(nocturneEffectHostFpr()[0]);}
float ps2FieldInfControllerNative_0013B928(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,float f12){set(4,a0);set(5,a1);set(6,a2);set(7,a3);nocturneEffectHostFpr()[12]=fieldBits(f12);body_0013b928();return fieldReal(nocturneEffectHostFpr()[0]);}
uint64_t ps2FieldInfControllerNative_0013BAD8(uint64_t a0,uint64_t a1,uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_0013bad8();return cpu(2);}
void ps2FieldInfControllerNative_0013C6F0(void){body_0013c6f0();}
void ps2FieldInfControllerNative_0013C860(void){body_0013c860();}
uint64_t ps2FieldInfControllerNative_001405B0(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_001405b0();return cpu(2);}
void ps2FieldInfControllerNative_00140CF0(void){body_00140cf0();}
void ps2FieldInfControllerNative_001452C8(void){body_001452c8();}
void ps2FieldInfControllerNative_001DD578(uint64_t a0,uint64_t a1,uint64_t a2,float f12,float f13){set(4,a0);set(5,a1);set(6,a2);nocturneEffectHostFpr()[12]=fieldBits(f12);nocturneEffectHostFpr()[13]=fieldBits(f13);body_001dd578();}
void ps2FieldInfControllerNative_001E1688(uint64_t a0,uint64_t a1){set(4,a0);set(5,a1);body_001e1688();}
void ps2FieldInfControllerNative_001E7228(uint64_t a0){set(4,a0);body_001e7228();}
void ps2FieldInfControllerNative_002C0560(float f12){nocturneEffectHostFpr()[12]=fieldBits(f12);body_002c0560();}
uint64_t ps2FieldInfControllerNative_002C16B8(uint64_t a0){set(4,a0);body_002c16b8();return cpu(2);}
uint64_t ps2FieldInfControllerNative_002C18D8(uint64_t a0,uint64_t a1,uint64_t a2){set(4,a0);set(5,a1);set(6,a2);body_002c18d8();return cpu(2);}
