/* Complete36 press-turn panel owner/dependency bodies; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_panel_owner.h"
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
static uint8_t *at(uint32_t a){return nocturneResolveBattlePanelOwnerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattlePanelOwnerCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneBattlePanelOwnerCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneBattlePanelOwnerCpuWrite(r,q);if(r==29u)nocturneBattlePanelOwnerSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}




void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sq(unsigned reg,uint32_t a){uint32_t q[4];nocturneBattlePanelOwnerCpuRead(reg,q);memcpy(at(a&~15u),q,16);}
static void nativeMultiply(unsigned rd,uint32_t a,uint32_t b,int isSigned,int secondary){
 uint64_t p=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)b):(uint64_t)a*b;
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 else nocturneEffectHostSetHilo(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 if(rd)set(rd,sx((uint32_t)p));
}






static void qmt(unsigned vf,unsigned reg){
 uint32_t q[4];nocturneBattlePanelOwnerCpuRead(reg,q);nocturneBattlePanelOwnerVuWrite(vf,q);
}
static void qmf(unsigned reg,unsigned vf){
 uint32_t q[4];nocturneBattlePanelOwnerVuRead(vf,q);nocturneBattlePanelOwnerCpuWrite(reg,q);
}
static void moveVu(unsigned dest,unsigned source){
 uint32_t q[4];nocturneBattlePanelOwnerVuRead(source,q);nocturneBattlePanelOwnerVuWrite(dest,q);
}
static void mulVu(unsigned dest,unsigned first,unsigned second,unsigned broadcastX){
 uint32_t a[4],b[4],q[4];unsigned k;
 nocturneBattlePanelOwnerVuRead(first,a);nocturneBattlePanelOwnerVuRead(second,b);
 for(k=0;k<4u;++k)q[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[broadcastX?0u:k]);
 nocturneBattlePanelOwnerVuWrite(dest,q);
}
static uint32_t byteFloat(uint32_t value){
 unsigned top=0;uint32_t t=value;if(!value)return 0;
 while(t>1u){t>>=1;++top;}
 return ((top+127u)<<23)|((value<<(23u-top))&UINT32_C(0x007fffff));
}
static void itof(unsigned dest,unsigned source){
 uint32_t q[4];unsigned k;nocturneBattlePanelOwnerVuRead(source,q);
 for(k=0;k<4u;++k)q[k]=byteFloat(q[k]);nocturneBattlePanelOwnerVuWrite(dest,q);
}
static void ftoi(unsigned dest,unsigned source){
 uint32_t q[4];unsigned k;nocturneBattlePanelOwnerVuRead(source,q);
 for(k=0;k<4u;++k)q[k]=nocturneEffectFtoi0Bits(q[k]);nocturneBattlePanelOwnerVuWrite(dest,q);
}
static void pextlb(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint8_t x[16],y[16],z[16];
 nocturneBattlePanelOwnerCpuRead(a,aq);nocturneBattlePanelOwnerCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<8;k++){z[k*2]=y[k];z[k*2+1]=x[k];}memcpy(q,z,16);nocturneBattlePanelOwnerCpuWrite(d,q);
}
static void pextlh(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint16_t x[8],y[8],z[8];
 nocturneBattlePanelOwnerCpuRead(a,aq);nocturneBattlePanelOwnerCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<4;k++){z[k*2]=y[k];z[k*2+1]=x[k];}memcpy(q,z,16);nocturneBattlePanelOwnerCpuWrite(d,q);
}
static void ppach(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint16_t x[8],y[8],z[8];
 nocturneBattlePanelOwnerCpuRead(a,aq);nocturneBattlePanelOwnerCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<4;k++){z[k]=y[k*2];z[k+4]=x[k*2];}memcpy(q,z,16);nocturneBattlePanelOwnerCpuWrite(d,q);
}
static void ppacb(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint8_t x[16],y[16],z[16];
 nocturneBattlePanelOwnerCpuRead(a,aq);nocturneBattlePanelOwnerCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<8;k++){z[k]=y[k*2];z[k+8]=x[k*2];}memcpy(q,z,16);nocturneBattlePanelOwnerCpuWrite(d,q);
}
static void addVu(unsigned d,unsigned s,unsigned t){uint32_t a[4],b[4],q[4];
 nocturneBattlePanelOwnerVuRead(s,a);nocturneBattlePanelOwnerVuRead(t,b);
 for(unsigned k=0;k<4;k++)q[k]=(uint32_t)EE_ROT_VU_ADD(a[k],b[k]);nocturneBattlePanelOwnerVuWrite(d,q);}

static void body_00117b08(void);
static void body_001abbd0(void);
static void body_001abc88(void);
static void body_002797b0(void);
static void body_00279868(void);
static void body_00279980(void);
static void body_00279a88(void);
static void body_00279c00(void);
static void body_00279d30(void);
static void body_00279e20(void);
static void body_0027a7c0(void);
static void body_0027d888(void);
static void body_0027d9d8(void);
static void body_002ab0c8(void);
static void body_002ab0d8(void);
static void body_002ab0e8(void);
static void body_002acb50(void);
static void body_002acb78(void);
static void body_002acb90(void);
static void body_002acbb8(void);
static void body_002acd40(void);
static void body_002acdc0(void);
static void body_002ace38(void);
static void body_002acea0(void);
static void body_002acee8(void);
static void body_002ad130(void);
static void body_002aef00(void);
static void body_002aefd0(void);
static void body_002b9c18(void);
static void body_002b9c20(void);
static void body_002b9cc8(void);
static void body_002b9d38(void);
static void body_002b9d68(void);
static void body_002b9d78(void);
static void body_002b9d80(void);
static void body_002b9dd0(void);
static void body_00117b08(void){
uint64_t incoming=cpu(31);
/* 00117b08: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00117b0c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00117b10: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00117b14: jal 0x002acb50 */ set(31,UINT64_C(0x00117b1c));/* delay 00117b18 */ set(4,sx(UINT32_C(0x00000020)));body_002acb50();
/* 00117b1c: move s0,v0 */ set(16,cpu(2));
/* 00117b20: jal 0x002acb90 */ set(31,UINT64_C(0x00117b28));/* delay 00117b24 */ set(4,cpu(16));body_002acb90();
/* 00117b28: move v0,s0 */ set(2,cpu(16));
/* 00117b2c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00117b30: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00117b34: jr ra */ {uint64_t target=cpu(31);/* delay 00117b38 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001abbd0(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 001abbd0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 001abbd4: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 001abbd8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001abbdc: move v1,a0 */ set(3,cpu(4));
/* 001abbe0: c.le.S f0,f12 */ (void)(EE_FPU_COMPARE_S(f[0],f[12],2)!=0);
/* 001abbe4: bc1t 0x001abc80 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)!=0);/* delay 001abbe8 */ set(2,cpu(5));if(taken){goto L_001abc80;}}
/* 001abbec: sw a1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
/* 001abbf0: lui a0,0x3c00 */ set(4,sx(UINT32_C(0x3c000000)));
/* 001abbf4: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001abbf8: pextlb v0,zero,v0 */ pextlb(2u,0u,2u);
/* 001abbfc: pextlh v0,zero,v0 */ pextlh(2u,0u,2u);
/* 001abc00: qmtc2 v0,vf10 */ qmt(10u,2u);
/* 001abc04: vitof0.xyzw vf10,vf10 */ itof(10u,10u);
/* 001abc08: qmtc2 a0,vf2 */ qmt(2u,4u);
/* 001abc0c: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abc10: vmove.xyzw vf11,vf10 */ moveVu(11u,10u);
/* 001abc14: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 001abc18: addiu v1,sp,0x10 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 001abc1c: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001abc20: pextlb v0,zero,v0 */ pextlb(2u,0u,2u);
/* 001abc24: pextlh v0,zero,v0 */ pextlh(2u,0u,2u);
/* 001abc28: qmtc2 v0,vf10 */ qmt(10u,2u);
/* 001abc2c: vitof0.xyzw vf10,vf10 */ itof(10u,10u);
/* 001abc30: qmtc2 a0,vf2 */ qmt(2u,4u);
/* 001abc34: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abc38: sub.S f0,f0,f12 */ f[0]=EE_FPU_SUB_S(f[0],f[12]);
/* 001abc3c: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 001abc40: qmtc2 v0,vf2 */ qmt(2u,2u);
/* 001abc44: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abc48: mfc1 v1,f12 */ set(3,sx(f[12]));
/* 001abc4c: qmtc2 v1,vf2 */ qmt(2u,3u);
/* 001abc50: vmulx.xyzw vf11,vf11,vf2 */ mulVu(11u,11u,2u,1u);
/* 001abc54: vadd.xyzw vf10,vf10,vf11 */ addVu(10u,10u,11u);
/* 001abc58: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 001abc5c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 001abc60: mfc1 v1,f0 */ set(3,sx(f[0]));
/* 001abc64: qmtc2 v1,vf2 */ qmt(2u,3u);
/* 001abc68: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abc6c: vftoi0.xyzw vf10,vf10 */ ftoi(10u,10u);
/* 001abc70: qmfc2 v0,vf10 */ qmf(2u,10u);
/* 001abc74: ppach v0,zero,v0 */ ppach(2u,0u,2u);
/* 001abc78: ppacb v0,zero,v0 */ ppacb(2u,0u,2u);
/* 001abc7c: sw v0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
L_001abc80:;
/* 001abc80: jr ra */ {uint64_t target=cpu(31);/* delay 001abc84 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001abc88(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 001abc88: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001abc8c: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001abc90: lui a0,0x3c00 */ set(4,sx(UINT32_C(0x3c000000)));
/* 001abc94: lw v0,0x0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001abc98: pextlb v0,zero,v0 */ pextlb(2u,0u,2u);
/* 001abc9c: pextlh v0,zero,v0 */ pextlh(2u,0u,2u);
/* 001abca0: qmtc2 v0,vf10 */ qmt(10u,2u);
/* 001abca4: vitof0.xyzw vf10,vf10 */ itof(10u,10u);
/* 001abca8: qmtc2 a0,vf2 */ qmt(2u,4u);
/* 001abcac: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abcb0: vmove.xyzw vf11,vf10 */ moveVu(11u,10u);
/* 001abcb4: sw a1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));
/* 001abcb8: addiu v1,sp,0x10 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 001abcbc: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001abcc0: pextlb v0,zero,v0 */ pextlb(2u,0u,2u);
/* 001abcc4: pextlh v0,zero,v0 */ pextlh(2u,0u,2u);
/* 001abcc8: qmtc2 v0,vf10 */ qmt(10u,2u);
/* 001abccc: vitof0.xyzw vf10,vf10 */ itof(10u,10u);
/* 001abcd0: qmtc2 a0,vf2 */ qmt(2u,4u);
/* 001abcd4: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abcd8: vmul.xyzw vf10,vf10,vf11 */ mulVu(10u,10u,11u,0u);
/* 001abcdc: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 001abce0: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 001abce4: mfc1 v1,f0 */ set(3,sx(f[0]));
/* 001abce8: qmtc2 v1,vf2 */ qmt(2u,3u);
/* 001abcec: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abcf0: vftoi0.xyzw vf10,vf10 */ ftoi(10u,10u);
/* 001abcf4: qmfc2 v0,vf10 */ qmf(2u,10u);
/* 001abcf8: ppach v0,zero,v0 */ ppach(2u,0u,2u);
/* 001abcfc: ppacb v0,zero,v0 */ ppacb(2u,0u,2u);
/* 001abd00: jr ra */ {uint64_t target=cpu(31);/* delay 001abd04 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002797b0(void){
uint64_t incoming=cpu(31);
/* 002797b0: jr ra */ {uint64_t target=cpu(31);/* delay 002797b4 */ sw(ea(28,(int32_t)UINT32_C(0xffffcff8)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_00279868(void){
uint64_t incoming=cpu(31);
/* 00279868: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 0027986c: sd s8,0x40(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279870: move s8,a0 */ set(30,cpu(4));
/* 00279874: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 00279878: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0027987c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00279880: move s1,t1 */ set(17,cpu(9));
/* 00279884: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279888: move s2,t0 */ set(18,cpu(8));
/* 0027988c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279890: move s3,a3 */ set(19,cpu(7));
/* 00279894: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279898: move s4,a1 */ set(20,cpu(5));
/* 0027989c: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002798a0: move s5,a2 */ set(21,cpu(6));
/* 002798a4: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002798a8: move s0,t3 */ set(16,cpu(11));
/* 002798ac: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002798b0: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002798b4: jal 0x002acb50 */ set(31,UINT64_C(0x002798bc));/* delay 002798b8 */ set(21,sx((uint32_t)cpu(21)<<4));body_002acb50();
/* 002798bc: move s6,v0 */ set(22,cpu(2));
/* 002798c0: sll s4,s4,0x1 */ set(20,sx((uint32_t)cpu(20)<<1));
/* 002798c4: move a0,s6 */ set(4,cpu(22));
/* 002798c8: jal 0x002acb90 */ set(31,UINT64_C(0x002798d0));/* delay 002798cc */ set(16,sx((uint32_t)cpu(16)<<17));body_002acb90();
/* 002798d0: jal 0x002acb50 */ set(31,UINT64_C(0x002798d8));/* delay 002798d4 */ set(4,sx(UINT32_C(0x00000030)));body_002acb50();
/* 002798d8: li a1,0x30 */ set(5,sx(UINT32_C(0x00000030)));
/* 002798dc: move s7,v0 */ set(23,cpu(2));
/* 002798e0: sll s2,s2,0xe */ set(18,sx((uint32_t)cpu(18)<<14));
/* 002798e4: move a0,s7 */ set(4,cpu(23));
/* 002798e8: jal 0x002b9d38 */ set(31,UINT64_C(0x002798f0));/* delay 002798ec */ set(17,sx((uint32_t)cpu(17)<<15));body_002b9d38();
/* 002798f0: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 002798f4: sll s3,s3,0xc */ set(19,sx((uint32_t)cpu(19)<<12));
/* 002798f8: or s2,s2,s5 */ set(18,cpu(18)|cpu(21));
/* 002798fc: or s3,s3,s4 */ set(19,cpu(19)|cpu(20));
/* 00279900: or s0,s0,s8 */ set(16,cpu(16)|cpu(30));
/* 00279904: or s1,s1,v1 */ set(17,cpu(17)|cpu(3));
/* 00279908: li v1,0x47 */ set(3,sx(UINT32_C(0x00000047)));
/* 0027990c: or s1,s1,s3 */ set(17,cpu(17)|cpu(19));
/* 00279910: or s0,s0,s2 */ set(16,cpu(16)|cpu(18));
/* 00279914: or s0,s0,s1 */ set(16,cpu(16)|cpu(17));
/* 00279918: sd v1,0x28(v0) */ save(3,ea(2,(int32_t)UINT32_C(0x00000028)));
/* 0027991c: sd s0,0x20(v0) */ save(16,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 00279920: move a1,s7 */ set(5,cpu(23));
/* 00279924: jal 0x002acbb8 */ set(31,UINT64_C(0x0027992c));/* delay 00279928 */ set(4,cpu(22));body_002acbb8();
/* 0027992c: lw a0,-0x3008(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcff8)));
/* 00279930: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00279934: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00279938: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 0027993c: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00279940: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00279944: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0027994c));/* delay 00279948 */ set(5,cpu(22));if(target==UINT64_C(0x002acd40)){body_002acd40();}else{nocturneBattlePanelOwnerIndirect(target,UINT32_C(0x00279944));}}
/* 0027994c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00279950: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00279954: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279958: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027995c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279960: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279964: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279968: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027996c: ld s8,0x40(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279970: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00279974: jr ra */ {uint64_t target=cpu(31);/* delay 00279978 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_00279980(void){
uint64_t incoming=cpu(31);
/* 00279980: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00279984: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00279988: move s0,a0 */ set(16,cpu(4));
/* 0027998c: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 00279990: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00279994: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279998: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027999c: jal 0x002acb50 */ set(31,UINT64_C(0x002799a4));/* delay 002799a0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));body_002acb50();
/* 002799a4: move s1,v0 */ set(17,cpu(2));
/* 002799a8: jal 0x002acb90 */ set(31,UINT64_C(0x002799b0));/* delay 002799ac */ set(4,cpu(17));body_002acb90();
/* 002799b0: jal 0x002acb50 */ set(31,UINT64_C(0x002799b8));/* delay 002799b4 */ set(4,sx(UINT32_C(0x00000030)));body_002acb50();
/* 002799b8: li a1,0x30 */ set(5,sx(UINT32_C(0x00000030)));
/* 002799bc: move s2,v0 */ set(18,cpu(2));
/* 002799c0: jal 0x002b9d38 */ set(31,UINT64_C(0x002799c8));/* delay 002799c4 */ set(4,cpu(18));body_002b9d38();
/* 002799c8: move a0,v0 */ set(4,cpu(2));
/* 002799cc: sltiu v0,s0,0x14 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000014));
/* 002799d0: beq v0,zero,0x00279a34 */ {int taken=(cpu(2)==cpu(0));/* delay 002799d4 */ set(2,sx(UINT32_C(0x00000044)));if(taken){goto L_00279a34;}}
/* 002799d8: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002799dc: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002799e0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002799e4: lw v1,0x52b0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x000052b0)));
/* 002799e8: jr v1 */ {uint64_t target=cpu(3);/* delay 002799ec */ switch((uint32_t)target){case UINT32_C(0x002799f0):goto L_002799f0;case UINT32_C(0x002799f8):goto L_002799f8;case UINT32_C(0x00279a00):goto L_00279a00;case UINT32_C(0x00279a08):goto L_00279a08;case UINT32_C(0x00279a10):goto L_00279a10;case UINT32_C(0x00279a18):goto L_00279a18;case UINT32_C(0x00279a20):goto L_00279a20;case UINT32_C(0x00279a28):goto L_00279a28;case UINT32_C(0x00279a30):goto L_00279a30;default:abort();}}
L_002799f0:;
/* 002799f0: b 0x00279a34 */ /* delay 002799f4 */ set(2,sx(UINT32_C(0x00000048)));goto L_00279a34;
L_002799f8:;
/* 002799f8: b 0x00279a34 */ /* delay 002799fc */ set(2,sx(UINT32_C(0x00000042)));goto L_00279a34;
L_00279a00:;
/* 00279a00: b 0x00279a34 */ /* delay 00279a04 */ set(2,sx(UINT32_C(0x00000084)));goto L_00279a34;
L_00279a08:;
/* 00279a08: b 0x00279a34 */ /* delay 00279a0c */ set(2,sx(UINT32_C(0x00000006)));goto L_00279a34;
L_00279a10:;
/* 00279a10: b 0x00279a34 */ /* delay 00279a14 */ set(2,sx(UINT32_C(0x00000089)));goto L_00279a34;
L_00279a18:;
/* 00279a18: b 0x00279a34 */ /* delay 00279a1c */ set(2,sx(UINT32_C(0x00000042)));goto L_00279a34;
L_00279a20:;
/* 00279a20: b 0x00279a34 */ /* delay 00279a24 */ set(2,sx(UINT32_C(0x0000002a)));goto L_00279a34;
L_00279a28:;
/* 00279a28: b 0x00279a34 */ /* delay 00279a2c */ set(2,sx(UINT32_C(0x0000004a)));goto L_00279a34;
L_00279a30:;
/* 00279a30: li v0,0x44 */ set(2,sx(UINT32_C(0x00000044)));
L_00279a34:;
/* 00279a34: sd v0,0x20(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 00279a38: li v0,0x42 */ set(2,sx(UINT32_C(0x00000042)));
/* 00279a3c: move a1,s2 */ set(5,cpu(18));
/* 00279a40: sd v0,0x28(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 00279a44: jal 0x002acbb8 */ set(31,UINT64_C(0x00279a4c));/* delay 00279a48 */ set(4,cpu(17));body_002acbb8();
/* 00279a4c: lw a0,-0x3008(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcff8)));
/* 00279a50: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00279a54: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00279a58: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 00279a5c: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00279a60: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00279a64: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00279a6c));/* delay 00279a68 */ set(5,cpu(17));if(target==UINT64_C(0x002acd40)){body_002acd40();}else{nocturneBattlePanelOwnerIndirect(target,UINT32_C(0x00279a64));}}
/* 00279a6c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00279a70: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00279a74: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279a78: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279a7c: jr ra */ {uint64_t target=cpu(31);/* delay 00279a80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00279a88(void){
uint64_t incoming=cpu(31);
/* 00279a88: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 00279a8c: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279a90: move s5,a0 */ set(21,cpu(4));
/* 00279a94: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00279a98: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279a9c: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279aa0: move s1,a1 */ set(17,cpu(5));
/* 00279aa4: lw s0,0x60(sp) */ lw(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00279aa8: sll s5,s5,0x4 */ set(21,sx((uint32_t)cpu(21)<<4));
/* 00279aac: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279ab0: move s2,t2 */ set(18,cpu(10));
/* 00279ab4: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279ab8: move s3,t3 */ set(19,cpu(11));
/* 00279abc: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279ac0: move s4,a2 */ set(20,cpu(6));
/* 00279ac4: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279ac8: move s6,a3 */ set(22,cpu(7));
/* 00279acc: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00279ad0: move s7,t0 */ set(23,cpu(8));
/* 00279ad4: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00279ad8: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00279adc: jal 0x002b9dd0 */ set(31,UINT64_C(0x00279ae4));/* delay 00279ae0 */ set(30,cpu(9));body_002b9dd0();
/* 00279ae4: move a0,v0 */ set(4,cpu(2));
/* 00279ae8: sll s1,s1,0x3 */ set(17,sx((uint32_t)cpu(17)<<3));
/* 00279aec: jal 0x002b9d78 */ set(31,UINT64_C(0x00279af4));/* delay 00279af0 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));body_002b9d78();
/* 00279af4: sll s7,s7,0x4 */ set(23,sx((uint32_t)cpu(23)<<4));
/* 00279af8: addiu s5,s5,0x7000 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00007000)));
/* 00279afc: sll t1,s8,0x4 */ set(9,sx((uint32_t)cpu(30)<<4));
/* 00279b00: addiu s1,s1,0x7900 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00007900)));
/* 00279b04: sra v1,s0,0x8 */ set(3,sx((uint32_t)((int32_t)cpu(16)>>8)));
/* 00279b08: sra a1,s0,0x10 */ set(5,sx((uint32_t)((int32_t)cpu(16)>>16)));
/* 00279b0c: sll s2,s2,0x4 */ set(18,sx((uint32_t)cpu(18)<<4));
/* 00279b10: sll s3,s3,0x4 */ set(19,sx((uint32_t)cpu(19)<<4));
/* 00279b14: sll s4,s4,0x4 */ set(20,sx((uint32_t)cpu(20)<<4));
/* 00279b18: sll s6,s6,0x3 */ set(22,sx((uint32_t)cpu(22)<<3));
/* 00279b1c: addu s3,t1,s3 */ set(19,sx((uint32_t)cpu(9)+(uint32_t)cpu(19)));
/* 00279b20: li a3,-0x1 */ set(7,sx(UINT32_C(0xffffffff)));
/* 00279b24: andi v1,v1,0xff */ set(3,cpu(3)&UINT32_C(0x000000ff));
/* 00279b28: srl a2,s0,0x18 */ set(6,sx((uint32_t)cpu(16)>>24));
/* 00279b2c: andi a1,a1,0xff */ set(5,cpu(5)&UINT32_C(0x000000ff));
/* 00279b30: addu s2,s7,s2 */ set(18,sx((uint32_t)cpu(23)+(uint32_t)cpu(18)));
/* 00279b34: addu s4,s5,s4 */ set(20,sx((uint32_t)cpu(21)+(uint32_t)cpu(20)));
/* 00279b38: addu s6,s1,s6 */ set(22,sx((uint32_t)cpu(17)+(uint32_t)cpu(22)));
/* 00279b3c: andi s0,s0,0xff */ set(16,cpu(16)&UINT32_C(0x000000ff));
/* 00279b40: sw v1,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 00279b44: sw a3,0x48(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(7));
/* 00279b48: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 00279b4c: sw t1,0x14(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(9));
/* 00279b50: sw a3,0x28(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(7));
/* 00279b54: sw a1,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 00279b58: sw a2,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(6));
/* 00279b5c: sw s0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 00279b60: sw s2,0x30(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(18));
/* 00279b64: sw s3,0x34(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(19));
/* 00279b68: sw s4,0x40(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(20));
/* 00279b6c: sw s6,0x44(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(22));
/* 00279b70: sw s7,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(23));
/* 00279b74: sw s5,0x20(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(21));
/* 00279b78: sw s1,0x24(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(17));
/* 00279b7c: sh zero,0x4c(v0) */ sh(ea(2,(int32_t)UINT32_C(0x0000004c)),(uint16_t)cpu(0));
/* 00279b80: jal 0x002acb50 */ set(31,UINT64_C(0x00279b88));/* delay 00279b84 */ sh(ea(2,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(0));body_002acb50();
/* 00279b88: move s0,v0 */ set(16,cpu(2));
/* 00279b8c: jal 0x002acb90 */ set(31,UINT64_C(0x00279b94));/* delay 00279b90 */ set(4,cpu(16));body_002acb90();
/* 00279b94: move a0,s0 */ set(4,cpu(16));
/* 00279b98: lw a1,0x68(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00279b9c: jal 0x002b9cc8 */ set(31,UINT64_C(0x00279ba4));/* delay 00279ba0 */ set(6,cpu(0));body_002b9cc8();
/* 00279ba4: move a0,s0 */ set(4,cpu(16));
/* 00279ba8: jal 0x002acbb8 */ set(31,UINT64_C(0x00279bb0));/* delay 00279bac */ lw(5,ea(29,(int32_t)UINT32_C(0x00000000)));body_002acbb8();
/* 00279bb0: lw a0,-0x3008(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcff8)));
/* 00279bb4: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00279bb8: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00279bbc: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 00279bc0: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00279bc4: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00279bc8: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00279bd0));/* delay 00279bcc */ set(5,cpu(16));if(target==UINT64_C(0x002acd40)){body_002acd40();}else{nocturneBattlePanelOwnerIndirect(target,UINT32_C(0x00279bc8));}}
/* 00279bd0: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279bd4: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279bd8: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279bdc: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279be0: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279be4: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279be8: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279bec: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00279bf0: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00279bf4: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00279bf8: jr ra */ {uint64_t target=cpu(31);/* delay 00279bfc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_00279c00(void){
uint64_t incoming=cpu(31);
/* 00279c00: srl a2,a0,0x8 */ set(6,sx((uint32_t)cpu(4)>>8));
/* 00279c04: andi a1,a0,0xff00 */ set(5,cpu(4)&UINT32_C(0x0000ff00));
/* 00279c08: sll a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)<<8));
/* 00279c0c: andi a2,a2,0xff00 */ set(6,cpu(6)&UINT32_C(0x0000ff00));
/* 00279c10: srl v0,a0,0x18 */ set(2,sx((uint32_t)cpu(4)>>24));
/* 00279c14: sll v1,a0,0x18 */ set(3,sx((uint32_t)cpu(4)<<24));
/* 00279c18: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 00279c1c: or a1,a1,a2 */ set(5,cpu(5)|cpu(6));
/* 00279c20: or v0,v0,a1 */ set(2,cpu(2)|cpu(5));
/* 00279c24: sw a0,-0x2ff0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd010)),(uint32_t)cpu(4));
/* 00279c28: jr ra */ {uint64_t target=cpu(31);/* delay 00279c2c */ sw(ea(28,(int32_t)UINT32_C(0xffffd014)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_00279d30(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00279d30: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 00279d34: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279d38: move s1,a3 */ set(17,cpu(7));
/* 00279d3c: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279d40: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279d44: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279d48: move s5,a0 */ set(21,cpu(4));
/* 00279d4c: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279d50: move s6,a1 */ set(22,cpu(5));
/* 00279d54: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00279d58: move s7,t1 */ set(23,cpu(9));
/* 00279d5c: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00279d60: move a0,t0 */ set(4,cpu(8));
/* 00279d64: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279d68: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279d6c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 00279d70: lw v1,0xc(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x0000000c)));
/* 00279d74: lw v0,0x10(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 00279d78: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 00279d7c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00279d80: lw s2,0x4(a2) */ lw(18,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 00279d84: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00279d88: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00279d8c: lw s0,0x0(a2) */ lw(16,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 00279d90: mul.S f1,f1,f12 */ f[1]=EE_FPU_MUL_S(f[1],f[12]);
/* 00279d94: mul.S f0,f0,f12 */ f[0]=EE_FPU_MUL_S(f[0],f[12]);
/* 00279d98: cvt.w.S f2,f1 */ f[2]=EE_FPU_CVT_W_S(f[1]);
/* 00279d9c: mfc1 s3,f2 */ set(19,sx(f[2]));
/* 00279da0: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00279da4: mfc1 s4,f1 */ set(20,sx(f[1]));
/* 00279da8: subu v1,s3,v1 */ set(3,sx((uint32_t)cpu(19)-(uint32_t)cpu(3)));
/* 00279dac: subu v0,s4,v0 */ set(2,sx((uint32_t)cpu(20)-(uint32_t)cpu(2)));
/* 00279db0: sra v1,v1,0x1 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>1)));
/* 00279db4: sra v0,v0,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 00279db8: subu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(3)));
/* 00279dbc: jal 0x001abc88 */ set(31,UINT64_C(0x00279dc4));/* delay 00279dc0 */ set(18,sx((uint32_t)cpu(18)-(uint32_t)cpu(2)));body_001abc88();
/* 00279dc4: lw t3,0xc(s1) */ lw(11,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 00279dc8: addu a0,s0,s5 */ set(4,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));
/* 00279dcc: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00279dd0: addu a1,s2,s6 */ set(5,sx((uint32_t)cpu(18)+(uint32_t)cpu(22)));
/* 00279dd4: lw t1,0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 00279dd8: move a2,s3 */ set(6,cpu(19));
/* 00279ddc: lw t2,0x8(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 00279de0: move a3,s4 */ set(7,cpu(20));
/* 00279de4: sw s7,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(23));
/* 00279de8: jal 0x00279a88 */ set(31,UINT64_C(0x00279df0));/* delay 00279dec */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));body_00279a88();
/* 00279df0: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279df4: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279df8: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279dfc: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279e00: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279e04: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279e08: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279e0c: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00279e10: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00279e14: jr ra */ {uint64_t target=cpu(31);/* delay 00279e18 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_00279e20(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00279e20: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 00279e24: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279e28: move s2,a3 */ set(18,cpu(7));
/* 00279e2c: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279e30: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279e34: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279e38: move s5,a0 */ set(21,cpu(4));
/* 00279e3c: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279e40: move s6,t1 */ set(22,cpu(9));
/* 00279e44: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00279e48: move s7,a1 */ set(23,cpu(5));
/* 00279e4c: sd ra,0x50(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00279e50: move a0,t0 */ set(4,cpu(8));
/* 00279e54: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279e58: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279e5c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 00279e60: lw v1,0xc(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x0000000c)));
/* 00279e64: lw v0,0x10(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 00279e68: mtc1 v1,f1 */ f[1]=(uint32_t)cpu(3);
/* 00279e6c: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 00279e70: lw s1,0x4(a2) */ lw(17,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 00279e74: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 00279e78: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 00279e7c: lw s0,0x0(a2) */ lw(16,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 00279e80: mul.S f1,f1,f12 */ f[1]=EE_FPU_MUL_S(f[1],f[12]);
/* 00279e84: mul.S f0,f0,f13 */ f[0]=EE_FPU_MUL_S(f[0],f[13]);
/* 00279e88: cvt.w.S f2,f1 */ f[2]=EE_FPU_CVT_W_S(f[1]);
/* 00279e8c: mfc1 s3,f2 */ set(19,sx(f[2]));
/* 00279e90: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 00279e94: mfc1 s4,f1 */ set(20,sx(f[1]));
/* 00279e98: subu v1,s3,v1 */ set(3,sx((uint32_t)cpu(19)-(uint32_t)cpu(3)));
/* 00279e9c: subu v0,s4,v0 */ set(2,sx((uint32_t)cpu(20)-(uint32_t)cpu(2)));
/* 00279ea0: sra v1,v1,0x1 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>1)));
/* 00279ea4: sra v0,v0,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 00279ea8: subu s0,s0,v1 */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(3)));
/* 00279eac: jal 0x001abc88 */ set(31,UINT64_C(0x00279eb4));/* delay 00279eb0 */ set(17,sx((uint32_t)cpu(17)-(uint32_t)cpu(2)));body_001abc88();
/* 00279eb4: lw t3,0xc(s2) */ lw(11,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 00279eb8: addu a0,s0,s5 */ set(4,sx((uint32_t)cpu(16)+(uint32_t)cpu(21)));
/* 00279ebc: lw t0,0x0(s2) */ lw(8,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00279ec0: addu a1,s1,s7 */ set(5,sx((uint32_t)cpu(17)+(uint32_t)cpu(23)));
/* 00279ec4: lw t1,0x4(s2) */ lw(9,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 00279ec8: move a2,s3 */ set(6,cpu(19));
/* 00279ecc: lw t2,0x8(s2) */ lw(10,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 00279ed0: move a3,s4 */ set(7,cpu(20));
/* 00279ed4: sw s6,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(22));
/* 00279ed8: jal 0x00279a88 */ set(31,UINT64_C(0x00279ee0));/* delay 00279edc */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));body_00279a88();
/* 00279ee0: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279ee4: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279ee8: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279eec: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279ef0: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279ef4: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279ef8: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279efc: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00279f00: ld ra,0x50(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00279f04: jr ra */ {uint64_t target=cpu(31);/* delay 00279f08 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_0027a7c0(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 0027a7c0: addiu sp,sp,-0xd0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff30)));
/* 0027a7c4: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027a7c8: move s2,a2 */ set(18,cpu(6));
/* 0027a7cc: sd s3,0x48(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027a7d0: move s3,a3 */ set(19,cpu(7));
/* 0027a7d4: sd s4,0x50(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027a7d8: move s4,a0 */ set(20,cpu(4));
/* 0027a7dc: sd s5,0x58(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027a7e0: move s5,a1 */ set(21,cpu(5));
/* 0027a7e4: sd s0,0x30(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0027a7e8: move s0,t0 */ set(16,cpu(8));
/* 0027a7ec: sd s1,0x38(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027a7f0: move s1,t1 */ set(17,cpu(9));
/* 0027a7f4: sd s6,0x60(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027a7f8: move s6,t2 */ set(22,cpu(10));
/* 0027a7fc: sd s7,0x68(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027a800: move s7,t3 */ set(23,cpu(11));
/* 0027a804: sd s8,0x70(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027a808: addu s2,s2,s4 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(20)));
/* 0027a80c: swc1 f29,0xc8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000c8)),f[29]);
/* 0027a810: addu s3,s3,s5 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(21)));
/* 0027a814: swc1 f28,0xc0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000c0)),f[28]);
/* 0027a818: sra s1,s1,0x1 */ set(17,sx((uint32_t)((int32_t)cpu(17)>>1)));
/* 0027a81c: swc1 f27,0xb8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b8)),f[27]);
/* 0027a820: mtc1 s2,f27 */ f[27]=(uint32_t)cpu(18);
/* 0027a824: cvt.s.W f27,f27 */ f[27]=EE_FPU_CVT_S_W(f[27]);
/* 0027a828: swc1 f26,0xb0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b0)),f[26]);
/* 0027a82c: mtc1 s1,f26 */ f[26]=(uint32_t)cpu(17);
/* 0027a830: cvt.s.W f26,f26 */ f[26]=EE_FPU_CVT_S_W(f[26]);
/* 0027a834: swc1 f25,0xa8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000a8)),f[25]);
/* 0027a838: mtc1 s3,f25 */ f[25]=(uint32_t)cpu(19);
/* 0027a83c: cvt.s.W f25,f25 */ f[25]=EE_FPU_CVT_S_W(f[25]);
/* 0027a840: swc1 f24,0xa0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000a0)),f[24]);
/* 0027a844: sra s0,s0,0x1 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>1)));
/* 0027a848: swc1 f23,0x98(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000098)),f[23]);
/* 0027a84c: sqrt.S f23,f26 */ f[23u]=nocturneBattlePanelOwnerSqrtS(f[26u],UINT32_C(0x0027a84c));
/* 0027a850: swc1 f22,0x90(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000090)),f[22]);
/* 0027a854: swc1 f21,0x88(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000088)),f[21]);
/* 0027a858: swc1 f20,0x80(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000080)),f[20]);
/* 0027a85c: mtc1 s0,f20 */ f[20]=(uint32_t)cpu(16);
/* 0027a860: cvt.s.W f20,f20 */ f[20]=EE_FPU_CVT_S_W(f[20]);
/* 0027a864: sd ra,0x78(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027a868: jal 0x00117b08 */ set(31,UINT64_C(0x0027a870));/* delay 0027a86c */ f[24]=f[25];body_00117b08();
/* 0027a870: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027a874: move s8,v0 */ set(30,cpu(2));
/* 0027a878: sll v1,s3,0x3 */ set(3,sx((uint32_t)cpu(19)<<3));
/* 0027a87c: move a0,s6 */ set(4,cpu(22));
/* 0027a880: sll v0,s2,0x4 */ set(2,sx((uint32_t)cpu(18)<<4));
/* 0027a884: addiu s4,v1,0x7900 */ set(20,sx((uint32_t)cpu(3)+UINT32_C(0x00007900)));
/* 0027a888: jal 0x001abc88 */ set(31,UINT64_C(0x0027a890));/* delay 0027a88c */ set(21,sx((uint32_t)cpu(2)+UINT32_C(0x00007000)));body_001abc88();
/* 0027a890: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027a894: move a0,s7 */ set(4,cpu(23));
/* 0027a898: nop  */ 
/* 0027a89c: nop  */ 
/* 0027a8a0: div.S f29,f20,f23 */ f[29]=EE_FPU_DIV_S(f[20],f[23]);
/* 0027a8a4: jal 0x001abc88 */ set(31,UINT64_C(0x0027a8ac));/* delay 0027a8a8 */ set(19,cpu(2));body_001abc88();
/* 0027a8ac: add.S f0,f23,f23 */ f[0]=EE_FPU_ADD_S(f[23],f[23]);
/* 0027a8b0: lui at,0x4220 */ set(1,sx(UINT32_C(0x42200000)));
/* 0027a8b4: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027a8b8: add.S f21,f27,f20 */ f[21]=EE_FPU_ADD_S(f[27],f[20]);
/* 0027a8bc: move s6,zero */ set(22,cpu(0));
/* 0027a8c0: li s7,-0x1 */ set(23,sx(UINT32_C(0xffffffff)));
/* 0027a8c4: move s2,v0 */ set(18,cpu(2));
/* 0027a8c8: mov.S f22,f24 */ f[22]=f[24];
/* 0027a8cc: nop  */ 
/* 0027a8d0: nop  */ 
/* 0027a8d4: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027a8d8: neg.S f28,f0 */ f[28u]=f[0u]^UINT32_C(0x80000000);
/* 0027a8dc: add.S f23,f23,f28 */ f[23]=EE_FPU_ADD_S(f[23],f[28]);
L_0027a8e0:;
/* 0027a8e0: move a0,s8 */ set(4,cpu(30));
/* 0027a8e4: cvt.w.S f0,f21 */ f[0]=EE_FPU_CVT_W_S(f[21]);
/* 0027a8e8: mfc1 s1,f0 */ set(17,sx(f[0]));
/* 0027a8ec: li a1,0x14c */ set(5,sx(UINT32_C(0x0000014c)));
/* 0027a8f0: cvt.w.S f0,f22 */ f[0]=EE_FPU_CVT_W_S(f[22]);
/* 0027a8f4: mfc1 t2,f0 */ set(10,sx(f[0]));
/* 0027a8f8: move a2,s5 */ set(6,cpu(21));
/* 0027a8fc: move a3,s4 */ set(7,cpu(20));
/* 0027a900: move t0,s3 */ set(8,cpu(19));
/* 0027a904: mul.S f20,f23,f23 */ f[20]=EE_FPU_MUL_S(f[23],f[23]);
/* 0027a908: move t3,s2 */ set(11,cpu(18));
/* 0027a90c: mul.S f21,f23,f29 */ f[21]=EE_FPU_MUL_S(f[23],f[29]);
/* 0027a910: sll s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)<<4));
/* 0027a914: addiu s1,s1,0x7000 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00007000)));
/* 0027a918: sll t2,t2,0x3 */ set(10,sx((uint32_t)cpu(10)<<3));
/* 0027a91c: addiu t2,t2,0x7900 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00007900)));
/* 0027a920: move t1,s1 */ set(9,cpu(17));
/* 0027a924: sub.S f20,f26,f20 */ f[20]=EE_FPU_SUB_S(f[26],f[20]);
/* 0027a928: sw s2,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 0027a92c: add.S f21,f27,f21 */ f[21]=EE_FPU_ADD_S(f[27],f[21]);
/* 0027a930: sw s7,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(23));
/* 0027a934: sw zero,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
/* 0027a938: addiu s6,s6,0x1 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000001)));
/* 0027a93c: add.S f22,f25,f20 */ f[22]=EE_FPU_ADD_S(f[25],f[20]);
/* 0027a940: cvt.w.S f0,f21 */ f[0]=EE_FPU_CVT_W_S(f[21]);
/* 0027a944: mfc1 s0,f0 */ set(16,sx(f[0]));
/* 0027a948: sub.S f20,f25,f20 */ f[20]=EE_FPU_SUB_S(f[25],f[20]);
/* 0027a94c: cvt.w.S f0,f22 */ f[0]=EE_FPU_CVT_W_S(f[22]);
/* 0027a950: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 0027a954: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027a958: addiu s0,s0,0x7000 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00007000)));
/* 0027a95c: sw s0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 0027a960: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0027a964: addiu v0,v0,0x7900 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00007900)));
/* 0027a968: jal 0x002aefd0 */ set(31,UINT64_C(0x0027a970));/* delay 0027a96c */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_002aefd0();
/* 0027a970: cvt.w.S f0,f24 */ f[0]=EE_FPU_CVT_W_S(f[24]);
/* 0027a974: mfc1 t2,f0 */ set(10,sx(f[0]));
/* 0027a978: mov.S f24,f20 */ f[24]=f[20];
/* 0027a97c: cvt.w.S f0,f20 */ f[0]=EE_FPU_CVT_W_S(f[20]);
/* 0027a980: mfc1 v0,f0 */ set(2,sx(f[0]));
/* 0027a984: move t1,s1 */ set(9,cpu(17));
/* 0027a988: move a0,s8 */ set(4,cpu(30));
/* 0027a98c: li a1,0x14c */ set(5,sx(UINT32_C(0x0000014c)));
/* 0027a990: move a2,s5 */ set(6,cpu(21));
/* 0027a994: move a3,s4 */ set(7,cpu(20));
/* 0027a998: sll t2,t2,0x3 */ set(10,sx((uint32_t)cpu(10)<<3));
/* 0027a99c: move t0,s3 */ set(8,cpu(19));
/* 0027a9a0: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0027a9a4: addiu t2,t2,0x7900 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00007900)));
/* 0027a9a8: addiu v0,v0,0x7900 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00007900)));
/* 0027a9ac: move t3,s2 */ set(11,cpu(18));
/* 0027a9b0: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0027a9b4: sw s0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 0027a9b8: sw s2,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(18));
/* 0027a9bc: sw s7,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(23));
/* 0027a9c0: jal 0x002aefd0 */ set(31,UINT64_C(0x0027a9c8));/* delay 0027a9c4 */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));body_002aefd0();
/* 0027a9c8: sltiu v0,s6,0x28 */ set(2,cpu(22)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000028));
/* 0027a9cc: bnel v0,zero,0x0027a8e0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027a9d0 */ f[23]=EE_FPU_ADD_S(f[23],f[28]);goto L_0027a8e0;}}
/* 0027a9d4: lui a0,0x2f */ set(4,sx(UINT32_C(0x002f0000)));
/* 0027a9d8: addiu a0,a0,0x67f8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000067f8)));
/* 0027a9dc: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 0027a9e0: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0027a9e8));/* delay 0027a9e4 */ set(5,cpu(30));if(target==UINT64_C(0x002acd40)){body_002acd40();}else{nocturneBattlePanelOwnerIndirect(target,UINT32_C(0x0027a9e0));}}
/* 0027a9e8: ld s0,0x30(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0027a9ec: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027a9f0: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027a9f4: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027a9f8: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027a9fc: ld s5,0x58(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027aa00: ld s6,0x60(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027aa04: ld s7,0x68(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027aa08: ld s8,0x70(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027aa0c: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027aa10: lwc1 f29,0xc8(sp) */ f[29]=word(ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 0027aa14: lwc1 f28,0xc0(sp) */ f[28]=word(ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 0027aa18: lwc1 f27,0xb8(sp) */ f[27]=word(ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0027aa1c: lwc1 f26,0xb0(sp) */ f[26]=word(ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0027aa20: lwc1 f25,0xa8(sp) */ f[25]=word(ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0027aa24: lwc1 f24,0xa0(sp) */ f[24]=word(ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0027aa28: lwc1 f23,0x98(sp) */ f[23]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0027aa2c: lwc1 f22,0x90(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0027aa30: lwc1 f21,0x88(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0027aa34: lwc1 f20,0x80(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0027aa38: jr ra */ {uint64_t target=cpu(31);/* delay 0027aa3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000d0)));checkReturn(target,incoming);return;}
}
static void body_0027d888(void){
uint64_t incoming=cpu(31);
/* 0027d888: lw v0,-0x2fc0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd040)));
/* 0027d88c: bne v0,zero,0x0027d8c4 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027d890 */ set(3,cpu(0));if(taken){goto L_0027d8c4;}}
/* 0027d894: lw v0,-0x2fb8(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd048)));
/* 0027d898: bnel v0,zero,0x0027d8c8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027d89c */ set(3,sx(UINT32_C(0x00000001)));goto L_0027d8c8;}}
/* 0027d8a0: lw v0,-0x2fac(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd054)));
/* 0027d8a4: bnel v0,zero,0x0027d8c8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027d8a8 */ set(3,sx(UINT32_C(0x00000001)));goto L_0027d8c8;}}
/* 0027d8ac: lw v0,-0x2f88(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd078)));
/* 0027d8b0: bnel v0,zero,0x0027d8c8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027d8b4 */ set(3,sx(UINT32_C(0x00000001)));goto L_0027d8c8;}}
/* 0027d8b8: lw v0,-0x2f90(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd070)));
/* 0027d8bc: beq v0,zero,0x0027d8c8 */ {int taken=(cpu(2)==cpu(0));/* delay 0027d8c0 */ if(taken){goto L_0027d8c8;}}
L_0027d8c4:;
/* 0027d8c4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
L_0027d8c8:;
/* 0027d8c8: jr ra */ {uint64_t target=cpu(31);/* delay 0027d8cc */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
static void body_0027d9d8(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();

/* 0027d9d8: addiu sp,sp,-0xe0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff20)));
/* 0027d9dc: sd s8,0x70(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027d9e0: move s8,a0 */ set(30,cpu(4));
/* 0027d9e4: sd s0,0x30(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0027d9e8: sd s1,0x38(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027d9ec: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027d9f0: sd s3,0x48(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027d9f4: sd s4,0x50(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027d9f8: sd s5,0x58(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027d9fc: sd s6,0x60(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027da00: sd s7,0x68(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027da04: sd ra,0x78(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027da08: swc1 f30,0xd0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000d0)),f[30]);
/* 0027da0c: swc1 f29,0xc8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000c8)),f[29]);
/* 0027da10: swc1 f28,0xc0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000c0)),f[28]);
/* 0027da14: swc1 f27,0xb8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b8)),f[27]);
/* 0027da18: swc1 f26,0xb0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000b0)),f[26]);
/* 0027da1c: swc1 f25,0xa8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000a8)),f[25]);
/* 0027da20: swc1 f24,0xa0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x000000a0)),f[24]);
/* 0027da24: swc1 f23,0x98(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000098)),f[23]);
/* 0027da28: swc1 f22,0x90(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000090)),f[22]);
/* 0027da2c: swc1 f21,0x88(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000088)),f[21]);
/* 0027da30: jal 0x0027d888 */ set(31,UINT64_C(0x0027da38));/* delay 0027da34 */ sw(ea(29,(int32_t)UINT32_C(0x00000080)),f[20]);body_0027d888();
/* 0027da38: beql v0,zero,0x0027f700 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027da3c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));goto L_0027f700;}}
/* 0027da40: jal 0x002797b0 */ set(31,UINT64_C(0x0027da48));/* delay 0027da44 */ set(4,sx(UINT32_C(0x00000047)));body_002797b0();
/* 0027da48: jal 0x00279980 */ set(31,UINT64_C(0x0027da50));/* delay 0027da4c */ set(4,cpu(0));body_00279980();
/* 0027da50: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 0027da54: move a1,zero */ set(5,cpu(0));
/* 0027da58: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 0027da5c: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 0027da60: move t0,zero */ set(8,cpu(0));
/* 0027da64: move t1,zero */ set(9,cpu(0));
/* 0027da68: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0027da6c: jal 0x00279868 */ set(31,UINT64_C(0x0027da74));/* delay 0027da70 */ set(11,sx(UINT32_C(0x00000001)));body_00279868();
/* 0027da74: jal 0x00279c00 */ set(31,UINT64_C(0x0027da7c));/* delay 0027da78 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd038)));body_00279c00();
/* 0027da7c: lw a1,0x60(s8) */ lw(5,ea(30,(int32_t)UINT32_C(0x00000060)));
/* 0027da80: andi v0,a1,0x8 */ set(2,cpu(5)&UINT32_C(0x00000008));
/* 0027da84: beq v0,zero,0x0027dac8 */ {int taken=(cpu(2)==cpu(0));/* delay 0027da88 */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027dac8;}}
/* 0027da8c: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027da90: lui a2,0x71 */ set(6,sx(UINT32_C(0x00710000)));
/* 0027da94: addiu v0,v0,0x180 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000180)));
/* 0027da98: addiu a0,a0,0x88 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000088)));
/* 0027da9c: ori a2,a2,0x539f */ set(6,cpu(6)|UINT32_C(0x0000539f));
/* 0027daa0: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 0027daa4: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027daa8: sw a0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(4));
/* 0027daac: lui s5,0x31 */ set(21,sx(UINT32_C(0x00310000)));
/* 0027dab0: sw a2,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(6));
/* 0027dab4: addiu s4,v1,0x70 */ set(20,sx((uint32_t)cpu(3)+UINT32_C(0x00000070)));
/* 0027dab8: ori s5,s5,0x109f */ set(21,cpu(21)|UINT32_C(0x0000109f));
/* 0027dabc: lw a3,0x12c(s8) */ lw(7,ea(30,(int32_t)UINT32_C(0x0000012c)));
/* 0027dac0: b 0x0027db04 */ /* delay 0027dac4 */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(7));goto L_0027db04;
L_0027dac8:;
/* 0027dac8: lw a3,0x128(s8) */ lw(7,ea(30,(int32_t)UINT32_C(0x00000128)));
/* 0027dacc: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027dad0: lui a0,0x4f */ set(4,sx(UINT32_C(0x004f0000)));
/* 0027dad4: lui a2,0x9f */ set(6,sx(UINT32_C(0x009f0000)));
/* 0027dad8: addiu v0,v0,0x190 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000190)));
/* 0027dadc: addiu a0,a0,0x70 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000070)));
/* 0027dae0: ori a2,a2,0x7153 */ set(6,cpu(6)|UINT32_C(0x00007153));
/* 0027dae4: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027dae8: lui s5,0x9e */ set(21,sx(UINT32_C(0x009e0000)));
/* 0027daec: sw a3,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(7));
/* 0027daf0: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 0027daf4: addiu s4,v1,0x88 */ set(20,sx((uint32_t)cpu(3)+UINT32_C(0x00000088)));
/* 0027daf8: sw a0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(4));
/* 0027dafc: ori s5,s5,0x2212 */ set(21,cpu(21)|UINT32_C(0x00002212));
/* 0027db00: sw a2,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(6));
L_0027db04:;
/* 0027db04: lw v1,-0x2f88(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd078)));
/* 0027db08: sltiu v0,v1,0x5 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 0027db0c: beq v0,zero,0x0027e054 */ {int taken=(cpu(2)==cpu(0));/* delay 0027db10 */ set(7,byte(ea(28,(int32_t)UINT32_C(0xffffd088))));if(taken){goto L_0027e054;}}
/* 0027db14: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 0027db18: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 0027db1c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0027db20: lw v1,0x53d0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x000053d0)));
/* 0027db24: jr v1 */ {uint64_t target=cpu(3);/* delay 0027db28 */ switch((uint32_t)target){case UINT32_C(0x0027db30):goto L_0027db30;case UINT32_C(0x0027dc20):goto L_0027dc20;case UINT32_C(0x0027dd70):goto L_0027dd70;case UINT32_C(0x0027e024):goto L_0027e024;case UINT32_C(0x0027e030):goto L_0027e030;default:abort();}}
L_0027db30:;
/* 0027db30: lbu a3,-0x2f78(gp) */ set(7,byte(ea(28,(int32_t)UINT32_C(0xffffd088))));
/* 0027db34: bne a3,zero,0x0027dc08 */ {int taken=(cpu(7)!=cpu(0));/* delay 0027db38 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd07c)));if(taken){goto L_0027dc08;}}
/* 0027db3c: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027db40: lui s3,0x4f */ set(19,sx(UINT32_C(0x004f0000)));
/* 0027db44: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027db48: lui s0,0x4f */ set(16,sx(UINT32_C(0x004f0000)));
/* 0027db4c: lw s1,0x0(v0) */ lw(17,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027db50: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027db54: addiu s0,s0,-0x8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff8)));
/* 0027db58: addiu s3,s3,-0x530 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xfffffad0)));
/* 0027db5c: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027db60: sll s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)<<4));
/* 0027db64: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 0027db68: jal 0x001abc88 */ set(31,UINT64_C(0x0027db70));/* delay 0027db6c */ lw(20,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027db70: lw t3,0xc(s1) */ lw(11,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027db74: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027db78: addiu s2,s0,0x14 */ set(18,sx((uint32_t)cpu(16)+UINT32_C(0x00000014)));
/* 0027db7c: lw a1,0x4(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027db80: lw a2,0xc(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027db84: addiu a0,a0,0x15d */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000015d)));
/* 0027db88: lw a3,0x10(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0027db8c: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027db90: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027db94: lw t1,0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027db98: lw t2,0x8(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 0027db9c: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027dba0: jal 0x00279a88 */ set(31,UINT64_C(0x0027dba8));/* delay 0027dba4 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));body_00279a88();
/* 0027dba8: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027dbac: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027dbb0: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027dbb4: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027dbb8: lw s0,0x4(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0027dbbc: jal 0x001abc88 */ set(31,UINT64_C(0x0027dbc4));/* delay 0027dbc0 */ lw(17,ea(30,(int32_t)UINT32_C(0x00000128)));body_001abc88();
/* 0027dbc4: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027dbc8: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0027dbcc: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 0027dbd0: lw a1,0x4(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0027dbd4: lw a3,0x10(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 0027dbd8: addiu a0,a0,0x15d */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000015d)));
/* 0027dbdc: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027dbe0: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027dbe4: lw a2,0xc(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 0027dbe8: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027dbec: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027dbf0: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027dbf4: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027dbf8: jal 0x00279a88 */ set(31,UINT64_C(0x0027dc00));/* delay 0027dbfc */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));body_00279a88();
/* 0027dc00: lbu a3,-0x2f78(gp) */ set(7,byte(ea(28,(int32_t)UINT32_C(0xffffd088))));
/* 0027dc04: lw v0,-0x2f84(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd07c)));
L_0027dc08:;
/* 0027dc08: addiu v1,v0,0x1 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027dc0c: bltz v1,0x0027e050 */ {int taken=((int64_t)cpu(3)<0);/* delay 0027dc10 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_0027e050;}}
/* 0027dc14: sw zero,-0x2f84(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd07c)),(uint32_t)cpu(0));
/* 0027dc18: b 0x0027e054 */ /* delay 0027dc1c */ sw(ea(28,(int32_t)UINT32_C(0xffffd078)),(uint32_t)cpu(2));goto L_0027e054;
L_0027dc20:;
/* 0027dc20: lw a2,-0x2f84(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd07c)));
/* 0027dc24: lui at,0x40c0 */ set(1,sx(UINT32_C(0x40c00000)));
/* 0027dc28: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027dc2c: mtc1 a2,f0 */ f[0]=(uint32_t)cpu(6);
/* 0027dc30: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027dc34: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027dc38: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027dc3c: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027dc40: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027dc44: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027dc48: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027dc4c: nop  */ 
/* 0027dc50: nop  */ 
/* 0027dc54: div.S f0,f0,f3 */ f[0]=EE_FPU_DIV_S(f[0],f[3]);
/* 0027dc58: sub.S f20,f1,f0 */ f[20]=EE_FPU_SUB_S(f[1],f[0]);
/* 0027dc5c: mul.S f0,f20,f2 */ f[0]=EE_FPU_MUL_S(f[20],f[2]);
/* 0027dc60: c.le.S f4,f0 */ (void)(EE_FPU_COMPARE_S(f[4],f[0],2)!=0);
/* 0027dc64: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027dc68: mfc1 a1,f1 */ set(5,sx(f[1]));
/* 0027dc6c: bc1f 0x0027dc8c */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027dc70 */ set(2,sx(UINT32_C(0x00800000)));if(taken){goto L_0027dc8c;}}
/* 0027dc74: sub.S f0,f0,f4 */ f[0]=EE_FPU_SUB_S(f[0],f[4]);
/* 0027dc78: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027dc7c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027dc80: mfc1 a1,f1 */ set(5,sx(f[1]));
/* 0027dc84: or a1,a1,v0 */ set(5,cpu(5)|cpu(2));
/* 0027dc88: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
L_0027dc8c:;
/* 0027dc8c: lbu a3,-0x2f78(gp) */ set(7,byte(ea(28,(int32_t)UINT32_C(0xffffd088))));
/* 0027dc90: sll t0,a1,0x18 */ set(8,sx((uint32_t)cpu(5)<<24));
/* 0027dc94: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027dc98: bne a3,zero,0x0027dd44 */ {int taken=(cpu(7)!=cpu(0));/* delay 0027dc9c */ set(23,cpu(8)|cpu(2));if(taken){goto L_0027dd44;}}
/* 0027dca0: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027dca4: lui s2,0x4f */ set(18,sx(UINT32_C(0x004f0000)));
/* 0027dca8: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027dcac: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 0027dcb0: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027dcb4: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027dcb8: addiu s1,s1,-0x8 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xfffffff8)));
/* 0027dcbc: addiu s2,s2,-0x530 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xfffffad0)));
/* 0027dcc0: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027dcc4: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027dcc8: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 0027dccc: jal 0x001abc88 */ set(31,UINT64_C(0x0027dcd4));/* delay 0027dcd0 */ lw(19,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027dcd4: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027dcd8: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027dcdc: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027dce0: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027dce4: addiu a0,a0,0x15d */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000015d)));
/* 0027dce8: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027dcec: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027dcf0: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027dcf4: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027dcf8: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027dcfc: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027dd00: jal 0x00279a88 */ set(31,UINT64_C(0x0027dd08));/* delay 0027dd04 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));body_00279a88();
/* 0027dd08: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027dd0c: addiu a2,s1,0x14 */ set(6,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));
/* 0027dd10: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027dd14: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0027dd18: move t0,s7 */ set(8,cpu(23));
/* 0027dd1c: lw a3,0x4(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0027dd20: mov.S f13,f20 */ f[13]=f[20];
/* 0027dd24: lw t1,0x128(s8) */ lw(9,ea(30,(int32_t)UINT32_C(0x00000128)));
/* 0027dd28: li a0,0x15d */ set(4,sx(UINT32_C(0x0000015d)));
/* 0027dd2c: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027dd30: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 0027dd34: jal 0x00279e20 */ set(31,UINT64_C(0x0027dd3c));/* delay 0027dd38 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(18)));body_00279e20();
/* 0027dd3c: lbu a3,-0x2f78(gp) */ set(7,byte(ea(28,(int32_t)UINT32_C(0xffffd088))));
/* 0027dd40: lw a2,-0x2f84(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd07c)));
L_0027dd44:;
/* 0027dd44: addiu v1,a2,0x1 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 0027dd48: slti v0,v1,0x6 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0027dd4c: bnel v0,zero,0x0027e054 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027dd50 */ sw(ea(28,(int32_t)UINT32_C(0xffffd07c)),(uint32_t)cpu(3));goto L_0027e054;}}
/* 0027dd54: lwc1 f0,-0x5bb4(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa44c)));
/* 0027dd58: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 0027dd5c: sw v0,-0x2f88(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd078)),(uint32_t)cpu(2));
/* 0027dd60: swc1 f0,-0x2f7c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd084)),f[0]);
/* 0027dd64: sw zero,-0x2f84(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd07c)),(uint32_t)cpu(0));
/* 0027dd68: b 0x0027e054 */ /* delay 0027dd6c */ sw(ea(28,(int32_t)UINT32_C(0xffffd080)),f[0]);goto L_0027e054;
L_0027dd70:;
/* 0027dd70: lw a2,-0x2f84(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd07c)));
/* 0027dd74: lui at,0x4140 */ set(1,sx(UINT32_C(0x41400000)));
/* 0027dd78: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027dd7c: mtc1 a2,f1 */ f[1]=(uint32_t)cpu(6);
/* 0027dd80: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027dd84: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027dd88: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027dd8c: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027dd90: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027dd94: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027dd98: mtc1 at,f5 */ f[5]=(uint32_t)cpu(1);
/* 0027dd9c: nop  */ 
/* 0027dda0: nop  */ 
/* 0027dda4: div.S f20,f1,f3 */ f[20]=EE_FPU_DIV_S(f[1],f[3]);
/* 0027dda8: sub.S f0,f0,f20 */ f[0]=EE_FPU_SUB_S(f[0],f[20]);
/* 0027ddac: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0027ddb0: c.le.S f5,f0 */ (void)(EE_FPU_COMPARE_S(f[5],f[0],2)!=0);
/* 0027ddb4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027ddb8: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027ddbc: bc1f 0x0027ddd8 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027ddc0 */ set(5,cpu(6));if(taken){goto L_0027ddd8;}}
/* 0027ddc4: sub.S f0,f0,f5 */ f[0]=EE_FPU_SUB_S(f[0],f[5]);
/* 0027ddc8: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027ddcc: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027ddd0: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027ddd4: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
L_0027ddd8:;
/* 0027ddd8: sll t0,v1,0x18 */ set(8,sx((uint32_t)cpu(3)<<24));
/* 0027dddc: lui v1,0x8000 */ set(3,sx(UINT32_C(0x80000000)));
/* 0027dde0: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
/* 0027dde4: subu v1,v1,t0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(8)));
/* 0027dde8: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027ddec: slti a0,a1,0x8 */ set(4,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0027ddf0: or s7,v1,v0 */ set(23,cpu(3)|cpu(2));
/* 0027ddf4: beq a0,zero,0x0027de30 */ {int taken=(cpu(4)==cpu(0));/* delay 0027ddf8 */ set(3,cpu(8)|cpu(2));if(taken){goto L_0027de30;}}
/* 0027ddfc: mtc1 a1,f2 */ f[2]=(uint32_t)cpu(5);
/* 0027de00: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0027de04: lui at,0x3e00 */ set(1,sx(UINT32_C(0x3e000000)));
/* 0027de08: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027de0c: lui at,0x4220 */ set(1,sx(UINT32_C(0x42200000)));
/* 0027de10: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027de14: mul.S f20,f2,f1 */ f[20]=EE_FPU_MUL_S(f[2],f[1]);
/* 0027de18: mul.S f0,f20,f0 */ f[0]=EE_FPU_MUL_S(f[20],f[0]);
/* 0027de1c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027de20: mfc1 s6,f1 */ set(22,sx(f[1]));
/* 0027de24: b 0x0027de38 */ /* delay 0027de28 */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffd088))));goto L_0027de38;
L_0027de30:;
/* 0027de30: li s6,0x28 */ set(22,sx(UINT32_C(0x00000028)));
/* 0027de34: lbu v0,-0x2f78(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffd088))));
L_0027de38:;
/* 0027de38: bne v0,zero,0x0027deb4 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027de3c */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_0027deb4;}}
/* 0027de40: lw v0,0x18(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027de44: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 0027de48: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027de4c: addiu s1,s1,-0x8 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xfffffff8)));
/* 0027de50: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027de54: move a0,v1 */ set(4,cpu(3));
/* 0027de58: jal 0x001abc88 */ set(31,UINT64_C(0x0027de60));/* delay 0027de5c */ lw(19,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027de60: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027de64: li s2,0x15d */ set(18,sx(UINT32_C(0x0000015d)));
/* 0027de68: lui at,0x4f */ set(1,sx(UINT32_C(0x004f0000)));
/* 0027de6c: addiu at,at,-0x530 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xfffffad0)));
/* 0027de70: addu s0,at,s0 */ set(16,sx((uint32_t)cpu(1)+(uint32_t)cpu(16)));
/* 0027de74: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027de78: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027de7c: subu s2,s2,s6 */ set(18,sx((uint32_t)cpu(18)-(uint32_t)cpu(22)));
/* 0027de80: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027de84: addu a0,a0,s2 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(18)));
/* 0027de88: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027de8c: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027de90: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027de94: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027de98: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027de9c: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027dea0: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027dea4: jal 0x00279a88 */ set(31,UINT64_C(0x0027deac));/* delay 0027dea8 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));body_00279a88();
/* 0027deac: lw a2,-0x2f84(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd07c)));
/* 0027deb0: slti v0,a2,0x4 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000004));
L_0027deb4:;
/* 0027deb4: bne v0,zero,0x0027e00c */ {int taken=(cpu(2)!=cpu(0));/* delay 0027deb8 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));if(taken){goto L_0027e00c;}}
/* 0027debc: slti v0,a2,0x8 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0027dec0: beq v0,zero,0x0027df28 */ {int taken=(cpu(2)==cpu(0));/* delay 0027dec4 */ set(22,cpu(0));if(taken){goto L_0027df28;}}
/* 0027dec8: addiu v0,a2,-0x4 */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0xfffffffc)));
/* 0027decc: lui at,0x3e80 */ set(1,sx(UINT32_C(0x3e800000)));
/* 0027ded0: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027ded4: mtc1 v0,f3 */ f[3]=(uint32_t)cpu(2);
/* 0027ded8: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027dedc: lwc1 f2,-0x2f7c(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffd084)));
/* 0027dee0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027dee4: mtc1 at,f5 */ f[5]=(uint32_t)cpu(1);
/* 0027dee8: lui at,0x4220 */ set(1,sx(UINT32_C(0x42200000)));
/* 0027deec: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027def0: lwc1 f0,-0x5bb0(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa450)));
/* 0027def4: mul.S f20,f3,f4 */ f[20]=EE_FPU_MUL_S(f[3],f[4]);
/* 0027def8: mul.S f0,f2,f0 */ f[0]=EE_FPU_MUL_S(f[2],f[0]);
/* 0027defc: mul.S f20,f20,f2 */ f[20]=EE_FPU_MUL_S(f[20],f[2]);
/* 0027df00: swc1 f0,-0x2f7c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd084)),f[0]);
/* 0027df04: sub.S f20,f5,f20 */ f[20]=EE_FPU_SUB_S(f[5],f[20]);
/* 0027df08: mul.S f1,f20,f1 */ f[1]=EE_FPU_MUL_S(f[20],f[1]);
/* 0027df0c: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0027df10: mfc1 s6,f0 */ set(22,sx(f[0]));
/* 0027df14: slti v0,s6,0x29 */ set(2,(int64_t)cpu(22)<(int64_t)(int32_t)UINT32_C(0x00000029));
/* 0027df18: beql v0,zero,0x0027df28 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027df1c */ set(22,sx(UINT32_C(0x00000028)));goto L_0027df28;}}
/* 0027df20: b 0x0027df2c */ /* delay 0027df24 */ lw(16,ea(20,(int32_t)UINT32_C(0x00000000)));goto L_0027df2c;
L_0027df28:;
/* 0027df28: lw s0,0x0(s4) */ lw(16,ea(20,(int32_t)UINT32_C(0x00000000)));
L_0027df2c:;
/* 0027df2c: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 0027df30: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027df34: addiu s1,s1,-0x8 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xfffffff8)));
/* 0027df38: move a0,s7 */ set(4,cpu(23));
/* 0027df3c: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027df40: lui at,0x4f */ set(1,sx(UINT32_C(0x004f0000)));
/* 0027df44: addiu at,at,-0x530 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xfffffad0)));
/* 0027df48: addu s0,at,s0 */ set(16,sx((uint32_t)cpu(1)+(uint32_t)cpu(16)));
/* 0027df4c: jal 0x001abc88 */ set(31,UINT64_C(0x0027df54));/* delay 0027df50 */ lw(18,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027df54: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027df58: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027df5c: addiu a0,s6,0x15d */ set(4,sx((uint32_t)cpu(22)+UINT32_C(0x0000015d)));
/* 0027df60: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027df64: addu a0,v1,a0 */ set(4,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0027df68: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027df6c: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027df70: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027df74: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027df78: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027df7c: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027df80: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027df84: jal 0x00279a88 */ set(31,UINT64_C(0x0027df8c));/* delay 0027df88 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));body_00279a88();
/* 0027df8c: lw a2,-0x2f84(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd07c)));
/* 0027df90: slti v0,a2,0x4 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0027df94: bne v0,zero,0x0027e00c */ {int taken=(cpu(2)!=cpu(0));/* delay 0027df98 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));if(taken){goto L_0027e00c;}}
/* 0027df9c: slti v0,a2,0x8 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0027dfa0: beq v0,zero,0x0027dfc0 */ {int taken=(cpu(2)==cpu(0));/* delay 0027dfa4 */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0xfffffffc)));if(taken){goto L_0027dfc0;}}
/* 0027dfa8: lui at,0x3e80 */ set(1,sx(UINT32_C(0x3e800000)));
/* 0027dfac: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027dfb0: mtc1 v0,f0 */ f[0]=(uint32_t)cpu(2);
/* 0027dfb4: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027dfb8: b 0x0027dfc8 */ /* delay 0027dfbc */ f[20]=EE_FPU_MUL_S(f[0],f[1]);goto L_0027dfc8;
L_0027dfc0:;
/* 0027dfc0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027dfc4: mtc1 at,f20 */ f[20]=(uint32_t)cpu(1);
L_0027dfc8:;
/* 0027dfc8: lw a3,0x4(s4) */ lw(7,ea(20,(int32_t)UINT32_C(0x00000004)));
/* 0027dfcc: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027dfd0: addiu v0,v0,-0x530 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027dfd4: lui a2,0x4f */ set(6,sx(UINT32_C(0x004f0000)));
/* 0027dfd8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027dfdc: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0027dfe0: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027dfe4: lw t1,0x128(s8) */ lw(9,ea(30,(int32_t)UINT32_C(0x00000128)));
/* 0027dfe8: addiu a2,a2,0xc */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x0000000c)));
/* 0027dfec: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 0027dff0: move t0,s7 */ set(8,cpu(23));
/* 0027dff4: mov.S f13,f20 */ f[13]=f[20];
/* 0027dff8: li a0,0x15d */ set(4,sx(UINT32_C(0x0000015d)));
/* 0027dffc: jal 0x00279e20 */ set(31,UINT64_C(0x0027e004));/* delay 0027e000 */ set(5,sx(UINT32_C(0x00000001)));body_00279e20();
/* 0027e004: lw a2,-0x2f84(gp) */ lw(6,ea(28,(int32_t)UINT32_C(0xffffd07c)));
/* 0027e008: addiu v1,a2,0x1 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
L_0027e00c:;
/* 0027e00c: slti v0,v1,0xc */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 0027e010: bnel v0,zero,0x0027e024 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027e014 */ sw(ea(28,(int32_t)UINT32_C(0xffffd07c)),(uint32_t)cpu(3));goto L_0027e024;}}
/* 0027e018: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 0027e01c: sw zero,-0x2f84(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd07c)),(uint32_t)cpu(0));
/* 0027e020: sw v0,-0x2f88(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd078)),(uint32_t)cpu(2));
L_0027e024:;
/* 0027e024: b 0x0027e054 */ /* delay 0027e028 */ set(7,byte(ea(28,(int32_t)UINT32_C(0xffffd088))));goto L_0027e054;
L_0027e030:;
/* 0027e030: andi v0,a1,0x8 */ set(2,cpu(5)&UINT32_C(0x00000008));
/* 0027e034: sw zero,-0x2f88(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd078)),(uint32_t)cpu(0));
/* 0027e038: nop  */ 
/* 0027e03c: nop  */ 
/* 0027e040: nop  */ 
/* 0027e044: b 0x0027e024 */ /* delay 0027e048 */ sw(ea(28,(int32_t)UINT32_C(0xffffd01c)),(uint32_t)cpu(2));goto L_0027e024;
L_0027e050:;
/* 0027e050: sw v1,-0x2f84(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd07c)),(uint32_t)cpu(3));
L_0027e054:;
/* 0027e054: beq a3,zero,0x0027e0c0 */ {int taken=(cpu(7)==cpu(0));/* delay 0027e058 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_0027e0c0;}}
/* 0027e05c: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027e060: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027e064: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027e068: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027e06c: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027e070: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027e074: ld s5,0x58(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027e078: ld s6,0x60(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027e07c: ld s7,0x68(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027e080: ld s8,0x70(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027e084: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027e088: lwc1 f30,0xd0(sp) */ f[30]=word(ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 0027e08c: lwc1 f29,0xc8(sp) */ f[29]=word(ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 0027e090: lwc1 f28,0xc0(sp) */ f[28]=word(ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 0027e094: lwc1 f27,0xb8(sp) */ f[27]=word(ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0027e098: lwc1 f26,0xb0(sp) */ f[26]=word(ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0027e09c: lwc1 f25,0xa8(sp) */ f[25]=word(ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0027e0a0: lwc1 f24,0xa0(sp) */ f[24]=word(ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0027e0a4: lwc1 f23,0x98(sp) */ f[23]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0027e0a8: lwc1 f22,0x90(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0027e0ac: lwc1 f21,0x88(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0027e0b0: lwc1 f20,0x80(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0027e0b4: j 0x00279c00 */ /* delay 0027e0b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000e0)));checkReturn(cpu(31),incoming);body_00279c00();return;
L_0027e0c0:;
/* 0027e0c0: lw v1,-0x2fc0(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd040)));
/* 0027e0c4: sltiu v0,v1,0x5 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 0027e0c8: beql v0,zero,0x0027e398 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027e0cc */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd048)));goto L_0027e398;}}
/* 0027e0d0: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 0027e0d4: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 0027e0d8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0027e0dc: lw v1,0x53f0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x000053f0)));
/* 0027e0e0: jr v1 */ {uint64_t target=cpu(3);/* delay 0027e0e4 */ switch((uint32_t)target){case UINT32_C(0x0027e0e8):goto L_0027e0e8;case UINT32_C(0x0027e1f0):goto L_0027e1f0;case UINT32_C(0x0027e260):goto L_0027e260;case UINT32_C(0x0027e390):goto L_0027e390;case UINT32_C(0x0027e394):goto L_0027e394;default:abort();}}
L_0027e0e8:;
/* 0027e0e8: jal 0x00279980 */ set(31,UINT64_C(0x0027e0f0));/* delay 0027e0ec */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e0f0: lwc1 f0,-0x2fbc(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffd044)));
/* 0027e0f4: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e0f8: lui at,0x4160 */ set(1,sx(UINT32_C(0x41600000)));
/* 0027e0fc: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e100: lui at,0x4200 */ set(1,sx(UINT32_C(0x42000000)));
/* 0027e104: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027e108: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027e10c: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027e110: nop  */ 
/* 0027e114: nop  */ 
/* 0027e118: div.S f20,f0,f1 */ f[20]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027e11c: mul.S f0,f20,f2 */ f[0]=EE_FPU_MUL_S(f[20],f[2]);
/* 0027e120: c.le.S f3,f0 */ (void)(EE_FPU_COMPARE_S(f[3],f[0],2)!=0);
/* 0027e124: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027e128: mfc1 t2,f1 */ set(10,sx(f[1]));
/* 0027e12c: bc1f 0x0027e14c */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027e130 */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027e14c;}}
/* 0027e134: sub.S f0,f0,f3 */ f[0]=EE_FPU_SUB_S(f[0],f[3]);
/* 0027e138: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027e13c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027e140: mfc1 t2,f1 */ set(10,sx(f[1]));
/* 0027e144: or t2,t2,v0 */ set(10,cpu(10)|cpu(2));
/* 0027e148: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
L_0027e14c:;
/* 0027e14c: sll t2,t2,0x18 */ set(10,sx((uint32_t)cpu(10)<<24));
/* 0027e150: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e154: or t2,s5,t2 */ set(10,cpu(21)|cpu(10));
/* 0027e158: lw t5,0x34(v0) */ lw(13,ea(2,(int32_t)UINT32_C(0x00000034)));
/* 0027e15c: lwc1 f1,0x74(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000074)));
/* 0027e160: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027e164: lw t4,0x38(v0) */ lw(12,ea(2,(int32_t)UINT32_C(0x00000038)));
/* 0027e168: lwc1 f0,0x70(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000070)));
/* 0027e16c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e170: mtc1 t5,f2 */ f[2]=(uint32_t)cpu(13);
/* 0027e174: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0027e178: lw a0,0x28(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000028)));
/* 0027e17c: mtc1 t4,f3 */ f[3]=(uint32_t)cpu(12);
/* 0027e180: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e184: lw v1,0x2c(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000002c)));
/* 0027e188: sra a2,t5,0x1 */ set(6,sx((uint32_t)((int32_t)cpu(13)>>1)));
/* 0027e18c: sra a3,t4,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(12)>>1)));
/* 0027e190: addu a2,a0,a2 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(6)));
/* 0027e194: move a0,zero */ set(4,cpu(0));
/* 0027e198: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
/* 0027e19c: addu a3,v1,a3 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 0027e1a0: sub.S f1,f1,f3 */ f[1]=EE_FPU_SUB_S(f[1],f[3]);
/* 0027e1a4: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e1a8: move t3,s5 */ set(11,cpu(21));
/* 0027e1ac: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 0027e1b0: mul.S f1,f1,f20 */ f[1]=EE_FPU_MUL_S(f[1],f[20]);
/* 0027e1b4: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e1b8: mfc1 t0,f2 */ set(8,sx(f[2]));
/* 0027e1bc: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0027e1c0: mfc1 t1,f0 */ set(9,sx(f[0]));
/* 0027e1c4: addu t0,t5,t0 */ set(8,sx((uint32_t)cpu(13)+(uint32_t)cpu(8)));
/* 0027e1c8: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e1d0));/* delay 0027e1cc */ set(9,sx((uint32_t)cpu(12)+(uint32_t)cpu(9)));body_0027a7c0();
/* 0027e1d0: lw v0,-0x2fbc(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd044)));
/* 0027e1d4: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e1d8: slti v1,v0,0xe */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 0027e1dc: bnel v1,zero,0x0027e394 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e1e0 */ sw(ea(28,(int32_t)UINT32_C(0xffffd044)),(uint32_t)cpu(2));goto L_0027e394;}}
/* 0027e1e4: b 0x0027e380 */ /* delay 0027e1e8 */ set(2,sx(UINT32_C(0x00000002)));goto L_0027e380;
L_0027e1f0:;
/* 0027e1f0: jal 0x00279980 */ set(31,UINT64_C(0x0027e1f8));/* delay 0027e1f4 */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e1f8: lui t2,0x2000 */ set(10,sx(UINT32_C(0x20000000)));
/* 0027e1fc: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027e200: or t2,s5,t2 */ set(10,cpu(21)|cpu(10));
/* 0027e204: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e208: move a0,zero */ set(4,cpu(0));
/* 0027e20c: lw a2,0x34(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x00000034)));
/* 0027e210: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e214: lw a3,0x38(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000038)));
/* 0027e218: move t3,s5 */ set(11,cpu(21));
/* 0027e21c: lw v1,0x28(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000028)));
/* 0027e220: sra a2,a2,0x1 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>1)));
/* 0027e224: lw t4,0x2c(v0) */ lw(12,ea(2,(int32_t)UINT32_C(0x0000002c)));
/* 0027e228: sra a3,a3,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(7)>>1)));
/* 0027e22c: lw t1,0x74(v0) */ lw(9,ea(2,(int32_t)UINT32_C(0x00000074)));
/* 0027e230: addu a2,v1,a2 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
/* 0027e234: lw t0,0x70(v0) */ lw(8,ea(2,(int32_t)UINT32_C(0x00000070)));
/* 0027e238: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e240));/* delay 0027e23c */ set(7,sx((uint32_t)cpu(12)+(uint32_t)cpu(7)));body_0027a7c0();
/* 0027e240: lw v0,-0x2fbc(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd044)));
/* 0027e244: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e248: slti v1,v0,0x14 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000014));
/* 0027e24c: bnel v1,zero,0x0027e394 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e250 */ sw(ea(28,(int32_t)UINT32_C(0xffffd044)),(uint32_t)cpu(2));goto L_0027e394;}}
/* 0027e254: b 0x0027e380 */ /* delay 0027e258 */ set(2,sx(UINT32_C(0x00000003)));goto L_0027e380;
L_0027e260:;
/* 0027e260: jal 0x00279980 */ set(31,UINT64_C(0x0027e268));/* delay 0027e264 */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e268: lwc1 f0,-0x2fbc(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffd044)));
/* 0027e26c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e270: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 0027e274: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e278: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e27c: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027e280: lui at,0x4200 */ set(1,sx(UINT32_C(0x42000000)));
/* 0027e284: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027e288: nop  */ 
/* 0027e28c: nop  */ 
/* 0027e290: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027e294: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027e298: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e29c: sub.S f20,f2,f0 */ f[20]=EE_FPU_SUB_S(f[2],f[0]);
/* 0027e2a0: mul.S f0,f20,f3 */ f[0]=EE_FPU_MUL_S(f[20],f[3]);
/* 0027e2a4: c.le.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],2)!=0);
/* 0027e2a8: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e2ac: mfc1 t2,f2 */ set(10,sx(f[2]));
/* 0027e2b0: bc1f 0x0027e2d0 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027e2b4 */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027e2d0;}}
/* 0027e2b8: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 0027e2bc: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027e2c0: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027e2c4: mfc1 t2,f1 */ set(10,sx(f[1]));
/* 0027e2c8: or t2,t2,v0 */ set(10,cpu(10)|cpu(2));
/* 0027e2cc: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
L_0027e2d0:;
/* 0027e2d0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e2d4: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027e2d8: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e2dc: sll t2,t2,0x18 */ set(10,sx((uint32_t)cpu(10)<<24));
/* 0027e2e0: lw t5,0x74(v0) */ lw(13,ea(2,(int32_t)UINT32_C(0x00000074)));
/* 0027e2e4: lwc1 f1,0xac(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x000000ac)));
/* 0027e2e8: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027e2ec: lw t4,0x70(v0) */ lw(12,ea(2,(int32_t)UINT32_C(0x00000070)));
/* 0027e2f0: lwc1 f0,0xb0(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x000000b0)));
/* 0027e2f4: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e2f8: mtc1 t5,f2 */ f[2]=(uint32_t)cpu(13);
/* 0027e2fc: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0027e300: lw v1,0x28(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000028)));
/* 0027e304: mtc1 t4,f3 */ f[3]=(uint32_t)cpu(12);
/* 0027e308: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e30c: lw a0,0x2c(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x0000002c)));
/* 0027e310: sub.S f4,f4,f20 */ f[4]=EE_FPU_SUB_S(f[4],f[20]);
/* 0027e314: lw a2,0x34(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x00000034)));
/* 0027e318: lw a3,0x38(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000038)));
/* 0027e31c: or t2,s5,t2 */ set(10,cpu(21)|cpu(10));
/* 0027e320: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
/* 0027e324: sra a2,a2,0x1 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>1)));
/* 0027e328: sub.S f1,f1,f3 */ f[1]=EE_FPU_SUB_S(f[1],f[3]);
/* 0027e32c: sra a3,a3,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(7)>>1)));
/* 0027e330: addu a2,v1,a2 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
/* 0027e334: addu a3,a0,a3 */ set(7,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 0027e338: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e33c: move t3,s5 */ set(11,cpu(21));
/* 0027e340: mul.S f0,f0,f4 */ f[0]=EE_FPU_MUL_S(f[0],f[4]);
/* 0027e344: move a0,zero */ set(4,cpu(0));
/* 0027e348: mul.S f1,f1,f4 */ f[1]=EE_FPU_MUL_S(f[1],f[4]);
/* 0027e34c: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e350: mfc1 t1,f2 */ set(9,sx(f[2]));
/* 0027e354: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0027e358: mfc1 t0,f0 */ set(8,sx(f[0]));
/* 0027e35c: addu t1,t5,t1 */ set(9,sx((uint32_t)cpu(13)+(uint32_t)cpu(9)));
/* 0027e360: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e368));/* delay 0027e364 */ set(8,sx((uint32_t)cpu(12)+(uint32_t)cpu(8)));body_0027a7c0();
/* 0027e368: lw v0,-0x2fbc(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd044)));
/* 0027e36c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e370: slti v1,v0,0x14 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000014));
/* 0027e374: bnel v1,zero,0x0027e394 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e378 */ sw(ea(28,(int32_t)UINT32_C(0xffffd044)),(uint32_t)cpu(2));goto L_0027e394;}}
/* 0027e37c: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
L_0027e380:;
/* 0027e380: sw zero,-0x2fbc(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd044)),(uint32_t)cpu(0));
/* 0027e384: b 0x0027e394 */ /* delay 0027e388 */ sw(ea(28,(int32_t)UINT32_C(0xffffd040)),(uint32_t)cpu(2));goto L_0027e394;
L_0027e390:;
/* 0027e390: sw zero,-0x2fc0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd040)),(uint32_t)cpu(0));
L_0027e394:;
/* 0027e394: lw v1,-0x2fb8(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd048)));
L_0027e398:;
/* 0027e398: sltiu v0,v1,0x6 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0027e39c: beql v0,zero,0x0027e730 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027e3a0 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd054)));goto L_0027e730;}}
/* 0027e3a4: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 0027e3a8: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 0027e3ac: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0027e3b0: lw v1,0x5410(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00005410)));
/* 0027e3b4: jr v1 */ {uint64_t target=cpu(3);/* delay 0027e3b8 */ switch((uint32_t)target){case UINT32_C(0x0027e3c0):goto L_0027e3c0;case UINT32_C(0x0027e480):goto L_0027e480;case UINT32_C(0x0027e4f8):goto L_0027e4f8;case UINT32_C(0x0027e5f8):goto L_0027e5f8;case UINT32_C(0x0027e728):goto L_0027e728;case UINT32_C(0x0027e72c):goto L_0027e72c;default:abort();}}
L_0027e3c0:;
/* 0027e3c0: jal 0x00279980 */ set(31,UINT64_C(0x0027e3c8));/* delay 0027e3c4 */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e3c8: lwc1 f0,-0x2fb4(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffd04c)));
/* 0027e3cc: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e3d0: lui at,0x40c0 */ set(1,sx(UINT32_C(0x40c00000)));
/* 0027e3d4: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e3d8: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027e3dc: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027e3e0: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027e3e4: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027e3e8: nop  */ 
/* 0027e3ec: nop  */ 
/* 0027e3f0: div.S f20,f0,f1 */ f[20]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027e3f4: mul.S f0,f20,f2 */ f[0]=EE_FPU_MUL_S(f[20],f[2]);
/* 0027e3f8: c.le.S f3,f0 */ (void)(EE_FPU_COMPARE_S(f[3],f[0],2)!=0);
/* 0027e3fc: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027e400: mfc1 a0,f1 */ set(4,sx(f[1]));
/* 0027e404: bc1f 0x0027e424 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027e408 */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027e424;}}
/* 0027e40c: sub.S f0,f0,f3 */ f[0]=EE_FPU_SUB_S(f[0],f[3]);
/* 0027e410: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027e414: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027e418: mfc1 a0,f1 */ set(4,sx(f[1]));
/* 0027e41c: or a0,a0,v0 */ set(4,cpu(4)|cpu(2));
/* 0027e420: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
L_0027e424:;
/* 0027e424: lw v1,0x1c(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027e428: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e42c: sll t2,a0,0x18 */ set(10,sx((uint32_t)cpu(4)<<24));
/* 0027e430: lw t0,0x48(v0) */ lw(8,ea(2,(int32_t)UINT32_C(0x00000048)));
/* 0027e434: or t2,v1,t2 */ set(10,cpu(3)|cpu(10));
/* 0027e438: lw t1,0x4c(v0) */ lw(9,ea(2,(int32_t)UINT32_C(0x0000004c)));
/* 0027e43c: move a0,zero */ set(4,cpu(0));
/* 0027e440: lw v1,0x40(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 0027e444: sra t3,t0,0x1 */ set(11,sx((uint32_t)((int32_t)cpu(8)>>1)));
/* 0027e448: lw a2,0x3c(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x0000003c)));
/* 0027e44c: sra a3,t1,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(9)>>1)));
/* 0027e450: addu a3,v1,a3 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 0027e454: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e458: addu a2,a2,t3 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(11)));
/* 0027e45c: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e464));/* delay 0027e460 */ set(11,cpu(21));body_0027a7c0();
/* 0027e464: lw v0,-0x2fb4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd04c)));
/* 0027e468: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e46c: slti v1,v0,0x6 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0027e470: bnel v1,zero,0x0027e72c */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e474 */ sw(ea(28,(int32_t)UINT32_C(0xffffd04c)),(uint32_t)cpu(2));goto L_0027e72c;}}
/* 0027e478: b 0x0027e71c */ /* delay 0027e47c */ set(2,sx(UINT32_C(0x00000002)));goto L_0027e71c;
L_0027e480:;
/* 0027e480: jal 0x00279980 */ set(31,UINT64_C(0x0027e488));/* delay 0027e484 */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e488: lui t2,0x8000 */ set(10,sx(UINT32_C(0x80000000)));
/* 0027e48c: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027e490: lw a0,0x1c(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027e494: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e498: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e49c: lw t0,0x48(v0) */ lw(8,ea(2,(int32_t)UINT32_C(0x00000048)));
/* 0027e4a0: or t2,a0,t2 */ set(10,cpu(4)|cpu(10));
/* 0027e4a4: lw t1,0x4c(v0) */ lw(9,ea(2,(int32_t)UINT32_C(0x0000004c)));
/* 0027e4a8: move t3,s5 */ set(11,cpu(21));
/* 0027e4ac: lw v1,0x40(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 0027e4b0: sra t4,t0,0x1 */ set(12,sx((uint32_t)((int32_t)cpu(8)>>1)));
/* 0027e4b4: lw a2,0x3c(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x0000003c)));
/* 0027e4b8: sra a3,t1,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(9)>>1)));
/* 0027e4bc: addu a3,v1,a3 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 0027e4c0: move a0,zero */ set(4,cpu(0));
/* 0027e4c4: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e4cc));/* delay 0027e4c8 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(12)));body_0027a7c0();
/* 0027e4cc: lw v0,-0x2fb4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd04c)));
/* 0027e4d0: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e4d4: slti v1,v0,0x6 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0027e4d8: bnel v1,zero,0x0027e72c */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e4dc */ sw(ea(28,(int32_t)UINT32_C(0xffffd04c)),(uint32_t)cpu(2));goto L_0027e72c;}}
/* 0027e4e0: lwc1 f0,-0x5bac(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa454)));
/* 0027e4e4: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 0027e4e8: sw v0,-0x2fb8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd048)),(uint32_t)cpu(2));
/* 0027e4ec: swc1 f0,-0x2fb0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd050)),f[0]);
/* 0027e4f0: b 0x0027e72c */ /* delay 0027e4f4 */ sw(ea(28,(int32_t)UINT32_C(0xffffd04c)),(uint32_t)cpu(0));goto L_0027e72c;
L_0027e4f8:;
/* 0027e4f8: jal 0x00279980 */ set(31,UINT64_C(0x0027e500));/* delay 0027e4fc */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e500: lwc1 f3,-0x2fb4(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffd04c)));
/* 0027e504: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e508: lwc1 f2,-0x2fb0(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffd050)));
/* 0027e50c: lwc1 f0,-0x5ba8(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffa458)));
/* 0027e510: lui at,0x4120 */ set(1,sx(UINT32_C(0x41200000)));
/* 0027e514: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e518: mul.S f0,f2,f0 */ f[0]=EE_FPU_MUL_S(f[2],f[0]);
/* 0027e51c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e520: mtc1 at,f6 */ f[6]=(uint32_t)cpu(1);
/* 0027e524: nop  */ 
/* 0027e528: nop  */ 
/* 0027e52c: div.S f20,f3,f1 */ f[20]=EE_FPU_DIV_S(f[3],f[1]);
/* 0027e530: c.lt.S f6,f0 */ (void)(EE_FPU_COMPARE_S(f[6],f[0],1)!=0);
/* 0027e534: bc1f 0x0027e548 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027e538 */ f[4]=EE_FPU_MUL_S(f[20],f[2]);if(taken){goto L_0027e548;}}
/* 0027e53c: b 0x0027e54c */ /* delay 0027e540 */ sw(ea(28,(int32_t)UINT32_C(0xffffd050)),f[6]);goto L_0027e54c;
L_0027e548:;
/* 0027e548: swc1 f0,-0x2fb0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd050)),f[0]);
L_0027e54c:;
/* 0027e54c: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027e550: lw a2,0x1c(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027e554: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e558: lui t2,0x8000 */ set(10,sx(UINT32_C(0x80000000)));
/* 0027e55c: lw t5,0x48(v0) */ lw(13,ea(2,(int32_t)UINT32_C(0x00000048)));
/* 0027e560: lwc1 f1,0x88(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000088)));
/* 0027e564: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027e568: lw t4,0x4c(v0) */ lw(12,ea(2,(int32_t)UINT32_C(0x0000004c)));
/* 0027e56c: lwc1 f0,0x84(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000084)));
/* 0027e570: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e574: mtc1 t5,f2 */ f[2]=(uint32_t)cpu(13);
/* 0027e578: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0027e57c: lw a0,0x3c(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x0000003c)));
/* 0027e580: mtc1 t4,f3 */ f[3]=(uint32_t)cpu(12);
/* 0027e584: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e588: lw v1,0x40(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 0027e58c: or t2,a2,t2 */ set(10,cpu(6)|cpu(10));
/* 0027e590: sra a2,t5,0x1 */ set(6,sx((uint32_t)((int32_t)cpu(13)>>1)));
/* 0027e594: sra a3,t4,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(12)>>1)));
/* 0027e598: addu a2,a0,a2 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(6)));
/* 0027e59c: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
/* 0027e5a0: addu a3,v1,a3 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 0027e5a4: sub.S f1,f1,f3 */ f[1]=EE_FPU_SUB_S(f[1],f[3]);
/* 0027e5a8: move a0,zero */ set(4,cpu(0));
/* 0027e5ac: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e5b0: move t3,s5 */ set(11,cpu(21));
/* 0027e5b4: mul.S f0,f0,f4 */ f[0]=EE_FPU_MUL_S(f[0],f[4]);
/* 0027e5b8: mul.S f1,f1,f4 */ f[1]=EE_FPU_MUL_S(f[1],f[4]);
/* 0027e5bc: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e5c0: mfc1 t0,f2 */ set(8,sx(f[2]));
/* 0027e5c4: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0027e5c8: mfc1 t1,f0 */ set(9,sx(f[0]));
/* 0027e5cc: addu t0,t5,t0 */ set(8,sx((uint32_t)cpu(13)+(uint32_t)cpu(8)));
/* 0027e5d0: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e5d8));/* delay 0027e5d4 */ set(9,sx((uint32_t)cpu(12)+(uint32_t)cpu(9)));body_0027a7c0();
/* 0027e5d8: lw v0,-0x2fb4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd04c)));
/* 0027e5dc: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e5e0: slti v1,v0,0xa */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 0027e5e4: bnel v1,zero,0x0027e72c */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e5e8 */ sw(ea(28,(int32_t)UINT32_C(0xffffd04c)),(uint32_t)cpu(2));goto L_0027e72c;}}
/* 0027e5ec: b 0x0027e71c */ /* delay 0027e5f0 */ set(2,sx(UINT32_C(0x00000004)));goto L_0027e71c;
L_0027e5f8:;
/* 0027e5f8: jal 0x00279980 */ set(31,UINT64_C(0x0027e600));/* delay 0027e5fc */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e600: lwc1 f0,-0x2fb4(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffd04c)));
/* 0027e604: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e608: lui at,0x4204 */ set(1,sx(UINT32_C(0x42040000)));
/* 0027e60c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e610: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e614: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027e618: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027e61c: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027e620: nop  */ 
/* 0027e624: nop  */ 
/* 0027e628: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027e62c: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027e630: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e634: sub.S f20,f2,f0 */ f[20]=EE_FPU_SUB_S(f[2],f[0]);
/* 0027e638: mul.S f0,f20,f3 */ f[0]=EE_FPU_MUL_S(f[20],f[3]);
/* 0027e63c: c.le.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],2)!=0);
/* 0027e640: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e644: mfc1 t2,f2 */ set(10,sx(f[2]));
/* 0027e648: bc1f 0x0027e668 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027e64c */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027e668;}}
/* 0027e650: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 0027e654: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027e658: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027e65c: mfc1 t2,f1 */ set(10,sx(f[1]));
/* 0027e660: or t2,t2,v0 */ set(10,cpu(10)|cpu(2));
/* 0027e664: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
L_0027e668:;
/* 0027e668: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e66c: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027e670: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e674: sll t2,t2,0x18 */ set(10,sx((uint32_t)cpu(10)<<24));
/* 0027e678: lw t5,0x88(v0) */ lw(13,ea(2,(int32_t)UINT32_C(0x00000088)));
/* 0027e67c: lwc1 f1,0xc0(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x000000c0)));
/* 0027e680: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027e684: lw t4,0x84(v0) */ lw(12,ea(2,(int32_t)UINT32_C(0x00000084)));
/* 0027e688: lwc1 f0,0xc4(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x000000c4)));
/* 0027e68c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e690: mtc1 t5,f2 */ f[2]=(uint32_t)cpu(13);
/* 0027e694: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0027e698: lw a2,0x48(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x00000048)));
/* 0027e69c: mtc1 t4,f3 */ f[3]=(uint32_t)cpu(12);
/* 0027e6a0: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e6a4: lw v1,0x3c(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000003c)));
/* 0027e6a8: sub.S f4,f4,f20 */ f[4]=EE_FPU_SUB_S(f[4],f[20]);
/* 0027e6ac: lw a0,0x40(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 0027e6b0: lw a3,0x4c(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x0000004c)));
/* 0027e6b4: sra a2,a2,0x1 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>1)));
/* 0027e6b8: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
/* 0027e6bc: lw v0,0x1c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000001c)));
/* 0027e6c0: sub.S f1,f1,f3 */ f[1]=EE_FPU_SUB_S(f[1],f[3]);
/* 0027e6c4: addu a2,v1,a2 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
/* 0027e6c8: or t2,v0,t2 */ set(10,cpu(2)|cpu(10));
/* 0027e6cc: sra a3,a3,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(7)>>1)));
/* 0027e6d0: addu a3,a0,a3 */ set(7,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 0027e6d4: move a0,zero */ set(4,cpu(0));
/* 0027e6d8: mul.S f0,f0,f4 */ f[0]=EE_FPU_MUL_S(f[0],f[4]);
/* 0027e6dc: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e6e0: mul.S f1,f1,f4 */ f[1]=EE_FPU_MUL_S(f[1],f[4]);
/* 0027e6e4: move t3,s5 */ set(11,cpu(21));
/* 0027e6e8: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e6ec: mfc1 t1,f2 */ set(9,sx(f[2]));
/* 0027e6f0: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0027e6f4: mfc1 t0,f0 */ set(8,sx(f[0]));
/* 0027e6f8: addu t1,t5,t1 */ set(9,sx((uint32_t)cpu(13)+(uint32_t)cpu(9)));
/* 0027e6fc: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e704));/* delay 0027e700 */ set(8,sx((uint32_t)cpu(12)+(uint32_t)cpu(8)));body_0027a7c0();
/* 0027e704: lw v0,-0x2fb4(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd04c)));
/* 0027e708: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e70c: slti v1,v0,0x21 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000021));
/* 0027e710: bnel v1,zero,0x0027e72c */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e714 */ sw(ea(28,(int32_t)UINT32_C(0xffffd04c)),(uint32_t)cpu(2));goto L_0027e72c;}}
/* 0027e718: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
L_0027e71c:;
/* 0027e71c: sw zero,-0x2fb4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd04c)),(uint32_t)cpu(0));
/* 0027e720: b 0x0027e72c */ /* delay 0027e724 */ sw(ea(28,(int32_t)UINT32_C(0xffffd048)),(uint32_t)cpu(2));goto L_0027e72c;
L_0027e728:;
/* 0027e728: sw zero,-0x2fb8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd048)),(uint32_t)cpu(0));
L_0027e72c:;
/* 0027e72c: lw v1,-0x2fac(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd054)));
L_0027e730:;
/* 0027e730: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0027e734: beq v1,v0,0x0027e760 */ {int taken=(cpu(3)==cpu(2));/* delay 0027e738 */ if(taken){goto L_0027e760;}}
/* 0027e73c: beq v1,zero,0x0027e9b0 */ {int taken=(cpu(3)==cpu(0));/* delay 0027e740 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_0027e9b0;}}
/* 0027e744: beq v1,v0,0x0027e888 */ {int taken=(cpu(3)==cpu(2));/* delay 0027e748 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_0027e888;}}
/* 0027e74c: beql v1,v0,0x0027e9b0 */ {int taken=(cpu(3)==cpu(2));if(taken){/* delay 0027e750 */ sw(ea(28,(int32_t)UINT32_C(0xffffd054)),(uint32_t)cpu(0));goto L_0027e9b0;}}
/* 0027e754: b 0x0027e9b0 */ /* delay 0027e758 */ goto L_0027e9b0;
L_0027e760:;
/* 0027e760: jal 0x00279980 */ set(31,UINT64_C(0x0027e768));/* delay 0027e764 */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e768: lwc1 f3,-0x2fa8(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffd058)));
/* 0027e76c: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e770: lwc1 f2,-0x2fa4(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffd05c)));
/* 0027e774: lwc1 f1,-0x5ba4(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa45c)));
/* 0027e778: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e77c: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027e780: mul.S f2,f2,f1 */ f[2]=EE_FPU_MUL_S(f[2],f[1]);
/* 0027e784: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 0027e788: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027e78c: nop  */ 
/* 0027e790: nop  */ 
/* 0027e794: div.S f20,f3,f0 */ f[20]=EE_FPU_DIV_S(f[3],f[0]);
/* 0027e798: c.lt.S f4,f2 */ (void)(EE_FPU_COMPARE_S(f[4],f[2],1)!=0);
/* 0027e79c: bc1fl 0x0027e7a8 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);if(taken){/* delay 0027e7a0 */ sw(ea(28,(int32_t)UINT32_C(0xffffd05c)),f[2]);goto L_0027e7a8;}}
/* 0027e7a4: swc1 f4,-0x2fa4(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd05c)),f[4]);
L_0027e7a8:;
/* 0027e7a8: lui at,0x4280 */ set(1,sx(UINT32_C(0x42800000)));
/* 0027e7ac: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027e7b0: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027e7b4: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e7b8: mul.S f0,f20,f0 */ f[0]=EE_FPU_MUL_S(f[20],f[0]);
/* 0027e7bc: c.le.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],2)!=0);
/* 0027e7c0: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e7c4: mfc1 t2,f2 */ set(10,sx(f[2]));
/* 0027e7c8: bc1f 0x0027e7e8 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027e7cc */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027e7e8;}}
/* 0027e7d0: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 0027e7d4: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027e7d8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027e7dc: mfc1 t2,f1 */ set(10,sx(f[1]));
/* 0027e7e0: or t2,t2,v0 */ set(10,cpu(10)|cpu(2));
/* 0027e7e4: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
L_0027e7e8:;
/* 0027e7e8: sll t2,t2,0x18 */ set(10,sx((uint32_t)cpu(10)<<24));
/* 0027e7ec: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e7f0: or t2,s5,t2 */ set(10,cpu(21)|cpu(10));
/* 0027e7f4: lw t5,0x5c(v0) */ lw(13,ea(2,(int32_t)UINT32_C(0x0000005c)));
/* 0027e7f8: lwc1 f1,0x9c(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x0000009c)));
/* 0027e7fc: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027e800: lw t4,0x60(v0) */ lw(12,ea(2,(int32_t)UINT32_C(0x00000060)));
/* 0027e804: lwc1 f0,0x98(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x00000098)));
/* 0027e808: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e80c: mtc1 t5,f2 */ f[2]=(uint32_t)cpu(13);
/* 0027e810: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0027e814: lw a0,0x50(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000050)));
/* 0027e818: mtc1 t4,f3 */ f[3]=(uint32_t)cpu(12);
/* 0027e81c: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e820: lw v1,0x54(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000054)));
/* 0027e824: sra a2,t5,0x1 */ set(6,sx((uint32_t)((int32_t)cpu(13)>>1)));
/* 0027e828: sra a3,t4,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(12)>>1)));
/* 0027e82c: addu a2,a0,a2 */ set(6,sx((uint32_t)cpu(4)+(uint32_t)cpu(6)));
/* 0027e830: move a0,zero */ set(4,cpu(0));
/* 0027e834: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
/* 0027e838: addu a3,v1,a3 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 0027e83c: sub.S f1,f1,f3 */ f[1]=EE_FPU_SUB_S(f[1],f[3]);
/* 0027e840: move t3,s5 */ set(11,cpu(21));
/* 0027e844: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e848: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 0027e84c: mul.S f1,f1,f20 */ f[1]=EE_FPU_MUL_S(f[1],f[20]);
/* 0027e850: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e854: mfc1 t0,f2 */ set(8,sx(f[2]));
/* 0027e858: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0027e85c: mfc1 t1,f0 */ set(9,sx(f[0]));
/* 0027e860: addu t0,t5,t0 */ set(8,sx((uint32_t)cpu(13)+(uint32_t)cpu(8)));
/* 0027e864: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e86c));/* delay 0027e868 */ set(9,sx((uint32_t)cpu(12)+(uint32_t)cpu(9)));body_0027a7c0();
/* 0027e86c: lw v0,-0x2fa8(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd058)));
/* 0027e870: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e874: slti v1,v0,0x14 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000014));
/* 0027e878: bnel v1,zero,0x0027e9b0 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e87c */ sw(ea(28,(int32_t)UINT32_C(0xffffd058)),(uint32_t)cpu(2));goto L_0027e9b0;}}
/* 0027e880: b 0x0027e9a8 */ /* delay 0027e884 */ set(2,sx(UINT32_C(0x00000002)));goto L_0027e9a8;
L_0027e888:;
/* 0027e888: jal 0x00279980 */ set(31,UINT64_C(0x0027e890));/* delay 0027e88c */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027e890: lwc1 f0,-0x2fa8(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffd058)));
/* 0027e894: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e898: lui at,0x41a0 */ set(1,sx(UINT32_C(0x41a00000)));
/* 0027e89c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e8a0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e8a4: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027e8a8: lui at,0x4280 */ set(1,sx(UINT32_C(0x42800000)));
/* 0027e8ac: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027e8b0: nop  */ 
/* 0027e8b4: nop  */ 
/* 0027e8b8: div.S f0,f0,f1 */ f[0]=EE_FPU_DIV_S(f[0],f[1]);
/* 0027e8bc: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027e8c0: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e8c4: sub.S f20,f2,f0 */ f[20]=EE_FPU_SUB_S(f[2],f[0]);
/* 0027e8c8: mul.S f0,f20,f3 */ f[0]=EE_FPU_MUL_S(f[20],f[3]);
/* 0027e8cc: c.le.S f1,f0 */ (void)(EE_FPU_COMPARE_S(f[1],f[0],2)!=0);
/* 0027e8d0: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e8d4: mfc1 t2,f2 */ set(10,sx(f[2]));
/* 0027e8d8: bc1f 0x0027e8f8 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027e8dc */ set(2,sx(UINT32_C(0x004f0000)));if(taken){goto L_0027e8f8;}}
/* 0027e8e0: sub.S f0,f0,f1 */ f[0]=EE_FPU_SUB_S(f[0],f[1]);
/* 0027e8e4: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027e8e8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027e8ec: mfc1 t2,f1 */ set(10,sx(f[1]));
/* 0027e8f0: or t2,t2,v0 */ set(10,cpu(10)|cpu(2));
/* 0027e8f4: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
L_0027e8f8:;
/* 0027e8f8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e8fc: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027e900: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027e904: sll t2,t2,0x18 */ set(10,sx((uint32_t)cpu(10)<<24));
/* 0027e908: lw t5,0x9c(v0) */ lw(13,ea(2,(int32_t)UINT32_C(0x0000009c)));
/* 0027e90c: lwc1 f1,0xd4(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x000000d4)));
/* 0027e910: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027e914: lw t4,0x98(v0) */ lw(12,ea(2,(int32_t)UINT32_C(0x00000098)));
/* 0027e918: lwc1 f0,0xd8(v0) */ f[0]=word(ea(2,(int32_t)UINT32_C(0x000000d8)));
/* 0027e91c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027e920: mtc1 t5,f2 */ f[2]=(uint32_t)cpu(13);
/* 0027e924: cvt.s.W f2,f2 */ f[2]=EE_FPU_CVT_S_W(f[2]);
/* 0027e928: lw v1,0x50(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000050)));
/* 0027e92c: mtc1 t4,f3 */ f[3]=(uint32_t)cpu(12);
/* 0027e930: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e934: lw a0,0x54(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000054)));
/* 0027e938: sub.S f4,f4,f20 */ f[4]=EE_FPU_SUB_S(f[4],f[20]);
/* 0027e93c: lw a2,0x5c(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x0000005c)));
/* 0027e940: lw a3,0x60(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000060)));
/* 0027e944: or t2,s5,t2 */ set(10,cpu(21)|cpu(10));
/* 0027e948: sub.S f0,f0,f2 */ f[0]=EE_FPU_SUB_S(f[0],f[2]);
/* 0027e94c: sra a2,a2,0x1 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>1)));
/* 0027e950: sub.S f1,f1,f3 */ f[1]=EE_FPU_SUB_S(f[1],f[3]);
/* 0027e954: sra a3,a3,0x1 */ set(7,sx((uint32_t)((int32_t)cpu(7)>>1)));
/* 0027e958: addu a2,v1,a2 */ set(6,sx((uint32_t)cpu(3)+(uint32_t)cpu(6)));
/* 0027e95c: addu a3,a0,a3 */ set(7,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));
/* 0027e960: move t3,s5 */ set(11,cpu(21));
/* 0027e964: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027e968: mul.S f0,f0,f4 */ f[0]=EE_FPU_MUL_S(f[0],f[4]);
/* 0027e96c: move a0,zero */ set(4,cpu(0));
/* 0027e970: mul.S f1,f1,f4 */ f[1]=EE_FPU_MUL_S(f[1],f[4]);
/* 0027e974: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027e978: mfc1 t1,f2 */ set(9,sx(f[2]));
/* 0027e97c: cvt.w.S f0,f1 */ f[0]=EE_FPU_CVT_W_S(f[1]);
/* 0027e980: mfc1 t0,f0 */ set(8,sx(f[0]));
/* 0027e984: addu t1,t5,t1 */ set(9,sx((uint32_t)cpu(13)+(uint32_t)cpu(9)));
/* 0027e988: jal 0x0027a7c0 */ set(31,UINT64_C(0x0027e990));/* delay 0027e98c */ set(8,sx((uint32_t)cpu(12)+(uint32_t)cpu(8)));body_0027a7c0();
/* 0027e990: lw v0,-0x2fa8(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd058)));
/* 0027e994: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027e998: slti v1,v0,0x14 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000014));
/* 0027e99c: bnel v1,zero,0x0027e9b0 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027e9a0 */ sw(ea(28,(int32_t)UINT32_C(0xffffd058)),(uint32_t)cpu(2));goto L_0027e9b0;}}
/* 0027e9a4: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
L_0027e9a8:;
/* 0027e9a8: sw zero,-0x2fa8(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd058)),(uint32_t)cpu(0));
/* 0027e9ac: sw v0,-0x2fac(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd054)),(uint32_t)cpu(2));
L_0027e9b0:;
/* 0027e9b0: jal 0x00279980 */ set(31,UINT64_C(0x0027e9b8));/* delay 0027e9b4 */ set(4,cpu(0));body_00279980();
/* 0027e9b8: lw v1,-0x2f9c(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd064)));
/* 0027e9bc: sltiu v0,v1,0x5 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));
/* 0027e9c0: beql v0,zero,0x0027ee0c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027e9c4 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd070)));goto L_0027ee0c;}}
/* 0027e9c8: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 0027e9cc: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 0027e9d0: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0027e9d4: lw v1,0x5430(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00005430)));
/* 0027e9d8: jr v1 */ {uint64_t target=cpu(3);/* delay 0027e9dc */ switch((uint32_t)target){case UINT32_C(0x0027e9e0):goto L_0027e9e0;case UINT32_C(0x0027eb30):goto L_0027eb30;case UINT32_C(0x0027ec18):goto L_0027ec18;case UINT32_C(0x0027ed30):goto L_0027ed30;case UINT32_C(0x0027ee08):goto L_0027ee08;default:abort();}}
L_0027e9e0:;
/* 0027e9e0: lwc1 f3,-0x2fa0(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffd060)));
/* 0027e9e4: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027e9e8: lui at,0x40c0 */ set(1,sx(UINT32_C(0x40c00000)));
/* 0027e9ec: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027e9f0: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027e9f4: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027e9f8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027e9fc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027ea00: lui at,0x41b0 */ set(1,sx(UINT32_C(0x41b00000)));
/* 0027ea04: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027ea08: nop  */ 
/* 0027ea0c: nop  */ 
/* 0027ea10: div.S f20,f3,f1 */ f[20]=EE_FPU_DIV_S(f[3],f[1]);
/* 0027ea14: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027ea18: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027ea1c: mul.S f6,f20,f2 */ f[6]=EE_FPU_MUL_S(f[20],f[2]);
/* 0027ea20: sub.S f0,f0,f20 */ f[0]=EE_FPU_SUB_S(f[0],f[20]);
/* 0027ea24: c.le.S f1,f6 */ (void)(EE_FPU_COMPARE_S(f[1],f[6],2)!=0);
/* 0027ea28: mul.S f0,f0,f4 */ f[0]=EE_FPU_MUL_S(f[0],f[4]);
/* 0027ea2c: cvt.w.S f2,f6 */ f[2]=EE_FPU_CVT_W_S(f[6]);
/* 0027ea30: mfc1 v1,f2 */ set(3,sx(f[2]));
/* 0027ea34: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027ea38: mfc1 s6,f2 */ set(22,sx(f[2]));
/* 0027ea3c: bc1f 0x0027ea5c */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027ea40 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));if(taken){goto L_0027ea5c;}}
/* 0027ea44: sub.S f0,f6,f1 */ f[0]=EE_FPU_SUB_S(f[6],f[1]);
/* 0027ea48: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027ea4c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027ea50: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027ea54: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 0027ea58: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
L_0027ea5c:;
/* 0027ea5c: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 0027ea60: lui s2,0x4f */ set(18,sx(UINT32_C(0x004f0000)));
/* 0027ea64: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027ea68: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0027ea6c: lw a3,0x0(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027ea70: lui v0,0x80 */ set(2,sx(UINT32_C(0x00800000)));
/* 0027ea74: lw t1,0x12c(s8) */ lw(9,ea(30,(int32_t)UINT32_C(0x0000012c)));
/* 0027ea78: addiu s1,s1,0xa0 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x000000a0)));
/* 0027ea7c: addiu s2,s2,-0x530 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xfffffad0)));
/* 0027ea80: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027ea84: lui t0,0x8080 */ set(8,sx(UINT32_C(0x80800000)));
/* 0027ea88: move a2,s1 */ set(6,cpu(17));
/* 0027ea8c: addu a3,a3,s2 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(18)));
/* 0027ea90: mov.S f13,f20 */ f[13]=f[20];
/* 0027ea94: sll v1,v1,0x18 */ set(3,sx((uint32_t)cpu(3)<<24));
/* 0027ea98: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027ea9c: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027eaa0: move a0,zero */ set(4,cpu(0));
/* 0027eaa4: li a1,0x57 */ set(5,sx(UINT32_C(0x00000057)));
/* 0027eaa8: jal 0x00279e20 */ set(31,UINT64_C(0x0027eab0));/* delay 0027eaac */ set(23,cpu(3)|cpu(2));body_00279e20();
/* 0027eab0: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027eab4: addiu s1,s1,0x14 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));
/* 0027eab8: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027eabc: move a0,s7 */ set(4,cpu(23));
/* 0027eac0: jal 0x001abc88 */ set(31,UINT64_C(0x0027eac8));/* delay 0027eac4 */ lw(16,ea(3,(int32_t)UINT32_C(0x00000004)));body_001abc88();
/* 0027eac8: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027eacc: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027ead0: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027ead4: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 0027ead8: li a0,0x57 */ set(4,sx(UINT32_C(0x00000057)));
/* 0027eadc: subu v1,a0,s6 */ set(3,sx((uint32_t)cpu(4)-(uint32_t)cpu(22)));
/* 0027eae0: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027eae4: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027eae8: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 0027eaec: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027eaf0: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027eaf4: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027eaf8: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027eafc: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027eb00: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027eb04: jal 0x00279a88 */ set(31,UINT64_C(0x0027eb0c));/* delay 0027eb08 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_00279a88();
/* 0027eb0c: lw v0,-0x2fa0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd060)));
/* 0027eb10: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027eb14: slti v1,v0,0x6 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000006));
/* 0027eb18: bnel v1,zero,0x0027ee08 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027eb1c */ sw(ea(28,(int32_t)UINT32_C(0xffffd060)),(uint32_t)cpu(2));goto L_0027ee08;}}
/* 0027eb20: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0027eb24: sw zero,-0x2fa0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd060)),(uint32_t)cpu(0));
/* 0027eb28: b 0x0027ee08 */ /* delay 0027eb2c */ sw(ea(28,(int32_t)UINT32_C(0xffffd064)),(uint32_t)cpu(2));goto L_0027ee08;
L_0027eb30:;
/* 0027eb30: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027eb34: lui s3,0x4f */ set(19,sx(UINT32_C(0x004f0000)));
/* 0027eb38: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027eb3c: lui s0,0x4f */ set(16,sx(UINT32_C(0x004f0000)));
/* 0027eb40: lw s1,0x0(v1) */ lw(17,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0027eb44: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027eb48: addiu s0,s0,0xa0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000000a0)));
/* 0027eb4c: addiu s3,s3,-0x530 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xfffffad0)));
/* 0027eb50: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027eb54: sll s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)<<4));
/* 0027eb58: addu s1,s1,s3 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));
/* 0027eb5c: jal 0x001abc88 */ set(31,UINT64_C(0x0027eb64));/* delay 0027eb60 */ lw(20,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027eb64: lw t3,0xc(s1) */ lw(11,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027eb68: lw a1,0x4(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027eb6c: addiu s2,s0,0x14 */ set(18,sx((uint32_t)cpu(16)+UINT32_C(0x00000014)));
/* 0027eb70: lw a2,0xc(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027eb74: lw a3,0x10(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0027eb78: addiu a1,a1,0x57 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000057)));
/* 0027eb7c: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027eb80: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027eb84: lw t1,0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027eb88: lw t2,0x8(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 0027eb8c: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027eb90: jal 0x00279a88 */ set(31,UINT64_C(0x0027eb98));/* delay 0027eb94 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));body_00279a88();
/* 0027eb98: lw a0,0x14(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027eb9c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027eba0: lw s0,0x4(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 0027eba4: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027eba8: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027ebac: jal 0x001abc88 */ set(31,UINT64_C(0x0027ebb4));/* delay 0027ebb0 */ set(16,sx((uint32_t)cpu(16)<<4));body_001abc88();
/* 0027ebb4: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 0027ebb8: lw a1,0x4(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0027ebbc: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0027ebc0: lw a3,0x10(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 0027ebc4: addiu a1,a1,0x57 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000057)));
/* 0027ebc8: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027ebcc: lw a2,0xc(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 0027ebd0: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027ebd4: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027ebd8: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027ebdc: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027ebe0: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027ebe4: jal 0x00279a88 */ set(31,UINT64_C(0x0027ebec));/* delay 0027ebe8 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_00279a88();
/* 0027ebec: lw a0,-0x2f90(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd070)));
/* 0027ebf0: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 0027ebf4: bne a0,v0,0x0027ee10 */ {int taken=(cpu(4)!=cpu(2));/* delay 0027ebf8 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000007));if(taken){goto L_0027ee10;}}
/* 0027ebfc: lui v0,0x8080 */ set(2,sx(UINT32_C(0x80800000)));
/* 0027ec00: li v1,0x2 */ set(3,sx(UINT32_C(0x00000002)));
/* 0027ec04: ori v0,v0,0x8080 */ set(2,cpu(2)|UINT32_C(0x00008080));
/* 0027ec08: sw v1,-0x2f9c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd064)),(uint32_t)cpu(3));
/* 0027ec0c: sw v0,-0x2f98(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd068)),(uint32_t)cpu(2));
/* 0027ec10: b 0x0027ee0c */ /* delay 0027ec14 */ sw(ea(28,(int32_t)UINT32_C(0xffffd060)),(uint32_t)cpu(0));goto L_0027ee0c;
L_0027ec18:;
/* 0027ec18: lwc1 f0,-0x2fa0(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffd060)));
/* 0027ec1c: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027ec20: lui at,0x4190 */ set(1,sx(UINT32_C(0x41900000)));
/* 0027ec24: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 0027ec28: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027ec2c: lui a1,0x80a0 */ set(5,sx(UINT32_C(0x80a00000)));
/* 0027ec30: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027ec34: ori a1,a1,0xa0a0 */ set(5,cpu(5)|UINT32_C(0x0000a0a0));
/* 0027ec38: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 0027ec3c: lui s2,0x4f */ set(18,sx(UINT32_C(0x004f0000)));
/* 0027ec40: nop  */ 
/* 0027ec44: nop  */ 
/* 0027ec48: div.S f12,f0,f12 */ f[12]=EE_FPU_DIV_S(f[0],f[12]);
/* 0027ec4c: addiu s1,s1,0xa0 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x000000a0)));
/* 0027ec50: addiu s2,s2,-0x530 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xfffffad0)));
/* 0027ec54: jal 0x001abbd0 */ set(31,UINT64_C(0x0027ec5c));/* delay 0027ec58 */ set(19,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));body_001abbd0();
/* 0027ec5c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027ec60: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027ec64: move a0,v0 */ set(4,cpu(2));
/* 0027ec68: sw v0,-0x2f98(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd068)),(uint32_t)cpu(2));
/* 0027ec6c: lw s4,0x12c(s8) */ lw(20,ea(30,(int32_t)UINT32_C(0x0000012c)));
/* 0027ec70: jal 0x001abc88 */ set(31,UINT64_C(0x0027ec78));/* delay 0027ec74 */ lw(16,ea(3,(int32_t)UINT32_C(0x00000000)));body_001abc88();
/* 0027ec78: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027ec7c: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027ec80: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027ec84: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 0027ec88: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027ec8c: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027ec90: addiu a1,a1,0x57 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000057)));
/* 0027ec94: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027ec98: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027ec9c: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027eca0: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027eca4: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027eca8: jal 0x00279a88 */ set(31,UINT64_C(0x0027ecb0));/* delay 0027ecac */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));body_00279a88();
/* 0027ecb0: lw a0,0x14(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027ecb4: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027ecb8: lw s0,0x4(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 0027ecbc: lw a0,-0x2f98(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd068)));
/* 0027ecc0: jal 0x001abc88 */ set(31,UINT64_C(0x0027ecc8));/* delay 0027ecc4 */ set(16,sx((uint32_t)cpu(16)<<4));body_001abc88();
/* 0027ecc8: lw a0,0x0(s3) */ lw(4,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 0027eccc: addu s0,s0,s2 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(18)));
/* 0027ecd0: lw a1,0x4(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000004)));
/* 0027ecd4: lw a3,0x10(s3) */ lw(7,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 0027ecd8: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027ecdc: addiu a1,a1,0x57 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000057)));
/* 0027ece0: lw a2,0xc(s3) */ lw(6,ea(19,(int32_t)UINT32_C(0x0000000c)));
/* 0027ece4: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027ece8: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027ecec: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027ecf0: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027ecf4: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027ecf8: jal 0x00279a88 */ set(31,UINT64_C(0x0027ed00));/* delay 0027ecfc */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_00279a88();
/* 0027ed00: lw v0,-0x2fa0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd060)));
/* 0027ed04: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0027ed08: slti v1,v0,0x12 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000012));
/* 0027ed0c: bnel v1,zero,0x0027ee08 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 0027ed10 */ sw(ea(28,(int32_t)UINT32_C(0xffffd060)),(uint32_t)cpu(2));goto L_0027ee08;}}
/* 0027ed14: lui v0,0x80a0 */ set(2,sx(UINT32_C(0x80a00000)));
/* 0027ed18: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 0027ed1c: ori v0,v0,0xa0a0 */ set(2,cpu(2)|UINT32_C(0x0000a0a0));
/* 0027ed20: sw v1,-0x2f9c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd064)),(uint32_t)cpu(3));
/* 0027ed24: sw v0,-0x2f98(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd068)),(uint32_t)cpu(2));
/* 0027ed28: b 0x0027ee08 */ /* delay 0027ed2c */ sw(ea(28,(int32_t)UINT32_C(0xffffd060)),(uint32_t)cpu(0));goto L_0027ee08;
L_0027ed30:;
/* 0027ed30: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027ed34: lui s3,0x4f */ set(19,sx(UINT32_C(0x004f0000)));
/* 0027ed38: lw a0,-0x2f98(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd068)));
/* 0027ed3c: lui s0,0x4f */ set(16,sx(UINT32_C(0x004f0000)));
/* 0027ed40: lw s1,0x0(v1) */ lw(17,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0027ed44: addiu s0,s0,0xa0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x000000a0)));
/* 0027ed48: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027ed4c: addiu s3,s3,-0x530 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xfffffad0)));
/* 0027ed50: sll s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)<<4));
/* 0027ed54: lw s4,0x12c(s8) */ lw(20,ea(30,(int32_t)UINT32_C(0x0000012c)));
/* 0027ed58: jal 0x001abc88 */ set(31,UINT64_C(0x0027ed60));/* delay 0027ed5c */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(19)));body_001abc88();
/* 0027ed60: lw a1,0x4(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027ed64: addiu s2,s0,0x14 */ set(18,sx((uint32_t)cpu(16)+UINT32_C(0x00000014)));
/* 0027ed68: lw a2,0xc(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027ed6c: lw a3,0x10(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 0027ed70: addiu a1,a1,0x57 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000057)));
/* 0027ed74: lw a0,0x0(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027ed78: lw t3,0xc(s1) */ lw(11,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027ed7c: lw t0,0x0(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027ed80: lw t1,0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027ed84: lw t2,0x8(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 0027ed88: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027ed8c: jal 0x00279a88 */ set(31,UINT64_C(0x0027ed94));/* delay 0027ed90 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));body_00279a88();
/* 0027ed94: lw a0,0x14(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027ed98: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027ed9c: lw s0,0x4(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 0027eda0: lw a0,-0x2f98(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd068)));
/* 0027eda4: jal 0x001abc88 */ set(31,UINT64_C(0x0027edac));/* delay 0027eda8 */ set(16,sx((uint32_t)cpu(16)<<4));body_001abc88();
/* 0027edac: lw a0,0x0(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 0027edb0: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 0027edb4: lw a1,0x4(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 0027edb8: lw a3,0x10(s2) */ lw(7,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 0027edbc: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027edc0: addiu a1,a1,0x57 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000057)));
/* 0027edc4: lw a2,0xc(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 0027edc8: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027edcc: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027edd0: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027edd4: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027edd8: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027eddc: jal 0x00279a88 */ set(31,UINT64_C(0x0027ede4));/* delay 0027ede0 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_00279a88();
/* 0027ede4: lw a0,-0x2f90(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd070)));
/* 0027ede8: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 0027edec: bne a0,v0,0x0027ee10 */ {int taken=(cpu(4)!=cpu(2));/* delay 0027edf0 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000007));if(taken){goto L_0027ee10;}}
/* 0027edf4: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 0027edf8: sw zero,-0x2fa0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd060)),(uint32_t)cpu(0));
/* 0027edfc: b 0x0027ee0c */ /* delay 0027ee00 */ sw(ea(28,(int32_t)UINT32_C(0xffffd064)),(uint32_t)cpu(2));goto L_0027ee0c;
L_0027ee08:;
/* 0027ee08: lw a0,-0x2f90(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd070)));
L_0027ee0c:;
/* 0027ee0c: sltiu v0,a0,0x7 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000007));
L_0027ee10:;
/* 0027ee10: beq v0,zero,0x0027f69c */ {int taken=(cpu(2)==cpu(0));/* delay 0027ee14 */ set(2,sx((uint32_t)cpu(4)<<2));if(taken){goto L_0027f69c;}}
/* 0027ee18: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 0027ee1c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0027ee20: lw v1,0x5450(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00005450)));
/* 0027ee24: jr v1 */ {uint64_t target=cpu(3);/* delay 0027ee28 */ switch((uint32_t)target){case UINT32_C(0x0027ee30):goto L_0027ee30;case UINT32_C(0x0027ee58):goto L_0027ee58;case UINT32_C(0x0027ef80):goto L_0027ef80;case UINT32_C(0x0027f0e0):goto L_0027f0e0;case UINT32_C(0x0027f238):goto L_0027f238;case UINT32_C(0x0027f270):goto L_0027f270;case UINT32_C(0x0027f69c):goto L_0027f69c;default:abort();}}
L_0027ee30:;
/* 0027ee30: addiu v0,gp,-0x2f94 */ set(2,sx((uint32_t)cpu(28)+UINT32_C(0xffffd06c)));
/* 0027ee34: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027ee38: move a0,v1 */ set(4,cpu(3));
/* 0027ee3c: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027ee40: slti a0,a0,0x4 */ set(4,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0027ee44: bne a0,zero,0x0027f69c */ {int taken=(cpu(4)!=cpu(0));/* delay 0027ee48 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_0027f69c;}}
/* 0027ee4c: b 0x0027f694 */ /* delay 0027ee50 */ set(4,sx(UINT32_C(0x00000001)));goto L_0027f694;
L_0027ee58:;
/* 0027ee58: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027ee5c: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 0027ee60: jal 0x00279980 */ set(31,UINT64_C(0x0027ee68));/* delay 0027ee64 */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027ee68: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027ee6c: lw v1,-0x2f94(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd06c)));
/* 0027ee70: addiu a2,v0,0xa0 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027ee74: mov.S f22,f21 */ f[22]=f[21];
/* 0027ee78: lwc1 f30,-0x5ba0(gp) */ f[30]=word(ea(28,(int32_t)UINT32_C(0xffffa460)));
/* 0027ee7c: lwc1 f28,-0x5b9c(gp) */ f[28]=word(ea(28,(int32_t)UINT32_C(0xffffa464)));
/* 0027ee80: lwc1 f23,0x10(a2) */ f[23]=word(ea(6,(int32_t)UINT32_C(0x00000010)));
/* 0027ee84: cvt.s.W f23,f23 */ f[23]=EE_FPU_CVT_S_W(f[23]);
/* 0027ee88: lwc1 f24,0x24(a2) */ f[24]=word(ea(6,(int32_t)UINT32_C(0x00000024)));
/* 0027ee8c: cvt.s.W f24,f24 */ f[24]=EE_FPU_CVT_S_W(f[24]);
/* 0027ee90: beq v1,zero,0x0027ef5c */ {int taken=(cpu(3)==cpu(0));/* delay 0027ee94 */ set(16,cpu(0));if(taken){goto L_0027ef5c;}}
/* 0027ee98: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027ee9c: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0027eea0: mtc1 at,f25 */ f[25]=(uint32_t)cpu(1);
/* 0027eea4: move s2,a2 */ set(18,cpu(6));
/* 0027eea8: addiu s1,v0,-0x530 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0xfffffad0)));
/* 0027eeac: mov.S f20,f21 */ f[20]=f[21];
/* 0027eeb0: sub.S f0,f22,f20 */ f[0]=EE_FPU_SUB_S(f[22],f[20]);
/* 0027eeb4: nop  */ 
L_0027eeb8:;
/* 0027eeb8: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027eebc: lw t1,0x12c(s8) */ lw(9,ea(30,(int32_t)UINT32_C(0x0000012c)));
/* 0027eec0: lui t0,0x880 */ set(8,sx(UINT32_C(0x08800000)));
/* 0027eec4: lw a3,0x0(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0027eec8: mov.S f12,f22 */ f[12]=f[22];
/* 0027eecc: move a0,zero */ set(4,cpu(0));
/* 0027eed0: move a2,s2 */ set(6,cpu(18));
/* 0027eed4: mul.S f0,f23,f0 */ f[0]=EE_FPU_MUL_S(f[23],f[0]);
/* 0027eed8: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027eedc: addu a3,a3,s1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(17)));
/* 0027eee0: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027eee4: addiu s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
/* 0027eee8: add.S f22,f22,f30 */ f[22]=EE_FPU_ADD_S(f[22],f[30]);
/* 0027eeec: mul.S f0,f0,f25 */ f[0]=EE_FPU_MUL_S(f[0],f[25]);
/* 0027eef0: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027eef4: mfc1 s6,f1 */ set(22,sx(f[1]));
/* 0027eef8: li v0,0x57 */ set(2,sx(UINT32_C(0x00000057)));
/* 0027eefc: jal 0x00279d30 */ set(31,UINT64_C(0x0027ef04));/* delay 0027ef00 */ set(5,sx((uint32_t)cpu(2)-(uint32_t)cpu(22)));body_00279d30();
/* 0027ef04: sub.S f0,f21,f20 */ f[0]=EE_FPU_SUB_S(f[21],f[20]);
/* 0027ef08: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027ef0c: lui t0,0x880 */ set(8,sx(UINT32_C(0x08800000)));
/* 0027ef10: lw t1,0x20(sp) */ lw(9,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027ef14: mov.S f12,f21 */ f[12]=f[21];
/* 0027ef18: lw a3,0x4(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0027ef1c: move a0,zero */ set(4,cpu(0));
/* 0027ef20: mul.S f0,f24,f0 */ f[0]=EE_FPU_MUL_S(f[24],f[0]);
/* 0027ef24: addiu a2,s2,0x14 */ set(6,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 0027ef28: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027ef2c: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027ef30: addu a3,a3,s1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(17)));
/* 0027ef34: add.S f21,f21,f28 */ f[21]=EE_FPU_ADD_S(f[21],f[28]);
/* 0027ef38: mul.S f0,f0,f25 */ f[0]=EE_FPU_MUL_S(f[0],f[25]);
/* 0027ef3c: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027ef40: mfc1 s6,f1 */ set(22,sx(f[1]));
/* 0027ef44: jal 0x00279d30 */ set(31,UINT64_C(0x0027ef4c));/* delay 0027ef48 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0x00000057)));body_00279d30();
/* 0027ef4c: lw v0,-0x2f94(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd06c)));
/* 0027ef50: sltu v0,s0,v0 */ set(2,cpu(16)<cpu(2));
/* 0027ef54: bnel v0,zero,0x0027eeb8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027ef58 */ f[0]=EE_FPU_SUB_S(f[22],f[20]);goto L_0027eeb8;}}
L_0027ef5c:;
/* 0027ef5c: addiu v0,gp,-0x2f94 */ set(2,sx((uint32_t)cpu(28)+UINT32_C(0xffffd06c)));
/* 0027ef60: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027ef64: move a0,v1 */ set(4,cpu(3));
/* 0027ef68: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027ef6c: slti a0,a0,0x4 */ set(4,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0027ef70: bne a0,zero,0x0027f69c */ {int taken=(cpu(4)!=cpu(0));/* delay 0027ef74 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_0027f69c;}}
/* 0027ef78: b 0x0027f694 */ /* delay 0027ef7c */ set(4,sx(UINT32_C(0x00000002)));goto L_0027f694;
L_0027ef80:;
/* 0027ef80: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027ef84: mtc1 at,f21 */ f[21]=(uint32_t)cpu(1);
/* 0027ef88: jal 0x00279980 */ set(31,UINT64_C(0x0027ef90));/* delay 0027ef8c */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027ef90: lwc1 f1,-0x2f94(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffd06c)));
/* 0027ef94: cvt.s.W f1,f1 */ f[1]=EE_FPU_CVT_S_W(f[1]);
/* 0027ef98: lui at,0x3e00 */ set(1,sx(UINT32_C(0x3e000000)));
/* 0027ef9c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027efa0: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027efa4: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027efa8: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027efac: lwc1 f23,0x10(v0) */ f[23]=word(ea(2,(int32_t)UINT32_C(0x00000010)));
/* 0027efb0: cvt.s.W f23,f23 */ f[23]=EE_FPU_CVT_S_W(f[23]);
/* 0027efb4: lwc1 f30,-0x5b98(gp) */ f[30]=word(ea(28,(int32_t)UINT32_C(0xffffa468)));
/* 0027efb8: mul.S f20,f1,f0 */ f[20]=EE_FPU_MUL_S(f[1],f[0]);
/* 0027efbc: lwc1 f28,-0x5b94(gp) */ f[28]=word(ea(28,(int32_t)UINT32_C(0xffffa46c)));
/* 0027efc0: lwc1 f24,0x24(v0) */ f[24]=word(ea(2,(int32_t)UINT32_C(0x00000024)));
/* 0027efc4: cvt.s.W f24,f24 */ f[24]=EE_FPU_CVT_S_W(f[24]);
/* 0027efc8: lwc1 f29,-0x5b90(gp) */ f[29]=word(ea(28,(int32_t)UINT32_C(0xffffa470)));
/* 0027efcc: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0027efd0: mtc1 at,f26 */ f[26]=(uint32_t)cpu(1);
/* 0027efd4: move s2,v0 */ set(18,cpu(2));
/* 0027efd8: lwc1 f27,-0x5b8c(gp) */ f[27]=word(ea(28,(int32_t)UINT32_C(0xffffa474)));
/* 0027efdc: addiu s1,v1,-0x530 */ set(17,sx((uint32_t)cpu(3)+UINT32_C(0xfffffad0)));
/* 0027efe0: mov.S f22,f21 */ f[22]=f[21];
/* 0027efe4: move s0,zero */ set(16,cpu(0));
/* 0027efe8: mov.S f25,f21 */ f[25]=f[21];
/* 0027efec: sub.S f0,f29,f22 */ f[0]=EE_FPU_SUB_S(f[29],f[22]);
L_0027eff0:;
/* 0027eff0: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027eff4: lw t1,0x12c(s8) */ lw(9,ea(30,(int32_t)UINT32_C(0x0000012c)));
/* 0027eff8: lui t0,0x880 */ set(8,sx(UINT32_C(0x08800000)));
/* 0027effc: lw a3,0x0(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027f000: li v0,0x57 */ set(2,sx(UINT32_C(0x00000057)));
/* 0027f004: move a0,zero */ set(4,cpu(0));
/* 0027f008: move a2,s2 */ set(6,cpu(18));
/* 0027f00c: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 0027f010: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027f014: addu a3,a3,s1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(17)));
/* 0027f018: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027f01c: addiu s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
/* 0027f020: add.S f12,f22,f0 */ f[12]=EE_FPU_ADD_S(f[22],f[0]);
/* 0027f024: add.S f22,f22,f30 */ f[22]=EE_FPU_ADD_S(f[22],f[30]);
/* 0027f028: sub.S f0,f12,f25 */ f[0]=EE_FPU_SUB_S(f[12],f[25]);
/* 0027f02c: mul.S f0,f23,f0 */ f[0]=EE_FPU_MUL_S(f[23],f[0]);
/* 0027f030: mul.S f0,f0,f26 */ f[0]=EE_FPU_MUL_S(f[0],f[26]);
/* 0027f034: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f038: mfc1 s6,f1 */ set(22,sx(f[1]));
/* 0027f03c: jal 0x00279d30 */ set(31,UINT64_C(0x0027f044));/* delay 0027f040 */ set(5,sx((uint32_t)cpu(2)-(uint32_t)cpu(22)));body_00279d30();
/* 0027f044: sub.S f0,f27,f21 */ f[0]=EE_FPU_SUB_S(f[27],f[21]);
/* 0027f048: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027f04c: lui t0,0x880 */ set(8,sx(UINT32_C(0x08800000)));
/* 0027f050: lw t1,0x20(sp) */ lw(9,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027f054: move a0,zero */ set(4,cpu(0));
/* 0027f058: lw a3,0x4(v1) */ lw(7,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 0027f05c: addiu a2,s2,0x14 */ set(6,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 0027f060: mul.S f0,f0,f20 */ f[0]=EE_FPU_MUL_S(f[0],f[20]);
/* 0027f064: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027f068: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027f06c: addu a3,a3,s1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(17)));
/* 0027f070: add.S f12,f21,f0 */ f[12]=EE_FPU_ADD_S(f[21],f[0]);
/* 0027f074: add.S f21,f21,f28 */ f[21]=EE_FPU_ADD_S(f[21],f[28]);
/* 0027f078: sub.S f0,f12,f25 */ f[0]=EE_FPU_SUB_S(f[12],f[25]);
/* 0027f07c: mul.S f0,f24,f0 */ f[0]=EE_FPU_MUL_S(f[24],f[0]);
/* 0027f080: mul.S f0,f0,f26 */ f[0]=EE_FPU_MUL_S(f[0],f[26]);
/* 0027f084: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f088: mfc1 s6,f1 */ set(22,sx(f[1]));
/* 0027f08c: jal 0x00279d30 */ set(31,UINT64_C(0x0027f094));/* delay 0027f090 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0x00000057)));body_00279d30();
/* 0027f094: sltiu v0,s0,0x4 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0027f098: bnel v0,zero,0x0027eff0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027f09c */ f[0]=EE_FPU_SUB_S(f[29],f[22]);goto L_0027eff0;}}
/* 0027f0a0: addiu v0,gp,-0x2f94 */ set(2,sx((uint32_t)cpu(28)+UINT32_C(0xffffd06c)));
/* 0027f0a4: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027f0a8: move a0,v1 */ set(4,cpu(3));
/* 0027f0ac: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027f0b0: slti a0,a0,0x8 */ set(4,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0027f0b4: bne a0,zero,0x0027f69c */ {int taken=(cpu(4)!=cpu(0));/* delay 0027f0b8 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_0027f69c;}}
/* 0027f0bc: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027f0c0: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f0c4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 0027f0c8: li a0,0x3 */ set(4,sx(UINT32_C(0x00000003)));
/* 0027f0cc: sw v1,-0x2f94(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd06c)),(uint32_t)cpu(3));
/* 0027f0d0: swc1 f0,-0x2f8c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd074)),f[0]);
/* 0027f0d4: b 0x0027f69c */ /* delay 0027f0d8 */ sw(ea(28,(int32_t)UINT32_C(0xffffd070)),(uint32_t)cpu(4));goto L_0027f69c;
L_0027f0e0:;
/* 0027f0e0: lui at,0x3f00 */ set(1,sx(UINT32_C(0x3f000000)));
/* 0027f0e4: mtc1 at,f26 */ f[26]=(uint32_t)cpu(1);
/* 0027f0e8: jal 0x00279980 */ set(31,UINT64_C(0x0027f0f0));/* delay 0027f0ec */ set(4,sx(UINT32_C(0x00000001)));body_00279980();
/* 0027f0f0: lwc1 f4,-0x2f94(gp) */ f[4]=word(ea(28,(int32_t)UINT32_C(0xffffd06c)));
/* 0027f0f4: cvt.s.W f4,f4 */ f[4]=EE_FPU_CVT_S_W(f[4]);
/* 0027f0f8: lui at,0x4190 */ set(1,sx(UINT32_C(0x41900000)));
/* 0027f0fc: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f100: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027f104: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027f108: mtc1 at,f3 */ f[3]=(uint32_t)cpu(1);
/* 0027f10c: addiu v0,v0,0xa0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027f110: lwc1 f5,-0x2f8c(gp) */ f[5]=word(ea(28,(int32_t)UINT32_C(0xffffd074)));
/* 0027f114: lwc1 f23,0x10(v0) */ f[23]=word(ea(2,(int32_t)UINT32_C(0x00000010)));
/* 0027f118: cvt.s.W f23,f23 */ f[23]=EE_FPU_CVT_S_W(f[23]);
/* 0027f11c: nop  */ 
/* 0027f120: nop  */ 
/* 0027f124: div.S f4,f4,f0 */ f[4]=EE_FPU_DIV_S(f[4],f[0]);
/* 0027f128: lui at,0x3f40 */ set(1,sx(UINT32_C(0x3f400000)));
/* 0027f12c: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f130: lwc1 f2,-0x5b88(gp) */ f[2]=word(ea(28,(int32_t)UINT32_C(0xffffa478)));
/* 0027f134: mov.S f25,f3 */ f[25]=f[3];
/* 0027f138: mul.S f0,f5,f0 */ f[0]=EE_FPU_MUL_S(f[5],f[0]);
/* 0027f13c: lwc1 f1,-0x5b84(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffa47c)));
/* 0027f140: lwc1 f24,0x24(v0) */ f[24]=word(ea(2,(int32_t)UINT32_C(0x00000024)));
/* 0027f144: cvt.s.W f24,f24 */ f[24]=EE_FPU_CVT_S_W(f[24]);
/* 0027f148: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027f14c: move s2,v0 */ set(18,cpu(2));
/* 0027f150: addiu s1,v1,-0x530 */ set(17,sx((uint32_t)cpu(3)+UINT32_C(0xfffffad0)));
/* 0027f154: move s0,zero */ set(16,cpu(0));
/* 0027f158: swc1 f0,-0x2f8c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd074)),f[0]);
/* 0027f15c: sub.S f20,f3,f4 */ f[20]=EE_FPU_SUB_S(f[3],f[4]);
/* 0027f160: mul.S f20,f20,f5 */ f[20]=EE_FPU_MUL_S(f[20],f[5]);
/* 0027f164: mul.S f2,f20,f2 */ f[2]=EE_FPU_MUL_S(f[20],f[2]);
/* 0027f168: mul.S f1,f20,f1 */ f[1]=EE_FPU_MUL_S(f[20],f[1]);
/* 0027f16c: add.S f22,f2,f3 */ f[22]=EE_FPU_ADD_S(f[2],f[3]);
/* 0027f170: add.S f21,f1,f3 */ f[21]=EE_FPU_ADD_S(f[1],f[3]);
/* 0027f174: sub.S f0,f22,f25 */ f[0]=EE_FPU_SUB_S(f[22],f[25]);
/* 0027f178: mul.S f0,f23,f0 */ f[0]=EE_FPU_MUL_S(f[23],f[0]);
/* 0027f17c: mul.S f20,f0,f26 */ f[20]=EE_FPU_MUL_S(f[0],f[26]);
L_0027f180:;
/* 0027f180: cvt.w.S f0,f20 */ f[0]=EE_FPU_CVT_W_S(f[20]);
/* 0027f184: mfc1 s6,f0 */ set(22,sx(f[0]));
/* 0027f188: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027f18c: li v1,0x57 */ set(3,sx(UINT32_C(0x00000057)));
/* 0027f190: lw t1,0x12c(s8) */ lw(9,ea(30,(int32_t)UINT32_C(0x0000012c)));
/* 0027f194: lw a3,0x0(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027f198: lui t0,0x880 */ set(8,sx(UINT32_C(0x08800000)));
/* 0027f19c: move a0,zero */ set(4,cpu(0));
/* 0027f1a0: move a2,s2 */ set(6,cpu(18));
/* 0027f1a4: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027f1a8: subu a1,v1,s6 */ set(5,sx((uint32_t)cpu(3)-(uint32_t)cpu(22)));
/* 0027f1ac: addu a3,a3,s1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(17)));
/* 0027f1b0: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027f1b4: mov.S f12,f22 */ f[12]=f[22];
/* 0027f1b8: jal 0x00279d30 */ set(31,UINT64_C(0x0027f1c0));/* delay 0027f1bc */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));body_00279d30();
/* 0027f1c0: sub.S f0,f21,f25 */ f[0]=EE_FPU_SUB_S(f[21],f[25]);
/* 0027f1c4: lw a0,0x14(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027f1c8: lui t0,0x880 */ set(8,sx(UINT32_C(0x08800000)));
/* 0027f1cc: lw t1,0x20(sp) */ lw(9,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027f1d0: addiu a2,s2,0x14 */ set(6,sx((uint32_t)cpu(18)+UINT32_C(0x00000014)));
/* 0027f1d4: lw a3,0x4(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 0027f1d8: move a0,zero */ set(4,cpu(0));
/* 0027f1dc: mul.S f0,f24,f0 */ f[0]=EE_FPU_MUL_S(f[24],f[0]);
/* 0027f1e0: ori t0,t0,0x8080 */ set(8,cpu(8)|UINT32_C(0x00008080));
/* 0027f1e4: sll a3,a3,0x4 */ set(7,sx((uint32_t)cpu(7)<<4));
/* 0027f1e8: mov.S f12,f21 */ f[12]=f[21];
/* 0027f1ec: addu a3,a3,s1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(17)));
/* 0027f1f0: mul.S f0,f0,f26 */ f[0]=EE_FPU_MUL_S(f[0],f[26]);
/* 0027f1f4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f1f8: mfc1 s6,f1 */ set(22,sx(f[1]));
/* 0027f1fc: jal 0x00279d30 */ set(31,UINT64_C(0x0027f204));/* delay 0027f200 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0x00000057)));body_00279d30();
/* 0027f204: sltiu v0,s0,0x4 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0027f208: bne v0,zero,0x0027f180 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027f20c */ if(taken){goto L_0027f180;}}
/* 0027f210: addiu v0,gp,-0x2f94 */ set(2,sx((uint32_t)cpu(28)+UINT32_C(0xffffd06c)));
/* 0027f214: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027f218: move a0,v1 */ set(4,cpu(3));
/* 0027f21c: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027f220: slti a0,a0,0x12 */ set(4,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000012));
/* 0027f224: bne a0,zero,0x0027f69c */ {int taken=(cpu(4)!=cpu(0));/* delay 0027f228 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_0027f69c;}}
/* 0027f22c: b 0x0027f694 */ /* delay 0027f230 */ set(4,sx(UINT32_C(0x00000004)));goto L_0027f694;
L_0027f238:;
/* 0027f238: addiu v0,gp,-0x2f94 */ set(2,sx((uint32_t)cpu(28)+UINT32_C(0xffffd06c)));
/* 0027f23c: lw v1,0x0(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027f240: move a0,v1 */ set(4,cpu(3));
/* 0027f244: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0027f248: slti a0,a0,0x8 */ set(4,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0027f24c: bne a0,zero,0x0027f69c */ {int taken=(cpu(4)!=cpu(0));/* delay 0027f250 */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_0027f69c;}}
/* 0027f254: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027f258: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f25c: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 0027f260: sw a0,-0x2f90(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd070)),(uint32_t)cpu(4));
/* 0027f264: swc1 f0,-0x2f8c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd074)),f[0]);
/* 0027f268: b 0x0027f69c */ /* delay 0027f26c */ sw(ea(28,(int32_t)UINT32_C(0xffffd06c)),(uint32_t)cpu(0));goto L_0027f69c;
L_0027f270:;
/* 0027f270: jal 0x00279980 */ set(31,UINT64_C(0x0027f278));/* delay 0027f274 */ set(4,cpu(0));body_00279980();
/* 0027f278: lw v1,-0x2f98(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd068)));
/* 0027f27c: lwc1 f3,-0x2f94(gp) */ f[3]=word(ea(28,(int32_t)UINT32_C(0xffffd06c)));
/* 0027f280: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027f284: lui at,0x4160 */ set(1,sx(UINT32_C(0x41600000)));
/* 0027f288: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027f28c: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027f290: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f294: lui v0,0xff */ set(2,sx(UINT32_C(0x00ff0000)));
/* 0027f298: lui at,0x41d0 */ set(1,sx(UINT32_C(0x41d00000)));
/* 0027f29c: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027f2a0: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 0027f2a4: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027f2a8: mtc1 at,f6 */ f[6]=(uint32_t)cpu(1);
/* 0027f2ac: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 0027f2b0: nop  */ 
/* 0027f2b4: nop  */ 
/* 0027f2b8: div.S f20,f3,f2 */ f[20]=EE_FPU_DIV_S(f[3],f[2]);
/* 0027f2bc: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 0027f2c0: sub.S f0,f0,f20 */ f[0]=EE_FPU_SUB_S(f[0],f[20]);
/* 0027f2c4: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0027f2c8: c.le.S f6,f0 */ (void)(EE_FPU_COMPARE_S(f[6],f[0],2)!=0);
/* 0027f2cc: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f2d0: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027f2d4: bc1f 0x0027f2f0 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027f2d8 */ if(taken){goto L_0027f2f0;}}
/* 0027f2dc: sub.S f0,f0,f6 */ f[0]=EE_FPU_SUB_S(f[0],f[6]);
/* 0027f2e0: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027f2e4: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f2e8: mfc1 v1,f1 */ set(3,sx(f[1]));
/* 0027f2ec: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
L_0027f2f0:;
/* 0027f2f0: lui at,0x41d0 */ set(1,sx(UINT32_C(0x41d00000)));
/* 0027f2f4: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f2f8: sll v0,v1,0x18 */ set(2,sx((uint32_t)cpu(3)<<24));
/* 0027f2fc: lwc1 f1,-0x2f8c(gp) */ f[1]=word(ea(28,(int32_t)UINT32_C(0xffffd074)));
/* 0027f300: lui a2,0x4f */ set(6,sx(UINT32_C(0x004f0000)));
/* 0027f304: mul.S f0,f20,f0 */ f[0]=EE_FPU_MUL_S(f[20],f[0]);
/* 0027f308: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027f30c: lw a0,0x10(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027f310: addiu s3,a2,-0x530 */ set(19,sx((uint32_t)cpu(6)+UINT32_C(0xfffffad0)));
/* 0027f314: lw s0,0x0(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0027f318: li v1,0x57 */ set(3,sx(UINT32_C(0x00000057)));
/* 0027f31c: or s7,a0,v0 */ set(23,cpu(4)|cpu(2));
/* 0027f320: lui v0,0x4f */ set(2,sx(UINT32_C(0x004f0000)));
/* 0027f324: cvt.w.S f2,f0 */ f[2]=EE_FPU_CVT_W_S(f[0]);
/* 0027f328: mfc1 s6,f2 */ set(22,sx(f[2]));
/* 0027f32c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027f330: addiu s1,v0,0xa0 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x000000a0)));
/* 0027f334: move a0,s7 */ set(4,cpu(23));
/* 0027f338: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027f33c: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 0027f340: lw s4,0x12c(s8) */ lw(20,ea(30,(int32_t)UINT32_C(0x0000012c)));
/* 0027f344: mtc1 s6,f0 */ f[0]=(uint32_t)cpu(22);
/* 0027f348: cvt.s.W f0,f0 */ f[0]=EE_FPU_CVT_S_W(f[0]);
/* 0027f34c: subu s5,v1,s6 */ set(21,sx((uint32_t)cpu(3)-(uint32_t)cpu(22)));
/* 0027f350: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0027f354: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f358: mfc1 s2,f1 */ set(18,sx(f[1]));
/* 0027f35c: jal 0x001abc88 */ set(31,UINT64_C(0x0027f364));/* delay 0027f360 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000057)));body_001abc88();
/* 0027f364: lw v1,0x4(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027f368: li a3,0x57 */ set(7,sx(UINT32_C(0x00000057)));
/* 0027f36c: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027f370: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027f374: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027f378: subu a1,a3,s2 */ set(5,sx((uint32_t)cpu(7)-(uint32_t)cpu(18)));
/* 0027f37c: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027f380: addu a1,v1,a1 */ set(5,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0027f384: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027f388: addiu s2,s2,0x57 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000057)));
/* 0027f38c: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027f390: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027f394: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027f398: jal 0x00279a88 */ set(31,UINT64_C(0x0027f3a0));/* delay 0027f39c */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));body_00279a88();
/* 0027f3a0: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027f3a4: move a0,s7 */ set(4,cpu(23));
/* 0027f3a8: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027f3ac: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027f3b0: jal 0x001abc88 */ set(31,UINT64_C(0x0027f3b8));/* delay 0027f3b4 */ lw(20,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027f3b8: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027f3bc: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027f3c0: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 0027f3c4: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027f3c8: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027f3cc: addu a1,a1,s5 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(21)));
/* 0027f3d0: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027f3d4: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027f3d8: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027f3dc: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027f3e0: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027f3e4: sw s4,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));
/* 0027f3e8: jal 0x00279a88 */ set(31,UINT64_C(0x0027f3f0));/* delay 0027f3ec */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));body_00279a88();
/* 0027f3f0: lw v1,0x14(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027f3f4: move a0,s7 */ set(4,cpu(23));
/* 0027f3f8: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027f3fc: lw s0,0x0(v1) */ lw(16,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0027f400: jal 0x001abc88 */ set(31,UINT64_C(0x0027f408));/* delay 0027f404 */ lw(20,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027f408: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027f40c: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027f410: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 0027f414: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027f418: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027f41c: addu a1,a1,s2 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(18)));
/* 0027f420: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027f424: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027f428: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027f42c: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027f430: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027f434: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027f438: jal 0x00279a88 */ set(31,UINT64_C(0x0027f440));/* delay 0027f43c */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));body_00279a88();
/* 0027f440: lw a0,0x14(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027f444: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027f448: lw s0,0x0(a0) */ lw(16,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0027f44c: move a0,s7 */ set(4,cpu(23));
/* 0027f450: jal 0x001abc88 */ set(31,UINT64_C(0x0027f458));/* delay 0027f454 */ lw(18,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027f458: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027f45c: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027f460: addu s0,s0,s3 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 0027f464: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027f468: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027f46c: addu a1,a1,s6 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(22)));
/* 0027f470: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027f474: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027f478: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027f47c: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027f480: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027f484: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027f488: jal 0x00279a88 */ set(31,UINT64_C(0x0027f490));/* delay 0027f48c */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));body_00279a88();
/* 0027f490: lw v1,-0x2f94(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd06c)));
/* 0027f494: slti v0,v1,0xd */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000d));
/* 0027f498: beq v0,zero,0x0027f574 */ {int taken=(cpu(2)==cpu(0));/* delay 0027f49c */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));if(taken){goto L_0027f574;}}
/* 0027f4a0: mtc1 v1,f3 */ f[3]=(uint32_t)cpu(3);
/* 0027f4a4: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027f4a8: lui at,0x4150 */ set(1,sx(UINT32_C(0x41500000)));
/* 0027f4ac: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027f4b0: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027f4b4: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f4b8: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027f4bc: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027f4c0: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027f4c4: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027f4c8: nop  */ 
/* 0027f4cc: nop  */ 
/* 0027f4d0: div.S f20,f3,f1 */ f[20]=EE_FPU_DIV_S(f[3],f[1]);
/* 0027f4d4: sub.S f0,f0,f20 */ f[0]=EE_FPU_SUB_S(f[0],f[20]);
/* 0027f4d8: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0027f4dc: c.le.S f4,f0 */ (void)(EE_FPU_COMPARE_S(f[4],f[0],2)!=0);
/* 0027f4e0: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f4e4: mfc1 a0,f1 */ set(4,sx(f[1]));
/* 0027f4e8: bc1f 0x0027f508 */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027f4ec */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));if(taken){goto L_0027f508;}}
/* 0027f4f0: sub.S f0,f0,f4 */ f[0]=EE_FPU_SUB_S(f[0],f[4]);
/* 0027f4f4: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027f4f8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f4fc: mfc1 a0,f1 */ set(4,sx(f[1]));
/* 0027f500: or a0,a0,v0 */ set(4,cpu(4)|cpu(2));
/* 0027f504: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
L_0027f508:;
/* 0027f508: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027f50c: lw a3,0x10(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027f510: lui a2,0x4f */ set(6,sx(UINT32_C(0x004f0000)));
/* 0027f514: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0027f518: addiu v0,v1,-0x530 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xfffffad0)));
/* 0027f51c: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027f520: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 0027f524: addiu s1,a2,0xa0 */ set(17,sx((uint32_t)cpu(6)+UINT32_C(0x000000a0)));
/* 0027f528: or a0,a3,a0 */ set(4,cpu(7)|cpu(4));
/* 0027f52c: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027f530: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 0027f534: jal 0x001abc88 */ set(31,UINT64_C(0x0027f53c));/* delay 0027f538 */ lw(18,ea(30,(int32_t)UINT32_C(0x0000012c)));body_001abc88();
/* 0027f53c: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027f540: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027f544: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027f548: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027f54c: addiu a1,a1,0x57 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000057)));
/* 0027f550: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027f554: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027f558: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027f55c: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027f560: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027f564: jal 0x00279a88 */ set(31,UINT64_C(0x0027f56c));/* delay 0027f568 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));body_00279a88();
/* 0027f56c: lw v1,-0x2f94(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd06c)));
/* 0027f570: slti v0,v1,0x8 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
L_0027f574:;
/* 0027f574: bne v0,zero,0x0027f590 */ {int taken=(cpu(2)!=cpu(0));/* delay 0027f578 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000a));if(taken){goto L_0027f590;}}
/* 0027f57c: lwc1 f0,-0x2f8c(gp) */ f[0]=word(ea(28,(int32_t)UINT32_C(0xffffd074)));
/* 0027f580: lui at,0x3fa0 */ set(1,sx(UINT32_C(0x3fa00000)));
/* 0027f584: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027f588: mul.S f0,f0,f1 */ f[0]=EE_FPU_MUL_S(f[0],f[1]);
/* 0027f58c: swc1 f0,-0x2f8c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd074)),f[0]);
L_0027f590:;
/* 0027f590: beql v0,zero,0x0027f684 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027f594 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));goto L_0027f684;}}
/* 0027f598: mtc1 v1,f3 */ f[3]=(uint32_t)cpu(3);
/* 0027f59c: cvt.s.W f3,f3 */ f[3]=EE_FPU_CVT_S_W(f[3]);
/* 0027f5a0: lui at,0x4120 */ set(1,sx(UINT32_C(0x41200000)));
/* 0027f5a4: mtc1 at,f1 */ f[1]=(uint32_t)cpu(1);
/* 0027f5a8: lui at,0x3f80 */ set(1,sx(UINT32_C(0x3f800000)));
/* 0027f5ac: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f5b0: lui at,0x4300 */ set(1,sx(UINT32_C(0x43000000)));
/* 0027f5b4: mtc1 at,f2 */ f[2]=(uint32_t)cpu(1);
/* 0027f5b8: lui at,0x4f00 */ set(1,sx(UINT32_C(0x4f000000)));
/* 0027f5bc: mtc1 at,f4 */ f[4]=(uint32_t)cpu(1);
/* 0027f5c0: nop  */ 
/* 0027f5c4: nop  */ 
/* 0027f5c8: div.S f20,f3,f1 */ f[20]=EE_FPU_DIV_S(f[3],f[1]);
/* 0027f5cc: sub.S f0,f0,f20 */ f[0]=EE_FPU_SUB_S(f[0],f[20]);
/* 0027f5d0: mul.S f0,f0,f2 */ f[0]=EE_FPU_MUL_S(f[0],f[2]);
/* 0027f5d4: c.le.S f4,f0 */ (void)(EE_FPU_COMPARE_S(f[4],f[0],2)!=0);
/* 0027f5d8: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f5dc: mfc1 a0,f1 */ set(4,sx(f[1]));
/* 0027f5e0: bc1f 0x0027f5fc */ {int taken=(((nocturneBattlePanelOwnerFcsr()>>23)&1u)==0);/* delay 0027f5e4 */ if(taken){goto L_0027f5fc;}}
/* 0027f5e8: sub.S f0,f0,f4 */ f[0]=EE_FPU_SUB_S(f[0],f[4]);
/* 0027f5ec: lui v0,0x8000 */ set(2,sx(UINT32_C(0x80000000)));
/* 0027f5f0: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f5f4: mfc1 a0,f1 */ set(4,sx(f[1]));
/* 0027f5f8: or a0,a0,v0 */ set(4,cpu(4)|cpu(2));
L_0027f5fc:;
/* 0027f5fc: lui at,0x41d0 */ set(1,sx(UINT32_C(0x41d00000)));
/* 0027f600: mtc1 at,f0 */ f[0]=(uint32_t)cpu(1);
/* 0027f604: lui v1,0x4f */ set(3,sx(UINT32_C(0x004f0000)));
/* 0027f608: lw v0,0x14(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000014)));
/* 0027f60c: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 0027f610: mul.S f0,f20,f0 */ f[0]=EE_FPU_MUL_S(f[20],f[0]);
/* 0027f614: lw a2,0x10(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027f618: lw s0,0x4(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 0027f61c: addiu v0,v1,-0x530 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xfffffad0)));
/* 0027f620: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027f624: lui s1,0x4f */ set(17,sx(UINT32_C(0x004f0000)));
/* 0027f628: addiu s1,s1,0xb4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x000000b4)));
/* 0027f62c: or a0,a2,a0 */ set(4,cpu(6)|cpu(4));
/* 0027f630: cvt.w.S f1,f0 */ f[1]=EE_FPU_CVT_W_S(f[0]);
/* 0027f634: mfc1 s6,f1 */ set(22,sx(f[1]));
/* 0027f638: sll s0,s0,0x4 */ set(16,sx((uint32_t)cpu(16)<<4));
/* 0027f63c: jal 0x001abc88 */ set(31,UINT64_C(0x0027f644));/* delay 0027f640 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));body_001abc88();
/* 0027f644: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 0027f648: lw v1,0x4(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 0027f64c: lw t3,0xc(s0) */ lw(11,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 0027f650: addiu a1,s6,0x57 */ set(5,sx((uint32_t)cpu(22)+UINT32_C(0x00000057)));
/* 0027f654: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0027f658: addu a1,v1,a1 */ set(5,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0027f65c: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 0027f660: lw t0,0x0(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0027f664: lw t1,0x4(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 0027f668: lw t2,0x8(s0) */ lw(10,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 0027f66c: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027f670: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027f674: jal 0x00279a88 */ set(31,UINT64_C(0x0027f67c));/* delay 0027f678 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_00279a88();
/* 0027f67c: lw v1,-0x2f94(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd06c)));
/* 0027f680: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
L_0027f684:;
/* 0027f684: slti v0,v1,0xe */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 0027f688: bnel v0,zero,0x0027f69c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027f68c */ sw(ea(28,(int32_t)UINT32_C(0xffffd06c)),(uint32_t)cpu(3));goto L_0027f69c;}}
/* 0027f690: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
L_0027f694:;
/* 0027f694: sw zero,-0x2f94(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd06c)),(uint32_t)cpu(0));
/* 0027f698: sw a0,-0x2f90(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd070)),(uint32_t)cpu(4));
L_0027f69c:;
/* 0027f69c: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 0027f6a0: ld s0,0x30(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0027f6a4: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027f6a8: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 0027f6ac: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027f6b0: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027f6b4: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027f6b8: ld s5,0x58(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027f6bc: ld s6,0x60(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027f6c0: ld s7,0x68(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027f6c4: ld s8,0x70(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027f6c8: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027f6cc: lwc1 f30,0xd0(sp) */ f[30]=word(ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 0027f6d0: lwc1 f29,0xc8(sp) */ f[29]=word(ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 0027f6d4: lwc1 f28,0xc0(sp) */ f[28]=word(ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 0027f6d8: lwc1 f27,0xb8(sp) */ f[27]=word(ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0027f6dc: lwc1 f26,0xb0(sp) */ f[26]=word(ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0027f6e0: lwc1 f25,0xa8(sp) */ f[25]=word(ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0027f6e4: lwc1 f24,0xa0(sp) */ f[24]=word(ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0027f6e8: lwc1 f23,0x98(sp) */ f[23]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0027f6ec: lwc1 f22,0x90(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0027f6f0: lwc1 f21,0x88(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0027f6f4: lwc1 f20,0x80(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0027f6f8: j 0x00279c00 */ /* delay 0027f6fc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000e0)));checkReturn(cpu(31),incoming);body_00279c00();return;
L_0027f700:;
/* 0027f700: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0027f704: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0027f708: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 0027f70c: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0027f710: ld s5,0x58(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 0027f714: ld s6,0x60(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0027f718: ld s7,0x68(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0027f71c: ld s8,0x70(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0027f720: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 0027f724: lwc1 f30,0xd0(sp) */ f[30]=word(ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 0027f728: lwc1 f29,0xc8(sp) */ f[29]=word(ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 0027f72c: lwc1 f28,0xc0(sp) */ f[28]=word(ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 0027f730: lwc1 f27,0xb8(sp) */ f[27]=word(ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 0027f734: lwc1 f26,0xb0(sp) */ f[26]=word(ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0027f738: lwc1 f25,0xa8(sp) */ f[25]=word(ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 0027f73c: lwc1 f24,0xa0(sp) */ f[24]=word(ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 0027f740: lwc1 f23,0x98(sp) */ f[23]=word(ea(29,(int32_t)UINT32_C(0x00000098)));
/* 0027f744: lwc1 f22,0x90(sp) */ f[22]=word(ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0027f748: lwc1 f21,0x88(sp) */ f[21]=word(ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0027f74c: lwc1 f20,0x80(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0027f750: jr ra */ {uint64_t target=cpu(31);/* delay 0027f754 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000e0)));checkReturn(target,incoming);return;}
}
static void body_002ab0c8(void){
uint64_t incoming=cpu(31);
/* 002ab0c8: lw v1,0x28(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002ab0cc: jr ra */ {uint64_t target=cpu(31);/* delay 002ab0d0 */ restore(2,ea(3,(int32_t)UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002ab0d8(void){
uint64_t incoming=cpu(31);
/* 002ab0d8: lw v1,0x28(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002ab0dc: jr ra */ {uint64_t target=cpu(31);/* delay 002ab0e0 */ restore(2,ea(3,(int32_t)UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002ab0e8(void){
uint64_t incoming=cpu(31);
/* 002ab0e8: lw v1,0x28(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002ab0ec: jr ra */ {uint64_t target=cpu(31);/* delay 002ab0f0 */ restore(2,ea(3,(int32_t)UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002acb50(void){
uint64_t incoming=cpu(31);
/* 002acb50: lw v1,-0x28f8(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd708)));
/* 002acb54: li v0,-0x10 */ set(2,sx(UINT32_C(0xfffffff0)));
/* 002acb58: addiu a0,a0,0xf */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000000f)));
/* 002acb5c: and a0,a0,v0 */ set(4,cpu(4)&cpu(2));
/* 002acb60: move v0,v1 */ set(2,cpu(3));
/* 002acb64: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002acb68: jr ra */ {uint64_t target=cpu(31);/* delay 002acb6c */ sw(ea(28,(int32_t)UINT32_C(0xffffd708)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
static void body_002acb78(void){
uint64_t incoming=cpu(31);
/* 002acb78: addiu a0,a0,0xf */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000000f)));
/* 002acb7c: li v0,-0x10 */ set(2,sx(UINT32_C(0xfffffff0)));
/* 002acb80: and a0,a0,v0 */ set(4,cpu(4)&cpu(2));
/* 002acb84: jr ra */ {uint64_t target=cpu(31);/* delay 002acb88 */ sw(ea(28,(int32_t)UINT32_C(0xffffd708)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_002acb90(void){
uint64_t incoming=cpu(31);
/* 002acb90: ori v0,zero,0xffff */ set(2,cpu(0)|UINT32_C(0x0000ffff));
/* 002acb94: sw zero,0x1c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 002acb98: sw v0,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002acb9c: sw zero,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002acba0: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002acba4: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002acba8: sw zero,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002acbac: sw zero,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002acbb0: jr ra */ {uint64_t target=cpu(31);/* delay 002acbb4 */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_002acbb8(void){
uint64_t incoming=cpu(31);
/* 002acbb8: lw a2,0x8(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002acbbc: bne a2,zero,0x002acbd0 */ {int taken=(cpu(6)!=cpu(0));/* delay 002acbc0 */ set(2,sx(UINT32_C(0x0fff0000)));if(taken){goto L_002acbd0;}}
/* 002acbc4: b 0x002acbe4 */ /* delay 002acbc8 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));goto L_002acbe4;
L_002acbd0:;
/* 002acbd0: li v1,0x20 */ set(3,sx(UINT32_C(0x00000020)));
/* 002acbd4: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002acbd8: sb v1,0x3(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(3));
/* 002acbdc: and v0,a1,v0 */ set(2,cpu(5)&cpu(2));
/* 002acbe0: sw v0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002acbe4:;
/* 002acbe4: jr ra */ {uint64_t target=cpu(31);/* delay 002acbe8 */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_002acd40(void){
uint64_t incoming=cpu(31);
/* 002acd40: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002acd44: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002acd48: move s0,a1 */ set(16,cpu(5));
/* 002acd4c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002acd50: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002acd54: lw v0,0x4(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002acd58: beq v0,zero,0x002acd84 */ {int taken=(cpu(2)==cpu(0));/* delay 002acd5c */ set(17,cpu(4));if(taken){goto L_002acd84;}}
/* 002acd60: lw v0,0x8(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002acd64: bne v0,zero,0x002acd78 */ {int taken=(cpu(2)!=cpu(0));/* delay 002acd68 */ set(4,cpu(2));if(taken){goto L_002acd78;}}
/* 002acd6c: b 0x002acd80 */ /* delay 002acd70 */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(16));goto L_002acd80;
L_002acd78:;
/* 002acd78: jal 0x002acee8 */ set(31,UINT64_C(0x002acd80));/* delay 002acd7c */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));body_002acee8();
L_002acd80:;
/* 002acd80: sw s0,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(16));
L_002acd84:;
/* 002acd84: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002acd88: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002acd8c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002acd90: jr ra */ {uint64_t target=cpu(31);/* delay 002acd94 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002acdc0(void){
uint64_t incoming=cpu(31);
/* 002acdc0: lui t0,0x2b */ set(8,sx(UINT32_C(0x002b0000)));
/* 002acdc4: lui a3,0x2b */ set(7,sx(UINT32_C(0x002b0000)));
/* 002acdc8: addiu v0,t0,-0x32c0 */ set(2,sx((uint32_t)cpu(8)+UINT32_C(0xffffcd40)));
/* 002acdcc: addiu v1,a3,-0x3268 */ set(3,sx((uint32_t)cpu(7)+UINT32_C(0xffffcd98)));
/* 002acdd0: addiu a1,a1,-0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 002acdd4: sw v0,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002acdd8: sw v1,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 002acddc: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002acde0: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002acde4: sw zero,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002acde8: bne a1,zero,0x002acdf8 */ {int taken=(cpu(5)!=cpu(0));/* delay 002acdec */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));if(taken){goto L_002acdf8;}}
/* 002acdf0: jr ra */ {uint64_t target=cpu(31);/* delay 002acdf4 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
L_002acdf8:;
/* 002acdf8: addiu a2,a0,0x20 */ set(6,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));
/* 002acdfc: addiu v0,t0,-0x32c0 */ set(2,sx((uint32_t)cpu(8)+UINT32_C(0xffffcd40)));
/* 002ace00: addiu v1,a3,-0x3268 */ set(3,sx((uint32_t)cpu(7)+UINT32_C(0xffffcd98)));
/* 002ace04: addiu a1,a1,-0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 002ace08: sw a2,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(6));
/* 002ace0c: move a0,a2 */ set(4,cpu(6));
/* 002ace10: sw v0,0x10(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 002ace14: sw v1,0x14(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 002ace18: sw zero,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002ace1c: sw zero,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002ace20: sw zero,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002ace24: bne a1,zero,0x002acdf8 */ {int taken=(cpu(5)!=cpu(0));/* delay 002ace28 */ sw(ea(6,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));if(taken){goto L_002acdf8;}}
/* 002ace2c: jr ra */ {uint64_t target=cpu(31);/* delay 002ace30 */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_002ace38(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 002ace38: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002ace3c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ace40: move s0,a0 */ set(16,cpu(4));
/* 002ace44: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ace48: jal 0x002acb50 */ set(31,UINT64_C(0x002ace50));/* delay 002ace4c */ set(4,sx(UINT32_C(0x00000020)));body_002acb50();
/* 002ace50: lhu a1,0x0(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002ace54: lui v1,0xfff */ set(3,sx(UINT32_C(0x0fff0000)));
/* 002ace58: addiu a0,s0,0x10 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002ace5c: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002ace60: lui a2,0x3000 */ set(6,sx(UINT32_C(0x30000000)));
/* 002ace64: and a0,a0,v1 */ set(4,cpu(4)&cpu(3));
/* 002ace68: clear v1 */ {const uint32_t q[4]={0,0,0,0};nocturneBattlePanelOwnerCpuWrite(3u,q);}
/* 002ace6c: or a1,a1,a2 */ set(5,cpu(5)|cpu(6));
/* 002ace70: dsll32 a0,a0,0x0 */ set(4,cpu(4)<<32);
/* 002ace74: move a3,v0 */ set(7,cpu(2));
/* 002ace78: or a1,a1,a0 */ set(5,cpu(5)|cpu(4));
/* 002ace7c: sd a1,0x0(a3) */ save(5,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002ace80: sq v1,0x10(a3) */ sq(3,ea(7,(int32_t)UINT32_C(0x00000010)));
/* 002ace84: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002ace88: ld v1,0x8(s0) */ restore(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002ace8c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002ace90: sd v1,0x8(a3) */ save(3,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 002ace94: jr ra */ {uint64_t target=cpu(31);/* delay 002ace98 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002acea0(void){
uint64_t incoming=cpu(31);
/* 002acea0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002acea4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002acea8: move s0,a0 */ set(16,cpu(4));
/* 002aceac: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aceb0: jal 0x002ace38 */ set(31,UINT64_C(0x002aceb8));/* delay 002aceb4 */ set(4,cpu(5));body_002ace38();
/* 002aceb8: lui v1,0xfff */ set(3,sx(UINT32_C(0x0fff0000)));
/* 002acebc: move a0,v0 */ set(4,cpu(2));
/* 002acec0: li v0,0x20 */ set(2,sx(UINT32_C(0x00000020)));
/* 002acec4: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002acec8: sb v0,0x3(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(2));
/* 002acecc: addiu v0,a0,0x10 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
/* 002aced0: and a0,a0,v1 */ set(4,cpu(4)&cpu(3));
/* 002aced4: sw a0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002aced8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002acedc: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002acee0: jr ra */ {uint64_t target=cpu(31);/* delay 002acee4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002acee8(void){
uint64_t incoming=cpu(31);
/* 002acee8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002aceec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002acef0: move s0,a0 */ set(16,cpu(4));
/* 002acef4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002acef8: move s1,a1 */ set(17,cpu(5));
/* 002acefc: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002acf00: lw a1,0x10(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002acf04: lw v0,0x10(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002acf08: beq v0,a1,0x002acf24 */ {int taken=(cpu(2)==cpu(5));/* delay 002acf0c */ lw(6,ea(16,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002acf24;}}
/* 002acf10: beql a1,zero,0x002acf24 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 002acf14 */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));goto L_002acf24;}}
/* 002acf18: jal 0x002acea0 */ set(31,UINT64_C(0x002acf20));/* delay 002acf1c */ set(4,cpu(6));body_002acea0();
/* 002acf20: move a2,v0 */ set(6,cpu(2));
L_002acf24:;
/* 002acf24: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 002acf28: lw a1,0x14(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 002acf2c: beq v0,a1,0x002acf4c */ {int taken=(cpu(2)==cpu(5));/* delay 002acf30 */ set(4,sx(UINT32_C(0x00000020)));if(taken){goto L_002acf4c;}}
/* 002acf34: beql a1,zero,0x002acf4c */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 002acf38 */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));goto L_002acf4c;}}
/* 002acf3c: jal 0x002acea0 */ set(31,UINT64_C(0x002acf44));/* delay 002acf40 */ set(4,cpu(6));body_002acea0();
/* 002acf44: move a2,v0 */ set(6,cpu(2));
/* 002acf48: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
L_002acf4c:;
/* 002acf4c: lui v1,0xfff */ set(3,sx(UINT32_C(0x0fff0000)));
/* 002acf50: sb a0,0x3(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000003)),(uint8_t)cpu(4));
/* 002acf54: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002acf58: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002acf5c: lw v0,0x4(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002acf60: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002acf64: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002acf68: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002acf6c: sw v0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002acf70: jr ra */ {uint64_t target=cpu(31);/* delay 002acf74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002ad130(void){
uint64_t incoming=cpu(31);
/* 002ad130: addiu a3,a1,0x1 */ set(7,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002ad134: lui v0,0x5000 */ set(2,sx(UINT32_C(0x50000000)));
/* 002ad138: or v0,a3,v0 */ set(2,cpu(7)|cpu(2));
/* 002ad13c: lui a2,0x1000 */ set(6,sx(UINT32_C(0x10000000)));
/* 002ad140: lui v1,0x1000 */ set(3,sx(UINT32_C(0x10000000)));
/* 002ad144: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002ad148: ori v1,v1,0x8000 */ set(3,cpu(3)|UINT32_C(0x00008000));
/* 002ad14c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002ad150: or v1,a1,v1 */ set(3,cpu(5)|cpu(3));
/* 002ad154: li a1,0xe */ set(5,sx(UINT32_C(0x0000000e)));
/* 002ad158: or v0,v0,a2 */ set(2,cpu(2)|cpu(6));
/* 002ad15c: sd a1,0x18(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002ad160: sd v0,0x8(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002ad164: sd v1,0x10(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002ad168: jr ra */ {uint64_t target=cpu(31);/* delay 002ad16c */ save(7,ea(4,(int32_t)UINT32_C(0x00000000)));checkReturn(target,incoming);return;}
}
static void body_002aef00(void){
uint64_t incoming=cpu(31);
/* 002aef00: lw v1,0x0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aef04: sll a3,a3,0x10 */ set(7,sx((uint32_t)cpu(7)<<16));
/* 002aef08: lw v0,0x8(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aef0c: andi a2,a2,0xffff */ set(6,cpu(6)&UINT32_C(0x0000ffff));
/* 002aef10: andi t1,t1,0xffff */ set(9,cpu(9)&UINT32_C(0x0000ffff));
/* 002aef14: sll t2,t2,0x10 */ set(10,sx((uint32_t)cpu(10)<<16));
/* 002aef18: sll v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)<<16));
/* 002aef1c: andi v1,v1,0xffff */ set(3,cpu(3)&UINT32_C(0x0000ffff));
/* 002aef20: lw t4,0x10(sp) */ lw(12,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aef24: or a2,a2,a3 */ set(6,cpu(6)|cpu(7));
/* 002aef28: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002aef2c: ori v0,zero,0xfe00 */ set(2,cpu(0)|UINT32_C(0x0000fe00));
/* 002aef30: dsll32 v0,v0,0xe */ set(2,cpu(2)<<46);
/* 002aef34: or t1,t1,t2 */ set(9,cpu(9)|cpu(10));
/* 002aef38: lw a3,0x18(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aef3c: ori a1,a1,0x10c */ set(5,cpu(5)|UINT32_C(0x0000010c));
/* 002aef40: dsll32 t0,t0,0x0 */ set(8,cpu(8)<<32);
/* 002aef44: dsll32 a2,a2,0x0 */ set(6,cpu(6)<<32);
/* 002aef48: dsll32 t3,t3,0x0 */ set(11,cpu(11)<<32);
/* 002aef4c: dsll32 t1,t1,0x0 */ set(9,cpu(9)<<32);
/* 002aef50: dsll32 t4,t4,0x0 */ set(12,cpu(12)<<32);
/* 002aef54: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002aef58: dsll32 a3,a3,0x0 */ set(7,cpu(7)<<32);
/* 002aef5c: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002aef60: dsrl32 t0,t0,0x0 */ set(8,cpu(8)>>32);
/* 002aef64: dsrl32 a2,a2,0x0 */ set(6,cpu(6)>>32);
/* 002aef68: dsrl32 t3,t3,0x0 */ set(11,cpu(11)>>32);
/* 002aef6c: dsrl32 t1,t1,0x0 */ set(9,cpu(9)>>32);
/* 002aef70: dsrl32 t4,t4,0x0 */ set(12,cpu(12)>>32);
/* 002aef74: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002aef78: or t4,t4,v0 */ set(12,cpu(12)|cpu(2));
/* 002aef7c: or v1,v1,a3 */ set(3,cpu(3)|cpu(7));
/* 002aef80: or t0,t0,v0 */ set(8,cpu(8)|cpu(2));
/* 002aef84: or a2,a2,a3 */ set(6,cpu(6)|cpu(7));
/* 002aef88: or t3,t3,v0 */ set(11,cpu(11)|cpu(2));
/* 002aef8c: or t1,t1,a3 */ set(9,cpu(9)|cpu(7));
/* 002aef90: lui a3,0xf515 */ set(7,sx(UINT32_C(0xf5150000)));
/* 002aef94: ori a3,a3,0x1510 */ set(7,cpu(7)|UINT32_C(0x00001510));
/* 002aef98: dsrl32 a1,a1,0x0 */ set(5,cpu(5)>>32);
/* 002aef9c: lui v0,0x8400 */ set(2,sx(UINT32_C(0x84000000)));
/* 002aefa0: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002aefa4: ori v0,v0,0x8001 */ set(2,cpu(2)|UINT32_C(0x00008001));
/* 002aefa8: sd v1,0x40(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 002aefac: sd v0,0x0(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002aefb0: sd a3,0x8(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002aefb4: sd a1,0x10(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002aefb8: sd t0,0x18(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002aefbc: sd a2,0x20(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002aefc0: sd t3,0x28(a0) */ save(11,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002aefc4: sd t1,0x30(a0) */ save(9,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002aefc8: jr ra */ {uint64_t target=cpu(31);/* delay 002aefcc */ save(12,ea(4,(int32_t)UINT32_C(0x00000038)));checkReturn(target,incoming);return;}
}
static void body_002aefd0(void){
uint64_t incoming=cpu(31);
/* 002aefd0: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
/* 002aefd4: lw v1,0x88(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002aefd8: lw v0,0xa0(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002aefdc: sw v1,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(3));
/* 002aefe0: lw v1,0x90(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002aefe4: sd s1,0x38(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002aefe8: move s1,a1 */ set(17,cpu(5));
/* 002aefec: sw v1,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 002aeff0: lw v1,0x98(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002aeff4: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002aeff8: move s2,a2 */ set(18,cpu(6));
/* 002aeffc: sd s3,0x48(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002af000: move s3,a3 */ set(19,cpu(7));
/* 002af004: sd s4,0x50(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002af008: move s4,t0 */ set(20,cpu(8));
/* 002af00c: sd s5,0x58(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002af010: move s5,t1 */ set(21,cpu(9));
/* 002af014: sd s6,0x60(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002af018: move s6,t2 */ set(22,cpu(10));
/* 002af01c: sd s7,0x68(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002af020: move s7,t3 */ set(23,cpu(11));
/* 002af024: sd s8,0x70(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002af028: sw a0,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(4));
/* 002af02c: li a0,0x60 */ set(4,sx(UINT32_C(0x00000060)));
/* 002af030: sd s0,0x30(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002af034: sd ra,0x78(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002af038: lw s8,0x80(sp) */ lw(30,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002af03c: bne v0,zero,0x002af04c */ {int taken=(cpu(2)!=cpu(0));/* delay 002af040 */ sw(ea(29,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(3));if(taken){goto L_002af04c;}}
/* 002af044: lui v0,0x2b */ set(2,sx(UINT32_C(0x002b0000)));
/* 002af048: addiu v0,v0,-0x34b0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffcb50)));
L_002af04c:;
/* 002af04c: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002af054));/* delay 002af050 */ if(target==UINT64_C(0x002acb50)){body_002acb50();}else{nocturneBattlePanelOwnerIndirect(target,UINT32_C(0x002af04c));}}
/* 002af054: lui v1,0x5000 */ set(3,sx(UINT32_C(0x50000000)));
/* 002af058: ori v1,v1,0x5 */ set(3,cpu(3)|UINT32_C(0x00000005));
/* 002af05c: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002af060: ori v1,v1,0x1000 */ set(3,cpu(3)|UINT32_C(0x00001000));
/* 002af064: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002af068: move s0,v0 */ set(16,cpu(2));
/* 002af06c: lui v0,0x2000 */ set(2,sx(UINT32_C(0x20000000)));
/* 002af070: ori v0,v0,0x5 */ set(2,cpu(2)|UINT32_C(0x00000005));
/* 002af074: sd v0,0x0(s0) */ save(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002af078: move a1,s1 */ set(5,cpu(17));
/* 002af07c: sd v1,0x8(s0) */ save(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002af080: move a2,s2 */ set(6,cpu(18));
/* 002af084: move a3,s3 */ set(7,cpu(19));
/* 002af088: move t0,s4 */ set(8,cpu(20));
/* 002af08c: lw v0,0x24(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 002af090: move t1,s5 */ set(9,cpu(21));
/* 002af094: lw v1,0x28(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002af098: move t2,s6 */ set(10,cpu(22));
/* 002af09c: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002af0a0: move t3,s7 */ set(11,cpu(23));
/* 002af0a4: lw v0,0x2c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000002c)));
/* 002af0a8: addiu a0,s0,0x10 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002af0ac: sw s8,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(30));
/* 002af0b0: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 002af0b4: jal 0x002aef00 */ set(31,UINT64_C(0x002af0bc));/* delay 002af0b8 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));body_002aef00();
/* 002af0bc: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002af0c0: move a1,s0 */ set(5,cpu(16));
/* 002af0c4: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002af0c8: ld s0,0x30(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002af0cc: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002af0d0: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002af0d4: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002af0d8: ld s5,0x58(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002af0dc: ld s6,0x60(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002af0e0: ld s7,0x68(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002af0e4: ld s8,0x70(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002af0e8: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002af0ec: j 0x002acbb8 */ /* delay 002af0f0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));checkReturn(cpu(31),incoming);body_002acbb8();return;
}
static void body_002b9c18(void){
uint64_t incoming=cpu(31);
/* 002b9c18: jr ra */ {uint64_t target=cpu(31);/* delay 002b9c1c */ set(2,sx(UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_002b9c20(void){
uint64_t incoming=cpu(31);
/* 002b9c20: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b9c24: lui v0,0x5000 */ set(2,sx(UINT32_C(0x50000000)));
/* 002b9c28: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9c2c: move s0,a0 */ set(16,cpu(4));
/* 002b9c30: li a3,0xe */ set(7,sx(UINT32_C(0x0000000e)));
/* 002b9c34: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 002b9c38: ori v0,v0,0x4 */ set(2,cpu(2)|UINT32_C(0x00000004));
/* 002b9c3c: lui a0,0x1000 */ set(4,sx(UINT32_C(0x10000000)));
/* 002b9c40: dsll32 a0,a0,0x0 */ set(4,cpu(4)<<32);
/* 002b9c44: ori a0,a0,0x8003 */ set(4,cpu(4)|UINT32_C(0x00008003));
/* 002b9c48: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9c4c: move s1,a2 */ set(17,cpu(6));
/* 002b9c50: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b9c54: move s2,a1 */ set(18,cpu(5));
/* 002b9c58: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b9c5c: sd a3,0x18(s0) */ save(7,ea(16,(int32_t)UINT32_C(0x00000018)));
/* 002b9c60: sh v1,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002b9c64: sd a0,0x10(s0) */ save(4,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002b9c68: move a0,s2 */ set(4,cpu(18));
/* 002b9c6c: sw v0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002b9c70: jal 0x002ab0d8 */ set(31,UINT64_C(0x002b9c78));/* delay 002b9c74 */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));body_002ab0d8();
/* 002b9c78: addiu v1,s1,0x14 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));
/* 002b9c7c: sd v1,0x28(s0) */ save(3,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002b9c80: move a0,s2 */ set(4,cpu(18));
/* 002b9c84: jal 0x002ab0c8 */ set(31,UINT64_C(0x002b9c8c));/* delay 002b9c88 */ save(2,ea(16,(int32_t)UINT32_C(0x00000020)));body_002ab0c8();
/* 002b9c8c: addiu v1,s1,0x6 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000006)));
/* 002b9c90: sd v1,0x38(s0) */ save(3,ea(16,(int32_t)UINT32_C(0x00000038)));
/* 002b9c94: move a0,s2 */ set(4,cpu(18));
/* 002b9c98: sd v0,0x30(s0) */ save(2,ea(16,(int32_t)UINT32_C(0x00000030)));
/* 002b9c9c: jal 0x002ab0e8 */ set(31,UINT64_C(0x002b9ca4));/* delay 002b9ca0 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000008)));body_002ab0e8();
/* 002b9ca4: sd s1,0x48(s0) */ save(17,ea(16,(int32_t)UINT32_C(0x00000048)));
/* 002b9ca8: sd v0,0x40(s0) */ save(2,ea(16,(int32_t)UINT32_C(0x00000040)));
/* 002b9cac: move v0,s0 */ set(2,cpu(16));
/* 002b9cb0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9cb4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9cb8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b9cbc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b9cc0: jr ra */ {uint64_t target=cpu(31);/* delay 002b9cc4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002b9cc8(void){
uint64_t incoming=cpu(31);
/* 002b9cc8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b9ccc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9cd0: move s0,a1 */ set(16,cpu(5));
/* 002b9cd4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b9cd8: move s2,a0 */ set(18,cpu(4));
/* 002b9cdc: move a0,s0 */ set(4,cpu(16));
/* 002b9ce0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9ce4: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b9ce8: jal 0x002b9c18 */ set(31,UINT64_C(0x002b9cf0));/* delay 002b9cec */ set(17,cpu(6));body_002b9c18();
/* 002b9cf0: jal 0x002acb50 */ set(31,UINT64_C(0x002b9cf8));/* delay 002b9cf4 */ set(4,cpu(2));body_002acb50();
/* 002b9cf8: move a1,s0 */ set(5,cpu(16));
/* 002b9cfc: move a2,s1 */ set(6,cpu(17));
/* 002b9d00: jal 0x002b9c20 */ set(31,UINT64_C(0x002b9d08));/* delay 002b9d04 */ set(4,cpu(2));body_002b9c20();
/* 002b9d08: move a0,s2 */ set(4,cpu(18));
/* 002b9d0c: move s0,v0 */ set(16,cpu(2));
/* 002b9d10: jal 0x002acbb8 */ set(31,UINT64_C(0x002b9d18));/* delay 002b9d14 */ set(5,cpu(16));body_002acbb8();
/* 002b9d18: move v0,s0 */ set(2,cpu(16));
/* 002b9d1c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9d20: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9d24: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b9d28: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002b9d2c: jr ra */ {uint64_t target=cpu(31);/* delay 002b9d30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002b9d38(void){
uint64_t incoming=cpu(31);
/* 002b9d38: sra a1,a1,0x4 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>4)));
/* 002b9d3c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002b9d40: addiu a1,a1,-0x2 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xfffffffe)));
/* 002b9d44: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9d48: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9d4c: jal 0x002ad130 */ set(31,UINT64_C(0x002b9d54));/* delay 002b9d50 */ set(16,cpu(4));body_002ad130();
/* 002b9d54: move v0,s0 */ set(2,cpu(16));
/* 002b9d58: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9d5c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9d60: jr ra */ {uint64_t target=cpu(31);/* delay 002b9d64 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002b9d68(void){
uint64_t incoming=cpu(31);
/* 002b9d68: mult v0,a0,a1 */ nativeMultiply(2,(uint32_t)cpu(4),(uint32_t)cpu(5),1,0);
/* 002b9d6c: addiu v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 002b9d70: jr ra */ {uint64_t target=cpu(31);/* delay 002b9d74 */ set(2,sx((uint32_t)cpu(2)<<4));checkReturn(target,incoming);return;}
}
static void body_002b9d78(void){
uint64_t incoming=cpu(31);
/* 002b9d78: jr ra */ {uint64_t target=cpu(31);/* delay 002b9d7c */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002b9d80(void){
uint64_t incoming=cpu(31);
/* 002b9d80: mult v1,a2,t0 */ nativeMultiply(3,(uint32_t)cpu(6),(uint32_t)cpu(8),1,0);
/* 002b9d84: dsll32 a2,a2,0x1c */ set(6,cpu(6)<<60);
/* 002b9d88: dsll32 a1,a1,0xf */ set(5,cpu(5)<<47);
/* 002b9d8c: or a2,t0,a2 */ set(6,cpu(8)|cpu(6));
/* 002b9d90: or a2,a2,a1 */ set(6,cpu(6)|cpu(5));
/* 002b9d94: li a1,0x4000 */ set(5,sx(UINT32_C(0x00004000)));
/* 002b9d98: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002b9d9c: ori a1,a1,0x8000 */ set(5,cpu(5)|UINT32_C(0x00008000));
/* 002b9da0: lui v0,0x5000 */ set(2,sx(UINT32_C(0x50000000)));
/* 002b9da4: or a2,a2,a1 */ set(6,cpu(6)|cpu(5));
/* 002b9da8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002b9dac: sd a2,0x10(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002b9db0: or v0,v1,v0 */ set(2,cpu(3)|cpu(2));
/* 002b9db4: sd a3,0x18(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002b9db8: sw v0,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 002b9dbc: move v0,a0 */ set(2,cpu(4));
/* 002b9dc0: sh v1,0x0(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
/* 002b9dc4: jr ra */ {uint64_t target=cpu(31);/* delay 002b9dc8 */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_002b9dd0(void){
uint64_t incoming=cpu(31);
/* 002b9dd0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002b9dd4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9dd8: move s1,a0 */ set(17,cpu(4));
/* 002b9ddc: move a1,s1 */ set(5,cpu(17));
/* 002b9de0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9de4: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b9de8: jal 0x002b9d68 */ set(31,UINT64_C(0x002b9df0));/* delay 002b9dec */ set(4,sx(UINT32_C(0x00000005)));body_002b9d68();
/* 002b9df0: jal 0x002acb50 */ set(31,UINT64_C(0x002b9df8));/* delay 002b9df4 */ set(4,cpu(2));body_002acb50();
/* 002b9df8: li a1,0x156 */ set(5,sx(UINT32_C(0x00000156)));
/* 002b9dfc: move s0,v0 */ set(16,cpu(2));
/* 002b9e00: move t0,s1 */ set(8,cpu(17));
/* 002b9e04: move a0,s0 */ set(4,cpu(16));
/* 002b9e08: lui a3,0x5 */ set(7,sx(UINT32_C(0x00050000)));
/* 002b9e0c: ori a3,a3,0x3531 */ set(7,cpu(7)|UINT32_C(0x00003531));
/* 002b9e10: jal 0x002b9d80 */ set(31,UINT64_C(0x002b9e18));/* delay 002b9e14 */ set(6,sx(UINT32_C(0x00000005)));body_002b9d80();
/* 002b9e18: move v0,s0 */ set(2,cpu(16));
/* 002b9e1c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002b9e20: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002b9e24: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002b9e28: jr ra */ {uint64_t target=cpu(31);/* delay 002b9e2c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelOwnerBody(uint32_t entry){switch(entry){
case UINT32_C(0x00117b08):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_00117b08();return 1u;case UINT32_C(0x001abbd0):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_001abbd0();return 1u;case UINT32_C(0x001abc88):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_001abc88();return 1u;case UINT32_C(0x002797b0):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002797b0();return 1u;case UINT32_C(0x00279868):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_00279868();return 1u;case UINT32_C(0x00279980):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_00279980();return 1u;case UINT32_C(0x00279a88):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_00279a88();return 1u;case UINT32_C(0x00279c00):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_00279c00();return 1u;case UINT32_C(0x00279d30):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_00279d30();return 1u;case UINT32_C(0x00279e20):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_00279e20();return 1u;case UINT32_C(0x0027a7c0):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_0027a7c0();return 1u;case UINT32_C(0x0027d888):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_0027d888();return 1u;case UINT32_C(0x0027d9d8):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_0027d9d8();return 1u;case UINT32_C(0x002ab0c8):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002ab0c8();return 1u;case UINT32_C(0x002ab0d8):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002ab0d8();return 1u;case UINT32_C(0x002ab0e8):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002ab0e8();return 1u;case UINT32_C(0x002acb50):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002acb50();return 1u;case UINT32_C(0x002acb78):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002acb78();return 1u;case UINT32_C(0x002acb90):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002acb90();return 1u;case UINT32_C(0x002acbb8):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002acbb8();return 1u;case UINT32_C(0x002acd40):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002acd40();return 1u;case UINT32_C(0x002acdc0):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002acdc0();return 1u;case UINT32_C(0x002ace38):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002ace38();return 1u;case UINT32_C(0x002acea0):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002acea0();return 1u;case UINT32_C(0x002acee8):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002acee8();return 1u;case UINT32_C(0x002ad130):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002ad130();return 1u;case UINT32_C(0x002aef00):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002aef00();return 1u;case UINT32_C(0x002aefd0):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002aefd0();return 1u;case UINT32_C(0x002b9c18):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002b9c18();return 1u;case UINT32_C(0x002b9c20):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002b9c20();return 1u;case UINT32_C(0x002b9cc8):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002b9cc8();return 1u;case UINT32_C(0x002b9d38):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002b9d38();return 1u;case UINT32_C(0x002b9d68):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002b9d68();return 1u;case UINT32_C(0x002b9d78):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002b9d78();return 1u;case UINT32_C(0x002b9d80):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002b9d80();return 1u;case UINT32_C(0x002b9dd0):if(nocturneBattlePanelOwnerStackPointer()!=(uint32_t)cpu(29))abort();body_002b9dd0();return 1u;
default:return 0u;}}

void ps2BattlePanelSetOrderingOffset_002797B0(uint64_t a0){
set(4u,a0);
body_002797b0();
return;
}

void ps2BattlePanelDrawScaledTexture_00279D30(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,float f12){
set(4u,a0);
set(5u,a1);
set(6u,a2);
set(7u,a3);
set(8u,a4);
set(9u,a5);
memcpy(&nocturneEffectHostFpr()[12u],&f12,4);
body_00279d30();
return;
}

void ps2BattlePanelDrawScaledTextureXY_00279E20(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,float f12,float f13){
set(4u,a0);
set(5u,a1);
set(6u,a2);
set(7u,a3);
set(8u,a4);
set(9u,a5);
memcpy(&nocturneEffectHostFpr()[12u],&f12,4);
memcpy(&nocturneEffectHostFpr()[13u],&f13,4);
body_00279e20();
return;
}

void ps2BattlePanelDrawCurveHighlight_0027A7C0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7){
set(4u,a0);
set(5u,a1);
set(6u,a2);
set(7u,a3);
set(8u,a4);
set(9u,a5);
set(10u,a6);
set(11u,a7);
body_0027a7c0();
return;
}

uint64_t nbPanelPressTurnRun(void){
body_0027d888();
return cpu(2);
}

void nbPanelPressTurn(uint64_t a0){
set(4u,a0);
body_0027d9d8();
return;
}

void ps2DrawBuildColoredTrianglePacket_002AEF00(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7,uint32_t a8,uint32_t a9,uint32_t a10,uint32_t a11){
set(4u,a0);
set(5u,a1);
set(6u,a2);
set(7u,a3);
set(8u,a4);
set(9u,a5);
set(10u,a6);
set(11u,a7);
sw((uint32_t)cpu(29)+0u,(uint32_t)a8);
sw((uint32_t)cpu(29)+8u,(uint32_t)a9);
sw((uint32_t)cpu(29)+16u,(uint32_t)a10);
sw((uint32_t)cpu(29)+24u,(uint32_t)a11);
body_002aef00();
return;
}

void ps2DrawAppendColoredTrianglePacket_002AEFD0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7,uint32_t a8,uint32_t a9,uint32_t a10,uint32_t a11,uint32_t a12){
set(4u,a0);
set(5u,a1);
set(6u,a2);
set(7u,a3);
set(8u,a4);
set(9u,a5);
set(10u,a6);
set(11u,a7);
sw((uint32_t)cpu(29)+0u,(uint32_t)a8);
sw((uint32_t)cpu(29)+8u,(uint32_t)a9);
sw((uint32_t)cpu(29)+16u,(uint32_t)a10);
sw((uint32_t)cpu(29)+24u,(uint32_t)a11);
sw((uint32_t)cpu(29)+32u,(uint32_t)a12);
body_002aefd0();
return;
}
