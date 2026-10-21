/* Complete23 registered script/process/frame carrier variants; fixed native-PC statements.
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




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}






static void requestLq(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneFieldMovementCpuWrite(d,q);}
static void requestPacked(unsigned kind,unsigned d,unsigned s,unsigned t){
 uint32_t a[4],c[4],q[4];nocturneFieldMovementCpuRead(s,a);nocturneFieldMovementCpuRead(t,c);
 if(kind==0){q[0]=c[0];q[1]=c[1];q[2]=a[0];q[3]=a[1];}
 else if(kind==1){q[0]=a[2];q[1]=a[3];q[2]=c[2];q[3]=c[3];}
 else if(kind==2){for(unsigned i=0;i<4;i++)q[i]=a[i]&c[i];}
 else if(kind==3){for(unsigned i=0;i<4;i++)q[i]=~(a[i]|c[i]);}
 else if(kind==5){for(unsigned i=0;i<4;i++)q[i]=a[i]^c[i];}
 else{uint8_t x[16],y[16],z[16];memcpy(x,a,16);memcpy(y,c,16);for(unsigned i=0;i<16;i++)z[i]=(uint8_t)(x[i]-y[i]);memcpy(q,z,16);}
 nocturneFieldMovementCpuWrite(d,q);
}













static void carrierPsubw(unsigned d,unsigned s,unsigned t){uint32_t a[4],b[4],q[4];nocturneFieldMovementCpuRead(s,a);nocturneFieldMovementCpuRead(t,b);for(unsigned k=0;k<4;k++)q[k]=a[k]-b[k];nocturneFieldMovementCpuWrite(d,q);}
static void body_0010f4d8(void);
static void body_0010a0d0(void);
static void body_00109d98(void);
static void body_00109b48(void);
static void body_001098e0(void);
static void body_00109848(void);
static void body_00109cb8(void);
static void body_001015b0(void);
static void body_00100760(void);
static void body_001097e8(void);
static void body_00101898(void);
static void body_002d5ab4(void);
static void body_00101738(void);
static void body_00100e08(void);
static void body_00100d70(void);
static void body_001005e8(void);
static void body_00101b80(void);
static void body_0010a210(void);
static void body_00101ab0(void);
static void body_00101aa8(void);
static void body_00109e50(void);
static void body_00109888(void);
static void body_002a8bd8(void);
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
/* 0010f500: jal 0x002d4748 */ set(31,UINT64_C(0x0010f508));/* delay 0010f504 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff770)));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x0010f500));
/* 0010f508: b 0x0010f580 */ /* delay 0010f50c */ set(2,cpu(0));goto L_0010f580;
L_0010f510:;
/* 0010f510: bne s0,zero,0x0010f528 */ {int taken=(cpu(16)!=cpu(0));/* delay 0010f514 */ if(taken){goto L_0010f528;}}
/* 0010f518: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0010f51c: b 0x0010f544 */ /* delay 0010f520 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff788)));goto L_0010f544;
L_0010f528:;
/* 0010f528: jal 0x0010a0d0 */ set(31,UINT64_C(0x0010f530));/* delay 0010f52c */ set(4,cpu(17));body_0010a0d0();
/* 0010f530: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 0010f534: move s2,v0 */ set(18,cpu(2));
/* 0010f538: addiu a0,a0,-0x860 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff7a0)));
/* 0010f53c: bgez s2,0x0010f558 */ {int taken=((int64_t)cpu(18)>=0);/* delay 0010f540 */ set(5,cpu(16));if(taken){goto L_0010f558;}}
L_0010f544:;
/* 0010f544: jal 0x002d4748 */ set(31,UINT64_C(0x0010f54c));/* delay 0010f548 */ nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x0010f544));
/* 0010f54c: b 0x0010f580 */ /* delay 0010f550 */ set(2,cpu(0));goto L_0010f580;
L_0010f558:;
/* 0010f558: jal 0x00101898 */ set(31,UINT64_C(0x0010f560));/* delay 0010f55c */ set(4,cpu(16));body_00101898();
/* 0010f560: li a0,0x3ea */ set(4,sx(UINT32_C(0x000003ea)));
/* 0010f564: beq v0,zero,0x0010f578 */ {int taken=(cpu(2)==cpu(0));/* delay 0010f568 */ set(6,cpu(18));if(taken){goto L_0010f578;}}
/* 0010f56c: b 0x0010f580 */ /* delay 0010f570 */ set(2,cpu(0));goto L_0010f580;
L_0010f578:;
/* 0010f578: jal 0x00109d98 */ set(31,UINT64_C(0x0010f580));/* delay 0010f57c */ set(5,cpu(17));body_00109d98();
L_0010f580:;
/* 0010f580: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010f584: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010f588: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010f58c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010f590: jr ra */ {uint64_t target=cpu(31);/* delay 0010f594 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0010a0d0(void){
uint64_t incoming=cpu(31);
/* 0010a0d0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0010a0d4: move t1,zero */ set(9,cpu(0));
/* 0010a0d8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010a0dc: move s3,a1 */ set(19,cpu(5));
/* 0010a0e0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010a0e4: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 0010a0e8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010a0ec: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010a0f0: beq a0,zero,0x0010a1ac */ {int taken=(cpu(4)==cpu(0));/* delay 0010a0f4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_0010a1ac;}}
/* 0010a0f8: lw a3,0x10(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0010a0fc: addiu t0,a0,0x20 */ set(8,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 0010a100: slt v0,t1,a3 */ set(2,(int64_t)cpu(9)<(int64_t)cpu(7));
/* 0010a104: beq v0,zero,0x0010a14c */ {int taken=(cpu(2)==cpu(0));/* delay 0010a108 */ set(6,cpu(0));if(taken){goto L_0010a14c;}}
/* 0010a10c: lw v0,0x0(t0) */ lw(2,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 0010a110: bnel v0,zero,0x0010a120 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0010a114 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));goto L_0010a120;}}
/* 0010a118: b 0x0010a148 */ /* delay 0010a11c */ lw(2,ea(8,(int32_t)UINT32_C(0x0000000c)));goto L_0010a148;
L_0010a120:;
/* 0010a120: sll v0,a2,0x4 */ set(2,sx((uint32_t)cpu(6)<<4));
/* 0010a124: slt v1,a2,a3 */ set(3,(int64_t)cpu(6)<(int64_t)cpu(7));
/* 0010a128: beq v1,zero,0x0010a14c */ {int taken=(cpu(3)==cpu(0));/* delay 0010a12c */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(8)));if(taken){goto L_0010a14c;}}
/* 0010a130: lw v0,0x0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 0010a134: nop  */ 
/* 0010a138: nop  */ 
/* 0010a13c: bnel v0,zero,0x0010a120 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0010a140 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));goto L_0010a120;}}
/* 0010a144: lw v0,0xc(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x0000000c)));
L_0010a148:;
/* 0010a148: addu t1,a0,v0 */ set(9,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
L_0010a14c:;
/* 0010a14c: bne t1,zero,0x0010a160 */ {int taken=(cpu(9)!=cpu(0));/* delay 0010a150 */ set(3,sx((uint32_t)cpu(6)<<4));if(taken){goto L_0010a160;}}
/* 0010a154: b 0x0010a1ac */ /* delay 0010a158 */ set(2,sx(UINT32_C(0xffffffff)));goto L_0010a1ac;
L_0010a160:;
/* 0010a160: addu v1,v1,t0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(8)));
/* 0010a164: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 0010a168: blez v0,0x0010a1a8 */ {int taken=((int64_t)cpu(2)<=0);/* delay 0010a16c */ set(17,cpu(0));if(taken){goto L_0010a1a8;}}
/* 0010a170: move s2,v1 */ set(18,cpu(3));
/* 0010a174: move s0,t1 */ set(16,cpu(9));
/* 0010a178: move a0,s0 */ set(4,cpu(16));
/* 0010a17c: nop  */ 
L_0010a180:;
/* 0010a180: addiu s0,s0,0x20 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
/* 0010a184: jal 0x002d5ab4 */ set(31,UINT64_C(0x0010a18c));/* delay 0010a188 */ set(5,cpu(19));body_002d5ab4();
/* 0010a18c: beq v0,zero,0x0010a1ac */ {int taken=(cpu(2)==cpu(0));/* delay 0010a190 */ set(2,cpu(17));if(taken){goto L_0010a1ac;}}
/* 0010a194: lw v0,0x8(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 0010a198: addiu s1,s1,0x1 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 0010a19c: slt v0,s1,v0 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(2));
/* 0010a1a0: bne v0,zero,0x0010a180 */ {int taken=(cpu(2)!=cpu(0));/* delay 0010a1a4 */ set(4,cpu(16));if(taken){goto L_0010a180;}}
L_0010a1a8:;
/* 0010a1a8: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
L_0010a1ac:;
/* 0010a1ac: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010a1b0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010a1b4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0010a1b8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0010a1bc: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0010a1c0: jr ra */ {uint64_t target=cpu(31);/* delay 0010a1c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00109d98(void){
uint64_t incoming=cpu(31);
/* 00109d98: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00109d9c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109da0: move s0,a0 */ set(16,cpu(4));
/* 00109da4: move a0,a1 */ set(4,cpu(5));
/* 00109da8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00109dac: jal 0x00109b48 */ set(31,UINT64_C(0x00109db4));/* delay 00109db0 */ set(5,cpu(6));body_00109b48();
/* 00109db4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00109db8: move a0,s0 */ set(4,cpu(16));
/* 00109dbc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109dc0: move a1,v0 */ set(5,cpu(2));
/* 00109dc4: j 0x00109cb8 */ /* delay 00109dc8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00109cb8();return;
}
static void body_00109b48(void){
uint64_t incoming=cpu(31);
/* 00109b48: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00109b4c: move t4,a0 */ set(12,cpu(4));
/* 00109b50: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109b54: lui v1,0x3057 */ set(3,sx(UINT32_C(0x30570000)));
/* 00109b58: ori v1,v1,0x4c46 */ set(3,cpu(3)|UINT32_C(0x00004c46));
/* 00109b5c: move t3,a1 */ set(11,cpu(5));
/* 00109b60: lw a0,0x8(t4) */ lw(4,ea(12,(int32_t)UINT32_C(0x00000008)));
/* 00109b64: move a2,zero */ set(6,cpu(0));
/* 00109b68: move a3,zero */ set(7,cpu(0));
/* 00109b6c: move t0,zero */ set(8,cpu(0));
/* 00109b70: move t1,zero */ set(9,cpu(0));
/* 00109b74: move t2,zero */ set(10,cpu(0));
/* 00109b78: addiu a1,t4,0x20 */ set(5,sx((uint32_t)cpu(12)+UINT32_C(0x00000020)));
/* 00109b7c: bne a0,v1,0x00109c48 */ {int taken=(cpu(4)!=cpu(3));/* delay 00109b80 */ set(2,cpu(0));if(taken){goto L_00109c48;}}
/* 00109b84: lw t6,0x10(t4) */ lw(14,ea(12,(int32_t)UINT32_C(0x00000010)));
/* 00109b88: blez t6,0x00109c34 */ {int taken=((int64_t)cpu(14)<=0);/* delay 00109b8c */ set(13,cpu(0));if(taken){goto L_00109c34;}}
/* 00109b90: sll a0,t5,0x4 */ set(4,sx((uint32_t)cpu(13)<<4));
/* 00109b94: nop  */ 
L_00109b98:;
/* 00109b98: addu v0,a0,a1 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 00109b9c: lw v0,0x0(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00109ba0: sltiu v1,v0,0x5 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 00109ba4: beql v1,zero,0x00109c48 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00109ba8 */ set(2,cpu(0));goto L_00109c48;}}
/* 00109bac: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00109bb0: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 00109bb4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00109bb8: lw v1,-0x1d60(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffffe2a0)));
/* 00109bbc: jr v1 */ {uint64_t target=cpu(3);/* delay 00109bc0 */ switch((uint32_t)target){case UINT32_C(0x00109bc8):goto L_00109bc8;case UINT32_C(0x00109bd8):goto L_00109bd8;case UINT32_C(0x00109be8):goto L_00109be8;case UINT32_C(0x00109bf8):goto L_00109bf8;case UINT32_C(0x00109c18):goto L_00109c18;default:abort();}}
L_00109bc8:;
/* 00109bc8: addu v0,a0,a1 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 00109bcc: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 00109bd0: b 0x00109c24 */ /* delay 00109bd4 */ set(6,sx((uint32_t)cpu(12)+(uint32_t)cpu(3)));goto L_00109c24;
L_00109bd8:;
/* 00109bd8: addu v0,a0,a1 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 00109bdc: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 00109be0: b 0x00109c24 */ /* delay 00109be4 */ set(7,sx((uint32_t)cpu(12)+(uint32_t)cpu(3)));goto L_00109c24;
L_00109be8:;
/* 00109be8: addu v0,a0,a1 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 00109bec: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 00109bf0: b 0x00109c24 */ /* delay 00109bf4 */ set(8,sx((uint32_t)cpu(12)+(uint32_t)cpu(3)));goto L_00109c24;
L_00109bf8:;
/* 00109bf8: addu v1,a0,a1 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 00109bfc: lw v0,0x8(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 00109c00: beql v0,zero,0x00109c28 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00109c04 */ set(13,sx((uint32_t)cpu(13)+UINT32_C(0x00000001)));goto L_00109c28;}}
/* 00109c08: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 00109c0c: b 0x00109c24 */ /* delay 00109c10 */ set(9,sx((uint32_t)cpu(12)+(uint32_t)cpu(2)));goto L_00109c24;
L_00109c18:;
/* 00109c18: addu v0,a0,a1 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 00109c1c: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 00109c20: addu t2,t4,v1 */ set(10,sx((uint32_t)cpu(12)+(uint32_t)cpu(3)));
L_00109c24:;
/* 00109c24: addiu t5,t5,0x1 */ set(13,sx((uint32_t)cpu(13)+UINT32_C(0x00000001)));
L_00109c28:;
/* 00109c28: slt v0,t5,t6 */ set(2,(int64_t)cpu(13)<(int64_t)cpu(14));
/* 00109c2c: bne v0,zero,0x00109b98 */ {int taken=(cpu(2)!=cpu(0));/* delay 00109c30 */ set(4,sx((uint32_t)cpu(13)<<4));if(taken){goto L_00109b98;}}
L_00109c34:;
/* 00109c34: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109c38: move a0,t4 */ set(4,cpu(12));
/* 00109c3c: j 0x001098e0 */ /* delay 00109c40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001098e0();return;
L_00109c48:;
/* 00109c48: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109c4c: jr ra */ {uint64_t target=cpu(31);/* delay 00109c50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001098e0(void){
uint64_t incoming=cpu(31);
/* 001098e0: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001098e4: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001098e8: move s3,a0 */ set(19,cpu(4));
/* 001098ec: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001098f0: move s0,t3 */ set(16,cpu(11));
/* 001098f4: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001098f8: move s2,a1 */ set(18,cpu(5));
/* 001098fc: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00109900: move s4,a2 */ set(20,cpu(6));
/* 00109904: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00109908: move s6,t1 */ set(22,cpu(9));
/* 0010990c: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00109910: move s7,t0 */ set(23,cpu(8));
/* 00109914: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00109918: move s8,t2 */ set(30,cpu(10));
/* 0010991c: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00109920: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00109924: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00109928: beq s3,zero,0x00109960 */ {int taken=(cpu(19)==cpu(0));/* delay 0010992c */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(7));if(taken){goto L_00109960;}}
/* 00109930: beq s2,zero,0x00109b18 */ {int taken=(cpu(18)==cpu(0));/* delay 00109934 */ set(2,cpu(0));if(taken){goto L_00109b18;}}
/* 00109938: beql s4,zero,0x00109b1c */ {int taken=(cpu(20)==cpu(0));if(taken){/* delay 0010993c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_00109b1c;}}
/* 00109940: beql s7,zero,0x00109b1c */ {int taken=(cpu(23)==cpu(0));if(taken){/* delay 00109944 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_00109b1c;}}
/* 00109948: bltzl s0,0x00109b1c */ {int taken=((int64_t)cpu(16)<0);if(taken){/* delay 0010994c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_00109b1c;}}
/* 00109950: lw v0,0x8(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 00109954: slt v0,s0,v0 */ set(2,(int64_t)cpu(16)<(int64_t)cpu(2));
/* 00109958: bne v0,zero,0x00109968 */ {int taken=(cpu(2)!=cpu(0));/* delay 0010995c */ if(taken){goto L_00109968;}}
L_00109960:;
/* 00109960: b 0x00109b18 */ /* delay 00109964 */ set(2,cpu(0));goto L_00109b18;
L_00109968:;
/* 00109968: jal 0x002a8af8 */ set(31,UINT64_C(0x00109970));/* delay 0010996c */ set(4,sx(UINT32_C(0x000000f4)));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x00109968));
/* 00109970: move s1,v0 */ set(17,cpu(2));
/* 00109974: beq s1,zero,0x00109b18 */ {int taken=(cpu(17)==cpu(0));/* delay 00109978 */ set(21,sx((uint32_t)cpu(16)<<5));if(taken){goto L_00109b18;}}
/* 0010997c: move a2,zero */ set(6,cpu(0));
/* 00109980: addu a0,s5,s4 */ set(4,sx((uint32_t)cpu(21)+(uint32_t)cpu(20)));
/* 00109984: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00109988: sll v1,v0,0x18 */ set(3,sx((uint32_t)cpu(2)<<24));
/* 0010998c: beq v1,zero,0x001099b4 */ {int taken=(cpu(3)==cpu(0));/* delay 00109990 */ sb(ea(17,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));if(taken){goto L_001099b4;}}
/* 00109994: move a3,a0 */ set(7,cpu(4));
L_00109998:;
/* 00109998: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 0010999c: addu v1,a3,a2 */ set(3,sx((uint32_t)cpu(7)+(uint32_t)cpu(6)));
/* 001099a0: addu a1,s1,a2 */ set(5,sx((uint32_t)cpu(17)+(uint32_t)cpu(6)));
/* 001099a4: lbu v0,0x0(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001099a8: sll a0,v0,0x18 */ set(4,sx((uint32_t)cpu(2)<<24));
/* 001099ac: bne a0,zero,0x00109998 */ {int taken=(cpu(4)!=cpu(0));/* delay 001099b0 */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));if(taken){goto L_00109998;}}
L_001099b4:;
/* 001099b4: addu v0,s5,s4 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(20)));
/* 001099b8: addiu a0,s1,0x3c */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x0000003c)));
/* 001099bc: lw v1,0x18(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 001099c0: addiu v0,s1,0x20 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000020)));
/* 001099c4: sw zero,0x1c(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 001099c8: li a2,0x1b */ set(6,sx(UINT32_C(0x0000001b)));
/* 001099cc: sw v1,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
L_001099d0:;
/* 001099d0: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 001099d4: sb zero,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 001099d8: sw zero,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001099dc: addiu a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 001099e0: nop  */ 
/* 001099e4: bgez a2,0x001099d0 */ {int taken=((int64_t)cpu(6)>=0);/* delay 001099e8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));if(taken){goto L_001099d0;}}
/* 001099ec: sw s2,0xb0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000b0)),(uint32_t)cpu(18));
/* 001099f0: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 001099f4: lh a0,0x14(s3) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 001099f8: lw v1,0x0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001099fc: sw s7,0xbc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000bc)),(uint32_t)cpu(23));
/* 00109a00: sw v1,0xb8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000b8)),(uint32_t)cpu(3));
/* 00109a04: sw s8,0xc4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000c4)),(uint32_t)cpu(30));
/* 00109a08: sw s0,0xc8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000c8)),(uint32_t)cpu(16));
/* 00109a0c: sw v0,0xcc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000cc)),(uint32_t)cpu(2));
/* 00109a10: sw s3,0xac(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000ac)),(uint32_t)cpu(19));
/* 00109a14: sw s4,0xb4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000b4)),(uint32_t)cpu(20));
/* 00109a18: sw s6,0xc0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000c0)),(uint32_t)cpu(22));
/* 00109a1c: sw zero,0xd0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000d0)),(uint32_t)cpu(0));
/* 00109a20: sw zero,0xd4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000d4)),(uint32_t)cpu(0));
/* 00109a24: sw zero,0xd8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000d8)),(uint32_t)cpu(0));
/* 00109a28: sw zero,0xdc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000dc)),(uint32_t)cpu(0));
/* 00109a2c: sw zero,0xe0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000e0)),(uint32_t)cpu(0));
/* 00109a30: sw zero,0xe4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000e4)),(uint32_t)cpu(0));
/* 00109a34: sw zero,0xe8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000e8)),(uint32_t)cpu(0));
/* 00109a38: blez a0,0x00109a88 */ {int taken=((int64_t)cpu(4)<=0);/* delay 00109a3c */ sw(ea(17,(int32_t)UINT32_C(0x000000ec)),(uint32_t)cpu(0));if(taken){goto L_00109a88;}}
/* 00109a40: jal 0x002a8af8 */ set(31,UINT64_C(0x00109a48));/* delay 00109a44 */ set(4,sx((uint32_t)cpu(4)<<2));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x00109a40));
/* 00109a48: lh v1,0x14(s3) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(19,(int32_t)UINT32_C(0x00000014))));
/* 00109a4c: sw v0,0xdc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000dc)),(uint32_t)cpu(2));
/* 00109a50: blez v1,0x00109a8c */ {int taken=((int64_t)cpu(3)<=0);/* delay 00109a54 */ set(6,cpu(0));if(taken){goto L_00109a8c;}}
/* 00109a58: move a0,v1 */ set(4,cpu(3));
/* 00109a5c: move v1,v0 */ set(3,cpu(2));
L_00109a60:;
/* 00109a60: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 00109a64: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 00109a68: slt v0,a2,a0 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(4));
/* 00109a6c: nop  */ 
/* 00109a70: nop  */ 
/* 00109a74: bne v0,zero,0x00109a60 */ {int taken=(cpu(2)!=cpu(0));/* delay 00109a78 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000004)));if(taken){goto L_00109a60;}}
/* 00109a7c: b 0x00109a90 */ /* delay 00109a80 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(19,(int32_t)UINT32_C(0x00000016))));goto L_00109a90;
L_00109a88:;
/* 00109a88: sw zero,0xdc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000dc)),(uint32_t)cpu(0));
L_00109a8c:;
/* 00109a8c: lh a0,0x16(s3) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(19,(int32_t)UINT32_C(0x00000016))));
L_00109a90:;
/* 00109a90: blezl a0,0x00109ad4 */ {int taken=((int64_t)cpu(4)<=0);if(taken){/* delay 00109a94 */ sw(ea(17,(int32_t)UINT32_C(0x000000e0)),(uint32_t)cpu(0));goto L_00109ad4;}}
/* 00109a98: jal 0x002a8af8 */ set(31,UINT64_C(0x00109aa0));/* delay 00109a9c */ set(4,sx((uint32_t)cpu(4)<<2));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x00109a98));
/* 00109aa0: lh a0,0x16(s3) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(19,(int32_t)UINT32_C(0x00000016))));
/* 00109aa4: sw v0,0xe0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000e0)),(uint32_t)cpu(2));
/* 00109aa8: blez a0,0x00109ad4 */ {int taken=((int64_t)cpu(4)<=0);/* delay 00109aac */ set(6,cpu(0));if(taken){goto L_00109ad4;}}
/* 00109ab0: move v1,v0 */ set(3,cpu(2));
/* 00109ab4: nop  */ 
L_00109ab8:;
/* 00109ab8: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 00109abc: sw zero,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 00109ac0: slt v0,a2,a0 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(4));
/* 00109ac4: nop  */ 
/* 00109ac8: nop  */ 
/* 00109acc: bne v0,zero,0x00109ab8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00109ad0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000004)));if(taken){goto L_00109ab8;}}
L_00109ad4:;
/* 00109ad4: beql s6,zero,0x00109aec */ {int taken=(cpu(22)==cpu(0));if(taken){/* delay 00109ad8 */ set(4,cpu(17));goto L_00109aec;}}
/* 00109adc: jal 0x001cda40 */ set(31,UINT64_C(0x00109ae4));/* delay 00109ae0 */ set(4,cpu(22));nocturneFieldMovementCall(UINT32_C(0x001cda40),UINT32_C(0x00109adc));
/* 00109ae4: sw v0,0xcc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x000000cc)),(uint32_t)cpu(2));
/* 00109ae8: move a0,s1 */ set(4,cpu(17));
L_00109aec:;
/* 00109aec: jal 0x00109848 */ set(31,UINT64_C(0x00109af4));/* delay 00109af0 */ set(16,sx((uint32_t)cpu(20)+(uint32_t)cpu(21)));body_00109848();
/* 00109af4: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00109af8: addiu a0,a0,-0x1d90 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffe270)));
/* 00109afc: jal 0x002d4748 */ set(31,UINT64_C(0x00109b04));/* delay 00109b00 */ set(5,cpu(16));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x00109afc));
/* 00109b04: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00109b08: addiu a0,a0,-0x1d78 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffe288)));
/* 00109b0c: jal 0x001097e8 */ set(31,UINT64_C(0x00109b14));/* delay 00109b10 */ set(5,cpu(16));body_001097e8();
/* 00109b14: move v0,s1 */ set(2,cpu(17));
L_00109b18:;
/* 00109b18: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
L_00109b1c:;
/* 00109b1c: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00109b20: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00109b24: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00109b28: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00109b2c: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00109b30: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00109b34: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00109b38: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00109b3c: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00109b40: jr ra */ {uint64_t target=cpu(31);/* delay 00109b44 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_00109848(void){
uint64_t incoming=cpu(31);
/* 00109848: lw v0,-0x57d4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa82c)));
/* 0010984c: bnel v0,zero,0x00109868 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00109850 */ sw(ea(4,(int32_t)UINT32_C(0x000000e8)),(uint32_t)cpu(2));goto L_00109868;}}
/* 00109854: sw a0,-0x57d8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa828)),(uint32_t)cpu(4));
/* 00109858: sw a0,-0x57d4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa82c)),(uint32_t)cpu(4));
/* 0010985c: sw zero,0xec(a0) */ sw(ea(4,(int32_t)UINT32_C(0x000000ec)),(uint32_t)cpu(0));
/* 00109860: b 0x00109874 */ /* delay 00109864 */ sw(ea(4,(int32_t)UINT32_C(0x000000e8)),(uint32_t)cpu(0));goto L_00109874;
L_00109868:;
/* 00109868: sw a0,0xec(v0) */ sw(ea(2,(int32_t)UINT32_C(0x000000ec)),(uint32_t)cpu(4));
/* 0010986c: sw zero,0xec(a0) */ sw(ea(4,(int32_t)UINT32_C(0x000000ec)),(uint32_t)cpu(0));
/* 00109870: sw a0,-0x57d4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa82c)),(uint32_t)cpu(4));
L_00109874:;
/* 00109874: lw v0,-0x57dc(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa824)));
/* 00109878: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0010987c: jr ra */ {uint64_t target=cpu(31);/* delay 00109880 */ sw(ea(28,(int32_t)UINT32_C(0xffffa824)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_00109cb8(void){
uint64_t incoming=cpu(31);
/* 00109cb8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00109cbc: lui t0,0x11 */ set(8,sx(UINT32_C(0x00110000)));
/* 00109cc0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109cc4: move s0,a1 */ set(16,cpu(5));
/* 00109cc8: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00109ccc: move a1,a0 */ set(5,cpu(4));
/* 00109cd0: lui t1,0x11 */ set(9,sx(UINT32_C(0x00110000)));
/* 00109cd4: move t2,s0 */ set(10,cpu(16));
/* 00109cd8: lw a0,0xc8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000c8)));
/* 00109cdc: addiu t0,t0,-0x5d98 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0xffffa268)));
/* 00109ce0: lw v0,0xb4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x000000b4)));
/* 00109ce4: addiu t1,t1,-0x5df0 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xffffa210)));
/* 00109ce8: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00109cec: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 00109cf0: addu a0,v0,a0 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00109cf4: jal 0x001015b0 */ set(31,UINT64_C(0x00109cfc));/* delay 00109cf8 */ set(7,sx(UINT32_C(0x00000001)));body_001015b0();
/* 00109cfc: sw v0,0xe4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000000e4)),(uint32_t)cpu(2));
/* 00109d00: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00109d04: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109d08: jr ra */ {uint64_t target=cpu(31);/* delay 00109d0c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001015b0(void){
uint64_t incoming=cpu(31);
/* 001015b0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 001015b4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001015b8: move s1,a0 */ set(17,cpu(4));
/* 001015bc: li a0,0x50 */ set(4,sx(UINT32_C(0x00000050)));
/* 001015c0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001015c4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001015c8: move s2,a1 */ set(18,cpu(5));
/* 001015cc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001015d0: move s3,a2 */ set(19,cpu(6));
/* 001015d4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001015d8: move s4,a3 */ set(20,cpu(7));
/* 001015dc: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001015e0: move s5,t0 */ set(21,cpu(8));
/* 001015e4: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001015e8: move s6,t1 */ set(22,cpu(9));
/* 001015ec: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001015f0: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001015f4: jal 0x002a8af8 */ set(31,UINT64_C(0x001015fc));/* delay 001015f8 */ set(23,cpu(10));nocturneFieldMovementCall(UINT32_C(0x002a8af8),UINT32_C(0x001015f4));
/* 001015fc: move s0,v0 */ set(16,cpu(2));
/* 00101600: beq s0,zero,0x001016c0 */ {int taken=(cpu(16)==cpu(0));/* delay 00101604 */ set(7,cpu(0));if(taken){goto L_001016c0;}}
/* 00101608: sw zero,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 0010160c: lbu v0,0x0(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
/* 00101610: sll v1,v0,0x18 */ set(3,sx((uint32_t)cpu(2)<<24));
/* 00101614: beq v1,zero,0x00101660 */ {int taken=(cpu(3)==cpu(0));/* delay 00101618 */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));if(taken){goto L_00101660;}}
/* 0010161c: move a2,s1 */ set(6,cpu(17));
/* 00101620: lb a0,0x0(a2) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000000))));
/* 00101624: nop  */ 
L_00101628:;
/* 00101628: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 0010162c: lw v1,0x18(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 00101630: addu v0,s1,a3 */ set(2,sx((uint32_t)cpu(17)+(uint32_t)cpu(7)));
/* 00101634: move a2,v0 */ set(6,cpu(2));
/* 00101638: addu a1,s0,a3 */ set(5,sx((uint32_t)cpu(16)+(uint32_t)cpu(7)));
/* 0010163c: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 00101640: slti a0,a3,0x18 */ set(4,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x00000018));
/* 00101644: sw v1,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 00101648: lbu v0,0x0(a2) */ set(2,byte(ea(6,(int32_t)UINT32_C(0x00000000))));
/* 0010164c: sll v1,v0,0x18 */ set(3,sx((uint32_t)cpu(2)<<24));
/* 00101650: beq v1,zero,0x00101660 */ {int taken=(cpu(3)==cpu(0));/* delay 00101654 */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));if(taken){goto L_00101660;}}
/* 00101658: bnel a0,zero,0x00101628 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 0010165c */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(6,(int32_t)UINT32_C(0x00000000))));goto L_00101628;}}
L_00101660:;
/* 00101660: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00101664: sw s2,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(18));
/* 00101668: sw v0,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));
/* 0010166c: move a0,s0 */ set(4,cpu(16));
/* 00101670: sh s3,0x2c(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(19));
/* 00101674: sh s4,0x2e(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(20));
/* 00101678: sw s5,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(21));
/* 0010167c: sw s6,0x34(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(22));
/* 00101680: sw s7,0x38(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(23));
/* 00101684: sb zero,0x17(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000017)),(uint8_t)cpu(0));
/* 00101688: sw zero,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 0010168c: sw zero,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 00101690: sw zero,0x3c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));
/* 00101694: sw zero,0x40(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));
/* 00101698: sw zero,0x44(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(0));
/* 0010169c: sw zero,0x48(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(0));
/* 001016a0: jal 0x00100760 */ set(31,UINT64_C(0x001016a8));/* delay 001016a4 */ sw(ea(16,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));body_00100760();
/* 001016a8: lh v0,0x2c(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002c))));
/* 001016ac: bne v0,zero,0x001016c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001016b0 */ set(2,cpu(16));if(taken){goto L_001016c0;}}
/* 001016b4: jal 0x001009a0 */ set(31,UINT64_C(0x001016bc));/* delay 001016b8 */ set(4,cpu(16));nocturneFieldMovementCall(UINT32_C(0x001009a0),UINT32_C(0x001016b4));
/* 001016bc: move v0,s0 */ set(2,cpu(16));
L_001016c0:;
/* 001016c0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001016c4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001016c8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001016cc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001016d0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001016d4: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001016d8: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001016dc: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001016e0: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001016e4: jr ra */ {uint64_t target=cpu(31);/* delay 001016e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_00100760(void){
uint64_t incoming=cpu(31);
/* 00100760: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 00100764: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00100768: andi v1,a2,0xf */ set(3,cpu(6)&UINT32_C(0x0000000f));
/* 0010076c: beq v1,v0,0x00100798 */ {int taken=(cpu(3)==cpu(2));/* delay 00100770 */ set(7,cpu(6));if(taken){goto L_00100798;}}
/* 00100774: beq v1,zero,0x0010078c */ {int taken=(cpu(3)==cpu(0));/* delay 00100778 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_0010078c;}}
/* 0010077c: beq v1,v0,0x001007a0 */ {int taken=(cpu(3)==cpu(2));/* delay 00100780 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_001007a0;}}
/* 00100784: beq v1,v0,0x001007a4 */ {int taken=(cpu(3)==cpu(2));/* delay 00100788 */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6ec)));if(taken){goto L_001007a4;}}
L_0010078c:;
/* 0010078c: jr ra */ {uint64_t target=cpu(31);/* delay 00100790 */ checkReturn(target,incoming);return;}
L_00100798:;
/* 00100798: b 0x001007a4 */ /* delay 0010079c */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6e0)));goto L_001007a4;
L_001007a0:;
/* 001007a0: lw a1,-0x5908(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6f8)));
L_001007a4:;
/* 001007a4: bnel a1,zero,0x00100830 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 001007a8 */ lw(3,ea(4,(int32_t)UINT32_C(0x00000020)));goto L_00100830;}}
/* 001007ac: andi v1,a3,0xf */ set(3,cpu(7)&UINT32_C(0x0000000f));
/* 001007b0: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 001007b4: beq v1,v0,0x001007f0 */ {int taken=(cpu(3)==cpu(2));/* delay 001007b8 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_001007f0;}}
/* 001007bc: beq v0,zero,0x001007d8 */ {int taken=(cpu(2)==cpu(0));/* delay 001007c0 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_001007d8;}}
/* 001007c4: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001007c8: beql v1,v0,0x001007e8 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 001007cc */ sw(ea(28,(int32_t)UINT32_C(0xffffa6e0)),(uint32_t)cpu(4));goto L_001007e8;}}
/* 001007d0: b 0x0010080c */ /* delay 001007d4 */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));goto L_0010080c;
L_001007d8:;
/* 001007d8: beql v1,v0,0x00100800 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 001007dc */ sw(ea(28,(int32_t)UINT32_C(0xffffa6ec)),(uint32_t)cpu(4));goto L_00100800;}}
/* 001007e0: b 0x0010080c */ /* delay 001007e4 */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));goto L_0010080c;
L_001007e8:;
/* 001007e8: b 0x00100804 */ /* delay 001007ec */ sw(ea(28,(int32_t)UINT32_C(0xffffa6e4)),(uint32_t)cpu(4));goto L_00100804;
L_001007f0:;
/* 001007f0: sw a0,-0x5908(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa6f8)),(uint32_t)cpu(4));
/* 001007f4: b 0x00100804 */ /* delay 001007f8 */ sw(ea(28,(int32_t)UINT32_C(0xffffa6fc)),(uint32_t)cpu(4));goto L_00100804;
L_00100800:;
/* 00100800: sw a0,-0x5910(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa6f0)),(uint32_t)cpu(4));
L_00100804:;
/* 00100804: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 00100808: sw zero,0x3c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));
L_0010080c:;
/* 0010080c: b 0x00100934 */ /* delay 00100810 */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));goto L_00100934;
L_00100818:;
/* 00100818: lw v0,0x40(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000040)));
/* 0010081c: sw a1,0x3c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(5));
/* 00100820: sw v0,0x40(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
/* 00100824: b 0x001008b0 */ /* delay 00100828 */ sw(ea(5,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(4));goto L_001008b0;
L_00100830:;
/* 00100830: li t0,0x2 */ set(8,sx(UINT32_C(0x00000002)));
/* 00100834: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 00100838: li t1,0x3 */ set(9,sx(UINT32_C(0x00000003)));
/* 0010083c: lw v0,0x20(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000020)));
L_00100840:;
/* 00100840: sltu v0,v1,v0 */ set(2,cpu(3)<cpu(2));
/* 00100844: beql v0,zero,0x001008a8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00100848 */ lw(5,ea(5,(int32_t)UINT32_C(0x0000003c)));goto L_001008a8;}}
/* 0010084c: lw v0,0x40(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000040)));
/* 00100850: bnel v0,zero,0x00100818 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00100854 */ sw(ea(2,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(4));goto L_00100818;}}
/* 00100858: andi v1,a3,0xf */ set(3,cpu(7)&UINT32_C(0x0000000f));
/* 0010085c: beq v1,t0,0x00100890 */ {int taken=(cpu(3)==cpu(8));/* delay 00100860 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_00100890;}}
/* 00100864: beq v0,zero,0x00100880 */ {int taken=(cpu(2)==cpu(0));/* delay 00100868 */ if(taken){goto L_00100880;}}
/* 0010086c: beql v1,t2,0x00100894 */ {int taken=(cpu(3)==cpu(10));if(taken){/* delay 00100870 */ sw(ea(28,(int32_t)UINT32_C(0xffffa6e0)),(uint32_t)cpu(4));goto L_00100894;}}
/* 00100874: b 0x0010089c */ /* delay 00100878 */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));goto L_0010089c;
L_00100880:;
/* 00100880: beql v1,t1,0x00100894 */ {int taken=(cpu(3)==cpu(9));if(taken){/* delay 00100884 */ sw(ea(28,(int32_t)UINT32_C(0xffffa6ec)),(uint32_t)cpu(4));goto L_00100894;}}
/* 00100888: b 0x0010089c */ /* delay 0010088c */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));goto L_0010089c;
L_00100890:;
/* 00100890: sw a0,-0x5908(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa6f8)),(uint32_t)cpu(4));
L_00100894:;
/* 00100894: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 00100898: sw zero,0x40(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));
L_0010089c:;
/* 0010089c: sw a1,0x3c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(5));
/* 001008a0: b 0x001008b0 */ /* delay 001008a4 */ sw(ea(5,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(4));goto L_001008b0;
L_001008a8:;
/* 001008a8: bnel a1,zero,0x00100840 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 001008ac */ lw(2,ea(5,(int32_t)UINT32_C(0x00000020)));goto L_00100840;}}
L_001008b0:;
/* 001008b0: bne a1,zero,0x00100938 */ {int taken=(cpu(5)!=cpu(0));/* delay 001008b4 */ set(3,cpu(6)&UINT32_C(0x0000000f));if(taken){goto L_00100938;}}
/* 001008b8: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 001008bc: beq v1,v0,0x00100908 */ {int taken=(cpu(3)==cpu(2));/* delay 001008c0 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_00100908;}}
/* 001008c4: beq v0,zero,0x001008e0 */ {int taken=(cpu(2)==cpu(0));/* delay 001008c8 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_001008e0;}}
/* 001008cc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001008d0: beq v1,v0,0x001008f0 */ {int taken=(cpu(3)==cpu(2));/* delay 001008d4 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6e4)));if(taken){goto L_001008f0;}}
/* 001008d8: b 0x00100938 */ /* delay 001008dc */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));goto L_00100938;
L_001008e0:;
/* 001008e0: beq v1,v0,0x00100920 */ {int taken=(cpu(3)==cpu(2));/* delay 001008e4 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6f0)));if(taken){goto L_00100920;}}
/* 001008e8: b 0x00100934 */ /* delay 001008ec */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));goto L_00100934;
L_001008f0:;
/* 001008f0: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001008f4: sw a0,0x3c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(4));
/* 001008f8: sw v0,0x40(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
/* 001008fc: b 0x00100930 */ /* delay 00100900 */ sw(ea(28,(int32_t)UINT32_C(0xffffa6e4)),(uint32_t)cpu(4));goto L_00100930;
L_00100908:;
/* 00100908: lw v0,-0x5904(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6fc)));
/* 0010090c: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 00100910: sw a0,0x3c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(4));
/* 00100914: sw v0,0x40(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
/* 00100918: b 0x00100930 */ /* delay 0010091c */ sw(ea(28,(int32_t)UINT32_C(0xffffa6fc)),(uint32_t)cpu(4));goto L_00100930;
L_00100920:;
/* 00100920: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 00100924: sw a0,0x3c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(4));
/* 00100928: sw v0,0x40(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));
/* 0010092c: sw a0,-0x5910(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa6f0)),(uint32_t)cpu(4));
L_00100930:;
/* 00100930: sw zero,0x3c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));
L_00100934:;
/* 00100934: andi v1,a2,0xf */ set(3,cpu(6)&UINT32_C(0x0000000f));
L_00100938:;
/* 00100938: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0010093c: beq v1,v0,0x00100980 */ {int taken=(cpu(3)==cpu(2));/* delay 00100940 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_00100980;}}
/* 00100944: beq v0,zero,0x00100960 */ {int taken=(cpu(2)==cpu(0));/* delay 00100948 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00100960;}}
/* 0010094c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00100950: beql v1,v0,0x00100970 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 00100954 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6e8)));goto L_00100970;}}
/* 00100958: jr ra */ {uint64_t target=cpu(31);/* delay 0010095c */ checkReturn(target,incoming);return;}
L_00100960:;
/* 00100960: beql v1,v0,0x00100990 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 00100964 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6f4)));goto L_00100990;}}
/* 00100968: jr ra */ {uint64_t target=cpu(31);/* delay 0010096c */ checkReturn(target,incoming);return;}
L_00100970:;
/* 00100970: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00100974: jr ra */ {uint64_t target=cpu(31);/* delay 00100978 */ sw(ea(28,(int32_t)UINT32_C(0xffffa6e8)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
L_00100980:;
/* 00100980: lw v0,-0x5900(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa700)));
/* 00100984: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00100988: jr ra */ {uint64_t target=cpu(31);/* delay 0010098c */ sw(ea(28,(int32_t)UINT32_C(0xffffa700)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
L_00100990:;
/* 00100990: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 00100994: sw v0,-0x590c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa6f4)),(uint32_t)cpu(2));
/* 00100998: jr ra */ {uint64_t target=cpu(31);/* delay 0010099c */ checkReturn(target,incoming);return;}
}
static void body_001097e8(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 001097e8: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001097ec: swc1 f19,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[19]);
/* 001097f0: sd a1,0x28(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001097f4: sd a2,0x30(sp) */ save(6,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001097f8: sd a3,0x38(sp) */ save(7,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001097fc: sd t0,0x40(sp) */ save(8,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00109800: sd t1,0x48(sp) */ save(9,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00109804: sd t2,0x50(sp) */ save(10,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00109808: sd t3,0x58(sp) */ save(11,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0010980c: swc1 f12,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),f[12]);
/* 00109810: swc1 f13,0xc(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),f[13]);
/* 00109814: swc1 f14,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),f[14]);
/* 00109818: swc1 f15,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),f[15]);
/* 0010981c: swc1 f16,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[16]);
/* 00109820: swc1 f17,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),f[17]);
/* 00109824: swc1 f18,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[18]);
/* 00109828: jr ra */ {uint64_t target=cpu(31);/* delay 0010982c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_00101898(void){
uint64_t incoming=cpu(31);
/* 00101898: move t0,a0 */ set(8,cpu(4));
/* 0010189c: move a3,zero */ set(7,cpu(0));
/* 001018a0: lb v0,0x0(t0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(8,(int32_t)UINT32_C(0x00000000))));
/* 001018a4: move t3,zero */ set(11,cpu(0));
/* 001018a8: beq v0,zero,0x001018cc */ {int taken=(cpu(2)==cpu(0));/* delay 001018ac */ set(10,cpu(0));if(taken){goto L_001018cc;}}
L_001018b0:;
/* 001018b0: addiu t2,t2,0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000001)));
/* 001018b4: lb v0,0x0(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 001018b8: addu v1,t0,t2 */ set(3,sx((uint32_t)cpu(8)+(uint32_t)cpu(10)));
/* 001018bc: move a0,v1 */ set(4,cpu(3));
/* 001018c0: lb v1,0x0(a0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 001018c4: bne v1,zero,0x001018b0 */ {int taken=(cpu(3)!=cpu(0));/* delay 001018c8 */ set(11,sx((uint32_t)cpu(11)+(uint32_t)cpu(2)));if(taken){goto L_001018b0;}}
L_001018cc:;
/* 001018cc: move t1,zero */ set(9,cpu(0));
/* 001018d0: li t5,0x1 */ set(13,sx(UINT32_C(0x00000001)));
/* 001018d4: li t4,0x2 */ set(12,sx(UINT32_C(0x00000002)));
L_001018d8:;
/* 001018d8: beq t1,t5,0x00101908 */ {int taken=(cpu(9)==cpu(13));/* delay 001018dc */ set(2,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_00101908;}}
/* 001018e0: beq v0,zero,0x001018f8 */ {int taken=(cpu(2)==cpu(0));/* delay 001018e4 */ if(taken){goto L_001018f8;}}
/* 001018e8: beql t1,zero,0x0010190c */ {int taken=(cpu(9)==cpu(0));if(taken){/* delay 001018ec */ lw(7,ea(28,(int32_t)UINT32_C(0xffffa6e0)));goto L_0010190c;}}
/* 001018f0: b 0x0010190c */ /* delay 001018f4 */ goto L_0010190c;
L_001018f8:;
/* 001018f8: beql t1,t4,0x0010190c */ {int taken=(cpu(9)==cpu(12));if(taken){/* delay 001018fc */ lw(7,ea(28,(int32_t)UINT32_C(0xffffa6ec)));goto L_0010190c;}}
/* 00101900: b 0x0010190c */ /* delay 00101904 */ goto L_0010190c;
L_00101908:;
/* 00101908: lw a3,-0x5908(gp) */ lw(7,ea(28,(int32_t)UINT32_C(0xffffa6f8)));
L_0010190c:;
/* 0010190c: beql a3,zero,0x0010195c */ {int taken=(cpu(7)==cpu(0));if(taken){/* delay 00101910 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000001)));goto L_0010195c;}}
/* 00101914: lw v0,0x18(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000018)));
L_00101918:;
/* 00101918: bnel v0,t3,0x00101950 */ {int taken=(cpu(2)!=cpu(11));if(taken){/* delay 0010191c */ lw(7,ea(7,(int32_t)UINT32_C(0x0000003c)));goto L_00101950;}}
/* 00101920: b 0x00101934 */ /* delay 00101924 */ set(6,cpu(10));goto L_00101934;
L_00101928:;
/* 00101928: beq a2,zero,0x0010196c */ {int taken=(cpu(6)==cpu(0));/* delay 0010192c */ set(2,cpu(7));if(taken){goto L_0010196c;}}
/* 00101930: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
L_00101934:;
/* 00101934: addu v1,t0,a2 */ set(3,sx((uint32_t)cpu(8)+(uint32_t)cpu(6)));
/* 00101938: addu a0,a3,a2 */ set(4,sx((uint32_t)cpu(7)+(uint32_t)cpu(6)));
/* 0010193c: lb a1,0x0(v1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00101940: lb v0,0x0(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00101944: beq a1,v0,0x00101928 */ {int taken=(cpu(5)==cpu(2));/* delay 00101948 */ if(taken){goto L_00101928;}}
/* 0010194c: lw a3,0x3c(a3) */ lw(7,ea(7,(int32_t)UINT32_C(0x0000003c)));
L_00101950:;
/* 00101950: bnel a3,zero,0x00101918 */ {int taken=(cpu(7)!=cpu(0));if(taken){/* delay 00101954 */ lw(2,ea(7,(int32_t)UINT32_C(0x00000018)));goto L_00101918;}}
/* 00101958: addiu t1,t1,0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000001)));
L_0010195c:;
/* 0010195c: slti v0,t1,0x3 */ set(2,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00101960: bne v0,zero,0x001018d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00101964 */ if(taken){goto L_001018d8;}}
/* 00101968: move v0,zero */ set(2,cpu(0));
L_0010196c:;
/* 0010196c: jr ra */ {uint64_t target=cpu(31);/* delay 00101970 */ checkReturn(target,incoming);return;}
}
static void body_002d5ab4(void){
uint64_t incoming=cpu(31);
/* 002d5ab4: or t0,a0,a1 */ set(8,cpu(4)|cpu(5));
/* 002d5ab8: andi v0,t0,0x7 */ set(2,cpu(8)&UINT32_C(0x00000007));
/* 002d5abc: bnel v0,zero,0x002d5be4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d5ac0 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5be4;}}
/* 002d5ac4: andi t1,t0,0xf */ set(9,cpu(8)&UINT32_C(0x0000000f));
/* 002d5ac8: lui a3,0x101 */ set(7,sx(UINT32_C(0x01010000)));
/* 002d5acc: ori a3,a3,0x101 */ set(7,cpu(7)|UINT32_C(0x00000101));
/* 002d5ad0: dsll a3,a3,0x10 */ set(7,cpu(7)<<16);
/* 002d5ad4: ori a3,a3,0x101 */ set(7,cpu(7)|UINT32_C(0x00000101));
/* 002d5ad8: dsll a3,a3,0x10 */ set(7,cpu(7)<<16);
/* 002d5adc: ori a3,a3,0x101 */ set(7,cpu(7)|UINT32_C(0x00000101));
/* 002d5ae0: lui a2,0x8080 */ set(6,sx(UINT32_C(0x80800000)));
/* 002d5ae4: ori a2,a2,0x8080 */ set(6,cpu(6)|UINT32_C(0x00008080));
/* 002d5ae8: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d5aec: ori a2,a2,0x8080 */ set(6,cpu(6)|UINT32_C(0x00008080));
/* 002d5af0: dsll a2,a2,0x10 */ set(6,cpu(6)<<16);
/* 002d5af4: ori a2,a2,0x8080 */ set(6,cpu(6)|UINT32_C(0x00008080));
/* 002d5af8: bne t1,zero,0x002d5b78 */ {int taken=(cpu(9)!=cpu(0));/* delay 002d5afc */ restore(2,ea(5,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002d5b78;}}
/* 002d5b00: lq v1,0x0(a0) */ requestLq(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5b04: pcpyld t0,a3,a3 */ requestPacked(0,8,7,7);
/* 002d5b08: lq v0,0x0(a1) */ requestLq(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5b0c: pcpyld t2,a2,a2 */ requestPacked(0,10,6,6);
/* 002d5b10: psubw a3,v0,v1 */ carrierPsubw(7u,2u,3u);
/* 002d5b14: pcpyud a2,a3,a0 */ requestPacked(1,6,7,4);
/* 002d5b18: or v1,a2,a3 */ set(3,cpu(6)|cpu(7));
/* 002d5b1c: bnel v1,zero,0x002d5be4 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d5b20 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5be4;}}
/* 002d5b24: lq v0,0x0(a0) */ requestLq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5b28: pnor v1,zero,v0 */ requestPacked(3,3,0,2);
L_002d5b2c:;
/* 002d5b2c: psubb v0,v0,t0 */ requestPacked(4,2,2,8);
/* 002d5b30: pand v0,v0,v1 */ requestPacked(2,2,2,3);
/* 002d5b34: pand v0,v0,t2 */ requestPacked(2,2,2,10);
/* 002d5b38: pcpyud v1,v0,a0 */ requestPacked(1,3,2,4);
/* 002d5b3c: or a2,v1,v0 */ set(6,cpu(3)|cpu(2));
/* 002d5b40: beq a2,zero,0x002d5b50 */ {int taken=(cpu(6)==cpu(0));/* delay 002d5b44 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));if(taken){goto L_002d5b50;}}
/* 002d5b48: jr ra */ {uint64_t target=cpu(31);/* delay 002d5b4c */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_002d5b50:;
/* 002d5b50: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d5b54: lq v0,0x0(a0) */ requestLq(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5b58: lq v1,0x0(a1) */ requestLq(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5b5c: psubw a3,v0,v1 */ carrierPsubw(7u,2u,3u);
/* 002d5b60: pcpyud a2,a3,a0 */ requestPacked(1,6,7,4);
/* 002d5b64: or t1,a2,a3 */ set(9,cpu(6)|cpu(7));
/* 002d5b68: beql t1,zero,0x002d5b2c */ {int taken=(cpu(9)==cpu(0));if(taken){/* delay 002d5b6c */ requestPacked(3,3,0,2);goto L_002d5b2c;}}
/* 002d5b70: b 0x002d5be4 */ /* delay 002d5b74 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5be4;
L_002d5b78:;
/* 002d5b78: ld v1,0x0(a0) */ restore(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5b7c: bnel v1,v0,0x002d5be4 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 002d5b80 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5be4;}}
/* 002d5b84: ld v0,0x0(a0) */ restore(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5b88: nor t0,zero,v0 */ set(8,~(cpu(0)|cpu(2)));
L_002d5b8c:;
/* 002d5b8c: dsubu v0,v0,a3 */ set(2,cpu(2)-cpu(7));
/* 002d5b90: and v0,v0,t0 */ set(2,cpu(2)&cpu(8));
/* 002d5b94: and v0,v0,a2 */ set(2,cpu(2)&cpu(6));
/* 002d5b98: beq v0,zero,0x002d5ba8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d5b9c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));if(taken){goto L_002d5ba8;}}
/* 002d5ba0: jr ra */ {uint64_t target=cpu(31);/* delay 002d5ba4 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_002d5ba8:;
/* 002d5ba8: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 002d5bac: ld v0,0x0(a0) */ restore(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d5bb0: ld v1,0x0(a1) */ restore(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5bb4: beql v1,v0,0x002d5b8c */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 002d5bb8 */ set(8,~(cpu(0)|cpu(2)));goto L_002d5b8c;}}
/* 002d5bbc: b 0x002d5be4 */ /* delay 002d5bc0 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5be4;
L_002d5bc4:;
/* 002d5bc4: sll v0,v1,0x18 */ set(2,sx((uint32_t)cpu(3)<<24));
/* 002d5bc8: lb v1,0x0(a1) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d5bcc: sra v0,v0,0x18 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 002d5bd0: bnel v0,v1,0x002d5bec */ {int taken=(cpu(2)!=cpu(3));if(taken){/* delay 002d5bd4 */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_002d5bec;}}
/* 002d5bd8: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002d5bdc: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002d5be0: lb v0,0x0(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));
L_002d5be4:;
/* 002d5be4: bne v0,zero,0x002d5bc4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5be8 */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_002d5bc4;}}
L_002d5bec:;
/* 002d5bec: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d5bf0: jr ra */ {uint64_t target=cpu(31);/* delay 002d5bf4 */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));checkReturn(target,incoming);return;}
}
static void body_00101738(void){
uint64_t incoming=cpu(31);
/* 00101738: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0010173c: move a3,a0 */ set(7,cpu(4));
/* 00101740: beq a3,zero,0x001017b8 */ {int taken=(cpu(7)==cpu(0));/* delay 00101744 */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_001017b8;}}
/* 00101748: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 0010174c: beq a3,v0,0x001017c4 */ {int taken=(cpu(7)==cpu(2));/* delay 00101750 */ set(2,cpu(0));if(taken){goto L_001017c4;}}
/* 00101754: lw v0,0x1c(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x0000001c)));
/* 00101758: andi a2,v0,0xf */ set(6,cpu(2)&UINT32_C(0x0000000f));
/* 0010175c: sltiu v1,a2,0x3 */ set(3,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00101760: beq v1,zero,0x00101778 */ {int taken=(cpu(3)==cpu(0));/* delay 00101764 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00101778;}}
/* 00101768: bne a2,zero,0x00101788 */ {int taken=(cpu(6)!=cpu(0));/* delay 0010176c */ if(taken){goto L_00101788;}}
/* 00101770: b 0x001017c4 */ /* delay 00101774 */ set(2,cpu(0));goto L_001017c4;
L_00101778:;
/* 00101778: beq a2,v0,0x00101798 */ {int taken=(cpu(6)==cpu(2));/* delay 0010177c */ set(2,cpu(0));if(taken){goto L_00101798;}}
/* 00101780: b 0x001017c8 */ /* delay 00101784 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001017c8;
L_00101788:;
/* 00101788: jal 0x00100e08 */ set(31,UINT64_C(0x00101790));/* delay 0010178c */ sh(ea(7,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(5));body_00100e08();
/* 00101790: b 0x001017c4 */ /* delay 00101794 */ set(2,sx(UINT32_C(0x00000001)));goto L_001017c4;
L_00101798:;
/* 00101798: sll v0,a1,0x10 */ set(2,sx((uint32_t)cpu(5)<<16));
/* 0010179c: bne v0,zero,0x001017c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001017a0 */ sh(ea(7,(int32_t)UINT32_C(0x0000002e)),(uint16_t)cpu(5));if(taken){goto L_001017c0;}}
/* 001017a4: jal 0x00100d70 */ set(31,UINT64_C(0x001017ac));/* delay 001017a8 */ body_00100d70();
/* 001017ac: b 0x001017c4 */ /* delay 001017b0 */ set(2,sx(UINT32_C(0x00000001)));goto L_001017c4;
L_001017b8:;
/* 001017b8: b 0x001017c4 */ /* delay 001017bc */ set(2,cpu(0));goto L_001017c4;
L_001017c0:;
/* 001017c0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_001017c4:;
/* 001017c4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001017c8:;
/* 001017c8: jr ra */ {uint64_t target=cpu(31);/* delay 001017cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00100e08(void){
uint64_t incoming=cpu(31);
/* 00100e08: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00100e0c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100e10: move s0,a0 */ set(16,cpu(4));
/* 00100e14: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100e18: lw v0,0x1c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 00100e1c: andi v0,v0,0xf */ set(2,cpu(2)&UINT32_C(0x0000000f));
/* 00100e20: sltiu v1,v0,0x3 */ set(3,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00100e24: beql v1,zero,0x00100e70 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00100e28 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00100e70;}}
/* 00100e2c: beql v0,zero,0x00100e70 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00100e30 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00100e70;}}
/* 00100e34: jal 0x001005e8 */ set(31,UINT64_C(0x00100e3c));/* delay 00100e38 */ body_001005e8();
/* 00100e3c: li v0,-0x10 */ set(2,sx(UINT32_C(0xfffffff0)));
/* 00100e40: lw v1,0x1c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 00100e44: move a0,s0 */ set(4,cpu(16));
/* 00100e48: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 00100e4c: ori v1,v1,0x3 */ set(3,cpu(3)|UINT32_C(0x00000003));
/* 00100e50: jal 0x00100760 */ set(31,UINT64_C(0x00100e58));/* delay 00100e54 */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(3));body_00100760();
/* 00100e58: lh v0,0x2e(s0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000002e))));
/* 00100e5c: bne v0,zero,0x00100e6c */ {int taken=(cpu(2)!=cpu(0));/* delay 00100e60 */ set(4,cpu(16));if(taken){goto L_00100e6c;}}
/* 00100e64: jal 0x00100d70 */ set(31,UINT64_C(0x00100e6c));/* delay 00100e68 */ body_00100d70();
L_00100e6c:;
/* 00100e6c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00100e70:;
/* 00100e70: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100e74: jr ra */ {uint64_t target=cpu(31);/* delay 00100e78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00100d70(void){
uint64_t incoming=cpu(31);
/* 00100d70: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00100d74: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100d78: move s1,a0 */ set(17,cpu(4));
/* 00100d7c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100d80: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00100d84: lw a0,0x48(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000048)));
/* 00100d88: beq a0,zero,0x00100dac */ {int taken=(cpu(4)==cpu(0));/* delay 00100d8c */ if(taken){goto L_00100dac;}}
/* 00100d90: lw s0,0x4c(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x0000004c)));
/* 00100d94: nop  */ 
L_00100d98:;
/* 00100d98: jal 0x00101738 */ set(31,UINT64_C(0x00100da0));/* delay 00100d9c */ set(5,cpu(0));body_00101738();
/* 00100da0: move a0,s0 */ set(4,cpu(16));
/* 00100da4: bnel a0,zero,0x00100d98 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 00100da8 */ lw(16,ea(4,(int32_t)UINT32_C(0x0000004c)));goto L_00100d98;}}
L_00100dac:;
/* 00100dac: jal 0x001005e8 */ set(31,UINT64_C(0x00100db4));/* delay 00100db0 */ set(4,cpu(17));body_001005e8();
/* 00100db4: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00100db8: addiu a0,a0,-0x22e8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffdd18)));
/* 00100dbc: jal 0x002d4748 */ set(31,UINT64_C(0x00100dc4));/* delay 00100dc0 */ set(5,cpu(17));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x00100dbc));
/* 00100dc4: lw v0,0x34(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000034)));
/* 00100dc8: beql v0,zero,0x00100ddc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00100dcc */ lw(2,ea(17,(int32_t)UINT32_C(0x0000001c)));goto L_00100ddc;}}
/* 00100dd0: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00100dd8));/* delay 00100dd4 */ set(4,cpu(17));nocturneFieldMovementIndirect(target,UINT32_C(0x00100dd0));}
/* 00100dd8: lw v0,0x1c(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000001c)));
L_00100ddc:;
/* 00100ddc: li v1,-0x10 */ set(3,sx(UINT32_C(0xfffffff0)));
/* 00100de0: move a0,s1 */ set(4,cpu(17));
/* 00100de4: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 00100de8: jal 0x00101b80 */ set(31,UINT64_C(0x00100df0));/* delay 00100dec */ sw(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));body_00101b80();
/* 00100df0: move a0,s1 */ set(4,cpu(17));
/* 00100df4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00100df8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00100dfc: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00100e00: j 0x002a8bd8 */ /* delay 00100e04 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002a8bd8();return;
}
static void body_001005e8(void){
uint64_t incoming=cpu(31);
/* 001005e8: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001005ec: andi v1,a2,0xf */ set(3,cpu(6)&UINT32_C(0x0000000f));
/* 001005f0: beq v1,zero,0x00100718 */ {int taken=(cpu(3)==cpu(0));/* delay 001005f4 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_00100718;}}
/* 001005f8: beq v0,zero,0x00100758 */ {int taken=(cpu(2)==cpu(0));/* delay 001005fc */ if(taken){goto L_00100758;}}
/* 00100600: lw a1,0x40(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 00100604: beq a1,zero,0x00100618 */ {int taken=(cpu(5)==cpu(0));/* delay 00100608 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_00100618;}}
/* 0010060c: lw v0,0x3c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000003c)));
/* 00100610: b 0x0010066c */ /* delay 00100614 */ sw(ea(5,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(2));goto L_0010066c;
L_00100618:;
/* 00100618: beq v1,v0,0x00100658 */ {int taken=(cpu(3)==cpu(2));/* delay 0010061c */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_00100658;}}
/* 00100620: beq v0,zero,0x00100640 */ {int taken=(cpu(2)==cpu(0));/* delay 00100624 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00100640;}}
/* 00100628: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0010062c: beql v1,v0,0x00100650 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 00100630 */ lw(2,ea(4,(int32_t)UINT32_C(0x0000003c)));goto L_00100650;}}
/* 00100634: b 0x00100670 */ /* delay 00100638 */ lw(3,ea(4,(int32_t)UINT32_C(0x0000003c)));goto L_00100670;
L_00100640:;
/* 00100640: beql v1,v0,0x00100668 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 00100644 */ lw(2,ea(4,(int32_t)UINT32_C(0x0000003c)));goto L_00100668;}}
/* 00100648: b 0x00100670 */ /* delay 0010064c */ lw(3,ea(4,(int32_t)UINT32_C(0x0000003c)));goto L_00100670;
L_00100650:;
/* 00100650: b 0x0010066c */ /* delay 00100654 */ sw(ea(28,(int32_t)UINT32_C(0xffffa6e0)),(uint32_t)cpu(2));goto L_0010066c;
L_00100658:;
/* 00100658: lw v0,0x3c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000003c)));
/* 0010065c: b 0x0010066c */ /* delay 00100660 */ sw(ea(28,(int32_t)UINT32_C(0xffffa6f8)),(uint32_t)cpu(2));goto L_0010066c;
L_00100668:;
/* 00100668: sw v0,-0x5914(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa6ec)),(uint32_t)cpu(2));
L_0010066c:;
/* 0010066c: lw v1,0x3c(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x0000003c)));
L_00100670:;
/* 00100670: beql v1,zero,0x00100688 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00100674 */ set(3,cpu(6)&UINT32_C(0x0000000f));goto L_00100688;}}
/* 00100678: lw v0,0x40(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 0010067c: b 0x001006ec */ /* delay 00100680 */ sw(ea(3,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(2));goto L_001006ec;
L_00100688:;
/* 00100688: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0010068c: beq v1,v0,0x001006d0 */ {int taken=(cpu(3)==cpu(2));/* delay 00100690 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));if(taken){goto L_001006d0;}}
/* 00100694: beq v0,zero,0x001006b0 */ {int taken=(cpu(2)==cpu(0));/* delay 00100698 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_001006b0;}}
/* 0010069c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001006a0: beq v1,v0,0x001006c0 */ {int taken=(cpu(3)==cpu(2));/* delay 001006a4 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_001006c0;}}
/* 001006a8: b 0x001006f8 */ /* delay 001006ac */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));goto L_001006f8;
L_001006b0:;
/* 001006b0: beq v1,v0,0x001006e0 */ {int taken=(cpu(3)==cpu(2));/* delay 001006b4 */ set(3,cpu(6)&UINT32_C(0x0000000f));if(taken){goto L_001006e0;}}
/* 001006b8: b 0x001006f4 */ /* delay 001006bc */ set(2,sx(UINT32_C(0x00000002)));goto L_001006f4;
L_001006c0:;
/* 001006c0: lw v0,0x40(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 001006c4: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001006c8: b 0x001006ec */ /* delay 001006cc */ sw(ea(28,(int32_t)UINT32_C(0xffffa6e4)),(uint32_t)cpu(2));goto L_001006ec;
L_001006d0:;
/* 001006d0: lw v0,0x40(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 001006d4: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001006d8: b 0x001006ec */ /* delay 001006dc */ sw(ea(28,(int32_t)UINT32_C(0xffffa6fc)),(uint32_t)cpu(2));goto L_001006ec;
L_001006e0:;
/* 001006e0: lw v0,0x40(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 001006e4: lw a2,0x1c(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x0000001c)));
/* 001006e8: sw v0,-0x5910(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa6f0)),(uint32_t)cpu(2));
L_001006ec:;
/* 001006ec: andi v1,a2,0xf */ set(3,cpu(6)&UINT32_C(0x0000000f));
/* 001006f0: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
L_001006f4:;
/* 001006f4: sw zero,0x40(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));
L_001006f8:;
/* 001006f8: beq v1,v0,0x00100740 */ {int taken=(cpu(3)==cpu(2));/* delay 001006fc */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(0));if(taken){goto L_00100740;}}
/* 00100700: sltiu v0,v1,0x3 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00100704: beq v0,zero,0x00100720 */ {int taken=(cpu(2)==cpu(0));/* delay 00100708 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_00100720;}}
/* 0010070c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00100710: beql v1,v0,0x00100730 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 00100714 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6e8)));goto L_00100730;}}
L_00100718:;
/* 00100718: jr ra */ {uint64_t target=cpu(31);/* delay 0010071c */ checkReturn(target,incoming);return;}
L_00100720:;
/* 00100720: beql v1,v0,0x00100750 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 00100724 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa6f4)));goto L_00100750;}}
/* 00100728: jr ra */ {uint64_t target=cpu(31);/* delay 0010072c */ checkReturn(target,incoming);return;}
L_00100730:;
/* 00100730: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00100734: jr ra */ {uint64_t target=cpu(31);/* delay 00100738 */ sw(ea(28,(int32_t)UINT32_C(0xffffa6e8)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
L_00100740:;
/* 00100740: lw v0,-0x5900(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa700)));
/* 00100744: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00100748: jr ra */ {uint64_t target=cpu(31);/* delay 0010074c */ sw(ea(28,(int32_t)UINT32_C(0xffffa700)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
L_00100750:;
/* 00100750: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00100754: sw v0,-0x590c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffa6f4)),(uint32_t)cpu(2));
L_00100758:;
/* 00100758: jr ra */ {uint64_t target=cpu(31);/* delay 0010075c */ checkReturn(target,incoming);return;}
}
static void body_00101b80(void){
uint64_t incoming=cpu(31);
/* 00101b80: lw v1,0x44(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000044)));
/* 00101b84: beq v1,zero,0x00101be4 */ {int taken=(cpu(3)==cpu(0));/* delay 00101b88 */ if(taken){goto L_00101be4;}}
/* 00101b8c: lw v0,0x48(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000048)));
/* 00101b90: bne v0,a0,0x00101ba8 */ {int taken=(cpu(2)!=cpu(4));/* delay 00101b94 */ set(5,cpu(2));if(taken){goto L_00101ba8;}}
/* 00101b98: lw v0,0x4c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000004c)));
/* 00101b9c: b 0x00101bdc */ /* delay 00101ba0 */ sw(ea(3,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(2));goto L_00101bdc;
L_00101ba8:;
/* 00101ba8: lw v1,0x4c(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x0000004c)));
/* 00101bac: beql v1,a0,0x00101bd8 */ {int taken=(cpu(3)==cpu(4));if(taken){/* delay 00101bb0 */ lw(2,ea(4,(int32_t)UINT32_C(0x0000004c)));goto L_00101bd8;}}
/* 00101bb4: nop  */ 
L_00101bb8:;
/* 00101bb8: move a1,v1 */ set(5,cpu(3));
/* 00101bbc: lw v0,0x4c(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x0000004c)));
/* 00101bc0: nop  */ 
/* 00101bc4: nop  */ 
/* 00101bc8: nop  */ 
/* 00101bcc: bne v0,a0,0x00101bb8 */ {int taken=(cpu(2)!=cpu(4));/* delay 00101bd0 */ set(3,cpu(2));if(taken){goto L_00101bb8;}}
/* 00101bd4: lw v0,0x4c(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000004c)));
L_00101bd8:;
/* 00101bd8: sw v0,0x4c(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(2));
L_00101bdc:;
/* 00101bdc: sw zero,0x4c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(0));
/* 00101be0: sw zero,0x44(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(0));
L_00101be4:;
/* 00101be4: jr ra */ {uint64_t target=cpu(31);/* delay 00101be8 */ checkReturn(target,incoming);return;}
}
static void body_0010a210(void){
uint64_t incoming=cpu(31);
/* 0010a210: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0010a214: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010a218: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010a21c: jal 0x00101ab0 */ set(31,UINT64_C(0x0010a224));/* delay 0010a220 */ set(16,cpu(4));body_00101ab0();
/* 0010a224: beq v0,zero,0x0010a234 */ {int taken=(cpu(2)==cpu(0));/* delay 0010a228 */ set(4,cpu(2));if(taken){goto L_0010a234;}}
/* 0010a22c: jal 0x00109e50 */ set(31,UINT64_C(0x0010a234));/* delay 0010a230 */ body_00109e50();
L_0010a234:;
/* 0010a234: move a0,s0 */ set(4,cpu(16));
/* 0010a238: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0010a23c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0010a240: move a1,zero */ set(5,cpu(0));
/* 0010a244: j 0x00101aa8 */ /* delay 0010a248 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00101aa8();return;
}
static void body_00101ab0(void){
uint64_t incoming=cpu(31);
/* 00101ab0: jr ra */ {uint64_t target=cpu(31);/* delay 00101ab4 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000038)));checkReturn(target,incoming);return;}
}
static void body_00101aa8(void){
uint64_t incoming=cpu(31);
/* 00101aa8: jr ra */ {uint64_t target=cpu(31);/* delay 00101aac */ sw(ea(4,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_00109e50(void){
uint64_t incoming=cpu(31);
/* 00109e50: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00109e54: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109e58: move s0,a0 */ set(16,cpu(4));
/* 00109e5c: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00109e60: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00109e64: addiu a0,a0,-0x1d48 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffe2b8)));
/* 00109e68: lw a1,0xc8(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000c8)));
/* 00109e6c: lw v0,0xb4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x000000b4)));
/* 00109e70: sll a1,a1,0x5 */ set(5,sx((uint32_t)cpu(5)<<5));
/* 00109e74: jal 0x002d4748 */ set(31,UINT64_C(0x00109e7c));/* delay 00109e78 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));nocturneFieldMovementCall(UINT32_C(0x002d4748),UINT32_C(0x00109e74));
/* 00109e7c: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 00109e80: lw a1,0xc8(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x000000c8)));
/* 00109e84: addiu a0,a0,-0x1d30 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffe2d0)));
/* 00109e88: lw v0,0xb4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x000000b4)));
/* 00109e8c: sll a1,a1,0x5 */ set(5,sx((uint32_t)cpu(5)<<5));
/* 00109e90: jal 0x001097e8 */ set(31,UINT64_C(0x00109e98));/* delay 00109e94 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));body_001097e8();
/* 00109e98: lw v0,0xdc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x000000dc)));
/* 00109e9c: beq v0,zero,0x00109eac */ {int taken=(cpu(2)==cpu(0));/* delay 00109ea0 */ set(4,cpu(2));if(taken){goto L_00109eac;}}
/* 00109ea4: jal 0x002a8bd8 */ set(31,UINT64_C(0x00109eac));/* delay 00109ea8 */ body_002a8bd8();
L_00109eac:;
/* 00109eac: lw a0,0xe0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000e0)));
/* 00109eb0: beql a0,zero,0x00109ec4 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00109eb4 */ lw(4,ea(16,(int32_t)UINT32_C(0x000000cc)));goto L_00109ec4;}}
/* 00109eb8: jal 0x002a8bd8 */ set(31,UINT64_C(0x00109ec0));/* delay 00109ebc */ body_002a8bd8();
/* 00109ec0: lw a0,0xcc(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000cc)));
L_00109ec4:;
/* 00109ec4: bltzl a0,0x00109ed8 */ {int taken=((int64_t)cpu(4)<0);if(taken){/* delay 00109ec8 */ lw(4,ea(16,(int32_t)UINT32_C(0x000000d8)));goto L_00109ed8;}}
/* 00109ecc: jal 0x001cdb38 */ set(31,UINT64_C(0x00109ed4));/* delay 00109ed0 */ nocturneFieldMovementCall(UINT32_C(0x001cdb38),UINT32_C(0x00109ecc));
/* 00109ed4: lw a0,0xd8(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x000000d8)));
L_00109ed8:;
/* 00109ed8: beq a0,zero,0x00109ee8 */ {int taken=(cpu(4)==cpu(0));/* delay 00109edc */ if(taken){goto L_00109ee8;}}
/* 00109ee0: jal 0x002a9558 */ set(31,UINT64_C(0x00109ee8));/* delay 00109ee4 */ nocturneFieldMovementCall(UINT32_C(0x002a9558),UINT32_C(0x00109ee0));
L_00109ee8:;
/* 00109ee8: jal 0x00109888 */ set(31,UINT64_C(0x00109ef0));/* delay 00109eec */ set(4,cpu(16));body_00109888();
/* 00109ef0: move a0,s0 */ set(4,cpu(16));
/* 00109ef4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00109ef8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00109efc: j 0x002a8bd8 */ /* delay 00109f00 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002a8bd8();return;
}
static void body_00109888(void){
uint64_t incoming=cpu(31);
/* 00109888: lw v0,-0x57d8(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa828)));
/* 0010988c: bnel v0,a0,0x001098a0 */ {int taken=(cpu(2)!=cpu(4));if(taken){/* delay 00109890 */ lw(3,ea(4,(int32_t)UINT32_C(0x000000e8)));goto L_001098a0;}}
/* 00109894: lw v0,0xec(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x000000ec)));
/* 00109898: b 0x001098a8 */ /* delay 0010989c */ sw(ea(28,(int32_t)UINT32_C(0xffffa828)),(uint32_t)cpu(2));goto L_001098a8;
L_001098a0:;
/* 001098a0: lw v0,0xec(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x000000ec)));
/* 001098a4: sw v0,0xec(v1) */ sw(ea(3,(int32_t)UINT32_C(0x000000ec)),(uint32_t)cpu(2));
L_001098a8:;
/* 001098a8: lw v0,-0x57d4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa82c)));
/* 001098ac: bnel v0,a0,0x001098c0 */ {int taken=(cpu(2)!=cpu(4));if(taken){/* delay 001098b0 */ lw(3,ea(4,(int32_t)UINT32_C(0x000000ec)));goto L_001098c0;}}
/* 001098b4: lw v0,0xe8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x000000e8)));
/* 001098b8: b 0x001098c8 */ /* delay 001098bc */ sw(ea(28,(int32_t)UINT32_C(0xffffa82c)),(uint32_t)cpu(2));goto L_001098c8;
L_001098c0:;
/* 001098c0: lw v0,0xe8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x000000e8)));
/* 001098c4: sw v0,0xe8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x000000e8)),(uint32_t)cpu(2));
L_001098c8:;
/* 001098c8: lw v0,-0x57dc(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa824)));
/* 001098cc: sw zero,0xec(a0) */ sw(ea(4,(int32_t)UINT32_C(0x000000ec)),(uint32_t)cpu(0));
/* 001098d0: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 001098d4: sw zero,0xe8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x000000e8)),(uint32_t)cpu(0));
/* 001098d8: jr ra */ {uint64_t target=cpu(31);/* delay 001098dc */ sw(ea(28,(int32_t)UINT32_C(0xffffa824)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_002a8bd8(void){
uint64_t incoming=cpu(31);
/* 002a8bd8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002a8bdc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a8be0: move s2,a0 */ set(18,cpu(4));
/* 002a8be4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8be8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8bec: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8bf0: beq s2,zero,0x002a8cdc */ {int taken=(cpu(18)==cpu(0));/* delay 002a8bf4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002a8cdc;}}
/* 002a8bf8: lw v0,-0x2110(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdef0)));
/* 002a8bfc: lw a1,-0x2118(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffdee8)));
/* 002a8c00: subu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)-(uint32_t)cpu(2)));
/* 002a8c04: addiu a0,v0,0xfff */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00000fff)));
/* 002a8c08: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 002a8c0c: movn v0,a0,v1 */ if(cpu(3)!=0){set(2,cpu(4));}
/* 002a8c10: sra v0,v0,0xc */ set(2,sx((uint32_t)((int32_t)cpu(2)>>12)));
/* 002a8c14: sll v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)<<1));
/* 002a8c18: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002a8c1c: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 002a8c20: addu s0,a1,v1 */ set(16,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 002a8c24: jal 0x002e4070 */ set(31,UINT64_C(0x002a8c2c));/* delay 002a8c28 */ lw(17,ea(16,(int32_t)UINT32_C(0x0000000c)));nocturneFieldMovementCall(UINT32_C(0x002e4070),UINT32_C(0x002a8c24));
/* 002a8c2c: lh a0,0x14(s0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 002a8c30: move s3,v0 */ set(19,cpu(2));
/* 002a8c34: addiu v0,a0,-0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 002a8c38: sll v1,v0,0x10 */ set(3,sx((uint32_t)cpu(2)<<16));
/* 002a8c3c: bne v1,zero,0x002a8ca8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002a8c40 */ sh(ea(16,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(2));if(taken){goto L_002a8ca8;}}
/* 002a8c44: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002a8c48: bne v0,s0,0x002a8c60 */ {int taken=(cpu(2)!=cpu(16));/* delay 002a8c4c */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));if(taken){goto L_002a8c60;}}
/* 002a8c50: jal 0x002a89c0 */ set(31,UINT64_C(0x002a8c58));/* delay 002a8c54 */ set(4,cpu(17));nocturneFieldMovementCall(UINT32_C(0x002a89c0),UINT32_C(0x002a8c50));
/* 002a8c58: b 0x002a8c98 */ /* delay 002a8c5c */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdeec)));goto L_002a8c98;
L_002a8c60:;
/* 002a8c60: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002a8c64: beql v1,s0,0x002a8c90 */ {int taken=(cpu(3)==cpu(16));if(taken){/* delay 002a8c68 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002a8c90;}}
/* 002a8c6c: nop  */ 
L_002a8c70:;
/* 002a8c70: move a0,v1 */ set(4,cpu(3));
/* 002a8c74: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002a8c78: nop  */ 
/* 002a8c7c: nop  */ 
/* 002a8c80: nop  */ 
/* 002a8c84: bne v0,s0,0x002a8c70 */ {int taken=(cpu(2)!=cpu(16));/* delay 002a8c88 */ set(3,cpu(2));if(taken){goto L_002a8c70;}}
/* 002a8c8c: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
L_002a8c90:;
/* 002a8c90: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a8c94: lw v0,-0x2114(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdeec)));
L_002a8c98:;
/* 002a8c98: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002a8c9c: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a8ca0: b 0x002a8ccc */ /* delay 002a8ca4 */ sw(ea(28,(int32_t)UINT32_C(0xffffdeec)),(uint32_t)cpu(16));goto L_002a8ccc;
L_002a8ca8:;
/* 002a8ca8: lh v0,0xa(s1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000a))));
/* 002a8cac: bnel a0,v0,0x002a8cc4 */ {int taken=(cpu(4)!=cpu(2));if(taken){/* delay 002a8cb0 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));goto L_002a8cc4;}}
/* 002a8cb4: lw v0,0x4(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002a8cb8: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a8cbc: sw s0,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));
/* 002a8cc0: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
L_002a8cc4:;
/* 002a8cc4: sw v0,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002a8cc8: sw s2,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
L_002a8ccc:;
/* 002a8ccc: beq s3,zero,0x002a8ce0 */ {int taken=(cpu(19)==cpu(0));/* delay 002a8cd0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002a8ce0;}}
/* 002a8cd4: jal 0x002e40b8 */ set(31,UINT64_C(0x002a8cdc));/* delay 002a8cd8 */ nocturneFieldMovementCall(UINT32_C(0x002e40b8),UINT32_C(0x002a8cd4));
L_002a8cdc:;
/* 002a8cdc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002a8ce0:;
/* 002a8ce0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8ce4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a8ce8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8cec: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a8cf0: jr ra */ {uint64_t target=cpu(31);/* delay 002a8cf4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
uint32_t nocturneFieldMovementCarrierBody(uint32_t entry){switch(entry){
case UINT32_C(0x0010f4d8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010f4d8();return 1u;case UINT32_C(0x0010a0d0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010a0d0();return 1u;case UINT32_C(0x00109d98):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00109d98();return 1u;case UINT32_C(0x00109b48):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00109b48();return 1u;case UINT32_C(0x001098e0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001098e0();return 1u;case UINT32_C(0x00109848):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00109848();return 1u;case UINT32_C(0x00109cb8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00109cb8();return 1u;case UINT32_C(0x001015b0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001015b0();return 1u;case UINT32_C(0x00100760):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00100760();return 1u;case UINT32_C(0x001097e8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001097e8();return 1u;case UINT32_C(0x00101898):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00101898();return 1u;case UINT32_C(0x002d5ab4):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002d5ab4();return 1u;case UINT32_C(0x00101738):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00101738();return 1u;case UINT32_C(0x00100e08):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00100e08();return 1u;case UINT32_C(0x00100d70):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00100d70();return 1u;case UINT32_C(0x001005e8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_001005e8();return 1u;case UINT32_C(0x00101b80):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00101b80();return 1u;case UINT32_C(0x0010a210):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_0010a210();return 1u;case UINT32_C(0x00101ab0):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00101ab0();return 1u;case UINT32_C(0x00101aa8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00101aa8();return 1u;case UINT32_C(0x00109e50):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00109e50();return 1u;case UINT32_C(0x00109888):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_00109888();return 1u;case UINT32_C(0x002a8bd8):if(nocturneFieldMovementStackPointer()!=(uint32_t)cpu(29))abort();body_002a8bd8();return 1u;
default:return 0u;}}
