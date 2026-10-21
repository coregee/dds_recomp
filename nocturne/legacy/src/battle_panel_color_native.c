/* Whole native 001ABC88/32 instructions. Actual bank/frame value profile.
 * No per-call observed upper words, supplied color results or host floating
 * arithmetic. Architectural timing and full VU MAC/STATUS flags are not added
 * by the existing EE_ROT value primitive; see the source admission limits. */
#include "battle_panel_color_native.h"
#include "ee_vu_rotation.h"
#include "effect_ftoi0.h"
#include <stdlib.h>
#include <string.h>

static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned reg){
 uint32_t q[4];nocturneBattlePanelColorCpuRead(reg,q);
 return (uint64_t)q[0]|((uint64_t)q[1]<<32);
}
/* All scalar native writes preserve the actual destination upper64. */
static void set(unsigned reg,uint64_t value){
 uint32_t q[4];nocturneBattlePanelColorCpuRead(reg,q);
 q[0]=(uint32_t)value;q[1]=(uint32_t)(value>>32);
 nocturneBattlePanelColorCpuWrite(reg,q);
 if(reg==29u)nocturneBattlePanelColorSetStackPointer(q[0]);
}
static uint32_t address(unsigned reg,int32_t offset){return (uint32_t)cpu(reg)+(uint32_t)offset;}
static void sw(uint32_t a,uint32_t v){memcpy(nocturneResolveBattlePanelColorAddress(a),&v,4);}
static void lw(unsigned reg,uint32_t a){uint32_t v;memcpy(&v,nocturneResolveBattlePanelColorAddress(a),4);set(reg,sx(v));}
static void qmt(unsigned vf,unsigned reg){
 uint32_t q[4];nocturneBattlePanelColorCpuRead(reg,q);nocturneBattlePanelColorVuWrite(vf,q);
}
static void qmf(unsigned reg,unsigned vf){
 uint32_t q[4];nocturneBattlePanelColorVuRead(vf,q);nocturneBattlePanelColorCpuWrite(reg,q);
}
static void moveVu(unsigned dest,unsigned source){
 uint32_t q[4];nocturneBattlePanelColorVuRead(source,q);nocturneBattlePanelColorVuWrite(dest,q);
}
static void mulVu(unsigned dest,unsigned first,unsigned second,unsigned broadcastX){
 uint32_t a[4],b[4],q[4];unsigned k;
 nocturneBattlePanelColorVuRead(first,a);nocturneBattlePanelColorVuRead(second,b);
 for(k=0;k<4u;++k)q[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[broadcastX?0u:k]);
 nocturneBattlePanelColorVuWrite(dest,q);
}
/* PEXTLB ZERO/LH ZERO followed by VITOF0 always supplies four 0..255 words.
 * These are exactly representable binary32 values; no COP1/FCSR operation. */
static uint32_t byteFloat(uint32_t value){
 unsigned top=0;uint32_t t=value;if(!value)return 0;
 while(t>1u){t>>=1;++top;}
 return ((top+127u)<<23)|((value<<(23u-top))&UINT32_C(0x007fffff));
}
static void itof(unsigned dest,unsigned source){
 uint32_t q[4];unsigned k;nocturneBattlePanelColorVuRead(source,q);
 for(k=0;k<4u;++k)q[k]=byteFloat(q[k]);nocturneBattlePanelColorVuWrite(dest,q);
}
static void ftoi(unsigned dest,unsigned source){
 uint32_t q[4];unsigned k;nocturneBattlePanelColorVuRead(source,q);
 for(k=0;k<4u;++k)q[k]=nocturneEffectFtoi0Bits(q[k]);nocturneBattlePanelColorVuWrite(dest,q);
}

