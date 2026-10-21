/* Complete16 field movement/encounter/process bodies including native active-unit publisher; fixed native-PC statements.
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




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);


static void sq(unsigned reg,uint32_t a){uint32_t q[4];nocturneFieldMovementCpuRead(reg,q);memcpy(at(a&~15u),q,16);}





static void requestLq(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneFieldMovementCpuWrite(d,q);}















#include "ee_fpu_sqrt.h"
static void loadVu(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneFieldMovementVuWrite(d,q);}
static void storeVu(unsigned s,uint32_t a){uint32_t q[4];nocturneFieldMovementVuRead(s,q);memcpy(at(a&~15u),q,16);}
/* Value operations use actual source operands and destination masks. Other
 * lanes and shared Q survive untouched. VWAITQ scheduling is not modeled. */
static void movementVu(unsigned d,unsigned s,unsigned t,unsigned kind,unsigned mask,unsigned broadcast){
 uint32_t a[4],b[4],out[4];nocturneFieldMovementVuRead(s,a);nocturneFieldMovementVuRead(t,b);nocturneFieldMovementVuRead(d,out);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){
  uint32_t rhs=b[broadcast<4u?broadcast:k];
  out[k]=(uint32_t)(kind==0u?EE_ROT_VU_ADD(a[k],rhs):kind==1u?EE_ROT_VU_SUB(a[k],rhs):EE_ROT_VU_MUL(a[k],rhs));
 }
 nocturneFieldMovementVuWrite(d,out);
}
static void movementSqrt(unsigned s,unsigned lane,uint32_t pc){uint32_t v[4];nocturneFieldMovementVuRead(s,v);EE_ROT_Q_WRITE(nocturneFieldMovementVuSqrt(v[lane],pc));}

