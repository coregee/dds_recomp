#include "battle_panel_renderer_remaining.h"
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
static void loadPartial(unsigned reg,uint32_t address,int left){
 unsigned offset=address&7u,count=left?offset+1u:8u-offset;
 uint32_t start=left?(address&~7u):address;unsigned target=left?7u-offset:0u;
 uint64_t value=cpu(reg);
 for(unsigned i=0;i<count;i++){unsigned shift=8u*(target+i);value=(value&~(UINT64_C(255)<<shift))|((uint64_t)*at(start+i)<<shift);}
 set(reg,value);
}
static void storePartial(uint32_t address,unsigned reg,int left){
 unsigned offset=address&7u,count=left?offset+1u:8u-offset;
 uint32_t start=left?(address&~7u):address;unsigned source=left?7u-offset:0u;
 uint64_t value=cpu(reg);
 for(unsigned i=0;i<count;i++)*at(start+i)=(uint8_t)(value>>(8u*(source+i)));
}
static void body_002592b0(void);
static void body_00267ec8(void);
static void body_0025e8e0(void);
static void body_0025ea48(void);
static void body_001c86a0(void);
static void body_00101898(void);
static void body_001c6098(void);
static void body_001c8758(void);
static void body_00257cc8(void);
static void body_0025d690(void);
static void body_001ce7d8(void);
static void body_00267f18(void);
static void body_002d4748(void);
static void body_002469c0(void);
static void body_001b1740(void);
static void body_001c7a60(void);
static void body_00246ab8(void);
static void body_002627c0(void);
static void body_002629e8(void);
static void body_002642e0(void);
static void body_00264368(void);
static void body_00267788(void);
static void body_002677b8(void);
static void body_0026a468(void);
static void body_002a9688(void);
static void body_001c8730(void);
static void body_001c96d8(void);
static void body_001c98c0(void);
static void body_001c9a98(void);
static void body_001c9b58(void);
static void body_001c9c28(void);
static void body_001cf320(void);
static void body_001e9998(void);
static void body_00246a40(void);
static void body_00246b68(void);
static void body_00258de8(void);
static void body_00259c48(void);
static void body_0025dc00(void);
static void body_002645a8(void);
static void body_002a8bd8(void);
static void body_002a9038(void);
static void body_002a9540(void);
static void body_002c10e8(void);
static void body_002c1c20(void);
static void body_002dbdd0(void);
static void body_002de458(void);
static void body_00173cb0(void);
static void body_00173ef0(void);
static void body_001c60e0(void);
static void body_001c6b68(void);
static void body_001c7288(void);
static void body_001c81b8(void);
static void body_001c8508(void);
static void body_001c87c8(void);
static void body_001c8f08(void);
static void body_001c9188(void);
static void body_001c9230(void);
static void body_001c9d00(void);
static void body_001cdd78(void);
static void body_001ce538(void);
static void body_001ce5e8(void);
static void body_001ce808(void);
static void body_001cf178(void);
static void body_001cf1a8(void);
static void body_001cf440(void);
static void body_001cfc58(void);
static void body_001cfc80(void);
static void body_001cfe48(void);
static void body_002262e8(void);
static void body_00243f40(void);
static void body_00245c90(void);
static void body_002514f0(void);
static void body_00251538(void);
static void body_002517e0(void);
static void body_00259300(void);
static void body_0025da78(void);
static void body_0025e9c8(void);
static void body_0025ef10(void);
static void body_00261ca0(void);
static void body_00261d20(void);
static void body_00262480(void);
static void body_00262610(void);
static void body_00262a68(void);
static void body_00262ac8(void);
static void body_00262b38(void);
static void body_00262bb8(void);
static void body_00262cc0(void);
static void body_00264010(void);
static void body_0026a3d8(void);
static void body_002a8520(void);
static void body_002a9558(void);
static void body_002acce0(void);
static void body_002c0f28(void);
static void body_002c1238(void);
static void body_002c1240(void);
static void body_002c18d8(void);
static void body_002c1ca0(void);
static void body_002d57f8(void);
static void body_002d5bf8(void);
static void body_002dbc20(void);
static void body_002dbdc0(void);
static void body_002dbdf0(void);
static void body_002dc260(void);
static void body_002dc270(void);
static void body_002dc830(void);
static void body_002dc8d8(void);
static void body_002de178(void);
static void body_002de2b0(void);
static void body_002acd98(void);
static void body_002592b0(void){
uint64_t incoming=cpu(31);
/* 002592b0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002592b4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002592b8: move s0,a0 */ set(16,cpu(4));
/* 002592bc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002592c0: move s1,a3 */ set(17,cpu(7));
/* 002592c4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002592c8: move s2,a2 */ set(18,cpu(6));
/* 002592cc: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002592d0: jal 0x00259300 */ set(31,UINT64_C(0x002592d8));/* delay 002592d4 */ lw(4,ea(16,(int32_t)UINT32_C(0x00000000)));body_00259300();
/* 002592d8: sw s2,0x4c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000004c)),(uint32_t)cpu(18));
/* 002592dc: sw s1,0x50(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000050)),(uint32_t)cpu(17));
/* 002592e0: sw v0,0x48(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000048)),(uint32_t)cpu(2));
/* 002592e4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002592e8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002592ec: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002592f0: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002592f4: jr ra */ {uint64_t target=cpu(31);/* delay 002592f8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00267ec8(void){
uint64_t incoming=cpu(31);
/* 00267ec8: sltiu v0,a0,0x14 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000014));
/* 00267ecc: beq v0,zero,0x00267f0c */ {int taken=(cpu(2)==cpu(0));/* delay 00267ed0 */ set(3,cpu(0));if(taken){goto L_00267f0c;}}
/* 00267ed4: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00267ed8: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00267edc: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00267ee0: lw v1,0x4c60(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004c60)));
/* 00267ee4: jr v1 */ {uint64_t target=cpu(3);/* delay 00267ee8 */ switch((uint32_t)target){case UINT32_C(0x00267ef0):goto L_00267ef0;case UINT32_C(0x00267ef8):goto L_00267ef8;case UINT32_C(0x00267f00):goto L_00267f00;case UINT32_C(0x00267f08):goto L_00267f08;default:abort();}}
L_00267ef0:;
/* 00267ef0: b 0x00267f0c */ /* delay 00267ef4 */ set(3,sx(UINT32_C(0x0000007f)));goto L_00267f0c;
L_00267ef8:;
/* 00267ef8: b 0x00267f0c */ /* delay 00267efc */ set(3,sx(UINT32_C(0x00000004)));goto L_00267f0c;
L_00267f00:;
/* 00267f00: b 0x00267f0c */ /* delay 00267f04 */ set(3,sx(UINT32_C(0x00000001)));goto L_00267f0c;
L_00267f08:;
/* 00267f08: li v1,0x7fff */ set(3,sx(UINT32_C(0x00007fff)));
L_00267f0c:;
/* 00267f0c: jr ra */ {uint64_t target=cpu(31);/* delay 00267f10 */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
static void body_0025e8e0(void){
uint64_t incoming=cpu(31);
/* 0025e8e0: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 0025e8e4: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0025e8e8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025e8ec: jal 0x00101898 */ set(31,UINT64_C(0x0025e8f4));/* delay 0025e8f0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004350)));body_00101898();
/* 0025e8f4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025e8f8: move a0,v0 */ set(4,cpu(2));
/* 0025e8fc: j 0x00101ab0 */ /* delay 0025e900 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattlePanelRendererRemainingCall(UINT32_C(0x00101ab0),UINT32_C(0x0025e8fc));return;
}
static void body_0025ea48(void){
uint64_t incoming=cpu(31);
/* 0025ea48: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0025ea4c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0025ea50: move s4,a0 */ set(20,cpu(4));
/* 0025ea54: li a0,0x40 */ set(4,sx(UINT32_C(0x00000040)));
/* 0025ea58: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025ea5c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025ea60: move s1,a1 */ set(17,cpu(5));
/* 0025ea64: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025ea68: move s2,a2 */ set(18,cpu(6));
/* 0025ea6c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025ea70: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0025ea74: jal 0x002a8af8 */ set(31,UINT64_C(0x0025ea7c));/* delay 0025ea78 */ set(19,cpu(7));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002a8af8),UINT32_C(0x0025ea74));
/* 0025ea7c: move s0,v0 */ set(16,cpu(2));
/* 0025ea80: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 0025ea84: sh s1,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(17));
/* 0025ea88: move a0,s4 */ set(4,cpu(20));
/* 0025ea8c: sh s2,0x2(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(18));
/* 0025ea90: move a1,s0 */ set(5,cpu(16));
/* 0025ea94: sw s3,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(19));
/* 0025ea98: sw v0,0x20(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(2));
/* 0025ea9c: sb zero,0x4(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(0));
/* 0025eaa0: sb zero,0x5(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000005)),(uint8_t)cpu(0));
/* 0025eaa4: sh zero,0x6(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000006)),(uint16_t)cpu(0));
/* 0025eaa8: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 0025eaac: sw zero,0x10(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 0025eab0: sw zero,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 0025eab4: sw zero,0x18(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 0025eab8: sw zero,0x1c(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(0));
/* 0025eabc: sw zero,0x24(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(0));
/* 0025eac0: sw zero,0x28(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 0025eac4: jal 0x0025e9c8 */ set(31,UINT64_C(0x0025eacc));/* delay 0025eac8 */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(0));body_0025e9c8();
/* 0025eacc: move v0,s0 */ set(2,cpu(16));
/* 0025ead0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025ead4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025ead8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025eadc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025eae0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0025eae4: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0025eae8: jr ra */ {uint64_t target=cpu(31);/* delay 0025eaec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c86a0(void){
uint64_t incoming=cpu(31);
/* 001c86a0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c86a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c86a8: move s0,a0 */ set(16,cpu(4));
/* 001c86ac: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c86b0: lw v0,0x14(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c86b4: beq v0,zero,0x001c86c8 */ {int taken=(cpu(2)==cpu(0));/* delay 001c86b8 */ set(8,cpu(2));if(taken){goto L_001c86c8;}}
/* 001c86bc: lw v0,0x1c(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0x0000001c)));
/* 001c86c0: beql v0,zero,0x001c86c8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c86c4 */ sb(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(0));goto L_001c86c8;}}
L_001c86c8:;
/* 001c86c8: lb v0,0x1c(s0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000001c))));
/* 001c86cc: beql v0,zero,0x001c8704 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c86d0 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000001d))));goto L_001c8704;}}
/* 001c86d4: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
/* 001c86d8: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 001c86dc: lb a3,0xe(s0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 001c86e0: addiu a0,a0,-0xbd0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff430)));
/* 001c86e4: jal 0x001c7828 */ set(31,UINT64_C(0x001c86ec));/* delay 001c86e8 */ set(5,cpu(0));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7828),UINT32_C(0x001c86e4));
/* 001c86ec: lbu a1,0xf(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000f))));
/* 001c86f0: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c86f4: jal 0x001c7a60 */ set(31,UINT64_C(0x001c86fc));/* delay 001c86f8 */ set(4,cpu(2));body_001c7a60();
/* 001c86fc: sb zero,0x1c(s0) */ sb(ea(16,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(0));
/* 001c8700: lb v0,0x1d(s0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000001d))));
L_001c8704:;
/* 001c8704: beql v0,zero,0x001c8724 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c8708 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_001c8724;}}
/* 001c870c: lw a0,0x14(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c8710: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001c8714: jal 0x001c7b30 */ set(31,UINT64_C(0x001c871c));/* delay 001c8718 */ lw(6,ea(16,(int32_t)UINT32_C(0x00000004)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7b30),UINT32_C(0x001c8714));
/* 001c871c: sb zero,0x1d(s0) */ sb(ea(16,(int32_t)UINT32_C(0x0000001d)),(uint8_t)cpu(0));
/* 001c8720: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_001c8724:;
/* 001c8724: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c8728: jr ra */ {uint64_t target=cpu(31);/* delay 001c872c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
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
static void body_001c6098(void){
uint64_t incoming=cpu(31);
/* 001c6098: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001c609c: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 001c60a0: addiu a3,v0,0x5b10 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0x00005b10)));
/* 001c60a4: move a2,zero */ set(6,cpu(0));
/* 001c60a8: lhu v1,0x0(a3) */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000000))));
/* 001c60ac: nop  */ 
L_001c60b0:;
/* 001c60b0: addiu a3,a3,0x2 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000002)));
/* 001c60b4: move v0,a2 */ set(2,cpu(6));
/* 001c60b8: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001c60bc: beq v1,a0,0x001c60d8 */ {int taken=(cpu(3)==cpu(4));/* delay 001c60c0 */ set(5,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x000001a0));if(taken){goto L_001c60d8;}}
/* 001c60c4: nop  */ 
/* 001c60c8: nop  */ 
/* 001c60cc: bnel a1,zero,0x001c60b0 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 001c60d0 */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000000))));goto L_001c60b0;}}
/* 001c60d4: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
L_001c60d8:;
/* 001c60d8: jr ra */ {uint64_t target=cpu(31);/* delay 001c60dc */ checkReturn(target,incoming);return;}
}
static void body_001c8758(void){
uint64_t incoming=cpu(31);
/* 001c8758: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c875c: andi a1,a1,0xffff */ set(5,cpu(5)&UINT32_C(0x0000ffff));
/* 001c8760: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c8764: move s0,a0 */ set(16,cpu(4));
/* 001c8768: srl v0,a1,0x8 */ set(2,sx((uint32_t)cpu(5)>>8));
/* 001c876c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c8770: sb a1,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(5));
/* 001c8774: sb v0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001c8778: jal 0x001c86a0 */ set(31,UINT64_C(0x001c8780));/* delay 001c877c */ sb(ea(29,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(0));body_001c86a0();
/* 001c8780: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
/* 001c8784: move a0,sp */ set(4,cpu(29));
/* 001c8788: lb a3,0xe(s0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 001c878c: move t1,zero */ set(9,cpu(0));
/* 001c8790: lw t0,0x14(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c8794: jal 0x001c7890 */ set(31,UINT64_C(0x001c879c));/* delay 001c8798 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000c))));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7890),UINT32_C(0x001c8794));
/* 001c879c: lb a1,-0x4d68(gp) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));
/* 001c87a0: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c87a4: jal 0x001c7a88 */ set(31,UINT64_C(0x001c87ac));/* delay 001c87a8 */ set(4,cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7a88),UINT32_C(0x001c87a4));
/* 001c87ac: lw a0,0x14(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c87b0: jal 0x001c7b40 */ set(31,UINT64_C(0x001c87b8));/* delay 001c87b4 */ lw(5,ea(16,(int32_t)UINT32_C(0x00000008)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7b40),UINT32_C(0x001c87b0));
/* 001c87b8: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c87bc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c87c0: jr ra */ {uint64_t target=cpu(31);/* delay 001c87c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00257cc8(void){
uint64_t incoming=cpu(31);
/* 00257cc8: jr ra */ {uint64_t target=cpu(31);/* delay 00257ccc */ sb(ea(4,(int32_t)UINT32_C(0x00000009)),(uint8_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_0025d690(void){
uint64_t incoming=cpu(31);
/* 0025d690: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 0025d694: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0025d698: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025d69c: jal 0x00101898 */ set(31,UINT64_C(0x0025d6a4));/* delay 0025d6a0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000042b8)));body_00101898();
/* 0025d6a4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025d6a8: move a0,v0 */ set(4,cpu(2));
/* 0025d6ac: j 0x00101ab0 */ /* delay 0025d6b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);nocturneBattlePanelRendererRemainingCall(UINT32_C(0x00101ab0),UINT32_C(0x0025d6ac));return;
}
static void body_001ce7d8(void){
uint64_t incoming=cpu(31);
/* 001ce7d8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001ce7dc: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001ce7e0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ce7e4: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001ce7e8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001ce7ec: move a3,zero */ set(7,cpu(0));
/* 001ce7f0: lui a0,0x57 */ set(4,sx(UINT32_C(0x00570000)));
/* 001ce7f4: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001ce7f8: lw a0,-0x4174(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0xffffbe8c)));
/* 001ce7fc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ce800: j 0x001cf320 */ /* delay 001ce804 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001cf320();return;
}
static void body_00267f18(void){
uint64_t incoming=cpu(31);
/* 00267f18: sltiu v0,a0,0x14 */ set(2,cpu(4)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000014));
/* 00267f1c: beq v0,zero,0x00267f4c */ {int taken=(cpu(2)==cpu(0));/* delay 00267f20 */ set(3,cpu(0));if(taken){goto L_00267f4c;}}
/* 00267f24: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 00267f28: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00267f2c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00267f30: lw v1,0x4cb0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004cb0)));
/* 00267f34: jr v1 */ {uint64_t target=cpu(3);/* delay 00267f38 */ switch((uint32_t)target){case UINT32_C(0x00267f40):goto L_00267f40;case UINT32_C(0x00267f48):goto L_00267f48;default:abort();}}
L_00267f40:;
/* 00267f40: b 0x00267f4c */ /* delay 00267f44 */ set(3,sx(UINT32_C(0xfffffffc)));goto L_00267f4c;
L_00267f48:;
/* 00267f48: move v1,zero */ set(3,cpu(0));
L_00267f4c:;
/* 00267f4c: jr ra */ {uint64_t target=cpu(31);/* delay 00267f50 */ set(2,cpu(3));checkReturn(target,incoming);return;}
}
static void body_002d4748(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 002d4748: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 002d474c: lui t4,0x53 */ set(12,sx(UINT32_C(0x00530000)));
/* 002d4750: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d4754: sd a1,0x38(sp) */ save(5,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002d4758: move a1,a0 */ set(5,cpu(4));
/* 002d475c: sd a2,0x40(sp) */ save(6,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002d4760: addiu a2,sp,0x38 */ set(6,sx((uint32_t)cpu(29)+UINT32_C(0x00000038)));
/* 002d4764: sd a3,0x48(sp) */ save(7,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 002d4768: sd t0,0x50(sp) */ save(8,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002d476c: sd t1,0x58(sp) */ save(9,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 002d4770: sd t2,0x60(sp) */ save(10,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002d4774: sd t3,0x68(sp) */ save(11,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 002d4778: swc1 f12,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[12]);
/* 002d477c: swc1 f13,0x1c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000001c)),f[13]);
/* 002d4780: swc1 f14,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[14]);
/* 002d4784: swc1 f15,0x24(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000024)),f[15]);
/* 002d4788: swc1 f16,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[16]);
/* 002d478c: swc1 f17,0x2c(sp) */ sw(ea(29,(int32_t)UINT32_C(0x0000002c)),f[17]);
/* 002d4790: swc1 f18,0x30(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000030)),f[18]);
/* 002d4794: swc1 f19,0x34(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000034)),f[19]);
/* 002d4798: lw v0,-0x41d8(t4) */ lw(2,ea(12,(int32_t)UINT32_C(0xffffbe28)));
/* 002d479c: lw v1,0x8(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 002d47a0: sw v0,0x54(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000054)),(uint32_t)cpu(2));
/* 002d47a4: jal 0x002d6600 */ set(31,UINT64_C(0x002d47ac));/* delay 002d47a8 */ lw(4,ea(2,(int32_t)UINT32_C(0x00000008)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d6600),UINT32_C(0x002d47a4));
/* 002d47ac: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d47b0: jr ra */ {uint64_t target=cpu(31);/* delay 002d47b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
static void body_002469c0(void){
uint64_t incoming=cpu(31);
/* 002469c0: lhu a2,0x0(a1) */ set(6,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002469c4: move v0,zero */ set(2,cpu(0));
/* 002469c8: andi v1,a2,0x1 */ set(3,cpu(6)&UINT32_C(0x00000001));
/* 002469cc: andi v1,v1,0xffff */ set(3,cpu(3)&UINT32_C(0x0000ffff));
/* 002469d0: beq v1,zero,0x00246a34 */ {int taken=(cpu(3)==cpu(0));/* delay 002469d4 */ set(7,cpu(6)&UINT32_C(0x00000002));if(taken){goto L_00246a34;}}
/* 002469d8: beq a3,zero,0x00246a08 */ {int taken=(cpu(7)==cpu(0));/* delay 002469dc */ set(3,cpu(6)&UINT32_C(0x00000004));if(taken){goto L_00246a08;}}
/* 002469e0: lh v1,0x4(a1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000004))));
/* 002469e4: lw a0,0x8(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002469e8: sll v0,v1,0x4 */ set(2,sx((uint32_t)cpu(3)<<4));
/* 002469ec: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002469f0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002469f4: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 002469f8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 002469fc: jr ra */ {uint64_t target=cpu(31);/* delay 00246a00 */ set(2,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));checkReturn(target,incoming);return;}
L_00246a08:;
/* 00246a08: bne v1,zero,0x00246a34 */ {int taken=(cpu(3)!=cpu(0));/* delay 00246a0c */ set(2,cpu(0));if(taken){goto L_00246a34;}}
/* 00246a10: lh v1,0x4(a1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000004))));
/* 00246a14: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00246a18: sll a0,v1,0x4 */ set(4,sx((uint32_t)cpu(3)<<4));
/* 00246a1c: subu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(3)));
/* 00246a20: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00246a24: subu a0,a0,v1 */ set(4,sx((uint32_t)cpu(4)-(uint32_t)cpu(3)));
/* 00246a28: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 00246a2c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 00246a30: addiu v0,v0,0xa54 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000a54)));
L_00246a34:;
/* 00246a34: jr ra */ {uint64_t target=cpu(31);/* delay 00246a38 */ checkReturn(target,incoming);return;}
}
static void body_001b1740(void){
uint64_t incoming=cpu(31);
/* 001b1740: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 001b1744: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001b1748: sll v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)<<4));
/* 001b174c: addiu v0,v0,0xe40 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000e40)));
/* 001b1750: lui a1,0x32 */ set(5,sx(UINT32_C(0x00320000)));
/* 001b1754: addu a1,a1,v1 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 001b1758: lb a1,0xc5c(a1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000c5c))));
/* 001b175c: beq a1,zero,0x001b1768 */ {int taken=(cpu(5)==cpu(0));/* delay 001b1760 */ sw(ea(2,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(4));if(taken){goto L_001b1768;}}
/* 001b1764: sw zero,0x2c(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(0));
L_001b1768:;
/* 001b1768: jr ra */ {uint64_t target=cpu(31);/* delay 001b176c */ checkReturn(target,incoming);return;}
}
static void body_001c7a60(void){
uint64_t incoming=cpu(31);
/* 001c7a60: andi a1,a1,0xff */ set(5,cpu(5)&UINT32_C(0x000000ff));
/* 001c7a64: sll a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)<<1));
/* 001c7a68: slti v0,a1,0x81 */ set(2,(int64_t)cpu(5)<(int64_t)(int32_t)UINT32_C(0x00000081));
/* 001c7a6c: bne v0,zero,0x001c7a80 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c7a70 */ set(2,sx(UINT32_C(0xffffff80)));if(taken){goto L_001c7a80;}}
/* 001c7a74: jr ra */ {uint64_t target=cpu(31);/* delay 001c7a78 */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));checkReturn(target,incoming);return;}
L_001c7a80:;
/* 001c7a80: jr ra */ {uint64_t target=cpu(31);/* delay 001c7a84 */ sb(ea(4,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(5));checkReturn(target,incoming);return;}
}
static void body_00246ab8(void){
uint64_t incoming=cpu(31);
/* 00246ab8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00246abc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00246ac0: move s0,a0 */ set(16,cpu(4));
/* 00246ac4: addiu a0,s0,-0x10 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0xfffffff0)));
/* 00246ac8: slti v0,s0,0x10 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00246acc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246ad0: sll v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)<<4));
/* 00246ad4: bne v0,zero,0x00246b00 */ {int taken=(cpu(2)!=cpu(0));/* delay 00246ad8 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_00246b00;}}
/* 00246adc: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 00246ae0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 00246ae4: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00246ae8: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 00246aec: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00246af0: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 00246af4: b 0x00246b50 */ /* delay 00246af8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000a54)));goto L_00246b50;
L_00246b00:;
/* 00246b00: jal 0x002469a0 */ set(31,UINT64_C(0x00246b08));/* delay 00246b04 */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002469a0),UINT32_C(0x00246b00));
/* 00246b08: move a0,s0 */ set(4,cpu(16));
/* 00246b0c: jal 0x00246a40 */ set(31,UINT64_C(0x00246b14));/* delay 00246b10 */ set(17,cpu(2));body_00246a40();
/* 00246b14: move a1,v0 */ set(5,cpu(2));
/* 00246b18: beq a1,zero,0x00246b54 */ {int taken=(cpu(5)==cpu(0));/* delay 00246b1c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00246b54;}}
/* 00246b20: lhu v1,0x0(a1) */ set(3,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 00246b24: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 00246b28: andi v1,v1,0xffff */ set(3,cpu(3)&UINT32_C(0x0000ffff));
/* 00246b2c: beq v1,zero,0x00246b54 */ {int taken=(cpu(3)==cpu(0));/* delay 00246b30 */ set(2,cpu(0));if(taken){goto L_00246b54;}}
/* 00246b34: move a0,s1 */ set(4,cpu(17));
/* 00246b38: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246b3c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00246b40: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00246b44: j 0x002469c0 */ /* delay 00246b48 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002469c0();return;
L_00246b50:;
/* 00246b50: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00246b54:;
/* 00246b54: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246b58: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00246b5c: jr ra */ {uint64_t target=cpu(31);/* delay 00246b60 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002627c0(void){
uint64_t incoming=cpu(31);
/* 002627c0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002627c4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002627c8: move s0,a0 */ set(16,cpu(4));
/* 002627cc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002627d0: move s1,a2 */ set(17,cpu(6));
/* 002627d4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002627d8: move s2,a3 */ set(18,cpu(7));
/* 002627dc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002627e0: move s3,a1 */ set(19,cpu(5));
/* 002627e4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002627e8: move s4,t1 */ set(20,cpu(9));
/* 002627ec: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002627f0: move s5,t2 */ set(21,cpu(10));
/* 002627f4: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002627f8: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002627fc: jal 0x0025e8e0 */ set(31,UINT64_C(0x00262804));/* delay 00262800 */ set(22,cpu(8));body_0025e8e0();
/* 00262804: move a3,v0 */ set(7,cpu(2));
/* 00262808: lw a1,0x8(a3) */ lw(5,ea(7,(int32_t)UINT32_C(0x00000008)));
/* 0026280c: beq a1,zero,0x0026287c */ {int taken=(cpu(5)==cpu(0));/* delay 00262810 */ set(4,cpu(7));if(taken){goto L_0026287c;}}
/* 00262814: li t0,0x10 */ set(8,sx(UINT32_C(0x00000010)));
/* 00262818: lb v0,0x4(a1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000004))));
/* 0026281c: nop  */ 
L_00262820:;
/* 00262820: bne v0,t0,0x0026286c */ {int taken=(cpu(2)!=cpu(8));/* delay 00262824 */ lw(6,ea(5,(int32_t)UINT32_C(0x0000000c)));if(taken){goto L_0026286c;}}
/* 00262828: lw v0,0x8(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 0026282c: bnel v0,s1,0x00262870 */ {int taken=(cpu(2)!=cpu(17));if(taken){/* delay 00262830 */ set(5,cpu(6));goto L_00262870;}}
/* 00262834: lw v0,0x14(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000014)));
/* 00262838: bnel v0,s2,0x00262870 */ {int taken=(cpu(2)!=cpu(18));if(taken){/* delay 0026283c */ set(5,cpu(6));goto L_00262870;}}
/* 00262840: lh v0,0x2(a1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000002))));
/* 00262844: lh v1,0x0(a1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 00262848: lhu a0,0x0(a1) */ set(4,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 0026284c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00262850: slt v1,s0,v1 */ set(3,(int64_t)cpu(16)<(int64_t)cpu(3));
/* 00262854: subu v0,s0,a0 */ set(2,sx((uint32_t)cpu(16)-(uint32_t)cpu(4)));
/* 00262858: beq v1,zero,0x0026286c */ {int taken=(cpu(3)==cpu(0));/* delay 0026285c */ set(4,sx((uint32_t)cpu(2)<<16));if(taken){goto L_0026286c;}}
/* 00262860: bgez a0,0x0026286c */ {int taken=((int64_t)cpu(4)>=0);/* delay 00262864 */ sh(ea(5,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));if(taken){goto L_0026286c;}}
/* 00262868: sh zero,0x2(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(0));
L_0026286c:;
/* 0026286c: move a1,a2 */ set(5,cpu(6));
L_00262870:;
/* 00262870: bnel a1,zero,0x00262820 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 00262874 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000004))));goto L_00262820;}}
/* 00262878: move a0,a3 */ set(4,cpu(7));
L_0026287c:;
/* 0026287c: move a3,s1 */ set(7,cpu(17));
/* 00262880: move a1,s0 */ set(5,cpu(16));
/* 00262884: jal 0x0025ea48 */ set(31,UINT64_C(0x0026288c));/* delay 00262888 */ set(6,cpu(19));body_0025ea48();
/* 0026288c: li v1,0x10 */ set(3,sx(UINT32_C(0x00000010)));
/* 00262890: move a1,v0 */ set(5,cpu(2));
/* 00262894: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262898: sw s4,0x20(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(20));
/* 0026289c: sw s2,0x14(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 002628a0: sw s5,0x28(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(21));
/* 002628a4: sw s6,0x2c(a1) */ sw(ea(5,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(22));
/* 002628a8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002628ac: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002628b0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002628b4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002628b8: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002628bc: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002628c0: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002628c4: sb v1,0x4(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 002628c8: jr ra */ {uint64_t target=cpu(31);/* delay 002628cc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002629e8(void){
uint64_t incoming=cpu(31);
/* 002629e8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002629ec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002629f0: move s0,a0 */ set(16,cpu(4));
/* 002629f4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002629f8: move s1,a1 */ set(17,cpu(5));
/* 002629fc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262a00: move s2,a3 */ set(18,cpu(7));
/* 00262a04: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262a08: move s3,t0 */ set(19,cpu(8));
/* 00262a0c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262a10: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262a14: jal 0x0025e8e0 */ set(31,UINT64_C(0x00262a1c));/* delay 00262a18 */ set(20,cpu(6));body_0025e8e0();
/* 00262a1c: move a0,v0 */ set(4,cpu(2));
/* 00262a20: move a1,s0 */ set(5,cpu(16));
/* 00262a24: move a3,s1 */ set(7,cpu(17));
/* 00262a28: jal 0x0025ea48 */ set(31,UINT64_C(0x00262a30));/* delay 00262a2c */ set(6,cpu(0));body_0025ea48();
/* 00262a30: li a0,0x11 */ set(4,sx(UINT32_C(0x00000011)));
/* 00262a34: move v1,v0 */ set(3,cpu(2));
/* 00262a38: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262a3c: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00262a40: sw s4,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(20));
/* 00262a44: sw s3,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(19));
/* 00262a48: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262a4c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262a50: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262a54: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262a58: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262a5c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262a60: jr ra */ {uint64_t target=cpu(31);/* delay 00262a64 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002642e0(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 002642e0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002642e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002642e8: move s0,a0 */ set(16,cpu(4));
/* 002642ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002642f0: move s1,a1 */ set(17,cpu(5));
/* 002642f4: swc1 f20,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);
/* 002642f8: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002642fc: jal 0x002469a0 */ set(31,UINT64_C(0x00264304));/* delay 00264300 */ f[20]=f[12];nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002469a0),UINT32_C(0x002642fc));
/* 00264304: move v1,v0 */ set(3,cpu(2));
/* 00264308: move a0,s0 */ set(4,cpu(16));
/* 0026430c: lw v0,0x60(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000060)));
/* 00264310: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 00264314: beq v0,zero,0x00264328 */ {int taken=(cpu(2)==cpu(0));/* delay 00264318 */ set(5,cpu(17));if(taken){goto L_00264328;}}
/* 0026431c: b 0x0026432c */ /* delay 00264320 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x0000001a))));goto L_0026432c;
L_00264328:;
/* 00264328: lh v0,0x18(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000018))));
L_0026432c:;
/* 0026432c: mtc1 v0,f12 */ f[12]=(uint32_t)cpu(2);
/* 00264330: cvt.s.W f12,f12 */ f[12]=EE_FPU_CVT_S_W(f[12]);
/* 00264334: nop  */ 
/* 00264338: nop  */ 
/* 0026433c: div.S f12,f20,f12 */ f[12]=EE_FPU_DIV_S(f[20],f[12]);
/* 00264340: jal 0x00262a68 */ set(31,UINT64_C(0x00264348));/* delay 00264344 */ body_00262a68();
/* 00264348: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0026434c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00264350: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00264354: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00264358: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026435c: jr ra */ {uint64_t target=cpu(31);/* delay 00264360 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00264368(void){
uint64_t incoming=cpu(31);
/* 00264368: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0026436c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00264370: move s0,a2 */ set(16,cpu(6));
/* 00264374: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00264378: move s1,a0 */ set(17,cpu(4));
/* 0026437c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00264380: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00264384: jal 0x002469a0 */ set(31,UINT64_C(0x0026438c));/* delay 00264388 */ set(18,cpu(5));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002469a0),UINT32_C(0x00264384));
/* 0026438c: lh t1,0x7a(v0) */ set(9,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x0000007a))));
/* 00264390: move t4,zero */ set(12,cpu(0));
/* 00264394: lhu t8,0x78(v0) */ set(24,half(ea(2,(int32_t)UINT32_C(0x00000078))));
/* 00264398: move t3,zero */ set(11,cpu(0));
/* 0026439c: lh t0,0x78(v0) */ set(8,(uint64_t)(int64_t)(int16_t)half(ea(2,(int32_t)UINT32_C(0x00000078))));
/* 002643a0: move a2,zero */ set(6,cpu(0));
/* 002643a4: lhu t7,0x7a(v0) */ set(15,half(ea(2,(int32_t)UINT32_C(0x0000007a))));
/* 002643a8: move a3,zero */ set(7,cpu(0));
/* 002643ac: move t5,zero */ set(13,cpu(0));
/* 002643b0: sltiu t6,s0,0x12 */ set(14,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000012));
/* 002643b4: sltiu a1,t0,0x1 */ set(5,cpu(8)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_002643b8:;
/* 002643b8: beq t6,zero,0x00264468 */ {int taken=(cpu(14)==cpu(0));/* delay 002643bc */ set(4,(int64_t)cpu(8)<(int64_t)cpu(9));if(taken){goto L_00264468;}}
/* 002643c0: sll v0,s0,0x2 */ set(2,sx((uint32_t)cpu(16)<<2));
/* 002643c4: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 002643c8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002643cc: lw v1,0x4940(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004940)));
/* 002643d0: jr v1 */ {uint64_t target=cpu(3);/* delay 002643d4 */ switch((uint32_t)target){case UINT32_C(0x002643d8):goto L_002643d8;case UINT32_C(0x002643e8):goto L_002643e8;case UINT32_C(0x002643f8):goto L_002643f8;case UINT32_C(0x00264408):goto L_00264408;case UINT32_C(0x00264440):goto L_00264440;case UINT32_C(0x00264450):goto L_00264450;case UINT32_C(0x00264458):goto L_00264458;case UINT32_C(0x00264460):goto L_00264460;default:abort();}}
L_002643d8:;
/* 002643d8: bne a0,zero,0x00264468 */ {int taken=(cpu(4)!=cpu(0));/* delay 002643dc */ set(11,sx(UINT32_C(0xffffffff)));if(taken){goto L_00264468;}}
/* 002643e0: b 0x00264468 */ /* delay 002643e4 */ set(12,sx(UINT32_C(0xffffffff)));goto L_00264468;
L_002643e8:;
/* 002643e8: beql a0,zero,0x00264468 */ {int taken=(cpu(4)==cpu(0));if(taken){/* delay 002643ec */ set(12,sx(UINT32_C(0xffffffff)));goto L_00264468;}}
/* 002643f0: b 0x00264468 */ /* delay 002643f4 */ set(11,sx(UINT32_C(0xffffffff)));goto L_00264468;
L_002643f8:;
/* 002643f8: beql a1,zero,0x00264468 */ {int taken=(cpu(5)==cpu(0));if(taken){/* delay 002643fc */ set(12,sx(UINT32_C(0xffffffff)));goto L_00264468;}}
/* 00264400: b 0x00264468 */ /* delay 00264404 */ set(11,sx(UINT32_C(0xffffffff)));goto L_00264468;
L_00264408:;
/* 00264408: beq a0,zero,0x00264430 */ {int taken=(cpu(4)==cpu(0));/* delay 0026440c */ set(2,sx((uint32_t)cpu(9)+UINT32_C(0xfffffffe)));if(taken){goto L_00264430;}}
/* 00264410: slt v0,v0,t0 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(8));
/* 00264414: beq v0,zero,0x00264468 */ {int taken=(cpu(2)==cpu(0));/* delay 00264418 */ set(11,sx(UINT32_C(0xfffffffe)));if(taken){goto L_00264468;}}
/* 0026441c: subu v0,t0,t1 */ set(2,sx((uint32_t)cpu(8)-(uint32_t)cpu(9)));
/* 00264420: addiu v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 00264424: b 0x00264468 */ /* delay 00264428 */ set(12,sx((uint32_t)cpu(0)-(uint32_t)cpu(2)));goto L_00264468;
L_00264430:;
/* 00264430: li t3,-0x2 */ set(11,sx(UINT32_C(0xfffffffe)));
/* 00264434: b 0x00264468 */ /* delay 00264438 */ set(12,sx(UINT32_C(0xfffffffe)));goto L_00264468;
L_00264440:;
/* 00264440: li t3,-0xa */ set(11,sx(UINT32_C(0xfffffff6)));
/* 00264444: b 0x00264468 */ /* delay 00264448 */ set(12,sx(UINT32_C(0xfffffff6)));goto L_00264468;
L_00264450:;
/* 00264450: b 0x00264464 */ /* delay 00264454 */ set(11,sx(UINT32_C(0x00000002)));goto L_00264464;
L_00264458:;
/* 00264458: b 0x00264464 */ /* delay 0026445c */ set(11,sx(UINT32_C(0x00000004)));goto L_00264464;
L_00264460:;
/* 00264460: li t3,0x3 */ set(11,sx(UINT32_C(0x00000003)));
L_00264464:;
/* 00264464: move t4,zero */ set(12,cpu(0));
L_00264468:;
/* 00264468: addu t0,t0,t4 */ set(8,sx((uint32_t)cpu(8)+(uint32_t)cpu(12)));
/* 0026446c: addu t1,t1,t3 */ set(9,sx((uint32_t)cpu(9)+(uint32_t)cpu(11)));
/* 00264470: sll v0,t8,0x10 */ set(2,sx((uint32_t)cpu(24)<<16));
/* 00264474: slti v1,t0,0x0 */ set(3,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00264478: sra t2,v0,0x10 */ set(10,sx((uint32_t)((int32_t)cpu(2)>>16)));
/* 0026447c: slti a0,t1,0x0 */ set(4,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 00264480: addu a2,a2,t4 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(12)));
/* 00264484: movn t0,zero,v1 */ if(cpu(3)!=0){set(8,cpu(0));}
/* 00264488: movn t1,zero,a0 */ if(cpu(4)!=0){set(9,cpu(0));}
/* 0026448c: li a0,0x7 */ set(4,sx(UINT32_C(0x00000007)));
/* 00264490: addu v1,t2,a2 */ set(3,sx((uint32_t)cpu(10)+(uint32_t)cpu(6)));
/* 00264494: slti a1,t0,0x8 */ set(5,(int64_t)cpu(8)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 00264498: slti v0,t1,0x8 */ set(2,(int64_t)cpu(9)<(int64_t)(int32_t)UINT32_C(0x00000008));
/* 0026449c: slti v1,v1,0x9 */ set(3,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 002644a0: movz t1,a0,v0 */ if(cpu(2)==0){set(9,cpu(4));}
/* 002644a4: movz t0,a0,a1 */ if(cpu(5)==0){set(8,cpu(4));}
/* 002644a8: bne v1,zero,0x002644b8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002644ac */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(11)));if(taken){goto L_002644b8;}}
/* 002644b0: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002644b4: subu a2,v0,t2 */ set(6,sx((uint32_t)cpu(2)-(uint32_t)cpu(10)));
L_002644b8:;
/* 002644b8: sll v1,t7,0x10 */ set(3,sx((uint32_t)cpu(15)<<16));
/* 002644bc: sra v1,v1,0x10 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 002644c0: addu v0,v1,a3 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(7)));
/* 002644c4: slti v0,v0,0x9 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000009));
/* 002644c8: bne v0,zero,0x002644d8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002644cc */ set(13,sx((uint32_t)cpu(13)+UINT32_C(0x00000001)));if(taken){goto L_002644d8;}}
/* 002644d0: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 002644d4: subu a3,v0,v1 */ set(7,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
L_002644d8:;
/* 002644d8: blez t5,0x002643b8 */ {int taken=((int64_t)cpu(13)<=0);/* delay 002644dc */ set(5,cpu(8)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));if(taken){goto L_002643b8;}}
/* 002644e0: move a0,s1 */ set(4,cpu(17));
/* 002644e4: jal 0x00262ac8 */ set(31,UINT64_C(0x002644ec));/* delay 002644e8 */ set(5,cpu(18));body_00262ac8();
/* 002644ec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002644f0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002644f4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002644f8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002644fc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00264500: jr ra */ {uint64_t target=cpu(31);/* delay 00264504 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00267788(void){
uint64_t incoming=cpu(31);
/* 00267788: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026778c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267790: jal 0x00246ab8 */ set(31,UINT64_C(0x00267798));/* delay 00267794 */ body_00246ab8();
/* 00267798: move v1,v0 */ set(3,cpu(2));
/* 0026779c: beq v1,zero,0x002677ac */ {int taken=(cpu(3)==cpu(0));/* delay 002677a0 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002677ac;}}
/* 002677a4: lhu v0,0xe(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000e))));
/* 002677a8: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
L_002677ac:;
/* 002677ac: jr ra */ {uint64_t target=cpu(31);/* delay 002677b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002677b8(void){
uint64_t incoming=cpu(31);
/* 002677b8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002677bc: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002677c0: jal 0x00246ab8 */ set(31,UINT64_C(0x002677c8));/* delay 002677c4 */ body_00246ab8();
/* 002677c8: move v1,v0 */ set(3,cpu(2));
/* 002677cc: beq v1,zero,0x002677e0 */ {int taken=(cpu(3)==cpu(0));/* delay 002677d0 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002677e0;}}
/* 002677d4: lhu v0,0xe(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000e))));
/* 002677d8: andi v0,v0,0x8000 */ set(2,cpu(2)&UINT32_C(0x00008000));
/* 002677dc: sltu v0,zero,v0 */ set(2,cpu(0)<cpu(2));
L_002677e0:;
/* 002677e0: jr ra */ {uint64_t target=cpu(31);/* delay 002677e4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_0026a468(void){
uint64_t incoming=cpu(31);
/* 0026a468: jr ra */ {uint64_t target=cpu(31);/* delay 0026a46c */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000004));checkReturn(target,incoming);return;}
}
static void body_002a9688(void){
uint64_t incoming=cpu(31);
/* 002a9688: lhu v1,0xe(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x0000000e))));
/* 002a968c: lw v0,0x8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 002a9690: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002a9694: jr ra */ {uint64_t target=cpu(31);/* delay 002a9698 */ sh(ea(4,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(3));checkReturn(target,incoming);return;}
}
static void body_001c8730(void){
uint64_t incoming=cpu(31);
/* 001c8730: lw v0,-0x4d64(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb29c)));
/* 001c8734: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001c8738: lw v1,0x4(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001c873c: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 001c8740: sb a1,0x1d(a0) */ sb(ea(4,(int32_t)UINT32_C(0x0000001d)),(uint8_t)cpu(5));
/* 001c8744: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8748: sb a1,0x1c(a0) */ sb(ea(4,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(5));
/* 001c874c: jr ra */ {uint64_t target=cpu(31);/* delay 001c8750 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
static void body_001c96d8(void){
uint64_t incoming=cpu(31);
/* 001c96d8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c96dc: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c96e0: sll a2,a2,0x18 */ set(6,sx((uint32_t)cpu(6)<<24));
/* 001c96e4: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c96e8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c96ec: sra s3,a0,0x18 */ set(19,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c96f0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c96f4: sra a2,a2,0x18 */ set(6,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c96f8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c96fc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9700: bne a1,zero,0x001c9720 */ {int taken=(cpu(5)!=cpu(0));/* delay 001c9704 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_001c9720;}}
/* 001c9708: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c970c: sll v0,s3,0x1 */ set(2,sx((uint32_t)cpu(19)<<1));
/* 001c9710: move a1,zero */ set(5,cpu(0));
/* 001c9714: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c9718: b 0x001c973c */ /* delay 001c971c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x0000657c))));goto L_001c973c;
L_001c9720:;
/* 001c9720: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9724: sll v1,s3,0x1 */ set(3,sx((uint32_t)cpu(19)<<1));
/* 001c9728: addiu v0,v0,0xc */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x0000000c)));
/* 001c972c: addu a0,v1,v0 */ set(4,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c9730: move v1,a0 */ set(3,cpu(4));
/* 001c9734: lb v0,0x6571(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00006571))));
/* 001c9738: lb a1,0x6570(v1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x00006570))));
L_001c973c:;
/* 001c973c: move s0,a1 */ set(16,cpu(5));
/* 001c9740: addu v1,s0,v0 */ set(3,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001c9744: slt v0,s0,v1 */ set(2,(int64_t)cpu(16)<(int64_t)cpu(3));
/* 001c9748: beq v0,zero,0x001c978c */ {int taken=(cpu(2)==cpu(0));/* delay 001c974c */ if(taken){goto L_001c978c;}}
/* 001c9750: sll v0,s3,0x4 */ set(2,sx((uint32_t)cpu(19)<<4));
/* 001c9754: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c9758: subu s0,v1,s0 */ set(16,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 001c975c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c9760: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c9764: addiu at,at,-0x43b0 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffffbc50)));
/* 001c9768: addu v0,at,v0 */ set(2,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 001c976c: nop  */ 
L_001c9770:;
/* 001c9770: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 001c9774: sw zero,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
/* 001c9778: nop  */ 
/* 001c977c: nop  */ 
/* 001c9780: nop  */ 
/* 001c9784: bne s0,zero,0x001c9770 */ {int taken=(cpu(16)!=cpu(0));/* delay 001c9788 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));if(taken){goto L_001c9770;}}
L_001c978c:;
/* 001c978c: blezl a2,0x001c989c */ {int taken=((int64_t)cpu(6)<=0);if(taken){/* delay 001c9790 */ set(5,cpu(19));goto L_001c989c;}}
/* 001c9794: sll v0,s3,0x4 */ set(2,sx((uint32_t)cpu(19)<<4));
/* 001c9798: move s1,a3 */ set(17,cpu(7));
/* 001c979c: addu v0,a1,v0 */ set(2,sx((uint32_t)cpu(5)+(uint32_t)cpu(2)));
/* 001c97a0: move s0,a2 */ set(16,cpu(6));
/* 001c97a4: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c97a8: lui s2,0x57 */ set(18,sx(UINT32_C(0x00570000)));
/* 001c97ac: addiu s2,s2,-0x43b0 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffbc50)));
/* 001c97b0: addu s2,s2,v0 */ set(18,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001c97b4: nop  */ 
L_001c97b8:;
/* 001c97b8: jal 0x002a8af8 */ set(31,UINT64_C(0x001c97c0));/* delay 001c97bc */ set(4,sx(UINT32_C(0x00000120)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002a8af8),UINT32_C(0x001c97b8));
/* 001c97c0: move v1,s1 */ set(3,cpu(17));
/* 001c97c4: move a2,v0 */ set(6,cpu(2));
/* 001c97c8: or v0,s1,a2 */ set(2,cpu(17)|cpu(6));
/* 001c97cc: andi v0,v0,0x7 */ set(2,cpu(2)&UINT32_C(0x00000007));
/* 001c97d0: beq v0,zero,0x001c9838 */ {int taken=(cpu(2)==cpu(0));/* delay 001c97d4 */ set(4,cpu(6));if(taken){goto L_001c9838;}}
/* 001c97d8: addiu v0,s1,0x120 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000120)));
L_001c97dc:;
/* 001c97dc: ldl a1,0x7(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000007)),1);
/* 001c97e0: ldr a1,0x0(v1) */ loadPartial(5,ea(3,(int32_t)UINT32_C(0x00000000)),0);
/* 001c97e4: ldl a3,0xf(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x0000000f)),1);
/* 001c97e8: ldr a3,0x8(v1) */ loadPartial(7,ea(3,(int32_t)UINT32_C(0x00000008)),0);
/* 001c97ec: ldl t0,0x17(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x00000017)),1);
/* 001c97f0: ldr t0,0x10(v1) */ loadPartial(8,ea(3,(int32_t)UINT32_C(0x00000010)),0);
/* 001c97f4: ldl t1,0x1f(v1) */ loadPartial(9,ea(3,(int32_t)UINT32_C(0x0000001f)),1);
/* 001c97f8: ldr t1,0x18(v1) */ loadPartial(9,ea(3,(int32_t)UINT32_C(0x00000018)),0);
/* 001c97fc: sdl a1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),5,1);
/* 001c9800: sdr a1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),5,0);
/* 001c9804: sdl a3,0xf(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000000f)),7,1);
/* 001c9808: sdr a3,0x8(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000008)),7,0);
/* 001c980c: sdl t0,0x17(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000017)),8,1);
/* 001c9810: sdr t0,0x10(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000010)),8,0);
/* 001c9814: sdl t1,0x1f(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x0000001f)),9,1);
/* 001c9818: sdr t1,0x18(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000018)),9,0);
/* 001c981c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001c9820: nop  */ 
/* 001c9824: nop  */ 
/* 001c9828: bne v1,v0,0x001c97dc */ {int taken=(cpu(3)!=cpu(2));/* delay 001c982c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_001c97dc;}}
/* 001c9830: b 0x001c9874 */ /* delay 001c9834 */ set(4,sx(UINT32_C(0x00000018)));goto L_001c9874;
L_001c9838:;
/* 001c9838: addiu v0,s1,0x120 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000120)));
L_001c983c:;
/* 001c983c: ld a1,0x0(v1) */ restore(5,ea(3,(int32_t)UINT32_C(0x00000000)));
/* 001c9840: ld a3,0x8(v1) */ restore(7,ea(3,(int32_t)UINT32_C(0x00000008)));
/* 001c9844: ld t0,0x10(v1) */ restore(8,ea(3,(int32_t)UINT32_C(0x00000010)));
/* 001c9848: ld t1,0x18(v1) */ restore(9,ea(3,(int32_t)UINT32_C(0x00000018)));
/* 001c984c: sd a1,0x0(a0) */ save(5,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 001c9850: sd a3,0x8(a0) */ save(7,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 001c9854: sd t0,0x10(a0) */ save(8,ea(4,(int32_t)UINT32_C(0x00000010)));
/* 001c9858: sd t1,0x18(a0) */ save(9,ea(4,(int32_t)UINT32_C(0x00000018)));
/* 001c985c: addiu v1,v1,0x20 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
/* 001c9860: nop  */ 
/* 001c9864: nop  */ 
/* 001c9868: bne v1,v0,0x001c983c */ {int taken=(cpu(3)!=cpu(2));/* delay 001c986c */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000020)));if(taken){goto L_001c983c;}}
/* 001c9870: li a0,0x18 */ set(4,sx(UINT32_C(0x00000018)));
L_001c9874:;
/* 001c9874: li a1,0x18 */ set(5,sx(UINT32_C(0x00000018)));
/* 001c9878: li a3,0x1 */ set(7,sx(UINT32_C(0x00000001)));
/* 001c987c: jal 0x001c7408 */ set(31,UINT64_C(0x001c9884));/* delay 001c9880 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7408),UINT32_C(0x001c987c));
/* 001c9884: addiu s1,s1,0x120 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000120)));
/* 001c9888: sw v0,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001c988c: addiu s2,s2,0x4 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000004)));
/* 001c9890: bne s0,zero,0x001c97b8 */ {int taken=(cpu(16)!=cpu(0));/* delay 001c9894 */ sh(ea(2,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(19));if(taken){goto L_001c97b8;}}
/* 001c9898: move a1,s3 */ set(5,cpu(19));
L_001c989c:;
/* 001c989c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c98a0: lui a0,0x53 */ set(4,sx(UINT32_C(0x00530000)));
/* 001c98a4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c98a8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c98ac: addiu a0,a0,0x5998 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00005998)));
/* 001c98b0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c98b4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c98b8: j 0x002d4748 */ /* delay 001c98bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_002d4748();return;
}
static void body_001c98c0(void){
uint64_t incoming=cpu(31);
/* 001c98c0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c98c4: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c98c8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c98cc: sra s1,a0,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c98d0: sll v1,s1,0x2 */ set(3,sx((uint32_t)cpu(17)<<2));
/* 001c98d4: sll a2,a1,0x18 */ set(6,sx((uint32_t)cpu(5)<<24));
/* 001c98d8: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c98dc: lui s3,0x57 */ set(19,sx(UINT32_C(0x00570000)));
/* 001c98e0: addiu s3,s3,-0x42b0 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0xffffbd50)));
/* 001c98e4: addu s3,s3,v1 */ set(19,sx((uint32_t)cpu(19)+(uint32_t)cpu(3)));
/* 001c98e8: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c98ec: sra s5,a2,0x18 */ set(21,sx((uint32_t)((int32_t)cpu(6)>>24)));
/* 001c98f0: sll v0,s1,0x3 */ set(2,sx((uint32_t)cpu(17)<<3));
/* 001c98f4: lw a2,0x0(s3) */ lw(6,ea(19,(int32_t)UINT32_C(0x00000000)));
/* 001c98f8: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 001c98fc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9900: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9904: sll s4,v0,0x9 */ set(20,sx((uint32_t)cpu(2)<<9));
/* 001c9908: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c990c: move a1,zero */ set(5,cpu(0));
/* 001c9910: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9914: sll s2,s1,0x1 */ set(18,sx((uint32_t)cpu(17)<<1));
/* 001c9918: bne a2,zero,0x001c9970 */ {int taken=(cpu(6)!=cpu(0));/* delay 001c991c */ set(4,cpu(17));if(taken){goto L_001c9970;}}
/* 001c9920: lw a3,-0x5750(gp) */ lw(7,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9924: addu v0,s2,a3 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(7)));
/* 001c9928: addu a3,a3,s4 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(20)));
/* 001c992c: lb s0,0x657c(v0) */ set(16,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x0000657c))));
/* 001c9930: addiu a3,a3,0x1d7c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00001d7c)));
/* 001c9934: jal 0x001c96d8 */ set(31,UINT64_C(0x001c993c));/* delay 001c9938 */ set(6,cpu(16));body_001c96d8();
/* 001c993c: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9940: sll v0,s0,0x3 */ set(2,sx((uint32_t)cpu(16)<<3));
/* 001c9944: move a0,s1 */ set(4,cpu(17));
/* 001c9948: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c994c: addu a3,v1,s4 */ set(7,sx((uint32_t)cpu(3)+(uint32_t)cpu(20)));
/* 001c9950: sll v0,v0,0x5 */ set(2,sx((uint32_t)cpu(2)<<5));
/* 001c9954: addu v1,s2,v1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(3)));
/* 001c9958: addu a3,a3,v0 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(2)));
/* 001c995c: lb a2,0x657d(v1) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(3,(int32_t)UINT32_C(0x0000657d))));
/* 001c9960: addiu a3,a3,0x1d7c */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00001d7c)));
/* 001c9964: jal 0x001c96d8 */ set(31,UINT64_C(0x001c996c));/* delay 001c9968 */ set(5,sx(UINT32_C(0x00000001)));body_001c96d8();
/* 001c996c: lw a2,0x0(s3) */ lw(6,ea(19,(int32_t)UINT32_C(0x00000000)));
L_001c9970:;
/* 001c9970: bne s5,zero,0x001c9988 */ {int taken=(cpu(21)!=cpu(0));/* delay 001c9974 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));if(taken){goto L_001c9988;}}
/* 001c9978: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001c997c: b 0x001c9990 */ /* delay 001c9980 */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000657c))));goto L_001c9990;
L_001c9988:;
/* 001c9988: addu v0,s2,v0 */ set(2,sx((uint32_t)cpu(18)+(uint32_t)cpu(2)));
/* 001c998c: lbu v1,0x657d(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000657d))));
L_001c9990:;
/* 001c9990: addu v1,a2,v1 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(3)));
/* 001c9994: sw v1,0x0(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c9998: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c999c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c99a0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c99a4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c99a8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c99ac: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c99b0: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c99b4: jr ra */ {uint64_t target=cpu(31);/* delay 001c99b8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c9a98(void){
uint64_t incoming=cpu(31);
/* 001c9a98: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c9a9c: sll a1,a1,0x18 */ set(5,sx((uint32_t)cpu(5)<<24));
/* 001c9aa0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9aa4: sll s0,a0,0x18 */ set(16,sx((uint32_t)cpu(4)<<24));
/* 001c9aa8: sra a1,a1,0x18 */ set(5,sx((uint32_t)((int32_t)cpu(5)>>24)));
/* 001c9aac: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9ab0: sra s0,s0,0x14 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>20)));
/* 001c9ab4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9ab8: addu s0,s0,a1 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(5)));
/* 001c9abc: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9ac0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9ac4: sll v1,s0,0x1 */ set(3,sx((uint32_t)cpu(16)<<1));
/* 001c9ac8: addiu v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c9acc: sll s0,s0,0x2 */ set(16,sx((uint32_t)cpu(16)<<2));
/* 001c9ad0: addu a0,v1,v0 */ set(4,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c9ad4: move s2,a2 */ set(18,cpu(6));
/* 001c9ad8: move v1,a0 */ set(3,cpu(4));
/* 001c9adc: lbu s1,0x6580(a0) */ set(17,byte(ea(4,(int32_t)UINT32_C(0x00006580))));
/* 001c9ae0: lbu a1,0x6581(v1) */ set(5,byte(ea(3,(int32_t)UINT32_C(0x00006581))));
/* 001c9ae4: sll v0,s1,0x8 */ set(2,sx((uint32_t)cpu(17)<<8));
/* 001c9ae8: or s1,v0,a1 */ set(17,cpu(2)|cpu(5));
/* 001c9aec: move a0,s1 */ set(4,cpu(17));
/* 001c9af0: jal 0x001c6128 */ set(31,UINT64_C(0x001c9af8));/* delay 001c9af4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0xffffffe0)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c6128),UINT32_C(0x001c9af0));
/* 001c9af8: lui a0,0x57 */ set(4,sx(UINT32_C(0x00570000)));
/* 001c9afc: addu a0,a0,s0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(16)));
/* 001c9b00: lw a0,-0x43b0(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0xffffbc50)));
/* 001c9b04: jal 0x001c7288 */ set(31,UINT64_C(0x001c9b0c));/* delay 001c9b08 */ set(5,cpu(18));body_001c7288();
/* 001c9b0c: move a1,s1 */ set(5,cpu(17));
/* 001c9b10: move s2,v0 */ set(18,cpu(2));
/* 001c9b14: addiu v0,s1,0x20 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00000020)));
/* 001c9b18: lw a0,0x20(s2) */ lw(4,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 001c9b1c: move a2,zero */ set(6,cpu(0));
/* 001c9b20: jal 0x001c7088 */ set(31,UINT64_C(0x001c9b28));/* delay 001c9b24 */ sh(ea(4,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7088),UINT32_C(0x001c9b20));
/* 001c9b28: move a0,zero */ set(4,cpu(0));
/* 001c9b2c: jal 0x001c7080 */ set(31,UINT64_C(0x001c9b34));/* delay 001c9b30 */ set(5,cpu(17));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7080),UINT32_C(0x001c9b2c));
/* 001c9b34: lw v1,0x20(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 001c9b38: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9b3c: sw v0,0x8(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(2));
/* 001c9b40: move v0,s2 */ set(2,cpu(18));
/* 001c9b44: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9b48: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9b4c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9b50: jr ra */ {uint64_t target=cpu(31);/* delay 001c9b54 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c9b58(void){
uint64_t incoming=cpu(31);
/* 001c9b58: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c9b5c: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c9b60: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9b64: sra s1,a0,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c9b68: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9b6c: move s0,a1 */ set(16,cpu(5));
/* 001c9b70: move a0,s1 */ set(4,cpu(17));
/* 001c9b74: move a1,zero */ set(5,cpu(0));
/* 001c9b78: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9b7c: move s2,zero */ set(18,cpu(0));
/* 001c9b80: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9b84: move s3,zero */ set(19,cpu(0));
/* 001c9b88: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9b8c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9b90: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9b94: jal 0x001c98c0 */ set(31,UINT64_C(0x001c9b9c));/* delay 001c9b98 */ set(21,cpu(6));body_001c98c0();
/* 001c9b9c: sll v0,s1,0x1 */ set(2,sx((uint32_t)cpu(17)<<1));
/* 001c9ba0: lw v1,-0x5750(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9ba4: addiu a0,v0,0x6570 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00006570)));
/* 001c9ba8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001c9bac: lbu v0,0xc(v1) */ set(2,byte(ea(3,(int32_t)UINT32_C(0x0000000c))));
/* 001c9bb0: beq v0,zero,0x001c9c04 */ {int taken=(cpu(2)==cpu(0));/* delay 001c9bb4 */ set(2,cpu(16));if(taken){goto L_001c9c04;}}
/* 001c9bb8: move s4,a0 */ set(20,cpu(4));
/* 001c9bbc: move a2,s0 */ set(6,cpu(16));
L_001c9bc0:;
/* 001c9bc0: move a1,s2 */ set(5,cpu(18));
/* 001c9bc4: move a0,s1 */ set(4,cpu(17));
/* 001c9bc8: jal 0x001c9a98 */ set(31,UINT64_C(0x001c9bd0));/* delay 001c9bcc */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));body_001c9a98();
/* 001c9bd0: move s0,v0 */ set(16,cpu(2));
/* 001c9bd4: addiu v0,s2,0x1 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 001c9bd8: lw v1,0x20(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000020)));
/* 001c9bdc: sll v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)<<24));
/* 001c9be0: sra s2,v0,0x18 */ set(18,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 001c9be4: sb s5,0x14(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(21));
/* 001c9be8: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9bec: addu v0,v0,s4 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(20)));
/* 001c9bf0: lbu v1,0xc(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 001c9bf4: slt v1,s3,v1 */ set(3,(int64_t)cpu(19)<(int64_t)cpu(3));
/* 001c9bf8: bne v1,zero,0x001c9bc0 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c9bfc */ set(6,cpu(16));if(taken){goto L_001c9bc0;}}
/* 001c9c00: move v0,s0 */ set(2,cpu(16));
L_001c9c04:;
/* 001c9c04: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9c08: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9c0c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9c10: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9c14: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9c18: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9c1c: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9c20: jr ra */ {uint64_t target=cpu(31);/* delay 001c9c24 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c9c28(void){
uint64_t incoming=cpu(31);
/* 001c9c28: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c9c2c: sll a0,a0,0x18 */ set(4,sx((uint32_t)cpu(4)<<24));
/* 001c9c30: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9c34: sra s4,a0,0x18 */ set(20,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c9c38: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9c3c: move a0,s4 */ set(4,cpu(20));
/* 001c9c40: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9c44: sll s0,s4,0x1 */ set(16,sx((uint32_t)cpu(20)<<1));
/* 001c9c48: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9c4c: move s1,a1 */ set(17,cpu(5));
/* 001c9c50: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9c54: move s3,zero */ set(19,cpu(0));
/* 001c9c58: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9c5c: move s5,a2 */ set(21,cpu(6));
/* 001c9c60: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9c64: addu v0,s0,v0 */ set(2,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 001c9c68: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9c6c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 001c9c70: addiu s0,s0,0x6571 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00006571)));
/* 001c9c74: jal 0x001c98c0 */ set(31,UINT64_C(0x001c9c7c));/* delay 001c9c78 */ set(18,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x0000657c))));body_001c98c0();
/* 001c9c7c: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9c80: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c9c84: lbu v1,0xc(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 001c9c88: beq v1,zero,0x001c9cdc */ {int taken=(cpu(3)==cpu(0));/* delay 001c9c8c */ set(2,cpu(17));if(taken){goto L_001c9cdc;}}
/* 001c9c90: move a2,s1 */ set(6,cpu(17));
/* 001c9c94: nop  */ 
L_001c9c98:;
/* 001c9c98: move a1,s2 */ set(5,cpu(18));
/* 001c9c9c: move a0,s4 */ set(4,cpu(20));
/* 001c9ca0: jal 0x001c9a98 */ set(31,UINT64_C(0x001c9ca8));/* delay 001c9ca4 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));body_001c9a98();
/* 001c9ca8: move s1,v0 */ set(17,cpu(2));
/* 001c9cac: addiu v0,s2,0x1 */ set(2,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));
/* 001c9cb0: lw v1,0x20(s1) */ lw(3,ea(17,(int32_t)UINT32_C(0x00000020)));
/* 001c9cb4: sll v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)<<24));
/* 001c9cb8: sra s2,v0,0x18 */ set(18,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 001c9cbc: sb s5,0x14(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(21));
/* 001c9cc0: lw v0,-0x5750(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001c9cc4: addu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(16)));
/* 001c9cc8: lbu v1,0xc(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x0000000c))));
/* 001c9ccc: slt v1,s3,v1 */ set(3,(int64_t)cpu(19)<(int64_t)cpu(3));
/* 001c9cd0: bne v1,zero,0x001c9c98 */ {int taken=(cpu(3)!=cpu(0));/* delay 001c9cd4 */ set(6,cpu(17));if(taken){goto L_001c9c98;}}
/* 001c9cd8: move v0,s1 */ set(2,cpu(17));
L_001c9cdc:;
/* 001c9cdc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9ce0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9ce4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9ce8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c9cec: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c9cf0: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c9cf4: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9cf8: jr ra */ {uint64_t target=cpu(31);/* delay 001c9cfc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001cf320(void){
uint64_t incoming=cpu(31);
/* 001cf320: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001cf324: sll a1,a1,0x2 */ set(5,sx((uint32_t)cpu(5)<<2));
/* 001cf328: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf32c: addiu s1,a1,0x80 */ set(17,sx((uint32_t)cpu(5)+UINT32_C(0x00000080)));
/* 001cf330: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cf334: addiu s2,a0,0xc4 */ set(18,sx((uint32_t)cpu(4)+UINT32_C(0x000000c4)));
/* 001cf338: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cf33c: move s3,a3 */ set(19,cpu(7));
/* 001cf340: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cf344: addu s4,s2,a1 */ set(20,sx((uint32_t)cpu(18)+(uint32_t)cpu(5)));
/* 001cf348: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001cf34c: move s5,a2 */ set(21,cpu(6));
/* 001cf350: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf354: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001cf358: lw v0,0x0(s4) */ lw(2,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 001cf35c: beq v0,zero,0x001cf370 */ {int taken=(cpu(2)==cpu(0));/* delay 001cf360 */ set(4,sx((uint32_t)cpu(18)+(uint32_t)cpu(17)));if(taken){goto L_001cf370;}}
/* 001cf364: jal 0x002a9558 */ set(31,UINT64_C(0x001cf36c));/* delay 001cf368 */ lw(4,ea(4,(int32_t)UINT32_C(0x00000000)));body_002a9558();
/* 001cf36c: sw zero,0x0(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(0));
L_001cf370:;
/* 001cf370: bgtz s3,0x001cf3d8 */ {int taken=((int64_t)cpu(19)>0);/* delay 001cf374 */ set(3,sx((uint32_t)cpu(19)+UINT32_C(0x00000005)));if(taken){goto L_001cf3d8;}}
/* 001cf378: jal 0x002d5d0c */ set(31,UINT64_C(0x001cf380));/* delay 001cf37c */ set(4,cpu(21));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d5d0c),UINT32_C(0x001cf378));
/* 001cf380: li v1,-0x4 */ set(3,sx(UINT32_C(0xfffffffc)));
/* 001cf384: addiu v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001cf388: and s0,v0,v1 */ set(16,cpu(2)&cpu(3));
/* 001cf38c: jal 0x002a9038 */ set(31,UINT64_C(0x001cf394));/* delay 001cf390 */ set(4,cpu(16));body_002a9038();
/* 001cf394: addu v1,s2,s1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(17)));
/* 001cf398: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001cf39c: jal 0x002a9688 */ set(31,UINT64_C(0x001cf3a4));/* delay 001cf3a0 */ set(4,cpu(2));body_002a9688();
/* 001cf3a4: move a1,s5 */ set(5,cpu(21));
/* 001cf3a8: sw v0,0x0(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001cf3ac: move a2,s0 */ set(6,cpu(16));
/* 001cf3b0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf3b4: move a0,v0 */ set(4,cpu(2));
/* 001cf3b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf3bc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cf3c0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cf3c4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cf3c8: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001cf3cc: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001cf3d0: j 0x002d43a4 */ /* delay 001cf3d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d43a4),UINT32_C(0x001cf3d0));return;
L_001cf3d8:;
/* 001cf3d8: li v0,-0x4 */ set(2,sx(UINT32_C(0xfffffffc)));
/* 001cf3dc: and s0,v1,v0 */ set(16,cpu(3)&cpu(2));
/* 001cf3e0: jal 0x002a9038 */ set(31,UINT64_C(0x001cf3e8));/* delay 001cf3e4 */ set(4,cpu(16));body_002a9038();
/* 001cf3e8: addu v1,s2,s1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(17)));
/* 001cf3ec: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001cf3f0: jal 0x002a9688 */ set(31,UINT64_C(0x001cf3f8));/* delay 001cf3f4 */ set(4,cpu(2));body_002a9688();
/* 001cf3f8: move a1,zero */ set(5,cpu(0));
/* 001cf3fc: sw v0,0x0(s4) */ sw(ea(20,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001cf400: move a2,s0 */ set(6,cpu(16));
/* 001cf404: jal 0x002d4558 */ set(31,UINT64_C(0x001cf40c));/* delay 001cf408 */ set(4,cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d4558),UINT32_C(0x001cf404));
/* 001cf40c: lw a0,0x0(s4) */ lw(4,ea(20,(int32_t)UINT32_C(0x00000000)));
/* 001cf410: move a1,s5 */ set(5,cpu(21));
/* 001cf414: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001cf418: move a2,s3 */ set(6,cpu(19));
/* 001cf41c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cf420: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf424: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf428: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cf42c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cf430: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001cf434: j 0x002d43a4 */ /* delay 001cf438 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d43a4),UINT32_C(0x001cf434));return;
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
static void body_00246a40(void){
uint64_t incoming=cpu(31);
/* 00246a40: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00246a44: move v0,zero */ set(2,cpu(0));
/* 00246a48: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00246a4c: move s0,a0 */ set(16,cpu(4));
/* 00246a50: slti v1,s0,0x10 */ set(3,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00246a54: beq v1,zero,0x00246aa8 */ {int taken=(cpu(3)==cpu(0));/* delay 00246a58 */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));if(taken){goto L_00246aa8;}}
/* 00246a5c: jal 0x002469a0 */ set(31,UINT64_C(0x00246a64));/* delay 00246a60 */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002469a0),UINT32_C(0x00246a5c));
/* 00246a64: sll v1,s0,0x4 */ set(3,sx((uint32_t)cpu(16)<<4));
/* 00246a68: move a3,v0 */ set(7,cpu(2));
/* 00246a6c: lw a1,0x0(a3) */ lw(5,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 00246a70: subu v1,v1,s0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(16)));
/* 00246a74: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 00246a78: addu v1,a1,v1 */ set(3,sx((uint32_t)cpu(5)+(uint32_t)cpu(3)));
/* 00246a7c: lw a0,0x78(v1) */ lw(4,ea(3,(int32_t)UINT32_C(0x00000078)));
/* 00246a80: andi a2,a0,0x40 */ set(6,cpu(4)&UINT32_C(0x00000040));
/* 00246a84: andi a0,a0,0x1 */ set(4,cpu(4)&UINT32_C(0x00000001));
/* 00246a88: beq a0,zero,0x00246aa8 */ {int taken=(cpu(4)==cpu(0));/* delay 00246a8c */ set(2,cpu(0));if(taken){goto L_00246aa8;}}
/* 00246a90: beq a2,zero,0x00246aac */ {int taken=(cpu(6)==cpu(0));/* delay 00246a94 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_00246aac;}}
/* 00246a98: lh v0,0x90(v1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000090))));
/* 00246a9c: lw v1,0x10(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000010)));
/* 00246aa0: sll v0,v0,0x7 */ set(2,sx((uint32_t)cpu(2)<<7));
/* 00246aa4: addu v0,v1,v0 */ set(2,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
L_00246aa8:;
/* 00246aa8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00246aac:;
/* 00246aac: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00246ab0: jr ra */ {uint64_t target=cpu(31);/* delay 00246ab4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_00246b68(void){
uint64_t incoming=cpu(31);
/* 00246b68: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00246b6c: move a0,zero */ set(4,cpu(0));
/* 00246b70: move a1,zero */ set(5,cpu(0));
/* 00246b74: li a2,0x1 */ set(6,sx(UINT32_C(0x00000001)));
/* 00246b78: addiu v1,v0,0x78 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000078)));
/* 00246b7c: lw v0,0x0(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));
L_00246b80:;
/* 00246b80: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 00246b84: beq v0,zero,0x00246b94 */ {int taken=(cpu(2)==cpu(0));/* delay 00246b88 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000f0)));if(taken){goto L_00246b94;}}
/* 00246b8c: sllv v0,a2,a0 */ set(2,sx((uint32_t)((uint32_t)cpu(6)<<((uint32_t)cpu(4)&31u))));
/* 00246b90: or a1,a1,v0 */ set(5,cpu(5)|cpu(2));
L_00246b94:;
/* 00246b94: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00246b98: slti v0,a0,0x10 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00246b9c: bnel v0,zero,0x00246b80 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00246ba0 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_00246b80;}}
/* 00246ba4: jr ra */ {uint64_t target=cpu(31);/* delay 00246ba8 */ set(2,cpu(5));checkReturn(target,incoming);return;}
}
static void body_00258de8(void){
uint64_t incoming=cpu(31);
/* 00258de8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00258dec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00258df0: move s0,zero */ set(16,cpu(0));
/* 00258df4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00258df8: move s1,zero */ set(17,cpu(0));
/* 00258dfc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00258e00: move s2,t1 */ set(18,cpu(9));
/* 00258e04: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00258e08: move s3,zero */ set(19,cpu(0));
/* 00258e0c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00258e10: move s4,a2 */ set(20,cpu(6));
/* 00258e14: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00258e18: move s5,a3 */ set(21,cpu(7));
/* 00258e1c: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00258e20: move s6,t0 */ set(22,cpu(8));
/* 00258e24: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00258e28: lh v1,0x6a(a1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x0000006a))));
/* 00258e2c: sltiu v0,v1,0x7 */ set(2,cpu(3)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000007));
/* 00258e30: beq v0,zero,0x00258fd8 */ {int taken=(cpu(2)==cpu(0));/* delay 00258e34 */ set(6,half(ea(5,(int32_t)UINT32_C(0x0000006a))));if(taken){goto L_00258fd8;}}
/* 00258e38: sll v0,v1,0x2 */ set(2,sx((uint32_t)cpu(3)<<2));
/* 00258e3c: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00258e40: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00258e44: lw v1,0x4150(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004150)));
/* 00258e48: jr v1 */ {uint64_t target=cpu(3);/* delay 00258e4c */ switch((uint32_t)target){case UINT32_C(0x00258e50):goto L_00258e50;case UINT32_C(0x00258f48):goto L_00258f48;case UINT32_C(0x00258f90):goto L_00258f90;case UINT32_C(0x00258fa0):goto L_00258fa0;case UINT32_C(0x00258fd8):goto L_00258fd8;default:abort();}}
L_00258e50:;
/* 00258e50: sll v0,a2,0x10 */ set(2,sx((uint32_t)cpu(6)<<16));
/* 00258e54: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00258e58: sra v0,v0,0x10 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>16)));
/* 00258e5c: bne v0,v1,0x00258e70 */ {int taken=(cpu(2)!=cpu(3));/* delay 00258e60 */ if(taken){goto L_00258e70;}}
/* 00258e64: b 0x00258e7c */ /* delay 00258e68 */ set(4,half(ea(5,(int32_t)UINT32_C(0x0000006c))));goto L_00258e7c;
L_00258e70:;
/* 00258e70: jal 0x00259c48 */ set(31,UINT64_C(0x00258e78));/* delay 00258e74 */ set(5,half(ea(5,(int32_t)UINT32_C(0x0000006c))));body_00259c48();
/* 00258e78: move a0,v0 */ set(4,cpu(2));
L_00258e7c:;
/* 00258e7c: sll a1,a0,0x4 */ set(5,sx((uint32_t)cpu(4)<<4));
/* 00258e80: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 00258e84: subu v0,a1,a0 */ set(2,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));
/* 00258e88: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00258e8c: lui a2,0x3d */ set(6,sx(UINT32_C(0x003d0000)));
/* 00258e90: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 00258e94: lbu a2,0x79a0(a2) */ set(6,byte(ea(6,(int32_t)UINT32_C(0x000079a0))));
/* 00258e98: beq a2,v1,0x00258ed0 */ {int taken=(cpu(6)==cpu(3));/* delay 00258e9c */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_00258ed0;}}
/* 00258ea0: beq v0,zero,0x00258eb8 */ {int taken=(cpu(2)==cpu(0));/* delay 00258ea4 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_00258eb8;}}
/* 00258ea8: beq a2,zero,0x00258ec8 */ {int taken=(cpu(6)==cpu(0));/* delay 00258eac */ set(3,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));if(taken){goto L_00258ec8;}}
/* 00258eb0: b 0x00258ee4 */ /* delay 00258eb4 */ set(2,sx(UINT32_C(0x003d0000)));goto L_00258ee4;
L_00258eb8:;
/* 00258eb8: beq a2,v0,0x00258ed8 */ {int taken=(cpu(6)==cpu(2));/* delay 00258ebc */ set(3,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));if(taken){goto L_00258ed8;}}
/* 00258ec0: b 0x00258ee4 */ /* delay 00258ec4 */ set(2,sx(UINT32_C(0x003d0000)));goto L_00258ee4;
L_00258ec8:;
/* 00258ec8: b 0x00258edc */ /* delay 00258ecc */ set(19,cpu(0));goto L_00258edc;
L_00258ed0:;
/* 00258ed0: b 0x00258edc */ /* delay 00258ed4 */ set(19,sx(UINT32_C(0x00000001)));goto L_00258edc;
L_00258ed8:;
/* 00258ed8: li s3,0x2 */ set(19,sx(UINT32_C(0x00000002)));
L_00258edc:;
/* 00258edc: subu v1,a1,a0 */ set(3,sx((uint32_t)cpu(5)-(uint32_t)cpu(4)));
/* 00258ee0: lui v0,0x3d */ set(2,sx(UINT32_C(0x003d0000)));
L_00258ee4:;
/* 00258ee4: addiu v0,v0,0x7998 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00007998)));
/* 00258ee8: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00258eec: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00258ef0: lbu a0,0x9(v1) */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000009))));
/* 00258ef4: andi v0,a0,0x1 */ set(2,cpu(4)&UINT32_C(0x00000001));
/* 00258ef8: andi v0,v0,0xff */ set(2,cpu(2)&UINT32_C(0x000000ff));
/* 00258efc: beq v0,zero,0x00258f0c */ {int taken=(cpu(2)==cpu(0));/* delay 00258f00 */ set(5,sx(UINT32_C(0x00000001)));if(taken){goto L_00258f0c;}}
/* 00258f04: li s1,0x2 */ set(17,sx(UINT32_C(0x00000002)));
/* 00258f08: movz s1,a1,s2 */ if(cpu(18)==0){set(17,cpu(5));}
L_00258f0c:;
/* 00258f0c: lbu v1,0xa(v1) */ set(3,byte(ea(3,(int32_t)UINT32_C(0x0000000a))));
/* 00258f10: andi v0,a0,0x2 */ set(2,cpu(4)&UINT32_C(0x00000002));
/* 00258f14: move s0,zero */ set(16,cpu(0));
/* 00258f18: or s1,v0,s1 */ set(17,cpu(2)|cpu(17));
/* 00258f1c: andi a0,v1,0x1 */ set(4,cpu(3)&UINT32_C(0x00000001));
/* 00258f20: andi v0,v1,0x2 */ set(2,cpu(3)&UINT32_C(0x00000002));
/* 00258f24: movn s0,a1,a0 */ if(cpu(4)!=0){set(16,cpu(5));}
/* 00258f28: andi a1,v1,0x8 */ set(5,cpu(3)&UINT32_C(0x00000008));
/* 00258f2c: or s0,v0,s0 */ set(16,cpu(2)|cpu(16));
/* 00258f30: andi v1,v1,0x4 */ set(3,cpu(3)&UINT32_C(0x00000004));
/* 00258f34: beq a1,zero,0x00258fd8 */ {int taken=(cpu(5)==cpu(0));/* delay 00258f38 */ set(16,cpu(3)|cpu(16));if(taken){goto L_00258fd8;}}
/* 00258f3c: b 0x00258fd8 */ /* delay 00258f40 */ set(16,cpu(16)|UINT32_C(0x00000008));goto L_00258fd8;
L_00258f48:;
/* 00258f48: beq s2,zero,0x00258f60 */ {int taken=(cpu(18)==cpu(0));/* delay 00258f4c */ set(19,cpu(0));if(taken){goto L_00258f60;}}
/* 00258f50: li s0,0x2 */ set(16,sx(UINT32_C(0x00000002)));
/* 00258f54: b 0x00258f68 */ /* delay 00258f58 */ set(17,sx(UINT32_C(0x00000001)));goto L_00258f68;
L_00258f60:;
/* 00258f60: move s0,zero */ set(16,cpu(0));
/* 00258f64: li s1,0x2 */ set(17,sx(UINT32_C(0x00000002)));
L_00258f68:;
/* 00258f68: move a0,a1 */ set(4,cpu(5));
/* 00258f6c: jal 0x0026a3d8 */ set(31,UINT64_C(0x00258f74));/* delay 00258f70 */ set(5,sx(UINT32_C(0x00000130)));body_0026a3d8();
/* 00258f74: beq v0,zero,0x00258fd8 */ {int taken=(cpu(2)==cpu(0));/* delay 00258f78 */ if(taken){goto L_00258fd8;}}
/* 00258f7c: beql s2,zero,0x00258fd8 */ {int taken=(cpu(18)==cpu(0));if(taken){/* delay 00258f80 */ set(19,sx(UINT32_C(0x00000001)));goto L_00258fd8;}}
/* 00258f84: b 0x00258fd8 */ /* delay 00258f88 */ goto L_00258fd8;
L_00258f90:;
/* 00258f90: move s3,zero */ set(19,cpu(0));
/* 00258f94: move s0,zero */ set(16,cpu(0));
/* 00258f98: b 0x00258fd8 */ /* delay 00258f9c */ set(17,sx(UINT32_C(0x00000002)));goto L_00258fd8;
L_00258fa0:;
/* 00258fa0: lw a0,0x0(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00258fa4: lw v0,0x60(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000060)));
/* 00258fa8: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 00258fac: bne v0,zero,0x00258fd8 */ {int taken=(cpu(2)!=cpu(0));/* delay 00258fb0 */ if(taken){goto L_00258fd8;}}
/* 00258fb4: lh v0,0x18(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000018))));
/* 00258fb8: slti v0,v0,0x4 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000004));
/* 00258fbc: bne v0,zero,0x00258fd0 */ {int taken=(cpu(2)!=cpu(0));/* delay 00258fc0 */ set(19,cpu(0));if(taken){goto L_00258fd0;}}
/* 00258fc4: b 0x00258fd4 */ /* delay 00258fc8 */ set(16,sx(UINT32_C(0x00000002)));goto L_00258fd4;
L_00258fd0:;
/* 00258fd0: li s0,0xc */ set(16,sx(UINT32_C(0x0000000c)));
L_00258fd4:;
/* 00258fd4: li s1,0x1 */ set(17,sx(UINT32_C(0x00000001)));
L_00258fd8:;
/* 00258fd8: bnel s4,zero,0x00258fe0 */ {int taken=(cpu(20)!=cpu(0));if(taken){/* delay 00258fdc */ sw(ea(20,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(19));goto L_00258fe0;}}
L_00258fe0:;
/* 00258fe0: bnel s5,zero,0x00258fe8 */ {int taken=(cpu(21)!=cpu(0));if(taken){/* delay 00258fe4 */ sw(ea(21,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));goto L_00258fe8;}}
L_00258fe8:;
/* 00258fe8: bnel s6,zero,0x00258ff0 */ {int taken=(cpu(22)!=cpu(0));if(taken){/* delay 00258fec */ sw(ea(22,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));goto L_00258ff0;}}
L_00258ff0:;
/* 00258ff0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00258ff4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00258ff8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00258ffc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00259000: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00259004: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00259008: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0025900c: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 00259010: jr ra */ {uint64_t target=cpu(31);/* delay 00259014 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_00259c48(void){
uint64_t incoming=cpu(31);
/* 00259c48: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00259c4c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259c50: move s0,a1 */ set(16,cpu(5));
/* 00259c54: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00259c58: move s1,a0 */ set(17,cpu(4));
/* 00259c5c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00259c60: jal 0x00245c90 */ set(31,UINT64_C(0x00259c68));/* delay 00259c64 */ set(4,cpu(16));body_00245c90();
/* 00259c68: move v1,v0 */ set(3,cpu(2));
/* 00259c6c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00259c70: beql s0,v0,0x00259c78 */ {int taken=(cpu(16)==cpu(2));if(taken){/* delay 00259c74 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000064)));goto L_00259c78;}}
L_00259c78:;
/* 00259c78: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259c7c: move v0,v1 */ set(2,cpu(3));
/* 00259c80: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00259c84: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00259c88: jr ra */ {uint64_t target=cpu(31);/* delay 00259c8c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_0025dc00(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
uint32_t condition=0;
/* 0025dc00: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 0025dc04: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025dc08: move s0,a0 */ set(16,cpu(4));
/* 0025dc0c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025dc10: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025dc14: move s2,zero */ set(18,cpu(0));
/* 0025dc18: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025dc1c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0025dc20: sll s4,s0,0x7 */ set(20,sx((uint32_t)cpu(16)<<7));
/* 0025dc24: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0025dc28: move s5,a3 */ set(21,cpu(7));
/* 0025dc2c: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0025dc30: move s6,a2 */ set(22,cpu(6));
/* 0025dc34: sd s7,0x38(sp) */ save(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0025dc38: sd ra,0x40(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0025dc3c: jal 0x0025d690 */ set(31,UINT64_C(0x0025dc44));/* delay 0025dc40 */ set(23,cpu(5));body_0025d690();
/* 0025dc44: move s1,v0 */ set(17,cpu(2));
/* 0025dc48: move s0,zero */ set(16,cpu(0));
/* 0025dc4c: sb zero,0x12(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000012)),(uint8_t)cpu(0));
/* 0025dc50: addiu s3,s1,0x4 */ set(19,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
/* 0025dc54: sb zero,0x13(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000013)),(uint8_t)cpu(0));
L_0025dc58:;
/* 0025dc58: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0025dc5c: li t2,-0x5 */ set(10,sx(UINT32_C(0xfffffffb)));
/* 0025dc60: li t3,-0x9 */ set(11,sx(UINT32_C(0xfffffff7)));
/* 0025dc64: move a1,s7 */ set(5,cpu(23));
/* 0025dc68: lw t1,0x0(v0) */ lw(9,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0025dc6c: move t0,s0 */ set(8,cpu(16));
/* 0025dc70: lw v1,0x10(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000010)));
/* 0025dc74: move a2,s6 */ set(6,cpu(22));
/* 0025dc78: addu t1,s2,t1 */ set(9,sx((uint32_t)cpu(18)+(uint32_t)cpu(9)));
/* 0025dc7c: move a3,s5 */ set(7,cpu(21));
/* 0025dc80: lw v0,0x78(t1) */ lw(2,ea(9,(int32_t)UINT32_C(0x00000078)));
/* 0025dc84: addu v1,s4,v1 */ set(3,sx((uint32_t)cpu(20)+(uint32_t)cpu(3)));
/* 0025dc88: lh a0,0x2(v1) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(3,(int32_t)UINT32_C(0x00000002))));
/* 0025dc8c: and v0,v0,t2 */ set(2,cpu(2)&cpu(10));
/* 0025dc90: and v0,v0,t3 */ set(2,cpu(2)&cpu(11));
/* 0025dc94: jal 0x0025da78 */ set(31,UINT64_C(0x0025dc9c));/* delay 0025dc98 */ sw(ea(9,(int32_t)UINT32_C(0x00000078)),(uint32_t)cpu(2));body_0025da78();
/* 0025dc9c: beq v0,zero,0x0025dd24 */ {int taken=(cpu(2)==cpu(0));/* delay 0025dca0 */ set(5,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000004));if(taken){goto L_0025dd24;}}
/* 0025dca4: lw a0,0x0(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0025dca8: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0025dcac: addu v1,s2,v1 */ set(3,sx((uint32_t)cpu(18)+(uint32_t)cpu(3)));
/* 0025dcb0: lw v0,0x78(v1) */ lw(2,ea(3,(int32_t)UINT32_C(0x00000078)));
/* 0025dcb4: ori v0,v0,0x4 */ set(2,cpu(2)|UINT32_C(0x00000004));
/* 0025dcb8: beq a1,zero,0x0025dcd8 */ {int taken=(cpu(5)==cpu(0));/* delay 0025dcbc */ sw(ea(3,(int32_t)UINT32_C(0x00000078)),(uint32_t)cpu(2));if(taken){goto L_0025dcd8;}}
/* 0025dcc0: lw v0,0x60(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000060)));
/* 0025dcc4: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 0025dcc8: beql v0,zero,0x0025dcf8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025dccc */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x00000012))));goto L_0025dcf8;}}
/* 0025dcd0: b 0x0025dd10 */ /* delay 0025dcd4 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x00000013))));goto L_0025dd10;
L_0025dcd8:;
/* 0025dcd8: slti v0,s0,0xe */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x0000000e));
/* 0025dcdc: beql v0,zero,0x0025dd28 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025dce0 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));goto L_0025dd28;}}
/* 0025dce4: lw v0,0x60(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000060)));
/* 0025dce8: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 0025dcec: beql v0,zero,0x0025dd10 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025dcf0 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x00000013))));goto L_0025dd10;}}
/* 0025dcf4: lb v0,0x12(s1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x00000012))));
L_0025dcf8:;
/* 0025dcf8: addu v0,v0,s3 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(19)));
/* 0025dcfc: sb s0,0x10(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000010)),(uint8_t)cpu(16));
/* 0025dd00: lbu v1,0x12(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000012))));
/* 0025dd04: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0025dd08: b 0x0025dd24 */ /* delay 0025dd0c */ sb(ea(17,(int32_t)UINT32_C(0x00000012)),(uint8_t)cpu(3));goto L_0025dd24;
L_0025dd10:;
/* 0025dd10: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 0025dd14: sb s0,0x20(v0) */ sb(ea(2,(int32_t)UINT32_C(0x00000020)),(uint8_t)cpu(16));
/* 0025dd18: lbu v1,0x13(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000013))));
/* 0025dd1c: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 0025dd20: sb v1,0x13(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000013)),(uint8_t)cpu(3));
L_0025dd24:;
/* 0025dd24: addiu s0,s0,0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
L_0025dd28:;
/* 0025dd28: slti v0,s0,0x10 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 0025dd2c: bne v0,zero,0x0025dc58 */ {int taken=(cpu(2)!=cpu(0));/* delay 0025dd30 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x000000f0)));if(taken){goto L_0025dc58;}}
/* 0025dd34: lbu t3,0x13(s1) */ set(11,byte(ea(17,(int32_t)UINT32_C(0x00000013))));
/* 0025dd38: move s0,zero */ set(16,cpu(0));
/* 0025dd3c: sll v0,t3,0x18 */ set(2,sx((uint32_t)cpu(11)<<24));
/* 0025dd40: sra v0,v0,0x18 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 0025dd44: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 0025dd48: blez v0,0x0025ddfc */ {int taken=((int64_t)cpu(2)<=0);/* delay 0025dd4c */ set(3,cpu(11));if(taken){goto L_0025ddfc;}}
L_0025dd50:;
/* 0025dd50: sll v0,v1,0x18 */ set(2,sx((uint32_t)cpu(3)<<24));
/* 0025dd54: addiu t4,s0,0x1 */ set(12,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
/* 0025dd58: sra v0,v0,0x18 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 0025dd5c: slt v0,t4,v0 */ set(2,(int64_t)cpu(12)<(int64_t)cpu(2));
/* 0025dd60: beq v0,zero,0x0025dde0 */ {int taken=(cpu(2)==cpu(0));/* delay 0025dd64 */ set(10,cpu(12));if(taken){goto L_0025dde0;}}
/* 0025dd68: addiu v0,s0,0x20 */ set(2,sx((uint32_t)cpu(16)+UINT32_C(0x00000020)));
/* 0025dd6c: addu v1,t4,s1 */ set(3,sx((uint32_t)cpu(12)+(uint32_t)cpu(17)));
/* 0025dd70: addu t0,s1,v0 */ set(8,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 0025dd74: addiu a3,v1,0x20 */ set(7,sx((uint32_t)cpu(3)+UINT32_C(0x00000020)));
L_0025dd78:;
/* 0025dd78: lb a0,0x0(a3) */ set(4,(uint64_t)(int64_t)(int8_t)byte(ea(7,(int32_t)UINT32_C(0x00000000))));
/* 0025dd7c: lb t1,0x0(t0) */ set(9,(uint64_t)(int64_t)(int8_t)byte(ea(8,(int32_t)UINT32_C(0x00000000))));
/* 0025dd80: lw a2,0x0(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 0025dd84: sll v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)<<4));
/* 0025dd88: sll v0,t1,0x4 */ set(2,sx((uint32_t)cpu(9)<<4));
/* 0025dd8c: subu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(4)));
/* 0025dd90: lw a1,0x0(a2) */ lw(5,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 0025dd94: subu v0,v0,t1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(9)));
/* 0025dd98: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 0025dd9c: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 0025dda0: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 0025dda4: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 0025dda8: lwc1 f1,0x0(v0) */ f[1]=word(ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0025ddac: lwc1 f0,0x0(v1) */ f[0]=word(ea(3,(int32_t)UINT32_C(0x00000000)));
/* 0025ddb0: c.lt.S f0,f1 */ condition=EE_FPU_COMPARE_S(f[0],f[1],1)!=0;
/* 0025ddb4: bc1f 0x0025ddc8 */ {int taken=(((nocturneBattlePanelRendererRemainingFcsr()>>23)&1u)==0);/* delay 0025ddb8 */ set(2,byte(ea(7,(int32_t)UINT32_C(0x00000000))));if(taken){goto L_0025ddc8;}}
/* 0025ddbc: sb v0,0x0(t0) */ sb(ea(8,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 0025ddc0: sb t1,0x0(a3) */ sb(ea(7,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(9));
/* 0025ddc4: lbu t3,0x13(s1) */ set(11,byte(ea(17,(int32_t)UINT32_C(0x00000013))));
L_0025ddc8:;
/* 0025ddc8: sll v0,t3,0x18 */ set(2,sx((uint32_t)cpu(11)<<24));
/* 0025ddcc: addiu t2,t2,0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000001)));
/* 0025ddd0: sra v0,v0,0x18 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 0025ddd4: slt v0,t2,v0 */ set(2,(int64_t)cpu(10)<(int64_t)cpu(2));
/* 0025ddd8: bne v0,zero,0x0025dd78 */ {int taken=(cpu(2)!=cpu(0));/* delay 0025dddc */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));if(taken){goto L_0025dd78;}}
L_0025dde0:;
/* 0025dde0: sll v0,t3,0x18 */ set(2,sx((uint32_t)cpu(11)<<24));
/* 0025dde4: move s0,t4 */ set(16,cpu(12));
/* 0025dde8: sra v0,v0,0x18 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 0025ddec: addiu v0,v0,-0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xffffffff)));
/* 0025ddf0: slt v0,s0,v0 */ set(2,(int64_t)cpu(16)<(int64_t)cpu(2));
/* 0025ddf4: bne v0,zero,0x0025dd50 */ {int taken=(cpu(2)!=cpu(0));/* delay 0025ddf8 */ set(3,cpu(11));if(taken){goto L_0025dd50;}}
L_0025ddfc:;
/* 0025ddfc: lb v0,0x12(s1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x00000012))));
/* 0025de00: sll v1,t3,0x18 */ set(3,sx((uint32_t)cpu(11)<<24));
/* 0025de04: sra v1,v1,0x18 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>24)));
/* 0025de08: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025de0c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0025de10: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025de14: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025de18: sltu v0,zero,v0 */ set(2,cpu(0)<cpu(2));
/* 0025de1c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025de20: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0025de24: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0025de28: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 0025de2c: ld s7,0x38(sp) */ restore(23,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0025de30: ld ra,0x40(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 0025de34: jr ra */ {uint64_t target=cpu(31);/* delay 0025de38 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_002645a8(void){
uint64_t incoming=cpu(31);
/* 002645a8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002645ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002645b0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002645b4: move s1,a2 */ set(17,cpu(6));
/* 002645b8: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002645bc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002645c0: move s3,a1 */ set(19,cpu(5));
/* 002645c4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002645c8: move s4,a0 */ set(20,cpu(4));
/* 002645cc: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002645d0: lh v0,0x92(s1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(17,(int32_t)UINT32_C(0x00000092))));
/* 002645d4: move a0,v0 */ set(4,cpu(2));
/* 002645d8: slti v0,v0,0x10 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 002645dc: jal 0x00267788 */ set(31,UINT64_C(0x002645e4));/* delay 002645e0 */ set(18,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));body_00267788();
/* 002645e4: move s0,v0 */ set(16,cpu(2));
/* 002645e8: beq s0,zero,0x00264604 */ {int taken=(cpu(16)==cpu(0));/* delay 002645ec */ set(4,cpu(20));if(taken){goto L_00264604;}}
/* 002645f0: move a1,s3 */ set(5,cpu(19));
/* 002645f4: move a2,s1 */ set(6,cpu(17));
/* 002645f8: li a3,0xfff */ set(7,sx(UINT32_C(0x00000fff)));
/* 002645fc: jal 0x00262b38 */ set(31,UINT64_C(0x00264604));/* delay 00264600 */ set(8,cpu(0));body_00262b38();
L_00264604:;
/* 00264604: bnel s2,zero,0x002646ec */ {int taken=(cpu(18)!=cpu(0));if(taken){/* delay 00264608 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002646ec;}}
/* 0026460c: li v0,0x20 */ set(2,sx(UINT32_C(0x00000020)));
/* 00264610: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 00264614 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000021));if(taken){goto L_002646c8;}}
/* 00264618: beq v0,zero,0x00264668 */ {int taken=(cpu(2)==cpu(0));/* delay 0026461c */ set(2,sx(UINT32_C(0x00000100)));if(taken){goto L_00264668;}}
/* 00264620: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 00264624: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 00264628 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));if(taken){goto L_002646c8;}}
/* 0026462c: beq v0,zero,0x00264650 */ {int taken=(cpu(2)==cpu(0));/* delay 00264630 */ set(2,sx(UINT32_C(0x00000008)));if(taken){goto L_00264650;}}
/* 00264634: sltiu v0,s0,0x3 */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000003));
/* 00264638: beql v0,zero,0x002646ec */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0026463c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002646ec;}}
/* 00264640: beq s0,zero,0x002646ec */ {int taken=(cpu(16)==cpu(0));/* delay 00264644 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002646ec;}}
/* 00264648: b 0x002646cc */ /* delay 0026464c */ set(4,cpu(20));goto L_002646cc;
L_00264650:;
/* 00264650: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 00264654 */ set(2,sx(UINT32_C(0x00000010)));if(taken){goto L_002646c8;}}
/* 00264658: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 0026465c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002646c8;}}
/* 00264660: b 0x002646f0 */ /* delay 00264664 */ set(2,sx(UINT32_C(0x00000001)));goto L_002646f0;
L_00264668:;
/* 00264668: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 0026466c */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000101));if(taken){goto L_002646c8;}}
/* 00264670: beq v0,zero,0x00264698 */ {int taken=(cpu(2)==cpu(0));/* delay 00264674 */ set(2,sx(UINT32_C(0x00000400)));if(taken){goto L_00264698;}}
/* 00264678: li v0,0x40 */ set(2,sx(UINT32_C(0x00000040)));
/* 0026467c: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 00264680 */ set(2,sx(UINT32_C(0x00000080)));if(taken){goto L_002646c8;}}
/* 00264684: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 00264688 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002646c8;}}
/* 0026468c: b 0x002646f0 */ /* delay 00264690 */ set(2,sx(UINT32_C(0x00000001)));goto L_002646f0;
L_00264698:;
/* 00264698: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 0026469c */ set(2,cpu(16)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000401));if(taken){goto L_002646c8;}}
/* 002646a0: beq v0,zero,0x002646c0 */ {int taken=(cpu(2)==cpu(0));/* delay 002646a4 */ set(2,sx(UINT32_C(0x00000800)));if(taken){goto L_002646c0;}}
/* 002646a8: li v0,0x200 */ set(2,sx(UINT32_C(0x00000200)));
/* 002646ac: beq s0,v0,0x002646c8 */ {int taken=(cpu(16)==cpu(2));/* delay 002646b0 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002646c8;}}
/* 002646b4: b 0x002646f0 */ /* delay 002646b8 */ set(2,sx(UINT32_C(0x00000001)));goto L_002646f0;
L_002646c0:;
/* 002646c0: bne s0,v0,0x002646ec */ {int taken=(cpu(16)!=cpu(2));/* delay 002646c4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002646ec;}}
L_002646c8:;
/* 002646c8: move a0,s4 */ set(4,cpu(20));
L_002646cc:;
/* 002646cc: move a1,s3 */ set(5,cpu(19));
/* 002646d0: jal 0x00262bb8 */ set(31,UINT64_C(0x002646d8));/* delay 002646d4 */ set(6,cpu(17));body_00262bb8();
/* 002646d8: move a0,s4 */ set(4,cpu(20));
/* 002646dc: move a1,s3 */ set(5,cpu(19));
/* 002646e0: jal 0x00262610 */ set(31,UINT64_C(0x002646e8));/* delay 002646e4 */ set(6,cpu(17));body_00262610();
/* 002646e8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002646ec:;
/* 002646ec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002646f0:;
/* 002646f0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002646f4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002646f8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002646fc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00264700: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00264704: jr ra */ {uint64_t target=cpu(31);/* delay 00264708 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
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
/* 002a8c24: jal 0x002e4070 */ set(31,UINT64_C(0x002a8c2c));/* delay 002a8c28 */ lw(17,ea(16,(int32_t)UINT32_C(0x0000000c)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e4070),UINT32_C(0x002a8c24));
/* 002a8c2c: lh a0,0x14(s0) */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(16,(int32_t)UINT32_C(0x00000014))));
/* 002a8c30: move s3,v0 */ set(19,cpu(2));
/* 002a8c34: addiu v0,a0,-0x1 */ set(2,sx((uint32_t)cpu(4)+UINT32_C(0xffffffff)));
/* 002a8c38: sll v1,v0,0x10 */ set(3,sx((uint32_t)cpu(2)<<16));
/* 002a8c3c: bne v1,zero,0x002a8ca8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002a8c40 */ sh(ea(16,(int32_t)UINT32_C(0x00000014)),(uint16_t)cpu(2));if(taken){goto L_002a8ca8;}}
/* 002a8c44: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 002a8c48: bne v0,s0,0x002a8c60 */ {int taken=(cpu(2)!=cpu(16));/* delay 002a8c4c */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));if(taken){goto L_002a8c60;}}
/* 002a8c50: jal 0x002a89c0 */ set(31,UINT64_C(0x002a8c58));/* delay 002a8c54 */ set(4,cpu(17));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002a89c0),UINT32_C(0x002a8c50));
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
/* 002a8cd4: jal 0x002e40b8 */ set(31,UINT64_C(0x002a8cdc));/* delay 002a8cd8 */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e40b8),UINT32_C(0x002a8cd4));
L_002a8cdc:;
/* 002a8cdc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002a8ce0:;
/* 002a8ce0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8ce4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a8ce8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a8cec: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a8cf0: jr ra */ {uint64_t target=cpu(31);/* delay 002a8cf4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002a9038(void){
uint64_t incoming=cpu(31);
/* 002a9038: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002a903c: addiu a0,a0,0x7f */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x0000007f)));
/* 002a9040: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9044: lui s0,0x57 */ set(16,sx(UINT32_C(0x00570000)));
/* 002a9048: li v0,-0x80 */ set(2,sx(UINT32_C(0xffffff80)));
/* 002a904c: addiu s0,s0,0x7f18 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00007f18)));
/* 002a9050: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9054: and s1,a0,v0 */ set(17,cpu(4)&cpu(2));
/* 002a9058: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a905c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a9060: li s3,0x2 */ set(19,sx(UINT32_C(0x00000002)));
/* 002a9064: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a9068: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002a906c: jal 0x002e4070 */ set(31,UINT64_C(0x002a9074));/* delay 002a9070 */ set(20,sx(UINT32_C(0x00000001)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e4070),UINT32_C(0x002a906c));
/* 002a9074: lw s0,0x4(s0) */ lw(16,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002a9078: move s2,v0 */ set(18,cpu(2));
/* 002a907c: nop  */ 
L_002a9080:;
/* 002a9080: lhu v0,0xc(s0) */ set(2,half(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 002a9084: beql v0,zero,0x002a90c0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002a9088 */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a90c0;}}
/* 002a908c: bnel v0,s3,0x002a9150 */ {int taken=(cpu(2)!=cpu(19));if(taken){/* delay 002a9090 */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a9150;}}
/* 002a9094: beql s2,zero,0x002a90a8 */ {int taken=(cpu(18)==cpu(0));if(taken){/* delay 002a9098 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6c0)));goto L_002a90a8;}}
/* 002a909c: jal 0x002e40b8 */ set(31,UINT64_C(0x002a90a4));/* delay 002a90a0 */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e40b8),UINT32_C(0x002a909c));
/* 002a90a4: lw v0,-0x2940(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd6c0)));
L_002a90a8:;
/* 002a90a8: beql v0,zero,0x002a9150 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002a90ac */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a9150;}}
/* 002a90b0: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002a90b8));/* delay 002a90b4 */ set(4,cpu(17));nocturneBattlePanelRendererRemainingIndirect(target,UINT32_C(0x002a90b0));}
/* 002a90b8: b 0x002a9150 */ /* delay 002a90bc */ lw(5,ea(16,(int32_t)UINT32_C(0x00000004)));goto L_002a9150;
L_002a90c0:;
/* 002a90c0: lw v0,0x8(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002a90c4: lw v1,0x8(a1) */ lw(3,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 002a90c8: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 002a90cc: slt a0,v1,s1 */ set(4,(int64_t)cpu(3)<(int64_t)cpu(17));
/* 002a90d0: bnel a0,zero,0x002a9080 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 002a90d4 */ set(16,cpu(5));goto L_002a9080;}}
/* 002a90d8: slt v0,s1,v1 */ set(2,(int64_t)cpu(17)<(int64_t)cpu(3));
/* 002a90dc: beq v0,zero,0x002a9118 */ {int taken=(cpu(2)==cpu(0));/* delay 002a90e0 */ if(taken){goto L_002a9118;}}
/* 002a90e4: jal 0x002a8af8 */ set(31,UINT64_C(0x002a90ec));/* delay 002a90e8 */ set(4,sx(UINT32_C(0x00000010)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002a8af8),UINT32_C(0x002a90e4));
/* 002a90ec: lw v1,0x8(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000008)));
/* 002a90f0: sw s0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002a90f4: addu v1,v1,s1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(17)));
/* 002a90f8: sh zero,0xc(v0) */ sh(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(0));
/* 002a90fc: lw a0,0x4(s0) */ lw(4,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002a9100: sw v1,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(3));
/* 002a9104: sw a0,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002a9108: sh zero,0xe(v0) */ sh(ea(2,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(0));
/* 002a910c: lw v1,0x4(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002a9110: sw v0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002a9114: sw v0,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_002a9118:;
/* 002a9118: beq s2,zero,0x002a9128 */ {int taken=(cpu(18)==cpu(0));/* delay 002a911c */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(20));if(taken){goto L_002a9128;}}
/* 002a9120: jal 0x002e40b8 */ set(31,UINT64_C(0x002a9128));/* delay 002a9124 */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e40b8),UINT32_C(0x002a9120));
L_002a9128:;
/* 002a9128: move v0,s0 */ set(2,cpu(16));
/* 002a912c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9130: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9134: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a9138: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a913c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002a9140: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002a9144: jr ra */ {uint64_t target=cpu(31);/* delay 002a9148 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
L_002a9150:;
/* 002a9150: b 0x002a9080 */ /* delay 002a9154 */ set(16,cpu(5));goto L_002a9080;
}
static void body_002a9540(void){
uint64_t incoming=cpu(31);
/* 002a9540: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 002a9544: lw v1,0x4(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000004)));
/* 002a9548: sw a0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002a954c: jr ra */ {uint64_t target=cpu(31);/* delay 002a9550 */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));checkReturn(target,incoming);return;}
}
static void body_002c10e8(void){
uint64_t incoming=cpu(31);
/* 002c10e8: lw v0,-0x27a0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd860)));
/* 002c10ec: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002c10f0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c10f4: move s2,a3 */ set(18,cpu(7));
/* 002c10f8: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002c10fc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c1100: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c1104: move s4,a1 */ set(20,cpu(5));
/* 002c1108: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c110c: move s3,a0 */ set(19,cpu(4));
/* 002c1110: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c1114: move a1,a2 */ set(5,cpu(6));
/* 002c1118: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c111c: bne v0,zero,0x002c1130 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c1120 */ set(3,cpu(2));if(taken){goto L_002c1130;}}
/* 002c1124: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c1128: b 0x002c1134 */ /* delay 002c112c */ sw(ea(28,(int32_t)UINT32_C(0xffffd860)),(uint32_t)cpu(2));goto L_002c1134;
L_002c1130:;
/* 002c1130: sw v1,-0x27a0(gp) */ sw(ea(28,(int32_t)UINT32_C(0xffffd860)),(uint32_t)cpu(3));
L_002c1134:;
/* 002c1134: lhu v0,-0x203c(gp) */ set(2,half(ea(28,(int32_t)UINT32_C(0xffffdfc4))));
/* 002c1138: lhu v1,-0x203e(gp) */ set(3,half(ea(28,(int32_t)UINT32_C(0xffffdfc2))));
/* 002c113c: sll v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)<<16));
/* 002c1140: sra v0,v0,0x10 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>16)));
/* 002c1144: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002c1148: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002c114c: sra v1,v1,0x10 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 002c1150: andi s1,v0,0x1f */ set(17,cpu(2)&UINT32_C(0x0000001f));
/* 002c1154: bne s1,v1,0x002c1190 */ {int taken=(cpu(17)!=cpu(3));/* delay 002c1158 */ set(16,sx(UINT32_C(0x00000008)));if(taken){goto L_002c1190;}}
/* 002c115c: nop  */ 
L_002c1160:;
/* 002c1160: jal 0x002dbdd0 */ set(31,UINT64_C(0x002c1168));/* delay 002c1164 */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfc8)));body_002dbdd0();
/* 002c1168: lhu v1,-0x203e(gp) */ set(3,half(ea(28,(int32_t)UINT32_C(0xffffdfc2))));
/* 002c116c: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002c1170: sra v1,v1,0x10 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>16)));
/* 002c1174: bne v1,s1,0x002c1160 */ {int taken=(cpu(3)!=cpu(17));/* delay 002c1178 */ if(taken){goto L_002c1160;}}
/* 002c117c: addiu s0,s0,-0x1 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffffff)));
/* 002c1180: bne s0,zero,0x002c1160 */ {int taken=(cpu(16)!=cpu(0));/* delay 002c1184 */ set(2,cpu(0));if(taken){goto L_002c1160;}}
/* 002c1188: b 0x002c1218 */ /* delay 002c118c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002c1218;
L_002c1190:;
/* 002c1190: lhu v0,-0x203c(gp) */ set(2,half(ea(28,(int32_t)UINT32_C(0xffffdfc4))));
/* 002c1194: lw v1,-0x27a0(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd860)));
/* 002c1198: sll v0,v0,0x10 */ set(2,sx((uint32_t)cpu(2)<<16));
/* 002c119c: sra v0,v0,0x9 */ set(2,sx((uint32_t)((int32_t)cpu(2)>>9)));
/* 002c11a0: lui s0,0x59 */ set(16,sx(UINT32_C(0x00590000)));
/* 002c11a4: addiu s0,s0,0x840 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000840)));
/* 002c11a8: addu s0,s0,v0 */ set(16,sx((uint32_t)cpu(16)+(uint32_t)cpu(2)));
/* 002c11ac: beq s2,zero,0x002c11c0 */ {int taken=(cpu(18)==cpu(0));/* delay 002c11b0 */ sw(ea(16,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));if(taken){goto L_002c11c0;}}
/* 002c11b4: addiu a0,s0,0x14 */ set(4,sx((uint32_t)cpu(16)+UINT32_C(0x00000014)));
/* 002c11b8: jal 0x002d43a4 */ set(31,UINT64_C(0x002c11c0));/* delay 002c11bc */ set(6,cpu(18));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d43a4),UINT32_C(0x002c11b8));
L_002c11c0:;
/* 002c11c0: addiu v1,s2,0x23 */ set(3,sx((uint32_t)cpu(18)+UINT32_C(0x00000023)));
/* 002c11c4: andi v0,s4,0xffff */ set(2,cpu(20)&UINT32_C(0x0000ffff));
/* 002c11c8: sll a0,s3,0x10 */ set(4,sx((uint32_t)cpu(19)<<16));
/* 002c11cc: sra v1,v1,0x4 */ set(3,sx((uint32_t)((int32_t)cpu(3)>>4)));
/* 002c11d0: or a0,a0,v0 */ set(4,cpu(4)|cpu(2));
/* 002c11d4: lb v0,-0x2040(gp) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffdfc0))));
/* 002c11d8: sll v1,v1,0x1c */ set(3,sx((uint32_t)cpu(3)<<28));
/* 002c11dc: or a0,a0,v1 */ set(4,cpu(4)|cpu(3));
/* 002c11e0: sw a0,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
/* 002c11e4: sh s1,-0x203c(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffdfc4)),(uint16_t)cpu(17));
/* 002c11e8: beq v0,zero,0x002c1208 */ {int taken=(cpu(2)==cpu(0));/* delay 002c11ec */ if(taken){goto L_002c1208;}}
L_002c11f0:;
/* 002c11f0: jal 0x002c0f28 */ set(31,UINT64_C(0x002c11f8));/* delay 002c11f4 */ body_002c0f28();
/* 002c11f8: bne v0,zero,0x002c11f0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c11fc */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd860)));if(taken){goto L_002c11f0;}}
/* 002c1200: b 0x002c1218 */ /* delay 002c1204 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_002c1218;
L_002c1208:;
/* 002c1208: jal 0x002dbdd0 */ set(31,UINT64_C(0x002c1210));/* delay 002c120c */ lw(4,ea(28,(int32_t)UINT32_C(0xffffdfc8)));body_002dbdd0();
/* 002c1210: lw v0,-0x27a0(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd860)));
/* 002c1214: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002c1218:;
/* 002c1218: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c121c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c1220: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c1224: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c1228: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c122c: jr ra */ {uint64_t target=cpu(31);/* delay 002c1230 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002c1c20(void){
uint64_t incoming=cpu(31);
/* 002c1c20: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c1c24: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c1c28: lui s0,0x59 */ set(16,sx(UINT32_C(0x00590000)));
/* 002c1c2c: addiu s0,s0,0x3880 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00003880)));
/* 002c1c30: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c1c34: addiu a1,s0,0x5a0 */ set(5,sx((uint32_t)cpu(16)+UINT32_C(0x000005a0)));
/* 002c1c38: sra s1,a0,0x10 */ set(17,sx((uint32_t)((int32_t)cpu(4)>>16)));
/* 002c1c3c: move a0,s0 */ set(4,cpu(16));
/* 002c1c40: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c1c44: jal 0x002dc8d8 */ set(31,UINT64_C(0x002c1c4c));/* delay 002c1c48 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000190)));body_002dc8d8();
/* 002c1c4c: move a0,zero */ set(4,cpu(0));
/* 002c1c50: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002c1c54: nop  */ 
L_002c1c58:;
/* 002c1c58: addiu s0,s0,0x8 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));
/* 002c1c5c: beq v1,s1,0x002c1c8c */ {int taken=(cpu(3)==cpu(17));/* delay 002c1c60 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002c1c8c;}}
/* 002c1c64: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 002c1c68: slti v0,a0,0x7 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x00000007));
/* 002c1c6c: nop  */ 
/* 002c1c70: nop  */ 
/* 002c1c74: bnel v0,zero,0x002c1c58 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002c1c78 */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_002c1c58;}}
/* 002c1c7c: lw v1,-0x27b0(gp) */ lw(3,ea(28,(int32_t)UINT32_C(0xffffd850)));
/* 002c1c80: li v0,0x2 */ set(2,sx(UINT32_C(0x00000002)));
/* 002c1c84: xor v1,v1,s1 */ set(3,cpu(3)^cpu(17));
/* 002c1c88: movn v0,zero,v1 */ if(cpu(3)!=0){set(2,cpu(0));}
L_002c1c8c:;
/* 002c1c8c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c1c90: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c1c94: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c1c98: jr ra */ {uint64_t target=cpu(31);/* delay 002c1c9c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002dbdd0(void){
uint64_t incoming=cpu(31);
/* 002dbdd0: li v1,0x33 */ set(3,sx(UINT32_C(0x00000033)));
/* 002dbdd4: syscall 0x0 */ nocturneBattlePanelRendererRemainingSyscall(UINT32_C(0x002dbdd4),cpu(3));
/* 002dbdd8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbddc */ checkReturn(target,incoming);return;}
}
static void body_002de458(void){
uint64_t incoming=cpu(31);
/* 002de458: lui t9,0xffff */ set(25,sx(UINT32_C(0xffff0000)));
/* 002de45c: ori t9,t9,0xffc0 */ set(25,cpu(25)|UINT32_C(0x0000ffc0));
/* 002de460: blez a1,0x002de4fc */ {int taken=((int64_t)cpu(5)<=0);/* delay 002de464 */ set(10,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));if(taken){goto L_002de4fc;}}
/* 002de468: and t0,a0,t9 */ set(8,cpu(4)&cpu(25));
/* 002de46c: addiu t2,t2,-0x1 */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0xffffffff)));
/* 002de470: and t1,t2,t9 */ set(9,cpu(10)&cpu(25));
/* 002de474: subu t2,t1,t0 */ set(10,sx((uint32_t)cpu(9)-(uint32_t)cpu(8)));
/* 002de478: srl t3,t2,0x6 */ set(11,sx((uint32_t)cpu(10)>>6));
/* 002de47c: addiu t3,t3,0x1 */ set(11,sx((uint32_t)cpu(11)+UINT32_C(0x00000001)));
/* 002de480: andi t1,t3,0x7 */ set(9,cpu(11)&UINT32_C(0x00000007));
/* 002de484: beq t1,zero,0x002de4a8 */ {int taken=(cpu(9)==cpu(0));/* delay 002de488 */ set(10,sx((uint32_t)cpu(11)>>3));if(taken){goto L_002de4a8;}}
L_002de48c:;
/* 002de48c: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de48c),0u);
/* 002de490: cache DHWBIN,0x0(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de490),24u,ea(8u,(int32_t)UINT32_C(0x00000000)));
/* 002de494: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de494),0u);
/* 002de498: addiu t1,t1,-0x1 */ set(9,sx((uint32_t)cpu(9)+UINT32_C(0xffffffff)));
/* 002de49c: nop  */ 
/* 002de4a0: bgtz t1,0x002de48c */ {int taken=((int64_t)cpu(9)>0);/* delay 002de4a4 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000040)));if(taken){goto L_002de48c;}}
L_002de4a8:;
/* 002de4a8: beq t2,zero,0x002de4fc */ {int taken=(cpu(10)==cpu(0));/* delay 002de4ac */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0xffffffff)));if(taken){goto L_002de4fc;}}
L_002de4b0:;
/* 002de4b0: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4b0),0u);
/* 002de4b4: cache DHWBIN,0x0(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de4b4),24u,ea(8u,(int32_t)UINT32_C(0x00000000)));
/* 002de4b8: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4b8),0u);
/* 002de4bc: cache DHWBIN,0x40(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de4bc),24u,ea(8u,(int32_t)UINT32_C(0x00000040)));
/* 002de4c0: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4c0),0u);
/* 002de4c4: cache DHWBIN,0x80(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de4c4),24u,ea(8u,(int32_t)UINT32_C(0x00000080)));
/* 002de4c8: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4c8),0u);
/* 002de4cc: cache DHWBIN,0xc0(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de4cc),24u,ea(8u,(int32_t)UINT32_C(0x000000c0)));
/* 002de4d0: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4d0),0u);
/* 002de4d4: cache DHWBIN,0x100(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de4d4),24u,ea(8u,(int32_t)UINT32_C(0x00000100)));
/* 002de4d8: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4d8),0u);
/* 002de4dc: cache DHWBIN,0x140(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de4dc),24u,ea(8u,(int32_t)UINT32_C(0x00000140)));
/* 002de4e0: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4e0),0u);
/* 002de4e4: cache DHWBIN,0x180(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de4e4),24u,ea(8u,(int32_t)UINT32_C(0x00000180)));
/* 002de4e8: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4e8),0u);
/* 002de4ec: cache DHWBIN,0x1c0(t0) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002de4ec),24u,ea(8u,(int32_t)UINT32_C(0x000001c0)));
/* 002de4f0: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002de4f0),0u);
/* 002de4f4: bgtz t2,0x002de4ac */ {int taken=((int64_t)cpu(10)>0);/* delay 002de4f8 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000200)));if(taken){goto L_002de4ac;}}
L_002de4fc:;
/* 002de4fc: jr ra */ {uint64_t target=cpu(31);/* delay 002de500 */ checkReturn(target,incoming);return;}
L_002de4ac:;
/* native standalone entry to delay-slot 002de4ac */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0xffffffff)));goto L_002de4b0;
}
static void body_00173cb0(void){
uint64_t incoming=cpu(31);
/* 00173cb0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00173cb4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00173cb8: move s1,a0 */ set(17,cpu(4));
/* 00173cbc: li a0,0xc */ set(4,sx(UINT32_C(0x0000000c)));
/* 00173cc0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173cc4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00173cc8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00173ccc: jal 0x002a8af8 */ set(31,UINT64_C(0x00173cd4));/* delay 00173cd0 */ set(16,cpu(5));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002a8af8),UINT32_C(0x00173ccc));
/* 00173cd4: move s2,v0 */ set(18,cpu(2));
/* 00173cd8: sll v0,s0,0x3 */ set(2,sx((uint32_t)cpu(16)<<3));
/* 00173cdc: subu v0,v0,s0 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(16)));
/* 00173ce0: move a0,s1 */ set(4,cpu(17));
/* 00173ce4: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00173ce8: sw s0,0x0(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 00173cec: lui at,0x32 */ set(1,sx(UINT32_C(0x00320000)));
/* 00173cf0: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 00173cf4: lw v0,-0x4100(at) */ lw(2,ea(1,(int32_t)UINT32_C(0xffffbf00)));
/* 00173cf8: beq v0,zero,0x00173d0c */ {int taken=(cpu(2)==cpu(0));/* delay 00173cfc */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));if(taken){goto L_00173d0c;}}
/* 00173d00: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00173d08));/* delay 00173d04 */ nocturneBattlePanelRendererRemainingIndirect(target,UINT32_C(0x00173d00));}
/* 00173d08: sw v0,0x4(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));
L_00173d0c:;
/* 00173d0c: move v0,s2 */ set(2,cpu(18));
/* 00173d10: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173d14: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00173d18: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00173d1c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00173d20: jr ra */ {uint64_t target=cpu(31);/* delay 00173d24 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00173ef0(void){
uint64_t incoming=cpu(31);
/* 00173ef0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00173ef4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00173ef8: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00173efc: sll v0,v1,0x3 */ set(2,sx((uint32_t)cpu(3)<<3));
/* 00173f00: subu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(3)));
/* 00173f04: sll v0,v0,0x3 */ set(2,sx((uint32_t)cpu(2)<<3));
/* 00173f08: lui at,0x32 */ set(1,sx(UINT32_C(0x00320000)));
/* 00173f0c: addu at,at,v0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(2)));
/* 00173f10: lw v0,-0x40ec(at) */ lw(2,ea(1,(int32_t)UINT32_C(0xffffbf14)));
/* 00173f14: beql v0,zero,0x00173f30 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 00173f18 */ set(2,cpu(0));goto L_00173f30;}}
/* 00173f1c: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x00173f24));/* delay 00173f20 */ lw(4,ea(4,(int32_t)UINT32_C(0x00000004)));nocturneBattlePanelRendererRemainingIndirect(target,UINT32_C(0x00173f1c));}
/* 00173f24: b 0x00173f34 */ /* delay 00173f28 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00173f34;
L_00173f30:;
/* 00173f30: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00173f34:;
/* 00173f34: jr ra */ {uint64_t target=cpu(31);/* delay 00173f38 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_001c60e0(void){
uint64_t incoming=cpu(31);
/* 001c60e0: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001c60e4: andi a0,a0,0xffff */ set(4,cpu(4)&UINT32_C(0x0000ffff));
/* 001c60e8: addiu a3,v0,0x5e50 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0x00005e50)));
/* 001c60ec: move a2,zero */ set(6,cpu(0));
/* 001c60f0: lhu v1,0x0(a3) */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000000))));
/* 001c60f4: nop  */ 
L_001c60f8:;
/* 001c60f8: addiu a3,a3,0x2 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000002)));
/* 001c60fc: move v0,a2 */ set(2,cpu(6));
/* 001c6100: addiu a2,a2,0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000001)));
/* 001c6104: beq v1,a0,0x001c6120 */ {int taken=(cpu(3)==cpu(4));/* delay 001c6108 */ set(5,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00000108));if(taken){goto L_001c6120;}}
/* 001c610c: nop  */ 
/* 001c6110: nop  */ 
/* 001c6114: bnel a1,zero,0x001c60f8 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 001c6118 */ set(3,half(ea(7,(int32_t)UINT32_C(0x00000000))));goto L_001c60f8;}}
/* 001c611c: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
L_001c6120:;
/* 001c6120: jr ra */ {uint64_t target=cpu(31);/* delay 001c6124 */ checkReturn(target,incoming);return;}
}
static void body_001c6b68(void){
uint64_t incoming=cpu(31);
/* 001c6b68: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c6b6c: move t0,a1 */ set(8,cpu(5));
/* 001c6b70: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c6b74: move s0,a2 */ set(16,cpu(6));
/* 001c6b78: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c6b7c: andi s1,a0,0xff */ set(17,cpu(4)&UINT32_C(0x000000ff));
/* 001c6b80: bne t0,zero,0x001c6b9c */ {int taken=(cpu(8)!=cpu(0));/* delay 001c6b84 */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_001c6b9c;}}
/* 001c6b88: beq s0,zero,0x001c6ba0 */ {int taken=(cpu(16)==cpu(0));/* delay 001c6b8c */ set(2,sx((uint32_t)cpu(17)<<3));if(taken){goto L_001c6ba0;}}
/* 001c6b90: jal 0x002a9688 */ set(31,UINT64_C(0x001c6b98));/* delay 001c6b94 */ set(4,cpu(16));body_002a9688();
/* 001c6b98: move t0,v0 */ set(8,cpu(2));
L_001c6b9c:;
/* 001c6b9c: sll v0,s1,0x3 */ set(2,sx((uint32_t)cpu(17)<<3));
L_001c6ba0:;
/* 001c6ba0: lw a0,0x0(t0) */ lw(4,ea(8,(int32_t)UINT32_C(0x00000000)));
/* 001c6ba4: addu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(17)));
/* 001c6ba8: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c6bac: lui a2,0x57 */ set(6,sx(UINT32_C(0x00570000)));
/* 001c6bb0: addiu a2,a2,-0x45d0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffba30)));
/* 001c6bb4: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001c6bb8: sw s0,0x0(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 001c6bbc: sw t0,0x4(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(8));
/* 001c6bc0: lbu v0,0xa(t0) */ set(2,byte(ea(8,(int32_t)UINT32_C(0x0000000a))));
/* 001c6bc4: lbu v1,0x16(t0) */ set(3,byte(ea(8,(int32_t)UINT32_C(0x00000016))));
/* 001c6bc8: sll v0,v0,0x6 */ set(2,sx((uint32_t)cpu(2)<<6));
/* 001c6bcc: beq v1,zero,0x001c6c10 */ {int taken=(cpu(3)==cpu(0));/* delay 001c6bd0 */ set(7,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));if(taken){goto L_001c6c10;}}
/* 001c6bd4: addu v0,t0,a3 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(7)));
/* 001c6bd8: lw a0,0x0(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001c6bdc: addiu v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c6be0: sw v1,0x10(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(3));
/* 001c6be4: addiu a1,a0,0x4 */ set(5,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 001c6be8: sw a0,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(4));
/* 001c6bec: addu a3,a3,a1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(5)));
/* 001c6bf0: addu v0,t0,a3 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(7)));
/* 001c6bf4: lw a0,0x0(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 001c6bf8: addiu v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c6bfc: sw v0,0x14(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c6c00: addiu v1,a0,0x4 */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x00000004)));
/* 001c6c04: sw a0,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(4));
/* 001c6c08: b 0x001c6c20 */ /* delay 001c6c0c */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(3)));goto L_001c6c20;
L_001c6c10:;
/* 001c6c10: sw zero,0x10(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(0));
/* 001c6c14: sw zero,0x14(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(0));
/* 001c6c18: sw zero,0x8(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001c6c1c: sw zero,0xc(a2) */ sw(ea(6,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
L_001c6c20:;
/* 001c6c20: lw v0,0x4(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000004)));
/* 001c6c24: addu a0,t0,a3 */ set(4,sx((uint32_t)cpu(8)+(uint32_t)cpu(7)));
/* 001c6c28: sw a0,0x18(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(4));
/* 001c6c2c: lhu v1,0xe(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x0000000e))));
/* 001c6c30: lw a1,0x18(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x00000018)));
/* 001c6c34: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001c6c38: addu a3,a3,v1 */ set(7,sx((uint32_t)cpu(7)+(uint32_t)cpu(3)));
/* 001c6c3c: addu a0,t0,a1 */ set(4,sx((uint32_t)cpu(8)+(uint32_t)cpu(5)));
/* 001c6c40: addu v0,t0,a3 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(7)));
/* 001c6c44: beq a1,zero,0x001c6c58 */ {int taken=(cpu(5)==cpu(0));/* delay 001c6c48 */ sw(ea(6,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(2));if(taken){goto L_001c6c58;}}
/* 001c6c4c: b 0x001c6c5c */ /* delay 001c6c50 */ sw(ea(6,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(4));goto L_001c6c5c;
L_001c6c58:;
/* 001c6c58: sw zero,0x20(a2) */ sw(ea(6,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(0));
L_001c6c5c:;
/* 001c6c5c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c6c60: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c6c64: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c6c68: jr ra */ {uint64_t target=cpu(31);/* delay 001c6c6c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c7288(void){
uint64_t incoming=cpu(31);
/* 001c7288: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c728c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c7290: move s2,a1 */ set(18,cpu(5));
/* 001c7294: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c7298: move s4,a0 */ set(20,cpu(4));
/* 001c729c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c72a0: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c72a4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c72a8: bne s2,zero,0x001c72e0 */ {int taken=(cpu(18)!=cpu(0));/* delay 001c72ac */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));if(taken){goto L_001c72e0;}}
/* 001c72b0: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
/* 001c72b4: addiu s0,s1,-0x45d0 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0xffffba30)));
/* 001c72b8: jal 0x001cabd8 */ set(31,UINT64_C(0x001c72c0));/* delay 001c72bc */ lw(4,ea(16,(int32_t)UINT32_C(0x00000154)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001cabd8),UINT32_C(0x001c72b8));
/* 001c72c0: move s2,v0 */ set(18,cpu(2));
/* 001c72c4: lw v0,0x14c(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000014c)));
/* 001c72c8: move a0,s2 */ set(4,cpu(18));
/* 001c72cc: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c72d0: jal 0x001c76a8 */ set(31,UINT64_C(0x001c72d8));/* delay 001c72d4 */ sw(ea(16,(int32_t)UINT32_C(0x0000014c)),(uint32_t)cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c76a8),UINT32_C(0x001c72d0));
/* 001c72d8: b 0x001c72e8 */ /* delay 001c72dc */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0xffffba30)));goto L_001c72e8;
L_001c72e0:;
/* 001c72e0: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
/* 001c72e4: addiu s0,s1,-0x45d0 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0xffffba30)));
L_001c72e8:;
/* 001c72e8: jal 0x001cabd8 */ set(31,UINT64_C(0x001c72f0));/* delay 001c72ec */ lw(4,ea(16,(int32_t)UINT32_C(0x00000150)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001cabd8),UINT32_C(0x001c72e8));
/* 001c72f0: lw s3,0x20(s2) */ lw(19,ea(18,(int32_t)UINT32_C(0x00000020)));
/* 001c72f4: move s1,v0 */ set(17,cpu(2));
/* 001c72f8: lw v0,0x148(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000148)));
/* 001c72fc: lui t0,0xa09d */ set(8,sx(UINT32_C(0xa09d0000)));
/* 001c7300: move a0,s1 */ set(4,cpu(17));
/* 001c7304: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c7308: move a1,zero */ set(5,cpu(0));
/* 001c730c: sw v0,0x148(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000148)),(uint32_t)cpu(2));
/* 001c7310: move a2,zero */ set(6,cpu(0));
/* 001c7314: move a3,zero */ set(7,cpu(0));
/* 001c7318: ori t0,t0,0xc300 */ set(8,cpu(8)|UINT32_C(0x0000c300));
/* 001c731c: jal 0x001c7660 */ set(31,UINT64_C(0x001c7324));/* delay 001c7320 */ set(9,cpu(0));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7660),UINT32_C(0x001c731c));
/* 001c7324: bne s3,zero,0x001c7338 */ {int taken=(cpu(19)!=cpu(0));/* delay 001c7328 */ set(4,cpu(0));if(taken){goto L_001c7338;}}
/* 001c732c: b 0x001c733c */ /* delay 001c7330 */ sw(ea(18,(int32_t)UINT32_C(0x0000001c)),(uint32_t)cpu(17));goto L_001c733c;
L_001c7338:;
/* 001c7338: sw s1,0x28(s3) */ sw(ea(19,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(17));
L_001c733c:;
/* 001c733c: sw s4,0x20(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(20));
/* 001c7340: lui v0,0x32 */ set(2,sx(UINT32_C(0x00320000)));
/* 001c7344: lb v1,0x6060(v0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(2,(int32_t)UINT32_C(0x00006060))));
/* 001c7348: jal 0x001c83b0 */ set(31,UINT64_C(0x001c7350));/* delay 001c734c */ sw(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c83b0),UINT32_C(0x001c7348));
/* 001c7350: move a0,zero */ set(4,cpu(0));
/* 001c7354: jal 0x001c8418 */ set(31,UINT64_C(0x001c735c));/* delay 001c7358 */ sb(ea(17,(int32_t)UINT32_C(0x00000018)),(uint8_t)cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c8418),UINT32_C(0x001c7354));
/* 001c735c: sw s3,0x24(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000024)),(uint32_t)cpu(19));
/* 001c7360: sb v0,0x19(s1) */ sb(ea(17,(int32_t)UINT32_C(0x00000019)),(uint8_t)cpu(2));
/* 001c7364: move v0,s2 */ set(2,cpu(18));
/* 001c7368: sw s1,0x20(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000020)),(uint32_t)cpu(17));
/* 001c736c: lw v1,0x18(s2) */ lw(3,ea(18,(int32_t)UINT32_C(0x00000018)));
/* 001c7370: lw a1,0xc(s2) */ lw(5,ea(18,(int32_t)UINT32_C(0x0000000c)));
/* 001c7374: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001c7378: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c737c: sw v1,0x18(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
/* 001c7380: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c7384: lw a0,0xc(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x0000000c)));
/* 001c7388: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c738c: addu a1,a1,a0 */ set(5,sx((uint32_t)cpu(5)+(uint32_t)cpu(4)));
/* 001c7390: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c7394: sw a1,0xc(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(5));
/* 001c7398: lbu v1,0x18(s1) */ set(3,byte(ea(17,(int32_t)UINT32_C(0x00000018))));
/* 001c739c: sh v1,0x10(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000010)),(uint16_t)cpu(3));
/* 001c73a0: lbu a0,0x19(s1) */ set(4,byte(ea(17,(int32_t)UINT32_C(0x00000019))));
/* 001c73a4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c73a8: sh a0,0x12(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000012)),(uint16_t)cpu(4));
/* 001c73ac: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c73b0: jr ra */ {uint64_t target=cpu(31);/* delay 001c73b4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c81b8(void){
uint64_t incoming=cpu(31);
/* 001c81b8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001c81bc: move a1,a0 */ set(5,cpu(4));
/* 001c81c0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c81c4: move a2,zero */ set(6,cpu(0));
/* 001c81c8: li a0,0x8 */ set(4,sx(UINT32_C(0x00000008)));
/* 001c81cc: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c81d0: j 0x001c6b68 */ /* delay 001c81d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001c6b68();return;
}
static void body_001c8508(void){
uint64_t incoming=cpu(31);
/* 001c8508: andi v0,a0,0xff */ set(2,cpu(4)&UINT32_C(0x000000ff));
/* 001c850c: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 001c8510: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001c8514: sd s5,0x38(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c8518: lui s5,0x57 */ set(21,sx(UINT32_C(0x00570000)));
/* 001c851c: addu s5,s5,v0 */ set(21,sx((uint32_t)cpu(21)+(uint32_t)cpu(2)));
/* 001c8520: lw s5,-0x4430(s5) */ lw(21,ea(21,(int32_t)UINT32_C(0xffffbbd0)));
/* 001c8524: move a0,sp */ set(4,cpu(29));
/* 001c8528: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c852c: move s0,a1 */ set(16,cpu(5));
/* 001c8530: li a2,0x3 */ set(6,sx(UINT32_C(0x00000003)));
/* 001c8534: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c8538: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c853c: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c8540: sd s4,0x30(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c8544: sd s6,0x40(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c8548: sd ra,0x48(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c854c: jal 0x002d4558 */ set(31,UINT64_C(0x001c8554));/* delay 001c8550 */ set(5,cpu(0));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d4558),UINT32_C(0x001c854c));
/* 001c8554: beql s5,zero,0x001c8678 */ {int taken=(cpu(21)==cpu(0));if(taken){/* delay 001c8558 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));goto L_001c8678;}}
/* 001c855c: move a0,s5 */ set(4,cpu(21));
/* 001c8560: jal 0x002d5d0c */ set(31,UINT64_C(0x001c8568));/* delay 001c8564 */ set(19,cpu(0));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d5d0c),UINT32_C(0x001c8560));
/* 001c8568: lbu a1,0xc(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000c))));
/* 001c856c: move s6,v0 */ set(22,cpu(2));
/* 001c8570: blez s6,0x001c8674 */ {int taken=((int64_t)cpu(22)<=0);/* delay 001c8574 */ set(20,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000c))));if(taken){goto L_001c8674;}}
/* 001c8578: b 0x001c8588 */ /* delay 001c857c */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));goto L_001c8588;
L_001c8580:;
/* 001c8580: addu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));
/* 001c8584: nop  */ 
L_001c8588:;
/* 001c8588: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c858c: andi a0,v1,0x80 */ set(4,cpu(3)&UINT32_C(0x00000080));
/* 001c8590: beq a0,zero,0x001c85c0 */ {int taken=(cpu(4)==cpu(0));/* delay 001c8594 */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));if(taken){goto L_001c85c0;}}
/* 001c8598: addiu s3,s3,0x1 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));
/* 001c859c: andi s2,v1,0xff */ set(18,cpu(3)&UINT32_C(0x000000ff));
/* 001c85a0: addu v0,s5,s3 */ set(2,sx((uint32_t)cpu(21)+(uint32_t)cpu(19)));
/* 001c85a4: sll a0,s2,0x8 */ set(4,sx((uint32_t)cpu(18)<<8));
/* 001c85a8: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c85ac: andi v0,v1,0xff */ set(2,cpu(3)&UINT32_C(0x000000ff));
/* 001c85b0: sb v1,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(3));
/* 001c85b4: b 0x001c85c8 */ /* delay 001c85b8 */ set(18,cpu(4)|cpu(2));goto L_001c85c8;
L_001c85c0:;
/* 001c85c0: sb zero,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));
/* 001c85c4: lbu s2,0x0(sp) */ set(18,byte(ea(29,(int32_t)UINT32_C(0x00000000))));
L_001c85c8:;
/* 001c85c8: sll v0,a1,0x18 */ set(2,sx((uint32_t)cpu(5)<<24));
/* 001c85cc: sra s1,v0,0x18 */ set(17,sx((uint32_t)((int32_t)cpu(2)>>24)));
/* 001c85d0: beql s1,s4,0x001c8634 */ {int taken=(cpu(17)==cpu(20));if(taken){/* delay 001c85d4 */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));goto L_001c8634;}}
/* 001c85d8: lw t0,0x14(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c85dc: beq t0,zero,0x001c8600 */ {int taken=(cpu(8)==cpu(0));/* delay 001c85e0 */ set(4,sx(UINT32_C(0x00550000)));if(taken){goto L_001c8600;}}
/* 001c85e4: lw v0,0x1c(t0) */ lw(2,ea(8,(int32_t)UINT32_C(0x0000001c)));
/* 001c85e8: beql v0,zero,0x001c8624 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c85ec */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000f))));goto L_001c8624;}}
/* 001c85f0: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
/* 001c85f4: b 0x001c860c */ /* delay 001c85f8 */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));goto L_001c860c;
L_001c8600:;
/* 001c8600: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
/* 001c8604: lb a3,0xe(s0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 001c8608: move t0,zero */ set(8,cpu(0));
L_001c860c:;
/* 001c860c: addiu a0,a0,-0xbd0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffff430)));
/* 001c8610: jal 0x001c7828 */ set(31,UINT64_C(0x001c8618));/* delay 001c8614 */ set(5,cpu(0));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7828),UINT32_C(0x001c8610));
/* 001c8618: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c861c: move t0,v0 */ set(8,cpu(2));
/* 001c8620: lbu a1,0xf(s0) */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000f))));
L_001c8624:;
/* 001c8624: move a0,t0 */ set(4,cpu(8));
/* 001c8628: jal 0x001c7a60 */ set(31,UINT64_C(0x001c8630));/* delay 001c862c */ set(20,cpu(17));body_001c7a60();
/* 001c8630: lb a2,0xd(s0) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000d))));
L_001c8634:;
/* 001c8634: move a0,sp */ set(4,cpu(29));
/* 001c8638: lb a3,0xe(s0) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 001c863c: sltiu t1,s3,0x1 */ set(9,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
/* 001c8640: lw t0,0x14(s0) */ lw(8,ea(16,(int32_t)UINT32_C(0x00000014)));
/* 001c8644: move a1,s1 */ set(5,cpu(17));
/* 001c8648: jal 0x001c7890 */ set(31,UINT64_C(0x001c8650));/* delay 001c864c */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x00000001)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7890),UINT32_C(0x001c8648));
/* 001c8650: lb a1,-0x4d68(gp) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));
/* 001c8654: sw v0,0x14(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c8658: jal 0x001c7a88 */ set(31,UINT64_C(0x001c8660));/* delay 001c865c */ set(4,cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7a88),UINT32_C(0x001c8658));
/* 001c8660: jal 0x001c6128 */ set(31,UINT64_C(0x001c8668));/* delay 001c8664 */ set(4,cpu(18));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c6128),UINT32_C(0x001c8660));
/* 001c8668: slt v0,s3,s6 */ set(2,(int64_t)cpu(19)<(int64_t)cpu(22));
/* 001c866c: bnel v0,zero,0x001c8580 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c8670 */ set(5,byte(ea(16,(int32_t)UINT32_C(0x0000000c))));goto L_001c8580;}}
L_001c8674:;
/* 001c8674: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
L_001c8678:;
/* 001c8678: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c867c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c8680: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c8684: ld s4,0x30(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c8688: ld s5,0x38(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 001c868c: ld s6,0x40(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 001c8690: ld ra,0x48(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000048)));
/* 001c8694: jr ra */ {uint64_t target=cpu(31);/* delay 001c8698 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000050)));checkReturn(target,incoming);return;}
}
static void body_001c87c8(void){
uint64_t incoming=cpu(31);
/* 001c87c8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c87cc: sll v0,a0,0x8 */ set(2,sx((uint32_t)cpu(4)<<8));
/* 001c87d0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c87d4: andi t0,a0,0xf */ set(8,cpu(4)&UINT32_C(0x0000000f));
/* 001c87d8: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c87dc: move s1,a1 */ set(17,cpu(5));
/* 001c87e0: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c87e4: addiu s0,s1,0x18 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));
/* 001c87e8: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c87ec: ori a3,zero,0xf118 */ set(7,cpu(0)|UINT32_C(0x0000f118));
/* 001c87f0: lw a1,0x0(s0) */ lw(5,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001c87f4: lw a2,0x10(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c87f8: lb s2,0xd(s1) */ set(18,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000d))));
/* 001c87fc: addu v1,a2,a1 */ set(3,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c8800: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 001c8804: lbu a0,0x0(v1) */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001c8808: or a0,v0,a0 */ set(4,cpu(2)|cpu(4));
/* 001c880c: beq a0,a3,0x001c8c60 */ {int taken=(cpu(4)==cpu(7));/* delay 001c8810 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));if(taken){goto L_001c8c60;}}
/* 001c8814: slt v0,a3,a0 */ set(2,(int64_t)cpu(7)<(int64_t)cpu(4));
/* 001c8818: bne v0,zero,0x001c88d0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c881c */ set(2,cpu(0)|UINT32_C(0x0000f209));if(taken){goto L_001c88d0;}}
/* 001c8820: ori v0,zero,0xf112 */ set(2,cpu(0)|UINT32_C(0x0000f112));
/* 001c8824: beq a0,v0,0x001c8ba0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8828 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c8ba0;}}
/* 001c882c: bne v0,zero,0x001c8880 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c8830 */ set(2,cpu(0)|UINT32_C(0x0000f115));if(taken){goto L_001c8880;}}
/* 001c8834: ori v0,zero,0xf10f */ set(2,cpu(0)|UINT32_C(0x0000f10f));
/* 001c8838: beq a0,v0,0x001c8b50 */ {int taken=(cpu(4)==cpu(2));/* delay 001c883c */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c8b50;}}
/* 001c8840: bne v0,zero,0x001c8860 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c8844 */ set(2,cpu(0)|UINT32_C(0x0000f110));if(taken){goto L_001c8860;}}
/* 001c8848: ori v0,zero,0xf104 */ set(2,cpu(0)|UINT32_C(0x0000f104));
/* 001c884c: beql a0,v0,0x001c8b8c */ {int taken=(cpu(4)==cpu(2));if(taken){/* delay 001c8850 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb294)));goto L_001c8b8c;}}
/* 001c8854: b 0x001c8ca0 */ /* delay 001c8858 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8860:;
/* 001c8860: beq a0,v0,0x001c8b70 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8864 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb294)));if(taken){goto L_001c8b70;}}
/* 001c8868: ori v0,zero,0xf111 */ set(2,cpu(0)|UINT32_C(0x0000f111));
/* 001c886c: beq a0,v0,0x001c8b80 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8870 */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));if(taken){goto L_001c8b80;}}
/* 001c8874: b 0x001c8ca0 */ /* delay 001c8878 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8880:;
/* 001c8880: beq a0,v0,0x001c8be0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8884 */ if(taken){goto L_001c8be0;}}
/* 001c8888: slt v0,v0,a0 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));
/* 001c888c: bne v0,zero,0x001c88b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c8890 */ set(2,cpu(0)|UINT32_C(0x0000f116));if(taken){goto L_001c88b8;}}
/* 001c8894: ori v0,zero,0xf113 */ set(2,cpu(0)|UINT32_C(0x0000f113));
/* 001c8898: beq a0,v0,0x001c8bb0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c889c */ if(taken){goto L_001c8bb0;}}
/* 001c88a0: ori v0,zero,0xf114 */ set(2,cpu(0)|UINT32_C(0x0000f114));
/* 001c88a4: beq a0,v0,0x001c8bc8 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88a8 */ if(taken){goto L_001c8bc8;}}
/* 001c88ac: b 0x001c8ca0 */ /* delay 001c88b0 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c88b8:;
/* 001c88b8: beq a0,v0,0x001c8c08 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88bc */ set(2,cpu(0)|UINT32_C(0x0000f117));if(taken){goto L_001c8c08;}}
/* 001c88c0: beq a0,v0,0x001c8c30 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88c4 */ if(taken){goto L_001c8c30;}}
/* 001c88c8: b 0x001c8ca0 */ /* delay 001c88cc */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c88d0:;
/* 001c88d0: beq a0,v0,0x001c89a0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88d4 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c89a0;}}
/* 001c88d8: bne v0,zero,0x001c8920 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c88dc */ set(2,cpu(0)|UINT32_C(0x0000f20c));if(taken){goto L_001c8920;}}
/* 001c88e0: ori v0,zero,0xf203 */ set(2,cpu(0)|UINT32_C(0x0000f203));
/* 001c88e4: beq a0,v0,0x001c89d8 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88e8 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c89d8;}}
/* 001c88ec: bne v0,zero,0x001c8908 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c88f0 */ set(2,cpu(0)|UINT32_C(0x0000f206));if(taken){goto L_001c8908;}}
/* 001c88f4: ori v0,zero,0xf202 */ set(2,cpu(0)|UINT32_C(0x0000f202));
/* 001c88f8: beq a0,v0,0x001c8988 */ {int taken=(cpu(4)==cpu(2));/* delay 001c88fc */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));if(taken){goto L_001c8988;}}
/* 001c8900: b 0x001c8ca0 */ /* delay 001c8904 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8908:;
/* 001c8908: beq a0,v0,0x001c8968 */ {int taken=(cpu(4)==cpu(2));/* delay 001c890c */ set(2,cpu(0)|UINT32_C(0x0000f207));if(taken){goto L_001c8968;}}
/* 001c8910: beq a0,v0,0x001c89c0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8914 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));if(taken){goto L_001c89c0;}}
/* 001c8918: b 0x001c8ca0 */ /* delay 001c891c */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8920:;
/* 001c8920: beq a0,v0,0x001c8aa0 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8924 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(4));if(taken){goto L_001c8aa0;}}
/* 001c8928: bne v0,zero,0x001c8950 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c892c */ set(2,cpu(0)|UINT32_C(0x0000f20d));if(taken){goto L_001c8950;}}
/* 001c8930: ori v0,zero,0xf20a */ set(2,cpu(0)|UINT32_C(0x0000f20a));
/* 001c8934: beq a0,v0,0x001c8a30 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8938 */ set(2,cpu(0)|UINT32_C(0x0000f20b));if(taken){goto L_001c8a30;}}
/* 001c893c: beq a0,v0,0x001c8a68 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8940 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));if(taken){goto L_001c8a68;}}
/* 001c8944: b 0x001c8ca0 */ /* delay 001c8948 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8950:;
/* 001c8950: beq a0,v0,0x001c8ae8 */ {int taken=(cpu(4)==cpu(2));/* delay 001c8954 */ set(2,cpu(0)|UINT32_C(0x0000f20e));if(taken){goto L_001c8ae8;}}
/* 001c8958: beq a0,v0,0x001c8b48 */ {int taken=(cpu(4)==cpu(2));/* delay 001c895c */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_001c8b48;}}
/* 001c8960: b 0x001c8ca0 */ /* delay 001c8964 */ lw(3,ea(17,(int32_t)UINT32_C(0x00000018)));goto L_001c8ca0;
L_001c8968:;
/* 001c8968: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c896c: addiu a0,a1,0x2 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8970: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8974: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 001c8978: sb v1,0xc(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(3));
/* 001c897c: b 0x001c8cb0 */ /* delay 001c8980 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_001c8cb0;
L_001c8988:;
/* 001c8988: addiu a0,a1,0x2 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c898c: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8990: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 001c8994: sb v1,0xd(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000000d)),(uint8_t)cpu(3));
/* 001c8998: b 0x001c8cb0 */ /* delay 001c899c */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_001c8cb0;
L_001c89a0:;
/* 001c89a0: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c89a4: addiu a0,a1,0x2 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c89a8: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c89ac: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 001c89b0: sb v1,0xe(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000000e)),(uint8_t)cpu(3));
/* 001c89b4: b 0x001c8cb0 */ /* delay 001c89b8 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_001c8cb0;
L_001c89c0:;
/* 001c89c0: addiu a0,a1,0x2 */ set(4,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c89c4: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c89c8: addiu v1,v1,0xff */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x000000ff)));
/* 001c89cc: sb v1,0xf(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000000f)),(uint8_t)cpu(3));
/* 001c89d0: b 0x001c8cb0 */ /* delay 001c89d4 */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));goto L_001c8cb0;
L_001c89d8:;
/* 001c89d8: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c89dc: lbu v1,0x0(v0) */ set(3,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c89e0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 001c89e4: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 001c89e8: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c89ec: lw v0,-0x4434(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffffbbcc)));
/* 001c89f0: beql v0,zero,0x001c8a24 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c89f4 */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));goto L_001c8a24;}}
/* 001c89f8: jal 0x001c86a0 */ set(31,UINT64_C(0x001c8a00));/* delay 001c89fc */ set(4,cpu(17));body_001c86a0();
/* 001c8a00: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c8a04: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 001c8a08: move a1,s1 */ set(5,cpu(17));
/* 001c8a0c: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c8a10: lbu a0,0x0(v0) */ set(4,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8a14: addiu a0,a0,0xff */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x000000ff)));
/* 001c8a18: jal 0x001c8508 */ set(31,UINT64_C(0x001c8a20));/* delay 001c8a1c */ set(4,cpu(4)&UINT32_C(0x000000ff));body_001c8508();
/* 001c8a20: lw v0,0x0(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x00000000)));
L_001c8a24:;
/* 001c8a24: addiu v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000002)));
/* 001c8a28: b 0x001c8cb0 */ /* delay 001c8a2c */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_001c8cb0;
L_001c8a30:;
/* 001c8a30: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c8a34: addiu v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8a38: lbu a1,0x0(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8a3c: move a0,s1 */ set(4,cpu(17));
/* 001c8a40: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c8a44: jal 0x001c86a0 */ set(31,UINT64_C(0x001c8a4c));/* delay 001c8a48 */ set(16,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));body_001c86a0();
/* 001c8a4c: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 001c8a50: lw a1,0x14(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8a54: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c8a58: jal 0x001c9d00 */ set(31,UINT64_C(0x001c8a60));/* delay 001c8a5c */ set(6,cpu(18));body_001c9d00();
/* 001c8a60: b 0x001c8ad4 */ /* delay 001c8a64 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));goto L_001c8ad4;
L_001c8a68:;
/* 001c8a68: addiu v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8a6c: lbu a1,0x0(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8a70: move a0,s1 */ set(4,cpu(17));
/* 001c8a74: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c8a78: jal 0x001c86a0 */ set(31,UINT64_C(0x001c8a80));/* delay 001c8a7c */ set(16,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));body_001c86a0();
/* 001c8a80: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 001c8a84: lw a1,0x14(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8a88: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c8a8c: jal 0x001c9b58 */ set(31,UINT64_C(0x001c8a94));/* delay 001c8a90 */ set(6,cpu(18));body_001c9b58();
/* 001c8a94: b 0x001c8ad4 */ /* delay 001c8a98 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));goto L_001c8ad4;
L_001c8aa0:;
/* 001c8aa0: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c8aa4: addiu v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8aa8: lbu a1,0x0(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8aac: move a0,s1 */ set(4,cpu(17));
/* 001c8ab0: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c8ab4: jal 0x001c86a0 */ set(31,UINT64_C(0x001c8abc));/* delay 001c8ab8 */ set(16,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));body_001c86a0();
/* 001c8abc: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 001c8ac0: lw a1,0x14(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8ac4: sra a0,a0,0x18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));
/* 001c8ac8: jal 0x001c9c28 */ set(31,UINT64_C(0x001c8ad0));/* delay 001c8acc */ set(6,cpu(18));body_001c9c28();
/* 001c8ad0: lb a1,-0x4d68(gp) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));
L_001c8ad4:;
/* 001c8ad4: sw v0,0x14(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c8ad8: jal 0x001c7a88 */ set(31,UINT64_C(0x001c8ae0));/* delay 001c8adc */ set(4,cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7a88),UINT32_C(0x001c8ad8));
/* 001c8ae0: b 0x001c8cb4 */ /* delay 001c8ae4 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8ae8:;
/* 001c8ae8: addu v0,a2,a1 */ set(2,sx((uint32_t)cpu(6)+(uint32_t)cpu(5)));
/* 001c8aec: addiu v1,a1,0x2 */ set(3,sx((uint32_t)cpu(5)+UINT32_C(0x00000002)));
/* 001c8af0: lbu a1,0x0(v0) */ set(5,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c8af4: move a0,s1 */ set(4,cpu(17));
/* 001c8af8: sw v1,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001c8afc: jal 0x001c86a0 */ set(31,UINT64_C(0x001c8b04));/* delay 001c8b00 */ set(16,sx((uint32_t)cpu(5)+UINT32_C(0xffffffff)));body_001c86a0();
/* 001c8b04: sll a0,s0,0x18 */ set(4,sx((uint32_t)cpu(16)<<24));
/* 001c8b08: lb a1,0xc(s1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 001c8b0c: move a3,s2 */ set(7,cpu(18));
/* 001c8b10: lw a2,0x14(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8b14: jal 0x001c9d60 */ set(31,UINT64_C(0x001c8b1c));/* delay 001c8b18 */ set(4,sx((uint32_t)((int32_t)cpu(4)>>24)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c9d60),UINT32_C(0x001c8b14));
/* 001c8b1c: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c8b20: jal 0x001c7c00 */ set(31,UINT64_C(0x001c8b28));/* delay 001c8b24 */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7c00),UINT32_C(0x001c8b20));
/* 001c8b28: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8b2c: jal 0x001c7a88 */ set(31,UINT64_C(0x001c8b34));/* delay 001c8b30 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7a88),UINT32_C(0x001c8b2c));
/* 001c8b34: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8b38: jal 0x001c7a60 */ set(31,UINT64_C(0x001c8b40));/* delay 001c8b3c */ set(5,byte(ea(17,(int32_t)UINT32_C(0x0000000f))));body_001c7a60();
/* 001c8b40: b 0x001c8cb4 */ /* delay 001c8b44 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8b48:;
/* 001c8b48: b 0x001c8cb0 */ /* delay 001c8b4c */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));goto L_001c8cb0;
L_001c8b50:;
/* 001c8b50: lbu v0,-0x4d54(gp) */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));
/* 001c8b54: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 001c8b58: bnel v0,zero,0x001c8cb4 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001c8b5c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;}}
/* 001c8b60: jal 0x001c8730 */ set(31,UINT64_C(0x001c8b68));/* delay 001c8b64 */ set(4,cpu(17));body_001c8730();
/* 001c8b68: b 0x001c8cb4 */ /* delay 001c8b6c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8b70:;
/* 001c8b70: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c8b74: ori v1,v1,0x2 */ set(3,cpu(3)|UINT32_C(0x00000002));
/* 001c8b78: b 0x001c8cc8 */ /* delay 001c8b7c */ sw(ea(28,(int32_t)UINT32_C(0xffffb294)),(uint32_t)cpu(3));goto L_001c8cc8;
L_001c8b80:;
/* 001c8b80: andi v0,v0,0x8 */ set(2,cpu(2)&UINT32_C(0x00000008));
/* 001c8b84: beq v0,zero,0x001c8cb0 */ {int taken=(cpu(2)==cpu(0));/* delay 001c8b88 */ lw(3,ea(28,(int32_t)UINT32_C(0xffffb294)));if(taken){goto L_001c8cb0;}}
L_001c8b8c:;
/* 001c8b8c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c8b90: ori v1,v1,0x1 */ set(3,cpu(3)|UINT32_C(0x00000001));
/* 001c8b94: b 0x001c8cc8 */ /* delay 001c8b98 */ sw(ea(28,(int32_t)UINT32_C(0xffffb294)),(uint32_t)cpu(3));goto L_001c8cc8;
L_001c8ba0:;
/* 001c8ba0: lw v0,-0x4d6c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb294)));
/* 001c8ba4: ori v0,v0,0x4 */ set(2,cpu(2)|UINT32_C(0x00000004));
/* 001c8ba8: b 0x001c8cb0 */ /* delay 001c8bac */ sw(ea(28,(int32_t)UINT32_C(0xffffb294)),(uint32_t)cpu(2));goto L_001c8cb0;
L_001c8bb0:;
/* 001c8bb0: jal 0x001c6098 */ set(31,UINT64_C(0x001c8bb8));/* delay 001c8bb4 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8bb8: ori v1,zero,0x80e2 */ set(3,cpu(0)|UINT32_C(0x000080e2));
/* 001c8bbc: slti v0,v0,0x0 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001c8bc0: b 0x001c8bf4 */ /* delay 001c8bc4 */ set(5,cpu(0)|UINT32_C(0x000080e3));goto L_001c8bf4;
L_001c8bc8:;
/* 001c8bc8: jal 0x001c6098 */ set(31,UINT64_C(0x001c8bd0));/* delay 001c8bcc */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8bd0: ori v1,zero,0x80e4 */ set(3,cpu(0)|UINT32_C(0x000080e4));
/* 001c8bd4: slti v0,v0,0x0 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001c8bd8: b 0x001c8bf4 */ /* delay 001c8bdc */ set(5,cpu(0)|UINT32_C(0x000080e5));goto L_001c8bf4;
L_001c8be0:;
/* 001c8be0: jal 0x001c6098 */ set(31,UINT64_C(0x001c8be8));/* delay 001c8be4 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8be8: ori v1,zero,0x80e0 */ set(3,cpu(0)|UINT32_C(0x000080e0));
/* 001c8bec: slti v0,v0,0x0 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000000));
/* 001c8bf0: ori a1,zero,0x80e1 */ set(5,cpu(0)|UINT32_C(0x000080e1));
L_001c8bf4:;
/* 001c8bf4: movn a1,v1,v0 */ if(cpu(2)!=0){set(5,cpu(3));}
/* 001c8bf8: jal 0x001c8758 */ set(31,UINT64_C(0x001c8c00));/* delay 001c8bfc */ set(4,cpu(17));body_001c8758();
/* 001c8c00: b 0x001c8cb4 */ /* delay 001c8c04 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8c08:;
/* 001c8c08: jal 0x001c6098 */ set(31,UINT64_C(0x001c8c10));/* delay 001c8c0c */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8c10: bgezl v0,0x001c8cb4 */ {int taken=((int64_t)cpu(2)>=0);if(taken){/* delay 001c8c14 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;}}
/* 001c8c18: move a0,s1 */ set(4,cpu(17));
/* 001c8c1c: jal 0x001c8758 */ set(31,UINT64_C(0x001c8c24));/* delay 001c8c20 */ set(5,cpu(0)|UINT32_C(0x000080e2));body_001c8758();
/* 001c8c24: b 0x001c8cb4 */ /* delay 001c8c28 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8c30:;
/* 001c8c30: jal 0x001c6098 */ set(31,UINT64_C(0x001c8c38));/* delay 001c8c34 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8c38: bgez v0,0x001c8c50 */ {int taken=((int64_t)cpu(2)>=0);/* delay 001c8c3c */ set(4,cpu(17));if(taken){goto L_001c8c50;}}
/* 001c8c40: jal 0x001c8758 */ set(31,UINT64_C(0x001c8c48));/* delay 001c8c44 */ set(5,cpu(0)|UINT32_C(0x000080e7));body_001c8758();
/* 001c8c48: b 0x001c8cb4 */ /* delay 001c8c4c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8c50:;
/* 001c8c50: jal 0x001c8758 */ set(31,UINT64_C(0x001c8c58));/* delay 001c8c54 */ set(5,cpu(0)|UINT32_C(0x000080e6));body_001c8758();
/* 001c8c58: b 0x001c8cb4 */ /* delay 001c8c5c */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8c60:;
/* 001c8c60: jal 0x001c6098 */ set(31,UINT64_C(0x001c8c68));/* delay 001c8c64 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c6098();
/* 001c8c68: bgez v0,0x001c8c8c */ {int taken=((int64_t)cpu(2)>=0);/* delay 001c8c6c */ set(4,cpu(17));if(taken){goto L_001c8c8c;}}
/* 001c8c70: jal 0x001c60e0 */ set(31,UINT64_C(0x001c8c78));/* delay 001c8c74 */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffa890))));body_001c60e0();
/* 001c8c78: bgez v0,0x001c8c8c */ {int taken=((int64_t)cpu(2)>=0);/* delay 001c8c7c */ set(4,cpu(17));if(taken){goto L_001c8c8c;}}
/* 001c8c80: jal 0x001c8758 */ set(31,UINT64_C(0x001c8c88));/* delay 001c8c84 */ set(5,cpu(0)|UINT32_C(0x000080e9));body_001c8758();
/* 001c8c88: move a0,s1 */ set(4,cpu(17));
L_001c8c8c:;
/* 001c8c8c: jal 0x001c8758 */ set(31,UINT64_C(0x001c8c94));/* delay 001c8c90 */ set(5,cpu(0)|UINT32_C(0x000080e8));body_001c8758();
/* 001c8c94: b 0x001c8cb4 */ /* delay 001c8c98 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));goto L_001c8cb4;
L_001c8ca0:;
/* 001c8ca0: addiu v0,t0,-0x1 */ set(2,sx((uint32_t)cpu(8)+UINT32_C(0xffffffff)));
/* 001c8ca4: sll v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)<<1));
/* 001c8ca8: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001c8cac: sw v1,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(3));
L_001c8cb0:;
/* 001c8cb0: lb v0,0x1c(s1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000001c))));
L_001c8cb4:;
/* 001c8cb4: bne v0,zero,0x001c8cc8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001c8cb8 */ set(2,cpu(0));if(taken){goto L_001c8cc8;}}
/* 001c8cbc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 001c8cc0: sb v0,0x1c(s1) */ sb(ea(17,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(2));
/* 001c8cc4: move v0,zero */ set(2,cpu(0));
L_001c8cc8:;
/* 001c8cc8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c8ccc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c8cd0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c8cd4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c8cd8: jr ra */ {uint64_t target=cpu(31);/* delay 001c8cdc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001c8f08(void){
uint64_t incoming=cpu(31);
/* 001c8f08: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 001c8f0c: li v1,0xf0 */ set(3,sx(UINT32_C(0x000000f0)));
/* 001c8f10: sd s1,0x18(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c8f14: move s1,a0 */ set(17,cpu(4));
/* 001c8f18: sd s3,0x28(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c8f1c: sd s0,0x10(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c8f20: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c8f24: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c8f28: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c8f2c: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 001c8f30: andi v0,v0,0xf0 */ set(2,cpu(2)&UINT32_C(0x000000f0));
/* 001c8f34: beq v0,v1,0x001c8f58 */ {int taken=(cpu(2)==cpu(3));/* delay 001c8f38 */ set(19,sx(UINT32_C(0x00000001)));if(taken){goto L_001c8f58;}}
/* 001c8f3c: lbu v1,0x1(a0) */ set(3,byte(ea(4,(int32_t)UINT32_C(0x00000001))));
/* 001c8f40: li v0,0x8 */ set(2,sx(UINT32_C(0x00000008)));
/* 001c8f44: bne v1,v0,0x001c8f5c */ {int taken=(cpu(3)!=cpu(2));/* delay 001c8f48 */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb294)));if(taken){goto L_001c8f5c;}}
/* 001c8f4c: lw v0,0x18(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000018)));
/* 001c8f50: addiu v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000004)));
/* 001c8f54: sw v0,0x18(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(2));
L_001c8f58:;
/* 001c8f58: lw v0,-0x4d6c(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffb294)));
L_001c8f5c:;
/* 001c8f5c: li v1,-0x2 */ set(3,sx(UINT32_C(0xfffffffe)));
/* 001c8f60: li a1,-0x3 */ set(5,sx(UINT32_C(0xfffffffd)));
/* 001c8f64: li a2,-0x5 */ set(6,sx(UINT32_C(0xfffffffb)));
/* 001c8f68: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001c8f6c: li a0,0x1 */ set(4,sx(UINT32_C(0x00000001)));
/* 001c8f70: and v0,v0,a1 */ set(2,cpu(2)&cpu(5));
/* 001c8f74: and v0,v0,a2 */ set(2,cpu(2)&cpu(6));
/* 001c8f78: jal 0x001c7c00 */ set(31,UINT64_C(0x001c8f80));/* delay 001c8f7c */ sw(ea(28,(int32_t)UINT32_C(0xffffb294)),(uint32_t)cpu(2));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7c00),UINT32_C(0x001c8f78));
/* 001c8f80: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c8f84: b 0x001c909c */ /* delay 001c8f88 */ set(18,sx((uint32_t)cpu(17)+UINT32_C(0x00000018)));goto L_001c909c;
L_001c8f90:;
/* 001c8f90: bne s0,v0,0x001c8fb8 */ {int taken=(cpu(16)!=cpu(2));/* delay 001c8f94 */ set(2,byte(ea(28,(int32_t)UINT32_C(0xffffb2ac))));if(taken){goto L_001c8fb8;}}
/* 001c8f98: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 001c8f9c: beql v0,zero,0x001c909c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c8fa0 */ set(19,sx(UINT32_C(0x00000001)));goto L_001c909c;}}
/* 001c8fa4: jal 0x001c8730 */ set(31,UINT64_C(0x001c8fac));/* delay 001c8fa8 */ set(4,cpu(17));body_001c8730();
/* 001c8fac: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c8fb0: b 0x001c909c */ /* delay 001c8fb4 */ set(19,sx(UINT32_C(0x00000001)));goto L_001c909c;
L_001c8fb8:;
/* 001c8fb8: jal 0x001c86a0 */ set(31,UINT64_C(0x001c8fc0));/* delay 001c8fbc */ set(4,cpu(17));body_001c86a0();
/* 001c8fc0: slti v0,s0,0x80 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000080));
/* 001c8fc4: beql v0,zero,0x001c8ff8 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c8fc8 */ lw(3,ea(18,(int32_t)UINT32_C(0x00000000)));goto L_001c8ff8;}}
/* 001c8fcc: lb a1,0xc(s1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 001c8fd0: move t1,s3 */ set(9,cpu(19));
/* 001c8fd4: lb a2,0xd(s1) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000d))));
/* 001c8fd8: move a0,sp */ set(4,cpu(29));
/* 001c8fdc: lb a3,0xe(s1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 001c8fe0: lw t0,0x14(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c8fe4: sb s0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(16));
/* 001c8fe8: jal 0x001c7890 */ set(31,UINT64_C(0x001c8ff0));/* delay 001c8fec */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7890),UINT32_C(0x001c8fe8));
/* 001c8ff0: b 0x001c907c */ /* delay 001c8ff4 */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));goto L_001c907c;
L_001c8ff8:;
/* 001c8ff8: sll a2,s0,0x8 */ set(6,sx((uint32_t)cpu(16)<<8));
/* 001c8ffc: lw v0,0x10(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000010)));
/* 001c9000: ori a1,zero,0xc07f */ set(5,cpu(0)|UINT32_C(0x0000c07f));
/* 001c9004: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 001c9008: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 001c900c: lbu a0,0x0(v0) */ set(4,byte(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 001c9010: or s0,a2,a0 */ set(16,cpu(6)|cpu(4));
/* 001c9014: slt a1,a1,s0 */ set(5,(int64_t)cpu(5)<(int64_t)cpu(16));
/* 001c9018: bne a1,zero,0x001c9040 */ {int taken=(cpu(5)!=cpu(0));/* delay 001c901c */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));if(taken){goto L_001c9040;}}
/* 001c9020: lb a1,0xc(s1) */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 001c9024: srl v0,s0,0x8 */ set(2,sx((uint32_t)cpu(16)>>8));
/* 001c9028: lb a2,0xd(s1) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000d))));
/* 001c902c: move t1,s3 */ set(9,cpu(19));
/* 001c9030: lb a3,0xe(s1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 001c9034: move a0,sp */ set(4,cpu(29));
/* 001c9038: b 0x001c9060 */ /* delay 001c903c */ lw(8,ea(17,(int32_t)UINT32_C(0x00000014)));goto L_001c9060;
L_001c9040:;
/* 001c9040: lb a2,0xd(s1) */ set(6,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000d))));
/* 001c9044: addiu s0,s0,-0x4000 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffc000)));
/* 001c9048: lb a3,0xe(s1) */ set(7,(uint64_t)(int64_t)(int8_t)byte(ea(17,(int32_t)UINT32_C(0x0000000e))));
/* 001c904c: srl v0,s0,0x8 */ set(2,sx((uint32_t)cpu(16)>>8));
/* 001c9050: lw t0,0x14(s1) */ lw(8,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c9054: move t1,s3 */ set(9,cpu(19));
/* 001c9058: move a0,sp */ set(4,cpu(29));
/* 001c905c: li a1,0x8 */ set(5,sx(UINT32_C(0x00000008)));
L_001c9060:;
/* 001c9060: sb v0,0x0(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001c9064: sb s0,0x1(sp) */ sb(ea(29,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(16));
/* 001c9068: jal 0x001c7890 */ set(31,UINT64_C(0x001c9070));/* delay 001c906c */ sb(ea(29,(int32_t)UINT32_C(0x00000002)),(uint8_t)cpu(0));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7890),UINT32_C(0x001c9068));
/* 001c9070: sw v0,0x14(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c9074: jal 0x001c6128 */ set(31,UINT64_C(0x001c907c));/* delay 001c9078 */ set(4,cpu(16)&UINT32_C(0x0000ffff));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c6128),UINT32_C(0x001c9074));
L_001c907c:;
/* 001c907c: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c9080: move s3,zero */ set(19,cpu(0));
/* 001c9084: jal 0x001c7a88 */ set(31,UINT64_C(0x001c908c));/* delay 001c9088 */ set(5,(uint64_t)(int64_t)(int8_t)byte(ea(28,(int32_t)UINT32_C(0xffffb298))));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7a88),UINT32_C(0x001c9084));
/* 001c908c: lw a0,0x14(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c9090: jal 0x001c7b40 */ set(31,UINT64_C(0x001c9098));/* delay 001c9094 */ lw(5,ea(17,(int32_t)UINT32_C(0x00000008)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7b40),UINT32_C(0x001c9090));
/* 001c9098: lw a0,0x10(s1) */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));
L_001c909c:;
/* 001c909c: lw v0,0x0(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000000)));
/* 001c90a0: addu v1,a0,v0 */ set(3,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001c90a4: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 001c90a8: lbu s0,0x0(v1) */ set(16,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001c90ac: beq s0,zero,0x001c90d8 */ {int taken=(cpu(16)==cpu(0));/* delay 001c90b0 */ sw(ea(18,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_001c90d8;}}
/* 001c90b4: andi v1,s0,0xf0 */ set(3,cpu(16)&UINT32_C(0x000000f0));
/* 001c90b8: li v0,0xf0 */ set(2,sx(UINT32_C(0x000000f0)));
/* 001c90bc: bne v1,v0,0x001c8f90 */ {int taken=(cpu(3)!=cpu(2));/* delay 001c90c0 */ set(2,sx(UINT32_C(0x0000000a)));if(taken){goto L_001c8f90;}}
/* 001c90c4: move a0,s0 */ set(4,cpu(16));
/* 001c90c8: jal 0x001c87c8 */ set(31,UINT64_C(0x001c90d0));/* delay 001c90cc */ set(5,cpu(17));body_001c87c8();
/* 001c90d0: beql v0,zero,0x001c909c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 001c90d4 */ lw(4,ea(17,(int32_t)UINT32_C(0x00000010)));goto L_001c909c;}}
L_001c90d8:;
/* 001c90d8: jal 0x001c7c10 */ set(31,UINT64_C(0x001c90e0));/* delay 001c90dc */ set(4,sx(UINT32_C(0x00000001)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7c10),UINT32_C(0x001c90d8));
/* 001c90e0: jal 0x001c7c00 */ set(31,UINT64_C(0x001c90e8));/* delay 001c90e4 */ set(4,sx(UINT32_C(0x00000002)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c7c00),UINT32_C(0x001c90e0));
/* 001c90e8: lw v0,0x14(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000014)));
/* 001c90ec: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c90f0: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001c90f4: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c90f8: ld s3,0x28(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 001c90fc: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9100: jr ra */ {uint64_t target=cpu(31);/* delay 001c9104 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_001c9188(void){
uint64_t incoming=cpu(31);
/* 001c9188: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001c918c: li v1,0x1 */ set(3,sx(UINT32_C(0x00000001)));
/* 001c9190: lw v0,0x30(sp) */ lw(2,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 001c9194: sll a2,a2,0x4 */ set(6,sx((uint32_t)cpu(6)<<4));
/* 001c9198: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 001c919c: move a0,sp */ set(4,cpu(29));
/* 001c91a0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c91a4: sw a1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(5));
/* 001c91a8: sw a2,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 001c91ac: sb a3,0xc(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint8_t)cpu(7));
/* 001c91b0: sb t0,0xd(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000000d)),(uint8_t)cpu(8));
/* 001c91b4: sb t1,0xe(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000000e)),(uint8_t)cpu(9));
/* 001c91b8: sb t2,0xf(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000000f)),(uint8_t)cpu(10));
/* 001c91bc: sw t3,0x10(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(11));
/* 001c91c0: sw v0,0x14(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(2));
/* 001c91c4: sb v1,0x1d(sp) */ sb(ea(29,(int32_t)UINT32_C(0x0000001d)),(uint8_t)cpu(3));
/* 001c91c8: sw zero,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),(uint32_t)cpu(0));
/* 001c91cc: jal 0x001c8f08 */ set(31,UINT64_C(0x001c91d4));/* delay 001c91d0 */ sb(ea(29,(int32_t)UINT32_C(0x0000001c)),(uint8_t)cpu(3));body_001c8f08();
/* 001c91d4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001c91d8: jr ra */ {uint64_t target=cpu(31);/* delay 001c91dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001c9230(void){
uint64_t incoming=cpu(31);
/* 001c9230: sll a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)<<2));
/* 001c9234: lui at,0x57 */ set(1,sx(UINT32_C(0x00570000)));
/* 001c9238: addu at,at,a0 */ set(1,sx((uint32_t)cpu(1)+(uint32_t)cpu(4)));
/* 001c923c: sw a1,-0x4430(at) */ sw(ea(1,(int32_t)UINT32_C(0xffffbbd0)),(uint32_t)cpu(5));
/* 001c9240: jr ra */ {uint64_t target=cpu(31);/* delay 001c9244 */ checkReturn(target,incoming);return;}
}
static void body_001c9d00(void){
uint64_t incoming=cpu(31);
/* 001c9d00: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001c9d04: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9d08: sll s0,a0,0x18 */ set(16,sx((uint32_t)cpu(4)<<24));
/* 001c9d0c: sra s0,s0,0x18 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>24)));
/* 001c9d10: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9d14: move a0,s0 */ set(4,cpu(16));
/* 001c9d18: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9d1c: jal 0x001c9c28 */ set(31,UINT64_C(0x001c9d24));/* delay 001c9d20 */ set(17,cpu(6));body_001c9c28();
/* 001c9d24: lw v1,0xc(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x0000000c)));
/* 001c9d28: move a1,v0 */ set(5,cpu(2));
/* 001c9d2c: lw a3,0x20(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000020)));
/* 001c9d30: move a0,s0 */ set(4,cpu(16));
/* 001c9d34: addiu v1,v1,0x8 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000008)));
/* 001c9d38: move a2,s1 */ set(6,cpu(17));
/* 001c9d3c: sw v1,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(3));
/* 001c9d40: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001c9d44: lw v0,0xc(a3) */ lw(2,ea(7,(int32_t)UINT32_C(0x0000000c)));
/* 001c9d48: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001c9d4c: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001c9d50: addiu v0,v0,0x8 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000008)));
/* 001c9d54: sw v0,0xc(a3) */ sw(ea(7,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(2));
/* 001c9d58: j 0x001c9b58 */ /* delay 001c9d5c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_001c9b58();return;
}
static void body_001cdd78(void){
uint64_t incoming=cpu(31);
/* 001cdd78: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001cdd7c: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001cdd80: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cdd84: move s3,a1 */ set(19,cpu(5));
/* 001cdd88: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cdd8c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cdd90: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cdd94: bltz a0,0x001cde38 */ {int taken=((int64_t)cpu(4)<0);/* delay 001cdd98 */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));if(taken){goto L_001cde38;}}
/* 001cdd9c: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001cdda0: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001cdda4: lui s1,0x57 */ set(17,sx(UINT32_C(0x00570000)));
/* 001cdda8: addu s1,s1,v0 */ set(17,sx((uint32_t)cpu(17)+(uint32_t)cpu(2)));
/* 001cddac: lw s1,-0x4174(s1) */ lw(17,ea(17,(int32_t)UINT32_C(0xffffbe8c)));
/* 001cddb0: addiu s0,s1,0x24 */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0x00000024)));
/* 001cddb4: addiu s2,s1,0x14 */ set(18,sx((uint32_t)cpu(17)+UINT32_C(0x00000014)));
/* 001cddb8: lw v0,0xc(s0) */ lw(2,ea(16,(int32_t)UINT32_C(0x0000000c)));
/* 001cddbc: beq v0,zero,0x001cddd0 */ {int taken=(cpu(2)==cpu(0));/* delay 001cddc0 */ set(4,cpu(2));if(taken){goto L_001cddd0;}}
/* 001cddc4: jal 0x001c6ff8 */ set(31,UINT64_C(0x001cddcc));/* delay 001cddc8 */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c6ff8),UINT32_C(0x001cddc4));
/* 001cddcc: sw zero,0xc(s0) */ sw(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
L_001cddd0:;
/* 001cddd0: move a0,s0 */ set(4,cpu(16));
/* 001cddd4: jal 0x001cfc80 */ set(31,UINT64_C(0x001cdddc));/* delay 001cddd8 */ set(5,cpu(0));body_001cfc80();
/* 001cdddc: li a0,-0x8 */ set(4,sx(UINT32_C(0xfffffff8)));
/* 001cdde0: lw v0,0x0(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001cdde4: lui v1,0xfffd */ set(3,sx(UINT32_C(0xfffd0000)));
/* 001cdde8: ori v1,v1,0xffff */ set(3,cpu(3)|UINT32_C(0x0000ffff));
/* 001cddec: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 001cddf0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 001cddf4: beq s3,zero,0x001cde38 */ {int taken=(cpu(19)==cpu(0));/* delay 001cddf8 */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));if(taken){goto L_001cde38;}}
/* 001cddfc: lw v0,0x8(s2) */ lw(2,ea(18,(int32_t)UINT32_C(0x00000008)));
/* 001cde00: beq v0,zero,0x001cde14 */ {int taken=(cpu(2)==cpu(0));/* delay 001cde04 */ set(4,cpu(2));if(taken){goto L_001cde14;}}
/* 001cde08: jal 0x001c6ff8 */ set(31,UINT64_C(0x001cde10));/* delay 001cde0c */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x001c6ff8),UINT32_C(0x001cde08));
/* 001cde10: sw zero,0x8(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
L_001cde14:;
/* 001cde14: move a0,s2 */ set(4,cpu(18));
/* 001cde18: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cde1c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cde20: move a1,zero */ set(5,cpu(0));
/* 001cde24: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cde28: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cde2c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cde30: j 0x001cfc58 */ /* delay 001cde34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(cpu(31),incoming);body_001cfc58();return;
L_001cde38:;
/* 001cde38: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cde3c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cde40: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cde44: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 001cde48: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 001cde4c: jr ra */ {uint64_t target=cpu(31);/* delay 001cde50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_001ce538(void){
uint64_t incoming=cpu(31);
/* 001ce538: move a1,a0 */ set(5,cpu(4));
/* 001ce53c: lw t1,-0x5750(gp) */ lw(9,ea(28,(int32_t)UINT32_C(0xffffa8b0)));
/* 001ce540: addiu a2,a1,0x6650 */ set(6,sx((uint32_t)cpu(5)+UINT32_C(0x00006650)));
/* 001ce544: lui v0,0x57 */ set(2,sx(UINT32_C(0x00570000)));
/* 001ce548: addu v1,t1,a2 */ set(3,sx((uint32_t)cpu(9)+(uint32_t)cpu(6)));
/* 001ce54c: addiu a3,v0,-0x3780 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0xffffc880)));
/* 001ce550: lbu a0,0x4(v1) */ set(4,byte(ea(3,(int32_t)UINT32_C(0x00000004))));
/* 001ce554: move t6,t1 */ set(14,cpu(9));
/* 001ce558: beq a0,zero,0x001ce5dc */ {int taken=(cpu(4)==cpu(0));/* delay 001ce55c */ set(12,cpu(0));if(taken){goto L_001ce5dc;}}
/* 001ce560: sll v0,a1,0x2 */ set(2,sx((uint32_t)cpu(5)<<2));
/* 001ce564: move t5,a2 */ set(13,cpu(6));
/* 001ce568: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 001ce56c: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001ce570: addiu a2,v0,0x6601 */ set(6,sx((uint32_t)cpu(2)+UINT32_C(0x00006601)));
/* 001ce574: addiu a0,v0,0x6600 */ set(4,sx((uint32_t)cpu(2)+UINT32_C(0x00006600)));
/* 001ce578: move t2,a2 */ set(10,cpu(6));
/* 001ce57c: nop  */ 
L_001ce580:;
/* 001ce580: addiu v0,t1,0x4 */ set(2,sx((uint32_t)cpu(9)+UINT32_C(0x00000004)));
/* 001ce584: move t1,t6 */ set(9,cpu(14));
/* 001ce588: addu v1,v0,a0 */ set(3,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001ce58c: addiu a0,a0,0x2 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000002)));
/* 001ce590: lbu v1,0x0(v1) */ set(3,byte(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 001ce594: addu t0,v0,t2 */ set(8,sx((uint32_t)cpu(2)+(uint32_t)cpu(10)));
/* 001ce598: addu a1,v0,a2 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 001ce59c: addiu a2,a2,0x2 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000002)));
/* 001ce5a0: andi v0,v1,0x80 */ set(2,cpu(3)&UINT32_C(0x00000080));
/* 001ce5a4: addu t3,t1,t5 */ set(11,sx((uint32_t)cpu(9)+(uint32_t)cpu(13)));
/* 001ce5a8: beq v0,zero,0x001ce5c0 */ {int taken=(cpu(2)==cpu(0));/* delay 001ce5ac */ set(10,sx((uint32_t)cpu(10)+UINT32_C(0x00000002)));if(taken){goto L_001ce5c0;}}
/* 001ce5b0: sb v1,0x0(a3) */ sb(ea(7,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(3));
/* 001ce5b4: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 001ce5b8: b 0x001ce5c4 */ /* delay 001ce5bc */ set(2,byte(ea(8,(int32_t)UINT32_C(0x00000000))));goto L_001ce5c4;
L_001ce5c0:;
/* 001ce5c0: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
L_001ce5c4:;
/* 001ce5c4: sb v0,0x0(a3) */ sb(ea(7,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001ce5c8: lbu v0,0x4(t3) */ set(2,byte(ea(11,(int32_t)UINT32_C(0x00000004))));
/* 001ce5cc: addiu t4,t4,0x1 */ set(12,sx((uint32_t)cpu(12)+UINT32_C(0x00000001)));
/* 001ce5d0: slt v0,t4,v0 */ set(2,(int64_t)cpu(12)<(int64_t)cpu(2));
/* 001ce5d4: bne v0,zero,0x001ce580 */ {int taken=(cpu(2)!=cpu(0));/* delay 001ce5d8 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));if(taken){goto L_001ce580;}}
L_001ce5dc:;
/* 001ce5dc: jr ra */ {uint64_t target=cpu(31);/* delay 001ce5e0 */ sb(ea(7,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_001ce5e8(void){
uint64_t incoming=cpu(31);
/* 001ce5e8: addiu sp,sp,-0x70 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff90)));
/* 001ce5ec: sltiu v0,a3,0xb */ set(2,cpu(7)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000b));
/* 001ce5f0: sd s1,0x58(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001ce5f4: move s1,a0 */ set(17,cpu(4));
/* 001ce5f8: sd s2,0x60(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001ce5fc: move s2,a1 */ set(18,cpu(5));
/* 001ce600: sd s0,0x50(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 001ce604: move a0,a2 */ set(4,cpu(6));
/* 001ce608: beq v0,zero,0x001ce7c0 */ {int taken=(cpu(2)==cpu(0));/* delay 001ce60c */ save(31,ea(29,(int32_t)UINT32_C(0x00000068)));if(taken){goto L_001ce7c0;}}
/* 001ce610: sll v0,a3,0x2 */ set(2,sx((uint32_t)cpu(7)<<2));
/* 001ce614: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 001ce618: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 001ce61c: lw v1,0x5ae0(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00005ae0)));
/* 001ce620: jr v1 */ {uint64_t target=cpu(3);/* delay 001ce624 */ switch((uint32_t)target){case UINT32_C(0x001ce628):goto L_001ce628;case UINT32_C(0x001ce658):goto L_001ce658;case UINT32_C(0x001ce670):goto L_001ce670;case UINT32_C(0x001ce688):goto L_001ce688;case UINT32_C(0x001ce6a0):goto L_001ce6a0;case UINT32_C(0x001ce708):goto L_001ce708;case UINT32_C(0x001ce720):goto L_001ce720;case UINT32_C(0x001ce748):goto L_001ce748;case UINT32_C(0x001ce770):goto L_001ce770;case UINT32_C(0x001ce798):goto L_001ce798;case UINT32_C(0x001ce7c0):goto L_001ce7c0;default:abort();}}
L_001ce628:;
/* 001ce628: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 001ce62c: move a2,a0 */ set(6,cpu(4));
/* 001ce630: addiu a1,a1,-0xb40 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xfffff4c0)));
/* 001ce634: jal 0x002d5690 */ set(31,UINT64_C(0x001ce63c));/* delay 001ce638 */ set(4,cpu(29));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d5690),UINT32_C(0x001ce634));
/* 001ce63c: move a0,s1 */ set(4,cpu(17));
/* 001ce640: move a1,s2 */ set(5,cpu(18));
/* 001ce644: jal 0x001ce7d8 */ set(31,UINT64_C(0x001ce64c));/* delay 001ce648 */ set(6,cpu(29));body_001ce7d8();
/* 001ce64c: b 0x001ce7c4 */ /* delay 001ce650 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_001ce7c4;
L_001ce658:;
/* 001ce658: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001ce65c: lui a2,0x3e */ set(6,sx(UINT32_C(0x003e0000)));
/* 001ce660: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001ce664: lw a2,0x7328(a2) */ lw(6,ea(6,(int32_t)UINT32_C(0x00007328)));
/* 001ce668: b 0x001ce784 */ /* delay 001ce66c */ set(4,cpu(17));goto L_001ce784;
L_001ce670:;
/* 001ce670: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001ce674: lui a2,0x3e */ set(6,sx(UINT32_C(0x003e0000)));
/* 001ce678: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001ce67c: lw a2,0x7930(a2) */ lw(6,ea(6,(int32_t)UINT32_C(0x00007930)));
/* 001ce680: b 0x001ce784 */ /* delay 001ce684 */ set(4,cpu(17));goto L_001ce784;
L_001ce688:;
/* 001ce688: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001ce68c: lui a2,0x3f */ set(6,sx(UINT32_C(0x003f0000)));
/* 001ce690: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001ce694: lw a2,-0x7e90(a2) */ lw(6,ea(6,(int32_t)UINT32_C(0xffff8170)));
/* 001ce698: b 0x001ce784 */ /* delay 001ce69c */ set(4,cpu(17));goto L_001ce784;
L_001ce6a0:;
/* 001ce6a0: addiu s0,sp,0x10 */ set(16,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 001ce6a4: slti v0,a0,0x3e9 */ set(2,(int64_t)cpu(4)<(int64_t)(int32_t)UINT32_C(0x000003e9));
/* 001ce6a8: bne v0,zero,0x001ce6c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 001ce6ac */ set(5,cpu(16));if(taken){goto L_001ce6c0;}}
/* 001ce6b0: li v0,0x52 */ set(2,sx(UINT32_C(0x00000052)));
/* 001ce6b4: sb v0,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001ce6b8: b 0x001ce6ec */ /* delay 001ce6bc */ sb(ea(29,(int32_t)UINT32_C(0x00000011)),(uint8_t)cpu(0));goto L_001ce6ec;
L_001ce6c0:;
/* 001ce6c0: bgez a0,0x001ce6d4 */ {int taken=((int64_t)cpu(4)>=0);/* delay 001ce6c4 */ set(2,sx(UINT32_C(0x00000042)));if(taken){goto L_001ce6d4;}}
/* 001ce6c8: subu a0,zero,a0 */ set(4,sx((uint32_t)cpu(0)-(uint32_t)cpu(4)));
/* 001ce6cc: sb v0,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001ce6d0: addiu a1,sp,0x11 */ set(5,sx((uint32_t)cpu(29)+UINT32_C(0x00000011)));
L_001ce6d4:;
/* 001ce6d4: jal 0x001cfe48 */ set(31,UINT64_C(0x001ce6dc));/* delay 001ce6d8 */ body_001cfe48();
/* 001ce6dc: move a1,v0 */ set(5,cpu(2));
/* 001ce6e0: li v0,0x46 */ set(2,sx(UINT32_C(0x00000046)));
/* 001ce6e4: sb v0,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001ce6e8: sb zero,0x1(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000001)),(uint8_t)cpu(0));
L_001ce6ec:;
/* 001ce6ec: move a0,s1 */ set(4,cpu(17));
/* 001ce6f0: move a1,s2 */ set(5,cpu(18));
/* 001ce6f4: jal 0x001ce7d8 */ set(31,UINT64_C(0x001ce6fc));/* delay 001ce6f8 */ set(6,cpu(16));body_001ce7d8();
/* 001ce6fc: b 0x001ce7c4 */ /* delay 001ce700 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_001ce7c4;
L_001ce708:;
/* 001ce708: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001ce70c: lui a2,0x3f */ set(6,sx(UINT32_C(0x003f0000)));
/* 001ce710: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001ce714: lw a2,-0x7c10(a2) */ lw(6,ea(6,(int32_t)UINT32_C(0xffff83f0)));
/* 001ce718: b 0x001ce784 */ /* delay 001ce71c */ set(4,cpu(17));goto L_001ce784;
L_001ce720:;
/* 001ce720: sll a2,a0,0x5 */ set(6,sx((uint32_t)cpu(4)<<5));
/* 001ce724: move a0,s1 */ set(4,cpu(17));
/* 001ce728: lui at,0x31 */ set(1,sx(UINT32_C(0x00310000)));
/* 001ce72c: addiu at,at,0x1450 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00001450)));
/* 001ce730: addu a2,at,a2 */ set(6,sx((uint32_t)cpu(1)+(uint32_t)cpu(6)));
/* 001ce734: jal 0x001ce7d8 */ set(31,UINT64_C(0x001ce73c));/* delay 001ce738 */ set(5,cpu(18));body_001ce7d8();
/* 001ce73c: b 0x001ce7c4 */ /* delay 001ce740 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_001ce7c4;
L_001ce748:;
/* 001ce748: sll a2,a0,0x5 */ set(6,sx((uint32_t)cpu(4)<<5));
/* 001ce74c: move a0,s1 */ set(4,cpu(17));
/* 001ce750: lui at,0x31 */ set(1,sx(UINT32_C(0x00310000)));
/* 001ce754: addiu at,at,0x1850 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0x00001850)));
/* 001ce758: addu a2,at,a2 */ set(6,sx((uint32_t)cpu(1)+(uint32_t)cpu(6)));
/* 001ce75c: jal 0x001ce7d8 */ set(31,UINT64_C(0x001ce764));/* delay 001ce760 */ set(5,cpu(18));body_001ce7d8();
/* 001ce764: b 0x001ce7c4 */ /* delay 001ce768 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_001ce7c4;
L_001ce770:;
/* 001ce770: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001ce774: move a0,s1 */ set(4,cpu(17));
/* 001ce778: lui a2,0x3f */ set(6,sx(UINT32_C(0x003f0000)));
/* 001ce77c: addu a2,a2,v0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(2)));
/* 001ce780: lw a2,-0x73d0(a2) */ lw(6,ea(6,(int32_t)UINT32_C(0xffff8c30)));
L_001ce784:;
/* 001ce784: jal 0x001ce7d8 */ set(31,UINT64_C(0x001ce78c));/* delay 001ce788 */ set(5,cpu(18));body_001ce7d8();
/* 001ce78c: b 0x001ce7c4 */ /* delay 001ce790 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));goto L_001ce7c4;
L_001ce798:;
/* 001ce798: jal 0x001ce538 */ set(31,UINT64_C(0x001ce7a0));/* delay 001ce79c */ set(16,sx(UINT32_C(0x00570000)));body_001ce538();
/* 001ce7a0: addiu s0,s0,-0x3780 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0xffffc880)));
/* 001ce7a4: jal 0x002d5d0c */ set(31,UINT64_C(0x001ce7ac));/* delay 001ce7a8 */ set(4,cpu(16));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d5d0c),UINT32_C(0x001ce7a4));
/* 001ce7ac: move a0,s1 */ set(4,cpu(17));
/* 001ce7b0: move a1,s2 */ set(5,cpu(18));
/* 001ce7b4: move a2,s0 */ set(6,cpu(16));
/* 001ce7b8: jal 0x001ce808 */ set(31,UINT64_C(0x001ce7c0));/* delay 001ce7bc */ set(7,cpu(2));body_001ce808();
L_001ce7c0:;
/* 001ce7c0: ld s0,0x50(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000050)));
L_001ce7c4:;
/* 001ce7c4: ld s1,0x58(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000058)));
/* 001ce7c8: ld s2,0x60(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 001ce7cc: ld ra,0x68(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000068)));
/* 001ce7d0: jr ra */ {uint64_t target=cpu(31);/* delay 001ce7d4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000070)));checkReturn(target,incoming);return;}
}
static void body_001ce808(void){
uint64_t incoming=cpu(31);
/* 001ce808: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 001ce80c: sll v0,a0,0x2 */ set(2,sx((uint32_t)cpu(4)<<2));
/* 001ce810: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ce814: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 001ce818: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 001ce81c: lui a0,0x57 */ set(4,sx(UINT32_C(0x00570000)));
/* 001ce820: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 001ce824: lw a0,-0x4174(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0xffffbe8c)));
/* 001ce828: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001ce82c: j 0x001cf320 */ /* delay 001ce830 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_001cf320();return;
}
static void body_001cf178(void){
uint64_t incoming=cpu(31);
/* 001cf178: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 001cf17c: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 001cf180: addiu v0,v0,0x20 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000020)));
/* 001cf184: jr ra */ {uint64_t target=cpu(31);/* delay 001cf188 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));checkReturn(target,incoming);return;}
}
static void body_001cf1a8(void){
uint64_t incoming=cpu(31);
/* 001cf1a8: bltz a1,0x001cf1bc */ {int taken=((int64_t)cpu(5)<0);/* delay 001cf1ac */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000018))));if(taken){goto L_001cf1bc;}}
/* 001cf1b0: slt v0,a1,v0 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(2));
/* 001cf1b4: bne v0,zero,0x001cf1c8 */ {int taken=(cpu(2)!=cpu(0));/* delay 001cf1b8 */ set(3,sx((uint32_t)cpu(5)<<2));if(taken){goto L_001cf1c8;}}
L_001cf1bc:;
/* 001cf1bc: jr ra */ {uint64_t target=cpu(31);/* delay 001cf1c0 */ set(2,cpu(0));checkReturn(target,incoming);return;}
L_001cf1c8:;
/* 001cf1c8: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 001cf1cc: jr ra */ {uint64_t target=cpu(31);/* delay 001cf1d0 */ lw(2,ea(3,(int32_t)UINT32_C(0x0000001c)));checkReturn(target,incoming);return;}
}
static void body_001cf440(void){
uint64_t incoming=cpu(31);
/* 001cf440: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 001cf444: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cf448: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf44c: move s0,zero */ set(16,cpu(0));
/* 001cf450: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf454: move s1,a0 */ set(17,cpu(4));
/* 001cf458: lw a1,0x0(s1) */ lw(5,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 001cf45c: nop  */ 
L_001cf460:;
/* 001cf460: addiu s1,s1,0x4 */ set(17,sx((uint32_t)cpu(17)+UINT32_C(0x00000004)));
/* 001cf464: move a0,s0 */ set(4,cpu(16));
/* 001cf468: jal 0x001c9230 */ set(31,UINT64_C(0x001cf470));/* delay 001cf46c */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));body_001c9230();
/* 001cf470: slti v0,s0,0x20 */ set(2,(int64_t)cpu(16)<(int64_t)(int32_t)UINT32_C(0x00000020));
/* 001cf474: bnel v0,zero,0x001cf460 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 001cf478 */ lw(5,ea(17,(int32_t)UINT32_C(0x00000000)));goto L_001cf460;}}
/* 001cf47c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 001cf480: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 001cf484: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 001cf488: jr ra */ {uint64_t target=cpu(31);/* delay 001cf48c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_001cfc58(void){
uint64_t incoming=cpu(31);
/* 001cfc58: beq a1,zero,0x001cfc6c */ {int taken=(cpu(5)==cpu(0));/* delay 001cfc5c */ set(3,sx(UINT32_C(0x000009b0)));if(taken){goto L_001cfc6c;}}
/* 001cfc60: li v0,0x430 */ set(2,sx(UINT32_C(0x00000430)));
/* 001cfc64: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001cfc68: sw v1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
L_001cfc6c:;
/* 001cfc6c: li v0,-0x1 */ set(2,sx(UINT32_C(0xffffffff)));
/* 001cfc70: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001cfc74: jr ra */ {uint64_t target=cpu(31);/* delay 001cfc78 */ sh(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_001cfc80(void){
uint64_t incoming=cpu(31);
/* 001cfc80: beq a1,zero,0x001cfc94 */ {int taken=(cpu(5)==cpu(0));/* delay 001cfc84 */ set(3,sx(UINT32_C(0x00000a88)));if(taken){goto L_001cfc94;}}
/* 001cfc88: li v0,0x4b0 */ set(2,sx(UINT32_C(0x000004b0)));
/* 001cfc8c: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 001cfc90: sw v1,0x4(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(3));
L_001cfc94:;
/* 001cfc94: li v0,-0x80 */ set(2,sx(UINT32_C(0xffffff80)));
/* 001cfc98: sw zero,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(0));
/* 001cfc9c: sb v0,0x15(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000015)),(uint8_t)cpu(2));
/* 001cfca0: sw zero,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));
/* 001cfca4: sb zero,0x10(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000010)),(uint8_t)cpu(0));
/* 001cfca8: sb zero,0x11(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000011)),(uint8_t)cpu(0));
/* 001cfcac: sh zero,0x16(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000016)),(uint16_t)cpu(0));
/* 001cfcb0: sh zero,0x18(a0) */ sh(ea(4,(int32_t)UINT32_C(0x00000018)),(uint16_t)cpu(0));
/* 001cfcb4: sh zero,0x1a(a0) */ sh(ea(4,(int32_t)UINT32_C(0x0000001a)),(uint16_t)cpu(0));
/* 001cfcb8: sb zero,0x12(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000012)),(uint8_t)cpu(0));
/* 001cfcbc: sb zero,0x13(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000013)),(uint8_t)cpu(0));
/* 001cfcc0: jr ra */ {uint64_t target=cpu(31);/* delay 001cfcc4 */ sb(ea(4,(int32_t)UINT32_C(0x00000014)),(uint8_t)cpu(0));checkReturn(target,incoming);return;}
}
static void body_001cfe48(void){
uint64_t incoming=cpu(31);
/* 001cfe48: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 001cfe4c: move v0,a0 */ set(2,cpu(4));
/* 001cfe50: move a3,zero */ set(7,cpu(0));
/* 001cfe54: li a2,0xa */ set(6,sx(UINT32_C(0x0000000a)));
/* 001cfe58: move t0,sp */ set(8,cpu(29));
/* 001cfe5c: div v0,a2 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(6),1,0);
L_001cfe60:;
/* 001cfe60: addiu a3,a3,0x1 */ set(7,sx((uint32_t)cpu(7)+UINT32_C(0x00000001)));
/* 001cfe64: beql a2,zero,0x001cfe6c */ {int taken=(cpu(6)==cpu(0));if(taken){/* delay 001cfe68 */ nocturneBattlePanelColorCallerTrap(7u,UINT32_C(0x001cfe68));goto L_001cfe6c;}}
L_001cfe6c:;
/* 001cfe6c: slti a0,a3,0xa */ set(4,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x0000000a));
/* 001cfe70: mfhi v1 */ set(3,nocturneEffectHostHi());
/* 001cfe74: mflo v0 */ set(2,nocturneEffectHostLo());
/* 001cfe78: sw v1,0x0(t0) */ sw(ea(8,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(3));
/* 001cfe7c: blez v0,0x001cfe8c */ {int taken=((int64_t)cpu(2)<=0);/* delay 001cfe80 */ set(8,sx((uint32_t)cpu(8)+UINT32_C(0x00000004)));if(taken){goto L_001cfe8c;}}
/* 001cfe84: bnel a0,zero,0x001cfe60 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 001cfe88 */ nativeDivide((uint32_t)cpu(2),(uint32_t)cpu(6),1,0);goto L_001cfe60;}}
L_001cfe8c:;
/* 001cfe8c: addiu v1,a3,-0x1 */ set(3,sx((uint32_t)cpu(7)+UINT32_C(0xffffffff)));
/* 001cfe90: bltz v1,0x001cfebc */ {int taken=((int64_t)cpu(3)<0);/* delay 001cfe94 */ set(2,sx((uint32_t)cpu(3)<<2));if(taken){goto L_001cfebc;}}
/* 001cfe98: addu a0,v0,sp */ set(4,sx((uint32_t)cpu(2)+(uint32_t)cpu(29)));
/* 001cfe9c: nop  */ 
L_001cfea0:;
/* 001cfea0: lbu v0,0x0(a0) */ set(2,byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 001cfea4: addiu a0,a0,-0x4 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xfffffffc)));
/* 001cfea8: addiu v1,v1,-0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0xffffffff)));
/* 001cfeac: addiu v0,v0,0x30 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000030)));
/* 001cfeb0: sb v0,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 001cfeb4: bgez v1,0x001cfea0 */ {int taken=((int64_t)cpu(3)>=0);/* delay 001cfeb8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));if(taken){goto L_001cfea0;}}
L_001cfebc:;
/* 001cfebc: move v0,a1 */ set(2,cpu(5));
/* 001cfec0: sb zero,0x0(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(0));
/* 001cfec4: jr ra */ {uint64_t target=cpu(31);/* delay 001cfec8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002262e8(void){
uint64_t incoming=cpu(31);
/* 002262e8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002262ec: lui v0,0x55 */ set(2,sx(UINT32_C(0x00550000)));
/* 002262f0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002262f4: addiu t0,v0,-0x2e8 */ set(8,sx((uint32_t)cpu(2)+UINT32_C(0xfffffd18)));
/* 002262f8: ldl v1,0x7(t0) */ loadPartial(3,ea(8,(int32_t)UINT32_C(0x00000007)),1);
/* 002262fc: ldr v1,0x0(t0) */ loadPartial(3,ea(8,(int32_t)UINT32_C(0x00000000)),0);
/* 00226300: sdl v1,0x7(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000007)),3,1);
/* 00226304: sdr v1,0x0(a0) */ storePartial(ea(4,(int32_t)UINT32_C(0x00000000)),3,0);
/* 00226308: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0022630c: j 0x002d57f8 */ /* delay 00226310 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);body_002d57f8();return;
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
static void body_00245c90(void){
uint64_t incoming=cpu(31);
/* 00245c90: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00245c94: move v0,a0 */ set(2,cpu(4));
/* 00245c98: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00245c9c: li a1,0x1 */ set(5,sx(UINT32_C(0x00000001)));
/* 00245ca0: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00245ca4: move a0,zero */ set(4,cpu(0));
/* 00245ca8: addiu t2,v1,0x3170 */ set(10,sx((uint32_t)cpu(3)+UINT32_C(0x00003170)));
/* 00245cac: ldl a3,0x7(t2) */ loadPartial(7,ea(10,(int32_t)UINT32_C(0x00000007)),1);
/* 00245cb0: ldr a3,0x0(t2) */ loadPartial(7,ea(10,(int32_t)UINT32_C(0x00000000)),0);
/* 00245cb4: ldl t0,0xf(t2) */ loadPartial(8,ea(10,(int32_t)UINT32_C(0x0000000f)),1);
/* 00245cb8: ldr t0,0x8(t2) */ loadPartial(8,ea(10,(int32_t)UINT32_C(0x00000008)),0);
/* 00245cbc: ldl t1,0x17(t2) */ loadPartial(9,ea(10,(int32_t)UINT32_C(0x00000017)),1);
/* 00245cc0: ldr t1,0x10(t2) */ loadPartial(9,ea(10,(int32_t)UINT32_C(0x00000010)),0);
/* 00245cc4: sdl a3,0x7(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000007)),7,1);
/* 00245cc8: sdr a3,0x0(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000000)),7,0);
/* 00245ccc: sdl t0,0xf(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x0000000f)),8,1);
/* 00245cd0: sdr t0,0x8(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000008)),8,0);
/* 00245cd4: sdl t1,0x17(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000017)),9,1);
/* 00245cd8: sdr t1,0x10(sp) */ storePartial(ea(29,(int32_t)UINT32_C(0x00000010)),9,0);
/* 00245cdc: bne v0,a1,0x00245d00 */ {int taken=(cpu(2)!=cpu(5));/* delay 00245ce0 */ set(6,sx((uint32_t)cpu(2)<<3));if(taken){goto L_00245d00;}}
/* 00245ce4: jal 0x002c0c60 */ set(31,UINT64_C(0x00245cec));/* delay 00245ce8 */ set(5,sx(UINT32_C(0x00000006)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002c0c60),UINT32_C(0x00245ce4));
/* 00245cec: sll v0,v0,0x2 */ set(2,sx((uint32_t)cpu(2)<<2));
/* 00245cf0: addu v1,sp,v0 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(2)));
/* 00245cf4: b 0x00245d0c */ /* delay 00245cf8 */ lw(2,ea(3,(int32_t)UINT32_C(0x00000000)));goto L_00245d0c;
L_00245d00:;
/* 00245d00: lui v0,0x3e */ set(2,sx(UINT32_C(0x003e0000)));
/* 00245d04: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 00245d08: lhu v0,-0x3b5e(v0) */ set(2,half(ea(2,(int32_t)UINT32_C(0xffffc4a2))));
L_00245d0c:;
/* 00245d0c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00245d10: jr ra */ {uint64_t target=cpu(31);/* delay 00245d14 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002514f0(void){
uint64_t incoming=cpu(31);
/* 002514f0: li a1,0x80 */ set(5,sx(UINT32_C(0x00000080)));
/* 002514f4: addiu t1,a0,0xc */ set(9,sx((uint32_t)cpu(4)+UINT32_C(0x0000000c)));
/* 002514f8: addiu t0,a0,0x8 */ set(8,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
/* 002514fc: addiu a3,a0,0xa */ set(7,sx((uint32_t)cpu(4)+UINT32_C(0x0000000a)));
/* 00251500: li a2,0x1f */ set(6,sx(UINT32_C(0x0000001f)));
/* 00251504: nop  */ 
L_00251508:;
/* 00251508: addu v0,t0,a1 */ set(2,sx((uint32_t)cpu(8)+(uint32_t)cpu(5)));
/* 0025150c: addu v1,a3,a1 */ set(3,sx((uint32_t)cpu(7)+(uint32_t)cpu(5)));
/* 00251510: addu a0,t1,a1 */ set(4,sx((uint32_t)cpu(9)+(uint32_t)cpu(5)));
/* 00251514: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 00251518: addiu a2,a2,-0x1 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0xffffffff)));
/* 0025151c: sh zero,0x0(v0) */ sh(ea(2,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(0));
/* 00251520: sh zero,0x0(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(0));
/* 00251524: bgez a2,0x00251508 */ {int taken=((int64_t)cpu(6)>=0);/* delay 00251528 */ sh(ea(4,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(0));if(taken){goto L_00251508;}}
/* 0025152c: jr ra */ {uint64_t target=cpu(31);/* delay 00251530 */ checkReturn(target,incoming);return;}
}
static void body_00251538(void){
uint64_t incoming=cpu(31);
/* 00251538: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0025153c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00251540: move s1,a0 */ set(17,cpu(4));
/* 00251544: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00251548: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025154c: addiu s0,s1,0x8c */ set(16,sx((uint32_t)cpu(17)+UINT32_C(0x0000008c)));
/* 00251550: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00251554: li s2,0xf */ set(18,sx(UINT32_C(0x0000000f)));
/* 00251558: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025155c: move s3,zero */ set(19,cpu(0));
L_00251560:;
/* 00251560: lw a2,0x0(s1) */ lw(6,ea(17,(int32_t)UINT32_C(0x00000000)));
/* 00251564: sh zero,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(0));
/* 00251568: lw v0,0x0(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 0025156c: addu a0,s3,v0 */ set(4,sx((uint32_t)cpu(19)+(uint32_t)cpu(2)));
/* 00251570: lw v0,0x78(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000078)));
/* 00251574: andi v1,v0,0x40 */ set(3,cpu(2)&UINT32_C(0x00000040));
/* 00251578: andi v0,v0,0x1 */ set(2,cpu(2)&UINT32_C(0x00000001));
/* 0025157c: beq v0,zero,0x002515ac */ {int taken=(cpu(2)==cpu(0));/* delay 00251580 */ set(19,sx((uint32_t)cpu(19)+UINT32_C(0x000000f0)));if(taken){goto L_002515ac;}}
/* 00251584: beql v1,zero,0x002515b0 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 00251588 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));goto L_002515b0;}}
/* 0025158c: lh a1,0x90(a0) */ set(5,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000090))));
/* 00251590: move a0,a2 */ set(4,cpu(6));
/* 00251594: lw v0,0x10(a2) */ lw(2,ea(6,(int32_t)UINT32_C(0x00000010)));
/* 00251598: sll a1,a1,0x7 */ set(5,sx((uint32_t)cpu(5)<<7));
/* 0025159c: jal 0x002469c0 */ set(31,UINT64_C(0x002515a4));/* delay 002515a0 */ set(5,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));body_002469c0();
/* 002515a4: lhu v1,0x6(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000006))));
/* 002515a8: sh v1,0x0(s0) */ sh(ea(16,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(3));
L_002515ac:;
/* 002515ac: addiu s2,s2,-0x1 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0xffffffff)));
L_002515b0:;
/* 002515b0: bgez s2,0x00251560 */ {int taken=((int64_t)cpu(18)>=0);/* delay 002515b4 */ set(16,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));if(taken){goto L_00251560;}}
/* 002515b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002515bc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002515c0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002515c4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002515c8: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002515cc: jr ra */ {uint64_t target=cpu(31);/* delay 002515d0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002517e0(void){
uint64_t incoming=cpu(31);
/* 002517e0: sll a1,a1,0x3 */ set(5,sx((uint32_t)cpu(5)<<3));
/* 002517e4: addiu v1,a0,0xa */ set(3,sx((uint32_t)cpu(4)+UINT32_C(0x0000000a)));
/* 002517e8: addiu v0,a1,0x80 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000080)));
/* 002517ec: addiu a0,a0,0x8 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000008)));
/* 002517f0: addu t1,a0,v0 */ set(9,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 002517f4: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 002517f8: move a0,t1 */ set(4,cpu(9));
/* 002517fc: lhu a1,0x0(a0) */ set(5,half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 00251800: slt v0,a2,a1 */ set(2,(int64_t)cpu(6)<(int64_t)cpu(5));
/* 00251804: bltz a3,0x0025181c */ {int taken=((int64_t)cpu(7)<0);/* delay 00251808 */ if(cpu(2)!=0){set(6,cpu(5));}if(taken){goto L_0025181c;}}
/* 0025180c: addu a3,a2,a3 */ set(7,sx((uint32_t)cpu(6)+(uint32_t)cpu(7)));
/* 00251810: slt v0,a1,a3 */ set(2,(int64_t)cpu(5)<(int64_t)cpu(7));
/* 00251814: bnel v0,zero,0x0025181c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251818 */ sh(ea(4,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(7));goto L_0025181c;}}
L_0025181c:;
/* 0025181c: bltz t0,0x0025184c */ {int taken=((int64_t)cpu(8)<0);/* delay 00251820 */ if(taken){goto L_0025184c;}}
/* 00251824: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00251828: addu a2,a2,t0 */ set(6,sx((uint32_t)cpu(6)+(uint32_t)cpu(8)));
/* 0025182c: slt v0,v0,a2 */ set(2,(int64_t)cpu(2)<(int64_t)cpu(6));
/* 00251830: bnel v0,zero,0x00251838 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251834 */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(6));goto L_00251838;}}
L_00251838:;
/* 00251838: lhu a0,0x0(t1) */ set(4,half(ea(9,(int32_t)UINT32_C(0x00000000))));
/* 0025183c: lhu v0,0x0(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00251840: sltu v0,v0,a0 */ set(2,cpu(2)<cpu(4));
/* 00251844: bnel v0,zero,0x0025184c */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 00251848 */ sh(ea(3,(int32_t)UINT32_C(0x00000000)),(uint16_t)cpu(4));goto L_0025184c;}}
L_0025184c:;
/* 0025184c: jr ra */ {uint64_t target=cpu(31);/* delay 00251850 */ checkReturn(target,incoming);return;}
}
static void body_00259300(void){
uint64_t incoming=cpu(31);
/* 00259300: lw v1,0x60(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000060)));
/* 00259304: addiu v0,a1,0x1 */ set(2,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 00259308: andi v1,v1,0x8 */ set(3,cpu(3)&UINT32_C(0x00000008));
/* 0025930c: xori v1,v1,0x0 */ set(3,cpu(3)^UINT32_C(0x00000000));
/* 00259310: jr ra */ {uint64_t target=cpu(31);/* delay 00259314 */ if(cpu(3)==0){set(2,cpu(5));}checkReturn(target,incoming);return;}
}
static void body_0025da78(void){
uint64_t incoming=cpu(31);
/* 0025da78: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0025da7c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025da80: move s0,a1 */ set(16,cpu(5));
/* 0025da84: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025da88: move s1,t0 */ set(17,cpu(8));
/* 0025da8c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025da90: move s2,a3 */ set(18,cpu(7));
/* 0025da94: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025da98: move s3,a2 */ set(19,cpu(6));
/* 0025da9c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0025daa0: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0025daa4: jal 0x0025d690 */ set(31,UINT64_C(0x0025daac));/* delay 0025daa8 */ set(20,cpu(4));body_0025d690();
/* 0025daac: lw a3,0x0(v0) */ lw(7,ea(2,(int32_t)UINT32_C(0x00000000)));
/* 0025dab0: sll v0,s1,0x4 */ set(2,sx((uint32_t)cpu(17)<<4));
/* 0025dab4: subu v0,v0,s1 */ set(2,sx((uint32_t)cpu(2)-(uint32_t)cpu(17)));
/* 0025dab8: li a1,0x2 */ set(5,sx(UINT32_C(0x00000002)));
/* 0025dabc: lw v1,0x60(a3) */ lw(3,ea(7,(int32_t)UINT32_C(0x00000060)));
/* 0025dac0: sll v0,v0,0x4 */ set(2,sx((uint32_t)cpu(2)<<4));
/* 0025dac4: lw a0,0x0(a3) */ lw(4,ea(7,(int32_t)UINT32_C(0x00000000)));
/* 0025dac8: li t0,0x1 */ set(8,sx(UINT32_C(0x00000001)));
/* 0025dacc: andi v1,v1,0x8 */ set(3,cpu(3)&UINT32_C(0x00000008));
/* 0025dad0: addu a0,a0,v0 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(2)));
/* 0025dad4: beq s0,a1,0x0025db48 */ {int taken=(cpu(16)==cpu(5));/* delay 0025dad8 */ set(6,cpu(0)<cpu(3));if(taken){goto L_0025db48;}}
/* 0025dadc: andi v1,s2,0x3 */ set(3,cpu(18)&UINT32_C(0x00000003));
/* 0025dae0: li v0,0x3 */ set(2,sx(UINT32_C(0x00000003)));
/* 0025dae4: beq v1,v0,0x0025db34 */ {int taken=(cpu(3)==cpu(2));/* delay 0025dae8 */ set(8,cpu(0));if(taken){goto L_0025db34;}}
/* 0025daec: andi v0,s2,0x1 */ set(2,cpu(18)&UINT32_C(0x00000001));
/* 0025daf0: beq v0,zero,0x0025db10 */ {int taken=(cpu(2)==cpu(0));/* delay 0025daf4 */ set(2,cpu(18)&UINT32_C(0x00000002));if(taken){goto L_0025db10;}}
/* 0025daf8: beq a2,zero,0x0025db28 */ {int taken=(cpu(6)==cpu(0));/* delay 0025dafc */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0025db28;}}
/* 0025db00: bne a2,v0,0x0025db48 */ {int taken=(cpu(6)!=cpu(2));/* delay 0025db04 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0xfffffffc)));if(taken){goto L_0025db48;}}
/* 0025db08: b 0x0025db2c */ /* delay 0025db0c */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));goto L_0025db2c;
L_0025db10:;
/* 0025db10: beq v0,zero,0x0025db48 */ {int taken=(cpu(2)==cpu(0));/* delay 0025db14 */ if(taken){goto L_0025db48;}}
/* 0025db18: beq a2,zero,0x0025db40 */ {int taken=(cpu(6)==cpu(0));/* delay 0025db1c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0025db40;}}
/* 0025db20: bne a2,v0,0x0025db48 */ {int taken=(cpu(6)!=cpu(2));/* delay 0025db24 */ if(taken){goto L_0025db48;}}
L_0025db28:;
/* 0025db28: slti v0,s1,0x4 */ set(2,(int64_t)cpu(17)<(int64_t)(int32_t)UINT32_C(0x00000004));
L_0025db2c:;
/* 0025db2c: beq v0,zero,0x0025db48 */ {int taken=(cpu(2)==cpu(0));/* delay 0025db30 */ if(taken){goto L_0025db48;}}
L_0025db34:;
/* 0025db34: b 0x0025db48 */ /* delay 0025db38 */ set(8,sx(UINT32_C(0x00000001)));goto L_0025db48;
L_0025db40:;
/* 0025db40: addiu v0,s1,-0x4 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0xfffffffc)));
/* 0025db44: sltiu t0,v0,0xa */ set(8,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000a));
L_0025db48:;
/* 0025db48: beq t0,zero,0x0025dbd8 */ {int taken=(cpu(8)==cpu(0));/* delay 0025db4c */ set(2,cpu(19)&UINT32_C(0x00000001));if(taken){goto L_0025dbd8;}}
/* 0025db50: beq v0,zero,0x0025db5c */ {int taken=(cpu(2)==cpu(0));/* delay 0025db54 */ set(2,cpu(20)^cpu(17));if(taken){goto L_0025db5c;}}
/* 0025db58: sltiu t0,v0,0x1 */ set(8,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_0025db5c:;
/* 0025db5c: beq t0,zero,0x0025dbd8 */ {int taken=(cpu(8)==cpu(0));/* delay 0025db60 */ set(2,cpu(19)&UINT32_C(0x00000002));if(taken){goto L_0025dbd8;}}
/* 0025db64: beq v0,zero,0x0025db70 */ {int taken=(cpu(2)==cpu(0));/* delay 0025db68 */ set(2,cpu(20)^cpu(17));if(taken){goto L_0025db70;}}
/* 0025db6c: sltu t0,zero,v0 */ set(8,cpu(0)<cpu(2));
L_0025db70:;
/* 0025db70: beq t0,zero,0x0025dbdc */ {int taken=(cpu(8)==cpu(0));/* delay 0025db74 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0025dbdc;}}
/* 0025db78: lw v1,0x78(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000078)));
/* 0025db7c: andi v0,v1,0x1 */ set(2,cpu(3)&UINT32_C(0x00000001));
/* 0025db80: bne v0,zero,0x0025db98 */ {int taken=(cpu(2)!=cpu(0));/* delay 0025db84 */ set(2,cpu(19)&UINT32_C(0x00000004));if(taken){goto L_0025db98;}}
/* 0025db88: beq v0,zero,0x0025db98 */ {int taken=(cpu(2)==cpu(0));/* delay 0025db8c */ set(8,cpu(0));if(taken){goto L_0025db98;}}
/* 0025db90: andi v0,v1,0x800 */ set(2,cpu(3)&UINT32_C(0x00000800));
/* 0025db94: sltu t0,zero,v0 */ set(8,cpu(0)<cpu(2));
L_0025db98:;
/* 0025db98: beq t0,zero,0x0025dbd8 */ {int taken=(cpu(8)==cpu(0));/* delay 0025db9c */ set(2,cpu(19)&UINT32_C(0x00000008));if(taken){goto L_0025dbd8;}}
/* 0025dba0: beq v0,zero,0x0025dbac */ {int taken=(cpu(2)==cpu(0));/* delay 0025dba4 */ set(2,cpu(3)&UINT32_C(0x00000001));if(taken){goto L_0025dbac;}}
/* 0025dba8: sltiu t0,v0,0x1 */ set(8,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_0025dbac:;
/* 0025dbac: beq t0,zero,0x0025dbd8 */ {int taken=(cpu(8)==cpu(0));/* delay 0025dbb0 */ set(2,cpu(3)&UINT32_C(0x00000040));if(taken){goto L_0025dbd8;}}
/* 0025dbb4: beq v0,zero,0x0025dbdc */ {int taken=(cpu(2)==cpu(0));/* delay 0025dbb8 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0025dbdc;}}
/* 0025dbbc: lh v0,0x90(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000090))));
/* 0025dbc0: lw a0,0x10(a3) */ lw(4,ea(7,(int32_t)UINT32_C(0x00000010)));
/* 0025dbc4: sll v0,v0,0x7 */ set(2,sx((uint32_t)cpu(2)<<7));
/* 0025dbc8: addu v0,v0,a0 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(4)));
/* 0025dbcc: lhu v1,0x0(v0) */ set(3,half(ea(2,(int32_t)UINT32_C(0x00000000))));
/* 0025dbd0: andi v1,v1,0x38 */ set(3,cpu(3)&UINT32_C(0x00000038));
/* 0025dbd4: movn t0,zero,v1 */ if(cpu(3)!=0){set(8,cpu(0));}
L_0025dbd8:;
/* 0025dbd8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0025dbdc:;
/* 0025dbdc: move v0,t0 */ set(2,cpu(8));
/* 0025dbe0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025dbe4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025dbe8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025dbec: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0025dbf0: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0025dbf4: jr ra */ {uint64_t target=cpu(31);/* delay 0025dbf8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_0025e9c8(void){
uint64_t incoming=cpu(31);
/* 0025e9c8: lw v0,0x8(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000008)));
/* 0025e9cc: beql v0,zero,0x0025e9d4 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025e9d0 */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));goto L_0025e9d4;}}
L_0025e9d4:;
/* 0025e9d4: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 0025e9d8: beql v0,zero,0x0025e9f0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025e9dc */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(5));goto L_0025e9f0;}}
/* 0025e9e0: sw a1,0xc(v0) */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(5));
/* 0025e9e4: lw v0,0xc(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x0000000c)));
/* 0025e9e8: sw v0,0x10(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000010)),(uint32_t)cpu(2));
/* 0025e9ec: sw a1,0xc(a0) */ sw(ea(4,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(5));
L_0025e9f0:;
/* 0025e9f0: lw v0,0x4(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000004)));
/* 0025e9f4: addiu v0,v0,0x1 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 0025e9f8: jr ra */ {uint64_t target=cpu(31);/* delay 0025e9fc */ sw(ea(4,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(2));checkReturn(target,incoming);return;}
}
static void body_0025ef10(void){
uint64_t incoming=cpu(31);
/* 0025ef10: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0025ef14: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025ef18: move s0,a0 */ set(16,cpu(4));
/* 0025ef1c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025ef20: move s1,a2 */ set(17,cpu(6));
/* 0025ef24: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025ef28: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025ef2c: jal 0x002469a0 */ set(31,UINT64_C(0x0025ef34));/* delay 0025ef30 */ set(18,cpu(5));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002469a0),UINT32_C(0x0025ef2c));
/* 0025ef34: jal 0x00101ab0 */ set(31,UINT64_C(0x0025ef3c));/* delay 0025ef38 */ lw(4,ea(2,(int32_t)UINT32_C(0x000000f4)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x00101ab0),UINT32_C(0x0025ef34));
/* 0025ef3c: lw a0,0x8(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000008)));
/* 0025ef40: beq a0,zero,0x0025efb8 */ {int taken=(cpu(4)==cpu(0));/* delay 0025ef44 */ set(2,cpu(0));if(taken){goto L_0025efb8;}}
/* 0025ef48: subu a2,s0,s1 */ set(6,sx((uint32_t)cpu(16)-(uint32_t)cpu(17)));
/* 0025ef4c: li a1,0x19 */ set(5,sx(UINT32_C(0x00000019)));
/* 0025ef50: lh v0,0x0(a0) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 0025ef54: nop  */ 
L_0025ef58:;
/* 0025ef58: slt v1,a2,v0 */ set(3,(int64_t)cpu(6)<(int64_t)cpu(2));
/* 0025ef5c: slt v0,s0,v0 */ set(2,(int64_t)cpu(16)<(int64_t)cpu(2));
/* 0025ef60: bnel v0,zero,0x0025efac */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0025ef64 */ lw(4,ea(4,(int32_t)UINT32_C(0x0000000c)));goto L_0025efac;}}
/* 0025ef68: beql v1,zero,0x0025efac */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 0025ef6c */ lw(4,ea(4,(int32_t)UINT32_C(0x0000000c)));goto L_0025efac;}}
/* 0025ef70: lb v1,0x4(a0) */ set(3,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 0025ef74: beq v1,a1,0x0025ef9c */ {int taken=(cpu(3)==cpu(5));/* delay 0025ef78 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000019));if(taken){goto L_0025ef9c;}}
/* 0025ef7c: bnel v0,zero,0x0025efac */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0025ef80 */ lw(4,ea(4,(int32_t)UINT32_C(0x0000000c)));goto L_0025efac;}}
/* 0025ef84: slti v0,v1,0x1e */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000001e));
/* 0025ef88: beql v0,zero,0x0025efac */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 0025ef8c */ lw(4,ea(4,(int32_t)UINT32_C(0x0000000c)));goto L_0025efac;}}
/* 0025ef90: slti v0,v1,0x1c */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x0000001c));
/* 0025ef94: bnel v0,zero,0x0025efac */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 0025ef98 */ lw(4,ea(4,(int32_t)UINT32_C(0x0000000c)));goto L_0025efac;}}
L_0025ef9c:;
/* 0025ef9c: lw v1,0x28(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 0025efa0: beq v1,s2,0x0025efb8 */ {int taken=(cpu(3)==cpu(18));/* delay 0025efa4 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0025efb8;}}
/* 0025efa8: lw a0,0xc(a0) */ lw(4,ea(4,(int32_t)UINT32_C(0x0000000c)));
L_0025efac:;
/* 0025efac: bnel a0,zero,0x0025ef58 */ {int taken=(cpu(4)!=cpu(0));if(taken){/* delay 0025efb0 */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000000))));goto L_0025ef58;}}
/* 0025efb4: move v0,zero */ set(2,cpu(0));
L_0025efb8:;
/* 0025efb8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025efbc: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025efc0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025efc4: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025efc8: jr ra */ {uint64_t target=cpu(31);/* delay 0025efcc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00261ca0(void){
uint64_t incoming=cpu(31);
/* 00261ca0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00261ca4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261ca8: move s0,a0 */ set(16,cpu(4));
/* 00261cac: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261cb0: move s1,a1 */ set(17,cpu(5));
/* 00261cb4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261cb8: move s2,a3 */ set(18,cpu(7));
/* 00261cbc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261cc0: move s3,t0 */ set(19,cpu(8));
/* 00261cc4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261cc8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00261ccc: jal 0x0025e8e0 */ set(31,UINT64_C(0x00261cd4));/* delay 00261cd0 */ set(20,cpu(6));body_0025e8e0();
/* 00261cd4: move a0,v0 */ set(4,cpu(2));
/* 00261cd8: move a1,s0 */ set(5,cpu(16));
/* 00261cdc: move a3,s1 */ set(7,cpu(17));
/* 00261ce0: jal 0x0025ea48 */ set(31,UINT64_C(0x00261ce8));/* delay 00261ce4 */ set(6,cpu(0));body_0025ea48();
/* 00261ce8: li a0,0x5 */ set(4,sx(UINT32_C(0x00000005)));
/* 00261cec: move v1,v0 */ set(3,cpu(2));
/* 00261cf0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261cf4: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00261cf8: sw s4,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(20));
/* 00261cfc: sw s3,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(19));
/* 00261d00: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261d04: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261d08: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261d0c: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261d10: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00261d14: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00261d18: jr ra */ {uint64_t target=cpu(31);/* delay 00261d1c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00261d20(void){
uint64_t incoming=cpu(31);
/* 00261d20: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00261d24: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261d28: move s0,a0 */ set(16,cpu(4));
/* 00261d2c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261d30: move s1,a1 */ set(17,cpu(5));
/* 00261d34: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261d38: move s2,a3 */ set(18,cpu(7));
/* 00261d3c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261d40: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261d44: jal 0x0025e8e0 */ set(31,UINT64_C(0x00261d4c));/* delay 00261d48 */ set(19,cpu(6));body_0025e8e0();
/* 00261d4c: move a0,v0 */ set(4,cpu(2));
/* 00261d50: move a1,s0 */ set(5,cpu(16));
/* 00261d54: move a3,s1 */ set(7,cpu(17));
/* 00261d58: jal 0x0025ea48 */ set(31,UINT64_C(0x00261d60));/* delay 00261d5c */ set(6,cpu(0));body_0025ea48();
/* 00261d60: li a0,0x6 */ set(4,sx(UINT32_C(0x00000006)));
/* 00261d64: move v1,v0 */ set(3,cpu(2));
/* 00261d68: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261d6c: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00261d70: sw s3,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 00261d74: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261d78: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261d7c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261d80: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261d84: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00261d88: jr ra */ {uint64_t target=cpu(31);/* delay 00261d8c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00262480(void){
uint64_t incoming=cpu(31);
/* 00262480: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00262484: move v0,zero */ set(2,cpu(0));
/* 00262488: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026248c: move s0,zero */ set(16,cpu(0));
/* 00262490: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262494: move s1,a3 */ set(17,cpu(7));
/* 00262498: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026249c: move s3,a2 */ set(19,cpu(6));
/* 002624a0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002624a4: move s4,a1 */ set(20,cpu(5));
/* 002624a8: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002624ac: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002624b0: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002624b4: lw v1,0x78(s3) */ lw(3,ea(19,(int32_t)UINT32_C(0x00000078)));
/* 002624b8: andi v1,v1,0x1 */ set(3,cpu(3)&UINT32_C(0x00000001));
/* 002624bc: beq v1,zero,0x002625e8 */ {int taken=(cpu(3)==cpu(0));/* delay 002624c0 */ set(21,cpu(4));if(taken){goto L_002625e8;}}
/* 002624c4: jal 0x0025e8e0 */ set(31,UINT64_C(0x002624cc));/* delay 002624c8 */ body_0025e8e0();
/* 002624cc: move a1,s5 */ set(5,cpu(21));
/* 002624d0: move a0,v0 */ set(4,cpu(2));
/* 002624d4: move a2,zero */ set(6,cpu(0));
/* 002624d8: jal 0x0025ea48 */ set(31,UINT64_C(0x002624e0));/* delay 002624dc */ set(7,cpu(20));body_0025ea48();
/* 002624e0: li v1,0xf */ set(3,sx(UINT32_C(0x0000000f)));
/* 002624e4: move s2,v0 */ set(18,cpu(2));
/* 002624e8: sltiu a0,s1,0xb */ set(4,cpu(17)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x0000000b));
/* 002624ec: sb v1,0x4(s2) */ sb(ea(18,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 002624f0: sw s3,0x14(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 002624f4: beq a0,zero,0x002625e8 */ {int taken=(cpu(4)==cpu(0));/* delay 002624f8 */ sw(ea(18,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(17));if(taken){goto L_002625e8;}}
/* 002624fc: sll v0,s1,0x2 */ set(2,sx((uint32_t)cpu(17)<<2));
/* 00262500: lui v1,0x54 */ set(3,sx(UINT32_C(0x00540000)));
/* 00262504: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00262508: lw v1,0x4910(v1) */ lw(3,ea(3,(int32_t)UINT32_C(0x00004910)));
/* 0026250c: jr v1 */ {uint64_t target=cpu(3);/* delay 00262510 */ switch((uint32_t)target){case UINT32_C(0x00262518):goto L_00262518;case UINT32_C(0x00262520):goto L_00262520;case UINT32_C(0x00262528):goto L_00262528;case UINT32_C(0x00262538):goto L_00262538;case UINT32_C(0x00262548):goto L_00262548;case UINT32_C(0x00262558):goto L_00262558;case UINT32_C(0x00262568):goto L_00262568;case UINT32_C(0x00262570):goto L_00262570;case UINT32_C(0x00262578):goto L_00262578;case UINT32_C(0x00262588):goto L_00262588;case UINT32_C(0x00262598):goto L_00262598;default:abort();}}
L_00262518:;
/* 00262518: b 0x002625a4 */ /* delay 0026251c */ set(5,sx(UINT32_C(0x00000018)));goto L_002625a4;
L_00262520:;
/* 00262520: b 0x002625a4 */ /* delay 00262524 */ set(5,sx(UINT32_C(0x00000019)));goto L_002625a4;
L_00262528:;
/* 00262528: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
/* 0026252c: li a1,0x11 */ set(5,sx(UINT32_C(0x00000011)));
/* 00262530: b 0x002625a4 */ /* delay 00262534 */ set(16,cpu(16)|UINT32_C(0x00000008));goto L_002625a4;
L_00262538:;
/* 00262538: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
/* 0026253c: li a1,0x12 */ set(5,sx(UINT32_C(0x00000012)));
/* 00262540: b 0x002625a4 */ /* delay 00262544 */ set(16,cpu(16)|UINT32_C(0x00000009));goto L_002625a4;
L_00262548:;
/* 00262548: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
/* 0026254c: li a1,0x1a */ set(5,sx(UINT32_C(0x0000001a)));
/* 00262550: b 0x002625a4 */ /* delay 00262554 */ set(16,cpu(16)|UINT32_C(0x00000001));goto L_002625a4;
L_00262558:;
/* 00262558: li a1,0x14 */ set(5,sx(UINT32_C(0x00000014)));
/* 0026255c: b 0x002625a4 */ /* delay 00262560 */ set(16,sx(UINT32_C(0x00010000)));goto L_002625a4;
L_00262568:;
/* 00262568: b 0x002625a4 */ /* delay 0026256c */ set(5,sx(UINT32_C(0x0000000e)));goto L_002625a4;
L_00262570:;
/* 00262570: b 0x002625e4 */ /* delay 00262574 */ sh(ea(18,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(0));goto L_002625e4;
L_00262578:;
/* 00262578: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
/* 0026257c: li a1,0x1b */ set(5,sx(UINT32_C(0x0000001b)));
/* 00262580: b 0x002625a4 */ /* delay 00262584 */ set(16,cpu(16)|UINT32_C(0x00000005));goto L_002625a4;
L_00262588:;
/* 00262588: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
/* 0026258c: li a1,0x1c */ set(5,sx(UINT32_C(0x0000001c)));
/* 00262590: b 0x002625a4 */ /* delay 00262594 */ set(16,cpu(16)|UINT32_C(0x00000007));goto L_002625a4;
L_00262598:;
/* 00262598: lui s0,0x1 */ set(16,sx(UINT32_C(0x00010000)));
/* 0026259c: li a1,0x1d */ set(5,sx(UINT32_C(0x0000001d)));
/* 002625a0: ori s0,s0,0x6 */ set(16,cpu(16)|UINT32_C(0x00000006));
L_002625a4:;
/* 002625a4: jal 0x00173cb0 */ set(31,UINT64_C(0x002625ac));/* delay 002625a8 */ set(4,cpu(19));body_00173cb0();
/* 002625ac: sw v0,0x2c(s2) */ sw(ea(18,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(2));
/* 002625b0: jal 0x00173ef0 */ set(31,UINT64_C(0x002625b8));/* delay 002625b4 */ set(4,cpu(2));body_00173ef0();
/* 002625b8: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 002625bc: sll a1,v0,0x10 */ set(5,sx((uint32_t)cpu(2)<<16));
/* 002625c0: sh v0,0x2(s2) */ sh(ea(18,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));
/* 002625c4: addiu a0,a0,0x4900 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004900)));
/* 002625c8: jal 0x002d4748 */ set(31,UINT64_C(0x002625d0));/* delay 002625cc */ set(5,sx((uint32_t)((int32_t)cpu(5)>>16)));body_002d4748();
/* 002625d0: beq s0,zero,0x002625e4 */ {int taken=(cpu(16)==cpu(0));/* delay 002625d4 */ set(4,cpu(21));if(taken){goto L_002625e4;}}
/* 002625d8: move a1,s4 */ set(5,cpu(20));
/* 002625dc: jal 0x00262cc0 */ set(31,UINT64_C(0x002625e4));/* delay 002625e0 */ set(6,cpu(16));body_00262cc0();
L_002625e4:;
/* 002625e4: move v0,s2 */ set(2,cpu(18));
L_002625e8:;
/* 002625e8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002625ec: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002625f0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002625f4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002625f8: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002625fc: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262600: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00262604: jr ra */ {uint64_t target=cpu(31);/* delay 00262608 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_00262610(void){
uint64_t incoming=cpu(31);
/* 00262610: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262614: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262618: move s0,a0 */ set(16,cpu(4));
/* 0026261c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262620: move s1,a1 */ set(17,cpu(5));
/* 00262624: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262628: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026262c: jal 0x0025e8e0 */ set(31,UINT64_C(0x00262634));/* delay 00262630 */ set(18,cpu(6));body_0025e8e0();
/* 00262634: move a0,v0 */ set(4,cpu(2));
/* 00262638: move a1,s0 */ set(5,cpu(16));
/* 0026263c: move a3,s1 */ set(7,cpu(17));
/* 00262640: jal 0x0025ea48 */ set(31,UINT64_C(0x00262648));/* delay 00262644 */ set(6,cpu(0));body_0025ea48();
/* 00262648: li a0,0x18 */ set(4,sx(UINT32_C(0x00000018)));
/* 0026264c: move v1,v0 */ set(3,cpu(2));
/* 00262650: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262654: sw s2,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 00262658: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026265c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262660: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262664: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262668: jr ra */ {uint64_t target=cpu(31);/* delay 0026266c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00262a68(void){
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();if(!f)abort();
/* 00262a68: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262a6c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262a70: move s0,a0 */ set(16,cpu(4));
/* 00262a74: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262a78: move s1,a1 */ set(17,cpu(5));
/* 00262a7c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262a80: swc1 f20,0x18(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000018)),f[20]);
/* 00262a84: jal 0x0025e8e0 */ set(31,UINT64_C(0x00262a8c));/* delay 00262a88 */ f[20]=f[12];body_0025e8e0();
/* 00262a8c: move a1,s0 */ set(5,cpu(16));
/* 00262a90: move a3,s1 */ set(7,cpu(17));
/* 00262a94: move a0,v0 */ set(4,cpu(2));
/* 00262a98: jal 0x0025ea48 */ set(31,UINT64_C(0x00262aa0));/* delay 00262a9c */ set(6,cpu(0));body_0025ea48();
/* 00262aa0: li a0,0x12 */ set(4,sx(UINT32_C(0x00000012)));
/* 00262aa4: move v1,v0 */ set(3,cpu(2));
/* 00262aa8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262aac: swc1 f20,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 00262ab0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262ab4: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262ab8: lwc1 f20,0x18(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262abc: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262ac0: jr ra */ {uint64_t target=cpu(31);/* delay 00262ac4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00262ac8(void){
uint64_t incoming=cpu(31);
/* 00262ac8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262acc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262ad0: move s0,a0 */ set(16,cpu(4));
/* 00262ad4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262ad8: move s1,a1 */ set(17,cpu(5));
/* 00262adc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262ae0: move s2,a3 */ set(18,cpu(7));
/* 00262ae4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262ae8: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262aec: jal 0x0025e8e0 */ set(31,UINT64_C(0x00262af4));/* delay 00262af0 */ set(19,cpu(6));body_0025e8e0();
/* 00262af4: move a0,v0 */ set(4,cpu(2));
/* 00262af8: move a1,s0 */ set(5,cpu(16));
/* 00262afc: move a3,s1 */ set(7,cpu(17));
/* 00262b00: jal 0x0025ea48 */ set(31,UINT64_C(0x00262b08));/* delay 00262b04 */ set(6,cpu(0));body_0025ea48();
/* 00262b08: li a0,0x1f */ set(4,sx(UINT32_C(0x0000001f)));
/* 00262b0c: move v1,v0 */ set(3,cpu(2));
/* 00262b10: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262b14: sh s2,0x2a(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000002a)),(uint16_t)cpu(18));
/* 00262b18: sh s3,0x28(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000028)),(uint16_t)cpu(19));
/* 00262b1c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262b20: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262b24: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262b28: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262b2c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262b30: jr ra */ {uint64_t target=cpu(31);/* delay 00262b34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00262b38(void){
uint64_t incoming=cpu(31);
/* 00262b38: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262b3c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262b40: move s0,a0 */ set(16,cpu(4));
/* 00262b44: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262b48: move s1,a1 */ set(17,cpu(5));
/* 00262b4c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262b50: move s2,a3 */ set(18,cpu(7));
/* 00262b54: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262b58: move s3,t0 */ set(19,cpu(8));
/* 00262b5c: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262b60: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262b64: jal 0x0025e8e0 */ set(31,UINT64_C(0x00262b6c));/* delay 00262b68 */ set(20,cpu(6));body_0025e8e0();
/* 00262b6c: move a0,v0 */ set(4,cpu(2));
/* 00262b70: move a1,s0 */ set(5,cpu(16));
/* 00262b74: move a3,s1 */ set(7,cpu(17));
/* 00262b78: jal 0x0025ea48 */ set(31,UINT64_C(0x00262b80));/* delay 00262b7c */ set(6,cpu(0));body_0025ea48();
/* 00262b80: li a0,0x13 */ set(4,sx(UINT32_C(0x00000013)));
/* 00262b84: move v1,v0 */ set(3,cpu(2));
/* 00262b88: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262b8c: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00262b90: sw s4,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(20));
/* 00262b94: sw s3,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(19));
/* 00262b98: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262b9c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262ba0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262ba4: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262ba8: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262bac: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262bb0: jr ra */ {uint64_t target=cpu(31);/* delay 00262bb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_00262bb8(void){
uint64_t incoming=cpu(31);
/* 00262bb8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262bbc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262bc0: move s0,a0 */ set(16,cpu(4));
/* 00262bc4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262bc8: move s1,a1 */ set(17,cpu(5));
/* 00262bcc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262bd0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262bd4: jal 0x0025e8e0 */ set(31,UINT64_C(0x00262bdc));/* delay 00262bd8 */ set(18,cpu(6));body_0025e8e0();
/* 00262bdc: move a0,v0 */ set(4,cpu(2));
/* 00262be0: move a1,s0 */ set(5,cpu(16));
/* 00262be4: move a3,s1 */ set(7,cpu(17));
/* 00262be8: jal 0x0025ea48 */ set(31,UINT64_C(0x00262bf0));/* delay 00262bec */ set(6,cpu(0));body_0025ea48();
/* 00262bf0: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 00262bf4: move v1,v0 */ set(3,cpu(2));
/* 00262bf8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262bfc: sw s2,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 00262c00: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262c04: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262c08: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262c0c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262c10: jr ra */ {uint64_t target=cpu(31);/* delay 00262c14 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00262cc0(void){
uint64_t incoming=cpu(31);
/* 00262cc0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262cc4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262cc8: move s2,a2 */ set(18,cpu(6));
/* 00262ccc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262cd0: move s1,a1 */ set(17,cpu(5));
/* 00262cd4: li a2,0x5 */ set(6,sx(UINT32_C(0x00000005)));
/* 00262cd8: move a1,s2 */ set(5,cpu(18));
/* 00262cdc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262ce0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262ce4: jal 0x0025ef10 */ set(31,UINT64_C(0x00262cec));/* delay 00262ce8 */ set(16,cpu(4));body_0025ef10();
/* 00262cec: bne v0,zero,0x00262d20 */ {int taken=(cpu(2)!=cpu(0));/* delay 00262cf0 */ set(2,cpu(0));if(taken){goto L_00262d20;}}
/* 00262cf4: jal 0x0025e8e0 */ set(31,UINT64_C(0x00262cfc));/* delay 00262cf8 */ body_0025e8e0();
/* 00262cfc: move a1,s0 */ set(5,cpu(16));
/* 00262d00: move a0,v0 */ set(4,cpu(2));
/* 00262d04: move a3,s1 */ set(7,cpu(17));
/* 00262d08: jal 0x0025ea48 */ set(31,UINT64_C(0x00262d10));/* delay 00262d0c */ set(6,cpu(0));body_0025ea48();
/* 00262d10: li a0,0x19 */ set(4,sx(UINT32_C(0x00000019)));
/* 00262d14: move v1,v0 */ set(3,cpu(2));
/* 00262d18: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00262d1c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
L_00262d20:;
/* 00262d20: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262d24: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262d28: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262d2c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262d30: jr ra */ {uint64_t target=cpu(31);/* delay 00262d34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_00264010(void){
uint64_t incoming=cpu(31);
/* 00264010: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 00264014: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00264018: move s0,a1 */ set(16,cpu(5));
/* 0026401c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00264020: move s1,a0 */ set(17,cpu(4));
/* 00264024: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00264028: move s2,a2 */ set(18,cpu(6));
/* 0026402c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00264030: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00264034: move s4,t0 */ set(20,cpu(8));
/* 00264038: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026403c: move s5,t1 */ set(21,cpu(9));
/* 00264040: sd s6,0x30(sp) */ save(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00264044: move s6,t2 */ set(22,cpu(10));
/* 00264048: sd ra,0x38(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 0026404c: lh v0,0x92(s2) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(18,(int32_t)UINT32_C(0x00000092))));
/* 00264050: slti v0,v0,0x10 */ set(2,(int64_t)cpu(2)<(int64_t)(int32_t)UINT32_C(0x00000010));
/* 00264054: sltiu s3,v0,0x1 */ set(19,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
/* 00264058: bne s3,zero,0x002640b8 */ {int taken=(cpu(19)!=cpu(0));/* delay 0026405c */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_002640b8;}}
/* 00264060: beq a3,v0,0x00264088 */ {int taken=(cpu(7)==cpu(2));/* delay 00264064 */ set(2,(int64_t)cpu(7)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_00264088;}}
/* 00264068: bne v0,zero,0x002640b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 0026406c */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_002640b8;}}
/* 00264070: beq a3,v0,0x002640b8 */ {int taken=(cpu(7)==cpu(2));/* delay 00264074 */ set(2,sx(UINT32_C(0x00000003)));if(taken){goto L_002640b8;}}
/* 00264078: beq a3,v0,0x00264098 */ {int taken=(cpu(7)==cpu(2));/* delay 0026407c */ set(8,sx(UINT32_C(0x0000000a)));if(taken){goto L_00264098;}}
/* 00264080: b 0x002640b8 */ /* delay 00264084 */ goto L_002640b8;
L_00264088:;
/* 00264088: jal 0x00262480 */ set(31,UINT64_C(0x00264090));/* delay 0026408c */ set(7,sx(UINT32_C(0x00000002)));body_00262480();
/* 00264090: b 0x002640b8 */ /* delay 00264094 */ goto L_002640b8;
L_00264098:;
/* 00264098: lui a3,0x8086 */ set(7,sx(UINT32_C(0x80860000)));
/* 0026409c: jal 0x00261ca0 */ set(31,UINT64_C(0x002640a4));/* delay 002640a0 */ set(7,cpu(7)|UINT32_C(0x0000eb9b));body_00261ca0();
/* 002640a4: addiu a0,s1,0xa */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x0000000a)));
/* 002640a8: move a1,s0 */ set(5,cpu(16));
/* 002640ac: move a2,s2 */ set(6,cpu(18));
/* 002640b0: jal 0x00261d20 */ set(31,UINT64_C(0x002640b8));/* delay 002640b4 */ set(7,sx(UINT32_C(0x0000000a)));body_00261d20();
L_002640b8:;
/* 002640b8: bltz s4,0x00264120 */ {int taken=((int64_t)cpu(20)<0);/* delay 002640bc */ if(taken){goto L_00264120;}}
/* 002640c0: bltz s5,0x00264170 */ {int taken=((int64_t)cpu(21)<0);/* delay 002640c4 */ if(taken){goto L_00264170;}}
/* 002640c8: bnel s3,zero,0x002640f4 */ {int taken=(cpu(19)!=cpu(0));if(taken){/* delay 002640cc */ set(7,cpu(20));goto L_002640f4;}}
/* 002640d0: addiu a0,s1,0x1 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 002640d4: li a1,0x2d */ set(5,sx(UINT32_C(0x0000002d)));
/* 002640d8: move a2,s0 */ set(6,cpu(16));
/* 002640dc: move a3,s2 */ set(7,cpu(18));
/* 002640e0: move t0,s4 */ set(8,cpu(20));
/* 002640e4: move t1,s5 */ set(9,cpu(21));
/* 002640e8: jal 0x002627c0 */ set(31,UINT64_C(0x002640f0));/* delay 002640ec */ set(10,sx(UINT32_C(0x00000005)));body_002627c0();
/* 002640f0: move a3,s4 */ set(7,cpu(20));
L_002640f4:;
/* 002640f4: move t0,zero */ set(8,cpu(0));
/* 002640f8: move a0,s1 */ set(4,cpu(17));
/* 002640fc: move a1,s0 */ set(5,cpu(16));
/* 00264100: jal 0x002629e8 */ set(31,UINT64_C(0x00264108));/* delay 00264104 */ set(6,cpu(18));body_002629e8();
/* 00264108: move a0,s1 */ set(4,cpu(17));
/* 0026410c: move a1,s0 */ set(5,cpu(16));
/* 00264110: move a2,s2 */ set(6,cpu(18));
/* 00264114: b 0x00264160 */ /* delay 00264118 */ set(7,cpu(21));goto L_00264160;
L_00264120:;
/* 00264120: bltz s5,0x00264170 */ {int taken=((int64_t)cpu(21)<0);/* delay 00264124 */ if(taken){goto L_00264170;}}
/* 00264128: bne s3,zero,0x00264154 */ {int taken=(cpu(19)!=cpu(0));/* delay 0026412c */ set(7,cpu(21));if(taken){goto L_00264154;}}
/* 00264130: addiu a0,s1,0x1 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 00264134: li a1,0x2d */ set(5,sx(UINT32_C(0x0000002d)));
/* 00264138: move a2,s0 */ set(6,cpu(16));
/* 0026413c: move a3,s2 */ set(7,cpu(18));
/* 00264140: move t0,s5 */ set(8,cpu(21));
/* 00264144: move t1,zero */ set(9,cpu(0));
/* 00264148: jal 0x002627c0 */ set(31,UINT64_C(0x00264150));/* delay 0026414c */ set(10,sx(UINT32_C(0x00000003)));body_002627c0();
/* 00264150: move a3,s5 */ set(7,cpu(21));
L_00264154:;
/* 00264154: move a0,s1 */ set(4,cpu(17));
/* 00264158: move a1,s0 */ set(5,cpu(16));
/* 0026415c: move a2,s2 */ set(6,cpu(18));
L_00264160:;
/* 00264160: jal 0x002629e8 */ set(31,UINT64_C(0x00264168));/* delay 00264164 */ set(8,sx(UINT32_C(0x00000001)));body_002629e8();
/* 00264168: b 0x002641b8 */ /* delay 0026416c */ goto L_002641b8;
L_00264170:;
/* 00264170: bltz s4,0x002641b8 */ {int taken=((int64_t)cpu(20)<0);/* delay 00264174 */ if(taken){goto L_002641b8;}}
/* 00264178: bne s3,zero,0x002641a4 */ {int taken=(cpu(19)!=cpu(0));/* delay 0026417c */ set(7,cpu(20));if(taken){goto L_002641a4;}}
/* 00264180: addiu a0,s1,0x1 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));
/* 00264184: li a1,0x2d */ set(5,sx(UINT32_C(0x0000002d)));
/* 00264188: move a2,s0 */ set(6,cpu(16));
/* 0026418c: move a3,s2 */ set(7,cpu(18));
/* 00264190: move t0,s4 */ set(8,cpu(20));
/* 00264194: move t1,zero */ set(9,cpu(0));
/* 00264198: jal 0x002627c0 */ set(31,UINT64_C(0x002641a0));/* delay 0026419c */ set(10,sx(UINT32_C(0x00000002)));body_002627c0();
/* 002641a0: move a3,s4 */ set(7,cpu(20));
L_002641a4:;
/* 002641a4: move a0,s1 */ set(4,cpu(17));
/* 002641a8: move a1,s0 */ set(5,cpu(16));
/* 002641ac: move a2,s2 */ set(6,cpu(18));
/* 002641b0: jal 0x002629e8 */ set(31,UINT64_C(0x002641b8));/* delay 002641b4 */ set(8,cpu(0));body_002629e8();
L_002641b8:;
/* 002641b8: beq s6,zero,0x002641cc */ {int taken=(cpu(22)==cpu(0));/* delay 002641bc */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00000001)));if(taken){goto L_002641cc;}}
/* 002641c0: move a1,s0 */ set(5,cpu(16));
/* 002641c4: jal 0x002645a8 */ set(31,UINT64_C(0x002641cc));/* delay 002641c8 */ set(6,cpu(18));body_002645a8();
L_002641cc:;
/* 002641cc: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002641d0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002641d4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002641d8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002641dc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002641e0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002641e4: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002641e8: ld s6,0x30(sp) */ restore(22,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002641ec: ld ra,0x38(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000038)));
/* 002641f0: jr ra */ {uint64_t target=cpu(31);/* delay 002641f4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_0026a3d8(void){
uint64_t incoming=cpu(31);
/* 0026a3d8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026a3dc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a3e0: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a3e4: jal 0x00243f40 */ set(31,UINT64_C(0x0026a3ec));/* delay 0026a3e8 */ set(16,cpu(5));body_00243f40();
/* 0026a3ec: beq v0,zero,0x0026a434 */ {int taken=(cpu(2)==cpu(0));/* delay 0026a3f0 */ set(3,sx(UINT32_C(0x0000012c)));if(taken){goto L_0026a434;}}
/* 0026a3f4: beq s0,v1,0x0026a410 */ {int taken=(cpu(16)==cpu(3));/* delay 0026a3f8 */ set(2,sx(UINT32_C(0x0000012d)));if(taken){goto L_0026a410;}}
/* 0026a3fc: beq s0,v0,0x0026a428 */ {int taken=(cpu(16)==cpu(2));/* delay 0026a400 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_0026a428;}}
/* 0026a404: b 0x0026a438 */ /* delay 0026a408 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_0026a438;
L_0026a410:;
/* 0026a410: jal 0x001e9998 */ set(31,UINT64_C(0x0026a418));/* delay 0026a414 */ body_001e9998();
/* 0026a418: xori v0,v0,0x8 */ set(2,cpu(2)^UINT32_C(0x00000008));
/* 0026a41c: b 0x0026a434 */ /* delay 0026a420 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));goto L_0026a434;
L_0026a428:;
/* 0026a428: jal 0x001e9998 */ set(31,UINT64_C(0x0026a430));/* delay 0026a42c */ body_001e9998();
/* 0026a430: sltiu v0,v0,0x1 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_0026a434:;
/* 0026a434: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0026a438:;
/* 0026a438: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026a43c: jr ra */ {uint64_t target=cpu(31);/* delay 0026a440 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002a8520(void){
uint64_t incoming=cpu(31);
/* 002a8520: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002a8524: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a8528: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a852c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a8530: jal 0x002dbd90 */ set(31,UINT64_C(0x002a8538));/* delay 002a8534 */ set(17,cpu(4));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002dbd90),UINT32_C(0x002a8530));
/* 002a8538: move s0,v0 */ set(16,cpu(2));
/* 002a853c: jal 0x002dbdf0 */ set(31,UINT64_C(0x002a8544));/* delay 002a8540 */ set(4,cpu(16));body_002dbdf0();
/* 002a8544: lui a1,0x2b */ set(5,sx(UINT32_C(0x002b0000)));
/* 002a8548: andi a0,s1,0xffff */ set(4,cpu(17)&UINT32_C(0x0000ffff));
/* 002a854c: move a2,s0 */ set(6,cpu(16));
/* 002a8550: jal 0x002dbc20 */ set(31,UINT64_C(0x002a8558));/* delay 002a8554 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffff8508)));body_002dbc20();
/* 002a8558: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a855c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a8560: ld ra,0x10(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a8564: j 0x002dbdc0 */ /* delay 002a8568 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(cpu(31),incoming);body_002dbdc0();return;
}
static void body_002a9558(void){
uint64_t incoming=cpu(31);
/* 002a9558: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002a955c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002a9560: move s0,a0 */ set(16,cpu(4));
/* 002a9564: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a9568: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a956c: beq s0,zero,0x002a95e0 */ {int taken=(cpu(16)==cpu(0));/* delay 002a9570 */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));if(taken){goto L_002a95e0;}}
/* 002a9574: jal 0x002e4070 */ set(31,UINT64_C(0x002a957c));/* delay 002a9578 */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e4070),UINT32_C(0x002a9574));
/* 002a957c: lw s1,0x4(s0) */ lw(17,ea(16,(int32_t)UINT32_C(0x00000004)));
/* 002a9580: move s2,v0 */ set(18,cpu(2));
/* 002a9584: lhu v0,0xc(s1) */ set(2,half(ea(17,(int32_t)UINT32_C(0x0000000c))));
/* 002a9588: bne v0,zero,0x002a95a0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002a958c */ set(4,cpu(16));if(taken){goto L_002a95a0;}}
/* 002a9590: jal 0x002a9540 */ set(31,UINT64_C(0x002a9598));/* delay 002a9594 */ body_002a9540();
/* 002a9598: jal 0x002a8bd8 */ set(31,UINT64_C(0x002a95a0));/* delay 002a959c */ set(4,cpu(17));body_002a8bd8();
L_002a95a0:;
/* 002a95a0: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002a95a4: lhu v0,0xc(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000c))));
/* 002a95a8: bne v0,zero,0x002a95c8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002a95ac */ set(4,cpu(3));if(taken){goto L_002a95c8;}}
/* 002a95b0: jal 0x002a9540 */ set(31,UINT64_C(0x002a95b8));/* delay 002a95b4 */ body_002a9540();
/* 002a95b8: jal 0x002a8bd8 */ set(31,UINT64_C(0x002a95c0));/* delay 002a95bc */ set(4,cpu(16));body_002a8bd8();
/* 002a95c0: b 0x002a95d0 */ /* delay 002a95c4 */ goto L_002a95d0;
L_002a95c8:;
/* 002a95c8: sh zero,0xe(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000e)),(uint16_t)cpu(0));
/* 002a95cc: sh zero,0xc(s0) */ sh(ea(16,(int32_t)UINT32_C(0x0000000c)),(uint16_t)cpu(0));
L_002a95d0:;
/* 002a95d0: beq s2,zero,0x002a95e4 */ {int taken=(cpu(18)==cpu(0));/* delay 002a95d4 */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002a95e4;}}
/* 002a95d8: jal 0x002e40b8 */ set(31,UINT64_C(0x002a95e0));/* delay 002a95dc */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e40b8),UINT32_C(0x002a95d8));
L_002a95e0:;
/* 002a95e0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002a95e4:;
/* 002a95e4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002a95e8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002a95ec: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002a95f0: jr ra */ {uint64_t target=cpu(31);/* delay 002a95f4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002acce0(void){
uint64_t incoming=cpu(31);
/* 002acce0: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002acce4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002acce8: move s1,a1 */ set(17,cpu(5));
/* 002accec: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002accf0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002accf4: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002accf8: lw v0,0x8(s1) */ lw(2,ea(17,(int32_t)UINT32_C(0x00000008)));
/* 002accfc: beq v0,zero,0x002acd28 */ {int taken=(cpu(2)==cpu(0));/* delay 002acd00 */ set(18,cpu(4));if(taken){goto L_002acd28;}}
/* 002acd04: lw s0,0x4(s2) */ lw(16,ea(18,(int32_t)UINT32_C(0x00000004)));
/* 002acd08: bne s0,zero,0x002acd18 */ {int taken=(cpu(16)!=cpu(0));/* delay 002acd0c */ set(5,cpu(16));if(taken){goto L_002acd18;}}
/* 002acd10: b 0x002acd20 */ /* delay 002acd14 */ sw(ea(18,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(17));goto L_002acd20;
L_002acd18:;
/* 002acd18: jal 0x002acee8 */ set(31,UINT64_C(0x002acd20));/* delay 002acd1c */ set(4,cpu(17));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002acee8),UINT32_C(0x002acd18));
L_002acd20:;
/* 002acd20: sw s0,0x0(s1) */ sw(ea(17,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002acd24: sw s1,0x4(s2) */ sw(ea(18,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
L_002acd28:;
/* 002acd28: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002acd2c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002acd30: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002acd34: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002acd38: jr ra */ {uint64_t target=cpu(31);/* delay 002acd3c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002c0f28(void){
uint64_t incoming=cpu(31);
/* 002c0f28: lhu a0,-0x203e(gp) */ set(4,half(ea(28,(int32_t)UINT32_C(0xffffdfc2))));
/* 002c0f2c: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c0f30: lhu v1,-0x203c(gp) */ set(3,half(ea(28,(int32_t)UINT32_C(0xffffdfc4))));
/* 002c0f34: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c0f38: sll a0,a0,0x10 */ set(4,sx((uint32_t)cpu(4)<<16));
/* 002c0f3c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0f40: sll v1,v1,0x10 */ set(3,sx((uint32_t)cpu(3)<<16));
/* 002c0f44: sra s0,a0,0x10 */ set(16,sx((uint32_t)((int32_t)cpu(4)>>16)));
/* 002c0f48: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0f4c: beq a0,v1,0x002c0fb0 */ {int taken=(cpu(4)==cpu(3));/* delay 002c0f50 */ set(5,sx((uint32_t)cpu(16)<<7));if(taken){goto L_002c0fb0;}}
/* 002c0f54: lui v0,0x59 */ set(2,sx(UINT32_C(0x00590000)));
/* 002c0f58: addiu v0,v0,0x840 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0x00000840)));
/* 002c0f5c: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002c0f60: move a0,zero */ set(4,cpu(0));
/* 002c0f64: lbu a2,0xf(v0) */ set(6,byte(ea(2,(int32_t)UINT32_C(0x0000000f))));
/* 002c0f68: move a1,v0 */ set(5,cpu(2));
/* 002c0f6c: move a3,zero */ set(7,cpu(0));
/* 002c0f70: move t0,zero */ set(8,cpu(0));
/* 002c0f74: move t1,zero */ set(9,cpu(0));
/* 002c0f78: jal 0x002de2b0 */ set(31,UINT64_C(0x002c0f80));/* delay 002c0f7c */ set(6,cpu(6)&UINT32_C(0x000000f0));body_002de2b0();
/* 002c0f80: addiu v1,s0,0x1 */ set(3,sx((uint32_t)cpu(16)+UINT32_C(0x00000001)));
/* 002c0f84: lui a0,0x55 */ set(4,sx(UINT32_C(0x00550000)));
/* 002c0f88: andi s0,v1,0x1f */ set(16,cpu(3)&UINT32_C(0x0000001f));
/* 002c0f8c: bne v0,zero,0x002c0fa8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002c0f90 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0xffff9950)));if(taken){goto L_002c0fa8;}}
/* 002c0f94: jal 0x002d4748 */ set(31,UINT64_C(0x002c0f9c));/* delay 002c0f98 */ body_002d4748();
/* 002c0f9c: b 0x002c0fb0 */ /* delay 002c0fa0 */ set(2,sx(UINT32_C(0x00000001)));goto L_002c0fb0;
L_002c0fa8:;
/* 002c0fa8: sh s0,-0x203e(gp) */ sh(ea(28,(int32_t)UINT32_C(0xffffdfc2)),(uint16_t)cpu(16));
/* 002c0fac: move v0,zero */ set(2,cpu(0));
L_002c0fb0:;
/* 002c0fb0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0fb4: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0fb8: jr ra */ {uint64_t target=cpu(31);/* delay 002c0fbc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002c1238(void){
uint64_t incoming=cpu(31);
/* 002c1238: jr ra */ {uint64_t target=cpu(31);/* delay 002c123c */ checkReturn(target,incoming);return;}
}
static void body_002c1240(void){
uint64_t incoming=cpu(31);
/* 002c1240: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c1244: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c1248: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c124c: jal 0x002c10e8 */ set(31,UINT64_C(0x002c1254));/* delay 002c1250 */ body_002c10e8();
/* 002c1254: move s0,v0 */ set(16,cpu(2));
/* 002c1258: jal 0x002c1238 */ set(31,UINT64_C(0x002c1260));/* delay 002c125c */ set(4,cpu(16));body_002c1238();
/* 002c1260: move v0,s0 */ set(2,cpu(16));
/* 002c1264: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c1268: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c126c: jr ra */ {uint64_t target=cpu(31);/* delay 002c1270 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
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
/* 002c18f4: jal 0x002c1ca0 */ set(31,UINT64_C(0x002c18fc));/* delay 002c18f8 */ set(18,cpu(4));body_002c1ca0();
/* 002c18fc: andi s1,s1,0xff */ set(17,cpu(17)&UINT32_C(0x000000ff));
/* 002c1900: move a2,sp */ set(6,cpu(29));
/* 002c1904: li a0,0x90 */ set(4,sx(UINT32_C(0x00000090)));
/* 002c1908: move a1,zero */ set(5,cpu(0));
/* 002c190c: li a3,0xc */ set(7,sx(UINT32_C(0x0000000c)));
/* 002c1910: sw s2,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(18));
/* 002c1914: sh s0,0x8(sp) */ sh(ea(29,(int32_t)UINT32_C(0x00000008)),(uint16_t)cpu(16));
/* 002c1918: jal 0x002c10e8 */ set(31,UINT64_C(0x002c1920));/* delay 002c191c */ sh(ea(29,(int32_t)UINT32_C(0x0000000a)),(uint16_t)cpu(17));body_002c10e8();
/* 002c1920: ld s0,0x10(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c1924: ld s1,0x18(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002c1928: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002c192c: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002c1930: jr ra */ {uint64_t target=cpu(31);/* delay 002c1934 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
static void body_002c1ca0(void){
uint64_t incoming=cpu(31);
/* 002c1ca0: addiu sp,sp,-0x130 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffed0)));
/* 002c1ca4: sd s0,0x110(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000110)));
/* 002c1ca8: sd s1,0x118(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000118)));
/* 002c1cac: sd ra,0x120(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000120)));
/* 002c1cb0: jal 0x002c1c20 */ set(31,UINT64_C(0x002c1cb8));/* delay 002c1cb4 */ set(16,cpu(4));body_002c1c20();
/* 002c1cb8: move v1,v0 */ set(3,cpu(2));
/* 002c1cbc: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002c1cc0: beq v1,v0,0x002c1d64 */ {int taken=(cpu(3)==cpu(2));/* delay 002c1cc4 */ set(2,(int64_t)cpu(3)<(int64_t)(int32_t)UINT32_C(0x00000002));if(taken){goto L_002c1d64;}}
/* 002c1cc8: beql v0,zero,0x002c1ce0 */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002c1ccc */ set(2,sx(UINT32_C(0x00000002)));goto L_002c1ce0;}}
/* 002c1cd0: beql v1,zero,0x002c1cf0 */ {int taken=(cpu(3)==cpu(0));if(taken){/* delay 002c1cd4 */ set(16,sx((uint32_t)((int32_t)cpu(16)>>16)));goto L_002c1cf0;}}
/* 002c1cd8: b 0x002c1d68 */ /* delay 002c1cdc */ restore(16,ea(29,(int32_t)UINT32_C(0x00000110)));goto L_002c1d68;
L_002c1ce0:;
/* 002c1ce0: beq v1,v0,0x002c1d38 */ {int taken=(cpu(3)==cpu(2));/* delay 002c1ce4 */ set(17,sx(UINT32_C(0x00000001)));if(taken){goto L_002c1d38;}}
/* 002c1ce8: b 0x002c1d68 */ /* delay 002c1cec */ restore(16,ea(29,(int32_t)UINT32_C(0x00000110)));goto L_002c1d68;
L_002c1cf0:;
/* 002c1cf0: lui a1,0x55 */ set(5,sx(UINT32_C(0x00550000)));
/* 002c1cf4: move a0,sp */ set(4,cpu(29));
/* 002c1cf8: move a2,s0 */ set(6,cpu(16));
/* 002c1cfc: jal 0x002d5690 */ set(31,UINT64_C(0x002c1d04));/* delay 002c1d00 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0xffff9aa8)));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d5690),UINT32_C(0x002c1cfc));
/* 002c1d04: addiu s1,sp,0x10 */ set(17,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));
/* 002c1d08: move a1,sp */ set(5,cpu(29));
/* 002c1d0c: jal 0x002262e8 */ set(31,UINT64_C(0x002c1d14));/* delay 002c1d10 */ set(4,cpu(17));body_002262e8();
/* 002c1d14: jal 0x002d5d0c */ set(31,UINT64_C(0x002c1d1c));/* delay 002c1d18 */ set(4,cpu(17));nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002d5d0c),UINT32_C(0x002c1d14));
/* 002c1d1c: li a0,0xa0 */ set(4,sx(UINT32_C(0x000000a0)));
/* 002c1d20: move a2,s1 */ set(6,cpu(17));
/* 002c1d24: addiu a3,v0,0x1 */ set(7,sx((uint32_t)cpu(2)+UINT32_C(0x00000001)));
/* 002c1d28: jal 0x002c1240 */ set(31,UINT64_C(0x002c1d30));/* delay 002c1d2c */ set(5,cpu(0));body_002c1240();
/* 002c1d30: b 0x002c1d64 */ /* delay 002c1d34 */ sw(ea(28,(int32_t)UINT32_C(0xffffd850)),(uint32_t)cpu(16));goto L_002c1d64;
L_002c1d38:;
/* 002c1d38: jal 0x002a8520 */ set(31,UINT64_C(0x002c1d40));/* delay 002c1d3c */ set(4,sx(UINT32_C(0x00000002)));body_002a8520();
/* 002c1d40: lw v0,-0x2798(gp) */ lw(2,ea(28,(int32_t)UINT32_C(0xffffd868)));
/* 002c1d44: beq v0,zero,0x002c1d54 */ {int taken=(cpu(2)==cpu(0));/* delay 002c1d48 */ if(taken){goto L_002c1d54;}}
/* 002c1d4c: jalr v0 */ {uint64_t target=cpu(2);set(31,UINT64_C(0x002c1d54));/* delay 002c1d50 */ nocturneBattlePanelRendererRemainingIndirect(target,UINT32_C(0x002c1d4c));}
L_002c1d54:;
/* 002c1d54: jal 0x002c1c20 */ set(31,UINT64_C(0x002c1d5c));/* delay 002c1d58 */ set(4,cpu(16));body_002c1c20();
/* 002c1d5c: bne v0,s1,0x002c1d38 */ {int taken=(cpu(2)!=cpu(17));/* delay 002c1d60 */ if(taken){goto L_002c1d38;}}
L_002c1d64:;
/* 002c1d64: ld s0,0x110(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000110)));
L_002c1d68:;
/* 002c1d68: ld s1,0x118(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000118)));
/* 002c1d6c: ld ra,0x120(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000120)));
/* 002c1d70: jr ra */ {uint64_t target=cpu(31);/* delay 002c1d74 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000130)));checkReturn(target,incoming);return;}
}
static void body_002d57f8(void){
uint64_t incoming=cpu(31);
/* 002d57f8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002d57fc: sq s0,0x0(sp) */ sq(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d5800: move s0,a0 */ set(16,cpu(4));
/* 002d5804: andi v0,s0,0x7 */ set(2,cpu(16)&UINT32_C(0x00000007));
/* 002d5808: bne v0,zero,0x002d58ec */ {int taken=(cpu(2)!=cpu(0));/* delay 002d580c */ sq(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002d58ec;}}
/* 002d5810: andi v0,s0,0xf */ set(2,cpu(16)&UINT32_C(0x0000000f));
/* 002d5814: lui v1,0x101 */ set(3,sx(UINT32_C(0x01010000)));
/* 002d5818: ori v1,v1,0x101 */ set(3,cpu(3)|UINT32_C(0x00000101));
/* 002d581c: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002d5820: ori v1,v1,0x101 */ set(3,cpu(3)|UINT32_C(0x00000101));
/* 002d5824: dsll v1,v1,0x10 */ set(3,cpu(3)<<16);
/* 002d5828: ori v1,v1,0x101 */ set(3,cpu(3)|UINT32_C(0x00000101));
/* 002d582c: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 002d5830: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5834: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5838: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d583c: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5840: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5844: bne v0,zero,0x002d58a8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5848 */ restore(6,ea(16,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002d58a8;}}
/* 002d584c: lq v0,0x0(s0) */ requestLq(2,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 002d5850: pcpyld a3,v1,v1 */ requestPacked(0,7,3,3);
/* 002d5854: pcpyld t0,a0,a0 */ requestPacked(0,8,4,4);
/* 002d5858: psubb v1,v0,a3 */ requestPacked(4,3,2,7);
/* 002d585c: pnor v0,zero,v0 */ requestPacked(3,2,0,2);
/* 002d5860: pand v1,v1,v0 */ requestPacked(2,3,3,2);
/* 002d5864: pand v1,v1,t0 */ requestPacked(2,3,3,8);
/* 002d5868: pcpyud v0,v1,v1 */ requestPacked(1,2,3,3);
/* 002d586c: or v1,v0,v1 */ set(3,cpu(2)|cpu(3));
/* 002d5870: bne v1,zero,0x002d58ec */ {int taken=(cpu(3)!=cpu(0));/* delay 002d5874 */ set(4,cpu(16));if(taken){goto L_002d58ec;}}
/* 002d5878: addiu a2,a0,0x10 */ set(6,sx((uint32_t)cpu(4)+UINT32_C(0x00000010)));
L_002d587c:;
/* 002d587c: lq v0,0x0(a2) */ requestLq(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002d5880: pnor v1,zero,v0 */ requestPacked(3,3,0,2);
/* 002d5884: psubb v0,v0,a3 */ requestPacked(4,2,2,7);
/* 002d5888: pand v0,v0,v1 */ requestPacked(2,2,2,3);
/* 002d588c: pand v0,v0,t0 */ requestPacked(2,2,2,8);
/* 002d5890: pcpyud v1,v0,v0 */ requestPacked(1,3,2,2);
/* 002d5894: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002d5898: beql v0,zero,0x002d587c */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d589c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000010)));goto L_002d587c;}}
/* 002d58a0: b 0x002d58ec */ /* delay 002d58a4 */ set(4,cpu(6));goto L_002d58ec;
L_002d58a8:;
/* 002d58a8: move a3,v1 */ set(7,cpu(3));
/* 002d58ac: move t0,a0 */ set(8,cpu(4));
/* 002d58b0: dsubu v1,a2,v1 */ set(3,cpu(6)-cpu(3));
/* 002d58b4: nor v0,zero,a2 */ set(2,~(cpu(0)|cpu(6)));
/* 002d58b8: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 002d58bc: and v1,v1,a0 */ set(3,cpu(3)&cpu(4));
/* 002d58c0: bne v1,zero,0x002d58ec */ {int taken=(cpu(3)!=cpu(0));/* delay 002d58c4 */ set(4,cpu(16));if(taken){goto L_002d58ec;}}
/* 002d58c8: addiu a2,s0,0x8 */ set(6,sx((uint32_t)cpu(16)+UINT32_C(0x00000008)));
L_002d58cc:;
/* 002d58cc: ld v0,0x0(a2) */ restore(2,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002d58d0: nor v1,zero,v0 */ set(3,~(cpu(0)|cpu(2)));
/* 002d58d4: dsubu v0,v0,a3 */ set(2,cpu(2)-cpu(7));
/* 002d58d8: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d58dc: and v0,v0,t0 */ set(2,cpu(2)&cpu(8));
/* 002d58e0: beql v0,zero,0x002d58cc */ {int taken=(cpu(2)==cpu(0));if(taken){/* delay 002d58e4 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000008)));goto L_002d58cc;}}
/* 002d58e8: move a0,a2 */ set(4,cpu(6));
L_002d58ec:;
/* 002d58ec: lb v0,0x0(a0) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(4,(int32_t)UINT32_C(0x00000000))));
/* 002d58f0: nop  */ 
/* 002d58f4: nop  */ 
/* 002d58f8: nop  */ 
/* 002d58fc: nop  */ 
/* 002d5900: bnel v0,zero,0x002d58ec */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d5904 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));goto L_002d58ec;}}
/* 002d5908: jal 0x002d5bf8 */ set(31,UINT64_C(0x002d5910));/* delay 002d590c */ body_002d5bf8();
/* 002d5910: move v0,s0 */ set(2,cpu(16));
/* 002d5914: lq ra,0x10(sp) */ requestLq(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002d5918: lq s0,0x0(sp) */ requestLq(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002d591c: jr ra */ {uint64_t target=cpu(31);/* delay 002d5920 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002d5bf8(void){
uint64_t incoming=cpu(31);
/* 002d5bf8: move a3,a0 */ set(7,cpu(4));
/* 002d5bfc: or t0,a1,a3 */ set(8,cpu(5)|cpu(7));
/* 002d5c00: andi v0,t0,0x7 */ set(2,cpu(8)&UINT32_C(0x00000007));
/* 002d5c04: bne v0,zero,0x002d5ce8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5c08 */ set(3,cpu(7));if(taken){goto L_002d5ce8;}}
/* 002d5c0c: andi v0,t0,0xf */ set(2,cpu(8)&UINT32_C(0x0000000f));
/* 002d5c10: lui t1,0x101 */ set(9,sx(UINT32_C(0x01010000)));
/* 002d5c14: ori t1,t1,0x101 */ set(9,cpu(9)|UINT32_C(0x00000101));
/* 002d5c18: dsll t1,t1,0x10 */ set(9,cpu(9)<<16);
/* 002d5c1c: ori t1,t1,0x101 */ set(9,cpu(9)|UINT32_C(0x00000101));
/* 002d5c20: dsll t1,t1,0x10 */ set(9,cpu(9)<<16);
/* 002d5c24: ori t1,t1,0x101 */ set(9,cpu(9)|UINT32_C(0x00000101));
/* 002d5c28: lui a0,0x8080 */ set(4,sx(UINT32_C(0x80800000)));
/* 002d5c2c: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5c30: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5c34: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5c38: dsll a0,a0,0x10 */ set(4,cpu(4)<<16);
/* 002d5c3c: ori a0,a0,0x8080 */ set(4,cpu(4)|UINT32_C(0x00008080));
/* 002d5c40: bnel v0,zero,0x002d5ca8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002d5c44 */ restore(10,ea(5,(int32_t)UINT32_C(0x00000000)));goto L_002d5ca8;}}
/* 002d5c48: pcpyld t2,t1,t1 */ requestPacked(0,10,9,9);
/* 002d5c4c: lq t1,0x0(a1) */ requestLq(9,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5c50: pcpyld t0,a0,a0 */ requestPacked(0,8,4,4);
/* 002d5c54: psubb v0,t1,t2 */ requestPacked(4,2,9,10);
/* 002d5c58: pnor v1,zero,t1 */ requestPacked(3,3,0,9);
/* 002d5c5c: pand v0,v0,v1 */ requestPacked(2,2,2,3);
/* 002d5c60: pand v0,v0,t0 */ requestPacked(2,2,2,8);
/* 002d5c64: pcpyud a0,v0,t1 */ requestPacked(1,4,2,9);
/* 002d5c68: or v1,v0,a0 */ set(3,cpu(2)|cpu(4));
/* 002d5c6c: bne v1,zero,0x002d5ce4 */ {int taken=(cpu(3)!=cpu(0));/* delay 002d5c70 */ set(6,cpu(7));if(taken){goto L_002d5ce4;}}
L_002d5c74:;
/* 002d5c74: sq t1,0x0(a2) */ sq(9,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002d5c78: addiu a1,a1,0x10 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000010)));
/* 002d5c7c: lq t1,0x0(a1) */ requestLq(9,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5c80: psubb v0,t1,t2 */ requestPacked(4,2,9,10);
/* 002d5c84: pnor v1,zero,t1 */ requestPacked(3,3,0,9);
/* 002d5c88: pand v0,v0,v1 */ requestPacked(2,2,2,3);
/* 002d5c8c: pand v0,v0,t0 */ requestPacked(2,2,2,8);
/* 002d5c90: pcpyud a0,v0,t1 */ requestPacked(1,4,2,9);
/* 002d5c94: or v1,v0,a0 */ set(3,cpu(2)|cpu(4));
/* 002d5c98: beq v1,zero,0x002d5c74 */ {int taken=(cpu(3)==cpu(0));/* delay 002d5c9c */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000010)));if(taken){goto L_002d5c74;}}
/* 002d5ca0: b 0x002d5ce8 */ /* delay 002d5ca4 */ set(3,cpu(6));goto L_002d5ce8;
L_002d5ca8:;
/* 002d5ca8: dsubu v0,t2,t1 */ set(2,cpu(10)-cpu(9));
/* 002d5cac: nor v1,zero,t2 */ set(3,~(cpu(0)|cpu(10)));
/* 002d5cb0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002d5cb4: and v0,v0,a0 */ set(2,cpu(2)&cpu(4));
/* 002d5cb8: bne v0,zero,0x002d5ce4 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5cbc */ set(6,cpu(7));if(taken){goto L_002d5ce4;}}
L_002d5cc0:;
/* 002d5cc0: sd t2,0x0(a2) */ save(10,ea(6,(int32_t)UINT32_C(0x00000000)));
/* 002d5cc4: addiu a1,a1,0x8 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000008)));
/* 002d5cc8: ld t2,0x0(a1) */ restore(10,ea(5,(int32_t)UINT32_C(0x00000000)));
/* 002d5ccc: nor v0,zero,t2 */ set(2,~(cpu(0)|cpu(10)));
/* 002d5cd0: dsubu v1,t2,t1 */ set(3,cpu(10)-cpu(9));
/* 002d5cd4: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 002d5cd8: and v1,v1,a0 */ set(3,cpu(3)&cpu(4));
/* 002d5cdc: beq v1,zero,0x002d5cc0 */ {int taken=(cpu(3)==cpu(0));/* delay 002d5ce0 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000008)));if(taken){goto L_002d5cc0;}}
L_002d5ce4:;
/* 002d5ce4: move v1,a2 */ set(3,cpu(6));
L_002d5ce8:;
/* 002d5ce8: lbu v0,0x0(a1) */ set(2,byte(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 002d5cec: addiu a1,a1,0x1 */ set(5,sx((uint32_t)cpu(5)+UINT32_C(0x00000001)));
/* 002d5cf0: sb v0,0x0(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(2));
/* 002d5cf4: sll v0,v0,0x18 */ set(2,sx((uint32_t)cpu(2)<<24));
/* 002d5cf8: addiu v1,v1,0x1 */ set(3,sx((uint32_t)cpu(3)+UINT32_C(0x00000001)));
/* 002d5cfc: bne v0,zero,0x002d5ce8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002d5d00 */ if(taken){goto L_002d5ce8;}}
/* 002d5d04: jr ra */ {uint64_t target=cpu(31);/* delay 002d5d08 */ set(2,cpu(7));checkReturn(target,incoming);return;}
}
static void body_002dbc20(void){
uint64_t incoming=cpu(31);
/* 002dbc20: li v1,0xfc */ set(3,sx(UINT32_C(0x000000fc)));
/* 002dbc24: syscall 0x0 */ nocturneBattlePanelRendererRemainingSyscall(UINT32_C(0x002dbc24),cpu(3));
/* 002dbc28: jr ra */ {uint64_t target=cpu(31);/* delay 002dbc2c */ checkReturn(target,incoming);return;}
}
static void body_002dbdc0(void){
uint64_t incoming=cpu(31);
/* 002dbdc0: li v1,0x32 */ set(3,sx(UINT32_C(0x00000032)));
/* 002dbdc4: syscall 0x0 */ nocturneBattlePanelRendererRemainingSyscall(UINT32_C(0x002dbdc4),cpu(3));
/* 002dbdc8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbdcc */ checkReturn(target,incoming);return;}
}
static void body_002dbdf0(void){
uint64_t incoming=cpu(31);
/* 002dbdf0: li v1,0x35 */ set(3,sx(UINT32_C(0x00000035)));
/* 002dbdf4: syscall 0x0 */ nocturneBattlePanelRendererRemainingSyscall(UINT32_C(0x002dbdf4),cpu(3));
/* 002dbdf8: jr ra */ {uint64_t target=cpu(31);/* delay 002dbdfc */ checkReturn(target,incoming);return;}
}
static void body_002dc260(void){
uint64_t incoming=cpu(31);
/* 002dc260: li v1,0x77 */ set(3,sx(UINT32_C(0x00000077)));
/* 002dc264: syscall 0x0 */ nocturneBattlePanelRendererRemainingSyscall(UINT32_C(0x002dc264),cpu(3));
/* 002dc268: jr ra */ {uint64_t target=cpu(31);/* delay 002dc26c */ checkReturn(target,incoming);return;}
}
static void body_002dc270(void){
uint64_t incoming=cpu(31);
/* 002dc270: li v1,-0x77 */ set(3,sx(UINT32_C(0xffffff89)));
/* 002dc274: syscall 0x0 */ nocturneBattlePanelRendererRemainingSyscall(UINT32_C(0x002dc274),cpu(3));
/* 002dc278: jr ra */ {uint64_t target=cpu(31);/* delay 002dc27c */ checkReturn(target,incoming);return;}
}
static void body_002dc830(void){
uint64_t incoming=cpu(31);
/* 002dc830: lui a3,0xffff */ set(7,sx(UINT32_C(0xffff0000)));
/* 002dc834: move a2,zero */ set(6,cpu(0));
/* 002dc838: ori a3,a3,0xf000 */ set(7,cpu(7)|UINT32_C(0x0000f000));
/* 002dc83c: nop  */ 
L_002dc840:;
/* 002dc840: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc840),0u);
/* 002dc844: cache DXLTG,0x0(a2) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002dc844),16u,ea(6u,(int32_t)UINT32_C(0x00000000)));
/* 002dc848: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc848),0u);
/* 002dc84c: mfc0 v0,TagLo */ set(2u,sx(nocturneBattlePanelRendererRemainingCp0(UINT32_C(0x002dc84c),28u)));
/* 002dc850: and v0,v0,a3 */ set(2,cpu(2)&cpu(7));
/* 002dc854: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 002dc858: sltu v1,a1,v0 */ set(3,cpu(5)<cpu(2));
/* 002dc85c: sltu v0,v0,a0 */ set(2,cpu(2)<cpu(4));
/* 002dc860: bne v0,zero,0x002dc87c */ {int taken=(cpu(2)!=cpu(0));/* delay 002dc864 */ if(taken){goto L_002dc87c;}}
/* 002dc868: bne v1,zero,0x002dc87c */ {int taken=(cpu(3)!=cpu(0));/* delay 002dc86c */ if(taken){goto L_002dc87c;}}
/* 002dc870: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc870),0u);
/* 002dc874: cache DXIN,0x0(a2) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002dc874),22u,ea(6u,(int32_t)UINT32_C(0x00000000)));
/* 002dc878: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc878),0u);
L_002dc87c:;
/* 002dc87c: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc87c),0u);
/* 002dc880: cache DXLTG,0x1(a2) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002dc880),16u,ea(6u,(int32_t)UINT32_C(0x00000001)));
/* 002dc884: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc884),0u);
/* 002dc888: mfc0 v0,TagLo */ set(2u,sx(nocturneBattlePanelRendererRemainingCp0(UINT32_C(0x002dc888),28u)));
/* 002dc88c: and v0,v0,a3 */ set(2,cpu(2)&cpu(7));
/* 002dc890: addu v0,v0,a2 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(6)));
/* 002dc894: sltu v1,a1,v0 */ set(3,cpu(5)<cpu(2));
/* 002dc898: sltu v0,v0,a0 */ set(2,cpu(2)<cpu(4));
/* 002dc89c: bne v0,zero,0x002dc8b8 */ {int taken=(cpu(2)!=cpu(0));/* delay 002dc8a0 */ if(taken){goto L_002dc8b8;}}
/* 002dc8a4: bne v1,zero,0x002dc8b8 */ {int taken=(cpu(3)!=cpu(0));/* delay 002dc8a8 */ if(taken){goto L_002dc8b8;}}
/* 002dc8ac: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc8ac),0u);
/* 002dc8b0: cache DXIN,0x1(a2) */ nocturneBattlePanelRendererRemainingCache(UINT32_C(0x002dc8b0),22u,ea(6u,(int32_t)UINT32_C(0x00000001)));
/* 002dc8b4: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc8b4),0u);
L_002dc8b8:;
/* 002dc8b8: sync 0x0 */ nocturneBattlePanelRendererRemainingSync(UINT32_C(0x002dc8b8),0u);
/* 002dc8bc: addiu a2,a2,0x40 */ set(6,sx((uint32_t)cpu(6)+UINT32_C(0x00000040)));
/* 002dc8c0: slti v0,a2,0x1000 */ set(2,(int64_t)cpu(6)<(int64_t)(int32_t)UINT32_C(0x00001000));
/* 002dc8c4: bne v0,zero,0x002dc840 */ {int taken=(cpu(2)!=cpu(0));/* delay 002dc8c8 */ if(taken){goto L_002dc840;}}
/* 002dc8cc: jr ra */ {uint64_t target=cpu(31);/* delay 002dc8d0 */ checkReturn(target,incoming);return;}
}
static void body_002dc8d8(void){
uint64_t incoming=cpu(31);
/* 002dc8d8: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002dc8dc: sd s2,0x20(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dc8e0: sd s1,0x10(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dc8e4: move s2,a0 */ set(18,cpu(4));
/* 002dc8e8: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002dc8ec: move s1,a1 */ set(17,cpu(5));
/* 002dc8f0: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dc8f4: mfc0 s0,Status */ set(16u,sx(nocturneBattlePanelRendererRemainingCp0(UINT32_C(0x002dc8f4),12u)));
/* 002dc8f8: lui v0,0x1 */ set(2,sx(UINT32_C(0x00010000)));
/* 002dc8fc: and s0,s0,v0 */ set(16,cpu(16)&cpu(2));
/* 002dc900: beq s0,zero,0x002dc910 */ {int taken=(cpu(16)==cpu(0));/* delay 002dc904 */ if(taken){goto L_002dc910;}}
/* 002dc908: jal 0x002e4070 */ set(31,UINT64_C(0x002dc910));/* delay 002dc90c */ nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e4070),UINT32_C(0x002dc908));
L_002dc910:;
/* 002dc910: lui a0,0xffff */ set(4,sx(UINT32_C(0xffff0000)));
/* 002dc914: ori a0,a0,0xffc0 */ set(4,cpu(4)|UINT32_C(0x0000ffc0));
/* 002dc918: and a1,s1,a0 */ set(5,cpu(17)&cpu(4));
/* 002dc91c: jal 0x002dc830 */ set(31,UINT64_C(0x002dc924));/* delay 002dc920 */ set(4,cpu(18)&cpu(4));body_002dc830();
/* 002dc924: beq s0,zero,0x002dc940 */ {int taken=(cpu(16)==cpu(0));/* delay 002dc928 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));if(taken){goto L_002dc940;}}
/* 002dc92c: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dc930: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dc934: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dc938: j 0x002e40b8 */ /* delay 002dc93c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(cpu(31),incoming);nocturneBattlePanelRendererRemainingCall(UINT32_C(0x002e40b8),UINT32_C(0x002dc938));return;
L_002dc940:;
/* 002dc940: ld s2,0x20(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002dc944: ld s1,0x10(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002dc948: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002dc94c: jr ra */ {uint64_t target=cpu(31);/* delay 002dc950 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
static void body_002de178(void){
uint64_t incoming=cpu(31);
/* 002de178: addiu sp,sp,-0x80 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffff80)));
/* 002de17c: sd s1,0x30(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002de180: sd s4,0x60(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002de184: move s1,a3 */ set(17,cpu(7));
/* 002de188: sd s3,0x50(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002de18c: move s4,a0 */ set(20,cpu(4));
/* 002de190: sd s0,0x20(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de194: addiu v0,s1,-0x10 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0xfffffff0)));
/* 002de198: move s3,a1 */ set(19,cpu(5));
/* 002de19c: sd ra,0x70(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000070)));
/* 002de1a0: sd s2,0x40(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002de1a4: move s0,a2 */ set(16,cpu(6));
/* 002de1a8: move a0,t0 */ set(4,cpu(8));
/* 002de1ac: sltiu v0,v0,0x61 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000061));
/* 002de1b0: bne v0,zero,0x002de1c0 */ {int taken=(cpu(2)!=cpu(0));/* delay 002de1b4 */ set(5,cpu(10));if(taken){goto L_002de1c0;}}
/* 002de1b8: b 0x002de28c */ /* delay 002de1bc */ set(2,cpu(0));goto L_002de28c;
L_002de1c0:;
/* 002de1c0: blez a1,0x002de208 */ {int taken=((int64_t)cpu(5)<=0);/* delay 002de1c4 */ set(18,cpu(0));if(taken){goto L_002de208;}}
/* 002de1c8: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002de1cc: sll v1,a1,0x8 */ set(3,sx((uint32_t)cpu(5)<<8));
/* 002de1d0: sw t1,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(9));
/* 002de1d4: li s2,0x1 */ set(18,sx(UINT32_C(0x00000001)));
/* 002de1d8: or v0,v0,v1 */ set(2,cpu(2)|cpu(3));
/* 002de1dc: sw a0,0x0(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002de1e0: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002de1e4: andi v1,s3,0x4 */ set(3,cpu(19)&UINT32_C(0x00000004));
/* 002de1e8: sw t1,0x4(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(9));
/* 002de1ec: sw a1,0x8(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(5));
/* 002de1f0: beq v1,zero,0x002de214 */ {int taken=(cpu(3)==cpu(0));/* delay 002de1f4 */ sw(ea(29,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));if(taken){goto L_002de214;}}
/* 002de1f8: jal 0x002de458 */ set(31,UINT64_C(0x002de200));/* delay 002de1fc */ body_002de458();
/* 002de200: b 0x002de218 */ /* delay 002de204 */ set(5,sx((uint32_t)cpu(18)<<4));goto L_002de218;
L_002de208:;
/* 002de208: lbu v0,0x0(s0) */ set(2,byte(ea(16,(int32_t)UINT32_C(0x00000000))));
/* 002de20c: sw zero,0x4(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(0));
/* 002de210: sw v0,0x0(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
L_002de214:;
/* 002de214: sll a1,s2,0x4 */ set(5,sx((uint32_t)cpu(18)<<4));
L_002de218:;
/* 002de218: lui v0,0x5a */ set(2,sx(UINT32_C(0x005a0000)));
/* 002de21c: lw a0,-0x4560(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0xffffbaa0)));
/* 002de220: addu v1,sp,a1 */ set(3,sx((uint32_t)cpu(29)+(uint32_t)cpu(5)));
/* 002de224: sw s0,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 002de228: addiu v0,sp,0x4 */ set(2,sx((uint32_t)cpu(29)+UINT32_C(0x00000004)));
/* 002de22c: addu v0,v0,a1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(5)));
/* 002de230: addiu v1,sp,0x8 */ set(3,sx((uint32_t)cpu(29)+UINT32_C(0x00000008)));
/* 002de234: sw a0,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(4));
/* 002de238: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 002de23c: sw s1,0x0(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(17));
/* 002de240: addiu a0,sp,0xc */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x0000000c)));
/* 002de244: addu a0,a0,a1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 002de248: sw s4,0x8(s0) */ sw(ea(16,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(20));
/* 002de24c: sb s1,0x0(s0) */ sb(ea(16,(int32_t)UINT32_C(0x00000000)),(uint8_t)cpu(17));
/* 002de250: li v0,0x44 */ set(2,sx(UINT32_C(0x00000044)));
/* 002de254: sw v0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(2));
/* 002de258: move a1,s1 */ set(5,cpu(17));
/* 002de25c: move a0,s0 */ set(4,cpu(16));
/* 002de260: jal 0x002de458 */ set(31,UINT64_C(0x002de268));/* delay 002de264 */ set(18,sx((uint32_t)cpu(18)+UINT32_C(0x00000001)));body_002de458();
/* 002de268: andi v0,s3,0x1 */ set(2,cpu(19)&UINT32_C(0x00000001));
/* 002de26c: beq v0,zero,0x002de284 */ {int taken=(cpu(2)==cpu(0));/* delay 002de270 */ set(5,cpu(18));if(taken){goto L_002de284;}}
/* 002de274: jal 0x002dc270 */ set(31,UINT64_C(0x002de27c));/* delay 002de278 */ set(4,cpu(29));body_002dc270();
/* 002de27c: b 0x002de290 */ /* delay 002de280 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000070)));goto L_002de290;
L_002de284:;
/* 002de284: jal 0x002dc260 */ set(31,UINT64_C(0x002de28c));/* delay 002de288 */ set(4,cpu(29));body_002dc260();
L_002de28c:;
/* 002de28c: ld ra,0x70(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000070)));
L_002de290:;
/* 002de290: ld s4,0x60(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000060)));
/* 002de294: ld s3,0x50(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000050)));
/* 002de298: ld s2,0x40(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000040)));
/* 002de29c: ld s1,0x30(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002de2a0: ld s0,0x20(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002de2a4: jr ra */ {uint64_t target=cpu(31);/* delay 002de2a8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000080)));checkReturn(target,incoming);return;}
}
static void body_002de2b0(void){
uint64_t incoming=cpu(31);
/* 002de2b0: move v0,a2 */ set(2,cpu(6));
/* 002de2b4: move v1,a3 */ set(3,cpu(7));
/* 002de2b8: move t3,t0 */ set(11,cpu(8));
/* 002de2bc: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002de2c0: move t2,t1 */ set(10,cpu(9));
/* 002de2c4: move a2,a1 */ set(6,cpu(5));
/* 002de2c8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de2cc: move a3,v0 */ set(7,cpu(2));
/* 002de2d0: move t0,v1 */ set(8,cpu(3));
/* 002de2d4: move t1,t3 */ set(9,cpu(11));
/* 002de2d8: jal 0x002de178 */ set(31,UINT64_C(0x002de2e0));/* delay 002de2dc */ set(5,cpu(0));body_002de178();
/* 002de2e0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002de2e4: jr ra */ {uint64_t target=cpu(31);/* delay 002de2e8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
static void body_002acd98(void){
uint64_t incoming=cpu(31);
/* 002acd98: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002acd9c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002acda0: bne a1,v0,0x002acdb0 */ {int taken=(cpu(5)!=cpu(2));/* delay 002acda4 */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002acdb0;}}
/* 002acda8: jal 0x002acce0 */ set(31,UINT64_C(0x002acdb0));/* delay 002acdac */ set(5,cpu(6));body_002acce0();
L_002acdb0:;
/* 002acdb0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002acdb4: jr ra */ {uint64_t target=cpu(31);/* delay 002acdb8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelRendererRemainingBody(uint32_t entry){switch(entry){
case UINT32_C(0x002592b0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002592b0();return 1u;case UINT32_C(0x00267ec8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00267ec8();return 1u;case UINT32_C(0x0025e8e0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0025e8e0();return 1u;case UINT32_C(0x0025ea48):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0025ea48();return 1u;case UINT32_C(0x001c86a0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c86a0();return 1u;case UINT32_C(0x00101898):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00101898();return 1u;case UINT32_C(0x001c6098):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c6098();return 1u;case UINT32_C(0x001c8758):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c8758();return 1u;case UINT32_C(0x00257cc8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00257cc8();return 1u;case UINT32_C(0x0025d690):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0025d690();return 1u;case UINT32_C(0x001ce7d8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001ce7d8();return 1u;case UINT32_C(0x00267f18):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00267f18();return 1u;case UINT32_C(0x002d4748):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d4748();return 1u;case UINT32_C(0x002469c0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002469c0();return 1u;case UINT32_C(0x001b1740):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001b1740();return 1u;case UINT32_C(0x001c7a60):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c7a60();return 1u;case UINT32_C(0x00246ab8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00246ab8();return 1u;case UINT32_C(0x002627c0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002627c0();return 1u;case UINT32_C(0x002629e8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002629e8();return 1u;case UINT32_C(0x002642e0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002642e0();return 1u;case UINT32_C(0x00264368):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00264368();return 1u;case UINT32_C(0x00267788):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00267788();return 1u;case UINT32_C(0x002677b8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002677b8();return 1u;case UINT32_C(0x0026a468):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0026a468();return 1u;case UINT32_C(0x002a9688):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a9688();return 1u;case UINT32_C(0x001c8730):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c8730();return 1u;case UINT32_C(0x001c96d8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c96d8();return 1u;case UINT32_C(0x001c98c0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c98c0();return 1u;case UINT32_C(0x001c9a98):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c9a98();return 1u;case UINT32_C(0x001c9b58):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c9b58();return 1u;case UINT32_C(0x001c9c28):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c9c28();return 1u;case UINT32_C(0x001cf320):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001cf320();return 1u;case UINT32_C(0x001e9998):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001e9998();return 1u;case UINT32_C(0x00246a40):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00246a40();return 1u;case UINT32_C(0x00246b68):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00246b68();return 1u;case UINT32_C(0x00258de8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00258de8();return 1u;case UINT32_C(0x00259c48):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00259c48();return 1u;case UINT32_C(0x0025dc00):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0025dc00();return 1u;case UINT32_C(0x002645a8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002645a8();return 1u;case UINT32_C(0x002a8bd8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a8bd8();return 1u;case UINT32_C(0x002a9038):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a9038();return 1u;case UINT32_C(0x002a9540):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a9540();return 1u;case UINT32_C(0x002c10e8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c10e8();return 1u;case UINT32_C(0x002c1c20):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c1c20();return 1u;case UINT32_C(0x002dbdd0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dbdd0();return 1u;case UINT32_C(0x002de458):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002de458();return 1u;case UINT32_C(0x00173cb0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00173cb0();return 1u;case UINT32_C(0x00173ef0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00173ef0();return 1u;case UINT32_C(0x001c60e0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c60e0();return 1u;case UINT32_C(0x001c6b68):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c6b68();return 1u;case UINT32_C(0x001c7288):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c7288();return 1u;case UINT32_C(0x001c81b8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c81b8();return 1u;case UINT32_C(0x001c8508):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c8508();return 1u;case UINT32_C(0x001c87c8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c87c8();return 1u;case UINT32_C(0x001c8f08):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c8f08();return 1u;case UINT32_C(0x001c9188):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c9188();return 1u;case UINT32_C(0x001c9230):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c9230();return 1u;case UINT32_C(0x001c9d00):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001c9d00();return 1u;case UINT32_C(0x001cdd78):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001cdd78();return 1u;case UINT32_C(0x001ce538):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001ce538();return 1u;case UINT32_C(0x001ce5e8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001ce5e8();return 1u;case UINT32_C(0x001ce808):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001ce808();return 1u;case UINT32_C(0x001cf178):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001cf178();return 1u;case UINT32_C(0x001cf1a8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001cf1a8();return 1u;case UINT32_C(0x001cf440):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001cf440();return 1u;case UINT32_C(0x001cfc58):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001cfc58();return 1u;case UINT32_C(0x001cfc80):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001cfc80();return 1u;case UINT32_C(0x001cfe48):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_001cfe48();return 1u;case UINT32_C(0x002262e8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002262e8();return 1u;case UINT32_C(0x00243f40):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00243f40();return 1u;case UINT32_C(0x00245c90):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00245c90();return 1u;case UINT32_C(0x002514f0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002514f0();return 1u;case UINT32_C(0x00251538):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00251538();return 1u;case UINT32_C(0x002517e0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002517e0();return 1u;case UINT32_C(0x00259300):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00259300();return 1u;case UINT32_C(0x0025da78):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0025da78();return 1u;case UINT32_C(0x0025e9c8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0025e9c8();return 1u;case UINT32_C(0x0025ef10):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0025ef10();return 1u;case UINT32_C(0x00261ca0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00261ca0();return 1u;case UINT32_C(0x00261d20):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00261d20();return 1u;case UINT32_C(0x00262480):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00262480();return 1u;case UINT32_C(0x00262610):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00262610();return 1u;case UINT32_C(0x00262a68):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00262a68();return 1u;case UINT32_C(0x00262ac8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00262ac8();return 1u;case UINT32_C(0x00262b38):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00262b38();return 1u;case UINT32_C(0x00262bb8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00262bb8();return 1u;case UINT32_C(0x00262cc0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00262cc0();return 1u;case UINT32_C(0x00264010):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_00264010();return 1u;case UINT32_C(0x0026a3d8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_0026a3d8();return 1u;case UINT32_C(0x002a8520):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a8520();return 1u;case UINT32_C(0x002a9558):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002a9558();return 1u;case UINT32_C(0x002acce0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002acce0();return 1u;case UINT32_C(0x002c0f28):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c0f28();return 1u;case UINT32_C(0x002c1238):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c1238();return 1u;case UINT32_C(0x002c1240):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c1240();return 1u;case UINT32_C(0x002c18d8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c18d8();return 1u;case UINT32_C(0x002c1ca0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c1ca0();return 1u;case UINT32_C(0x002d57f8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d57f8();return 1u;case UINT32_C(0x002d5bf8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002d5bf8();return 1u;case UINT32_C(0x002dbc20):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dbc20();return 1u;case UINT32_C(0x002dbdc0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dbdc0();return 1u;case UINT32_C(0x002dbdf0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dbdf0();return 1u;case UINT32_C(0x002dc260):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dc260();return 1u;case UINT32_C(0x002dc270):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dc270();return 1u;case UINT32_C(0x002dc830):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dc830();return 1u;case UINT32_C(0x002dc8d8):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002dc8d8();return 1u;case UINT32_C(0x002de178):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002de178();return 1u;case UINT32_C(0x002de2b0):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002de2b0();return 1u;case UINT32_C(0x002acd98):if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002acd98();return 1u;
default:return 0u;}}
