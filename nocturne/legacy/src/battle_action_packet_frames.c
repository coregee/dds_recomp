/* Complete fixed original registered packet/queue/Counter dependencies.
 * Shared live CPU/FPR/RAM, true guest frames and native volatile carry into
 * printf are preserved. No expected data, stack patch or game-result provider.
 */
#include "battle_action_packet_frames.h"
#include "battle_action_consumer.h"
#include "battle_action_scale_lookup_frames.h"
#include "effect_host_bindings.h"
#include "effect_model_child_dependency_frames.h"
#include "effect_random_frames.h"
#include "anchor_callbacks.h"
#include "compiler_numeric.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
extern uint64_t nocturneEffectHostHi(void);
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){return *at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void sb(uint32_t a,uint8_t v){*at(a)=v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t o){return (uint32_t)cpu(r)+(uint32_t)o;}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
static void lw(unsigned r,uint32_t a){set(r,sx(word(a)));}
static uint32_t bits(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}
static void divideUnsigned(uint32_t n,uint32_t d){EE_ANCHOR_DIVU_STATE(d?n/d:UINT32_MAX,d?n%d:n);}

static uint64_t body_002515e8(void);
static uint64_t body_0026a7d0(void);
static void body_00247ed8(void);
static uint64_t body_002c0c60(void);
static uint64_t body_00101898(void);
static uint64_t body_0025e8e0(void);
static uint64_t body_0025ea48(void);
static void body_0025e9c8(void);
static uint64_t body_0025ef10(void);
static uint64_t body_00261ca0(void);
static uint64_t body_00261d20(void);
static uint64_t body_00261d90(void);
static uint64_t body_00261ff0(void);
static uint64_t body_002620f0(void);
static uint64_t body_00262170(void);
static uint64_t body_002621e0(void);
static uint64_t body_00262610(void);
static uint64_t body_00262670(void);
static void body_002627c0(void);
static void body_002628d0(void);
static uint64_t body_002629e8(void);
static uint64_t body_00262b38(void);
static uint64_t body_00262bb8(void);
static uint64_t body_00262c18(void);
static uint64_t body_00262cc0(void);
static uint64_t body_002630a8(void);
static uint64_t body_00263350(void);
static uint64_t body_002633e8(void);
static uint64_t body_00263458(void);
static uint64_t body_002635a8(void);
static uint64_t body_002638a0(void);
static uint64_t body_00264508(void);
static uint64_t body_00264528(void);
static uint64_t body_002645a8(void);
static uint64_t body_00267788(void);
static uint64_t body_00259ab0(void);
static uint64_t body_00259b70(void);
static uint64_t body_00259a30(void);
static uint64_t body_002515e8(void){
nocturneEffectAxisNoteEntry(0x002515e8u);
uint64_t incoming=cpu(31);
/* 002515e8: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002515ec: sll v1,a1,0x3 */ set(3,sx((uint32_t)cpu(5)<<3));
/* 002515f0: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002515f4: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 002515f8: move a0,a1 */ set(4,cpu(5));
/* 002515fc: lhu a1,0x8c(v1) */ set(5,half(ea(3,(int32_t)UINT32_C(0x0000008c))));
/* 00251600: bne a1,zero,0x00251618 */ {int taken=(cpu(5)!=cpu(0));/* delay 00251604 */ set(2,cpu(0));if(taken){goto L_00251618;}}
/* 00251608: jal 0x0026a7d0 */ set(31,0x00251610u);/* delay 0025160c */ body_0026a7d0();
/* 00251610: andi v0,v0,0x100 */ set(2,cpu(2)&UINT32_C(0x00000100));
/* 00251614: sltiu v0,v0,0x1 */ set(2,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));
L_00251618:;
/* 00251618: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025161c: jr ra */ {uint64_t target=cpu(31);/* delay 00251620 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002515E8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_002515e8();
}
static uint64_t body_0026a7d0(void){
nocturneEffectAxisNoteEntry(0x0026a7d0u);
uint64_t incoming=cpu(31);
/* 0026a7d0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026a7d4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026a7d8: jal 0x00246ab8 */ set(31,0x0026a7e0u);/* delay 0026a7dc */ ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 0026a7e0: move a0,v0 */ set(4,cpu(2));
/* 0026a7e4: beq a0,zero,0x0026a81c */ {int taken=(cpu(4)==cpu(0));/* delay 0026a7e8 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_0026a81c;}}
/* 0026a7ec: lw v1,0x0(a0) */ lw(3,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 0026a7f0: andi v1,v1,0x4 */ set(3,cpu(3)&UINT32_C(0x00000004));
/* 0026a7f4: bne v1,zero,0x0026a81c */ {int taken=(cpu(3)!=cpu(0));/* delay 0026a7f8 */ set(2,cpu(0));if(taken){goto L_0026a81c;}}
/* 0026a7fc: lhu v0,0x4(a0) */ set(2,half(ea(4,(int32_t)UINT32_C(0x00000004))));
/* 0026a800: sll v1,v0,0x4 */ set(3,sx((uint32_t)cpu(2)<<4));
/* 0026a804: subu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)-(uint32_t)cpu(2)));
/* 0026a808: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 0026a80c: lui v0,0x35 */ set(2,sx(UINT32_C(0x00350000)));
/* 0026a810: addu v0,v0,v1 */ set(2,sx((uint32_t)cpu(2)+(uint32_t)cpu(3)));
/* 0026a814: lw v0,-0x6840(v0) */ lw(2,ea(2,(int32_t)UINT32_C(0xffff97c0)));
/* 0026a818: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
L_0026a81c:;
/* 0026a81c: jr ra */ {uint64_t target=cpu(31);/* delay 0026a820 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_0026A7D0(uint64_t a0){
set(4,a0);
return body_0026a7d0();
}
static void body_00247ed8(void){
nocturneEffectAxisNoteEntry(0x00247ed8u);
uint64_t incoming=cpu(31);
/* 00247ed8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00247edc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00247ee0: move s0,a0 */ set(16,cpu(4));
/* 00247ee4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00247ee8: move s1,a1 */ set(17,cpu(5));
/* 00247eec: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00247ef0: move s2,a2 */ set(18,cpu(6));
/* 00247ef4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00247ef8: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00247efc: jal 0x002469a0 */ set(31,0x00247f04u);/* delay 00247f00 */ set(19,cpu(7));ps2BattleActionScaleLookup_002469A0();
/* 00247f04: lw a0,0x40(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 00247f08: lw a1,0x3c(v0) */ lw(5,ea(2,(int32_t)UINT32_C(0x0000003c)));
/* 00247f0c: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 00247f10: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00247f14: addu a0,a0,a1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 00247f18: sw s0,0x0(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(16));
/* 00247f1c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00247f20: lw v1,0x40(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 00247f24: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 00247f28: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00247f2c: sw s1,0x4(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(17));
/* 00247f30: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00247f34: lw a0,0x40(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 00247f38: sll a0,a0,0x4 */ set(4,sx((uint32_t)cpu(4)<<4));
/* 00247f3c: addu a0,a0,a1 */ set(4,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));
/* 00247f40: sw s2,0x8(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(18));
/* 00247f44: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00247f48: lw v1,0x40(v0) */ lw(3,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 00247f4c: sll v1,v1,0x4 */ set(3,sx((uint32_t)cpu(3)<<4));
/* 00247f50: addu v1,v1,a1 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(5)));
/* 00247f54: sw s3,0xc(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(19));
/* 00247f58: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00247f5c: lw a0,0x40(v0) */ lw(4,ea(2,(int32_t)UINT32_C(0x00000040)));
/* 00247f60: addiu a0,a0,0x1 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00000001)));
/* 00247f64: sw a0,0x40(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(4));
/* 00247f68: jr ra */ {uint64_t target=cpu(31);/* delay 00247f6c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPacket_00247ED8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
body_00247ed8();
}
static uint64_t body_002c0c60(void){
nocturneEffectAxisNoteEntry(0x002c0c60u);
uint64_t incoming=cpu(31);
/* 002c0c60: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 002c0c64: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0c68: sd ra,0x8(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0c6c: jal 0x002c0ba8 */ set(31,0x002c0c74u);/* delay 002c0c70 */ set(16,cpu(5));ps2EffectRandomWord_002C0BA8(cpu(4));
/* 002c0c74: divu v0,s0 */ divideUnsigned((uint32_t)cpu(2),(uint32_t)cpu(16));
/* 002c0c78: beql s0,zero,0x002c0c80 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 002c0c7c */ nocturneCompilerArithmeticTrap(7u);goto L_002c0c80;}}
L_002c0c80:;
/* 002c0c80: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c0c84: ld ra,0x8(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c0c88: mfhi v0 */ set(2,nocturneEffectHostHi());
/* 002c0c8c: jr ra */ {uint64_t target=cpu(31);/* delay 002c0c90 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002C0C60(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
return body_002c0c60();
}
static uint64_t body_00101898(void){
nocturneEffectAxisNoteEntry(0x00101898u);
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
/* 0010196c: jr ra */ {uint64_t target=cpu(31);/* delay 00101970 */ checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00101898(uint64_t a0){
set(4,a0);
return body_00101898();
}
static uint64_t body_0025e8e0(void){
nocturneEffectAxisNoteEntry(0x0025e8e0u);
uint64_t incoming=cpu(31);
/* 0025e8e0: lui a0,0x54 */ set(4,sx(UINT32_C(0x00540000)));
/* 0025e8e4: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0025e8e8: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025e8ec: jal 0x00101898 */ set(31,0x0025e8f4u);/* delay 0025e8f0 */ set(4,sx((uint32_t)cpu(4)+UINT32_C(0x00004350)));body_00101898();
/* 0025e8f4: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025e8f8: move a0,v0 */ set(4,cpu(2));
/* 0025e8fc: j 0x00101ab0 */ /* delay 0025e900 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(cpu(31),incoming);ps2BattleActionScaleLookup_00101AB0(cpu(4));return cpu(2);
}
uint64_t ps2BattleActionPacket_0025E8E0(void){

return body_0025e8e0();
}
static uint64_t body_0025ea48(void){
nocturneEffectAxisNoteEntry(0x0025ea48u);
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
/* 0025ea74: jal 0x002a8af8 */ set(31,0x0025ea7cu);/* delay 0025ea78 */ set(19,cpu(7));ps2EffectPoolAllocate_002A8AF8(cpu(4));
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
/* 0025eac4: jal 0x0025e9c8 */ set(31,0x0025eaccu);/* delay 0025eac8 */ sw(ea(16,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(0));body_0025e9c8();
/* 0025eacc: move v0,s0 */ set(2,cpu(16));
/* 0025ead0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025ead4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025ead8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025eadc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025eae0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0025eae4: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0025eae8: jr ra */ {uint64_t target=cpu(31);/* delay 0025eaec */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_0025EA48(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_0025ea48();
}
static void body_0025e9c8(void){
nocturneEffectAxisNoteEntry(0x0025e9c8u);
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
void ps2BattleActionPacket_0025E9C8(uint64_t a0, uint64_t a1){
set(4,a0);set(5,a1);
body_0025e9c8();
}
static uint64_t body_0025ef10(void){
nocturneEffectAxisNoteEntry(0x0025ef10u);
uint64_t incoming=cpu(31);
/* 0025ef10: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 0025ef14: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0025ef18: move s0,a0 */ set(16,cpu(4));
/* 0025ef1c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0025ef20: move s1,a2 */ set(17,cpu(6));
/* 0025ef24: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0025ef28: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0025ef2c: jal 0x002469a0 */ set(31,0x0025ef34u);/* delay 0025ef30 */ set(18,cpu(5));ps2BattleActionScaleLookup_002469A0();
/* 0025ef34: jal 0x00101ab0 */ set(31,0x0025ef3cu);/* delay 0025ef38 */ lw(4,ea(2,(int32_t)UINT32_C(0x000000f4)));ps2BattleActionScaleLookup_00101AB0(cpu(4));
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
/* 0025efc8: jr ra */ {uint64_t target=cpu(31);/* delay 0025efcc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_0025EF10(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_0025ef10();
}
static uint64_t body_00261ca0(void){
nocturneEffectAxisNoteEntry(0x00261ca0u);
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
/* 00261ccc: jal 0x0025e8e0 */ set(31,0x00261cd4u);/* delay 00261cd0 */ set(20,cpu(6));body_0025e8e0();
/* 00261cd4: move a0,v0 */ set(4,cpu(2));
/* 00261cd8: move a1,s0 */ set(5,cpu(16));
/* 00261cdc: move a3,s1 */ set(7,cpu(17));
/* 00261ce0: jal 0x0025ea48 */ set(31,0x00261ce8u);/* delay 00261ce4 */ set(6,cpu(0));body_0025ea48();
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
/* 00261d18: jr ra */ {uint64_t target=cpu(31);/* delay 00261d1c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00261CA0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
return body_00261ca0();
}
static uint64_t body_00261d20(void){
nocturneEffectAxisNoteEntry(0x00261d20u);
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
/* 00261d44: jal 0x0025e8e0 */ set(31,0x00261d4cu);/* delay 00261d48 */ set(19,cpu(6));body_0025e8e0();
/* 00261d4c: move a0,v0 */ set(4,cpu(2));
/* 00261d50: move a1,s0 */ set(5,cpu(16));
/* 00261d54: move a3,s1 */ set(7,cpu(17));
/* 00261d58: jal 0x0025ea48 */ set(31,0x00261d60u);/* delay 00261d5c */ set(6,cpu(0));body_0025ea48();
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
/* 00261d88: jr ra */ {uint64_t target=cpu(31);/* delay 00261d8c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00261D20(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_00261d20();
}
static uint64_t body_00261d90(void){
nocturneEffectAxisNoteEntry(0x00261d90u);
uint64_t incoming=cpu(31);
/* 00261d90: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00261d94: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261d98: move s0,a0 */ set(16,cpu(4));
/* 00261d9c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261da0: move s1,a1 */ set(17,cpu(5));
/* 00261da4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261da8: move s2,a3 */ set(18,cpu(7));
/* 00261dac: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261db0: move s3,t0 */ set(19,cpu(8));
/* 00261db4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261db8: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00261dbc: jal 0x0025e8e0 */ set(31,0x00261dc4u);/* delay 00261dc0 */ set(20,cpu(6));body_0025e8e0();
/* 00261dc4: move a0,v0 */ set(4,cpu(2));
/* 00261dc8: move a1,s0 */ set(5,cpu(16));
/* 00261dcc: move a3,s1 */ set(7,cpu(17));
/* 00261dd0: jal 0x0025ea48 */ set(31,0x00261dd8u);/* delay 00261dd4 */ set(6,cpu(0));body_0025ea48();
/* 00261dd8: li a0,0x7 */ set(4,sx(UINT32_C(0x00000007)));
/* 00261ddc: move v1,v0 */ set(3,cpu(2));
/* 00261de0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261de4: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00261de8: sw s4,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(20));
/* 00261dec: sw s3,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(19));
/* 00261df0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00261df4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00261df8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00261dfc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00261e00: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00261e04: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00261e08: jr ra */ {uint64_t target=cpu(31);/* delay 00261e0c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00261D90(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
return body_00261d90();
}
static uint64_t body_00261ff0(void){
nocturneEffectAxisNoteEntry(0x00261ff0u);
uint64_t incoming=cpu(31);
/* 00261ff0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00261ff4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00261ff8: move s0,a0 */ set(16,cpu(4));
/* 00261ffc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262000: move s1,a1 */ set(17,cpu(5));
/* 00262004: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262008: move s2,a3 */ set(18,cpu(7));
/* 0026200c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262010: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262014: jal 0x0025e8e0 */ set(31,0x0026201cu);/* delay 00262018 */ set(19,cpu(6));body_0025e8e0();
/* 0026201c: move a0,v0 */ set(4,cpu(2));
/* 00262020: move a1,s0 */ set(5,cpu(16));
/* 00262024: move a3,s1 */ set(7,cpu(17));
/* 00262028: jal 0x0025ea48 */ set(31,0x00262030u);/* delay 0026202c */ set(6,cpu(0));body_0025ea48();
/* 00262030: li a0,0x1b */ set(4,sx(UINT32_C(0x0000001b)));
/* 00262034: move v1,v0 */ set(3,cpu(2));
/* 00262038: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026203c: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00262040: sw s3,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 00262044: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262048: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 0026204c: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262050: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262054: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262058: jr ra */ {uint64_t target=cpu(31);/* delay 0026205c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00261FF0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_00261ff0();
}
static uint64_t body_002620f0(void){
nocturneEffectAxisNoteEntry(0x002620f0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002620f0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002620f4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002620f8: move s0,a0 */ set(16,cpu(4));
/* 002620fc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262100: move s1,a1 */ set(17,cpu(5));
/* 00262104: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262108: move s2,a3 */ set(18,cpu(7));
/* 0026210c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262110: move s3,a2 */ set(19,cpu(6));
/* 00262114: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262118: swc1 f20,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 0026211c: jal 0x0025e8e0 */ set(31,0x00262124u);/* delay 00262120 */ f[20]=f[12];body_0025e8e0();
/* 00262124: move a1,s0 */ set(5,cpu(16));
/* 00262128: move a3,s1 */ set(7,cpu(17));
/* 0026212c: move a0,v0 */ set(4,cpu(2));
/* 00262130: jal 0x0025ea48 */ set(31,0x00262138u);/* delay 00262134 */ set(6,cpu(0));body_0025ea48();
/* 00262138: li a0,0x9 */ set(4,sx(UINT32_C(0x00000009)));
/* 0026213c: move v1,v0 */ set(3,cpu(2));
/* 00262140: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262144: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00262148: sw s3,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 0026214c: swc1 f20,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 00262150: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262154: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262158: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026215c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262160: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262164: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262168: jr ra */ {uint64_t target=cpu(31);/* delay 0026216c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002620F0(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
nocturneEffectHostFpr()[12]=bits(f12);
return body_002620f0();
}
static uint64_t body_00262170(void){
nocturneEffectAxisNoteEntry(0x00262170u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00262170: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262174: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262178: move s0,a0 */ set(16,cpu(4));
/* 0026217c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262180: move s1,a1 */ set(17,cpu(5));
/* 00262184: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262188: move s2,a2 */ set(18,cpu(6));
/* 0026218c: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262190: swc1 f20,0x20(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000020)),f[20]);
/* 00262194: jal 0x0025e8e0 */ set(31,0x0026219cu);/* delay 00262198 */ f[20]=f[12];body_0025e8e0();
/* 0026219c: move a1,s0 */ set(5,cpu(16));
/* 002621a0: move a3,s1 */ set(7,cpu(17));
/* 002621a4: move a0,v0 */ set(4,cpu(2));
/* 002621a8: jal 0x0025ea48 */ set(31,0x002621b0u);/* delay 002621ac */ set(6,cpu(0));body_0025ea48();
/* 002621b0: li a0,0x35 */ set(4,sx(UINT32_C(0x00000035)));
/* 002621b4: move v1,v0 */ set(3,cpu(2));
/* 002621b8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002621bc: swc1 f20,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 002621c0: sw s2,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 002621c4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002621c8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002621cc: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002621d0: lwc1 f20,0x20(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002621d4: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002621d8: jr ra */ {uint64_t target=cpu(31);/* delay 002621dc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00262170(float f12, uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
nocturneEffectHostFpr()[12]=bits(f12);
return body_00262170();
}
static uint64_t body_002621e0(void){
nocturneEffectAxisNoteEntry(0x002621e0u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 002621e0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002621e4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002621e8: move s0,a0 */ set(16,cpu(4));
/* 002621ec: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002621f0: move s1,a1 */ set(17,cpu(5));
/* 002621f4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002621f8: move s2,a3 */ set(18,cpu(7));
/* 002621fc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262200: move s3,a2 */ set(19,cpu(6));
/* 00262204: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262208: swc1 f20,0x28(sp) */ sw(ea(29,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 0026220c: jal 0x0025e8e0 */ set(31,0x00262214u);/* delay 00262210 */ f[20]=f[12];body_0025e8e0();
/* 00262214: move a1,s0 */ set(5,cpu(16));
/* 00262218: move a3,s1 */ set(7,cpu(17));
/* 0026221c: move a0,v0 */ set(4,cpu(2));
/* 00262220: jal 0x0025ea48 */ set(31,0x00262228u);/* delay 00262224 */ set(6,cpu(0));body_0025ea48();
/* 00262228: li a0,0xa */ set(4,sx(UINT32_C(0x0000000a)));
/* 0026222c: move v1,v0 */ set(3,cpu(2));
/* 00262230: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262234: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00262238: sw s3,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 0026223c: swc1 f20,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),f[20]);
/* 00262240: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262244: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262248: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026224c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262250: lwc1 f20,0x28(sp) */ f[20]=word(ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00262254: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262258: jr ra */ {uint64_t target=cpu(31);/* delay 0026225c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002621E0(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
nocturneEffectHostFpr()[12]=bits(f12);
return body_002621e0();
}
static uint64_t body_00262610(void){
nocturneEffectAxisNoteEntry(0x00262610u);
uint64_t incoming=cpu(31);
/* 00262610: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262614: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262618: move s0,a0 */ set(16,cpu(4));
/* 0026261c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262620: move s1,a1 */ set(17,cpu(5));
/* 00262624: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262628: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026262c: jal 0x0025e8e0 */ set(31,0x00262634u);/* delay 00262630 */ set(18,cpu(6));body_0025e8e0();
/* 00262634: move a0,v0 */ set(4,cpu(2));
/* 00262638: move a1,s0 */ set(5,cpu(16));
/* 0026263c: move a3,s1 */ set(7,cpu(17));
/* 00262640: jal 0x0025ea48 */ set(31,0x00262648u);/* delay 00262644 */ set(6,cpu(0));body_0025ea48();
/* 00262648: li a0,0x18 */ set(4,sx(UINT32_C(0x00000018)));
/* 0026264c: move v1,v0 */ set(3,cpu(2));
/* 00262650: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262654: sw s2,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 00262658: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026265c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262660: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262664: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262668: jr ra */ {uint64_t target=cpu(31);/* delay 0026266c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00262610(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_00262610();
}
static uint64_t body_00262670(void){
nocturneEffectAxisNoteEntry(0x00262670u);
uint64_t incoming=cpu(31);
/* 00262670: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262674: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262678: move s0,a0 */ set(16,cpu(4));
/* 0026267c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262680: move s1,a1 */ set(17,cpu(5));
/* 00262684: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262688: move s2,a2 */ set(18,cpu(6));
/* 0026268c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262690: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262694: jal 0x0025e8e0 */ set(31,0x0026269cu);/* delay 00262698 */ set(19,cpu(7));body_0025e8e0();
/* 0026269c: move a0,v0 */ set(4,cpu(2));
/* 002626a0: move a1,s0 */ set(5,cpu(16));
/* 002626a4: move a2,zero */ set(6,cpu(0));
/* 002626a8: jal 0x0025ea48 */ set(31,0x002626b0u);/* delay 002626ac */ set(7,cpu(17));body_0025ea48();
/* 002626b0: li v1,0x20 */ set(3,sx(UINT32_C(0x00000020)));
/* 002626b4: move a0,v0 */ set(4,cpu(2));
/* 002626b8: li v0,0x17 */ set(2,sx(UINT32_C(0x00000017)));
/* 002626bc: move s0,zero */ set(16,cpu(0));
/* 002626c0: sb v0,0x4(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(2));
/* 002626c4: beq s3,v1,0x00262780 */ {int taken=(cpu(19)==cpu(3));/* delay 002626c8 */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));if(taken){goto L_00262780;}}
/* 002626cc: sltiu v0,s3,0x21 */ set(2,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000021));
/* 002626d0: beq v0,zero,0x00262720 */ {int taken=(cpu(2)==cpu(0));/* delay 002626d4 */ set(2,sx(UINT32_C(0x00000100)));if(taken){goto L_00262720;}}
/* 002626d8: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
/* 002626dc: beq s3,v0,0x00262770 */ {int taken=(cpu(19)==cpu(2));/* delay 002626e0 */ set(2,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000005));if(taken){goto L_00262770;}}
/* 002626e4: beq v0,zero,0x00262708 */ {int taken=(cpu(2)==cpu(0));/* delay 002626e8 */ set(2,sx(UINT32_C(0x00000008)));if(taken){goto L_00262708;}}
/* 002626ec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002626f0: beq s3,v0,0x00262768 */ {int taken=(cpu(19)==cpu(2));/* delay 002626f4 */ set(2,sx(UINT32_C(0x00000002)));if(taken){goto L_00262768;}}
/* 002626f8: beql s3,v0,0x0026279c */ {int taken=(cpu(19)==cpu(2));if(taken){/* delay 002626fc */ set(16,sx(UINT32_C(0x00000002)));goto L_0026279c;}}
/* 00262700: b 0x002627a0 */ /* delay 00262704 */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(16));goto L_002627a0;
L_00262708:;
/* 00262708: beq s3,v0,0x00262778 */ {int taken=(cpu(19)==cpu(2));/* delay 0026270c */ set(2,sx(UINT32_C(0x00000010)));if(taken){goto L_00262778;}}
/* 00262710: beql s3,v0,0x0026279c */ {int taken=(cpu(19)==cpu(2));if(taken){/* delay 00262714 */ set(16,sx(UINT32_C(0x00000005)));goto L_0026279c;}}
/* 00262718: b 0x002627a0 */ /* delay 0026271c */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(16));goto L_002627a0;
L_00262720:;
/* 00262720: beq s3,v0,0x00262790 */ {int taken=(cpu(19)==cpu(2));/* delay 00262724 */ set(2,cpu(19)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000101));if(taken){goto L_00262790;}}
/* 00262728: beq v0,zero,0x00262750 */ {int taken=(cpu(2)==cpu(0));/* delay 0026272c */ set(2,sx(UINT32_C(0x00000200)));if(taken){goto L_00262750;}}
/* 00262730: li v0,0x40 */ set(2,sx(UINT32_C(0x00000040)));
/* 00262734: beq s3,v0,0x00262788 */ {int taken=(cpu(19)==cpu(2));/* delay 00262738 */ set(2,sx(UINT32_C(0x00000080)));if(taken){goto L_00262788;}}
/* 0026273c: beql s3,v0,0x0026279c */ {int taken=(cpu(19)==cpu(2));if(taken){/* delay 00262740 */ set(16,sx(UINT32_C(0x00000008)));goto L_0026279c;}}
/* 00262744: b 0x002627a0 */ /* delay 00262748 */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(16));goto L_002627a0;
L_00262750:;
/* 00262750: beq s3,v0,0x00262798 */ {int taken=(cpu(19)==cpu(2));/* delay 00262754 */ set(2,sx(UINT32_C(0x00000400)));if(taken){goto L_00262798;}}
/* 00262758: beql s3,v0,0x0026279c */ {int taken=(cpu(19)==cpu(2));if(taken){/* delay 0026275c */ set(16,sx(UINT32_C(0x0000000b)));goto L_0026279c;}}
/* 00262760: b 0x002627a0 */ /* delay 00262764 */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(16));goto L_002627a0;
L_00262768:;
/* 00262768: b 0x0026279c */ /* delay 0026276c */ set(16,sx(UINT32_C(0x00000001)));goto L_0026279c;
L_00262770:;
/* 00262770: b 0x0026279c */ /* delay 00262774 */ set(16,sx(UINT32_C(0x00000003)));goto L_0026279c;
L_00262778:;
/* 00262778: b 0x0026279c */ /* delay 0026277c */ set(16,sx(UINT32_C(0x00000004)));goto L_0026279c;
L_00262780:;
/* 00262780: b 0x0026279c */ /* delay 00262784 */ set(16,sx(UINT32_C(0x00000006)));goto L_0026279c;
L_00262788:;
/* 00262788: b 0x0026279c */ /* delay 0026278c */ set(16,sx(UINT32_C(0x00000007)));goto L_0026279c;
L_00262790:;
/* 00262790: b 0x0026279c */ /* delay 00262794 */ set(16,sx(UINT32_C(0x00000009)));goto L_0026279c;
L_00262798:;
/* 00262798: li s0,0xa */ set(16,sx(UINT32_C(0x0000000a)));
L_0026279c:;
/* 0026279c: sw s0,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(16));
L_002627a0:;
/* 002627a0: move v0,a0 */ set(2,cpu(4));
/* 002627a4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002627a8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002627ac: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002627b0: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002627b4: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002627b8: jr ra */ {uint64_t target=cpu(31);/* delay 002627bc */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00262670(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_00262670();
}
static void body_002627c0(void){
nocturneEffectAxisNoteEntry(0x002627c0u);
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
/* 002627fc: jal 0x0025e8e0 */ set(31,0x00262804u);/* delay 00262800 */ set(22,cpu(8));body_0025e8e0();
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
/* 00262884: jal 0x0025ea48 */ set(31,0x0026288cu);/* delay 00262888 */ set(6,cpu(19));body_0025ea48();
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
void ps2BattleActionPacket_002627C0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);set(10,a6);
body_002627c0();
}
static void body_002628d0(void){
nocturneEffectAxisNoteEntry(0x002628d0u);
uint64_t incoming=cpu(31);
/* 002628d0: addiu sp,sp,-0x40 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffc0)));
/* 002628d4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002628d8: move s0,a0 */ set(16,cpu(4));
/* 002628dc: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002628e0: move s1,a2 */ set(17,cpu(6));
/* 002628e4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002628e8: move s2,a3 */ set(18,cpu(7));
/* 002628ec: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002628f0: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002628f4: move s4,t0 */ set(20,cpu(8));
/* 002628f8: sd s5,0x28(sp) */ save(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002628fc: sd ra,0x30(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 00262900: jal 0x0025e8e0 */ set(31,0x00262908u);/* delay 00262904 */ set(21,cpu(5));body_0025e8e0();
/* 00262908: move s3,v0 */ set(19,cpu(2));
/* 0026290c: lw a1,0x8(s3) */ lw(5,ea(19,(int32_t)UINT32_C(0x00000008)));
/* 00262910: beq a1,zero,0x0026297c */ {int taken=(cpu(5)==cpu(0));/* delay 00262914 */ set(2,sx(UINT32_C(0x00000004)));if(taken){goto L_0026297c;}}
/* 00262918: li a3,0x16 */ set(7,sx(UINT32_C(0x00000016)));
/* 0026291c: lb v0,0x4(a1) */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000004))));
L_00262920:;
/* 00262920: bne v0,a3,0x0026296c */ {int taken=(cpu(2)!=cpu(7));/* delay 00262924 */ lw(6,ea(5,(int32_t)UINT32_C(0x0000000c)));if(taken){goto L_0026296c;}}
/* 00262928: lw v0,0x8(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000008)));
/* 0026292c: bnel v0,s1,0x00262970 */ {int taken=(cpu(2)!=cpu(17));if(taken){/* delay 00262930 */ set(5,cpu(6));goto L_00262970;}}
/* 00262934: lw v0,0x14(a1) */ lw(2,ea(5,(int32_t)UINT32_C(0x00000014)));
/* 00262938: bnel v0,s2,0x00262970 */ {int taken=(cpu(2)!=cpu(18));if(taken){/* delay 0026293c */ set(5,cpu(6));goto L_00262970;}}
/* 00262940: lh v0,0x2(a1) */ set(2,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000002))));
/* 00262944: lh v1,0x0(a1) */ set(3,(uint64_t)(int64_t)(int16_t)half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 00262948: lhu a0,0x0(a1) */ set(4,half(ea(5,(int32_t)UINT32_C(0x00000000))));
/* 0026294c: addu v1,v1,v0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(2)));
/* 00262950: slt v1,s0,v1 */ set(3,(int64_t)cpu(16)<(int64_t)cpu(3));
/* 00262954: subu v0,s0,a0 */ set(2,sx((uint32_t)cpu(16)-(uint32_t)cpu(4)));
/* 00262958: beq v1,zero,0x0026296c */ {int taken=(cpu(3)==cpu(0));/* delay 0026295c */ set(4,sx((uint32_t)cpu(2)<<16));if(taken){goto L_0026296c;}}
/* 00262960: bgez a0,0x0026296c */ {int taken=((int64_t)cpu(4)>=0);/* delay 00262964 */ sh(ea(5,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(2));if(taken){goto L_0026296c;}}
/* 00262968: sh zero,0x2(a1) */ sh(ea(5,(int32_t)UINT32_C(0x00000002)),(uint16_t)cpu(0));
L_0026296c:;
/* 0026296c: move a1,a2 */ set(5,cpu(6));
L_00262970:;
/* 00262970: bnel a1,zero,0x00262920 */ {int taken=(cpu(5)!=cpu(0));if(taken){/* delay 00262974 */ set(2,(uint64_t)(int64_t)(int8_t)byte(ea(5,(int32_t)UINT32_C(0x00000004))));goto L_00262920;}}
/* 00262978: li v0,0x4 */ set(2,sx(UINT32_C(0x00000004)));
L_0026297c:;
/* 0026297c: bne s4,v0,0x0026299c */ {int taken=(cpu(20)!=cpu(2));/* delay 00262980 */ set(4,cpu(19));if(taken){goto L_0026299c;}}
/* 00262984: lui a2,0x1 */ set(6,sx(UINT32_C(0x00010000)));
/* 00262988: move a0,s0 */ set(4,cpu(16));
/* 0026298c: move a1,s1 */ set(5,cpu(17));
/* 00262990: jal 0x00262cc0 */ set(31,0x00262998u);/* delay 00262994 */ set(6,cpu(6)|UINT32_C(0x0000000a));body_00262cc0();
/* 00262998: move a0,s3 */ set(4,cpu(19));
L_0026299c:;
/* 0026299c: move a1,s0 */ set(5,cpu(16));
/* 002629a0: move a2,s5 */ set(6,cpu(21));
/* 002629a4: jal 0x0025ea48 */ set(31,0x002629acu);/* delay 002629a8 */ set(7,cpu(17));body_0025ea48();
/* 002629ac: li v1,0x16 */ set(3,sx(UINT32_C(0x00000016)));
/* 002629b0: move a1,v0 */ set(5,cpu(2));
/* 002629b4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002629b8: sw s4,0x28(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(20));
/* 002629bc: sw s2,0x14(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 002629c0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002629c4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002629c8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002629cc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002629d0: ld s5,0x28(sp) */ restore(21,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002629d4: ld ra,0x30(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000030)));
/* 002629d8: sb v1,0x4(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(3));
/* 002629dc: jr ra */ {uint64_t target=cpu(31);/* delay 002629e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000040)));checkReturn(target,incoming);return;}
}
void ps2BattleActionPacket_002628D0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
body_002628d0();
}
static uint64_t body_002629e8(void){
nocturneEffectAxisNoteEntry(0x002629e8u);
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
/* 00262a14: jal 0x0025e8e0 */ set(31,0x00262a1cu);/* delay 00262a18 */ set(20,cpu(6));body_0025e8e0();
/* 00262a1c: move a0,v0 */ set(4,cpu(2));
/* 00262a20: move a1,s0 */ set(5,cpu(16));
/* 00262a24: move a3,s1 */ set(7,cpu(17));
/* 00262a28: jal 0x0025ea48 */ set(31,0x00262a30u);/* delay 00262a2c */ set(6,cpu(0));body_0025ea48();
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
/* 00262a60: jr ra */ {uint64_t target=cpu(31);/* delay 00262a64 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002629E8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
return body_002629e8();
}
static uint64_t body_00262b38(void){
nocturneEffectAxisNoteEntry(0x00262b38u);
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
/* 00262b64: jal 0x0025e8e0 */ set(31,0x00262b6cu);/* delay 00262b68 */ set(20,cpu(6));body_0025e8e0();
/* 00262b6c: move a0,v0 */ set(4,cpu(2));
/* 00262b70: move a1,s0 */ set(5,cpu(16));
/* 00262b74: move a3,s1 */ set(7,cpu(17));
/* 00262b78: jal 0x0025ea48 */ set(31,0x00262b80u);/* delay 00262b7c */ set(6,cpu(0));body_0025ea48();
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
/* 00262bb0: jr ra */ {uint64_t target=cpu(31);/* delay 00262bb4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00262B38(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
return body_00262b38();
}
static uint64_t body_00262bb8(void){
nocturneEffectAxisNoteEntry(0x00262bb8u);
uint64_t incoming=cpu(31);
/* 00262bb8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 00262bbc: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262bc0: move s0,a0 */ set(16,cpu(4));
/* 00262bc4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262bc8: move s1,a1 */ set(17,cpu(5));
/* 00262bcc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262bd0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262bd4: jal 0x0025e8e0 */ set(31,0x00262bdcu);/* delay 00262bd8 */ set(18,cpu(6));body_0025e8e0();
/* 00262bdc: move a0,v0 */ set(4,cpu(2));
/* 00262be0: move a1,s0 */ set(5,cpu(16));
/* 00262be4: move a3,s1 */ set(7,cpu(17));
/* 00262be8: jal 0x0025ea48 */ set(31,0x00262bf0u);/* delay 00262bec */ set(6,cpu(0));body_0025ea48();
/* 00262bf0: li a0,0x14 */ set(4,sx(UINT32_C(0x00000014)));
/* 00262bf4: move v1,v0 */ set(3,cpu(2));
/* 00262bf8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262bfc: sw s2,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 00262c00: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262c04: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262c08: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262c0c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00262c10: jr ra */ {uint64_t target=cpu(31);/* delay 00262c14 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00262BB8(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_00262bb8();
}
static uint64_t body_00262c18(void){
nocturneEffectAxisNoteEntry(0x00262c18u);
uint64_t incoming=cpu(31);
/* 00262c18: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00262c1c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262c20: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262c24: move s1,a1 */ set(17,cpu(5));
/* 00262c28: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262c2c: move s2,a0 */ set(18,cpu(4));
/* 00262c30: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262c34: move s3,a2 */ set(19,cpu(6));
/* 00262c38: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262c3c: jal 0x00246ab8 */ set(31,0x00262c44u);/* delay 00262c40 */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(19,(int32_t)UINT32_C(0x00000092))));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00262c44: move s0,v0 */ set(16,cpu(2));
/* 00262c48: beql s0,zero,0x00262ca4 */ {int taken=(cpu(16)==cpu(0));if(taken){/* delay 00262c4c */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));goto L_00262ca4;}}
/* 00262c50: jal 0x0025e8e0 */ set(31,0x00262c58u);/* delay 00262c54 */ body_0025e8e0();
/* 00262c58: move a1,s2 */ set(5,cpu(18));
/* 00262c5c: move a0,v0 */ set(4,cpu(2));
/* 00262c60: move a3,s1 */ set(7,cpu(17));
/* 00262c64: jal 0x0025ea48 */ set(31,0x00262c6cu);/* delay 00262c68 */ set(6,cpu(0));body_0025ea48();
/* 00262c6c: li a0,0x200 */ set(4,sx(UINT32_C(0x00000200)));
/* 00262c70: move a1,v0 */ set(5,cpu(2));
/* 00262c74: li v0,0x24 */ set(2,sx(UINT32_C(0x00000024)));
/* 00262c78: sb v0,0x4(a1) */ sb(ea(5,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(2));
/* 00262c7c: sw s3,0x14(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 00262c80: lhu v1,0xe(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x0000000e))));
/* 00262c84: andi v1,v1,0xfff */ set(3,cpu(3)&UINT32_C(0x00000fff));
/* 00262c88: bne v1,a0,0x00262c98 */ {int taken=(cpu(3)!=cpu(4));/* delay 00262c8c */ set(2,cpu(5));if(taken){goto L_00262c98;}}
/* 00262c90: b 0x00262c9c */ /* delay 00262c94 */ set(3,sx(UINT32_C(0x000000ff)));goto L_00262c9c;
L_00262c98:;
/* 00262c98: lhu v1,0x4(s0) */ set(3,half(ea(16,(int32_t)UINT32_C(0x00000004))));
L_00262c9c:;
/* 00262c9c: sw v1,0x28(a1) */ sw(ea(5,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(3));
/* 00262ca0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_00262ca4:;
/* 00262ca4: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262ca8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262cac: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262cb0: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00262cb4: jr ra */ {uint64_t target=cpu(31);/* delay 00262cb8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00262C18(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_00262c18();
}
static uint64_t body_00262cc0(void){
nocturneEffectAxisNoteEntry(0x00262cc0u);
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
/* 00262ce4: jal 0x0025ef10 */ set(31,0x00262cecu);/* delay 00262ce8 */ set(16,cpu(4));body_0025ef10();
/* 00262cec: bne v0,zero,0x00262d20 */ {int taken=(cpu(2)!=cpu(0));/* delay 00262cf0 */ set(2,cpu(0));if(taken){goto L_00262d20;}}
/* 00262cf4: jal 0x0025e8e0 */ set(31,0x00262cfcu);/* delay 00262cf8 */ body_0025e8e0();
/* 00262cfc: move a1,s0 */ set(5,cpu(16));
/* 00262d00: move a0,v0 */ set(4,cpu(2));
/* 00262d04: move a3,s1 */ set(7,cpu(17));
/* 00262d08: jal 0x0025ea48 */ set(31,0x00262d10u);/* delay 00262d0c */ set(6,cpu(0));body_0025ea48();
/* 00262d10: li a0,0x19 */ set(4,sx(UINT32_C(0x00000019)));
/* 00262d14: move v1,v0 */ set(3,cpu(2));
/* 00262d18: sw s2,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(18));
/* 00262d1c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
L_00262d20:;
/* 00262d20: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00262d24: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00262d28: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00262d2c: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00262d30: jr ra */ {uint64_t target=cpu(31);/* delay 00262d34 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00262CC0(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_00262cc0();
}
static uint64_t body_002630a8(void){
nocturneEffectAxisNoteEntry(0x002630a8u);
uint64_t incoming=cpu(31);
/* 002630a8: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002630ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002630b0: move s0,a0 */ set(16,cpu(4));
/* 002630b4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002630b8: move s1,a1 */ set(17,cpu(5));
/* 002630bc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002630c0: sd ra,0x18(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002630c4: jal 0x0025e8e0 */ set(31,0x002630ccu);/* delay 002630c8 */ set(18,cpu(6));body_0025e8e0();
/* 002630cc: move a0,v0 */ set(4,cpu(2));
/* 002630d0: move a1,s0 */ set(5,cpu(16));
/* 002630d4: move a3,s1 */ set(7,cpu(17));
/* 002630d8: jal 0x0025ea48 */ set(31,0x002630e0u);/* delay 002630dc */ set(6,cpu(0));body_0025ea48();
/* 002630e0: li a0,0x2d */ set(4,sx(UINT32_C(0x0000002d)));
/* 002630e4: move v1,v0 */ set(3,cpu(2));
/* 002630e8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002630ec: sw s2,0x14(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(18));
/* 002630f0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002630f4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002630f8: ld ra,0x18(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002630fc: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00263100: sw zero,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(0));
/* 00263104: jr ra */ {uint64_t target=cpu(31);/* delay 00263108 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002630A8(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_002630a8();
}
static uint64_t body_00263350(void){
nocturneEffectAxisNoteEntry(0x00263350u);
uint64_t incoming=cpu(31);
/* 00263350: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 00263354: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263358: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026335c: move s1,a0 */ set(17,cpu(4));
/* 00263360: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263364: move s2,a1 */ set(18,cpu(5));
/* 00263368: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026336c: move s3,a2 */ set(19,cpu(6));
/* 00263370: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263374: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00263378: jal 0x0025e8e0 */ set(31,0x00263380u);/* delay 0026337c */ set(20,cpu(7));body_0025e8e0();
/* 00263380: move s0,v0 */ set(16,cpu(2));
/* 00263384: move a1,s1 */ set(5,cpu(17));
/* 00263388: move a0,s0 */ set(4,cpu(16));
/* 0026338c: move a3,s2 */ set(7,cpu(18));
/* 00263390: jal 0x0025ea48 */ set(31,0x00263398u);/* delay 00263394 */ set(6,cpu(0));body_0025ea48();
/* 00263398: lw v1,0x0(s0) */ lw(3,ea(16,(int32_t)UINT32_C(0x00000000)));
/* 0026339c: move a0,v0 */ set(4,cpu(2));
/* 002633a0: li a2,0x7 */ set(6,sx(UINT32_C(0x00000007)));
/* 002633a4: sw zero,0x40(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000040)),(uint32_t)cpu(0));
/* 002633a8: li a3,0x2e */ set(7,sx(UINT32_C(0x0000002e)));
/* 002633ac: sw s3,0x14(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000014)),(uint32_t)cpu(19));
/* 002633b0: lw a1,0x28(a0) */ lw(5,ea(4,(int32_t)UINT32_C(0x00000028)));
/* 002633b4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002633b8: sw a2,0x44(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000044)),(uint32_t)cpu(6));
/* 002633bc: sw a1,0x88(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000088)),(uint32_t)cpu(5));
/* 002633c0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002633c4: sw s4,0x28(a0) */ sw(ea(4,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(20));
/* 002633c8: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002633cc: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002633d0: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002633d4: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002633d8: sb a3,0x4(a0) */ sb(ea(4,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(7));
/* 002633dc: jr ra */ {uint64_t target=cpu(31);/* delay 002633e0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00263350(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_00263350();
}
static uint64_t body_002633e8(void){
nocturneEffectAxisNoteEntry(0x002633e8u);
uint64_t incoming=cpu(31);
/* 002633e8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002633ec: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002633f0: move s0,a0 */ set(16,cpu(4));
/* 002633f4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002633f8: move s1,a1 */ set(17,cpu(5));
/* 002633fc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263400: move s2,a3 */ set(18,cpu(7));
/* 00263404: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263408: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0026340c: jal 0x0025e8e0 */ set(31,0x00263414u);/* delay 00263410 */ set(19,cpu(6));body_0025e8e0();
/* 00263414: move a0,v0 */ set(4,cpu(2));
/* 00263418: move a1,s0 */ set(5,cpu(16));
/* 0026341c: move a3,s1 */ set(7,cpu(17));
/* 00263420: jal 0x0025ea48 */ set(31,0x00263428u);/* delay 00263424 */ set(6,cpu(0));body_0025ea48();
/* 00263428: li a0,0x2f */ set(4,sx(UINT32_C(0x0000002f)));
/* 0026342c: move v1,v0 */ set(3,cpu(2));
/* 00263430: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263434: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 00263438: sw s3,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(19));
/* 0026343c: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263440: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263444: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263448: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0026344c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00263450: jr ra */ {uint64_t target=cpu(31);/* delay 00263454 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002633E8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_002633e8();
}
static uint64_t body_00263458(void){
nocturneEffectAxisNoteEntry(0x00263458u);
uint64_t incoming=cpu(31);
/* 00263458: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0026345c: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00263460: move s0,a0 */ set(16,cpu(4));
/* 00263464: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00263468: move s1,a1 */ set(17,cpu(5));
/* 0026346c: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263470: move s2,a3 */ set(18,cpu(7));
/* 00263474: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263478: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 0026347c: jal 0x0025e8e0 */ set(31,0x00263484u);/* delay 00263480 */ set(19,cpu(6));body_0025e8e0();
/* 00263484: move a0,v0 */ set(4,cpu(2));
/* 00263488: move a1,s0 */ set(5,cpu(16));
/* 0026348c: move a3,s1 */ set(7,cpu(17));
/* 00263490: jal 0x0025ea48 */ set(31,0x00263498u);/* delay 00263494 */ set(6,cpu(0));body_0025ea48();
/* 00263498: li a0,0x30 */ set(4,sx(UINT32_C(0x00000030)));
/* 0026349c: move v1,v0 */ set(3,cpu(2));
/* 002634a0: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002634a4: sw s2,0x2c(v1) */ sw(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint32_t)cpu(18));
/* 002634a8: sw s3,0x28(v1) */ sw(ea(3,(int32_t)UINT32_C(0x00000028)),(uint32_t)cpu(19));
/* 002634ac: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002634b0: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002634b4: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002634b8: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002634bc: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 002634c0: jr ra */ {uint64_t target=cpu(31);/* delay 002634c4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00263458(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_00263458();
}
static uint64_t body_002635a8(void){
nocturneEffectAxisNoteEntry(0x002635a8u);
uint64_t incoming=cpu(31);
/* 002635a8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002635ac: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002635b0: move s0,a0 */ set(16,cpu(4));
/* 002635b4: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002635b8: move s1,a1 */ set(17,cpu(5));
/* 002635bc: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002635c0: move s2,t0 */ set(18,cpu(8));
/* 002635c4: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002635c8: move s3,a2 */ set(19,cpu(6));
/* 002635cc: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002635d0: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002635d4: jal 0x0025e8e0 */ set(31,0x002635dcu);/* delay 002635d8 */ set(20,cpu(7));body_0025e8e0();
/* 002635dc: move a0,v0 */ set(4,cpu(2));
/* 002635e0: move a1,s0 */ set(5,cpu(16));
/* 002635e4: move a3,s1 */ set(7,cpu(17));
/* 002635e8: jal 0x0025ea48 */ set(31,0x002635f0u);/* delay 002635ec */ set(6,cpu(0));body_0025ea48();
/* 002635f0: li a0,0x34 */ set(4,sx(UINT32_C(0x00000034)));
/* 002635f4: move v1,v0 */ set(3,cpu(2));
/* 002635f8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002635fc: sh s2,0x2c(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000002c)),(uint16_t)cpu(18));
/* 00263600: sh s3,0x28(v1) */ sh(ea(3,(int32_t)UINT32_C(0x00000028)),(uint16_t)cpu(19));
/* 00263604: sh s4,0x2a(v1) */ sh(ea(3,(int32_t)UINT32_C(0x0000002a)),(uint16_t)cpu(20));
/* 00263608: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 0026360c: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263610: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263614: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263618: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026361c: sb a0,0x4(v1) */ sb(ea(3,(int32_t)UINT32_C(0x00000004)),(uint8_t)cpu(4));
/* 00263620: jr ra */ {uint64_t target=cpu(31);/* delay 00263624 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002635A8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);
return body_002635a8();
}
static uint64_t body_002638a0(void){
nocturneEffectAxisNoteEntry(0x002638a0u);
uint64_t incoming=cpu(31);
/* 002638a0: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 002638a4: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002638a8: move s0,a0 */ set(16,cpu(4));
/* 002638ac: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002638b0: move s1,a1 */ set(17,cpu(5));
/* 002638b4: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002638b8: move s2,a2 */ set(18,cpu(6));
/* 002638bc: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002638c0: move s3,t0 */ set(19,cpu(8));
/* 002638c4: sd s4,0x20(sp) */ save(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002638c8: move s4,t2 */ set(20,cpu(10));
/* 002638cc: sd ra,0x28(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 002638d0: jal 0x00261ca0 */ set(31,0x002638d8u);/* delay 002638d4 */ set(8,cpu(9));body_00261ca0();
/* 002638d8: addu a0,s0,s3 */ set(4,sx((uint32_t)cpu(16)+(uint32_t)cpu(19)));
/* 002638dc: move a1,s1 */ set(5,cpu(17));
/* 002638e0: move a2,s2 */ set(6,cpu(18));
/* 002638e4: move t0,s4 */ set(8,cpu(20));
/* 002638e8: jal 0x00261d90 */ set(31,0x002638f0u);/* delay 002638ec */ set(7,cpu(0));body_00261d90();
/* 002638f0: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 002638f4: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002638f8: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002638fc: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00263900: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00263904: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00263908: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 0026390c: jr ra */ {uint64_t target=cpu(31);/* delay 00263910 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002638A0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);set(8,a4);set(9,a5);set(10,a6);
return body_002638a0();
}
static uint64_t body_00264508(void){
nocturneEffectAxisNoteEntry(0x00264508u);
uint64_t incoming=cpu(31);
/* 00264508: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026450c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00264510: jal 0x002630a8 */ set(31,0x00264518u);/* delay 00264514 */ body_002630a8();
/* 00264518: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 0026451c: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 00264520: jr ra */ {uint64_t target=cpu(31);/* delay 00264524 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00264508(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_00264508();
}
static uint64_t body_00264528(void){
nocturneEffectAxisNoteEntry(0x00264528u);
uint64_t incoming=cpu(31);
uint32_t *f=nocturneEffectHostFpr();
/* 00264528: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffd0)));
/* 0026452c: lui at,0x4188 */ set(1,sx(UINT32_C(0x41880000)));
/* 00264530: mtc1 at,f12 */ f[12]=(uint32_t)cpu(1);
/* 00264534: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00264538: move s0,a0 */ set(16,cpu(4));
/* 0026453c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00264540: move s1,a1 */ set(17,cpu(5));
/* 00264544: sd s2,0x10(sp) */ save(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00264548: move s2,a2 */ set(18,cpu(6));
/* 0026454c: sd s3,0x18(sp) */ save(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 00264550: sd ra,0x20(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00264554: jal 0x002621e0 */ set(31,0x0026455cu);/* delay 00264558 */ set(19,cpu(7));body_002621e0();
/* 0026455c: move a0,s0 */ set(4,cpu(16));
/* 00264560: move a1,s1 */ set(5,cpu(17));
/* 00264564: move a2,s2 */ set(6,cpu(18));
/* 00264568: jal 0x00262670 */ set(31,0x00264570u);/* delay 0026456c */ set(7,cpu(19));body_00262670();
/* 00264570: move a0,s0 */ set(4,cpu(16));
/* 00264574: move a1,s1 */ set(5,cpu(17));
/* 00264578: move a2,s2 */ set(6,cpu(18));
/* 0026457c: move a3,s3 */ set(7,cpu(19));
/* 00264580: jal 0x00262b38 */ set(31,0x00264588u);/* delay 00264584 */ set(8,sx(UINT32_C(0x00000001)));body_00262b38();
/* 00264588: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
/* 0026458c: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00264590: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 00264594: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 00264598: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 0026459c: ld ra,0x20(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 002645a0: jr ra */ {uint64_t target=cpu(31);/* delay 002645a4 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00264528(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3){
set(4,a0);set(5,a1);set(6,a2);set(7,a3);
return body_00264528();
}
static uint64_t body_002645a8(void){
nocturneEffectAxisNoteEntry(0x002645a8u);
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
/* 002645dc: jal 0x00267788 */ set(31,0x002645e4u);/* delay 002645e0 */ set(18,cpu(2)<(uint64_t)(int64_t)(int32_t)UINT32_C(0x00000001));body_00267788();
/* 002645e4: move s0,v0 */ set(16,cpu(2));
/* 002645e8: beq s0,zero,0x00264604 */ {int taken=(cpu(16)==cpu(0));/* delay 002645ec */ set(4,cpu(20));if(taken){goto L_00264604;}}
/* 002645f0: move a1,s3 */ set(5,cpu(19));
/* 002645f4: move a2,s1 */ set(6,cpu(17));
/* 002645f8: li a3,0xfff */ set(7,sx(UINT32_C(0x00000fff)));
/* 002645fc: jal 0x00262b38 */ set(31,0x00264604u);/* delay 00264600 */ set(8,cpu(0));body_00262b38();
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
/* 002646d0: jal 0x00262bb8 */ set(31,0x002646d8u);/* delay 002646d4 */ set(6,cpu(17));body_00262bb8();
/* 002646d8: move a0,s4 */ set(4,cpu(20));
/* 002646dc: move a1,s3 */ set(5,cpu(19));
/* 002646e0: jal 0x00262610 */ set(31,0x002646e8u);/* delay 002646e4 */ set(6,cpu(17));body_00262610();
/* 002646e8: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
L_002646ec:;
/* 002646ec: li v0,0x1 */ set(2,sx(UINT32_C(0x00000001)));
L_002646f0:;
/* 002646f0: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002646f4: ld s2,0x10(sp) */ restore(18,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002646f8: ld s3,0x18(sp) */ restore(19,ea(29,(int32_t)UINT32_C(0x00000018)));
/* 002646fc: ld s4,0x20(sp) */ restore(20,ea(29,(int32_t)UINT32_C(0x00000020)));
/* 00264700: ld ra,0x28(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000028)));
/* 00264704: jr ra */ {uint64_t target=cpu(31);/* delay 00264708 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000030)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_002645A8(uint64_t a0, uint64_t a1, uint64_t a2){
set(4,a0);set(5,a1);set(6,a2);
return body_002645a8();
}
static uint64_t body_00267788(void){
nocturneEffectAxisNoteEntry(0x00267788u);
uint64_t incoming=cpu(31);
/* 00267788: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 0026778c: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00267790: jal 0x00246ab8 */ set(31,0x00267798u);/* delay 00267794 */ ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00267798: move v1,v0 */ set(3,cpu(2));
/* 0026779c: beq v1,zero,0x002677ac */ {int taken=(cpu(3)==cpu(0));/* delay 002677a0 */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));if(taken){goto L_002677ac;}}
/* 002677a4: lhu v0,0xe(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x0000000e))));
/* 002677a8: andi v0,v0,0xfff */ set(2,cpu(2)&UINT32_C(0x00000fff));
L_002677ac:;
/* 002677ac: jr ra */ {uint64_t target=cpu(31);/* delay 002677b0 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00267788(uint64_t a0){
set(4,a0);
return body_00267788();
}
static uint64_t body_00259ab0(void){
nocturneEffectAxisNoteEntry(0x00259ab0u);
uint64_t incoming=cpu(31);
/* 00259ab0: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00259ab4: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259ab8: jal 0x00246ab8 */ set(31,0x00259ac0u);/* delay 00259abc */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000092))));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00259ac0: jal 0x00259a30 */ set(31,0x00259ac8u);/* delay 00259ac4 */ set(4,cpu(2));body_00259a30();
/* 00259ac8: move a0,v0 */ set(4,cpu(2));
/* 00259acc: beq a0,zero,0x00259b04 */ {int taken=(cpu(4)==cpu(0));/* delay 00259ad0 */ set(3,sx((uint32_t)cpu(4)<<2));if(taken){goto L_00259b04;}}
/* 00259ad4: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 00259ad8: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00259adc: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 00259ae0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00259ae4: lui at,0x3a */ set(1,sx(UINT32_C(0x003a0000)));
/* 00259ae8: addiu at,at,-0x7580 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffff8a80)));
/* 00259aec: addu v1,at,v1 */ set(3,sx((uint32_t)cpu(1)+(uint32_t)cpu(3)));
/* 00259af0: lhu a0,0x0(v1) */ set(4,half(ea(3,(int32_t)UINT32_C(0x00000000))));
/* 00259af4: bne a0,zero,0x00259b04 */ {int taken=(cpu(4)!=cpu(0));/* delay 00259af8 */ set(2,sx(UINT32_C(0x00000001)));if(taken){goto L_00259b04;}}
/* 00259afc: lhu v0,0x2(v1) */ set(2,half(ea(3,(int32_t)UINT32_C(0x00000002))));
/* 00259b00: sltu v0,zero,v0 */ set(2,cpu(0)<cpu(2));
L_00259b04:;
/* 00259b04: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259b08: jr ra */ {uint64_t target=cpu(31);/* delay 00259b0c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00259AB0(uint64_t a0){
set(4,a0);
return body_00259ab0();
}
static uint64_t body_00259b70(void){
nocturneEffectAxisNoteEntry(0x00259b70u);
uint64_t incoming=cpu(31);
/* 00259b70: addiu sp,sp,-0x10 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xfffffff0)));
/* 00259b74: sd ra,0x0(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259b78: jal 0x00246ab8 */ set(31,0x00259b80u);/* delay 00259b7c */ set(4,(uint64_t)(int64_t)(int16_t)half(ea(4,(int32_t)UINT32_C(0x00000092))));ps2BattleActionScaleLookup_00246AB8(cpu(4));
/* 00259b80: jal 0x00259a30 */ set(31,0x00259b88u);/* delay 00259b84 */ set(4,cpu(2));body_00259a30();
/* 00259b88: move a0,v0 */ set(4,cpu(2));
/* 00259b8c: beq a0,zero,0x00259bc0 */ {int taken=(cpu(4)==cpu(0));/* delay 00259b90 */ set(3,sx((uint32_t)cpu(4)<<2));if(taken){goto L_00259bc0;}}
/* 00259b94: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 00259b98: sll v1,v1,0x3 */ set(3,sx((uint32_t)cpu(3)<<3));
/* 00259b9c: addu v1,v1,a0 */ set(3,sx((uint32_t)cpu(3)+(uint32_t)cpu(4)));
/* 00259ba0: sll v1,v1,0x2 */ set(3,sx((uint32_t)cpu(3)<<2));
/* 00259ba4: lui at,0x3a */ set(1,sx(UINT32_C(0x003a0000)));
/* 00259ba8: addiu at,at,-0x7580 */ set(1,sx((uint32_t)cpu(1)+UINT32_C(0xffff8a80)));
/* 00259bac: addu v1,at,v1 */ set(3,sx((uint32_t)cpu(1)+(uint32_t)cpu(3)));
/* 00259bb0: lhu a0,0x2(v1) */ set(4,half(ea(3,(int32_t)UINT32_C(0x00000002))));
/* 00259bb4: beq a0,zero,0x00259bc0 */ {int taken=(cpu(4)==cpu(0));/* delay 00259bb8 */ set(2,cpu(0));if(taken){goto L_00259bc0;}}
/* 00259bbc: move v0,a0 */ set(2,cpu(4));
L_00259bc0:;
/* 00259bc0: ld ra,0x0(sp) */ restore(31,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 00259bc4: jr ra */ {uint64_t target=cpu(31);/* delay 00259bc8 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000010)));checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00259B70(uint64_t a0){
set(4,a0);
return body_00259b70();
}
static uint64_t body_00259a30(void){
nocturneEffectAxisNoteEntry(0x00259a30u);
uint64_t incoming=cpu(31);
/* 00259a30: lw v0,0x0(a0) */ lw(2,ea(4,(int32_t)UINT32_C(0x00000000)));
/* 00259a34: andi v0,v0,0x4 */ set(2,cpu(2)&UINT32_C(0x00000004));
/* 00259a38: bne v0,zero,0x00259a44 */ {int taken=(cpu(2)!=cpu(0));/* delay 00259a3c */ set(5,cpu(0));if(taken){goto L_00259a44;}}
/* 00259a40: lhu a1,0x4(a0) */ set(5,half(ea(4,(int32_t)UINT32_C(0x00000004))));
L_00259a44:;
/* 00259a44: lhu v1,0xe(a0) */ set(3,half(ea(4,(int32_t)UINT32_C(0x0000000e))));
/* 00259a48: li v0,0xff */ set(2,sx(UINT32_C(0x000000ff)));
/* 00259a4c: andi v1,v1,0xfff */ set(3,cpu(3)&UINT32_C(0x00000fff));
/* 00259a50: xori v1,v1,0x200 */ set(3,cpu(3)^UINT32_C(0x00000200));
/* 00259a54: jr ra */ {uint64_t target=cpu(31);/* delay 00259a58 */ if(cpu(3)!=0){set(2,cpu(5));}checkReturn(target,incoming);return cpu(2);}
}
uint64_t ps2BattleActionPacket_00259A30(uint64_t a0){
set(4,a0);
return body_00259a30();
}
uint32_t ps2BattleActionPacketRandomInt(uint32_t *state,uint32_t limit){
if((state?at((uint32_t)cpu(4))!= (uint8_t *)state:cpu(4)!=0)||limit!=(uint32_t)cpu(5))abort();
body_002c0c60();return (uint32_t)cpu(2);
}