static void body_001010d8(void);
static void body_00101130(void);
static void body_0010f598(void);
static void body_00116050(void);
static void body_0011be98(void);
static void body_0011f510(void);
static void body_00123c10(void);
static void body_001275d0(void);
static void body_00134fd8(void);
static void body_00135380(void);
static void body_0013c9a0(void);
static void body_0013fcd8(void);
static void body_00145410(void);
static void body_001e1ab0(void);
static void body_001e7188(void);
static void body_0010f1c0(void);
static void body_002c1730(void);
static void body_001010d8(void){
uint64_t incoming=cpu(31);
/* 001010d8: andi a0,a0,0xf */ set(4,cpu(4)&UINT32_C(0x0000000f));
/* 001010dc: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 001010e0: beq a0,v0,0x00101120 */ {int taken=(cpu(4)==cpu(2));/* delay 001010e4 */ if(taken){goto L_00101120;}}
/* 001010e8: sltiu v0,a0,0x3 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 001010ec: beq v0,zero,0x00101108 */ {int taken=(cpu(2)==cpu(0));/* delay 001010f0 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00101108;}}
/* 001010f4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001010f8: beq a0,v0,0x00101118 */ {int taken=(cpu(4)==cpu(2));/* delay 001010fc */ if(taken){goto L_00101118;}}
/* 00101100: jr ra */ {uint64_t target=cpu(31);/* delay 00101104 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_00101108:;
/* 00101108: beq a0,v0,0x00101128 */ {int taken=(cpu(4)==cpu(2));/* delay 0010110c */ if(taken){goto L_00101128;}}
/* 00101110: jr ra */ {uint64_t target=cpu(31);/* delay 00101114 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_00101118:;
/* 00101118: jr ra */ {uint64_t target=cpu(31);/* delay 0010111c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6e8)));checkReturn(target,incoming);return;}
L_00101120:;
/* 00101120: jr ra */ {uint64_t target=cpu(31);/* delay 00101124 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa700)));checkReturn(target,incoming);return;}
L_00101128:;
/* 00101128: jr ra */ {uint64_t target=cpu(31);/* delay 0010112c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6f4)));checkReturn(target,incoming);return;}
}
static void body_00101130(void){
uint64_t incoming=cpu(31);
/* 00101130: andi a0,a0,0xf */ set(4,cpu(4)&UINT32_C(0x0000000f));
/* 00101134: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00101138: beq a0,v0,0x00101180 */ {int taken=(cpu(4)==cpu(2));/* delay 0010113c */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa6e0)));if(taken){goto L_00101180;}}
/* 00101140: beq a0,zero,0x00101178 */ {int taken=(cpu(4)==cpu(0));/* delay 00101144 */ if(taken){goto L_00101178;}}
/* 00101148: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0010114c: beq a0,v0,0x00101168 */ {int taken=(cpu(4)==cpu(2));/* delay 00101150 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00101168;}}
/* 00101154: beq a0,v0,0x00101170 */ {int taken=(cpu(4)==cpu(2));/* delay 00101158 */ set(2,cpu(0));if(taken){goto L_00101170;}}
/* 0010115c: b 0x001011c0 */ /* delay 00101160 */ goto L_001011c0;
L_00101168:;
/* 00101168: b 0x00101180 */ /* delay 0010116c */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa6f8)));goto L_00101180;
L_00101170:;
/* 00101170: b 0x00101180 */ /* delay 00101174 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa6ec)));goto L_00101180;
L_00101178:;
/* 00101178: jr ra */ {uint64_t target=cpu(31);/* delay 0010117c */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_00101180:;
/* 00101180: blez a1,0x001011bc */ {int taken=((int64_t)cpu(5)<=0);/* delay 00101184 */ set(4,cpu(0));if(taken){goto L_001011bc;}}
/* 00101188: beq v1,zero,0x001011c0 */ {int taken=(cpu(3)==cpu(0));/* delay 0010118c */ set(2,cpu(3));if(taken){goto L_001011c0;}}
/* 00101190: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00101194: nop  */ 
L_00101198:;
/* 00101198: slt v0,a0,a1 */ set(2,(int64_t)cpu(4)<(int64_t)cpu(5));
/* 0010119c: beq v0,zero,0x001011bc */ {int taken=(cpu(2)==cpu(0));/* delay 001011a0 */ lw(3,ea(3,(int32_t)UINT32_C(0x0000003c)));if(taken){goto L_001011bc;}}
/* 001011a4: nop  */ 
/* 001011a8: nop  */ 
/* 001011ac: nop  */ 
/* 001011b0: nop  */ 
/* 001011b4: bnel v1,zero,0x00101198 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 001011b8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));goto L_00101198;}}
L_001011bc:;
/* 001011bc: move v0,v1 */ set(2,cpu(3));
L_001011c0:;
/* 001011c0: jr ra */ {uint64_t target=cpu(31);/* delay 001011c4 */ checkReturn(target,incoming);return;}
}
static void body_0010f598(void){
uint64_t incoming=cpu(31);
/* 0010f598: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0010f59c: move a0,a1 */ set(4,cpu(5));
/* 0010f5a0: beq a1,zero,0x0010f5c4 */ {int taken=(cpu(5)==cpu(0));/* delay 0010f5a4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0010f5c4;}}
/* 0010f5a8: jal 0x00101898 */ set(31,UINT64_C(0x0010f5b0));/* delay 0010f5ac */ nocturneFieldMovementCall(UINT32_C(0x00101898),UINT32_C(0x0010f5a8));
/* 0010f5b0: move a1,zero */ set(5,cpu(0));
/* 0010f5b4: beq v0,zero,0x0010f5c4 */ {int taken=(cpu(2)==cpu(0));/* delay 0010f5b8 */ set(4,cpu(2));if(taken){goto L_0010f5c4;}}
/* 0010f5bc: jal 0x00101738 */ set(31,UINT64_C(0x0010f5c4));/* delay 0010f5c0 */ nocturneFieldMovementCall(UINT32_C(0x00101738),UINT32_C(0x0010f5bc));
L_0010f5c4:;
/* 0010f5c4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f5c8: jr ra */ {uint64_t target=cpu(31);/* delay 0010f5cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00116050(void){
uint64_t incoming=cpu(31);
/* 00116050: jr ra */ {uint64_t target=cpu(31);/* delay 00116054 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000018)));checkReturn(target,incoming);return;}
}
static void body_0011be98(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 0011be98: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0011be9c: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0011bea0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0011bea4: move s0,a1 */ set(16,cpu(5));
/* 0011bea8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0011beac: move s1,a0 */ set(17,cpu(4));
/* 0011beb0: swc1 f20,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);
/* 0011beb4: lui v1,0x56 */ set(3,sx(UINT32_C(0x00560000)));
/* 0011beb8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0011bebc: addiu v0,v0,-0x4080 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffbf80)));
/* 0011bec0: addiu v1,v1,-0x2a50 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffd5b0)));
/* 0011bec4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0011bec8: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0011becc: lwc1 f1,0xc(v1) */ f[1]=word(ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 0011bed0: lwc1 f0,0x4(v1) */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0011bed4: lwc1 f13,0x108(v0) */ f[13]=word(ea(2,(int32_t)UINT32_C(0x00000108)));
/* 0011bed8: lwc1 f12,0x100(v0) */ f[12]=word(ea(2,(int32_t)UINT32_C(0x00000100)));
/* 0011bedc: sub.S f13,f13,f1 */ f[13]=EE_FPU_SUB_S(f[13],f[1]);
/* 0011bee0: sub.S f12,f12,f0 */ f[12]=EE_FPU_SUB_S(f[12],f[0]);
/* 0011bee4: clear f3 */ f[3]=0;
/* 0011bee8: mul.S f1,f13,f13 */ f[1]=EE_FPU_MUL_S(f[13],f[13]);
/* 0011beec: mul.S f0,f12,f12 */ f[0]=EE_FPU_MUL_S(f[12],f[12]);
/* 0011bef0: add.S f0,f0,f1 */ f[0]=EE_FPU_ADD_S(f[0],f[1]);
/* 0011bef4: sqrt.S f20,f0 */ f[20u]=EE_FPU_SQRT_S(f[0u]);
/* 0011bef8: c.lt.S f20,f2 */ (void)(EE_FPU_COMPARE_S(f[20],f[2],1)!=0);
/* 0011befc: bc1tl 0x0011bf2c */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)!=0);if(taken){/* delay 0011bf00 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),f[20]);goto L_0011bf2c;}}
/* 0011bf04: jal 0x002c0258 */ set(31,UINT64_C(0x0011bf0c));/* delay 0011bf08 */ nocturneFieldMovementCall(UINT32_C(0x002c0258),UINT32_C(0x0011bf04));
/* 0011bf0c: lui at,0x4334 */ set(1,sx(UINT32_C(0x43340000)));
/* 0011bf10: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0011bf14: lwc1 f2,-0x7f60(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffff80a0)));
/* 0011bf18: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0011bf1c: nop  */ 
/* 0011bf20: nop  */ 
/* 0011bf24: div.S f3,f0,f2 */ f[3]=EE_FPU_DIV_S(f[0],f[2]);
/* 0011bf28: swc1 f20,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),f[20]);
L_0011bf2c:;
/* 0011bf2c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0011bf30: swc1 f3,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),f[3]);
/* 0011bf34: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0011bf38: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0011bf3c: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0011bf40: jr ra */ {uint64_t target=cpu(31);/* delay 0011bf44 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0011f510(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 0011f510: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0011f514: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0011f518: jal 0x001e0f50 */ set(31,UINT64_C(0x0011f520));/* delay 0011f51c */ set(4,sx(UINT32_C(0x00000af3)));nocturneFieldMovementCall(UINT32_C(0x001e0f50),UINT32_C(0x0011f518));
/* 0011f520: beq v0,zero,0x0011f568 */ {int taken=(cpu(2)==cpu(0));/* delay 0011f524 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_0011f568;}}
/* 0011f528: lui v0,0x56 */ set(2,sx(UINT32_C(0x00560000)));
/* 0011f52c: lw v1,-0x2a04(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0xffffd5fc)));
/* 0011f530: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 0011f534: bne v1,zero,0x0011f568 */ {int taken=(cpu(3)!=cpu(0));/* delay 0011f538 */ set(2,cpu(0));if(taken){goto L_0011f568;}}
/* 0011f53c: move a0,sp */ set(4,cpu(29));
/* 0011f540: jal 0x0011be98 */ set(31,UINT64_C(0x0011f548));/* delay 0011f544 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000004)));body_0011be98();
/* 0011f548: lui at,0x437a */ set(1,sx(UINT32_C(0x437a0000)));
/* 0011f54c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0011f550: lwc1 f0,0x0(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0011f554: c.lt.S f0,f1 */ (void)(EE_FPU_COMPARE_S(f[0],f[1],1)!=0);
/* 0011f558: bc1t 0x0011f564 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)!=0);/* delay 0011f55c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0011f564;}}
/* 0011f560: move v0,zero */ set(2,cpu(0));
L_0011f564:;
/* 0011f564: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
L_0011f568:;
/* 0011f568: jr ra */ {uint64_t target=cpu(31);/* delay 0011f56c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00123c10(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 00123c10: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00123c14: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 00123c18: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00123c1c: addiu s2,v0,-0x3b70 */ set(18,sx((uint32_t)cpu(2)+UINT32_C(0xffffc490)));
/* 00123c20: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00123c24: lui s3,0x30 */ set(19,sx(UINT32_C(0x00300000)));
/* 00123c28: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00123c2c: addiu v1,s3,-0x4080 */ set(3,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));
/* 00123c30: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00123c34: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00123c38: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00123c3c: swc1 f20,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[20]);
/* 00123c40: lw v0,0x70(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000070)));
/* 00123c44: blezl v0,0x00123c58 */ {int taken=((int64_t)cpu(2)<=0);if(taken){/* delay 00123c48 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000074)));goto L_00123c58;}}
/* 00123c4c: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00123c50: sw v0,0x70(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000070)),(uint32_t)cpu(2));
/* 00123c54: lw v0,0x74(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000074)));
L_00123c58:;
/* 00123c58: blezl v0,0x00123c6c */ {int taken=((int64_t)cpu(2)<=0);if(taken){/* delay 00123c5c */ lw(2,ea(3,(int32_t)UINT32_C(0x0000005c)));goto L_00123c6c;}}
/* 00123c60: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00123c64: sw v0,0x74(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000074)),(uint32_t)cpu(2));
/* 00123c68: lw v0,0x5c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000005c)));
L_00123c6c:;
/* 00123c6c: blez v0,0x00123c78 */ {int taken=((int64_t)cpu(2)<=0);/* delay 00123c70 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));if(taken){goto L_00123c78;}}
/* 00123c74: sw v0,0x5c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000005c)),(uint32_t)cpu(2));
L_00123c78:;
/* 00123c78: jal 0x001259f8 */ set(31,UINT64_C(0x00123c80));/* delay 00123c7c */ set(4,sx(UINT32_C(0x00000040)));nocturneFieldMovementCall(UINT32_C(0x001259f8),UINT32_C(0x00123c78));
/* 00123c80: beq v0,zero,0x001241d0 */ {int taken=(cpu(2)==cpu(0));/* delay 00123c84 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001241d0;}}
/* 00123c88: jal 0x001259c0 */ set(31,UINT64_C(0x00123c90));/* delay 00123c8c */ set(4,sx(UINT32_C(0x00000001)));nocturneFieldMovementCall(UINT32_C(0x001259c0),UINT32_C(0x00123c88));
/* 00123c90: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00123c94: beql v0,v1,0x001241cc */ {int taken=(cpu(2)==cpu(3));if(taken){/* delay 00123c98 */ set(2,cpu(0));goto L_001241cc;}}
/* 00123c9c: jal 0x0010e548 */ set(31,UINT64_C(0x00123ca4));/* delay 00123ca0 */ nocturneFieldMovementCall(UINT32_C(0x0010e548),UINT32_C(0x00123c9c));
/* 00123ca4: move a0,v0 */ set(4,cpu(2));
/* 00123ca8: beq a0,zero,0x001241d0 */ {int taken=(cpu(4)==cpu(0));/* delay 00123cac */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001241d0;}}
/* 00123cb0: jal 0x0010f1f8 */ set(31,UINT64_C(0x00123cb8));/* delay 00123cb4 */ nocturneFieldMovementCall(UINT32_C(0x0010f1f8),UINT32_C(0x00123cb0));
/* 00123cb8: move s1,v0 */ set(17,cpu(2));
/* 00123cbc: beq s1,zero,0x001241d0 */ {int taken=(cpu(17)==cpu(0));/* delay 00123cc0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001241d0;}}
/* 00123cc4: jal 0x0010df38 */ set(31,UINT64_C(0x00123ccc));/* delay 00123cc8 */ set(4,cpu(17));nocturneFieldMovementCall(UINT32_C(0x0010df38),UINT32_C(0x00123cc4));
/* 00123ccc: lqc2 vf11,0x0(s2) */ loadVu(11,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00123cd0: sqc2 vf10,0x0(s2) */ storeVu(10,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00123cd4: vsub.xyzw vf10,vf10,vf11 */ movementVu(10u,10u,11u,1u,15u,4u);
/* 00123cd8: vmul.xyz vf2,vf10,vf10 */ movementVu(2u,10u,10u,2u,14u,4u);
/* 00123cdc: vaddy.x vf2,vf2,vf2 */ movementVu(2u,2u,2u,0u,8u,1u);
/* 00123ce0: vaddz.x vf2,vf2,vf2 */ movementVu(2u,2u,2u,0u,8u,2u);
/* 00123ce4: vsqrt Q,vf2x */ movementSqrt(2u,0u,UINT32_C(0x00123ce4));
/* 00123ce8: vwaitq  */ (void)0;/* Value profile: actualQ already published; scheduling excluded. */
/* 00123cec: cfc2 v0,vc6 */ set(2u,sx(nocturneFieldMovementQ()));
/* 00123cf0: mtc1 v0,f20 */ f[20]=(uint32_t)cpu(2);
/* 00123cf4: lwc1 f0,-0x7f08(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff80f8)));
/* 00123cf8: c.lt.S f20,f0 */ (void)(EE_FPU_COMPARE_S(f[20],f[0],1)!=0);
/* 00123cfc: bc1f 0x00123d08 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 00123d00 */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));if(taken){goto L_00123d08;}}
/* 00123d04: clear f20 */ f[20]=0;
L_00123d08:;
/* 00123d08: jal 0x001e99c0 */ set(31,UINT64_C(0x00123d10));/* delay 00123d0c */ sw(ea(16,(int32_t)UINT32_C(0x000000c8)),f[20]);nocturneFieldMovementCall(UINT32_C(0x001e99c0),UINT32_C(0x00123d08));
/* 00123d10: move s4,v0 */ set(20,cpu(2));
/* 00123d14: lw v0,0x5c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000005c)));
/* 00123d18: blezl v0,0x00123d40 */ {int taken=((int64_t)cpu(2)<=0);if(taken){/* delay 00123d1c */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_00123d40;}}
/* 00123d20: jal 0x0010df38 */ set(31,UINT64_C(0x00123d28));/* delay 00123d24 */ set(4,cpu(17));nocturneFieldMovementCall(UINT32_C(0x0010df38),UINT32_C(0x00123d20));
/* 00123d28: sqc2 vf10,0x0(s2) */ storeVu(10,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00123d2c: addiu v1,s3,-0x4080 */ set(3,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));
/* 00123d30: move v0,zero */ set(2,cpu(0));
/* 00123d34: b 0x001241cc */ /* delay 00123d38 */ sw(ea(3,(int32_t)UINT32_C(0x000000c8)),(uint32_t)cpu(0));goto L_001241cc;
L_00123d40:;
/* 00123d40: slti v0,v0,0xa */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 00123d44: beq v0,zero,0x00123d68 */ {int taken=(cpu(2)==cpu(0));/* delay 00123d48 */ if(taken){goto L_00123d68;}}
/* 00123d4c: lui at,0x4080 */ set(1,sx(UINT32_C(0x40800000)));
/* 00123d50: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 00123d54: jal 0x001eac20 */ set(31,UINT64_C(0x00123d5c));/* delay 00123d58 */ f[12]=EE_FPU_MUL_S(f[20],f[12]);nocturneFieldMovementCall(UINT32_C(0x001eac20),UINT32_C(0x00123d54));
/* 00123d5c: b 0x00123d74 */ /* delay 00123d60 */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));goto L_00123d74;
L_00123d68:;
/* 00123d68: jal 0x001eac20 */ set(31,UINT64_C(0x00123d70));/* delay 00123d6c */ f[12]=f[20];nocturneFieldMovementCall(UINT32_C(0x001eac20),UINT32_C(0x00123d68));
/* 00123d70: addiu s0,s3,-0x4080 */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));
L_00123d74:;
/* 00123d74: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 00123d78: andi v0,v0,0xf */ set(2,cpu(2)&UINT32_C(0x0000000f));
/* 00123d7c: beq v0,zero,0x00123db8 */ {int taken=(cpu(2)==cpu(0));/* delay 00123d80 */ if(taken){goto L_00123db8;}}
/* 00123d84: jal 0x00122718 */ set(31,UINT64_C(0x00123d8c));/* delay 00123d88 */ nocturneFieldMovementCall(UINT32_C(0x00122718),UINT32_C(0x00123d84));
/* 00123d8c: jal 0x0010e548 */ set(31,UINT64_C(0x00123d94));/* delay 00123d90 */ nocturneFieldMovementCall(UINT32_C(0x0010e548),UINT32_C(0x00123d8c));
/* 00123d94: lui a1,0x53 */ set(5,sx(UINT32_C(0x00530000)));
/* 00123d98: move a0,v0 */ set(4,cpu(2));
/* 00123d9c: jal 0x0010f4d8 */ set(31,UINT64_C(0x00123da4));/* delay 00123da0 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001860)));nocturneFieldMovementCall(UINT32_C(0x0010f4d8),UINT32_C(0x00123d9c));
/* 00123da4: jal 0x00135380 */ set(31,UINT64_C(0x00123dac));/* delay 00123da8 */ body_00135380();
/* 00123dac: b 0x001241cc */ /* delay 00123db0 */ set(2,cpu(0));goto L_001241cc;
L_00123db8:;
/* 00123db8: jal 0x001e99c0 */ set(31,UINT64_C(0x00123dc0));/* delay 00123dbc */ nocturneFieldMovementCall(UINT32_C(0x001e99c0),UINT32_C(0x00123db8));
/* 00123dc0: lw a0,0x4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00123dc4: move s1,v0 */ set(17,cpu(2));
/* 00123dc8: li v0,0x2a */ set(2,sx(UINT32_C(0x0000002a)));
/* 00123dcc: bne a0,v0,0x00123dec */ {int taken=(cpu(4)!=cpu(2));/* delay 00123dd0 */ set(2,sx(UINT32_C(0x0000002c)));if(taken){goto L_00123dec;}}
/* 00123dd4: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00123dd8: li v0,0xd */ set(2,sx(UINT32_C(0x0000000d)));
/* 00123ddc: beq v1,v0,0x00123e14 */ {int taken=(cpu(3)==cpu(2));/* delay 00123de0 */ set(2,sx(UINT32_C(0x00000019)));if(taken){goto L_00123e14;}}
/* 00123de4: beq v1,v0,0x00123e14 */ {int taken=(cpu(3)==cpu(2));/* delay 00123de8 */ set(2,sx(UINT32_C(0x0000002c)));if(taken){goto L_00123e14;}}
L_00123dec:;
/* 00123dec: bnel a0,v0,0x00123e68 */ {int taken=(cpu(4)!=cpu(2));if(taken){/* delay 00123df0 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));goto L_00123e68;}}
/* 00123df4: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 00123df8: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00123dfc: beq v1,v0,0x00123e14 */ {int taken=(cpu(3)==cpu(2));/* delay 00123e00 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_00123e14;}}
/* 00123e04: beq v1,v0,0x00123e14 */ {int taken=(cpu(3)==cpu(2));/* delay 00123e08 */ set(2,sx(UINT32_C(0x00000018)));if(taken){goto L_00123e14;}}
/* 00123e0c: bne v1,v0,0x00123e68 */ {int taken=(cpu(3)!=cpu(2));/* delay 00123e10 */ set(4,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));if(taken){goto L_00123e68;}}
L_00123e14:;
/* 00123e14: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 00123e18: lw v1,-0x3ee4(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0xffffc11c)));
/* 00123e1c: beq v1,zero,0x00123f2c */ {int taken=(cpu(3)==cpu(0));/* delay 00123e20 */ set(16,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));if(taken){goto L_00123f2c;}}
/* 00123e24: lui at,0x43e1 */ set(1,sx(UINT32_C(0x43e10000)));
/* 00123e28: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00123e2c: lwc1 f0,0xb4(s0) */ f[0]=word(ea(16,(int32_t)UINT32_C(0x000000b4)));
/* 00123e30: add.S f0,f0,f20 */ f[0]=EE_FPU_ADD_S(f[0],f[20]);
/* 00123e34: c.lt.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],1)!=0);
/* 00123e38: bc1f 0x00123f2c */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 00123e3c */ sw(ea(16,(int32_t)UINT32_C(0x000000b4)),f[0]);if(taken){goto L_00123f2c;}}
/* 00123e40: jal 0x001259e0 */ set(31,UINT64_C(0x00123e48));/* delay 00123e44 */ set(4,sx(UINT32_C(0x00000040)));nocturneFieldMovementCall(UINT32_C(0x001259e0),UINT32_C(0x00123e40));
/* 00123e48: li v0,0x3c */ set(2,sx(UINT32_C(0x0000003c)));
/* 00123e4c: sw v0,0x80(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000080)),(uint32_t)cpu(2));
/* 00123e50: li a0,0x4 */ set(4,sx(UINT32_C(0x00000004)));
/* 00123e54: jal 0x00244a38 */ set(31,UINT64_C(0x00123e5c));/* delay 00123e58 */ sw(ea(16,(int32_t)UINT32_C(0x000000b4)),(uint32_t)cpu(0));nocturneFieldMovementCall(UINT32_C(0x00244a38),UINT32_C(0x00123e54));
/* 00123e5c: b 0x001241cc */ /* delay 00123e60 */ set(2,cpu(0));goto L_001241cc;
L_00123e68:;
/* 00123e68: lw a1,0xb0(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x000000b0)));
/* 00123e6c: bnel a1,zero,0x00123e8c */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 00123e70 */ f[0]=word(ea(4,(int32_t)UINT32_C(0x000000b4)));goto L_00123e8c;}}
/* 00123e74: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 00123e78: lw v0,-0x3ef0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0xffffc110)));
/* 00123e7c: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 00123e80: beq v0,zero,0x00123f20 */ {int taken=(cpu(2)==cpu(0));/* delay 00123e84 */ if(taken){goto L_00123f20;}}
/* 00123e88: lwc1 f0,0xb4(a0) */ f[0]=word(ea(4,(int32_t)UINT32_C(0x000000b4)));
L_00123e8c:;
/* 00123e8c: lui at,0x43e1 */ set(1,sx(UINT32_C(0x43e10000)));
/* 00123e90: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00123e94: add.S f0,f0,f20 */ f[0]=EE_FPU_ADD_S(f[0],f[20]);
/* 00123e98: bne a1,zero,0x00123ebc */ {int taken=(cpu(5)!=cpu(0));/* delay 00123e9c */ sw(ea(4,(int32_t)UINT32_C(0x000000b4)),f[0]);if(taken){goto L_00123ebc;}}
/* 00123ea0: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 00123ea4: lw v0,-0x3ef0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0xffffc110)));
/* 00123ea8: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 00123eac: beq v0,zero,0x00123ec0 */ {int taken=(cpu(2)==cpu(0));/* delay 00123eb0 */ set(5,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));if(taken){goto L_00123ec0;}}
/* 00123eb4: lui at,0x447a */ set(1,sx(UINT32_C(0x447a0000)));
/* 00123eb8: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
L_00123ebc:;
/* 00123ebc: addiu a1,s3,-0x4080 */ set(5,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));
L_00123ec0:;
/* 00123ec0: lwc1 f0,0xb4(a1) */ f[0]=word(ea(5,(int32_t)UINT32_C(0x000000b4)));
/* 00123ec4: c.lt.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],1)!=0);
/* 00123ec8: bc1f 0x00123f2c */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 00123ecc */ if(taken){goto L_00123f2c;}}
/* 00123ed0: lw v0,0xb0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x000000b0)));
/* 00123ed4: beq v0,zero,0x00123f00 */ {int taken=(cpu(2)==cpu(0));/* delay 00123ed8 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_00123f00;}}
/* 00123edc: lw v0,0xa4c(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000a4c)));
/* 00123ee0: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00123ee4: beq v0,zero,0x00123ef8 */ {int taken=(cpu(2)==cpu(0));/* delay 00123ee8 */ set(2,sx(UINT32_C(0x0000003c)));if(taken){goto L_00123ef8;}}
/* 00123eec: sw zero,0xb4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x000000b4)),(uint32_t)cpu(0));
/* 00123ef0: b 0x00123f2c */ /* delay 00123ef4 */ sw(ea(28,(int32_t)UINT32_C(0xffffab80)),(uint32_t)cpu(0));goto L_00123f2c;
L_00123ef8:;
/* 00123ef8: b 0x00123f08 */ /* delay 00123efc */ set(4,sx(UINT32_C(0x00000002)));goto L_00123f08;
L_00123f00:;
/* 00123f00: li v0,0x3c */ set(2,sx(UINT32_C(0x0000003c)));
/* 00123f04: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
L_00123f08:;
/* 00123f08: sw v0,-0x5480(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffab80)),(uint32_t)cpu(2));
/* 00123f0c: jal 0x00244a38 */ set(31,UINT64_C(0x00123f14));/* delay 00123f10 */ sw(ea(5,(int32_t)UINT32_C(0x000000b4)),(uint32_t)cpu(0));nocturneFieldMovementCall(UINT32_C(0x00244a38),UINT32_C(0x00123f0c));
/* 00123f14: b 0x00123f2c */ /* delay 00123f18 */ goto L_00123f2c;
L_00123f20:;
/* 00123f20: lui at,0x43e1 */ set(1,sx(UINT32_C(0x43e10000)));
/* 00123f24: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 00123f28: swc1 f0,0xb4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x000000b4)),f[0]);
L_00123f2c:;
/* 00123f2c: beq s4,s1,0x00123f3c */ {int taken=(cpu(20)==cpu(17));/* delay 00123f30 */ if(taken){goto L_00123f3c;}}
/* 00123f34: jal 0x002455b8 */ set(31,UINT64_C(0x00123f3c));/* delay 00123f38 */ nocturneFieldMovementCall(UINT32_C(0x002455b8),UINT32_C(0x00123f34));
L_00123f3c:;
/* 00123f3c: jal 0x001275d0 */ set(31,UINT64_C(0x00123f44));/* delay 00123f40 */ body_001275d0();
/* 00123f44: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00123f48: beq v0,v1,0x001241c8 */ {int taken=(cpu(2)==cpu(3));/* delay 00123f4c */ set(3,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));if(taken){goto L_001241c8;}}
/* 00123f50: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 00123f54: slti v0,v0,0xa */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 00123f58: beq v0,zero,0x00123ff0 */ {int taken=(cpu(2)==cpu(0));/* delay 00123f5c */ if(taken){goto L_00123ff0;}}
/* 00123f60: jal 0x0013fcd8 */ set(31,UINT64_C(0x00123f68));/* delay 00123f64 */ body_0013fcd8();
/* 00123f68: bne v0,zero,0x00123ff0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00123f6c */ if(taken){goto L_00123ff0;}}
/* 00123f70: jal 0x001e99c0 */ set(31,UINT64_C(0x00123f78));/* delay 00123f74 */ nocturneFieldMovementCall(UINT32_C(0x001e99c0),UINT32_C(0x00123f70));
/* 00123f78: lw v1,-0x560c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa9f4)));
/* 00123f7c: beq v1,v0,0x00123ff0 */ {int taken=(cpu(3)==cpu(2));/* delay 00123f80 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_00123ff0;}}
/* 00123f84: lbu v1,0xa42(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000a42))));
/* 00123f88: bne v1,zero,0x00123ff0 */ {int taken=(cpu(3)!=cpu(0));/* delay 00123f8c */ set(4,sx(UINT32_C(0x00530000)));if(taken){goto L_00123ff0;}}
/* 00123f90: jal 0x001097e8 */ set(31,UINT64_C(0x00123f98));/* delay 00123f94 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00001870)));nocturneFieldMovementCall(UINT32_C(0x001097e8),UINT32_C(0x00123f90));
/* 00123f98: jal 0x002456d0 */ set(31,UINT64_C(0x00123fa0));/* delay 00123f9c */ nocturneFieldMovementCall(UINT32_C(0x002456d0),UINT32_C(0x00123f98));
/* 00123fa0: beq v0,zero,0x00123ff0 */ {int taken=(cpu(2)==cpu(0));/* delay 00123fa4 */ sw(ea(28,(int32_t)UINT32_C(0xffffa9e8)),(uint32_t)cpu(2));if(taken){goto L_00123ff0;}}
/* 00123fa8: jal 0x00122718 */ set(31,UINT64_C(0x00123fb0));/* delay 00123fac */ nocturneFieldMovementCall(UINT32_C(0x00122718),UINT32_C(0x00123fa8));
/* 00123fb0: jal 0x0010e548 */ set(31,UINT64_C(0x00123fb8));/* delay 00123fb4 */ nocturneFieldMovementCall(UINT32_C(0x0010e548),UINT32_C(0x00123fb0));
/* 00123fb8: lui a1,0x53 */ set(5,sx(UINT32_C(0x00530000)));
/* 00123fbc: move a0,v0 */ set(4,cpu(2));
/* 00123fc0: jal 0x0010f4d8 */ set(31,UINT64_C(0x00123fc8));/* delay 00123fc4 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00001888)));nocturneFieldMovementCall(UINT32_C(0x0010f4d8),UINT32_C(0x00123fc0));
/* 00123fc8: jal 0x001e99c0 */ set(31,UINT64_C(0x00123fd0));/* delay 00123fcc */ nocturneFieldMovementCall(UINT32_C(0x001e99c0),UINT32_C(0x00123fc8));
/* 00123fd0: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00123fd4: lw a1,-0x5618(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa9e8)));
/* 00123fd8: addiu a0,a0,0x18a0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000018a0)));
/* 00123fdc: jal 0x001097e8 */ set(31,UINT64_C(0x00123fe4));/* delay 00123fe0 */ sw(ea(28,(int32_t)UINT32_C(0xffffa9f4)),(uint32_t)cpu(2));nocturneFieldMovementCall(UINT32_C(0x001097e8),UINT32_C(0x00123fdc));
/* 00123fe4: b 0x001241cc */ /* delay 00123fe8 */ set(2,cpu(0));goto L_001241cc;
L_00123ff0:;
/* 00123ff0: jal 0x001e99c0 */ set(31,UINT64_C(0x00123ff8));/* delay 00123ff4 */ set(17,sx(UINT32_C(0x00300000)));nocturneFieldMovementCall(UINT32_C(0x001e99c0),UINT32_C(0x00123ff0));
/* 00123ff8: addiu s0,s1,-0x3f40 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0xffffc0c0)));
/* 00123ffc: sw v0,-0x560c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa9f4)),(uint32_t)cpu(2));
/* 00124000: lw v0,0x44(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000044)));
/* 00124004: beq v0,zero,0x001240e0 */ {int taken=(cpu(2)==cpu(0));/* delay 00124008 */ if(taken){goto L_001240e0;}}
/* 0012400c: jal 0x0011f510 */ set(31,UINT64_C(0x00124014));/* delay 00124010 */ body_0011f510();
/* 00124014: beq v0,zero,0x001240e0 */ {int taken=(cpu(2)==cpu(0));/* delay 00124018 */ if(taken){goto L_001240e0;}}
/* 0012401c: lw v0,0x5c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000005c)));
/* 00124020: beq v0,zero,0x001240e0 */ {int taken=(cpu(2)==cpu(0));/* delay 00124024 */ if(taken){goto L_001240e0;}}
/* 00124028: jal 0x0013c9a0 */ set(31,UINT64_C(0x00124030));/* delay 0012402c */ body_0013c9a0();
/* 00124030: jal 0x00125990 */ set(31,UINT64_C(0x00124038));/* delay 00124034 */ set(4,sx(UINT32_C(0x00000001)));nocturneFieldMovementCall(UINT32_C(0x00125990),UINT32_C(0x00124030));
/* 00124038: jal 0x00125990 */ set(31,UINT64_C(0x00124040));/* delay 0012403c */ set(4,sx(UINT32_C(0x00000002)));nocturneFieldMovementCall(UINT32_C(0x00125990),UINT32_C(0x00124038));
/* 00124040: jal 0x00122718 */ set(31,UINT64_C(0x00124048));/* delay 00124044 */ nocturneFieldMovementCall(UINT32_C(0x00122718),UINT32_C(0x00124040));
/* 00124048: jal 0x001e1ab0 */ set(31,UINT64_C(0x00124050));/* delay 0012404c */ body_001e1ab0();
/* 00124050: addiu a1,gp,-0x55e0 */ set(5,sx((uint32_t)cpu(28)+UINT32_C(0xffffaa20)));
/* 00124054: addiu v0,s3,-0x4080 */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));
/* 00124058: li v1,0x40a */ set(3,sx(UINT32_C(0x0000040a)));
/* 0012405c: lw a0,0x8(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 00124060: sw v1,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 00124064: addiu v1,a0,-0x3 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffd)));
/* 00124068: sltiu v0,v1,0x8 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0012406c: beq v0,zero,0x001240cc */ {int taken=(cpu(2)==cpu(0));/* delay 00124070 */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));if(taken){goto L_001240cc;}}
/* 00124074: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 00124078: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 0012407c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00124080: lw v1,0x18c0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x000018c0)));
/* 00124084: jr v1 */ {uint64_t target=cpu(3);/* delay 00124088 */ switch((uint32_t)target){case UINT32_C(0x00124090):goto L_00124090;case UINT32_C(0x001240a8):goto L_001240a8;case UINT32_C(0x001240c0):goto L_001240c0;case UINT32_C(0x001240cc):goto L_001240cc;default:abort();}}
L_00124090:;
/* 00124090: li a0,0x2b */ set(4,sx(UINT32_C(0x0000002b)));
/* 00124094: jal 0x00125cb8 */ set(31,UINT64_C(0x0012409c));/* delay 00124098 */ set(5,sx(UINT32_C(0x000000c8)));nocturneFieldMovementCall(UINT32_C(0x00125cb8),UINT32_C(0x00124094));
/* 0012409c: b 0x001240d0 */ /* delay 001240a0 */ set(4,sx(UINT32_C(0x0000040a)));goto L_001240d0;
L_001240a8:;
/* 001240a8: li a0,0x2b */ set(4,sx(UINT32_C(0x0000002b)));
/* 001240ac: jal 0x00125cb8 */ set(31,UINT64_C(0x001240b4));/* delay 001240b0 */ set(5,sx(UINT32_C(0x000000c9)));nocturneFieldMovementCall(UINT32_C(0x00125cb8),UINT32_C(0x001240ac));
/* 001240b4: b 0x001240d0 */ /* delay 001240b8 */ set(4,sx(UINT32_C(0x0000040a)));goto L_001240d0;
L_001240c0:;
/* 001240c0: li a0,0x2b */ set(4,sx(UINT32_C(0x0000002b)));
/* 001240c4: jal 0x00125cb8 */ set(31,UINT64_C(0x001240cc));/* delay 001240c8 */ set(5,sx(UINT32_C(0x000000ca)));nocturneFieldMovementCall(UINT32_C(0x00125cb8),UINT32_C(0x001240c4));
L_001240cc:;
/* 001240cc: li a0,0x40a */ set(4,sx(UINT32_C(0x0000040a)));
L_001240d0:;
/* 001240d0: jal 0x001e7188 */ set(31,UINT64_C(0x001240d8));/* delay 001240d4 */ set(5,cpu(0));body_001e7188();
/* 001240d8: b 0x001241cc */ /* delay 001240dc */ set(2,sx(UINT32_C(0xffffffff)));goto L_001241cc;
L_001240e0:;
/* 001240e0: lwc1 f0,-0x7f04(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff80fc)));
/* 001240e4: c.lt.S f20,f0 */ (void)(EE_FPU_COMPARE_S(f[20],f[0],1)!=0);
/* 001240e8: bc1f 0x00124100 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 001240ec */ if(taken){goto L_00124100;}}
/* 001240f0: addiu a0,s1,-0x3f40 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0xffffc0c0)));
/* 001240f4: lw v1,0x44(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000044)));
/* 001240f8: beq v1,zero,0x001241cc */ {int taken=(cpu(3)==cpu(0));/* delay 001240fc */ set(2,cpu(0));if(taken){goto L_001241cc;}}
L_00124100:;
/* 00124100: jal 0x001259f8 */ set(31,UINT64_C(0x00124108));/* delay 00124104 */ set(4,sx(UINT32_C(0x00000010)));nocturneFieldMovementCall(UINT32_C(0x001259f8),UINT32_C(0x00124100));
/* 00124108: beq v0,zero,0x001241d0 */ {int taken=(cpu(2)==cpu(0));/* delay 0012410c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001241d0;}}
/* 00124110: addiu v0,s3,-0x4080 */ set(2,sx((uint32_t)cpu(19)+UINT32_C(0xffffbf80)));
/* 00124114: lw a1,0xc0(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x000000c0)));
/* 00124118: beql a1,zero,0x00124120 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 0012411c */ lw(5,ea(2,(int32_t)UINT32_C(0x000000bc)));goto L_00124120;}}
L_00124120:;
/* 00124120: addiu s0,gp,-0x55e0 */ set(16,sx((uint32_t)cpu(28)+UINT32_C(0xffffaa20)));
/* 00124124: move a0,a1 */ set(4,cpu(5));
/* 00124128: sw a1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
/* 0012412c: jal 0x0028cca8 */ set(31,UINT64_C(0x00124134));/* delay 00124130 */ f[12]=f[20];nocturneFieldMovementCall(UINT32_C(0x0028cca8),UINT32_C(0x0012412c));
/* 00124134: beq v0,zero,0x001241c8 */ {int taken=(cpu(2)==cpu(0));/* delay 00124138 */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));if(taken){goto L_001241c8;}}
/* 0012413c: addiu v0,s1,-0x3f40 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0xffffc0c0)));
/* 00124140: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00124144: lw v1,0x44(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000044)));
/* 00124148: beq v1,a0,0x00124160 */ {int taken=(cpu(3)==cpu(4));/* delay 0012414c */ if(taken){goto L_00124160;}}
/* 00124150: lwc1 f0,-0x7f00(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffff8100)));
/* 00124154: c.lt.S f0,f20 */ (void)(EE_FPU_COMPARE_S(f[0],f[20],1)!=0);
/* 00124158: bc1f 0x00124190 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);/* delay 0012415c */ if(taken){goto L_00124190;}}
L_00124160:;
/* 00124160: jal 0x0013c9a0 */ set(31,UINT64_C(0x00124168));/* delay 00124164 */ body_0013c9a0();
/* 00124168: jal 0x00125990 */ set(31,UINT64_C(0x00124170));/* delay 0012416c */ set(4,sx(UINT32_C(0x00000001)));nocturneFieldMovementCall(UINT32_C(0x00125990),UINT32_C(0x00124168));
/* 00124170: jal 0x00125990 */ set(31,UINT64_C(0x00124178));/* delay 00124174 */ set(4,sx(UINT32_C(0x00000002)));nocturneFieldMovementCall(UINT32_C(0x00125990),UINT32_C(0x00124170));
/* 00124178: jal 0x00122718 */ set(31,UINT64_C(0x00124180));/* delay 0012417c */ nocturneFieldMovementCall(UINT32_C(0x00122718),UINT32_C(0x00124178));
/* 00124180: jal 0x001e1ab0 */ set(31,UINT64_C(0x00124188));/* delay 00124184 */ body_001e1ab0();
/* 00124188: b 0x001241cc */ /* delay 0012418c */ set(2,sx(UINT32_C(0xffffffff)));goto L_001241cc;
L_00124190:;
/* 00124190: jal 0x0028cfb0 */ set(31,UINT64_C(0x00124198));/* delay 00124194 */ nocturneFieldMovementCall(UINT32_C(0x0028cfb0),UINT32_C(0x00124190));
/* 00124198: li a0,0xf */ set(4,sx(UINT32_C(0x0000000f)));
/* 0012419c: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 001241a0: jal 0x002c18d8 */ set(31,UINT64_C(0x001241a8));/* delay 001241a4 */ set(6,sx(UINT32_C(0x0000003f)));nocturneFieldMovementCall(UINT32_C(0x002c18d8),UINT32_C(0x001241a0));
/* 001241a8: li a0,0x80 */ set(4,sx(UINT32_C(0x00000080)));
/* 001241ac: li a1,0x80 */ set(5,sx(UINT32_C(0x00000080)));
/* 001241b0: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 001241b4: jal 0x00104fe0 */ set(31,UINT64_C(0x001241bc));/* delay 001241b8 */ set(7,sx(UINT32_C(0x00000006)));nocturneFieldMovementCall(UINT32_C(0x00104fe0),UINT32_C(0x001241b4));
/* 001241bc: lw v0,-0x561c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa9e4)));
/* 001241c0: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001241c4: sw v0,-0x561c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa9e4)),(uint32_t)cpu(2));
L_001241c8:;
/* 001241c8: move v0,zero */ set(2,cpu(0));
L_001241cc:;
/* 001241cc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001241d0:;
/* 001241d0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001241d4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001241d8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001241dc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001241e0: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001241e4: lwc1 f20,0x30(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001241e8: jr ra */ {uint64_t target=cpu(31);/* delay 001241ec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001275d0(void){
uint64_t incoming=cpu(31);
/* 001275d0: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 001275d4: jr ra */ {uint64_t target=cpu(31);/* delay 001275d8 */ lw(2,ea(3,(int32_t)UINT32_C(0xffffc004)));checkReturn(target,incoming);return;}
}
static void body_00134fd8(void){
uint64_t incoming=cpu(31);
/* 00134fd8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00134fdc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00134fe0: jal 0x001225e8 */ set(31,UINT64_C(0x00134fe8));/* delay 00134fe4 */ nocturneFieldMovementCall(UINT32_C(0x001225e8),UINT32_C(0x00134fe0));
/* 00134fe8: move a0,v0 */ set(4,cpu(2));
/* 00134fec: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 00134ff0: beq v0,zero,0x00135008 */ {int taken=(cpu(2)==cpu(0));/* delay 00134ff4 */ set(5,sx(UINT32_C(0x00000400)));if(taken){goto L_00135008;}}
/* 00134ff8: lw a0,0x0(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00134ffc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00135000: j 0x00110138 */ /* delay 00135004 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneFieldMovementCall(UINT32_C(0x00110138),UINT32_C(0x00135000));return;
L_00135008:;
/* 00135008: lw a0,0x0(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0013500c: li a1,0x200 */ set(5,sx(UINT32_C(0x00000200)));
/* 00135010: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00135014: j 0x00110138 */ /* delay 00135018 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneFieldMovementCall(UINT32_C(0x00110138),UINT32_C(0x00135014));return;
}
static void body_00135380(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 00135380: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00135384: sd s0,0x30(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00135388: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0013538c: jal 0x001225e8 */ set(31,UINT64_C(0x00135394));/* delay 00135390 */ nocturneFieldMovementCall(UINT32_C(0x001225e8),UINT32_C(0x0013538c));
/* 00135394: move s0,v0 */ set(16,cpu(2));
/* 00135398: beql s0,zero,0x001356c4 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 0013539c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));goto L_001356c4;}}
/* 001353a0: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001353a4: beql a0,zero,0x001356c4 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 001353a8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));goto L_001356c4;}}
/* 001353ac: jal 0x00110350 */ set(31,UINT64_C(0x001353b4));/* delay 001353b0 */ nocturneFieldMovementCall(UINT32_C(0x00110350),UINT32_C(0x001353ac));
/* 001353b4: jal 0x0010df50 */ set(31,UINT64_C(0x001353bc));/* delay 001353b8 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));nocturneFieldMovementCall(UINT32_C(0x0010df50),UINT32_C(0x001353b4));
/* 001353bc: jal 0x002c0b60 */ set(31,UINT64_C(0x001353c4));/* delay 001353c0 */ nocturneFieldMovementCall(UINT32_C(0x002c0b60),UINT32_C(0x001353bc));
/* 001353c4: lui at,0x4334 */ set(1,sx(UINT32_C(0x43340000)));
/* 001353c8: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 001353cc: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 001353d0: lwc1 f2,-0x7d4c(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffff82b4)));
/* 001353d4: addiu v0,v0,-0x4080 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffbf80)));
/* 001353d8: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 001353dc: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001353e0: nop  */ 
/* 001353e4: nop  */ 
/* 001353e8: div.S f0,f0,f2 */ f[0]=EE_FPU_DIV_S(f[0],f[2]);
/* 001353ec: swc1 f0,0x128(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000128)),f[0]);
/* 001353f0: jal 0x0010df38 */ set(31,UINT64_C(0x001353f8));/* delay 001353f4 */ sw(ea(2,(int32_t)UINT32_C(0x00000124)),f[0]);nocturneFieldMovementCall(UINT32_C(0x0010df38),UINT32_C(0x001353f0));
/* 001353f8: sqc2 vf10,0x0(sp) */ storeVu(10,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001353fc: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 00135400: lwc1 f3,0x0(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00135404: addiu v0,v0,-0x4080 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffbf80)));
/* 00135408: lwc1 f4,0x4(sp) */ f[4]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0013540c: lwc1 f0,0x8(sp) */ f[0]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00135410: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00135414: lwc1 f5,0x100(v0) */ f[5]=word(ea(2,(int32_t)UINT32_C(0x00000100)));
/* 00135418: lwc1 f1,0x104(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000104)));
/* 0013541c: lwc1 f2,0x108(v0) */ f[2]=word(ea(2,(int32_t)UINT32_C(0x00000108)));
/* 00135420: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00135424: swc1 f5,0x10c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000010c)),f[5]);
/* 00135428: lw a0,0x1c(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x0000001c)));
/* 0013542c: swc1 f0,0x108(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000108)),f[0]);
/* 00135430: swc1 f1,0x110(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000110)),f[1]);
/* 00135434: swc1 f2,0x114(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000114)),f[2]);
/* 00135438: swc1 f3,0x100(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000100)),f[3]);
/* 0013543c: jal 0x0010ddf0 */ set(31,UINT64_C(0x00135444));/* delay 00135440 */ sw(ea(2,(int32_t)UINT32_C(0x00000104)),f[4]);nocturneFieldMovementCall(UINT32_C(0x0010ddf0),UINT32_C(0x0013543c));
/* 00135444: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 00135448: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
/* 0013544c: jal 0x0010ddf0 */ set(31,UINT64_C(0x00135454));/* delay 00135450 */ lw(4,ea(2,(int32_t)UINT32_C(0x0000001c)));nocturneFieldMovementCall(UINT32_C(0x0010ddf0),UINT32_C(0x0013544c));
/* 00135454: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00135458: beql v0,zero,0x00135480 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0013545c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffab7c)));goto L_00135480;}}
/* 00135460: lw a0,0x1c(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x0000001c)));
/* 00135464: jal 0x0010ddf0 */ set(31,UINT64_C(0x0013546c));/* delay 00135468 */ set(5,sx(UINT32_C(0x00000001)));nocturneFieldMovementCall(UINT32_C(0x0010ddf0),UINT32_C(0x00135464));
/* 0013546c: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00135470: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
/* 00135474: jal 0x0010ddf0 */ set(31,UINT64_C(0x0013547c));/* delay 00135478 */ lw(4,ea(2,(int32_t)UINT32_C(0x0000001c)));nocturneFieldMovementCall(UINT32_C(0x0010ddf0),UINT32_C(0x00135474));
/* 0013547c: lw v0,-0x5484(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffab7c)));
L_00135480:;
/* 00135480: beq v0,zero,0x001354a8 */ {int taken=(cpu(2)==cpu(0));/* delay 00135484 */ if(taken){goto L_001354a8;}}
/* 00135488: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0013548c: lw v1,0x1c(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x0000001c)));
/* 00135490: addiu a0,v1,0x40 */ set(4,sx((uint32_t)cpu(3)+UINT32_C(0x00000040)));
/* 00135494: addiu v1,v1,0x70 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000070)));
/* 00135498: lq v0,0x0(a0) */ requestLq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0013549c: sq v0,0x0(v1) */ sq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001354a0: b 0x001355cc */ /* delay 001354a4 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_001355cc;
L_001354a8:;
/* 001354a8: jal 0x00134fd8 */ set(31,UINT64_C(0x001354b0));/* delay 001354ac */ body_00134fd8();
/* 001354b0: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001354b4: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 001354b8: lw v1,0x1c(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x0000001c)));
/* 001354bc: move a2,a1 */ set(6,cpu(5));
/* 001354c0: addiu v1,v1,0x70 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000070)));
/* 001354c4: lq v0,0x0(v1) */ requestLq(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001354c8: sq v0,0x0(a0) */ sq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001354cc: lwc1 f3,0x20(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001354d0: lwc1 f2,0x0(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001354d4: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001354d8: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 001354dc: sub.S f0,f3,f2 */ f[0]=EE_FPU_SUB_S(f[3],f[2]);
/* 001354e0: abs.S f0,f0 */ f[0u]=f[0u]&UINT32_C(0x7fffffff);
/* 001354e4: c.lt.S f0,f1 */ (void)(EE_FPU_COMPARE_S(f[0],f[1],1)!=0);
/* 001354e8: bc1fl 0x001354f8 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);if(taken){/* delay 001354ec */ f[0]=EE_FPU_SUB_S(f[2],f[3]);goto L_001354f8;}}
/* 001354f0: b 0x00135514 */ /* delay 001354f4 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),f[2]);goto L_00135514;
L_001354f8:;
/* 001354f8: lui at,0x4040 */ set(1,sx(UINT32_C(0x40400000)));
/* 001354fc: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00135500: nop  */ 
/* 00135504: nop  */ 
/* 00135508: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 0013550c: add.S f0,f3,f0 */ f[0]=EE_FPU_ADD_S(f[3],f[0]);
/* 00135510: swc1 f0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),f[0]);
L_00135514:;
/* 00135514: lwc1 f3,0x24(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000024)));
/* 00135518: lwc1 f2,0x4(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000004)));
/* 0013551c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00135520: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00135524: sub.S f0,f3,f2 */ f[0]=EE_FPU_SUB_S(f[3],f[2]);
/* 00135528: abs.S f0,f0 */ f[0u]=f[0u]&UINT32_C(0x7fffffff);
/* 0013552c: c.lt.S f0,f1 */ (void)(EE_FPU_COMPARE_S(f[0],f[1],1)!=0);
/* 00135530: bc1fl 0x00135548 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);if(taken){/* delay 00135534 */ f[0]=EE_FPU_SUB_S(f[2],f[3]);goto L_00135548;}}
/* 00135538: lw v0,0x1c(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 0013553c: b 0x00135568 */ /* delay 00135540 */ sw(ea(2,(int32_t)UINT32_C(0x00000074)),f[2]);goto L_00135568;
L_00135548:;
/* 00135548: lui at,0x4040 */ set(1,sx(UINT32_C(0x40400000)));
/* 0013554c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00135550: lw v0,0x1c(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 00135554: nop  */ 
/* 00135558: nop  */ 
/* 0013555c: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 00135560: add.S f0,f3,f0 */ f[0]=EE_FPU_ADD_S(f[3],f[0]);
/* 00135564: swc1 f0,0x74(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000074)),f[0]);
L_00135568:;
/* 00135568: lwc1 f3,0x28(sp) */ f[3]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0013556c: lwc1 f2,0x8(sp) */ f[2]=word(ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00135570: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 00135574: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 00135578: sub.S f0,f3,f2 */ f[0]=EE_FPU_SUB_S(f[3],f[2]);
/* 0013557c: abs.S f0,f0 */ f[0u]=f[0u]&UINT32_C(0x7fffffff);
/* 00135580: c.lt.S f0,f1 */ (void)(EE_FPU_COMPARE_S(f[0],f[1],1)!=0);
/* 00135584: bc1fl 0x00135598 */ {int taken=(((nocturneFieldMovementFcsr()>>23)&1u)==0);if(taken){/* delay 00135588 */ f[0]=EE_FPU_SUB_S(f[2],f[3]);goto L_00135598;}}
/* 0013558c: lw v0,0x1c(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 00135590: b 0x001355b8 */ /* delay 00135594 */ sw(ea(2,(int32_t)UINT32_C(0x00000078)),f[2]);goto L_001355b8;
L_00135598:;
/* 00135598: lui at,0x4040 */ set(1,sx(UINT32_C(0x40400000)));
/* 0013559c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 001355a0: lw v0,0x1c(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 001355a4: nop  */ 
/* 001355a8: nop  */ 
/* 001355ac: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 001355b0: add.S f0,f3,f0 */ f[0]=EE_FPU_ADD_S(f[3],f[0]);
/* 001355b4: swc1 f0,0x78(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000078)),f[0]);
L_001355b8:;
/* 001355b8: lw v0,0x1c(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x0000001c)));
/* 001355bc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001355c0: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 001355c4: swc1 f0,0x7c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000007c)),f[0]);
/* 001355c8: lw v1,0x4(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));
L_001355cc:;
/* 001355cc: beq v1,zero,0x00135674 */ {int taken=(cpu(3)==cpu(0));/* delay 001355d0 */ set(4,cpu(3));if(taken){goto L_00135674;}}
/* 001355d4: lw v0,0x1c(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x0000001c)));
/* 001355d8: move a1,sp */ set(5,cpu(29));
/* 001355dc: lw v1,0x1c(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x0000001c)));
/* 001355e0: lwc1 f1,0x70(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000070)));
/* 001355e4: swc1 f1,0x70(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000070)),f[1]);
/* 001355e8: lwc1 f0,0x74(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000074)));
/* 001355ec: swc1 f0,0x74(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000074)),f[0]);
/* 001355f0: lwc1 f1,0x78(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000078)));
/* 001355f4: swc1 f1,0x78(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000078)),f[1]);
/* 001355f8: lwc1 f0,0x7c(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x0000007c)));
/* 001355fc: swc1 f0,0x7c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000007c)),f[0]);
/* 00135600: lwc1 f1,0x40(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000040)));
/* 00135604: swc1 f1,0x40(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000040)),f[1]);
/* 00135608: lwc1 f0,0x44(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000044)));
/* 0013560c: swc1 f0,0x44(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000044)),f[0]);
/* 00135610: lwc1 f1,0x48(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000048)));
/* 00135614: swc1 f1,0x48(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000048)),f[1]);
/* 00135618: lwc1 f0,0x4c(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x0000004c)));
/* 0013561c: swc1 f0,0x4c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000004c)),f[0]);
/* 00135620: lwc1 f1,0x50(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000050)));
/* 00135624: swc1 f1,0x50(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000050)),f[1]);
/* 00135628: lwc1 f0,0x54(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000054)));
/* 0013562c: swc1 f0,0x54(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000054)),f[0]);
/* 00135630: lwc1 f1,0x58(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000058)));
/* 00135634: swc1 f1,0x58(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000058)),f[1]);
/* 00135638: lwc1 f0,0x5c(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x0000005c)));
/* 0013563c: swc1 f0,0x5c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000005c)),f[0]);
/* 00135640: lwc1 f1,0x50(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000050)));
/* 00135644: swc1 f1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[1]);
/* 00135648: lwc1 f0,0x54(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000054)));
/* 0013564c: swc1 f0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[0]);
/* 00135650: lwc1 f1,0x58(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000058)));
/* 00135654: swc1 f1,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[1]);
/* 00135658: lwc1 f0,0x5c(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x0000005c)));
/* 0013565c: jal 0x0010dea8 */ set(31,UINT64_C(0x00135664));/* delay 00135660 */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),f[0]);nocturneFieldMovementCall(UINT32_C(0x0010dea8),UINT32_C(0x0013565c));
/* 00135664: lw a0,0x4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 00135668: jal 0x0010ded8 */ set(31,UINT64_C(0x00135670));/* delay 0013566c */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));nocturneFieldMovementCall(UINT32_C(0x0010ded8),UINT32_C(0x00135668));
/* 00135670: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
L_00135674:;
/* 00135674: lw v1,0x1c(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x0000001c)));
/* 00135678: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0013567c: addiu v0,v0,-0x3ce0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffc320)));
/* 00135680: lwc1 f0,0x70(v1) */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000070)));
/* 00135684: swc1 f0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),f[0]);
/* 00135688: lwc1 f1,0x74(v1) */ f[1]=word(ea(3,(int32_t)UINT32_C(0x00000074)));
/* 0013568c: swc1 f1,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),f[1]);
/* 00135690: lwc1 f0,0x78(v1) */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000078)));
/* 00135694: swc1 f0,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),f[0]);
/* 00135698: lwc1 f1,0x7c(v1) */ f[1]=word(ea(3,(int32_t)UINT32_C(0x0000007c)));
/* 0013569c: swc1 f1,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),f[1]);
/* 001356a0: lwc1 f0,0x50(v1) */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000050)));
/* 001356a4: swc1 f0,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),f[0]);
/* 001356a8: lwc1 f1,0x54(v1) */ f[1]=word(ea(3,(int32_t)UINT32_C(0x00000054)));
/* 001356ac: swc1 f1,0x14(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000014)),f[1]);
/* 001356b0: lwc1 f0,0x58(v1) */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000058)));
/* 001356b4: swc1 f0,0x18(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000018)),f[0]);
/* 001356b8: lwc1 f1,0x5c(v1) */ f[1]=word(ea(3,(int32_t)UINT32_C(0x0000005c)));
/* 001356bc: swc1 f1,0x1c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000001c)),f[1]);
/* 001356c0: ld s0,0x30(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));
L_001356c4:;
/* 001356c4: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001356c8: jr ra */ {uint64_t target=cpu(31);/* delay 001356cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_0013c9a0(void){
uint64_t incoming=cpu(31);
/* 0013c9a0: lw v1,-0x53b8(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffac48)));
/* 0013c9a4: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0013c9a8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0013c9ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0013c9b0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013c9b4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0013c9b8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0013c9bc: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0013c9c0: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0013c9c4: blez v1,0x0013c9f4 */ {int taken=((int64_t)cpu(3)<=0);/* delay 0013c9c8 */ sw(ea(28,(int32_t)UINT32_C(0xffffac5c)),(uint32_t)cpu(2));if(taken){goto L_0013c9f4;}}
/* 0013c9cc: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0013c9d0: move s1,v1 */ set(17,cpu(3));
/* 0013c9d4: addiu v0,v0,-0x3160 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffcea0)));
L_0013c9d8:;
/* 0013c9d8: addiu s1,s1,-0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffff)));
/* 0013c9dc: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 0013c9e0: nop  */ 
/* 0013c9e4: nop  */ 
/* 0013c9e8: nop  */ 
/* 0013c9ec: bne s1,zero,0x0013c9d8 */ {int taken=(cpu(17)!=cpu(0));/* delay 0013c9f0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));if(taken){goto L_0013c9d8;}}
L_0013c9f4:;
/* 0013c9f4: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 0013c9f8: sw v0,-0x53ac(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac54)),(uint32_t)cpu(2));
/* 0013c9fc: sw v0,-0x53b4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffac4c)),(uint32_t)cpu(2));
/* 0013ca00: jal 0x0010e588 */ set(31,UINT64_C(0x0013ca08));/* delay 0013ca04 */ sw(ea(28,(int32_t)UINT32_C(0xffffac50)),(uint32_t)cpu(2));nocturneFieldMovementCall(UINT32_C(0x0010e588),UINT32_C(0x0013ca00));
/* 0013ca08: move s3,v0 */ set(19,cpu(2));
/* 0013ca0c: beq s3,zero,0x0013caac */ {int taken=(cpu(19)==cpu(0));/* delay 0013ca10 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0013caac;}}
/* 0013ca14: lw a1,-0x53b8(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffac48)));
/* 0013ca18: blez a1,0x0013caac */ {int taken=((int64_t)cpu(5)<=0);/* delay 0013ca1c */ set(17,cpu(0));if(taken){goto L_0013caac;}}
/* 0013ca20: lui v1,0x30 */ set(3,sx(UINT32_C(0x00300000)));
/* 0013ca24: lui v0,0x56 */ set(2,sx(UINT32_C(0x00560000)));
/* 0013ca28: addiu s4,v0,-0x24d0 */ set(20,sx((uint32_t)cpu(2)+UINT32_C(0xffffdb30)));
/* 0013ca2c: addiu s2,v1,-0x3260 */ set(18,sx((uint32_t)cpu(3)+UINT32_C(0xffffcda0)));
/* 0013ca30: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0013ca34: nop  */ 
L_0013ca38:;
/* 0013ca38: addiu s2,s2,0x4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000004)));
/* 0013ca3c: lw v1,0x20(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 0013ca40: lw a0,0x4(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0013ca44: bltz a0,0x0013ca98 */ {int taken=((int64_t)cpu(4)<0);/* delay 0013ca48 */ set(3,sx((uint32_t)cpu(4)<<2));if(taken){goto L_0013ca98;}}
/* 0013ca4c: addu v1,v1,s4 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(20)));
/* 0013ca50: li a2,0xd */ set(6,sx(UINT32_C(0x0000000d)));
/* 0013ca54: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0013ca58: move a0,s3 */ set(4,cpu(19));
/* 0013ca5c: jal 0x0010f208 */ set(31,UINT64_C(0x0013ca64));/* delay 0013ca60 */ lw(5,ea(2,(int32_t)UINT32_C(0x00000000)));nocturneFieldMovementCall(UINT32_C(0x0010f208),UINT32_C(0x0013ca5c));
/* 0013ca64: jal 0x00116050 */ set(31,UINT64_C(0x0013ca6c));/* delay 0013ca68 */ set(4,cpu(2));body_00116050();
/* 0013ca6c: move s0,v0 */ set(16,cpu(2));
/* 0013ca70: jal 0x0010a078 */ set(31,UINT64_C(0x0013ca78));/* delay 0013ca74 */ set(4,cpu(16));nocturneFieldMovementCall(UINT32_C(0x0010a078),UINT32_C(0x0013ca70));
/* 0013ca78: beq v0,zero,0x0013ca98 */ {int taken=(cpu(2)==cpu(0));/* delay 0013ca7c */ lw(5,ea(28,(int32_t)UINT32_C(0xffffac48)));if(taken){goto L_0013ca98;}}
/* 0013ca80: jal 0x0010e548 */ set(31,UINT64_C(0x0013ca88));/* delay 0013ca84 */ nocturneFieldMovementCall(UINT32_C(0x0010e548),UINT32_C(0x0013ca80));
/* 0013ca88: move a1,s0 */ set(5,cpu(16));
/* 0013ca8c: jal 0x0010f598 */ set(31,UINT64_C(0x0013ca94));/* delay 0013ca90 */ set(4,cpu(2));body_0010f598();
/* 0013ca94: lw a1,-0x53b8(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffac48)));
L_0013ca98:;
/* 0013ca98: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 0013ca9c: slt v0,s1,a1 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(5));
/* 0013caa0: bnel v0,zero,0x0013ca38 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0013caa4 */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));goto L_0013ca38;}}
/* 0013caa8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0013caac:;
/* 0013caac: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0013cab0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0013cab4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0013cab8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0013cabc: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0013cac0: jr ra */ {uint64_t target=cpu(31);/* delay 0013cac4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_0013fcd8(void){
uint64_t incoming=cpu(31);
/* 0013fcd8: lw a0,-0x53b8(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffac48)));
/* 0013fcdc: blez a0,0x0013fd1c */ {int taken=((int64_t)cpu(4)<=0);/* delay 0013fce0 */ set(5,cpu(0));if(taken){goto L_0013fd1c;}}
/* 0013fce4: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 0013fce8: move a2,a0 */ set(6,cpu(4));
/* 0013fcec: addiu a0,v0,-0x3160 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0xffffcea0)));
/* 0013fcf0: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0013fcf4: nop  */ 
L_0013fcf8:;
/* 0013fcf8: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 0013fcfc: bne v1,zero,0x0013fd20 */ {int taken=(cpu(3)!=cpu(0));/* delay 0013fd00 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0013fd20;}}
/* 0013fd04: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0013fd08: slt v0,a1,a2 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(6));
/* 0013fd0c: nop  */ 
/* 0013fd10: nop  */ 
/* 0013fd14: bnel v0,zero,0x0013fcf8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0013fd18 */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));goto L_0013fcf8;}}
L_0013fd1c:;
/* 0013fd1c: move v0,zero */ set(2,cpu(0));
L_0013fd20:;
/* 0013fd20: jr ra */ {uint64_t target=cpu(31);/* delay 0013fd24 */ checkReturn(target,incoming);return;}
}
static void body_00145410(void){
uint64_t incoming=cpu(31);
/* 00145410: lw a0,-0x534c(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffacb4)));
/* 00145414: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00145418: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0014541c: jal 0x002c1730 */ set(31,UINT64_C(0x00145424));/* delay 00145420 */ body_002c1730();
/* 00145424: lui v0,0x30 */ set(2,sx(UINT32_C(0x00300000)));
/* 00145428: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0014542c: sw zero,-0x3fe0(v0) */ sw(ea(2,(int32_t)UINT32_C(0xffffc020)),(uint32_t)cpu(0));
/* 00145430: jr ra */ {uint64_t target=cpu(31);/* delay 00145434 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001e1ab0(void){
uint64_t incoming=cpu(31);
/* 001e1ab0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001e1ab4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001e1ab8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001e1abc: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001e1ac0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e1ac4: li s2,0x1 */ set(18,sx(UINT32_C(0x00000001)));
/* 001e1ac8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e1acc: li s3,0x3ea */ set(19,sx(UINT32_C(0x000003ea)));
/* 001e1ad0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001e1ad4: lui s4,0x54 */ set(20,sx(UINT32_C(0x00540000)));
/* 001e1ad8: b 0x001e1b14 */ /* delay 001e1adc */ set(17,cpu(0));goto L_001e1b14;
L_001e1ae0:;
/* 001e1ae0: jal 0x00101130 */ set(31,UINT64_C(0x001e1ae8));/* delay 001e1ae4 */ body_00101130();
/* 001e1ae8: move s0,v0 */ set(16,cpu(2));
/* 001e1aec: lw v0,0x20(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 001e1af0: bnel v0,s3,0x001e1b14 */ {int taken=(cpu(2)!=cpu(19));if(taken){/* delay 001e1af4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));goto L_001e1b14;}}
/* 001e1af8: move a1,s0 */ set(5,cpu(16));
/* 001e1afc: jal 0x002d4748 */ set(31,UINT64_C(0x001e1b04));/* delay 001e1b00 */ set(4,sx((uint32_t)cpu(20)+UINT32_C(0xffffa828)));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x001e1afc));
/* 001e1b04: move a0,s0 */ set(4,cpu(16));
/* 001e1b08: jal 0x00101738 */ set(31,UINT64_C(0x001e1b10));/* delay 001e1b0c */ set(5,cpu(0));nocturneFieldMovementCall(UINT32_C(0x00101738),UINT32_C(0x001e1b08));
/* 001e1b10: move s1,zero */ set(17,cpu(0));
L_001e1b14:;
/* 001e1b14: jal 0x001010d8 */ set(31,UINT64_C(0x001e1b1c));/* delay 001e1b18 */ set(4,cpu(18));body_001010d8();
/* 001e1b1c: move a0,s2 */ set(4,cpu(18));
/* 001e1b20: slt v0,s1,v0 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(2));
/* 001e1b24: bne v0,zero,0x001e1ae0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001e1b28 */ set(5,cpu(17));if(taken){goto L_001e1ae0;}}
/* 001e1b2c: addiu s2,s2,0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 001e1b30: slti v0,s2,0x3 */ set(2,(int64_t)cpu(18)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 001e1b34: bne v0,zero,0x001e1b14 */ {int taken=(cpu(2)!=cpu(0));/* delay 001e1b38 */ set(17,cpu(0));if(taken){goto L_001e1b14;}}
/* 001e1b3c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001e1b40: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001e1b44: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e1b48: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e1b4c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001e1b50: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001e1b54: jr ra */ {uint64_t target=cpu(31);/* delay 001e1b58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001e7188(void){
uint64_t incoming=cpu(31);
/* 001e7188: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001e718c: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e7190: move s0,a1 */ set(16,cpu(5));
/* 001e7194: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e7198: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001e719c: jal 0x00145410 */ set(31,UINT64_C(0x001e71a4));/* delay 001e71a0 */ set(17,cpu(4));body_00145410();
/* 001e71a4: li a0,0xf */ set(4,sx(UINT32_C(0x0000000f)));
/* 001e71a8: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 001e71ac: jal 0x002c18d8 */ set(31,UINT64_C(0x001e71b4));/* delay 001e71b0 */ set(6,sx(UINT32_C(0x0000003f)));nocturneFieldMovementCall(UINT32_C(0x002c18d8),UINT32_C(0x001e71ac));
/* 001e71b4: jal 0x0012c360 */ set(31,UINT64_C(0x001e71bc));/* delay 001e71b8 */ nocturneFieldMovementCall(UINT32_C(0x0012c360),UINT32_C(0x001e71b4));
/* 001e71bc: move a1,sp */ set(5,cpu(29));
/* 001e71c0: slt a3,zero,s0 */ set(7,(int64_t)cpu(0)<(int64_t)cpu(16));
/* 001e71c4: li a0,0x13 */ set(4,sx(UINT32_C(0x00000013)));
/* 001e71c8: li a2,0x8 */ set(6,sx(UINT32_C(0x00000008)));
/* 001e71cc: sw s1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 001e71d0: sw zero,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001e71d4: jal 0x00102848 */ set(31,UINT64_C(0x001e71dc));/* delay 001e71d8 */ sw(ea(28,(int32_t)UINT32_C(0xffffb5e0)),(uint32_t)cpu(16));nocturneFieldMovementCall(UINT32_C(0x00102848),UINT32_C(0x001e71d4));
/* 001e71dc: jal 0x00109f08 */ set(31,UINT64_C(0x001e71e4));/* delay 001e71e0 */ nocturneFieldMovementCall(UINT32_C(0x00109f08),UINT32_C(0x001e71dc));
/* 001e71e4: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001e71e8: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001e71ec: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001e71f0: jr ra */ {uint64_t target=cpu(31);/* delay 001e71f4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_0010f1c0(void){
uint64_t incoming=cpu(31);
/* 0010f1c0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0010f1c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f1c8: move s0,a1 */ set(16,cpu(5));
/* 0010f1cc: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f1d0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f1d4: jal 0x0010f1f8 */ set(31,UINT64_C(0x0010f1dc));/* delay 0010f1d8 */ lw(17,ea(4,(int32_t)UINT32_C(0x00000018)));nocturneFieldMovementCall(UINT32_C(0x0010f1f8),UINT32_C(0x0010f1d4));
/* 0010f1dc: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f1e0: sw s0,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(16));
/* 0010f1e4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f1e8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f1ec: jr ra */ {uint64_t target=cpu(31);/* delay 0010f1f0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002c1730(void){
uint64_t incoming=cpu(31);
/* 002c1730: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c1734: move a1,zero */ set(5,cpu(0));
/* 002c1738: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002c173c: li a0,0x30 */ set(4,sx(UINT32_C(0x00000030)));
/* 002c1740: move a2,sp */ set(6,cpu(29));
/* 002c1744: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c1748: jal 0x002c10e8 */ set(31,UINT64_C(0x002c1750));/* delay 002c174c */ set(7,sx(UINT32_C(0x00000010)));nocturneFieldMovementCall(UINT32_C(0x002c10e8),UINT32_C(0x002c1748));
/* 002c1750: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c1754: jr ra */ {uint64_t target=cpu(31);/* delay 002c1758 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint32_t nocturneFieldMovementBody(uint32_t entry){switch(entry){
case UINT32_C(0x001010d8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001010d8();return 1u;case UINT32_C(0x00101130):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00101130();return 1u;case UINT32_C(0x0010f598):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010f598();return 1u;case UINT32_C(0x00116050):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00116050();return 1u;case UINT32_C(0x0011be98):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0011be98();return 1u;case UINT32_C(0x0011f510):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0011f510();return 1u;case UINT32_C(0x00123c10):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00123c10();return 1u;case UINT32_C(0x001275d0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001275d0();return 1u;case UINT32_C(0x00134fd8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00134fd8();return 1u;case UINT32_C(0x00135380):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00135380();return 1u;case UINT32_C(0x0013c9a0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0013c9a0();return 1u;case UINT32_C(0x0013fcd8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0013fcd8();return 1u;case UINT32_C(0x00145410):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00145410();return 1u;case UINT32_C(0x001e1ab0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001e1ab0();return 1u;case UINT32_C(0x001e7188):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001e7188();return 1u;case UINT32_C(0x0010f1c0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010f1c0();return 1u;case UINT32_C(0x002c1730):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002c1730();return 1u;
default:return 0u;}}

uint64_t ps2FieldProcessCount_001010D8(uint64_t a0){
set(4u,a0);
body_001010d8();
return cpu(2);
}

uint64_t ps2FieldProcessAt_00101130(uint64_t a0,uint64_t a1){
set(4u,a0);
set(5u,a1);
body_00101130();
return cpu(2);
}

void ps2FieldEndSceneScript_0010F598(uint64_t a0,uint64_t a1){
set(4u,a0);
set(5u,a1);
body_0010f598();
return;
}

uint64_t ps2FieldBasicGetData_00116050(uint64_t a0){
set(4u,a0);
body_00116050();
return cpu(2);
}

void ps2FieldRunDistanceAngle_0011BE98(uint64_t a0,uint64_t a1){
set(4u,a0);
set(5u,a1);
body_0011be98();
return;
}

uint64_t ps2FieldSpecialEncounterCheck_0011F510(void){
body_0011f510();
return cpu(2);
}

uint64_t ps2FieldMovementEncounterCheck_00123C10(void){
body_00123c10();
return cpu(2);
}

uint64_t ps2FieldNextLoadStatus_001275D0(void){
body_001275d0();
return cpu(2);
}

void ps2FieldPlayerShadowOn_00134FD8(void){
body_00134fd8();
return;
}

void ps2FieldPlayerPositionRotation_00135380(void){
body_00135380();
return;
}

void ps2FieldEventHitEnd_0013C9A0(void){
body_0013c9a0();
return;
}

uint64_t ps2FieldEventHitProcessCheck_0013FCD8(void){
body_0013fcd8();
return cpu(2);
}

void ps2FieldBgmStop_00145410(void){
body_00145410();
return;
}

void ps2FieldKillScripts_001E1AB0(void){
body_001e1ab0();
return;
}

void ps2FieldCallBattle_001E7188(uint64_t a0,uint64_t a1){
set(4u,a0);
set(5u,a1);
body_001e7188();
return;
}

uint64_t ps2FieldPublishActiveUnit_0010F1C0(uint64_t a0,uint64_t a1){
set(4u,a0);
set(5u,a1);
body_0010f1c0();
return cpu(2);
}