static void pextlb(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint8_t x[16],y[16],z[16];
 nocturneBattlePanelColorCpuRead(a,aq);nocturneBattlePanelColorCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<8;k++){z[k*2]=y[k];z[k*2+1]=x[k];}memcpy(q,z,16);nocturneBattlePanelColorCpuWrite(d,q);
}
static void pextlh(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint16_t x[8],y[8],z[8];
 nocturneBattlePanelColorCpuRead(a,aq);nocturneBattlePanelColorCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<4;k++){z[k*2]=y[k];z[k*2+1]=x[k];}memcpy(q,z,16);nocturneBattlePanelColorCpuWrite(d,q);
}
static void ppach(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint16_t x[8],y[8],z[8];
 nocturneBattlePanelColorCpuRead(a,aq);nocturneBattlePanelColorCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<4;k++){z[k]=y[k*2];z[k+4]=x[k*2];}memcpy(q,z,16);nocturneBattlePanelColorCpuWrite(d,q);
}
static void ppacb(unsigned d,unsigned a,unsigned b){
 uint32_t aq[4],bq[4],q[4];uint8_t x[16],y[16],z[16];
 nocturneBattlePanelColorCpuRead(a,aq);nocturneBattlePanelColorCpuRead(b,bq);memcpy(x,aq,16);memcpy(y,bq,16);
 for(unsigned k=0;k<8;k++){z[k]=y[k*2];z[k+8]=x[k*2];}memcpy(q,z,16);nocturneBattlePanelColorCpuWrite(d,q);
}
uint64_t nocturneBattlePanelColorBody_001ABC88(void){
 uint64_t incoming=cpu(31);
 if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();
/* 001abc88: addiu sp,sp,-0x30 */ set(29u,sx((uint32_t)cpu(29u)+UINT32_C(0xffffffd0)));
/* 001abc8c: sw a0,0x0(sp) */ sw(address(29u,0),(uint32_t)cpu(4u));
/* 001abc90: lui a0,0x3c00 */ set(4u,sx(UINT32_C(0x3c000000)));
/* 001abc94: lw v0,0x0(sp) */ lw(2u,address(29u,0));
/* 001abc98: pextlb v0,zero,v0 */ pextlb(2,0,2);
/* 001abc9c: pextlh v0,zero,v0 */ pextlh(2,0,2);
/* 001abca0: qmtc2 v0,vf10 */ qmt(10u,2u);
/* 001abca4: vitof0.xyzw vf10,vf10 */ itof(10u,10u);
/* 001abca8: qmtc2 a0,vf2 */ qmt(2u,4u);
/* 001abcac: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abcb0: vmove.xyzw vf11,vf10 */ moveVu(11u,10u);
/* 001abcb4: sw a1,0x10(sp) */ sw(address(29u,16),(uint32_t)cpu(5u));
/* 001abcb8: addiu v1,sp,0x10 */ set(3u,sx((uint32_t)cpu(29u)+UINT32_C(0x00000010)));
/* 001abcbc: lw v0,0x0(v1) */ lw(2u,address(3u,0));
/* 001abcc0: pextlb v0,zero,v0 */ pextlb(2,0,2);
/* 001abcc4: pextlh v0,zero,v0 */ pextlh(2,0,2);
/* 001abcc8: qmtc2 v0,vf10 */ qmt(10u,2u);
/* 001abccc: vitof0.xyzw vf10,vf10 */ itof(10u,10u);
/* 001abcd0: qmtc2 a0,vf2 */ qmt(2u,4u);
/* 001abcd4: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abcd8: vmul.xyzw vf10,vf10,vf11 */ mulVu(10u,10u,11u,0u);
/* 001abcdc: lui at,0x4300 */ set(1u,sx(UINT32_C(0x43000000)));
/* 001abce0: mtc1 at,f0 */ nocturneBattlePanelColorWriteFpr(0u,(uint32_t)cpu(1u));
/* 001abce4: mfc1 v1,f0 */ set(3u,sx(nocturneBattlePanelColorReadFpr(0u)));
/* 001abce8: qmtc2 v1,vf2 */ qmt(2u,3u);
/* 001abcec: vmulx.xyzw vf10,vf10,vf2 */ mulVu(10u,10u,2u,1u);
/* 001abcf0: vftoi0.xyzw vf10,vf10 */ ftoi(10u,10u);
/* 001abcf4: qmfc2 v0,vf10 */ qmf(2u,10u);
/* 001abcf8: ppach v0,zero,v0 */ ppach(2,0,2);
/* 001abcfc: ppacb v0,zero,v0 */ ppacb(2,0,2);
/* 001abd00: jr ra; 001abd04 delay: addiu sp,sp,0x30 */
 {uint64_t target=cpu(31);set(29u,sx((uint32_t)cpu(29u)+UINT32_C(0x00000030)));if((uint32_t)target!=(uint32_t)incoming)abort();return cpu(2);}
}
uint64_t ps2BattlePanelColorNative_001ABC88(uint64_t first,uint64_t second){
 set(4,first);set(5,second);return nocturneBattlePanelColorBody_001ABC88();
}
