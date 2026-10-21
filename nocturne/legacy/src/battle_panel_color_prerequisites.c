/* Six whole original direct color callers; fixed native-PC statements.
 * Actual128 upper halves survive every scalar write; external calls remain
 * explicitly unimplemented native bank/frame routes. No runtime decoder,
 * result provider, source register-zero fill or per-call upper-word trace. */
#include "battle_panel_color_callers.h"
#include "battle_panel_color_native.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <stdlib.h>
#include <string.h>
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void);
uint64_t nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t lo,uint64_t hi);
static uint8_t *at(uint32_t a){return nocturneResolveBattlePanelColorAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattlePanelColorCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){
 uint32_t q[4];if(!r)return;nocturneBattlePanelColorCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);
 nocturneBattlePanelColorCpuWrite(r,q);if(r==29u)nocturneBattlePanelColorSetStackPointer(q[0]);
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


#include "battle_panel_color_prerequisites.h"
void nocturneBattleActionFormulaSecondaryWrite(uint64_t lo,uint64_t hi);
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sq(unsigned reg,uint32_t a){uint32_t q[4];nocturneBattlePanelColorCpuRead(reg,q);memcpy(at(a&~15u),q,16);}
static void nativeMultiply(unsigned rd,uint32_t a,uint32_t b,int isSigned,int secondary){
 uint64_t p=isSigned?(uint64_t)((int64_t)(int32_t)a*(int64_t)(int32_t)b):(uint64_t)a*b;
 if(secondary)nocturneBattleActionFormulaSecondaryWrite(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 else nocturneEffectHostSetHilo(sx((uint32_t)p),sx((uint32_t)(p>>32)));
 if(rd)set(rd,sx((uint32_t)p));
}
static void prerequisitePcpyh(unsigned d,unsigned s){
 uint32_t a[4],q[4];nocturneBattlePanelColorCpuRead(s,a);
 q[0]=q[1]=(a[0]&65535u)*65537u;q[2]=q[3]=(a[2]&65535u)*65537u;
 nocturneBattlePanelColorCpuWrite(d,q);
}
static uint32_t leadingSign(uint32_t v){
 uint32_t sign=v>>31,count=0;int bit;
 for(bit=30;bit>=0;--bit){if(((v>>bit)&1u)!=sign)break;++count;}return count;
}
static void prerequisitePlzcw(unsigned d,unsigned s){
 uint64_t a=cpu(s);set(d,(uint64_t)leadingSign((uint32_t)a)|((uint64_t)leadingSign((uint32_t)(a>>32))<<32));
}

static void requestLq(unsigned d,uint32_t a){uint32_t q[4];memcpy(q,at(a&~15u),16);nocturneBattlePanelColorCpuWrite(d,q);}
static void requestPacked(unsigned kind,unsigned d,unsigned s,unsigned t){
 uint32_t a[4],c[4],q[4];nocturneBattlePanelColorCpuRead(s,a);nocturneBattlePanelColorCpuRead(t,c);
 if(kind==0){q[0]=c[0];q[1]=c[1];q[2]=a[0];q[3]=a[1];}
 else if(kind==1){q[0]=a[2];q[1]=a[3];q[2]=c[2];q[3]=c[3];}
 else if(kind==2){for(unsigned i=0;i<4;i++)q[i]=a[i]&c[i];}
 else if(kind==3){for(unsigned i=0;i<4;i++)q[i]=~(a[i]|c[i]);}
 else if(kind==5){for(unsigned i=0;i<4;i++)q[i]=a[i]^c[i];}
 else{uint8_t x[16],y[16],z[16];memcpy(x,a,16);memcpy(y,c,16);for(unsigned i=0;i<16;i++)z[i]=(uint8_t)(x[i]-y[i]);memcpy(q,z,16);}
 nocturneBattlePanelColorCpuWrite(d,q);
}
static void body_00101978(void);
static void body_00101ab0(void);
static void body_00117b08(void);
static void body_001c6160(void);
static void body_001c6338(void);
static void body_001c6438(void);
static void body_001c7cb8(void);
static void body_001c7e38(void);
static void body_001ca298(void);
static void body_001ca430(void);
static void body_00244200(void);
static void body_002469a0(void);
static void body_00279868(void);
static void body_00279980(void);
static void body_00279a88(void);
static void body_00279c00(void);
static void body_0027a290(void);
static void body_0027a318(void);
static void body_0027aa40(void);
static void body_0027fba0(void);
static void body_00282270(void);
static void body_002a89c0(void);
static void body_002a8a30(void);
static void body_002a8ab0(void);
static void body_002a8af8(void);
static void body_002aa980(void);
static void body_002aa9e0(void);
static void body_002ab0c8(void);
static void body_002ab0d8(void);
static void body_002ab0e8(void);
static void body_002acb50(void);
static void body_002acd40(void);
static void body_002acdc0(void);
static void body_002ace38(void);
static void body_002acea0(void);
static void body_002acee8(void);
static void body_002af0f8(void);
static void body_002af210(void);
static void body_002b9c18(void);
static void body_002b9c20(void);
static void body_002b9cc8(void);
static void body_002b9d38(void);
static void body_002b9d68(void);
static void body_002b9d78(void);
static void body_002b9d80(void);
static void body_002b9dd0(void);
static void body_002c0ba8(void);
static void body_002d1590(void);
static void body_002d17f0(void);
static void body_002d1848(void);
static void body_002d1b38(void);
static void body_002d1b88(void);
static void body_002d1c40(void);
static void body_002d34a0(void);
static void body_002d3578(void);
static void body_002d3638(void);
static void body_002d5690(void);
static void body_002d6548(void);
static void body_002d7ea8(void);
static void body_002d8038(void);
static void body_002d95e0(void);
static void body_002d96f8(void);
static void body_002d9908(void);
static void body_002da1e0(void);
static void body_002da360(void);
static void body_002da4ec(void);
static void body_002db5e8(void);
static void body_002db630(void);
static void body_002db950(void);
static void body_002dc650(void);
static void body_002dc658(void);
static void body_00101978(void){
uint64_t incoming=cpu(31);
/* 00101978: move a1,zero */ set(5,cpu(0));
/* 0010197c: move a2,zero */ set(6,cpu(0));
/* 00101980: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 00101984: li a3,0x2 */ set(7,sx(UINT32_C(0x00000002)));
L_00101988:;
/* 00101988: beq a2,t0,0x001019b8 */ {int taken=(cpu(6)==cpu(8));/* delay 0010198c */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_001019b8;}}
/* 00101990: beq v0,zero,0x001019a8 */ {int taken=(cpu(2)==cpu(0));/* delay 00101994 */ if(taken){goto L_001019a8;}}
/* 00101998: beql a2,zero,0x001019bc */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 0010199c */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6e0)));goto L_001019bc;}}
/* 001019a0: b 0x001019bc */ /* delay 001019a4 */ goto L_001019bc;
L_001019a8:;
/* 001019a8: beql a2,a3,0x001019bc */ {int taken=(cpu(6)==cpu(7));if(taken){/* delay 001019ac */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6ec)));goto L_001019bc;}}
/* 001019b0: b 0x001019bc */ /* delay 001019b4 */ goto L_001019bc;
L_001019b8:;
/* 001019b8: lw a1,-0x5908(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffa6f8)));
L_001019bc:;
/* 001019bc: beql a1,zero,0x001019f0 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 001019c0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));goto L_001019f0;}}
/* 001019c4: lw v1,0x20(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000020)));
L_001019c8:;
/* 001019c8: beq v1,a0,0x001019fc */ {int taken=(cpu(3)==cpu(4));/* delay 001019cc */ set(2,cpu(5));if(taken){goto L_001019fc;}}
/* 001019d0: lw a1,0x3c(a1) */ lw(5,ea(5,(int32_t)UINT32_C(0x0000003c)));
/* 001019d4: nop  */ 
/* 001019d8: nop  */ 
/* 001019dc: nop  */ 
/* 001019e0: nop  */ 
/* 001019e4: bnel a1,zero,0x001019c8 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 001019e8 */ lw(3,ea(5,(int32_t)UINT32_C(0x00000020)));goto L_001019c8;}}
/* 001019ec: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
L_001019f0:;
/* 001019f0: slti v0,a2,0x3 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 001019f4: bne v0,zero,0x00101988 */ {int taken=(cpu(2)!=cpu(0));/* delay 001019f8 */ set(2,cpu(0));if(taken){goto L_00101988;}}
L_001019fc:;
/* 001019fc: jr ra */ {uint64_t target=cpu(31);/* delay 00101a00 */ checkReturn(target,incoming);return;}
}
static void body_00101ab0(void){
uint64_t incoming=cpu(31);
/* 00101ab0: jr ra */ {uint64_t target=cpu(31);/* delay 00101ab4 */ lw(2,ea(4,(int32_t)UINT32_C(0x00000038)));checkReturn(target,incoming);return;}
}
static void body_00117b08(void){
uint64_t incoming=cpu(31);
/* 00117b08: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00117b0c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00117b10: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00117b14: jal 0x002acb50 */ set(31,UINT64_C(0x00117b1c));/* delay 00117b18 */ set(4,sx(UINT32_C(0x00000020)));body_002acb50();
/* 00117b1c: move s0,v0 */ set(16,cpu(2));
/* 00117b20: jal 0x002acb90 */ set(31,UINT64_C(0x00117b28));/* delay 00117b24 */ set(4,cpu(16));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acb90),UINT32_C(0x00117b20));
/* 00117b28: move v0,s0 */ set(2,cpu(16));
/* 00117b2c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00117b30: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00117b34: jr ra */ {uint64_t target=cpu(31);/* delay 00117b38 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c6160(void){
uint64_t incoming=cpu(31);
/* 001c6160: li a1,0x14 */ set(5,sx(UINT32_C(0x00000014)));
/* 001c6164: slt v0,zero,a0 */ set(2,(int64_t)cpu(0)<(int64_t)cpu(4));
/* 001c6168: movz a0,a1,v0 */ if(cpu(2)==0){set(4,cpu(5));}
/* 001c616c: lui a2,0x32 */ set(6,sx(UINT32_C(0x00320000)));
/* 001c6170: addiu v1,a0,-0x5 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffb)));
/* 001c6174: sw a0,-0x4d60(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffb2a0)),(uint32_t)cpu(4));
/* 001c6178: jr ra */ {uint64_t target=cpu(31);/* delay 001c617c */ sb(ea(6,(int32_t)UINT32_C(0x00006061)),(uint8_t)cpu(3));checkReturn(target,incoming);return;}
}
static void body_001c6338(void){
uint64_t incoming=cpu(31);
/* 001c6338: srl v0,a0,0x8 */ set(2,sx((uint32_t)cpu(4)>>8));
/* 001c633c: andi v1,a0,0xff00 */ set(3,cpu(4)&UINT32_C(0x0000ff00));
/* 001c6340: sll a1,a0,0x18 */ set(5,sx((uint32_t)cpu(4)<<24));
/* 001c6344: srl a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)>>24));
/* 001c6348: andi v0,v0,0xff00 */ set(2,cpu(2)&UINT32_C(0x0000ff00));
/* 001c634c: sll v1,v1,0x8 */ set(3,sx((uint32_t)cpu(3)<<8));
/* 001c6350: or a1,a1,a0 */ set(5,cpu(5)|cpu(4));
/* 001c6354: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 001c6358: jr ra */ {uint64_t target=cpu(31);/* delay 001c635c */ set(2,cpu(5)|cpu(2));checkReturn(target,incoming);return;}
}
static void body_001c6438(void){
uint64_t incoming=cpu(31);
/* 001c6438: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 001c643c: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c6440: move s3,a0 */ set(19,cpu(4));
/* 001c6444: move a0,t1 */ set(4,cpu(9));
/* 001c6448: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c644c: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c6450: move s0,t3 */ set(16,cpu(11));
/* 001c6454: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c6458: move s2,a2 */ set(18,cpu(6));
/* 001c645c: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c6460: move s4,a3 */ set(20,cpu(7));
/* 001c6464: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c6468: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c646c: addiu s3,s3,0x7000 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00007000)));
/* 001c6470: lw s6,0x68(sp) */ lw(22,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001c6474: sll s2,s2,0x4 */ set(18,sx((uint32_t)cpu(18)<<4));
/* 001c6478: sd s7,0x48(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c647c: andi s7,t0,0xff */ set(23,cpu(8)&UINT32_C(0x000000ff));
/* 001c6480: sd s8,0x50(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c6484: move s8,a1 */ set(30,cpu(5));
/* 001c6488: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c648c: sll s7,s7,0x2 */ set(23,sx((uint32_t)cpu(23)<<2));
/* 001c6490: jal 0x001c6338 */ set(31,UINT64_C(0x001c6498));/* delay 001c6494 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(10));body_001c6338();
/* 001c6498: li a0,0x90 */ set(4,sx(UINT32_C(0x00000090)));
/* 001c649c: jal 0x002acb50 */ set(31,UINT64_C(0x001c64a4));/* delay 001c64a0 */ set(21,cpu(2));body_002acb50();
/* 001c64a4: lui v1,0x7000 */ set(3,sx(UINT32_C(0x70000000)));
/* 001c64a8: move s1,v0 */ set(17,cpu(2));
/* 001c64ac: dsll v0,s0,0x6 */ set(2,cpu(16)<<6);
/* 001c64b0: lui a0,0x5000 */ set(4,sx(UINT32_C(0x50000000)));
/* 001c64b4: dsll s0,s0,0x5 */ set(16,cpu(16)<<5);
/* 001c64b8: or s0,s0,v0 */ set(16,cpu(16)|cpu(2));
/* 001c64bc: lui v0,0x10af */ set(2,sx(UINT32_C(0x10af0000)));
/* 001c64c0: ori v0,v0,0x4000 */ set(2,cpu(2)|UINT32_C(0x00004000));
/* 001c64c4: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 001c64c8: ori v0,v0,0x3 */ set(2,cpu(2)|UINT32_C(0x00000003));
/* 001c64cc: ori v1,v1,0x8 */ set(3,cpu(3)|UINT32_C(0x00000008));
/* 001c64d0: ori a0,a0,0x8 */ set(4,cpu(4)|UINT32_C(0x00000008));
/* 001c64d4: li a1,0xe */ set(5,sx(UINT32_C(0x0000000e)));
/* 001c64d8: li a2,0x14 */ set(6,sx(UINT32_C(0x00000014)));
/* 001c64dc: sd s0,0x30(s1) */ save(16,ea(17,(int32_t)UINT32_C(0x00000030)));
/* 001c64e0: ori t5,zero,0x8000 */ set(13,cpu(0)|UINT32_C(0x00008000));
/* 001c64e4: dsll32 t5,t5,0x10 */ set(13,cpu(13)<<48);
/* 001c64e8: sw v1,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c64ec: ori t3,zero,0x8000 */ set(11,cpu(0)|UINT32_C(0x00008000));
/* 001c64f0: dsll t3,t3,0x13 */ set(11,cpu(11)<<19);
/* 001c64f4: sw a0,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
/* 001c64f8: lui t4,0x140 */ set(12,sx(UINT32_C(0x01400000)));
/* 001c64fc: sd v0,0x10(s1) */ save(2,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c6500: li a3,0x6 */ set(7,sx(UINT32_C(0x00000006)));
/* 001c6504: sd a1,0x18(s1) */ save(5,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 001c6508: li t0,0x8 */ set(8,sx(UINT32_C(0x00000008)));
/* 001c650c: sd a2,0x38(s1) */ save(6,ea(17,(int32_t)UINT32_C(0x00000038)));
/* 001c6510: lui t1,0x3400 */ set(9,sx(UINT32_C(0x34000000)));
/* 001c6514: dsll32 t1,t1,0x0 */ set(9,cpu(9)<<32);
/* 001c6518: ori t1,t1,0x8002 */ set(9,cpu(9)|UINT32_C(0x00008002));
/* 001c651c: sw zero,0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 001c6520: li t2,0x413 */ set(10,sx(UINT32_C(0x00000413)));
/* 001c6524: sw zero,0x8(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001c6528: addiu s8,s8,0x7900 */ set(30,sx((uint32_t)cpu(30)+UINT32_C(0x00007900)));
/* 001c652c: sll s4,s4,0x4 */ set(20,sx((uint32_t)cpu(20)<<4));
/* 001c6530: addu s2,s3,s2 */ set(18,sx((uint32_t)cpu(19)+(uint32_t)cpu(18)));
/* 001c6534: lwu a1,0xc(s6) */ set(5,word(ea(22,(int32_t)UINT32_C(0x0000000c))));
/* 001c6538: addu s4,s8,s4 */ set(20,sx((uint32_t)cpu(30)+(uint32_t)cpu(20)));
/* 001c653c: lui a2,0x57 */ set(6,sx(UINT32_C(0x00570000)));
/* 001c6540: addu a2,a2,s7 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(23)));
/* 001c6544: lwu a2,-0x4458(a2) */ set(6,word(ea(6,(int32_t)UINT32_C(0xffffbba8))));
/* 001c6548: sll s4,s4,0x10 */ set(20,sx((uint32_t)cpu(20)<<16));
/* 001c654c: lwu a0,0x4(s6) */ set(4,word(ea(22,(int32_t)UINT32_C(0x00000004))));
/* 001c6550: dsll a1,a1,0x1e */ set(5,cpu(5)<<30);
/* 001c6554: lwu v0,0x14(s6) */ set(2,word(ea(22,(int32_t)UINT32_C(0x00000014))));
/* 001c6558: dsll32 a2,a2,0x5 */ set(6,cpu(6)<<37);
/* 001c655c: lwu v1,0x10(s6) */ set(3,word(ea(22,(int32_t)UINT32_C(0x00000010))));
/* 001c6560: dsll a0,a0,0x1a */ set(4,cpu(4)<<26);
/* 001c6564: dsll v0,v0,0xe */ set(2,cpu(2)<<14);
/* 001c6568: or a0,a0,t3 */ set(4,cpu(4)|cpu(11));
/* 001c656c: or a1,a1,a2 */ set(5,cpu(5)|cpu(6));
/* 001c6570: or v1,v1,t5 */ set(3,cpu(3)|cpu(13));
/* 001c6574: or v0,v0,t4 */ set(2,cpu(2)|cpu(12));
/* 001c6578: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 001c657c: or v0,v0,a1 */ set(2,cpu(2)|cpu(5));
/* 001c6580: sd a3,0x28(s1) */ save(7,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 001c6584: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 001c6588: sd t0,0x48(s1) */ save(8,ea(17,(int32_t)UINT32_C(0x00000048)));
/* 001c658c: sd t1,0x50(s1) */ save(9,ea(17,(int32_t)UINT32_C(0x00000050)));
/* 001c6590: andi s2,s2,0xffff */ set(18,cpu(18)&UINT32_C(0x0000ffff));
/* 001c6594: sd t2,0x58(s1) */ save(10,ea(17,(int32_t)UINT32_C(0x00000058)));
/* 001c6598: or s2,s2,s4 */ set(18,cpu(18)|cpu(20));
/* 001c659c: sd v1,0x20(s1) */ save(3,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 001c65a0: dsll32 s2,s2,0x0 */ set(18,cpu(18)<<32);
/* 001c65a4: sd zero,0x40(s1) */ save(0,ea(17,(int32_t)UINT32_C(0x00000040)));
/* 001c65a8: dsll32 s5,s5,0x0 */ set(21,cpu(21)<<32);
/* 001c65ac: dsrl32 s5,s5,0x0 */ set(21,cpu(21)>>32);
/* 001c65b0: dsrl32 s2,s2,0x0 */ set(18,cpu(18)>>32);
/* 001c65b4: lw v1,0x60(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001c65b8: andi s3,s3,0xffff */ set(19,cpu(19)&UINT32_C(0x0000ffff));
/* 001c65bc: lw a1,0x0(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c65c0: lw v0,0xc(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x0000000c)));
/* 001c65c4: lw a0,0x8(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001c65c8: ori v1,zero,0xfe00 */ set(3,cpu(0)|UINT32_C(0x0000fe00));
/* 001c65cc: dsll32 v1,v1,0xe */ set(3,cpu(3)<<46);
/* 001c65d0: dsll32 t2,a1,0x0 */ set(10,cpu(5)<<32);
/* 001c65d4: sll a1,s8,0x10 */ set(5,sx((uint32_t)cpu(30)<<16));
/* 001c65d8: sll v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)<<16));
/* 001c65dc: or s2,s2,t2 */ set(18,cpu(18)|cpu(10));
/* 001c65e0: or s5,s5,v1 */ set(21,cpu(21)|cpu(3));
/* 001c65e4: or v0,v0,a0 */ set(2,cpu(2)|cpu(4));
/* 001c65e8: sd s2,0x70(s1) */ save(18,ea(17,(int32_t)UINT32_C(0x00000070)));
/* 001c65ec: or s3,s3,a1 */ set(19,cpu(19)|cpu(5));
/* 001c65f0: sd s5,0x68(s1) */ save(21,ea(17,(int32_t)UINT32_C(0x00000068)));
/* 001c65f4: dsll32 s3,s3,0x0 */ set(19,cpu(19)<<32);
/* 001c65f8: sd v0,0x60(s1) */ save(2,ea(17,(int32_t)UINT32_C(0x00000060)));
/* 001c65fc: dsrl32 s3,s3,0x0 */ set(19,cpu(19)>>32);
/* 001c6600: or s3,s3,t2 */ set(19,cpu(19)|cpu(10));
/* 001c6604: li a0,0x20 */ set(4,sx(UINT32_C(0x00000020)));
/* 001c6608: lw v1,0x60(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001c660c: lw v0,0x4(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000004)));
/* 001c6610: lw v1,0x0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001c6614: sll v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)<<16));
/* 001c6618: sd s5,0x80(s1) */ save(21,ea(17,(int32_t)UINT32_C(0x00000080)));
/* 001c661c: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 001c6620: sd s3,0x88(s1) */ save(19,ea(17,(int32_t)UINT32_C(0x00000088)));
/* 001c6624: jal 0x002acb50 */ set(31,UINT64_C(0x001c662c));/* delay 001c6628 */ save(2,ea(17,(int32_t)UINT32_C(0x00000078)));body_002acb50();
/* 001c662c: move s0,v0 */ set(16,cpu(2));
/* 001c6630: jal 0x002acb90 */ set(31,UINT64_C(0x001c6638));/* delay 001c6634 */ set(4,cpu(16));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acb90),UINT32_C(0x001c6630));
/* 001c6638: move a0,s0 */ set(4,cpu(16));
/* 001c663c: jal 0x002acbb8 */ set(31,UINT64_C(0x001c6644));/* delay 001c6640 */ set(5,cpu(17));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acbb8),UINT32_C(0x001c663c));
/* 001c6644: lw v0,0x70(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 001c6648: sll a0,v0,0x5 */ set(4,sx((uint32_t)cpu(2)<<5));
/* 001c664c: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 001c6650: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 001c6654: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 001c6658: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 001c665c: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x001c6664));/* delay 001c6660 */ set(5,cpu(16));nocturneBattlePanelColorPrerequisiteIndirect(target,UINT32_C(0x001c665c));}
/* 001c6664: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c6668: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c666c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c6670: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c6674: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c6678: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c667c: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c6680: ld s7,0x48(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c6684: ld s8,0x50(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c6688: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c668c: jr ra */ {uint64_t target=cpu(31);/* delay 001c6690 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_001c7cb8(void){
uint64_t incoming=cpu(31);
/* 001c7cb8: move t2,a1 */ set(10,cpu(5));
/* 001c7cbc: li a1,0x80 */ set(5,sx(UINT32_C(0x00000080)));
/* 001c7cc0: lw v0,0x24(t2) */ lw(2,ea(10,(int32_t)UINT32_C(0x00000024)));
/* 001c7cc4: andi a2,a2,0xff */ set(6,cpu(6)&UINT32_C(0x000000ff));
/* 001c7cc8: andi a3,a3,0xff */ set(7,cpu(7)&UINT32_C(0x000000ff));
/* 001c7ccc: move t4,zero */ set(12,cpu(0));
/* 001c7cd0: move t3,zero */ set(11,cpu(0));
/* 001c7cd4: bne v0,zero,0x001c7d10 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c7cd8 */ set(9,cpu(0));if(taken){goto L_001c7d10;}}
/* 001c7cdc: lw v1,0x24(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000024)));
/* 001c7ce0: beq v1,zero,0x001c7d14 */ {int taken=(cpu(3)==cpu(0));/* delay 001c7ce4 */ if(taken){goto L_001c7d14;}}
/* 001c7ce8: lw v0,0x20(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000020)));
/* 001c7cec: bnel v0,zero,0x001c7d10 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c7cf0 */ set(9,byte(ea(2,(int32_t)UINT32_C(0x00000016))));goto L_001c7d10;}}
/* 001c7cf4: lw v0,0x24(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000024)));
/* 001c7cf8: beq v0,zero,0x001c7d14 */ {int taken=(cpu(2)==cpu(0));/* delay 001c7cfc */ if(taken){goto L_001c7d14;}}
/* 001c7d00: lw v0,0x20(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 001c7d04: beq v0,zero,0x001c7d14 */ {int taken=(cpu(2)==cpu(0));/* delay 001c7d08 */ if(taken){goto L_001c7d14;}}
/* 001c7d0c: lbu t1,0x16(v0) */ set(9,byte(ea(2,(int32_t)UINT32_C(0x00000016))));
L_001c7d10:;
/* 001c7d10: lbu a1,0x10(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000010))));
L_001c7d14:;
/* 001c7d14: beq t1,zero,0x001c7d28 */ {int taken=(cpu(9)==cpu(0));/* delay 001c7d18 */ set(8,sx((uint32_t)cpu(10)+UINT32_C(0x00000010)));if(taken){goto L_001c7d28;}}
/* 001c7d1c: lbu v0,0x16(t2) */ set(2,byte(ea(10,(int32_t)UINT32_C(0x00000016))));
/* 001c7d20: bne t1,v0,0x001c7d40 */ {int taken=(cpu(9)!=cpu(2));/* delay 001c7d24 */ set(2,cpu(5)^UINT32_C(0x00000080));if(taken){goto L_001c7d40;}}
L_001c7d28:;
/* 001c7d28: sltu v0,a1,a2 */ set(2,cpu(5)<cpu(6));
/* 001c7d2c: beql v0,zero,0x001c7d44 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c7d30 */ set(11,sx(UINT32_C(0x00000001)));goto L_001c7d44;}}
/* 001c7d34: b 0x001c7d44 */ /* delay 001c7d38 */ goto L_001c7d44;
L_001c7d40:;
/* 001c7d40: sltiu t3,v0,0x1 */ set(11,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_001c7d44:;
/* 001c7d44: beq t3,zero,0x001c7dbc */ {int taken=(cpu(11)==cpu(0));/* delay 001c7d48 */ set(5,sx(UINT32_C(0x00000018)));if(taken){goto L_001c7dbc;}}
/* 001c7d4c: lb a0,0x1(a0) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 001c7d50: lw v0,0xc(t2) */ lw(2,ea(10,(int32_t)UINT32_C(0x0000000c)));
/* 001c7d54: sll v1,a3,0x18 */ set(3,sx((uint32_t)cpu(7)<<24));
/* 001c7d58: addu a0,v0,a0 */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c7d5c: bltz v1,0x001c7d8c */ {int taken=((int64_t)cpu(3)<0);/* delay 001c7d60 */ if(cpu(4)==0){set(4,cpu(5));}if(taken){goto L_001c7d8c;}}
/* 001c7d64: sll v0,a3,0x1 */ set(2,sx((uint32_t)cpu(7)<<1));
/* 001c7d68: beql a0,zero,0x001c7d70 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 001c7d6c */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x001c7d6c));goto L_001c7d70;}}
L_001c7d70:;
/* 001c7d70: addu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(7)));
/* 001c7d74: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c7d78: subu v0,v0,a3 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(7)));
/* 001c7d7c: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 001c7d80: div v0,a0 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(4),1,0);
/* 001c7d84: mflo v0 */ set(2,nocturneEffectHostLo());
/* 001c7d88: andi a3,v0,0xff */ set(7,cpu(2)&UINT32_C(0x000000ff));
L_001c7d8c:;
/* 001c7d8c: lw a0,0x0(t0) */ lw(4,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 001c7d90: li v0,0x80 */ set(2,sx(UINT32_C(0x00000080)));
/* 001c7d94: andi v1,a0,0xff */ set(3,cpu(4)&UINT32_C(0x000000ff));
/* 001c7d98: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 001c7d9c: sltu v0,v0,a3 */ set(2,cpu(2)<cpu(7));
/* 001c7da0: bnel v0,zero,0x001c7db0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c7da4 */ set(2,sx(UINT32_C(0xffffff00)));goto L_001c7db0;}}
/* 001c7da8: b 0x001c7db8 */ /* delay 001c7dac */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(7)));goto L_001c7db8;
L_001c7db0:;
/* 001c7db0: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 001c7db4: ori v0,v0,0x80 */ set(2,cpu(2)|UINT32_C(0x00000080));
L_001c7db8:;
/* 001c7db8: sw v0,0x0(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_001c7dbc:;
/* 001c7dbc: lb v0,0x0(t0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(8,(int32_t)UINT32_C(0x00000000))));
/* 001c7dc0: bltz v0,0x001c7df8 */ {int taken=((int64_t)cpu(2)<0);/* delay 001c7dc4 */ set(4,half(ea(10,(int32_t)UINT32_C(0x00000002))));if(taken){goto L_001c7df8;}}
/* 001c7dc8: lbu v1,0x16(t2) */ set(3,byte(ea(10,(int32_t)UINT32_C(0x00000016))));
/* 001c7dcc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c7dd0: bne v1,v0,0x001c7df8 */ {int taken=(cpu(3)!=cpu(2));/* delay 001c7dd4 */ set(4,sx((uint32_t)cpu(4)<<1));if(taken){goto L_001c7df8;}}
/* 001c7dd8: li v0,0x5 */ set(2,sx(UINT32_C(0x00000005)));
/* 001c7ddc: div a0,v0 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(2),1,0);
/* 001c7de0: beql v0,zero,0x001c7de8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c7de4 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x001c7de4));goto L_001c7de8;}}
L_001c7de8:;
/* 001c7de8: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 001c7dec: addiu v1,v1,-0x2 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xfffffffe)));
/* 001c7df0: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 001c7df4: subu t4,zero,v1 */ set(12,sx((uint32_t)cpu(0)-(uint32_t)cpu(3)));
L_001c7df8:;
/* 001c7df8: jr ra */ {uint64_t target=cpu(31);/* delay 001c7dfc */ set(2,cpu(12));checkReturn(target,incoming);return;}
}
static void body_001c7e38(void){
uint64_t incoming=cpu(31);
/* 001c7e38: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
/* 001c7e3c: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c7e40: sd s1,0x38(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c7e44: move s1,a0 */ set(17,cpu(4));
/* 001c7e48: sra a1,a1,0x18 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c7e4c: sd s4,0x50(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c7e50: sd s6,0x60(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001c7e54: move s6,a2 */ set(22,cpu(6));
/* 001c7e58: sd s7,0x68(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001c7e5c: li s7,0x1 */ set(23,sx(UINT32_C(0x00000001)));
/* 001c7e60: sd s0,0x30(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c7e64: li s4,0x1 */ set(20,sx(UINT32_C(0x00000001)));
/* 001c7e68: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c7e6c: move v0,zero */ set(2,cpu(0));
/* 001c7e70: sd s3,0x48(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c7e74: sd s5,0x58(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c7e78: sd s8,0x70(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 001c7e7c: sd ra,0x78(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 001c7e80: sw a1,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(5));
/* 001c7e84: beq s1,zero,0x001c8088 */ {int taken=(cpu(17)==cpu(0));/* delay 001c7e88 */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));if(taken){goto L_001c8088;}}
/* 001c7e8c: lw s1,0x2c(s1) */ lw(17,ea(17,(int32_t)UINT32_C(0x0000002c)));
/* 001c7e90: beq s1,zero,0x001c8084 */ {int taken=(cpu(17)==cpu(0));/* delay 001c7e94 */ lw(2,ea(29,(int32_t)UINT32_C(0x00000024)));if(taken){goto L_001c8084;}}
L_001c7e98:;
/* 001c7e98: lw s0,0x1c(s1) */ lw(16,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 001c7e9c: lw s2,0x4(s1) */ lw(18,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 001c7ea0: lw s3,0x8(s1) */ lw(19,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 001c7ea4: lb s8,0x1(s1) */ set(30,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x00000001))));
/* 001c7ea8: beq s0,zero,0x001c8068 */ {int taken=(cpu(16)==cpu(0));/* delay 001c7eac */ sw(ea(28,(int32_t)UINT32_C(0xffffb2b8)),(uint32_t)cpu(0));if(taken){goto L_001c8068;}}
/* 001c7eb0: lui a2,0x57 */ set(6,sx(UINT32_C(0x00570000)));
/* 001c7eb4: addiu s5,a2,-0x4470 */ set(21,sx((uint32_t)cpu(6)+UINT32_C(0xffffbb90)));
L_001c7eb8:;
/* 001c7eb8: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7ebc: bnel v0,zero,0x001c7edc */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c7ec0 */ set(8,cpu(0));goto L_001c7edc;}}
/* 001c7ec4: lbu a3,0x0(s1) */ set(7,byte(ea(17,(int32_t)UINT32_C(0x00000000))));
/* 001c7ec8: move a0,s1 */ set(4,cpu(17));
/* 001c7ecc: move a1,s0 */ set(5,cpu(16));
/* 001c7ed0: jal 0x001c7cb8 */ set(31,UINT64_C(0x001c7ed8));/* delay 001c7ed4 */ set(6,sx(UINT32_C(0x0000001c)));body_001c7cb8();
/* 001c7ed8: move t0,v0 */ set(8,cpu(2));
L_001c7edc:;
/* 001c7edc: lbu v0,0x15(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000015))));
/* 001c7ee0: sltiu v0,v0,0x2 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 001c7ee4: beq v0,zero,0x001c7f70 */ {int taken=(cpu(2)==cpu(0));/* delay 001c7ee8 */ set(9,cpu(0));if(taken){goto L_001c7f70;}}
/* 001c7eec: lhu v1,0x0(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 001c7ef0: ori v0,zero,0xffbf */ set(2,cpu(0)|UINT32_C(0x0000ffbf));
/* 001c7ef4: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c7ef8: andi v0,v0,0xffff */ set(2,cpu(2)&UINT32_C(0x0000ffff));
/* 001c7efc: sltiu v0,v0,0x1a */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000001a));
/* 001c7f00: beq v0,zero,0x001c7f28 */ {int taken=(cpu(2)==cpu(0));/* delay 001c7f04 */ set(2,cpu(3)&UINT32_C(0x0000ffff));if(taken){goto L_001c7f28;}}
/* 001c7f08: lui a0,0x32 */ set(4,sx(UINT32_C(0x00320000)));
/* 001c7f0c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c7f10: addiu a0,a0,0x6278 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00006278)));
/* 001c7f14: addiu v0,v0,-0x104 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffefc)));
/* 001c7f18: addu v1,v0,a0 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c7f1c: lui a0,0x32 */ set(4,sx(UINT32_C(0x00320000)));
/* 001c7f20: b 0x001c7f60 */ /* delay 001c7f24 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00006210)));goto L_001c7f60;
L_001c7f28:;
/* 001c7f28: ori v0,zero,0xff9f */ set(2,cpu(0)|UINT32_C(0x0000ff9f));
/* 001c7f2c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c7f30: andi v0,v0,0xffff */ set(2,cpu(2)&UINT32_C(0x0000ffff));
/* 001c7f34: sltiu v0,v0,0x1a */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000001a));
/* 001c7f38: beql v0,zero,0x001c7f74 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c7f3c */ lw(2,ea(16,(int32_t)UINT32_C(0x00000020)));goto L_001c7f74;}}
/* 001c7f40: lhu v0,0x0(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 001c7f44: lui a0,0x32 */ set(4,sx(UINT32_C(0x00320000)));
/* 001c7f48: addiu a0,a0,0x62e0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000062e0)));
/* 001c7f4c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c7f50: addiu v0,v0,-0x184 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffe7c)));
/* 001c7f54: addu v1,v0,a0 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c7f58: lui a0,0x32 */ set(4,sx(UINT32_C(0x00320000)));
/* 001c7f5c: addiu a0,a0,0x6348 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00006348)));
L_001c7f60:;
/* 001c7f60: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001c7f64: lw a0,0x0(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001c7f68: lw t1,0x0(v0) */ lw(9,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001c7f6c: addu t0,t0,a0 */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(4)));
L_001c7f70:;
/* 001c7f70: lw v0,0x20(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000020)));
L_001c7f74:;
/* 001c7f74: bne v0,zero,0x001c7fe0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c7f78 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_001c7fe0;}}
/* 001c7f7c: lw a2,0x1c(s0) */ lw(6,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 001c7f80: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 001c7f84: lhu v0,0x0(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 001c7f88: lw a1,0x8(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001c7f8c: sltiu v0,v0,0x80 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001c7f90: lw t4,0x8(a2) */ lw(12,ea(6,(int32_t)UINT32_C(0x00000008)));
/* 001c7f94: addu a0,s2,a0 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(4)));
/* 001c7f98: lbu a3,0x19(s0) */ set(7,byte(ea(16,(int32_t)UINT32_C(0x00000019))));
/* 001c7f9c: addu a1,s3,a1 */ set(5,sx((uint32_t)cpu(19)+(uint32_t)cpu(5)));
/* 001c7fa0: lbu a2,0x18(s0) */ set(6,byte(ea(16,(int32_t)UINT32_C(0x00000018))));
/* 001c7fa4: movn s4,v1,v0 */ if(cpu(2)!=0){set(20,cpu(3));}
/* 001c7fa8: lw t2,0x14(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c7fac: addu a0,a0,t0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(8)));
/* 001c7fb0: addu a1,a1,t1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(9)));
/* 001c7fb4: lw t1,0x10(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 001c7fb8: lbu t0,0x14(s0) */ set(8,byte(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 001c7fbc: addiu t4,t4,0x4 */ set(12,sx((uint32_t)cpu(12)+UINT32_C(0x00000004)));
/* 001c7fc0: srl a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)>>1));
/* 001c7fc4: move t3,s4 */ set(11,cpu(20));
/* 001c7fc8: sw t4,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 001c7fcc: sw s5,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(21));
/* 001c7fd0: jal 0x001c6438 */ set(31,UINT64_C(0x001c7fd8));/* delay 001c7fd4 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(22));body_001c6438();
/* 001c7fd8: b 0x001c802c */ /* delay 001c7fdc */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb2b8)));goto L_001c802c;
L_001c7fe0:;
/* 001c7fe0: move t3,s4 */ set(11,cpu(20));
/* 001c7fe4: lw a1,0x8(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 001c7fe8: lw v0,0x8(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 001c7fec: addu a0,s2,a0 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(4)));
/* 001c7ff0: lbu a3,0x19(s0) */ set(7,byte(ea(16,(int32_t)UINT32_C(0x00000019))));
/* 001c7ff4: addu a1,s3,a1 */ set(5,sx((uint32_t)cpu(19)+(uint32_t)cpu(5)));
/* 001c7ff8: lbu a2,0x18(s0) */ set(6,byte(ea(16,(int32_t)UINT32_C(0x00000018))));
/* 001c7ffc: addu a0,a0,t0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(8)));
/* 001c8000: lw t2,0x14(s1) */ lw(10,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8004: addu a1,a1,t1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(9)));
/* 001c8008: lbu t0,0x14(s0) */ set(8,byte(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 001c800c: addiu v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c8010: lw t1,0x10(s0) */ lw(9,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 001c8014: srl a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)>>1));
/* 001c8018: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001c801c: sw s5,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(21));
/* 001c8020: jal 0x001c6438 */ set(31,UINT64_C(0x001c8028));/* delay 001c8024 */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(22));body_001c6438();
/* 001c8028: lw v0,-0x4d48(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb2b8)));
L_001c802c:;
/* 001c802c: lbu v1,0x10(s0) */ set(3,byte(ea(16,(int32_t)UINT32_C(0x00000010))));
/* 001c8030: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c8034: beq v1,zero,0x001c8048 */ {int taken=(cpu(3)==cpu(0));/* delay 001c8038 */ sw(ea(28,(int32_t)UINT32_C(0xffffb2b8)),(uint32_t)cpu(2));if(taken){goto L_001c8048;}}
/* 001c803c: lhu v0,0x2(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x00000002))));
/* 001c8040: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c8044: sh v0,0x2(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));
L_001c8048:;
/* 001c8048: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001c804c: sltiu v1,v1,0x80 */ set(3,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001c8050: lw s0,0x28(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 001c8054: movn s7,zero,v1 */ if(cpu(3)!=0){set(23,cpu(0));}
/* 001c8058: addu v0,v0,s8 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(30)));
/* 001c805c: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 001c8060: bne s0,zero,0x001c7eb8 */ {int taken=(cpu(16)!=cpu(0));/* delay 001c8064 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));if(taken){goto L_001c7eb8;}}
L_001c8068:;
/* 001c8068: lw v0,0x18(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 001c806c: lw v1,0x24(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 001c8070: lw s1,0x28(s1) */ lw(17,ea(17,(int32_t)UINT32_C(0x00000028)));
/* 001c8074: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8078: bne s1,zero,0x001c7e98 */ {int taken=(cpu(17)!=cpu(0));/* delay 001c807c */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(3));if(taken){goto L_001c7e98;}}
/* 001c8080: lw v0,0x24(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000024)));
L_001c8084:;
/* 001c8084: movz v0,zero,s7 */ if(cpu(23)==0){set(2,cpu(0));}
L_001c8088:;
/* 001c8088: ld s0,0x30(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c808c: ld s1,0x38(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c8090: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c8094: ld s3,0x48(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c8098: ld s4,0x50(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001c809c: ld s5,0x58(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001c80a0: ld s6,0x60(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001c80a4: ld s7,0x68(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001c80a8: ld s8,0x70(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 001c80ac: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 001c80b0: jr ra */ {uint64_t target=cpu(31);/* delay 001c80b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));checkReturn(target,incoming);return;}
}
static void body_001ca298(void){
uint64_t incoming=cpu(31);
/* 001ca298: addiu sp,sp,-0x440 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffbc0)));
/* 001ca29c: sd s0,0x400(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000400)));
/* 001ca2a0: move s0,t0 */ set(16,cpu(8));
/* 001ca2a4: sd s2,0x410(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000410)));
/* 001ca2a8: move s2,a0 */ set(18,cpu(4));
/* 001ca2ac: move a0,s0 */ set(4,cpu(16));
/* 001ca2b0: sd s1,0x408(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000408)));
/* 001ca2b4: sd s3,0x418(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000418)));
/* 001ca2b8: move s3,a2 */ set(19,cpu(6));
/* 001ca2bc: sd s4,0x420(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000420)));
/* 001ca2c0: move s4,a3 */ set(20,cpu(7));
/* 001ca2c4: sd s5,0x428(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000428)));
/* 001ca2c8: move s5,t1 */ set(21,cpu(9));
/* 001ca2cc: sd ra,0x430(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000430)));
/* 001ca2d0: jal 0x002d5d0c */ set(31,UINT64_C(0x001ca2d8));/* delay 001ca2d4 */ set(17,cpu(5));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002d5d0c),UINT32_C(0x001ca2d0));
/* 001ca2d8: move a2,zero */ set(6,cpu(0));
/* 001ca2dc: move t0,v0 */ set(8,cpu(2));
/* 001ca2e0: addu v0,sp,t0 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(8)));
/* 001ca2e4: blez t0,0x001ca370 */ {int taken=((int64_t)cpu(8)<=0);/* delay 001ca2e8 */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));if(taken){goto L_001ca370;}}
/* 001ca2ec: ori t2,zero,0xffff */ set(10,cpu(0)|UINT32_C(0x0000ffff));
/* 001ca2f0: li t1,-0x80 */ set(9,sx(UINT32_C(0xffffff80)));
/* 001ca2f4: addu v1,s0,a2 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));
L_001ca2f8:;
/* 001ca2f8: lbu a0,0x0(v1) */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001ca2fc: sltiu v0,a0,0x80 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001ca300: beq v0,zero,0x001ca318 */ {int taken=(cpu(2)==cpu(0));/* delay 001ca304 */ set(5,sx((uint32_t)cpu(4)<<8));if(taken){goto L_001ca318;}}
/* 001ca308: addu v0,sp,a2 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(6)));
/* 001ca30c: b 0x001ca360 */ /* delay 001ca310 */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));goto L_001ca360;
L_001ca318:;
/* 001ca318: lbu v0,0x1(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000001))));
/* 001ca31c: or v0,v0,a1 */ set(2,cpu(2)|cpu(5));
/* 001ca320: andi a0,v0,0xffff */ set(4,cpu(2)&UINT32_C(0x0000ffff));
/* 001ca324: beq a0,t2,0x001ca348 */ {int taken=(cpu(4)==cpu(10));/* delay 001ca328 */ set(7,sx((uint32_t)cpu(4)>>8));if(taken){goto L_001ca348;}}
/* 001ca32c: addiu a1,a2,0x1 */ set(5,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001ca330: addu v0,sp,a2 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(6)));
/* 001ca334: addu v1,sp,a1 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(5)));
/* 001ca338: sb a3,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(7));
/* 001ca33c: b 0x001ca35c */ /* delay 001ca340 */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(4));goto L_001ca35c;
L_001ca348:;
/* 001ca348: addiu a1,a2,0x1 */ set(5,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001ca34c: addu v0,sp,a2 */ set(2,sx((uint32_t)cpu(29)+(uint32_t)cpu(6)));
/* 001ca350: addu v1,sp,a1 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(5)));
/* 001ca354: sb t1,0x0(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(9));
/* 001ca358: sb t1,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(9));
L_001ca35c:;
/* 001ca35c: move a2,a1 */ set(6,cpu(5));
L_001ca360:;
/* 001ca360: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001ca364: slt v0,a2,t0 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(8));
/* 001ca368: bne v0,zero,0x001ca2f8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001ca36c */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(6)));if(taken){goto L_001ca2f8;}}
L_001ca370:;
/* 001ca370: jal 0x001c7c00 */ set(31,UINT64_C(0x001ca378));/* delay 001ca374 */ set(4,sx(UINT32_C(0x00000001)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7c00),UINT32_C(0x001ca370));
/* 001ca378: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001ca37c: move a0,sp */ set(4,cpu(29));
/* 001ca380: move a3,zero */ set(7,cpu(0));
/* 001ca384: move t0,zero */ set(8,cpu(0));
/* 001ca388: jal 0x001c7828 */ set(31,UINT64_C(0x001ca390));/* delay 001ca38c */ set(6,cpu(0));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7828),UINT32_C(0x001ca388));
/* 001ca390: li a0,0x2 */ set(4,sx(UINT32_C(0x00000002)));
/* 001ca394: jal 0x001c7c00 */ set(31,UINT64_C(0x001ca39c));/* delay 001ca398 */ set(16,cpu(2));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7c00),UINT32_C(0x001ca394));
/* 001ca39c: jal 0x001c7c10 */ set(31,UINT64_C(0x001ca3a4));/* delay 001ca3a0 */ set(4,sx(UINT32_C(0x00000001)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7c10),UINT32_C(0x001ca39c));
/* 001ca3a4: move a0,s0 */ set(4,cpu(16));
/* 001ca3a8: move a2,s1 */ set(6,cpu(17));
/* 001ca3ac: jal 0x001c7b30 */ set(31,UINT64_C(0x001ca3b4));/* delay 001ca3b0 */ set(5,cpu(18));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7b30),UINT32_C(0x001ca3ac));
/* 001ca3b4: move a0,s0 */ set(4,cpu(16));
/* 001ca3b8: jal 0x001c7b40 */ set(31,UINT64_C(0x001ca3c0));/* delay 001ca3bc */ set(5,sx((uint32_t)cpu(19)<<4));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7b40),UINT32_C(0x001ca3b8));
/* 001ca3c0: move a0,s0 */ set(4,cpu(16));
/* 001ca3c4: jal 0x001c7ba8 */ set(31,UINT64_C(0x001ca3cc));/* delay 001ca3c8 */ set(5,cpu(20));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7ba8),UINT32_C(0x001ca3c4));
/* 001ca3cc: move a0,s0 */ set(4,cpu(16));
/* 001ca3d0: jal 0x001c7a88 */ set(31,UINT64_C(0x001ca3d8));/* delay 001ca3d4 */ set(5,sx(UINT32_C(0x00000003)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7a88),UINT32_C(0x001ca3d0));
/* 001ca3d8: move a0,s5 */ set(4,cpu(21));
/* 001ca3dc: move a1,s0 */ set(5,cpu(16));
/* 001ca3e0: jal 0x001c8120 */ set(31,UINT64_C(0x001ca3e8));/* delay 001ca3e4 */ set(6,cpu(0));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c8120),UINT32_C(0x001ca3e0));
/* 001ca3e8: ld s0,0x400(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000400)));
/* 001ca3ec: ld s1,0x408(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000408)));
/* 001ca3f0: ld s2,0x410(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000410)));
/* 001ca3f4: ld s3,0x418(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000418)));
/* 001ca3f8: ld s4,0x420(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000420)));
/* 001ca3fc: ld s5,0x428(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000428)));
/* 001ca400: ld ra,0x430(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000430)));
/* 001ca404: jr ra */ {uint64_t target=cpu(31);/* delay 001ca408 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000440)));checkReturn(target,incoming);return;}
}
static void body_001ca430(void){
uint64_t incoming=cpu(31);
/* 001ca430: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001ca434: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 001ca438: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ca43c: move s0,t0 */ set(16,cpu(8));
/* 001ca440: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001ca444: move s1,a0 */ set(17,cpu(4));
/* 001ca448: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001ca44c: move s2,a1 */ set(18,cpu(5));
/* 001ca450: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001ca454: move s3,a2 */ set(19,cpu(6));
/* 001ca458: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001ca45c: move s4,a3 */ set(20,cpu(7));
/* 001ca460: move t0,t1 */ set(8,cpu(9));
/* 001ca464: move a1,zero */ set(5,cpu(0));
/* 001ca468: move a2,zero */ set(6,cpu(0));
/* 001ca46c: move a3,zero */ set(7,cpu(0));
/* 001ca470: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001ca474: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001ca478: jal 0x001c7828 */ set(31,UINT64_C(0x001ca480));/* delay 001ca47c */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0xfffff448)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7828),UINT32_C(0x001ca478));
/* 001ca480: move s5,v0 */ set(21,cpu(2));
/* 001ca484: jal 0x001c7c10 */ set(31,UINT64_C(0x001ca48c));/* delay 001ca488 */ set(4,sx(UINT32_C(0x00000002)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7c10),UINT32_C(0x001ca484));
/* 001ca48c: move a0,s0 */ set(4,cpu(16));
/* 001ca490: move t0,s5 */ set(8,cpu(21));
/* 001ca494: move a3,zero */ set(7,cpu(0));
/* 001ca498: move t1,zero */ set(9,cpu(0));
/* 001ca49c: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 001ca4a0: jal 0x001c7890 */ set(31,UINT64_C(0x001ca4a8));/* delay 001ca4a4 */ set(6,cpu(0));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7890),UINT32_C(0x001ca4a0));
/* 001ca4a8: li a0,0x2 */ set(4,sx(UINT32_C(0x00000002)));
/* 001ca4ac: jal 0x001c7c00 */ set(31,UINT64_C(0x001ca4b4));/* delay 001ca4b0 */ set(21,cpu(2));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7c00),UINT32_C(0x001ca4ac));
/* 001ca4b4: move a2,s2 */ set(6,cpu(18));
/* 001ca4b8: move a0,s5 */ set(4,cpu(21));
/* 001ca4bc: jal 0x001c7b30 */ set(31,UINT64_C(0x001ca4c4));/* delay 001ca4c0 */ set(5,cpu(17));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7b30),UINT32_C(0x001ca4bc));
/* 001ca4c4: move a0,s5 */ set(4,cpu(21));
/* 001ca4c8: jal 0x001c7b40 */ set(31,UINT64_C(0x001ca4d0));/* delay 001ca4cc */ set(5,sx((uint32_t)cpu(19)<<4));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7b40),UINT32_C(0x001ca4c8));
/* 001ca4d0: move a0,s5 */ set(4,cpu(21));
/* 001ca4d4: jal 0x001c7ba8 */ set(31,UINT64_C(0x001ca4dc));/* delay 001ca4d8 */ set(5,cpu(20));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x001c7ba8),UINT32_C(0x001ca4d4));
/* 001ca4dc: move v0,s5 */ set(2,cpu(21));
/* 001ca4e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ca4e4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001ca4e8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001ca4ec: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001ca4f0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001ca4f4: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001ca4f8: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001ca4fc: jr ra */ {uint64_t target=cpu(31);/* delay 001ca500 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_00244200(void){
uint64_t incoming=cpu(31);
/* 00244200: lhu v1,0x6(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x00000006))));
/* 00244204: lhu a1,0x8(a0) */ set(5,half(ea(4,(int32_t)UINT32_C(0x00000008))));
/* 00244208: sll v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)<<1));
/* 0024420c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00244210: beql a1,zero,0x00244218 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 00244214 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x00244214));goto L_00244218;}}
L_00244218:;
/* 00244218: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 0024421c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00244220: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00244224: div v0,a1 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(5),1,0);
/* 00244228: mflo v0 */ set(2,nocturneEffectHostLo());
/* 0024422c: jr ra */ {uint64_t target=cpu(31);/* delay 00244230 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000019));checkReturn(target,incoming);return;}
}
static void body_002469a0(void){
uint64_t incoming=cpu(31);
/* 002469a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002469a4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002469a8: jal 0x00101978 */ set(31,UINT64_C(0x002469b0));/* delay 002469ac */ set(4,sx(UINT32_C(0x000003fa)));body_00101978();
/* 002469b0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002469b4: move a0,v0 */ set(4,cpu(2));
/* 002469b8: j 0x00101ab0 */ /* delay 002469bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_00101ab0();return;
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
/* 002798c8: jal 0x002acb90 */ set(31,UINT64_C(0x002798d0));/* delay 002798cc */ set(16,sx((uint32_t)cpu(16)<<17));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acb90),UINT32_C(0x002798c8));
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
/* 00279924: jal 0x002acbb8 */ set(31,UINT64_C(0x0027992c));/* delay 00279928 */ set(4,cpu(22));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acbb8),UINT32_C(0x00279924));
/* 0027992c: lw a0,-0x3008(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcff8)));
/* 00279930: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00279934: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00279938: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 0027993c: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00279940: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00279944: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x0027994c));/* delay 00279948 */ set(5,cpu(22));nocturneBattlePanelColorPrerequisiteIndirect(target,UINT32_C(0x00279944));}
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
/* 002799a8: jal 0x002acb90 */ set(31,UINT64_C(0x002799b0));/* delay 002799ac */ set(4,cpu(17));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acb90),UINT32_C(0x002799a8));
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
/* 00279a44: jal 0x002acbb8 */ set(31,UINT64_C(0x00279a4c));/* delay 00279a48 */ set(4,cpu(17));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acbb8),UINT32_C(0x00279a44));
/* 00279a4c: lw a0,-0x3008(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcff8)));
/* 00279a50: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00279a54: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00279a58: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 00279a5c: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00279a60: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00279a64: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00279a6c));/* delay 00279a68 */ set(5,cpu(17));nocturneBattlePanelColorPrerequisiteIndirect(target,UINT32_C(0x00279a64));}
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
/* 00279b8c: jal 0x002acb90 */ set(31,UINT64_C(0x00279b94));/* delay 00279b90 */ set(4,cpu(16));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acb90),UINT32_C(0x00279b8c));
/* 00279b94: move a0,s0 */ set(4,cpu(16));
/* 00279b98: lw a1,0x68(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 00279b9c: jal 0x002b9cc8 */ set(31,UINT64_C(0x00279ba4));/* delay 00279ba0 */ set(6,cpu(0));body_002b9cc8();
/* 00279ba4: move a0,s0 */ set(4,cpu(16));
/* 00279ba8: jal 0x002acbb8 */ set(31,UINT64_C(0x00279bb0));/* delay 00279bac */ lw(5,ea(29,(int32_t)UINT32_C(0x00000000)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acbb8),UINT32_C(0x00279ba8));
/* 00279bb0: lw a0,-0x3008(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffcff8)));
/* 00279bb4: sll a0,a0,0x5 */ set(4,sx((uint32_t)cpu(4)<<5));
/* 00279bb8: lui at,0x2f */ set(1,sx(UINT32_C(0x002f0000)));
/* 00279bbc: addiu at,at,0x5f18 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00005f18)));
/* 00279bc0: addu a0,at,a0 */ set(4,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 00279bc4: lw v0,0x10(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 00279bc8: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00279bd0));/* delay 00279bcc */ set(5,cpu(16));nocturneBattlePanelColorPrerequisiteIndirect(target,UINT32_C(0x00279bc8));}
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
static void body_0027a290(void){
uint64_t incoming=cpu(31);
/* 0027a290: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0027a294: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0027a298: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0027a29c: jal 0x00244200 */ set(31,UINT64_C(0x0027a2a4));/* delay 0027a2a0 */ set(16,cpu(4));body_00244200();
/* 0027a2a4: beq v0,zero,0x0027a2b8 */ {int taken=(cpu(2)==cpu(0));/* delay 0027a2a8 */ set(2,sx(UINT32_C(0x754b0000)));if(taken){goto L_0027a2b8;}}
/* 0027a2ac: b 0x0027a308 */ /* delay 0027a2b0 */ set(2,cpu(2)|UINT32_C(0x00003d80));goto L_0027a308;
L_0027a2b8:;
/* 0027a2b8: lhu a0,0x6(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x00000006))));
/* 0027a2bc: lhu a1,0x8(s0) */ set(5,half(ea(16,(int32_t)UINT32_C(0x00000008))));
/* 0027a2c0: ori v0,v0,0x3d80 */ set(2,cpu(2)|UINT32_C(0x00003d80));
/* 0027a2c4: sll v1,a0,0x1 */ set(3,sx((uint32_t)cpu(4)<<1));
/* 0027a2c8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0027a2cc: beql a1,zero,0x0027a2d4 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 0027a2d0 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x0027a2d0));goto L_0027a2d4;}}
L_0027a2d4:;
/* 0027a2d4: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 0027a2d8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 0027a2dc: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0027a2e0: div v1,a1 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(5),1,0);
/* 0027a2e4: mflo v1 */ set(3,nocturneEffectHostLo());
/* 0027a2e8: slti a0,v1,0x19 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000019));
/* 0027a2ec: bne a0,zero,0x0027a308 */ {int taken=(cpu(4)!=cpu(0));/* delay 0027a2f0 */ set(5,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000032));if(taken){goto L_0027a308;}}
/* 0027a2f4: lui v1,0xa09d */ set(3,sx(UINT32_C(0xa09d0000)));
/* 0027a2f8: lui v0,0xb4a0 */ set(2,sx(UINT32_C(0xb4a00000)));
/* 0027a2fc: ori v1,v1,0xc380 */ set(3,cpu(3)|UINT32_C(0x0000c380));
/* 0027a300: ori v0,v0,0x6480 */ set(2,cpu(2)|UINT32_C(0x00006480));
/* 0027a304: movz v0,v1,a1 */ if(cpu(5)==0){set(2,cpu(3));}
L_0027a308:;
/* 0027a308: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0027a30c: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0027a310: jr ra */ {uint64_t target=cpu(31);/* delay 0027a314 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0027a318(void){
uint64_t incoming=cpu(31);
/* 0027a318: lhu a1,0xa(a0) */ set(5,half(ea(4,(int32_t)UINT32_C(0x0000000a))));
/* 0027a31c: lui v0,0x754b */ set(2,sx(UINT32_C(0x754b0000)));
/* 0027a320: lhu a2,0xc(a0) */ set(6,half(ea(4,(int32_t)UINT32_C(0x0000000c))));
/* 0027a324: ori v0,v0,0x3d80 */ set(2,cpu(2)|UINT32_C(0x00003d80));
/* 0027a328: sll v1,a1,0x1 */ set(3,sx((uint32_t)cpu(5)<<1));
/* 0027a32c: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0027a330: beql a2,zero,0x0027a338 */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 0027a334 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x0027a334));goto L_0027a338;}}
L_0027a338:;
/* 0027a338: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 0027a33c: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0027a340: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0027a344: div v1,a2 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(6),1,0);
/* 0027a348: mflo v1 */ set(3,nocturneEffectHostLo());
/* 0027a34c: slti a0,v1,0x19 */ set(4,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000019));
/* 0027a350: bne a0,zero,0x0027a36c */ {int taken=(cpu(4)!=cpu(0));/* delay 0027a354 */ set(5,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000032));if(taken){goto L_0027a36c;}}
/* 0027a358: lui v1,0xa09d */ set(3,sx(UINT32_C(0xa09d0000)));
/* 0027a35c: lui v0,0xb4a0 */ set(2,sx(UINT32_C(0xb4a00000)));
/* 0027a360: ori v1,v1,0xc380 */ set(3,cpu(3)|UINT32_C(0x0000c380));
/* 0027a364: ori v0,v0,0x6480 */ set(2,cpu(2)|UINT32_C(0x00006480));
/* 0027a368: movz v0,v1,a1 */ if(cpu(5)==0){set(2,cpu(3));}
L_0027a36c:;
/* 0027a36c: jr ra */ {uint64_t target=cpu(31);/* delay 0027a370 */ checkReturn(target,incoming);return;}
}
static void body_0027aa40(void){
uint64_t incoming=cpu(31);
/* 0027aa40: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0027aa44: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 0027aa48: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027aa4c: move s0,a2 */ set(16,cpu(6));
/* 0027aa50: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027aa54: move s1,a0 */ set(17,cpu(4));
/* 0027aa58: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027aa5c: move s2,a1 */ set(18,cpu(5));
/* 0027aa60: li a2,0x80 */ set(6,sx(UINT32_C(0x00000080)));
/* 0027aa64: move t0,zero */ set(8,cpu(0));
/* 0027aa68: move a1,zero */ set(5,cpu(0));
/* 0027aa6c: move t1,zero */ set(9,cpu(0));
/* 0027aa70: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0027aa74: li t3,0x1 */ set(11,sx(UINT32_C(0x00000001)));
/* 0027aa78: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0027aa7c: jal 0x00279868 */ set(31,UINT64_C(0x0027aa84));/* delay 0027aa80 */ set(4,sx(UINT32_C(0x00000001)));body_00279868();
/* 0027aa84: jal 0x00279980 */ set(31,UINT64_C(0x0027aa8c));/* delay 0027aa88 */ set(4,cpu(0));body_00279980();
/* 0027aa8c: lw v0,-0x2ff0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027aa90: lw v1,0x120(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000120)));
/* 0027aa94: move a0,s1 */ set(4,cpu(17));
/* 0027aa98: move a1,s2 */ set(5,cpu(18));
/* 0027aa9c: li a2,0x36 */ set(6,sx(UINT32_C(0x00000036)));
/* 0027aaa0: li a3,0x17 */ set(7,sx(UINT32_C(0x00000017)));
/* 0027aaa4: li t0,0x34 */ set(8,sx(UINT32_C(0x00000034)));
/* 0027aaa8: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0027aaac: li t2,0x36 */ set(10,sx(UINT32_C(0x00000036)));
/* 0027aab0: li t3,0x17 */ set(11,sx(UINT32_C(0x00000017)));
/* 0027aab4: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027aab8: jal 0x00279a88 */ set(31,UINT64_C(0x0027aac0));/* delay 0027aabc */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));body_00279a88();
/* 0027aac0: lw v1,0x120(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000120)));
/* 0027aac4: addiu a0,s1,0x36 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000036)));
/* 0027aac8: lw v0,-0x2ff0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0027aacc: move a1,s2 */ set(5,cpu(18));
/* 0027aad0: li a2,0xe4 */ set(6,sx(UINT32_C(0x000000e4)));
/* 0027aad4: li a3,0x17 */ set(7,sx(UINT32_C(0x00000017)));
/* 0027aad8: li t0,0x69 */ set(8,sx(UINT32_C(0x00000069)));
/* 0027aadc: li t1,0x1 */ set(9,sx(UINT32_C(0x00000001)));
/* 0027aae0: li t2,0x1 */ set(10,sx(UINT32_C(0x00000001)));
/* 0027aae4: li t3,0x17 */ set(11,sx(UINT32_C(0x00000017)));
/* 0027aae8: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0027aaec: jal 0x00279a88 */ set(31,UINT64_C(0x0027aaf4));/* delay 0027aaf0 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));body_00279a88();
/* 0027aaf4: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0027aaf8: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0027aafc: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0027ab00: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0027ab04: jr ra */ {uint64_t target=cpu(31);/* delay 0027ab08 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_0027fba0(void){
uint64_t incoming=cpu(31);
/* 0027fba0: lw v1,-0x2f64(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd09c)));
/* 0027fba4: slti v1,v1,0x8 */ set(3,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0027fba8: bne v1,zero,0x0027fd00 */ {int taken=(cpu(3)!=cpu(0));/* delay 0027fbac */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_0027fd00;}}
/* 0027fbb0: lui a2,0x2f */ set(6,sx(UINT32_C(0x002f0000)));
/* 0027fbb4: addiu v1,a2,0x5810 */ set(3,sx((uint32_t)cpu(6)+UINT32_C(0x00005810)));
/* 0027fbb8: lbu a1,0x26(v1) */ set(5,byte(ea(3,(int32_t)UINT32_C(0x00000026))));
/* 0027fbbc: andi v0,a1,0x2 */ set(2,cpu(5)&UINT32_C(0x00000002));
/* 0027fbc0: beq v0,zero,0x0027fc40 */ {int taken=(cpu(2)==cpu(0));/* delay 0027fbc4 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd0ac)));if(taken){goto L_0027fc40;}}
/* 0027fbc8: blez a0,0x0027fbe8 */ {int taken=((int64_t)cpu(4)<=0);/* delay 0027fbcc */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd0a8)));if(taken){goto L_0027fbe8;}}
/* 0027fbd0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0027fbd4: bnel v1,v0,0x0027fbf4 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 0027fbd8 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));goto L_0027fbf4;}}
/* 0027fbdc: addiu v0,a0,-0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 0027fbe0: b 0x0027fd08 */ /* delay 0027fbe4 */ sw(ea(28,(int32_t)UINT32_C(0xffffd0ac)),(uint32_t)cpu(2));goto L_0027fd08;
L_0027fbe8:;
/* 0027fbe8: blezl v1,0x0027fc00 */ {int taken=((int64_t)cpu(3)<=0);if(taken){/* delay 0027fbec */ set(2,sx((uint32_t)cpu(5)<<24));goto L_0027fc00;}}
/* 0027fbf0: addiu v0,v1,-0x1 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
L_0027fbf4:;
/* 0027fbf4: b 0x0027fd08 */ /* delay 0027fbf8 */ sw(ea(28,(int32_t)UINT32_C(0xffffd0a8)),(uint32_t)cpu(2));goto L_0027fd08;
L_0027fc00:;
/* 0027fc00: bgez v0,0x0027fd00 */ {int taken=((int64_t)cpu(2)>=0);/* delay 0027fc04 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_0027fd00;}}
/* 0027fc08: bne v1,zero,0x0027fd00 */ {int taken=(cpu(3)!=cpu(0));/* delay 0027fc0c */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd0a4)));if(taken){goto L_0027fd00;}}
/* 0027fc10: slti v0,v1,0x4 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 0027fc14: bnel v0,zero,0x0027fc30 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0027fc18 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));goto L_0027fc30;}}
/* 0027fc1c: addiu v0,v1,-0x4 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0xfffffffc)));
/* 0027fc20: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 0027fc24: sw v0,-0x2f54(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0ac)),(uint32_t)cpu(2));
/* 0027fc28: b 0x0027fd08 */ /* delay 0027fc2c */ sw(ea(28,(int32_t)UINT32_C(0xffffd0a8)),(uint32_t)cpu(3));goto L_0027fd08;
L_0027fc30:;
/* 0027fc30: sw zero,-0x2f54(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0ac)),(uint32_t)cpu(0));
/* 0027fc34: b 0x0027fd08 */ /* delay 0027fc38 */ sw(ea(28,(int32_t)UINT32_C(0xffffd0a8)),(uint32_t)cpu(2));goto L_0027fd08;
L_0027fc40:;
/* 0027fc40: lbu v0,0x27(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x00000027))));
/* 0027fc44: andi v0,v0,0x2 */ set(2,cpu(2)&UINT32_C(0x00000002));
/* 0027fc48: beq v0,zero,0x0027fcc0 */ {int taken=(cpu(2)==cpu(0));/* delay 0027fc4c */ lw(4,ea(28,(int32_t)UINT32_C(0xffffd0a4)));if(taken){goto L_0027fcc0;}}
/* 0027fc50: lw a1,-0x2f54(gp) */ lw(5,ea(28,(int32_t)UINT32_C(0xffffd0ac)));
/* 0027fc54: addiu v0,a0,-0x4 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffc)));
/* 0027fc58: slt v0,a1,v0 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(2));
/* 0027fc5c: beq v0,zero,0x0027fc80 */ {int taken=(cpu(2)==cpu(0));/* delay 0027fc60 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd0a8)));if(taken){goto L_0027fc80;}}
/* 0027fc64: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 0027fc68: bnel v1,v0,0x0027fca0 */ {int taken=(cpu(3)!=cpu(2));if(taken){/* delay 0027fc6c */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));goto L_0027fca0;}}
/* 0027fc70: addiu v0,a1,0x1 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 0027fc74: b 0x0027fd08 */ /* delay 0027fc78 */ sw(ea(28,(int32_t)UINT32_C(0xffffd0ac)),(uint32_t)cpu(2));goto L_0027fd08;
L_0027fc80:;
/* 0027fc80: addiu v0,a0,-0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 0027fc84: slt v0,v1,v0 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(2));
/* 0027fc88: beq v0,zero,0x0027fca8 */ {int taken=(cpu(2)==cpu(0));/* delay 0027fc8c */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0x00005810)));if(taken){goto L_0027fca8;}}
/* 0027fc90: slti v0,v1,0x3 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000003));
/* 0027fc94: beql v0,zero,0x0027fca8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0027fc98 */ set(2,sx((uint32_t)cpu(6)+UINT32_C(0x00005810)));goto L_0027fca8;}}
/* 0027fc9c: addiu v0,v1,0x1 */ set(2,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
L_0027fca0:;
/* 0027fca0: b 0x0027fd08 */ /* delay 0027fca4 */ sw(ea(28,(int32_t)UINT32_C(0xffffd0a8)),(uint32_t)cpu(2));goto L_0027fd08;
L_0027fca8:;
/* 0027fca8: lb v1,0x27(v0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000027))));
/* 0027fcac: bgezl v1,0x0027fd00 */ {int taken=((int64_t)cpu(3)>=0);if(taken){/* delay 0027fcb0 */ set(2,sx(UINT32_C(0xffffffff)));goto L_0027fd00;}}
/* 0027fcb4: sw zero,-0x2f54(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd0ac)),(uint32_t)cpu(0));
/* 0027fcb8: b 0x0027fd08 */ /* delay 0027fcbc */ sw(ea(28,(int32_t)UINT32_C(0xffffd0a8)),(uint32_t)cpu(0));goto L_0027fd08;
L_0027fcc0:;
/* 0027fcc0: lb v0,0x23(v1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000023))));
/* 0027fcc4: bgezl v0,0x0027fcd8 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 0027fcc8 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00000021))));goto L_0027fcd8;}}
/* 0027fccc: sb zero,-0x2f6f(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffd091)),(uint8_t)cpu(0));
/* 0027fcd0: jr ra */ {uint64_t target=cpu(31);/* delay 0027fcd4 */ set(2,sx(UINT32_C(0xfffffffe)));checkReturn(target,incoming);return;}
L_0027fcd8:;
/* 0027fcd8: bgezl v0,0x0027fd00 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 0027fcdc */ set(2,sx(UINT32_C(0xffffffff)));goto L_0027fd00;}}
/* 0027fce0: lw v0,-0x2f58(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd0a8)));
/* 0027fce4: lw v1,-0x2f54(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd0ac)));
/* 0027fce8: sb zero,-0x2f6f(gp) */ sb(ea(28,(int32_t)UINT32_C(0xffffd091)),(uint8_t)cpu(0));
/* 0027fcec: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 0027fcf0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0027fcf4: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 0027fcf8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0027fcfc: lw v0,0x5400(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00005400)));
L_0027fd00:;
/* 0027fd00: jr ra */ {uint64_t target=cpu(31);/* delay 0027fd04 */ checkReturn(target,incoming);return;}
L_0027fd08:;
/* 0027fd08: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 0027fd0c: jr ra */ {uint64_t target=cpu(31);/* delay 0027fd10 */ checkReturn(target,incoming);return;}
}
static void body_00282270(void){
uint64_t incoming=cpu(31);
/* 00282270: lb v0,-0x2f33(gp) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffd0cd))));
/* 00282274: addiu sp,sp,-0xc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff40)));
/* 00282278: sd s0,0x70(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 0028227c: sd s1,0x78(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00282280: sd s2,0x80(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00282284: sd s3,0x88(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 00282288: sd s4,0x90(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 0028228c: sd s5,0x98(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 00282290: sd s6,0xa0(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 00282294: sd s7,0xa8(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 00282298: sd s8,0xb0(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 0028229c: beq v0,zero,0x0028278c */ {int taken=(cpu(2)==cpu(0));/* delay 002822a0 */ save(31,ea(29,(int32_t)UINT32_C(0x000000b8)));if(taken){goto L_0028278c;}}
/* 002822a4: jal 0x002469a0 */ set(31,UINT64_C(0x002822ac));/* delay 002822a8 */ body_002469a0();
/* 002822ac: move s2,v0 */ set(18,cpu(2));
/* 002822b0: beq s2,zero,0x0028278c */ {int taken=(cpu(18)==cpu(0));/* delay 002822b4 */ set(7,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));if(taken){goto L_0028278c;}}
/* 002822b8: addiu t0,sp,0x40 */ set(8,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
/* 002822bc: addiu t8,sp,0x30 */ set(24,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));
/* 002822c0: addiu v0,sp,0x10 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002822c4: lw a2,0x0(s2) */ lw(6,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 002822c8: move s3,zero */ set(19,cpu(0));
/* 002822cc: move s5,v0 */ set(21,cpu(2));
/* 002822d0: li t4,-0x1 */ set(12,sx(UINT32_C(0xffffffff)));
/* 002822d4: move s4,a3 */ set(20,cpu(7));
/* 002822d8: move s1,t0 */ set(17,cpu(8));
/* 002822dc: move s0,t8 */ set(16,cpu(24));
/* 002822e0: li t7,0x41 */ set(15,sx(UINT32_C(0x00000041)));
/* 002822e4: li t6,0x1 */ set(14,sx(UINT32_C(0x00000001)));
L_002822e8:;
/* 002822e8: sll v0,s3,0x2 */ set(2,sx((uint32_t)cpu(19)<<2));
/* 002822ec: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002822f0: addu t3,s0,v0 */ set(11,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002822f4: addu t1,s5,v0 */ set(9,sx((uint32_t)cpu(21)+(uint32_t)cpu(2)));
/* 002822f8: addu t2,s4,v0 */ set(10,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 002822fc: addu v0,s1,v0 */ set(2,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 00282300: sw t4,0x0(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 00282304: sw t4,0x0(t2) */ sw(ea(10,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 00282308: sw t4,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 0028230c: sw t4,0x0(t3) */ sw(ea(11,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));
/* 00282310: lw v0,0x78(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000078)));
/* 00282314: andi v0,v0,0x41 */ set(2,cpu(2)&UINT32_C(0x00000041));
/* 00282318: bne v0,t7,0x00282348 */ {int taken=(cpu(2)!=cpu(15));/* delay 0028231c */ set(13,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_00282348;}}
/* 00282320: lh a1,0x90(a2) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(6,(int32_t)UINT32_C(0x00000090))));
/* 00282324: lw v1,0x10(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000010)));
/* 00282328: sll v0,a1,0x7 */ set(2,sx((uint32_t)cpu(5)<<7));
/* 0028232c: sw a1,0x0(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
/* 00282330: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00282334: lh a0,0x4(v0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000004))));
/* 00282338: sw a0,0x0(t2) */ sw(ea(10,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 0028233c: lw v0,0x70(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000070)));
/* 00282340: beql v0,t6,0x00282348 */ {int taken=(cpu(2)==cpu(14));if(taken){/* delay 00282344 */ sw(ea(11,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_00282348;}}
L_00282348:;
/* 00282348: bne t5,zero,0x002822e8 */ {int taken=(cpu(13)!=cpu(0));/* delay 0028234c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x000000f0)));if(taken){goto L_002822e8;}}
/* 00282350: lw v0,0x60(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000060)));
/* 00282354: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 00282358: bne v0,zero,0x002823ec */ {int taken=(cpu(2)!=cpu(0));/* delay 0028235c */ set(5,sx(UINT32_C(0x00000153)));if(taken){goto L_002823ec;}}
/* 00282360: lb t1,0x54(s2) */ set(9,(uint64_t)(int64_t)(int8_t)byte(ea(18,(int32_t)UINT32_C(0x00000054))));
/* 00282364: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 00282368: beq t1,v0,0x002823ec */ {int taken=(cpu(9)==cpu(2));/* delay 0028236c */ set(13,cpu(0));if(taken){goto L_002823ec;}}
/* 00282370: addiu t6,s2,0x8 */ set(14,sx((uint32_t)cpu(18)+UINT32_C(0x00000008)));
/* 00282374: li s0,-0x1 */ set(16,sx(UINT32_C(0xffffffff)));
/* 00282378: li s3,0xb */ set(19,sx(UINT32_C(0x0000000b)));
/* 0028237c: move t7,t6 */ set(15,cpu(14));
L_00282380:;
/* 00282380: addiu a0,t1,0x40 */ set(4,sx((uint32_t)cpu(9)+UINT32_C(0x00000040)));
/* 00282384: addu v0,t6,a0 */ set(2,sx((uint32_t)cpu(14)+(uint32_t)cpu(4)));
/* 00282388: lb v1,0x0(v0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 0028238c: beq v1,s0,0x002823d4 */ {int taken=(cpu(3)==cpu(16));/* delay 00282390 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));if(taken){goto L_002823d4;}}
/* 00282394: addu t4,t7,a0 */ set(12,sx((uint32_t)cpu(15)+(uint32_t)cpu(4)));
/* 00282398: move a2,zero */ set(6,cpu(0));
/* 0028239c: move t3,v1 */ set(11,cpu(3));
/* 002823a0: move t2,t0 */ set(10,cpu(8));
/* 002823a4: sll v0,a2,0x2 */ set(2,sx((uint32_t)cpu(6)<<2));
L_002823a8:;
/* 002823a8: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 002823ac: addu v1,t3,v0 */ set(3,sx((uint32_t)cpu(11)+(uint32_t)cpu(2)));
/* 002823b0: addu a1,t2,v0 */ set(5,sx((uint32_t)cpu(10)+(uint32_t)cpu(2)));
/* 002823b4: lw a0,0x0(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002823b8: lb v0,0x0(t4) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(12,(int32_t)UINT32_C(0x00000000))));
/* 002823bc: bne v0,a0,0x002823cc */ {int taken=(cpu(2)!=cpu(4));/* delay 002823c0 */ set(3,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_002823cc;}}
/* 002823c4: sw t5,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(13));
/* 002823c8: addiu t5,t5,0x1 */ set(13,sx((uint32_t)cpu(13)+UINT32_C(0x00000001)));
L_002823cc:;
/* 002823cc: bne v1,zero,0x002823a8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002823d0 */ set(2,sx((uint32_t)cpu(6)<<2));if(taken){goto L_002823a8;}}
L_002823d4:;
/* 002823d4: addiu t1,t1,0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0x00000001)));
/* 002823d8: addiu s3,s3,-0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffffff)));
/* 002823dc: slti v0,t1,0xc */ set(2,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x0000000c));
/* 002823e0: bgez s3,0x00282380 */ {int taken=((int64_t)cpu(19)>=0);/* delay 002823e4 */ if(cpu(2)==0){set(9,cpu(0));}if(taken){goto L_00282380;}}
/* 002823e8: li a1,0x153 */ set(5,sx(UINT32_C(0x00000153)));
L_002823ec:;
/* 002823ec: sw zero,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(0));
/* 002823f0: sw a1,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(5));
/* 002823f4: move s7,t0 */ set(23,cpu(8));
/* 002823f8: move s6,a3 */ set(22,cpu(7));
/* 002823fc: move s5,t8 */ set(21,cpu(24));
/* 00282400: move s3,zero */ set(19,cpu(0));
/* 00282404: li s8,0x3 */ set(30,sx(UINT32_C(0x00000003)));
/* 00282408: move s4,zero */ set(20,cpu(0));
/* 0028240c: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
/* 00282410: addiu s1,s1,0x53a4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x000053a4)));
/* 00282414: nop  */ 
L_00282418:;
/* 00282418: lw v0,0x0(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000000)));
/* 0028241c: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 00282420: bne v0,a2,0x00282438 */ {int taken=(cpu(2)!=cpu(6));/* delay 00282424 */ set(16,sx((uint32_t)cpu(19)<<2));if(taken){goto L_00282438;}}
/* 00282428: lw v0,0x54(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 0028242c: li t2,0xe6 */ set(10,sx(UINT32_C(0x000000e6)));
/* 00282430: b 0x00282468 */ /* delay 00282434 */ set(9,sx((uint32_t)cpu(2)+UINT32_C(0x00000153)));goto L_00282468;
L_00282438:;
/* 00282438: move a0,zero */ set(4,cpu(0));
/* 0028243c: jal 0x002c0c60 */ set(31,UINT64_C(0x00282444));/* delay 00282440 */ set(5,sx(UINT32_C(0x00000006)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002c0c60),UINT32_C(0x0028243c));
/* 00282444: move a0,zero */ set(4,cpu(0));
/* 00282448: addiu t2,v0,0xe3 */ set(10,sx((uint32_t)cpu(2)+UINT32_C(0x000000e3)));
/* 0028244c: li a1,0x6 */ set(5,sx(UINT32_C(0x00000006)));
/* 00282450: jal 0x002c0c60 */ set(31,UINT64_C(0x00282458));/* delay 00282454 */ sq(10,ea(29,(int32_t)UINT32_C(0x00000060)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002c0c60),UINT32_C(0x00282450));
/* 00282458: lw v1,0x50(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 0028245c: lq t2,0x60(sp) */ requestLq(10,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 00282460: addu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00282464: addiu t1,v0,-0x3 */ set(9,sx((uint32_t)cpu(2)+UINT32_C(0xfffffffd)));
L_00282468:;
/* 00282468: addiu a0,sp,0x10 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 0028246c: addu v0,a0,s0 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(16)));
/* 00282470: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 00282474: lw s0,0x0(v0) */ lw(16,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 00282478: beql s0,a0,0x002826a8 */ {int taken=(cpu(16)==cpu(4));if(taken){/* delay 0028247c */ set(4,cpu(10));goto L_002826a8;}}
/* 00282480: lb v0,0x54(s2) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(18,(int32_t)UINT32_C(0x00000054))));
/* 00282484: addu v0,v0,s2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(18)));
/* 00282488: lb v1,0x48(v0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00000048))));
/* 0028248c: bnel v1,s0,0x002824e4 */ {int taken=(cpu(3)!=cpu(16));if(taken){/* delay 00282490 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));goto L_002824e4;}}
/* 00282494: lw v0,0x0(s7) */ lw(2,ea(23,(int32_t)UINT32_C(0x00000000)));
/* 00282498: beq v0,a0,0x002824e0 */ {int taken=(cpu(2)==cpu(4));/* delay 0028249c */ set(5,sx(UINT32_C(0x00000010)));if(taken){goto L_002824e0;}}
/* 002824a0: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002824a4: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 002824a8: subu v0,a1,a0 */ set(2,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));
/* 002824ac: sw a2,-0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0xfffffffc)),(uint32_t)cpu(6));
/* 002824b0: div v0,s8 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(30),1,0);
/* 002824b4: beql s8,zero,0x002824bc */ {int taken=(cpu(30)==cpu(0));if(taken){/* delay 002824b8 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x002824b8));goto L_002824bc;}}
L_002824bc:;
/* 002824bc: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002824c0: slt v1,zero,v0 */ set(3,(int64_t)cpu(0)<(int64_t)cpu(2));
/* 002824c4: movz v0,a2,v1 */ if(cpu(3)==0){set(2,cpu(6));}
/* 002824c8: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002824cc: slti v0,a0,0x11 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002824d0: bne v0,zero,0x00282514 */ {int taken=(cpu(2)!=cpu(0));/* delay 002824d4 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));if(taken){goto L_00282514;}}
/* 002824d8: b 0x00282514 */ /* delay 002824dc */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));goto L_00282514;
L_002824e0:;
/* 002824e0: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
L_002824e4:;
/* 002824e4: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 002824e8: sw zero,-0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0xfffffffc)),(uint32_t)cpu(0));
/* 002824ec: beql s8,zero,0x002824f4 */ {int taken=(cpu(30)==cpu(0));if(taken){/* delay 002824f0 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x002824f0));goto L_002824f4;}}
L_002824f4:;
/* 002824f4: div a0,s8 */ nativeDivide((uint32_t)cpu(4),(uint32_t)cpu(30),1,0);
/* 002824f8: mflo v0 */ set(2,nocturneEffectHostLo());
/* 002824fc: slt v1,zero,v0 */ set(3,(int64_t)cpu(0)<(int64_t)cpu(2));
/* 00282500: movz v0,a1,v1 */ if(cpu(3)==0){set(2,cpu(5));}
/* 00282504: subu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(2)));
/* 00282508: slti v0,a0,0x0 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 0028250c: movn a0,zero,v0 */ if(cpu(2)!=0){set(4,cpu(0));}
/* 00282510: sw a0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
L_00282514:;
/* 00282514: lui a2,0x57 */ set(6,sx(UINT32_C(0x00570000)));
/* 00282518: lui v1,0x57 */ set(3,sx(UINT32_C(0x00570000)));
/* 0028251c: addiu a2,a2,0x53a8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x000053a8)));
/* 00282520: li a3,-0x1 */ set(7,sx(UINT32_C(0xffffffff)));
/* 00282524: addu a1,s4,a2 */ set(5,sx((uint32_t)cpu(20)+(uint32_t)cpu(6)));
/* 00282528: lw a2,0x0(s6) */ lw(6,ea(22,(int32_t)UINT32_C(0x00000000)));
/* 0028252c: lw v0,0x0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00282530: bne v0,a3,0x0028255c */ {int taken=(cpu(2)!=cpu(7));/* delay 00282534 */ set(8,sx((uint32_t)cpu(3)+UINT32_C(0x000053a0)));if(taken){goto L_0028255c;}}
/* 00282538: sll v0,a2,0x4 */ set(2,sx((uint32_t)cpu(6)<<4));
/* 0028253c: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00282540: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00282544: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00282548: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 0028254c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00282550: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00282554: lhu v1,0xa5a(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000a5a))));
/* 00282558: sw v1,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
L_0028255c:;
/* 0028255c: lw v0,0x0(s5) */ lw(2,ea(21,(int32_t)UINT32_C(0x00000000)));
/* 00282560: bne v0,a3,0x002825b0 */ {int taken=(cpu(2)!=cpu(7));/* delay 00282564 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(8)));if(taken){goto L_002825b0;}}
/* 00282568: addiu v0,s4,0x10 */ set(2,sx((uint32_t)cpu(20)+UINT32_C(0x00000010)));
/* 0028256c: addu v1,v0,t0 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(8)));
/* 00282570: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 00282574: blezl v0,0x00282588 */ {int taken=((int64_t)cpu(2)<=0);if(taken){/* delay 00282578 */ set(2,sx((uint32_t)cpu(6)<<4));goto L_00282588;}}
/* 0028257c: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00282580: b 0x002825b8 */ /* delay 00282584 */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_002825b8;
L_00282588:;
/* 00282588: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028258c: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00282590: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00282594: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00282598: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 0028259c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002825a0: lhu v1,0xa5a(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000a5a))));
/* 002825a4: b 0x002825b8 */ /* delay 002825a8 */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));goto L_002825b8;
L_002825b0:;
/* 002825b0: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 002825b4: sw a0,0x10(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(4));
L_002825b8:;
/* 002825b8: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 002825bc: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002825c0: addiu v0,v0,0x53ac */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x000053ac)));
/* 002825c4: addu a1,s4,v0 */ set(5,sx((uint32_t)cpu(20)+(uint32_t)cpu(2)));
/* 002825c8: lw v0,0x0(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002825cc: bne v0,v1,0x002825fc */ {int taken=(cpu(2)!=cpu(3));/* delay 002825d0 */ set(4,sx(UINT32_C(0x00570000)));if(taken){goto L_002825fc;}}
/* 002825d4: sll v0,a2,0x4 */ set(2,sx((uint32_t)cpu(6)<<4));
/* 002825d8: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 002825dc: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 002825e0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002825e4: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 002825e8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002825ec: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 002825f0: lhu v1,0xa5e(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000a5e))));
/* 002825f4: sw v1,0x0(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 002825f8: lui a0,0x57 */ set(4,sx(UINT32_C(0x00570000)));
L_002825fc:;
/* 002825fc: addiu v0,s4,0x10 */ set(2,sx((uint32_t)cpu(20)+UINT32_C(0x00000010)));
/* 00282600: addiu a0,a0,0x53a4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000053a4)));
/* 00282604: addu a3,v0,a0 */ set(7,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00282608: lw v0,0x0(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 0028260c: blezl v0,0x00282648 */ {int taken=((int64_t)cpu(2)<=0);if(taken){/* delay 00282610 */ set(2,sx((uint32_t)cpu(6)<<4));goto L_00282648;}}
/* 00282614: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 00282618: bgtz v0,0x0028267c */ {int taken=((int64_t)cpu(2)>0);/* delay 0028261c */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_0028267c;}}
/* 00282620: sll v0,a2,0x4 */ set(2,sx((uint32_t)cpu(6)<<4));
/* 00282624: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00282628: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 0028262c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00282630: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00282634: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00282638: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0028263c: lhu v1,0xa5e(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000a5e))));
/* 00282640: b 0x0028267c */ /* delay 00282644 */ sw(ea(5,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));goto L_0028267c;
L_00282648:;
/* 00282648: lw a0,-0x5750(gp) */ lw(4,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 0028264c: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 00282650: lw a1,0x0(a1) */ lw(5,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 00282654: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00282658: subu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(6)));
/* 0028265c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00282660: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00282664: lhu v1,0xa5e(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000a5e))));
/* 00282668: slt v1,v1,a1 */ set(3,(int64_t)cpu(3)<(int64_t)cpu(5));
/* 0028266c: beql v1,zero,0x00282680 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00282670 */ set(5,cpu(9));goto L_00282680;}}
/* 00282674: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
/* 00282678: sw a1,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
L_0028267c:;
/* 0028267c: move a1,t1 */ set(5,cpu(9));
L_00282680:;
/* 00282680: lw t1,-0x4(s1) */ lw(9,ea(17,(int32_t)UINT32_C(0xfffffffc)));
/* 00282684: lw a3,0x0(s6) */ lw(7,ea(22,(int32_t)UINT32_C(0x00000000)));
/* 00282688: move a0,t2 */ set(4,cpu(10));
/* 0028268c: lw t0,0x0(s7) */ lw(8,ea(23,(int32_t)UINT32_C(0x00000000)));
/* 00282690: move a2,s3 */ set(6,cpu(19));
/* 00282694: jal 0x0027ab10 */ set(31,UINT64_C(0x0028269c));/* delay 00282698 */ set(10,cpu(18));if(!nocturneBattlePanelColorCallerBody(UINT32_C(0x0027ab10)))abort();
/* 0028269c: b 0x002826e8 */ /* delay 002826a0 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_002826e8;
L_002826a8:;
/* 002826a8: move a2,s2 */ set(6,cpu(18));
/* 002826ac: jal 0x0027aa40 */ set(31,UINT64_C(0x002826b4));/* delay 002826b0 */ set(5,cpu(9));body_0027aa40();
/* 002826b4: sw zero,-0x4(s1) */ sw(ea(17,(int32_t)UINT32_C(0xfffffffc)),(uint32_t)cpu(0));
/* 002826b8: lui a2,0x57 */ set(6,sx(UINT32_C(0x00570000)));
/* 002826bc: lui a0,0x57 */ set(4,sx(UINT32_C(0x00570000)));
/* 002826c0: addiu a2,a2,0x53a8 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x000053a8)));
/* 002826c4: addiu a0,a0,0x53ac */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000053ac)));
/* 002826c8: addu v0,s4,a2 */ set(2,sx((uint32_t)cpu(20)+(uint32_t)cpu(6)));
/* 002826cc: addu v1,s4,a0 */ set(3,sx((uint32_t)cpu(20)+(uint32_t)cpu(4)));
/* 002826d0: sw zero,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002826d4: sw s0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002826d8: sw s0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002826dc: sw zero,0xc(s1) */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 002826e0: sw zero,0x10(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002826e4: lw a1,0x50(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000050)));
L_002826e8:;
/* 002826e8: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 002826ec: lw a2,0x54(sp) */ lw(6,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 002826f0: slti v0,s3,0x4 */ set(2,(int64_t)cpu(19)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 002826f4: addiu a1,a1,0x17 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000017)));
/* 002826f8: addiu s4,s4,0x18 */ set(20,sx((uint32_t)cpu(20)+UINT32_C(0x00000018)));
/* 002826fc: addiu a2,a2,0x17 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000017)));
/* 00282700: addiu s7,s7,0x4 */ set(23,sx((uint32_t)cpu(23)+UINT32_C(0x00000004)));
/* 00282704: addiu s6,s6,0x4 */ set(22,sx((uint32_t)cpu(22)+UINT32_C(0x00000004)));
/* 00282708: addiu s5,s5,0x4 */ set(21,sx((uint32_t)cpu(21)+UINT32_C(0x00000004)));
/* 0028270c: addiu s1,s1,0x18 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));
/* 00282710: sw a1,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(5));
/* 00282714: bne v0,zero,0x00282418 */ {int taken=(cpu(2)!=cpu(0));/* delay 00282718 */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(6));if(taken){goto L_00282418;}}
/* 0028271c: jal 0x00279980 */ set(31,UINT64_C(0x00282724));/* delay 00282720 */ set(4,cpu(0));body_00279980();
/* 00282724: lw v0,-0x2ff0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 00282728: li a0,0x103 */ set(4,sx(UINT32_C(0x00000103)));
/* 0028272c: li a1,0x14f */ set(5,sx(UINT32_C(0x0000014f)));
/* 00282730: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 00282734: li a2,0xfd */ set(6,sx(UINT32_C(0x000000fd)));
/* 00282738: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 0028273c: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 00282740: lw v0,0x124(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000124)));
/* 00282744: li t1,0x73 */ set(9,sx(UINT32_C(0x00000073)));
/* 00282748: li t2,0xfd */ set(10,sx(UINT32_C(0x000000fd)));
/* 0028274c: li t3,0x3 */ set(11,sx(UINT32_C(0x00000003)));
/* 00282750: jal 0x00279a88 */ set(31,UINT64_C(0x00282758));/* delay 00282754 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_00279a88();
/* 00282758: lw v0,-0x2ff0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd010)));
/* 0028275c: li a0,0x103 */ set(4,sx(UINT32_C(0x00000103)));
/* 00282760: li a1,0x1ae */ set(5,sx(UINT32_C(0x000001ae)));
/* 00282764: li a2,0xfd */ set(6,sx(UINT32_C(0x000000fd)));
/* 00282768: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 0028276c: li a3,0x3 */ set(7,sx(UINT32_C(0x00000003)));
/* 00282770: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 00282774: li t1,0x73 */ set(9,sx(UINT32_C(0x00000073)));
/* 00282778: lw v0,0x124(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000124)));
/* 0028277c: li t2,0xfd */ set(10,sx(UINT32_C(0x000000fd)));
/* 00282780: li t3,0x3 */ set(11,sx(UINT32_C(0x00000003)));
/* 00282784: jal 0x00279a88 */ set(31,UINT64_C(0x0028278c));/* delay 00282788 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));body_00279a88();
L_0028278c:;
/* 0028278c: ld s0,0x70(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 00282790: ld s1,0x78(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 00282794: ld s2,0x80(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 00282798: ld s3,0x88(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 0028279c: ld s4,0x90(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002827a0: ld s5,0x98(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002827a4: ld s6,0xa0(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002827a8: ld s7,0xa8(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002827ac: ld s8,0xb0(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 002827b0: ld ra,0xb8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 002827b4: jr ra */ {uint64_t target=cpu(31);/* delay 002827b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000c0)));checkReturn(target,incoming);return;}
}
static void body_002a89c0(void){
uint64_t incoming=cpu(31);
/* 002a89c0: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 002a89c4: beq v1,zero,0x002a89d4 */ {int taken=(cpu(3)==cpu(0));/* delay 002a89c8 */ if(taken){goto L_002a89d4;}}
/* 002a89cc: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 002a89d0: sw v0,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002a89d4:;
/* 002a89d4: jr ra */ {uint64_t target=cpu(31);/* delay 002a89d8 */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
static void body_002a8a30(void){
uint64_t incoming=cpu(31);
/* 002a8a30: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a8a34: move t0,a1 */ set(8,cpu(5));
/* 002a8a38: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8a3c: move a3,a0 */ set(7,cpu(4));
/* 002a8a40: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8a44: lhu v0,0x14(t0) */ set(2,half(ea(8,(int32_t)UINT32_C(0x00000014))));
/* 002a8a48: lh t2,0xa(a3) */ set(10,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x0000000a))));
/* 002a8a4c: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002a8a50: lh v1,0x16(t0) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(8,(int32_t)UINT32_C(0x00000016))));
/* 002a8a54: sh v0,0x14(t0) */ sh(ea(8,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(2));
/* 002a8a58: sll v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)<<16));
/* 002a8a5c: subu a1,t2,v1 */ set(5,sx((uint32_t)cpu(10)-(uint32_t)cpu(3)));
/* 002a8a60: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 002a8a64: lh a2,0x8(a3) */ set(6,(uint64_t)(int64_t)(int16_t)half(ea(7,(int32_t)UINT32_C(0x00000008))));
/* 002a8a68: sra t1,v0,0x10 */ set(9,sx((uint32_t)((int32_t)cpu(2)>>16)));
/* 002a8a6c: lw a3,0x4(t0) */ lw(7,ea(8,(int32_t)UINT32_C(0x00000004)));
/* 002a8a70: sll v0,v1,0x10 */ set(2,sx((uint32_t)cpu(3)<<16));
/* 002a8a74: mult a1,a1,a2 */ nativeMultiply(5,(uint32_t)cpu(5),(uint32_t)cpu(6),1,0);
/* 002a8a78: sh v1,0x16(t0) */ sh(ea(8,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(3));
/* 002a8a7c: bne v0,zero,0x002a8a9c */ {int taken=(cpu(2)!=cpu(0));/* delay 002a8a80 */ set(16,sx((uint32_t)cpu(7)+(uint32_t)cpu(5)));if(taken){goto L_002a8a9c;}}
/* 002a8a84: lui v0,0x2b */ set(2,sx(UINT32_C(0x002b0000)));
/* 002a8a88: addiu v0,v0,-0x7620 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff89e0)));
/* 002a8a8c: bne t1,t2,0x002a8a9c */ {int taken=(cpu(9)!=cpu(10));/* delay 002a8a90 */ sw(ea(8,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002a8a9c;}}
/* 002a8a94: jal 0x002a89c0 */ set(31,UINT64_C(0x002a8a9c));/* delay 002a8a98 */ body_002a89c0();
L_002a8a9c:;
/* 002a8a9c: move v0,s0 */ set(2,cpu(16));
/* 002a8aa0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8aa4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8aa8: jr ra */ {uint64_t target=cpu(31);/* delay 002a8aac */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002a8ab0(void){
uint64_t incoming=cpu(31);
/* 002a8ab0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002a8ab4: lw v0,-0x2114(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffdeec)));
/* 002a8ab8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8abc: move a3,a0 */ set(7,cpu(4));
/* 002a8ac0: lui v1,0x2b */ set(3,sx(UINT32_C(0x002b0000)));
/* 002a8ac4: move a1,v0 */ set(5,cpu(2));
/* 002a8ac8: lw a2,0x0(v0) */ lw(6,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 002a8acc: addiu v1,v1,-0x75d0 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffff8a30)));
/* 002a8ad0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8ad4: sw a2,-0x2114(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffdeec)),(uint32_t)cpu(6));
/* 002a8ad8: sh zero,0x14(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(0));
/* 002a8adc: sw v1,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002a8ae0: lhu a2,0xa(a3) */ set(6,half(ea(7,(int32_t)UINT32_C(0x0000000a))));
/* 002a8ae4: sw v0,0x0(a3) */ sw(ea(7,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a8ae8: sh a2,0x16(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(6));
/* 002a8aec: sw a3,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(7));
/* 002a8af0: j 0x002a8a30 */ /* delay 002a8af4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002a8a30();return;
}
static void body_002a8af8(void){
uint64_t incoming=cpu(31);
/* 002a8af8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002a8afc: addiu v0,a0,-0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 002a8b00: slti a0,a0,0x11 */ set(4,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000011));
/* 002a8b04: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8b08: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8b0c: move a1,zero */ set(5,cpu(0));
/* 002a8b10: bne a0,zero,0x002a8b28 */ {int taken=(cpu(4)!=cpu(0));/* delay 002a8b14 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002a8b28;}}
/* 002a8b18: plzcw a1,v0 */ prerequisitePlzcw(5,2);
/* 002a8b1c: li v1,0x1b */ set(3,sx(UINT32_C(0x0000001b)));
/* 002a8b20: andi v0,a1,0xff */ set(2,cpu(5)&UINT32_C(0x000000ff));
/* 002a8b24: subu a1,v1,v0 */ set(5,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
L_002a8b28:;
/* 002a8b28: sll v0,a1,0x1 */ set(2,sx((uint32_t)cpu(5)<<1));
/* 002a8b2c: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002a8b30: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002a8b34: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 002a8b38: addiu s0,s0,0x7ec0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00007ec0)));
/* 002a8b3c: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002a8b40: jal 0x002e4070 */ set(31,UINT64_C(0x002a8b48));/* delay 002a8b44 */ nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002e4070),UINT32_C(0x002a8b40));
/* 002a8b48: move s1,v0 */ set(17,cpu(2));
/* 002a8b4c: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002a8b50: move a0,s0 */ set(4,cpu(16));
/* 002a8b54: bne v0,zero,0x002a8b70 */ {int taken=(cpu(2)!=cpu(0));/* delay 002a8b58 */ set(5,cpu(2));if(taken){goto L_002a8b70;}}
/* 002a8b5c: jal 0x002a8ab0 */ set(31,UINT64_C(0x002a8b64));/* delay 002a8b60 */ body_002a8ab0();
/* 002a8b64: b 0x002a8b80 */ /* delay 002a8b68 */ set(16,cpu(2));goto L_002a8b80;
L_002a8b70:;
/* 002a8b70: lw v0,0x8(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 002a8b74: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002a8b7c));/* delay 002a8b78 */ set(4,cpu(16));nocturneBattlePanelColorPrerequisiteIndirect(target,UINT32_C(0x002a8b74));}
/* 002a8b7c: move s0,v0 */ set(16,cpu(2));
L_002a8b80:;
/* 002a8b80: beq s1,zero,0x002a8b94 */ {int taken=(cpu(17)==cpu(0));/* delay 002a8b84 */ set(2,cpu(16));if(taken){goto L_002a8b94;}}
/* 002a8b88: jal 0x002e40b8 */ set(31,UINT64_C(0x002a8b90));/* delay 002a8b8c */ nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002e40b8),UINT32_C(0x002a8b88));
/* 002a8b90: move v0,s0 */ set(2,cpu(16));
L_002a8b94:;
/* 002a8b94: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8b98: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8b9c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a8ba0: jr ra */ {uint64_t target=cpu(31);/* delay 002a8ba4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002aa980(void){
uint64_t incoming=cpu(31);
/* 002aa980: addiu a0,a0,-0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 002aa984: sltiu v0,a0,0x3a */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000003a));
/* 002aa988: beq v0,zero,0x002aa9cc */ {int taken=(cpu(2)==cpu(0));/* delay 002aa98c */ set(2,sx(UINT32_C(0x00000020)));if(taken){goto L_002aa9cc;}}
/* 002aa990: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 002aa994: lui v1,0x55 */ set(3,sx(UINT32_C(0x00550000)));
/* 002aa998: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002aa99c: lw v1,-0x6ce0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0xffff9320)));
/* 002aa9a0: jr v1 */ {uint64_t target=cpu(3);/* delay 002aa9a4 */ switch((uint32_t)target){case UINT32_C(0x002aa9a8):goto L_002aa9a8;case UINT32_C(0x002aa9b0):goto L_002aa9b0;case UINT32_C(0x002aa9b8):goto L_002aa9b8;case UINT32_C(0x002aa9c0):goto L_002aa9c0;case UINT32_C(0x002aa9c8):goto L_002aa9c8;default:abort();}}
L_002aa9a8:;
/* 002aa9a8: b 0x002aa9cc */ /* delay 002aa9ac */ set(2,sx(UINT32_C(0x00000018)));goto L_002aa9cc;
L_002aa9b0:;
/* 002aa9b0: b 0x002aa9cc */ /* delay 002aa9b4 */ set(2,sx(UINT32_C(0x00000010)));goto L_002aa9cc;
L_002aa9b8:;
/* 002aa9b8: b 0x002aa9cc */ /* delay 002aa9bc */ set(2,sx(UINT32_C(0x00000008)));goto L_002aa9cc;
L_002aa9c0:;
/* 002aa9c0: b 0x002aa9cc */ /* delay 002aa9c4 */ set(2,sx(UINT32_C(0x00000004)));goto L_002aa9cc;
L_002aa9c8:;
/* 002aa9c8: li v0,0x20 */ set(2,sx(UINT32_C(0x00000020)));
L_002aa9cc:;
/* 002aa9cc: mult v0,v0,a1 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(5),1,0);
/* 002aa9d0: mult1 v0,v0,a2 */ nativeMultiply(2,(uint32_t)cpu(2),(uint32_t)cpu(6),1,1);
/* 002aa9d4: jr ra */ {uint64_t target=cpu(31);/* delay 002aa9d8 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>7)));checkReturn(target,incoming);return;}
}
static void body_002aa9e0(void){
uint64_t incoming=cpu(31);
/* 002aa9e0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002aa9e4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002aa9e8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aa9ec: move s1,a0 */ set(17,cpu(4));
/* 002aa9f0: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002aa9f4: lui v0,0x58 */ set(2,sx(UINT32_C(0x00580000)));
/* 002aa9f8: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002aa9fc: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002aaa00: addiu s7,v0,0x1018 */ set(23,sx((uint32_t)cpu(2)+UINT32_C(0x00001018)));
/* 002aaa04: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aaa08: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aaa0c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aaa10: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002aaa14: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002aaa18: lbu s2,0x9(s1) */ set(18,byte(ea(17,(int32_t)UINT32_C(0x00000009))));
/* 002aaa1c: lhu s4,0x14(s1) */ set(20,half(ea(17,(int32_t)UINT32_C(0x00000014))));
/* 002aaa20: lhu s3,0x16(s1) */ set(19,half(ea(17,(int32_t)UINT32_C(0x00000016))));
/* 002aaa24: move a0,s2 */ set(4,cpu(18));
/* 002aaa28: lhu s0,0xa(s1) */ set(16,half(ea(17,(int32_t)UINT32_C(0x0000000a))));
/* 002aaa2c: move a1,s4 */ set(5,cpu(20));
/* 002aaa30: move a2,s3 */ set(6,cpu(19));
/* 002aaa34: dsll32 s3,s3,0x0 */ set(19,cpu(19)<<32);
/* 002aaa38: srl s0,s0,0x6 */ set(16,sx((uint32_t)cpu(16)>>6));
/* 002aaa3c: dsll32 s2,s2,0x18 */ set(18,cpu(18)<<56);
/* 002aaa40: jal 0x002aa980 */ set(31,UINT64_C(0x002aaa48));/* delay 002aaa44 */ if(cpu(16)==0){set(16,cpu(3));}body_002aa980();
/* 002aaa48: move s5,v0 */ set(21,cpu(2));
/* 002aaa4c: li v0,0x7ff0 */ set(2,sx(UINT32_C(0x00007ff0)));
/* 002aaa50: addiu v1,s5,0x7fef */ set(3,sx((uint32_t)cpu(21)+UINT32_C(0x00007fef)));
/* 002aaa54: beql v0,zero,0x002aaa5c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002aaa58 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x002aaa58));goto L_002aaa5c;}}
L_002aaa5c:;
/* 002aaa5c: div v1,v0 */ nativeDivide((uint32_t)cpu(3),(uint32_t)cpu(2),1,0);
/* 002aaa60: dsll32 s0,s0,0x10 */ set(16,cpu(16)<<48);
/* 002aaa64: or s2,s2,s0 */ set(18,cpu(18)|cpu(16));
/* 002aaa68: or s4,s4,s3 */ set(20,cpu(20)|cpu(19));
/* 002aaa6c: mflo v1 */ set(3,nocturneEffectHostLo());
/* 002aaa70: sll a0,v1,0x1 */ set(4,sx((uint32_t)cpu(3)<<1));
/* 002aaa74: addu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(3)));
/* 002aaa78: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 002aaa7c: jal 0x002a8af8 */ set(31,UINT64_C(0x002aaa84));/* delay 002aaa80 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000080)));body_002a8af8();
/* 002aaa84: lw v1,0x4(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000004)));
/* 002aaa88: move s6,v0 */ set(22,cpu(2));
/* 002aaa8c: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002aaa90: sw v1,0x8(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002aaa94: addiu s3,s6,0x10 */ set(19,sx((uint32_t)cpu(22)+UINT32_C(0x00000010)));
/* 002aaa98: sw v0,0x4(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002aaa9c: lui a2,0x1000 */ set(6,sx(UINT32_C(0x10000000)));
/* 002aaaa0: ori a2,a2,0x5 */ set(6,cpu(6)|UINT32_C(0x00000005));
/* 002aaaa4: sw zero,0x0(s6) */ sw(ea(22,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002aaaa8: li t4,0x52 */ set(12,sx(UINT32_C(0x00000052)));
/* 002aaaac: li t5,0x53 */ set(13,sx(UINT32_C(0x00000053)));
/* 002aaab0: lui a3,0x5000 */ set(7,sx(UINT32_C(0x50000000)));
/* 002aaab4: ori a3,a3,0x5 */ set(7,cpu(7)|UINT32_C(0x00000005));
/* 002aaab8: dsll32 a3,a3,0x0 */ set(7,cpu(7)<<32);
/* 002aaabc: lbu v0,0x8(s1) */ set(2,byte(ea(17,(int32_t)UINT32_C(0x00000008))));
/* 002aaac0: lui t0,0x1000 */ set(8,sx(UINT32_C(0x10000000)));
/* 002aaac4: dsll32 t0,t0,0x0 */ set(8,cpu(8)<<32);
/* 002aaac8: ori t0,t0,0x4 */ set(8,cpu(8)|UINT32_C(0x00000004));
/* 002aaacc: li t1,0xe */ set(9,sx(UINT32_C(0x0000000e)));
/* 002aaad0: li t2,0x50 */ set(10,sx(UINT32_C(0x00000050)));
/* 002aaad4: sb v0,0xc(s6) */ sb(ea(22,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(2));
/* 002aaad8: li t3,0x51 */ set(11,sx(UINT32_C(0x00000051)));
/* 002aaadc: sd a2,0x0(s3) */ save(6,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 002aaae0: addiu s0,s6,0x70 */ set(16,sx((uint32_t)cpu(22)+UINT32_C(0x00000070)));
/* 002aaae4: lw v0,0xc(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 002aaae8: lui t7,0x1000 */ set(15,sx(UINT32_C(0x10000000)));
/* 002aaaec: ori t7,t7,0x1 */ set(15,cpu(15)|UINT32_C(0x00000001));
/* 002aaaf0: lhu a0,0x12(s1) */ set(4,half(ea(17,(int32_t)UINT32_C(0x00000012))));
/* 002aaaf4: lui t6,0x5000 */ set(14,sx(UINT32_C(0x50000000)));
/* 002aaaf8: ori t6,t6,0x1 */ set(14,cpu(14)|UINT32_C(0x00000001));
/* 002aaafc: dsll32 t6,t6,0x0 */ set(14,cpu(14)<<32);
/* 002aab00: lhu v1,0x10(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x00000010))));
/* 002aab04: srl v0,v0,0x6 */ set(2,sx((uint32_t)cpu(2)>>6));
/* 002aab08: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002aab0c: dsll32 a0,a0,0x10 */ set(4,cpu(4)<<48);
/* 002aab10: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002aab14: or s2,s2,v0 */ set(18,cpu(18)|cpu(2));
/* 002aab18: or a0,a0,v1 */ set(4,cpu(4)|cpu(3));
/* 002aab1c: lw a1,0x0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002aab20: lui v0,0xfff */ set(2,sx(UINT32_C(0x0fff0000)));
/* 002aab24: sd s2,0x20(s3) */ save(18,ea(19,(int32_t)UINT32_C(0x00000020)));
/* 002aab28: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002aab2c: sd a0,0x30(s3) */ save(4,ea(19,(int32_t)UINT32_C(0x00000030)));
/* 002aab30: sd s4,0x40(s3) */ save(20,ea(19,(int32_t)UINT32_C(0x00000040)));
/* 002aab34: sd t4,0x48(s3) */ save(12,ea(19,(int32_t)UINT32_C(0x00000048)));
/* 002aab38: sd t5,0x58(s3) */ save(13,ea(19,(int32_t)UINT32_C(0x00000058)));
/* 002aab3c: sd zero,0x50(s3) */ save(0,ea(19,(int32_t)UINT32_C(0x00000050)));
/* 002aab40: sd a3,0x8(s3) */ save(7,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 002aab44: and a3,a1,v0 */ set(7,cpu(5)&cpu(2));
/* 002aab48: sd t0,0x10(s3) */ save(8,ea(19,(int32_t)UINT32_C(0x00000010)));
/* 002aab4c: move t0,zero */ set(8,cpu(0));
/* 002aab50: sd t1,0x18(s3) */ save(9,ea(19,(int32_t)UINT32_C(0x00000018)));
/* 002aab54: lui t1,0x5100 */ set(9,sx(UINT32_C(0x51000000)));
/* 002aab58: sd t2,0x28(s3) */ save(10,ea(19,(int32_t)UINT32_C(0x00000028)));
/* 002aab5c: lui t2,0x3000 */ set(10,sx(UINT32_C(0x30000000)));
/* 002aab60: sd t3,0x38(s3) */ save(11,ea(19,(int32_t)UINT32_C(0x00000038)));
/* 002aab64: ori t3,zero,0x8000 */ set(11,cpu(0)|UINT32_C(0x00008000));
/* 002aab68: dsll32 t3,t3,0xc */ set(11,cpu(11)<<44);
/* 002aab6c: nop  */ 
L_002aab70:;
/* 002aab70: slti v0,s5,0x7ff1 */ set(2,(int64_t)cpu(21)<(int64_t)(int32_t)UINT32_C(0x00007ff1));
/* 002aab74: beq v0,zero,0x002aab84 */ {int taken=(cpu(2)==cpu(0));/* delay 002aab78 */ set(6,sx(UINT32_C(0x00007ff0)));if(taken){goto L_002aab84;}}
/* 002aab7c: move a2,s5 */ set(6,cpu(21));
/* 002aab80: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
L_002aab84:;
/* 002aab84: dsll v1,t0,0xf */ set(3,cpu(8)<<15);
/* 002aab88: andi a0,a2,0xffff */ set(4,cpu(6)&UINT32_C(0x0000ffff));
/* 002aab8c: dsll32 v0,a3,0x0 */ set(2,cpu(7)<<32);
/* 002aab90: or v1,a2,v1 */ set(3,cpu(6)|cpu(3));
/* 002aab94: or a0,a0,t2 */ set(4,cpu(4)|cpu(10));
/* 002aab98: or a1,a2,t1 */ set(5,cpu(6)|cpu(9));
/* 002aab9c: or a0,a0,v0 */ set(4,cpu(4)|cpu(2));
/* 002aaba0: sll v0,a2,0x4 */ set(2,sx((uint32_t)cpu(6)<<4));
/* 002aaba4: or v1,v1,t3 */ set(3,cpu(3)|cpu(11));
/* 002aaba8: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002aabac: sd v1,0x10(s0) */ save(3,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002aabb0: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 002aabb4: sd a0,0x20(s0) */ save(4,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 002aabb8: subu s5,s5,a2 */ set(21,sx((uint32_t)cpu(21)-(uint32_t)cpu(6)));
/* 002aabbc: sd a1,0x28(s0) */ save(5,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002aabc0: sd t7,0x0(s0) */ save(15,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002aabc4: sd t6,0x8(s0) */ save(14,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002aabc8: beq t0,zero,0x002aab70 */ {int taken=(cpu(8)==cpu(0));/* delay 002aabcc */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000030)));if(taken){goto L_002aab70;}}
/* 002aabd0: jal 0x002dbee0 */ set(31,UINT64_C(0x002aabd8));/* delay 002aabd4 */ lw(4,ea(23,(int32_t)UINT32_C(0x00000000)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002dbee0),UINT32_C(0x002aabd0));
/* 002aabd8: lw v0,0x8(s7) */ lw(2,ea(23,(int32_t)UINT32_C(0x00000008)));
/* 002aabdc: beql v0,zero,0x002aabe8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002aabe0 */ sw(ea(23,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(22));goto L_002aabe8;}}
/* 002aabe4: sw s6,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(22));
L_002aabe8:;
/* 002aabe8: lui v0,0xfff */ set(2,sx(UINT32_C(0x0fff0000)));
/* 002aabec: lw a0,0x10(s7) */ lw(4,ea(23,(int32_t)UINT32_C(0x00000010)));
/* 002aabf0: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002aabf4: sw s6,0x8(s7) */ sw(ea(23,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(22));
/* 002aabf8: beq a0,zero,0x002aac18 */ {int taken=(cpu(4)==cpu(0));/* delay 002aabfc */ set(19,cpu(19)&cpu(2));if(taken){goto L_002aac18;}}
/* 002aac00: dsll32 v0,s3,0x0 */ set(2,cpu(19)<<32);
/* 002aac04: lui v1,0x2000 */ set(3,sx(UINT32_C(0x20000000)));
/* 002aac08: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002aac0c: sd zero,0x8(a0) */ save(0,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002aac10: b 0x002aac1c */ /* delay 002aac14 */ save(2,ea(4,(int32_t)UINT32_C(0x00000000)));goto L_002aac1c;
L_002aac18:;
/* 002aac18: sw s3,0xc(s7) */ sw(ea(23,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(19));
L_002aac1c:;
/* 002aac1c: sw s0,0x10(s7) */ sw(ea(23,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(16));
/* 002aac20: lw a0,0x0(s7) */ lw(4,ea(23,(int32_t)UINT32_C(0x00000000)));
/* 002aac24: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002aac28: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002aac2c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002aac30: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002aac34: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002aac38: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002aac3c: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002aac40: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002aac44: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002aac48: j 0x002dbec0 */ /* delay 002aac4c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(cpu(31),incoming);nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002dbec0),UINT32_C(0x002aac48));return;
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
/* 002ace68: clear v1 */ {const uint32_t q[4]={0,0,0,0};nocturneBattlePanelColorCpuWrite(3u,q);}
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
static void body_002af0f8(void){
uint64_t incoming=cpu(31);
/* 002af0f8: lw t4,0x0(sp) */ lw(12,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002af0fc: sll a3,a3,0x10 */ set(7,sx((uint32_t)cpu(7)<<16));
/* 002af100: lw t5,0x8(sp) */ lw(13,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002af104: andi a2,a2,0xffff */ set(6,cpu(6)&UINT32_C(0x0000ffff));
/* 002af108: lw v1,0x18(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002af10c: andi t1,t1,0xffff */ set(9,cpu(9)&UINT32_C(0x0000ffff));
/* 002af110: lw v0,0x20(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002af114: sll t2,t2,0x10 */ set(10,sx((uint32_t)cpu(10)<<16));
/* 002af118: andi t4,t4,0xffff */ set(12,cpu(12)&UINT32_C(0x0000ffff));
/* 002af11c: sll t5,t5,0x10 */ set(13,sx((uint32_t)cpu(13)<<16));
/* 002af120: sll v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)<<16));
/* 002af124: andi v1,v1,0xffff */ set(3,cpu(3)&UINT32_C(0x0000ffff));
/* 002af128: lw t6,0x10(sp) */ lw(14,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002af12c: or a2,a2,a3 */ set(6,cpu(6)|cpu(7));
/* 002af130: lw t7,0x28(sp) */ lw(15,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002af134: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002af138: or t1,t1,t2 */ set(9,cpu(9)|cpu(10));
/* 002af13c: or t4,t4,t5 */ set(12,cpu(12)|cpu(13));
/* 002af140: lw a3,0x30(sp) */ lw(7,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002af144: ori a1,a1,0x10c */ set(5,cpu(5)|UINT32_C(0x0000010c));
/* 002af148: dsll32 t0,t0,0x0 */ set(8,cpu(8)<<32);
/* 002af14c: dsll32 a2,a2,0x0 */ set(6,cpu(6)<<32);
/* 002af150: dsll32 t3,t3,0x0 */ set(11,cpu(11)<<32);
/* 002af154: dsll32 t1,t1,0x0 */ set(9,cpu(9)<<32);
/* 002af158: dsll32 t6,t6,0x0 */ set(14,cpu(14)<<32);
/* 002af15c: dsll32 t4,t4,0x0 */ set(12,cpu(12)<<32);
/* 002af160: dsll32 t7,t7,0x0 */ set(15,cpu(15)<<32);
/* 002af164: dsll32 v1,v1,0x0 */ set(3,cpu(3)<<32);
/* 002af168: dsll32 a3,a3,0x0 */ set(7,cpu(7)<<32);
/* 002af16c: ori v0,zero,0xfe00 */ set(2,cpu(0)|UINT32_C(0x0000fe00));
/* 002af170: dsll32 v0,v0,0xe */ set(2,cpu(2)<<46);
/* 002af174: dsll32 a1,a1,0x0 */ set(5,cpu(5)<<32);
/* 002af178: dsrl32 t0,t0,0x0 */ set(8,cpu(8)>>32);
/* 002af17c: dsrl32 a2,a2,0x0 */ set(6,cpu(6)>>32);
/* 002af180: dsrl32 t3,t3,0x0 */ set(11,cpu(11)>>32);
/* 002af184: dsrl32 t1,t1,0x0 */ set(9,cpu(9)>>32);
/* 002af188: dsrl32 t6,t6,0x0 */ set(14,cpu(14)>>32);
/* 002af18c: dsrl32 t4,t4,0x0 */ set(12,cpu(12)>>32);
/* 002af190: dsrl32 t7,t7,0x0 */ set(15,cpu(15)>>32);
/* 002af194: dsrl32 v1,v1,0x0 */ set(3,cpu(3)>>32);
/* 002af198: or t7,t7,v0 */ set(15,cpu(15)|cpu(2));
/* 002af19c: or v1,v1,a3 */ set(3,cpu(3)|cpu(7));
/* 002af1a0: or t0,t0,v0 */ set(8,cpu(8)|cpu(2));
/* 002af1a4: or a2,a2,a3 */ set(6,cpu(6)|cpu(7));
/* 002af1a8: or t3,t3,v0 */ set(11,cpu(11)|cpu(2));
/* 002af1ac: or t1,t1,a3 */ set(9,cpu(9)|cpu(7));
/* 002af1b0: or t6,t6,v0 */ set(14,cpu(14)|cpu(2));
/* 002af1b4: or t4,t4,a3 */ set(12,cpu(12)|cpu(7));
/* 002af1b8: li a3,0xf5 */ set(7,sx(UINT32_C(0x000000f5)));
/* 002af1bc: dsll a3,a3,0x10 */ set(7,cpu(7)<<16);
/* 002af1c0: ori a3,a3,0x1515 */ set(7,cpu(7)|UINT32_C(0x00001515));
/* 002af1c4: dsll a3,a3,0x10 */ set(7,cpu(7)<<16);
/* 002af1c8: ori a3,a3,0x1510 */ set(7,cpu(7)|UINT32_C(0x00001510));
/* 002af1cc: dsrl32 a1,a1,0x0 */ set(5,cpu(5)>>32);
/* 002af1d0: lui v0,0xa400 */ set(2,sx(UINT32_C(0xa4000000)));
/* 002af1d4: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002af1d8: ori v0,v0,0x8001 */ set(2,cpu(2)|UINT32_C(0x00008001));
/* 002af1dc: sd v1,0x50(a0) */ save(3,ea(4,(int32_t)UINT32_C(0x00000050)));
/* 002af1e0: sd v0,0x0(a0) */ save(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002af1e4: sd a3,0x8(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002af1e8: sd a1,0x10(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002af1ec: sd t0,0x18(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 002af1f0: sd a2,0x20(a0) */ save(6,ea(4,(int32_t)UINT32_C(0x00000020)));
/* 002af1f4: sd t3,0x28(a0) */ save(11,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002af1f8: sd t1,0x30(a0) */ save(9,ea(4,(int32_t)UINT32_C(0x00000030)));
/* 002af1fc: sd t6,0x38(a0) */ save(14,ea(4,(int32_t)UINT32_C(0x00000038)));
/* 002af200: sd t4,0x40(a0) */ save(12,ea(4,(int32_t)UINT32_C(0x00000040)));
/* 002af204: jr ra */ {uint64_t target=cpu(31);/* delay 002af208 */ save(15,ea(4,(int32_t)UINT32_C(0x00000048)));checkReturn(target,incoming);return;}
}
static void body_002af210(void){
uint64_t incoming=cpu(31);
/* 002af210: addiu sp,sp,-0xb0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff50)));
/* 002af214: lw v1,0xb8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 002af218: lw v0,0xe8(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x000000e8)));
/* 002af21c: sw v1,0x44(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(3));
/* 002af220: lw v1,0xc0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000c0)));
/* 002af224: sd s1,0x68(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002af228: move s1,a1 */ set(17,cpu(5));
/* 002af22c: sw v1,0x48(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(3));
/* 002af230: lw v1,0xc8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000c8)));
/* 002af234: sd s2,0x70(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002af238: move s2,a2 */ set(18,cpu(6));
/* 002af23c: sw v1,0x4c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(3));
/* 002af240: lw v1,0xd0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000d0)));
/* 002af244: sd s3,0x78(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002af248: move s3,a3 */ set(19,cpu(7));
/* 002af24c: sw v1,0x50(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(3));
/* 002af250: lw v1,0xd8(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000d8)));
/* 002af254: sd s4,0x80(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002af258: move s4,t0 */ set(20,cpu(8));
/* 002af25c: sw v1,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(3));
/* 002af260: lw v1,0xe0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x000000e0)));
/* 002af264: sd s5,0x88(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002af268: move s5,t1 */ set(21,cpu(9));
/* 002af26c: sd s6,0x90(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002af270: move s6,t2 */ set(22,cpu(10));
/* 002af274: sd s7,0x98(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002af278: move s7,t3 */ set(23,cpu(11));
/* 002af27c: sd s8,0xa0(sp) */ save(30,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002af280: sw a0,0x40(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(4));
/* 002af284: li a0,0x70 */ set(4,sx(UINT32_C(0x00000070)));
/* 002af288: sd s0,0x60(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002af28c: sd ra,0xa8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002af290: lw s8,0xb0(sp) */ lw(30,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 002af294: bne v0,zero,0x002af2a4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002af298 */ sw(ea(29,(int32_t)UINT32_C(0x00000058)),(uint32_t)cpu(3));if(taken){goto L_002af2a4;}}
/* 002af29c: lui v0,0x2b */ set(2,sx(UINT32_C(0x002b0000)));
/* 002af2a0: addiu v0,v0,-0x34b0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffcb50)));
L_002af2a4:;
/* 002af2a4: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002af2ac));/* delay 002af2a8 */ nocturneBattlePanelColorPrerequisiteIndirect(target,UINT32_C(0x002af2a4));}
/* 002af2ac: lui v1,0x5000 */ set(3,sx(UINT32_C(0x50000000)));
/* 002af2b0: ori v1,v1,0x6 */ set(3,cpu(3)|UINT32_C(0x00000006));
/* 002af2b4: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002af2b8: ori v1,v1,0x1000 */ set(3,cpu(3)|UINT32_C(0x00001000));
/* 002af2bc: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002af2c0: move s0,v0 */ set(16,cpu(2));
/* 002af2c4: lui v0,0x2000 */ set(2,sx(UINT32_C(0x20000000)));
/* 002af2c8: ori v0,v0,0x6 */ set(2,cpu(2)|UINT32_C(0x00000006));
/* 002af2cc: sd v0,0x0(s0) */ save(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002af2d0: move a1,s1 */ set(5,cpu(17));
/* 002af2d4: sd v1,0x8(s0) */ save(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002af2d8: move a2,s2 */ set(6,cpu(18));
/* 002af2dc: move a3,s3 */ set(7,cpu(19));
/* 002af2e0: move t0,s4 */ set(8,cpu(20));
/* 002af2e4: lw v0,0x44(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000044)));
/* 002af2e8: move t1,s5 */ set(9,cpu(21));
/* 002af2ec: lw v1,0x48(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002af2f0: move t2,s6 */ set(10,cpu(22));
/* 002af2f4: sw v0,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002af2f8: move t3,s7 */ set(11,cpu(23));
/* 002af2fc: lw v0,0x4c(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x0000004c)));
/* 002af300: addiu a0,s0,0x10 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000010)));
/* 002af304: sw v1,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 002af308: lw v1,0x50(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002af30c: sw v0,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
/* 002af310: sw v1,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(3));
/* 002af314: lw v0,0x54(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000054)));
/* 002af318: lw v1,0x58(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002af31c: sw s8,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(30));
/* 002af320: sw v0,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(2));
/* 002af324: jal 0x002af0f8 */ set(31,UINT64_C(0x002af32c));/* delay 002af328 */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(3));body_002af0f8();
/* 002af32c: lw a0,0x40(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002af330: move a1,s0 */ set(5,cpu(16));
/* 002af334: ld s1,0x68(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002af338: ld s0,0x60(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002af33c: ld s2,0x70(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002af340: ld s3,0x78(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002af344: ld s4,0x80(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002af348: ld s5,0x88(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002af34c: ld s6,0x90(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002af350: ld s7,0x98(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002af354: ld s8,0xa0(sp) */ restore(30,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002af358: ld ra,0xa8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002af35c: j 0x002acbb8 */ /* delay 002af360 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000b0)));checkReturn(cpu(31),incoming);nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acbb8),UINT32_C(0x002af35c));return;
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
/* 002b9d10: jal 0x002acbb8 */ set(31,UINT64_C(0x002b9d18));/* delay 002b9d14 */ set(5,cpu(16));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002acbb8),UINT32_C(0x002b9d10));
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
/* 002b9d4c: jal 0x002ad130 */ set(31,UINT64_C(0x002b9d54));/* delay 002b9d50 */ set(16,cpu(4));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002ad130),UINT32_C(0x002b9d4c));
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
static void body_002c0ba8(void){
uint64_t incoming=cpu(31);
/* 002c0ba8: move t1,a0 */ set(9,cpu(4));
/* 002c0bac: bnel t1,zero,0x002c0bc0 */ {int taken=(cpu(9)!=cpu(0));if(taken){/* delay 002c0bb0 */ lw(7,ea(9,(int32_t)UINT32_C(0x00000000)));goto L_002c0bc0;}}
/* 002c0bb4: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002c0bb8: addiu t1,v0,-0x6428 */ set(9,sx((uint32_t)cpu(2)+UINT32_C(0xffff9bd8)));
/* 002c0bbc: lw a3,0x0(t1) */ lw(7,ea(9,(int32_t)UINT32_C(0x00000000)));
L_002c0bc0:;
/* 002c0bc0: lw t0,0x4(t1) */ lw(8,ea(9,(int32_t)UINT32_C(0x00000004)));
/* 002c0bc4: lw a2,0x8(t1) */ lw(6,ea(9,(int32_t)UINT32_C(0x00000008)));
/* 002c0bc8: srl a0,a3,0x1e */ set(4,sx((uint32_t)cpu(7)>>30));
/* 002c0bcc: lw v1,0xc(t1) */ lw(3,ea(9,(int32_t)UINT32_C(0x0000000c)));
/* 002c0bd0: sll v0,t0,0x2 */ set(2,sx((uint32_t)cpu(8)<<2));
/* 002c0bd4: srl a1,a2,0x1f */ set(5,sx((uint32_t)cpu(6)>>31));
/* 002c0bd8: or v0,v0,a0 */ set(2,cpu(2)|cpu(4));
/* 002c0bdc: sll v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)<<1));
/* 002c0be0: sw a2,0xc(t1) */ sw(ea(9,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(6));
/* 002c0be4: or v1,v1,a1 */ set(3,cpu(3)|cpu(5));
/* 002c0be8: sw a3,0x4(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(7));
/* 002c0bec: xor v0,v0,v1 */ set(2,cpu(2)^cpu(3));
/* 002c0bf0: sw t0,0x8(t1) */ sw(ea(9,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
/* 002c0bf4: jr ra */ {uint64_t target=cpu(31);/* delay 002c0bf8 */ sw(ea(9,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_002d1590(void){
uint64_t incoming=cpu(31);
/* 002d1590: move t3,a0 */ set(11,cpu(4));
/* 002d1594: lw a3,0x0(t3) */ lw(7,ea(11,(int32_t)UINT32_C(0x00000000)));
/* 002d1598: sltiu v1,a3,0x2 */ set(3,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d159c: bne v1,zero,0x002d17e4 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d15a0 */ set(2,cpu(11));if(taken){goto L_002d17e4;}}
/* 002d15a4: lw a0,0x0(a1) */ lw(4,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d15a8: sltiu v1,a0,0x2 */ set(3,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d15ac: bne v1,zero,0x002d17e4 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d15b0 */ set(2,cpu(5));if(taken){goto L_002d17e4;}}
/* 002d15b4: xori v0,a3,0x4 */ set(2,cpu(7)^UINT32_C(0x00000004));
/* 002d15b8: bne v0,zero,0x002d15e8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d15bc */ set(3,cpu(4)^UINT32_C(0x00000004));if(taken){goto L_002d15e8;}}
/* 002d15c0: xori v0,a0,0x4 */ set(2,cpu(4)^UINT32_C(0x00000004));
/* 002d15c4: bne v0,zero,0x002d1638 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d15c8 */ if(taken){goto L_002d1638;}}
/* 002d15cc: lw v1,0x4(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d15d0: lw v0,0x4(t3) */ lw(2,ea(11,(int32_t)UINT32_C(0x00000004)));
/* 002d15d4: beq v0,v1,0x002d1638 */ {int taken=(cpu(2)==cpu(3));/* delay 002d15d8 */ if(taken){goto L_002d1638;}}
/* 002d15dc: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002d15e0: jr ra */ {uint64_t target=cpu(31);/* delay 002d15e4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb460)));checkReturn(target,incoming);return;}
L_002d15e8:;
/* 002d15e8: beq v1,zero,0x002d17e4 */ {int taken=(cpu(3)==cpu(0));/* delay 002d15ec */ set(2,cpu(5));if(taken){goto L_002d17e4;}}
/* 002d15f0: xori v0,a0,0x2 */ set(2,cpu(4)^UINT32_C(0x00000002));
/* 002d15f4: bne v0,zero,0x002d1640 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d15f8 */ set(3,cpu(7)^UINT32_C(0x00000002));if(taken){goto L_002d1640;}}
/* 002d15fc: xori v0,a3,0x2 */ set(2,cpu(7)^UINT32_C(0x00000002));
/* 002d1600: bne v0,zero,0x002d1638 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d1604 */ if(taken){goto L_002d1638;}}
/* 002d1608: ld a0,0x0(t3) */ restore(4,ea(11,(int32_t)UINT32_C(0x00000000)));
/* 002d160c: move v0,a2 */ set(2,cpu(6));
/* 002d1610: sd a0,0x0(a2) */ save(4,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002d1614: ld v1,0x8(t3) */ restore(3,ea(11,(int32_t)UINT32_C(0x00000008)));
/* 002d1618: sd v1,0x8(a2) */ save(3,ea(6,(int32_t)UINT32_C(0x00000008)));
/* 002d161c: ld a0,0x10(t3) */ restore(4,ea(11,(int32_t)UINT32_C(0x00000010)));
/* 002d1620: sd a0,0x10(a2) */ save(4,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002d1624: lw v1,0x4(t3) */ lw(3,ea(11,(int32_t)UINT32_C(0x00000004)));
/* 002d1628: lw a0,0x4(a1) */ lw(4,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d162c: and v1,v1,a0 */ set(3,cpu(3)&cpu(4));
/* 002d1630: jr ra */ {uint64_t target=cpu(31);/* delay 002d1634 */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
L_002d1638:;
/* 002d1638: jr ra */ {uint64_t target=cpu(31);/* delay 002d163c */ set(2,cpu(11));checkReturn(target,incoming);return;}
L_002d1640:;
/* 002d1640: beq v1,zero,0x002d17e4 */ {int taken=(cpu(3)==cpu(0));/* delay 002d1644 */ set(2,cpu(5));if(taken){goto L_002d17e4;}}
/* 002d1648: lw t0,0x8(t3) */ lw(8,ea(11,(int32_t)UINT32_C(0x00000008)));
/* 002d164c: lw a3,0x8(a1) */ lw(7,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 002d1650: ld t2,0x10(t3) */ restore(10,ea(11,(int32_t)UINT32_C(0x00000010)));
/* 002d1654: subu v0,t0,a3 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(7)));
/* 002d1658: subu a0,zero,v0 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));
/* 002d165c: slti v1,v0,0x0 */ set(3,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 002d1660: movn v0,a0,v1 */ if(cpu(3)!=0){set(2,cpu(4));}
/* 002d1664: slti v0,v0,0x40 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000040));
/* 002d1668: beq v0,zero,0x002d16e0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d166c */ restore(9,ea(5,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002d16e0;}}
/* 002d1670: slt v0,a3,t0 */ set(2,(int64_t)cpu(7)<(int64_t)cpu(8));
/* 002d1674: beq v0,zero,0x002d16ac */ {int taken=(cpu(2)==cpu(0));/* delay 002d1678 */ set(2,(int64_t)cpu(8)<(int64_t)cpu(7));if(taken){goto L_002d16ac;}}
/* 002d167c: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 002d1680: subu a3,t0,a3 */ set(7,sx((uint32_t)cpu(8)-(uint32_t)cpu(7)));
/* 002d1684: nop  */ 
L_002d1688:;
/* 002d1688: dsrl v1,t1,0x1 */ set(3,cpu(9)>>1);
/* 002d168c: and v0,t1,a0 */ set(2,cpu(9)&cpu(4));
/* 002d1690: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002d1694: nop  */ 
/* 002d1698: nop  */ 
/* 002d169c: bne a3,zero,0x002d1688 */ {int taken=(cpu(7)!=cpu(0));/* delay 002d16a0 */ set(9,cpu(2)|cpu(3));if(taken){goto L_002d1688;}}
/* 002d16a4: move a3,t0 */ set(7,cpu(8));
/* 002d16a8: slt v0,t0,a3 */ set(2,(int64_t)cpu(8)<(int64_t)cpu(7));
L_002d16ac:;
/* 002d16ac: beql v0,zero,0x002d1700 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d16b0 */ lw(4,ea(11,(int32_t)UINT32_C(0x00000004)));goto L_002d1700;}}
/* 002d16b4: li t4,0x1 */ set(12,sx(UINT32_C(0x00000001)));
L_002d16b8:;
/* 002d16b8: addiu t0,t0,0x1 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000001)));
/* 002d16bc: dsrl v0,t2,0x1 */ set(2,cpu(10)>>1);
/* 002d16c0: and v1,t2,t4 */ set(3,cpu(10)&cpu(12));
/* 002d16c4: slt a0,t0,a3 */ set(4,(int64_t)cpu(8)<(int64_t)cpu(7));
/* 002d16c8: nop  */ 
/* 002d16cc: bne a0,zero,0x002d16b8 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d16d0 */ set(10,cpu(3)|cpu(2));if(taken){goto L_002d16b8;}}
/* 002d16d4: b 0x002d1700 */ /* delay 002d16d8 */ lw(4,ea(11,(int32_t)UINT32_C(0x00000004)));goto L_002d1700;
L_002d16e0:;
/* 002d16e0: slt v0,a3,t0 */ set(2,(int64_t)cpu(7)<(int64_t)cpu(8));
/* 002d16e4: beql v0,zero,0x002d16f8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d16e8 */ set(8,cpu(7));goto L_002d16f8;}}
/* 002d16ec: b 0x002d16fc */ /* delay 002d16f0 */ set(9,cpu(0));goto L_002d16fc;
L_002d16f8:;
/* 002d16f8: move t2,zero */ set(10,cpu(0));
L_002d16fc:;
/* 002d16fc: lw a0,0x4(t3) */ lw(4,ea(11,(int32_t)UINT32_C(0x00000004)));
L_002d1700:;
/* 002d1700: lw v0,0x4(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d1704: beq a0,v0,0x002d1798 */ {int taken=(cpu(4)==cpu(2));/* delay 002d1708 */ set(2,cpu(10)-cpu(9));if(taken){goto L_002d1798;}}
/* 002d170c: dsubu v1,t1,t2 */ set(3,cpu(9)-cpu(10));
/* 002d1710: movz v1,v0,a0 */ if(cpu(4)==0){set(3,cpu(2));}
/* 002d1714: bltzl v1,0x002d1730 */ {int taken=((int64_t)cpu(3)<0);if(taken){/* delay 002d1718 */ set(3,cpu(0)-cpu(3));goto L_002d1730;}}
/* 002d171c: sw t0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
/* 002d1720: sd v1,0x10(a2) */ save(3,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002d1724: b 0x002d1740 */ /* delay 002d1728 */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));goto L_002d1740;
L_002d1730:;
/* 002d1730: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d1734: sw v0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002d1738: sw t0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
/* 002d173c: sd v1,0x10(a2) */ save(3,ea(6,(int32_t)UINT32_C(0x00000010)));
L_002d1740:;
/* 002d1740: ld a3,0x10(a2) */ restore(7,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002d1744: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d1748: dsll v0,v0,0x5 */ set(2,cpu(2)<<5);
/* 002d174c: dsrl v0,v0,0x4 */ set(2,cpu(2)>>4);
/* 002d1750: daddiu v1,a3,-0x1 */ set(3,cpu(7)+UINT64_C(0xffffffffffffffff));
/* 002d1754: sltu v0,v0,v1 */ set(2,cpu(2)<cpu(3));
/* 002d1758: bne v0,zero,0x002d17ac */ {int taken=(cpu(2)!=cpu(0));/* delay 002d175c */ if(taken){goto L_002d17ac;}}
L_002d1760:;
/* 002d1760: dsll a1,a3,0x1 */ set(5,cpu(7)<<1);
/* 002d1764: lw v0,0x8(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000008)));
/* 002d1768: daddiu v1,a1,-0x1 */ set(3,cpu(5)+UINT64_C(0xffffffffffffffff));
/* 002d176c: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 002d1770: dsll a0,a0,0x5 */ set(4,cpu(4)<<5);
/* 002d1774: dsrl a0,a0,0x4 */ set(4,cpu(4)>>4);
/* 002d1778: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 002d177c: sltu a0,a0,v1 */ set(4,cpu(4)<cpu(3));
/* 002d1780: sw v0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 002d1784: move a3,a1 */ set(7,cpu(5));
/* 002d1788: beq a0,zero,0x002d1760 */ {int taken=(cpu(4)==cpu(0));/* delay 002d178c */ save(5,ea(6,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002d1760;}}
/* 002d1790: b 0x002d17ac */ /* delay 002d1794 */ goto L_002d17ac;
L_002d1798:;
/* 002d1798: daddu v0,t2,t1 */ set(2,cpu(10)+cpu(9));
/* 002d179c: sw a0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002d17a0: sw t0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(8));
/* 002d17a4: move a3,v0 */ set(7,cpu(2));
/* 002d17a8: sd v0,0x10(a2) */ save(2,ea(6,(int32_t)UINT32_C(0x00000010)));
L_002d17ac:;
/* 002d17ac: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d17b0: dsrl v0,v0,0x3 */ set(2,cpu(2)>>3);
/* 002d17b4: li v1,0x3 */ set(3,sx(UINT32_C(0x00000003)));
/* 002d17b8: sltu v0,v0,a3 */ set(2,cpu(2)<cpu(7));
/* 002d17bc: beq v0,zero,0x002d17e0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d17c0 */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_002d17e0;}}
/* 002d17c4: lw v0,0x8(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000008)));
/* 002d17c8: dsrl a0,a3,0x1 */ set(4,cpu(7)>>1);
/* 002d17cc: andi v1,a3,0x1 */ set(3,cpu(7)&UINT32_C(0x00000001));
/* 002d17d0: or v1,v1,a0 */ set(3,cpu(3)|cpu(4));
/* 002d17d4: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002d17d8: sd v1,0x10(a2) */ save(3,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002d17dc: sw v0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
L_002d17e0:;
/* 002d17e0: move v0,a2 */ set(2,cpu(6));
L_002d17e4:;
/* 002d17e4: jr ra */ {uint64_t target=cpu(31);/* delay 002d17e8 */ checkReturn(target,incoming);return;}
}
static void body_002d17f0(void){
uint64_t incoming=cpu(31);
/* 002d17f0: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
/* 002d17f4: sd a0,0x60(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d17f8: addiu a0,sp,0x60 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 002d17fc: sd a1,0x68(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002d1800: sd s0,0x70(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d1804: sd ra,0x78(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d1808: jal 0x002d3578 */ set(31,UINT64_C(0x002d1810));/* delay 002d180c */ set(5,cpu(29));body_002d3578();
/* 002d1810: addiu s0,sp,0x20 */ set(16,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d1814: addiu a0,sp,0x68 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000068)));
/* 002d1818: jal 0x002d3578 */ set(31,UINT64_C(0x002d1820));/* delay 002d181c */ set(5,cpu(16));body_002d3578();
/* 002d1820: move a1,s0 */ set(5,cpu(16));
/* 002d1824: move a0,sp */ set(4,cpu(29));
/* 002d1828: jal 0x002d1590 */ set(31,UINT64_C(0x002d1830));/* delay 002d182c */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));body_002d1590();
/* 002d1830: jal 0x002d34a0 */ set(31,UINT64_C(0x002d1838));/* delay 002d1834 */ set(4,cpu(2));body_002d34a0();
/* 002d1838: ld s0,0x70(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d183c: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d1840: jr ra */ {uint64_t target=cpu(31);/* delay 002d1844 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));checkReturn(target,incoming);return;}
}
static void body_002d1848(void){
uint64_t incoming=cpu(31);
/* 002d1848: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
/* 002d184c: sd a0,0x60(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d1850: addiu a0,sp,0x60 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 002d1854: sd a1,0x68(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002d1858: sd s0,0x70(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d185c: sd ra,0x78(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d1860: jal 0x002d3578 */ set(31,UINT64_C(0x002d1868));/* delay 002d1864 */ set(5,cpu(29));body_002d3578();
/* 002d1868: addiu s0,sp,0x20 */ set(16,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d186c: addiu a0,sp,0x68 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000068)));
/* 002d1870: jal 0x002d3578 */ set(31,UINT64_C(0x002d1878));/* delay 002d1874 */ set(5,cpu(16));body_002d3578();
/* 002d1878: move a1,s0 */ set(5,cpu(16));
/* 002d187c: lw v0,0x24(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000024)));
/* 002d1880: move a0,sp */ set(4,cpu(29));
/* 002d1884: addiu a2,sp,0x40 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
/* 002d1888: xori v0,v0,0x1 */ set(2,cpu(2)^UINT32_C(0x00000001));
/* 002d188c: jal 0x002d1590 */ set(31,UINT64_C(0x002d1894));/* delay 002d1890 */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(2));body_002d1590();
/* 002d1894: jal 0x002d34a0 */ set(31,UINT64_C(0x002d189c));/* delay 002d1898 */ set(4,cpu(2));body_002d34a0();
/* 002d189c: ld s0,0x70(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002d18a0: ld ra,0x78(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002d18a4: jr ra */ {uint64_t target=cpu(31);/* delay 002d18a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));checkReturn(target,incoming);return;}
}
static void body_002d1b38(void){
uint64_t incoming=cpu(31);
/* 002d1b38: addiu sp,sp,-0x60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffa0)));
/* 002d1b3c: sd a0,0x40(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d1b40: addiu a0,sp,0x40 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));
/* 002d1b44: sd a1,0x48(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d1b48: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d1b4c: sd ra,0x58(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002d1b50: jal 0x002d3578 */ set(31,UINT64_C(0x002d1b58));/* delay 002d1b54 */ set(5,cpu(29));body_002d3578();
/* 002d1b58: addiu s0,sp,0x20 */ set(16,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d1b5c: addiu a0,sp,0x48 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000048)));
/* 002d1b60: jal 0x002d3578 */ set(31,UINT64_C(0x002d1b68));/* delay 002d1b64 */ set(5,cpu(16));body_002d3578();
/* 002d1b68: move a1,s0 */ set(5,cpu(16));
/* 002d1b6c: jal 0x002d3638 */ set(31,UINT64_C(0x002d1b74));/* delay 002d1b70 */ set(4,cpu(29));body_002d3638();
/* 002d1b74: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d1b78: ld ra,0x58(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002d1b7c: jr ra */ {uint64_t target=cpu(31);/* delay 002d1b80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));checkReturn(target,incoming);return;}
}
static void body_002d1b88(void){
uint64_t incoming=cpu(31);
/* 002d1b88: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002d1b8c: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002d1b90: srl v1,a0,0x1f */ set(3,sx((uint32_t)cpu(4)>>31));
/* 002d1b94: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d1b98: sw v0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002d1b9c: bne a0,zero,0x002d1bb0 */ {int taken=(cpu(4)!=cpu(0));/* delay 002d1ba0 */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));if(taken){goto L_002d1bb0;}}
/* 002d1ba4: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002d1ba8: b 0x002d1c2c */ /* delay 002d1bac */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_002d1c2c;
L_002d1bb0:;
/* 002d1bb0: li v0,0x3c */ set(2,sx(UINT32_C(0x0000003c)));
/* 002d1bb4: beq v1,zero,0x002d1be0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d1bb8 */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002d1be0;}}
/* 002d1bbc: lui v1,0x8000 */ set(3,sx(UINT32_C(0x80000000)));
/* 002d1bc0: ori v0,zero,0xc1e0 */ set(2,cpu(0)|UINT32_C(0x0000c1e0));
/* 002d1bc4: dsll32 v0,v0,0x10 */ set(2,cpu(2)<<48);
/* 002d1bc8: beq a0,v1,0x002d1c38 */ {int taken=(cpu(4)==cpu(3));/* delay 002d1bcc */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_002d1c38;}}
/* 002d1bd0: subu v0,zero,a0 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
/* 002d1bd4: b 0x002d1be4 */ /* delay 002d1bd8 */ save(2,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_002d1be4;
L_002d1be0:;
/* 002d1be0: sd a0,0x10(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000010)));
L_002d1be4:;
/* 002d1be4: ld a0,0x10(sp) */ restore(4,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d1be8: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d1bec: dsrl v0,v0,0x4 */ set(2,cpu(2)>>4);
/* 002d1bf0: sltu v0,v0,a0 */ set(2,cpu(2)<cpu(4));
/* 002d1bf4: bne v0,zero,0x002d1c2c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d1bf8 */ lw(5,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002d1c2c;}}
/* 002d1bfc: li a2,-0x1 */ set(6,sx(UINT32_C(0xffffffff)));
/* 002d1c00: dsrl a2,a2,0x4 */ set(6,cpu(6)>>4);
/* 002d1c04: nop  */ 
L_002d1c08:;
/* 002d1c08: dsll v1,a0,0x1 */ set(3,cpu(4)<<1);
/* 002d1c0c: addiu a1,a1,-0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));
/* 002d1c10: sltu v0,a2,v1 */ set(2,cpu(6)<cpu(3));
/* 002d1c14: nop  */ 
/* 002d1c18: nop  */ 
/* 002d1c1c: beq v0,zero,0x002d1c08 */ {int taken=(cpu(2)==cpu(0));/* delay 002d1c20 */ set(4,cpu(3));if(taken){goto L_002d1c08;}}
/* 002d1c24: sw a1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 002d1c28: sd v1,0x10(sp) */ save(3,ea(29,(int32_t)UINT32_C(0x00000010)));
L_002d1c2c:;
/* 002d1c2c: jal 0x002d34a0 */ set(31,UINT64_C(0x002d1c34));/* delay 002d1c30 */ set(4,cpu(29));body_002d34a0();
/* 002d1c34: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
L_002d1c38:;
/* 002d1c38: jr ra */ {uint64_t target=cpu(31);/* delay 002d1c3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002d1c40(void){
uint64_t incoming=cpu(31);
/* 002d1c40: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002d1c44: sd a0,0x20(sp) */ save(4,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002d1c48: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));
/* 002d1c4c: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002d1c50: jal 0x002d3578 */ set(31,UINT64_C(0x002d1c58));/* delay 002d1c54 */ set(5,cpu(29));body_002d3578();
/* 002d1c58: move v0,zero */ set(2,cpu(0));
/* 002d1c5c: lw a0,0x0(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d1c60: xori v1,a0,0x2 */ set(3,cpu(4)^UINT32_C(0x00000002));
/* 002d1c64: beq v1,zero,0x002d1cd0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d1c68 */ set(5,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_002d1cd0;}}
/* 002d1c6c: bne a1,zero,0x002d1cd4 */ {int taken=(cpu(5)!=cpu(0));/* delay 002d1c70 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_002d1cd4;}}
/* 002d1c74: xori v0,a0,0x4 */ set(2,cpu(4)^UINT32_C(0x00000004));
/* 002d1c78: beq v0,zero,0x002d1c9c */ {int taken=(cpu(2)==cpu(0));/* delay 002d1c7c */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_002d1c9c;}}
/* 002d1c80: lw a1,0x8(sp) */ lw(5,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d1c84: move v0,zero */ set(2,cpu(0));
/* 002d1c88: bltz a1,0x002d1cd4 */ {int taken=((int64_t)cpu(5)<0);/* delay 002d1c8c */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000001f));if(taken){goto L_002d1cd4;}}
/* 002d1c90: bne v1,zero,0x002d1cb0 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d1c94 */ set(3,sx(UINT32_C(0x0000003c)));if(taken){goto L_002d1cb0;}}
/* 002d1c98: lw v1,0x4(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000004)));
L_002d1c9c:;
/* 002d1c9c: lui v0,0x7fff */ set(2,sx(UINT32_C(0x7fff0000)));
/* 002d1ca0: lui a0,0x8000 */ set(4,sx(UINT32_C(0x80000000)));
/* 002d1ca4: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d1ca8: b 0x002d1cd0 */ /* delay 002d1cac */ if(cpu(3)!=0){set(2,cpu(4));}goto L_002d1cd0;
L_002d1cb0:;
/* 002d1cb0: ld v0,0x10(sp) */ restore(2,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d1cb4: subu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(5)));
/* 002d1cb8: lw a0,0x4(sp) */ lw(4,ea(29,(int32_t)UINT32_C(0x00000004)));
/* 002d1cbc: dsrlv v0,v0,v1 */ set(2,cpu(2)>>((unsigned)cpu(3)&63u));
/* 002d1cc0: dsll32 v0,v0,0x0 */ set(2,cpu(2)<<32);
/* 002d1cc4: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002d1cc8: subu v1,zero,v0 */ set(3,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));
/* 002d1ccc: movn v0,v1,a0 */ if(cpu(4)!=0){set(2,cpu(3));}
L_002d1cd0:;
/* 002d1cd0: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
L_002d1cd4:;
/* 002d1cd4: jr ra */ {uint64_t target=cpu(31);/* delay 002d1cd8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002d34a0(void){
uint64_t incoming=cpu(31);
/* 002d34a0: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d34a4: move a3,zero */ set(7,cpu(0));
/* 002d34a8: ld a1,0x10(a0) */ restore(5,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002d34ac: sltiu v0,v1,0x2 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d34b0: beq v0,zero,0x002d34d0 */ {int taken=(cpu(2)==cpu(0));/* delay 002d34b4 */ lw(8,ea(4,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_002d34d0;}}
/* 002d34b8: ori v0,zero,0x8000 */ set(2,cpu(0)|UINT32_C(0x00008000));
/* 002d34bc: dsll32 v0,v0,0x4 */ set(2,cpu(2)<<36);
/* 002d34c0: li a3,0x7ff */ set(7,sx(UINT32_C(0x000007ff)));
/* 002d34c4: b 0x002d351c */ /* delay 002d34c8 */ set(5,cpu(5)|cpu(2));goto L_002d351c;
L_002d34d0:;
/* 002d34d0: xori v0,v1,0x4 */ set(2,cpu(3)^UINT32_C(0x00000004));
/* 002d34d4: beql v0,zero,0x002d3510 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d34d8 */ set(7,sx(UINT32_C(0x000007ff)));goto L_002d3510;}}
/* 002d34dc: xori v0,v1,0x2 */ set(2,cpu(3)^UINT32_C(0x00000002));
/* 002d34e0: beql v0,zero,0x002d351c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d34e4 */ set(5,cpu(0));goto L_002d351c;}}
/* 002d34e8: beq a1,zero,0x002d351c */ {int taken=(cpu(5)==cpu(0));/* delay 002d34ec */ if(taken){goto L_002d351c;}}
/* 002d34f0: lw a0,0x8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002d34f4: slti v0,a0,-0x3fe */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0xfffffc02));
/* 002d34f8: bnel v0,zero,0x002d351c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d34fc */ set(5,cpu(0));goto L_002d351c;}}
/* 002d3500: slti v0,a0,0x400 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000400));
/* 002d3504: bnel v0,zero,0x002d3518 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d3508 */ set(7,sx((uint32_t)cpu(4)+UINT32_C(0x000003ff)));goto L_002d3518;}}
/* 002d350c: li a3,0x7ff */ set(7,sx(UINT32_C(0x000007ff)));
L_002d3510:;
/* 002d3510: b 0x002d351c */ /* delay 002d3514 */ set(5,cpu(0));goto L_002d351c;
L_002d3518:;
/* 002d3518: dsrl a1,a1,0x8 */ set(5,cpu(5)>>8);
L_002d351c:;
/* 002d351c: ori v1,zero,0xfff0 */ set(3,cpu(0)|UINT32_C(0x0000fff0));
/* 002d3520: dsll32 v1,v1,0x10 */ set(3,cpu(3)<<48);
/* 002d3524: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d3528: dsrl v0,v0,0xc */ set(2,cpu(2)>>12);
/* 002d352c: and v0,a1,v0 */ set(2,cpu(5)&cpu(2));
/* 002d3530: and a2,a2,v1 */ set(6,cpu(6)&cpu(3));
/* 002d3534: or a2,a2,v0 */ set(6,cpu(6)|cpu(2));
/* 002d3538: lui v0,0x800f */ set(2,sx(UINT32_C(0x800f0000)));
/* 002d353c: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d3540: dsll v0,v0,0x10 */ set(2,cpu(2)<<16);
/* 002d3544: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d3548: dsll v0,v0,0x10 */ set(2,cpu(2)<<16);
/* 002d354c: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002d3550: andi v1,a3,0x7ff */ set(3,cpu(7)&UINT32_C(0x000007ff));
/* 002d3554: and a2,a2,v0 */ set(6,cpu(6)&cpu(2));
/* 002d3558: dsll32 v1,v1,0x14 */ set(3,cpu(3)<<52);
/* 002d355c: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 002d3560: dsrl a0,a0,0x1 */ set(4,cpu(4)>>1);
/* 002d3564: or a2,a2,v1 */ set(6,cpu(6)|cpu(3));
/* 002d3568: dsll32 v0,t0,0x1f */ set(2,cpu(8)<<63);
/* 002d356c: and a2,a2,a0 */ set(6,cpu(6)&cpu(4));
/* 002d3570: jr ra */ {uint64_t target=cpu(31);/* delay 002d3574 */ set(2,cpu(6)|cpu(2));checkReturn(target,incoming);return;}
}
static void body_002d3578(void){
uint64_t incoming=cpu(31);
/* 002d3578: ld v0,0x0(a0) */ restore(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d357c: move a2,a1 */ set(6,cpu(5));
/* 002d3580: li a1,-0x1 */ set(5,sx(UINT32_C(0xffffffff)));
/* 002d3584: dsrl a1,a1,0xc */ set(5,cpu(5)>>12);
/* 002d3588: dsrl32 v1,v0,0x14 */ set(3,cpu(2)>>52);
/* 002d358c: dsrl32 a0,v0,0x1f */ set(4,cpu(2)>>63);
/* 002d3590: andi a3,v1,0x7ff */ set(7,cpu(3)&UINT32_C(0x000007ff));
/* 002d3594: and v1,v0,a1 */ set(3,cpu(2)&cpu(5));
/* 002d3598: bne a3,zero,0x002d35b0 */ {int taken=(cpu(7)!=cpu(0));/* delay 002d359c */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));if(taken){goto L_002d35b0;}}
/* 002d35a0: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002d35a4: jr ra */ {uint64_t target=cpu(31);/* delay 002d35a8 */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
L_002d35b0:;
/* 002d35b0: li v0,0x7ff */ set(2,sx(UINT32_C(0x000007ff)));
/* 002d35b4: bnel a3,v0,0x002d3610 */ {int taken=(cpu(7)!=cpu(2));if(taken){/* delay 002d35b8 */ set(3,cpu(3)<<8);goto L_002d3610;}}
/* 002d35bc: li v0,0x3ff */ set(2,sx(UINT32_C(0x000003ff)));
/* 002d35c0: bne v1,zero,0x002d35e0 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d35c4 */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));if(taken){goto L_002d35e0;}}
/* 002d35c8: li v1,0x4 */ set(3,sx(UINT32_C(0x00000004)));
/* 002d35cc: ori v0,zero,0x8000 */ set(2,cpu(0)|UINT32_C(0x00008000));
/* 002d35d0: dsll32 v0,v0,0xd */ set(2,cpu(2)<<45);
/* 002d35d4: sd v0,0x10(a2) */ save(2,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002d35d8: jr ra */ {uint64_t target=cpu(31);/* delay 002d35dc */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
L_002d35e0:;
/* 002d35e0: ori v0,zero,0x8000 */ set(2,cpu(0)|UINT32_C(0x00008000));
/* 002d35e4: dsll32 v0,v0,0x4 */ set(2,cpu(2)<<36);
/* 002d35e8: and v0,v1,v0 */ set(2,cpu(3)&cpu(2));
/* 002d35ec: beq v0,zero,0x002d3600 */ {int taken=(cpu(2)==cpu(0));/* delay 002d35f0 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002d3600;}}
/* 002d35f4: b 0x002d3604 */ /* delay 002d35f8 */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_002d3604;
L_002d3600:;
/* 002d3600: sw zero,0x0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
L_002d3604:;
/* 002d3604: jr ra */ {uint64_t target=cpu(31);/* delay 002d3608 */ save(3,ea(6,(int32_t)UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
L_002d3610:;
/* 002d3610: ori v0,zero,0x8000 */ set(2,cpu(0)|UINT32_C(0x00008000));
/* 002d3614: dsll32 v0,v0,0xd */ set(2,cpu(2)<<45);
/* 002d3618: or v1,v1,v0 */ set(3,cpu(3)|cpu(2));
/* 002d361c: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002d3620: addiu a0,a3,-0x3ff */ set(4,sx((uint32_t)cpu(7)+UINT32_C(0xfffffc01)));
/* 002d3624: sd v1,0x10(a2) */ save(3,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 002d3628: sw a0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 002d362c: jr ra */ {uint64_t target=cpu(31);/* delay 002d3630 */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_002d3638(void){
uint64_t incoming=cpu(31);
/* 002d3638: lw a2,0x0(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 002d363c: sltiu v0,a2,0x2 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d3640: bne v0,zero,0x002d3658 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3644 */ if(taken){goto L_002d3658;}}
/* 002d3648: lw v1,0x0(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d364c: sltiu v0,v1,0x2 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000002));
/* 002d3650: beql v0,zero,0x002d3660 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d3654 */ set(2,cpu(6)^UINT32_C(0x00000004));goto L_002d3660;}}
L_002d3658:;
/* 002d3658: jr ra */ {uint64_t target=cpu(31);/* delay 002d365c */ set(2,sx(UINT32_C(0x00000001)));checkReturn(target,incoming);return;}
L_002d3660:;
/* 002d3660: bne v0,zero,0x002d3680 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3664 */ set(2,cpu(3)^UINT32_C(0x00000004));if(taken){goto L_002d3680;}}
/* 002d3668: bnel v0,zero,0x002d36d4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d366c */ lw(4,ea(4,(int32_t)UINT32_C(0x00000004)));goto L_002d36d4;}}
/* 002d3670: lw v1,0x4(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d3674: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 002d3678: jr ra */ {uint64_t target=cpu(31);/* delay 002d367c */ set(2,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));checkReturn(target,incoming);return;}
L_002d3680:;
/* 002d3680: bnel v0,zero,0x002d36a0 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d3684 */ set(2,cpu(6)^UINT32_C(0x00000002));goto L_002d36a0;}}
/* 002d3688: lw a0,0x4(a1) */ lw(4,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d368c: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002d3690: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d3694: jr ra */ {uint64_t target=cpu(31);/* delay 002d3698 */ if(cpu(4)==0){set(2,cpu(3));}checkReturn(target,incoming);return;}
L_002d36a0:;
/* 002d36a0: bnel v0,zero,0x002d36c8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d36a4 */ set(2,cpu(3)^UINT32_C(0x00000002));goto L_002d36c8;}}
/* 002d36a8: xori v1,v1,0x2 */ set(3,cpu(3)^UINT32_C(0x00000002));
/* 002d36ac: beq v1,zero,0x002d3750 */ {int taken=(cpu(3)==cpu(0));/* delay 002d36b0 */ set(2,cpu(0));if(taken){goto L_002d3750;}}
/* 002d36b4: lw a0,0x4(a1) */ lw(4,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d36b8: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002d36bc: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d36c0: jr ra */ {uint64_t target=cpu(31);/* delay 002d36c4 */ if(cpu(4)!=0){set(2,cpu(3));}checkReturn(target,incoming);return;}
L_002d36c8:;
/* 002d36c8: bnel v0,zero,0x002d36e8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d36cc */ lw(7,ea(4,(int32_t)UINT32_C(0x00000004)));goto L_002d36e8;}}
/* 002d36d0: lw a0,0x4(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000004)));
L_002d36d4:;
/* 002d36d4: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002d36d8: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d36dc: jr ra */ {uint64_t target=cpu(31);/* delay 002d36e0 */ if(cpu(4)==0){set(2,cpu(3));}checkReturn(target,incoming);return;}
L_002d36e8:;
/* 002d36e8: lw v0,0x4(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000004)));
/* 002d36ec: bne a3,v0,0x002d372c */ {int taken=(cpu(7)!=cpu(2));/* delay 002d36f0 */ set(3,sx(UINT32_C(0x00000001)));if(taken){goto L_002d372c;}}
/* 002d36f4: lw a2,0x8(a0) */ lw(6,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002d36f8: lw v1,0x8(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 002d36fc: slt v0,v1,a2 */ set(2,(int64_t)cpu(3)<(int64_t)cpu(6));
/* 002d3700: bnel v0,zero,0x002d372c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d3704 */ set(3,sx(UINT32_C(0x00000001)));goto L_002d372c;}}
/* 002d3708: slt v0,a2,v1 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(3));
/* 002d370c: bne v0,zero,0x002d3744 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d3710 */ set(3,sx(UINT32_C(0xffffffff)));if(taken){goto L_002d3744;}}
/* 002d3714: ld v1,0x10(a0) */ restore(3,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 002d3718: ld a0,0x10(a1) */ restore(4,ea(5,(int32_t)UINT32_C(0x00000010)));
/* 002d371c: sltu v0,a0,v1 */ set(2,cpu(4)<cpu(3));
/* 002d3720: beql v0,zero,0x002d3738 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d3724 */ set(2,cpu(3)<cpu(4));goto L_002d3738;}}
/* 002d3728: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
L_002d372c:;
/* 002d372c: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d3730: jr ra */ {uint64_t target=cpu(31);/* delay 002d3734 */ if(cpu(7)==0){set(2,cpu(3));}checkReturn(target,incoming);return;}
L_002d3738:;
/* 002d3738: beql v0,zero,0x002d3750 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d373c */ set(2,cpu(0));goto L_002d3750;}}
/* 002d3740: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
L_002d3744:;
/* 002d3744: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002d3748: jr ra */ {uint64_t target=cpu(31);/* delay 002d374c */ if(cpu(7)==0){set(2,cpu(3));}checkReturn(target,incoming);return;}
L_002d3750:;
/* 002d3750: jr ra */ {uint64_t target=cpu(31);/* delay 002d3754 */ checkReturn(target,incoming);return;}
}
static void body_002d5690(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 002d5690: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d5694: addiu sp,sp,-0xc0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff40)));
/* 002d5698: lw t5,-0x41d8(v0) */ lw(13,ea(2,(int32_t)UINT32_C(0xffffbe28)));
/* 002d569c: li v0,0x208 */ set(2,sx(UINT32_C(0x00000208)));
/* 002d56a0: lui v1,0x7fff */ set(3,sx(UINT32_C(0x7fff0000)));
/* 002d56a4: move t4,a0 */ set(12,cpu(4));
/* 002d56a8: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002d56ac: sd a2,0x90(sp) */ save(6,ea(29,(int32_t)UINT32_C(0x00000090)));
/* 002d56b0: move a0,sp */ set(4,cpu(29));
/* 002d56b4: addiu a2,sp,0x90 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000090)));
/* 002d56b8: sd ra,0x60(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d56bc: sw v1,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 002d56c0: sw v1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002d56c4: sd a3,0x98(sp) */ save(7,ea(29,(int32_t)UINT32_C(0x00000098)));
/* 002d56c8: sd t0,0xa0(sp) */ save(8,ea(29,(int32_t)UINT32_C(0x000000a0)));
/* 002d56cc: sd t1,0xa8(sp) */ save(9,ea(29,(int32_t)UINT32_C(0x000000a8)));
/* 002d56d0: sd t2,0xb0(sp) */ save(10,ea(29,(int32_t)UINT32_C(0x000000b0)));
/* 002d56d4: sd t3,0xb8(sp) */ save(11,ea(29,(int32_t)UINT32_C(0x000000b8)));
/* 002d56d8: swc1 f12,0x70(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000070)),f[12]);
/* 002d56dc: swc1 f13,0x74(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000074)),f[13]);
/* 002d56e0: swc1 f14,0x78(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000078)),f[14]);
/* 002d56e4: swc1 f15,0x7c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000007c)),f[15]);
/* 002d56e8: swc1 f16,0x80(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000080)),f[16]);
/* 002d56ec: swc1 f17,0x84(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000084)),f[17]);
/* 002d56f0: swc1 f18,0x88(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000088)),f[18]);
/* 002d56f4: swc1 f19,0x8c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000008c)),f[19]);
/* 002d56f8: sh v0,0xc(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 002d56fc: sw t4,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(12));
/* 002d5700: sw t5,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(13));
/* 002d5704: jal 0x002d6600 */ set(31,UINT64_C(0x002d570c));/* delay 002d5708 */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(12));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002d6600),UINT32_C(0x002d5704));
/* 002d570c: lw v1,0x0(sp) */ lw(3,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d5710: ld ra,0x60(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d5714: sb zero,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 002d5718: jr ra */ {uint64_t target=cpu(31);/* delay 002d571c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x000000c0)));checkReturn(target,incoming);return;}
}
static void body_002d6548(void){
uint64_t incoming=cpu(31);
/* 002d6548: addiu sp,sp,-0x480 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffb80)));
/* 002d654c: li t2,0x400 */ set(10,sx(UINT32_C(0x00000400)));
/* 002d6550: sd s0,0x460(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000460)));
/* 002d6554: move s0,a0 */ set(16,cpu(4));
/* 002d6558: sd s1,0x468(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000468)));
/* 002d655c: addiu t3,sp,0x60 */ set(11,sx((uint32_t)cpu(29)+UINT32_C(0x00000060)));
/* 002d6560: sd ra,0x470(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000470)));
/* 002d6564: move a0,sp */ set(4,cpu(29));
/* 002d6568: sw t3,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(11));
/* 002d656c: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002d6570: lhu t1,0xe(s0) */ set(9,half(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 002d6574: lw t0,0x54(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000054)));
/* 002d6578: andi v0,v0,0xfffd */ set(2,cpu(2)&UINT32_C(0x0000fffd));
/* 002d657c: lw v1,0x1c(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x0000001c)));
/* 002d6580: lw a3,0x24(s0) */ lw(7,ea(16,(int32_t)UINT32_C(0x00000024)));
/* 002d6584: sw t0,0x54(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(8));
/* 002d6588: sh v0,0xc(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 002d658c: sh t1,0xe(sp) */ sh(ea(29,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(9));
/* 002d6590: sw v1,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(3));
/* 002d6594: sw a3,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(7));
/* 002d6598: sw t2,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(10));
/* 002d659c: sw t3,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(11));
/* 002d65a0: sw t2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(10));
/* 002d65a4: jal 0x002d6600 */ set(31,UINT64_C(0x002d65ac));/* delay 002d65a8 */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002d6600),UINT32_C(0x002d65a4));
/* 002d65ac: move s1,v0 */ set(17,cpu(2));
/* 002d65b0: bltz s1,0x002d65c8 */ {int taken=((int64_t)cpu(17)<0);/* delay 002d65b4 */ set(4,cpu(29));if(taken){goto L_002d65c8;}}
/* 002d65b8: jal 0x002d95e0 */ set(31,UINT64_C(0x002d65c0));/* delay 002d65bc */ body_002d95e0();
/* 002d65c0: li v1,-0x1 */ set(3,sx(UINT32_C(0xffffffff)));
/* 002d65c4: movn s1,v1,v0 */ if(cpu(2)!=0){set(17,cpu(3));}
L_002d65c8:;
/* 002d65c8: lhu v0,0xc(sp) */ set(2,half(ea(29,(int32_t)UINT32_C(0x0000000c))));
/* 002d65cc: andi v0,v0,0x40 */ set(2,cpu(2)&UINT32_C(0x00000040));
/* 002d65d0: beq v0,zero,0x002d65e8 */ {int taken=(cpu(2)==cpu(0));/* delay 002d65d4 */ set(2,cpu(17));if(taken){goto L_002d65e8;}}
/* 002d65d8: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002d65dc: ori v0,v0,0x40 */ set(2,cpu(2)|UINT32_C(0x00000040));
/* 002d65e0: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 002d65e4: move v0,s1 */ set(2,cpu(17));
L_002d65e8:;
/* 002d65e8: ld s0,0x460(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000460)));
/* 002d65ec: ld s1,0x468(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000468)));
/* 002d65f0: ld ra,0x470(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000470)));
/* 002d65f4: jr ra */ {uint64_t target=cpu(31);/* delay 002d65f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000480)));checkReturn(target,incoming);return;}
}
static void body_002d7ea8(void){
uint64_t incoming=cpu(31);
/* 002d7ea8: sb a2,0x0(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(6));
/* 002d7eac: addiu a2,a0,0x1 */ set(6,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002d7eb0: bgez a1,0x002d7ec8 */ {int taken=((int64_t)cpu(5)>=0);/* delay 002d7eb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffec0)));if(taken){goto L_002d7ec8;}}
/* 002d7eb8: li v0,0x2d */ set(2,sx(UINT32_C(0x0000002d)));
/* 002d7ebc: b 0x002d7ecc */ /* delay 002d7ec0 */ set(5,sx((uint32_t)cpu(0)-(uint32_t)cpu(5)));goto L_002d7ecc;
L_002d7ec8:;
/* 002d7ec8: li v0,0x2b */ set(2,sx(UINT32_C(0x0000002b)));
L_002d7ecc:;
/* 002d7ecc: sb v0,0x0(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d7ed0: addiu a2,a0,0x2 */ set(6,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));
/* 002d7ed4: addiu a3,sp,0x134 */ set(7,sx((uint32_t)cpu(29)+UINT32_C(0x00000134)));
/* 002d7ed8: slti v0,a1,0xa */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 002d7edc: bne v0,zero,0x002d7f60 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d7ee0 */ set(9,cpu(7));if(taken){goto L_002d7f60;}}
/* 002d7ee4: li t0,0xa */ set(8,sx(UINT32_C(0x0000000a)));
/* 002d7ee8: div a1,t0 */ nativeDivide((uint32_t)cpu(5),(uint32_t)cpu(8),1,0);
/* 002d7eec: nop  */ 
L_002d7ef0:;
/* 002d7ef0: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002d7ef4: beql t0,zero,0x002d7efc */ {int taken=(cpu(8)==cpu(0));if(taken){/* delay 002d7ef8 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x002d7ef8));goto L_002d7efc;}}
L_002d7efc:;
/* 002d7efc: mflo v1 */ set(3,nocturneEffectHostLo());
/* 002d7f00: mfhi v0 */ set(2,nocturneEffectHostHi());
/* 002d7f04: move a1,v1 */ set(5,cpu(3));
/* 002d7f08: addiu v0,v0,0x30 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000030)));
/* 002d7f0c: slti v1,a1,0xa */ set(3,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 002d7f10: sb v0,0x0(a3) */ sb(ea(7,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d7f14: beql v1,zero,0x002d7ef0 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002d7f18 */ nativeDivide((uint32_t)cpu(5),(uint32_t)cpu(8),1,0);goto L_002d7ef0;}}
/* 002d7f1c: addiu a3,a3,-0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 002d7f20: addiu v0,a1,0x30 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000030)));
/* 002d7f24: sltu v1,a3,t1 */ set(3,cpu(7)<cpu(9));
/* 002d7f28: beq v1,zero,0x002d7f78 */ {int taken=(cpu(3)==cpu(0));/* delay 002d7f2c */ sb(ea(7,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));if(taken){goto L_002d7f78;}}
/* 002d7f30: move a1,t1 */ set(5,cpu(9));
/* 002d7f34: nop  */ 
L_002d7f38:;
/* 002d7f38: lbu v0,0x0(a3) */ set(2,byte(ea(7,(int32_t)UINT32_C(0x00000000))));
/* 002d7f3c: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 002d7f40: sltu v1,a3,a1 */ set(3,cpu(7)<cpu(5));
/* 002d7f44: sb v0,0x0(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d7f48: nop  */ 
/* 002d7f4c: bne v1,zero,0x002d7f38 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d7f50 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));if(taken){goto L_002d7f38;}}
/* 002d7f54: b 0x002d7f7c */ /* delay 002d7f58 */ set(2,sx((uint32_t)cpu(6)-(uint32_t)cpu(4)));goto L_002d7f7c;
L_002d7f60:;
/* 002d7f60: li v0,0x30 */ set(2,sx(UINT32_C(0x00000030)));
/* 002d7f64: addiu v1,a1,0x30 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000030)));
/* 002d7f68: sb v0,0x0(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d7f6c: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 002d7f70: sb v1,0x0(a2) */ sb(ea(6,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
/* 002d7f74: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
L_002d7f78:;
/* 002d7f78: subu v0,a2,a0 */ set(2,sx((uint32_t)cpu(6)-(uint32_t)cpu(4)));
L_002d7f7c:;
/* 002d7f7c: jr ra */ {uint64_t target=cpu(31);/* delay 002d7f80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000140)));checkReturn(target,incoming);return;}
}
static void body_002d8038(void){
uint64_t incoming=cpu(31);
/* 002d8038: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002d803c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d8040: move s0,a0 */ set(16,cpu(4));
/* 002d8044: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d8048: lw v1,0x54(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000054)));
/* 002d804c: bnel v1,zero,0x002d8068 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d8050 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000038)));goto L_002d8068;}}
/* 002d8054: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d8058: lw v1,-0x41d8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0xffffbe28)));
/* 002d805c: sw v1,0x54(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(3));
/* 002d8060: lw v0,0x38(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000038)));
/* 002d8064: nop  */ 
L_002d8068:;
/* 002d8068: bnel v0,zero,0x002d807c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d806c */ set(4,half(ea(16,(int32_t)UINT32_C(0x0000000c))));goto L_002d807c;}}
/* 002d8070: jal 0x002d9908 */ set(31,UINT64_C(0x002d8078));/* delay 002d8074 */ set(4,cpu(3));body_002d9908();
/* 002d8078: lhu a0,0xc(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
L_002d807c:;
/* 002d807c: andi v0,a0,0x8 */ set(2,cpu(4)&UINT32_C(0x00000008));
/* 002d8080: bnel v0,zero,0x002d80e8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d8084 */ lw(5,ea(16,(int32_t)UINT32_C(0x00000010)));goto L_002d80e8;}}
/* 002d8088: andi v1,a0,0x10 */ set(3,cpu(4)&UINT32_C(0x00000010));
/* 002d808c: beq v1,zero,0x002d8134 */ {int taken=(cpu(3)==cpu(0));/* delay 002d8090 */ set(2,sx(UINT32_C(0xffffffff)));if(taken){goto L_002d8134;}}
/* 002d8094: andi v0,a0,0x4 */ set(2,cpu(4)&UINT32_C(0x00000004));
/* 002d8098: beql v0,zero,0x002d80e0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d809c */ lw(5,ea(16,(int32_t)UINT32_C(0x00000010)));goto L_002d80e0;}}
/* 002d80a0: lw a1,0x30(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000030)));
/* 002d80a4: beq a1,zero,0x002d80c4 */ {int taken=(cpu(5)==cpu(0));/* delay 002d80a8 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000040)));if(taken){goto L_002d80c4;}}
/* 002d80ac: beql a1,v0,0x002d80c4 */ {int taken=(cpu(5)==cpu(2));if(taken){/* delay 002d80b0 */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));goto L_002d80c4;}}
/* 002d80b4: jal 0x002d9998 */ set(31,UINT64_C(0x002d80bc));/* delay 002d80b8 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000054)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002d9998),UINT32_C(0x002d80b4));
/* 002d80bc: lhu a0,0xc(s0) */ set(4,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002d80c0: sw zero,0x30(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000030)),(uint32_t)cpu(0));
L_002d80c4:;
/* 002d80c4: li v0,-0x25 */ set(2,sx(UINT32_C(0xffffffdb)));
/* 002d80c8: lw a1,0x10(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000010)));
/* 002d80cc: and v0,a0,v0 */ set(2,cpu(4)&cpu(2));
/* 002d80d0: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002d80d4: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 002d80d8: move a0,v0 */ set(4,cpu(2));
/* 002d80dc: sw a1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
L_002d80e0:;
/* 002d80e0: ori v0,a0,0x8 */ set(2,cpu(4)|UINT32_C(0x00000008));
/* 002d80e4: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
L_002d80e8:;
/* 002d80e8: bnel a1,zero,0x002d80fc */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 002d80ec */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000c))));goto L_002d80fc;}}
/* 002d80f0: jal 0x002da360 */ set(31,UINT64_C(0x002d80f8));/* delay 002d80f4 */ set(4,cpu(16));body_002da360();
/* 002d80f8: lhu v1,0xc(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
L_002d80fc:;
/* 002d80fc: andi v0,v1,0x1 */ set(2,cpu(3)&UINT32_C(0x00000001));
/* 002d8100: beq v0,zero,0x002d8120 */ {int taken=(cpu(2)==cpu(0));/* delay 002d8104 */ set(2,cpu(3)&UINT32_C(0x00000002));if(taken){goto L_002d8120;}}
/* 002d8108: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 002d810c: sw zero,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002d8110: subu v0,zero,v0 */ set(2,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));
/* 002d8114: b 0x002d8130 */ /* delay 002d8118 */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));goto L_002d8130;
L_002d8120:;
/* 002d8120: bne v0,zero,0x002d812c */ {int taken=(cpu(2)!=cpu(0));/* delay 002d8124 */ set(3,cpu(0));if(taken){goto L_002d812c;}}
/* 002d8128: lw v1,0x14(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000014)));
L_002d812c:;
/* 002d812c: sw v1,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
L_002d8130:;
/* 002d8130: move v0,zero */ set(2,cpu(0));
L_002d8134:;
/* 002d8134: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d8138: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d813c: jr ra */ {uint64_t target=cpu(31);/* delay 002d8140 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002d95e0(void){
uint64_t incoming=cpu(31);
/* 002d95e0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002d95e4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d95e8: move s1,a0 */ set(17,cpu(4));
/* 002d95ec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d95f0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d95f4: bne s1,zero,0x002d9628 */ {int taken=(cpu(17)!=cpu(0));/* delay 002d95f8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002d9628;}}
/* 002d95fc: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d9600: lui a1,0x2e */ set(5,sx(UINT32_C(0x002e0000)));
/* 002d9604: lw a0,-0x41d8(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0xffffbe28)));
/* 002d9608: addiu a1,a1,-0x6a20 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffff95e0)));
/* 002d960c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9610: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9614: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d9618: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d961c: j 0x002da1e0 */ /* delay 002d9620 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002da1e0();return;
L_002d9628:;
/* 002d9628: lw v1,0x54(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000054)));
/* 002d962c: bnel v1,zero,0x002d9648 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002d9630 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000038)));goto L_002d9648;}}
/* 002d9634: lui v0,0x53 */ set(2,sx(UINT32_C(0x00530000)));
/* 002d9638: lw v1,-0x41d8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0xffffbe28)));
/* 002d963c: sw v1,0x54(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(3));
/* 002d9640: lw v0,0x38(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000038)));
/* 002d9644: nop  */ 
L_002d9648:;
/* 002d9648: bnel v0,zero,0x002d965c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d964c */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000c))));goto L_002d965c;}}
/* 002d9650: jal 0x002d9908 */ set(31,UINT64_C(0x002d9658));/* delay 002d9654 */ set(4,cpu(3));body_002d9908();
/* 002d9658: lh v1,0xc(s1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000c))));
L_002d965c:;
/* 002d965c: andi v0,v1,0x8 */ set(2,cpu(3)&UINT32_C(0x00000008));
/* 002d9660: beq v0,zero,0x002d96dc */ {int taken=(cpu(2)==cpu(0));/* delay 002d9664 */ set(2,cpu(0));if(taken){goto L_002d96dc;}}
/* 002d9668: lw s2,0x10(s1) */ lw(18,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 002d966c: beq s2,zero,0x002d96dc */ {int taken=(cpu(18)==cpu(0));/* delay 002d9670 */ set(4,cpu(0));if(taken){goto L_002d96dc;}}
/* 002d9674: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002d9678: andi v1,v1,0x3 */ set(3,cpu(3)&UINT32_C(0x00000003));
/* 002d967c: sw s2,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));
/* 002d9680: bne v1,zero,0x002d96a8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d9684 */ set(16,sx((uint32_t)cpu(2)-(uint32_t)cpu(18)));if(taken){goto L_002d96a8;}}
/* 002d9688: b 0x002d96a8 */ /* delay 002d968c */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));goto L_002d96a8;
L_002d9690:;
/* 002d9690: lhu v1,0xc(s1) */ set(3,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002d9694: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 002d9698: ori v1,v1,0x40 */ set(3,cpu(3)|UINT32_C(0x00000040));
/* 002d969c: b 0x002d96dc */ /* delay 002d96a0 */ sh(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(3));goto L_002d96dc;
L_002d96a8:;
/* 002d96a8: blez s0,0x002d96d8 */ {int taken=((int64_t)cpu(16)<=0);/* delay 002d96ac */ sw(ea(17,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));if(taken){goto L_002d96d8;}}
L_002d96b0:;
/* 002d96b0: lw v0,0x24(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000024)));
/* 002d96b4: move a2,s0 */ set(6,cpu(16));
/* 002d96b8: lw a0,0x1c(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000001c)));
/* 002d96bc: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002d96c4));/* delay 002d96c0 */ set(5,cpu(18));nocturneBattlePanelColorPrerequisiteIndirect(target,UINT32_C(0x002d96bc));}
/* 002d96c4: move v1,v0 */ set(3,cpu(2));
/* 002d96c8: blez v1,0x002d9690 */ {int taken=((int64_t)cpu(3)<=0);/* delay 002d96cc */ set(16,sx((uint32_t)cpu(16)-(uint32_t)cpu(3)));if(taken){goto L_002d9690;}}
/* 002d96d0: bgtz s0,0x002d96b0 */ {int taken=((int64_t)cpu(16)>0);/* delay 002d96d4 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(3)));if(taken){goto L_002d96b0;}}
L_002d96d8:;
/* 002d96d8: move v0,zero */ set(2,cpu(0));
L_002d96dc:;
/* 002d96dc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d96e0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d96e4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d96e8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002d96ec: jr ra */ {uint64_t target=cpu(31);/* delay 002d96f0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002d96f8(void){
uint64_t incoming=cpu(31);
/* 002d96f8: lui v0,0x2e */ set(2,sx(UINT32_C(0x002e0000)));
/* 002d96fc: lui v1,0x2e */ set(3,sx(UINT32_C(0x002e0000)));
/* 002d9700: lui t0,0x2e */ set(8,sx(UINT32_C(0x002e0000)));
/* 002d9704: lui t1,0x2e */ set(9,sx(UINT32_C(0x002e0000)));
/* 002d9708: addiu v0,v0,-0x4990 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb670)));
/* 002d970c: addiu v1,v1,-0x4928 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffb6d8)));
/* 002d9710: addiu t0,t0,-0x48a8 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0xffffb758)));
/* 002d9714: addiu t1,t1,-0x4840 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xffffb7c0)));
/* 002d9718: sw a3,0x54(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(7));
/* 002d971c: sh a1,0xc(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(5));
/* 002d9720: sh a2,0xe(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(6));
/* 002d9724: sw v0,0x20(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 002d9728: sw v1,0x24(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(3));
/* 002d972c: sw t0,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(8));
/* 002d9730: sw t1,0x2c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(9));
/* 002d9734: sw zero,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 002d9738: sw zero,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002d973c: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 002d9740: sw zero,0x10(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 002d9744: sw zero,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 002d9748: sw zero,0x18(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 002d974c: jr ra */ {uint64_t target=cpu(31);/* delay 002d9750 */ sw(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(4));checkReturn(target,incoming);return;}
}
static void body_002d9908(void){
uint64_t incoming=cpu(31);
/* 002d9908: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002d990c: lui v0,0x2e */ set(2,sx(UINT32_C(0x002e0000)));
/* 002d9910: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9914: move s0,a0 */ set(16,cpu(4));
/* 002d9918: addiu v0,v0,-0x6738 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffff98c8)));
/* 002d991c: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002d9920: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9924: addiu s1,s0,0x1e4 */ set(17,sx((uint32_t)cpu(16)+UINT32_C(0x000001e4)));
/* 002d9928: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d992c: move a0,s1 */ set(4,cpu(17));
/* 002d9930: sw v0,0x3c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(2));
/* 002d9934: move a3,s0 */ set(7,cpu(16));
/* 002d9938: sw v1,0x38(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000038)),(uint32_t)cpu(3));
/* 002d993c: li a1,0x4 */ set(5,sx(UINT32_C(0x00000004)));
/* 002d9940: jal 0x002d96f8 */ set(31,UINT64_C(0x002d9948));/* delay 002d9944 */ set(6,cpu(0));body_002d96f8();
/* 002d9948: addiu a0,s0,0x23c */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x0000023c)));
/* 002d994c: move a3,s0 */ set(7,cpu(16));
/* 002d9950: li a1,0x9 */ set(5,sx(UINT32_C(0x00000009)));
/* 002d9954: jal 0x002d96f8 */ set(31,UINT64_C(0x002d995c));/* delay 002d9958 */ set(6,sx(UINT32_C(0x00000001)));body_002d96f8();
/* 002d995c: addiu a0,s0,0x294 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000294)));
/* 002d9960: move a3,s0 */ set(7,cpu(16));
/* 002d9964: li a1,0xa */ set(5,sx(UINT32_C(0x0000000a)));
/* 002d9968: jal 0x002d96f8 */ set(31,UINT64_C(0x002d9970));/* delay 002d996c */ set(6,sx(UINT32_C(0x00000002)));body_002d96f8();
/* 002d9970: sw zero,0x1d8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000001d8)),(uint32_t)cpu(0));
/* 002d9974: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 002d9978: sw s1,0x1e0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000001e0)),(uint32_t)cpu(17));
/* 002d997c: sw v0,0x1dc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x000001dc)),(uint32_t)cpu(2));
/* 002d9980: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002d9984: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d9988: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d998c: jr ra */ {uint64_t target=cpu(31);/* delay 002d9990 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002da1e0(void){
uint64_t incoming=cpu(31);
/* 002da1e0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002da1e4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002da1e8: addiu s2,a0,0x1d8 */ set(18,sx((uint32_t)cpu(4)+UINT32_C(0x000001d8)));
/* 002da1ec: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002da1f0: move s3,zero */ set(19,cpu(0));
/* 002da1f4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002da1f8: move s4,a1 */ set(20,cpu(5));
/* 002da1fc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002da200: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002da204: beq s2,zero,0x002da250 */ {int taken=(cpu(18)==cpu(0));/* delay 002da208 */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_002da250;}}
/* 002da20c: lw s0,0x4(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000004)));
L_002da210:;
/* 002da210: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 002da214: bltz s0,0x002da244 */ {int taken=((int64_t)cpu(16)<0);/* delay 002da218 */ lw(17,ea(18,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_002da244;}}
/* 002da21c: nop  */ 
L_002da220:;
/* 002da220: lh v0,0xc(s1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002da224: beql v0,zero,0x002da23c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002da228 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));goto L_002da23c;}}
/* 002da22c: jalr s4 */ {uint64_t target=cpu(20);set(31,UINT64_C(0x002da234));/* delay 002da230 */ set(4,cpu(17));nocturneBattlePanelColorPrerequisiteIndirect(target,UINT32_C(0x002da22c));}
/* 002da234: or s3,s3,v0 */ set(19,cpu(19)|cpu(2));
/* 002da238: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
L_002da23c:;
/* 002da23c: bgez s0,0x002da220 */ {int taken=((int64_t)cpu(16)>=0);/* delay 002da240 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000058)));if(taken){goto L_002da220;}}
L_002da244:;
/* 002da244: lw s2,0x0(s2) */ lw(18,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 002da248: bnel s2,zero,0x002da210 */ {int taken=(cpu(18)!=cpu(0));if(taken){/* delay 002da24c */ lw(16,ea(18,(int32_t)UINT32_C(0x00000004)));goto L_002da210;}}
L_002da250:;
/* 002da250: move v0,s3 */ set(2,cpu(19));
/* 002da254: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002da258: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002da25c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002da260: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002da264: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002da268: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002da26c: jr ra */ {uint64_t target=cpu(31);/* delay 002da270 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002da360(void){
uint64_t incoming=cpu(31);
/* 002da360: addiu sp,sp,-0x90 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff70)));
/* 002da364: sd s0,0x70(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002da368: move s0,a0 */ set(16,cpu(4));
/* 002da36c: sd s1,0x78(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002da370: sd s2,0x80(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002da374: sd ra,0x88(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002da378: lhu v1,0xc(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002da37c: andi v0,v1,0x2 */ set(2,cpu(3)&UINT32_C(0x00000002));
/* 002da380: beq v0,zero,0x002da3a0 */ {int taken=(cpu(2)==cpu(0));/* delay 002da384 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002da3a0;}}
/* 002da388: addiu v1,s0,0x43 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000043)));
/* 002da38c: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 002da390: sw v1,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 002da394: b 0x002da49c */ /* delay 002da398 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));goto L_002da49c;
L_002da3a0:;
/* 002da3a0: lh a1,0xe(s0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 002da3a4: bltz a1,0x002da3c8 */ {int taken=((int64_t)cpu(5)<0);/* delay 002da3a8 */ set(2,cpu(3)|UINT32_C(0x00000800));if(taken){goto L_002da3c8;}}
/* 002da3ac: lw a0,0x54(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000054)));
/* 002da3b0: jal 0x002db950 */ set(31,UINT64_C(0x002da3b8));/* delay 002da3b4 */ set(6,cpu(29));body_002db950();
/* 002da3b8: bgez v0,0x002da3d8 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002da3bc */ lw(2,ea(29,(int32_t)UINT32_C(0x00000004)));if(taken){goto L_002da3d8;}}
/* 002da3c0: lhu v1,0xc(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002da3c4: ori v0,v1,0x800 */ set(2,cpu(3)|UINT32_C(0x00000800));
L_002da3c8:;
/* 002da3c8: move s2,zero */ set(18,cpu(0));
/* 002da3cc: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 002da3d0: b 0x002da41c */ /* delay 002da3d4 */ set(17,sx(UINT32_C(0x00000400)));goto L_002da41c;
L_002da3d8:;
/* 002da3d8: ori a0,zero,0x8000 */ set(4,cpu(0)|UINT32_C(0x00008000));
/* 002da3dc: li s1,0x400 */ set(17,sx(UINT32_C(0x00000400)));
/* 002da3e0: andi v0,v0,0xf000 */ set(2,cpu(2)&UINT32_C(0x0000f000));
/* 002da3e4: xori v1,v0,0x2000 */ set(3,cpu(2)^UINT32_C(0x00002000));
/* 002da3e8: bne v0,a0,0x002da410 */ {int taken=(cpu(2)!=cpu(4));/* delay 002da3ec */ set(18,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));if(taken){goto L_002da410;}}
/* 002da3f0: lui v0,0x2e */ set(2,sx(UINT32_C(0x002e0000)));
/* 002da3f4: lw v1,0x28(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000028)));
/* 002da3f8: addiu v0,v0,-0x48a8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffb758)));
/* 002da3fc: bne v1,v0,0x002da414 */ {int taken=(cpu(3)!=cpu(2));/* delay 002da400 */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));if(taken){goto L_002da414;}}
/* 002da404: sw s1,0x4c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(17));
/* 002da408: b 0x002da418 */ /* delay 002da40c */ set(2,cpu(2)|UINT32_C(0x00000400));goto L_002da418;
L_002da410:;
/* 002da410: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
L_002da414:;
/* 002da414: ori v0,v0,0x800 */ set(2,cpu(2)|UINT32_C(0x00000800));
L_002da418:;
/* 002da418: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
L_002da41c:;
/* 002da41c: lw a0,0x54(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000054)));
/* 002da420: jal 0x002d3be8 */ set(31,UINT64_C(0x002da428));/* delay 002da424 */ set(5,sx(UINT32_C(0x00000400)));nocturneBattlePanelColorCallerNativeCall(UINT32_C(0x002d3be8),UINT32_C(0x002da420));
/* 002da428: move a1,v0 */ set(5,cpu(2));
/* 002da42c: bne a1,zero,0x002da458 */ {int taken=(cpu(5)!=cpu(0));/* delay 002da430 */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));if(taken){goto L_002da458;}}
/* 002da434: addiu a0,s0,0x43 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000043)));
/* 002da438: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 002da43c: sw a0,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(4));
/* 002da440: ori v0,v0,0x2 */ set(2,cpu(2)|UINT32_C(0x00000002));
/* 002da444: sw v1,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(3));
/* 002da448: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 002da44c: b 0x002da49c */ /* delay 002da450 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_002da49c;
L_002da458:;
/* 002da458: lui v1,0x2e */ set(3,sx(UINT32_C(0x002e0000)));
/* 002da45c: lw a0,0x54(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000054)));
/* 002da460: addiu v1,v1,-0x6738 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffff98c8)));
/* 002da464: ori v0,v0,0x80 */ set(2,cpu(2)|UINT32_C(0x00000080));
/* 002da468: sw a1,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(5));
/* 002da46c: sw v1,0x3c(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000003c)),(uint32_t)cpu(3));
/* 002da470: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
/* 002da474: sw s1,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(17));
/* 002da478: beq s2,zero,0x002da49c */ {int taken=(cpu(18)==cpu(0));/* delay 002da47c */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));if(taken){goto L_002da49c;}}
/* 002da480: jal 0x002dc650 */ set(31,UINT64_C(0x002da488));/* delay 002da484 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x0000000e))));body_002dc650();
/* 002da488: beql v0,zero,0x002da4a0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002da48c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000070)));goto L_002da4a0;}}
/* 002da490: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002da494: ori v0,v0,0x1 */ set(2,cpu(2)|UINT32_C(0x00000001));
/* 002da498: sh v0,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));
L_002da49c:;
/* 002da49c: ld s0,0x70(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000070)));
L_002da4a0:;
/* 002da4a0: ld s1,0x78(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000078)));
/* 002da4a4: ld s2,0x80(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000080)));
/* 002da4a8: ld ra,0x88(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000088)));
/* 002da4ac: jr ra */ {uint64_t target=cpu(31);/* delay 002da4b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000090)));checkReturn(target,incoming);return;}
}
static void body_002da4ec(void){
uint64_t incoming=cpu(31);
/* 002da4ec: sltiu v0,a2,0x10 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002da4f0: bne v0,zero,0x002da58c */ {int taken=(cpu(2)!=cpu(0));/* delay 002da4f4 */ set(5,cpu(5)&UINT32_C(0x000000ff));if(taken){goto L_002da58c;}}
/* 002da4f8: andi v0,a0,0xf */ set(2,cpu(4)&UINT32_C(0x0000000f));
/* 002da4fc: bne v0,zero,0x002da58c */ {int taken=(cpu(2)!=cpu(0));/* delay 002da500 */ set(7,cpu(4));if(taken){goto L_002da58c;}}
/* 002da504: dsll v1,a1,0x8 */ set(3,cpu(5)<<8);
/* 002da508: lui v0,0x101 */ set(2,sx(UINT32_C(0x01010000)));
/* 002da50c: ori v0,v0,0x101 */ set(2,cpu(2)|UINT32_C(0x00000101));
/* 002da510: dsll v0,v0,0x10 */ set(2,cpu(2)<<16);
/* 002da514: ori v0,v0,0x101 */ set(2,cpu(2)|UINT32_C(0x00000101));
/* 002da518: dsll v0,v0,0x10 */ set(2,cpu(2)<<16);
/* 002da51c: ori v0,v0,0x101 */ set(2,cpu(2)|UINT32_C(0x00000101));
/* 002da520: daddu t2,v1,a1 */ set(10,cpu(3)+cpu(5));
/* 002da524: lui v1,0x8080 */ set(3,sx(UINT32_C(0x80800000)));
/* 002da528: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 002da52c: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002da530: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 002da534: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002da538: ori v1,v1,0x8080 */ set(3,cpu(3)|UINT32_C(0x00008080));
/* 002da53c: pcpyh t0,t2 */ prerequisitePcpyh(8,10);
/* 002da540: pcpyld t1,t0,t0 */ requestPacked(0,9,8,8);
/* 002da544: move a0,v0 */ set(4,cpu(2));
/* 002da548: pcpyld t0,v1,v1 */ requestPacked(0,8,3,3);
L_002da54c:;
/* 002da54c: lq v0,0x0(a3) */ requestLq(2,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 002da550: pxor v0,v0,t1 */ requestPacked(5,2,2,9);
/* 002da554: pcpyld t2,a0,a0 */ requestPacked(0,10,4,4);
/* 002da558: pnor v1,zero,v0 */ requestPacked(3,3,0,2);
/* 002da55c: psubb v0,v0,t2 */ requestPacked(4,2,2,10);
/* 002da560: pand v0,v0,v1 */ requestPacked(2,2,2,3);
/* 002da564: pand v0,v0,t0 */ requestPacked(2,2,2,8);
/* 002da568: pcpyud v1,v0,t1 */ requestPacked(1,3,2,9);
/* 002da56c: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002da570: bnel v0,zero,0x002da58c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002da574 */ set(4,cpu(7));goto L_002da58c;}}
/* 002da578: addiu a2,a2,-0x10 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xfffffff0)));
/* 002da57c: sltiu v0,a2,0x10 */ set(2,cpu(6)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002da580: beq v0,zero,0x002da54c */ {int taken=(cpu(2)==cpu(0));/* delay 002da584 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000010)));if(taken){goto L_002da54c;}}
/* 002da588: move a0,a3 */ set(4,cpu(7));
L_002da58c:;
/* 002da58c: lui v0,0xffff */ set(2,sx(UINT32_C(0xffff0000)));
/* 002da590: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 002da594: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002da598: beq a2,v0,0x002da5bc */ {int taken=(cpu(6)==cpu(2));/* delay 002da59c */ if(taken){goto L_002da5bc;}}
/* 002da5a0: lui v1,0xffff */ set(3,sx(UINT32_C(0xffff0000)));
/* 002da5a4: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
L_002da5a8:;
/* 002da5a8: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002da5ac: beq v0,a1,0x002da5c4 */ {int taken=(cpu(2)==cpu(5));/* delay 002da5b0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));if(taken){goto L_002da5c4;}}
/* 002da5b4: bne a2,v1,0x002da5a8 */ {int taken=(cpu(6)!=cpu(3));/* delay 002da5b8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));if(taken){goto L_002da5a8;}}
L_002da5bc:;
/* 002da5bc: jr ra */ {uint64_t target=cpu(31);/* delay 002da5c0 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_002da5c4:;
/* 002da5c4: jr ra */ {uint64_t target=cpu(31);/* delay 002da5c8 */ set(2,cpu(4));checkReturn(target,incoming);return;}
}
static void body_002db5e8(void){
uint64_t incoming=cpu(31);
/* 002db5e8: dsll32 v1,a0,0x0 */ set(3,cpu(4)<<32);
/* 002db5ec: dsra32 v1,v1,0x0 */ set(3,(uint64_t)((int64_t)cpu(3)>>32));
/* 002db5f0: dsra32 a0,a0,0x0 */ set(4,(uint64_t)((int64_t)cpu(4)>>32));
/* 002db5f4: lui v0,0x7fff */ set(2,sx(UINT32_C(0x7fff0000)));
/* 002db5f8: lui a2,0x7ff0 */ set(6,sx(UINT32_C(0x7ff00000)));
/* 002db5fc: subu a1,zero,v1 */ set(5,sx((uint32_t)cpu(0)-(uint32_t)cpu(3)));
/* 002db600: ori v0,v0,0xffff */ set(2,cpu(2)|UINT32_C(0x0000ffff));
/* 002db604: or v1,v1,a1 */ set(3,cpu(3)|cpu(5));
/* 002db608: and a0,a0,v0 */ set(4,cpu(4)&cpu(2));
/* 002db60c: srl v1,v1,0x1f */ set(3,sx((uint32_t)cpu(3)>>31));
/* 002db610: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002db614: or a0,a0,v1 */ set(4,cpu(4)|cpu(3));
/* 002db618: subu a0,a2,a0 */ set(4,sx((uint32_t)cpu(6)-(uint32_t)cpu(4)));
/* 002db61c: subu v1,zero,a0 */ set(3,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
/* 002db620: or a0,a0,v1 */ set(4,cpu(4)|cpu(3));
/* 002db624: srl a0,a0,0x1f */ set(4,sx((uint32_t)cpu(4)>>31));
/* 002db628: jr ra */ {uint64_t target=cpu(31);/* delay 002db62c */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(4)));checkReturn(target,incoming);return;}
}
static void body_002db630(void){
uint64_t incoming=cpu(31);
/* 002db630: move v0,a0 */ set(2,cpu(4));
/* 002db634: dsll32 a0,v0,0x0 */ set(4,cpu(2)<<32);
/* 002db638: dsra32 a0,a0,0x0 */ set(4,(uint64_t)((int64_t)cpu(4)>>32));
/* 002db63c: dsra32 v0,v0,0x0 */ set(2,(uint64_t)((int64_t)cpu(2)>>32));
/* 002db640: lui v1,0x7fff */ set(3,sx(UINT32_C(0x7fff0000)));
/* 002db644: lui a2,0x7ff0 */ set(6,sx(UINT32_C(0x7ff00000)));
/* 002db648: subu a1,zero,a0 */ set(5,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
/* 002db64c: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 002db650: or a0,a0,a1 */ set(4,cpu(4)|cpu(5));
/* 002db654: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002db658: srl a0,a0,0x1f */ set(4,sx((uint32_t)cpu(4)>>31));
/* 002db65c: or v0,v0,a0 */ set(2,cpu(2)|cpu(4));
/* 002db660: subu v0,a2,v0 */ set(2,sx((uint32_t)cpu(6)-(uint32_t)cpu(2)));
/* 002db664: jr ra */ {uint64_t target=cpu(31);/* delay 002db668 */ set(2,sx((uint32_t)cpu(2)>>31));checkReturn(target,incoming);return;}
}
static void body_002db950(void){
uint64_t incoming=cpu(31);
/* 002db950: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002db954: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002db958: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002db95c: move s0,a0 */ set(16,cpu(4));
/* 002db960: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002db964: addiu s1,v0,0x2178 */ set(17,sx((uint32_t)cpu(2)+UINT32_C(0x00002178)));
/* 002db968: move a0,a1 */ set(4,cpu(5));
/* 002db96c: move a1,a2 */ set(5,cpu(6));
/* 002db970: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002db974: jal 0x002dc658 */ set(31,UINT64_C(0x002db97c));/* delay 002db978 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));body_002dc658();
/* 002db97c: move v1,v0 */ set(3,cpu(2));
/* 002db980: li a0,-0x1 */ set(4,sx(UINT32_C(0xffffffff)));
/* 002db984: bnel v1,a0,0x002db99c */ {int taken=(cpu(3)!=cpu(4));if(taken){/* delay 002db988 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002db99c;}}
/* 002db98c: lw v1,0x0(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002db990: bnel v1,zero,0x002db998 */ {int taken=(cpu(3)!=cpu(0));if(taken){/* delay 002db994 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));goto L_002db998;}}
L_002db998:;
/* 002db998: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002db99c:;
/* 002db99c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002db9a0: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002db9a4: jr ra */ {uint64_t target=cpu(31);/* delay 002db9a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002dc650(void){
uint64_t incoming=cpu(31);
/* 002dc650: jr ra */ {uint64_t target=cpu(31);/* delay 002dc654 */ set(2,sx(UINT32_C(0x00000001)));checkReturn(target,incoming);return;}
}
static void body_002dc658(void){
uint64_t incoming=cpu(31);
/* 002dc658: li v0,0x2000 */ set(2,sx(UINT32_C(0x00002000)));
/* 002dc65c: sd zero,0x48(a1) */ save(0,ea(5,(int32_t)UINT32_C(0x00000048)));
/* 002dc660: sw v0,0x4(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
/* 002dc664: jr ra */ {uint64_t target=cpu(31);/* delay 002dc668 */ set(2,cpu(0));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelColorPrerequisiteBody(uint32_t entry){switch(entry){
case UINT32_C(0x00101978):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00101978();return 1u;case UINT32_C(0x00101ab0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00101ab0();return 1u;case UINT32_C(0x00117b08):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00117b08();return 1u;case UINT32_C(0x001c6160):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c6160();return 1u;case UINT32_C(0x001c6338):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c6338();return 1u;case UINT32_C(0x001c6438):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c6438();return 1u;case UINT32_C(0x001c7cb8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c7cb8();return 1u;case UINT32_C(0x001c7e38):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c7e38();return 1u;case UINT32_C(0x001ca298):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001ca298();return 1u;case UINT32_C(0x001ca430):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001ca430();return 1u;case UINT32_C(0x00244200):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00244200();return 1u;case UINT32_C(0x002469a0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002469a0();return 1u;case UINT32_C(0x00279868):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00279868();return 1u;case UINT32_C(0x00279980):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00279980();return 1u;case UINT32_C(0x00279a88):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00279a88();return 1u;case UINT32_C(0x00279c00):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00279c00();return 1u;case UINT32_C(0x0027a290):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0027a290();return 1u;case UINT32_C(0x0027a318):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0027a318();return 1u;case UINT32_C(0x0027aa40):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0027aa40();return 1u;case UINT32_C(0x0027fba0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0027fba0();return 1u;case UINT32_C(0x00282270):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00282270();return 1u;case UINT32_C(0x002a89c0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a89c0();return 1u;case UINT32_C(0x002a8a30):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a8a30();return 1u;case UINT32_C(0x002a8ab0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a8ab0();return 1u;case UINT32_C(0x002a8af8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a8af8();return 1u;case UINT32_C(0x002aa980):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002aa980();return 1u;case UINT32_C(0x002aa9e0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002aa9e0();return 1u;case UINT32_C(0x002ab0c8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002ab0c8();return 1u;case UINT32_C(0x002ab0d8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002ab0d8();return 1u;case UINT32_C(0x002ab0e8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002ab0e8();return 1u;case UINT32_C(0x002acb50):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002acb50();return 1u;case UINT32_C(0x002acd40):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002acd40();return 1u;case UINT32_C(0x002acdc0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002acdc0();return 1u;case UINT32_C(0x002ace38):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002ace38();return 1u;case UINT32_C(0x002acea0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002acea0();return 1u;case UINT32_C(0x002acee8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002acee8();return 1u;case UINT32_C(0x002af0f8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002af0f8();return 1u;case UINT32_C(0x002af210):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002af210();return 1u;case UINT32_C(0x002b9c18):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002b9c18();return 1u;case UINT32_C(0x002b9c20):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002b9c20();return 1u;case UINT32_C(0x002b9cc8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002b9cc8();return 1u;case UINT32_C(0x002b9d38):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002b9d38();return 1u;case UINT32_C(0x002b9d68):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002b9d68();return 1u;case UINT32_C(0x002b9d78):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002b9d78();return 1u;case UINT32_C(0x002b9d80):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002b9d80();return 1u;case UINT32_C(0x002b9dd0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002b9dd0();return 1u;case UINT32_C(0x002c0ba8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c0ba8();return 1u;case UINT32_C(0x002d1590):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d1590();return 1u;case UINT32_C(0x002d17f0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d17f0();return 1u;case UINT32_C(0x002d1848):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d1848();return 1u;case UINT32_C(0x002d1b38):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d1b38();return 1u;case UINT32_C(0x002d1b88):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d1b88();return 1u;case UINT32_C(0x002d1c40):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d1c40();return 1u;case UINT32_C(0x002d34a0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d34a0();return 1u;case UINT32_C(0x002d3578):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d3578();return 1u;case UINT32_C(0x002d3638):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d3638();return 1u;case UINT32_C(0x002d5690):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d5690();return 1u;case UINT32_C(0x002d6548):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d6548();return 1u;case UINT32_C(0x002d7ea8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d7ea8();return 1u;case UINT32_C(0x002d8038):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d8038();return 1u;case UINT32_C(0x002d95e0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d95e0();return 1u;case UINT32_C(0x002d96f8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d96f8();return 1u;case UINT32_C(0x002d9908):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d9908();return 1u;case UINT32_C(0x002da1e0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002da1e0();return 1u;case UINT32_C(0x002da360):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002da360();return 1u;case UINT32_C(0x002da4ec):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002da4ec();return 1u;case UINT32_C(0x002db5e8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002db5e8();return 1u;case UINT32_C(0x002db630):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002db630();return 1u;case UINT32_C(0x002db950):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002db950();return 1u;case UINT32_C(0x002dc650):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dc650();return 1u;case UINT32_C(0x002dc658):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dc658();return 1u;
default:return 0u;}}
