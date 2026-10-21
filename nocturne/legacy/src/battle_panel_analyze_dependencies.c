/* Complete16 private Analyze dependencies with actual native bank/frame ownership; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_panel_analyze_dependencies.h"
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
static uint8_t *at(uint32_t a){return nocturneResolveBattlePanelAnalyzeAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneEffectHostCpuWrite(r,q);if(r==29u)nocturneBattlePanelAnalyzeSetStackPointer(q[0]);
}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}
static void nativeDivide(uint32_t n,uint32_t d,int isSigned,int secondary){
 uint32_t q,r;
 if(!d){q=isSigned&&(int32_t)n<0?1u:UINT32_MAX;r=n;}
 else if(isSigned&&n==UINT32_C(0x80000000)&&d==UINT32_MAX){q=n;r=0;}
 else if(isSigned){q=(uint32_t)((int32_t)n/(int32_t)d);r=(uint32_t)((int32_t)n%(int32_t)d);}
 else{q=n/d;r=n%d;}
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx(q),sx(r));else nocturneEffectHostSetHilo(sx(q),sx(r));
}



void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sq(unsigned reg,uint32_t a){uint32_t q[4];nocturneEffectHostCpuRead(reg,q);memcpy(at(a&~15u),q,16);}
static void nativeMultiply(unsigned rd,uint32_t a,uint32_t b,int isSigned,int secondary){
 uint64_t p=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)b):(uint64_t)a*b;
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 else nocturneEffectHostSetHilo(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 if(rd)set(rd,sx((uint32_t)p));
}
static void prerequisitePcpyh(unsigned d,unsigned s){
 uint32_t a[4],q[4];nocturneEffectHostCpuRead(s,a);
 q[0]=q[1]=(a[0]&65535u)*65537u;q[2]=q[3]=(a[2]&65535u)*65537u;
 nocturneEffectHostCpuWrite(d,q);
}




static void requestPacked(unsigned kind,unsigned d,unsigned s,unsigned t){
 uint32_t a[4],c[4],q[4];nocturneEffectHostCpuRead(s,a);nocturneEffectHostCpuRead(t,c);
 if(kind==0){q[0]=c[0];q[1]=c[1];q[2]=a[0];q[3]=a[1];}
 else if(kind==1){q[0]=a[2];q[1]=a[3];q[2]=c[2];q[3]=c[3];}
 else if(kind==2){for(unsigned i=0;i<4;i++)q[i]=a[i]&c[i];}
 else if(kind==3){for(unsigned i=0;i<4;i++)q[i]=~(a[i]|c[i]);}
 else if(kind==5){for(unsigned i=0;i<4;i++)q[i]=a[i]^c[i];}
 else{uint8_t x[16],y[16],z[16];memcpy(x,a,16);memcpy(y,c,16);for(unsigned i=0;i<16;i++)z[i]=(uint8_t)(x[i]-y[i]);memcpy(q,z,16);}
 nocturneEffectHostCpuWrite(d,q);
}














static void analyzeLoadPartialWord(unsigned r,uint32_t a,int left){
 uint8_t d[4],s[4];uint32_t v=(uint32_t)cpu(r);unsigned o=a&3u;
 memcpy(d,&v,4);memcpy(s,at(a&~3u),4);
 if(left){for(unsigned i=0;i<=o;i++)d[3u-o+i]=s[i];}
 else{for(unsigned i=o;i<4;i++)d[i-o]=s[i];}
 memcpy(&v,d,4);set(r,sx(v));
}
static void analyzeStorePartialWord(uint32_t a,unsigned r,int left){
 uint8_t s[4];uint32_t v=(uint32_t)cpu(r);unsigned o=a&3u;
 memcpy(s,&v,4);uint8_t *d=at(a&~3u);
 if(left){for(unsigned i=0;i<=o;i++)d[i]=s[3u-o+i];}
 else{for(unsigned i=o;i<4;i++)d[i]=s[i-o];}
}
static void loadPartial(unsigned r,uint32_t a,int left){uint8_t d[8],s[8];uint64_t v=cpu(r);memcpy(d,&v,8);memcpy(s,at(a&~7u),8);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[7u-o+i]=s[i];}else{for(unsigned i=o;i<8;i++)d[i-o]=s[i];}memcpy(&v,d,8);set(r,v);}
static void storePartial(uint32_t a,unsigned r,int left){uint8_t s[8];uint64_t v=cpu(r);memcpy(s,&v,8);uint8_t *d=at(a&~7u);unsigned o=a&7u;if(left){for(unsigned i=0;i<=o;i++)d[i]=s[7u-o+i];}else{for(unsigned i=o;i<8;i++)d[i]=s[i-o];}}static void body_00212248(void);
static void body_002122c8(void);
static void body_00212878(void);
static void body_00214530(void);
static void body_00214550(void);
static void body_00214730(void);
static void body_00235ff8(void);
static void body_002361c0(void);
static void body_00239d20(void);
static void body_00239df8(void);
static void body_00245d18(void);
static void body_00279c58(void);
static void body_00279c80(void);
static void body_00282268(void);
static void body_002ab0f8(void);
static void body_002d4558(void);
static void body_002aad88(void);
static void body_002aaf20(void);
static void body_00280528(void);
static void body_00212248(void){
uint64_t incoming=cpu(31);
/* 00212248: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0021224c: andi a2,a2,0xff */ set(6,cpu(6)&UINT32_C(0x000000ff));
/* 00212250: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00212254: sll a2,a2,0x3 */ set(6,sx((uint32_t)cpu(6)<<3));
/* 00212258: addu a2,a2,t1 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(9)));
/* 0021225c: lui t1,0x8080 */ set(9,sx(UINT32_C(0x80800000)));
/* 00212260: lw v1,0x4(a2) */ lw(3,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 00212264: andi a3,a3,0xffff */ set(7,cpu(7)&UINT32_C(0x0000ffff));
/* 00212268: sll a3,a3,0x3 */ set(7,sx((uint32_t)cpu(7)<<3));
/* 0021226c: move t4,a0 */ set(12,cpu(4));
/* 00212270: addu v1,v1,a3 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 00212274: move a0,a1 */ set(4,cpu(5));
/* 00212278: lhu a1,0x6(v1) */ set(5,half(ea(3,(int32_t)UINT32_C(0x00000006))));
/* 0021227c: ori t1,t1,0x8080 */ set(9,cpu(9)|UINT32_C(0x00008080));
/* 00212280: lw t3,0x0(a2) */ lw(11,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 00212284: sll v0,a1,0x3 */ set(2,sx((uint32_t)cpu(5)<<3));
/* 00212288: lbu t2,0x4(v1) */ set(10,byte(ea(3,(int32_t)UINT32_C(0x00000004))));
/* 0021228c: subu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(5)));
/* 00212290: lh a2,0x0(v1) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00212294: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 00212298: lh a3,0x2(v1) */ set(7,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000002))));
/* 0021229c: addu t3,t3,v0 */ set(11,sx((uint32_t)cpu(11)+(uint32_t)cpu(2)));
/* 002122a0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002122a4: lb v1,0x0(t3) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(11,(int32_t)UINT32_C(0x00000000))));
/* 002122a8: addiu a1,t3,0x2 */ set(5,sx((uint32_t)cpu(11)+UINT32_C(0x00000002)));
/* 002122ac: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 002122b0: addu v1,v1,t0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(8)));
/* 002122b4: move t0,t4 */ set(8,cpu(12));
/* 002122b8: lw t3,0x0(v1) */ lw(11,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002122bc: j 0x00214550 */ /* delay 002122c0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00214550();return;
}
static void body_002122c8(void){
uint64_t incoming=cpu(31);
/* 002122c8: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 002122cc: sd s1,0x48(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002122d0: move s1,t1 */ set(17,cpu(9));
/* 002122d4: sd s2,0x50(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002122d8: move s2,t0 */ set(18,cpu(8));
/* 002122dc: lw t1,0x78(sp) */ lw(9,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002122e0: lw t0,0x70(sp) */ lw(8,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002122e4: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002122e8: move s0,a3 */ set(16,cpu(7));
/* 002122ec: sd s3,0x58(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002122f0: move s3,a1 */ set(19,cpu(5));
/* 002122f4: andi a3,t3,0xffff */ set(7,cpu(11)&UINT32_C(0x0000ffff));
/* 002122f8: sd s4,0x60(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002122fc: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 00212300: move s4,a0 */ set(20,cpu(4));
/* 00212304: move a0,a2 */ set(4,cpu(6));
/* 00212308: sd ra,0x68(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 0021230c: jal 0x00212248 */ set(31,UINT64_C(0x00212314));/* delay 00212310 */ set(6,cpu(10)&UINT32_C(0x000000ff));body_00212248();
/* 00212314: li a0,0x3e8 */ set(4,sx(UINT32_C(0x000003e8)));
/* 00212318: lhu v0,0x1c(sp) */ set(2,half(ea(29,(int32_t)UINT32_C(0x0000001c))));
/* 0021231c: beql a0,zero,0x00212324 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 00212320 */ nocturneBattlePanelAnalyzeTrap(7u,UINT32_C(0x00212320));goto L_00212324;}}
L_00212324:;
/* 00212324: lhu v1,0x1e(sp) */ set(3,half(ea(29,(int32_t)UINT32_C(0x0000001e))));
/* 00212328: lhu t4,0x18(sp) */ set(12,half(ea(29,(int32_t)UINT32_C(0x00000018))));
/* 0021232c: li a2,0x3e8 */ set(6,sx(UINT32_C(0x000003e8)));
/* 00212330: lhu a1,0x1a(sp) */ set(5,half(ea(29,(int32_t)UINT32_C(0x0000001a))));
/* 00212334: li a3,0x3e8 */ set(7,sx(UINT32_C(0x000003e8)));
/* 00212338: subu v0,v0,t4 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(12)));
/* 0021233c: li t2,0x3e8 */ set(10,sx(UINT32_C(0x000003e8)));
/* 00212340: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
/* 00212344: mult v0,v0,s0 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(16),1,0);
/* 00212348: mult1 v1,v1,s2 */ nativeMultiply(3,(uint32_t)cpu(3),(uint32_t)cpu(18),1,1);
/* 0021234c: move t0,s1 */ set(8,cpu(17));
/* 00212350: addiu t1,sp,0x10 */ set(9,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 00212354: move t3,zero */ set(11,cpu(0));
/* 00212358: div v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),1,0);
/* 0021235c: div1 v1,a0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(4),1,1);
/* 00212360: mflo v0 */ set(2,nocturneEffectHostLo());
/* 00212364: mflo1 v1 */ set(3,nocturneBattleActionFormulaSecondaryLo());
/* 00212368: addu v0,t4,v0 */ set(2,sx((uint32_t)cpu(12)+(uint32_t)cpu(2)));
/* 0021236c: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 00212370: sh v0,0x1c(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint16_t)cpu(2));
/* 00212374: sh a1,0x1e(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000001e)),(uint16_t)cpu(5));
/* 00212378: lhu v1,0x16(sp) */ set(3,half(ea(29,(int32_t)UINT32_C(0x00000016))));
/* 0021237c: lhu v0,0x14(sp) */ set(2,half(ea(29,(int32_t)UINT32_C(0x00000014))));
/* 00212380: mult v1,v1,s2 */ nativeMultiply(3,(uint32_t)cpu(3),(uint32_t)cpu(18),1,0);
/* 00212384: mult1 v0,v0,s0 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(16),1,1);
/* 00212388: div v1,a0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(4),1,0);
/* 0021238c: div1 v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),1,1);
/* 00212390: mflo v1 */ set(3,nocturneEffectHostLo());
/* 00212394: mflo1 v0 */ set(2,nocturneBattleActionFormulaSecondaryLo());
/* 00212398: andi a1,v0,0xffff */ set(5,cpu(2)&UINT32_C(0x0000ffff));
/* 0021239c: sh v0,0x14(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(2));
/* 002123a0: sltiu a1,a1,0x4 */ set(5,cpu(5)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000004));
/* 002123a4: beq s0,zero,0x002123c0 */ {int taken=(cpu(16)==cpu(0));/* delay 002123a8 */ sh(ea(29,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(3));if(taken){goto L_002123c0;}}
/* 002123ac: beq a1,zero,0x002123c0 */ {int taken=(cpu(5)==cpu(0));/* delay 002123b0 */ set(2,sx((uint32_t)cpu(12)+UINT32_C(0x00000040)));if(taken){goto L_002123c0;}}
/* 002123b4: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 002123b8: sh v0,0x1c(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint16_t)cpu(2));
/* 002123bc: sh v1,0x14(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(3));
L_002123c0:;
/* 002123c0: beq s2,zero,0x002123e8 */ {int taken=(cpu(18)==cpu(0));/* delay 002123c4 */ set(2,half(ea(29,(int32_t)UINT32_C(0x00000016))));if(taken){goto L_002123e8;}}
/* 002123c8: sltiu v0,v0,0x4 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000004));
/* 002123cc: beq v0,zero,0x002123ec */ {int taken=(cpu(2)==cpu(0));/* delay 002123d0 */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002123ec;}}
/* 002123d4: lhu v0,0x1a(sp) */ set(2,half(ea(29,(int32_t)UINT32_C(0x0000001a))));
/* 002123d8: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 002123dc: sh v1,0x16(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(3));
/* 002123e0: addiu v0,v0,0x40 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000040)));
/* 002123e4: sh v0,0x1e(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000001e)),(uint16_t)cpu(2));
L_002123e8:;
/* 002123e8: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
L_002123ec:;
/* 002123ec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002123f0: lw a1,0x24(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 002123f4: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002123f8: addu a0,s4,a0 */ set(4,sx((uint32_t)cpu(20)+(uint32_t)cpu(4)));
/* 002123fc: lw v0,0x80(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00212400: addu a1,s3,a1 */ set(5,sx((uint32_t)cpu(19)+(uint32_t)cpu(5)));
/* 00212404: lhu a2,0x14(sp) */ set(6,half(ea(29,(int32_t)UINT32_C(0x00000014))));
/* 00212408: lhu a3,0x16(sp) */ set(7,half(ea(29,(int32_t)UINT32_C(0x00000016))));
/* 0021240c: lbu t2,0x30(sp) */ set(10,byte(ea(29,(int32_t)UINT32_C(0x00000030))));
/* 00212410: jal 0x00214730 */ set(31,UINT64_C(0x00212418));/* delay 00212414 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_00214730();
/* 00212418: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0021241c: ld s1,0x48(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00212420: ld s2,0x50(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00212424: ld s3,0x58(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00212428: ld s4,0x60(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0021242c: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00212430: jr ra */ {uint64_t target=cpu(31);/* delay 00212434 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
static void body_00212878(void){
uint64_t incoming=cpu(31);
/* 00212878: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 0021287c: sd s0,0x40(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00212880: move s0,a3 */ set(16,cpu(7));
/* 00212884: sd s1,0x48(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00212888: move s1,a0 */ set(17,cpu(4));
/* 0021288c: sd s2,0x50(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00212890: move s2,a1 */ set(18,cpu(5));
/* 00212894: move a0,a2 */ set(4,cpu(6));
/* 00212898: andi a2,t0,0xff */ set(6,cpu(8)&UINT32_C(0x000000ff));
/* 0021289c: addiu a1,sp,0x10 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002128a0: andi a3,t1,0xffff */ set(7,cpu(9)&UINT32_C(0x0000ffff));
/* 002128a4: move t0,t2 */ set(8,cpu(10));
/* 002128a8: move t1,t3 */ set(9,cpu(11));
/* 002128ac: sd s3,0x58(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002128b0: sd ra,0x60(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002128b4: jal 0x00212248 */ set(31,UINT64_C(0x002128bc));/* delay 002128b8 */ lw(19,ea(29,(int32_t)UINT32_C(0x00000070)));body_00212248();
/* 002128bc: lw a0,0x20(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002128c0: addiu t1,sp,0x10 */ set(9,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002128c4: lw a1,0x24(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 002128c8: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002128cc: lhu a2,0x14(sp) */ set(6,half(ea(29,(int32_t)UINT32_C(0x00000014))));
/* 002128d0: move t0,s0 */ set(8,cpu(16));
/* 002128d4: lhu a3,0x16(sp) */ set(7,half(ea(29,(int32_t)UINT32_C(0x00000016))));
/* 002128d8: addu a0,s1,a0 */ set(4,sx((uint32_t)cpu(17)+(uint32_t)cpu(4)));
/* 002128dc: lbu t2,0x30(sp) */ set(10,byte(ea(29,(int32_t)UINT32_C(0x00000030))));
/* 002128e0: addu a1,s2,a1 */ set(5,sx((uint32_t)cpu(18)+(uint32_t)cpu(5)));
/* 002128e4: move t3,zero */ set(11,cpu(0));
/* 002128e8: sw s3,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));
/* 002128ec: jal 0x00214730 */ set(31,UINT64_C(0x002128f4));/* delay 002128f0 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));body_00214730();
/* 002128f4: ld s0,0x40(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002128f8: ld s1,0x48(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002128fc: ld s2,0x50(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00212900: ld s3,0x58(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00212904: ld ra,0x60(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00212908: jr ra */ {uint64_t target=cpu(31);/* delay 0021290c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
static void body_00214530(void){
uint64_t incoming=cpu(31);
/* 00214530: srl v0,a1,0x18 */ set(2,sx((uint32_t)cpu(5)>>24));
/* 00214534: srl v1,a1,0x10 */ set(3,sx((uint32_t)cpu(5)>>16));
/* 00214538: srl a2,a1,0x8 */ set(6,sx((uint32_t)cpu(5)>>8));
/* 0021453c: sb a1,0x1f(a0) */ sb(ea(4,(int32_t)UINT32_C(0x0000001f)),(uint8_t)cpu(5));
/* 00214540: sb v0,0x1c(a0) */ sb(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(2));
/* 00214544: sb v1,0x1d(a0) */ sb(ea(4,(int32_t)UINT32_C(0x0000001d)),(uint8_t)cpu(3));
/* 00214548: jr ra */ {uint64_t target=cpu(31);/* delay 0021454c */ sb(ea(4,(int32_t)UINT32_C(0x0000001e)),(uint8_t)cpu(6));checkReturn(target,incoming);return;}
}
static void body_00214550(void){
uint64_t incoming=cpu(31);
/* 00214550: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00214554: sll a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)<<4));
/* 00214558: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0021455c: move s1,a0 */ set(17,cpu(4));
/* 00214560: sll a3,a3,0x3 */ set(7,sx((uint32_t)cpu(7)<<3));
/* 00214564: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00214568: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0021456c: move s0,a1 */ set(16,cpu(5));
/* 00214570: sw a2,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(6));
/* 00214574: move a1,t1 */ set(5,cpu(9));
/* 00214578: sw t3,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(11));
/* 0021457c: sw a3,0x14(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(7));
/* 00214580: sw t0,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(8));
/* 00214584: jal 0x00214530 */ set(31,UINT64_C(0x0021458c));/* delay 00214588 */ sb(ea(17,(int32_t)UINT32_C(0x00000020)),(uint8_t)cpu(10));body_00214530();
/* 0021458c: addiu v1,s1,0x4 */ set(3,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
/* 00214590: ldl v0,0x7(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000007)),1);
/* 00214594: ldr v0,0x0(s0) */ loadPartial(2,ea(16,(int32_t)UINT32_C(0x00000000)),0);
/* 00214598: lwl a0,0xb(s0) */ analyzeLoadPartialWord(4u,ea(16u,(int32_t)UINT32_C(0x0000000b)),1);
/* 0021459c: lwr a0,0x8(s0) */ analyzeLoadPartialWord(4u,ea(16u,(int32_t)UINT32_C(0x00000008)),0);
/* 002145a0: sdl v0,0x7(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000007)),2,1);
/* 002145a4: sdr v0,0x0(v1) */ storePartial(ea(3,(int32_t)UINT32_C(0x00000000)),2,0);
/* 002145a8: swl a0,0xb(v1) */ analyzeStorePartialWord(ea(3u,(int32_t)UINT32_C(0x0000000b)),4u,1);
/* 002145ac: swr a0,0x8(v1) */ analyzeStorePartialWord(ea(3u,(int32_t)UINT32_C(0x00000008)),4u,0);
/* 002145b0: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 002145b4: bnel v0,zero,0x002145c8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002145b8 */ set(2,half(ea(17,(int32_t)UINT32_C(0x00000006))));goto L_002145c8;}}
/* 002145bc: lhu v0,0xc(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002145c0: sh v0,0x0(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));
/* 002145c4: lhu v0,0x6(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x00000006))));
L_002145c8:;
/* 002145c8: bne v0,zero,0x002145d4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002145cc */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000e))));if(taken){goto L_002145d4;}}
/* 002145d0: sh v0,0x6(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(2));
L_002145d4:;
/* 002145d4: lhu a0,0x8(s1) */ set(4,half(ea(17,(int32_t)UINT32_C(0x00000008))));
/* 002145d8: lhu a1,0xa(s1) */ set(5,half(ea(17,(int32_t)UINT32_C(0x0000000a))));
/* 002145dc: lhu v1,0xc(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002145e0: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002145e4: sll a1,a1,0x4 */ set(5,sx((uint32_t)cpu(5)<<4));
/* 002145e8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002145ec: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 002145f0: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 002145f4: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 002145f8: sh v0,0xe(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(2));
/* 002145fc: sh a0,0x8(s1) */ sh(ea(17,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(4));
/* 00214600: sh a1,0xa(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(5));
/* 00214604: sh v1,0xc(s1) */ sh(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(3));
/* 00214608: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0021460c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00214610: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00214614: jr ra */ {uint64_t target=cpu(31);/* delay 00214618 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00214730(void){
uint64_t incoming=cpu(31);
/* 00214730: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 00214734: andi t3,t3,0xff */ set(11,cpu(11)&UINT32_C(0x000000ff));
/* 00214738: lbu v0,0x70(sp) */ set(2,byte(ea(29,(int32_t)UINT32_C(0x00000070))));
/* 0021473c: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00214740: move s0,t0 */ set(16,cpu(8));
/* 00214744: sd s1,0x28(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00214748: move s1,t1 */ set(17,cpu(9));
/* 0021474c: sd s3,0x38(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00214750: move s3,a0 */ set(19,cpu(4));
/* 00214754: sd s4,0x40(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00214758: andi s4,t2,0xff */ set(20,cpu(10)&UINT32_C(0x000000ff));
/* 0021475c: sd s5,0x48(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 00214760: move s5,a1 */ set(21,cpu(5));
/* 00214764: sd s6,0x50(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00214768: move s6,a2 */ set(22,cpu(6));
/* 0021476c: sd s7,0x58(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00214770: move s7,a3 */ set(23,cpu(7));
/* 00214774: sd s8,0x60(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00214778: sd s2,0x30(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0021477c: sd ra,0x68(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00214780: sw t3,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(11));
/* 00214784: bne v0,zero,0x002147a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00214788 */ lw(30,ea(29,(int32_t)UINT32_C(0x00000078)));if(taken){goto L_002147a8;}}
/* 0021478c: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00214790: move a1,zero */ set(5,cpu(0));
/* 00214794: jal 0x002ab0f8 */ set(31,UINT64_C(0x0021479c));/* delay 00214798 */ set(6,sx(UINT32_C(0x00000001)));body_002ab0f8();
/* 0021479c: b 0x002147bc */ /* delay 002147a0 */ set(5,sx(UINT32_C(0x00000001)));goto L_002147bc;
L_002147a8:;
/* 002147a8: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002147ac: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002147b0: jal 0x002ab0f8 */ set(31,UINT64_C(0x002147b8));/* delay 002147b4 */ set(6,sx(UINT32_C(0x00000001)));body_002ab0f8();
/* 002147b8: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
L_002147bc:;
/* 002147bc: jal 0x002b9d68 */ set(31,UINT64_C(0x002147c4));/* delay 002147c0 */ set(4,sx(UINT32_C(0x00000005)));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002b9d68),UINT32_C(0x002147bc));
/* 002147c4: jal 0x002acb50 */ set(31,UINT64_C(0x002147cc));/* delay 002147c8 */ set(4,cpu(2));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002acb50),UINT32_C(0x002147c4));
/* 002147cc: li a1,0x156 */ set(5,sx(UINT32_C(0x00000156)));
/* 002147d0: move s2,v0 */ set(18,cpu(2));
/* 002147d4: li a2,0x5 */ set(6,sx(UINT32_C(0x00000005)));
/* 002147d8: lui a3,0x4 */ set(7,sx(UINT32_C(0x00040000)));
/* 002147dc: ori a3,a3,0x3431 */ set(7,cpu(7)|UINT32_C(0x00003431));
/* 002147e0: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 002147e4: jal 0x002b9d80 */ set(31,UINT64_C(0x002147ec));/* delay 002147e8 */ set(4,cpu(18));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002b9d80),UINT32_C(0x002147e4));
/* 002147ec: jal 0x002b9d78 */ set(31,UINT64_C(0x002147f4));/* delay 002147f0 */ set(4,cpu(18));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002b9d78),UINT32_C(0x002147ec));
/* 002147f4: addiu t2,s3,0x6ff8 */ set(10,sx((uint32_t)cpu(19)+UINT32_C(0x00006ff8)));
/* 002147f8: move t3,v0 */ set(11,cpu(2));
/* 002147fc: lhu v0,0xc(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 00214800: lhu a1,0x8(s1) */ set(5,half(ea(17,(int32_t)UINT32_C(0x00000008))));
/* 00214804: andi a2,s4,0x1 */ set(6,cpu(20)&UINT32_C(0x00000001));
/* 00214808: lhu v1,0xa(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000a))));
/* 0021480c: addiu t1,s5,0x78fc */ set(9,sx((uint32_t)cpu(21)+UINT32_C(0x000078fc)));
/* 00214810: lhu a0,0xe(s1) */ set(4,half(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 00214814: sll a3,s6,0x4 */ set(7,sx((uint32_t)cpu(22)<<4));
/* 00214818: sll t0,s7,0x3 */ set(8,sx((uint32_t)cpu(23)<<3));
/* 0021481c: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 00214820: addiu v0,v0,0x8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000008)));
/* 00214824: addiu v1,v1,0x8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 00214828: addiu a0,a0,0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
/* 0021482c: andi a2,a2,0xff */ set(6,cpu(6)&UINT32_C(0x000000ff));
/* 00214830: sw a1,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
/* 00214834: addu a3,t2,a3 */ set(7,sx((uint32_t)cpu(10)+(uint32_t)cpu(7)));
/* 00214838: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 0021483c: addu t0,t1,t0 */ set(8,sx((uint32_t)cpu(9)+(uint32_t)cpu(8)));
/* 00214840: sw v1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
/* 00214844: beq a2,zero,0x00214858 */ {int taken=(cpu(6)==cpu(0));/* delay 00214848 */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));if(taken){goto L_00214858;}}
/* 0021484c: move v0,t2 */ set(2,cpu(10));
/* 00214850: move t2,a3 */ set(10,cpu(7));
/* 00214854: move a3,v0 */ set(7,cpu(2));
L_00214858:;
/* 00214858: andi v0,s4,0x2 */ set(2,cpu(20)&UINT32_C(0x00000002));
/* 0021485c: beq v0,zero,0x0021486c */ {int taken=(cpu(2)==cpu(0));/* delay 00214860 */ set(2,cpu(9));if(taken){goto L_0021486c;}}
/* 00214864: move t1,t0 */ set(9,cpu(8));
/* 00214868: move t0,v0 */ set(8,cpu(2));
L_0021486c:;
/* 0021486c: bnel s0,zero,0x002148a0 */ {int taken=(cpu(16)!=cpu(0));if(taken){/* delay 00214870 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002148a0;}}
/* 00214874: lbu v0,0x1d(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x0000001d))));
/* 00214878: lbu v1,0x1c(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x0000001c))));
/* 0021487c: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 00214880: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 00214884: sd v1,0x0(t3) */ save(3,ea(11,(int32_t)UINT32_C(0x00000000)));
/* 00214888: lbu v0,0x1f(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x0000001f))));
/* 0021488c: lbu v1,0x1e(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x0000001e))));
/* 00214890: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 00214894: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 00214898: b 0x002148d4 */ /* delay 0021489c */ save(3,ea(11,(int32_t)UINT32_C(0x00000008)));goto L_002148d4;
L_002148a0:;
/* 002148a0: lbu a1,0x0(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002148a4: srl v1,v0,0x10 */ set(3,sx((uint32_t)cpu(2)>>16));
/* 002148a8: srl a0,v0,0x8 */ set(4,sx((uint32_t)cpu(2)>>8));
/* 002148ac: andi v1,v1,0xff */ set(3,cpu(3)&UINT32_C(0x000000ff));
/* 002148b0: srl v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)>>24));
/* 002148b4: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 002148b8: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002148bc: andi a0,a0,0xff */ set(4,cpu(4)&UINT32_C(0x000000ff));
/* 002148c0: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002148c4: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002148c8: or a0,a0,a1 */ set(4,cpu(4)|cpu(5));
/* 002148cc: sd v0,0x0(t3) */ save(2,ea(11,(int32_t)UINT32_C(0x00000000)));
/* 002148d0: sd a0,0x8(t3) */ save(4,ea(11,(int32_t)UINT32_C(0x00000008)));
L_002148d4:;
/* 002148d4: lwu a0,0x4(sp) */ set(4,word(ea(29,(int32_t)UINT32_C(0x00000004))));
/* 002148d8: dsll32 v0,t2,0x0 */ set(2,cpu(10)<<32);
/* 002148dc: lwu a1,0xc(sp) */ set(5,word(ea(29,(int32_t)UINT32_C(0x0000000c))));
/* 002148e0: dsll32 v1,a3,0x0 */ set(3,cpu(7)<<32);
/* 002148e4: lwu a2,0x0(sp) */ set(6,word(ea(29,(int32_t)UINT32_C(0x00000000))));
/* 002148e8: dsll32 a0,a0,0x0 */ set(4,cpu(4)<<32);
/* 002148ec: lwu a3,0x8(sp) */ set(7,word(ea(29,(int32_t)UINT32_C(0x00000008))));
/* 002148f0: dsrl32 v0,v0,0x0 */ set(2,cpu(2)>>32);
/* 002148f4: lwu t2,0x18(s1) */ set(10,word(ea(17,(int32_t)UINT32_C(0x00000018))));
/* 002148f8: dsll32 t1,t1,0x0 */ set(9,cpu(9)<<32);
/* 002148fc: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 00214900: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 00214904: dsll32 t0,t0,0x0 */ set(8,cpu(8)<<32);
/* 00214908: or a2,a2,a0 */ set(6,cpu(6)|cpu(4));
/* 0021490c: or v0,v0,t1 */ set(2,cpu(2)|cpu(9));
/* 00214910: or a3,a3,a1 */ set(7,cpu(7)|cpu(5));
/* 00214914: or v1,v1,t0 */ set(3,cpu(3)|cpu(8));
/* 00214918: sd t2,0x48(t3) */ save(10,ea(11,(int32_t)UINT32_C(0x00000048)));
/* 0021491c: sd a2,0x10(t3) */ save(6,ea(11,(int32_t)UINT32_C(0x00000010)));
/* 00214920: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00214924: sd v0,0x20(t3) */ save(2,ea(11,(int32_t)UINT32_C(0x00000020)));
/* 00214928: sd a3,0x30(t3) */ save(7,ea(11,(int32_t)UINT32_C(0x00000030)));
/* 0021492c: sd v1,0x40(t3) */ save(3,ea(11,(int32_t)UINT32_C(0x00000040)));
/* 00214930: sd t2,0x28(t3) */ save(10,ea(11,(int32_t)UINT32_C(0x00000028)));
/* 00214934: lw v0,0x10(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00214938: beq v0,a0,0x00214958 */ {int taken=(cpu(2)==cpu(4));/* delay 0021493c */ lw(3,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_00214958;}}
/* 00214940: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00214944: beq v1,v0,0x00214960 */ {int taken=(cpu(3)==cpu(2));/* delay 00214948 */ set(4,sx(UINT32_C(0x00000044)));if(taken){goto L_00214960;}}
/* 0021494c: b 0x00214978 */ /* delay 00214950 */ goto L_00214978;
L_00214958:;
/* 00214958: b 0x00214964 */ /* delay 0021495c */ set(4,sx(UINT32_C(0x00000048)));goto L_00214964;
L_00214960:;
/* 00214960: li a0,0x42 */ set(4,sx(UINT32_C(0x00000042)));
L_00214964:;
/* 00214964: jal 0x00239df8 */ set(31,UINT64_C(0x0021496c));/* delay 00214968 */ set(5,cpu(30));body_00239df8();
/* 0021496c: b 0x00214980 */ /* delay 00214970 */ goto L_00214980;
L_00214978:;
/* 00214978: jal 0x00239df8 */ set(31,UINT64_C(0x00214980));/* delay 0021497c */ set(5,cpu(30));body_00239df8();
L_00214980:;
/* 00214980: jal 0x002acb50 */ set(31,UINT64_C(0x00214988));/* delay 00214984 */ set(4,sx(UINT32_C(0x00000020)));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002acb50),UINT32_C(0x00214980));
/* 00214988: move s0,v0 */ set(16,cpu(2));
/* 0021498c: jal 0x002acb90 */ set(31,UINT64_C(0x00214994));/* delay 00214990 */ set(4,cpu(16));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002acb90),UINT32_C(0x0021498c));
/* 00214994: move a0,s0 */ set(4,cpu(16));
/* 00214998: lw a1,0x0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0021499c: jal 0x002b9cc8 */ set(31,UINT64_C(0x002149a4));/* delay 002149a0 */ set(6,cpu(0));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002b9cc8),UINT32_C(0x0021499c));
/* 002149a4: move a0,s0 */ set(4,cpu(16));
/* 002149a8: jal 0x002acbb8 */ set(31,UINT64_C(0x002149b0));/* delay 002149ac */ set(5,cpu(18));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002acbb8),UINT32_C(0x002149a8));
/* 002149b0: sll a0,s8,0x5 */ set(4,sx((uint32_t)cpu(30)<<5));
/* 002149b4: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 002149b8: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 002149bc: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 002149c0: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002149c4: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002149cc));/* delay 002149c8 */ set(5,cpu(16));nocturneBattlePanelAnalyzeIndirect(target,UINT32_C(0x002149c4));}
/* 002149cc: li a0,0x44 */ set(4,sx(UINT32_C(0x00000044)));
/* 002149d0: jal 0x00239df8 */ set(31,UINT64_C(0x002149d8));/* delay 002149d4 */ set(5,cpu(30));body_00239df8();
/* 002149d8: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002149dc: ld s1,0x28(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002149e0: ld s2,0x30(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002149e4: ld s3,0x38(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002149e8: ld s4,0x40(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002149ec: ld s5,0x48(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002149f0: ld s6,0x50(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002149f4: ld s7,0x58(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002149f8: ld s8,0x60(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002149fc: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00214a00: jr ra */ {uint64_t target=cpu(31);/* delay 00214a04 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
static void body_00235ff8(void){
uint64_t incoming=cpu(31);
/* 00235ff8: beq a0,zero,0x00236004 */ {int taken=(cpu(4)==cpu(0));/* delay 00235ffc */ set(3,sx(UINT32_C(0x00000080)));if(taken){goto L_00236004;}}
/* 00236000: lbu v1,0x0(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
L_00236004:;
/* 00236004: li v0,-0x100 */ set(2,sx(UINT32_C(0xffffff00)));
/* 00236008: and v0,a1,v0 */ set(2,cpu(5)&cpu(2));
/* 0023600c: jr ra */ {uint64_t target=cpu(31);/* delay 00236010 */ set(2,cpu(2)|cpu(3));checkReturn(target,incoming);return;}
}
static void body_002361c0(void){
uint64_t incoming=cpu(31);
/* 002361c0: addiu sp,sp,-0xa0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff60)));
/* 002361c4: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002361c8: andi s0,t1,0xff */ set(16,cpu(9)&UINT32_C(0x000000ff));
/* 002361cc: sd s3,0x68(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002361d0: andi v1,s0,0x5 */ set(3,cpu(16)&UINT32_C(0x00000005));
/* 002361d4: sd s4,0x70(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002361d8: li s4,0x1 */ set(20,sx(UINT32_C(0x00000001)));
/* 002361dc: sd s5,0x78(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002361e0: li s5,0x1 */ set(21,sx(UINT32_C(0x00000001)));
/* 002361e4: sd s7,0x88(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002361e8: move s7,a0 */ set(23,cpu(4));
/* 002361ec: sd s8,0x90(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002361f0: move s8,a1 */ set(30,cpu(5));
/* 002361f4: sd s1,0x58(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002361f8: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002361fc: sd s6,0x80(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00236200: sd ra,0x98(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00236204: sw a3,0x3c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(7));
/* 00236208: lhu v0,0xe(t0) */ set(2,half(ea(8,(int32_t)UINT32_C(0x0000000e))));
/* 0023620c: sw a3,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(7));
/* 00236210: andi v0,v0,0x800 */ set(2,cpu(2)&UINT32_C(0x00000800));
/* 00236214: sw a2,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(6));
/* 00236218: andi t1,v0,0xffff */ set(9,cpu(2)&UINT32_C(0x0000ffff));
/* 0023621c: sw t2,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(10));
/* 00236220: sw a3,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),(uint32_t)cpu(7));
/* 00236224: sltu s3,zero,t1 */ set(19,cpu(0)<cpu(9));
/* 00236228: beq v1,zero,0x00236238 */ {int taken=(cpu(3)==cpu(0));/* delay 0023622c */ sw(ea(29,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(7));if(taken){goto L_00236238;}}
/* 00236230: lhu s4,0x6(t0) */ set(20,half(ea(8,(int32_t)UINT32_C(0x00000006))));
/* 00236234: lhu s5,0x8(t0) */ set(21,half(ea(8,(int32_t)UINT32_C(0x00000008))));
L_00236238:;
/* 00236238: andi v0,s0,0xa */ set(2,cpu(16)&UINT32_C(0x0000000a));
/* 0023623c: beq v0,zero,0x0023625c */ {int taken=(cpu(2)==cpu(0));/* delay 00236240 */ set(2,cpu(19)|UINT32_C(0x00000004));if(taken){goto L_0023625c;}}
/* 00236244: ori a0,s3,0x2 */ set(4,cpu(19)|UINT32_C(0x00000002));
/* 00236248: xori v1,t1,0x0 */ set(3,cpu(9)^UINT32_C(0x00000000));
/* 0023624c: lhu s5,0xc(t0) */ set(21,half(ea(8,(int32_t)UINT32_C(0x0000000c))));
/* 00236250: move s3,v0 */ set(19,cpu(2));
/* 00236254: lhu s4,0xa(t0) */ set(20,half(ea(8,(int32_t)UINT32_C(0x0000000a))));
/* 00236258: movz s3,a0,v1 */ if(cpu(3)==0){set(19,cpu(4));}
L_0023625c:;
/* 0023625c: li a0,0x3e7 */ set(4,sx(UINT32_C(0x000003e7)));
/* 00236260: slti a1,s5,0x3e8 */ set(5,(int64_t)cpu(21)<(int64_t)(int32_t)UINT32_C(0x000003e8));
/* 00236264: slti v0,s4,0x3e8 */ set(2,(int64_t)cpu(20)<(int64_t)(int32_t)UINT32_C(0x000003e8));
/* 00236268: andi v1,s3,0x1 */ set(3,cpu(19)&UINT32_C(0x00000001));
/* 0023626c: movz s4,a0,v0 */ if(cpu(2)==0){set(20,cpu(4));}
/* 00236270: beq v1,zero,0x00236298 */ {int taken=(cpu(3)==cpu(0));/* delay 00236274 */ if(cpu(5)==0){set(21,cpu(4));}if(taken){goto L_00236298;}}
/* 00236278: addiu v0,sp,0x30 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 0023627c: lui a1,0x754b */ set(5,sx(UINT32_C(0x754b0000)));
/* 00236280: move a0,v0 */ set(4,cpu(2));
/* 00236284: jal 0x00235ff8 */ set(31,UINT64_C(0x0023628c));/* delay 00236288 */ set(5,cpu(5)|UINT32_C(0x00003d80));body_00235ff8();
/* 0023628c: b 0x002362b0 */ /* delay 00236290 */ set(22,cpu(2));goto L_002362b0;
L_00236298:;
/* 00236298: addiu v1,sp,0x30 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 0023629c: lui a1,0xa09d */ set(5,sx(UINT32_C(0xa09d0000)));
/* 002362a0: move a0,v1 */ set(4,cpu(3));
/* 002362a4: jal 0x00235ff8 */ set(31,UINT64_C(0x002362ac));/* delay 002362a8 */ set(5,cpu(5)|UINT32_C(0x0000c380));body_00235ff8();
/* 002362ac: move s6,v0 */ set(22,cpu(2));
L_002362b0:;
/* 002362b0: andi v0,s0,0xc */ set(2,cpu(16)&UINT32_C(0x0000000c));
/* 002362b4: beq v0,zero,0x002362d0 */ {int taken=(cpu(2)==cpu(0));/* delay 002362b8 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));if(taken){goto L_002362d0;}}
/* 002362bc: lui a1,0xffbd */ set(5,sx(UINT32_C(0xffbd0000)));
/* 002362c0: move a0,v0 */ set(4,cpu(2));
/* 002362c4: jal 0x00235ff8 */ set(31,UINT64_C(0x002362cc));/* delay 002362c8 */ set(5,cpu(5)|UINT32_C(0x00008380));body_00235ff8();
/* 002362cc: move s6,v0 */ set(22,cpu(2));
L_002362d0:;
/* 002362d0: lw v1,0x40(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002362d4: lui a0,0x34 */ set(4,sx(UINT32_C(0x00340000)));
/* 002362d8: lui v0,0x34 */ set(2,sx(UINT32_C(0x00340000)));
/* 002362dc: addiu s0,a0,0x5d88 */ set(16,sx((uint32_t)cpu(4)+UINT32_C(0x00005d88)));
/* 002362e0: sll s2,v1,0x4 */ set(18,sx((uint32_t)cpu(3)<<4));
/* 002362e4: addiu v1,sp,0x30 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 002362e8: addiu s1,v0,0x5100 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00005100)));
/* 002362ec: lw v0,0x44(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002362f0: move a3,v1 */ set(7,cpu(3));
/* 002362f4: move a0,s7 */ set(4,cpu(23));
/* 002362f8: move a1,s8 */ set(5,cpu(30));
/* 002362fc: move a2,s2 */ set(6,cpu(18));
/* 00236300: li t0,0x2 */ set(8,sx(UINT32_C(0x00000002)));
/* 00236304: li t1,0x6 */ set(9,sx(UINT32_C(0x00000006)));
/* 00236308: move t2,s0 */ set(10,cpu(16));
/* 0023630c: move t3,s1 */ set(11,cpu(17));
/* 00236310: jal 0x00212878 */ set(31,UINT64_C(0x00236318));/* delay 00236314 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));body_00212878();
/* 00236318: lw v0,0x44(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 0023631c: addiu v1,sp,0x30 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 00236320: move a3,v1 */ set(7,cpu(3));
/* 00236324: move a0,s7 */ set(4,cpu(23));
/* 00236328: move t2,s0 */ set(10,cpu(16));
/* 0023632c: move t3,s1 */ set(11,cpu(17));
/* 00236330: move a1,s8 */ set(5,cpu(30));
/* 00236334: move a2,s2 */ set(6,cpu(18));
/* 00236338: li t0,0x2 */ set(8,sx(UINT32_C(0x00000002)));
/* 0023633c: li t1,0x5 */ set(9,sx(UINT32_C(0x00000005)));
/* 00236340: jal 0x00212878 */ set(31,UINT64_C(0x00236348));/* delay 00236344 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));body_00212878();
/* 00236348: sll v0,s4,0x5 */ set(2,sx((uint32_t)cpu(20)<<5));
/* 0023634c: beql s5,zero,0x00236354 */ {int taken=(cpu(21)==cpu(0));if(taken){/* delay 00236350 */ nocturneBattlePanelAnalyzeTrap(7u,UINT32_C(0x00236350));goto L_00236354;}}
L_00236354:;
/* 00236354: subu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(20)));
/* 00236358: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0023635c: addu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(20)));
/* 00236360: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00236364: div v0,s5 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(21),1,0);
/* 00236368: mflo a3 */ set(7,nocturneEffectHostLo());
/* 0023636c: beq a3,zero,0x002363d8 */ {int taken=(cpu(7)==cpu(0));/* delay 00236370 */ set(2,cpu(19)&UINT32_C(0x0000000e));if(taken){goto L_002363d8;}}
/* 00236374: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00236378: srl a0,v0,0x1 */ set(4,sx((uint32_t)cpu(2)>>1));
/* 0023637c: beq a0,v1,0x00236398 */ {int taken=(cpu(4)==cpu(3));/* delay 00236380 */ set(11,sx(UINT32_C(0x00000008)));if(taken){goto L_00236398;}}
/* 00236384: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 00236388: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 0023638c: xor v0,a0,v0 */ set(2,cpu(4)^cpu(2));
/* 00236390: li t3,0xb */ set(11,sx(UINT32_C(0x0000000b)));
/* 00236394: movn t3,v1,v0 */ if(cpu(2)!=0){set(11,cpu(3));}
L_00236398:;
/* 00236398: lui v1,0x34 */ set(3,sx(UINT32_C(0x00340000)));
/* 0023639c: lui a0,0x34 */ set(4,sx(UINT32_C(0x00340000)));
/* 002363a0: addiu v0,v1,0x5d88 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00005d88)));
/* 002363a4: addiu v1,a0,0x5100 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00005100)));
/* 002363a8: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002363ac: addiu a0,sp,0x30 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 002363b0: lw v0,0x44(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002363b4: move t1,a0 */ set(9,cpu(4));
/* 002363b8: move a2,s2 */ set(6,cpu(18));
/* 002363bc: move a1,s8 */ set(5,cpu(30));
/* 002363c0: move a0,s7 */ set(4,cpu(23));
/* 002363c4: li t0,0x3e8 */ set(8,sx(UINT32_C(0x000003e8)));
/* 002363c8: li t2,0x2 */ set(10,sx(UINT32_C(0x00000002)));
/* 002363cc: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002363d0: jal 0x002122c8 */ set(31,UINT64_C(0x002363d8));/* delay 002363d4 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));body_002122c8();
L_002363d8:;
/* 002363d8: lui s0,0x55 */ set(16,sx(UINT32_C(0x00550000)));
/* 002363dc: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002363e0: addiu s0,s0,-0x160 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xfffffea0)));
/* 002363e4: move a2,s4 */ set(6,cpu(20));
/* 002363e8: move a1,s0 */ set(5,cpu(16));
/* 002363ec: jal 0x002d5690 */ set(31,UINT64_C(0x002363f4));/* delay 002363f0 */ set(17,sx((uint32_t)cpu(23)+UINT32_C(0x00000050)));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002d5690),UINT32_C(0x002363ec));
/* 002363f4: move a0,s1 */ set(4,cpu(17));
/* 002363f8: lw a2,0x40(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002363fc: addiu t0,sp,0x20 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 00236400: move a3,s6 */ set(7,cpu(22));
/* 00236404: move a1,s8 */ set(5,cpu(30));
/* 00236408: move t1,zero */ set(9,cpu(0));
/* 0023640c: jal 0x001ca430 */ set(31,UINT64_C(0x00236414));/* delay 00236410 */ set(17,sx((uint32_t)cpu(23)+UINT32_C(0x000002c0)));nocturneBattlePanelAnalyzeCall(UINT32_C(0x001ca430),UINT32_C(0x0023640c));
/* 00236414: move a1,s0 */ set(5,cpu(16));
/* 00236418: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 0023641c: move a2,s5 */ set(6,cpu(21));
/* 00236420: jal 0x002d5690 */ set(31,UINT64_C(0x00236428));/* delay 00236424 */ set(18,cpu(2));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002d5690),UINT32_C(0x00236420));
/* 00236428: lw a2,0x40(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0023642c: addiu t0,sp,0x20 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 00236430: move a3,s6 */ set(7,cpu(22));
/* 00236434: move t1,s2 */ set(9,cpu(18));
/* 00236438: move a0,s1 */ set(4,cpu(17));
/* 0023643c: jal 0x001ca430 */ set(31,UINT64_C(0x00236444));/* delay 00236440 */ set(5,cpu(30));nocturneBattlePanelAnalyzeCall(UINT32_C(0x001ca430),UINT32_C(0x0023643c));
/* 00236444: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00236448: move s2,v0 */ set(18,cpu(2));
/* 0023644c: li a2,0x47 */ set(6,sx(UINT32_C(0x00000047)));
/* 00236450: jal 0x001c7e38 */ set(31,UINT64_C(0x00236458));/* delay 00236454 */ set(4,cpu(18));nocturneBattlePanelAnalyzeCall(UINT32_C(0x001c7e38),UINT32_C(0x00236450));
/* 00236458: jal 0x001c6ff8 */ set(31,UINT64_C(0x00236460));/* delay 0023645c */ set(4,cpu(18));nocturneBattlePanelAnalyzeCall(UINT32_C(0x001c6ff8),UINT32_C(0x00236458));
/* 00236460: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 00236464: ld s1,0x58(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 00236468: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 0023646c: ld s3,0x68(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00236470: ld s4,0x70(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 00236474: ld s5,0x78(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00236478: ld s6,0x80(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 0023647c: ld s7,0x88(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 00236480: ld s8,0x90(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 00236484: ld ra,0x98(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00236488: jr ra */ {uint64_t target=cpu(31);/* delay 0023648c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000a0)));checkReturn(target,incoming);return;}
}
static void body_00239d20(void){
uint64_t incoming=cpu(31);
/* 00239d20: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00239d24: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00239d28: move s0,a1 */ set(16,cpu(5));
/* 00239d2c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00239d30: move s1,a0 */ set(17,cpu(4));
/* 00239d34: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00239d38: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 00239d3c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00239d40: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00239d44: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00239d48: jal 0x002b9d68 */ set(31,UINT64_C(0x00239d50));/* delay 00239d4c */ set(19,cpu(6));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002b9d68),UINT32_C(0x00239d48));
/* 00239d50: jal 0x002acb50 */ set(31,UINT64_C(0x00239d58));/* delay 00239d54 */ set(4,cpu(2));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002acb50),UINT32_C(0x00239d50));
/* 00239d58: move a1,zero */ set(5,cpu(0));
/* 00239d5c: move s2,v0 */ set(18,cpu(2));
/* 00239d60: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 00239d64: move a0,s2 */ set(4,cpu(18));
/* 00239d68: li a3,0xe */ set(7,sx(UINT32_C(0x0000000e)));
/* 00239d6c: jal 0x002b9d80 */ set(31,UINT64_C(0x00239d74));/* delay 00239d70 */ set(8,sx(UINT32_C(0x00000001)));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002b9d80),UINT32_C(0x00239d6c));
/* 00239d74: jal 0x002b9d78 */ set(31,UINT64_C(0x00239d7c));/* delay 00239d78 */ set(4,cpu(18));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002b9d78),UINT32_C(0x00239d74));
/* 00239d7c: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 00239d80: move v1,v0 */ set(3,cpu(2));
/* 00239d84: bne s0,zero,0x00239d98 */ {int taken=(cpu(16)!=cpu(0));/* delay 00239d88 */ save(17,ea(3,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00239d98;}}
/* 00239d8c: b 0x00239d9c */ /* delay 00239d90 */ set(2,sx(UINT32_C(0x00000042)));goto L_00239d9c;
L_00239d98:;
/* 00239d98: li v0,0x43 */ set(2,sx(UINT32_C(0x00000043)));
L_00239d9c:;
/* 00239d9c: jal 0x002acb50 */ set(31,UINT64_C(0x00239da4));/* delay 00239da0 */ save(2,ea(3,(int32_t)UINT32_C(0x00000008)));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002acb50),UINT32_C(0x00239d9c));
/* 00239da4: move s0,v0 */ set(16,cpu(2));
/* 00239da8: jal 0x002acb90 */ set(31,UINT64_C(0x00239db0));/* delay 00239dac */ set(4,cpu(16));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002acb90),UINT32_C(0x00239da8));
/* 00239db0: move a0,s0 */ set(4,cpu(16));
/* 00239db4: jal 0x002acbb8 */ set(31,UINT64_C(0x00239dbc));/* delay 00239db8 */ set(5,cpu(18));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002acbb8),UINT32_C(0x00239db4));
/* 00239dbc: sll a0,s3,0x5 */ set(4,sx((uint32_t)cpu(19)<<5));
/* 00239dc0: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00239dc4: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 00239dc8: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00239dcc: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00239dd0: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00239dd8));/* delay 00239dd4 */ set(5,cpu(16));nocturneBattlePanelAnalyzeIndirect(target,UINT32_C(0x00239dd0));}
/* 00239dd8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00239ddc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00239de0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00239de4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00239de8: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00239dec: jr ra */ {uint64_t target=cpu(31);/* delay 00239df0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00239df8(void){
uint64_t incoming=cpu(31);
/* 00239df8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00239dfc: move a2,a1 */ set(6,cpu(5));
/* 00239e00: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00239e04: move a1,zero */ set(5,cpu(0));
/* 00239e08: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00239e0c: j 0x00239d20 */ /* delay 00239e10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00239d20();return;
}
static void body_00245d18(void){
uint64_t incoming=cpu(31);
/* 00245d18: lhu v0,0x14(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000014))));
/* 00245d1c: li a0,0x63 */ set(4,sx(UINT32_C(0x00000063)));
/* 00245d20: slti v1,v0,0x64 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000064));
/* 00245d24: jr ra */ {uint64_t target=cpu(31);/* delay 00245d28 */ if(cpu(3)==0){set(2,cpu(4));}checkReturn(target,incoming);return;}
}
static void body_00279c58(void){
uint64_t incoming=cpu(31);
/* 00279c58: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00279c5c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00279c60: jal 0x00281e28 */ set(31,UINT64_C(0x00279c68));/* delay 00279c64 */ nocturneBattlePanelAnalyzeCall(UINT32_C(0x00281e28),UINT32_C(0x00279c60));
/* 00279c68: jal 0x00282268 */ set(31,UINT64_C(0x00279c70));/* delay 00279c6c */ body_00282268();
/* 00279c70: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00279c74: j 0x0027c338 */ /* delay 00279c78 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));goto L_0027c338;
L_0027c338:;
/* 0027c338: jr ra */ {uint64_t target=cpu(31);/* delay 0027c33c */ sb(ea(28,(int32_t)UINT32_C(0xffffd035)),(uint8_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_00279c80(void){
uint64_t incoming=cpu(31);
/* 00279c80: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 00279c84: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279c88: move s1,a2 */ set(17,cpu(6));
/* 00279c8c: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279c90: move s2,t0 */ set(18,cpu(8));
/* 00279c94: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279c98: move s3,a0 */ set(19,cpu(4));
/* 00279c9c: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279ca0: move s4,a1 */ set(20,cpu(5));
/* 00279ca4: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279ca8: move s5,t2 */ set(21,cpu(10));
/* 00279cac: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279cb0: move a0,t1 */ set(4,cpu(9));
/* 00279cb4: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279cb8: lw a1,-0x2ff0(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 00279cbc: lw v1,0xc(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 00279cc0: lw v0,0xc(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x0000000c)));
/* 00279cc4: lw s0,0x0(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00279cc8: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 00279ccc: sra v0,v0,0x1 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>1)));
/* 00279cd0: jal 0x001abc88 */ set(31,UINT64_C(0x00279cd8));/* delay 00279cd4 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));nocturneBattlePanelAnalyzeCall(UINT32_C(0x001abc88),UINT32_C(0x00279cd0));
/* 00279cd8: lw a1,0x4(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 00279cdc: addu a0,s0,s3 */ set(4,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 00279ce0: lw a3,0x10(s1) */ lw(7,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 00279ce4: lw t3,0xc(s2) */ lw(11,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 00279ce8: addu a1,a1,s4 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(20)));
/* 00279cec: lw a2,0xc(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 00279cf0: lw t0,0x0(s2) */ lw(8,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 00279cf4: lw t1,0x4(s2) */ lw(9,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 00279cf8: lw t2,0x8(s2) */ lw(10,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 00279cfc: sw s5,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(21));
/* 00279d00: jal 0x00279a88 */ set(31,UINT64_C(0x00279d08));/* delay 00279d04 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));nocturneBattlePanelAnalyzeCall(UINT32_C(0x00279a88),UINT32_C(0x00279d00));
/* 00279d08: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00279d0c: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00279d10: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00279d14: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00279d18: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00279d1c: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00279d20: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 00279d24: jr ra */ {uint64_t target=cpu(31);/* delay 00279d28 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_00282268(void){
uint64_t incoming=cpu(31);
/* 00282268: jr ra */ {uint64_t target=cpu(31);/* delay 0028226c */ sb(ea(28,(int32_t)UINT32_C(0xffffd0cd)),(uint8_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_002ab0f8(void){
uint64_t incoming=cpu(31);
/* 002ab0f8: lw a3,0x28(a0) */ lw(7,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002ab0fc: li v1,-0x1e1 */ set(3,sx(UINT32_C(0xfffffe1f)));
/* 002ab100: sll a1,a1,0x5 */ set(5,sx((uint32_t)cpu(5)<<5));
/* 002ab104: sll a2,a2,0x6 */ set(6,sx((uint32_t)cpu(6)<<6));
/* 002ab108: ld v0,0x10(a3) */ restore(2,ea(7,(int32_t)UINT32_C(0x00000010)));
/* 002ab10c: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002ab110: or v0,a1,v0 */ set(2,cpu(5)|cpu(2));
/* 002ab114: or v0,a2,v0 */ set(2,cpu(6)|cpu(2));
/* 002ab118: jr ra */ {uint64_t target=cpu(31);/* delay 002ab11c */ save(2,ea(7,(int32_t)UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002d4558(void){
uint64_t incoming=cpu(31);
/* 002d4558: sltiu v0,a2,0x8 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));
/* 002d455c: bne v0,zero,0x002d45d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d4560 */ set(3,cpu(4));if(taken){goto L_002d45d8;}}
/* 002d4564: andi v0,a0,0xf */ set(2,cpu(4)&UINT32_C(0x0000000f));
/* 002d4568: bne v0,zero,0x002d45d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d456c */ set(7,cpu(4));if(taken){goto L_002d45d8;}}
/* 002d4570: andi t1,a1,0xff */ set(9,cpu(5)&UINT32_C(0x000000ff));
/* 002d4574: sltiu t2,a2,0x20 */ set(10,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d4578: move t0,t1 */ set(8,cpu(9));
/* 002d457c: dsll v1,t0,0x8 */ set(3,cpu(8)<<8);
/* 002d4580: or t0,v1,t1 */ set(8,cpu(3)|cpu(9));
/* 002d4584: pcpyh v1,t0 */ prerequisitePcpyh(3,8);
/* 002d4588: bne t2,zero,0x002d45c4 */ {int taken=(cpu(10)!=cpu(0));/* delay 002d458c */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));if(taken){goto L_002d45c4;}}
/* 002d4590: pcpyld t0,v1,v1 */ requestPacked(0,8,3,3);
L_002d4594:;
/* 002d4594: sq t0,0x0(a3) */ sq(8,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d4598: addiu a2,a2,-0x20 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffe0)));
/* 002d459c: addiu a3,a3,0x10 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));
/* 002d45a0: sltiu v0,a2,0x20 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000020));
/* 002d45a4: sq t0,0x0(a3) */ sq(8,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002d45a8: beq v0,zero,0x002d4594 */ {int taken=(cpu(2)==cpu(0));/* delay 002d45ac */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));if(taken){goto L_002d4594;}}
/* 002d45b0: b 0x002d45c4 */ /* delay 002d45b4 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));goto L_002d45c4;
L_002d45b8:;
/* 002d45b8: addiu a2,a2,-0x8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xfffffff8)));
/* 002d45bc: addiu a3,a3,0x8 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000008)));
/* 002d45c0: sltiu v0,a2,0x8 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000008));
L_002d45c4:;
/* 002d45c4: nop  */ 
/* 002d45c8: nop  */ 
/* 002d45cc: beql v0,zero,0x002d45b8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d45d0 */ save(3,ea(7,(int32_t)UINT32_C(0x00000000)));goto L_002d45b8;}}
/* 002d45d4: move v1,a3 */ set(3,cpu(7));
L_002d45d8:;
/* 002d45d8: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 002d45dc: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d45e0: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d45e4: beq a2,v0,0x002d4610 */ {int taken=(cpu(6)==cpu(2));/* delay 002d45e8 */ if(taken){goto L_002d4610;}}
/* 002d45ec: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 002d45f0: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
L_002d45f4:;
/* 002d45f4: sb a1,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(5));
/* 002d45f8: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002d45fc: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d4600: nop  */ 
/* 002d4604: nop  */ 
/* 002d4608: bne a2,v0,0x002d45f4 */ {int taken=(cpu(6)!=cpu(2));/* delay 002d460c */ if(taken){goto L_002d45f4;}}
L_002d4610:;
/* 002d4610: jr ra */ {uint64_t target=cpu(31);/* delay 002d4614 */ set(2,cpu(4));checkReturn(target,incoming);return;}
}
static void body_002aad88(void){
uint64_t incoming=cpu(31);
/* 002aad88: sw zero,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002aad8c: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002aad90: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002aad94: jr ra */ {uint64_t target=cpu(31);/* delay 002aad98 */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_002aaf20(void){
uint64_t incoming=cpu(31);
/* 002aaf20: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002aaf24: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002aaf28: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aaf2c: lui s0,0x58 */ set(16,sx(UINT32_C(0x00580000)));
/* 002aaf30: li a1,0x7f */ set(5,sx(UINT32_C(0x0000007f)));
/* 002aaf34: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aaf38: jal 0x002a8080 */ set(31,UINT64_C(0x002aaf40));/* delay 002aaf3c */ set(6,cpu(0));nocturneBattlePanelAnalyzeCall(UINT32_C(0x002a8080),UINT32_C(0x002aaf38));
/* 002aaf40: addiu s0,s0,0x1018 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00001018)));
/* 002aaf44: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aaf48: move a0,s0 */ set(4,cpu(16));
/* 002aaf4c: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002aaf50: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aaf54: j 0x002aad88 */ /* delay 002aaf58 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002aad88();return;
}
static void body_00280528(void){
uint64_t incoming=cpu(31);
/* 00280528: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 0028052c: sw zero,-0x2f4c(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0b4)),(uint32_t)cpu(0));
/* 00280530: jr ra */ {uint64_t target=cpu(31);/* delay 00280534 */ sw(ea(28,(int32_t)UINT32_C(0xffffd0b0)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelAnalyzeDependencyBody(uint32_t entry){switch(entry){
case UINT32_C(0x00212248):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00212248();return 1u;case UINT32_C(0x002122c8):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_002122c8();return 1u;case UINT32_C(0x00212878):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00212878();return 1u;case UINT32_C(0x00214530):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00214530();return 1u;case UINT32_C(0x00214550):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00214550();return 1u;case UINT32_C(0x00214730):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00214730();return 1u;case UINT32_C(0x00235ff8):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00235ff8();return 1u;case UINT32_C(0x002361c0):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_002361c0();return 1u;case UINT32_C(0x00239d20):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00239d20();return 1u;case UINT32_C(0x00239df8):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00239df8();return 1u;case UINT32_C(0x00245d18):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00245d18();return 1u;case UINT32_C(0x00279c58):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00279c58();return 1u;case UINT32_C(0x00279c80):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00279c80();return 1u;case UINT32_C(0x00282268):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00282268();return 1u;case UINT32_C(0x002ab0f8):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_002ab0f8();return 1u;case UINT32_C(0x002d4558):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_002d4558();return 1u;case UINT32_C(0x002aad88):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_002aad88();return 1u;case UINT32_C(0x002aaf20):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_002aaf20();return 1u;case UINT32_C(0x00280528):if(nocturneBattlePanelAnalyzeStackPointer()!=(uint32_t)cpu(29))abort();body_00280528();return 1u;
default:return 0u;}}
